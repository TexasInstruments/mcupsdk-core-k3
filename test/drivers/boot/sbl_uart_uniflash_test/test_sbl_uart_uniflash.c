/*
 *  Copyright (C) 2024-2026 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * test_sbl_uart_uniflash.c
 *
 * Common test source for the SBL UART uniflash server.
 * Shared by both nortos and freertos builds on AM62DX and AM275X.
 *
 * ONE Unity test case: test_uniflashServer
 *   - Mirrors the exact functionality of
 *     examples/drivers/boot/sbl_uart_uniflash/am275x-evm/wkup-r5fss0-0_nortos/main.c
 *   - Receives files over XMODEM on CONFIG_UART0
 *   - Processes each uniflash command (flash/verify/erase/XIP/tuning-data)
 *   - Asserts the response header magic is always set correctly
 *   - Exits when the host sends the EOFT end-of-transfer marker
 *
 * Unity output is routed through debug_log to the wakeup UART (CONFIG_UART1),
 * independent of the XMODEM data channel (CONFIG_UART0).
 *
 * EOFT = 4 bytes {0x45, 0x4F, 0x46, 0x54} => 'E','O','F','T'
 * The host script (uart_uniflash.py) must send this as the last XMODEM frame.
 */

/*===================================================================*/
/* 					  Include Files 					     */
/*===================================================================*/

#include <stdlib.h>
#include <string.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/bootloader.h>
#include <drivers/bootloader/bootloader_xmodem.h>
#include <drivers/bootloader/bootloader_uniflash.h>
#include <kernel/dpl/DebugP.h>
#include <unity.h>

/*===================================================================*/
/* 					  Macro defines 					     */
/*===================================================================*/

/*
 * Use SOC-specific sizes matching the .bss.filebuf linker sections:
 *   AM275X: FILE_BUFF = 4 MB total  => 2 MB file buf + 2 MB verify buf
 *   AM62DX: DDR1      = 64 MB total => 32 MB file buf + 32 MB verify buf
 */
#if defined(SOC_AM275X)
#define BOOTLOADER_UNIFLASH_MAX_FILE_SIZE       (0x200000U)
#define BOOTLOADER_UNIFLASH_VERIFY_BUF_MAX_SIZE (0x200000U)
#else   /* AM62DX and similar */
#define BOOTLOADER_UNIFLASH_MAX_FILE_SIZE       (0x2000000U)
#define BOOTLOADER_UNIFLASH_VERIFY_BUF_MAX_SIZE (0x2000000U)
#endif

/*
 * The host script sends this 4-byte word as the last XMODEM frame to signal
 * end of test.  Pattern matches the convention used in sbl_test_uart_boot.
 * Add "--eot" or a dummy file containing these bytes at the end of the .cfg.
 */
#define BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH (4U)

/*===================================================================*/
/* 					     Typedefs 					         */
/*===================================================================*/

/*===================================================================*/
/* 					  Global Variables				         */
/*===================================================================*/

/*
 * Receive buffer — placed in the dedicated .bss.filebuf linker section
 * (FILE_BUFF on AM275X, DDR1 on AM62DX).
 * The XMODEM receive pointer is offset backwards by the response header size
 * so the uniflash library can read/write protocol headers in-place.
 */
uint8_t gUniflashFileBuf[BOOTLOADER_UNIFLASH_MAX_FILE_SIZE]
    __attribute__((aligned(128), section(".bss.filebuf")));

uint8_t gUniflashVerifyBuf[BOOTLOADER_UNIFLASH_VERIFY_BUF_MAX_SIZE]
    __attribute__((aligned(128), section(".bss.filebuf")));

static const uint8_t gEndOfFilesTransferWord[BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH] =
    {0x45U, 0x4FU, 0x46U, 0x54U};   /* 'E','O','F','T' */

/*===================================================================*/
/* 				  Function Declarations				         */
/*===================================================================*/

/*===================================================================*/
/* 				  Function Definitions				         */
/*===================================================================*/

/**
 * @brief Unity per-test setup hook.
 *
 * Called automatically by the Unity framework before each test case.
 * No special initialization is required for the uniflash server tests.
 *
 * @return void
 */
void setUp(void)    { /* nothing */ }

/**
 * @brief Unity per-test teardown hook.
 *
 * Called automatically by the Unity framework after each test case.
 * No special cleanup is required for the uniflash server tests.
 *
 * @return void
 */
void tearDown(void) { /* nothing */ }

/**
 * @brief XMODEM uniflash server loop test.
 *
 * Runs the XMODEM uniflash server loop, mirroring the functionality of
 * sbl_uart_uniflash. Receives files from the host over XMODEM, processes
 * each uniflash command, and verifies the response header is well-formed.
 *
 * Test Steps:
 * 1. Receive one XMODEM frame on CONFIG_UART0 into gUniflashFileBuf.
 * 2. Detect EOFT end-of-transfer marker and exit the loop if found.
 * 3. If XMODEM receive times out (no more files), exit cleanly.
 * 4. Detect buffer overflow and send an error response to the host.
 * 5. Parse the Bootloader_UniflashFileHeader from the received data.
 * 6. Call Bootloader_uniflashProcessFlashCommands() with the parsed config.
 * 7. Assert the response header magic is always BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER.
 * 8. Transmit the response header back to the host via CONFIG_UART0.
 * 9. Repeat until EOFT is received or XMODEM times out.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSblUartUniflash_uniflashServer(void *args)
{
    int32_t  status   = SystemP_SUCCESS;
    int32_t  txStatus = SystemP_SUCCESS;
    uint32_t done     = 0U;
    uint32_t fileSize = 0U;
    Bootloader_UniflashConfig         uniflashConfig = {0};
    Bootloader_UniflashResponseHeader respHeader     = {0};
    Bootloader_UniflashFileHeader     fileHeader     = {0};

    DebugP_log("\r\n[SBL UART UNIFLASH TEST] Uniflash server test started.\r\n");
    DebugP_log("[SBL UART UNIFLASH TEST] Waiting for files on UART0 (XMODEM)...\r\n");
    DebugP_log("[SBL UART UNIFLASH TEST] Send EOFT {0x45,0x4F,0x46,0x54} as last frame to end.\r\n");

    while(!done)
    {
        /*
         * Receive one XMODEM frame.
         * The buffer pointer is offset backwards by the response header size
         * so that the uniflash protocol library can read/write in-place.
         */
        status = Bootloader_xmodemReceive(CONFIG_UART0,
                     gUniflashFileBuf - sizeof(Bootloader_UniflashResponseHeader),
                     BOOTLOADER_UNIFLASH_MAX_FILE_SIZE,
                     &fileSize);

        /*
         * If the XMODEM receive times out (no more files from host), treat it as
         * a clean end-of-session rather than a test failure.
         * This is the normal exit path when uart_uniflash.py finishes sending.
         */
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("[SBL UART UNIFLASH TEST] XMODEM receive ended — no more files from host.\r\n");
            done = 1U;
            break;
        }

        /* Check for end-of-test signal (sent by uart_uniflash.py as EOFT magic) */
        if(memcmp(gUniflashFileBuf - sizeof(Bootloader_UniflashResponseHeader),
                  gEndOfFilesTransferWord,
                  BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH) == 0)
        {
            DebugP_log("[SBL UART UNIFLASH TEST] EOFT received — ending server loop.\r\n");
            done = 1U;
            break;
        }

        /*
         * The fileSize from xmodem includes ~1 KB padding overhead.
         * Check for gross overflow using this value.
         */
        if(fileSize >= BOOTLOADER_UNIFLASH_MAX_FILE_SIZE)
        {
            status = SystemP_FAILURE;
            respHeader.magicNumber = BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER;
            respHeader.statusCode  = BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR;

            txStatus = Bootloader_xmodemTransmit(CONFIG_UART0,
                (uint8_t *)&respHeader, sizeof(Bootloader_UniflashResponseHeader));
            TEST_ASSERT_EQUAL(SystemP_SUCCESS, txStatus);

            TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
                "Received file exceeded max buffer size");
        }

        if(status == SystemP_SUCCESS)
        {
            memcpy(&fileHeader,
                   gUniflashFileBuf - sizeof(Bootloader_UniflashResponseHeader),
                   sizeof(Bootloader_UniflashFileHeader));

            uniflashConfig.flashIndex    = Flash_getFlashInterfaceIndex(fileHeader.flashType);
            uniflashConfig.buf           = gUniflashFileBuf - sizeof(Bootloader_UniflashResponseHeader);
            uniflashConfig.bufSize       = 0; /* actual size is parsed from the header */
            uniflashConfig.verifyBuf     = gUniflashVerifyBuf;
            uniflashConfig.verifyBufSize = 0;

            /* Process the flash command */
            status = Bootloader_uniflashProcessFlashCommands(&uniflashConfig, &respHeader);

            /* Response magic MUST always be set regardless of outcome */
            TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER,
                                     respHeader.magicNumber);

            TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
                "Bootloader_uniflashProcessFlashCommands failed");

            DebugP_log("[SBL UART UNIFLASH TEST] Command result: 0x%08x\r\n",
                       respHeader.statusCode);

            status = Bootloader_xmodemTransmit(CONFIG_UART0,
                         (uint8_t *)&respHeader,
                         sizeof(Bootloader_UniflashResponseHeader));

            TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
                "XMODEM transmit of response header failed");
        }
    }

    DebugP_log("[SBL UART UNIFLASH TEST] Server loop finished.\r\n");
}

/**
 * @brief Main SBL UART uniflash test entry point.
 *
 * Entry point called from both nortos main() and freertos main_thread().
 * Initializes Unity, executes the uniflash server test case, and finalizes
 * the Unity framework. Unity output is routed through DebugP_log to the
 * wakeup UART (CONFIG_UART1).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(TestSblUartUniflash_uniflashServer, 11472, NULL);

    UNITY_END();
}


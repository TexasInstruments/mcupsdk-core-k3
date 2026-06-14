/*
 * Copyright (C) 2021-2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*===================================================================*/
/* 					  Include Files 					     */
/*===================================================================*/

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <drivers/bootloader.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/bootloader/bootloader_xmodem.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/bootloader/bootloader_profile.h>

/*===================================================================*/
/* 					  Macro defines 					     */
/*===================================================================*/

#define BOOTLOADER_UART_STATUS_LOAD_SUCCESS           (0x53554343) 
#define BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL          (0x4641494C) 
#define BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED (0x45584344) 

#define BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS          (5)
#define BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH  (4) 
#if defined(SOC_AM275X)
/* AM275x uses MCELF format.  The full MCELF file is received via XMODEM
 * and then parsed + loaded from memory. */
#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x100000U)
#define TEST_SBL_SCRATCH_BUF_SIZE        (0x1000U)
#else
#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x1900000)
#endif

/*===================================================================*/
/* 					     Typedefs 					         */
/*===================================================================*/

/*===================================================================*/
/* 					  Global Variables				         */
/*===================================================================*/

#if defined(SOC_AM275X)
static uint8_t gScratchBuf[TEST_SBL_SCRATCH_BUF_SIZE] __attribute__((aligned(128), section(".bss.app")));
#endif

/*===================================================================*/
/* 					     Typedefs 					         */
/*===================================================================*/

/*===================================================================*/
/* 					  Global Variables				         */
/*===================================================================*/

uint8_t gAppimage[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__ ((section (".bss.app"), aligned (128)));
uint8_t gEndOfFilesTransferWord[BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH] = {0x45,0x4F,0x46,0x54};

Bootloader_Handle bootHandle;
Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];
uint8_t socCpuCores[CSL_CORE_ID_MAX]    = {0};

/*===================================================================*/
/* 				  Function Declarations				         */
/*===================================================================*/

void TestSbl_uartBoot(void *args);
void TestSbl_uartSmpBoot(void *args);
static void TestSbl_uartBootImpl(bool isSmpBoot);

int32_t TestSbl_loadCpu();
int32_t TestSbl_runCpus();


/**
 * @brief Safe imgReadFxn that writes only 32-bit words to the destination.
 *
 * Utils_memcpyWord (the default) can generate byte-level STRB instructions when
 * the source and destination have different alignments or the length is not a
 * multiple of 4.  On ECC-protected AXI-connected SRAM (e.g. C75 L2 SRAM) a STRB
 * triggers a read-modify-write that reads an uninitialised ECC word, causing a
 * data abort.  Using only 32-bit word writes (STR) avoids this entirely, so the
 * SDK's Bootloader_socInitC7xL2Sram does not need to pre-initialise the full SRAM.
 *
 * Bytes are assembled word-by-word from the (possibly unaligned) source buffer
 * using byte loads — which are safe because the source lives in normal OCRAM.
 * Any sub-word tail is zero-padded; the extra zero bytes are beyond the ELF
 * segment boundary and have no effect on execution.
 *
 * This function is installed as a temporary override of imgReadFxn in
 * TestSbl_loadCpu() so the fix is fully contained within the test without
 * modifying any SDK library source.
 */
static int32_t TestSbl_safeImgRead(void *dst, uint32_t len, void *args)
{
    Bootloader_MemArgs *memArgs  = (Bootloader_MemArgs *)args;
    const uint8_t      *src8    = (const uint8_t *)(memArgs->appImageBaseAddr +
                                                     memArgs->curOffset);
    volatile uint32_t  *dst32   = (volatile uint32_t *)dst;
    uint32_t            i;
    uint32_t            fullWords = len >> 2U;
    uint32_t            remBytes  = len & 3U;

    /* Assemble each word from individual byte reads (handles unaligned source)
     * and write it as a single 32-bit store to avoid STRB on ECC SRAM. */
    for(i = 0U; i < fullWords; i++)
    {
        uint32_t w;
        w  = (uint32_t)src8[0];
        w |= (uint32_t)src8[1] << 8U;
        w |= (uint32_t)src8[2] << 16U;
        w |= (uint32_t)src8[3] << 24U;
        *dst32 = w;
        src8  += 4U;
        dst32++;
    }

    if(remBytes > 0U)
    {
        /* Tail bytes: zero-pad the unused bits and write one final 32-bit word. */
        uint32_t w = 0U;
        for(i = 0U; i < remBytes; i++)
        {
            w |= (uint32_t)src8[i] << (i * 8U);
        }
        *dst32 = w;
    }

    CacheP_wbInv(dst, len, CacheP_TYPE_ALL);
    memArgs->curOffset += len;
    return SystemP_SUCCESS;
}

/*===================================================================*/
/* 				  Function Definitions				         */
/*===================================================================*/

/**
 * @brief Unity per-test setup hook.
 *
 * Called automatically by the Unity framework before each test case.
 * No special initialization is required for the UART boot tests.
 *
 * @return void
 */
void setUp(void)
{
    /* Setup function nothing to perform */
}

/**
 * @brief Unity per-test teardown hook.
 *
 * Called automatically by the Unity framework after each test case.
 * No special cleanup is required for the UART boot tests.
 *
 * @return void
 */
void tearDown(void)
{
    /* Tear down function nothing to perform */
}

void loop_forever()
{
    volatile uint32_t loop = 1;
    DebugP_log("Inside the loop...\r\n");
    while(loop)
        ;
}

/**
 * @brief Main SBL UART boot test entry point.
 *
 * Initializes Unity, executes the UART SMP boot test case, and finalizes
 * the Unity framework.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void test_main(void * args)
{

    UNITY_BEGIN();

    /* Enable one test at a time due to SOC reset issue */
    /* RUN_TEST(TestSbl_uartBoot,    11448, NULL); */
    RUN_TEST(TestSbl_uartSmpBoot, 11449, NULL);

    UNITY_END();
}

/**
 * @brief Common UART boot implementation for both SMP and non-SMP modes.
 *
 * Receives appimages over XMODEM, loads and boots the embedded cores,
 * waits for IPC sync, then resets CPUs.
 *
 * @param[in] isSmpBoot true to run as SMP boot, false for single-image boot.
 *
 * @return void
 */
static void TestSbl_uartBootImpl(bool isSmpBoot)
{
    int32_t     status        = SystemP_SUCCESS;
    int32_t     txStatus      = SystemP_SUCCESS;
    int32_t     xmitStatus    = SystemP_SUCCESS;
    bool        bEndOfTransfer;
    uint32_t    fileSize;
    uint32_t    response;
    const char *testName      = isSmpBoot ? "TestSbl_uartSmpBoot" : "TestSbl_uartBoot";

    bEndOfTransfer = false;
    response = BOOTLOADER_UART_STATUS_LOAD_SUCCESS;

    Bootloader_profileReset();

    while(bEndOfTransfer == false)
    {
        status = Bootloader_xmodemReceive(CONFIG_UART0, gAppimage, BOOTLOADER_APPIMAGE_MAX_FILE_SIZE, &fileSize);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

        if(memcmp(gAppimage, gEndOfFilesTransferWord, BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH) == 0)
        {
            bEndOfTransfer = true;
            DebugP_log("Starting %s: All images received, running CPUs...\r\n", testName);
            Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_UART, 0);
            Bootloader_profileAddProfilePoint("Running CPUs");
            ClockP_sleep(BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS);
            status = TestSbl_runCpus();
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_profilePrintProfileLog();
            DebugP_log("%s: All CPUs booted and IPC sync done successfully!\r\n", testName);
        }
        else
        {
            if(SystemP_SUCCESS == status && fileSize == BOOTLOADER_APPIMAGE_MAX_FILE_SIZE)
            {
                status = SystemP_FAILURE;
                response = BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED;
                txStatus = Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
                TEST_ASSERT_EQUAL(SystemP_SUCCESS, txStatus);
            }

            if(SystemP_SUCCESS == status)
            {
                status = TestSbl_loadCpu();

                if(status != SystemP_SUCCESS)
                {
                    response = BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL;
                }
                else
                {
                    Bootloader_profileAddProfilePoint("UART Image Load");
                }
                xmitStatus = Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
                TEST_ASSERT_EQUAL(SystemP_SUCCESS, xmitStatus);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }
}

/**
 * @brief UART single-image boot test.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uartBoot(void *args)
{
    TestSbl_uartBootImpl(false);
}

/**
 * @brief UART SMP boot test.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uartSmpBoot(void *args)
{
    TestSbl_uartBootImpl(true);
}

/**
 * @brief Run all loaded CPUs, wait for IPC sync, and reset.
 *
 * Iterates over all core IDs, runs each loaded core via Bootloader_runCpu,
 * waits for IPC sync from each, and resets them to their original state.
 *
 * @return int32_t SystemP_SUCCESS if all cores booted and synced, SystemP_FAILURE otherwise.
 */
int32_t TestSbl_runCpus()
{
    int32_t status = SystemP_SUCCESS;
    uint8_t cpuId;

    status = SystemP_FAILURE;

    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        DebugP_log("CPU %d: Booting...\r\n", cpuId);
        if(socCpuCores[cpuId] == BOOTLOADER_IMAGE_LOADED)
        {
            DebugP_log("CPU %d: Image loaded, running CPU...\r\n", cpuId);
#if !defined(SOC_AM275X)
            if (((cpuId == CSL_CORE_ID_MCU_R5FSS0_0) && !Bootloader_socIsMCUResetIsoEnabled()) ||
                (cpuId != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
                {
                    DebugP_log("CPU %d: Running CPU...\r\n", cpuId);
                    status = Bootloader_runCpu(bootHandle, &bootCpuInfo[cpuId]);
                    DebugP_log("CPU %d: Bootloader_runCpu status = %d\r\n", cpuId, status);
                }
        }
    }

    /* Wait for sync from each loaded core using IPC */
    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        if(socCpuCores[cpuId] == BOOTLOADER_IMAGE_LOADED)
        {
#if !defined(SOC_AM275X)
            if (((cpuId == CSL_CORE_ID_MCU_R5FSS0_0) && !Bootloader_socIsMCUResetIsoEnabled()) ||
                (cpuId != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("CPU %d: Waiting for IPC sync...\r\n", cpuId);
                status = IpcNotify_waitSync(cpuId, 30);
                DebugP_log("CPU %d: IPC sync status = %d\r\n", cpuId, status);
            }
        }
    }

    /* Reset the CPUs to the original state */
    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        if(socCpuCores[cpuId] == BOOTLOADER_IMAGE_LOADED)
        {
            status = Bootloader_socCpuRequest(bootCpuInfo[cpuId].cpuId);
            Bootloader_socCpuPowerOff(bootCpuInfo[cpuId].cpuId);
            status = Bootloader_socCpuRelease(bootCpuInfo[cpuId].cpuId);
            DebugP_log("CPU %d: Reset complete\r\n", cpuId);
        }
    }

    Bootloader_close(bootHandle);
    return status;
}

/**
 * @brief Parse and load a received appimage to the appropriate CPU cores.
 *
 * Opens the bootloader, parses the multi-core appimage, and loads each
 * present core (MCU R5, A53, C75). Handles SMP detection for A53 cores.
 * On AM275x, uses MCELF format via Bootloader_parseAndLoadMultiCoreELF.
 *
 * @return int32_t SystemP_SUCCESS if parsing and loading succeeded, SystemP_FAILURE otherwise.
 */
int32_t TestSbl_loadCpu()
{
    int32_t                status = SystemP_SUCCESS;
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params        bootParams;
    

    /* The test executable to be booted is ipc_rpmsg
     * system project for AM62DX which has the following
     * cores enabled
     */
    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    bootParams.bufIoTempBuf     = gAppimage;
    bootParams.bufIoTempBufSize = BOOTLOADER_APPIMAGE_MAX_FILE_SIZE;
    bootParams.bufIoDeviceIndex = CONFIG_UART0;
    bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppimage;

    bootHandle = Bootloader_open(CONFIG_BOOTLOADER0, &bootParams);
    if(bootHandle != NULL)
    {
#if defined(SOC_AM275X)
        /*
         * AM275x uses MCELF format.  The full MCELF file was received via
         * XMODEM into gAppimage.  Override bootMedia to EMMC so that
         * Bootloader_parseAndLoadMultiCoreELF takes the SD/EMMC auth code
         * path (seek+read+authUpdate).  The underlying imgReadFxn/imgSeekFxn
         * still read from the memory buffer.
         */
        
        static Bootloader_Fxns   sCustomFxns;
        Bootloader_Config       *bootConfig = NULL;
        {
            bootConfig = (Bootloader_Config *)bootHandle;
            bootConfig->coresPresentMap = 0;
            bootConfig->bootMedia       = BOOTLOADER_MEDIA_EMMC;
            bootConfig->scratchMemPtr   = gScratchBuf;

            /* Install a safe imgReadFxn that uses memcpy so all segment sizes
             * work correctly.  Utils_memcpyWord (the default) aligns the source
             * before doing 32-bit word stores; when source and destination have
             * different initial alignments and the length is not a multiple of 4
             * the destination ends up misaligned for those stores.  A misaligned
             * 32-bit STR to AXI-connected SRAM (e.g. C75 L2 SRAM) causes a bus
             * fault.  We create a local copy of the Fxns struct so the global
             * default is not modified. */
            sCustomFxns              = *bootConfig->fxns;
            sCustomFxns.imgReadFxn   = TestSbl_safeImgRead;
            bootConfig->fxns         = &sCustomFxns;
        }

        status = Bootloader_parseAndLoadMultiCoreELF(bootHandle, &bootImageInfo);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("Bootloader_parseAndLoadMultiCoreELF failed, status = %d\r\n", status);
        }
        else
        {
            /* Record which cores were loaded so TestSbl_runCpus can run them */
            Bootloader_Config *config = (Bootloader_Config *)bootHandle;
            uint8_t cpuId;
            for(cpuId = 0U; cpuId < CSL_CORE_ID_MAX; cpuId++)
            {
                if(config->coresPresentMap & ((uint32_t)1U << cpuId))
                {
                    socCpuCores[cpuId] = BOOTLOADER_IMAGE_LOADED;
                    bootCpuInfo[cpuId] = bootImageInfo.cpuInfo[cpuId];
                    Bootloader_profileAddCore(cpuId);
                }
            }
        }
#else
        status = Bootloader_parseMultiCoreAppImage(bootHandle, &bootImageInfo);

        if(status != SystemP_SUCCESS)
        {
            DebugP_log("Bootloader_parseMultiCoreAppImage failed with status = %d\r\n", status);
        }

        /* Load CPUs */
        if ((status == SystemP_SUCCESS) && !Bootloader_socIsMCUResetIsoEnabled())
        {
            if((TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MCU_R5FSS0_0)))
            {
                bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                socCpuCores[CSL_CORE_ID_MCU_R5FSS0_0] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_MCU_R5FSS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0];
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
            }
        }
        if(((status == SystemP_SUCCESS) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS0_0))))
        {
            if(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0].smpEnable != true)
            {
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0]));
                socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0];
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
            }
            else
            {
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_1].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_1);
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS1_0);
                bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_1].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS1_1);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0]));

                socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0];
                socCpuCores[CSL_CORE_ID_A53SS0_1] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS0_1] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_1];
                socCpuCores[CSL_CORE_ID_A53SS1_0] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS1_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0];
                socCpuCores[CSL_CORE_ID_A53SS1_1] = BOOTLOADER_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_A53SS1_1] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_1];
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_1);
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS1_0);
                Bootloader_profileAddCore(CSL_CORE_ID_A53SS1_1);

            }
        }
        if(((status == SystemP_SUCCESS) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_C75SS0_0))))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0]));
            socCpuCores[CSL_CORE_ID_C75SS0_0] = BOOTLOADER_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0];
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS0_0);
        }
#endif
        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandle));
    }
    return status;
}


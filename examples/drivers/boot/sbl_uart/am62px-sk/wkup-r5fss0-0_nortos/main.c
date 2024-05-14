/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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


#include <stdlib.h>
#include <string.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>
#include <drivers/pinmux.h>
#include <drivers/gtc.h>
#include <drivers/bootloader/bootloader_xmodem.h>
#include <drivers/bootloader/bootloader_buf_io.h>
#include <stdbool.h>

#define BOOTLOADER_UART_STATUS_LOAD_SUCCESS           (0x53554343) /* SUCC */
#define BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL          (0x4641494C) /* FAIL */
#define BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED (0x45584344) /* EXCD */

#define BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS          (5)
#define BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH  (4) /* bytes */
#define BOOTLOADER_APP_IMAGE_LOADED                   (1)

#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x2000000) /* Max size of the file that xmodem can receive */
uint8_t gAppImageBuf[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

uint8_t gEndOfFilesTransferWord[BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH] = {0x45,0x4F,0x46,0x54}; /* Contain Magic word Indicating End Of File Transfer(EOFT) */
uint8_t socCpuCores[CSL_CORE_ID_MAX]    = {0};

extern Bootloader_MemArgs gBootloader0Args;
extern Bootloader_MemArgs gBootloader1Args;
extern Bootloader_MemArgs gBootloader2Args;

Bootloader_Handle bootHandle;
Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

/* call this API to stop the booting process and spin, do that you can connect
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1;
    while(loop)
        ;
}

int32_t App_loadImages(void)
{
	int32_t status = SystemP_FAILURE;

    Bootloader_BootImageInfo bootImageInfo;
	Bootloader_Params bootParams;
    Bootloader_Config *bootConfig;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    bootParams.bufIoTempBuf     = gAppImageBuf;
    bootParams.bufIoTempBufSize = BOOTLOADER_APPIMAGE_MAX_FILE_SIZE;
    bootParams.bufIoDeviceIndex = CONFIG_UART0;
    bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;

    bootHandle = Bootloader_open(CONFIG_BOOTLOADER0, &bootParams);

    if(bootHandle != NULL)
    {
        bootConfig = (Bootloader_Config *)bootHandle;
        bootConfig->coresPresentMap = 0;
        status = Bootloader_parseMultiCoreAppImage(bootHandle, &bootImageInfo);

        /* Load CPUs */
        if (!Bootloader_socIsMCUResetIsoEnabled())
        {
            if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MCU_R5FSS0_0)))
            {
                bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                socCpuCores[CSL_CORE_ID_MCU_R5FSS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_MCU_R5FSS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0];
            }
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_WKUP_R5FSS0_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_WKUP_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0]));
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS0_0)))
		{
			bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
			status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0]));
            socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0];
		}
    }

    return status;
}

int32_t App_runCpus(void)
{
    int32_t status = SystemP_FAILURE;
    uint8_t cpuId;

    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        if(socCpuCores[cpuId] == BOOTLOADER_APP_IMAGE_LOADED)
        {
            if (((cpuId == CSL_CORE_ID_MCU_R5FSS0_0) && !Bootloader_socIsMCUResetIsoEnabled()) ||
                (cpuId != CSL_CORE_ID_MCU_R5FSS0_0))
                {
                    status = Bootloader_runCpu(bootHandle, &bootCpuInfo[cpuId]);
                }
        }
    }
    Bootloader_close(bootHandle);
    return status;
}

int main()
{
    int32_t status;

    bool    bEndOfTransfer = false;

    Bootloader_socWaitForFWBoot();
    status = Bootloader_socOpenFirewalls();

    DebugP_assertNoLog(status == SystemP_SUCCESS);

    System_init();
    Board_init();
    Drivers_open();

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);

    if(SystemP_SUCCESS == status)
    {

        uint32_t fileSize;
        uint32_t response = BOOTLOADER_UART_STATUS_LOAD_SUCCESS;

        while(bEndOfTransfer == false)
        {
            /* Xmodem Receive */
            status = Bootloader_xmodemReceive(CONFIG_UART0, gAppImageBuf, BOOTLOADER_APPIMAGE_MAX_FILE_SIZE, &fileSize);

            if(SystemP_SUCCESS == status && memcmp(gAppImageBuf, gEndOfFilesTransferWord, BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH) == 0)
            {
                bEndOfTransfer = true;
                /* Delay 5 seconds for the user to connect to UART before the CPUs start running */
                ClockP_sleep(BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS);

                /* Run CPUs */
                status = App_runCpus();
            }
            else
            {
                if(SystemP_SUCCESS == status && fileSize == BOOTLOADER_APPIMAGE_MAX_FILE_SIZE)
                {
                    /* A file larger than 1 GB was sent, and xmodem probably dropped bytes */
                    status = SystemP_FAILURE;

                    /* Send response to the script that file size exceeded */
                    uint32_t response;
                    response = BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED;

                    Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
                }

                if(SystemP_SUCCESS == status)
                {

                    status = App_loadImages();

                    if(status != SystemP_SUCCESS)
                    {
                        response = BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL;
                    }

                    Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
                }
            }
        }
    }

    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to DM*/
    Dpl_deinit();

    Bootloader_JumpSelfCpu();

    Drivers_close();
    Board_deinit();
    System_deinit();

    return 0;
}

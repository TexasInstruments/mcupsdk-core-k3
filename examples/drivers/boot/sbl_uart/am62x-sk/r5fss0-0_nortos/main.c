/*
 *  Copyright (C) 2018-2021 Texas Instruments Incorporated
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

#define BOOTLOADER_UART_STATUS_LOAD_SUCCESS           (0x53554343) /* SUCC */
#define BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL          (0x4641494C) /* FAIL */
#define BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED (0x45584344) /* EXCD */

#define BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS (5)

#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x40000000) /* Size of section DDR specified in linker.cmd */
uint8_t gAppImageBuf[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

extern Bootloader_MemArgs gBootloader0Args;
extern Bootloader_MemArgs gBootloader1Args;
extern Bootloader_MemArgs gBootloader2Args;

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

int32_t App_loadImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
        if (!Bootloader_socIsMCUResetIsoEnabled())
        {
            status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

            /* Load CPUs */
            if(status == SystemP_SUCCESS)
            {
                bootImageInfo->cpuInfo[CSL_CORE_ID_M4FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_M4FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_M4FSS0_0]));
            }
        }
        else
        {
            status = SystemP_SUCCESS;
        }
    }

    return status;
}

int32_t App_loadSelfcoreImage(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
        status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

        if(status == SystemP_SUCCESS)
        {
            /* Set clocks for self cluster */
            bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_R5FSS0_0);

            /* Reset self cluster, both Core0 and Core 1. Init RAMs and load the app  */
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0]));
        }
    }

    return status;
}

int32_t App_runCpus(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if (!Bootloader_socIsMCUResetIsoEnabled())
    {
	    status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_M4FSS0_0]));
    }
    else
    {
        status = SystemP_SUCCESS;
    }

	return status;
}

int main()
{
    int32_t status;

    Bootloader_socWaitForFWBoot();
    //status = Bootloader_socOpenFirewalls();

    System_init();
    Drivers_open();

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);

    if(SystemP_SUCCESS == status)
    {

        uint32_t fileSize;
        uint32_t response = BOOTLOADER_UART_STATUS_LOAD_SUCCESS;

        Bootloader_BootImageInfo bootImageInfo;
		Bootloader_Params bootParams;
        Bootloader_Handle bootHandle;

        Bootloader_BootImageInfo bootImageInfoDM;
		Bootloader_Params bootParamsDM;
        Bootloader_Handle bootHandleDM;

        Bootloader_Params_init(&bootParams);
        Bootloader_Params_init(&bootParamsDM);

		Bootloader_BootImageInfo_init(&bootImageInfo);
        Bootloader_BootImageInfo_init(&bootImageInfoDM);

        bootParams.bufIoTempBuf     = gAppImageBuf;
        bootParams.bufIoTempBufSize = BOOTLOADER_APPIMAGE_MAX_FILE_SIZE;
        bootParams.bufIoDeviceIndex = CONFIG_UART0;
        bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;

        bootParamsDM.bufIoTempBuf     = gAppImageBuf;
        bootParamsDM.bufIoTempBufSize = BOOTLOADER_APPIMAGE_MAX_FILE_SIZE;
        bootParamsDM.bufIoDeviceIndex = CONFIG_UART0;
        bootParamsDM.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;

        bootHandle = Bootloader_open(CONFIG_BOOTLOADER0, &bootParams);
        bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_DM, &bootParamsDM);

        if(BOOTLOADER_MEDIA_MEM == Bootloader_getBootMedia(bootHandle))
        {
            /* Xmodem Receive */
            status = Bootloader_xmodemReceive(CONFIG_UART0, gAppImageBuf, BOOTLOADER_APPIMAGE_MAX_FILE_SIZE, &fileSize);

            if(SystemP_SUCCESS == status && fileSize == BOOTLOADER_APPIMAGE_MAX_FILE_SIZE)
            {
                /* A file larger than 384 KB was sent, and xmodem probably dropped bytes */
                status = SystemP_FAILURE;

                /* Send response to the script that file size exceeded */
                uint32_t response;
                response = BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED;

                Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
            }

            if(SystemP_SUCCESS == status)
            {
                if(bootHandle != NULL)
                {
                    status = App_loadImages(bootHandle, &bootImageInfo);
                }

                if(status != SystemP_SUCCESS)
                {
                    response = BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL;
                }

                Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
            }
        }

        if(SystemP_SUCCESS == status && BOOTLOADER_MEDIA_MEM == Bootloader_getBootMedia(bootHandleDM))
        {
            /* Xmodem Receive */
            status = Bootloader_xmodemReceive(CONFIG_UART0, gAppImageBuf, BOOTLOADER_APPIMAGE_MAX_FILE_SIZE, &fileSize);

            if(SystemP_SUCCESS == status && fileSize == BOOTLOADER_APPIMAGE_MAX_FILE_SIZE)
            {
                /* A file larger than 384 KB was sent, and xmodem probably dropped bytes */
                status = SystemP_FAILURE;

                /* Send response to the script that file size exceeded */
                uint32_t response;
                response = BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED;

                Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
            }

            if(SystemP_SUCCESS == status)
            {
                if(bootHandleDM != NULL)
                {
                    status = App_loadSelfcoreImage(bootHandleDM, &bootImageInfoDM);
                }

                if(status != SystemP_SUCCESS)
                {
                    response = BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL;
                }

                Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
            }
        }


        if(SystemP_SUCCESS == status)
        {
            /* Delay 2 seconds for the user to connect to UART before the CPUs start running*/
            ClockP_sleep(BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS);

            /* Run CPUs */

            if(SystemP_SUCCESS == status)
            {
                status = App_runCpus(bootHandle, &bootImageInfo);
            }

            Bootloader_close(bootHandle);
        }
    }

    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    Bootloader_JumpSelfCpu();

    Drivers_close();
    System_deinit();

    return 0;
}


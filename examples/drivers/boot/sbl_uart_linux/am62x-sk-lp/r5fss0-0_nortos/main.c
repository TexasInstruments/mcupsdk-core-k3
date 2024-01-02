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

/* Workaround to initialize MMC SD Pinmux (Later will be done in SPL) */
static Pinmux_PerCfg_t gPinMuxMMCSDCfg[] = {
            /* MMC1 pin config */
    /* MMC1_CLK -> MMC1_CLK (B22) */
    {
        PIN_MMC1_CLK,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_CMD -> MMC1_CMD (A21) */
    {
        PIN_MMC1_CMD,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_DAT0 -> MMC1_DAT0 (A22) */
    {
        PIN_MMC1_DAT0,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_DAT1 -> MMC1_DAT1 (B21) */
    {
        PIN_MMC1_DAT1,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_DAT2 -> MMC1_DAT2 (C21) */
    {
        PIN_MMC1_DAT2,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_DAT3 -> MMC1_DAT3 (D22) */
    {
        PIN_MMC1_DAT3,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_SDCD -> MMC1_SDCD (D17) */
    {
        PIN_MMC1_SDCD,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },

    {PINMUX_END, PINMUX_END}
};


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

int32_t App_loadLinuxImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
		status = Bootloader_parseAndLoadLinuxAppImage(bootHandle, bootImageInfo);

		if(status == SystemP_SUCCESS)
		{
			bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
			status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));
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

int32_t App_runLinuxCpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    /* Initialize GTC by enabling using Syscfg */

    /* Change the dev stat register to SD card bootmode so that SPL loads uBoot and linux kernel from SD card */
	SOC_setDevStat(SOC_BOOTMODE_MMCSD);

    /* Enable pinmux for MMCSD (Workaround as MMC SD pinmux is not initialized in A53 SPL) */
    Pinmux_config(gPinMuxMMCSDCfg, PINMUX_DOMAIN_ID_MAIN);

    /* Unlock all the control MMRs. Linux/U-boot expects all the MMRs to be unlocked */
    SOC_unlockAllMMR();

	status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));

	return status;
}

int main()
{
    int32_t status;

    Bootloader_socWaitForFWBoot();

    System_init();
    Board_init();
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

		Bootloader_BootImageInfo bootImageInfoLinux;
		Bootloader_Params bootParamsLinux;
        Bootloader_Handle bootHandleLinux;

        Bootloader_Params_init(&bootParams);
        Bootloader_Params_init(&bootParamsDM);
		Bootloader_Params_init(&bootParamsLinux);

		Bootloader_BootImageInfo_init(&bootImageInfo);
        Bootloader_BootImageInfo_init(&bootImageInfoDM);
		Bootloader_BootImageInfo_init(&bootImageInfoLinux);

        bootParams.bufIoTempBuf     = gAppImageBuf;
        bootParams.bufIoTempBufSize = BOOTLOADER_APPIMAGE_MAX_FILE_SIZE;
        bootParams.bufIoDeviceIndex = CONFIG_UART0;
        bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;

        bootParamsDM.bufIoTempBuf     = gAppImageBuf;
        bootParamsDM.bufIoTempBufSize = BOOTLOADER_APPIMAGE_MAX_FILE_SIZE;
        bootParamsDM.bufIoDeviceIndex = CONFIG_UART0;
        bootParamsDM.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;

        bootParamsLinux.bufIoTempBuf     = gAppImageBuf;
        bootParamsLinux.bufIoTempBufSize = BOOTLOADER_APPIMAGE_MAX_FILE_SIZE;
        bootParamsLinux.bufIoDeviceIndex = CONFIG_UART0;
        bootParamsLinux.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;

        bootHandle = Bootloader_open(CONFIG_BOOTLOADER0, &bootParams);
        bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_DM, &bootParamsDM);
        bootHandleLinux = Bootloader_open(CONFIG_BOOTLOADER_LINUX, &bootParamsLinux);

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

        if(SystemP_SUCCESS == status && BOOTLOADER_MEDIA_MEM == Bootloader_getBootMedia(bootHandleLinux))
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
                if(bootHandleLinux != NULL)
                {
                    status = App_loadLinuxImages(bootHandleLinux, &bootImageInfoLinux);
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
                status = App_runLinuxCpu(bootHandleLinux, &bootImageInfoLinux);
            }

            Bootloader_close(bootHandleLinux);

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

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to DM*/
    Dpl_deinit();

    Bootloader_JumpSelfCpu();

    Drivers_close();
    Board_deinit();
    System_deinit();

    return 0;
}


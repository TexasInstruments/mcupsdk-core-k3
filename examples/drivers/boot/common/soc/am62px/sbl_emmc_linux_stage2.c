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
#include <kernel/dpl/CacheP.h>
#include "FreeRTOS.h"
#include "task.h"


/* This start address and length depends upon the linker memory for second stage SBL.
 *  It is necessary to change the below start address and length if in case the linker
 *  memory region for second stage SBL is changed.
 */

#define BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_START       0x9CA00000
#define BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_LENGTH      0x1D00000

/* This buffer needs to be defined for eMMC boot in case of HS device for
 *  image authentication
 *  The size of the buffer should be large enough to accomodate the appimage
 */
uint8_t gAppimage[0x1900000] __attribute__ ((section (".app"), aligned (4096)));

/*  In this sample bootloader, we load appimages for RTOS/Baremetal and Linux at different offset
 *  i.e the appimage for Linux (for A53) and RTOS/Baremetal (for R5, MCU_R5) is flashed at different offset in eMMC
 *
 *  Here at one eMMC offset, there is a multi-core .appimage that holds RPRC for MCU_R5 and R5
 *  and another .appimage that holds the linux binaries(ATF, OPTEE, A53-SPL) at another offset.
 *
 *  When flashing make sure to flash images to below offset using the flash tool.
 *
 *  RTOS/Baremetal appimage (for HSM) flash at offset 0x800000 of eMMC
 *  Linux appimage (for A53) flash at offset 0xA00000 of eMMC
 */

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
        status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

        /* Load CPUs */
        if(status == SystemP_SUCCESS)
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_HSM_M4FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_HSM_M4FSS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0]));
        }
    }

    return status;
}

int32_t App_loadMCUImage(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
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
                bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
            }
        }
        else
        {
            status = SystemP_SUCCESS;
        }
    }

    return status;
}

int32_t App_loadLinuxImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
		status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

		if(status == SystemP_SUCCESS)
		{
			bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
			Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));
		}
	}

	return status;
}

int32_t App_runCpus(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

	status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0]));

	return status;
}

int32_t App_runMCUCpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if (!Bootloader_socIsMCUResetIsoEnabled())
    {
	    status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
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

    /* Unlock all the control MMRs. Linux/U-boot expects all the MMRs to be unlocked */
    SOC_unlockAllMMR();

	status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));

	return status;
}

void App_driversOpen()
{
    gMmcsdHandle[CONFIG_MMCSD_SBL] = NULL;

    gMmcsdHandle[CONFIG_MMCSD_SBL] = MMCSD_open(CONFIG_MMCSD_SBL, &gMmcsdParams[CONFIG_MMCSD_SBL]);
    if(NULL == gMmcsdHandle[CONFIG_MMCSD_SBL])
    {
        DebugP_logError("MMCSD open failed for instance %d !!!\r\n", CONFIG_MMCSD_SBL);
    }

    gUartHandle[CONFIG_UART_SBL] = NULL;

    gUartHandle[CONFIG_UART_SBL] = UART_open(CONFIG_UART_SBL, &gUartParams[CONFIG_UART_SBL]);
    if(NULL == gUartHandle[CONFIG_UART_SBL])
    {
        DebugP_logError("UART open failed for instance %d !!!\r\n", CONFIG_UART_SBL);
    }
}

void App_driversClose()
{
    MMCSD_close(gMmcsdHandle[CONFIG_MMCSD_SBL]);
    gMmcsdHandle[CONFIG_MMCSD_SBL] = NULL;

    UART_close(gUartHandle[CONFIG_UART_SBL]);
    gUartHandle[CONFIG_UART_SBL] = NULL;
}

void App_bootMultipleCoreEMMC()
{
    int32_t status = SystemP_SUCCESS;

    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");


    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle;

    Bootloader_BootImageInfo bootImageInfoLinux;
    Bootloader_Params bootParamsLinux;
    Bootloader_Handle bootHandleLinux;

    Bootloader_BootImageInfo bootImageInfoMCU;
    Bootloader_Params bootParamsMCU;
    Bootloader_Handle bootHandleMCU;

    Bootloader_Params_init(&bootParams);
    Bootloader_Params_init(&bootParamsLinux);
    Bootloader_Params_init(&bootParamsMCU);

    Bootloader_BootImageInfo_init(&bootImageInfo);
    Bootloader_BootImageInfo_init(&bootImageInfoLinux);
    Bootloader_BootImageInfo_init(&bootImageInfoMCU);

    bootHandle = Bootloader_open(CONFIG_BOOTLOADER_EMMC_HSM, &bootParams);
    bootHandleLinux = Bootloader_open(CONFIG_BOOTLOADER_EMMC_LINUX, &bootParamsLinux);
    bootHandleMCU = Bootloader_open(CONFIG_BOOTLOADER_EMMC_MCU, &bootParamsMCU);

    Bootloader_ReservedMemInit(BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_START, \
                                BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_LENGTH);

    if(SystemP_SUCCESS == status)
    {
        if(bootHandle != NULL)
        {
        ((Bootloader_Config *)bootHandle)->scratchMemPtr = gAppimage;
            status = App_loadImages(bootHandle, &bootImageInfo);
            Bootloader_profileAddProfilePoint("App_loadImages");
        }
    }

    if(SystemP_SUCCESS == status)
    {
        status = App_runCpus(bootHandle, &bootImageInfo);
    }

    Bootloader_close(bootHandle);

    if(SystemP_SUCCESS == status)
    {
        if(bootHandleMCU != NULL)
        {
            ((Bootloader_Config *)bootHandleMCU)->scratchMemPtr = gAppimage;
            status = App_loadMCUImage(bootHandleMCU, &bootImageInfoMCU);
            Bootloader_profileAddProfilePoint("App_loadMCUImages");
        }
    }

    if(SystemP_SUCCESS == status)
    {
        status = App_runMCUCpu(bootHandleMCU, &bootImageInfoMCU);
    }

    Bootloader_close(bootHandleMCU);

    if(SystemP_SUCCESS == status)
    {
        if(bootHandleLinux != NULL)
        {
            ((Bootloader_Config *)bootHandleLinux)->scratchMemPtr = gAppimage;
            status = App_loadLinuxImages(bootHandleLinux, &bootImageInfoLinux);
            Bootloader_profileAddProfilePoint("App_loadLinuxImages");
        }
    }

    Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandle) + \
                                        Bootloader_getMulticoreImageSize(bootHandleLinux) + \
                                        Bootloader_getMulticoreImageSize(bootHandleMCU));
    Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_EMMC, MMCSD_getInputClk(gMmcsdHandle[CONFIG_MMCSD_SBL]));

    if(SystemP_SUCCESS == status)
    {
        /* Use CONFIG_UART_SBL (UART0) for SBL logs */
        DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

        /* Print SBL log as Linux prints log to the same UART port */
        Bootloader_profilePrintProfileLog();
        DebugP_log("Image loading done, switching to application ...\r\n");
        DebugP_log("Starting linux and RTOS/Baremetal applications\r\n");
        UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);

        /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
        DebugP_uartSetDrvIndex(CONFIG_UART_APP);
    }

    /* Deinitialise the flash and driver peripherial used by bootloader before starting other cores,
     * so that other systems can access and reinitialise it.
     */

    App_driversClose();
    SOC_moduleClockEnable(TISCI_DEV_MMCSD0, 0);

    if(SystemP_SUCCESS == status)
    {
        status = App_runLinuxCpu(bootHandleLinux, &bootImageInfoLinux);
    }

    Bootloader_close(bootHandleLinux);


    if(status != SystemP_SUCCESS )
    {
        /* Use CONFIG_UART_SBL (UART0) for SBL logs */
        DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

        /* Open UART to print failure log */
        gUartHandle[CONFIG_UART_SBL] = UART_open(CONFIG_UART_SBL, &gUartParams[CONFIG_UART_SBL]);
        if(NULL == gUartHandle[CONFIG_UART_SBL])
        {
            DebugP_logError("UART open failed for instance %d !!!\r\n", CONFIG_UART_SBL);
        }

        DebugP_log("Stage 2 booting failed!!\r\n");

        UART_close(gUartHandle[CONFIG_UART_SBL]);
        gUartHandle[CONFIG_UART_SBL] = NULL;

        /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
        DebugP_uartSetDrvIndex(CONFIG_UART_APP);
    }

}

void sbl_stage2_main(void * args)
{
    int32_t status = SystemP_FAILURE;

    status = Bootloader_socIsSBLBoot();

    if(status  == SystemP_SUCCESS)
    {
        App_bootMultipleCoreEMMC();
    }

    vTaskDelete(NULL);
}

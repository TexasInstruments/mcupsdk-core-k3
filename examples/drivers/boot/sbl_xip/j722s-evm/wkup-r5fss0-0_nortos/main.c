/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>
#include <drivers/pinmux.h>
#include <drivers/gtc.h>

void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle);

#define BOOTLOADER_APP_IMAGE_LOADED                         0x1U

uint8_t socCpuCores[CSL_CORE_ID_MAX] = {0};

Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

/* This buffer needs to be defined for OSPI nand boot in case of HS device for
   image authentication
   The size of the buffer should be large enough to accomodate the appimage */
uint8_t gAppImage[0x4000000U] __attribute__ ((section (".bss.app"), aligned (128)));

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
        if (!Bootloader_socIsMCUResetIsoEnabled())
        {
            if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MCU_R5FSS0_0)))
            {
                bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
                socCpuCores[CSL_CORE_ID_MCU_R5FSS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_MCU_R5FSS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0];
            }
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_WKUP_R5FSS0_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_WKUP_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_WKUP_R5FSS0_0);
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MAIN_R5FSS0_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MAIN_R5FSS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_MAIN_R5FSS0_0);
            socCpuCores[CSL_CORE_ID_MAIN_R5FSS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_C75SS0_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS0_0);
            socCpuCores[CSL_CORE_ID_C75SS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_C75SS1_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS1_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS1_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS1_0);
            socCpuCores[CSL_CORE_ID_C75SS1_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS1_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS1_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS0_0)))
		{
			bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
			status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));
            socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0];
		}
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS1_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS1_0);
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS1_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS1_0]));
            socCpuCores[CSL_CORE_ID_A53SS1_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS1_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS1_0];
        }
    }

    return status;
}

int32_t App_runCpus(Bootloader_Handle bootHandle)
{
    int32_t status = SystemP_SUCCESS;
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

    Bootloader_profileReset();

    Bootloader_socWaitForFWBoot();

    System_init();
    Bootloader_profileAddProfilePoint("System_init");

    status = Bootloader_socOpenFirewalls();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    Board_init();
    Bootloader_profileAddProfilePoint("Board_init");

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");
    flashFixUpOspiBoot(gOspiHandle[CONFIG_OSPI_SBL], gFlashHandle[CONFIG_FLASH_SBL]);

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("Board_driversOpen");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_BootImageInfo bootImageInfoDM;
        Bootloader_Params bootParamsDM;
        Bootloader_Handle bootHandleDM;

        Bootloader_Params_init(&bootParamsDM);  

        Bootloader_BootImageInfo_init(&bootImageInfoDM);

        bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_FLASH_SBL, &bootParamsDM);

         if(bootHandleDM != NULL)
        {
            ((Bootloader_Config *)bootHandleDM)->scratchMemPtr = gAppImage;
            status = App_loadImages(bootHandleDM, &bootImageInfoDM);
            Bootloader_profileAddProfilePoint("App_loadImages");
        }

        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleDM));
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI_SBL]));

		if(SystemP_SUCCESS == status)
		{
			/* Print SBL log as Linux prints log to the same UART port */
			Bootloader_profilePrintProfileLog();
			DebugP_log("Image loading done, switching to application ...\r\n");
			DebugP_log("Starting RTOS/Baremetal applications\r\n");
			UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);

            status = App_runCpus(bootHandleDM);
		}
    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Some tests have failed!!\r\n");
        DebugP_assert(0);
    }
    else
    {
        Board_driversClose();
        Drivers_close();

        /* Call DPL deinit to close the tick timer and disable interrupts before jumping to Stage2*/
        Dpl_deinit();
        System_deinit();

        Bootloader_JumpSelfCpu();
    }

    return 0;
}

void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle)
{
    
        OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(8,8,8,1));
        OSPI_enableDDR(oHandle);
        OSPI_setDualOpCodeMode(oHandle);
        Flash_reset(fHandle);
        OSPI_enableSDR(oHandle);
        OSPI_clearDualOpCodeMode(oHandle);
        OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(1,1,1,0));

}

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
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>
#include <drivers/pinmux.h>
#include <drivers/gtc.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/soc.h>

/*  In this sample bootloader, we load appimages for RTOS/Baremetal and Linux at different offset
    i.e the appimage for Linux (for A53) and RTOS/Baremetal (for R5, MCU R5) is flashed at different offset in flash

    Here at one flash offset, there is a multi-core .appimage that holds RPRC for MCU R5 and R5
    and another .appimage that holds the linux binaries(ATF, OPTEE, A53-SPL) at another offset.

    When flashing make sure to flash images to below offset using the flash tool.

    RTOS/Baremetal appimage (MCU R5 cores) flash at offset 0x100000 of flash
    Linux appimage (for A53) flash at offset 0xC00000 of flash
*/

void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle);

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
/*
    Code for enabling the power and clock of MCAN
*/
#define SOC_MODULES_END (0xFFFFFFFFu)

typedef struct
{

    uint32_t moduleId;
    uint32_t clkId;
    uint32_t clkRate;

} MCAN_SOC_ModuleClockFrequency;

uint32_t mcan_gSocModules[] = {
     TISCI_DEV_MCU_MCAN1,
    SOC_MODULES_END,
};

MCAN_SOC_ModuleClockFrequency mcan_gSocModulesClockFrequency[] = {
    { TISCI_DEV_MCU_MCAN1, TISCI_DEV_MCU_MCAN1_MCANSS_CCLK_CLK, 80000000 },
    {SOC_MODULES_END, SOC_MODULES_END, SOC_MODULES_END},
};

void MCAN_Module_clockEnable(void)
{
    int32_t status;
    uint32_t i = 0;

    while (mcan_gSocModules[i] != SOC_MODULES_END)
    {
        status = SOC_moduleClockEnable(mcan_gSocModules[i], 1);
        DebugP_assertNoLog(status == SystemP_SUCCESS);
        i++;
    }
}

void MCAN_Module_clockDisable(void)
{
    int32_t status;
    uint32_t i = 0;

    while (mcan_gSocModules[i] != SOC_MODULES_END)
    {
        status = SOC_moduleClockEnable(mcan_gSocModules[i], 0);
        DebugP_assertNoLog(status == SystemP_SUCCESS);
        i++;
    }
}

void MCAN_Module_clockSetFrequency(void)
{
    int32_t status;
    uint32_t i = 0;

    while (mcan_gSocModulesClockFrequency[i].moduleId != SOC_MODULES_END)
    {
        status = SOC_moduleSetClockFrequency(
            mcan_gSocModulesClockFrequency[i].moduleId,
            mcan_gSocModulesClockFrequency[i].clkId,
            mcan_gSocModulesClockFrequency[i].clkRate);

        DebugP_assertNoLog(status == SystemP_SUCCESS);
        i++;
    }
}

void MCAN_PowerClock_init(void)
{
    MCAN_Module_clockEnable();
    MCAN_Module_clockSetFrequency();
}

void MCAN_PowerClock_deinit()
{
    MCAN_Module_clockDisable();
}
/*Code for MCAN power clock init ends here*/

int32_t App_loadImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
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
            bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_R5FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_R5FSS0_0);
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
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
			status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));
		}
	}

	return status;
}

int32_t App_runCpus(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

	status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));

	return status;
}

int32_t App_runLinuxCpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

	status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));

	return status;
}

int main()
{
    int32_t status;

    Bootloader_profileReset();

    Bootloader_socWaitForFWBoot();


    System_init();
    Bootloader_profileAddProfilePoint("System_init");
    MCAN_PowerClock_init();
    Bootloader_profileAddProfilePoint("MCAN_PowerClock_init");

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");

    flashFixUpOspiBoot(gOspiHandle[CONFIG_OSPI0], gFlashHandle[CONFIG_FLASH0]);

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("Board_driversOpen");


    if(SystemP_SUCCESS == status)
    {
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

        bootHandle = Bootloader_open(CONFIG_BOOTLOADER_FLASH_MCU, &bootParams);
        bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_FLASH_SBL, &bootParamsDM);

        if(bootHandle != NULL)
        {
			status = App_loadImages(bootHandle, &bootImageInfo);
            Bootloader_profileAddProfilePoint("App_loadImages");
        }

        if(SystemP_SUCCESS == status)
		{
			DebugP_log("Image loading done, switching to application ...\r\n");
			DebugP_log("Starting MCU-r5f and 2nd stage bootloader\r\n");
			UART_flushTxFifo(gUartHandle[CONFIG_UART0]);
		}

        if(SystemP_SUCCESS == status)
		{
			status = App_runCpus(bootHandle, &bootImageInfo);
		}

        if(SystemP_SUCCESS == status)
		{
            if(bootHandleDM != NULL)
            {
                status = App_loadSelfcoreImage(bootHandleDM, &bootImageInfoDM);
                Bootloader_profileAddProfilePoint("App_loadSelfcoreImage");
            }
        }
        Bootloader_profilePrintProfileLog();

        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleDM) + Bootloader_getMulticoreImageSize(bootHandle));
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI0]));



        Bootloader_close(bootHandle);
    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    Bootloader_JumpSelfCpu();

    Drivers_close();
    System_deinit();

    MCAN_PowerClock_deinit();

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
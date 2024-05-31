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
#include <drivers/ospi.h>

/*
 * In this sample bootloader, we load appimages for RTOS/Baremetal and Linux at different offset
 * i.e the appimage for Linux (for A53) and RTOS/Baremetal (for R5, MCU R5) is flashed at different
 * offset in OSPI NOR flash
 *
 * Here at one ospi nor flash offset, there is a multi-core .appimage that holds RPRC for MCU R5 and R5
 * and another .appimage that holds the linux binaries(ATF, OPTEE, A53-SPL) at another offset.
 *
 * When flashing make sure to flash images to below offset using the flash tool
 *
 * RTOS/Baremetal appimage (MCU R5 cores) flash at offset 0x800000 of flash
 * Linux appimage (for A53) flash at offset 0x1200000 of flash
 */

void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle);

/*
 * This buffer needs to be defined for OSPI nand boot in case of HS device for
 * image authentication.
 * The size of the buffer should be large enough to accomodate the appimage
 */
uint8_t gAppimage[0x800000] __attribute__ ((section (".bss.app"), aligned (128)));

/*
 * Call this API to stop the booting process and spin, do that you can connect
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1;
    while(loop)
        ;
}
/* Enable MCAN power and clock */
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

void App_loadImages(Bootloader_LoadImageParams *bootLoadParams)
{
	int32_t status = SystemP_FAILURE;
    Bootloader_Config *bootConfig;

    if(bootLoadParams->bootHandle != NULL)
    {
        bootConfig = (Bootloader_Config *)bootLoadParams->bootHandle;
        bootConfig->coresPresentMap = 0;
        status = Bootloader_parseMultiCoreAppImage(bootLoadParams->bootHandle, &bootLoadParams->bootImageInfo);
            /* Load CPUs */
        if((status == SystemP_SUCCESS) && Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_MCU_R5FSS0_0))
        {
            if (!Bootloader_socIsMCUResetIsoEnabled())
            {
                (&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                if(status == SystemP_SUCCESS)
                {
                    Bootloader_profileAddProfilePoint("MCU R5 Image Load");
                    bootLoadParams->coreId = CSL_CORE_ID_MCU_R5FSS0_0;
                    bootLoadParams->loadStatus = BOOTLOADER_IMAGE_LOADED;
                }
                else
                {
                    Bootloader_powerOffCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                }
            }
            return;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS0_0)))
        {
            (&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_R5FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS0_0]));
            if(status == SystemP_SUCCESS)
            {
                Bootloader_profileAddProfilePoint("DM R5 Image Load");
                bootLoadParams->coreId = CSL_CORE_ID_R5FSS0_0;
                bootLoadParams->loadStatus = BOOTLOADER_IMAGE_LOADED;
            }
            return;
        }

    }
}

void App_runCpus(Bootloader_LoadImageParams *bootLoadParams)
{
    int32_t status = SystemP_FAILURE;
    int8_t coreId = bootLoadParams->coreId;

    if(coreId != CSL_CORE_ID_R5FSS0_0)
    {
        if(bootLoadParams->loadStatus == BOOTLOADER_IMAGE_LOADED)
        {
            status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[coreId]));\
            if(status == SystemP_FAILURE)
            {
                Bootloader_powerOffCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[coreId]));
            }
        }
        Bootloader_close(bootLoadParams->bootHandle);
    }
}

int main()
{
    int32_t status;

    Bootloader_profileReset();

    Bootloader_socWaitForFWBoot();
    status = Bootloader_socOpenFirewalls();

    DebugP_assertNoLog(status == SystemP_SUCCESS);

    System_init();
    Bootloader_profileAddProfilePoint("System_init");

    Board_init();
    Bootloader_profileAddProfilePoint("Board_init");

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
        Bootloader_LoadImageParams bootArray[CONFIG_BOOTLOADER_NUM_INSTANCES] = {0};
        uint32_t imageSize = 0;

        for(uint8_t inst = 0; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
        {
            Bootloader_Params_init(&bootArray[inst].bootParams);
            Bootloader_BootImageInfo_init(&bootArray[inst].bootImageInfo);
            bootArray[inst].bootHandle = Bootloader_open(inst, &bootArray[inst].bootParams);
            bootArray[inst].loadStatus = BOOTLOADER_IMAGE_NOT_LOADED;
            if(bootArray[inst].bootHandle != NULL)
            {
               ((Bootloader_Config *)bootArray[inst].bootHandle)->scratchMemPtr = gAppimage;
		    	App_loadImages(&bootArray[inst]);
            }
            imageSize += Bootloader_getMulticoreImageSize(bootArray[inst].bootHandle);
        }

        Bootloader_profileUpdateAppimageSize(imageSize);
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI0]));

        Bootloader_profilePrintProfileLog();
        DebugP_log("Image loading done, switching to application ...\r\n");
		DebugP_log("Starting MCU-r5f and 2nd stage bootloader\r\n");
		UART_flushTxFifo(gUartHandle[CONFIG_UART0]);

        if(bootArray[CONFIG_BOOTLOADER_FLASH_DM].loadStatus == BOOTLOADER_IMAGE_LOADED)
        {
            for(uint8_t inst = 0; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
            {
		        App_runCpus(&bootArray[inst]);
            }
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("DM image not loaded\r\n");
    }

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to Stage2*/
    Dpl_deinit();

    Bootloader_JumpSelfCpu();

    Drivers_close();
    Board_deinit();
    System_deinit();

    MCAN_PowerClock_deinit();

    return 0;
}

void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle)
{
    /*
     *  In Fast XSPI mode, reintialization is not required unless
     *  user configures it or PHY configuration failed
     */
    if(SystemP_SUCCESS != OSPI_skipTuning(oHandle))
    {
        OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(8,8,8,1));
        OSPI_enableDDR(oHandle);
        OSPI_setDualOpCodeMode(oHandle);
        Flash_reset(fHandle);
        OSPI_enableSDR(oHandle);
        OSPI_clearDualOpCodeMode(oHandle);
        OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(1,1,1,0));
    }

}
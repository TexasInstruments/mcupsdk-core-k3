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
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>
#include <drivers/pinmux.h>
#include <drivers/gtc.h>
#include <kernel/dpl/CacheP.h>
#include "FreeRTOS.h"
#include "task.h"


/* This start address and length depends upon the linker memory for second stage SBL.
 * It is necessary to change the below start address and length if in case the linker
 * memory region for second stage SBL is changed.
 */

#define BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_START       0x9CA00000
#define BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_LENGTH      0x1D00000

/* This buffer needs to be defined for OSPI NOR boot in case of HS device for
 * image authentication.
 * The size of the buffer should be large enough to accomodate the appimage
 */
uint8_t gAppimage[0x1900000] __attribute__ ((section (".app"), aligned (128)));
uint32_t gImageSize = 0U;

/*  In this sample bootloader, we load appimages for RTOS/Baremetal and Linux at different offset
 *  i.e the appimage for Linux (for A53) and RTOS/Baremetal (for R5, MCU R5) is flashed at different offset in eMMC
 *
 *  Here at one flash offset, there is a multi-core .appimage that holds RPRC for MCU R5 and R5
 *  and another .appimage that holds the linux binaries(ATF, OPTEE, A53-SPL) at another offset.
 *
 *  When flashing make sure to flash images to below offset using the flash tool.
 *
 *  RTOS/Baremetal appimage (for HSM) flash at offset 0x800000 of flash
 *  Linux appimage (for A53) flash at offset 0xC00000 of flash
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

int32_t App_boardDriversOpen()
{
    int32_t status = SystemP_SUCCESS;

    gFlashHandle[CONFIG_FLASH_SBL] = NULL;

    gFlashConfig[CONFIG_FLASH_SBL].attrs->driverInstance = CONFIG_OSPI_SBL;

    gFlashHandle[CONFIG_FLASH_SBL] = Flash_open(CONFIG_FLASH_SBL, &gFlashParams[CONFIG_FLASH_SBL]);
    if(NULL == gFlashHandle[CONFIG_FLASH_SBL])
    {
        DebugP_logError("FLASH open failed for instance %d !!!\r\n", CONFIG_FLASH_SBL);
        status = SystemP_FAILURE;
    }

    return status;
}

void App_driversOpen()
{
    gOspiHandle[CONFIG_OSPI_SBL] = NULL;

    gOspiHandle[CONFIG_OSPI_SBL] = OSPI_open(CONFIG_OSPI_SBL, &gOspiParams[CONFIG_OSPI_SBL]);
    if(NULL == gOspiHandle[CONFIG_OSPI_SBL])
    {
        DebugP_logError("OSPI open failed for instance %d !!!\r\n", CONFIG_OSPI_SBL);
    }

    gUartHandle[CONFIG_UART_SBL] = NULL;

    gUartHandle[CONFIG_UART_SBL] = UART_open(CONFIG_UART_SBL, &gUartParams[CONFIG_UART_SBL]);
    if(NULL == gUartHandle[CONFIG_UART_SBL])
    {
        DebugP_logError("UART open failed for instance %d !!!\r\n", CONFIG_UART_SBL);
    }
}

void App_boardDriversClose()
{
    Flash_close(gFlashHandle[CONFIG_FLASH_SBL]);
    gFlashHandle[CONFIG_FLASH_SBL] = NULL;
}

void App_driversClose()
{
    OSPI_close(gOspiHandle[CONFIG_OSPI_SBL]);
    gOspiHandle[CONFIG_OSPI_SBL] = NULL;

    UART_close(gUartHandle[CONFIG_UART_SBL]);
    gUartHandle[CONFIG_UART_SBL] = NULL;
}

void App_printBootloaderLogs()
{
    Bootloader_profileUpdateAppimageSize(gImageSize);
    Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI_SBL]));

    /* Create a critical section to prevent other cores from printing the log in UART0 */
    vPortEnterCritical();

    /* Use CONFIG_UART_SBL (UART0) for SBL logs */
    DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

    /* Print SBL log as Linux prints log to the same UART port */
	Bootloader_profilePrintProfileLog();
	DebugP_log("Image loading done, switching to application ...\r\n");
	DebugP_log("Starting linux and RTOS/Baremetal applications\r\n");

    /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
    DebugP_uartSetDrvIndex(CONFIG_UART_APP);

    vPortExitCritical();

	UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);

    /* Deinitialise the flash and driver peripherial used by bootloader before starting other cores,
     * so that other systems can access and reinitialise it.
     */

    App_boardDriversClose();
    App_driversClose();
}

void App_loadAndRunImages(Bootloader_LoadImageParams *bootLoadParams)
{
	int32_t status = SystemP_FAILURE;
    Bootloader_Config *bootConfig;

    if(bootLoadParams->bootHandle != NULL)
    {
        bootConfig = (Bootloader_Config *)bootLoadParams->bootHandle;
        bootConfig->coresPresentMap = 0;
        status = Bootloader_parseMultiCoreAppImage(bootLoadParams->bootHandle, &bootLoadParams->bootImageInfo);

        /* Load CPUs */
        if((status == SystemP_SUCCESS) && TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_HSM_M4FSS0_0))
        {
            (&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_HSM_M4FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_HSM_M4FSS0_0);
            status = Bootloader_loadCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0]));
            if(status == SystemP_SUCCESS)
            {
                Bootloader_profileAddProfilePoint("HSM Image Load");

                gImageSize += Bootloader_getMulticoreImageSize(bootLoadParams->bootHandle);

                status += Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0]));
            }

            if(status == SystemP_FAILURE)
            {
                Bootloader_powerOffCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0]));
            }

            Bootloader_close(bootLoadParams->bootHandle);

            return;
        }

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

                    status += Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                }

                if(status == SystemP_FAILURE)
                {
                    Bootloader_powerOffCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                }

                Bootloader_close(bootLoadParams->bootHandle);
            }

            return;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_A53SS0_0)))
		{
			(&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
			Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
            status = Bootloader_loadCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_A53SS0_0]));

            if(status == SystemP_SUCCESS)
            {
                Bootloader_profileAddProfilePoint("A53 Image Load");
                gImageSize += Bootloader_getMulticoreImageSize(bootLoadParams->bootHandle);

                App_printBootloaderLogs();

                /* Unlock all the control MMRs. Linux/U-boot expects all the MMRs to be unlocked */
                SOC_unlockAllMMR();

                status += Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_A53SS0_0]));
            }

            if(status == SystemP_FAILURE)
            {
                Bootloader_powerOffCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_A53SS0_0]));
            }

            Bootloader_close(bootLoadParams->bootHandle);

            return;
        }
    }
}

/* Core boot order - First HSM, Second MCU R5 and Third A53 */
void App_bootMultipleCoreFlash()
{
    int32_t status;

    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    status = App_boardDriversOpen();
    DebugP_assertNoLog(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("SBL Board_driversOpen");

    Bootloader_ReservedMemInit(BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_START, \
                                BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_LENGTH);

    if(SystemP_SUCCESS == status)
    {
        Bootloader_LoadImageParams bootArray[CONFIG_BOOTLOADER_NUM_INSTANCES];

        for(uint8_t inst = 0; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
        {
            Bootloader_Params_init(&bootArray[inst].bootParams);
            Bootloader_BootImageInfo_init(&bootArray[inst].bootImageInfo);
            bootArray[inst].bootHandle = Bootloader_open(inst, &bootArray[inst].bootParams);
            if(bootArray[inst].bootHandle != NULL)
            {
               ((Bootloader_Config *)bootArray[inst].bootHandle)->scratchMemPtr = gAppimage;
		    	App_loadAndRunImages(&bootArray[inst]);
            }
        }
    }
}

void sbl_stage2_main(void * args)
{
    int32_t status = SystemP_FAILURE;

    status = Bootloader_socIsSBLBoot();

    if(status  == SystemP_SUCCESS)
    {
        App_bootMultipleCoreFlash();
    }

    vTaskDelete(NULL);
}
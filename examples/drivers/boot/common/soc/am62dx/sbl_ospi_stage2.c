/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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
#define BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_LENGTH      0x1C08000

/* This buffer needs to be defined for OSPI NOR boot in case of HS device for
 * image authentication.
 * The size of the buffer should be large enough to accomodate the appimage
 */
extern uint8_t gAppimage[0x1900000] __attribute__ ((section (".app"), aligned (128)));

/*  In this sample bootloader, we load appimages for RTOS/Baremetal at different offset
    i.e the appimage for RTOS/Baremetal (for R5, MCU R5, A53) is flashed at different offset in flash

    Here at one flash offset, there is a multi-core .appimage that holds RPRC for MCU R5 and R5
    and another .appimage that holds the A53 binaries at another offset.

    When flashing make sure to flash images to below offset using the flash tool.

    RTOS/Baremetal appimage (for HSM) flash at offset 0x240000 of flash
    RTOS/Baremetal appimage (for A53) flash at offset 0x1200000 of flash
*/

void loop_forever();
int32_t App_loadImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo);
int32_t App_loadMCUImage(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo);
int32_t App_loadDSPImage(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo);
int32_t App_loadSelfcoreImage(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo);
int32_t App_loadA53Images(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo);
int32_t App_runCpus(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo);
int32_t App_runDSPCpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo);
int32_t App_runA53Cpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo);
int32_t App_runMCUCpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo);



int32_t App_boardDriversOpen_Flash()
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

void App_driversOpen_Flash()
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

void App_boardDriversClose_Flash()
{
    Flash_close(gFlashHandle[CONFIG_FLASH_SBL]);
    gFlashHandle[CONFIG_FLASH_SBL] = NULL;
}

void App_driversClose_Flash()
{
    OSPI_close(gOspiHandle[CONFIG_OSPI_SBL]);
    gOspiHandle[CONFIG_OSPI_SBL] = NULL;

    UART_close(gUartHandle[CONFIG_UART_SBL]);
    gUartHandle[CONFIG_UART_SBL] = NULL;
}

void App_bootMultipleCoreFlash()
{
    int32_t status = SystemP_SUCCESS;

    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    App_driversOpen_Flash();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    status = App_boardDriversOpen_Flash();
    DebugP_assertNoLog(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("SBL Board_driversOpen");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_BootImageInfo bootImageInfo;
		Bootloader_Params bootParams;
        Bootloader_Handle bootHandle = NULL;


        Bootloader_BootImageInfo bootImageInfoMCU;
        Bootloader_Params bootParamsMCU;
        Bootloader_Handle bootHandleMCU = NULL;

        Bootloader_BootImageInfo bootImageInfoA53;
        Bootloader_Params bootParamsA53;
        Bootloader_Handle bootHandleA53 = NULL;

        Bootloader_BootImageInfo bootImageInfoDSP;
        Bootloader_Params bootParamsDSP;
        Bootloader_Handle bootHandleDSP = NULL;

        Bootloader_Params_init(&bootParams);
        Bootloader_Params_init(&bootParamsMCU);
        Bootloader_Params_init(&bootParamsA53);
        Bootloader_Params_init(&bootParamsDSP);

        Bootloader_BootImageInfo_init(&bootImageInfo);
        Bootloader_BootImageInfo_init(&bootImageInfoMCU);
        Bootloader_BootImageInfo_init(&bootImageInfoA53);
        Bootloader_BootImageInfo_init(&bootImageInfoDSP);


#ifdef CONFIG_BOOTLOADER_FLASH_HSM
        bootHandle  = Bootloader_open(CONFIG_BOOTLOADER_FLASH_HSM, &bootParams);
#endif

#ifdef CONFIG_BOOTLOADER_FLASH_MCU
        bootHandleMCU  = Bootloader_open(CONFIG_BOOTLOADER_FLASH_MCU, &bootParamsMCU);
#endif

#ifdef CONFIG_BOOTLOADER_FLASH_A53
        bootHandleA53 = Bootloader_open(CONFIG_BOOTLOADER_FLASH_A53, &bootParamsA53);
#endif

#ifdef CONFIG_BOOTLOADER_FLASH_DSP
        bootHandleDSP = Bootloader_open(CONFIG_BOOTLOADER_FLASH_DSP, &bootParamsDSP);
#endif

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

        if((SystemP_SUCCESS == status) && (bootHandle != NULL))
        {
            status = App_runCpus(bootHandle, &bootImageInfo);
            Bootloader_close(bootHandle);
        }

        if(SystemP_SUCCESS == status)
        {
            if(bootHandleMCU != NULL)
            {
                ((Bootloader_Config *)bootHandleMCU)->scratchMemPtr = gAppimage;
				status = App_loadMCUImage(bootHandleMCU, &bootImageInfoMCU);
                Bootloader_profileAddProfilePoint("App_loadMCUImages");
            }
        }

        if((SystemP_SUCCESS == status) && (bootHandleMCU != NULL))
        {
            status = App_runMCUCpu(bootHandleMCU, &bootImageInfoMCU);
            Bootloader_close(bootHandleMCU);
        }

        if(SystemP_SUCCESS == status)
        {
            if(bootHandleA53 != NULL)
            {
                ((Bootloader_Config *)bootHandleA53)->scratchMemPtr = gAppimage;
                status = App_loadA53Images(bootHandleA53, &bootImageInfoA53);
                Bootloader_profileAddProfilePoint("App_loadA53Images");
            }
        }

        if((SystemP_SUCCESS == status) && (bootHandleA53 != NULL))
        {
            status = App_runA53Cpu(bootHandleA53, &bootImageInfoA53);
            Bootloader_close(bootHandleA53);
        }

        if(SystemP_SUCCESS == status)
        {
            if(bootHandleDSP != NULL)
            {
                ((Bootloader_Config *)bootHandleDSP)->scratchMemPtr = gAppimage;
                status = App_loadDSPImage(bootHandleDSP, &bootImageInfoDSP);
                Bootloader_profileAddProfilePoint("App_loadDSPImages");
            }
        }

        if((SystemP_SUCCESS == status) && (bootHandleDSP != NULL))
        {
            status = App_runDSPCpu(bootHandleDSP, &bootImageInfoDSP);
            Bootloader_close(bootHandleDSP);
        }

        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandle) + \
                                            Bootloader_getMulticoreImageSize(bootHandleMCU) + \
                                            Bootloader_getMulticoreImageSize(bootHandleA53) + \
                                            Bootloader_getMulticoreImageSize(bootHandleDSP));
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI_SBL]));

        if(SystemP_SUCCESS == status)
        {
            /* Use CONFIG_UART_SBL (UART0) for SBL logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

#ifndef DEBUG_LOG_DISABLE
			/* Print SBL log as Linux prints log to the same UART port */
            Bootloader_profilePrintProfileLog();
            DebugP_log("Image loading done, switching to application ...\r\n");
            DebugP_log("Starting RTOS/Baremetal applications\r\n");
#endif

            UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);

            /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_APP);
        }

        /* Deinitialise the flash peripherial before starting other cores,
            so that other systems can access and reinitialise it.*/
        App_boardDriversClose_Flash();
        App_driversClose_Flash();
    }

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


void sbl_ospi_stage2_main(void * args)
{
    App_bootMultipleCoreFlash();

    vTaskDelete(NULL);
}
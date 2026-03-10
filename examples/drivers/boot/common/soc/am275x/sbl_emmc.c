/*
 *  Copyright (C) 2024-2026 Texas Instruments Incorporated
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

/*
 * Auto generated file - DO NOT MODIFY
 */

#include <stdlib.h>
#include <string.h>
#include <drivers/device_manager/sciclient.h>
#include "FreeRTOS.h"
#include "task.h"
#include <drivers/bootloader.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* This start address and length depends upon the linker memory for second stage SBL.
 *  It is necessary to change the below start address and length if in case the linker
 *  memory region for second stage SBL is changed.
 */

#define BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_START       0x9CA00000
#define BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_LENGTH      0x1D00000

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* This buffer needs to be defined for eMMC boot in case of HS device for
 *  image authentication
 */
uint8_t gScratchBuffer[0x1000];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t App_loadImages(Bootloader_LoadImageParams *bootLoadParams);
int32_t App_runCpus(Bootloader_LoadImageParams *bootLoadParams);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* call this API to stop the booting process and spin, do that you can connect
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1U;
    while(loop)
        ;
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

void App_bootMultipleCoreEmmc()
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("\r\n");
    DebugP_log("Starting Emmc Bootloader ... \r\n");

    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        /*
         * Wait for completion of Positive PBIST tests
         * that are started in System_init()
         */
        status = SDL_PBIST_completeAllTests();
        DebugP_assert(status == SDL_PASS);
        Bootloader_profileAddProfilePoint("PBIST Positive Tests");

        /* Turn On PSC devices before initializing Negative tests */
        status = SDL_PBIST_handlePSCdevices(true);
        DebugP_assert(status == SDL_PASS);

        /* Start Negative PBIST tests of all selected instances */
        status = SDL_PBIST_startAllTests(false);
        DebugP_assert(status == SDL_PASS);

        /* Wait for completion of all Negative PBIST tests */
        status = SDL_PBIST_completeAllTests();
        DebugP_assert(status == SDL_PASS);
        Bootloader_profileAddProfilePoint("PBIST Negative Tests");

        /* Turn Off PSC devices after completion of Negative tests */
        status = SDL_PBIST_handlePSCdevices(false);
        DebugP_assert(status == SDL_PASS);
        
        Bootloader_openDma();

        Bootloader_LoadImageParams bootArray[CONFIG_BOOTLOADER_NUM_INSTANCES];
        uint32_t imageSize = 0U;

        for(uint8_t inst = 0U; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
        {
            Bootloader_Params_init(&bootArray[inst].bootParams);
            Bootloader_BootImageInfo_init(&bootArray[inst].bootImageInfo);
            bootArray[inst].bootHandle = Bootloader_open(inst, &bootArray[inst].bootParams);
            bootArray[inst].loadStatus = BOOTLOADER_IMAGE_NOT_LOADED;

            if(bootArray[inst].bootHandle != NULL)
            {
                ((Bootloader_Config *)bootArray[inst].bootHandle)->scratchMemPtr = gScratchBuffer;
		    	status = App_loadImages(&bootArray[inst]);
            }

            if(SystemP_SUCCESS == status)
            {
                imageSize += Bootloader_getMulticoreImageSize(bootArray[inst].bootHandle);
            }
            else
            {
                DebugP_logError("App_loadImages failed !!!\r\n");
                break;
            }
        }

        Bootloader_profileUpdateAppimageSize(imageSize);
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
        }

         /* Deinitialise the flash and driver peripherial used by bootloader before starting other cores,
          * so that other systems can access and reinitialise it.
          */
        App_driversClose();
        SOC_moduleClockEnable(TISCI_DEV_MMCSD0, 0);

        if(SystemP_SUCCESS == status)
        {
            for(uint8_t inst = 0U; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
            {
                if(bootArray[inst].loadStatus == BOOTLOADER_IMAGE_LOADED)
                {
                    status = App_runCpus(&bootArray[inst]);
                    if(SystemP_SUCCESS != status)
                    {
                        DebugP_logError("App_runCpus failed !!!\r\n");
                    }
                }
                else
                {
                    Bootloader_powerOffCpu(bootArray[inst].bootHandle, &bootArray[inst].bootImageInfo.cpuInfo[inst + 1]);
                }
            }
        }

        Bootloader_closeDma();
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

        DebugP_log("SBL booting cores failed!!\r\n");

        UART_close(gUartHandle[CONFIG_UART_SBL]);
        gUartHandle[CONFIG_UART_SBL] = NULL;
    }
}

void sbl_emmc_main(void * args)
{
    App_bootMultipleCoreEmmc();

    vTaskDelete(NULL);
}

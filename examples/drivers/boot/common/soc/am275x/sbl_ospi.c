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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdlib.h>
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

#define SCRATCH_BUFFER_SIZE                             (0x1000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t App_loadImages(Bootloader_LoadImageParams *bootLoadParams);
int32_t App_runCpus(Bootloader_LoadImageParams *bootLoadParams);
int32_t App_loadSSOImage(Bootloader_Handle bootHandle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8_t gScratchBuffer[SCRATCH_BUFFER_SIZE];

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
}

void App_boardDriversClose()
{
#if !defined (SBL_BOOT_XIP_IMAGE)
    Flash_close(gFlashHandle[CONFIG_FLASH_SBL]);
    gFlashHandle[CONFIG_FLASH_SBL] = NULL;
#endif
}

void App_driversClose()
{
#if !defined (SBL_BOOT_XIP_IMAGE)
    OSPI_close(gOspiHandle[CONFIG_OSPI_SBL]);
    gOspiHandle[CONFIG_OSPI_SBL] = NULL;
#endif
}

void App_bootMultipleCoreFlash()
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("\r\n");
    DebugP_log("Starting OSPI Bootloader ... \r\n");

    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    status = App_boardDriversOpen();
    DebugP_assertNoLog(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("SBL Board_driversOpen");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_openDma();

        Bootloader_LoadImageParams bootArray[CONFIG_BOOTLOADER_NUM_INSTANCES];
        uint32_t imageSize = 0U;

        /*
         * Step 1: Load SSO (Shared Static Object) image first.
         *
         * The SSO image (CONFIG_BOOTLOADER_SHARED, offset 0x1C00000) contains
         * shared code and data placed in SSO_SHM.  It must be loaded into memory
         * before any per-core optishare image starts executing, because those
         * images reference symbols that live in SSO_SHM.
         *
         * The SSO image is NOT associated with any application core — do NOT call
         * App_runCpus for it.  Its bootloader handle is closed after loading.
         */
        {
            Bootloader_Params_init(&bootArray[CONFIG_BOOTLOADER_SHARED].bootParams);
            Bootloader_BootImageInfo_init(&bootArray[CONFIG_BOOTLOADER_SHARED].bootImageInfo);
            bootArray[CONFIG_BOOTLOADER_SHARED].bootHandle =
                Bootloader_open(CONFIG_BOOTLOADER_SHARED, &bootArray[CONFIG_BOOTLOADER_SHARED].bootParams);
            bootArray[CONFIG_BOOTLOADER_SHARED].loadStatus = BOOTLOADER_IMAGE_NOT_LOADED;

            if(bootArray[CONFIG_BOOTLOADER_SHARED].bootHandle != NULL)
            {
                ((Bootloader_Config *)bootArray[CONFIG_BOOTLOADER_SHARED].bootHandle)->scratchMemPtr = gScratchBuffer;
                status = App_loadSSOImage(bootArray[CONFIG_BOOTLOADER_SHARED].bootHandle);
                if(SystemP_SUCCESS == status)
                {
                    imageSize += Bootloader_getMulticoreImageSize(bootArray[CONFIG_BOOTLOADER_SHARED].bootHandle);
                    Bootloader_profileAddProfilePoint("SSO Image Load");
                }
                else
                {
                    DebugP_logWarn("SSO image load failed, shared memory may not be initialised !!!\r\n");
                    status = SystemP_SUCCESS; /* non-fatal: attempt per-core boot regardless */
                }
                Bootloader_close(bootArray[CONFIG_BOOTLOADER_SHARED].bootHandle);
                bootArray[CONFIG_BOOTLOADER_SHARED].bootHandle = NULL;
            }
        }

        /*
         * Step 2: Load per-core images.
         *
         * Iterate over all instances except CONFIG_BOOTLOADER_SHARED.
         * Each instance maps to one flash offset and one core image.
         */
        for(uint8_t inst = 0U; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
        {
            if(inst == CONFIG_BOOTLOADER_SHARED)
                continue;

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
                DebugP_logWarn("App_loadImages failed for core %s !!!\r\n", \
                    Bootloader_socGetCoreName(bootArray[inst].bootImageInfo.cpuInfo[inst].cpuId));

                DebugP_logWarn("App_loadImages failed at address %x !!!\r\n", \
                    bootArray[inst].bootImageInfo.cpuInfo[inst].entryPoint);
            }
        }

        Bootloader_profileUpdateAppimageSize(imageSize);
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI_SBL]));

        if(SystemP_SUCCESS == status)
        {
            Bootloader_profilePrintProfileLog();
            DebugP_log("Image loading done...\r\n");
            DebugP_log("Starting RTOS/Baremetal applications\r\n");
            UART_flushTxFifo(gUartHandle[CONFIG_UART0]);
        }

        /* Deinitialise the flash and driver peripheral used by bootloader before
         * starting other cores, so that other systems can access and reinitialise it.
         */
        App_boardDriversClose();
        App_driversClose();

        /*
         * Step 3: Run per-core images.
         *
         * CONFIG_BOOTLOADER_SHARED is skipped — its handle was already closed
         * after loading in Step 1 and there is no core to boot from it.
         */
        for(uint8_t inst = 0U; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
        {
            if(inst == CONFIG_BOOTLOADER_SHARED)
                continue;

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
                if(bootArray[inst].bootHandle != NULL)
                {
                    Bootloader_powerOffCpu(bootArray[inst].bootHandle, &bootArray[inst].bootImageInfo.cpuInfo[inst]);
                }
            }
        }

        Bootloader_closeDma();
    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("SBL booting cores failed!!\r\n");
    }
}

void sbl_ospi_main(void * args)
{
    App_bootMultipleCoreFlash();

    vTaskDelete(NULL);
}


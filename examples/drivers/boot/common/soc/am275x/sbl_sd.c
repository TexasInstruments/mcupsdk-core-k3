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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdlib.h>
#include <string.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BOOTLOADER_SD_R50_0_APPIMAGE_FILENAME              ("/sd0/app_r50_0")
#define BOOTLOADER_SD_R50_1_APPIMAGE_FILENAME              ("/sd0/app_r50_1")
#define BOOTLOADER_SD_R51_0_APPIMAGE_FILENAME              ("/sd0/app_r51_0")
#define BOOTLOADER_SD_R51_1_APPIMAGE_FILENAME              ("/sd0/app_r51_1")
#define BOOTLOADER_SD_C7X0_0_APPIMAGE_FILENAME             ("/sd0/app_dsp0_0")
#define BOOTLOADER_SD_C7X0_1_APPIMAGE_FILENAME             ("/sd0/app_dsp0_1")

#define BOOTLOADER_SD_APP_IMAGE_LOADED                  (1U)
#define BOOTLOADER_SD_MAX_NO_OF_FILES                   (6U)
#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE               (0x800000U)
#define SCRATCH_BUFFER_SIZE                             (0x1000U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8_t gScratchBuffer[SCRATCH_BUFFER_SIZE] __attribute__ ((section (".app"), aligned (128)));
uint32_t coresPresentMap = 0U;

Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

char* gBootLoaderSDFiles[BOOTLOADER_SD_MAX_NO_OF_FILES] =
           {
            BOOTLOADER_SD_R50_0_APPIMAGE_FILENAME,
            BOOTLOADER_SD_R50_1_APPIMAGE_FILENAME,
            BOOTLOADER_SD_R51_0_APPIMAGE_FILENAME,
            BOOTLOADER_SD_R51_1_APPIMAGE_FILENAME,
            BOOTLOADER_SD_C7X0_0_APPIMAGE_FILENAME,
            BOOTLOADER_SD_C7X0_1_APPIMAGE_FILENAME,
           };
char** pFiles = gBootLoaderSDFiles;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

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

void App_driversOpen()
{
    FF_Disk_t *diskStatus;

    /* Open MMCSD */
    gMmcsdHandle[CONFIG_MMCSD_SBL] = NULL;

    gMmcsdHandle[CONFIG_MMCSD_SBL] = MMCSD_open(CONFIG_MMCSD_SBL, &gMmcsdParams[CONFIG_MMCSD_SBL]);
    if(NULL == gMmcsdHandle[CONFIG_MMCSD_SBL])
    {
        DebugP_logError("MMCSD open failed for instance %d !!!\r\n", CONFIG_MMCSD_SBL);
    }

    /* Open UART */
    gUartHandle[CONFIG_UART_SBL] = NULL;

    gUartHandle[CONFIG_UART_SBL] = UART_open(CONFIG_UART_SBL, &gUartParams[CONFIG_UART_SBL]);
    if(NULL == gUartHandle[CONFIG_UART_SBL])
    {
        DebugP_logError("UART open failed for instance %d !!!\r\n", CONFIG_UART_SBL);
    }

   /* Init the MMCSD disk driver */
    diskStatus = FF_MMCSDDiskInit(gFFPartitionIds[CONFIG_FREERTOS_FAT_SBL].partitionName,
                                &gFFDisks[CONFIG_FREERTOS_FAT_SBL],
                                &gFFMmcsdConfig[CONFIG_FREERTOS_FAT_SBL],
                                gFFPartitionIds[CONFIG_FREERTOS_FAT_SBL].partitionNumber);
    if(NULL == diskStatus)
    {
        DebugP_logError("FF Disk Init failed for instance %d !!!\r\n", CONFIG_FREERTOS_FAT_SBL);
    }
}

void App_driversClose()
{
    MMCSD_close(gMmcsdHandle[CONFIG_MMCSD_SBL]);
    gMmcsdHandle[CONFIG_MMCSD_SBL] = NULL;

    UART_close(gUartHandle[CONFIG_UART_SBL]);
    gUartHandle[CONFIG_UART_SBL] = NULL;

    FF_MMCSDDiskDelete(&gFFDisks[CONFIG_FREERTOS_FAT_SBL]);
}

int32_t App_runCpus(Bootloader_Handle bootHandle,Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t cpuId;

    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        if(coresPresentMap & (0x1<<cpuId))
        {
            bootCpuInfo[cpuId] = bootImageInfo->cpuInfo[cpuId];
            status = Bootloader_runCpu(bootHandle, &bootCpuInfo[cpuId]);

            if(status != SystemP_SUCCESS)
            {
                DebugP_logError("App_runCpus failed for %s !!!\r\n", Bootloader_socGetCoreName(cpuId));
            }
        }
        else
        {
            Bootloader_powerOffCpu(bootHandle, &bootCpuInfo[cpuId]);
        }
    }

    return status;
}

void App_bootMultipleCoreSD()
{
    int32_t status;
    uint32_t appImageSize = 0;
    uint8_t noOfFiles = 0;

    DebugP_log("\r\n");
    DebugP_log("Starting SD Bootloader ... \r\n");

    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_openDma();

        Bootloader_BootImageInfo bootImageInfo;
		Bootloader_Params bootParams;
        Bootloader_Handle bootHandle;

        Bootloader_BootImageInfo_init(&bootImageInfo);

        while(noOfFiles < BOOTLOADER_SD_MAX_NO_OF_FILES)
        {
            Bootloader_Params_init(&bootParams);
            bootParams.fileName = pFiles[noOfFiles];

            /* Open File */
            bootHandle = Bootloader_open(CONFIG_BOOTLOADER_APP, &bootParams);

            if( bootHandle != NULL)
            {
                ((Bootloader_Config *)bootHandle)->scratchMemPtr = gScratchBuffer;

                status = Bootloader_parseAndLoadMultiCoreELF(bootHandle, &bootImageInfo);
                appImageSize += Bootloader_getMulticoreImageSize(bootHandle);

                if(status == SystemP_SUCCESS)
                {
                    coresPresentMap |= ((Bootloader_Config *)bootHandle)->coresPresentMap;
                }
            }

            if(status == SystemP_SUCCESS)
            {
                noOfFiles++;
            }
            else
            {
                break;
            }

            Bootloader_close(bootHandle);
        }
        if(status == SystemP_SUCCESS)
        {
            Bootloader_profileAddProfilePoint("File read from SD card");
            status = App_runCpus(bootHandle, &bootImageInfo);
        }

        Bootloader_profileUpdateAppimageSize(appImageSize);
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_SD, 0);
        if(status == SystemP_SUCCESS)
        {
            Bootloader_profileAddProfilePoint("SBL End");

            /* Use CONFIG_UART_SBL (UART0) for SBL logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

            /* Print SBL log  */
            Bootloader_profilePrintProfileLog();

            DebugP_log("Image loading done, switching to application ...\r\n");
            UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);

            /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_APP);
        }

        Bootloader_closeDma();
    }

    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    App_driversClose();
    Board_deinit();
}

void sbl_sd_main(void * args)
{
    App_bootMultipleCoreSD();

    vTaskDelete(NULL);
}


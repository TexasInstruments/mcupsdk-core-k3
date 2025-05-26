/*
 *  Copyright (C) 2023-25 Texas Instruments Incorporated
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

#define BOOTLOADER_SD_APPIMAGE_FILENAME                  ("/sd0/app")

#define BOOTLOADER_APP_IMAGE_LOADED                      (1U)
#define BOOTLOADER_SD_MAX_NO_OF_FILES                    (1U)

#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x4000000U) /* Size of section DDR specified in linker.cmd */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8_t gAppImage[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128U), section(".bss.filebuf")));

uint8_t socCpuCores[CSL_CORE_ID_MAX] = {0U};

Bootloader_Handle bootHandle;
Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

char* gBootLoaderSDFiles[BOOTLOADER_SD_MAX_NO_OF_FILES] = {BOOTLOADER_SD_APPIMAGE_FILENAME};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Call this API to stop the booting process and spin, so that a debugger can be
 * connected, load symbols and then make the 'loop' variable as 0 to continue
 * execution with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1U;
    while(loop)
        ;
}

int32_t App_OpenloadableImage(char* imageName)
{
    int32_t status = SystemP_SUCCESS;
    /* File I/O */

    /* Open app file */
    FF_FILE *appFp = ff_fopen(imageName, "rb");

    /* Check if file open succeeded */
    if(appFp == NULL)
    {
        status =  SystemP_FAILURE;
    }
    else
    {
        /* Check file size */
        uint32_t fileSize = ff_filelength(appFp);

        if(fileSize >= BOOTLOADER_APPIMAGE_MAX_FILE_SIZE)
        {
            /* Application size more than buffer size, abort */
            status = SystemP_FAILURE;
            DebugP_log("Appimage size exceeded limit !!\r\n");
        }
        else
        {
            /* Read the file into RAM buffer */
            memset(gAppImage, 0x0, sizeof(gAppImage));
            ff_fread(gAppImage, fileSize, 1, appFp);
        }

        /* Close the file */
        ff_fclose(appFp);
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
            bootImageInfo->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_WKUP_R5FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_WKUP_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0]));
        }
    }

    return status;
}

int32_t App_runCpus(void)
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
    status = Bootloader_socOpenFirewalls();

    DebugP_assertNoLog(SystemP_SUCCESS == status);

    System_init();
    Bootloader_profileAddProfilePoint("System_init");

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");

    status = Sciclient_getVersionCheck(1U);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        if (App_OpenloadableImage(gBootLoaderSDFiles[0]) == SystemP_SUCCESS)
        {
            Bootloader_BootImageInfo bootImageInfoDM;
            Bootloader_Params bootParamsDM;
            Bootloader_Handle bootHandleDM;

            Bootloader_BootImageInfo_init(&bootImageInfoDM);
            bootParamsDM.memArgsAppImageBaseAddr = (uintptr_t)gAppImage;

            bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_SD_SBL, &bootParamsDM);

            if (bootHandleDM != NULL)
            {
                ((Bootloader_Config *)bootHandleDM)->scratchMemPtr = gAppImage;
                ((Bootloader_Config *)bootHandleDM)->coresPresentMap = 0U;
                status = App_loadSelfcoreImage(bootHandleDM, &bootImageInfoDM);
                Bootloader_profileAddProfilePoint("App_loadSelfcoreImage");
            }

            Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleDM));
            Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_SD, 0U);
        }

        if(SystemP_SUCCESS == status)
        {
            /* Print SBL log as Linux prints log to the same UART port */
            Bootloader_profilePrintProfileLog();
            DebugP_log("Image loading done, switching to the second stage application ...\r\n");
            UART_flushTxFifo(gUartHandle[CONFIG_UART0]);

            status = App_runCpus();
        }
    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Some tests have failed!!\r\n");
        DebugP_assert(0);
    }
    else
    {
        /* Close all the open drivers. */
        Drivers_close();

        /* Call DPL deinit to close the tick timer and disable interrupts before jumping to DM Stage 2 */
        Dpl_deinit();

        Bootloader_JumpSelfCpu();

        /* Jump to CPU above it to prevent DDR clock disable in it. */
        System_deinit();
    }

    return 0;
}

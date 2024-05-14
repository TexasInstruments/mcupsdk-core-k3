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

#define BOOTLOADER_SD_MCU_R5_APPIMAGE_FILENAME          ("/sd0/mcu_r5_image")
#define BOOTLOADER_SD_WKUP_APPIMAGE_FILENAME            ("/sd0/wkup_r5_image")
#define BOOTLOADER_SD_A53_APPIMAGE_FILENAME             ("/sd0/linux_a53_image")

#define BOOTLOADER_SD_APP_IMAGE_LOADED                  (1)
#define BOOTLOADER_SD_MAX_NO_OF_FILES                   (2)

#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x2000000) /* Size of section DDR specified in linker.cmd */
uint8_t gAppimage[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

uint8_t socCpuCores[CSL_CORE_ID_MAX] = {0};

Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

char* gBootLoaderSDFiles[BOOTLOADER_SD_MAX_NO_OF_FILES] =
           {BOOTLOADER_SD_MCU_R5_APPIMAGE_FILENAME,
            BOOTLOADER_SD_WKUP_APPIMAGE_FILENAME
           };
char** pFiles = gBootLoaderSDFiles;

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

int App_OpenloadableImage(char* imageName)
{
    int status = SystemP_SUCCESS;
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
            memset(gAppimage, 0x0, sizeof(gAppimage));
            ff_fread(gAppimage, fileSize, 1, appFp);
        }

        /* Close the file */
        ff_fclose(appFp);
    }

    return status;
}

int32_t App_loadImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;
    Bootloader_Config *bootConfig;

    if(bootHandle != NULL)
    {
        bootConfig = (Bootloader_Config *)bootHandle;
        bootConfig->coresPresentMap = 0;
        status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

        /* Load CPUs */
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MCU_R5FSS0_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
            socCpuCores[CSL_CORE_ID_MCU_R5FSS0_0] = BOOTLOADER_SD_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_MCU_R5FSS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_WKUP_R5FSS0_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_WKUP_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0]));

            Bootloader_profileAddCore(CSL_CORE_ID_WKUP_R5FSS0_0);
            Bootloader_profileAddProfilePoint("App_loadImages(CSL_CORE_ID_WKUP_R5FSS0_0)");
        }
    }

    return status;
}

int32_t App_loadLinuxImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;
    Bootloader_Config *bootConfig;

    if(bootHandle != NULL)
    {
        bootConfig = (Bootloader_Config *)bootHandle;
        bootConfig->coresPresentMap = 0;
        status = Bootloader_parseAndLoadLinuxAppImage(bootHandle, bootImageInfo);
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS0_0)))
        {
		    bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
	        Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));
            socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_SD_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0];
        }
    }

	return status;
}

int32_t App_runCpus(Bootloader_Handle bootHandle)
{
    int32_t status = SystemP_FAILURE;
    uint8_t cpuId;

    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        if(cpuId == CSL_CORE_ID_A53SS0_0)
        {
            continue;
        }

        if(socCpuCores[cpuId] == BOOTLOADER_SD_APP_IMAGE_LOADED)
        {
            status = Bootloader_runCpu(bootHandle, &bootCpuInfo[cpuId]);
        }
    }

    return status;
}

int32_t App_runLinuxCpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    /* Unlock all the control MMRs. Linux/U-boot expects all the MMRs to be unlocked */
    SOC_unlockAllMMR();

    if(socCpuCores[CSL_CORE_ID_A53SS0_0] == BOOTLOADER_SD_APP_IMAGE_LOADED)
    {
	    status = Bootloader_runCpu(bootHandle, &bootCpuInfo[CSL_CORE_ID_A53SS0_0]);
    }
	return status;
}

int main()
{
    int32_t status;
    uint32_t appImageSize = 0;
    uint8_t noOfFiles = 0;

    Bootloader_profileReset();

    Bootloader_socWaitForFWBoot();
    status = Bootloader_socOpenFirewalls();

    DebugP_assertNoLog(status == SystemP_SUCCESS);

    System_init();
    Bootloader_profileAddProfilePoint("System_init");

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("Board_driversOpen");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_BootImageInfo bootImageInfo;
		Bootloader_Params bootParams;
        Bootloader_Handle bootHandle;

		Bootloader_BootImageInfo bootImageInfoLinux;
		Bootloader_Params bootParamsLinux;
        Bootloader_Handle bootHandleLinux;

        Bootloader_Params_init(&bootParams);
		Bootloader_Params_init(&bootParamsLinux);

		Bootloader_BootImageInfo_init(&bootImageInfo);
		Bootloader_BootImageInfo_init(&bootImageInfoLinux);

        while(noOfFiles < BOOTLOADER_SD_MAX_NO_OF_FILES)
        {
            Bootloader_Params_init(&bootParams);
		    Bootloader_BootImageInfo_init(&bootImageInfo);
            bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppimage;
            if(App_OpenloadableImage(pFiles[noOfFiles]) == SystemP_SUCCESS)
            {
                bootHandle = Bootloader_open(CONFIG_BOOTLOADER_APP, &bootParams);

                if(bootHandle != NULL)
                {
                    appImageSize += Bootloader_getMulticoreImageSize(bootHandle);
                    status = App_loadImages(bootHandle, &bootImageInfo);
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
        }

        bootParamsLinux.memArgsAppImageBaseAddr = (uintptr_t)gAppimage;
        if(App_OpenloadableImage(BOOTLOADER_SD_A53_APPIMAGE_FILENAME) == SystemP_SUCCESS)
        {
            bootHandleLinux = Bootloader_open(CONFIG_BOOTLOADER_APP, &bootParamsLinux);
		    if(SystemP_SUCCESS == status)
		    {
                if(bootHandleLinux != NULL)
		{
                    appImageSize+=Bootloader_getMulticoreImageSize(bootHandleLinux);
                    status = App_loadLinuxImages(bootHandleLinux, &bootImageInfoLinux);
                    Bootloader_profileAddProfilePoint("App_loadLinuxImages");
                }
            }
        }

        /* Power off MMC 1 instance */
        status = SOC_moduleClockEnable(TISCI_DEV_MMCSD1, 0);

        Bootloader_profileUpdateAppimageSize(appImageSize);
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_SD, 0);
		if(SystemP_SUCCESS == status)
		{
			/* Print SBL log as Linux prints log to the same UART port */
			Bootloader_profilePrintProfileLog();
			DebugP_log("Image loading done, switching to application ...\r\n");
			DebugP_log("Starting linux and RTOS/Baremetal applications\r\n");
			UART_flushTxFifo(gUartHandle[CONFIG_UART0]);
		}

		if(SystemP_SUCCESS == status)
		{
			status = App_runLinuxCpu(bootHandleLinux, &bootImageInfoLinux);
            Bootloader_close(bootHandleLinux);
		}

        if(SystemP_SUCCESS == status)
		{
			status = App_runCpus(bootHandle);
            Bootloader_close(bootHandle);
		}

    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to DM*/
    Dpl_deinit();

    Bootloader_JumpSelfCpu();

    Drivers_close();
    System_deinit();

    return 0;
}

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

/*
 * Auto generated file - DO NOT MODIFY
 */

#include <stdlib.h>
#include <string.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>

#define BOOTLOADER_SD_MULTICORE_APPIMAGE_FILENAME ("/sd0/app")
#define BOOTLOADER_SD_DM_APPIMAGE_FILENAME ("/sd0/dm")
#define BOOTLOADER_SD_LINUX_APPIMAGE_FILENAME ("/sd0/linux")

#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x800000) /* Size of section DDR specified in linker.cmd */
uint8_t gAppImageBuf[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

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
            memset(gAppImageBuf, 0x0, sizeof(gAppImageBuf));
            ff_fread(gAppImageBuf, fileSize, 1, appFp);
        }

        /* Close the file */
        ff_fclose(appFp);
    }

    return status;
}

int32_t App_loadImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
        status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

        /* Load CPUs */
        if(status == SystemP_SUCCESS)
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_M4FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_M4FSS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_M4FSS0_0]));
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
            /* Set clocks for self cluster */
            bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_R5FSS0_0);

            /* Reset self cluster, both Core0 and Core 1. Init RAMs and load the app  */
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
			status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));
		}
	}

	return status;
}

int32_t App_runCpus(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

	status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_M4FSS0_0]));

	return status;
}

int32_t App_runLinuxCpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    /* Initialize GTC by enabling using Syscfg */

	status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));

	return status;
}
int main()
{
    int32_t status;

    Bootloader_profileReset();

    Bootloader_socWaitForFWBoot();
    //Bootloader_socOpenFirewalls();

    System_init();
    Bootloader_profileAddProfilePoint("System_init");

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("Board_driversOpen");

    status = Sciclient_getVersionCheck(1);


    Bootloader_profileAddProfilePoint("File read from SD card");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_BootImageInfo bootImageInfo;
		Bootloader_Params bootParams;
        Bootloader_Handle bootHandle;

        Bootloader_BootImageInfo bootImageInfoDM;
		Bootloader_Params bootParamsDM;
        Bootloader_Handle bootHandleDM;

        // Bootloader_BootImageInfo bootImageInfoLinux;
        // Bootloader_Params bootParamsLinux;
        // Bootloader_Handle bootHandleLinux;

        Bootloader_Params_init(&bootParams);
        Bootloader_Params_init(&bootParamsDM);
		//Bootloader_Params_init(&bootParamsLinux);

		Bootloader_BootImageInfo_init(&bootImageInfo);
        Bootloader_BootImageInfo_init(&bootImageInfoDM);
		//Bootloader_BootImageInfo_init(&bootImageInfoLinux);

        bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;
        bootParamsDM.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;
        //bootParamsLinux.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;

        if(App_OpenloadableImage(BOOTLOADER_SD_MULTICORE_APPIMAGE_FILENAME) == SystemP_SUCCESS)
        {
            bootHandle = Bootloader_open(CONFIG_BOOTLOADER_APP, &bootParams);

            if(bootHandle != NULL)
            {
                status = App_loadImages(bootHandle, &bootImageInfo);
                Bootloader_close(bootHandle);
                Bootloader_profileAddProfilePoint("App_loadImages");
            }
        }

        if(status == SystemP_SUCCESS)
        {
            if(App_OpenloadableImage(BOOTLOADER_SD_DM_APPIMAGE_FILENAME) == SystemP_SUCCESS)
            {
                bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_APP, &bootParamsDM);

                if(bootHandleDM !=NULL)
                {
                    status = App_loadSelfcoreImage(bootHandleDM, &bootImageInfoDM);
                    Bootloader_profileAddProfilePoint("App_loadSelfcoreImage");
                }
            }
        }

        // if(status == SystemP_SUCCESS)
        // {
        //     if(App_OpenloadableImage(BOOTLOADER_SD_LINUX_APPIMAGE_FILENAME) == SystemP_SUCCESS)
        //     {
        //         bootHandleLinux = Bootloader_open(CONFIG_BOOTLOADER_APP, &bootParamsLinux);

        //         if(bootHandleLinux != NULL)
        //         {
        //             status = App_loadLinuxImages(bootHandleLinux, &bootImageInfoLinux);
        //             Bootloader_close(bootHandleLinux);
        //             Bootloader_profileAddProfilePoint("App_loadLinuxImages");
        //         }
        //     }
        // }

		// if(SystemP_SUCCESS == status)
		// {
		// 	status = App_runLinuxCpu(bootHandleLinux, &bootImageInfoLinux);
		// }

        if(SystemP_SUCCESS == status)
		{
			status = App_runCpus(bootHandle, &bootImageInfo);
		}

        if(status == SystemP_SUCCESS)
        {
            /* Reset self cluster, both Core0 and Core 1. Init RAMs and run the app  */
            Bootloader_profileAddProfilePoint("SBL End");
            Bootloader_profilePrintProfileLog();
            DebugP_log("Image loading done, switching to application ...\r\n");
            //UART_flushTxFifo(gUartHandle[CONFIG_UART0]);
        }

    }

    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    MMCSD_deinit();

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to DM*/
    Dpl_deinit();

    Bootloader_JumpSelfCpu();

    Drivers_close();
    System_deinit();

    return 0;
}



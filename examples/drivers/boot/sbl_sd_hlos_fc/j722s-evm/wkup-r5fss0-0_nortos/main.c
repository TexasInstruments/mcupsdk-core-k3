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

#include <stdlib.h>
#include <string.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>

#define BOOTLOADER_SD_APPIMAGE_FILENAME          ("/sd0/app")
#define BOOTLOADER_HSM_IMG_LOAD_ADDR             (0x79100000U)
#define BOOTLOADER_HSM_IMG_MAX_SIZE              (0x40000U)
#define BOOTLOADER_SD_HSM_BINARY                 ("/sd0/hsm.bin")
#define BOOTLOADER_HSM_IMG_NOT_FOUND             (((int32_t)(-2)))
#define BOOTLOADER_APP_IMAGE_LOADED              (1)
#define BOOTLOADER_SD_MAX_NO_OF_FILES            (1)

#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x4000000) /* Size of section DDR specified in linker.cmd */
uint8_t gAppimage[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

uint8_t socCpuCores[CSL_CORE_ID_MAX] = {0};

Bootloader_Handle bootHandle;
Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

char* gBootLoaderSDFiles[BOOTLOADER_SD_MAX_NO_OF_FILES] =
           {BOOTLOADER_SD_APPIMAGE_FILENAME
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

int32_t App_loadImages()
{
	int32_t status = SystemP_FAILURE;

    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Config *bootConfig;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppimage;

    bootHandle = Bootloader_open(CONFIG_BOOTLOADER_APP, &bootParams);

    if(bootHandle != NULL)
    {
        bootConfig = (Bootloader_Config *)bootHandle;
        bootConfig->coresPresentMap = 0;
        status = Bootloader_parseMultiCoreAppImage(bootHandle, &bootImageInfo);

        /* Load CPUs */
        if (!Bootloader_socIsMCUResetIsoEnabled())
        {
            if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MCU_R5FSS0_0)))
            {
                bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
                socCpuCores[CSL_CORE_ID_MCU_R5FSS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_MCU_R5FSS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0];
            }
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_WKUP_R5FSS0_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_WKUP_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_WKUP_R5FSS0_0);
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MAIN_R5FSS0_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MAIN_R5FSS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_MAIN_R5FSS0_0);
            socCpuCores[CSL_CORE_ID_MAIN_R5FSS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_C75SS0_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS0_0);
            socCpuCores[CSL_CORE_ID_C75SS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_C75SS1_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS1_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS1_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS1_0);
            socCpuCores[CSL_CORE_ID_C75SS1_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS1_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS1_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS0_0)))
		{
			bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
			status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
            socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0];
		}
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS1_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS1_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS1_0);
            socCpuCores[CSL_CORE_ID_A53SS1_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS1_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0];
        }
    }

    return status;
}

int32_t App_runCpus()
{
    int32_t status = SystemP_SUCCESS;
    uint8_t cpuId;

    /* Unlock all the control MMRs. Linux/U-boot expects all the MMRs to be unlocked */
    SOC_unlockAllMMR();

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

int32_t App_mmcCopyHsmImage(uint8_t* pHsm, uint32_t numBytes)
{
    int32_t status = SystemP_SUCCESS;
    char *fileName = BOOTLOADER_SD_HSM_BINARY;

    /* Open file */
    FF_FILE *appFp = ff_fopen(fileName, "rb");

    /* Check if file open succeeded */
    if(appFp == NULL)
    {
        status = BOOTLOADER_HSM_IMG_NOT_FOUND;
    }
    else
    {
        /* Check file size */
        uint32_t fileSize = ff_filelength(appFp);
        if(fileSize >= BOOTLOADER_HSM_IMG_MAX_SIZE)
        {
            /* Binary size more than buffer size, abort */
            status = SystemP_FAILURE;
            DebugP_logError("HSM Binary size exceeded limit !!\r\n");
        }
        else
        {
            /* Read the file into RAM buffer */
            memset((uint8_t *)BOOTLOADER_HSM_IMG_LOAD_ADDR, 0x0, BOOTLOADER_HSM_IMG_MAX_SIZE);
            ff_fread((uint8_t *)BOOTLOADER_HSM_IMG_LOAD_ADDR, fileSize, 1, appFp);
        }
        /* Close the file */
        ff_fclose(appFp);
    }
    return status;
}

int32_t App_loadAndAuthHsmBinary(void)
{
    int32_t status = SystemP_SUCCESS;
    /* Define sbl scratch memory as HSM address */
    uint8_t *sblScratchMem = ((uint8_t *)(BOOTLOADER_HSM_IMG_LOAD_ADDR));
    struct tisci_msg_proc_auth_boot_req authReq;
    struct tisci_msg_proc_auth_boot_resp authResp = {0};
    struct tisci_msg_proc_get_status_resp cpuStatus;
    uint32_t hsmCoreProcId = SCICLIENT_PROC_ID_HSM_M4FSS0_CORE0;

    status = App_mmcCopyHsmImage(sblScratchMem, BOOTLOADER_HSM_IMG_MAX_SIZE);

    if(status != SystemP_SUCCESS)
    {
        if (status == BOOTLOADER_HSM_IMG_NOT_FOUND)
        {
            DebugP_log("\n HSM Binary is not present.. \r\n");
            DebugP_log("\n Continuing with normal boot.. \r\n");
        }
        else
        {
            DebugP_logError("\nFailed to copy hsm binary.. \r\n");
        }
    }
    else
    {
        /* Get Processor state */
        DebugP_log("Calling Sciclient_procBootGetProcessorState, ProcId 0x%x... \r\n", hsmCoreProcId);
        status = Sciclient_procBootGetProcessorState(hsmCoreProcId, &cpuStatus, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != SystemP_SUCCESS)
        {
            DebugP_logError("Sciclient_procBootGetProcessorState...FAILED \r\n");
        }

        /* Request for processor */
        DebugP_log("Calling Sciclient_procBootRequestProcessor, ProcId 0x%x... \r\n", hsmCoreProcId);
        status = Sciclient_procBootRequestProcessor(hsmCoreProcId, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != SystemP_SUCCESS)
        {
            DebugP_logError("Sciclient_procBootRequestProcessor, ProcId 0x%x...FAILED \r\n", hsmCoreProcId);
        }

        /* Setting HALT for Processor */
        DebugP_log("Setting HALT for ProcId 0x%x... \r\n", hsmCoreProcId);
        status =  Sciclient_procBootSetSequenceCtrl(hsmCoreProcId, TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_HSM_M4_RESET, 0, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != SystemP_SUCCESS)
        {
            DebugP_logError("Sciclient_procBootSetSequenceCtrl...FAILED \r\n");
        }

        authReq.certificate_address_hi = 0;
        authReq.certificate_address_lo = (uint32_t) sblScratchMem;
        /* Request TIFS to authenticate and load the HSM image */
        DebugP_log("Calling Sciclient_procBootAuthAndStart ... \r\n");
        status = Sciclient_procBootAuthAndStart(&authReq, &authResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != SystemP_SUCCESS)
        {
            DebugP_logError("Sciclient_procBootAuthAndStart...FAILED \r\n");
        }

        /* Clearing HALT for Processor */
        DebugP_log("Clearing HALT for ProcId 0x%x... \r\n", hsmCoreProcId);
        status =  Sciclient_procBootSetSequenceCtrl(hsmCoreProcId, 0, TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_HSM_M4_RESET, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != SystemP_SUCCESS)
        {
            DebugP_logError("Sciclient_procBootSetSequenceCtrl...FAILED \r\n");
        }

        /* Release Processor */
        DebugP_log("Calling Sciclient_procBootReleaseProcessor, ProcId 0x%x... \r\n", hsmCoreProcId);
        status = Sciclient_procBootReleaseProcessor(hsmCoreProcId, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != SystemP_SUCCESS)
        {
            DebugP_logError("Sciclient_procBootReleaseProcessor, ProcId 0x%x...FAILED \r\n", hsmCoreProcId);
        }
    }

    return status;
}

int main()
{
    int32_t status;
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
        DebugP_log("Booting HSM core ... \r\n");
        status = App_loadAndAuthHsmBinary();
        if(SystemP_SUCCESS == status)
        {
            DebugP_log("HSM Core booted successfully \r\n");
        }
        else
        {
            DebugP_log("Failed to boot HSM core !! \r\n");
        }

        if(App_OpenloadableImage(pFiles[noOfFiles]) == SystemP_SUCCESS)
        {
            status = App_loadImages();
        }
    }

    /* Power off MMC 1 instance */
    status = SOC_moduleClockEnable(TISCI_DEV_MMCSD1, 0);

    Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandle));
    Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_SD, 0);
    if(SystemP_SUCCESS == status)
    {
        /* Print SBL log as Linux prints log to the same UART port */
        Bootloader_profilePrintProfileLog();
        DebugP_log("Image loading done, switching to application ...\r\n");
        DebugP_log("Starting linux and RTOS/Baremetal applications\r\n");
        UART_flushTxFifo(gUartHandle[CONFIG_UART0]);

        status = App_runCpus();
    }

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Some tests have failed!!\r\n");
        DebugP_assert(0);
    }
    else
    {
        Board_driversClose();
        Drivers_close();
        /* Call DPL deinit to close the tick timer and disable interrupts before jumping to DM*/
        Dpl_deinit();

        Bootloader_JumpSelfCpu();
        System_deinit();
    }

    return 0;
}

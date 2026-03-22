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


#define BOOTLOADER_APP_IMAGE_LOADED     (0x1U)
#define BOOTLOADER_HSM_IMG_LOAD_ADDR    (0x79100000U)
#define BOOTLOADER_HSM_HEADER           (0x30U)
#define BOOTLOADER_HSM_IMG_NOT_FOUND    ((int32_t)(-2))
#define BOOTLOADER_HSM_BIN_SIZE         (192*1024U)        /* 192KB */

#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x4000000) /* Size of section DDR specified in linker.cmd */
uint8_t gAppimage[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

uint8_t socCpuCores[CSL_CORE_ID_MAX] = {0};

Bootloader_Handle bootHandleApp, bootHandleHSM;
Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

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

int32_t App_loadImages(void)
{
	int32_t status = SystemP_FAILURE;

    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Config *bootConfig;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    bootHandleApp = Bootloader_open(CONFIG_BOOTLOADER_APP, &bootParams);

    if(bootHandleApp != NULL)
    {
        /* scratch pointer is required for image authentication */
        ((Bootloader_Config *)bootHandleApp)->scratchMemPtr = gAppimage;

        bootConfig = (Bootloader_Config *)bootHandleApp;
        bootConfig->coresPresentMap = 0;
        status = Bootloader_parseMultiCoreAppImage(bootHandleApp, &bootImageInfo);

        /* Load CPUs */
        if (!Bootloader_socIsMCUResetIsoEnabled())
        {
            if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandleApp, CSL_CORE_ID_MCU_R5FSS0_0)))
            {
                bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootHandleApp, &(bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
                socCpuCores[CSL_CORE_ID_MCU_R5FSS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_MCU_R5FSS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0];
            }
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandleApp, CSL_CORE_ID_WKUP_R5FSS0_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_WKUP_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandleApp, &(bootImageInfo.cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_WKUP_R5FSS0_0);
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandleApp, CSL_CORE_ID_MAIN_R5FSS0_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MAIN_R5FSS0_0);
            status = Bootloader_loadCpu(bootHandleApp, &(bootImageInfo.cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_MAIN_R5FSS0_0);
            socCpuCores[CSL_CORE_ID_MAIN_R5FSS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandleApp, CSL_CORE_ID_C75SS0_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS0_0);
            status = Bootloader_loadCpu(bootHandleApp, &(bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS0_0);
            socCpuCores[CSL_CORE_ID_C75SS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandleApp, CSL_CORE_ID_C75SS1_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS1_0);
            status = Bootloader_loadCpu(bootHandleApp, &(bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS1_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS1_0);
            socCpuCores[CSL_CORE_ID_C75SS1_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS1_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS1_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandleApp, CSL_CORE_ID_A53SS0_0)))
		{
			bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
			status = Bootloader_loadCpu(bootHandleApp, &(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
            socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0];
		}
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandleApp, CSL_CORE_ID_A53SS1_0)))
        {
            bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS1_0);
            status = Bootloader_loadCpu(bootHandleApp, &(bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS1_0);
            socCpuCores[CSL_CORE_ID_A53SS1_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS1_0] = bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0];
        }
    }

    return status;
}

int32_t App_runCpus(void)
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
                    status = Bootloader_runCpu(bootHandleApp, &bootCpuInfo[cpuId]);
                }
        }
    }
    Bootloader_close(bootHandleApp);
    return status;
}

int32_t App_eMMCCopyHsmImage(uint8_t* ptr)
{
    int32_t retVal = SystemP_SUCCESS;

    Bootloader_Params bootParams;
    Bootloader_Params_init(&bootParams);

    bootHandleHSM = Bootloader_open(CONFIG_BOOTLOADER_HSM, &bootParams);

    ((Bootloader_Config *)bootHandleHSM)->scratchMemPtr = ptr;
    Bootloader_Config *config = (Bootloader_Config *)bootHandleHSM;

    retVal = config->fxns->imgReadFxn((void *)config->scratchMemPtr, BOOTLOADER_HSM_BIN_SIZE, config->args);
    CacheP_wbInv((void *)config->scratchMemPtr, BOOTLOADER_HSM_BIN_SIZE, CacheP_TYPE_ALL);

    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("\nimgReadFxn FAILED\r\n");
    }
    else
    {
        if (*ptr != BOOTLOADER_HSM_HEADER)
        {
            retVal = BOOTLOADER_HSM_IMG_NOT_FOUND;
        }
    }
    return retVal;
}

int32_t App_loadAndAuthHsmBinary(void)
{
    int32_t status = SystemP_SUCCESS;
    struct tisci_msg_proc_auth_boot_req authReq;
    struct tisci_msg_proc_auth_boot_resp response = {0};
    struct tisci_msg_proc_get_status_resp cpuStatus;
    uint32_t hsmCoreProcId = SCICLIENT_PROC_ID_HSM_M4FSS0_CORE0;

    /* Define sbl scratch memory as HSM address */
    uint8_t *sblScratchMem = ((uint8_t *)(BOOTLOADER_HSM_IMG_LOAD_ADDR));

    status = App_eMMCCopyHsmImage(sblScratchMem);

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
        authReq.certificate_address_lo = (uint32_t)sblScratchMem;
        /* Request TIFS to authenticate and load the HSM image */
        DebugP_log("Calling Sciclient_procBootAuthAndStart ... \r\n");
        status = Sciclient_procBootAuthAndStart(&authReq, &response, SCICLIENT_SERVICE_WAIT_FOREVER);
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

        status = App_loadImages();
        Bootloader_profileAddProfilePoint("App_loadImages");

        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleApp));
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_EMMC, MMCSD_getInputClk(gMmcsdHandle[CONFIG_MMCSD0]));

		if(SystemP_SUCCESS == status)
		{
			/* Print SBL log as Linux prints log to the same UART port */
			Bootloader_profilePrintProfileLog();
			DebugP_log("Image loading done, switching to application ...\r\n");
			DebugP_log("Starting linux and RTOS/Baremetal applications\r\n");
			UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);

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
        Board_driversClose();
        Drivers_close();

        /* Call DPL deinit to close the tick timer and disable interrupts before jumping to Stage2*/
        Dpl_deinit();

        Bootloader_JumpSelfCpu();
        System_deinit();
    }

    return 0;
}

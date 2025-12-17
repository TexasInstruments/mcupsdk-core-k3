/*
 *  Copyright (C) 2023-26 Texas Instruments Incorporated
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
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include "ti_board_config.h"
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include <drivers/bootloader.h>
#include <drivers/device_manager/sciclient.h>
#include "FreeRTOS.h"
#include "task.h"
#include <drivers/device_manager/sciserver/sciserver_init.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * This start address and length depends upon the linker memory for second stage SBL.
 * It is necessary to change the below start address and length if in case the linker
 * memory region for second stage SBL is changed.
 */
#define BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_START       0xC2000000
#define BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_LENGTH      0x800000

#define BOOTLOADER_APP_IMAGE_LOADED     (0x1U)
#define BOOTLOADER_OSPI_ADDR            (0x60000000U)
#define BOOTLOADER_OSPI_OFFSET_HSM      (0x80000U)
#define BOOTLOADER_HSM_HEADER           (0x30)
#define BOOTLOADER_HSM_IMG_NOT_FOUND    ((int32_t)(-2))
/*
 * FreeRTOS Task Size and Priorities
 */
#define TASK_SIZE (16384U/sizeof(configSTACK_DEPTH_TYPE))
#define TASK_PRI_MAIN_THREAD  (configMAX_PRIORITIES-1)
#define TASK_PRI_BOOT_THREAD  (configMAX_PRIORITIES-1)

/* Stack size allocated for the sciserver task */
#define SCISERVER_TASK_STACK_SIZE                   (2U*1024U)

/* Stack memory alignment requirement for the sciserver task */
#define SCISERVER_TASK_STACK_ALIGNMENT              (32)

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

/*
 * This buffer needs to be defined for OSPI boot in case of HS device for
 * image authentication.
 * The size of the buffer should be large enough to accomodate the application image.
 */
uint8_t gAppImage[0x800000U] __attribute__ ((section (".app"), aligned (128U)));
uint8_t socCpuCores[CSL_CORE_ID_MAX]    = {0U};

Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

/* FreeRTOS Task-based objects */
StackType_t gMainTaskStack[TASK_SIZE] __attribute__((aligned(32U)));
StaticTask_t gMainTaskObj;
TaskHandle_t gMainTask;

StackType_t gBootTaskStack[TASK_SIZE] __attribute__((aligned(32U)));
StaticTask_t gBootTaskObj;
TaskHandle_t gBootTask;

/* Stack buffers for user high and low priority tasks */
uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserHiTaskStack[SCISERVER_TASK_STACK_SIZE];
uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserLoTaskStack[SCISERVER_TASK_STACK_SIZE];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Call this API to stop the booting process and spin, so that you can connect a
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1U;
    while(loop)
        ;
}

int32_t App_loadImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
        status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

        /* Load CPUs other than SBL core */
        if (!Bootloader_socIsMCUResetIsoEnabled())
        {
            if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MCU_R5FSS0_0)))
            {
                bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
                socCpuCores[CSL_CORE_ID_MCU_R5FSS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
                bootCpuInfo[CSL_CORE_ID_MCU_R5FSS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0];
            }
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_MAIN_R5FSS0_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MAIN_R5FSS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_MAIN_R5FSS0_0);
            socCpuCores[CSL_CORE_ID_MAIN_R5FSS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_MAIN_R5FSS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_C75SS0_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS0_0);
            socCpuCores[CSL_CORE_ID_C75SS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_C75SS1_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_C75SS1_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS1_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_C75SS1_0);
            socCpuCores[CSL_CORE_ID_C75SS1_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_C75SS1_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_C75SS1_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS0_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
            socCpuCores[CSL_CORE_ID_A53SS0_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS0_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0];
        }
        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootHandle, CSL_CORE_ID_A53SS1_0)))
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS1_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS1_0);
            status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS1_0]));
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS1_0);
            socCpuCores[CSL_CORE_ID_A53SS1_0] = BOOTLOADER_APP_IMAGE_LOADED;
            bootCpuInfo[CSL_CORE_ID_A53SS1_0] = bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS1_0];
        }
    }

    return status;
}

int32_t App_runCpus(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_FAILURE;
    uint8_t cpuId;

    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        if(socCpuCores[cpuId] == BOOTLOADER_APP_IMAGE_LOADED)
        {
            if (((cpuId == CSL_CORE_ID_MCU_R5FSS0_0) && !Bootloader_socIsMCUResetIsoEnabled()) ||
                (cpuId != CSL_CORE_ID_MCU_R5FSS0_0))
            {
                status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[cpuId]));
            }
        }
    }
    return status;
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

int32_t App_ospiCopyHsmImage(uint8_t** dstAddr, uint32_t srcOffsetAddr)
{
    int32_t retVal = CSL_PASS;

    /* In case of OSPI NOR, Pointer to OSPI NOR can be directly passed to
       Sciclient_procBootAuthAndStart() API */
    /* Check if HSM binary is present or not */
    uint8_t* ptr = (uint8_t *) *dstAddr;
    if (*ptr != BOOTLOADER_HSM_HEADER)
    {
        retVal = BOOTLOADER_HSM_IMG_NOT_FOUND;
    }
    return retVal;
}

int32_t App_loadAndAuthHsmBinary(void)
{
    int32_t status = SystemP_SUCCESS;
    /* Define sbl scratch memory as HSM address */
    uint8_t *sblScratchMem = ((uint8_t *)(BOOTLOADER_OSPI_ADDR + BOOTLOADER_OSPI_OFFSET_HSM));
    struct tisci_msg_proc_auth_boot_req authReq;
    struct tisci_msg_proc_auth_boot_resp response = {0};
    struct tisci_msg_proc_get_status_resp cpuStatus;
    uint32_t hsmCoreProcId = SCICLIENT_PROC_ID_HSM_M4FSS0_CORE0;

    status = App_ospiCopyHsmImage(&sblScratchMem, BOOTLOADER_OSPI_OFFSET_HSM);

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

void sciserver_main_thread(void *args)
{
    int32_t status = SystemP_SUCCESS;

    /* Configure sciserver task parameters */
    Sciserver_TirtosCfgPrms_t sciserverCfg = {0};
    sciserverCfg.hiTaskStack    =   gUserHiTaskStack;
    sciserverCfg.loTaskStack    =   gUserLoTaskStack;
    sciserverCfg.taskStackSize  =   SCISERVER_TASK_STACK_SIZE;

    /* Open drivers */
    Drivers_open();
    /* Open flash and board drivers */
    status = Board_driversOpen();
    DebugP_assert(status==SystemP_SUCCESS);

    sciServer_init(&sciserverCfg);

    /* Close board and flash drivers */
    Board_driversClose();
    /* Close drivers */
    Drivers_close();

    vTaskDelete(NULL);
}

void sbl_ospi_stage2_main_thread(void *args)
{
    int32_t status;

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    status = App_boardDriversOpen();
    DebugP_assertNoLog(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("SBL Board_driversOpen");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_BootImageInfo bootImageInfo;
        Bootloader_Params bootParams;
        Bootloader_Handle bootHandle;

        Bootloader_Params_init(&bootParams);
        Bootloader_BootImageInfo_init(&bootImageInfo);

        bootHandle = Bootloader_open(CONFIG_BOOTLOADER_FLASH_APPIMAGE, &bootParams);

        Bootloader_ReservedMemInit(BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_START, \
                                   BOOTLOADER_SECOND_STAGE_RESERVED_MEMORY_LENGTH);

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
            if(bootHandle != NULL)
            {
                ((Bootloader_Config *)bootHandle)->scratchMemPtr = gAppImage;
                status = App_loadImages(bootHandle, &bootImageInfo);
                Bootloader_profileAddProfilePoint("App_loadImages");
            }
        }

        if(SystemP_SUCCESS == status)
        {
            status = App_runCpus(bootHandle, &bootImageInfo);
        }

        Bootloader_close(bootHandle);

        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandle));
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI_SBL]));

        if(SystemP_SUCCESS == status)
        {
            /* Use CONFIG_UART_SBL (UART0) for SBL logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

            /* Print SBL log as Linux prints log to the same UART port */
            Bootloader_profilePrintProfileLog();
            DebugP_log("Image loading done, switching to application ...\r\n");
            DebugP_log("Starting RTOS/Baremetal applications\r\n");
            UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);

            /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_APP);
        }
    }

    if(status != SystemP_SUCCESS )
    {
        /* Use CONFIG_UART_SBL (UART0) for SBL logs */
        DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

        /* Open UART to print failure log */
        DebugP_logError("Stage 2 booting failed!!\r\n");

        /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
        DebugP_uartSetDrvIndex(CONFIG_UART_APP);
    }

    /* Deinitialise the flash and driver peripherial used by boot-loader before starting other cores,
     * so that other systems can access and re-initialise it. */
    App_boardDriversClose();
    App_driversClose();

    /* Delete the task upon completion */
    vTaskDelete(NULL);
}

int main()
{
    Bootloader_profileReset();

    /* Init SOC-specific modules */
    System_init();
    Bootloader_profileAddProfilePoint("System_init");
    Board_init();
    Bootloader_profileAddProfilePoint("Board_init");

    gMainTask = xTaskCreateStatic(sciserver_main_thread,    /* Pointer to the function that implements the task. */
                                  "sciserver_main_thread",  /* Text name for the task.  This is to facilitate debugging only. */
                                  TASK_SIZE,                /* Stack depth in units of StackType_t typically uint32_t on 32b CPUs */
                                  NULL,                     /* Not using the task parameter. */
                                  TASK_PRI_MAIN_THREAD,     /* task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest */
                                  gMainTaskStack,           /* pointer to stack base */
                                  &gMainTaskObj );          /* pointer to statically allocated task object memory */
    configASSERT(gMainTask != NULL);

    gBootTask = xTaskCreateStatic(sbl_ospi_stage2_main_thread,      /* Pointer to the function that implements the task. */
                                  "boot_thread",                    /* Text name for the task.  This is to facilitate debugging only. */
                                  TASK_SIZE,                        /* Stack depth in units of StackType_t typically uint32_t on 32b CPUs */
                                  NULL,                             /* Not using the task parameter. */
                                  TASK_PRI_BOOT_THREAD,             /* task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest */
                                  gBootTaskStack,                   /* pointer to stack base */
                                  &gBootTaskObj );                  /* pointer to statically allocated task object memory */
    configASSERT(gBootTask != NULL);

    Bootloader_profileAddProfilePoint("FreeRTOS Task Created");

    /* Start the scheduler to start the tasks executing. */
    vTaskStartScheduler();

    /*
     * The following line should never be reached because vTaskStartScheduler()
     * will only return if there was not enough FreeRTOS heap memory available to
     * create the Idle and (if configured) Timer tasks.  Heap management, and
     * techniques for trapping heap exhaustion, are described in the book text.
     */
    DebugP_assertNoLog(0);

    return 0;
}

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
#include <string.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/bootloader.h>
#include <drivers/device_manager/sciclient.h>
#include <drivers/device_manager/sciserver/sciserver_init.h>
#include "FreeRTOS.h"
#include "task.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BOOTLOADER_SD_APPIMAGE_FILENAME                  ("/sd0/lateapp")

#define BOOTLOADER_APP_IMAGE_LOADED                      (1U)
#define BOOTLOADER_SD_MAX_NO_OF_FILES                    (1U)

/*
 * AppImage size can be a maximum size of section DDR specified in linker.cmd,
 * leaving space for the other application components
 */
#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x800000)

/*
 * FreeRTOS Task Size and Priorities
 */
#define TASK_PRI_BOOT_THREAD    (1U)
#define TASK_PRI_MAIN_THREAD    (1U)
#define TASK_SIZE (16384U/sizeof(configSTACK_DEPTH_TYPE))

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

uint8_t gAppImage[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128), section(".application_image")));

uint8_t socCpuCores[CSL_CORE_ID_MAX] = {0U};

Bootloader_Handle bootHandle;
Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

char* gBootLoaderSDFiles[BOOTLOADER_SD_MAX_NO_OF_FILES] = {BOOTLOADER_SD_APPIMAGE_FILENAME};
char** pFiles = gBootLoaderSDFiles;

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
 * Call this API to stop the booting process and spin, so that you can connect
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1U;
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
            memset(gAppImage, 0x0, sizeof(gAppImage));
            ff_fread(gAppImage, fileSize, 1, appFp);
        }

        /* Close the file */
        ff_fclose(appFp);
    }

    return status;
}

int32_t App_loadImages(void)
{
    int32_t status = SystemP_FAILURE;

    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Config *bootConfig;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppImage;

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

    return status;
}

void sciserver_main_thread(void *args)
{
    /* Configure sciserver task parameters */
    Sciserver_TirtosCfgPrms_t sciserverCfg = {0};
    sciserverCfg.hiTaskStack    =   gUserHiTaskStack;
    sciserverCfg.loTaskStack    =   gUserLoTaskStack;
    sciserverCfg.taskStackSize  =   SCISERVER_TASK_STACK_SIZE;

    sciServer_init(&sciserverCfg);

    /* Close the open drivers */
    Drivers_close();

    /* Delete the task upon completion */
    vTaskDelete(NULL);
}

void sbl_sd_stage2_main_thread(void* args)
{
    int32_t status;
    uint8_t noOfFiles = 0U;

    if(App_OpenloadableImage(pFiles[noOfFiles]) == SystemP_SUCCESS)
    {
        status = App_loadImages();
    }
    else
    {
        status = SystemP_FAILURE;
    }

    Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandle));
    Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_SD, 0);

    if(SystemP_SUCCESS == status)
    {
        /* Print SBL log as Linux prints log to the same UART port */
        Bootloader_profilePrintProfileLog();
        DebugP_log("Image loading done, switching to application ...\r\n");
        DebugP_log("Starting applications from the other cores.\r\n");
        UART_flushTxFifo(gUartHandle[CONFIG_UART0]);

        status = App_runCpus();
    }

    Bootloader_close(bootHandle);

    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Some tests have failed!!\r\n");
        DebugP_assert(0);
    }
    else
    {
        /* Close the open drivers */
        Drivers_close();

        /* Call DPL deinit to close the tick timer and disable interrupts before jumping to DM*/
        Dpl_deinit();

        /* Deinitialize Drivers and Power clock disables in it. */
        System_deinit();
    }

    /* Delete this task upon completion */
    vTaskDelete(NULL);
}

int main()
{
    Bootloader_profileReset();

    /* Init SOC-specific modules */
    System_init();
    Bootloader_profileAddProfilePoint("System_init");

    /* Open drivers */
    Drivers_open();

    gMainTask = xTaskCreateStatic(sciserver_main_thread,            /* Pointer to the function that implements the task. */
                                  "sciserver_main_thread",          /* Text name for the task.  This is to facilitate debugging only. */
                                  TASK_SIZE,                        /* Stack depth in units of StackType_t typically uint32_t on 32b CPUs */
                                  NULL,                             /* Not using the task parameter. */
                                  TASK_PRI_MAIN_THREAD,             /* task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest */
                                  gMainTaskStack,                   /* Pointer to stack base */
                                  &gMainTaskObj );                  /* Pointer to statically allocated task object memory */
    configASSERT(gMainTask != NULL);

    gBootTask = xTaskCreateStatic(sbl_sd_stage2_main_thread,        /* Pointer to the function that implements the task. */
                                  "boot_thread",                    /* Text name for the task.  This is to facilitate debugging only. */
                                  TASK_SIZE,                        /* Stack depth in units of StackType_t typically uint32_t on 32b CPUs */
                                  NULL,                             /* Not using the task parameter. */
                                  TASK_PRI_BOOT_THREAD,             /* task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest */
                                  gBootTaskStack,                   /* Pointer to stack base */
                                  &gBootTaskObj );                  /* Pointer to statically allocated task object memory */

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
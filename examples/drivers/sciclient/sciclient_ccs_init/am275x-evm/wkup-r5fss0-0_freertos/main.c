/*
 *  Copyright (C) 2018-2025 Texas Instruments Incorporated
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
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include <drivers/device_manager/sciserver/sciserver_init.h>
#include <drivers/bootloader/soc/bootloader_soc.h>

#define TASK_PRI_MAIN_THREAD  (configMAX_PRIORITIES-1)


#define TASK_SIZE (16384U/sizeof(configSTACK_DEPTH_TYPE))

StackType_t gMainTaskStack[TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gMainTaskObj;
TaskHandle_t gMainTask;

extern int32_t sciclient_set_boardcfg(void);
extern int32_t sciclient_load_sysfw(void);
extern int32_t app_system_init(void);

void initializeCores(void);

void init_cpus(void)
{
    int32_t status = SystemP_SUCCESS;

    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);
    bootHandle = Bootloader_open(CONFIG_BOOTLOADER0, &bootParams);
    if(bootHandle != NULL)
        {
            if (!Bootloader_socIsMCUResetIsoEnabled())
            {
                status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_R5FSS0_0]);
            }
        }

        if(status == SystemP_SUCCESS)
        {
            status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_R5FSS0_1]);
        }

        if(status == SystemP_SUCCESS)
        {
            status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_R5FSS1_0]);
        }

        if(status == SystemP_SUCCESS)
        {
            status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_R5FSS1_1]);
        }

        if(status == SystemP_SUCCESS)
        {
            status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0]);
        }

        if(status == SystemP_SUCCESS)
        {
            status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS1_0]);
        }
        Bootloader_close(bootHandle);
}

void main_thread(void *args)
{
    int32_t status = SystemP_SUCCESS;

    /* Open drivers */
    Drivers_open();
    /* Open flash and board drivers */
    status = Board_driversOpen();
    DebugP_assert(status==SystemP_SUCCESS);

    sciServer_init();

    init_cpus();

    /* Close board and flash drivers */
    Board_driversClose();
    /* Close drivers */
    Drivers_close();

    vTaskDelete(NULL);
}

int main()
{
    int32_t status = SystemP_SUCCESS;

    status = sciclient_load_sysfw();
    DebugP_assert(status == SystemP_SUCCESS);

    Dpl_init();

    status = sciclient_set_boardcfg();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    status = Bootloader_socOpenFirewalls();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    /* init SOC specific modules */

    status = app_system_init();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    gMainTask = xTaskCreateStatic( main_thread,   /* Pointer to the function that implements the task. */
                                  "main_thread", /* Text name for the task.  This is to facilitate debugging only. */
                                  TASK_SIZE,  /* Stack depth in units of StackType_t typically uint32_t on 32b CPUs */
                                  NULL,            /* We are not using the task parameter. */
                                  TASK_PRI_MAIN_THREAD,   /* task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest */
                                  gMainTaskStack,  /* pointer to stack base */
                                  &gMainTaskObj ); /* pointer to statically allocated task object memory */
    configASSERT(gMainTask != NULL);

    /* Start the scheduler to start the tasks executing. */
    vTaskStartScheduler();

    /* The following line should never be reached because vTaskStartScheduler()
    will only return if there was not enough FreeRTOS heap memory available to
    create the Idle and (if configured) Timer tasks.  Heap management, and
    techniques for trapping heap exhaustion, are described in the book text. */
    DebugP_assertNoLog(0);

    return 0;
}

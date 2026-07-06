/*
 *  Copyright (C) 2024-2026 Texas Instruments Incorporated
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

#define TASK_PRI_MAIN_THREAD  (configMAX_PRIORITIES-1)

#define TASK_SIZE (16384U/sizeof(configSTACK_DEPTH_TYPE))

#define SCISERVER_TASK_STACK_SIZE       (2U*1024U)
#define SCISERVER_TASK_STACK_ALIGNMENT  (32)

StackType_t gMainTaskStack[TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gMainTaskObj;
TaskHandle_t gMainTask;

uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserHiTaskStack[SCISERVER_TASK_STACK_SIZE];
uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserLoTaskStack[SCISERVER_TASK_STACK_SIZE];

void test_main(void *args);

void main_thread(void *args)
{
    int32_t status = SystemP_SUCCESS;

    /* Open drivers */
    Drivers_open();
    /* Open flash and board drivers */
    status = Board_driversOpen();
    DebugP_assert(status==SystemP_SUCCESS);

    Sciserver_TirtosCfgPrms_t sciserverCfg = {0};
    sciserverCfg.hiTaskStack    = gUserHiTaskStack;
    sciserverCfg.loTaskStack    = gUserLoTaskStack;
    sciserverCfg.taskStackSize  = SCISERVER_TASK_STACK_SIZE;

    sciServer_init(&sciserverCfg);

    test_main(NULL);

    /* Close board and flash drivers */
    Board_driversClose();
    /* Close drivers */
    Drivers_close();

    vTaskDelete(NULL);
}


int main()
{
    int32_t status;
    Bootloader_profileReset();

#if !defined(SOC_AM62AX)
    /* LPM-exit IO isolation clearing is not yet ported to AM62AX
     * (Bootloader_socClrIOIsolationOnLPMExit does not exist for this SoC). */
    status = Bootloader_socClrIOIsolationOnLPMExit();
    DebugP_assertNoLog(status == SystemP_SUCCESS);
#endif

    status = Bootloader_socOpenFirewalls();

    DebugP_assertNoLog(status == SystemP_SUCCESS);

    /* init SOC specific modules */
    System_init();
    Board_init();

    gMainTask = xTaskCreateStatic( main_thread,
                                  "main_thread",
                                  TASK_SIZE,
                                  NULL,
                                  TASK_PRI_MAIN_THREAD,
                                  gMainTaskStack,
                                  &gMainTaskObj );
    configASSERT(gMainTask != NULL);

    vTaskStartScheduler();

    DebugP_assertNoLog(0);

    return 0;
}

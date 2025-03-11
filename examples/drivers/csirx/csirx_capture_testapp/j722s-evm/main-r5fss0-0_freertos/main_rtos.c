/*
 *  Copyright (c) 2018-2025 Texas Instruments Incorporated
 *  All rights reserved.
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

/**
 *  \file main_rtos.c
 *
 *  \brief Main file for RTOS builds
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <drivers/hw_include/csl_types.h>
/* BIOS Header files */
#include <kernel/dpl/TaskP.h>
#include <drivers/sciclient.h>
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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define CAPT_APP_TSK_STACK_MAIN         (10U * 1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern int Csirx_captureTest(void);
static void taskFxn(void* a0);
void App_wait(uint32_t wait_in_ms);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test application stack */
static uint8_t gCaptAppTskStackMain[CAPT_APP_TSK_STACK_MAIN];

/* Task handle */
TaskP_Object gCsirxAppTask;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    TaskP_Params taskParams;
    /* init SOC specific modules */
    System_init();
    Board_init();

    /* Initialize the task params */
    TaskP_Params_init(&taskParams);
    /* Set the task priority higher than the default priority (1) */
    taskParams.priority = 2;
    taskParams.stack = gCaptAppTskStackMain;
    taskParams.taskMain = taskFxn;
    taskParams.stackSize = sizeof(gCaptAppTskStackMain);

    TaskP_construct(&gCsirxAppTask, &taskParams);
    vTaskStartScheduler();

    return(0);
}

void taskFxn(void* a0)
{
    int32_t retVal = CSL_PASS;

    Drivers_open();

    retVal += Sciclient_pmSetModuleState(TISCI_DEV_CSI_RX_IF0,
                                         TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                         TISCI_MSG_FLAG_AOP,
                                         SystemP_WAIT_FOREVER);
    retVal += Sciclient_pmSetModuleState(TISCI_DEV_CSI_RX_IF0,
                                         TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                         TISCI_MSG_FLAG_AOP,
                                         SystemP_WAIT_FOREVER);
    retVal += Sciclient_pmSetModuleState(TISCI_DEV_CSI_RX_IF1,
                                         TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                         TISCI_MSG_FLAG_AOP,
                                         SystemP_WAIT_FOREVER);
    retVal += Sciclient_pmSetModuleState(TISCI_DEV_DPHY_RX0,
                                         TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                         TISCI_MSG_FLAG_AOP,
                                         SystemP_WAIT_FOREVER);
    retVal += Sciclient_pmSetModuleState(TISCI_DEV_DPHY_RX1,
                                         TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                         TISCI_MSG_FLAG_AOP,
                                         SystemP_WAIT_FOREVER);

    if (retVal == CSL_PASS)
    {
        Csirx_captureTest();
    }

    return;
}

void App_wait(uint32_t wait_in_ms)
{
    ClockP_usleep(wait_in_ms*1000);
}

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

/**
 *  \file main_rtos.c
 *
 *  \brief Main file for RTOS builds
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
 #include <stdlib.h>
 #include <kernel/dpl/TaskP.h>
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

StackType_t gMainTaskStack[TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gMainTaskObj;
TaskHandle_t gMainTask;
DM_LPMData_t gDMLPMData __attribute__((section(".lpm_data"), aligned(4)));

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
extern int Csirx_fusion2Test(void);
static void taskFxn(void* a0);
extern void Drivers_open(void);
void App_wait(uint32_t wait_in_ms);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* Test application stack */
static uint8_t gCaptAppTskStackMain[TASK_SIZE];
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

    return 0;
}

void loop_forever()
{
    volatile uint32_t loop = 1;
    while(loop)
    ;
}

void taskFxn(void* a0)
{
    // loop_forever();
    int32_t retVal = 0;
    //Drivers_uartOpen();
    Drivers_open();

    retVal = Sciclient_pmSetModuleState(TISCI_DEV_CSI_RX_IF0,
                                    TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                    TISCI_MSG_FLAG_AOP,
                                    SCICLIENT_SERVICE_WAIT_FOREVER);

    retVal |= Sciclient_pmSetModuleState(TISCI_DEV_DPHY_RX0,
                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                TISCI_MSG_FLAG_AOP,
                                SCICLIENT_SERVICE_WAIT_FOREVER);

    retVal |= Sciclient_pmSetModuleState(TISCI_DEV_DMASS0,
                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                TISCI_MSG_FLAG_AOP,
                                SCICLIENT_SERVICE_WAIT_FOREVER);

    retVal |= Sciclient_pmSetModuleState(TISCI_DEV_DMASS0_BCDMA_0,
                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                TISCI_MSG_FLAG_AOP,
                                SCICLIENT_SERVICE_WAIT_FOREVER);

    retVal |= Sciclient_pmSetModuleState(TISCI_DEV_DMASS0_RINGACC_0,
                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                TISCI_MSG_FLAG_AOP,
                                SCICLIENT_SERVICE_WAIT_FOREVER);

    retVal |= Sciclient_pmSetModuleState(TISCI_DEV_DMASS0_INTAGGR_0,
                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                TISCI_MSG_FLAG_AOP,
                                SCICLIENT_SERVICE_WAIT_FOREVER);

    retVal |= Sciclient_pmSetModuleState(TISCI_DEV_DMASS1,
                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                TISCI_MSG_FLAG_AOP,
                                SCICLIENT_SERVICE_WAIT_FOREVER);

    retVal |= Sciclient_pmSetModuleState(TISCI_DEV_DMASS1_BCDMA_0,
                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                TISCI_MSG_FLAG_AOP,
                                SCICLIENT_SERVICE_WAIT_FOREVER);

    retVal |= Sciclient_pmSetModuleState(TISCI_DEV_DMASS1_INTAGGR_0,
                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                TISCI_MSG_FLAG_AOP,
                                SCICLIENT_SERVICE_WAIT_FOREVER);

    DebugP_logInfo("Starting AM62A DM R5F CSIRX Fusion 2 Test \r\n");

    if (retVal == 0)
    {
        DebugP_log("Csirx Fusion 2 Setup Passed!!!\r\n");
    }
    else
    {
        DebugP_log("Csirx Fusion 2 Setup Failed!!!\r\n");
    }

    /* CSIRx Fusion 2 Test */
    retVal |= Csirx_fusion2Test();

    if (retVal == 0)
    {
        DebugP_log("Csirx Fusion 2 Test Passed!!!\r\n");
    }
    else
    {
        DebugP_log("Csirx Fusion 2 Test Failed!!!\r\n");
    }

    while(1)
    {
        __asm("wfi");
    }

    return;
}

void App_wait(uint32_t wait_in_ms)
{
    ClockP_usleep(wait_in_ms*1000);
}

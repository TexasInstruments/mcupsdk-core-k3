/*
 *  Copyright (c) Texas Instruments Incorporated 2019-25
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
 *  \brief Main file for TI-RTOS build
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <drivers/hw_include/csl_types.h>
/* BIOS Header files */
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
#include "csirx_test.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define APP_TSK_STACK_MAIN              (20U * 1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void taskFxn(void * a0);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test application stack */
static uint8_t  gAppTskStackMain[APP_TSK_STACK_MAIN] __attribute__((aligned(32)));;
/*
 * UDMA driver objects
 */
Udma_DrvObject gUdmaDrvObj;

/** \brief Log enable for CSIRX Unit Test  application */
uint32_t gAppTrace = ((uint32_t) GT_INFO   |\
                      (uint32_t) GT_TraceState_Enable);

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
    taskParams.priority     = 2;
    taskParams.stack        = gAppTskStackMain;
    taskParams.taskMain     = taskFxn;
    taskParams.stackSize    = sizeof (gAppTskStackMain);

    TaskP_construct(&gCsirxAppTask, &taskParams);
    vTaskStartScheduler();

    return(0);
}

static void taskFxn(void * a0)
{
    int32_t                  dmaStatus = UDMA_SOK;
    int32_t                  testPassed = FVID2_SOK, retVal = FVID2_SOK;
    Fvid2_InitPrms           fvid2InitPrms;
    uint32_t                 instId;
    Udma_InitPrms            udmaInitPrms;
    Udma_DrvHandle           drvHandle = &gUdmaDrvObj;


    if (FVID2_SOK == retVal)
    {

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

    }
    Drivers_open();
    if (FVID2_SOK == retVal)
    {
        Fvid2InitPrms_init(&fvid2InitPrms);
        fvid2InitPrms.printFxn = &App_fvidPrint;
        Fvid2_init(&fvid2InitPrms);

        /* UDMA driver init */
        instId = UDMA_INST_ID_BCDMA_1;
        UdmaInitPrms_init(instId, &udmaInitPrms);
        dmaStatus = Udma_init(drvHandle, &udmaInitPrms);
        if(UDMA_SOK != dmaStatus)
        {
            testPassed = FVID2_EFAIL;
            GT_0trace(gAppTrace,
                      GT_ERR,
                      APP_NAME ": UDMA Init Failed!!!\r\n");
        }

        if (FVID2_SOK == testPassed)
        {
            testPassed = csirxTestParser();
        }

        if (FVID2_SOK != testPassed)
        {
            GT_0trace(gAppTrace, GT_INFO1, " CSIRX Unit Test Failed!!!\n");
        }

        dmaStatus = Udma_deinit(drvHandle);
        if(UDMA_SOK != dmaStatus)
        {
            testPassed = FVID2_EFAIL;
            GT_0trace(gAppTrace,
                      GT_ERR,
                      APP_NAME ": UDMA De-init Failed!!!\r\n");
        }
        Fvid2_deInit(NULL);
    }
    return;
}


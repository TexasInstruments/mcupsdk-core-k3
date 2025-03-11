/*
 *  Copyright (c) Texas Instruments Incorporated 2024-25
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
#include "csitx_transmit_test_cfg.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define TX_APP_TSK_STACK_MAIN         (16U * 1024U)

#define CSITX_ESC_CLK_FREQ_HZ         (16000000U)
#define CSITX_MAIN_CLK_HZ             (500000000U)

#define CSITX_PSIL_MOD                          TISCI_DEV_CSI_PSILSS0

#define CSITX_MOD                               TISCI_DEV_CSI_TX_IF0
#define CSITX_DPHY_MOD                          TISCI_DEV_DPHY_TX0
#define CSITX_MOD_ESC_CLK                       TISCI_DEV_CSI_TX_IF0_ESC_CLK_CLK
#define CSITX_MOD_MAIN_CLK                      TISCI_DEV_CSI_TX_IF0_MAIN_CLK_CLK
#define CSITX_MOD_DPHY_TXBYTECLKHS_CLK          TISCI_DEV_CSI_TX_IF0_DPHY_TXBYTECLKHS_CL_CLK
#define CSITX_MOD_VBUS_CLK                      TISCI_DEV_CSI_TX_IF0_VBUS_CLK_CLK

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void taskFxn(void* a0);
static void App_clkRateSet(uint32_t moduleId,
                           uint32_t clkId,
                           uint64_t clkRateHz);
extern int32_t Csitx_transmitTest(void);
extern void App_consolePrintf(const char *pcString, ...);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test application stack */
static uint8_t gTxAppTskStackMain[TX_APP_TSK_STACK_MAIN]__attribute__((aligned(TX_APP_TSK_STACK_MAIN)));
/* Task handle */
TaskP_Object gCsitxAppTask;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    TaskP_Params taskParams;

    /* init SOC specific modules */
    System_init();
    Board_init();
    Drivers_open();

    /* Initialize the task params */
    TaskP_Params_init(&taskParams);
    /* Set the task priority higher than the default priority (1) */
    taskParams.priority = 2;
    taskParams.stack = gTxAppTskStackMain;
    taskParams.stackSize = sizeof(gTxAppTskStackMain);
    taskParams.taskMain = taskFxn;

    TaskP_construct(&gCsitxAppTask, &taskParams);

    vTaskStartScheduler();    /* does not return */

    return(0);
}

void taskFxn(void* a0)
{
    int32_t retVal = CSL_PASS;
    uint64_t clkFreq = 0U;


    retVal += Sciclient_pmSetModuleState(CSITX_MOD,
                               TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                               TISCI_MSG_FLAG_AOP,
                               SystemP_WAIT_FOREVER);
    retVal += Sciclient_pmSetModuleState(CSITX_DPHY_MOD,
                               TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                               TISCI_MSG_FLAG_AOP,
                               SystemP_WAIT_FOREVER);

    /* set CSITX clocks */
    App_clkRateSet(CSITX_MOD,
                   CSITX_MOD_ESC_CLK,
                   CSITX_ESC_CLK_FREQ_HZ);
    App_clkRateSet(CSITX_MOD,
                   CSITX_MOD_MAIN_CLK,
                   CSITX_MAIN_CLK_HZ);

   if (retVal == CSL_PASS)
    {
        /* Get the CSITX clock frequencies */
        retVal += Sciclient_pmGetModuleClkFreq(CSITX_MOD,
                                  CSITX_MOD_ESC_CLK,
                                  &clkFreq, SystemP_WAIT_FOREVER);
        App_consolePrintf("\nClock Freq: CSITX_MOD_ESC_CLK = %lldHz", clkFreq);
        retVal += Sciclient_pmGetModuleClkFreq(CSITX_MOD,
                                  CSITX_MOD_DPHY_TXBYTECLKHS_CLK,
                                  &clkFreq, SystemP_WAIT_FOREVER);
        App_consolePrintf("\nClock Freq: CSITX_MOD_DPHY_TXBYTECLKHS_CLK = %lldHz", clkFreq);
        retVal += Sciclient_pmGetModuleClkFreq(CSITX_MOD,
                                  CSITX_MOD_VBUS_CLK,
                                  &clkFreq, SystemP_WAIT_FOREVER);
        App_consolePrintf("\nClock Freq: CSITX_MOD_VBUS_CLK = %lldHz", clkFreq);
        retVal += Sciclient_pmGetModuleClkFreq(CSITX_MOD,
                                  CSITX_MOD_MAIN_CLK,
                                  &clkFreq, SystemP_WAIT_FOREVER);
        App_consolePrintf("\nClock Freq: CSITX_MOD_MAIN_CLK = %lldHz\n", clkFreq);
        Csitx_transmitTest();
    }


    return;
}

static void App_clkRateSet(uint32_t moduleId,
                           uint32_t clkId,
                           uint64_t clkRateHz)
{
    int32_t status;
    uint64_t currClkFreqHz;

    status = Sciclient_pmGetModuleClkFreq(moduleId, clkId, &currClkFreqHz, SystemP_WAIT_FOREVER);
    if ((status == CSL_PASS) &&
        (currClkFreqHz != clkRateHz))
    {
        status = Sciclient_pmSetModuleClkFreq(moduleId, clkId, clkRateHz,TISCI_MSG_FLAG_AOP,SystemP_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            App_consolePrintf("\nsciclient_pmSetModuleClkFreq Passed for clock Id = %d\n", clkId);
        }
        else
        {
            App_consolePrintf("\nsciclient_pmSetModuleClkFreq failed for clock Id = %d\n", clkId);
        }
    }
}

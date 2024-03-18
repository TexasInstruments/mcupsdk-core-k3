/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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
  *  \file    safety_app.c
  *
  *  \brief   This file contains safety checkers app code demonstrating
  *           the use of PM, RM and TIFS checker APIs.
  *
  */

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/TimerP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/ClockP.h>
#include <safety_checkers_common.h>
#include <safety_checkers_pm.h>
#include <safety_checkers_tifs.h>
#include "safety_app_fwl_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SAFETY_APP_RM_CHECKERS_REG_BLOB_SIZE    25000U
#define SAFETY_LOOP_TASK_PRI                    (configMAX_PRIORITIES-1)
#define SAFETY_LOOP_STACK_SIZE                  (4*1024U)
#define SAFETY_LOOP_NUM_ITERATIONS              (10U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uintptr_t    pscRegisterData[SAFETY_CHECKERS_PM_PSC_REGDUMP_SIZE];
uintptr_t    pllRegisterData[SAFETY_CHECKERS_PM_PLL_REGDUMP_SIZE];
uintptr_t    rmRegisterData[SAFETY_APP_RM_CHECKERS_REG_BLOB_SIZE];

SafetyCheckers_TifsFwlConfig *pFwlConfig = gSafetyApp_TifsFwlConfig;
uint32_t gSafetyCheckersTifsCfgSize = TIFS_CHECKER_FWL_MAX_NUM;

uint8_t gSafetyLoopTaskStack[SAFETY_LOOP_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gSafetyLoopTask;

static SemaphoreP_Object gBinarySemTaskSync;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void SafetyApp_safetyLoop(void *args);

static void SafetyApp_clockCbFxn(ClockP_Object *obj, void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SafetyApp_main(void *args)
{
    uint32_t  status = SystemP_SUCCESS;

    /* Creating a binary semaphore to sync the main task and safety loop*/
    status = SemaphoreP_constructBinary(&gBinarySemTaskSync, 0);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Binary semaphore object creation failed!!");
        return;
    }

    /* Get PM Checkers Register Configuration */
    status = SafetyCheckers_pmGetPscRegCfg(pscRegisterData, SAFETY_CHECKERS_PM_PSC_REGDUMP_SIZE);
    if (status == SystemP_SUCCESS)
    {
        DebugP_log("Get PSC configuration successful.\r\n");
    }
    else
    {
        DebugP_log("Get PSC configuration unsuccessful.\r\n");
    }

    status = SafetyCheckers_pmGetPllRegCfg(pllRegisterData, SAFETY_CHECKERS_PM_PLL_REGDUMP_SIZE);
    if (status == SystemP_SUCCESS)
    {
        DebugP_log("Get PLL configuration successful.\r\n");
    }
    else
    {
        DebugP_log("Get PLL configuration unsuccessful.\r\n");
    }

    /* Get RM Checkers Register Configuration */
    status = SafetyCheckers_rmGetRegCfg(rmRegisterData, SAFETY_APP_RM_CHECKERS_REG_BLOB_SIZE);
    if (status == SystemP_SUCCESS)
    {
        DebugP_log("Get RM configuration successful.\r\n");
    }
    else
    {
        DebugP_log("Get RM configuration unsuccessful.\r\n");
    }

    /* Request TIFS firewall open */
    status = SafetyCheckers_tifsReqFwlOpen();
    if (status == SystemP_SUCCESS)
    {
        DebugP_log("Firewall open successful.\r\n");
    }
    else
    {
        DebugP_log("Firewall open unsuccessful.\r\n");
    }

    /* Get TIFS Checkers Register Configuration */
    status = SafetyCheckers_tifsGetFwlCfg(pFwlConfig, gSafetyCheckersTifsCfgSize);
    if (status == SystemP_SUCCESS)
    {
        DebugP_log("Get firewall configuration successful.\r\n");
    }
    else
    {
        DebugP_log("Get firewall configuration unsuccessful.\r\n");
    }

    /* Place to verify and save firewall configuration as golden reference */

    /* Creating safety loop thread */
    TaskP_Params SafetyLoopTaskParams;

    TaskP_Params_init(&SafetyLoopTaskParams);
    SafetyLoopTaskParams.name = "SAFETY_LOOP";
    SafetyLoopTaskParams.stackSize = SAFETY_LOOP_STACK_SIZE;
    SafetyLoopTaskParams.stack = gSafetyLoopTaskStack;
    SafetyLoopTaskParams.priority = SAFETY_LOOP_TASK_PRI;

    SafetyLoopTaskParams.taskMain = SafetyApp_safetyLoop;

    status = TaskP_construct(&gSafetyLoopTask, &SafetyLoopTaskParams);

    if (status == SystemP_FAILURE)
    {
        DebugP_log("Safety loop task creation failed!!\r\n");
        TaskP_destruct(&gSafetyLoopTask);
        SemaphoreP_post(&gBinarySemTaskSync);
    }

    /* Semaphore pend to see if safety loop has finished execution */
    SemaphoreP_pend(&gBinarySemTaskSync, SystemP_WAIT_FOREVER);
    SemaphoreP_destruct(&gBinarySemTaskSync);
}

void SafetyApp_safetyLoop(void *args)
{
    uint32_t  status = SystemP_SUCCESS, numIter = SAFETY_LOOP_NUM_ITERATIONS;
    uint32_t  mismatch = 0U;
    ClockP_Object clockObj;
    ClockP_Params clockParams;
    SemaphoreP_Object binarySemFromCbFxn;

    status = SemaphoreP_constructBinary(&binarySemFromCbFxn, 0);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Binary semaphore object creation failed!!");
        status = SystemP_FAILURE;
    }

    /* Creating timer for safety loop thread timeout */
    if(status == SystemP_SUCCESS)
    {
        ClockP_Params_init(&clockParams);
        clockParams.timeout = 5000;
        clockParams.period = 5000;
        clockParams.start = 1;
        clockParams.callback = SafetyApp_clockCbFxn;
        clockParams.args = &binarySemFromCbFxn;

        status = ClockP_construct(&clockObj, &clockParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("Clock object creation failed!!");
            status = SystemP_FAILURE;
        }

        if(status == SystemP_SUCCESS)
        {
            DebugP_log("Verifying registers against golden reference...\r\n");

            while(numIter > 0)
            {
                status = SemaphoreP_pend(&binarySemFromCbFxn, SystemP_WAIT_FOREVER);

                if(status == SystemP_SUCCESS)
                {
                    /* Verify PM Checkers Register Configuration */
                    status = SafetyCheckers_pmVerifyPscRegCfg(pscRegisterData, SAFETY_CHECKERS_PM_PSC_REGDUMP_SIZE);
                    if (status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
                    {
                        DebugP_log("PSC register mismatch with golden reference.\r\n");
                        mismatch++;
                    }

                    status = SafetyCheckers_pmGetPllRegCfg(pllRegisterData, SAFETY_CHECKERS_PM_PLL_REGDUMP_SIZE);
                    if (status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
                    {
                        DebugP_log("PLL register mismatch with golden reference.\r\n");
                        mismatch++;
                    }

                    status = SafetyCheckers_pmRegisterLock();
                    if (status == SAFETY_CHECKERS_FAIL)
                    {
                        DebugP_log("PM register lock failed.\r\n");
                        mismatch++;
                    }

                    /* Verify RM Checkers Register Configuration */
                    status = SafetyCheckers_rmVerifyRegCfg(rmRegisterData, SAFETY_APP_RM_CHECKERS_REG_BLOB_SIZE);
                    if (status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
                    {
                        DebugP_log("RM register mismatch with golden reference.\r\n");
                        mismatch++;
                    }

                    /* Verify TIFS Checkers Register Configuration */
                    status = SafetyCheckers_tifsVerifyFwlCfg(pFwlConfig, gSafetyCheckersTifsCfgSize);
                    if (status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
                    {
                        DebugP_log("Firewall register mismatch with golden reference.\r\n");
                        mismatch++;
                    }

                    numIter--;
                }
            }

            if (mismatch == 0U)
            {
                DebugP_log("No register mismatch with golden reference.\r\n");
            }
        }
    }

    /* Request TIFS firewall close */
    status = SafetyCheckers_tifsReqFwlClose();
    if (status == SystemP_SUCCESS)
    {
        DebugP_log("Firewall close successful.\r\n");
    }
    else
    {
        DebugP_log("Firewall close unsuccessful.\r\n");
    }

    ClockP_destruct(&clockObj);
    SemaphoreP_destruct(&binarySemFromCbFxn);
    SemaphoreP_post(&gBinarySemTaskSync);
    TaskP_exit();
}

static void SafetyApp_clockCbFxn(ClockP_Object *obj, void *args)
{
    if (args != NULL)
    {
        SemaphoreP_Object *pSemObj = (SemaphoreP_Object *)args;
        SemaphoreP_post(pSemObj);
    }
}


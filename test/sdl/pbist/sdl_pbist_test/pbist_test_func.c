/*
 *  Copyright (C) 2023-2024 Texas Instruments Incorporated
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
 *  \file     sdl_pbist_test_func.c
 *
 *  \brief    This file contains PBIST Functional test code.
 *
 *  \details  PBIST Functional tests
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_pbist.h>
#include <sdl/pbist/sdl_pbist_priv.h>
#include <drivers/sciclient.h>

/* DPL API header files */

#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>

#include <pbist_test_cfg.h>

#include "power_seq.h"

/* This is to power up the cores before test and power down afterwards */
#define POWERUP_CORES_BEFORE_TEST

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_PBIST_TIMEOUT   (0x400000U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


int32_t PBIST_runTest(uint32_t instanceId, bool runNegTest)
{
    int32_t testResult = 0;
    SDL_ErrType_t status;
    bool PBISTResult;
    SDL_PBIST_testType testType;

    uint64_t startTime , testStartTime,  testEndTime, endTime;
    uint64_t prepTime, diffTime, restoreTime;
    int i;
#ifdef DEBUG
    char inputChar;
#endif
#ifdef PBIST_POST_CORE_MAX
    uint8_t  postStatus = SDL_PBIST_POST_COMPLETED_SUCCESS;
#endif
    uint32_t moduleState = TISCI_MSG_VALUE_DEVICE_HW_STATE_OFF;
    uint32_t resetState = 0U;
    uint32_t contextLossState = 0U;

    if (runNegTest == true)
    {
        DebugP_log("\r\n Starting PBIST failure insertion test on %s, index %d...\r\n",
                    PBIST_TestHandleArray[instanceId].testName,
                    instanceId);
        testType = SDL_PBIST_NEG_TEST;
    }
    else
    {
        DebugP_log("\r\n Starting PBIST test on %s, index %d...\r\n",
                    PBIST_TestHandleArray[instanceId].testName,
                    instanceId);
        testType = SDL_PBIST_TEST;
    }

#ifdef DEBUG
    DebugP_log("\r\n Press any key to continue...");
    inputChar = UART_getChar();

    if (inputChar == 'n')
    {
        DebugP_log("\r\n Skipping this test. on request \r\n");
        return 0;
    }
#endif

    /* Get start time of test */
    startTime = ClockP_getTimeUsec();
#ifdef PBIST_POST_CORE_MAX

    if ((testResult == 0) &&
        (PBIST_TestHandleArray[instanceId].numPostPbistToCheck > 0))
    {
        if (runNegTest == 0u)
        {
#ifdef DEBUG
            DebugP_log("  HW POST: Running test on HW POST, %d Instances \n",
                        PBIST_TestHandleArray[instanceId].numPostPbistToCheck);
#endif
            SDL_PBIST_postResult result;

            status = SDL_PBIST_getPOSTStatus(&result);

            if (status != SDL_PASS)
            {
                testResult = -1;
                DebugP_log("SDL_PBIST_getPOSTStatus failed: Status %d \n", status);
            }
            else
            {
                PBIST_printPostStatus(&result);
            }
        }
    }
#endif  /* PBIST_POST_CORE_MAX */

    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded))
    {
        if (PBIST_TestHandleArray[instanceId].tisciProcId != 0u)
        {
#ifdef DEBUG
            DebugP_log("  Primary core: %s: Requesting processor \r\n",
                        PBIST_TestHandleArray[instanceId].coreName);
#endif
            /* Request Primary core */
            status = Sciclient_procBootRequestProcessor(PBIST_TestHandleArray[instanceId].tisciProcId,
                                                        SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Primary core: Sciclient_procBootRequestProcessor, ProcId 0x%x...FAILED \r\n",
                            PBIST_TestHandleArray[instanceId].tisciProcId);
                testResult = -1;
            }
        }
    }
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded))
    {
        if ((PBIST_TestHandleArray[instanceId].secondaryCoreNeeded)
            && (PBIST_TestHandleArray[instanceId].tisciSecProcId != 0u))
        {

#ifdef DEBUG
            DebugP_log("  Secondary core: %s: Requesting processor \r\n",
                    PBIST_TestHandleArray[instanceId].secCoreName);
#endif
            /* Request secondary core */
            status = Sciclient_procBootRequestProcessor(PBIST_TestHandleArray[instanceId].tisciSecProcId,
                                                        SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Secondary core: Sciclient_procBootRequestProcessor, ProcId 0x%x...FAILED \r\n",
                            PBIST_TestHandleArray[instanceId].tisciSecProcId);
                testResult = -1;
            }
        }
    }
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded))
    {
        if (PBIST_TestHandleArray[instanceId].tisciDeviceId != 0u)
        {
            /* Set Local reset for Primary core */
#ifdef DEBUG
            DebugP_log("  %s: Primary core: Set module reset \r\n",
                        PBIST_TestHandleArray[instanceId].coreName);
#endif
            status =  Sciclient_pmSetModuleRst(PBIST_TestHandleArray[instanceId].tisciDeviceId,
                                               0x1, /* Local Reset asserted */
                                               SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Primary core: Sciclient_pmSetModuleRst...FAILED \r\n");
                testResult = -1;
            }
        }
    }
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded))
    {
        if ((PBIST_TestHandleArray[instanceId].secondaryCoreNeeded)
            && (PBIST_TestHandleArray[instanceId].tisciSecDeviceId != 0u))
        {
            /* Set Local reset for Secondary core */
#ifdef DEBUG
            DebugP_log("  %s: Secondary core: Set Module reset \r\n",
                        PBIST_TestHandleArray[instanceId].secCoreName);
#endif
            status =  Sciclient_pmSetModuleRst(PBIST_TestHandleArray[instanceId].tisciSecDeviceId,
                                               0x1, /* Local Reset asserted */
                                               SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Secondary core: Sciclient_pmSetModuleRst...FAILED \r\n");
                testResult = -1;
            }
        }
    }
#ifdef POWERUP_CORES_BEFORE_TEST
    /* Custom core power restore sequence - needed to allow core to be powered
     * up later by Secondary Bootloader (SBL) */
    if ((testResult == 0) &&
        (PBIST_TestHandleArray[instanceId].coreCustPwrSeqNeeded) &&
        (PBIST_TestHandleArray[instanceId].tisciProcId != 0u))
    {
        status = customPrepareForPowerUpSequence(PBIST_TestHandleArray[instanceId].tisciProcId);
        if (status != SDL_PASS)
        {
            DebugP_log("  Custom core power restore sequence, ProcId 0x%x ...FAILED \r\n",
                        PBIST_TestHandleArray[instanceId].tisciProcId);
            testResult = -1;
        }
    }
    /* Power up of Auxilliary modules needed to run test */
    if (testResult == 0)
    {
        /* Power all modules required for test */
        for ( i = 0; i < PBIST_TestHandleArray[instanceId].numAuxDevices; i++)
        {
#ifdef DEBUG
            DebugP_log("  Powering on Device number %d Device Id %x\r\n",
                        i, PBIST_TestHandleArray[instanceId].auxDeviceIdsP[i]);
#endif

            status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].auxDeviceIdsP[i],
                                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                                TISCI_MSG_FLAG_AOP,
                                                SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("  Sciclient_pmSetModuleState 0x%x ...FAILED \r\n",
                            PBIST_TestHandleArray[instanceId].auxDeviceIdsP[i]);
                testResult = -1;
                break;
            }
        }
    }
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded)
                          && (PBIST_TestHandleArray[instanceId].tisciDeviceId != 0U))
    {
        /* power on Primary core*/
#ifdef DEBUG
        DebugP_log("  Primary core: Powering on %s \r\n",
                    PBIST_TestHandleArray[instanceId].coreName);
#endif
        status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].tisciDeviceId,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            TISCI_MSG_FLAG_AOP,
                                            SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("   Primary core: Sciclient_pmSetModuleState 0x%x ...FAILED \r\n",
                        PBIST_TestHandleArray[instanceId].tisciDeviceId);
            testResult = -1;
        }
    }
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded)
                          && (PBIST_TestHandleArray[instanceId].tisciSecDeviceId != 0U))
    {
        if (PBIST_TestHandleArray[instanceId].secondaryCoreNeeded)
        {
            /* power on Secondary core*/
#ifdef DEBUG
            DebugP_log("  Secondary core: Powering on %s \r\n",
                        PBIST_TestHandleArray[instanceId].secCoreName);
#endif
            status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].tisciSecDeviceId,
                                                TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                                TISCI_MSG_FLAG_AOP,
                                                SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Secondary core: Sciclient_pmSetModuleState 0x%x ...FAILED \r\n",
                            PBIST_TestHandleArray[instanceId].tisciSecDeviceId);
                testResult = -1;
                return testResult;
            }
        }
    }
#endif /* #ifdef POWERUP_CORES_BEFORE_TEST */
    /* Double check the Power up of Auxilliary modules needed to run test and wait until they
     * are powered up */
    if (testResult == 0)
    {
        /* Wait for all modules required for test to be powered up */
        for ( i = 0; i < PBIST_TestHandleArray[instanceId].numAuxDevices; i++)
        {
#ifdef DEBUG
        DebugP_log(
                        "  Double checking Powering on Device number %d Device Id %x\r\n",
                        i, PBIST_TestHandleArray[instanceId].auxDeviceIdsP[i]);
#endif
            do
            {
                status = Sciclient_pmGetModuleState(PBIST_TestHandleArray[instanceId].auxDeviceIdsP[i],
                                                    &moduleState,
                                                    &resetState,
                                                    &contextLossState,
                                                    SystemP_WAIT_FOREVER);
                if (status != SDL_PASS)
                {
                    DebugP_log("  Sciclient_pmGetModuleState 0x%x ...FAILED \r\n",
                                PBIST_TestHandleArray[instanceId].auxDeviceIdsP[i]);
                    testResult = -1;
                    break;
                }
            } while (moduleState != TISCI_MSG_VALUE_DEVICE_HW_STATE_ON);
        }
    }
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded)
                          && (PBIST_TestHandleArray[instanceId].tisciDeviceId != 0U))
    {
        /* Double check power on Primary core*/
#ifdef DEBUG
        DebugP_log(
                        "  Primary core: Double checking Powering on %s \r\n",
                        PBIST_TestHandleArray[instanceId].coreName);
#endif
        do
        {
            status = Sciclient_pmGetModuleState(PBIST_TestHandleArray[instanceId].tisciDeviceId,
                                                &moduleState,
                                                &resetState,
                                                &contextLossState,
                                                SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Primary core: Sciclient_pmGetModuleState 0x%x ...FAILED \r\n",
                            PBIST_TestHandleArray[instanceId].tisciDeviceId);
                testResult = -1;
                break;
            }
        } while (moduleState != TISCI_MSG_VALUE_DEVICE_HW_STATE_ON);
    }
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded)
                          && (PBIST_TestHandleArray[instanceId].tisciSecDeviceId != 0U))
    {
        if (PBIST_TestHandleArray[instanceId].secondaryCoreNeeded)
        {
            /* Double check power on Secondary core*/
#ifdef DEBUG
            DebugP_log(
                            "  Secondary core: Double checking Powering on %s \r\n",
                            PBIST_TestHandleArray[instanceId].coreName);
#endif
            do
            {
                status = Sciclient_pmGetModuleState(PBIST_TestHandleArray[instanceId].tisciSecDeviceId,
                                                    &moduleState,
                                                    &resetState,
                                                    &contextLossState,
                                                    SystemP_WAIT_FOREVER);
                if (status != SDL_PASS)
                {
                    DebugP_log("   Secondary core: Sciclient_pmGetModuleState 0x%x ...FAILED \r\n",
                                PBIST_TestHandleArray[instanceId].tisciSecDeviceId);
                    testResult = -1;
                    break;
                }
            } while (moduleState != TISCI_MSG_VALUE_DEVICE_HW_STATE_ON);
        }
    }
    /* Power up PBIST */
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].tisciPBISTDeviceId != 0u))
    {
#ifdef DEBUG
        DebugP_log("  Powering on PBIST %d \r\n",
                    PBIST_TestHandleArray[instanceId].tisciPBISTDeviceId);
#endif
        status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].tisciPBISTDeviceId,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            TISCI_MSG_FLAG_AOP,
                                            SystemP_WAIT_FOREVER);

        if (status != SDL_PASS)
        {
            DebugP_log("   PBIST Sciclient_pmSetModuleState 0x%x ...FAILED: retValue %d\r\n",
                        PBIST_TestHandleArray[instanceId].tisciPBISTDeviceId, status);
            testResult = -1;
        }
    }

    /* Execute Auxilliary init function */
    if (testResult == 0)
    {

        if (PBIST_TestHandleArray[instanceId].auxInitRestoreFunction != 0)
        {
            status = PBIST_TestHandleArray[instanceId].auxInitRestoreFunction(TRUE);
            if (status != SDL_PASS)
            {
                testResult = -1;
            }
        }
    }

    if (testResult == 0)
    {
        /* Get start time for PBIST test */
        testStartTime = ClockP_getTimeUsec();
        status = SDL_PBIST_selfTest((SDL_PBIST_inst)PBIST_TestHandleArray[instanceId].pbistInst, testType, APP_PBIST_TIMEOUT, &PBISTResult);
        if ((status != SDL_PASS) || (PBISTResult == false))
        {
            testResult = -1;
        }
    }

    /* Record test end time */
    testEndTime = ClockP_getTimeUsec();
    /* Execute Auxilliary restore function */
    if (testResult == 0)
    {
        if (PBIST_TestHandleArray[instanceId].auxInitRestoreFunction != 0)
        {
            status = PBIST_TestHandleArray[instanceId].auxInitRestoreFunction(FALSE);
            if (status != SDL_PASS)
            {
                testResult = -1;
            }
        }
    }

    /* The following sequence is needed to restore core to normal operation */
    /* Power off PBIST */
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].tisciPBISTDeviceId != 0u))
    {
#ifdef DEBUG
        DebugP_log("  Powering off PBIST %d \r\n",
                    PBIST_TestHandleArray[instanceId].tisciPBISTDeviceId);
#endif
        status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].tisciPBISTDeviceId,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                            TISCI_MSG_FLAG_AOP,
                                            SystemP_WAIT_FOREVER);

        if (status != SDL_PASS)
        {
            DebugP_log("   PBIST Sciclient_pmSetModuleState 0x%x ...FAILED \r\n",
                            PBIST_TestHandleArray[instanceId].tisciPBISTDeviceId);
            testResult = -1;
        }
    }
#ifdef POWERUP_CORES_BEFORE_TEST
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded)
                          && (PBIST_TestHandleArray[instanceId].tisciSecDeviceId != 0U))
    {
        if (PBIST_TestHandleArray[instanceId].secondaryCoreNeeded)
        {
            /* power off Secondary core*/
#ifdef DEBUG
            DebugP_log("  Secondary core: Powering off %s \r\n",
                        PBIST_TestHandleArray[instanceId].secCoreName);
#endif
            status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].tisciSecDeviceId,
                                                TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                                TISCI_MSG_FLAG_AOP,
                                                SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Secondary core: Sciclient_pmSetModuleState Power off 0x%x ...FAILED \r\n",
                            PBIST_TestHandleArray[instanceId].tisciSecDeviceId);
                testResult = -1;
                return testResult;
            }
        }
    }
    /* Custom core power down sequence */
    if ((testResult == 0) &&
        (PBIST_TestHandleArray[instanceId].coreCustPwrSeqNeeded) &&
        (PBIST_TestHandleArray[instanceId].tisciProcId != 0u))
    {
        status = customPowerDownSequence(PBIST_TestHandleArray[instanceId].tisciProcId);
        if (status != SDL_PASS)
        {
            DebugP_log("  Custom core power down sequence, ProcId 0x%x ...FAILED \r\n",
                        PBIST_TestHandleArray[instanceId].tisciProcId);
            testResult = -1;
        }
    }

    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].tisciProcId != 0u)
                    && (PBIST_TestHandleArray[instanceId].procRstNeeded))
    {
        /* power off Primary core*/
#ifdef DEBUG
        DebugP_log("  Primary core: Powering off %s \r\n",
                    PBIST_TestHandleArray[instanceId].coreName);
#endif
        status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].tisciDeviceId,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                            TISCI_MSG_FLAG_AOP,
                                            SystemP_WAIT_FOREVER);

        if (status != SDL_PASS)
        {
            DebugP_log("   Primary core: Sciclient_pmSetModuleState Power off 0x%x ...FAILED \r\n",
                        PBIST_TestHandleArray[instanceId].tisciDeviceId);
            testResult = -1;
        }
    }

    /* Power off of Auxilliary modules needed to run test */
    if (testResult == 0)
    {
        /* Power all modules required for test */
        for ( i = 0; i < PBIST_TestHandleArray[instanceId].numAuxDevices; i++)
        {
#ifdef DEBUG
            DebugP_log("  Powering off Device number %d Device Id %x\r\n",
                        i, PBIST_TestHandleArray[instanceId].auxDeviceIdsP[i]);
#endif
            status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].auxDeviceIdsP[i],
                                                TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                                TISCI_MSG_FLAG_AOP,
                                                SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("  Sciclient_pmSetModuleState 0x%x ...FAILED \r\n",
                            PBIST_TestHandleArray[instanceId].auxDeviceIdsP[i]);
                testResult = -1;
                break;
            }
        }
    }

    /* Custom core power restore sequence - needed to allow core to be powered
     * up properly later */
    if ((testResult == 0) &&
        (PBIST_TestHandleArray[instanceId].coreCustPwrSeqNeeded) &&
        (PBIST_TestHandleArray[instanceId].tisciProcId != 0u))
    {
        status = customPrepareForPowerUpSequence(PBIST_TestHandleArray[instanceId].tisciProcId);
        if (status != SDL_PASS)
        {
            DebugP_log("  Custom core power restore sequence, ProcId 0x%x ...FAILED \r\n",
                        PBIST_TestHandleArray[instanceId].tisciProcId);
            testResult = -1;
        }
    }

    /* Take Primary core out of local reset */
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded)
                          && (PBIST_TestHandleArray[instanceId].tisciDeviceId != 0U))
    {
#ifdef DEBUG
        DebugP_log("  Primary core: Taking out of local reset the core %s \r\n",
                    PBIST_TestHandleArray[instanceId].coreName);
#endif
        status = Sciclient_pmSetModuleRst(PBIST_TestHandleArray[instanceId].tisciDeviceId,
                                          0x0, /* Local Reset de-asserted */
                                          SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
             DebugP_log("  Sciclient_pmSetModuleRst 0x%x ...FAILED \r\n",
                         PBIST_TestHandleArray[instanceId].tisciDeviceId);
             testResult = -1;
        }
    }

    /* Take Secondary core out of local reset */
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded)
                          && (PBIST_TestHandleArray[instanceId].tisciSecDeviceId != 0U))
    {
#ifdef DEBUG
        DebugP_log("  Secondary core: Taking out of local reset the core %s \r\n",
                    PBIST_TestHandleArray[instanceId].secCoreName);
#endif
        status = Sciclient_pmSetModuleRst(PBIST_TestHandleArray[instanceId].tisciSecProcId,
                                          0x0, /* Local Reset de-asserted */
                                          SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
             DebugP_log("  Sciclient_pmSetModuleRst 0x%x ...FAILED \r\n",
                         PBIST_TestHandleArray[instanceId].tisciSecDeviceId);
             testResult = -1;
        }
    }
#endif /* #ifdef POWERUP_CORES_BEFORE_TEST */

    /* Ensure that cores have been turned off */
    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded))
    {
        if (PBIST_TestHandleArray[instanceId].tisciDeviceId != 0u)
        {
            /* Set Software Reset Disable State for Primary core */
#ifdef DEBUG
            DebugP_log("  %s: Primary core: Put in Software Reset Disable \r\n",
                        PBIST_TestHandleArray[instanceId].coreName);
#endif
            status =  Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].tisciDeviceId,
                                                 TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                                 TISCI_MSG_FLAG_AOP,
                                                 SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Primary core: Sciclient_pmSetModuleState...FAILED \r\n");
                testResult = -1;
            }
        }
    }

    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].procRstNeeded))
    {
        if ((PBIST_TestHandleArray[instanceId].secondaryCoreNeeded)
            && (PBIST_TestHandleArray[instanceId].tisciSecDeviceId != 0u))
        {
            /* Set Software Reset Disable State for Secondary core */
#ifdef DEBUG
            DebugP_log("  %s: Secondary Core Put in Software Reset Disable \r\n",
                        PBIST_TestHandleArray[instanceId].secCoreName);
#endif
            status =  Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].tisciSecDeviceId,
                                                 TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                                 TISCI_MSG_FLAG_AOP,
                                                 SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Secondary core Sciclient_pmSetModuleState...FAILED \r\n");
                testResult = -1;
            }
        }
    }

    if ((testResult == 0) && (PBIST_TestHandleArray[instanceId].tisciProcId != 0u)
            && (PBIST_TestHandleArray[instanceId].procRstNeeded))
    {
        /* release processor Primary core */
#ifdef DEBUG
        DebugP_log("  Primary core: Releasing %s \r\n",
                    PBIST_TestHandleArray[instanceId].coreName);
#endif

        status = Sciclient_procBootReleaseProcessor(PBIST_TestHandleArray[instanceId].tisciProcId,
                                                    TISCI_MSG_FLAG_AOP,
                                                    SystemP_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("   Primary core: Sciclient_procBootReleaseProcessor, ProcId 0x%x...FAILED \r\n",
                        PBIST_TestHandleArray[instanceId].tisciProcId);
            testResult = -1;
        }
    }

    if (testResult == 0)
    {
        if ((PBIST_TestHandleArray[instanceId].secondaryCoreNeeded)
            && (PBIST_TestHandleArray[instanceId].tisciSecProcId != 0u)
            && (PBIST_TestHandleArray[instanceId].procRstNeeded))
        {
            /* release processor Secondary core */
#ifdef DEBUG
            DebugP_log("  Secondary core: Releasing %s \r\n",
                        PBIST_TestHandleArray[instanceId].secCoreName);
#endif
            status = Sciclient_procBootReleaseProcessor(PBIST_TestHandleArray[instanceId].tisciSecProcId,
                                                        TISCI_MSG_FLAG_AOP,
                                                        SystemP_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Secondary core: Sciclient_procBootReleaseProcessor, ProcId 0x%x...FAILED \r\n",
                            PBIST_TestHandleArray[instanceId].tisciSecProcId);
                testResult = -1;
            }
        }
    }
    /* Record end time */
    endTime = ClockP_getTimeUsec();
    prepTime = testStartTime - startTime;
    diffTime = testEndTime - testStartTime;
    restoreTime = endTime - testEndTime;
    DebugP_log("  Delta Cores prep time in micro secs %d \r\n", (uint32_t)prepTime );
    DebugP_log("  Delta PBIST execution time in micro secs %d \r\n", (uint32_t)diffTime );
    DebugP_log("  Delta Cores restore time in micro secs %d \r\n", (uint32_t)restoreTime );
    DebugP_log(" PBIST complete %s, test index %d\r\n",
                PBIST_TestHandleArray[instanceId].testName,
                instanceId);

#ifdef PBIST_POST_CORE_MAX
    if (PBIST_TestHandleArray[instanceId].numPostPbistToCheck > 0)
    {
        switch(postStatus)
        {
            case SDL_PBIST_POST_COMPLETED_FAILURE:
                DebugP_log("\n HW POST: PBIST test failed\n");
                break;

            case SDL_PBIST_POST_TIMEOUT:
                DebugP_log("\n HW POST: PBIST was attempted but timed out\n");
                break;

            case SDL_PBIST_POST_NOT_RUN:
                DebugP_log("\n HW POST: PBIST was not performed on this device\n");
                break;

            case SDL_PBIST_POST_COMPLETED_SUCCESS:
            default:
                DebugP_log("\n HW POST: PBIST ran and succeeded\n");
                break;
        }
    }
#endif /* PBIST_POST_CORE_MAX */
    return (testResult);
}

/* PBIST Functional test */
int32_t PBIST_funcTest(void)
{
    int32_t    testResult = 0;
    int i;

    testResult = PBIST_commonInit();

    if (testResult != 0)
    {
        DebugP_log("  PBIST_commonInit ...FAILED \r\n");
    }
    else
    {
        /* Run the test for diagnostics first */
        for (i = 0; i < PBIST_NUM_INSTANCE; i++)
        {
            /* Run test on selected instance */
#if defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)
            testResult = PBIST_runTest(i, true);
#endif
            if ( testResult != 0)
            {
                break;
            }
        }

        if (testResult == 0)
        {
            /* Then run the pbist test */
            for (i = 0; i < PBIST_NUM_INSTANCE; i++)
            {
                /* Run test on selected instance */
#if defined (SOC_AM62X) || defined (SOC_AM62AX) || defined (SOC_AM62PX)
                testResult = PBIST_runTest(i, false);
#endif
                if ( testResult != 0)
                {
                    break;
                }
            }
        }
    }

    return (testResult);
}
/* Nothing past this point */

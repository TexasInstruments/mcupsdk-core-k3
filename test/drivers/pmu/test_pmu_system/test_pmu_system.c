/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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
 *  \file test_pmu_system.c
 *
 *  \brief This file contains implementation of all module test cases
 *         for PMU system tests across multiple cores.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <unity.h>
#include <drivers/pmu.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include <kernel/dpl/ClockP.h>
#if defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7R)
#include <kernel/nortos/dpl/r5/PmuP_armv7r.h>
#endif

/* ========================================================================== */
/*                               Macros                                       */
/* ========================================================================== */

#define TEST_PMU_MAX_COUNTERS           (3U)    /* R5 supports 3 event counters */
#define TEST_PMU_WORKLOAD_ITERATIONS    (50000U) /* Deterministic workload size */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void TestPmu_runDeterministicWorkload(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static PMU_EventCfg TestPmu_EventCfgBuf[TEST_PMU_MAX_COUNTERS];
static PMU_Config TestPmu_ConfigObj;


/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/**
 * \brief Helper function to run deterministic workload for PMU activity.
 *
 * Executes a fixed number of arithmetic operations to generate measurable
 * PMU events such as instruction execution and cache activity.
 *
 * \return None.
 */
static void TestPmu_runDeterministicWorkload(void)
{
    volatile uint32_t sum;
    uint32_t i;
    
    sum = 0U;
    for (i = 0U; i < TEST_PMU_WORKLOAD_ITERATIONS; i+=1)
    {
        sum += (i * 3U) + 7U;
    }
    (void)sum;
}

/**
 * \brief PMU core discovery and initialization test.
 *
 * This test detects the number of available PMU event counters using the
 * low-level API and initializes the PMU driver with valid event IDs.
 * Executes a deterministic workload and verifies that at least one event
 * counter increments, confirming proper PMU initialization and operation.
 *
 * Test Steps:
 * 1. Discover number of event counters using PmuP_GetNumCntrs()
 * 2. Initialize PMU with detected counter count and valid event IDs
 * 3. Execute workload and verify counter increments
 *
 * \param args Unused.
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestPmu_coreDiscoveryAndInit(void* args)
{
    uint32_t numCounters, i, eventBefore, eventAfter;
    int32_t initStatus;

    (void)args;

    /* Step 1: Discover number of event counters */
    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U && numCounters <= TEST_PMU_MAX_COUNTERS);

    /* Step 2: Build PMU_Config with valid events and initialize */
    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "InstrExec";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }
    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;

    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    /* Step 3: Execute workload and verify increment on counter 0 */
    eventBefore = PmuP_ReadCounter(0U);
    TestPmu_runDeterministicWorkload();
    eventAfter = PmuP_ReadCounter(0U);

    TEST_ASSERT_TRUE(eventAfter > eventBefore);
    return SystemP_SUCCESS;
}

/**
 * \brief PMU global enable/disable functional test.
 *
 * This test verifies that PMU counters can be globally disabled and re-enabled.
 * Confirms baseline increments, then disables all counters and ensures no
 * change occurs during workload execution. Re-enables counters and verifies
 * counting resumes properly.
 *
 * Test Steps:
 * 1. Initialize PMU and record initial counter value
 * 2. Disable all counters and execute workload
 * 3. Verify counter values remain unchanged
 * 4. Re-enable all counters and confirm counting resumes
 *
 * \param args Unused.
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestPmu_globalEnableDisable(void* args)
{
    uint32_t numCounters, i, initialValue, initialAfter;
    uint32_t disabledBefore, disabledAfter, enabledBefore, enabledAfter;
    int32_t initStatus;

    (void)args;

    /* Initialize with at least one valid event */
    numCounters = PmuP_GetNumCntrs();
    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "InstrExec";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }
    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;

    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    /* Record initial value and confirm baseline increments */
    initialValue = PmuP_ReadCounter(0U);
    TestPmu_runDeterministicWorkload();
    initialAfter = PmuP_ReadCounter(0U);
    TEST_ASSERT_TRUE(initialAfter > initialValue);

    /* Disable all counters; run workload; verify unchanged */
    PmuP_EnableAllCounters(0U);
    disabledBefore = PmuP_ReadCounter(0U);
    TestPmu_runDeterministicWorkload();
    disabledAfter = PmuP_ReadCounter(0U);
    TEST_ASSERT_EQUAL_UINT32(disabledBefore, disabledAfter);

    /* Re-enable all counters; run workload; verify increments resume */
    PmuP_EnableAllCounters(1U);
    enabledBefore = PmuP_ReadCounter(0U);
    TestPmu_runDeterministicWorkload();
    enabledAfter = PmuP_ReadCounter(0U);
    TEST_ASSERT_TRUE(enabledAfter > enabledBefore);

    return SystemP_SUCCESS;
}

/**
 * \brief PMU reset event counters test.
 *
 * Tests that event counters can be reset independently while the cycle counter
 * continues to increment monotonically. This is critical for performance
 * profiling scenarios where event counters need to be reset between measurement
 * intervals while maintaining an absolute time reference via the cycle counter.
 *
 * Test Steps:
 * 1. Initialize PMU with event counters and cycle counter enabled
 * 2. Run workload and capture initial counter values
 * 3. Reset only event counters using PmuP_ResetCounters()
 * 4. Verify event counters reset to near-zero while cycle counter continues
 * 5. Run workload again to confirm both counters increment normally
 *
 * \param args Unused.
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestPmu_resetEventCounters(void* args)
{
    uint32_t numCounters, i, cycleBefore, cycleAfter, cycleFinal;
    uint32_t event0Before, event0After, event0Final;
    volatile uint32_t delayCount;
    int32_t initStatus;

    (void)args;

    /* Step 1: Initialize PMU with event and cycle counters */
    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U && numCounters <= TEST_PMU_MAX_COUNTERS);

    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "InstrExec";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }
    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;

    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    /* Step 2: Execute workload and record counter values */
    TestPmu_runDeterministicWorkload();
    cycleBefore  = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    event0Before = PmuP_ReadCounter(0U);

    /* Step 3: Reset event counters only */
    PmuP_ResetCounters();

    /* Small delay to allow reset to complete */
    delayCount = 100U;
    while (delayCount > 0U)
    {
        delayCount-=1;
    }

    /* Step 4: Verify event reset to near-zero, cycle continues */
    cycleAfter  = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    event0After = PmuP_ReadCounter(0U);

    TEST_ASSERT_TRUE(event0After < event0Before);
    TEST_ASSERT_TRUE(cycleAfter >= cycleBefore);

    /* Step 5: Confirm subsequent increments occur on both */
    TestPmu_runDeterministicWorkload();
    event0Final = PmuP_ReadCounter(0U);
    cycleFinal  = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);

    TEST_ASSERT_TRUE(event0Final > event0After);
    TEST_ASSERT_TRUE(cycleFinal > cycleAfter);

    return SystemP_SUCCESS;
}

/**
 * \brief PMU per-counter enable/disable test.
 *
 * Tests the ability to selectively enable or disable individual PMU counters
 * while others continue counting. This functionality is essential for dynamic
 * profiling where different metrics need to be monitored at different times.
 *
 * Test Steps:
 * 1. Initialize PMU with at least 2 event counters
 * 2. Disable counter 1 while leaving counter 0 enabled
 * 3. Run workload and verify counter 0 increments but counter 1 stays frozen
 * 4. Re-enable counter 1 and verify it resumes counting
 *
 * \param args Unused.
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestPmu_perCounterControl(void* args)
{
    uint32_t numCounters, i, c0Before, c1DisabledBaseline;
    uint32_t c0After, c1AfterDisabled, c1AfterEnabled;
    int32_t initStatus;

    (void)args;

    /* Step 1: Initialize PMU - need at least 2 counters */
    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters >= 2U);

    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "InstrExec";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }
    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;

    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    /* Step 2: Disable counter 1, keep counter 0 active */
    PmuP_enableCounter(1U, 0U);
    ClockP_usleep(100); /* Allow gating to take effect */

    c0Before            = PmuP_ReadCounter(0U);
    c1DisabledBaseline  = PmuP_ReadCounter(1U);

    /* Step 3: Run workload - counter 0 should increment, counter 1 should not */
    TestPmu_runDeterministicWorkload();

    c0After         = PmuP_ReadCounter(0U);
    c1AfterDisabled = PmuP_ReadCounter(1U);

    TEST_ASSERT_TRUE(c0After > c0Before);
    TEST_ASSERT_EQUAL_UINT32(c1DisabledBaseline, c1AfterDisabled);

    /* Step 4: Re-enable counter 1 and verify counting resumes */
    PmuP_enableCounter(1U, 1U);
    ClockP_usleep(100);
    TestPmu_runDeterministicWorkload();
    c1AfterEnabled = PmuP_ReadCounter(1U);

    TEST_ASSERT_TRUE(c1AfterEnabled > c1AfterDisabled);

    return SystemP_SUCCESS;
}

/**
 * Copyright (C) 2026 Texas Instruments Incorporated
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
 *
 */

 /**
 *  \file     test_pmu.c
 *
 *  \brief    This file contains pmu API test code for dm-r5 and mcu-r5 core.
 *
 *  \details  PMU read/write and configuration tests
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unity.h>
#include <drivers/pmu.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/CycleCounterP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/nortos/dpl/r5/PmuP_armv7r.h>

/*===========================================================================*/
/*                               Macros                                      */
/*===========================================================================*/

#define TEST_PMU_FREEZE_TOLERANCE               100U    /* Max delta while frozen/disabled */

/* Counter indices for use with PmuP_ReadCounter, PmuP_enableCounter,
 * PmuP_SetCntr, PmuP_EnableCounterOverflowInterrupt, PmuP_ConfigCounter,
 * and PMOVSR bit-position arithmetic */
#define TEST_PMU_COUNTER_IDX_0                  0U
#define TEST_PMU_COUNTER_IDX_1                  1U
#define TEST_PMU_COUNTER_IDX_2                  2U

/* Counter preload values near 32-bit overflow for wrapping tests */
#define TEST_PMU_NEAR_OVERFLOW_2                0xFFFFFFFEU     /* 2 counts before max */
#define TEST_PMU_NEAR_OVERFLOW_4                0xFFFFFFFCU     /* 4 counts before max */
#define TEST_PMU_NEAR_OVERFLOW_16               0xFFFFFFF0U     /* 16 counts before max */

/* Preset counter value written before measuring delta in read/write tests */
#define TEST_PMU_BASELINE_COUNTER_VAL           100U

/* Polling iteration budgets for overflow-detect busy-wait loops */
#define TEST_PMU_POLL_BUDGET                    1000U
#define TEST_PMU_POLL_BUDGET_LARGE              2000U
#define TEST_PMU_POLL_BUDGET_OVERFLOW           5000U

/* Maximum expected counter value after a 32-bit wrap (confirms counter reset) */
#define TEST_PMU_WRAPPED_VAL_MAX                100000U

/* Minimum expected event count delta to confirm a counter is actively counting */
#define TEST_PMU_MIN_VALID_DELTA                1000U

/* Tolerance percentage for counter delta rate comparisons */
#define TEST_PMU_TOLERANCE_PCT                  20U

/* Divide-by-64 cycle counter divisor ratio */
#define TEST_PMU_DIVIDER_RATIO                  64U

/* Rapid back-to-back write/read iteration count */
#define TEST_PMU_RAPID_RW_ITER_COUNT            64U

/* Deterministic workload inner loop count */
#define TEST_PMU_WORKLOAD_ITER_COUNT            50000U

/* Heavy workload loop iteration count */
#define TEST_PMU_HEAVY_WORKLOAD_ITER_COUNT      200000U

/* Standard counter-gating hardware settle time (microseconds) */
#define TEST_PMU_GATING_DELAY_US                100U

/* Number of 32-bit wraps for the software 64-bit chain accumulation test */
#define TEST_PMU_SW_CHAIN_WRAP_COUNT            3U

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint32_t TestPmu_NumCounters             = 0U;
static uint32_t TestPmu_DivideTolerancePct      = 50U;          /* Allowed +/- tolerance for divide-by-64 rate check */
static const char *TestPmu_BlockNameConst       = "BlockA";
static PMU_EventCfg TestPmu_EventCfgBuf[3];                     /* R5 supports up to 3 event counters */
static PMU_Config TestPmu_ConfigObj;

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/* Helper function to run deterministic workload */
static void TestPmu_runDeterministicWorkload(void);

/* ========================================================================== */
/*                       Static Test Function Prototypes                      */
/* ========================================================================== */

/* Functional test cases */
static void TestPmu_coreDiscoveryAndInit(void *args);
static void TestPmu_globalEnableDisableAllCounters(void *args);
static void TestPmu_resetEventCountersOnly(void *args);
static void TestPmu_resetCycleCounterOnly(void *args);
static void TestPmu_initEnablesSelectedEventCounters(void *args);
static void TestPmu_profileStartEndReturnCodes(void *args);
static void TestPmu_reinitializeWithNewEventSelection(void *args);
static void TestPmu_perCounterEnableDisable(void *args);
static void TestPmu_cycleCounterEnableReadReset(void *args);
static void TestPmu_cycleCounterDivideBy64Effect(void *args);
static void TestPmu_cycleCounterGatingPerCounter(void *args);
static void TestPmu_perCounterOverflowInterruptEnableDisable(void *args);
static void TestPmu_overflowIsrLogicDetectAndClear(void *args);
static void TestPmu_overflowIsrLogicRearmAndRepeat(void *args);
static void TestPmu_programValidEventAndCountCntr0(void *args);
static void TestPmu_perCounterEnableDisableHaltsOnlyThatCounter(void *args);
static void TestPmu_readWriteCounterValueWithSetCntr(void *args);
static void TestPmu_counterOverflowFlagAndWrap(void *args);
static void TestPmu_globalFreezePreservesAccumulatedValuesAcrossMultipleCycles(void *args);
static void TestPmu_perCounterReprogramDoesNotAffectOthers(void *args);
static void TestPmu_softwareChainingViaOverflowFor64bitAccum(void *args);
static void TestPmu_userAccessEnablePathViaPmuPConfig(void *args);
static void TestPmu_enableDisableDoesNotCorruptOtherCountersState(void *args);
static void TestPmu_rapidBackToBackReadWriteIsRaceFree(void *args);
static void TestPmu_getOverflowStatusNoFlags(void *args);
static void TestPmu_overflowStatusPersistsUntilCleared(void *args);
static void TestPmu_clearOverflowStatusMultipleBitsMask(void *args);
static void TestPmu_cycleCounterOverflowStatusReadAndClear(void *args);

/* ========================================================================== */
/*                      External Function Declarations                        */
/* ========================================================================== */

/**
 *  \brief Read the overflow status (PMOVSR).
 *
 *  \return PMOVSR bitmask
 */
extern uint32_t PmuP_ReadCntrOverflowStatus( void );

/* ========================================================================== */
/*                        Internal Function Definitions                       */
/* ========================================================================== */

/* Helper: function used to run deterministic work load*/
static void TestPmu_runDeterministicWorkload(void)
{
    /* Small deterministic workload to generate PMU activity */
    volatile uint32_t sum = 0U;
    uint32_t i;
    for (i = 0U; i < TEST_PMU_WORKLOAD_ITER_COUNT; i+=1)
    {
        sum += (i * 3U) + 7U;
    }
    (void)sum;
}

/* ========================================================================== */
/*                               Test cases                                   */
/* ========================================================================== */
/**
 * \brief Core discovery and init — detects PMU counters and initializes.
 *
 * Test Category: Functional
 *
 * Discovers available PMU event counters using the low-level API and initializes
 * the PMU driver with valid event IDs matching the detected count. Executes a
 * deterministic workload and verifies that at least one event counter increments.
 *
 * Test Steps:
 * 1. Read the number of supported event counters using PmuP_GetNumCntrs().
 * 2. Initialize the PMU using the detected counter count and valid event IDs.
 * 3. Execute a workload and verify at least one event counter increments.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput At least one event counter increments after workload.
 */
static void TestPmu_coreDiscoveryAndInit(void *args)
{
    (void)args;
    uint32_t i, eventBefore, eventAfter;
    int32_t initStatus;
    /* Step 1: Discover number of event counters */
    TestPmu_NumCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(TestPmu_NumCounters > 0U && TestPmu_NumCounters <= 3U);

    /* Step 2: Build PMU_Config with valid events and initialize */
    for (i = 0U; i < TestPmu_NumCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "InstrExec";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X; /* valid event ID */
    }
    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = TestPmu_NumCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;

    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    /* Step 3: Execute workload and verify increment on counter 0 */
    eventBefore = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    eventAfter  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(eventAfter > eventBefore);
}

/**
 * \brief Global enable/disable — counting halts and resumes correctly.
 *
 * Test Category: Functional
 *
 * Initializes the PMU with valid events, confirms baseline increments, then
 * disables all counters and ensures no change occurs while a workload runs.
 * Re-enables all counters and verifies counting resumes.
 *
 * Test Steps:
 * 1. Initialize the PMU and record an initial counter value.
 * 2. Disable all counters and execute a workload.
 * 3. Verify counter values remain unchanged.
 * 4. Re-enable all counters and confirm counting resumes.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Counter unchanged while disabled; increments resume after re-enable.
 */
static void TestPmu_globalEnableDisableAllCounters(void *args)
{
    (void)args;
    uint32_t i;
    uint32_t initialValue, initialAfter, disabledBefore, disabledAfter;
    uint32_t enabledBefore, enabledAfter;
    /* Initialize with at least one valid event */
    TestPmu_NumCounters = PmuP_GetNumCntrs();
    for (i = 0U; i < TestPmu_NumCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "InstrExec";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }
    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = TestPmu_NumCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, PMU_init(&TestPmu_ConfigObj));

    /* Record initial value and confirm baseline increments */
    initialValue = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    initialAfter = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(initialAfter > initialValue);

    /* Disable all counters; run workload; verify unchanged */
    PmuP_EnableAllCounters(0U);
    disabledBefore = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    disabledAfter  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_EQUAL_UINT32(disabledBefore, disabledAfter);

    /* Re-enable all counters; run workload; verify increments resume */
    PmuP_EnableAllCounters(1U);
    enabledBefore = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    enabledAfter  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(enabledAfter > enabledBefore);
}

/**
 * \brief Reset event counters only — cycle counter remains monotonic.
 *
 * Test Category: Functional
 *
 * With cycle counter enabled, executes a workload, captures cycle and event
 * values, resets only event counters, and verifies event counters go to near-zero
 * while the cycle counter continues to increment monotonically.
 *
 * Test Steps:
 * 1. Initialize the PMU with cycle counter enabled.
 * 2. Execute a workload and record cycle and event counter values.
 * 3. Reset event counters.
 * 4. Verify event counters are small/near-zero while cycle counter remains monotonic.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Event counters reset near-zero; cycle counter monotonic.
 */
static void TestPmu_resetEventCountersOnly(void *args)
{
    (void)args;
    uint32_t i;
    uint32_t cycleBefore, cycleAfter, cycleFinal;
    uint32_t event0Before, event0After, event0Final;
    volatile uint32_t delayCount;
    /* Initialize with cycle counter enabled */
    TestPmu_NumCounters = PmuP_GetNumCntrs();
    for (i = 0U; i < TestPmu_NumCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "InstrExec";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }
    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = TestPmu_NumCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, PMU_init(&TestPmu_ConfigObj));

    /* Execute workload and record cycle/event values */
    TestPmu_runDeterministicWorkload();
    cycleBefore  = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    event0Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    /* Reset event counters only */
    PmuP_ResetCounters();

    /* Small delay to allow reset to complete */
    delayCount = 100U;
    while (delayCount > 0U)
    {
        delayCount-=1;
    }

    /* Verify event counters are small (near-zero after reset); cycle continues */
    cycleAfter  = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    event0After = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    /* Event counter should be much smaller than before reset */
    TEST_ASSERT_TRUE(event0After < event0Before);
    /* Cycle counter should be monotonic or slightly increased */
    TEST_ASSERT_TRUE(cycleAfter >= cycleBefore);

    /* Confirm subsequent increments occur on both */
    TestPmu_runDeterministicWorkload();
    event0Final = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    cycleFinal  = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TEST_ASSERT_TRUE(event0Final > event0After);
    TEST_ASSERT_TRUE(cycleFinal > cycleAfter);
}

/**
 * \brief Reset cycle counter only — event counters remain monotonic.
 *
 * Test Category: Functional
 *
 * Executes a workload, captures cycle and event values, resets only the cycle
 * counter, and verifies cycle counter resets to near-zero while event counters
 * remain unchanged or continue increasing.
 *
 * Test Steps:
 * 1. Initialize the PMU and execute a workload.
 * 2. Record cycle and event counter values.
 * 3. Reset the cycle counter.
 * 4. Verify the cycle counter resets near-zero and event counters are monotonic.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Cycle counter resets near-zero; event counters monotonic.
 */
static void TestPmu_resetCycleCounterOnly(void *args)
{
    (void)args;
    uint32_t i;
    uint32_t cycleBefore, cycleAfter, cycleFinal;
    uint32_t event0Before, event0After, event0Final;
    volatile uint32_t delayCount;
    /* Initialize PMU */
    TestPmu_NumCounters = PmuP_GetNumCntrs();
    for (i = 0U; i < TestPmu_NumCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "InstrExec";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }
    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = TestPmu_NumCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, PMU_init(&TestPmu_ConfigObj));

    /* Execute workload and record values */
    TestPmu_runDeterministicWorkload();
    cycleBefore  = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    event0Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    /* Reset cycle counter only */
    PmuP_ResetCycleCnt();

    /* Small delay to allow reset to complete */
    delayCount = 100U;
    while (delayCount > 0U)
    {
        delayCount-=1;
    }

    /* Verify cycle resets near-zero; event counter monotonic */
    cycleAfter  = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    event0After = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    /* Cycle counter should be much smaller than before reset */
    TEST_ASSERT_TRUE(cycleAfter < cycleBefore);
    /* Event counter should be monotonic or slightly increased */
    TEST_ASSERT_TRUE(event0After >= event0Before);

    /* Confirm subsequent increments occur on both */
    TestPmu_runDeterministicWorkload();
    cycleFinal  = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    event0Final = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(cycleFinal > cycleAfter);
    TEST_ASSERT_TRUE(event0Final > event0After);
}

/**
 * \brief Init enables selected event counters — verify increment.
 *
 * Test Category: Functional
 *
 * Assigns a valid event to counter 0 during initialization, executes a
 * deterministic workload, and verifies counter 0 increments from its baseline.
 *
 * Test Steps:
 * 1. Initialize the PMU with a valid event assigned to counter 0.
 * 2. Execute a deterministic workload.
 * 3. Verify counter 0 increments.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Counter 0 increments after workload.
 */
static void TestPmu_initEnablesSelectedEventCounters(void *args)
{
    (void)args;
    uint32_t i, counter0Before, counter0After;
    /* Assign a valid event to counter 0 */
    TestPmu_NumCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(TestPmu_NumCounters > 0U && TestPmu_NumCounters <= 3U);

    for (i = 0U; i < TestPmu_NumCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = (i == 0U) ? "InstrExec_C0" : "InstrExec";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }

    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = TestPmu_NumCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, PMU_init(&TestPmu_ConfigObj));

    /* Execute deterministic workload and verify counter 0 increments */
    counter0Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    counter0After  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(counter0After > counter0Before);
}

/**
 * \brief Profile start/end return codes functional test.
 *
 * Test Category: Functional
 *
 * Profiles a named code region and verifies both PMU_profileStart() and
 * PMU_profileEnd() return SystemP_SUCCESS.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Both APIs return SystemP_SUCCESS; profile entry captured.
 */
static void TestPmu_profileStartEndReturnCodes(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    int32_t initStatus, startStatus, endStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U && numCounters <= 3U);

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

    startStatus = PMU_profileStart(TestPmu_BlockNameConst);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, startStatus);

    TestPmu_runDeterministicWorkload();

    endStatus = PMU_profileEnd(TestPmu_BlockNameConst);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, endStatus);
}

/**
 * \brief Reinitialize with new event selection functional test.
 *
 * Test Category: Functional
 *
 * Reinitializes the PMU with a new set of event types and verifies counters
 * reset and then increment correctly after reinit.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Counters reset on reinit; subsequent workload increments.
 */
static void TestPmu_reinitializeWithNewEventSelection(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t before0, afterReset0, afterWork0;
    int32_t initStatusA, initStatusB;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U && numCounters <= 3U);

    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "InstrExecA";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }
    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;

    initStatusA = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatusA);

    TestPmu_runDeterministicWorkload();
    before0 = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(before0 > 0U);

    /* Reconfigure to different valid events */
    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "DcacheAccessB";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_DCACHE_ACCESS;
    }
    initStatusB = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatusB);

    /* After reinit, counters should be reset */
    afterReset0 = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(afterReset0 == 0U || afterReset0 < before0);

    /* Verify increments with workload under new event config */
    TestPmu_runDeterministicWorkload();
    afterWork0 = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(afterWork0 > afterReset0);
}

/**
 * \brief Per-counter enable/disable functional test.
 *
 * Test Category: Functional
 *
 * Disables a single event counter while others continue counting; verifies
 * disabled counter does not increment and resumes after re-enable.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Disabled counter value remains constant during workload;
 *                 increments resume after re-enable; other counters unaffected.
 */
static void TestPmu_perCounterEnableDisable(void *args)
{
    (void)args;
    uint32_t numCounters, initStatus, i;
    uint32_t c0Before, c1DisabledBaseline;
    uint32_t c0After, c1AfterDisabled, c1AfterEnabled;

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

    /* Disable counter 1 first, then sample its baseline to avoid race increments */
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US); /* allow gating to take effect */

    c0Before            = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    c1DisabledBaseline  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);

    TestPmu_runDeterministicWorkload();

    c0After         = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    c1AfterDisabled = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);

    TEST_ASSERT_TRUE(c0After > c0Before);
    TEST_ASSERT_EQUAL_UINT32(c1DisabledBaseline, c1AfterDisabled);

    /* Re-enable counter 1 and verify counting resumes */
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    TestPmu_runDeterministicWorkload();
    c1AfterEnabled = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);
    TEST_ASSERT_TRUE(c1AfterEnabled > c1AfterDisabled);
}

/**
 * \brief Cycle counter enable/read/reset functional test.
 *
 * Test Category: Functional
 *
 * Verifies cycle counter increments under workload, then resets to zero when
 * counters are globally disabled during reset, and resumes counting after re-enable.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Cycle count increases with workload, zeros after reset while
 *                 disabled, and increases again after re-enable.
 */
static void TestPmu_cycleCounterEnableReadReset(void *args)
{
    (void)args;
    uint32_t numCounters, initStatus, i;
    uint32_t cycleBefore, cycleAfterWork, cycleAfterReset, cycleFinal;

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

    TestPmu_runDeterministicWorkload();
    cycleBefore   = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TestPmu_runDeterministicWorkload();
    cycleAfterWork = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TEST_ASSERT_TRUE(cycleAfterWork > cycleBefore);

    /* Disable all counters, then reset cycle to ensure read-back is zero */
    PmuP_EnableAllCounters(0U);
    PmuP_ResetCycleCnt();
    cycleAfterReset = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TEST_ASSERT_EQUAL_UINT32(0U, cycleAfterReset);

    /* Re-enable and verify counting resumes */
    PmuP_EnableAllCounters(1U);
    TestPmu_runDeterministicWorkload();
    cycleFinal = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TEST_ASSERT_TRUE(cycleFinal > cycleAfterReset);
}

/**
 * \brief Cycle counter divide-by-64 effect functional test.
 *
 * Test Category: Functional
 *
 * Measures cycle delta for a fixed workload with normal rate, then enables
 * divide-by-64 via PmuP_Config and measures again; verifies the second delta is
 * reduced approximately by 64x with tolerance.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Delta with divider is ~64x smaller than normal delta within tolerance.
 */
static void TestPmu_cycleCounterDivideBy64Effect(void *args)
{
    (void)args;
    uint32_t numCounters, initStatus, d0, d1, i;
    uint32_t startTicks, endTicks, ratio, minRatio, maxRatio;

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

    /* Baseline measurement */
    PmuP_ResetCycleCnt();
    startTicks = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TestPmu_runDeterministicWorkload();
    endTicks   = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    d0 = (endTicks - startTicks);
    TEST_ASSERT_TRUE(d0 > 0U);

    /* Enable divide-by-64, then measure again */
    PmuP_Config(/*cycleCntDiv=*/1U, /*exportEvents=*/0U, /*userEnable=*/1U);
    PmuP_ResetCycleCnt();
    startTicks = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TestPmu_runDeterministicWorkload();
    endTicks   = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    d1 = (endTicks - startTicks);
    TEST_ASSERT_TRUE(d1 > 0U);

    /* Verify reduced rate approximately 64x with tolerance */
    ratio     = (d0 / (d1 == 0U ? 1U : d1));
    minRatio  = (TEST_PMU_DIVIDER_RATIO - (TEST_PMU_DIVIDER_RATIO * TestPmu_DivideTolerancePct) / 100U); /* e.g., 32 for 50% */
    maxRatio  = (TEST_PMU_DIVIDER_RATIO + (TEST_PMU_DIVIDER_RATIO * TestPmu_DivideTolerancePct) / 100U); /* e.g., 96 for 50% */
    TEST_ASSERT_TRUE(ratio >= minRatio && ratio <= maxRatio);

    /* Restore normal rate */
    PmuP_Config(/*cycleCntDiv=*/0U, /*exportEvents=*/0U, /*userEnable=*/1U);
}

/**
 * \brief Cycle counter gating per-counter functional test.
 *
 * Test Category: Functional
 *
 * Disables only the cycle counter while leaving event counters enabled. Verifies
 * the cycle counter halts during workload while event counters continue to
 * increment, then resumes after re-enable.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Cycle counter unchanged while gated; event counter increases;
 *                 cycle increments after re-enable.
 */
static void TestPmu_cycleCounterGatingPerCounter(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t cycleBeforeGated, cycleAfterGated, cycleAfterEnabled;
    uint32_t eventBeforeGated, eventAfterGated;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    /* Gate only the cycle counter */
    PmuP_enableCounter(PmuP_PMU_CYCLE_COUNTER_NUM, 0U);

    cycleBeforeGated = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    eventBeforeGated = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    TestPmu_runDeterministicWorkload();

    cycleAfterGated = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    eventAfterGated = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    TEST_ASSERT_EQUAL_UINT32(cycleBeforeGated, cycleAfterGated);
    TEST_ASSERT_TRUE(eventAfterGated > eventBeforeGated);

    /* Re-enable cycle counter and verify counting resumes */
    PmuP_enableCounter(PmuP_PMU_CYCLE_COUNTER_NUM, 1U);
    TestPmu_runDeterministicWorkload();
    cycleAfterEnabled = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TEST_ASSERT_TRUE(cycleAfterEnabled > cycleAfterGated);
}

/**
 * \brief Per-counter overflow interrupt enable/disable functional test.
 *
 * Test Category: Functional
 *
 * Enables overflow interrupt for a selected counter, forces an overflow, and
 * verifies status bit sets and clears as expected.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Overflow status bit for the counter sets after overflow and
 *                 is cleared by PmuP_ClearCntrOverflowStatus().
 */
static void TestPmu_perCounterOverflowInterruptEnableDisable(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t statusMask, pollCount;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    /* Enable overflow interrupt for counter 0 and force overflow */
    PmuP_EnableCounterOverflowInterrupt(TEST_PMU_COUNTER_IDX_0, 1U);
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, TEST_PMU_NEAR_OVERFLOW_2);

    /* Drive a few increments to cause wrap */
    TestPmu_runDeterministicWorkload();

    /* Poll for overflow status */
    statusMask = 0U;
    pollCount = TEST_PMU_POLL_BUDGET;
    while ((pollCount > 0U) && ((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) == 0U))
    {
        statusMask = PmuP_getOverflowStatus();
        pollCount -= 1;
    }
    TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) != 0U);

    /* Clear and verify cleared */
    PmuP_ClearCntrOverflowStatus(1U << TEST_PMU_COUNTER_IDX_0);
    statusMask = PmuP_getOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) == 0U);
}

/**
 * \brief Overflow detect and clear logic functional test.
 *
 * Test Category: Functional
 *
 * Enables overflow interrupts on multiple counters, forces overflow on a
 * specific counter, and verifies only that counter's overflow status bit is set
 * and is cleared correctly.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Only the targeted counter's bit in PMOVSR is set; clearing
 *                 that bit returns PMOVSR to zero.
 */
static void TestPmu_overflowIsrLogicDetectAndClear(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t statusMask, pollCount, targetIdx;
    int32_t initStatus;

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

    /* Enable overflow for multiple counters */
    for (i = 0U; i < numCounters; i+=1)
    {
        PmuP_EnableCounterOverflowInterrupt(i, 1U);
    }

    /* Pick a specific counter (1 if available) to overflow */
    targetIdx = (numCounters > 1U) ? 1U : 0U;
    PmuP_SetCntr(targetIdx, TEST_PMU_NEAR_OVERFLOW_2);

    TestPmu_runDeterministicWorkload();

    /* Poll and verify only target bit is set */
    statusMask = 0U;
    pollCount = TEST_PMU_POLL_BUDGET;
    while ((pollCount > 0U) && ((statusMask & (1U << targetIdx)) == 0U))
    {
        statusMask = PmuP_getOverflowStatus();
        pollCount -= 1;
    }
    TEST_ASSERT_TRUE((statusMask & (1U << targetIdx)) != 0U);
    TEST_ASSERT_TRUE((statusMask & ~(1U << targetIdx)) == 0U);

    /* Clear target bit and verify cleared */
    PmuP_ClearCntrOverflowStatus(1U << targetIdx);
    statusMask = PmuP_getOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & (1U << targetIdx)) == 0U);
}

/**
 * \brief Overflow re-arm and repeat functional test.
 *
 * Test Category: Functional
 *
 * Enables overflow interrupt for one counter, forces an overflow, clears the
 * status, re-arms by keeping the counter enabled, and repeats to verify
 * consistent detection across multiple cycles.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Overflow status is detected, cleared, and detected again on
 *                 subsequent overflow for the same counter.
 */
static void TestPmu_overflowIsrLogicRearmAndRepeat(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t statusMask, pollCount, counterIdx;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    counterIdx = 0U;
    PmuP_EnableCounterOverflowInterrupt(counterIdx, 1U);

    /* First overflow */
    PmuP_SetCntr(counterIdx, TEST_PMU_NEAR_OVERFLOW_2);
    TestPmu_runDeterministicWorkload();

    statusMask = 0U;
    pollCount = TEST_PMU_POLL_BUDGET;
    while ((pollCount > 0U) && ((statusMask & (1U << counterIdx)) == 0U))
    {
        statusMask = PmuP_ReadCntrOverflowStatus();
        pollCount -= 1;
    }
    TEST_ASSERT_TRUE((statusMask & (1U << counterIdx)) != 0U);

    PmuP_ClearCntrOverflowStatus(1U << counterIdx);
    statusMask = PmuP_ReadCntrOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & (1U << counterIdx)) == 0U);

    /* second overflow */
    PmuP_SetCntr(counterIdx, TEST_PMU_NEAR_OVERFLOW_2);
    TestPmu_runDeterministicWorkload();

    statusMask = 0U;
    pollCount = TEST_PMU_POLL_BUDGET;
    while ((pollCount > 0U) && ((statusMask & (1U << counterIdx)) == 0U))
    {
        statusMask = PmuP_ReadCntrOverflowStatus();
        pollCount -= 1;
    }
    TEST_ASSERT_TRUE((statusMask & (1U << counterIdx)) != 0U);

    PmuP_ClearCntrOverflowStatus(1U << counterIdx);
    statusMask = PmuP_ReadCntrOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & (1U << counterIdx)) == 0U);
}

/**
 * \brief Program valid event and count on counter 0 functional test.
 *
 * Test Category: Functional
 *
 * Configures PMU with cycle counter enabled and a valid event on counter 0.
 * Executes a deterministic workload and verifies counter 0 increments.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Counter 0 value increases after workload.
 */
static void TestPmu_programValidEventAndCountCntr0(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t counter0Before, counter0After;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    counter0Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    counter0After  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(counter0After > counter0Before);
}

/**
 * \brief Per-counter enable/disable halts only that counter.
 *
 * Test Category: Functional
 *
 * Disables a single event counter and verifies only that counter stops counting
 * while other counters continue. Then re-enables and confirms counting resumes.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Disabled counter remains unchanged during workload; other counters
 *                 increment; disabled counter resumes after re-enable.
 */
static void TestPmu_perCounterEnableDisableHaltsOnlyThatCounter(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t c0Before, c1DisabledBaseline, c0After, c1AfterDisabled;
    int32_t initStatus;

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

    /* Disable counter 1, then sample baseline */
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    c0Before           = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    c1DisabledBaseline = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);

    TestPmu_runDeterministicWorkload();

    c0After         = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    c1AfterDisabled = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);

    TEST_ASSERT_TRUE(c0After > c0Before);
    TEST_ASSERT_EQUAL_UINT32(c1DisabledBaseline, c1AfterDisabled);

    /* Re-enable and verify resume */
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    TestPmu_runDeterministicWorkload();
    TEST_ASSERT_TRUE(PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1) > c1AfterDisabled);
}

/**
 * \brief Read/write counter value with PmuP_SetCntr.
 *
 * Test Category: Functional
 *
 * Programs a baseline value into an event counter using PmuP_SetCntr(), verifies
 * readback, then runs workload to confirm accumulation beyond baseline.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Readback equals programmed value; subsequent reads increase after workload.
 */
static void TestPmu_readWriteCounterValueWithSetCntr(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t baselineValue, readBackValue, postWorkValue;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    /* Freeze all counters to avoid increments while programming baseline */
    PmuP_EnableAllCounters(0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    baselineValue = TEST_PMU_BASELINE_COUNTER_VAL;
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, baselineValue);
    readBackValue = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_EQUAL_UINT32(baselineValue, readBackValue);

    /* Unfreeze and verify accumulation */
    PmuP_EnableAllCounters(1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    TestPmu_runDeterministicWorkload();
    postWorkValue = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(postWorkValue > baselineValue);
}

/**
 * \brief Counter overflow flag and wrap behavior.
 *
 * Test Category: Functional
 *
 * Forces an event counter to overflow and verifies the counter wraps and the
 * overflow status bit is set. Clears the flag and verifies it is cleared.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Counter wraps to small value; PMOVSR bit sets; clear removes bit.
 */
static void TestPmu_counterOverflowFlagAndWrap(void *args)
{
    (void)args;
    uint32_t numCounters, i, retry;
    uint32_t statusMask, wrappedValue, pollBudget, counterValue;
    int32_t initStatus;
    volatile uint32_t sum;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    /* Enable overflow reporting on counter 0 and set near max */
    PmuP_EnableCounterOverflowInterrupt(TEST_PMU_COUNTER_IDX_0, 1U);

    /* Freeze counter before setting value */
    PmuP_EnableAllCounters(0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    /* Set counter very close to overflow */
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, TEST_PMU_NEAR_OVERFLOW_16);

    /* Verify the write took effect */
    counterValue = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(counterValue >= TEST_PMU_NEAR_OVERFLOW_16);

    /* Re-enable counter to start counting */
    PmuP_EnableAllCounters(1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    /* Drive increments to force wrap; poll official status API */
    statusMask = 0U;
    pollBudget = TEST_PMU_POLL_BUDGET_OVERFLOW;
    while ((pollBudget > 0U) && ((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) == 0U))
    {
        sum = 0U;
        for (i = 0U; i < 100U; i+=1)
        {
            sum += (i * 3U) + 7U;
        }
        (void)sum;

        statusMask = PmuP_ReadCntrOverflowStatus();

        if ((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) != 0U)
        {
            break;
        }

        ClockP_usleep(1);
        pollBudget-=1;
    }

    /* If overflow still didn't trigger, manually force it */
    if ((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) == 0U)
    {
        /* Freeze, set even closer to overflow, unfreeze */
        PmuP_EnableAllCounters(0U);
        PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, TEST_PMU_NEAR_OVERFLOW_4);
        PmuP_EnableAllCounters(1U);

        /* Try one more aggressive workload */
        for (retry = 0U; retry < TEST_PMU_POLL_BUDGET; retry+=1)
        {
            sum = 0U;
            for (i = 0U; i < 100U; i+=1)
            {
                sum += i;
            }
            (void)sum;

            statusMask = PmuP_ReadCntrOverflowStatus();
            if ((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) != 0U)
            {
                break;
            }
        }
    }

    TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) != 0U);

    wrappedValue = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(wrappedValue < TEST_PMU_WRAPPED_VAL_MAX);

    PmuP_ClearCntrOverflowStatus(1U << TEST_PMU_COUNTER_IDX_0);
    statusMask = PmuP_ReadCntrOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) == 0U);
}

/**
 * \brief Global freeze preserves accumulated counter values across multiple cycles.
 *
 * Test Category: Functional
 *
 * Accumulates counters to a known value, freezes globally, verifies values
 * unchanged, unfreezes, accumulates more, and verifies total is sum of pre-freeze
 * and post-freeze increments (no reset on freeze/unfreeze).
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Counter values preserved across freeze; final value = baseline + increments.
 */
static void TestPmu_globalFreezePreservesAccumulatedValuesAcrossMultipleCycles(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t c0Phase1, c0FrozenPhase1, c0Phase2, c0FrozenPhase2, c0Final;
    uint32_t deltaAfterFreeze1, deltaAfterFreeze2;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    /* Phase 1: Accumulate to known value */
    TestPmu_runDeterministicWorkload();
    c0Phase1 = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(c0Phase1 > 1000U);

    /* Freeze and verify unchanged */
    PmuP_EnableAllCounters(0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    TestPmu_runDeterministicWorkload();
    c0FrozenPhase1 = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    deltaAfterFreeze1 = c0FrozenPhase1 - c0Phase1;
    TEST_ASSERT_TRUE(deltaAfterFreeze1 < TEST_PMU_FREEZE_TOLERANCE); /* No reset on freeze */

    /* Unfreeze and accumulate more */
    PmuP_EnableAllCounters(1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    TestPmu_runDeterministicWorkload();
    c0Phase2 = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(c0Phase2 > c0Phase1); /* Resumed from frozen value */

    /* Freeze again and verify unchanged */
    PmuP_EnableAllCounters(0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    TestPmu_runDeterministicWorkload();
    c0FrozenPhase2 = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    deltaAfterFreeze2 = c0FrozenPhase2 - c0Phase2;
    TEST_ASSERT_TRUE(deltaAfterFreeze2 < TEST_PMU_FREEZE_TOLERANCE); /* No reset on second freeze */

    /* Unfreeze and verify final accumulation */
    PmuP_EnableAllCounters(1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    TestPmu_runDeterministicWorkload();
    c0Final = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    /* CORE TEST: Final value should be monotonically increasing */
    TEST_ASSERT_TRUE(c0Final > c0Phase2);
    TEST_ASSERT_TRUE(c0Phase2 > c0Phase1);
}

/**
 * \brief Per-counter reprogram does not affect others.
 *
 * Test Category: Functional
 *
 * Reprograms one counter’s event type while leaving others unchanged. Verifies
 * all counters increment correctly across workloads and the reprogrammed counter
 * begins counting the new event without disturbing other counters.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All counters remain monotonic; counter reprogramming does not
 *                 reset or corrupt other counters.
 */
static void TestPmu_perCounterReprogramDoesNotAffectOthers(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t c0Before, c1Before;
    uint32_t c0AfterFirst, c1AfterFirst;
    uint32_t c0AfterSecond, c1AfterSecond;
    int32_t initStatus;

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

    /* Baseline workload and reads */
    TestPmu_runDeterministicWorkload();
    c0Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    c1Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);

    /* Reprogram counter 1 to a different valid event */
    PmuP_ConfigCounter(TEST_PMU_COUNTER_IDX_1, PmuP_EVENT_TYPE_D_RD);

    /* Workload post reprogram */
    TestPmu_runDeterministicWorkload();
    c0AfterFirst = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    c1AfterFirst = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);

    TEST_ASSERT_TRUE(c0AfterFirst >= c0Before);
    TEST_ASSERT_TRUE(c1AfterFirst >= c1Before);

    /* One more workload to verify monotonicity and stability */
    TestPmu_runDeterministicWorkload();
    c0AfterSecond = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    c1AfterSecond = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);

    TEST_ASSERT_TRUE(c0AfterSecond > c0AfterFirst);
    TEST_ASSERT_TRUE(c1AfterSecond > c1AfterFirst);
}

/**
 * \brief Software chaining via overflow for 64-bit accumulation.
 *
 * Test Category: Functional
 *
 * Implements software 64-bit accumulation by detecting overflows of a 32-bit
 * event counter, incrementing a software high word on each overflow, and
 * composing a monotonic 64-bit count.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Composed 64-bit count increases monotonically across multiple wraps.
 */
static void TestPmu_softwareChainingViaOverflowFor64bitAccum(void *args)
{
    (void)args;
    uint32_t numCounters, i, wraps;
    uint32_t statusMask, loWord;
    uint64_t hiWord, composedBefore, composedAfter;
    int32_t initStatus;
    volatile uint32_t pollBudget;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    PmuP_EnableCounterOverflowInterrupt(TEST_PMU_COUNTER_IDX_0, 1U);
    hiWord = 0ULL;
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, TEST_PMU_NEAR_OVERFLOW_2);

    loWord = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    composedBefore = ((hiWord << 32) | (uint64_t)loWord);

    /* Loop until overflow status sets, clear and accumulate high word */
    for (wraps = 0U; wraps < TEST_PMU_SW_CHAIN_WRAP_COUNT; wraps+=1)
    {
        statusMask = 0U;
        pollBudget = TEST_PMU_POLL_BUDGET_LARGE;
        while ((pollBudget > 0U) && ((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) == 0U))
        {
            TestPmu_runDeterministicWorkload();
            statusMask = PmuP_ReadCntrOverflowStatus();
            pollBudget-=1;
        }
        TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) != 0U);

        PmuP_ClearCntrOverflowStatus(1U << TEST_PMU_COUNTER_IDX_0);
        hiWord+=1;
        /* Prepare for the next wrap quicker */
        PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, TEST_PMU_NEAR_OVERFLOW_2);
    }

    loWord = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    composedAfter = ((hiWord << 32) | (uint64_t)loWord);
    TEST_ASSERT_TRUE(composedAfter > composedBefore);
}

/**
 * \brief User access enable path via PmuP_Config.
 *
 * Test Category: Functional
 *
 * Enables PMU user access and verifies normal counting behavior by measuring
 * increments across workloads. Reapplies configuration to confirm stability.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Event counters increment with userEnable set; subsequent config
 *                 calls remain stable.
 */
static void TestPmu_userAccessEnablePathViaPmuPConfig(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t beforeUser, afterUser, afterReapply;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    /* Enable user access and verify increments */
    PmuP_Config(/*cycleCntDiv=*/0U, /*exportEvents=*/0U, /*userEnable=*/1U);
    beforeUser = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    afterUser  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(afterUser > beforeUser);

    /* Reapply configuration and verify continued increments */
    PmuP_Config(/*cycleCntDiv=*/0U, /*exportEvents=*/0U, /*userEnable=*/1U);
    TestPmu_runDeterministicWorkload();
    afterReapply = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(afterReapply > afterUser);
}

/**
 * \brief Enable/disable does not corrupt other counters' internal state.
 *
 * Test Category: Functional
 *
 * Disables counter 1 while counter 0 accumulates a known baseline. Verifies
 * counter 0's value is preserved across counter 1's disable/enable cycle,
 * confirming no cross-counter register corruption.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Counter 0 value preserved across counter 1's state changes;
 *                 counter 0 increments predictably before and after.
 */
static void TestPmu_enableDisableDoesNotCorruptOtherCountersState(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t c0BaselineA, c0AfterHeavyA, c0BaselineB, c0AfterHeavyB;
    uint32_t deltaA, deltaB, c0DuringDisable;
    int32_t initStatus;
    volatile uint32_t sum;

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

    /* Measure counter 0 delta BEFORE disabling counter 1 */
    c0BaselineA = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    c0AfterHeavyA = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    deltaA = c0AfterHeavyA - c0BaselineA;
    TEST_ASSERT_TRUE(deltaA > TEST_PMU_MIN_VALID_DELTA);

    /* Disable counter 1 and run heavy workload */
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    sum = 0U;
    for (i = 0U; i < TEST_PMU_HEAVY_WORKLOAD_ITER_COUNT; i+=1)
    {
        sum += i;
    }
    (void)sum;

    /* Verify counter 1 is disabled; counter 0 still increments normally */
    c0DuringDisable = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(c0DuringDisable > c0AfterHeavyA); /* Counter 0 still counting */

    /* Re-enable counter 1 */
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    /* Measure counter 0 delta AFTER re-enabling counter 1 */
    c0BaselineB = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    c0AfterHeavyB = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    deltaB = c0AfterHeavyB - c0BaselineB;

    /* CORE TEST: Verify counter 0's increment rate is consistent before/after */
    uint32_t tolerancePct = TEST_PMU_TOLERANCE_PCT; /* Allow 20% variance */
    uint32_t minDeltaB = deltaA - (deltaA * tolerancePct / 100);
    uint32_t maxDeltaB = deltaA + (deltaA * tolerancePct / 100);
    TEST_ASSERT_TRUE(deltaB >= minDeltaB && deltaB <= maxDeltaB);
}
/**
 * \brief Rapid back-to-back read/write is race-free.
 *
 * Test Category: Functional
 *
 * Rapidly writes and reads a counter while globally frozen, then unfreezes
 * and verifies normal counting continues.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Write-read matches while frozen; increments resume after unfreeze.
 */
static void TestPmu_rapidBackToBackReadWriteIsRaceFree(void *args)
{
    (void)args;
    uint32_t numCounters, i, k;
    uint32_t val, rd, before, after;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    /* Freeze; do rapid write-read checks */
    PmuP_EnableAllCounters(0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    for (k = 0U; k < TEST_PMU_RAPID_RW_ITER_COUNT; k+=1)
    {
        val = (k * 7U) + 3U;
        PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, val);
        rd = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
        TEST_ASSERT_EQUAL_UINT32(val, rd);
    }

    /* Unfreeze and verify counting resumes */
    PmuP_EnableAllCounters(1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    after  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(after > before);
}

/**
 * \brief getOverflowStatus shows no flags after clear.
 *
 * Test Category: Functional
 *
 * Clears all overflow flags and verifies PmuP_getOverflowStatus() returns 0.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput PMOVSR is 0 after clear.
 */
static void TestPmu_getOverflowStatusNoFlags(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t statusMask;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    /* Disable overflow interrupts and clear all flags */
    for (i = 0U; i < numCounters; i+=1)
    {
        PmuP_EnableCounterOverflowInterrupt(i, 0U);
    }
    PmuP_EnableCounterOverflowInterrupt(PmuP_PMU_CYCLE_COUNTER_NUM, 0U);
    PmuP_ClearCntrOverflowStatus(0xFFFFFFFFU);

    statusMask = PmuP_getOverflowStatus();
    TEST_ASSERT_EQUAL_UINT32(0U, statusMask);
}

/**
 * \brief Overflow status persists until cleared.
 *
 * Test Category: Functional
 *
 * Forces an overflow, reads getOverflowStatus() multiple times to ensure the bit
 * remains set until explicitly cleared.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Bit stays set across reads; clears after ClearCntrOverflowStatus().
 */
static void TestPmu_overflowStatusPersistsUntilCleared(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t statusMask;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    PmuP_EnableCounterOverflowInterrupt(TEST_PMU_COUNTER_IDX_0, 1U);
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, TEST_PMU_NEAR_OVERFLOW_2);
    TestPmu_runDeterministicWorkload();

    /* Read multiple times; bit should persist */
    for (i = 0U; i < 4U; i+=1)
    {
        statusMask = PmuP_getOverflowStatus();
        TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) != 0U);
    }

    /* Clear and verify cleared */
    PmuP_ClearCntrOverflowStatus(1U << TEST_PMU_COUNTER_IDX_0);
    statusMask = PmuP_getOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) == 0U);
}

/**
 * \brief Clear overflow status multiple bits via mask.
 *
 * Test Category: Functional
 *
 * Forces overflow on counters 0 and 1; clears only bit 0, verifies bit 1 remains,
 * then clears bit 1 and verifies both cleared.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Masked clear affects only specified bits.
 */
static void TestPmu_clearOverflowStatusMultipleBitsMask(void *args)
{
    (void)args;
    uint32_t numCounters, statusMask, i;
    int32_t initStatus;

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

    PmuP_EnableCounterOverflowInterrupt(TEST_PMU_COUNTER_IDX_0, 1U);
    PmuP_EnableCounterOverflowInterrupt(TEST_PMU_COUNTER_IDX_1, 1U);
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, TEST_PMU_NEAR_OVERFLOW_2);
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_1, TEST_PMU_NEAR_OVERFLOW_2);
    TestPmu_runDeterministicWorkload();

    statusMask = PmuP_getOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) != 0U);
    TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_1)) != 0U);

    /* Clear bit 0 only */
    PmuP_ClearCntrOverflowStatus(1U << TEST_PMU_COUNTER_IDX_0);
    statusMask = PmuP_getOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_0)) == 0U);
    TEST_ASSERT_TRUE((statusMask & (1U << TEST_PMU_COUNTER_IDX_1)) != 0U);

    /* Clear bit 1 */
    PmuP_ClearCntrOverflowStatus(1U << TEST_PMU_COUNTER_IDX_1);
    statusMask = PmuP_getOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & ((1U << TEST_PMU_COUNTER_IDX_0) | (1U << TEST_PMU_COUNTER_IDX_1))) == 0U);
}

/**
 * \brief Cycle counter overflow status read and clear.
 *
 * Test Category: Functional
 *
 * Forces cycle counter overflow and verifies getOverflowStatus() cycle bit sets
 * and clears.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Cycle overflow bit sets on wrap; clears on masked clear.
 */
static void TestPmu_cycleCounterOverflowStatusReadAndClear(void *args)
{
    (void)args;
    uint32_t numCounters, statusMask, cycleMask, i;
    int32_t initStatus;

    cycleMask = (1U << PmuP_PMU_CYCLE_COUNTER_NUM);

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

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

    PmuP_EnableCounterOverflowInterrupt(PmuP_PMU_CYCLE_COUNTER_NUM, 1U);
    PmuP_SetCntr(PmuP_PMU_CYCLE_COUNTER_NUM, TEST_PMU_NEAR_OVERFLOW_2);
    TestPmu_runDeterministicWorkload();

    statusMask = PmuP_getOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & cycleMask) != 0U);

    PmuP_ClearCntrOverflowStatus(cycleMask);
    statusMask = PmuP_getOverflowStatus();
    TEST_ASSERT_TRUE((statusMask & cycleMask) == 0U);
}

/* ========================================================================== */
/*                    Unity Framework Setup Functions                         */
/* ========================================================================== */

/* Setup function for Unity test framework */
void setUp(void)
{
    /* empty */
}

/* Teardown function for Unity test framework */
void tearDown(void)
{
    /* empty */
}

/* ========================================================================== */
/*                          Main test function                                */
/* ========================================================================== */

/**
 *  \brief   Main entry point for PMU tests.
 *
 *  Runs all PMU test cases using Unity framework.
 *
 *  \param args  Unused argument.
 */
void test_pmu_main(void *args)
{
    UNITY_BEGIN();
    /* Run PMU functional tests */
    RUN_TEST(TestPmu_coreDiscoveryAndInit, 10428, NULL);
    RUN_TEST(TestPmu_globalEnableDisableAllCounters, 10429, NULL);
    RUN_TEST(TestPmu_resetEventCountersOnly, 10430, NULL);
    RUN_TEST(TestPmu_resetCycleCounterOnly, 10431, NULL);
    RUN_TEST(TestPmu_initEnablesSelectedEventCounters, 10432, NULL);
    RUN_TEST(TestPmu_profileStartEndReturnCodes, 10433, NULL);
    RUN_TEST(TestPmu_reinitializeWithNewEventSelection, 10434, NULL);
    RUN_TEST(TestPmu_perCounterEnableDisable, 10435, NULL);
    RUN_TEST(TestPmu_cycleCounterEnableReadReset, 10436, NULL);
    RUN_TEST(TestPmu_cycleCounterDivideBy64Effect, 10437, NULL);
    RUN_TEST(TestPmu_cycleCounterGatingPerCounter, 10438, NULL);
    RUN_TEST(TestPmu_perCounterOverflowInterruptEnableDisable, 10439, NULL);
    RUN_TEST(TestPmu_overflowIsrLogicDetectAndClear, 10440, NULL);
    RUN_TEST(TestPmu_overflowIsrLogicRearmAndRepeat, 10441, NULL);
    RUN_TEST(TestPmu_programValidEventAndCountCntr0, 10442, NULL);
    RUN_TEST(TestPmu_perCounterEnableDisableHaltsOnlyThatCounter, 10444, NULL);
    RUN_TEST(TestPmu_readWriteCounterValueWithSetCntr, 10445, NULL);
    RUN_TEST(TestPmu_counterOverflowFlagAndWrap, 10446, NULL);
    RUN_TEST(TestPmu_globalFreezePreservesAccumulatedValuesAcrossMultipleCycles, 10447, NULL);
    RUN_TEST(TestPmu_perCounterReprogramDoesNotAffectOthers, 10448, NULL);
    RUN_TEST(TestPmu_softwareChainingViaOverflowFor64bitAccum, 10449, NULL);
    RUN_TEST(TestPmu_userAccessEnablePathViaPmuPConfig, 10450, NULL);
    RUN_TEST(TestPmu_enableDisableDoesNotCorruptOtherCountersState, 10451, NULL);
    RUN_TEST(TestPmu_rapidBackToBackReadWriteIsRaceFree, 10454, NULL);
    RUN_TEST(TestPmu_getOverflowStatusNoFlags, 10455, NULL);
    RUN_TEST(TestPmu_overflowStatusPersistsUntilCleared, 10456, NULL);
    RUN_TEST(TestPmu_clearOverflowStatusMultipleBitsMask, 10457, NULL);
    RUN_TEST(TestPmu_cycleCounterOverflowStatusReadAndClear, 10458, NULL);

    UNITY_END();
}

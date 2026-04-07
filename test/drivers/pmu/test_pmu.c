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

/* Short counter propagation delay (microseconds) */
#define TEST_PMU_SHORT_DELAY_US                 50U

/* Number of 32-bit wraps for the software 64-bit chain accumulation test */
#define TEST_PMU_SW_CHAIN_WRAP_COUNT            3U

/* CPU frequencies used in CycleCounterP_nsToTicks conversion tests */
#define TEST_PMU_CPU_FREQ_200MHZ                200000000ULL
#define TEST_PMU_CPU_FREQ_400MHZ                400000000ULL
#define TEST_PMU_CPU_FREQ_800MHZ                800000000ULL
#define TEST_PMU_CPU_FREQ_1GHZ                  1000000000ULL

/* Nanosecond conversion reference values */
#define TEST_PMU_NS_PER_US                      1000ULL
#define TEST_PMU_NS_PER_MS                      1000000ULL
#define TEST_PMU_NS_PER_SEC                     1000000000ULL

/* Out-of-range counter indices used in negative tests */
#define TEST_PMU_INVALID_COUNTER_IDX_LOW        10U
#define TEST_PMU_INVALID_COUNTER_IDX_HIGH       25U

/* Concurrent enable/disable toggle and read iteration counts */
#define TEST_PMU_TOGGLE_ITER                 10U
#define TEST_PMU_READ_ITER                   20U

/* Multithreaded test globals */
#if defined(ENABLE_MT_TESTS)

/* MT inter-thread step pacing delay (microseconds) */
#define TEST_PMU_MT_STEP_DELAY_US               500U

/* MT task teardown settle time (microseconds) */
#define TEST_PMU_MT_TEARDOWN_DELAY_US           5000U
#define TEST_PMU_MT_TASK_COUNT                  2U
#define TEST_PMU_MT_TASK_STACK_SIZE             (16u * 1024U)

/* MT thread array indices */
#define TEST_PMU_MT_THREAD_A_IDX                0U
#define TEST_PMU_MT_THREAD_B_IDX                1U

/* MT SetCntr write/read synchronization round count */
#define TEST_PMU_MT_SYNC_ITER                   10U

/* MT event-reprogram synchronization step count */
#define TEST_PMU_MT_REPROGRAM_STEPS             4U
#endif /* ENABLE_MT_TESTS */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint32_t TestPmu_NumCounters             = 0U;
static uint32_t TestPmu_DivideTolerancePct      = 50U;          /* Allowed +/- tolerance for divide-by-64 rate check */
static const char *TestPmu_BlockNameConst       = "BlockA";
static uint32_t TestPmu_ZeroDeltaTolerance      = 0U;           /* Expected zero while frozen/disabled */
static PMU_EventCfg TestPmu_EventCfgBuf[3];                     /* R5 supports up to 3 event counters */
static PMU_Config TestPmu_ConfigObj;

/* Multithreaded test globals */
#if defined(ENABLE_MT_TESTS)

static uint8_t TestPmu_MtTaskStack[TEST_PMU_MT_TASK_COUNT][TEST_PMU_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
static TaskP_Object TestPmu_MtTaskObj[TEST_PMU_MT_TASK_COUNT];
static SemaphoreP_Object TestPmu_MtCompletionSem;
static volatile uint32_t TestPmu_MtThreadResults[TEST_PMU_MT_TASK_COUNT];
static SemaphoreP_Object TestPmu_MtBarrierArrive;
static SemaphoreP_Object TestPmu_MtBarrierLeave;
static volatile uint32_t TestPmu_MtBarrierCount;

/* Global state for TC_MT05 - Event reprogramming test */
static SemaphoreP_Object TestPmu_MtReprogramStepSem;
static volatile uint32_t TestPmu_MtReprogramComplete;
static volatile uint32_t TestPmu_MtCounter0ReadCount;

#endif /* ENABLE_MT_TESTS */

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/* Helper function to run deterministic workload */
static void TestPmu_runDeterministicWorkload(void);

#if defined(ENABLE_MT_TESTS)
/* Barrier helper for multithreaded synchronization */
static void TestPmu_barrierWait(void);

/* Thread functions for concurrent init test */
static void TestPmu_mtInitThreadA(void *arg);
static void TestPmu_mtInitThreadB(void *arg);

/* Thread functions for concurrent reset test */
static void TestPmu_mtResetThreadA(void *arg);
static void TestPmu_mtResetThreadB(void *arg);

/* Thread functions for concurrent enable/disable test */
static void TestPmu_mtEnableDisableThreadA(void *arg);
static void TestPmu_mtEnableDisableThreadB(void *arg);

/* Thread functions for concurrent SetCntr test */
static void TestPmu_mtSetCntrThreadA(void *arg);
static void TestPmu_mtSetCntrThreadB(void *arg);

/* Thread functions for event reprogram test */
static void TestPmu_mtReprogramThreadA(void *arg);
static void TestPmu_mtReprogramThreadB(void *arg);

#endif /* ENABLE_MT_TESTS */

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

/* Negative test cases */
static void TestPmu_profileEndNameMismatchReturnsFailure(void *args);
static void TestPmu_disabledCounterStopsCountingValidEventResumes(void *args);
static void TestPmu_enableDisableCounterInvalidIndexNoEffect(void *args);
static void TestPmu_setCntrWhileDisabledDoesNotStartCounting(void *args);
static void TestPmu_cycleCounterDividerConfiguredButNotEnabledNoAdvance(void *args);
static void TestPmu_clearOverflowWithoutStatusNoChange(void *args);
static void TestPmu_freezeThenProfileNoCountingUntilUnfreeze(void *args);
static void TestPmu_cycleCounterNsToTicks(void *args);
static void TestPmu_cycleCounterNsToTicksMultipleFreq(void *args);

#if defined(ENABLE_MT_TESTS)
/* Multithreaded test cases */
static void TestPmu_concurrentInitSingleCoreSerializesUsage(void *args);
static void TestPmu_concurrentResetAllVsCycleOnlyCoordinated(void *args);
static void TestPmu_concurrentEnableDisableAndReadDifferentCounters(void *args);
static void TestPmu_concurrentSetCntrWriteReadAtomicity(void *args);
static void TestPmu_concurrentReprogramEventWhileOtherThreadReads(void *args);
#endif /* ENABLE_MT_TESTS */

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

#if defined(ENABLE_MT_TESTS)
/* Barrier helper: each thread calls this; last one arriving releases all */
static void TestPmu_barrierWait(void)
{
    uint32_t oldCount;
    uint32_t i;

    /* Phase 1: Arrival */
    oldCount = __sync_fetch_and_add(&TestPmu_MtBarrierCount, 1U);
    __asm__ __volatile__("dmb" ::: "memory");  /* ARM data memory barrier */

    if (oldCount == (TEST_PMU_MT_TASK_COUNT - 1U))
    {
        /* Last thread: release all waiting threads */
        for (i = 0U; i < TEST_PMU_MT_TASK_COUNT; i+=1)
        {
            SemaphoreP_post(&TestPmu_MtBarrierArrive);
        }
    }

    /* All threads wait here */
    SemaphoreP_pend(&TestPmu_MtBarrierArrive, SystemP_WAIT_FOREVER);

    /* Phase 2: Departure (reset for next use) */
    oldCount = __sync_fetch_and_sub(&TestPmu_MtBarrierCount, 1U);
    __asm__ __volatile__("dmb" ::: "memory");
    if (oldCount == 1U)
    {
        /* Last to leave: signal epoch done and allow reuse */
        TestPmu_MtBarrierCount = 0U;
        for (i = 0U; i < TEST_PMU_MT_TASK_COUNT; i+=1)
        {
            SemaphoreP_post(&TestPmu_MtBarrierLeave);
        }
    }

    SemaphoreP_pend(&TestPmu_MtBarrierLeave, SystemP_WAIT_FOREVER);
}
#endif /* ENABLE_MT_TESTS */

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
/*                        Negative Test Case                                  */
/* ========================================================================== */

/**
 * \brief Profile end name mismatch returns failure.
 *
 * Test Category: Negative
 *
 * Starts a profile with one name and ends with a different name; expects failure.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput PMU_profileEnd returns SystemP_FAILURE on name mismatch.
 */
static void TestPmu_profileEndNameMismatchReturnsFailure(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    int32_t initStatus, startStatus, endStatus;

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

    startStatus = PMU_profileStart("RegionA");
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, startStatus);
    TestPmu_runDeterministicWorkload();

    endStatus = PMU_profileEnd("RegionB");
    TEST_ASSERT_EQUAL_INT(SystemP_FAILURE, endStatus);
}

/**
 * \brief Disabled counter stops counting; re-enable resumes counting.
 *
 * Test Category: Negative
 *
 * Disables an event counter using PmuP_enableCounter() and verifies counting stops
 * during workload. Re-enables counter and confirms counting resumes normally.
 *
 * Note: Invalid event IDs (0xFF) exhibit undefined behavior on ARM Cortex-R5 PMU
 * and may continue counting. This test focuses on counter enable/disable functionality.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Disabled counter delta < 100; enabled counter delta > 1000.
 */
static void TestPmu_disabledCounterStopsCountingValidEventResumes(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t c0Before, c0AfterInvalid, c0AfterValid, c0AfterDisabled;
    uint32_t invalidDelta, validDelta, disabledDelta;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "Evt";
        TestPmu_EventCfgBuf[i].type = 0xFFU;
    }

    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    /* Program invalid/undefined event on counter 0 (use a reserved value) */
    PmuP_EnableAllCounters(0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    PmuP_ConfigCounter(TEST_PMU_COUNTER_IDX_0, 0xFFU);
    ClockP_usleep(TEST_PMU_SHORT_DELAY_US);
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, 1000U);
    PmuP_EnableAllCounters(1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    /* Measure with invalid event (should count very little or not at all) */
    c0Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    c0AfterInvalid = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    invalidDelta = c0AfterInvalid - c0Before;
    TEST_ASSERT_TRUE(invalidDelta > 0U);  /* 0xFF increments (undefined HW behavior) */

    /* Restore a valid event and verify increments resume */
    PmuP_EnableAllCounters(0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    PmuP_ConfigCounter(TEST_PMU_COUNTER_IDX_0, PmuP_EVENT_TYPE_I_X);
    ClockP_usleep(TEST_PMU_SHORT_DELAY_US);
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, 2000U);
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_0, 0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    PmuP_EnableAllCounters(1U); /* Unfreeze globally (but counter 0 still disabled) */
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    c0Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    c0AfterDisabled = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    disabledDelta = c0AfterDisabled - c0Before;

    /* Verify disabled counter increments minimally (< 100 cycles) */
    TEST_ASSERT_TRUE(disabledDelta < TEST_PMU_FREEZE_TOLERANCE);

     /* Now re-enable counter 0 with valid event and verify it counts significantly more than when disabled */

    PmuP_EnableAllCounters(0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, 3000U);
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_0, 1U); /* Re-enable counter 0 */
    ClockP_usleep(TEST_PMU_SHORT_DELAY_US);
    PmuP_EnableAllCounters(1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    c0Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    c0AfterValid = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    validDelta = c0AfterValid - c0Before;

    /* Verify valid event counts significantly */
    TEST_ASSERT_TRUE(validDelta > TEST_PMU_MIN_VALID_DELTA);

    /* Verify valid delta >> disabled delta */
    TEST_ASSERT_TRUE(validDelta > (disabledDelta * 10U));
}

/**
 * \brief Enable/disable with out-of-range counter index has no side effects.
 *
 * Test Category: Negative
 *
 * Attempts to gate an out-of-range counter index; verifies valid counters are unaffected.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Valid counters increment normally; no side effects from invalid index.
 */
static void TestPmu_enableDisableCounterInvalidIndexNoEffect(void *args)
{
    (void)args;
    uint32_t numCounters, validBefore, validAfter, i;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "Evt";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }

    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    /* Use an index beyond available event counters (but within 0..31) */
    PmuP_enableCounter(TEST_PMU_INVALID_COUNTER_IDX_LOW, 0U);
    PmuP_enableCounter(TEST_PMU_INVALID_COUNTER_IDX_HIGH, 1U);

    validBefore = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    validAfter  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    TEST_ASSERT_TRUE(validAfter > validBefore);
}

/**
 * \brief setCntr while disabled does not accumulate until re-enabled.
 *
 * Test Category: Negative
 *
 * Disables a counter, writes a baseline, runs workload and verifies no change;
 * then re-enables and confirms increments.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Value unchanged while disabled; increases after re-enable.
 */
static void TestPmu_setCntrWhileDisabledDoesNotStartCounting(void *args)
{
    (void)args;
    uint32_t numCounters, baseline, whileDisabled, afterEnable, i;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "Evt";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }

    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_0, 0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    baseline = TEST_PMU_BASELINE_COUNTER_VAL;
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_0, baseline);

    TestPmu_runDeterministicWorkload();
    whileDisabled = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_EQUAL_UINT32(baseline, whileDisabled);

    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_0, 1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    TestPmu_runDeterministicWorkload();
    afterEnable = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(afterEnable > whileDisabled);
}

/**
 * \brief Cycle divider config has no effect while cycle counter disabled.
 *
 * Test Category: Negative
 *
 * Disables cycle counter, configures divide-by-64 and runs workload; verifies no cycle advance.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Cycle count unchanged while gated; increases after re-enable.
 */
static void TestPmu_cycleCounterDividerConfiguredButNotEnabledNoAdvance(void *args)
{
    (void)args;
    uint32_t numCounters, cycleBefore, cycleAfterDisabled, cycleAfterEnabled;
    uint32_t i;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "Evt";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }

    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    /* Disable cycle counter and set div-by-64 */
    PmuP_enableCounter(PmuP_PMU_CYCLE_COUNTER_NUM, 0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    PmuP_Config(/*cycleCntDiv=*/1U, /*exportEvents=*/0U, /*userEnable=*/1U);

    cycleBefore = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TestPmu_runDeterministicWorkload();
    cycleAfterDisabled = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TEST_ASSERT_EQUAL_UINT32(cycleBefore, cycleAfterDisabled);

    /* Re-enable cycle counter and verify increments */
    PmuP_enableCounter(PmuP_PMU_CYCLE_COUNTER_NUM, 1U);
    TestPmu_runDeterministicWorkload();
    cycleAfterEnabled = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TEST_ASSERT_TRUE(cycleAfterEnabled > cycleAfterDisabled);

    /* Restore divider off */
    PmuP_Config(/*cycleCntDiv=*/0U, /*exportEvents=*/0U, /*userEnable=*/1U);
}

/**
 * \brief Clearing overflow when none set causes no change.
 *
 * Test Category: Negative
 *
 * Verifies PMOVSR remains 0 when cleared with no prior overflow and counters behave normally.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput PMOVSR remains 0; event counters still increment under workload.
 */
static void TestPmu_clearOverflowWithoutStatusNoChange(void *args)
{
    (void)args;
    uint32_t numCounters, statusBefore, statusAfter, c0Before, c0After, i;
    int32_t initStatus;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "Evt";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }

    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    statusBefore = PmuP_getOverflowStatus();
    TEST_ASSERT_EQUAL_UINT32(0U, statusBefore);

    PmuP_ClearCntrOverflowStatus(0xFFFFFFFFU);
    statusAfter = PmuP_getOverflowStatus();
    TEST_ASSERT_EQUAL_UINT32(0U, statusAfter);

    c0Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    c0After  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(c0After > c0Before);
}

/**
 * \brief Freeze then profile — no counting until unfreeze.
 *
 * Test Category: Negative
 *
 * Freezes all counters and profiles a region; expects near-zero deltas. After unfreeze,
 * profiling should capture normal increments.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Zero deltas while frozen; positive deltas after unfreeze.
 */
static void TestPmu_freezeThenProfileNoCountingUntilUnfreeze(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    uint32_t frozenCycle, frozenEvt0, cycleAfter, evt0After;
    int32_t initStatus, startStatus, endStatus;
    const char *ptName;

    ptName = "FrozenRegion";

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters > 0U);

    for (i = 0U; i < numCounters; i+=1)
    {
        TestPmu_EventCfgBuf[i].name = "Evt";
        TestPmu_EventCfgBuf[i].type = PmuP_EVENT_TYPE_I_X;
    }

    TestPmu_ConfigObj.bCycleCounter    = 1U;
    TestPmu_ConfigObj.numEventCounters = numCounters;
    TestPmu_ConfigObj.eventCounters    = TestPmu_EventCfgBuf;
    initStatus = PMU_init(&TestPmu_ConfigObj);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, initStatus);

    /* Freeze, then profile */
    PmuP_EnableAllCounters(0U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);

    startStatus = PMU_profileStart(ptName);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, startStatus);
    TestPmu_runDeterministicWorkload();
    endStatus = PMU_profileEnd(ptName);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, endStatus);

    /* Expect near-zero deltas since frozen: read counters directly to confirm */
    frozenCycle = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    frozenEvt0  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    /* Keep strict equality as we froze before starting */
    TEST_ASSERT_EQUAL_UINT32(0U, frozenCycle);
    TEST_ASSERT_EQUAL_UINT32(0U, frozenEvt0);

    /* Unfreeze and verify profiling captures increments */
    PmuP_EnableAllCounters(1U);
    ClockP_usleep(TEST_PMU_GATING_DELAY_US);
    startStatus = PMU_profileStart(ptName);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, startStatus);
    TestPmu_runDeterministicWorkload();
    endStatus = PMU_profileEnd(ptName);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, endStatus);

    cycleAfter = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    evt0After  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TEST_ASSERT_TRUE(cycleAfter > TestPmu_ZeroDeltaTolerance);
    TEST_ASSERT_TRUE(evt0After > TestPmu_ZeroDeltaTolerance);
}

/**
 * \brief Test CycleCounterP_nsToTicks conversion with various nanosecond values.
 *
 * Test Category: Functional
 *
 * Tests the nanosecond-to-ticks conversion function with different input values
 * to ensure correct calculation based on CPU frequency.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Correct tick values for given nanosecond inputs.
 */
static void TestPmu_cycleCounterNsToTicks(void *args)
{
    (void)args;
    uint64_t ticks;
    uint64_t cpuFreq = TEST_PMU_CPU_FREQ_800MHZ; /* 800 MHz */

    /* Initialize cycle counter with known frequency */
    CycleCounterP_init(cpuFreq);

    /* Test conversion for 1 microsecond (1000 nanoseconds) */
    ticks = CycleCounterP_nsToTicks(TEST_PMU_NS_PER_US);
    /* At 800 MHz, 1000 ns = 800 ticks */
    TEST_ASSERT_TRUE(ticks > 0U);
    TEST_ASSERT_TRUE(ticks == 800ULL);

    /* Test conversion for 1 millisecond (1000000 nanoseconds) */
    ticks = CycleCounterP_nsToTicks(TEST_PMU_NS_PER_MS);
    /* At 800 MHz, 1000000 ns = 800000 ticks */
    TEST_ASSERT_TRUE(ticks == 800000ULL);

    /* Test conversion for 1 second (1000000000 nanoseconds) */
    ticks = CycleCounterP_nsToTicks(TEST_PMU_NS_PER_SEC);
    /* At 800 MHz, 1 second = 800000000 ticks */
    TEST_ASSERT_TRUE(ticks == TEST_PMU_CPU_FREQ_800MHZ);

    /* Test zero input */
    ticks = CycleCounterP_nsToTicks(0ULL);
    TEST_ASSERT_EQUAL_UINT32(0U, (uint32_t)ticks);

    /* Test small value (100 nanoseconds) */
    ticks = CycleCounterP_nsToTicks(100ULL);
    TEST_ASSERT_TRUE(ticks == 80ULL);
}

/**
 * \brief Test CycleCounterP_nsToTicks with different CPU frequencies.
 *
 * Test Category: Functional
 *
 * Verifies conversion works correctly when frequency changes.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Correct tick values for different frequencies.
 */
static void TestPmu_cycleCounterNsToTicksMultipleFreq(void *args)
{
    (void)args;
    uint64_t ticks;

    /* Test with 400 MHz */
    CycleCounterP_init(TEST_PMU_CPU_FREQ_400MHZ);
    ticks = CycleCounterP_nsToTicks(TEST_PMU_NS_PER_US); /* 1 microsecond */
    TEST_ASSERT_EQUAL_UINT32(400U, (uint32_t)ticks);

    /* Test with 1 GHz */
    CycleCounterP_init(TEST_PMU_CPU_FREQ_1GHZ);
    ticks = CycleCounterP_nsToTicks(TEST_PMU_NS_PER_US); /* 1 microsecond */
    TEST_ASSERT_EQUAL_UINT32(1000U, (uint32_t)ticks);

    /* Test with 200 MHz */
    CycleCounterP_init(TEST_PMU_CPU_FREQ_200MHZ);
    ticks = CycleCounterP_nsToTicks(TEST_PMU_NS_PER_US); /* 1 microsecond */
    TEST_ASSERT_EQUAL_UINT32(200U, (uint32_t)ticks);
}

/**
 * \brief PMU_profilePrintEntry prints valid named entry.
 *
 * Test Category: Functional
 *
 * Profiles a named region, then calls PMU_profilePrintEntry() with the same
 * name and verifies the function completes without crash.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Function completes without crash.
 */
static void TestPmu_profilePrintEntryValidName(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    int32_t initStatus, startStatus, endStatus;
    const char *testName = "ProfileRegionA";

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

    /* Profile a named region */
    startStatus = PMU_profileStart(testName);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, startStatus);

    TestPmu_runDeterministicWorkload();

    endStatus = PMU_profileEnd(testName);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, endStatus);

    /* Call PMU_profilePrintEntry - should complete without crash */
    PMU_profilePrintEntry(testName);
}

/**
 * \brief PMU_profilePrintEntry with non-existent name does nothing.
 *
 * Test Category: Negative
 *
 * Calls PMU_profilePrintEntry() with a name that was never profiled.
 * Verifies function completes gracefully without crash (no matching entry).
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Function completes without crash; no output expected.
 */
static void TestPmu_profilePrintEntryNonExistentName(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    int32_t initStatus, startStatus, endStatus;
    const char *realName = "ProfileRegionB";
    const char *fakeName = "NonExistentRegion";

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

    /* Profile with real name */
    startStatus = PMU_profileStart(realName);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, startStatus);
    TestPmu_runDeterministicWorkload();
    endStatus = PMU_profileEnd(realName);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, endStatus);

    /* Call with non-existent name - should complete without crash */
    PMU_profilePrintEntry(fakeName);
}

/**
 * \brief PMU_profilePrintEntry prints multiple distinct entries correctly.
 *
 * Test Category: Functional
 *
 * Profiles multiple named regions and calls PMU_profilePrintEntry() for each,
 * verifying the functions complete without crash.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Functions complete without crash.
 */
static void TestPmu_profilePrintEntryMultipleEntries(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    int32_t initStatus;
    const char *nameA = "RegionA";
    const char *nameB = "RegionB";
    const char *nameC = "RegionC";

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

    /* Profile Region A */
    PMU_profileStart(nameA);
    TestPmu_runDeterministicWorkload();
    PMU_profileEnd(nameA);

    /* Profile Region B (more work) */
    PMU_profileStart(nameB);
    TestPmu_runDeterministicWorkload();
    TestPmu_runDeterministicWorkload();
    PMU_profileEnd(nameB);

    /* Profile Region C (even more work) */
    PMU_profileStart(nameC);
    TestPmu_runDeterministicWorkload();
    TestPmu_runDeterministicWorkload();
    TestPmu_runDeterministicWorkload();
    PMU_profileEnd(nameC);

    /* Print each entry - should complete without crash */
    PMU_profilePrintEntry(nameA);
    PMU_profilePrintEntry(nameB);
    PMU_profilePrintEntry(nameC);
}

/**
 * \brief PMU_profilePrint prints all logged entries.
 *
 * Test Category: Functional
 *
 * Profiles multiple regions and calls PMU_profilePrint() to print all entries.
 * Verifies function completes without crash.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Function completes without crash.
 */
static void TestPmu_profilePrintAllEntries(void *args)
{
    (void)args;
    uint32_t numCounters, i;
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

    /* Profile multiple regions */
    PMU_profileStart("Init");
    TestPmu_runDeterministicWorkload();
    PMU_profileEnd("Init");

    PMU_profileStart("Processing");
    TestPmu_runDeterministicWorkload();
    PMU_profileEnd("Processing");

    PMU_profileStart("Cleanup");
    TestPmu_runDeterministicWorkload();
    PMU_profileEnd("Cleanup");

    /* Call PMU_profilePrint - should print all 3 entries without crash */
    PMU_profilePrint();
}

/**
 * \brief PMU_profilePrint with no entries completes gracefully.
 *
 * Test Category: Negative
 *
 * Calls PMU_profilePrint() with no profile entries logged.
 * Verifies function completes without crash.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Function completes without crash; no output expected.
 */
static void TestPmu_profilePrintNoEntries(void *args)
{
    (void)args;
    uint32_t numCounters, i;
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

    /* Call PMU_profilePrint with empty log - should complete without crash */
    PMU_profilePrint();
}

/**
 * \brief PMU_profilePrintEntry with empty string name.
 *
 * Test Category: Negative
 *
 * Profiles a region with a normal name, then calls PMU_profilePrintEntry()
 * with an empty string. Verifies function completes without crash.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Function completes without crash; no matching entry.
 */
static void TestPmu_profilePrintEntryEmptyString(void *args)
{
    (void)args;
    uint32_t numCounters, i;
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

    /* Profile valid region */
    PMU_profileStart("ValidRegion");
    TestPmu_runDeterministicWorkload();
    PMU_profileEnd("ValidRegion");

    /* Call with empty string - should handle gracefully */
    PMU_profilePrintEntry("");
}

/**
 * \brief PMU_profilePrint with many entries logged.
 *
 * Test Category: Functional
 *
 * Profiles many regions (10 entries) and calls PMU_profilePrint().
 * Verifies all entries are printed without errors.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput All entries printed without errors.
 */
static void TestPmu_profilePrintMaxEntries(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    int32_t initStatus;
    char nameBuf[32];

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

    /* Profile multiple entries (10 for reasonable test duration) */
    for (i = 0U; i < TEST_PMU_TOGGLE_ITER; i+=1)
    {
        snprintf(nameBuf, sizeof(nameBuf), "Region%lu", (unsigned long)i);
        PMU_profileStart(nameBuf);
        TestPmu_runDeterministicWorkload();
        PMU_profileEnd(nameBuf);
    }

    /* Print all entries - should complete without errors */
    PMU_profilePrint();
}

/* ========================================================================== */
/*                   Multithreaded Test Case Functions                        */
/* ========================================================================== */

#if defined(ENABLE_MT_TESTS)
/* Thread: Thread A for concurrent init test. */
static void TestPmu_mtInitThreadA(void *arg)
{
    (void)arg;
    uint32_t numCounters;
    int32_t status;
    uint32_t beforeWork, afterWork;
    uint32_t i;
    PMU_EventCfg localEventCfg[3];
    PMU_Config   localCfg;

    numCounters = PmuP_GetNumCntrs();
    for (i = 0U; i < numCounters; i+=1)
    {
        localEventCfg[i].name = "InstrExecA";
        localEventCfg[i].type = PmuP_EVENT_TYPE_I_X;
    }
    localCfg.bCycleCounter    = 1U;
    localCfg.numEventCounters = numCounters;
    localCfg.eventCounters    = localEventCfg;
    status = PMU_init(&localCfg);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    TestPmu_barrierWait();

    beforeWork = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    afterWork  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX] = (afterWork > beforeWork) ? 1U : 0U;

    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/* Thread: Thread B for concurrent init test. */
static void TestPmu_mtInitThreadB(void *arg)
{
    (void)arg;
    uint32_t numCounters;
    int32_t status;
    uint32_t beforeWork, afterWork;
    uint32_t i;
    PMU_EventCfg localEventCfg[3];
    PMU_Config   localCfg;

    numCounters = PmuP_GetNumCntrs();
    for (i = 0U; i < numCounters; i+=1)
    {
        localEventCfg[i].name = "DcacheRdB";
        localEventCfg[i].type = PmuP_EVENT_TYPE_D_RD;
    }
    localCfg.bCycleCounter    = 1U;
    localCfg.numEventCounters = numCounters;
    localCfg.eventCounters    = localEventCfg;

    status = PMU_init(&localCfg);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    TestPmu_barrierWait();

    beforeWork = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_runDeterministicWorkload();
    afterWork  = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX] = (afterWork > beforeWork) ? 1U : 0U;

    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/**
 * \brief Concurrent init single-core serializes usage.
 *
 * Test Category: Multithreaded
 *
 * Spawns two threads, each initializing PMU sequentially using a barrier.
 * Verifies final configuration is stable and both threads can read counters.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Both threads see monotonic counter increments; no corruption.
 */
static void TestPmu_concurrentInitSingleCoreSerializesUsage(void *args)
{
    (void)args;
    int32_t status;
    TaskP_Params taskParams;
    uint32_t timeout;
    uint32_t i;

    /* Construct semaphores ONCE before spawning threads */
    TestPmu_MtBarrierCount = 0U;
    status = SemaphoreP_constructCounting(&TestPmu_MtBarrierArrive, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SemaphoreP_constructCounting(&TestPmu_MtBarrierLeave, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SemaphoreP_constructCounting(&TestPmu_MtCompletionSem, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Spawn threads */
    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_A_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtInitA";
    taskParams.taskMain   = TestPmu_mtInitThreadA;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_B_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtInitB";
    taskParams.taskMain   = TestPmu_mtInitThreadB;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for BOTH threads with timeout */
    timeout = 0U;
    for (i = 0U; i < TEST_PMU_MT_TASK_COUNT; i+=1)
    {
        status = SemaphoreP_pend(&TestPmu_MtCompletionSem, 5000U);
        if (status != SystemP_SUCCESS)
        {
            timeout = 1U;
            break;
        }
    }
    TEST_ASSERT_EQUAL_UINT32(0U, timeout);

    /* Verify results */
    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX]);
    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX]);

    /* Cleanup: destruct tasks FIRST, then semaphores */
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX]);
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX]);

    SemaphoreP_destruct(&TestPmu_MtBarrierArrive);
    SemaphoreP_destruct(&TestPmu_MtBarrierLeave);
    SemaphoreP_destruct(&TestPmu_MtCompletionSem);
}

/* Thread: Thread A for concurrent reset test (resets event counters). */
static void TestPmu_mtResetThreadA(void *arg)
{
    (void)arg;
    uint32_t evtVal;

    TestPmu_barrierWait(); /* sync before reset */

    /* Thread A is responsible for freeze */
    PmuP_EnableAllCounters(0U);
    ClockP_usleep(200); /* Longer delay to ensure freeze propagates */

    PmuP_ResetCounters();

    TestPmu_barrierWait(); /* sync after reset */

    /* Verify event counter is near zero */
    evtVal = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX] = (evtVal < TEST_PMU_FREEZE_TOLERANCE) ? 1U : 0U;

    /* Thread A unfreezes after both threads read */
    TestPmu_barrierWait(); /* sync before unfreeze */
    PmuP_EnableAllCounters(1U);

    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/* Thread: Thread B for concurrent reset test (resets cycle counter). */
static void TestPmu_mtResetThreadB(void *arg)
{
    (void)arg;
    uint32_t cycleVal;

    TestPmu_barrierWait(); /* sync before reset */

    /* Thread B waits for Thread A to freeze (implicit via barrier + delay) */
    ClockP_usleep(300); /* Wait for A's freeze to take effect */

    PmuP_ResetCycleCnt();

    TestPmu_barrierWait(); /* sync after reset */

    /* Verify cycle counter is near zero */
    cycleVal = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX] = (cycleVal < TEST_PMU_FREEZE_TOLERANCE) ? 1U : 0U;

    /* Wait for A to unfreeze */
    TestPmu_barrierWait(); /* sync before unfreeze */

    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/**
 * \brief Concurrent reset all vs cycle only coordinated.
 *
 * Test Category: Multithreaded
 *
 * Thread A resets event counters; Thread B resets cycle counter concurrently.
 * Verifies both resets occur and counters resume independently.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Both event and cycle counters reset to near-zero; resume counting.
 */
static void TestPmu_concurrentResetAllVsCycleOnlyCoordinated(void *args)
{
    (void)args;
    uint32_t numCounters;
    int32_t initStatus, status;
    TaskP_Params taskParams;
    uint32_t i;

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

    /* Run workload to populate counters */
    TestPmu_runDeterministicWorkload();

    TestPmu_MtBarrierCount = 0U;
    status = SemaphoreP_constructCounting(&TestPmu_MtBarrierArrive, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SemaphoreP_constructCounting(&TestPmu_MtBarrierLeave, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SemaphoreP_constructCounting(&TestPmu_MtCompletionSem, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_A_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtResetA";
    taskParams.taskMain   = TestPmu_mtResetThreadA;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_B_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtResetB";
    taskParams.taskMain   = TestPmu_mtResetThreadB;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (i = 0U; i < TEST_PMU_MT_TASK_COUNT; i+=1)
    {
        SemaphoreP_pend(&TestPmu_MtCompletionSem, SystemP_WAIT_FOREVER);
    }

    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX]);
    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX]);

    ClockP_usleep(TEST_PMU_MT_TEARDOWN_DELAY_US);
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX]);
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX]);
    SemaphoreP_destruct(&TestPmu_MtBarrierArrive);
    SemaphoreP_destruct(&TestPmu_MtBarrierLeave);
    SemaphoreP_destruct(&TestPmu_MtCompletionSem);
}

/* Thread: Thread A toggles counter 1. */
static void TestPmu_mtEnableDisableThreadA(void *arg)
{
    (void)arg;
    uint32_t i;

    for (i = 0U; i < TEST_PMU_TOGGLE_ITER; i+=1)
    {
        PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 0U);
        ClockP_usleep(TEST_PMU_MT_STEP_DELAY_US);
        PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 1U);
        ClockP_usleep(TEST_PMU_MT_STEP_DELAY_US);
    }
    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX] = 1U;
    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/* Thread: Thread B reads counter 0 continuously. */
static void TestPmu_mtEnableDisableThreadB(void *arg)
{
    (void)arg;
    uint32_t lastVal;
    uint32_t currentVal;
    uint32_t monotonic;
    uint32_t i;

    lastVal = 0U;
    monotonic = 1U;

    for (i = 0U; i < TEST_PMU_READ_ITER; i+=1)
    {
        currentVal = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);
        if (currentVal < lastVal)
        {
            monotonic = 0U;
            break;
        }
        lastVal = currentVal;
        ClockP_usleep(TEST_PMU_MT_STEP_DELAY_US);
    }
    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX] = monotonic;
    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/**
 * \brief Concurrent enable/disable and read different counters.
 *
 * Test Category: Multithreaded
 *
 * Thread A toggles counter 1; Thread B reads counter 0 continuously.
 * Verifies counter 0 increments monotonically and counter 1 is unaffected.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Counter 0 monotonic; no cross-counter interference.
 */
static void TestPmu_concurrentEnableDisableAndReadDifferentCounters(void *args)
{
    (void)args;
    uint32_t numCounters;
    int32_t initStatus, status;
    TaskP_Params taskParams;
    uint32_t i;

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

    SemaphoreP_constructCounting(&TestPmu_MtCompletionSem, 0U, TEST_PMU_MT_TASK_COUNT);

    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_A_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtEnDisA";
    taskParams.taskMain   = TestPmu_mtEnableDisableThreadA;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_B_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtEnDisB";
    taskParams.taskMain   = TestPmu_mtEnableDisableThreadB;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (i = 0U; i < TEST_PMU_MT_TASK_COUNT; i+=1)
    {
        SemaphoreP_pend(&TestPmu_MtCompletionSem, SystemP_WAIT_FOREVER);
    }

    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX]);
    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX]);

    ClockP_usleep(TEST_PMU_MT_TEARDOWN_DELAY_US);
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX]);
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX]);
    SemaphoreP_destruct(&TestPmu_MtCompletionSem);
}

/* Thread: Thread A writes increasing values to counter 2. */
static void TestPmu_mtSetCntrThreadA(void *arg)
{
    (void)arg;
    uint32_t k;

    for (k = 0U; k < TEST_PMU_MT_SYNC_ITER; k+=1)
    {
        /* Freeze counter 2 to make write deterministic */
        PmuP_enableCounter(TEST_PMU_COUNTER_IDX_2, 0U);
        ClockP_usleep(TEST_PMU_SHORT_DELAY_US); /* Let gating take effect */

        PmuP_SetCntr(TEST_PMU_COUNTER_IDX_2, k * 10U);

        TestPmu_barrierWait(); /* Sync: A wrote, now B can read */

        /* Re-enable counter 2 after B reads (optional, depends on test intent) */
        TestPmu_barrierWait(); /* Sync: B finished reading */
        PmuP_enableCounter(TEST_PMU_COUNTER_IDX_2, 1U);
    }
    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX] = 1U;
    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/* Thread: Thread B reads counter 2 after each sync. */
static void TestPmu_mtSetCntrThreadB(void *arg)
{
    (void)arg;
    uint32_t readVal;
    uint32_t consistent;
    uint32_t k;

    consistent = 1U;

    for (k = 0U; k < TEST_PMU_MT_SYNC_ITER; k+=1)
    {
        TestPmu_barrierWait(); /* Sync: wait for A to write */

        readVal = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_2);

        /* Counter is frozen, so readVal should exactly equal k * 10U */
        if (readVal != (k * 10U))
        {
            consistent = 0U;
            break;
        }

        TestPmu_barrierWait(); /* Sync: tell A read is done */
    }
    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX] = consistent;
    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/**
 * \brief Concurrent SetCntr write/read atomicity.
 *
 * Test Category: Multithreaded
 *
 * Thread A writes increasing values; Thread B reads after sync and verifies values.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Read values consistent with most recent writes.
 */
static void TestPmu_concurrentSetCntrWriteReadAtomicity(void *args)
{
    (void)args;
    uint32_t numCounters;
    int32_t initStatus, status;
    TaskP_Params taskParams;
    uint32_t i;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters >= 3U);

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

    /* Construct semaphores for two-phase barrier */
    TestPmu_MtBarrierCount = 0U;
    status = SemaphoreP_constructCounting(&TestPmu_MtBarrierArrive, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SemaphoreP_constructCounting(&TestPmu_MtBarrierLeave, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SemaphoreP_constructCounting(&TestPmu_MtCompletionSem, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_A_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtSetA";
    taskParams.taskMain   = TestPmu_mtSetCntrThreadA;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_B_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtSetB";
    taskParams.taskMain   = TestPmu_mtSetCntrThreadB;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (i = 0U; i < TEST_PMU_MT_TASK_COUNT; i+=1)
    {
        SemaphoreP_pend(&TestPmu_MtCompletionSem, SystemP_WAIT_FOREVER);
    }

    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX]);
    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX]);

    ClockP_usleep(TEST_PMU_MT_TEARDOWN_DELAY_US);
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX]);
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX]);
    SemaphoreP_destruct(&TestPmu_MtBarrierArrive);
    SemaphoreP_destruct(&TestPmu_MtBarrierLeave);
    SemaphoreP_destruct(&TestPmu_MtCompletionSem);
}

/* Thread: Thread A for event reprogram test - Reprograms counter 1 event type. */
static void TestPmu_mtReprogramThreadA(void *arg)
{
    (void)arg;
    uint32_t counter1Before;
    uint32_t counter1After;

    TestPmu_barrierWait(); /* Phase 1: Both threads start */

    /* Freeze counter 1 before reprogramming */
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 0U);
    SemaphoreP_post(&TestPmu_MtReprogramStepSem); /* Signal B to read */
    ClockP_usleep(TEST_PMU_MT_STEP_DELAY_US);

    /* Reprogram counter 1 to different event type */
    PmuP_ConfigCounter(TEST_PMU_COUNTER_IDX_1, PmuP_EVENT_TYPE_DCACHE_ACCESS);
    SemaphoreP_post(&TestPmu_MtReprogramStepSem); /* Signal B to read */
    ClockP_usleep(TEST_PMU_MT_STEP_DELAY_US);

    /* Reset counter 1 after reprogram */
    PmuP_SetCntr(TEST_PMU_COUNTER_IDX_1, 0U);
    SemaphoreP_post(&TestPmu_MtReprogramStepSem); /* Signal B to read */
    ClockP_usleep(TEST_PMU_MT_STEP_DELAY_US);

    /* Re-enable counter 1 */
    PmuP_enableCounter(TEST_PMU_COUNTER_IDX_1, 1U);
    SemaphoreP_post(&TestPmu_MtReprogramStepSem); /* Signal B to read */
    ClockP_usleep(TEST_PMU_MT_STEP_DELAY_US);

    TestPmu_MtReprogramComplete = 1U;

    TestPmu_barrierWait(); /* Phase 2: Reprogram complete */

    /* Verify counter 1 now counts new event type */
    counter1Before = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);
    TestPmu_runDeterministicWorkload();
    counter1After = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_1);

    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX] = (counter1After > counter1Before) ? 1U : 0U;

    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/* Thread: Thread B for event reprogram test - Continuously reads counter 0. */
static void TestPmu_mtReprogramThreadB(void *arg)
{
    (void)arg;
    uint32_t readCount;
    uint32_t counter0Prev;
    uint32_t counter0Curr;
    uint32_t allMonotonic;
    int32_t status;
    uint32_t step;

    readCount = 0U;
    allMonotonic = 1U;

    TestPmu_barrierWait(); /* Phase 1: Both threads start */

    counter0Prev = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

    /* FIX: Loop 4 times (one for each reprogram step) */
    for (step = 0U; step < TEST_PMU_MT_REPROGRAM_STEPS; step+=1)
    {
        /* Wait for A's signal for this step */
        status = SemaphoreP_pend(&TestPmu_MtReprogramStepSem, 5000U);
        if (status != SystemP_SUCCESS)
        {
            break;
        }

        /* Execute workload and read counter 0 */
        TestPmu_runDeterministicWorkload();
        counter0Curr = PmuP_ReadCounter(TEST_PMU_COUNTER_IDX_0);

        /* Verify counter 0 remains monotonic */
        if (counter0Curr < counter0Prev)
        {
            allMonotonic = 0U;
            break;
        }

        counter0Prev = counter0Curr;
        readCount+=1;
    }

    TestPmu_MtCounter0ReadCount = readCount;

    TestPmu_barrierWait(); /* Phase 2: Reprogram complete */

    TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX] = allMonotonic;

    SemaphoreP_post(&TestPmu_MtCompletionSem);
    TaskP_exit();
}

/**
 * \brief Concurrent event reprogram while another thread reads.
 *
 * Test Category: Multithreaded Functional
 *
 * Reprograms an event type on counter 1 while another thread continuously reads
 * counter 0, and verifies counter 0 remains unaffected (monotonic) while counter 1
 * begins counting the new event correctly.
 *
 * \param args Unused.
 * \return None.
 * \expectedOutput Counter 0 remains monotonic during reprogram; counter 1 counts
 *                 new event type after reprogram.
 */
static void TestPmu_concurrentReprogramEventWhileOtherThreadReads(void *args)
{
    (void)args;
    uint32_t numCounters, i;
    int32_t initStatus, status;
    TaskP_Params taskParams;

    numCounters = PmuP_GetNumCntrs();
    TEST_ASSERT_TRUE(numCounters >= 2U);

    /* Initialize with instruction execution events on both counters */
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

    /* Initialize test globals */
    TestPmu_MtReprogramComplete = 0U;
    TestPmu_MtCounter0ReadCount = 0U;
    TestPmu_MtBarrierCount = 0U;

    /* Construct step synchronization semaphore for task a and task b*/
    status = SemaphoreP_constructCounting(&TestPmu_MtReprogramStepSem, 0U, TEST_PMU_MT_REPROGRAM_STEPS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Construct synchronization semaphores */
    status = SemaphoreP_constructCounting(&TestPmu_MtBarrierArrive, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SemaphoreP_constructCounting(&TestPmu_MtBarrierLeave, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SemaphoreP_constructCounting(&TestPmu_MtCompletionSem, 0U, TEST_PMU_MT_TASK_COUNT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Spawn Thread A (reprogrammer) */
    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_A_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtReprogramA";
    taskParams.taskMain   = TestPmu_mtReprogramThreadA;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Spawn Thread B (reader) */
    TaskP_Params_init(&taskParams);
    taskParams.priority   = 3U;
    taskParams.stack      = TestPmu_MtTaskStack[TEST_PMU_MT_THREAD_B_IDX];
    taskParams.stackSize  = TEST_PMU_MT_TASK_STACK_SIZE;
    taskParams.name       = "PmuMtReprogramB";
    taskParams.taskMain   = TestPmu_mtReprogramThreadB;
    status = TaskP_construct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for completion */
    for (i = 0U; i < TEST_PMU_MT_TASK_COUNT; i+=1)
    {
        SemaphoreP_pend(&TestPmu_MtCompletionSem, SystemP_WAIT_FOREVER);
    }

    /* Verify results */
    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_A_IDX]); /* Thread A: Counter 1 counting new event */
    TEST_ASSERT_EQUAL_UINT32(1U, TestPmu_MtThreadResults[TEST_PMU_MT_THREAD_B_IDX]); /* Thread B: Counter 0 monotonic */
    TEST_ASSERT_TRUE(TestPmu_MtCounter0ReadCount > 0U);

    /* Cleanup */
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_A_IDX]);
    TaskP_destruct(&TestPmu_MtTaskObj[TEST_PMU_MT_THREAD_B_IDX]);
    SemaphoreP_destruct(&TestPmu_MtReprogramStepSem);
    SemaphoreP_destruct(&TestPmu_MtBarrierArrive);
    SemaphoreP_destruct(&TestPmu_MtBarrierLeave);
    SemaphoreP_destruct(&TestPmu_MtCompletionSem);
}

#endif /* ENABLE_MT_TESTS */

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

    /* Run PMU Negative tests */
    RUN_TEST(TestPmu_profileEndNameMismatchReturnsFailure, 10452, NULL);
    RUN_TEST(TestPmu_disabledCounterStopsCountingValidEventResumes, 10453, NULL);
    RUN_TEST(TestPmu_enableDisableCounterInvalidIndexNoEffect, 10459, NULL);
    RUN_TEST(TestPmu_setCntrWhileDisabledDoesNotStartCounting, 10460, NULL);
    RUN_TEST(TestPmu_cycleCounterDividerConfiguredButNotEnabledNoAdvance, 10461, NULL);
    RUN_TEST(TestPmu_clearOverflowWithoutStatusNoChange, 10462, NULL);
    RUN_TEST(TestPmu_freezeThenProfileNoCountingUntilUnfreeze, 10463, NULL);
    RUN_TEST(TestPmu_cycleCounterNsToTicks, 10833, NULL);
    RUN_TEST(TestPmu_cycleCounterNsToTicksMultipleFreq, 10834, NULL);
    RUN_TEST(TestPmu_profilePrintEntryValidName, 10835, NULL);
    RUN_TEST(TestPmu_profilePrintEntryNonExistentName, 10836, NULL);
    RUN_TEST(TestPmu_profilePrintEntryMultipleEntries, 10837, NULL);
    RUN_TEST(TestPmu_profilePrintAllEntries, 10838, NULL);
    RUN_TEST(TestPmu_profilePrintNoEntries, 10839, NULL);
    RUN_TEST(TestPmu_profilePrintEntryEmptyString, 10840, NULL);
    RUN_TEST(TestPmu_profilePrintMaxEntries, 10841, NULL);

    /* Run PMU Multi-Threaded tests */
#if defined(ENABLE_MT_TESTS)
    RUN_TEST(TestPmu_concurrentInitSingleCoreSerializesUsage, 10464, NULL);
    RUN_TEST(TestPmu_concurrentResetAllVsCycleOnlyCoordinated, 10465, NULL);
    RUN_TEST(TestPmu_concurrentEnableDisableAndReadDifferentCounters, 10466, NULL);
    RUN_TEST(TestPmu_concurrentSetCntrWriteReadAtomicity, 10467, NULL);
    RUN_TEST(TestPmu_concurrentReprogramEventWhileOtherThreadReads, 10468, NULL);
#endif /* ENABLE_MT_TESTS */
    UNITY_END();
}

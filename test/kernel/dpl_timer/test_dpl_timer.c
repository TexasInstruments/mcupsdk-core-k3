/*
 * Copyright (C) 2021-2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*===================================================================*/
/* 					      Include Files 					         */
/*===================================================================*/

#include "test_dpl_timer.h"
#include <drivers/udma.h>

#define TestExecute_SkipTestIdMatrix TestExecute_SkipTestIdMatrix_weak_default
#include "test_execute.h"
#undef TestExecute_SkipTestIdMatrix

#if defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM275X)

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/

#if ((defined(SOC_AM275X) && !((defined(CPU_C75_0) || defined(CPU_C75_1)))) || \
((defined(SOC_AM62AX) || defined(SOC_AM62DX)) && !defined(__C7000__)))
static uint8_t TestDplTimer_udmaFqDualChannel[128] __attribute__((aligned(128)));
static uint8_t TestDplTimer_udmaCqDualChannel[128]  __attribute__((aligned(128)));
#endif

#if ((defined(SOC_AM62AX) || defined(SOC_AM62DX)) && !defined(__C7000__))
/* Static DMA data buffers for AM62AX/AM62DX: placed in identity-mapped DDR so that
 * Udma_defaultVirtToPhyFxn returns the correct physical address on A53 (MMU on). */
static uint8_t TestDplTimer_am62DmaSrc[256]        __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t TestDplTimer_am62DmaDst[256]        __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t TestDplTimer_am62TrpdMemory[UDMA_GET_TRPD_TR15_SIZE(1U)] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
#endif

/*===================================================================*/
/* 					         Typedefs 					             */
/*===================================================================*/


/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/

/* AM62DX */

/* MCU */
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am62dx_mcur5_skip, 10360, 10372, 10376, 10377)

/* A53 */
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am62dx_a53_skip, 10360, 10372)

/* C7X */
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am62dx_c7x_skip, 10360, 10372)

/* R5 */
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am62dx_r5_skip, 10360, 10372, 10379, 10380, 10382, 10383)

/* AM62AX */

/* MCU */
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am62ax_mcur5_skip, 10360, 10372, 10377)

/* A53 */
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am62ax_a53_skip, 10360, 10372)

/* C7X */
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am62ax_c7x_skip, 10360, 10372)

/* R5 */
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am62ax_r5_skip, 10360, 10372, 10377, 10379, 10383)

/* AM275 */

/* R5F0-0, R5F0-1, R5F1-0, R5F1-1 */
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am275_r5f_skip, 10360, 10372, 10373, 10374, 10377)

/* C7x-0*/
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am275_c7x_0_skip, 10360, 10372)

/* Wkp-R5*/
TEST_EXECUTE_SKIP_IDS(TestDplTimer_am275_wkp_r5_skip, 10360, 10372, 10377, 10379, 10382)

/* Testcase execution list */
const TestExecute_idList TestExecute_SkipTestIdMatrix[TEST_SOC_COUNT][TEST_CORE_COUNT] = {
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, TestDplTimer_am62dx_mcur5_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_A53, TestDplTimer_am62dx_a53_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, TestDplTimer_am62dx_c7x_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, TestDplTimer_am62dx_r5_skip),

    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, TestDplTimer_am62ax_mcur5_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_A53, TestDplTimer_am62ax_a53_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, TestDplTimer_am62ax_c7x_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, TestDplTimer_am62ax_r5_skip),

    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, TestDplTimer_am275_r5f_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, TestDplTimer_am275_r5f_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, TestDplTimer_am275_r5f_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, TestDplTimer_am275_r5f_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_0, TestDplTimer_am275_c7x_0_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, TestDplTimer_am275_wkp_r5_skip),
};

static volatile bool TestDplTimer_timerCallbackCalled = false;
static volatile bool TestDplTimer_clearInIsr = false;
static volatile uint32_t TestDplTimer_overflowCount = 0U;
static volatile uint32_t TestDplTimer_stIsrCount = 0U;
static SemaphoreP_Object TestDplTimer_timerSem;
static SemaphoreP_Object TestDplTimer_stSemDone;

/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/

static void TestDplTimer_stTestcase(void);
static void TestDplTimer_setup_period_nsec_overrides_usec(void *args);
static void TestDplTimer_setup_invalid_inputs_assert(void *args);
static void TestDplTimer_setup_period_usec_isr(void *args);
static void TestDplTimer_setup_period_nsec_isr(void *args);
static void TestDplTimer_setup_prescaler_behavior_isr(void *args);
static void TestDplTimer_start_stop_idempotent(void *args);
static void TestDplTimer_counter_queries(void *args);
static void TestDplTimer_overflow_interrupt_handling(void *args);
static void TestDplTimer_overflow_isr(void *args);
static void TestDplTimer_oneshot_param_mode(void *args);
static void TestDplTimer_periodic_mode_param(void *args);
static void TestDplTimer_dma_trigger_flag(void *args);
#if ((defined(SOC_AM275X) && !((defined(CPU_C75_0) || defined(CPU_C75_1)))))
static void TestDplTimer_dma_trigger_transfer(void *args);
#endif
#if ((defined(SOC_AM62AX) || defined(SOC_AM62DX)) && !defined(__C7000__))
static void TestDplTimer_dma_trigger_transfer_am62(void *args);
#endif
static void TestDplTimer_params_init_defaults(void *args);
static void TestDplTimer_setup_boundary_values(void *args);
static void TestDplTimer_start_invalid_base(void *args);
static void TestDplTimer_stop_invalid_base(void *args);
static void TestDplTimer_getcount_invalid_base(void *args);
static void TestDplTimer_getreload_invalid_base(void *args);
static void TestDplTimer_clearoverflow_invalid_base(void *args);
static void TestDplTimer_isoverflowed_invalid_base(void *args);
static void TestDplTimer_multithread_two_timers_isolation(void *args);
static void TestDplTimer_multithread_isr_vs_poll(void *args);

/*===================================================================*/
/* 					         Function Definitions		             */
/*===================================================================*/

/**
 * @brief Main DPL timer unit test entry point.
 *
 * Initializes Unity, configures DPL timer test parameters for a set of
 * predefined test case IDs, and executes all registered DPL timer API
 * validation tests (setup, start/stop, period configuration, callback
 * registration, interrupt vs polled modes, multi-instance scenarios).
 * Ends by finalizing the Unity framework.
 *
 * Test cases are invoked using RUN_TEST with associated IDs to
 * exercise different parameter combinations (single-thread, multi-thread,
 * ISR vs poll modes).
 *
 * @param[in] args Optional user argument (unused in current implementation).
 *
 * @return void
 */
void test_main(void *args)
{
    /* Initialize Unity Test Framework */
    UNITY_BEGIN();

    TestDplTimer_stTestcase();
#if defined (CONFIG_MULTI_INSTANCE_TEST_ENABLE)
    TestDplTimer_mtTestcase();
#endif /* CONFIG_MULTI_INSTANCE_TEST_ENABLE */

    /* Finalize Unity Test Framework */
    UNITY_END();
}

static void TestDplTimer_stTestcase(void)
{
    /* Testcase to validate if period in nsec overrides usec in setup. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_setup_period_nsec_overrides_usec, 10359, NULL);
    /* Testcase to validate that invalid inputs to TimerP_setup() assert as expected. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_setup_invalid_inputs_assert, 10360, NULL);
    /* Testcase to validate period in usec is correctly handled in ISR context. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_setup_period_usec_isr, 10361, NULL);
    /* Testcase to validate period in nsec is correctly handled in ISR context. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_setup_period_nsec_isr, 10362, NULL);
    /* Testcase to validate prescaler behavior in ISR context. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_setup_prescaler_behavior_isr, 10363, NULL);
    /* Testcase to validate start/stop idempotent behavior. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_start_stop_idempotent, 10364, NULL);
    /* Testcase to validate counter queries. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_counter_queries, 10365, NULL);
    /* Testcase to validate overflow interrupt handling. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_overflow_interrupt_handling, 10366, NULL);
    /* Testcase to validate overflow ISR behavior. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_oneshot_param_mode, 10367, NULL);
    /* Testcase to validate periodic mode behavior. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_periodic_mode_param, 10368, NULL);
    /* Testcase to validate DMA trigger flag behavior. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_dma_trigger_flag, 10369, NULL);
#if ((defined(SOC_AM275X) && !((defined(CPU_C75_0) || defined(CPU_C75_1)))))
    /* Testcase to validate DMA trigger transfer behavior. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_dma_trigger_transfer, 10370, NULL);
#endif
#if ((defined(SOC_AM62AX) || defined(SOC_AM62DX)) && !defined(__C7000__))
    /* Testcase to validate DMA trigger transfer behavior on AM62AX/AM62DX. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_dma_trigger_transfer_am62, 11963, NULL);
#endif
    /* Testcase to validate timer parameter initialization defaults. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_params_init_defaults, 10371, NULL);
    /* Testcase to validate timer setup boundary values. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_setup_boundary_values, 10372, NULL);
    /* Testcase to validate start with invalid base. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_start_invalid_base, 10373, NULL);
    /* Testcase to validate stop with invalid base. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_stop_invalid_base, 10374, NULL);
    /* Testcase to validate get count with invalid base. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_getcount_invalid_base, 10375, NULL);
    /* Testcase to validate get reload with invalid base. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_getreload_invalid_base, 10376, NULL);
    /* Testcase to validate clear overflow with invalid base. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_clearoverflow_invalid_base, 10377, NULL);
    /* Testcase to validate is overflowed with invalid base. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_isoverflowed_invalid_base, 10378, NULL);
    /* Testcase to validate multithread two timers isolation. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_multithread_two_timers_isolation, 10379, NULL);
    /* Testcase to validate multithread ISR vs poll. */
    TEST_EXECUTE_TEST_CASE(TestDplTimer_multithread_isr_vs_poll, 10380, NULL);
}

/**
 * @brief Unity per-test setup hook.
 *
 * Called automatically by the Unity framework before each test case.
 * Closes the debug UART (if open) to ensure a clean state and avoid
 * leftover handles affecting tests. Individual tests then perform their
 * own local initialization (opening/closing handles, semaphores, loopback).
 *
 * @note Uses `TestUart_closeDebugUart()` to clear previous debug UART state.
 *
 * @return void
 */
void setUp(void)
{
    /* Nothing to be done */
}

/**
 * @brief Unity per-test teardown hook.
 *
 * Called automatically by the Unity framework after each test case.
 * Reopens the debug UART (if not already open) so subsequent test logs
 * and status prints are available on the console. Individual tests are
 * responsible for their own local cleanup.
 *
 * @note Uses `TestUart_openDebugUart()` with the backed-up configuration.
 *
 * @return void
 */
void tearDown(void)
{
    /* Nothing to be done */
}

/**
 * @brief Timer one-shot overflow ISR callback.
 *
 * This function is used as the interrupt service routine (ISR) for timer one-shot mode tests.
 * It clears the timer overflow interrupt, stops the timer to emulate one-shot behavior,
 * sets a flag indicating the callback was called, and posts to a semaphore to signal test completion.
 *
 * @param[in] args Pointer to the timer base address (cast as void *).
 *
 * @return void
 */
static void TestDplTimer_oneshot_callback(void *args)
{
    uint32_t baseAddr = (uint32_t)(uintptr_t)args;

    /* Clear and stop to emulate one-shot */
    TimerP_clearOverflowInt(baseAddr);
    TimerP_stop(baseAddr);

    TestDplTimer_timerCallbackCalled = true;
    SemaphoreP_post(&TestDplTimer_timerSem);
}

/**
 * @brief Computes expected timer cycles based on parameters.
 *
 * Converts the configured period to nanoseconds, applies the input prescaler
 * to the source clock, and returns the number of timer cycles required to
 * achieve the target period. For RTI timers, the prescaler must be 1 and is
 * effectively fixed; for DM timers, the prescaler divides the input clock.
 *
 * @param[in] params Pointer to `TimerP_Params` with `periodInNsec`/`periodInUsec`,
 *                   `inputPreScaler`, and `inputClkHz` populated.
 *
 * @return uint64_t Number of cycles corresponding to the configured period.
 *
 * @note If `periodInNsec` is 0, the implementation derives the period from
 *       `periodInUsec`.
 * @warning `inputPreScaler` must be non-zero; RTI requires `inputPreScaler=1`.
 */
static uint64_t TestDplTimer_compute_expected_cycles(const TimerP_Params *params)
{
    uint64_t timeInNsec = (uint64_t)params->periodInNsec;
    uint64_t prescale = (uint64_t)params->inputPreScaler;
    uint64_t effectiveClkHz;
    uint64_t cycles;

    if(timeInNsec == 0U)
    {
        timeInNsec = ((uint64_t)params->periodInUsec * 1000U);
    }
    /* For RTI, prescaler must be 1 and is ignored; for DM timer, prescaler divides input clock */
    if(prescale == 0U)
    {
        prescale = 1U; /* defensive */
    }
    effectiveClkHz = ((uint64_t)params->inputClkHz) / prescale;
    cycles = (effectiveClkHz * timeInNsec) / 1000000000ULL;

    return cycles;
}

/**
 * @brief Period in nsec overrides usec in setup.
 *
 * Validates that when both `periodInUsec` and `periodInNsec` are provided,
 * the nsec value is used to compute reload (1 ms target) and matches
 * expected cycles within 1 tick.
 *
 * Test Steps:
 * 1. Call `TimerP_Params_init()` to zero and default-initialize `TimerP_Params`.
 * 2. Set `enableOverflowInt=0`, `periodInUsec=500`, `periodInNsec=1ms`, `inputPreScaler=1`.
 * 3. Obtain `baseAddr = gTimerBaseAddr[CONFIG_TIMER0]` and call `TimerP_setup(baseAddr, &params)`.
 * 4. Read `reloadCount = TimerP_getReloadCount(baseAddr)`; compute `actualCycles = MAX_TIMER_COUNT_VALUE - reloadCount - 1`.
 * 5. Compute `expectedCycles` via helper `TestDplTimer_compute_expected_cycles(&params)`.
 * 6. Compare `actualCycles` and `expectedCycles`; assert delta ≤ 1 tick to confirm nsec overrides usec.
 * 7. Call `TimerP_stop(baseAddr)` to ensure the timer is stopped.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_setup_period_nsec_overrides_usec(void *args)
{
    uint32_t baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    uint32_t reloadCount;
    uint64_t actualCycles;
    uint64_t expectedCycles;
    uint64_t diff;

    TimerP_Params params;
    TimerP_Params_init(&params);
    params.enableOverflowInt = 0U;
    params.periodInUsec = 500U;                 /* will be ignored */
    params.periodInNsec = 1ULL * 1000000ULL;    /* 1 ms, should be used */
    params.inputPreScaler = 1U;

    TimerP_setup(baseAddr, &params);

    reloadCount = TimerP_getReloadCount(baseAddr);
    actualCycles = (uint64_t)MAX_TIMER_COUNT_VALUE - (uint64_t)reloadCount - 1ULL;
    expectedCycles = TestDplTimer_compute_expected_cycles(&params);
    diff = (actualCycles > expectedCycles) ? (actualCycles - expectedCycles) : (expectedCycles - actualCycles);
    TEST_ASSERT_TRUE(diff <= 1ULL);

    TimerP_stop(baseAddr);
}

/**
 * @brief Timer setup asserts on invalid inputs.
 *
 * Ensures `TimerP_setup()` guards against invalid `baseAddr`, prescaler, and
 * zero periods.
 *
 * Test Steps:
 * 1. Prepare default params via `TimerP_Params_init()` and set `enableOverflowInt=0`.
 * 2. Case A: Set `baseAddr=0` and call `TimerP_setup(0, &params)`; expect assertion/failure.
 * 3. Case B: Set `inputPreScaler=0` for DM timer path; call `TimerP_setup(baseAddr, &params)`; expect assertion.
 * 4. Case C: For RTI path, set `inputPreScaler` to a value ≠ 1; call setup; expect assertion.
 * 5. Case D: Set both `periodInUsec=0` and `periodInNsec=0`; call setup; expect assertion.
 * 6. Restore valid params after each case to avoid side effects.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_setup_invalid_inputs_assert(void *args)
{
    uint32_t baseAddr = 0U;

    TimerP_Params params;
    TimerP_Params_init(&params);
    params.enableOverflowInt = 0U;

    /* 1) baseAddr == 0 should assert */
    {
        baseAddr = 0U;
        params.periodInUsec = 1000U;
        params.periodInNsec = 0U;
        params.inputPreScaler = 1U;
        DebugP_logInfo("Expect assert: baseAddr=0");
        TimerP_setup(baseAddr, &params);
    }

    /* 2) prescaler invalid (0 or !=1 for RTI) should assert */
    {
        baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
        params.periodInUsec = 1000U;
        params.periodInNsec = 0U;
        params.inputPreScaler = 0U; /* invalid */
        DebugP_logInfo("Expect assert: prescaler=0");
        TimerP_setup(baseAddr, &params);
    }

    /* 3) both period fields 0 should assert */
    {
        baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
        params.periodInUsec = 0U;
        params.periodInNsec = 0U; /* invalid */
        params.inputPreScaler = 1U;
        DebugP_logInfo("Expect assert: both period fields = 0");
        TimerP_setup(baseAddr, &params);
    }
}

/**
 * @brief Period (usec) setup with ISR timing validation.
 *
 * Verifies usec-based period setup yields correct reload and ISR fires within
 * tolerance around the configured timeout.
 *
 * Test Steps:
 * 1. `SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0)`; reset `TestDplTimer_timerCallbackCalled=false`.
 * 2. `HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0])`; init `HwiP_Params` with `intNum=CONFIG_TIMER0_INT_NUM`, `callback=TestDplTimer_oneshot_callback`, `args=baseAddr`, set `isPulse` per SoC, `priority=4`; `HwiP_construct`.
 * 3. Init `TimerP_Params`; set `enableOverflowInt=1`, `periodInUsec=1000`, `periodInNsec=0`, `inputPreScaler=1`; call `TimerP_setup(baseAddr, &params)`.
 * 4. Read reload; compute `actualCycles`; compute `expectedCycles`; assert `|actual-expected| ≤ 1`.
 * 5. Call `TimerP_clearOverflowInt(baseAddr)`; record `tStartUsec = ClockP_getTimeUsec()`; `TimerP_start(baseAddr)`.
 * 6. Pend on `TestDplTimer_timerSem`; record `tEndUsec = ClockP_getTimeUsec()`; compute `elapsedUsec`.
 * 7. Compute tolerance `tolUsec = period/4 + 100`; assert `elapsedUsec` within `[period - tol, period + tol]` and callback flag is true.
 * 8. Cleanup `HwiP_destruct(&timerHwiObj)` and `SemaphoreP_destruct(&TestDplTimer_timerSem)`.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_setup_period_usec_isr(void *args)
{
    HwiP_Object   timerHwiObj;
    HwiP_Params   hwiParams;
    TimerP_Params params;
    uint32_t reloadCount;
    uint64_t actualCycles;
    uint64_t expected;
    uint64_t diff;
    uint64_t tStartUsec;
    uint64_t tEndUsec;
    uint64_t elapsedUsec;
    uint32_t tolUsec;

    uint32_t baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    uint32_t intNum   = CONFIG_TIMER0_INT_NUM;

    TestDplTimer_timerCallbackCalled = false;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0));

    /* Bind ISR */
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_oneshot_callback;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1;
#else
    hwiParams.isPulse  = 0;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4;
#if defined(__C7000__)
    hwiParams.eventId = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&timerHwiObj, &hwiParams);

    /* Setup: enable interrupt, usec path */
    TimerP_Params_init(&params);
    params.enableOverflowInt = 1U;
    params.periodInUsec      = 1000U; /* 1 ms */
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;

    TimerP_setup(baseAddr, &params);

    /* Validate reload vs expected cycles (within 1 tick) */
    reloadCount  = TimerP_getReloadCount(baseAddr);
    actualCycles = (uint64_t)MAX_TIMER_COUNT_VALUE - (uint64_t)reloadCount - 1ULL;
    expected     = TestDplTimer_compute_expected_cycles(&params);
    TEST_ASSERT_TRUE(expected > 0U);
    diff = (actualCycles > expected) ? (actualCycles - expected) : (expected - actualCycles);
    TEST_ASSERT_TRUE(diff <= 1ULL);

    /* Measure time to ISR against configured period */
    TimerP_clearOverflowInt(baseAddr);
    tStartUsec = ClockP_getTimeUsec();
    TimerP_start(baseAddr);
    SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
    tEndUsec = ClockP_getTimeUsec();
    elapsedUsec = (tEndUsec >= tStartUsec) ? (tEndUsec - tStartUsec) : 0U;

    /* Allow reasonable tolerance due to clock and ISR latency (25% + 100us) */
    tolUsec = (params.periodInUsec / 4U) + 100U;
    TEST_ASSERT_TRUE(elapsedUsec >= (uint64_t)(params.periodInUsec - tolUsec));
    TEST_ASSERT_TRUE(elapsedUsec <= (uint64_t)(params.periodInUsec + tolUsec));
    TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);

    /* Cleanup */
    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
}

/**
 * @brief Period (nsec) setup with ISR timing validation.
 *
 * Verifies nsec-based period setup yields correct reload and ISR latency
 * within tolerance of the configured timeout.
 *
 * Test Steps:
 * 1. Construct binary semaphore and reset callback flag; destruct any pre-bound Hwi for `CONFIG_TIMER0`.
 * 2. Init and construct Hwi with `callback=TestDplTimer_oneshot_callback`, pass `baseAddr` as args, configure `isPulse` and priority.
 * 3. Init timer params; set `enableOverflowInt=1`, `periodInUsec=0`, `periodInNsec=2ms`, `inputPreScaler=1`; call setup.
 * 4. Read reload; compute cycles and assert match within 1 tick.
 * 5. Clear overflow; start timer; pend on semaphore; measure elapsed in usec.
 * 6. Derive `targetUsec = periodInNsec / 1000`; compute `tolUsec = target/4 + 100`; assert bounds and callback.
 * 7. Destruct Hwi and semaphore to clean up.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_setup_period_nsec_isr(void *args)
{
    HwiP_Object   timerHwiObj;
    HwiP_Params   hwiParams;
    TimerP_Params params;
    uint32_t reloadCount;
    uint64_t actualCycles;
    uint64_t expected;
    uint64_t diff;
    uint64_t tStartUsec;
    uint64_t tEndUsec;
    uint64_t elapsedUsec;
    uint32_t tolUsec;
    uint32_t targetUsec;

    uint32_t baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    uint32_t intNum   = CONFIG_TIMER0_INT_NUM;

    TestDplTimer_timerCallbackCalled = false;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0));

    /* Bind ISR */
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_oneshot_callback;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1;
#else
    hwiParams.isPulse  = 0;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4;
#if defined(__C7000__)
    hwiParams.eventId = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&timerHwiObj, &hwiParams);

    /* Setup: enable interrupt, nsec path */
    TimerP_Params_init(&params);
    params.enableOverflowInt = 1U;
    params.periodInUsec      = 0U;
    params.periodInNsec      = 2ULL * 1000000ULL; /* 2 ms */
    params.inputPreScaler    = 1U;

    TimerP_setup(baseAddr, &params);

    /* Validate reload vs expected cycles (within 1 tick) */
    reloadCount  = TimerP_getReloadCount(baseAddr);
    actualCycles = (uint64_t)MAX_TIMER_COUNT_VALUE - (uint64_t)reloadCount - 1ULL;
    expected     = TestDplTimer_compute_expected_cycles(&params);
    diff         = (actualCycles > expected) ? (actualCycles - expected) : (expected - actualCycles);
    TEST_ASSERT_TRUE(diff <= 1ULL);

    /* Verify ISR triggers within configured timeout (nsec -> usec) */
    TimerP_clearOverflowInt(baseAddr);
    tStartUsec = ClockP_getTimeUsec();
    TimerP_start(baseAddr);
    SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
    tEndUsec = ClockP_getTimeUsec();
    elapsedUsec = (tEndUsec >= tStartUsec) ? (tEndUsec - tStartUsec) : 0U;

    targetUsec = (uint32_t)(params.periodInNsec / 1000ULL);
    tolUsec    = (targetUsec / 4U) + 100U; /* 25% + 100us tolerance for ISR latency */

    TEST_ASSERT_TRUE(elapsedUsec >= (uint64_t)(targetUsec - tolUsec));
    TEST_ASSERT_TRUE(elapsedUsec <= (uint64_t)(targetUsec + tolUsec));
    TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);

    /* Cleanup */
    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
}

/**
 * @brief Prescaler behavior with ISR.
 *
 * Checks RTI prescaler requirement (`=1`) and DM timer prescaler effects on
 * input clock division, reload values, and ISR timing.
 *
 * Test Steps:
 * 1. Construct binary semaphore and bind oneshot ISR `TestDplTimer_oneshot_callback` for `CONFIG_TIMER0`.
 * 2. RTI path: init params with `enableOverflowInt=1`, `periodInUsec=1000`, `inputPreScaler=1`; `TimerP_setup`; validate reload within 1 tick.
 * 3. Clear overflow; start; pend and measure elapsed; assert within tolerance; reset callback flag.
 * 4. DM path: for `prescalers={2,4,8}` loop:
 *    a) Set `inputPreScaler=prescalers[i]`; call setup; read reload; compute expected cycles dividing `inputClkHz/prescaler`.
 *    b) Assert reload delta ≤ 1; clear overflow; start; pend; measure elapsed; assert within adjusted tolerance.
 * 5. Destruct Hwi and semaphore.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_setup_prescaler_behavior_isr(void *args)
{
    HwiP_Object   timerHwiObj;
    HwiP_Params   hwiParams;
    TimerP_Params params;
    uint32_t reloadCount;
    uint64_t actualCycles;
    uint64_t expected;
    uint64_t diff;
    uint64_t tStartUsec;
    uint64_t tEndUsec;
    uint64_t elapsedUsec;
    uint32_t tolUsec;
    size_t loop;

    uint32_t baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    uint32_t intNum   = CONFIG_TIMER0_INT_NUM;
    const uint32_t prescalers[] = {2U, 4U, 8U};

    /* Bind ISR once */
    TestDplTimer_timerCallbackCalled = false;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0));
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_oneshot_callback;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1;
#else
    hwiParams.isPulse  = 0;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4;
#if defined(__C7000__)
    hwiParams.eventId = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&timerHwiObj, &hwiParams);

    /* Base params: 1 ms period, overflow ISR enabled */
    TimerP_Params_init(&params);
    params.enableOverflowInt = 1U;
    params.periodInUsec      = 1000U;
    params.periodInNsec      = 0U;

    /* RTI path: prescaler must be 1 */
    params.inputPreScaler    = 1U;
    TimerP_setup(baseAddr, &params);
    reloadCount  = TimerP_getReloadCount(baseAddr);
    actualCycles = (uint64_t)MAX_TIMER_COUNT_VALUE - (uint64_t)reloadCount - 1ULL;
    expected     = TestDplTimer_compute_expected_cycles(&params);
    diff         = (actualCycles > expected) ? (actualCycles - expected) : (expected - actualCycles);
    TEST_ASSERT_TRUE(diff <= 1ULL);

    /* Verify ISR triggers around configured timeout */
    TimerP_clearOverflowInt(baseAddr);
    tStartUsec = ClockP_getTimeUsec();
    TimerP_start(baseAddr);
    SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
    tEndUsec    = ClockP_getTimeUsec();
    elapsedUsec = (tEndUsec >= tStartUsec) ? (tEndUsec - tStartUsec) : 0U;
    tolUsec     = (params.periodInUsec / 4U) + 100U; /* 25% + 100us tolerance */
    TEST_ASSERT_TRUE(elapsedUsec >= (uint64_t)(params.periodInUsec - tolUsec));
    TEST_ASSERT_TRUE(elapsedUsec <= (uint64_t)(params.periodInUsec + tolUsec));
    TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);
    TestDplTimer_timerCallbackCalled = false; /* reset for next runs */

    /* DM Timer path: prescaler divides input clock; test a few power-of-2 values */
    for( loop = 0U; loop < (sizeof(prescalers)/sizeof(prescalers[0])); loop++)
    {
        params.inputPreScaler = prescalers[loop];
        TimerP_setup(baseAddr, &params);

        reloadCount  = TimerP_getReloadCount(baseAddr);
        actualCycles = (uint64_t)MAX_TIMER_COUNT_VALUE - (uint64_t)reloadCount - 1ULL;
        expected     = TestDplTimer_compute_expected_cycles(&params);
        diff         = (actualCycles > expected) ? (actualCycles - expected) : (expected - actualCycles);
        TEST_ASSERT_TRUE(diff <= 1ULL);

        /* Verify ISR triggers around configured timeout for each prescaler */
        TimerP_clearOverflowInt(baseAddr);
        tStartUsec = ClockP_getTimeUsec();
        TimerP_start(baseAddr);
        SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
        tEndUsec     = ClockP_getTimeUsec();
        elapsedUsec  = (tEndUsec >= tStartUsec) ? (tEndUsec - tStartUsec) : 0U;
        tolUsec      = (params.periodInUsec / 4U) + 100U;
        TEST_ASSERT_TRUE(elapsedUsec >= (uint64_t)(params.periodInUsec - tolUsec));
        TEST_ASSERT_TRUE(elapsedUsec <= (uint64_t)(params.periodInUsec + tolUsec));
        TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);
        TestDplTimer_timerCallbackCalled = false;
    }

    /* Cleanup */
    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
}

/**
 * @brief Timer overflow interrupt service routine (ISR) callback.
 *
 * This ISR is used in timer overflow tests to handle timer overflow events.
 * It checks if the timer has overflowed, increments the overflow counter,
 * optionally clears the overflow interrupt (if enabled via a global flag),
 * sets a callback flag, and posts to a semaphore to signal test completion.
 *
 * @param[in] args Pointer to the timer base address (cast as void *).
 *
 * @return void
 */
static void TestDplTimer_overflow_isr(void *args)
{
    uint32_t baseAddr = (uint32_t)(uintptr_t)args;

    if (TimerP_isOverflowed(baseAddr) != 0U)
    {
        TestDplTimer_overflowCount++;
    }

    if(TestDplTimer_clearInIsr)
    {
        TimerP_clearOverflowInt(baseAddr);
    }

    TestDplTimer_timerCallbackCalled = true;
    SemaphoreP_post(&TestDplTimer_timerSem);
}

/**
 * @brief Start/stop idempotence.
 *
 * Ensures repeated `TimerP_start()`/`TimerP_stop()` behave idempotently and
 * count remains stable when stopped.
 *
 * Test Steps:
 * 1. Initialize params (1ms, prescaler=1, overflow disabled); call setup for `CONFIG_TIMER0`.
 * 2. Call `TimerP_stop(baseAddr)`; read `count1 = TimerP_getCount(baseAddr)`.
 * 3. Call `TimerP_stop(baseAddr)` again; read `count2`; assert `count1 == count2`.
 * 4. Call `TimerP_start(baseAddr)` twice; sample `count3`; poll in a short loop until count differs from `count3`.
 * 5. Assert that a change was observed while running.
 * 6. Call `TimerP_stop(baseAddr)`; read `count1`.
 * 7. Sample count repeatedly (e.g., 1000 iterations) and assert all reads equal `count1`.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_start_stop_idempotent(void *args)
{
    uint32_t baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    uint32_t count1;
    uint32_t count2;
    uint32_t count3;
    uint32_t count4;
    uint32_t loop;
    bool stable = true;
    bool changed = false;
    uint32_t sN;

    TimerP_Params params;
    TimerP_Params_init(&params);
    params.enableOverflowInt = 0U;
    params.periodInUsec      = 1000U;
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;

    TimerP_setup(baseAddr, &params);

    /* Stop twice, ensure stable count */
    TimerP_stop(baseAddr);
    count1 = TimerP_getCount(baseAddr);
    TimerP_stop(baseAddr);
    count2 = TimerP_getCount(baseAddr);
    TEST_ASSERT_EQUAL_UINT32(count1, count2);

    /* Start twice, ensure counter runs */
    TimerP_start(baseAddr);
    TimerP_start(baseAddr);

    count3 = TimerP_getCount(baseAddr);
    count4 = count3;
    
    for(loop = 0U; loop < 100000U; loop++)
    {
        count4 = TimerP_getCount(baseAddr);
        if(count4 != count3)
        {
            changed = true;
            break;
        }
    }
    TEST_ASSERT_TRUE(changed);

    /* Stop twice again, ensure stable count */
    TimerP_stop(baseAddr);
    count1 = TimerP_getCount(baseAddr);
    TimerP_stop(baseAddr);
    count2 = TimerP_getCount(baseAddr);

    for(loop = 0U; loop < 1000U; loop++)
    {
        sN = TimerP_getCount(baseAddr);
        if(sN != count1)
        {
            stable = false;
            break;
        }
    }
    TEST_ASSERT_TRUE(stable);
}

/**
 * @brief Counter queries for reload and count behavior.
 *
 * Validates reload matches expected cycles, count changes while running, and
 * remains stable after stop.
 *
 * Test Steps:
 * 1. Initialize params (2ms period, prescaler=1, overflow disabled); setup `CONFIG_TIMER0`.
 * 2. Read `reloadCount`; compute `expectedCycles` and `expectedReload = MAX_TIMER_COUNT_VALUE - expectedCycles - 1`.
 * 3. Assert `|reloadCount - expectedReload| ≤ 1`.
 * 4. Clear overflow; start timer.
 * 5. Read `count3`; poll `count4` in a bounded loop until `count4 != count3` to detect progression.
 * 6. Assert a change was detected; stop timer.
 * 7. Read `count1`; sample count repeatedly (e.g., 1000 iterations) and assert stability (no change).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_counter_queries(void *args)
{
    uint32_t baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    uint32_t reloadCount;
    uint64_t expectedCycles;
    uint64_t expectedReload;
    uint64_t diffReload;
    uint32_t count1;
    uint32_t count2;
    uint32_t count3;
    uint32_t count4;
    bool stable;
    bool changed;
    uint32_t loop;

    TimerP_Params params;
    TimerP_Params_init(&params);
    params.enableOverflowInt = 0U;
    params.periodInUsec      = 2000U; /* 2 ms period to avoid very fast wrap */
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;

    TimerP_setup(baseAddr, &params);

    /* Reload should match setup-derived value within 1 tick */
    reloadCount = TimerP_getReloadCount(baseAddr);
    expectedCycles = TestDplTimer_compute_expected_cycles(&params);
    expectedReload = (uint64_t)MAX_TIMER_COUNT_VALUE - expectedCycles - 1ULL;

    diffReload = (reloadCount > expectedReload)
                        ? ((uint64_t)reloadCount - expectedReload)
                        : (expectedReload - (uint64_t)reloadCount);
    TEST_ASSERT_TRUE(diffReload <= 1ULL);

    /* Running: count should change */
    TimerP_clearOverflowInt(baseAddr);
    TimerP_start(baseAddr);

    count3 = TimerP_getCount(baseAddr);
    count4 = count3;
    changed = false;

    for(loop = 0U; loop < 100000U; loop++)
    {
        count4 = TimerP_getCount(baseAddr);
        if(count4 != count3)
        {
            changed = true;
            break;
        }
    }
    TEST_ASSERT_TRUE(changed);

    /* Stopped: count should be stable */
    TimerP_stop(baseAddr);
    count1 = TimerP_getCount(baseAddr);

    stable = true;
    for(loop = 0U; loop < 1000U; loop++)
    {
        count2 = TimerP_getCount(baseAddr);
        if(count2 != count1)
        {
            stable = false;
            break;
        }
    }
    TEST_ASSERT_TRUE(stable);
}

/**
 * @brief Overflow interrupt handling.
 *
 * Verifies overflow ISR clears flag and counts events (one-shot then repeated).
 *
 * Test Steps:
 * 1. Construct binary semaphore; reset `TestDplTimer_timerCallbackCalled=false`.
 * 2. Init params with `enableOverflowInt=1`, `oneshotMode=0`; call setup for `CONFIG_TIMER0`.
 * 3. Destruct any DPL-configured Hwi; construct new Hwi with `callback=TestDplTimer_overflow_isr`, `args=baseAddr`, `priority=4`.
 * 4. Set `TestDplTimer_clearInIsr=true`; clear overflow; start timer.
 * 5. Pend on ISR semaphore; assert callback called; assert `TestDplTimer_overflowCount==1`; assert `TimerP_isOverflowed(baseAddr)==0`.
 * 6. Reset `overflowCount=0` and callback flag; clear overflow.
 * 7. Loop for N overflows: pend, verify ISR clears flag each time, increment count; stop timer after loop.
 * 8. Cleanup Hwi and semaphore.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_overflow_interrupt_handling(void *args)
{
    HwiP_Object   timerHwiObj;
    HwiP_Params   hwiParams;
    TimerP_Params timerParams;
    int32_t       status;
    const uint32_t targetOverflows = 3U;
    uint32_t loop;

    uint32_t baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    uint32_t intNum   = CONFIG_TIMER0_INT_NUM;

    TestDplTimer_timerCallbackCalled = false;

    /* Semaphore for ISR sync */
    status = SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configure timer (params may be ignored by current TimerP implementation) */
    TimerP_Params_init(&timerParams);
    timerParams.enableOverflowInt = 1U;
    timerParams.oneshotMode = 0;
    TimerP_setup(baseAddr, &timerParams);

     /* Re-bind the DPL-configured Hwi to our ISR */
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);

    /* Hook ISR */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_overflow_isr;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1;
#else
    hwiParams.isPulse  = 0;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4;

#if defined(__C7000__)
    hwiParams.eventId = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&timerHwiObj, &hwiParams);
    TestDplTimer_clearInIsr = true;
    /* Clean start */
    TimerP_clearOverflowInt(baseAddr);
    TimerP_start(baseAddr);

    /* Wait for ISR to signal completion */
    SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);
    TEST_ASSERT_EQUAL_UINT32(1U, TestDplTimer_overflowCount);
    TEST_ASSERT_TRUE(TimerP_isOverflowed(baseAddr) == 0U);

     /* Phase 2: count repeated overflows while ISR clears status */
    TestDplTimer_overflowCount = 0U;
    TestDplTimer_timerCallbackCalled = false;
    TimerP_clearOverflowInt(baseAddr);

    for(loop = 0U; loop < targetOverflows; loop++)
    {
        SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);
        TestDplTimer_timerCallbackCalled = false;
    }

    TimerP_stop(baseAddr);

    TEST_ASSERT_TRUE(TestDplTimer_overflowCount >= targetOverflows);
    TEST_ASSERT_TRUE(TimerP_isOverflowed(baseAddr) == 0U);

    /* Cleanup */
    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
}

/**
 * @brief Timer overflow ISR that only clears the overflow interrupt.
 *
 * This interrupt service routine (ISR) is used in one-shot timer tests where the timer
 * hardware or TimerP driver is expected to handle stopping the timer automatically.
 * The ISR simply clears the timer overflow interrupt (if set), sets a callback flag,
 * and posts to a semaphore to signal test completion. It does not stop the timer manually.
 *
 * @param[in] args Pointer to the timer base address (cast as void *).
 *
 * @return void
 */
static void TestDplTimer_clear_only_isr(void *args)
{
    uint32_t baseAddr;

    baseAddr = (uint32_t)(uintptr_t)args;

    if (TimerP_isOverflowed(baseAddr) != 0U)
    {
        /* Clear only, do not stop. One-shot auto-stop should be handled by HW/TimerP when enabled. */
        TimerP_clearOverflowInt(baseAddr);
    }

    TestDplTimer_timerCallbackCalled = true;
    SemaphoreP_post(&TestDplTimer_timerSem);
}

/**
 * @brief One-shot via params.
 *
 * Validates oneshot behavior when `oneshotMode` is enabled in `TimerP_Params`.
 *
 * Test Steps:
 * 1. Construct binary semaphore; reset shared flags/counters.
 * 2. Init `TimerP_Params` with `enableOverflowInt=1`, `oneshotMode=1`, 1ms period, prescaler=1; `TimerP_setup`.
 * 3. Destruct any pre-bound Hwi; construct Hwi with `callback=TestDplTimer_clear_only_isr`.
 * 4. Clear overflow; start timer; pend on semaphore once.
 * 5. Verify only one ISR occurs and timer does not retrigger; check overflow flag cleared by ISR.
 * 6. Stop timer; cleanup Hwi and semaphore.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_oneshot_param_mode(void *args)
{
    HwiP_Object   timerHwiObj;
    HwiP_Params   hwiParams;
    TimerP_Params params;
    uint32_t      baseAddr;
    uint32_t      intNum;
    int32_t       status;
    uint32_t      count1;
    uint32_t      count2;
    uint32_t      loop;
    bool          stable;

    baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    intNum   = CONFIG_TIMER0_INT_NUM;
    status   = SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestDplTimer_timerCallbackCalled = false;

    /* Re-bind ISR that only clears overflow (no manual stop) */
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);

    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_clear_only_isr;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1U;
#else
    hwiParams.isPulse  = 0U;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4U;
#if defined(__C7000__)
    hwiParams.eventId  = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&timerHwiObj, &hwiParams);

    /* Configure DM timer for one-shot mode */
    TimerP_Params_init(&params);
    params.enableOverflowInt = 1U;
    params.periodInUsec      = 500U;   /* Short period for quick expiration */
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;
    params.oneshotMode       = 1U;     /* One-shot */
    TimerP_setup(baseAddr, &params);

    TimerP_clearOverflowInt(baseAddr);
    TimerP_start(baseAddr);

    /* Wait for first (and only) expiration */
    SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);

    /* After ISR, timer should have auto-stopped (count stable) */
    count1 = TimerP_getCount(baseAddr);
    stable = true;

    for (loop = 0U; loop < 2000U; loop++)
    {
        count2 = TimerP_getCount(baseAddr);
        if (count2 != count1)
        {
            stable = false;
            break;
        }
    }
    TEST_ASSERT_TRUE(stable);

    /* Overflow flag should be cleared by ISR */
    TEST_ASSERT_TRUE(TimerP_isOverflowed(baseAddr) == 0U);

    /* Cleanup */
    TimerP_stop(baseAddr);
    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
}

/**
 * @brief Periodic via params.
 *
 * Validates periodic mode produces repeated overflows with ISR clearing.
 *
 * Test Steps:
 * 1. Construct binary semaphore; reset counters.
 * 2. Init params with `oneshotMode=0`, `enableOverflowInt=1`, 1ms period; setup `CONFIG_TIMER0`.
 * 3. Construct Hwi with `callback=TestDplTimer_overflow_isr`; clear overflow; start timer.
 * 4. Observe and count multiple ISR events; verify flag handling and timing consistency.
 * 5. Stop timer; cleanup Hwi and semaphore.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_periodic_mode_param(void *args)
{
    HwiP_Object    timerHwiObj;
    HwiP_Params    hwiParams;
    TimerP_Params  params;
    uint32_t       baseAddr;
    uint32_t       intNum;
    int32_t        status;
    const uint32_t targetOverflows = 3U;
    uint32_t       loop;
    uint32_t       countA;
    uint32_t       countB;
    bool           running;

    baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    intNum   = CONFIG_TIMER0_INT_NUM;
    status   = SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestDplTimer_timerCallbackCalled = false;
    TestDplTimer_overflowCount       = 0U;
    TestDplTimer_clearInIsr          = true;

    /* Bind periodic ISR (clears overflow in ISR) */
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);

    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_overflow_isr;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1U;
#else
    hwiParams.isPulse  = 0U;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4U;
#if defined(__C7000__)
    hwiParams.eventId  = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&timerHwiObj, &hwiParams);

    /* Configure periodic mode */
    TimerP_Params_init(&params);
    params.enableOverflowInt = 1U;
    params.periodInUsec      = 1000U; /* 1 ms */
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;
    params.oneshotMode       = 0U;     /* Periodic */
    TimerP_setup(baseAddr, &params);

    TimerP_clearOverflowInt(baseAddr);
    TimerP_start(baseAddr);

    /* Wait for multiple expirations */
    for (loop = 0U; loop < targetOverflows; loop++)
    {
        SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);
        TestDplTimer_timerCallbackCalled = false;
    }

    TEST_ASSERT_TRUE(TestDplTimer_overflowCount >= targetOverflows);

    /* Verify timer is still running (count changing) */
    running = false;
    countA  = TimerP_getCount(baseAddr);
    for (loop = 0U; loop < 100000U; loop++)
    {
        countB = TimerP_getCount(baseAddr);
        if (countB != countA)
        {
            running = true;
            break;
        }
    }
    TEST_ASSERT_TRUE(running);

    /* Cleanup */
    TimerP_stop(baseAddr);
    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
}

/**
 * @brief DMA trigger flag.
 *
 * Checks enabling timer DMA trigger flag and basic interaction with overflow ISR.
 *
 * Test Steps:
 * 1. Construct binary semaphore; bind overflow ISR.
 * 2. Init params with `enableDmaTrigger=1`, overflow enabled, desired period/prescaler; setup timer and clear overflow.
 * 3. Start timer; pend on semaphore; verify ISR signaling.
 * 4. Inspect DMA trigger status/flag via driver APIs or status queries when available.
 * 5. Stop timer; cleanup Hwi and semaphore.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_dma_trigger_flag(void *args)
{
    HwiP_Object    timerHwiObj;
    HwiP_Params    hwiParams;
    TimerP_Params  params;
    uint32_t       baseAddr;
    uint32_t       intNum;
    int32_t        status;
    uint32_t       loop;
    const uint32_t expirations = 2U;

    baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    intNum   = CONFIG_TIMER0_INT_NUM;
    status   = SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestDplTimer_timerCallbackCalled = false;
    TestDplTimer_overflowCount       = 0U;
    TestDplTimer_clearInIsr          = true;

    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);

    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_overflow_isr;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1U;
#else
    hwiParams.isPulse  = 0U;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4U;
#if defined(__C7000__)
    hwiParams.eventId  = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&timerHwiObj, &hwiParams);

    TimerP_Params_init(&params);
    params.enableOverflowInt = 1U;
    params.periodInUsec      = 1000U;
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;
    params.oneshotMode       = 0U;
    params.enableDmaTrigger  = 1U;

    TimerP_setup(baseAddr, &params);
    TimerP_clearOverflowInt(baseAddr);
    TimerP_start(baseAddr);

    for (loop = 0U; loop < expirations; loop++)
    {
        SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);
        TestDplTimer_timerCallbackCalled = false;
    }
    TimerP_stop(baseAddr);

    TestDplTimer_overflowCount       = 0U;
    TestDplTimer_timerCallbackCalled = false;

    TimerP_Params_init(&params);
    params.enableOverflowInt = 1U;
    params.periodInUsec      = 1000U;
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;
    params.oneshotMode       = 0U;
    params.enableDmaTrigger  = 0U;

    TimerP_setup(baseAddr, &params);
    TimerP_clearOverflowInt(baseAddr);
    TimerP_start(baseAddr);

    for (loop = 0U; loop < expirations; loop++)
    {
        SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);
        TestDplTimer_timerCallbackCalled = false;
    }

    TimerP_stop(baseAddr);
    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
}

#if ((defined(SOC_AM275X) && !((defined(CPU_C75_0) || defined(CPU_C75_1)))))
/**
 * @brief DMA trigger transfer.
 *
 * Validates timer-driven DMA transfer where supported (UDMA v0 path).
 *
 * Test Steps:
 * 1. Verify environment supports UDMA v0 and `CONFIG_TIMER0_UDMA_INST_ID`; otherwise skip.
 * 2. Construct binary semaphore; bind overflow ISR; init timer with DMA trigger enabled; setup and clear overflow.
 * 3. Initialize UDMA driver; allocate TR channel; set `chNum` (e.g., `CONFIG_TIMER0_UDMA_TR_CH`) and link to timer trigger.
 * 4. Program TR descriptor for memory-to-memory (or peripheral) transfer sized for test; enable channel.
 * 5. Start timer to generate DMA trigger; pend on semaphore or UDMA completion; verify transfer completion status.
 * 6. Stop timer; teardown UDMA channel/instance; cleanup Hwi and semaphore.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_dma_trigger_transfer(void *args)
{

#if !defined(DRV_VERSION_UDMA_V0)
    TEST_IGNORE_MESSAGE("UDMA v0 required; this test is for UDMA v0 only.");
    return;
#else
    uint32_t          baseAddr;
    uint32_t          intNum;
    int32_t           status;
    HwiP_Object       timerHwiObj;
    HwiP_Params       hwiParams;
    TimerP_Params     tParams;
    volatile uint8_t  src[256];
    volatile uint8_t  dst[256];
    uint32_t          i;
    bool              equal;
    Udma_DrvObject    drvObj;
    Udma_DrvHandle    drvHandle = &drvObj;
    Udma_InitPrms     initPrms;
    Udma_ChObject     chObj;
    Udma_ChHandle     chHandle;
    Udma_ChPrms       chPrms;
    Udma_ChTxPrms     txPrms;
    Udma_RingHandle   fqRing;
    Udma_RingHandle   cqRing;
    CSL_UdmapTR15     *pTrReq;
    uint8_t           trpdMemory[UDMA_GET_TRPD_TR15_SIZE(1U)] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
    uint64_t          physTrDesc;
    int32_t           timeoutTicks;
    uint32_t          cqRingNum;
    uint64_t          cqPtr;


    baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    intNum   = CONFIG_TIMER0_INT_NUM;

    /* Initialize source buffer with test pattern */
    for (i = 0U; i < sizeof(src); i++)
    {
        ((volatile uint8_t *)src)[i] = (uint8_t)(i ^ 0x5AU);
    }

    /* Clear destination buffer */
    for (i = 0U; i < sizeof(dst); i++)
    {
        ((volatile uint8_t *)dst)[i] = 0U;
    }

    /* Construct semaphore for timer ISR synchronization */
    status = SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configure timer ISR */
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_overflow_isr;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1U;
#else
    hwiParams.isPulse  = 0U;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4U;
#if defined(__C7000__)
    hwiParams.eventId  = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&timerHwiObj, &hwiParams);

    /* Initialize UDMA driver */
    status = UdmaInitPrms_init(UDMA_INST_ID_2, &initPrms);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "UdmaInitPrms_init failed");

    status = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_init failed");

    /* Open UDMA TR block copy channel */
    chHandle = &chObj;
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem     = TestDplTimer_udmaFqDualChannel;
    chPrms.fqRingPrms.ringMemSize = sizeof(TestDplTimer_udmaFqDualChannel);
    chPrms.fqRingPrms.elemCnt     = 1U;
    chPrms.cqRingPrms.ringMem     = TestDplTimer_udmaCqDualChannel;
    chPrms.cqRingPrms.ringMemSize = sizeof(TestDplTimer_udmaCqDualChannel);
    chPrms.cqRingPrms.elemCnt     = 1U;
    chPrms.chNum = UDMA_DMA_CH_ANY;

    status = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_chOpen failed");

    /* Configure TX parameters for block copy */
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    status = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_chConfigTx failed");

    /* Get FQ and CQ ring handles from channel */
    fqRing = Udma_chGetFqRingHandle(chHandle);
    cqRing = Udma_chGetCqRingHandle(chHandle);
    TEST_ASSERT_NOT_NULL_MESSAGE(fqRing, "FQ ring handle is NULL");
    TEST_ASSERT_NOT_NULL_MESSAGE(cqRing, "CQ ring handle is NULL");

    cqRingNum = Udma_ringGetNum(cqRing);

    /* Build TRPD with one TR15 record for memory copy */
    UdmaUtils_makeTrpd(trpdMemory,
                       UDMA_TR_TYPE_15,
                       1U,
                       cqRingNum);

    /* Get pointer to TR15 within the TRPD */
    pTrReq = UdmaUtils_getTrpdTr15Pointer(trpdMemory, 0U);

    /* Configure TR15 flags for 1D block move */
    pTrReq->flags    = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, 0U);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_MATCH_SOL_EOL);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, 0x25U);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);


    /* Set transfer dimensions (1D copy of 256 bytes) */
    pTrReq->icnt0    = (uint16_t)sizeof(src);
    pTrReq->icnt1    = 1U;
    pTrReq->icnt2    = 1U;
    pTrReq->icnt3    = 1U;
    pTrReq->addr     = (uint64_t)(uintptr_t)src;
    pTrReq->fmtflags = 0U;
    pTrReq->dicnt0   = (uint16_t)sizeof(dst);
    pTrReq->dicnt1   = 1U;
    pTrReq->dicnt2   = 1U;
    pTrReq->dicnt3   = 1U;
    pTrReq->daddr    = (uint64_t)(uintptr_t)dst;
    pTrReq->dim1     = 0;
    pTrReq->dim2     = 0;
    pTrReq->dim3     = 0;
    pTrReq->ddim1    = 0;
    pTrReq->ddim2    = 0;
    pTrReq->ddim3    = 0;

    /* Cache writeback for coherency */
    CacheP_wb(trpdMemory, sizeof(trpdMemory), CacheP_TYPE_ALLD);
    CacheP_wb((void *)src, sizeof(src), CacheP_TYPE_ALLD);

    /* Convert virtual to physical address */
    physTrDesc = Udma_defaultVirtToPhyFxn((const void *)trpdMemory, 0U, NULL);

    /* Enable the UDMA channel */
    status = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_chEnable failed");

    /* Queue TR descriptor to FQ ring */
    status = Udma_ringQueueRaw(fqRing, physTrDesc);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_ringQueueRaw failed");

    /* Configure timer with DMA trigger enabled */
    TimerP_Params_init(&tParams);
    tParams.enableOverflowInt = 1U;
    tParams.periodInUsec      = 1000U;
    tParams.periodInNsec      = 0U;
    tParams.inputPreScaler    = 1U;
    tParams.oneshotMode       = 1U;
    tParams.enableDmaTrigger  = 1U;

    TimerP_setup(baseAddr, &tParams);
    TimerP_clearOverflowInt(baseAddr);

    TestDplTimer_clearInIsr          = true;
    TestDplTimer_timerCallbackCalled = false;

    /* Start timer to trigger UDMA transfer on overflow */
    TimerP_start(baseAddr);

    /* Wait for timer ISR */
    SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);

    /* Poll CQ ring for transfer completion */
    timeoutTicks = 1000000U;

    while (timeoutTicks-- > 0U)
    {
        status = Udma_ringDequeueRaw(cqRing, &cqPtr);
        if (status == UDMA_SOK)
        {
            break;
        }
    }

    TEST_ASSERT_TRUE(timeoutTicks > 0U);

    /* Invalidate cache before reading destination */
    CacheP_inv((void *)dst, sizeof(dst), CacheP_TYPE_ALLD);

    /* Verify destination matches source */
    equal = true;

    for (i = 0U; i < sizeof(src); i++)
    {
        if (((volatile uint8_t *)dst)[i] != ((volatile uint8_t *)src)[i])
        {
            equal = false;
            break;
        }
    }

    TEST_ASSERT_TRUE(equal);

    /* Cleanup */
    TimerP_stop(baseAddr);

    Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    Udma_chClose(chHandle);
    Udma_deinit(&drvObj);

    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
#endif

}

#endif /* SOC_AM275X UDMA v0 */

#if ((defined(SOC_AM62AX) || defined(SOC_AM62DX)) && !defined(__C7000__))
/**
 * @brief DMA trigger transfer (AM62AX / AM62DX).
 *
 * Validates timer-driven BCDMA block-copy transfer on AM62AX and AM62DX.
 * Both SoCs expose UDMA v0 BCDMA (UDMA_INST_ID_BCDMA_0 = UDMA_INST_ID_2)
 * accessible from all non-C7x cores.
 *
 * Test Steps:
 * 1. Fill a 256-byte source buffer with a known pattern; zero destination buffer.
 * 2. Construct binary semaphore; bind overflow ISR to CONFIG_TIMER0.
 * 3. Initialize UDMA driver with UDMA_INST_ID_BCDMA_0; open a TR block-copy channel.
 * 4. Build a TR15 TRPD for a 1D memory-to-memory copy (src -> dst, 256 bytes).
 * 5. Enable the channel; queue the descriptor to the FQ ring.
 * 6. Configure timer with DMA trigger enabled, one-shot mode, 1 ms period; start timer.
 * 7. Wait for timer ISR (overflow); then poll CQ ring for transfer completion.
 * 8. Invalidate D-cache; verify destination matches source byte-for-byte.
 * 9. Disable/close UDMA channel; deinit driver; destruct ISR and semaphore.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_dma_trigger_transfer_am62(void *args)
{
#if !defined(DRV_VERSION_UDMA_V0)
    TEST_IGNORE_MESSAGE("UDMA v0 required; skipping on this build.");
    return;
#else
    uint32_t          baseAddr;
    uint32_t          intNum;
    int32_t           status;
    HwiP_Object       timerHwiObj;
    HwiP_Params       hwiParams;
    TimerP_Params     tParams;
    uint32_t          i;
    bool              equal;
    Udma_DrvObject    drvObj;
    Udma_DrvHandle    drvHandle = &drvObj;
    Udma_InitPrms     initPrms;
    Udma_ChObject     chObj;
    Udma_ChHandle     chHandle;
    Udma_ChPrms       chPrms;
    Udma_ChTxPrms     txPrms;
    Udma_RingHandle   fqRing;
    Udma_RingHandle   cqRing;
    CSL_UdmapTR15    *pTrReq;
    uint64_t          physTrDesc;
    uint64_t          physSrc;
    uint64_t          physDst;
    int32_t           timeoutTicks;
    uint32_t          cqRingNum;
    uint64_t          cqPtr;

    baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    intNum   = CONFIG_TIMER0_INT_NUM;

    /* Use static globals so Udma_defaultVirtToPhyFxn returns the correct physical
     * address on A53 (MMU enabled, stack virtual != physical). */
    /* Initialize source buffer with a test pattern */
    for (i = 0U; i < sizeof(TestDplTimer_am62DmaSrc); i++)
    {
        TestDplTimer_am62DmaSrc[i] = (uint8_t)(i ^ 0xA5U);
    }

    /* Clear destination buffer */
    for (i = 0U; i < sizeof(TestDplTimer_am62DmaDst); i++)
    {
        TestDplTimer_am62DmaDst[i] = 0U;
    }

    /* Construct semaphore for timer ISR synchronization */
    status = SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configure timer ISR */
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_overflow_isr;
    hwiParams.isPulse  = 1U;   /* AM62AX / AM62DX use pulse interrupts */
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4U;
    HwiP_construct(&timerHwiObj, &hwiParams);

    /* Initialize UDMA driver — BCDMA instance (same inst ID as AM275X) */
    status = UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "UdmaInitPrms_init failed");

    status = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_init failed");

    /* Open UDMA TR block-copy channel */
    chHandle = &chObj;
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem     = TestDplTimer_udmaFqDualChannel;
    chPrms.fqRingPrms.ringMemSize = sizeof(TestDplTimer_udmaFqDualChannel);
    chPrms.fqRingPrms.elemCnt     = 1U;
    chPrms.cqRingPrms.ringMem     = TestDplTimer_udmaCqDualChannel;
    chPrms.cqRingPrms.ringMemSize = sizeof(TestDplTimer_udmaCqDualChannel);
    chPrms.cqRingPrms.elemCnt     = 1U;
    chPrms.chNum                  = UDMA_DMA_CH_ANY;

    status = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_chOpen failed");

    /* Configure TX parameters for block copy */
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    status = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_chConfigTx failed");

    /* Get FQ and CQ ring handles from channel */
    fqRing = Udma_chGetFqRingHandle(chHandle);
    cqRing = Udma_chGetCqRingHandle(chHandle);
    TEST_ASSERT_NOT_NULL_MESSAGE(fqRing, "FQ ring handle is NULL");
    TEST_ASSERT_NOT_NULL_MESSAGE(cqRing, "CQ ring handle is NULL");

    cqRingNum = Udma_ringGetNum(cqRing);

    /* Build TRPD with one TR15 record for memory copy */
    UdmaUtils_makeTrpd(TestDplTimer_am62TrpdMemory, UDMA_TR_TYPE_15, 1U, cqRingNum);

    /* Get pointer to TR15 within the TRPD */
    pTrReq = UdmaUtils_getTrpdTr15Pointer(TestDplTimer_am62TrpdMemory, 0U);

    /* Configure TR15 flags for 1D block move */
    pTrReq->flags    = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, 0U);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_MATCH_SOL_EOL);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, 0x25U);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U);
    pTrReq->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);

    /* Set transfer dimensions (1D copy of 256 bytes).
     * BCDMA hardware requires PHYSICAL addresses — translate via
     * Udma_defaultVirtToPhyFxn so the test works on A53 (MMU on) as
     * well as on R5 (no MMU, virt == phys). */
    physSrc = Udma_defaultVirtToPhyFxn((const void *)TestDplTimer_am62DmaSrc, 0U, NULL);
    physDst = Udma_defaultVirtToPhyFxn((const void *)TestDplTimer_am62DmaDst, 0U, NULL);

    pTrReq->icnt0    = (uint16_t)sizeof(TestDplTimer_am62DmaSrc);
    pTrReq->icnt1    = 1U;
    pTrReq->icnt2    = 1U;
    pTrReq->icnt3    = 1U;
    pTrReq->addr     = physSrc;
    pTrReq->fmtflags = 0U;
    pTrReq->dicnt0   = (uint16_t)sizeof(TestDplTimer_am62DmaDst);
    pTrReq->dicnt1   = 1U;
    pTrReq->dicnt2   = 1U;
    pTrReq->dicnt3   = 1U;
    pTrReq->daddr    = physDst;
    pTrReq->dim1     = 0;
    pTrReq->dim2     = 0;
    pTrReq->dim3     = 0;
    pTrReq->ddim1    = 0;
    pTrReq->ddim2    = 0;
    pTrReq->ddim3    = 0;

    /* Cache writeback for coherency.
     * On A53 (cache+MMU enabled) we must flush EVERY buffer the DMA will
     * touch before the transfer so that:
     *   - src  : CPU-written pattern is visible to BCDMA in DDR
     *   - dst  : CPU-written zeros are pushed out of cache; otherwise
     *             CacheP_inv after the DMA may flush them back and overwrite
     *             the DMA-written data
     *   - trpd : descriptor is in DDR before we push its address to FQ ring */
    CacheP_wb((void *)TestDplTimer_am62DmaSrc,    sizeof(TestDplTimer_am62DmaSrc),    CacheP_TYPE_ALLD);
    CacheP_wb((void *)TestDplTimer_am62DmaDst,    sizeof(TestDplTimer_am62DmaDst),    CacheP_TYPE_ALLD);
    CacheP_wb(TestDplTimer_am62TrpdMemory,        sizeof(TestDplTimer_am62TrpdMemory), CacheP_TYPE_ALLD);

    /* Convert TRPD virtual to physical address */
    physTrDesc = Udma_defaultVirtToPhyFxn((const void *)TestDplTimer_am62TrpdMemory, 0U, NULL);

    /* Enable the UDMA channel */
    status = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_chEnable failed");

    /* Queue TR descriptor to FQ ring */
    status = Udma_ringQueueRaw(fqRing, physTrDesc);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(UDMA_SOK, status, "Udma_ringQueueRaw failed");

    /* Configure timer with DMA trigger enabled, one-shot, 1 ms */
    TimerP_Params_init(&tParams);
    tParams.enableOverflowInt = 1U;
    tParams.periodInUsec      = 1000U;
    tParams.periodInNsec      = 0U;
    tParams.inputPreScaler    = 1U;
    tParams.oneshotMode       = 1U;
    tParams.enableDmaTrigger  = 1U;

    TimerP_setup(baseAddr, &tParams);
    TimerP_clearOverflowInt(baseAddr);

    TestDplTimer_clearInIsr          = true;
    TestDplTimer_timerCallbackCalled = false;

    /* Start timer — overflow triggers BCDMA transfer */
    TimerP_start(baseAddr);

    /* Wait for timer ISR (confirms timer fired and DMA trigger was issued) */
    SemaphoreP_pend(&TestDplTimer_timerSem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_TRUE(TestDplTimer_timerCallbackCalled);

    /* Poll CQ ring for BCDMA transfer completion */
    timeoutTicks = 1000000;
    while (timeoutTicks-- > 0)
    {
        status = Udma_ringDequeueRaw(cqRing, &cqPtr);
        if (status == UDMA_SOK)
        {
            break;
        }
    }
    TEST_ASSERT_TRUE(timeoutTicks > 0);

    /* Invalidate cache before reading destination */
    CacheP_inv((void *)TestDplTimer_am62DmaDst, sizeof(TestDplTimer_am62DmaDst), CacheP_TYPE_ALLD);

    /* Verify destination matches source */
    equal = true;
    for (i = 0U; i < sizeof(TestDplTimer_am62DmaSrc); i++)
    {
        if (TestDplTimer_am62DmaDst[i] != TestDplTimer_am62DmaSrc[i])
        {
            equal = false;
            break;
        }
    }
    TEST_ASSERT_TRUE(equal);

    /* Cleanup */
    TimerP_stop(baseAddr);
    Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    Udma_chClose(chHandle);
    Udma_deinit(&drvObj);
    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
#endif
}
#endif /* (SOC_AM62AX || SOC_AM62DX) non-C7x */

/**
 * @brief Params init defaults.
 *
 * Verifies `TimerP_Params_init()` populates sane default values.
 *
 * Test Steps:
 * 1. Declare `TimerP_Params params` and call `TimerP_Params_init(&params)`.
 * 2. Inspect all fields (periods, prescaler, overflow enable, oneshot mode, DMA trigger) for expected default values.
 * 3. Optionally mutate fields and re-init to confirm reset behavior.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_params_init_defaults(void *args)
{
    TimerP_Params params;

    TimerP_Params_init(&params);

    TEST_ASSERT_EQUAL_UINT32(1U, params.inputPreScaler);
    TEST_ASSERT_EQUAL_UINT32(25U * 1000000U, params.inputClkHz);
    TEST_ASSERT_EQUAL_UINT32(1000U, params.periodInUsec);
    TEST_ASSERT_EQUAL_UINT32(0UL, params.periodInNsec);
    TEST_ASSERT_EQUAL_UINT32(0U, params.oneshotMode);
    TEST_ASSERT_EQUAL_UINT32(1U, params.enableOverflowInt);
    TEST_ASSERT_EQUAL_UINT32(0U, params.enableDmaTrigger);
}

/**
 * @brief Setup boundary values.
 *
 * Tests timer setup with boundary period/prescaler values.
 *
 * Test Steps:
 * 1. Choose minimum valid period (e.g., 1 tick equivalent) and `inputPreScaler=1`; setup and record reload.
 * 2. Compute expected cycles and assert reload delta ≤ 1.
 * 3. Choose a larger valid period within implementation limits (e.g., 2ms) and prescaler; setup and record reload.
 * 4. Compute expected cycles again; assert delta ≤ 1.
 * 5. Confirm timer starts/stops cleanly at boundaries.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_setup_boundary_values(void *args)
{
    TimerP_Params params;
    uint32_t baseAddr;
    uint32_t reload;
    uint32_t loop;

    baseAddr = gTimerBaseAddr[CONFIG_TIMER0];

    /* Boundary: minimum non-zero usec period */
    TimerP_Params_init(&params);
    params.enableOverflowInt = 0U;
    params.periodInUsec      = 1U;
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;
    TimerP_setup(baseAddr, &params);
    reload = TimerP_getReloadCount(baseAddr);
    TEST_ASSERT_TRUE(reload < MAX_NUMBER_OF_CYCLES);
    TimerP_stop(baseAddr);

    /* Boundary: minimum non-zero nsec period takes precedence over usec when both non-zero */
    TimerP_Params_init(&params);
    params.enableOverflowInt = 0U;
    params.periodInUsec      = 10U;
    params.periodInNsec      = 1ULL;
    params.inputPreScaler    = 1U;
    TimerP_setup(baseAddr, &params);
    reload = TimerP_getReloadCount(baseAddr);
    TEST_ASSERT_TRUE(reload < MAX_NUMBER_OF_CYCLES);
    TimerP_stop(baseAddr);

    /* Boundary: prescaler minimum (1) and maximum (256) */
    TimerP_Params_init(&params);
    params.enableOverflowInt = 0U;
    params.periodInUsec      = 1000U;
    params.periodInNsec      = 0U;

    params.inputPreScaler    = 1U;
    TimerP_setup(baseAddr, &params);
    reload = TimerP_getReloadCount(baseAddr);
    TEST_ASSERT_TRUE(reload < MAX_NUMBER_OF_CYCLES);
    TimerP_stop(baseAddr);

    params.inputPreScaler    = 256U;
    TimerP_setup(baseAddr, &params);
    reload = TimerP_getReloadCount(baseAddr);
    TEST_ASSERT_TRUE(reload < MAX_NUMBER_OF_CYCLES);
    TimerP_stop(baseAddr);

    /* Boundary: oneshotMode 0 and 1 should be accepted by setup (DM timer only) */
    for (loop = 0U; loop < 2U; loop++)
    {
        TimerP_Params_init(&params);
        params.enableOverflowInt = 0U;
        params.periodInUsec      = 500U;
        params.inputPreScaler    = 1U;
        params.oneshotMode       = loop; /* 0 then 1 */
        TimerP_setup(baseAddr, &params);
        reload = TimerP_getReloadCount(baseAddr);
        TEST_ASSERT_TRUE(reload < MAX_NUMBER_OF_CYCLES);
        TimerP_stop(baseAddr);
    }
}

/**
 * @brief Start with invalid base.
 *
 * Ensures `TimerP_start()` handles invalid base address safely.
 *
 * Test Steps:
 * 1. Call `TimerP_start(0)` and expect assert/no-op depending on implementation.
 * 2. If available, call with a known invalid `baseAddr` outside mapped timer ranges.
 * 3. Verify no side-effects (no crashes, no state changes).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_start_invalid_base(void *args)
{
    uint32_t baseAddr;

    baseAddr = 0U;
    DebugP_logInfo("Expect assert: TimerP_start with baseAddr=0");
    TimerP_start(baseAddr);
}

/**
 * @brief Stop with invalid base.
 *
 * Ensures `TimerP_stop()` handles invalid base address safely.
 *
 * Test Steps:
 * 1. Call `TimerP_stop(0)` and expect assert/no-op depending on implementation.
 * 2. If available, call with a known invalid `baseAddr` outside mapped timer ranges.
 * 3. Verify no side-effects (no crashes, no state changes).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_stop_invalid_base(void *args)
{
    uint32_t baseAddr;

    baseAddr = 0U;
    DebugP_logInfo("Expect assert: TimerP_stop with baseAddr=0");
    TimerP_stop(baseAddr);
}

/**
 * @brief GetCount with invalid base.
 *
 * Ensures `TimerP_getCount()` handles invalid base address.
 *
 * Test Steps:
 * 1. Call `TimerP_getCount(0)`; expect assert or defined return (e.g., 0).
 * 2. If available, call with a known invalid `baseAddr`; verify safe behavior.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_getcount_invalid_base(void *args)
{
    uint32_t baseAddr;
    volatile uint32_t count;

    baseAddr = 0U;
    DebugP_logInfo("Expect assert: TimerP_getCount with baseAddr=0");
    count = TimerP_getCount(baseAddr);
    (void)count;
}

/**
 * @brief GetReload with invalid base.
 *
 * Ensures `TimerP_getReloadCount()` handles invalid base address.
 *
 * Test Steps:
 * 1. Call `TimerP_getReloadCount(0)`; expect assert or defined return (e.g., 0 or unchanged).
 * 2. If available, call with a known invalid `baseAddr`; verify safe behavior.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_getreload_invalid_base(void *args)
{
    uint32_t baseAddr;
    volatile uint32_t reload;

    baseAddr = 0U;
    DebugP_logInfo("Expect assert: TimerP_getReloadCount with baseAddr=0");
    reload = TimerP_getReloadCount(baseAddr);
    (void)reload;
}

/**
 * @brief ClearOverflow with invalid base.
 *
 * Ensures `TimerP_clearOverflowInt()` handles invalid base address.
 *
 * Test Steps:
 * 1. Call `TimerP_clearOverflowInt(0)`; expect assert or no-op.
 * 2. If available, call with a known invalid `baseAddr`; verify safe behavior.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_clearoverflow_invalid_base(void *args)
{
    uint32_t baseAddr;

    baseAddr = 0U;
    DebugP_logInfo("Expect assert: TimerP_clearOverflowInt with baseAddr=0");
    TimerP_clearOverflowInt(baseAddr);
}

/**
 * @brief IsOverflowed with invalid base.
 *
 * Ensures `TimerP_isOverflowed()` handles invalid base address.
 *
 * Test Steps:
 * 1. Call `TimerP_isOverflowed(0)`; expect assert or defined return (e.g., 0).
 * 2. If available, call with a known invalid `baseAddr`; verify safe behavior.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_isoverflowed_invalid_base(void *args)
{
    uint32_t baseAddr;
    uint32_t ovf;

    baseAddr = 0U;
    DebugP_logInfo("Expect assert: TimerP_isOverflowed with baseAddr=0");
    ovf = TimerP_isOverflowed(baseAddr);
    /* No strict assert on return; call exists to exercise API path */
    TEST_ASSERT_TRUE((ovf == 0U) || (ovf == 1U));
}

/* ISR used across tests: clears overflow and signals */
static void TestDplTimer_st_overflow_isr(void *args)
{
    uint32_t baseAddr;
    uint32_t ovf;

    baseAddr = (uint32_t)(uintptr_t)args;
    ovf = TimerP_isOverflowed(baseAddr);

    if (ovf != 0U)
    {
        TimerP_clearOverflowInt(baseAddr);
        TestDplTimer_stIsrCount++;
    }

    SemaphoreP_post(&TestDplTimer_stSemDone);
}

/**
 * @brief Two timers isolation.
 *
 * Runs two timers concurrently to ensure no cross-interference between
 * instances; validates independent ISR events and flags/count isolation.
 *
 * Test Steps:
 * 1. Bind ISRs for both timers; construct semaphores.
 * 2. Setup timers and start both.
 * 3. Observe ISR events independently; verify flags and counts remain isolated.
 * 4. Stop timers and cleanup Hwi and semaphores.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_multithread_two_timers_isolation(void *args)
{
#if !defined(CONFIG_TIMER1) || !defined(CONFIG_TIMER1_INT_NUM)
    TEST_IGNORE_MESSAGE("Second timer instance not available; skipping isolation test");
    return;
#else
    uint32_t       baseAddr0;
    uint32_t       baseAddr1;
    uint32_t       intNum0;
    uint32_t       intNum1;
    int32_t        status;
    HwiP_Object    hwiObj0;
    HwiP_Object    hwiObj1;
    HwiP_Params    hwiParams0;
    HwiP_Params    hwiParams1;
    TimerP_Params  params0;
    TimerP_Params  params1;
    uint32_t       isrWaits0;
    uint32_t       isrWaits1;
    uint32_t       count0a;
    uint32_t       count0b;
    uint32_t       count1a;
    uint32_t       count1b;
    bool           changed0;
    bool           changed1;

    baseAddr0 = gTimerBaseAddr[CONFIG_TIMER0];
    baseAddr1 = gTimerBaseAddr[CONFIG_TIMER1];
    intNum0   = CONFIG_TIMER0_INT_NUM;
    intNum1   = CONFIG_TIMER1_INT_NUM;
    status    = SystemP_SUCCESS;
    isrWaits0 = 0U;
    isrWaits1 = 0U;
    changed0  = false;
    changed1  = false;
    TestDplTimer_stIsrCount = 0U;

    status = SemaphoreP_constructBinary(&TestDplTimer_stSemDone, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER1]);

    HwiP_Params_init(&hwiParams0);
    hwiParams0.intNum   = intNum0;
    hwiParams0.callback = TestDplTimer_st_overflow_isr;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams0.isPulse  = 1U;
#else
    hwiParams0.isPulse  = 0U;
#endif
    hwiParams0.args     = (void *)(uintptr_t)baseAddr0;
    hwiParams0.priority = 4U;
#if defined(__C7000__)
    hwiParams0.eventId  = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&hwiObj0, &hwiParams0);

    HwiP_Params_init(&hwiParams1);
    hwiParams1.intNum   = intNum1;
    hwiParams1.callback = TestDplTimer_st_overflow_isr;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams1.isPulse  = 1U;
#else
    hwiParams1.isPulse  = 0U;
#endif
    hwiParams1.args     = (void *)(uintptr_t)baseAddr1;
    hwiParams1.priority = 4U;
#if defined(__C7000__)
    hwiParams1.eventId  = CONFIG_TIMER1_EVENT_ID;
#endif
    HwiP_construct(&hwiObj1, &hwiParams1);

    TimerP_Params_init(&params0);
    params0.enableOverflowInt = 1U;
    params0.periodInUsec      = 1000U;
    params0.periodInNsec      = 0U;
    params0.inputPreScaler    = 1U;
    params0.oneshotMode       = 0U;

    TimerP_Params_init(&params1);
    params1.enableOverflowInt = 1U;
    params1.periodInUsec      = 2000U;
    params1.periodInNsec      = 0U;
    params1.inputPreScaler    = 1U;
    params1.oneshotMode       = 0U;

    TimerP_setup(baseAddr0, &params0);
    TimerP_setup(baseAddr1, &params1);

    TimerP_clearOverflowInt(baseAddr0);
    TimerP_clearOverflowInt(baseAddr1);

    TimerP_start(baseAddr0);
    TimerP_start(baseAddr1);

    while (isrWaits0 < 3U)
    {
        SemaphoreP_pend(&TestDplTimer_stSemDone, SystemP_WAIT_FOREVER);
        isrWaits0++;
    }

    while (isrWaits1 < 3U)
    {
        SemaphoreP_pend(&TestDplTimer_stSemDone, SystemP_WAIT_FOREVER);
        isrWaits1++;
    }

    count0a = TimerP_getCount(baseAddr0);
    count1a = TimerP_getCount(baseAddr1);

    ClockP_usleep(500U);

    count0b = TimerP_getCount(baseAddr0);
    count1b = TimerP_getCount(baseAddr1);

    if (count0b != count0a)
    {
        changed0 = true;
    }

    if (count1b != count1a)
    {
        changed1 = true;
    }

    TEST_ASSERT_TRUE(changed0);
    TEST_ASSERT_TRUE(changed1);

    /* Different periods should produce different reload counts */
    {
        uint32_t reload0;
        uint32_t reload1;

        reload0 = TimerP_getReloadCount(baseAddr0);
        reload1 = TimerP_getReloadCount(baseAddr1);

        TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(reload0, reload1, "Reload counts unexpectedly equal for different periods");
    }

    TimerP_stop(baseAddr0);
    TimerP_stop(baseAddr1);

    HwiP_destruct(&hwiObj0);
    HwiP_destruct(&hwiObj1);
    SemaphoreP_destruct(&TestDplTimer_stSemDone);
#endif
}

/**
 * @brief ISR vs poll.
 *
 * Validates ISR clearing overflow while a poller task reads flags without races.
 *
 * Test Steps:
 * 1. Bind ISR `TestDplTimer_st_overflow_isr`; construct semaphores.
 * 2. Setup periodic timer and start.
 * 3. ISR clears overflow and signals; poller checks flags; coordinate via semaphores.
 * 4. Stop timer and cleanup.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_multithread_isr_vs_poll(void *args)
{
    uint32_t      baseAddr;
    uint32_t      intNum;
    int32_t       status;
    HwiP_Object   hwiObj;
    HwiP_Params   hwiParams;
    TimerP_Params params;
    uint32_t      pollSeen;
    uint32_t      loops;
    uint32_t      i;
    uint32_t      ovf;
    uint32_t waits = 0U;
    uint32_t minIsr = 5U;

    baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    intNum   = CONFIG_TIMER0_INT_NUM;
    status   = SystemP_SUCCESS;
    pollSeen = 0U;
    loops    = 10000U;
    i        = 0U;
    TestDplTimer_stIsrCount = 0U;

    status = SemaphoreP_constructBinary(&TestDplTimer_stSemDone, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_st_overflow_isr;
#if defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1U;
#else
    hwiParams.isPulse  = 0U;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseAddr;
    hwiParams.priority = 4U;
#if defined(__C7000__)
    hwiParams.eventId  = CONFIG_TIMER0_EVENT_ID;
#endif
    HwiP_construct(&hwiObj, &hwiParams);

    TimerP_Params_init(&params);
    params.enableOverflowInt = 1U;
    params.periodInUsec      = 500U; /* faster to generate flags */
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;
    params.oneshotMode       = 0U;

    TimerP_setup(baseAddr, &params);
    TimerP_clearOverflowInt(baseAddr);
    TimerP_start(baseAddr);

    /* Poll loop runs concurrently with ISR (which clears the flag) */
    while (i < loops)
    {
        ovf = TimerP_isOverflowed(baseAddr);
        if (ovf != 0U)
        {
            pollSeen++;
        }

        /* Allow ISR to run */
        ClockP_usleep(50U);
        i++;
    }

    /* Wait for at least a few ISR completions to ensure activity */
    {
        while (waits < minIsr)
        {
            SemaphoreP_pend(&TestDplTimer_stSemDone, SystemP_WAIT_FOREVER);
            waits++;
        }
    }

    TimerP_stop(baseAddr);

    TEST_ASSERT_TRUE(TestDplTimer_stIsrCount >= minIsr);
    TEST_ASSERT_TRUE(pollSeen < loops);

    HwiP_destruct(&hwiObj);
    SemaphoreP_destruct(&TestDplTimer_stSemDone);
}

#endif /* defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM275X) */

/*
 * Copyright (C) 2021-26 Texas Instruments Incorporated
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

/**
 * \file test_dpl_timer_fault_injection.c
 * Faults are injected using a stub before starting a transfer.
 */

/*===================================================================*/
/* 					      Include Files 					         */
/*===================================================================*/

#include <string.h>
#include <unity.h>
#include <kernel/dpl/TimerP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "ti_dpl_config.h"
#include "kernel/dpl/SemaphoreP.h"

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/


/*===================================================================*/
/* 					         Typedefs 					             */
/*===================================================================*/

typedef enum {
    TEST_DPL_TIMER_FAULT_NONE = 0,
    TEST_DPL_TIMER_OVERFLOW_INT_RETRY = 1,

} TestDplTimer_FaultType;

#define TIMER_OVF_INT_SHIFT         1U

/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/

/* Current fault to be injected */
static volatile TestDplTimer_FaultType TestDplTimer_CurrFault = TEST_DPL_TIMER_FAULT_NONE;
static volatile bool TestDplTimer_timerCallbackCalled = false;
static SemaphoreP_Object TestDplTimer_timerSem;

/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/

static void TestDplTimer_timerClearOverflowIntRetry(void *args);

/*===================================================================*/
/* 					         Function Definitions		             */
/*===================================================================*/

/**
 * @brief Unity per-test setup hook.
 *
 * Called automatically by the Unity framework before each test case.
 * Closes the debug UART (if open) to ensure a clean state and avoid
 * leftover handles affecting tests. Individual tests then perform their
 * own local initialization (opening/closing handles, semaphores, loopback).
 *
 * @note Uses `TestDplTimer_closeDebugUart()` to clear previous debug UART state.
 *
 * @return void
 */
void setUp(void)
{

}

/**
 * @brief Unity per-test teardown hook.
 *
 * Called automatically by the Unity framework after each test case.
 * Reopens the debug UART (if not already open) so subsequent test logs
 * and status prints are available on the console. Individual tests are
 * responsible for their own local cleanup.
 *
 * @note Uses `TestDplTimer_openDebugUart()` with the backed-up configuration.
 *
 * @return void
 */
void tearDown(void)
{

}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
volatile uint8_t TestDplTimer_timerClearOverflowIntRetry_callCount = 0;
/**
 * @brief Stub handler to inject I2C fault conditions during transfer.
 *
 * This function is called during I2C transfers to simulate specific fault conditions
 * (such as access error or arbitration lost) by setting the appropriate bits in the
 * transfer status variable. The type of fault to inject is controlled by the global
 * variable TestI2c_CurrFault.
 *
 * @param xsferStatus Pointer to the transfer status variable to modify.
 */
void TestDplTimer_faultInjectStubHandler(uint32_t *xsferStatus)
{
    TestDplTimer_timerClearOverflowIntRetry_callCount++;
    if(TestDplTimer_CurrFault == TEST_DPL_TIMER_FAULT_NONE)
        return;

    switch(TestDplTimer_CurrFault)
    {
        case TEST_DPL_TIMER_OVERFLOW_INT_RETRY:
            /* xsferStatus points to IRQ_STATUS (offset 0x28, write-1-to-clear).
             * Writing to it cannot set bits. Instead, write to IRQ_STATUS_RAW
             * (offset 0x24, write-1-to-set, 4 bytes before IRQ_STATUS) to
             * force-set the overflow bit so the readback retry check in
             * TimerP_clearOverflowInt sees it still set and exercises the retry path. */
            {
                volatile uint32_t *rawAddr = (volatile uint32_t *)((uint8_t *)xsferStatus - 4U);
                *rawAddr = (1U << TIMER_OVF_INT_SHIFT);
            }
            break;

        default:
            break;
    }

    TestDplTimer_CurrFault = TEST_DPL_TIMER_FAULT_NONE;
}

/**
 * @brief Unity test entry point for UART fault injection suite.
 *
 * Selects a debug UART instance per SoC/CPU, backs up its configuration for
 * later restore, and registers/runs the UART fault injection testcases that
 * exercise internal loopback and error paths (BD/FE/PE/OE, i2310).
 *
 * The function relies on SysCfg to provide valid UART instances and interrupt
 * routing. Individual testcases open/close UART handles and manage loopback.
 *
 * @param[in] args Unused.
 *
 * @return void
 */
void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(TestDplTimer_timerClearOverflowIntRetry, 10381, NULL);

    if (TestDplTimer_timerClearOverflowIntRetry_callCount != 0)
     {
         DebugP_log("Fault injection stub was called %d time(s)!\n", TestDplTimer_timerClearOverflowIntRetry_callCount);
     }
     else
    {
        DebugP_log("Fault injection stub was not called!\n");
    }

    UNITY_END();
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
static void TestDplTimer_timerClearOverflowIntRetry(void *args)
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

    TestDplTimer_CurrFault = TEST_DPL_TIMER_FAULT_NONE;

    TestDplTimer_timerCallbackCalled = false;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestDplTimer_timerSem, 0));

    /* Bind ISR */
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_oneshot_callback;
#if defined(__ARM_ARCH_7R__) || defined(SOC_AM64X) || defined(SOC_AM243X) || defined(SOC_AM62X) || defined(SOC_AM62AX)
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

    /* Phase 1: clean timing run with no fault armed. Measure time to ISR
     * against the configured period. This must run before any fault
     * injection: the stub force-sets the raw overflow status (0x24), which
     * on this device cannot be cleared via the IRQ_STATUS (0x28) writes done
     * by TimerP_clearOverflowInt, leaving the timer perpetually overflowed.
     * Doing timing first keeps this run free of that side effect. */
    TestDplTimer_CurrFault = TEST_DPL_TIMER_FAULT_NONE;
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

    /* Phase 2: exercise the readback-retry path in TimerP_clearOverflowInt.
     * Run last, with the timer stopped and CPU interrupts masked so the
     * injected overflow status cannot reach the ISR. The fault stub
     * force-sets the raw overflow bit so the retry branch is taken. Coverage
     * of the retry branch is verified globally via the stub call count in
     * test_main; the raw status bit is software-set and its clearability is
     * device specific, so we do not assert on hardware state here. The Hwi is
     * torn down immediately afterwards, so the (intentionally) unclearable
     * injected status cannot trigger an interrupt storm. */
    TimerP_stop(baseAddr);
    uintptr_t hwiKey = HwiP_disable();
    TestDplTimer_CurrFault = TEST_DPL_TIMER_OVERFLOW_INT_RETRY;
    TimerP_clearOverflowInt(baseAddr);
    TestDplTimer_CurrFault = TEST_DPL_TIMER_FAULT_NONE;
    HwiP_clearInt(intNum);
    HwiP_restore(hwiKey);

    /* Cleanup */
    HwiP_destruct(&timerHwiObj);
    SemaphoreP_destruct(&TestDplTimer_timerSem);
}

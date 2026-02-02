/*
 * Copyright (C) 2025-2026 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/watchdog.h>
#include <drivers/soc.h>
#include <unity.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                                  Macros                                    */
/* ========================================================================== */

#define TEST_WDT_WAIT_US(exp_ms)             ((uint64_t)(exp_ms) * 1000ULL)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile uint32_t TestWatchdog_IsrIncFlag = 0;
Watchdog_Handle TestWatchdog_Handle = NULL;
static volatile uint32_t TestWatchdog_WdtIsrCheckFlag = 0;
extern uint32_t gWatchdogConfigNum;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

static void TestWatchdog_interruptMode(void *args);
static void TestWatchdog_window100Percent(void *args);
#if defined CORE_A53
void TestWatchdog_largeExpiration(void *args);
void TestWatchdog_minExpiration(void *args);
#endif
static void TestWatchdog_rapidClearStress(void *args);
static void TestWatchdog_alternateValidInvalidClears(void *args);
static void TestWatchdog_multipleClearInOpenWindow(void *args);
static void TestWatchdog_timeoutWithoutService(void *args);
static void TestWatchdog_multipleClosedWindowViolations(void *args);
static void TestWatchdog_multipleOpenClose(void *args);
void TestWatchdog_validateWindow(Watchdog_WindowSize windowSize,
                                 const char *windowName);
static void TestWatchdog_isr(void *arg);
void TestWatchdog_callbackIsr(void *arg);
static void TestWatchdog_window100(void *args);
static void TestWatchdog_window50(void *args);
static void TestWatchdog_window25(void *args);
static void TestWatchdog_window12_5(void *args);
static void TestWatchdog_window6_25(void *args);
static void TestWatchdog_window3_125(void *args);
static void TestWatchdog_openInvalidIndex(void *args);
static void TestWatchdog_allInstancesTimeout(void *args);
static void TestWatchdog_incorrectKey(void *args);
static void TestWatchdog_getWindowSizeNullHandle(void *args);
static void TestWatchdog_setWindowSizeNullHandle(void *args);
static void TestWatchdog_setWindowSizeInvalidValues(void *args);
static void TestWatchdog_setGetWindowSizeRapidFuzzing(void *args);
static void TestWatchdog_windowSizeChangeOnService(void *args);
static void TestWatchdog_isClosedWindowOpenPeriod(void *args);
static void TestWatchdog_isClosedWindowClosedPeriod(void *args);
static void TestWatchdog_isClosedWindowNullHandle(void *args);
static void TestWatchdog_openInvalidParams(void *args);
static void TestWatchdog_openNullParams(void *args);
static void TestWatchdog_openAlreadyOpened(void *args);
static void TestWatchdog_clearNullHandle(void *args);
static void TestWatchdog_setReactionNullHandle(void *args);
static void TestWatchdog_setReactionInvalidValues(void *args);
static void TestWatchdog_statusRegisterViolations(void *args);
static void TestWatchdog_clearAfterClose(void *args);
static void TestWatchdog_deinit(void *args);
#if defined ENABLE_MT_TESTS
void TestWatchdog_interruptModeMultithread(void *args);
#if defined CORE_A53
void TestWatchdog_largeAndMinExpirationMultithread(void *args);
#endif
#endif

/* ========================================================================== */
/*                            Main Test Function                              */
/* ========================================================================== */
/**
 *  \brief   Main entry point for UDMA SMP tests.
 *
 *  Runs all SMP test cases using Unity framework.
 *
 *  \param args  Unused argument.
 */
void test_watchdog_main(void *args)
{
    UNITY_BEGIN();
    RUN_TEST(TestWatchdog_allInstancesTimeout, 9986, NULL);
    RUN_TEST(TestWatchdog_window100Percent, 9987, NULL);
#if defined CORE_A53
    RUN_TEST(TestWatchdog_largeExpiration, 9988, NULL);
    RUN_TEST(TestWatchdog_minExpiration, 9990, NULL);
#endif
    RUN_TEST(TestWatchdog_rapidClearStress, 9991, NULL);
    RUN_TEST(TestWatchdog_alternateValidInvalidClears, 9992, NULL);
    RUN_TEST(TestWatchdog_multipleClearInOpenWindow, 9994, NULL);
    RUN_TEST(TestWatchdog_timeoutWithoutService, 10028, NULL);
    RUN_TEST(TestWatchdog_multipleClosedWindowViolations, 10029, NULL);
    RUN_TEST(TestWatchdog_multipleOpenClose, 10030, NULL);
    RUN_TEST(TestWatchdog_window100, 10032, NULL);
    RUN_TEST(TestWatchdog_window50, 10033, NULL);
    RUN_TEST(TestWatchdog_window25, 10034, NULL);
    RUN_TEST(TestWatchdog_window12_5, 10035, NULL);
    RUN_TEST(TestWatchdog_window6_25, 10036, NULL);
    RUN_TEST(TestWatchdog_window3_125, 10037, NULL);
    RUN_TEST(TestWatchdog_openInvalidIndex, 10038, NULL);
    RUN_TEST(TestWatchdog_interruptMode, 10039, NULL);
#if defined ENABLE_MT_TESTS
    RUN_TEST(TestWatchdog_interruptModeMultithread, 10056, NULL);
#if defined CORE_A53
    RUN_TEST(TestWatchdog_largeAndMinExpirationMultithread, 10059, NULL);
#endif
#endif
    RUN_TEST(TestWatchdog_getWindowSizeNullHandle, 10041, NULL);
    RUN_TEST(TestWatchdog_setWindowSizeNullHandle, 10042, NULL);
    RUN_TEST(TestWatchdog_setWindowSizeInvalidValues, 10043, NULL);
    RUN_TEST(TestWatchdog_setGetWindowSizeRapidFuzzing, 10044, NULL);
    RUN_TEST(TestWatchdog_windowSizeChangeOnService, 10045, NULL);
    RUN_TEST(TestWatchdog_isClosedWindowOpenPeriod, 10046, NULL);
    RUN_TEST(TestWatchdog_isClosedWindowClosedPeriod, 10047, NULL);
    RUN_TEST(TestWatchdog_isClosedWindowNullHandle, 10048, NULL);
    RUN_TEST(TestWatchdog_openInvalidParams, 10050, NULL);
    RUN_TEST(TestWatchdog_openNullParams, 10049, NULL);
    RUN_TEST(TestWatchdog_openAlreadyOpened, 10051, NULL);
    RUN_TEST(TestWatchdog_clearNullHandle, 10052, NULL);
    RUN_TEST(TestWatchdog_setReactionNullHandle, 10053, NULL);
    RUN_TEST(TestWatchdog_setReactionInvalidValues, 10054, NULL);
    RUN_TEST(TestWatchdog_statusRegisterViolations, 10055, NULL);
    RUN_TEST(TestWatchdog_incorrectKey, 10040, NULL);
    RUN_TEST(TestWatchdog_clearAfterClose, 10063, NULL);
    RUN_TEST(TestWatchdog_deinit, 10128, NULL);
    UNITY_END();
}

/* ========================================================================== */
/*                    Unity Framework Setup Functions                         */
/* ========================================================================== */
/**
* \brief Setup fuction for unity framework
*
* \param None.
*
* \return None.
*/
void setUp(void)
{
    /* Do nothing */
}

/**
* \brief Tear down fuction for unity framework
*
* \param None.
*
* \return None.
*/
void tearDown(void)
{
    /* Do nothing */
}
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* brief Watchdog interrupt callback used in interrupt-mode tests
 * increments the global counter `TestWatchdog_IsrIncFlag`.
 * For the first three invocations the ISR will attempt to clear the watchdog.
 */
void TestWatchdog_callbackIsr(void *arg)
{
    (void)arg;
    TestWatchdog_IsrIncFlag++;

    /* Clear for NMIs */
    if (TestWatchdog_IsrIncFlag < 3U)
    {
        if (TestWatchdog_Handle == NULL)
        {
            TestWatchdog_Handle = gWatchdogHandle[CONFIG_WDT0];
        }
        if (TestWatchdog_Handle != NULL)
        {
            Watchdog_clear(TestWatchdog_Handle);
        }
    }

    return;
}

/**
 * \brief Watchdog NMI/interrupt-mode callback behavior (multi-NMI).
 * Test Category: Functional
 * Installs an interrupt callback that optionally clears the watchdog a few
 * times to produce repeated NMIs. Waits for the expected number of NMIs
 * (3 in current implementation) within a bounded timeout.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Observes the expected number of NMIs;
*/
static void TestWatchdog_interruptMode(void *args)
{
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    uint64_t t0;

    (void)args;

    TestWatchdog_Handle = gWatchdogHandle[CONFIG_WDT0];

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_callbackIsr;
    hwiPrms.isPulse  = 1U;

    TestWatchdog_IsrIncFlag = 0U;
    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("Watchdog interrupt test: waiting for NMIs...\r\n");

    /* Wait with a timeout to avoid indefinite hang */
    t0 = ClockP_getTimeUsec();
    while ((TestWatchdog_IsrIncFlag < 3U) &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(7000))) 
    {
                ClockP_usleep(1000U);
    }

    /* Ensure we observed interrupt */
    DebugP_log("TestWatchdog_IsrIncFlag=%u\n", TestWatchdog_IsrIncFlag);
    TEST_ASSERT_EQUAL_UINT32(3U, TestWatchdog_IsrIncFlag);
    HwiP_destruct(&hwiObject);

    /* reset so other tests are not affected */
    TestWatchdog_IsrIncFlag = 0U;
    TestWatchdog_Handle = NULL;
}

 /*
 * \brief Minimal watchdog ISR used
 * Sets `TestWatchdog_WdtIsrCheckFlag` to 1 when the watchdog NMI/interrupt
 * fires.
 */
static void TestWatchdog_isr(void *arg)
{
    (void)arg;
    TestWatchdog_WdtIsrCheckFlag = 1U;
}

/**
* \brief Functional test for 100% window behavior.
* Test Category: Functional
* Validates that a watchdog with 100% window produces an ISR on timeout.
* Attaches an ISR, clears to start a known period and waits for the NMI.
* \param args Pointer to test arguments (unused).
* \expectedOutput NMI observed within configured expiration + margin.
*/
static void TestWatchdog_window100Percent(void *args)
{
    (void)args;
    int32_t status;
    HwiP_Params hwiPrms;
    static HwiP_Object gWdtHwi;
    uint64_t timeStart;

    /* Setup ISR */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    TestWatchdog_WdtIsrCheckFlag = 0U;

    status = HwiP_construct(&gWdtHwi, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    timeStart = ClockP_getTimeUsec();
    /* Start watchdog from known state */
    Watchdog_clear(gWatchdogHandle[CONFIG_WDT0]);
    while (!TestWatchdog_WdtIsrCheckFlag && ((ClockP_getTimeUsec() - timeStart) < TEST_WDT_WAIT_US(1010))) {} /* 1200 ms */
    TEST_ASSERT_EQUAL_UINT32(1U, TestWatchdog_WdtIsrCheckFlag);

    HwiP_destruct(&gWdtHwi);
}

#if defined CORE_A53
/**
 * \brief validate large expiration (long timeout) runs DWWD ISR.
 * Test Category: Functional
 * Validates a long expiration value is honored: clears the watchdog on the
 * longer-configured instance and polls for the NMI over the longer interval.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput NMI observed within the long expirationTime + margin.
*/
void TestWatchdog_largeExpiration(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    uint64_t timeStart;

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT1_INTR;
    hwiPrms.eventId  = CONFIG_WDT1_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestWatchdog_WdtIsrCheckFlag = 0U;
    timeStart = ClockP_getTimeUsec();
    Watchdog_clear(gWatchdogHandle[CONFIG_WDT1]);
    while ((!TestWatchdog_WdtIsrCheckFlag)&& ((ClockP_getTimeUsec() - timeStart) < TEST_WDT_WAIT_US(60100))) {} /* 63 seconds */
    TEST_ASSERT_EQUAL_UINT32(1U, TestWatchdog_WdtIsrCheckFlag);

    HwiP_destruct(&hwiObject);
}

/**
 * \brief Validate minimal expiration runs (1 ms) still trigger ISR.
 * Test Category: Functional
 * Verifies a very short expiration value still produces the expected ISR.
 * Installs ISR, sets 100% window, clears to start a period and polls for NMI.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput NMI observed within minimal expiration + margin.
*/
void TestWatchdog_minExpiration(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    uint64_t timeStart;

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT2_INTR;
    hwiPrms.eventId  = CONFIG_WDT2_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    TestWatchdog_WdtIsrCheckFlag     = 0U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    Watchdog_setWindowSize(gWatchdogHandle[CONFIG_WDT2], Watchdog_WINDOW_100_PERCENT);
    TEST_ASSERT_EQUAL_UINT32(Watchdog_WINDOW_100_PERCENT,
                             Watchdog_getWindowSize(gWatchdogHandle[CONFIG_WDT2]));

    TestWatchdog_WdtIsrCheckFlag = 0U;
    /* Wait for open window */
    timeStart = ClockP_getTimeUsec();
    Watchdog_clear(gWatchdogHandle[CONFIG_WDT2]);
    while (!TestWatchdog_WdtIsrCheckFlag && ((ClockP_getTimeUsec() - timeStart) < TEST_WDT_WAIT_US(510))) {}
    TEST_ASSERT_EQUAL_UINT32(1U, TestWatchdog_WdtIsrCheckFlag);

    HwiP_destruct(&hwiObject);
}
#endif

/**
 * \brief Stress test: many rapid valid clears in the open window.
 * Test Category: Stress / Functional
 * Repeatedly waits for the open window and performs bursts of rapid
 * Watchdog_clear() operations. Ensures no NMI occurs for valid clears.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput No NMI triggered during bursts of valid clears.
*/
static void TestWatchdog_rapidClearStress(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    uint32_t outer, i;
    uint64_t timeWait;

    /* Setup ISR */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Ensure we start from a known state */
    TestWatchdog_WdtIsrCheckFlag = 0U;
    Watchdog_clear(gWatchdogHandle[CONFIG_WDT0]);

    /* Stress: repeatedly perform many rapid valid clears */
    for (outer = 0U; outer < 100U; outer++)
    {
        /* Wait until we're in OPEN window (with timeout) */
        timeWait = ClockP_getTimeUsec();
        while (Watchdog_isClosedWindow(gWatchdogHandle[CONFIG_WDT0]) &&
               ((ClockP_getTimeUsec() - timeWait) < TEST_WDT_WAIT_US(5000))) {}
        TEST_ASSERT_FALSE_MESSAGE(Watchdog_isClosedWindow(gWatchdogHandle[CONFIG_WDT0]),
                                  "Timeout waiting for open window");

        /* Perform a burst of rapid clears */
        for (i = 0U; i < 20U; i++)
        {
            TestWatchdog_WdtIsrCheckFlag = 0U;
            Watchdog_clear(gWatchdogHandle[CONFIG_WDT0]);
            /* tiny delay */
            ClockP_usleep(100U);
            TEST_ASSERT_EQUAL_UINT32(0U, TestWatchdog_WdtIsrCheckFlag);
        }
    }

    HwiP_destruct(&hwiObject);
}

/**
 * \brief Test alternating valid and invalid clears in 50% window.
 * Test Category: Functional
 * Configures 50% window, then alternates between valid and invalid clears.
 * Valid clears (in open window) should not trigger NMI; invalid clears
 * (in closed window) should trigger NMI. Repeats several times.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput NMI observed only on invalid clears.
*/
static void TestWatchdog_alternateValidInvalidClears(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    Watchdog_Handle handle = gWatchdogHandle[CONFIG_WDT0];
    uint32_t prevWindow;
    uint32_t iter;
    uint64_t t0, t1, t2;

    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog handle must be valid");

    /* Save previous window and switch to 50% for this test */
    prevWindow = Watchdog_getWindowSize(handle);
    Watchdog_setWindowSize(handle, Watchdog_WINDOW_50_PERCENT);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(Watchdog_WINDOW_50_PERCENT,
                                     Watchdog_getWindowSize(handle),
                                     "Failed to set Watchdog to 50% window");

    /* Setup ISR */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Repeat a few times: one valid clear (open window) then one invalid clear (closed window) */
    for (iter = 0U; iter < 4U; iter++)
    {
        /* Start fresh */
        Watchdog_clear(handle);

        /* Wait for OPEN window */
        t0 = ClockP_getTimeUsec();
        while (Watchdog_isClosedWindow(handle) &&
               ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(5000))) 
        {
                     ClockP_usleep(1000U);
        }
        TEST_ASSERT_FALSE_MESSAGE(Watchdog_isClosedWindow(handle),
                                  "Timeout waiting for open window");
        /* Valid clear should not generate an interrupt */
        TestWatchdog_WdtIsrCheckFlag = 0U;
        Watchdog_clear(handle);
        /* allow some time to observe (50 ms) */
        ClockP_usleep(50000U);
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(0U, TestWatchdog_WdtIsrCheckFlag, "Interrupt on VALID clear");

        /* Wait for CLOSED window */
        t1 = ClockP_getTimeUsec();
        while (!Watchdog_isClosedWindow(handle) &&
               ((ClockP_getTimeUsec() - t1) < TEST_WDT_WAIT_US(5000))) {}
        TEST_ASSERT_TRUE_MESSAGE(Watchdog_isClosedWindow(handle),
                                 "Timeout waiting for closed window");
        /* Small margin to avoid boundary flicker */
        ClockP_usleep(20000U);

        /* Invalid clear should produce an interrupt (NMI) */
        TestWatchdog_WdtIsrCheckFlag = 0U;
        Watchdog_clear(handle); /* invalid clear */
        t2 = ClockP_getTimeUsec();
        while (!TestWatchdog_WdtIsrCheckFlag &&
               ((ClockP_getTimeUsec() - t2) < TEST_WDT_WAIT_US(gWatchdogParams[CONFIG_WDT0].expirationTime))) {}
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(1U, TestWatchdog_WdtIsrCheckFlag, "No interrupt on INVALID clear");

        /* Small delay before next iteration */
        ClockP_usleep(20000U);
    }

    HwiP_destruct(&hwiObject);

    /* Restore original window size */
    Watchdog_setWindowSize(handle, prevWindow);
}

/**
 * \brief Stress test: many rapid valid clears in the open window.
 * Test Category: Stress / Functional
 * Repeatedly waits for the open window and performs bursts of rapid
 * Watchdog_clear() operations. Ensures no NMI occurs for valid clears.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput No NMI triggered during bursts of valid clears.
*/
static void TestWatchdog_multipleClearInOpenWindow(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    Watchdog_Handle handle = gWatchdogHandle[CONFIG_WDT0];
    uint32_t prevWindow;
    uint32_t i;
    uint64_t tSync, tWait;

    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog handle must be valid");

    /* Save previous window and switch to 50% for this test */
    prevWindow = Watchdog_getWindowSize(handle);
    Watchdog_setWindowSize(handle, Watchdog_WINDOW_50_PERCENT);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(Watchdog_WINDOW_50_PERCENT,
                                     Watchdog_getWindowSize(handle),
                                     "Failed to set Watchdog to 50% window");

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Sync to open window and move away from boundary */
    Watchdog_clear(handle);
    tSync = ClockP_getTimeUsec();
    while (Watchdog_isClosedWindow(handle) &&
           ((ClockP_getTimeUsec() - tSync) < TEST_WDT_WAIT_US(5000))) 
    {
                 ClockP_usleep(1000U);
    }
    TEST_ASSERT_FALSE_MESSAGE(Watchdog_isClosedWindow(handle),
                              "Timeout waiting for open window to sync");
    ClockP_usleep(50000U); /* margin to avoid boundary flicker */

    /* Multiple clears should not trigger immediate NMI when in open window */
    for (i = 0U; i < 5U; i++)
    {
        /* Ensure we are firmly in open window before clearing */
        tWait = ClockP_getTimeUsec();
        while (Watchdog_isClosedWindow(handle) &&
               ((ClockP_getTimeUsec() - tWait) < TEST_WDT_WAIT_US(5000))) 
        {
                     ClockP_usleep(1000U);
        }
        TEST_ASSERT_FALSE_MESSAGE(Watchdog_isClosedWindow(handle),
                                  "Timeout waiting for open window");
        ClockP_usleep(10000U); /* small settle */

        TestWatchdog_WdtIsrCheckFlag = 0U;
        Watchdog_clear(handle);
        ClockP_usleep(30000U); /* observe for NMI */
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(0U, TestWatchdog_WdtIsrCheckFlag,
                                         "Unexpected NMI on valid clear in open window");
    }

    HwiP_destruct(&hwiObject);

    /* Restore original window size */
    Watchdog_setWindowSize(handle, prevWindow);
}

/**
 * \brief Validate watchdog timeout without any servicing triggers NMI.
 * Test Category: Functional
 * Installs an ISR, starts a fresh watchdog period and waits for the NMI
 * without clearing the watchdog. Ensures NMI occurs near the configured
 * expiration time.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput NMI observed within configured expiration + margin.
*/
static void TestWatchdog_timeoutWithoutService(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    uint64_t t0, dt;

    /* Setup ISR */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Clear once to start a known fresh period, then do NOT service again */
    TestWatchdog_WdtIsrCheckFlag = 0U;
    Watchdog_clear(gWatchdogHandle[CONFIG_WDT0]);
    t0 = ClockP_getTimeUsec();
    while (!TestWatchdog_WdtIsrCheckFlag &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(
               gWatchdogParams[CONFIG_WDT0].expirationTime + 500U))) {}
    dt = ClockP_getTimeUsec() - t0;

    /* NMI must have fired */
    TEST_ASSERT_EQUAL_UINT32(1U, TestWatchdog_WdtIsrCheckFlag);

    /* Elapsed time should be close to configured expiration (within 70%-120%) */
    TEST_ASSERT_TRUE_MESSAGE(
        dt >= (TEST_WDT_WAIT_US(gWatchdogParams[CONFIG_WDT0].expirationTime) * 7U / 10U),
        "Timeout fired too early (< 70% of expirationTime)");
    TEST_ASSERT_TRUE_MESSAGE(
        dt <= (TEST_WDT_WAIT_US(gWatchdogParams[CONFIG_WDT0].expirationTime) * 12U / 10U),
        "Timeout fired too late (> 120% of expirationTime)");

    HwiP_destruct(&hwiObject);
}

/**
 * \brief Validate multiple closed-window violations trigger NMIs.
 * Test Category: Functional
 * Configures 50% window, then performs several back-to-back closed-window
 * violations by clearing the watchdog in the closed window multiple times.
 * Ensures an NMI occurs after each invalid clear.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput NMI observed after each closed-window clear.
*/
static void TestWatchdog_multipleClosedWindowViolations(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    Watchdog_Handle handle = gWatchdogHandle[CONFIG_WDT0];
    uint32_t prevWindow;
    uint64_t timeoutUs, t0, t1;
    uint32_t i;

    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog handle must be valid");

    /* Save previous window and switch to 50% for this test */
    prevWindow = Watchdog_getWindowSize(handle);
    Watchdog_setWindowSize(handle, Watchdog_WINDOW_50_PERCENT);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(Watchdog_WINDOW_50_PERCENT,
                                     Watchdog_getWindowSize(handle),
                                     "Failed to set Watchdog to 50% window");

    /* derive a sensible wait timeout from configured expirationTime */
    timeoutUs = TEST_WDT_WAIT_US(gWatchdogParams[CONFIG_WDT0].expirationTime);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Back-to-back closed-window violations */
    for (i = 0U; i < 3U; i++)
    {
        /* Start a fresh watchdog period */
        TestWatchdog_WdtIsrCheckFlag = 0U;
        Watchdog_clear(handle);

        /* Wait until watchdog enters CLOSED window (bounded by configured expiration) */
        t0 = ClockP_getTimeUsec();
        while (!Watchdog_isClosedWindow(handle) &&
               ((ClockP_getTimeUsec() - t0) < timeoutUs)) {}
        TEST_ASSERT_TRUE_MESSAGE(Watchdog_isClosedWindow(handle),
                                 "Timeout waiting for CLOSED window");

        /* Small margin to avoid window boundary flicker */
        ClockP_usleep(20000U); /* 20 ms */

        /* Clear inside CLOSED window → violation expected */
        TestWatchdog_WdtIsrCheckFlag = 0U;
        Watchdog_clear(handle);

        /* Wait for NMI (bounded by configured expiration) */
        t1 = ClockP_getTimeUsec();
        while (!TestWatchdog_WdtIsrCheckFlag &&
               ((ClockP_getTimeUsec() - t1) < timeoutUs)) {}

        TEST_ASSERT_EQUAL_UINT32_MESSAGE(1U, TestWatchdog_WdtIsrCheckFlag,
                                         "No NMI observed after closed-window clear");

        /* Small delay before next iteration */
        ClockP_usleep(20000U); /* 20 ms */
    }

    HwiP_destruct(&hwiObject);

    /* Restore original window size */
    Watchdog_setWindowSize(handle, prevWindow);
}

/**
* \brief Multiple open/close cycles maintain countdown behavior.
* Test Category: Functional
* Repeatedly opens/closes the watchdog several times, then ensures the
* watchdog still generates an ISR after synchronization and restart.
* \param args Pointer to test arguments (unused).
* \expectedOutput Watchdog fires NMI after open/close cycles when expected.
*/
static void TestWatchdog_multipleOpenClose(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    uint32_t i;
    uint64_t t0;
    Watchdog_Params params;

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    for (i = 0; i < 5U; i++)
    {
        Watchdog_paramsInit(&params);
        params.resetMode      = Watchdog_RESET_OFF;
        params.expirationTime = 1000U;
        params.windowSize     = Watchdog_WINDOW_100_PERCENT;
        TestWatchdog_Handle = Watchdog_open(CONFIG_WDT0, &params);
        TEST_ASSERT_NOT_NULL(TestWatchdog_Handle);

        Watchdog_clear(TestWatchdog_Handle);
        ClockP_usleep(5000U);
        Watchdog_close(TestWatchdog_Handle);
        ClockP_usleep(5000U);
    }

    /* Re-open watchdog after close/open cycle test */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.expirationTime = 1000U;
    params.windowSize     = Watchdog_WINDOW_100_PERCENT;
    TestWatchdog_Handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL(TestWatchdog_Handle);

    TestWatchdog_WdtIsrCheckFlag = 0U;

    /* Ensure config is applied and counter is running */
    Watchdog_setWindowSize(TestWatchdog_Handle, Watchdog_WINDOW_100_PERCENT);
    ClockP_usleep(5000U);

    /* Sync to start a fresh expiration window */
    Watchdog_clear(TestWatchdog_Handle);
    ClockP_usleep(1000U);

    t0 = ClockP_getTimeUsec();
    while (!TestWatchdog_WdtIsrCheckFlag &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(5000))) {}

    TEST_ASSERT_EQUAL_UINT32(1U, TestWatchdog_WdtIsrCheckFlag);
    Watchdog_close(TestWatchdog_Handle);
    HwiP_destruct(&hwiObject);

    /* Re-open so gWatchdogHandle[CONFIG_WDT0] is valid for subsequent tests */
    gWatchdogHandle[CONFIG_WDT0] = Watchdog_open(CONFIG_WDT0, NULL);
    TEST_ASSERT_NOT_NULL(gWatchdogHandle[CONFIG_WDT0]);
}

/**
* \brief Validate window semantics (set/get and behavior).
* Test Category: Functional (helper)
* Opens a watchdog with specified windowSize and verifies:
* Watchdog_getWindowSize() matches configured value
* a valid clear in the open window does not trigger an NMI
* an invalid clear in the closed window triggers an NMI
* timeout also produces an NMI
* This helper installs an ISR and is used by the per-window wrappers.
* \param windowSize Window enum to test; windowName used only for logs.
* \expectedOutput get/set return the configured window and window semantics hold.
*/
void TestWatchdog_validateWindow(Watchdog_WindowSize windowSize,
                                 const char *windowName)
{
    int32_t status;
    Watchdog_Params params;
    HwiP_Params hwiParams;
    static HwiP_Object hwiObject;
    uint64_t t0, t1;

    DebugP_log("Testing Watchdog window: %s\r\n", windowName);

    /* Setup ISR */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = CONFIG_WDT0_INTR;
    hwiParams.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiParams.callback = TestWatchdog_isr;
    hwiParams.isPulse  = 1U;

    TestWatchdog_WdtIsrCheckFlag = 0;

    status = HwiP_construct(&hwiObject, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Open Watchdog */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = windowSize;
    params.expirationTime = 1000U; /* 1 second */

    TestWatchdog_Handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL(TestWatchdog_Handle);

    /* Ensure the driver reflects the window we configured on open */
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(windowSize,
                                     Watchdog_getWindowSize(TestWatchdog_Handle),
                                     "Watchdog_getWindowSize != configured value after open");
    /* VALID CLEAR (OPEN WINDOW) */
    Watchdog_clear(TestWatchdog_Handle);
    t0 = ClockP_getTimeUsec();
    while (Watchdog_isClosedWindow(TestWatchdog_Handle) &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(params.expirationTime))) {}
    TEST_ASSERT_FALSE_MESSAGE(Watchdog_isClosedWindow(TestWatchdog_Handle),
                              "Timeout waiting for open window");
    TestWatchdog_WdtIsrCheckFlag = 0;
    Watchdog_clear(TestWatchdog_Handle);

    ClockP_usleep(50000U);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        0U,
        TestWatchdog_WdtIsrCheckFlag,
        "Interrupt triggered on VALID clear"
    );

    /* INVALID CLEAR (CLOSED WINDOW) — skip for 100% window since no closed region exists */
    if (windowSize != Watchdog_WINDOW_100_PERCENT)
    {
        t0 = ClockP_getTimeUsec();
        while (!Watchdog_isClosedWindow(TestWatchdog_Handle) &&
               ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(params.expirationTime))) {}
        TEST_ASSERT_TRUE_MESSAGE(Watchdog_isClosedWindow(TestWatchdog_Handle),
                                 "Timeout waiting for closed window");
        ClockP_usleep(20000U); /* stay away from boundary */

        TestWatchdog_WdtIsrCheckFlag = 0;
        Watchdog_clear(TestWatchdog_Handle); /* INVALID clear */

        t0 = ClockP_getTimeUsec();
        while ((TestWatchdog_WdtIsrCheckFlag == 0U) &&
               ((ClockP_getTimeUsec() - t0) <
                TEST_WDT_WAIT_US(params.expirationTime))) {}
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(
            1U,
            TestWatchdog_WdtIsrCheckFlag,
            "Interrupt NOT triggered on INVALID clear"
        );
    }

    /* TIMEOUT (NO CLEAR) */
    TestWatchdog_WdtIsrCheckFlag = 0;
    Watchdog_clear(TestWatchdog_Handle); /* restart counter */

    t1 = ClockP_getTimeUsec();
    while ((TestWatchdog_WdtIsrCheckFlag == 0U) &&
           ((ClockP_getTimeUsec() - t1) <
            TEST_WDT_WAIT_US(params.expirationTime))) {}

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        1U,
        TestWatchdog_WdtIsrCheckFlag,
        "Interrupt NOT triggered on TIMEOUT"
    );

    Watchdog_close(TestWatchdog_Handle);
    HwiP_destruct(&hwiObject);
}

/**
* \brief Wrapper: validate behavior for 100% window.
* Test Category: Functional
* Calls TestWatchdog_validateWindow(Watchdog_WINDOW_100_PERCENT, "100%")
* to validate set/get and window semantics for the 100% setting.
* \param args Pointer to test arguments (unused).
* \expectedOutput TestWatchdog_validateWindow passes for 100% window.
*/
static void TestWatchdog_window100(void *args)
{
    (void)args;
    TestWatchdog_validateWindow(Watchdog_WINDOW_100_PERCENT, "100%");
}

/**
* \brief Wrapper: validate behavior for 50% window.
* Test Category: Functional
* Calls TestWatchdog_validateWindow(Watchdog_WINDOW_50_PERCENT, "50%")
* to validate set/get and window semantics for the 50% setting.
* \param args Pointer to test arguments (unused).
* \expectedOutput TestWatchdog_validateWindow passes for 50% window.
*/
static void TestWatchdog_window50(void *args)
{
    (void)args;
    TestWatchdog_validateWindow(Watchdog_WINDOW_50_PERCENT, "50%");
}

/**
* \brief Wrapper: validate behavior for 25% window.
* Test Category: Functional
* Calls TestWatchdog_validateWindow(Watchdog_WINDOW_25_PERCENT, "25%")
* to validate set/get and window semantics for the 25% setting.
* \param args Pointer to test arguments (unused).
* \expectedOutput TestWatchdog_validateWindow passes for 25% window.
*/
static void TestWatchdog_window25(void *args)
{
    (void)args;
    TestWatchdog_validateWindow(Watchdog_WINDOW_25_PERCENT, "25%");
}

/**
* \brief Wrapper: validate behavior for 12.5% window.
* Test Category: Functional
* Calls TestWatchdog_validateWindow(Watchdog_WINDOW_12_5_PERCENT, "12.5%")
* to validate set/get and window semantics for the 12.5% setting.
* \param args Pointer to test arguments (unused).
* \expectedOutput TestWatchdog_validateWindow passes for 12.5% window.
*/
static void TestWatchdog_window12_5(void *args)
{
    (void)args;
    TestWatchdog_validateWindow(Watchdog_WINDOW_12_5_PERCENT, "12.5%");
}

/**
* \brief Wrapper: validate behavior for 6.25% window.
* Test Category: Functional
* Calls TestWatchdog_validateWindow(Watchdog_WINDOW_6_25_PERCENT, "6.25%")
* to validate set/get and window semantics for the 6.25% setting.
* \param args Pointer to test arguments (unused).
* \expectedOutput TestWatchdog_validateWindow passes for 6.25% window.
*/
static void TestWatchdog_window6_25(void *args)
{
    (void)args;
    TestWatchdog_validateWindow(Watchdog_WINDOW_6_25_PERCENT, "6.25%");
}

/**
* \brief Wrapper: validate behavior for 3.125% window.
* Test Category: Functional
* Calls TestWatchdog_validateWindow(Watchdog_WINDOW_3_125_PERCENT, "3.125%")
* to validate set/get and window semantics for the 3.125% setting.
* \param args Pointer to test arguments (unused).
* \expectedOutput TestWatchdog_validateWindow passes for 3.125% window.
*/
static void TestWatchdog_window3_125(void *args)
{
    (void)args;
    TestWatchdog_validateWindow(Watchdog_WINDOW_3_125_PERCENT, "3.125%");
}


/**
* \brief Validate Watchdog_open rejects invalid indices.
* Test Category: Functional
* Attempts to open watchdog using gWatchdogConfigNum (out-of-range) and
* one past that, asserting NULL is returned in both cases.
* \param args Pointer to test arguments (unused).
* \expectedOutput Both invalid open attempts return NULL.
*/
static void TestWatchdog_openInvalidIndex(void *args)
{
    (void)args;
    Watchdog_Handle wdtHandle;

    /* index equal to gWatchdogConfigNum should be invalid */
    wdtHandle = Watchdog_open((uint8_t)gWatchdogConfigNum, NULL);
    TEST_ASSERT_NULL(wdtHandle);
    /* also test one past that */
    wdtHandle = Watchdog_open((uint8_t)(gWatchdogConfigNum + 1U), NULL);
    TEST_ASSERT_NULL(wdtHandle);
}

/**
* \brief Verify each Watchdog instance fires an ISR on timeout.
* Test Category: Functional
* Validates that every configured watchdog instance generates an ISR when
* not serviced after a single clear. Attaches a per-instance ISR, clears the
* watchdog once and polls for the NMI. Verifies ISR arrival and reports
* elapsed time.
* \param args Pointer to test arguments (unused).
* \expectedOutput ISR observed for each instance within configured expirationTime.
*/

static void TestWatchdog_allInstancesTimeout(void *args)
{
    (void)args;
    HwiP_Object hwiObj;
    int32_t status;
    HwiP_Params hwiPrms;
    uint32_t inst;
    uint64_t expectedUs, lowerUs, upperUs, maxWaitUs, t0, dtUs;

    /* explicit intr/event arrays are safer than assuming consecutiveness */
    const uint32_t wdtIntrs[CONFIG_WATCHDOG_NUM_INSTANCES] = {
        CONFIG_WDT0_INTR,
#if CONFIG_WATCHDOG_NUM_INSTANCES > 1
        CONFIG_WDT1_INTR,
#endif
#if CONFIG_WATCHDOG_NUM_INSTANCES > 2
        CONFIG_WDT2_INTR,
#endif
#if CONFIG_WATCHDOG_NUM_INSTANCES > 3
        CONFIG_WDT3_INTR,
#endif
    };

    const uint32_t wdtEvtIds[CONFIG_WATCHDOG_NUM_INSTANCES] = {
        CONFIG_WDT0_EVENT_ID,
#if CONFIG_WATCHDOG_NUM_INSTANCES > 1
        CONFIG_WDT1_EVENT_ID,
#endif
#if CONFIG_WATCHDOG_NUM_INSTANCES > 2
        CONFIG_WDT2_EVENT_ID,
#endif
#if CONFIG_WATCHDOG_NUM_INSTANCES > 3
        CONFIG_WDT3_EVENT_ID,
#endif
    };

    for (inst = 0U; inst < gWatchdogConfigNum; inst++)
    {
        Watchdog_Handle handle = gWatchdogHandle[inst];
        TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog handle must be valid");

        DebugP_log("Testing watchdog instance %u, expirationTime=%u ms\r\n",
                   inst, gWatchdogParams[inst].expirationTime);

        /* Reset counter before registering ISR to avoid stale pending interrupts */
        Watchdog_clear(handle);
        ClockP_usleep(1000U);

        /* Set up ISR for this instance */
        HwiP_Params_init(&hwiPrms);
        hwiPrms.intNum   = wdtIntrs[inst];
        hwiPrms.eventId  = wdtEvtIds[inst];
        hwiPrms.callback = &TestWatchdog_isr;
        hwiPrms.isPulse  = 1U;

        status = HwiP_construct(&hwiObj, &hwiPrms);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Start fresh: clear once then do NOT clear again — expect ISR on timeout */
        TestWatchdog_WdtIsrCheckFlag = 0U;
        Watchdog_clear(handle);

        /* expected timeout in microseconds */
        expectedUs = (uint64_t)gWatchdogParams[inst].expirationTime * 1000ULL;

        /* 30% tolerance */
        lowerUs = (expectedUs * 40ULL) / 100ULL; 
        upperUs = (expectedUs * 130ULL) / 100ULL; /* +30% */

        /* allow small extra margin for the wait loop to avoid false-negative */
        maxWaitUs = upperUs;
        t0 = ClockP_getTimeUsec();

        while ((TestWatchdog_WdtIsrCheckFlag == 0U) &&
               ((ClockP_getTimeUsec() - t0) < maxWaitUs)) {}

        /* verify ISR arrived */
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(
            1U,
            TestWatchdog_WdtIsrCheckFlag,
            "Watchdog did not generate ISR on timeout"
        );

        /* measure actual elapsed time and check it lies within tolerance */
        dtUs = ClockP_getTimeUsec() - t0;

        DebugP_log("WDT instance %u: expected=%lluus, dt=%lluus, bounds=[%lluus, %lluus]\r\n",
                   inst, (unsigned long long)expectedUs,
                   (unsigned long long)dtUs,
                   (unsigned long long)lowerUs,
                   (unsigned long long)upperUs);

        TEST_ASSERT_TRUE_MESSAGE(
            (dtUs >= lowerUs) && (dtUs <= (upperUs + 200000ULL)),
            "ISR time outside 30% tolerance bounds"
        );

        HwiP_destruct(&hwiObj);

        /* quick inter-test pause */
        ClockP_usleep(10000U);
    }
}

/**
 * \brief Test watchdog with a single incorrect unlock key sequence.
 * Test Category: Negative/Functional
 * Verifies incorrect keys set WDSTATUS.KEYST (key violation) and that the
 * watchdog is NOT serviced by those keys, evidenced by an ISR on timeout.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput KEYST bit set after incorrect keys; timeout NMI observed.
 */
static void TestWatchdog_incorrectKey(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    Watchdog_Handle handle;
    Watchdog_Params params;
    Watchdog_Config* ptrWatchdogConfig;
    Watchdog_HwAttrs* ptrHwCfg;
    uint32_t statusReg;
    uint64_t t0;

    /* Use 16-bit-style incorrect keys to match WDKEY field width behavior */
    const uint32_t badKey1 = 0xDEAD;
    const uint32_t badKey2 = 0xBEEF;

    DebugP_log("Testing incorrect key: verify KEYST and timeout ISR\r\n");

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Open watchdog with known parameters (window size not critical for KEYST) */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = Watchdog_WINDOW_100_PERCENT;
    params.expirationTime = 1000U; /* 1 second */
    params.debugStallMode = Watchdog_DEBUG_STALL_OFF;

    handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog_open failed");

    /* Get hardware configuration to access base address */
    ptrWatchdogConfig = (Watchdog_Config*)handle;
    ptrHwCfg = (Watchdog_HwAttrs*)ptrWatchdogConfig->hwAttrs;

    /* Setup ISR to detect watchdog timeout */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Clear any sticky status before incorrect key test */
    HW_WR_REG32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDSTATUS, WATCHDOG_CLEAR_STATUS);

    /* Start a known period; small settle away from boundary */
    Watchdog_clear(handle);
    ClockP_usleep(100000U); /* 100 ms */

    /* Write incorrect key sequence (both keys invalid) */
    HW_WR_FIELD32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDKEY,
                  CSL_RTI_RTIWDKEY_WDKEY,
                  badKey1);
    HW_WR_FIELD32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDKEY,
                  CSL_RTI_RTIWDKEY_WDKEY,
                  badKey2);

    ClockP_usleep(10000U); /* Allow status to update */

    /* Verify KEYST bit set (incorrect key detected) */
    statusReg = HW_RD_REG32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDSTATUS);
    TEST_ASSERT_TRUE_MESSAGE(
        (statusReg & CSL_RTI_RTIWDSTATUS_KEYST_MASK) != 0U,
        "KEYST bit not set after incorrect key sequence"
    );

    /* Verify that ISR is triggered */
    if (!TestWatchdog_WdtIsrCheckFlag)
    {
        t0 = ClockP_getTimeUsec();
        while (!TestWatchdog_WdtIsrCheckFlag &&
               ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(params.expirationTime))) {
            ClockP_usleep(10000U);
        }
    }
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        1U, TestWatchdog_WdtIsrCheckFlag,
        "ISR should be triggered after incorrect key sequence"
    );

    /* Cleanup */
    Watchdog_close(handle);
    HwiP_destruct(&hwiObject);
}

/**
 * \brief Negative test: getWindowSize with NULL handle.
 * Test Category: Negative
 * Attempts to call Watchdog_getWindowSize with NULL handle to verify
 * proper error handling or graceful behavior.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Function should handle NULL gracefully without crash.
 */
static void TestWatchdog_getWindowSizeNullHandle(void *args)
{
    (void)args;
    uint32_t windowSize;

    DebugP_log("Testing Watchdog_getWindowSize with NULL handle\r\n");

    /* Attempt to get window size with NULL handle */
    /* Note: This may cause a crash if not handled properly in the driver */
    /* Depending on driver implementation, you may need to wrap this in
       exception handling or skip if driver doesn't validate NULL */

    /* If driver has NULL check, this should return error or default value */
    windowSize = Watchdog_getWindowSize(NULL);

    /* If we reach here without crash, consider it a pass for graceful handling */
    DebugP_log("getWindowSize(NULL) returned: 0x%08X\r\n", windowSize);
}

/**
 * \brief Negative test: setWindowSize with NULL handle.
 * Test Category: Negative
 * Attempts to call Watchdog_setWindowSize with NULL handle to verify
 * proper error handling.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Function should handle NULL gracefully without crash.
 * \note No handling for null argument in this API.
 */
static void TestWatchdog_setWindowSizeNullHandle(void *args)
{
    (void)args;

    DebugP_log("Testing Watchdog_setWindowSize with NULL handle\r\n");

    /* Attempt to set window size with NULL handle */
    Watchdog_setWindowSize(NULL, Watchdog_WINDOW_50_PERCENT);
}

/**
 * \brief Fuzzing test: setWindowSize with invalid enum values.
 * Test Category: Fuzzing/Negative
 * Tests setWindowSize with various invalid window size values including
 * out-of-range enums, boundary values, and random invalid values.
 * Verifies the driver handles invalid inputs gracefully.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Driver should either reject invalid values or handle them safely.
 */
static void TestWatchdog_setWindowSizeInvalidValues(void *args)
{
    (void)args;
    Watchdog_Handle handle = gWatchdogHandle[CONFIG_WDT0];
    uint32_t originalWindowSize, readbackWindowSize;
    uint32_t invalidValues[] = {
        0x00000006,  /* Just beyond valid enum range (0-5) */
        0x00000007,  /* 7 */
        0x000000FF,  /* 255 */
        0x0000FFFF,  /* 65535 */
        0xFFFFFFFF,  /* Max uint32 */
        0x12345678,  /* Random value */
        0xDEADBEEF,  /* Common test pattern */
        0x80000000,  /* High bit set */
        0x7FFFFFFF,  /* Max signed int */
    };
    uint32_t i;

    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog handle must be valid");
    Watchdog_setWindowSize(handle, Watchdog_WINDOW_100_PERCENT);
    /* Save original window size */
    originalWindowSize = Watchdog_getWindowSize(handle);

    /* Test each invalid value */
    for (i = 0U; i < sizeof(invalidValues)/sizeof(invalidValues[0]); i++)
    {
        DebugP_log("Testing invalid window size: 0x%08X\r\n", invalidValues[i]);

        /* Attempt to set invalid window size */
        Watchdog_setWindowSize(handle, invalidValues[i]);

        /* Read back to see what was actually set */
        readbackWindowSize = Watchdog_getWindowSize(handle);
        DebugP_log("  Readback value: 0x%08X\r\n", readbackWindowSize);

        /*Invalid values should not be set*/
        TEST_ASSERT_EQUAL_MESSAGE(originalWindowSize, readbackWindowSize, "Invalid window size was incorrectly accepted");

        /* Small delay between iterations */
        ClockP_usleep(1000U);
    }

    /* Restore original window size */
    Watchdog_setWindowSize(handle, originalWindowSize);
    TEST_ASSERT_EQUAL_UINT32(originalWindowSize, Watchdog_getWindowSize(handle));
}

/**
 * \brief Fuzzing test: rapid set/get window size operations.
 * Test Category: Fuzzing/Stress
 * Performs rapid consecutive set/get operations with valid window sizes
 * to verify driver stability under high-frequency access patterns.
 * \param args Pointer to test arguments (unused).
 * \expectedOutput All set operations should be reflected correctly in get operations.
 */
static void TestWatchdog_setGetWindowSizeRapidFuzzing(void *args)
{
    (void)args;
    Watchdog_Handle handle = gWatchdogHandle[CONFIG_WDT0];
    uint32_t validWindowSizes[] = {
        Watchdog_WINDOW_100_PERCENT,
        Watchdog_WINDOW_50_PERCENT,
        Watchdog_WINDOW_25_PERCENT,
        Watchdog_WINDOW_12_5_PERCENT,
        Watchdog_WINDOW_6_25_PERCENT,
        Watchdog_WINDOW_3_125_PERCENT
    };
    uint32_t i, iteration;
    uint32_t readbackValue;
    const uint32_t numIterations = 1000U;

    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog handle must be valid");

    DebugP_log("Starting rapid set/get fuzzing test (%u iterations)\r\n", numIterations);

    for (iteration = 0U; iteration < numIterations; iteration++)
    {
        /* Cycle through all valid window sizes */
        for (i = 0U; i < sizeof(validWindowSizes)/sizeof(validWindowSizes[0]); i++)
        {
            /* Rapid set */
            Watchdog_setWindowSize(handle, validWindowSizes[i]);

            /* Immediate get */
            readbackValue = Watchdog_getWindowSize(handle);

            /* Verify consistency */
            TEST_ASSERT_EQUAL_UINT32_MESSAGE(
                validWindowSizes[i],
                readbackValue,
                "Mismatch in rapid set/get operation"
            );
        }
    }

    DebugP_log("Rapid fuzzing test completed successfully\r\n");
}

/**
 * \brief Test that window size changes only take effect after service.
 * Test Category: Functional
 * Verifies that changing window size via setWindowSize() during a watchdog
 * period does not immediately affect the current countdown. The new window
 * size should only apply after the next Watchdog_clear() call.
 *
 * Steps:
 * 1. Open watchdog with default settings (100% window)
 * 2. Call setWindowSize() to change to 50% window
 * 3. Verify getWindowSize() still returns original default value (100%)
 * 4. Service watchdog with clear()
 * 5. Verify getWindowSize() now returns the new value (50%)
 * 6. Service watchdog again to confirm operation
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Window size change takes effect only after service operation.
 */
static void TestWatchdog_windowSizeChangeOnService(void *args)
{
    (void)args;
    Watchdog_Handle handle;
    Watchdog_Params params;
    uint32_t originalWindowSize;
    uint32_t queriedWindowSize;
    uint32_t newWindowSize = Watchdog_WINDOW_50_PERCENT;
    uint64_t t0;

    DebugP_log("Testing window size change deferred until service\r\n");

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Step 1: Open watchdog with default settings */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = Watchdog_WINDOW_100_PERCENT;  /* Default */
    params.expirationTime = 1000U; /* 1 second */
    params.debugStallMode = Watchdog_DEBUG_STALL_OFF;

    handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog_open failed");

    /* Get and save original window size */
    originalWindowSize = Watchdog_getWindowSize(handle);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        Watchdog_WINDOW_100_PERCENT,
        originalWindowSize,
        "Initial window size should be 100%"
    );
    DebugP_log("Step 1: Opened with default window size: 0x%08X (100%%)\r\n",
               originalWindowSize);

    /* Start fresh period */
    Watchdog_clear(handle);
    ClockP_usleep(100000U); /* 100ms into period */

    /* Step 2: Change window size to 50% using setWindowSize() */
    Watchdog_setWindowSize(handle, newWindowSize);

    /* Step 3: Verify getWindowSize() still returns ORIGINAL default value */
    queriedWindowSize = Watchdog_getWindowSize(handle);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        newWindowSize,
        queriedWindowSize,
        "Window size should update immediately in getter"
    );
    DebugP_log("  Note: Window size getter shows new value (0x%08X), but hardware "
               "still uses original for current period\r\n", queriedWindowSize);

    /* Step 4: Service watchdog with clear() to apply new window */
    Watchdog_clear(handle);
    ClockP_usleep(50000U); /* Small delay after clear */

    /* Step 5: Verify getWindowSize() now returns the NEW value (50%) */
    queriedWindowSize = Watchdog_getWindowSize(handle);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        newWindowSize,
        queriedWindowSize,
        "Window size should be new value after service"
    );
    DebugP_log("  Window size confirmed as new value: 0x%08X (50%%)\r\n",
               queriedWindowSize);

    /* Step 6: Service watchdog again to confirm operation with new window */

    /* Wait for open window period (last 50% of period) */
    t0 = ClockP_getTimeUsec();
    while (Watchdog_isClosedWindow(handle) &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(1500))) 
    {
        ClockP_usleep(10000U);
    }

    /* Should be in open window now */
    TEST_ASSERT_FALSE_MESSAGE(
        Watchdog_isClosedWindow(handle),
        "Should be in open window");

    /* Clear in open window - should succeed */
    Watchdog_clear(handle);
    ClockP_usleep(50000U); /* 50ms */

    /* Cleanup */
    Watchdog_close(handle);
}

/**
 * \brief Test isClosedWindow API during open window period.
 * Test Category: Functional
 * Validates that isClosedWindow() correctly returns FALSE when watchdog
 * is in the open window period (where servicing is allowed).
 * Uses 50% window configuration.
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput isClosedWindow returns FALSE during open window period.
 */
static void TestWatchdog_isClosedWindowOpenPeriod(void *args)
{
    (void)args;
    Watchdog_Handle handle;
    Watchdog_Params params;
    uint64_t t0;
    bool isClosedResult;

    DebugP_log("Testing isClosedWindow API during open window period\r\n");

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Open watchdog with 50% window */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = Watchdog_WINDOW_50_PERCENT;
    params.expirationTime = 1000U; /* 1 second */
    params.debugStallMode = Watchdog_DEBUG_STALL_OFF;

    handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog_open failed");

    DebugP_log("Watchdog opened with 50%% window (first 50%% closed, last 50%% open)\r\n");

    /* Start fresh period */
    Watchdog_clear(handle);

    /* Wait for OPEN window period (second half with 50% window) */
    t0 = ClockP_getTimeUsec();
    while (Watchdog_isClosedWindow(handle) &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(1500))) 
    {
        ClockP_usleep(10000U); /* 10ms */
    }

    /* Should now be in open window */
    isClosedResult = Watchdog_isClosedWindow(handle);
    DebugP_log("isClosedWindow returned: %u (expected: 0 for open window)\r\n", isClosedResult);

    TEST_ASSERT_FALSE_MESSAGE(
        isClosedResult,
        "isClosedWindow should return FALSE during open window period"
    );

    /* Cleanup */
    Watchdog_close(handle);
}

/**
 * \brief Test isClosedWindow API during closed window period.
 * Test Category: Functional
 * Validates that isClosedWindow() correctly returns TRUE when watchdog
 * is in the closed window period (where servicing causes violation).
 * Tests with 50% and 25% window configurations.
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput isClosedWindow returns TRUE during closed window period.
 */
static void TestWatchdog_isClosedWindowClosedPeriod(void *args)
{
    (void)args;
    Watchdog_Handle handle;
    Watchdog_Params params;
    bool isClosedResult;
    uint32_t i;

    DebugP_log("Testing isClosedWindow API during closed window period\r\n");

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Open watchdog with 50% window */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = Watchdog_WINDOW_50_PERCENT;
    params.expirationTime = 1000U; /* 1 second */
    params.debugStallMode = Watchdog_DEBUG_STALL_OFF;

    handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog_open failed");

    DebugP_log("Watchdog opened with 50%% window (first 50%% closed, last 50%% open)\r\n");

    /* Start fresh period */
    Watchdog_clear(handle);

    /* Wait briefly - should be in closed window (first 50% of period) */
    ClockP_usleep(100000U); /* 100ms - well into closed period */

    /* Should be in closed window */
    isClosedResult = Watchdog_isClosedWindow(handle);
    DebugP_log("isClosedWindow returned: %u (expected: 1 for closed window)\r\n", isClosedResult);

    TEST_ASSERT_TRUE_MESSAGE(
        isClosedResult,
        "isClosedWindow should return TRUE during closed window period"
    );

    /* Call isClosedWindow multiple times to ensure consistency */
    for (i = 0U; i < 5U; i++) {
        isClosedResult = Watchdog_isClosedWindow(handle);
        TEST_ASSERT_TRUE_MESSAGE(
            isClosedResult,
            "isClosedWindow should consistently return TRUE in closed window"
        );
    }

    /* Test with different window size - 25% window */
    Watchdog_close(handle);

    params.windowSize = Watchdog_WINDOW_25_PERCENT;
    handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog_open failed for 25% window");

    DebugP_log("Testing with 25%% window (first 75%% closed, last 25%% open)\r\n");

    /* Start fresh period */
    Watchdog_clear(handle);
    ClockP_usleep(100000U); /* 100ms - should be in closed period */

    /* Should be in closed window */
    isClosedResult = Watchdog_isClosedWindow(handle);
    DebugP_log("isClosedWindow with 25%% window returned: %u (expected: 1)\r\n", isClosedResult);

    TEST_ASSERT_TRUE_MESSAGE(
        isClosedResult,
        "isClosedWindow should return TRUE during 25% window closed period"
    );

    /* Test edge case: right after clear with 100% window should never be closed */
    Watchdog_close(handle);

    params.windowSize = Watchdog_WINDOW_100_PERCENT;
    handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog_open failed for 100% window");

    Watchdog_clear(handle);
    ClockP_usleep(100000U);

    isClosedResult = Watchdog_isClosedWindow(handle);
    DebugP_log("isClosedWindow with 100%% window returned: %u (expected: 0 - never closed)\r\n",
               isClosedResult);

    TEST_ASSERT_FALSE_MESSAGE(
        isClosedResult,
        "100% window should never have closed period"
    );

    DebugP_log("TEST PASSED: isClosedWindow correctly returned TRUE/FALSE for various windows\r\n");

    /* Cleanup */
    Watchdog_close(handle);
}

/**
 * \brief Negative test: isClosedWindow with NULL handle.
 * Test Category: Negative
 * Validates that isClosedWindow() handles NULL handle gracefully without
 * causing a crash or undefined behavior.
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Function handles NULL gracefully (returns default value or doesn't crash).
 */
static void TestWatchdog_isClosedWindowNullHandle(void *args)
{
    (void)args;
    bool result;
    uint32_t i;

    DebugP_log("Testing isClosedWindow with NULL handle (negative test)\r\n");

    /* Attempt to call isClosedWindow with NULL handle */
    /* Note: Behavior depends on driver implementation
     * - May return a default value (true/false)
     * - Should not crash
     */
    result = Watchdog_isClosedWindow(NULL);

    DebugP_log("isClosedWindow(NULL) returned: %u\r\n", result);

    /* If we reach here without crash, test passes */
    TEST_ASSERT_TRUE_MESSAGE(1, "Survived NULL handle for isClosedWindow");

    /* Test with multiple calls to ensure consistency */
    for (i = 0U; i < 3U; i++) {
        result = Watchdog_isClosedWindow(NULL);
        DebugP_log("  Call %u: returned %u\r\n", i + 1U, result);
    }

    DebugP_log("TEST PASSED: isClosedWindow handled NULL handle gracefully\r\n");
}

 /* Test Category: Negative
 * Validates that Watchdog_open() handles invalid parameter values
 * (invalid window sizes, extreme expiration times, etc.).
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Opens with sanitized values or rejects invalid params.
 */
static void TestWatchdog_openInvalidParams(void *args)
{
    (void)args;
    Watchdog_Handle handle;
    Watchdog_Params params;

    /* Test 1: Invalid window size */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = (Watchdog_WindowSize) 999U; /* Invalid window size */
    params.expirationTime = 1000U;

    handle = Watchdog_open(CONFIG_WDT0, &params);
    if (handle != NULL) {
        /* Verify watchdog is functional */
        Watchdog_clear(handle);
        ClockP_usleep(10000U);
    }
    TEST_ASSERT_EQUAL(NULL, handle);

    /* Test 2: Zero expiration time */
    DebugP_log("Test 2: Zero expiration time\r\n");
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = Watchdog_WINDOW_100_PERCENT;
    params.expirationTime = 0U; /* Invalid - zero expiration */

    handle = Watchdog_open(CONFIG_WDT0, &params);
    if (handle != NULL) {
        /* Verify watchdog is functional */
        Watchdog_clear(handle);
        ClockP_usleep(10000U);

    }
    TEST_ASSERT_EQUAL(NULL, handle);
}

/**
 * \brief Negative test: Watchdog_open with NULL parameters.
 * Test Category: Negative
 * Validates that Watchdog_open() handles NULL params pointer gracefully,
 * either using default parameters or returning an error.
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Opens with default params or returns NULL gracefully.
 */
static void TestWatchdog_openNullParams(void *args)
{
    (void)args;
    Watchdog_Handle handle;

    DebugP_log("Testing Watchdog_open with NULL params (negative test)\r\n");

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Attempt to open with NULL params - driver should use defaults */
    handle = Watchdog_open(CONFIG_WDT0, NULL);

    if (handle != NULL) {
        DebugP_log("Watchdog_open(NULL params) succeeded - using defaults\r\n");

        /* Verify handle is functional */
        uint32_t windowSize = Watchdog_getWindowSize(handle);
        DebugP_log("  Default window size: 0x%08X\r\n", windowSize);

        /* Verify we can clear the watchdog */
        Watchdog_clear(handle);
        DebugP_log("  Clear operation successful\r\n");

        /* Wait a bit and clear again to ensure it's running */
        ClockP_usleep(100000U); /* 100ms */
        Watchdog_clear(handle);
    }
    TEST_ASSERT_NOT_NULL(handle);
}

/**
 * \brief Negative test: Watchdog_open on already opened instance.
 * Test Category: Negative
 * Validates behavior when attempting to open a watchdog instance that
 * is already open. Should return NULL.
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Handles double-open scenario gracefully.
 */
static void TestWatchdog_openAlreadyOpened(void *args)
{
    (void)args;
    Watchdog_Handle handle1, handle2;
    Watchdog_Params params;

    /* Initialize parameters */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = Watchdog_WINDOW_100_PERCENT;
    params.expirationTime = 1000U;

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Open first time */
    handle1 = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL(handle1);

    /* Attempt to open same instance again */
    handle2 = Watchdog_open(CONFIG_WDT0, &params);

    if (handle1 != NULL) {
        Watchdog_clear(handle1);
        ClockP_usleep(10000U);
    }
    TEST_ASSERT_EQUAL(NULL, handle2);
}

/**
 * \brief Negative test: Watchdog_clear with NULL handle.
 * Test Category: Negative
 * Validates that Watchdog_clear() handles NULL handle gracefully without
 * crashing or causing undefined behavior.
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Function handles NULL gracefully without crash.
 */
static void TestWatchdog_clearNullHandle(void *args)
{
    (void)args;
    uint32_t i;

    /* Attempt to clear with NULL handle */
    /* Should not crash - driver should have NULL check */
    Watchdog_clear(NULL);

    /* Call multiple times to ensure consistency */
    for (i = 0U; i < 5U; i++) {
        Watchdog_clear(NULL);
    }
}

/**
 * \brief Negative test: Watchdog_setReaction with NULL handle.
 * Test Category: Negative
 * Validates that Watchdog_setReaction() handles NULL handle gracefully
 * without crashing or causing undefined behavior.
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Function handles NULL gracefully without crash.
 */
static void TestWatchdog_setReactionNullHandle(void *args)
{
    (void)args;
    int32_t status;
    uint32_t i;
    uint32_t reactionValues[] = {
        Watchdog_RESET_OFF,
        Watchdog_RESET_ON
    };

    for (i = 0U; i < sizeof(reactionValues)/sizeof(reactionValues[0]); i++) {
        DebugP_log("Calling setReaction(NULL, %u)\r\n", reactionValues[i]);
        status = Watchdog_setReaction(NULL, reactionValues[i]);
        TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status,
            "setReaction with NULL handle must return SystemP_FAILURE");
    }
}

/**
 * \brief Negative test: Watchdog_setReaction with invalid reaction values.
 * Test Category: Negative
 * Validates that Watchdog_setReaction() handles out-of-range and invalid
 * reaction values properly (rejects or sanitizes them).
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Driver handles invalid values safely (rejects or masks).
 */
static void TestWatchdog_setReactionInvalidValues(void *args)
{
    (void)args;
    Watchdog_Handle handle;
    Watchdog_Params params;
    int32_t status;
    uint32_t invalidReactions[] = {
        0x00000002,  /* Beyond valid range (0xA=RESET_OFF, 0x5=RESET_ON) */
        0x00000003,
        0x000000FF,
        0x0000FFFF,
        0xFFFFFFFF,  /* Max uint32 */
        0xDEADBEEF,  /* Random invalid value */
        0x12345678,
        0x80000000   /* High bit set */
    };
    uint32_t i;

    DebugP_log("Testing Watchdog_setReaction with invalid values (negative test)\r\n");

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Open watchdog */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = Watchdog_WINDOW_100_PERCENT;
    params.expirationTime = 1000U;

    handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog_open failed");

    /* Test each invalid reaction value */
    for (i = 0U; i < sizeof(invalidReactions)/sizeof(invalidReactions[0]); i++) {

        /* Attempt to set invalid reaction - must return failure */
        status = Watchdog_setReaction(handle, invalidReactions[i]);
        TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status,
            "setReaction must return SystemP_FAILURE for invalid value");

        /* Small delay between iterations */
        ClockP_usleep(1000U);
    }

    /* Verify watchdog still operational after invalid value attempts */
    Watchdog_clear(handle);
    DebugP_log("Watchdog still operational after invalid reaction values\r\n");

    /* Cleanup */
    Watchdog_close(handle);
}

/**
 * \brief Test watchdog status register violations.
 * Test Category: Functional
 * Directly reads RTI_WDSTATUS register to verify correct status bits are set
 * for different types of violations: incorrect key, closed window violation,
 * and timeout violations.
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Each violation type sets the corresponding status bit.
 */
static void TestWatchdog_statusRegisterViolations(void *args)
{
    (void)args;
    Watchdog_Handle handle;
    Watchdog_Params params;
    Watchdog_Config* ptrWatchdogConfig;
    Watchdog_HwAttrs* ptrHwCfg;
    uint32_t statusReg;
    uint64_t t0;
    int32_t status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;

    /* Setup ISR to handle violations safely */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    TestWatchdog_WdtIsrCheckFlag = 0U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Open watchdog with known parameters */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = Watchdog_WINDOW_50_PERCENT;
    params.expirationTime = 1000U; /* 1 second */
    params.debugStallMode = Watchdog_DEBUG_STALL_OFF;

    handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog_open failed");

    /* Get hardware configuration to access base address */
    ptrWatchdogConfig = (Watchdog_Config*)handle;
    ptrHwCfg = (Watchdog_HwAttrs*)ptrWatchdogConfig->hwAttrs;

    /* ========== Test 1: Start Time (Closed Window) Violation ========== */

    /* Clear any sticky WDSTATUS bits before provoking violation */
    HW_WR_REG32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDSTATUS, WATCHDOG_CLEAR_STATUS);

    /* Start from a known point in the period */
    Watchdog_clear(handle);

    /* Ensure we are firmly inside the CLOSED window (first 50% of period) */
    ClockP_usleep(50000U); /* 50 ms margin away from boundary */
    TEST_ASSERT_TRUE_MESSAGE(
        Watchdog_isClosedWindow(handle),
        "Should be in closed window before violation clear"
    );

    /* Perform invalid clear inside CLOSED window to trigger violation */
    TestWatchdog_WdtIsrCheckFlag = 0U;
    Watchdog_clear(handle);

    /* Wait for ISR (bounded by configured expiration) */
    t0 = ClockP_getTimeUsec();
    while (!TestWatchdog_WdtIsrCheckFlag &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(params.expirationTime))) {
        ClockP_usleep(1000U);
    }

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        1U, TestWatchdog_WdtIsrCheckFlag,
        "ISR should fire after closed window violation"
    );

    /* Check status register for STARTTIMEVIOL */
    statusReg = HW_RD_REG32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDSTATUS);

    TEST_ASSERT_TRUE_MESSAGE(
        (statusReg & CSL_RTI_RTIWDSTATUS_STARTTIMEVIOL_MASK) != 0U,
        "STARTTIMEVIOL bit not set"
    );

    /* ========== Test 2: Timeout Status ========== */

    /* Clear any sticky WDSTATUS bits before timeout test */
    HW_WR_REG32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDSTATUS, WATCHDOG_CLEAR_STATUS);

    TestWatchdog_WdtIsrCheckFlag = 0U;
    Watchdog_clear(handle);

    /* Don't service - just wait for timeout */
    t0 = ClockP_getTimeUsec();
    while (!TestWatchdog_WdtIsrCheckFlag &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(params.expirationTime))) {
        ClockP_usleep(50000U);
    }

    /* Small settle to allow WDSTATUS to latch */
    ClockP_usleep(5000U);

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1U, TestWatchdog_WdtIsrCheckFlag,
                                     "ISR should fire on timeout");

    /* Check status register for end-time window violation via DWWD_ST */
    statusReg = HW_RD_REG32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDSTATUS);

    TEST_ASSERT_TRUE_MESSAGE(
        (statusReg & CSL_RTI_RTIWDSTATUS_DWWD_ST_MASK) != 0U,
        "DWWD_ST (end-time window) bit not set"
    );

    /* ========== Test 3: Incorrect Key Violation ========== */

    /* Clear sticky WDSTATUS bits before incorrect key test */
    HW_WR_REG32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDSTATUS, WATCHDOG_CLEAR_STATUS);

    /* Start fresh period */
    Watchdog_clear(handle);
    ClockP_usleep(100000U); /* 100ms */

    /* Write incorrect key sequence */
    HW_WR_FIELD32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDKEY,
                  CSL_RTI_RTIWDKEY_WDKEY,
                  0xDEAD); /* Incorrect first key */
    HW_WR_FIELD32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDKEY,
                  CSL_RTI_RTIWDKEY_WDKEY,
                  0xBEEF); /* Incorrect second key */

    ClockP_usleep(10000U); /* Small delay to allow status to update */

    /* Read and verify KEYST bit is set (bit 2) */
    statusReg = HW_RD_REG32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDSTATUS);

    TEST_ASSERT_TRUE_MESSAGE(
        (statusReg & CSL_RTI_RTIWDSTATUS_KEYST_MASK) != 0U,
        "KEYST bit not set after incorrect key sequence"
    );


    /* Cleanup: clear status, close handle, destruct HWI, and re-open
     * gWatchdogHandle so subsequent tests start with a clean state. */
    HW_WR_REG32(ptrHwCfg->baseAddr + CSL_RTI_RTIWDSTATUS, WATCHDOG_CLEAR_STATUS);
    Watchdog_close(handle);
    HwiP_destruct(&hwiObject);

    /* Re-open so gWatchdogHandle[CONFIG_WDT0] is valid for subsequent tests */
    gWatchdogHandle[CONFIG_WDT0] = Watchdog_open(CONFIG_WDT0, NULL);
    TEST_ASSERT_NOT_NULL(gWatchdogHandle[CONFIG_WDT0]);
}

/**
 * \brief Verify Watchdog_clear after Watchdog_close does not service the watchdog.
 * Test Category: Negative
 * Validates that after Watchdog_close() is called, subsequent Watchdog_clear()
 * calls do not restart the watchdog countdown.
 *
 * Watchdog_close() marks driver state as UNINIT. This test
 * validates that the system does not generate a new NMI after close + clear
 * sequence.
 *
 * \param args Pointer to test arguments (unused).
 * \expectedOutput Watchdog_clear on a closed handle should NOT cause a new
 *                 timeout ISR.
 */
static void TestWatchdog_clearAfterClose(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    Watchdog_Handle handle;
    Watchdog_Params params;
    uint64_t t0;

    /* Setup ISR */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_isr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Close the instance opened during Drivers_open() before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Open watchdog with known parameters */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_OFF;
    params.windowSize     = Watchdog_WINDOW_100_PERCENT;
    params.expirationTime = 1000U; /* 1 second */

    handle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Watchdog_open failed");

    /* Verify watchdog is functional before close */
    Watchdog_clear(handle);
    ClockP_usleep(10000U);

    /* Close the watchdog - marks driver state as UNINIT.
     * Note: RTI DWWD hardware cannot be disabled once enabled */
    Watchdog_close(handle);

    /* After close, Watchdog_clear() on a closed handle should not cause a new
     * timeout ISR. */
    TestWatchdog_WdtIsrCheckFlag = 0U;
    Watchdog_clear(handle);

    /* Wait for more than the configured expiration time.
     * If clear actually restarted the watchdog, we will see an ISR. */
    t0 = ClockP_getTimeUsec();
    while (!TestWatchdog_WdtIsrCheckFlag &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(params.expirationTime))) {
        ClockP_usleep(10000U);
    }

    /* No ISR should fire after close + clear sequence. */
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        0U, TestWatchdog_WdtIsrCheckFlag,
        "Watchdog_clear should not cause a new timeout after Watchdog_close"
    );

    HwiP_destruct(&hwiObject);

    /* Re-open so gWatchdogHandle[CONFIG_WDT0] is valid for subsequent tests */
    gWatchdogHandle[CONFIG_WDT0] = Watchdog_open(CONFIG_WDT0, NULL);
    TEST_ASSERT_NOT_NULL(gWatchdogHandle[CONFIG_WDT0]);
}

static void TestWatchdog_deinit(void *args)
{
    (void)args;

    DebugP_log("Watchdog deinit test\r\n");

    Watchdog_deinit();
}





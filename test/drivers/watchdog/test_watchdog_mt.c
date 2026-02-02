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
#include <unity.h>
#include "ti_drivers_config.h"
#include <drivers/soc.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                                  Macros                                    */
/* ========================================================================== */

#define TEST_WDT_WAIT_US(exp_ms)             ((uint64_t)(exp_ms) * 1000ULL)

#if defined ENABLE_MT_TESTS

/* ========================================================================== */
/*                   External Symbol Declarations                             */
/* ========================================================================== */

/* Globals defined in test_watchdog.c */
extern volatile uint32_t TestWatchdog_IsrIncFlag;
extern Watchdog_Handle TestWatchdog_Handle;

/* Functions defined in test_watchdog.c */
void TestWatchdog_callbackIsr(void *arg);
void TestWatchdog_validateWindow(Watchdog_WindowSize windowSize,
                                 const char *windowName);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static SemaphoreP_Object TestWatchdog_MtDoneSem;
#if defined CORE_C75
static uint8_t TestWatchdog_Task1Stack[4096 * 8] __attribute__((aligned(32)));
static uint8_t TestWatchdog_Task2Stack[4096 * 8] __attribute__((aligned(32)));
#else
static uint8_t TestWatchdog_Task1Stack[4096] __attribute__((aligned(32)));
static uint8_t TestWatchdog_Task2Stack[4096] __attribute__((aligned(32)));
#endif

#if defined CORE_A53
/* Per-task ISR flags */
static volatile uint32_t TestWatchdog_MtLargeIsrFlag = 0U;
static volatile uint32_t TestWatchdog_MtMinIsrFlag   = 0U;
#endif

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

static void TestWatchdog_MtTriggerTask(void *arg);
static void TestWatchdog_MtCompletionTask(void *arg);
#if defined CORE_A53
static void TestWatchdog_MtLargeIsr(void *arg);
static void TestWatchdog_MtMinIsr(void *arg);
static void TestWatchdog_TaskLargeExpiration(void *arg);
static void TestWatchdog_TaskMinExpiration(void *arg);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * @brief Trigger task used by multithread tests.
 *
 * Starts the watchdog from a known state by clearing the configured
 * `CONFIG_WDT0` instance. Posts the multithread-done semaphore to
 * signal completion and exits the task.
 *
 * @param arg Unused.
 */
static void TestWatchdog_MtTriggerTask(void *arg)
{
    (void)arg;
    Watchdog_Handle handle = gWatchdogHandle[CONFIG_WDT0];
    if (handle != NULL)
    {
        Watchdog_clear(handle);
    }
    SemaphoreP_post(&TestWatchdog_MtDoneSem);
    TaskP_exit();
}

/**
 * @brief Completion task used by multithread interrupt test.
 *
 * Polls the global ISR invocation counter until the expected number of
 * NMIs have been observed (3) or a bounded timeout elapses. On exit
 * the task posts the multithread-done semaphore.
 *
 * @param arg Unused.
 */
static void TestWatchdog_MtCompletionTask(void *arg)
{
    (void)arg;
    uint64_t t0 = ClockP_getTimeUsec();
    while ((TestWatchdog_IsrIncFlag < 3U) &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(7000)))
    {
        /* tiny yield to other tasks */
        ClockP_usleep(1000U);
    }
    SemaphoreP_post(&TestWatchdog_MtDoneSem);
    TaskP_exit();
}

/**
 * @brief Multithreaded interrupt-mode test.
 *
 * Installs an ISR callback that may clear the watchdog and constructs two
 * tasks: a trigger task that starts a known watchdog period and a
 * completion task that waits for the expected NMIs. Synchronizes via a
 * counting semaphore and verifies the ISR count.
 *
 * @param args Unused.
 */
void TestWatchdog_interruptModeMultithread(void *args)
{
    (void)args;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    TaskP_Params tParams;
    static TaskP_Object taskTrigObj, taskComplObj;

    /* Bind handle for ISR clears */
    TestWatchdog_Handle = gWatchdogHandle[CONFIG_WDT0];

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_callbackIsr;
    hwiPrms.isPulse  = 1U;

    TestWatchdog_IsrIncFlag = 0U;
    /* Done semaphore to sync two tasks */
    status = SemaphoreP_constructCounting(&TestWatchdog_MtDoneSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Construct trigger task */
    TaskP_Params_init(&tParams);
    tParams.name      = (char*)"WdtMtTrigger";
    tParams.stackSize = sizeof(TestWatchdog_Task1Stack);
    tParams.stack     = TestWatchdog_Task1Stack;
    tParams.priority  = 2U;
    tParams.args      = NULL;
    tParams.taskMain  = TestWatchdog_MtTriggerTask;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskTrigObj, &tParams));

    /* Construct completion task */
    TaskP_Params_init(&tParams);
    tParams.name      = (char*)"WdtMtCompletion";
    tParams.stackSize = sizeof(TestWatchdog_Task2Stack);
    tParams.stack     = TestWatchdog_Task2Stack;
    tParams.priority  = 2U;
    tParams.args      = NULL;
    tParams.taskMain  = TestWatchdog_MtCompletionTask;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskComplObj, &tParams));

    /* Wait for both tasks to complete */
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestWatchdog_MtDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestWatchdog_MtDoneSem, SystemP_WAIT_FOREVER));

    /* Ensure we observed interrupt count update as well */
    DebugP_log("TestWatchdog_IsrIncFlag=%u\n", TestWatchdog_IsrIncFlag);
    TEST_ASSERT_EQUAL_UINT32(3U, TestWatchdog_IsrIncFlag);

    /* Cleanup */
    TaskP_destruct(&taskTrigObj);
    TaskP_destruct(&taskComplObj);
    HwiP_destruct(&hwiObject);
    SemaphoreP_destruct(&TestWatchdog_MtDoneSem);

    /* reset so other tests are not affected */
    TestWatchdog_IsrIncFlag = 0U;
    TestWatchdog_Handle = NULL;
}

#if defined CORE_A53
/**
 * @brief ISR callback for the large-expiration multithread task.
 *
 * Sets the per-task flag `TestWatchdog_MtLargeIsrFlag` when WDT1 fires.
 *
 * @param arg Unused.
 */
static void TestWatchdog_MtLargeIsr(void *arg)
{
    (void)arg;
    TestWatchdog_MtLargeIsrFlag = 1U;
}

/**
 * @brief ISR callback for the min-expiration multithread task.
 *
 * Sets the per-task flag `TestWatchdog_MtMinIsrFlag` when WDT2 fires.
 *
 * @param arg Unused.
 */
static void TestWatchdog_MtMinIsr(void *arg)
{
    (void)arg;
    TestWatchdog_MtMinIsrFlag = 1U;
}

/**
 * @brief Task that validates large expiration in multithread context.
 *
 * @param arg Unused.
 */
static void TestWatchdog_TaskLargeExpiration(void *arg)
{
    (void)arg;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    uint64_t timeStart;

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT1_INTR;
    hwiPrms.eventId  = CONFIG_WDT1_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_MtLargeIsr;
    hwiPrms.isPulse  = 1U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestWatchdog_MtLargeIsrFlag = 0U;
    timeStart = ClockP_getTimeUsec();
    Watchdog_clear(gWatchdogHandle[CONFIG_WDT1]);
    while ((!TestWatchdog_MtLargeIsrFlag) &&
           ((ClockP_getTimeUsec() - timeStart) < TEST_WDT_WAIT_US(70000)))
    {
        /* Yield to allow peer task to run */
        ClockP_usleep(1000U);
    }
    TEST_ASSERT_EQUAL_UINT32(1U, TestWatchdog_MtLargeIsrFlag);

    HwiP_destruct(&hwiObject);
    SemaphoreP_post(&TestWatchdog_MtDoneSem);
    TaskP_exit();
}

/**
 * @brief Task that validates minimal expiration in multithread context.
 *
 * @param arg Unused.
 */
static void TestWatchdog_TaskMinExpiration(void *arg)
{
    (void)arg;
    int32_t     status;
    HwiP_Params hwiPrms;
    static HwiP_Object hwiObject;
    uint64_t timeStart;

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT2_INTR;
    hwiPrms.eventId  = CONFIG_WDT2_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_MtMinIsr;
    hwiPrms.isPulse  = 1U;

    TestWatchdog_MtMinIsrFlag = 0U;

    status = HwiP_construct(&hwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    Watchdog_setWindowSize(gWatchdogHandle[CONFIG_WDT2], Watchdog_WINDOW_100_PERCENT);
    TEST_ASSERT_EQUAL_UINT32(Watchdog_WINDOW_100_PERCENT,
                             Watchdog_getWindowSize(gWatchdogHandle[CONFIG_WDT2]));

    TestWatchdog_MtMinIsrFlag = 0U;
    timeStart = ClockP_getTimeUsec();
    Watchdog_clear(gWatchdogHandle[CONFIG_WDT2]);
    while ((!TestWatchdog_MtMinIsrFlag) &&
           ((ClockP_getTimeUsec() - timeStart) < TEST_WDT_WAIT_US(510)))
    {
        /* Yield to allow peer task to run */
        ClockP_usleep(1000U);
    }
    TEST_ASSERT_EQUAL_UINT32(1U, TestWatchdog_MtMinIsrFlag);

    HwiP_destruct(&hwiObject);
    SemaphoreP_post(&TestWatchdog_MtDoneSem);
    TaskP_exit();
}

/**
 * @brief Multithreaded large/min expiration test.
 *
 * Spawns two tasks: one executing the long-expiration workload and the
 * other executing the minimal-expiration workload. Uses a counting
 * semaphore to wait for both tasks to finish and then performs cleanup.
 *
 * @param args Unused.
 */
void TestWatchdog_largeAndMinExpirationMultithread(void *args)
{
    (void)args;
    int32_t status;
    TaskP_Params tParams;
    static TaskP_Object taskLargeExpObj, taskMinExpObj;

    /* Construct counting semaphore to wait for both tasks */
    status = SemaphoreP_constructCounting(&TestWatchdog_MtDoneSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Task 1: largeExpiration (uses WDT1) */
    TaskP_Params_init(&tParams);
    tParams.name      = (char*)"WdtTaskLargeExpiration";
    tParams.stackSize = sizeof(TestWatchdog_Task1Stack);
    tParams.stack     = TestWatchdog_Task1Stack;
    tParams.priority  = 2U;
    tParams.args      = NULL;
    tParams.taskMain  = TestWatchdog_TaskLargeExpiration;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskLargeExpObj, &tParams));

    /* Task 2: minExpiration (uses WDT2) */
    TaskP_Params_init(&tParams);
    tParams.name      = (char*)"WdtTaskMinExpiration";
    tParams.stackSize = sizeof(TestWatchdog_Task2Stack);
    tParams.stack     = TestWatchdog_Task2Stack;
    tParams.priority  = 2U;
    tParams.args      = NULL;
    tParams.taskMain  = TestWatchdog_TaskMinExpiration;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskMinExpObj, &tParams));

    /* Wait for both tasks to finish */
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestWatchdog_MtDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestWatchdog_MtDoneSem, SystemP_WAIT_FOREVER));

    /* Cleanup */
    TaskP_destruct(&taskLargeExpObj);
    TaskP_destruct(&taskMinExpObj);
    SemaphoreP_destruct(&TestWatchdog_MtDoneSem);
}
#endif /* defined CORE_A53 */

#endif /* ENABLE_MT_TESTS */

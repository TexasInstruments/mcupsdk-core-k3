/*
 * Copyright (C) 2026 Texas Instruments Incorporated
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
 * @file test_watchdog_smp.c
 * @brief The following test aims at creating tasks for each A53 core.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "test_config.h"
#include "unity.h"
#include <drivers/watchdog.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                           Macros & Defines                                 */
/* ========================================================================== */

/* Wait timeout helper: expiration ms to usec + margin */
#define TEST_WDT_WAIT_US(exp_ms)             ((uint64_t)(exp_ms) * 1000ULL + 200000ULL)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile uint32_t TestWatchdog_IsrIncFlag = 0;
Watchdog_Handle TestWatchdog_Handle = NULL;
static volatile uint32_t TestWatchdog_WdtIsrCheckFlag = 0;
static SemaphoreP_Object TestWatchdog_MtDoneSem;
static uint8_t TestWatchdog_Task1Stack[4096] __attribute__((aligned(32)));
static uint8_t TestWatchdog_Task2Stack[4096] __attribute__((aligned(32)));

/* ========================================================================== */
/*                              Structures                                    */
/* ========================================================================== */

/* ========================================================================== */
/*                     Internal Function Declarations                         */
/* ========================================================================== */

static void TestWatchdog_isrCallback(void *arg);
static void TestWatchdog_triggerTask(void *arg);
static void TestWatchdog_completionTask(void *arg);

/* ========================================================================== */
/*                       Static Test Function Prototypes                      */
/* ========================================================================== */

static void TestWatchdog_interruptModeThreads(void *args);

/* ========================================================================== */
/*                            Main Test Function                              */
/* ========================================================================== */
/**
 *  \brief   Main entry point for Watchdog threaded tests.
 *
 *  Runs selected thread-based test cases using the Unity framework.
 *
 *  \param args  Unused argument.
 */
void test_watchdog_smp_main(void *args)
{
    UNITY_BEGIN();
    RUN_TEST(TestWatchdog_interruptModeThreads, 10120, NULL);
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

/* brief Watchdog interrupt callback for interrupt-mode threads test.
 * Increments the global counter `TestWatchdog_IsrIncFlag`.
 * For the first three invocations the ISR attempts to clear the watchdog.
 */
static void TestWatchdog_isrCallback(void *arg)
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
 * @brief Trigger task used by threaded tests.
 *
 * Starts the watchdog from a known state by clearing the configured
 * `CONFIG_WDT0` instance. Posts the threads-done semaphore to
 * signal completion and exits the task.
 *
 * @param arg Unused.
 */
static void TestWatchdog_triggerTask(void *arg)
{
    (void)arg;
    Watchdog_Handle handle = gWatchdogHandle[CONFIG_WDT0];
    if (handle != NULL)
    {
        Watchdog_clear(handle);
    }
    ClockP_usleep(5000U);
    SemaphoreP_post(&TestWatchdog_MtDoneSem);
    TaskP_exit();
}

/**
 * @brief Completion task used by interrupt-mode threads test.
 *
 * Polls the global ISR invocation counter until the expected number of
 * NMIs have been observed (3) or a bounded timeout elapses. On exit
 * the task posts the threads-done semaphore.
 *
 * @param arg Unused.
 */
static void TestWatchdog_completionTask(void *arg)
{
    (void)arg;
    uint64_t t0 = ClockP_getTimeUsec();
    while ((TestWatchdog_IsrIncFlag < 3U) &&
           ((ClockP_getTimeUsec() - t0) < TEST_WDT_WAIT_US(7000)))
    {
        /* tiny yield to other tasks */
        ClockP_usleep(1000U);
    }
    ClockP_usleep(5000U);
    SemaphoreP_post(&TestWatchdog_MtDoneSem);
    TaskP_exit();
}

/**
 * @brief Interrupt-mode threads test.
 *
 * Installs an ISR callback that may clear the watchdog and constructs two
 * tasks: a trigger task that starts a known watchdog period and a
 * completion task that waits for the expected NMIs. Synchronizes via a
 * counting semaphore and verifies the ISR count.
 *
 * @param args Unused.
 */
static void TestWatchdog_interruptModeThreads(void *args)
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
    hwiPrms.callback = &TestWatchdog_isrCallback;
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
    tParams.taskMain  = TestWatchdog_triggerTask;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskTrigObj, &tParams));

    /* Construct completion task */
    TaskP_Params_init(&tParams);
    tParams.name      = (char*)"WdtMtCompletion";
    tParams.stackSize = sizeof(TestWatchdog_Task2Stack);
    tParams.stack     = TestWatchdog_Task2Stack;
    tParams.priority  = 2U;
    tParams.args      = NULL;
    tParams.taskMain  = TestWatchdog_completionTask;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskComplObj, &tParams));

    /* Wait for both tasks to complete */
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestWatchdog_MtDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestWatchdog_MtDoneSem, SystemP_WAIT_FOREVER));

    /* Ensure we observed interrupt count update as well */
    DebugP_log("TestWatchdog_IsrIncFlag=%u\n", TestWatchdog_IsrIncFlag);
    TEST_ASSERT_EQUAL_UINT32(3U, TestWatchdog_IsrIncFlag);
    ClockP_usleep(5000U);
    /* Cleanup */
    TaskP_destruct(&taskTrigObj);
    TaskP_destruct(&taskComplObj);
    HwiP_destruct(&hwiObject);
    SemaphoreP_destruct(&TestWatchdog_MtDoneSem);

    /* reset so other tests are not affected */
    TestWatchdog_IsrIncFlag = 0U;
    TestWatchdog_Handle = NULL;
}



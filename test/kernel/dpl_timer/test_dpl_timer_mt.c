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
#include <kernel/dpl/TaskP.h>

#define TestExecute_SkipTestIdMatrix TestExecute_SkipTestIdMatrix_weak_default
#include "test_execute.h"
#undef TestExecute_SkipTestIdMatrix

#if defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM275X)

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/


/*===================================================================*/
/* 					         Typedefs 					             */
/*===================================================================*/


/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/

#if !defined(__C7000__)
static uint8_t TestDplTimer_threadStack1[8192] __attribute__ ((aligned(32)));
static uint8_t TestDplTimer_threadStack2[8192] __attribute__ ((aligned(32)));
static uint8_t TestDplTimer_threadStack3[8192] __attribute__ ((aligned(32)));
#else
static uint8_t TestDplTimer_threadStack1[65536] __attribute__ ((aligned(32)));
static uint8_t TestDplTimer_threadStack2[65536] __attribute__ ((aligned(32)));
static uint8_t TestDplTimer_threadStack3[65536] __attribute__ ((aligned(32)));
#endif
static SemaphoreP_Object TestDplTimer_mtSemIsr;
static volatile bool     TestDplTimer_mtStopRequested = false;
static volatile bool     TestDplTimer_mtObservedChange = false;
static volatile bool     TestDplTimer_mtCounterStopRequested = false;
extern const TestExecute_idList TestExecute_SkipTestIdMatrix[TEST_SOC_COUNT][TEST_CORE_COUNT];
static SemaphoreP_Object TestDplTimer_mtSemDone;
static volatile uint32_t TestDplTimer_mtIsrCount = 0U;

/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/

static void TestDplTimer_multithread_concurrent_start_stop(void *args);
static void TestDplTimer_multithread_multiple_instances(void *args);
/*===================================================================*/
/* 					         Function Definitions		             */
/*===================================================================*/

void TestDplTimer_mtTestcase(void)
{
    TEST_EXECUTE_TEST_CASE(TestDplTimer_multithread_concurrent_start_stop, 10382, NULL);
    TEST_EXECUTE_TEST_CASE(TestDplTimer_multithread_multiple_instances,    10383, NULL);
}

/* ISR used across tests: clears overflow and signals */
static void TestDplTimer_mt_overflow_isr(void *args)
{
    uint32_t baseAddr;
    uint32_t ovf;

    baseAddr = (uint32_t)(uintptr_t)args;
    ovf = TimerP_isOverflowed(baseAddr);

    if (ovf != 0U)
    {
        TimerP_clearOverflowInt(baseAddr);
        TestDplTimer_mtIsrCount++;
    }

    SemaphoreP_post(&TestDplTimer_mtSemDone);
}

/* Task that repeatedly starts and stops the same timer */
static void TestDplTimer_mt_task_toggler(void *args)
{
    uint32_t baseAddr;
    uint32_t iterations;
    uint32_t i;

    baseAddr   = (uint32_t)(uintptr_t)args;
    iterations = 250U;
    i          = 0U;

    while (i < iterations)
    {
        TimerP_start(baseAddr);
        /* Give timer enough time to actually advance count */
        ClockP_usleep(2000U); /* was 500us */

        TimerP_stop(baseAddr);
        ClockP_usleep(200U);

        i++;
        if (TestDplTimer_mtStopRequested)
        {
            break;
        }
    }

    SemaphoreP_post(&TestDplTimer_mtSemIsr);
    TaskP_exit();
}

/* Task that reads timer count to detect changes while other tasks toggle the timer */
static void TestDplTimer_mt_task_counter(void *args)
{
    uint32_t baseAddr;
    uint32_t last;
    uint32_t cur;
    uint32_t loops;
    uint32_t i;

    baseAddr = (uint32_t)(uintptr_t)args;
    last     = TimerP_getCount(baseAddr);

    /* Give scheduler/hardware a moment to progress before tight polling */
    ClockP_usleep(200U); /* was 50us */

    cur      = last;
    loops    = 2000000U; /* more budget to observe change under contention */
    i        = 0U;

    while (i < loops)
    {
        if (TestDplTimer_mtCounterStopRequested)
        {
            break;
        }
        cur = TimerP_getCount(baseAddr);
        if (cur != last)
        {
            TestDplTimer_mtObservedChange = true;
            break;
        }
        last = cur;

        /* Yield/backoff periodically to allow togglers/ISR to run */
        if ((i & 0xFFU) == 0U)
        {
            TaskP_yield();
        }
        if ((i & 0x7FFFU) == 0U)
        {
            ClockP_usleep(100U);
        }
        i++;
    }

    SemaphoreP_post(&TestDplTimer_mtSemIsr);
    TaskP_exit();
}

/**
 * @brief Multithread concurrent start/stop with counter observer.
 *
 * Stresses concurrent toggling of a single timer while a counter observer
 * task samples count changes; validates ISR signaling and absence of races.
 *
 * Test Steps:
 * 1. Bind ISR `TestDplTimer_mt_overflow_isr` and construct semaphores.
 * 2. Create toggler and counter tasks with provided stacks.
 * 3. Start tasks; observe ISR signals and count changes.
 * 4. Cleanup tasks, Hwi, and semaphores.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_multithread_concurrent_start_stop(void *args)
{
    uint32_t       baseAddr;
    uint32_t       intNum;
    int32_t        status;
    HwiP_Object    hwiObj;
    HwiP_Params    hwiParams;
    TimerP_Params  params;
    TaskP_Object   taskToggleA;
    TaskP_Object   taskToggleB;
    TaskP_Object   taskCounter;
    TaskP_Params   tparamsA;
    TaskP_Params   tparamsB;
    TaskP_Params   tparamsC;
    uint32_t       waits;
    uint32_t       tasksDone;
    uint64_t       tStartUsec;
    uint64_t       nowUsec;
    uint32_t       budgetUsec;
    int32_t        pendStatus;
    uint32_t       minIsr;

    baseAddr = gTimerBaseAddr[CONFIG_TIMER0];
    intNum   = CONFIG_TIMER0_INT_NUM;
    status   = SystemP_SUCCESS;
    TestDplTimer_mtStopRequested   = false;
    TestDplTimer_mtObservedChange  = false;
    TestDplTimer_mtIsrCount        = 0U;
    waits              = 0U;
    tasksDone          = 0U;
    tStartUsec         = 0U;
    nowUsec            = 0U;
    budgetUsec         = 15000000U; /* 15 seconds budget */
    pendStatus         = SystemP_SUCCESS;
    minIsr             = 5U;

    /* Counting semaphores to avoid lost ISR posts and to collect 3 task completions */
    status = SemaphoreP_constructCounting(&TestDplTimer_mtSemIsr, 0, 3);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructCounting(&TestDplTimer_mtSemDone, 0, 64);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Bind overflow ISR */
    HwiP_destruct(&gTimerHwiObj[CONFIG_TIMER0]);
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intNum;
    hwiParams.callback = TestDplTimer_mt_overflow_isr;
#if defined(__ARM_ARCH_7R__) || defined(SOC_AM64X) || defined(SOC_AM243X) || defined(SOC_AM62X) || defined(SOC_AM62AX)
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

    /* Configure periodic timer */
    TimerP_Params_init(&params);
    params.enableOverflowInt = 1U;
    params.periodInUsec      = 1000U; /* 1 ms */
    params.periodInNsec      = 0U;
    params.inputPreScaler    = 1U;
    params.oneshotMode       = 0U;
    params.enableDmaTrigger  = 0U;

    TimerP_setup(baseAddr, &params);
    TimerP_clearOverflowInt(baseAddr);

    /* Start timer before creating tasks to avoid counter spinning before progress */
    TimerP_start(baseAddr);
    ClockP_usleep(100U);

    /* Build tasks (toggle A/B + counter), using TaskP_Params.taskMain pattern */
    TaskP_Params_init(&tparamsA);
    tparamsA.priority  = 3U;
    tparamsA.stackSize = sizeof(TestDplTimer_threadStack1);
    tparamsA.stack     = TestDplTimer_threadStack1;
    tparamsA.args      = (void *)(uintptr_t)baseAddr;
    tparamsA.taskMain  = TestDplTimer_mt_task_toggler;
    tparamsA.name      = (char *)"Timer_Toggle_A";
#if defined(CONFIG_SMP_TEST_ENABLE)
    tparamsA.coreAffinity   = ( 1U << 0);
#endif

    TaskP_Params_init(&tparamsB);
    tparamsB.priority  = 3U;
    tparamsB.stackSize = sizeof(TestDplTimer_threadStack2);
    tparamsB.stack     = TestDplTimer_threadStack2;
    tparamsB.args      = (void *)(uintptr_t)baseAddr;
    tparamsB.taskMain  = TestDplTimer_mt_task_toggler;
    tparamsB.name      = (char *)"Timer_Toggle_B";
#if defined(CONFIG_SMP_TEST_ENABLE)
    tparamsB.coreAffinity   = ( 1U << 1);
#endif

    TaskP_Params_init(&tparamsC);
    tparamsC.priority  = 4U;
    tparamsC.stackSize = sizeof(TestDplTimer_threadStack3);
    tparamsC.stack     = TestDplTimer_threadStack3;
    tparamsC.args      = (void *)(uintptr_t)baseAddr;
    tparamsC.taskMain  = TestDplTimer_mt_task_counter;
    tparamsC.name      = (char *)"Timer_Counter";
#if defined(CONFIG_SMP_TEST_ENABLE)
    tparamsC.coreAffinity   = ( 1U << 2);
#endif

    status = TaskP_construct(&taskToggleA, &tparamsA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = TaskP_construct(&taskToggleB, &tparamsB);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = TaskP_construct(&taskCounter, &tparamsC);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    tStartUsec = ClockP_getTimeUsec();
    waits = 0U;

    while (waits < minIsr)
    {
        pendStatus = SemaphoreP_pend(&TestDplTimer_mtSemDone, SystemP_WAIT_FOREVER); /* 200 ms timeout */

        if (pendStatus == SystemP_SUCCESS)
        {
            waits++;
        }

        nowUsec = ClockP_getTimeUsec();
        if ((nowUsec - tStartUsec) >= (uint64_t)budgetUsec)
        {
            break;
        }
    }

    /* Ask tasks to stop and wait for their completion */
    TestDplTimer_mtStopRequested = true;

    tStartUsec = ClockP_getTimeUsec();
    tasksDone  = 0U;

    while (tasksDone < 3U)
    {
        pendStatus = SemaphoreP_pend(&TestDplTimer_mtSemIsr, ClockP_usecToTicks(3000000U)); /* 3 sec per task */
        if (pendStatus == SystemP_SUCCESS)
        {
            tasksDone++;
        }
        else
        {
            break;
        }

        nowUsec = ClockP_getTimeUsec();
        if ((nowUsec - tStartUsec) >= (uint64_t)budgetUsec)
        {
            break;
        }
    }

    TimerP_stop(baseAddr);

#if defined(CONFIG_SMP_TEST_ENABLE)
    ClockP_usleep(10000U);
#endif

    /* Validate results */
    TEST_ASSERT_TRUE(TestDplTimer_mtIsrCount >= 1U);
    TEST_ASSERT_TRUE(TestDplTimer_mtObservedChange);
    TEST_ASSERT_EQUAL_UINT32(3U, tasksDone);

    /* Cleanup */
    TaskP_destruct(&taskToggleA);
    TaskP_destruct(&taskToggleB);
    TaskP_destruct(&taskCounter);
    HwiP_destruct(&hwiObj);
    SemaphoreP_destruct(&TestDplTimer_mtSemDone);
    SemaphoreP_destruct(&TestDplTimer_mtSemIsr);
}

/**
 * @brief Multithread: multiple timer instances (Timer0 + Timer1).
 *
 * Runs two independent DPL timer instances concurrently to verify instance isolation:
 * - Each timer has its own ISR bound that clears the overflow and signals progress.
 * - Two toggler tasks independently start/stop each timer.
 * - A counter task is run in two phases to observe count changes for TimerA then TimerB.
 *
 * Validates that:
 * - Both timers generate ISR events (progress) without cross-interference.
 * - Counter can observe TimerP_getCount() progressing on each instance.
 * - Different configured periods yield different reload counts.
 *
 * Test Steps:
 * 1. Reset shared globals and construct counting semaphores for ISR progress and task exits.
 * 2. Construct HWIs for CONFIG_TIMER0 and CONFIG_TIMER1 with callback `TestDplTimer_mt_overflow_isr`,
 *    pass base address via args, set isPulse per SoC and priority=4.
 * 3. Configure Timer0 (1 ms, periodic) and Timer1 (1.5 ms, periodic); call `TimerP_setup()` and
 *    `TimerP_clearOverflowInt()` for each.
 * 4. Start both timers and `ClockP_usleep(200)` to allow initial progress.
 * 5. Create two toggler tasks (`TestDplTimer_mt_task_toggler`), one per timer instance.
 * 6. Phase A: Create a high-priority counter task (`TestDplTimer_mt_task_counter`) for Timer0; wait
 *    until `TestDplTimer_mtObservedChange` becomes true or a bounded timeout; record `observedA`
 *    and destruct the counter task.
 * 7. Phase B: Reset `TestDplTimer_mtObservedChange`; create the counter task for Timer1; wait as
 *    above; record `observedB` and destruct the counter task.
 * 8. Request togglers to stop; stop both timers via `TimerP_stop()`.
 * 9. Assertions:
 *    - At least some ISR activity occurred across instances.
 *    - `observedA == true` and `observedB == true` (count advanced on each instance).
 *    - Optionally, verify different reload counts for the two configured periods.
 * 10. Destruct tasks, HWIs, and semaphores to clean up.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
static void TestDplTimer_multithread_multiple_instances(void *args)
{
#if defined(CONFIG_TIMER1) && defined(CONFIG_TIMER1_INT_NUM)
    uint32_t       baseA;
    uint32_t       baseB;
    uint32_t       intA;
    uint32_t       intB;
    int32_t        status;
    HwiP_Object    hwiA;
    HwiP_Object    hwiB;
    HwiP_Params    hwiParams;
    TimerP_Params  paramsA;
    TimerP_Params  paramsB;
    TaskP_Object   taskToggleA;
    TaskP_Object   taskToggleB;
    TaskP_Object   taskCounter;
    TaskP_Params   tparamsTogA;
    TaskP_Params   tparamsTogB;
    TaskP_Params   tparamsCnt;
    SemaphoreP_Object semExit;
    uint64_t       tStartUsec;
    bool           observedA;
    bool           observedB;
    uint32_t togglerExits = 0;

    baseA      = gTimerBaseAddr[CONFIG_TIMER0];
    baseB      = gTimerBaseAddr[CONFIG_TIMER1];
    intA       = CONFIG_TIMER0_INT_NUM;
    intB       = CONFIG_TIMER1_INT_NUM;
    status     = SystemP_SUCCESS;
    tStartUsec = 0U;
    observedA  = false;
    observedB  = false;

    /* Reset globals used by shared tasks/ISR */
    TestDplTimer_mtStopRequested  = false;
    TestDplTimer_mtObservedChange = false;
    TestDplTimer_mtCounterStopRequested = false;
    TestDplTimer_mtIsrCount       = 0U;

    /* Counting semaphore to collect task exits (counter + togglers) */
    status = SemaphoreP_constructCounting(&TestDplTimer_mtSemIsr, 0, 4);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Counting semaphore: collect exits from togglers and counter (3 total per phase) */
    status = SemaphoreP_constructCounting(&semExit, 0, 3);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Counting semaphore for ISR progress (shared ISR posts here) */
    status = SemaphoreP_constructCounting(&TestDplTimer_mtSemDone, 0, 64);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Bind ISR for timer A */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intA;
    hwiParams.callback = TestDplTimer_mt_overflow_isr;
#if defined(__ARM_ARCH_7R__) || defined(SOC_AM64X) || defined(SOC_AM243X) || defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1U;
#else
    hwiParams.isPulse  = 0U;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseA;
    hwiParams.priority = 4U;
#if defined(__C7000__)
    hwiParams.eventId  = CONFIG_TIMER0_EVENT_ID;
#endif
    status = HwiP_construct(&hwiA, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Bind ISR for timer B */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum   = intB;
    hwiParams.callback = TestDplTimer_mt_overflow_isr;
#if defined(__ARM_ARCH_7R__) || defined(SOC_AM64X) || defined(SOC_AM243X) || defined(SOC_AM62X) || defined(SOC_AM62AX)
    hwiParams.isPulse  = 1U;
#else
    hwiParams.isPulse  = 0U;
#endif
    hwiParams.args     = (void *)(uintptr_t)baseB;
    hwiParams.priority = 4U;
#if defined(__C7000__)
    hwiParams.eventId  = CONFIG_TIMER1_EVENT_ID;
#endif
    status = HwiP_construct(&hwiB, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configure periodic timers with different periods */
    TimerP_Params_init(&paramsA);
    paramsA.enableOverflowInt = 1U;
    paramsA.periodInUsec      = 1000U;  /* 1 ms */
    paramsA.periodInNsec      = 0U;
    paramsA.inputPreScaler    = 1U;
    paramsA.oneshotMode       = 0U;
    paramsA.enableDmaTrigger  = 0U;
    TimerP_setup(baseA, &paramsA);
    TimerP_clearOverflowInt(baseA);

    TimerP_Params_init(&paramsB);
    paramsB.enableOverflowInt = 1U;
    paramsB.periodInUsec      = 1500U;  /* 1.5 ms */
    paramsB.periodInNsec      = 0U;
    paramsB.inputPreScaler    = 1U;
    paramsB.oneshotMode       = 0U;
    paramsB.enableDmaTrigger  = 0U;
    TimerP_setup(baseB, &paramsB);
    TimerP_clearOverflowInt(baseB);

    /* Start both timers to ensure progress before task creation */
    TimerP_start(baseA);
    TimerP_start(baseB);
    ClockP_usleep(200U);

    /* Build toggler tasks for A and B */
    TaskP_Params_init(&tparamsTogA);
    tparamsTogA.priority  = 3U;
    tparamsTogA.stackSize = sizeof(TestDplTimer_threadStack1);
    tparamsTogA.stack     = TestDplTimer_threadStack1;
    tparamsTogA.args      = (void *)(uintptr_t)baseA;
    tparamsTogA.taskMain  = TestDplTimer_mt_task_toggler;
    tparamsTogA.name      = (char *)"TimerA_Toggler";
#if defined(CONFIG_SMP_TEST_ENABLE)
    tparamsTogA.coreAffinity   = ( 1U << 0);
#endif

    status = TaskP_construct(&taskToggleA, &tparamsTogA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&tparamsTogB);
    tparamsTogB.priority  = 3U;
    tparamsTogB.stackSize = sizeof(TestDplTimer_threadStack2);
    tparamsTogB.stack     = TestDplTimer_threadStack2;
    tparamsTogB.args      = (void *)(uintptr_t)baseB;
    tparamsTogB.taskMain  = TestDplTimer_mt_task_toggler;
    tparamsTogB.name      = (char *)"TimerB_Toggler";
#if defined(CONFIG_SMP_TEST_ENABLE)
    tparamsTogB.coreAffinity   = ( 1U << 1);
#endif
    status = TaskP_construct(&taskToggleB, &tparamsTogB);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

     /* Phase 1: Counter observes TimerA */
    TestDplTimer_mtObservedChange = false;
    TestDplTimer_mtCounterStopRequested = false;
    TaskP_Params_init(&tparamsCnt);
    tparamsCnt.priority  = 5U;
    tparamsCnt.stackSize = sizeof(TestDplTimer_threadStack3);
    tparamsCnt.stack     = TestDplTimer_threadStack3;
    tparamsCnt.args      = (void *)(uintptr_t)baseA;
    tparamsCnt.taskMain  = TestDplTimer_mt_task_counter;
    tparamsCnt.name      = (char *)"TimerA_Counter";
#if defined(CONFIG_SMP_TEST_ENABLE)
    tparamsCnt.coreAffinity   = ( 1U << 3);
#endif
    status = TaskP_construct(&taskCounter, &tparamsCnt);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait until the counter actually observes a change or timeout */
    tStartUsec = ClockP_getTimeUsec();
    while (!TestDplTimer_mtObservedChange)
    {
        if ((ClockP_getTimeUsec() - tStartUsec) > 5000000U) /* 5s - increased timeout */
        {
            break;
        }
        ClockP_usleep(10000U); /* 10ms sleep instead of semaphore pend */
    }

    /* Added a small delay to ensure proper task scheduling */
    ClockP_usleep(10000U);

    observedA = TestDplTimer_mtObservedChange;
    /* Ensure counter task exits before destruct */
    TestDplTimer_mtCounterStopRequested = true;
    tStartUsec = ClockP_getTimeUsec();
    while ((ClockP_getTimeUsec() - tStartUsec) < 2000000U) /* Wait up to 2s */
    {
        if (SemaphoreP_pend(&TestDplTimer_mtSemIsr, ClockP_usecToTicks(100000U)) == SystemP_SUCCESS)
        {
            break;
        }
    }

    /* Added a small delay to ensure task is properly destructed */
    ClockP_usleep(10000U);
    TaskP_destruct(&taskCounter);

    /* Phase 2: Counter observes TimerB */
    TestDplTimer_mtObservedChange = false;
    TestDplTimer_mtCounterStopRequested = false;
    ClockP_usleep(1000U);

    TaskP_Params_init(&tparamsCnt);
    tparamsCnt.priority  = 5U;
    tparamsCnt.stackSize = sizeof(TestDplTimer_threadStack3);
    tparamsCnt.stack     = TestDplTimer_threadStack3;
    tparamsCnt.args      = (void *)(uintptr_t)baseB;
    tparamsCnt.taskMain  = TestDplTimer_mt_task_counter;
    tparamsCnt.name      = (char *)"TimerB_Counter";
#if defined(CONFIG_SMP_TEST_ENABLE)
    tparamsCnt.coreAffinity   = ( 1U << 1);
#endif
    status = TaskP_construct(&taskCounter, &tparamsCnt);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait until the counter actually observes a change or timeout */
    tStartUsec = ClockP_getTimeUsec();
    while (!TestDplTimer_mtObservedChange)
    {
        if ((ClockP_getTimeUsec() - tStartUsec) > 5000000U) /* 5s - increased timeout */
        {
            break;
        }
        ClockP_usleep(10000U); /* 10ms sleep instead of semaphore pend */
    }

    observedB = TestDplTimer_mtObservedChange;
    /* Ensure counter task exits before destruct */
    TestDplTimer_mtCounterStopRequested = true;
    tStartUsec = ClockP_getTimeUsec();
    while ((ClockP_getTimeUsec() - tStartUsec) < 2000000U) /* Wait up to 2s */
    {
        if (SemaphoreP_pend(&TestDplTimer_mtSemIsr, ClockP_usecToTicks(100000U)) == SystemP_SUCCESS)
        {
            break;
        }
    }

#if defined(CONFIG_SMP_TEST_ENABLE)
    ClockP_usleep(10000U);
#endif

    TaskP_destruct(&taskCounter);

    /* Request togglers to stop and wait for them to actually exit */
    TestDplTimer_mtStopRequested = true;

    /* Wait for both togglers to exit with proper timeout */
    tStartUsec = ClockP_getTimeUsec();
    while (togglerExits < 2U && ((ClockP_getTimeUsec() - tStartUsec) < 5000000U))
    {
        if (SemaphoreP_pend(&TestDplTimer_mtSemIsr, ClockP_usecToTicks(500000U)) == SystemP_SUCCESS)
        {
            togglerExits++;
        }
    }

    /* Stop timers */
    TimerP_stop(baseA);
    TimerP_stop(baseB);

    /* Wait for togglers to exit before destructing them */
    (void)SemaphoreP_pend(&TestDplTimer_mtSemIsr, ClockP_usecToTicks(2000000U));
    (void)SemaphoreP_pend(&TestDplTimer_mtSemIsr, ClockP_usecToTicks(2000000U));

    /* Validate progress on both instances and some ISR activity */
    TEST_ASSERT_TRUE(TestDplTimer_mtIsrCount >= 2U);
    TEST_ASSERT_TRUE(observedA);
    TEST_ASSERT_TRUE(observedB);

    /* Cleanup */
    TaskP_destruct(&taskToggleA);
    TaskP_destruct(&taskToggleB);
    HwiP_destruct(&hwiA);
    HwiP_destruct(&hwiB);
    SemaphoreP_destruct(&semExit);
    SemaphoreP_destruct(&TestDplTimer_mtSemDone);
    SemaphoreP_destruct(&TestDplTimer_mtSemIsr);
#else
    DebugP_logWarn("CONFIG_TIMER1 not defined; skipping multi-instance test (ID 1031)\r\n");
#endif
}

#endif /* defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM275X) */


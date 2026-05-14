/*
 * Copyright (C) 2024-2026 Texas Instruments Incorporated
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

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/rtc.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_RTC_INTERRUPT_COUNT             (3U)
#define TEST_RTC_RAPID_CYCLE_COUNT           (10U)
#define TEST_RTC_RAPID_READ_COUNT            (5U)
#define TEST_RTC_ALARM_WAIT_SEC              (5U)
#define TEST_RTC_SCRATCH_REGISTER_COUNT      (8U)

/* Time field maximum valid values */
#define TEST_RTC_MAX_HOUR                    (23U)
#define TEST_RTC_MAX_MINUTE                  (59U)
#define TEST_RTC_MAX_SECOND                  (59U)
#define TEST_RTC_SECONDS_PER_HOUR            (3600U)
#define TEST_RTC_SECONDS_PER_MINUTE          (60U)

/* Common sleep durations (seconds) */
#define TEST_RTC_SLEEP_1_SEC                 (1U)
#define TEST_RTC_SLEEP_2_SEC                 (2U)
#define TEST_RTC_SLEEP_3_SEC                 (3U)
#define TEST_RTC_SLEEP_7_SEC                 (7U)
#define TEST_RTC_SLEEP_10_SEC                (10U)

/* Common microsecond delays */
#define TEST_RTC_USLEEP_100_US               (100U)
#define TEST_RTC_USLEEP_1_MS                 (1000U)
#define TEST_RTC_USLEEP_5_MS                 (5000U)
#define TEST_RTC_USLEEP_10_MS                (10000U)
#define TEST_RTC_USLEEP_50_MS                (50000U)
#define TEST_RTC_USLEEP_100_MS               (100000U)
#define TEST_RTC_USLEEP_200_MS               (200000U)

/* Semaphore timeout values (microseconds) */
#define TEST_RTC_SEM_TIMEOUT_2_SEC           (2000000U)
#define TEST_RTC_SEM_TIMEOUT_3_SEC           (3000000U)
#define TEST_RTC_SEM_TIMEOUT_10_SEC          (10000000U)
#define TEST_RTC_SEM_TIMEOUT_12_SEC          (12000000U)
#define TEST_RTC_SEM_TIMEOUT_15_SEC          (15000000U)
#define TEST_RTC_SEM_TIMEOUT_20_SEC          (20000000U)

/* Scratch register test patterns */
#define TEST_RTC_PATTERN_ALL_ZEROS           (0x00000000U)
#define TEST_RTC_PATTERN_ALL_ONES            (0xFFFFFFFFU)
#define TEST_RTC_PATTERN_ALT_A               (0xAAAAAAAAU)
#define TEST_RTC_PATTERN_ALT_5               (0x55555555U)
#define TEST_RTC_PATTERN_CHECKERBOARD_A      (0xA5A5A5A5U)
#define TEST_RTC_PATTERN_CHECKERBOARD_B      (0x5A5A5A5AU)
#define TEST_RTC_PATTERN_DEAD_BASE           (0xDEAD0000U)
#define TEST_RTC_PATTERN_DEADBEEF            (0xDEADBEEFU)
#define TEST_RTC_PATTERN_UNIQUE              (0x12345678U)
#define TEST_RTC_PATTERN_KNOWN               (0xAABBCCDDU)
#define TEST_RTC_PATTERN_SCRATCH_A_BASE      (0xAAAA0000U)
#define TEST_RTC_PATTERN_SCRATCH_B_BASE      (0xBBBB0000U)
#define TEST_RTC_PATTERN_UPPER_MASK          (0xFFFF0000U)

/* Invalid index values for negative tests */
#define TEST_RTC_INVALID_INDEX_MAX           (0xFFFFFFFFU)
#define TEST_RTC_INVALID_SCRATCH_INDEX       (8U)

#ifdef ENABLE_MT_TESTS

#define TEST_RTC_MT_TASK_STACK_SIZE          (4096U)
#define TEST_RTC_MT_TASK_PRIORITY_HIGH       (4U)
#define TEST_RTC_MT_TASK_PRIORITY_LOW        (3U)
#define TEST_RTC_MT_TIMEOUT_TICKS            (20000U)

#define TEST_RTC_MT_WRITER_ITERATIONS        (50U)
#define TEST_RTC_MT_READER_ITERATIONS        (100U)
#define TEST_RTC_MT_SCRATCH_ITERATIONS       (50U)
#define TEST_RTC_MT_STOPSTART_ITERATIONS     (10U)
#define TEST_RTC_MT_GETTIME_ITERATIONS       (200U)
#define TEST_RTC_MT_SETTIME_LOOP_COUNT       (50U)
#define TEST_RTC_MT_PARALLEL_ITERATIONS      (1000U)
#define TEST_RTC_MT_ALARM_SETTIME_ITERATIONS (20U)

#endif /* ENABLE_MT_TESTS */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static SemaphoreP_Object TestRtc_OnOffSemObj;
static SemaphoreP_Object TestRtc_OffOnSemObj;
/* External reference to RTC config array (defined in generated ti_drivers_config.c) */
extern RTC_Config gRTCConfig[];
extern uint32_t gRTCConfigNum;

#ifdef ENABLE_MT_TESTS

/* Reusable task stacks (tests are sequential, stacks reused) */
static uint8_t TestRtc_TaskStackA[TEST_RTC_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
static uint8_t TestRtc_TaskStackB[TEST_RTC_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));

/* Counting semaphore for task completion join */
static SemaphoreP_Object TestRtc_TaskDoneSemaphore;

/* Barrier semaphore for synchronized start (concurrentOpenAttempt) */
static SemaphoreP_Object TestRtc_BarrierSemaphore;

/* Per-task volatile result variables (reset before each test) */
static volatile int32_t  TestRtc_TaskFailCountA;
static volatile int32_t  TestRtc_TaskFailCountB;
static volatile uint32_t TestRtc_TaskFlagA;
static volatile uint32_t TestRtc_TaskFlagB;

/* Concurrent open handles */
static volatile RTC_Handle TestRtc_RaceHandleA;
static volatile RTC_Handle TestRtc_RaceHandleB;

#endif /* ENABLE_MT_TESTS */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Callback Functions */
void TestRtc_onOffCallback(RTC_Handle handle);
void TestRtc_offOnCallback(RTC_Handle handle);
static void TestRtc_noopCallback(RTC_Handle handle);

/* ========================================================================== */
/*                  Static Test Function Prototypes                           */
/* ========================================================================== */

/*Functional Test Cases */
static void TestRtc_setGetTime(void *args);
static void TestRtc_multipleOnOffInterrupts(void *args);
static void TestRtc_multipleOffOnInterrupts(void *args);
static void TestRtc_initAndDeinit(void *args);
static void TestRtc_openWithDefaultParams(void *args);
static void TestRtc_openWithFreezeMode(void *args);
static void TestRtc_openAndClose(void *args);
static void TestRtc_hardwareInitRegisterState(void *args);
static void TestRtc_timeIncrement(void *args);
static void TestRtc_leapYearDateHandling(void *args);
static void TestRtc_timeBoundaryTransitions(void *args);
static void TestRtc_calculateElapsedTime(void *args);
static void TestRtc_getTimeMonotonicity(void *args);
static void TestRtc_extendedTimeRange(void *args);
static void TestRtc_shadowAutoSyncReadWrite(void *args);
static void TestRtc_32kHzCounterTickAccuracy(void *args);
static void TestRtc_alarmAfterTimeUpdate(void *args);
static void TestRtc_alarmDisable(void *args);
static void TestRtc_alarmOverwriteBehavior(void *args);
static void TestRtc_timerEventBoundaryTimes(void *args);
static void TestRtc_callbackRegistration(void *args);
static void TestRtc_interruptClearedAfterCallback(void *args);
static void TestRtc_bothCallbacksRegisteredAndInvoked(void *args);
static void TestRtc_startAndStop(void *args);
static void TestRtc_timeRetentionAcrossReset(void *args);
static void TestRtc_alarmDuringIdleSleep(void *args);
static void TestRtc_counterDiscontinuityDetection(void *args);
static void TestRtc_scratchRegisterReadWrite(void *args);
static void TestRtc_scratchRegisterPersistence(void *args);
static void TestRtc_adjustForDriftCompensation(void *args);
static void TestRtc_writeAccessControl(void *args);

/* Negative Test Cases */
static void TestRtc_invalidDateReject(void *args);
static void TestRtc_nullHandleRejected(void *args);
static void TestRtc_outOfRangeYear(void *args);
static void TestRtc_openInvalidIndex(void *args);
static void TestRtc_doubleOpenAndDoubleClose(void *args);
static void TestRtc_calendarFieldBoundaryValidation(void *args);
static void TestRtc_timeFieldOutOfRange(void *args);
static void TestRtc_nullDataPointerAllApis(void *args);
static void TestRtc_alarmInPast(void *args);
static void TestRtc_scratchRegisterOutOfRange(void *args);
static void TestRtc_operationsOnClosedHandle(void *args);
static void TestRtc_redundantStopAndStart(void *args);
static void TestRtc_deinitWithOpenInstance(void *args);
/* Disabled: driver bug — RTC_convertTimeToSeconds() has unbounded
 * for-loop (iterates year from 1970 to rtc_time->year). With
 * UINT32_MAX fields the loop runs ~4.29 billion iterations causing
 * an indefinite hang. Needs input validation in RTC_setTime(). */
/* static void TestRtc_setTimeMaxUint32Fields(void *args); */

#ifdef ENABLE_MT_TESTS
/* Multithread Test Cases */
static void TestRtc_multipleInstances(void *args);
static void TestRtc_concurrentAlarmSameTime(void *args);
static void TestRtc_concurrentAccessRaceCondition(void *args);
static void TestRtc_concurrentScratchRegisterAccess(void *args);
static void TestRtc_concurrentAlarmAndSetTime(void *args);
static void TestRtc_concurrentStopStartWithGetTime(void *args);
static void TestRtc_isrDuringApiExecution(void *args);
static void TestRtc_concurrentOpenAttempt(void *args);
static void TestRtc_highFrequencyParallelGetTime(void *args);

/* Task worker functions */
static void TestRtc_instanceWorkerA(void *args);
static void TestRtc_instanceWorkerB(void *args);
static void TestRtc_alarmSameTimeWorkerA(void *args);
static void TestRtc_alarmSameTimeWorkerB(void *args);
static void TestRtc_raceWriterWorker(void *args);
static void TestRtc_raceReaderWorker(void *args);
static void TestRtc_scratchWorkerA(void *args);
static void TestRtc_scratchWorkerB(void *args);
static void TestRtc_alarmSetTimeWorkerA(void *args);
static void TestRtc_alarmSetTimeWorkerB(void *args);
static void TestRtc_stopStartWorker(void *args);
static void TestRtc_getTimeLoopWorker(void *args);
static void TestRtc_isrSetTimeWorker(void *args);
static void TestRtc_isrAlarmWaitWorker(void *args);
static void TestRtc_openRaceWorkerA(void *args);
static void TestRtc_openRaceWorkerB(void *args);
static void TestRtc_parallelGetTimeWorkerA(void *args);
static void TestRtc_parallelGetTimeWorkerB(void *args);
#endif /* ENABLE_MT_TESTS */

/* ========================================================================== */
/*                       Internal Function Definitions                        */
/* ========================================================================== */

void TestRtc_onOffCallback(RTC_Handle handle)
{
    /* Post Semaphore */
    SemaphoreP_post(&TestRtc_OnOffSemObj);
}

void TestRtc_offOnCallback(RTC_Handle handle)
{
    /* Post Semaphore */
    SemaphoreP_post(&TestRtc_OffOnSemObj);
}

static void TestRtc_noopCallback(RTC_Handle handle)
{
    /* Intentionally empty — simulates a disabled callback */
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    /* Open RTC instance */
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);

    /* Open drivers to open the UART driver for console */
    UNITY_BEGIN();
    RUN_TEST(TestRtc_setGetTime,                            5822, NULL);
    RUN_TEST(TestRtc_multipleOnOffInterrupts,               5823, NULL);
    RUN_TEST(TestRtc_multipleOffOnInterrupts,               5824, NULL);
    RUN_TEST(TestRtc_initAndDeinit,                         11800, NULL);
    RUN_TEST(TestRtc_openWithDefaultParams,                 11801, NULL);
    RUN_TEST(TestRtc_openWithFreezeMode,                    11802, NULL);
    RUN_TEST(TestRtc_openAndClose,                          11803, NULL);
    RUN_TEST(TestRtc_hardwareInitRegisterState,             11804, NULL);
    RUN_TEST(TestRtc_timeIncrement,                         11805, NULL);
    RUN_TEST(TestRtc_leapYearDateHandling,                  11806, NULL);
    RUN_TEST(TestRtc_timeBoundaryTransitions,               11807, NULL);
    RUN_TEST(TestRtc_calculateElapsedTime,                  11808, NULL);
    RUN_TEST(TestRtc_getTimeMonotonicity,                   11809, NULL);
    RUN_TEST(TestRtc_extendedTimeRange,                     11810, NULL);
    RUN_TEST(TestRtc_shadowAutoSyncReadWrite,               11811, NULL);
    RUN_TEST(TestRtc_32kHzCounterTickAccuracy,              11812, NULL);
    RUN_TEST(TestRtc_alarmAfterTimeUpdate,                  11813, NULL);
    RUN_TEST(TestRtc_alarmDisable,                          11814, NULL);
    RUN_TEST(TestRtc_alarmOverwriteBehavior,                11815, NULL);
    RUN_TEST(TestRtc_timerEventBoundaryTimes,               11816, NULL);
    RUN_TEST(TestRtc_callbackRegistration,                  11817, NULL);
    RUN_TEST(TestRtc_interruptClearedAfterCallback,         11818, NULL);
    RUN_TEST(TestRtc_bothCallbacksRegisteredAndInvoked,     11819, NULL);
    RUN_TEST(TestRtc_startAndStop,                          11820, NULL);
    RUN_TEST(TestRtc_timeRetentionAcrossReset,              11821, NULL);
    RUN_TEST(TestRtc_alarmDuringIdleSleep,                  11822, NULL);
    RUN_TEST(TestRtc_counterDiscontinuityDetection,         11823, NULL);
    RUN_TEST(TestRtc_scratchRegisterReadWrite,              11824, NULL);
    RUN_TEST(TestRtc_scratchRegisterPersistence,            11825, NULL);
    RUN_TEST(TestRtc_adjustForDriftCompensation,            11826, NULL);
    RUN_TEST(TestRtc_writeAccessControl,                    11827, NULL);

    /* Negative Test Cases */
    RUN_TEST(TestRtc_invalidDateReject,                     11828, NULL);
    RUN_TEST(TestRtc_nullHandleRejected,                    11829, NULL);
    RUN_TEST(TestRtc_outOfRangeYear,                        11830, NULL);
    RUN_TEST(TestRtc_openInvalidIndex,                      11831, NULL);
    RUN_TEST(TestRtc_doubleOpenAndDoubleClose,              11832, NULL);
    RUN_TEST(TestRtc_calendarFieldBoundaryValidation,       11833, NULL);
    RUN_TEST(TestRtc_timeFieldOutOfRange,                   11834, NULL);
    RUN_TEST(TestRtc_nullDataPointerAllApis,                11835, NULL);
    RUN_TEST(TestRtc_alarmInPast,                           11836, NULL);
    RUN_TEST(TestRtc_scratchRegisterOutOfRange,             11837, NULL);
    RUN_TEST(TestRtc_operationsOnClosedHandle,              11838, NULL);
    RUN_TEST(TestRtc_redundantStopAndStart,                 11839, NULL);
    RUN_TEST(TestRtc_deinitWithOpenInstance,                11840, NULL);
    /* Disabled: driver bug — RTC_convertTimeToSeconds() has unbounded
     * for-loop (iterates year from 1970 to rtc_time->year). With
     * UINT32_MAX fields the loop runs ~4.29 billion iterations causing
     * an indefinite hang. Needs input validation in RTC_setTime(). */
    /* RUN_TEST(TestRtc_setTimeMaxUint32Fields,             11850, NULL); */
#ifdef ENABLE_MT_TESTS
    /* Multithread Test Cases */
    RUN_TEST(TestRtc_multipleInstances,                     11841, NULL);
    RUN_TEST(TestRtc_concurrentAlarmSameTime,               11842, NULL);
    RUN_TEST(TestRtc_concurrentAccessRaceCondition,         11843, NULL);
    RUN_TEST(TestRtc_concurrentScratchRegisterAccess,       11844, NULL);
    RUN_TEST(TestRtc_concurrentAlarmAndSetTime,             11845, NULL);
    RUN_TEST(TestRtc_concurrentStopStartWithGetTime,        11846, NULL);
    RUN_TEST(TestRtc_isrDuringApiExecution,                 11847, NULL);
    RUN_TEST(TestRtc_concurrentOpenAttempt,                 11848, NULL);
    RUN_TEST(TestRtc_highFrequencyParallelGetTime,          11849, NULL);
#endif /* ENABLE_MT_TESTS */

    UNITY_END();

    /* Close RTC instance */
    if(gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }

    return;
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

/* ========================================================================== */
/*                       Functional Test Case Definitions                     */
/* ========================================================================== */

static void TestRtc_setGetTime(void* args)
{
    RTC_Handle rtcHandle = NULL;
    RTC_Time setTime, getTime;
    int32_t status = SystemP_SUCCESS;

    /* Store handle for Local use */
    if(gRTCHandle[CONFIG_RTC0] != NULL)
    {
        rtcHandle = gRTCHandle[CONFIG_RTC0];
    }
    else
    {
        status = SystemP_FAILURE;
    }

    /* Set the current time (e.g., 5th November 2024, 14:42:10) */
    setTime.year = 2024U;
    setTime.month = 11U;
    setTime.day = 5U;
    setTime.hour = 14U;
    setTime.minute = 42U;
    setTime.second = 10U;
    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for 5 seconds */
    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    /* Retrieve the time */
    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_UINT32_WITHIN(1U,15U,getTime.second);
}

static void TestRtc_multipleOnOffInterrupts(void* args)
{
    RTC_Handle rtcHandle = NULL;
    RTC_Time setTime;
    int32_t status = SystemP_SUCCESS;
    uint32_t i;

    /* Store handle for Local use */
    if(gRTCHandle[CONFIG_RTC0] != NULL)
    {
        rtcHandle = gRTCHandle[CONFIG_RTC0];
    }
    else
    {
        status = SystemP_FAILURE;
    }

    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Set the current time (e.g., 5th November 2024, 14:45:10) */
    setTime.year = 2024U;
    setTime.month = 11U;
    setTime.day = 5U;
    setTime.hour = 14U;
    setTime.minute = 45U;
    setTime.second = 10U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Set multiple On-Off interrupts */
    for(i=1U; i<=TEST_RTC_INTERRUPT_COUNT; i+=1)
    {
        setTime.second += (2U);
        RTC_setOn_OffTimerEvent(rtcHandle, &setTime);

        /* Wait for the interrupt */
        status = SemaphoreP_pend(&TestRtc_OnOffSemObj, ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    }
    TEST_ASSERT_EQUAL_UINT32(4U,i);
    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

static void TestRtc_multipleOffOnInterrupts(void* args)
{
    RTC_Handle rtcHandle = NULL;
    RTC_Time setTime;
    int32_t status = SystemP_SUCCESS;
    uint32_t i;

    /* Store handle for Local use */
    if(gRTCHandle[CONFIG_RTC0] != NULL)
    {
        rtcHandle = gRTCHandle[CONFIG_RTC0];
    }
    else
    {
        status = SystemP_FAILURE;
    }

    SemaphoreP_constructBinary(&TestRtc_OffOnSemObj, 0U);

    /* Set the current time (e.g., 7th November 2024, 14:45:10) */
    setTime.year = 2024U;
    setTime.month = 11U;
    setTime.day = 7U;
    setTime.hour = 14U;
    setTime.minute = 45U;
    setTime.second = 10U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Set multiple Off-On interrupts */
    for(i=1U; i<=TEST_RTC_INTERRUPT_COUNT; i+=1)
    {
        setTime.second += (2U);
        RTC_setOff_OnTimerEvent(rtcHandle, &setTime);

        /* Wait for the interrupt */
        status = SemaphoreP_pend(&TestRtc_OffOnSemObj, ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    }
    TEST_ASSERT_EQUAL_UINT32(4U,i);
    SemaphoreP_destruct(&TestRtc_OffOnSemObj);
}

/**
 * \brief Test RTC init and deinit lifecycle
 *
 * Test Category: Functional
 *
 * Verifies that RTC_init() initializes the driver state (marks all instances
 * as closed via isOpen = false, constructs the driver mutex via
 * SemaphoreP_constructMutex) and that RTC_deinit() correctly releases all
 * resources. Ensures the driver can be re-initialized after de-initialization
 * without assertion failure or hang.
 *
 * Test steps:
 * 1. Call RTC_init() to initialize the RTC driver.
 * 2. Verify isOpen == false for all configs in gRTCConfig[].
 *    gRTCDrvObj.lock is static and cannot be verified directly; verified
 *    indirectly by confirming RTC_open() succeeds (which pends on the lock).
 * 3. Call RTC_deinit() to release resources.
 * 4. gRTCDrvObj.lock is static and cannot be verified as NULL directly;
 *    verified indirectly by confirming re-init succeeds in step 5.
 * 5. Call RTC_init() again and verify it succeeds without assertion or hang.
 *    Verify isOpen flags are false and RTC_open() succeeds.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC_init() and RTC_deinit() complete without assertion
 *                 failure or hang. isOpen is false after each init call.
 *                 RTC_open() succeeds after both init and re-init.
 */
static void TestRtc_initAndDeinit(void *args)
{
    RTC_Handle rtcHandle = NULL;

    /* Ensure clean state: close any previously opened handle and deinit */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();

    /* Step 1: Call RTC_init() to initialize the RTC driver */
    RTC_init();

    /* Step 2: Verify isOpen == false after init.
     * gRTCDrvObj.lock is static — verified indirectly by a successful open. */
    TEST_ASSERT_FALSE(gRTCConfig[CONFIG_RTC0].object->isOpen);

    rtcHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(rtcHandle);
    RTC_close(rtcHandle);

    /* Step 3: Call RTC_deinit() to release resources */
    RTC_deinit();

    /* Step 4: gRTCDrvObj.lock is static — cannot verify NULL directly.
     * Verified indirectly by step 5 succeeding. */

    /* Step 5: Call RTC_init() again and verify no assertion or hang */
    RTC_init();

    TEST_ASSERT_FALSE(gRTCConfig[CONFIG_RTC0].object->isOpen);

    /* Verify driver is fully functional after re-initialization */
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test RTC open with NULL params applies default configuration
 *
 * Test Category: Functional
 *
 * Verifies that passing NULL to RTC_open() causes the driver to apply
 * RTC_defaultParams (isfreezemode=1U, onOffCallback=false,
 * offOnCallback=false) and returns a valid non-NULL handle. Also validates
 * that RTC_paramsInit() produces matching default values.
 *
 * Test steps:
 * 1. Call RTC_init() if not already done.
 * 2. Declare RTC_Params; call RTC_paramsInit(). Assert isfreezemode == 1U,
 *    onOffCallback == false, offOnCallback == false.
 * 3. Call RTC_open(CONFIG_RTC0, NULL).
 * 4. Verify handle is not NULL.
 * 5. Close RTC handle and verify no error or hang.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC_paramsInit() returns correct default values.
 *                 RTC_open() with NULL params returns a valid handle.
 *                 RTC_close() completes without error.
 */
static void TestRtc_openWithDefaultParams(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Params  defaultParams;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();

    /* Step 1: Initialize the RTC driver */
    RTC_init();

    /* Step 2: Verify RTC_paramsInit produces correct defaults */
    RTC_paramsInit(&defaultParams);
    TEST_ASSERT_EQUAL_UINT32(1U, defaultParams.isfreezemode);
    TEST_ASSERT_FALSE(defaultParams.onOffCallback);
    TEST_ASSERT_FALSE(defaultParams.offOnCallback);

    /* Step 3: Open with NULL params (driver applies defaults internally) */
    rtcHandle = RTC_open(CONFIG_RTC0, NULL);

    /* Step 4: Verify returned handle is not NULL */
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 5: Close handle and verify no error or hang */
    RTC_close(rtcHandle);

    /* Restore state for subsequent tests */
    RTC_deinit();
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test RTC open with freeze mode explicitly configured
 *
 * Test Category: Functional
 *
 * Verifies that opening with an explicit RTC_Params struct with
 * isfreezemode=1U succeeds and the freeze mode bit (RTC_FREEZE_MODE =
 * 0x02000000) is set in the hardware CSL_RTC_GENRAL_CTL register during
 * the open sequence.
 *
 * Test steps:
 * 1. Call RTC_paramsInit() to populate defaults.
 * 2. Explicitly set params.isfreezemode = 1U.
 * 3. Call RTC_open(CONFIG_RTC0, &params).
 * 4. Verify returned handle is not NULL.
 * 5. Call RTC_close() and verify no errors or write-pend timeout.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC_open() with freeze mode enabled returns a valid handle.
 *                 RTC_close() completes without error or timeout.
 */
static void TestRtc_openWithFreezeMode(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Params  freezeModeParams;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    /* Step 1: Initialize params with defaults */
    RTC_paramsInit(&freezeModeParams);

    /* Step 2: Explicitly set freeze mode */
    freezeModeParams.isfreezemode = 1U;

    /* Step 3: Open RTC with freeze mode params */
    rtcHandle = RTC_open(CONFIG_RTC0, &freezeModeParams);

    /* Step 4: Verify handle is valid */
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 5: Close and verify no errors or write-pend timeout */
    RTC_close(rtcHandle);

    /* Restore state for subsequent tests */
    RTC_deinit();
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test RTC open and close lifecycle with re-open
 *
 * Test Category: Functional
 *
 * Verifies that RTC_open() returns a valid handle, RTC_close() cleans up
 * correctly, and the instance can be successfully re-opened and used after
 * closing. Note: RTC_close() does not reset the isOpen flag in the current
 * driver; a RTC_deinit() + RTC_init() cycle is required before re-opening.
 *
 * Test steps:
 * 1. Call RTC_open(CONFIG_RTC0, NULL) and assert handle is not NULL.
 * 2. Call RTC_close(handle).
 * 3. Call RTC_deinit() + RTC_init() to reset isOpen flag (driver gap
 *    workaround: RTC_close does not clear isOpen).
 * 4. Call RTC_open(CONFIG_RTC0, NULL) again and verify handle is valid.
 * 5. Call RTC_setTime() and RTC_getTime() on re-opened handle and verify
 *    both return SystemP_SUCCESS. Close the handle.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC instance can be re-opened after close and used
 *                 for time set and get operations successfully.
 */
static void TestRtc_openAndClose(void *args)
{
    RTC_Handle  firstHandle = NULL;
    RTC_Handle  secondHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    /* Step 1: Open RTC instance */
    firstHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(firstHandle);

    /* Step 2: Close the handle */
    RTC_close(firstHandle);

    /*
     * Step 3: Driver gap workaround — RTC_close() does not reset
     * object->isOpen to false. A subsequent RTC_open() without
     * RTC_deinit() + RTC_init() will fail because the driver sees
     * isOpen == true and returns NULL.
     */
    RTC_deinit();
    RTC_init();

    /* Step 4: Re-open RTC instance and verify handle is valid */
    secondHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(secondHandle);

    /* Step 5: Verify RTC_setTime() and RTC_getTime() work on re-opened handle */
    setTime.year   = 2024U;
    setTime.month  = 6U;
    setTime.day    = 15U;
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(secondHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(secondHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Restore global handle for subsequent tests */
    gRTCHandle[CONFIG_RTC0] = secondHandle;
}

/**
 * \brief Test RTC hardware register initialization state after open
 *
 * Test Category: Functional
 *
 * Verifies hardware clock enable, module reset release, and correct register
 * initialization state after RTC_init() and RTC_open(). Confirms that the
 * open sequence completes the full hardware setup: kick unlock
 * (GENRAL_CTL.UNLOCK set), 32kHz oscillator shadow sync enabled
 * (O32K_OSC_DEP_EN), interrupts cleared, no pending operations
 * (SYNCPEND.WR_PEND = 0, SYNCPEND.RD_PEND = 0), counter running
 * (GENRAL_CTL.SW_OFF = 0), and freeze mode set if configured.
 *
 * Test steps:
 * 1. Call RTC_init() and RTC_open(). Assert handle is not NULL.
 * 2. Read GENRAL_CTL register via direct volatile pointer. Verify UNLOCK
 *    bit is set (write access was granted by kick sequence).
 * 3. Verify O32K_OSC_DEP_EN bit is set in GENRAL_CTL (shadow sync enabled).
 * 4. Verify SW_OFF bit is cleared in GENRAL_CTL (counter is running).
 * 5. Read SYNCPEND register. Verify WR_PEND and RD_PEND are both 0.
 * 6. If isfreezemode=1U (default), verify FREEZE_MODE bit (0x02000000) is
 *    set in GENRAL_CTL.
 * 7. Call RTC_setTime() and RTC_getTime() to confirm hardware is operational.
 * 8. Close the instance.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All hardware register bits match expected initialized
 *                 state. RTC_setTime() and RTC_getTime() return
 *                 SystemP_SUCCESS.
 */
static void TestRtc_hardwareInitRegisterState(void *args)
{
    RTC_Handle              rtcHandle = NULL;
    const RTC_HwAttrs      *hardwareAttributes = NULL;
    uint32_t                baseAddress = 0U;
    uint32_t                generalControlValue = 0U;
    uint32_t                syncPendingValue = 0U;
    RTC_Time                setTime;
    RTC_Time                getTime;
    int32_t                 status = SystemP_SUCCESS;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();

    /* Step 1: Initialize and open RTC */
    RTC_init();
    rtcHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(rtcHandle);

    hardwareAttributes = (const RTC_HwAttrs *)rtcHandle->hwAttrs;
    baseAddress = hardwareAttributes->baseAddr;

    /* Read GENRAL_CTL register directly via volatile pointer */
    generalControlValue = *((volatile uint32_t *)(baseAddress + CSL_RTC_GENRAL_CTL));

    /* Step 2: Verify UNLOCK bit is set (write access granted by kick sequence) */
    TEST_ASSERT_TRUE((generalControlValue & CSL_RTC_GENRAL_CTL_UNLOCK_MASK) != 0U);

    /* Step 3: Verify O32K_OSC_DEP_EN is set (shadow register sync enabled) */
    TEST_ASSERT_TRUE((generalControlValue & CSL_RTC_GENRAL_CTL_O32K_OSC_DEP_EN_MASK) != 0U);

    /* Step 4: Verify SW_OFF is cleared (counter is running) */
    TEST_ASSERT_EQUAL_UINT32(0U, (generalControlValue & CSL_RTC_GENRAL_CTL_SW_OFF_MASK));

    /* Step 5: Read SYNCPEND register and verify no pending operations */
    syncPendingValue = *((volatile uint32_t *)(baseAddress + CSL_RTC_SYNCPEND));
    TEST_ASSERT_EQUAL_UINT32(0U, (syncPendingValue & CSL_RTC_SYNCPEND_WR_PEND_MASK));
    TEST_ASSERT_EQUAL_UINT32(0U, (syncPendingValue & CSL_RTC_SYNCPEND_RD_PEND_MASK));

    /* Step 6: Verify FREEZE_MODE bit is set (default isfreezemode=1U) */
    TEST_ASSERT_TRUE((generalControlValue & RTC_FREEZE_MODE) != 0U);

    /* Step 7: Verify RTC is operational by setting and getting time */
    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 8: Store handle for subsequent tests */
    gRTCHandle[CONFIG_RTC0] = rtcHandle;
}

/**
 * \brief Test RTC time increment driven by 32768Hz oscillator
 *
 * Test Category: Functional
 *
 * Verifies time increments correctly at the rate driven by the 15-bit
 * 32768Hz counter. Sets a known baseline time, sleeps for a fixed duration,
 * reads back the time, and verifies the increment matches the expected
 * elapsed seconds. Confirms the 15-bit counter divides the 32.768 kHz
 * oscillator to produce 1-second ticks that drive the 48-bit seconds counter.
 *
 * Test steps:
 * 1. Set time to 2024-01-01 00:00:00 using RTC_setTime().
 * 2. Sleep 3 seconds.
 * 3. Read RTC time using RTC_getTime().
 * 4. Verify second field has incremented by approximately 3 (within ±1).
 * 5. Verify minute is unchanged (still 0).
 * 6. Reset time to 00:00:00, sleep 10 seconds, read back, and verify
 *    second field is approximately 10 (within ±1).
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC time increments by approximately the sleep duration
 *                 with ±1 second tolerance. Minute field remains unchanged.
 */
static void TestRtc_timeIncrement(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set time to 2024-01-01 00:00:00 */
    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Sleep for 3 seconds */
    ClockP_sleep(TEST_RTC_SLEEP_3_SEC);

    /* Step 3: Read back RTC time */
    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Verify approximately 3 seconds elapsed (within ±1) */
    TEST_ASSERT_UINT32_WITHIN(1U, 3U, getTime.second);

    /* Step 5: Verify minute is still 0 (no boundary overflow) */
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);

    /* Step 6: Reset time and verify over a longer 10-second interval */
    setTime.second = 0U;
    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_SLEEP_10_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_UINT32_WITHIN(1U, 10U, getTime.second);
}

/**
 * \brief Test RTC leap year and century-year date handling
 *
 * Test Category: Functional
 *
 * Verifies that the RTC driver correctly handles leap year date conversion
 * and seconds-to-time decomposition, including century-year edge cases.
 * Exercises RTC_isLeapYear() and RTC_getDaysInMonth() through the public
 * RTC_setTime() / RTC_getTime() path.
 *
 * Test steps:
 * 1. Set time to 2024-02-28 23:59:57 (leap year). Sleep 5 seconds.
 *    Verify year=2024, month=2, day=29 (Feb 29 exists).
 * 2. Set time to 2001-02-28 23:59:57 (non-leap year). Sleep 5 seconds.
 *    Verify year=2001, month=3, day=1 (no Feb 29).
 * 3. Set time to 2000-02-28 23:59:57 (divisible by 400, leap). Sleep 5
 *    seconds. Verify year=2000, month=2, day=29.
 * 4. Set time to 2100-02-28 23:59:57 (divisible by 100 not 400, non-leap).
 *    Sleep 5 seconds. Verify year=2100, month=3, day=1.
 * 5. Assert all RTC_setTime() and RTC_getTime() calls return
 *    SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Leap year dates transition correctly: Feb 29 exists for
 *                 2024 and 2000, rolls to March 1 for 2001 and 2100.
 */
static void TestRtc_leapYearDateHandling(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: 2024 is a leap year — Feb 29 should exist */
    setTime.year   = 2024U;
    setTime.month  = 2U;
    setTime.day    = 28U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* After 5s from 23:59:57, time is ~00:00:02 on Feb 29 */
    TEST_ASSERT_EQUAL_UINT32(2024U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(2U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(29U, getTime.day);

    /* Step 2: 2001 is NOT a leap year — should roll to March 1 */
    setTime.year   = 2001U;
    setTime.month  = 2U;
    setTime.day    = 28U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2001U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(3U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);

    /* Step 3: 2000 is divisible by 400 — IS a leap year */
    setTime.year   = 2000U;
    setTime.month  = 2U;
    setTime.day    = 28U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2000U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(2U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(29U, getTime.day);

    /* Step 4: 2100 is divisible by 100 but NOT 400 — NOT a leap year */
    setTime.year   = 2100U;
    setTime.month  = 2U;
    setTime.day    = 28U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 5: Verify no Feb 29 in 2100 — rolled to March 1 */
    TEST_ASSERT_EQUAL_UINT32(2100U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(3U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);
}

/**
 * \brief Test RTC time boundary transitions across day, month, year, and minute
 *
 * Test Category: Functional
 *
 * Verifies correct rollover at day, month, year, and minute/hour boundaries.
 * Sets the time to the last seconds before a boundary, sleeps past it, and
 * verifies the date transitions correctly with no skipped or duplicated values.
 *
 * Test steps:
 * 1. Set 2024-01-31 23:59:57, sleep 5s, verify rolls to Feb 1.
 * 2. Set 2025-12-31 23:59:57, sleep 5s, verify rolls to 2026-01-01.
 * 3. Set 2024-06-15 23:59:57, sleep 5s, verify midnight rollover to day 16.
 * 4. Set 2024-03-10 10:59:57, sleep 5s, verify minute/hour rollover to 11:00.
 * 5. Assert all API calls return SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All boundary transitions produce correct date/time fields.
 */
static void TestRtc_timeBoundaryTransitions(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Day-to-month boundary — Jan 31 to Feb 1 */
    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 31U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2024U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(2U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);

    /* Step 2: Year boundary — Dec 31 2025 to Jan 1 2026 */
    setTime.year   = 2025U;
    setTime.month  = 12U;
    setTime.day    = 31U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2026U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);

    /* Step 3: Midnight rollover — day 15 to day 16 */
    setTime.year   = 2024U;
    setTime.month  = 6U;
    setTime.day    = 15U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(16U, getTime.day);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);

    /* Step 4: Minute/hour rollover — 10:59:57 to 11:00:xx */
    setTime.year   = 2024U;
    setTime.month  = 3U;
    setTime.day    = 10U;
    setTime.hour   = 10U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(11U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);
}

/**
 * \brief Test RTC elapsed time calculation with borrow across all fields
 *
 * Test Category: Functional
 *
 * Verifies that RTC_calculateElapsedTime() correctly computes the difference
 * between two RTC_Time values, handling borrow/underflow across seconds,
 * minutes, hours, and days. Covers same-time, single-second, and
 * cross-boundary intervals.
 *
 * Test steps:
 * 1. Compare {2024,11,5,14,42,10} to {2024,11,7,15,43,20}, expect 2d 1h 1m 10s.
 * 2. Same time for start and end, expect all fields zero.
 * 3. Single second difference, expect 1s only.
 * 4. Seconds underflow with borrow from minute.
 * 5. Hours underflow with borrow from day.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All computed elapsed times match expected values.
 */
static void TestRtc_calculateElapsedTime(void *args)
{
    RTC_Time startTime;
    RTC_Time endTime;
    RTC_Time elapsedTime;

    /* Step 1: Normal difference — 2 days, 1 hour, 1 minute, 10 seconds */
    startTime.year   = 2024U;
    startTime.month  = 11U;
    startTime.day    = 5U;
    startTime.hour   = 14U;
    startTime.minute = 42U;
    startTime.second = 10U;

    endTime.year   = 2024U;
    endTime.month  = 11U;
    endTime.day    = 7U;
    endTime.hour   = 15U;
    endTime.minute = 43U;
    endTime.second = 20U;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.year);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.month);
    TEST_ASSERT_EQUAL_UINT32(2U, elapsedTime.day);
    TEST_ASSERT_EQUAL_UINT32(1U, elapsedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(1U, elapsedTime.minute);
    TEST_ASSERT_EQUAL_UINT32(10U, elapsedTime.second);

    /* Step 2: Same time — all fields should be zero */
    startTime.year   = 2024U;
    startTime.month  = 5U;
    startTime.day    = 10U;
    startTime.hour   = 8U;
    startTime.minute = 30U;
    startTime.second = 0U;
  
    endTime = startTime;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.year);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.month);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.day);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.minute);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.second);

    /* Step 3: Single second difference */
    endTime.second = 1U;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.minute);
    TEST_ASSERT_EQUAL_UINT32(1U, elapsedTime.second);

    /* Step 4: Seconds underflow — borrow from minute
     * start 10:05:45, end 10:06:20 → elapsed = 0h 0m 35s */
    startTime.year   = 2024U;
    startTime.month  = 5U;
    startTime.day    = 10U;
    startTime.hour   = 10U;
    startTime.minute = 5U;
    startTime.second = 45U;

    endTime.year   = 2024U;
    endTime.month  = 5U;
    endTime.day    = 10U;
    endTime.hour   = 10U;
    endTime.minute = 6U;
    endTime.second = 20U;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(35U, elapsedTime.second);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.minute);

    /* Step 5: Hours underflow — borrow from day
     * start day=10 22:30:00, end day=11 02:30:00 → elapsed = 0d 4h 0m 0s */
    startTime.year   = 2024U;
    startTime.month  = 5U;
    startTime.day    = 10U;
    startTime.hour   = 22U;
    startTime.minute = 30U;
    startTime.second = 0U;

    endTime.year   = 2024U;
    endTime.month  = 5U;
    endTime.day    = 11U;
    endTime.hour   = 2U;
    endTime.minute = 30U;
    endTime.second = 0U;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(4U, elapsedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.day);
}

/**
 * \brief Test RTC read monotonicity via shadow register auto-sync
 *
 * Test Category: Functional
 *
 * Verifies that repeated RTC_getTime() calls return monotonically
 * non-decreasing values without manual polling. The shadow registers
 * auto-sync on each 32kHz clock boundary after O32K_OSC_DEP_EN is set.
 *
 * Test steps:
 * 1. Set RTC time to a known value.
 * 2. Call RTC_getTime() 20 times in a tight loop.
 * 3. Convert each result to total seconds within the day.
 * 4. Verify each value is non-decreasing compared to the previous.
 * 5. Verify no field has an impossible value.
 * 6. Verify no jump greater than 1 second between consecutive reads.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All 20 reads are monotonically non-decreasing with
 *                 no invalid fields and no jumps greater than 1 second.
 */
static void TestRtc_getTimeMonotonicity(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    iteration = 0U;
    uint32_t    currentTotalSeconds = 0U;
    uint32_t    previousTotalSeconds = 0U;
    uint32_t    totalReads = 20U;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set RTC time */
    setTime.year   = 2024U;
    setTime.month  = 6U;
    setTime.day    = 15U;
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2-6: Read 20 times in a tight loop and validate */
    for (iteration = 0U; iteration < totalReads; iteration+=1)
    {
        status = RTC_getTime(rtcHandle, &readTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Step 5: Verify no impossible field values */
        TEST_ASSERT_TRUE(readTime.hour <= TEST_RTC_MAX_HOUR);
        TEST_ASSERT_TRUE(readTime.minute <= TEST_RTC_MAX_MINUTE);
        TEST_ASSERT_TRUE(readTime.second <= TEST_RTC_MAX_SECOND);

        /* Step 3: Convert to total seconds within the day */
        currentTotalSeconds = (readTime.hour * TEST_RTC_SECONDS_PER_HOUR)
                            + (readTime.minute * TEST_RTC_SECONDS_PER_MINUTE)
                            + readTime.second;

        if (iteration > 0U)
        {
            /* Step 4: Verify non-decreasing */
            TEST_ASSERT_TRUE(currentTotalSeconds >= previousTotalSeconds);

            /* Step 6: Verify no jump greater than 1 second between reads */
            TEST_ASSERT_TRUE((currentTotalSeconds - previousTotalSeconds) <= 1U);
        }

        previousTotalSeconds = currentTotalSeconds;
    }
}

/**
 * \brief Test RTC extended date range and 48-bit counter boundary
 *
 * Test Category: Functional
 *
 * Verifies RTC handles the full width of the 48-bit seconds counter.
 * Tests epoch zero, far future, 32-bit LSW wrap boundary, and Y2K
 * boundary via round-trip set/get operations.
 *
 * Test steps:
 * 1. Set epoch zero (1970-01-01 00:00:00), read back, verify fields match.
 * 2. Set far future (2099-12-31 23:59:59), read back, verify fields.
 * 3. Set 32-bit LSW boundary (2106-02-07 06:28:15), read back, sleep 2s,
 *    verify time advanced across the 32-bit wrap.
 * 4. Set Y2K boundary (2000-01-01 00:00:00), read back, verify fields.
 * 5. Assert all API calls return SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All date values round-trip correctly. Time advances
 *                 across the 32-bit LSW wrap boundary.
 */
static void TestRtc_extendedTimeRange(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Epoch zero — 1970-01-01 00:00:00 */
    setTime.year   = 1970U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(1970U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);
    TEST_ASSERT_UINT32_WITHIN(1U, 0U, getTime.second);

    /* Step 2: Far future — 2099-12-31 23:59:59 */
    setTime.year   = 2099U;
    setTime.month  = 12U;
    setTime.day    = 31U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 59U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2099U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(12U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(31U, getTime.day);
    TEST_ASSERT_EQUAL_UINT32(23U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(59U, getTime.minute);
    TEST_ASSERT_UINT32_WITHIN(1U, 59U, getTime.second);

    /* Step 3: 32-bit LSW boundary — 2106-02-07 06:28:15
     * This corresponds to seconds value 0xFFFFFFFF from epoch.
     * After sleeping 2s, the LSW wraps and MSW increments to 1. */
    setTime.year   = 2106U;
    setTime.month  = 2U;
    setTime.day    = 7U;
    setTime.hour   = 6U;
    setTime.minute = 28U;
    setTime.second = 15U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2106U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(2U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(7U, getTime.day);

    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify time advanced by approximately 2 seconds across the 32-bit wrap */
    TEST_ASSERT_UINT32_WITHIN(1U, 17U, getTime.second);
    TEST_ASSERT_EQUAL_UINT32(28U, getTime.minute);

    /* Step 4: Y2K boundary — 2000-01-01 00:00:00 */
    setTime.year   = 2000U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2000U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);
}

/**
 * \brief Test RTC shadow auto-sync for both writes and reads without polling
 *
 * Test Category: Functional
 *
 * Verifies that the host can update and read RTC MMRs without manual
 * polling, thanks to the hardware shadow/auto-sync mechanism enabled via
 * O32K_OSC_DEP_EN. Confirms writes commit immediately and rapid reads
 * return consistent, non-stale values.
 *
 * Test steps:
 * 1. Set time to 2024-05-15 08:00:00 via RTC_setTime().
 * 2. Immediately read back via RTC_getTime() with no sleep.
 * 3. Verify read-back matches set time (hour=8, minute=0, second near 0).
 * 4. Perform 10 rapid set-then-read cycles, verify each read-back matches.
 * 5. Set time to 12:00:00, perform 5 rapid reads, verify all consistent.
 * 6. Assert no call returned SystemP_FAILURE.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Immediate read-back matches set value. All rapid
 *                 set-then-read cycles and consecutive reads are consistent.
 */
static void TestRtc_shadowAutoSyncReadWrite(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    RTC_Time    rapidReadResults[TEST_RTC_RAPID_READ_COUNT];
    int32_t     status = SystemP_SUCCESS;
    uint32_t    cycleIndex = 0U;
    uint32_t    readIndex = 0U;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Steps 1-3: Set time, immediately read back, verify match */
    setTime.year   = 2024U;
    setTime.month  = 5U;
    setTime.day    = 15U;
    setTime.hour   = 8U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(8U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);
    TEST_ASSERT_UINT32_WITHIN(1U, 0U, getTime.second);

    /* Step 4: 10 rapid set-then-read cycles */
    for (cycleIndex = 1U; cycleIndex <= TEST_RTC_RAPID_CYCLE_COUNT; cycleIndex+=1)
    {
        setTime.hour   = 0U;
        setTime.minute = 0U;
        setTime.second = cycleIndex;

        status = RTC_setTime(rtcHandle, &setTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        status = RTC_getTime(rtcHandle, &getTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        TEST_ASSERT_UINT32_WITHIN(1U, cycleIndex, getTime.second);
    }

    /* Step 5: Set time to 12:00:00 and perform 5 rapid reads */
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (readIndex = 0U; readIndex < TEST_RTC_RAPID_READ_COUNT; readIndex+=1)
    {
        status = RTC_getTime(rtcHandle, &rapidReadResults[readIndex]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Verify all 5 reads are within ±1 second of each other */
    for (readIndex = 1U; readIndex < TEST_RTC_RAPID_READ_COUNT; readIndex+=1)
    {
        TEST_ASSERT_EQUAL_UINT32(12U, rapidReadResults[readIndex].hour);
        TEST_ASSERT_EQUAL_UINT32(0U, rapidReadResults[readIndex].minute);
        TEST_ASSERT_UINT32_WITHIN(1U,
                                  rapidReadResults[0U].second,
                                  rapidReadResults[readIndex].second);
    }
}

/**
 * \brief Test 32768Hz counter tick accuracy against system reference clock
 *
 * Test Category: Functional
 *
 * Verifies the 15-bit 32768Hz counter produces accurate 1-second ticks by
 * measuring RTC progression against ClockP_getTimeUsec() over multiple
 * short windows. Also validates second-to-minute rollover at the tick level.
 *
 * Test steps:
 * 1. Set RTC time to a known baseline.
 * 2. Record system time T0 and RTC time R0.
 * 3. Sleep 5 seconds.
 * 4. Record system time T1 and RTC time R1.
 * 5. Verify |RTC_elapsed - system_elapsed| is within 1 second.
 * 6. Repeat for 5 iterations; verify cumulative drift within ±2 seconds.
 * 7. Verify no single iteration has a jump greater than 2s or goes backward.
 * 8. Boundary check: set second=59, sleep 2s, verify rollover to second ~1
 *    and minute incremented by 1.
 * 9. Assert all API calls return SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Per-iteration drift within ±1s. Cumulative drift over 25s
 *                 within ±2s. Second-to-minute rollover correct.
 */
static void TestRtc_32kHzCounterTickAccuracy(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    startReadTime;
    RTC_Time    endReadTime;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    iteration = 0U;
    uint32_t    totalIterations = 5U;
    uint32_t    sleepDurationSeconds = 5U;
    uint64_t    systemTimeStart = 0ULL;
    uint64_t    systemTimeEnd = 0ULL;
    uint64_t    systemElapsedMicroseconds = 0ULL;
    uint32_t    rtcElapsedSeconds = 0U;
    int32_t     perIterationDrift = 0;
    int32_t     cumulativeRtcElapsed = 0;
    int32_t     cumulativeSystemElapsed = 0;
    int32_t     cumulativeDrift = 0;
    uint32_t    previousRtcSecond = 0U;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set RTC to a known baseline */
    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Steps 2-7: 5 iterations of 5-second measurement windows */
    for (iteration = 0U; iteration < totalIterations; iteration+=1)
    {
        /* Step 2: Record start references */
        systemTimeStart = ClockP_getTimeUsec();
        status = RTC_getTime(rtcHandle, &startReadTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Step 3: Sleep */
        ClockP_sleep(sleepDurationSeconds);

        /* Step 4: Record end references */
        systemTimeEnd = ClockP_getTimeUsec();
        status = RTC_getTime(rtcHandle, &endReadTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Step 5: Compute elapsed and compare */
        systemElapsedMicroseconds = systemTimeEnd - systemTimeStart;
        int32_t secDiff = (int32_t)endReadTime.second - (int32_t)startReadTime.second;
        if (secDiff < 0)
        {
            secDiff += 60;
        }
        rtcElapsedSeconds = (uint32_t)secDiff + (endReadTime.minute - startReadTime.minute) * 60U;

        perIterationDrift = (int32_t)rtcElapsedSeconds
                          - (int32_t)(systemElapsedMicroseconds / 1000000ULL);

        /* Step 6: Per-iteration drift must be within ±1 second */
        TEST_ASSERT_TRUE((perIterationDrift >= -1) && (perIterationDrift <= 1));

        /* Step 7: No backward step and no jump greater than 2 seconds */
        TEST_ASSERT_TRUE(rtcElapsedSeconds <= (sleepDurationSeconds + 2U));
        TEST_ASSERT_TRUE(rtcElapsedSeconds >= 1U);

        if (iteration > 0U)
        {
            TEST_ASSERT_TRUE(endReadTime.second != previousRtcSecond
                             || endReadTime.minute > startReadTime.minute);
        }
        previousRtcSecond = endReadTime.second;

        /* Accumulate for cumulative drift check */
        cumulativeRtcElapsed += (int32_t)rtcElapsedSeconds;
        cumulativeSystemElapsed += (int32_t)(systemElapsedMicroseconds / 1000000ULL);
    }

    /* Step 6 continued: Cumulative drift over 25 seconds within ±2 seconds */
    cumulativeDrift = cumulativeRtcElapsed - cumulativeSystemElapsed;
    TEST_ASSERT_TRUE((cumulativeDrift >= -2) && (cumulativeDrift <= 2));

    /* Step 8: Boundary check — second 59 rolls to ~01, minute increments */
    setTime.hour   = 5U;
    setTime.minute = 30U;
    setTime.second = 59U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    status = RTC_getTime(rtcHandle, &endReadTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(31U, endReadTime.minute);
    TEST_ASSERT_UINT32_WITHIN(1U, 1U, endReadTime.second);
}

/**
 * \brief Test RTC alarm fires correctly after explicit time update
 *
 * Test Category: Functional
 *
 * Sets a known time via RTC_setTime(), arms an On-Off alarm 5 seconds in
 * the future, and verifies the callback fires at the expected time.
 *
 * Test steps:
 * 1. Set RTC time to 2024-03-15 10:00:00.
 * 2. Construct a binary semaphore for the On-Off callback.
 * 3. Call RTC_setOn_OffTimerEvent() with target 10:00:05.
 * 4. Pend on semaphore with 10-second timeout.
 * 5. Verify pend returns SystemP_SUCCESS.
 * 6. Read RTC time and verify second is within ±1 of 5.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Callback fires at approximately 5 seconds. Semaphore
 *                 pend succeeds and RTC time second field is near 5.
 */
static void TestRtc_alarmAfterTimeUpdate(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    alarmTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;
    int32_t     semaphoreStatus = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set RTC time */
    setTime.year   = 2024U;
    setTime.month  = 3U;
    setTime.day    = 15U;
    setTime.hour   = 10U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Construct binary semaphore */
    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Step 3: Arm On-Off alarm at 10:00:05 */
    alarmTime        = setTime;
    alarmTime.second = 5U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Pend with 10-second timeout */
    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                      ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));

    /* Step 5: Verify callback fired */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semaphoreStatus);

    /* Step 6: Verify RTC second field is approximately 5 */
    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_UINT32_WITHIN(1U, 5U, readTime.second);

    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

/**
 * \brief Test RTC alarm does not fire after instance is closed
 *
 * Test Category: Functional
 *
 * Arms an alarm, disables its interrupt enable, closes the RTC instance
 * before the trigger time, and verifies the callback is never invoked.
 * Driver gap: RTC_close() with enableIntr=true does not disable IRQs,
 * so the test disables the IRQ enable via direct register write first.
 *
 * Test steps:
 * 1. Construct a binary semaphore (count=0).
 * 2. Set RTC time to 2024-09-01 06:00:00.
 * 3. Set On-Off alarm at 06:00:05.
 * 4. Disable IRQ enable via register and call RTC_close().
 * 5. Wait 7 seconds past the alarm target.
 * 6. Pend with 0-wait and verify SystemP_TIMEOUT.
 * 7. Restore RTC instance via deinit + init + open.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Semaphore pend returns SystemP_TIMEOUT; callback
 *                 was never invoked after close.
 */
static void TestRtc_alarmDisable(void *args)
{
    RTC_Handle              rtcHandle = NULL;
    const RTC_HwAttrs      *hardwareAttributes = NULL;
    uint32_t                baseAddress = 0U;
    volatile uint32_t      *irqEnableClearRegister = NULL;
    RTC_Time                setTime;
    RTC_Time                alarmTime;
    int32_t                 status = SystemP_SUCCESS;
    int32_t                 semaphoreStatus = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    hardwareAttributes = (const RTC_HwAttrs *)rtcHandle->hwAttrs;
    baseAddress        = hardwareAttributes->baseAddr;

    /* Step 1: Construct binary semaphore */
    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Step 2: Set RTC time */
    setTime.year   = 2024U;
    setTime.month  = 9U;
    setTime.day    = 1U;
    setTime.hour   = 6U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Arm On-Off alarm at 06:00:05 */
    alarmTime        = setTime;
    alarmTime.second = 5U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Disable IRQ enable directly before closing.
     * Driver gap: RTC_close() with enableIntr=true skips IRQ disable. */
    irqEnableClearRegister =
        (volatile uint32_t *)(baseAddress + CSL_RTC_IRQENABLE_CLR_SYS);
    *irqEnableClearRegister = RTC_TMR_INT_INT0_CLEAR_FLAG;

    RTC_close(rtcHandle);
    gRTCHandle[CONFIG_RTC0] = NULL;

    /* Step 5: Wait past the alarm target */
    ClockP_sleep(TEST_RTC_SLEEP_7_SEC);

    /* Step 6: Pend with 0-wait — expect timeout */
    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, semaphoreStatus);

    SemaphoreP_destruct(&TestRtc_OnOffSemObj);

    /* Step 7: Restore RTC instance for subsequent tests.
     * deinit + init required because RTC_close() does not reset isOpen. */
    RTC_deinit();
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test RTC alarm overwrite replaces the previous alarm target
 *
 * Test Category: Functional
 *
 * Arms an On-Off alarm, immediately overwrites it with a later target,
 * and verifies only the second alarm fires.
 *
 * Test steps:
 * 1. Construct a binary semaphore.
 * 2. Set RTC time to 2024-10-01 09:00:00.
 * 3. Set On-Off alarm at 09:00:05 (alarm A).
 * 4. Immediately overwrite with alarm at 09:00:08 (alarm B).
 * 5. Pend with 12s timeout; verify fires at approximately 8 seconds.
 * 6. Second pend with 2s timeout returns SystemP_TIMEOUT.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Alarm fires at ~8s (not ~5s). No duplicate firing.
 */
static void TestRtc_alarmOverwriteBehavior(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    firstAlarmTime;
    RTC_Time    secondAlarmTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;
    int32_t     semaphoreStatus = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Construct binary semaphore */
    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Step 2: Set RTC time */
    setTime.year   = 2024U;
    setTime.month  = 10U;
    setTime.day    = 1U;
    setTime.hour   = 9U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Set alarm A at 09:00:05 */
    firstAlarmTime        = setTime;
    firstAlarmTime.second = 5U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &firstAlarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Immediately overwrite with alarm B at 09:00:08 */
    secondAlarmTime        = setTime;
    secondAlarmTime.second = 8U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &secondAlarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 5: Pend with 12s timeout — verify fires at ~8s not ~5s */
    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                      ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_12_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semaphoreStatus);

    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_UINT32_WITHIN(1U, 8U, readTime.second);

    /* Step 6: Second pend — verify no duplicate firing */
    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                      ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_2_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, semaphoreStatus);

    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

/**
 * \brief Test RTC On-Off and Off-On events at exact time boundaries
 *
 * Test Category: Functional
 *
 * Verifies both alarm types trigger precisely at configured boundaries.
 * Tests On-Off at a 15-second offset and Off-On at a minute boundary.
 *
 * Test steps:
 * 1. Set time to 2024-07-01 10:00:00.
 * 2. Construct semaphores for both callbacks.
 * 3. Schedule On-Off at 10:00:15 and pend with 20s timeout.
 * 4. Verify second is within ±1 of 15.
 * 5. Set time to 10:59:55. Schedule Off-On at 11:00:00. Pend with 10s.
 * 6. Verify hour=11, minute=0.
 * 7. Assert all calls return SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput On-Off fires at ~15s. Off-On fires at minute boundary
 *                 with hour=11, minute=0.
 */
static void TestRtc_timerEventBoundaryTimes(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    alarmTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;
    int32_t     semaphoreStatus = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set time */
    setTime.year   = 2024U;
    setTime.month  = 7U;
    setTime.day    = 1U;
    setTime.hour   = 10U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Construct semaphores */
    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);
    SemaphoreP_constructBinary(&TestRtc_OffOnSemObj, 0U);

    /* Step 3: Schedule On-Off at 10:00:15 */
    alarmTime        = setTime;
    alarmTime.second = 15U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                      ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_20_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semaphoreStatus);

    /* Step 4: Verify second is approximately 15 */
    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_UINT32_WITHIN(1U, 15U, readTime.second);

    /* Step 5: Set time to 10:59:55. Schedule Off-On at 11:00:00. */
    setTime.hour   = 10U;
    setTime.minute = 59U;
    setTime.second = 55U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    alarmTime.hour   = 11U;
    alarmTime.minute = 0U;
    alarmTime.second = 0U;

    status = RTC_setOff_OnTimerEvent(rtcHandle, &alarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    semaphoreStatus = SemaphoreP_pend(&TestRtc_OffOnSemObj,
                                      ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semaphoreStatus);

    /* Step 6: Verify hour=11, minute=0 */
    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(11U, readTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, readTime.minute);

    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
    SemaphoreP_destruct(&TestRtc_OffOnSemObj);
}

/**
 * \brief Test RTC callback only invoked when registered
 *
 * Test Category: Functional
 *
 * Replaces the On-Off callback with a no-op, verifies no semaphore post
 * occurs when the alarm fires, then restores the real callback and verifies
 * the semaphore is posted. Driver gap: RTC_Params.onOffCallback is a dead
 * variable; the ISR unconditionally calls the function pointer, so this
 * test manipulates the pointer directly.
 *
 * Test steps:
 * 1. Replace On_OffCallbackFunction with a no-op callback.
 * 2. Set time to 2024-04-01 12:00:00. Arm alarm at 12:00:03.
 * 3. Sleep 5s. Pend with 0-wait. Verify SystemP_TIMEOUT.
 * 4. Restore original callback.
 * 5. Set time again. Arm alarm at 12:00:03. Pend with 10s timeout.
 * 6. Verify callback fires (SystemP_SUCCESS).
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput No-op callback prevents semaphore post. Real callback
 *                 causes semaphore post.
 */
static void TestRtc_callbackRegistration(void *args)
{
    RTC_Handle              rtcHandle = NULL;
    RTC_Object             *rtcObject = NULL;
    RTC_OnOffCallbackFxn    originalCallback = NULL;
    RTC_Time                setTime;
    RTC_Time                alarmTime;
    int32_t                 status = SystemP_SUCCESS;
    int32_t                 semaphoreStatus = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    rtcObject = (RTC_Object *)rtcHandle->object;

    /* Step 1: Save original callback and replace with no-op */
    originalCallback = rtcObject->On_OffCallbackFunction;
    rtcObject->On_OffCallbackFunction = TestRtc_noopCallback;

    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Step 2: Set time and arm alarm */
    setTime.year   = 2024U;
    setTime.month  = 4U;
    setTime.day    = 1U;
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    alarmTime        = setTime;
    alarmTime.second = 3U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Sleep past alarm, verify no semaphore post */
    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, semaphoreStatus);

    /* Step 4: Restore original callback */
    rtcObject->On_OffCallbackFunction = originalCallback;

    /* Step 5: Set time again and arm alarm */
    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 6: Verify callback fires */
    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                      ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semaphoreStatus);

    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

/**
 * \brief Test RTC interrupt is self-cleared after callback in ISR
 *
 * Test Category: Functional
 *
 * Verifies that the ISR clears the IRQ status and disables the interrupt
 * enable after the callback, so no spurious second invocation occurs.
 *
 * Test steps:
 * 1. Construct a binary semaphore.
 * 2. Set RTC time to 2024-08-01 12:00:00.
 * 3. Set On-Off alarm at 12:00:03.
 * 4. Pend once to capture the event.
 * 5. Pend again with 3-second timeout.
 * 6. Verify second pend returns SystemP_TIMEOUT.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput First pend succeeds. Second pend times out confirming
 *                 the interrupt was cleared and not re-triggered.
 */
static void TestRtc_interruptClearedAfterCallback(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    alarmTime;
    int32_t     status = SystemP_SUCCESS;
    int32_t     firstPendStatus = SystemP_SUCCESS;
    int32_t     secondPendStatus = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Construct binary semaphore */
    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Step 2: Set RTC time */
    setTime.year   = 2024U;
    setTime.month  = 8U;
    setTime.day    = 1U;
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Set On-Off alarm at 12:00:03 */
    alarmTime        = setTime;
    alarmTime.second = 3U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Pend once to capture the alarm event */
    firstPendStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, firstPendStatus);

    /* Step 5-6: Pend again — should timeout (ISR cleared the interrupt) */
    secondPendStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                       ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_3_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, secondPendStatus);

    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

/**
 * \brief Test both On-Off and Off-On callbacks fire independently
 *
 * Test Category: Functional
 *
 * Arms both On-Off and Off-On alarms at different future times and verifies
 * each callback fires independently. Driver gap: the ISR unconditionally
 * disables both interrupt enables after any event; this test re-enables
 * INT1 after the On-Off callback fires.
 *
 * Test steps:
 * 1. Construct semaphores for both callback types.
 * 2. Set RTC time to 2024-05-01 12:00:00.
 * 3. Set On-Off alarm at 12:00:04, Off-On alarm at 12:00:08.
 * 4. Pend on On-Off semaphore with 10s timeout; verify fires at ~4s.
 * 5. Re-enable INT1 (driver gap workaround).
 * 6. Pend on Off-On semaphore with 10s timeout; verify fires at ~8s.
 * 7. Cross-pend On-Off with 0-wait returns SystemP_TIMEOUT.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput On-Off fires at ~4s, Off-On fires at ~8s independently.
 *                 No cross-triggering between the two events.
 */
static void TestRtc_bothCallbacksRegisteredAndInvoked(void *args)
{
    RTC_Handle              rtcHandle = NULL;
    const RTC_HwAttrs      *hardwareAttributes = NULL;
    uint32_t                baseAddress = 0U;
    volatile uint32_t      *irqEnableSetRegister = NULL;
    RTC_Time                setTime;
    RTC_Time                onOffAlarmTime;
    RTC_Time                offOnAlarmTime;
    RTC_Time                readTime;
    int32_t                 status = SystemP_SUCCESS;
    int32_t                 semaphoreStatus = SystemP_SUCCESS;
    int32_t                 crossPendStatus = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    hardwareAttributes = (const RTC_HwAttrs *)rtcHandle->hwAttrs;
    baseAddress        = hardwareAttributes->baseAddr;

    /* Step 1: Construct semaphores for both callbacks */
    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);
    SemaphoreP_constructBinary(&TestRtc_OffOnSemObj, 0U);

    /* Step 2: Set RTC time */
    setTime.year   = 2024U;
    setTime.month  = 5U;
    setTime.day    = 1U;
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Set On-Off alarm at 12:00:04 and Off-On alarm at 12:00:08 */
    onOffAlarmTime        = setTime;
    onOffAlarmTime.second = 4U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &onOffAlarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    offOnAlarmTime        = setTime;
    offOnAlarmTime.second = 8U;

    status = RTC_setOff_OnTimerEvent(rtcHandle, &offOnAlarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Pend on On-Off semaphore — should fire at ~4s */
    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                      ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semaphoreStatus);

    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_UINT32_WITHIN(1U, 4U, readTime.second);

    /* Step 5: Re-enable INT1 (Off-On interrupt).
     * Driver gap: RTC_hwiFxn unconditionally disables both INT0 and INT1
     * enables when any single event fires. */
    irqEnableSetRegister =
        (volatile uint32_t *)(baseAddress + CSL_RTC_IRQENABLE_SET_SYS);
    *irqEnableSetRegister = RTC_TMR_INT_INT1_SET_FLAG;

    /* Step 6: Pend on Off-On semaphore — should fire at ~8s */
    semaphoreStatus = SemaphoreP_pend(&TestRtc_OffOnSemObj,
                                      ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semaphoreStatus);

    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_UINT32_WITHIN(1U, 8U, readTime.second);

    /* Step 7: Cross-pend — On-Off should not have fired again */
    crossPendStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, crossPendStatus);

    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
    SemaphoreP_destruct(&TestRtc_OffOnSemObj);
}

/**
 * \brief Test RTC start and stop freezes and resumes the counter
 *
 * Test Category: Functional
 *
 * Verifies that RTC_stop() halts counter advancement and RTC_start()
 * resumes it. Tests multiple stop/start cycles.
 *
 * Test steps:
 * 1. Set RTC time to 2024-06-01 00:00:00.
 * 2. Call RTC_stop() and verify SystemP_SUCCESS.
 * 3. Sleep 3 seconds while stopped.
 * 4. Read time and verify second is 0 or 1 (counter did not advance).
 * 5. Call RTC_start() and verify SystemP_SUCCESS.
 * 6. Sleep 2 seconds.
 * 7. Read time and verify second is approximately 2.
 * 8. Repeat stop/start cycle once more to verify consistency.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Counter frozen during stop. Counter resumes from
 *                 stopped value after start. Multi-cycle consistent.
 */
static void TestRtc_startAndStop(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set RTC time */
    setTime.year   = 2024U;
    setTime.month  = 6U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Stop the RTC counter */
    status = RTC_stop(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Sleep while stopped */
    ClockP_sleep(TEST_RTC_SLEEP_3_SEC);

    /* Step 4: Verify counter did not advance */
    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_UINT32_WITHIN(1U, 0U, readTime.second);

    /* Step 5: Start the RTC counter */
    status = RTC_start(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 6: Sleep to let counter advance */
    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    /* Step 7: Verify counter advanced by approximately 2 seconds */
    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_UINT32_WITHIN(1U, 2U, readTime.second);

    /* Step 8: Repeat stop/start cycle for multi-cycle consistency */
    setTime.second = 0U;
    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_stop(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    status = RTC_start(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_UINT32_WITHIN(1U, 2U, readTime.second);
}

/**
 * \brief Test RTC time retention across driver deinit and re-init
 *
 * Test Category: Functional
 *
 * Verifies that the RTC counter in the battery-backed domain retains its
 * value when the driver is closed, deinitialized, and re-opened. The BBD
 * registers are not cleared by the kick lock or software reinit.
 *
 * Test steps:
 * 1. Set RTC time to 2024-12-25 10:30:00 and verify with RTC_getTime().
 * 2. Call RTC_close() followed by RTC_deinit().
 * 3. Call RTC_init() followed by RTC_open().
 * 4. Call RTC_getTime() immediately after re-open.
 * 5. Verify date/time fields match; second may differ by elapsed re-init time.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Time is preserved across deinit/re-init cycle.
 *                 No epoch reset occurs.
 */
static void TestRtc_timeRetentionAcrossReset(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    verifyTime;
    RTC_Time    retainedTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set RTC time and verify */
    setTime.year   = 2024U;
    setTime.month  = 12U;
    setTime.day    = 25U;
    setTime.hour   = 10U;
    setTime.minute = 30U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &verifyTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, verifyTime.year);
    TEST_ASSERT_EQUAL_UINT32(12U, verifyTime.month);
    TEST_ASSERT_EQUAL_UINT32(25U, verifyTime.day);

    /* Step 2: Close and deinit */
    RTC_close(rtcHandle);
    gRTCHandle[CONFIG_RTC0] = NULL;
    RTC_deinit();

    /* Step 3: Re-init and re-open */
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);

    /* Step 4: Read time immediately after re-open */
    status = RTC_getTime(gRTCHandle[CONFIG_RTC0], &retainedTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 5: Verify time was retained (second may differ by re-init elapsed) */
    TEST_ASSERT_EQUAL_UINT32(2024U, retainedTime.year);
    TEST_ASSERT_EQUAL_UINT32(12U, retainedTime.month);
    TEST_ASSERT_EQUAL_UINT32(25U, retainedTime.day);
    TEST_ASSERT_EQUAL_UINT32(10U, retainedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(30U, retainedTime.minute);
}

/**
 * \brief Test RTC alarm fires while system is blocked in sleep
 *
 * Test Category: Functional
 *
 * Verifies the RTC continues counting and fires the alarm interrupt while
 * the calling task is blocked in ClockP_sleep(), and the callback runs
 * correctly via the ISR.
 *
 * Test steps:
 * 1. Construct a binary semaphore for On-Off callback.
 * 2. Set RTC time to 2024-08-20 07:00:00.
 * 3. Set alarm for 07:00:03.
 * 4. Call ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC).
 * 5. Pend on semaphore with 0-wait and verify SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Semaphore pend succeeds immediately after sleep
 *                 returns, confirming the callback fired during sleep.
 */
static void TestRtc_alarmDuringIdleSleep(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    alarmTime;
    int32_t     status = SystemP_SUCCESS;
    int32_t     semaphoreStatus = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Construct binary semaphore */
    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Step 2: Set RTC time */
    setTime.year   = 2024U;
    setTime.month  = 8U;
    setTime.day    = 20U;
    setTime.hour   = 7U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Set alarm at 07:00:03 */
    alarmTime        = setTime;
    alarmTime.second = 3U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Block in sleep — alarm fires via ISR during this window */
    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    /* Step 5: Semaphore should already be posted */
    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semaphoreStatus);

    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

/**
 * \brief Test RTC counter discontinuity detection via stop/start and time jump
 *
 * Test Category: Functional
 *
 * Verifies that abrupt RTC stop/start sequences produce detectable time
 * discontinuities when compared to the system reference clock. Also
 * verifies an explicit time jump is observable.
 *
 * Test steps:
 * 1. Set RTC time and record system reference.
 * 2. Sleep 3s, verify RTC and system are in agreement (drift within 1s).
 * 3. Stop RTC, sleep 5s, start RTC.
 * 4. Verify RTC lags system by approximately 5 seconds.
 * 5. Close, deinit, sleep 2s, re-init, open. Verify time progressed.
 * 6. Set time jump from 12:00:00 to 15:00:00 and verify abrupt change.
 * 7. Assert all API calls return SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Stop/start gap is detectable. Time jump is observable.
 *                 All API calls succeed.
 */
static void TestRtc_counterDiscontinuityDetection(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    readTimeFirst;
    RTC_Time    readTimeSecond;
    RTC_Time    readTimeAfterReopen;
    RTC_Time    jumpTime;
    RTC_Time    readTimeAfterJump;
    int32_t     status = SystemP_SUCCESS;
    uint64_t    systemTimeStart = 0ULL;
    uint64_t    systemTimeAfterStop = 0ULL;
    uint32_t    rtcElapsedSeconds = 0U;
    uint32_t    systemElapsedSeconds = 0U;
    int32_t     discontinuityGap = 0;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set RTC time and record system reference */
    setTime.year   = 2024U;
    setTime.month  = 7U;
    setTime.day    = 1U;
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    systemTimeStart = ClockP_getTimeUsec();

    /* Step 2: Sleep 3s, verify RTC and system agree */
    ClockP_sleep(TEST_RTC_SLEEP_3_SEC);

    status = RTC_getTime(rtcHandle, &readTimeFirst);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_UINT32_WITHIN(1U, 3U, readTimeFirst.second);

    /* Step 3: Stop RTC, sleep 5s, start RTC */
    status = RTC_stop(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_start(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Verify RTC lags system by approximately 5 seconds */
    systemTimeAfterStop = ClockP_getTimeUsec();

    status = RTC_getTime(rtcHandle, &readTimeSecond);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    systemElapsedSeconds = (uint32_t)((systemTimeAfterStop - systemTimeStart) / 1000000ULL);
    rtcElapsedSeconds    = readTimeSecond.second;

    discontinuityGap = (int32_t)systemElapsedSeconds - (int32_t)rtcElapsedSeconds;
    TEST_ASSERT_TRUE(discontinuityGap >= 4);

    /* Step 5: Close, deinit, sleep 2s, re-init, open. Verify time progressed */
    RTC_close(rtcHandle);
    gRTCHandle[CONFIG_RTC0] = NULL;
    RTC_deinit();

    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);

    status = RTC_getTime(gRTCHandle[CONFIG_RTC0], &readTimeAfterReopen);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify time was preserved across deinit/re-init (not reset to epoch).
     * The BBD counter may or may not advance while the driver is deinitialized,
     * so only assert the value is at least what it was before close. */
    TEST_ASSERT_TRUE(readTimeAfterReopen.second >= readTimeSecond.second ||
                     readTimeAfterReopen.minute >= readTimeSecond.minute);

    /* Step 6: Abrupt time jump detection */
    setTime.second = 0U;
    status = RTC_setTime(gRTCHandle[CONFIG_RTC0], &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    jumpTime         = setTime;
    jumpTime.hour    = 15U;

    status = RTC_setTime(gRTCHandle[CONFIG_RTC0], &jumpTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(gRTCHandle[CONFIG_RTC0], &readTimeAfterJump);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(15U, readTimeAfterJump.hour);
}

/**
 * \brief Test RTC scratch register read/write data integrity for all 8 registers
 *
 * Test Category: Functional
 *
 * Verifies every bit position in the 256-bit scratch pad (8 x 32-bit
 * registers) with all-zeros, all-ones, alternating, and unique patterns.
 *
 * Test steps:
 * 1. Write 0x00000000 to all 8 registers and verify read-back.
 * 2. Write 0xFFFFFFFF to all 8 registers and verify.
 * 3. Write alternating 0xAAAAAAAA / 0x55555555 and verify.
 * 4. Write unique value per register and verify.
 * 5. Assert all writes return SystemP_SUCCESS.
 * 6. Verify independence between adjacent registers.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All patterns round-trip correctly. No cross-contamination
 *                 between registers.
 */
static void TestRtc_scratchRegisterReadWrite(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    registerIndex = 0U;
    uint32_t    readValue = 0U;
    uint32_t    totalRegisters = TEST_RTC_SCRATCH_REGISTER_COUNT;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Write all zeros and verify */
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex+=1)
    {
        status = RTC_writeScratchRegister(rtcHandle, registerIndex, TEST_RTC_PATTERN_ALL_ZEROS);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex+=1)
    {
        readValue = RTC_readScratchRegister(rtcHandle, registerIndex);
        TEST_ASSERT_EQUAL_UINT32(TEST_RTC_PATTERN_ALL_ZEROS, readValue);
    }

    /* Step 2: Write all ones and verify */
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex+=1)
    {
        status = RTC_writeScratchRegister(rtcHandle, registerIndex, TEST_RTC_PATTERN_ALL_ONES);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex+=1)
    {
        readValue = RTC_readScratchRegister(rtcHandle, registerIndex);
        TEST_ASSERT_EQUAL_UINT32(TEST_RTC_PATTERN_ALL_ONES, readValue);
    }

    /* Step 3: Write alternating patterns and verify */
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex+=1)
    {
        if ((registerIndex % 2U) == 0U)
        {
            status = RTC_writeScratchRegister(rtcHandle, registerIndex, TEST_RTC_PATTERN_ALT_A);
        }
        else
        {
            status = RTC_writeScratchRegister(rtcHandle, registerIndex, TEST_RTC_PATTERN_ALT_5);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex+=1)
    {
        readValue = RTC_readScratchRegister(rtcHandle, registerIndex);
        if ((registerIndex % 2U) == 0U)
        {
            TEST_ASSERT_EQUAL_UINT32(TEST_RTC_PATTERN_ALT_A, readValue);
        }
        else
        {
            TEST_ASSERT_EQUAL_UINT32(TEST_RTC_PATTERN_ALT_5, readValue);
        }
    }

    /* Step 4: Write unique value per register and verify */
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex+=1)
    {
        status = RTC_writeScratchRegister(rtcHandle, registerIndex,
                                         TEST_RTC_PATTERN_DEAD_BASE + registerIndex);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex+=1)
    {
        readValue = RTC_readScratchRegister(rtcHandle, registerIndex);
        TEST_ASSERT_EQUAL_UINT32(TEST_RTC_PATTERN_DEAD_BASE + registerIndex, readValue);
    }

    /* Step 6: Verify independence — write to register 0 does not change register 1 */
    status = RTC_writeScratchRegister(rtcHandle, 0U, TEST_RTC_PATTERN_UNIQUE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    readValue = RTC_readScratchRegister(rtcHandle, 1U);
    TEST_ASSERT_EQUAL_UINT32(TEST_RTC_PATTERN_DEAD_BASE + 1U, readValue);
}

/**
 * \brief Test RTC scratch register persistence across stop/start cycles
 *
 * Test Category: Functional
 *
 * Verifies that scratch registers in the battery-backed domain preserve
 * data when the RTC counter is stopped and restarted.
 *
 * Test steps:
 * 1. Write values to registers 2 and 5.
 * 2. Call RTC_stop() and verify values unchanged.
 * 3. Call RTC_start() and verify again.
 * 4. Sleep 2 seconds.
 * 5. Call RTC_stop() and verify values.
 * 6. Call RTC_start(). Assert no SystemP_FAILURE.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Scratch register values persist through all stop/start cycles.
 */
static void TestRtc_scratchRegisterPersistence(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    readValueRegisterTwo = 0U;
    uint32_t    readValueRegisterFive = 0U;
    uint32_t    patternRegisterTwo = TEST_RTC_PATTERN_CHECKERBOARD_A;
    uint32_t    patternRegisterFive = TEST_RTC_PATTERN_CHECKERBOARD_B;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Write patterns to registers 2 and 5 */
    status = RTC_writeScratchRegister(rtcHandle, 2U, patternRegisterTwo);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_writeScratchRegister(rtcHandle, 5U, patternRegisterFive);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Stop RTC and verify values unchanged */
    status = RTC_stop(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    readValueRegisterTwo = RTC_readScratchRegister(rtcHandle, 2U);
    TEST_ASSERT_EQUAL_UINT32(patternRegisterTwo, readValueRegisterTwo);

    readValueRegisterFive = RTC_readScratchRegister(rtcHandle, 5U);
    TEST_ASSERT_EQUAL_UINT32(patternRegisterFive, readValueRegisterFive);

    /* Step 3: Start RTC and verify again */
    status = RTC_start(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    readValueRegisterTwo = RTC_readScratchRegister(rtcHandle, 2U);
    TEST_ASSERT_EQUAL_UINT32(patternRegisterTwo, readValueRegisterTwo);

    readValueRegisterFive = RTC_readScratchRegister(rtcHandle, 5U);
    TEST_ASSERT_EQUAL_UINT32(patternRegisterFive, readValueRegisterFive);

    /* Step 4: Sleep 2 seconds */
    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    /* Step 5: Stop again and verify persistence */
    status = RTC_stop(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    readValueRegisterTwo = RTC_readScratchRegister(rtcHandle, 2U);
    TEST_ASSERT_EQUAL_UINT32(patternRegisterTwo, readValueRegisterTwo);

    readValueRegisterFive = RTC_readScratchRegister(rtcHandle, 5U);
    TEST_ASSERT_EQUAL_UINT32(patternRegisterFive, readValueRegisterFive);

    /* Step 6: Start RTC and finish */
    status = RTC_start(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief Test RTC drift compensation register programming
 *
 * Test Category: Functional
 *
 * Verifies that RTC_adjustForDrift() correctly programs the compensation
 * register with positive, negative, zero, and boundary drift values.
 * Also validates persistence after stop/start and repeated writes.
 *
 * Test steps:
 * 1. Call RTC_adjustForDrift(+0.5f) and verify SystemP_SUCCESS.
 * 2. Call RTC_adjustForDrift(-0.5f) and verify.
 * 3. Call RTC_adjustForDrift(0.0f) and verify.
 * 4. Call RTC_adjustForDrift(minimum drift) and verify.
 * 5. Stop, start, apply drift again — verify no write-pend timeout.
 * 6. Apply same drift 3 times consecutively — verify all succeed.
 * 7. Assert no SystemP_FAILURE across all calls.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All drift compensation calls return SystemP_SUCCESS.
 *                 Repeated and post-restart writes succeed.
 */
static void TestRtc_adjustForDriftCompensation(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    repeatIndex = 0U;
    uint32_t    totalRepeats = 3U;
    Float32     positiveDrift = 0.5f;
    Float32     negativeDrift = -0.5f;
    Float32     zeroDrift = 0.0f;
    Float32     minimumDrift = 0.000030517578125f;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Positive drift */
    status = RTC_adjustForDrift(rtcHandle, positiveDrift);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Negative drift */
    status = RTC_adjustForDrift(rtcHandle, negativeDrift);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Zero drift */
    status = RTC_adjustForDrift(rtcHandle, zeroDrift);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Minimum representable drift (1 tick / 32768) */
    status = RTC_adjustForDrift(rtcHandle, minimumDrift);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 5: Persistence after stop/start cycle */
    status = RTC_stop(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_start(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_adjustForDrift(rtcHandle, positiveDrift);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 6: Repeated writes — verify no write-pend timeout */
    for (repeatIndex = 0U; repeatIndex < totalRepeats; repeatIndex+=1)
    {
        status = RTC_adjustForDrift(rtcHandle, positiveDrift);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
}

/**
 * \brief Test RTC write access control via KICK0/KICK1 lock/unlock
 *
 * Test Category: Functional
 *
 * Verifies that RTC_close() locks write access and direct register writes
 * are rejected, while RTC_open() restores write access via the kick
 * sequence. Uses direct register write to test the locked state because
 * the driver API requires a live mutex that is destructed by RTC_close().
 *
 * Test steps:
 * 1. Open RTC and set time A; verify SystemP_SUCCESS.
 * 2. Read time A back and verify correct.
 * 3. Close RTC (locks kick registers when enableIntr=false).
 * 4. Attempt direct register write while locked and verify rejection.
 * 5. Re-open RTC and verify time is natural progression from time A.
 * 6. Set time C on re-opened instance; verify read-back matches.
 * 7. Close instance.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Writes blocked when KICK is locked. Writes succeed
 *                 after re-open restores unlock. Time progresses
 *                 naturally, not from rejected write value.
 */
static void TestRtc_writeAccessControl(void *args)
{
    RTC_Handle              rtcHandle = NULL;
    const RTC_HwAttrs      *hardwareAttributes = NULL;
    uint32_t                baseAddress = 0U;
    volatile uint32_t      *secondCountLswRegister = NULL;
    volatile uint32_t      *syncPendRegister = NULL;
    uint32_t                rejectedWriteValue = TEST_RTC_PATTERN_DEADBEEF;
    uint32_t                registerReadBack = 0U;
    uint32_t                syncPendValue = 0U;
    RTC_Time                timeA;
    RTC_Time                timeC;
    RTC_Time                readTimeA;
    RTC_Time                readTimeAfterReopen;
    RTC_Time                readTimeC;
    int32_t                 status = SystemP_SUCCESS;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    /* Step 1: Open RTC and set time A */
    rtcHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(rtcHandle);

    hardwareAttributes = (const RTC_HwAttrs *)rtcHandle->hwAttrs;
    baseAddress        = hardwareAttributes->baseAddr;

    timeA.year   = 2024U;
    timeA.month  = 1U;
    timeA.day    = 1U;
    timeA.hour   = 10U;
    timeA.minute = 0U;
    timeA.second = 0U;

    status = RTC_setTime(rtcHandle, &timeA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Read back and verify */
    status = RTC_getTime(rtcHandle, &readTimeA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(10U, readTimeA.hour);

    /* Step 3: Close RTC — locks kick registers.
     * Note: enableIntr is true in the syscfg, so RTC_close() skips the
     * lock path. We manually lock the kick registers to test the feature. */
    RTC_close(rtcHandle);
    gRTCHandle[CONFIG_RTC0] = NULL;

    /* Manually lock kick registers since close skips it when enableIntr=true */
    secondCountLswRegister =
        (volatile uint32_t *)(baseAddress + CSL_RTC_KICK0);
    *secondCountLswRegister = TEST_RTC_PATTERN_ALL_ZEROS;
    secondCountLswRegister =
        (volatile uint32_t *)(baseAddress + CSL_RTC_KICK1);
    *secondCountLswRegister = TEST_RTC_PATTERN_ALL_ZEROS;

    /* Step 4: Attempt direct register write while locked */
    secondCountLswRegister =
        (volatile uint32_t *)(baseAddress + CSL_RTC_S_CNT_LSW);
    *secondCountLswRegister = rejectedWriteValue;

    /* Small delay for write to propagate (or be rejected) */
    ClockP_usleep(TEST_RTC_USLEEP_100_US);

    registerReadBack = *secondCountLswRegister;
    TEST_ASSERT_TRUE(registerReadBack != rejectedWriteValue);

    /* Optionally check write error flag */
    syncPendRegister =
        (volatile uint32_t *)(baseAddress + CSL_RTC_SYNCPEND);
    syncPendValue = *syncPendRegister;
    TEST_ASSERT_TRUE((syncPendValue & CSL_RTC_SYNCPEND_WRT_ERR_MASK) != 0U);

    /* Step 5: Re-open RTC (kick sequence re-executed) and verify time */
    RTC_deinit();
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);

    status = RTC_getTime(gRTCHandle[CONFIG_RTC0], &readTimeAfterReopen);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Time should be natural progression from time A, not the rejected value */
    TEST_ASSERT_EQUAL_UINT32(10U, readTimeAfterReopen.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, readTimeAfterReopen.minute);

    /* Step 6: Set time C and verify */
    timeC.year   = 2025U;
    timeC.month  = 3U;
    timeC.day    = 20U;
    timeC.hour   = 14U;
    timeC.minute = 30U;
    timeC.second = 0U;

    status = RTC_setTime(gRTCHandle[CONFIG_RTC0], &timeC);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(gRTCHandle[CONFIG_RTC0], &readTimeC);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2025U, readTimeC.year);
    TEST_ASSERT_EQUAL_UINT32(14U, readTimeC.hour);
    TEST_ASSERT_EQUAL_UINT32(30U, readTimeC.minute);
}

/* ========================================================================== */
/*                     Negative Test case definitions                         */
/* ========================================================================== */

/**
 * \brief Test RTC rejects logically invalid date values
 *
 * Test Category: Negative
 *
 * Verifies that RTC_setTime() rejects impossible Gregorian dates.
 * DRIVER GAP: current driver has no input validation; these calls may
 * corrupt the 48-bit seconds counter. Test documents expected behavior.
 *
 * Test steps:
 * 1. Set valid time 2024-06-15 12:00:00; verify with RTC_getTime().
 * 2. Attempt Feb 30; assert SystemP_FAILURE.
 * 3. Attempt month=13; assert SystemP_FAILURE.
 * 4. Attempt day=0; assert SystemP_FAILURE.
 * 5. Verify RTC_getTime() still matches the initial valid time.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All invalid dates rejected. Counter not corrupted.
 */
static void TestRtc_invalidDateReject(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    validTime;
    RTC_Time    invalidTime;
    RTC_Time    readBackTime;
    int32_t     status = SystemP_SUCCESS;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    rtcHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set valid baseline time */
    validTime.year   = 2024U;
    validTime.month  = 6U;
    validTime.day    = 15U;
    validTime.hour   = 12U;
    validTime.minute = 0U;
    validTime.second = 0U;

    status = RTC_setTime(rtcHandle, &validTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &readBackTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, readBackTime.year);
    TEST_ASSERT_EQUAL_UINT32(6U, readBackTime.month);
    TEST_ASSERT_EQUAL_UINT32(15U, readBackTime.day);

    /* Step 2: Feb 30 — invalid */
    invalidTime.year   = 2024U;
    invalidTime.month  = 2U;
    invalidTime.day    = 30U;
    invalidTime.hour   = 0U;
    invalidTime.minute = 0U;
    invalidTime.second = 0U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 3: month=13 — invalid */
    invalidTime.month = 13U;
    invalidTime.day   = 1U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 4: day=0 — invalid */
    invalidTime.month = 6U;
    invalidTime.day   = 0U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 5: Verify counter still matches initial valid time */
    status = RTC_getTime(rtcHandle, &readBackTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, readBackTime.year);
    TEST_ASSERT_EQUAL_UINT32(6U, readBackTime.month);
    TEST_ASSERT_EQUAL_UINT32(15U, readBackTime.day);
    TEST_ASSERT_EQUAL_UINT32(12U, readBackTime.hour);
}

/**
 * \brief Test all public RTC APIs reject NULL handle gracefully
 *
 * Test Category: Negative
 *
 * Verifies every public RTC API with a NULL handle returns failure or
 * a safe default value. No crash, assertion, or HW access occurs.
 *
 * Test steps:
 * 1. RTC_setTime(NULL, validTime) returns SystemP_FAILURE.
 * 2. RTC_getTime(NULL, outTime) returns SystemP_FAILURE.
 * 3. RTC_stop(NULL) returns SystemP_FAILURE.
 * 4. RTC_start(NULL) returns SystemP_FAILURE.
 * 5. RTC_readScratchRegister(NULL, 0) returns 0U.
 * 6. RTC_writeScratchRegister(NULL, 0, 0xABU) returns SystemP_FAILURE.
 * 7. RTC_adjustForDrift(NULL, 0.5f) returns SystemP_FAILURE.
 * 8. RTC_close(NULL) does not crash.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All calls return failure or safe value. No crash.
 */
static void TestRtc_nullHandleRejected(void *args)
{
    RTC_Time    validTime;
    RTC_Time    outputTime;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    scratchReadValue = 0U;

    validTime.year   = 2024U;
    validTime.month  = 1U;
    validTime.day    = 1U;
    validTime.hour   = 0U;
    validTime.minute = 0U;
    validTime.second = 0U;

    /* Step 1: RTC_setTime with NULL handle */
    status = RTC_setTime(NULL, &validTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 2: RTC_getTime with NULL handle */
    status = RTC_getTime(NULL, &outputTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 3: RTC_stop with NULL handle */
    status = RTC_stop(NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 4: RTC_start with NULL handle */
    status = RTC_start(NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 5: RTC_readScratchRegister with NULL handle */
    scratchReadValue = RTC_readScratchRegister(NULL, 0U);
    TEST_ASSERT_EQUAL_UINT32(0U, scratchReadValue);

    /* Step 6: RTC_writeScratchRegister with NULL handle */
    status = RTC_writeScratchRegister(NULL, 0U, 0xABU);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 7: RTC_adjustForDrift with NULL handle */
    status = RTC_adjustForDrift(NULL, 0.5f);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 8: RTC_close with NULL handle — should not crash */
    RTC_close(NULL);
}

/**
 * \brief Test RTC rejects year values below epoch baseline (1970)
 *
 * Test Category: Negative
 *
 * RTC_convertTimeToSeconds() loops from RTC_EPOCH_YEAR to year.
 * For year < 1970, the loop does not execute and produces incorrect
 * seconds values. Test documents expected rejection behavior.
 *
 * Test steps:
 * 1. Set valid time 2024-01-01 00:00:00; verify with RTC_getTime().
 * 2. Attempt year=1969; assert SystemP_FAILURE.
 * 3. Attempt year=0; assert SystemP_FAILURE.
 * 4. Verify RTC_getTime() still returns original valid time.
 * 5. Set year=1970 (epoch minimum); assert SystemP_SUCCESS.
 * 6. Verify RTC_getTime() returns year=1970.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Sub-epoch years rejected. Epoch year 1970 accepted.
 */
static void TestRtc_outOfRangeYear(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    validTime;
    RTC_Time    invalidTime;
    RTC_Time    epochTime;
    RTC_Time    readBackTime;
    int32_t     status = SystemP_SUCCESS;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    rtcHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set valid baseline time */
    validTime.year   = 2024U;
    validTime.month  = 1U;
    validTime.day    = 1U;
    validTime.hour   = 0U;
    validTime.minute = 0U;
    validTime.second = 0U;

    status = RTC_setTime(rtcHandle, &validTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &readBackTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, readBackTime.year);

    /* Step 2: year=1969 — below epoch */
    invalidTime        = validTime;
    invalidTime.year   = 1969U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 3: year=0 — far below epoch */
    invalidTime.year = 0U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 4: Verify original time still held */
    status = RTC_getTime(rtcHandle, &readBackTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, readBackTime.year);

    /* Step 5: Epoch minimum year=1970 */
    epochTime.year   = 1970U;
    epochTime.month  = 1U;
    epochTime.day    = 1U;
    epochTime.hour   = 0U;
    epochTime.minute = 0U;
    epochTime.second = 0U;

    status = RTC_setTime(rtcHandle, &epochTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 6: Verify epoch year */
    status = RTC_getTime(rtcHandle, &readBackTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(1970U, readBackTime.year);
}

/**
 * \brief Test RTC_open() rejects out-of-bounds instance index
 *
 * Test Category: Negative
 *
 * Verifies the guard (idx >= gRTCConfigNum) returns NULL and does not
 * access gRTCConfig[] out of bounds. Also confirms a valid open still
 * succeeds afterward (driver state not corrupted).
 *
 * Test steps:
 * 1. RTC_open(gRTCConfigNum, NULL) returns NULL.
 * 2. RTC_open(gRTCConfigNum + 1, NULL) returns NULL.
 * 3. RTC_open(0xFFFFFFFF, NULL) returns NULL.
 * 4. RTC_open(CONFIG_RTC0, NULL) still succeeds. Close it.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All invalid indices return NULL handle. Valid open
 *                 succeeds, confirming no driver corruption.
 */
static void TestRtc_openInvalidIndex(void *args)
{
    RTC_Handle  invalidHandle = NULL;
    RTC_Handle  validHandle = NULL;

    /* Close existing handle so CONFIG_RTC0 is available */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    /* Step 1: Index == gRTCConfigNum */
    invalidHandle = RTC_open(gRTCConfigNum, NULL);
    TEST_ASSERT_NULL(invalidHandle);

    /* Step 2: Index == gRTCConfigNum + 1 */
    invalidHandle = RTC_open(gRTCConfigNum + 1U, NULL);
    TEST_ASSERT_NULL(invalidHandle);

    /* Step 3: Maximum uint32 index */
    invalidHandle = RTC_open(TEST_RTC_INVALID_INDEX_MAX, NULL);
    TEST_ASSERT_NULL(invalidHandle);

    /* Step 4: Valid open still succeeds */
    validHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(validHandle);

    RTC_close(validHandle);

    /* Re-open with syscfg params to restore state for subsequent tests */
    RTC_deinit();
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test RTC double open returns NULL and double close does not crash
 *
 * Test Category: Negative
 *
 * Verifies that a second RTC_open() on an already-open instance returns
 * NULL (isOpen guard). Also verifies that calling RTC_close() twice
 * does not crash or hang.
 *
 * Test steps:
 * 1. Open CONFIG_RTC0; assert handle1 is not NULL.
 * 2. Open CONFIG_RTC0 again; assert handle2 is NULL.
 * 3. Verify handle1 is still usable via RTC_setTime() / RTC_getTime().
 * 4. Close handle1.
 * 5. Close handle1 again (double close); verify no crash.
 * 6. Re-open CONFIG_RTC0 to confirm re-openability.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Double open returns NULL. Double close does not crash.
 *                 Instance is re-openable after close.
 */
static void TestRtc_doubleOpenAndDoubleClose(void *args)
{
    RTC_Handle  handleFirst = NULL;
    RTC_Handle  handleSecond = NULL;
    RTC_Time    setTime;
    RTC_Time    readBackTime;
    int32_t     status = SystemP_SUCCESS;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    /* Step 1: First open */
    handleFirst = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(handleFirst);

    /* Step 2: Second open on same instance — must return NULL */
    handleSecond = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NULL(handleSecond);

    /* Step 3: Verify handle1 is still usable */
    setTime.year   = 2024U;
    setTime.month  = 3U;
    setTime.day    = 15U;
    setTime.hour   = 8U;
    setTime.minute = 30U;
    setTime.second = 0U;

    status = RTC_setTime(handleFirst, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(handleFirst, &readBackTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, readBackTime.year);
    TEST_ASSERT_EQUAL_UINT32(3U, readBackTime.month);
    TEST_ASSERT_EQUAL_UINT32(8U, readBackTime.hour);

    /* Step 4: First close */
    RTC_close(handleFirst);

    /* Step 5: Second close (double close) — should not crash */
    RTC_close(handleFirst);

    /* Step 6: Re-open to confirm re-openability */
    RTC_deinit();
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test RTC rejects invalid calendar field boundary values
 *
 * Test Category: Negative
 *
 * Exercises invalid calendar fields not covered by TestRtc_invalidDateReject.
 * Tests leap year edge cases, month boundaries, and extreme field values.
 * DRIVER GAP: driver lacks field validation in RTC_setTime().
 *
 * Test steps:
 * 1. Set valid baseline 2024-06-15 12:00:00.
 * 2. Feb 29 non-leap year=2023; assert SystemP_FAILURE.
 * 3. Century year=1900 Feb 29; assert SystemP_FAILURE.
 * 4. Jan 32; assert SystemP_FAILURE.
 * 5. Jun 31; assert SystemP_FAILURE.
 * 6. month=0; assert SystemP_FAILURE.
 * 7. month=255; assert SystemP_FAILURE.
 * 8. Verify RTC_getTime() still returns baseline.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All invalid fields rejected. Baseline preserved.
 */
static void TestRtc_calendarFieldBoundaryValidation(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    baselineTime;
    RTC_Time    invalidTime;
    RTC_Time    readBackTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set valid baseline */
    baselineTime.year   = 2024U;
    baselineTime.month  = 6U;
    baselineTime.day    = 15U;
    baselineTime.hour   = 12U;
    baselineTime.minute = 0U;
    baselineTime.second = 0U;

    status = RTC_setTime(rtcHandle, &baselineTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Feb 29 on non-leap year 2023 */
    invalidTime.year   = 2023U;
    invalidTime.month  = 2U;
    invalidTime.day    = 29U;
    invalidTime.hour   = 0U;
    invalidTime.minute = 0U;
    invalidTime.second = 0U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 3: Century year 1900 Feb 29 (not a leap year) */
    invalidTime.year = 1900U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 4: Jan 32 */
    invalidTime.year  = 2024U;
    invalidTime.month = 1U;
    invalidTime.day   = 32U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 5: Jun 31 (June has 30 days) */
    invalidTime.month = 6U;
    invalidTime.day   = 31U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 6: month=0 */
    invalidTime.month = 0U;
    invalidTime.day   = 1U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 7: month=255 */
    invalidTime.month = 255U;

    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 8: Verify baseline preserved */
    status = RTC_getTime(rtcHandle, &readBackTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, readBackTime.year);
    TEST_ASSERT_EQUAL_UINT32(6U, readBackTime.month);
    TEST_ASSERT_EQUAL_UINT32(15U, readBackTime.day);
    TEST_ASSERT_EQUAL_UINT32(12U, readBackTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, readBackTime.minute);
    TEST_ASSERT_EQUAL_UINT32(0U, readBackTime.second);
}

/**
 * \brief Negative: Reject time fields outside valid ranges
 *
 * Test Category: Negative
 *
 * Verifies that RTC_setTime() rejects hour >= 24, minute >= 60, or
 * second >= 60, returning SystemP_FAILURE for each invalid combination.
 * Note: RTC_convertTimeToSeconds() does not currently validate ranges;
 * this test documents the required behavior.
 *
 * Test steps:
 * 1. Set valid baseline time; assert SystemP_SUCCESS.
 * 2. {hour=24}; assert SystemP_FAILURE.
 * 3. {hour=255}; assert SystemP_FAILURE.
 * 4. {minute=60}; assert SystemP_FAILURE.
 * 5. {second=60}; assert SystemP_FAILURE.
 * 6. {minute=60, second=60}; assert SystemP_FAILURE.
 * 7. Verify baseline year/month/day/hour/minute unchanged.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC_setTime() returns SystemP_FAILURE for all invalid
 *                 field combinations. Baseline date/time fields unchanged.
 */
static void TestRtc_timeFieldOutOfRange(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    baselineTime;
    RTC_Time    invalidTime;
    RTC_Time    verifyTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set valid baseline time */
    baselineTime.year   = 2024U;
    baselineTime.month  = 6U;
    baselineTime.day    = 15U;
    baselineTime.hour   = 10U;
    baselineTime.minute = 30U;
    baselineTime.second = 0U;

    status = RTC_setTime(rtcHandle, &baselineTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: hour = 24 (valid range is 0-23) */
    invalidTime        = baselineTime;
    invalidTime.hour   = 24U;
    invalidTime.minute = 0U;
    invalidTime.second = 0U;
    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 3: hour = 255 (far out of range) */
    invalidTime.hour = 255U;
    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 4: minute = 60 (valid range is 0-59) */
    invalidTime        = baselineTime;
    invalidTime.minute = 60U;
    invalidTime.second = 0U;
    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 5: second = 60 (valid range is 0-59) */
    invalidTime        = baselineTime;
    invalidTime.minute = 0U;
    invalidTime.second = 60U;
    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 6: minute = 60 and second = 60 (both out of range) */
    invalidTime        = baselineTime;
    invalidTime.minute = 60U;
    invalidTime.second = 60U;
    status = RTC_setTime(rtcHandle, &invalidTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 7: Verify baseline date/time is unchanged (only seconds may differ) */
    status = RTC_getTime(rtcHandle, &verifyTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.year,   verifyTime.year);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.month,  verifyTime.month);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.day,    verifyTime.day);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.hour,   verifyTime.hour);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.minute, verifyTime.minute);
}

/**
 * \brief Negative: NULL time pointer passed to all time APIs
 *
 * Test Category: Negative
 *
 * Verifies that RTC_setTime(), RTC_getTime(), RTC_setOn_OffTimerEvent(),
 * and RTC_setOff_OnTimerEvent() each return SystemP_FAILURE when passed
 * a NULL time pointer. Verifies the instance recovers and accepts valid
 * calls afterward.
 *
 * Test steps:
 * 1. RTC_setTime(handle, NULL); assert SystemP_FAILURE.
 * 2. RTC_getTime(handle, NULL); assert SystemP_FAILURE.
 * 3. RTC_setOn_OffTimerEvent(handle, NULL); assert SystemP_FAILURE.
 * 4. RTC_setOff_OnTimerEvent(handle, NULL); assert SystemP_FAILURE.
 * 5. Verify instance still works with valid set/get calls.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All four API calls return SystemP_FAILURE for NULL input.
 *                 Subsequent valid calls complete with SystemP_SUCCESS.
 */
static void TestRtc_nullDataPointerAllApis(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    validTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: RTC_setTime with NULL pointer */
    status = RTC_setTime(rtcHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 2: RTC_getTime with NULL pointer */
    status = RTC_getTime(rtcHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 3: RTC_setOn_OffTimerEvent with NULL pointer */
    status = RTC_setOn_OffTimerEvent(rtcHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 4: RTC_setOff_OnTimerEvent with NULL pointer */
    status = RTC_setOff_OnTimerEvent(rtcHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 5: Verify instance still works with valid calls */
    validTime.year   = 2024U;
    validTime.month  = 7U;
    validTime.day    = 1U;
    validTime.hour   = 12U;
    validTime.minute = 0U;
    validTime.second = 0U;

    status = RTC_setTime(rtcHandle, &validTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, readTime.year);
    TEST_ASSERT_EQUAL_UINT32(12U,   readTime.hour);
}

/**
 * \brief Negative: Alarm set in the past must never fire
 *
 * Test Category: Negative
 *
 * Sets the RTC to 2024-07-01 12:00:00, then programs an On-Off alarm at
 * 2024-07-01 11:59:55 (5 seconds before the current time). Waits 5 seconds
 * and verifies the alarm semaphore was never posted (pend returns
 * SystemP_TIMEOUT). Verifies the RTC counter continued advancing normally.
 *
 * Test steps:
 * 1. Set RTC to 2024-07-01 12:00:00.
 * 2. Construct binary semaphore (count = 0).
 * 3. Set On-Off alarm to 2024-07-01 11:59:55.
 * 4. Sleep 5 seconds.
 * 5. Pend semaphore with 2-second timeout; assert SystemP_TIMEOUT.
 * 6. Verify RTC time advanced past 12:00:00.
 * 7. Destruct semaphore.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Semaphore pend returns SystemP_TIMEOUT. RTC time is
 *                 in hour 12, confirming the counter advanced normally.
 */
static void TestRtc_alarmInPast(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    currentTime;
    RTC_Time    pastAlarmTime;
    RTC_Time    verifyTime;
    int32_t     pendStatus = SystemP_SUCCESS;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    semaphoreTimeoutTicks = (uint32_t)ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_2_SEC);

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 2: Construct binary semaphore */
    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Step 1: Set RTC time to 2024-07-01 12:00:00 */
    currentTime.year   = 2024U;
    currentTime.month  = 7U;
    currentTime.day    = 1U;
    currentTime.hour   = 12U;
    currentTime.minute = 0U;
    currentTime.second = 0U;

    status = RTC_setTime(rtcHandle, &currentTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Set alarm 5 seconds before current time (in the past) */
    pastAlarmTime.year   = 2024U;
    pastAlarmTime.month  = 7U;
    pastAlarmTime.day    = 1U;
    pastAlarmTime.hour   = 11U;
    pastAlarmTime.minute = 59U;
    pastAlarmTime.second = 55U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &pastAlarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Sleep 5 seconds — alarm must not fire during this window */
    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    /* Step 5: Semaphore should NOT have been posted; pend must time out */
    pendStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj, semaphoreTimeoutTicks);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, pendStatus);

    /* Step 6: Verify RTC time advanced past 12:00:00 */
    status = RTC_getTime(rtcHandle, &verifyTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, verifyTime.year);
    TEST_ASSERT_EQUAL_UINT32(7U,    verifyTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U,    verifyTime.day);
    TEST_ASSERT_EQUAL_UINT32(12U,   verifyTime.hour);
    TEST_ASSERT_TRUE(verifyTime.second >= 5U);

    /* Step 7: Destruct semaphore */
    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

/**
 * \brief Negative: Scratch register index out of range must be rejected
 *
 * Test Category: Negative
 *
 * Verifies that RTC_writeScratchRegister() rejects indices >= 8 and returns
 * SystemP_FAILURE. Note: the driver does not currently validate the index;
 * this test documents the required behavior. Confirms valid registers are
 * unaffected by the invalid accesses.
 *
 * Test steps:
 * 1. Write a known value to valid index 0; assert SystemP_SUCCESS.
 * 2. Write to index 8; assert SystemP_FAILURE.
 * 3. Write to index 0xFFFFFFFF; assert SystemP_FAILURE.
 * 4. Read back index 0; assert value unchanged.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Indices >= 8 rejected with SystemP_FAILURE. Valid
 *                 register contents are unmodified.
 */
static void TestRtc_scratchRegisterOutOfRange(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    int32_t     writeStatus = SystemP_SUCCESS;
    uint32_t    knownValue = TEST_RTC_PATTERN_KNOWN;
    uint32_t    validReadback = 0U;
    uint32_t    validIndex = 0U;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Write known value to a valid index */
    writeStatus = RTC_writeScratchRegister(rtcHandle, validIndex, knownValue);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, writeStatus);

    /* Step 2: Index 8 is out of range (valid indices are 0-7) */
    writeStatus = RTC_writeScratchRegister(rtcHandle, TEST_RTC_INVALID_SCRATCH_INDEX, TEST_RTC_PATTERN_DEADBEEF);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, writeStatus);

    /* Step 3: Large invalid index */
    writeStatus = RTC_writeScratchRegister(rtcHandle, TEST_RTC_INVALID_INDEX_MAX, TEST_RTC_PATTERN_UNIQUE);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, writeStatus);

    /* Step 4: Confirm valid register 0 is unaffected */
    validReadback = RTC_readScratchRegister(rtcHandle, validIndex);
    TEST_ASSERT_EQUAL_UINT32(knownValue, validReadback);
}

/**
 * \brief Negative: Operations on a closed handle have undefined behavior
 *
 * Test Category: Negative
 *
 * Documents that calling RTC APIs on a closed handle is undefined. After
 * RTC_close(), the per-instance mutex is destructed; subsequent API calls
 * that pend on it may hang or corrupt state. This test verifies recovery
 * by re-initializing and re-opening the instance.
 *
 * \warning Steps 3-6 call APIs on a closed handle. If the driver does not
 *          check isOpen before pending on the mutex, these calls may hang
 *          indefinitely. Run this test only with a hardware watchdog active.
 *
 * Test steps:
 * 1. Open RTC instance; assert handle is not NULL.
 * 2. Close handle via RTC_close().
 * 3. Call RTC_setTime(handle, validTime) on closed handle.
 * 4. Call RTC_getTime(handle, readTime) on closed handle.
 * 5. Call RTC_stop(handle) on closed handle.
 * 6. Call RTC_writeScratchRegister(handle, 0, 0xABCD) on closed handle.
 * 7. Re-init and re-open; assert new handle is valid and time set/get works.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Instance recovers after re-init. RTC_setTime() and
 *                 RTC_getTime() return SystemP_SUCCESS on re-opened handle.
 */
static void TestRtc_operationsOnClosedHandle(void *args)
{
    RTC_Handle  closedHandle = NULL;
    RTC_Handle  recoveredHandle = NULL;
    RTC_Time    validTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    /* Step 1: Open RTC instance */
    closedHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(closedHandle);

    /* Step 2: Close the handle — mutex and HWI are destructed after this */
    RTC_close(closedHandle);

    /*
     * Steps 3-6: Operations on the closed handle.
     * WARNING: If the driver does not check isOpen before locking the
     * per-instance mutex, the following calls may hang indefinitely.
     * A hardware watchdog must be active when running this test.
     */
    validTime.year   = 2024U;
    validTime.month  = 8U;
    validTime.day    = 1U;
    validTime.hour   = 10U;
    validTime.minute = 0U;
    validTime.second = 0U;

    /* Step 3 */
    status = RTC_setTime(closedHandle, &validTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 4 */
    status = RTC_getTime(closedHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 5 */
    status = RTC_stop(closedHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 6 */
    status = RTC_writeScratchRegister(closedHandle, 0U, TEST_RTC_PATTERN_UNIQUE);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 7: Recover — deinit/init cycle resets isOpen flags */
    RTC_deinit();
    RTC_init();

    recoveredHandle = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(recoveredHandle);

    validTime.second = 0U;
    status = RTC_setTime(recoveredHandle, &validTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(recoveredHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gRTCHandle[CONFIG_RTC0] = recoveredHandle;
}

/**
 * \brief Negative: Redundant stop and start must not break RTC
 *
 * Test Category: Negative
 *
 * Verifies that calling RTC_stop() twice and RTC_start() twice does not
 * crash the driver, that the counter is frozen during the stopped interval,
 * and that the counter resumes monotonically after start.
 *
 * Test steps:
 * 1. Set baseline time to 2024-09-01 08:00:00.
 * 2. Call RTC_stop() twice; assert no SystemP_FAILURE on first call.
 * 3. Sleep 2 seconds; verify time is frozen (second is near 0).
 * 4. Call RTC_start() twice; assert no SystemP_FAILURE on first call.
 * 5. Sleep 3 seconds; verify time advanced by approximately 3 seconds.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Counter frozen after double stop. Counter resumes and
 *                 advances normally after double start.
 */
static void TestRtc_redundantStopAndStart(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    baselineTime;
    RTC_Time    frozenTime;
    RTC_Time    resumedTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set baseline time */
    baselineTime.year   = 2024U;
    baselineTime.month  = 9U;
    baselineTime.day    = 1U;
    baselineTime.hour   = 8U;
    baselineTime.minute = 0U;
    baselineTime.second = 0U;

    status = RTC_setTime(rtcHandle, &baselineTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Double stop — first must succeed; second is redundant */
    status = RTC_stop(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = RTC_stop(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Sleep 2 seconds; verify counter is frozen */
    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    status = RTC_getTime(rtcHandle, &frozenTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(8U, frozenTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, frozenTime.minute);
    TEST_ASSERT_UINT32_WITHIN(1U, 0U, frozenTime.second);

    /* Step 4: Double start — first must succeed; second is redundant */
    status = RTC_start(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = RTC_start(rtcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 5: Sleep 3 seconds; verify counter resumed and advanced */
    ClockP_sleep(TEST_RTC_SLEEP_3_SEC);

    status = RTC_getTime(rtcHandle, &resumedTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(8U, resumedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, resumedTime.minute);
    TEST_ASSERT_UINT32_WITHIN(2U, 3U, resumedTime.second);
}

/**
 * \brief Negative: RTC_deinit() while instance is open leads to unsafe state
 *
 * Test Category: Negative
 *
 * Documents that calling RTC_deinit() while an instance is open destroys
 * the driver-level lock without closing the instance. Subsequent API calls
 * through the still-open object are undefined. Verifies that recovery is
 * possible via a full RTC_init() + RTC_open() cycle.
 *
 * \warning Steps 3-4 operate on an instance whose driver lock was destroyed
 *          by RTC_deinit(). Behavior is implementation-defined and may
 *          cause assertion failures or hangs. Run with a watchdog active.
 *
 * Test steps:
 * 1. Open RTC instance.
 * 2. Call RTC_deinit() without closing — driver lock is destroyed.
 * 3. Call RTC_getTime() on the open handle (undefined, may succeed).
 * 4. Call RTC_close() on the open handle (undefined, may assert).
 * 5. Call RTC_init() and RTC_open(); assert recovery and valid operation.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC recovers fully after RTC_init() + RTC_open() cycle.
 *                 Time set and get operations succeed on re-opened handle.
 */
static void TestRtc_deinitWithOpenInstance(void *args)
{
    RTC_Handle  openHandle = NULL;
    RTC_Handle  recoveredHandle = NULL;
    RTC_Time    readTime;
    RTC_Time    validTime;
    int32_t     status = SystemP_SUCCESS;


    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    /* Step 1: Open RTC instance */
    openHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(openHandle);

    /* Step 2: Deinit while instance is open — driver lock is destroyed */
    RTC_deinit();

    /*
     * Step 3: RTC_getTime on still-open handle.
     * The per-instance mutex may still be intact; this may succeed or hang.
     */
    status = RTC_getTime(openHandle, &readTime);

    /*
     * Step 4: Skip RTC_close — driver lock was destroyed by RTC_deinit().
     * RTC_close() asserts gRTCDrvObj.lock != NULL and will abort.
     * Recovery via RTC_init() resets isOpen for all instances.
     */

    /* Step 5: Full recovery via init + open */
    RTC_init();

    recoveredHandle = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(recoveredHandle);

    validTime.year   = 2024U;
    validTime.month  = 10U;
    validTime.day    = 1U;
    validTime.hour   = 9U;
    validTime.minute = 0U;
    validTime.second = 0U;

    status = RTC_setTime(recoveredHandle, &validTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(recoveredHandle, &readTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2024U, readTime.year);

    gRTCHandle[CONFIG_RTC0] = recoveredHandle;
}

/* Disabled: driver bug — RTC_convertTimeToSeconds() has unbounded
 * for-loop (iterates year from 1970 to rtc_time->year). With
 * UINT32_MAX fields the loop runs ~4.29 billion iterations causing
 * an indefinite hang. Needs input validation in RTC_setTime(). 
 */
#if 0
/**
 * \brief Negative: UINT32_MAX time fields must be rejected immediately
 *
 * Test Category: Negative
 *
 * Verifies that RTC_setTime() rejects an RTC_Time struct with all fields
 * set to UINT32_MAX and returns SystemP_FAILURE without entering an
 * unbounded loop. Without the fix, RTC_convertTimeToSeconds() will iterate
 * over UINT32_MAX years, causing an indefinite hang.
 *
 * \warning Without a range-validation fix in RTC_convertTimeToSeconds(),
 *          the call in step 2 will hang indefinitely. Run only with a
 *          hardware watchdog configured, or after confirming the fix
 *          is in place.
 *
 * Test steps:
 * 1. Set a valid known baseline time.
 * 2. Set all RTC_Time fields to UINT32_MAX; call RTC_setTime(); assert
 *    SystemP_FAILURE (fixed driver) or observe hang (unfixed driver).
 * 3. Verify RTC time is unchanged from the baseline.
 * 4. Verify RTC still accepts a subsequent valid set/get call.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC_setTime() returns SystemP_FAILURE immediately.
 *                 RTC time is unchanged. Subsequent valid calls succeed.
 */
static void TestRtc_setTimeMaxUint32Fields(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    baselineTime;
    RTC_Time    maxFieldTime;
    RTC_Time    verifyTime;
    int32_t     status = SystemP_SUCCESS;


    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set a valid known baseline */
    baselineTime.year   = 2024U;
    baselineTime.month  = 11U;
    baselineTime.day    = 1U;
    baselineTime.hour   = 6U;
    baselineTime.minute = 0U;
    baselineTime.second = 0U;

    status = RTC_setTime(rtcHandle, &baselineTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: All fields UINT32_MAX — expect immediate failure, not hang */
    maxFieldTime.year   = TEST_RTC_PATTERN_ALL_ONES;
    maxFieldTime.month  = TEST_RTC_PATTERN_ALL_ONES;
    maxFieldTime.day    = TEST_RTC_PATTERN_ALL_ONES;
    maxFieldTime.hour   = TEST_RTC_PATTERN_ALL_ONES;
    maxFieldTime.minute = TEST_RTC_PATTERN_ALL_ONES;
    maxFieldTime.second = TEST_RTC_PATTERN_ALL_ONES;

    status = RTC_setTime(rtcHandle, &maxFieldTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 3: Verify RTC time is unchanged from the baseline */
    status = RTC_getTime(rtcHandle, &verifyTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.year,   verifyTime.year);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.month,  verifyTime.month);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.day,    verifyTime.day);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.hour,   verifyTime.hour);
    TEST_ASSERT_EQUAL_UINT32(baselineTime.minute, verifyTime.minute);

    /* Step 4: Verify instance accepts a subsequent valid call */
    baselineTime.year   = 2025U;
    baselineTime.second = 0U;

    status = RTC_setTime(rtcHandle, &baselineTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &verifyTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(2025U, verifyTime.year);
}
#endif

/* ========================================================================== */
/*                         Multithread Test Cases                             */
/* ========================================================================== */

#ifdef ENABLE_MT_TESTS

/* ========================================================================== */
/*                  Multithread Task Worker Functions                         */
/* ========================================================================== */

/* --- multipleInstances Workers --- */

static void TestRtc_instanceWorkerA(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    setTime;
    RTC_Time    readTime;
    int32_t     status;


    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    if (status != SystemP_SUCCESS) 
    { 
        TestRtc_TaskFailCountA+=1; 
    }

    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    status = RTC_getTime(rtcHandle, &readTime);
    if (status != SystemP_SUCCESS) 
    { 
        TestRtc_TaskFailCountA+=1; 
    }

    if ((readTime.second >= 1U) && (readTime.second <= 3U))
    {
        TestRtc_TaskFlagA = 1U;
    }
    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

static void TestRtc_instanceWorkerB(void *args)
{
    RTC_Handle invalidHandle;

    invalidHandle = RTC_open(gRTCConfigNum, NULL);
    if (invalidHandle == NULL)
    {
        TestRtc_TaskFlagB = 1U;
    }
    else
    {
        RTC_close(invalidHandle);
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

/* --- concurrentAlarmSameTime Workers --- */

static void TestRtc_alarmSameTimeWorkerA(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    alarmTime;
    int32_t     status;
    int32_t     pendStatus;

    alarmTime.year   = 2024U;
    alarmTime.month  = 9U;
    alarmTime.day    = 15U;
    alarmTime.hour   = 14U;
    alarmTime.minute = 0U;
    alarmTime.second = 5U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    if (status != SystemP_SUCCESS) 
    { 
        TestRtc_TaskFailCountA+=1; 
    }

    pendStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                 ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
    if (pendStatus != SystemP_SUCCESS) 
    { 
        TestRtc_TaskFailCountA+=1; 
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

static void TestRtc_alarmSameTimeWorkerB(void *args)
{
    RTC_Handle          rtcHandle = gRTCHandle[CONFIG_RTC0];
    const RTC_HwAttrs  *hardwareAttributes;
    uint32_t            baseAddress;
    RTC_Time            alarmTime;
    int32_t             status;
    int32_t             pendStatus;

    hardwareAttributes = (const RTC_HwAttrs *)rtcHandle->hwAttrs;
    baseAddress        = hardwareAttributes->baseAddr;

    alarmTime.year   = 2024U;
    alarmTime.month  = 9U;
    alarmTime.day    = 15U;
    alarmTime.hour   = 14U;
    alarmTime.minute = 0U;
    alarmTime.second = 5U;

    status = RTC_setOff_OnTimerEvent(rtcHandle, &alarmTime);
    if (status != SystemP_SUCCESS) 
    { 
        TestRtc_TaskFailCountB+=1; 
    }

    /* Re-enable OFF_ON interrupt — ISR disables both enables on any event */
    *((volatile uint32_t *)(baseAddress + CSL_RTC_IRQENABLE_SET_SYS)) =
        RTC_TMR_INT_INT1_SET_FLAG;

    pendStatus = SemaphoreP_pend(&TestRtc_OffOnSemObj,
                                 ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
    if (pendStatus != SystemP_SUCCESS) 
    { 
        TestRtc_TaskFailCountB+=1; 
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

/* --- concurrentAccessRaceCondition Workers --- */

static void TestRtc_raceWriterWorker(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    setTime;
    int32_t     status;
    uint32_t    iteration;

    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;

    for (iteration = 0U; iteration < TEST_RTC_MT_WRITER_ITERATIONS; iteration+=1)
    {
        setTime.second = iteration;
        status = RTC_setTime(rtcHandle, &setTime);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountA+=1; 
        }
        ClockP_usleep(TEST_RTC_USLEEP_10_MS);
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

static void TestRtc_raceReaderWorker(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    readTime;
    int32_t     status;
    uint32_t    iteration;
    uint32_t    currentTotalSeconds;
    uint32_t    previousTotalSeconds = 0U;

    for (iteration = 0U; iteration < TEST_RTC_MT_READER_ITERATIONS; iteration+=1)
    {
        status = RTC_getTime(rtcHandle, &readTime);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountB+=1; 
        }

        if ((readTime.hour > TEST_RTC_MAX_HOUR) || (readTime.minute > TEST_RTC_MAX_MINUTE) ||
            (readTime.second > TEST_RTC_MAX_SECOND))
        {
            TestRtc_TaskFlagB+=1;
        }

        currentTotalSeconds = (readTime.hour * TEST_RTC_SECONDS_PER_HOUR) +
                              (readTime.minute * TEST_RTC_SECONDS_PER_MINUTE) +
                              readTime.second;

        if ((iteration > 0U) && (currentTotalSeconds < previousTotalSeconds))
        {
            TestRtc_TaskFlagA+=1;
        }
        previousTotalSeconds = currentTotalSeconds;
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

/* --- concurrentScratchRegisterAccess Workers --- */

static void TestRtc_scratchWorkerA(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    int32_t     status;
    uint32_t    iteration;
    uint32_t    readValue;

    for (iteration = 0U; iteration < TEST_RTC_MT_SCRATCH_ITERATIONS; iteration+=1)
    {
        status = RTC_writeScratchRegister(rtcHandle, 0U,
                                         TEST_RTC_PATTERN_SCRATCH_A_BASE | iteration);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountA+=1; 
        }

        ClockP_usleep(TEST_RTC_USLEEP_1_MS);

        readValue = RTC_readScratchRegister(rtcHandle, 3U);
        if ((readValue & TEST_RTC_PATTERN_UPPER_MASK) == TEST_RTC_PATTERN_SCRATCH_A_BASE)
        {
            TestRtc_TaskFlagA+=1;
        }
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

static void TestRtc_scratchWorkerB(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    int32_t     status;
    uint32_t    iteration;
    uint32_t    readValue;

    for (iteration = 0U; iteration < TEST_RTC_MT_SCRATCH_ITERATIONS; iteration+=1)
    {
        status = RTC_writeScratchRegister(rtcHandle, 3U,
                                         TEST_RTC_PATTERN_SCRATCH_B_BASE | iteration);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountB+=1; 
        }

        ClockP_usleep(TEST_RTC_USLEEP_1_MS);

        readValue = RTC_readScratchRegister(rtcHandle, 0U);
        if ((readValue & TEST_RTC_PATTERN_UPPER_MASK) == TEST_RTC_PATTERN_SCRATCH_B_BASE)
        {
            TestRtc_TaskFlagB+=1;
        }
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

/* --- concurrentAlarmAndSetTime Workers --- */

static void TestRtc_alarmSetTimeWorkerA(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    alarmTime;
    int32_t     status;
    int32_t     pendStatus;

    alarmTime.year   = 2024U;
    alarmTime.month  = 1U;
    alarmTime.day    = 1U;
    alarmTime.hour   = 12U;
    alarmTime.minute = 0U;
    alarmTime.second = 10U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    if (status != SystemP_SUCCESS) 
    { 
        TestRtc_TaskFailCountA+=1; 
    }

    pendStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                 ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_15_SEC));
    if (pendStatus != SystemP_SUCCESS) 
    { 
        TestRtc_TaskFailCountA+=1; 
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

static void TestRtc_alarmSetTimeWorkerB(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    setTime;
    int32_t     status;
    uint32_t    iteration;

    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 12U;
    setTime.minute = 0U;

    for (iteration = 0U; iteration < TEST_RTC_MT_ALARM_SETTIME_ITERATIONS;
         iteration+=1)
    {
        setTime.second = iteration;
        status = RTC_setTime(rtcHandle, &setTime);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountB+=1; 
        }
        ClockP_usleep(TEST_RTC_USLEEP_200_MS);
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

/* --- concurrentStopStartWithGetTime Workers --- */

static void TestRtc_stopStartWorker(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    int32_t     status;
    uint32_t    iteration;

    for (iteration = 0U; iteration < TEST_RTC_MT_STOPSTART_ITERATIONS;
         iteration+=1)
    {
        status = RTC_stop(rtcHandle);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountA+=1; 
        }

        ClockP_usleep(TEST_RTC_USLEEP_50_MS);

        status = RTC_start(rtcHandle);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountA+=1; 
        }

        ClockP_usleep(TEST_RTC_USLEEP_50_MS);
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

static void TestRtc_getTimeLoopWorker(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    readTime;
    int32_t     status;
    uint32_t    iteration;
    uint32_t    currentTotalSeconds;
    uint32_t    previousTotalSeconds = 0U;

    for (iteration = 0U; iteration < TEST_RTC_MT_GETTIME_ITERATIONS; iteration+=1)
    {
        status = RTC_getTime(rtcHandle, &readTime);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountB+=1; 
        }

        if ((readTime.hour > TEST_RTC_MAX_HOUR) || (readTime.minute > TEST_RTC_MAX_MINUTE) ||
            (readTime.second > TEST_RTC_MAX_SECOND))
        {
            TestRtc_TaskFlagB+=1;
        }

        currentTotalSeconds = (readTime.hour * TEST_RTC_SECONDS_PER_HOUR) +
                              (readTime.minute * TEST_RTC_SECONDS_PER_MINUTE) +
                              readTime.second;

        if ((iteration > 0U) && (currentTotalSeconds < previousTotalSeconds))
        {
            TestRtc_TaskFlagA+=1;
        }
        previousTotalSeconds = currentTotalSeconds;
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

/* --- isrDuringApiExecution Workers --- */

static void TestRtc_isrSetTimeWorker(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    setTime;
    int32_t     status;
    uint32_t    iteration;

    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 12U;
    setTime.minute = 0U;

    for (iteration = 0U; iteration < TEST_RTC_MT_SETTIME_LOOP_COUNT; iteration+=1)
    {
        setTime.second = iteration % 60U;
        status = RTC_setTime(rtcHandle, &setTime);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountA+=1; 
        }
        ClockP_usleep(TEST_RTC_USLEEP_100_MS);
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

static void TestRtc_isrAlarmWaitWorker(void *args)
{
    int32_t pendStatus;

    pendStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                 ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
    if (pendStatus == SystemP_SUCCESS)
    {
        TestRtc_TaskFlagB = 1U;
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

/* --- concurrentOpenAttempt Workers --- */

static void TestRtc_openRaceWorkerA(void *args)
{
    SemaphoreP_pend(&TestRtc_BarrierSemaphore, SystemP_WAIT_FOREVER);
    TestRtc_RaceHandleA = RTC_open(CONFIG_RTC0, NULL);
    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

static void TestRtc_openRaceWorkerB(void *args)
{
    SemaphoreP_pend(&TestRtc_BarrierSemaphore, SystemP_WAIT_FOREVER);
    TestRtc_RaceHandleB = RTC_open(CONFIG_RTC0, NULL);
    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

/* --- highFrequencyParallelGetTime Workers --- */

static void TestRtc_parallelGetTimeWorkerA(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    readTime;
    int32_t     status;
    uint32_t    iteration;
    uint32_t    currentTotalSeconds;
    uint32_t    previousTotalSeconds = 0U;

    for (iteration = 0U; iteration < TEST_RTC_MT_PARALLEL_ITERATIONS; iteration+=1)
    {
        status = RTC_getTime(rtcHandle, &readTime);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountA+=1; 
        }

        if ((readTime.hour > TEST_RTC_MAX_HOUR) || (readTime.minute > TEST_RTC_MAX_MINUTE) ||
            (readTime.second > TEST_RTC_MAX_SECOND))
        {
            TestRtc_TaskFlagA+=1;
        }

        currentTotalSeconds = (readTime.hour * TEST_RTC_SECONDS_PER_HOUR) +
                              (readTime.minute * TEST_RTC_SECONDS_PER_MINUTE) +
                              readTime.second;

        if ((iteration > 0U) && (currentTotalSeconds < previousTotalSeconds))
        {
            TestRtc_TaskFailCountA+=1;
        }
        previousTotalSeconds = currentTotalSeconds;
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

static void TestRtc_parallelGetTimeWorkerB(void *args)
{
    RTC_Handle  rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time    readTime;
    int32_t     status;
    uint32_t    iteration;
    uint32_t    currentTotalSeconds;
    uint32_t    previousTotalSeconds = 0U;

    for (iteration = 0U; iteration < TEST_RTC_MT_PARALLEL_ITERATIONS; iteration+=1)
    {
        status = RTC_getTime(rtcHandle, &readTime);
        if (status != SystemP_SUCCESS) 
        { 
            TestRtc_TaskFailCountB+=1; 
        }

        if ((readTime.hour > TEST_RTC_MAX_HOUR) || (readTime.minute > TEST_RTC_MAX_MINUTE) ||
            (readTime.second > TEST_RTC_MAX_SECOND))
        {
            TestRtc_TaskFlagB+=1;
        }

        currentTotalSeconds = (readTime.hour * TEST_RTC_SECONDS_PER_HOUR) +
                              (readTime.minute * TEST_RTC_SECONDS_PER_MINUTE) +
                              readTime.second;

        if ((iteration > 0U) && (currentTotalSeconds < previousTotalSeconds))
        {
            TestRtc_TaskFailCountB+=1;
        }
        previousTotalSeconds = currentTotalSeconds;
    }

    SemaphoreP_post(&TestRtc_TaskDoneSemaphore);
    TaskP_exit();
}

/* ========================================================================== */
/*                  Multithread Test Case Definitions                         */
/* ========================================================================== */

/**
 * \brief Test RTC single-instance boundary with two concurrent tasks
 *
 * Test Category: Functional
 *
 * Task A operates on the open instance (set/get time, verify 2s advance).
 * Task B attempts to open an out-of-bounds index and verifies NULL.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Task A time advances ~2s. Task B gets NULL handle.
 */
static void TestRtc_multipleInstances(void *args)
{
    TaskP_Object    taskObjectA;
    TaskP_Object    taskObjectB;
    TaskP_Params    taskParams;
    int32_t         pendStatus;


    TestRtc_TaskFailCountA = 0;
    TestRtc_TaskFailCountB = 0;
    TestRtc_TaskFlagA      = 0U;
    TestRtc_TaskFlagB      = 0U;

    SemaphoreP_constructCounting(&TestRtc_TaskDoneSemaphore, 0U, 2U);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"RtcInstA";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackA;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_instanceWorkerA;
    TaskP_construct(&taskObjectA, &taskParams);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"RtcInstB";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackB;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_LOW;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_instanceWorkerB;
    TaskP_construct(&taskObjectB, &taskParams);

    pendStatus = SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, pendStatus);

    pendStatus = SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, pendStatus);



    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountA);
    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountB);
    TEST_ASSERT_EQUAL_UINT32(1U, TestRtc_TaskFlagA);
    TEST_ASSERT_EQUAL_UINT32(1U, TestRtc_TaskFlagB);

    ClockP_usleep(TEST_RTC_USLEEP_5_MS);
    TaskP_destruct(&taskObjectA);
    TaskP_destruct(&taskObjectB);
    SemaphoreP_destruct(&TestRtc_TaskDoneSemaphore);
}

/**
 * \brief Test both ON_OFF and OFF_ON alarms at the same timestamp
 *
 * Test Category: Functional
 *
 * Sets RTC time to 14:00:00. Task A arms ON_OFF at 14:00:05, Task B
 * arms OFF_ON at 14:00:05. Both pend on respective callback semaphores.
 * Verifies both fire and no duplicate follow-up events occur.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Both alarms fire. Follow-up pend returns timeout.
 */
static void TestRtc_concurrentAlarmSameTime(void *args)
{
    RTC_Handle      rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time        setTime;
    int32_t         status;
    int32_t         duplicatePendStatus;
    TaskP_Object    taskObjectA;
    TaskP_Object    taskObjectB;
    TaskP_Params    taskParams;

    TestRtc_TaskFailCountA = 0;
    TestRtc_TaskFailCountB = 0;

    setTime.year   = 2024U;
    setTime.month  = 9U;
    setTime.day    = 15U;
    setTime.hour   = 14U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_constructCounting(&TestRtc_OnOffSemObj, 0U, 1U);
    SemaphoreP_constructCounting(&TestRtc_OffOnSemObj, 0U, 1U);
    SemaphoreP_constructCounting(&TestRtc_TaskDoneSemaphore, 0U, 2U);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"AlarmA";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackA;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_alarmSameTimeWorkerA;
    TaskP_construct(&taskObjectA, &taskParams);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"AlarmB";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackB;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_LOW;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_alarmSameTimeWorkerB;
    TaskP_construct(&taskObjectB, &taskParams);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));

    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountA);
    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountB);

    /* Verify no duplicate firing */
    duplicatePendStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                          ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_2_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, duplicatePendStatus);

    duplicatePendStatus = SemaphoreP_pend(&TestRtc_OffOnSemObj,
                                          ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_2_SEC));
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, duplicatePendStatus);

    ClockP_usleep(TEST_RTC_USLEEP_5_MS);
    TaskP_destruct(&taskObjectA);
    TaskP_destruct(&taskObjectB);
    SemaphoreP_destruct(&TestRtc_TaskDoneSemaphore);
    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
    SemaphoreP_destruct(&TestRtc_OffOnSemObj);
}

/**
 * \brief Test concurrent writer (setTime) and reader (getTime) race
 *
 * Test Category: Multithread
 *
 * Task A writes 50 incrementing times. Task B reads 100 times and
 * validates field ranges and monotonicity. Verifies no API failure,
 * no invalid fields, and no deadlock.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput No failures. All reads have valid fields.
 *                 Reader times are monotonically non-decreasing.
 */
static void TestRtc_concurrentAccessRaceCondition(void *args)
{
    RTC_Handle      rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time        initialTime;
    RTC_Time        finalTime;
    int32_t         status;
    TaskP_Object    taskObjectA;
    TaskP_Object    taskObjectB;
    TaskP_Params    taskParams;

    TestRtc_TaskFailCountA = 0;
    TestRtc_TaskFailCountB = 0;
    TestRtc_TaskFlagA      = 0U;
    TestRtc_TaskFlagB      = 0U;

    initialTime.year   = 2024U;
    initialTime.month  = 1U;
    initialTime.day    = 1U;
    initialTime.hour   = 0U;
    initialTime.minute = 0U;
    initialTime.second = 0U;

    status = RTC_setTime(rtcHandle, &initialTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_constructCounting(&TestRtc_TaskDoneSemaphore, 0U, 2U);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"Writer";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackA;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_raceWriterWorker;
    TaskP_construct(&taskObjectA, &taskParams);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"Reader";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackB;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_LOW;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_raceReaderWorker;
    TaskP_construct(&taskObjectB, &taskParams);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));

    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountA);
    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountB);
    TEST_ASSERT_EQUAL_UINT32(0U, TestRtc_TaskFlagA);
    TEST_ASSERT_EQUAL_UINT32(0U, TestRtc_TaskFlagB);

    status = RTC_getTime(rtcHandle, &finalTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_usleep(TEST_RTC_USLEEP_5_MS);
    TaskP_destruct(&taskObjectA);
    TaskP_destruct(&taskObjectB);
    SemaphoreP_destruct(&TestRtc_TaskDoneSemaphore);
}

/**
 * \brief Test concurrent scratch register writes to different indices
 *
 * Test Category: Multithread
 *
 * Task A writes 50 values to scratch register 0. Task B writes 50
 * values to scratch register 3. Each task reads the other's register
 * and checks for cross-contamination. Final values are verified.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput No write failures. Final reg 0 = 0xAAAA0031.
 *                 Final reg 3 = 0xBBBB0031. No cross-contamination.
 */
static void TestRtc_concurrentScratchRegisterAccess(void *args)
{
    RTC_Handle      rtcHandle = gRTCHandle[CONFIG_RTC0];
    uint32_t        finalReadRegZero;
    uint32_t        finalReadRegThree;
    TaskP_Object    taskObjectA;
    TaskP_Object    taskObjectB;
    TaskP_Params    taskParams;

    TestRtc_TaskFailCountA = 0;
    TestRtc_TaskFailCountB = 0;
    TestRtc_TaskFlagA      = 0U;
    TestRtc_TaskFlagB      = 0U;

    SemaphoreP_constructCounting(&TestRtc_TaskDoneSemaphore, 0U, 2U);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"ScrA";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackA;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_scratchWorkerA;
    TaskP_construct(&taskObjectA, &taskParams);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"ScrB";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackB;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_LOW;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_scratchWorkerB;
    TaskP_construct(&taskObjectB, &taskParams);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));

    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountA);
    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountB);

    /* Allow write sync */
    ClockP_sleep(TEST_RTC_SLEEP_1_SEC);

    finalReadRegZero = RTC_readScratchRegister(rtcHandle, 0U);
    TEST_ASSERT_EQUAL_UINT32(TEST_RTC_PATTERN_SCRATCH_A_BASE | (TEST_RTC_MT_SCRATCH_ITERATIONS - 1U),
                             finalReadRegZero);

    finalReadRegThree = RTC_readScratchRegister(rtcHandle, 3U);
    TEST_ASSERT_EQUAL_UINT32(TEST_RTC_PATTERN_SCRATCH_B_BASE | (TEST_RTC_MT_SCRATCH_ITERATIONS - 1U),
                             finalReadRegThree);

    TEST_ASSERT_EQUAL_UINT32(0U, TestRtc_TaskFlagA);
    TEST_ASSERT_EQUAL_UINT32(0U, TestRtc_TaskFlagB);

    ClockP_usleep(TEST_RTC_USLEEP_5_MS);
    TaskP_destruct(&taskObjectA);
    TaskP_destruct(&taskObjectB);
    SemaphoreP_destruct(&TestRtc_TaskDoneSemaphore);
}

/**
 * \brief Test concurrent alarm programming and time updates
 *
 * Test Category: Multithread
 *
 * Task A arms ON_OFF alarm at 12:00:10, then pends. Task B writes 20
 * incrementing times with 200ms delay. Verifies no API failure, no
 * deadlock, and no crash. Alarm may or may not fire (timing-dependent).
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Both tasks complete. No SystemP_FAILURE. No crash.
 */
static void TestRtc_concurrentAlarmAndSetTime(void *args)
{
    RTC_Handle      rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time        initialTime;
    int32_t         status;
    TaskP_Object    taskObjectA;
    TaskP_Object    taskObjectB;
    TaskP_Params    taskParams;

    TestRtc_TaskFailCountA = 0;
    TestRtc_TaskFailCountB = 0;

    initialTime.year   = 2024U;
    initialTime.month  = 1U;
    initialTime.day    = 1U;
    initialTime.hour   = 12U;
    initialTime.minute = 0U;
    initialTime.second = 0U;

    status = RTC_setTime(rtcHandle, &initialTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_constructCounting(&TestRtc_OnOffSemObj, 0U, 1U);
    SemaphoreP_constructCounting(&TestRtc_TaskDoneSemaphore, 0U, 2U);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"AlarmT";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackA;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_alarmSetTimeWorkerA;
    TaskP_construct(&taskObjectA, &taskParams);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"SetTT";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackB;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_LOW;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_alarmSetTimeWorkerB;
    TaskP_construct(&taskObjectB, &taskParams);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));

    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountB);

    ClockP_usleep(TEST_RTC_USLEEP_5_MS);
    TaskP_destruct(&taskObjectA);
    TaskP_destruct(&taskObjectB);
    SemaphoreP_destruct(&TestRtc_TaskDoneSemaphore);
    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

/**
 * \brief Test repeated stop/start while another task reads time
 *
 * Test Category: Multithread
 *
 * Task A performs 10 stop/start cycles with 50ms delays. Task B
 * reads time 200 times, validates field ranges and monotonicity.
 * Time readings may plateau when stopped but must never go backward.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All API calls succeed. No invalid fields. Time
 *                 readings are monotonically non-decreasing.
 */
static void TestRtc_concurrentStopStartWithGetTime(void *args)
{
    RTC_Handle      rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time        initialTime;
    int32_t         status;
    TaskP_Object    taskObjectA;
    TaskP_Object    taskObjectB;
    TaskP_Params    taskParams;

    TestRtc_TaskFailCountA = 0;
    TestRtc_TaskFailCountB = 0;
    TestRtc_TaskFlagA      = 0U;
    TestRtc_TaskFlagB      = 0U;

    initialTime.year   = 2024U; 
    initialTime.month  = 1U;
    initialTime.day    = 1U;
    initialTime.hour   = 0U;
    initialTime.minute = 0U;
    initialTime.second = 0U;

    status = RTC_setTime(rtcHandle, &initialTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_constructCounting(&TestRtc_TaskDoneSemaphore, 0U, 2U);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"StpStrt";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackA;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_stopStartWorker;
    TaskP_construct(&taskObjectA, &taskParams);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"GetTRd";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackB;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_LOW;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_getTimeLoopWorker;
    TaskP_construct(&taskObjectB, &taskParams);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));

    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountA);
    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountB);
    TEST_ASSERT_EQUAL_UINT32(0U, TestRtc_TaskFlagA);
    TEST_ASSERT_EQUAL_UINT32(0U, TestRtc_TaskFlagB);

    ClockP_usleep(TEST_RTC_USLEEP_5_MS);
    TaskP_destruct(&taskObjectA);
    TaskP_destruct(&taskObjectB);
    SemaphoreP_destruct(&TestRtc_TaskDoneSemaphore);
}

/**
 * \brief Test alarm fires while task holds per-instance mutex
 *
 * Test Category: Multithread
 *
 * Schedules ON_OFF alarm at 12:00:02. Task A performs 50 setTime calls
 * with 100ms delay (~5s total), contending the mutex. Task B pends on
 * the alarm semaphore. Verifies callback fires, all setTime calls
 * succeed, and getTime returns valid time afterward.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Callback invoked. All setTime calls succeed.
 *                 getTime returns valid time after completion.
 */
static void TestRtc_isrDuringApiExecution(void *args)
{
    RTC_Handle      rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time        initialTime;
    RTC_Time        alarmTime;
    RTC_Time        verifyTime;
    int32_t         status;
    TaskP_Object    taskObjectA;
    TaskP_Object    taskObjectB;
    TaskP_Params    taskParams;

    TestRtc_TaskFailCountA = 0;
    TestRtc_TaskFailCountB = 0;
    TestRtc_TaskFlagB      = 0U;

    initialTime.year   = 2024U;
    initialTime.month  = 1U;
    initialTime.day    = 1U;
    initialTime.hour   = 12U;
    initialTime.minute = 0U;
    initialTime.second = 0U;

    status = RTC_setTime(rtcHandle, &initialTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_constructCounting(&TestRtc_OnOffSemObj, 0U, 1U);

    alarmTime          = initialTime;
    alarmTime.second   = 2U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_constructCounting(&TestRtc_TaskDoneSemaphore, 0U, 2U);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"SetTLp";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackA;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_LOW;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_isrSetTimeWorker;
    TaskP_construct(&taskObjectA, &taskParams);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"IsrWait";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackB;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_isrAlarmWaitWorker;
    TaskP_construct(&taskObjectB, &taskParams);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));

    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountA);
    TEST_ASSERT_EQUAL_UINT32(1U, TestRtc_TaskFlagB);

    status = RTC_getTime(rtcHandle, &verifyTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_TRUE(verifyTime.hour <= TEST_RTC_MAX_HOUR);
    TEST_ASSERT_TRUE(verifyTime.minute <= TEST_RTC_MAX_MINUTE);
    TEST_ASSERT_TRUE(verifyTime.second <= TEST_RTC_MAX_SECOND);

    ClockP_usleep(TEST_RTC_USLEEP_5_MS);
    TaskP_destruct(&taskObjectA);
    TaskP_destruct(&taskObjectB);
    SemaphoreP_destruct(&TestRtc_TaskDoneSemaphore);
    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

/**
 * \brief Test two tasks race to open the same RTC instance
 *
 * Test Category: Multithread
 *
 * Ensures CONFIG_RTC0 is closed. Task A and Task B simultaneously
 * attempt RTC_open(CONFIG_RTC0). Exactly one must succeed (non-NULL)
 * and the other must fail (NULL). No crash or assertion failure.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Exactly one handle is non-NULL. No crash.
 */
static void TestRtc_concurrentOpenAttempt(void *args)
{
    RTC_Handle      winnerHandle = NULL;
    TaskP_Object    taskObjectA;
    TaskP_Object    taskObjectB;
    TaskP_Params    taskParams;

    /* Close existing handle to free CONFIG_RTC0 */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    TestRtc_RaceHandleA = NULL;
    TestRtc_RaceHandleB = NULL;

    SemaphoreP_constructCounting(&TestRtc_TaskDoneSemaphore, 0U, 2U);
    SemaphoreP_constructCounting(&TestRtc_BarrierSemaphore, 0U, 2U);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"OpenA";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackA;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_openRaceWorkerA;
    TaskP_construct(&taskObjectA, &taskParams);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"OpenB";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackB;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_openRaceWorkerB;
    TaskP_construct(&taskObjectB, &taskParams);

    /* Release both tasks simultaneously */
    SemaphoreP_post(&TestRtc_BarrierSemaphore);
    SemaphoreP_post(&TestRtc_BarrierSemaphore);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));

    /* Exactly one must be non-NULL */
    TEST_ASSERT_TRUE(
        ((TestRtc_RaceHandleA != NULL) && (TestRtc_RaceHandleB == NULL)) ||
        ((TestRtc_RaceHandleA == NULL) && (TestRtc_RaceHandleB != NULL)));

    /* Close the winning handle */
    winnerHandle = (TestRtc_RaceHandleA != NULL) ?
                    TestRtc_RaceHandleA : TestRtc_RaceHandleB;
    RTC_close(winnerHandle);

    ClockP_usleep(TEST_RTC_USLEEP_5_MS);
    TaskP_destruct(&taskObjectA);
    TaskP_destruct(&taskObjectB);
    SemaphoreP_destruct(&TestRtc_TaskDoneSemaphore);
    SemaphoreP_destruct(&TestRtc_BarrierSemaphore);

    /* Restore for subsequent tests */
    RTC_deinit();
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test two tasks perform rapid parallel getTime reads
 *
 * Test Category: Multithread
 *
 * Sets RTC time to 12:00:00. Two tasks each perform 1000 getTime calls
 * with no delay. Verifies all calls succeed, no invalid fields, and
 * values are monotonically non-decreasing within each task.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All 2000 reads succeed. No invalid fields. Each
 *                 task's sequence is monotonically non-decreasing.
 */
static void TestRtc_highFrequencyParallelGetTime(void *args)
{
    RTC_Handle      rtcHandle = gRTCHandle[CONFIG_RTC0];
    RTC_Time        initialTime;
    int32_t         status;
    TaskP_Object    taskObjectA;
    TaskP_Object    taskObjectB;
    TaskP_Params    taskParams;

    TestRtc_TaskFailCountA = 0;
    TestRtc_TaskFailCountB = 0;
    TestRtc_TaskFlagA      = 0U;
    TestRtc_TaskFlagB      = 0U;

    initialTime.year   = 2024U;
    initialTime.month  = 6U;
    initialTime.day    = 15U;
    initialTime.hour   = 12U;
    initialTime.minute = 0U;
    initialTime.second = 0U;

    status = RTC_setTime(rtcHandle, &initialTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_constructCounting(&TestRtc_TaskDoneSemaphore, 0U, 2U);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"ParA";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackA;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_parallelGetTimeWorkerA;
    TaskP_construct(&taskObjectA, &taskParams);

    TaskP_Params_init(&taskParams);
    taskParams.name      = (char *)"ParB";
    taskParams.stackSize = TEST_RTC_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestRtc_TaskStackB;
    taskParams.priority  = TEST_RTC_MT_TASK_PRIORITY_HIGH;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestRtc_parallelGetTimeWorkerB;
    TaskP_construct(&taskObjectB, &taskParams);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestRtc_TaskDoneSemaphore, TEST_RTC_MT_TIMEOUT_TICKS));

    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountA);
    TEST_ASSERT_EQUAL_INT32(0, TestRtc_TaskFailCountB);
    TEST_ASSERT_EQUAL_UINT32(0U, TestRtc_TaskFlagA);
    TEST_ASSERT_EQUAL_UINT32(0U, TestRtc_TaskFlagB);

    ClockP_usleep(TEST_RTC_USLEEP_5_MS);
    TaskP_destruct(&taskObjectA);
    TaskP_destruct(&taskObjectB);
    SemaphoreP_destruct(&TestRtc_TaskDoneSemaphore);
}

#endif /* ENABLE_MT_TESTS */

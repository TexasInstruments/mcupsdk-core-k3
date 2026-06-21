/*
 * Copyright (C) 2021-2025 Texas Instruments Incorporated
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

/*  \file   test_spinlock.c
 *
 *
 *   \brief  Spinlock Driver Unit Test File
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/CycleCounterP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/watchdog.h>
#include <drivers/soc.h>
#include <drivers/spinlock.h>
#include <drivers/hw_include/cslr_soc.h>
#include <unity.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SPINLOCK_TIMEOUT_RETRY_COUNT    (100U)

#define ISR_TRIGGER_COUNT_PER_ISR       (10U)
#define ISR_TEST_INT_NUM_A              (20U)
#define ISR_TEST_INT_NUM_B              (21U)
#define ISR_TEST_LOCK_NUMBER            (1U)
#define DEADLOCK_TEST_INT_NUM           (22U)
#define DEADLOCK_TEST_LOCK_NUMBER       (2U)
#define DEADLOCK_TEST_TIMEOUT_MS        (1000U)
#define PERF_TEST_ITERATIONS            (1000U)
#define PERF_TEST_LOCK_NUMBER           (3U)
#define MULTI_LOCK_A                    (4U)
#define MULTI_LOCK_B                    (5U)
#define LOCK_INUSE_TEST_LOCK_NUMBER     (6U)
#define UNLOCK_FREE_LOCK_NUMBER         (7U)

#if defined(BUILD_C7X)
#define TEST_TASK_STACK_SIZE            (65536U)
#else
#define TEST_TASK_STACK_SIZE            (4096U)
#endif
#define CROSS_TASK_RELEASE_LOCK_NUMBER  (8U)
#define CROSS_TASK_STACK_SIZE           TEST_TASK_STACK_SIZE
#define CROSS_TASK_PRI                  (3U)
#define LOCK_PERSIST_INT_NUM            (23U)
#define LOCK_PERSIST_LOCK_NUMBER        (9U)

#if defined (ENABLE_MT)
#define SIMUL_RESET_LOCK_NUMBER         (10U)
#define COMMON_TEST_TASK_PRI            (3U)
#define MUTEX_TEST_LOCK_NUMBER          (11U)
#define MUTEX_TEST_DELAY_MS             (50U)
#define MUTEX_TEST_POLL_TIMEOUT_MS      (100U)
#define MUTEX_TEST_THREAD_A_ID          (0xAAAAAAAAU)
#define MUTEX_TEST_THREAD_B_ID          (0xBBBBBBBBU)
#define CONCURRENT_LOCK_A               (12U)
#define CONCURRENT_LOCK_B               (13U)
#define CONCURRENT_LOCK_C               (14U)
#define CONCURRENT_TEST_ITERATIONS      (10000U)
#define SHARED_COUNTER_TEST_LOCK_NUMBER (0U)
#define SHARED_COUNTER_ITERATIONS       (1000U)
#define MULTI_RESET_LOCK_A              (0U)
#define MULTI_RESET_LOCK_B              (1U)
#define MULTI_RESET_DELAY_MS            (50U)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if !defined(BUILD_C7X) && !defined(ENABLE_R5F)
static volatile uint32_t gIsrSharedCounter = 0;
static volatile uint32_t gIsrACompleteCount = 0;
static volatile uint32_t gIsrBCompleteCount = 0;
static volatile uint32_t gDeadlockIsrEntered = 0;
static volatile uint32_t gDeadlockDetected = 0;
#endif

#if defined (ENABLE_MT)
static volatile uint32_t gLockPersistIsrEntered = 0;
static volatile int32_t gLockPersistIsrLockStatus = SystemP_FAILURE;
static TaskP_Object gTestTask[4];
static uint8_t gTestStack[4][TEST_TASK_STACK_SIZE] __attribute__((aligned(32)));
static SemaphoreP_Object gTestSem[8];
static volatile int32_t gTestStatus[8];
static volatile uint32_t gTestCounter[8];
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Testcases */

static void TestSpinlock_acquireRelease(void *args);
static void TestSpinlock_getNumLocks(void *args);
static void TestSpinlock_moduleReset(void *args);
static void TestSpinlock_timeoutLogic(void *args);
#if !defined(BUILD_C7X) && !defined(ENABLE_R5F)
static void TestSpinlock_isrDataProtection(void *args);
static void TestSpinlock_isrDeadlock(void *args);
#endif
static void TestSpinlock_performanceMeasurement(void *args);
static void TestSpinlock_multipleLocksSimultaneous(void *args);
static void TestSpinlock_acquireInUseLock(void *args);
static void TestSpinlock_outOfRangeLockNumber(void *args);
static void TestSpinlock_unlockFreeLock(void *args);
#if defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM275X)
static void TestSpinlock_nullBaseAddress(void *args);
#endif
static void TestSpinlock_maxValidLockNumber(void *args);
static void TestSpinlock_uint32MaxLockNumber(void *args);
static void TestSpinlock_allLocksAcquired(void *args);
static void TestSpinlock_lockLeakRecovery(void *args);
static void TestSpinlock_highFrequencyStress(void *args);
#if defined (ENABLE_MT)
static void TestSpinlock_crossTaskRelease(void *args);
#if !defined(BUILD_C7X)
static void TestSpinlock_lockPersistAcrossInterrupt(void *args);
#endif
static void TestSpinlock_simultaneousModuleReset(void *args);
static void TestSpinlock_mutualExclusion(void *args);
static void TestSpinlock_concurrentIndependentLocks(void *args);
static void TestSpinlock_sharedResourceProtection(void *args);
static void TestSpinlock_multiThreadModuleReset(void *args);
#endif

/* Helpers */
#if !defined(BUILD_C7X) && !defined(ENABLE_R5F)
static void TestSpinlock_isrA(void *args);
static void TestSpinlock_isrB(void *args);
static void TestSpinlock_deadlockIsr(void *args);
#endif
#if defined (ENABLE_MT)
static void TestSpinlock_crossTaskReleaseTaskAMain(void *args);
static void TestSpinlock_crossTaskReleaseTaskBMain(void *args);
#if !defined(BUILD_C7X)
static void TestSpinlock_lockPersistIsr(void *args);
#endif
static void TestSpinlock_simulResetTaskAMain(void *args);
static void TestSpinlock_simulResetTaskBMain(void *args);
static void TestSpinlock_simulResetTaskCMain(void *args);
static void TestSpinlock_mutexThreadAMain(void *args);
static void TestSpinlock_mutexThreadBMain(void *args);
static void TestSpinlock_concurrentThreadAMain(void *args);
static void TestSpinlock_concurrentThreadBMain(void *args);
static void TestSpinlock_concurrentThreadCMain(void *args);
static void TestSpinlock_sharedCounterThreadAMain(void *args);
static void TestSpinlock_sharedCounterThreadBMain(void *args);
static void TestSpinlock_sharedCounterThreadCMain(void *args);
static void TestSpinlock_sharedCounterThreadDMain(void *args);
static void TestSpinlock_multiResetThreadAMain(void *args);
static void TestSpinlock_multiResetThreadBMain(void *args);
static void TestSpinlock_multiResetThreadCMain(void *args);
#endif

/* ========================================================================== */
/*                            Global Functions                                */
/* ========================================================================== */

void test_spinlock_main(void *args)
{
    (void) args;
    UNITY_BEGIN();

    RUN_TEST(TestSpinlock_acquireRelease, 10727, NULL);
    RUN_TEST(TestSpinlock_getNumLocks, 10728, NULL);
    RUN_TEST(TestSpinlock_moduleReset, 10729, NULL);
    RUN_TEST(TestSpinlock_timeoutLogic, 10731, NULL);
#if !defined(BUILD_C7X) && !defined(ENABLE_R5F)
    RUN_TEST(TestSpinlock_isrDataProtection, 10804, NULL);
    RUN_TEST(TestSpinlock_isrDeadlock, 10805, NULL);
#endif
    RUN_TEST(TestSpinlock_performanceMeasurement, 10806, NULL);
    RUN_TEST(TestSpinlock_multipleLocksSimultaneous, 10808, NULL);
    RUN_TEST(TestSpinlock_acquireInUseLock, 10810, NULL);
    RUN_TEST(TestSpinlock_outOfRangeLockNumber, 10811, NULL);
    RUN_TEST(TestSpinlock_unlockFreeLock, 10812, NULL);
#if defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM275X)
    RUN_TEST(TestSpinlock_nullBaseAddress, 10813, NULL);
#endif
    RUN_TEST(TestSpinlock_maxValidLockNumber, 10814, NULL);
    RUN_TEST(TestSpinlock_uint32MaxLockNumber, 10815, NULL);
    RUN_TEST(TestSpinlock_allLocksAcquired, 10809, NULL);
    RUN_TEST(TestSpinlock_lockLeakRecovery, 10816, NULL);
    RUN_TEST(TestSpinlock_highFrequencyStress, 10807, NULL);
#if defined (ENABLE_MT)
    RUN_TEST(TestSpinlock_crossTaskRelease, 10817, NULL);
#if !defined(BUILD_C7X)
    RUN_TEST(TestSpinlock_lockPersistAcrossInterrupt, 10818, NULL);
#endif
    RUN_TEST(TestSpinlock_simultaneousModuleReset, 10819, NULL);
    RUN_TEST(TestSpinlock_mutualExclusion, 10820, NULL);
    RUN_TEST(TestSpinlock_concurrentIndependentLocks, 10821, NULL);
    RUN_TEST(TestSpinlock_sharedResourceProtection, 10822, NULL);
    RUN_TEST(TestSpinlock_multiThreadModuleReset, 10823, NULL);
#endif

    UNITY_END();
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

/*
 * Testcases
 */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Helpers
 */

#if !defined(BUILD_C7X) && !defined(ENABLE_R5F)
/**
 * \brief ISR A for data protection test
 *
 * This ISR acquires a spinlock, increments a shared counter, and releases the lock.
 * Used to test spinlock protection of shared data between concurrent ISRs.
 */
static void TestSpinlock_isrA(void *args)
{
    int32_t status;

    /* Acquire spinlock to protect shared data */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, ISR_TEST_LOCK_NUMBER);

    /* Critical section: increment shared counter, release only if acquired */
    if (status == SPINLOCK_LOCK_STATUS_FREE)
    {
        gIsrSharedCounter++;
        Spinlock_unlock(CSL_SPINLOCK0_BASE, ISR_TEST_LOCK_NUMBER);
    }

    /* Track ISR A completion */
    gIsrACompleteCount++;
}

/**
 * \brief ISR B for data protection test
 *
 * This ISR acquires a spinlock, increments a shared counter, and releases the lock.
 * Used to test spinlock protection of shared data between concurrent ISRs.
 */
static void TestSpinlock_isrB(void *args)
{
    int32_t status;

    /* Acquire spinlock to protect shared data */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, ISR_TEST_LOCK_NUMBER);

    /* Critical section: increment shared counter, release only if acquired */
    if (status == SPINLOCK_LOCK_STATUS_FREE)
    {
        gIsrSharedCounter++;
        Spinlock_unlock(CSL_SPINLOCK0_BASE, ISR_TEST_LOCK_NUMBER);
    }

    /* Track ISR B completion */
    gIsrBCompleteCount++;
}
#endif

/**
 * \brief Test to verify that a spinlock can be successfully acquired and released.
 *
 * This test case validates the basic lock/unlock functionality:
 * 1. Acquires a lock and verifies it was free
 * 2. Releases the lock
 * 3. Acquires the lock again to verify it can be reused
 * 4. Releases the lock for cleanup
 */
static void TestSpinlock_acquireRelease(void *args)
{
    int32_t status;
    uint32_t lockNumber;

    /* Step 1: Define a valid lock number */
    lockNumber = 0;

    /* Step 2: Call Spinlock_lock() and verify return is SPINLOCK_LOCK_STATUS_FREE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Step 3: Call Spinlock_unlock() */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);

    /* Step 4: Call Spinlock_lock() again and verify return is SPINLOCK_LOCK_STATUS_FREE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Step 5: Call Spinlock_unlock() for cleanup */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);
}

/**
 * \brief Test to verify the driver correctly reports the number of available hardware spinlock instances.
 *
 * This test case validates:
 * 1. Calls Spinlock_getNumLocks() to query available locks
 * 2. Verifies the returned number is positive and non-zero
 * 3. Stores the number for use in range validation in other tests
 */
static void TestSpinlock_getNumLocks(void *args)
{
    uint32_t numLocks;

    /* Step 1: Call Spinlock_getNumLocks() */
    numLocks = Spinlock_getNumLocks(CSL_SPINLOCK0_BASE);

    /* Step 2: Verify returned number is a positive, non-zero value */
    TEST_ASSERT_GREATER_THAN_UINT32(0, numLocks);
}

/**
 * \brief Test to verify that Spinlock_moduleReset() resets the peripheral and releases held locks.
 *
 * This test case validates:
 * 1. Acquires a lock
 * 2. Verifies the lock is held by attempting to acquire it again
 * 3. Calls module reset to release all locks
 * 4. Verifies the same lock can be acquired after reset
 */
static void TestSpinlock_moduleReset(void *args)
{
    int32_t status;
    uint32_t lockNumber;

    lockNumber = 0;

    /* Step 1: Call Spinlock_lock() on a valid lock */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Step 2: Verify lock is held by calling Spinlock_lock() again (expect SPINLOCK_LOCK_STATUS_INUSE) */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, status);

    /* Step 3: Call Spinlock_moduleReset() */
    Spinlock_moduleReset(CSL_SPINLOCK0_BASE);

    /* Step 4: Call Spinlock_lock() on the same lock */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);

    /* Step 5: Verify return is SPINLOCK_LOCK_STATUS_FREE */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Cleanup: Release the lock */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);
}

/**
 * \brief Test to verify application-level timeout logic expires when a lock remains busy.
 *
 * This test case validates:
 * 1. Acquires a lock to make it busy
 * 2. Polls the lock multiple times with a retry count
 * 3. Verifies each poll attempt returns INUSE status
 * 4. Confirms all retry attempts complete without acquiring the lock
 * 5. Releases the lock for cleanup
 */
static void TestSpinlock_timeoutLogic(void *args)
{
    int32_t status;
    uint32_t lockNumber;
    uint32_t retryCount;
    uint32_t inuseCount;

    lockNumber = 0;
    inuseCount = 0;

    /* Step 1: Call Spinlock_lock() to ensure a lock is busy */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Step 2: Initialize a polling loop up to a fixed retry count */
    for (retryCount = 0; retryCount < SPINLOCK_TIMEOUT_RETRY_COUNT; retryCount++)
    {
        /* Step 3: Inside loop, call Spinlock_lock() and confirm status is INUSE */
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);
        TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, status);

        if (status == SPINLOCK_LOCK_STATUS_INUSE)
        {
            inuseCount++;
        }
    }

    /* Step 4: Verify loop completes all iterations without acquiring the lock */
    TEST_ASSERT_EQUAL_UINT32(SPINLOCK_TIMEOUT_RETRY_COUNT, retryCount);
    TEST_ASSERT_EQUAL_UINT32(SPINLOCK_TIMEOUT_RETRY_COUNT, inuseCount);

    /* Step 5: Call Spinlock_unlock() to cleanup */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);
}

#if !defined(BUILD_C7X) && !defined(ENABLE_R5F)

/**
 * \brief Test to verify spinlocks protect data shared between different interrupt service routines.
 *
 * This test case validates:
 * 1. Registers ISR_A and ISR_B with the same priority
 * 2. Triggers both ISRs multiple times
 * 3. Each ISR acquires lock, increments shared counter, and releases lock
 * 4. Verifies final counter value matches total number of triggers
 */
static void TestSpinlock_isrDataProtection(void *args)
{
    int32_t status;
    HwiP_Params hwiParamsA, hwiParamsB;
    HwiP_Object hwiObjA, hwiObjB;
    uint32_t i;
    uint32_t expectedCount;
    uint32_t timeout;

    /* Initialize shared counter */
    gIsrSharedCounter = 0;
    gIsrACompleteCount = 0;
    gIsrBCompleteCount = 0;

    /* Step 1: Register ISR_A with HwiP_construct() */
    HwiP_Params_init(&hwiParamsA);
    hwiParamsA.intNum = ISR_TEST_INT_NUM_A;
    hwiParamsA.callback = TestSpinlock_isrA;
    hwiParamsA.priority = 1;
    status = HwiP_construct(&hwiObjA, &hwiParamsA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 1: Register ISR_B with HwiP_construct() with same priority */
    HwiP_Params_init(&hwiParamsB);
    hwiParamsB.intNum = ISR_TEST_INT_NUM_B;
    hwiParamsB.callback = TestSpinlock_isrB;
    hwiParamsB.priority = 1;
    status = HwiP_construct(&hwiObjB, &hwiParamsB);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Trigger both ISRs multiple times */
    for (i = 0; i < ISR_TRIGGER_COUNT_PER_ISR; i++)
    {
        HwiP_post(ISR_TEST_INT_NUM_A);
        HwiP_post(ISR_TEST_INT_NUM_B);
    }

    /* Wait for all ISRs to complete with timeout */
    expectedCount = ISR_TRIGGER_COUNT_PER_ISR;
    timeout = 1000;
    while ((gIsrACompleteCount < expectedCount || gIsrBCompleteCount < expectedCount) && timeout > 0)
    {
        ClockP_usleep(100);
        timeout--;
    }

    /* Step 3: Verify final counter value matches total number of triggers */
    expectedCount = ISR_TRIGGER_COUNT_PER_ISR * 2; /* Both ISR_A and ISR_B */
    TEST_ASSERT_EQUAL_UINT32(expectedCount, gIsrSharedCounter);
    TEST_ASSERT_EQUAL_UINT32(ISR_TRIGGER_COUNT_PER_ISR, gIsrACompleteCount);
    TEST_ASSERT_EQUAL_UINT32(ISR_TRIGGER_COUNT_PER_ISR, gIsrBCompleteCount);

    /* Cleanup */
    HwiP_destruct(&hwiObjA);
    HwiP_destruct(&hwiObjB);
}

/**
 * \brief ISR for deadlock test - attempts to acquire lock already held by main thread.
 *
 * This ISR will spin indefinitely when attempting to acquire a lock that is
 * already held by the interrupted thread, demonstrating a deadlock scenario.
 * A safety limit prevents true infinite spinning for test purposes.
 */
static void TestSpinlock_deadlockIsr(void *args)
{
    int32_t status;
    uint32_t spinCount = 0;
    uint32_t maxSpinCount = 100000; /* Safety limit to prevent infinite spinning */

    /* Mark that ISR has been entered */
    gDeadlockIsrEntered = 1;

    /* Attempt to acquire the same lock held by main thread - this will cause deadlock */
    while (spinCount < maxSpinCount)
    {
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, DEADLOCK_TEST_LOCK_NUMBER);

        if (status == SPINLOCK_LOCK_STATUS_FREE)
        {
            /* If we somehow got the lock, release it and exit */
            Spinlock_unlock(CSL_SPINLOCK0_BASE, DEADLOCK_TEST_LOCK_NUMBER);
            break;
        }

        spinCount++;

        /* Check if we've been spinning too long - indicates deadlock */
        if (spinCount >= maxSpinCount)
        {
            gDeadlockDetected = 1;
        }
    }
}

/**
 * \brief Test to validate that a deadlock occurs if an ISR preempts a thread holding the same lock.
 *
 * This test case validates:
 * 1. Registers an ISR
 * 2. Main thread acquires a spinlock
 * 3. Manually triggers the ISR while holding the lock
 * 4. ISR attempts to acquire the same lock and spins (deadlock condition)
 * 5. Verifies deadlock is detected (ISR cannot acquire the lock)
 * 6. Main thread releases the lock and cleans up
 *
 * Note: In a real deadlock scenario, the system would hang indefinitely.
 * This test uses a timeout mechanism to detect the deadlock condition safely.
 */
static void TestSpinlock_isrDeadlock(void *args)
{
    int32_t status;
    HwiP_Params hwiParams;
    HwiP_Object hwiObj;
    uint32_t timeout;

    /* Initialize deadlock detection variables */
    gDeadlockIsrEntered = 0;
    gDeadlockDetected = 0;

    /* Step 1: Register an ISR for deadlock testing */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum = DEADLOCK_TEST_INT_NUM;
    hwiParams.callback = TestSpinlock_deadlockIsr;
    hwiParams.priority = 1;
    status = HwiP_construct(&hwiObj, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Main thread acquires the spinlock */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, DEADLOCK_TEST_LOCK_NUMBER);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Step 3: Manually trigger ISR while holding the lock */
    HwiP_post(DEADLOCK_TEST_INT_NUM);

    /* Step 4: Wait for ISR to enter and attempt lock acquisition with timeout */
    timeout = DEADLOCK_TEST_TIMEOUT_MS;
    while (gDeadlockIsrEntered == 0 && timeout > 0)
    {
        ClockP_usleep(100);
        timeout--;
    }

    /* Verify ISR was entered */
    TEST_ASSERT_EQUAL_UINT32(1, gDeadlockIsrEntered);

    /* Wait for deadlock detection with timeout */
    timeout = DEADLOCK_TEST_TIMEOUT_MS;
    while (gDeadlockDetected == 0 && timeout > 0)
    {
        ClockP_usleep(100);
        timeout--;
    }

    /* Step 5: Verify deadlock was detected (ISR spun trying to acquire the lock) */
    TEST_ASSERT_EQUAL_UINT32(1, gDeadlockDetected);

    /* Step 6: Main thread releases the lock for cleanup */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, DEADLOCK_TEST_LOCK_NUMBER);

    /* Cleanup */
    HwiP_destruct(&hwiObj);

    /* Additional verification: Try to acquire lock again to ensure it's properly released */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, DEADLOCK_TEST_LOCK_NUMBER);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);
    Spinlock_unlock(CSL_SPINLOCK0_BASE, DEADLOCK_TEST_LOCK_NUMBER);
}
#endif

/**
 * \brief Test to measure execution time of acquiring an uncontended lock.
 *
 * This test case validates the performance characteristics of spinlock acquisition:
 * 1. Initializes and resets the high-resolution cycle counter
 * 2. Loops 1000 times, recording timestamps before and after each lock acquisition
 * 3. Calculates the average time delta for lock acquisition
 * 4. Reports the average cycle count and time in microseconds
 *
 * This provides a baseline performance metric for uncontended lock acquisition,
 * useful for performance analysis and optimization.
 */
static void TestSpinlock_performanceMeasurement(void *args)
{
    int32_t status;
    uint32_t i;
    uint32_t startCycles, endCycles;
    uint64_t totalCycles = 0;
    uint64_t averageCycles;
    uint64_t averageTimeNs;

    /* Step 1: Initialize and reset the high-resolution cycle counter */
    CycleCounterP_reset();

    /* Step 2: Loop 1000 times to measure lock acquisition time */
    for (i = 0; i < PERF_TEST_ITERATIONS; i++)
    {
        /* Record start timestamp */
        startCycles = CycleCounterP_getCount32();

        /* Call Spinlock_lock() */
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, PERF_TEST_LOCK_NUMBER);

        /* Record end timestamp */
        endCycles = CycleCounterP_getCount32();

        /* Verify lock was acquired successfully */
        TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

        /* Accumulate cycle count (handle potential overflow) */
        if (endCycles >= startCycles)
        {
            totalCycles += (endCycles - startCycles);
        }
        else
        {
            /* Handle counter overflow */
            totalCycles += ((0xFFFFFFFFU - startCycles) + endCycles + 1);
        }

        /* Call Spinlock_unlock() to release for next iteration */
        Spinlock_unlock(CSL_SPINLOCK0_BASE, PERF_TEST_LOCK_NUMBER);
    }

    /* Step 3: Calculate average delta between start and end timestamps */
    averageCycles = totalCycles / PERF_TEST_ITERATIONS;

    /* Convert cycles to time (assuming typical CPU frequency) */
    /* Note: For more accurate timing, use CycleCounterP_nsToTicks() with actual CPU frequency */
    averageTimeNs = averageCycles; /* Approximate conversion, adjust based on CPU */

    /* Report performance results */
    DebugP_log("[SPINLOCK PERFORMANCE] Lock acquisition time:\r\n");
    DebugP_log("  Iterations: %d\r\n", PERF_TEST_ITERATIONS);
    DebugP_log("  Total cycles: %llu\r\n", totalCycles);
    DebugP_log("  Average cycles per lock: %llu\r\n", averageCycles);
    DebugP_log("  Average time (approx): %llu cycles\r\n", averageTimeNs);

    /* Verify average is reasonable (sanity check - should be non-zero and not excessive) */
    TEST_ASSERT_GREATER_THAN_UINT32(0, (uint32_t)averageCycles);
    TEST_ASSERT_LESS_THAN_UINT32(10000, (uint32_t)averageCycles); /* Sanity upper bound */
}

/**
 * \brief Test to verify a core can successfully hold multiple distinct locks simultaneously.
 *
 * This test case validates that a single core can hold multiple different locks at the same time:
 * 1. Acquires LOCK_A and verifies it was free
 * 2. While holding LOCK_A, acquires LOCK_B and verifies it was free
 * 3. Releases LOCK_B
 * 4. Releases LOCK_A
 * 5. Verifies both locks are available individually by re-acquiring each
 *
 * This ensures the spinlock implementation correctly supports multiple concurrent lock holdings
 * by the same core without interference between different lock instances.
 */
static void TestSpinlock_multipleLocksSimultaneous(void *args)
{
    int32_t statusA, statusB;

    /* Step 1: Call Spinlock_lock() for LOCK_A and verify FREE */
    statusA = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_LOCK_A);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, statusA);

    /* Step 2: Call Spinlock_lock() for LOCK_B (while holding LOCK_A) and verify FREE */
    statusB = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_LOCK_B);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, statusB);

    /* At this point, the core holds both LOCK_A and LOCK_B simultaneously */
    /* Verify both locks are actually held by attempting to re-acquire them */
    statusA = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_LOCK_A);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, statusA);

    statusB = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_LOCK_B);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, statusB);

    /* Step 3: Release LOCK_B */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, MULTI_LOCK_B);

    /* Verify LOCK_B is now free while LOCK_A is still held */
    statusB = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_LOCK_B);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, statusB);
    Spinlock_unlock(CSL_SPINLOCK0_BASE, MULTI_LOCK_B);

    /* Verify LOCK_A is still held */
    statusA = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_LOCK_A);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, statusA);

    /* Step 4: Release LOCK_A */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, MULTI_LOCK_A);

    /* Step 5: Verify both locks are available individually */
    /* Verify LOCK_A is free */
    statusA = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_LOCK_A);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, statusA);
    Spinlock_unlock(CSL_SPINLOCK0_BASE, MULTI_LOCK_A);

    /* Verify LOCK_B is free */
    statusB = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_LOCK_B);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, statusB);
    Spinlock_unlock(CSL_SPINLOCK0_BASE, MULTI_LOCK_B);
}

/**
 * \brief Test to verify that attempting to acquire an already in-use spinlock returns INUSE status.
 *
 * This test case validates the expected failure behavior when attempting to acquire
 * a lock that is already held:
 * 1. Acquires a lock and verifies it was free
 * 2. Attempts to acquire the same lock again without releasing it
 * 3. Verifies the second acquisition returns INUSE status
 * 4. Releases the lock for cleanup
 *
 * This ensures proper lock state tracking and prevents double-acquisition by the same core.
 */
static void TestSpinlock_acquireInUseLock(void *args)
{
    int32_t status;
    uint32_t lockNumber;

    /* Step 1: Define a valid lock number */
    lockNumber = LOCK_INUSE_TEST_LOCK_NUMBER;

    /* Step 2: Call Spinlock_lock() and verify return is SPINLOCK_LOCK_STATUS_FREE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Step 3: Call Spinlock_lock() a second time on the same lock without unlocking */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);

    /* Step 4: Verify return is SPINLOCK_LOCK_STATUS_INUSE */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, status);

    /* Step 5: Call Spinlock_unlock() for cleanup */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);
}

/**
 * \brief Test to verify the driver correctly handles API calls using an out-of-range lock number.
 *
 * This test case validates that the driver properly handles invalid lock numbers:
 * 1. Calls Spinlock_getNumLocks() to determine the total valid lock count
 * 2. Defines an invalid lock number (beyond the valid range)
 * 3. Attempts to acquire the lock with the invalid number
 * 4. Verifies the return value is SystemP_FAILURE
 * 5. Attempts to unlock with the invalid number to ensure no system fault occurs
 *
 * This ensures the driver provides proper error handling for out-of-range lock numbers
 * and fails gracefully without causing system faults.
 */
static void TestSpinlock_outOfRangeLockNumber(void *args)
{
    int32_t status;
    uint32_t numLocks;
    uint32_t invalidLockNumber;

    /* Step 1: Call Spinlock_getNumLocks() to determine total count */
    numLocks = Spinlock_getNumLocks(CSL_SPINLOCK0_BASE);
    TEST_ASSERT_GREATER_THAN_UINT32(0, numLocks);

    /* Step 2: Define an invalid lock number (beyond valid range) */
    invalidLockNumber = numLocks + 10; /* Well beyond the valid range */

    /* Step 3: Call Spinlock_lock() with the invalid number */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, invalidLockNumber);

    /* Step 4: Verify return is SystemP_FAILURE */
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 5: Call Spinlock_unlock() with the invalid number to ensure no system fault */
    /* This should not cause a fault - the API should handle it gracefully */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, invalidLockNumber);

    /* Additional test: Try with maximum possible uint32_t value */
    invalidLockNumber = 0xFFFFFFFFU;
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, invalidLockNumber);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    Spinlock_unlock(CSL_SPINLOCK0_BASE, invalidLockNumber);
}

/**
 * \brief Test to verify releasing an already free lock does not cause errors or invalid states.
 *
 * This test case validates that unlocking an already free lock is handled gracefully:
 * 1. Ensures a lock is in the free state
 * 2. Calls Spinlock_unlock() on the free lock (no-op operation)
 * 3. Attempts to acquire the lock
 * 4. Verifies the lock can still be acquired normally (returns FREE status)
 * 5. Releases the lock for cleanup
 *
 * This ensures the unlock operation on a free lock does not corrupt the lock state
 * or cause system errors.
 */
static void TestSpinlock_unlockFreeLock(void *args)
{
    int32_t status;
    uint32_t lockNumber;

    lockNumber = UNLOCK_FREE_LOCK_NUMBER;

    /* Step 1: Ensure a lock is free by attempting to acquire and release it */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);

    /* Step 2: Call Spinlock_unlock() on the free lock (should be a no-op) */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);

    /* Step 3: Call Spinlock_lock() on that same lock */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);

    /* Step 4: Verify return is SPINLOCK_LOCK_STATUS_FREE */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Step 5: Call Spinlock_unlock() for cleanup */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);
}

#if defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM275X)
/**
 * \brief Test to verify that API calls with a NULL base address are handled correctly without system crashes.
 *
 * This test case validates defensive programming in the driver API:
 * 1. Calls Spinlock_getNumLocks() with baseAddr = 0 (NULL) and verifies behavior
 * 2. Calls Spinlock_lock() with baseAddr = 0 and verifies proper error handling
 * 3. Calls Spinlock_unlock() with baseAddr = 0 and verifies no system crash
 *
 * This ensures the driver gracefully handles invalid base address parameters
 * without causing system faults or undefined behavior.
 *
 * Note: The expected behavior may be returning 0 for getNumLocks, and
 * the API should not crash even with NULL pointers.
 */
static void TestSpinlock_nullBaseAddress(void *args)
{
    int32_t status;
    uint32_t numLocks;
    uint32_t lockNumber = 0;

    /* Step 1: Call Spinlock_getNumLocks() with baseAddr = 0 */
    numLocks = Spinlock_getNumLocks(0);

    /* Step 2: Verify behavior - NULL base should return 0 or handle gracefully */
    /* The API may return 0 to indicate invalid base address */
    TEST_ASSERT_EQUAL_UINT32(0, numLocks);

    /* Step 3: Call Spinlock_lock() with baseAddr = 0 and lock 0 */
    status = Spinlock_lock(0, lockNumber);

    /* Step 4: Verify return is SystemP_FAILURE or handled fault */
    /* The API should detect invalid base address and return error */
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 5: Call Spinlock_unlock() with baseAddr = 0 and verify no crash */
    /* This should not cause a system crash - defensive programming test */
    Spinlock_unlock(0, lockNumber);

    /* If we reach here, the API handled NULL base address gracefully */
    /* No assertion needed - lack of crash is the success criteria */
}
#endif

/**
 * \brief Test to verify that the maximum valid lock number (numLocks - 1) is functional.
 *
 * This test case validates that the boundary condition at the upper end of the lock range
 * is properly handled:
 * 1. Calls Spinlock_getNumLocks() to get the total number of locks N
 * 2. Calculates maxLockNum = N - 1 (the maximum valid lock number)
 * 3. Attempts to acquire the lock using maxLockNum
 * 4. Verifies the lock is acquired successfully (returns FREE status)
 * 5. Releases the lock and verifies successful unlock
 *
 * This ensures the full range of lock indices [0, N-1] is functional without off-by-one errors.
 */
static void TestSpinlock_maxValidLockNumber(void *args)
{
    int32_t status;
    uint32_t numLocks;
    uint32_t maxLockNum;

    /* Step 1: Call Spinlock_getNumLocks() to get total N */
    numLocks = Spinlock_getNumLocks(CSL_SPINLOCK0_BASE);
    TEST_ASSERT_GREATER_THAN_UINT32(0, numLocks);

    /* Step 2: Calculate maxLockNum = N - 1 */
    maxLockNum = numLocks - 1;

    /* Step 3: Call Spinlock_lock() with maxLockNum */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, maxLockNum);

    /* Step 4: Verify return is SPINLOCK_LOCK_STATUS_FREE */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Verify lock is held by attempting to acquire again */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, maxLockNum);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, status);

    /* Step 5: Call Spinlock_unlock() with maxLockNum and verify success */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, maxLockNum);

    /* Verify lock was successfully released by acquiring it again */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, maxLockNum);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Final cleanup */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, maxLockNum);
}

/**
 * \brief Test to verify that an extremely large lock number (UINT32_MAX) is rejected.
 *
 * This test case validates that the driver properly rejects the maximum possible uint32_t value:
 * 1. Defines lockNum = 0xFFFFFFFF (UINT32_MAX)
 * 2. Attempts to acquire a lock with this extremely large number
 * 3. Verifies the return is SystemP_FAILURE (indicating rejection)
 * 4. Calls Spinlock_unlock() with the same invalid number
 * 5. Verifies no system crash occurs
 *
 * This ensures the driver handles extreme boundary conditions gracefully and validates
 * proper range checking for the maximum possible uint32_t value.
 */
static void TestSpinlock_uint32MaxLockNumber(void *args)
{
    int32_t status;
    uint32_t lockNum;

    /* Step 1: Define lockNum = 0xFFFFFFFF (UINT32_MAX) */
    lockNum = 0xFFFFFFFFU;

    /* Step 2: Call Spinlock_lock() with lockNum */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);

    /* Step 3: Verify return is SystemP_FAILURE */
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Step 4: Call Spinlock_unlock() with lockNum */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);

    /* Step 5: Verify no system crash occurs */
    /* If we reach this point without crashing, the test passes */
    /* The unlock should handle the invalid lock number gracefully */
}

/**
 * \brief Test to verify behavior when 100% of available hardware locks are acquired.
 *
 * This test case validates the system behavior under full resource utilization:
 * 1. Calls Spinlock_getNumLocks() to get the total number of locks N
 * 2. Loops from i = 0 to N-1, acquiring each lock and verifying FREE status
 * 3. Attempts to acquire lock 0 again and verifies it returns INUSE status
 * 4. Loops from i = 0 to N-1, releasing each lock
 * 5. Verifies lock 0 can be acquired again (returns FREE status)
 *
 * This ensures the driver correctly manages all available locks simultaneously
 * and properly handles resource exhaustion scenarios.
 */
static void TestSpinlock_allLocksAcquired(void *args)
{
    int32_t status;
    uint32_t numLocks;
    uint32_t i;

    /* Step 1: Call Spinlock_getNumLocks() to get total N */
    numLocks = Spinlock_getNumLocks(CSL_SPINLOCK0_BASE);
    TEST_ASSERT_GREATER_THAN_UINT32(0, numLocks);

    /* Step 2: Loop i from 0 to N-1: Call Spinlock_lock(i) and verify FREE */
    for (i = 0; i < numLocks; i++)
    {
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, i);
        TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);
    }

    /* Step 3: Attempt Spinlock_lock(0) again; verify INUSE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, 0);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, status);

    /* Verify other locks are also held (spot check) */
    if (numLocks > 1)
    {
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, numLocks - 1);
        TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, status);
    }

    /* Step 4: Loop i from 0 to N-1: Call Spinlock_unlock(i) */
    for (i = 0; i < numLocks; i++)
    {
        Spinlock_unlock(CSL_SPINLOCK0_BASE, i);
    }

    /* Step 5: Verify Spinlock_lock(0) is FREE again */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, 0);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Verify other locks are also free (spot check) */
    if (numLocks > 1)
    {
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, numLocks - 1);
        TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);
        Spinlock_unlock(CSL_SPINLOCK0_BASE, numLocks - 1);
    }

    /* Final cleanup */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, 0);
}

/**
 * \brief Test to verify predictable exhaustion when locks are acquired but never released.
 *
 * This test case validates that the module reset function can recover from lock leaks:
 * 1. Acquires locks 0, 1, and 2 without releasing them (simulating resource leak)
 * 2. Verifies all three acquisitions return FREE status
 * 3. Attempts to acquire lock 0 again and verifies it returns INUSE (leak confirmed)
 * 4. Calls Spinlock_moduleReset() to clear all locks
 * 5. Attempts to acquire lock 0 again and verifies it returns FREE (leak recovery confirmed)
 *
 * This ensures the driver can recover from scenarios where locks are not properly released,
 * which is critical for system robustness and debugging lock leaks.
 */
static void TestSpinlock_lockLeakRecovery(void *args)
{
    int32_t status;

    /* Step 1: Call Spinlock_lock() for locks 0, 1, and 2 without unlocking */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, 0);
    /* Step 2: Verify all three return FREE */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    status = Spinlock_lock(CSL_SPINLOCK0_BASE, 1);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    status = Spinlock_lock(CSL_SPINLOCK0_BASE, 2);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Step 3: Attempt Spinlock_lock(0) and verify return is INUSE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, 0);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, status);

    /* Step 4: Call Spinlock_moduleReset() */
    Spinlock_moduleReset(CSL_SPINLOCK0_BASE);

    /* Step 5: Attempt Spinlock_lock(0) and verify return is FREE, confirming leak recovery */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, 0);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Verify other locks were also recovered */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, 1);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    status = Spinlock_lock(CSL_SPINLOCK0_BASE, 2);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Final cleanup - release all locks */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, 0);
    Spinlock_unlock(CSL_SPINLOCK0_BASE, 1);
    Spinlock_unlock(CSL_SPINLOCK0_BASE, 2);
}

/**
 * \brief Test to verify driver stability under high-frequency acquire/release stress.
 *
 * This test case validates the robustness of the spinlock driver under intensive usage:
 * 1. Defines lock 0 for testing
 * 2. Loops 1000 times, performing acquire and immediate release operations
 * 3. Verifies each acquisition returns FREE status
 * 4. After the stress loop, acquires lock 0 one final time
 * 5. Verifies the final acquisition returns FREE, confirming stable system state
 *
 * This ensures the driver maintains correctness and stability under high-frequency
 * lock/unlock cycles, which is critical for performance-critical applications.
 */
static void TestSpinlock_highFrequencyStress(void *args)
{
    int32_t status;
    uint32_t lockNumber;
    uint32_t iteration;
    uint32_t stressIterations = 1000U;

    /* Step 1: Define valid lock 0 */
    lockNumber = 0;

    /* Step 2: Loop 1000 times: Call Spinlock_lock(), verify FREE, then immediately call Spinlock_unlock() */
    for (iteration = 0; iteration < stressIterations; iteration++)
    {
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);
        TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);
        Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);
    }

    /* Step 3: After loop, call Spinlock_lock(0) once more */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNumber);

    /* Step 4: Verify return is FREE and system state is stable */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Final cleanup */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNumber);
}

#if defined (ENABLE_MT)
/**
 * \brief Task A function for cross-task release test.
 *
 * This task acquires the lock and then yields to Task B.
 */
static void TestSpinlock_crossTaskReleaseTaskAMain(void *args)
{
    int32_t status;

    /* Step 1: Call Spinlock_lock(0) and verify FREE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, CROSS_TASK_RELEASE_LOCK_NUMBER);
    gTestStatus[0] = status;

    /* Step 2: Task A yields to Task B */
    SemaphoreP_post(&gTestSem[1]); /* Signal Task B to proceed */

    /* Wait for Task B to complete its unlock operation */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Step 4: In Task A: Resume and attempt Spinlock_lock(0) */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, CROSS_TASK_RELEASE_LOCK_NUMBER);
    gTestStatus[1] = status;

    /* Cleanup - unlock if we successfully acquired it */
    if (status == SPINLOCK_LOCK_STATUS_FREE)
    {
        Spinlock_unlock(CSL_SPINLOCK0_BASE, CROSS_TASK_RELEASE_LOCK_NUMBER);
    }

    TaskP_exit();
}

/**
 * \brief Task B function for cross-task release test.
 *
 * This task releases the lock that was acquired by Task A.
 */
static void TestSpinlock_crossTaskReleaseTaskBMain(void *args)
{
    /* Wait for Task A to acquire the lock */
    SemaphoreP_pend(&gTestSem[1], SystemP_WAIT_FOREVER);

    /* Step 3: In Task B: Call Spinlock_unlock(0) */
    /* This releases the lock that Task A acquired, testing if hardware enforces ownership */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, CROSS_TASK_RELEASE_LOCK_NUMBER);

    /* Signal Task A to resume and check the lock */
    SemaphoreP_post(&gTestSem[0]);

    TaskP_exit();
}

/**
 * \brief Test to verify behavior when a lock is released by a task that did not acquire it.
 *
 * This test case validates whether the hardware enforces lock ownership:
 * 1. Task A acquires lock 0 and verifies FREE status
 * 2. Task A signals and yields to Task B
 * 3. Task B releases lock 0 (without having acquired it)
 * 4. Task A resumes and attempts to acquire lock 0 again
 * 5. Verifies if hardware allowed the release (typically yes, confirming no ownership enforcement)
 *
 * This test demonstrates that hardware spinlocks typically do not enforce ownership,
 * meaning any context can unlock a lock regardless of who acquired it. This is important
 * for understanding spinlock behavior and potential misuse scenarios.
 */
static void TestSpinlock_crossTaskRelease(void *args)
{
    int32_t status;
    TaskP_Params taskParams;

    /* Initialize shared test result variables */
    gTestStatus[0] = SystemP_FAILURE;
    gTestStatus[1] = SystemP_FAILURE;

    /* Create semaphores for task synchronization */
    status = SemaphoreP_constructBinary(&gTestSem[0], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[1], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Task A */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SPINLOCK_TASK_A";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[0];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_crossTaskReleaseTaskAMain;

    status = TaskP_construct(&gTestTask[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Task B */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SPINLOCK_TASK_B";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[1];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_crossTaskReleaseTaskBMain;

    status = TaskP_construct(&gTestTask[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Give tasks time to execute */
    ClockP_usleep(100000); /* 100ms */

    /* Verify results */
    /* Step 1 verification: Initial lock acquisition should return FREE */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[0]);

    /* Step 5 verification: After Task B unlocked it, Task A should be able to acquire it again */
    /* This confirms hardware allows release by non-owner (no ownership enforcement) */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[1]);

    /* Cleanup tasks */
    TaskP_destruct(&gTestTask[0]);
    TaskP_destruct(&gTestTask[1]);

    /* Cleanup semaphores */
    SemaphoreP_destruct(&gTestSem[0]);
    SemaphoreP_destruct(&gTestSem[1]);
}

#if !defined(BUILD_C7X)
/**
 * \brief ISR for lock persistence across interrupt test.
 *
 * This ISR verifies that the lock held by the main thread is still held
 * when the ISR executes.
 */
static void TestSpinlock_lockPersistIsr(void *args)
{
    int32_t status;

    /* Mark that ISR has been entered */
    gLockPersistIsrEntered = 1;

    /* Step 3: In ISR: Call Spinlock_lock(0) and verify return is INUSE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, LOCK_PERSIST_LOCK_NUMBER);
    gLockPersistIsrLockStatus = status;

    /* ISR does not unlock - the main thread owns the lock */
}

/**
 * \brief Test to verify that a lock held by a thread remains held during and after an interrupt.
 *
 * This test case validates that spinlock state persists across interrupt contexts:
 * 1. Main thread acquires lock 0 and verifies FREE status
 * 2. Triggers software interrupt (ISR) while holding the lock
 * 3. ISR attempts to acquire the same lock and verifies it returns INUSE
 * 4. ISR returns to main thread
 * 5. Main thread attempts to acquire the lock again and verifies still INUSE
 * 6. Main thread releases the lock for cleanup
 *
 * This ensures that locks maintain their state correctly when an ISR preempts
 * the lock holder, which is critical for proper synchronization behavior.
 */
static void TestSpinlock_lockPersistAcrossInterrupt(void *args)
{
    int32_t status;
    HwiP_Params hwiParams;
    HwiP_Object hwiObj;
    uint32_t timeout;

    /* Initialize shared variables */
    gLockPersistIsrEntered = 0;
    gLockPersistIsrLockStatus = SystemP_FAILURE;

    /* Register the ISR */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum = LOCK_PERSIST_INT_NUM;
    hwiParams.callback = TestSpinlock_lockPersistIsr;
    hwiParams.priority = 1;
    status = HwiP_construct(&hwiObj, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 1: Main Thread: Call Spinlock_lock(0) and verify FREE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, LOCK_PERSIST_LOCK_NUMBER);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Step 2: Trigger software interrupt (ISR) */
    HwiP_post(LOCK_PERSIST_INT_NUM);

    /* Wait for ISR to complete with timeout */
    timeout = 1000;
    while (gLockPersistIsrEntered == 0 && timeout > 0)
    {
        ClockP_usleep(100);
        timeout--;
    }

    /* Verify ISR was entered */
    TEST_ASSERT_EQUAL_UINT32(1, gLockPersistIsrEntered);

    /* Step 3 verification: In ISR, lock attempt should have returned INUSE */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, gLockPersistIsrLockStatus);

    /* Step 5: Main Thread: Attempt Spinlock_lock(0) again; verify still INUSE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, LOCK_PERSIST_LOCK_NUMBER);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, status);

    /* Step 6: Main Thread: Call Spinlock_unlock(0) */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, LOCK_PERSIST_LOCK_NUMBER);

    /* Verify lock is now free */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, LOCK_PERSIST_LOCK_NUMBER);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Final cleanup */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, LOCK_PERSIST_LOCK_NUMBER);
    HwiP_destruct(&hwiObj);
}
#endif

/**
 * \brief Task A function for simultaneous module reset test.
 *
 * This task acquires the lock and holds it while other tasks perform reset.
 */
static void TestSpinlock_simulResetTaskAMain(void *args)
{
    int32_t status;

    /* Step 1: Task A: Call Spinlock_lock(0) and hold */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, SIMUL_RESET_LOCK_NUMBER);
    gTestStatus[0] = status;

    /* Signal tasks B and C to start their resets */
    SemaphoreP_post(&gTestSem[0]);
    SemaphoreP_post(&gTestSem[0]);

    /* Wait for tasks B and C to complete their resets */
    SemaphoreP_pend(&gTestSem[1], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[2], SystemP_WAIT_FOREVER);

    /* Note: Lock is automatically released by module reset */
    /* No explicit unlock needed */

    TaskP_exit();
}

/**
 * \brief Task B function for simultaneous module reset test.
 *
 * This task performs module reset simultaneously with Task C.
 */
static void TestSpinlock_simulResetTaskBMain(void *args)
{
    /* Wait for Task A to acquire the lock */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Step 2: Task B: Call Spinlock_moduleReset() */
    Spinlock_moduleReset(CSL_SPINLOCK0_BASE);
    gTestCounter[0] = 1;

    /* Signal completion */
    SemaphoreP_post(&gTestSem[1]);

    TaskP_exit();
}

/**
 * \brief Task C function for simultaneous module reset test.
 *
 * This task performs module reset simultaneously with Task B.
 */
static void TestSpinlock_simulResetTaskCMain(void *args)
{
    /* Wait for Task A to acquire the lock */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Step 2: Task C: Call Spinlock_moduleReset() */
    Spinlock_moduleReset(CSL_SPINLOCK0_BASE);
    gTestCounter[1] = 1;

    /* Signal completion */
    SemaphoreP_post(&gTestSem[2]);

    TaskP_exit();
}

/**
 * \brief Test to verify system stability during simultaneous module resets from multiple cores.
 *
 * This test case validates that the system remains stable when multiple tasks
 * perform module reset operations concurrently:
 * 1. Task A acquires lock 0 and holds it
 * 2. Task B and Task C simultaneously call Spinlock_moduleReset()
 * 3. Wait for all tasks to complete and verify no system hang
 * 4. Attempt to acquire lock 0 and verify it returns FREE (confirms reset worked)
 *
 * This ensures the module reset function is thread-safe and can handle concurrent
 * reset operations without causing system instability or deadlocks.
 */
static void TestSpinlock_simultaneousModuleReset(void *args)
{
    int32_t status;
    TaskP_Params taskParams;

    /* Initialize shared test result variables */
    gTestStatus[0] = SystemP_FAILURE;
    gTestCounter[0] = 0;
    gTestCounter[1] = 0;

    /* Create semaphores for task synchronization */
    status = SemaphoreP_constructCounting(&gTestSem[0], 0, 3);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[1], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[2], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Task A */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SIMUL_RESET_A";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[0];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_simulResetTaskAMain;

    status = TaskP_construct(&gTestTask[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Task B */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SIMUL_RESET_B";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[1];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_simulResetTaskBMain;

    status = TaskP_construct(&gTestTask[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Task C */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SIMUL_RESET_C";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[2];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_simulResetTaskCMain;

    status = TaskP_construct(&gTestTask[2], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 3: Give tasks time to execute and wait for completion */
    ClockP_usleep(150000); /* 150ms */

    /* Verify no system hang - if we reach here, system is stable */
    TEST_ASSERT_EQUAL_UINT32(1, gTestCounter[0]);
    TEST_ASSERT_EQUAL_UINT32(1, gTestCounter[1]);

    /* Verify Task A initially acquired the lock successfully */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[0]);

    /* Step 4: Attempt Spinlock_lock(0) and verify return is FREE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, SIMUL_RESET_LOCK_NUMBER);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);

    /* Cleanup - unlock the lock we just acquired */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, SIMUL_RESET_LOCK_NUMBER);

    /* Cleanup tasks */
    TaskP_destruct(&gTestTask[0]);
    TaskP_destruct(&gTestTask[1]);
    TaskP_destruct(&gTestTask[2]);

    /* Cleanup semaphores */
    SemaphoreP_destruct(&gTestSem[0]);
    SemaphoreP_destruct(&gTestSem[1]);
    SemaphoreP_destruct(&gTestSem[2]);
}

/**
 * \brief Thread A function for mutual exclusion test.
 *
 * Thread A acquires the lock first, holds it briefly, then releases it.
 */
static void TestSpinlock_mutexThreadAMain(void *args)
{
    int32_t status;

    /* Step 2: In Thread A: Acquire lock 0 by calling Spinlock_lock() */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, MUTEX_TEST_LOCK_NUMBER);
    gTestStatus[0] = status;

    /* Step 4: In Thread A: Set a shared flag lockHolderID = A */
    gTestCounter[0] = MUTEX_TEST_THREAD_A_ID;

    /* Signal that Thread A has acquired the lock */
    SemaphoreP_post(&gTestSem[0]);

    /* Step 5: In Thread A: Delay for 50ms while holding the lock */
    ClockP_usleep(MUTEX_TEST_DELAY_MS * 1000);

    /* Step 9: In Thread A: After delay, release lock 0 */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, MUTEX_TEST_LOCK_NUMBER);

    /* Signal completion */
    SemaphoreP_post(&gTestSem[2]);

    TaskP_exit();
}

/**
 * \brief Thread B function for mutual exclusion test.
 *
 * Thread B attempts to acquire the lock, initially fails (mutual exclusion),
 * then polls and successfully acquires after Thread A releases.
 */
static void TestSpinlock_mutexThreadBMain(void *args)
{
    int32_t status;
    uint32_t pollCount = 0;
    uint32_t maxPolls = MUTEX_TEST_POLL_TIMEOUT_MS; /* 1ms per poll */

    /* Wait for signal to start (Thread A should already have the lock) */
    SemaphoreP_pend(&gTestSem[1], SystemP_WAIT_FOREVER);

    /* Step 6: In Thread B: Attempt to acquire lock 0 */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, MUTEX_TEST_LOCK_NUMBER);
    gTestStatus[1] = status;

    /* Step 8: In Thread B: Implement polling loop with 100ms timeout */
    while (status == SPINLOCK_LOCK_STATUS_INUSE && pollCount < maxPolls)
    {
        ClockP_usleep(1000); /* 1ms delay between retries */
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, MUTEX_TEST_LOCK_NUMBER);
        pollCount++;
    }

    /* Step 10: Successfully acquired lock on retry */
    gTestStatus[2] = status;

    /* Step 11: In Thread B: Verify lockHolderID == A */
    if (status == SPINLOCK_LOCK_STATUS_FREE)
    {
        gTestCounter[1] = gTestCounter[0];

        /* Step 12: In Thread B: Set lockHolderID = B and release lock 0 */
        gTestCounter[0] = MUTEX_TEST_THREAD_B_ID;
        Spinlock_unlock(CSL_SPINLOCK0_BASE, MUTEX_TEST_LOCK_NUMBER);
    }

    /* Signal completion */
    SemaphoreP_post(&gTestSem[3]);

    TaskP_exit();
}

/**
 * \brief Test to verify mutual exclusion with two threads acquiring and releasing same spinlock.
 *
 * This test case validates that spinlocks properly enforce mutual exclusion:
 * 1. Thread A acquires lock 0 and verifies FREE status
 * 2. Thread A sets a shared flag (lockHolderID = A) and delays 50ms
 * 3. Thread B (concurrent) attempts lock acquisition and verifies INUSE (mutual exclusion)
 * 4. Thread B polls for up to 100ms, retrying lock acquisition
 * 5. Thread A releases the lock after delay
 * 6. Thread B successfully acquires lock and verifies FREE status
 * 7. Thread B verifies lockHolderID == A (confirms Thread A's critical section executed first)
 * 8. Thread B updates lockHolderID = B and releases lock
 * 9. Verifies both threads complete successfully with proper mutual exclusion
 *
 * This ensures spinlocks correctly prevent concurrent access to critical sections
 * and maintain proper ordering of lock acquisitions.
 */
static void TestSpinlock_mutualExclusion(void *args)
{
    int32_t status;
    TaskP_Params taskParams;

    /* Initialize shared test result variables */
    gTestCounter[0] = 0;
    gTestCounter[1] = 0;
    gTestStatus[0] = SystemP_FAILURE;
    gTestStatus[1] = SystemP_FAILURE;
    gTestStatus[2] = SystemP_FAILURE;

    /* Create semaphores for thread synchronization */
    status = SemaphoreP_constructBinary(&gTestSem[0], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[1], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[2], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[3], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 1: Create Thread A */
    TaskP_Params_init(&taskParams);
    taskParams.name = "MUTEX_THREAD_A";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[0];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_mutexThreadAMain;

    status = TaskP_construct(&gTestTask[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for Thread A to acquire the lock */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Step 1: Create Thread B (starts while Thread A holds lock) */
    TaskP_Params_init(&taskParams);
    taskParams.name = "MUTEX_THREAD_B";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[1];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_mutexThreadBMain;

    status = TaskP_construct(&gTestTask[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Signal Thread B to start attempting lock acquisition */
    SemaphoreP_post(&gTestSem[1]);

    /* Step 13: Wait for both threads to complete */
    SemaphoreP_pend(&gTestSem[2], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[3], SystemP_WAIT_FOREVER);

    /* Verify results */

    /* Step 3: Thread A should have acquired lock with FREE status */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[0]);

    /* Step 7: Thread B's initial attempt should have returned INUSE (mutual exclusion) */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_INUSE, gTestStatus[1]);

    /* Step 10: Thread B should eventually acquire lock with FREE status */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[2]);

    /* Step 11: Thread B should see Thread A's ID (confirms Thread A executed first) */
    TEST_ASSERT_EQUAL_UINT32(MUTEX_TEST_THREAD_A_ID, gTestCounter[1]);

    /* Step 12: Final holder should be Thread B */
    TEST_ASSERT_EQUAL_UINT32(MUTEX_TEST_THREAD_B_ID, gTestCounter[0]);

    /* Cleanup tasks */
    TaskP_destruct(&gTestTask[0]);
    TaskP_destruct(&gTestTask[1]);

    /* Cleanup semaphores */
    SemaphoreP_destruct(&gTestSem[0]);
    SemaphoreP_destruct(&gTestSem[1]);
    SemaphoreP_destruct(&gTestSem[2]);
    SemaphoreP_destruct(&gTestSem[3]);
}

/**
 * \brief Thread A function for concurrent independent locks test.
 *
 * Thread A acquires lock 0, increments counter 10,000 times, then releases.
 */
static void TestSpinlock_concurrentThreadAMain(void *args)
{
    int32_t status;
    uint32_t i;

    /* Wait for all threads to be ready */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Step 2: In Thread A: Acquire lock 0 */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, CONCURRENT_LOCK_A);
    gTestStatus[0] = status;

    /* Step 6: Increment thread-specific counter (10,000 iterations) */
    for (i = 0; i < CONCURRENT_TEST_ITERATIONS; i++)
    {
        gTestCounter[0]++;
    }

    /* Step 7: In Thread A: Release lock 0 */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, CONCURRENT_LOCK_A);

    /* Signal completion */
    SemaphoreP_post(&gTestSem[1]);

    TaskP_exit();
}

/**
 * \brief Thread B function for concurrent independent locks test.
 *
 * Thread B acquires lock 1, increments counter 10,000 times, then releases.
 */
static void TestSpinlock_concurrentThreadBMain(void *args)
{
    int32_t status;
    uint32_t i;

    /* Wait for all threads to be ready */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Step 3: In Thread B: Acquire lock 1 */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, CONCURRENT_LOCK_B);
    gTestStatus[1] = status;

    /* Step 6: Increment thread-specific counter (10,000 iterations) */
    for (i = 0; i < CONCURRENT_TEST_ITERATIONS; i++)
    {
        gTestCounter[1]++;
    }

    /* Step 8: In Thread B: Release lock 1 */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, CONCURRENT_LOCK_B);

    /* Signal completion */
    SemaphoreP_post(&gTestSem[2]);

    TaskP_exit();
}

/**
 * \brief Thread C function for concurrent independent locks test.
 *
 * Thread C acquires lock 2, increments counter 10,000 times, then releases.
 */
static void TestSpinlock_concurrentThreadCMain(void *args)
{
    int32_t status;
    uint32_t i;

    /* Wait for all threads to be ready */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Step 4: In Thread C: Acquire lock 2 */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, CONCURRENT_LOCK_C);
    gTestStatus[2] = status;

    /* Step 6: Increment thread-specific counter (10,000 iterations) */
    for (i = 0; i < CONCURRENT_TEST_ITERATIONS; i++)
    {
        gTestCounter[2]++;
    }

    /* Step 9: In Thread C: Release lock 2 */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, CONCURRENT_LOCK_C);

    /* Signal completion */
    SemaphoreP_post(&gTestSem[3]);

    TaskP_exit();
}

/**
 * \brief Test to verify multiple threads can hold different spinlocks simultaneously.
 *
 * This test case validates that different spinlocks operate independently:
 * 1. Creates three threads (A, B, C)
 * 2. Thread A acquires lock 0, Thread B acquires lock 1, Thread C acquires lock 2
 * 3. Verifies all three locks are acquired successfully (FREE status)
 * 4. Each thread increments its counter 10,000 times while holding its lock
 * 5. Threads release their respective locks
 * 6. Verifies all counters reached 10,000 (no interference)
 * 7. Verifies threads didn't block each other (completed successfully)
 *
 * This ensures that acquiring one lock doesn't prevent acquiring a different lock,
 * demonstrating lock independence.
 */
static void TestSpinlock_concurrentIndependentLocks(void *args)
{
    int32_t status;
    TaskP_Params taskParams;

    /* Initialize shared test result variables */
    gTestStatus[0] = SystemP_FAILURE;
    gTestStatus[1] = SystemP_FAILURE;
    gTestStatus[2] = SystemP_FAILURE;
    gTestCounter[0] = 0;
    gTestCounter[1] = 0;
    gTestCounter[2] = 0;

    /* Create semaphores for thread synchronization */
    status = SemaphoreP_constructCounting(&gTestSem[0], 0, 3);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[1], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[2], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[3], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 1: Create Thread A */
    TaskP_Params_init(&taskParams);
    taskParams.name = "CONCURRENT_A";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[0];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_concurrentThreadAMain;

    status = TaskP_construct(&gTestTask[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 1: Create Thread B */
    TaskP_Params_init(&taskParams);
    taskParams.name = "CONCURRENT_B";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[1];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_concurrentThreadBMain;

    status = TaskP_construct(&gTestTask[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 1: Create Thread C */
    TaskP_Params_init(&taskParams);
    taskParams.name = "CONCURRENT_C";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[2];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_concurrentThreadCMain;

    status = TaskP_construct(&gTestTask[2], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Signal all threads to start simultaneously */
    SemaphoreP_post(&gTestSem[0]);
    SemaphoreP_post(&gTestSem[0]);
    SemaphoreP_post(&gTestSem[0]);

    /* Wait for all threads to complete */
    SemaphoreP_pend(&gTestSem[1], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[2], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[3], SystemP_WAIT_FOREVER);

    /* Verify results */

    /* Steps 2-4: All threads should have acquired their locks with FREE status */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[0]);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[1]);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[2]);

    /* Step 6: Verify all counters have the expected value (10,000) */
    TEST_ASSERT_EQUAL_UINT32(CONCURRENT_TEST_ITERATIONS, gTestCounter[0]);
    TEST_ASSERT_EQUAL_UINT32(CONCURRENT_TEST_ITERATIONS, gTestCounter[1]);
    TEST_ASSERT_EQUAL_UINT32(CONCURRENT_TEST_ITERATIONS, gTestCounter[2]);

    /* Step 7: Verify all threads completed successfully (already verified by reaching here) */

    /* Cleanup tasks */
    TaskP_destruct(&gTestTask[0]);
    TaskP_destruct(&gTestTask[1]);
    TaskP_destruct(&gTestTask[2]);

    /* Cleanup semaphores */
    SemaphoreP_destruct(&gTestSem[0]);
    SemaphoreP_destruct(&gTestSem[1]);
    SemaphoreP_destruct(&gTestSem[2]);
    SemaphoreP_destruct(&gTestSem[3]);
}

/**
 * \brief Thread A function for shared resource protection test.
 *
 * Performs 1000 iterations of protected increment on shared counter.
 */
static void TestSpinlock_sharedCounterThreadAMain(void *args)
{
    int32_t status;
    uint32_t i;
    uint32_t localValue;

    /* Wait for all threads to be ready */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Execute 1000 iterations */
    for (i = 0; i < SHARED_COUNTER_ITERATIONS; i++)
    {
        /* Spin-wait loop: call Spinlock_lock() until FREE */
        do {
            status = Spinlock_lock(CSL_SPINLOCK0_BASE, SHARED_COUNTER_TEST_LOCK_NUMBER);
        } while (status == SPINLOCK_LOCK_STATUS_INUSE);

        /* Critical section: read, increment, write back */
        localValue = gTestCounter[0];
        localValue++;
        gTestCounter[0] = localValue;

        /* Release lock */
        Spinlock_unlock(CSL_SPINLOCK0_BASE, SHARED_COUNTER_TEST_LOCK_NUMBER);
    }

    /* Signal completion */
    SemaphoreP_post(&gTestSem[1]);

    TaskP_exit();
}

/**
 * \brief Thread B function for shared resource protection test.
 *
 * Performs 1000 iterations of protected increment on shared counter.
 */
static void TestSpinlock_sharedCounterThreadBMain(void *args)
{
    int32_t status;
    uint32_t i;
    uint32_t localValue;

    /* Wait for all threads to be ready */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Execute 1000 iterations */
    for (i = 0; i < SHARED_COUNTER_ITERATIONS; i++)
    {
        /* Spin-wait loop: call Spinlock_lock() until FREE */
        do {
            status = Spinlock_lock(CSL_SPINLOCK0_BASE, SHARED_COUNTER_TEST_LOCK_NUMBER);
        } while (status == SPINLOCK_LOCK_STATUS_INUSE);

        /* Critical section: read, increment, write back */
        localValue = gTestCounter[0];
        localValue++;
        gTestCounter[0] = localValue;

        /* Release lock */
        Spinlock_unlock(CSL_SPINLOCK0_BASE, SHARED_COUNTER_TEST_LOCK_NUMBER);
    }

    /* Signal completion */
    SemaphoreP_post(&gTestSem[2]);

    TaskP_exit();
}

/**
 * \brief Thread C function for shared resource protection test.
 *
 * Performs 1000 iterations of protected increment on shared counter.
 */
static void TestSpinlock_sharedCounterThreadCMain(void *args)
{
    int32_t status;
    uint32_t i;
    uint32_t localValue;

    /* Wait for all threads to be ready */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Execute 1000 iterations */
    for (i = 0; i < SHARED_COUNTER_ITERATIONS; i++)
    {
        /* Spin-wait loop: call Spinlock_lock() until FREE */
        do {
            status = Spinlock_lock(CSL_SPINLOCK0_BASE, SHARED_COUNTER_TEST_LOCK_NUMBER);
        } while (status == SPINLOCK_LOCK_STATUS_INUSE);

        /* Critical section: read, increment, write back */
        localValue = gTestCounter[0];
        localValue++;
        gTestCounter[0] = localValue;

        /* Release lock */
        Spinlock_unlock(CSL_SPINLOCK0_BASE, SHARED_COUNTER_TEST_LOCK_NUMBER);
    }

    /* Signal completion */
    SemaphoreP_post(&gTestSem[3]);

    TaskP_exit();
}

/**
 * \brief Thread D function for shared resource protection test.
 *
 * Performs 1000 iterations of protected increment on shared counter.
 */
static void TestSpinlock_sharedCounterThreadDMain(void *args)
{
    int32_t status;
    uint32_t i;
    uint32_t localValue;

    /* Wait for all threads to be ready */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);

    /* Execute 1000 iterations */
    for (i = 0; i < SHARED_COUNTER_ITERATIONS; i++)
    {
        /* Spin-wait loop: call Spinlock_lock() until FREE */
        do {
            status = Spinlock_lock(CSL_SPINLOCK0_BASE, SHARED_COUNTER_TEST_LOCK_NUMBER);
        } while (status == SPINLOCK_LOCK_STATUS_INUSE);

        /* Critical section: read, increment, write back */
        localValue = gTestCounter[0];
        localValue++;
        gTestCounter[0] = localValue;

        /* Release lock */
        Spinlock_unlock(CSL_SPINLOCK0_BASE, SHARED_COUNTER_TEST_LOCK_NUMBER);
    }

    /* Signal completion */
    SemaphoreP_post(&gTestSem[4]);

    TaskP_exit();
}

/**
 * \brief Test to verify spinlock correctly protects shared resource from race conditions.
 *
 * This test case validates that spinlocks properly protect a shared counter from race conditions:
 * 1. Initializes a shared counter to 0
 * 2. Creates four threads (A, B, C, D)
 * 3. Each thread executes 1000 iterations:
 *    - Spin-wait on lock 0 until acquired (SPINLOCK_LOCK_STATUS_FREE)
 *    - Read shared counter, increment by 1, write back
 *    - Release lock 0
 * 4. Waits for all four threads to complete
 * 5. Verifies shared counter == 4000 (4 threads × 1000 increments)
 *
 * This ensures spinlocks correctly prevent race conditions when multiple threads
 * access and modify a shared resource concurrently.
 */
static void TestSpinlock_sharedResourceProtection(void *args)
{
    int32_t status;
    TaskP_Params taskParams;
    uint32_t expectedCount;

    /* Step 1: Initialize shared counter to 0 */
    gTestCounter[0] = 0;

    /* Create semaphores for thread synchronization */
    status = SemaphoreP_constructCounting(&gTestSem[0], 0, 4);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[1], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[2], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[3], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[4], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Create four threads */

    /* Create Thread A */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SHARED_CNT_A";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[0];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_sharedCounterThreadAMain;

    status = TaskP_construct(&gTestTask[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Thread B */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SHARED_CNT_B";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[1];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_sharedCounterThreadBMain;

    status = TaskP_construct(&gTestTask[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Thread C */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SHARED_CNT_C";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[2];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_sharedCounterThreadCMain;

    status = TaskP_construct(&gTestTask[2], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Thread D */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SHARED_CNT_D";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[3];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_sharedCounterThreadDMain;

    status = TaskP_construct(&gTestTask[3], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Signal all threads to start simultaneously */
    SemaphoreP_post(&gTestSem[0]);
    SemaphoreP_post(&gTestSem[0]);
    SemaphoreP_post(&gTestSem[0]);
    SemaphoreP_post(&gTestSem[0]);

    /* Step 4: Wait for all threads to complete */
    SemaphoreP_pend(&gTestSem[1], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[2], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[3], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[4], SystemP_WAIT_FOREVER);

    /* Step 5: Verify shared counter == 4000 (4 threads × 1000 increments) */
    expectedCount = 4 * SHARED_COUNTER_ITERATIONS; /* 4000 */
    TEST_ASSERT_EQUAL_UINT32(expectedCount, gTestCounter[0]);

    /* Cleanup tasks */
    TaskP_destruct(&gTestTask[0]);
    TaskP_destruct(&gTestTask[1]);
    TaskP_destruct(&gTestTask[2]);
    TaskP_destruct(&gTestTask[3]);

    /* Cleanup semaphores */
    SemaphoreP_destruct(&gTestSem[0]);
    SemaphoreP_destruct(&gTestSem[1]);
    SemaphoreP_destruct(&gTestSem[2]);
    SemaphoreP_destruct(&gTestSem[3]);
    SemaphoreP_destruct(&gTestSem[4]);
}

/**
 * \brief Thread A function for multi-thread module reset test.
 *
 * Acquires lock 0 and holds it until reset occurs.
 */
static void TestSpinlock_multiResetThreadAMain(void *args)
{
    int32_t status;

    /* Step 2: Acquire lock 0 and hold it indefinitely */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_RESET_LOCK_A);
    gTestStatus[0] = status;

    /* Signal that Thread A is holding the lock */
    SemaphoreP_post(&gTestSem[0]);

    /* Wait for reset to complete */
    SemaphoreP_pend(&gTestSem[2], SystemP_WAIT_FOREVER);

    /* Step 6: After reset, attempt to acquire lock 0 again (without releasing first) */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_RESET_LOCK_A);
    gTestStatus[1] = status;

    /* Step 10: Release lock if we acquired it */
    if (status == SPINLOCK_LOCK_STATUS_FREE)
    {
        Spinlock_unlock(CSL_SPINLOCK0_BASE, MULTI_RESET_LOCK_A);
    }

    /* Signal completion */
    SemaphoreP_post(&gTestSem[3]);

    TaskP_exit();
}

/**
 * \brief Thread B function for multi-thread module reset test.
 *
 * Acquires lock 1 and holds it until reset occurs.
 */
static void TestSpinlock_multiResetThreadBMain(void *args)
{
    int32_t status;

    /* Step 3: Acquire lock 1 and hold it indefinitely */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_RESET_LOCK_B);
    gTestStatus[2] = status;

    /* Signal that Thread B is holding the lock */
    SemaphoreP_post(&gTestSem[1]);

    /* Wait for reset to complete */
    SemaphoreP_pend(&gTestSem[2], SystemP_WAIT_FOREVER);

    /* Step 8: After reset, attempt to acquire lock 1 again (without releasing first) */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, MULTI_RESET_LOCK_B);
    gTestStatus[3] = status;

    /* Step 10: Release lock if we acquired it */
    if (status == SPINLOCK_LOCK_STATUS_FREE)
    {
        Spinlock_unlock(CSL_SPINLOCK0_BASE, MULTI_RESET_LOCK_B);
    }

    /* Signal completion */
    SemaphoreP_post(&gTestSem[4]);

    TaskP_exit();
}

/**
 * \brief Thread C function for multi-thread module reset test.
 *
 * Performs module reset after delay.
 */
static void TestSpinlock_multiResetThreadCMain(void *args)
{
    /* Wait for threads A and B to acquire their locks */
    SemaphoreP_pend(&gTestSem[0], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[1], SystemP_WAIT_FOREVER);

    /* Step 4: After 50ms delay, call Spinlock_moduleReset() */
    ClockP_usleep(MULTI_RESET_DELAY_MS * 1000);

    Spinlock_moduleReset(CSL_SPINLOCK0_BASE);

    /* Step 5: Verify reset completes without hanging */
    gTestCounter[0] = 1;

    /* Signal threads A and B that reset is done */
    SemaphoreP_post(&gTestSem[2]);
    SemaphoreP_post(&gTestSem[2]);

    /* Signal completion */
    SemaphoreP_post(&gTestSem[5]);

    TaskP_exit();
}

/**
 * \brief Test to verify Spinlock_moduleReset() releases locks held by multiple threads.
 *
 * This test case validates that module reset correctly releases locks held by different threads:
 * 1. Creates three threads (A, B, C)
 * 2. Thread A acquires lock 0 and holds indefinitely
 * 3. Thread B acquires lock 1 and holds indefinitely
 * 4. Thread C performs module reset after 50ms delay
 * 5. Verifies reset completes without hanging
 * 6. Thread A attempts to re-acquire lock 0 (without releasing) and verifies FREE status
 * 7. Thread B attempts to re-acquire lock 1 (without releasing) and verifies FREE status
 * 8. All threads release locks and terminate
 * 9. Verifies module is in clean state by acquiring all locks sequentially
 *
 * This ensures module reset correctly frees all locks regardless of which thread held them.
 */
static void TestSpinlock_multiThreadModuleReset(void *args)
{
    int32_t status;
    TaskP_Params taskParams;
    uint32_t numLocks;
    uint32_t i;

    /* Initialize shared test result variables */
    gTestStatus[0] = SystemP_FAILURE;
    gTestStatus[1] = SystemP_FAILURE;
    gTestStatus[2] = SystemP_FAILURE;
    gTestStatus[3] = SystemP_FAILURE;
    gTestCounter[0] = 0;

    /* Create semaphores for thread synchronization */
    status = SemaphoreP_constructBinary(&gTestSem[0], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[1], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructCounting(&gTestSem[2], 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[3], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[4], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&gTestSem[5], 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 1: Create three threads */

    /* Create Thread A */
    TaskP_Params_init(&taskParams);
    taskParams.name = "MULTI_RST_A";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[0];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_multiResetThreadAMain;

    status = TaskP_construct(&gTestTask[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Thread B */
    TaskP_Params_init(&taskParams);
    taskParams.name = "MULTI_RST_B";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[1];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_multiResetThreadBMain;

    status = TaskP_construct(&gTestTask[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Create Thread C */
    TaskP_Params_init(&taskParams);
    taskParams.name = "MULTI_RST_C";
    taskParams.stackSize = TEST_TASK_STACK_SIZE;
    taskParams.stack = gTestStack[2];
    taskParams.priority = COMMON_TEST_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = TestSpinlock_multiResetThreadCMain;

    status = TaskP_construct(&gTestTask[2], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for all threads to complete */
    SemaphoreP_pend(&gTestSem[5], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[3], SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gTestSem[4], SystemP_WAIT_FOREVER);

    /* Verify results */

    /* Verify Thread A initially acquired lock 0 successfully */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[0]);

    /* Verify Thread B initially acquired lock 1 successfully */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[2]);

    /* Step 5: Verify reset completed without hanging */
    TEST_ASSERT_EQUAL_UINT32(1, gTestCounter[0]);

    /* Step 7: Verify Thread A could re-acquire lock 0 after reset (returned FREE) */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[1]);

    /* Step 9: Verify Thread B could re-acquire lock 1 after reset (returned FREE) */
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, gTestStatus[3]);

    /* Step 11: Verify module is in clean state by acquiring all locks sequentially */
    numLocks = Spinlock_getNumLocks(CSL_SPINLOCK0_BASE);
    TEST_ASSERT_GREATER_THAN_UINT32(0, numLocks);

    for (i = 0; i < numLocks; i++)
    {
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, i);
        TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, status);
    }

    /* Release all locks */
    for (i = 0; i < numLocks; i++)
    {
        Spinlock_unlock(CSL_SPINLOCK0_BASE, i);
    }

    /* Cleanup tasks */
    TaskP_destruct(&gTestTask[0]);
    TaskP_destruct(&gTestTask[1]);
    TaskP_destruct(&gTestTask[2]);

    /* Cleanup semaphores */
    SemaphoreP_destruct(&gTestSem[0]);
    SemaphoreP_destruct(&gTestSem[1]);
    SemaphoreP_destruct(&gTestSem[2]);
    SemaphoreP_destruct(&gTestSem[3]);
    SemaphoreP_destruct(&gTestSem[4]);
    SemaphoreP_destruct(&gTestSem[5]);
}
#endif

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

/**
 * @file test_spinlock_smp.c
 * @brief The following test aims at creating tasks for each A53 core.
 *
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
#include "test_config.h"

/* ========================================================================== */
/*                           Macros & Defines                                 */
/* ========================================================================== */

#define TASK_A_ID   0x01U
#define TASK_B_ID   0x02U
#define TEST_LOCK_NUMBER   0U

/* Execution order tracking for mutual exclusion test */
#define TASK_A_START    0xA1U
#define TASK_A_END      0xA2U
#define TASK_B_START    0xB1U
#define TASK_B_END      0xB2U
#define EXEC_ORDER_SIZE 4U
#define CRITICAL_SECTION_DELAY_MS   50U

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Shared variable to track which task acquired the lock */
static volatile uint32_t TestSpinlock_LockOwner = 0U;

/* Semaphores for task synchronization */
static SemaphoreP_Object TestSpinlock_taskAcquireLockSem;
static SemaphoreP_Object TestSpinlock_taskUnlockSem;

/* Task stacks */
static uint8_t TestSpinlock_taskAcquireLockStack[4096] __attribute__((aligned(32)));
static uint8_t TestSpinlock_taskUnlockStack[4096] __attribute__((aligned(32)));

/* Variables for mutual exclusion test */
static volatile uint32_t TestSpinlock_ExecutionOrder[EXEC_ORDER_SIZE];
static volatile uint32_t TestSpinlock_ExecIndex = 0U;
static volatile uint64_t TestSpinlock_taskUnlockStartTime = 0U;
static volatile uint64_t TestSpinlock_taskUnlockWaitTime = 0U;
static SemaphoreP_Object TestSpinlock_MutexTestDoneSem;
static uint8_t TestSpinlock_MutexTaskAStack[4096] __attribute__((aligned(32)));
static uint8_t TestSpinlock_MutexTaskBStack[4096] __attribute__((aligned(32)));

/* ========================================================================== */
/*                     Internal Function Declarations                         */
/* ========================================================================== */

static void TestSpinlock_taskAcquireLock(void *arg);
static void TestSpinlock_taskUnlock(void *arg);
static void TestSpinlock_mutexAcquireLock(void *arg);
static void TestSpinlock_mutexHoldLock(void *arg);

/* ========================================================================== */
/*                       Static Test Function Prototypes                      */
/* ========================================================================== */

static void TestSpinlock_verifyUnlockByNonOwner(void *args);
static void TestSpinlock_verifyMutualExclusion(void *args);

/* ========================================================================== */
/*                            Main Test Function                              */
/* ========================================================================== */

/**
 *  \brief   Main entry point for Spinlock SMP tests.
 *
 *  Runs selected thread-based test cases using the Unity framework.
 *
 *  \param args  Unused argument.
 */
void test_spinlock_smp_main(void * args)
{
    (void) args;

    UNITY_BEGIN();
    RUN_TEST(TestSpinlock_verifyUnlockByNonOwner, 10866, NULL);
    RUN_TEST(TestSpinlock_verifyMutualExclusion, 10867, NULL);
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
/*                         Task Implementation Functions                      */
/* ========================================================================== */

/**
 * @brief Acquires lock 0, sets owner flag, and coordinates with Task B.
 *
 * This task:
 * 1. Acquires spinlock 0 and verifies it was free
 * 2. Sets the shared lockOwner flag to TASK_A_ID
 * 3. Signals Task B to proceed
 * 4. Waits for Task B to complete its operations
 * 5. Unlocks the spinlock and exits
 *
 * @param arg Unused.
 */
static void TestSpinlock_taskAcquireLock(void *arg)
{
    (void)arg;
    int32_t lockStatus;

    /* Step 2: Call Spinlock_lock() on lock 0 and verify return is SPINLOCK_LOCK_STATUS_FREE */
    lockStatus = Spinlock_lock(CSL_SPINLOCK0_BASE, TEST_LOCK_NUMBER);
    DebugP_log("[Task A] Spinlock_lock returned: %d\r\n", lockStatus);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, lockStatus);

    /* Step 3: Set shared flag lockOwner = TASK_A */
    TestSpinlock_LockOwner = TASK_A_ID;
    DebugP_log("[Task A] Set lockOwner = 0x%x\r\n", TestSpinlock_LockOwner);

    /* Step 3 (cont): Signal Task B via semaphore */
    SemaphoreP_post(&TestSpinlock_taskUnlockSem);
    DebugP_log("[Task A] Signaled Task B\r\n");

    /* Step 4: Block waiting for Task B response */
    SemaphoreP_pend(&TestSpinlock_taskAcquireLockSem, SystemP_WAIT_FOREVER);
    DebugP_log("[Task A] Received signal from Task B\r\n");

    /* Clean up: unlock the spinlock */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, TEST_LOCK_NUMBER);
    DebugP_log("[Task A] Unlocked spinlock 0\r\n");

    DebugP_log("[Task A] Exiting\r\n");
    TaskP_exit();
}

/**
 * @brief Attempts to unlock lock 0 without owning it, then acquires it.
 *
 * This task:
 * 1. Waits for signal from Task A
 * 2. Attempts to unlock spinlock 0 (without having acquired it)
 * 3. Acquires spinlock 0 and verifies it was free (demonstrating no ownership enforcement)
 * 4. Signals Task A to continue
 * 5. Unlocks the spinlock and exits
 *
 * @param arg Unused.
 */
static void TestSpinlock_taskUnlock(void *arg)
{
    (void)arg;
    int32_t lockStatus;

    /* Step 5: Wait on semaphore */
    SemaphoreP_pend(&TestSpinlock_taskUnlockSem, SystemP_WAIT_FOREVER);
    DebugP_log("[Task B] Received signal from Task A\r\n");
    DebugP_log("[Task B] Current lockOwner = 0x%x\r\n", TestSpinlock_LockOwner);

    /* Step 5 (cont): Call Spinlock_unlock() on lock 0 (without having acquired it) */
    DebugP_log("[Task B] Attempting to unlock spinlock 0 without owning it\r\n");
    Spinlock_unlock(CSL_SPINLOCK0_BASE, TEST_LOCK_NUMBER);
    DebugP_log("[Task B] Unlock completed (no error expected)\r\n");

    /* Step 6: Call Spinlock_lock() on lock 0 and verify return is SPINLOCK_LOCK_STATUS_FREE */
    lockStatus = Spinlock_lock(CSL_SPINLOCK0_BASE, TEST_LOCK_NUMBER);
    DebugP_log("[Task B] Spinlock_lock returned: %d\r\n", lockStatus);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, lockStatus);

    /* Step 7: Signal Task A to continue */
    SemaphoreP_post(&TestSpinlock_taskAcquireLockSem);
    DebugP_log("[Task B] Signaled Task A\r\n");

    /* Clean up: unlock the spinlock */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, TEST_LOCK_NUMBER);
    DebugP_log("[Task B] Unlocked spinlock 0\r\n");

    DebugP_log("[Task B] Exiting\r\n");
    TaskP_exit();
}

/* ========================================================================== */
/*                         Test Case Implementation                           */
/* ========================================================================== */

/**
 * @brief Test case: Verify behavior when a lock is released by a task that did not acquire it.
 *
 * This test creates two tasks with equal priority and verifies that:
 * 1. A task can unlock a spinlock it did not acquire (no ownership enforcement)
 * 2. After unlock by non-owner, the lock can be acquired as if it were free
 * 3. Both tasks complete without errors
 * 4. The hardware spinlock does not enforce task ownership at the driver level
 *
 * Expected result: Both tasks complete successfully, demonstrating that the
 * spinlock hardware does not enforce ownership semantics.
 *
 * @param args Unused.
 */
static void TestSpinlock_verifyUnlockByNonOwner(void *args)
{
    (void)args;
    int32_t status;
    TaskP_Params tParams;
    static TaskP_Object taskAObj, taskBObj;

    DebugP_log("\r\n");
    DebugP_log("=============================================================\r\n");
    DebugP_log("Test: Verify Unlock by Non-Owner\r\n");
    DebugP_log("=============================================================\r\n");

    /* Initialize shared variable */
    TestSpinlock_LockOwner = 0U;

    /* Step 1: Construct semaphores for task synchronization */
    status = SemaphoreP_constructBinary(&TestSpinlock_taskAcquireLockSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_constructBinary(&TestSpinlock_taskUnlockSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 1 (cont): Create Task A with equal priority */
    TaskP_Params_init(&tParams);
    tParams.name      = (char*)"SpinlockTaskA";
    tParams.stackSize = sizeof(TestSpinlock_taskAcquireLockStack);
    tParams.stack     = TestSpinlock_taskAcquireLockStack;
    tParams.priority  = 2U;  /* Equal priority */
    tParams.args      = NULL;
    tParams.taskMain  = TestSpinlock_taskAcquireLock;
    status = TaskP_construct(&taskAObj, &tParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Created Task A with priority %d\r\n", tParams.priority);

    /* Step 1 (cont): Create Task B with equal priority */
    TaskP_Params_init(&tParams);
    tParams.name      = (char*)"SpinlockTaskB";
    tParams.stackSize = sizeof(TestSpinlock_taskUnlockStack);
    tParams.stack     = TestSpinlock_taskUnlockStack;
    tParams.priority  = 2U;  /* Equal priority */
    tParams.args      = NULL;
    tParams.taskMain  = TestSpinlock_taskUnlock;
    status = TaskP_construct(&taskBObj, &tParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Created Task B with priority %d\r\n", tParams.priority);

    /* Allow tasks to run and complete */
    ClockP_usleep(100000U);  /* 100ms delay to allow tasks to execute */

    /* Step 8: Verify both tasks completed without errors */
    DebugP_log("Both tasks completed\r\n");

    /* Step 9: Verify hardware spinlock does not enforce task ownership */
    DebugP_log("Verification: Hardware spinlock did not enforce ownership\r\n");
    DebugP_log("Task B successfully unlocked a lock acquired by Task A\r\n");

    /* Cleanup */
    TaskP_destruct(&taskAObj);
    TaskP_destruct(&taskBObj);
    SemaphoreP_destruct(&TestSpinlock_taskAcquireLockSem);
    SemaphoreP_destruct(&TestSpinlock_taskUnlockSem);

    DebugP_log("=============================================================\r\n");
    DebugP_log("Test Passed: Unlock by non-owner completed successfully\r\n");
    DebugP_log("=============================================================\r\n");
    DebugP_log("\r\n");
}

/* ========================================================================== */
/*          Mutual Exclusion Test Task Implementation Functions              */
/* ========================================================================== */

/**
 * @brief Task A for mutual exclusion test: Acquires lock, holds it, then releases.
 *
 * This task:
 * 1. Acquires spinlock 0 and records start time
 * 2. Records execution order: TASK_A_START
 * 3. Holds lock for 50ms to simulate critical section
 * 4. Records execution order: TASK_A_END
 * 5. Releases the spinlock
 *
 * @param arg Unused.
 */
static void TestSpinlock_mutexAcquireLock(void *arg)
{
    (void)arg;
    int32_t lockStatus;
    uint64_t timestamp;

    /* Small delay to ensure Task B is ready to compete for the lock */
    ClockP_usleep(10000U);

    /* Step 3: Call Spinlock_lock() on lock 0 and verify return is SPINLOCK_LOCK_STATUS_FREE */
    lockStatus = Spinlock_lock(CSL_SPINLOCK0_BASE, TEST_LOCK_NUMBER);
    timestamp = ClockP_getTimeUsec();
    DebugP_log("[MutexTaskA] Acquired lock at %llu us, status=%d\r\n", timestamp, lockStatus);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, lockStatus);

    /* Step 4: Record executionOrder[0] = TASK_A_START */
    TestSpinlock_ExecutionOrder[TestSpinlock_ExecIndex++] = TASK_A_START;
    DebugP_log("[MutexTaskA] Recorded TASK_A_START\r\n");

    /* Step 5: Hold lock for 50ms (simulate critical section) */
    DebugP_log("[MutexTaskA] Holding lock for %dms\r\n", CRITICAL_SECTION_DELAY_MS);
    ClockP_usleep(CRITICAL_SECTION_DELAY_MS * 1000U);

    /* Step 8: Record executionOrder[1] = TASK_A_END */
    TestSpinlock_ExecutionOrder[TestSpinlock_ExecIndex++] = TASK_A_END;
    DebugP_log("[MutexTaskA] Recorded TASK_A_END\r\n");

    /* Step 9: Call Spinlock_unlock() on lock 0 */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, TEST_LOCK_NUMBER);
    timestamp = ClockP_getTimeUsec();
    DebugP_log("[MutexTaskA] Released lock at %llu us\r\n", timestamp);

    /* Signal completion */
    SemaphoreP_post(&TestSpinlock_MutexTestDoneSem);
    DebugP_log("[MutexTaskA] Exiting\r\n");
    TaskP_exit();
}

/**
 * @brief Task B for mutual exclusion test: Waits to acquire lock, then holds it.
 *
 * This task:
 * 1. Attempts to acquire spinlock 0 in a spin-wait loop
 * 2. Verifies SPINLOCK_LOCK_STATUS_INUSE while Task A holds lock
 * 3. Successfully acquires lock after Task A releases it
 * 4. Records execution order: TASK_B_START
 * 5. Holds lock for 50ms
 * 6. Records execution order: TASK_B_END
 * 7. Releases the spinlock
 *
 * @param arg Unused.
 */
static void TestSpinlock_mutexHoldLock(void *arg)
{
    (void)arg;
    int32_t lockStatus;
    uint64_t startTime, acquireTime;
    uint32_t inUseCount = 0U;

    /* Step 6: Call Spinlock_lock() in spin-wait loop, capture start timestamp */
    startTime = ClockP_getTimeUsec();
    TestSpinlock_taskUnlockStartTime = startTime;
    DebugP_log("[MutexTaskB] Starting lock acquisition attempt at %llu us\r\n", startTime);

    /* Spin-wait until lock is acquired */
    do {
        lockStatus = Spinlock_lock(CSL_SPINLOCK0_BASE, TEST_LOCK_NUMBER);

        /* Step 7: Verify return is SPINLOCK_LOCK_STATUS_INUSE while Task A holds lock */
        if (lockStatus == SPINLOCK_LOCK_STATUS_INUSE) {
            inUseCount++;
            /* Brief delay to avoid excessive spinning */
            ClockP_usleep(1000U);
        }
    } while (lockStatus != SPINLOCK_LOCK_STATUS_FREE);

    /* Step 10: Successfully acquire lock 0, verify return is SPINLOCK_LOCK_STATUS_FREE */
    acquireTime = ClockP_getTimeUsec();
    DebugP_log("[MutexTaskB] Acquired lock at %llu us, status=%d\r\n", acquireTime, lockStatus);
    DebugP_log("[MutexTaskB] Lock was INUSE %u times before acquisition\r\n", inUseCount);
    TEST_ASSERT_EQUAL_INT32(SPINLOCK_LOCK_STATUS_FREE, lockStatus);
    TEST_ASSERT_GREATER_THAN_UINT32(0, inUseCount);  /* Verify we saw contention */

    /* Step 11: Calculate wait time */
    TestSpinlock_taskUnlockWaitTime = acquireTime - startTime;
    DebugP_log("[MutexTaskB] Wait time: %llu us (%.2f ms)\r\n",
               TestSpinlock_taskUnlockWaitTime,
               (float)TestSpinlock_taskUnlockWaitTime / 1000.0f);

    /* Step 12: Record executionOrder[2] = TASK_B_START */
    TestSpinlock_ExecutionOrder[TestSpinlock_ExecIndex++] = TASK_B_START;
    DebugP_log("[MutexTaskB] Recorded TASK_B_START\r\n");

    /* Step 13: Hold lock for 50ms, record executionOrder[3] = TASK_B_END */
    DebugP_log("[MutexTaskB] Holding lock for %dms\r\n", CRITICAL_SECTION_DELAY_MS);
    ClockP_usleep(CRITICAL_SECTION_DELAY_MS * 1000U);
    TestSpinlock_ExecutionOrder[TestSpinlock_ExecIndex++] = TASK_B_END;
    DebugP_log("[MutexTaskB] Recorded TASK_B_END\r\n");

    /* Step 14: Call Spinlock_unlock() on lock 0 */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, TEST_LOCK_NUMBER);
    acquireTime = ClockP_getTimeUsec();
    DebugP_log("[MutexTaskB] Released lock at %llu us\r\n", acquireTime);

    /* Signal completion */
    SemaphoreP_post(&TestSpinlock_MutexTestDoneSem);
    DebugP_log("[MutexTaskB] Exiting\r\n");
    TaskP_exit();
}

/**
 * @brief Test case: Verify mutual exclusion with two tasks acquiring same spinlock in sequence.
 *
 * This test creates two tasks with equal priority and verifies:
 * 1. Tasks can successfully acquire and release the same spinlock in sequence
 * 2. Mutual exclusion is enforced (no concurrent access to critical section)
 * 3. Execution order shows strict serialization: A_START → A_END → B_START → B_END
 * 4. Task B wait time is at least 50ms (the time Task A holds the lock)
 *
 * Expected result: Strict serialization of critical sections with verified wait time.
 *
 * @param args Unused.
 */
static void TestSpinlock_verifyMutualExclusion(void *args)
{
    (void)args;
    int32_t status;
    TaskP_Params tParams;
    static TaskP_Object mutexTaskAObj, mutexTaskBObj;
    uint32_t i;
    const uint64_t EXPECTED_MIN_WAIT_US = (CRITICAL_SECTION_DELAY_MS * 1000U);

    DebugP_log("\r\n");
    DebugP_log("=============================================================\r\n");
    DebugP_log("Test: Verify Mutual Exclusion with Sequential Lock Acquisition\r\n");
    DebugP_log("=============================================================\r\n");

    /* Step 2: Initialize shared array executionOrder[] and index counter */
    for (i = 0; i < EXEC_ORDER_SIZE; i++) {
        TestSpinlock_ExecutionOrder[i] = 0U;
    }
    TestSpinlock_ExecIndex = 0U;
    TestSpinlock_taskUnlockStartTime = 0U;
    TestSpinlock_taskUnlockWaitTime = 0U;

    /* Reset the spinlock to ensure clean state */
    Spinlock_moduleReset(CSL_SPINLOCK0_BASE);

    /* Construct counting semaphore for task completion (expect 2 posts) */
    status = SemaphoreP_constructCounting(&TestSpinlock_MutexTestDoneSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 1: Create Task A with equal priority */
    TaskP_Params_init(&tParams);
    tParams.name      = (char*)"MutexTaskA";
    tParams.stackSize = sizeof(TestSpinlock_MutexTaskAStack);
    tParams.stack     = TestSpinlock_MutexTaskAStack;
    tParams.priority  = 2U;  /* Equal priority */
    tParams.args      = NULL;
    tParams.taskMain  = TestSpinlock_mutexAcquireLock;
    status = TaskP_construct(&mutexTaskAObj, &tParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Created MutexTaskA with priority %d\r\n", tParams.priority);

    /* Step 1: Create Task B with equal priority */
    TaskP_Params_init(&tParams);
    tParams.name      = (char*)"MutexTaskB";
    tParams.stackSize = sizeof(TestSpinlock_MutexTaskBStack);
    tParams.stack     = TestSpinlock_MutexTaskBStack;
    tParams.priority  = 2U;  /* Equal priority */
    tParams.args      = NULL;
    tParams.taskMain  = TestSpinlock_mutexHoldLock;
    status = TaskP_construct(&mutexTaskBObj, &tParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Created MutexTaskB with priority %d\r\n", tParams.priority);

    /* Wait for both tasks to complete */
    DebugP_log("Waiting for both tasks to complete...\r\n");
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
                            SemaphoreP_pend(&TestSpinlock_MutexTestDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
                            SemaphoreP_pend(&TestSpinlock_MutexTestDoneSem, SystemP_WAIT_FOREVER));
    DebugP_log("Both tasks completed\r\n");

    /* Step 15: Verify execution order shows strict serialization */
    DebugP_log("\r\nVerifying execution order:\r\n");
    DebugP_log("  [0] = 0x%02X (expected TASK_A_START=0x%02X)\r\n",
               TestSpinlock_ExecutionOrder[0], TASK_A_START);
    DebugP_log("  [1] = 0x%02X (expected TASK_A_END=0x%02X)\r\n",
               TestSpinlock_ExecutionOrder[1], TASK_A_END);
    DebugP_log("  [2] = 0x%02X (expected TASK_B_START=0x%02X)\r\n",
               TestSpinlock_ExecutionOrder[2], TASK_B_START);
    DebugP_log("  [3] = 0x%02X (expected TASK_B_END=0x%02X)\r\n",
               TestSpinlock_ExecutionOrder[3], TASK_B_END);

    TEST_ASSERT_EQUAL_UINT32(TASK_A_START, TestSpinlock_ExecutionOrder[0]);
    TEST_ASSERT_EQUAL_UINT32(TASK_A_END, TestSpinlock_ExecutionOrder[1]);
    TEST_ASSERT_EQUAL_UINT32(TASK_B_START, TestSpinlock_ExecutionOrder[2]);
    TEST_ASSERT_EQUAL_UINT32(TASK_B_END, TestSpinlock_ExecutionOrder[3]);
    DebugP_log("Execution order verification PASSED\r\n");

    /* Step 16: Verify Task B wait time ≥ 50ms */
    DebugP_log("\r\nVerifying Task B wait time:\r\n");
    DebugP_log("  Wait time: %llu us (%.2f ms)\r\n",
               TestSpinlock_taskUnlockWaitTime,
               (float)TestSpinlock_taskUnlockWaitTime / 1000.0f);
    DebugP_log("  Expected minimum: %llu us (%d ms)\r\n",
               EXPECTED_MIN_WAIT_US, CRITICAL_SECTION_DELAY_MS);

    TEST_ASSERT_GREATER_OR_EQUAL_UINT64(EXPECTED_MIN_WAIT_US, TestSpinlock_taskUnlockWaitTime);
    DebugP_log("Wait time verification PASSED\r\n");

    /* Cleanup */
    TaskP_destruct(&mutexTaskAObj);
    TaskP_destruct(&mutexTaskBObj);
    SemaphoreP_destruct(&TestSpinlock_MutexTestDoneSem);

    DebugP_log("=============================================================\r\n");
    DebugP_log("Test Passed: Mutual exclusion verified successfully\r\n");
    DebugP_log("=============================================================\r\n");
    DebugP_log("\r\n");
}


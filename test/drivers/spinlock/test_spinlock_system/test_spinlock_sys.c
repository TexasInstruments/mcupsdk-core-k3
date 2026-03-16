/*
 *  Copyright (C) 2021-2026 Texas Instruments Incorporated
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
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/spinlock.h>
#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <drivers/hw_include/cslr_soc.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include <unity.h>

#include "system_test_utils.h"
#include "test_spinlock_sys.h"

/* ========================================================================== */
/*                           Macro  Defines                                   */
/* ========================================================================== */

#define MUTUAL_EXCLUSION_TEST_ITERATIONS    (10000U)
#define MUTUAL_EXCLUSION_TEST_LOCK_NUMBER   (0U)

#define STARVATION_TEST_DURATION_MS         (5000U)
#define STARVATION_TEST_LOCK_NUMBER         (1U)

#define MODULE_RESET_TEST_LOCK_NUMBER       (2U)
#define MODULE_RESET_HOLD_TIME_MS           (100U)

#define CIRCULAR_BUFFER_SIZE                (128U)
#define CIRCULAR_BUFFER_LOCK_NUMBER         (3U)
#define CIRCULAR_BUFFER_BATCH_SIZE          (10U)

/* ========================================================================== */
/*                         Structure Definitions                              */
/* ========================================================================== */

/**
 * \brief Structure representing an item in the circular buffer
 */
typedef struct CircularBufferItem_s
{
    uint32_t sequenceNumber;  /* Sequence number for validation */
    uint32_t data;            /* Payload data */
} CircularBufferItem_t;

/**
 * \brief Structure representing the shared circular buffer
 */
typedef struct CircularBuffer_s
{
    CircularBufferItem_t items[CIRCULAR_BUFFER_SIZE];
    volatile uint32_t head;   /* Read index */
    volatile uint32_t tail;   /* Write index */
    volatile uint32_t count;  /* Number of items in buffer */
} CircularBuffer_t;

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* Shared counter for mutual exclusion test */
static volatile uint32_t gSharedCounter = 0;

/* Per-core acquisition counters for starvation test - shared across cores in DDR */
static volatile uint32_t gCoreAcquisitionCount[CSL_CORE_ID_MAX] = {0};

/* Shared memory counter - tracks total acquisitions */
static volatile uint32_t gSharedAcquisitionCounter = 0;

/* Shared circular buffer for buffer protection test */
static CircularBuffer_t gSharedCircularBuffer;

/* ========================================================================== */
/*                           Function declarations                            */
/* ========================================================================== */


/* ========================================================================== */
/*                           Function definitions                             */
/* ========================================================================== */

/**
 * \brief Test to verify mutual exclusion and data integrity for a shared resource
 *
 * This test validates that spinlocks properly protect a shared counter:
 * 1. Initialize shared counter to 0
 * 2. Run a loop for 10,000 iterations
 * 3. In each iteration: acquire lock, increment counter, release lock
 * 4. After loops finish, verify counter equals 10,000
 *
 * This ensures spinlocks correctly provide mutual exclusion and maintain
 * data integrity for shared resources.
 *
 * \param args Unused test arguments
 * \return SystemP_SUCCESS if test passes, SystemP_FAILURE otherwise
 */
int32_t TestSpinlock_mutualExclusion(void *args)
{
    int32_t status;
    uint32_t i;
    uint32_t expectedCount = MUTUAL_EXCLUSION_TEST_ITERATIONS;

    DebugP_log("[SPINLOCK SYSTEM TEST] Starting mutual exclusion test\r\n");

    /* Step 1: Initialize shared counter to 0 */
    gSharedCounter = 0;

    /* Step 2-3: Run loop for 10,000 iterations */
    for (i = 0; i < MUTUAL_EXCLUSION_TEST_ITERATIONS; i++)
    {
        /* Acquire lock - spin until lock is obtained */
        do {
            status = Spinlock_lock(CSL_SPINLOCK0_BASE, MUTUAL_EXCLUSION_TEST_LOCK_NUMBER);
        } while (status == SPINLOCK_LOCK_STATUS_INUSE);

        /* Critical section: increment counter */
        gSharedCounter++;

        /* Release lock */
        Spinlock_unlock(CSL_SPINLOCK0_BASE, MUTUAL_EXCLUSION_TEST_LOCK_NUMBER);
    }

    /* Step 4: Verify counter equals expected value */
    if (gSharedCounter == expectedCount)
    {
        DebugP_log("[SPINLOCK SYSTEM TEST] PASSED - counter=%d\r\n", gSharedCounter);
        status = SystemP_SUCCESS;
    }
    else
    {
        DebugP_log("[SPINLOCK SYSTEM TEST] FAILED - expected=%d, actual=%d\r\n",
                   expectedCount, gSharedCounter);
        status = SystemP_FAILURE;
    }

    return status;
}

/**
 * \brief Test to observe lock acquisition patterns and identify potential starvation
 *
 * This test validates lock fairness across multiple cores by:
 * 1. Initialize shared memory counter and per-core counters to 0
 * 2. Start concurrent loops for 5 seconds on each core
 * 3. Each core continuously attempts Spinlock_lock(), increments its specific counter
 *    and the shared counter, then calls Spinlock_unlock()
 * 4. After 5 seconds, halt and compare counter values to observe distribution/starvation
 *
 * This test helps identify if the hardware spinlock provides fair arbitration
 * or if certain cores are starved of lock access.
 *
 * \param args Unused test arguments
 * \return SystemP_SUCCESS if test completes (regardless of distribution)
 */
int32_t TestSpinlock_observeStarvation(void *args)
{
    int32_t status;
    uint32_t coreId;
    uint64_t startTime, currentTime;
    uint32_t elapsedMs;
    uint32_t myAcquisitions = 0;

    /* Get the current core ID */
    coreId = IpcNotify_getSelfCoreId();

    DebugP_log("[SPINLOCK STARVATION TEST] Core %d: Starting test\r\n", coreId);

    /* Step 1: Initialize this core's counter to 0 */
    gCoreAcquisitionCount[coreId] = 0;

    /* If this is the main core, initialize shared counter */
    if (coreId == CSL_CORE_ID_R5FSS0_0)
    {
        uint32_t i;
        gSharedAcquisitionCounter = 0;
        for (i = 0; i < CSL_CORE_ID_MAX; i++)
        {
            gCoreAcquisitionCount[i] = 0;
        }
    }

    /* Synchronize all cores before starting the test */
    ClockP_usleep(100000); /* 100ms delay to ensure all cores are ready */

    /* Step 2-3: Run concurrent loop for 5 seconds */
    startTime = ClockP_getTimeUsec();
    elapsedMs = 0;

    while (elapsedMs < STARVATION_TEST_DURATION_MS)
    {
        /* Attempt to acquire lock - spin until lock is obtained */
        do {
            status = Spinlock_lock(CSL_SPINLOCK0_BASE, STARVATION_TEST_LOCK_NUMBER);
        } while (status == SPINLOCK_LOCK_STATUS_INUSE);

        /* Critical section: increment this core's counter and shared counter */
        gCoreAcquisitionCount[coreId]++;
        gSharedAcquisitionCounter++;
        myAcquisitions++;

        /* Release lock */
        Spinlock_unlock(CSL_SPINLOCK0_BASE, STARVATION_TEST_LOCK_NUMBER);

        /* Update elapsed time */
        currentTime = ClockP_getTimeUsec();
        elapsedMs = (uint32_t)((currentTime - startTime) / 1000);
    }

    DebugP_log("[SPINLOCK STARVATION TEST] Core %d: PASSED - %d acquisitions\r\n",
               coreId, myAcquisitions);

    /* Step 4: Wait for all cores to complete */
    ClockP_usleep(500000);

    status = SystemP_SUCCESS;

    return status;
}

/**
 * \brief Test to verify that Spinlock_moduleReset() releases locks and resumes operation
 *
 * This test validates that the module reset function properly clears locked spinlocks
 * and restores hardware functionality:
 * 1. Acquire & Abandon: Call Spinlock_lock(0) and verify it returns SPINLOCK_LOCK_STATUS_FREE
 * 2. Verify State: Attempt to acquire Lock 0 again (nested lock). Verify it returns
 *    SPINLOCK_LOCK_STATUS_INUSE
 * 3. Execute Reset: Call Spinlock_moduleReset()
 * 4. Verify Recovery: Attempt Spinlock_lock(0) again. Verify it now returns
 *    SPINLOCK_LOCK_STATUS_FREE (proving the reset cleared the internal ownership register)
 * 5. Sanity Check: Perform a standard Spinlock_lock(0) followed by Spinlock_unlock(0)
 *    to ensure the hardware logic is functional post-reset
 *
 * This test is critical for verifying recovery mechanisms when locks are abandoned or
 * a core crashes while holding a lock.
 *
 * \param args Unused test arguments
 * \return SystemP_SUCCESS if test passes, SystemP_FAILURE otherwise
 */
int32_t TestSpinlock_moduleResetRecovery(void *args)
{
    int32_t status;
    uint32_t lockNum = MODULE_RESET_TEST_LOCK_NUMBER;

    DebugP_log("[SPINLOCK MODULE RESET TEST] Starting test\r\n");

    /* Step 1: Acquire lock and verify it was free */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
    if (status != SPINLOCK_LOCK_STATUS_FREE)
    {
        DebugP_log("[SPINLOCK MODULE RESET TEST] FAIL: Initial lock status %d\r\n", status);
        return SystemP_FAILURE;
    }

    /* Step 2: Verify nested lock returns INUSE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
    if (status != SPINLOCK_LOCK_STATUS_INUSE)
    {
        DebugP_log("[SPINLOCK MODULE RESET TEST] FAIL: Nested lock status %d\r\n", status);
        return SystemP_FAILURE;
    }

    /* Step 3: Execute module reset */
    Spinlock_moduleReset(CSL_SPINLOCK0_BASE);

    /* Step 4: Verify lock is free after reset */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
    if (status != SPINLOCK_LOCK_STATUS_FREE)
    {
        DebugP_log("[SPINLOCK MODULE RESET TEST] FAIL: Post-reset lock status %d\r\n", status);
        return SystemP_FAILURE;
    }

    /* Step 5: Sanity check - normal lock/unlock sequence */
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
    if (status != SPINLOCK_LOCK_STATUS_FREE)
    {
        DebugP_log("[SPINLOCK MODULE RESET TEST] FAIL: Sanity check lock status %d\r\n", status);
        return SystemP_FAILURE;
    }
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);

    DebugP_log("[SPINLOCK MODULE RESET TEST] PASSED\r\n");
    return SystemP_SUCCESS;
}

/**
 * \brief Test to verify spinlock correctly protects a shared circular buffer
 *
 * This test validates that spinlocks provide proper protection for a shared circular
 * buffer with production and consumption operations:
 * 1. Initialization: Initialize 128-element circular buffer and verify lock is free
 * 2. Simulated Production: Acquire lock, write 10 items with sequence numbers,
 *    verify nested lock returns INUSE, then unlock
 * 3. Simulated Consumption: Acquire lock, read 10 items, verify sequence numbers
 *    are contiguous (no corruption), then unlock
 * 4. Boundary Verification: Fill buffer to capacity (128 elements) using
 *    lock/write/unlock cycles and verify buffer reports full
 * 5. Final Validation: Verify head == tail after all items are read and lock is free
 *
 * This test ensures spinlocks correctly protect complex shared data structures
 * and prevent race conditions during concurrent access.
 *
 * \param args Unused test arguments
 * \return SystemP_SUCCESS if test passes, SystemP_FAILURE otherwise
 */
int32_t TestSpinlock_circularBufferProtection(void *args)
{
    int32_t status;
    uint32_t lockNum = CIRCULAR_BUFFER_LOCK_NUMBER;
    uint32_t i, batchCount;
    uint32_t expectedSeqNum = 0;
    uint32_t writeSeqNum = 0;

    DebugP_log("[SPINLOCK BUFFER TEST] Starting test\r\n");

    /* Step 1: Initialization */
    gSharedCircularBuffer.head = 0;
    gSharedCircularBuffer.tail = 0;
    gSharedCircularBuffer.count = 0;

    for (i = 0; i < CIRCULAR_BUFFER_SIZE; i++)
    {
        gSharedCircularBuffer.items[i].sequenceNumber = 0;
        gSharedCircularBuffer.items[i].data = 0;
    }

    /* Verify lock is free */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
    if (status != SPINLOCK_LOCK_STATUS_FREE)
    {
        DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Initial lock check returned status %d\r\n", status);
        return SystemP_FAILURE;
    }
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);

    /* Step 2: Simulated Production */
    do {
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
    } while (status == SPINLOCK_LOCK_STATUS_INUSE);

    if (status != SPINLOCK_LOCK_STATUS_FREE)
    {
        DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Production lock returned status %d\r\n", status);
        return SystemP_FAILURE;
    }

    /* Write items to buffer */
    for (i = 0; i < CIRCULAR_BUFFER_BATCH_SIZE; i++)
    {
        if (gSharedCircularBuffer.count >= CIRCULAR_BUFFER_SIZE)
        {
            DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Buffer full during initial write\r\n");
            Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);
            return SystemP_FAILURE;
        }

        gSharedCircularBuffer.items[gSharedCircularBuffer.tail].sequenceNumber = writeSeqNum++;
        gSharedCircularBuffer.items[gSharedCircularBuffer.tail].data = 0xDEAD0000 + writeSeqNum;
        gSharedCircularBuffer.tail = (gSharedCircularBuffer.tail + 1) % CIRCULAR_BUFFER_SIZE;
        gSharedCircularBuffer.count++;
    }

    /* Verify nested lock returns INUSE */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
    if (status != SPINLOCK_LOCK_STATUS_INUSE)
    {
        DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Nested lock status %d\r\n", status);
        Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);
        return SystemP_FAILURE;
    }

    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);

    /* Step 3: Simulated Consumption */
    do {
        status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
    } while (status == SPINLOCK_LOCK_STATUS_INUSE);

    if (status != SPINLOCK_LOCK_STATUS_FREE)
    {
        DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Consumption lock status %d\r\n", status);
        return SystemP_FAILURE;
    }

    /* Read items and verify sequence numbers */
    expectedSeqNum = 0;
    for (i = 0; i < CIRCULAR_BUFFER_BATCH_SIZE; i++)
    {
        if (gSharedCircularBuffer.count == 0)
        {
            DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Buffer empty during read (read %d/%d items)\r\n",
                       i, CIRCULAR_BUFFER_BATCH_SIZE);
            Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);
            return SystemP_FAILURE;
        }

        uint32_t seqNum = gSharedCircularBuffer.items[gSharedCircularBuffer.head].sequenceNumber;
        if (seqNum != expectedSeqNum)
        {
            DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Sequence corruption! Expected %d, got %d\r\n",
                       expectedSeqNum, seqNum);
            Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);
            return SystemP_FAILURE;
        }

        expectedSeqNum++;
        gSharedCircularBuffer.head = (gSharedCircularBuffer.head + 1) % CIRCULAR_BUFFER_SIZE;
        gSharedCircularBuffer.count--;
    }

    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);

    /* Step 4: Boundary Verification - Fill to capacity */
    batchCount = 0;
    while (gSharedCircularBuffer.count < CIRCULAR_BUFFER_SIZE)
    {
        /* Acquire lock */
        do {
            status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
        } while (status == SPINLOCK_LOCK_STATUS_INUSE);

        /* Write batch (up to BATCH_SIZE or remaining space) */
        uint32_t itemsToWrite = CIRCULAR_BUFFER_BATCH_SIZE;
        if (gSharedCircularBuffer.count + itemsToWrite > CIRCULAR_BUFFER_SIZE)
        {
            itemsToWrite = CIRCULAR_BUFFER_SIZE - gSharedCircularBuffer.count;
        }

        for (i = 0; i < itemsToWrite; i++)
        {
            gSharedCircularBuffer.items[gSharedCircularBuffer.tail].sequenceNumber = writeSeqNum++;
            gSharedCircularBuffer.items[gSharedCircularBuffer.tail].data = 0xBEEF0000 + writeSeqNum;
            gSharedCircularBuffer.tail = (gSharedCircularBuffer.tail + 1) % CIRCULAR_BUFFER_SIZE;
            gSharedCircularBuffer.count++;
        }

        /* Release lock */
        Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);
        batchCount++;

        if (batchCount > 20) /* Safety check to prevent infinite loop */
        {
            DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Too many batches written\r\n");
            return SystemP_FAILURE;
        }
    }

    if (gSharedCircularBuffer.count != CIRCULAR_BUFFER_SIZE)
    {
        DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Buffer not full (count=%d)\r\n", gSharedCircularBuffer.count);
        return SystemP_FAILURE;
    }

    /* Step 5: Final Validation - Read all and verify */
    expectedSeqNum = CIRCULAR_BUFFER_BATCH_SIZE; /* Start after the first consumed batch */
    while (gSharedCircularBuffer.count > 0)
    {
        /* Acquire lock */
        do {
            status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
        } while (status == SPINLOCK_LOCK_STATUS_INUSE);

        /* Read batch */
        uint32_t itemsToRead = CIRCULAR_BUFFER_BATCH_SIZE;
        if (itemsToRead > gSharedCircularBuffer.count)
        {
            itemsToRead = gSharedCircularBuffer.count;
        }

        for (i = 0; i < itemsToRead; i++)
        {
            uint32_t seqNum = gSharedCircularBuffer.items[gSharedCircularBuffer.head].sequenceNumber;
            if (seqNum != expectedSeqNum)
            {
                DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Final sequence corruption! Expected %d, got %d\r\n",
                           expectedSeqNum, seqNum);
                Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);
                return SystemP_FAILURE;
            }

            expectedSeqNum++;
            gSharedCircularBuffer.head = (gSharedCircularBuffer.head + 1) % CIRCULAR_BUFFER_SIZE;
            gSharedCircularBuffer.count--;
        }

        /* Release lock */
        Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);
    }

    if (gSharedCircularBuffer.head != gSharedCircularBuffer.tail)
    {
        DebugP_log("[SPINLOCK BUFFER TEST] FAIL: head != tail after reading all items\r\n");
        return SystemP_FAILURE;
    }

    /* Verify lock is free */
    status = Spinlock_lock(CSL_SPINLOCK0_BASE, lockNum);
    if (status != SPINLOCK_LOCK_STATUS_FREE)
    {
        DebugP_log("[SPINLOCK BUFFER TEST] FAIL: Final lock status %d\r\n", status);
        return SystemP_FAILURE;
    }
    Spinlock_unlock(CSL_SPINLOCK0_BASE, lockNum);

    DebugP_log("[SPINLOCK BUFFER TEST] PASSED - validated %d sequences\r\n", expectedSeqNum);
    return SystemP_SUCCESS;
}


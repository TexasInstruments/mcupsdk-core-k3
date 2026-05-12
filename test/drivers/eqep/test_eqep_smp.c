/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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

/**
 * @file test_eqep_smp.c
 * @brief The following test aims at creating SMP tasks for A53 cores with core affinity.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* Standard includes. */
#include <stdint.h>
#include <string.h>

/* Kernel includes. */
#include <drivers/eqep.h>
#include <drivers/hw_include/csl_types.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "unity.h"
#include <kernel/dpl/SystemP.h>
#include "test_eqep_pattern_gen.h"

/* ========================================================================== */
/*                             Macros & Defines                               */
/* ========================================================================== */

#define TEST_EQEP_MT_TASK_STACK_SIZE             (8 * 1024)
#define TEST_EQEP_MT_TEST_DURATION_MS            (5000U)
#define TEST_EQEP_POSITION_READ_INTERVAL_MS      (100U)
#define TEST_EQEP_POS_CNT_VARIANCE               (4U)

/* Number of EQEP EVENTS */
#define TEST_EQEP_EVENT_CNT                      (10U)

/* Frequency of EQEP signal for testing unit timeout event in Hz. */
#define TEST_EQEP_SIGNAL_TEST_FREQ               (500U)

/* Number of times the EQEP pattern is generated. */
#define TEST_EQEP_PATTERN_GEN_LOOP_COUNT         (TEST_EQEP_SIGNAL_TEST_FREQ / TEST_EQEP_EVENT_CNT)

#define TEST_EQEP_INT_ALL                        (EQEP_INT_GLOBAL            | \
                                                 EQEP_INT_POS_CNT_ERROR     | \
                                                 EQEP_INT_PHASE_ERROR       | \
                                                 EQEP_INT_DIR_CHANGE        | \
                                                 EQEP_INT_WATCHDOG          | \
                                                 EQEP_INT_UNDERFLOW         | \
                                                 EQEP_INT_OVERFLOW          | \
                                                 EQEP_INT_POS_COMP_READY    | \
                                                 EQEP_INT_POS_COMP_MATCH    | \
                                                 EQEP_INT_STROBE_EVNT_LATCH | \
                                                 EQEP_INT_INDEX_EVNT_LATCH  | \
                                                 EQEP_INT_UNIT_TIME_OUT     | \
                                                 EQEP_INT_QMA_ERROR)


/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

typedef struct {
    uint32_t instanceId;
    uint32_t positionReadings[100];
    uint32_t readingCount;
    uint32_t speedValues[100];
    uint32_t speedCount;
    uint32_t dataCorruptionDetected;
} EQEP_ThreadResults;

static EQEP_ThreadResults TestEqep_thread1Results = {0};
static EQEP_ThreadResults TestEqep_thread2Results = {0};

static uint8_t TestEqep_task1Stack[TEST_EQEP_MT_TASK_STACK_SIZE];
static uint8_t TestEqep_task2Stack[TEST_EQEP_MT_TASK_STACK_SIZE];
static TaskP_Object TestEqep_TaskObjs[2];
static SemaphoreP_Object TestEqep_mtTestSem;

/* ========================================================================== */
/*                        Internal Function Declarations                      */
/* ========================================================================== */

static void TestEqep_initPattern(EqepAppPatternParams *eqepPattern);
static void TestEqep_smpWatchdogMonitorWhileCaptureCalc(void *args);
static void TestEqep_smpDualInstanceQMAOperation(void *args);
static void TestEqep_smpPositionReadWhileSpeedCalc(void *args);
static void TestEqep_verifyThreadResults(void);
void setUp(void);
void tearDown(void);

/* ========================================================================== */
/*                        Function Definitions                                */
/* ========================================================================== */

/**
 * \brief  Verify results from multithreaded EQEP test execution.
 *
 * This helper function logs and validates the results collected by position
 * reader and speed calculator threads, checking for data corruption, verifying
 * that both threads operated independently, and asserting that valid position
 * advancement and speed calculations occurred.
 * Test case category: utility function
 */
static void TestEqep_verifyThreadResults(void)
{
    uint32_t corruptionCount = 0;
    uint32_t i;
    uint32_t avgSpeed = 0;
    uint32_t finalPos1 = 0;
    uint32_t finalPos2 = 0;

    DebugP_log("  Instance ID: %d\r\n", TestEqep_thread1Results.instanceId);
    DebugP_log("  Readings collected: %d\r\n", TestEqep_thread1Results.readingCount);
    DebugP_log("  Data corruption detected: %s\r\n",
               TestEqep_thread1Results.dataCorruptionDetected ? "YES" : "NO");

    if (TestEqep_thread1Results.readingCount > 0)
    {
        finalPos1 = TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount - 1];
        DebugP_log("  Position range: %d to %d\r\n",
                   TestEqep_thread1Results.positionReadings[0], finalPos1);
    }

    if (TestEqep_thread1Results.dataCorruptionDetected)
    {
        corruptionCount++;
    }

    DebugP_log("\nThread 2 (Speed Calculator on EQEP1/2):\r\n");
    DebugP_log("  Instance ID: %d\r\n", TestEqep_thread2Results.instanceId);
    DebugP_log("  Speed samples collected: %d\r\n", TestEqep_thread2Results.speedCount);
    DebugP_log("  Data corruption detected: %s\r\n",
               TestEqep_thread2Results.dataCorruptionDetected ? "YES" : "NO");

    if (TestEqep_thread2Results.speedCount > 0)
    {
        finalPos2 = TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.speedCount - 1];
        DebugP_log("  Position range: %d to %d\r\n",
                   TestEqep_thread2Results.positionReadings[0], finalPos2);
    }

    if (TestEqep_thread2Results.dataCorruptionDetected)
    {
        corruptionCount++;
    }

    DebugP_log("  Threads with data corruption: %d\r\n", corruptionCount);

    /* ---------------------------------------------------------------------- */
    /* STRICT VALIDATIONS                                                     */
    /* ---------------------------------------------------------------------- */

    /* 1. Verify no non-monotonic/corrupted data was read */
    TEST_ASSERT_EQUAL_UINT32(0U, corruptionCount);

    /* 2. Verify threads actually executed and collected arrays of data */
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread1Results.readingCount);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread2Results.speedCount);

    /* 3. VALIDATE POSITION: Ensure the hardware actually counted edges and moved */
    /* We expect thousands of edges over 5 seconds at 100Hz. 100U is a safe lower bound. */
    TEST_ASSERT_GREATER_THAN_UINT32(100U, finalPos1);
    TEST_ASSERT_GREATER_THAN_UINT32(100U, finalPos2);
    DebugP_log("\n  [Validation] Position advancement confirmed. Thread1 Final Pos: %u, Thread2 Final Pos: %u\r\n", finalPos1, finalPos2);

    /* 4. VALIDATE SPEED: Ensure the math in the thread yielded actual speeds */
    for (i = 1; i < TestEqep_thread2Results.speedCount; i++)
    {
        /* Skip index 0 as delta might be 0 on the very first immediate read */
        avgSpeed += TestEqep_thread2Results.speedValues[i];
    }
    
    if (TestEqep_thread2Results.speedCount > 1) 
    {
        avgSpeed = avgSpeed / (TestEqep_thread2Results.speedCount - 1);
    }

    /* Assert that the average calculated speed is greater than zero */
    TEST_ASSERT_GREATER_THAN_UINT32(0U, avgSpeed);
    DebugP_log("  [Validation] Average calculated speed is %u (Valid non-zero speed confirmed)\r\n", avgSpeed);
}

/**
 * \brief  Capture speed from EQEP0 in SMP test.
 *
 * Continuously reads position from EQEP0 and calculates speed based on position deltas.
 * Test case category: functionality test case
 *
 * \param arg  Thread ID passed as argument.
 */
static void TestEqep_captureSpeedThread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t lastPos = 0, posDelta, speed;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;

    TestEqep_thread1Results.instanceId = threadId;
    TestEqep_thread1Results.speedCount = 0;
    TestEqep_thread1Results.readingCount = 0;
    TestEqep_thread1Results.dataCorruptionDetected = 0;

    DebugP_log("Thread %d (Capture Speed) started on EQEP0\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);

        /* Calculate position delta with rollover support */
        if (currentPos >= lastPos)
        {
            posDelta = currentPos - lastPos;
        }
        else
        {
            posDelta = (CSL_EQEP_QPOSCNT_QPOSCNT_MAX - lastPos) + currentPos + 1U;
        }

        /* CORRUPTION CHECK: Flag massive delta anomalies */
        if ((i > 0U) && (posDelta > (TEST_EQEP_SIGNAL_TEST_FREQ * 4U))) 
        {
            TestEqep_thread1Results.dataCorruptionDetected = 1;
            DebugP_log("Thread %d: Corruption detected - massive delta anomaly (prev=%u, curr=%u, delta=%u)\r\n",
                       threadId, lastPos, currentPos, posDelta);
        }

        speed = (posDelta * 1000U) / TEST_EQEP_POSITION_READ_INTERVAL_MS;

        if (TestEqep_thread1Results.readingCount < 100U)
        {
            TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount] = currentPos;
            TestEqep_thread1Results.speedValues[TestEqep_thread1Results.readingCount] = speed;
            TestEqep_thread1Results.readingCount++;
            TestEqep_thread1Results.speedCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000U);
    }

    DebugP_log("Thread %d (Capture Speed): Calculated %d speed samples\r\n",
               threadId, TestEqep_thread1Results.speedCount);

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Monitor watchdog on EQEP1 in SMP test.
 *
 * Monitors the watchdog timer on EQEP1 and detects stalls when input is intermittent.
 * Test case category: functionality test case
 *
 * \param arg  Thread ID passed as argument.
 */
static void TestEqep_eqepWatchdogMonitorThread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;
    uint32_t wdgTimerVal;
    uint32_t stallDetectedCount = 0U;
    uint32_t lastPos = 0U;

    TestEqep_thread2Results.instanceId = threadId;
    TestEqep_thread2Results.readingCount = 0;
    TestEqep_thread2Results.speedCount = 0;
    TestEqep_thread2Results.dataCorruptionDetected = 0;

    DebugP_log("Thread %d (Watchdog Monitor) started on EQEP1\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);
        wdgTimerVal = EQEP_getWatchdogTimerValue(baseAddr);

        if ((i > 0U) && (currentPos == lastPos))
        {
            stallDetectedCount++;
        }

        if (TestEqep_thread2Results.readingCount < 100U)
        {
            TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount] = currentPos;
            TestEqep_thread2Results.speedValues[TestEqep_thread2Results.readingCount] = wdgTimerVal;
            TestEqep_thread2Results.readingCount++;
            TestEqep_thread2Results.speedCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000U);
    }

    if (stallDetectedCount > 0U)
    {
        DebugP_log("Thread %d: Stall detected %d times (expected for intermittent input)\r\n",
                   threadId, stallDetectedCount);
    }
    else
    {
        DebugP_log("Thread %d: No stall detected\r\n", threadId);
    }

    DebugP_log("Thread %d (Watchdog Monitor): Monitored %d samples, Stalls: %d\r\n",
               threadId, TestEqep_thread2Results.readingCount, stallDetectedCount);

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Test watchdog monitor and speed capture on separate EQEP instances with SMP.
 *
 * Verifies independent watchdog monitoring on EQEP1 and speed capture on EQEP0 using tasks
 * with core affinity. Intermittent input patterns validate stall detection across cores.
 * Test case category: functionality test case
 *
 * \param args  Unused argument.
 */
static void TestEqep_smpWatchdogMonitorWhileCaptureCalc(void *args)
{
    int32_t status, i;
    TaskP_Params taskParams1, taskParams2;
    EqepAppPatternParams eqepPattern = {0U};
    uint32_t baseAddr0, baseAddr1;

    DebugP_log("\n SMP Watchdog Monitor + Capture Calc Test Started\r\n");

    status = SemaphoreP_constructCounting(&TestEqep_mtTestSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    baseAddr0 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    baseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);

    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);
    EQEP_disableInterrupt(baseAddr0, TEST_EQEP_INT_ALL);
    EQEP_disableInterrupt(baseAddr1, TEST_EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr0, TEST_EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr1, TEST_EQEP_INT_ALL);

    EQEP_setInitialPosition(baseAddr0, 0U);
    EQEP_setPosition(baseAddr0, 0U);
    EQEP_setDecoderConfig(baseAddr0, (EQEP_CONFIG_2X_RESOLUTION |
                                      EQEP_CONFIG_QUADRATURE |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr0, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr0, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_enableModule(baseAddr0);

    EQEP_setInitialPosition(baseAddr1, 0U);
    EQEP_setPosition(baseAddr1, 0U);
    EQEP_setDecoderConfig(baseAddr1, (EQEP_CONFIG_2X_RESOLUTION |
                                      EQEP_CONFIG_QUADRATURE |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr1, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr1, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_setWatchdogTimerValue(baseAddr1, 0U);
    EQEP_enableWatchdog(baseAddr1, CSL_EQEP_QWDPRD_QWDPRD_MAX / 2);
    EQEP_enableModule(baseAddr1);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestEqep_task1Stack;
    taskParams1.stackSize      = sizeof(TestEqep_task1Stack);
    taskParams1.name           = "EQEPCaptureSpeed";
    taskParams1.taskMain       = &TestEqep_captureSpeedThread;
    taskParams1.args           = (void *)(uintptr_t)0;
    taskParams1.coreAffinity   = (1U << 0);

    status = TaskP_construct(&TestEqep_TaskObjs[0], &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    DebugP_log("Thread 1 (Core 0 - Capture Speed on EQEP0) spawned\r\n");

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestEqep_task2Stack;
    taskParams2.stackSize      = sizeof(TestEqep_task2Stack);
    taskParams2.name           = "EQEPWdgMonitor";
    taskParams2.taskMain       = &TestEqep_eqepWatchdogMonitorThread;
    taskParams2.args           = (void *)(uintptr_t)1;
    taskParams2.coreAffinity   = (1U << 1);

    status = TaskP_construct(&TestEqep_TaskObjs[1], &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    DebugP_log("Thread 2 (Core 1 - Watchdog Monitor on EQEP2) spawned\r\n");

    TestEqep_initPattern(&eqepPattern);
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.idxEvtCnt        = 1U;

    eqepPattern.loopCnt = 200U;
    App_eqepGenerateDualPattern(&eqepPattern);

    ClockP_usleep(1000U * 1000U);

    eqepPattern.loopCnt = 200U;
    App_eqepGenerateDualPattern(&eqepPattern);

    DebugP_log("Waiting for threads to complete...\r\n");
    for (i = 0; i < 2; i++)
    {
        int32_t semStatus = SemaphoreP_pend(&TestEqep_mtTestSem,
                                            ClockP_usecToTicks((TEST_EQEP_MT_TEST_DURATION_MS + 5000U) * 1000U));
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semStatus);
    }

    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread1Results.speedCount);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread2Results.readingCount);
    
    /* Strict Validation for Speed/Watchdog test */
    if(TestEqep_thread1Results.readingCount > 0U) {
        TEST_ASSERT_GREATER_THAN_UINT32(100U, TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount - 1]);
    }
    if(TestEqep_thread2Results.readingCount > 0U) {
        TEST_ASSERT_GREATER_THAN_UINT32(100U, TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount - 1]);
    }

    DebugP_log("Test completed\r\n");
    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);
    EQEP_disableWatchdog(baseAddr1);

    for (i = 0; i < 2; i++)
    {
        TaskP_destruct(&TestEqep_TaskObjs[i]);
    }
    SemaphoreP_destruct(&TestEqep_mtTestSem);
}

/**
 * \brief  QMA Mode 1 operation thread on EQEP0 in SMP test.
 *
 * Executes QMA Mode 1 error correction on EQEP0 with error detection for invalid direction changes.
 * Test case category: functionality test case
 *
 * \param arg  Thread ID passed as argument.
 */
static void TestEqep_eqepQmaMode1Thread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;
    uint32_t lastPos = 0U;
    uint32_t backwardCount = 0U;

    TestEqep_thread1Results.instanceId = threadId;
    TestEqep_thread1Results.readingCount = 0U;
    TestEqep_thread1Results.speedCount = 0U;
    TestEqep_thread1Results.dataCorruptionDetected = 0U;

    DebugP_log("Thread %d (QMA Mode 1 - EQEP0) started\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);
        int32_t  direction  = EQEP_getDirection(baseAddr);

        if ((i > 0U) && (currentPos < lastPos) && (lastPos > TEST_EQEP_POS_CNT_VARIANCE) &&
            (direction == EQEP_MOD_FORWARD_DIR))
        {
            backwardCount++;
            TestEqep_thread1Results.dataCorruptionDetected = 1U;
        }

        if (TestEqep_thread1Results.readingCount < 100U)
        {
            TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount] = currentPos;
            TestEqep_thread1Results.speedValues[TestEqep_thread1Results.readingCount] = (uint32_t)direction;
            TestEqep_thread1Results.readingCount++;
            TestEqep_thread1Results.speedCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000U);
    }

    DebugP_log("Thread %d (QMA Mode 1): %d samples, backward movements: %d\r\n",
               threadId, TestEqep_thread1Results.readingCount, backwardCount);

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  QMA Mode 2 operation thread on EQEP2 in SMP test.
 *
 * Executes QMA Mode 2 strict validation on EQEP2 with error detection for invalid direction changes.
 * Test case category: functionality test case
 *
 * \param arg  Thread ID passed as argument.
 */
static void TestEqep_eqepQmaMode2Thread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;
    uint32_t lastPos = 0U;

    TestEqep_thread2Results.instanceId = threadId;
    TestEqep_thread2Results.readingCount = 0U;
    TestEqep_thread2Results.speedCount = 0U;
    TestEqep_thread2Results.dataCorruptionDetected = 0U;

    DebugP_log("Thread %d (QMA Mode 2 - EQEP2) started\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);
        int32_t  direction  = EQEP_getDirection(baseAddr);

        if ((i > 0U) && (currentPos < lastPos) && (lastPos > TEST_EQEP_POS_CNT_VARIANCE) &&
            (direction == EQEP_MOD_FORWARD_DIR))
        {
            TestEqep_thread2Results.dataCorruptionDetected = 1U;
            DebugP_log("Thread %d: Unexpected backward movement (prev=%d, curr=%d)\r\n",
                       threadId, lastPos, currentPos);
        }

        if (TestEqep_thread2Results.readingCount < 100U)
        {
            TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount] = currentPos;
            TestEqep_thread2Results.speedValues[TestEqep_thread2Results.readingCount] = (uint32_t)direction;
            TestEqep_thread2Results.readingCount++;
            TestEqep_thread2Results.speedCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000U);
    }

    DebugP_log("Thread %d (QMA Mode 2): %d samples, Corruption: %s\r\n",
               threadId, TestEqep_thread2Results.readingCount,
               TestEqep_thread2Results.dataCorruptionDetected ? "YES" : "NO");

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Test dual instance QMA operation with core affinity.
 *
 * Creates two tasks with core affinity: one for QMA Mode 1 and one for QMA Mode 2.
 * Each task operates on a different EQEP instance independently.
 * Test case category: functionality test case
 *
 * \param args  Unused argument.
 */
static void TestEqep_smpDualInstanceQMAOperation(void *args)
{
    int32_t status, i;
    TaskP_Params taskParams1, taskParams2;
    EqepAppPatternParams eqepPattern = {0U};
    uint32_t baseAddr0, baseAddr1;

    DebugP_log("\n SMP Dual Instance QMA Operation Test Started \r\n");

    status = SemaphoreP_constructCounting(&TestEqep_mtTestSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    baseAddr0 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    baseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);

    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);
    EQEP_disableInterrupt(baseAddr0, TEST_EQEP_INT_ALL);
    EQEP_disableInterrupt(baseAddr1, TEST_EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr0, TEST_EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr1, TEST_EQEP_INT_ALL);

    EQEP_setInitialPosition(baseAddr0, 0U);
    EQEP_setPosition(baseAddr0, 0U);
    EQEP_setDecoderConfig(baseAddr0, (EQEP_CONFIG_1X_RESOLUTION |
                                      EQEP_CONFIG_CLOCK_DIR |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr0, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr0, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_setQMAModuleMode(baseAddr0, EQEP_QMA_MODE_1);
    EQEP_enableModule(baseAddr0);

    EQEP_setInitialPosition(baseAddr1, 0U);
    EQEP_setPosition(baseAddr1, 0U);
    EQEP_setDecoderConfig(baseAddr1, (EQEP_CONFIG_1X_RESOLUTION |
                                      EQEP_CONFIG_CLOCK_DIR |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr1, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr1, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_setQMAModuleMode(baseAddr1, EQEP_QMA_MODE_2);
    EQEP_enableModule(baseAddr1);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestEqep_task1Stack;
    taskParams1.stackSize      = sizeof(TestEqep_task1Stack);
    taskParams1.name           = "EQEPQmaMode1";
    taskParams1.taskMain       = &TestEqep_eqepQmaMode1Thread;
    taskParams1.args           = (void *)(uintptr_t)0;
    taskParams1.coreAffinity   = (1U << 0);

    status = TaskP_construct(&TestEqep_TaskObjs[0], &taskParams1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Thread 1 (Core 0 - QMA Mode 1 on EQEP0) spawned\r\n");

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestEqep_task2Stack;
    taskParams2.stackSize      = sizeof(TestEqep_task2Stack);
    taskParams2.name           = "EQEPQmaMode2";
    taskParams2.taskMain       = &TestEqep_eqepQmaMode2Thread;
    taskParams2.args           = (void *)(uintptr_t)1;
    taskParams2.coreAffinity   = (1U << 1);

    status = TaskP_construct(&TestEqep_TaskObjs[1], &taskParams2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Thread 2 (Core 1 - QMA Mode 2 on EQEP2) spawned\r\n");

    TestEqep_initPattern(&eqepPattern);
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.idxEvtCnt        = 1U;
    eqepPattern.loopCnt          = 100U;
    App_eqepGenerateDualClockDirPattern(&eqepPattern);

    eqepPattern.loopCnt = 200U;
    App_eqepGenerateDualClockDirPattern(&eqepPattern);

    eqepPattern.direction = EQEP_DIR_ANTI_CLOCKWISE;
    eqepPattern.loopCnt   = 200U;
    App_eqepGenerateDualClockDirPattern(&eqepPattern);

    DebugP_log("Waiting for threads to complete...\r\n");
    for (i = 0; i < 2; i++)
    {
        int32_t semStatus = SemaphoreP_pend(&TestEqep_mtTestSem,
                                            ClockP_usecToTicks((TEST_EQEP_MT_TEST_DURATION_MS + 5000U) * 1000U));
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semStatus);
    }

    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread1Results.readingCount);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread2Results.readingCount);

    TEST_ASSERT_EQUAL_UINT32(0U, TestEqep_thread2Results.dataCorruptionDetected);

    if (TestEqep_thread1Results.readingCount > 1U && TestEqep_thread2Results.readingCount > 1U)
    {
        uint32_t pos0_last = TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount - 1U];
        uint32_t pos1_last = TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount - 1U];

        TEST_ASSERT_NOT_EQUAL(0U, pos0_last);
        TEST_ASSERT_NOT_EQUAL(0U, pos1_last);
    }
    DebugP_log("Test completed\r\n");
    EQEP_setQMAModuleMode(baseAddr0, EQEP_QMA_MODE_BYPASS);
    EQEP_setQMAModuleMode(baseAddr1, EQEP_QMA_MODE_BYPASS);
    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);

    for (i = 0; i < 2; i++)
    {
        TaskP_destruct(&TestEqep_TaskObjs[i]);
    }
    SemaphoreP_destruct(&TestEqep_mtTestSem);
}

/**
 * \brief  Position reader thread on EQEP0 in SMP test.
 *
 * Continuously reads position from EQEP0 and detects non-monotonic position changes.
 * Test case category: functionality test case
 *
 * \param arg  Thread ID passed as argument.
 */
static void TestEqep_positionReaderThread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t lastPos = 0;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;

    TestEqep_thread1Results.instanceId = threadId;
    TestEqep_thread1Results.readingCount = 0;
    TestEqep_thread1Results.dataCorruptionDetected = 0;

    DebugP_log("Thread %d (Position Reader) started on EQEP0\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);

        if (currentPos < lastPos && lastPos > 100)
        {
            TestEqep_thread1Results.dataCorruptionDetected = 1;
            DebugP_log("Thread %d: Corruption detected - non-monotonic position (prev=%d, curr=%d)\r\n",
                       threadId, lastPos, currentPos);
        }

        if (TestEqep_thread1Results.readingCount < 100)
        {
            TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount++] = currentPos;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000);
    }

    DebugP_log("Thread %d (Position Reader): Read %d position samples, Corruption: %s\r\n",
               threadId, TestEqep_thread1Results.readingCount,
               TestEqep_thread1Results.dataCorruptionDetected ? "YES" : "NO");

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Speed calculation thread on EQEP2 in SMP test.
 *
 * Continuously reads position from EQEP2 and calculates speed based on position deltas.
 * Test case category: functionality test case
 *
 * \param arg  Thread ID passed as argument.
 */
static void App_eqepSpeedCalcThread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t lastPos = 0, posDelta, speed;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;

    TestEqep_thread2Results.instanceId = threadId;
    TestEqep_thread2Results.speedCount = 0;
    TestEqep_thread2Results.readingCount = 0;
    TestEqep_thread2Results.dataCorruptionDetected = 0;

    DebugP_log("Thread %d (Speed Calculator) started on EQEP2\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);

        /* Calculate position delta with rollover support */
        if (currentPos >= lastPos)
        {
            posDelta = currentPos - lastPos;
        }
        else
        {
            /* Rollover occurred: calculate wrapped distance */
            posDelta = (CSL_EQEP_QPOSCNT_QPOSCNT_MAX - lastPos) + currentPos + 1U;
        }

        /* CORRUPTION CHECK: Flag massive delta anomalies */
        if ((i > 0U) && (posDelta > (TEST_EQEP_SIGNAL_TEST_FREQ * 4U))) 
        {
            TestEqep_thread2Results.dataCorruptionDetected = 1;
            DebugP_log("Thread %d: Corruption detected - massive delta anomaly (prev=%u, curr=%u, delta=%u)\r\n",
                       threadId, lastPos, currentPos, posDelta);
        }

        speed = (posDelta * 1000U) / (TEST_EQEP_POSITION_READ_INTERVAL_MS);

        if (TestEqep_thread2Results.speedCount < 100)
        {
            TestEqep_thread2Results.speedValues[TestEqep_thread2Results.speedCount] = speed;
            TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount] = currentPos;
            TestEqep_thread2Results.speedCount++;
            TestEqep_thread2Results.readingCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000);
    }

    DebugP_log("Thread %d (Speed Calculator): Calculated %d speed samples, Corruption: %s\r\n",
               threadId, TestEqep_thread2Results.speedCount,
               TestEqep_thread2Results.dataCorruptionDetected ? "YES" : "NO");

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Test position read and speed calculation with core affinity.
 *
 * Creates two tasks with core affinity: one for position reading and one for speed calculation.
 * Each task operates on a different EQEP instance independently.
 * Test case category: functionality test case
 *
 * \param args  Unused argument.
 */
static void TestEqep_smpPositionReadWhileSpeedCalc(void *args)
{
    int32_t status, i;
    TaskP_Params taskParams1, taskParams2;
    EqepAppPatternParams eqepPattern = {0U};
    uint32_t baseAddr0, baseAddr1;

    DebugP_log("\n SMP Position Read + Speed Calc Test Started \r\n");

    status = SemaphoreP_constructCounting(&TestEqep_mtTestSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    baseAddr0 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    baseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);

    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);
    EQEP_clearInterruptStatus(baseAddr0, TEST_EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr1, TEST_EQEP_INT_ALL);

    EQEP_setInitialPosition(baseAddr0, 0U);
    EQEP_setPosition(baseAddr0, 0U);
    EQEP_setDecoderConfig(baseAddr0, (EQEP_CONFIG_2X_RESOLUTION |
                                      EQEP_CONFIG_QUADRATURE |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr0, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr0, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_enableModule(baseAddr0);

    EQEP_setInitialPosition(baseAddr1, 0U);
    EQEP_setPosition(baseAddr1, 0U);
    EQEP_setDecoderConfig(baseAddr1, (EQEP_CONFIG_2X_RESOLUTION |
                                      EQEP_CONFIG_QUADRATURE |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr1, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr1, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_enableModule(baseAddr1);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestEqep_task1Stack;
    taskParams1.stackSize      = sizeof(TestEqep_task1Stack);
    taskParams1.name           = "EQEPPositionReader";
    taskParams1.taskMain       = &TestEqep_positionReaderThread;
    taskParams1.args           = (void *)(uintptr_t)0;
    taskParams1.coreAffinity   = (1U << 0);

    status = TaskP_construct(&TestEqep_TaskObjs[0], &taskParams1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Thread 1 (Core 0 - Position Reader on EQEP0) spawned\r\n");

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestEqep_task2Stack;
    taskParams2.stackSize      = sizeof(TestEqep_task2Stack);
    taskParams2.name           = "EQEPSpeedCalc";
    taskParams2.taskMain       = &App_eqepSpeedCalcThread;
    taskParams2.args           = (void *)(uintptr_t)1;
    taskParams2.coreAffinity   = (1U << 1);

    status = TaskP_construct(&TestEqep_TaskObjs[1], &taskParams2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Thread 2 (Core 1 - Speed Calculator on EQEP2) spawned\r\n");

    TestEqep_initPattern(&eqepPattern);
    eqepPattern.direction = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.eqepClockFreq = 100U;
    eqepPattern.loopCnt = (TEST_EQEP_MT_TEST_DURATION_MS / (1000U / eqepPattern.eqepClockFreq));
    eqepPattern.idxEvtCnt = 1U;
    App_eqepGenerateDualPattern(&eqepPattern);

    DebugP_log("Waiting for threads to complete...\r\n");
    for (i = 0; i < 2; i++)
    {
        int32_t semStatus = SemaphoreP_pend(&TestEqep_mtTestSem, ClockP_usecToTicks((TEST_EQEP_MT_TEST_DURATION_MS + 5000U) * 1000U));
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semStatus);
    }

    TestEqep_verifyThreadResults();

    DebugP_log("Test completed\r\n");
    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);

    for (i = 0; i < 2; i++)
    {
        TaskP_destruct(&TestEqep_TaskObjs[i]);
    }
    SemaphoreP_destruct(&TestEqep_mtTestSem);
}

static void TestEqep_initPattern(EqepAppPatternParams *eqepPattern)
{
    eqepPattern->eqepClockFreq    = TEST_EQEP_SIGNAL_TEST_FREQ;
    eqepPattern->direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern->idxEvtCnt        = TEST_EQEP_EVENT_CNT;
    eqepPattern->loopCnt          = TEST_EQEP_PATTERN_GEN_LOOP_COUNT;
    eqepPattern->generateIdxPulse = TRUE;
}

/**
 * \brief  Unity test setup function.
 *
 * Called before each test case execution.
 */
void setUp(void)
{
}

/**
 * \brief  Unity test teardown function.
 *
 * Called after each test case execution.
 */
void tearDown(void)
{
}

/**
 * \brief  Main entry point for EQEP SMP tests.
 *
 * Runs all SMP test cases using Unity framework.
 * Test case category: functionality test case
 *
 * \param args  Unused argument.
 */
void test_eqep_smp_main(void *args)
{
    UNITY_BEGIN();
#if defined(SOC_AM62AX)
    Board_userExpansionHeaderEnable();
#endif
    RUN_TEST(TestEqep_smpWatchdogMonitorWhileCaptureCalc, 11980, args);
    RUN_TEST(TestEqep_smpDualInstanceQMAOperation, 11981, args);
    RUN_TEST(TestEqep_smpPositionReadWhileSpeedCalc, 11982, args);
    UNITY_END();
}

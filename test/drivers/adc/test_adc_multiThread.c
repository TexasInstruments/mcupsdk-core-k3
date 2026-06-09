/*
 * Copyright (C) 2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file test_adc_multiThread.c
 *
 *  \brief Multi-threaded test cases for the ADC driver. Implements concurrency
 *         scenarios (test cases 10856-10860) using FreeRTOS tasks, mutexes
 *         and binary/counting semaphores.
 */

/*===================================================================*/
/* Include Files                                                      */
/*===================================================================*/

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include "test_adc.h"

#if defined(SOC_AM275X) && defined(ADC_TEST_FREERTOS)

/*===================================================================*/
/*                      Macro Defines                                */
/*===================================================================*/

#define TEST_ADC_MT_TASK_PRI_HIGH       (3U)
#define TEST_ADC_MT_TASK_PRI_LOW        (2U)
#define TEST_ADC_MT_TASK_STACK_SIZE     (4U * 1024U)
#define TEST_ADC_MT_FIFO_DEPTH          (64U)
/*
 * ADC_OPENDELAY_MAX = 0x3FFFF cycles. At ~3-12 MHz ADC clock a 16-step
 * sequence can take up to ~1.5 s.  All timeouts must exceed that.
 */
/* Polling loop timeout : 3 seconds expressed in microseconds              */
#define TEST_ADC_MT_WAIT_TIMEOUT_US     (3000000U)
/* SemaphoreP_pend timeout : 10 seconds expressed in ticks (1 tick = 1 ms) */
#define TEST_ADC_MT_WAIT_TIMEOUT_TICKS  (10000U)

/*===================================================================*/
/*                      Global Variables                            */
/*===================================================================*/

/* Task stacks */
static uint8_t  TestAdc_mtTask1Stack[TEST_ADC_MT_TASK_STACK_SIZE]
                    __attribute__((aligned(32)));
static uint8_t  TestAdc_mtTask2Stack[TEST_ADC_MT_TASK_STACK_SIZE]
                    __attribute__((aligned(32)));

/* Task objects */
static TaskP_Object TestAdc_mtTask1Obj;
static TaskP_Object TestAdc_mtTask2Obj;

/* Synchronization objects shared across all multi-threaded tests */
static SemaphoreP_Object TestAdc_mtCfgMutex;     /* Serializes ADC config */
static SemaphoreP_Object TestAdc_mtJoinSem;      /* Counting sem for task join */
static SemaphoreP_Object TestAdc_mtStartSem;     /* Binary start signal */
static SemaphoreP_Object TestAdc_mtHandoffSem;   /* Binary handoff (T1 -> T2) */
static SemaphoreP_Object TestAdc_mtIsrSem;       /* Binary ISR -> Task signal */
static SemaphoreP_Object TestAdc_mtPauseSem;     /* Binary pause/resume signal */

/* HWI handle for shared interrupt scenarios */
static HwiP_Object  TestAdc_mtHwiObj;
static uint32_t     TestAdc_mtHwiInstalled = 0U;

/* Atomic flags / counters (volatile for cross-thread/ISR visibility) */
static volatile uint32_t TestAdc_mtRangeViol     = 0U;
static volatile uint32_t TestAdc_mtSamplesRead   = 0U;
static volatile uint32_t TestAdc_mtThreshChanged = 0U;
static volatile uint32_t TestAdc_mtIsrCount      = 0U;

/* Per-thread quotas for sequential FIFO read test (10858) */
static volatile uint32_t TestAdc_mt858T1Quota   = 0U;
static volatile uint32_t TestAdc_mt858T2Quota   = 0U;

/* Per-task results */
static volatile int32_t  gAdcMtTask1Status = SystemP_FAILURE;
static volatile int32_t  gAdcMtTask2Status = SystemP_FAILURE;

/* Pointer to current test parameters used by tasks/ISR */
static test_adc_testcaseParams_t *TestAdc_mtTestParams = NULL;

/*===================================================================*/
/*                      Function Declarations                        */
/*===================================================================*/

static int32_t TestAdc_mtConcurrentFifo(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_mtPollingInterrupt(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_mtSequentialFifoRead(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_mtConcurrentRangeCheck(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_mtDynamicThreshold(test_adc_testcaseParams_t *testParams);

/*===================================================================*/
/*                        Helper Functions                           */
/*===================================================================*/

static void TestAdc_mtConfigStep(uint32_t baseAddr,
                                 const test_adc_stepConfigParams_t *step)
{
    adcStepConfig_t cfg;
    cfg.mode             = step->mode;
    cfg.channel          = step->channel;
    cfg.openDelay        = step->openDelay;
    cfg.sampleDelay      = step->sampleDelay;
    cfg.rangeCheckEnable = step->rangeCheckEnable;
    cfg.averaging        = step->averaging;
    cfg.fifoNum          = step->fifoNum;
    (void)ADC_setStepParams(baseAddr, step->stepId, &cfg);
    ADC_stepEnable(baseAddr, step->stepId, TRUE);
}

static void TestAdc_mtDrainFifo(uint32_t baseAddr, uint32_t fifoNum,
                                uint32_t *count)
{
    uint32_t guard = TEST_ADC_MT_FIFO_DEPTH * 2U;
    while ((ADC_getFIFOWordCount(baseAddr, fifoNum) > 0U) && (guard > 0U))
    {
        (void)ADC_getFIFOData(baseAddr, fifoNum);
        if (count != NULL)
        {
            (*count)++;
        }
        guard--;
    }
}

static void TestAdc_mtResetSyncObjs(void)
{
    TestAdc_mtRangeViol     = 0U;
    TestAdc_mtSamplesRead   = 0U;
    TestAdc_mtThreshChanged = 0U;
    TestAdc_mtIsrCount      = 0U;
    gAdcMtTask1Status   = SystemP_FAILURE;
    gAdcMtTask2Status   = SystemP_FAILURE;
}

static int32_t TestAdc_mtCreateTaskPair(TaskP_FxnMain task1Fxn,
                                        TaskP_FxnMain task2Fxn,
                                        uint32_t pri1, uint32_t pri2,
                                        void *arg1, void *arg2)
{
    int32_t      status;
    TaskP_Params p1, p2;

    TaskP_Params_init(&p1);
    p1.priority  = pri1;
    p1.stack     = TestAdc_mtTask1Stack;
    p1.stackSize = sizeof(TestAdc_mtTask1Stack);
    p1.args      = arg1;
    p1.name      = "AdcMtTask1";
    p1.taskMain  = task1Fxn;
    status = TaskP_construct(&TestAdc_mtTask1Obj, &p1);
    if (status != SystemP_SUCCESS)
    {
        return status;
    }

    TaskP_Params_init(&p2);
    p2.priority  = pri2;
    p2.stack     = TestAdc_mtTask2Stack;
    p2.stackSize = sizeof(TestAdc_mtTask2Stack);
    p2.args      = arg2;
    p2.name      = "AdcMtTask2";
    p2.taskMain  = task2Fxn;
    status = TaskP_construct(&TestAdc_mtTask2Obj, &p2);
    if (status != SystemP_SUCCESS)
    {
        TaskP_destruct(&TestAdc_mtTask1Obj);
        return status;
    }

    return SystemP_SUCCESS;
}

static void TestAdc_mtJoinAndDestructTasks(void)
{
    int32_t i;
    for (i = 0; i < 2; i++)
    {
        SemaphoreP_pend(&TestAdc_mtJoinSem, SystemP_WAIT_FOREVER);
    }
    TaskP_destruct(&TestAdc_mtTask1Obj);
    TaskP_destruct(&TestAdc_mtTask2Obj);
}

/*===================================================================*/
/*                      Function Definitions                        */
/*===================================================================*/

/**
 * \brief  Main dispatcher for ADC multi-threaded test cases.
 *
 *  Test Category: Functionality
 *
 *   Routes execution to the specific multi-threaded test function based
 *   on testCaseName string matching. Covers concurrent FIFO access,
 *   polling/interrupt concurrency, sequential FIFO read, range checking,
 *   and dynamic threshold updates.
 *
 *  \param testParams Pointer to test case parameters
 *
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestAdc_multiThread_main(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_FAILURE;

    if (testParams == NULL)
    {
        return SystemP_FAILURE;
    }

    TestAdc_mtTestParams = testParams;
    TestAdc_mtResetSyncObjs();

    if (strstr(testParams->testCaseName,
               "concurrent FIFO0 FIFO1") != NULL)
    {
        status = TestAdc_mtConcurrentFifo(testParams);
    }
    else if (strstr(testParams->testCaseName,
                    "polling interrupt concurrent") != NULL)
    {
        status = TestAdc_mtPollingInterrupt(testParams);
    }
    else if (strstr(testParams->testCaseName,
                    "sequential FIFO read") != NULL)
    {
        status = TestAdc_mtSequentialFifoRead(testParams);
    }
    else if (strstr(testParams->testCaseName,
                    "concurrent range checking") != NULL)
    {
        status = TestAdc_mtConcurrentRangeCheck(testParams);
    }
    else if (strstr(testParams->testCaseName,
                    "dynamic threshold updates") != NULL)
    {
        status = TestAdc_mtDynamicThreshold(testParams);
    }
    else
    {
        DebugP_log("Invalid multi-thread test name: %s\r\n",
                   testParams->testCaseName);
        status = SystemP_FAILURE;
    }

    TestAdc_mtTestParams = NULL;
    return status;
}

/*===================================================================*/
/* Test 10856 : Concurrent FIFO0 / FIFO1 access from two threads      */
/*===================================================================*/

static void TestAdc_mt856_thread1(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    uint32_t i, iter;
    int32_t  result = SystemP_FAILURE;
    uint32_t totalSamples = 0U;

    /* Configure first half of steps targeting FIFO0 (mutex protected) */
    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    for (i = 0U; i < (tp->adcConfigParams.numSteps / 2U); i++)
    {
        TestAdc_mtConfigStep(baseAddr, &tp->adcConfigParams.adcSteps[i]);
    }
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    /* Wait for T2 to start ADC */
    SemaphoreP_pend(&TestAdc_mtStartSem, SystemP_WAIT_FOREVER);

    for (iter = 0U; iter < tp->adcConfigParams.numIterations; iter++)
    {
        uint32_t samples = 0U;
        uint32_t timeout = TEST_ADC_MT_WAIT_TIMEOUT_US;
        while ((ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) == 0U) &&
               (timeout > 0U))
        {
            ClockP_usleep(10U);
            timeout -= 10U;
        }
        TestAdc_mtDrainFifo(baseAddr, ADC_FIFO_NUM_0, &samples);
        totalSamples += samples;

        if ((iter + 1U) < tp->adcConfigParams.numIterations)
        {
            /* Ack T2: FIFO0 drained, safe to restart ADC */
            SemaphoreP_post(&TestAdc_mtPauseSem);
            /* Wait for T2 to confirm ADC has been restarted.
             * Two-way handshake guarantees T2 always posts this. */
            (void)SemaphoreP_pend(&TestAdc_mtHandoffSem, SystemP_WAIT_FOREVER);
        }
    }

    if (totalSamples > 0U)
    {
        result = SystemP_SUCCESS;
    }
    DebugP_log("T1 (FIFO0) total samples=%u\r\n", totalSamples);

    gAdcMtTask1Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static void TestAdc_mt856_thread2(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    uint32_t i, iter;
    int32_t  result = SystemP_FAILURE;
    uint32_t totalSamples = 0U;

    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    for (i = (tp->adcConfigParams.numSteps / 2U);
         i < tp->adcConfigParams.numSteps; i++)
    {
        TestAdc_mtConfigStep(baseAddr, &tp->adcConfigParams.adcSteps[i]);
    }
    /* Start conversion (only Thread2 drives the ADC start/restart) */
    TestAdc_moduleStart(baseAddr);
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    /* Signal Thread1 to start reading */
    SemaphoreP_post(&TestAdc_mtStartSem);

    for (iter = 0U; iter < tp->adcConfigParams.numIterations; iter++)
    {
        uint32_t samples = 0U;
        uint32_t timeout = TEST_ADC_MT_WAIT_TIMEOUT_US;
        while ((ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_1) == 0U) &&
               (timeout > 0U))
        {
            ClockP_usleep(10U);
            timeout -= 10U;
        }
        TestAdc_mtDrainFifo(baseAddr, ADC_FIFO_NUM_1, &samples);
        totalSamples += samples;

        /* Re-trigger ADC only after T1 has finished draining FIFO0.          */
        /* TestAdc_mtPauseSem (T1->T2 ack) prevents T2 from racing ahead of T1.   */
        if ((iter + 1U) < tp->adcConfigParams.numIterations)
        {
            uint32_t s;
            /* Wait for T1 to confirm FIFO0 has been drained */
            (void)SemaphoreP_pend(&TestAdc_mtPauseSem, SystemP_WAIT_FOREVER);
            /* In SINGLE_SHOT mode HW auto-clears STEPENABLE after the
             * sequence — re-enable all steps and toggle EN for a fresh edge. */
            SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
            ADC_start(baseAddr, FALSE);
            ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
            for (s = 0U; s < tp->adcConfigParams.numSteps; s++)
            {
                ADC_stepEnable(baseAddr,
                               tp->adcConfigParams.adcSteps[s].stepId, TRUE);
            }
            TestAdc_moduleStart(baseAddr);
            SemaphoreP_post(&TestAdc_mtCfgMutex);
            /* Notify T1 that ADC has been restarted */
            SemaphoreP_post(&TestAdc_mtHandoffSem);
        }
    }

    if (totalSamples > 0U)
    {
        result = SystemP_SUCCESS;
    }
    DebugP_log("T2 (FIFO1) total samples=%u\r\n", totalSamples);

    gAdcMtTask2Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static int32_t TestAdc_mtConcurrentFifo(test_adc_testcaseParams_t *testParams)
{
    int32_t  status;
    uint32_t baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("MT Test 10856: concurrent FIFO0/FIFO1 access\r\n");

    TestAdc_moduleInit(baseAddr);
    ADC_stepIdTagEnable(baseAddr, testParams->adcConfigParams.stepIdTagEnable);
    (void)ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, 1U);
    (void)ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1, 1U);
    ADC_setRange(baseAddr, testParams->adcConfigParams.highRange,
                 testParams->adcConfigParams.lowRange);

    SemaphoreP_constructMutex(&TestAdc_mtCfgMutex);
    SemaphoreP_constructBinary(&TestAdc_mtStartSem, 0U);
    SemaphoreP_constructBinary(&TestAdc_mtHandoffSem, 0U); /* T2 -> T1 : ADC restarted */
    SemaphoreP_constructBinary(&TestAdc_mtPauseSem, 0U);   /* T1 -> T2 : FIFO0 drained */
    SemaphoreP_constructCounting(&TestAdc_mtJoinSem, 0U, 2U);

    status = TestAdc_mtCreateTaskPair(&TestAdc_mt856_thread1,
                                      &TestAdc_mt856_thread2,
                                      TEST_ADC_MT_TASK_PRI_HIGH,
                                      TEST_ADC_MT_TASK_PRI_HIGH,
                                      testParams, testParams);
    if (status == SystemP_SUCCESS)
    {
        TestAdc_mtJoinAndDestructTasks();
        if ((gAdcMtTask1Status != SystemP_SUCCESS) ||
            (gAdcMtTask2Status != SystemP_SUCCESS))
        {
            status = SystemP_FAILURE;
        }
    }

    TestAdc_moduleStop(testParams);
    ADC_clearAllSteps(baseAddr);
    ADC_powerUp(baseAddr, FALSE);

    SemaphoreP_destruct(&TestAdc_mtCfgMutex);
    SemaphoreP_destruct(&TestAdc_mtStartSem);
    SemaphoreP_destruct(&TestAdc_mtHandoffSem);
    SemaphoreP_destruct(&TestAdc_mtPauseSem);
    SemaphoreP_destruct(&TestAdc_mtJoinSem);

    DebugP_log("MT Test 10856: %s\r\n",
               (status == SystemP_SUCCESS) ? "PASSED" : "FAILED");
    return status;
}

/*===================================================================*/
/* Test 10857 : Polling + Interrupt concurrent                        */
/*===================================================================*/

static void TestAdc_mt857_isr(void *handle)
{
    uint32_t baseAddr = (uint32_t)((uintptr_t)handle);
    uint32_t intrStatus;

    intrStatus = ADC_getIntrStatus(baseAddr);
    if ((intrStatus & ADC_INTR_SRC_END_OF_SEQUENCE) != 0U)
    {
        ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
        TestAdc_mtIsrCount++;
        SemaphoreP_post(&TestAdc_mtIsrSem);
    }
    /* Clear remaining and EOI */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
    ADC_writeEOI(baseAddr);
}

static void TestAdc_mt857_thread1(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    uint32_t iter;
    int32_t  result = SystemP_FAILURE;
    uint32_t totalSamples = 0U;

    DebugP_log("T1: started\r\n");
    for (iter = 0U; iter < tp->adcConfigParams.numIterations; iter++)
    {
        uint32_t samples = 0U;

        DebugP_log("T1[%u]: pend handoff\r\n", iter);
        SemaphoreP_pend(&TestAdc_mtHandoffSem, SystemP_WAIT_FOREVER);
        DebugP_log("T1[%u]: got handoff, FIFO0=%u\r\n", iter,
                   ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0));

        while (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) > 0U)
        {
            (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
            samples++;
        }
        totalSamples += samples;

        DebugP_log("T1[%u]: drained %u, post pause\r\n", iter, samples);
        SemaphoreP_post(&TestAdc_mtPauseSem);
    }

    if (totalSamples > 0U)
    {
        result = SystemP_SUCCESS;
    }
    DebugP_log("T1 (poll FIFO0) total samples=%u\r\n", totalSamples);

    gAdcMtTask1Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static void TestAdc_mt857_thread2(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    uint32_t iter;
    int32_t  result = SystemP_FAILURE;
    uint32_t totalSamples = 0U;

    DebugP_log("T2: started, numIter=%u\r\n", tp->adcConfigParams.numIterations);
    for (iter = 0U; iter < tp->adcConfigParams.numIterations; iter++)
    {
        uint32_t samples = 0U;

        DebugP_log("T2[%u]: pend ISR sem (isrCnt=%u)\r\n", iter, TestAdc_mtIsrCount);
        SemaphoreP_pend(&TestAdc_mtIsrSem, SystemP_WAIT_FOREVER);
        DebugP_log("T2[%u]: got ISR (isrCnt=%u), FIFO1=%u\r\n", iter,
                   TestAdc_mtIsrCount,
                   ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_1));

        SemaphoreP_post(&TestAdc_mtHandoffSem);

        while (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_1) > 0U)
        {
            (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_1);
            samples++;
        }
        totalSamples += samples;

        DebugP_log("T2[%u]: drained %u, pend pause\r\n", iter, samples);
        SemaphoreP_pend(&TestAdc_mtPauseSem, SystemP_WAIT_FOREVER);
        DebugP_log("T2[%u]: got pause\r\n", iter);

        if ((iter + 1U) < tp->adcConfigParams.numIterations)
        {
            uint32_t s;
            /* In SINGLE_SHOT mode, the HW auto-clears STEPENABLE after
             * END_OF_SEQUENCE.  Re-enable all steps and toggle EN to get a
             * fresh start edge. */
            ADC_start(baseAddr, FALSE);
            ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
            for (s = 0U; s < tp->adcConfigParams.numSteps; s++)
            {
                ADC_stepEnable(baseAddr,
                               tp->adcConfigParams.adcSteps[s].stepId, TRUE);
            }
            TestAdc_moduleStart(baseAddr);
            DebugP_log("T2[%u]: ADC restarted\r\n", iter);
        }
    }

    ADC_disableIntr(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);

    if (totalSamples > 0U)
    {
        result = SystemP_SUCCESS;
    }
    DebugP_log("T2 (intr FIFO1) total samples=%u\r\n", totalSamples);

    gAdcMtTask2Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static int32_t TestAdc_mtPollingInterrupt(test_adc_testcaseParams_t *testParams)
{
    int32_t     status;
    HwiP_Params hwiPrms;
    uint32_t    baseAddr = testParams->adcConfigParams.adcModule;
    uint32_t    i;

    DebugP_log("MT Test 10857: polling + interrupt concurrent\r\n");

    TestAdc_moduleInit(baseAddr);
    ADC_stepIdTagEnable(baseAddr, testParams->adcConfigParams.stepIdTagEnable);
    (void)ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, 1U);
    (void)ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1, 1U);
    ADC_setRange(baseAddr, testParams->adcConfigParams.highRange,
                 testParams->adcConfigParams.lowRange);

    /* Configure ALL steps here (not in tasks) to avoid race conditions.
     * Steps 0..N/2-1 -> FIFO0 (T1 will read), N/2..N-1 -> FIFO1 (T2 reads). */
    for (i = 0U; i < testParams->adcConfigParams.numSteps; i++)
    {
        TestAdc_mtConfigStep(baseAddr, &testParams->adcConfigParams.adcSteps[i]);
    }

    /* Enable END_OF_SEQUENCE interrupt and start the first conversion */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
    ADC_enableIntr(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);

    SemaphoreP_constructBinary(&TestAdc_mtIsrSem, 0U);
    SemaphoreP_constructBinary(&TestAdc_mtHandoffSem, 0U); /* T2 -> T1 : seq done   */
    SemaphoreP_constructBinary(&TestAdc_mtPauseSem, 0U);   /* T1 -> T2 : FIFO0 done */
    SemaphoreP_constructCounting(&TestAdc_mtJoinSem, 0U, 2U);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_ADC0_INTR;
    hwiPrms.callback = &TestAdc_mt857_isr;
    hwiPrms.args     = (void *)((uintptr_t)baseAddr);
    hwiPrms.priority = 1U;
    status = HwiP_construct(&TestAdc_mtHwiObj, &hwiPrms);
    DebugP_log("10857: HwiP_construct=%d intNum=%u\r\n", status, CONFIG_ADC0_INTR);
    if (status == SystemP_SUCCESS)
    {
        TestAdc_mtHwiInstalled = 1U;

        /* Start first ADC conversion before creating tasks */
        DebugP_log("10857: starting ADC\r\n");
        TestAdc_moduleStart(baseAddr);
        DebugP_log("10857: ADC started, intrStatus=0x%x\r\n",
                   ADC_getIntrStatus(baseAddr));

        status = TestAdc_mtCreateTaskPair(&TestAdc_mt857_thread1,
                                          &TestAdc_mt857_thread2,
                                          TEST_ADC_MT_TASK_PRI_HIGH,
                                          TEST_ADC_MT_TASK_PRI_HIGH,
                                          testParams, testParams);
        if (status == SystemP_SUCCESS)
        {
            TestAdc_mtJoinAndDestructTasks();
            if ((gAdcMtTask1Status != SystemP_SUCCESS) ||
                (gAdcMtTask2Status != SystemP_SUCCESS))
            {
                status = SystemP_FAILURE;
            }
        }

        HwiP_destruct(&TestAdc_mtHwiObj);
        TestAdc_mtHwiInstalled = 0U;
    }

    TestAdc_moduleStop(testParams);
    ADC_clearAllSteps(baseAddr);
    ADC_powerUp(baseAddr, FALSE);

    SemaphoreP_destruct(&TestAdc_mtIsrSem);
    SemaphoreP_destruct(&TestAdc_mtHandoffSem);
    SemaphoreP_destruct(&TestAdc_mtPauseSem);
    SemaphoreP_destruct(&TestAdc_mtJoinSem);

    DebugP_log("MT Test 10857: %s (ISR cnt=%u)\r\n",
               (status == SystemP_SUCCESS) ? "PASSED" : "FAILED",
               TestAdc_mtIsrCount);
    return status;
}

/*===================================================================*/
/* Test 10858 : Sequential FIFO read from two threads                 */
/*===================================================================*/

static void TestAdc_mt858_thread1(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    uint32_t i;
    int32_t  result = SystemP_SUCCESS;
    uint32_t myCount = 0U;
    uint32_t quota   = TestAdc_mt858T1Quota;

    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    for (i = 0U; i < quota; i++)
    {
        if (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) == 0U)
        {
            break;
        }
        (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
        myCount++;
        TestAdc_mtSamplesRead++;
    }
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    if ((quota > 0U) && (myCount == 0U))
    {
        result = SystemP_FAILURE;
    }

    /* Hand off to Thread2 */
    SemaphoreP_post(&TestAdc_mtHandoffSem);

    gAdcMtTask1Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static void TestAdc_mt858_thread2(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    uint32_t i;
    int32_t  result = SystemP_SUCCESS;
    uint32_t myCount = 0U;
    uint32_t quota   = TestAdc_mt858T2Quota;

    /* Wait for Thread1's signal */
    SemaphoreP_pend(&TestAdc_mtHandoffSem, SystemP_WAIT_FOREVER);

    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    for (i = 0U; i < quota; i++)
    {
        if (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) == 0U)
        {
            break;
        }
        (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
        myCount++;
        TestAdc_mtSamplesRead++;
    }
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    if ((quota > 0U) && (myCount == 0U))
    {
        result = SystemP_FAILURE;
    }

    gAdcMtTask2Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static int32_t TestAdc_mtSequentialFifoRead(
    test_adc_testcaseParams_t *testParams)
{
    int32_t  status;
    uint32_t baseAddr = testParams->adcConfigParams.adcModule;
    uint32_t i, fillTimeout;
    uint32_t prefillTarget = testParams->adcConfigParams.numSteps;
    uint32_t wordCount = 0U;

    DebugP_log("MT Test 10858: sequential FIFO read\r\n");

    TestAdc_moduleInit(baseAddr);
    ADC_stepIdTagEnable(baseAddr, testParams->adcConfigParams.stepIdTagEnable);
    (void)ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, 1U);
    ADC_setRange(baseAddr, testParams->adcConfigParams.highRange,
                 testParams->adcConfigParams.lowRange);

    /* Drain any leftover samples from a previous test */
    while (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) > 0U)
    {
        (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
    }

    /* Configure all steps to FIFO0 (this also enables each step) */
    for (i = 0U; i < testParams->adcConfigParams.numSteps; i++)
    {
        TestAdc_mtConfigStep(baseAddr, &testParams->adcConfigParams.adcSteps[i]);
    }

    /* Provide a clean rising edge on EN so a fresh sequence runs.
     * Previous test may have left EN high. */
    ADC_start(baseAddr, FALSE);
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
    TestAdc_moduleStart(baseAddr);

    /* Wait for one full sequence to deliver numSteps samples to FIFO0.
     * With AVERAGING_16 + OPENDELAY_MAX + SAMPLEDELAY_MAX, a single step
     * can take >100 ms, so allow up to 10 s for the full sequence. */
    fillTimeout = 10000U;   /* in ms */
    while ((wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0))
               < prefillTarget)
    {
        if (fillTimeout == 0U)
        {
            break;
        }
        ClockP_usleep(10000U);  /* 10 ms */
        fillTimeout -= 10U;
    }
    /* Disable steps so no new samples are queued, but keep EN asserted -
     * dropping EN clears the FIFO on AM275X.  In SINGLE_SHOT mode HW
     * already auto-cleared STEPENABLE on EoS; we re-clear defensively. */
    ADC_clearAllSteps(baseAddr);
    wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
    DebugP_log("Pre-fill FIFO0 wordCount=%u\r\n", wordCount);

    if (wordCount == 0U)
    {
        DebugP_log("MT Test 10858: FAILED (no samples produced)\r\n");
        TestAdc_moduleStop(testParams);
        ADC_clearAllSteps(baseAddr);
        ADC_powerUp(baseAddr, FALSE);
        return SystemP_FAILURE;
    }

    /* Split FIFO0 contents between the two threads. */
    TestAdc_mt858T1Quota = wordCount / 2U;
    TestAdc_mt858T2Quota = wordCount - TestAdc_mt858T1Quota;

    SemaphoreP_constructMutex(&TestAdc_mtCfgMutex);
    SemaphoreP_constructBinary(&TestAdc_mtHandoffSem, 0U);
    SemaphoreP_constructCounting(&TestAdc_mtJoinSem, 0U, 2U);

    status = TestAdc_mtCreateTaskPair(&TestAdc_mt858_thread1,
                                      &TestAdc_mt858_thread2,
                                      TEST_ADC_MT_TASK_PRI_HIGH,
                                      TEST_ADC_MT_TASK_PRI_HIGH,
                                      testParams, testParams);
    if (status == SystemP_SUCCESS)
    {
        TestAdc_mtJoinAndDestructTasks();
        if ((gAdcMtTask1Status != SystemP_SUCCESS) ||
            (gAdcMtTask2Status != SystemP_SUCCESS) ||
            (TestAdc_mtSamplesRead != wordCount))
        {
            DebugP_log("samplesRead=%u expected=%u\r\n",
                       TestAdc_mtSamplesRead, wordCount);
            status = SystemP_FAILURE;
        }
        if (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) != 0U)
        {
            DebugP_log("FIFO0 not empty after reads\r\n");
            status = SystemP_FAILURE;
        }
    }

    TestAdc_moduleStop(testParams);
    ADC_clearAllSteps(baseAddr);
    ADC_powerUp(baseAddr, FALSE);

    SemaphoreP_destruct(&TestAdc_mtCfgMutex);
    SemaphoreP_destruct(&TestAdc_mtHandoffSem);
    SemaphoreP_destruct(&TestAdc_mtJoinSem);

    DebugP_log("MT Test 10858: %s\r\n",
               (status == SystemP_SUCCESS) ? "PASSED" : "FAILED");
    return status;
}

/*===================================================================*/
/* Test 10859 : Concurrent range checking from two threads            */
/*===================================================================*/

static void TestAdc_mt859_isr(void *handle)
{
    uint32_t baseAddr = (uint32_t)((uintptr_t)handle);
    uint32_t intrStatus;

    intrStatus = ADC_getIntrStatus(baseAddr);
    if ((intrStatus & ADC_INTR_SRC_OUT_OF_RANGE) != 0U)
    {
        TestAdc_mtRangeViol = 1U;
        ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_OUT_OF_RANGE);
    }
    if ((intrStatus & ADC_INTR_SRC_END_OF_SEQUENCE) != 0U)
    {
        ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
        SemaphoreP_post(&TestAdc_mtIsrSem);
    }
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
    ADC_writeEOI(baseAddr);
    TestAdc_mtIsrCount++;
}

static void TestAdc_mt859_thread1(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    uint32_t i;
    int32_t  result = SystemP_SUCCESS;
    uint32_t samples = 0U;

    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    for (i = 0U; i < 4U; i++)
    {
        TestAdc_mtConfigStep(baseAddr, &tp->adcConfigParams.adcSteps[i]);
    }
    ADC_setRange(baseAddr, 0x400U, 0x200U);
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    /* Tell T2 that T1's steps are configured so it can safely start ADC */
    SemaphoreP_post(&TestAdc_mtStartSem);

    /* Wait for T2 to signal that the conversion sequence has completed */
    (void)SemaphoreP_pend(&TestAdc_mtPauseSem, TEST_ADC_MT_WAIT_TIMEOUT_TICKS);

    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    TestAdc_mtDrainFifo(baseAddr, ADC_FIFO_NUM_0, &samples);
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    if (samples == 0U)
    {
        result = SystemP_FAILURE;
    }
    DebugP_log("T1: samples=%u rangeViol=%u\r\n", samples, TestAdc_mtRangeViol);

    gAdcMtTask1Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static void TestAdc_mt859_thread2(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    uint32_t i;
    int32_t  result = SystemP_SUCCESS;
    uint32_t samples = 0U;

    /* Wait until T1 has configured its steps */
    SemaphoreP_pend(&TestAdc_mtStartSem, SystemP_WAIT_FOREVER);

    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    for (i = 4U; i < 8U; i++)
    {
        TestAdc_mtConfigStep(baseAddr, &tp->adcConfigParams.adcSteps[i]);
    }
    /* Range setting is shared with Thread1, last writer wins. We re-apply
     * a wider range that includes both bands so OUT_OF_RANGE only fires
     * for true out-of-band conversions. Spec mentions per-thread bands
     * but the hardware has a single range register. */
    ADC_setRange(baseAddr, 0x800U, 0x000U);
    /* Drop EN low so the upcoming moduleStart() produces a fresh rising
     * edge.  A previous test may have left EN high. */
    ADC_start(baseAddr, FALSE);
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
    ADC_enableIntr(baseAddr,
                   ADC_INTR_SRC_OUT_OF_RANGE | ADC_INTR_SRC_END_OF_SEQUENCE);
    TestAdc_moduleStart(baseAddr);
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    /* Wait for at least one EoS interrupt */
    (void)SemaphoreP_pend(&TestAdc_mtIsrSem, TEST_ADC_MT_WAIT_TIMEOUT_TICKS);

    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    TestAdc_mtDrainFifo(baseAddr, ADC_FIFO_NUM_1, &samples);
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    /* Signal T1 that conversion has finished and FIFO0 is ready */
    SemaphoreP_post(&TestAdc_mtPauseSem);

    if (samples == 0U)
    {
        result = SystemP_FAILURE;
    }
    DebugP_log("T2: samples=%u rangeViol=%u\r\n", samples, TestAdc_mtRangeViol);

    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    ADC_disableIntr(baseAddr,
                    ADC_INTR_SRC_OUT_OF_RANGE | ADC_INTR_SRC_END_OF_SEQUENCE);
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    gAdcMtTask2Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static int32_t TestAdc_mtConcurrentRangeCheck(
    test_adc_testcaseParams_t *testParams)
{
    int32_t     status;
    HwiP_Params hwiPrms;
    uint32_t    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("MT Test 10859: concurrent range checking\r\n");

    TestAdc_moduleInit(baseAddr);
    ADC_stepIdTagEnable(baseAddr, testParams->adcConfigParams.stepIdTagEnable);
    (void)ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0,
                                       testParams->adcConfigParams.fifoThreshold);
    (void)ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1,
                                       testParams->adcConfigParams.fifoThreshold);

    /* Drain any leftover samples from a previous test */
    while (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) > 0U)
    {
        (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
    }
    while (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_1) > 0U)
    {
        (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_1);
    }

    SemaphoreP_constructMutex(&TestAdc_mtCfgMutex);
    SemaphoreP_constructBinary(&TestAdc_mtStartSem, 0U);
    SemaphoreP_constructBinary(&TestAdc_mtIsrSem, 0U);
    SemaphoreP_constructBinary(&TestAdc_mtPauseSem, 0U);
    SemaphoreP_constructCounting(&TestAdc_mtJoinSem, 0U, 2U);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_ADC0_INTR;
    hwiPrms.callback = &TestAdc_mt859_isr;
    hwiPrms.args     = (void *)((uintptr_t)baseAddr);
    hwiPrms.priority = 1U;
    status = HwiP_construct(&TestAdc_mtHwiObj, &hwiPrms);
    if (status == SystemP_SUCCESS)
    {
        TestAdc_mtHwiInstalled = 1U;
        status = TestAdc_mtCreateTaskPair(&TestAdc_mt859_thread1,
                                          &TestAdc_mt859_thread2,
                                          TEST_ADC_MT_TASK_PRI_HIGH,
                                          TEST_ADC_MT_TASK_PRI_HIGH,
                                          testParams, testParams);
        if (status == SystemP_SUCCESS)
        {
            TestAdc_mtJoinAndDestructTasks();
            if ((gAdcMtTask1Status != SystemP_SUCCESS) ||
                (gAdcMtTask2Status != SystemP_SUCCESS))
            {
                status = SystemP_FAILURE;
            }
        }
        HwiP_destruct(&TestAdc_mtHwiObj);
        TestAdc_mtHwiInstalled = 0U;
    }

    TestAdc_moduleStop(testParams);
    ADC_clearAllSteps(baseAddr);
    ADC_powerUp(baseAddr, FALSE);

    SemaphoreP_destruct(&TestAdc_mtCfgMutex);
    SemaphoreP_destruct(&TestAdc_mtStartSem);
    SemaphoreP_destruct(&TestAdc_mtIsrSem);
    SemaphoreP_destruct(&TestAdc_mtPauseSem);
    SemaphoreP_destruct(&TestAdc_mtJoinSem);

    DebugP_log("MT Test 10859: %s (rangeViol=%u, isrCnt=%u)\r\n",
               (status == SystemP_SUCCESS) ? "PASSED" : "FAILED",
               TestAdc_mtRangeViol, TestAdc_mtIsrCount);
    return status;
}

/*===================================================================*/
/* Test 10860 : Dynamic threshold updates while conversions active    */
/*===================================================================*/

static void TestAdc_mt860_thread1(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    uint32_t i;
    int32_t  result = SystemP_SUCCESS;
    uint32_t totalSamples = 0U;
    uint32_t loopGuard    = 200U;

    SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
    /* Drain any leftover FIFO0 samples from a prior test */
    while (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) > 0U)
    {
        (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
    }
    for (i = 0U; i < tp->adcConfigParams.numSteps; i++)
    {
        TestAdc_mtConfigStep(baseAddr, &tp->adcConfigParams.adcSteps[i]);
    }
    (void)ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, 10U);
    /* Provide a clean rising edge on EN */
    ADC_start(baseAddr, FALSE);
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
    TestAdc_moduleStart(baseAddr);
    SemaphoreP_post(&TestAdc_mtCfgMutex);

    /* Let Thread2 begin its work */
    SemaphoreP_post(&TestAdc_mtStartSem);

    /* Drain samples until T2 has performed all 5 threshold updates,
     * yielding regularly so the lower-priority T2 can run. */
    while ((TestAdc_mtThreshChanged < 5U) && (loopGuard > 0U))
    {
        uint32_t samples = 0U;

        SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
        TestAdc_mtDrainFifo(baseAddr, ADC_FIFO_NUM_0, &samples);
        SemaphoreP_post(&TestAdc_mtCfgMutex);
        totalSamples += samples;

        /* Sleep at least one tick so T2 (lower priority) gets to run */
        ClockP_usleep(10000U);  /* 10 ms */
        loopGuard--;
    }

    if ((totalSamples == 0U) || (loopGuard == 0U))
    {
        result = SystemP_FAILURE;
    }
    DebugP_log("T1: totalSamples=%u threshChanged=%u\r\n",
               totalSamples, TestAdc_mtThreshChanged);

    gAdcMtTask1Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static void TestAdc_mt860_thread2(void *args)
{
    test_adc_testcaseParams_t *tp = (test_adc_testcaseParams_t *)args;
    uint32_t baseAddr = tp->adcConfigParams.adcModule;
    int32_t  result = SystemP_SUCCESS;
    uint32_t levels[5] = {10U, 20U, 30U, 40U, 50U};
    uint32_t idx;

    (void)tp;

    SemaphoreP_pend(&TestAdc_mtStartSem, SystemP_WAIT_FOREVER);

    for (idx = 0U; idx < 5U; idx++)
    {
        int32_t apiStatus;

        /* Space out the threshold updates so T1 can collect samples
         * between changes.  20 ms is well above one tick and lets the
         * scheduler interleave the two tasks. */
        ClockP_usleep(20000U);

        SemaphoreP_pend(&TestAdc_mtCfgMutex, SystemP_WAIT_FOREVER);
        apiStatus = ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0,
                                                 levels[idx]);
        SemaphoreP_post(&TestAdc_mtCfgMutex);
        if (apiStatus != SystemP_SUCCESS)
        {
            result = SystemP_FAILURE;
        }

        TestAdc_mtThreshChanged++;
    }

    DebugP_log("T2: threshChanged=%u\r\n", TestAdc_mtThreshChanged);

    gAdcMtTask2Status = result;
    SemaphoreP_post(&TestAdc_mtJoinSem);
}

static int32_t TestAdc_mtDynamicThreshold(
    test_adc_testcaseParams_t *testParams)
{
    int32_t  status;
    uint32_t baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("MT Test 10860: dynamic threshold updates\r\n");

    TestAdc_moduleInit(baseAddr);
    ADC_stepIdTagEnable(baseAddr, testParams->adcConfigParams.stepIdTagEnable);
    ADC_setRange(baseAddr, testParams->adcConfigParams.highRange,
                 testParams->adcConfigParams.lowRange);

    SemaphoreP_constructMutex(&TestAdc_mtCfgMutex);
    SemaphoreP_constructBinary(&TestAdc_mtStartSem, 0U);
    SemaphoreP_constructCounting(&TestAdc_mtJoinSem, 0U, 2U);

    status = TestAdc_mtCreateTaskPair(&TestAdc_mt860_thread1,
                                      &TestAdc_mt860_thread2,
                                      TEST_ADC_MT_TASK_PRI_HIGH,
                                      TEST_ADC_MT_TASK_PRI_HIGH,
                                      testParams, testParams);
    if (status == SystemP_SUCCESS)
    {
        TestAdc_mtJoinAndDestructTasks();
        if ((gAdcMtTask1Status != SystemP_SUCCESS) ||
            (gAdcMtTask2Status != SystemP_SUCCESS) ||
            (TestAdc_mtThreshChanged < 5U))
        {
            DebugP_log("threshChanged=%u (expected >=5)\r\n",
                       TestAdc_mtThreshChanged);
            status = SystemP_FAILURE;
        }
    }

    TestAdc_moduleStop(testParams);
    ADC_clearAllSteps(baseAddr);
    ADC_powerUp(baseAddr, FALSE);

    SemaphoreP_destruct(&TestAdc_mtCfgMutex);
    SemaphoreP_destruct(&TestAdc_mtStartSem);
    SemaphoreP_destruct(&TestAdc_mtJoinSem);

    DebugP_log("MT Test 10860: %s\r\n",
               (status == SystemP_SUCCESS) ? "PASSED" : "FAILED");
    return status;
}

#endif /* defined(SOC_AM275X) && defined(ADC_TEST_FREERTOS) */

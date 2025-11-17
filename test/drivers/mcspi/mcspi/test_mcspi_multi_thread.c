/*
 *  Copyright (C) 2021-25 Texas Instruments Incorporated
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
 *  \file test_mcspi_multi_thread.c
 *
 *  \brief File containing MCSPI Driver test cases for multi-threaded
 *         usecases.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <unity.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
#include <drivers/mcspi/v0/dma/mcspi_dma.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Base address and interrupt number abstraction for various SoCs */
#if defined(SOC_AM263X)

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_U_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_U_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_U_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI3_U_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI4_U_BASE)

#define MCSPI0_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI0_INTR)
#define MCSPI1_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI1_INTR)
#define MCSPI2_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI2_INTR)
#define MCSPI3_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI3_INTR)
#define MCSPI4_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI4_INTR)

#elif defined(SOC_AM62AX)

#ifdef R5F_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)

#define MCSPI0_INT_NUM                  (207U)
#define MCSPI1_INT_NUM                  (208U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (205U)
#define MCSPI4_INT_NUM                  (206U)
#endif

#ifdef A53_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)

#define MCSPI0_INT_NUM                  (208U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (209U)
#define MCSPI3_INT_NUM                  (206U)
#define MCSPI4_INT_NUM                  (209U)
#endif

#ifdef DM_R5F_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)

#define MCSPI0_INT_NUM                  (207U)
#define MCSPI1_INT_NUM                  (208U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (205U)
#define MCSPI4_INT_NUM                  (206U)
#endif

#elif defined(SOC_AM62DX)

#ifdef R5F_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)

#define MCSPI0_INT_NUM                  (207U)
#define MCSPI1_INT_NUM                  (208U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (205U)
#define MCSPI4_INT_NUM                  (206U)
#endif

#ifdef A53_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)

#define MCSPI0_INT_NUM                  (208U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (206U)
#define MCSPI4_INT_NUM                  (209U)
#endif

#ifdef C75_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)

#define MCSPI0_INT_NUM                  (1U)
#define MCSPI1_INT_NUM                  (1U)
#define MCSPI2_INT_NUM                  (2U)
#define MCSPI3_INT_NUM                  (31U)
#define MCSPI4_INT_NUM                  (31U)

#define MCSPI0_EVENT_ID                 (177U)
#define MCSPI1_EVENT_ID                 (177U)
#define MCSPI2_EVENT_ID                 (172U)
#define MCSPI3_EVENT_ID                 (173U)
#define MCSPI4_EVENT_ID                 (173U)
#endif

#elif defined(SOC_AM62X)

#ifdef A53_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)

#define MCSPI0_INT_NUM                  (204U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (208U)
#define MCSPI3_INT_NUM                  (206U)
#define MCSPI4_INT_NUM                  (209U)
#endif

#elif defined(SOC_AM275X)

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI4_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI3_CFG_BASE)

#define MCSPI0_INT_NUM                  (204U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (208U)
#define MCSPI3_INT_NUM                  (206U)
#define MCSPI4_INT_NUM                  (207U)

#define MCSPI0_EVENT_ID                 (177U)
#define MCSPI1_EVENT_ID                 (178U)
#define MCSPI2_EVENT_ID                 (172U)
#define MCSPI3_EVENT_ID                 (173U)
#define MCSPI4_EVENT_ID                 (173U)

#elif defined(SOC_AM62LX)

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI3_CFG_BASE)

#define MCSPI0_INT_NUM                  (112U)
#define MCSPI1_INT_NUM                  (113U)
#define MCSPI2_INT_NUM                  (114U)
#define MCSPI3_INT_NUM                  (115U)

#elif defined(SOC_J722S)

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)

#define MCSPI0_INT_NUM                  (204U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (206U)
#define MCSPI3_INT_NUM                  (63U)
#define MCSPI4_INT_NUM                  (207U)

#else

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI3_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI4_CFG_BASE)

#define MCSPI0_INT_NUM                  (204U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (206U)
#define MCSPI3_INT_NUM                  (63U)
#define MCSPI4_INT_NUM                  (207U)
#endif

/* Task Macros */
#define MCSPI_TASK_PRIORITY   (8U)
#define MCSPI_TASK_STACK_SIZE (32U * 1024U)

/* Macro to define the number of threads in multi instance and single instance modes */
#define TEST_MCSPI_MT_THREADS                    (2U)

/* Macro to define the number of max threads to test multi instance  */
#define TEST_MCSPI_MT_MULTI_CHANNEL_THREADS      (4U)

/* Macro that defines the number of bytes involved in a single transaction */
#define TEST_MCSPI_MT_BYTES                     (32U)

/* Macro to define the timeout used by the slave function to return failure */
#define MCSPI_SLAVE_TIMEOUT_MS   (3000U)

/* ========================================================================== */
/*                               Typedefs                                     */
/* ========================================================================== */

typedef struct MCSPI_TestParams_s {
    MCSPI_ChConfig      mcspiChConfigParams;
    MCSPI_OpenParams    mcspiOpenParams;
    uint32_t            transferLength;
    uint32_t            testcaseId;
    uint32_t            dataSize;
} MCSPI_TestParams;



/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Semaphore for marking completion of each thread */
static SemaphoreP_Object gMtSiCountSemCmp;

/* Thread related objects */
static TaskP_Object         TestMcspi_MtThreadTaskObj[TEST_MCSPI_MT_MULTI_CHANNEL_THREADS];
static uint8_t              TestMcspi_MtThreadTaskStack[TEST_MCSPI_MT_MULTI_CHANNEL_THREADS][MCSPI_TASK_STACK_SIZE];

/* Variable to hold the result of each thread */
static uint32_t TestMcspi_MtThreadResults[TEST_MCSPI_MT_MULTI_CHANNEL_THREADS];

/* Buffers for TX and RX data. This buffer is specifically to be used by DMA test cases */
uint8_t  gMcspiTxBuffer[TEST_MCSPI_MT_BYTES] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
uint8_t  gMcspiRxBuffer[TEST_MCSPI_MT_BYTES] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */
static void TestMcspi_multithreadCallback(MCSPI_Handle handle, MCSPI_Transaction *trans);
static void TestMcspi_multithreadSingleInstanceBlockingWorker(void *arg);
static void TestMcspi_multithreadSingleInstanceBlocking(void *args);
static void TestMcspi_multithreadMultiInstanceBlockingWorker(void *arg);
static void TestMcspi_multithreadMultiInstanceBlocking(void *args);
static void TestMcspi_multithreadMultiInstanceCallback(void *args);
static void TestMcspi_multithreadMultiInstanceCallbackWorker(void *arg);
static void TestMcspi_setParamsIns(MCSPI_TestParams *testParams, uint32_t tcId);
static void TestMcspi_setParamsIns1(MCSPI_TestParams *testParams, uint32_t tcId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void run_multi_threaded_tests(void *args)
{
    MCSPI_TestParams  testParams;

    TestMcspi_setParamsIns(&testParams, 8785);
    RUN_TEST(TestMcspi_multithreadSingleInstanceBlocking, 8785, (void*) &testParams);
    TestMcspi_setParamsIns(&testParams, 8421);
    RUN_TEST(TestMcspi_multithreadMultiInstanceBlocking, 8421, (void*)&testParams);
    TestMcspi_setParamsIns(&testParams, 8422);
    RUN_TEST(TestMcspi_multithreadMultiInstanceCallback, 8422, (void*)&testParams);

    return;
}

#ifdef SMP_FREERTOS
void test_main(void *args)
{
    MCSPI_TestParams  testParams;

    UNITY_BEGIN();

    TestMcspi_setParamsIns(&testParams, 8785);
    RUN_TEST(TestMcspi_multithreadSingleInstanceBlocking, 9090, (void*) &testParams);
    #if defined(SOC_AM62AX)
    /* NOTE: On AM62DX, getting data mismatch at 2nd position; all other data matches. */
    /* Only the 2nd position is overwritten, causing mismatch and hanging other test cases. */
    TestMcspi_setParamsIns(&testParams, 8421);
    RUN_TEST(TestMcspi_multithreadMultiInstanceBlocking, 9091, (void*)&testParams);
    TestMcspi_setParamsIns(&testParams, 8422);
    RUN_TEST(TestMcspi_multithreadMultiInstanceCallback, 9092, (void*)&testParams);
    #endif
    UNITY_END();

}

/**
 * @brief Unity test setup hook.
 *
 * Called before each Unity test. Left empty because tests perform their own
 * per-test setup and teardown.
 */
void setUp(void)
{
}

/**
 * @brief Unity test teardown hook.
 *
 * Called after each Unity test. Left empty because tests perform their own
 * per-test cleanup.
 */
void tearDown(void)
{
}

#endif

/* ========================================================================== */
/*                     Internal Function Definitions                          */
/* ========================================================================== */

/**
 * @brief MCSPI transfer completion callback.
 *
 * This function is used as the driver callback for asynchronous MCSPI transfers.
 * If the transaction provided an argument pointer that points to a DPL semaphore,
 * the semaphore is posted to signal transfer completion to the waiting task.
 *
 * @param handle MCSPI driver handle (unused)
 * @param trans  Pointer to the completed transaction; trans->args may be a
 *               SemaphoreP_Object* that will be posted.
 */
static void TestMcspi_multithreadCallback(MCSPI_Handle handle, MCSPI_Transaction *trans)
{
    if(trans && trans->args)
    {
        SemaphoreP_post((SemaphoreP_Object*)trans->args);
    }
}

/**
 * @brief Worker: single-instance blocking-mode multithread test.
 *
 * Each worker prepares a unique transmit pattern, issues a blocking transfer to
 * the shared MCSPI instance and validates that the received data matches the
 * transmitted pattern. The result is stored in a shared results array and a
 * counting semaphore is posted to indicate completion.
 *
 * @param arg  Worker index (cast from uintptr_t) used to derive the pattern.
 */
static void TestMcspi_multithreadSingleInstanceBlockingWorker(void *arg)
{
    uint32_t i;
    uint32_t idx = (uint32_t)(uintptr_t)arg;
    uint8_t           tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t           tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;
    int32_t status = SystemP_SUCCESS;
    int32_t dataMismatch = 0;

    for(i = 0; i < TEST_MCSPI_MT_BYTES; i++)
    {
        tempTxPtr8[i] = (uint8_t)(0xA0 ^ idx ^ i);
        tempRxPtr8[i] = 0U;
    }

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = tempTxPtr8;
    spiTransaction.rxBuf     = tempRxPtr8;
    spiTransaction.args      = NULL;

    if (idx == CONFIG_MCSPI0)
    {
        spiTransaction.channel = 1;
    }

    status = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);

    /* Verify */
    if ((status == SystemP_SUCCESS) && (spiTransaction.status == MCSPI_TRANSFER_COMPLETED))
    {
        uint8_t *tempTxPtr, *tempRxPtr;
        tempTxPtr = (uint8_t *) tempTxPtr8;
        tempRxPtr = (uint8_t *) tempRxPtr8;
        for(i = 0U; i < TEST_MCSPI_MT_BYTES; i++)
        {
            if(*tempTxPtr++ != *tempRxPtr++)
            {
                dataMismatch = 1;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
                break;
            }
        }
    }

    /* Set the result as pass/fail depending upon the results */
    TestMcspi_MtThreadResults[idx] = (status == SystemP_SUCCESS) &&
                                     (spiTransaction.status == MCSPI_TRANSFER_COMPLETED) &&
                                     (dataMismatch == 0);

    SemaphoreP_post(&gMtSiCountSemCmp);
    TaskP_exit();
}

/**
 * @brief Test harness: single-instance, blocking-mode multithread case.
 *
 * Sets up the shared MCSPI instance according to provided parameters, spawns
 * multiple worker tasks that simultaneously call the blocking transfer API, and
 * waits for them to finish. Verifies expected pass/fail behavior across workers.
 *
 * @param args  Pointer to MCSPI_TestParams containing open/chconfig settings.
 */
static void TestMcspi_multithreadSingleInstanceBlocking(void *args)
{
    uint32_t i;
    int32_t status;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

    if(gMcspiHandle[CONFIG_MCSPI0])
    {
        MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
        gMcspiHandle[CONFIG_MCSPI0] = NULL;
    }

    gMcspiHandle[CONFIG_MCSPI0] = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams );
    TEST_ASSERT_NOT_NULL(gMcspiHandle[CONFIG_MCSPI0]);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&gMtSiCountSemCmp, 0, TEST_MCSPI_MT_THREADS));

    for(i = 0; i < TEST_MCSPI_MT_THREADS; i++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCSPI_MT_BLOCK";
        taskParams.stackSize = MCSPI_TASK_STACK_SIZE;
        taskParams.stack     = TestMcspi_MtThreadTaskStack[i];
        taskParams.priority  = MCSPI_TASK_PRIORITY+i;
        taskParams.args      = (void*)(uintptr_t)i;
        taskParams.taskMain  = TestMcspi_multithreadSingleInstanceBlockingWorker;
        taskParams.coreAffinity = 1 << i;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&gMtSiCountSemCmp, SystemP_WAIT_FOREVER));
    }

    /* One test case should pass and other should fail */
    TEST_ASSERT_NOT_EQUAL_INT32(TestMcspi_MtThreadResults[0], TestMcspi_MtThreadResults[1]);

    SemaphoreP_destruct(&gMtSiCountSemCmp);

    for(i = 0; i < TEST_MCSPI_MT_THREADS; i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
}

/**
 * @brief Worker: multi-instance blocking-mode test.
 *
 * Each worker selects its MCSPI handle based on the passed index, prepares
 * a transmit pattern, issues a blocking transfer and verifies the received
 * data. Posts a counting semaphore to signal completion.
 *
 * @param arg  Worker index (cast from uintptr_t).
 */
static void TestMcspi_multithreadMultiInstanceBlockingWorker(void *arg)
{
    uint32_t i;
    uint32_t idx = (uint32_t)(uintptr_t)arg;
    uint8_t           tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t           tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;
    MCSPI_Handle      mcspiHandle;
    int32_t status = SystemP_SUCCESS;

    mcspiHandle = gMcspiHandle[idx];

    /* Fill pattern */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        tempTxPtr8[i] = (uint8_t)(0xC0 + (idx * 0x10) + i);
        tempRxPtr8[i] = 0U;
    }

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = tempTxPtr8;
    spiTransaction.rxBuf     = tempRxPtr8;
    spiTransaction.args      = NULL;

    if (idx == CONFIG_MCSPI0)
    {
        /* This function is used for both Instance 0 and Instance 1.
        * For Instance 0, chip-select is configured as CS1 in SysConfig due to external pinout,
        * so channel = 1; for other instances, channel defaults to 0.
        */
        spiTransaction.channel = 1;
    }

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify */
    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) tempTxPtr8;
    tempRxPtr = (uint8_t *) tempRxPtr8;
    for(i = 0U; i < TEST_MCSPI_MT_BYTES; i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_post(&gMtSiCountSemCmp);
    TaskP_exit();
}

/**
 * @brief Test harness: multi-instance blocking-mode case.
 *
 * Opens multiple MCSPI instances (per configuration), spawns worker tasks that
 * each use a different instance, and waits for all to complete using a counting
 * semaphore. Ensures correct operation when multiple instances are used in
 * parallel.
 *
 * @param args Pointer to MCSPI_TestParams with instance-specific settings.
 */
static void TestMcspi_multithreadMultiInstanceBlocking(void *args)
{
    uint32_t i;
    int32_t status;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&gMtSiCountSemCmp,0, TEST_MCSPI_MT_THREADS));

    for (i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        switch (i)
        {
            case CONFIG_MCSPI1:
                TestMcspi_setParamsIns1(testParams, testParams->testcaseId);
                break;
            default:
                break;
        }

        MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
        MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

        if(gMcspiHandle[i])
        {
            MCSPI_close(gMcspiHandle[i]);
            gMcspiHandle[i]=NULL;
        }

        gMcspiHandle[i] = MCSPI_open(i, mcspiOpenParams);
        TEST_ASSERT_NOT_NULL(gMcspiHandle[i]);

        status = MCSPI_chConfig(gMcspiHandle[i], mcspiChConfigParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCSPI_MT_MI_BLOCKING_REUSE";
        taskParams.stackSize = MCSPI_TASK_STACK_SIZE;
        taskParams.stack     = TestMcspi_MtThreadTaskStack[i];
        taskParams.priority  = MCSPI_TASK_PRIORITY;
        taskParams.args      = (void*)(uintptr_t)i;
        taskParams.taskMain  = TestMcspi_multithreadMultiInstanceBlockingWorker;
        taskParams.coreAffinity = 1 << i;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&gMtSiCountSemCmp, SystemP_WAIT_FOREVER));
    }

    /* Cleanup */

    SemaphoreP_destruct(&gMtSiCountSemCmp);

    for(i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);
}

/**
 * @brief Worker: multi-instance callback-mode test.
 *
 * Selects the MCSPI handle for this worker, constructs per-worker buffers and
 * a semaphore, issues an asynchronous transfer and waits for its completion
 * via the semaphore. Verifies data integrity and signals completion.
 *
 * @param arg Worker index (cast from uintptr_t).
 */
static void TestMcspi_multithreadMultiInstanceCallbackWorker(void *arg)
{
    uint32_t i;
    uint32_t idx = (uint32_t)(uintptr_t)arg;
    uint8_t           tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t           tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;
    MCSPI_Handle      mcspiHandle;
    SemaphoreP_Object transferDoneMutex;
    int32_t status;

    mcspiHandle = gMcspiHandle[idx];

    status = SemaphoreP_constructBinary(&transferDoneMutex, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Fill pattern */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        tempTxPtr8[i] = (uint8_t)(0xC0 + (idx * 0x10) + i);
        tempRxPtr8[i] = 0U;
    }

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = tempTxPtr8;
    spiTransaction.rxBuf     = tempRxPtr8;
    spiTransaction.args      = &transferDoneMutex;

    if (idx == CONFIG_MCSPI0)
    {
        spiTransaction.channel = 1;
    }

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for transfer completion */
    SemaphoreP_pend(&transferDoneMutex, SystemP_WAIT_FOREVER);

    /* Verify */
    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) tempTxPtr8;
    tempRxPtr = (uint8_t *) tempRxPtr8;
    for(i = 0U; i < (TEST_MCSPI_MT_BYTES); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_post(&gMtSiCountSemCmp);

    SemaphoreP_destruct(&transferDoneMutex);

    TaskP_exit();
}

/**
 * @brief Test harness: multi-instance, callback-mode case.
 *
 * Configures multiple MCSPI instances in callback mode, spawns a worker per
 * instance which performs an asynchronous transfer, and waits for all callbacks
 * to occur using a counting semaphore.
 *
 * @param args Pointer to MCSPI_TestParams with instance-specific settings.
 */
static void TestMcspi_multithreadMultiInstanceCallback(void *args)
{
    uint32_t i;
    int32_t status;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&gMtSiCountSemCmp,0, TEST_MCSPI_MT_THREADS));

    for (i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        switch (i)
        {
            case CONFIG_MCSPI1:
                TestMcspi_setParamsIns1(testParams, testParams->testcaseId);
                break;
            default:
                break;
        }

        MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
        MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

        mcspiOpenParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
        mcspiOpenParams->transferCallbackFxn    = TestMcspi_multithreadCallback;

        if(gMcspiHandle[i])
        {
            MCSPI_close(gMcspiHandle[i]);
            gMcspiHandle[i]=NULL;
        }

        gMcspiHandle[i] = MCSPI_open(i, mcspiOpenParams);
        TEST_ASSERT_NOT_NULL(gMcspiHandle[i]);

        status = MCSPI_chConfig(gMcspiHandle[i], mcspiChConfigParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCSPI_MT_MI_CB_REUSE";
        taskParams.stackSize = MCSPI_TASK_STACK_SIZE;
        taskParams.stack     = TestMcspi_MtThreadTaskStack[i];
        taskParams.priority  = MCSPI_TASK_PRIORITY;
        taskParams.args      = (void*)(uintptr_t)i;
        taskParams.taskMain  = TestMcspi_multithreadMultiInstanceCallbackWorker;
        taskParams.coreAffinity = 1 << i;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&gMtSiCountSemCmp, SystemP_WAIT_FOREVER));
    }

    /* Cleanup */
    SemaphoreP_destruct(&gMtSiCountSemCmp);

    for(i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }


    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);
}

/**
 * @brief Populate default MCSPI parameters for the primary instance.
 *
 * Fills in attr/open/channel configuration fields with sane defaults and then
 * applies test-case-specific adjustments based on tcId (e.g. callback mode,
 * DMA enable, data size changes, input select). This is used to prepare the
 * MCSPI_TestParams passed to test harnesses.
 *
 * @param testParams Pointer to structure to fill
 * @param tcId       Test case identifier that selects specialized options
 */
static void TestMcspi_setParamsIns(MCSPI_TestParams *testParams, uint32_t tcId)
{
    MCSPI_Config     *config = &gMcspiConfig[CONFIG_MCSPI0];
    MCSPI_Attrs      *attrParams = (MCSPI_Attrs *)config->attrs;
    MCSPI_OpenParams *openParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig   *chConfigParams = &(testParams->mcspiChConfigParams);

    /* Default Attribute Parameters */
    attrParams->baseAddr           = MCSPI0_BASE_ADDRESS;
    attrParams->inputClkFreq       = 50000000U;
    attrParams->intrNum            = MCSPI0_INT_NUM;
    attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
    attrParams->intrPriority       = 4U;
    attrParams->chMode             = MCSPI_CH_MODE_SINGLE;
    attrParams->pinMode            = MCSPI_PINMODE_4PIN;
    attrParams->initDelay          = MCSPI_INITDLY_0;

    /* Default Open Parameters */
    openParams->transferMode           = MCSPI_TRANSFER_MODE_BLOCKING;
    openParams->transferTimeout        = SystemP_WAIT_FOREVER;
    openParams->transferCallbackFxn    = NULL;
    openParams->msMode                 = MCSPI_MS_MODE_MASTER;
    openParams->mcspiDmaIndex          = -1;

    /* Default Channel Config Parameters */
    chConfigParams->chNum              = MCSPI_CHANNEL_1;
    chConfigParams->frameFormat        = MCSPI_FF_POL0_PHA0;
    chConfigParams->bitRate            = 50000000;
    chConfigParams->csPolarity         = MCSPI_CS_POL_LOW;
    testParams->dataSize               = 32;
    chConfigParams->trMode             = MCSPI_TR_MODE_TX_RX;
    chConfigParams->inputSelect        = MCSPI_IS_D0;
    chConfigParams->dpe0               = MCSPI_DPE_ENABLE;
    chConfigParams->dpe1               = MCSPI_DPE_DISABLE;
    chConfigParams->slvCsSelect        = MCSPI_SLV_CS_SELECT_0;
    chConfigParams->startBitEnable     = FALSE;
    chConfigParams->startBitPolarity   = MCSPI_SB_POL_LOW;
    chConfigParams->csIdleTime         = MCSPI_TCS0_0_CLK;
    chConfigParams->defaultTxData      = 0x0U;
    chConfigParams->txFifoTrigLvl      = 16U;
    chConfigParams->rxFifoTrigLvl      = 16U;
    testParams->testcaseId             = tcId;
    switch (tcId)
    {

       case 8785:
            testParams->dataSize               = 8;
            break;

        case 8421:
            testParams->dataSize               = 8;
            break;

        case 8422:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            break;
    }

    return;
}

/**
 * @brief Populate MCSPI parameters for instance CONFIG_MCSPI1.
 *
 * Similar to TestMcspi_setParamsIns but tailored to instance 1's base address
 * and defaults. Adjusts behavior for specific test ids as needed.
 */
static void TestMcspi_setParamsIns1(MCSPI_TestParams *testParams, uint32_t tcId)
{
    MCSPI_Config     *config = &gMcspiConfig[CONFIG_MCSPI1];
    MCSPI_Attrs      *attrParams = (MCSPI_Attrs *)config->attrs;
    MCSPI_OpenParams *openParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig   *chConfigParams = &(testParams->mcspiChConfigParams);

    /* Default Attribute Parameters */
    attrParams->baseAddr           = MCSPI1_BASE_ADDRESS;
    attrParams->inputClkFreq       = 50000000U;
    attrParams->intrNum            = MCSPI1_INT_NUM;
    attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
    attrParams->intrPriority       = 4U;
    attrParams->chMode             = MCSPI_CH_MODE_SINGLE;
    attrParams->pinMode            = MCSPI_PINMODE_4PIN;
    attrParams->initDelay          = MCSPI_INITDLY_0;

    /* Default Open Parameters */
    openParams->transferMode           = MCSPI_TRANSFER_MODE_BLOCKING;
    openParams->transferTimeout        = SystemP_WAIT_FOREVER;
    openParams->transferCallbackFxn    = NULL;
    openParams->msMode                 = MCSPI_MS_MODE_MASTER;
    openParams->mcspiDmaIndex          = -1;

    /* Default Channel Config Parameters */
    chConfigParams->chNum              = MCSPI_CHANNEL_0;
    chConfigParams->frameFormat        = MCSPI_FF_POL0_PHA0;
    chConfigParams->bitRate            = 50000000;
    chConfigParams->csPolarity         = MCSPI_CS_POL_LOW;
    testParams->dataSize               = 32;
    chConfigParams->trMode             = MCSPI_TR_MODE_TX_RX;
    chConfigParams->inputSelect        = MCSPI_IS_D0;
    chConfigParams->dpe0               = MCSPI_DPE_ENABLE;
    chConfigParams->dpe1               = MCSPI_DPE_DISABLE;
    chConfigParams->slvCsSelect        = MCSPI_SLV_CS_SELECT_0;
    chConfigParams->startBitEnable     = FALSE;
    chConfigParams->startBitPolarity   = MCSPI_SB_POL_LOW;
    chConfigParams->csIdleTime         = MCSPI_TCS0_0_CLK;
    chConfigParams->defaultTxData      = 0x0U;
    chConfigParams->txFifoTrigLvl      = 16U;
    chConfigParams->rxFifoTrigLvl      = 16U;
    switch (tcId)
    {
       case 8421:
            testParams->dataSize               = 8;
            break;

        case 8422:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            break;
    }
    return;
}


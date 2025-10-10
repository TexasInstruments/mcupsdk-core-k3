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
 *  \file test_mcspi_v0.c
 *
 *  \brief File containing MCSPI Driver test cases for version V0.
 *
 */

/* This UT demonstrates the McSPI RX and TX operation configured
 * in different configurations and all possible MCSPI instances that can be
 * configured. MCSPI2 instance is muxed with UART, so it is not tested.
 * In case of AM243 LP we, have only 3 instances available.
 *
 * This example sends a known data in the TX mode of length APP_MCSPI_MSGSIZE
 * and then receives the same in RX mode. Internal pad level loopback mode
 * is enabled to receive data.
 *
 * When transfer is completed, TX and RX buffer data are compared.
 * If data is matched, test result is passed otherwise failed.
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


/* Number of Word count */
#define APP_MCSPI_MSGSIZE                   (100U)
#define APP_MCSPI_TXONLYMSGSIZE             (5U)
#define APP_MCSPI_TRANSFER_LOOPCOUNT        (5U)
#define APP_MCSPI_PERF_LOOP_ITER_CNT        (1000U)

#define TEST_MCSPI_MT_THREADS      (2U)
#define TEST_MCSPI_MT_BYTES        (32U)


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

static SemaphoreP_Object gMtSiCountSemCmp;

static TaskP_Object         TestMcspi_MtThreadTaskObj[TEST_MCSPI_MT_THREADS];
static uint8_t              TestMcspi_MtThreadTaskStack[TEST_MCSPI_MT_THREADS][MCSPI_TASK_STACK_SIZE];

static uint32_t TestMcspi_MtThreadResults[TEST_MCSPI_MT_THREADS];

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */
static void Test_Mcspi_MultithreadCallback(MCSPI_Handle handle, MCSPI_Transaction *trans);
static void Test_Mcspi_MultithreadSingleInstanceBlockingWorker(void *arg);
static void Test_Mcspi_MultithreadSingleInstanceBlocking(void *args);
/* static void Test_Mcspi_MultithreadSingleInstanceCallbackWorker(void *arg); */
/* static void Test_Mcspi_MultithreadSingleInstanceCallback(void *args); */
static void Test_Mcspi_MultithreadMultiInstanceBlockingWorker(void *arg);
static void Test_Mcspi_MultithreadMultiInstanceBlocking(void *args);
static void Test_Mcspi_MultithreadMultiInstanceCallbackWorker(void *arg);
static void Test_Mcspi_MultithreadMultiInstanceCallback(void *args);

static void test_mcspi_set_params(MCSPI_TestParams *testParams, uint32_t tcId);
static void test_mcspi_set_params_ins1(MCSPI_TestParams *testParams, uint32_t tcId);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void run_multi_threaded_tests(void *args)
{
    MCSPI_TestParams  testParams;

    test_mcspi_set_params(&testParams, 8784);
    /* Test case will hang because of the driver fail to queue the multi thread*/
    /* RUN_TEST(Test_Mcspi_MultithreadSingleInstanceCallback, 8784, (void*) &testParams); */
    test_mcspi_set_params(&testParams, 8785);
    RUN_TEST(Test_Mcspi_MultithreadSingleInstanceBlocking, 8785, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8421);
    RUN_TEST(Test_Mcspi_MultithreadMultiInstanceBlocking, 8421, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8422);
    RUN_TEST(Test_Mcspi_MultithreadMultiInstanceCallback, 8422, (void*)&testParams);

    return;
}


/* ========================================================================== */
/*                     Internal Function Definitions                          */
/* ========================================================================== */

static void Test_Mcspi_MultithreadCallback(MCSPI_Handle handle, MCSPI_Transaction *trans)
{
    if(trans && trans->args)
    {
        SemaphoreP_post((SemaphoreP_Object*)trans->args);
    }
}

/**
 * @brief Worker function for MCSPI multi-threaded blocking test case.
 *
 * This function executes the blocking operations for the MCSPI driver
 * in a multi-threaded test scenario. It is used to validate correct
 * behavior of the driver under concurrent access conditions.
 *
 * @param arg Pointer to arguments required by the worker function.
 */
static void Test_Mcspi_MultithreadSingleInstanceBlockingWorker(void *arg)
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
    spiTransaction.channel   = gMcspiConfig[CONFIG_MCSPI0].object->chObj[0].chCfg.chNum;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = tempTxPtr8;
    spiTransaction.rxBuf     = tempRxPtr8;
    spiTransaction.args      = NULL;

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
 * @brief Test case for blocking multi-threaded MCSPI operation using DPL.
 *
 * This test validates the correct behavior of the MCSPI driver in a blocking mode
 * when accessed from multiple threads. It ensures thread safety and data integrity
 * during concurrent SPI transactions. The test leverages DPL primitives for synchronization.
 */

static void Test_Mcspi_MultithreadSingleInstanceBlocking(void *args)
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
    DebugP_assert(status == SystemP_SUCCESS);

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
        taskParams.taskMain  = Test_Mcspi_MultithreadSingleInstanceBlockingWorker;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        DebugP_assert(status == SystemP_SUCCESS);
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
#if 0
/**
 * @brief Worker function for single instance MCSPI test case.
 *
 * This function executes the test logic for a single instance of the MCSPI peripheral.
 * It is designed to be run as a thread or task, receiving its configuration via the 'arg' parameter.
 * The test validates correct operation and data transfer for the selected MCSPI instance.
 * Results and status are reported for further analysis in the test framework.
 */
static void Test_Mcspi_MultithreadSingleInstanceCallbackWorker(void *arg)
{
    uint32_t i;
    uint32_t idx = (uint32_t)(uintptr_t)arg;
    SemaphoreP_Object transferDoneMutex;
    int32_t             status = SystemP_SUCCESS;
    uint8_t           tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t           tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;

    status = SemaphoreP_constructBinary(&transferDoneMutex, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Prepare pattern */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        tempTxPtr8[i] = (uint8_t)(idx ^ i);
        tempRxPtr8[i] = 0;
    }

    /* Init transaction */
    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = gMcspiConfig[CONFIG_MCSPI0].object->chObj[0].chCfg.chNum;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = &tempTxPtr8;
    spiTransaction.rxBuf     = &tempRxPtr8;
    spiTransaction.args      = &transferDoneMutex;

    status = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for transfer completion */
    SemaphoreP_pend(&transferDoneMutex, SystemP_WAIT_FOREVER);

    /* Simple data check */
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

    SemaphoreP_destruct(&transferDoneMutex);

    TaskP_exit();
}

/**
 * @brief Test case for multithreaded access to a single MCSPI instance.
 *
 * This test verifies the behavior of the MCSPI driver when accessed by multiple threads
 * sharing the same instance. It checks for data integrity, thread safety, and proper
 * synchronization mechanisms within the driver under concurrent operations.
 */
static void Test_Mcspi_MultithreadSingleInstanceCallback(void *args)
{
    uint32_t i;
    int32_t status;
    TaskP_Params  taskParams;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

    /* Close previous */
    if(gMcspiHandle[CONFIG_MCSPI0]) { MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]); gMcspiHandle[CONFIG_MCSPI0]=NULL; }

    gMcspiHandle[CONFIG_MCSPI0] = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(gMcspiHandle[CONFIG_MCSPI0]);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Counting semaphore */
    status = SemaphoreP_constructCounting(&gMtSiCountSemCmp, 0, TEST_MCSPI_MT_THREADS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Construct semaphores and spawn tasks */
    for(i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCSPI_MT_SI";
        taskParams.stackSize = MCSPI_TASK_STACK_SIZE;
        taskParams.stack     = TestMcspi_MtThreadTaskStack[i];
        taskParams.priority  = MCSPI_TASK_PRIORITY;
        taskParams.args      = (void*)(uintptr_t)i;
        taskParams.taskMain  = Test_Mcspi_MultithreadSingleInstanceCallbackWorker;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        DebugP_assert(status == SystemP_SUCCESS);
    }

    /* Wait for all threads to complete */
    for (i = 0; i < TEST_MCSPI_MT_THREADS; i++)
    {
        status = SemaphoreP_pend(&gMtSiCountSemCmp, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Cleanup */
    SemaphoreP_destruct(&gMtSiCountSemCmp);

    for(i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

}
#endif
/**
 * @brief Worker function for simple shared MCSPI test case.
 *
 * This function executes the shared mode SPI operations for the test.
 * It is used to validate basic data transfer and synchronization in shared mode.
 */

static void Test_Mcspi_MultithreadMultiInstanceBlockingWorker(void *arg)
{
    uint32_t i;
    uint32_t idx = (uint32_t)(uintptr_t)arg;
    uint8_t           tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t           tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;
    MCSPI_Handle      mcspiHandle;
    int32_t status = SystemP_SUCCESS;

    switch (idx)
    {
        case 0:
            mcspiHandle = gMcspiHandle[CONFIG_MCSPI0];
            break;
        case 1:
            mcspiHandle = gMcspiHandle[CONFIG_MCSPI1];
            break;
        default:
            mcspiHandle = gMcspiHandle[CONFIG_MCSPI0];
            break;
    }

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

    DebugP_assert(MCSPI_transfer(mcspiHandle, &spiTransaction) == SystemP_SUCCESS);

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
 * @brief Test case for multi-threaded shared MCSPI loopback functionality.
 *
 * This test verifies the correct operation of the MCSPI driver in a shared mode
 * when accessed from multiple threads. It ensures thread safety and data integrity
 * during concurrent SPI transactions in loopback configuration. The test leverages
 * DPL primitives for synchronization.
 */
static void Test_Mcspi_MultithreadMultiInstanceBlocking(void *args)
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
            case 1:
                test_mcspi_set_params_ins1(testParams, testParams->testcaseId);
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
        DebugP_assert(status == SystemP_SUCCESS);

        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCSPI_MT_MI_BLOCKING_REUSE";
        taskParams.stackSize = MCSPI_TASK_STACK_SIZE;
        taskParams.stack     = TestMcspi_MtThreadTaskStack[i];
        taskParams.priority  = MCSPI_TASK_PRIORITY;
        taskParams.args      = (void*)(uintptr_t)i;
        taskParams.taskMain  = Test_Mcspi_MultithreadMultiInstanceBlockingWorker;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        DebugP_assert(status == SystemP_SUCCESS);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&gMtSiCountSemCmp, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&gMtSiCountSemCmp);
    /* Cleanup */
    for(i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);
}

/**
 * @brief Test case for multi-instance reuse of MCSPI worker.
 *
 * This function validates the ability to reuse multiple MCSPI instances
 * within a worker thread context. It ensures correct initialization,
 * operation, and cleanup of reused instances.
 */
static void Test_Mcspi_MultithreadMultiInstanceCallbackWorker(void *arg)
{
    uint32_t i;
    uint32_t idx = (uint32_t)(uintptr_t)arg;
    uint8_t           tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t           tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;
    MCSPI_Handle      mcspiHandle;
    SemaphoreP_Object transferDoneMutex;
    int32_t status;

    switch (idx)
    {
        case 0:
            mcspiHandle = gMcspiHandle[CONFIG_MCSPI0];
            break;
        case 1:
            mcspiHandle = gMcspiHandle[CONFIG_MCSPI1];
            break;
        default:
            mcspiHandle = gMcspiHandle[CONFIG_MCSPI0];
            break;
    }

    status = SemaphoreP_constructBinary(&transferDoneMutex, 0);
    DebugP_assert(SystemP_SUCCESS == status);

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

    DebugP_assert(MCSPI_transfer(mcspiHandle, &spiTransaction) == SystemP_SUCCESS);

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
 * @brief Test case for multi-threaded, multi-instance MCSPI callback functionality.
 *
 * This test verifies the correct operation of the MCSPI driver when accessed from multiple threads,
 * each using a separate instance. It ensures that callbacks are triggered as expected for each instance.
 * The test helps validate thread safety and proper event handling in concurrent scenarios.
 */
static void Test_Mcspi_MultithreadMultiInstanceCallback(void *args)
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
            case 1:
                test_mcspi_set_params_ins1(testParams, testParams->testcaseId);
                break;
            default:
                break;
        }

        MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
        MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

        mcspiOpenParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
        mcspiOpenParams->transferCallbackFxn    = Test_Mcspi_MultithreadCallback;

        if(gMcspiHandle[i])
        {
            MCSPI_close(gMcspiHandle[i]);
            gMcspiHandle[i]=NULL;
        }

        gMcspiHandle[i] = MCSPI_open(i, mcspiOpenParams);
        TEST_ASSERT_NOT_NULL(gMcspiHandle[i]);

        status = MCSPI_chConfig(gMcspiHandle[i], mcspiChConfigParams);
        DebugP_assert(status == SystemP_SUCCESS);

        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCSPI_MT_MI_CB_REUSE";
        taskParams.stackSize = MCSPI_TASK_STACK_SIZE;
        taskParams.stack     = TestMcspi_MtThreadTaskStack[i];
        taskParams.priority  = MCSPI_TASK_PRIORITY;
        taskParams.args      = (void*)(uintptr_t)i;
        taskParams.taskMain  = Test_Mcspi_MultithreadMultiInstanceCallbackWorker;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        DebugP_assert(status == SystemP_SUCCESS);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&gMtSiCountSemCmp, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&gMtSiCountSemCmp);
    /* Cleanup */
    for(i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }


    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);
}

/**
 * @brief Sets the parameters for the MCSPI test instance 0.
 *
 * This function configures the test parameters for the specified test case ID.
 * It is used to set the parameters for instance 0 of the MCSPI test.
 *
 * @param testParams Pointer to the MCSPI_TestParams structure to be configured.
 * @param tcId Test case ID for which the parameters are to be set.
 */
static void test_mcspi_set_params(MCSPI_TestParams *testParams, uint32_t tcId)
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
    testParams->testcaseId             = tcId;
    switch (tcId)
    {
       case 8784:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = Test_Mcspi_MultithreadCallback;
            testParams->dataSize               = 8;
            break;

       case 8785:
            testParams->dataSize               = 8;
            break;

        case 8421:
            testParams->dataSize               = 8;
            break;

        case 8422:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = Test_Mcspi_MultithreadCallback;
            testParams->dataSize               = 8;
            break;
    }

    return;
}

/**
 * @brief Configures MCSPI instance 1 parameters for testing.
 *
 * This function sets up the test parameters for MCSPI instance 1.
 * It customizes the configuration based on the provided test case ID.
 * The parameters are updated in the supplied MCSPI_TestParams structure.
 * Use this function to prepare instance 1 for multi-threaded test scenarios.
 *
 * @param testParams Pointer to the MCSPI_TestParams structure to be configured.
 * @param tcId       Test case ID used to select specific configuration.
 */
static void test_mcspi_set_params_ins1(MCSPI_TestParams *testParams, uint32_t tcId)
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
            openParams->transferCallbackFxn    = Test_Mcspi_MultithreadCallback;
            testParams->dataSize               = 8;
            break;
    }

    return;
}

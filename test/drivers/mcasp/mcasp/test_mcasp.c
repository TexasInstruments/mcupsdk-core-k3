/*
 * Copyright (C) 2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
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

/*  \file test_mcasp.c
*
*
*   \brief Test file for MCASP Driver.
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/mcasp/v1/mcasp.h>
#include <string.h>
#include <unity.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/hw_include/cslr_mcasp.h>

/* ========================================================================== */
/*                           Macro Defines                                    */
/* ========================================================================== */

#define TEST_MCASP_APP_MSGSIZE           (1280U)
#define TEST_MCASP_APP_MSG_COUNT         (2U)
#define TEST_MCASP_APP_TEST_COUNT        (2U)
#define TEST_MCASP_APP_TEST_COUNT_MT     (10U)
#define TEST_MCASP_NUM_INSTANCES         (2U)
#define TEST_MCASP_APP_TASK_STACK_SIZE   (48*1024u)
#define TEST_MCASP_APP_TASK_PRIORITY     (2U)
#define TEST_MCASP_DMA_MODE              (1U)
#define TEST_MCASP_INTERRUPT_MODE        (2U)

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

MCASP_Handle McaspHandle;

extern uint8_t gTxLoopjobBuf0[];
extern uint8_t gRxLoopjobBuf0[];
extern MCASP_Config gMcaspConfig[];

static uint8_t TestMcasp_TxBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE]__attribute__((aligned(256)));
static uint8_t TestMcasp_RxBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE]__attribute__((aligned(256)));

volatile uint32_t TestMcasp_CntRx = 0;
volatile uint32_t TestMcasp_CntTx = 0;

MCASP_Transaction TestMcasp_TxnTx[TEST_MCASP_APP_MSG_COUNT] = {0};
MCASP_Transaction TestMcasp_TxnRx[TEST_MCASP_APP_MSG_COUNT] = {0};

#ifdef ENABLE_MT_TESTS
static uint8_t TestMcasp_TxTaskStack[TEST_MCASP_APP_TASK_STACK_SIZE]__attribute__((aligned(32)));
static uint8_t TestMcasp_RxTaskStack[TEST_MCASP_APP_TASK_STACK_SIZE]__attribute__((aligned(32)));
static uint8_t TestMcasp_TaskStack[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_TASK_STACK_SIZE]__attribute__((aligned(32)));

static uint8_t TestMcasp_TxBufferMt[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE]__attribute__((aligned(256)));
static uint8_t TestMcasp_RxBufferMt[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE]__attribute__((aligned(256)));

volatile uint32_t TestMcasp_CntRxMt[TEST_MCASP_NUM_INSTANCES] = {0};
volatile uint32_t TestMcasp_CntTxMt[TEST_MCASP_NUM_INSTANCES] = {0};
volatile int32_t TestMcasp_ThreadResult[TEST_MCASP_NUM_INSTANCES] = { SystemP_SUCCESS };

MCASP_Transaction TestMcasp_TxnTxMt[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT] = {0};
MCASP_Transaction TestMcasp_TxnRxMt[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT] = {0};

static SemaphoreP_Object TestMcasp_MultiSem[TEST_MCASP_NUM_INSTANCES];
static TaskP_Object TestMcasp_TaskObj[TEST_MCASP_NUM_INSTANCES];
static TaskP_Object TestMcasp_TxTaskObj;
static TaskP_Object TestMcasp_RxTaskObj;
static SemaphoreP_Object TestMcasp_SemTxDone;
static SemaphoreP_Object TestMcasp_SemRxDone;
static SemaphoreP_Object *TestMcasp_SemTxDonePtr = NULL;
static SemaphoreP_Object *TestMcasp_SemRxDonePtr = NULL;
#endif

/* ========================================================================== */
/*                  Function Declarations                                     */
/* ========================================================================== */

static void Test_Mcasp_LoopbackTransfer(void* args);
static void Test_Mcasp_DmaIcntsNegative(void *args);
static void Test_Mcasp_NegativeNullBuffer(void *args);
static void Test_Mcasp_NegativeBufferWithdraw(void *args);
static void Test_Mcasp_NegativeMultipleOpen(void *args);
static void Test_Mcasp_SelectConfig(int32_t mode, void *args);
static void Test_Mcasp_LoopbackTxncount(void *args);

#ifdef ENABLE_MT_TESTS
static void Test_Mcasp_MultiThreadCreate(void *args);
static void Test_Mcasp_TxcbMt(MCASP_Handle handle, MCASP_Transaction *transaction);
static void Test_Mcasp_RxcbMt(MCASP_Handle handle, MCASP_Transaction *transaction);
static void Test_Mcasp_LoopbackTransferMultithread(void *args);
static void Test_Mcasp_TxTask(void *args);
static void Test_Mcasp_RxTask(void *args);
static void Test_Mcasp_InstanceThread(void *args);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();
    #ifdef ENABLE_MT_TESTS
    RUN_TEST(Test_Mcasp_MultiThreadCreate, 8451,NULL);
    #endif
    Test_Mcasp_SelectConfig(TEST_MCASP_INTERRUPT_MODE,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(Test_Mcasp_LoopbackTransfer, 8343, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    Test_Mcasp_SelectConfig(TEST_MCASP_DMA_MODE,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(Test_Mcasp_LoopbackTransfer, 8344, (void*)&gMcaspOpenParams[CONFIG_MCASP1]);
    RUN_TEST(Test_Mcasp_LoopbackTransfer, 8345, (void*)&gMcaspOpenParams[CONFIG_MCASP2]);
    #ifdef ENABLE_MT_TESTS
    RUN_TEST(Test_Mcasp_LoopbackTransferMultithread, 8346, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    #endif
    RUN_TEST(Test_Mcasp_NegativeMultipleOpen, 8347, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(Test_Mcasp_NegativeBufferWithdraw, 8348, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(Test_Mcasp_NegativeNullBuffer, 8349, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(Test_Mcasp_DmaIcntsNegative, 8350, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(Test_Mcasp_LoopbackTxncount, 8453, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    UNITY_END();
    return;
}

void setUp(void)
{
    /* nothing to do */
}
void tearDown(void)
{
     /* nothing to do */
}

/**
 * \brief  Test MCASP loopback transfer.
 *
 * This test verifies basic loopback functionality for the MCASP instance.
 * It initializes buffers, submits transactions, and checks data integrity after transfer.
 * Test case category: functionality test case
 */
static void Test_Mcasp_LoopbackTransfer(void *args)
{
    uint32_t status = SystemP_SUCCESS;
    uint32_t i=0, j=0;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instanceId = (uint32_t)(openParams - &gMcaspOpenParams[0]);/* Compute instance index from pointer arithmetic */

    MCASP_close(gMcaspHandle[instanceId]);
    gMcaspHandle[instanceId] = NULL;

    openParams->txLoopjobBuf = gTxLoopjobBuf0; /* Common TX loopjob buffer */
    openParams->rxLoopjobBuf = gRxLoopjobBuf0; /* Common RX loopjob buffer */

    McaspHandle = MCASP_open(instanceId, openParams);

    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;
    /* Memfill buffers */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_TxBuffer[i][j] = j % 256;
            TestMcasp_RxBuffer[i][j] = 0U;
        }
    }

    CacheP_wb(TestMcasp_TxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_RxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i] = 0xa5;
        gRxLoopjobBuf0[i] = 0;
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*) &TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(McaspHandle,  &TestMcasp_TxnRx[i]);
    }

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*) &TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(McaspHandle, &TestMcasp_TxnTx[i]);
    }


    status = MCASP_startTransferRx(McaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferTx(McaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);
    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT ) ||
           (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT ))
    {
        /* wait for transfer completion. */
    }

    MCASP_stopTransferRx(McaspHandle);
    MCASP_stopTransferTx(McaspHandle);

    /* withdraw the buffers submitted to driver. */
    if(SystemP_SUCCESS == status)
    {
        MCASP_Transaction *transaction;
        do {
            transaction = MCASP_withdrawRx(McaspHandle);
        }while (transaction != NULL);
        do {
            transaction = MCASP_withdrawTx(McaspHandle);
        }while (transaction != NULL);
    }

    /* Invalidate RX buffer only for DMA mode */
    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_RxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    if(SystemP_SUCCESS == status)
    {
        /* Compare data */
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
            {
                if(TestMcasp_TxBuffer[i][j] != TestMcasp_RxBuffer[i][j])
                {
                    status = SystemP_FAILURE;   /* Data mismatch */
                }
            }
        }
    }

    /* Final Unity assert */
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP loopback transfer data mismatch");
    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    MCASP_close(McaspHandle);
    McaspHandle = NULL;
    return;
}

#ifdef ENABLE_MT_TESTS

/**
 * \brief  Test MCASP loopback in multithreaded mode.
 *
 * This test verifies loopback functionality when TX and RX operations
 * are executed in separate threads. It ensures data integrity and
 * proper synchronization between threads.
 * Test case category: functionality test case
 */
static void Test_Mcasp_LoopbackTransferMultithread(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i, j, retry;
    uint32_t found = 0;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Transaction *transaction;

    /* Reset counters */
    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;

    /* Close if already open and reopen */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    McaspHandle = MCASP_open(CONFIG_MCASP0, openParams);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_TxBuffer[i][j] = j % 256;
            TestMcasp_RxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_TxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_RxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i] = 0xa5;
        gRxLoopjobBuf0[i] = 0;
    }
    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    /* Construct semaphores */
    SemaphoreP_constructBinary(&TestMcasp_SemTxDone, 0);
    SemaphoreP_constructBinary(&TestMcasp_SemRxDone, 0);
    TestMcasp_SemTxDonePtr = &TestMcasp_SemTxDone;
    TestMcasp_SemRxDonePtr = &TestMcasp_SemRxDone;

    /* Create RX task first so that RX starts before TX */
    TaskP_Params taskPrms;
    TaskP_Params_init(&taskPrms);
    taskPrms.name = "MCASP RX Task";
    taskPrms.stackSize = TEST_MCASP_APP_TASK_STACK_SIZE;
    taskPrms.stack = TestMcasp_RxTaskStack;
    taskPrms.priority = TEST_MCASP_APP_TASK_PRIORITY;
    taskPrms.args = openParams;
    taskPrms.taskMain = Test_Mcasp_RxTask;
    status = TaskP_construct(&TestMcasp_RxTaskObj, &taskPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    TaskP_Params_init(&taskPrms);
    taskPrms.name = "MCASP TX Task";
    taskPrms.stackSize = TEST_MCASP_APP_TASK_STACK_SIZE;
    taskPrms.stack = TestMcasp_TxTaskStack;
    taskPrms.priority = TEST_MCASP_APP_TASK_PRIORITY;
    taskPrms.args = openParams;
    taskPrms.taskMain = Test_Mcasp_TxTask;
    status = TaskP_construct(&TestMcasp_TxTaskObj, &taskPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Wait for both tasks to signal completion */
    (void)SemaphoreP_pend(&TestMcasp_SemRxDone, SystemP_WAIT_FOREVER);
    (void)SemaphoreP_pend(&TestMcasp_SemTxDone, SystemP_WAIT_FOREVER);

    /* Stop transfers */
    MCASP_stopTransferRx(McaspHandle);
    MCASP_stopTransferTx(McaspHandle);

    /* Withdraw any remaining buffers with retries */
    for (retry = 0; retry < 10; retry++)
    {
        do {
            transaction = MCASP_withdrawRx(McaspHandle);
            if (transaction)
            {
                found = 1;
            }
        } while (transaction != NULL);
        do {
            transaction = MCASP_withdrawTx(McaspHandle);
            if (transaction)
            {
                found = 1;
            }
        } while (transaction != NULL);
        if (!found)
        {
            break;
        }
        ClockP_usleep(1000); /* Wait 1ms and try again */
    }

    CacheP_inv(TestMcasp_RxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);

    if(SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
            {
                if(TestMcasp_TxBuffer[i][j] != TestMcasp_RxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP multithread loopback data mismatch");
    /* Cleanup */
    TaskP_destruct(&TestMcasp_TxTaskObj);
    TaskP_destruct(&TestMcasp_RxTaskObj);
    SemaphoreP_destruct(&TestMcasp_SemTxDone);
    SemaphoreP_destruct(&TestMcasp_SemRxDone);
    TestMcasp_SemTxDonePtr = NULL;
    TestMcasp_SemRxDonePtr = NULL;
    MCASP_close(McaspHandle);
    return;
}

/**
 * \brief  MCASP transmit task for multithreaded loopback test.
 *
 * This task handles the transmit side of the MCASP multithreaded test.
 * It submits transmit transactions and waits for completion via semaphore.
 * Test case category: task support function
 */
static void Test_Mcasp_TxTask(void *args)
{
    uint32_t i;
    /* Prepare TX transactions */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*) &TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(McaspHandle, &TestMcasp_TxnTx[i]);
    }
    /* Start TX after RX started (assumed) */
    int32_t status = MCASP_startTransferTx(McaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);
    /* Task waits until semaphore is posted by callback, then exits */
    (void)SemaphoreP_pend(&TestMcasp_SemTxDone, SystemP_WAIT_FOREVER);
    SemaphoreP_post(&TestMcasp_SemTxDone); /* Allow main test to also pend */
    TaskP_exit();
}

/**
 * \brief  MCASP receive task for multithreaded loopback test.
 *
 * This task handles the receive side of the MCASP multithreaded test.
 * It submits receive transactions and waits for completion via semaphore.
 * Test case category: task support function
 */
static void Test_Mcasp_RxTask(void *args)
{
    uint32_t i;
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*) &TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(McaspHandle,  &TestMcasp_TxnRx[i]);
    }
    int32_t status = MCASP_startTransferRx(McaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);
    (void)SemaphoreP_pend(&TestMcasp_SemRxDone, SystemP_WAIT_FOREVER);
    SemaphoreP_post(&TestMcasp_SemRxDone); /* Allow main test to also pend */
    TaskP_exit();
}

#endif
/**
 * \brief  MCASP transmit callback for single-threaded mode.
 *
 * This callback is invoked upon completion of a transmit transaction in single-threaded mode.
 * It manages transaction submission and completion signaling.
 * Test case category: callback support function
 */
void mcasp_txcb(MCASP_Handle McaspHandle,
                          MCASP_Transaction *transaction)
{
    if (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT)
    {
        TestMcasp_CntTx++;
        if (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT)
        {
            MCASP_submitTx(McaspHandle, transaction);
        }
        #ifdef ENABLE_MT_TESTS
        else
        {
            /* Final completion */
            if(TestMcasp_SemTxDonePtr != NULL)
            {
                SemaphoreP_post(TestMcasp_SemTxDonePtr);
            }
        }
        #endif
    }
}

/**
 * \brief  MCASP receive callback for single-threaded mode.
 *
 * This callback is invoked upon completion of a receive transaction in single-threaded mode.
 * It manages transaction submission and completion signaling.
 * Test case category: callback support function
 */
void mcasp_rxcb(MCASP_Handle McaspHandle,
                          MCASP_Transaction *transaction)
{
    if (TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT)
    {
        TestMcasp_CntRx++;
        if (TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT)
        {
            MCASP_submitRx(McaspHandle, transaction);
        }
        #ifdef ENABLE_MT_TESTS
        else
        {
            if(TestMcasp_SemRxDonePtr != NULL)
            {
                SemaphoreP_post(TestMcasp_SemRxDonePtr);
            }
        }
        #endif
    }
}

/**
 * \brief  Test MCASP driver with invalid DMA transaction counts.
 *
 * This test validates driver behavior for invalid DMA transaction counts,
 * including size mismatches and out-of-bounds transaction counts.
 * Test case category: negative test case
 */
static void Test_Mcasp_DmaIcntsNegative(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Handle h;
    int32_t status;

    /* Larger buffers to accommodate loopjob counts */
    static uint32_t txBufA[2048] __attribute__((aligned(64)));
    static uint32_t txBufB[2048] __attribute__((aligned(64)));
    static uint32_t rxBufA[2048] __attribute__((aligned(64)));

    /* TX size mismatch (initDone == 1 path) */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    h = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(h);
    MCASP_Object *obj = ((MCASP_Config*)h)->object;
    uint32_t ljCntWordsTx = obj->XmtObj.txnLoopjob.count; /* required TX word count */
    TEST_ASSERT_TRUE_MESSAGE(ljCntWordsTx > 0 && ljCntWordsTx <= 2048, "Loopjob TX count out of test buffer range");

    MCASP_Transaction txTxnOk  = { .buf = txBufA, .count = ljCntWordsTx };
    uint32_t badTxCnt = (ljCntWordsTx > 1U) ? (ljCntWordsTx - 1U) : (ljCntWordsTx + 1U);
    MCASP_Transaction txTxnBad = { .buf = txBufB, .count = badTxCnt };

    /* Prime with valid TX */
    status = MCASP_submitTx(h, &txTxnOk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    /* Mismatched TX */
    status = MCASP_submitTx(h, &txTxnBad);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    MCASP_close(h);

    /* RX size mismatch (initDone == 1 path) */
    h = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(h);
    obj = ((MCASP_Config*)h)->object;
    uint32_t ljCntWordsRx = obj->RcvObj.txnLoopjob.count;
    TEST_ASSERT_TRUE_MESSAGE(ljCntWordsRx > 0 && ljCntWordsRx <= 2048, "Loopjob RX count out of test buffer range");

    MCASP_Transaction rxTxnOk  = { .buf = rxBufA, .count = ljCntWordsRx };
    uint32_t badRxCnt = (ljCntWordsRx > 1U) ? (ljCntWordsRx - 1U) : (ljCntWordsRx + 1U);
    MCASP_Transaction rxTxnBad = { .buf = rxBufA, .count = badRxCnt };

    status = MCASP_submitRx(h, &rxTxnOk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_submitRx(h, &rxTxnBad);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    MCASP_close(h);

    /* Out-of-bounds icnt (override + initDone == 1 path) */
    h = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(h);
    /* Prime a valid TX submit so txDmaIcnt.initDone becomes 1 */
    obj = ((MCASP_Config*)h)->object;
    const MCASP_Attrs *attrs = ((MCASP_Config*)h)->attrs;
    uint32_t waterLevelTx = (attrs->txFifoWaterLevel != 0U) ? attrs->txFifoWaterLevel : 1U;
    uint32_t primeCntTx = obj->XmtObj.txnLoopjob.count;
    MCASP_Transaction primeTx = { .buf = txBufA, .count = primeCntTx };
    status = MCASP_submitTx(h, &primeTx);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    /* Valid override (same as loopjob) */
    status = MCASP_setTxTxnCount(h, primeCntTx);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    /* Compute an overflow transaction count in words: (MCASP_ICNT2_MAX+1)*waterLevel */
    uint32_t overflowTxCnt = (65535U + 1U) * waterLevelTx; /* 65536 * waterLevel */
    status = MCASP_setTxTxnCount(h, overflowTxCnt);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    /* Repeat for RX */
    uint32_t waterLevelRx = (attrs->rxFifoWaterLevel != 0U) ? attrs->rxFifoWaterLevel : 1U;
    uint32_t primeCntRx = obj->RcvObj.txnLoopjob.count;
    MCASP_Transaction primeRx = { .buf = rxBufA, .count = primeCntRx };
    status = MCASP_submitRx(h, &primeRx);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_setRxTxnCount(h, primeCntRx);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    uint32_t overflowRxCnt = (65535U + 1U) * waterLevelRx;
    status = MCASP_setRxTxnCount(h, overflowRxCnt);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    MCASP_close(h);

    /* Loopjob mismatch on fresh open */
    h = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(h);
    obj = ((MCASP_Config*)h)->object;
    ljCntWordsTx = obj->XmtObj.txnLoopjob.count;
    MCASP_Transaction txTxnMismatch = { .buf = txBufA, .count = ljCntWordsTx + 1U };
    status = MCASP_submitTx(h, &txTxnMismatch);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    MCASP_close(h);
}

/**
 * \brief  Configure MCASP instance based on mode.
 *
 * This function sets the MCASP open parameters and hardware attributes
 * based on the specified transfer mode (DMA or interrupt mode).
 * Test case category: utility support function
 */
void Test_Mcasp_SelectConfig(int mode, void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[CONFIG_MCASP0].attrs;

    /* Set transfer mode */
    switch (mode)
    {
        case TEST_MCASP_DMA_MODE:
            openParams->transferMode = MCASP_TRANSFER_MODE_DMA;
            attrs->hwCfg.rx.fmt = (uint32_t) 0x180F0U;
            attrs->hwCfg.rx.intCtl = (uint32_t) 0x0U;
            attrs->hwCfg.rx.evtCtl = (uint32_t) 0x1U;

            attrs->hwCfg.tx.fmt = (uint32_t)0x180F0U;
            attrs->hwCfg.tx.intCtl = (uint32_t) 0x0U;
            attrs->hwCfg.tx.evtCtl = (uint32_t) 0x1U;
            break;
        case TEST_MCASP_INTERRUPT_MODE:
            openParams->transferMode = MCASP_TRANSFER_MODE_INTERRUPT;
            attrs->hwCfg.rx.fmt = (uint32_t) 0x180F8U;
            attrs->hwCfg.rx.intCtl = (uint32_t) 0x20U;
            attrs->hwCfg.rx.evtCtl = (uint32_t) 0x0U;

            attrs->hwCfg.tx.fmt = (uint32_t)  0x180F8U;
            attrs->hwCfg.tx.intCtl = (uint32_t) 0x20U;
            attrs->hwCfg.tx.evtCtl = (uint32_t) 0x0U;
            break;
        default:
            /* Invalid mode */
            break;
    }

}

/**
 * \brief  Test MCASP driver with NULL buffer pointers.
 *
 * This test ensures the driver handles NULL buffer pointers gracefully
 * and does not perform unintended operations.
 * Test case category: negative test case
 */
static void Test_Mcasp_NegativeNullBuffer(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Handle handle;
    int32_t status;
    uint32_t i,j;

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    handle = MCASP_open(CONFIG_MCASP0, openParams);

    /* Initialize TX and RX buffers with test data */
    for ( i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for ( j = 0; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_TxBuffer[i][j] = 0xA5;
            TestMcasp_RxBuffer[i][j] = 0x00;
        }
    }

    /* Intentionally submit NULL transaction pointers */
    status = MCASP_submitTx(handle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = MCASP_submitRx(handle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Start transfers (should not move any data) */
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Wait briefly to allow any (unexpected) activity */
    ClockP_usleep(100000);

    /* Stop transfers */
    MCASP_stopTransferTx(handle);
    MCASP_stopTransferRx(handle);

    MCASP_close(handle);
}

/**
 * \brief  Test MCASP buffer withdraw with no submitted buffers.
 *
 * This test checks that MCASP_withdrawTx/Rx returns NULL when no buffer is present,
 * ensuring correct driver behavior.
 * Test case category: negative test case
 */
static void Test_Mcasp_NegativeBufferWithdraw(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Handle handle;
    MCASP_Transaction *txn;
    int32_t status;

    /* Open MCASP instance */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    /* Do not submit any buffer, directly call withdraw */
    txn = MCASP_withdrawTx(handle);
    TEST_ASSERT_NULL(txn); /* Should return NULL, nothing to withdraw */

    txn = MCASP_withdrawRx(handle);
    TEST_ASSERT_NULL(txn); /* Should return NULL, nothing to withdraw */

    /* Start and stop transfers to confirm no impact */
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    ClockP_usleep(100000);
    MCASP_stopTransferTx(handle);
    MCASP_stopTransferRx(handle);

    MCASP_close(handle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "mcasp_negative_buffer_withdraw transfer failure");
}

/**
 * \brief  Test MCASP multiple open attempts.
 *
 * This test verifies that opening an already open MCASP instance fails as expected.
 * Test case category: negative test case
 */
static void Test_Mcasp_NegativeMultipleOpen(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Handle handle1, handle2;

    /* Open MCASP instance first time */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    handle1 = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle1);

    /* Attempt to open again without closing */
    handle2 = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NULL(handle2); /* Should fail or return NULL */

    /* Close the instance */
    MCASP_close(handle2);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle1, "First open failed in multiple_open test");
}

/**
 * \brief  Test MCASP loopback with custom transaction counts.
 *
 * This test validates loopback operation with custom transaction counts,
 * ensuring correct data transfer for various transaction sizes.
 * Test case category: functionality test case
 */
static void Test_Mcasp_LoopbackTxncount(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status = SystemP_SUCCESS;
    uint32_t i,j;
    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;
    /* Re-open instance fresh */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle h = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(h);

    /* Access driver object to fetch loopjob transaction size (required by setTxnCount API) */
    MCASP_Object *obj = ((MCASP_Config*)h)->object;
    uint32_t txLjCnt = obj->XmtObj.txnLoopjob.count; /* count units consistent with previous tests */
    uint32_t rxLjCnt = obj->RcvObj.txnLoopjob.count;
    TEST_ASSERT_TRUE(txLjCnt > 0U);
    TEST_ASSERT_TRUE(rxLjCnt > 0U);

    /* Prepare buffers */
    for(i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for(j = 0; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_TxBuffer[i][j] = (uint8_t)(j & 0xFF);
            TestMcasp_RxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_TxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_RxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i] = 0x5A;
        gRxLoopjobBuf0[i] = 0;
    }
    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    /* Set desired transaction counts BEFORE starting transfers */
    status = MCASP_setTxTxnCount(h, txLjCnt); TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_setRxTxnCount(h, rxLjCnt); TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestMcasp_CntRx = 0; TestMcasp_CntTx = 0;

    /* Queue RX then TX transactions sized to loopjob count */
    for(i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*)&TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = rxLjCnt; /* match configured txn count */
        TestMcasp_TxnRx[i].timeout = 0xFFFFFFU;
        status = MCASP_submitRx(h, &TestMcasp_TxnRx[i]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
    for(i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*)&TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = txLjCnt; /* match configured txn count */
        TestMcasp_TxnTx[i].timeout = 0xFFFFFFU;
        status = MCASP_submitTx(h, &TestMcasp_TxnTx[i]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    status = MCASP_startTransferRx(h); TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(h); TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for completion */
    }

    MCASP_stopTransferRx(h);
    MCASP_stopTransferTx(h);

    if(openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_RxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    /* Compare only the portion actually transferred: txLjCnt units each transaction */
    if(status == SystemP_SUCCESS)
    {
        uint32_t bytesEach = txLjCnt * 4U; /* existing code uses count=bytes/4; mirror pattern */
        if(bytesEach > TEST_MCASP_APP_MSGSIZE)
        {
            bytesEach = TEST_MCASP_APP_MSGSIZE;
        }
        for(i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for(j = 0; j < bytesEach; j++)
            {
                if(TestMcasp_TxBuffer[i][j] != TestMcasp_RxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "TxnCount loopback data mismatch");
    MCASP_close(h);
}

#ifdef ENABLE_MT_TESTS

/**
 * \brief  MCASP transmit callback used in multi-instance multithreaded tests.
 *
 * Re-submits transaction until the per-instance target transfer count is reached.
 * Test case category: callback support function
 */
void Test_Mcasp_TxcbMt(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    uint32_t *testCntTx = (uint32_t *)transaction->args;
    *testCntTx = *testCntTx + 1; /* increment every time */

    if (*testCntTx < TEST_MCASP_APP_TEST_COUNT_MT)
    {
        MCASP_submitTx(handle, transaction);
    }
}

/**
 * \brief  MCASP receive callback used in multi-instance multithreaded tests.
 *
 * Re-submits transaction until the per-instance target receive count is reached.
 * Test case category: callback support function
 */
void Test_Mcasp_RxcbMt(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    uint32_t *testCntRx = (uint32_t *)transaction->args;
    *testCntRx = *testCntRx + 1; /* increment every time */

    if (*testCntRx < TEST_MCASP_APP_TEST_COUNT_MT)
    {
        MCASP_submitRx(handle, transaction);
    }
}

/**
 * \brief  Thread function for individual MCASP instance in multithreaded test.
 *
 * This function executes transmit and receive operations for a specific
 * MCASP instance in a multithreaded environment. It initializes instance-
 * specific buffers, submits transactions, starts transfers, monitors
 * completion, validates the received data, and signals the main thread
 * upon completion.
 * Test case category: functionality test case
 */
static void Test_Mcasp_InstanceThread(void *args)
{
    uint32_t inst = (uint32_t)(uintptr_t)args;
    int32_t status = SystemP_SUCCESS;
    uint32_t j, k;
    MCASP_Handle mcaspHandle;

    /*  Initialize buffer values with a unique offset for each MCASP instance, */
    uint32_t bufStartOffset = 64 * inst;
    for (j = 0U; j < TEST_MCASP_APP_MSG_COUNT; j++)
    {
        for (k = 0U; k < TEST_MCASP_APP_MSGSIZE; k++)
        {
            TestMcasp_TxBufferMt[inst][j][k] = (bufStartOffset + k) % 256;
            TestMcasp_RxBufferMt[inst][j][k] = 0U;
        }
    }
    CacheP_wb(TestMcasp_TxBufferMt[inst], sizeof(TestMcasp_TxBufferMt[inst]), CacheP_TYPE_ALLD);
    CacheP_wb(TestMcasp_RxBufferMt[inst], sizeof(TestMcasp_RxBufferMt[inst]), CacheP_TYPE_ALLD);

    mcaspHandle = MCASP_getHandle(inst);

    /* Submit TX */
    for (j = 0U; j < TEST_MCASP_APP_MSG_COUNT; j++)
    {
        TestMcasp_TxnTxMt[inst][j].buf = (void*)&TestMcasp_TxBufferMt[inst][j][0];
        TestMcasp_TxnTxMt[inst][j].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_TxnTxMt[inst][j].timeout = 0xFFFFFF;
        TestMcasp_TxnTxMt[inst][j].args = (void*)&TestMcasp_CntTxMt[inst];
        MCASP_submitTx(mcaspHandle, &TestMcasp_TxnTxMt[inst][j]);
    }

    /* Submit RX */
    for (j = 0U; j < TEST_MCASP_APP_MSG_COUNT; j++)
    {
        TestMcasp_TxnRxMt[inst][j].buf = (void*)&TestMcasp_RxBufferMt[inst][j][0];
        TestMcasp_TxnRxMt[inst][j].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_TxnRxMt[inst][j].timeout = 0xFFFFFF;
        TestMcasp_TxnRxMt[inst][j].args = (void*)&TestMcasp_CntRxMt[inst];
        MCASP_submitRx(mcaspHandle, &TestMcasp_TxnRxMt[inst][j]);
    }

    /* Start transfers */
    status = MCASP_startTransferRx(mcaspHandle);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(mcaspHandle);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    uint32_t timeout = 10000U;
    while (((TestMcasp_CntRxMt[inst] < TEST_MCASP_APP_TEST_COUNT_MT) ||
            (TestMcasp_CntTxMt[inst] < TEST_MCASP_APP_TEST_COUNT_MT)) && (timeout > 0))
    {
        ClockP_usleep(1000);
        timeout--;
    }
    if (timeout == 0)
    {
        status = SystemP_FAILURE;
    }

    /* Stop transfers */
    MCASP_stopTransferRx(mcaspHandle);
    MCASP_stopTransferTx(mcaspHandle);

    /* Withdraw transactions */
    MCASP_Transaction *transaction;
    do
    {
        transaction = MCASP_withdrawRx(mcaspHandle);
    } while (transaction != NULL);
    do
    {
        transaction = MCASP_withdrawTx(mcaspHandle);
    } while (transaction != NULL);

    /* Validate */
    CacheP_inv(TestMcasp_RxBufferMt[inst], sizeof(TestMcasp_RxBufferMt[inst]), CacheP_TYPE_ALL);
    for (j = 0U; j < TEST_MCASP_APP_MSG_COUNT ; j++)
    {
        for (k = 0U; k < TEST_MCASP_APP_MSGSIZE; k++)
        {
            if (TestMcasp_TxBufferMt[inst][j][k] != TestMcasp_RxBufferMt[inst][j][k])
            {
                status = SystemP_FAILURE;
                break;
            }
        }
    }

    if (status != SystemP_SUCCESS)
    {
        TestMcasp_ThreadResult[inst] = SystemP_FAILURE;
    }

    /* Notify main thread */
    SemaphoreP_post(&TestMcasp_MultiSem[inst]);
    TaskP_exit();
    return;
}

/**
 * \brief  Creates and manages multiple MCASP instance threads for parallel testing.
 *
 * This function initializes and opens all MCASP instances, sets up
 * callback functions, and creates individual FreeRTOS tasks for each
 * instance to perform concurrent transmit and receive operations.
 * It waits for all instance threads to complete, validates results,
 * restores the original configuration, and closes all instances.
 * Test case category: functionality test case
 */
static void Test_Mcasp_MultiThreadCreate(void *args)
{
    uint32_t i;
    uint32_t  status = SystemP_SUCCESS;
    MCASP_OpenParams savedPrms[TEST_MCASP_NUM_INSTANCES];

    /* Ensure fresh open for each MCASP instance (similar pattern as other tests) */
    for (i = 0; i < TEST_MCASP_NUM_INSTANCES; i++)
    {
        /* Save current params so later tests use original callbacks */
        savedPrms[i] = gMcaspOpenParams[i];
        if (gMcaspHandle[i] != NULL)
        {
            MCASP_close(gMcaspHandle[i]);
            gMcaspHandle[i] = NULL;
        }
        /* Override callbacks for this multi-thread test only */
        gMcaspOpenParams[i].txCallbackFxn = Test_Mcasp_TxcbMt;
        gMcaspOpenParams[i].rxCallbackFxn = Test_Mcasp_RxcbMt;
        gMcaspHandle[i] = MCASP_open(i, &gMcaspOpenParams[i]);
        TEST_ASSERT_NOT_NULL_MESSAGE(gMcaspHandle[i], "MCASP_open failed in multi_thread_create");
    }

    for (i = 0; i < TEST_MCASP_NUM_INSTANCES; i++)
    {
        /* Create binary semaphore for each instance */
        SemaphoreP_constructBinary(&TestMcasp_MultiSem[i], 0);

        /* Initialize task parameters */
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);

        taskParams.name = "MCASP instance thread";
        taskParams.stackSize = TEST_MCASP_APP_TASK_STACK_SIZE;
        taskParams.stack = TestMcasp_TaskStack[i];
        taskParams.priority = TEST_MCASP_APP_TASK_PRIORITY;
        taskParams.args = (void *)(uintptr_t)i;
        taskParams.taskMain = Test_Mcasp_InstanceThread;

        /* Create the task */
        status = TaskP_construct(&TestMcasp_TaskObj[i], &taskParams);
        if (status != SystemP_SUCCESS)
        {
            TestMcasp_ThreadResult[i] = SystemP_FAILURE;
            return;
        }
    }

    /* Wait for all threads to finish */
    for (i = 0; i < TEST_MCASP_NUM_INSTANCES; i++)
    {
        SemaphoreP_pend(&TestMcasp_MultiSem[i], SystemP_WAIT_FOREVER);
    }
    for (i = 0; i < TEST_MCASP_NUM_INSTANCES; i++)
    {
        /* Task self deletes; handle retained only for clarity */
        SemaphoreP_destruct(&TestMcasp_MultiSem[i]);
        TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,TestMcasp_ThreadResult[i],"MCASP instance failed");
    }

    /* Close all instances opened for this test */
    for (i = 0; i < TEST_MCASP_NUM_INSTANCES; i++)
    {
        if (gMcaspHandle[i] != NULL)
        {
            MCASP_close(gMcaspHandle[i]);
            gMcaspHandle[i] = NULL;
        }
        /* Restore original open params (original callbacks) */
        gMcaspOpenParams[i] = savedPrms[i];
    }

    TEST_ASSERT_TRUE(1);
}
#endif

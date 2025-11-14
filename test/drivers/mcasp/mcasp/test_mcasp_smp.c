/*
 * Copyright (C) 2025 Texas Instruments Incorporated
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
* @file  test_mcasp_smp.c
* @brief  MCASP SMP Multicore Loopback Test
**/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "unity.h"
#include "kernel/dpl/DebugP.h"
#include "kernel/dpl/SemaphoreP.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/mcasp/v1/mcasp.h>
#include <kernel/dpl/TaskP.h>

/* ========================================================================== */
/*                             Macros Defines                                 */
/* ========================================================================== */

#define TEST_MCASP_APP_MSGSIZE           (1280U)
#define TEST_MCASP_APP_MSG_COUNT         (2U)
#define TEST_MCASP_APP_COUNT             (10U)
#define TEST_MCASP_NUM_INSTANCES         (2U)
#define TEST_MCASP_TASK_STACK_SIZE       (8*1024U)
#define TEST_MCASP_TASK_PRIORITY         (3U)
#define TEST_MCASP_DMA_MODE              (1U)
#define TEST_MCASP_INTERRUPT_MODE        (2U)

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

static void TestMcasp_smpMultiInstance(void *args);
static void TestMcasp_instanceTask(void *arg);
static void TestMcasp_selectConfig(int32_t mode,void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint8_t TestMcasp_txBuffer[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE] __attribute__((aligned(256)));
static uint8_t TestMcasp_rxBuffer[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE] __attribute__((aligned(256)));
static MCASP_Transaction TestMcasp_txnTx[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT];
static MCASP_Transaction TestMcasp_txnRx[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT];
static SemaphoreP_Object TestMcasp_instDoneSem[TEST_MCASP_NUM_INSTANCES];
static int32_t TestMcasp_instResult[TEST_MCASP_NUM_INSTANCES];
static uint8_t TestMcasp_txLoopjobBuf[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSGSIZE] __attribute__((aligned(64)));
static uint8_t TestMcasp_rxLoopjobBuf[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSGSIZE] __attribute__((aligned(64)));
static TaskP_Object TestMcasp_TaskObj[TEST_MCASP_NUM_INSTANCES];
static uint8_t TestMcasp_TaskStack[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_TASK_STACK_SIZE];
static volatile uint32_t TestMcasp_CntTx[TEST_MCASP_NUM_INSTANCES] = {0};
static volatile uint32_t TestMcasp_CntRx[TEST_MCASP_NUM_INSTANCES] = {0};

/* ========================================================================== */
/*                            Function Definitions                            */
/* ========================================================================== */

/**
 * \brief  MCASP transmit callback for SMP test.
 *
 * Callback function for TX completion:
 * Increments per-instance transfer counter.
 * Resubmits transaction until target count is reached.
 * Test case category: callback support function
 *
 * \param handle      MCASP driver handle
 * \param transaction Pointer to the completed transaction
 */
void mcasp_txcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    uint32_t *cntTx = (uint32_t*)transaction->args;
    if(cntTx == NULL) 
    {
        return;
    }

    (*cntTx)++;
    
    if(*cntTx < TEST_MCASP_APP_COUNT)
    {
        (void)MCASP_submitTx(handle, transaction);
    }
}

/**
 * \brief  MCASP receive callback for SMP test.
 *
 * Callback function for RX completion:
 * Increments per-instance transfer counter.
 * Resubmits the same transaction target count is reached.
 * Test case category: callback support function
 *
 * \param handle      MCASP driver handle
 * \param transaction Pointer to the completed transaction
 */
void mcasp_rxcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    uint32_t *cntRx = (uint32_t*)transaction->args;
    if(cntRx == NULL)
    {
        return;
    }

    (*cntRx)++;

    if(*cntRx < TEST_MCASP_APP_COUNT)
    {
        (void)MCASP_submitRx(handle, transaction);
    }
}

/**
 *  \brief  Instance task for the MCASP SMP test.
 *
 *  Performs per-instance loopback:
 *  Initializes TX/RX and loopjob buffers.
 *  Prepares and submits TX/RX transactions.
 *  Starts transfers and polls for completion with timeout.
 *  Stops transfers and withdraws pending transactions.
 *  Validates RX data against TX data.
 *  Signals completion via semaphore.
 *
 *  \param arg  Instance index
 */
static void TestMcasp_instanceTask(void *arg)
{
    uint32_t inst = (uint32_t)arg;
    MCASP_Handle mcaspHandle;
    int32_t status;

    TestMcasp_CntTx[inst] = 0;
    TestMcasp_CntRx[inst] = 0;
    TestMcasp_instResult[inst] = SystemP_SUCCESS;

    mcaspHandle = MCASP_getHandle(inst);
    if(mcaspHandle != NULL)
    {
        MCASP_close(mcaspHandle);
        mcaspHandle = NULL;
    }

    for(uint32_t i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        TestMcasp_txLoopjobBuf[inst][i] = 0xA5;
        TestMcasp_rxLoopjobBuf[inst][i] = 0x00;
    }
    CacheP_wb(TestMcasp_txLoopjobBuf[inst],TEST_MCASP_APP_MSGSIZE,CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxLoopjobBuf[inst],TEST_MCASP_APP_MSGSIZE,CacheP_TYPE_ALL);

    MCASP_OpenParams *openParams = &gMcaspOpenParams[inst];
    openParams->txLoopjobBuf  = TestMcasp_txLoopjobBuf[inst];
    openParams->rxLoopjobBuf  = TestMcasp_rxLoopjobBuf[inst];

    mcaspHandle = MCASP_open(inst, openParams);
    TEST_ASSERT_NOT_NULL_MESSAGE(mcaspHandle, "MCASP_open failed in SMP multicore test");

    /* Fill buffers */
    uint32_t offset = 64U * inst;
    for(uint32_t m=0; m<TEST_MCASP_APP_MSG_COUNT; m++)
    {
        for(uint32_t b=0; b<TEST_MCASP_APP_MSGSIZE; b++)
        {
            TestMcasp_txBuffer[inst][m][b] = (uint8_t)((offset + b) & 0xFF);
            TestMcasp_rxBuffer[inst][m][b] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer[inst], sizeof(TestMcasp_txBuffer[inst]), CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer[inst], sizeof(TestMcasp_rxBuffer[inst]), CacheP_TYPE_ALL);

    /* Prepare transactions */
    for(uint32_t m=0; m<TEST_MCASP_APP_MSG_COUNT; m++)
    {
        TestMcasp_txnTx[inst][m].buf = &TestMcasp_txBuffer[inst][m][0];
        TestMcasp_txnTx[inst][m].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[inst][m].timeout = 0xFFFFFF;
        TestMcasp_txnTx[inst][m].args = (void*)&TestMcasp_CntTx[inst];
        status = MCASP_submitTx(mcaspHandle, &TestMcasp_txnTx[inst][m]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    for(uint32_t m=0; m<TEST_MCASP_APP_MSG_COUNT; m++)
    {
        TestMcasp_txnRx[inst][m].buf = &TestMcasp_rxBuffer[inst][m][0];
        TestMcasp_txnRx[inst][m].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[inst][m].timeout = 0xFFFFFF;
        TestMcasp_txnRx[inst][m].args = (void*)&TestMcasp_CntRx[inst];
        status = MCASP_submitRx(mcaspHandle, &TestMcasp_txnRx[inst][m]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    status = MCASP_startTransferRx(mcaspHandle);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(mcaspHandle);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    uint32_t timeout = 1000000U;
    while(((TestMcasp_CntTx[inst] < TEST_MCASP_APP_COUNT) || (TestMcasp_CntRx[inst] < TEST_MCASP_APP_COUNT)) && (timeout > 0U))
    {
        TaskP_yield();
        timeout--;
    }

    if(timeout == 0U)
    {
        TestMcasp_instResult[inst] = SystemP_FAILURE;
    }

    MCASP_stopTransferRx(mcaspHandle);
    MCASP_stopTransferTx(mcaspHandle);

    /* Withdraw any leftover (safety) */
    MCASP_Transaction *t;
    while((t = MCASP_withdrawRx(mcaspHandle)) != NULL)
    {
    }
    while((t = MCASP_withdrawTx(mcaspHandle)) != NULL)
    {
    }

    if (gMcaspOpenParams[inst].transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer[inst], sizeof(TestMcasp_rxBuffer[inst]), CacheP_TYPE_ALL);
    }

    /* Validate */
    if(TestMcasp_instResult[inst] == SystemP_SUCCESS)
    {
        for(uint32_t m=0; m<TEST_MCASP_APP_MSG_COUNT; m++)
        {
            for(uint32_t b=0; b<TEST_MCASP_APP_MSGSIZE; b++)
            {
                if(TestMcasp_txBuffer[inst][m][b] != TestMcasp_rxBuffer[inst][m][b])
                {
                    TestMcasp_instResult[inst] = SystemP_FAILURE;
                    break;
                }
            }
            if(TestMcasp_instResult[inst] != SystemP_SUCCESS)
            {
                break;
            }
        }
    }
    if(mcaspHandle != NULL)
    {
            MCASP_close(mcaspHandle);
            mcaspHandle = NULL;
    }
    /* Post semaphore now (was previously inside callbacks) */
    SemaphoreP_post(&TestMcasp_instDoneSem[inst]);
    TaskP_exit();
}


/**
 *  \brief  MCASP multicore multi-instance loopback test.
 *
 *  Executes a loopback across all configured MCASP instances:
 *  Closes and reopens each instance with callbacks and loopjob buffers.
 *  Creates one task per instance with core affinity.
 *  Waits for all tasks to complete.
 *  Checks per-instance results.
 *  Cleans up semaphores and task objects.
 *
 *  \param args  Unused argument.
 */
static void TestMcasp_smpMultiInstance(void *args)
{
    (void)args;

    uint32_t inst;

    /* Create per-instance semaphore and task pinned to core (inst % cores) */
    for( inst = 0; inst < TEST_MCASP_NUM_INSTANCES; inst++)
    {
        SemaphoreP_constructBinary(&TestMcasp_instDoneSem[inst], 0);
        TestMcasp_instResult[inst] = SystemP_FAILURE;

        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.priority     = TEST_MCASP_TASK_PRIORITY;
        taskParams.stack        = TestMcasp_TaskStack[inst];
        taskParams.stackSize    = TEST_MCASP_TASK_STACK_SIZE;
        taskParams.name         = (inst==0) ? "MCASP_SMP_INST0" : "MCASP_SMP_INST1";
        taskParams.args         = (void*)inst;
        taskParams.taskMain     = &TestMcasp_instanceTask;
        taskParams.coreAffinity = 1U << inst;

        int32_t status = TaskP_construct(&TestMcasp_TaskObj[inst], &taskParams);
        TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS, status, "TaskP_construct failed");
    }
    /* Wait for all instances */
    for( inst = 0; inst < TEST_MCASP_NUM_INSTANCES; inst++)
    {
        SemaphoreP_pend(&TestMcasp_instDoneSem[inst], SystemP_WAIT_FOREVER);

        SemaphoreP_destruct(&TestMcasp_instDoneSem[inst]);
        TaskP_destruct(&TestMcasp_TaskObj[inst]);
        ClockP_usleep(1000);

        TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS, TestMcasp_instResult[inst], "Instance failed");
    }
}

/**
 * \brief  Select and apply MCASP configuration for a given mode.
 *
 * Adjusts MCASP_OpenParams and underlying MCASP_Attrs fields to switch
 * between DMA and interrupt transfer modes for the specified instance.
 * Sets openParams->transferMode.
 * Updates RX/TX format registers (fmt) for mode-specific settings.
 * Updates interrupt/event control (intCtl / evtCtl) to enable either
 * DMA events or CPU interrupts.
 *
 * \param mode  TEST_MCASP_DMA_MODE or TEST_MCASP_INTERRUPT_MODE.
 * \param args  Pointer to MCASP_OpenParams of the target instance.
 */
static void TestMcasp_selectConfig(int32_t mode,void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instanceId = (uint32_t)(openParams - &gMcaspOpenParams[CONFIG_MCASP0]);/* Compute instance index from pointer arithmetic */
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instanceId].attrs;

    /* Set transfer mode */
    switch (mode)
    {
        case TEST_MCASP_DMA_MODE:
            openParams->transferMode = MCASP_TRANSFER_MODE_DMA;
            attrs->hwCfg.rx.fmt = (uint32_t) 0x181F0U;
            attrs->hwCfg.rx.intCtl = (uint32_t) 0x0U;
            attrs->hwCfg.rx.evtCtl = (uint32_t) 0x1U;

            attrs->hwCfg.tx.fmt = (uint32_t)0x181F0U;
            attrs->hwCfg.tx.intCtl = (uint32_t) 0x0U;
            attrs->hwCfg.tx.evtCtl = (uint32_t) 0x1U;
            break;
        case TEST_MCASP_INTERRUPT_MODE:
            openParams->transferMode = MCASP_TRANSFER_MODE_INTERRUPT;
            attrs->hwCfg.rx.fmt = (uint32_t) 0x181F8U;
            attrs->hwCfg.rx.intCtl = (uint32_t) 0x20U;
            attrs->hwCfg.rx.evtCtl = (uint32_t) 0x0U;

            attrs->hwCfg.tx.fmt = (uint32_t)  0x181F8U;
            attrs->hwCfg.tx.intCtl = (uint32_t) 0x20U;
            attrs->hwCfg.tx.evtCtl = (uint32_t) 0x0U;
            break;
        default:
            /* Invalid mode */
            break;
    }
}

void setUp(void)
{
}
void tearDown(void)
{
}


/**
 * \brief  Main entry point for mcasp SMP tests..
 *
 * Initializes Unity and runs the multicore MCASP loopback test in both DMA and interrupt modes.
 *
 * \param args  Unused argument.
 */
void test_mcasp_smp_main(void *args)
{
    UNITY_BEGIN();
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE,(void*)&gMcaspOpenParams[CONFIG_MCASP1]);
    RUN_TEST(TestMcasp_smpMultiInstance, 9005, args);  /* Interrupt mode */
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP1]);
    RUN_TEST(TestMcasp_smpMultiInstance, 9006, args);  /* DMA mode */
    UNITY_END();
}

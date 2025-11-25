/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \file test_mcasp_systems.c
 *
 *  \brief This file contains implementation of all module test cases
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <unity.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/mcasp/v1/mcasp.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define TEST_MCASP_MSGSIZE           (1280U)
#define TEST_MCASP_APP_MSG_COUNT     (2U)
#define TEST_MCASP_APP_COUNT         (10U)


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t TestMcasp_loopbackInstance(void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint8_t TestMcasp_txBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_MSGSIZE] __attribute__((aligned(256)));
static uint8_t TestMcasp_rxBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_MSGSIZE] __attribute__((aligned(256)));
static MCASP_Transaction TestMcasp_txnTx[TEST_MCASP_APP_MSG_COUNT];
static MCASP_Transaction TestMcasp_txnRx[TEST_MCASP_APP_MSG_COUNT];
static volatile uint32_t TestMcasp_cntRx = 0U;
static volatile uint32_t TestMcasp_cntTx = 0U;
extern uint8_t gTxLoopjobBuf0[];
extern uint8_t gRxLoopjobBuf0[];
extern MCASP_OpenParams gMcaspOpenParams[];

/* ========================================================================== */
/*                              Function Definitions                          */
/* ========================================================================== */

/**
 * \brief  MCASP transmit completion callback (system test).
 *
 * Callback function invoked when a TX transaction completes.
 * Increments the global TX completion counter.
 * Resubmits the same transaction until TEST_MCASP_APP_COUNT completions are reached
 * to simulate continuous streaming.
 *
 * \param handle      MCASP driver handle.
 * \param transaction Pointer to the completed transaction (reused on resubmit).
 */
void mcasp_txcb (MCASP_Handle handle, MCASP_Transaction *transaction)
{
    if (TestMcasp_cntTx < TEST_MCASP_APP_COUNT)
    {
        TestMcasp_cntTx++;
        (void)MCASP_submitTx(handle, transaction);
    }
}

/**
 * \brief  MCASP receive completion callback (system test).
 *
 * Callback function invoked when an RX transaction completes.
 * Increments the global RX completion counter.
 * Resubmits the same transaction until TEST_MCASP_APP_COUNT completions are reached
 * to simulate continuous streaming.
 *
 * \param handle      MCASP driver handle.
 * \param transaction Pointer to the completed transaction (reused on resubmit).
 */
void mcasp_rxcb (MCASP_Handle handle, MCASP_Transaction *transaction)
{
    if (TestMcasp_cntRx < TEST_MCASP_APP_COUNT)
    {
        TestMcasp_cntRx++;
        (void)MCASP_submitRx(handle, transaction);
    }
}

/**
 * \brief  MCASP single-instance loopback (system test).
 *
 * Performs a loopback transfer on one MCASP instance:
 * Opens the driver with callbacks and loopjob buffers.
 * Initializes TX/RX buffers and writes back cache.
 * Queues RX then TX transactions (ping-pong), starts transfers.
 * Waits until TEST_MCASP_APP_COUNT completions via callbacks.
 * Stops transfers and withdraws any pending transactions.
 * Invalidates RX cache (DMA mode) and compares TX vs RX data.
 * Closes the driver and returns pass/fail status.
 *
 * \param args  Unused (or pointer to open params per test harness).
 *
 * \return SystemP_SUCCESS on data match, SystemP_FAILURE otherwise.
 */
int32_t TestMcasp_loopbackInstance(void *args)
{
    MCASP_OpenParams *openparams = &gMcaspOpenParams[0];
    int32_t status = SystemP_SUCCESS;
    uint32_t i,j;
    uint32_t instanceId = 0;
    MCASP_Handle mcaspHandle;

    mcaspHandle = MCASP_getHandle(instanceId);
    if(mcaspHandle != NULL)
    {
        MCASP_close(mcaspHandle);
        mcaspHandle = NULL;
    }

    mcaspHandle = MCASP_open(instanceId, openparams);
    TEST_ASSERT_NOT_NULL_MESSAGE(mcaspHandle, "MCASP_open failed in system test");

    TestMcasp_cntRx = 0U;
    TestMcasp_cntTx = 0U;

    /* Fill TX/RX buffers */
    for(i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for(j=0; j<TEST_MCASP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = (uint8_t)(j & 0xFF);
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, sizeof(TestMcasp_txBuffer), CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, sizeof(TestMcasp_rxBuffer), CacheP_TYPE_ALL);

    for(i = 0; i < TEST_MCASP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i]=0xA5;
        gRxLoopjobBuf0[i]=0;
    }
    CacheP_wb(gTxLoopjobBuf0, TEST_MCASP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, TEST_MCASP_MSGSIZE, CacheP_TYPE_ALL);

    /* Queue RX then TX */
    for(i = 0;i < TEST_MCASP_APP_MSG_COUNT;i++)
    {
        TestMcasp_txnRx[i].buf = &TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFFU;
        TestMcasp_txnRx[i].args = (void*)&TestMcasp_cntRx;
        (void)MCASP_submitRx(mcaspHandle, &TestMcasp_txnRx[i]);
    }
    for(i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = &TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFFU;
        TestMcasp_txnTx[i].args = (void*)&TestMcasp_cntTx;
        (void)MCASP_submitTx(mcaspHandle, &TestMcasp_txnTx[i]);
    }

    status = MCASP_startTransferRx(mcaspHandle);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(mcaspHandle);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    uint32_t timeout = 1000000U;
    while( ((TestMcasp_cntRx < TEST_MCASP_APP_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_COUNT)) && (timeout > 0U))
    {
        TaskP_yield();
        timeout--;
    }

    if(timeout == 0U)
    {
        status = SystemP_FAILURE;
    }

    MCASP_stopTransferRx(mcaspHandle);
    MCASP_stopTransferTx(mcaspHandle);

    if(openparams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, sizeof(TestMcasp_rxBuffer), CacheP_TYPE_ALL);
    }

    /* Withdraw */
    if(status == SystemP_SUCCESS)
    {
        MCASP_Transaction *transaction;
        do
        {
            transaction = MCASP_withdrawRx(mcaspHandle);
        } while (transaction != NULL);
        do
        {
            transaction = MCASP_withdrawTx(mcaspHandle);
        } while (transaction != NULL);
    }

    /* Compare */
    if(status == SystemP_SUCCESS)
    {
        for(i=0;i<TEST_MCASP_APP_MSG_COUNT -1U;i++)
        {
            for(j=0;j<TEST_MCASP_MSGSIZE;j++)
            {
                if(TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }


    MCASP_close(mcaspHandle);
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS, status, "MCASP loopback data mismatch");
    return status;
}



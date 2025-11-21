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

/**\file test_mcasp_fault_injection.c
 *
 * \brief Test application for MCASP fault injection.
 *
 * This file contains test routines to validate file input/output functionality
 * using the MCASP driver in the MCU+ SDK.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdarg.h>
#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <unity.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/hw_include/cslr_mcasp.h>
#include <drivers/mcasp/v1/mcasp.h>

/* ========================================================================== */
/*                           Macro Defines                                    */
/* ========================================================================== */

#define TEST_MCASP_APP_MSGSIZE           (1280U)
#define TEST_MCASP_APP_MSG_COUNT         (2U)
#define TEST_MCASP_APP_TEST_COUNT        (2U)
#define TEST_MCASP_DMA_MODE              (1U)
#define TEST_MCASP_INTERRUPT_MODE        (2U)

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

static uint8_t TestMcasp_TxBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE] __attribute__((aligned(256)));
static uint8_t TestMcasp_RxBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE] __attribute__((aligned(256)));

volatile uint32_t TestMcasp_CntRx = 0;
volatile uint32_t TestMcasp_CntTx = 0;

MCASP_Transaction TestMcasp_TxnTx[TEST_MCASP_APP_MSG_COUNT] = {0};
MCASP_Transaction TestMcasp_TxnRx[TEST_MCASP_APP_MSG_COUNT] = {0};

extern uint8_t gTxLoopjobBuf0[];
extern uint8_t gRxLoopjobBuf0[];
extern MCASP_Config gMcaspConfig[];
extern MCASP_Handle gMcaspHandle[];
extern MCASP_OpenParams gMcaspOpenParams[];

/* ========================================================================== */
/*                                Typedef                                     */
/* ========================================================================== */

typedef enum {
    TEST_MCASP_FAULT_NONE = 0,
    TEST_MCASP_FAULT_XUNDRN,    /* Transmit underrun */
    TEST_MCASP_FAULT_XSYNCERR,  /* Unexpected transmit frame sync */
    TEST_MCASP_FAULT_XCKFAIL,   /* Transmit clock failure */
    TEST_MCASP_FAULT_XDMAERR,   /* Transmit DATA port error */
    TEST_MCASP_FAULT_ROVRN,     /* Receiver overrun */
    TEST_MCASP_FAULT_RSYNCERR,  /* Unexpected receive frame sync */
    TEST_MCASP_FAULT_RCKFAIL,   /* Receive clock failure */
    TEST_MCASP_FAULT_RDMAERR,   /* Receive DATA port error */
    TEST_MCASP_FAULT_XERR,   /* Generic TX error (XSTAT_XERR) */
    TEST_MCASP_FAULT_RERR,   /* Generic RX error (RSTAT_RERR) */
    TEST_MCASP_FAULT_MAX
} TestMcasp_FaultType;

volatile TestMcasp_FaultType TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
extern volatile uint8_t TestMcasp_TxXferInProgress ;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void TestMcasp_selectConfig(int mode, void *args);
static void TestMcasp_faultUnderrun(void *args);
static void TestMcasp_faultTransmitSyncErr(void *args);
static void TestMcasp_faultTransmitClkErr(void *args);
static void TestMcasp_faultTransmitDmaErr(void *args);
static void TestMcasp_faultReceiverOverrun(void *args);
static void TestMcasp_faultReceiveSyncErr(void *args);
static void TestMcasp_faultReceiveClkErr(void *args);
static void TestMcasp_faultReceiveDmaErr(void *args);
static void TestMcasp_faultReceiveGenericErr(void *args);
static void TestMcasp_faultTransmitGenericErr(void *args);

static void TestMcasp_loopbackWithFault(TestMcasp_FaultType faultType, void *args);


/* ========================================================================== */
/*                          Callback Functions                                */
/* ========================================================================== */

void mcasp_txcb(MCASP_Handle McaspHandle, MCASP_Transaction *transaction)
{
    if (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT)
    {
        TestMcasp_CntTx++;
        if (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT)
        {
            MCASP_submitTx(McaspHandle, transaction);
        }
    }
}

void mcasp_rxcb(MCASP_Handle McaspHandle, MCASP_Transaction *transaction)
{
    if (TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT)
    {
        TestMcasp_CntRx++;
        if (TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT)
        {
            MCASP_submitRx(McaspHandle, transaction);
        }
    }
}

/* ========================================================================== */
/*                            Function Definitions                                   */
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
     /* Setup function nothing to perform */
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
    /* Tear down function nothing to perform */
}

/**
* \brief Main fuction for unity framework
*
* \param None.
*
* \return None.
*/

void test_main(void *args)
{
    UNITY_BEGIN();
    RUN_TEST(TestMcasp_faultUnderrun, 9253, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_faultTransmitSyncErr, 9254, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_faultTransmitClkErr, 9255, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_faultTransmitDmaErr, 9256, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_faultReceiverOverrun, 9257, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_faultReceiveSyncErr, 9258, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_faultReceiveClkErr, 9259, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_faultReceiveDmaErr, 9260, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_faultTransmitGenericErr, 9261, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_faultReceiveGenericErr, 9262, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    UNITY_END();
}

/* Inject TX underrun (XSTAT_XUNDRN) and run loopback. */
static void TestMcasp_faultUnderrun(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_XUNDRN, args);
}

/* Inject TX sync error (XSTAT_XSYNCERR) and run loopback. */
static void TestMcasp_faultTransmitSyncErr(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_XSYNCERR, args);
}

/* Inject TX clock fail (XSTAT_XCKFAIL) and run loopback. */
static void TestMcasp_faultTransmitClkErr(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_XCKFAIL, args);
}

/* Inject TX DMA error (XSTAT_XDMAERR) and run loopback. */
static void TestMcasp_faultTransmitDmaErr(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_XDMAERR, args);
}


/* Inject RX overrun (RSTAT_ROVRN) and run loopback. */
static void TestMcasp_faultReceiverOverrun(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_ROVRN, args);
}

/* Inject RX sync error (RSTAT_RSYNCERR) and run loopback. */
static void TestMcasp_faultReceiveSyncErr(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_RSYNCERR, args);
}

/* Inject RX clock fail (RSTAT_RCKFAIL) and run loopback. */
static void TestMcasp_faultReceiveClkErr(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_RCKFAIL, args);
}

/* Inject RX DMA error (RSTAT_RDMAERR) and run loopback. */
static void TestMcasp_faultReceiveDmaErr(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_RDMAERR, args);
}

/* Inject TX generic error (XSTAT_XERR) and run loopback. */
static void TestMcasp_faultTransmitGenericErr(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_XERR, args);
}

/* Inject RX generic error (RSTAT_RERR) and run loopback. */
static void TestMcasp_faultReceiveGenericErr(void *args)
{
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_loopbackWithFault(TEST_MCASP_FAULT_RERR, args);
}

/**
 * \brief Fault injection stub to set MCASP status bits for TX/RX ISR paths.
 *
 * Test Category: Fault injection test.
 *
 * This hook is called by the MCASP driver ISR to allow tests to inject
 * specific fault bits into the local status snapshot. Based on the current
 * TestMcasp_CurrFaultType and side (TX=0, RX=1), it ORs or assigns the
 * corresponding XSTAT/RSTAT mask into xstat. The fault type is then cleared.
 *
 * \param side MCASP side selector.
 *             - 0: Transmit (TX) side, updates XSTAT bits.
 *             - 1: Receive (RX) side, updates RSTAT bits.
 * \param xstat Pointer to the ISR-local status value to modify.
 *
 * \return None.
 */
void Test_Mcasp_FaultInjectStubHandler(uint32_t side, uint32_t *xstat)
{
    if(TestMcasp_CurrFaultType == TEST_MCASP_FAULT_NONE)
    {
        return;
    }

    if (side == 0) /* TX side */
    {
        switch (TestMcasp_CurrFaultType)
        {
            case TEST_MCASP_FAULT_XUNDRN:
                *xstat = CSL_MCASP_XSTAT_XUNDRN_MASK;
                 TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
            case TEST_MCASP_FAULT_XSYNCERR:
                *xstat = CSL_MCASP_XSTAT_XSYNCERR_MASK;
                TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
            case TEST_MCASP_FAULT_XCKFAIL:
                *xstat = CSL_MCASP_XSTAT_XCKFAIL_MASK;
                TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
            case TEST_MCASP_FAULT_XDMAERR:
                *xstat = CSL_MCASP_XSTAT_XDMAERR_MASK;
                TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
             case TEST_MCASP_FAULT_XERR:
                *xstat = CSL_MCASP_XSTAT_XERR_MASK;
                TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
            default:
                break;
        }
    }
    else if (side == 1) /* RX side */
    {
        switch (TestMcasp_CurrFaultType)
        {
            case TEST_MCASP_FAULT_ROVRN:
                *xstat = CSL_MCASP_RSTAT_ROVRN_MASK;
                TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
            case TEST_MCASP_FAULT_RSYNCERR:
                *xstat = CSL_MCASP_RSTAT_RSYNCERR_MASK;
                TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
            case TEST_MCASP_FAULT_RCKFAIL:
                *xstat = CSL_MCASP_RSTAT_RCKFAIL_MASK;
                TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
            case TEST_MCASP_FAULT_RDMAERR:
                *xstat = CSL_MCASP_RSTAT_RDMAERR_MASK;
                TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
            case TEST_MCASP_FAULT_RERR:
                *xstat = CSL_MCASP_RSTAT_RERR_MASK;
                TestMcasp_CurrFaultType = TEST_MCASP_FAULT_NONE;
                break;
            default:
                break;
        }
    }
    return;
}

/**
 * \brief Execute MCASP loopback with a specific fault injected.
 *
 * Test Category: Fault injection test.
 *
 * This helper sets up buffers, opens the MCASP instance with previously
 * selected configuration, submits TX/RX transactions, injects the requested
 * fault via the stub hook, and performs a loopback transfer to validate
 * error handling and ISR paths. It stops transfer, withdraws any queued
 * buffers, and asserts data integrity at the end.
 *
 * \param faultType Fault to inject during the loopback run.

 * \param args Pointer to MCASP_OpenParams for the target instance
 *
 * \return None.
 */
static void TestMcasp_loopbackWithFault(TestMcasp_FaultType faultType, void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i=0, j=0;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instanceId = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Handle McaspHandle;

    MCASP_close(gMcaspHandle[instanceId]);
    gMcaspHandle[instanceId] = NULL;

    openParams->txLoopjobBuf = gTxLoopjobBuf0;
    openParams->rxLoopjobBuf = gRxLoopjobBuf0;
    openParams->txCallbackFxn = mcasp_txcb;
    openParams->rxCallbackFxn = mcasp_rxcb;

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

    /* Set the fault flag just before or after starting transfer */
    TestMcasp_CurrFaultType = faultType;

    status = MCASP_startTransferRx(McaspHandle);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(McaspHandle);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

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

}

/**
 * \brief Select and apply MCASP configuration for a given test mode.
 *
 * Test Category: Fault injection test.
 *
 * This function configures the MCASP driver open parameters and hardware
 * attributes for either DMA or Interrupt transfer mode. It sets RX/TX format,
 * interrupt control, and event control registers to prepare the instance for
 * the fault injection loopback tests.
 *
 * \param mode Transfer mode selector.
 *             TEST_MCASP_DMA_MODE: Configure for DMA-based transfers.
 *             TEST_MCASP_INTERRUPT_MODE: Configure for interrupt-based transfers.
 * \param args Pointer to MCASP_OpenParams for the target instance
 *
 *
 * \return None.
 */
void TestMcasp_selectConfig(int mode, void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[CONFIG_MCASP0].attrs;

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
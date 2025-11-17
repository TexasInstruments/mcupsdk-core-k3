/*
 *  Copyright (C) 2021-2024 Texas Instruments Incorporated
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
/*
 *  The application demonstrates MCSPI Master operation by sending
 *  a known data from the master and then receiving the same from slave
 *  and finally compare the results.
 *  Please connect pins as described below on AM62AX-SK EVM.
 *
 *  MCU SPI0 CS1 = J8-8   ------------->   EXP SPI0 CS0 = J3-24
 *  MCU SPI0 CLK= J8-18  ------------->   EXP SPI0 CLK= J3-23
 *  MCU SPI0 D0 = J8-6    ------------->   EXP SPI0 D0 = J3-19
 *  MCU SPI0 D1= J8-4    ------------->   EXP SPI0 D1 = J3-21
 */

 /**
 *  \file test_mcspi_slave.c
 *
 *  \brief This file contains implementation of system test cases for
 *         mcspi slave
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
#include <unity.h>
#include "system_test_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_MCSPI_MSGSIZE       (128U)
#define APP_PERF_LOOP_ITER_CNT  (10U)
#define TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, transaction) \
    do { \
        if((SystemP_SUCCESS != (transferOK)) || \
                ((MCSPI_TRANSFER_COMPLETED != transaction.status) && \
                (MCSPI_TRANSFER_STARTED != transaction.status))) \
        { \
            DebugP_assert(FALSE); /* MCSPI TX/RX failed!! */ \
        } \
    } while(0) \

#define SPI_TEST_NUM_CLK_LIST            (sizeof (gClkDividerTestListRampUp) / \
                                          sizeof (gClkDividerTestListRampUp[0U]))


typedef struct MCSPI_TestParams_s {
    MCSPI_ChConfig      mcspiChConfigParams;
    MCSPI_OpenParams    mcspiOpenParams;
    uint32_t            testcaseId;
    uint32_t            dataSize;
} MCSPI_SlaveTestParams;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static uint32_t TestMcspi_slaveTransfer(void *args);
static int32_t TestMcspi_slaveMain(uint32_t size);
static void TestMcspi_callBack(MCSPI_Handle handle, MCSPI_Transaction *trans);
static void TestMcspi_setSlaveParams(MCSPI_SlaveTestParams *testParams, uint32_t tcId);
static uint32_t TestMcspi_slaveTransferTc(void *args);
static int32_t TestMcspi_slaveTransferPerformance(void *args);
static int32_t TestMcspi_slaveTransfer_8_16_32Bit(void *args);

/* ========================================================================== */
/*                       Function Declarations                                */
/* ========================================================================== */
extern uint32_t get_master_core_id(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint32_t   gClkDividerTestListRampUp[] =
{
    1U,   2U,   3U,   4U,   5U,   6U,    7U,    8U,    9U,    10U,
    99U,  15U,  31U,  63U,  127U,  199U,  255U,  299U, 399U, 499U, 511U, 599U,
    699U, 799U, 899U, 999U, 1023U, 2047U, 3000U
};

static uint32_t   gClkDividerTestListRampDown[] =
{
    3000U, 2047U, 1023U, 999U, 899U, 799U,
    699U, 599U, 511U, 499U, 399U, 299U, 255U,
    199U, 127U, 99U, 63U, 31U, 15U, 10U, 9U,
    8U, 7U, 6U, 5U, 4U, 3U, 2U, 1U
};

uint8_t gMcspiTxBuffer[APP_MCSPI_MSGSIZE];
uint8_t gMcspiRxBuffer[APP_MCSPI_MSGSIZE];
uint32_t gMcspiMasterTxBuffer[APP_MCSPI_MSGSIZE];
uint32_t gMcspiMasterRxBuffer[APP_MCSPI_MSGSIZE];
/* Semaphore to indicate Tx/Rx completion used in callback api's */
static SemaphoreP_Object gMcspiTransferDoneSem;

/* ========================================================================== */
/*                            Function Definitions                            */
/* ========================================================================== */

int32_t TestMcspi_slaveTest1(void *args)
{
    MCSPI_SlaveTestParams   SlavetestParams;
    uint32_t test_case_id = *((int32_t *)args);
    int32_t status = SystemP_FAILURE;

    TestMcspi_setSlaveParams(&SlavetestParams, test_case_id );
    status = TestMcspi_slaveTransfer((void*)&SlavetestParams);

    return status;
}

int32_t TestMcspi_slaveTest2(void *args)
{
    MCSPI_SlaveTestParams   SlavetestParams;
    uint32_t test_case_id = *((int32_t *)args);
    int32_t status = SystemP_FAILURE;

    TestMcspi_setSlaveParams(&SlavetestParams, test_case_id );
    status = TestMcspi_slaveTransferTc((void*)&SlavetestParams);

    return status;
}

int32_t TestMcspi_slaveTest3(void *args)
{
    MCSPI_SlaveTestParams   SlavetestParams;
    uint32_t test_case_id = *((int32_t *)args);
    uint32_t          clkList;
    MCSPI_ChConfig   *chConfigParams;
    MCSPI_Config     *config;
    MCSPI_Attrs      *attrParams;
    int32_t status = SystemP_FAILURE;
    int32_t statusAll = SystemP_SUCCESS;

    TestMcspi_setSlaveParams(&SlavetestParams, test_case_id );
    chConfigParams = &(SlavetestParams.mcspiChConfigParams);
    config = &gMcspiConfig[CONFIG_MCSPI0];
    attrParams = (MCSPI_Attrs *)config->attrs;
    for (clkList = 0U; clkList < SPI_TEST_NUM_CLK_LIST; clkList++)
    {
        chConfigParams->bitRate = (attrParams->inputClkFreq / (gClkDividerTestListRampUp[clkList] + 1));
        status = TestMcspi_slaveTransferTc((void*)&SlavetestParams);

        if (status != SystemP_SUCCESS)
        {
            statusAll = SystemP_FAILURE;
            DebugP_log("[MCSPI Slave] test %d failed for clkList: %d!!\r\n", test_case_id, clkList);
        }
    }

    return statusAll;
}

int32_t TestMcspi_slaveTest4(void *args)
{
    MCSPI_SlaveTestParams   SlavetestParams;
    uint32_t test_case_id = *((int32_t *)args);
    uint32_t          clkList;
    MCSPI_ChConfig   *chConfigParams;
    MCSPI_Config     *config;
    MCSPI_Attrs      *attrParams;
    int32_t status = SystemP_FAILURE;
    int32_t statusAll = SystemP_SUCCESS;

    TestMcspi_setSlaveParams(&SlavetestParams, test_case_id );
    chConfigParams = &(SlavetestParams.mcspiChConfigParams);
    config = &gMcspiConfig[CONFIG_MCSPI0];
    attrParams = (MCSPI_Attrs *)config->attrs;
    for (clkList = 0U; clkList < SPI_TEST_NUM_CLK_LIST; clkList++)
    {
        chConfigParams->bitRate = (attrParams->inputClkFreq / (gClkDividerTestListRampDown[clkList] + 1));
        status = TestMcspi_slaveTransferTc((void*)&SlavetestParams);

        if (status != SystemP_SUCCESS)
        {
            statusAll = SystemP_FAILURE;
        }
    }

    return statusAll;
}

int32_t TestMcspi_slaveTest5(void *args)
{
    MCSPI_SlaveTestParams   SlavetestParams;
    uint32_t test_case_id = *((int32_t *)args);
    int32_t status = SystemP_FAILURE;

    TestMcspi_setSlaveParams(&SlavetestParams, test_case_id );
    status = TestMcspi_slaveTransferPerformance((void*)&SlavetestParams);

    return status;
}

int32_t TestMcspi_slaveTest6(void *args)
{
    MCSPI_SlaveTestParams   SlavetestParams;
    uint32_t test_case_id = *((int32_t *)args);
    int32_t status = SystemP_FAILURE;

    TestMcspi_setSlaveParams(&SlavetestParams, test_case_id );
    status = TestMcspi_slaveTransfer_8_16_32Bit((void*)&SlavetestParams);

    return status;
}

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

static uint32_t TestMcspi_slaveTransfer(void *args)
{
    int32_t             status = SystemP_SUCCESS, statusAll = SystemP_SUCCESS;
    uint32_t            size;

    size = APP_MCSPI_MSGSIZE/4;
    status = TestMcspi_slaveMain(size);
    if (status != SystemP_SUCCESS)
    {
        statusAll = status;
        DebugP_log("[MCSPI Slave] test failed for size: %d!!\r\n", size);
    }

    size = APP_MCSPI_MSGSIZE/2;
    status = TestMcspi_slaveMain(size);
    if (status != SystemP_SUCCESS)
    {
        statusAll = status;
        DebugP_log("[MCSPI Slave] test failed for size: %d!!\r\n", size);
    }

    size = APP_MCSPI_MSGSIZE;
    status = TestMcspi_slaveMain(size);
    if (status != SystemP_SUCCESS)
    {
        statusAll = status;
        DebugP_log("[MCSPI Slave] test failed for size: %d!!\r\n", size);
    }

   return statusAll;
}

static int32_t TestMcspi_slaveMain(uint32_t size)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint32_t masterId;

    masterId = get_master_core_id();

    /* Memfill buffers */
    for(i = 0U; i < size; i++)
    {
        gMcspiTxBuffer[i] = i + 1U;
        gMcspiRxBuffer[i] = 0U;
    }

    TestUtils_syncRemoteCore(masterId, SystemP_WAIT_FOREVER);

    /* Initiate transfer */
    spiTransaction.channel  = gConfigMcspi0ChCfg[0].chNum;
    spiTransaction.dataSize  = 8;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = size / (spiTransaction.dataSize/8);
    spiTransaction.txBuf    = (void *)gMcspiTxBuffer;
    spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
    spiTransaction.args     = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

    /* Compare data */
    for(i = 0U; i < size; i++)
    {
        if(gMcspiTxBuffer[i] != gMcspiRxBuffer[i])
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("[MCSPI Slave] Data Mismatch at offset %d\r\n", i);
            break;
        }
    }

    return status;
}

static uint32_t TestMcspi_slaveTransferTc(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    uint32_t            bufWidthShift;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_SlaveTestParams   *testParams = (MCSPI_SlaveTestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);
    uint32_t masterId;

    masterId = get_master_core_id();

    /* Memset Buffers */
    memset(&gMcspiMasterTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));
    memset(&gMcspiMasterRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    DebugP_assert(mcspiHandle != NULL);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    dataWidth = testParams->dataSize;
    bufWidthShift = MCSPI_getBufWidthShift(dataWidth);
    if (dataWidth < 9U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8_t *) &gMcspiMasterTxBuffer[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiMasterRxBuffer[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiMasterTxBuffer[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiMasterRxBuffer[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiMasterTxBuffer[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiMasterRxBuffer[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers, TX data should be same as what done in Master application */
    for (i = 0U; i < (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift))); i++)
    {
        tempTxData = 0xDEADBABE + i;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t) (tempTxData);
            *tempRxPtr8++ = 0U;
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t) (tempTxData);
            *tempRxPtr16++ = 0U;
        }
        else
        {
            *tempTxPtr32++ = (uint32_t) (tempTxData);
            *tempRxPtr32++ = 0U;
        }
    }

    /* wait for mcspi slave to be ready */
    TestUtils_syncRemoteCore(masterId, SystemP_WAIT_FOREVER);

    /* Initiate transfer */
    spiTransaction.channel   = testParams->mcspiChConfigParams.chNum;
    spiTransaction.dataSize  = testParams->dataSize;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count     = (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift)));
    spiTransaction.txBuf     = (void *)gMcspiMasterTxBuffer;
    spiTransaction.rxBuf     = (void *)gMcspiMasterRxBuffer;
    spiTransaction.args      = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Compare data */
    uint8_t *tempTxPtr, *tempRxPtr;
    /* This parameter value should be same as master */
    uint32_t defaultTxData = 0xCCU;
    /* For a default TX data test, we need to match with defaultTxData.
    From master it always sends defaultTxData */
    if(testParams->testcaseId == 8680U)
    {
        tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            if ((defaultTxData != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
            {
                status = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
       }
    }
    else if((testParams->testcaseId == 8662U) || (testParams->testcaseId == 8676U))
    {
        tempTxPtr = (uint8_t *) &gMcspiMasterTxBuffer[0U];
        tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            /* In this test case, Slave is in Transmit mode only */
            if ((0 != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
            {
                status = SystemP_FAILURE;   /* Data mismatch */
                break;
            }
        }
    }
    else
    {
        tempTxPtr = (uint8_t *) &gMcspiMasterTxBuffer[0U];
        tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            if ((*tempTxPtr++ != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
            {
                status = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
        }
    }

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    MCSPI_close(mcspiHandle);

    return status;
}

static int32_t TestMcspi_slaveTransfer_8_16_32Bit(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    int32_t             statusAll = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    uint32_t            bufWidthShift;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_SlaveTestParams   *testParams = (MCSPI_SlaveTestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);
    uint8_t *tempTxPtr, *tempRxPtr;
    uint32_t masterId;

    masterId = get_master_core_id();

    /* Memset Buffers */
    memset(&gMcspiMasterTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));
    memset(&gMcspiMasterRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    DebugP_assert(mcspiHandle != NULL);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    dataWidth = 8U;
    bufWidthShift = MCSPI_getBufWidthShift(dataWidth);
    /* Init TX buffer with known data and memset RX buffer */
    tempTxPtr8 = (uint8_t *) &gMcspiMasterTxBuffer[0U];
    tempRxPtr8 = (uint8_t *) &gMcspiMasterRxBuffer[0U];

    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers, TX data should be same as what done in Master application */
    for (i = 0U; i < (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift))); i++)
    {
        tempTxData = 0xDEADBABE + i;
        tempTxData &= (fifoBitMask);
        *tempTxPtr8++ = (uint8_t) (tempTxData);
        *tempRxPtr8++ = 0U;
    }

    /* wait for mcspi slave to be ready */
    TestUtils_syncRemoteCore(masterId, SystemP_WAIT_FOREVER);

    /* Initiate transfer */
    spiTransaction.channel   = testParams->mcspiChConfigParams.chNum;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = FALSE;
    spiTransaction.count     = (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift)));
    spiTransaction.txBuf     = (void *)gMcspiMasterTxBuffer;
    spiTransaction.rxBuf     = (void *)gMcspiMasterRxBuffer;
    spiTransaction.args      = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Compare data */
    /* This parameter value should be same as master */
    uint32_t defaultTxData = 0xCCU;
    /* For a default TX data test, we need to match with defaultTxData.
    From master it always sends defaultTxData */
    if(testParams->testcaseId == 8680U)
    {
        tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            if ((defaultTxData != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
            {
                statusAll = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
       }
    }
    else if((testParams->testcaseId == 8662U) || (testParams->testcaseId == 8676U))
    {
        tempTxPtr = (uint8_t *) &gMcspiMasterTxBuffer[0U];
        tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            /* In this test case, Slave is in Transmit mode only */
            if ((0 != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
            {
                statusAll = SystemP_FAILURE;   /* Data mismatch */
                break;
            }
        }
    }
    else
    {
        tempTxPtr = (uint8_t *) &gMcspiMasterTxBuffer[0U];
        tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            if ((*tempTxPtr++ != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
            {
                statusAll = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
        }
    }

    /* Memset Buffers */
    memset(&gMcspiMasterTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));
    memset(&gMcspiMasterRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));
    dataWidth = 16U;
    bufWidthShift = MCSPI_getBufWidthShift(dataWidth);
    /* Init TX buffer with known data and memset RX buffer */
    tempTxPtr16 = (uint16_t *) &gMcspiMasterTxBuffer[0U];
    tempRxPtr16 = (uint16_t *) &gMcspiMasterRxBuffer[0U];

    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers, TX data should be same as what done in Master application */
    for (i = 0U; i < (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift))); i++)
    {
        tempTxData = 0xDEADBABE + i;
        tempTxData &= (fifoBitMask);
        *tempTxPtr16++ = (uint16_t) (tempTxData);
        *tempRxPtr16++ = 0U;
    }

    /* Initiate transfer */
    spiTransaction.channel   = testParams->mcspiChConfigParams.chNum;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = FALSE;
    spiTransaction.count     = (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift)));
    spiTransaction.txBuf     = (void *)gMcspiMasterTxBuffer;
    spiTransaction.rxBuf     = (void *)gMcspiMasterRxBuffer;
    spiTransaction.args      = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Compare data */
    /* This parameter value should be same as master */
    /* For a default TX data test, we need to match with defaultTxData.
    From master it always sends defaultTxData */
    if(testParams->testcaseId == 8680U)
    {
        tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            if ((defaultTxData != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
            {
                statusAll = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
       }
    }
    else if((testParams->testcaseId == 8662U) || (testParams->testcaseId == 8676U))
    {
        tempTxPtr = (uint8_t *) &gMcspiMasterTxBuffer[0U];
        tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            /* In this test case, Slave is in Transmit mode only */
            if ((0 != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
            {
                statusAll = SystemP_FAILURE;   /* Data mismatch */
                break;
            }
        }
    }
    else
    {
        tempTxPtr = (uint8_t *) &gMcspiMasterTxBuffer[0U];
        tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            if ((*tempTxPtr++ != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
            {
                statusAll = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
        }
    }

    /* Memset Buffers */
    memset(&gMcspiMasterTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));
    memset(&gMcspiMasterRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));
    dataWidth = 32U;
    bufWidthShift = MCSPI_getBufWidthShift(dataWidth);
    /* Init TX buffer with known data and memset RX buffer */
    tempTxPtr32 = (uint32_t *) &gMcspiMasterTxBuffer[0U];
    tempRxPtr32 = (uint32_t *) &gMcspiMasterRxBuffer[0U];

    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers, TX data should be same as what done in Master application */
    for (i = 0U; i < (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift))); i++)
    {
        tempTxData = 0xDEADBABE + i;
        tempTxData &= (fifoBitMask);
        *tempTxPtr32++ = (uint32_t) (tempTxData);
        *tempRxPtr32++ = 0U;
    }

    /* Initiate transfer */
    spiTransaction.channel   = testParams->mcspiChConfigParams.chNum;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count     = (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift)));
    spiTransaction.txBuf     = (void *)gMcspiMasterTxBuffer;
    spiTransaction.rxBuf     = (void *)gMcspiMasterRxBuffer;
    spiTransaction.args      = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Compare data */
    tempTxPtr = (uint8_t *) &gMcspiMasterTxBuffer[0U];
    tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
    for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
    {
        if ((*tempTxPtr++ != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
        {
            statusAll = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d\r\n", i);
            break;
        }
    }

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    MCSPI_close(mcspiHandle);

    return statusAll;
}

static int32_t TestMcspi_slaveTransferPerformance(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    int32_t             statusAll = SystemP_SUCCESS;
    uint32_t            i,j, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    uint32_t            bufWidthShift;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_SlaveTestParams   *testParams = (MCSPI_SlaveTestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);
    uint32_t masterId;

    masterId = get_master_core_id();

    for(j = 0U; j < APP_PERF_LOOP_ITER_CNT; j++)
    {
        /* Memset Buffers */
        memset(&gMcspiMasterTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));
        memset(&gMcspiMasterRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(uint32_t));

        MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

        mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
        DebugP_assert(mcspiHandle != NULL);

        status = MCSPI_chConfig(
                     gMcspiHandle[CONFIG_MCSPI0],
                     mcspiChConfigParams);
        DebugP_assert(status == SystemP_SUCCESS);

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
            DebugP_assert(SystemP_SUCCESS == status);
        }

        dataWidth = testParams->dataSize;
        bufWidthShift = MCSPI_getBufWidthShift(dataWidth);
        if (dataWidth < 9U)
        {
            /* Init TX buffer with known data and memset RX buffer */
            tempTxPtr8 = (uint8_t *) &gMcspiMasterTxBuffer[0U];
            tempRxPtr8 = (uint8_t *) &gMcspiMasterRxBuffer[0U];
        }
        else if (dataWidth < 17U)
        {
            /* Init TX buffer with known data and memset RX buffer */
            tempTxPtr16 = (uint16_t *) &gMcspiMasterTxBuffer[0U];
            tempRxPtr16 = (uint16_t *) &gMcspiMasterRxBuffer[0U];
        }
        else
        {
            /* Init TX buffer with known data and memset RX buffer */
            tempTxPtr32 = (uint32_t *) &gMcspiMasterTxBuffer[0U];
            tempRxPtr32 = (uint32_t *) &gMcspiMasterRxBuffer[0U];
        }
        fifoBitMask = 0x0U;
        for (dataWidthIdx = 0U;
             dataWidthIdx < dataWidth; dataWidthIdx++)
        {
            fifoBitMask |= (1U << dataWidthIdx);
        }

        /* Memfill buffers, TX data should be same as what done in Master application */
        for (i = 0U; i < (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift))); i++)
        {
            tempTxData = 0xDEADBABE + i;
            tempTxData &= (fifoBitMask);
            if (dataWidth < 9U)
            {
                *tempTxPtr8++ = (uint8_t) (tempTxData);
                *tempRxPtr8++ = 0U;
            }
            else if (dataWidth < 17U)
            {
                *tempTxPtr16++ = (uint16_t) (tempTxData);
                *tempRxPtr16++ = 0U;
            }
            else
            {
                *tempTxPtr32++ = (uint32_t) (tempTxData);
                *tempRxPtr32++ = 0U;
            }
        }

        /* wait for mcspi slave to be ready */
        TestUtils_syncRemoteCore(masterId, SystemP_WAIT_FOREVER);

        /* Initiate transfer */
        spiTransaction.channel  = testParams->mcspiChConfigParams.chNum;
        spiTransaction.dataSize  = testParams->dataSize;
        spiTransaction.csDisable = TRUE;
        spiTransaction.count    = (APP_MCSPI_MSGSIZE  * (sizeof(uint32_t) / (1 << bufWidthShift)));
        spiTransaction.txBuf    = (void *)gMcspiMasterTxBuffer;
        spiTransaction.rxBuf    = (void *)gMcspiMasterRxBuffer;
        spiTransaction.args     = NULL;
        transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
        TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            /* Wait for transfer completion */
            SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
        }

        /* Compare data */
        uint8_t *tempTxPtr, *tempRxPtr;
        /* This parameter value should be same as master */
        uint32_t defaultTxData = 0xCCU;
        /* For a default TX data test, we need to match with defaultTxData.
        From master it always sends defaultTxData */
        if(testParams->testcaseId == 8680U)
        {
            tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
            for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
            {
                if ((defaultTxData != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
                {
                    statusAll = SystemP_FAILURE;   /* Data mismatch */
                    DebugP_log("Data Mismatch at offset %d\r\n", i);
                    break;
                }
        }
        }
        else if((testParams->testcaseId == 8662U) || (testParams->testcaseId == 8676U))
        {
            tempTxPtr = (uint8_t *) &gMcspiMasterTxBuffer[0U];
            tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
            for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
            {
                /* In this test case, Slave is in Transmit mode only */
                if ((0 != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
                {
                    statusAll = SystemP_FAILURE;   /* Data mismatch */
                    break;
                }
            }
        }
        else
        {
            tempTxPtr = (uint8_t *) &gMcspiMasterTxBuffer[0U];
            tempRxPtr = (uint8_t *) &gMcspiMasterRxBuffer[0U];
            for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
            {
                if ((*tempTxPtr++ != *tempRxPtr++) && (mcspiChConfigParams->startBitEnable == FALSE))
                {
                    statusAll = SystemP_FAILURE;   /* Data mismatch */
                    DebugP_log("Data Mismatch at offset %d\r\n", i);
                    break;
                }
            }
        }
    }
    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    MCSPI_close(mcspiHandle);

    return statusAll;
}

static void TestMcspi_callBack(MCSPI_Handle handle, MCSPI_Transaction *trans)
{
    DebugP_assertNoLog(MCSPI_TRANSFER_COMPLETED == trans->status);
    SemaphoreP_post(&gMcspiTransferDoneSem);

    return;
}

static void TestMcspi_setSlaveParams(MCSPI_SlaveTestParams *testParams, uint32_t tcId)
{
    MCSPI_Config     *config = &gMcspiConfig[CONFIG_MCSPI0];
    MCSPI_Attrs      *attrParams = (MCSPI_Attrs *)config->attrs;
    MCSPI_OpenParams *openParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig   *chConfigParams = &(testParams->mcspiChConfigParams);
    testParams->testcaseId             = 0U;

    /* Default Attribute Parameters */
    attrParams->inputClkFreq       = 50000000U;
    attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
    attrParams->intrPriority       = 4U;
    attrParams->chMode             = MCSPI_CH_MODE_SINGLE;
    attrParams->pinMode            = MCSPI_PINMODE_4PIN;
    attrParams->initDelay          = MCSPI_INITDLY_0;

    /* Default Open Parameters */
    openParams->transferMode           = MCSPI_TRANSFER_MODE_BLOCKING;
    openParams->transferTimeout        = SystemP_WAIT_FOREVER;
    openParams->transferCallbackFxn    = NULL;
    openParams->msMode                 = MCSPI_MS_MODE_SLAVE;

    /* Default Channel Config Parameters */
    chConfigParams->chNum              = MCSPI_CHANNEL_0;
    chConfigParams->frameFormat        = MCSPI_FF_POL0_PHA0;
    chConfigParams->bitRate            = 1000000;
    chConfigParams->csPolarity         = MCSPI_CS_POL_LOW;
    testParams->dataSize               = 8;
    chConfigParams->trMode             = MCSPI_TR_MODE_TX_RX;
    chConfigParams->inputSelect        = MCSPI_IS_D1;
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
        case 8651:
        attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        break;
        case 8652:
        attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize           = 16;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        break;
        case 8653:
        attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize           = 8;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        break;
        case 8654:
        attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->frameFormat    = MCSPI_FF_POL0_PHA1;
        break;
        case 8655:
        attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->frameFormat    = MCSPI_FF_POL1_PHA0;
        break;
        case 8656:
        attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->frameFormat    = MCSPI_FF_POL1_PHA1;
        break;
        case 8657:
        attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        attrParams->pinMode            = MCSPI_PINMODE_3PIN;
        break;
        case 8658:
        attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        attrParams->initDelay          = MCSPI_INITDLY_32;
        break;
        case 8659:
        attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        break;
        case 8660:
        attrParams->operMode               = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize               = 32;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->startBitEnable     = TRUE;
        chConfigParams->startBitPolarity   = MCSPI_SB_POL_HIGH;
        break;
        case 8661:
        attrParams->operMode               = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize               = 32;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->csIdleTime         = MCSPI_TCS0_1_CLK;
        break;
        case 8662:
        attrParams->operMode               = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize               = 8;
        chConfigParams->trMode             = MCSPI_TR_MODE_TX_ONLY;
        chConfigParams->dpe0               = MCSPI_DPE_ENABLE;
        testParams->testcaseId             = 8662U;
        break;
        case 8663:
        case 8664:
        attrParams->operMode               = MCSPI_OPER_MODE_POLLED;
        testParams->dataSize               = 32;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        break;
        case 8665:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 32;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        break;
        case 8666:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 15;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        break;
        case 8667:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 6;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        break;
        case 8668:
        attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        attrParams->pinMode            = MCSPI_PINMODE_3PIN;
        break;
        case 8669:
        attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        attrParams->initDelay          = MCSPI_INITDLY_4;
        break;
        case 8670:
        attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize           = 32;
        chConfigParams->trMode         = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->csPolarity     = MCSPI_CS_POL_LOW;
        break;
        case 8671:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 32;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->startBitEnable     = TRUE;
        chConfigParams->startBitPolarity   = MCSPI_SB_POL_LOW;
        break;
        case 8673:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 32;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->csIdleTime         = MCSPI_TCS0_2_CLK;
        break;
        case 8674:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 32;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->inputSelect        = MCSPI_IS_D0;
        chConfigParams->dpe0               = MCSPI_DPE_DISABLE;
        chConfigParams->dpe1               = MCSPI_DPE_DISABLE;
        break;
        case 8675:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 32;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
        openParams->transferCallbackFxn    = TestMcspi_callBack;
        break;
        case 8676:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 8;
        chConfigParams->trMode             = MCSPI_TR_MODE_TX_ONLY;
        testParams->testcaseId             = 8676U;
        chConfigParams->dpe0               = MCSPI_DPE_ENABLE;
        break;
        case 8677:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 8;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        break;
        case 8678:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 16;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
        openParams->transferCallbackFxn    = TestMcspi_callBack;
        break;
        case 8679:
        attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
        testParams->dataSize               = 8;
        chConfigParams->trMode             = MCSPI_TR_MODE_RX_ONLY;
        chConfigParams->bitRate            = 25000000;
        break;
        case 8680:
        chConfigParams->defaultTxData      = 0xCCU;
        testParams->testcaseId             = 8680U;
        break;
        case 8681:
        testParams->testcaseId             = 8681U;
        break;

    }

    return;
}

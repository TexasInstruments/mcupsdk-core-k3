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
#include <drivers/pinmux.h>

/* ========================================================================== */
/*                           Macro Defines                                    */
/* ========================================================================== */

#define TEST_MCASP_APP_MSGSIZE           (1280U)
#define TEST_MCASP_APP_MSG_COUNT         (2U)
#define TEST_MCASP_APP_TEST_COUNT        (2U)
#define TEST_MCASP_APP_TEST_COUNT_MT     (10U)
#define TEST_MCASP_NUM_INSTANCES         (2U)
#define TEST_MCASP_NUM_INSTANCES_MT      (3U)
#define TEST_MCASP_APP_TASK_STACK_SIZE   (48*1024u)
#define TEST_MCASP_APP_TASK_PRIORITY     (2U)
#define TEST_MCASP_DMA_MODE              (1U)
#define TEST_MCASP_INTERRUPT_MODE        (2U)
#define TEST_MCASP_USE_EXTERNAL_CLK      (1U)
#define TEST_MCASP_USE_INTERNAL_CLK      (0U)


/* ========================================================================== */
/*                           Typedefs & enum                                  */
/* ========================================================================== */

typedef enum
{
    TEST_MCASP_DEFAULT        = 0,
    TEST_MCASP_RIGHT_ROTATION = 1,
    TEST_MCASP_FRAME_SYNC_BIT = 2,
    TEST_MCASP_SERIAL_BITSTREAM = 3,
    TEST_MCASP_FRAME_SYNC_WIDTH = 4,
    TEST_MCASP_CLOCK_POLARITY = 5
} Test_Mcasp_ConfigId;

typedef enum
{
    TEST_MCASP_RIGHT_ROTATION_0 = 0,
    TEST_MCASP_RIGHT_ROTATION_4 = 1,
    TEST_MCASP_RIGHT_ROTATION_8 = 2,
    TEST_MCASP_RIGHT_ROTATION_12 = 3,
    TEST_MCASP_RIGHT_ROTATION_16 = 4,
    TEST_MCASP_RIGHT_ROTATION_20 = 5,
    TEST_MCASP_RIGHT_ROTATION_24 = 6,
    TEST_MCASP_RIGHT_ROTATION_28 = 7
} Test_Mcasp_RightRotation;

typedef enum
{
    TEST_MCASP_FRAME_SYNC_BIT_0 = 0,
    TEST_MCASP_FRAME_SYNC_BIT_1 = 1,
    TEST_MCASP_FRAME_SYNC_BIT_2 = 2
} Test_Mcasp_FrameSyncBit;

typedef enum
{
    TEST_MCASP_SERIAL_BITSTREAM_LSB = 0,
    TEST_MCASP_SERIAL_BITSTREAM_MSB = 1
} Test_Mcasp_SerialBitstream;

typedef enum
{
    TEST_MCASP_FRAME_SYNC_WIDTH_BIT = 0,
    TEST_MCASP_FRAME_SYNC_WIDTH_WORD = 1
} Test_Mcasp_FrameSyncWidth;

typedef enum
{
    TEST_MCASP_CLOCK_POLARITY_RISING = 0,
    TEST_MCASP_CLOCK_POLARITY_FALLING = 1
} Test_Mcasp_ClockPolarity;

typedef struct
{
    int32_t mode;
    int32_t paramType;
    int32_t paramValue;

} Test_Mcasp_Config;

Test_Mcasp_Config cfg = {
    .paramType = TEST_MCASP_DEFAULT,
    .paramValue = TEST_MCASP_DEFAULT
};

typedef struct
{
    uint32_t tisciDevice;
    uint32_t tisciClock;
    uint32_t type;
    uint32_t isConfigurable;
    uint32_t freq;
    uint32_t option;
} Mcasp_AuxClkConfig;

typedef enum {
    MCASP_CONFIG_DEFAULT = 0,
    MCASP_CONFIG_NEW = 1

} Mcasp_ConfigMode;

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

MCASP_Handle McaspHandle;

extern uint8_t gTxLoopjobBuf0[];
extern uint8_t gRxLoopjobBuf0[];
extern MCASP_Config gMcaspConfig[];
extern Mcasp_AuxClkConfig gMcaspAuxClkConfig[];

static uint8_t TestMcasp_txBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE]__attribute__((aligned(256)));
static uint8_t TestMcasp_rxBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE]__attribute__((aligned(256)));
static uint8_t TestMcasp_txBufferMt[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE]__attribute__((aligned(256)));
static uint8_t TestMcasp_rxBufferMt[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE]__attribute__((aligned(256)));

volatile uint32_t TestMcasp_cntRx = 0;
volatile uint32_t TestMcasp_cntTx = 0;
volatile uint32_t TestMcasp_cntRxMt[TEST_MCASP_NUM_INSTANCES] = {0};
volatile uint32_t TestMcasp_cntTxMt[TEST_MCASP_NUM_INSTANCES] = {0};

MCASP_Transaction TestMcasp_txnTx[TEST_MCASP_APP_MSG_COUNT] = {0};
MCASP_Transaction TestMcasp_txnRx[TEST_MCASP_APP_MSG_COUNT] = {0};
MCASP_Transaction TestMcasp_txnTxMt[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT] = {0};
MCASP_Transaction TestMcasp_txnRxMt[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_MSG_COUNT] = {0};

#ifdef ENABLE_MT_TESTS
static uint8_t TestMcasp_txTaskStack[TEST_MCASP_APP_TASK_STACK_SIZE]__attribute__((aligned(32)));
static uint8_t TestMcasp_rxTaskStack[TEST_MCASP_APP_TASK_STACK_SIZE]__attribute__((aligned(32)));
static uint8_t TestMcasp_taskStack[TEST_MCASP_NUM_INSTANCES][TEST_MCASP_APP_TASK_STACK_SIZE]__attribute__((aligned(32)));
volatile int32_t TestMcasp_threadResult[TEST_MCASP_NUM_INSTANCES] = { SystemP_SUCCESS };

static SemaphoreP_Object TestMcasp_multiSem[TEST_MCASP_NUM_INSTANCES];
static TaskP_Object TestMcasp_TaskObj[TEST_MCASP_NUM_INSTANCES];
static TaskP_Object TestMcasp_txTaskObj;
static TaskP_Object TestMcasp_rxTaskObj;
static SemaphoreP_Object TestMcasp_semTxDone;
static SemaphoreP_Object TestMcasp_semRxDone;
static SemaphoreP_Object *TestMcasp_semTxDonePtr = NULL;
static SemaphoreP_Object *TestMcasp_semRxDonePtr = NULL;
#endif

/* ========================================================================== */
/*                  Function Declarations                                     */
/* ========================================================================== */

static void TestMcasp_loopbackTransfer(void* args);
static void TestMcasp_dmaIcntsNegative(void *args);
static void TestMcasp_negativeNullBuffer(void *args);
static void TestMcasp_negativeBufferWithdraw(void *args);
static void TestMcasp_negativeMultipleOpen(void *args);
static void TestMcasp_selectConfig(int32_t mode, Test_Mcasp_Config *cfg, void *openParams);
static void TestMcasp_loopbackTxncount(void *args);
static void TestMcasp_restartAfterStop(void *args);
static void TestMcasp_loopjobRecovery(void *args);
static void TestMcasp_multiInstanceLoopback(void *args);
static void TestMcasp_selectClockSource(uint32_t instance, int useExternal);
static void TestMcasp_configTxRightRotate(void *args);
static void TestMcasp_validateFrameSyncBitDelay(void *args);
static void TestMcasp_configFrameSyncWidth(void *args);
static void TestMcasp_configSerialBitstream(void *args);
static void TestMcasp_configClockPolarity(void *args);
static void TestMcasp_nullLoopjob(void *args);
void TestMcasp_callbackNull(void *args);
#ifdef SOC_AM62AX
static void TestMcasp_externalLoopback(void *args);
#endif
static int32_t TestMcasp_loopbackTxRightRotate(void *args);
static int32_t TestMcasp_validateConfigLoopback(void *args);
static void TestMcasp_allSerializerLoopback(void *args);
static void TestMcasp_DynamicCoverage(void *args);
static void TestMcasp_dmaInitDoneZeroRxMismatch(void *args);
static void TestMcasp_dmaInitDoneZeroRxWaterLevelMultipleFail(void *args);
static void TestMcasp_dmaFifoWaterLevelMultipleInitDoneZero(void *args);
static void TestMcasp_dmaInitDoneZeroFifoDisabledLoopjobMismatch(void *args);
static void TestMcasp_dmaInitDoneOneLoopjobAndWaterLevelNegative(void *args);
static void TestMcasp_dmaChannelReset(void *args);
static int32_t TestMcasp_compareInstance0(uint8_t *tx, uint8_t *rx, uint32_t msgSize);
static int32_t TestMcasp_compareInstance1(uint8_t *tx, uint8_t *rx, uint32_t msgSize);
static int32_t TestMcasp_compareInstance2(uint8_t *tx, uint8_t *rx, uint32_t msgSize);
static void TestMcasp_withdrawQueuedBuff(void *args);
static void TestMcasp_fifoDisable(void *args);
static void TestMcasp_multiInstanceConfigTest(void *args);
#if ((defined(C75_CORE) && !defined(SOC_AM62DX)) || defined(SOC_AM62AX))
static void TestMcasp_interruptNullLoopjob(void *args);
#endif
static void TestMcasp_loopbackNonInterleavedToInterleaved(void *args);
static void TestMcasp_loopbackInterleavedToNonInterleaved(void *args);
static void TestMcasp_loopbackSemiInterleaved1ToSemiInterleaved2(void *args);
static void TestMcasp_loopbackSemiInterleaved2ToSemiInterleaved1(void *args);
int32_t Drivers_mcaspAuxClkCfg(void);
void mcasp_txcb(MCASP_Handle handle, MCASP_Transaction *transaction);
void mcasp_rxcb(MCASP_Handle handle, MCASP_Transaction *transaction);
#ifdef ENABLE_MT_TESTS
static void TestMcasp_multiThreadCreate(void *args);
static void TestMcasp_txcbMt(MCASP_Handle handle, MCASP_Transaction *transaction);
static void TestMcasp_rxcbMt(MCASP_Handle handle, MCASP_Transaction *transaction);
static void TestMcasp_loopbackTransferMultithread(void *args);
static void TestMcasp_txTask(void *args);
static void TestMcasp_rxTask(void *args);
static void TestMcasp_instanceThread(void *args);
#endif
static void TestMcasp_invalidBufferFormat(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();
    #ifdef ENABLE_MT_TESTS
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP1]);
    RUN_TEST(TestMcasp_multiThreadCreate, 8451,NULL);
    #if !defined(C75_CORE)
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP1]);
    RUN_TEST(TestMcasp_multiThreadCreate, 8452,NULL);
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP1]);
    #endif
    #endif
    #if ((defined(C75_CORE) && !defined(SOC_AM62DX)) || defined(SOC_AM62AX)) /* Added macro guard due to hanging of interrupt case in AM62DX c75 core*/
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_loopbackTransfer, 8343, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    #endif
    RUN_TEST(TestMcasp_loopbackTransfer, 8344, (void*)&gMcaspOpenParams[CONFIG_MCASP1]);
    RUN_TEST(TestMcasp_loopbackTransfer, 8345, (void*)&gMcaspOpenParams[CONFIG_MCASP2]);
    #ifdef ENABLE_MT_TESTS
    RUN_TEST(TestMcasp_loopbackTransferMultithread, 8346, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    #if !defined(C75_CORE)
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_loopbackTransferMultithread, 9268, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    #endif
    #endif
    RUN_TEST(TestMcasp_negativeMultipleOpen, 8347, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_negativeBufferWithdraw, 8348, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_negativeNullBuffer, 8349, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_dmaIcntsNegative, 8350, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_loopbackTxncount, 8453, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_loopjobRecovery, 8729, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_restartAfterStop, 8730, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_configTxRightRotate, 8731, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_validateFrameSyncBitDelay, 8732, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_configFrameSyncWidth, 8733, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_configSerialBitstream, 8734, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_configClockPolarity, 8735, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_nullLoopjob, 8736, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    #ifdef SOC_AM62AX
    RUN_TEST(TestMcasp_externalLoopback, 8737, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    #endif
    /* RUN_TEST(TestMcasp_callbackNull, 8738, (void*)&gMcaspOpenParams[CONFIG_MCASP0]); */ /* raised a bug for this hanging issue */
    TestMcasp_selectClockSource(CONFIG_MCASP0, TEST_MCASP_USE_EXTERNAL_CLK);
    TestMcasp_selectClockSource(CONFIG_MCASP1, TEST_MCASP_USE_EXTERNAL_CLK);
    RUN_TEST(TestMcasp_multiInstanceLoopback, 8739, NULL);
    TestMcasp_selectClockSource(CONFIG_MCASP0, TEST_MCASP_USE_INTERNAL_CLK);
    RUN_TEST(TestMcasp_allSerializerLoopback, 9075, (void*)&gMcaspOpenParams[CONFIG_MCASP2]);
    RUN_TEST(TestMcasp_DynamicCoverage, 9076, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_dmaInitDoneOneLoopjobAndWaterLevelNegative, 9263, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_dmaInitDoneZeroFifoDisabledLoopjobMismatch, 9264, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_dmaFifoWaterLevelMultipleInitDoneZero, 9265, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_dmaInitDoneZeroRxWaterLevelMultipleFail, 9266, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_dmaInitDoneZeroRxMismatch, 9267, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_withdrawQueuedBuff, 9077, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_fifoDisable, 9078, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    #if ((defined(C75_CORE) && !defined(SOC_AM62DX)) || defined(SOC_AM62AX)) /* Added macro guard due to hanging of interrupt case in AM62DX c75 core*/
    TestMcasp_selectConfig(TEST_MCASP_INTERRUPT_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_interruptNullLoopjob, 9079, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE,&cfg,(void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    #endif
    RUN_TEST(TestMcasp_multiInstanceConfigTest, 9080, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_loopbackNonInterleavedToInterleaved, 9081, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_loopbackInterleavedToNonInterleaved, 9082, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_loopbackSemiInterleaved1ToSemiInterleaved2, 9083, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_loopbackSemiInterleaved2ToSemiInterleaved1, 9084, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_dmaChannelReset, 9298, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(TestMcasp_invalidBufferFormat, 9086, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
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
static void TestMcasp_loopbackTransfer(void *args)
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

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;
    /* Memfill buffers */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = j % 256;
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }

    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i] = 0xa5;
        gRxLoopjobBuf0[i] = 0;
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*) &TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(McaspHandle,  &TestMcasp_txnRx[i]);
    }

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*) &TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(McaspHandle, &TestMcasp_txnTx[i]);
    }


    status = MCASP_startTransferRx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    while ((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT ) ||
           (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT ))
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
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    if(SystemP_SUCCESS == status)
    {
        /* Compare data */
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
            {
                if(TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
                {
                    status = SystemP_FAILURE;   /* Data mismatch */
                }
            }
        }
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    MCASP_close(McaspHandle);
    McaspHandle = NULL;

    /* Final Unity assert */
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP loopback transfer data mismatch");
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
static void TestMcasp_loopbackTransferMultithread(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i, j, retry;
    uint32_t found = 0;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Transaction *transaction;

    /* Reset counters */
    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    openParams->txLoopjobBuf = gTxLoopjobBuf0;
    openParams->rxLoopjobBuf = gRxLoopjobBuf0;
    openParams->txCallbackFxn = mcasp_txcb;
    openParams->rxCallbackFxn = mcasp_rxcb;

    /* Close if already open and reopen */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    McaspHandle = MCASP_open(CONFIG_MCASP0, openParams);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = j % 256;
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i] = 0xa5;
        gRxLoopjobBuf0[i] = 0;
    }
    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    /* Construct semaphores */
    SemaphoreP_constructBinary(&TestMcasp_semTxDone, 0);
    SemaphoreP_constructBinary(&TestMcasp_semRxDone, 0);
    TestMcasp_semTxDonePtr = &TestMcasp_semTxDone;
    TestMcasp_semRxDonePtr = &TestMcasp_semRxDone;

    /* Create RX task first so that RX starts before TX */
    TaskP_Params taskPrms;
    TaskP_Params_init(&taskPrms);
    taskPrms.name = "MCASP RX Task";
    taskPrms.stackSize = TEST_MCASP_APP_TASK_STACK_SIZE;
    taskPrms.stack = TestMcasp_rxTaskStack;
    taskPrms.priority = TEST_MCASP_APP_TASK_PRIORITY;
    taskPrms.args = openParams;
    taskPrms.taskMain = TestMcasp_rxTask;
    status = TaskP_construct(&TestMcasp_rxTaskObj, &taskPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskPrms);
    taskPrms.name = "MCASP TX Task";
    taskPrms.stackSize = TEST_MCASP_APP_TASK_STACK_SIZE;
    taskPrms.stack = TestMcasp_txTaskStack;
    taskPrms.priority = TEST_MCASP_APP_TASK_PRIORITY;
    taskPrms.args = openParams;
    taskPrms.taskMain = TestMcasp_txTask;
    status = TaskP_construct(&TestMcasp_txTaskObj, &taskPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for both tasks to signal completion */
    (void)SemaphoreP_pend(&TestMcasp_semRxDone, SystemP_WAIT_FOREVER);
    (void)SemaphoreP_pend(&TestMcasp_semTxDone, SystemP_WAIT_FOREVER);

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
    if (gMcaspOpenParams[CONFIG_MCASP0].transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }
    if(SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
            {
                if(TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    /* Cleanup */
    TaskP_destruct(&TestMcasp_txTaskObj);
    TaskP_destruct(&TestMcasp_rxTaskObj);
    SemaphoreP_destruct(&TestMcasp_semTxDone);
    SemaphoreP_destruct(&TestMcasp_semRxDone);
    TestMcasp_semTxDonePtr = NULL;
    TestMcasp_semRxDonePtr = NULL;
    MCASP_close(McaspHandle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP multithread loopback data mismatch");
    return;
}

/**
 * \brief  MCASP transmit task for multithreaded loopback test.
 *
 * This task handles the transmit side of the MCASP multithreaded test.
 * It submits transmit transactions and waits for completion via semaphore.
 * Test case category: task support function
 */
static void TestMcasp_txTask(void *args)
{
    uint32_t i;
    /* Prepare TX transactions */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*) &TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(McaspHandle, &TestMcasp_txnTx[i]);
    }
    /* Start TX after RX started (assumed) */
    int32_t status = MCASP_startTransferTx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    /* Task waits until semaphore is posted by callback, then exits */
    (void)SemaphoreP_pend(&TestMcasp_semTxDone, SystemP_WAIT_FOREVER);
    SemaphoreP_post(&TestMcasp_semTxDone); /* Allow main test to also pend */
    TaskP_exit();
}

/**
 * \brief  MCASP receive task for multithreaded loopback test.
 *
 * This task handles the receive side of the MCASP multithreaded test.
 * It submits receive transactions and waits for completion via semaphore.
 * Test case category: task support function
 */
static void TestMcasp_rxTask(void *args)
{
    uint32_t i;
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*) &TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(McaspHandle,  &TestMcasp_txnRx[i]);
    }
    int32_t status = MCASP_startTransferRx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    (void)SemaphoreP_pend(&TestMcasp_semRxDone, SystemP_WAIT_FOREVER);
    SemaphoreP_post(&TestMcasp_semRxDone); /* Allow main test to also pend */
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
    if (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT)
    {
        TestMcasp_cntTx++;
        if (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT)
        {
            MCASP_submitTx(McaspHandle, transaction);
        }
        #ifdef ENABLE_MT_TESTS
        else
        {
            /* Final completion */
            if(TestMcasp_semTxDonePtr != NULL)
            {
                SemaphoreP_post(TestMcasp_semTxDonePtr);
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
    if (TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT)
    {
        TestMcasp_cntRx++;
        if (TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT)
        {
            MCASP_submitRx(McaspHandle, transaction);
        }
        #ifdef ENABLE_MT_TESTS
        else
        {
            if(TestMcasp_semRxDonePtr != NULL)
            {
                SemaphoreP_post(TestMcasp_semRxDonePtr);
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
static void TestMcasp_dmaIcntsNegative(void *args)
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
void TestMcasp_selectConfig(int32_t mode, Test_Mcasp_Config *cfg, void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    if (openParams == NULL)
    {
        return;
    }

    /* Derive instance from pointer arithmetic */
    uint32_t instanceId = (uint32_t)(openParams - &gMcaspOpenParams[CONFIG_MCASP0]);
    if (instanceId >= gMcaspConfigNum)
    {
        return;
    }

    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instanceId].attrs;
    if (attrs == NULL)
    {
        return;
    }

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

    if (cfg->paramType == TEST_MCASP_RIGHT_ROTATION) /* Transmit Right-rotation Value */
    {
        switch(cfg->paramValue)
        {
            case TEST_MCASP_RIGHT_ROTATION_0: /* Right-rotation by 0 */
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.rx.fmt & ~0xF) | (((attrs->hwCfg.tx.fmt & 0xF) + (0 & 0xF)) & 0xF);
                break;
            case TEST_MCASP_RIGHT_ROTATION_4: /* Right-rotation by 4 */
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.tx.fmt & ~0xF) | (((attrs->hwCfg.tx.fmt & 0xF) + (1 & 0xF)) & 0xF);
                break;
            case TEST_MCASP_RIGHT_ROTATION_8: /* Right-rotation by 8 */
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.rx.fmt & ~0xF) | (((attrs->hwCfg.tx.fmt & 0xF) + (2 & 0xF)) & 0xF);
                break;
            case TEST_MCASP_RIGHT_ROTATION_12: /* Right-rotation by 12 */
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.tx.fmt & ~0xF) | (((attrs->hwCfg.tx.fmt & 0xF) + (3 & 0xF)) & 0xF);
                break;
            case TEST_MCASP_RIGHT_ROTATION_16: /* Right-rotation by 16 */
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.tx.fmt & ~0xF) | (((attrs->hwCfg.tx.fmt & 0xF) + (4 & 0xF)) & 0xF);
                break;
            case TEST_MCASP_RIGHT_ROTATION_20: /* Right-rotation by 20 */
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.tx.fmt & ~0xF) | (((attrs->hwCfg.tx.fmt & 0xF) + (5 & 0xF)) & 0xF);
                break;
            case TEST_MCASP_RIGHT_ROTATION_24: /* Right-rotation by 24 */
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.tx.fmt & ~0xF) | (((attrs->hwCfg.tx.fmt & 0xF) + (6 & 0xF)) & 0xF);
                break;
            case TEST_MCASP_RIGHT_ROTATION_28: /* Right-rotation by 28 */
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.tx.fmt & ~0xF) | (((attrs->hwCfg.tx.fmt & 0xF) + (7 & 0xF)) & 0xF);
                break;
            default:
                break;
        }
    }
    else if (cfg->paramType == TEST_MCASP_FRAME_SYNC_BIT) /* Frame Sync Bit */
    {
        switch(cfg->paramValue)
        {
            case TEST_MCASP_FRAME_SYNC_BIT_0:
                attrs->hwCfg.rx.fmt = (attrs->hwCfg.rx.fmt & ~(0x3U << 16)) | (0U << 16);
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.tx.fmt & ~(0x3U << 16)) | (0U << 16);
                break;
            case TEST_MCASP_FRAME_SYNC_BIT_1:
                attrs->hwCfg.rx.fmt = (attrs->hwCfg.rx.fmt & ~(0x3U << 16)) | (1U << 16);
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.tx.fmt & ~(0x3U << 16)) | (1U << 16);
                break;
            case TEST_MCASP_FRAME_SYNC_BIT_2:
                attrs->hwCfg.rx.fmt = (attrs->hwCfg.rx.fmt & ~(0x3U << 16)) | (2U << 16);
                attrs->hwCfg.tx.fmt = (attrs->hwCfg.tx.fmt & ~(0x3U << 16)) | (2U << 16);
                break;
            default:
                break;
        }
    }
    else if (cfg->paramType == TEST_MCASP_SERIAL_BITSTREAM) /* Transmit Serial Bitstream Order */
    {
        switch(cfg->paramValue)
        {
            case TEST_MCASP_SERIAL_BITSTREAM_LSB: /* LSB */
                attrs->hwCfg.rx.fmt &= ~(1U << 15);
                attrs->hwCfg.tx.fmt &= ~(1U << 15);
                break;
            case TEST_MCASP_SERIAL_BITSTREAM_MSB: /* MSB */
                attrs->hwCfg.rx.fmt |= (1U << 15);
                attrs->hwCfg.tx.fmt |= (1U << 15);
                break;
            default:
                break;
        }

    }
    else if (cfg->paramType == TEST_MCASP_FRAME_SYNC_WIDTH) /* frame sync width */
    {

        switch (cfg->paramValue)
        {
            case TEST_MCASP_FRAME_SYNC_WIDTH_BIT:
                attrs->hwCfg.rx.frSyncCtl &= ~(1U << 4);
                attrs->hwCfg.tx.frSyncCtl &= ~(1U << 4);
                break;
            case TEST_MCASP_FRAME_SYNC_WIDTH_WORD:
                attrs->hwCfg.rx.frSyncCtl |= (1U << 4);
                attrs->hwCfg.tx.frSyncCtl |= (1U << 4);
                break;
            default:
                /* No change */
                break;
        }
    }
    else if (cfg->paramType == TEST_MCASP_CLOCK_POLARITY)
    {
        switch (cfg->paramValue)
        {
            case TEST_MCASP_CLOCK_POLARITY_RISING: /* Polarity 0: clear bit 0 */
                attrs->hwCfg.rx.frSyncCtl &= ~(1U << 0);
                attrs->hwCfg.tx.frSyncCtl &= ~(1U << 0);
                break;
            case TEST_MCASP_CLOCK_POLARITY_FALLING: /* Polarity 1: set bit 0 */
                attrs->hwCfg.rx.frSyncCtl |= (1U << 0);
                attrs->hwCfg.tx.frSyncCtl |= (1U << 0);
                break;
            default:
                /* No change */
                break;
        }
    }
    else
    {
        /* nothing to do */
    }
}

/**
 * \brief  Test MCASP driver with NULL buffer pointers.
 *
 * This test ensures the driver handles NULL buffer pointers gracefully
 * and does not perform unintended operations.
 * Test case category: negative test case
 */
static void TestMcasp_negativeNullBuffer(void *args)
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
            TestMcasp_txBuffer[i][j] = 0xA5;
            TestMcasp_rxBuffer[i][j] = 0x00;
        }
    }

    /* Intentionally submit NULL transaction pointers */
    status = MCASP_submitTx(handle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = MCASP_submitRx(handle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Start transfers (should not move any data) */
    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

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
static void TestMcasp_negativeBufferWithdraw(void *args)
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
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
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
static void TestMcasp_negativeMultipleOpen(void *args)
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
static void TestMcasp_loopbackTxncount(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status = SystemP_SUCCESS;
    uint32_t i,j;
    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;
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
            TestMcasp_txBuffer[i][j] = (uint8_t)(j & 0xFF);
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

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

    TestMcasp_cntRx = 0; TestMcasp_cntTx = 0;

    /* Queue RX then TX transactions sized to loopjob count */
    for(i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = rxLjCnt; /* match configured txn count */
        TestMcasp_txnRx[i].timeout = 0xFFFFFFU;
        status = MCASP_submitRx(h, &TestMcasp_txnRx[i]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
    for(i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = txLjCnt; /* match configured txn count */
        TestMcasp_txnTx[i].timeout = 0xFFFFFFU;
        status = MCASP_submitTx(h, &TestMcasp_txnTx[i]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    status = MCASP_startTransferRx(h); TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(h); TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    while ((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for completion */
    }

    MCASP_stopTransferRx(h);
    MCASP_stopTransferTx(h);

    if(openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
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
                if(TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    MCASP_close(h);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "TxnCount loopback data mismatch");
}

/**
 * \brief  MCASP transmit callback used in multi-instance multithreaded tests.
 *
 * Re-submits transaction until the per-instance target transfer count is reached.
 * Test case category: callback support function
 */
void TestMcasp_txcbMt(MCASP_Handle handle, MCASP_Transaction *transaction)
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
void TestMcasp_rxcbMt(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    uint32_t *testCntRx = (uint32_t *)transaction->args;
    *testCntRx = *testCntRx + 1; /* increment every time */

    if (*testCntRx < TEST_MCASP_APP_TEST_COUNT_MT)
    {
        MCASP_submitRx(handle, transaction);
    }
}

#ifdef ENABLE_MT_TESTS
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
static void TestMcasp_instanceThread(void *args)
{
    uint32_t inst = (uint32_t)(uintptr_t)args;
    int32_t status = SystemP_SUCCESS;
    uint32_t j, k;
    MCASP_Handle mcaspHandle;

    /* Reset per-instance counters explicitly */
    TestMcasp_cntRxMt[inst] = 0;
    TestMcasp_cntTxMt[inst] = 0;

    /*  Initialize buffer values with a unique offset for each MCASP instance, */
    uint32_t bufStartOffset = 64 * inst;
    for (j = 0U; j < TEST_MCASP_APP_MSG_COUNT; j++)
    {
        for (k = 0U; k < TEST_MCASP_APP_MSGSIZE; k++)
        {
            TestMcasp_txBufferMt[inst][j][k] = (bufStartOffset + k) % 256;
            TestMcasp_rxBufferMt[inst][j][k] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBufferMt[inst], sizeof(TestMcasp_txBufferMt[inst]), CacheP_TYPE_ALLD);
    CacheP_wb(TestMcasp_rxBufferMt[inst], sizeof(TestMcasp_rxBufferMt[inst]), CacheP_TYPE_ALLD);

    mcaspHandle = MCASP_getHandle(inst);

    /* Submit TX */
    for (j = 0U; j < TEST_MCASP_APP_MSG_COUNT; j++)
    {
        TestMcasp_txnTxMt[inst][j].buf = (void*)&TestMcasp_txBufferMt[inst][j][0];
        TestMcasp_txnTxMt[inst][j].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTxMt[inst][j].timeout = 0xFFFFFF;
        TestMcasp_txnTxMt[inst][j].args = (void*)&TestMcasp_cntTxMt[inst];
        MCASP_submitTx(mcaspHandle, &TestMcasp_txnTxMt[inst][j]);
    }

    /* Submit RX */
    for (j = 0U; j < TEST_MCASP_APP_MSG_COUNT; j++)
    {
        TestMcasp_txnRxMt[inst][j].buf = (void*)&TestMcasp_rxBufferMt[inst][j][0];
        TestMcasp_txnRxMt[inst][j].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRxMt[inst][j].timeout = 0xFFFFFF;
        TestMcasp_txnRxMt[inst][j].args = (void*)&TestMcasp_cntRxMt[inst];
        MCASP_submitRx(mcaspHandle, &TestMcasp_txnRxMt[inst][j]);
    }

    /* Start transfers */
    status = MCASP_startTransferRx(mcaspHandle);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(mcaspHandle);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    uint32_t timeout = 10000U;
    while (((TestMcasp_cntRxMt[inst] < TEST_MCASP_APP_TEST_COUNT_MT) ||
            (TestMcasp_cntTxMt[inst] < TEST_MCASP_APP_TEST_COUNT_MT)) && (timeout > 0))
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
    if (gMcaspOpenParams[inst].transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBufferMt[inst], sizeof(TestMcasp_rxBufferMt[inst]), CacheP_TYPE_ALL);
    }
    for (j = 0U; j < TEST_MCASP_APP_MSG_COUNT ; j++)
    {
        for (k = 0U; k < TEST_MCASP_APP_MSGSIZE; k++)
        {
            if (TestMcasp_txBufferMt[inst][j][k] != TestMcasp_rxBufferMt[inst][j][k])
            {
                status = SystemP_FAILURE;
                break;
            }
        }
    }

    if (status != SystemP_SUCCESS)
    {
        TestMcasp_threadResult[inst] = SystemP_FAILURE;
    }

    /* Notify main thread */
    SemaphoreP_post(&TestMcasp_multiSem[inst]);
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
static void TestMcasp_multiThreadCreate(void *args)
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
        gMcaspOpenParams[i].txCallbackFxn = TestMcasp_txcbMt;
        gMcaspOpenParams[i].rxCallbackFxn = TestMcasp_rxcbMt;
        gMcaspHandle[i] = MCASP_open(i, &gMcaspOpenParams[i]);
        TEST_ASSERT_NOT_NULL_MESSAGE(gMcaspHandle[i], "MCASP_open failed in multi_thread_create");
    }

    for (i = 0; i < TEST_MCASP_NUM_INSTANCES; i++)
    {
        /* Create binary semaphore for each instance */
        SemaphoreP_constructBinary(&TestMcasp_multiSem[i], 0);

        /* Initialize task parameters */
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);

        taskParams.name = "MCASP instance thread";
        taskParams.stackSize = TEST_MCASP_APP_TASK_STACK_SIZE;
        taskParams.stack = TestMcasp_taskStack[i];
        taskParams.priority = TEST_MCASP_APP_TASK_PRIORITY;
        taskParams.args = (void *)(uintptr_t)i;
        taskParams.taskMain = TestMcasp_instanceThread;

        /* Create the task */
        status = TaskP_construct(&TestMcasp_TaskObj[i], &taskParams);
        if (status != SystemP_SUCCESS)
        {
            TestMcasp_threadResult[i] = SystemP_FAILURE;
            return;
        }
    }

    /* Wait for all threads to finish */
    for (i = 0; i < TEST_MCASP_NUM_INSTANCES; i++)
    {
        SemaphoreP_pend(&TestMcasp_multiSem[i], SystemP_WAIT_FOREVER);
    }
    for (i = 0; i < TEST_MCASP_NUM_INSTANCES; i++)
    {
        /* Task self deletes; handle retained only for clarity */
        SemaphoreP_destruct(&TestMcasp_multiSem[i]);
        TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,TestMcasp_threadResult[i],"MCASP instance failed");
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

/**
 * \brief  Test MCASP restart after stopTransfer.
 *
 * This test starts a transfer in DMA mode, stops it, then restarts without driver close and verifies correct operation.
 * Test case category: functionality test case
 */
static void TestMcasp_restartAfterStop(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i, j = 0;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instanceId = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Handle handle;
    MCASP_close(gMcaspHandle[instanceId]);
    gMcaspHandle[instanceId] = NULL;

    /* Open MCASP instance */
    handle = MCASP_open(instanceId, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    /* First transfer */
    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = (uint8_t)(j % 256);
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFFU;
        MCASP_submitRx(handle, &TestMcasp_txnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFFU;
        MCASP_submitTx(handle, &TestMcasp_txnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    while ((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /*wait for completion*/
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    /* Second transfer (restart) */
    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    /* Change pattern for second transfer */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = (uint8_t)((j + 0x55) & 0xFF);
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFFU;
        MCASP_submitRx(handle, &TestMcasp_txnRx[i]);
    }

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFFU;
        MCASP_submitTx(handle, &TestMcasp_txnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    while ((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /*wait for completion*/
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            if (TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
            {
                status = SystemP_FAILURE;
            }
        }
    }
    MCASP_close(handle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP restart after stopTransfer data mismatch");
}

/**
 * \brief  Test MCASP loopjob recovery.
 *
 * This test verifies that the MCASP driver can switch from loopjob-only operation
 * to normal data transfer when real buffers are submitted after transfer start.
 * It starts transfers with only loopjob buffers, checks that no real data is moved,
 * then submits real buffers and checks for correct data transfer.
 */
static void TestMcasp_loopjobRecovery(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, j;
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle h = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(h);

    /* Fill TX with pattern, RX with zero */
    for (i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (j = 0; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = (uint8_t)(j & 0xFF);
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    /* Set loopjob buffers (already set in openParams typically) */
    for (i = 0; i < 256; i++)
    {
        gTxLoopjobBuf0[i] = 0xA5;
        gRxLoopjobBuf0[i] = 0;
    }
    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    /* Start transfers WITHOUT submitting any real buffer (only loopjob active) */
    status = MCASP_startTransferRx(h);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(h);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait briefly to ensure loopjob is running */
    ClockP_usleep(100000);

    /* No real data should be transferred yet */
    TEST_ASSERT_EQUAL_UINT32(0, TestMcasp_cntRx);
    TEST_ASSERT_EQUAL_UINT32(0, TestMcasp_cntTx);

    /* Now submit multiple real RX and TX buffers */
    for (i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFFU;
        MCASP_submitRx(h, &TestMcasp_txnRx[i]);
    }
    for (i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFFU;
        MCASP_submitTx(h, &TestMcasp_txnTx[i]);
    }

    /* Wait for completion of real data transfer */
    while ((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) ||
           (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for completion */
    }

    /* Withdraw any remaining buffers */
    MCASP_Transaction *transaction;
    do
    {
        transaction = MCASP_withdrawRx(h);
    } while (transaction != NULL);
    do
    {
        transaction = MCASP_withdrawTx(h);
    } while (transaction != NULL);


    MCASP_stopTransferRx(h);
    MCASP_stopTransferTx(h);

    if(openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    /* Compare data */
    if(status == SystemP_SUCCESS)
    {
        for(i = 0; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for(j = 0; j < TEST_MCASP_APP_MSGSIZE; j++)
            {
                if(TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    MCASP_close(h);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP loopjob recovery data mismatch");

}

/**
 * \brief  Configure MCASP clock source (internal or external).
 *
 * This utility function sets the MCASP instance's RX and TX clock source
 * to either internal or external, and configures the pinmux as needed.
 * It updates the hardware attributes for clock direction.
 */
static void TestMcasp_selectClockSource(uint32_t instance, int32_t useExternal)
{
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;

    /* RX clock config */
    if (useExternal == TEST_MCASP_USE_EXTERNAL_CLK)
    {
        /* Set HCLK as external */
        attrs->hwCfg.gbl.pdir = (uint32_t)0xB4000001;
        attrs->hwCfg.rx.clk.hiClk = (uint32_t)0x0U;
        attrs->hwCfg.rx.clk.isHClkExt = (uint32_t)0x1;
        attrs->hwCfg.rx.clk.hClkExt = (uint32_t)1;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
        static Pinmux_PerCfg_t extClkPinEnable[] =
        {
            { PIN_EXT_REFCLK1, (PIN_MODE(5) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE) },
            { PINMUX_END, 0U }
        };
        Pinmux_config(extClkPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif
    }
    else
    {
        /* Set HCLK as internal */
        attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000001;
        attrs->hwCfg.rx.clk.hiClk = (uint32_t)0x8001U;
        attrs->hwCfg.rx.clk.isHClkExt = (uint32_t)0x0;
        attrs->hwCfg.rx.clk.hClkExt = (uint32_t)0;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
        static Pinmux_PerCfg_t extClkPinDisable[] =
        {
            { PIN_EXT_REFCLK1, (PIN_MODE(5) | PIN_PULL_DISABLE) },
            { PINMUX_END, 0U }
        };
        Pinmux_config(extClkPinDisable, PINMUX_DOMAIN_ID_MAIN);
#endif
    }

    /* TX clock config */
    if (useExternal == TEST_MCASP_USE_EXTERNAL_CLK)
    {
        attrs->hwCfg.gbl.pdir = (uint32_t)0xB4000001;
        attrs->hwCfg.tx.clk.hiClk = (uint32_t)0x0U;
        attrs->hwCfg.tx.clk.isHClkExt = (uint32_t)0x1;
        attrs->hwCfg.tx.clk.hClkExt = (uint32_t)1;
    }
    else
    {
        attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000001;
        attrs->hwCfg.tx.clk.hiClk = (uint32_t)0x8001U;
        attrs->hwCfg.tx.clk.isHClkExt = (uint32_t)0x0;
        attrs->hwCfg.tx.clk.hClkExt = (uint32_t)0;
    }
}

/**
 * \brief  MCASP multi-instance loopback test.
 *
 * This test verifies loopback functionality for all MCASP instances in the SoC
 * when ran in same external clock.
 * It initializes buffers, submits transactions, and checks data integrity after transfer.
 * Test case category: functionality test case
 */
static void TestMcasp_multiInstanceLoopback(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i, j, k;
    MCASP_Handle mcaspHandle;
    uint32_t mismatch = 0;
    uint32_t numInstances = 2U;
    uint32_t msgCount = TEST_MCASP_APP_MSG_COUNT;
    uint32_t msgSize = TEST_MCASP_APP_MSGSIZE;
    uint32_t testCount = TEST_MCASP_APP_MSG_COUNT;

    for (i = 0; i < numInstances; i++)
    {
        uint32_t bufStartOffset = 64 * i;
        for (j = 0; j < msgCount; j++)
        {
            for (k = 0; k < msgSize; k++)
            {
                TestMcasp_txBufferMt[i][j][k] = (bufStartOffset + k) % 256;
                TestMcasp_rxBufferMt[i][j][k] = 0U;
            }
        }
        TestMcasp_cntTxMt[i] = 0;
        TestMcasp_cntRxMt[i] = 0;
    }

    CacheP_wb(TestMcasp_txBufferMt, sizeof(TestMcasp_txBufferMt), CacheP_TYPE_ALLD);
    CacheP_wb(TestMcasp_rxBufferMt, sizeof(TestMcasp_rxBufferMt), CacheP_TYPE_ALLD);

    for (i = 0; i < numInstances; i++)
    {
        if (gMcaspHandle[i] != NULL)
        {
            MCASP_close(gMcaspHandle[i]);
            gMcaspHandle[i] = NULL;
        }

        gMcaspOpenParams[i].txCallbackFxn = TestMcasp_txcbMt;
        gMcaspOpenParams[i].rxCallbackFxn = TestMcasp_rxcbMt;
        gMcaspHandle[i] = MCASP_open(i, &gMcaspOpenParams[i]);
        TEST_ASSERT_NOT_NULL_MESSAGE(gMcaspHandle[0], "MCASP_open failed in multi-instance loopback");
        mcaspHandle = gMcaspHandle[i];

        for (j = 0; j < msgCount; j++)
        {
            TestMcasp_txnTxMt[i][j].buf = (void*)&TestMcasp_txBufferMt[i][j][0];
            TestMcasp_txnTxMt[i][j].count = msgSize/4;
            TestMcasp_txnTxMt[i][j].timeout = 0xFFFFFF;
            TestMcasp_txnTxMt[i][j].args = (void*)&TestMcasp_cntTxMt[i];
            MCASP_submitTx(mcaspHandle, &TestMcasp_txnTxMt[i][j]);
        }
        for (j = 0; j < msgCount; j++)
        {
            TestMcasp_txnRxMt[i][j].buf = (void*)&TestMcasp_rxBufferMt[i][j][0];
            TestMcasp_txnRxMt[i][j].count = msgSize/4;
            TestMcasp_txnRxMt[i][j].timeout = 0xFFFFFF;
            TestMcasp_txnRxMt[i][j].args = (void*)&TestMcasp_cntRxMt[i];
            MCASP_submitRx(mcaspHandle, &TestMcasp_txnRxMt[i][j]);
        }

        status = MCASP_startTransferRx(mcaspHandle);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        status = MCASP_startTransferTx(mcaspHandle);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    uint32_t transferComplete = 0;
    while (!transferComplete)
    {
        transferComplete = 1;
        for (i = 0; i < numInstances; i++)
        {
            if ((TestMcasp_cntRxMt[i] < testCount) || (TestMcasp_cntTxMt[i] < testCount))
            {
                transferComplete = 0;
            }
        }
    }
    CacheP_inv(TestMcasp_rxBufferMt, sizeof(TestMcasp_rxBufferMt), CacheP_TYPE_ALLD);

    mismatch = 0;
    for (i = 0; i < numInstances; i++)
    {
        for (j = 0; j < msgCount; j++)
        {
            for (k = 0; k < msgSize; k++)
            {
                if (TestMcasp_txBufferMt[i][j][k] != TestMcasp_rxBufferMt[i][j][k])
                {
                    mismatch++;
                }
            }
        }
    }

    for (i = 0; i < numInstances; i++)
    {
        MCASP_Handle h = gMcaspHandle[i];
        if (h != NULL)
        {
            /* Withdraw any remaining queued transactions */
            MCASP_Transaction *txn;
            do
            {
                txn = MCASP_withdrawRx(h);
            } while (txn != NULL);
            do
            {
                txn = MCASP_withdrawTx(h);
            } while (txn != NULL);

            /* Stop transfers for this instance */
            MCASP_stopTransferRx(h);
            MCASP_stopTransferTx(h);

            MCASP_close(h);
            gMcaspHandle[i] = NULL;
        }
    }

    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, mismatch, "Multi-instance loopback data mismatch");
}

/**
 * \brief  Test MCASP transmit right-rotation configuration.
 *
 * This test iterates through all supported right-rotation values for MCASP transmit,
 * configures the hardware accordingly, performs a loopback transfer for each value,
 * and verifies that the received data matches the expected right-rotated transmit data.
 * It ensures correct operation of the right-rotation feature across all settings.
 * Test case category: functionality test case
 */
void TestMcasp_configTxRightRotate(void *args)
{
    int32_t failCount = 0;
    int32_t rot;
    for (rot = 0; rot < 8; rot++)
    {
        cfg.paramType = TEST_MCASP_RIGHT_ROTATION;
        cfg.paramValue = rot;
        TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, &cfg, args);
        int32_t status = SystemP_SUCCESS;

        status = TestMcasp_loopbackTxRightRotate(args);
        if (status != SystemP_SUCCESS)
        {
            failCount++;
        }
    }
    /* reset configuration */
    cfg.paramType = TEST_MCASP_RIGHT_ROTATION;
    cfg.paramValue = TEST_MCASP_RIGHT_ROTATION_0;
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, &cfg, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, failCount, "One or more MCASP Tx right-rotate loopback tests failed");
}

/**
 * \brief  Loopback test for MCASP transmit right-rotation.
 *
 * This test configures the MCASP transmit right-rotation value,
 * performs a loopback transfer, and compares the received data
 * against the expected right-rotated transmit data.
 * Test case category: functionality test case
 */
static int32_t TestMcasp_loopbackTxRightRotate(void *args)
{
    uint32_t status = SystemP_SUCCESS;
    uint32_t i, j = 0;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;

    /* Prepare buffers */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = j % 256;
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i] = 0xa5;
        gRxLoopjobBuf0[i] = 0;
    }
    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    /* Open MCASP instance */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    McaspHandle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    /* Submit RX and TX transactions */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(McaspHandle, &TestMcasp_txnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(McaspHandle, &TestMcasp_txnTx[i]);
    }

    status = MCASP_startTransferRx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    while ((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) ||
           (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(McaspHandle);
    MCASP_stopTransferTx(McaspHandle);

    /* Withdraw buffers */
    if (SystemP_SUCCESS == status)
    {
        MCASP_Transaction *transaction;
        do
        {
            transaction = MCASP_withdrawRx(McaspHandle);
        } while (transaction != NULL);
        do
        {
            transaction = MCASP_withdrawTx(McaspHandle);
        } while (transaction != NULL);
    }

    /* Invalidate RX buffer for DMA mode */
    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    /* Data comparison with right-rotation logic */
    if (SystemP_SUCCESS == status)
    {
        int params = ((MCASP_Attrs *)gMcaspConfig[CONFIG_MCASP0].attrs)->hwCfg.tx.fmt & 0xF;
        uint32_t rot_bits = params * 4;
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j += 4)
            {
                uint32_t tx_word = ((uint32_t)TestMcasp_txBuffer[i][j]) |
                                   ((uint32_t)TestMcasp_txBuffer[i][j+1] << 8) |
                                   ((uint32_t)TestMcasp_txBuffer[i][j+2] << 16) |
                                   ((uint32_t)TestMcasp_txBuffer[i][j+3] << 24);
                uint32_t rx_word = ((uint32_t)TestMcasp_rxBuffer[i][j]) |
                                   ((uint32_t)TestMcasp_rxBuffer[i][j+1] << 8) |
                                   ((uint32_t)TestMcasp_rxBuffer[i][j+2] << 16) |
                                   ((uint32_t)TestMcasp_rxBuffer[i][j+3] << 24);
                uint32_t expected = (tx_word >> rot_bits) | (tx_word << (32 - rot_bits));
                expected &= 0xFFFFFFFF;
                if (rx_word != expected)
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    MCASP_close(McaspHandle);
    McaspHandle = NULL;
    return status;

}

/**
 * \brief  Test MCASP transmit frame sync bit delay configuration.
 *
 * This test iterates through supported frame sync bit delay values for MCASP transmit,
 * configures the hardware accordingly, performs a loopback transfer for each value,
 * and verifies that the received data matches the expected transmit data.
 * It ensures correct operation of the frame sync bit delay feature across all settings.
 * Test case category: functionality test case
 */
static void TestMcasp_validateFrameSyncBitDelay(void *args)
{
    int32_t status = SystemP_SUCCESS;
    int32_t delay;
    for (delay = 0; delay < 2; delay++)
    {
       cfg.paramType = TEST_MCASP_FRAME_SYNC_BIT;
       cfg.paramValue = delay;
       TestMcasp_selectConfig(TEST_MCASP_DMA_MODE,&cfg, args);

        status = SystemP_SUCCESS;
        status = TestMcasp_validateConfigLoopback(args);

    }
    cfg.paramType = TEST_MCASP_FRAME_SYNC_BIT;
    cfg.paramValue = TEST_MCASP_FRAME_SYNC_BIT_0;
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, &cfg, args); /* resetting the parameter */
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP Tx Frame Sync Bit Delay loopback data mismatch");
}

/**
 * \brief  MCASP loopback test for current configuration.
 *
 * This function performs a loopback transfer using the current MCASP configuration,
 * then compares the transmitted and received data for integrity.
 * It is used as a common validation routine for various MCASP configuration tests.
 * Test case category: functionality test case
 */
static int32_t TestMcasp_validateConfigLoopback(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i, j;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instanceId = (uint32_t)(openParams - &gMcaspOpenParams[0]);

    MCASP_close(gMcaspHandle[instanceId]);
    gMcaspHandle[instanceId] = NULL;

    openParams->txLoopjobBuf = gTxLoopjobBuf0;
    openParams->rxLoopjobBuf = gRxLoopjobBuf0;

    MCASP_Handle handle = MCASP_open(instanceId, openParams);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = j % 256;
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }

    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i] = 0xa5;
        gRxLoopjobBuf0[i] = 0;
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*) &TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE / 4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_txnRx[i]);
    }

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*) &TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE / 4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_txnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    while ((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) ||
          (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    /* Withdraw transactions to flush DMA/QM lists */
    if (status == SystemP_SUCCESS)
    {
        MCASP_Transaction *txn;
        do
        {
            txn = MCASP_withdrawRx(handle);
        } while (txn != NULL);
        do
        {
            txn = MCASP_withdrawTx(handle);
        } while (txn != NULL);
    }

    /* Invalidate RX buffer cache if DMA mode */
    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer,
                   TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT,
                   CacheP_TYPE_ALL);
    }

    /* Compare data */
    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
            {
                if (TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    MCASP_close(handle);

    return status;
}

/**
 * \brief  Test MCASP transmit frame sync width configuration.
 *
 * This test iterates through supported frame sync width values for MCASP transmit,
 * configures the hardware accordingly, performs a loopback transfer for each value,
 * and verifies that the received data matches the expected transmit data.
 * It ensures correct operation of the frame sync width feature across all settings.
 * Test case category: functionality test case
 */
static void TestMcasp_configFrameSyncWidth(void *args)
{
    int32_t failCount = 0;
    int32_t status;
    int32_t width;

    for (width = 0; width <= 1; width++)
    {
        cfg.paramType = TEST_MCASP_FRAME_SYNC_WIDTH;
        cfg.paramValue = width;
        TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, &cfg, args);
        status = TestMcasp_validateConfigLoopback(args);

        if (status != SystemP_SUCCESS)
        {
            failCount++;
        }
    }
    cfg.paramType = TEST_MCASP_FRAME_SYNC_WIDTH;
    cfg.paramValue = TEST_MCASP_FRAME_SYNC_WIDTH_WORD;
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, &cfg, args); /* reset config */
    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, failCount, "One or more MCASP Tx Frame Sync Width loopback tests failed");

}

/**
 * \brief  Test MCASP transmit serial bitstream order configuration.
 *
 * This test iterates through supported serial bitstream order values (LSB/MSB) for MCASP,
 * configures the hardware accordingly, performs a loopback transfer for each value,
 * and verifies that the received data matches the expected transmit data.
 * It ensures correct operation of the serial bitstream order feature across all settings.
 * Test case category: functionality test case
 */
static void TestMcasp_configSerialBitstream(void *args)
{
    int32_t failCount = 0;
    int32_t status;
    int32_t order;

    for (order = 0; order <= 1; order++)
    {
        cfg.paramType = TEST_MCASP_SERIAL_BITSTREAM;
        cfg.paramValue = order;
        TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, &cfg, args);
        status = TestMcasp_validateConfigLoopback(args);

        if (status != SystemP_SUCCESS)
        {
            failCount++;
        }
    }
    cfg.paramType = TEST_MCASP_SERIAL_BITSTREAM;
    cfg.paramValue = TEST_MCASP_SERIAL_BITSTREAM_MSB;
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, &cfg, args);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, failCount, "One or more MCASP Tx Serial Bitstream Order loopback tests failed");
}

/**
 * \brief  Test MCASP transmit clock polarity configuration.
 *
 * This test iterates through supported clock polarity values for MCASP transmit,
 * configures the hardware accordingly, performs a loopback transfer for each value,
 * and verifies that the received data matches the expected transmit data.
 * It ensures correct operation of the clock polarity feature across all settings.
 * Test case category: functionality test case
 */
static void TestMcasp_configClockPolarity(void *args)
{
    int32_t failCount = 0;
    int32_t status;
    int32_t polarity;

    for (polarity = 0; polarity <= 1; polarity++)
    {
        cfg.paramType = TEST_MCASP_CLOCK_POLARITY;
        cfg.paramValue = polarity;
        TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, &cfg, args);
        status = TestMcasp_validateConfigLoopback(args);

        if (status != SystemP_SUCCESS)
        {
            failCount++;
        }
    }
    cfg.paramType = TEST_MCASP_CLOCK_POLARITY;
    cfg.paramValue = TEST_MCASP_CLOCK_POLARITY_FALLING;
    TestMcasp_selectConfig(TEST_MCASP_DMA_MODE, &cfg, args); /* reset config */
    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, failCount, "One or more MCASP Tx Clock Polarity loopback tests failed");
}

/**
 * \brief  Test MCASP with NULL loopjob buffers.
 *
 * This test verifies how the driver handles if loopjob is disabled.
 * Test category : Negative test case
 */
static void TestMcasp_nullLoopjob(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Handle h;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, j = 0;

    /* Open MCASP in DMA mode */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;

    openParams->txLoopjobEnable = FALSE;
    openParams->rxLoopjobEnable = FALSE;
    openParams->rxLoopjobBuf = NULL;
    openParams->txLoopjobBuf = NULL;

    h = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(h);

    /* Fill TX buffer with pattern, clear RX buffer */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = (uint8_t)(j & 0xFF);
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    /* Start transfer with only loopjob buffers (no user buffer submitted) */
    status = MCASP_startTransferRx(h);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(h);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFFU;
        status = MCASP_submitRx(h, &TestMcasp_txnRx[i]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFFU;
        status = MCASP_submitTx(h, &TestMcasp_txnTx[i]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for a short time to let MCASP run with loopjob */
    ClockP_usleep(1000000);

    /* Wait for completion */
    while ((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT))
    {
    /*wait for completion*/
    }

    MCASP_stopTransferRx(h);
    MCASP_stopTransferTx(h);

    /* Withdraw any remaining buffers */
    MCASP_Transaction *transaction;
    do
    {
        transaction = MCASP_withdrawRx(h);
    } while (transaction != NULL);
    do
    {
        transaction = MCASP_withdrawTx(h);
    } while (transaction != NULL);

    /* Invalidate RX buffer for DMA */
    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    /* Compare data */
    if(status == SystemP_SUCCESS)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
            {
                if(TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    openParams->txLoopjobEnable = TRUE;
    openParams->rxLoopjobEnable = TRUE;
    openParams->rxLoopjobBuf = gRxLoopjobBuf0;
    openParams->txLoopjobBuf = gTxLoopjobBuf0;
    MCASP_close(h);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP loopjob recovery data mismatch");
}

/**
 * \brief  Test MCASP driver behavior with NULL callback functions.
 *
 * This test verifies that the MCASP driver operates correctly when the TX and/or RX
 * callback function pointers are set to NULL. It ensures that the driver does not crash
 * or misbehave if callbacks are not provided, and that data transfer and integrity are maintained.
 * Test case category: negative test case
 */
void TestMcasp_callbackNull(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i=0, j=0;
    MCASP_OpenParams *openparams = (MCASP_OpenParams*)args;
    /* Compute instance index from pointer arithmetic */
    uint32_t instanceId = (uint32_t)(openparams - &gMcaspOpenParams[0]);
    MCASP_close(gMcaspHandle[instanceId]);
    gMcaspHandle[instanceId] = NULL;

    openparams->txCallbackFxn = NULL;
    openparams->rxCallbackFxn = NULL;

    McaspHandle = MCASP_open(instanceId, openparams);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;
    /* Memfill buffers */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = j % 256;
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }

    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < 256; i++)
    {
        gTxLoopjobBuf0[i] = 0xa5;
        gRxLoopjobBuf0[i] = 0;
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*) &TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(McaspHandle,  &TestMcasp_txnRx[i]);
    }

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*) &TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(McaspHandle, &TestMcasp_txnTx[i]);
    }


    status = MCASP_startTransferRx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    while ((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT ) ||
           (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT ))
    {
        /* wait for transfer completion. */
    }

    MCASP_stopTransferRx(McaspHandle);
    MCASP_stopTransferTx(McaspHandle);

    /* withdraw the buffers submitted to driver. */
    if(SystemP_SUCCESS == status)
    {
        MCASP_Transaction *transaction;
        do
        {
            transaction = MCASP_withdrawRx(McaspHandle);
        }while (transaction != NULL);
        do
        {
            transaction = MCASP_withdrawTx(McaspHandle);
        }while (transaction != NULL);
    }

    /* Invalidate RX buffer only for DMA mode */
    if (openparams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    if(SystemP_SUCCESS == status)
    {
        /* Compare data */
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
            {
                if(TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    openparams->txCallbackFxn = mcasp_txcb;
    openparams->rxCallbackFxn = mcasp_rxcb;
    MCASP_close(McaspHandle);
    McaspHandle = NULL;

    /* Final Unity assert */
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP loopback transfer data mismatch");
    return;
}
#ifdef SOC_AM62AX
/**
 * \brief  Test MCASP external loopback.
 *
 * This test verifies MCASP data integrity when using external loopback mode.
 * It disables internal digital loopback, performs a loopback transfer with the
 * expectation that the MCASP TX and RX pins are externally connected, and checks
 * that the received data matches the transmitted data.
 * Test case category: functionality test case
 */
static void TestMcasp_externalLoopback(void *args)
{
    int32_t status;
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[CONFIG_MCASP0].attrs;

    attrs->hwCfg.gbl.dlbCtl = (uint32_t)0x0; /* internal loopback disable*/
    status = TestMcasp_validateConfigLoopback(args);
     attrs->hwCfg.gbl.dlbCtl = (uint32_t)0x7; /* internal loopback enable*/

    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP external loopback data mismatch");
}
#endif

/**
 * \brief  Test MCASP all-serializer loopback.
 *
 * This test verifies MCASP loopback functionality when multiple serializers are enabled.
 * It configures all available serializers for both transmit and receive, sets up the pinmux,
 * performs a loopback transfer, and checks that the received data matches the transmitted data.
 * After the test, it restores the serializer and FIFO configuration to default values.
 * Test case category: functionality test case
 */
static void TestMcasp_allSerializerLoopback(void *args)
{
    int32_t status,i;
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[CONFIG_MCASP2].attrs;
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC005555;

    for (i = 0; i < 16; i++)
    {
        attrs->hwCfg.gbl.serSetup[i] = (i % 2) ? 0x2 : 0x1;
    }
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12008U;
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12008U;

    uint8_t gMcasp2TxSersUsed[8] = {0,2,4,6,8,10,12,14};
    uint8_t gMcasp2RxSersUsed[8] = {1,3,5,7,9,11,13,15};

    gMcaspOpenParams[2].txSerUsedCount = 8;
    gMcaspOpenParams[2].rxSerUsedCount = 8;
    gMcaspOpenParams[2].txSerUsedArray = (uint8_t *) gMcasp2TxSersUsed;
    gMcaspOpenParams[2].rxSerUsedArray = (uint8_t *) gMcasp2RxSersUsed;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinEnable[] = {

    /* MCASP2 pin config */
    { PIN_GPMC0_AD10, ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR2 */
    { PIN_GPMC0_AD11, ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR3 */
    { PIN_GPMC0_AD0,  ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR4 */
    { PIN_GPMC0_AD1,  ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR5 */
    { PIN_GPMC0_AD2,  ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR6 */
    { PIN_GPMC0_AD3,  ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR7 */
    { PIN_GPMC0_AD4,  ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR8 */
    { PIN_GPMC0_AD5,  ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR9 */
    { PIN_GPMC0_AD6,  ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR10 */
    { PIN_GPMC0_AD7,  ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR11 */
    { PIN_GPMC0_BE1N, ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR12 */
    { PIN_GPMC0_DIR,  ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR13 */
    { PIN_GPMC0_CSN0, ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR14 */
    { PIN_GPMC0_CSN1, ( PIN_MODE(3) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE ) }, /* MCASP2_AXR15 */
    { PINMUX_END, 0U }
    };

    Pinmux_config(serPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif

    status = TestMcasp_validateConfigLoopback(args);

    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000001;
    for (i = 2; i < 16; i++)
    {
        attrs->hwCfg.gbl.serSetup[i] = 0x0;
    }
    attrs->hwCfg.gbl.serSetup[0] = 0x1;
    attrs->hwCfg.gbl.serSetup[1] = 0x2;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12001U;

    gMcasp2TxSersUsed[1] = 0;
    gMcasp2RxSersUsed[1] = 1;

    gMcaspOpenParams[2].txSerUsedCount = 1;
    gMcaspOpenParams[2].rxSerUsedCount = 1;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinDisable[] = {

    /* MCASP2 pin config */
    { PIN_GPMC0_AD10, ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR2 */
    { PIN_GPMC0_AD11, ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR3 */
    { PIN_GPMC0_AD0,  ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR4 */
    { PIN_GPMC0_AD1,  ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR5 */
    { PIN_GPMC0_AD2,  ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR6 */
    { PIN_GPMC0_AD3,  ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR7 */
    { PIN_GPMC0_AD4,  ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR8 */
    { PIN_GPMC0_AD5,  ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR9 */
    { PIN_GPMC0_AD6,  ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR10 */
    { PIN_GPMC0_AD7,  ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR11 */
    { PIN_GPMC0_BE1N, ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR12 */
    { PIN_GPMC0_DIR,  ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR13 */
    { PIN_GPMC0_CSN0, ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR14 */
    { PIN_GPMC0_CSN1, ( PIN_MODE(3) | PIN_PULL_DISABLE ) }, /* MCASP2_AXR15 */
    { PINMUX_END, 0U }
    };
    Pinmux_config(serPinDisable, PINMUX_DOMAIN_ID_MAIN);
#endif

    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "All serializers enable loopback data mismatch");

}

/**
 * \brief  Test MCASP semi-interleaved 2 to semi-interleaved 1 loopback.
 *
 * This test verifies MCASP data integrity when transmitting in semi-interleaved-2 format
 * and receiving in semi-interleaved-1 format. It configures the serializers and buffer formats,
 * performs a loopback transfer, and checks that the received data matches the transmitted data
 * after appropriate reordering for the buffer formats.
 * Test case category: functionality test case
 */
static void TestMcasp_loopbackSemiInterleaved2ToSemiInterleaved1(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, ser, slot, b, sample;

    const uint32_t numSerializers = 2;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8;

    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000005;
    attrs->hwCfg.gbl.serSetup[2]=0x1;
    attrs->hwCfg.gbl.serSetup[3]=0x2;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0TxSersUsed[2] = {0,2};
    uint8_t gMcasp0RxSersUsed[2] = {1,3};
    gMcaspOpenParams[0].rxSerUsedCount = 2;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;
    gMcaspOpenParams[0].txSerUsedCount = 2;
    gMcaspOpenParams[0].txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinEnable[]=
    {
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif

    /* Set buffer formats */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (b = 0U; b < TEST_MCASP_APP_MSGSIZE; b++)
        {
            TestMcasp_txBuffer[i][b] = b % 256;
            TestMcasp_rxBuffer[i][b] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;


    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_txnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_txnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    uint32_t timeout = 10000;
    while (((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT)) && (timeout > 0))
    {
        ClockP_usleep(1000);
        timeout--;
    }

    if (timeout == 0)
    {
        status = SystemP_FAILURE; /* Timeout occurred */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    if (SystemP_SUCCESS == status)
    {
        const uint32_t numSamples = TEST_MCASP_APP_MSGSIZE / (slotSize * numSlots * numSerializers);
        
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for (sample = 0; sample < numSamples; sample++)
            {
                for (ser = 0; ser < numSerializers; ser++)
                {
                    for (slot = 0; slot < numSlots; slot++)
                    {
                        uint32_t txOffset = ((ser * numSamples * numSlots) + 
                                            (sample * numSlots) + 
                                            slot) * slotSize;
                        
                        uint32_t rxOffset = ((sample * numSlots * numSerializers) + 
                                            (slot * numSerializers) + 
                                            ser) * slotSize;
                        
                        /* Compare slot data byte by byte */
                        for (b = 0; b < slotSize; b++)
                        {
                            if (TestMcasp_txBuffer[i][txOffset + b] != TestMcasp_rxBuffer[i][rxOffset + b])
                            {
                                status = SystemP_FAILURE;
                            }
                        }
                    }
                }
            }
        }
    }

    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000001;
    attrs->hwCfg.gbl.serSetup[2]=0x0;
    attrs->hwCfg.gbl.serSetup[3]=0x0;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    gMcasp0RxSersUsed[1] = 1;
    gMcasp0TxSersUsed[1] = 1;
    gMcaspOpenParams[0].rxSerUsedCount = 1;
    gMcaspOpenParams[0].txSerUsedCount = 1;
    gMcaspOpenParams[0].txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinDisable[] =
    {
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinDisable, PINMUX_DOMAIN_ID_MAIN);
#endif

    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    MCASP_close(handle);

    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "Interleaved to Semi-Interleaved loopback mismatch");
}

/**
 * \brief  Test MCASP semi-interleaved-1 to semi-interleaved-2 loopback.
 *
 * This test verifies MCASP data integrity when transmitting in semi-interleaved-1 format
 * and receiving in semi-interleaved-2 format. It configures the serializers and buffer formats,
 * performs a loopback transfer, and checks that the received data matches the transmitted data
 * after appropriate reordering for the buffer formats.
 * Test case category: functionality test case
 */
static void TestMcasp_loopbackSemiInterleaved1ToSemiInterleaved2(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, ser, slot, b, sample;
    const uint32_t numSerializers = 2;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8;

    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000005;
    attrs->hwCfg.gbl.serSetup[2]=0x1;
    attrs->hwCfg.gbl.serSetup[3]=0x2;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0TxSersUsed[2] = {0,2};
    uint8_t gMcasp0RxSersUsed[2] = {1,3};
    gMcaspOpenParams[0].rxSerUsedCount = 2;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;
    gMcaspOpenParams[0].txSerUsedCount = 2;
    gMcaspOpenParams[0].txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinEnable[]=
    {
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif

    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (b = 0U; b < TEST_MCASP_APP_MSGSIZE; b++)
        {
            TestMcasp_txBuffer[i][b] = b % 256;
            TestMcasp_rxBuffer[i][b] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_txnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_txnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    uint32_t timeout = 10000;
    while (((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT)) && (timeout > 0))
    {
        ClockP_usleep(1000);
        timeout--;
    }

    if (timeout == 0)
    {
        status = SystemP_FAILURE; /* Timeout occurred */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    if (SystemP_SUCCESS == status)
    {
        
        const uint32_t numSamples = TEST_MCASP_APP_MSGSIZE / (slotSize * numSlots * numSerializers);
        
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for (sample = 0; sample < numSamples; sample++)
            {
                for (ser = 0; ser < numSerializers; ser++)
                {
                    for (slot = 0; slot < numSlots; slot++)
                    {
                        uint32_t txOffset = ((sample * numSerializers * numSlots) + 
                                            (ser * numSlots) + 
                                            slot) * slotSize;
                        
                        uint32_t rxOffset = ((slot * numSamples * numSerializers) + 
                                            (sample * numSerializers) + 
                                            ser) * slotSize;
                        
                        /* Compare slot data byte by byte */
                        for (b = 0; b < slotSize; b++)
                        {
                            if (TestMcasp_txBuffer[i][txOffset + b] != TestMcasp_rxBuffer[i][rxOffset + b])
                            {
                                status = SystemP_FAILURE;
                            }
                        }
                    }
                }
            }
        }
    }
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000001;
    attrs->hwCfg.gbl.serSetup[2]=0x0;
    attrs->hwCfg.gbl.serSetup[3]=0x0;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    gMcasp0RxSersUsed[1] = 1;
    gMcasp0TxSersUsed[1] = 1;
    gMcaspOpenParams[0].rxSerUsedCount = 1;
    gMcaspOpenParams[0].txSerUsedCount = 1;
    gMcaspOpenParams[0].txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinDisable[] =
    {
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinDisable, PINMUX_DOMAIN_ID_MAIN);
#endif
    
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    MCASP_close(handle);

    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "Interleaved to Semi-Interleaved-2 loopback mismatch");
}

/**
 * \brief  Test MCASP interleaved to non-interleaved loopback.
 *
 * This test verifies MCASP data integrity when transmitting in interleaved format
 * and receiving in non-interleaved format. It configures the buffer formats,
 * performs a loopback transfer, and checks that the received data matches the transmitted data
 * after appropriate reordering for the buffer formats.
 * Test case category: functionality test case
 */
static void TestMcasp_loopbackInterleavedToNonInterleaved(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, slot, sample, b;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8;
    const uint32_t numSamples = TEST_MCASP_APP_MSGSIZE / (numSlots * slotSize);

    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_NON_INTERLEAVED;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (b = 0U; b < TEST_MCASP_APP_MSGSIZE; b++)
        {
            TestMcasp_txBuffer[i][b] = b % 256;
            TestMcasp_rxBuffer[i][b] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_txnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_txnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    uint32_t timeout = 10000;
    while (((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT)) && (timeout > 0))
    {
        ClockP_usleep(1000);
        timeout--;
    }

    if (timeout == 0)
    {
        status = SystemP_FAILURE; /* Timeout occurred */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for (slot = 0; slot < numSlots; slot++)
            {
                for (sample = 0; sample < numSamples; sample++)
                {
                    uint32_t tx_offset = (sample * numSlots + slot) * slotSize;
                    uint32_t rx_offset = (slot * numSamples + sample) * slotSize;
                    for (b = 0; b < slotSize; b++)
                    {
                        if (TestMcasp_txBuffer[i][tx_offset + b] != TestMcasp_rxBuffer[i][rx_offset + b])
                        {
                            status = SystemP_FAILURE;
                        }
                    }
                }
            }
        }
    }
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    MCASP_close(handle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "Interleaved to Non-Interleaved loopback mismatch");
}

/**
 * \brief  Test MCASP non-interleaved to interleaved loopback.
 *
 * This test verifies MCASP data integrity when transmitting in non-interleaved format
 * and receiving in interleaved format. It configures the buffer formats,
 * performs a loopback transfer, and checks that the received data matches the transmitted data
 * after appropriate reordering for the buffer formats.
 * Test case category: functionality test case
 */
static void TestMcasp_loopbackNonInterleavedToInterleaved(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, slot, sample, b;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8;
    const uint32_t numSamples = TEST_MCASP_APP_MSGSIZE / (numSlots * slotSize);

    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_NON_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (b = 0U; b < TEST_MCASP_APP_MSGSIZE; b++)
        {
            TestMcasp_txBuffer[i][b] = b % 256;
            TestMcasp_rxBuffer[i][b] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_txnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_txnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    uint32_t timeout = 10000;
    while (((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT)) && (timeout > 0))
    {
        ClockP_usleep(1000);
        timeout--;
    }

    if (timeout == 0)
    {
        status = SystemP_FAILURE; /* Timeout occurred */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for (sample = 0; sample < numSamples; sample++)
            {
                for (slot = 0; slot < numSlots; slot++)
                {
                    uint32_t tx_offset = (slot * numSamples + sample) * slotSize;
                    uint32_t rx_offset = (sample * numSlots + slot) * slotSize;
                    for (b = 0; b < slotSize; b++)
                    {
                        if (TestMcasp_txBuffer[i][tx_offset + b] != TestMcasp_rxBuffer[i][rx_offset + b])
                        {
                            status = SystemP_FAILURE;
                        }
                    }
                }
            }
        }
    }
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    MCASP_close(handle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "Non-Interleaved to Interleaved loopback mismatch");
}

/**
 * \brief  Configure MCASP instance for multi-instance tests.
 *
 * This function sets the MCASP open parameters and hardware attributes
 * for the specified MCASP instance, based on the test scenario and configuration mode.
 * It supports both normal and revert configurations, adjusting slot counts, slot sizes,
 * masks, formats, frame sync, clock settings, and auxiliary clock configuration as needed.
 * Used by multi-instance loopback and configuration tests.
 * Test case category: utility support function
 */
static void TestMcasp_configMultiInstance(int instance, int32_t flag,MCASP_OpenParams *openparams)
{
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;

    switch(instance)
    {
        case 0:
            /* MCASP Instance 0If flag indicates new configuration, configure for 24-bit slots, 8 slots (multichannel) and
             * set an auxiliary clock for 50MHz for the test scenario.
             */
            if (flag == MCASP_CONFIG_NEW)
            {
                /* 24 128khz */
                gMcaspOpenParams[instance].rxSlotCount = 8;
                gMcaspOpenParams[instance].txSlotCount = 8;
                attrs->rxSlotSize         = 24;
                attrs->txSlotSize         = 24;
                attrs->hwCfg.rx.mask      = (uint32_t)0xFFFFFFU;
                attrs->hwCfg.rx.fmt       = (uint32_t)0x181B0U; /* MCASP_RXFMT */
                attrs->hwCfg.rx.frSyncCtl = (uint32_t)0x413U; /* MCASP_RXFMCTL */
                attrs->hwCfg.tx.mask      = (uint32_t)0xFFFFFFU;
                attrs->hwCfg.tx.fmt       = (uint32_t)0x181B6U; /* MCASP_TXFMT */
                attrs->hwCfg.tx.frSyncCtl = (uint32_t)0x413U; /* MCASP_TXFMCTL */
                gMcaspAuxClkConfig[0].tisciDevice = TISCI_DEV_MCASP0;
                gMcaspAuxClkConfig[0].tisciClock = TISCI_DEV_MCASP0_AUX_CLK;
                gMcaspAuxClkConfig[0].isConfigurable = 1U;
                gMcaspAuxClkConfig[0].freq = 50000000;
                gMcaspAuxClkConfig[0].option = TISCI_DEV_MCASP0_AUX_CLK_PARENT_POSTDIV4_16FF_MAIN_2_HSDIVOUT8_CLK;
            }
            else
            {
                /* Else: revert to the default configuration.
                 * This branch uses 32-bit slots, 2 slots and a standard 48MHz aux clock.
                 */
                gMcaspOpenParams[instance].rxSlotCount = 2;
                gMcaspOpenParams[instance].txSlotCount = 2;
                attrs->rxSlotSize         = 32;
                attrs->txSlotSize         = 32;
                attrs->hwCfg.rx.mask      = (uint32_t)0xFFFFFFFFU;
                attrs->hwCfg.rx.fmt       = (uint32_t)0x181F0U; /* MCASP_RXFMT */
                attrs->hwCfg.rx.frSyncCtl = (uint32_t)0x113U; /* MCASP_RXFMCTL */
                attrs->hwCfg.tx.mask      = (uint32_t)0xFFFFFFFFU;
                attrs->hwCfg.tx.fmt       = (uint32_t)0x181F0U; /* MCASP_TXFMT */
                attrs->hwCfg.tx.frSyncCtl = (uint32_t)0x113U; /* MCASP_TXFMCTL */
                gMcaspAuxClkConfig[0].tisciDevice = TISCI_DEV_MCASP0;
                gMcaspAuxClkConfig[0].tisciClock = TISCI_DEV_MCASP0_AUX_CLK;
                gMcaspAuxClkConfig[0].isConfigurable = 1U;
                gMcaspAuxClkConfig[0].freq = 48000000;
                gMcaspAuxClkConfig[0].option = TISCI_DEV_MCASP0_AUX_CLK_PARENT_POSTDIV1_16FFT_MAIN_1_HSDIVOUT6_CLK;
            }
            break;
        case 1:
            /* MCASP Instance 1: branch sets 16-bit slots and slot count as 2 for tx and rx
            * aux clock is set to 50MHz
            */
            if (flag == MCASP_CONFIG_NEW)
            {
                /* 16 50khz */
                gMcaspOpenParams[instance].rxSlotCount = 2;
                gMcaspOpenParams[instance].txSlotCount = 2;
                attrs->rxSlotSize         = 16;
                attrs->txSlotSize         = 16;
                attrs->hwCfg.rx.mask      = (uint32_t)0xFFFFU;
                attrs->hwCfg.rx.fmt       = (uint32_t)0x18170U; /* MCASP_RXFMT */
                attrs->hwCfg.rx.frSyncCtl = (uint32_t)0x113U; /* MCASP_RXFMCTL */
                attrs->hwCfg.tx.mask      = (uint32_t)0xFFFFU;
                attrs->hwCfg.tx.fmt       = (uint32_t)0x18174U; /* MCASP_TXFMT */
                attrs->hwCfg.tx.frSyncCtl = (uint32_t)0x113U; /* MCASP_TXFMCTL */
                gMcaspAuxClkConfig[1] .tisciDevice = TISCI_DEV_MCASP1;
                gMcaspAuxClkConfig[1].tisciClock = TISCI_DEV_MCASP1_AUX_CLK;
                gMcaspAuxClkConfig[1].isConfigurable = 1U;
                gMcaspAuxClkConfig[1].freq = 50000000;
                gMcaspAuxClkConfig[1].option = TISCI_DEV_MCASP1_AUX_CLK_PARENT_POSTDIV4_16FF_MAIN_2_HSDIVOUT8_CLK;
            }
            else
            {
                /* Else: revert to the default configuration.
                 * This branch uses 32-bit slots, 2 slots and a standard 48MHz aux clock.
                 */
                gMcaspOpenParams[instance].rxSlotCount = 2;
                gMcaspOpenParams[instance].txSlotCount = 2;
                attrs->rxSlotSize         = 32;
                attrs->txSlotSize         = 32;
                attrs->hwCfg.rx.mask      = (uint32_t)0xFFFFFFFFU;
                attrs->hwCfg.rx.fmt       = (uint32_t)0x181F0U; /* MCASP_RXFMT */
                attrs->hwCfg.rx.frSyncCtl = (uint32_t)0x113U; /* MCASP_RXFMCTL */
                attrs->hwCfg.tx.mask      = (uint32_t)0xFFFFFFFFU;
                attrs->hwCfg.tx.fmt       = (uint32_t)0x181F0U; /* MCASP_TXFMT */
                attrs->hwCfg.tx.frSyncCtl = (uint32_t)0x113U; /* MCASP_TXFMCTL */
                gMcaspAuxClkConfig[1].tisciDevice = TISCI_DEV_MCASP1;
                gMcaspAuxClkConfig[1].tisciClock = TISCI_DEV_MCASP1_AUX_CLK;
                gMcaspAuxClkConfig[1].isConfigurable = 1U;
                gMcaspAuxClkConfig[1].freq = 48000000;
                gMcaspAuxClkConfig[1].option = TISCI_DEV_MCASP1_AUX_CLK_PARENT_POSTDIV1_16FFT_MAIN_1_HSDIVOUT6_CLK;
            }
            break;

        case 2:
            /* Instance 2: 'new' config selects 4-slot 32-bit operation for MCASP instance 2;
            * aux clock is set to 48MHz.
            */
             if (flag == MCASP_CONFIG_NEW)
            {
                gMcaspOpenParams[instance].rxSlotCount = 4;
                gMcaspOpenParams[instance].txSlotCount = 4;
                attrs->rxSlotSize         = 32;
                attrs->txSlotSize         = 32;
                attrs->hwCfg.rx.fmt       = (uint32_t)0x181F0U; /* MCASP_RXFMT */
                attrs->hwCfg.rx.frSyncCtl = (uint32_t)0x213U; /* MCASP_RXFMCTL */
                attrs->hwCfg.tx.fmt       = (uint32_t)0x181F0U; /* MCASP_TXFMT */
                attrs->hwCfg.tx.frSyncCtl = (uint32_t)0x213U; /* MCASP_TXFMCTL */
                gMcaspAuxClkConfig[2] .tisciDevice = TISCI_DEV_MCASP2;
                gMcaspAuxClkConfig[2].tisciClock = TISCI_DEV_MCASP2_AUX_CLK;
                gMcaspAuxClkConfig[2].isConfigurable = 1U;
                gMcaspAuxClkConfig[2].freq = 48000000;
                gMcaspAuxClkConfig[2].option = TISCI_DEV_MCASP2_AUX_CLK_PARENT_POSTDIV1_16FFT_MAIN_1_HSDIVOUT6_CLK;
            }
            else
            {
                /* Else: revert to the default configuration.
                 * This branch uses 32-bit slots, 2 slots and a standard 48MHz aux clock.
                 */
                gMcaspOpenParams[instance].rxSlotCount = 2;
                gMcaspOpenParams[instance].txSlotCount = 2;
                attrs->rxSlotSize         = 32;
                attrs->txSlotSize         = 32;
                attrs->hwCfg.rx.fmt       = (uint32_t)0x181F0U; /* MCASP_RXFMT */
                attrs->hwCfg.rx.frSyncCtl = (uint32_t)0x113U; /* MCASP_RXFMCTL */
                attrs->hwCfg.tx.fmt       = (uint32_t)0x181F0U; /* MCASP_TXFMT */
                attrs->hwCfg.tx.frSyncCtl = (uint32_t)0x113U; /* MCASP_TXFMCTL */
                gMcaspAuxClkConfig[2].tisciDevice = TISCI_DEV_MCASP2;
                gMcaspAuxClkConfig[2].tisciClock = TISCI_DEV_MCASP2_AUX_CLK;
                gMcaspAuxClkConfig[2].isConfigurable = 1U;
                gMcaspAuxClkConfig[2].freq = 48000000;
                gMcaspAuxClkConfig[2].option = TISCI_DEV_MCASP2_AUX_CLK_PARENT_POSTDIV1_16FFT_MAIN_1_HSDIVOUT6_CLK;
            }
            break;

        default:
            break;

    }
}

/**
 * \brief  Test MCASP multi-instance configuration.
 *
 * This test verifies loopback functionality and data integrity for multiple MCASP instances
 * with different configurations. It initializes per-instance buffers, configures each instance,
 * submits transactions, starts transfers, and checks that the received data matches the transmitted data.
 * The test also reverts instance configurations to default after completion.
 * Test case category: functionality test case
 */
static void TestMcasp_multiInstanceConfigTest(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i, j, k;
    uint32_t mismatch = 0;
    const uint32_t numInstances = TEST_MCASP_NUM_INSTANCES_MT;
    const uint32_t msgCount     = TEST_MCASP_APP_MSG_COUNT;
    const uint32_t msgSize      = TEST_MCASP_APP_MSGSIZE;
    const uint32_t testCount    = TEST_MCASP_APP_TEST_COUNT_MT;

    /* Per-instance TX/RX counters */
    static volatile uint32_t TestMcasp_instanceCntTx[TEST_MCASP_NUM_INSTANCES_MT];
    static volatile uint32_t TestMcasp_instanceCntRx[TEST_MCASP_NUM_INSTANCES_MT];

    /* Aligned buffers */
    static uint8_t TestMcasp_instanceBufferTx[TEST_MCASP_NUM_INSTANCES_MT][TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE] __attribute__((aligned(256)));
    static uint8_t TestMcasp_instanceBufferRx[TEST_MCASP_NUM_INSTANCES_MT][TEST_MCASP_APP_MSG_COUNT] [TEST_MCASP_APP_MSGSIZE] __attribute__((aligned(256)));

    MCASP_Transaction TestMcasp_txnBufferTx[TEST_MCASP_NUM_INSTANCES_MT][TEST_MCASP_APP_MSG_COUNT] = {0};
    MCASP_Transaction TestMcasp_txnBufferRx[TEST_MCASP_NUM_INSTANCES_MT][TEST_MCASP_APP_MSG_COUNT] = {0};

    for (i = 0; i < numInstances; i++)
    {
        uint32_t bufStartOffset = 64 * i;

        for (j = 0; j < msgCount; j++)
        {
            for (k = 0; k < msgSize; k++)
            {
                TestMcasp_instanceBufferTx[i][j][k] = (bufStartOffset + k) & 0xFF;
                TestMcasp_instanceBufferRx[i][j][k] = 0;
            }
        }

        TestMcasp_instanceCntTx[i] = 0;
        TestMcasp_instanceCntRx[i] = 0;
    }

    CacheP_wb(TestMcasp_instanceBufferTx, sizeof(TestMcasp_instanceBufferTx), CacheP_TYPE_ALLD);
    CacheP_wb(TestMcasp_instanceBufferRx, sizeof(TestMcasp_instanceBufferRx), CacheP_TYPE_ALLD);

    for (i = 0; i < numInstances; i++)
    {
        if (gMcaspHandle[i] != NULL)
        {
            MCASP_close(gMcaspHandle[i]);
            gMcaspHandle[i] = NULL;
        }

        TestMcasp_configMultiInstance(i, MCASP_CONFIG_NEW,&gMcaspOpenParams[i]);
    }

    Drivers_mcaspAuxClkCfg();

    for (i = 0; i < numInstances; i++)
    {

        gMcaspOpenParams[i].txCallbackFxn = TestMcasp_txcbMt;
        gMcaspOpenParams[i].rxCallbackFxn = TestMcasp_rxcbMt;

        gMcaspHandle[i] = MCASP_open(i, &gMcaspOpenParams[i]);
        TEST_ASSERT_NOT_NULL_MESSAGE(gMcaspHandle[i], "MCASP_open failed in multi-instance loopback");

        MCASP_Handle mh = gMcaspHandle[i];

        /* Submit TX */
        for (j = 0; j < msgCount; j++)
        {
            TestMcasp_txnBufferTx[i][j].buf     = &TestMcasp_instanceBufferTx[i][j][0];
            TestMcasp_txnBufferTx[i][j].count   = msgSize / 4;
            TestMcasp_txnBufferTx[i][j].timeout = 0xFFFFFF;
            TestMcasp_txnBufferTx[i][j].args    = (void*)&TestMcasp_instanceCntTx[i];

            MCASP_submitTx(mh, &TestMcasp_txnBufferTx[i][j]);
        }

        /* Submit RX */
        for (j = 0; j < msgCount; j++)
        {
            TestMcasp_txnBufferRx[i][j].buf     = &TestMcasp_instanceBufferRx[i][j][0];
            TestMcasp_txnBufferRx[i][j].count   = msgSize / 4;
            TestMcasp_txnBufferRx[i][j].timeout = 0xFFFFFF;
            TestMcasp_txnBufferRx[i][j].args    = (void*)&TestMcasp_instanceCntRx[i];

            MCASP_submitRx(mh, &TestMcasp_txnBufferRx[i][j]);
        }

        /* Start transfers */
        status = MCASP_startTransferRx(mh);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        status = MCASP_startTransferTx(mh);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    uint32_t transferComplete = 0;
    while (!transferComplete)
    {
        transferComplete = 1;
        for (i = 0; i < numInstances; i++)
        {
            if ((TestMcasp_instanceCntRx[i] < testCount) ||
                (TestMcasp_instanceCntTx[i] < testCount))
            {
                transferComplete = 0;
            }
        }
    }

    for (i = 0; i < numInstances; i++)
    {
        MCASP_Handle mh = gMcaspHandle[i];
        MCASP_stopTransferRx(mh);
        MCASP_stopTransferTx(mh);

        gMcaspOpenParams[i].txCallbackFxn = mcasp_txcb;
        gMcaspOpenParams[i].rxCallbackFxn = mcasp_rxcb;

        MCASP_close(mh);
        gMcaspHandle[i] = NULL;
    }

    CacheP_inv(TestMcasp_instanceBufferRx, sizeof(TestMcasp_instanceBufferRx), CacheP_TYPE_ALLD);

    mismatch = 0;

    for (i = 0; i < numInstances; i++)
    {
        for (j = 0; j < msgCount; j++)
        {
            int cmp_result;

            if (i == 0)
            {
                cmp_result = TestMcasp_compareInstance0(TestMcasp_instanceBufferTx[i][j],
                                               TestMcasp_instanceBufferRx[i][j], msgSize);
            }
            else if (i == 1)
            {
                cmp_result = TestMcasp_compareInstance1(TestMcasp_instanceBufferTx[i][j],
                                               TestMcasp_instanceBufferRx[i][j], msgSize);
            }
            else
            {
                cmp_result = TestMcasp_compareInstance2(TestMcasp_instanceBufferTx[i][j],
                                               TestMcasp_instanceBufferRx[i][j], msgSize);
            }

            if (cmp_result)
            {
                mismatch++;
            }
        }
    }

    for (i = 0; i < numInstances; i++)
    {
        if (gMcaspHandle[i] != NULL)
        {
            MCASP_close(gMcaspHandle[i]);
            gMcaspHandle[i] = NULL;
        }
        /* Revert instance configuration to default */
        TestMcasp_configMultiInstance(i, MCASP_CONFIG_DEFAULT, &gMcaspOpenParams[i]);
    }
    Drivers_mcaspAuxClkCfg();
    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, mismatch, "Multi-instance loopback data mismatch");
}

/**
 * \brief  Compare TX and RX buffers for MCASP instance 0.
 *
 * function compares the transmitted and received buffers for instance 0,
 * checking that the lower 24 bits of each transmitted word match the received word.
 * Used by multi-instance configuration and loopback tests to validate data integrity.
 * Test case category: utility support function
 */
static int32_t TestMcasp_compareInstance0(uint8_t *tx, uint8_t *rx, uint32_t msgSize)
{
    uint32_t tx_word, rx_word, j;
    for (j = 0; j < msgSize; j += 4)
    {
        tx_word = (tx[j+3] << 24) |
                  (tx[j+2] << 16) |
                  (tx[j+1] << 8)  |
                  (tx[j+0]);
        rx_word = (rx[j+2] << 16) |
                  (rx[j+1] << 8)  |
                  (rx[j+0]);

        if ((tx_word & 0x00FFFFFF) != rx_word)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * \brief  Compare TX and RX buffers for MCASP instance 1.
 *
 *  This function compares the transmitted and received buffers for instance 1,
 *  checking that the lower 16 bits of each transmitted word match the received word.
 *  Used by multi-instance configuration and loopback tests to validate data integrity.
 *  Test case category: utility support function
 */
static int32_t TestMcasp_compareInstance1(uint8_t *tx, uint8_t *rx, uint32_t msgSize)
{
    uint32_t tx_word, rx_word, j;
    for (j = 0; j < msgSize; j += 4)
    {
        tx_word = (tx[j+3] << 24) |
                  (tx[j+2] << 16) |
                  (tx[j+1] << 8)  |
                  (tx[j+0]);
        rx_word = (rx[j+2] << 16) |
                  (rx[j+1] << 8)  |
                  (rx[j+0]);

        if ((tx_word & 0x0000FFFF) != rx_word)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * \brief  Compare TX and RX buffers for MCASP instance 2.
 *
 *  This function compares the transmitted and received buffers for instance 2,
 *  checking that each byte in the transmit buffer matches the corresponding byte in the receive buffer.
 *  Used by multi-instance configuration and loopback tests to validate data integrity.
 *  Test case category: utility support function
 */
static int32_t TestMcasp_compareInstance2(uint8_t *tx, uint8_t *rx, uint32_t msgSize)
{
    uint32_t k;
    for ( k = 0; k < msgSize; k++)
    {
        if (tx[k] != rx[k])
        {
            return 1;
        }
    }
    return 0;
}

/**
 * \brief  Test MCASP FIFO disable configuration.
 *
 * This test verifies MCASP loopback functionality when the FIFO is disabled.
 * It sets the FIFO water-level to zero and disables the FIFO control registers,
 * performs a loopback transfer, and checks that the received data matches the transmitted data.
 * After the test, it restores the FIFO configuration to default values.
 * Test case category: functionality test case
 */
static void TestMcasp_fifoDisable(void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[CONFIG_MCASP0].attrs;

    attrs->txFifoWaterLevel = 0;
    attrs->rxFifoWaterLevel = 0;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x2001U;
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x2001U;
    openParams->rxCallbackFxn = mcasp_rxcb;
    openParams->txCallbackFxn = mcasp_txcb;

    status =  TestMcasp_validateConfigLoopback(args);

    attrs->txFifoWaterLevel = 32;
    attrs->rxFifoWaterLevel = 32;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "MCASP loopback transfer data mismatch");

}


/**
 * \brief  Test MCASP driver dynamic coverage.
 *
 * This test exercises various negative and edge-case scenarios for the MCASP driver,
 * including invalid handles, zero transaction counts, NULL transaction pointers,
 * invalid object pointers, and FIFO water-level violations. It ensures the driver
 * returns correct error codes and does not crash or misbehave under these conditions.
 * Test case category: negative and coverage test case
 */
static void TestMcasp_DynamicCoverage(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status = SystemP_SUCCESS;
    MCASP_Handle handle;
    /* mcasp invalid hanlde */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    int32_t invalidIndex = gMcaspConfigNum; /* first invalid index */
    handle = MCASP_open(invalidIndex, NULL);
    if (handle != NULL)
    {
        MCASP_close(handle);
    }
    TEST_ASSERT_NULL_MESSAGE(handle, "MCASP_open should fail with invalid index");

    /* passing txn count as 0 for validate transaction*/
    handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Valid MCASP_open failed unexpectedly");
    MCASP_Transaction txZero = {0};
    MCASP_Transaction rxZero = {0};
    txZero.buf = (void*)TestMcasp_txBuffer[0];
    txZero.count = 0;          /* invalid */
    txZero.timeout = 0xFFFFFF;
    rxZero.buf = (void*)TestMcasp_rxBuffer[0];
    rxZero.count = 0;          /* invalid */
    rxZero.timeout = 0xFFFFFF;
    status = MCASP_submitTx(handle, &txZero);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_submitTx should fail for count=0");
    status = MCASP_submitRx(handle, &rxZero);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_submitRx should fail for count=0");
    if (handle != NULL)
    {
        MCASP_close(handle);
    }

    /* Zero count with NULL transaction pointer */
    handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);
    status = MCASP_submitTx(handle, NULL);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_submitTx should fail on NULL txn");
    status = MCASP_submitRx(handle, NULL);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_submitRx should fail on NULL txn");
    if (handle != NULL)
    {
        MCASP_close(handle);
    }
    TEST_ASSERT_TRUE_MESSAGE(1, "Dynamic coverage completed");
    MCASP_Transaction *txn = MCASP_withdrawTx(NULL);
    TEST_ASSERT_NULL_MESSAGE(txn, "MCASP_withdrawTx should return NULL when handle is NULL");
    txn = MCASP_withdrawRx(NULL);
    TEST_ASSERT_NULL_MESSAGE(txn, "MCASP_withdrawRx should return NULL when handle is NULL");

    /* Negative withdraw: object is NULL */
    /* Create a dummy config with NULL object */
    MCASP_Config dummyConfig = {0};
    dummyConfig.object = NULL;
    txn = MCASP_withdrawTx((MCASP_Handle)&dummyConfig);
    TEST_ASSERT_NULL_MESSAGE(txn, "MCASP_withdrawTx should return NULL when object is NULL");
    txn = MCASP_withdrawRx((MCASP_Handle)&dummyConfig);
    TEST_ASSERT_NULL_MESSAGE(txn, "MCASP_withdrawRx should return NULL when object is NULL");

    handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    /* Test TX with NULL handle */
    status = MCASP_startTransferTx(NULL);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_startTransferTx should fail for NULL handle");

    /* Test RX with NULL handle */
    status = MCASP_startTransferRx(NULL);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_startTransferRx should fail for NULL handle");

    /* Negative test for stopTransferTx with NULL handle */
    status = MCASP_stopTransferTx(NULL);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_stopTransferTx should fail for NULL handle");

    /* Negative test for stopTransferRx with NULL handle */
    status = MCASP_stopTransferRx(NULL);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_stopTransferRx should fail for NULL handle");

    dummyConfig.object = NULL;
    status = MCASP_startTransferTx((MCASP_Handle)&dummyConfig);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_startTransferTx should fail for NULL attrs/pReg");

    status = MCASP_startTransferRx((MCASP_Handle)&dummyConfig);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_startTransferRx should fail for NULL attrs/pReg");

    /* Negative test for stopTransferTx with invalid object */
    status = MCASP_stopTransferTx((MCASP_Handle)&dummyConfig);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_stopTransferTx should fail for NULL attrs/pReg");

    /* Negative test for stopTransferRx with invalid object */
    status = MCASP_stopTransferRx((MCASP_Handle)&dummyConfig);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_stopTransferRx should fail for NULL attrs/pReg");

    /* Negative test for MCASP_setTxTxnCount with NULL handle */
    status = MCASP_setTxTxnCount(NULL, 1);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_setTxTxnCount should fail for NULL handle");

    /* Negative test for MCASP_setRxTxnCount with NULL handle */
    status = MCASP_setRxTxnCount(NULL, 1);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_setRxTxnCount should fail for NULL handle");

    MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_setRxTxnCount should fail for NULL handle");

    handle = MCASP_getHandle(CONFIG_MCASP0);
    if (handle != NULL)
    {
        MCASP_close(handle);
        handle = NULL;
    }

}

/**
 * \brief  DMA initDone==1, loopjob count mismatch and FIFO water-level violations.
 *
 * This test primes TX and RX to set txDmaIcnt.initDone/rxDmaIcnt.initDone == 1,
 * Forces a mismatch between submitted transaction count and object->txnLoopjob.count
 * to validate failure on the initDone==1 path.
 * Programs TX/RX FIFO water-levels to non-divisible values and submits counts matching
 * loopjob.count to exercise the "count not multiple of water-level bytes" failure.
 * TX/RX submit path when initDone == 1 (loopjob/count equality check).
 * FIFO water-level multiple rule: byteCnt % (WORD_BYTE_COUNT * waterLevel) != 0 -> failure.
 *
 * Test case category: negative test case
 */
static void TestMcasp_dmaInitDoneOneLoopjobAndWaterLevelNegative(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status;
    MCASP_Handle handle;

    /* Use local aligned buffers for submits */
    static uint32_t txBuf[2048] __attribute__((aligned(64)));
    static uint32_t rxBuf[2048] __attribute__((aligned(64)));

    handle =  MCASP_getHandle(CONFIG_MCASP0);
    if(handle != NULL)
    {
        MCASP_close(handle);
        handle = NULL;
    }
    handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "MCASP_open failed in DMA initDone==1 negative test");

    MCASP_Config *cfgH = (MCASP_Config*)handle;
    MCASP_Object *obj = cfgH->object;
    MCASP_Attrs  *attrs = (MCASP_Attrs *)cfgH->attrs;

    uint32_t txLjCnt = obj->XmtObj.txnLoopjob.count; /* words */
    uint32_t rxLjCnt = obj->RcvObj.txnLoopjob.count; /* words */
    TEST_ASSERT_TRUE_MESSAGE(txLjCnt > 0U, "TX loopjob count is zero");
    TEST_ASSERT_TRUE_MESSAGE(rxLjCnt > 0U, "RX loopjob count is zero");

    /* Prime once to set initDone == 1 */
    MCASP_Transaction txPrime = { .buf = txBuf, .count = txLjCnt, .timeout = 0xFFFFFFU };
    MCASP_Transaction rxPrime = { .buf = rxBuf, .count = rxLjCnt, .timeout = 0xFFFFFFU };
    status = MCASP_submitTx(handle, &txPrime);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "TX prime failed");
    status = MCASP_submitRx(handle, &rxPrime);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "RX prime failed");

    /* initDone == 1 mismatch: keep txnByteCnt same; change loopjob.count to force mismatch */
    uint32_t origTxLjCnt = txLjCnt, origRxLjCnt = rxLjCnt;
    uint32_t savedTxWater1 = attrs->txFifoWaterLevel;
    uint32_t savedRxWater1 = attrs->rxFifoWaterLevel;
    attrs->txFifoWaterLevel = 0U;
    attrs->rxFifoWaterLevel = 0U;

    obj->XmtObj.txnLoopjob.count = origTxLjCnt + 1U;
    MCASP_Transaction txLoopjobMismatch1 = { .buf = txBuf, .count = origTxLjCnt, .timeout = 0xFFFFFFU };
    status = MCASP_submitTx(handle, &txLoopjobMismatch1);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "Expected TX loopjob-count failure (initDone==1)");

    obj->RcvObj.txnLoopjob.count = origRxLjCnt + 1U;
    MCASP_Transaction rxLoopjobMismatch1 = { .buf = rxBuf, .count = origRxLjCnt, .timeout = 0xFFFFFFU };
    status = MCASP_submitRx(handle, &rxLoopjobMismatch1);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "Expected RX loopjob-count failure (initDone==1)");

    /* Restore original loopjob counts and water-levels */
    obj->XmtObj.txnLoopjob.count = origTxLjCnt;
    obj->RcvObj.txnLoopjob.count = origRxLjCnt;
    attrs->txFifoWaterLevel = savedTxWater1;
    attrs->rxFifoWaterLevel = savedRxWater1;

    /* FIFO water-level multiple violation: choose non-divisible levels */
    uint32_t txWater = 3U;
    if ((txLjCnt % txWater) == 0U)
    {
        txWater = 5U;
    }
    if ((txLjCnt % txWater) == 0U)
    {
        txWater = 7U;
    }
    uint32_t rxWater = 3U;
    if ((rxLjCnt % rxWater) == 0U)
    {
        rxWater = 5U;
    }
    if ((rxLjCnt % rxWater) == 0U)
    {
        rxWater = 7U;
    }

    uint32_t savedTxWater = attrs->txFifoWaterLevel;
    uint32_t savedRxWater = attrs->rxFifoWaterLevel;
    attrs->txFifoWaterLevel = txWater;
    attrs->rxFifoWaterLevel = rxWater;

    MCASP_Transaction txWaterBad = { .buf = txBuf, .count = txLjCnt, .timeout = 0xFFFFFFU };
    MCASP_Transaction rxWaterBad = { .buf = rxBuf, .count = rxLjCnt, .timeout = 0xFFFFFFU };
    status = MCASP_submitTx(handle, &txWaterBad);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "Expected TX fifo water-level failure");
    status = MCASP_submitRx(handle, &rxWaterBad);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "Expected RX fifo water-level failure");

    /* Restore and close */
    attrs->txFifoWaterLevel = savedTxWater;
    attrs->rxFifoWaterLevel = savedRxWater;
    handle =  MCASP_getHandle(CONFIG_MCASP0);
    MCASP_close(handle);
}

 /**
 * \brief initDone==0 with FIFO disabled requires count == loopjob.count.
 *
 * This test opens MCASP, disables TX/RX FIFO (waterLevel=0), and forces txDmaIcnt.initDone/rxDmaIcnt.initDone == 0.
 * It then submits TX/RX transactions with count = loopjob.count + 1 (words) to validate that the driver
 * rejects non-matching counts when initDone != MCASP_TXN_COUNT_OVERRIDE in the FIFO-disabled path.
 * TX submit path when initDone == 0 and FIFO disabled: count must equal object->XmtObj.txnLoopjob.count.
 * RX submit path when initDone == 0 and FIFO disabled: count must equal object->RcvObj.txnLoopjob.count.
 *
 * Test case category: negative test case
 */
static void TestMcasp_dmaInitDoneZeroFifoDisabledLoopjobMismatch(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status;
    MCASP_Handle handle;
    MCASP_Config *cfgH;
    MCASP_Object *obj;
    MCASP_Attrs  *attrs;

    handle =  MCASP_getHandle(CONFIG_MCASP0);
    if(handle != NULL)
    {
        MCASP_close(handle);
        handle = NULL;
    }

    /* Negative: initDone == 0 and waterLevel == 0 (fifo disabled) -> count must equal loopjob.count (words) */
    handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "MCASP_open failed (negative: loopjob count check)");

    cfgH   = (MCASP_Config*)handle;
    obj    = cfgH->object;
    attrs  = (MCASP_Attrs *)cfgH->attrs;

    /* Force fifo disabled (waterLevel=0 path) and initDone==0 */
    attrs->txFifoWaterLevel = 0U;
    attrs->rxFifoWaterLevel = 0U;
    obj->txDmaIcnt.initDone = 0U;
    obj->rxDmaIcnt.initDone = 0U;

    /* Make loopjob.count known */
    uint32_t ljTxWords = obj->XmtObj.txnLoopjob.count;
    uint32_t ljRxWords = obj->RcvObj.txnLoopjob.count;
    TEST_ASSERT_TRUE_MESSAGE(ljTxWords > 0U, "Loopjob TX must be > 0");
    TEST_ASSERT_TRUE_MESSAGE(ljRxWords > 0U, "Loopjob RX must be > 0");

    /* Case: mismatch to loopjob.count (should fail when initDone != MCASP_TXN_COUNT_OVERRIDE) */
    MCASP_Transaction txMismatchInit0 = { .buf = TestMcasp_txBuffer[0], .count = ljTxWords + 1U, .timeout = 0xFFFFFFU };
    status = MCASP_submitTx(handle, &txMismatchInit0);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "Expected TX failure: count != loopjob.count (initDone=0, FIFO disabled)");

    MCASP_Transaction rxMismatchInit0 = { .buf = TestMcasp_rxBuffer[0], .count = ljRxWords + 1U, .timeout = 0xFFFFFFU };
    status = MCASP_submitRx(handle, &rxMismatchInit0);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "Expected RX failure: count != loopjob.count (initDone=0, FIFO disabled)");

    MCASP_close(handle);
}

/**
 * \brief FIFO water-level multiple rule with initDone==0 (TX/RX).
 *
 * Opens MCASP, enables TX/RX FIFO with water levels >1 while keeping txDmaIcnt/rxDmaIcnt.initDone == 0.
 * Submits TX/RX counts that are NOT multiples of WORD_BYTE_COUNT * waterLevel to validate failure.
 * Then adjusts water levels to divide loopjob counts and validates success when multiples are satisfied.
 *
 * Test case category: negative test case
 */
static void TestMcasp_dmaFifoWaterLevelMultipleInitDoneZero(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status;
    MCASP_Handle handle;
    MCASP_Config *cfgH;
    MCASP_Object *obj;
    MCASP_Attrs  *attrs;
    uint32_t ljTxWords, ljRxWords;

    handle =  MCASP_getHandle(CONFIG_MCASP0);
    if(handle != NULL)
    {
        MCASP_close(handle);
        handle = NULL;
    }
    /* Negative: waterLevel multiple check when fifo enabled (waterLevel>1) */
    handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    cfgH   = (MCASP_Config*)handle;
    obj    = cfgH->object;
    attrs  = (MCASP_Attrs *)cfgH->attrs;

    /* Enable fifo and set non-trivial waterLevels */
    attrs->txFifoWaterLevel = 5U;  /* arbitrary >1 */
    attrs->rxFifoWaterLevel = 7U;  /* arbitrary >1 */
    obj->txDmaIcnt.initDone = 0U;
    obj->rxDmaIcnt.initDone = 0U;

    ljTxWords = obj->XmtObj.txnLoopjob.count;
    ljRxWords = obj->RcvObj.txnLoopjob.count;
    TEST_ASSERT_TRUE(ljTxWords > 0U);
    TEST_ASSERT_TRUE(ljRxWords > 0U);

    /* Choose counts that are NOT multiples of WORD_BYTE_COUNT*waterLevel */
    /* Count in words; byteCnt = count*4. Multiplicity check is on bytes. */
    uint32_t badTxWords = ljTxWords + 1U;
    uint32_t badRxWords = ljRxWords + 1U;

    /* Should fail due to water-level multiple rule (initDone==0 path) */
    MCASP_Transaction txBadWater = { .buf = TestMcasp_txBuffer[0], .count = badTxWords, .timeout = 0xFFFFFFU };
    status = MCASP_submitTx(handle, &txBadWater);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "Expected TX failure: count not multiple of fifo water level");

    MCASP_Transaction rxBadWater = { .buf = TestMcasp_rxBuffer[0], .count = badRxWords, .timeout = 0xFFFFFFU };
    status = MCASP_submitRx(handle, &rxBadWater);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "Expected RX failure: count not multiple of fifo water level");

    /* Positive control: valid multiples should pass */
    uint32_t goodTxWords = ljTxWords;
    uint32_t goodRxWords = ljRxWords;

    /* Pick water levels >1 that divide the loopjob counts (in words) */
    uint32_t goodTxWater = 2U;
    while (goodTxWater <= 32U && (goodTxWords % goodTxWater) != 0U)
    {
        goodTxWater++;
    }
    attrs->txFifoWaterLevel = (goodTxWater <= 32U) ? goodTxWater : 2U;

    uint32_t goodRxWater = 2U;
    while (goodRxWater <= 32U && (goodRxWords % goodRxWater) != 0U)
    {
        goodRxWater++;
    }
    attrs->rxFifoWaterLevel = (goodRxWater <= 32U) ? goodRxWater : 2U;

    MCASP_Transaction txGoodWater = { .buf = TestMcasp_txBuffer[0], .count = goodTxWords, .timeout = 0xFFFFFFU };
    status = MCASP_submitTx(handle, &txGoodWater);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "TX should pass: count multiple of fifo water level");

    MCASP_Transaction rxGoodWater = { .buf = TestMcasp_rxBuffer[0], .count = goodRxWords, .timeout = 0xFFFFFFU };
    status = MCASP_submitRx(handle, &rxGoodWater);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "RX should pass: count multiple of fifo water level");

    MCASP_close(handle);
}

/**
 * \brief Negative test: RX count equals loopjob.count but fails FIFO water-level multiple rule (initDone==0).
 *
 * This test opens MCASP, keeps rxDmaIcnt.initDone == 0, enables RX FIFO with a water level (>1)
 * that does not divide the RX loopjob count in words, and submits an RX transaction with
 * count == loopjob.count. It validates failure due to:
 * byteCnt % (WORD_BYTE_COUNT * rxFifoWaterLevel) != 0.
 *
 * Test case category: negative test case
 */
static void TestMcasp_dmaInitDoneZeroRxWaterLevelMultipleFail(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status;
    MCASP_Handle handle;
    MCASP_Config *cfgH;
    MCASP_Object *obj;
    MCASP_Attrs  *attrs;
    uint32_t ljRxWords;

    handle =  MCASP_getHandle(CONFIG_MCASP0);
    if(handle != NULL)
    {
        MCASP_close(handle);
        handle = NULL;
    }

    /* Fresh open */
    handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    cfgH  = (MCASP_Config*)handle;
    obj   = cfgH->object;
    attrs = (MCASP_Attrs *)cfgH->attrs;

    /* Enable RX FIFO with a water level that does not divide ljRxWords; keep initDone == 0 */
    obj->rxDmaIcnt.initDone = 0U;
    attrs->rxFifoWaterLevel = 3U; /* pick >1 */
    ljRxWords = obj->RcvObj.txnLoopjob.count;
    TEST_ASSERT_TRUE_MESSAGE(ljRxWords > 0U, "Loopjob RX must be > 0");

    /* Ensure non-divisible water level */
    if ((ljRxWords % attrs->rxFifoWaterLevel) == 0U)
    {
        attrs->rxFifoWaterLevel = 7U;
    }

    /* Submit RX with count == loopjob.count -> fails water-level multiple check */
    static uint32_t rxBufWaterFail[2048] __attribute__((aligned(64)));
    MCASP_Transaction rxWaterMultipleFail = { .buf = rxBufWaterFail, .count = ljRxWords, .timeout = 0xFFFFFFU };
    status = MCASP_submitRx(handle, &rxWaterMultipleFail);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status,
        "Expected RX failure: count not multiple of fifo water level (initDone=0)");

    MCASP_close(handle);
}

/**
 * \brief Negative test: RX transaction count mismatch with initDone==0 and FIFO disabled.
 *
 * Opens MCASP in DMA mode, forces rxDmaIcnt.initDone == 0 and disables the RX FIFO
 * (rxFifoWaterLevel = 0). Submits an RX transaction whose count (loopjob.count + 1)
 * intentionally differs from the loopjob word count to triggers mismatch
 *
 * Test case category: negative test case
 */
static void TestMcasp_dmaInitDoneZeroRxMismatch(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status;
    MCASP_Handle handle;

    handle =  MCASP_getHandle(CONFIG_MCASP0);
    if(handle != NULL)
    {
        MCASP_close(handle);
        handle = NULL;
    }
    /* Fresh open */
    handle = MCASP_open(CONFIG_MCASP0, openParams);
    TEST_ASSERT_NOT_NULL(handle);

    MCASP_Config *cfgH = (MCASP_Config*)handle;
    MCASP_Object *obj   = cfgH->object;
    MCASP_Attrs  *attrs = (MCASP_Attrs *)cfgH->attrs;

    /* Disable RX FIFO and ensure initDone == 0 so the path is taken */
    attrs->rxFifoWaterLevel = 0U;
    obj->rxDmaIcnt.initDone = 0U;

    /* Use current loopjob count to derive mismatch */
    uint32_t ljRxWords = obj->RcvObj.txnLoopjob.count;
    TEST_ASSERT_TRUE_MESSAGE(ljRxWords > 0U, "Loopjob RX count must be > 0");

    /* Submit RX with mismatched count (ljRxWords + 1) to trigger failure branch */
    static uint32_t rxBuf[2048] __attribute__((aligned(64)));
    MCASP_Transaction rxMismatchInit0 = { .buf = rxBuf, .count = ljRxWords + 1U, .timeout = 0xFFFFFFU };

    status = MCASP_submitRx(handle, &rxMismatchInit0);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status,
        "Expected RX failure: count != loopjob.count (initDone=0, fifo disabled)");

    MCASP_close(handle);
}

#if ((defined(C75_CORE) && !defined(SOC_AM62DX)) || defined(SOC_AM62AX))
/**
 * \brief  Test MCASP interrupt mode with NULL loopjob buffers.
 *
 * This test verifies that the MCASP driver returns failure when starting transfers
 * in interrupt mode with both loopjob disabled and no user buffers queued.
 * It ensures the driver does not proceed without valid buffers and handles this
 * negative scenario gracefully.
 * Test case category: negative test case
 */
static void TestMcasp_interruptNullLoopjob(void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t i,j;

    openParams->txLoopjobEnable = FALSE;
    openParams->rxLoopjobEnable = FALSE;
    openParams->rxLoopjobBuf = NULL;
    openParams->txLoopjobBuf = NULL;

    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = j % 256;
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }

    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_startTransferTx should fail with no buffer and no loopjob");
    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_startTransferRx should fail with no buffer and no loopjob");

    openParams->txLoopjobEnable = TRUE;
    openParams->rxLoopjobEnable = TRUE;
    openParams->txLoopjobBuf = gTxLoopjobBuf0;
    openParams->rxLoopjobBuf = gRxLoopjobBuf0;

    MCASP_close(handle);

}
#endif
/**
 * \brief  Test MCASP buffer withdraw after queuing.
 *
 * This test verifies that MCASP_withdrawTx and MCASP_withdrawRx correctly
 * withdraw all queued buffers after submission. It submits multiple TX and RX
 * transactions, withdraws them using the driver API, and checks that the queues
 * are empty after withdrawal. This ensures proper buffer management and driver
 * behavior for queued transactions.
 * Test case category: negative test case
 */
static void TestMcasp_withdrawQueuedBuff(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i, j;
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instanceId = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Transaction *txn = NULL;

    MCASP_close(gMcaspHandle[instanceId]);
    gMcaspHandle[instanceId] = NULL;

    openParams->txLoopjobBuf = gTxLoopjobBuf0;
    openParams->rxLoopjobBuf = gRxLoopjobBuf0;

    MCASP_Handle handle = MCASP_open(instanceId, openParams);

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = j % 256;
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }

    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i] = 0xa5;
        gRxLoopjobBuf0[i] = 0;
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*) &TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE / 4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_txnRx[i]);
    }

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*) &TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE / 4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_txnTx[i]);
    }

    if (status == SystemP_SUCCESS)
    {
        do
        {
            txn = MCASP_withdrawRx(handle);
        } while (txn != NULL);
        do
        {
            txn = MCASP_withdrawTx(handle);
        } while (txn != NULL);
    }
    TEST_ASSERT_NULL_MESSAGE(txn, "RX queue not empty after drain");
    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    MCASP_close(handle);

}

/**
 * \brief  Test MCASP DMA channel reset.
 *
 * This test verifies the MCASP driver's ability to reset DMA channels and recover from teardown scenarios.
 * It closes any open MCASP handle, reopens the instance, initializes loopjob buffers, and fills TX/RX buffers with test patterns.
 * Transactions are submitted for both TX and RX, transfers are started, and the driver is closed without explicitly stopping the transfer,
 * forcing a DMA teardown. The test checks that the driver handles this sequence correctly and does not leave the DMA in an inconsistent state.
 * Test case category: negative/teardown test case
 */
static void TestMcasp_dmaChannelReset(void *args)
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

    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;
    /* Memfill buffers */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for(j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = j % 256;
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }

    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    for (i = 0; i < TEST_MCASP_APP_MSGSIZE; i++)
    {
        gTxLoopjobBuf0[i] = 0xa5;
        gRxLoopjobBuf0[i] = 0;
    }

    CacheP_wb(gTxLoopjobBuf0, 256, CacheP_TYPE_ALL);
    CacheP_wb(gRxLoopjobBuf0, 256, CacheP_TYPE_ALL);

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*) &TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(McaspHandle,  &TestMcasp_txnRx[i]);
    }

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*) &TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(McaspHandle, &TestMcasp_txnTx[i]);
    }


    status = MCASP_startTransferRx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(McaspHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* closing without stopping the transfer to force teardown */
    MCASP_close(McaspHandle);
    McaspHandle = NULL;

    /* Give some time for DMA teardown to complete */
    ClockP_usleep(50000); 

    /* Re-open the instance to ensure resources were released */
    MCASP_Handle handle = MCASP_open(instanceId, openParams);
    TEST_ASSERT_NOT_NULL_MESSAGE(handle, "Re-open after forced teardown failed");

    /* Full transaction: submit TEST_MCASP_APP_MSG_COUNT RX/TX transactions and verify transfer */
    TestMcasp_cntRx = 0;
    TestMcasp_cntTx = 0;

    /* reuse buffers already filled above; ensure cache is written */
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    /* Submit multiple RX transactions */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnRx[i].buf = (void*)&TestMcasp_rxBuffer[i][0];
        TestMcasp_txnRx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnRx[i].timeout = 0xFFFFFF;
        status = MCASP_submitRx(handle, &TestMcasp_txnRx[i]);
        TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "submitRx failed after reopen (multi)");
    }

    /* Submit multiple TX transactions */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_txnTx[i].buf = (void*)&TestMcasp_txBuffer[i][0];
        TestMcasp_txnTx[i].count = TEST_MCASP_APP_MSGSIZE/4;
        TestMcasp_txnTx[i].timeout = 0xFFFFFF;
        status = MCASP_submitTx(handle, &TestMcasp_txnTx[i]);
        TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "submitTx failed after reopen (multi)");
    }

    status = MCASP_startTransferRx(handle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "startTransferRx failed after reopen");
    status = MCASP_startTransferTx(handle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "startTransferTx failed after reopen");

    /* Wait for completion with timeout */
    uint32_t timeout = 10000;
    while (((TestMcasp_cntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_cntTx < TEST_MCASP_APP_TEST_COUNT)) && (timeout > 0))
    {
        ClockP_usleep(1000);
        timeout--;
    }
    if (timeout == 0)
    {
        status = SystemP_FAILURE;
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    /* Withdraw any queued transactions */
    MCASP_Transaction *transaction;
    do {
        transaction = MCASP_withdrawRx(handle);
    } while (transaction != NULL);
    do {
        transaction = MCASP_withdrawTx(handle);
    } while (transaction != NULL);

    /* Validate data for DMA mode */
    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        CacheP_inv(TestMcasp_rxBuffer, TEST_MCASP_APP_MSGSIZE * TEST_MCASP_APP_MSG_COUNT, CacheP_TYPE_ALL);
    }

    if (status == SystemP_SUCCESS)
    {
        /* Compare all messages */
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for (j = 0; j < TEST_MCASP_APP_MSGSIZE; j++)
            {
                if (TestMcasp_txBuffer[i][j] != TestMcasp_rxBuffer[i][j])
                {
                    status = SystemP_FAILURE;
                    break;
                }
            }
            if (status != SystemP_SUCCESS)
            {
                break;
            }
        }
    }

    MCASP_close(handle);

    /* Final assertion: test should pass if re-open and full loopback succeeded */
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "DMA channel reset recovery test failed");

    return;

}

/**
 * \brief  Test MCASP handling of invalid buffer format values.
 *
 * Injects unsupported tx/rx buffer format values, attempts to open the MCASP
 * instance and, if opened, submits minimal TX/RX transactions. Expected:
 * - MCASP_submitTx/MCASP_submitRx return SystemP_FAILURE.
 * Restores safe defaults and closes the handle.
 * Test case category: negative test case
 */
static void TestMcasp_invalidBufferFormat(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    MCASP_Handle handle;
    int32_t status;
    uint32_t i, j;
    uint8_t invalidTXBuffFormat = 10U;
    uint8_t invalidRXBuffFormat = 10U;

    /* Ensure fresh open */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;

    /* Intentionally set invalid buffer formats */
    openParams->txBufferFormat = invalidTXBuffFormat;
    openParams->rxBufferFormat = invalidRXBuffFormat;

    handle = MCASP_open(CONFIG_MCASP0, openParams);
    if (handle == NULL)
    {
        return;
    }

    /* Prepare minimal buffers/transactions for submit */
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        for (j = 0U; j < TEST_MCASP_APP_MSGSIZE; j++)
        {
            TestMcasp_txBuffer[i][j] = (uint8_t)(j & 0xFF);
            TestMcasp_rxBuffer[i][j] = 0U;
        }
    }
    CacheP_wb(TestMcasp_txBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);
    CacheP_wb(TestMcasp_rxBuffer, TEST_MCASP_APP_MSG_COUNT * TEST_MCASP_APP_MSGSIZE, CacheP_TYPE_ALL);

    /* Build one txn each */
    TestMcasp_txnRx[0].buf = (void*)&TestMcasp_rxBuffer[0][0];
    TestMcasp_txnRx[0].count = TEST_MCASP_APP_MSGSIZE/4;
    TestMcasp_txnRx[0].timeout = 0xFFFFFFU;

    TestMcasp_txnTx[0].buf = (void*)&TestMcasp_txBuffer[0][0];
    TestMcasp_txnTx[0].count = TEST_MCASP_APP_MSGSIZE/4;
    TestMcasp_txnTx[0].timeout = 0xFFFFFFU;

    /* Submits should fail for invalid buffer formats */
    status = MCASP_submitRx(handle, &TestMcasp_txnRx[0]);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_submitRx should fail for invalid buffer format");

    status = MCASP_submitTx(handle, &TestMcasp_txnTx[0]);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_FAILURE, status, "MCASP_submitTx should fail for invalid buffer format");

    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;

    /* Clean up */
    MCASP_close(handle);
}

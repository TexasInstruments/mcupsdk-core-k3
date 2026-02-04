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

#include "drivers/mcasp.h"
#include <drivers/pinmux.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/CacheP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <string.h>
#include <unity.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_MCASP_APP_MSGSIZE_1         (1280U * 100U)
#define TEST_MCASP_APP_MSGSIZE_2         (TEST_MCASP_APP_MSGSIZE_1 / 2U)
#define TEST_MCASP_APP_MSGSIZE_3         (TEST_MCASP_APP_MSGSIZE_1 / 10U)
#define TEST_MCASP_APP_MSGSIZE_4         (TEST_MCASP_APP_MSGSIZE_1 / 100U)
#define TEST_MCASP_APP_MSG_COUNT         (2U)
#define TEST_MCASP_APP_TEST_COUNT        (2U)
#define TEST_MCASP_APP_NUM_TESTS         (4U)   /* Change this value as per gtestSizes list size */

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

MCASP_Handle McaspHandle;

extern uint8_t gTxLoopjobBuf0[];
extern uint8_t gRxLoopjobBuf0[];
extern MCASP_Config gMcaspConfig[];
extern MCASP_OpenParams gMcaspOpenParams[];
extern MCASP_Handle gMcaspHandle[];

static uint8_t TestMcasp_TxBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE_1]__attribute__ ((aligned (256U)));
static uint8_t TestMcasp_RxBuffer[TEST_MCASP_APP_MSG_COUNT][TEST_MCASP_APP_MSGSIZE_1]__attribute__ ((aligned (256U)));

volatile uint32_t TestMcasp_CntRx = 0U;
volatile uint32_t TestMcasp_CntTx = 0U;

MCASP_Transaction TestMcasp_TxnTx[TEST_MCASP_APP_MSG_COUNT] = {0};
MCASP_Transaction TestMcasp_TxnRx[TEST_MCASP_APP_MSG_COUNT] = {0};

/* MCASP Txn Configuration Structure */
typedef struct {
    uint32_t slotCount;      /* Number of slots */
    uint32_t serCount;       /* Number of serializers */
    uint32_t bufferFormat;   /* Buffer format type */
    uint32_t slotSize;       /* Slot size in bits */
    uint32_t frameCount;     /* Number of frames */
    uint32_t msgSize;        /* Message size in bytes */
} Test_Mcasp_TxnConfig;

Test_Mcasp_TxnConfig config;

uint8_t gTestPassCount = 0;

uint32_t gtestSizes[TEST_MCASP_APP_NUM_TESTS] = {TEST_MCASP_APP_MSGSIZE_1,\
        TEST_MCASP_APP_MSGSIZE_2, TEST_MCASP_APP_MSGSIZE_3, TEST_MCASP_APP_MSGSIZE_4};
/* ========================================================================== */
/*                  Function Declarations                                     */
/* ========================================================================== */

static void Test_Mcasp_loopbackInterleavedToNonInterleaved_wrapper(void *args);
static void Test_Mcasp_loopbackNonInterleavedToInterleaved_wrapper(void *args);
static void Test_Mcasp_loopbacksemiInterleaved1ToSemiInterleaved2_wrapper(void *args);
static void Test_Mcasp_loopbacksemiInterleaved2ToSemiInterleaved1_wrapper(void *args);
static void Test_Mcasp_loopbacksemiInterleaved1ToNonInterleaved_wrapper(void *args);
static void Test_Mcasp_loopbacksemiInterleaved2ToNonInterleaved_wrapper(void *args);
static void Test_Mcasp_loopbackNonInterleavedToSemiInterleaved1_wrapper(void *args);
static void Test_Mcasp_loopbackNonInterleavedToSemiInterleaved2_wrapper(void *args);
static void Test_Mcasp_invalidTxBufferFormat(void *args);
static void Test_Mcasp_invalidRxBufferFormat(void *args);
#if defined(SOC_AM275X)
static void Test_Mcasp_transactionCountBoundsCheck(void *args);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(Test_Mcasp_loopbackInterleavedToNonInterleaved_wrapper, 10192, NULL);
    RUN_TEST(Test_Mcasp_loopbackNonInterleavedToInterleaved_wrapper, 10198, NULL);
    RUN_TEST(Test_Mcasp_loopbacksemiInterleaved1ToSemiInterleaved2_wrapper, 10199, NULL);
    RUN_TEST(Test_Mcasp_loopbacksemiInterleaved2ToSemiInterleaved1_wrapper, 10200, NULL);
    RUN_TEST(Test_Mcasp_loopbacksemiInterleaved1ToNonInterleaved_wrapper, 10201, NULL);
    RUN_TEST(Test_Mcasp_loopbacksemiInterleaved2ToNonInterleaved_wrapper, 10202, NULL);
    RUN_TEST(Test_Mcasp_loopbackNonInterleavedToSemiInterleaved1_wrapper, 10203, NULL);
    RUN_TEST(Test_Mcasp_loopbackNonInterleavedToSemiInterleaved2_wrapper, 10204, NULL);
#if defined(SOC_AM275X)
    RUN_TEST(Test_Mcasp_transactionCountBoundsCheck, 10343, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
#endif
    RUN_TEST(Test_Mcasp_invalidRxBufferFormat, 10342, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    RUN_TEST(Test_Mcasp_invalidTxBufferFormat, 10341, (void*)&gMcaspOpenParams[CONFIG_MCASP0]);

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

/* ========================================================================== */
/*                        Static Function Declaration                         */
/* ========================================================================== */

/**
 * \brief Initialize MCASP buffer according to the specified buffer format
 *
 * This function initializes source and destination buffers based on the MCASP buffer format.
 * Different buffer formats organize data differently in memory.
 *
 * \param srcBuf        [OUT] Source buffer to initialize
 * \param destBuf       [OUT] Destination buffer to initialize
 * \param config        [IN] MCASP configuration parameters
 *
 * \return None
 */
static void Test_Mcasp_initBuffers(uint8_t *srcBuf, uint8_t *destBuf, const Test_Mcasp_TxnConfig *config)
{
    uint32_t i, j, k, l, bufferIndex;
    uint32_t elementSize;
    uint32_t totalElements;
    uint8_t baseValue;

    /* Calculate element size in bytes */
    elementSize = (config->slotSize / 8U) + (((config->slotSize % 8U) == 0U) ? 0U : 1U);
    totalElements = config->slotCount * config->serCount * config->frameCount;

    /* Initialize destination buffer with known pattern */
    for(i = 0U; i < totalElements * elementSize; i++)
    {
        destBuf[i] = 0xA5U;
    }

    /* Initialize source buffer based on buffer format */
    switch(config->bufferFormat)
    {
        case MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED:
        {
            /* Interleaved: [slot0][slot1]...[slotN] per frame */
            bufferIndex = 0U;
            for(i = 0U; i < config->frameCount; i++)
            {
                for(j = 0U; j < config->slotCount; j++)
                {
                    baseValue = (uint8_t)(0x10U + j);  /* Different value per slot */
                    for(k = 0U; k < elementSize; k++)
                    {
                        srcBuf[bufferIndex++] = baseValue;
                    }
                }
            }
            break;
        }

        case MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_NON_INTERLEAVED:
        {
            /* Non-interleaved: [slot0_frame0][slot0_frame1]...[slot1_frame0]... */
            bufferIndex = 0U;
            for(i = 0U; i < config->frameCount; i++)
            {
                baseValue = (uint8_t)(0x20U);  /* Different value per slot */
                for(j = 0U; j < config->slotCount; j++)
                {
                    for(k = 0U; k < elementSize; k++)
                    {
                        srcBuf[bufferIndex++] = baseValue + (uint8_t)(j & 0xFFU);
                    }
                    if( j + 1U < config->slotCount)
                    {
                        bufferIndex -= elementSize;
                    }
                    bufferIndex = (bufferIndex + (config->frameCount * elementSize)) % ( config->slotCount * config->frameCount * elementSize);
                }
            }
            break;
        }

        case MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1:
        {
            /* Semi-interleaved type 1: [ser0_slot0][ser1_slot0]...[ser0_slot1]... */
            bufferIndex = 0U;
            for(i = 0U; i < config->frameCount; i++)
            {
                for(j = 0U; j < config->slotCount; j++)
                {
                    for(k = 0U; k < config->serCount; k++)
                    {
                        baseValue = (uint8_t)(0x40U + ((k * config->slotCount) + (j * 0x10U)));
                        for(l = 0U; l < elementSize; l++)
                        {
                            srcBuf[bufferIndex++] = baseValue;
                        }
                    }
                }
            }
            break;
        }

        case MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2:
        {
            /* Semi-interleaved type 2: organized by serializer groups */
            bufferIndex = 0U;
            for(i = 0U; i < config->frameCount; i++)
            {
                for(k = 0U; k < config->serCount; k++)
                {
                    for(j = 0U; j < config->slotCount; j++)
                    {
                        baseValue = (uint8_t)(0x40U + ((k * config->slotCount) + (j * 0x10U)));
                        for(l = 0U; l < elementSize; l++)
                        {
                            srcBuf[bufferIndex++] = baseValue;
                        }
                    }
                    if( k + 1U < config->serCount)
                    {
                        bufferIndex -= config->slotCount * elementSize;
                    }
                    bufferIndex = (bufferIndex + (config->frameCount * config->slotCount * elementSize)) % ( config->serCount * config->slotCount * config->frameCount * elementSize);
                }
            }
            break;
        }
        case MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_NON_INTERLEAVED:
        {
            /* Semi-interleaved type 2: organized by serializer groups */
            bufferIndex = 0U;
            for(i = 0U; i < config->frameCount; i++)
            {
                for(j = 0U; j < config->slotCount; j++)
                {
                    for(k = 0U; k < config->serCount; k++)
                    {
                        baseValue = (uint8_t)(0x40U + ((k * config->slotCount) + (j * 0x10U)));
                        for(l = 0U; l < elementSize; l++)
                        {
                            srcBuf[bufferIndex++] = baseValue;
                        }
                        if( k + 1U < config->serCount)
                        {
                            bufferIndex -= elementSize;
                        }
                        bufferIndex = (bufferIndex + (config->frameCount * elementSize))\
                                       % ( config->serCount * config->slotCount * config->frameCount * elementSize);
                    }
                    if( j + 1U < config->slotCount)
                    {
                        bufferIndex -= elementSize;
                    }
                }
            }
            break;
        }

        default:
        {
            /* Default initialization for unknown formats */
            for(i = 0U; i < totalElements * elementSize; i++)
            {
                srcBuf[i] = (uint8_t)(0x50U + (i & 0xFFU));
            }
            break;
        }
    }

    /* Writeback source and destination buffers */
    CacheP_wb(srcBuf, totalElements * elementSize, CacheP_TYPE_ALLD);
    CacheP_wb(destBuf, totalElements * elementSize, CacheP_TYPE_ALLD);
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
static void Test_Mcasp_loopbackInterleavedToNonInterleaved(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, slot, sample, b;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8U;
    const uint32_t numSamples = config.msgSize / (numSlots * slotSize);

    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_NON_INTERLEAVED;
    
    openParams->txLoopjobBufLength = config.msgSize/4;
    openParams->rxLoopjobBufLength = config.msgSize/4;

    config.bufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    config.frameCount = numSamples;
    config.slotCount = numSlots;
    config.serCount = 1;
    config.slotSize = attrs->txSlotSize;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        Test_Mcasp_initBuffers(&TestMcasp_TxBuffer[i][0], &TestMcasp_RxBuffer[i][0], &config);
    }

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*)&TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = config.msgSize/4U;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_TxnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*)&TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = config.msgSize/4U;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_TxnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);

    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            CacheP_inv(TestMcasp_RxBuffer[i], config.msgSize, CacheP_TYPE_ALL);
        }
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for (slot = 0; slot < numSlots; slot++)
            {
                for (sample = 0; sample < numSamples; sample++)
                {
                    uint32_t tx_offset = ((sample * numSlots) + slot) * slotSize;
                    uint32_t rx_offset = ((slot * numSamples) + sample) * slotSize;
                    for (b = 0; b < slotSize; b++)
                    {
                        if (TestMcasp_TxBuffer[i][tx_offset + b] != TestMcasp_RxBuffer[i][rx_offset + b])
                        {
                            status = SystemP_FAILURE;
                        }
                    }
                }
            }
        }
    }

    MCASP_close(handle);
    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All bytes match!!\r\n");
        gTestPassCount++;
    }
    else
    {
        DebugP_log("Data mismatch\r\n");
    }
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
static void Test_Mcasp_loopbackNonInterleavedToInterleaved(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, slot, sample, b;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8U;
    const uint32_t numSamples = config.msgSize / (numSlots * slotSize);

    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_NON_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;

    openParams->txLoopjobBufLength = config.msgSize/4;
    openParams->rxLoopjobBufLength = config.msgSize/4;

    config.bufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_NON_INTERLEAVED;
    config.frameCount = numSamples;
    config.slotCount = numSlots;
    config.serCount = 1;
    config.slotSize = attrs->txSlotSize;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        Test_Mcasp_initBuffers(&TestMcasp_TxBuffer[i][0], &TestMcasp_RxBuffer[i][0], &config);
    }

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*)&TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = config.msgSize/4U;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_TxnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*)&TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = config.msgSize/4U;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_TxnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);

    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            CacheP_inv(TestMcasp_RxBuffer[i], config.msgSize, CacheP_TYPE_ALL);
        }
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            for (sample = 0; sample < numSamples; sample++)
            {
                for (slot = 0; slot < numSlots; slot++)
                {
                    uint32_t tx_offset = ((slot * numSamples) + sample) * slotSize;
                    uint32_t rx_offset = ((sample * numSlots) + slot) * slotSize;
                    for (b = 0; b < slotSize; b++)
                    {
                        if (TestMcasp_TxBuffer[i][tx_offset + b] != TestMcasp_RxBuffer[i][rx_offset + b])
                        {
                            status = SystemP_FAILURE;
                        }
                    }
                }
            }
        }
    }

    MCASP_close(handle);
    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All bytes match!!\r\n");
        gTestPassCount++;
    }
    else
    {
        DebugP_log("Data mismatch\r\n");
    }
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
static void Test_Mcasp_loopbacksemiInterleaved1ToSemiInterleaved2(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, ser, slot, sample, b;
    const uint32_t numSerializers = 2;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8U;
    const uint32_t numSamples = config.msgSize / (numSerializers * numSlots * slotSize);

    /* Use different serializers for TX and RX to avoid conflicts */
    /* Configure TX serializers for semi-interleaved-1 */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000005;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Configure serializer 0 as TX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x1;  /* Configure serializer 2 as TX */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0TxSersUsed[2] = {0,2};  /* Use serializers 0,2 for TX */
    openParams->txSerUsedCount = 2;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;

    /* Configure RX serializers for semi-interleaved-2 */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Configure serializer 1 as RX */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x2;  /* Configure serializer 3 as RX */
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0RxSersUsed[2] = {1,3};  /* Use serializers 1,3 for RX */
    gMcaspOpenParams[0].rxSerUsedCount = 2;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinEnable[] =
    {
        {PIN_MCASP0_AXR0,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR1,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif

    /* Set buffer formats */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2;

    openParams->txLoopjobBufLength = config.msgSize/4;
    openParams->rxLoopjobBufLength = config.msgSize/4;

    config.bufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1;
    config.frameCount = numSamples;
    config.slotCount = numSlots;
    config.serCount = numSerializers;
    config.slotSize = attrs->txSlotSize;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        Test_Mcasp_initBuffers(&TestMcasp_TxBuffer[i][0], &TestMcasp_RxBuffer[i][0], &config);
    }

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*)&TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = config.msgSize/4U;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_TxnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*)&TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = config.msgSize/4U;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_TxnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);

    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            CacheP_inv(TestMcasp_RxBuffer[i], config.msgSize, CacheP_TYPE_ALL);
        }
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            /* For semi-interleaved-1 to semi-interleaved-2 conversion:
             * TX (semi-interleaved-1): [ser0_slot0][ser1_slot0][ser0_slot1][ser1_slot1]...
             * RX (semi-interleaved-2): Different DMA organization pattern
             * Since we're using different serializers, we expect the data to be organized differently */
            for (sample = 0; sample < numSamples; sample++)
            {
                for (slot = 0; slot < numSlots; slot++)
                {
                    for (ser = 0; ser < numSerializers; ser++)
                    {
                        /* TX semi-interleaved-1: frame -> slot -> serializer */
                        uint32_t tx_offset = ((sample * numSlots * numSerializers) + (slot * numSerializers) + ser) * slotSize;
                        /* RX semi-interleaved-2: different organization - serializer -> frame -> slot */
                        uint32_t rx_offset = ((ser * numSamples * numSlots) + (sample * numSlots) + slot) * slotSize;

                        for (b = 0; b < slotSize; b++)
                        {
                            if (TestMcasp_TxBuffer[i][tx_offset + b] != TestMcasp_RxBuffer[i][rx_offset + b])
                            {
                                status = SystemP_FAILURE;
                            }
                        }
                    }
                }
            }
        }
    }

    /* Restore original configuration */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000001;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Reset serializer 0 to TX */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Reset serializer 1 to RX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x0;  /* Reset serializer 2 */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x0;  /* Reset serializer 3 */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    gMcasp0TxSersUsed[0] = 0;  /* Reset to use serializer 0 for TX */
    gMcasp0TxSersUsed[1] = 0;  /* Clear second element */
    openParams->txSerUsedCount = 1;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;
    gMcasp0RxSersUsed[0] = 1;  /* Reset to use serializer 1 for RX */
    gMcasp0RxSersUsed[1] = 1;  /* Clear second element */
    gMcaspOpenParams[0].rxSerUsedCount = 1;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinDisable[] =
    {
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinDisable, PINMUX_DOMAIN_ID_MAIN);
#endif

    MCASP_close(handle);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All bytes match!!\r\n");
        gTestPassCount++;
    }
    else
    {
        DebugP_log("Data mismatch\r\n");
    }
}

/**
 * \brief  Test MCASP semi-interleaved-2 to semi-interleaved-1 loopback.
 *
 * This test verifies MCASP data integrity when transmitting in semi-interleaved-2 format
 * and receiving in semi-interleaved-1 format. It configures the serializers and buffer formats,
 * performs a loopback transfer, and checks that the received data matches the transmitted data
 * after appropriate reordering for the buffer formats.
 * Test case category: functionality test case
 */
static void Test_Mcasp_loopbacksemiInterleaved2ToSemiInterleaved1(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, ser, slot, sample, b;
    const uint32_t numSerializers = 2;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8U;
    const uint32_t numSamples = config.msgSize / (numSerializers * numSlots * slotSize);

    /* Use different serializers for TX and RX to avoid conflicts */
    /* Configure TX serializers for semi-interleaved-2 */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000005;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Configure serializer 0 as TX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x1;  /* Configure serializer 2 as TX */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0TxSersUsed[2] = {0,2};  /* Use serializers 0,2 for TX */
    openParams->txSerUsedCount = 2;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;

    /* Configure RX serializers for semi-interleaved-1 */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Configure serializer 1 as RX */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x2;  /* Configure serializer 3 as RX */
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0RxSersUsed[2] = {1,3};  /* Use serializers 1,3 for RX */
    gMcaspOpenParams[0].rxSerUsedCount = 2;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinEnable[] =
    {
        {PIN_MCASP0_AXR0,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR1,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif

    /* Set buffer formats - reverse of the previous function */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1;

    openParams->txLoopjobBufLength = config.msgSize/4;
    openParams->rxLoopjobBufLength = config.msgSize/4;

    config.bufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2;
    config.frameCount = numSamples;
    config.slotCount = numSlots;
    config.serCount = numSerializers;
    config.slotSize = attrs->txSlotSize;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        Test_Mcasp_initBuffers(&TestMcasp_TxBuffer[i][0], &TestMcasp_RxBuffer[i][0], &config);
    }

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*)&TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = config.msgSize/4U;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_TxnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*)&TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = config.msgSize/4U;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_TxnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);

    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            CacheP_inv(TestMcasp_RxBuffer[i], config.msgSize, CacheP_TYPE_ALL);
        }
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            /* For semi-interleaved-2 to semi-interleaved-1 conversion:
             * TX (semi-interleaved-2): Different DMA organization pattern - serializer -> frame -> slot
             * RX (semi-interleaved-1): [ser0_slot0][ser1_slot0][ser0_slot1][ser1_slot1]...
             * Since we're using different serializers, we expect the data to be organized differently */
            for (sample = 0; sample < numSamples; sample++)
            {
                for (slot = 0; slot < numSlots; slot++)
                {
                    for (ser = 0; ser < numSerializers; ser++)
                    {
                        /* TX semi-interleaved-2: serializer -> frame -> slot */
                        uint32_t tx_offset = ((ser * numSamples * numSlots) + (sample * numSlots) + slot) * slotSize;
                        /* RX semi-interleaved-1: frame -> slot -> serializer */
                        uint32_t rx_offset = ((sample * numSlots * numSerializers) + (slot * numSerializers) + ser) * slotSize;

                        for (b = 0; b < slotSize; b++)
                        {
                            if (TestMcasp_TxBuffer[i][tx_offset + b] != TestMcasp_RxBuffer[i][rx_offset + b])
                            {
                                status = SystemP_FAILURE;
                            }
                        }
                    }
                }
            }
        }
    }

    /* Restore original configuration */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000001;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Reset serializer 0 to TX */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Reset serializer 1 to RX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x0;  /* Reset serializer 2 */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x0;  /* Reset serializer 3 */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    gMcasp0TxSersUsed[0] = 0;  /* Reset to use serializer 0 for TX */
    gMcasp0TxSersUsed[1] = 0;  /* Clear second element */
    openParams->txSerUsedCount = 1;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;
    gMcasp0RxSersUsed[0] = 1;  /* Reset to use serializer 1 for RX */
    gMcasp0RxSersUsed[1] = 1;  /* Clear second element */
    gMcaspOpenParams[0].rxSerUsedCount = 1;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinDisable[] =
    {
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinDisable, PINMUX_DOMAIN_ID_MAIN);
#endif

    MCASP_close(handle);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All bytes match!!\r\n");
        gTestPassCount++;
    }
    else
    {
        DebugP_log("Data mismatch\r\n");
    }
}

/**
 * \brief  Test MCASP semi-interleaved-1 to non-interleaved loopback.
 *
 * This test verifies MCASP data integrity when transmitting in semi-interleaved-1 format
 * and receiving in non-interleaved format. It configures the serializers and buffer formats,
 * performs a loopback transfer, and checks that the received data matches the transmitted data
 * after appropriate reordering for the buffer formats.
 * Test case category: functionality test case
 */
static void Test_Mcasp_loopbacksemiInterleaved1ToNonInterleaved(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, ser, slot, sample, b;
    const uint32_t numSerializers = 2;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8U;
    const uint32_t numSamples = config.msgSize / (numSerializers * numSlots * slotSize);

    /* Use different serializers for TX and RX to avoid conflicts */
    /* Configure TX serializers for semi-interleaved-1 */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000005;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Configure serializer 0 as TX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x1;  /* Configure serializer 2 as TX */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0TxSersUsed[2] = {0,2};  /* Use serializers 0,2 for TX */
    openParams->txSerUsedCount = 2;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;

    /* Configure RX serializers for multi-serializer non-interleaved */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Configure serializer 1 as RX */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x2;  /* Configure serializer 3 as RX */
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0RxSersUsed[2] = {1,3};  /* Use serializers 1,3 for RX */
    gMcaspOpenParams[0].rxSerUsedCount = 2;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinEnable[] =
    {
        {PIN_MCASP0_AXR0,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR1,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif

    /* Set buffer formats */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_NON_INTERLEAVED;

    openParams->txLoopjobBufLength = config.msgSize/4;
    openParams->rxLoopjobBufLength = config.msgSize/4;

    config.bufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1;
    config.frameCount = numSamples;
    config.slotCount = numSlots;
    config.serCount = numSerializers;
    config.slotSize = attrs->txSlotSize;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        Test_Mcasp_initBuffers(&TestMcasp_TxBuffer[i][0], &TestMcasp_RxBuffer[i][0], &config);
    }

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*)&TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = config.msgSize/4U;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_TxnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*)&TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = config.msgSize/4U;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_TxnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);

    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            CacheP_inv(TestMcasp_RxBuffer[i], config.msgSize, CacheP_TYPE_ALL);
        }
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            /* For semi-interleaved-1 to multi-serializer non-interleaved conversion:
             * TX (semi-interleaved-1): [ser0_slot0][ser1_slot0][ser0_slot1][ser1_slot1]... (frame -> slot -> serializer)
             * RX (multi-serializer non-interleaved): [ser0_slot0_sample0][ser0_slot0_sample1]...[ser0_slot1_sample0]...[ser1_slot0_sample0]... (serializer -> slot -> frame)
             * Need to map from multi-serializer semi-interleaved to multi-serializer non-interleaved */
            for (sample = 0; sample < numSamples; sample++)
            {
                for (slot = 0; slot < numSlots; slot++)
                {
                    for (ser = 0; ser < numSerializers; ser++)
                    {
                        /* TX semi-interleaved-1: frame -> slot -> serializer */
                        uint32_t tx_offset = ((sample * numSlots * numSerializers) + (slot * numSerializers) + ser) * slotSize;
                        /* RX multi-serializer non-interleaved: serializer -> slot -> frame */
                        uint32_t rx_offset = ((((slot * numSerializers) + ser) * numSamples) + sample ) * slotSize;

                        for (b = 0; b < slotSize; b++)
                        {
                            if (TestMcasp_TxBuffer[i][tx_offset + b] != TestMcasp_RxBuffer[i][rx_offset + b])
                            {
                                status = SystemP_FAILURE;
                            }
                        }
                    }
                }
            }
        }
    }

    /* Keep multi-serializer configuration - do not restore to single serializer */

    MCASP_close(handle);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All bytes match!!\r\n");
        gTestPassCount++;
    }
    else
    {
        DebugP_log("Data mismatch\r\n");
    }
}

/**
 * \brief  Test MCASP semi-interleaved-2 to non-interleaved loopback.
 *
 * This test verifies MCASP data integrity when transmitting in semi-interleaved-2 format
 * and receiving in non-interleaved format. It configures the serializers and buffer formats,
 * performs a loopback transfer, and checks that the received data matches the transmitted data
 * after appropriate reordering for the buffer formats.
 * Test case category: functionality test case
 */
static void Test_Mcasp_loopbacksemiInterleaved2ToNonInterleaved(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, ser, slot, sample, b;
    const uint32_t numSerializers = 2;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8U;
    const uint32_t numSamples = config.msgSize / (numSerializers * numSlots * slotSize);

    /* Use different serializers for TX and RX to avoid conflicts */
    /* Configure TX serializers for semi-interleaved-2 */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000005;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Configure serializer 0 as TX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x1;  /* Configure serializer 2 as TX */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0TxSersUsed[2] = {0,2};  /* Use serializers 0,2 for TX */
    openParams->txSerUsedCount = 2;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;

    /* Configure RX serializers for semi-interleaved-1 */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Configure serializer 1 as RX */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x2;  /* Configure serializer 3 as RX */
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0RxSersUsed[2] = {1,3};  /* Use serializers 1,3 for RX */
    gMcaspOpenParams[0].rxSerUsedCount = 2;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinEnable[] =
    {
        {PIN_MCASP0_AXR0,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR1,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif

    /* Set buffer formats - reverse of the previous function */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_NON_INTERLEAVED;

    openParams->txLoopjobBufLength = config.msgSize/4;
    openParams->rxLoopjobBufLength = config.msgSize/4;

    config.bufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2;
    config.frameCount = numSamples;
    config.slotCount = numSlots;
    config.serCount = numSerializers;
    config.slotSize = attrs->txSlotSize;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        Test_Mcasp_initBuffers(&TestMcasp_TxBuffer[i][0], &TestMcasp_RxBuffer[i][0], &config);
    }

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*)&TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = config.msgSize/4U;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_TxnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*)&TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = config.msgSize/4U;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_TxnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);

    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            CacheP_inv(TestMcasp_RxBuffer[i], config.msgSize, CacheP_TYPE_ALL);
        }
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            /* For semi-interleaved-2 to semi-interleaved-1 conversion:
             * TX (semi-interleaved-2): Different DMA organization pattern - serializer -> frame -> slot
             * RX (semi-interleaved-1): [ser0_slot0][ser1_slot0][ser0_slot1][ser1_slot1]...
             * Since we're using different serializers, we expect the data to be organized differently */
            for (sample = 0; sample < numSamples; sample++)
            {
                for (slot = 0; slot < numSlots; slot++)
                {
                    for (ser = 0; ser < numSerializers; ser++)
                    {
                        /* TX semi-interleaved-2: serializer -> frame -> slot */
                        uint32_t tx_offset = ((ser * numSamples * numSlots) + (sample * numSlots) + slot) * slotSize;
                        /* RX semi-interleaved-1: frame -> slot -> serializer */
                        uint32_t rx_offset = ((((slot * numSerializers) + ser) * numSamples) + sample ) * slotSize;

                        for (b = 0; b < slotSize; b++)
                        {
                            if (TestMcasp_TxBuffer[i][tx_offset + b] != TestMcasp_RxBuffer[i][rx_offset + b])
                            {
                                status = SystemP_FAILURE;
                            }
                        }
                    }
                }
            }
        }
    }

    /* Restore original configuration */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000001;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Reset serializer 0 to TX */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Reset serializer 1 to RX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x0;  /* Reset serializer 2 */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x0;  /* Reset serializer 3 */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    gMcasp0TxSersUsed[0] = 0;  /* Reset to use serializer 0 for TX */
    gMcasp0TxSersUsed[1] = 0;  /* Clear second element */
    openParams->txSerUsedCount = 1;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;
    gMcasp0RxSersUsed[0] = 1;  /* Reset to use serializer 1 for RX */
    gMcasp0RxSersUsed[1] = 1;  /* Clear second element */
    gMcaspOpenParams[0].rxSerUsedCount = 1;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinDisable[] =
    {
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinDisable, PINMUX_DOMAIN_ID_MAIN);
#endif

    MCASP_close(handle);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All bytes match!!\r\n");
        gTestPassCount++;
    }
    else
    {
        DebugP_log("Data mismatch\r\n");
    }
}

/**
 * \brief  Test MCASP semi-interleaved-1 to non-interleaved loopback.
 *
 * This test verifies MCASP data integrity when transmitting in semi-interleaved-1 format
 * and receiving in non-interleaved format. It configures the serializers and buffer formats,
 * performs a loopback transfer, and checks that the received data matches the transmitted data
 * after appropriate reordering for the buffer formats.
 * Test case category: functionality test case
 */
static void Test_Mcasp_loopbackNonInterleavedToSemiInterleaved1(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, ser, slot, sample, b;
    const uint32_t numSerializers = 2;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8U;
    const uint32_t numSamples = config.msgSize / (numSerializers * numSlots * slotSize);

    /* Use different serializers for TX and RX to avoid conflicts */
    /* Configure TX serializers for semi-interleaved-1 */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000005;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Configure serializer 0 as TX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x1;  /* Configure serializer 2 as TX */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0TxSersUsed[2] = {0,2};  /* Use serializers 0,2 for TX */
    openParams->txSerUsedCount = 2;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;

    /* Configure RX serializers for multi-serializer non-interleaved */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Configure serializer 1 as RX */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x2;  /* Configure serializer 3 as RX */
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0RxSersUsed[2] = {1,3};  /* Use serializers 1,3 for RX */
    gMcaspOpenParams[0].rxSerUsedCount = 2;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinEnable[] =
    {
        {PIN_MCASP0_AXR0,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR1,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif

    /* Set buffer formats */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_NON_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_1;

    openParams->txLoopjobBufLength = config.msgSize/4;
    openParams->rxLoopjobBufLength = config.msgSize/4;

    config.bufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_NON_INTERLEAVED;
    config.frameCount = numSamples;
    config.slotCount = numSlots;
    config.serCount = numSerializers;
    config.slotSize = attrs->txSlotSize;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        Test_Mcasp_initBuffers(&TestMcasp_TxBuffer[i][0], &TestMcasp_RxBuffer[i][0], &config);
    }

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*)&TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = config.msgSize/4U;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_TxnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*)&TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = config.msgSize/4U;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_TxnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);

    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            CacheP_inv(TestMcasp_RxBuffer[i], config.msgSize, CacheP_TYPE_ALL);
        }
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            /* For semi-interleaved-1 to multi-serializer non-interleaved conversion:
             * TX (semi-interleaved-1): [ser0_slot0][ser1_slot0][ser0_slot1][ser1_slot1]... (frame -> slot -> serializer)
             * RX (multi-serializer non-interleaved): [ser0_slot0_sample0][ser0_slot0_sample1]...[ser0_slot1_sample0]...[ser1_slot0_sample0]... (serializer -> slot -> frame)
             * Need to map from multi-serializer semi-interleaved to multi-serializer non-interleaved */
            for (sample = 0; sample < numSamples; sample++)
            {
                for (slot = 0; slot < numSlots; slot++)
                {
                    for (ser = 0; ser < numSerializers; ser++)
                    {
                        /* TX semi-interleaved-1: frame -> slot -> serializer */
                        uint32_t tx_offset = ((((slot * numSerializers) + ser) * numSamples) + sample ) * slotSize;
                        /* RX multi-serializer non-interleaved: serializer -> slot -> frame */
                        uint32_t rx_offset = ((sample * numSlots * numSerializers) + (slot * numSerializers) + ser) * slotSize;

                        for (b = 0; b < slotSize; b++)
                        {
                            if (TestMcasp_TxBuffer[i][tx_offset + b] != TestMcasp_RxBuffer[i][rx_offset + b])
                            {
                                status = SystemP_FAILURE;
                            }
                        }
                    }
                }
            }
        }
    }

    /* Keep multi-serializer configuration - do not restore to single serializer */

    MCASP_close(handle);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All bytes match!!\r\n");
        gTestPassCount++;
    }
    else
    {
        DebugP_log("Data mismatch\r\n");
    }
}

/**
 * \brief  Test MCASP non-interleaved to semi-interleaved-2 loopback.
 *
 * This test verifies MCASP data integrity when transmitting in non-interleaved format
 * and receiving in semi-interleaved-2 format. It configures the serializers and buffer formats,
 * performs a loopback transfer, and checks that the received data matches the transmitted data
 * after appropriate reordering for the buffer formats.
 * Test case category: functionality test case
 */
static void Test_Mcasp_loopbackNonInterleavedToSemiInterleaved2(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, ser, slot, sample, b;
    const uint32_t numSerializers = 2;
    const uint32_t numSlots = openParams->rxSlotCount;
    const uint32_t slotSize = attrs->txSlotSize/8U;
    const uint32_t numSamples = config.msgSize / (numSerializers * numSlots * slotSize);

    /* Use different serializers for TX and RX to avoid conflicts */
    /* Configure TX serializers for semi-interleaved-2 */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000005;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Configure serializer 0 as TX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x1;  /* Configure serializer 2 as TX */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0TxSersUsed[2] = {0,2};  /* Use serializers 0,2 for TX */
    openParams->txSerUsedCount = 2;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;

    /* Configure RX serializers for semi-interleaved-1 */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Configure serializer 1 as RX */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x2;  /* Configure serializer 3 as RX */
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12002U;
    uint8_t gMcasp0RxSersUsed[2] = {1,3};  /* Use serializers 1,3 for RX */
    gMcaspOpenParams[0].rxSerUsedCount = 2;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinEnable[] =
    {
        {PIN_MCASP0_AXR0,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR1,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinEnable, PINMUX_DOMAIN_ID_MAIN);
#endif

    /* Set buffer formats - reverse of the previous function */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_NON_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_SEMI_INTERLEAVED_2;

    openParams->txLoopjobBufLength = config.msgSize/4;
    openParams->rxLoopjobBufLength = config.msgSize/4;

    config.bufferFormat = MCASP_AUDBUFF_FORMAT_MULTISER_MULTISLOT_NON_INTERLEAVED;
    config.frameCount = numSamples;
    config.slotCount = numSlots;
    config.serCount = numSerializers;
    config.slotSize = attrs->txSlotSize;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        Test_Mcasp_initBuffers(&TestMcasp_TxBuffer[i][0], &TestMcasp_RxBuffer[i][0], &config);
    }

    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);

    TestMcasp_CntRx = 0;
    TestMcasp_CntTx = 0;

    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnRx[i].buf = (void*)&TestMcasp_RxBuffer[i][0];
        TestMcasp_TxnRx[i].count = config.msgSize/4U;
        TestMcasp_TxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(handle, &TestMcasp_TxnRx[i]);
    }
    for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
    {
        TestMcasp_TxnTx[i].buf = (void*)&TestMcasp_TxBuffer[i][0];
        TestMcasp_TxnTx[i].count = config.msgSize/4U;
        TestMcasp_TxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(handle, &TestMcasp_TxnTx[i]);
    }

    status = MCASP_startTransferRx(handle);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCASP_startTransferTx(handle);
    DebugP_assert(status == SystemP_SUCCESS);

    while ((TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT) || (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT))
    {
        /* wait for transfer completion */
    }

    MCASP_stopTransferRx(handle);
    MCASP_stopTransferTx(handle);

    if (openParams->transferMode == MCASP_TRANSFER_MODE_DMA)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            CacheP_inv(TestMcasp_RxBuffer[i], config.msgSize, CacheP_TYPE_ALL);
        }
    }

    if (SystemP_SUCCESS == status)
    {
        for (i = 0U; i < TEST_MCASP_APP_MSG_COUNT; i++)
        {
            /* For semi-interleaved-2 to semi-interleaved-1 conversion:
             * TX (semi-interleaved-2): Different DMA organization pattern - serializer -> frame -> slot
             * RX (semi-interleaved-1): [ser0_slot0][ser1_slot0][ser0_slot1][ser1_slot1]...
             * Since we're using different serializers, we expect the data to be organized differently */
            for (sample = 0; sample < numSamples; sample++)
            {
                for (slot = 0; slot < numSlots; slot++)
                {
                    for (ser = 0; ser < numSerializers; ser++)
                    {
                        /* TX semi-interleaved-2: serializer -> frame -> slot */
                        uint32_t tx_offset = (((slot * numSerializers + ser) * numSamples) + sample ) * slotSize;
                        /* RX semi-interleaved-1: frame -> slot -> serializer */
                        uint32_t rx_offset = ((ser * numSamples * numSlots) + (sample * numSlots) + slot) * slotSize;

                        for (b = 0; b < slotSize; b++)
                        {
                            if (TestMcasp_TxBuffer[i][tx_offset + b] != TestMcasp_RxBuffer[i][rx_offset + b])
                            {
                                status = SystemP_FAILURE;
                            }
                        }
                    }
                }
            }
        }
    }

    /* Restore original configuration */
    attrs->hwCfg.gbl.pdir = (uint32_t)0xBC000001;
    attrs->hwCfg.gbl.serSetup[0] = (uint32_t)0x1;  /* Reset serializer 0 to TX */
    attrs->hwCfg.gbl.serSetup[1] = (uint32_t)0x2;  /* Reset serializer 1 to RX */
    attrs->hwCfg.gbl.serSetup[2] = (uint32_t)0x0;  /* Reset serializer 2 */
    attrs->hwCfg.gbl.serSetup[3] = (uint32_t)0x0;  /* Reset serializer 3 */
    attrs->hwCfg.tx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    attrs->hwCfg.rx.fifoCfg.fifoCtl = (uint32_t)0x12001U;
    gMcasp0TxSersUsed[0] = 0;  /* Reset to use serializer 0 for TX */
    gMcasp0TxSersUsed[1] = 0;  /* Clear second element */
    openParams->txSerUsedCount = 1;
    openParams->txSerUsedArray = (uint8_t *) gMcasp0TxSersUsed;
    gMcasp0RxSersUsed[0] = 1;  /* Reset to use serializer 1 for RX */
    gMcasp0RxSersUsed[1] = 1;  /* Clear second element */
    gMcaspOpenParams[0].rxSerUsedCount = 1;
    gMcaspOpenParams[0].rxSerUsedArray = (uint8_t *) gMcasp0RxSersUsed;

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    static Pinmux_PerCfg_t serPinDisable[] =
    {
        {PIN_MCASP0_AXR2,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        {PIN_MCASP0_AXR3,( PIN_MODE(0) | PIN_PULL_DISABLE )},
        { PINMUX_END, 0U }
    };
    Pinmux_config(serPinDisable, PINMUX_DOMAIN_ID_MAIN);
#endif

    MCASP_close(handle);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All bytes match!!\r\n");
        gTestPassCount++;
    }
    else
    {
        DebugP_log("Data mismatch\r\n");
    }
}

static void Test_Mcasp_loopbackInterleavedToNonInterleaved_wrapper(void *args)
{
    uint32_t i = 0U; 
    gTestPassCount = 0U;
    DebugP_log("\nInterleaved to Non-Interleaved loopback :-\r\n");

    for(i = 0U; i < TEST_MCASP_APP_NUM_TESTS; i++)
    {
        DebugP_log("\nRunning test for MsgSize of %.2f KB:-\r\n", (float)(gtestSizes[i])/(1024U));
        config.msgSize = gtestSizes[i];
        Test_Mcasp_loopbackInterleavedToNonInterleaved((void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    }

    if(gTestPassCount == TEST_MCASP_APP_NUM_TESTS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
}

static void Test_Mcasp_loopbackNonInterleavedToInterleaved_wrapper(void *args)
{
    uint32_t i = 0U; 
    gTestPassCount = 0U;
    DebugP_log("\nNon-Interleaved to Interleaved loopback :-\r\n");

    for(i = 0U; i < TEST_MCASP_APP_NUM_TESTS; i++)
    {
        DebugP_log("\nRunning test for MsgSize of %.2f KB:-\r\n", (float)(gtestSizes[i])/(1024U));
        config.msgSize = gtestSizes[i];
        Test_Mcasp_loopbackNonInterleavedToInterleaved((void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    }

    if(gTestPassCount == TEST_MCASP_APP_NUM_TESTS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
}

static void Test_Mcasp_loopbacksemiInterleaved1ToSemiInterleaved2_wrapper(void *args)
{
    uint32_t i = 0U; 
    gTestPassCount = 0U;
    DebugP_log("\nSemi-Interleaved-1 to Semi-Interleaved-2 loopback :-\r\n");

    for(i = 0U; i < TEST_MCASP_APP_NUM_TESTS; i++)
    {
        DebugP_log("\nRunning test for MsgSize of %.2f KB:-\r\n", (float)(gtestSizes[i])/(1024U));
        config.msgSize = gtestSizes[i];
        Test_Mcasp_loopbacksemiInterleaved1ToSemiInterleaved2((void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    }

    if(gTestPassCount == TEST_MCASP_APP_NUM_TESTS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
}

static void Test_Mcasp_loopbacksemiInterleaved2ToSemiInterleaved1_wrapper(void *args)
{
    uint32_t i = 0U; 
    gTestPassCount = 0U;
    DebugP_log("\nSemi-Interleaved-2 to Semi-Interleaved-1 loopback :-\r\n");

    for(i = 0U; i < TEST_MCASP_APP_NUM_TESTS; i++)
    {
        DebugP_log("\nRunning test for MsgSize of %.2f KB:-\r\n", (float)(gtestSizes[i])/(1024U));
        config.msgSize = gtestSizes[i];
        Test_Mcasp_loopbacksemiInterleaved2ToSemiInterleaved1((void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    }

    if(gTestPassCount == TEST_MCASP_APP_NUM_TESTS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
}

static void Test_Mcasp_loopbacksemiInterleaved1ToNonInterleaved_wrapper(void *args)
{
    uint32_t i = 0U; 
    gTestPassCount = 0U;
    DebugP_log("\nSemi-Interleaved-1 to Non-Interleaved loopback :-\r\n");

    for(i = 0U; i < TEST_MCASP_APP_NUM_TESTS; i++)
    {
        DebugP_log("\nRunning test for MsgSize of %.2f KB:-\r\n", (float)(gtestSizes[i])/(1024U));
        config.msgSize = gtestSizes[i];
        Test_Mcasp_loopbacksemiInterleaved1ToNonInterleaved((void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    }

    if(gTestPassCount == TEST_MCASP_APP_NUM_TESTS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
}

static void Test_Mcasp_loopbacksemiInterleaved2ToNonInterleaved_wrapper(void *args)
{
    uint32_t i = 0U; 
    gTestPassCount = 0U;
    DebugP_log("\nSemi-Interleaved-2 to Non-Interleaved loopback :-\r\n");

    for(i = 0U; i < TEST_MCASP_APP_NUM_TESTS; i++)
    {
        DebugP_log("\nRunning test for MsgSize of %.2f KB:-\r\n", (float)(gtestSizes[i])/(1024U));
        config.msgSize = gtestSizes[i];
        Test_Mcasp_loopbacksemiInterleaved2ToNonInterleaved((void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    }

    if(gTestPassCount == TEST_MCASP_APP_NUM_TESTS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
}

static void Test_Mcasp_loopbackNonInterleavedToSemiInterleaved1_wrapper(void *args)
{
    uint32_t i = 0U; 
    gTestPassCount = 0U;
    DebugP_log("\nNon-Interleaved to Semi-Interleaved-1 loopback :-\r\n");

    for(i = 0U; i < TEST_MCASP_APP_NUM_TESTS; i++)
    {
        DebugP_log("\nRunning test for MsgSize of %.2f KB:-\r\n", (float)(gtestSizes[i])/(1024U));
        config.msgSize = gtestSizes[i];
        Test_Mcasp_loopbackNonInterleavedToSemiInterleaved1((void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    }

    if(gTestPassCount == TEST_MCASP_APP_NUM_TESTS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
}

static void Test_Mcasp_loopbackNonInterleavedToSemiInterleaved2_wrapper(void *args)
{
    uint32_t i = 0U; 
    gTestPassCount = 0U;
    DebugP_log("\nNon-Interleaved to Semi-Interleaved-2 loopback :-\r\n");

    for(i = 0U; i < TEST_MCASP_APP_NUM_TESTS; i++)
    {
        DebugP_log("\nRunning test for MsgSize of %.2f KB:-\r\n", (float)(gtestSizes[i])/(1024U));
        config.msgSize = gtestSizes[i];
        Test_Mcasp_loopbackNonInterleavedToSemiInterleaved2((void*)&gMcaspOpenParams[CONFIG_MCASP0]);
    }

    if(gTestPassCount == TEST_MCASP_APP_NUM_TESTS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
}
#if defined(SOC_AM275X)

/**
 * \brief Test MCASP transaction count bounds checking.
 *
 * This test verifies that the MCASP driver correctly validates transaction count
 * bounds by checking tempIcntX against MCASP_ICNT2_MAX.
 * Test case category: negative test case
 */
static void Test_Mcasp_transactionCountBoundsCheck(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    uint32_t instance = (uint32_t)(openParams - &gMcaspOpenParams[0]);
    MCASP_Attrs *attrs = (MCASP_Attrs *)gMcaspConfig[instance].attrs;
    int32_t status = SystemP_SUCCESS;
    uint8_t originalWaterLevel;
    
    DebugP_log("\nTesting transaction count bounds checking...\r\n");
    
    /* Save original waterLevel */
    originalWaterLevel = attrs->txFifoWaterLevel;
    
    /* Set up configuration that could trigger bounds checking */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    
    /* Set a very small waterLevel to force large tempIcntX/tempIcntY values */
    attrs->txFifoWaterLevel = 1U;
    attrs->rxFifoWaterLevel = 1U;
    
    /* Use a very large transaction size to trigger bounds checking */
    /* MCASP_ICNT2_MAX is 65535U, so we need to create conditions where
     * tempIcntX exceeds this value */
    uint32_t largeTransactionSize = (256U * 1024U);
    
    openParams->txLoopjobBufLength = largeTransactionSize/4U;
    openParams->rxLoopjobBufLength = largeTransactionSize/4U;
    
    /* Close existing handle */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    
    /* Try to open with large transaction size */
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);
    
    if(handle != NULL)
    {
        /* Try to start transfer - this should trigger transaction count bounds checking */
        status = MCASP_startTransferTx(handle);
        
        if(status == SystemP_FAILURE)
        {
            DebugP_log("Transaction count bounds checking correctly detected overflow!\r\n");
            status = SystemP_SUCCESS;  /* Test passed */
        }
        else
        {
            DebugP_log("WARNING: Transaction count bounds checking did not detect overflow - may need larger size\r\n");
            status = SystemP_FAILURE;
        }
       
        MCASP_close(handle);
    }
    else
    {
        DebugP_log("ERROR: Failed to open MCASP for transaction count bounds checking test\r\n");
        status = SystemP_FAILURE;
    }
    
    /* Restore original settings */
    attrs->txFifoWaterLevel = originalWaterLevel;
    openParams->txLoopjobBufLength = TEST_MCASP_APP_MSGSIZE_1/4U;
    openParams->rxLoopjobBufLength = TEST_MCASP_APP_MSGSIZE_1/4U;
    
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}
#endif

/**
 * \brief Test MCASP invalid RX buffer format handling.
 *
 * This test verifies that the MCASP driver correctly handles invalid RX buffer formats
 * by returning SystemP_FAILURE when an unsupported RX buffer format is used.
 * Test case category: negative test case
 */
static void Test_Mcasp_invalidRxBufferFormat(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status = SystemP_SUCCESS;
    
    DebugP_log("\nTesting invalid RX buffer format handling...\r\n");
    
    /* Set valid TX format but invalid RX buffer format */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    openParams->rxBufferFormat = 99U;  /* Invalid format - not in the defined enum range */
    
    openParams->txLoopjobBufLength = TEST_MCASP_APP_MSGSIZE_4/4U;
    openParams->rxLoopjobBufLength = TEST_MCASP_APP_MSGSIZE_4/4U;
    
    /* Close existing handle */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    
    /* Try to open with invalid RX buffer format */
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);
    
    if(handle != NULL)
    {
        /* Submit RX transaction to trigger the buffer format validation */
        TestMcasp_TxnRx[0].buf = (void*)&TestMcasp_RxBuffer[0][0];
        TestMcasp_TxnRx[0].count = TEST_MCASP_APP_MSGSIZE_4/4U;
        TestMcasp_TxnRx[0].timeout = 0xFFFFFF;
        status = MCASP_submitRx(handle, &TestMcasp_TxnRx[0]);
        
        if(status == SystemP_FAILURE)
        {
            DebugP_log("Invalid RX buffer format correctly detected and rejected!\r\n");
            status = SystemP_SUCCESS;  /* Test passed */
        }
        else
        {
            DebugP_log("ERROR: Invalid RX buffer format was not detected!\r\n");
            status = SystemP_FAILURE;  /* Test failed */
        }
        
        MCASP_close(handle);
    }
    else
    {
        DebugP_log("ERROR: Failed to open MCASP with invalid RX buffer format\r\n");
        status = SystemP_FAILURE;
    }
    
    /* Restore valid buffer format for subsequent tests */
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_NON_INTERLEAVED;
    
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief Test MCASP invalid buffer format handling.
 *
 * This test verifies that the MCASP driver correctly handles invalid buffer formats
 * by returning SystemP_FAILURE when an unsupported buffer format is used.
 * Test case category: negative test case
 */
static void Test_Mcasp_invalidTxBufferFormat(void *args)
{
    MCASP_OpenParams *openParams = (MCASP_OpenParams*)args;
    int32_t status = SystemP_SUCCESS;
    
    DebugP_log("\nTesting invalid buffer format handling...\r\n");
    
    /* Set an invalid buffer format (value outside the defined range) */
    openParams->txBufferFormat = 99U;  /* Invalid format - not in the defined enum range */
    openParams->rxBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_INTERLEAVED;
    
    openParams->txLoopjobBufLength = TEST_MCASP_APP_MSGSIZE_4/4U;
    openParams->rxLoopjobBufLength = TEST_MCASP_APP_MSGSIZE_4/4U;
    
    /* Close existing handle */
    MCASP_close(gMcaspHandle[CONFIG_MCASP0]);
    gMcaspHandle[CONFIG_MCASP0] = NULL;
    
    /* Try to open with invalid buffer format - this should succeed as validation happens later */
    MCASP_Handle handle = MCASP_open(CONFIG_MCASP0, openParams);
    
    if(handle != NULL)
    {
        /* Submit a transaction to trigger the buffer format validation */
        TestMcasp_TxnTx[0].buf = (void*)&TestMcasp_TxBuffer[0][0];
        TestMcasp_TxnTx[0].count = TEST_MCASP_APP_MSGSIZE_4/4U;
        TestMcasp_TxnTx[0].timeout = 0xFFFFFF;
        status = MCASP_submitTx(handle, &TestMcasp_TxnTx[0]);
        
        if(status == SystemP_FAILURE)
        {
            DebugP_log("Invalid buffer format correctly detected and rejected!\r\n");
            status = SystemP_SUCCESS;  /* Test passed */
        }
        else
        {
            DebugP_log("ERROR: Invalid buffer format was not detected!\r\n");
            status = SystemP_FAILURE;  /* Test failed */
        }

        MCASP_close(handle);
    }
    else
    {
        DebugP_log("ERROR: Failed to open MCASP with invalid buffer format\r\n");
        status = SystemP_FAILURE;
    }
    
    /* Restore valid buffer format for subsequent tests */
    openParams->txBufferFormat = MCASP_AUDBUFF_FORMAT_1SER_MULTISLOT_NON_INTERLEAVED;
    
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

void mcasp_txcb (MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    if (TestMcasp_CntTx < TEST_MCASP_APP_TEST_COUNT)
    {
        TestMcasp_CntTx++;
        MCASP_submitTx(handle, transaction);
    }
}

void mcasp_rxcb (MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    if (TestMcasp_CntRx < TEST_MCASP_APP_TEST_COUNT)
    {
        TestMcasp_CntRx++;
        MCASP_submitRx(handle, transaction);
    }
}

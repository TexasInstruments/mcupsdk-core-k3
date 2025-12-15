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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "udma_test.h"
#include "udma_testconfig.h"
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/udma.h>

/* ========================================================================== */
/*                              MACROS                                        */
/* ========================================================================== */
#define TEST_UDMA_BUF_ATTR __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")))
#define TEST_UDMA_NUM_BYTES                                             (1024U)   /* Default memcpy size */
#define TEST_UDMA_TRPD_SIZE                                             (UDMA_GET_TRPD_TR15_SIZE(1U)) /* One TR15 desc */
#define TEST_UDMA_RING_ELEM_CNT                                         (1U)      /* Elements per ring */

#define TEST_UDMA_TR_CMD_ID                                             (0x25U)
#define TEST_UDMA_TR_FMTFLAGS_LINEAR_1B                                 (0x00000000U)/* Linear addressing */
#define TEST_UDMA_POISON_PATTERN_BYTE                                   (0xA5U)      /* Fill before transfer */

/* --- Helper/Zero/None/Invalid Macros for Refactoring --- */
#define TEST_UDMA_BUF_INDEX_ZERO                                        (0U)         /* Buffer index zero */
#define TEST_UDMA_FLAG_STATIC_NONE                                      (0U)         /* Static flag none */
#define TEST_UDMA_FLAG_INDIRECT_NONE                                    (0U)         /* Indirect flag none */
#define TEST_UDMA_PHY_ADDR_NONE                                         (0U)         /* Physical address none */
#define TEST_UDMA_CB_COUNT_ZERO                                         (0U)         /* Callback count zero */
#define TEST_UDMA_EVENT_LOCAL_ID_NONE                                   (0U)         /* Local event ID none */
#define TEST_UDMA_EVENT_GLOBAL_ID_NONE                                  (0U)         /* Global event ID none */
#define UDMA_EVENT_TYPE_NONE                                            (0U)         /* Event type none */
#define UDMA_EVENT_MODE_NONE                                            (0U)         /* Event mode none */
#define UDMA_CORE_INTR_NONE                                             (0U)         /* Core interrupt none */
#define TEST_UDMA_ALLOC_FLAG_NONE                                       (0U)         /* Allocation flag none */

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

/* ---------------- Single-transfer / Basic Buffers ------------------------ */
uint8_t TestUdma_TrpdSingleDesc[TEST_UDMA_TRPD_SIZE]                    TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_Src[TEST_UDMA_NUM_BYTES]                               TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_Dst[TEST_UDMA_NUM_BYTES]                               TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_FqRingMem[UDMA_CACHELINE_ALIGNMENT]                    TEST_UDMA_BUF_ATTR;
uint8_t TestUdma_CqRingMem[UDMA_CACHELINE_ALIGNMENT]                    TEST_UDMA_BUF_ATTR;
Udma_ChObject TestUdma_ChObj;
Udma_DrvObject TestUdma_DrvObj;

/* Declare zero-length dummy arrays in the unused linker sections. */
__attribute__((section(".udma_buffer_msmc"), used))  static uint8_t gDummy_msmc[1];
__attribute__((section(".udma_buffer_ospi"), used))  static uint8_t gDummy_ospi[1];
__attribute__((section(".udma_buffer_internal"), used)) static uint8_t gDummy_internal[1];

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ---------------- Single-value Semantic Enum ------------------------------ */
typedef enum
{
    TEST_UDMA_VALUE_ZERO                    = 0U,
    TEST_UDMA_VALUE_ONE                     = 1U,

    TEST_UDMA_FLOW_INDEX_0                  = TEST_UDMA_VALUE_ZERO,
    TEST_UDMA_FLOW_INDEX_1                  = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_RING_ORDER_ID_DEFAULT         = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_RING_NUM_ONE                  = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_STATUS_ENABLED                = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_ALLOC_FLAG_SET                = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_OES_ALLOC_DONE_FLAG           = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_QNUM_INDEX_1                  = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_CLEARBUF_SINGLE_COUNT         = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_TR_COUNT_SINGLE               = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_TR_FLAG_SET                   = TEST_UDMA_VALUE_ONE,
    TEST_UDMA_TR_ICNT_UNIT                  = TEST_UDMA_VALUE_ONE
} TestUdmaConst;

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */
static int32_t TestUdma_trpdInit(Udma_ChHandle chHandle,
                                 uint8_t *trpdMemory,
                                 const void *destBuf,
                                 const void *srcBuffer,
                                 uint32_t length);
static int32_t TestUdma_initBuffer(uint8_t *srcBuffer, uint8_t *destBuf, uint32_t length);
static void TestUdma_enableForceTeardownTest(void *args);
extern bool TestUdma_faultInjectForceTeardown(uint32_t disablePhase);

/* ========================================================================== */
/*                         Internal Function Definitions                      */
/* ========================================================================== */
/* Helper: Initialize a TR15 transfer record packet descriptor (TRPD) for a
 * simple 1D block move. Fills source/destination addressing, element counts,
 * dimensions, and completion event configuration, then performs cache
 * writeback so hardware sees updated descriptor contents. Expects an already
 * opened/allocated channel handle. */
static int32_t TestUdma_trpdInit(Udma_ChHandle chHandle,
                                 uint8_t *trpdMemory,
                                 const void *destBuf,
                                 const void *srcBuffer,
                                 uint32_t length)
{
    CSL_UdmapTR15  *chainTrDescriptor;
    uint32_t        cqRingNum;
    if ((NULL == chHandle) || (NULL == trpdMemory) ||
        (NULL == destBuf) || (NULL == srcBuffer) || (TEST_UDMA_VALUE_ZERO == length))
    {
        return UDMA_EBADARGS;
    }
    cqRingNum = Udma_chGetCqRingNum(chHandle);
    if (UDMA_RING_INVALID == cqRingNum)
    {
        return UDMA_EFAIL;
    }

    /* Make TRPD with TR15 TR type */
    UdmaUtils_makeTrpdTr15(trpdMemory, TEST_UDMA_TR_COUNT_SINGLE, cqRingNum);

    /* Setup TR */
    chainTrDescriptor = UdmaUtils_getTrpdTr15Pointer(trpdMemory, TEST_UDMA_BUF_INDEX_ZERO);
    chainTrDescriptor->flags    = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, TEST_UDMA_FLAG_STATIC_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_MATCH_SOL_EOL);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, TEST_UDMA_TR_CMD_ID);  /* This will come back in TR response */
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, TEST_UDMA_FLAG_INDIRECT_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, TEST_UDMA_FLAG_INDIRECT_NONE);
    chainTrDescriptor->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOP, TEST_UDMA_TR_FLAG_SET);
    chainTrDescriptor->icnt0    = length;
    chainTrDescriptor->icnt1    = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->icnt2    = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->icnt3    = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->dim1     = chainTrDescriptor->icnt0;
    chainTrDescriptor->dim2     = (chainTrDescriptor->icnt0 * chainTrDescriptor->icnt1);
    chainTrDescriptor->dim3     = (chainTrDescriptor->icnt0 * chainTrDescriptor->icnt1 * chainTrDescriptor->icnt2);
    chainTrDescriptor->addr     = (uint64_t) Udma_defaultVirtToPhyFxn(srcBuffer, TEST_UDMA_BUF_INDEX_ZERO, NULL);
    chainTrDescriptor->fmtflags = TEST_UDMA_TR_FMTFLAGS_LINEAR_1B;    /* Linear addressing, 1 byte per elem */
    chainTrDescriptor->dicnt0   = length;
    chainTrDescriptor->dicnt1   = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->dicnt2   = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->dicnt3   = TEST_UDMA_TR_ICNT_UNIT;
    chainTrDescriptor->ddim1    = chainTrDescriptor->dicnt0;
    chainTrDescriptor->ddim2    = (chainTrDescriptor->dicnt0 * chainTrDescriptor->dicnt1);
    chainTrDescriptor->ddim3    = (chainTrDescriptor->dicnt0 * chainTrDescriptor->dicnt1 * chainTrDescriptor->dicnt2);
    chainTrDescriptor->daddr    = (uint64_t) Udma_defaultVirtToPhyFxn(destBuf, TEST_UDMA_BUF_INDEX_ZERO, NULL);

    /* Perform cache writeback */
    CacheP_wb(trpdMemory, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALLD);
    return UDMA_SOK;
}


/* Helper: Initialize source and destination buffers for memcpy tests.
 * Source is filled with incremental pattern 0..length-1 while destination is
 * poisoned with 0xA5 to detect incomplete transfers. Performs cache writeback
 * for both buffers to ensure coherence before DMA submission. */
static int32_t TestUdma_initBuffer(uint8_t *srcBuffer, uint8_t *destBuf, uint32_t length)
{
    int32_t index;
    if ((NULL == srcBuffer) || (NULL == destBuf) || (TEST_UDMA_VALUE_ZERO == length))
    {
        return UDMA_EBADARGS;
    }
    for(index = 0U; index < length; index+=1)
    {
        srcBuffer[index] = index;
        destBuf[index] = TEST_UDMA_POISON_PATTERN_BYTE;
    }
    /* Writeback source and destination buffer */
    CacheP_wb(srcBuffer, length, CacheP_TYPE_ALLD);
    CacheP_wb(destBuf, length, CacheP_TYPE_ALLD);
    return UDMA_SOK;
}

/**
 * \brief Test to force UDMA channel teardown during disable
 *
 * Test Category: Fault injection / robustness test.
 *
 * This test verifies correct UDMA channel behavior when a transfer
 * is intentionally left incomplete and channel disable is invoked
 * with forced teardown enabled. The test ensures no hang, crash,
 * or resource leak occurs during channel close and driver deinit.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused).
 *
 * \return None.
 */
static void TestUdma_enableForceTeardownTest(void *args)
{
    Udma_InitPrms udmaInitPrms;
    Udma_DrvHandle drvHandle = &TestUdma_DrvObj;
    Udma_ChHandle chHandle = &TestUdma_ChObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    uint8_t *trpdMem = TestUdma_TrpdSingleDesc;
    int32_t retVal;

    /* Initialize BCDMA driver object */
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &udmaInitPrms);
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Open blkcopy channel */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_FqRingMem;
    chPrms.cqRingPrms.ringMem = TestUdma_CqRingMem;
    chPrms.fqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
    chPrms.cqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
    chPrms.fqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_CNT;
    chPrms.cqRingPrms.elemCnt = TEST_UDMA_RING_ELEM_CNT;

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retVal);

    /* Configure TX/RX */
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, Udma_chConfigTx(chHandle, &txPrms));
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, Udma_chConfigRx(chHandle, &rxPrms));

    /* Initialize buffers */
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES));

    /* Build TRPD: simple linear memcpy for TEST_UDMA_NUM_BYTES */
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK,
        TestUdma_trpdInit(chHandle,
                          trpdMem,
                          TestUdma_Dst,
                          TestUdma_Src,
                          TEST_UDMA_NUM_BYTES));

    /* Writeback TRPD */
    CacheP_wb(trpdMem, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALLD);

    /* Enable channel and queue TRPD */
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, Udma_chEnable(chHandle));
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK,
        Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle),
                          Udma_defaultVirtToPhyFxn(trpdMem, 0U, NULL)));

    /* No trigger : TR never completes, Channel stays busy */
    /* Give small time slice to let transfer not complete */
    ClockP_usleep(1000U);

    /* Attempt to disable with timeout=0 to force graceful timeout */
    retVal = Udma_chDisable(chHandle, 0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retVal);

    /* Post-disable: verify disabled, guard close */
    {
        uint8_t enable = 1U;
        uint32_t guard = 2000U;
        while (guard)
        {
            TEST_ASSERT_EQUAL_INT32(UDMA_SOK, Udma_chGetChanEnStatus(chHandle, &enable));
            if (enable == 0U) break;
            ClockP_usleep(1000U);
            guard -= 1;
        }
        if (enable != 0U)
        {
            TEST_ASSERT_EQUAL_INT32(UDMA_SOK, Udma_chReset(chHandle));
        }
    }

    /* CQ may contain either a normal completion or a teardown completion */
    uint64_t pDescChk = 0U;
    int32_t dqRet = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &pDescChk);
    if (dqRet == UDMA_SOK)
    {
        /* Completion present — acceptable for this scenario */
    }
    else
    {
        /* No completion present is also fine */
    }

    /* Cleanup channel and driver */
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, Udma_chClose(chHandle));
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, Udma_deinit(drvHandle));
}

/* ========================================================================== */
/*                         Fault Injection Handler                            */
/* ========================================================================== */

/**
 * \brief Fault injection hook to force UDMA teardown during disable
 *
 * Test Category: Fault injection helper.
 *
 * This function overrides the UDMA driver weak hook and is used to
 * force the disable path to enter forced teardown instead of graceful
 * completion, enabling validation of teardown robustness.
 *
 * \param disablePhase Indicates the disable phase at which the
 * fault injection decision is made.
 *
 * \return false to force teardown, true to allow normal behavior.
 */
bool TestUdma_faultInjectForceTeardown(uint32_t disablePhase)
{
    bool result = true;
    if(disablePhase == 1)
    {
        TEST_ASSERT_EQUAL_INT32(UDMA_SOK, Udma_chEnable(&TestUdma_ChObj));
        /* Return false in order to set end_loop variable in
         * source code as false to enter forced teardown
         */
        result = false;
    }
    return result;
}

/* ========================================================================== */
/*                            Main Test Function                              */
/* ========================================================================== */
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
    RUN_TEST(TestUdma_enableForceTeardownTest, 9598, NULL);
    UNITY_END();
}

/* ========================================================================== */
/*                    Unity Framework Setup Functions                         */
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
    /* Do nothing */
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
    /* Do nothing */
}

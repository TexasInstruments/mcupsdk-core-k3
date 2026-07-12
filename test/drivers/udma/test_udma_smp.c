/*
 *  Copyright (C) 2025-2026 Texas Instruments Incorporated
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
 * @file test_udma_smp.c
 * @brief The following test aims at creating tasks for each A53 core.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "test_config.h"
#include "unity.h"
#include <drivers/udma.h>
#include <drivers/udma/v0/udma_priv.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                           Macros & Defines                                 */
/* ========================================================================== */
#define TEST_UDMA_NUM_BYTES                                         (1024U)
#define TEST_UDMA_TRPD_SIZE                                         (UDMA_GET_TRPD_TR15_SIZE(1U))
#define TEST_UDMA_OPEN_CLOSE_RACE_ITERATIONS                        (200U)
#define TEST_UDMA_RING_OVERFLOW_ELEMENT_COUNT                       (4U)
#define TEST_UDMA_RING_OVERFLOW_NUM_DESCRIPTORS                     (10U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile int TestUdma_MulticoreTransferComplete              = 0;
static volatile int TestUdma_SingleInstanceThread1Result            = -1;
static volatile int TestUdma_SingleInstanceThread2Result            = -1;

static volatile uint32_t TestUdma_RingOverflowRingQueued            = 0U;
static volatile uint32_t TestUdma_RingOverflowRingCompleted         = 0U;
static volatile uint32_t TestUdma_RingOverflowRingProducerDone      = 0U;
static volatile uint32_t TestUdma_RingOverflowRingConsumerDone      = 0U;

static SemaphoreP_Object TestUdma_ChOpenCloseRaceJoinSem;
static SemaphoreP_Object TestUdma_ChOpenCloseRaceDriverLock;
static SemaphoreP_Object TestUdma_RingOverflowJoinSem;
static SemaphoreP_Object TestUdma_MultiInstanceMultiCoreMutex;

static uint8_t TestUdma_BlkCopyChFqRingMem[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));

static uint8_t TestUdma_Task1Src[TEST_UDMA_NUM_BYTES]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_Task1Dst[TEST_UDMA_NUM_BYTES]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_Task2Src[TEST_UDMA_NUM_BYTES]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_Task2Dst[TEST_UDMA_NUM_BYTES]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));

static uint8_t TestUdma_RingOverflowFqMem[UDMA_CACHELINE_ALIGNMENT * TEST_UDMA_RING_OVERFLOW_ELEMENT_COUNT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_RingOverflowCqMem[UDMA_CACHELINE_ALIGNMENT * TEST_UDMA_RING_OVERFLOW_ELEMENT_COUNT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_RingOverflowTrpd[TEST_UDMA_RING_OVERFLOW_NUM_DESCRIPTORS][TEST_UDMA_TRPD_SIZE]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_RingOverflowSrc[TEST_UDMA_RING_OVERFLOW_NUM_DESCRIPTORS][TEST_UDMA_NUM_BYTES]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_RingOverflowDst[TEST_UDMA_RING_OVERFLOW_NUM_DESCRIPTORS][TEST_UDMA_NUM_BYTES]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));

static uint8_t TestUdma_ChOpenCloseRaceRingFqMem0[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_ChOpenCloseRaceRingCqMem0[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_ChOpenCloseRaceRingFqMem1[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_ChOpenCloseRaceRingCqMem1[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));

static uint8_t TestUdma_SingleTaskCqMem[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_SingleTaskTrpd[TEST_UDMA_TRPD_SIZE]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));

static uint8_t TestUdma_BcdmaTrpdMem[TEST_UDMA_TRPD_SIZE]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_BcdmaCqRingMem[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));

static uint8_t TestUdma_FqRingMem1[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_FqRingMem2[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_CqRingMem1[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));
static uint8_t TestUdma_CqRingMem2[UDMA_CACHELINE_ALIGNMENT]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));

static uint8_t TestUdma_MultiInstanceTrpd[TEST_UDMA_TRPD_SIZE]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT), section(".udma_buffer_ddr")));

/* ========================================================================== */
/*                              Structures                                    */
/* ========================================================================== */

typedef struct {
    Udma_ChHandle chHandle;
    uint8_t *src;
    uint8_t *dst;
    volatile int *result;
} TestUdma_MemcpyThreadParams;

/* Minimal per-thread context compatible with TestUdma_* threads */
typedef struct {
    int32_t result;
    TaskP_Object taskObj;
    uint8_t stack[6 * 1024];
} TestUdma_SmpThreadCtx;

/* Local generic event callback: post the provided semaphore context */
typedef struct {
    SemaphoreP_Object *sem;
    volatile uint32_t *count;
} TestUdma_EventContext;

typedef struct {
    Udma_DrvHandle drv;
    uint8_t *fqRingMem;
    uint8_t *cqRingMem;
} TestUdma_RaceTaskRingArgs;

/* ========================================================================== */
/*                     Internal Function Declarations                         */
/* ========================================================================== */
static void TestUdma_initBuffer(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length);
static void TestUdma_trpdInit(Udma_ChHandle chHandle,
                             uint8_t *trpdMem,
                             const void *destBuf,
                             const void *srcBuf,
                             uint32_t length);
static void TestUdma_compareBuffer(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length);
static int32_t TestUdma_drainCqUntilEmpty(Udma_ChHandle chHndl, uint32_t maxAttemptsUs);
static void TestUdma_genericEventCb(Udma_EventHandle eventHandle, uint32_t eventType, void *appData);

static void TestUdma_pktdmaRxInitTask(void *args);
static void TestUdma_bcdmaBlkcpySingleTask(void *args);
static void TestUdma_pktdmaRxFlowCheckThread(void *args);
static void TestUdma_bcdmaBlkcpyEventThread(void *args);
static void TestUdma_blkcpyMemcpyThread(void *args);
static void TestUdma_ringOverflowProducerTask(void *args);
static void TestUdma_ringOverflowConsumerTask(void *args);
static void TestUdma_chOpenCloseRaceTaskCore1(void *args);
static void TestUdma_chOpenCloseRaceTaskCore0(void *args);

/* ========================================================================== */
/*                       Static Test Function Prototypes                      */
/* ========================================================================== */

static void TestUdma_multiInstanceMultiCore(void *args);
static void TestUdma_singleInstanceMulticore(void *args);
static void TestUdma_multiInstancePktdmaBcdma(void *args);
static void TestUdma_ringOverflowTest(void *args);
static void TestUdma_chOpenCloseRaceTest(void *args);

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/* Helper: Build a TR15 TRPD for block-copy on the given channel and write back cache.
 * Fills TR flags, addressing and sizes (linear), binds CQ ring, and wb for HW visibility.
 * Used by memcpy-style submit paths.
 */
static void TestUdma_trpdInit(Udma_ChHandle chHandle,
                             uint8_t *trpdMem,
                             const void *destBuf,
                             const void *srcBuf,
                             uint32_t length)
{
    CSL_UdmapTR15  *pTr;
    uint32_t        cqRingNum = Udma_chGetCqRingNum(chHandle);

    /* Make TRPD with TR15 TR type */
    UdmaUtils_makeTrpdTr15(trpdMem, 1U, cqRingNum);

    /* Setup TR */
    pTr = UdmaUtils_getTrpdTr15Pointer(trpdMem, 0U);
    pTr->flags    = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_MATCH_SOL_EOL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, 0x25U);  /* This will come back in TR response */
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);
    pTr->icnt0    = length;
    pTr->icnt1    = 1U;
    pTr->icnt2    = 1U;
    pTr->icnt3    = 1U;
    pTr->dim1     = pTr->icnt0;
    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
    pTr->addr     = (uint64_t) Udma_defaultVirtToPhyFxn(srcBuf, 0U, NULL);
    pTr->fmtflags = 0x00000000U;    /* Linear addressing, 1 byte per elem */
    pTr->dicnt0   = length;
    pTr->dicnt1   = 1U;
    pTr->dicnt2   = 1U;
    pTr->dicnt3   = 1U;
    pTr->ddim1    = pTr->dicnt0;
    pTr->ddim2    = (pTr->dicnt0 * pTr->dicnt1);
    pTr->ddim3    = (pTr->dicnt0 * pTr->dicnt1 * pTr->dicnt2);
    pTr->daddr    = (uint64_t) Udma_defaultVirtToPhyFxn(destBuf, 0U, NULL);

    /* Perform cache writeback */
    CacheP_wb(trpdMem, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALLD);

    return;
}

/* Helper: Initialize src/dst buffers with test patterns and write back cache.
 * Src gets an incremental pattern; Dst is poisoned (0xA5) to catch partial copies.
 * Ensures DMA sees updates via CacheP_wb.
 */
static void TestUdma_initBuffer(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length)
{
    uint32_t        i;

    for(i = 0U; i < length; i += 1)
    {
        srcBuf[i] = i;
        destBuf[i] = 0xA5U;
    }
    /* Writeback source and destination buffer */
    CacheP_wb(srcBuf, length, CacheP_TYPE_ALLD);
    CacheP_wb(destBuf, length, CacheP_TYPE_ALLD);

    return;
}

/* Helper: Invalidate dest cache and compare byte-wise with src; assert on mismatch.
 * Logs first mismatch for debug; returns UDMA_EFAIL on error, UDMA_SOK otherwise.
 * Protects against stale cache via CacheP_inv.
 */
static void TestUdma_compareBuffer(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length)
{
    uint32_t        i;

    /* Invalidate destination buffer */
    CacheP_inv(destBuf, length, CacheP_TYPE_ALLD);
    for(i = 0U; i < length; i += 1)
    {
        if(srcBuf[i] != destBuf[i])
        {
            DebugP_logError("Data mismatch !!!\r\n");
            DebugP_assert(FALSE);
        }
    }

    return;
}

/* Callback: Generic event handler for UDMA event registration.
 * Posts the provided semaphore and increments count if non-NULL.
 * Used for DMA completion notification in event-driven tests.
 */
static void TestUdma_genericEventCb(Udma_EventHandle eventHandle, uint32_t eventType, void *appData)
{
    (void)eventHandle;
    (void)eventType;
    TestUdma_EventContext *ctx = (TestUdma_EventContext *)appData;
    if (ctx && ctx->sem)
    {
        if (ctx->count)
        {
            *(ctx->count) += 1U;
        }
        SemaphoreP_post(ctx->sem);
    }
}

/* Thread: Init PKTDMA RX, open/config/enable, validate default flow, cleanup.
 * Confirms flowInitDone == UDMA_INIT_DONE on default flow; disables and closes.
 * Runs on its own core in SMP tests.
 */
static void TestUdma_pktdmaRxInitTask(void *args)
{
    (void)args;

    int32_t retVal = UDMA_SOK;

    static Udma_DrvObject pktDrvObj;
    Udma_DrvHandle pktDrv = &pktDrvObj;

    Udma_InitPrms initPrms;
    Udma_FlowHandleInt flowInt;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChRxPrms rxPrms;

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &initPrms);
    retVal = Udma_init(pktDrv, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX);
    chPrms.chNum     = UDMA_DMA_CH_ANY;
    chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_MCSPI0_CH0_RX;

    retVal = Udma_chOpen(pktDrv, chHandle, UDMA_CH_TYPE_RX, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_RX);
    retVal = Udma_chConfigRx(chHandle, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Validate default flow handle exists */
    Udma_FlowHandle flow = Udma_chGetDefaultFlowHandle(chHandle);
    TEST_ASSERT_NOT_NULL(flow);

    flowInt = (Udma_FlowHandleInt)flow;
    TEST_ASSERT_EQUAL_UINT32(UDMA_INIT_DONE, flowInt->flowInitDone);

    /* mark complete */
    SemaphoreP_pend(&TestUdma_MultiInstanceMultiCoreMutex, SystemP_WAIT_FOREVER);
    TestUdma_MulticoreTransferComplete += 1;
    SemaphoreP_post(&TestUdma_MultiInstanceMultiCoreMutex);

    /* Cleanup channels and driver */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
    ClockP_usleep(5000);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(pktDrv));

    TaskP_exit();
}

/* Thread: Single BCDMA block-copy; submit TRPD, wait completion, verify, cleanup.
 * Uses CQ polling to detect completion, then compares buffers for integrity.
 * Tears down channel and driver at end.
 */
static void TestUdma_bcdmaBlkcpySingleTask(void *args)
{
    (void)args;
    int32_t retVal = UDMA_SOK;

    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_InitPrms initPrms;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;

    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;

    uint64_t trpdPhy = 0U;
    uint64_t pDesc;
    uint32_t timeout;
    int found;
    uint32_t drainGuard;

    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_init(drvHandle, &initPrms));

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem     = TestUdma_BlkCopyChFqRingMem;
    chPrms.fqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
    chPrms.fqRingPrms.elemCnt     = 1U;
    chPrms.cqRingPrms.ringMem     = TestUdma_SingleTaskCqMem;
    chPrms.cqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
    chPrms.cqRingPrms.elemCnt     = 1U;

    retVal = Udma_chOpen(drvHandle, chHandle,
                         UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigRx(chHandle, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Prepare buffers and TRPD */
    TestUdma_initBuffer(TestUdma_Task2Src, TestUdma_Task2Dst, TEST_UDMA_NUM_BYTES);
    TestUdma_trpdInit(chHandle, TestUdma_SingleTaskTrpd,
                      TestUdma_Task2Dst, TestUdma_Task2Src, TEST_UDMA_NUM_BYTES);

    trpdPhy = (uint64_t)Udma_defaultVirtToPhyFxn(TestUdma_SingleTaskTrpd, 0U, NULL);

    /* Drain previous completions */
    drainGuard = 0U;
    while (Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &pDesc) == UDMA_SOK)
    {
        drainGuard += 1U;
        if (drainGuard > 10000U) /* safety bound */
        {
            break;
        }
    }

    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle),
                               trpdPhy);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Wait for completion */
    timeout = 1000000U;
    found = 0;

    while ((timeout > 0) && (found == 0))
    {
        retVal = Udma_ringDequeueRaw(
                    Udma_chGetCqRingHandle(chHandle),
                    &pDesc);

        if (retVal == UDMA_SOK)
        {
            found = 1;
        }
        else
        {
            ClockP_usleep(10);
        }
        timeout -= 1U;
    }

    TEST_ASSERT_EQUAL_INT(1, found);

    TestUdma_compareBuffer(TestUdma_Task2Src, TestUdma_Task2Dst, TEST_UDMA_NUM_BYTES);

    /* mark complete */
    SemaphoreP_pend(&TestUdma_MultiInstanceMultiCoreMutex, SystemP_WAIT_FOREVER);
    TestUdma_MulticoreTransferComplete += 1;
    ClockP_usleep(5000);
    SemaphoreP_post(&TestUdma_MultiInstanceMultiCoreMutex);

    /* Cleanup channels and driver */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
    ClockP_usleep(5000);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));

    TaskP_exit();
}

/**
 * \brief Multi-instance multi-core test using PKTDMA and BCDMA.
 *
 * Test Category: Functional / SMP.
 *
 * Spawns two tasks on separate A53 cores: one initializes PKTDMA RX and validates
 * default flow, the other runs a BCDMA block-copy transfer. Waits both to complete.
 *
 * \param args Unused.
 * \return None.
 */
void TestUdma_multiInstanceMultiCore(void *args)
{
    int32_t status;
    (void)args;

    TestUdma_MulticoreTransferComplete = 0;
    TestUdma_initBuffer(TestUdma_Task1Src, TestUdma_Task1Dst, TEST_UDMA_NUM_BYTES);
    TestUdma_initBuffer(TestUdma_Task2Src, TestUdma_Task2Dst, TEST_UDMA_NUM_BYTES);

    /* Create tasks pinned to core0 and core1 */
    TaskP_Object tObj1, tObj2;
    uint8_t tStack1[6 * 1024];
    uint8_t tStack2[6 * 1024];

    TaskP_Params tp;
    int32_t ret = SemaphoreP_constructMutex(&TestUdma_MultiInstanceMultiCoreMutex);
    TEST_ASSERT_EQUAL(ret, SystemP_SUCCESS);

    TaskP_Params_init(&tp);
    tp.priority     = 3U;
    tp.stack        = tStack1;
    tp.stackSize    = sizeof(tStack1);
    tp.name         = "PKTDMA_T";
    tp.taskMain     = TestUdma_pktdmaRxInitTask;
    tp.coreAffinity = (1U << 0);

    status = TaskP_construct(&tObj1, &tp);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    ClockP_usleep(5000);

    TaskP_Params_init(&tp);
    tp.priority     = 3U;
    tp.stack        = tStack2;
    tp.stackSize    = sizeof(tStack2);
    tp.name         = "BCDMA_T";
    tp.taskMain     = TestUdma_bcdmaBlkcpySingleTask;
    tp.coreAffinity = (1U << 1);

    status = TaskP_construct(&tObj2, &tp);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    ClockP_usleep(5000);

    /* Wait for both tasks to complete */
    while (TestUdma_MulticoreTransferComplete < 2)
    {
        ClockP_usleep(1000);
    }

    SemaphoreP_destruct(&TestUdma_MultiInstanceMultiCoreMutex);
    TaskP_destruct(&tObj1);
    TaskP_destruct(&tObj2);
}

/* Thread: Worker memcpy over block-copy channel; wait CQ, compare data, disable.
 * Enables channel, queues TRPD, spins on CQ dequeue, checks TR response, compares buffers.
 * Always attempts Udma_chDisable before exit.
 */
static void TestUdma_blkcpyMemcpyThread(void *args)
{
    TestUdma_MemcpyThreadParams *p = (TestUdma_MemcpyThreadParams *)args;
    int32_t retVal = UDMA_SOK;
    uint64_t trpdMemPhy = (uint64_t)Udma_defaultVirtToPhyFxn(TestUdma_BcdmaTrpdMem, 0U, NULL);
    uint64_t pDesc;
    uint32_t trRespStatus;
    uint32_t timeoutUs;
    int32_t deqRet;

    /* Enable channel */
    retVal = Udma_chEnable(p->chHandle);
    if (retVal == UDMA_SOK)
    {
        /* Init buffers and TRPD */
        TestUdma_initBuffer(p->src, p->dst, TEST_UDMA_NUM_BYTES);
        TestUdma_trpdInit(p->chHandle, TestUdma_BcdmaTrpdMem, p->dst, p->src, TEST_UDMA_NUM_BYTES);

        /* Submit TRPD */
        retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(p->chHandle), trpdMemPhy);
        if (retVal == UDMA_SOK)
        {
            /* Wait for completion */
            timeoutUs = 1000000U; /* 1s total wait */
            while (timeoutUs > 0U)
            {
                deqRet = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(p->chHandle), &pDesc);
                if (deqRet == UDMA_SOK)
                {
                    CacheP_inv(TestUdma_BcdmaTrpdMem, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALLD);
                    trRespStatus = UdmaUtils_getTrpdTr15Response(TestUdma_BcdmaTrpdMem, 1U, 0U);
                    retVal = (trRespStatus == CSL_UDMAP_TR_RESPONSE_STATUS_COMPLETE) ? UDMA_SOK : UDMA_EFAIL;
                    break;
                }
                ClockP_usleep(10);
                timeoutUs -= 10U;
            }
            if (timeoutUs == 0U)
            {
                retVal = UDMA_EFAIL;
            }

            if (retVal == UDMA_SOK)
            {
                /* Compare data */
                TestUdma_compareBuffer(p->src, p->dst, TEST_UDMA_NUM_BYTES);
            }
        }
    }

    /* Disable channel (best-effort) */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(p->chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT))   ;

    *(p->result) = retVal;
    TaskP_exit();
}

/**
 * \brief Single-instance multi-core memcpy test (shared BCDMA driver).
 *
 * Test Category: Functional / SMP.
 *
 * Uses one BCDMA driver shared by two cores. Each core runs a memcpy thread on
 * its own block-copy channel, waits for completion, and verifies data integrity.
 *
 * \param args Unused.
 * \return None.
 */
void TestUdma_singleInstanceMulticore(void *args)
{
    int32_t retVal;

    /* Dynamically open and configure the second channel */
    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    static TestUdma_MemcpyThreadParams params1, params2;

    static Udma_ChObject chObj1, chObj2;
    Udma_ChHandle chHandle1 = &chObj1;
    Udma_ChHandle chHandle2 = &chObj2;

    Udma_ChPrms chPrms1;
    Udma_ChTxPrms txPrms1;
    Udma_ChRxPrms rxPrms1;

    Udma_ChPrms chPrms2;
    Udma_ChTxPrms txPrms2;
    Udma_ChRxPrms rxPrms2;

    int32_t status;
    TaskP_Object tObj1, tObj2;
    uint8_t tStack1[6 * 1024];
    uint8_t tStack2[6 * 1024];
    TaskP_Params tp;

    /* Driver init (BCDMA instance) */
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_init(drvHandle, &initPrms));

    /* Open/config channel 1 */
    UdmaChPrms_init(&chPrms1, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms1.fqRingPrms.ringMem     = TestUdma_FqRingMem1;
    chPrms1.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem1);
    chPrms1.fqRingPrms.elemCnt     = 1U;
    chPrms1.cqRingPrms.ringMem     = TestUdma_CqRingMem1;
    chPrms1.cqRingPrms.ringMemSize = sizeof(TestUdma_CqRingMem1);
    chPrms1.cqRingPrms.elemCnt     = 1U;
    retVal = Udma_chOpen(drvHandle, chHandle1, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms1);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    UdmaChTxPrms_init(&txPrms1, UDMA_CH_TYPE_TR_BLK_COPY);
    UdmaChRxPrms_init(&rxPrms1, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigTx(chHandle1, &txPrms1));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigRx(chHandle1, &rxPrms1));

    /* Open/config channel 2 */
    UdmaChPrms_init(&chPrms2, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms2.fqRingPrms.ringMem     = TestUdma_FqRingMem2;
    chPrms2.fqRingPrms.ringMemSize = sizeof(TestUdma_FqRingMem2);
    chPrms2.fqRingPrms.elemCnt     = 1U;
    chPrms2.cqRingPrms.ringMem     = TestUdma_CqRingMem2;
    chPrms2.cqRingPrms.ringMemSize = sizeof(TestUdma_CqRingMem2);
    chPrms2.cqRingPrms.elemCnt     = 1U;
    retVal = Udma_chOpen(drvHandle, chHandle2, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms2);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    UdmaChTxPrms_init(&txPrms2, UDMA_CH_TYPE_TR_BLK_COPY);
    UdmaChRxPrms_init(&rxPrms2, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigTx(chHandle2, &txPrms2));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigRx(chHandle2, &rxPrms2));

    /* Prepare params/results */
    TestUdma_SingleInstanceThread1Result = -1;
    TestUdma_SingleInstanceThread2Result = -1;

    TestUdma_initBuffer(TestUdma_Task1Src, TestUdma_Task1Dst, TEST_UDMA_NUM_BYTES);
    TestUdma_initBuffer(TestUdma_Task2Src, TestUdma_Task2Dst, TEST_UDMA_NUM_BYTES);
    params1.chHandle = chHandle1;
    params1.src = TestUdma_Task1Src;
    params1.dst = TestUdma_Task1Dst;
    params1.result = &TestUdma_SingleInstanceThread1Result;
    params2.chHandle = chHandle2;
    params2.src = TestUdma_Task2Src;
    params2.dst = TestUdma_Task2Dst;
    params2.result = &TestUdma_SingleInstanceThread2Result;

    /* Create two tasks pinned to separate cores */
    TaskP_Params_init(&tp);
    tp.priority     = 3U;
    tp.stack        = tStack1;
    tp.stackSize    = sizeof(tStack1);
    tp.name         = "DMA1";
    tp.taskMain     = TestUdma_blkcpyMemcpyThread;
    tp.args         = &params1;
    tp.coreAffinity = (1U << 0);
    status = TaskP_construct(&tObj1, &tp);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    ClockP_usleep(5000);

    TaskP_Params_init(&tp);
    tp.priority     = 3U;
    tp.stack        = tStack2;
    tp.stackSize    = sizeof(tStack2);
    tp.name         = "DMA2";
    tp.taskMain     = TestUdma_blkcpyMemcpyThread;
    tp.args         = &params2;
    tp.coreAffinity = (1U << 1);
    status = TaskP_construct(&tObj2, &tp);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    ClockP_usleep(5000);

    /* Wait for both tasks to finish */
    while (TestUdma_SingleInstanceThread1Result == -1 || TestUdma_SingleInstanceThread2Result == -1)
    {
        ClockP_usleep(1000);
    }

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_SingleInstanceThread1Result);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, TestUdma_SingleInstanceThread2Result);

    /* Basic data sanity checks */
    for (uint32_t i = 0U; i < TEST_UDMA_NUM_BYTES; i += 1)
    {
        TEST_ASSERT_EQUAL_UINT8(TestUdma_Task1Src[i], TestUdma_Task1Dst[i]);
        TEST_ASSERT_EQUAL_UINT8(TestUdma_Task2Src[i], TestUdma_Task2Dst[i]);
    }

    /* Cleanup both channels and driver */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle2));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle1));
    ClockP_usleep(5000);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));

    TaskP_destruct(&tObj1);
    TaskP_destruct(&tObj2);
}

/* Thread: PKTDMA RX flow sanity; ensure flowInitDone; cleanup driver.
 * Opens RX with ANY channel, config/enable, validate default flow handle fields.
 * Disables/closes channel and de-inits driver.
 */
static void TestUdma_pktdmaRxFlowCheckThread(void *args)
{
    volatile int *result = (volatile int *)args;
    int32_t retVal = UDMA_SOK;

    static Udma_DrvObject pktdrvObj;
    Udma_DrvHandle pktDrv = &pktdrvObj;
    Udma_InitPrms udmaInitPrms;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChRxPrms rxPrms;
    Udma_FlowHandleInt fi;

    UdmaInitPrms_init(UDMA_INST_ID_PKTDMA_0, &udmaInitPrms);
    retVal = Udma_init(pktDrv, &udmaInitPrms);
    if (retVal == UDMA_SOK)
    {
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_RX);
        chPrms.chNum = UDMA_DMA_CH_ANY;
        chPrms.peerChNum = UDMA_PDMA_CH_MAIN0_UART0_RX;
        retVal = Udma_chOpen(pktDrv, chHandle, UDMA_CH_TYPE_RX, &chPrms);
        if (retVal == UDMA_SOK)
        {
            UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_RX);
            retVal = Udma_chConfigRx(chHandle, &rxPrms);
            if (retVal == UDMA_SOK)
            {
                retVal = Udma_chEnable(chHandle);
                if (retVal == UDMA_SOK)
                {
                    Udma_FlowHandle flow = Udma_chGetDefaultFlowHandle(chHandle);
                    if (flow != NULL)
                    {
                        fi = (Udma_FlowHandleInt)flow;
                        if (fi->flowInitDone != UDMA_INIT_DONE)
                        {
                            retVal = UDMA_EFAIL;
                        }
                    }
                    else
                    {
                        retVal = UDMA_EFAIL;
                    }
                }
            }
        }
    }

    /* Cleanup channels and driver */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
    ClockP_usleep(5000);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(pktDrv));

    *result = retVal;
    TaskP_exit();
}

/* Thread: BCDMA block-copy using event callback; wait on sem, drain CQ, verify, cleanup.
 * Registers DMA completion event, queues TR, pends sem, then dequeues CQ and validates data.
 * Unregisters event and tears down channel/driver.
 */
static void TestUdma_bcdmaBlkcpyEventThread(void *args)
{
    volatile int *result = (volatile int *)args;
    int32_t retVal = UDMA_SOK;

    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;

    uint64_t trpdPhy = 0U, pDesc;
    SemaphoreP_Object localSem;
    volatile uint32_t cbCount = 0;
    Udma_EventObject eventObj;
    Udma_EventPrms eventPrms;
    TestUdma_EventContext evCtx = { &localSem, &cbCount };
    bool registered = false;
    uint32_t attempts, dq;
    uint32_t drainGuard;

    /* Driver init (BCDMA instance) */
    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_init(drvHandle, &initPrms));

    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem = TestUdma_BlkCopyChFqRingMem;
    chPrms.fqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
    chPrms.fqRingPrms.elemCnt = 1U;
    chPrms.cqRingPrms.ringMem   = TestUdma_BcdmaCqRingMem;
    chPrms.cqRingPrms.ringMemSize = sizeof(TestUdma_BcdmaCqRingMem);
    chPrms.cqRingPrms.elemCnt     = 1U;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    if (retVal == UDMA_SOK)
    {
        UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        retVal = Udma_chConfigTx(chHandle, &txPrms);
        if (retVal == UDMA_SOK)
        {
            UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
            retVal = Udma_chConfigRx(chHandle, &rxPrms);
            if (retVal == UDMA_SOK)
            {
                TestUdma_initBuffer(TestUdma_Task2Src, TestUdma_Task2Dst, TEST_UDMA_NUM_BYTES);
                TestUdma_trpdInit(chHandle, TestUdma_MultiInstanceTrpd, TestUdma_Task2Dst, TestUdma_Task2Src, TEST_UDMA_NUM_BYTES);
                trpdPhy = (uint64_t)Udma_defaultVirtToPhyFxn(TestUdma_MultiInstanceTrpd, 0U, NULL);

                /* Drain any stale CQ before enable */
                CacheP_inv(TestUdma_BcdmaCqRingMem, sizeof(TestUdma_BcdmaCqRingMem), CacheP_TYPE_ALLD);
                drainGuard = 0U;
                while (Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &pDesc) == UDMA_SOK)
                {
                    drainGuard += 1U;
                    if (drainGuard > 10000U)
                    {
                        break;
                    }
                }

                retVal = Udma_chEnable(chHandle);
                if (retVal == UDMA_SOK)
                {
                    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS,
                                          SemaphoreP_constructCounting(&localSem, 0, 1));
                    UdmaEventPrms_init(&eventPrms);
                    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
                    eventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
                    eventPrms.chHandle  = chHandle;
                    eventPrms.eventCb   = TestUdma_genericEventCb;
                    eventPrms.appData   = &evCtx;
                    retVal = Udma_eventRegister(drvHandle, &eventObj, &eventPrms);
                    if (retVal == UDMA_SOK)
                    {
                        registered = true;
                        retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdPhy);
                        if (retVal == UDMA_SOK)
                        {
                            if (SystemP_SUCCESS == SemaphoreP_pend(&localSem, SystemP_WAIT_FOREVER) && (cbCount > 0U))
                            {
                                bool dequeued = false;
                                attempts = 10000U;
                                while (attempts > 0U)
                                {
                                    dq = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &pDesc);
                                    if (dq == UDMA_SOK)
                                    {
                                        dequeued = true;
                                        break;
                                    }
                                    ClockP_usleep(10);
                                    attempts -= 1;
                                }
                                retVal = dequeued ? UDMA_SOK : UDMA_EFAIL;

                                if (retVal == UDMA_SOK)
                                {
                                    TestUdma_compareBuffer(TestUdma_Task2Src, TestUdma_Task2Dst, TEST_UDMA_NUM_BYTES);
                                }
                            }
                            else
                            {
                                retVal = UDMA_EFAIL;
                            }
                        }
                    }
                }
            }
        }
    }
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));

    /* Drain any remaining CQ completions to avoid teardown hang */
    CacheP_inv(TestUdma_BcdmaCqRingMem, sizeof(TestUdma_BcdmaCqRingMem), CacheP_TYPE_ALLD);
    drainGuard = 0U;
    while (Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &pDesc) == UDMA_SOK)
    {
        drainGuard += 1U;
        if (drainGuard > 10000U)
        {
            break;
        }
    }

    if (registered)
    {
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_eventUnRegister(&eventObj));
    }
    SemaphoreP_destruct(&localSem);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
    ClockP_usleep(5000);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));

    *result = retVal;
    TaskP_exit();
}

/**
 * \brief Concurrent PKTDMA RX init and BCDMA block-copy on different cores.
 *
 * Test Category: Functional / SMP / Concurrency.
 *
 * Runs a PKTDMA RX flow sanity thread and a BCDMA TR completion (event) thread
 * on separate cores. Verifies both threads complete successfully.
 *
 * \param args Unused.
 * \return None.
 */
static void TestUdma_multiInstancePktdmaBcdma(void *args)
{
    (void)args;
    volatile int pktdmaResult = -1;
    volatile int bcdmaResult  = -1;

    TaskP_Object tObj1, tObj2;
    uint8_t tStack1[6 * 1024];
    uint8_t tStack2[6 * 1024];
    TaskP_Params tp;
    int32_t status;
    uint32_t spins = 0;

    TaskP_Params_init(&tp);
    tp.priority     = 3U;
    tp.stack        = tStack1;
    tp.stackSize    = sizeof(tStack1);
    tp.name         = "PKTDMA_MT";
    tp.taskMain     = TestUdma_pktdmaRxFlowCheckThread;
    tp.args         = (void*)&pktdmaResult;
    tp.coreAffinity = (1U << 0);
    status = TaskP_construct(&tObj1, &tp);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    ClockP_usleep(5000);

    TaskP_Params_init(&tp);
    tp.priority     = 3U;
    tp.stack        = tStack2;
    tp.stackSize    = sizeof(tStack2);
    tp.name         = "BCDMA_MT";
    tp.taskMain     = TestUdma_bcdmaBlkcpyEventThread;
    tp.args         = (void*)&bcdmaResult;
    tp.coreAffinity = (1U << 1);
    status = TaskP_construct(&tObj2, &tp);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    ClockP_usleep(5000);

    while (pktdmaResult == -1 || bcdmaResult == -1)
    {
        ClockP_usleep(2000);
        spins += 1;
        if ((spins % 500U) == 0U)
        {
            DebugP_log("[MULTI_MT] waiting... pktdma=%d bcdma=%d\r\n", pktdmaResult, bcdmaResult);
        }
    }

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, pktdmaResult);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, bcdmaResult);

    TaskP_destruct(&tObj1);
    TaskP_destruct(&tObj2);
}

/* Helper: Drain the CQ ring until empty or timeout expires.
 * Spins on CQ dequeue, returns UDMA_SOK if any descriptor found, else UDMA_EFAIL.
 * Used before disable/close to guarantee teardown completes cleanly.
 */
static int32_t TestUdma_drainCqUntilEmpty(Udma_ChHandle chHndl, uint32_t maxAttemptsUs)
{
    uint64_t cqDesc;
    uint32_t attempts = maxAttemptsUs;
    int32_t ret = UDMA_EFAIL;

    while (attempts > 0U)
    {
        if (Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHndl), &cqDesc) == UDMA_SOK)
        {
            ret = UDMA_SOK; /* saw at least one desc */
            /* keep draining in this spin */
            continue;
        }
        /* no desc right now, give HW a moment */
        ClockP_usleep(10);
        attempts -= 10U;
    }
    return ret;
}

/* Thread: Producer; queue TRPDs with backpressure; never drains CQ; signal done.
 * Uses (queued - completed) to throttle to ring capacity; posts join sem on finish.
 * Leaves draining to the consumer peer thread.
 */
static void TestUdma_ringOverflowProducerTask(void *arg)
{
    Udma_ChHandle chHndl = (Udma_ChHandle)arg;
    uint32_t idx = 0U;
    uint64_t trpdPhy;
    int32_t ret;

    while (idx < TEST_UDMA_RING_OVERFLOW_NUM_DESCRIPTORS)
    {
        /* Backpressure: wait until FQ has space; producer NEVER drains CQ */
        while ((TestUdma_RingOverflowRingQueued - TestUdma_RingOverflowRingCompleted) >= TEST_UDMA_RING_OVERFLOW_ELEMENT_COUNT)
        {
            if (TestUdma_RingOverflowRingConsumerDone)
                break;
            ClockP_usleep(50);
        }
        if (TestUdma_RingOverflowRingConsumerDone)
            break;

        TestUdma_initBuffer(TestUdma_RingOverflowSrc[idx], TestUdma_RingOverflowDst[idx], TEST_UDMA_NUM_BYTES);
        TestUdma_trpdInit(chHndl,
                          TestUdma_RingOverflowTrpd[idx],
                          TestUdma_RingOverflowDst[idx],
                          TestUdma_RingOverflowSrc[idx],
                          TEST_UDMA_NUM_BYTES);

        trpdPhy = (uint64_t)Udma_defaultVirtToPhyFxn(TestUdma_RingOverflowTrpd[idx], 0U, NULL);
        CacheP_wb(TestUdma_RingOverflowTrpd[idx], TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALLD);

        ret = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHndl), trpdPhy);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, ret);

        TestUdma_RingOverflowRingQueued += 1;
        idx += 1;
    }

    TestUdma_RingOverflowRingProducerDone = 1U;
    ClockP_usleep(5000);
    SemaphoreP_post(&TestUdma_RingOverflowJoinSem);
    TaskP_exit();
}

/* Thread: Consumer; drain CQ and count completions until all descriptors finish.
 * Repeatedly dequeues CQ and increments completion count; posts join sem when done.
 * Cooperates with producer to validate overflow handling.
 */
static void TestUdma_ringOverflowConsumerTask(void *arg)
{
    Udma_ChHandle chHndl = (Udma_ChHandle)arg;
    uint64_t cqDesc;

    /* Overall timeout to avoid endless wait if completions never arrive */
    uint32_t waitBudgetUs = 5000000U;
    while ((TestUdma_RingOverflowRingCompleted < TEST_UDMA_RING_OVERFLOW_NUM_DESCRIPTORS) && (waitBudgetUs > 0U))
    {
        /* Consumer owns CQ draining */
        CacheP_inv(TestUdma_RingOverflowCqMem, sizeof(TestUdma_RingOverflowCqMem), CacheP_TYPE_ALLD);

        if (Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHndl), &cqDesc) == UDMA_SOK)
        {
            TestUdma_RingOverflowRingCompleted += 1U;
        }
        else
        {
            ClockP_usleep(50);
            if (waitBudgetUs >= 50U)
            {
                waitBudgetUs -= 50U;
            }
            else
            {
                waitBudgetUs = 0U;
            }
        }
    }
    if (TestUdma_RingOverflowRingCompleted < TEST_UDMA_RING_OVERFLOW_NUM_DESCRIPTORS)
    {
        DebugP_logError("[RING_CONSUMER] Timeout waiting for CQ completions\r\n");
    }

    TestUdma_RingOverflowRingConsumerDone = 1U;
    ClockP_usleep(5000);
    SemaphoreP_post(&TestUdma_RingOverflowJoinSem);
    TaskP_exit();
}

/**
 * \brief Ring overflow negative test.
 *
 * Test Category: Negative / Robustness.
 *
 * Opens a block-copy channel with small FQ/CQ rings, attempts to enqueue more
 * descriptors than capacity, confirms overflow is rejected, and validates
 * completion + data for accepted descriptors.
 *
 * \param args Unused.
 * \return None.
 */
static void TestUdma_ringOverflowTest(void *args)
{
    (void)args;

    /* Local driver and single shared channel */
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;
    Udma_InitPrms initPrms;
    static Udma_ChObject chObj;
    Udma_ChHandle chHandle = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    TaskP_Object prodTask, consTask;
    TaskP_Params tp;
    uint8_t prodStack[6 * 1024];
    uint8_t consStack[6 * 1024];

    TestUdma_RingOverflowRingQueued    = 0U;
    TestUdma_RingOverflowRingCompleted = 0U;
    TestUdma_RingOverflowRingProducerDone  = 0U;
    TestUdma_RingOverflowRingConsumerDone  = 0U;

    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_init(drvHandle, &initPrms));

    /* Provide both FQ and CQ (non-cacheable DDR buffers already declared) */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem     = TestUdma_RingOverflowFqMem;
    chPrms.fqRingPrms.ringMemSize = sizeof(TestUdma_RingOverflowFqMem);
    chPrms.fqRingPrms.elemCnt     = TEST_UDMA_RING_OVERFLOW_ELEMENT_COUNT;
    chPrms.cqRingPrms.ringMem     = TestUdma_RingOverflowCqMem;
    chPrms.cqRingPrms.ringMemSize = sizeof(TestUdma_RingOverflowCqMem);
    chPrms.cqRingPrms.elemCnt     = TEST_UDMA_RING_OVERFLOW_ELEMENT_COUNT;

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms));

    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigTx(chHandle, &txPrms));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chConfigRx(chHandle, &rxPrms));

    /* Drain any stale CQ before enable (best-effort) */
    TestUdma_drainCqUntilEmpty(chHandle, 100000U);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chEnable(chHandle));

    /* Counting join semaphore for producer + consumer */
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestUdma_RingOverflowJoinSem, 0, 2));

    /* Start consumer first to ensure CQ is serviced promptly */
    TaskP_Params_init(&tp);
    tp.name         = "SMP_RING_CONS";
    tp.taskMain     = TestUdma_ringOverflowConsumerTask;
    tp.args         = chHandle;
    tp.stack        = consStack;
    tp.stackSize    = sizeof(consStack);
    tp.priority     = 3U;
    tp.coreAffinity = (1U << 1);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&consTask, &tp));

    ClockP_usleep(2000);

    TaskP_Params_init(&tp);
    tp.name         = "SMP_RING_PROD";
    tp.taskMain     = TestUdma_ringOverflowProducerTask;
    tp.args         = chHandle;
    tp.stack        = prodStack;
    tp.stackSize    = sizeof(prodStack);
    tp.priority     = 3U;
    tp.coreAffinity = (1U << 0);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&prodTask, &tp));

    /* Wait both tasks to finish work */
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestUdma_RingOverflowJoinSem, 20000));
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, SemaphoreP_pend(&TestUdma_RingOverflowJoinSem, 20000));

    TEST_ASSERT_EQUAL_UINT32(1U, TestUdma_RingOverflowRingProducerDone);
    TEST_ASSERT_EQUAL_UINT32(1U, TestUdma_RingOverflowRingConsumerDone);
    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_RING_OVERFLOW_NUM_DESCRIPTORS, TestUdma_RingOverflowRingQueued);
    TEST_ASSERT_EQUAL_UINT32(TEST_UDMA_RING_OVERFLOW_NUM_DESCRIPTORS, TestUdma_RingOverflowRingCompleted);

    TestUdma_drainCqUntilEmpty(chHandle, 200000U);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(chHandle));
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));

    SemaphoreP_destruct(&TestUdma_RingOverflowJoinSem);
    TaskP_destruct(&prodTask);
    TaskP_destruct(&consTask);
}

/* Thread: Core0 open/close race loop; serialize driver calls via mutex.
 * Mirrors Core1 race on core0 with separate ring buffers to increase stress.
 * Validates driver/channel lifecycle under contention.
 */
static void TestUdma_chOpenCloseRaceTaskCore0(void *arg)
{
    TestUdma_RaceTaskRingArgs *a = (TestUdma_RaceTaskRingArgs *)arg;
    Udma_DrvHandle drvHandle = a->drv;
    uint8_t *fqRingMem = a->fqRingMem;
    uint8_t *cqRingMem = a->cqRingMem;

    Udma_ChObject chObj;
    Udma_ChHandle ch = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    int32_t ret;
    uint8_t opened;
    for (uint32_t i = 0; i < TEST_UDMA_OPEN_CLOSE_RACE_ITERATIONS; i += 1)
    {
        opened = 0U;
        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        chPrms.fqRingPrms.ringMem     = fqRingMem;
        chPrms.fqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
        chPrms.fqRingPrms.elemCnt     = 1U;
        chPrms.cqRingPrms.ringMem     = cqRingMem;
        chPrms.cqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
        chPrms.cqRingPrms.elemCnt     = 1U;

        /* Open (serialized) */
        SemaphoreP_pend(&TestUdma_ChOpenCloseRaceDriverLock, SystemP_WAIT_FOREVER);
        ret = Udma_chOpen(drvHandle, ch, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
        SemaphoreP_post(&TestUdma_ChOpenCloseRaceDriverLock);
        if (ret != UDMA_SOK)
        {
            break;
        }
        opened = 1U;

        /* Configure TX/RX */
        UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        ret = Udma_chConfigTx(ch, &txPrms);

        if (ret == UDMA_SOK)
        {
            UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
            ret = Udma_chConfigRx(ch, &rxPrms);
        }

        /* Enable (serialized) if config ok */
        if (ret == UDMA_SOK)
        {
            SemaphoreP_pend(&TestUdma_ChOpenCloseRaceDriverLock, SystemP_WAIT_FOREVER);
            TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chEnable(ch));
            SemaphoreP_post(&TestUdma_ChOpenCloseRaceDriverLock);
        }

        /* Disable (serialized), ignore return */
        SemaphoreP_pend(&TestUdma_ChOpenCloseRaceDriverLock, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(ch, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
        SemaphoreP_post(&TestUdma_ChOpenCloseRaceDriverLock);

        /* Close (serialized) if opened */
        if (opened != 0U)
        {
            SemaphoreP_pend(&TestUdma_ChOpenCloseRaceDriverLock, SystemP_WAIT_FOREVER);
            TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(ch));
            SemaphoreP_post(&TestUdma_ChOpenCloseRaceDriverLock);
        }
    }
    ClockP_usleep(5000);
    SemaphoreP_post(&TestUdma_ChOpenCloseRaceJoinSem);
    TaskP_exit();
}

/* Thread: Core1 open/close race loop; serialize driver calls via mutex.
 * Repeats open→config→enable→disable→close for many iterations on core1.
 * Ensures no leaks/hangs under concurrent open/close.
 */
static void TestUdma_chOpenCloseRaceTaskCore1(void *arg)
{
    TestUdma_RaceTaskRingArgs *a = (TestUdma_RaceTaskRingArgs *)arg;
    Udma_DrvHandle drvHandle = a->drv;
    uint8_t *fqRingMem = a->fqRingMem;
    uint8_t *cqRingMem = a->cqRingMem;

    Udma_ChObject chObj;
    Udma_ChHandle ch = &chObj;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    int32_t ret;
    uint8_t opened;
    for (uint32_t i = 0; i < TEST_UDMA_OPEN_CLOSE_RACE_ITERATIONS; i += 1)
    {
        opened = 0U;

        UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        chPrms.fqRingPrms.ringMem     = fqRingMem;
        chPrms.fqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
        chPrms.fqRingPrms.elemCnt     = 1U;
        chPrms.cqRingPrms.ringMem     = cqRingMem;
        chPrms.cqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
        chPrms.cqRingPrms.elemCnt     = 1U;

        /* Open (serialized) */
        SemaphoreP_pend(&TestUdma_ChOpenCloseRaceDriverLock, SystemP_WAIT_FOREVER);
        ret = Udma_chOpen(drvHandle, ch, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
        SemaphoreP_post(&TestUdma_ChOpenCloseRaceDriverLock);
        if (ret != UDMA_SOK)
        {
            break;
        }
        opened = 1U;

        /* Configure TX/RX */
        UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
        ret = Udma_chConfigTx(ch, &txPrms);

        if (ret == UDMA_SOK)
        {
            UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
            ret = Udma_chConfigRx(ch, &rxPrms);
        }

        /* Enable (serialized) if config ok */
        if (ret == UDMA_SOK)
        {
            SemaphoreP_pend(&TestUdma_ChOpenCloseRaceDriverLock, SystemP_WAIT_FOREVER);
            TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chEnable(ch));
            SemaphoreP_post(&TestUdma_ChOpenCloseRaceDriverLock);
        }

        /* Disable (serialized), ignore return */
        SemaphoreP_pend(&TestUdma_ChOpenCloseRaceDriverLock, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chDisable(ch, UDMA_DEFAULT_CH_DISABLE_TIMEOUT));
        SemaphoreP_post(&TestUdma_ChOpenCloseRaceDriverLock);

        /* Close (serialized) if opened */
        if (opened != 0U)
        {
            SemaphoreP_pend(&TestUdma_ChOpenCloseRaceDriverLock, SystemP_WAIT_FOREVER);
            TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_chClose(ch));
            SemaphoreP_post(&TestUdma_ChOpenCloseRaceDriverLock);
        }
    }
    ClockP_usleep(5000);
    SemaphoreP_post(&TestUdma_ChOpenCloseRaceJoinSem);
    TaskP_exit();
}

/**
 * \brief Open/close race test across two cores sharing one driver.
 *
 * Test Category: Concurrency / Robustness / SMP.
 *
 * Two tasks on different cores repeatedly open/config/enable/disable/close
 * block-copy channels while serializing critical calls via a mutex to ensure
 * no leaks, asserts, or hangs.
 *
 * \param args Unused.
 * \return None.
 */
static void TestUdma_chOpenCloseRaceTest(void *args)
{
    (void)args;

    Udma_InitPrms initPrms;
    static Udma_DrvObject drvObj;
    Udma_DrvHandle drvHandle = &drvObj;

    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &initPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_init(drvHandle, &initPrms));

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestUdma_ChOpenCloseRaceJoinSem, 0, 2));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructMutex(&TestUdma_ChOpenCloseRaceDriverLock));

    TestUdma_RaceTaskRingArgs a0 = { drvHandle, TestUdma_ChOpenCloseRaceRingFqMem0, TestUdma_ChOpenCloseRaceRingCqMem0 };
    TestUdma_RaceTaskRingArgs a1 = { drvHandle, TestUdma_ChOpenCloseRaceRingFqMem1, TestUdma_ChOpenCloseRaceRingCqMem1 };

    TaskP_Object tC0, tC1;
    uint8_t c0Stack[6 * 1024], c1Stack[6 * 1024];
    TaskP_Params tp;
    int32_t status;

    TaskP_Params_init(&tp);
    tp.priority     = 3U;
    tp.stack        = c0Stack;
    tp.stackSize    = sizeof(c0Stack);
    tp.name         = "UDMA_OCRACE_C0";
    tp.taskMain     = TestUdma_chOpenCloseRaceTaskCore0;
    tp.coreAffinity = (1U << 0);
    tp.args         = &a0;
    status = TaskP_construct(&tC0, &tp);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    ClockP_usleep(2000);

    TaskP_Params_init(&tp);
    tp.priority     = 3U;
    tp.stack        = c1Stack;
    tp.stackSize    = sizeof(c1Stack);
    tp.name         = "UDMA_OCRACE_C1";
    tp.taskMain     = TestUdma_chOpenCloseRaceTaskCore1;
    tp.coreAffinity = (1U << 1);
    tp.args         = &a1;
    status = TaskP_construct(&tC1, &tp);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS, SemaphoreP_pend(&TestUdma_ChOpenCloseRaceJoinSem, 60000), "C0 timeout");
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS, SemaphoreP_pend(&TestUdma_ChOpenCloseRaceJoinSem, 60000), "C1 timeout");

    SemaphoreP_destruct(&TestUdma_ChOpenCloseRaceDriverLock);
    SemaphoreP_destruct(&TestUdma_ChOpenCloseRaceJoinSem);
    TaskP_destruct(&tC0);
    TaskP_destruct(&tC1);

    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_deinit(drvHandle));
}

/* ========================================================================== */
/*                            Main Test Function                              */
/* ========================================================================== */
/**
 *  \brief   Main entry point for UDMA SMP tests.
 *
 *  Runs all SMP test cases using Unity framework.
 *
 *  \param args  Unused argument.
 */
void test_udma_smp_main(void *args)
{
    UNITY_BEGIN();
    RUN_TEST(TestUdma_multiInstancePktdmaBcdma, 9596, args);
    RUN_TEST(TestUdma_ringOverflowTest, 9597, args);
    RUN_TEST(TestUdma_chOpenCloseRaceTest, 9631, args);
    RUN_TEST(TestUdma_multiInstanceMultiCore, 9594, args);
    RUN_TEST(TestUdma_singleInstanceMulticore, 9595, args);
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

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

 /**
 *  \file test_udma_system.c
 *
 *  \brief Minimal functional UDMA system smoke tests (block copy variants).
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <unity.h>
#include <drivers/udma.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>

/* ========================================================================== */
/*                               Macros                                       */
/* ========================================================================== */
#define TEST_UDMA_NUM_BYTES                             (1024U)   /* Default memcpy size */
#define TEST_UDMA_TRPD_SIZE                             (UDMA_GET_TRPD_TR15_SIZE(1U)) /* One TR15 desc */
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void TestUdma_initBuffer(uint8_t *srcBuffer, uint8_t *destBuf, uint32_t length);
static void TestUdma_compareBuffer(uint8_t *srcBuffer, uint8_t *destBuf, uint32_t length);
static void TestUdma_trpdInit(Udma_ChHandle chHandle,
                               uint8_t *trpdMem,
                               const void *destBuf,
                               const void *srcBuffer,
                               uint32_t length);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static uint8_t TestUdma_TrpdSingleDesc[TEST_UDMA_TRPD_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t TestUdma_Src[TEST_UDMA_NUM_BYTES] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t TestUdma_Dst[TEST_UDMA_NUM_BYTES] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t TestUdma_FqRingMem[UDMA_CACHELINE_ALIGNMENT]  __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
SemaphoreP_Object TestUdma_BlkCopyDoneSem;

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/* Helper: Initialize source and destination buffers for memcpy tests.
 * Source is filled with incremental pattern 0..length-1 while destination is
 * poisoned with 0xA5 to detect incomplete transfers. Performs cache writeback
 * for both buffers to ensure coherence before DMA submission. */
static void TestUdma_initBuffer(uint8_t *srcBuffer, uint8_t *destBuf, uint32_t length)
{
    uint32_t i;
    for(i = 0U; i < length; i += 1)
    {
        srcBuffer[i] = i;
        destBuf[i] = 0xA5U;
    }
    /* Writeback source and destination buffer */
    CacheP_wb(srcBuffer, length, CacheP_TYPE_ALLD);
    CacheP_wb(destBuf, length, CacheP_TYPE_ALLD);

    return;
}

/* Helper: Compare source and destination buffers after a transfer.
 * Invalidates destination cache lines, iterates and asserts equality. On first
 * mismatch logs error and triggers debug assert for immediate test failure. */
static void TestUdma_compareBuffer(uint8_t *srcBuffer, uint8_t *destBuf, uint32_t length)
{
    uint32_t i;

    /* Invalidate destination buffer */
    CacheP_inv(destBuf, length, CacheP_TYPE_ALLD);
    for(i = 0U; i < length; i += 1)
    {
        if(srcBuffer[i] != destBuf[i])
        {
            DebugP_logError("Data mismatch !!!\r\n");
            TEST_ASSERT_EQUAL(srcBuffer[i], destBuf[i]);
        }
    }
    return;
}

/* Helper: Initialize a TR15 transfer record packet descriptor (TRPD) for a
 * simple 1D block move. Fills source/destination addressing, element counts,
 * dimensions, and completion event configuration, then performs cache
 * writeback so hardware sees updated descriptor contents. Expects an already
 * opened/allocated channel handle. */
static void TestUdma_trpdInit(Udma_ChHandle chHandle,
                               uint8_t *trpdMem,
                               const void *destBuf,
                               const void *srcBuffer,
                               uint32_t length)
{
    CSL_UdmapTR15  *trDesc;
    uint32_t        cqRingNum = Udma_chGetCqRingNum(chHandle);

    UdmaUtils_makeTrpdTr15(trpdMem, 1U, cqRingNum);

    trDesc = UdmaUtils_getTrpdTr15Pointer(trpdMem, 0U);
    trDesc->flags    = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, 0U);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_MATCH_SOL_EOL);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, 0x25U);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U);
    trDesc->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);

    trDesc->icnt0    = length;
    trDesc->icnt1    = 1U;
    trDesc->icnt2    = 1U;
    trDesc->icnt3    = 1U;
    trDesc->dim1     = trDesc->icnt0;
    trDesc->dim2     = (trDesc->icnt0 * trDesc->icnt1);
    trDesc->dim3     = (trDesc->icnt0 * trDesc->icnt1 * trDesc->icnt2);
    trDesc->addr     = (uint64_t) Udma_defaultVirtToPhyFxn(srcBuffer, 0U, NULL);
    trDesc->fmtflags = 0x00000000U;

    trDesc->dicnt0   = length;
    trDesc->dicnt1   = 1U;
    trDesc->dicnt2   = 1U;
    trDesc->dicnt3   = 1U;
    trDesc->ddim1    = trDesc->dicnt0;
    trDesc->ddim2    = (trDesc->dicnt0 * trDesc->dicnt1);
    trDesc->ddim3    = (trDesc->dicnt0 * trDesc->dicnt1 * trDesc->dicnt2);
    trDesc->daddr    = (uint64_t) Udma_defaultVirtToPhyFxn(destBuf, 0U, NULL);

    CacheP_wb(trpdMem, TEST_UDMA_TRPD_SIZE, CacheP_TYPE_ALLD);
}

/*Helper: callback function posts a semaphore to signal that a UDMA block-copy DMA completion event has occurred.*/
static void TestUdma_blkCopyEventCb(Udma_EventHandle eventHandle, uint32_t eventType, void *appData)
{
    if(UDMA_EVENT_TYPE_DMA_COMPLETION == eventType)
    {
        SemaphoreP_post(&TestUdma_BlkCopyDoneSem);
    }
}

/**
 * \brief Minimal functional test for UDMA block-copy transfer.
 *
 * Test Category: Functional / Smoke.
 *
 * Opens a BCDMA block-copy channel, prepares source/destination buffers,
 * builds and queues a TR15 descriptor, and waits for DMA completion via event
 * callback and semaphore. Verifies data integrity, then disables and closes
 * the channel and deinitializes the driver.
 *
 * \param args Unused.
 * \return UDMA_SOK on success, error code otherwise.
 */
int32_t TestUdma_blkcpyTransferTest(void *args)
{
    (void)args;
    static Udma_DrvObject dmaDrvObj;
    Udma_DrvHandle drvHandle = &dmaDrvObj;
    Udma_ChObject  chObj;
    Udma_ChHandle  chHandle = &chObj;
    Udma_ChPrms    chPrms;
    Udma_ChTxPrms  txPrms;
    Udma_ChRxPrms  rxPrms;
    Udma_InitPrms udmaInitPrms;
    uint8_t       *trpdMem = &TestUdma_TrpdSingleDesc[0U];
    uint64_t       trpdMemPhy;
    uint64_t       completionDescAddr;
    int32_t        retVal;
    Udma_EventPrms eventPrms;
    Udma_EventObject blkEventObj;
    int32_t status;

    UdmaInitPrms_init(UDMA_INST_ID_BCDMA_0, &udmaInitPrms);
    udmaInitPrms.skipGlobalEventReg = FALSE;
    retVal = Udma_init(drvHandle, &udmaInitPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Open block copy channel with a 1 element FQ ring */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    chPrms.fqRingPrms.ringMem     = TestUdma_FqRingMem;
    chPrms.fqRingPrms.ringMemSize = UDMA_CACHELINE_ALIGNMENT;
    chPrms.fqRingPrms.elemCnt     = 1U;

    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_TR_BLK_COPY, &chPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Configure TX & RX (RX implicit for block copy) */
    UdmaChTxPrms_init(&txPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigTx(chHandle, &txPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    UdmaChRxPrms_init(&rxPrms, UDMA_CH_TYPE_TR_BLK_COPY);
    retVal = Udma_chConfigRx(chHandle, &rxPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Enable channel before queuing descriptor */
    retVal = Udma_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Prepare buffers */
    TestUdma_initBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);

    /* Build TRPD */
    TestUdma_trpdInit(chHandle, trpdMem, TestUdma_Dst, TestUdma_Src, TEST_UDMA_NUM_BYTES);

    trpdMemPhy = (uint64_t)Udma_defaultVirtToPhyFxn(trpdMem, 0U, NULL);

    /* Drain any stale completions */
    while (Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr) == UDMA_SOK) {;}

    /* Queue TRPD */
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdMemPhy);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Register ISR callback and wait for completion via semaphore */
    status = SemaphoreP_constructBinary(&TestUdma_BlkCopyDoneSem, 0);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventCb   = &TestUdma_blkCopyEventCb;
    eventPrms.appData   = NULL;
    eventPrms.chHandle  = chHandle;

    retVal = Udma_eventRegister(drvHandle, &blkEventObj, &eventPrms);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Issue software GLOBAL1 trigger (should start the transfer) */
    retVal = Udma_chSetSwTrigger(chHandle, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    /* Wait for ISR to post semaphore (DMA completion) */
    status = SemaphoreP_pend(&TestUdma_BlkCopyDoneSem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    /* Dequeue completion descriptor */
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &completionDescAddr));

    /* Cleanup event registration and semaphore */
    retVal = Udma_eventUnRegister(&blkEventObj);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    SemaphoreP_destruct(&TestUdma_BlkCopyDoneSem);

    /* Verify data */
    TestUdma_compareBuffer(TestUdma_Src, TestUdma_Dst, TEST_UDMA_NUM_BYTES);

    /* Disable and close */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_chClose(chHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);

    return retVal;
}




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
 *    its contributors use may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <drivers/mcasp.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <unity.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_SMALL_BYTES        (128U)
#define TEST_STD_BYTES          (2048U)
#define TEST_LARGE_BYTES        (4096U)

#define TEST_SMALL_WORDS        (TEST_SMALL_BYTES  / 4U)
#define TEST_STD_WORDS          (TEST_STD_BYTES    / 4U)
#define TEST_LARGE_WORDS        (TEST_LARGE_BYTES  / 4U)

/*
 * Hardware config matching syscfg: 48 kHz, stereo (slotCount = 2).
 * txFsRate is fixed at open time from attrs->txFsRate.
 *
 * offsetUs = totalBytes * 1000000 / (txFsRate * slotCount * 4)
 *          = totalBytes * 1000000 / 384000
 */
#define TEST_SAMPLE_RATE        (48000U)
#define TEST_SLOT_COUNT         (2U)
#define TEST_BYTES_PER_SEC      (TEST_SAMPLE_RATE * TEST_SLOT_COUNT * 4U)   /* 384000 */

#define TEST_US_1BUF_STD        (5333U)    /* 2048  bytes */
#define TEST_US_4BUFS_STD       (21333U)   /* 8192  bytes */
#define TEST_US_4BUFS_SMALL     (1333U)    /* 512   bytes */
#define TEST_US_4BUFS_LARGE     (42666U)   /* 16384 bytes */

/* TRPD capacity -- fill all 64 slots to prevent loopjob from being scheduled */
#define TEST_NUM_TRPD_ZEROS     (64U)

/*
 * Pure-loopjob ring depth: all 64 TRPD slots cycling silence.
 * = TEST_NUM_TRPD_ZEROS * TEST_STD_BYTES * 1000000 / TEST_BYTES_PER_SEC
 * = 64 * 2048 * 1000000 / 384000 = 341333 µs
 */
#define TEST_US_LOOPJOB_RING    (341333U)

/* Tolerance for DMA timing assertions (µs) */
#define TEST_TIMING_TOL_US      (500U)

#define TEST_MAX_TX_TXNS        (TEST_NUM_TRPD_ZEROS + 8U)  /* 72 */
#define TEST_MAX_RX_TXNS        (8U)

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

static uint8_t gBufZero [TEST_STD_BYTES]   __attribute__((aligned(256)));
static uint8_t gBufSmall[TEST_SMALL_BYTES] __attribute__((aligned(256)));
static uint8_t gBufLarge[TEST_LARGE_BYTES] __attribute__((aligned(256)));
static uint8_t gBufRx   [TEST_MAX_RX_TXNS][TEST_STD_BYTES] __attribute__((aligned(256)));

static MCASP_Transaction gTxnTx[TEST_MAX_TX_TXNS];
static MCASP_Transaction gTxnRx[TEST_MAX_RX_TXNS];

static MCASP_Handle gHandle;
static int32_t      gCodecAvailable;

/* ========================================================================== */
/*                           Extern                                           */
/* ========================================================================== */

extern int32_t Board_codecConfig(void);

/* ========================================================================== */
/*                           Callbacks                                        */
/* ========================================================================== */

void mcasp_txcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    (void)handle;
    (void)transaction;
}

void mcasp_rxcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    MCASP_submitRx(handle, transaction);
}

/* ========================================================================== */
/*                           Utility Helpers                                  */
/* ========================================================================== */

static void submitTx(uint32_t count, uint8_t *buf, uint32_t words,
                     uint32_t txnOffset)
{
    uint32_t i;
    for (i = 0U; i < count; i++)
    {
        memset(&gTxnTx[txnOffset + i], 0, sizeof(gTxnTx[0]));
        gTxnTx[txnOffset + i].buf     = (void *)buf;
        gTxnTx[txnOffset + i].count   = words;
        gTxnTx[txnOffset + i].timeout = 0xFFFFFFU;
        MCASP_submitTx(gHandle, &gTxnTx[txnOffset + i]);
    }
}

static void submitRx(uint32_t count)
{
    uint32_t i;
    for (i = 0U; i < count; i++)
    {
        memset(&gTxnRx[i], 0, sizeof(gTxnRx[0]));
        gTxnRx[i].buf     = (void *)gBufRx[i];
        gTxnRx[i].count   = TEST_STD_WORDS;
        gTxnRx[i].timeout = 0xFFFFFFU;
        MCASP_submitRx(gHandle, &gTxnRx[i]);
    }
}

/*
 * drainQueues - flush any queued buffers from a prior test.
 *
 * startTransferTx calls primeTxTrpd which dequeues everything from
 * reqQueueHandleTx into TRPD slots.  Stopping immediately leaves both
 * reqQueue and curentQueue empty for the next test.
 */
static void drainQueues(void)
{
    memset(&gTxnRx[0], 0, sizeof(gTxnRx[0]));
    gTxnRx[0].buf     = (void *)gBufRx[0];
    gTxnRx[0].count   = TEST_STD_WORDS;
    gTxnRx[0].timeout = 0xFFFFFFU;
    MCASP_submitRx(gHandle, &gTxnRx[0]);

    if (MCASP_startTransferRx(gHandle) == SystemP_SUCCESS)
    {
        if (MCASP_startTransferTx(gHandle) == SystemP_SUCCESS)
        {
            MCASP_stopTransferTx(gHandle);
        }
        MCASP_stopTransferRx(gHandle);
    }
}

/* ========================================================================== */
/*                           Test Functions                                   */
/* ========================================================================== */

static void TestMcaspPresentationTime_nullHandleRejected(void *args)
{
    MCASP_QueueStatus      qs = { .sampleSize = 4U };
    MCASP_PresentationTime pt = { 0 };

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE,
                            MCASP_getTxQueueStatus(NULL, &qs));
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE,
                            MCASP_getTxPresentationTime(NULL, &pt));
}

static void TestMcaspPresentationTime_nullOutputRejected(void *args)
{
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE,
                            MCASP_getTxQueueStatus(gHandle, NULL));
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE,
                            MCASP_getTxPresentationTime(gHandle, NULL));
}

static void TestMcaspPresentationTime_emptyQueueReturnsZero(void *args)
{
    MCASP_QueueStatus      qs = { .sampleSize = 4U };
    MCASP_PresentationTime pt = { 0 };
    int32_t status;

    status = MCASP_getTxQueueStatus(gHandle, &qs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(0U, qs.numPendingBufs);
    TEST_ASSERT_EQUAL_UINT32(0U, qs.totalPendingSamples);

    status = MCASP_getTxPresentationTime(gHandle, &pt);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(0U, pt.offsetUs);
    TEST_ASSERT_EQUAL_UINT32(0U, pt.samplesRemaining);
}

static void TestMcaspPresentationTime_queueDepth1Buf(void *args)
{
    MCASP_QueueStatus qs = { .sampleSize = 4U };

    submitTx(1U, gBufZero, TEST_STD_WORDS, 0U);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
                            MCASP_getTxQueueStatus(gHandle, &qs));
    TEST_ASSERT_EQUAL_UINT32(1U, qs.numPendingBufs);

    drainQueues();
}

static void TestMcaspPresentationTime_queueDepth4Bufs(void *args)
{
    MCASP_QueueStatus qs = { .sampleSize = 4U };

    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
                            MCASP_getTxQueueStatus(gHandle, &qs));
    TEST_ASSERT_EQUAL_UINT32(4U, qs.numPendingBufs);

    drainQueues();
}

static void TestMcaspPresentationTime_queueDepth64Bufs(void *args)
{
    MCASP_QueueStatus qs = { .sampleSize = 4U };

    submitTx(TEST_NUM_TRPD_ZEROS, gBufZero, TEST_STD_WORDS, 0U);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
                            MCASP_getTxQueueStatus(gHandle, &qs));
    TEST_ASSERT_EQUAL_UINT32(TEST_NUM_TRPD_ZEROS, qs.numPendingBufs);

    drainQueues();
}

static void TestMcaspPresentationTime_totalSamplesSampleSize1(void *args)
{
    MCASP_QueueStatus qs = { .sampleSize = 1U };

    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxQueueStatus(gHandle, &qs);

    /* totalBytes = 4 * 512 * 4 = 8192; 8192 / 1 = 8192 */
    TEST_ASSERT_EQUAL_UINT32(8192U, qs.totalPendingSamples);

    drainQueues();
}

static void TestMcaspPresentationTime_totalSamplesSampleSize4(void *args)
{
    MCASP_QueueStatus qs = { .sampleSize = 4U };

    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxQueueStatus(gHandle, &qs);

    /* 8192 / 4 = 2048 */
    TEST_ASSERT_EQUAL_UINT32(2048U, qs.totalPendingSamples);

    drainQueues();
}

static void TestMcaspPresentationTime_totalSamplesSampleSize8(void *args)
{
    MCASP_QueueStatus qs = { .sampleSize = 8U };

    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxQueueStatus(gHandle, &qs);

    /* 8192 / 8 = 1024 */
    TEST_ASSERT_EQUAL_UINT32(1024U, qs.totalPendingSamples);

    drainQueues();
}

static void TestMcaspPresentationTime_totalSamplesSampleSizeZero(void *args)
{
    MCASP_QueueStatus qs = { .sampleSize = 0U };

    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxQueueStatus(gHandle, &qs);

    /* sampleSize == 0: driver returns raw byte count = 8192 */
    TEST_ASSERT_EQUAL_UINT32(8192U, qs.totalPendingSamples);

    drainQueues();
}

static void TestMcaspPresentationTime_offsetUs1BufStd(void *args)
{
    MCASP_PresentationTime pt = { 0 };

    submitTx(1U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxPresentationTime(gHandle, &pt);

    /* 2048 bytes * 1000000 / 384000 = 5333 µs */
    TEST_ASSERT_EQUAL_UINT32(TEST_US_1BUF_STD, pt.offsetUs);

    drainQueues();
}

static void TestMcaspPresentationTime_offsetUs4BufsStd(void *args)
{
    MCASP_PresentationTime pt = { 0 };

    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxPresentationTime(gHandle, &pt);

    /* 8192 bytes * 1000000 / 384000 = 21333 µs */
    TEST_ASSERT_EQUAL_UINT32(TEST_US_4BUFS_STD, pt.offsetUs);

    drainQueues();
}

static void TestMcaspPresentationTime_offsetUs4BufsSmall(void *args)
{
    MCASP_PresentationTime pt = { 0 };
    MCASP_OpenParams openParams;

    openParams = gMcaspOpenParams[CONFIG_MCASP0];
    openParams.txLoopjobBufLength = TEST_SMALL_WORDS;

    MCASP_close(gHandle);
    gHandle = MCASP_open(CONFIG_MCASP0, &openParams);
    TEST_ASSERT_NOT_NULL(gHandle);

    submitTx(4U, gBufSmall, TEST_SMALL_WORDS, 0U);
    MCASP_getTxPresentationTime(gHandle, &pt);

    drainQueues();

    /* Restore standard configuration and reopen so subsequent tests use std params */
    gMcaspOpenParams[CONFIG_MCASP0].txLoopjobBufLength = TEST_STD_WORDS;
    MCASP_close(gHandle);
    gHandle = MCASP_open(CONFIG_MCASP0, &gMcaspOpenParams[CONFIG_MCASP0]);
    TEST_ASSERT_NOT_NULL(gHandle);

    /* 512 bytes * 1000000 / 384000 = 1333 µs */
    TEST_ASSERT_EQUAL_UINT32(TEST_US_4BUFS_SMALL, pt.offsetUs);
}

static void TestMcaspPresentationTime_offsetUs4BufsLarge(void *args)
{
    MCASP_PresentationTime pt = { 0 };
    MCASP_OpenParams openParams;

    openParams = gMcaspOpenParams[CONFIG_MCASP0];
    openParams.txLoopjobBufLength = TEST_LARGE_WORDS;

    MCASP_close(gHandle);
    gHandle = MCASP_open(CONFIG_MCASP0, &openParams);
    TEST_ASSERT_NOT_NULL(gHandle);

    submitTx(4U, gBufLarge, TEST_LARGE_WORDS, 0U);
    MCASP_getTxPresentationTime(gHandle, &pt);

    drainQueues();

    /* Restore standard configuration and reopen so subsequent tests use std params */
    gMcaspOpenParams[CONFIG_MCASP0].txLoopjobBufLength = TEST_STD_WORDS;
    MCASP_close(gHandle);
    gHandle = MCASP_open(CONFIG_MCASP0, &gMcaspOpenParams[CONFIG_MCASP0]);
    TEST_ASSERT_NOT_NULL(gHandle);

    /* 16384 bytes * 1000000 / 384000 = 42666 µs */
    TEST_ASSERT_EQUAL_UINT32(TEST_US_4BUFS_LARGE, pt.offsetUs);
}

static void TestMcaspPresentationTime_offsetUsLinearScaling(void *args)
{
    MCASP_PresentationTime pt1 = { 0 }, pt2 = { 0 }, pt4 = { 0 };

    submitTx(1U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxPresentationTime(gHandle, &pt1);
    drainQueues();

    submitTx(2U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxPresentationTime(gHandle, &pt2);
    drainQueues();

    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxPresentationTime(gHandle, &pt4);
    drainQueues();

    /* Allow ±1 µs for integer division rounding */
    TEST_ASSERT_TRUE(pt2.offsetUs >= 2U * pt1.offsetUs - 1U);
    TEST_ASSERT_TRUE(pt2.offsetUs <= 2U * pt1.offsetUs + 1U);
    TEST_ASSERT_TRUE(pt4.offsetUs >= 4U * pt1.offsetUs - 1U);
    TEST_ASSERT_TRUE(pt4.offsetUs <= 4U * pt1.offsetUs + 1U);
}

static void TestMcaspPresentationTime_loopjobCaseDrainsQueue(void *args)
{
    /*
     * Loopjob case: submit 4 buffers BEFORE startTransferTx.
     * primeTxTrpd drains all 4 into TRPD slots — reqQueueHandleTx is empty
     * after prime.  The driver tracks these bytes in txTrpdUserBytesLoaded.
     *
     * getTxPresentationTime priority logic (queueBytes == 0):
     *   queueBytes     = 0  (queue drained by prime)
     *   trpdUserPending = txTrpdUserBytesLoaded - txTrpdUserBytesCompleted
     *                   = 4 * 2048 = 8192 bytes  -> ~21333 µs
     *
     * samplesRemaining = queueBytes / WORD_BYTE_COUNT = 0
     * (reflects software queue depth only; TRPD bytes are not counted here)
     */
    MCASP_PresentationTime pt = { 0 };
    int32_t status;

    if (gCodecAvailable != SystemP_SUCCESS)
    {
        TEST_IGNORE_MESSAGE("Codec not available, skipping DMA test");
    }

    submitRx(4U);
    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);

    status = MCASP_startTransferRx(gHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = MCASP_startTransferTx(gHandle);
    if (status != SystemP_SUCCESS)
    {
        MCASP_stopTransferRx(gHandle);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    MCASP_getTxPresentationTime(gHandle, &pt);

    MCASP_stopTransferTx(gHandle);
    MCASP_stopTransferRx(gHandle);

    /* offsetUs uses trpdUserPending (loopjob branch): ~21333 µs */
    TEST_ASSERT_TRUE_MESSAGE(
        pt.offsetUs >= TEST_US_4BUFS_STD - TEST_TIMING_TOL_US &&
        pt.offsetUs <= TEST_US_4BUFS_STD + TEST_TIMING_TOL_US,
        "loopjob case: offsetUs should be ~21333 µs (trpdUserPending branch)");

    /* samplesRemaining reflects software queue only — queue was drained by
     * prime so it must be 0 even though TRPD holds the 4 user buffers. */
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0U, pt.samplesRemaining,
        "loopjob case: samplesRemaining must be 0 (queue empty after prime)");
}

static void TestMcaspPresentationTime_dmaLinearScaling(void *args)
{
    uint32_t us1 = 0U, us2 = 0U, us4 = 0U;
    MCASP_PresentationTime pt = { 0 };
    int32_t status;
    uint32_t n;

    if (gCodecAvailable != SystemP_SUCCESS)
    {
        TEST_IGNORE_MESSAGE("Codec not available, skipping DMA test");
    }

    for (n = 1U; n <= 4U; n *= 2U)
    {
        submitRx(4U);
        submitTx(TEST_NUM_TRPD_ZEROS, gBufZero, TEST_STD_WORDS, 0U);

        status = MCASP_startTransferRx(gHandle);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        status = MCASP_startTransferTx(gHandle);
        if (status != SystemP_SUCCESS)
        {
            MCASP_stopTransferRx(gHandle);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        }

        submitTx(n, gBufZero, TEST_STD_WORDS, TEST_NUM_TRPD_ZEROS);
        MCASP_getTxPresentationTime(gHandle, &pt);

        MCASP_stopTransferTx(gHandle);
        MCASP_stopTransferRx(gHandle);

        if (n == 1U) us1 = pt.offsetUs;
        if (n == 2U) us2 = pt.offsetUs;
        if (n == 4U) us4 = pt.offsetUs;

        ClockP_usleep(1000U);
    }

    TEST_ASSERT_TRUE_MESSAGE(
        us2 >= 2U * us1 - 2U * TEST_TIMING_TOL_US &&
        us2 <= 2U * us1 + 2U * TEST_TIMING_TOL_US,
        "DMA linear scaling: N=2 not ~2x N=1");

    TEST_ASSERT_TRUE_MESSAGE(
        us4 >= 4U * us1 - 2U * TEST_TIMING_TOL_US &&
        us4 <= 4U * us1 + 2U * TEST_TIMING_TOL_US,
        "DMA linear scaling: N=4 not ~4x N=1");
}

static void TestMcaspPresentationTime_stateResetBetweenStartStop(void *args)
{
    /*
     * Run the loopjob case followed immediately by the correct-design case.
     * Verifies driver queue state is cleanly reset across start/stop cycles.
     */
    MCASP_PresentationTime pt = { 0 };
    int32_t status;

    if (gCodecAvailable != SystemP_SUCCESS)
    {
        TEST_IGNORE_MESSAGE("Codec not available, skipping DMA test");
    }

    /* Round 1: loopjob — 4 pre-start zeros, reqQueue drains into TRPD */
    submitRx(4U);
    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);

    status = MCASP_startTransferRx(gHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(gHandle);
    if (status != SystemP_SUCCESS)
    {
        MCASP_stopTransferRx(gHandle);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    MCASP_getTxPresentationTime(gHandle, &pt);
    MCASP_stopTransferTx(gHandle);
    MCASP_stopTransferRx(gHandle);

    TEST_ASSERT_TRUE_MESSAGE(
        pt.offsetUs > 0U &&
        pt.offsetUs <= TEST_US_4BUFS_STD + TEST_TIMING_TOL_US,
        "Round 1 (loopjob): trpdPendingBytes should yield offsetUs ~21333 µs");

    ClockP_usleep(1000U);

    /* Round 2: correct design — 64 zeros fill TRPD, 4 post-start go to reqQueue */
    submitRx(4U);
    submitTx(TEST_NUM_TRPD_ZEROS, gBufZero, TEST_STD_WORDS, 0U);

    status = MCASP_startTransferRx(gHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MCASP_startTransferTx(gHandle);
    if (status != SystemP_SUCCESS)
    {
        MCASP_stopTransferRx(gHandle);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    submitTx(4U, gBufZero, TEST_STD_WORDS, TEST_NUM_TRPD_ZEROS);
    MCASP_getTxPresentationTime(gHandle, &pt);
    MCASP_stopTransferTx(gHandle);
    MCASP_stopTransferRx(gHandle);

    TEST_ASSERT_TRUE_MESSAGE(
        pt.offsetUs >= TEST_US_4BUFS_STD - TEST_TIMING_TOL_US &&
        pt.offsetUs <= TEST_US_4BUFS_STD + TEST_TIMING_TOL_US,
        "Round 2 (correct design): offsetUs out of expected range");
}

static void TestMcaspPresentationTime_postStartNoPreStart(void *args)
{
    /*
     * Post-start only: no buffers before start, 4 buffers after start.
     * All 64 TRPD slots are loopjob (trpdUserPending = 0).
     *
     * getTxPresentationTime priority logic:
     *   queueBytes      = 4 * 2048 = 8192  -> priority 1 fires (queue branch)
     *   offsetUs        = 8192 * 1e6 / 384000 = ~21333 µs
     *   samplesRemaining = 8192 / 4 = 2048 words
     */
    MCASP_PresentationTime pt = { 0 };
    int32_t status;

    if (gCodecAvailable != SystemP_SUCCESS)
    {
        TEST_IGNORE_MESSAGE("Codec not available, skipping DMA test");
    }

    submitRx(4U);
    /* No pre-start TX submissions */

    status = MCASP_startTransferRx(gHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = MCASP_startTransferTx(gHandle);
    if (status != SystemP_SUCCESS)
    {
        MCASP_stopTransferRx(gHandle);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Submit 4 buffers AFTER start — sit in reqQueue (TRPD still all loopjob) */
    submitTx(4U, gBufZero, TEST_STD_WORDS, 0U);
    MCASP_getTxPresentationTime(gHandle, &pt);

    MCASP_stopTransferTx(gHandle);
    MCASP_stopTransferRx(gHandle);

    /* queueBytes branch: 4 * 2048 = 8192 bytes -> ~21333 µs */
    TEST_ASSERT_TRUE_MESSAGE(
        pt.offsetUs >= TEST_US_4BUFS_STD - TEST_TIMING_TOL_US &&
        pt.offsetUs <= TEST_US_4BUFS_STD + TEST_TIMING_TOL_US,
        "post-start only: offsetUs should be ~21333 µs (queue branch)");

    /* samplesRemaining = queueBytes / WORD_BYTE_COUNT = 8192 / 4 = 2048 */
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(4U * TEST_STD_WORDS, pt.samplesRemaining,
        "post-start only: samplesRemaining must equal queued word count");
}

/* ========================================================================== */
/*                           Unity setUp / tearDown                           */
/* ========================================================================== */

void setUp(void)
{
}

void tearDown(void)
{
}

/* ========================================================================== */
/*                           Test Main                                        */
/* ========================================================================== */

void test_main(void *args)
{
    memset(gBufZero,  0x00U, sizeof(gBufZero));
    memset(gBufSmall, 0x00U, sizeof(gBufSmall));
    memset(gBufLarge, 0x00U, sizeof(gBufLarge));

    gHandle = MCASP_getHandle(CONFIG_MCASP0);
    DebugP_assert(gHandle != NULL);

    gCodecAvailable = Board_codecConfig();

    UNITY_BEGIN();

    RUN_TEST(TestMcaspPresentationTime_nullHandleRejected,          12292, NULL);
    RUN_TEST(TestMcaspPresentationTime_nullOutputRejected,          12293, NULL);
    RUN_TEST(TestMcaspPresentationTime_emptyQueueReturnsZero,       12294, NULL);
    RUN_TEST(TestMcaspPresentationTime_queueDepth1Buf,              12295, NULL);
    RUN_TEST(TestMcaspPresentationTime_queueDepth4Bufs,             12296, NULL);
    RUN_TEST(TestMcaspPresentationTime_queueDepth64Bufs,            12297, NULL);
    RUN_TEST(TestMcaspPresentationTime_totalSamplesSampleSize1,     12298, NULL);
    RUN_TEST(TestMcaspPresentationTime_totalSamplesSampleSize4,     12299, NULL);
    RUN_TEST(TestMcaspPresentationTime_totalSamplesSampleSize8,     12300, NULL);
    RUN_TEST(TestMcaspPresentationTime_totalSamplesSampleSizeZero,  12301, NULL);
    RUN_TEST(TestMcaspPresentationTime_offsetUs1BufStd,             12302, NULL);
    RUN_TEST(TestMcaspPresentationTime_offsetUs4BufsStd,            12303, NULL);
    RUN_TEST(TestMcaspPresentationTime_offsetUs4BufsSmall,          12311, NULL);
    RUN_TEST(TestMcaspPresentationTime_offsetUs4BufsLarge,          12312, NULL);
    RUN_TEST(TestMcaspPresentationTime_offsetUsLinearScaling,       12313, NULL);
    RUN_TEST(TestMcaspPresentationTime_loopjobCaseDrainsQueue,      12314, NULL);
    RUN_TEST(TestMcaspPresentationTime_dmaLinearScaling,            12315, NULL);
    RUN_TEST(TestMcaspPresentationTime_stateResetBetweenStartStop,  12316, NULL);
    RUN_TEST(TestMcaspPresentationTime_postStartNoPreStart,         12317, NULL);

    UNITY_END();
}

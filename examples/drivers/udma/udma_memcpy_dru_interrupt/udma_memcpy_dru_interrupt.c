/*
 *  Copyright (C) 2021-2025 Texas Instruments Incorporated
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
 * This example performs UDMA DRU (Direct Resource Utilization) block copy
 * transfer using Type 9 Transfer Record (TR9) in interrupt mode.
 *
 * The application opens and configures a DRU UTC channel in Direct TR mode.
 * DRU completion events route through the C7x-local CLEC rather than the
 * DMASS0 Interrupt Aggregator, so Udma_eventRegister cannot be used.
 * Instead, a HwiP is registered directly on the CLEC output event;
 * HwiP_construct internally calls HwiP_configClec to set up the routing.
 * The callback App_druEventCb is registered equivalently to App_udmaEventCb
 * in the non-DRU interrupt example.
 *
 * The DRU queue scheduler CONSECUTIVE_TRANS field resets to 0 (queue
 * disabled); all queues must be explicitly configured before submitting TRs.
 *
 * TR type: only TR8–TR11 are supported by the C7x-local DRU (trTypeSupported
 * = 0xF00). TR9 (4D Block Move with Repacking) is used here.
 *
 * TR submission uses direct 64-bit writes to CHCORE[ch].CORE[0] with
 * TRIGGER_NONE so that execution starts immediately when word 0 is written.
 */

#include <string.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/udma.h>
#include <drivers/hw_include/dru/v2/csl_dru.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* Number of bytes to do memcpy */
#define UDMA_TEST_NUM_BYTES             (1024U)

/* DRU local event start for J722S (DRU_LOCAL_EVENT_START_DEFAULT) */
#define DRU_LOCAL_EVENT_START           (128U)

/* Application Buffers */
uint8_t gUdmaTestSrcBuf[UDMA_ALIGN_SIZE(UDMA_TEST_NUM_BYTES)]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
uint8_t gUdmaTestDestBuf[UDMA_ALIGN_SIZE(UDMA_TEST_NUM_BYTES)]
    __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

/* Semaphore to indicate transfer completion */
static SemaphoreP_Object gUdmaTestDoneSem;

/* HwiP object for DRU completion */
static HwiP_Object gUdmaTestHwiObj;

/* Channel object */
static Udma_ChObject gUdmaDruChObj;

void App_druEventCb(void *args);
static void App_udmaInitBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length);
static void App_udmaCompareBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length);
static void App_druBuildTr(CSL_UdmapTR15 *tr, const void *srcBuf,
                           const void *destBuf, uint32_t length);

void *udma_memcpy_dru_interrupt_main(void *args)
{
    int32_t         retVal = UDMA_SOK, status;
    Udma_DrvHandle  drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChHandle   chHandle  = (Udma_ChHandle)&gUdmaDruChObj;
    uint8_t        *srcBuf  = &gUdmaTestSrcBuf[0U];
    uint8_t        *destBuf = &gUdmaTestDestBuf[0U];
    uint32_t        length  = UDMA_TEST_NUM_BYTES;
    Udma_ChPrms     chPrms;
    Udma_ChUtcPrms  utcPrms;
    CSL_UdmapTR15   tr;
    uint32_t        druChNum;
    HwiP_Params     hwiPrms;

    DebugP_log("[UDMA] Memcpy DRU application started ...\r\n");

    status = SemaphoreP_constructBinary(&gUdmaTestDoneSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Open UTC channel */
    UdmaChPrms_init(&chPrms, UDMA_CH_TYPE_UTC);
    chPrms.utcId = UDMA_UTC_ID_MSMC_DRU0;
    retVal = Udma_chOpen(drvHandle, chHandle, UDMA_CH_TYPE_UTC, &chPrms);
    DebugP_assert(UDMA_SOK == retVal);

    /* Configure DRU channel for Direct TR mode */
    UdmaChUtcPrms_init(&utcPrms);
    utcPrms.druOwner   = CSL_DRU_OWNER_DIRECT_TR;
    utcPrms.druQueueId = UDMA_DEFAULT_UTC_DRU_QUEUE_ID;
    retVal = Udma_chConfigUtc(chHandle, &utcPrms);
    DebugP_assert(UDMA_SOK == retVal);

    /* Channel enable */
    retVal = Udma_chEnable(chHandle);
    DebugP_assert(UDMA_SOK == retVal);

    /* Register completion event via HwiP.
     * HwiP_construct calls HwiP_configClec internally to route
     * DRU local event (128 + druChNum) to C7x event (druChNum + 32). */
    druChNum = Udma_chGetNum(chHandle);
    HwiP_Params_init(&hwiPrms);
    hwiPrms.eventId  = DRU_LOCAL_EVENT_START + druChNum;
    hwiPrms.intNum   = druChNum + 32U;
    hwiPrms.callback = App_druEventCb;
    status = HwiP_construct(&gUdmaTestHwiObj, &hwiPrms);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Init buffers and TR */
    App_udmaInitBuf(srcBuf, destBuf, length);
    App_druBuildTr(&tr, srcBuf, destBuf, length);

    /* Submit TR to DMA channel */
    Udma_chDruSubmitTr(chHandle, (const CSL_UdmapTR *)&tr);

    /* Wait for completion */
    SemaphoreP_pend(&gUdmaTestDoneSem, SystemP_WAIT_FOREVER);

    /* Compare data */
    App_udmaCompareBuf(srcBuf, destBuf, length);

    /* Channel disable and close */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    DebugP_assert(UDMA_SOK == retVal);
    retVal = Udma_chClose(chHandle);
    DebugP_assert(UDMA_SOK == retVal);

    HwiP_destruct(&gUdmaTestHwiObj);
    SemaphoreP_destruct(&gUdmaTestDoneSem);

    DebugP_log("All tests have passed!!\r\n");

    return NULL;
}

void App_druEventCb(void *args)
{
    SemaphoreP_post(&gUdmaTestDoneSem);
}

static void App_udmaInitBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length)
{
    uint32_t i;

    for(i = 0U; i < length; i++)
    {
        srcBuf[i]  = (uint8_t)(i & 0xFFU);
        destBuf[i] = 0xA5U;
    }
    CacheP_wb(srcBuf,  length, CacheP_TYPE_ALLD);
    CacheP_wb(destBuf, length, CacheP_TYPE_ALLD);
}

static void App_udmaCompareBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length)
{
    uint32_t i;

    CacheP_inv(destBuf, length, CacheP_TYPE_ALLD);
    for(i = 0U; i < length; i++)
    {
        if(srcBuf[i] != destBuf[i])
        {
            DebugP_logError("Data mismatch !!!\r\n");
            DebugP_assert(FALSE);
        }
    }
}

static void App_druBuildTr(CSL_UdmapTR15 *tr, const void *srcBuf,
                           const void *destBuf, uint32_t length)
{
    (void)memset(tr, 0, sizeof(*tr));

    tr->flags  = CSL_FMK(UDMAP_TR_FLAGS_TYPE,
                         CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_STATIC,        0U);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_EOL,           0U);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE,
                         CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0,
                         CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE,
                         CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1,
                         CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE,
                         CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID,        0x25U);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT,   0U);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT,   0U);
    tr->flags |= CSL_FMK(UDMAP_TR_FLAGS_EOP,           1U);

    tr->icnt0 = length;   tr->icnt1 = 1U;   tr->icnt2 = 1U;   tr->icnt3 = 1U;
    tr->dim1  = (int32_t)tr->icnt0;
    tr->dim2  = (int32_t)(tr->icnt0 * tr->icnt1);
    tr->dim3  = (int32_t)(tr->icnt0 * tr->icnt1 * tr->icnt2);
    tr->addr  = (uint64_t) Udma_defaultVirtToPhyFxn(srcBuf, 0U, NULL);
    tr->fmtflags = 0x00000000U;

    tr->dicnt0 = length;  tr->dicnt1 = 1U;  tr->dicnt2 = 1U;  tr->dicnt3 = 1U;
    tr->ddim1  = (int32_t)tr->dicnt0;
    tr->ddim2  = (int32_t)(tr->dicnt0 * tr->dicnt1);
    tr->ddim3  = (int32_t)(tr->dicnt0 * tr->dicnt1 * tr->dicnt2);
    tr->daddr  = (uint64_t) Udma_defaultVirtToPhyFxn(destBuf, 0U, NULL);
}

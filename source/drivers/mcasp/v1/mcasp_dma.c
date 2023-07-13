/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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

#include <string.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/CacheP.h>
#include <drivers/udma.h>
#include <drivers/mcasp.h>
#include <drivers/mcasp/v1/mcasp_priv.h>
#include <drivers/mcasp/v1/dma_priv/mcasp_dma_priv.h>

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */
/* DMA Event count for 1 Ser Multislot Interleaved format */
#define MCASP_1SER_MULTISLOT_INTERLEAVED_DMA_EVNT_CNT   (0x20U)

/* DMA perpertual reload count */
#define MCASP_DMA_PERPETUAL_RELOAD_CNT                  (0x1FFU)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void MCASP_udmaIsrRx(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args);
static void MCASP_udmaIsrTx(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args);

static void MCASP_bcdmaTxIsr(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args);
static void MCASP_bcdmaRxIsr(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args);

static void MCASP_udmaTrpdInitTx(Udma_ChHandle chHandle, uint8_t *pTrpdMem,
                                const void *buf, uint32_t length, uint32_t buffCnt);
static void MCASP_udmaTrpdInitRx(Udma_ChHandle chHandle, uint8_t *pTrpdMem,
                                const void *buf, uint32_t length, uint32_t buffCnt);

static void MCASP_mem2memTrpdInit(Udma_ChHandle chHandle, uint8_t *trpdMem,
                            const void *destBuf,
                            const void *srcBuf,
                            uint32_t length);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t MCASP_openDma(MCASP_Config *config, MCASP_DmaChConfig *dmaChCfg)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    Udma_DrvHandle drvHandle = NULL;

    if(config != NULL)
    {
        obj = config->object;
        drvHandle = (Udma_DrvHandle)obj->mcaspDmaHandle;
    }
    else
    {
        status = SystemP_SUCCESS;
    }

    /*************** Configure TX PDMA and BCDMA channels ***************/
    if(SystemP_SUCCESS == status)
    {
        uint32_t chType;
        Udma_ChHandle txChHandle;
        Udma_EventHandle eventHandle;
        Udma_ChPrms chPrms;

        Udma_ChTxPrms       txPrms;
        Udma_EventPrms      eventPrms;

        /* Init TX channel parameters */
        chType = UDMA_CH_TYPE_PDMA_TX;
        UdmaChPrms_init(&chPrms, chType);
        chPrms.peerChNum                = dmaChCfg->txEvtNum;
        chPrms.fqRingPrms.ringMem       = dmaChCfg->txRingMem;
        chPrms.fqRingPrms.ringMemSize   = dmaChCfg->ringMemSize;
        chPrms.fqRingPrms.elemCnt       = dmaChCfg->ringElemCnt;
        txChHandle                      = dmaChCfg->txChHandle;

        /* UDMA channel for block copy */
        status = Udma_chOpen(drvHandle, txChHandle, chType, &chPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Config TX channel */
        UdmaChTxPrms_init(&txPrms, chType);

        status = Udma_chConfigTx(txChHandle, &txPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Register ring completion callback */
        eventHandle = dmaChCfg->cqTxEvtHandle;
        UdmaEventPrms_init(&eventPrms);
        eventPrms.eventType             = UDMA_EVENT_TYPE_TR;
        eventPrms.eventMode             = UDMA_EVENT_MODE_SHARED;
        eventPrms.chHandle              = txChHandle;
        eventPrms.masterEventHandle     = Udma_eventGetGlobalHandle(drvHandle);
        eventPrms.eventCb               = &MCASP_udmaIsrTx;
        eventPrms.appData               = config;
        status = Udma_eventRegister(drvHandle, eventHandle, &eventPrms);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    /*************** Configure RX PDMA and BCDMA channels ***************/
    if(SystemP_SUCCESS == status)
    {
        uint32_t chType;
        Udma_ChHandle rxChHandle;
        Udma_EventHandle eventHandle;
        Udma_ChPrms chPrms;

        Udma_ChRxPrms       rxPrms;
        Udma_EventPrms      eventPrms;

        /* Init RX channel parameters */
        chType = UDMA_CH_TYPE_PDMA_RX;
        UdmaChPrms_init(&chPrms, chType);
        chPrms.peerChNum                = dmaChCfg->rxEvtNum;
        chPrms.fqRingPrms.ringMem       = dmaChCfg->rxRingMem;
        chPrms.fqRingPrms.ringMemSize   = dmaChCfg->ringMemSize;
        chPrms.fqRingPrms.elemCnt       = dmaChCfg->ringElemCnt;
        rxChHandle                      = dmaChCfg->rxChHandle;

        /* UDMA channel for block copy */
        status = Udma_chOpen(drvHandle, rxChHandle, chType, &chPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Config RX channel */
        UdmaChRxPrms_init(&rxPrms, chType);
        rxPrms.configDefaultFlow = FALSE;
        status = Udma_chConfigRx(rxChHandle, &rxPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Register ring completion callback */
        eventHandle = dmaChCfg->cqRxEvtHandle;
        UdmaEventPrms_init(&eventPrms);
        eventPrms.eventType             = UDMA_EVENT_TYPE_TR;
        eventPrms.eventMode             = UDMA_EVENT_MODE_SHARED;
        eventPrms.chHandle              = rxChHandle;
        eventPrms.masterEventHandle     = Udma_eventGetGlobalHandle(drvHandle);
        eventPrms.eventCb               = &MCASP_udmaIsrRx;
        eventPrms.appData               = config;
        status = Udma_eventRegister(drvHandle, eventHandle, &eventPrms);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    return status;
}

void MCASP_closeDma(MCASP_Config *config, MCASP_DmaChConfig *dmaChCfg)
{
    int32_t status = SystemP_SUCCESS;
    Udma_ChHandle txChHandle = NULL, rxChHandle = NULL;

    if((NULL != config) && (NULL != dmaChCfg))
    {
        txChHandle = dmaChCfg->txChHandle;
        rxChHandle = dmaChCfg->rxChHandle;

        status = Udma_chDisable(txChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);

        /* Reset the tx channel if channel teardown fails */
        if(SystemP_SUCCESS != status)
        {
            status = Udma_chReset(txChHandle);
        }
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_chDisable(rxChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_eventUnRegister(dmaChCfg->cqTxEvtHandle);
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_eventUnRegister(dmaChCfg->cqRxEvtHandle);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Flush any pending request from the free queue */
        while(1U)
        {
            uint64_t pDesc;
            int32_t  tempRetVal;

            tempRetVal = Udma_ringFlushRaw(
                            Udma_chGetFqRingHandle(dmaChCfg->txChHandle), &pDesc);
            if(UDMA_ETIMEOUT == tempRetVal)
            {
                break;
            }
        }

        /* Flush any pending request from the free queue */
        while(1U)
        {
            uint64_t pDesc;
            int32_t  tempRetVal;

            tempRetVal = Udma_ringFlushRaw(
                            Udma_chGetFqRingHandle(dmaChCfg->rxChHandle), &pDesc);
            if(UDMA_ETIMEOUT == tempRetVal)
            {
                break;
            }
        }

        /* Close TX channel */
        status = Udma_chClose(dmaChCfg->txChHandle);
        DebugP_assert(UDMA_SOK == status);

        /* Close Rx channel */
        status = Udma_chClose(dmaChCfg->rxChHandle);
        DebugP_assert(UDMA_SOK == status);
    }

    return;
}

int32_t MCASP_enableDmaTx(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *object = NULL;
    MCASP_Transaction *txn;

    if(NULL != config)
    {
        object = config->object;
        txn = QueueP_get(object->reqQueueHandleTx);

        if (txn == object->reqQueueHandleTx)
        {
            /* No buffers are queued. */
            if (object->XmtObj.loopjobEnable == true)
            {
                txn = &object->XmtObj.txnLoopjob;
            }
            else
            {
                status = SystemP_FAILURE;
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    /* Get the cyclic buffer parameters to create TRPD and start the cyclic DMA */
    uint8_t *cyclicBuff = object->cyclicBuffTx;
    uint32_t cyclicSize = object->cyclicBuffSizeTx;
    uint32_t cyclicCnt = object->cyclicBuffCntTx;

    if(SystemP_SUCCESS == status)
    {
        /********** Register completion event for Cyclic buffer feeder *********/
        Udma_ChHandle *pBcdmaChHandle = object->cyclicTxFeedDMAHandle;
        Udma_ChHandle bcdmaChHandle = *pBcdmaChHandle;
        Udma_EventHandle eventHandle;
        Udma_EventPrms eventPrms;

        /* Register ring completion callback */
        eventHandle = object->bcdmaTxCyclicEvtHandle;
        UdmaEventPrms_init(&eventPrms);
        eventPrms.eventType             = UDMA_EVENT_TYPE_TR;
        eventPrms.eventMode             = UDMA_EVENT_MODE_SHARED;
        eventPrms.chHandle              = bcdmaChHandle;
        eventPrms.masterEventHandle     = Udma_eventGetGlobalHandle(object->bcdmaDrvHandle);
        eventPrms.eventCb               = &MCASP_bcdmaTxIsr;
        eventPrms.appData               = config;
        status = Udma_eventRegister(object->bcdmaDrvHandle, eventHandle, &eventPrms);
        DebugP_assert(SystemP_SUCCESS == status);
        /***********************************************************************/

        if((cyclicSize * cyclicCnt) < (txn->count * 4U))
        {
            /* Prime the cylcic buffer with tx buffer */
            memcpy(cyclicBuff, txn->buf, cyclicSize * cyclicCnt);

            CacheP_wb(cyclicBuff, cyclicSize * cyclicCnt, CacheP_TYPE_ALL);

            object->currTxTransRemCnt = txn->count - ((cyclicSize * cyclicCnt)/4U);
            object->currTransTx = txn;
        }
    }

    /* Start the cyclic DMA transfer from the cyclic buffer */
    if(SystemP_SUCCESS == status)
    {
        Udma_ChPdmaPrms pdmaPrms;
        Udma_ChHandle txChHandle = object->dmaChCfg->txChHandle;

        /* Config PDMA channel */
        UdmaChPdmaPrms_init(&pdmaPrms);
        pdmaPrms.elemSize = UDMA_PDMA_ES_32BITS;

        /* Number of words received in each transfer */
        pdmaPrms.elemCnt = MCASP_1SER_MULTISLOT_INTERLEAVED_DMA_EVNT_CNT;
        pdmaPrms.fifoCnt = 0U;

        pdmaPrms.acc32 = 1U;
        pdmaPrms.burst = 1U;

        status = Udma_chConfigPdma(txChHandle, &pdmaPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_chEnable(txChHandle);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Submit TRPPD for cyclic transfers from the cyclic buffer */
        MCASP_udmaTrpdInitTx(txChHandle, object->dmaChCfg->txTrpdMem, cyclicBuff,
                                cyclicSize, cyclicCnt);

        object->txTrCompletionIdx = 0U;

        status = Udma_ringQueueRaw(Udma_chGetFqRingHandle(txChHandle),
            (uint64_t) Udma_defaultVirtToPhyFxn(object->dmaChCfg->txTrpdMem, 0U, NULL));
        DebugP_assert(SystemP_SUCCESS == status);

    }

    return status;
}

int32_t MCASP_enableDmaRx(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;

    MCASP_Object *object = config->object;
    MCASP_Transaction *txn = QueueP_get(object->reqQueueHandleRx);

    if (txn == object->reqQueueHandleRx)
    {
        /* No buffers are queued. */
        if (object->RcvObj.loopjobEnable == true)
        {
            txn = &object->RcvObj.txnLoopjob;
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }

    object->currTransRx = txn;
    object->currRxTransRemCnt = txn->count;

    /********** Register completion event for Cyclic buffer feeder *********/
    Udma_ChHandle *pBcdmaChHandle = object->cyclicRxFeedDMAHandle;
    Udma_ChHandle bcdmaChHandle = *pBcdmaChHandle;
    Udma_EventHandle eventHandle;
    Udma_EventPrms eventPrms;

    /* Register ring completion callback */
    eventHandle = object->bcdmaRxCyclicEvtHandle;
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType             = UDMA_EVENT_TYPE_DMA_COMPLETION;
    eventPrms.eventMode             = UDMA_EVENT_MODE_SHARED;
    eventPrms.chHandle              = bcdmaChHandle;
    eventPrms.masterEventHandle     = Udma_eventGetGlobalHandle(object->bcdmaDrvHandle);
    eventPrms.eventCb               = &MCASP_bcdmaRxIsr;
    eventPrms.appData               = config;
    status = Udma_eventRegister(object->bcdmaDrvHandle, eventHandle, &eventPrms);
    DebugP_assert(SystemP_SUCCESS == status);

    status = Udma_chEnable(bcdmaChHandle);
    /*********************************************************************/

    uint8_t *cyclicBuff = object->cyclicBuffRx;
    uint32_t cyclicSize = object->cyclicBuffSizeRx;
    uint32_t cyclicCnt = object->cyclicBuffCntRx;

    /* Configure and enable peer for RX */
    if(SystemP_SUCCESS == status)
    {
        Udma_ChPdmaPrms pdmaPrms;
        Udma_ChHandle rxChHandle = object->dmaChCfg->rxChHandle;

        /* Config PDMA channel */
        UdmaChPdmaPrms_init(&pdmaPrms);
        pdmaPrms.elemSize = UDMA_PDMA_ES_32BITS;

        /* Number of words received in each transfer */
        pdmaPrms.elemCnt = MCASP_1SER_MULTISLOT_INTERLEAVED_DMA_EVNT_CNT;
        pdmaPrms.fifoCnt = 0U;

        pdmaPrms.acc32 = 1U;
        pdmaPrms.burst = 1U;

        status = Udma_chConfigPdma(rxChHandle, &pdmaPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_chEnable(rxChHandle);
        DebugP_assert(SystemP_SUCCESS == status);

        MCASP_udmaTrpdInitRx(rxChHandle, object->dmaChCfg->rxTrpdMem, cyclicBuff,
                                cyclicSize, cyclicCnt);

        object->rxTrCompletionIdx = 0U;

        status = Udma_ringQueueRaw(Udma_chGetFqRingHandle(rxChHandle),
            (uint64_t)Udma_defaultVirtToPhyFxn(object->dmaChCfg->rxTrpdMem, 0U, NULL));

        DebugP_assert(SystemP_SUCCESS == status);
    }


    return status;
}

void MCASP_disableDmaTx(MCASP_Config *config)
{
    return;
}

void MCASP_disableDmaRx(MCASP_Config *config)
{
    return;
}

static void MCASP_udmaIsrTx(Udma_EventHandle eventHandle,
                                 uint32_t eventType,
                                 void *args)
{
    MCASP_Object *object = ((MCASP_Config *)args)->object;
    MCASP_TransferObj *xfrObj = &(object->XmtObj);

    uint8_t *trpdMem = NULL;
    int32_t status = MCASP_getFreeTrpd(object->trpdMemAllocTx, &trpdMem);
    DebugP_assert(SystemP_SUCCESS == status);

    uint8_t *destPtr = (uint8_t *)(object->cyclicBuffTx +
                                (object->txTrCompletionIdx * object->cyclicBuffSizeTx));
    Udma_ChHandle *pHandle = object->cyclicTxFeedDMAHandle;
    Udma_ChHandle handle = *pHandle;

    /* Check remaining count from current transaction */
    uint32_t remCnt = object->currTxTransRemCnt;

    if(0U != remCnt)
    {
        MCASP_mem2memTrpdInit(handle, trpdMem, destPtr,
                ((uint8_t *)object->currTransTx->buf + (object->currTransTx->count*4 - remCnt*4U)),
                object->cyclicBuffSizeTx);

        object->currTxTransRemCnt = remCnt - (object->cyclicBuffSizeTx/4);
    }
    else
    {
        /* Call the callback function registered */
        object->currTransTx->status = SystemP_SUCCESS;

        MCASP_Transaction *txn = QueueP_get(object->reqQueueHandleTx);
        object->currTxTransRemCnt = txn->count;

        xfrObj->cbFxn((MCASP_Handle *)args, object->currTransTx);

        if(txn == object->reqQueueHandleTx)
        {
            object->currTransTx = &object->XmtObj.txnLoopjob;
            if(object->XmtObj.loopjobEnable)
            {
                MCASP_mem2memTrpdInit(handle, trpdMem, destPtr,
                object->currTransTx->buf, object->cyclicBuffSizeTx);
            }
        }
        else
        {
            object->currTransTx = txn;
            uint32_t offset = txn->count*4 - object->currTxTransRemCnt*4;

            if(txn->count*4 <= object->cyclicBuffSizeTx)
            {
                object->currTxTransRemCnt = 0U;
            }
            else
            {
                object->currTxTransRemCnt = txn->count - (object->cyclicBuffSizeTx/4U);
            }

            MCASP_mem2memTrpdInit(handle, trpdMem, destPtr,
            (uint8_t *)txn->buf + offset, object->cyclicBuffSizeTx);
        }
    }

    Udma_ringQueueRaw(Udma_chGetFqRingHandle(handle),
            (uint64_t) Udma_defaultVirtToPhyFxn(trpdMem, 0U, NULL));

    if(object->txTrCompletionIdx < object->cyclicBuffCntTx-1U)
    {
        object->txTrCompletionIdx++;
    }
    else
    {
        object->txTrCompletionIdx = 0U;
    }

    return;
}

static void MCASP_udmaIsrRx(Udma_EventHandle eventHandle,
                                 uint32_t eventType,
                                 void *args)
{
    int32_t status = SystemP_FAILURE;
    MCASP_Object *object = ((MCASP_Config *)args)->object;
    MCASP_TransferObj *xfrObj = &(object->RcvObj);
    uint8_t *trpdMem = NULL;

    status = MCASP_getFreeTrpd(object->trpdMemAllocRx, &trpdMem);
    DebugP_assert(SystemP_SUCCESS == status);

    uint8_t *srcPtr = (uint8_t *)(object->cyclicBuffRx +
                                (object->rxTrCompletionIdx * object->cyclicBuffSizeRx));

    Udma_ChHandle *pHandle = object->cyclicRxFeedDMAHandle;
    Udma_ChHandle handle = *pHandle;

    uint8_t *dstPtr = (uint8_t *)object->currTransRx->buf +
                    (object->currTransRx->count - object->currRxTransRemCnt)*4U;

    uint32_t remCnt = object->currRxTransRemCnt;

    if(0U != remCnt)
    {
        MCASP_mem2memTrpdInit(handle, trpdMem, dstPtr,
                                srcPtr, object->cyclicBuffSizeRx);

        object->currRxTransRemCnt = remCnt - (object->cyclicBuffSizeRx)/4U;
    }
    else
    {
        /* Call the callback function registered */
        object->currTransRx->status = SystemP_SUCCESS;

        MCASP_Transaction *txn = QueueP_get(object->reqQueueHandleRx);

        if(xfrObj->cbFxn != NULL)
        {
            QueueP_put(object->completedQueueHandleRx, object->currTransRx);
        }

        if(txn == object->reqQueueHandleRx)
        {
            object->currTransRx = &object->RcvObj.txnLoopjob;
            if(object->RcvObj.loopjobEnable)
            {
                MCASP_mem2memTrpdInit(handle, trpdMem, object->currTransRx->buf,
                srcPtr, object->cyclicBuffSizeRx);
            }
        }
        else
        {
            object->currTransRx = txn;
            object->currRxTransRemCnt = txn->count;
            uint32_t offset = txn->count*4 - object->currRxTransRemCnt*4;

            if(txn->count*4 <= object->cyclicBuffSizeRx)
            {
                object->currRxTransRemCnt = 0U;
            }
            else
            {
                object->currRxTransRemCnt = txn->count - (object->cyclicBuffSizeRx/4U);
            }

            MCASP_mem2memTrpdInit(handle, trpdMem, (uint8_t *)object->currTransRx->buf + offset,
                    srcPtr, object->cyclicBuffSizeRx);
        }

        CSL_UdmapCppi5TRPD *pTrpd = (CSL_UdmapCppi5TRPD *)trpdMem;

        pTrpd->srcDstTag = (uint32_t)args;
    }

    Udma_ringQueueRaw(Udma_chGetFqRingHandle(handle),
            (uint64_t) Udma_defaultVirtToPhyFxn(trpdMem, 0U, NULL));


    if(object->rxTrCompletionIdx < (object->cyclicBuffCntRx - 1U))
    {
        object->rxTrCompletionIdx++;
    }
    else
    {
        object->rxTrCompletionIdx = 0U;
    }

    return;
}

/* Create cyclic TRPD to move data from or to the cyclic Buffers */
static void MCASP_udmaTrpdInitTx(Udma_ChHandle chHandle, uint8_t *pTrpdMem,
                                const void *buf, uint32_t length, uint32_t buffCnt)
{
    CSL_UdmapCppi5TRPD *pTrpd = (CSL_UdmapCppi5TRPD *)pTrpdMem;
    CSL_UdmapTR1 *pTr;
    uint32_t cqRingNum = Udma_chGetCqRingNum(chHandle);

    /* Make TRPD with TR1 TR Type */
    UdmaUtils_makeTrpd((uint8_t *)pTrpd, UDMA_TR_TYPE_1, buffCnt, cqRingNum);

    /* Perpetual reload */
    UdmaUtils_setTrpdReload((uint8_t *)pTrpd, MCASP_DMA_PERPETUAL_RELOAD_CNT, 0U);

    int i;
    for(i = 0U; i<buffCnt; i++)
    {
        pTr = UdmaUtils_getTrpdTr1Pointer((uint8_t *)pTrpd, i);

        pTr->addr = (uint64_t)((uint8_t *)buf + (length*i));

        pTr->flags = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_2D_DATA_MOVE);

        pTr->icnt0 = length;
        pTr->icnt1 = 1U;
        pTr->dim1 = pTr->icnt0;
    }

    CacheP_wb(pTrpdMem, UDMA_GET_TRPD_TR15_SIZE(buffCnt), CacheP_TYPE_ALLD);

    return;
}

/* Create cyclic TRPD to move data from or to the cyclic Buffers */
static void MCASP_udmaTrpdInitRx(Udma_ChHandle chHandle, uint8_t *pTrpdMem,
                                const void *buf, uint32_t length, uint32_t buffCnt)
{
    CSL_UdmapCppi5TRPD *pTrpd = (CSL_UdmapCppi5TRPD *)pTrpdMem;
    CSL_UdmapTR1 *pTr;
    uint32_t cqRingNum = Udma_chGetCqRingNum(chHandle);

    /* Make TRPD with TR1 TR Type */
    UdmaUtils_makeTrpd((uint8_t *)pTrpd, UDMA_TR_TYPE_1, buffCnt, cqRingNum);

    /* Perpetual reload */
    UdmaUtils_setTrpdReload((uint8_t *)pTrpd, MCASP_DMA_PERPETUAL_RELOAD_CNT, 0);

    int i;
    for(i = 0; i<buffCnt; i++)
    {
        pTr = UdmaUtils_getTrpdTr1Pointer((uint8_t *)pTrpd, i);

        pTr->addr = (uint64_t)((uint8_t *)buf + (length*i));

        pTr->flags = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_2D_DATA_MOVE);

        pTr->icnt0 = length;
        pTr->icnt1 = 1;
        pTr->dim1 = pTr->icnt0;
    }

    CacheP_wb(pTrpdMem, UDMA_GET_TRPD_TR15_SIZE(buffCnt), CacheP_TYPE_ALLD);

    return;
}

static void MCASP_mem2memTrpdInit(Udma_ChHandle chHandle, uint8_t *trpdMem,
                            const void *destBuf,
                             const void *srcBuf,
                             uint32_t length)
{
    CSL_UdmapTR15  *pTr;
    uint32_t        cqRingNum = Udma_chGetCqRingNum(chHandle);

    /* Clear Trpd header */
    memset(trpdMem, 0, sizeof(CSL_UdmapCppi5HMPD));

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
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, 0x25U);
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
    CacheP_wb(trpdMem, UDMA_GET_TRPD_TR15_SIZE(1U), CacheP_TYPE_ALLD);

    return;
}

static void MCASP_bcdmaTxIsr(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args)
{
    MCASP_Object *object = ((MCASP_Config *)args)->object;
    uint64_t pDesc;

    /* Dequeue the response from ring */
    {
        Udma_ChHandle *pTxChHandle = object->cyclicTxFeedDMAHandle;
        Udma_ChHandle txChHandle = *pTxChHandle;

        int32_t status = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(txChHandle), &pDesc);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    MCASP_postFreeTrpd(object->trpdMemAllocTx, pDesc);

    return;
}

static void MCASP_bcdmaRxIsr(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args)
{
    MCASP_Object *object = ((MCASP_Config *)args)->object;
    uint64_t pDesc;

    /* Dequeue the response from ring */
    {
        Udma_ChHandle *pRxChHandle = object->cyclicRxFeedDMAHandle;
        Udma_ChHandle rxChHandle = *pRxChHandle;

        int32_t status = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(rxChHandle), &pDesc);
        DebugP_assert(SystemP_SUCCESS == status);

        CSL_UdmapCppi5TRPD *pTrpd = (CSL_UdmapCppi5TRPD *)pDesc;

        if(NULL != pTrpd->srcDstTag)
        {
            MCASP_Config *config = (MCASP_Config *)args;
            MCASP_TransferObj *xfrObj = &(config->object->RcvObj);
            MCASP_Transaction *trans;

            trans = QueueP_get(object->completedQueueHandleRx);

            xfrObj->cbFxn((MCASP_Handle *)args, trans);
        }
    }

    MCASP_postFreeTrpd(object->trpdMemAllocRx, pDesc);

    return;
}

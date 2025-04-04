/*
 *  Copyright (C) 2023-2025 Texas Instruments Incorporated
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
#include <drivers/mcasp/v1/mcasp_drv_configs/mcasp_drv_config.h>

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */
#define MCASP_DMA_L0_MAX_XFER_SIZE                      (65536U)

#define MCASP_DMA_UDMA_XFER_SIZE                        (64512U)

#define MCASP_BCDMA_TX_CH_DEPTH                         (64U)

#if defined (MCASP_TX_EVENT_TYPE_L2G)
#define MCASP_UDMA_TR15_TRPD_SIZE_TX        (UDMA_GET_TRPD_TR15_SIZE(MCASP_TX_DMA_TR_COUNT))
#else
#define MCASP_UDMA_TR3_TRPD_SIZE_TX         (UDMA_GET_TRPD_TR3_SIZE(MCASP_TX_DMA_TR_COUNT))
#endif
#define MCASP_UDMA_TR3_TRPD_SIZE_RX         (UDMA_GET_TRPD_TR3_SIZE(MCASP_RX_DMA_TR_COUNT))

#define MCASP_UDMA_HPD_SIZE              (UDMA_ALIGN_SIZE((sizeof(CSL_UdmapCppi5HMPD))))

#define MCASP_UDMA_RING_ENTRY_SIZE       (sizeof(uint64_t))
#define MCASP_UDMA_RING_MEM_SIZE_TX      (MCASP_TX_DMA_RING_ELEM_CNT * MCASP_UDMA_RING_ENTRY_SIZE)
#define MCASP_UDMA_RING_MEM_SIZE_RX      (MCASP_RX_DMA_RING_ELEM_CNT * MCASP_UDMA_RING_ENTRY_SIZE)

#define MCASP_PDMA_ELEM_CNT_WITH_FIFO    (32U)

/* DMA perpertual reload count */
#define MCASP_DMA_PERPETUAL_RELOAD_CNT                  (0x1FFU)

#define WORD_BYTE_COUNT                                 (4U)

#define MCASP_INVALID_TXN_IDX                           (0xDEADBEEFU)

#define MCASP_ICNT2_MAX                                 (65535U)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void MCASP_udmaIsrTx(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args);

static void MCASP_udmaIsrRx(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args);

static int32_t MCASP_primeTxTrpd(MCASP_Config *config);

static int32_t MCASP_primeRxTrpd(MCASP_Config *config);

extern uint64_t Udma_virtToPhyFxn(const void *virtAddr,
                           Udma_DrvHandle drvHandle,
                           Udma_ChHandle chHandle);

extern void *Udma_phyToVirtFxn(uint64_t phyAddr,
                        Udma_DrvHandle drvHandle,
                        Udma_ChHandle chHandle);

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
        status = SystemP_FAILURE;
    }

    if(obj != NULL)
    {
#if defined (MCASP_TX_EVENT_TYPE_L2G)
        if(SystemP_SUCCESS == status)
        {
            Udma_ChPrms chPrms;
            Udma_ChHandle txChHandle;
            Udma_ChTxPrms txPrms;
            Udma_ChRxPrms rxPrms;
            Udma_EventHandle eventHandle;
            Udma_EventPrms eventPrms;

            uint32_t chanType = UDMA_CH_TYPE_TR_BLK_COPY;
            UdmaChPrms_init(&chPrms, chanType);
            chPrms.fqRingPrms.ringMem = dmaChCfg->txRingMem;
            chPrms.fqRingPrms.ringMemSize = MCASP_UDMA_RING_MEM_SIZE_TX;
            chPrms.fqRingPrms.elemCnt = MCASP_TX_DMA_RING_ELEM_CNT;

            txChHandle = dmaChCfg->txChHandle;

            /* Channel open */
            status = Udma_chOpen(drvHandle, txChHandle, chanType, &chPrms);
            DebugP_assert(UDMA_SOK == status);

            /* Configure TX channel */
            UdmaChTxPrms_init(&txPrms, chanType);
            status = Udma_chConfigTx(txChHandle, &txPrms);
            DebugP_assert(UDMA_SOK == status);

            /* Config RX channel - which is implicitly paired to TX channel in
             * block copy mode */
            UdmaChRxPrms_init(&rxPrms, chanType);
            status = Udma_chConfigRx(txChHandle, &rxPrms);
            DebugP_assert(UDMA_SOK == status);

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

            /* Set lastPlayed index as MCASP_TX_DMA_RING_ELEM_CNT-1. (So on playing first TR will be updated to 0) */
            obj->lastPlayed = MCASP_TX_DMA_TR_COUNT-1U;
            obj->lastFilled = MCASP_TX_DMA_TR_COUNT-1U;
        }
#else
        /* Configure TX side PDMA <- BCDMA TX channel pair */
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
            chPrms.fqRingPrms.ringMemSize   = MCASP_UDMA_RING_MEM_SIZE_TX;
            chPrms.fqRingPrms.elemCnt       = MCASP_TX_DMA_RING_ELEM_CNT;
            txChHandle                      = dmaChCfg->txChHandle;

            status = Udma_chOpen(drvHandle, txChHandle, chType, &chPrms);
            DebugP_assert(SystemP_SUCCESS == status);

            /* Config TX channel */
            UdmaChTxPrms_init(&txPrms, chType);

            /* Set TX FIFO depth */
            txPrms.fifoDepth = MCASP_BCDMA_TX_CH_DEPTH;

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

            /* Set lastPlayed index as MCASP_TX_DMA_RING_ELEM_CNT-1. (So on playing first TR will be updated to 0) */
            obj->lastPlayed = MCASP_TX_DMA_TR_COUNT-1U;

            obj->lastFilled = MCASP_TX_DMA_TR_COUNT-1U;
        }
#endif
        /* Congfig RX side PDMA -> PKTDMA pair */
        if(status == SystemP_SUCCESS)
        {
            uint32_t chType;
            Udma_ChHandle rxChHandle;
            Udma_EventHandle eventHandle;
            Udma_ChPrms chPrms;

            Udma_ChRxPrms       rxPrms;
            Udma_EventPrms      eventPrms;

            /* Init TX channel parameters */
            chType = UDMA_CH_TYPE_PDMA_RX;
            UdmaChPrms_init(&chPrms, chType);
            chPrms.peerChNum                = dmaChCfg->rxEvtNum;
            chPrms.fqRingPrms.ringMem       = dmaChCfg->rxRingMem;
            chPrms.fqRingPrms.ringMemSize   = MCASP_UDMA_RING_MEM_SIZE_RX;
            chPrms.fqRingPrms.elemCnt       = MCASP_RX_DMA_RING_ELEM_CNT;
            rxChHandle                      = dmaChCfg->rxChHandle;

            status = Udma_chOpen(drvHandle, rxChHandle, chType, &chPrms);
            DebugP_assert(SystemP_SUCCESS == status);

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

            /* Set last record queued index */
            obj->lastRecQueued = MCASP_RX_DMA_TR_COUNT-1U;

            obj->lastReceived = MCASP_RX_DMA_TR_COUNT-1U;
        }
    }

    return status;
}

#if defined (MCASP_TX_EVENT_TYPE_L2G)

static int32_t MCASP_primeTxTrpd(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    CSL_UdmapTR15 *pTr = NULL;
    uint32_t i = 0;
    MCASP_Transaction **txCbParam;
    Udma_DrvHandle drvHandle;
    const MCASP_Attrs *attrs = NULL;
    const CSL_McaspRegs *pReg = NULL;

    if(config != NULL)
    {
        obj = config->object;
        attrs = config->attrs;
        pReg = (const CSL_McaspRegs *)attrs->baseAddr;
    }
    else
    {
        status = SystemP_FAILURE;
    }
    if(obj != NULL)
    {
        Udma_ChHandle txChHandle = obj->dmaChCfg->txChHandle;

        if(status == SystemP_SUCCESS)
        {
            uint32_t cqRingNum = Udma_chGetCqRingNum(txChHandle);

            drvHandle = obj->mcaspDmaHandle;

            memset(obj->dmaChCfg->txCbParams, 0, sizeof(MCASP_Transaction *)*MCASP_TX_DMA_TR_COUNT);

            memset(obj->dmaChCfg->txTrpdMem, 0, MCASP_UDMA_TR15_TRPD_SIZE_TX*MCASP_TX_DMA_RING_ELEM_CNT);

            CacheP_wb(obj->dmaChCfg->txTrpdMem, MCASP_UDMA_TR15_TRPD_SIZE_TX*MCASP_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

            UdmaUtils_makeTrpdTr15((uint8_t *)obj->dmaChCfg->txTrpdMem, MCASP_TX_DMA_TR_COUNT, cqRingNum);

            /* Perpetual reload */
            UdmaUtils_setTrpdReload((uint8_t *)obj->dmaChCfg->txTrpdMem, MCASP_DMA_PERPETUAL_RELOAD_CNT, 0U);

            /* Prime TRs in TRPD with loopjobs */
            for(i = 0; i < MCASP_TX_DMA_TR_COUNT; i++)
            {
                pTr = UdmaUtils_getTrpdTr15Pointer((uint8_t *)obj->dmaChCfg->txTrpdMem, i);

                pTr->flags = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);

                pTr->addr = (uint64_t)Udma_virtToPhyFxn(obj->XmtObj.txnLoopjob.buf, drvHandle, txChHandle);

                status = MCASP_prepareDmaIcnts((MCASP_Handle)config, ((uint64_t)obj->XmtObj.txnLoopjob.count * (uint64_t)WORD_BYTE_COUNT),
                                                                1U);
                DebugP_assert(status == SystemP_SUCCESS);

                pTr->flags = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, 0U);
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_MATCH_SOL_EOL);
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT2_DEC);
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, 0x25U);  /* This will come back in TR response */
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U);
                pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U);

                pTr->icnt0 = obj->txDmaIcnt.icnt0;
                pTr->icnt1 = obj->txDmaIcnt.icnt1;
                pTr->icnt2 = obj->txDmaIcnt.icnt2;
                pTr->icnt3 = obj->txDmaIcnt.icnt3;

                pTr->dim1     = pTr->icnt0;
                pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

                pTr->fmtflags = 0x00000000U;    /* Linear addressing, 1 byte per elem */

                /* Dest */
                pTr->daddr = (uint64_t)((uint8_t *)pReg + 0x8000U);
                pTr->dicnt0 = obj->txDmaIcnt.icnt0;
                pTr->dicnt1 = obj->txDmaIcnt.icnt1;
                pTr->dicnt2 = obj->txDmaIcnt.icnt2;
                pTr->dicnt3 = obj->txDmaIcnt.icnt3;
                pTr->ddim1 = 0;
                pTr->ddim2 = 0;
                pTr->ddim3 = 0;
            }

            /* Writeback the TRPD memory */
            CacheP_wb(obj->dmaChCfg->txTrpdMem, MCASP_UDMA_TR15_TRPD_SIZE_TX*MCASP_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

            /* Prime ring memory with pointers to TRPD */
            uint64_t *ringPtr = (uint64_t *)obj->dmaChCfg->txRingMem;
            *ringPtr = (uint64_t)Udma_virtToPhyFxn((uint8_t *)obj->dmaChCfg->txTrpdMem, drvHandle, txChHandle);

            /* Writeback ring memory */
            CacheP_wb(obj->dmaChCfg->txRingMem, MCASP_UDMA_RING_ENTRY_SIZE * MCASP_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

            /* Check if there are txn already submitted */
            if(QueueP_isEmpty(obj->reqQueueHandleTx) == QueueP_NOTEMPTY)
            {
                MCASP_Transaction *txn = NULL;
                uint64_t txCnt = 0;

                txCbParam = obj->dmaChCfg->txCbParams;

                for(i = 0; i < MCASP_TX_DMA_TR_COUNT; i++)
                {
                    txn = QueueP_get(obj->reqQueueHandleTx);

                    if(txn != obj->reqQueueHandleTx)
                    {
                        /* Update last filled index */
                        obj->lastFilled = (obj->lastFilled + 1U)%(MCASP_TX_DMA_TR_COUNT);

                        pTr = UdmaUtils_getTrpdTr15Pointer((uint8_t *)obj->dmaChCfg->txTrpdMem, obj->lastFilled);

                        txCnt = (uint32_t)(txn->count*WORD_BYTE_COUNT);

                        status = MCASP_prepareDmaIcnts((MCASP_Handle)config, (txCnt),
                                                                1U);

                        DebugP_assert(status == SystemP_SUCCESS);

                        pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, drvHandle, txChHandle);

                        pTr->icnt0 = obj->txDmaIcnt.icnt0;
                        pTr->icnt1 = obj->txDmaIcnt.icnt1;
                        pTr->icnt2 = obj->txDmaIcnt.icnt2;
                        pTr->icnt3 = obj->txDmaIcnt.icnt3;

                        pTr->dim1     = pTr->icnt0;
                        pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                        pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

                        CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);

                        txCbParam = obj->dmaChCfg->txCbParams;
                        txCbParam = txCbParam + (obj->lastFilled);
                        *txCbParam = txn;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        /* Set doorbell to push the TRPD  */
        Udma_ringSetDoorBell(Udma_chGetFqRingHandle(txChHandle), MCASP_TX_DMA_RING_ELEM_CNT);
    }

    return status;
}

#else

static int32_t MCASP_primeTxTrpd(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    CSL_UdmapTR3 *pTr = NULL;
    uint32_t i = 0;
    MCASP_Transaction **txCbParam;
    Udma_DrvHandle drvHandle;

    if(config != NULL)
    {
        obj = config->object;
    }
    else
    {
        status = SystemP_FAILURE;
    }
    if(obj != NULL)
    {
        Udma_ChHandle txChHandle = obj->dmaChCfg->txChHandle;

        if(status == SystemP_SUCCESS)
        {
            uint32_t cqRingNum = Udma_chGetCqRingNum(txChHandle);

            drvHandle = obj->mcaspDmaHandle;

            memset(obj->dmaChCfg->txCbParams, 0, sizeof(MCASP_Transaction *)*MCASP_TX_DMA_TR_COUNT);

            memset(obj->dmaChCfg->txTrpdMem, 0, MCASP_UDMA_TR3_TRPD_SIZE_TX*MCASP_TX_DMA_RING_ELEM_CNT);

            CacheP_wb(obj->dmaChCfg->txTrpdMem, MCASP_UDMA_TR3_TRPD_SIZE_TX*MCASP_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

            UdmaUtils_makeTrpd((uint8_t *)obj->dmaChCfg->txTrpdMem, UDMA_TR_TYPE_3, MCASP_TX_DMA_TR_COUNT, cqRingNum);

            /* Perpetual reload */
            UdmaUtils_setTrpdReload((uint8_t *)obj->dmaChCfg->txTrpdMem, MCASP_DMA_PERPETUAL_RELOAD_CNT, 0U);

            /* Prime TRs in TRPD with loopjobs */
            for(i = 0; i < MCASP_TX_DMA_TR_COUNT; i++)
            {
                pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)obj->dmaChCfg->txTrpdMem, i);

                pTr->flags = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_DATA_MOVE);

                pTr->addr = (uint64_t)Udma_virtToPhyFxn(obj->XmtObj.txnLoopjob.buf, drvHandle, txChHandle);

                status = MCASP_prepareDmaIcnts((MCASP_Handle)config, (obj->XmtObj.txnLoopjob.count * WORD_BYTE_COUNT),
                                                                1U);
                DebugP_assert(status == SystemP_SUCCESS);

                pTr->icnt0 = obj->txDmaIcnt.icnt0;
                pTr->icnt1 = obj->txDmaIcnt.icnt1;
                pTr->icnt2 = obj->txDmaIcnt.icnt2;
                pTr->icnt3 = obj->txDmaIcnt.icnt3;

                pTr->dim1     = pTr->icnt0;
                pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
            }

            /* Writeback the TRPD memory */
            CacheP_wb(obj->dmaChCfg->txTrpdMem, MCASP_UDMA_TR3_TRPD_SIZE_TX*MCASP_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

            /* Prime ring memory with pointers to TRPD */
            uint64_t *ringPtr = (uint64_t *)obj->dmaChCfg->txRingMem;
            *ringPtr = (uint64_t)Udma_virtToPhyFxn((uint8_t *)obj->dmaChCfg->txTrpdMem, drvHandle, txChHandle);

            /* Writeback ring memory */
            CacheP_wb(obj->dmaChCfg->txRingMem, MCASP_UDMA_RING_ENTRY_SIZE * MCASP_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

            /* Check if there are txn already submitted */
            if(QueueP_isEmpty(obj->reqQueueHandleTx) == QueueP_NOTEMPTY)
            {
                MCASP_Transaction *txn = NULL;
                uint64_t txCnt = 0;

                txCbParam = obj->dmaChCfg->txCbParams;

                for(i = 0; i < MCASP_TX_DMA_TR_COUNT; i++)
                {
                    txn = QueueP_get(obj->reqQueueHandleTx);

                    if(txn != obj->reqQueueHandleTx)
                    {
                        /* Update last filled index */
                        obj->lastFilled = (obj->lastFilled + 1U)%(MCASP_TX_DMA_TR_COUNT);

                        pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)obj->dmaChCfg->txTrpdMem, obj->lastFilled);

                        txCnt = (uint32_t)(txn->count*WORD_BYTE_COUNT);

                        status = MCASP_prepareDmaIcnts((MCASP_Handle)config, (txCnt),
                                                                1U);

                        DebugP_assert(status == SystemP_SUCCESS);

                        pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, drvHandle, txChHandle);

                        pTr->icnt0 = obj->txDmaIcnt.icnt0;
                        pTr->icnt1 = obj->txDmaIcnt.icnt1;
                        pTr->icnt2 = obj->txDmaIcnt.icnt2;
                        pTr->icnt3 = obj->txDmaIcnt.icnt3;

                        pTr->dim1     = pTr->icnt0;
                        pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                        pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

                        CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);

                        txCbParam = obj->dmaChCfg->txCbParams;
                        txCbParam = txCbParam + (obj->lastFilled);
                        *txCbParam = txn;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        /* Set doorbell to push the TRPD  */
        Udma_ringSetDoorBell(Udma_chGetFqRingHandle(txChHandle), MCASP_TX_DMA_RING_ELEM_CNT);
    }

    return status;
}

#endif

void MCASP_closeDma(MCASP_Config *config, MCASP_DmaChConfig *dmaChCfg)
{
    int32_t status = SystemP_SUCCESS;
    Udma_ChHandle txChHandle = NULL, rxChHandle = NULL;
    uint8_t chanEnStatus;

    if((NULL != config) && (NULL != dmaChCfg))
    {
        txChHandle = dmaChCfg->txChHandle;
        rxChHandle = dmaChCfg->rxChHandle;

        status = Udma_chGetChanEnStatus(txChHandle, &chanEnStatus);
        DebugP_assert(UDMA_SOK == status);
        if(chanEnStatus == 1U)
        {
            /* Disable Channel */
            status = Udma_chDisable(txChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
        }

        while(TRUE)
        {
            int32_t  tempRetVal;
            uint64_t pDesc;
            tempRetVal = Udma_ringFlushRaw(Udma_chGetFqRingHandle(txChHandle), &pDesc);
            if(UDMA_ETIMEOUT == tempRetVal)
            {
                break;
            }
        }

        /* Reset the tx channel if channel teardown fails */
        if(SystemP_SUCCESS != status)
        {
            status = Udma_chReset(txChHandle);
        }
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_chGetChanEnStatus(rxChHandle, &chanEnStatus);
        DebugP_assert(UDMA_SOK == status);
        if(chanEnStatus == 1U)
        {
            /* Disable Channel */
            status = Udma_chDisable(rxChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
            DebugP_assert(UDMA_SOK == status);
        }

        while(TRUE)
        {
            int32_t  tempRetVal;
            uint64_t pDesc;
            tempRetVal = Udma_ringFlushRaw(Udma_chGetFqRingHandle(rxChHandle), &pDesc);
            if(UDMA_ETIMEOUT == tempRetVal)
            {
                break;
            }
        }

        status = Udma_eventUnRegister(dmaChCfg->cqTxEvtHandle);
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_eventUnRegister(dmaChCfg->cqRxEvtHandle);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Flush any pending request from the free queue */
        while(TRUE)
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
        while(TRUE)
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

#if defined (MCASP_TX_EVENT_TYPE_L2G)

int32_t MCASP_enableDmaTx(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    Udma_ChStats chStats;
    uint32_t localEventId = 0;
    const MCASP_Attrs *attrs = NULL;

    if(NULL == config)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        obj = config->object;
        attrs = config->attrs;
    }

    if(status == SystemP_SUCCESS)
    {
        Udma_ChHandle txChHandle = obj->dmaChCfg->txChHandle;
        Udma_DrvHandle drvHandle = obj->mcaspDmaHandle;

        status = MCASP_primeTxTrpd(config);
        DebugP_assert(status == SystemP_SUCCESS);

        status = Udma_chEnable(txChHandle);
        DebugP_assert(status == SystemP_SUCCESS);

        localEventId = MCASP_getTxLocalEventId(attrs->instNum);
        DebugP_assert(localEventId != 0xFFFFFFFFU);

        UdmaUtils_mapLocaltoGlobalEvent(drvHandle, txChHandle, localEventId, 1U);

        obj->lastPlayed = MCASP_TX_DMA_TR_COUNT-1U;

        /* Reset BCDMA RT Pkt Count */
        do {
            status += Udma_chGetStats(txChHandle, &chStats);

            /* Reset/Decrement the number of processed packets */
            status += Udma_chDecStats(txChHandle, &chStats);

            status += Udma_chGetStats(txChHandle, &chStats);
        }while(chStats.packetCnt != 0U);
    }

    return status;
}

#else

int32_t MCASP_enableDmaTx(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    const MCASP_Attrs *attrs = NULL;
    Udma_ChStats chStats;

    if(NULL == config)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        obj = config->object;
        attrs = config->attrs;
    }

    if(status == SystemP_SUCCESS)
    {
        Udma_ChPdmaPrms pdmaPrms;
        Udma_ChHandle txChHandle = obj->dmaChCfg->txChHandle;

        /* Config PDMA channel */
        UdmaChPdmaPrms_init(&pdmaPrms);
        pdmaPrms.elemSize = UDMA_PDMA_ES_32BITS;

        /* Number of words received in each transfer */
        if(obj->txFifoEnable == 1U)
        {
            pdmaPrms.elemCnt = attrs->txFifoWaterLevel;
        }
        else
        {
            pdmaPrms.elemCnt = 1;
        }

        pdmaPrms.acc32 = 1U;
        pdmaPrms.burst = 1U;

        status = MCASP_primeTxTrpd(config);
        DebugP_assert(status == SystemP_SUCCESS);

        uint32_t txnByteCnt = obj->txDmaIcnt.txnByteCnt;
        pdmaPrms.fifoCnt = txnByteCnt/(WORD_BYTE_COUNT * pdmaPrms.elemCnt);

        status = Udma_chConfigPdma(txChHandle, &pdmaPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_chEnable(txChHandle);
        DebugP_assert(status == SystemP_SUCCESS);

        obj->lastPlayed = MCASP_TX_DMA_TR_COUNT-1U;

        /* Reset BCDMA RT Pkt Count */
        do {
            status += Udma_chGetStats(txChHandle, &chStats);

            /* Reset/Decrement the number of processed packets */
            status += Udma_chDecStats(txChHandle, &chStats);

            status += Udma_chGetStats(txChHandle, &chStats);
        }while(chStats.packetCnt != 0U);
    }

    return status;
}

#endif

int32_t MCASP_enableDmaRx(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    const MCASP_Attrs *attrs = NULL;
    Udma_ChStats chStats;

    if(NULL == config)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        obj = config->object;
        attrs = config->attrs;
    }

    if(status == SystemP_SUCCESS)
    {
        Udma_ChPdmaPrms pdmaPrms;
        Udma_ChHandle rxChHandle = obj->dmaChCfg->rxChHandle;

        /* Config PDMA channel */
        UdmaChPdmaPrms_init(&pdmaPrms);
        pdmaPrms.elemSize = UDMA_PDMA_ES_32BITS;

        /* Number of words received in each transfer */
        if(obj->rxFifoEnable == 1U)
        {
            pdmaPrms.elemCnt = attrs->rxFifoWaterLevel;
        }
        else
        {
            pdmaPrms.elemCnt = 1;
        }

        pdmaPrms.acc32 = 1U;
        pdmaPrms.burst = 1U;

        status = MCASP_primeRxTrpd(config);
        DebugP_assert(SystemP_SUCCESS == status);

        uint32_t txnByteCnt = obj->rxDmaIcnt.txnByteCnt;
        pdmaPrms.fifoCnt = txnByteCnt/(WORD_BYTE_COUNT * pdmaPrms.elemCnt);

        status = Udma_chConfigPdma(rxChHandle, &pdmaPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_chEnable(rxChHandle);
        DebugP_assert(SystemP_SUCCESS == status);

        obj->lastReceived = MCASP_RX_DMA_TR_COUNT-1U;

        /* Reset BCDMA RT Pkt Count */
        do {
            status += Udma_chGetStats(rxChHandle, &chStats);

            /* Reset/Decrement the number of processed packets */
            status += Udma_chDecStats(rxChHandle, &chStats);

            status += Udma_chGetStats(rxChHandle, &chStats);
        }while(chStats.packetCnt != 0U);
    }

    return status;
}

static int32_t MCASP_primeRxTrpd(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    CSL_UdmapTR3 *pTr = NULL;
    uint32_t i = 0;
    MCASP_Transaction **rxCbParam;
    Udma_DrvHandle drvHandle;

    if(config != NULL)
    {
        obj = config->object;
    }
    else
    {
        status = SystemP_FAILURE;
    }
    if(obj != NULL)
    {
        Udma_ChHandle rxChHandle = obj->dmaChCfg->rxChHandle;

        if(status == SystemP_SUCCESS)
        {
            uint32_t cqRingNum = Udma_chGetCqRingNum(rxChHandle);

            drvHandle = obj->mcaspDmaHandle;

            memset(obj->dmaChCfg->rxCbParams, 0, sizeof(MCASP_Transaction *)*MCASP_RX_DMA_TR_COUNT);

            memset(obj->dmaChCfg->rxTrpdMem, 0, MCASP_UDMA_TR3_TRPD_SIZE_RX*MCASP_RX_DMA_RING_ELEM_CNT);

            CacheP_wb(obj->dmaChCfg->rxTrpdMem, MCASP_UDMA_TR3_TRPD_SIZE_RX*MCASP_RX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

            UdmaUtils_makeTrpd((uint8_t *)obj->dmaChCfg->rxTrpdMem, UDMA_TR_TYPE_3, MCASP_RX_DMA_TR_COUNT, cqRingNum);

            /* Perpetual reload */
            UdmaUtils_setTrpdReload((uint8_t *)obj->dmaChCfg->rxTrpdMem, MCASP_DMA_PERPETUAL_RELOAD_CNT, 0U);

            /* Prime TRs in TRPD with loopjobs */
            for(i = 0; i < MCASP_RX_DMA_TR_COUNT; i++)
            {
                pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)obj->dmaChCfg->rxTrpdMem, i);

                pTr->flags = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_DATA_MOVE);
                pTr->flags |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);
                pTr->addr = (uint64_t)Udma_virtToPhyFxn(obj->RcvObj.txnLoopjob.buf, drvHandle, rxChHandle);

                status = MCASP_prepareDmaIcnts((MCASP_Handle)config, ((uint64_t)obj->RcvObj.txnLoopjob.count * (uint64_t)WORD_BYTE_COUNT),
                                                                0U);
                DebugP_assert(status == SystemP_SUCCESS);

                pTr->icnt0 = obj->rxDmaIcnt.icnt0;
                pTr->icnt1 = obj->rxDmaIcnt.icnt1;
                pTr->icnt2 = obj->rxDmaIcnt.icnt2;
                pTr->icnt3 = obj->rxDmaIcnt.icnt3;

                pTr->dim1     = pTr->icnt0;
                pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
            }

            /* Writeback the TRPD memory */
            CacheP_wb(obj->dmaChCfg->rxTrpdMem, MCASP_UDMA_TR3_TRPD_SIZE_RX*MCASP_RX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

            /* Prime ring memory with pointers to TRPD */
            uint64_t *ringPtr = (uint64_t *)obj->dmaChCfg->rxRingMem;
            *ringPtr = (uint64_t)Udma_virtToPhyFxn((uint8_t *)obj->dmaChCfg->rxTrpdMem, drvHandle, rxChHandle);

            /* Writeback ring memory */
            CacheP_wb(obj->dmaChCfg->rxRingMem, MCASP_UDMA_RING_ENTRY_SIZE * MCASP_RX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

            /* Check if there are txn already submitted */
            if(QueueP_isEmpty(obj->reqQueueHandleRx) == QueueP_NOTEMPTY)
            {
                MCASP_Transaction *txn = NULL;
                uint32_t txCnt = 0U;

                for(i = 0; i < MCASP_RX_DMA_TR_COUNT; i++)
                {
                    txn = QueueP_get(obj->reqQueueHandleRx);

                    if(txn != obj->reqQueueHandleRx)
                    {
                        /* Update last receive queued index */
                        obj->lastRecQueued= (obj->lastRecQueued + 1U)%(MCASP_RX_DMA_TR_COUNT);

                        pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)obj->dmaChCfg->rxTrpdMem, obj->lastRecQueued);

                        txCnt = (uint32_t)(txn->count * WORD_BYTE_COUNT);

                        status = MCASP_prepareDmaIcnts((MCASP_Handle)config, (txCnt),
                                                                0U);

                        DebugP_assert(status == SystemP_SUCCESS);

                        pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, drvHandle, rxChHandle);

                        pTr->icnt0 = obj->rxDmaIcnt.icnt0;
                        pTr->icnt1 = obj->rxDmaIcnt.icnt1;
                        pTr->icnt2 = obj->rxDmaIcnt.icnt2;
                        pTr->icnt3 = obj->rxDmaIcnt.icnt3;

                        pTr->dim1     = pTr->icnt0;
                        pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                        pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

                        CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);

                        rxCbParam = obj->dmaChCfg->rxCbParams;
                        rxCbParam = rxCbParam + (obj->lastRecQueued);
                        *rxCbParam = txn;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        /* Set doorbell to push the TRPD  */
        Udma_ringSetDoorBell(Udma_chGetFqRingHandle(rxChHandle), MCASP_RX_DMA_RING_ELEM_CNT);
    }

    return status;
}

void MCASP_disableDmaTx(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    Udma_ChHandle txChHandle = NULL;

    if(NULL != config)
    {
        obj = config->object;
        txChHandle = obj->dmaChCfg->txChHandle;

        status = Udma_chReset(txChHandle);

        while(TRUE)
        {
            int32_t  tempRetVal;
            uint64_t pDesc;
            tempRetVal = Udma_ringFlushRaw(Udma_chGetFqRingHandle(txChHandle), &pDesc);
            if(UDMA_ETIMEOUT == tempRetVal)
            {
                break;
            }
        }

        /* Set lastPlayed index as MCASP_TX_DMA_RING_ELEM_CNT-1. (So on playing first TRPD will be updated to 0) */
        obj->lastPlayed = MCASP_TX_DMA_TR_COUNT-1U;
        obj->lastFilled = MCASP_TX_DMA_TR_COUNT-1U;

        obj->txDmaIcnt.initDone = 0U;

        DebugP_assert(SystemP_SUCCESS == status);
    }
    else
    {
        /* Do nothing */
    }

    return;
}

void MCASP_disableDmaRx(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    Udma_ChHandle rxChHandle = NULL;
    uint8_t chanEnStatus;

    if(NULL != config)
    {
        obj = config->object;
        rxChHandle = obj->dmaChCfg->rxChHandle;

        status = Udma_chGetChanEnStatus(rxChHandle, &chanEnStatus);
        DebugP_assert(UDMA_SOK == status);
        if(chanEnStatus == 1U)
        {
            /* Disable Channel */
            status = Udma_chDisable(rxChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
        }

        while(TRUE)
        {
            int32_t  tempRetVal;
            uint64_t pDesc;
            tempRetVal = Udma_ringFlushRaw(Udma_chGetFqRingHandle(rxChHandle), &pDesc);
            if(UDMA_ETIMEOUT == tempRetVal)
            {
                break;
            }
        }

        /* Reset the rx channel if channel teardown fails */
        if(SystemP_SUCCESS != status)
        {
            status = Udma_chReset(rxChHandle);
        }

        /* Set last record queued index */
        obj->lastRecQueued = MCASP_RX_DMA_TR_COUNT-1U;
        obj->lastReceived = MCASP_RX_DMA_TR_COUNT-1U;

        obj->rxDmaIcnt.initDone = 0U;

        DebugP_assert(SystemP_SUCCESS == status);
    }
    else
    {
        /* Do nothing */
    }

    return;
}

#if defined (MCASP_TX_EVENT_TYPE_L2G)
static void MCASP_udmaIsrTx(Udma_EventHandle eventHandle,
                                 uint32_t eventType,
                                 void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *object = NULL;
    Udma_ChHandle txChHandle = NULL;
    Udma_DrvHandle drvHandle = NULL;
    MCASP_Transaction **txCbParam = NULL;
    MCASP_DmaChConfig *dmaChCfg = NULL;
    Udma_ChStats chStats;
    uint32_t pCnt = 0;
    void *trpdMem = NULL;
    uint32_t tempLastPlayed = 0;
    uint32_t totalPktCnt = 0;

    if(args != NULL)
    {
        object = ((MCASP_Config *)args)->object;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    /*
     * The ISR for the Tx DMA channel.
     *
     * This function is called from the UDMA ISR. It first retrieves the
     * statistics for the Tx DMA channel. Then it loops through the number of
     * packets that have been processed. For each packet, it updates the last
     * played index, updates the TR with the loop job, and calls the user
     * registered callback function. Finally, it resets the callback parameter
     * for the current packet.
     */
    if(status == SystemP_SUCCESS)
    {
        dmaChCfg = object->dmaChCfg;
        txChHandle = dmaChCfg->txChHandle;
        drvHandle = (Udma_DrvHandle)object->mcaspDmaHandle;

        tempLastPlayed = object->lastPlayed;

        do
        {
            status = Udma_chGetStats(txChHandle, &chStats);

            /* Reset/Decrement the number of processed packets */
            status += Udma_chDecStats(txChHandle, &chStats);

            pCnt = chStats.packetCnt;
            totalPktCnt += pCnt;

            while (pCnt != 0U)
            {
                pCnt--;

                trpdMem = object->dmaChCfg->txTrpdMem;

                /* Update last played index */
                object->lastPlayed = (object->lastPlayed + 1U)%MCASP_TX_DMA_TR_COUNT;

                /* Update current Processed TR with loopjob */
                {
                    CSL_UdmapTR15 *pTr = UdmaUtils_getTrpdTr15Pointer((uint8_t *)trpdMem, object->lastPlayed);
                    pTr = (CSL_UdmapTR15 *)Udma_phyToVirtFxn((uint64_t)pTr, drvHandle, txChHandle);
                    pTr->addr =(uint64_t)Udma_virtToPhyFxn(object->XmtObj.txnLoopjob.buf, drvHandle, txChHandle);

                    pTr->icnt0 = object->txDmaIcnt.icnt0;
                    pTr->icnt1 = object->txDmaIcnt.icnt1;
                    pTr->icnt2 = object->txDmaIcnt.icnt2;
                    pTr->icnt3 = object->txDmaIcnt.icnt3;

                    pTr->dim1     = pTr->icnt0;
                    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
                }

                txCbParam = object->dmaChCfg->txCbParams;
                txCbParam = txCbParam + (object->lastPlayed);

                /* Call the user registered callback function */
                if(NULL != *(txCbParam))
                {
                    MCASP_TransferObj *xfrObj = &(object->XmtObj);
                    if(xfrObj->cbFxn != NULL)
                    {
                        xfrObj->cbFxn((MCASP_Handle *)args, *(txCbParam));
                    }
                }

                /* Update the callback param to NULL */
                *(txCbParam) = NULL;
            }

            status += Udma_chGetStats(txChHandle, &chStats);
        } while(chStats.packetCnt != 0U);

        CacheP_wb((uint8_t *) UdmaUtils_getTrpdTr15Pointer((uint8_t *)object->dmaChCfg->txTrpdMem, 0),
                                        MCASP_TX_DMA_TR_COUNT*sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);
    }

    if(status == SystemP_SUCCESS)
    {
        uint32_t diff = 0;
        uint32_t nextCandidate = 0;

        if(tempLastPlayed < object->lastFilled)
        {
            diff = object->lastFilled - tempLastPlayed;
        }
        else
        {
            diff = (MCASP_TX_DMA_TR_COUNT-1U) - tempLastPlayed + object->lastFilled + 1U;
        }

        if(diff >= (totalPktCnt+2U))
        {
            nextCandidate = (object->lastFilled + 1U)%MCASP_TX_DMA_TR_COUNT;
        }
        else
        {
            nextCandidate = (object->lastPlayed + 2U)%MCASP_TX_DMA_TR_COUNT;
            object->lastFilled = MCASP_INVALID_TXN_IDX;
        }

        if(MCASP_INVALID_TXN_IDX == object->lastFilled)
        {
            nextCandidate = (object->lastPlayed + 2U)%MCASP_TX_DMA_TR_COUNT;
        }

        while (TRUE)
        {
            MCASP_Transaction *txn = NULL;
            CSL_UdmapTR15 *pTr = NULL;

            txn = QueueP_get(object->reqQueueHandleTx);

            if(txn != object->reqQueueHandleTx)
            {
                object->lastFilled = nextCandidate;

                txCbParam = object->dmaChCfg->txCbParams;
                txCbParam = txCbParam + (object->lastFilled);
                *(txCbParam) = txn;

                pTr = UdmaUtils_getTrpdTr15Pointer((uint8_t *)object->dmaChCfg->txTrpdMem, object->lastFilled);

                pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, drvHandle, txChHandle);

                pTr->icnt0 = object->txDmaIcnt.icnt0;
                pTr->icnt1 = object->txDmaIcnt.icnt1;
                pTr->icnt2 = object->txDmaIcnt.icnt2;
                pTr->icnt3 = object->txDmaIcnt.icnt3;

                CacheP_wb(pTr, sizeof(CSL_UdmapTR15), CacheP_TYPE_ALLD);

                nextCandidate = (nextCandidate+1U)%MCASP_TX_DMA_TR_COUNT;
            }
            else
            {
                break;
            }
        }
    }

    return;
}

#else

static void MCASP_udmaIsrTx(Udma_EventHandle eventHandle,
                                 uint32_t eventType,
                                 void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *object = NULL;
    Udma_ChHandle txChHandle = NULL;
    Udma_DrvHandle drvHandle = NULL;
    MCASP_Transaction **txCbParam = NULL;
    MCASP_DmaChConfig *dmaChCfg = NULL;
    Udma_ChStats chStats;
    uint32_t pCnt = 0;
    void *trpdMem = NULL;
    uint32_t tempLastPlayed = 0;
    uint32_t totalPktCnt = 0;

    if(args != NULL)
    {
        object = ((MCASP_Config *)args)->object;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    /*
     * The ISR for the Tx DMA channel.
     *
     * This function is called from the UDMA ISR. It first retrieves the
     * statistics for the Tx DMA channel. Then it loops through the number of
     * packets that have been processed. For each packet, it updates the last
     * played index, updates the TR with the loop job, and calls the user
     * registered callback function. Finally, it resets the callback parameter
     * for the current packet.
     */
    if(status == SystemP_SUCCESS)
    {
        dmaChCfg = object->dmaChCfg;
        txChHandle = dmaChCfg->txChHandle;
        drvHandle = (Udma_DrvHandle)object->mcaspDmaHandle;

        tempLastPlayed = object->lastPlayed;

        do
        {
            status = Udma_chGetStats(txChHandle, &chStats);

            /* Reset/Decrement the number of processed packets */
            status += Udma_chDecStats(txChHandle, &chStats);

            pCnt = chStats.packetCnt;
            totalPktCnt += pCnt;

            while (pCnt != 0U)
            {
                pCnt--;

                trpdMem = object->dmaChCfg->txTrpdMem;

                /* Update last played index */
                object->lastPlayed = (object->lastPlayed + 1U)%MCASP_TX_DMA_TR_COUNT;

                /* Update current Processed TR with loopjob */
                {
                    CSL_UdmapTR3 *pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)trpdMem, object->lastPlayed);
                    pTr = (CSL_UdmapTR3 *)Udma_phyToVirtFxn((uint64_t)pTr, drvHandle, txChHandle);
                    pTr->addr =(uint64_t)Udma_virtToPhyFxn(object->XmtObj.txnLoopjob.buf, drvHandle, txChHandle);

                    pTr->icnt0 = object->txDmaIcnt.icnt0;
                    pTr->icnt1 = object->txDmaIcnt.icnt1;
                    pTr->icnt2 = object->txDmaIcnt.icnt2;
                    pTr->icnt3 = object->txDmaIcnt.icnt3;

                    pTr->dim1     = pTr->icnt0;
                    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
                }

                txCbParam = object->dmaChCfg->txCbParams;
                txCbParam = txCbParam + (object->lastPlayed);

                /* Call the user registered callback function */
                if(NULL != *(txCbParam))
                {
                    MCASP_TransferObj *xfrObj = &(object->XmtObj);
                    if(xfrObj->cbFxn != NULL)
                    {
                        xfrObj->cbFxn((MCASP_Handle *)args, *(txCbParam));
                    }
                }

                /* Update the callback param to NULL */
                *(txCbParam) = NULL;
            }

            status += Udma_chGetStats(txChHandle, &chStats);
        } while(chStats.packetCnt != 0U);

        CacheP_wb((uint8_t *) UdmaUtils_getTrpdTr3Pointer((uint8_t *)object->dmaChCfg->txTrpdMem, 0),
                                        MCASP_TX_DMA_TR_COUNT*sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);
    }

    if(status == SystemP_SUCCESS)
    {
        uint32_t diff = 0;
        uint32_t nextCandidate = 0;

        if(tempLastPlayed < object->lastFilled)
        {
            diff = object->lastFilled - tempLastPlayed;
        }
        else
        {
            diff = (MCASP_TX_DMA_TR_COUNT-1U) - tempLastPlayed + object->lastFilled + 1U;
        }

        if(diff >= (totalPktCnt+2U))
        {
            nextCandidate = (object->lastFilled + 1U)%MCASP_TX_DMA_TR_COUNT;
        }
        else
        {
            nextCandidate = (object->lastPlayed + 2U)%MCASP_TX_DMA_TR_COUNT;
            object->lastFilled = MCASP_INVALID_TXN_IDX;
        }

        if(MCASP_INVALID_TXN_IDX == object->lastFilled)
        {
            nextCandidate = (object->lastPlayed + 2U)%MCASP_TX_DMA_TR_COUNT;
        }

        while (TRUE)
        {
            MCASP_Transaction *txn = NULL;
            CSL_UdmapTR3 *pTr = NULL;

            txn = QueueP_get(object->reqQueueHandleTx);

            if(txn != object->reqQueueHandleTx)
            {
                object->lastFilled = nextCandidate;

                txCbParam = object->dmaChCfg->txCbParams;
                txCbParam = txCbParam + (object->lastFilled);
                *(txCbParam) = txn;

                pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)object->dmaChCfg->txTrpdMem, object->lastFilled);

                pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, drvHandle, txChHandle);

                pTr->icnt0 = object->txDmaIcnt.icnt0;
                pTr->icnt1 = object->txDmaIcnt.icnt1;
                pTr->icnt2 = object->txDmaIcnt.icnt2;
                pTr->icnt3 = object->txDmaIcnt.icnt3;

                CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);

                nextCandidate = (nextCandidate+1U)%MCASP_TX_DMA_TR_COUNT;
            }
            else
            {
                break;
            }
        }
    }

    return;
}

#endif

static void MCASP_udmaIsrRx(Udma_EventHandle eventHandle,
                                 uint32_t eventType,
                                 void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *object = NULL;
    Udma_ChHandle rxChHandle = NULL;
    Udma_DrvHandle drvHandle = NULL;
    MCASP_Transaction **rxCbParam = NULL;
    MCASP_DmaChConfig *dmaChCfg = NULL;
    Udma_ChStats chStats;
    uint32_t pCnt = 0;
    void *trpdMem = NULL;
    uint32_t tempLastReceived = 0;
    uint32_t totalPktCnt = 0;

    if(args != NULL)
    {
        object = ((MCASP_Config *)args)->object;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    /*
     * The ISR for the Rx DMA channel.
     *
     * This function is called from the UDMA ISR. It first retrieves the
     * statistics for the Rx DMA channel. Then it loops through the number of
     * packets that have been processed. For each packet, it updates the last
     * played index, updates the TR with the loop job, and calls the user
     * registered callback function. Finally, it resets the callback parameter
     * for the current packet.
     */
    if(status == SystemP_SUCCESS)
    {
        dmaChCfg = object->dmaChCfg;
        rxChHandle = dmaChCfg->rxChHandle;
        drvHandle = (Udma_DrvHandle)object->mcaspDmaHandle;

        tempLastReceived = object->lastReceived;

        do
        {
            status = Udma_chGetStats(rxChHandle, &chStats);

            pCnt = chStats.packetCnt;
            totalPktCnt += pCnt;

            /* Reset/Decrement the number of processed packets */
            status += Udma_chDecStats(rxChHandle, &chStats);

            while (pCnt != 0U)
            {
                pCnt--;

                trpdMem = object->dmaChCfg->rxTrpdMem;

                /* Update last received index */
                object->lastReceived = (object->lastReceived + 1U)%MCASP_RX_DMA_TR_COUNT;

                /* Update current Processed TR with loopjob */
                {
                    CSL_UdmapTR3 *pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)trpdMem, object->lastReceived);
                    pTr = (CSL_UdmapTR3 *)Udma_phyToVirtFxn((uint64_t)pTr, drvHandle, rxChHandle);
                    pTr->addr =(uint64_t)Udma_virtToPhyFxn(object->RcvObj.txnLoopjob.buf, drvHandle, rxChHandle);

                    pTr->icnt0 = object->rxDmaIcnt.icnt0;
                    pTr->icnt1 = object->rxDmaIcnt.icnt1;
                    pTr->icnt2 = object->rxDmaIcnt.icnt2;
                    pTr->icnt3 = object->rxDmaIcnt.icnt3;

                    pTr->dim1     = pTr->icnt0;
                    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
                }

                rxCbParam = object->dmaChCfg->rxCbParams;
                rxCbParam = rxCbParam + (object->lastReceived);

                /* Call the user registered callback function */
                if(NULL != *(rxCbParam))
                {
                    MCASP_TransferObj *xfrObj = &(object->RcvObj);
                    if(xfrObj->cbFxn != NULL)
                    {
                        xfrObj->cbFxn((MCASP_Handle *)args, *(rxCbParam));
                    }
                }

                /* Update the callback param to NULL */
                *(rxCbParam) = NULL;
            }

            status += Udma_chGetStats(rxChHandle, &chStats);
        } while(chStats.packetCnt != 0U);

        CacheP_wb((uint8_t *) UdmaUtils_getTrpdTr3Pointer((uint8_t *)object->dmaChCfg->rxTrpdMem, 0),
                                        MCASP_RX_DMA_TR_COUNT*sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);
    }

    if(status == SystemP_SUCCESS)
    {
        uint32_t diff = 0;
        uint32_t nextCandidate = 0;

        if(tempLastReceived < object->lastRecQueued)
        {
            diff = object->lastRecQueued - tempLastReceived;
        }
        else
        {
            diff = (MCASP_RX_DMA_TR_COUNT-1U) - tempLastReceived + object->lastRecQueued + 1U;
        }

        if(diff >= (totalPktCnt+2U))
        {
            nextCandidate = (object->lastRecQueued + 1U)%MCASP_RX_DMA_TR_COUNT;
        }
        else
        {
            nextCandidate = (object->lastReceived+ 2U)%MCASP_RX_DMA_TR_COUNT;
            object->lastRecQueued = MCASP_INVALID_TXN_IDX;
        }

        if(MCASP_INVALID_TXN_IDX == object->lastRecQueued)
        {
            nextCandidate = (object->lastReceived+ 2U)%MCASP_TX_DMA_TR_COUNT;
        }

        while (TRUE)
        {
            MCASP_Transaction *txn = NULL;
            CSL_UdmapTR3 *pTr = NULL;

            txn = QueueP_get(object->reqQueueHandleRx);

            if(txn != object->reqQueueHandleRx)
            {
                object->lastRecQueued = nextCandidate;

                rxCbParam = object->dmaChCfg->rxCbParams;
                rxCbParam = rxCbParam + (object->lastRecQueued);
                *(rxCbParam) = txn;

                pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)object->dmaChCfg->rxTrpdMem, object->lastRecQueued);

                pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, drvHandle, rxChHandle);

                pTr->icnt0 = object->rxDmaIcnt.icnt0;
                pTr->icnt1 = object->rxDmaIcnt.icnt1;
                pTr->icnt2 = object->rxDmaIcnt.icnt2;
                pTr->icnt3 = object->rxDmaIcnt.icnt3;

                CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);

                nextCandidate = (nextCandidate+1U)%MCASP_TX_DMA_TR_COUNT;
            }
            else
            {
                break;
            }
        }
    }

    return;
}

int32_t MCASP_prepareDmaIcnts(MCASP_Handle handle, uint64_t byteCnt, uint8_t isTx)
{
    int32_t status = SystemP_SUCCESS;
    uint64_t txnByteCnt = 0U;
    MCASP_Object *object = NULL;
    const MCASP_Attrs *attrs = NULL;
    uint32_t tempIcntX = 0U;
    uint32_t tempIcntY = 0U;
    uint16_t waterLevel = 0U;

    if ((NULL == handle))
    {
        status = SystemP_FAILURE;
    }
    if(status  == SystemP_SUCCESS)
    {
        object = ((MCASP_Config *)handle)->object;
        attrs = ((MCASP_Config *)handle)->attrs;
    }

    if(status == SystemP_SUCCESS)
    {
        do
        {
            if(isTx == 1U)
            {
                txnByteCnt = byteCnt;

                if(object->txDmaIcnt.initDone == 1U)
                {
                    if(object->txDmaIcnt.txnByteCnt != txnByteCnt)
                    {
                        status = SystemP_FAILURE;
                        break;
                    }

                    if((object->XmtObj.txnLoopjob.count*WORD_BYTE_COUNT) != byteCnt)
                    {
                        DebugP_logError("Keep the transaction count same as loopjob count \r\n");
                        status = SystemP_FAILURE;
                        break;
                    }

                    if((attrs->txFifoWaterLevel != 0U) && ((byteCnt % (WORD_BYTE_COUNT * attrs->txFifoWaterLevel))!= 0U))
                    {
                        DebugP_logError("Keep the transaction count multiple of fifo water level \r\n");
                        status = SystemP_FAILURE;
                        break;
                    }
                }
                else
                {
                    if(attrs->txFifoWaterLevel != 0U)
                    {
                        waterLevel = attrs->txFifoWaterLevel;
                    }
                    else
                    {
                        waterLevel = 1U;
                    }

                    if(object->txDmaIcnt.initDone != MCASP_TXN_COUNT_OVERRIDE)
                    {
                        if((object->XmtObj.txnLoopjob.count*WORD_BYTE_COUNT) != byteCnt)
                        {
                            DebugP_logError("Keep the transaction count same as loopjob count \r\n");
                            status = SystemP_FAILURE;
                            break;
                        }
                    }
                    else
                    {
                        object->XmtObj.txnLoopjob.count = byteCnt/(WORD_BYTE_COUNT);
                    }

                    if((byteCnt % (WORD_BYTE_COUNT * waterLevel)) != 0U)
                    {
                        DebugP_logError("Keep the transaction count multiple of fifo water level \r\n");
                        status = SystemP_FAILURE;
                        break;
                    }

                    object->txDmaIcnt.icnt0 = WORD_BYTE_COUNT;
                    object->txDmaIcnt.icnt1 = (waterLevel);
                    tempIcntX = (uint32_t)(txnByteCnt/(WORD_BYTE_COUNT*(waterLevel)));
                    if(tempIcntX < MCASP_ICNT2_MAX)
                    {
                        object->txDmaIcnt.icnt2 = tempIcntX;
                        object->txDmaIcnt.icnt3 = 1U;
                    }
                    else
                    {
                        tempIcntX = tempIcntX&(-tempIcntX);
                        tempIcntY = txnByteCnt/(WORD_BYTE_COUNT*(waterLevel)*tempIcntX);
                        if((tempIcntY > MCASP_ICNT2_MAX) || (tempIcntX > MCASP_ICNT2_MAX))
                        {
                            DebugP_logError("Transaction count out of bounds \r\n");
                            status = SystemP_FAILURE;
                            break;
                        }
                        else
                        {
                            object->txDmaIcnt.icnt2 = (uint16_t)tempIcntX;
                            object->txDmaIcnt.icnt3 = (uint16_t)tempIcntY;
                        }
                    }

                    object->txDmaIcnt.txnByteCnt = txnByteCnt;
                    object->txDmaIcnt.initDone = 1;
                }
            }
            else
            {
                txnByteCnt = byteCnt;

                if(object->rxDmaIcnt.initDone == 1U)
                {
                    if(object->rxDmaIcnt.txnByteCnt != txnByteCnt)
                    {
                        status = SystemP_FAILURE;
                        break;
                    }

                    if((object->RcvObj.txnLoopjob.count*WORD_BYTE_COUNT) != txnByteCnt)
                    {
                        DebugP_logError("Keep the transaction count same as loopjob count \r\n");
                        status = SystemP_FAILURE;
                        break;
                    }

                    if((attrs->rxFifoWaterLevel != 0U) && ((byteCnt % (WORD_BYTE_COUNT * attrs->rxFifoWaterLevel)) != 0U))
                    {
                        DebugP_logError("Keep the transaction count multiple of fifo water level \r\n");
                        status = SystemP_FAILURE;
                        break;
                    }
                }
                else
                {
                    if(attrs->rxFifoWaterLevel != 0U)
                    {
                        waterLevel = attrs->rxFifoWaterLevel;
                    }
                    else
                    {
                        waterLevel = 1U;
                    }

                    if(object->rxDmaIcnt.initDone != MCASP_TXN_COUNT_OVERRIDE)
                    {
                        if((object->RcvObj.txnLoopjob.count*WORD_BYTE_COUNT) != txnByteCnt)
                        {
                            DebugP_logError("Keep the transaction count same as loopjob count \r\n");
                            status = SystemP_FAILURE;
                            break;
                        }
                    }
                    else
                    {
                        object->RcvObj.txnLoopjob.count = byteCnt/(WORD_BYTE_COUNT);
                    }

                    if((byteCnt % (WORD_BYTE_COUNT * waterLevel)) != 0U)
                    {
                        DebugP_logError("Keep the transaction count multiple of fifo water level \r\n");
                        status = SystemP_FAILURE;
                        break;
                    }

                    object->rxDmaIcnt.icnt0 = WORD_BYTE_COUNT;
                    object->rxDmaIcnt.icnt1 = waterLevel;
                    tempIcntX = (uint32_t)(txnByteCnt/(WORD_BYTE_COUNT*waterLevel));
                    if(tempIcntX < MCASP_ICNT2_MAX)
                    {
                        object->rxDmaIcnt.icnt2 = (uint16_t)tempIcntX;
                        object->rxDmaIcnt.icnt3 = 1U;
                    }
                    else
                    {
                        tempIcntX = tempIcntX&(-tempIcntX);
                        tempIcntY = (uint32_t)(txnByteCnt/(WORD_BYTE_COUNT*waterLevel*tempIcntX));
                        if((tempIcntY > MCASP_ICNT2_MAX) || (tempIcntX > MCASP_ICNT2_MAX))
                        {
                            DebugP_logError("Transaction count out of bounds \r\n");
                            status = SystemP_FAILURE;
                            break;
                        }
                        else
                        {
                            object->rxDmaIcnt.icnt2 = (uint16_t)tempIcntX;
                            object->rxDmaIcnt.icnt3 = (uint16_t)tempIcntY;
                        }
                    }

                    object->rxDmaIcnt.txnByteCnt = txnByteCnt;
                    object->rxDmaIcnt.initDone = 1U;
                }
            }
        } while(FALSE);
    }

    return status;
}

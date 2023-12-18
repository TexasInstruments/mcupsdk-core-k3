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
#include <drivers/mcasp/v1/mcasp_drv_configs/mcasp_drv_config.h>

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */
#define MCASP_DMA_L0_MAX_XFER_SIZE                      (65536U)

#define MCASP_DMA_UDMA_XFER_SIZE                        (64512U)

#define MCASP_BCDMA_TX_CH_DEPTH                         (64U)

#define MCASP_UDMA_TR3_TRPD_SIZE         (UDMA_GET_TRPD_TR3_SIZE(1))
#define MCASP_UDMA_HPD_SIZE              (UDMA_ALIGN_SIZE((sizeof(CSL_UdmapCppi5HMPD))))

#define MCASP_UDMA_RING_ENTRY_SIZE       (sizeof(uint64_t))
#define MCASP_UDMA_RING_MEM_SIZE_TX      (MCASP_TX_DMA_RING_ELEM_CNT * MCASP_UDMA_RING_ENTRY_SIZE)
#define MCASP_UDMA_RING_MEM_SIZE_RX      (MCASP_RX_DMA_RING_ELEM_CNT * MCASP_UDMA_RING_ENTRY_SIZE)

#define MCASP_PDMA_ELEM_CNT_WITH_FIFO    (32U)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void MCASP_udmaIsrTx(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args);

static void MCASP_udmaIsrRx(Udma_EventHandle eventHandle, uint32_t eventType,
                                                    void *args);

static int32_t MCASP_primeTxTrpd(MCASP_Config *config);

static int32_t MCASP_primeRxHpd(MCASP_Config *config);

static void MCASP_udmaTrInit(uint8_t *pTrpd, uint64_t pBuf, uint32_t bufSize);

static void MCASP_udmaHpdInit(Udma_ChHandle chHandle, uint8_t *pHpdMem,
                              const void *destBuf, uint32_t length);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t MCASP_openDma(MCASP_Config *config, MCASP_DmaChConfig *dmaChCfg)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    Udma_DrvHandle drvHandle = NULL;
    Udma_DrvHandle drvPktHandle = NULL;

    if(config != NULL)
    {
        obj = config->object;
        drvHandle = (Udma_DrvHandle)obj->mcaspDmaHandle;
        drvPktHandle = (Udma_DrvHandle)obj->mcaspPktDmaHandle;
    }
    else
    {
        status = SystemP_SUCCESS;
    }

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

        /* TODO: check configurable values ? */
        txPrms.fifoDepth = MCASP_BCDMA_TX_CH_DEPTH;

        status = Udma_chConfigTx(txChHandle, &txPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Register ring completion callback */
        eventHandle = dmaChCfg->cqTxEvtHandle;
        UdmaEventPrms_init(&eventPrms);
        eventPrms.eventType             = UDMA_EVENT_TYPE_DMA_COMPLETION;
        eventPrms.eventMode             = UDMA_EVENT_MODE_SHARED;
        eventPrms.chHandle              = txChHandle;
        eventPrms.masterEventHandle     = Udma_eventGetGlobalHandle(drvHandle);
        eventPrms.eventCb               = &MCASP_udmaIsrTx;
        eventPrms.appData               = config;
        status = Udma_eventRegister(drvHandle, eventHandle, &eventPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Set lastPlayed index as MCASP_TX_DMA_RING_ELEM_CNT-1. (So on playing first TRPD will be updated to 0) */
        obj->lastPlayed = MCASP_TX_DMA_RING_ELEM_CNT-1;

        obj->lastFilled = MCASP_TX_DMA_RING_ELEM_CNT-1;
    }

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

        status = Udma_chOpen(drvPktHandle, rxChHandle, chType, &chPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        UdmaChRxPrms_init(&rxPrms, chType);

        rxPrms.chanType = TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_PACKET_SINGLE_BUF;
        rxPrms.configDefaultFlow = FALSE;
        status = Udma_chConfigRx(rxChHandle, &rxPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Register ring completion callback */
        eventHandle = dmaChCfg->cqRxEvtHandle;
        UdmaEventPrms_init(&eventPrms);
        eventPrms.eventType             = UDMA_EVENT_TYPE_DMA_COMPLETION;
        eventPrms.eventMode             = UDMA_EVENT_MODE_SHARED;
        eventPrms.chHandle              = rxChHandle;
        eventPrms.masterEventHandle     = Udma_eventGetGlobalHandle(drvPktHandle);
        eventPrms.eventCb               = &MCASP_udmaIsrRx;
        eventPrms.appData               = config;
        status = Udma_eventRegister(drvPktHandle, eventHandle, &eventPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Set last record queued index */
        obj->lastRecQueued = MCASP_RX_DMA_RING_ELEM_CNT-1;

        /* Set lastReceived index as 63. (So on playing first TRPD will be updated to 0) */
        obj->lastReceived = MCASP_RX_DMA_RING_ELEM_CNT-1;
    }

    return status;
}

static int32_t MCASP_primeTxTrpd(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    CSL_UdmapTR3 *pTr = NULL;
    uint32_t i = 0;
    MCASP_Transaction **txCbParam;

    if(config != NULL)
    {
        obj = config->object;
    }
    else
    {
        status = SystemP_SUCCESS;
    }

    if(status == SystemP_SUCCESS)
    {
        Udma_ChHandle txChHandle = obj->dmaChCfg->txChHandle;

        uint32_t cqRingNum = Udma_chGetCqRingNum(txChHandle);

        memset(obj->dmaChCfg->txCbParams, 0, sizeof(MCASP_Transaction *)*MCASP_TX_DMA_RING_ELEM_CNT);

        memset(obj->dmaChCfg->txTrpdMem, 0, MCASP_UDMA_TR3_TRPD_SIZE*MCASP_TX_DMA_RING_ELEM_CNT);

        CacheP_wb(obj->dmaChCfg->txTrpdMem, MCASP_UDMA_TR3_TRPD_SIZE*MCASP_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

        /* Prime TRPD mem with the TRPDs all containing loopjobs */
        for(i = 0; i < MCASP_TX_DMA_RING_ELEM_CNT; i++)
        {
            UdmaUtils_makeTrpd(((uint8_t *)obj->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*i)), UDMA_TR_TYPE_3, 1, cqRingNum);

            CacheP_wb(((uint8_t *)obj->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*i)), MCASP_UDMA_TR3_TRPD_SIZE, CacheP_TYPE_ALLD);

            pTr = UdmaUtils_getTrpdTr3Pointer(((uint8_t *)obj->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*i)), 0);

            pTr->flags = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_DATA_MOVE);
            pTr->flags |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);
            pTr->addr = (uint64_t)obj->XmtObj.txnLoopjob.buf;
            pTr->icnt0 = (uint16_t)(obj->XmtObj.txnLoopjob.count*sizeof(uint32_t));
            pTr->icnt1 = 1;
            pTr->icnt2 = 1;
            pTr->icnt3 = 1;

            pTr->dim1     = pTr->icnt0;
            pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
            pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
        }

        /* Writeback the TRPD memory */
        CacheP_wb(obj->dmaChCfg->txTrpdMem, MCASP_UDMA_TR3_TRPD_SIZE*MCASP_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

        /* Prime ring memory with pointers to TRPD */
        for(i = 0; i < MCASP_TX_DMA_RING_ELEM_CNT; i++)
        {
            uint64_t *ringPtr = (uint64_t *)((uint8_t *)obj->dmaChCfg->txRingMem + (i*sizeof(uint64_t)));
            *ringPtr = (uint64_t)((uint8_t *)obj->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*i));
        }

        /* Writeback ring memory */
        CacheP_wb(obj->dmaChCfg->txRingMem, MCASP_UDMA_RING_ENTRY_SIZE * MCASP_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

        /* Check if there are txn already submitted */
        if(!QueueP_isEmpty(obj->reqQueueHandleTx))
        {
            MCASP_Transaction *txn = NULL;
            uint64_t txCnt = 0;
            uint32_t quotient = 0U;
            uint32_t remainder = 0U;
            uint16_t icnt[4] = { 0U, 0U, 0U, 0U };

            for(i = 0; i < MCASP_TX_DMA_RING_ELEM_CNT; i++)
            {
                txn = QueueP_get(obj->reqQueueHandleTx);

                if(txn != obj->reqQueueHandleTx)
                {
                    /* Update last filled index */
                    obj->lastFilled = (obj->lastFilled + 1)%(MCASP_TX_DMA_RING_ELEM_CNT);

                    pTr = UdmaUtils_getTrpdTr3Pointer(((uint8_t *)obj->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*obj->lastFilled)), 0);

                    txCnt = (uint64_t)(txn->count*4);
                    if(txCnt < MCASP_DMA_L0_MAX_XFER_SIZE)
                    {
                        icnt[0] = (uint16_t)(txCnt);
                        icnt[1] = 1;
                    }
                    else
                    {
                        icnt[0] = (uint16_t)MCASP_DMA_UDMA_XFER_SIZE;
                        quotient = (uint32_t)(txCnt / MCASP_DMA_UDMA_XFER_SIZE);
                        remainder = (uint32_t)(txCnt % MCASP_DMA_UDMA_XFER_SIZE);
                        icnt[1] = (uint16_t)quotient;
                    }

                    icnt[2] = (uint16_t)1U;
                    icnt[3] = (uint16_t)1U;

                    pTr->addr = (uint64_t)txn->buf;
                    pTr->icnt0 = icnt[0];
                    pTr->icnt1 = icnt[1];
                    pTr->icnt2 = icnt[2];
                    pTr->icnt3 = icnt[3];

                    pTr->dim1     = pTr->icnt0;
                    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

                    CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);

                    if(remainder != 0)
                    {
                        i++;

                        obj->lastFilled = (obj->lastFilled + 1)%(MCASP_TX_DMA_RING_ELEM_CNT);

                        pTr = UdmaUtils_getTrpdTr3Pointer(((uint8_t *)obj->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*obj->lastFilled)), 0);

                        pTr->addr = (uint64_t)((uint8_t *)txn->buf + (txCnt- remainder));
                        pTr->icnt0 = (uint16_t)remainder;
                        pTr->icnt1 = (uint16_t)1U;
                        pTr->icnt2 = (uint16_t)1U;
                        pTr->icnt3 = (uint16_t)1U;

                        pTr->dim1     = pTr->icnt0;
                        pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                        pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

                        CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);
                    }

                    txCbParam = obj->dmaChCfg->txCbParams;
                    txCbParam += obj->lastFilled;
                    *txCbParam = txn;
                }
                else
                {
                    break;
                }
            }
        }

        /* Set doorbell to push the number of TRPDs queued */
        Udma_ringSetDoorBell(Udma_chGetFqRingHandle(txChHandle), i);
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

        while(1)
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

        status = Udma_chDisable(rxChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
        DebugP_assert(SystemP_SUCCESS == status);

        while(1)
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
    MCASP_Object *obj = NULL;

    if(NULL == config)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        obj = config->object;
    }

    if(status == SystemP_SUCCESS)
    {
        Udma_ChPdmaPrms pdmaPrms;
        Udma_ChHandle txChHandle = obj->dmaChCfg->txChHandle;

        /* Config PDMA channel */
        UdmaChPdmaPrms_init(&pdmaPrms);
        pdmaPrms.elemSize = UDMA_PDMA_ES_32BITS;

        /* Number of words received in each transfer */
        if(obj->txFifoEnable == 1)
        {
            pdmaPrms.elemCnt = MCASP_PDMA_ELEM_CNT_WITH_FIFO;
        }
        else
        {
            pdmaPrms.elemCnt = 1;
        }
        pdmaPrms.fifoCnt = 0U;

        pdmaPrms.acc32 = 1U;
        pdmaPrms.burst = 1U;

        status = Udma_chConfigPdma(txChHandle, &pdmaPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_chEnable(txChHandle);
        DebugP_assert(status == SystemP_SUCCESS);

        status = MCASP_primeTxTrpd(config);
        DebugP_assert(status == SystemP_SUCCESS);
    }

    return status;
}

int32_t MCASP_enableDmaRx(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;

    if(NULL == config)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        obj = config->object;
    }


    if(status == SystemP_SUCCESS)
    {
        Udma_ChPdmaPrms pdmaPrms;
        Udma_ChHandle rxChHandle = obj->dmaChCfg->rxChHandle;

        /* Config PDMA channel */
        UdmaChPdmaPrms_init(&pdmaPrms);
        pdmaPrms.elemSize = UDMA_PDMA_ES_32BITS;

        /* Number of words received in each transfer */
        if(obj->rxFifoEnable == 1)
        {
            pdmaPrms.elemCnt = MCASP_PDMA_ELEM_CNT_WITH_FIFO;
        }
        else
        {
            pdmaPrms.elemCnt = 1;
        }
        pdmaPrms.fifoCnt = 0U;

        pdmaPrms.acc32 = 1U;
        pdmaPrms.burst = 1U;

        status = Udma_chConfigPdma(rxChHandle, &pdmaPrms);
        DebugP_assert(SystemP_SUCCESS == status);

        status = Udma_chEnable(rxChHandle);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Prime Rx host packet descriptors */
        MCASP_primeRxHpd(config);

        DebugP_assert(SystemP_SUCCESS == status);

    }

    return status;
}

static void MCASP_udmaHpdInit(Udma_ChHandle chHandle,
                              uint8_t       *pHpdMem,
                              const void    *destBuf,
                              uint32_t      length)
{
    CSL_UdmapCppi5HMPD *pHpd = (CSL_UdmapCppi5HMPD *) pHpdMem;
    uint32_t descType = (uint32_t)CSL_UDMAP_CPPI5_PD_DESCINFO_DTYPE_VAL_HOST;

    /* Setup descriptor */
    CSL_udmapCppi5SetDescType(pHpd, descType);
    CSL_udmapCppi5SetEpiDataPresent(pHpd, FALSE);
    CSL_udmapCppi5SetPsDataLoc(pHpd, 0U);
    CSL_udmapCppi5SetPsDataLen(pHpd, 0U);
    CSL_udmapCppi5SetPktLen(pHpd, descType, length);
    CSL_udmapCppi5SetPsFlags(pHpd, 0U);
    CSL_udmapCppi5SetIds(pHpd, descType, 0x321, UDMA_DEFAULT_FLOW_ID);
    CSL_udmapCppi5SetSrcTag(pHpd, 0x0000);     /* Not used */
    CSL_udmapCppi5SetDstTag(pHpd, 0x0000);     /* Not used */
    /* Return Policy descriptors are reserved in case of AM243X/Am64X */
    CSL_udmapCppi5SetReturnPolicy(
        pHpd,
        descType,
        0U,
        0U,
        0U,
        0U);
    CSL_udmapCppi5LinkDesc(pHpd, 0U);
    CSL_udmapCppi5SetBufferAddr(pHpd, (uint64_t) Udma_defaultVirtToPhyFxn(destBuf, 0U, NULL));
    CSL_udmapCppi5SetBufferLen(pHpd, length);
    CSL_udmapCppi5SetOrgBufferAddr(pHpd, (uint64_t) Udma_defaultVirtToPhyFxn(destBuf, 0U, NULL));
    CSL_udmapCppi5SetOrgBufferLen(pHpd, length);

    /* Writeback cache */
    CacheP_wb(pHpdMem, sizeof(CSL_UdmapCppi5HMPD), CacheP_TYPE_ALLD);

    return;
}

static int32_t MCASP_primeRxHpd(MCASP_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Object *obj = NULL;
    uint32_t i;
    MCASP_Transaction **rxCbParam = NULL;

    if(config != NULL)
    {
        obj = config->object;
    }
    else
    {
        status = SystemP_SUCCESS;
    }

    if(status == SystemP_SUCCESS)
    {
        Udma_ChHandle rxChHandle = obj->dmaChCfg->rxChHandle;

        memset(obj->dmaChCfg->rxCbParams, 0, sizeof(MCASP_Transaction *)*MCASP_RX_DMA_RING_ELEM_CNT);

        /* Prime TRPD mem with the TRPDs all containing loopjobs */
        for(i = 0; i < MCASP_RX_DMA_RING_ELEM_CNT; i++)
        {
            MCASP_udmaHpdInit(rxChHandle,
                            ((uint8_t *)obj->dmaChCfg->rxTrpdMem + (MCASP_UDMA_HPD_SIZE*i)),
                              obj->RcvObj.txnLoopjob.buf,
                              obj->RcvObj.txnLoopjob.count*sizeof(uint32_t));
        }

        /* Prime ring memory with pointers to TRPD */
        for(i = 0; i < MCASP_RX_DMA_RING_ELEM_CNT; i++)
        {
            uint64_t *ringPtr = (uint64_t *)((uint8_t *)obj->dmaChCfg->rxRingMem + (i*sizeof(uint64_t)));
            *ringPtr = (uint64_t)((uint8_t *)obj->dmaChCfg->rxTrpdMem + (MCASP_UDMA_HPD_SIZE*i));
        }

        CacheP_wb(obj->dmaChCfg->rxRingMem, MCASP_RX_DMA_RING_ELEM_CNT * MCASP_UDMA_RING_ENTRY_SIZE, CacheP_TYPE_ALLD);

        /* Check if there are txn already submitted for receiving */
        if(!QueueP_isEmpty(obj->reqQueueHandleRx))
        {
            MCASP_Transaction *txn = NULL;

            for(i = 0; i < MCASP_RX_DMA_RING_ELEM_CNT; i++)
            {
                txn = QueueP_get(obj->reqQueueHandleRx);

                if(txn != obj->reqQueueHandleRx)
                {
                    obj->lastRecQueued = (obj->lastRecQueued+1)%MCASP_RX_DMA_RING_ELEM_CNT;
                    MCASP_udmaHpdInit(rxChHandle,
                              ((uint8_t *)obj->dmaChCfg->rxTrpdMem + (MCASP_UDMA_HPD_SIZE*obj->lastRecQueued)),
                              txn->buf,
                              txn->count*sizeof(uint32_t));

                    rxCbParam = (MCASP_Transaction **)obj->dmaChCfg->rxCbParams + obj->lastRecQueued;
                    *(rxCbParam) = txn;
                }
                else
                {
                    break;
                }
            }
        }

        /* Set doorbell to inform the number of TRPDs queued */
        Udma_ringSetDoorBell(Udma_chGetFqRingHandle(rxChHandle), i);
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

static void MCASP_udmaTrInit(uint8_t *pTrpd, uint64_t pBuf, uint32_t bufSize)
{
    CSL_UdmapTR3 *pTr = NULL;
    uint16_t icnt[4] = { 0U, 0U, 0U, 0U };
    uint32_t quotient = 0U;

    if(pTrpd != NULL)
    {
        pTr = UdmaUtils_getTrpdTr3Pointer(pTrpd, 0);

        if(bufSize < MCASP_DMA_L0_MAX_XFER_SIZE)
        {
            icnt[0] = (uint16_t)(bufSize);
            icnt[1] = 0;
        }
        else
        {
            icnt[0] = (uint16_t)MCASP_DMA_UDMA_XFER_SIZE;
            quotient = bufSize / MCASP_DMA_UDMA_XFER_SIZE;
            icnt[1] = (uint16_t)(quotient);
        }

        icnt[2] = (uint16_t)1U;
        icnt[3] = (uint16_t)1U;

        pTr->addr = pBuf;
        pTr->icnt0 = icnt[0];
        pTr->icnt1 = icnt[1];
        pTr->icnt2 = icnt[2];
        pTr->icnt3 = icnt[3];

        pTr->dim1     = pTr->icnt0;
        pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
        pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

        CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);
    }
}

static void MCASP_udmaIsrTx(Udma_EventHandle eventHandle,
                                 uint32_t eventType,
                                 void *args)
{
    uint64_t pDesc;
    MCASP_Object *object;
    Udma_ChHandle txChHandle;
    MCASP_Transaction **txCbParam;

    object = ((MCASP_Config *)args)->object;

    MCASP_DmaChConfig *dmaChCfg = object->dmaChCfg;
    txChHandle = dmaChCfg->txChHandle;

    Udma_RingHandle ringHandle = Udma_chGetFqRingHandle(txChHandle);

    uint32_t ringOccPopCnt = 0;

    while(Udma_ringGetReverseRingOcc(ringHandle))
    {
        ringOccPopCnt++;

        int32_t status = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(txChHandle), &pDesc);
        DebugP_assert(SystemP_SUCCESS == status);

        /* Update current Processed TRPD with loopjob */
        {
            CSL_UdmapTR3 *pTr = (CSL_UdmapTR3 *)UdmaUtils_getTrpdTr3Pointer((uint8_t *)pDesc, 0);
            pTr->addr =(uint64_t)object->XmtObj.txnLoopjob.buf;
            pTr->icnt0 = (uint16_t)(object->XmtObj.txnLoopjob.count * sizeof(uint32_t));
            pTr->icnt1 = 1;
            pTr->icnt2 = 1;
            pTr->icnt3 = 1;

            pTr->dim1     = pTr->icnt0;
            pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
            pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

            CacheP_wb((uint8_t *)pDesc, MCASP_UDMA_TR3_TRPD_SIZE, CacheP_TYPE_ALLD);
        }

        /* Update last played index */
        uint32_t tmpLastPlayed = object->lastPlayed +1;
        object->lastPlayed = (tmpLastPlayed)%MCASP_TX_DMA_RING_ELEM_CNT;

        txCbParam = object->dmaChCfg->txCbParams;
        txCbParam += object->lastPlayed;

        if(NULL != *(txCbParam))
        {
            MCASP_TransferObj *xfrObj = &(object->XmtObj);
            if(xfrObj->cbFxn != NULL)
            {
                xfrObj->cbFxn((MCASP_Handle *)args, *(txCbParam));
            }
        }

        *(txCbParam) = NULL;
    }

    uint32_t txnPushed = 0;

    while(ringOccPopCnt > 0)
    {
        ringOccPopCnt--;

        MCASP_Transaction *txn = NULL;
        CSL_UdmapTR3 *pTr;
        uint32_t nextCandidate;
        uint64_t txCnt = 0;

        nextCandidate = (object->lastFilled+1)%MCASP_TX_DMA_RING_ELEM_CNT;

        pTr = UdmaUtils_getTrpdTr3Pointer(((uint8_t *)object->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*nextCandidate)), 0);

        /* If nextCandidate has relevant buffer to send; continue, else fill up with next buffer */
        if(pTr->addr == (uint64_t)object->XmtObj.txnLoopjob.buf)
        {
            txn = QueueP_get(object->reqQueueHandleTx);

            if(txn != object->reqQueueHandleTx)
            {
                txCnt = (uint64_t)(txn->count*4);

                if(txCnt < MCASP_DMA_L0_MAX_XFER_SIZE)
                {
                    MCASP_udmaTrInit(((uint8_t *)object->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*nextCandidate)),
                                        (uint64_t)txn->buf, txCnt);

                    object->lastFilled = nextCandidate;

                    txCbParam = object->dmaChCfg->txCbParams;
                    txCbParam += object->lastFilled;
                    *(txCbParam) = txn;

                    txnPushed++;
                }
                else
                {
                    if(txCnt % MCASP_DMA_UDMA_XFER_SIZE)
                    {
                        MCASP_udmaTrInit(((uint8_t *)object->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*nextCandidate)),
                                        (uint64_t)txn->buf, txCnt);

                        object->lastFilled = nextCandidate;

                        txnPushed++;

                        nextCandidate = (object->lastFilled+1)%MCASP_TX_DMA_RING_ELEM_CNT;
                        object->lastFilled = nextCandidate;

                        MCASP_udmaTrInit(((uint8_t *)object->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*nextCandidate)),
                                        (uint64_t)((uint8_t *)txn->buf + (txCnt- (txCnt % MCASP_DMA_UDMA_XFER_SIZE))), txCnt % MCASP_DMA_UDMA_XFER_SIZE);

                        txCbParam = object->dmaChCfg->txCbParams;
                        txCbParam += object->lastFilled;
                        *(txCbParam) = txn;

                        txnPushed++;
                    }
                    else
                    {
                        MCASP_udmaTrInit(((uint8_t *)object->dmaChCfg->txTrpdMem + (MCASP_UDMA_TR3_TRPD_SIZE*nextCandidate)),
                                        (uint64_t)txn->buf, txCnt);

                        object->lastFilled = nextCandidate;

                        txCbParam = object->dmaChCfg->txCbParams;
                        txCbParam += object->lastFilled;
                        *(txCbParam) = txn;

                        txnPushed++;
                    }
                }
            }
            else
            {
                int32_t diff = ((object->lastFilled - object->lastPlayed)%MCASP_TX_DMA_RING_ELEM_CNT);
                if(diff < 2)
                {
                    object->lastFilled = (object->lastFilled+1)%MCASP_TX_DMA_RING_ELEM_CNT;
                    txnPushed++;
                }
            }
        }
    }

    Udma_ringSetDoorBell(Udma_chGetFqRingHandle(txChHandle), txnPushed);
}

static void MCASP_udmaIsrRx(Udma_EventHandle eventHandle, uint32_t eventType, void *args)
{
    int32_t status;
    uint64_t pDesc;
    MCASP_Object *object = NULL;
    MCASP_DmaChConfig *dmaChCfg = NULL;
    Udma_ChHandle rxChHandle;
    Udma_RingHandle ringHandle;
    uint32_t ringOccPopCnt = 0;
    MCASP_TransferObj *xfrObj;
    MCASP_Transaction *txn = NULL;
    uint32_t nextCandidate;
    CSL_UdmapCppi5HMPD *pHpd;
    uint32_t txnPushed = 0;
    int32_t diff;
    MCASP_Transaction **rxCbParam = NULL;

    if(args != NULL)
    {
        object = ((MCASP_Config *)args)->object;
        dmaChCfg = object->dmaChCfg;
        rxChHandle = dmaChCfg->rxChHandle;
        ringHandle = Udma_chGetFqRingHandle(rxChHandle);
        xfrObj = &(object->RcvObj);

        status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        while(Udma_ringGetReverseRingOcc(ringHandle))
        {
            ringOccPopCnt++;
            status = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(rxChHandle), &pDesc);
            DebugP_assert(SystemP_SUCCESS == status);

            /* update last received index */
            uint32_t tmpLastReceived = object->lastReceived+1;
            object->lastReceived = (tmpLastReceived)%MCASP_RX_DMA_RING_ELEM_CNT;

            /* Update current processed TRPD with loopjob */
            {
                MCASP_udmaHpdInit(rxChHandle,
                                (uint8_t *)pDesc,
                                object->RcvObj.txnLoopjob.buf,
                                object->RcvObj.txnLoopjob.count*sizeof(uint32_t));
            }

            rxCbParam = (MCASP_Transaction **)object->dmaChCfg->rxCbParams + object->lastReceived;

            if(NULL != *(rxCbParam))
            {
                if(xfrObj->cbFxn != NULL)
                {
                    xfrObj->cbFxn((MCASP_Handle *)args, *rxCbParam);
                }
            }
            *rxCbParam = NULL;
        }

        while (ringOccPopCnt > 0)
        {
            ringOccPopCnt--;

            nextCandidate = (object->lastRecQueued+1)%MCASP_RX_DMA_RING_ELEM_CNT;

            pHpd = (CSL_UdmapCppi5HMPD *)((uint8_t *)object->dmaChCfg->rxTrpdMem + (MCASP_UDMA_HPD_SIZE*nextCandidate));

            if(!QueueP_isEmpty(object->reqQueueHandleRx))
            {
                if(CSL_udmapCppi5GetBufferAddr(pHpd) == (uint64_t)object->RcvObj.txnLoopjob.buf)
                {
                    txn = QueueP_get(object->reqQueueHandleRx);

                    MCASP_udmaHpdInit(rxChHandle,
                                (uint8_t *)pHpd,
                                txn->buf,
                                txn->count *sizeof(uint32_t));
                    rxCbParam = (MCASP_Transaction **)object->dmaChCfg->rxCbParams + nextCandidate;
                    *rxCbParam = txn;

                    object->lastRecQueued = (object->lastRecQueued+1)%MCASP_RX_DMA_RING_ELEM_CNT;
                    txnPushed++;
                }
            }
            else
            {
                diff = (int32_t)((int32_t)object->lastReceived - (int32_t)object->lastRecQueued)%64;
                if(diff < 2)
                {
                    object->lastRecQueued = (object->lastRecQueued+1)%MCASP_RX_DMA_RING_ELEM_CNT;
                    txnPushed++;
                }
            }
        }

        /* Push remaining Txn queued */
        while (!QueueP_isEmpty(object->reqQueueHandleRx))
        {
            nextCandidate = (object->lastRecQueued+1)%MCASP_RX_DMA_RING_ELEM_CNT;

            pHpd = (CSL_UdmapCppi5HMPD *)((uint8_t *)object->dmaChCfg->rxTrpdMem + (MCASP_UDMA_HPD_SIZE*nextCandidate));

            if(CSL_udmapCppi5GetBufferAddr(pHpd) == (uint64_t)object->RcvObj.txnLoopjob.buf)
            {
                txn = QueueP_get(object->reqQueueHandleRx);

                MCASP_udmaHpdInit(rxChHandle,
                                (uint8_t *)pHpd,
                                txn->buf,
                                txn->count *sizeof(uint32_t));
                rxCbParam = (MCASP_Transaction **)object->dmaChCfg->rxCbParams + nextCandidate;
                *rxCbParam = txn;
                object->lastRecQueued = nextCandidate;
                txnPushed++;
            }
        }

        Udma_ringSetDoorBell(Udma_chGetFqRingHandle(rxChHandle), txnPushed);
    }
}

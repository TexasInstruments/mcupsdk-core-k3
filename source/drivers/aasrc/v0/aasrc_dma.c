/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "aasrc.h"
#include <drivers/udma.h>

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Local Function Declarations                       */
/* ========================================================================== */

static int32_t AASRC_configUdmaTx(AASRC_ChObj *chObj);
static int32_t AASRC_configUdmaRx(AASRC_ChObj *chObj);
static int32_t AASRC_configPdmaTx(AASRC_ChObj *chObj);
static int32_t AASRC_configPdmaRx(AASRC_ChObj *chObj);
static int32_t AASRC_primeTxTrpd(AASRC_ChObj *chObj);
static int32_t AASRC_primeRxTrpd(AASRC_ChObj *chObj);
static int32_t AASRC_prepareDmaIcnts(AASRC_ChObj *chObj,
                            uint64_t byteCnt, uint8_t isTx);
static void AASRC_udmaIsrRx(Udma_EventHandle eventHandle, uint32_t eventType,
                            void *args);
static void AASRC_udmaIsrTx(Udma_EventHandle eventHandle, uint32_t eventType,
                            void *args);
extern uint64_t Udma_virtToPhyFxn(const void *virtAddr,
                                  Udma_DrvHandle drvHandle,
                                  Udma_ChHandle chHandle);
extern void *Udma_phyToVirtFxn(uint64_t phyAddr,
                                  Udma_DrvHandle drvHandle,
                                  Udma_ChHandle chHandle);


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                       API Function Definitions                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Local Function Definitions                          */
/* ========================================================================== */

int32_t AASRC_dmaChOpen(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;

    /* Configure AASRC Rx (Memory -> ASRC Input)
     * Source - Memory (UDMA-P)
     * Dest   - AASRC (PDMA)
     * UDMA Channel Direction - Tx
     */

    status = AASRC_configUdmaTx(chObj);

    /* Configure AASRC Tx (AASRC Output -> Memory)
     * Source - AASRC (PDMA)
     * Dest   - Memory (UDMA-P)
     * UDMA Channel Direction - Rx
     */

     if (AASRC_SOK == status)
     {
         status = AASRC_configUdmaRx(chObj);
     }

    return status;
}

int32_t AASRC_dmaChClose(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = NULL;
    AASRC_DmaChCfg *dmaChCfg = NULL;
    Udma_ChHandle txChHandle = NULL;
    Udma_ChHandle rxChHandle = NULL;
    Udma_RingHandle fqTxRingHandle = NULL;
    Udma_RingHandle fqRxRingHandle = NULL;
    int32_t  tempRetVal;
    uint64_t pDesc;
    uint8_t chanEnStatus;

    if(NULL != chHandle)
    {
        chObj = (AASRC_ChObj *)chHandle;
        dmaChCfg = chObj->dmaChCfg;

        if(NULL != dmaChCfg)
        {
            txChHandle = dmaChCfg->txChHandle;
            rxChHandle = dmaChCfg->rxChHandle;

            fqTxRingHandle = Udma_chGetFqRingHandle(txChHandle);
            fqRxRingHandle = Udma_chGetFqRingHandle(rxChHandle);
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }
    else
    {
        status = AASRC_EFAIL;
    }

    DebugP_assert(AASRC_SOK == status);


    if(AASRC_SOK == status)
    {
         status = Udma_chDisable(txChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT * 10U);
    }

    if(AASRC_SOK != status)
    {
        do
        {
            tempRetVal = Udma_ringFlushRaw(fqTxRingHandle, &pDesc);
        }while (UDMA_ETIMEOUT != tempRetVal);

        /* Reset the tx channel if channel teardown fails */
        status = Udma_chReset(txChHandle);
    }
    DebugP_assert(AASRC_SOK == status);

    if(status == AASRC_SOK)
    {
        status = Udma_chGetChanEnStatus(rxChHandle, &chanEnStatus);
        DebugP_assert(AASRC_SOK == status);

        if( (status == AASRC_SOK) && (chanEnStatus == 1U) )
        {
            /* Disable Channel */
            status = Udma_chDisable(rxChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT * 10U);
            DebugP_assert(AASRC_SOK == status);
        }
    }

    if(AASRC_SOK == status)
    {
        do
        {
            tempRetVal = Udma_ringFlushRaw(fqRxRingHandle, &pDesc);
        }while (UDMA_ETIMEOUT != tempRetVal);
    }

    if(AASRC_SOK == status)
    {
        if(NULL != dmaChCfg)
        {
            status = Udma_eventUnRegister(dmaChCfg->cqTxEvtHandle);
            DebugP_assert(AASRC_SOK == status);

            if(AASRC_SOK == status)
            {
                status = Udma_eventUnRegister(dmaChCfg->cqRxEvtHandle);
                DebugP_assert(AASRC_SOK == status);
            }
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }

    if(AASRC_SOK == status)
    {
        /* Flush any pending request from the free queue */
        do
        {
            tempRetVal = Udma_ringFlushRaw(fqTxRingHandle, &pDesc);
        }while (UDMA_ETIMEOUT != tempRetVal);

        /* Flush any pending request from the free queue */
        do
        {
            tempRetVal = Udma_ringFlushRaw(fqRxRingHandle, &pDesc);
        }while (UDMA_ETIMEOUT != tempRetVal);

        /* Close TX channel */
        status = Udma_chClose(dmaChCfg->txChHandle);
        DebugP_assert(AASRC_SOK == status);

        /* Close Rx channel */
        status += Udma_chClose(dmaChCfg->rxChHandle);
        DebugP_assert(AASRC_SOK == status);
    }

    return status;
}

static int32_t AASRC_configUdmaTx(AASRC_ChObj *chObj)
{
    int32_t status = AASRC_SOK;
    AASRC_Config *drvCfg = (AASRC_Config *)chObj->drvHandle;
    AASRC_Object *drvObj = drvCfg->object;
    AASRC_DmaChCfg *dmaChCfg = chObj->dmaChCfg;
    Udma_DrvHandle udmaDrvHandle = (Udma_DrvHandle)drvObj->dmaDrvObj;

    /* Configure TX side (AASRC Input)
     * (Source) BCDMA TX -> (Destination) AASRC PDMA Rx channel pair */
    uint32_t chType;
    Udma_ChHandle txChHandle;
    Udma_EventHandle eventHandle;
    Udma_ChPrms chPrms;
    Udma_ChTxPrms txPrms;
    Udma_EventPrms eventPrms;

    /* Init Tx channel parameters */
    chType = UDMA_CH_TYPE_PDMA_TX;
    UdmaChPrms_init(&chPrms, chType);
    chPrms.peerChNum                = dmaChCfg->txEvtNum;
    chPrms.fqRingPrms.ringMem       = dmaChCfg->txRingMem;
    chPrms.fqRingPrms.ringMemSize   = AASRC_UDMA_RING_MEM_SIZE_TX;
    chPrms.fqRingPrms.elemCnt       = AASRC_TX_DMA_RING_ELEM_CNT;
    txChHandle                      = dmaChCfg->txChHandle;

    status = Udma_chOpen(udmaDrvHandle, txChHandle, chType, &chPrms);
    DebugP_assert(AASRC_SOK == status);

    /* Config TX channel */
    UdmaChTxPrms_init(&txPrms, chType);

    txPrms.fifoDepth = AASRC_DMA_TX_CH_FIFO_DEPTH;

    status = Udma_chConfigTx(txChHandle, &txPrms);
    DebugP_assert(AASRC_SOK == status);

    /* Register ring completion callback */
    eventHandle = dmaChCfg->cqTxEvtHandle;
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType             = UDMA_EVENT_TYPE_TR;
    eventPrms.eventMode             = UDMA_EVENT_MODE_SHARED;
    eventPrms.chHandle              = txChHandle;
    eventPrms.masterEventHandle     = Udma_eventGetGlobalHandle(udmaDrvHandle);
    eventPrms.eventCb               = &AASRC_udmaIsrTx;
    eventPrms.appData               = (AASRC_ChHandle)chObj;
    status = Udma_eventRegister(udmaDrvHandle, eventHandle, &eventPrms);
    DebugP_assert(AASRC_SOK == status);

    /* Set lastPlayed index as AASRC_TX_DMA_RING_ELEM_CNT-1. (So on playing first TR will be updated to 0) */
    chObj->lastPlayed = AASRC_TX_DMA_TR_COUNT-1U;
    chObj->lastFilled = AASRC_TX_DMA_TR_COUNT-1U;

    return status;
}

static int32_t AASRC_configUdmaRx(AASRC_ChObj *chObj)
{
    int32_t status = AASRC_SOK;
    AASRC_Config *drvCfg = (AASRC_Config *)chObj->drvHandle;
    AASRC_Object *drvObj = drvCfg->object;
    AASRC_DmaChCfg *dmaChCfg = chObj->dmaChCfg;
    Udma_DrvHandle udmaDrvHandle = (Udma_DrvHandle)drvObj->dmaDrvObj;

    /* Configure Rx side (AASRC Output)
     * (Source) AASRC PDMA Tx channel pair -> (Destination) BCDMA Rx */
    uint32_t chType;
    Udma_ChHandle rxChHandle;
    Udma_EventHandle eventHandle;
    Udma_ChPrms chPrms;
    Udma_ChRxPrms rxPrms;
    Udma_EventPrms eventPrms;

    /* Init RX channel parameters */
    chType = UDMA_CH_TYPE_PDMA_RX;
    UdmaChPrms_init(&chPrms, chType);
    chPrms.peerChNum                = dmaChCfg->rxEvtNum;
    chPrms.fqRingPrms.ringMem       = dmaChCfg->rxRingMem;
    chPrms.fqRingPrms.ringMemSize   = AASRC_UDMA_RING_MEM_SIZE_RX;
    chPrms.fqRingPrms.elemCnt       = AASRC_RX_DMA_RING_ELEM_CNT;
    rxChHandle                      = dmaChCfg->rxChHandle;

    status = Udma_chOpen(udmaDrvHandle, rxChHandle, chType, &chPrms);
    DebugP_assert(AASRC_SOK == status);

    /* Config RX channel */
    UdmaChRxPrms_init(&rxPrms, chType);
    rxPrms.configDefaultFlow = FALSE;

    status = Udma_chConfigRx(rxChHandle, &rxPrms);
    DebugP_assert(AASRC_SOK == status);

    /* Register ring completion callback */
    eventHandle = dmaChCfg->cqRxEvtHandle;
    UdmaEventPrms_init(&eventPrms);
    eventPrms.eventType             = UDMA_EVENT_TYPE_TR;
    eventPrms.eventMode             = UDMA_EVENT_MODE_SHARED;
    eventPrms.chHandle              = rxChHandle;
    eventPrms.masterEventHandle     = Udma_eventGetGlobalHandle(udmaDrvHandle);
    eventPrms.eventCb               = &AASRC_udmaIsrRx;
    eventPrms.appData               = (AASRC_ChHandle)chObj;
    status = Udma_eventRegister(udmaDrvHandle, eventHandle, &eventPrms);
    DebugP_assert(AASRC_SOK == status);

    /* Set last record queued index */
    chObj->lastRecQueued = AASRC_RX_DMA_TR_COUNT-1U;
    chObj->lastReceived = AASRC_RX_DMA_TR_COUNT-1U;

    return status;
}

static int32_t AASRC_configPdmaRx(AASRC_ChObj *chObj)
{
    int32_t status = AASRC_SOK;
    AASRC_DmaChCfg *dmaChCfg = chObj->dmaChCfg;
    Udma_ChHandle txChHandle = dmaChCfg->txChHandle;
    Udma_ChPdmaPrms pdmaPrms;
    uint32_t chCount;
    uint32_t txnByteCnt;

    /* Config PDMA channel */

    /* AASRC Static TR Config */
    UdmaChPdmaPrms_init(&pdmaPrms);
    pdmaPrms.elemSize               = UDMA_PDMA_ES_32BITS; /* X */
    pdmaPrms.elemCnt                = chObj->chCfg.fifoControl.inFifoThreshold; /* Y */
    pdmaPrms.burst                  = 0U;
    pdmaPrms.acc32                  = 1U;
    pdmaPrms.eol                    = 0U;
    pdmaPrms.isAasrcCh              = 1U;

    /* Calculate fifoCnt based on transaction byte count */
    txnByteCnt = chObj->rxDmaIcnt.txnByteCnt;
    pdmaPrms.fifoCnt = txnByteCnt / (WORD_BYTE_COUNT * pdmaPrms.elemCnt); /* Z */

    /* AASRC Tx Fifo Config */
    if (chObj->chCfg.chType == AASRC_GROUP)
    {
        pdmaPrms.groupMode          = 0x01U;
    }
    else
    {
        pdmaPrms.groupMode          = 0x00U;
    }
    pdmaPrms.dmaReqReset            = 0x01U;
    chCount = chObj->chState->monoChCount;
    pdmaPrms.firstSlot              = (uint8_t)chObj->chState->chMap[0U];
    pdmaPrms.lastSlot               = (uint8_t)chObj->chState->chMap[chCount-1U];

    if (chObj->chCfg.chType == AASRC_GROUP)
    {
        pdmaPrms.dmaReqMask         = ((uint16_t)1 << (uint8_t)chObj->chState->hwGroupNum);
    }
    else
    {
        pdmaPrms.dmaReqMask         = (uint16_t)(chObj->chState->chMask);
    }

    /* AASRC Ordertable Config */
    pdmaPrms.orderTable0            = 0x76543210U;
    pdmaPrms.orderTable1            = 0xFEDCBA98U;

    status = Udma_chConfigPdma(txChHandle, &pdmaPrms);
    DebugP_assert(AASRC_SOK == status);

    return status;
}

static int32_t AASRC_configPdmaTx(AASRC_ChObj *chObj)
{
    int32_t status = AASRC_SOK;
    AASRC_DmaChCfg *dmaChCfg = chObj->dmaChCfg;
    Udma_ChHandle rxChHandle = dmaChCfg->rxChHandle;
    Udma_ChPdmaPrms pdmaPrms;
    uint32_t chCount;
    uint32_t txnByteCnt;

    /* Config PDMA channel */

    /* AASRC Static TR Config */
    UdmaChPdmaPrms_init(&pdmaPrms);
    pdmaPrms.elemSize               = UDMA_PDMA_ES_32BITS; /* X */
    pdmaPrms.elemCnt                = chObj->chCfg.fifoControl.outFifoThreshold; /* Y */
    pdmaPrms.burst                  = 0U;
    pdmaPrms.acc32                  = 1U;
    pdmaPrms.eol                    = 0U;
    pdmaPrms.isAasrcCh              = 1U;

    /* Calculate fifoCnt based on transaction byte count */
    txnByteCnt = chObj->txDmaIcnt.txnByteCnt;
    pdmaPrms.fifoCnt = txnByteCnt / (WORD_BYTE_COUNT * pdmaPrms.elemCnt); /* Z */

    /* AASRC Rx Fifo Config */
    if (chObj->chCfg.chType == AASRC_GROUP)
    {
        pdmaPrms.groupMode          = 0x01U;
    }
    else
    {
        pdmaPrms.groupMode          = 0x00U;
    }
    pdmaPrms.dmaReqReset            = 0x01U;
    chCount = chObj->chState->monoChCount;
    pdmaPrms.firstSlot              = (uint8_t)chObj->chState->chMap[0U];
    pdmaPrms.lastSlot               = (uint8_t)chObj->chState->chMap[chCount-1U];

    if (chObj->chCfg.chType == AASRC_GROUP)
    {
        pdmaPrms.dmaReqMask         = ((uint16_t)1 << (uint8_t)chObj->chState->hwGroupNum);
    }
    else
    {
        pdmaPrms.dmaReqMask         = (uint16_t)(chObj->chState->chMask);
    }

    /* AASRC Ordertable Config */
    pdmaPrms.orderTable0            = 0x76543210U;
    pdmaPrms.orderTable1            = 0xFEDCBA98U;

    status = Udma_chConfigPdma(rxChHandle, &pdmaPrms);
    DebugP_assert(AASRC_SOK == status);

    return status;
}

static int32_t AASRC_prepareDmaIcnts(AASRC_ChObj *chObj, uint64_t byteCnt, uint8_t isTx)
{
    int32_t status = AASRC_SOK;
    AASRC_ChCfg *chCfg;
    uint64_t txnByteCnt = 0U;
    uint32_t tempIcntX = 0U;
    uint32_t tempIcntY = 0U;
    uint16_t waterLevel = 0U;

    if ((NULL == chObj))
    {
        status = AASRC_EFAIL;
    }
    if(status  == AASRC_SOK)
    {
        chCfg = &chObj->chCfg;
    }

    if(status == AASRC_SOK)
    {
        do
        {
            if(isTx == 1U)
            {
                txnByteCnt = byteCnt;

                if(chObj->txDmaIcnt.initDone == 1U)
                {
                    if(chObj->txDmaIcnt.txnByteCnt != txnByteCnt)
                    {
                        status = AASRC_EFAIL;
                        break;
                    }

                    if((chObj->rcvObj.txnLoopjob.sampleCount*WORD_BYTE_COUNT) != byteCnt)
                    {
                        DebugP_logError("Keep the transaction count same as loopjob count \r\n");
                        status = AASRC_EFAIL;
                        break;
                    }

                    if((chCfg->fifoControl.inFifoThreshold != 0U) && ((byteCnt % (WORD_BYTE_COUNT * chCfg->fifoControl.inFifoThreshold))!= 0U))
                    {
                        DebugP_logError("Keep the transaction count multiple of fifo water level \r\n");
                        status = AASRC_EFAIL;
                        break;
                    }
                }
                else
                {
                    if(chCfg->fifoControl.inFifoThreshold != 0U)
                    {
                        waterLevel = (uint16_t)chCfg->fifoControl.inFifoThreshold;
                    }
                    else
                    {
                        waterLevel = 1U;
                    }

                    if((chObj->rcvObj.txnLoopjob.sampleCount*WORD_BYTE_COUNT) != byteCnt)
                    {
                        DebugP_logError("Keep the transaction count same as loopjob count \r\n");
                        status = AASRC_EFAIL;
                        break;
                    }

                    if((byteCnt % (WORD_BYTE_COUNT * waterLevel)) != 0U)
                    {
                        DebugP_logError("Keep the transaction count multiple of fifo water level \r\n");
                        status = AASRC_EFAIL;
                        break;
                    }

                    chObj->txDmaIcnt.icnt0 = WORD_BYTE_COUNT;
                    chObj->txDmaIcnt.icnt1 = (waterLevel);
                    tempIcntX = ((uint32_t)txnByteCnt / (WORD_BYTE_COUNT*(waterLevel)));
                    if(tempIcntX < AASRC_ICNT2_MAX)
                    {
                        chObj->txDmaIcnt.icnt2 = (uint16_t)tempIcntX;
                        chObj->txDmaIcnt.icnt3 = 1U;
                    }
                    else
                    {
                        tempIcntX = (uint32_t)(tempIcntX & ((uint32_t)(-((int32_t)tempIcntX))));
                        tempIcntY = ((uint32_t)txnByteCnt) / (WORD_BYTE_COUNT*(waterLevel) * tempIcntX);
                        if((tempIcntY > AASRC_ICNT2_MAX) || (tempIcntX > AASRC_ICNT2_MAX))
                        {
                            DebugP_logError("Transaction count out of bounds \r\n");
                            status = AASRC_EFAIL;
                            break;
                        }
                        else
                        {
                            chObj->txDmaIcnt.icnt2 = (uint16_t)tempIcntX;
                            chObj->txDmaIcnt.icnt3 = (uint16_t)tempIcntY;
                        }
                    }

                    chObj->txDmaIcnt.txnByteCnt = (uint32_t)txnByteCnt;
                    chObj->txDmaIcnt.initDone = 1U;
                }
            }
            else
            {
                txnByteCnt = byteCnt;

                if(chObj->rxDmaIcnt.initDone == 1U)
                {
                    if(chObj->rxDmaIcnt.txnByteCnt != txnByteCnt)
                    {
                        status = AASRC_EFAIL;
                        break;
                    }

                    if((chObj->xmtObj.txnLoopjob.sampleCount*WORD_BYTE_COUNT) != txnByteCnt)
                    {
                        DebugP_logError("Keep the transaction count same as loopjob count \r\n");
                        status = AASRC_EFAIL;
                        break;
                    }

                    if((chCfg->fifoControl.outFifoThreshold != 0U) && ((byteCnt % (WORD_BYTE_COUNT * chCfg->fifoControl.outFifoThreshold)) != 0U))
                    {
                        DebugP_logError("Keep the transaction count multiple of fifo water level \r\n");
                        status = AASRC_EFAIL;
                        break;
                    }
                }
                else
                {
                    if(chCfg->fifoControl.outFifoThreshold != 0U)
                    {
                        waterLevel = (uint16_t)chCfg->fifoControl.outFifoThreshold;
                    }
                    else
                    {
                        waterLevel = 1U;
                    }

                    if((chObj->xmtObj.txnLoopjob.sampleCount * WORD_BYTE_COUNT) != txnByteCnt)
                    {
                        DebugP_logError("Keep the transaction count same as loopjob count \r\n");
                        status = AASRC_EFAIL;
                        break;
                    }
                    
                    if((byteCnt % (WORD_BYTE_COUNT * waterLevel)) != 0U)
                    {
                        DebugP_logError("Keep the transaction count multiple of fifo water level \r\n");
                        status = AASRC_EFAIL;
                        break;
                    }

                    chObj->rxDmaIcnt.icnt0 = WORD_BYTE_COUNT;
                    chObj->rxDmaIcnt.icnt1 = waterLevel;
                    tempIcntX = ((uint32_t)(txnByteCnt)) / (WORD_BYTE_COUNT * waterLevel);
                    if(tempIcntX < AASRC_ICNT2_MAX)
                    {
                        chObj->rxDmaIcnt.icnt2 = (uint16_t)tempIcntX;
                        chObj->rxDmaIcnt.icnt3 = 1U;
                    }
                    else
                    {
                        tempIcntX = (uint32_t)(tempIcntX & ((uint32_t)(-((int32_t)tempIcntX))));
                        tempIcntY = ((uint32_t)(txnByteCnt)) / (WORD_BYTE_COUNT*waterLevel*tempIcntX);
                        if((tempIcntY > AASRC_ICNT2_MAX) || (tempIcntX > AASRC_ICNT2_MAX))
                        {
                            DebugP_logError("Transaction count out of bounds \r\n");
                            status = AASRC_EFAIL;
                            break;
                        }
                        else
                        {
                            chObj->rxDmaIcnt.icnt2 = (uint16_t)tempIcntX;
                            chObj->rxDmaIcnt.icnt3 = (uint16_t)tempIcntY;
                        }
                    }

                    chObj->rxDmaIcnt.txnByteCnt = (uint32_t)txnByteCnt;
                    chObj->rxDmaIcnt.initDone = 1U;
                }
            }
        } while(false);
    }

    return status;
}

static int32_t AASRC_primeTxTrpd(AASRC_ChObj *chObj)
{
    int32_t status = AASRC_SOK;
    AASRC_Config *drvCfg;
    AASRC_Object *drvObj;
    AASRC_DmaChCfg *dmaChCfg = NULL;

    Udma_DrvHandle udmaDrvHandle;
    Udma_ChHandle txChHandle;

    uint32_t cqRingNum = 0U;
    uint64_t *ringPtr;
    CSL_UdmapTR3 *pTr = NULL;
    uint32_t i;
    AASRC_Transaction **txCbParam;

    if(NULL != chObj)
    {
        drvCfg = (AASRC_Config *)chObj->drvHandle;
        drvObj =  drvCfg->object;
        dmaChCfg = chObj->dmaChCfg;

        udmaDrvHandle = (Udma_DrvHandle)(drvObj->dmaDrvObj);
        txChHandle = dmaChCfg->txChHandle;
        cqRingNum = Udma_chGetCqRingNum(txChHandle);
    }
    else
    {
        status = AASRC_EBADARGS;
    }

    if(AASRC_SOK == status)
    {
        memset(dmaChCfg->txTrpdMem, 0, AASRC_UDMA_TRPD_MEM_SIZE_TX * AASRC_TX_DMA_RING_ELEM_CNT);
        CacheP_wb(dmaChCfg->txTrpdMem, AASRC_UDMA_TRPD_MEM_SIZE_TX * AASRC_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

        UdmaUtils_makeTrpd((uint8_t *)dmaChCfg->txTrpdMem, UDMA_TR_TYPE_3, AASRC_TX_DMA_TR_COUNT, cqRingNum);

        /* Perpetual reload */
        UdmaUtils_setTrpdReload((uint8_t *)dmaChCfg->txTrpdMem, AASRC_DMA_PERPETUAL_RELOAD_CNT, 0U);

        /* Prime TRs in TRPD with loopjobs */
        for(i = 0; i < AASRC_TX_DMA_TR_COUNT; i++)
        {
            pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)dmaChCfg->txTrpdMem, i);

            pTr->flags = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_DATA_MOVE);
            pTr->flags |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);

            pTr->addr = (uint64_t)Udma_virtToPhyFxn(chObj->rcvObj.txnLoopjob.buf, udmaDrvHandle, txChHandle);

            status = AASRC_prepareDmaIcnts(chObj, ((uint64_t)chObj->rcvObj.txnLoopjob.sampleCount * WORD_BYTE_COUNT),
                                                            1U);
            DebugP_assert(status == AASRC_SOK);

            pTr->icnt0 = chObj->txDmaIcnt.icnt0;
            pTr->icnt1 = chObj->txDmaIcnt.icnt1;
            pTr->icnt2 = chObj->txDmaIcnt.icnt2;
            pTr->icnt3 = chObj->txDmaIcnt.icnt3;

            pTr->dim1     = pTr->icnt0;
            pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
            pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
        }
    }

    if(AASRC_SOK == status)
    {
        /* Writeback the TRPD memory */
        CacheP_wb(dmaChCfg->txTrpdMem, AASRC_UDMA_TRPD_MEM_SIZE_TX * AASRC_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

        /* Prime ring memory with pointers to TRPD */
        ringPtr = (uint64_t *)dmaChCfg->txRingMem;
        *ringPtr = (uint64_t)Udma_virtToPhyFxn((uint8_t *)dmaChCfg->txTrpdMem, udmaDrvHandle, txChHandle);

        /* Writeback ring memory */
        CacheP_wb(dmaChCfg->txRingMem, AASRC_UDMA_RING_ENTRY_SIZE * AASRC_TX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

        /* Check if there are txn already submitted */
        if(QueueP_isEmpty(chObj->reqQueueHandleRx) == QueueP_NOTEMPTY)
        {
            AASRC_Transaction *txn = NULL;
            uint64_t txCnt = 0;

            for(i = 0; i < AASRC_TX_DMA_TR_COUNT; i++)
            {
                txn = QueueP_get(chObj->reqQueueHandleRx);

                if(txn != chObj->reqQueueHandleRx)
                {
                    /* Update last filled index */
                    chObj->lastFilled = (chObj->lastFilled + 1U) % (AASRC_TX_DMA_TR_COUNT);

                    pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)dmaChCfg->txTrpdMem, chObj->lastFilled);

                    txCnt = (uint32_t)(txn->sampleCount * WORD_BYTE_COUNT);

                    status = AASRC_prepareDmaIcnts(chObj, (txCnt),
                                                            1U);

                    DebugP_assert(status == AASRC_SOK);

                    pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, udmaDrvHandle, txChHandle);

                    pTr->icnt0 = chObj->txDmaIcnt.icnt0;
                    pTr->icnt1 = chObj->txDmaIcnt.icnt1;
                    pTr->icnt2 = chObj->txDmaIcnt.icnt2;
                    pTr->icnt3 = chObj->txDmaIcnt.icnt3;

                    pTr->dim1     = pTr->icnt0;
                    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

                    CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);

                    txCbParam = dmaChCfg->txCbParams;
                    txCbParam = txCbParam + (chObj->lastFilled);
                    *txCbParam = txn;
                }
                else
                {
                    break;
                }
            }
        }
    }

    if(AASRC_SOK == status)
    {
        /* Set doorbell to push the TRPD  */
        Udma_ringSetDoorBell(Udma_chGetFqRingHandle(txChHandle), AASRC_TX_DMA_RING_ELEM_CNT);
    }

    return status;
}

static int32_t AASRC_primeRxTrpd(AASRC_ChObj *chObj)
{
    int32_t status = AASRC_SOK;
    AASRC_Config *drvCfg;
    AASRC_Object *drvObj;
    AASRC_DmaChCfg *dmaChCfg = NULL;

    Udma_DrvHandle udmaDrvHandle;
    Udma_ChHandle rxChHandle;

    uint32_t cqRingNum = 0U;
    uint64_t *ringPtr;
    CSL_UdmapTR3 *pTr = NULL;
    uint32_t i;
    AASRC_Transaction **rxCbParam;

    if(NULL != chObj)
    {
        drvCfg = (AASRC_Config *)chObj->drvHandle;
        drvObj =  drvCfg->object;
        dmaChCfg = chObj->dmaChCfg;

        udmaDrvHandle = (Udma_DrvHandle)(drvObj->dmaDrvObj);
        rxChHandle = dmaChCfg->rxChHandle;
        cqRingNum = Udma_chGetCqRingNum(rxChHandle);
    }
    else
    {
        status = AASRC_EBADARGS;
    }

    if(AASRC_SOK == status)
    {
        memset(dmaChCfg->rxTrpdMem, 0, AASRC_UDMA_TRPD_MEM_SIZE_RX * AASRC_RX_DMA_RING_ELEM_CNT);
        CacheP_wb(dmaChCfg->rxTrpdMem, AASRC_UDMA_TRPD_MEM_SIZE_RX * AASRC_RX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

        UdmaUtils_makeTrpd((uint8_t *)dmaChCfg->rxTrpdMem, UDMA_TR_TYPE_3, AASRC_RX_DMA_TR_COUNT, cqRingNum);

        /* Perpetual reload */
        UdmaUtils_setTrpdReload((uint8_t *)dmaChCfg->rxTrpdMem, AASRC_DMA_PERPETUAL_RELOAD_CNT, 0U);

        /* Prime TRs in TRPD with loopjobs */
        for(i = 0; i < AASRC_RX_DMA_TR_COUNT; i++)
        {
            pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)dmaChCfg->rxTrpdMem, i);

            pTr->flags = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_DATA_MOVE);
            pTr->flags |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);

            pTr->addr = (uint64_t)Udma_virtToPhyFxn(chObj->xmtObj.txnLoopjob.buf, udmaDrvHandle, rxChHandle);

            status = AASRC_prepareDmaIcnts(chObj, ((uint64_t)chObj->xmtObj.txnLoopjob.sampleCount * WORD_BYTE_COUNT),
                                                            0U);
            DebugP_assert(status == AASRC_SOK);

            pTr->icnt0 = chObj->rxDmaIcnt.icnt0;
            pTr->icnt1 = chObj->rxDmaIcnt.icnt1;
            pTr->icnt2 = chObj->rxDmaIcnt.icnt2;
            pTr->icnt3 = chObj->rxDmaIcnt.icnt3;

            pTr->dim1     = pTr->icnt0;
            pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
            pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
        }
    }

    if(AASRC_SOK == status)
    {
        /* Writeback the TRPD memory */
        CacheP_wb(dmaChCfg->rxTrpdMem, AASRC_UDMA_TRPD_MEM_SIZE_RX * AASRC_RX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

        /* Prime ring memory with pointers to TRPD */
        ringPtr = (uint64_t *)dmaChCfg->rxRingMem;
        *ringPtr = (uint64_t)Udma_virtToPhyFxn((uint8_t *)dmaChCfg->rxTrpdMem, udmaDrvHandle, rxChHandle);

        /* Writeback ring memory */
        CacheP_wb(dmaChCfg->rxRingMem, AASRC_UDMA_RING_ENTRY_SIZE * AASRC_RX_DMA_RING_ELEM_CNT, CacheP_TYPE_ALLD);

        /* Check if there are txn already submitted */
        if(QueueP_isEmpty(chObj->reqQueueHandleTx) == QueueP_NOTEMPTY)
        {
            AASRC_Transaction *txn = NULL;
            uint64_t txCnt = 0;

            for(i = 0; i < AASRC_RX_DMA_TR_COUNT; i++)
            {
                txn = QueueP_get(chObj->reqQueueHandleTx);

                if(txn != chObj->reqQueueHandleTx)
                {
                            /* Update last receive queued index */
                    chObj->lastRecQueued = (chObj->lastRecQueued + 1U)%(AASRC_RX_DMA_TR_COUNT);

                    pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)dmaChCfg->rxTrpdMem, chObj->lastRecQueued);

                    txCnt = (uint32_t)(txn->sampleCount * WORD_BYTE_COUNT);

                    status = AASRC_prepareDmaIcnts(chObj, (txCnt),
                                                            0U);

                    DebugP_assert(status == AASRC_SOK);

                    pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, udmaDrvHandle, rxChHandle);

                    pTr->icnt0 = chObj->rxDmaIcnt.icnt0;
                    pTr->icnt1 = chObj->rxDmaIcnt.icnt1;
                    pTr->icnt2 = chObj->rxDmaIcnt.icnt2;
                    pTr->icnt3 = chObj->rxDmaIcnt.icnt3;

                    pTr->dim1     = pTr->icnt0;
                    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);

                    CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);
                    rxCbParam = dmaChCfg->rxCbParams;
                    rxCbParam = rxCbParam + (chObj->lastRecQueued);
                    *rxCbParam = txn;
                }
                else
                {
                    break;
                }
            }
        }
    }

    if(AASRC_SOK == status)
    {
        /* Set doorbell to push the TRPD  */
        Udma_ringSetDoorBell(Udma_chGetFqRingHandle(rxChHandle), AASRC_RX_DMA_RING_ELEM_CNT);
    }

    return status;
}

int32_t AASRC_dmaChEnable(AASRC_ChHandle chHandle)
{
    int32_t status = UDMA_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    AASRC_DmaChCfg *dmaChCfg = chObj->dmaChCfg;
    Udma_ChHandle txChHandle = dmaChCfg->txChHandle;
    Udma_ChHandle rxChHandle = dmaChCfg->rxChHandle;

    if (UDMA_SOK == status)
    {
        status = AASRC_primeRxTrpd(chObj);

        if (UDMA_SOK == status)
        {
            status = AASRC_primeTxTrpd(chObj);
            DebugP_assert(status == UDMA_SOK);
        }
    }

    if (UDMA_SOK == status)
    {
        status = AASRC_configPdmaTx(chObj);

        if (UDMA_SOK == status)
        {
            status = AASRC_configPdmaRx(chObj);
            DebugP_assert(status == UDMA_SOK);
        }
    }

    if (UDMA_SOK == status)
    {
        /* Enable Input */
        status = Udma_chEnable(txChHandle);
        
        if (UDMA_SOK == status)
        {
            /* Enable Output */
            status = Udma_chEnable(rxChHandle);
            DebugP_assert(status == UDMA_SOK);
        }
    }

    return status;
}

static void AASRC_udmaIsrRx(Udma_EventHandle eventHandle,
                                 uint32_t eventType,
                                 void *args)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *aasrcChObj = NULL;
    AASRC_Object *aasrcDrvObj = NULL;
    Udma_ChHandle rxChHandle = NULL;
    Udma_ChHandle udmaDrvHandle = NULL;
    AASRC_Transaction **rxCbParam = NULL;
    AASRC_DmaChCfg *dmaChCfg = NULL;
    Udma_ChStats chStats;
    uint32_t pCnt = 0;
    void *trpdMem = NULL;
    uint32_t tempLastReceived = 0;
    uint32_t totalPktCnt = 0;
    bool ctrlVar = true;

    if(args != NULL)
    {
        aasrcChObj = (AASRC_ChObj *)args;
    }
    else
    {
        status = AASRC_EFAIL;
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
    if(status == AASRC_SOK)
    {
        dmaChCfg   = aasrcChObj->dmaChCfg;
        rxChHandle = dmaChCfg->rxChHandle;
        aasrcDrvObj = ((AASRC_Config *)aasrcChObj->drvHandle)->object;
        udmaDrvHandle  =  (Udma_DrvHandle)aasrcDrvObj->dmaDrvObj;

        tempLastReceived = aasrcChObj->lastReceived;

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

                trpdMem = dmaChCfg->rxTrpdMem;

                /* Update last received index */
                aasrcChObj->lastReceived = (aasrcChObj->lastReceived + 1U)%AASRC_RX_DMA_TR_COUNT;

                /* Update current Processed TR with loopjob */
                {
                    CSL_UdmapTR3 *pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)trpdMem, aasrcChObj->lastReceived);
                    pTr = (CSL_UdmapTR3 *)Udma_phyToVirtFxn((uint64_t)pTr, udmaDrvHandle, rxChHandle);
                    pTr->addr =(uint64_t)Udma_virtToPhyFxn(aasrcChObj->xmtObj.txnLoopjob.buf, udmaDrvHandle, rxChHandle);

                    pTr->icnt0 = aasrcChObj->rxDmaIcnt.icnt0;
                    pTr->icnt1 = aasrcChObj->rxDmaIcnt.icnt1;
                    pTr->icnt2 = aasrcChObj->rxDmaIcnt.icnt2;
                    pTr->icnt3 = aasrcChObj->rxDmaIcnt.icnt3;

                    pTr->dim1     = pTr->icnt0;
                    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
                }

                rxCbParam = aasrcChObj->dmaChCfg->rxCbParams;
                rxCbParam = rxCbParam + (aasrcChObj->lastReceived);

                /* Call the user registered callback function */
                if(NULL != *(rxCbParam))
                {
                    AASRC_TransferObj *xfrObj = &(aasrcChObj->xmtObj);
                    if(xfrObj->cbFxn != NULL)
                    {
                        xfrObj->cbFxn((AASRC_Handle *)args, *(rxCbParam));
                    }
                }

                /* Update the callback param to NULL */
                *(rxCbParam) = NULL;
            }

            status += Udma_chGetStats(rxChHandle, &chStats);
        } while(chStats.packetCnt != 0U);

        CacheP_wb((uint8_t *) UdmaUtils_getTrpdTr3Pointer((uint8_t *)aasrcChObj->dmaChCfg->rxTrpdMem, 0),
                                        AASRC_RX_DMA_TR_COUNT*sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);
    }

    if(status == AASRC_SOK)
    {
        uint32_t diff = 0;
        uint32_t nextCandidate = 0;

        if(tempLastReceived < aasrcChObj->lastRecQueued)
        {
            diff = aasrcChObj->lastRecQueued - tempLastReceived;
        }
        else
        {
            diff = (AASRC_RX_DMA_TR_COUNT-1U) - tempLastReceived + aasrcChObj->lastRecQueued + 1U;
        }

        if(diff >= (totalPktCnt+2U))
        {
            nextCandidate = (aasrcChObj->lastRecQueued + 1U)%AASRC_RX_DMA_TR_COUNT;
        }
        else
        {
            nextCandidate = (aasrcChObj->lastReceived+ 2U)%AASRC_RX_DMA_TR_COUNT;
            aasrcChObj->lastRecQueued = AASRC_INVALID_TXN_IDX;
        }

        if(AASRC_INVALID_TXN_IDX == aasrcChObj->lastRecQueued)
        {
            nextCandidate = (aasrcChObj->lastReceived+ 2U)%AASRC_RX_DMA_TR_COUNT;
        }

        while (ctrlVar)
        {
            AASRC_Transaction *txn = NULL;
            CSL_UdmapTR3 *pTr = NULL;

            txn = QueueP_get(aasrcChObj->reqQueueHandleTx);

            if(txn != aasrcChObj->reqQueueHandleTx)
            {
                aasrcChObj->lastRecQueued = nextCandidate;

                rxCbParam = aasrcChObj->dmaChCfg->rxCbParams;
                rxCbParam = rxCbParam + (aasrcChObj->lastRecQueued);
                *(rxCbParam) = txn;

                pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)aasrcChObj->dmaChCfg->rxTrpdMem, aasrcChObj->lastRecQueued);

                pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, udmaDrvHandle, rxChHandle);

                pTr->icnt0 = aasrcChObj->rxDmaIcnt.icnt0;
                pTr->icnt1 = aasrcChObj->rxDmaIcnt.icnt1;
                pTr->icnt2 = aasrcChObj->rxDmaIcnt.icnt2;
                pTr->icnt3 = aasrcChObj->rxDmaIcnt.icnt3;

                CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);

                nextCandidate = (nextCandidate + 1U) % AASRC_TX_DMA_TR_COUNT;
            }
            else
            {
                ctrlVar = false;
            }
        }
    }

    return;
}

static void AASRC_udmaIsrTx(Udma_EventHandle eventHandle,
                                 uint32_t eventType,
                                 void *args)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *aasrcChObj = NULL;
    AASRC_Object *aasrcDrvObj = NULL;
    Udma_ChHandle txChHandle = NULL;
    Udma_DrvHandle udmaDrvHandle = NULL;
    AASRC_Transaction **txCbParam = NULL;
    AASRC_DmaChCfg *dmaChCfg = NULL;
    Udma_ChStats chStats;
    uint32_t pCnt = 0;
    void *trpdMem = NULL;
    uint32_t tempLastPlayed = 0;
    uint32_t totalPktCnt = 0;
    bool ctrlVar = true;

    if(args != NULL)
    {
        aasrcChObj = (AASRC_ChObj *)args;
    }
    else
    {
        status = AASRC_EFAIL;
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
    if(status == AASRC_SOK)
    {
        dmaChCfg = aasrcChObj->dmaChCfg;
        txChHandle = dmaChCfg->txChHandle;
        aasrcDrvObj = ((AASRC_Config *)aasrcChObj->drvHandle)->object;
        udmaDrvHandle  =  (Udma_DrvHandle)aasrcDrvObj->dmaDrvObj;

        tempLastPlayed = aasrcChObj->lastPlayed;

        do
        {
            status = Udma_chGetStats(txChHandle, &chStats);

            pCnt = chStats.packetCnt;
            totalPktCnt += pCnt;

            /* Reset/Decrement the number of processed packets */
            status += Udma_chDecStats(txChHandle, &chStats);

            while (pCnt != 0U)
            {
                pCnt--;

                trpdMem = dmaChCfg->txTrpdMem;

                /* Update last played index */
                aasrcChObj->lastPlayed = (aasrcChObj->lastPlayed + 1U)%AASRC_TX_DMA_TR_COUNT;

                /* Update current Processed TR with loopjob */
                {
                    CSL_UdmapTR3 *pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)trpdMem, aasrcChObj->lastPlayed);
                    pTr = (CSL_UdmapTR3 *)Udma_phyToVirtFxn((uint64_t)pTr, udmaDrvHandle, txChHandle);
                    pTr->addr =(uint64_t)Udma_virtToPhyFxn(aasrcChObj->rcvObj.txnLoopjob.buf, udmaDrvHandle, txChHandle);

                    pTr->icnt0 = aasrcChObj->txDmaIcnt.icnt0;
                    pTr->icnt1 = aasrcChObj->txDmaIcnt.icnt1;
                    pTr->icnt2 = aasrcChObj->txDmaIcnt.icnt2;
                    pTr->icnt3 = aasrcChObj->txDmaIcnt.icnt3;

                    pTr->dim1     = pTr->icnt0;
                    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
                    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
                }

                txCbParam = aasrcChObj->dmaChCfg->txCbParams;
                txCbParam = txCbParam + (aasrcChObj->lastPlayed);

                /* Call the user registered callback function */
                if(NULL != *(txCbParam))
                {
                    AASRC_TransferObj *xfrObj = &(aasrcChObj->rcvObj);
                    if(xfrObj->cbFxn != NULL)
                    {
                        xfrObj->cbFxn((AASRC_Handle *)args, *(txCbParam));
                    }
                }

                /* Update the callback param to NULL */
                *(txCbParam) = NULL;
            }

            status += Udma_chGetStats(txChHandle, &chStats);
        } while(chStats.packetCnt != 0U);

        CacheP_wb((uint8_t *) UdmaUtils_getTrpdTr3Pointer((uint8_t *)aasrcChObj->dmaChCfg->txTrpdMem, 0),
                                        AASRC_TX_DMA_TR_COUNT*sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);
    }

    if(status == AASRC_SOK)
    {
        uint32_t diff = 0;
        uint32_t nextCandidate = 0;

        if(tempLastPlayed < aasrcChObj->lastFilled)
        {
            diff = aasrcChObj->lastFilled - tempLastPlayed;
        }
        else
        {
            diff = (AASRC_TX_DMA_TR_COUNT-1U) - tempLastPlayed + aasrcChObj->lastFilled + 1U;
        }

        if(diff >= (totalPktCnt+2U))
        {
            nextCandidate = (aasrcChObj->lastFilled + 1U)%AASRC_TX_DMA_TR_COUNT;
        }
        else
        {
            nextCandidate = (aasrcChObj->lastPlayed + 2U)%AASRC_TX_DMA_TR_COUNT;
            aasrcChObj->lastFilled = AASRC_INVALID_TXN_IDX;
        }

        if(AASRC_INVALID_TXN_IDX == aasrcChObj->lastFilled)
        {
            nextCandidate = (aasrcChObj->lastPlayed + 2U)%AASRC_TX_DMA_TR_COUNT;
        }

        while (ctrlVar)
        {
            AASRC_Transaction *txn = NULL;
            CSL_UdmapTR3 *pTr = NULL;

            txn = QueueP_get(aasrcChObj->reqQueueHandleRx);

            if(txn != aasrcChObj->reqQueueHandleRx)
            {
                aasrcChObj->lastFilled = nextCandidate;

                txCbParam = aasrcChObj->dmaChCfg->txCbParams;
                txCbParam = txCbParam + (aasrcChObj->lastFilled);
                *(txCbParam) = txn;

                pTr = UdmaUtils_getTrpdTr3Pointer((uint8_t *)aasrcChObj->dmaChCfg->txTrpdMem, aasrcChObj->lastFilled);

                pTr->addr =(uint64_t)Udma_virtToPhyFxn(txn->buf, udmaDrvHandle, txChHandle);

                pTr->icnt0 = aasrcChObj->txDmaIcnt.icnt0;
                pTr->icnt1 = aasrcChObj->txDmaIcnt.icnt1;
                pTr->icnt2 = aasrcChObj->txDmaIcnt.icnt2;
                pTr->icnt3 = aasrcChObj->txDmaIcnt.icnt3;

                CacheP_wb(pTr, sizeof(CSL_UdmapTR3), CacheP_TYPE_ALLD);

                nextCandidate = (nextCandidate+1U)%AASRC_TX_DMA_TR_COUNT;
            }
            else
            {
                ctrlVar = false;
            }
        }
    }

    return;
}

int32_t AASRC_disableDmaTx(AASRC_ChHandle chHandle)
{
    int32_t status = SystemP_SUCCESS;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    Udma_ChHandle txChHandle = NULL;
    uint8_t chanEnStatus;
    int32_t  tempRetVal;
    uint64_t pDesc;

    if(NULL != chObj)
    {
        txChHandle = chObj->dmaChCfg->txChHandle;
        status = Udma_chGetChanEnStatus(txChHandle, &chanEnStatus);
        DebugP_assert(UDMA_SOK == status);
        if(chanEnStatus == 1U)
        {
            /* Disable Channel */
            status = Udma_chDisable(txChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT * 10U);
        }

        do
        {
            tempRetVal = Udma_ringFlushRaw(Udma_chGetFqRingHandle(txChHandle), &pDesc);
        }while(UDMA_ETIMEOUT != tempRetVal);

        /* Reset the tx channel if channel teardown fails */
        if(SystemP_SUCCESS != status)
        {
            status = Udma_chReset(txChHandle);
        }

        /* Set lastPlayed index as AASRC_TX_DMA_RING_ELEM_CNT-1. (So on playing first TRPD will be updated to 0) */
        chObj->lastPlayed = AASRC_TX_DMA_TR_COUNT-1U;
        chObj->lastFilled = AASRC_TX_DMA_TR_COUNT-1U;

        chObj->txDmaIcnt.initDone = 0U;

        DebugP_assert(SystemP_SUCCESS == status);
    }
    else
    {
        /* Do nothing */
    }

    return status;
}

int32_t AASRC_disableDmaRx(AASRC_ChHandle chHandle)
{
    int32_t status = SystemP_SUCCESS;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    Udma_ChHandle rxChHandle = NULL;
    uint8_t chanEnStatus;
    int32_t  tempRetVal;
    uint64_t pDesc;

    if(NULL != chObj)
    {
        rxChHandle = chObj->dmaChCfg->rxChHandle;

        status = Udma_chGetChanEnStatus(rxChHandle, &chanEnStatus);
        DebugP_assert(UDMA_SOK == status);
        if(chanEnStatus == 1U)
        {
            /* Disable Channel */
            status = Udma_chDisable(rxChHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT * 10U);
        }

        do
        {
            tempRetVal = Udma_ringFlushRaw(Udma_chGetFqRingHandle(rxChHandle), &pDesc);
        }while(UDMA_ETIMEOUT != tempRetVal);

        /* Reset the rx channel if channel teardown fails */
        if(SystemP_SUCCESS != status)
        {
            status = Udma_chReset(rxChHandle);
        }

        /* Set last record queued index */
        chObj->lastRecQueued = AASRC_RX_DMA_TR_COUNT-1U;
        chObj->lastReceived = AASRC_RX_DMA_TR_COUNT-1U;

        chObj->rxDmaIcnt.initDone = 0U;

        DebugP_assert(SystemP_SUCCESS == status);
    }
    else
    {
        /* Do nothing */
    }

    return status;
}

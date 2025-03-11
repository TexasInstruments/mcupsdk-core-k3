/*
 *  Copyright (c) Texas Instruments Incorporated 2020-2025
 *  All rights reserved.
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
 *  \file csitx_drvUdma.c
 *
 *  \brief File containing the CSITX driver UDMA initialization and
 *         configuration code.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/csitx/v0/include/csitx_drvPriv.h>
#include <drivers/csitx/v0/include/csitx_drvUdma.h>
#include <kernel/dpl/CacheP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define INITIALIZED      0x1
#define UNINITIALIZED    0x0

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * UDMA Memories
 */
static uint8_t gCsitxRingMem[CSITX_NUM_CH][CSITX_DRV_RING_MEM_SIZE_ALIGN]
                            __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t gCsitxUdmaTprdMem
        [CSITX_NUM_CH][CSITX_TX_QUEUE_DEPTH_PER_CH][CSITX_DRV_TRPD_SIZE_ALIGN]
                            __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
extern CsitxDrv_CommonObj gCsitxCommonObj;
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
extern uint32_t gTxTrSubmit[CSITX_DRV_TR_LOG_CNT][3];
extern uint32_t gTxTrSubmitCnt;
extern uint32_t gTxTrOut[CSITX_DRV_TR_LOG_CNT][3];
extern uint32_t gTxTrOutCnt;
#endif
uint32_t gCsitxUdmaMasterEvntInitDone = UNINITIALIZED;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                   */
/* ========================================================================== */

static uint16_t CsitxDrv_getIcnt0(const Csitx_ChCfg *chCfg);
static uint32_t CsitxDrv_dtIndex(const CsitxDrv_ChObj *chObj);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t CsitxDrv_setDMACfgParams(CsitxDrv_ChObj *chObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chType;

    /* Assign UDMA Tx channel params from channel configurations */
    chObj->txChParams = &chObj->chCfg->txChParams;
    /* Init UDMA channel parameters */
    chType = UDMA_CH_TYPE_TX_TR;
    UdmaChPrms_init(&chObj->chParams, chType);
    chObj->trpdMem = &gCsitxUdmaTprdMem[chObj->psilThreadId][0U][0U];
    chObj->txFqRingMem = &gCsitxRingMem[chObj->psilThreadId][0U];
    if(CSITX_INSTANCE_ID_0 == chObj->instObj->drvInstId)
    {
        chObj->chParams.peerChNum            = (CSL_PSIL_CSI_TX0_CH0 +
                                           chObj->psilThreadId);
    }
    chObj->chParams.fqRingPrms.ringMem   = chObj->txFqRingMem;
    chObj->chParams.fqRingPrms.orderId   = chObj->chCfg->ringOrderId;
    chObj->chParams.fqRingPrms.elemCnt   = CSITX_TX_QUEUE_DEPTH_PER_CH;
    /* Config TX channel */
    /* Get the PSI-L Threads/DMA channel configuration parameters */
    chObj->dmaCfgParams.chNum = chObj->psilThreadId;
    chObj->dmaCfgParams.vc    = chObj->chCfg->vcNum;
    chObj->dmaCfgParams.dt    = chObj->chCfg->outCsiDataType;

    if (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_YUV422_8B)
    {
        /* Storage mode for YUV422 data format */
        if (chObj->chCfg->inFmt.dataFormat == FVID2_DF_YUV422I_UYVY)
        {
            chObj->dmaCfgParams.yuv422Mode      = CSL_CSITX_YUV422_MODE_YVYU;
        }
        else if (chObj->chCfg->inFmt.dataFormat == FVID2_DF_YUV422I_YUYV)
        {
            chObj->dmaCfgParams.yuv422Mode = CSL_CSITX_YUV422_MODE_VYUY;
        }
        else if (chObj->chCfg->inFmt.dataFormat == FVID2_DF_YUV422I_YVYU)
        {
            chObj->dmaCfgParams.yuv422Mode = CSL_CSITX_YUV422_MODE_UYVY;
        }
        else if (chObj->chCfg->inFmt.dataFormat == FVID2_DF_YUV422I_VYUY)
        {
            chObj->dmaCfgParams.yuv422Mode = CSL_CSITX_YUV422_MODE_YUYV;
        }
        else
        {
            /* If input format is not YUV422, this parameter values is not used */
            chObj->dmaCfgParams.yuv422Mode = CSL_CSITX_YUV422_MODE_UYVY;
        }
    }

    if (chObj->chCfg->inFmt.ccsFormat == FVID2_CCSF_BITS12_PACKED)
    {
        chObj->dmaCfgParams.pck12CfgEnable = 1U;
    }
    else if (chObj->chCfg->inFmt.ccsFormat == FVID2_CCSF_BITS12_UNPACKED16)
    {
        chObj->dmaCfgParams.pck12CfgEnable = 0U;
    }
    else
    {
        /* If input format is not RAW12, this parameter values is not used */
        chObj->dmaCfgParams.pck12CfgEnable = 0U;
    }
    if (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_RAW20)
    {
        chObj->dmaCfgParams.dataSizeShift =
                            CSL_CSITX_DMA_DATA_SIZE_SHIFT_32BITS;
    }
    else if ((chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_YUV420_10B) ||
             (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_YUV422_10B) ||
             (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_YUV422_8B) ||
             (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_RAW10) ||
             (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_RAW12) ||
             (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_RAW14) ||
             (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_RAW16) ||
             (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_RGB888))
    {
        chObj->dmaCfgParams.dataSizeShift =
                            CSL_CSITX_DMA_DATA_SIZE_SHIFT_32BITS;
        if ((chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_RAW12) &&
            (chObj->chCfg->inFmt.ccsFormat == FVID2_CCSF_BITS12_PACKED))
        {
            chObj->dmaCfgParams.dataSizeShift =
                            (uint32_t)CSL_CSITX_DMA_DATA_SIZE_SHIFT_8BITS;
        }
    }
    else if (chObj->chCfg->outCsiDataType == FVID2_CSI2_DF_RAW8)
    {
        chObj->dmaCfgParams.dataSizeShift =
                            CSL_CSITX_DMA_DATA_SIZE_SHIFT_16BITS;
    }
    else
    {
        chObj->dmaCfgParams.dataSizeShift =
                            CSL_CSITX_DMA_DATA_SIZE_SHIFT_8BITS;
    }
    chObj->dmaCfgParams.l2lDelay     = chObj->chCfg->hBlank;
    retVal = CSL_csitxFrmToFrmDelayCfg((CSL_csi_tx_ifRegs *)chObj->instObj->shimBaseAddr,
                                                            chObj->chCfg->vcNum,
                                                            chObj->chCfg->vBlank);
    chObj->dmaCfgParams.numBytesLine =  (chObj->chCfg->inFmt.width * CsitxDrv_getBpp(chObj->chCfg->outCsiDataType)) / 8;
    GT_assert(CsitxTrace,(chObj->dmaCfgParams.numBytesLine != 0U));

    return retVal;
}

int32_t CsitxDrv_setUdmaParams(CsitxDrv_CommonObj *txObj,
                               CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK, tempRetVal = UDMA_SOK;
    uint32_t chIdx, chType;
    CsitxDrv_ChObj *chObj;
    Udma_EventHandle eventHandle;
    Udma_EventPrms eventParams;


    if(retVal ==FVID2_SOK)
    {
        for (chIdx = 0U ; chIdx < instObj->createParams.numCh ; chIdx++)
        {
            chObj =&instObj->chObj[chIdx];
            if (chObj->chCfg->chType == CSITX_CH_TYPE_TX)
            {
                if (txObj->initParams.drvHandle == NULL)
                {
                    retVal = FVID2_EBADARGS;
                    GT_0trace(CsitxTrace,
                              GT_ERR,
                              "Invalid UDMA DRV Handle!!\r\n");
                    break;
                }
                if (gCsitxUdmaMasterEvntInitDone != INITIALIZED)
                {

                    /* Register the UDMA Master event handle */
                    UdmaEventPrms_init(&eventParams);
                    eventParams.eventType         = UDMA_EVENT_TYPE_MASTER;
                    eventParams.appData           = txObj;
                    tempRetVal = Udma_eventRegister(txObj->initParams.drvHandle,
                                                    &txObj->masterEvent,
                                                    &eventParams);
                    gCsitxUdmaMasterEvntInitDone = INITIALIZED;
                }
                /* Program UDMA channels only for Tx channels */
                chType = UDMA_CH_TYPE_TX_TR;
                /* Open UDMA channel */
                tempRetVal = Udma_chOpen(txObj->initParams.drvHandle,
                                         &chObj->txChObj,
                                         chType,
                                         &chObj->chParams);

                if(tempRetVal != UDMA_SOK)
                {
                    retVal = FVID2_EFAIL;
                    GT_0trace(CsitxTrace,
                              GT_ERR,
                              "[ERROR]UDMA channel open FAILED!!!\r\n");
                }

                if (retVal == FVID2_SOK)
                {
                    /* Configure UDMA Tx Channel */
                    tempRetVal = Udma_chConfigTx(&chObj->txChObj,
                                                 chObj->txChParams);

                    if(tempRetVal != UDMA_SOK)
                    {
                        retVal = FVID2_EFAIL;
                        GT_0trace(CsitxTrace,
                              GT_ERR,
                              "[ERROR]UDMA TX channel config FAILED!!!\r\n");
                    }

                }

                if (retVal == FVID2_SOK)
                {
                    /* Register callbacks here */
                    /* Register ring completion callback */
                    eventHandle = &chObj->cqEventObj;
                    UdmaEventPrms_init(&eventParams);
                    eventParams.eventType         = UDMA_EVENT_TYPE_DMA_COMPLETION;
                    eventParams.eventMode         = UDMA_EVENT_MODE_SHARED;
                    eventParams.chHandle          = &chObj->txChObj;
                    eventParams.masterEventHandle = &txObj->masterEvent;
                    eventParams.eventCb           = &CsitxDrv_udmaCQEventCb;
                    eventParams.appData           = chObj;
                    tempRetVal = Udma_eventRegister(txObj->initParams.drvHandle,
                                                    eventHandle,
                                                    &eventParams);

                    if(tempRetVal != UDMA_SOK)
                    {
                        retVal = FVID2_EFAIL;
                        GT_0trace(CsitxTrace,
                              GT_ERR,
                              "[ERROR]UDMA CQ event register FAILED!!!\r\n");
                    }

                }
            }

            if (retVal == FVID2_SOK)
            {
                /* Set channel status to created */
                chObj->status = CSITX_DRV_CH_STATE_CREATED;
            }

        }
    }

    return retVal;
}

int32_t CsitxDrv_clearUdmaParams(CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK, tempRetVal = UDMA_SOK;
    uint32_t chIdx;
    CsitxDrv_ChObj *chObj;
    Udma_EventHandle eventHandle;

    for (chIdx = 0U ; chIdx < instObj->createParams.numCh ; chIdx++)
    {
        chObj =&instObj->chObj[chIdx];
        if (chObj->chCfg->chType == CSITX_CH_TYPE_TX)
        {
            /* Unregister ring completion callback */
            eventHandle = &chObj->cqEventObj;
            tempRetVal += Udma_eventUnRegister(eventHandle);

            /* Close UDMA channel */
            tempRetVal += Udma_chClose(&chObj->txChObj);
        }
    }

    if (tempRetVal != UDMA_SOK)
    {
        retVal = FVID2_EFAIL;
    }

    return retVal;
}

int32_t CsitxDrv_udmaTxTrpdInit(Udma_ChHandle txChHandle,
                                uint8_t *pTrpdMem,
                                const uint32_t *srcBuf,
                                const Csitx_ChCfg *chCfg,
                                uint32_t chIdx)
{
    int32_t retVal = FVID2_SOK;
    CSL_UdmapCppi5TRPD *pTrpd = (CSL_UdmapCppi5TRPD *) pTrpdMem;
    uint32_t descType = (uint32_t)CSL_UDMAP_CPPI5_PD_DESCINFO_DTYPE_VAL_TR;
    uint32_t cqRingNum = Udma_chGetCqRingNum(txChHandle);
    CSL_UdmapTR1 *pTr = UdmaUtils_getTrpdTr1Pointer(pTrpdMem, 0U);
    uint32_t *pTrResp =
                (uint32_t *) (pTrpdMem + (sizeof(CSL_UdmapTR15) *
                                         (1U + 1U)));

    /* Setup descriptor */
    CSL_udmapCppi5SetDescType(pTrpd, descType);

    CSL_udmapCppi5TrSetReload(pTrpd, FALSE, 0U);
    /* Since each TRPD will always have only one TR */
    CSL_udmapCppi5SetPktLen(pTrpd, descType, 1U);
    /* Flow ID and Packet ID */
    CSL_udmapCppi5SetIds(pTrpd, descType, 0U, (uint32_t)UDMA_DEFAULT_FLOW_ID);
    CSL_udmapCppi5SetSrcTag(pTrpd, 0x0044);             /* Not used */
    CSL_udmapCppi5SetDstTag(pTrpd, 0x0416);             /* Not used */
    CSL_udmapCppi5TrSetEntryStride(pTrpd,
        CSL_UDMAP_CPPI5_TRPD_PKTINFO_RECSIZE_VAL_32B);
    CSL_udmapCppi5SetReturnPolicy(pTrpd,
        descType,
        /* Don't care for TR */
        CSL_UDMAP_CPPI5_PD_PKTINFO2_RETPOLICY_VAL_ENTIRE_PKT,
        CSL_UDMAP_CPPI5_PD_PKTINFO2_EARLYRET_VAL_NO,
        CSL_UDMAP_CPPI5_PD_PKTINFO2_RETPUSHPOLICY_VAL_TO_TAIL,
        cqRingNum);

    /* Initialize TR packet: Start */
    /* Setup TR */
    /* Bit fields::
       Bit No.->Info
       3:0->Type: 2D transfer
       7:6->Event Size: Event is only generated with the TR is complete
       9:8->Trigger0: No Trigger
       10:11->Trigger0 Type:
                    The second inner most loop (ICNT1) will be decremented by 1.
       13:12->Trigger1: No Trigger
       15:14->Trigger1 Type:
                    The second inner most loop (ICNT1) will be decremented by 1.
       23:16->Command ID: The Command ID for the TR
       31:24->Conf Flags: Configuration Specific Flags
       */
    pTr->flags = 0U;
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TYPE,
                            CSL_UDMAP_TR_FLAGS_TYPE_2D_DATA_MOVE);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, FALSE);
    /* EOP and EOL should be enabled as PSIL/SHIM expects these packets to
       mark the dimensions of the frame for transmission. */
    /* EOL is set to 'CSL_UDMAP_TR_FLAGS_EOL_ICNT0', this is due to ICNT0 is
       equal to the line size. EOL packet has to be sent out for each line of
       the frame. */
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_ICNT0);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE,
                            CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0,
                            CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE,
                            CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1,
                            CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE,
                            CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, chIdx);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U);
    pTr->icnt0    = CsitxDrv_getIcnt0(chCfg);
    pTr->icnt1    = (uint16_t)(chCfg->inFmt.height);
    pTr->dim1     = (uint32_t)(chCfg->inFmt.pitch[0U]);
    /* Destination address does not needed to be programmed,
       this will overwritten in Queue */
    pTr->addr     = (uint64_t) srcBuf;

    /* Clear TR response memory */
    *pTrResp = 0xFFFFFFFFU;
    /* Initialize TR packet: End */
    /* Writeback cache */
    CsitxDrv_cacheWb(pTrpdMem,
                     CSITX_DRV_TRPD_SIZE_ALIGN);
    /* check if line size is greater than pitch provided, pitch should be
       equal to or more than line size in bytes */
    if ((pTr->icnt0 > pTr->dim1) || (pTr->icnt0 == 0U))
    {
        retVal = FVID2_EFAIL;
    }

    return retVal;
}

void CsitxDrv_udmaCQEventCb(Udma_EventHandle eventHandle,
                            uint32_t eventType,
                            void *appData)
{
    int32_t retVal = UDMA_SOK;
    CsitxDrv_ChObj *chObj;
    CsitxDrv_QueObj *qObj;
    CsitxDrv_ChBufManObj *bmObj;
    CsitxDrv_InstObj *instObj;
    uint64_t pDesc = 0;
    uint32_t *pTrResp;
    uint32_t pTrRespVal, pTrRespStsTypeVal;
    uint32_t curQCnt, appCb = 0U, cookie, enterULP = 0U, chIdx;
    uint32_t chNum = 0U;
    uint64_t timeStamp;
    CsitxDrv_ChObj *submitChObj;

    chObj = (CsitxDrv_ChObj *) appData;
    instObj = chObj->instObj;
    GT_assert(CsitxTrace, (chObj != NULL));

    /* Take out completed TRPD from UDMA CQ Ring */
    if(eventType == UDMA_EVENT_TYPE_DMA_COMPLETION)
    {
        /* Disable HW interrupts here */
        cookie = HwiP_disable();
        bmObj = &chObj->bufManObj;
        /* Response received in completion queue, empty up full CQ Ring */
        while (retVal == UDMA_SOK)
        {
            retVal = Udma_ringDequeueRaw(
                         Udma_chGetCqRingHandle(&chObj->txChObj), &pDesc);
            if(retVal == UDMA_SOK)
            {
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
                {
                    gTxTrOut[gTxTrOutCnt][0U] = (uint32_t)pDesc;
                    gTxTrOut[gTxTrOutCnt][1U] = chObj->chCfg->chId;
                    if (gCsitxCommonObj.getTimeStamp != NULL)
                    {
                        gTxTrOut[gTxTrOutCnt][2U] =
                                        (uint32_t)gCsitxCommonObj.getTimeStamp(NULL);;
                    }
                    else
                    {
                        gTxTrOut[gTxTrOutCnt][2U] = 0U;
                    }
                    gTxTrOutCnt = (gTxTrOutCnt + 1U) % CSITX_DRV_TR_LOG_CNT;
                    CsitxDrv_cacheWb(&gTxTrOut[0U],
                                     sizeof(gTxTrOut));
                }
#endif
                if (gCsitxCommonObj.getTimeStamp != NULL)
                {
                    timeStamp = gCsitxCommonObj.getTimeStamp(NULL);
                }
                else
                {
                    timeStamp = 0U;
                }
                /* De-queue from curQ */
                qObj = (CsitxDrv_QueObj *) Fvid2Utils_dequeue(bmObj->curQ);
                GT_assert(CsitxTrace, (qObj != NULL));
                GT_assert(CsitxTrace,
                          (chObj->chCfg->chId == qObj->chObj->chCfg->chId));
                /* Check returned descriptor pointer */
                GT_assert(CsitxTrace, (pDesc == ((uint64_t) qObj->trpd)));
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
                gCsitxCommonObj.frmChId[gCsitxCommonObj.frmCnt] =
                                                qObj->chObj->chCfg->chId;
                gCsitxCommonObj.frmInstId[gCsitxCommonObj.frmCnt] =
                                        qObj->chObj->instObj->drvInstId;
                if (gCsitxCommonObj.getTimeStamp != NULL)
                {
                    gCsitxCommonObj.frmTS[gCsitxCommonObj.frmCnt] =
                                            (uint32_t)(timeStamp / 1000U);
                }
#endif
                GT_assert(CsitxTrace, (qObj->frm != NULL));
                qObj->frm->timeStamp64 = timeStamp;
                /* Invalidate cache */
                CsitxDrv_cacheInv(qObj->trpd,
                                  CSITX_DRV_TRPD_SIZE_ALIGN);
                /* de-queued TRPD was for frame submitted
                   by application */
                /* Check for truncated/elongated frame */
                pTrResp = (uint32_t *) ((uint8_t *)(qObj->trpd) +
                                       (sizeof(CSL_UdmapTR15) *
                                       (1U + 1U)));
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
                gCsitxCommonObj.trResp[gCsitxCommonObj.frmCnt] =
                                            CSL_REG32_RD(pTrResp);
                gCsitxCommonObj.frmType[gCsitxCommonObj.frmCnt] = 1U;
#endif
                pTrRespVal = CSL_REG32_RD(pTrResp);
                pTrRespStsTypeVal = CSL_REG32_FEXT(pTrResp, UDMAP_TR_RESPONSE_STATUS_TYPE);
                /* check TR response */
                if (pTrRespStsTypeVal!=
                   (CSL_UDMAP_TR_RESPONSE_STATUS_COMPLETE))
                {

                    if ((chObj->status == CSITX_DRV_CH_STATE_STOPPING) ||
                        (chObj->status == CSITX_DRV_CH_STATE_STOPPED) ||
                        (pTrRespStsTypeVal == CSL_UDMAP_TR_RESPONSE_STATUS_ABORTED_ERR))
                    {
                        /* Aborted frame due to forced teardown at
                           Udma_chDisable() */
                        qObj->frm->status = (uint32_t)FVID2_FRAME_STATUS_ABORTED;
                    }
                    else if (pTrRespStsTypeVal == CSL_UDMAP_TR_RESPONSE_STATUS_SUBMISSION_ERR)
                    {
                        /* Submission error */
                        qObj->frm->status =
                                (uint32_t)FVID2_FRAME_STATUS_SUBMISSION_ERROR;
                    }
                    else if (pTrRespStsTypeVal == CSL_UDMAP_TR_RESPONSE_STATUS_TRANSFER_EXCEP_ERR)
                    {
                        /* Transfer exception*/
                        if(((pTrRespVal >>
                            (CSL_UDMAP_TR_RESPONSE_STATUS_INFO_SHIFT)) &
                            (CSL_UDMAP_TR_RESPONSE_STATUS_INFO_MASK)) ==
                            (CSL_UDMAP_TR_RESPONSE_STATUS_TRANSFER_EXCEP_SHORT_PACKET))
                        {
                            /* Received frame is truncated */
                            qObj->frm->status =
                                   (uint32_t)FVID2_FRAME_STATUS_TRUNCATED;
                        }
                        else if (((pTrRespVal >>
                                  (CSL_UDMAP_TR_RESPONSE_STATUS_INFO_SHIFT)) &
                                  (CSL_UDMAP_TR_RESPONSE_STATUS_INFO_MASK)) ==
                                  (CSL_UDMAP_TR_RESPONSE_STATUS_TRANSFER_EXCEP_LONG_PACKET))
                        {
                            /* Received frame is elongated */
                            qObj->frm->status =
                                    (uint32_t)FVID2_FRAME_STATUS_ELONGATED;
                        }
                    }

                    else
                    {
                        /* Other UDMA TR errors */
                        qObj->frm->status =
                                (uint32_t)FVID2_FRAME_STATUS_ERROR;
                    }
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
                    gCsitxCommonObj.frmStatus[gCsitxCommonObj.frmCnt] =
                                                qObj->frm->status;
#endif
                }
                else
                {
                    /* Received frame has no error */
                    qObj->frm->status = FVID2_FRAME_STATUS_COMPLETED;
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
                    gCsitxCommonObj.frmStatus[gCsitxCommonObj.frmCnt] =
                                                    qObj->frm->status;
#endif
                }
                appCb = 1U;
                /* Return the frame to done queue */
                Fvid2Utils_queue(
                    instObj->bufManObj.doneQ,
                    &qObj->qElem,
                    qObj);
                if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                                CSITX_ENABLE_SERIAL_TRANS_ENABLE)
                {
                    instObj->bufManObj.curFrmNum--;
                }
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
                uint32_t oldFrmCnt;

                oldFrmCnt = gCsitxCommonObj.frmCnt;
                gCsitxCommonObj.frmCnt = (gCsitxCommonObj.frmCnt + 1U) %
                                          CSITX_DRV_LOG_CNT;
                if (oldFrmCnt > gCsitxCommonObj.frmCnt)
                {
                    gCsitxCommonObj.frmCntOverflow = 1U;
                }
#endif
            }
        }
        if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                    CSITX_ENABLE_SERIAL_TRANS_ENABLE)
        {
            /* Queue the next frame from waitQ to UDMA, this is needed to have only
               one frame active at a time. */
            /* Check if no frames are current being queue to UDMA channels.
               If not, submit a frame to UDMA channel */
            if (instObj->bufManObj.curFrmNum == 0U)
            {
                /* Take a object from waiting Q and put in respective channel's
                   curQ (submit the same to UDMA) */
                qObj =
                 (CsitxDrv_QueObj *) Fvid2Utils_dequeue(instObj->bufManObj.waitQ);
                if (qObj == NULL)
                {
                    /* No Error since, no frames could be queued */
                }
                else
                {
                    /* Submit it to respective channel's curQ */
                    submitChObj = qObj->chObj;
                    retVal = Udma_ringQueueRaw(
                        Udma_chGetFqRingHandle(&submitChObj->txChObj),
                        (uint64_t)qObj->trpd);
                    if(retVal != UDMA_SOK)
                    {
                        GT_0trace(
                            CsitxTrace, GT_ERR,
                            "Queue: Submitting of TR failed\r\n");
                        /* Queue back the Object which was
                           de-queued earlier from waitQ */
                        Fvid2Utils_queue(instObj->bufManObj.waitQ, &qObj->qElem, qObj);
                        retVal = FVID2_EFAIL;
                    }
                    else
                    {
                        /* Add the queue object in driver's current queue */
                        Fvid2Utils_queue(submitChObj->bufManObj.curQ,
                                         &qObj->qElem,
                                         qObj);
                        instObj->bufManObj.curFrmNum++;
                    }
                }
            }
        }
        /** Enable HW interrupts here */
        HwiP_restore(cookie);

        if (chObj->status == CSITX_DRV_CH_STATE_RUNNING)
        {
            /* Application call back */
            if (appCb == 1U)
            {
                if(instObj->fdmCbParams.fdmCbFxn != NULL)
                {
                    instObj->fdmCbParams.fdmCbFxn(instObj->fdmCbParams.fdmData);
                }
            }
        }

        /* Disable HW interrupts here */
        cookie = HwiP_disable();
        /* Go into ULP state only if there are no frames queued */
        if ((retVal == FVID2_SOK) &&
            (instObj->dphyCfg.clkMode == CSITX_CLK_MODE_NON_CONTINUOUS))
        {
            /* check waitQ first */
            if (Fvid2Utils_getNumQElem(instObj->bufManObj.waitQ) == 0U)
            {
                enterULP = 1U;
            }
            if ((instObj->numColorbarCh != 0U) ||
                (instObj->numLpbkCh != 0U))
            {
                enterULP = 1U;
            }
            /* check curQ for each channel */
            if (enterULP == 0U)
            {
                /* Set 'enterULP' to '1' and unset it if atleast a frame is
                   queued for any channel */
                enterULP = 1U;

                chNum = (instObj->numTxCh +
                         instObj->numColorbarCh +
                         instObj->numLpbkCh);
                for (chIdx = 0U ; chIdx < chNum ; chIdx++)
                {
                    if ((instObj->chObj[chIdx].psilThreadstatus == TRUE) &&
                        (Fvid2Utils_getNumQElem(instObj->chObj[chIdx].bufManObj.curQ)
                                                                    > 0U))
                    {
                        enterULP = 0U;
                        break;
                    }
                }
            }

            if (enterULP == 1U)
            {
                retVal = CsitxDrv_dphytxSetLaneState(instObj,
                                                CSITX_DPHY_MODE_ULP);
            }
        }
        if (chObj->status == CSITX_DRV_CH_STATE_RUNNING)
        {
            if (instObj->createParams.instCfg.enableFrameRepeat == 1U)
            {
                /* Repeat Frame only if enabled */
                /* Check if one more frame is queued by application,
                   if not then re-submit last TR */
                curQCnt = Fvid2Utils_getNumQElem(bmObj->curQ);
                if (curQCnt == 0U)
                {
                    /* Repeat last frame */
                }
            }
        }
        /** Enable HW interrupts here */
        HwiP_restore(cookie);
    }
    else
    {
        /* Spurious UDMA interrupt */
    }
}

void CsitxDrv_cacheWb(const void *addr, int32_t size)
{
    uint32_t    isCacheCoherent = Udma_isCacheCoherent();

    if(isCacheCoherent != TRUE)
    {
        CacheP_wb((void*)addr, size, CacheP_TYPE_ALL);
    }

    return;
}

void CsitxDrv_cacheInv(const void * addr, int32_t size)
{
    uint32_t    isCacheCoherent = Udma_isCacheCoherent();

    if(isCacheCoherent != TRUE)
    {
        CacheP_inv((void *)addr, size, CacheP_TYPE_ALL);
    }

    return;
}

uint8_t* CsitxDrv_getTrpdMemAddr(uint32_t chIdx, uint32_t qCnt)
{
    return (&gCsitxUdmaTprdMem[chIdx][qCnt][0U]);
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static uint16_t CsitxDrv_getIcnt0(const Csitx_ChCfg *chCfg)
{
    uint16_t icnt0     = 0U;
    uint32_t bpp       = 0U;
    uint32_t tempicnt0 = 0U;

    bpp = CsitxDrv_getStorageBpp(chCfg->outCsiDataType);
    GT_assert(CsitxTrace, (bpp != 0U));
    /* check for RAW12 packed format */
    if ((chCfg->outCsiDataType == FVID2_CSI2_DF_RAW12) &&
        (chCfg->inFmt.ccsFormat == FVID2_CCSF_BITS12_PACKED))
    {
        bpp = CSITX_BITS_PER_PIXEL_12_BITS;
    }

    /* icnt0 expressed in bits */
    tempicnt0 = (chCfg->inFmt.width * bpp);
    if ((chCfg->outCsiDataType == FVID2_CSI2_DF_RAW12) &&
         (chCfg->inFmt.ccsFormat == FVID2_CCSF_BITS12_PACKED))
    {
        /* icnt0 currently in bits, rounding off to next word boundary */
        icnt0 = (tempicnt0 + 31U) / 32U;
        /* icnt0 in bytes */
        icnt0 = icnt0 * 4U;
    }
    else
    {
        /* icnt0 in bytes */
        icnt0 = tempicnt0 / 8U;
    }

    return icnt0;
}

static uint32_t CsitxDrv_dtIndex(const CsitxDrv_ChObj *chObj)
{
    uint32_t dtIndex;

    for (dtIndex = 0U ; dtIndex < (chObj->instObj->cslObj.dtInUse) ; dtIndex++)
    {
        if (chObj->chCfg->outCsiDataType ==
                                chObj->instObj->cslObj.dtCfg[dtIndex].dataType)
        {
            break;
        }
    }

    return dtIndex;
}

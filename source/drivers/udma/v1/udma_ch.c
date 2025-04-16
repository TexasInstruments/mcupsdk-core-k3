/*
 *  Copyright (C)2018-2025 Texas Instruments Incorporated
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
 *  \file udma_ch.c
 *
 *  \brief File containing the UDMA driver channel related APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/udma/v1/udma_priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CSL_PSILCFG_REG_STATIC_TR               ((uint32_t) 0x400U)
#define CSL_PSILCFG_REG_RT_ENABLE               ((uint32_t) 0x408U)

/* PSILCFG_REG_RT_ENABLE */
#define CSL_PSILCFG_REG_RT_ENABLE_IDLE_SHIFT                (1U)
#define CSL_PSILCFG_REG_RT_ENABLE_IDLE_MASK                 ((uint32_t)0x01U<<CSL_PSILCFG_REG_RT_ENABLE_IDLE_SHIFT)
#define CSL_PSILCFG_REG_RT_ENABLE_FLUSH_SHIFT               (28U)
#define CSL_PSILCFG_REG_RT_ENABLE_FLUSH_MASK                ((uint32_t)0x01U << CSL_PSILCFG_REG_RT_ENABLE_FLUSH_SHIFT)
#define CSL_PSILCFG_REG_RT_ENABLE_PAUSE_SHIFT               (29U)
#define CSL_PSILCFG_REG_RT_ENABLE_PAUSE_MASK                ((uint32_t)0x01U<<CSL_PSILCFG_REG_RT_ENABLE_PAUSE_SHIFT)
#define CSL_PSILCFG_REG_RT_ENABLE_TDOWN_SHIFT               (30U)
#define CSL_PSILCFG_REG_RT_ENABLE_TDOWN_MASK                ((uint32_t)0x01U<<CSL_PSILCFG_REG_RT_ENABLE_TDOWN_SHIFT)
#define CSL_PSILCFG_REG_RT_ENABLE_ENABLE_SHIFT              (31U)
#define CSL_PSILCFG_REG_RT_ENABLE_ENABLE_MASK               ((uint32_t)0x01U<<CSL_PSILCFG_REG_RT_ENABLE_ENABLE_SHIFT)

/* PSILCFG_REG_STATIC_TR */
#define CSL_PSILCFG_REG_STATIC_TR_X_SHIFT                   (24U)
#define CSL_PSILCFG_REG_STATIC_TR_X_MASK                    (((uint32_t)0x0007U) << CSL_PSILCFG_REG_STATIC_TR_X_SHIFT)
#define CSL_PSILCFG_REG_STATIC_TR_Y_SHIFT                   (0U)
#define CSL_PSILCFG_REG_STATIC_TR_Y_MASK                    (((uint32_t)0x0FFFU) << CSL_PSILCFG_REG_STATIC_TR_Y_SHIFT)
#define CSL_PSILCFG_REG_STATIC_TR_Z_SHIFT                   (0U)
#define CSL_PSILCFG_REG_STATIC_TR_Z_MASK                    (((uint32_t)0x0FFFU) << CSL_PSILCFG_REG_STATIC_TR_Z_SHIFT)
#define CSL_PSIL_REG_STATIC_TR_BURST_SHIFT                  (31U)
#define CSL_PSIL_REG_STATIC_TR_BURST_MASK                   (((uint32_t)0x1U) << CSL_PSIL_REG_STATIC_TR_BURST_SHIFT)
#define CSL_PSIL_REG_STATIC_TR_ACC2_SHIFT                   (30U)
#define CSL_PSIL_REG_STATIC_TR_ACC2_MASK                    (((uint32_t)0x1U) << CSL_PSIL_REG_STATIC_TR_ACC2_SHIFT)
#define CSL_PSIL_REG_STATIC_TR_EOL_SHIFT                    (31U)
#define CSL_PSIL_REG_STATIC_TR_EOL_MASK                     (((uint32_t)0x1U) << CSL_PSIL_REG_STATIC_TR_EOL_SHIFT)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void  Udma_chAssignRegOverlay(Udma_DrvHandleInt drvHandle, Udma_ChHandleInt chHandle);
static void  Udma_chInitRegs(Udma_ChHandleInt chHandle);
static void  Udma_chPauseTxLocal(Udma_DrvHandleInt drvHandle, uint32_t txChNum, uint32_t chType);
static void  Udma_chUnpauseTxLocal(Udma_DrvHandleInt drvHandle, uint32_t txChNum, uint32_t chType);
static void  Udma_chPauseRxLocal(Udma_DrvHandleInt drvHandle, uint32_t rxChNum);
static void  Udma_chUnpauseRxLocal(Udma_DrvHandleInt drvHandle, uint32_t rxChNum);
static int32_t Udma_chCheckParams(Udma_DrvHandleInt drvHandle,
                                  uint32_t chType,
                                  const Udma_ChPrms *chPrms);
static int32_t Udma_chAllocResource(Udma_ChHandleInt chHandle);
static int32_t Udma_chFreeResource(Udma_ChHandleInt chHandle);
static int32_t Udma_chPair(Udma_ChHandleInt chHandle);
static int32_t Udma_chUnpair(Udma_ChHandleInt chHandle);
static void Udma_chEnableLocal(Udma_ChHandleInt chHandle);
static int32_t Udma_chDisableBlkCpyChan(Udma_ChHandleInt chHandle, uint32_t timeout);
static int32_t Udma_chDisableTxChan(Udma_ChHandleInt chHandle, uint32_t timeout);
static int32_t Udma_chDisableRxChan(Udma_ChHandleInt chHandle, uint32_t timeout);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Udma_chOpen(Udma_DrvHandle drvHandle,
                    Udma_ChHandle chHandle,
                    uint32_t chType,
                    const Udma_ChPrms *chPrms)
{
    int32_t             retVal = UDMA_SOK, tempRetVal;
    uint32_t            allocDone = (uint32_t) FALSE;
    Udma_ChHandleInt    chHandleInt;
    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle;

    /* Error check */
    if((drvHandleInt == NULL) || (NULL == chHandle) || (NULL == chPrms))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        if(drvHandleInt->drvInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        retVal = Udma_chCheckParams(drvHandleInt, chType, chPrms);
    }

    if(UDMA_SOK == retVal)
    {
        /* Copy and init parameters */
        chHandleInt = (Udma_ChHandleInt) chHandle;
        (void) memset(chHandleInt, 0, sizeof(Udma_ChObject));
        (void) memcpy(&chHandleInt->chPrms, chPrms, sizeof(Udma_ChPrms));
        chHandleInt->chType            = chType;
        chHandleInt->drvHandle         = drvHandleInt;
        chHandleInt->txChNum           = UDMA_DMA_CH_INVALID;
        chHandleInt->rxChNum           = UDMA_DMA_CH_INVALID;
        chHandleInt->pdmaChNum         = UDMA_DMA_CH_INVALID;
        chHandleInt->fqRing            = (Udma_RingHandleInt) NULL;
        chHandleInt->cqRing            = (Udma_RingHandleInt) NULL;
        chHandleInt->tdCqRing          = (Udma_RingHandleInt) NULL;
        UdmaChTxPrms_init(&chHandleInt->txPrms, chType);
        UdmaChRxPrms_init(&chHandleInt->rxPrms, chType);
        Udma_chInitRegs(chHandleInt);
        chHandleInt->chOesAllocDone    = FALSE;
        chHandleInt->trigger           = CSL_UDMAP_TR_FLAGS_TRIGGER_NONE;
    }

    if(UDMA_SOK == retVal)
    {
        /* Alloc UDMA channel/rings */
        retVal = Udma_chAllocResource(chHandleInt);
        if(UDMA_SOK == retVal)
        {
            allocDone = (uint32_t) TRUE;
        }
        else
        {
            DebugP_logError("[UDMA] Channel resource allocation failed!!\r\n");
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Pair channels */
        retVal = Udma_chPair(chHandleInt);
        if(UDMA_SOK != retVal)
        {
            DebugP_logError("[UDMA] Channel paring failed!!\r\n");
        }
    }

    if(UDMA_SOK == retVal)
    {
        chHandleInt->chInitDone = UDMA_INIT_DONE;
    }
    else
    {
        /* Error. Free-up resource if allocated */
        if(((uint32_t) TRUE) == allocDone)
        {
            tempRetVal = Udma_chFreeResource(chHandleInt);
            if(UDMA_SOK != tempRetVal)
            {
                DebugP_logError("[UDMA] Free resource failed!!!\r\n");
            }
        }
    }

    return (retVal);
}

int32_t Udma_chClose(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }
    if(UDMA_SOK == retVal)
    {
        if(TRUE == chHandleInt->chOesAllocDone)
        {
            retVal = UDMA_EFAIL;
            DebugP_logError("[UDMA] Channel OES not de-allocated!!!\r\n");
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Unpair channels */
        retVal = Udma_chUnpair(chHandleInt);
        if(UDMA_SOK != retVal)
        {
            DebugP_logError("[UDMA] Channel unparing failed!!\r\n");
        }

        /* Free-up UDMA channel/rings */
        retVal += Udma_chFreeResource(chHandleInt);
        if(UDMA_SOK != retVal)
        {
            DebugP_logError("[UDMA] Free resource failed!!!\r\n");
        }

        (void) memset(chHandleInt, 0, sizeof(*chHandleInt));
        chHandleInt->chInitDone = UDMA_DEINIT_DONE;
    }

    return (retVal);
}

int32_t Udma_chConfigTx(Udma_ChHandle chHandle, const Udma_ChTxPrms *txPrms)
{
    int32_t                 retVal = UDMA_SOK;
    Udma_DrvHandleInt       drvHandle;
    Udma_ChHandleInt        chHandleInt = (Udma_ChHandleInt) chHandle;
    CSL_PktdmaChanCfg       pPktTxChanCfg;
    CSL_BcdmaChanCfg        pBcTxChanCfg;

    /* Error check */
    if((NULL == chHandleInt) ||
       (chHandleInt->chInitDone != UDMA_INIT_DONE) ||
       ((chHandleInt->chType & UDMA_CH_FLAG_TX) != UDMA_CH_FLAG_TX))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        if(chHandleInt->txChNum != UDMA_DMA_CH_INVALID)
        {
            if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
            {
                pPktTxChanCfg.pauseOnError = txPrms->pauseOnError;
                pPktTxChanCfg.filterEinfo = txPrms->filterEinfo;
                pPktTxChanCfg.filterPsWords = txPrms->filterPsWords;
                pPktTxChanCfg.bNoTeardownCompletePkt = txPrms->supressTdCqPkt;
                pPktTxChanCfg.chanType = txPrms->chanType;
                pPktTxChanCfg.tdType = txPrms->tdType;
                pPktTxChanCfg.busPriority = txPrms->busPriority;
                pPktTxChanCfg.busOrderId = txPrms->busOrderId;
                pPktTxChanCfg.dmaPriority = txPrms->dmaPriority;
                pPktTxChanCfg.burstSize = txPrms->burstSize;
                retVal = CSL_pktdmaChanCfg( &drvHandle->pktdmaRegs, chHandleInt->txChNum, &pPktTxChanCfg );
            }
            else
            {
                pBcTxChanCfg.pauseOnError = txPrms->pauseOnError;
                pBcTxChanCfg.noTDPkt = txPrms->supressTdCqPkt;
                pBcTxChanCfg.chanType = txPrms->chanType;
                pBcTxChanCfg.tdType = txPrms->tdType;
                pBcTxChanCfg.busPriority = txPrms->busPriority;
                pBcTxChanCfg.busOrderId = txPrms->busOrderId;
                pBcTxChanCfg.dmaPriority = txPrms->dmaPriority;
                pBcTxChanCfg.burstSize = txPrms->burstSize;
                if((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
                {
                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_CONFIG, CSL_BCDMA_CHAN_TYPE_BLOCK_COPY, chHandleInt->txChNum, &pBcTxChanCfg);
                }
                else
                {
                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_CONFIG, CSL_BCDMA_CHAN_TYPE_SPLIT_TX, chHandleInt->txChNum, &pBcTxChanCfg);
                }
            }
        }
        else
        {
            retVal = UDMA_EINVALID_PARAMS;
        }

        if(CSL_PASS != retVal)
        {
            DebugP_logError("[UDMA] TX config failed!!!\r\n");
        }
    }

    return (retVal);
}

int32_t Udma_chConfigRx(Udma_ChHandle chHandle, const Udma_ChRxPrms *rxPrms)
{
    int32_t                 retVal = UDMA_SOK;
    Udma_DrvHandleInt       drvHandle;
    Udma_ChHandleInt        chHandleInt = (Udma_ChHandleInt) chHandle;
    CSL_LcdmaRingaccRingCfg flowPrms;
    CSL_PktdmaChanCfg pPktRxChanCfg;
    CSL_BcdmaChanCfg pBcRxChanCfg;

    /* Error check */
    if((NULL == chHandleInt) ||
        (chHandleInt->chInitDone != UDMA_INIT_DONE) ||
        ((chHandleInt->chType & UDMA_CH_FLAG_RX) != UDMA_CH_FLAG_RX))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        if ((UDMA_INST_TYPE_LCDMA_BCDMA                 == drvHandle->instType) &&
            ((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY))
        {
            /* For BCDMA Block Copy, no need to configure Rx Channel.*/
        }
        else
        {
           if(chHandleInt->rxChNum != UDMA_DMA_CH_INVALID)
           {  
               if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
               {
                  pPktRxChanCfg.pauseOnError = rxPrms->pauseOnError;
                  pPktRxChanCfg.chanType =  rxPrms->chanType;
                  pPktRxChanCfg.busPriority = rxPrms->busPriority;
                  pPktRxChanCfg.busOrderId = rxPrms->busOrderId;
                  pPktRxChanCfg.dmaPriority = rxPrms->dmaPriority;
                  pPktRxChanCfg.bIgnoreLongPkts = rxPrms->ignoreLongPkts; 
                  retVal = CSL_pktdmaChanCfg( &drvHandle->pktdmaRegs, chHandleInt->rxChNum, &pPktRxChanCfg );
               }
               else
               {
                  pBcRxChanCfg.pauseOnError = rxPrms->pauseOnError;
                  pBcRxChanCfg.chanType =  rxPrms->chanType;
                  pBcRxChanCfg.busPriority = rxPrms->busPriority;
                  pBcRxChanCfg.busOrderId = rxPrms->busOrderId;
                  pBcRxChanCfg.dmaPriority = rxPrms->dmaPriority;
                  pBcRxChanCfg.burstSize = rxPrms->burstSize;
                  pBcRxChanCfg.rxIgnoreLong = rxPrms->ignoreLongPkts;
                  retVal = CSL_bcdmaChanCfg( &drvHandle->bcdmaRegs, chHandleInt->rxChNum, &pBcRxChanCfg );
               }
           } 

            /* Configure default flow for PDMA and other PSIL channels */
            if((((chHandleInt->chType & UDMA_CH_FLAG_PDMA) == UDMA_CH_FLAG_PDMA) ||
                    ((chHandleInt->chType & UDMA_CH_FLAG_PSIL) == UDMA_CH_FLAG_PSIL)) &&
               (TRUE == rxPrms->configDefaultFlow))
            {
                flowPrms.psInfoPresent = rxPrms->flowPsInfoPresent;
                flowPrms.einfoPresent  = rxPrms->flowEInfoPresent;
                flowPrms.errorHandling = rxPrms->flowErrorHandling;
                flowPrms.sopOffset     = rxPrms->flowSopOffset;
                retVal = CSL_lcdmaFlowCfg( &drvHandle->lcdmaRaRegs, chHandleInt->rxChNum, &flowPrms );
                if(UDMA_SOK != retVal)
                {
                    DebugP_logError("[UDMA] Default RX flow config failed!!!\r\n");
                }
            }

            if(UDMA_SOK == retVal)
            {
                /* Copy the config */
                (void) memcpy(&chHandleInt->rxPrms, rxPrms, sizeof(chHandleInt->rxPrms));
            }
        }
    }
    return (retVal);
}

int32_t Udma_chConfigPdma(Udma_ChHandle chHandle,
                          const Udma_ChPdmaPrms *pdmaPrms)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) ||
       (NULL == pdmaPrms) ||
       (chHandleInt->chInitDone != UDMA_INIT_DONE) ||
       ((chHandleInt->chType & UDMA_CH_FLAG_PDMA) != UDMA_CH_FLAG_PDMA))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            uint32_t        regVal;
            CSL_BcdmaCfg  *pBcCfg;
            pBcCfg = &drvHandle->bcdmaRegs;
            if(pBcCfg != NULL)
            {
                if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                    regVal = CSL_FMK(PSILCFG_REG_STATIC_TR_X, pdmaPrms->elemSize) |
                         CSL_FMK(PSILCFG_REG_STATIC_TR_Y, pdmaPrms->elemCnt) |
                         CSL_FMK(PSIL_REG_STATIC_TR_BURST, pdmaPrms->burst) |
                         CSL_FMK(PSIL_REG_STATIC_TR_ACC2, pdmaPrms->acc32);
                    retVal = CSL_bcdmaSet_TR_XY(pBcCfg, regVal, chHandleInt->txChNum);

                    regVal = CSL_FMK(PSILCFG_REG_STATIC_TR_Z, pdmaPrms->fifoCnt)|
                         CSL_FMK(PSIL_REG_STATIC_TR_EOL, pdmaPrms->eol);
                    retVal = CSL_bcdmaSet_TR_Z(pBcCfg, regVal, chHandleInt->txChNum);
                }
                else
                {
                    regVal = CSL_FMK(PSILCFG_REG_STATIC_TR_X, pdmaPrms->elemSize) |
                         CSL_FMK(PSILCFG_REG_STATIC_TR_Y, pdmaPrms->elemCnt) |
                         CSL_FMK(PSIL_REG_STATIC_TR_BURST, pdmaPrms->burst) |
                         CSL_FMK(PSIL_REG_STATIC_TR_ACC2, pdmaPrms->acc32);
                    retVal = CSL_bcdmaSet_TR_XY(pBcCfg, regVal, chHandleInt->rxChNum);

                    regVal = CSL_FMK(PSILCFG_REG_STATIC_TR_Z, pdmaPrms->fifoCnt)|
                         CSL_FMK(PSIL_REG_STATIC_TR_EOL, pdmaPrms->eol);
                    retVal = CSL_bcdmaSet_TR_Z(pBcCfg, regVal, chHandleInt->rxChNum);
                }
            } 
            else
            {
                retVal = UDMA_EFAIL;
            }
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            uint32_t        regVal;
            CSL_PktdmaCfg *pPktCfg;
            pPktCfg = &drvHandle->pktdmaRegs;
            if(pPktCfg != NULL)
            {
                if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                    regVal = CSL_FMK(PSILCFG_REG_STATIC_TR_X, pdmaPrms->elemSize) |
                         CSL_FMK(PSILCFG_REG_STATIC_TR_Y, pdmaPrms->elemCnt) |
                         CSL_FMK(PSIL_REG_STATIC_TR_BURST, pdmaPrms->burst) |
                         CSL_FMK(PSIL_REG_STATIC_TR_ACC2, pdmaPrms->acc32);
                    retVal = CSL_pktdmaSet_TR_XY(pPktCfg, regVal, chHandleInt->txChNum);

                    regVal = CSL_FMK(PSILCFG_REG_STATIC_TR_Z, pdmaPrms->fifoCnt)|
                         CSL_FMK(PSIL_REG_STATIC_TR_EOL, pdmaPrms->eol);
                    retVal = CSL_pktdmaSet_TR_Z(pPktCfg, regVal, chHandleInt->txChNum);
                }
                else
                {
                    regVal = CSL_FMK(PSILCFG_REG_STATIC_TR_X, pdmaPrms->elemSize) |
                         CSL_FMK(PSILCFG_REG_STATIC_TR_Y, pdmaPrms->elemCnt) |
                         CSL_FMK(PSIL_REG_STATIC_TR_BURST, pdmaPrms->burst) |
                         CSL_FMK(PSIL_REG_STATIC_TR_ACC2, pdmaPrms->acc32);
                    retVal = CSL_pktdmaSet_TR_XY(pPktCfg, regVal, chHandleInt->rxChNum);

                    regVal = CSL_FMK(PSILCFG_REG_STATIC_TR_Z, pdmaPrms->fifoCnt)|
                         CSL_FMK(PSIL_REG_STATIC_TR_EOL, pdmaPrms->eol);
                    retVal = CSL_pktdmaSet_TR_Z(pPktCfg, regVal, chHandleInt->rxChNum);
                }
            }
            else
            {
                retVal = UDMA_EFAIL;
            }
        }
        else
        {
          /* Do Nothing */
        }
#endif
    }

    return (retVal);
}

int32_t Udma_chEnable(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Enable channel based on channel type */
        Udma_chEnableLocal(chHandleInt);
    }

    return (retVal);
}

int32_t Udma_chDisable(Udma_ChHandle chHandle, uint32_t timeout)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Call disable sequence for respective modes */
        if((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
        {
            retVal = Udma_chDisableBlkCpyChan(chHandleInt, timeout);
        }
        else
        {
            if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
            {
                retVal = Udma_chDisableTxChan(chHandleInt, timeout);
            }
            else
            {
                retVal = Udma_chDisableRxChan(chHandleInt, timeout);
            }
        }
    }

    return (retVal);
}

int32_t Udma_chPause(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            if(chHandleInt->txChNum != UDMA_DMA_CH_INVALID)
            {
                Udma_chPauseTxLocal(drvHandle, chHandleInt->txChNum, chHandleInt->chType);
            }
        }

        if((chHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
        {
            /* Note: Block copy uses same RX channel. So do for both TX/RX */
            if ((UDMA_INST_TYPE_LCDMA_BCDMA                 == chHandleInt->drvHandle->instType) &&
                ((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY))
            {
                /* In case of BCDMA Block Copy, No need to do for RX */
            }
            else
            {
                if(chHandleInt->rxChNum != UDMA_DMA_CH_INVALID)
                {
                    Udma_chPauseRxLocal(drvHandle, chHandleInt->rxChNum);
                }
            }
        }
    }

    return (retVal);
}

int32_t Udma_chResume(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            if(chHandleInt->txChNum != UDMA_DMA_CH_INVALID)
            {
               Udma_chUnpauseTxLocal(drvHandle, chHandleInt->txChNum, chHandleInt->chType);
            }
        }
        if((chHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
        {
            /* Note: Block copy uses same RX channel. So do for both TX/RX */
            if ((UDMA_INST_TYPE_LCDMA_BCDMA                 == chHandleInt->drvHandle->instType) &&
                ((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY))
            {
                /* In case of BCDMA Block Copy, No need to do for RX */
            }
            else
            {
                if(chHandleInt->rxChNum != UDMA_DMA_CH_INVALID)
                {
                    Udma_chUnpauseRxLocal(drvHandle, chHandleInt->rxChNum);
                }
            }
        }
    }

    return (retVal);
}

uint32_t Udma_chGetNum(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t            chNum = UDMA_DMA_CH_INVALID;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            if(chHandleInt->txChNum != UDMA_DMA_CH_INVALID)
            {
               chNum = chHandleInt->txChNum;
            }
        }
        else
        {
            if(chHandleInt->rxChNum != UDMA_DMA_CH_INVALID)
            {
               chNum = chHandleInt->rxChNum;
            }
        }
    }

    return (chNum);
}

Udma_RingHandle Udma_chGetFqRingHandle(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_RingHandle     fqRing = (Udma_RingHandle) NULL;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        fqRing = (Udma_RingHandle) chHandleInt->fqRing;
    }

    return (fqRing);
}

Udma_RingHandle Udma_chGetCqRingHandle(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_RingHandle     cqRing = (Udma_RingHandle) NULL;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        cqRing = (Udma_RingHandle) chHandleInt->cqRing;
    }

    return (cqRing);
}

Udma_RingHandle Udma_chGetTdCqRingHandle(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_RingHandle     tdCqRing = (Udma_RingHandle) NULL;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        tdCqRing = (Udma_RingHandle) chHandleInt->tdCqRing;
    }

    return (tdCqRing);
}

uint16_t Udma_chGetFqRingNum(Udma_ChHandle chHandle)
{
    uint16_t            ringNum = UDMA_RING_INVALID;
    Udma_RingHandle     ringHandle;

    ringHandle = Udma_chGetFqRingHandle(chHandle);
    if(ringHandle != NULL)
    {
        ringNum = Udma_ringGetNum(ringHandle);
    }

    return (ringNum);
}

uint16_t Udma_chGetCqRingNum(Udma_ChHandle chHandle)
{
    uint16_t            ringNum = UDMA_RING_INVALID;
    Udma_RingHandle     ringHandle;

    ringHandle = Udma_chGetCqRingHandle(chHandle);
    if(ringHandle != NULL)
    {
        ringNum = Udma_ringGetNum(ringHandle);
    }

    return (ringNum);
}

Udma_FlowHandle Udma_chGetDefaultFlowHandle(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_FlowHandle     defaultFlow = (Udma_FlowHandle) NULL;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        defaultFlow = (Udma_FlowHandle) chHandleInt->defaultFlow;
    }

    return (defaultFlow);
}

void *Udma_chGetSwTriggerRegister(Udma_ChHandle chHandle)
{
    int32_t                 retVal = UDMA_SOK;
    Udma_DrvHandleInt       drvHandle;
    Udma_ChHandleInt        chHandleInt = (Udma_ChHandleInt) chHandle;
    void                   *pSwTriggerReg = NULL;
    /* Error check */
    if((NULL == chHandleInt) ||
       (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        if(((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY) ||
           ((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX))
        {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
            if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
            {
                if(chHandleInt->pBcdmaBcRtRegs != NULL)
                {
                    pSwTriggerReg = (void *) &chHandleInt->pBcdmaBcRtRegs->SWTRIG;
                }
                else
                {
                  /* Do Nothing */
                }
            }
            else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
            {
                DebugP_logError("[UDMA] SW trigger not supported for PKTDMA TX channels!!!\r\n");
            }
            else
            {
              /* Do Nothing */
            }
#endif
        }
        else if((chHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
        {
            DebugP_logError("[UDMA] SW trigger not supported for RX channels!!!\r\n");
        }
        else
        {
            /* Do Nothing*/
        }
    }

    return (pSwTriggerReg);
}

int32_t Udma_chSetSwTrigger(Udma_ChHandle chHandle, uint32_t trigger)
{
    int32_t                 retVal = UDMA_SOK;
    Udma_DrvHandleInt       drvHandle;
    Udma_ChHandleInt        chHandleInt = (Udma_ChHandleInt) chHandle;
    void                   *pSwTriggerReg = NULL;

    /* Error check */
    if((NULL == chHandleInt) ||
       (chHandleInt->chInitDone != UDMA_INIT_DONE) ||
       (trigger > CSL_UDMAP_TR_FLAGS_TRIGGER_LOCAL_EVENT) ||
       (trigger == CSL_UDMAP_TR_FLAGS_TRIGGER_NONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        pSwTriggerReg = Udma_chGetSwTriggerRegister(chHandleInt);
        if(pSwTriggerReg != NULL)
        {
            CSL_REG32_WR(pSwTriggerReg, ((uint32_t)1U << (trigger - 1U)));
        }
        else
        {
            retVal = UDMA_EFAIL;
        }
    }

    return (retVal);
}

int32_t Udma_chSetChaining(Udma_ChHandle triggerChHandle,
                           Udma_ChHandle chainedChHandle,
                           uint32_t trigger)
{
    int32_t                             retVal = UDMA_SOK;
    Udma_DrvHandleInt                   drvHandle;
    Udma_ChHandleInt                    triggerChHandleInt = (Udma_ChHandleInt) triggerChHandle;
    Udma_ChHandleInt                    chainedChHandleInt = (Udma_ChHandleInt) chainedChHandle;
    CSL_LcdmaRingaccCfg *pCfg;
    CSL_BcdmaCfg *pBcCfg;
    /* Error check */
    if((NULL == triggerChHandleInt) || (triggerChHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if((NULL == chainedChHandleInt) || (chainedChHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = triggerChHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        pCfg = &drvHandle->lcdmaRaRegs;
        pBcCfg = &drvHandle->bcdmaRegs;
        if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            retVal = UDMA_EFAIL;
            DebugP_logError("UDMA chaining not supported for PKTDMA instance!!!\r\n");
        }
        else if((triggerChHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
        {
            if(triggerChHandleInt->txChNum != UDMA_DMA_CH_INVALID)
            {
                /* Enable the interrupt */
                CSL_lcdmaSetInterrupt(pCfg, chainedChHandleInt->txChNum, UDMA_SET_TR_INT, true);
                /* Set Channel event*/
                retVal = CSL_bcdmaSetLocalTrig(pBcCfg, 1U, chainedChHandleInt->txChNum, triggerChHandleInt->txChNum, UDMA_TR_FLAGS_TRIGGER_LOCAL0);
            }
        }
        else if((triggerChHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
        {
            if(triggerChHandleInt->rxChNum != UDMA_DMA_CH_INVALID)
            {
                if((chainedChHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
                {
                    /* Enable the interrupt */
                    CSL_lcdmaSetInterrupt(pCfg, chainedChHandleInt->rxChNum, UDMA_SET_TR_INT, true);
                    /* Set Channel event*/
                    retVal = CSL_bcdmaSetLocalTrig(pBcCfg, 1U, chainedChHandleInt->rxChNum, triggerChHandleInt->rxChNum, UDMA_TR_FLAGS_TRIGGER_LOCAL0);
                }
                else
                {
                    /* Enable the interrupt */
                    CSL_lcdmaSetInterrupt(pCfg, chainedChHandleInt->txChNum, UDMA_SET_TR_INT, true);
                    /* Set Channel event*/
                    retVal = CSL_bcdmaSetLocalTrig(pBcCfg, 1U, chainedChHandleInt->txChNum, triggerChHandleInt->rxChNum, UDMA_TR_FLAGS_TRIGGER_LOCAL0);
                }
            }
        }
        else if((triggerChHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            if(triggerChHandleInt->txChNum != UDMA_DMA_CH_INVALID)
            {
                if((chainedChHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
                {
                    /* Enable the interrupt */
                    CSL_lcdmaSetInterrupt(pCfg, chainedChHandleInt->rxChNum, UDMA_SET_TR_INT, true);
                    /* Set Channel event*/
                    retVal = CSL_bcdmaSetLocalTrig(pBcCfg, 1U, chainedChHandleInt->rxChNum, triggerChHandleInt->txChNum, UDMA_TR_FLAGS_TRIGGER_LOCAL0);
                }
                else
                {
                    /* Enable the interrupt */
                    CSL_lcdmaSetInterrupt(pCfg, chainedChHandleInt->txChNum, UDMA_SET_TR_INT, true);
                    /* Set Channel event*/
                    retVal = CSL_bcdmaSetLocalTrig(pBcCfg, 1U, chainedChHandleInt->txChNum, triggerChHandleInt->txChNum, UDMA_TR_FLAGS_TRIGGER_LOCAL0);
                }
            }
        }     
        else
        {
            retVal = UDMA_EFAIL;
            DebugP_logError("[UDMA] Chaining not supported for other channels!!\r\n");
        }
    }

    if(UDMA_SOK == retVal)
    {
        triggerChHandleInt->trigger        = trigger;
    }

    return (retVal);
}

int32_t Udma_chBreakChaining(Udma_ChHandle triggerChHandle,
                             Udma_ChHandle chainedChHandle)
{
    int32_t                             retVal = UDMA_SOK;
    Udma_DrvHandleInt                   drvHandle;
    Udma_ChHandleInt                    triggerChHandleInt = (Udma_ChHandleInt) triggerChHandle;
    Udma_ChHandleInt                    chainedChHandleInt = (Udma_ChHandleInt) chainedChHandle;

    /* Error check */
    if((NULL == triggerChHandleInt) || (triggerChHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if((NULL == chainedChHandleInt) || (chainedChHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = triggerChHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    return (retVal);
}

void UdmaChPrms_init(Udma_ChPrms *chPrms, uint32_t chType)
{
    if(NULL != chPrms)
    {
        chPrms->chNum       = UDMA_DMA_CH_ANY;
        chPrms->peerChNum   = UDMA_DMA_CH_INVALID;
        if((UDMA_CH_TYPE_TR_BLK_COPY == chType))
        {
            chPrms->peerChNum   = UDMA_DMA_CH_NA;
        }
        chPrms->mappedChGrp = UDMA_MAPPED_GROUP_INVALID;
        chPrms->appData     = NULL;
        UdmaRingPrms_init(&chPrms->fqRingPrms);
        UdmaRingPrms_init(&chPrms->cqRingPrms);
        UdmaRingPrms_init(&chPrms->tdCqRingPrms);
        /* TD and TR response is always 8 byte irrespective of mode */
        chPrms->tdCqRingPrms.elemSize = UDMA_RING_ES_8BYTES;
    }

    return;
}

void UdmaChTxPrms_init(Udma_ChTxPrms *txPrms, uint32_t chType)
{
    if(NULL != txPrms)
    {
        txPrms->pauseOnError    = FALSE;
        txPrms->chanType        = CSL_BCDMA_CHAN_TYPE_REF_PKT_RING;
        if((chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
        {
            txPrms->chanType    = CSL_BCDMA_CHAN_TYPE_COPY_REF_TR_RING;
        }
        txPrms->busPriority     = UDMA_DEFAULT_TX_CH_BUS_PRIORITY;
        txPrms->busOrderId      = UDMA_DEFAULT_TX_CH_BUS_ORDERID;
        txPrms->dmaPriority     = UDMA_DEFAULT_TX_CH_DMA_PRIORITY;
        if((chType & UDMA_CH_FLAG_UHC) == UDMA_CH_FLAG_UHC)
        {
            txPrms->fifoDepth   = (uint16_t)UDMA_TX_UHC_CHANS_FDEPTH;
            txPrms->burstSize   = CSL_BCDMA_CHAN_BURST_SIZE_256_BYTES;
        }
        else if((chType & UDMA_CH_FLAG_HC) == UDMA_CH_FLAG_HC)
        {
            txPrms->fifoDepth   = (uint16_t)UDMA_TX_HC_CHANS_FDEPTH;
            txPrms->burstSize   = CSL_BCDMA_CHAN_BURST_SIZE_256_BYTES;
        }
        else
        {
            txPrms->fifoDepth   = (uint16_t)UDMA_TX_CHANS_FDEPTH;
            txPrms->burstSize   = CSL_BCDMA_CHAN_BURST_SIZE_64_BYTES;
        }
        txPrms->supressTdCqPkt  = FALSE;
        txPrms->tdType = FALSE;
    }
    return;
}

void UdmaChRxPrms_init(Udma_ChRxPrms *rxPrms, uint32_t chType)
{
    if(NULL != rxPrms)
    {
        rxPrms->pauseOnError        = FALSE;
        rxPrms->addrType            = CSL_BCDMA_ADDR_TYPE_PHYS;
        rxPrms->chanType            = CSL_BCDMA_CHAN_TYPE_REF_PKT_RING;
        if((chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
        {
            rxPrms->chanType        = CSL_BCDMA_CHAN_TYPE_COPY_REF_TR_RING;
        }
        rxPrms->fetchWordSize       = 16U;  /* sizeof(CSL_UdmapTR15) / sizeof(uint32_t) */
        rxPrms->busPriority         = UDMA_DEFAULT_RX_CH_BUS_PRIORITY;
        rxPrms->busQos              = UDMA_DEFAULT_RX_CH_BUS_QOS;
        rxPrms->busOrderId          = UDMA_DEFAULT_RX_CH_BUS_ORDERID;
        rxPrms->dmaPriority         = UDMA_DEFAULT_RX_CH_DMA_PRIORITY;
        rxPrms->flowIdFwRangeStart  = 0U;       /* Reset value - to use default flow */
        rxPrms->flowIdFwRangeCnt    = 0U;       /* Reset value - to use default flow */
        rxPrms->flowEInfoPresent    = FALSE;       /* Default no EINFO */
        rxPrms->flowPsInfoPresent   = FALSE;      /* Default no PSINFO */
        rxPrms->flowErrorHandling   = TRUE;       /* Default Re-try descriptor allocation operation on starvation error */
        rxPrms->flowSopOffset       = 0U;      /* Default SOP offset is 0 */
        rxPrms->ignoreLongPkts      = FALSE;
        rxPrms->configDefaultFlow   = TRUE;
        if((chType & UDMA_CH_FLAG_UHC) == UDMA_CH_FLAG_UHC)
        {
            rxPrms->burstSize   = CSL_BCDMA_CHAN_BURST_SIZE_256_BYTES;
        }
        else if((chType & UDMA_CH_FLAG_HC) == UDMA_CH_FLAG_HC)
        {
            rxPrms->burstSize   = CSL_BCDMA_CHAN_BURST_SIZE_256_BYTES;
        }
        else
        {
            rxPrms->burstSize   = CSL_BCDMA_CHAN_BURST_SIZE_64_BYTES;
        }
    }

    return;
}

void UdmaChPdmaPrms_init(Udma_ChPdmaPrms *pdmaPrms)
{
    if(NULL != pdmaPrms)
    {
        pdmaPrms->elemSize  = UDMA_PDMA_ES_8BITS;
        pdmaPrms->elemCnt   = 0U;
        pdmaPrms->fifoCnt   = 0U;
        pdmaPrms->burst     = 0U;
        pdmaPrms->acc32     = 0U;
        pdmaPrms->eol       = 0U;
    }

    return;
}

int32_t Udma_chGetStats(Udma_ChHandle chHandle, Udma_ChStats *chStats)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;
    uint32_t            chNum;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    CSL_BcdmaChanStats  bcdmaChanStats = {0};
    CSL_BcdmaChanDir    bcdmaChDir;
    CSL_PktdmaChanStats pktdmaChanStats = {0};
    CSL_PktdmaChanDir   pktdmaChDir;
#endif

    /* Error check */
    if ((NULL == chHandleInt)                   ||
        (chHandleInt->chInitDone != UDMA_INIT_DONE) ||
        (chStats == NULL))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            if((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
            {
                chNum       = chHandleInt->txChNum;
                bcdmaChDir = CSL_BCDMA_CHAN_DIR_TX;
            }
            else
            {
                if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                    /* Add offset to chNum, so that BCDMA can identify it as Tx channel*/
                    chNum       = chHandleInt->txChNum;
                    bcdmaChDir = CSL_BCDMA_CHAN_DIR_TX;
                }
                else
                {
                    /* Add offset to chNum, so that BCDMA can identify it as Rx channel*/
                    chNum       = chHandleInt->rxChNum;
                    bcdmaChDir = CSL_BCDMA_CHAN_DIR_RX;
                }
            }
            CSL_bcdmaGetChanStats(&drvHandle->bcdmaRegs, chNum, bcdmaChDir, &bcdmaChanStats);
            chStats->packetCnt = bcdmaChanStats.packetCnt;
            chStats->completedByteCnt = bcdmaChanStats.completedByteCnt;
            chStats->startedByteCnt = bcdmaChanStats.startedByteCnt;
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            if((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
            {
                chNum       = chHandleInt->txChNum;
                pktdmaChDir = CSL_PKTDMA_CHAN_DIR_TX;
            }
            else
            {
                if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                    chNum       = chHandleInt->txChNum;
                    pktdmaChDir = CSL_PKTDMA_CHAN_DIR_TX;
                }
                else
                {
                    chNum       = chHandleInt->rxChNum;
                    pktdmaChDir = CSL_PKTDMA_CHAN_DIR_RX;
                }
            }
            CSL_pktdmaGetChanStats(&drvHandle->pktdmaRegs, chNum, pktdmaChDir, &pktdmaChanStats);
            chStats->packetCnt = pktdmaChanStats.packetCnt;
            chStats->completedByteCnt = pktdmaChanStats.completedByteCnt;
            chStats->startedByteCnt = pktdmaChanStats.startedByteCnt;
        }
        else
        {
          /* Do Nothing */
        }
#endif
    }

    return (retVal);
}

static int32_t Udma_chCheckParams(Udma_DrvHandleInt drvHandle,
                                  uint32_t chType,
                                  const Udma_ChPrms *chPrms)
{
    int32_t     retVal = UDMA_SOK;

    if((chType & UDMA_CH_FLAG_PDMA) == UDMA_CH_FLAG_PDMA)
    {
        if((UDMA_DMA_CH_INVALID == chPrms->peerChNum) ||
           (UDMA_DMA_CH_NA == chPrms->peerChNum))
        {
            retVal = UDMA_EINVALID_PARAMS;
            DebugP_logError("[UDMA] Invalid Peer Channel Number!!!\r\n");
        }
    }
    if((chType & UDMA_CH_FLAG_MAPPED) == UDMA_CH_FLAG_MAPPED)
    {
        if(UDMA_MAPPED_GROUP_INVALID == chPrms->mappedChGrp)
        {
            retVal = UDMA_EINVALID_PARAMS;
            DebugP_logError("[UDMA] Invalid Mapped Channel Group!!!\r\n");
        }
#if ((UDMA_NUM_MAPPED_TX_GROUP + UDMA_NUM_MAPPED_RX_GROUP) > 0)
        if((chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            if(chPrms->mappedChGrp >= UDMA_NUM_MAPPED_TX_GROUP)
            {
                retVal = UDMA_EINVALID_PARAMS;
                DebugP_logError("[UDMA] Incorrect TX Mapped Channel Group!!!\r\n");
            }
        }
        if((chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
        {
            /* Since RX mapped group index follows TX,
             * also check whether the group index is less than no.of tx groups
             * when channel type is RX */
            if((chPrms->mappedChGrp < UDMA_NUM_MAPPED_TX_GROUP) ||
               (chPrms->mappedChGrp >= (UDMA_NUM_MAPPED_TX_GROUP + UDMA_NUM_MAPPED_RX_GROUP)))
            {
                retVal = UDMA_EINVALID_PARAMS;
                DebugP_logError("[UDMA] Incorrect RX Mapped Channel Group!!!\r\n");
            }
        }
#endif
    }

    return (retVal);
}

static int32_t Udma_chAllocResource(Udma_ChHandleInt chHandle)
{
    int32_t                 retVal = UDMA_SOK, tempRetVal;
    Udma_DrvHandleInt       drvHandle;
    uint16_t                ringNum = UDMA_RING_INVALID;

    drvHandle = chHandle->drvHandle;
    /* Allocate UDMAP channel */
    if((chHandle->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
    {
        if((chHandle->chType & UDMA_CH_FLAG_HC) == UDMA_CH_FLAG_HC)
        {
            chHandle->txChNum =
                Udma_rmAllocBlkCopyHcCh(chHandle->chPrms.chNum, drvHandle);
        }
        else if((chHandle->chType & UDMA_CH_FLAG_UHC) == UDMA_CH_FLAG_UHC)
        {
            chHandle->txChNum =
                Udma_rmAllocBlkCopyUhcCh(chHandle->chPrms.chNum, drvHandle);
        }
        else
        {
            chHandle->txChNum =
                Udma_rmAllocBlkCopyCh(chHandle->chPrms.chNum, drvHandle);
            (void) Udma_getChAttr(chHandle->chPrms.peerChNum, &chHandle->chAttr, chHandle->txChNum);
        }
        if(UDMA_DMA_CH_INVALID == chHandle->txChNum)
        {
            retVal = UDMA_EALLOC;
            DebugP_logError("[UDMA] RM Alloc Blkcpy Ch failed!!!\r\n");
        }
        else
        {
            if (UDMA_INST_TYPE_LCDMA_BCDMA == chHandle->drvHandle->instType)
            {
                /* For BCDMA Block Copy, rxChNum is not used.*/
                chHandle->rxChNum     = UDMA_DMA_CH_INVALID;
                /* For BCDMA Block Copy, PeerThreadID is not applicable (no pairing required). */
                chHandle->peerThreadId = UDMA_THREAD_ID_INVALID;
            }
            else
            {
                /* RX channel same as TX channel for block copy */
                chHandle->rxChNum = chHandle->txChNum;
                /* Add thread offset and or RX relative channel as the thread
                 * already has bit info (CSL_PSILCFG_DEST_THREAD_OFFSET)
                 * for destination thread */
                chHandle->peerThreadId =
                    chHandle->rxChNum + drvHandle->udmapDestThreadOffset;
            }

        }
    }
    else
    {
        /* Allocate UDMAP for PDMA channels */
        if((chHandle->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            if((chHandle->chType & UDMA_CH_FLAG_HC) == UDMA_CH_FLAG_HC)
            {
                chHandle->txChNum =
                    Udma_rmAllocTxHcCh(chHandle->chPrms.chNum, drvHandle);
            }
            else if((chHandle->chType & UDMA_CH_FLAG_UHC) == UDMA_CH_FLAG_UHC)
            {
                chHandle->txChNum =
                    Udma_rmAllocTxUhcCh(chHandle->chPrms.chNum, drvHandle);
            }
            else
            {
                (void) Udma_getChAttr(chHandle->chPrms.peerChNum, &chHandle->chAttr, chHandle->chPrms.chNum);
                chHandle->txChNum =
                    Udma_rmAllocCh(chHandle->chAttr.ChNum, drvHandle);
            }
            if(UDMA_DMA_CH_INVALID == chHandle->txChNum)
            {
                retVal = UDMA_EALLOC;
                DebugP_logError("[UDMA] RM Alloc TX Ch failed!!!\r\n");
            }
        }
        else
        {
            if((chHandle->chType & UDMA_CH_FLAG_HC) == UDMA_CH_FLAG_HC)
            {
                chHandle->rxChNum =
                    Udma_rmAllocRxHcCh(chHandle->chPrms.chNum, drvHandle);
            }
            else if((chHandle->chType & UDMA_CH_FLAG_UHC) == UDMA_CH_FLAG_UHC)
            {
                chHandle->rxChNum =
                    Udma_rmAllocRxUhcCh(chHandle->chPrms.chNum, drvHandle);
            }
            else
            {
                (void) Udma_getChAttr(chHandle->chPrms.peerChNum, &chHandle->chAttr, chHandle->chPrms.chNum);
                chHandle->rxChNum =
                    Udma_rmAllocCh(chHandle->chAttr.ChNum, drvHandle);
            }
            if(UDMA_DMA_CH_INVALID == chHandle->rxChNum)
            {
                retVal = UDMA_EALLOC;
                DebugP_logError("[UDMA] RM Alloc RX Ch failed!!!\r\n");
            }
            else
            {
                /* Assign default flow */
                chHandle->defaultFlow               = &chHandle->defaultFlowObj;
                chHandle->defaultFlow->drvHandle    = drvHandle;
                chHandle->defaultFlow->flowStart    = chHandle->rxChNum;
                chHandle->defaultFlow->flowCnt      = 1U;
                chHandle->defaultFlow->flowInitDone = UDMA_INIT_DONE;
            }
        }

        if(UDMA_SOK == retVal)
        {
            /* Allocate peer channel for PDMA channels */
            if((chHandle->chType & UDMA_CH_FLAG_PDMA) == UDMA_CH_FLAG_PDMA)
            {
                /* PDMA peer channel assignment */
                chHandle->pdmaChNum = chHandle->chPrms.peerChNum;
                /* Thread ID already added while getting PDMA channel num */
                chHandle->peerThreadId = chHandle->pdmaChNum;
            }

            if((chHandle->chType & UDMA_CH_FLAG_PSIL) == UDMA_CH_FLAG_PSIL)
            {
                chHandle->peerThreadId = chHandle->chPrms.peerChNum;
            }
        }
    }
    
    if(UDMA_SOK == retVal)
    {
        /* Free queue ring number is same as UDMAP channel number */
        if(NULL != chHandle->chPrms.fqRingPrms.ringMem)
        {
            /* Allocate only when memory is provided */
            if((chHandle->chType & UDMA_CH_FLAG_BLK_COPY) ==
                UDMA_CH_FLAG_BLK_COPY)
            {
                /* Same as TX channel incase of block copy */
                ringNum = (uint16_t)chHandle->txChNum;
            }
            else
            {
                if((chHandle->chType & UDMA_CH_FLAG_MAPPED) == UDMA_CH_FLAG_MAPPED)
                {
#if ((UDMA_NUM_MAPPED_TX_GROUP + UDMA_NUM_MAPPED_RX_GROUP) > 0)
                    if((chHandle->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                    {
                        chHandle->chPrms.fqRingPrms.mappedChNum    = chHandle->txChNum;
                        /* Get default ringNum for the mapped TX channel */
                        ringNum = (uint16_t)(chHandle->txChNum + chHandle->chAttr.flowIdx);
                    }
                    else
                    {
                        chHandle->chPrms.fqRingPrms.mappedChNum    = chHandle->rxChNum;
                        /* Get default ringNum for the mapped RX channel */
                        ringNum = (uint16_t)(chHandle->rxChNum + chHandle->chAttr.flowIdx);
                    }
#endif
                }
                else if((chHandle->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                    /* For UDMAP, txChOffset is 0 */
                    ringNum = chHandle->txChNum;
                }
                else
                {
                    ringNum = chHandle->rxChNum;
                }
            }
            if( UDMA_CH_FLAG_UTC != (chHandle->chType & UDMA_CH_FLAG_UTC))
            {
                chHandle->fqRing = &chHandle->fqRingObj;
                retVal = Udma_ringAlloc(
                            drvHandle,
                            chHandle->fqRing,
                            ringNum,
                            &chHandle->chPrms.fqRingPrms);
                if(UDMA_SOK != retVal)
                {
                    chHandle->fqRing = (Udma_RingHandleInt) NULL;
                    DebugP_logError("[UDMA] FQ ring alloc failed!!!\r\n");
                }
                else if(((chHandle->chType & UDMA_CH_FLAG_MAPPED) == UDMA_CH_FLAG_MAPPED) &&
                        ((chHandle->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX))
                {
                    /* Assign the default flow start id as the allocated default ring num(without offset) for mapped RX channels.
                    * This is because the default flow start idx is not equal to rxChNum,
                    * since there may be 1 to many mapping between RX Channels and dedicated flows */
                    chHandle->defaultFlow->flowStart    = chHandle->fqRing->ringNum;
                }
                else
                {
                /* Do Nothing */
                }
            }
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* In devices like AM64x, there is no seperate completion queue. */
        chHandle->cqRing = &chHandle->fqRingObj;
    }

    if(UDMA_SOK == retVal)
    {
        /* In devices like AM64x, teardown is not supported.*/
        chHandle->tdCqRing = (Udma_RingHandleInt) NULL;
    }

    if(UDMA_SOK != retVal)
    {
        tempRetVal = Udma_chFreeResource(chHandle);
        if(UDMA_SOK != tempRetVal)
        {
            DebugP_logError("[UDMA] Free resource failed!!!\r\n");
        }
    }
    else
    {
        /* Assign overlay pointers */
        Udma_chAssignRegOverlay(drvHandle, chHandle);
    }

    return (retVal);
}

static int32_t Udma_chFreeResource(Udma_ChHandleInt chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;

    drvHandle = chHandle->drvHandle;
    if((chHandle->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
    {
        if(UDMA_DMA_CH_INVALID != chHandle->txChNum)
        {
            /* TX channel free */
            if((chHandle->chType & UDMA_CH_FLAG_HC) == UDMA_CH_FLAG_HC)
            {
                Udma_rmFreeBlkCopyHcCh(chHandle->txChNum, drvHandle);
            }
            else if((chHandle->chType & UDMA_CH_FLAG_UHC) == UDMA_CH_FLAG_UHC)
            {
                Udma_rmFreeBlkCopyUhcCh(chHandle->txChNum, drvHandle);
            }
            else
            {
                Udma_rmFreeBlkCopyCh(chHandle->txChNum, drvHandle);
            }
            chHandle->txChNum = UDMA_DMA_CH_INVALID;
            chHandle->rxChNum = UDMA_DMA_CH_INVALID;
        }
    }
    else
    {
        if(UDMA_DMA_CH_INVALID != chHandle->txChNum)
        {
            /* TX channel free */
            if((chHandle->chType & UDMA_CH_FLAG_HC) == UDMA_CH_FLAG_HC)
            {
                Udma_rmFreeTxHcCh(chHandle->txChNum, drvHandle);
            }
            else if((chHandle->chType & UDMA_CH_FLAG_UHC) == UDMA_CH_FLAG_UHC)
            {
                Udma_rmFreeTxUhcCh(chHandle->txChNum, drvHandle);
            }
            else
            {
                Udma_rmFreeCh(chHandle->txChNum, drvHandle);
            }
            chHandle->txChNum = UDMA_DMA_CH_INVALID;
        }
        if(UDMA_DMA_CH_INVALID != chHandle->rxChNum)
        {
            /* RX channel free */
            if((chHandle->chType & UDMA_CH_FLAG_HC) == UDMA_CH_FLAG_HC)
            {
                Udma_rmFreeRxHcCh(chHandle->rxChNum, drvHandle);
            }
            else if((chHandle->chType & UDMA_CH_FLAG_UHC) == UDMA_CH_FLAG_UHC)
            {
                Udma_rmFreeRxUhcCh(chHandle->rxChNum, drvHandle);
            }
            else
            {
                Udma_rmFreeCh(chHandle->rxChNum, drvHandle);
            }
            chHandle->rxChNum = UDMA_DMA_CH_INVALID;
        }

        chHandle->defaultFlowObj.drvHandle    = (Udma_DrvHandleInt) NULL;
        chHandle->defaultFlowObj.flowStart    = UDMA_FLOW_INVALID;
        chHandle->defaultFlowObj.flowCnt      = 0U;
        chHandle->defaultFlowObj.flowInitDone = UDMA_DEINIT_DONE;
        chHandle->defaultFlow                 = (Udma_FlowHandleInt) NULL;
    }
    chHandle->pdmaChNum = UDMA_DMA_CH_INVALID;
    chHandle->peerThreadId = UDMA_THREAD_ID_INVALID;

    if(NULL != chHandle->fqRing)
    {
        retVal += Udma_ringFree(chHandle->fqRing);
        if(UDMA_SOK != retVal)
        {
            DebugP_logError("[UDMA] RM Free FQ ring failed!!!\r\n");
        }
        chHandle->fqRing = (Udma_RingHandleInt) NULL;
    }
    if(NULL != chHandle->cqRing)
    {
        chHandle->cqRing = (Udma_RingHandleInt) NULL;
    }
    if(NULL != chHandle->tdCqRing)
    {
        retVal += Udma_ringFree(chHandle->tdCqRing);
        if(UDMA_SOK != retVal)
        {
            DebugP_logError("[UDMA] RM Free TDCQ ring failed!!!\r\n");
        }
        chHandle->tdCqRing = (Udma_RingHandleInt) NULL;
    }

    return (retVal);
}

static int32_t Udma_chPair(Udma_ChHandleInt chHandle)
{
    int32_t                 retVal = UDMA_SOK;
    Udma_DrvHandleInt       drvHandle;
    uint32_t chNum;
    uint64_t curTime;

    drvHandle = chHandle->drvHandle;

    if((UDMA_INST_TYPE_LCDMA_BCDMA                 == drvHandle->instType) &&
       ((chHandle->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY))
    {
        /* For BCDMA Block Copy, pairing not required.*/
    }
    else
    {
        if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            if(((chHandle->chType & UDMA_CH_TYPE_PDMA_TX) == UDMA_CH_TYPE_PDMA_TX) || 
               (((chHandle->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)))
            {
               chNum = chHandle->txChNum;
            }
            else
            {
               chNum = chHandle->rxChNum;
            }
            
            CSL_pktdmaSetChanAutoPair( &drvHandle->pktdmaRegs, chNum, 1);
            
            curTime = ClockP_getTimeUsec();

            /* Check if pairing the channel is complete with timeout. */
            while(((ClockP_getTimeUsec() - curTime) < UDMA_SOC_MAX_TIMEOUT))
            {
                retVal = CSL_pktdmaIsPairComp(&drvHandle->pktdmaRegs, chNum);
                if(retVal == UDMA_SOK)
                {
                    break;
                }
            }
        }
        else
        {
            if((chHandle->chType & UDMA_CH_TYPE_PDMA_TX) == UDMA_CH_TYPE_PDMA_TX)
            {
               chNum = chHandle->txChNum;
            }
            else
            {
               chNum = chHandle->rxChNum;
            }

            CSL_bcdmaSetChanAutoPair( &drvHandle->bcdmaRegs, chNum, 1);

            curTime = ClockP_getTimeUsec();

            /* Check if pairing the channel is complete with timeout. */
            while(((ClockP_getTimeUsec() - curTime) < UDMA_SOC_MAX_TIMEOUT))
            {
                retVal = CSL_bcdmaIsPairComp(&drvHandle->bcdmaRegs, chNum);
                if(retVal == UDMA_SOK)
                {
                    break;
                }
            }
        }
    }

    return (retVal);
}

static int32_t Udma_chUnpair(Udma_ChHandleInt chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    uint32_t chanIdx;
    drvHandle = chHandle->drvHandle;

    if((UDMA_INST_TYPE_LCDMA_BCDMA                 == drvHandle->instType) &&
    ((chHandle->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY))
    {
        /* For BCDMA Block Copy, un-pairing / thread disbale not required.*/
    }
    else
    {
        if((chHandle->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            if(chHandle->txChNum != UDMA_DMA_CH_INVALID)
            {
               /* For TX, UDMAP channel is source */
               chanIdx = chHandle->txChNum;
            }
            else
            {
                retVal = UDMA_EINVALID_PARAMS;
            }
        }
        else    /* RX channel */
        {
            if(chHandle->rxChNum != UDMA_DMA_CH_INVALID)
            {
               /* For TX, UDMAP channel is source */
               chanIdx = chHandle->rxChNum;
            }
            else
            {
                retVal = UDMA_EINVALID_PARAMS;
            }
        }
        if(retVal == UDMA_SOK)
        {
            if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
            {
              CSL_pktdmaSetChanAutoPair( &drvHandle->pktdmaRegs, chanIdx, 0);
            }
            else
            {
              CSL_bcdmaSetChanAutoPair( &drvHandle->bcdmaRegs, chanIdx, 0);
            }
        }
    }

    return (retVal);
}

static void Udma_chEnableLocal(Udma_ChHandleInt chHandle)
{
    Udma_DrvHandleInt       drvHandle;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    CSL_BcdmaRT             bcdmaRtEnable;
    CSL_PktdmaRT            pktdmaRtEnable;
#endif

    drvHandle = chHandle->drvHandle;

#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
    {
       /* Set only enable and clear all other flags which might be set from
        * previous run */
        bcdmaRtEnable.enable         = TRUE;
        bcdmaRtEnable.teardown       = FALSE;
        bcdmaRtEnable.forcedTeardown = FALSE;
        bcdmaRtEnable.pause          = FALSE;
        bcdmaRtEnable.error          = FALSE;

        if((chHandle->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY )
        {
            if(chHandle->txChNum != UDMA_DMA_CH_INVALID)
            {
                (void) CSL_bcdmaSetRT(&drvHandle->bcdmaRegs, chHandle->txChNum , &bcdmaRtEnable);
            }
        }

        else if((chHandle->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            if(chHandle->txChNum != UDMA_DMA_CH_INVALID)
            {
                (void) CSL_bcdmaSetRT(&drvHandle->bcdmaRegs, chHandle->txChNum , &bcdmaRtEnable);
            }
        }

        else if ((chHandle->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
        {
            if(chHandle->rxChNum != UDMA_DMA_CH_INVALID)
            {
                (void) CSL_bcdmaSetRT(&drvHandle->bcdmaRegs, chHandle->rxChNum , &bcdmaRtEnable);
            }
        }
        else
        {
          /* Do Nothing */
        }
    }
    else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
    {
       /* Set only enable and clear all other flags which might be set from
        * previous run */
        pktdmaRtEnable.enable         = TRUE;
        pktdmaRtEnable.teardown       = FALSE;
        pktdmaRtEnable.forcedTeardown = FALSE;
        pktdmaRtEnable.pause          = FALSE;
        pktdmaRtEnable.error          = FALSE;

        if((chHandle->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
        {
            if(chHandle->txChNum != UDMA_DMA_CH_INVALID)
            { 
               (void) CSL_pktdmaSetRT(&drvHandle->pktdmaRegs, chHandle->txChNum, &pktdmaRtEnable);
            }
        }

        if((chHandle->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
        {
            if(chHandle->rxChNum != UDMA_DMA_CH_INVALID)
            { 
               (void) CSL_pktdmaSetRT(&drvHandle->pktdmaRegs, chHandle->rxChNum, &pktdmaRtEnable);
            }
        }
        else
        {
          /* Do Nothing */
        }

    }
    else
    {
      /* Do Nothing */
    }
#endif
    return;
}

static int32_t Udma_chDisableBlkCpyChan(Udma_ChHandleInt chHandle, uint32_t timeout)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t            currTimeout = 0U;
    Udma_DrvHandleInt   drvHandle;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    CSL_BcdmaRT         bcdmaRtStatus;
    CSL_PktdmaRT        pktdmaRtStatus;
#endif

    drvHandle = chHandle->drvHandle;
    if(chHandle->txChNum != UDMA_DMA_CH_INVALID)
    {
    /* Initiate graceful teardown first - Source is udma thread for TX */
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
       if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
       {
           retVal = CSL_bcdmaTeardownChan(
                 &drvHandle->bcdmaRegs, chHandle->txChNum, (bool)false, (bool)false);
       }
       else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
       {
           retVal = CSL_pktdmaTeardownChannel(
                 &drvHandle->pktdmaRegs, chHandle->txChNum, (bool)false, (bool)false, CSL_PKTDMA_CHAN_DIR_TX);
       }
       else
       {
           /* Do Nothing */
       }
#endif
    }
    else
    {
       retVal = UDMA_EINVALID_PARAMS;
    }
    
    if(CSL_PASS != retVal)
    {
        DebugP_logError("[UDMA] Blkcpy teardown failed!!\r\n");
    }

    /* Check if graceful teardown is complete */
    while(UDMA_SOK == retVal)
    {
      bool end_loop = false;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            (void) CSL_bcdmaGetRT(&drvHandle->bcdmaRegs, chHandle->txChNum, &bcdmaRtStatus);
            if(FALSE == bcdmaRtStatus.enable)
            {
                /* Teardown complete */
                end_loop = true;
            }
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            (void) CSL_pktdmaGetRT(&drvHandle->pktdmaRegs, chHandle->txChNum, &pktdmaRtStatus);
            if(FALSE == pktdmaRtStatus.enable)
            {
                /* Teardown complete */
                end_loop = true;
            }
            else
            {
              /* Do Nothing */
            }
        }
        else
        {
          /* Do Nothing */
        }
        if (end_loop)
        {
          break;
        }
#endif
        if(currTimeout > timeout)
        {
            retVal = UDMA_ETIMEOUT;
        }
        else
        {
            (void) ClockP_usleep(1000U);
            currTimeout++;
        }
    }

    if(UDMA_SOK != retVal)
    {
        /* Graceful teardown failed - initiate force teardown */
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            retVal = CSL_bcdmaTeardownChan(
                        &drvHandle->bcdmaRegs, chHandle->txChNum, (bool)true, (bool)false);
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            retVal = CSL_pktdmaTeardownChannel(
                        &drvHandle->pktdmaRegs, chHandle->txChNum, (bool)true, (bool)false, CSL_PKTDMA_CHAN_DIR_TX);
        }
        else
        {
          /* Do Nothing */
        }
#endif

        if(CSL_PASS != retVal)
        {
            DebugP_logError("[UDMA] Blkcpy force disable failed!!\r\n");
        }

        /* Wait for disable to complete */
        currTimeout = 0U;
        while(UDMA_SOK == retVal)
        {
          bool end_loop = false;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
            if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
            {
                (void) CSL_bcdmaGetRT(&drvHandle->bcdmaRegs, chHandle->txChNum, &bcdmaRtStatus);
                if(FALSE == bcdmaRtStatus.enable)
                {
                    /* Teardown complete */
                    end_loop = true;
                }
            }
            else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
            {
                (void) CSL_pktdmaGetRT(&drvHandle->pktdmaRegs, chHandle->txChNum, &pktdmaRtStatus);
                if(FALSE == pktdmaRtStatus.enable)
                {
                    /* Teardown complete */
                    end_loop = true;
                }
            }
            else
            {
              /* Do Nothing */
            }
            if (end_loop)
            {
              break;
            }
#endif

            if(currTimeout > timeout)
            {
                retVal = UDMA_ETIMEOUT;
                DebugP_logError("[UDMA] Blockcpy ch teardown timed out!!!\r\n");
            }
            else
            {
                (void) ClockP_usleep(1000U);
                currTimeout++;
            }
        }
    }

    if(UDMA_SOK == retVal)
    {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            /* Clear teardown and enable bits in UDMAP */
            bcdmaRtStatus.enable   = FALSE;
            bcdmaRtStatus.teardown = FALSE;
            bcdmaRtStatus.forcedTeardown = FALSE;
            (void) CSL_bcdmaSetRT(&drvHandle->bcdmaRegs, chHandle->txChNum, &bcdmaRtStatus);
        }
        else
        {
          /* Do Nothing */
        }
#endif

    }

    return (retVal);
}

static int32_t Udma_chDisableTxChan(Udma_ChHandleInt chHandle, uint32_t timeout)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t            currTimeout = 0U;
    Udma_DrvHandleInt   drvHandle;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    CSL_BcdmaRT         bcdmaRtStatus;
    CSL_PktdmaRT        pktdmaRtStatus;
#endif

    drvHandle = chHandle->drvHandle;
    if(chHandle->txChNum != UDMA_DMA_CH_INVALID)
    {
    /* Initiate graceful teardown first - Source is udma thread for TX */
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
       if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
       {
           /*Add offset to chNum, so that BCDMA can identify it as Tx Channel*/
           retVal = CSL_bcdmaTeardownChan(
                 &drvHandle->bcdmaRegs, chHandle->txChNum, (bool)false, (bool)false);
       }
       else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
       {
           retVal = CSL_pktdmaTeardownChannel(
                 &drvHandle->pktdmaRegs, chHandle->txChNum, (bool)false, (bool)false, CSL_PKTDMA_CHAN_DIR_TX);
       }
       else
       {
          /* Do Nothing */
       }
#endif
    }
    else
    {
       retVal = UDMA_EINVALID_PARAMS;
    }

    if(CSL_PASS != retVal)
    {
        DebugP_logError("[UDMA] TX teardown failed!!\r\n");
    }

    /* Check if graceful teardown is complete */
    while(UDMA_SOK == retVal)
    {
      bool end_loop = false;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            /*Add offset to chNum, so that BCDMA can identify it as Tx Channel*/
            (void) CSL_bcdmaGetRT(&drvHandle->bcdmaRegs, chHandle->txChNum + drvHandle->txChOffset, &bcdmaRtStatus);
            if(FALSE == bcdmaRtStatus.enable)
            {
                /* Teardown complete */
                end_loop = true;
            }
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            (void) CSL_pktdmaGetRT(&drvHandle->pktdmaRegs, chHandle->txChNum, &pktdmaRtStatus);
            if(FALSE == pktdmaRtStatus.enable)
            {
                /* Teardown complete */
                end_loop = true;
            }
        }
        else
        {
          /* Do Nothing */
        }
        if (end_loop)
        {
          break;
        }
#endif

        if(currTimeout > timeout)
        {
            retVal = UDMA_ETIMEOUT;
        }
        else
        {
            (void) ClockP_usleep(1000U);
            currTimeout++;
        }
    }

    if(UDMA_SOK != retVal)
    {
        /* Graceful teardown failed - initiate force teardown */
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            /*Add offset to chNum, so that BCDMA can identify it as Tx Channel*/
            retVal = CSL_bcdmaTeardownChan(
                        &drvHandle->bcdmaRegs, chHandle->txChNum, (bool)true, (bool)false);
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            retVal = CSL_pktdmaTeardownChannel(
                        &drvHandle->pktdmaRegs, chHandle->txChNum, (bool)true, (bool)false, CSL_PKTDMA_CHAN_DIR_TX);
        }
        else
        {
          /* Do Nothing */
        }
#endif
        if(CSL_PASS != retVal)
        {
            DebugP_logError("[UDMA] TX force disable failed!!\r\n");
        }
        /* Wait for disable to complete */
        currTimeout = 0U;
        while(UDMA_SOK == retVal)
        {
          bool end_loop = false;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
            if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
            {
                /*Add offset to chNum, so that BCDMA can identify it as Tx Channel*/
                (void) CSL_bcdmaGetRT(&drvHandle->bcdmaRegs, chHandle->txChNum + drvHandle->txChOffset, &bcdmaRtStatus);
                if((FALSE == bcdmaRtStatus.enable))
                {
                    /* Teardown complete */
                    end_loop = true;
                }
            }
            else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
            {
                (void) CSL_pktdmaGetRT(&drvHandle->pktdmaRegs, chHandle->txChNum, &pktdmaRtStatus);

                if(FALSE == pktdmaRtStatus.enable)
                {
                    /* Teardown complete */
                    end_loop = true;
                }
            }
            else
            {
              /* Do Nothing */
            }
            if (end_loop)
            {
              break;
            }
#endif

            if(currTimeout > timeout)
            {
                retVal = UDMA_ETIMEOUT;
                DebugP_logError("[UDMA] TX ch teardown timed out!!!\r\n");
            }
            else
            {
                (void) ClockP_usleep(1000U);
                currTimeout++;
            }
        }
    }

    if(UDMA_SOK == retVal)
    {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            /* Clear teardown bits in both the BCDMA and peer */
            bcdmaRtStatus.enable   = FALSE;
            bcdmaRtStatus.forcedTeardown = FALSE;
            bcdmaRtStatus.teardown = FALSE;   /* Note that other bits are cleared from previous call */
            CSL_BcdmaCfg *pCfg;
            pCfg = &drvHandle->bcdmaRegs;

            CSL_REG32_WR(&pCfg->pBcChanRtv2Regs->CHAN[chHandle->txChNum].CTL,
                    CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_EN,           bcdmaRtStatus.enable)    |
                    CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_TDOWN,        bcdmaRtStatus.teardown)  |
                    CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_PAUSE,        bcdmaRtStatus.pause) );
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            /* Clear teardown and enable bits in both PKTDMA and peer */
            pktdmaRtStatus.enable   = FALSE;
            pktdmaRtStatus.teardown = FALSE;
            pktdmaRtStatus.forcedTeardown = FALSE;
             CSL_PktdmaCfg *pCfg;

            pCfg = &drvHandle->pktdmaRegs;
            CSL_REG32_WR(&pCfg->pPktChanRtv2Regs->CHAN[chHandle->txChNum].CTL,
                    CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_EN,           pktdmaRtStatus.enable)    |
                    CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_TDOWN,        pktdmaRtStatus.teardown)  |
                    CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_PAUSE,        pktdmaRtStatus.pause) );
        }
        else
        {
          /* Do Nothing */
        }
#endif
    }

    return (retVal);
}

static int32_t Udma_chDisableRxChan(Udma_ChHandleInt chHandle, uint32_t timeout)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t            currTimeout = 0U;
    Udma_DrvHandleInt   drvHandle;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    CSL_BcdmaRT         bcdmaRtStatus;
    CSL_PktdmaRT        pktdmaRtStatus;
#endif
    uint32_t regVal;
    drvHandle = chHandle->drvHandle;
    if(chHandle->rxChNum != UDMA_DMA_CH_INVALID)
    {
    /* Initiate graceful teardown first - Source is peer thread for RX */
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
       if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
       {
           regVal = CSL_REG32_RD(&chHandle->pBcdmaBcRtRegs->CTL);
           CSL_FINS(regVal, PSILCFG_REG_RT_ENABLE_TDOWN, (uint32_t) 1U);
           CSL_REG32_WR(&chHandle->pBcdmaBcRtRegs->CTL, regVal);
       }
       else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
       {
           regVal = CSL_REG32_RD(&chHandle->pPktdmaRtRegs->CTL);
           CSL_FINS(regVal, PSILCFG_REG_RT_ENABLE_TDOWN, (uint32_t) 1U);
           CSL_REG32_WR(&chHandle->pPktdmaRtRegs->CTL, regVal);
       }
       else
       {
           /* Do Nothing */
       }
#endif
    }
    else
    {
       retVal = UDMA_EINVALID_PARAMS;
    }

    /* Check if graceful teardown is complete */
    while(UDMA_SOK == retVal)
    {
      bool end_loop = false;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            /*Add offset to chNum, so that BCDMA can identify it as Rx Channel*/
            (void) CSL_bcdmaGetRT(&drvHandle->bcdmaRegs, chHandle->rxChNum, &bcdmaRtStatus);
            if(FALSE == bcdmaRtStatus.enable)
            {
                /* Teardown complete */
                end_loop = true;
            }
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            (void) CSL_pktdmaGetRT(&drvHandle->pktdmaRegs, chHandle->rxChNum, &pktdmaRtStatus);
            if(FALSE == pktdmaRtStatus.enable)
            {
                /* Teardown complete */
                end_loop = true;
            }
        }
        else
        {
          /* Do Nothing */
        }
        if (end_loop)
        {
          break;
        }
#endif

        if(currTimeout > timeout)
        {
            retVal = UDMA_ETIMEOUT;
        }
        else
        {
            (void) ClockP_usleep(1000U);
            currTimeout++;
        }
    }

    if(UDMA_SOK != retVal)
    {
        /* Graceful teardown failed - initiate force teardown */
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            /*Add offset to chNum, so that BCDMA can identify it as Rx Channel*/
            retVal = CSL_bcdmaTeardownChan(
                        &drvHandle->bcdmaRegs, chHandle->rxChNum, (bool)true, (bool)false);
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            retVal = CSL_pktdmaTeardownChannel(
                        &drvHandle->pktdmaRegs, chHandle->rxChNum, (bool)true, (bool)false, CSL_PKTDMA_CHAN_DIR_RX);
        }
        else
        {
          /* Do Nothing */
        }
#endif
        if(CSL_PASS != retVal)
        {
            DebugP_logError("[UDMA] RX force disable failed!!\r\n");
        }

        /* Wait for disable to complete - both locally and for peer thread */
        currTimeout = 0U;
        while(UDMA_SOK == retVal)
        {
          bool end_loop = false;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
            if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
            {
                /*Add offset to chNum, so that BCDMA can identify it as Rx Channel*/
                (void) CSL_bcdmaGetRT(&drvHandle->bcdmaRegs, chHandle->rxChNum, &bcdmaRtStatus);

                if(FALSE == bcdmaRtStatus.enable)
                {
                    /* Teardown complete */
                    end_loop = true;
                }
            }
            else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
            {
                (void) CSL_pktdmaGetRT(&drvHandle->pktdmaRegs, chHandle->rxChNum, &pktdmaRtStatus);
                if(FALSE == pktdmaRtStatus.enable)
                {
                    /* Teardown complete */
                    end_loop = true;
                }
            }
            else
            {
              /* Do Nothing */
            }
            if (end_loop)
            {
              break;
            }
#endif
            if(currTimeout > timeout)
            {
                retVal = UDMA_ETIMEOUT;
                DebugP_logError("[UDMA] RX ch teardown timed out!!!\r\n");
            }
            else
            {
                (void) ClockP_usleep(1000U);
                currTimeout++;
            }
        }
    }

    if(UDMA_SOK == retVal)
    {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            /* Clear teardown bits in both the BCDMA and peer */
            bcdmaRtStatus.enable   = FALSE;
            bcdmaRtStatus.forcedTeardown = FALSE;
            bcdmaRtStatus.teardown = FALSE;   /* Note that other bits are cleared from previous call */
            CSL_BcdmaCfg *pCfg;
            pCfg = &drvHandle->bcdmaRegs;

            CSL_REG32_WR(&pCfg->pBcChanRtv2Regs->CHAN[chHandle->rxChNum].CTL,
                    CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_EN,           bcdmaRtStatus.enable)    |
                    CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_TDOWN,        bcdmaRtStatus.teardown)  |
                    CSL_FMK(BCDMA_CHRT_V2_CHAN_CTL_PAUSE,        bcdmaRtStatus.pause) );
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            /* Clear teardown bits in both the PKTDMA and peer */
            pktdmaRtStatus.enable   = FALSE;
            pktdmaRtStatus.forcedTeardown = FALSE;
            pktdmaRtStatus.teardown = FALSE;   /* Note that other bits are cleared from previous call */
            CSL_PktdmaCfg *pCfg;

            pCfg = &drvHandle->pktdmaRegs;

            CSL_REG32_WR(&pCfg->pPktChanRtv2Regs->CHAN[chHandle->rxChNum].CTL,
                    CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_EN,           pktdmaRtStatus.enable)    |
                    CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_TDOWN,        pktdmaRtStatus.teardown)  |
                    CSL_FMK(PKTDMA_CHRT_V2_CHAN_CTL_PAUSE,        pktdmaRtStatus.pause) );
        }
        else
        {
          /* Do Nothing */
        }
#endif
    }

    return (retVal);
}

static void Udma_chAssignRegOverlay(Udma_DrvHandleInt drvHandle, Udma_ChHandleInt chHandle)
{
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
    {
        if(chHandle->txChNum != UDMA_DMA_CH_INVALID)
        {
            if((drvHandle->bcdmaRegs.pBcChanCfgv2Regs != NULL) && 
                (drvHandle->bcdmaRegs.pBcChanRtv2Regs != NULL))
            {
                chHandle->pBcdmaBcCfgRegs =
                  &drvHandle->bcdmaRegs.pBcChanCfgv2Regs->CHAN[chHandle->txChNum];
                chHandle->pBcdmaBcRtRegs  =
                  &drvHandle->bcdmaRegs.pBcChanRtv2Regs->CHAN[chHandle->txChNum];
            }
        }
        if(chHandle->rxChNum != UDMA_DMA_CH_INVALID)
        {
            if((drvHandle->bcdmaRegs.pBcChanCfgv2Regs != NULL) && 
                (drvHandle->bcdmaRegs.pBcChanRtv2Regs != NULL))
            {
               chHandle->pBcdmaBcCfgRegs =
                &drvHandle->bcdmaRegs.pBcChanCfgv2Regs->CHAN[chHandle->rxChNum];
               chHandle->pBcdmaBcRtRegs  =
                &drvHandle->bcdmaRegs.pBcChanRtv2Regs->CHAN[chHandle->rxChNum];
            }
        }
    }
    else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
    {
        if(chHandle->txChNum != UDMA_DMA_CH_INVALID)
        {
            if((drvHandle->pktdmaRegs.pPktChanCfgv2Regs != NULL) && 
                (drvHandle->pktdmaRegs.pPktChanRtv2Regs != NULL))
            {
                chHandle->pPktdmaCfgRegs =
                  &drvHandle->pktdmaRegs.pPktChanCfgv2Regs->CHAN[chHandle->txChNum];
                chHandle->pPktdmaRtRegs  =
                  &drvHandle->pktdmaRegs.pPktChanRtv2Regs->CHAN[chHandle->txChNum];
            }
        }
        if(chHandle->rxChNum != UDMA_DMA_CH_INVALID)
        {
            if((drvHandle->pktdmaRegs.pPktChanCfgv2Regs != NULL) && 
                (drvHandle->pktdmaRegs.pPktChanRtv2Regs != NULL))
            {
                chHandle->pPktdmaCfgRegs =
                  &drvHandle->pktdmaRegs.pPktChanCfgv2Regs->CHAN[chHandle->rxChNum];
                chHandle->pPktdmaRtRegs  =
                  &drvHandle->pktdmaRegs.pPktChanRtv2Regs->CHAN[chHandle->rxChNum];
            }
        }
    }
    else
    {
      /* Do Nothing */
    }
#endif
}

static void Udma_chInitRegs(Udma_ChHandleInt chHandle)
{
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    chHandle->pBcdmaBcCfgRegs   = (volatile CSL_bcdma_chcfg_v2Regs_chan *) NULL;
    chHandle->pBcdmaBcRtRegs    = (volatile CSL_bcdma_chrt_v2Regs_chan *) NULL;

    chHandle->pPktdmaCfgRegs   = (volatile CSL_pktdma_chcfg_v2Regs_chan *) NULL;
    chHandle->pPktdmaRtRegs    = (volatile CSL_pktdma_chrt_v2Regs_chan *) NULL;

#endif
}


static void Udma_chPauseTxLocal(Udma_DrvHandleInt drvHandle, uint32_t txChNum,uint32_t chType)
{
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
    {
        (void) CSL_bcdmaPauseChan(&drvHandle->bcdmaRegs, txChNum);
    }
    else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
    {
        (void) CSL_pktdmaPauseChannel(&drvHandle->pktdmaRegs, txChNum, 
                     CSL_PKTDMA_CHAN_DIR_TX);
    }
    else
    {
      /* Do Nothing */
    }
#endif
}

static void Udma_chUnpauseTxLocal(Udma_DrvHandleInt drvHandle, uint32_t txChNum, uint32_t chType)
{
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
    {
        (void) CSL_bcdmaUnpauseChan(&drvHandle->bcdmaRegs, txChNum);
    }
    else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
    {
        (void) CSL_pktdmaUnpauseChannel(&drvHandle->pktdmaRegs, txChNum, 
                     CSL_PKTDMA_CHAN_DIR_TX);
    }
    else
    {
      /* Do Nothing */
    }
#endif
}

static void Udma_chPauseRxLocal(Udma_DrvHandleInt drvHandle, uint32_t rxChNum)
{
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
    {
        /*Add offset to chNum, so that BCDMA can identify it as Rx Channel*/
        (void) CSL_bcdmaPauseChan(&drvHandle->bcdmaRegs, rxChNum);
    }
    else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
    {
        (void) CSL_pktdmaPauseChannel(&drvHandle->pktdmaRegs, rxChNum, 
                      CSL_PKTDMA_CHAN_DIR_RX);
    }
    else
    {
      /* Do Nothing */
    }
#endif
}

static void Udma_chUnpauseRxLocal(Udma_DrvHandleInt drvHandle, uint32_t rxChNum)
{
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
    {
        /*Add offset to chNum, so that BCDMA can identify it as Rx Channel*/
        (void) CSL_bcdmaUnpauseChan(&drvHandle->bcdmaRegs, rxChNum);
    }
    else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
    {
        (void) CSL_pktdmaUnpauseChannel(&drvHandle->pktdmaRegs, rxChNum, 
                        CSL_PKTDMA_CHAN_DIR_RX);
    }
    else
    {
      /* Do Nothing */
    }
#endif
}

int32_t Udma_chReset(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;

    /* Error check */
    if((NULL == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(retVal == UDMA_SOK)
    {
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            CSL_BcdmaChanStats chStat;

            if((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
            {
                /* Disable channel */
                retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_DISABLE,
                                            CSL_BCDMA_CHAN_TYPE_BLOCK_COPY, chHandleInt->txChNum,
                                            NULL);

                /* Reset stats */
                if(retVal == UDMA_SOK)
                {
                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_GET_STATS,
                                            CSL_BCDMA_CHAN_TYPE_BLOCK_COPY, chHandleInt->txChNum,
                                            &chStat);

                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_DEC_STATS,
                                            CSL_BCDMA_CHAN_TYPE_BLOCK_COPY, chHandleInt->txChNum,
                                            &chStat);
                }
            }
            else if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
            {
                /* Disable channel */
                retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_DISABLE,
                                            CSL_BCDMA_CHAN_TYPE_SPLIT_TX, chHandleInt->txChNum,
                                            NULL);

                /* Reset stats */
                if(retVal == UDMA_SOK)
                {
                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_GET_STATS,
                                            CSL_BCDMA_CHAN_TYPE_SPLIT_TX, chHandleInt->txChNum,
                                            &chStat);

                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_DEC_STATS,
                                            CSL_BCDMA_CHAN_TYPE_SPLIT_TX, chHandleInt->txChNum,
                                            &chStat);
                }
            }
            else if((chHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
            {
                /* Disable channel */
                retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_DISABLE,
                                            CSL_BCDMA_CHAN_TYPE_SPLIT_RX, chHandleInt->rxChNum,
                                            NULL);

                /* Reset stats */
                if(retVal == UDMA_SOK)
                {
                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_GET_STATS,
                                            CSL_BCDMA_CHAN_TYPE_SPLIT_RX, chHandleInt->rxChNum,
                                            &chStat);
                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_DEC_STATS,
                                            CSL_BCDMA_CHAN_TYPE_SPLIT_RX, chHandleInt->rxChNum,
                                            &chStat);
                }
            }
            else
            {
                retVal = UDMA_EBADARGS;
            }
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {

            if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
            {
                /* Disable channel */
                retVal = CSL_pktdmaDisableChannel(&drvHandle->pktdmaRegs, chHandleInt->txChNum, CSL_PKTDMA_CHAN_DIR_TX);

                /* Reset stats */
                CSL_PktdmaChanStats chanStats;
                CSL_pktdmaGetChanStats(&drvHandle->pktdmaRegs,
                                        chHandleInt->txChNum,
                                        CSL_PKTDMA_CHAN_DIR_TX, &chanStats);
                CSL_pktdmaDecChanStats(&drvHandle->pktdmaRegs,
                                        chHandleInt->txChNum,
                                        CSL_PKTDMA_CHAN_DIR_TX, &chanStats);
            }
            else if((chHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
            {
                /* Disable channel */
                retVal = CSL_pktdmaDisableChannel(&drvHandle->pktdmaRegs, chHandleInt->rxChNum, CSL_PKTDMA_CHAN_DIR_TX);

                /* Reset stats */
                CSL_PktdmaChanStats chanStats;
                CSL_pktdmaGetChanStats(&drvHandle->pktdmaRegs,
                                        chHandleInt->rxChNum,
                                        CSL_PKTDMA_CHAN_DIR_RX, &chanStats);
                CSL_pktdmaDecChanStats(&drvHandle->pktdmaRegs,
                                        chHandleInt->rxChNum,
                                        CSL_PKTDMA_CHAN_DIR_RX, &chanStats);
            }
            else
            {
                retVal = UDMA_EBADARGS;
            }
        }
        else
        {
            retVal = UDMA_EBADARGS;
        }
    }

    return retVal;
}


int32_t Udma_getPeerData(Udma_ChHandle chHandle, uint32_t *peerData)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;
    CSL_PktdmaCfg *pPktCfg;
    CSL_BcdmaCfg *pBcCfg;

    /* Error check */
    if((NULL == chHandleInt) ||
       (chHandleInt->chInitDone != UDMA_INIT_DONE) ||
       ((chHandleInt->chType & UDMA_CH_FLAG_PDMA) != UDMA_CH_FLAG_PDMA))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            pPktCfg = &drvHandle->pktdmaRegs;
            if(pPktCfg->pPktChanRtv2Regs != NULL)
            {
               if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
               {
                   *peerData = CSL_pktdmaGetPeerData(pPktCfg, chHandleInt->txChNum);
               }
               else
               {
                   *peerData = CSL_pktdmaGetPeerData(pPktCfg, chHandleInt->rxChNum);
               }
            }
        }
        else
        {
            pBcCfg = &drvHandle->bcdmaRegs;
            if(pBcCfg->pBcChanRtv2Regs != NULL)
            {
                if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                   *peerData = CSL_bcdmaGetPeerData(pBcCfg, chHandleInt->txChNum);
                }
                else
                {
                    *peerData = CSL_bcdmaGetPeerData(pBcCfg, chHandleInt->rxChNum);
                }
            }
        }
#endif
    }

    return (retVal);
}

int32_t Udma_clearPeerData(Udma_ChHandle chHandle, uint32_t peerData)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;
    CSL_PktdmaCfg *pPktCfg;
    CSL_BcdmaCfg *pBcCfg;

    /* Error check */
    if((NULL == chHandleInt) ||
       (chHandleInt->chInitDone != UDMA_INIT_DONE) ||
       ((chHandleInt->chType & UDMA_CH_FLAG_PDMA) != UDMA_CH_FLAG_PDMA))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            pPktCfg = &drvHandle->pktdmaRegs;
            if(pPktCfg->pPktChanRtv2Regs != NULL)
            {
                if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                    retVal = CSL_pktdmaSetPeerData(pPktCfg, peerData, chHandleInt->txChNum);
                }
                else
                {
                    retVal = CSL_pktdmaSetPeerData(pPktCfg, peerData, chHandleInt->rxChNum);
                }
            }
        }
        else
        {
            pBcCfg = &drvHandle->bcdmaRegs;
            if(pBcCfg->pBcChanRtv2Regs != NULL)
            {
                if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                   retVal = CSL_bcdmaSetPeerData(pBcCfg, peerData, chHandleInt->txChNum);
                }
                else
                {
                   retVal = CSL_bcdmaSetPeerData(pBcCfg, peerData, chHandleInt->rxChNum);
                }
            }
        }
#endif
    }

    return (retVal);
}


int32_t Udma_TeardownChan(Udma_ChHandle chHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;
    CSL_LcdmaRingaccCfg *pRaCfg;

/* Error check */
    if((NULL == chHandleInt) ||
       (chHandleInt->chInitDone != UDMA_INIT_DONE) ||
       ((chHandleInt->chType & UDMA_CH_FLAG_PDMA) != UDMA_CH_FLAG_PDMA))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        pRaCfg = &drvHandle->lcdmaRaRegs;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE)|| (NULL == pRaCfg))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(retVal == UDMA_SOK)
    {
        if((chHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX )
        {
            retVal = CSL_pktdmaTeardownChan(&drvHandle->pktdmaRegs, chHandleInt->rxChNum, CSL_PKTDMA_CHAN_DIR_RX, 1, 1 );
            CSL_lcdmaSetInterrupt(pRaCfg, chHandleInt->rxChNum, UDMA_SET_COMP_INT, false);
            CSL_lcdmaTdownACk(pRaCfg, chHandleInt->rxChNum);
        }
        else
        {
            retVal = CSL_pktdmaTeardownChan(&drvHandle->pktdmaRegs, chHandleInt->txChNum, CSL_PKTDMA_CHAN_DIR_TX, 1, 1 );
            CSL_lcdmaSetInterrupt(pRaCfg, chHandleInt->txChNum, UDMA_SET_COMP_INT, false);
            CSL_lcdmaTdownACk(pRaCfg, chHandleInt->txChNum);
        }
    }

    return retVal;
}

int32_t Udma_chGetChanEnStatus(Udma_ChHandle chHandle, uint8_t *chEnableStat)
{
    int32_t retVal = 0U;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    CSL_BcdmaRT pRT;
    CSL_PktdmaRT pktdmaRtStatus;
#endif

    /* Error check */
    if((NULL_PTR == chHandleInt) || (chHandleInt->chInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL_PTR == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(retVal == UDMA_SOK)
    {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            if((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
            {
                if(chHandleInt->txChNum == UDMA_DMA_CH_INVALID)
                {
                    retVal = UDMA_DMA_CH_INVALID;
                }
                else
                {
                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_GET_RT,
                    CSL_BCDMA_CHAN_TYPE_BLOCK_COPY, chHandleInt->txChNum, (void *)&pRT);

                    *chEnableStat = (uint8_t)pRT.enable;
                }
            }
            else if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
            {
                if(chHandleInt->txChNum == UDMA_DMA_CH_INVALID)
                {
                    retVal = UDMA_DMA_CH_INVALID;
                }
                else
                {
                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_GET_RT,
                    CSL_BCDMA_CHAN_TYPE_SPLIT_TX, chHandleInt->txChNum, (void *)&pRT);

                    *chEnableStat = (uint8_t)pRT.enable;
                }
            }
            else if((chHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
            {
                if(chHandleInt->rxChNum == UDMA_DMA_CH_INVALID)
                {
                    retVal = UDMA_DMA_CH_INVALID;
                }
                else
                {
                    retVal = CSL_bcdmaChanOp(&drvHandle->bcdmaRegs, CSL_BCDMA_CHAN_OP_GET_RT,
                    CSL_BCDMA_CHAN_TYPE_SPLIT_RX, chHandleInt->rxChNum, (void *)&pRT);

                    *chEnableStat = (uint8_t)pRT.enable;
                }
            }
            else
            {
                retVal = UDMA_EBADARGS;
            }
        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
            {
                if(chHandleInt->txChNum == UDMA_DMA_CH_INVALID)
                {
                    retVal = UDMA_DMA_CH_INVALID;
                }
                else
                {
                    retVal = CSL_pktdmaGetRT(&drvHandle->pktdmaRegs, chHandleInt->txChNum, &pktdmaRtStatus);

                    *chEnableStat = (uint8_t)pktdmaRtStatus.enable;
                }
            }
            else if((chHandleInt->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX)
            {
                if(chHandleInt->rxChNum == UDMA_DMA_CH_INVALID)
                {
                    retVal = UDMA_DMA_CH_INVALID;
                }
                else
                {
                    retVal = CSL_pktdmaGetRT(&drvHandle->pktdmaRegs, chHandleInt->rxChNum, &pktdmaRtStatus);

                    *chEnableStat = (uint8_t)pktdmaRtStatus.enable;
                }
            }
            else
            {
                retVal = UDMA_EBADARGS;
            }
        }
        else
        {
            retVal = UDMA_EBADARGS;
        }
#endif
    }

    return retVal;
}

int32_t Udma_chDecStats(Udma_ChHandle chHandle, Udma_ChStats *chStats)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandleInt = (Udma_ChHandleInt) chHandle;
    uint32_t            chNum;
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
    CSL_BcdmaChanStats  bcdmaChanStats = {0};
    CSL_BcdmaChanDir    bcdmaChDir;
    CSL_PktdmaChanStats pktdmaChanStats = {0};
    CSL_PktdmaChanDir   pktdmaChDir;
#endif

    /* Error check */
    if ((NULL_PTR == chHandleInt)                   ||
        (chHandleInt->chInitDone != UDMA_INIT_DONE) ||
        (chStats == NULL))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = chHandleInt->drvHandle;
        if((NULL_PTR == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
#if (UDMA_SOC_CFG_LCDMA_PRESENT == 1)
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            if((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
            {
                chNum       = chHandleInt->txChNum;
                bcdmaChDir = CSL_BCDMA_CHAN_DIR_TX;
            }
            else
            {
                if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                    /* Add offset to chNum, so that BCDMA can identify it as Tx channel*/
                    chNum       = chHandleInt->txChNum + drvHandle->txChOffset;
                    bcdmaChDir = CSL_BCDMA_CHAN_DIR_TX;
                }
                else
                {
                    /* Add offset to chNum, so that BCDMA can identify it as Rx channel*/
                    chNum       = chHandleInt->rxChNum + drvHandle->rxChOffset;
                    bcdmaChDir = CSL_BCDMA_CHAN_DIR_RX;
                }
            }
            bcdmaChanStats.packetCnt = chStats->packetCnt;
            bcdmaChanStats.completedByteCnt = chStats->completedByteCnt;
            bcdmaChanStats.startedByteCnt = chStats->startedByteCnt;
            CSL_bcdmaDecChanStats(&drvHandle->bcdmaRegs, chNum, bcdmaChDir, &bcdmaChanStats);

        }
        else if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            if((chHandleInt->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
            {
                chNum       = chHandleInt->txChNum;
                pktdmaChDir = CSL_PKTDMA_CHAN_DIR_TX;
            }
            else
            {
                if((chHandleInt->chType & UDMA_CH_FLAG_TX) == UDMA_CH_FLAG_TX)
                {
                    chNum       = chHandleInt->txChNum;
                    pktdmaChDir = CSL_PKTDMA_CHAN_DIR_TX;
                }
                else
                {
                    chNum       = chHandleInt->rxChNum;
                    pktdmaChDir = CSL_PKTDMA_CHAN_DIR_RX;
                }
            }
            pktdmaChanStats.packetCnt = chStats->packetCnt;
            pktdmaChanStats.completedByteCnt = chStats->completedByteCnt;
            pktdmaChanStats.startedByteCnt = chStats->startedByteCnt;
            CSL_pktdmaDecChanStats(&drvHandle->pktdmaRegs, chNum, pktdmaChDir, &pktdmaChanStats);
        }
        else
        {
          /* Do Nothing */
        }
#endif
    }

    return (retVal);
}
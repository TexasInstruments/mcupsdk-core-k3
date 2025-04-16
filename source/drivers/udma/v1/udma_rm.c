/*
 *  Copyright (C) 2018-2025 Texas Instruments Incorporated
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
 *  \file udma_rm.c
 *
 *  \brief File containing the UDMA driver Resource Manager (RM)
 *  abstraction functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/udma/v1/udma_priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

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

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t UdmaRmInitPrms_init(uint32_t instId, Udma_DrvHandleInt   drvHandle)
{
    Udma_RmInitPrms                              *rmInitPrms;
    CSL_BcdmaCfg                                 *pBcCfg;
    CSL_PktdmaCfg                                *pPktCfg;
    int32_t                                      retVal = UDMA_SOK;

    rmInitPrms = &drvHandle->rmInitPrms;
    /* Error check */
    if(NULL == rmInitPrms)
    {
        retVal = UDMA_EBADARGS;
    }

    if(UDMA_SOK == retVal)
    {
        if(UDMA_INST_ID_BCDMA_0 == instId)
        {
            pBcCfg = &drvHandle->bcdmaRegs;
            if((pBcCfg != NULL))
            {
                CSL_bcdmaGetCfg(pBcCfg);
                /* Ultra High Capacity Block Copy Channels */
                rmInitPrms->startBlkCopyUhcCh   = 0U;
                rmInitPrms->numBlkCopyUhcCh     = pBcCfg->bcUltraHighCapacityChanCnt;

                /* High Capacity Block Copy Channels */
                rmInitPrms->startBlkCopyHcCh    = 0U;
                rmInitPrms->numBlkCopyHcCh      = pBcCfg->bcHighCapacityChanCnt;

                /* Normal Capacity Block Copy Channels */
                rmInitPrms->startBlkCopyCh      = UDMA_RM_BLKCPY_START;
                rmInitPrms->numBlkCopyCh        = pBcCfg->bcChanCnt;

                /* Normal Capacity TX Channels */
                rmInitPrms->startTxCh           = UDMA_RM_SPLIT_TX_START;
                rmInitPrms->numTxCh             = pBcCfg->txChanCnt;

                /* Normal Capacity RX Channels */
                rmInitPrms->startRxCh           = UDMA_RM_SPLIT_RX_START;
                rmInitPrms->numRxCh             = pBcCfg->rxChanCnt;

                /* Ultra High Capacity TX Channels */
                rmInitPrms->startTxUhcCh        = 0U;
                rmInitPrms->numTxUhcCh          = pBcCfg->txUltraHighCapacityChanCnt;

                /* High Capacity TX Channels */
                rmInitPrms->startTxHcCh         = 0U;
                rmInitPrms->numTxHcCh           = pBcCfg->txHighCapacityChanCnt;

                /* Ultra High Capacity RX Channels */
                rmInitPrms->startRxUhcCh        = 0U;
                rmInitPrms->numRxUhcCh          = pBcCfg->rxUltraHighCapacityChanCnt;

                /* High Capacity RX Channels */
                rmInitPrms->startRxHcCh         = 0U;
                rmInitPrms->numRxHcCh           = pBcCfg->rxHighCapacityChanCnt;

                /* Flow counts */
                rmInitPrms->tflowCnt     = pBcCfg->tflowCnt;
                rmInitPrms->rflowCnt     = pBcCfg->rflowCnt; 
            }
        }
        else
        {
            pPktCfg = &drvHandle->pktdmaRegs;
            if((pPktCfg != NULL))
            {
                CSL_pktdmaGetCfg(pPktCfg);
               /* Normal Capacity TX Channels */
                rmInitPrms->startTxCh           = UDMA_RM_SPLIT_TX_START;
                rmInitPrms->numTxCh             = pPktCfg->txChanCnt;

                /* Normal Capacity RX Channels */
                rmInitPrms->startRxCh           = UDMA_RM_SPLIT_RX_START;
                rmInitPrms->numRxCh             = pPktCfg->rxChanCnt;

                /* Ultra High Capacity TX Channels */
                rmInitPrms->startTxUhcCh        = 0U;
                rmInitPrms->numTxUhcCh          = pPktCfg->txUltraHighCapacityChanCnt;

                /* High Capacity TX Channels */
                rmInitPrms->startTxHcCh         = 0U;
                rmInitPrms->numTxHcCh           = pPktCfg->txHighCapacityChanCnt;

                /* Ultra High Capacity RX Channels */
                rmInitPrms->startRxUhcCh        = 0U;
                rmInitPrms->numRxUhcCh          = pPktCfg->rxUltraHighCapacityChanCnt;

                /* High Capacity RX Channels */
                rmInitPrms->startRxHcCh         = 0U;
                rmInitPrms->numRxHcCh           = pPktCfg->rxHighCapacityChanCnt;

                /* Flow counts */
                rmInitPrms->tflowCnt     = pPktCfg->txFlowCnt;
                rmInitPrms->rflowCnt     = pPktCfg->rxFlowCnt;
            }
        } 
        rmInitPrms->numIrIntr        = UDMA_RM_TOTAL_CH_INT;
        rmInitPrms->startIrIntr      = UDMA_RM_CH_INT_START;                
    }
    return (retVal);
}

void Udma_rmInit(Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    /* Mark all resources as free */
    for(i = rmInitPrms->startBlkCopyCh; i < (rmInitPrms->startBlkCopyCh + rmInitPrms->numBlkCopyCh); i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_BLK_COPY_CH_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->blkCopyChFlag[offset] |= bitMask;
        }
    }
    for(i = rmInitPrms->startBlkCopyHcCh; i < rmInitPrms->numBlkCopyHcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_BLK_COPY_HC_CH_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->blkCopyHcChFlag[offset] |= bitMask;
        }
    }
    for(i = rmInitPrms->startBlkCopyUhcCh; i < rmInitPrms->numBlkCopyUhcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_BLK_COPY_UHC_CH_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->blkCopyUhcChFlag[offset] |= bitMask;
        }
    }
    for(i = rmInitPrms->startRxCh; i < UDMA_SOC_BCDMA_TOTAL_TX_RX_CHAN; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_TX_RX_CH_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->bcDmaChFlag[offset] |= bitMask;
        }
    }
    for(i = rmInitPrms->startRxCh; i < UDMA_SOC_PKTDMA_TOTAL_TX_RX_CHAN; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_TX_RX_CH_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->pktDmaChFlag[offset] |= bitMask;
        }
    }
    for(i = rmInitPrms->startTxHcCh; i < rmInitPrms->numTxHcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_TX_HC_CH_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->txHcChFlag[offset] |= bitMask;
        }
    }
    for(i = rmInitPrms->startRxHcCh; i < rmInitPrms->numRxHcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_RX_HC_CH_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->rxHcChFlag[offset] |= bitMask;
        }
    }
    for(i = rmInitPrms->startTxUhcCh; i < rmInitPrms->numTxUhcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_TX_UHC_CH_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->txUhcChFlag[offset] |= bitMask;
        }
    }
    for(i = rmInitPrms->startRxUhcCh; i < rmInitPrms->numRxUhcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_RX_UHC_CH_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->rxUhcChFlag[offset] |= bitMask;
        }
    }
    for(i = rmInitPrms->startIrIntr; 
       i < (rmInitPrms->startIrIntr + rmInitPrms->numIrIntr); i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_IR_INTR_ARR_SIZE)
        {
           bitPos = i - (offset << 5U);
           bitMask = (uint32_t) 1U << bitPos;
           drvHandle->irIntrFlag[offset] |= bitMask;
        }
    }

    return;
}

int32_t Udma_rmDeinit(Udma_DrvHandleInt drvHandle)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t    i, offset;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;
    uint32_t                copyblkCopyChFlag[UDMA_RM_BLK_COPY_CH_ARR_SIZE] = {0};
    uint32_t                copyblkCopyHcChFlag[UDMA_RM_BLK_COPY_HC_CH_ARR_SIZE] = {0};
    uint32_t                copyblkCopyUhcChFlag[UDMA_RM_BLK_COPY_UHC_CH_ARR_SIZE] = {0};
    uint32_t                copypktDmaChFlag[UDMA_RM_TX_RX_CH_ARR_SIZE] = {0};
    uint32_t                copytxHcChFlag[UDMA_RM_TX_HC_CH_ARR_SIZE] = {0};
    uint32_t                copytxUhcChFlag[UDMA_RM_TX_UHC_CH_ARR_SIZE] = {0};
    uint32_t                copybcDmaChFlag[UDMA_RM_TX_RX_CH_ARR_SIZE] = {0};
    uint32_t                copyrxHcChFlag[UDMA_RM_RX_HC_CH_ARR_SIZE] = {0};
    uint32_t                copyrxUhcChFlag[UDMA_RM_RX_UHC_CH_ARR_SIZE] = {0};
    uint32_t                copyirIntrFlag[UDMA_RM_IR_INTR_ARR_SIZE] = {0};

    /* Copy the allocated flags current state */
    memcpy(&copyblkCopyChFlag[0U], &drvHandle->blkCopyChFlag[0U], sizeof(drvHandle->blkCopyChFlag));
    memcpy(&copyblkCopyHcChFlag[0U], &drvHandle->blkCopyHcChFlag[0U], sizeof(drvHandle->blkCopyHcChFlag));
    memcpy(&copyblkCopyUhcChFlag[0U], &drvHandle->blkCopyUhcChFlag[0U], sizeof(drvHandle->blkCopyUhcChFlag));
    memcpy(&copypktDmaChFlag[0U], &drvHandle->pktDmaChFlag[0U], sizeof(drvHandle->pktDmaChFlag));
    memcpy(&copytxHcChFlag[0U], &drvHandle->txHcChFlag[0U], sizeof(drvHandle->txHcChFlag));
    memcpy(&copytxUhcChFlag[0U], &drvHandle->txUhcChFlag[0U], sizeof(drvHandle->txUhcChFlag));
    memcpy(&copybcDmaChFlag[0U], &drvHandle->bcDmaChFlag[0U], sizeof(drvHandle->bcDmaChFlag));
    memcpy(&copyrxHcChFlag[0U], &drvHandle->rxHcChFlag[0U], sizeof(drvHandle->rxHcChFlag));
    memcpy(&copyrxUhcChFlag[0U], &drvHandle->rxUhcChFlag[0U], sizeof(drvHandle->rxUhcChFlag));
    memcpy(&copyirIntrFlag[0U], &drvHandle->irIntrFlag[0U], sizeof(drvHandle->irIntrFlag));

    /* Initialise all the resources */
    Udma_rmInit(drvHandle);

    /* Compare the allocated resources to it's initial state */
    for(i = rmInitPrms->startBlkCopyCh; i < (rmInitPrms->startBlkCopyCh + rmInitPrms->numBlkCopyCh); i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_BLK_COPY_CH_ARR_SIZE)
        {
           if(copyblkCopyChFlag[offset] != drvHandle->blkCopyChFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }
    for(i = rmInitPrms->startBlkCopyHcCh; i < rmInitPrms->numBlkCopyHcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_BLK_COPY_HC_CH_ARR_SIZE)
        {
           if(copyblkCopyHcChFlag[offset] != drvHandle->blkCopyHcChFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }
    for(i = rmInitPrms->startBlkCopyUhcCh; i < rmInitPrms->numBlkCopyUhcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_BLK_COPY_UHC_CH_ARR_SIZE)
        {
           if(copyblkCopyUhcChFlag[offset] != drvHandle->blkCopyUhcChFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }
    for(i = rmInitPrms->startRxCh; i < UDMA_SOC_BCDMA_TOTAL_TX_RX_CHAN; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_TX_RX_CH_ARR_SIZE)
        {
           if(copybcDmaChFlag[offset] != drvHandle->bcDmaChFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }
    for(i = rmInitPrms->startRxCh; i < UDMA_SOC_PKTDMA_TOTAL_TX_RX_CHAN; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_TX_RX_CH_ARR_SIZE)
        {
           if(copypktDmaChFlag[offset] != drvHandle->pktDmaChFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }
    for(i = rmInitPrms->startTxHcCh; i < rmInitPrms->numTxHcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_TX_HC_CH_ARR_SIZE)
        {
           if(copytxHcChFlag[offset] != drvHandle->txHcChFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }
    for(i = rmInitPrms->startRxHcCh; i < rmInitPrms->numRxHcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_RX_HC_CH_ARR_SIZE)
        {
           if(copyrxHcChFlag[offset] != drvHandle->rxHcChFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }
    for(i = rmInitPrms->startTxUhcCh; i < rmInitPrms->numTxUhcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_TX_UHC_CH_ARR_SIZE)
        {
           if(copytxUhcChFlag[offset] != drvHandle->txUhcChFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }
    for(i = rmInitPrms->startRxUhcCh; i < rmInitPrms->numRxUhcCh; i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_RX_UHC_CH_ARR_SIZE)
        {
           if(copyrxUhcChFlag[offset] != drvHandle->rxUhcChFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }
    for(i = rmInitPrms->startIrIntr; 
       i < (rmInitPrms->startIrIntr + rmInitPrms->numIrIntr); i++)
    {
        offset = i >> 5U;
        if(offset < UDMA_RM_IR_INTR_ARR_SIZE)
        {
           if(copyirIntrFlag[offset] != drvHandle->irIntrFlag[offset])
           {
            retVal = UDMA_EFAIL;
           }
        }
    }

    return (retVal);
}

uint32_t Udma_rmAllocBlkCopyCh(uint32_t preferredChNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    uint32_t            chNum = UDMA_DMA_CH_INVALID;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if(UDMA_DMA_CH_ANY == preferredChNum)
    {
        /* Search and allocate from Blk Copy channel pool */
        for(i = rmInitPrms->startBlkCopyCh; i < (rmInitPrms->startBlkCopyCh + rmInitPrms->numBlkCopyCh); i++)
        {
            offset = i >> 5U;
            if(offset < UDMA_RM_BLK_COPY_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->blkCopyChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->blkCopyChFlag[offset] &= ~bitMask;
                   chNum = i;  /* Add start offset */
                   break;
                }
            }
        }
    }
    else
    {
        /* Allocate specific Block Copy channel if free */
        /* Array bound check */
        if((preferredChNum >= rmInitPrms->startBlkCopyCh) &&
           (preferredChNum < (rmInitPrms->startBlkCopyCh + rmInitPrms->numBlkCopyCh)))
        {
            i = preferredChNum - rmInitPrms->startBlkCopyCh;
            offset = i >> 5U;
            if(offset < UDMA_RM_BLK_COPY_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->blkCopyChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->blkCopyChFlag[offset] &= ~bitMask;
                   chNum = preferredChNum;
                }
            }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return (chNum);
}

void Udma_rmFreeBlkCopyCh(uint32_t chNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);
    i = chNum;
    offset = i >> 5U;
    if(offset < UDMA_RM_BLK_COPY_CH_ARR_SIZE)
    {
        bitPos = i - (offset << 5U);
        bitMask = (uint32_t) 1U << bitPos;
        if((drvHandle->blkCopyChFlag[offset] & bitMask) == 0U)
        {
          drvHandle->blkCopyChFlag[offset] |= bitMask;
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return;
}

uint32_t Udma_rmAllocBlkCopyHcCh(uint32_t preferredChNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    uint32_t            chNum = UDMA_DMA_CH_INVALID;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if(UDMA_DMA_CH_ANY == preferredChNum)
    {
        /* Search and allocate from Blk Copy high capacity channel pool */
        for(i = 0U; i < rmInitPrms->numBlkCopyHcCh; i++)
        {
            offset = i >> 5U;
            if(offset < UDMA_RM_BLK_COPY_HC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->blkCopyHcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->blkCopyHcChFlag[offset] &= ~bitMask;
                   chNum = i + rmInitPrms->startBlkCopyHcCh;  /* Add start offset */
                   break;
                }
            }
        }
    }
    else
    {
        /* Allocate specific Block Copy channel if free */
        /* Array bound check */
        if((preferredChNum >= rmInitPrms->startBlkCopyHcCh) &&
           (preferredChNum < (rmInitPrms->startBlkCopyHcCh + rmInitPrms->numBlkCopyHcCh)))
        {
            i = preferredChNum - rmInitPrms->startBlkCopyHcCh;
            offset = i >> 5U;
            if(offset < UDMA_RM_BLK_COPY_HC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->blkCopyHcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->blkCopyHcChFlag[offset] &= ~bitMask;
                   chNum = preferredChNum;
                }
            }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return (chNum);
}

void Udma_rmFreeBlkCopyHcCh(uint32_t chNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if((chNum >= (rmInitPrms->startBlkCopyHcCh))
    &&(chNum < (rmInitPrms->startBlkCopyHcCh + rmInitPrms->numBlkCopyHcCh)))
    {
        i = chNum - rmInitPrms->startBlkCopyHcCh;
        offset = i >> 5U;
        if(offset < UDMA_RM_BLK_COPY_HC_CH_ARR_SIZE)
        {
          bitPos = i - (offset << 5U);
          bitMask = (uint32_t) 1U << bitPos;
          if((drvHandle->blkCopyHcChFlag[offset] & bitMask) == 0U)
          {
            drvHandle->blkCopyHcChFlag[offset] |= bitMask;
          }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return;
}

uint32_t Udma_rmAllocBlkCopyUhcCh(uint32_t preferredChNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    uint32_t            chNum = UDMA_DMA_CH_INVALID;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if(UDMA_DMA_CH_ANY == preferredChNum)
    {
        /* Search and allocate from Blk Copy ultra high capacity channel pool */
        for(i = 0U; i < rmInitPrms->numBlkCopyUhcCh; i++)
        {
            offset = i >> 5U;
            if(offset < UDMA_RM_BLK_COPY_UHC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->blkCopyUhcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->blkCopyUhcChFlag[offset] &= ~bitMask;
                   chNum = i + rmInitPrms->startBlkCopyUhcCh;  /* Add start offset */
                   break;
                }
            }
        }
    }
    else
    {
        /* Allocate specific Block Copy channel if free */
        /* Array bound check */
        if((preferredChNum >= rmInitPrms->startBlkCopyUhcCh) &&
           (preferredChNum < (rmInitPrms->startBlkCopyUhcCh + rmInitPrms->numBlkCopyUhcCh)))
        {
            i = preferredChNum - rmInitPrms->startBlkCopyUhcCh;
            offset = i >> 5U;
            if(offset < UDMA_RM_BLK_COPY_UHC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->blkCopyUhcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->blkCopyUhcChFlag[offset] &= ~bitMask;
                   chNum = preferredChNum;
                }
            }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return (chNum);
}

void Udma_rmFreeBlkCopyUhcCh(uint32_t chNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if((chNum >= (rmInitPrms->startBlkCopyUhcCh))
    &&(chNum < (rmInitPrms->startBlkCopyUhcCh + rmInitPrms->numBlkCopyUhcCh)))
    {
        i = chNum - rmInitPrms->startBlkCopyUhcCh;
        offset = i >> 5U;
        if(offset < UDMA_RM_BLK_COPY_UHC_CH_ARR_SIZE)
        {
          bitPos = i - (offset << 5U);
          bitMask = (uint32_t) 1U << bitPos;
          if((drvHandle->blkCopyUhcChFlag[offset] & bitMask) == 0U)
          {
            drvHandle->blkCopyUhcChFlag[offset] |= bitMask;
          }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return;
}

uint32_t Udma_rmAllocCh(uint32_t preferredChNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    uint32_t chNum;
    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    /* Allocate specific TX/RX channel if free */
    /* Array bound check */

    if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
    {
        if((preferredChNum >= 0U) &&
        (preferredChNum <= UDMA_SOC_PKTDMA_TOTAL_TX_RX_CHAN))
        {
            i = preferredChNum;
            offset = i >> 5U;
            if(offset < UDMA_RM_TX_RX_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->pktDmaChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->pktDmaChFlag[offset] &= ~bitMask;
                }
            }
            chNum = preferredChNum;
        }
        else
        {
            chNum = UDMA_DMA_CH_INVALID;
        }
    }
    else
    {
        if((preferredChNum >= 0U) &&
        (preferredChNum <= UDMA_SOC_BCDMA_TOTAL_TX_RX_CHAN))
        {
            i = preferredChNum;
            offset = i >> 5U;
            if(offset < UDMA_RM_TX_RX_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->bcDmaChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->bcDmaChFlag[offset] &= ~bitMask;
                }
            }
            chNum = preferredChNum;
        }
        else
        {
            chNum = UDMA_DMA_CH_INVALID;
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return (chNum);
}

void Udma_rmFreeCh(uint32_t chNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
    {
        if((chNum >= 0U) && (chNum < UDMA_SOC_PKTDMA_TOTAL_TX_RX_CHAN))
        {
            i = chNum;
            offset = i >> 5U;
            if(offset < UDMA_RM_TX_RX_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->pktDmaChFlag[offset] & bitMask) == 0U)
                {
                  drvHandle->pktDmaChFlag[offset] |= bitMask;
                }
            }
        }
    }
    else
    {
        if((chNum >= 0U) && (chNum < UDMA_SOC_BCDMA_TOTAL_TX_RX_CHAN))
        {
            i = chNum;
            offset = i >> 5U;
            if(offset < UDMA_RM_TX_RX_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->bcDmaChFlag[offset] & bitMask) == 0U)
                {
                  drvHandle->bcDmaChFlag[offset] |= bitMask;
                }
            }
        }
    }
    
    SemaphoreP_post(&drvHandle->rmLockObj);

    return;
}

uint32_t Udma_rmAllocTxHcCh(uint32_t preferredChNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    uint32_t            chNum = UDMA_DMA_CH_INVALID;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if(UDMA_DMA_CH_ANY == preferredChNum)
    {
        /* Search and allocate from TX HC channel pool */
        for(i = 0U; i < rmInitPrms->numTxHcCh; i++)
        {
            offset = i >> 5U;
            if(offset < UDMA_RM_TX_HC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->txHcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->txHcChFlag[offset] &= ~bitMask;
                   chNum = i + rmInitPrms->startTxHcCh;  /* Add start offset */
                   break;
                }
            }
        }
    }
    else
    {
        /* Allocate specific TX HC channel if free */
        /* Array bound check */
        if((preferredChNum >= rmInitPrms->startTxHcCh) &&
           (preferredChNum < (rmInitPrms->startTxHcCh + rmInitPrms->numTxHcCh)))
        {
            i = preferredChNum - rmInitPrms->startTxHcCh;
            offset = i >> 5U;
            if(offset < UDMA_RM_TX_HC_CH_ARR_SIZE)
            {
               bitPos = i - (offset << 5U);
               bitMask = (uint32_t) 1U << bitPos;
               if((drvHandle->txHcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->txHcChFlag[offset] &= ~bitMask;
                   chNum = preferredChNum;
                }
            }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return (chNum);
}

void Udma_rmFreeTxHcCh(uint32_t chNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if((chNum >= (rmInitPrms->startTxHcCh))
      && (chNum < (rmInitPrms->startTxHcCh + rmInitPrms->numTxHcCh)))
    {
        i = chNum - rmInitPrms->startTxHcCh;
        offset = i >> 5U;
        if(offset < UDMA_RM_TX_HC_CH_ARR_SIZE)
        {
          bitPos = i - (offset << 5U);
          bitMask = (uint32_t) 1U << bitPos;
          if((drvHandle->txHcChFlag[offset] & bitMask) == 0U)
          {
            drvHandle->txHcChFlag[offset] |= bitMask;
          }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return;
}

uint32_t Udma_rmAllocRxHcCh(uint32_t preferredChNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    uint32_t            chNum = UDMA_DMA_CH_INVALID;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if(UDMA_DMA_CH_ANY == preferredChNum)
    {
        /* Search and allocate from RX HC channel pool */
        for(i = 0U; i < rmInitPrms->numRxHcCh; i++)
        {
            offset = i >> 5U;
            if(offset < UDMA_RM_RX_HC_CH_ARR_SIZE)
            {
               bitPos = i - (offset << 5U);
               bitMask = (uint32_t) 1U << bitPos;
               if((drvHandle->rxHcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->rxHcChFlag[offset] &= ~bitMask;
                   chNum = i + rmInitPrms->startRxHcCh;  /* Add start offset */
                   break;
                }
            }
        }
    }
    else
    {
        /* Allocate specific RX HC channel if free */
        /* Array bound check */
        if((preferredChNum >= rmInitPrms->startRxHcCh) &&
           (preferredChNum < (rmInitPrms->startRxHcCh + rmInitPrms->numRxHcCh)))
        {
            i = preferredChNum - rmInitPrms->startRxHcCh;
            offset = i >> 5U;
            if(offset < UDMA_RM_RX_HC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->rxHcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->rxHcChFlag[offset] &= ~bitMask;
                   chNum = preferredChNum;
                }
            }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return (chNum);
}

void Udma_rmFreeRxHcCh(uint32_t chNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if((chNum >= rmInitPrms->startRxHcCh) 
      && (chNum < (rmInitPrms->startRxHcCh + rmInitPrms->numRxHcCh)))
    {
       i = chNum - rmInitPrms->startRxHcCh;
       offset = i >> 5U;
       if(offset < UDMA_RM_RX_HC_CH_ARR_SIZE)
        {
          bitPos = i - (offset << 5U);
          bitMask = (uint32_t) 1U << bitPos;
          if((drvHandle->rxHcChFlag[offset] & bitMask) == 0U)
          {
            drvHandle->rxHcChFlag[offset] |= bitMask;
          }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return;
}

uint32_t Udma_rmAllocTxUhcCh(uint32_t preferredChNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    uint32_t            chNum = UDMA_DMA_CH_INVALID;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if(UDMA_DMA_CH_ANY == preferredChNum)
    {
        /* Search and allocate from TX UHC channel pool */
        for(i = 0U; i < rmInitPrms->numTxUhcCh; i++)
        {
            offset = i >> 5U;
            if(offset < UDMA_RM_TX_UHC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->txUhcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->txUhcChFlag[offset] &= ~bitMask;
                   chNum = i + rmInitPrms->startTxUhcCh;  /* Add start offset */
                   break;
                }
            }
        }
    }
    else
    {
        /* Allocate specific TX UHC channel if free */
        /* Array bound check */
        if((preferredChNum >= rmInitPrms->startTxUhcCh) &&
           (preferredChNum < (rmInitPrms->startTxUhcCh + rmInitPrms->numTxUhcCh)))
        {
            i = preferredChNum - rmInitPrms->startTxUhcCh;
            offset = i >> 5U;
            if(offset < UDMA_RM_TX_UHC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->txUhcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->txUhcChFlag[offset] &= ~bitMask;
                   chNum = preferredChNum;
                }
            }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return (chNum);
}

void Udma_rmFreeTxUhcCh(uint32_t chNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if((chNum >= (rmInitPrms->startTxUhcCh)) 
      && (chNum < (rmInitPrms->startTxUhcCh + rmInitPrms->numTxUhcCh)))
    {
       i = chNum - rmInitPrms->startTxUhcCh;
       offset = i >> 5U;
       if(offset < UDMA_RM_TX_UHC_CH_ARR_SIZE)
        {
          bitPos = i - (offset << 5U);
          bitMask = (uint32_t) 1U << bitPos;
          if((drvHandle->txUhcChFlag[offset] & bitMask) == 0U)
          {
            drvHandle->txUhcChFlag[offset] |= bitMask;
          }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return;
}

uint32_t Udma_rmAllocRxUhcCh(uint32_t preferredChNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    uint32_t            chNum = UDMA_DMA_CH_INVALID;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if(UDMA_DMA_CH_ANY == preferredChNum)
    {
        /* Search and allocate from RX UHC channel pool */
        for(i = 0U; i < rmInitPrms->numRxUhcCh; i++)
        {
            offset = i >> 5U;
            if(offset < UDMA_RM_RX_UHC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->rxUhcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->rxUhcChFlag[offset] &= ~bitMask;
                   chNum = i + rmInitPrms->startRxUhcCh;  /* Add start offset */
                   break;
                }
            }
        }
    }
    else
    {
        /* Allocate specific RX UHC channel if free */
        /* Array bound check */
        if((preferredChNum >= rmInitPrms->startRxUhcCh) &&
           (preferredChNum < (rmInitPrms->startRxUhcCh + rmInitPrms->numRxUhcCh)))
        {
            i = preferredChNum - rmInitPrms->startRxUhcCh;
            offset = i >> 5U;
            if(offset < UDMA_RM_RX_UHC_CH_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->rxUhcChFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->rxUhcChFlag[offset] &= ~bitMask;
                   chNum = preferredChNum;
                }
            }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return (chNum);
}

void Udma_rmFreeRxUhcCh(uint32_t chNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if((chNum >= rmInitPrms->startRxUhcCh) 
      &&(chNum < (rmInitPrms->startRxUhcCh + rmInitPrms->numRxUhcCh)))
    {
        i = chNum - rmInitPrms->startRxUhcCh;
        offset = i >> 5U;
        if(offset < UDMA_RM_RX_UHC_CH_ARR_SIZE)
        {
          bitPos = i - (offset << 5U);
          bitMask = (uint32_t) 1U << bitPos;
          if((drvHandle->rxUhcChFlag[offset] & bitMask) == 0U)
          {
            drvHandle->rxUhcChFlag[offset] |= bitMask;
          }
        }
    }


    SemaphoreP_post(&drvHandle->rmLockObj);

    return;
}

uint16_t Udma_rmAllocFreeRing(Udma_DrvHandleInt drvHandle)
{
    uint16_t            ringNum = UDMA_RING_INVALID;

    return (ringNum);
}

void Udma_rmFreeFreeRing(uint32_t ringNum, Udma_DrvHandleInt drvHandle)
{
    return;
}

uint32_t Udma_rmAllocIrIntr(uint32_t preferredIrIntrNum,
                            Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    uint32_t            irIntrNum = UDMA_INTR_INVALID;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if(UDMA_CORE_INTR_ANY == preferredIrIntrNum)
    {
        /* Search and allocate from pool */
        for(i = rmInitPrms->startIrIntr; 
            i < (rmInitPrms->startIrIntr + rmInitPrms->numIrIntr); i++)
        {
            offset = i >> 5U;
            if(offset < UDMA_RM_IR_INTR_ARR_SIZE)
            {
                bitPos = i - (offset << 5U);
                bitMask = (uint32_t) 1U << bitPos;
                if((drvHandle->irIntrFlag[offset] & bitMask) == bitMask)
                {
                   drvHandle->irIntrFlag[offset] &= ~bitMask;
                   irIntrNum = i + rmInitPrms->startIrIntr;    /* Add start offset */
                   break;
                }
            }
        }
    }
    else
    {
        /* Allocate specific IR interrupt number if free */
        /* Array bound check */
        i = preferredIrIntrNum;
        offset = i >> 5U;
        if(offset < UDMA_RM_IR_INTR_ARR_SIZE)
        {
            bitPos = i - (offset << 5U);
            bitMask = (uint32_t) 1U << bitPos;
            if((drvHandle->irIntrFlag[offset] & bitMask) == bitMask)
            {
                drvHandle->irIntrFlag[offset] &= ~bitMask;
                irIntrNum = preferredIrIntrNum;
            }
        }
    }
    
    SemaphoreP_post(&drvHandle->rmLockObj);

    return (irIntrNum);
}

void Udma_rmFreeIrIntr(uint32_t irIntrNum, Udma_DrvHandleInt drvHandle)
{
    uint32_t            i, offset, bitPos, bitMask;
    Udma_RmInitPrms    *rmInitPrms = &drvHandle->rmInitPrms;

    SemaphoreP_pend(&drvHandle->rmLockObj, SystemP_WAIT_FOREVER);

    if((irIntrNum < (rmInitPrms->startIrIntr + rmInitPrms->numIrIntr))
      && (irIntrNum >= rmInitPrms->startIrIntr))
    {
        i = irIntrNum;
        offset = i >> 5U;
        if(offset < UDMA_RM_IR_INTR_ARR_SIZE)
        {
          bitPos = i - (offset << 5U);
          bitMask = (uint32_t) 1U << bitPos;
          if((drvHandle->irIntrFlag[offset] & bitMask) == 0U)
          {
            drvHandle->irIntrFlag[offset] |= bitMask;
          }
        }
    }

    SemaphoreP_post(&drvHandle->rmLockObj);

    return;
}

uint32_t Udma_rmTranslateIrOutput(Udma_DrvHandleInt drvHandle, uint32_t irIntrNum)
{
    uint32_t    coreIntrNum = UDMA_INTR_INVALID;

    if(drvHandle->instType != UDMA_INST_TYPE_NORMAL)
    {
        /* In case of devices, where there are no Interrupt Routers,
         * irIntrNum refers to coreIntrNum number itself. */
        coreIntrNum = irIntrNum;
    }

    return (coreIntrNum);
}

uint32_t Udma_rmTranslateCoreIntrInput(Udma_DrvHandleInt drvHandle, uint32_t coreIntrNum)
{
    uint32_t    irIntrNum = UDMA_INTR_INVALID;

    if(drvHandle->instType != UDMA_INST_TYPE_NORMAL)
    {
        /* In case of devices, where there are no Interrupt Routers,
         * coreIntrNum refers to irIntrNum number itself. */
        irIntrNum = coreIntrNum;
    }

    return (irIntrNum);
}

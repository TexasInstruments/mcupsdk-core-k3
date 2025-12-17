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
#include <drivers/soc.h>
#include <drivers/hw_include/cslr_aasrc.h>
#include <drivers/hw_include/cslr_aasrc_data_r0.h>
#include <drivers/hw_include/cslr_aasrc_data_r1.h>
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Local Function Declarations                       */
/* ========================================================================== */

/* Internal functions */
static inline int32_t AASRC_validateChOpenConfig(uint32_t chType, uint32_t chCount);
static inline int32_t AASRC_validateChConfig(AASRC_ChObj *chObj);
static inline uint32_t AASRC_setSRCControlReg(AASRC_ChCfg *chCfg);
static inline int32_t AASRC_setSRCTransferModeConfig(AASRC_ChHandle chHandle);
static int32_t AASRC_chValidateClockRatios(float clkRxFreq,
                                            float clkTxFreq,
                                            AASRC_ClockZoneConfig *inClkZoneCfg,
                                            AASRC_ClockZoneConfig *outClkZoneCfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      API Function Definitions                              */
/* ========================================================================== */

AASRC_ChHandle AASRC_chOpen(uint8_t chIdx, AASRC_Handle drvHandle)
{
    int32_t status = AASRC_SOK;

    AASRC_Config *drvCfg = NULL;
    AASRC_Object *drvObj = NULL;
    const AASRC_Attrs *attrs = NULL;
    AASRC_ChObj *chObjInt = NULL;
    AASRC_ChObj *chObj = NULL;
    AASRC_ChHandle handle = NULL;
    uint8_t virtChIdxMap[AASRC_MAX_NUM_ASRC_CHANNELS] = {0U};
    uint32_t virtChIdx = 0U; /* virtual channel index */

    /* Need contiguous channel counts, because PDMA only allows a
       contiguous channel block (first to last) */
    uint32_t availMaxContiguousChCnt = 0U;
    uint32_t availContiguousChCnt = 0U;
    int32_t availContiguousBlkStartIdx = -1;
    uint32_t reqHwChPairCnt = 0U;
    uint32_t isGrpAvailable = 0U;
    uint32_t instNum;
    uint32_t i, j;
    uint32_t chType;
    uint32_t chCount;

    if (NULL_PTR == drvHandle)
    {
        status = AASRC_EBADARGS;
    }
    else
    {
        drvCfg = (AASRC_Config *)drvHandle;
    }

    if (NULL == drvCfg)
    {
        status = AASRC_EBADARGS;
    }
    else
    {
        drvObj = drvCfg->object;
        attrs = drvCfg->attrs;
    }

    if (AASRC_SOK == status)
    {
        if (NULL != drvObj)
        {
            if (!drvObj->isOpen)
            {
                /* Driver handle is not open */
                status = AASRC_EFAIL;
            }
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }

    if (AASRC_SOK == status)
    {
        if (NULL != attrs)
        {
            instNum = attrs->instNum;
        }
        else
        {
            status = AASRC_EBADARGS;
        }
    }

    if (AASRC_SOK == status)
    {
        chObj = &gConfigAasrcChObj[instNum][chIdx];
    }

    if(NULL != chObj)
    {
        chType  = chObj->chCfg.chType;
        chCount = chObj->chCfg.chCount;
    }
    else
    {
        status = AASRC_EBADARGS;
    }

    /* Protect this region from a concurrent AASRC_chOpen */
    if (NULL_PTR != gAasrcChLockObj.lock)
    {
        SemaphoreP_pend(&gAasrcChLockObj.lockObj, SystemP_WAIT_FOREVER);
    }
    else
    {
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
    {
        status = AASRC_validateChOpenConfig(chType, chCount);
    }

    if (AASRC_SOK == status)
    {
        for (i = 0U; i < AASRC_MAX_NUM_MONO_CHANNELS; i += 2U)
        {
            /* virtChIdxMap is an AASRC_MAX_NUM_ASRC_CHANNELS(=8) element array */
            /* Attemting to make a mask of which channels are in use*/
            int8_t usgElem = gAasrcDrvState[instNum].monoChUsageArray[i];
            if ( (usgElem >= (int8_t)0) &&
                 (usgElem < (int8_t)AASRC_MAX_NUM_ASRC_CHANNELS) )
            {
                /* Making a used channel bit mask */
                virtChIdxMap[usgElem] = 1U;
                availContiguousChCnt = 0U;
            }
            else if (usgElem == (int8_t)(-1))
            {
                /* Counting unused channels, +2 because if the 0th index channel
                   (from a single AASRC channel) is not in use, then both channels
                   MUST be free */
                availContiguousChCnt += 2U;
            }
            else
            {
                /* usgElem cannot be less than -1 or more than or eq to (AASRC_MAX_NUM_ASRC_CHANNELS : 8 ) */
                status = AASRC_EINVALID_PARAMS;
                break;
            }

            if (availContiguousChCnt > availMaxContiguousChCnt)
            {
                availMaxContiguousChCnt = availContiguousChCnt;
            }
        }
    }

    if (AASRC_SOK == status)
    {
        if (availMaxContiguousChCnt < chCount)
        {
            /* not enough hardware asrc channels available */
            status = AASRC_EFAIL;
        }
    }

    if (AASRC_SOK == status)
    {
        for (i = 0U; i < AASRC_MAX_NUM_ASRC_CHANNELS; i++)
        {
            if (virtChIdxMap[i] == 0U)
            {
                /* Finding the first available virtual channel index */
                virtChIdx = i;
                break;
            }
        }
    }

    if (AASRC_SOK == status)
    {
        if (AASRC_GROUP == chType)
        {
            for (i = 0U; i < AASRC_MAX_NUM_GROUP_CHANNELS; i++)
            {
                /* Trying to find which group number is available first */
                int8_t usgGrp = gAasrcDrvState[instNum].grpUsageArray[i];
                if (usgGrp == (int8_t)(-1))
                {
                    isGrpAvailable = (1U);
                    /* Assigning the group index to the available AASRC channel index */
                    gAasrcDrvState[instNum].chState[virtChIdx].hwGroupNum = (int8_t)i;
                    /* Marking the group usage array */
                    gAasrcDrvState[instNum].grpUsageArray[i] = (int8_t)virtChIdx;
                    break;
                }
                else if ( (usgGrp < (int8_t)(-1)) ||
                          (usgGrp >= (int8_t)AASRC_MAX_NUM_ASRC_CHANNELS) )
                {
                    /* if group index is out of bounds -> error*/
                    status = AASRC_EINVALID_PARAMS;
                    break;
                }
                else
                {
                    /* Skip */
                }
            }
        }
    }

    if (AASRC_SOK == status)
    {
        if ( (0U == isGrpAvailable) && (AASRC_GROUP == chType) )
        {
            /* not enough hardware groups available */
            status = AASRC_EFAIL;
        }
    }

    /* Need to find the minimum size contiguous channel block available for the
       required channel count. We shouldn't break large contiguous blocks into
       smaller ones if the user asks for a smaller channel count. Only use bigger
       blocks if we have no choice.
       Ex:- Assume channel usage like this
       |  0 |  0 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |  2 |  2 | -1 | -1 | -1 | -1 |
         If the user asks for 2 channels, we should allocate from the 4 channel contiguous
         block, NOT from the 8 channel contiguous block
            Expected allocation:
       |  0 |  0 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |  2 |  2 |  1 |  1 | -1 | -1 |
    */
    if (AASRC_SOK == status)
    {
        reqHwChPairCnt = (chCount / 2U) + (chCount % 2U);
        /* locate the starting index for the optimal block of channels */
        bool contiguousBlkFound = false;
        /* Loop to find the minimum size contiguous channel block available for
           the required channel count */
        for (i = (uint8_t)reqHwChPairCnt; i <= AASRC_MAX_NUM_ASRC_CHANNELS; i++)
        {
            int8_t usgElem;
            uint32_t tempContiguousChCnt = 0U;
            /*/ Reset the start index for the contiguous block */
            availContiguousBlkStartIdx = -1;
            /* Inner loop to check each channel pair for availability */
            for (j = 0U; j < AASRC_MAX_NUM_MONO_CHANNELS; j += 2U)
            {
                usgElem = gAasrcDrvState[instNum].monoChUsageArray[j];
                if (usgElem == (int8_t)(-1))
                {
                    /* Unused HW SRC */
                    if (availContiguousBlkStartIdx == -1)
                    {
                        availContiguousBlkStartIdx = (int32_t)j;
                    }
                    tempContiguousChCnt++;
                    if ((AASRC_MAX_NUM_MONO_CHANNELS - 2U) == j)
                    {
                        if (i == tempContiguousChCnt)
                        {
                            contiguousBlkFound = true;
                        }
                    }
                }
                else
                {
                    if (tempContiguousChCnt == i)
                    {
                        contiguousBlkFound = true;
                        break;
                    }
                    availContiguousBlkStartIdx = -1;
                    tempContiguousChCnt = 0U;
                }
            }
            if (contiguousBlkFound)
            {
                break;
            }
        }
    }

    if (AASRC_SOK == status)
    {
        uint32_t tempChCnt = chCount;

        /* Initialize global memory for the channel */
        AASRC_ChState *chState = &gAasrcDrvState[instNum].chState[virtChIdx];
        chState->virtChNum = virtChIdx;
        chState->hwChNum = -1;
        chState->monoChCount = (int8_t)chCount;
        chState->chMask = 0U;

        for (i = 0U; i < AASRC_MAX_NUM_MONO_CHANNELS; i++)
        {
            chState->chMap[i] = -1;
        }

        for (i = (uint8_t)availContiguousBlkStartIdx; i < AASRC_MAX_NUM_MONO_CHANNELS; i += 2U)
        {
            if (AASRC_MONO == chType)
            {
                /* Mono channels are always on the left channel of an HW AASRC channel */
                gAasrcDrvState[instNum].monoChUsageArray[i] = (int8_t)virtChIdx;

                chState->hwChNum = (int32_t)i / 2;
                chState->chMap[tempChCnt - 1U] = (int8_t)i;

                chState->chMask = (((uint32_t)1) << i);
                break;
            }
            else if (AASRC_STEREO == chType)
            {
                gAasrcDrvState[instNum].monoChUsageArray[i] = (int8_t)virtChIdx;
                gAasrcDrvState[instNum].monoChUsageArray[i + 1U] = (int8_t)virtChIdx;
                chState->hwChNum = (int32_t)i / 2;
                chState->chMap[tempChCnt - 2U] = (int8_t)i;
                chState->chMap[tempChCnt - 1U] = (((int8_t)i) + 1);
                chState->chMask = ((uint32_t)0x3) << i;
                break;
            }
            else if (AASRC_GROUP == chType)
            {
                if (tempChCnt >= 2U)
                {
                    gAasrcDrvState[instNum].monoChUsageArray[i] = (int8_t)virtChIdx;
                    gAasrcDrvState[instNum].monoChUsageArray[i + 1U] = (int8_t)virtChIdx;
                    chState->chMap[chCount - tempChCnt] = (int8_t)i;
                    chState->chMap[chCount - (tempChCnt - 1U)] = (((int8_t)i) + 1);
                    chState->chMask |= ((uint32_t)0x3) << i;
                    tempChCnt -= 2U;
                }
                else if (tempChCnt == 1U)
                {
                    gAasrcDrvState[instNum].monoChUsageArray[i] = (int8_t)virtChIdx;
                    chState->chMap[chCount - tempChCnt] = (int8_t)i;
                    chState->chMask |= ((uint32_t)1) << i;
                    break;
                }
                else
                {
                    /* Skip */
                }
            }
            else
            {
                /* Invalid channel type */
                status = AASRC_EINVALID_PARAMS;
                break;
            }
        }
    }

    if (AASRC_SOK == status)
    {
        chObjInt = &drvObj->chObj[virtChIdx];
        memcpy(&chObjInt->chCfg, &chObj->chCfg, sizeof(AASRC_ChCfg));
        chObjInt->drvHandle = drvHandle;
        chObjInt->isOpen = true;
        chObjInt->chState = &gAasrcDrvState[instNum].chState[virtChIdx];
        chObjInt->rcvObj.cbFxn = chObj->rcvObj.cbFxn;
        chObjInt->xmtObj.cbFxn = chObj->xmtObj.cbFxn;
        chObjInt->errCbFxn = chObj->errCbFxn;

        /* Create Queues to hold the application buffers. */
        chObjInt->reqQueueHandleRx = QueueP_create(&chObjInt->reqQueueObjRx);
        chObjInt->reqQueueHandleTx = QueueP_create(&chObjInt->reqQueueObjTx);

        chObjInt->rcvObj.loopjobEnable = chObj->rcvObj.loopjobEnable;
        chObjInt->rcvObj.txnLoopjob.buf = chObj->rcvObj.txnLoopjob.buf;
        chObjInt->rcvObj.txnLoopjob.sampleCount = chObj->rcvObj.txnLoopjob.sampleCount;

        chObjInt->xmtObj.loopjobEnable  = chObj->xmtObj.loopjobEnable;
        chObjInt->xmtObj.txnLoopjob.buf = chObj->xmtObj.txnLoopjob.buf;
        chObjInt->xmtObj.txnLoopjob.sampleCount = chObj->xmtObj.txnLoopjob.sampleCount;
        chObjInt->dmaChCfg = chObj->dmaChCfg;

        chObjInt->rcvObj.transaction = NULL;
        chObjInt->xmtObj.transaction = NULL;

        handle = (AASRC_ChHandle)chObjInt;
    }

    /* Protected region ends, lock released*/
    SemaphoreP_post(&gAasrcChLockObj.lockObj);

    /* No need to invoke a channelClose because resources are not allocated
       in failure situations */

    return handle;
}

AASRC_ChHandle AASRC_getChHandle(uint8_t instIdx, uint8_t chIdx)
{
    AASRC_Object *drvObj;
    AASRC_ChHandle chHandle = NULL;
    AASRC_ChObj *aasrcChObj;

    /* Check index */
    if (instIdx < gAasrcInstNum)
    {
        drvObj = gAasrcConfig[instIdx].object;

        if (NULL != drvObj)
        {
            /* Check if driver is opened */
            if (drvObj->isOpen)
            {
                /* Valid Driver Handle */
                aasrcChObj = &drvObj->chObj[chIdx];

                if (aasrcChObj->isOpen)
                {
                    /* Valid Channel Handle */
                    chHandle = (AASRC_ChHandle) aasrcChObj;
                }
            }
        }
    }
    return chHandle;
}

int32_t AASRC_chConfigInit(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *drvObj = NULL;

    if (NULL_PTR == chHandle)
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj->chState) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (!chObj->isOpen) )
    {
        /* Channel handle is not open */
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
    {
        drvCfg = (AASRC_Config *)chObj->drvHandle;
        if (NULL == drvCfg)
        {
            status = AASRC_EBADARGS;
        }
        else
        {
            drvObj = drvCfg->object;
        }
    }

    if (AASRC_SOK == status)
    {
        if (drvObj != NULL)
        {
            if (!drvObj->isOpen)
            {
                /* Driver handle is not open */
                status = AASRC_EFAIL;
            }
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }

    if (AASRC_SOK == status)
    {
        status = AASRC_validateChOpenConfig(chObj->chCfg.chType, chObj->chCfg.chCount);
    }

    if (AASRC_SOK == status)
    {
        chObj->chCfg.fifoControl.inFifoThreshold      = AASRC_DEFAULT_IN_FIFO_THRESHOLD;
        chObj->chCfg.fifoControl.outFifoThreshold     = AASRC_DEFAULT_OUT_FIFO_THRESHOLD;
        chObj->chCfg.inClkZone                        = AASRC_INPUT_CLOCK_ZONE0_IDX;
        chObj->chCfg.outClkZone                       = AASRC_OUTPUT_CLOCK_ZONE0_IDX;
        chObj->chCfg.inWordLen                        = AASRC_SAMPLE_WORD_LENGTH_24;
        chObj->chCfg.ditherEnable                     = 0U;
        chObj->chCfg.mute                             = 0U;
        chObj->chCfg.directDownSample                 = 0U;
        chObj->chCfg.attenuation                      = 0U;
        chObj->chCfg.deEmphasisMode                   = 0U;
        chObj->chCfg.groupDelay                       = AASRC_GROUP_DELAY_64;
        chObj->chCfg.outWordLen                       = AASRC_SAMPLE_WORD_LENGTH_24;
    }

    if (AASRC_SOK == status)
    {
        if (drvObj->transferMode == AASRC_TRANSFER_MODE_DMA)
        {
            status = AASRC_dmaChOpen(chObj);
        }
    }

    return status;
}


int32_t AASRC_chConfig(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *drvObj = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint32_t baseAddr;
    uint32_t regVal;
    uint32_t chNum;
    uint8_t i;

    if (NULL_PTR == chHandle)
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj->chState) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (!chObj->isOpen) )
    {
        /* Channel handle is not open */
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
    {
        drvCfg = (AASRC_Config *)chObj->drvHandle;
        if (NULL == drvCfg)
        {
            status = AASRC_EBADARGS;
        }
        else
        {
            drvObj = drvCfg->object;
            attrs = drvCfg->attrs;
        }
    }

    if (AASRC_SOK == status)
    {
        if (attrs != NULL)
        {
            baseAddr = (uint32_t)attrs->baseAddr;
        }
        else
        {
            status = AASRC_EBADARGS;
        }
    }

    if (AASRC_SOK == status)
    {
        if (drvObj != NULL)
        {
            if (!drvObj->isOpen)
            {
                /* Driver handle is not open */
                status = AASRC_EFAIL;
            }
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }

    if (AASRC_SOK == status)
    {
        status = AASRC_validateChConfig(chObj);
    }

    if (AASRC_SOK == status)
    {
        if( (NULL == chObj->rcvObj.cbFxn) || (NULL == chObj->xmtObj.cbFxn) )
        {
            status = AASRC_EBADARGS;
        }
    }

    if (AASRC_SOK == status)
    {
        switch (chObj->chCfg.chType)
        {
            case AASRC_MONO:
            case AASRC_STEREO:
                /* ----- Configuring the FIFO Control ----- */
                /* configuring the i/o fifo thresold for the ASRC channel */
                chNum = (uint32_t)(chObj->chState->hwChNum);
                CSL_REG32_FINS(baseAddr + AASRC_SRC_FIFO_CONTROL(chNum),
                            AASRC_CFG_SRC_FIFO_CONTROL_0_INFIFO_THRESHOLD,
                            chObj->chCfg.fifoControl.inFifoThreshold);
                CSL_REG32_FINS(baseAddr + AASRC_SRC_FIFO_CONTROL(chNum),
                            AASRC_CFG_SRC_FIFO_CONTROL_0_OUTFIFO_THRESHOLD,
                            chObj->chCfg.fifoControl.outFifoThreshold);
                regVal = AASRC_setSRCControlReg(&chObj->chCfg);
                /* configuring the ASRC channel's SRC control */
                CSL_REG32_WR(baseAddr + AASRC_SRC_CONTROL(chNum),
                            regVal);
                break;

            case AASRC_GROUP:
                /* ----- Configuring the Input/Output Group Select ----- */
                /* setting the bit mask for included channels for the group */
                regVal = 0U;
                for (i = 0; i < (uint8_t)chObj->chState->monoChCount; i++)
                {
                    regVal |= ((uint32_t)1) << (uint8_t)chObj->chState->chMap[i];
                }
                /* configuring the input group select */
                CSL_REG32_WR(baseAddr + AASRC_INPUT_GROUP_SELECT(chObj->chState->hwGroupNum),
                            regVal);
                /* configuring the output group select */
                CSL_REG32_WR(baseAddr + AASRC_OUTPUT_GROUP_SELECT(chObj->chState->hwGroupNum),
                            regVal);
                /* configuring the i/o fifo thresold for the ASRC group channel */
                CSL_REG32_FINS(baseAddr + AASRC_GROUP_FIFO_CONTROL(chObj->chState->hwGroupNum),
                            AASRC_CFG_GROUP_FIFO_CONTROL_0_INFIFO_THRESHOLD,
                            chObj->chCfg.fifoControl.inFifoThreshold);
                CSL_REG32_FINS(baseAddr + AASRC_GROUP_FIFO_CONTROL(chObj->chState->hwGroupNum),
                            AASRC_CFG_GROUP_FIFO_CONTROL_0_OUTFIFO_THRESHOLD,
                            chObj->chCfg.fifoControl.outFifoThreshold);
                regVal = AASRC_setSRCControlReg(&chObj->chCfg);
                /* configuring the ASRC group channel's SRC control */
                CSL_REG32_WR(baseAddr + AASRC_GROUP_SRC_CONTROL(chObj->chState->hwGroupNum),
                            regVal);
                break;

            default:
                status = AASRC_EINVALID_PARAMS;
                break;
        }
    }

    if (AASRC_SOK == status)
    {
        if (drvObj->transferMode == AASRC_TRANSFER_MODE_DMA)
        {
            status = AASRC_dmaChOpen(chObj);
        }
    }

    return status;
}

int32_t AASRC_chEnable(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *drvObj = NULL;
    const AASRC_Attrs *attrs = NULL;
    AASRC_Transaction *txn;
    uint32_t baseAddr;
    uint32_t chNum=0U;
    AASRC_ClockZoneConfig *inClkZoneCfg, *outClkZoneCfg;
    float clkRxFreq, clkTxFreq;
    bool isClkSettled;
    uint8_t inClkZone, outClkZone;

    if (NULL_PTR == chHandle)
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj->chState) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (!chObj->isOpen) )
    {
        /* Channel handle is not open */
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
    {
        drvCfg = (AASRC_Config *)chObj->drvHandle;
        if (NULL == drvCfg)
        {
            status = AASRC_EBADARGS;
        }
        else
        {
            drvObj = drvCfg->object;
            attrs = drvCfg->attrs;
        }
    }

    if (AASRC_SOK == status)
    {
        if (NULL != attrs)
        {
            baseAddr = (uint32_t)attrs->baseAddr;
        }
        else
        {
            status = AASRC_EBADARGS;
        }
    }

    if (AASRC_SOK == status)
    {
        if (NULL != drvObj)
        {
            if (!drvObj->isOpen)
            {
                /* Driver handle is not open */
                status = AASRC_EFAIL;
            }
            else
            {
                /* Clock Config */
                inClkZone = chObj->chCfg.inClkZone;
                outClkZone = chObj->chCfg.outClkZone;

                /* Validate clock zone indices are within bounds */
                if ((inClkZone >= AASRC_INPUT_CLOCK_ZONE_COUNT) ||
                    (outClkZone >= AASRC_OUTPUT_CLOCK_ZONE_COUNT))
                {
                    status = AASRC_EINVALID_PARAMS;
                }
                else
                {
                    inClkZoneCfg = &drvObj->rxClkZoneCfg[inClkZone];
                    outClkZoneCfg = &drvObj->txClkZoneCfg[outClkZone];
                }
            }
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }

    if (AASRC_SOK == status)
    {
        if (drvObj->transferMode == AASRC_TRANSFER_MODE_INTERRUPT)
        {
            /* Load the Rx transaction */
            txn = QueueP_get(chObj->reqQueueHandleRx);
            if ( txn == chObj->reqQueueHandleRx )
            {
                /* No buffers are queued. */
                if (chObj->rcvObj.loopjobEnable)
                {
                    txn = &chObj->rcvObj.txnLoopjob;
                }
                else
                {
                    status = AASRC_EFAIL;
                }
            }
            if (AASRC_SOK == status)
            {
                chObj->rcvObj.transaction = txn;
                txn->status = AASRC_TRANSFER_STATUS_LOADED;
            }

            /* Load the Tx transaction */
            txn = QueueP_get(chObj->reqQueueHandleTx);
            if (txn == chObj->reqQueueHandleTx)
            {
                /* No buffers are queued. */
                if (chObj->xmtObj.loopjobEnable)
                {
                    txn = &chObj->xmtObj.txnLoopjob;
                }
                else
                {
                    status = AASRC_EFAIL;
                }
            }
            if (AASRC_SOK == status)
            {
                chObj->xmtObj.transaction = txn;
                txn->status = AASRC_TRANSFER_STATUS_LOADED;
            }
        }
        else if (drvObj->transferMode == AASRC_TRANSFER_MODE_DMA)
        {
            /* Will not load the transaction here */
            chObj->rcvObj.transaction = NULL;
            chObj->xmtObj.transaction = NULL;
        }
        else
        {
            status = AASRC_EFAIL;
        }

        chObj->rcvObj.xferTotSampleCount = 0U;
        chObj->rcvObj.xferCurrSampleCount = 0U;
    }

    if ((AASRC_SOK == status) && (!inClkZoneCfg->overrideClkSettle))
    {
        isClkSettled = false;
        while (!isClkSettled)
        {
            status = AASRC_IsClockZoneRxSettled(chObj, &isClkSettled);
            if (AASRC_SOK != status)
            {
                break;
            }
        }
    }

    if (AASRC_SOK == status)
    {
        status = AASRC_GetClkZoneRxFrequency(chObj, &clkRxFreq);
    }

    if ((AASRC_SOK == status) && (!outClkZoneCfg->overrideClkSettle))
    {
        isClkSettled = false;
        while (!isClkSettled)
        {
            status = AASRC_IsClockZoneTxSettled(chObj, &isClkSettled);
            if (AASRC_SOK != status)
            {
                break;
            }
        }
    }

    if (AASRC_SOK == status)
    {
        status = AASRC_GetClkZoneTxFrequency(chObj, &clkTxFreq);
    }

    /* Validate clock frequencies and ratios only when override is not enabled */
    if ((AASRC_SOK == status) && (!inClkZoneCfg->overrideClkSettle) && \
        (!outClkZoneCfg->overrideClkSettle))
    {
        status = AASRC_chValidateClockRatios(clkRxFreq, clkTxFreq,
                                             inClkZoneCfg, outClkZoneCfg);
    }

    if (AASRC_SOK == status)
    {
        switch (chObj->chCfg.chType)
        {
            case AASRC_MONO:
                chNum = (uint32_t)(chObj->chState->hwChNum);
                /* configuring the enable bits in ASRC channel's SRC control */
                CSL_REG32_FINS(baseAddr + AASRC_SRC_CONTROL(chNum),
                               AASRC_CFG_SRC_CONTROL_0_CHANNEL_ENABLE,
                               0x2U);
                break;
            case AASRC_STEREO:
                chNum = (uint32_t)(chObj->chState->hwChNum);
                /* configuring the enable bits in ASRC channel's SRC control */
                CSL_REG32_FINS(baseAddr + AASRC_SRC_CONTROL(chNum),
                               AASRC_CFG_SRC_CONTROL_0_CHANNEL_ENABLE,
                               0x3U);
                break;
            case AASRC_GROUP:
                /* configuring the enable bit in ASRC group channel's SRC control */
                CSL_REG32_FINS(baseAddr + AASRC_GROUP_SRC_CONTROL(chObj->chState->hwGroupNum),
                               AASRC_CFG_GROUP_SRC_CONTROL_0_CHANNEL_ENABLE,
                               0x3U);
                break;
            default:
                status = AASRC_EINVALID_PARAMS;
                break;
        }
    }

    /* Release channel from reset */
    if (AASRC_SOK == status)
    {
        status = AASRC_setSRCTransferModeConfig(chHandle);
    }

    return status;
}

int32_t AASRC_chDisable(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *drvObj = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint32_t  baseAddr;
    uint32_t chNum;

    if (NULL_PTR == chHandle)
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj->chState) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (!chObj->isOpen) )
    {
        /* Channel handle is not open */
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
    {
        drvCfg = (AASRC_Config *)chObj->drvHandle;
        if (NULL == drvCfg)
        {
            status = AASRC_EBADARGS;
        }
        else
        {
            drvObj = drvCfg->object;
            attrs = drvCfg->attrs;
        }
    }

    if (AASRC_SOK == status)
    {
        if (attrs != NULL)
        {
            baseAddr = (uint32_t)attrs->baseAddr;
        }
        else
        {
            status = AASRC_EBADARGS;
        }
    }

    if (AASRC_SOK == status)
    {
        if (drvObj != NULL)
        {
            if (!drvObj->isOpen)
            {
                /* Driver handle is not open */
                status = AASRC_EFAIL;
            }
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }

    if (AASRC_SOK == status)
    {
        chObj->rcvObj.transaction = NULL;
        chObj->rcvObj.xferCurrSampleCount = 0U;
        chObj->xmtObj.transaction = NULL;
        chObj->xmtObj.xferCurrSampleCount = 0U;
        chObj->inFifoErrorStatus.lChannelOverflow   = 0U;
        chObj->inFifoErrorStatus.rChannelOverflow   = 0U;
        chObj->inFifoErrorStatus.lChannelUnderflow  = 0U;
        chObj->inFifoErrorStatus.rChannelUnderflow  = 0U;
        chObj->outFifoErrorStatus.lChannelOverflow  = 0U;
        chObj->outFifoErrorStatus.rChannelOverflow  = 0U;
        chObj->outFifoErrorStatus.lChannelUnderflow = 0U;
        chObj->outFifoErrorStatus.rChannelUnderflow = 0U;
    }

    if (AASRC_SOK == status)
    {
        switch (chObj->chCfg.chType)
        {
            case AASRC_MONO:
                chNum = (uint32_t)(chObj->chState->hwChNum);
                /* Configuring the enable bits in ASRC channel's SRC control */
                CSL_REG32_FINS(baseAddr + AASRC_SRC_CONTROL(chNum),
                               AASRC_CFG_SRC_CONTROL_0_CHANNEL_ENABLE,
                               0x0U);
                break;
            case AASRC_STEREO:
                chNum = (uint32_t)(chObj->chState->hwChNum);
                /* Configuring the enable bits in ASRC channel's SRC control */
                CSL_REG32_FINS(baseAddr + AASRC_SRC_CONTROL(chNum),
                               AASRC_CFG_SRC_CONTROL_0_CHANNEL_ENABLE,
                               0x0U);
                break;
            case AASRC_GROUP:
                /* Configuring the enable bit in ASRC group channel's SRC control */
                CSL_REG32_FINS(baseAddr + AASRC_GROUP_SRC_CONTROL(chObj->chState->hwGroupNum),
                               AASRC_CFG_GROUP_SRC_CONTROL_0_CHANNEL_ENABLE,
                               0x0U);
                break;
            default:
                status = AASRC_EINVALID_PARAMS;
                break;
        }
    }

    if (AASRC_SOK == status)
    {
        if (drvObj->transferMode == AASRC_TRANSFER_MODE_DMA)
        {
            /* Disable the DMA channel */
            status = AASRC_disableDmaTx(chHandle);

            if (AASRC_SOK == status)
            {
                status =  AASRC_disableDmaRx(chHandle);
            }
        }
    }

    return status;
}

int32_t AASRC_isChEnabled(AASRC_ChHandle chHandle, uint32_t *isEnabled)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *drvObj = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint32_t  baseAddr;
    uint32_t regVal = 0U;
    uint32_t chNum;
    *isEnabled = 0U;

    if (NULL_PTR == chHandle)
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj->chState) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (!chObj->isOpen) )
    {
        /* Channel handle is not open */
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
    {
        drvCfg = (AASRC_Config *)chObj->drvHandle;
        if (NULL == drvCfg)
        {
            status = AASRC_EBADARGS;
        }
        else
        {
            drvObj = drvCfg->object;
            attrs = drvCfg->attrs;
        }
    }

    if (AASRC_SOK == status)
    {
        if (attrs != NULL)
        {
            baseAddr = (uint32_t)attrs->baseAddr;
        }
        else
        {
            status = AASRC_EBADARGS;
        }
    }

    if (AASRC_SOK == status)
    {
        if (drvObj != NULL)
        {
            if (!drvObj->isOpen)
            {
                /* Driver handle is not open */
                status = AASRC_EFAIL;
            }
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }

    if (AASRC_SOK == status)
    {
        switch (chObj->chCfg.chType)
        {
            case AASRC_MONO:
                chNum = (uint32_t)(chObj->chState->hwChNum);
                /* configuring the enable bits in ASRC channel's SRC control */
                regVal = CSL_REG32_FEXT(baseAddr + AASRC_SRC_CONTROL(chNum),
                                        AASRC_CFG_SRC_CONTROL_0_CHANNEL_ENABLE);
                *isEnabled = regVal >> 1U;
                break;
            case AASRC_STEREO:
                chNum = (uint32_t)(chObj->chState->hwChNum);
                /* configuring the enable bits in ASRC channel's SRC control */
                regVal = CSL_REG32_FEXT(baseAddr + AASRC_SRC_CONTROL(chNum),
                                        AASRC_CFG_SRC_CONTROL_0_CHANNEL_ENABLE);
                *isEnabled = (regVal == 0x3U) ? 1U : 0U;
                break;
            case AASRC_GROUP:
                /* configuring the enable bit in ASRC group channel's SRC control */
                regVal = CSL_REG32_FEXT(baseAddr + AASRC_GROUP_SRC_CONTROL(chObj->chState->hwGroupNum),
                                        AASRC_CFG_GROUP_SRC_CONTROL_0_CHANNEL_ENABLE);
                *isEnabled = (regVal == 0x3U) ? 1U : 0U;
                break;
            default:
                status = AASRC_EINVALID_PARAMS;
                break;
        }
    }

    return status;
}

int32_t AASRC_chClose(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;

    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *drvObj = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint32_t instNum;
    uint8_t i;

    if (NULL_PTR == chHandle)
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj->chState) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (!chObj->isOpen) )
    {
        /* Channel handle is not open */
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
    {
        drvCfg = (AASRC_Config *)chObj->drvHandle;
        if (NULL == drvCfg)
        {
            status = AASRC_EBADARGS;
        }
        else
        {
            drvObj = drvCfg->object;
            attrs = drvCfg->attrs;
        }
    }

    if (AASRC_SOK == status)
    {
        if (NULL != attrs)
        {
            instNum = attrs->instNum;
        }
        else
        {
            status = AASRC_EBADARGS;
        }
    }

    if (AASRC_SOK == status)
    {
        if (NULL != drvObj)
        {
            if (!drvObj->isOpen)
            {
                /* Driver handle is not open */
                status = AASRC_EFAIL;
            }
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }

    /* Protect this region from a concurrent AASRC_chDisable */
    if (NULL_PTR != gAasrcChLockObj.lock)
    {
        SemaphoreP_pend(&gAasrcChLockObj.lockObj, SystemP_WAIT_FOREVER);
    }
    else
    {
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
    {
        status = AASRC_chDisable(chHandle);

    }

    if (AASRC_SOK == status)
    {
        if (drvObj->transferMode == AASRC_TRANSFER_MODE_DMA)
        {
            status = AASRC_dmaChClose(chHandle);
        }
    }

    if (AASRC_SOK == status)
    {
        for (i = 0; i < (uint8_t)chObj->chState->monoChCount; i++)
        {
            uint32_t monoChIdx = chObj->chState->chMap[i];
            gAasrcDrvState[instNum].monoChUsageArray[monoChIdx] = (int8_t)(-1);
        }
        if (AASRC_GROUP == chObj->chCfg.chType)
        {
            uint32_t hwGroupNum = chObj->chState->hwGroupNum;
            gAasrcDrvState[instNum].grpUsageArray[hwGroupNum] = (int8_t)(-1);
        }
        memset(chObj->chState, 0, sizeof(AASRC_ChState));

        chObj->isOpen = false;

        status += QueueP_delete(chObj->reqQueueHandleRx);
        status += QueueP_delete(chObj->reqQueueHandleTx);
    }

    /* Protected region ends, lock released*/
    SemaphoreP_post(&gAasrcChLockObj.lockObj);

    return status;
}

/* ========================================================================== */
/*                          Local Function Definitions                        */
/* ========================================================================== */

/* Internal functions */
static inline int32_t AASRC_validateChOpenConfig(uint32_t chType, uint32_t chCount)
{
    int32_t status = AASRC_SOK;

    switch (chType)
    {
        case AASRC_MONO:
            if (chCount != 1U)
            {
                status = AASRC_EINVALID_PARAMS;
            }
            break;
        case AASRC_STEREO:
            if (chCount != 2U)
            {
                status = AASRC_EINVALID_PARAMS;
            }
            break;
        case AASRC_GROUP:
            if ( (chCount < 2U) ||
                 (chCount > AASRC_MAX_NUM_MONO_CHANNELS) )
            {
                status = AASRC_EINVALID_PARAMS;
            }
            break;
        default:
            status = AASRC_EINVALID_PARAMS;
            break;
    }

    return status;
}

static inline int32_t AASRC_validateChConfig(AASRC_ChObj *chObj)
{
    int32_t status = AASRC_SOK;

    if (chObj->chCfg.fifoControl.inFifoThreshold > AASRC_MAX_IN_FIFO_THRESHOLD)
    {
        status = AASRC_EINVALID_PARAMS;
    }

    if (AASRC_SOK == status)
    {
        if (chObj->chCfg.fifoControl.outFifoThreshold > AASRC_MAX_OUT_FIFO_THRESHOLD)
        {
            status = AASRC_EINVALID_PARAMS;
        }
    }

    if (AASRC_SOK == status)
    {
        if ( (chObj->chCfg.inWordLen != AASRC_SAMPLE_WORD_LENGTH_24) &&
             (chObj->chCfg.inWordLen != AASRC_SAMPLE_WORD_LENGTH_20) &&
             (chObj->chCfg.inWordLen != AASRC_SAMPLE_WORD_LENGTH_18) &&
             (chObj->chCfg.inWordLen != AASRC_SAMPLE_WORD_LENGTH_16) )
        {
            status = AASRC_EINVALID_PARAMS;
        }
    }
    if (AASRC_SOK == status)
    {
        if (chObj->chCfg.ditherEnable > 1U)
        {
            status = AASRC_EINVALID_PARAMS;
        }
    }
    if (AASRC_SOK == status)
    {
        if (chObj->chCfg.mute > 1U)
        {
            status = AASRC_EINVALID_PARAMS;
        }
    }
    if (AASRC_SOK == status)
    {
        if (chObj->chCfg.directDownSample > 1U)
        {
            status = AASRC_EINVALID_PARAMS;
        }
    }
    if (AASRC_SOK == status)
    {
        if (chObj->chCfg.attenuation > AASRC_MAX_ATTENUATION)
        {
            status = AASRC_EINVALID_PARAMS;
        }
    }
    if (AASRC_SOK == status)
    {
        if (chObj->chCfg.deEmphasisMode >= AASRC_MAX_DEEMPHASIS_MODES)
        {
            status = AASRC_EINVALID_PARAMS;
        }
    }
    if (AASRC_SOK == status)
    {
        if ( (chObj->chCfg.groupDelay != AASRC_GROUP_DELAY_64) &&
             (chObj->chCfg.groupDelay != AASRC_GROUP_DELAY_32) &&
             (chObj->chCfg.groupDelay != AASRC_GROUP_DELAY_16) &&
             (chObj->chCfg.groupDelay != AASRC_GROUP_DELAY_8) )
        {
            status = AASRC_EINVALID_PARAMS;
        }
    }

    return status;
}

static inline uint32_t AASRC_setSRCControlReg(AASRC_ChCfg *chCfg)
{
    uint32_t regVal = 0U;
    uint32_t inWordLen = 0U, outWordLen = 0U;
    uint32_t groupDelay = 0U;
    if (chCfg->inWordLen == AASRC_SAMPLE_WORD_LENGTH_24)
    {
        inWordLen = 0U;
    }
    else if (chCfg->inWordLen == AASRC_SAMPLE_WORD_LENGTH_20)
    {
        inWordLen = 1U;
    }
    else if (chCfg->inWordLen == AASRC_SAMPLE_WORD_LENGTH_18)
    {
        inWordLen = 2U;
    }
    else if (chCfg->inWordLen == AASRC_SAMPLE_WORD_LENGTH_16)
    {
        inWordLen = 3U;
    }
    else
    {
        /* Invalid Input Word Length */
    }

    if (chCfg->outWordLen == AASRC_SAMPLE_WORD_LENGTH_24)
    {
        outWordLen = 0U;
    }
    else if (chCfg->outWordLen == AASRC_SAMPLE_WORD_LENGTH_20)
    {
        outWordLen = 1U;
    }
    else if (chCfg->outWordLen == AASRC_SAMPLE_WORD_LENGTH_18)
    {
        outWordLen = 2U;
    }
    else if (chCfg->outWordLen == AASRC_SAMPLE_WORD_LENGTH_16)
    {
        outWordLen = 3U;
    }
    else
    {
        /* Invalid Output Word Length */
    }

    if (chCfg->groupDelay == AASRC_GROUP_DELAY_64)
    {
        groupDelay = 0U;
    }
    else if (chCfg->groupDelay == AASRC_GROUP_DELAY_32)
    {
        groupDelay = 1U;
    }
    else if (chCfg->groupDelay == AASRC_GROUP_DELAY_16)
    {
        groupDelay = 2U;
    }
    else if (chCfg->groupDelay == AASRC_GROUP_DELAY_8)
    {
        groupDelay = 3U;
    }
    else
    {
        /* Invalid Group Delay */
    }

    regVal = CSL_FMK(AASRC_CFG_SRC_CONTROL_0_CHANNEL_ENABLE,
                     0U)                                                     |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_OUTPUT_WORD_LENGTH,
                     outWordLen)                                            |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_GROUP_DELAY,
                     groupDelay)                                            |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_DE_EMPHASIS_MODE,
                     chCfg->deEmphasisMode)                                 |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_ATTENUATION,
                     chCfg->attenuation)                                    |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_DIRECT_DOWN_SAMPLE,
                     chCfg->directDownSample)                               |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_MUTE,
                     chCfg->mute)                                           |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_DITHER_ENABLE,
                     chCfg->ditherEnable)                                   |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_INPUT_WORD_LENGTH,
                     inWordLen)                                             |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_OUTPUT_CLOCK_ZONE_SELECT,
                     (uint32_t)chCfg->outClkZone)                           |
             CSL_FMK(AASRC_CFG_SRC_CONTROL_0_INPUT_CLOCK_ZONE_SELECT,
                     (uint32_t)chCfg->inClkZone);

    return regVal;
}

static inline int32_t AASRC_setSRCTransferModeConfig(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *drvObj = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint32_t hwChMap = 0U;
    uint8_t i;
    const CSL_aasrc_cfgRegs *pReg = NULL;
    uint32_t regVal = 0U;

    if (NULL_PTR == chHandle)
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (NULL == chObj->chState) )
    {
        status = AASRC_EBADARGS;
    }

    if ( (AASRC_SOK == status) && (!chObj->isOpen) )
    {
        /* Channel handle is not open */
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
    {
        drvCfg = (AASRC_Config *)chObj->drvHandle;
        if (NULL == drvCfg)
        {
            status = AASRC_EBADARGS;
        }
        else
        {
            drvObj = drvCfg->object;
            attrs = drvCfg->attrs;
        }
    }

    if (AASRC_SOK == status)
    {
        if ((NULL != drvObj) && (NULL != attrs))
        {
            pReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
        }
        else
        {
            status = AASRC_EBADARGS;
        }
    }

    if (AASRC_SOK == status)
    {
        switch (chObj->chCfg.chType)
        {
            case AASRC_MONO:
            case AASRC_STEREO:

                for (i = 0; i < (uint8_t)chObj->chState->monoChCount; i++)
                {
                    hwChMap |= ((uint32_t)1) << (uint8_t)chObj->chState->chMap[i];
                }

                if (drvObj->transferMode == AASRC_TRANSFER_MODE_INTERRUPT)
                {
                    /* Enable AASRC hw interrupts */
                    regVal = CSL_REG32_RD(&pReg->OUTPUT_FIFO_INTERRUPT_ENABLE_SET_REGISTER);
                    regVal |= hwChMap;
                    CSL_REG32_WR(&pReg->OUTPUT_FIFO_INTERRUPT_ENABLE_SET_REGISTER,
                                regVal);

                    regVal = CSL_REG32_RD(&pReg->INPUT_FIFO_INTERRUPT_ENABLE_SET_REGISTER);
                    regVal |= hwChMap;
                    CSL_REG32_WR(&pReg->INPUT_FIFO_INTERRUPT_ENABLE_SET_REGISTER,
                                regVal);

                    regVal = CSL_REG32_RD(&pReg->ERROR_INTERRUPT_ENABLE_SET_REGISTER);
                    regVal |= hwChMap;
                    CSL_REG32_WR(&pReg->ERROR_INTERRUPT_ENABLE_SET_REGISTER,
                            regVal);
                }
                else if (drvObj->transferMode == AASRC_TRANSFER_MODE_DMA)
                {
                    /* Disable AASRC hw I/O interrupts, enable AASRC hw error interrupts */
                    regVal = CSL_REG32_RD(&pReg->OUTPUT_FIFO_INTERRUPT_ENABLE_CLEAR_REGISTER);
                    regVal |= hwChMap;
                    CSL_REG32_WR(&pReg->OUTPUT_FIFO_INTERRUPT_ENABLE_CLEAR_REGISTER,
                                regVal);

                    regVal = CSL_REG32_RD(&pReg->INPUT_FIFO_INTERRUPT_ENABLE_CLEAR_REGISTER);
                    regVal |= hwChMap;
                    CSL_REG32_WR(&pReg->INPUT_FIFO_INTERRUPT_ENABLE_CLEAR_REGISTER,
                                regVal);

                    regVal = CSL_REG32_RD(&pReg->ERROR_INTERRUPT_ENABLE_SET_REGISTER);
                    regVal |= hwChMap;
                    CSL_REG32_WR(&pReg->ERROR_INTERRUPT_ENABLE_SET_REGISTER,
                            regVal);
                    status = AASRC_dmaChEnable(chObj);
                }
                else
                {
                    status = AASRC_EFAIL;
                }
                break;

            case AASRC_GROUP:

                hwChMap = ((uint32_t)1) << (uint8_t)chObj->chState->hwGroupNum;
                if (drvObj->transferMode == AASRC_TRANSFER_MODE_INTERRUPT)
                {
                    CSL_REG32_WR(&pReg->INPUT_GROUP_INTERRUPT_ENABLE_SET_REGISTER,
                                hwChMap);
                    CSL_REG32_WR(&pReg->OUTPUT_GROUP_INTERRUPT_ENABLE_SET_REGISTER,
                                hwChMap);
                }
                else if (drvObj->transferMode == AASRC_TRANSFER_MODE_DMA)
                {
                    CSL_REG32_WR(&pReg->INPUT_GROUP_INTERRUPT_ENABLE_CLEAR_REGISTER,
                                hwChMap);
                    CSL_REG32_WR(&pReg->OUTPUT_GROUP_INTERRUPT_ENABLE_CLEAR_REGISTER,
                                hwChMap);
                    status = AASRC_dmaChEnable(chObj);
                }
                else
                {
                    status = AASRC_EFAIL;
                }
                break;

            default:
                break;
        }
    }

    return status;
}

static int32_t AASRC_chValidateClockRatios(float clkRxFreq,
                                           float clkTxFreq,
                                           AASRC_ClockZoneConfig *inClkZoneCfg,
                                           AASRC_ClockZoneConfig *outClkZoneCfg)
{
    int32_t status = AASRC_SOK;
    float clkRatio, srcFreq;

    /* Validate frequencies are non-zero */
    if ((0.0F == clkRxFreq) || (0.0F == clkTxFreq))
    {
        status = AASRC_EFAIL;
    }
    /* Validate frequencies are within supported range */
    else if ((clkRxFreq > (float)AASRC_AUDIO_CLK_FREQUENCY_MAX) ||
             (clkTxFreq > (float)AASRC_AUDIO_CLK_FREQUENCY_MAX))
    {
        status = AASRC_EFAIL;
    }
    else
    {
        /* Validate clock ratio */
        clkRatio = (clkTxFreq / clkRxFreq);

        if ((clkRatio > (float)AASRC_CLK_RATIO_MAX) ||
            (clkRatio < (1.0F / ((float)AASRC_CLK_RATIO_MAX))))
        {
            status = AASRC_EFAIL;
        }
        else
        {
            /* Validate input clock zone divider settings */
            if (inClkZoneCfg->isClkZoneDivEnable)
            {
                srcFreq = ((((float)inClkZoneCfg->clkZoneDiv) * clkRxFreq) / 1000.0F);
                if (srcFreq > (float)AASRC_CLK_SRC_MAX_FOR_DIVIDER)
                {
                    status = AASRC_EFAIL;
                }
            }

            /* Validate output clock zone divider settings */
            if ((AASRC_SOK == status) && (outClkZoneCfg->isClkZoneDivEnable))
            {
                srcFreq = ((((float)outClkZoneCfg->clkZoneDiv) * clkTxFreq) / 1000.0F);
                if (srcFreq > (float)AASRC_CLK_SRC_MAX_FOR_DIVIDER)
                {
                    status = AASRC_EFAIL;
                }
            }
        }
    }

    return status;
}

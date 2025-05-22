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
#include <kernel/dpl/ClockP.h>
#include <drivers/hw_include/cslr_aasrc.h>
#include <drivers/hw_include/cslr_aasrc_data_r0.h>
#include <drivers/hw_include/cslr_aasrc_data_r1.h>
#include <drivers/utils/utils.h>

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */

/** \brief Find base address of CSL_AASRC_DATA_STREAM_INPUT_FIFO_DATA(x) */
#define AASRC_STREAM_DATA_FIFO_REG_OFFSET   (0x00000100U)
#define AASRC_STREAM_DATA_INFIFO_REG(x)     ((uint32_t) CSL_AASRC_DATA_R1_STREAM_INPUT_FIFO_DATA_L0 + \
                                            (uint32_t) ((uint32_t) AASRC_STREAM_DATA_FIFO_REG_OFFSET * \
                                                        (uint32_t) (x)))

/** \brief Find base address of CSL_AASRC_DATA_STREAM_OUTPUT_FIFO_DATA(x) */
#define AASRC_STREAM_DATA_OUTFIFO_REG(x)    ((uint32_t) CSL_AASRC_DATA_R1_STREAM_OUTPUT_FIFO_DATA_L0 + \
                                            (uint32_t) ((uint32_t) AASRC_STREAM_DATA_FIFO_REG_OFFSET * \
                                                        (uint32_t) (x)))

/** \brief Find base address of CSL_AASRC_DATA_STREAM_INPUT_FIFO_DATA(x) */
#define AASRC_GROUP_DATA_FIFO_REG_OFFSET    (0x00000004U)
#define AASRC_GROUP_DATA_INFIFO_REG(x)      ((uint32_t) CSL_AASRC_DATA_R0_GROUP_INPUT_FIFO_DATA_L0 + \
                                             (uint32_t) ((uint32_t) AASRC_GROUP_DATA_FIFO_REG_OFFSET * \
                                                         (uint32_t) (x)))

#define AASRC_GROUP_DATA_OUTFIFO_REG(x)     ((uint32_t) CSL_AASRC_DATA_R0_GROUP_OUTPUT_FIFO_DATA_L0 + \
                                             (uint32_t) ((uint32_t) AASRC_GROUP_DATA_FIFO_REG_OFFSET * \
                                                         (uint32_t) (x)))

/* ========================================================================== */
/*                          Local Function Declarations                       */
/* ========================================================================== */

static void AASRC_StreamRxIsr(void *args);
static void AASRC_StreamTxIsr(void *args);
static void AASRC_GroupRxIsr(void *args);
static void AASRC_GroupTxIsr(void *args);
static void AASRC_ChErrorIsr(void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       API Function Definitions                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Local Function Definitions                          */
/* ========================================================================== */

int32_t AASRC_RegisterHwEventInterrupts(AASRC_Handle drvHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_Config *drvCfg = (AASRC_Config *)drvHandle;
    const AASRC_Attrs *attrs = drvCfg->attrs;
    AASRC_Object *obj = drvCfg->object;
    HwiP_Params hwiPrms;

    if(attrs->intCfg[AASRC_INFIFO_INTERUPT].intrNum != 0xFFFFFFFFU)
    {
        /* Stream Mode Receive section */
        HwiP_Params_init(&hwiPrms);
        hwiPrms.intNum      = attrs->intCfg[AASRC_INFIFO_INTERUPT].intrNum;
        hwiPrms.callback    = &AASRC_StreamRxIsr;
        hwiPrms.priority    = attrs->intCfg[AASRC_INFIFO_INTERUPT].intrPriority;
        hwiPrms.args        = drvHandle;
#if defined(__C7504__) || defined(__C7524__)
        hwiPrms.eventId = attrs->intCfg[AASRC_INFIFO_INTERUPT].evntNum +
                            AASRC_IRQ_CLEC_OFFSET;
#endif
        status = HwiP_construct(&obj->hwiObj[AASRC_INFIFO_INTERUPT], &hwiPrms);
    }

    if (AASRC_SOK == status)
    {
        if(attrs->intCfg[AASRC_OUTFIFO_INTERUPT].intrNum != 0xFFFFFFFFU)
        {
            /* Stream Mode Transmit section */
            HwiP_Params_init(&hwiPrms);
            hwiPrms.intNum      = attrs->intCfg[AASRC_OUTFIFO_INTERUPT].intrNum;
            hwiPrms.callback    = &AASRC_StreamTxIsr;
            hwiPrms.priority    = attrs->intCfg[AASRC_OUTFIFO_INTERUPT].intrPriority;
            hwiPrms.args        = drvHandle;
#if defined(__C7504__) || defined(__C7524__)
            hwiPrms.eventId = attrs->intCfg[AASRC_OUTFIFO_INTERUPT].evntNum +
                              AASRC_IRQ_CLEC_OFFSET;
#endif
            status = HwiP_construct(&obj->hwiObj[AASRC_OUTFIFO_INTERUPT], &hwiPrms);
        }
    }

    if (AASRC_SOK == status)
    {
        if(attrs->intCfg[AASRC_INGROUP_INTERUPT].intrNum != 0xFFFFFFFFU)
        {
            /* Group Mode Receive section */
            HwiP_Params_init(&hwiPrms);
            hwiPrms.intNum      = attrs->intCfg[AASRC_INGROUP_INTERUPT].intrNum;
            hwiPrms.callback    = &AASRC_GroupRxIsr;
            hwiPrms.priority    = attrs->intCfg[AASRC_INGROUP_INTERUPT].intrPriority;
            hwiPrms.args        = drvHandle;
#if defined(__C7504__) || defined(__C7524__)
            hwiPrms.eventId = attrs->intCfg[AASRC_INGROUP_INTERUPT].evntNum +
                              AASRC_IRQ_CLEC_OFFSET;
#endif
            status = HwiP_construct(&obj->hwiObj[AASRC_INGROUP_INTERUPT], &hwiPrms);
        }
    }

    if (AASRC_SOK == status)
    {
        if(attrs->intCfg[AASRC_OUTGROUP_INTERUPT].intrNum != 0xFFFFFFFFU)
        {
            /* Group Mode Transmit section */
            HwiP_Params_init(&hwiPrms);
            hwiPrms.intNum      = attrs->intCfg[AASRC_OUTGROUP_INTERUPT].intrNum;
            hwiPrms.callback    = &AASRC_GroupTxIsr;
            hwiPrms.priority    = attrs->intCfg[AASRC_OUTGROUP_INTERUPT].intrPriority;
            hwiPrms.args        = drvHandle;
#if defined(__C7504__) || defined(__C7524__)
            hwiPrms.eventId = attrs->intCfg[AASRC_OUTGROUP_INTERUPT].evntNum +
                              AASRC_IRQ_CLEC_OFFSET;
#endif
            status = HwiP_construct(&obj->hwiObj[AASRC_OUTGROUP_INTERUPT], &hwiPrms);
        }
    }

    return status;
}

int32_t AASRC_RegisterHwErrorInterrupts(AASRC_Handle drvHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_Config *drvCfg = (AASRC_Config *)drvHandle;
    const AASRC_Attrs *attrs = drvCfg->attrs;
    AASRC_Object *obj = drvCfg->object;
    HwiP_Params hwiPrms;

    if(attrs->intCfg[AASRC_ERROR_INTERUPT].intrNum != 0xFFFFFFFFU)
    {
        HwiP_Params_init(&hwiPrms);
        hwiPrms.intNum      = attrs->intCfg[AASRC_ERROR_INTERUPT].intrNum;
        hwiPrms.callback    = &AASRC_ChErrorIsr;
        hwiPrms.priority    = attrs->intCfg[AASRC_ERROR_INTERUPT].intrPriority;
        hwiPrms.args        = drvHandle;
#if defined(__C7504__) || defined(__C7524__)
        hwiPrms.eventId = attrs->intCfg[AASRC_ERROR_INTERUPT].evntNum +
                            AASRC_IRQ_CLEC_OFFSET;
#endif
        status = HwiP_construct(&obj->hwiObj[AASRC_ERROR_INTERUPT], &hwiPrms);
    }

    return status;
}

static void AASRC_StreamRxIsr(void *args)
{
    AASRC_Config *drvCfg = (AASRC_Config *)args;
    const AASRC_Attrs *attrs = drvCfg->attrs;
    AASRC_Object *obj = drvCfg->object;
    AASRC_TransferObj *xfrObj;
    AASRC_Transaction *txn;
    const CSL_aasrc_cfgRegs *pCtrlReg;
    uint32_t streamDataBaseAddr;
    uint32_t inFifoIntrRegVal, chMask, chType;
    uint32_t fifoThreshold, availSampleCount;
    uint32_t chMapIdx;
    uint32_t sampleCount = 0U;
    uint32_t wordStartIdx, wordEndIdx;
    uint32_t i, j;

    pCtrlReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
    streamDataBaseAddr = (uint32_t)attrs->streamDataBaseAddr;

    inFifoIntrRegVal = CSL_REG32_RD(&pCtrlReg->INPUT_FIFO_INTERRUPT_STATUS_ENABLED_REGISTER);

    for (i = 0U; i < AASRC_MAX_NUM_ASRC_CHANNELS; i++)
    {
        chType = obj->chObj[i].chCfg.chType;
        if (obj->chObj[i].isOpen &&
            ((AASRC_MONO == chType) || (AASRC_STEREO == chType)))
        {
            /* chMask indicates what mono channels should be active*/
            /* chMask will never be 0*/
            chMask = obj->chObj[i].chState->chMask;
            /* load the TransferObj from chObj*/
            xfrObj = &(obj->chObj[i].rcvObj);
            /* load the transaction*/
            txn = xfrObj->transaction;
            if (NULL != txn)
            {
                /* & with regVal to check if the interrupt specific to this channel has fired*/
                if (chMask == (chMask & inFifoIntrRegVal))
                {
                    /* Figure out how many sample words left to write for this txn*/
                    availSampleCount = txn->sampleCount - xfrObj->xferCurrSampleCount;
                    txn->status = AASRC_TRANSFER_STATUS_STARTED;

                    if (AASRC_MONO == chType)
                    {
                        fifoThreshold = obj->chObj[i].chCfg.fifoControl.inFifoThreshold;
                        /* Figure out how many sample words to write this time*/
                        if (availSampleCount > fifoThreshold)
                        {
                            sampleCount = fifoThreshold;
                        }
                        else
                        {
                            sampleCount = availSampleCount;
                        }
                        /* Find hardware ASRC channel ID*/
                        chMapIdx = obj->chObj[i].chState->chMap[0U];
                        wordStartIdx = xfrObj->xferCurrSampleCount;
                        wordEndIdx = xfrObj->xferCurrSampleCount + sampleCount;

                        for (j = wordStartIdx; j < wordEndIdx; j++)
                        {
                            /* Writing to AASRC channel fifo*/
                            CSL_REG32_WR(streamDataBaseAddr +
                                         AASRC_STREAM_DATA_INFIFO_REG(chMapIdx),
                                         *((uint32_t *)txn->buf + j));
                            /**
                             * Add a Barrier instruction after the last write to be sure that before
                             * exiting the function, the writes have indeed done.
                             */
                            Utils_dataAndInstructionBarrier();
                        }
                    }
                    else
                    {
                        /* For stereo, driver has to write to 2 fifos*/
                        fifoThreshold = obj->chObj[i].chCfg.fifoControl.inFifoThreshold * 2U;
                        /* Figure out how many sample words to write this time*/
                        if (availSampleCount > fifoThreshold)
                        {
                            sampleCount = fifoThreshold;
                        }
                        else
                        {
                            sampleCount = availSampleCount;
                        }
                        chMapIdx = obj->chObj[i].chState->chMap[0U];
                        wordStartIdx = xfrObj->xferCurrSampleCount;
                        wordEndIdx = xfrObj->xferCurrSampleCount + sampleCount;
                        for (j = wordStartIdx; j < wordEndIdx; j += 2U)
                        {
                            /* Writing to AASRC channel's two fifos*/
                            CSL_REG32_WR(streamDataBaseAddr + \
                                        AASRC_STREAM_DATA_INFIFO_REG(chMapIdx),
                                        *((uint32_t *)txn->buf + j));
                            Utils_dataAndInstructionBarrier();
                            CSL_REG32_WR(streamDataBaseAddr + \
                                        AASRC_STREAM_DATA_INFIFO_REG(chMapIdx+1U),
                                        *((uint32_t *)txn->buf + (j+1U)));
                            Utils_dataAndInstructionBarrier();
                        }
                    }

                    /* Clear the interrupt*/
                    CSL_REG32_WR(&pCtrlReg->INPUT_FIFO_INTERRUPT_STATUS_ENABLED_REGISTER, chMask);

                    xfrObj->xferCurrSampleCount += sampleCount;
                    xfrObj->xferTotSampleCount += sampleCount;

                    if (xfrObj->xferCurrSampleCount >= (txn->sampleCount))
                    {
                        txn->status = AASRC_TRANSFER_STATUS_COMPLETED;

                        /* Check if transaction is loobjob */
                        if(txn == &xfrObj->txnLoopjob)
                        {
                            /* Skip callback for loopjob transaction */
                        }
                        else
                        {
                            xfrObj->cbFxn((AASRC_ChHandle)(&obj->chObj[i]), txn);
                        }

                        AASRC_Transaction *newTxn = QueueP_get(obj->chObj[i].reqQueueHandleRx);
                        if(newTxn == (AASRC_Transaction *)obj->chObj[i].reqQueueHandleRx)
                        {
                            /** Queue is empty
                              * Load the loobjob transaction */

                            if(xfrObj->loopjobEnable)
                            {
                                newTxn = &xfrObj->txnLoopjob;
                            }
                            else
                            {
                                /* Repeat the current transaction */
                                newTxn = txn;
                            }
                        }
                        obj->chObj[i].rcvObj.transaction = newTxn;
                        obj->chObj[i].rcvObj.xferCurrSampleCount = 0U;
                        newTxn->status = AASRC_TRANSFER_STATUS_LOADED;
                    }
                }
            }
            else
            {
                AASRC_Transaction *newTxn = QueueP_get(obj->chObj[i].reqQueueHandleRx);
                if (newTxn != obj->chObj[i].reqQueueHandleRx)
                {
                    /* Queue is not empty*/
                    obj->chObj[i].rcvObj.transaction = newTxn;
                    obj->chObj[i].rcvObj.xferCurrSampleCount = 0U;
                    newTxn->status = AASRC_TRANSFER_STATUS_LOADED;
                }
                CSL_REG32_WR(&pCtrlReg->INPUT_FIFO_INTERRUPT_STATUS_ENABLED_REGISTER, chMask);
            }
        }
    }
    CSL_REG32_WR(&pCtrlReg->IRQ_EOI_REGISTER, AASRC_INFIFO_INTERUPT);
}

static void AASRC_StreamTxIsr(void *args)
{
    AASRC_Config *drvCfg = (AASRC_Config *)args;
    const AASRC_Attrs *attrs = drvCfg->attrs;
    AASRC_Object *obj = drvCfg->object;
    AASRC_TransferObj *xfrObj;
    AASRC_Transaction *txn;
    const CSL_aasrc_cfgRegs *pCtrlReg;
    uint32_t streamDataBaseAddr;
    uint32_t outFifoIntrRegVal, chMask, chType;
    uint32_t fifoThreshold, availSampleCount;
    uint32_t chMapIdx;
    uint32_t sampleCount = 0U;
    uint32_t wordStartIdx, wordEndIdx;
    uint32_t i, j;

    pCtrlReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
    streamDataBaseAddr = (uint32_t)attrs->streamDataBaseAddr;

    outFifoIntrRegVal = CSL_REG32_RD(&pCtrlReg->OUTPUT_FIFO_INTERRUPT_STATUS_ENABLED_REGISTER);

    for (i = 0U; i < AASRC_MAX_NUM_ASRC_CHANNELS; i++)
    {
        chType = obj->chObj[i].chCfg.chType;
        if (obj->chObj[i].isOpen &&
            ((AASRC_MONO == chType) || (AASRC_STEREO == chType)))
        {
            /* chMask indicates what mono channels should be active*/
            /* chMask will never be 0*/
            chMask = obj->chObj[i].chState->chMask;
            /* load the TransferObj from chObj*/
            xfrObj = &(obj->chObj[i].xmtObj);

            /* load the transaction*/
            txn = xfrObj->transaction;
            if (NULL != txn)
            {
                /* & with regVal to check if the interrupt specific to this channel has fired*/
                if (chMask == (chMask & outFifoIntrRegVal))
                {
                    /* Figure out how many sample words left to write for this txn*/
                    availSampleCount = txn->sampleCount - xfrObj->xferCurrSampleCount;
                    txn->status = AASRC_TRANSFER_STATUS_STARTED;

                    if (AASRC_MONO == chType)
                    {
                        fifoThreshold = obj->chObj[i].chCfg.fifoControl.outFifoThreshold;
                        /* Figure out how many sample words to write this time*/
                        if (availSampleCount > fifoThreshold)
                        {
                            sampleCount = fifoThreshold;
                        }
                        else
                        {
                            sampleCount = availSampleCount;
                        }
                        /* Find hardware ASRC channel ID*/
                        chMapIdx = obj->chObj[i].chState->chMap[0U];
                        wordStartIdx = xfrObj->xferCurrSampleCount;
                        wordEndIdx = xfrObj->xferCurrSampleCount + sampleCount;

                        for (j = wordStartIdx; j < wordEndIdx; j++)
                        {
                            *((uint32_t *)txn->buf + j) = CSL_REG32_RD(streamDataBaseAddr + \
                                                            AASRC_STREAM_DATA_OUTFIFO_REG(chMapIdx));
                        }
                    }
                    else
                    {
                        /* For stereo, driver has to write to 2 fifos*/
                        fifoThreshold = obj->chObj[i].chCfg.fifoControl.outFifoThreshold * 2U;
                        /* Figure out how many sample words to write this time*/
                        if (availSampleCount > fifoThreshold)
                        {
                            sampleCount = fifoThreshold;
                        }
                        else
                        {
                            sampleCount = availSampleCount;
                        }
                        chMapIdx = obj->chObj[i].chState->chMap[0U];
                        wordStartIdx = xfrObj->xferCurrSampleCount;
                        wordEndIdx = xfrObj->xferCurrSampleCount + sampleCount;
                        for (j = wordStartIdx; j < wordEndIdx; j += 2U)
                        {
                            *((uint32_t *)txn->buf + j) = CSL_REG32_RD(streamDataBaseAddr + \
                                                            AASRC_STREAM_DATA_OUTFIFO_REG(chMapIdx));
                            *((uint32_t *)txn->buf + (j+1U)) = CSL_REG32_RD(streamDataBaseAddr + \
                                                                AASRC_STREAM_DATA_OUTFIFO_REG(chMapIdx+1U));
                        }
                    }

                    /* Clear the interrupt*/
                    CSL_REG32_WR(&pCtrlReg->OUTPUT_FIFO_INTERRUPT_STATUS_ENABLED_REGISTER, chMask);

                    xfrObj->xferCurrSampleCount += sampleCount;
                    xfrObj->xferTotSampleCount += sampleCount;

                    if (xfrObj->xferCurrSampleCount >= (txn->sampleCount))
                    {
                        txn->status = AASRC_TRANSFER_STATUS_COMPLETED;

                        /* Check if transaction is loobjob */
                        if(txn == &xfrObj->txnLoopjob)
                        {
                            /* Skip callback for loopjob transaction */
                        }
                        else
                        {
                            xfrObj->cbFxn((AASRC_ChHandle)(&obj->chObj[i]), txn);
                        }

                        AASRC_Transaction *newTxn = QueueP_get(obj->chObj[i].reqQueueHandleTx);
                        if (newTxn == (AASRC_Transaction *)obj->chObj[i].reqQueueHandleTx)
                        {
                            /** Queue is empty
                              * Load the loobjob transaction */

                            if(xfrObj->loopjobEnable)
                            {
                                newTxn = &xfrObj->txnLoopjob;
                            }
                            else
                            {
                                /* Repeat the current transaction */
                                newTxn = txn;
                            }
                        }
                        obj->chObj[i].xmtObj.transaction = newTxn;
                        obj->chObj[i].xmtObj.xferCurrSampleCount = 0U;
                        newTxn->status = AASRC_TRANSFER_STATUS_LOADED;
                    }
                }
            }
            else
            {
                AASRC_Transaction *newTxn = QueueP_get(obj->chObj[i].reqQueueHandleTx);
                if (newTxn != obj->chObj[i].reqQueueHandleTx)
                {
                    /* Queue is not empty*/
                    obj->chObj[i].xmtObj.transaction = newTxn;
                    obj->chObj[i].xmtObj.xferCurrSampleCount = 0U;
                    newTxn->status = AASRC_TRANSFER_STATUS_LOADED;
                }
                CSL_REG32_WR(&pCtrlReg->OUTPUT_FIFO_INTERRUPT_STATUS_ENABLED_REGISTER, chMask);
            }
        }
    }
    CSL_REG32_WR(&pCtrlReg->IRQ_EOI_REGISTER, AASRC_OUTFIFO_INTERUPT);
}

static void AASRC_GroupRxIsr(void *args)
{
    AASRC_Config *drvCfg = (AASRC_Config *)args;
    const AASRC_Attrs *attrs = drvCfg->attrs;
    AASRC_Object *obj = drvCfg->object;
    AASRC_TransferObj *xfrObj;
    AASRC_Transaction *txn;
    const CSL_aasrc_cfgRegs *pCtrlReg;
    uint32_t groupDataBaseAddr;
    uint32_t inGrpFifoIntrRegVal, chType;
    uint32_t fifoThreshold, availSampleCount;
    uint32_t grpIdxMask, chMapIdx;
    uint32_t sampleCount, wordStartIdx, wordEndIdx;
    uint32_t i, j, k;

    pCtrlReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
    groupDataBaseAddr = (uint32_t)attrs->groupDataBaseAddr;

    inGrpFifoIntrRegVal = CSL_REG32_RD(&pCtrlReg->INPUT_GROUP_INTERRUPT_STATUS_ENABLED_REGISTER);

    for (i = 0U; i < AASRC_MAX_NUM_ASRC_CHANNELS; i++)
    {
        chType = obj->chObj[i].chCfg.chType;
        if (obj->chObj[i].isOpen && (AASRC_GROUP == chType))
        {
            /* grpIdxMask indicates which group index is this*/
            /* grpIdxMask will never be 0*/
            grpIdxMask = (uint32_t)1 << (uint8_t)obj->chObj[i].chState->hwGroupNum;
            /* load the TransferObj from chObj*/
            xfrObj = &(obj->chObj[i].rcvObj);
            /* load the transaction*/
            txn = xfrObj->transaction;
            if (NULL != txn)
            {
                /* & with regVal to check if the interrupt specific to this channel has fired*/
                if (grpIdxMask == (grpIdxMask & inGrpFifoIntrRegVal))
                {
                    /* Figure out how many sample words left to write for this txn*/
                    availSampleCount = txn->sampleCount - xfrObj->xferCurrSampleCount;
                    txn->status = AASRC_TRANSFER_STATUS_STARTED;
                    fifoThreshold = obj->chObj[i].chCfg.fifoControl.inFifoThreshold * \
                                        obj->chObj[i].chCfg.chCount;
                    /* Figure out how many sample words to write this time*/
                    if (availSampleCount > fifoThreshold)
                    {
                        sampleCount = fifoThreshold;
                    }
                    else
                    {
                        sampleCount = availSampleCount;
                    }
                    wordStartIdx = xfrObj->xferCurrSampleCount;
                    wordEndIdx = xfrObj->xferCurrSampleCount + sampleCount;

                    for (j = wordStartIdx; j < wordEndIdx; j += obj->chObj[i].chCfg.chCount)
                    {
                        for (k = 0U; k < (uint32_t)obj->chObj[i].chState->monoChCount; k++)
                        {
                            /* Writing to AASRC group channel's fifos*/
                            chMapIdx = obj->chObj[i].chState->chMap[k];
                            CSL_REG32_WR(groupDataBaseAddr + \
                                        AASRC_GROUP_DATA_INFIFO_REG(chMapIdx),
                                        *((uint32_t *)txn->buf + (j+k)));
                            Utils_dataAndInstructionBarrier();
                        }
                    }

                    /* Clear the interrupt*/
                    CSL_REG32_WR(&pCtrlReg->INPUT_GROUP_INTERRUPT_STATUS_ENABLED_REGISTER, grpIdxMask);

                    xfrObj->xferCurrSampleCount += sampleCount;
                    xfrObj->xferTotSampleCount += sampleCount;

                    if (xfrObj->xferCurrSampleCount >= txn->sampleCount)
                    {
                        txn->status = AASRC_TRANSFER_STATUS_COMPLETED;

                        /* Check if transaction is loobjob */
                        if(txn == &xfrObj->txnLoopjob)
                        {
                            /* Skip callback for loopjob transaction */
                        }
                        else
                        {
                            xfrObj->cbFxn((AASRC_ChHandle)(&obj->chObj[i]), txn);
                        }

                        AASRC_Transaction *newTxn = QueueP_get(obj->chObj[i].reqQueueHandleRx);
                        if (newTxn == (AASRC_Transaction *)obj->chObj[i].reqQueueHandleRx)
                        {
                            /** Queue is empty
                              * Load the loobjob transaction */

                            if(xfrObj->loopjobEnable)
                            {
                                newTxn = &xfrObj->txnLoopjob;
                            }
                            else
                            {
                                /* Repeat the current transaction */
                                newTxn = txn;
                            }
                        }
                        obj->chObj[i].rcvObj.transaction = newTxn;
                        obj->chObj[i].rcvObj.xferCurrSampleCount = 0U;
                        newTxn->status = AASRC_TRANSFER_STATUS_LOADED;
                    }
                }
            }
            else
            {
                AASRC_Transaction *newTxn = QueueP_get(obj->chObj[i].reqQueueHandleRx);
                if (newTxn != obj->chObj[i].reqQueueHandleRx)
                {
                    /* Queue is not empty*/
                    obj->chObj[i].rcvObj.transaction = newTxn;
                    obj->chObj[i].rcvObj.xferCurrSampleCount = 0U;
                    newTxn->status = AASRC_TRANSFER_STATUS_LOADED;
                }
                CSL_REG32_WR(&pCtrlReg->INPUT_GROUP_INTERRUPT_STATUS_ENABLED_REGISTER, grpIdxMask);
            }
        }
    }
    CSL_REG32_WR(&pCtrlReg->IRQ_EOI_REGISTER, AASRC_INGROUP_INTERUPT);
}

static void AASRC_GroupTxIsr(void *args)
{
    AASRC_Config *drvCfg = (AASRC_Config *)args;
    const AASRC_Attrs *attrs = drvCfg->attrs;
    AASRC_Object *obj = drvCfg->object;
    AASRC_TransferObj *xfrObj;
    AASRC_Transaction *txn;
    const CSL_aasrc_cfgRegs *pCtrlReg;
    uint32_t groupDataBaseAddr;
    uint32_t outGrpFifoIntrRegVal, chType;
    uint32_t fifoThreshold, availSampleCount;
    uint32_t grpIdxMask, chMapIdx;
    uint32_t sampleCount, wordStartIdx, wordEndIdx;
    uint32_t i, j, k;

    pCtrlReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
    groupDataBaseAddr = (uint32_t)attrs->groupDataBaseAddr;

    outGrpFifoIntrRegVal = CSL_REG32_RD(&pCtrlReg->OUTPUT_GROUP_INTERRUPT_STATUS_ENABLED_REGISTER);
    for (i = 0U; i < AASRC_MAX_NUM_ASRC_CHANNELS; i++)
    {
        chType = obj->chObj[i].chCfg.chType;
        if (obj->chObj[i].isOpen && (AASRC_GROUP == chType))
        {
            /* grpIdxMask indicates which group index is this*/
            /* grpIdxMask will never be 0*/
            grpIdxMask = (uint32_t)1 << (uint8_t)obj->chObj[i].chState->hwGroupNum;
            /* load the TransferObj from chObj*/
            xfrObj = &(obj->chObj[i].xmtObj);
            /* load the transaction*/
            txn = xfrObj->transaction;
            if (NULL != txn)
            {
                /* & with regVal to check if the interrupt specific to this channel has fired*/
                if (grpIdxMask == (grpIdxMask & outGrpFifoIntrRegVal))
                {
                    /* Figure out how many sample words left to write for this txn*/
                    availSampleCount = txn->sampleCount - xfrObj->xferCurrSampleCount;
                    txn->status = AASRC_TRANSFER_STATUS_STARTED;
                    fifoThreshold = obj->chObj[i].chCfg.fifoControl.outFifoThreshold * \
                                       obj->chObj[i].chCfg.chCount;
                    /* Figure out how many sample words to write this time*/
                    if (availSampleCount > fifoThreshold)
                    {
                        sampleCount = fifoThreshold;
                    }
                    else
                    {
                        sampleCount = availSampleCount;
                    }
                    wordStartIdx = xfrObj->xferCurrSampleCount;
                    wordEndIdx = xfrObj->xferCurrSampleCount + sampleCount;

                    for (j = wordStartIdx; j < wordEndIdx; j += obj->chObj[i].chCfg.chCount)
                    {
                        for (k = 0U; k < (uint32_t)obj->chObj[i].chState->monoChCount; k++)
                        {
                            /* Writing to AASRC group channel's fifos*/
                            chMapIdx = obj->chObj[i].chState->chMap[k];
                            *((uint32_t *)txn->buf + (j+k)) = CSL_REG32_RD(groupDataBaseAddr + \
                                                                AASRC_GROUP_DATA_OUTFIFO_REG(chMapIdx));
                        }
                    }

                    /* Clear the interrupt*/
                    CSL_REG32_WR(&pCtrlReg->OUTPUT_GROUP_INTERRUPT_STATUS_ENABLED_REGISTER, grpIdxMask);

                    xfrObj->xferCurrSampleCount += sampleCount;
                    xfrObj->xferTotSampleCount += sampleCount;

                    if (xfrObj->xferCurrSampleCount >= txn->sampleCount)
                    {
                        txn->status = AASRC_TRANSFER_STATUS_COMPLETED;

                        /* Check if transaction is loobjob */
                        if(txn == &xfrObj->txnLoopjob)
                        {
                            /* Skip callback for loopjob transaction */
                        }
                        else
                        {
                            xfrObj->cbFxn((AASRC_ChHandle)(&obj->chObj[i]), txn);
                        }

                        AASRC_Transaction *newTxn = QueueP_get(obj->chObj[i].reqQueueHandleTx);
                        if (newTxn == (AASRC_Transaction *)obj->chObj[i].reqQueueHandleTx)
                        {
                            /** Queue is empty
                              * Load the loobjob transaction */
                            if(xfrObj->loopjobEnable)
                            {
                                newTxn = &xfrObj->txnLoopjob;
                            }
                            else
                            {
                                /* Repeat the current transaction */
                                newTxn = txn;
                            }
                        }
                        obj->chObj[i].xmtObj.transaction = newTxn;
                        obj->chObj[i].xmtObj.xferCurrSampleCount = 0U;
                        newTxn->status = AASRC_TRANSFER_STATUS_LOADED;
                    }
                }
            }
            else
            {
                AASRC_Transaction *newTxn = QueueP_get(obj->chObj[i].reqQueueHandleTx);
                if (newTxn != obj->chObj[i].reqQueueHandleTx)
                {
                    /* Queue is not empty*/
                    obj->chObj[i].xmtObj.transaction = newTxn;
                    obj->chObj[i].xmtObj.xferCurrSampleCount = 0U;
                    newTxn->status = AASRC_TRANSFER_STATUS_LOADED;
                }
                CSL_REG32_WR(&pCtrlReg->OUTPUT_GROUP_INTERRUPT_STATUS_ENABLED_REGISTER, grpIdxMask);
            }
        }
    }
    CSL_REG32_WR(&pCtrlReg->IRQ_EOI_REGISTER, AASRC_OUTGROUP_INTERUPT);
}

static void AASRC_ChErrorIsr(void *args)
{
    AASRC_Config *drvCfg = (AASRC_Config *)args;
    const AASRC_Attrs *attrs = drvCfg->attrs;
    AASRC_Object *obj = drvCfg->object;
    AASRC_TransferObj *xfrObjRx, *xfrObjTx;
    AASRC_Transaction *txnRx, *txnTx;
    const CSL_aasrc_cfgRegs *pCtrlReg;
    uint32_t baseAddr;
    uint32_t errorIntrRegVal, chMask, chType;
    uint32_t hwChNum, hwGroupNum;
    uint32_t regVal;
    uint32_t i;

    pCtrlReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
    baseAddr = (uint32_t)attrs->baseAddr;

    errorIntrRegVal = CSL_REG32_RD(&pCtrlReg->ERROR_INTERRUPT_STATUS_ENABLED_REGISTER);
    for (i = 0U; i < AASRC_MAX_NUM_ASRC_CHANNELS; i++)
    {
        chType = obj->chObj[i].chCfg.chType;
        if (obj->chObj[i].isOpen)
        {
            /* chMask indicates what mono channels should be active*/
            /* chMask will never be 0*/
            chMask = obj->chObj[i].chState->chMask;
            /* & with regVal to check if the interrupt specific to this channel has fired*/
            if ((chMask & errorIntrRegVal) > 0U)
            {
                if (AASRC_MONO == chType)
                {
                    /* Find hardware ASRC channel ID*/
                    hwChNum = (uint32_t)(obj->chObj[i].chState->hwChNum);
                    /* Register the error condition*/
                    regVal = CSL_REG32_RD(baseAddr + AASRC_SRC_FIFO_CONTROL(hwChNum));
                    obj->chObj[i].inFifoErrorStatus.lChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].inFifoErrorStatus.lChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.lChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.lChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_UNDERFLOW_SHIFT);
                }
                else if (AASRC_STEREO == chType)
                {
                    /* Find hardware ASRC channel ID*/
                    hwChNum = (uint32_t)(obj->chObj[i].chState->hwChNum);
                    /* Register the error condition*/
                    regVal = CSL_REG32_RD(baseAddr + AASRC_SRC_FIFO_CONTROL(hwChNum));
                    obj->chObj[i].inFifoErrorStatus.lChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].inFifoErrorStatus.rChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_INFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_INFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].inFifoErrorStatus.lChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_SHIFT);
                    obj->chObj[i].inFifoErrorStatus.rChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_INFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_INFIFO_UNDERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.lChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.rChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_OUTFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_OUTFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.lChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_UNDERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.rChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_OUTFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_OUTFIFO_UNDERFLOW_SHIFT);
                }
                else if (AASRC_GROUP == chType)
                {
                    /* Find hardware group ASRC channel ID*/
                    hwGroupNum = (uint32_t)(obj->chObj[i].chState->hwGroupNum);
                    /* Register the error condition*/
                    regVal = CSL_REG32_RD(baseAddr + AASRC_GROUP_FIFO_CONTROL(hwGroupNum));
                    obj->chObj[i].inFifoErrorStatus.lChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_INFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_INFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].inFifoErrorStatus.rChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_INFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_INFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].inFifoErrorStatus.lChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_SHIFT);
                    obj->chObj[i].inFifoErrorStatus.rChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_INFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_INFIFO_UNDERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.lChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.rChannelOverflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_OUTFIFO_OVERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_OUTFIFO_OVERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.lChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_OUTFIFO_UNDERFLOW_SHIFT);
                    obj->chObj[i].outFifoErrorStatus.rChannelUnderflow = \
                        (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_OUTFIFO_UNDERFLOW_MASK) >> \
                                  CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_OUTFIFO_UNDERFLOW_SHIFT);
                }
                else
                {
                    /* Invalid Channel Type */
                }

                /* Clear the interrupt */
                CSL_REG32_WR(&pCtrlReg->ERROR_INTERRUPT_STATUS_ENABLED_REGISTER, chMask);

                xfrObjRx = &(obj->chObj[i].rcvObj);
                txnRx = xfrObjRx->transaction;
                xfrObjTx = &(obj->chObj[i].xmtObj);
                txnTx = xfrObjTx->transaction;

                if (obj->chObj[i].errCbFxn == NULL)
                {
                    AASRC_chDisable((AASRC_ChHandle)(&obj->chObj[i]));
                    AASRC_chEnable((AASRC_ChHandle)(&obj->chObj[i]));
                }
                else
                {
                    if (NULL != txnRx)
                    {
                        txnRx->status = AASRC_TRANSFER_STATUS_ERROR;
                    }
                    if (NULL != txnTx)
                    {
                        txnTx->status = AASRC_TRANSFER_STATUS_ERROR;
                    }
                    obj->chObj[i].errCbFxn((AASRC_ChHandle)(&obj->chObj[i]), txnRx, txnTx);
                }
            }
        }
    }
    CSL_REG32_WR(&pCtrlReg->IRQ_EOI_REGISTER, AASRC_ERROR_INTERUPT);
}

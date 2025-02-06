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

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Local Function Declarations                       */
/* ========================================================================== */

static int32_t AASRC_validateTransaction(AASRC_ChObj *chObj, AASRC_Transaction *transaction);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                       API Function Definitions                             */
/* ========================================================================== */

int32_t AASRC_queueTransactionRx(AASRC_ChHandle chHandle, AASRC_Transaction *transaction)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;

    if (NULL == chHandle || NULL == transaction)
    {
        status = AASRC_EBADARGS;
        if (NULL != transaction)
        {
            transaction->status = AASRC_TRANSFER_STATUS_FAILED;
        }
    }
    if (AASRC_SOK == status)
    {
        status = AASRC_validateTransaction(chObj, transaction);
    }
    if (AASRC_SOK == status)
    {
        QueueP_put(chObj->reqQueueHandleRx, transaction);
        transaction->status = AASRC_TRANSFER_STATUS_QUEUED;
    }

    return status;
}

int32_t AASRC_queueTransactionTx(AASRC_ChHandle chHandle, AASRC_Transaction *transaction)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;

    if (NULL == chHandle || NULL == transaction)
    {
        status = AASRC_EBADARGS;
        if (NULL != transaction)
        {
            transaction->status = AASRC_TRANSFER_STATUS_FAILED;
        }
    }
    if (AASRC_SOK == status)
    {
        status = AASRC_validateTransaction(chObj, transaction);
    }
    if (AASRC_SOK == status)
    {
        QueueP_put(chObj->reqQueueHandleTx, transaction);
        transaction->status = AASRC_TRANSFER_STATUS_QUEUED;
    }

    return status;
}

/* ========================================================================== */
/*                       Local Function Definitions                          */
/* ========================================================================== */

static int32_t AASRC_validateTransaction (AASRC_ChObj *chObj, AASRC_Transaction *txn)
{
    int32_t status = AASRC_SOK;
    uint8_t channel_error = 0U;

    if (1U != chObj->isOpen)
    {
        txn->status = AASRC_TRANSFER_STATUS_FAILED;
        status = AASRC_EINVALID_PARAMS;
    }
    if (AASRC_SOK == status)
    {
        if (NULL == chObj->chState)
        {
            txn->status = AASRC_TRANSFER_STATUS_FAILED;
            status = AASRC_EBADARGS;
        }
    }
    if (AASRC_SOK == status)
    {
        channel_error = chObj->inFifoErrorStatus.lChannelOverflow   |
                        chObj->inFifoErrorStatus.rChannelOverflow   |
                        chObj->inFifoErrorStatus.lChannelUnderflow  |
                        chObj->inFifoErrorStatus.rChannelUnderflow  |
                        chObj->outFifoErrorStatus.lChannelOverflow  |
                        chObj->outFifoErrorStatus.rChannelOverflow  |
                        chObj->outFifoErrorStatus.lChannelUnderflow |
                        chObj->outFifoErrorStatus.rChannelUnderflow;
        if (1U == channel_error)
        {
            txn->status = AASRC_TRANSFER_STATUS_ERROR;
            status = AASRC_EFAIL;
        }
    }
    if (AASRC_SOK == status)
    {
        if (NULL == txn->buf)
        {
            txn->status = AASRC_TRANSFER_STATUS_FAILED;
            status = AASRC_EBADARGS;
        }
    }
    if (AASRC_SOK == status)
    {
        if (0U == txn->sampleCount ||
            AASRC_MAX_TXN_WORD_COUNT < txn->sampleCount)
        {
            txn->status = AASRC_TRANSFER_STATUS_FAILED;
            status = AASRC_EINVALID_PARAMS;
        }
    }
    if (AASRC_SOK == status)
    {
        if (chObj->chCfg.chType == AASRC_STEREO)
        {
            if (0U != txn->sampleCount % 2U)
            {
                txn->status = AASRC_TRANSFER_STATUS_FAILED;
                status = AASRC_EINVALID_PARAMS;
            }
        }
        else if (chObj->chCfg.chType == AASRC_GROUP)
        {
            if (0U != txn->sampleCount % chObj->chCfg.chCount)
            {
                txn->status = AASRC_TRANSFER_STATUS_FAILED;
                status = AASRC_EINVALID_PARAMS;
            }
        }
    }
    return status;
}

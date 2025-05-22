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

/**
 *  \ingroup DRV_AASRC_MODULE
 *  \defgroup DRV_AASRC_TRANSACTIONS_MODULE AASRC Transactions
 *            This is AASRC data transfer related APIs, parameters and
 *            local functions
 *
 *  @{
 */

/**
 *  \file v0/aasrc_transactions.h
 *
 *  \brief AASRC transactions, transfer objects and parameters
 */

#ifndef AASRC_TRANSACTIONS_H_
#define AASRC_TRANSACTIONS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \anchor AASRC_TransferStatus
 *  \name Transfer Status Code
 *
 *  Status codes that are set by the AASRC driver
 *
 *  @{
 */

/** \brief I/O buffer queued and pending */
#define AASRC_TRANSFER_STATUS_QUEUED           (0U)
/** \brief I/O buffer fetched from queue, waiting for interrupt to fire */
#define AASRC_TRANSFER_STATUS_LOADED           (1U)
/** \brief I/O started processing */
#define AASRC_TRANSFER_STATUS_STARTED          (2U)
/** \brief I/O completed successfully */
#define AASRC_TRANSFER_STATUS_COMPLETED        (3U)
/** \brief I/O cancelled. Returned by incomplete read or write requests */
#define AASRC_TRANSFER_STATUS_CANCELLED        (4U)
/** \brief Generic failure condition */
#define AASRC_TRANSFER_STATUS_FAILED           (5U)
/** \brief ASRC channel has gone into an error */
#define AASRC_TRANSFER_STATUS_ERROR            (6U)
/** \brief I/O timeout occurred */
#define AASRC_TRANSFER_STATUS_TIMEOUT          (7U)
/** @} */

/**
 *  \anchor AASRC_TransferMode
 *  \name AASRC Transfer Mode
 *
 *  @{
 */
/**
 *  \brief AASRC read/write APIs does not block code execution and will call a
 *  #AASRC_TxnCallbackFxn
 *  This mode can be used in a Task, Swi, or Hwi context
 */
#define AASRC_TRANSFER_MODE_INTERRUPT           (0U)
/**
 *  \brief AASRC read/write APIs does not block code execution and will use DMA
 *  for transfers
 */
#define AASRC_TRANSFER_MODE_DMA                 (1U)
/** @} */

/* Limits the maximum number of words for an AASRC_Transaction
   This equals 2GB of data for 32 bit samples. */
#define AASRC_MAX_TXN_WORD_COUNT                (1024U*1024U*512U)

/* AASRC driver will always use 32 bit words for data read/write for aglignment,
   but the sample size can be 16, 18, 20, 24 bits */
#define AASRC_WORD_SIZE_IN_BYTES                (4U)
#define AASRC_WORD_SIZE_IN_BITS                 (32U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Data structure used with transfer call
 *
 */
typedef struct
{
    QueueP_Elem qElem;
    /**< [IN] This should be the first parameter.
     *    this is the queue element used by driver. */
    void *buf;
    /**< [IN] void * to a buffer with data to be transferred .
     *   This parameter can't be NULL */
    uint32_t sampleCount;
    /**< [IN/OUT] Number of sample words for this transaction.
      *  This is input incase of read/write call and on API return
      *  this represents number of sample words actually read by the API */
    int32_t status;
    /**< [OUT] \ref AASRC_TransferStatus code */
    void *args;
    /**< [IN] Argument to be passed to the callback function */
} AASRC_Transaction;


/**
 *  \brief  The definition of a callback function used by the AASRC driver
 *  when used in Callback Mode
 *
 *  \param chHandle        channel handle to identify AASRC channel
 *                         (returned from AASRC_chOpen())
 *  \param transaction*    Pointer to a #AASRC_Transaction
 */
typedef void (*AASRC_TxnCallbackFxn) (AASRC_ChHandle chHandle,
                                      AASRC_Transaction *transaction);

/**
 *  \brief  The definition of a channel error callback function used by the
 *  AASRC driver when used in Callback Mode.
 *
 *  \param chHandle        channel handle to identify AASRC channel
 *                         (returned from AASRC_chOpen())
 *  \param transactionRx*  Pointer to a receive #AASRC_Transaction
 *  \param transactionTx*  Pointer to a transmit #AASRC_Transaction
 */
typedef void (*AASRC_ChErrorCallbackFxn) (AASRC_ChHandle chHandle,
                                          AASRC_Transaction *transactionRx,
                                          AASRC_Transaction *transactionTx);
/**
 *  \brief AASRC Transfer Data structure stored in Channel object
 */
typedef struct
{
    uint32_t xferTotSampleCount;
    /**< AASRC RX/TX total sample word transfer count per channel.
     *   This counter will wrap around at uint32_t max boundry.
     *   This will be reset by ChEnable().
    */
    uint32_t xferCurrSampleCount;
    /**< AASRC RX/TX sample word transfer count per the current
     *   transaction. This will be reset by ChEnable().
    */
    AASRC_Transaction *transaction;
    /**< Pointer to current transaction struct */
    AASRC_TxnCallbackFxn cbFxn;
    /**< callback function provided by the app to be called by DMA or Host
     * after a transaction is complete.
     */
    AASRC_Transaction txnLoopjob;
    /**< transaction struct object for loopjob buffer */
    bool loopjobEnable;
    /*< Flag to enable loopjob. when enabled loopjob buffer is transmitted if application fails to load buffers.*/
} AASRC_TransferObj;

/* ========================================================================== */
/*                      API Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function submit transactions to AASRC input queue
 *
 *  submits transactions to AASRC input queue to be written to AASRC input fifo
 *
 *  \param chHandle                 [IN] channel handle to identify AASRC channel
 *                                       (returned from AASRC_chOpen())
 *  \param transaction*             [IN] Pointer to AASRC transaction to be queued
 *                                       in AASRC input
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_queueTransactionRx(AASRC_ChHandle chHandle, AASRC_Transaction *transaction);

/**
 *  \brief Function submit transactions to AASRC output queue
 *
 *  submits transactions to AASRC output queue to receive data from AASRC output fifo
 *
 *  \param chHandle                 [IN] channel handle to identify AASRC channel
 *                                       (returned from AASRC_chOpen())
 *  \param transaction*             [IN] Pointer to AASRC transaction to be queued
 *                                       for AASRC output
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_queueTransactionTx(AASRC_ChHandle chHandle, AASRC_Transaction *transaction);

/* ========================================================================== */
/*                       Local Function Definitions                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef AASRC_TRANSACTIONS_H_ */

/** @} */

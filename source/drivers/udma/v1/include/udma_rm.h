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
 *  \ingroup DRV_UDMA_MODULE
 *  \defgroup DRV_UDMA_RM_MODULE UDMA RM API
 *            This is UDMA driver resource manager related configuration
 *            parameters and API
 *
 *  @{
 */

/**
 *  \file udma_rm.h
 *
 *  \brief UDMA RM related parameters and API.
 */

#ifndef UDMA_RM_H_
#define UDMA_RM_H_

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

/** \brief Macro used to specify that Resource ID is invalid. */
#define UDMA_RM_RES_ID_INVALID          ((uint32_t) 0xFFFF0005U)

/** \brief Macro used to specify - reserve minimum required number of resources for an instance */
#define UDMA_RM_SHARED_RES_CNT_MIN      ((uint32_t) 0xFFFF0006U)

/** \brief Macro used to specify - reserve all the remaining unreserved resources for an instance */
#define UDMA_RM_SHARED_RES_CNT_REST     ((uint32_t) 0xFFFF0007U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief UDMA resource manager init parameters.
 *
 *  This assumes contiguos allocation of 'N' resources from a start offset
 *  to keep the interface simple.
 *
 *  Note: This is applicable for the driver handle as given during init call.
 *  The init call doesn't (can't rather) check for resource overlap across
 *  handles and across cores. It is the callers responsibility to ensure that
 *  resources overlaps are not present.
 */
typedef struct
{
    uint32_t                startBlkCopyUhcCh;
    /**< Start ultra high capacity block copy channel from which this UDMA
     *   driver instance manages */
    uint32_t                numBlkCopyUhcCh;
    /**< Number of ultra high capacity block copy channel to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_BLK_COPY_UHC_CH */
    uint32_t                startBlkCopyHcCh;
    /**< Start high capacity block copy channel from which this UDMA
     *   driver instance manages */
    uint32_t                numBlkCopyHcCh;
    /**< Number of ultra high capacity block copy channel to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_BLK_COPY_HC_CH */
    uint32_t                startBlkCopyCh;
    /**< Start Block copy channel from which this UDMA driver instance manages */
    uint32_t                numBlkCopyCh;
    /**< Number of Block copy channel to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_BLK_COPY_CH */

    uint32_t                startTxUhcCh;
    /**< Start ultra high capacity TX channel from which this UDMA driver
     *   instance manages */
    uint32_t                numTxUhcCh;
    /**< Number of ultra high capacity TX channel to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_TX_UHC_CH */
    uint32_t                startTxHcCh;
    /**< Start high capacity TX channel from which this UDMA driver instance
     *   manages */
    uint32_t                numTxHcCh;
    /**< Number of high capacity TX channel to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_TX_HC_CH */
    uint32_t                startTxCh;
    /**< Start TX channel from which this UDMA driver instance manages */
    uint32_t                numTxCh;
    /**< Number of TX channel to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_TX_CH */

    uint32_t                startRxUhcCh;
    /**< Start ultra high capacity RX channel from which this UDMA driver
     *   instance manages */
    uint32_t                numRxUhcCh;
    /**< Number of high capacity RX channel to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_RX_UHC_CH */
    uint32_t                startRxHcCh;
    /**< Start high capacity RX channel from which this UDMA driver instance
     *   manages */
    uint32_t                numRxHcCh;
    /**< Number of high capacity RX channel to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_RX_HC_CH */
    uint32_t                startRxCh;
    /**< Start RX channel from which this UDMA driver instance manages */
    uint32_t                numRxCh;
    /**< Number of RX channel to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_RX_CH */
    uint32_t                tflowCnt;
    /**< Number of TX channel flow count to be managed.*/
    uint32_t                rflowCnt;
    /**< Number of RX channel flow count to be managed.*/

    uint32_t                startFreeFlow;
    /**< Start free flow from which this UDMA driver instance manages */
    uint32_t                numFreeFlow;
    /**< Number of free flow to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_FREE_FLOW */
    uint32_t                startFreeRing;
    /**< Start free ring from which this UDMA driver instance manages */
    uint32_t                numFreeRing;
    /**< Number of free ring to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_FREE_RING */
    uint32_t                startIrIntr;
    /**< Start IR interrupt from which this UDMA driver instance manages. */
    uint32_t                numIrIntr;
    /**< Number of IR interrupts to be managed.
     *   Note: This cannot exceed UDMA_RM_MAX_IR_INTR */
} Udma_RmInitPrms;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef UDMA_RM_H_ */

/** @} */

/*
 *  Copyright (C) 2020 Texas Instruments Incorporated.
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
 *
 */
/**
 *  \file  csl_pktdma.h
 *
 *  \brief
 *  This CSL-FL header file contains various enumerations, structure
 *  definitions and function declarations for the Packet DMA (PKTDMA) IP.
 *
 *  This CSL-FL was designed to be orthogonal with the implementation
 *  of the udmap CSL-FL. Enumerations, structure definitions, and API functions
 *  are similarly named. The include file "csl_pktdma_alias_udmap_api.h" is
 *  available which maps pktdma CSL-FL content to their udmap equivalents for
 *  ease in porting existing udmap code to the pktdma.
 *
 *  There is CSL-FL content that is applicable for udmap but not for pktdma.
 *  Those items are denoted with the tag [udmap_only] in the comments below
 *  and are handled as follows:
 *    - Enumerations: The enumeration is defined, but is not used functionally
 *    - Structure definitions: The structure is defined, but is not used
 *      functionally
 *    - Structure elements: The element is defined in the structure, but
 *      is not used functionally
 *    - API functions: The function is implemented, but does no operations
 *
 *  The following is the required calling sequence in order to insure proper
 *  operation of this CSL-FL:
 *
 *    1. Allocate a PKTDMA configuration structure (#CSL_PktdmaCfg)
 *    2. (Optional) initialize the PKTDMA
 *       configuration structure to all zeros
 *    3. Initialize the register structure pointer elements of the PKTDMA
 *       configuration structure
 *    4. Call #CSL_pktdmaGetCfg to populate the PKTDMA configuration structure
 *       with configuration and capability information for the PKTDMA module
 *    5. Call the other PKTDMA API functions as required
 */
/**
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_PKTDMA PKTDMA CSL-FL
 *
 *  @{
 */

#ifndef CSL_PKTDMA_H_
#define CSL_PKTDMA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <drivers/udma/v0/include/csl_udmap_cppi5.h>
#include <drivers/udma/v0/include/csl_pktdma_cppi5.h>
#include <drivers/hw_include/cslr_pktdma.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/csl_utils.h>

/**
@defgroup CSL_PKTDMA_DATASTRUCT  PKTDMA Data Structures
@ingroup CSL_PKTDMA_API
*/
/**
@defgroup CSL_PKTDMA_FUNCTION  PKTDMA Functions
@ingroup CSL_PKTDMA_API
*/
/**
@defgroup CSL_PKTDMA_ENUM PKTDMA Enumerated Data Types
@ingroup CSL_PKTDMA_API
*/

/**
 *  \addtogroup CSL_PKTDMA_ENUM
 *  @{
 */

#define CSL_PKTDMA_NO_EVENT         ((uint32_t) 0xFFFFU)

/** ---------------------------------------------------------------------------
 * @brief This enumerator defines the possible channel directions
 *
 *  \anchor CSL_PktdmaChanDir
 *  \name PKTDMA channel direction
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
typedef uint32_t CSL_PktdmaChanDir;
    /** Transmit direction */
#define CSL_PKTDMA_CHAN_DIR_TX   ((uint32_t) 0U)
    /** Receive direction */
#define CSL_PKTDMA_CHAN_DIR_RX   ((uint32_t) 1U)
/* @} */

/** ---------------------------------------------------------------------------
 * @brief This enumerator defines the nominal burst size and alignment for
 * data transfers on a TX or RX channel
 *
 *  \anchor CSL_PktdmaChanBurstSize
 *  \name PKTDMA channel burst size
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
typedef uint32_t CSL_PktdmaChanBurstSize;
    /** 32-byte burst size */
#define CSL_PKTDMA_CHAN_BURST_SIZE_32_BYTES  ((uint32_t) 0U)
    /** 64-byte burst size */
#define CSL_PKTDMA_CHAN_BURST_SIZE_64_BYTES  ((uint32_t) 1U)
    /** 128-byte burst size */
#define CSL_PKTDMA_CHAN_BURST_SIZE_128_BYTES ((uint32_t) 2U)
    /** 256-byte burst size */
#define CSL_PKTDMA_CHAN_BURST_SIZE_256_BYTES ((uint32_t) 3U)
/* @} */

/** ---------------------------------------------------------------------------
 * @brief This enumerator defines the possible descriptor types
 *
 *  \anchor CSL_PktdmaDescType
 *  \name PKTDMA descriptor type
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
typedef uint32_t CSL_PktdmaDescType;
    /** Host */
#define CSL_PKTDMA_DESC_TYPE_HOST        ((uint32_t) 0U)
    /** Host single-buffer */
#define CSL_PKTDMA_DESC_TYPE_HOST_SB     ((uint32_t) 1U)
    /** Monolithic */
#define CSL_PKTDMA_DESC_TYPE_MONOLITHIC  ((uint32_t) 2U)
    /** Reserved */
#define CSL_PKTDMA_DESC_TYPE_RESERVED    ((uint32_t) 3U)
/* @} */

/** ---------------------------------------------------------------------------
 * @brief This enumerator defines the ps location for the descriptor
 *
 *  \anchor CSL_PktdmaPsLoc
 *  \name PKTDMA protocol-specific data location
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
typedef uint32_t CSL_PktdmaPsLoc;
    /** Located in descriptor */
#define CSL_PKTDMA_PS_LOC_DESC       ((uint32_t) 0U)
    /** Located in packet */
#define CSL_PKTDMA_PS_LOC_PACKET     ((uint32_t) 1U)
/* @} */

/** ---------------------------------------------------------------------------
 * @brief This enumerator defines the possible address types
 *
 *  \anchor CSL_PktdmaAddrType
 *  \name PKTDMA address type
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
typedef uint32_t CSL_PktdmaAddrType;
    /** Physical addressing */
#define CSL_PKTDMA_ADDR_TYPE_PHYS    ((uint32_t) 0U)
    /** Intermediate addressing */
#define CSL_PKTDMA_ADDR_TYPE_INTER   ((uint32_t) 1U)
    /** Virtual addressing */
#define CSL_PKTDMA_ADDR_TYPE_VIRT    ((uint32_t) 2U)
/* @} */

/** ---------------------------------------------------------------------------
 * @brief This enumerator defines the possible channel types
 *
 *  \anchor CSL_PktdmaChanType
 *  \name PKTDMA channel type
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
typedef uint32_t CSL_PktdmaChanType;
    /** Normal channel */
#define CSL_PKTDMA_CHAN_TYPE_NORMAL             ((uint32_t) 2U)
    /** Single buffer mode channel */
#define CSL_PKTDMA_CHAN_TYPE_SBMODE             ((uint32_t) 3U)
    /** RM, Packet Mode, Pass by reference */
#define CSL_PKTDMA_CHAN_TYPE_REF_PKT_RING       ((uint32_t) 2U)
    /** QM, Packet Single Buffer Mode, Pass by reference */
#define CSL_PKTDMA_CHAN_TYPE_REF_PKTSB_QUEUE    ((uint32_t) 3U)
/* @} */

/** ---------------------------------------------------------------------------
 * @brief This enumerator defines how tag values are determined
 *
 *  \anchor CSL_PktdmaTagSelect
 *  \name PKTDMA tag select
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
typedef uint32_t CSL_PktdmaTagSelect;
    /** Do not overwrite */
#define CSL_PKTDMA_TAG_SELECT_NO_OVERWRITE               ((uint32_t) 0U)
    /** Overwrite with value given in tag value */
#define CSL_PKTDMA_TAG_SELECT_OVERWRITE_WITH_VAL         ((uint32_t) 1U)
    /** Overwrite with flow_id[7:0] from back-end */
#define CSL_PKTDMA_TAG_SELECT_OVERWRITE_WITH_FLOWID_7_0  ((uint32_t) 2U)
    /** Overwrite with flow_id[15:8] from back-end */
#define CSL_PKTDMA_TAG_SELECT_OVERWRITE_WITH_FLOWID_15_8 ((uint32_t) 3U)
    /** Overwrite with tag[7:0] from back-end */
#define CSL_PKTDMA_TAG_SELECT_OVERWRITE_WITH_TAG_7_0     ((uint32_t) 4U)
    /** Overwrite with tag[15:8] from back-end */
#define CSL_PKTDMA_TAG_SELECT_OVERWRITE_WITH_TAG_15_8    ((uint32_t) 5U)
    /** Invalid */
#define CSL_PKTDMA_TAG_SELECT_INVALID                    ((uint32_t) 6U)
/* @} */

/** ---------------------------------------------------------------------------
 * @brief This enumerator selects which scheduling bin the channel will be
 *  placed in for bandwidth allocation of the DMA units
 *
 *  \anchor CSL_PktdmaChanSchedPri
 *  \name PKTDMA channel schedling priority
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
typedef uint32_t CSL_PktdmaChanSchedPri;
    /** High priority */
#define CSL_PKTDMA_CHAN_SCHED_PRI_HIGH       ((uint32_t) 0U)
    /** Medium-High priority */
#define CSL_PKTDMA_CHAN_SCHED_PRI_MED_HIGH   ((uint32_t) 1U)
    /** Medium-Low priority */
#define CSL_PKTDMA_CHAN_SCHED_PRI_MED_LOW    ((uint32_t) 2U)
    /** Low priority */
#define CSL_PKTDMA_CHAN_SCHED_PRI_LOW        ((uint32_t) 3U)
/* @} */

/* @} */

/**
 *  \addtogroup CSL_PKTDMA_DATASTRUCT
 *  @{
 */

/** \brief Channel runtime configuration information
 *
 *  This structure contains runtime configuration information for a channel.
 *
 */
typedef struct
{
    uint32_t                enable;               /**< [IN]  When set, enable the channel */
    uint32_t                teardown;             /**< [IN]  When set, teardown the channel */
    uint32_t                pause;                /**< [IN]  When set, pause the channel */
    uint32_t                error;                /**< [OUT] When set, an error has been detected on the channel */
    uint32_t                forcedTeardown;       /**< [udmap_only][IN]  When set, a forced teardown will be performed on the channel. Note that teardown must also be set when setting forcedTeardown. */
} CSL_PktdmaRT;

/** \brief PKTDMA configuration structure
 *
 *  This structure contains configuration information for the PKTDMA.
 *
 */
typedef struct
{
    CSL_pktdma_gcfgRegs     *pGenCfgRegs;               /**< [IN]  Pointer to the general configuration registers */
    CSL_pktdma_rxfcfgRegs   *pRxFlowCfgRegs;            /**< [IN]  Pointer to the rx flow configuration registers */
    CSL_pktdma_txccfgRegs   *pTxChanCfgRegs;            /**< [IN]  Pointer to the tx channel configuration registers */
    CSL_pktdma_rxccfgRegs   *pRxChanCfgRegs;            /**< [IN]  Pointer to the rx channel configuration registers */
    CSL_pktdma_txcrtRegs    *pTxChanRtRegs;             /**< [IN]  Pointer to the tx channel real-time registers */
    CSL_pktdma_rxcrtRegs    *pRxChanRtRegs;             /**< [IN]  Pointer to the rx channel real-time registers */
    uint32_t                cap0;                       /**< [OUT] Contains the contents of the Capabilities Register 0 (populated by the #CSL_pktdmaGetCfg function) */
    uint32_t                cap1;                       /**< [OUT] Contains the contents of the Capabilities Register 1 (populated by the #CSL_pktdmaGetCfg function) */
    uint32_t                txChanCnt;                  /**< [OUT] Tx channel count (populated by the #CSL_pktdmaGetCfg function) */
    uint32_t                rxChanCnt;                  /**< [OUT] Rx channel count (populated by the #CSL_pktdmaGetCfg function) */
    uint32_t                rxFlowCnt;                  /**< [OUT] Rx flow count (populated by the #CSL_pktdmaGetCfg function) */
    uint32_t                txExtUtcChanCnt;            /**< [udmap_only][OUT] Tx external UTC channel count (populated by the #CSL_pktdmaGetCfg function) */
    uint32_t                txHighCapacityChanCnt;      /**< [OUT] Tx external UTC channel count (populated by the #CSL_pktdmaGetCfg function) */
    uint32_t                txUltraHighCapacityChanCnt; /**< [OUT] Tx external UTC channel count (populated by the #CSL_pktdmaGetCfg function) */
} CSL_PktdmaCfg;

/** \brief Transmit / receive channel statistics
 *
 *  This structure contains statistics for transmit and receive channels.
 *
 */
typedef struct
{
    uint32_t    packetCnt;                      /**< [OUT] Current completed packet count for the channel */
    uint32_t    completedByteCnt;               /**< [OUT] Current completed payload byte count for the channel */
    uint32_t    startedByteCnt;                 /**< [OUT] Current started byte count for the channel */
    uint32_t    droppedPacketCnt;               /**< [OUT] Current dropped packet count for the channel. Valid only for receive channels. */
} CSL_PktdmaChanStats;

/* @} */

/**
 *  \addtogroup CSL_PKTDMA_FUNCTION
 *  @{
 */

/**
 *  \brief Return PKTDMA configuration information
 *
 *  This function returns configuration and capability information for the
 *  PKTDMA module. See the #CSL_PktdmaCfg structure for details on the
 *  information that is returned.
 *
 *  \param pCfg             [IN/OUT]    Pointer to the PKTDMA configuration structure
 *
 *  \return None
 */
extern void CSL_pktdmaGetCfg( CSL_PktdmaCfg *pCfg );

/**
 *  \brief Get an RX channel's real-time register values
 *
 *  This function returns the real-time register values for the specified
 *  receive channel.
 *
 *  Note that no parameter error checking is performed by this function
 *  for performance reasons.
 *
 *  \param pCfg             [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx          [IN]    Index of the receive channel
 *  \param pRT              [OUT]   Pointer to a #CSL_PktdmaRT structure where values are returned
 *
 *  \return CSL_PASS  = Function executed successfully
 */
extern int32_t CSL_pktdmaGetRxRT( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaRT *pRT );

/**
 *  \brief Get a TX channel's real-time register values
 *
 *  This function returns the real-time register values for the specified
 *  transmit channel.
 *
 *  Note that no parameter error checking is performed by this function
 *  for performance reasons.
 *
 *  \param pCfg             [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx          [IN]    Index of the transmit channel
 *  \param pRT              [OUT]   Pointer to a #CSL_PktdmaRT structure where values are returned
 *
 *  \return CSL_PASS  = Function executed successfully
 */
extern int32_t CSL_pktdmaGetTxRT( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaRT *pRT );

/**
 *  \brief Set an RX channel's real-time register values
 *
 *  This function sets the real-time register values for the specified
 *  receive channel.
 *
 *  Note that no parameter error checking is performed by this function
 *  for performance reasons.
 *
 *  \param pCfg             [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx          [IN]    Index of the receive channel
 *  \param pRT              [IN]    Pointer to a #CSL_PktdmaRT structure containing initialization values
 *
 *  \return CSL_PASS  = Function executed successfully
 */
extern int32_t CSL_pktdmaSetRxRT( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, const CSL_PktdmaRT *pRT );

/**
 *  \brief Set a TX channel's real-time register values
 *
 *  This function sets the real-time register values for the specified
 *  transmit channel.
 *
 *  \param pCfg             [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx          [IN]    Index of the transmit channel
 *  \param pRT              [IN]    Pointer to a #CSL_PktdmaRT structure containing initialization values
 *
 *  Note that no parameter error checking is performed by this function
 *  for performance reasons.
 *
 *  \return CSL_PASS  = Function executed successfully
 */
extern int32_t CSL_pktdmaSetTxRT( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, const CSL_PktdmaRT *pRT );

/**
 *  \brief Disable a transmit channel.
 *
 *  This function disables the transmit channel specified by 'chanIdx'.
 *
 *  \param pCfg     [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx  [IN]    The index of the transmit channel
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed
 */
extern int32_t CSL_pktdmaDisableTxChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx );

/**
 *  \brief Teardown a transmit channel.
 *
 *  This function tears down the transmit channel specified by 'chanIdx' at the
 *  next packet boundary.
 *
 *  \param pCfg     [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx  [IN]    The index of the transmit channel
 *  \param bForce   [IN]    If true, the channel is torn down without attempting
 *                          to preserve data or wait for events (flushes the
 *                          channel). If false, any packets in flight are
 *                          completed prior to the channel being torn down.
 *  \param bWait    [IN]    If true, wait for the teardown operation to complete.
 *                          Otherwise, return immediately.
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed (channel is disabled)
 */
extern int32_t CSL_pktdmaTeardownTxChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, bool bForce, bool bWait );

/**
 *  \brief Pause a transmit channel.
 *
 *  This function pauses the transmit channel specified by 'chanIdx' at the
 *  next packet boundary. This is a more graceful method of halting processing
 *  than disabling the channel as it will not allow any current packets to
 *  underflow.
 *
 *  \param pCfg     [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx  [IN]    The index of the transmit channel
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed (channel is disabled)
 */
extern int32_t CSL_pktdmaPauseTxChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx );

/**
 *  \brief Un-pause a transmit channel.
 *
 *  This function un-pauses the transmit channel specified by 'chanIdx'.
 *
 *  \param pCfg     [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx  [IN]    The index of the transmit channel
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed (channel is disabled)
 */
extern int32_t CSL_pktdmaUnpauseTxChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx );

/**
 *  \brief Disable a receive channel.
 *
 *  This function disables the receive channel specified by 'chanIdx'.
 *
 *  \param pCfg     [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx  [IN]    The index of the receive channel
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed
 */
extern int32_t CSL_pktdmaDisableRxChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx );

/**
 *  \brief Teardown a receive channel.
 *
 *  This function tears down the receive channel specified by 'chanIdx' at the
 *  next packet boundary.
 *
 *  \param pCfg     [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx  [IN]    The index of the receive channel
 *  \param bForce   [IN]    If true, the channel is torn down without attempting
 *                          to preserve data or wait for events (flushes the
 *                          channel). If false, any packets in flight are
 *                          completed prior to the channel being torn down.
 *  \param bWait    [IN]    If true, wait for the teardown operation to complete.
 *                          Otherwise, return immediately.
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed (channel is disabled)
 */
extern int32_t CSL_pktdmaTeardownRxChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, bool bForce, bool bWait );

/**
 *  \brief Pause a receive channel.
 *
 *  This function pauses the receive channel specified by 'chanIdx' at the
 *  next packet boundary. This is a more graceful method of halting processing
 *  than disabling the channel as it will not allow any current packets to
 *  underflow.
 *
 *  \param pCfg     [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx  [IN]    The index of the receive channel
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed (channel is disabled)
 */
extern int32_t CSL_pktdmaPauseRxChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx );

/**
 *  \brief Un-pause a receive channel.
 *
 *  This function un-pauses the receive channel specified by 'chanIdx'.
 *
 *  \param pCfg     [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx  [IN]    The index of the transmit channel
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed (channel is disabled)
 */
extern int32_t CSL_pktdmaUnpauseRxChan( CSL_PktdmaCfg *pCfg, uint32_t chanIdx );

/**
 *  \brief Get channel statistics
 *
 *  This function is used to read statistics for a transmit or receive channel.
 *
 *  Note that no parameter error checking is performed by this function
 *  for performance reasons.
 *
 *  \param pCfg             [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx          [IN]    Index of the channel
 *  \param chanDir          [IN]    Channel direction (see \ref CSL_PktdmaChanDir)
 *  \param pChanStats       [OUT]   Pointer to a #CSL_PktdmaChanStats structure
 *                                  where the statistics are returned
 *  \return None
 */
extern void CSL_pktdmaGetChanStats( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, CSL_PktdmaChanStats *pChanStats );

/**
 *  \brief Decrement channel statistics
 *
 *  Note that no parameter error checking is performed by this function
 *  for performance reasons.
 *
 *  This function is used to decrement statistics for a transmit or receive channel
 *  by the counts contained in the specified #CSL_PktdmaChanStats structure.
 *
 *  \param pCfg             [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx          [IN]    Index of the channel
 *  \param chanDir          [IN]    Channel direction (see \ref CSL_PktdmaChanDir)
 *  \param pChanStats       [IN]    Pointer to a #CSL_PktdmaChanStats structure
 *                                  containing the counts to decrement each
 *                                  statistic by
 *  \return None
 */
extern void CSL_pktdmaDecChanStats( CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, const CSL_PktdmaChanStats *pChanStats );

/**
 *  \brief Read a channel peer register
 *
 *  This function is used to read the value from a peer register for the
 *  specified channel.
 *
 *  \param pCfg             [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx          [IN]    Index of the channel
 *  \param chanDir          [IN]    Channel direction (see \ref CSL_PktdmaChanDir)
 *  \param regIdx           [IN]    Peer register index (0..15)
 *  \param pVal             [OUT]   Pointer where the register value is returned
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed (regIdx is out of range)
 */
extern int32_t CSL_pktdmaGetChanPeerReg( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, uint32_t regIdx, uint32_t *pVal );

/**
 *  \brief Write a channel peer register
 *
 *  This function is used to write a value to a peer register for the
 *  specified transmit channel.
 *
 *  \param pCfg             [IN]    Pointer to the PKTDMA configuration structure
 *  \param chanIdx          [IN]    Index of the transmit channel
 *  \param chanDir          [IN]    Channel direction (see \ref CSL_PktdmaChanDir)
 *  \param regIdx           [IN]    Peer register index (0..15)
 *  \param pVal             [IN]    Pointer to the register value to be written
 *
 *  \return CSL_PASS  = Function executed successfully
 *          CSL_EFAIL = Function execution failed (regIdx is out of range)
 */
extern int32_t CSL_pktdmaSetChanPeerReg( const CSL_PktdmaCfg *pCfg, uint32_t chanIdx, CSL_PktdmaChanDir chanDir, uint32_t regIdx, uint32_t *pVal );

/* @} */

#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif  /* end of CSL_PKTDMA_H_ definition */
/** @} */

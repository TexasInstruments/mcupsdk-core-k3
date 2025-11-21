/**
 * @file  csl_intaggr.h
 *
 * @brief
 *  Header file containing various enumerations, structure definitions and function
 *  declarations for the INTAGGR IP.
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2016-2019, Texas Instruments, Inc.
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
#ifndef CSL_INTAGGR_H_
#define CSL_INTAGGR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/cslr_intaggr.h>

/** ===========================================================================
 *
 * @defgroup CSL_INTAGGR_API Interrupt Aggregator (INTAGGR) API
 *
 *  This is the CSL-FL for the INTAGGR. It provides the structures
 *  and APIs needed to configure, initialize, and query the INTAGGR.
 *
 *  The following lists the steps required to use this CSL-FL:
 *
 *  1. Allocate and initialize a #CSL_IntaggrCfg structure. This structure
 *     provides the virtual base addresses for all INTAGGR register regions.
 *
 *  2. Call the #CSL_intaggrGetCfg function. This function reads configuration
 *     information from the INTAGGR IP and stores this information in the
 *     #CSL_IntaggrCfg structure. This information is used by the remaining
 *     INTAGGR API functions.
 *
 *  3. Call the remaining API functions to further configure and query the
 *     required events.
 *
 * ============================================================================
 */
/**
@defgroup CSL_INTAGGR_DATASTRUCT  INTAGGR Data Structures
@ingroup CSL_INTAGGR_API
*/
/**
@defgroup CSL_INTAGGR_FUNCTION  INTAGGR Functions
@ingroup CSL_INTAGGR_API
*/
/**
@defgroup CSL_INTAGGR_ENUM INTAGGR Enumerated Data Types
@ingroup CSL_INTAGGR_API
*/

/**
 *  \addtogroup CSL_INTAGGR_ENUM
 *  @{
 */

/**
 *  The CSL_INTAGGR_INTR_MODE_FLAG macro can be used to specify that the
 *  globalEventOutIdx parameter(s) to the CSL_intaggrMapEventRxCntEvent,
 *  CSL_intaggrEnableEventMulticast, and CSL_intaggrMapUnmappedEventToEvent
 *  functions contain an interrupt status bit value instead of an event index.
 */
#define CSL_INTAGGR_INTR_MODE_FLAG              ((uint32_t) 0x80000000U)

/** ---------------------------------------------------------------------------
 * @brief These defines map more meaningful function names to prior API
 *        function names
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
#define CSL_intaggrMapEventToIntr CSL_intaggrMapEventIntr
#define CSL_intaggrMapEventToRxCntEvent CSL_intaggrMapEventRxCntEvent
#define CSL_intaggrMapEventToMulticastEvents CSL_intaggrEnableEventMulticast
/* @} */

/** ---------------------------------------------------------------------------
 * @brief This enumerator defines valid modes used to detect local events
 *
 *  \anchor CSL_IntaggrEventDetectMode
 *  \name Intaggr event detect mode
 *
 *  @{
 * ----------------------------------------------------------------------------
 */
typedef uint32_t CSL_IntaggrEventDetectMode;
    /** Active-high pulse */
#define CSL_INTAGGR_EVT_DETECT_MODE_ACTIVE_HIGH_PULSE   ((uint32_t) 0U)
    /** Clock synchronous rising edge */
#define CSL_INTAGGR_EVT_DETECT_MODE_RISING_EDGE         ((uint32_t) 1U)
    /** Invalid */
#define CSL_INTAGGR_EVT_DETECT_MODE_INVALID             ((uint32_t) 2U)
/* @} */

/* @} */

/**
 *  \addtogroup CSL_INTAGGR_DATASTRUCT
 *  @{
 */

/** ---------------------------------------------------------------------------
 * @brief   This structure contains configuration information for the Interrupt
 *          Aggregator.
 *
 * ----------------------------------------------------------------------------
 */
typedef struct
{
    CSL_intaggr_cfgRegs     *pCfgRegs;          /** Pointer to configuration registers */
    CSL_intaggr_imapRegs    *pImapRegs;         /** Pointer to interrupt mapping registers */
    CSL_intaggr_intrRegs    *pIntrRegs;         /** Pointer to interrupt registers */
    CSL_intaggr_l2gRegs     *pL2gRegs;          /** Pointer to local-to-global event mapping registers */
    CSL_intaggr_mcastRegs   *pMcastRegs;        /** Pointer to global event multicast registers */
    CSL_intaggr_gcntcfgRegs *pGcntCfgRegs;      /** Pointer to global event counter configuration registers */
    CSL_intaggr_gcntrtiRegs *pGcntRtiRegs;      /** Pointer to global event counter rti registers */
#ifdef CSL_INTAGGR_UNMAP_UNMAP_MAP_MAPIDX_MASK
    CSL_intaggr_unmapRegs   *pUnmapRegs;        /** Pointer to unmapped event mapping registers */
#endif
    uint32_t                srcEventCnt;        /** Max # of source events (populated by #CSL_intaggrGetCfg) */
    uint32_t                virtIntrCnt;        /** Max # of virtual interrupts (populated by #CSL_intaggrGetCfg) */
    uint32_t                localEventCnt;      /** Max # of local events (populated by #CSL_intaggrGetCfg) */
    uint32_t                globalEventCnt;     /** Max # of global events (populated by #CSL_intaggrGetCfg) */
    uint32_t                mcastEventCnt;      /** Max # of multicast events (populated by #CSL_intaggrGetCfg) */
    uint32_t                unmapEventCnt;      /** Max # of unmapped events (populated by #CSL_intaggrGetCfg) */
} CSL_IntaggrCfg;

/* @} */

/**
 *  \addtogroup CSL_INTAGGR_FUNCTION
 *  @{
 */

/**
 *  \brief Get INTAGGR module configuration information
 *
 *  This function reads configuration-specific information for the
 *  INTAGGR and returns the values in the #CSL_IntaggrCfg structure.
 *
 *  The following structure fields are populated by this function:
 *      srcEventCnt       Max # of source events
 *      virtIntrCnt       Max # of virtual interrupts
 *      localEventCnt     Max # of local events
 *      globalEventCnt    Max # of global events
 *      mcastEventCnt     Max # of multicast events
 *      unmapEventCnt     Max # of unmapped events (if supported by intaggr in use)
 *
 *  This function must be called before calling any of the other API functions
 *  (except for #CSL_intaggrGetRevision).
 *
 *  \param pCfg             [IN/OUT]    Pointer to the #CSL_IntaggrCfg structure
 *
 *  \return None
 */
extern void CSL_intaggrGetCfg( CSL_IntaggrCfg *pCfg );

/**
 *  \brief Map a local event to a global event
 *
 *  This function is used to map the specified local event to the specified
 *  global event.
 *
 *  A local event is an active-high pulse or clock synchronous rising edge
 *  input into the INTAGGR. The global event is output from the INTAGGR and
 *  can optionally be fed back into the INTAGGR (via the ETL switch fabric)
 *  for further interrupt generation (see #CSL_intaggrMapEventIntr),
 *  counting (see #CSL_intaggrMapEventRxCntEvent), or multicasting (see
 *  #CSL_intaggrEnableEventMulticast).
 *
 *  Note: The #CSL_intaggrGetCfg function must be called prior to calling this
 *  function.
 *
 *  \param pCfg                 [IN]  Pointer to the #CSL_IntaggrCfg structure
 *  \param globalEventIdx       [IN]  Global event index
 *  \param localEventIdx        [IN]  Index of the local event (pin #;
 *                                    0..localEventCnt-1)
 *  \param localEventDetectMode [IN]  Mode used to detect the local event.
 *                                    See \ref CSL_IntaggrEventDetectMode.
 *
 *  \return CSL_PASS = success
 *          CSL_EFAIL = INTAGGR does not support this feature
 *          CSL_EBADARGS = Invalid localEventIdx or localEventDetectMode parameter
 */
extern int32_t CSL_intaggrMapEventToLocalEvent( CSL_IntaggrCfg *pCfg, uint32_t globalEventIdx, uint32_t localEventIdx, CSL_IntaggrEventDetectMode localEventDetectMode );

/**
 *  \brief Enable or disable a status interrupt
 *
 *  This function is used to enable or disable the specified status
 *  interrupt.
 *
 *  Note: The #CSL_intaggrGetCfg function must be called prior to calling this
 *  function.
 *
 *  \param pCfg             [IN]    Pointer to the #CSL_IntaggrCfg structure
 *  \param statusBitNum     [IN]    Status bit # (0..(virtIntrCnt*64)-1)
 *  \param bEnable          [IN]    If true, interrupt is enabled. If false,
 *                                  it is disabled.
 *
 *  \return CSL_PASS = success
 *          CSL_EBADARGS = Invalid statusBitNum parameter
 */
extern int32_t CSL_intaggrSetIntrEnable( CSL_IntaggrCfg *pCfg, uint32_t statusBitNum, bool bEnable );

/**
 *  \brief Determine if a status interrupt is pending
 *
 *  This function is used to determine if the specified status
 *  interrupt is pending. Either the raw or masked pending status can be
 *  queried.
 *
 *  Note: The #CSL_intaggrGetCfg function must be called prior to calling this
 *  function.
 *
 *  \param pCfg             [IN]    Pointer to the #CSL_IntaggrCfg structure
 *  \param statusBitNum     [IN]    Status bit # (0..(virtIntrCnt*64)-1)
 *  \param bMaskedStatus    [IN]    If true, the masked pending status is
 *                                  returned. If false, the raw pending status
 *                                  is returned.
 *
 *  \return  true  = The interrupt is pending
 *           false = The interrupt is not pending or the statusBitNum
 *                   is invalid
 */
extern bool CSL_intaggrIsIntrPending( const CSL_IntaggrCfg *pCfg, uint32_t statusBitNum, bool bMaskedStatus );

/**
 *  \brief Clear a pending status interrupt
 *
 *  This function is used to clear the specified pending status interrupt.
 *
 *  Note: The #CSL_intaggrGetCfg function must be called prior to calling this
 *  function.
 *
 *  \param pCfg             [IN]    Pointer to the #CSL_IntaggrCfg structure
 *  \param statusBitNum     [IN]    Status bit # (0..(virtIntrCnt*64)-1)
 *
 *  \return CSL_PASS = success
 *          CSL_EBADARGS = Invalid statusBitNum parameter
 */
extern int32_t CSL_intaggrClrIntr( CSL_IntaggrCfg *pCfg, uint32_t statusBitNum );

/* @} */

#ifdef __cplusplus
}
#endif  // extern "C"

#endif  // end of CSL_INTAGGR_H_ definition

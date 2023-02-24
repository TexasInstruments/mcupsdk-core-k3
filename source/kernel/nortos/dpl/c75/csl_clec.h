/*
 *  Copyright (C) 2017-2021 Texas Instruments Incorporated.
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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_CLEC CLEC - Compute cluster Event Controller
 *
 *  @{
 */
/**
 *  \file  csl_clec.h
 *
 *  \brief
 *     This is the include file for the CLEC CSL-FL module.
 */

#ifndef CSL_CLEC_H_
#define CSL_CLEC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/cslr_clec.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/**
 *  \brief Maximum number of input events supported by CLEC. This is just the
 *  maximum registers supported for programming. The actual event supported
 *  depends on the SOC.
 */
#define CSL_CLEC_MAX_EVT_IN             (512U)
/**
 *  \brief Maximum external events.
 */
#define CSL_CLEC_MAX_EXT_EVT_OUT        (256U)

/**
 *  \brief Maximum C7x events.
 */
#define CSL_CLEC_MAX_C7X_EVT_OUT        (64U)

/**
 *  \anchor CSL_ClecRouteMap
 *  \name CLEC route map - Determines where the event will be routed.
 *
 *  Note: All the cores may not be present in a particular SOC. The CSL-FL
 *  is provided to support the IP feature and hence all possible setting is
 *  provided. Also the meaning of each core is SOC dependent. Refer to
 *  SOC information to know the exact mapping.
 *
 *  @{
 */
/** \brief Send event to None */
#define CSL_CLEC_RTMAP_DISABLE          ((uint32_t)((uint32_t) 0x0001U) << 0U)
/** \brief Send event to SOC as Compute Cluster interrupt output */
#define CSL_CLEC_RTMAP_SYS              ((uint32_t)((uint32_t) 0x0001U) << 1U)
/** \brief Send event to CPU 0 - Typically reserved for ARM */
#define CSL_CLEC_RTMAP_CPU_0            ((uint32_t)((uint32_t) 0x0000U) << 2U)
/** \brief Send event to CPU 1 - Typically reserved for ARM */
#define CSL_CLEC_RTMAP_CPU_1            ((uint32_t)((uint32_t) 0x0001U) << 2U)
/** \brief Send event to CPU 2 - Typically reserved for ARM */
#define CSL_CLEC_RTMAP_CPU_2            ((uint32_t)((uint32_t) 0x0002U) << 2U)
/** \brief Send event to CPU 3 - Typically reserved for ARM */
#define CSL_CLEC_RTMAP_CPU_3            ((uint32_t)((uint32_t) 0x0003U) << 2U)
/** \brief Send event to CPU 4 - Typically C7x core starts from this */
#define CSL_CLEC_RTMAP_CPU_4            ((uint32_t)((uint32_t) 0x0004U) << 2U)
/** \brief Send event to CPU 5 */
#define CSL_CLEC_RTMAP_CPU_5            ((uint32_t)((uint32_t) 0x0005U) << 2U)
/** \brief Send event to CPU 6 */
#define CSL_CLEC_RTMAP_CPU_6            ((uint32_t)((uint32_t) 0x0006U) << 2U)
/** \brief Send event to CPU 7 */
#define CSL_CLEC_RTMAP_CPU_7            ((uint32_t)((uint32_t) 0x0007U) << 2U)
/** \brief Send event to CPU 8 */
#define CSL_CLEC_RTMAP_CPU_8            ((uint32_t)((uint32_t) 0x0008U) << 2U)
/** \brief Send event to CPU 9 */
#define CSL_CLEC_RTMAP_CPU_9            ((uint32_t)((uint32_t) 0x0009U) << 2U)
/** \brief Send event to CPU 10 */
#define CSL_CLEC_RTMAP_CPU_10           ((uint32_t)((uint32_t) 0x000AU) << 2U)
/** \brief Send event to All CPU */
#define CSL_CLEC_RTMAP_CPU_ALL          ((uint32_t)((uint32_t) 0x000FU) << 2U)
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief This structure contains the parameters to setup a event. */
typedef struct
{
    uint32_t                secureClaimEnable;
    /**< [IN] TRUE/FALSE.
     *   When set to TRUE, a non-secure read/write to MRR will generate a
     *   privilege error. */
    uint32_t                evtSendEnable;
    /**< [IN] TRUE/FALSE. Controls whether ESR sends this event when written.
     *   When set to TRUE, write to ESR triggers the event. */
    uint32_t                rtMap;
    /**< [IN] Route map bit field. Refer \ref CSL_ClecRouteMap. */
    uint32_t                extEvtNum;
    /**< [IN] Encoded external event number to send when this event
     *   is triggered. Range 0 to (#CSL_CLEC_MAX_EXT_EVT_OUT - 1). */
    uint32_t                c7xEvtNum;
    /**< [IN] C7x event number to send when this event is triggered.
     *   Range 0 to (#CSL_CLEC_MAX_C7X_EVT_OUT - 1). */
} CSL_ClecEventConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief   This API sets the event configuration.
 *
 *  \param   pRegs      [IN] CLEC register base.
 *  \param   evtNum     [IN] CLEC event number 0 to (#CSL_CLEC_MAX_EVT_IN - 1).
 *  \param   evtCfg     [IN] Pointer to event configuration.
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_clecConfigEvent(CSL_CLEC_EVTRegs *pRegs,
                            uint32_t evtNum,
                            const CSL_ClecEventConfig *evtCfg);

/**
 *  \brief   This API sends the event specified if the event send is enabled
 *  in the event configuration (evtSendEnable) and the output event generated
 *  depends on the rtMap, extEvtNum and c7xEvtNum.
 *
 *  \param   pRegs      [IN] CLEC register base.
 *  \param   evtNum     [IN] CLEC event number 0 to (#CSL_CLEC_MAX_EVT_IN - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_clecSendEvent(CSL_CLEC_EVTRegs *pRegs, uint32_t evtNum);

/**
 *  \brief   This API clear any level interrupt set for the event.
 *
 *  \param   pRegs      [IN] CLEC register base.
 *  \param   evtNum     [IN] CLEC event number 0 to (#CSL_CLEC_MAX_EVT_IN - 1).
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_clecClearEvent(CSL_CLEC_EVTRegs *pRegs, uint32_t evtNum);


/**
 *  \brief   This API does a set or clear of the is_lvl field in CLEC.MRR register
 *
 *  \param   pRegs      [IN] CLEC register base.
 *  \param   evtNum     [IN] CLEC event number 0 to (#CSL_CLEC_MAX_EVT_IN - 1).
 *  \param   is_level   [IN] 0: is_lvl field is set to 0, i.e pulse interrupt, 1: is_lvl field is set to 1, i.e level interrupt
 *
 *  \return \ref CSL_ErrType_t
 */
int32_t CSL_clecConfigEventLevel(CSL_CLEC_EVTRegs *pRegs,
                            uint32_t evtNum,
                            uint32_t is_level);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* CSL_CLEC_H_ */
/** @} */

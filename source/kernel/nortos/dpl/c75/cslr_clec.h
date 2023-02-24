/********************************************************************
 * Copyright (C) 2021 Texas Instruments Incorporated.
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
 *  Name        : cslr_clec.h
*/
#ifndef CSLR_CLEC_H_
#define CSLR_CLEC_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : CLEC Global config registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t EFR;                       /* CLEC event flag register */
} CSL_CLEC_EVTRegs_GLOBAL_SET_FLAG;


typedef struct {
    volatile uint32_t EDR;                       /* CLEC dropped event register */
} CSL_CLEC_EVTRegs_GLOBAL_DROP_FLAG;


typedef struct {
    volatile uint32_t PID;                       /* CLEC PID register */
    volatile uint8_t  Resv_40960[40956];
    CSL_CLEC_EVTRegs_GLOBAL_SET_FLAG SET_FLAG[63];
    volatile uint8_t  Resv_45056[3844];
    CSL_CLEC_EVTRegs_GLOBAL_DROP_FLAG DROP_FLAG[63];
    volatile uint8_t  Resv_49152[3844];
    volatile uint32_t GELRS;                     /* Global Event Lock register for secure claims */
    volatile uint8_t  Resv_53248[4092];
    volatile uint32_t GELRNS;                    /* Global Event Lock register for non-secure claims */
} CSL_CLEC_EVTRegs_GLOBAL;


typedef struct {
    volatile uint32_t MRR;                       /* Map and Routing register */
    volatile uint32_t ESR;                       /* Event send register. Ignores value written. Sends event to cpu */
    volatile uint32_t ECR;                       /* Event clear register. Ignores value written. Clears level events for that event number */
    volatile uint8_t  Resv_256[244];
} CSL_CLEC_EVTRegs_CFG;


typedef struct {
    CSL_CLEC_EVTRegs_GLOBAL GLOBAL;
    volatile uint8_t  Resv_524288[471036]; /* Reserved space 0x80000 - 0xD004 */
    CSL_CLEC_EVTRegs_CFG CFG[512];
} CSL_CLEC_EVTRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CLEC_EVT_GLOBAL_PID                                                (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_SET_FLAG_EFR(SET_FLAG)                             (0x0000A000U+((SET_FLAG)*0x4U))
#define CSL_CLEC_EVT_GLOBAL_DROP_FLAG_EDR(DROP_FLAG)                           (0x0000B000U+((DROP_FLAG)*0x4U))
#define CSL_CLEC_EVT_GLOBAL_GELRS                                              (0x0000C000U)
#define CSL_CLEC_EVT_GLOBAL_GELRNS                                             (0x0000D000U)
#define CSL_CLEC_EVT_CFG_MRR(CFG)                                              (0x00080000U+((CFG)*0x100U))
#define CSL_CLEC_EVT_CFG_ESR(CFG)                                              (0x00080004U+((CFG)*0x100U))
#define CSL_CLEC_EVT_CFG_ECR(CFG)                                              (0x00080008U+((CFG)*0x100U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* EFR */

#define CSL_CLEC_EVT_GLOBAL_SET_FLAG_EFR_EVNTFR_MASK                           (0xFFFFFFFFU)
#define CSL_CLEC_EVT_GLOBAL_SET_FLAG_EFR_EVNTFR_SHIFT                          (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_SET_FLAG_EFR_EVNTFR_RESETVAL                       (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_SET_FLAG_EFR_EVNTFR_MAX                            (0xFFFFFFFFU)

#define CSL_CLEC_EVT_GLOBAL_SET_FLAG_EFR_RESETVAL                              (0x00000000U)

/* EDR */

#define CSL_CLEC_EVT_GLOBAL_DROP_FLAG_EDR_EVNTFR_MASK                          (0xFFFFFFFFU)
#define CSL_CLEC_EVT_GLOBAL_DROP_FLAG_EDR_EVNTFR_SHIFT                         (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_DROP_FLAG_EDR_EVNTFR_RESETVAL                      (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_DROP_FLAG_EDR_EVNTFR_MAX                           (0xFFFFFFFFU)

#define CSL_CLEC_EVT_GLOBAL_DROP_FLAG_EDR_RESETVAL                             (0x00000000U)

/* PID */

#define CSL_CLEC_EVT_GLOBAL_PID_SCHEME_MASK                                    (0xC0000000U)
#define CSL_CLEC_EVT_GLOBAL_PID_SCHEME_SHIFT                                   (0x0000001EU)
#define CSL_CLEC_EVT_GLOBAL_PID_SCHEME_RESETVAL                                (0x00000001U)
#define CSL_CLEC_EVT_GLOBAL_PID_SCHEME_MAX                                     (0x00000003U)

#define CSL_CLEC_EVT_GLOBAL_PID_BU_MASK                                        (0x30000000U)
#define CSL_CLEC_EVT_GLOBAL_PID_BU_SHIFT                                       (0x0000001CU)
#define CSL_CLEC_EVT_GLOBAL_PID_BU_RESETVAL                                    (0x00000002U)
#define CSL_CLEC_EVT_GLOBAL_PID_BU_MAX                                         (0x00000003U)

#define CSL_CLEC_EVT_GLOBAL_PID_MODULE_ID_MASK                                 (0x0FFF0000U)
#define CSL_CLEC_EVT_GLOBAL_PID_MODULE_ID_SHIFT                                (0x00000010U)
#define CSL_CLEC_EVT_GLOBAL_PID_MODULE_ID_RESETVAL                             (0x00000010U)
#define CSL_CLEC_EVT_GLOBAL_PID_MODULE_ID_MAX                                  (0x00000FFFU)

#define CSL_CLEC_EVT_GLOBAL_PID_REVRTL_MASK                                    (0x0000F800U)
#define CSL_CLEC_EVT_GLOBAL_PID_REVRTL_SHIFT                                   (0x0000000BU)
#define CSL_CLEC_EVT_GLOBAL_PID_REVRTL_RESETVAL                                (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_PID_REVRTL_MAX                                     (0x0000001FU)

#define CSL_CLEC_EVT_GLOBAL_PID_REVMAX_MASK                                    (0x00000700U)
#define CSL_CLEC_EVT_GLOBAL_PID_REVMAX_SHIFT                                   (0x00000008U)
#define CSL_CLEC_EVT_GLOBAL_PID_REVMAX_RESETVAL                                (0x00000001U)
#define CSL_CLEC_EVT_GLOBAL_PID_REVMAX_MAX                                     (0x00000007U)

#define CSL_CLEC_EVT_GLOBAL_PID_CUSTOM_MASK                                    (0x000000C0U)
#define CSL_CLEC_EVT_GLOBAL_PID_CUSTOM_SHIFT                                   (0x00000006U)
#define CSL_CLEC_EVT_GLOBAL_PID_CUSTOM_RESETVAL                                (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_PID_CUSTOM_MAX                                     (0x00000003U)

#define CSL_CLEC_EVT_GLOBAL_PID_REVMIN_MASK                                    (0x0000003FU)
#define CSL_CLEC_EVT_GLOBAL_PID_REVMIN_SHIFT                                   (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_PID_REVMIN_RESETVAL                                (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_PID_REVMIN_MAX                                     (0x0000003FU)

#define CSL_CLEC_EVT_GLOBAL_PID_RESETVAL                                       (0x60100100U)

/* GELRS */

#define CSL_CLEC_EVT_GLOBAL_GELRS_RESERVED_MASK                                (0xFFFFFFFEU)
#define CSL_CLEC_EVT_GLOBAL_GELRS_RESERVED_SHIFT                               (0x00000001U)
#define CSL_CLEC_EVT_GLOBAL_GELRS_RESERVED_RESETVAL                            (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_GELRS_RESERVED_MAX                                 (0x7FFFFFFFU)

#define CSL_CLEC_EVT_GLOBAL_GELRS_LOCK_MASK                                    (0x00000001U)
#define CSL_CLEC_EVT_GLOBAL_GELRS_LOCK_SHIFT                                   (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_GELRS_LOCK_RESETVAL                                (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_GELRS_LOCK_MAX                                     (0x00000001U)

#define CSL_CLEC_EVT_GLOBAL_GELRS_RESETVAL                                     (0x00000000U)

/* GELRNS */

#define CSL_CLEC_EVT_GLOBAL_GELRNS_RESERVED_MASK                               (0xFFFFFFFEU)
#define CSL_CLEC_EVT_GLOBAL_GELRNS_RESERVED_SHIFT                              (0x00000001U)
#define CSL_CLEC_EVT_GLOBAL_GELRNS_RESERVED_RESETVAL                           (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_GELRNS_RESERVED_MAX                                (0x7FFFFFFFU)

#define CSL_CLEC_EVT_GLOBAL_GELRNS_LOCK_MASK                                   (0x00000001U)
#define CSL_CLEC_EVT_GLOBAL_GELRNS_LOCK_SHIFT                                  (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_GELRNS_LOCK_RESETVAL                               (0x00000000U)
#define CSL_CLEC_EVT_GLOBAL_GELRNS_LOCK_MAX                                    (0x00000001U)

#define CSL_CLEC_EVT_GLOBAL_GELRNS_RESETVAL                                    (0x00000000U)

/* MRR */

#define CSL_CLEC_EVT_CFG_MRR_S_MASK                                            (0x80000000U)
#define CSL_CLEC_EVT_CFG_MRR_S_SHIFT                                           (0x0000001FU)
#define CSL_CLEC_EVT_CFG_MRR_S_RESETVAL                                        (0x00000001U)
#define CSL_CLEC_EVT_CFG_MRR_S_MAX                                             (0x00000001U)

#define CSL_CLEC_EVT_CFG_MRR_ESE_MASK                                          (0x40000000U)
#define CSL_CLEC_EVT_CFG_MRR_ESE_SHIFT                                         (0x0000001EU)
#define CSL_CLEC_EVT_CFG_MRR_ESE_RESETVAL                                      (0x00000000U)
#define CSL_CLEC_EVT_CFG_MRR_ESE_MAX                                           (0x00000001U)

#define CSL_CLEC_EVT_CFG_MRR_RSVD3_MASK                                        (0x3C000000U)
#define CSL_CLEC_EVT_CFG_MRR_RSVD3_SHIFT                                       (0x0000001AU)
#define CSL_CLEC_EVT_CFG_MRR_RSVD3_RESETVAL                                    (0x00000000U)
#define CSL_CLEC_EVT_CFG_MRR_RSVD3_MAX                                         (0x0000000FU)

#define CSL_CLEC_EVT_CFG_MRR_EVTPF_MASK                                        (0x02000000U)
#define CSL_CLEC_EVT_CFG_MRR_EVTPF_SHIFT                                       (0x00000019U)
#define CSL_CLEC_EVT_CFG_MRR_EVTPF_RESETVAL                                    (0x00000000U)
#define CSL_CLEC_EVT_CFG_MRR_EVTPF_MAX                                         (0x00000001U)

#define CSL_CLEC_EVT_CFG_MRR_IS_LVL_MASK                                       (0x01000000U)
#define CSL_CLEC_EVT_CFG_MRR_IS_LVL_SHIFT                                      (0x00000018U)
#define CSL_CLEC_EVT_CFG_MRR_IS_LVL_RESETVAL                                   (0x00000001U)
#define CSL_CLEC_EVT_CFG_MRR_IS_LVL_MAX                                        (0x00000001U)

#define CSL_CLEC_EVT_CFG_MRR_RSVD2_MASK                                        (0x00C00000U)
#define CSL_CLEC_EVT_CFG_MRR_RSVD2_SHIFT                                       (0x00000016U)
#define CSL_CLEC_EVT_CFG_MRR_RSVD2_RESETVAL                                    (0x00000000U)
#define CSL_CLEC_EVT_CFG_MRR_RSVD2_MAX                                         (0x00000003U)

#define CSL_CLEC_EVT_CFG_MRR_RTMAP_MASK                                        (0x003F0000U)
#define CSL_CLEC_EVT_CFG_MRR_RTMAP_SHIFT                                       (0x00000010U)
#define CSL_CLEC_EVT_CFG_MRR_RTMAP_RESETVAL                                    (0x00000001U)
#define CSL_CLEC_EVT_CFG_MRR_RTMAP_MAX                                         (0x0000003FU)

#define CSL_CLEC_EVT_CFG_MRR_EXT_EVTNUM_MASK                                   (0x0000FF00U)
#define CSL_CLEC_EVT_CFG_MRR_EXT_EVTNUM_SHIFT                                  (0x00000008U)
#define CSL_CLEC_EVT_CFG_MRR_EXT_EVTNUM_RESETVAL                               (0x00000000U)
#define CSL_CLEC_EVT_CFG_MRR_EXT_EVTNUM_MAX                                    (0x000000FFU)

#define CSL_CLEC_EVT_CFG_MRR_RSVD0_MASK                                        (0x000000C0U)
#define CSL_CLEC_EVT_CFG_MRR_RSVD0_SHIFT                                       (0x00000006U)
#define CSL_CLEC_EVT_CFG_MRR_RSVD0_RESETVAL                                    (0x00000000U)
#define CSL_CLEC_EVT_CFG_MRR_RSVD0_MAX                                         (0x00000003U)

#define CSL_CLEC_EVT_CFG_MRR_C7X_EVTNUM_MASK                                   (0x0000003FU)
#define CSL_CLEC_EVT_CFG_MRR_C7X_EVTNUM_SHIFT                                  (0x00000000U)
#define CSL_CLEC_EVT_CFG_MRR_C7X_EVTNUM_RESETVAL                               (0x00000000U)
#define CSL_CLEC_EVT_CFG_MRR_C7X_EVTNUM_MAX                                    (0x0000003FU)

#define CSL_CLEC_EVT_CFG_MRR_RESETVAL                                          (0x81010000U)

/* ESR */

#define CSL_CLEC_EVT_CFG_ESR_ESR_N_MASK                                        (0xFFFFFFFFU)
#define CSL_CLEC_EVT_CFG_ESR_ESR_N_SHIFT                                       (0x00000000U)
#define CSL_CLEC_EVT_CFG_ESR_ESR_N_RESETVAL                                    (0x00000000U)
#define CSL_CLEC_EVT_CFG_ESR_ESR_N_MAX                                         (0xFFFFFFFFU)

#define CSL_CLEC_EVT_CFG_ESR_RESETVAL                                          (0x00000000U)

/* ECR */

#define CSL_CLEC_EVT_CFG_ECR_RESERVED_MASK                                     (0xFFFFFFFCU)
#define CSL_CLEC_EVT_CFG_ECR_RESERVED_SHIFT                                    (0x00000002U)
#define CSL_CLEC_EVT_CFG_ECR_RESERVED_RESETVAL                                 (0x00000000U)
#define CSL_CLEC_EVT_CFG_ECR_RESERVED_MAX                                      (0x3FFFFFFFU)

#define CSL_CLEC_EVT_CFG_ECR_ECR_PFLAG_MASK                                    (0x00000002U)
#define CSL_CLEC_EVT_CFG_ECR_ECR_PFLAG_SHIFT                                   (0x00000001U)
#define CSL_CLEC_EVT_CFG_ECR_ECR_PFLAG_RESETVAL                                (0x00000000U)
#define CSL_CLEC_EVT_CFG_ECR_ECR_PFLAG_MAX                                     (0x00000001U)

#define CSL_CLEC_EVT_CFG_ECR_ECR_FLAG_MASK                                     (0x00000001U)
#define CSL_CLEC_EVT_CFG_ECR_ECR_FLAG_SHIFT                                    (0x00000000U)
#define CSL_CLEC_EVT_CFG_ECR_ECR_FLAG_RESETVAL                                 (0x00000000U)
#define CSL_CLEC_EVT_CFG_ECR_ECR_FLAG_MAX                                      (0x00000001U)

#define CSL_CLEC_EVT_CFG_ECR_RESETVAL                                          (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif

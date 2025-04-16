/********************************************************************
 * Copyright (C) 2025 Texas Instruments Incorporated.
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
 *  Name        : cslr_lcdma_ringacc.h
 *  VPVERSION   : 3.0.377 - 2024.12.19.12.30.53
 *  VPREV       : 1.0.8
*/
#ifndef CSLR_LCDMA_RINGACC_H_
#define CSLR_LCDMA_RINGACC_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : Ring Control / Status Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RESRC;                     /* Flow Resource Register */
    volatile uint8_t  Resv_8[4];
    volatile uint32_t RFA;                       /* Rx Flow Config Register A */
    volatile uint8_t  Resv_64[52];
    volatile uint32_t BA_LO;                     /* Ring Base Address Lo Register */
    volatile uint32_t BA_HI;                     /* Ring Base Address Hi Register */
    volatile uint32_t SIZE;                      /* Ring Size Register */
    volatile uint8_t  Resv_256[180];
} CSL_lcdma_ringacc_flow_cfg_v2Regs_flow;


typedef struct {
    CSL_lcdma_ringacc_flow_cfg_v2Regs_flow FLOW[158];
} CSL_lcdma_ringacc_flow_cfg_v2Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RESRC(FLOW)                         (0x00000000U+((FLOW)*0x100U))
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA(FLOW)                           (0x00000008U+((FLOW)*0x100U))
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_LO(FLOW)                         (0x00000040U+((FLOW)*0x100U))
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI(FLOW)                         (0x00000044U+((FLOW)*0x100U))
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE(FLOW)                          (0x00000048U+((FLOW)*0x100U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RESRC */

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RESRC_ALIAS_MASK                    (0x80000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RESRC_ALIAS_SHIFT                   (0x0000001FU)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RESRC_ALIAS_RESETVAL                (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RESRC_ALIAS_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RESRC_RESETVAL                      (0x80000000U)

/* RFA */

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_EINFO_MASK                      (0x40000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_EINFO_SHIFT                     (0x0000001EU)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_EINFO_RESETVAL                  (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_EINFO_MAX                       (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_PSINFO_MASK                     (0x20000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_PSINFO_SHIFT                    (0x0000001DU)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_PSINFO_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_PSINFO_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_EHANDLING_MASK                  (0x10000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_EHANDLING_SHIFT                 (0x0000001CU)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_EHANDLING_RESETVAL              (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_EHANDLING_MAX                   (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_SOP_OFF_MASK                    (0x01FF0000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_SOP_OFF_SHIFT                   (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_SOP_OFF_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_SOP_OFF_MAX                     (0x000001FFU)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_RFA_RESETVAL                        (0x00000000U)

/* BA_LO */

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_LO_ADDR_LO_MASK                  (0xFFFFFFFFU)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_LO_ADDR_LO_SHIFT                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_LO_ADDR_LO_RESETVAL              (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_LO_ADDR_LO_MAX                   (0xFFFFFFFFU)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_LO_RESETVAL                      (0x00000000U)

/* BA_HI */

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI_ASEL_MASK                     (0x000F0000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI_ASEL_SHIFT                    (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI_ASEL_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI_ASEL_MAX                      (0x0000000FU)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI_ADDR_HI_MASK                  (0x0000000FU)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI_ADDR_HI_SHIFT                 (0x00000020U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI_ADDR_HI_RESETVAL              (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI_ADDR_HI_MAX                   (0x0000000FU)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_BA_HI_RESETVAL                      (0x00000000U)

/* SIZE */

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_QMODE_MASK                     (0xE0000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_QMODE_SHIFT                    (0x0000001DU)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_QMODE_RESETVAL                 (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_QMODE_MAX                      (0x00000007U)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_QMODE_VAL_DRING_MODE           (0x1U)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_ELSIZE_MASK                    (0x07000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_ELSIZE_SHIFT                   (0x00000018U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_ELSIZE_RESETVAL                (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_ELSIZE_MAX                     (0x00000007U)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_ELCNT_MASK                     (0x0000FFFFU)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_ELCNT_SHIFT                    (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_ELCNT_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_ELCNT_MAX                      (0x0000FFFFU)

#define CSL_LCDMA_RINGACC_FLOW_CFG_V2_FLOW_SIZE_RESETVAL                       (0x21000000U)

/**************************************************************************
* Hardware Region  : Flow Realtime Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_8[8];
    volatile uint32_t RFA;                       /* Rx Flow Config Register A */
    volatile uint8_t  Resv_16[4];
    volatile uint32_t FDB;                       /* Realtime Ring N Forward Doorbell Register */
    volatile uint8_t  Resv_24[4];
    volatile uint32_t FOCC;                      /* Realtime Ring N Forward Occupancy Register */
    volatile uint8_t  Resv_64[36];
    volatile uint32_t BA_LO;                     /* Ring Base Address Lo Register Aliased */
    volatile uint32_t BA_HI;                     /* Ring Base Address Hi Register Aliased */
    volatile uint32_t SIZE;                      /* Ring Size */
    volatile uint8_t  Resv_256[180];
    volatile uint32_t INTSRC;                    /* Interrupt Source */
    volatile uint8_t  Resv_288[28];
    volatile uint32_t INTPACE;                   /* Interrupt Pacing */
    volatile uint8_t  Resv_320[28];
    volatile uint32_t INT_ENABLE_SET;            /* Interrupt Enable Set */
    volatile uint8_t  Resv_328[4];
    volatile uint32_t INT_ENABLE_CLR;            /* Interrupt Enable Clear */
    volatile uint8_t  Resv_336[4];
    volatile uint32_t INT_STATUS_SET;            /* Interrupt Status */
    volatile uint8_t  Resv_344[4];
    volatile uint32_t INT_STATUS;                /* Interrupt Status */
    volatile uint8_t  Resv_352[4];
    volatile uint32_t INT_STATUS_MSKD;           /* Interrupt Status Masked */
    volatile uint8_t  Resv_360[4];
    volatile uint32_t RFLOWFWSTAT;               /* Rx Flow ID Firewall Status Register 0 */
    volatile uint8_t  Resv_4112[3748];
    volatile uint32_t RDB;                       /* Realtime Ring N Reverse Doorbell Register */
    volatile uint8_t  Resv_4120[4];
    volatile uint32_t ROCC;                      /* Realtime Ring N Reverse Occupancy Register */
    volatile uint8_t  Resv_8192[4068];
} CSL_lcdma_ringacc_flowrt_v2Regs_flow;


typedef struct {
    CSL_lcdma_ringacc_flowrt_v2Regs_flow FLOW[158];
} CSL_lcdma_ringacc_flowrt_v2Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA(FLOW)                             (0x00000008U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FDB(FLOW)                             (0x00000010U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FOCC(FLOW)                            (0x00000018U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_LO(FLOW)                           (0x00000040U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI(FLOW)                           (0x00000044U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE(FLOW)                            (0x00000048U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC(FLOW)                          (0x00000100U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE(FLOW)                         (0x00000120U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET(FLOW)                  (0x00000140U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR(FLOW)                  (0x00000148U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET(FLOW)                  (0x00000150U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS(FLOW)                      (0x00000158U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD(FLOW)                 (0x00000160U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT(FLOW)                     (0x00000168U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB(FLOW)                             (0x00001010U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC(FLOW)                            (0x00001018U+((FLOW)*0x2000U))

/**************************************************************************
* 64K Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8_t  Resv_8[8];
    volatile uint32_t RFA;                       /* Rx Flow Config Register A */
    volatile uint8_t  Resv_16[4];
    volatile uint32_t FDB;                       /* Realtime Ring N Forward Doorbell Register */
    volatile uint8_t  Resv_24[4];
    volatile uint32_t FOCC;                      /* Realtime Ring N Forward Occupancy Register */
    volatile uint8_t  Resv_64[36];
    volatile uint32_t BA_LO;                     /* Ring Base Address Lo Register Aliased */
    volatile uint32_t BA_HI;                     /* Ring Base Address Hi Register Aliased */
    volatile uint32_t SIZE;                      /* Ring Size */
    volatile uint8_t  Resv_256[180];
    volatile uint32_t INTSRC;                    /* Interrupt Source */
    volatile uint8_t  Resv_288[28];
    volatile uint32_t INTPACE;                   /* Interrupt Pacing */
    volatile uint8_t  Resv_320[28];
    volatile uint32_t INT_ENABLE_SET;            /* Interrupt Enable Set */
    volatile uint8_t  Resv_328[4];
    volatile uint32_t INT_ENABLE_CLR;            /* Interrupt Enable Clear */
    volatile uint8_t  Resv_336[4];
    volatile uint32_t INT_STATUS_SET;            /* Interrupt Status */
    volatile uint8_t  Resv_344[4];
    volatile uint32_t INT_STATUS;                /* Interrupt Status */
    volatile uint8_t  Resv_352[4];
    volatile uint32_t INT_STATUS_MSKD;           /* Interrupt Status Masked */
    volatile uint8_t  Resv_360[4];
    volatile uint32_t RFLOWFWSTAT;               /* Rx Flow ID Firewall Status Register 0 */
    volatile uint8_t  Resv_4112[3748];
    volatile uint32_t RDB;                       /* Realtime Ring N Reverse Doorbell Register */
    volatile uint8_t  Resv_4120[4];
    volatile uint32_t ROCC;                      /* Realtime Ring N Reverse Occupancy Register */
    volatile uint8_t  Resv_8192[4068];
} CSL_lcdma_ringacc_flowrt_v2Regs64_flow;


typedef struct {
    CSL_lcdma_ringacc_flowrt_v2Regs64_flow FLOW[158];
} CSL_lcdma_ringacc_flowrt_v2Regs64;


/**************************************************************************
* 64K Register Macros
**************************************************************************/

#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_RFA(FLOW)                          (0x00000008U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_FDB(FLOW)                          (0x00000010U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_FOCC(FLOW)                         (0x00000018U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_BA_LO(FLOW)                        (0x00000040U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_BA_HI(FLOW)                        (0x00000044U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_SIZE(FLOW)                         (0x00000048U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_INTSRC(FLOW)                       (0x00000100U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_INTPACE(FLOW)                      (0x00000120U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_INT_ENABLE_SET(FLOW)               (0x00000140U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_INT_ENABLE_CLR(FLOW)               (0x00000148U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_INT_STATUS_SET(FLOW)               (0x00000150U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_INT_STATUS(FLOW)                   (0x00000158U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_INT_STATUS_MSKD(FLOW)              (0x00000160U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_RFLOWFWSTAT(FLOW)                  (0x00000168U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_RDB(FLOW)                          (0x00001010U+((FLOW)*0x2000U))
#define CSL_LCDMA_RINGACC_FLOWRT_V2_64_FLOW_ROCC(FLOW)                         (0x00001018U+((FLOW)*0x2000U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RFA */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_EINFO_MASK                        (0x40000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_EINFO_SHIFT                       (0x0000001EU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_EINFO_RESETVAL                    (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_EINFO_MAX                         (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_PSINFO_MASK                       (0x20000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_PSINFO_SHIFT                      (0x0000001DU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_PSINFO_RESETVAL                   (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_PSINFO_MAX                        (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_EHANDLING_MASK                    (0x10000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_EHANDLING_SHIFT                   (0x0000001CU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_EHANDLING_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_EHANDLING_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_SOP_OFF_MASK                      (0x01FF0000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_SOP_OFF_SHIFT                     (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_SOP_OFF_RESETVAL                  (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_SOP_OFF_MAX                       (0x000001FFU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFA_RESETVAL                          (0x00000000U)

/* FDB */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FDB_CNT_MASK                          (0x000000FFU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FDB_CNT_SHIFT                         (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FDB_CNT_RESETVAL                      (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FDB_CNT_MAX                           (0x000000FFU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FDB_RESETVAL                          (0x00000000U)

/* FOCC */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FOCC_CNT_MASK                         (0x0001FFFFU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FOCC_CNT_SHIFT                        (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FOCC_CNT_RESETVAL                     (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FOCC_CNT_MAX                          (0x0001FFFFU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_FOCC_RESETVAL                         (0x00000000U)

/* BA_LO */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_LO_ADDR_LO_MASK                    (0xFFFFFFFFU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_LO_ADDR_LO_SHIFT                   (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_LO_ADDR_LO_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_LO_ADDR_LO_MAX                     (0xFFFFFFFFU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_LO_RESETVAL                        (0x00000000U)

/* BA_HI */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI_ASEL_MASK                       (0x000F0000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI_ASEL_SHIFT                      (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI_ASEL_RESETVAL                   (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI_ASEL_MAX                        (0x0000000FU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI_ADDR_HI_MASK                    (0x0000000FU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI_ADDR_HI_SHIFT                   (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI_ADDR_HI_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI_ADDR_HI_MAX                     (0x0000000FU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_BA_HI_RESETVAL                        (0x00000000U)

/* SIZE */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_QMODE_MASK                       (0xE0000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_QMODE_SHIFT                      (0x0000001DU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_QMODE_RESETVAL                   (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_QMODE_MAX                        (0x00000007U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_QMODE_VAL_DRING_MODE             (0x1U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_ELSIZE_MASK                      (0x07000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_ELSIZE_SHIFT                     (0x00000018U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_ELSIZE_RESETVAL                  (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_ELSIZE_MAX                       (0x00000007U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_ELCNT_MASK                       (0x0000FFFFU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_ELCNT_SHIFT                      (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_ELCNT_RESETVAL                   (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_ELCNT_MAX                        (0x0000FFFFU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_SIZE_RESETVAL                         (0x21000000U)

/* INTSRC */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR0_MASK                     (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR0_SHIFT                    (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR0_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR0_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR1_MASK                     (0x00000002U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR1_SHIFT                    (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR1_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR1_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR2_MASK                     (0x00000004U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR2_SHIFT                    (0x00000002U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR2_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR2_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR3_MASK                     (0x00000008U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR3_SHIFT                    (0x00000003U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR3_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR3_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR4_MASK                     (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR4_SHIFT                    (0x00000004U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR4_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR4_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR5_MASK                     (0x00000020U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR5_SHIFT                    (0x00000005U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR5_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR5_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR6_MASK                     (0x00000040U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR6_SHIFT                    (0x00000006U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR6_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR6_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR7_MASK                     (0x00000080U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR7_SHIFT                    (0x00000007U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR7_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR7_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR8_MASK                     (0x00000100U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR8_SHIFT                    (0x00000008U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR8_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR8_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR9_MASK                     (0x00000200U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR9_SHIFT                    (0x00000009U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR9_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR9_MAX                      (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR10_MASK                    (0x00000400U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR10_SHIFT                   (0x0000000AU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR10_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR10_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR11_MASK                    (0x00000800U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR11_SHIFT                   (0x0000000BU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR11_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR11_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR12_MASK                    (0x00001000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR12_SHIFT                   (0x0000000CU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR12_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR12_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR13_MASK                    (0x00002000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR13_SHIFT                   (0x0000000DU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR13_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR13_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR14_MASK                    (0x00004000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR14_SHIFT                   (0x0000000EU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR14_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR14_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR15_MASK                    (0x00008000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR15_SHIFT                   (0x0000000FU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR15_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR15_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR16_MASK                    (0x00010000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR16_SHIFT                   (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR16_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR16_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR17_MASK                    (0x00020000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR17_SHIFT                   (0x00000011U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR17_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR17_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR18_MASK                    (0x00040000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR18_SHIFT                   (0x00000012U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR18_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR18_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR19_MASK                    (0x00080000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR19_SHIFT                   (0x00000013U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR19_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR19_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR20_MASK                    (0x00100000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR20_SHIFT                   (0x00000014U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR20_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR20_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR21_MASK                    (0x00200000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR21_SHIFT                   (0x00000015U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR21_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR21_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR22_MASK                    (0x00400000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR22_SHIFT                   (0x00000016U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR22_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR22_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR23_MASK                    (0x00800000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR23_SHIFT                   (0x00000017U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR23_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR23_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR24_MASK                    (0x01000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR24_SHIFT                   (0x00000018U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR24_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR24_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR25_MASK                    (0x02000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR25_SHIFT                   (0x00000019U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR25_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR25_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR26_MASK                    (0x04000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR26_SHIFT                   (0x0000001AU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR26_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR26_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR27_MASK                    (0x08000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR27_SHIFT                   (0x0000001BU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR27_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR27_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR28_MASK                    (0x10000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR28_SHIFT                   (0x0000001CU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR28_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR28_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR29_MASK                    (0x20000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR29_SHIFT                   (0x0000001DU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR29_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR29_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR30_MASK                    (0x40000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR30_SHIFT                   (0x0000001EU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR30_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR30_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR31_MASK                    (0x80000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR31_SHIFT                   (0x0000001FU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR31_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_INTR31_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTSRC_RESETVAL                       (0x00000000U)

/* INTPACE */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE_ENABLE_MASK                   (0x80000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE_ENABLE_SHIFT                  (0x0000001FU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE_ENABLE_RESETVAL               (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE_ENABLE_MAX                    (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE_IMAX_MASK                     (0x0000003FU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE_IMAX_SHIFT                    (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE_IMAX_RESETVAL                 (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE_IMAX_MAX                      (0x0000003FU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INTPACE_RESETVAL                      (0x00000000U)

/* INT_ENABLE_SET */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_COMPLETE_MASK          (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_COMPLETE_SHIFT         (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_COMPLETE_RESETVAL      (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_COMPLETE_MAX           (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_ERROR_MASK             (0x00000002U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_ERROR_SHIFT            (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_ERROR_RESETVAL         (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_ERROR_MAX              (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_FLOWFW_MASK            (0x00000008U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_FLOWFW_SHIFT           (0x00000003U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_FLOWFW_RESETVAL        (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_FLOWFW_MAX             (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_PKTWAIT_MASK           (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_PKTWAIT_SHIFT          (0x00000004U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_PKTWAIT_RESETVAL       (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_PKTWAIT_MAX            (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_SET_RESETVAL               (0x00000000U)

/* INT_ENABLE_CLR */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_COMPLETE_MASK          (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_COMPLETE_SHIFT         (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_COMPLETE_RESETVAL      (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_COMPLETE_MAX           (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_ERROR_MASK             (0x00000002U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_ERROR_SHIFT            (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_ERROR_RESETVAL         (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_ERROR_MAX              (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_FLOWFW_MASK            (0x00000008U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_FLOWFW_SHIFT           (0x00000003U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_FLOWFW_RESETVAL        (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_FLOWFW_MAX             (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_PKTWAIT_MASK           (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_PKTWAIT_SHIFT          (0x00000004U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_PKTWAIT_RESETVAL       (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_PKTWAIT_MAX            (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_ENABLE_CLR_RESETVAL               (0x00000000U)

/* INT_STATUS_SET */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_COMPLETE_MASK          (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_COMPLETE_SHIFT         (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_COMPLETE_RESETVAL      (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_COMPLETE_MAX           (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_ERROR_MASK             (0x00000002U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_ERROR_SHIFT            (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_ERROR_RESETVAL         (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_ERROR_MAX              (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_FLOWFW_MASK            (0x00000008U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_FLOWFW_SHIFT           (0x00000003U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_FLOWFW_RESETVAL        (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_FLOWFW_MAX             (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_PKTWAIT_MASK           (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_PKTWAIT_SHIFT          (0x00000004U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_PKTWAIT_RESETVAL       (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_PKTWAIT_MAX            (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_SET_RESETVAL               (0x00000000U)

/* INT_STATUS */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_COMPLETE_MASK              (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_COMPLETE_SHIFT             (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_COMPLETE_RESETVAL          (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_COMPLETE_MAX               (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_ERROR_MASK                 (0x00000002U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_ERROR_SHIFT                (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_ERROR_RESETVAL             (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_ERROR_MAX                  (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_FLOWFW_MASK                (0x00000008U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_FLOWFW_SHIFT               (0x00000003U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_FLOWFW_RESETVAL            (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_FLOWFW_MAX                 (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_PKTWAIT_MASK               (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_PKTWAIT_SHIFT              (0x00000004U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_PKTWAIT_RESETVAL           (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_PKTWAIT_MAX                (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_RESETVAL                   (0x00000000U)

/* INT_STATUS_MSKD */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_COMPLETE_MASK         (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_COMPLETE_SHIFT        (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_COMPLETE_RESETVAL     (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_COMPLETE_MAX          (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_ERROR_MASK            (0x00000002U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_ERROR_SHIFT           (0x00000001U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_ERROR_RESETVAL        (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_ERROR_MAX             (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_FLOWFW_MASK           (0x00000008U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_FLOWFW_SHIFT          (0x00000003U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_FLOWFW_RESETVAL       (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_FLOWFW_MAX            (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_PKTWAIT_MASK          (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_PKTWAIT_SHIFT         (0x00000004U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_PKTWAIT_RESETVAL      (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_PKTWAIT_MAX           (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_INT_STATUS_MSKD_RESETVAL              (0x00000000U)

/* RFLOWFWSTAT */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_PEND_MASK                 (0x80000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_PEND_SHIFT                (0x0000001FU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_PEND_RESETVAL             (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_PEND_MAX                  (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_FLOWID_MASK               (0x3FFF0000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_FLOWID_SHIFT              (0x00000010U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_FLOWID_RESETVAL           (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_FLOWID_MAX                (0x00003FFFU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_CHANNEL_MASK              (0x000001FFU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_CHANNEL_SHIFT             (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_CHANNEL_RESETVAL          (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_CHANNEL_MAX               (0x000001FFU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RFLOWFWSTAT_RESETVAL                  (0x00000000U)

/* RDB */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB_ACK_MASK                          (0x80000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB_ACK_SHIFT                         (0x0000001FU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB_ACK_RESETVAL                      (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB_ACK_MAX                           (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB_CNT_MASK                          (0x000000FFU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB_CNT_SHIFT                         (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB_CNT_RESETVAL                      (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB_CNT_MAX                           (0x000000FFU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_RDB_RESETVAL                          (0x00000000U)

/* ROCC */

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC_COMP_MASK                        (0x80000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC_COMP_SHIFT                       (0x0000001FU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC_COMP_RESETVAL                    (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC_COMP_MAX                         (0x00000001U)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC_CNT_MASK                         (0x0001FFFFU)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC_CNT_SHIFT                        (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC_CNT_RESETVAL                     (0x00000000U)
#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC_CNT_MAX                          (0x0001FFFFU)

#define CSL_LCDMA_RINGACC_FLOWRT_V2_FLOW_ROCC_RESETVAL                         (0x00000000U)

/**************************************************************************
* Hardware Region  : Ring Credentials Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CRED;                      /* Credentials Register */
    volatile uint8_t  Resv_16[12];
} CSL_lcdma_ringacc_cred_v2Regs_ring;


typedef struct {
    CSL_lcdma_ringacc_cred_v2Regs_ring RING[158];
} CSL_lcdma_ringacc_cred_v2Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED(RING)                              (0x00000000U+((RING)*0x10U))

/**************************************************************************
* 64K Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CRED;                      /* Credentials Register */
    volatile uint8_t  Resv_16[12];
} CSL_lcdma_ringacc_cred_v2Regs64_ring;


typedef struct {
    CSL_lcdma_ringacc_cred_v2Regs64_ring RING[158];
} CSL_lcdma_ringacc_cred_v2Regs64;


/**************************************************************************
* 64K Register Macros
**************************************************************************/

#define CSL_LCDMA_RINGACC_CRED_V2_64_RING_CRED(RING)                           (0x00000000U+((RING)*0x10U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CRED */

#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_CHK_SECURE_MASK                    (0x80000000U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_CHK_SECURE_SHIFT                   (0x0000001FU)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_CHK_SECURE_RESETVAL                (0x00000000U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_CHK_SECURE_MAX                     (0x00000001U)

#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_SECURE_MASK                        (0x04000000U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_SECURE_SHIFT                       (0x0000001AU)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_SECURE_RESETVAL                    (0x00000000U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_SECURE_MAX                         (0x00000001U)

#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_PRIV_MASK                          (0x03000000U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_PRIV_SHIFT                         (0x00000018U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_PRIV_RESETVAL                      (0x00000000U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_PRIV_MAX                           (0x00000003U)

#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_PRIVID_MASK                        (0x00FF0000U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_PRIVID_SHIFT                       (0x00000010U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_PRIVID_RESETVAL                    (0x00000000U)
#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_PRIVID_MAX                         (0x000000FFU)

#define CSL_LCDMA_RINGACC_CRED_V2_RING_CRED_RESETVAL                           (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
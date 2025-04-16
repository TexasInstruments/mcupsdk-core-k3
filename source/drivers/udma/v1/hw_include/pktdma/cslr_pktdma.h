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
 *  Name        : cslr_pktdma.h
 *  VPVERSION   : 3.0.366 - 2024.01.19.14.34.16
 *  VPREV       : 1.0.8
*/
#ifndef CSLR_PKTDMA_H_
#define CSLR_PKTDMA_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : PKTDMA Control / Status Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CNTCTL;                    /* Debug Counter Control */
    volatile uint32_t EVTCTL;                    /* Debug Event Control */
    volatile uint32_t CNT;                       /* Debug Counter */
    volatile uint8_t  Resv_16[4];
} CSL_pktdma_gcfg_v2Regs_dbgcnt;


typedef struct {
    volatile uint32_t REVISION;                  /* Revision Register */
    volatile uint8_t  Resv_32[28];
    volatile uint32_t CAP0;                      /* Capabilities Register 0 */
    volatile uint32_t CAP1;                      /* Capabilities Register 1 */
    volatile uint32_t CAP2;                      /* Capabilities Register 2 */
    volatile uint32_t CAP3;                      /* Capabilities Register 3 */
    volatile uint32_t CAP4;                      /* Capabilities Register 4 */
    volatile uint32_t CAP5;                      /* Capabilities Register 5 */
    volatile uint8_t  Resv_4096[4040];
    volatile uint32_t PERF_CTRL;                 /* Performance Control Register */
    volatile uint32_t EMU_CTRL;                  /* Emulation Control Register */
    volatile uint32_t PSIL_TO;                   /* PSI-L Proxy Timeout Register */
    volatile uint8_t  Resv_4160[52];
    volatile uint32_t DBGADDR;                   /* Debug Address Register */
    volatile uint32_t DBGDATA;                   /* Debug Data Register */
    volatile uint8_t  Resv_4352[184];
    CSL_pktdma_gcfg_v2Regs_dbgcnt DBGCNT[5];
    volatile uint8_t  Resv_8192[3760];
    volatile uint32_t PM0;                       /* Power Management Register 0 */
    volatile uint32_t PM1;                       /* Power Management Register 1 */
    volatile uint8_t  Resv_12288[4088];
    volatile uint32_t INTPACE;                   /* Interrupt Pacing Control */
} CSL_pktdma_gcfg_v2Regs;

/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_PKTDMA_GCFG_V2_REVISION                                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP0                                                (0x00000020U)
#define CSL_PKTDMA_GCFG_V2_CAP1                                                (0x00000024U)
#define CSL_PKTDMA_GCFG_V2_CAP2                                                (0x00000028U)
#define CSL_PKTDMA_GCFG_V2_CAP3                                                (0x0000002CU)
#define CSL_PKTDMA_GCFG_V2_CAP4                                                (0x00000030U)
#define CSL_PKTDMA_GCFG_V2_CAP5                                                (0x00000034U)
#define CSL_PKTDMA_GCFG_V2_PERF_CTRL                                           (0x00001000U)
#define CSL_PKTDMA_GCFG_V2_EMU_CTRL                                            (0x00001004U)
#define CSL_PKTDMA_GCFG_V2_PSIL_TO                                             (0x00001008U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR                                             (0x00001040U)
#define CSL_PKTDMA_GCFG_V2_DBGDATA                                             (0x00001044U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL(DBGCNT)                               (0x00001100U+((DBGCNT)*0x10U))
#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL(DBGCNT)                               (0x00001104U+((DBGCNT)*0x10U))
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNT(DBGCNT)                                  (0x00001108U+((DBGCNT)*0x10U))
#define CSL_PKTDMA_GCFG_V2_PM0                                                 (0x00002000U)
#define CSL_PKTDMA_GCFG_V2_PM1                                                 (0x00002004U)
#define CSL_PKTDMA_GCFG_V2_INTPACE                                             (0x00003000U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* CNTCTL */

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_TYPE_MASK                             (0xC0000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_TYPE_SHIFT                            (0x0000001EU)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_TYPE_RESETVAL                         (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_TYPE_MAX                              (0x00000003U)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_TYPE_VAL_INCR                         (0x0U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_TYPE_VAL_ONESHOT                      (0x1U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_TYPE_VAL_CONT                         (0x2U)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_MASK                          (0x1E000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_SHIFT                         (0x00000019U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_MAX                           (0x0000000FU)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_VAL_SCHED                     (0x0U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_VAL_RD_CMD                    (0x1U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_VAL_WR_CMD                    (0x2U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_VAL_RD_RESP                   (0x3U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_VAL_WR_RESP                   (0x4U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_VAL_RD_RESP_EOP               (0x5U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_VAL_WR_RESP_EOP               (0x6U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPEVT_VAL_CNT_EVT                   (0x8U)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPFLOW_MASK                         (0x01FF0000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPFLOW_SHIFT                        (0x00000010U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPFLOW_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STOPFLOW_MAX                          (0x000001FFU)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_MASK                         (0x00001E00U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_SHIFT                        (0x00000009U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_MAX                          (0x0000000FU)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_VAL_SCHED                    (0x0U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_VAL_RD_CMD                   (0x1U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_VAL_WR_CMD                   (0x2U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_VAL_RD_RESP                  (0x3U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_VAL_WR_RESP                  (0x4U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_VAL_RD_RESP_EOP              (0x5U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_VAL_WR_RESP_EOP              (0x6U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTEVT_VAL_CNT_EVT                  (0x8U)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTFLOW_MASK                        (0x000001FFU)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTFLOW_SHIFT                       (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTFLOW_RESETVAL                    (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_STARTFLOW_MAX                         (0x000001FFU)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNTCTL_RESETVAL                              (0x00000000U)

/* EVTCTL */

#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_EVTTYPE_MASK                          (0xC0000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_EVTTYPE_SHIFT                         (0x0000001EU)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_EVTTYPE_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_EVTTYPE_MAX                           (0x00000003U)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_EVTTYPE_VAL_NO_EVT                    (0x0U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_EVTTYPE_VAL_EXACT                     (0x1U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_EVTTYPE_VAL_AND_MASK                  (0x2U)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_CNTMATCH_MASK                         (0x0000FFFFU)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_CNTMATCH_SHIFT                        (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_CNTMATCH_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_CNTMATCH_MAX                          (0x0000FFFFU)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_EVTCTL_RESETVAL                              (0x00000000U)

/* CNT */

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNT_CNT_MASK                                 (0x0000FFFFU)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNT_CNT_SHIFT                                (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNT_CNT_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNT_CNT_MAX                                  (0x0000FFFFU)

#define CSL_PKTDMA_GCFG_V2_DBGCNT_CNT_RESETVAL                                 (0x00000000U)

/* REVISION */

#define CSL_PKTDMA_GCFG_V2_REVISION_MODID_MASK                                 (0xFFFF0000U)
#define CSL_PKTDMA_GCFG_V2_REVISION_MODID_SHIFT                                (0x00000010U)
#define CSL_PKTDMA_GCFG_V2_REVISION_MODID_RESETVAL                             (0x0000662EU)
#define CSL_PKTDMA_GCFG_V2_REVISION_MODID_MAX                                  (0x0000FFFFU)

#define CSL_PKTDMA_GCFG_V2_REVISION_REVRTL_MASK                                (0x0000F800U)
#define CSL_PKTDMA_GCFG_V2_REVISION_REVRTL_SHIFT                               (0x0000000BU)
#define CSL_PKTDMA_GCFG_V2_REVISION_REVRTL_RESETVAL                            (0x00000010U)
#define CSL_PKTDMA_GCFG_V2_REVISION_REVRTL_MAX                                 (0x0000001FU)

#define CSL_PKTDMA_GCFG_V2_REVISION_REVMAJ_MASK                                (0x00000700U)
#define CSL_PKTDMA_GCFG_V2_REVISION_REVMAJ_SHIFT                               (0x00000008U)
#define CSL_PKTDMA_GCFG_V2_REVISION_REVMAJ_RESETVAL                            (0x00000002U)
#define CSL_PKTDMA_GCFG_V2_REVISION_REVMAJ_MAX                                 (0x00000007U)

#define CSL_PKTDMA_GCFG_V2_REVISION_CUSTOM_MASK                                (0x000000C0U)
#define CSL_PKTDMA_GCFG_V2_REVISION_CUSTOM_SHIFT                               (0x00000006U)
#define CSL_PKTDMA_GCFG_V2_REVISION_CUSTOM_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_REVISION_CUSTOM_MAX                                 (0x00000003U)

#define CSL_PKTDMA_GCFG_V2_REVISION_REVMIN_MASK                                (0x0000003FU)
#define CSL_PKTDMA_GCFG_V2_REVISION_REVMIN_SHIFT                               (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_REVISION_REVMIN_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_REVISION_REVMIN_MAX                                 (0x0000003FU)

#define CSL_PKTDMA_GCFG_V2_REVISION_RESETVAL                                   (0x662E8200U)

/* CAP0 */


/* CAP1 */


/* CAP2 */

#define CSL_PKTDMA_GCFG_V2_CAP2_RCHAN_CNT_MASK                                 (0x07FC0000U)
#define CSL_PKTDMA_GCFG_V2_CAP2_RCHAN_CNT_SHIFT                                (0x00000012U)
#define CSL_PKTDMA_GCFG_V2_CAP2_RCHAN_CNT_RESETVAL                             (0x0000000CU)
#define CSL_PKTDMA_GCFG_V2_CAP2_RCHAN_CNT_MAX                                  (0x000001FFU)

#define CSL_PKTDMA_GCFG_V2_CAP2_TCHAN_CNT_MASK                                 (0x0003FE00U)
#define CSL_PKTDMA_GCFG_V2_CAP2_TCHAN_CNT_SHIFT                                (0x00000009U)
#define CSL_PKTDMA_GCFG_V2_CAP2_TCHAN_CNT_RESETVAL                             (0x00000013U)
#define CSL_PKTDMA_GCFG_V2_CAP2_TCHAN_CNT_MAX                                  (0x000001FFU)

#define CSL_PKTDMA_GCFG_V2_CAP2_CHAN_CNT_MASK                                  (0x000001FFU)
#define CSL_PKTDMA_GCFG_V2_CAP2_CHAN_CNT_SHIFT                                 (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP2_CHAN_CNT_RESETVAL                              (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP2_CHAN_CNT_MAX                                   (0x000001FFU)

#define CSL_PKTDMA_GCFG_V2_CAP2_RESETVAL                                       (0x00302600U)

/* CAP3 */

#define CSL_PKTDMA_GCFG_V2_CAP3_UCHAN_CNT_MASK                                 (0xFF800000U)
#define CSL_PKTDMA_GCFG_V2_CAP3_UCHAN_CNT_SHIFT                                (0x00000017U)
#define CSL_PKTDMA_GCFG_V2_CAP3_UCHAN_CNT_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP3_UCHAN_CNT_MAX                                  (0x000001FFU)

#define CSL_PKTDMA_GCFG_V2_CAP3_HCHAN_CNT_MASK                                 (0x007FC000U)
#define CSL_PKTDMA_GCFG_V2_CAP3_HCHAN_CNT_SHIFT                                (0x0000000EU)
#define CSL_PKTDMA_GCFG_V2_CAP3_HCHAN_CNT_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP3_HCHAN_CNT_MAX                                  (0x000001FFU)

#define CSL_PKTDMA_GCFG_V2_CAP3_RESETVAL                                       (0x00000000U)

/* CAP4 */

#define CSL_PKTDMA_GCFG_V2_CAP4_TUCHAN_CNT_MASK                                (0xFF000000U)
#define CSL_PKTDMA_GCFG_V2_CAP4_TUCHAN_CNT_SHIFT                               (0x00000018U)
#define CSL_PKTDMA_GCFG_V2_CAP4_TUCHAN_CNT_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP4_TUCHAN_CNT_MAX                                 (0x000000FFU)

#define CSL_PKTDMA_GCFG_V2_CAP4_THCHAN_CNT_MASK                                (0x00FF0000U)
#define CSL_PKTDMA_GCFG_V2_CAP4_THCHAN_CNT_SHIFT                               (0x00000010U)
#define CSL_PKTDMA_GCFG_V2_CAP4_THCHAN_CNT_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP4_THCHAN_CNT_MAX                                 (0x000000FFU)

#define CSL_PKTDMA_GCFG_V2_CAP4_RUCHAN_CNT_MASK                                (0x0000FF00U)
#define CSL_PKTDMA_GCFG_V2_CAP4_RUCHAN_CNT_SHIFT                               (0x00000008U)
#define CSL_PKTDMA_GCFG_V2_CAP4_RUCHAN_CNT_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP4_RUCHAN_CNT_MAX                                 (0x000000FFU)

#define CSL_PKTDMA_GCFG_V2_CAP4_RHCHAN_CNT_MASK                                (0x000000FFU)
#define CSL_PKTDMA_GCFG_V2_CAP4_RHCHAN_CNT_SHIFT                               (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP4_RHCHAN_CNT_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP4_RHCHAN_CNT_MAX                                 (0x000000FFU)

#define CSL_PKTDMA_GCFG_V2_CAP4_RESETVAL                                       (0x00000000U)

/* CAP5 */

#define CSL_PKTDMA_GCFG_V2_CAP5_RFLOW_CNT_MASK                                 (0x00003FFFU)
#define CSL_PKTDMA_GCFG_V2_CAP5_RFLOW_CNT_SHIFT                                (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_CAP5_RFLOW_CNT_RESETVAL                             (0x0000001BU)
#define CSL_PKTDMA_GCFG_V2_CAP5_RFLOW_CNT_MAX                                  (0x00003FFFU)

#define CSL_PKTDMA_GCFG_V2_CAP5_TFLOW_CNT_MASK                                 (0x3FFF0000U)
#define CSL_PKTDMA_GCFG_V2_CAP5_TFLOW_CNT_SHIFT                                (0x00000010U)
#define CSL_PKTDMA_GCFG_V2_CAP5_TFLOW_CNT_RESETVAL                             (0x0000001BU)
#define CSL_PKTDMA_GCFG_V2_CAP5_TFLOW_CNT_MAX                                  (0x00003FFFU)

#define CSL_PKTDMA_GCFG_V2_CAP5_RESETVAL                                       (0x001B001BU)

/* PERF_CTRL */

#define CSL_PKTDMA_GCFG_V2_PERF_CTRL_TIMEOUT_CNT_MASK                          (0x0000FFFFU)
#define CSL_PKTDMA_GCFG_V2_PERF_CTRL_TIMEOUT_CNT_SHIFT                         (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PERF_CTRL_TIMEOUT_CNT_RESETVAL                      (0x00000040U)
#define CSL_PKTDMA_GCFG_V2_PERF_CTRL_TIMEOUT_CNT_MAX                           (0x0000FFFFU)

#define CSL_PKTDMA_GCFG_V2_PERF_CTRL_RESETVAL                                  (0x00000040U)

/* EMU_CTRL */

#define CSL_PKTDMA_GCFG_V2_EMU_CTRL_SOFT_MASK                                  (0x00000002U)
#define CSL_PKTDMA_GCFG_V2_EMU_CTRL_SOFT_SHIFT                                 (0x00000001U)
#define CSL_PKTDMA_GCFG_V2_EMU_CTRL_SOFT_RESETVAL                              (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_EMU_CTRL_SOFT_MAX                                   (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_EMU_CTRL_FREE_MASK                                  (0x00000001U)
#define CSL_PKTDMA_GCFG_V2_EMU_CTRL_FREE_SHIFT                                 (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_EMU_CTRL_FREE_RESETVAL                              (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_EMU_CTRL_FREE_MAX                                   (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_EMU_CTRL_RESETVAL                                   (0x00000000U)

/* PSIL_TO */

#define CSL_PKTDMA_GCFG_V2_PSIL_TO_TOUT_MASK                                   (0x80000000U)
#define CSL_PKTDMA_GCFG_V2_PSIL_TO_TOUT_SHIFT                                  (0x0000001FU)
#define CSL_PKTDMA_GCFG_V2_PSIL_TO_TOUT_RESETVAL                               (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PSIL_TO_TOUT_MAX                                    (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PSIL_TO_TOUT_CNT_MASK                               (0x0000FFFFU)
#define CSL_PKTDMA_GCFG_V2_PSIL_TO_TOUT_CNT_SHIFT                              (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PSIL_TO_TOUT_CNT_RESETVAL                           (0x00000400U)
#define CSL_PKTDMA_GCFG_V2_PSIL_TO_TOUT_CNT_MAX                                (0x0000FFFFU)

#define CSL_PKTDMA_GCFG_V2_PSIL_TO_RESETVAL                                    (0x00000400U)

/* DBGADDR */

#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_EN_MASK                                 (0x80000000U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_EN_SHIFT                                (0x0000001FU)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_EN_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_EN_MAX                                  (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_MASK                               (0x0000FF00U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_SHIFT                              (0x00000008U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_RESETVAL                           (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_MAX                                (0x000000FFU)

#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_RDEC2                          (0x12U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_SDEC3                          (0x23U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_CFG                            (0x50U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_TSU0                           (0xB0U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_TSU1                           (0xB1U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_TSU2                           (0xB2U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_TSU3                           (0xB3U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_RSU0                           (0xC0U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_RSU1                           (0xC1U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_RSU2                           (0xC2U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_UNIT_VAL_RSU3                           (0xC3U)

#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_ADDR_MASK                               (0x000000FFU)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_ADDR_SHIFT                              (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_ADDR_RESETVAL                           (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGADDR_DBG_ADDR_MAX                                (0x000000FFU)

#define CSL_PKTDMA_GCFG_V2_DBGADDR_RESETVAL                                    (0x00000000U)

/* DBGDATA */

#define CSL_PKTDMA_GCFG_V2_DBGDATA_DBG_DATA_MASK                               (0xFFFFFFFFU)
#define CSL_PKTDMA_GCFG_V2_DBGDATA_DBG_DATA_SHIFT                              (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGDATA_DBG_DATA_RESETVAL                           (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_DBGDATA_DBG_DATA_MAX                                (0xFFFFFFFFU)

#define CSL_PKTDMA_GCFG_V2_DBGDATA_RESETVAL                                    (0x00000000U)

/* PM0 */

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_CARB_MASK                                (0x00000001U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_CARB_SHIFT                               (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_CARB_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_CARB_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_WARB_MASK                                (0x00000010U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_WARB_SHIFT                               (0x00000004U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_WARB_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_WARB_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_SDEC_MASK                                (0x00000100U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_SDEC_SHIFT                               (0x00000008U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_SDEC_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_SDEC_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDEC_MASK                                (0x00001000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDEC_SHIFT                               (0x0000000CU)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDEC_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDEC_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU0_MASK                                (0x01000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU0_SHIFT                               (0x00000018U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU0_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU0_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU1_MASK                                (0x02000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU1_SHIFT                               (0x00000019U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU1_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU1_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU2_MASK                                (0x04000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU2_SHIFT                               (0x0000001AU)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU2_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU2_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU3_MASK                                (0x08000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU3_SHIFT                               (0x0000001BU)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU3_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_TDU3_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU0_MASK                                (0x10000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU0_SHIFT                               (0x0000001CU)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU0_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU0_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU1_MASK                                (0x20000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU1_SHIFT                               (0x0000001DU)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU1_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU1_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU2_MASK                                (0x40000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU2_SHIFT                               (0x0000001EU)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU2_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU2_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU3_MASK                                (0x80000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU3_SHIFT                               (0x0000001FU)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU3_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM0_NOGATE_RDU3_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM0_RESETVAL                                        (0x00000000U)

/* PM1 */

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_TCU_MASK                                 (0x00001000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_TCU_SHIFT                                (0x0000000CU)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_TCU_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_TCU_MAX                                  (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RCU_MASK                                 (0x00002000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RCU_SHIFT                                (0x0000000DU)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RCU_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RCU_MAX                                  (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RFLOWFW_MASK                             (0x00008000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RFLOWFW_SHIFT                            (0x0000000FU)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RFLOWFW_RESETVAL                         (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RFLOWFW_MAX                              (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_CFG_MASK                                 (0x00040000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_CFG_SHIFT                                (0x00000012U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_CFG_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_CFG_MAX                                  (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_TPCF_MASK                                (0x00400000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_TPCF_SHIFT                               (0x00000016U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_TPCF_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_TPCF_MAX                                 (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RINGOCC_MASK                             (0x01000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RINGOCC_SHIFT                            (0x00000018U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RINGOCC_RESETVAL                         (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_RINGOCC_MAX                              (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_EHANDLER_MASK                            (0x02000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_EHANDLER_SHIFT                           (0x00000019U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_EHANDLER_RESETVAL                        (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_EHANDLER_MAX                             (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_P2P_MASK                                 (0x08000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_P2P_SHIFT                                (0x0000001BU)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_P2P_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_P2P_MAX                                  (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_PROXY_MASK                               (0x20000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_PROXY_SHIFT                              (0x0000001DU)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_PROXY_RESETVAL                           (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_PROXY_MAX                                (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_STATS_MASK                               (0x40000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_STATS_SHIFT                              (0x0000001EU)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_STATS_RESETVAL                           (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_PM1_NOGATE_STATS_MAX                                (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_PM1_RESETVAL                                        (0x00000000U)

/* INTPACE */

#define CSL_PKTDMA_GCFG_V2_INTPACE_INT_TEST_MASK                               (0x80000000U)
#define CSL_PKTDMA_GCFG_V2_INTPACE_INT_TEST_SHIFT                              (0x0000001FU)
#define CSL_PKTDMA_GCFG_V2_INTPACE_INT_TEST_RESETVAL                           (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_INTPACE_INT_TEST_MAX                                (0x00000001U)

#define CSL_PKTDMA_GCFG_V2_INTPACE_INT_PRESCALE_MASK                           (0x00000FFFU)
#define CSL_PKTDMA_GCFG_V2_INTPACE_INT_PRESCALE_SHIFT                          (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_INTPACE_INT_PRESCALE_RESETVAL                       (0x00000000U)
#define CSL_PKTDMA_GCFG_V2_INTPACE_INT_PRESCALE_MAX                            (0x00000FFFU)

#define CSL_PKTDMA_GCFG_V2_INTPACE_RESETVAL                                    (0x00000000U)

/**************************************************************************
* Hardware Region  : Channel Configuration Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CFG;                       /* Channel Configuration Register */
    volatile uint8_t  Resv_8[4];
    volatile uint32_t RESRC;                     /* Resource Register */
    volatile uint8_t  Resv_100[88];
    volatile uint32_t PRI_CTRL;                  /* Channel Priority Control Register */
    volatile uint32_t THREAD;                    /* Channel Destination ThreadID Mapping Register */
    volatile uint8_t  Resv_112[4];
    volatile uint32_t FIFO_DEPTH;                /* Tx Channel FIFO Depth Register */
    volatile uint8_t  Resv_128[12];
    volatile uint32_t TST_SCHED;                 /* Channel Static Scheduler Config Register */
    volatile uint8_t  Resv_256[124];
} CSL_pktdma_chcfg_v2Regs_chan;


typedef struct {
    CSL_pktdma_chcfg_v2Regs_chan CHAN[97];
} CSL_pktdma_chcfg_v2Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG(CHAN)                                     (0x00000000U+((CHAN)*0x100U))
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC(CHAN)                                   (0x00000008U+((CHAN)*0x100U))
#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL(CHAN)                                (0x00000064U+((CHAN)*0x100U))
#define CSL_PKTDMA_CHCFG_V2_CHAN_THREAD(CHAN)                                  (0x00000068U+((CHAN)*0x100U))
#define CSL_PKTDMA_CHCFG_V2_CHAN_FIFO_DEPTH(CHAN)                              (0x00000070U+((CHAN)*0x100U))
#define CSL_PKTDMA_CHCFG_V2_CHAN_TST_SCHED(CHAN)                               (0x00000080U+((CHAN)*0x100U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CFG */

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_PAUSE_ON_ERR_MASK                         (0x80000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_PAUSE_ON_ERR_SHIFT                        (0x0000001FU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_PAUSE_ON_ERR_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_PAUSE_ON_ERR_MAX                          (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_EINFO_MASK                           (0x40000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_EINFO_SHIFT                          (0x0000001EU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_EINFO_RESETVAL                       (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_EINFO_MAX                            (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_EINFO_VAL_PASS                       (0x0U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_EINFO_VAL_FILT                       (0x1U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_PSWORDS_MASK                         (0x20000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_PSWORDS_SHIFT                        (0x0000001DU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_PSWORDS_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_PSWORDS_MAX                          (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_PSWORDS_VAL_PASS                     (0x0U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_FILT_PSWORDS_VAL_FILT                     (0x1U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE_MASK                            (0x000F0000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE_SHIFT                           (0x00000010U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE_RESETVAL                        (0x00000002U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE_MAX                             (0x0000000FU)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE_VAL_UNUSED                      (0x0U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE_VAL_PBR_PKT                     (0x2U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_CHAN_TYPE_VAL_PBR_SBP                     (0x3U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_IGNORE_LONG_MASK                          (0x00004000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_IGNORE_LONG_SHIFT                         (0x0000000EU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_IGNORE_LONG_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_IGNORE_LONG_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE_MASK                           (0x00000C00U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE_SHIFT                          (0x0000000AU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE_RESETVAL                       (0x00000001U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_BURST_SIZE_MAX                            (0x00000003U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_TDTYPE_MASK                               (0x00000200U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_TDTYPE_SHIFT                              (0x00000009U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_TDTYPE_RESETVAL                           (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_TDTYPE_MAX                                (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_NOTDPKT_MASK                              (0x00000100U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_NOTDPKT_SHIFT                             (0x00000008U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_NOTDPKT_RESETVAL                          (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_NOTDPKT_MAX                               (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_CFG_RESETVAL                                  (0x00020400U)

/* RESRC */

#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_CFG_ALIAS_MASK                          (0x80000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_CFG_ALIAS_SHIFT                         (0x0000001FU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_CFG_ALIAS_RESETVAL                      (0x00000001U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_CFG_ALIAS_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_PRI_CTRL_ALIAS_MASK                     (0x40000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_PRI_CTRL_ALIAS_SHIFT                    (0x0000001EU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_PRI_CTRL_ALIAS_RESETVAL                 (0x00000001U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_PRI_CTRL_ALIAS_MAX                      (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_THRD_ID_ALIAS_MASK                      (0x20000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_THRD_ID_ALIAS_SHIFT                     (0x0000001DU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_THRD_ID_ALIAS_RESETVAL                  (0x00000001U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_THRD_ID_ALIAS_MAX                       (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_FIFO_DEPTH_ALIAS_MASK                   (0x10000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_FIFO_DEPTH_ALIAS_SHIFT                  (0x0000001CU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_FIFO_DEPTH_ALIAS_RESETVAL               (0x00000001U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_FIFO_DEPTH_ALIAS_MAX                    (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_ST_SCHED_ALIAS_MASK                     (0x08000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_ST_SCHED_ALIAS_SHIFT                    (0x0000001BU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_ST_SCHED_ALIAS_RESETVAL                 (0x00000001U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_ST_SCHED_ALIAS_MAX                      (0x00000001U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_RESRC_RESETVAL                                (0xF8000000U)

/* PRI_CTRL */

#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_PRIORITY_MASK                        (0x70000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_PRIORITY_SHIFT                       (0x0000001CU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_PRIORITY_RESETVAL                    (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_PRIORITY_MAX                         (0x00000007U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_ORDERID_MASK                         (0x0000000FU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_ORDERID_SHIFT                        (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_ORDERID_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_ORDERID_MAX                          (0x0000000FU)

#define CSL_PKTDMA_CHCFG_V2_CHAN_PRI_CTRL_RESETVAL                             (0x00000000U)

/* THREAD */

#define CSL_PKTDMA_CHCFG_V2_CHAN_THREAD_ID_MASK                                (0x0000FFFFU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_THREAD_ID_SHIFT                               (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_THREAD_ID_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_THREAD_ID_MAX                                 (0x0000FFFFU)

#define CSL_PKTDMA_CHCFG_V2_CHAN_THREAD_RESETVAL                               (0x00000000U)

/* FIFO_DEPTH */

#define CSL_PKTDMA_CHCFG_V2_CHAN_FIFO_DEPTH_FDEPTH_MASK                        (0x000000FFU)
#define CSL_PKTDMA_CHCFG_V2_CHAN_FIFO_DEPTH_FDEPTH_SHIFT                       (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_FIFO_DEPTH_FDEPTH_RESETVAL                    (0x000000C0U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_FIFO_DEPTH_FDEPTH_MAX                         (0x000000FFU)

#define CSL_PKTDMA_CHCFG_V2_CHAN_FIFO_DEPTH_RESETVAL                           (0x000000C0U)

/* TST_SCHED */

#define CSL_PKTDMA_CHCFG_V2_CHAN_TST_SCHED_PRIORITY_MASK                       (0x00000003U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_TST_SCHED_PRIORITY_SHIFT                      (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_TST_SCHED_PRIORITY_RESETVAL                   (0x00000000U)
#define CSL_PKTDMA_CHCFG_V2_CHAN_TST_SCHED_PRIORITY_MAX                        (0x00000003U)

#define CSL_PKTDMA_CHCFG_V2_CHAN_TST_SCHED_RESETVAL                            (0x00000000U)

/**************************************************************************
* Hardware Region  : Channel Realtime Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CTL;                       /* Channel Realtime Control Register */
    volatile uint32_t CFG;                       /* Channel Configuration Register Aliased */
    volatile uint8_t  Resv_64[56];
    volatile uint32_t STATUS0;                   /* Channel Realtime Status Register 0 */
    volatile uint32_t STATUS1;                   /* Channel Realtime Status Register 1 */
    volatile uint8_t  Resv_100[28];
    volatile uint32_t PRI_CTRL;                  /* Channel Priority Control Register Aliased */
    volatile uint32_t THREAD;                    /* Channel Destination ThreadID Mapping Register Aliased */
    volatile uint8_t  Resv_112[4];
    volatile uint32_t FIFO_DEPTH;                /* Tx Channel FIFO Depth Register */
    volatile uint8_t  Resv_120[4];
    volatile uint32_t TST_SCHED;                 /* Channel Static Scheduler Config Register Aliased */
    volatile uint8_t  Resv_128[4];
    volatile uint32_t STDATA[32];                /* Channel Realtime Read State Data Register */
    volatile uint32_t STDATAW[32];               /* Channel Realtime Write State Data Register */
    volatile uint8_t  Resv_1024[640];
    volatile uint32_t PCNT;                      /* Channel Real-time Packet Count Statistics Register */
    volatile uint32_t DCNT;                      /* Rx Channel Real-time Dropped Packet Count Statistics Register */
    volatile uint32_t BCNT;                      /* Channel Real-time Completed Byte Count Statistics Register */
    volatile uint8_t  Resv_1040[4];
    volatile uint32_t SBCNT;                     /* Channel Real-time Started Byte Count Statistics Register */
    volatile uint8_t  Resv_2048[1004];
    volatile uint32_t STATIC_TR_XY;              /* STATIC_TR_XY */
    volatile uint32_t STATIC_TR_Z;               /* STATIC_TR_Z */
    volatile uint32_t PDMA_LCNTS;                /* Peripheral DMA Loop Counts */
    volatile uint32_t PDMA_STATE;                /* Peripheral DMA State */
    volatile uint32_t PERIPH_BCNT;               /* Peripheral Byte Count */
    volatile uint8_t  Resv_2084[16];
    volatile uint32_t FIFO_SEL;                  /* FIFO Selection register */
    volatile uint8_t  Resv_2108[20];
    volatile uint32_t PERIPH_FZCNT;              /* Peripheral Full Z Count */
    volatile uint8_t  Resv_4096[1984];
} CSL_pktdma_chrt_v2Regs_chan;


typedef struct {
    CSL_pktdma_chrt_v2Regs_chan CHAN[97];
} CSL_pktdma_chrt_v2Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL(CHAN)                                      (0x00000000U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG(CHAN)                                      (0x00000004U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0(CHAN)                                  (0x00000040U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1(CHAN)                                  (0x00000044U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL(CHAN)                                 (0x00000064U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_THREAD(CHAN)                                   (0x00000068U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_DEPTH(CHAN)                               (0x00000070U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_TST_SCHED(CHAN)                                (0x00000078U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_STDATA(CHAN,STDATA)                            (0x00000080U+((CHAN)*0x1000U)+((STDATA)*0x4U))
#define CSL_PKTDMA_CHRT_V2_CHAN_STDATAW(CHAN,STDATAW)                          (0x00000100U+((CHAN)*0x1000U)+((STDATAW)*0x4U))
#define CSL_PKTDMA_CHRT_V2_CHAN_PCNT(CHAN)                                     (0x00000400U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_DCNT(CHAN)                                     (0x00000404U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_BCNT(CHAN)                                     (0x00000408U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_SBCNT(CHAN)                                    (0x00000410U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY(CHAN)                             (0x00000800U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z(CHAN)                              (0x00000804U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS(CHAN)                               (0x00000808U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE(CHAN)                               (0x0000080CU+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_BCNT(CHAN)                              (0x00000810U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_SEL(CHAN)                                 (0x00000824U+((CHAN)*0x1000U))
#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_FZCNT(CHAN)                             (0x0000083CU+((CHAN)*0x1000U))

/**************************************************************************
* 64K Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CTL;                       /* Channel Realtime Control Register */
    volatile uint32_t CFG;                       /* Channel Configuration Register Aliased */
    volatile uint8_t  Resv_64[56];
    volatile uint32_t STATUS0;                   /* Channel Realtime Status Register 0 */
    volatile uint32_t STATUS1;                   /* Channel Realtime Status Register 1 */
    volatile uint8_t  Resv_100[28];
    volatile uint32_t PRI_CTRL;                  /* Channel Priority Control Register Aliased */
    volatile uint32_t THREAD;                    /* Channel Destination ThreadID Mapping Register Aliased */
    volatile uint8_t  Resv_112[4];
    volatile uint32_t FIFO_DEPTH;                /* Tx Channel FIFO Depth Register */
    volatile uint8_t  Resv_120[4];
    volatile uint32_t TST_SCHED;                 /* Channel Static Scheduler Config Register Aliased */
    volatile uint8_t  Resv_128[4];
    volatile uint32_t STDATA[32];                /* Channel Realtime Read State Data Register */
    volatile uint32_t STDATAW[32];               /* Channel Realtime Write State Data Register */
    volatile uint8_t  Resv_1024[640];
    volatile uint32_t PCNT;                      /* Channel Real-time Packet Count Statistics Register */
    volatile uint32_t DCNT;                      /* Rx Channel Real-time Dropped Packet Count Statistics Register */
    volatile uint32_t BCNT;                      /* Channel Real-time Completed Byte Count Statistics Register */
    volatile uint8_t  Resv_1040[4];
    volatile uint32_t SBCNT;                     /* Channel Real-time Started Byte Count Statistics Register */
    volatile uint8_t  Resv_2048[1004];
    volatile uint32_t STATIC_TR_XY;              /* STATIC_TR_XY */
    volatile uint32_t STATIC_TR_Z;               /* STATIC_TR_Z */
    volatile uint32_t PDMA_LCNTS;                /* Peripheral DMA Loop Counts */
    volatile uint32_t PDMA_STATE;                /* Peripheral DMA State */
    volatile uint32_t PERIPH_BCNT;               /* Peripheral Byte Count */
    volatile uint8_t  Resv_2084[16];
    volatile uint32_t FIFO_SEL;                  /* FIFO Selection register */
    volatile uint8_t  Resv_2108[20];
    volatile uint32_t PERIPH_FZCNT;              /* Peripheral Full Z Count */
    volatile uint8_t  Resv_65536[63424];
} CSL_pktdma_chrt_v2Regs64_chan;


typedef struct {
    CSL_pktdma_chrt_v2Regs64_chan CHAN[97];
} CSL_pktdma_chrt_v2Regs64;


/**************************************************************************
* 64K Register Macros
**************************************************************************/

#define CSL_PKTDMA_CHRT_V2_64_CHAN_CTL(CHAN)                                   (0x00000000U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_CFG(CHAN)                                   (0x00000004U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_STATUS0(CHAN)                               (0x00000040U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_STATUS1(CHAN)                               (0x00000044U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_PRI_CTRL(CHAN)                              (0x00000064U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_THREAD(CHAN)                                (0x00000068U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_FIFO_DEPTH(CHAN)                            (0x00000070U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_TST_SCHED(CHAN)                             (0x00000078U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_STDATA(CHAN,STDATA)                         (0x00000080U+((CHAN)*0x10000U)+((STDATA)*0x4U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_STDATAW(CHAN,STDATAW)                       (0x00000100U+((CHAN)*0x10000U)+((STDATAW)*0x4U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_PCNT(CHAN)                                  (0x00000400U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_DCNT(CHAN)                                  (0x00000404U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_BCNT(CHAN)                                  (0x00000408U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_SBCNT(CHAN)                                 (0x00000410U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_STATIC_TR_XY(CHAN)                          (0x00000800U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_STATIC_TR_Z(CHAN)                           (0x00000804U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_PDMA_LCNTS(CHAN)                            (0x00000808U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_PDMA_STATE(CHAN)                            (0x0000080CU+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_PERIPH_BCNT(CHAN)                           (0x00000810U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_FIFO_SEL(CHAN)                              (0x00000824U+((CHAN)*0x10000U))
#define CSL_PKTDMA_CHRT_V2_64_CHAN_PERIPH_FZCNT(CHAN)                          (0x0000083CU+((CHAN)*0x10000U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CTL */

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_EN_MASK                                    (0x80000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_EN_SHIFT                                   (0x0000001FU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_EN_RESETVAL                                (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_EN_MAX                                     (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_TDOWN_MASK                                 (0x40000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_TDOWN_SHIFT                                (0x0000001EU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_TDOWN_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_TDOWN_MAX                                  (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAUSE_MASK                                 (0x20000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAUSE_SHIFT                                (0x0000001DU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAUSE_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAUSE_MAX                                  (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_FTDOWN_MASK                                (0x10000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_FTDOWN_SHIFT                               (0x0000001CU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_FTDOWN_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_FTDOWN_MAX                                 (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAUSE_EOP_MASK                             (0x08000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAUSE_EOP_SHIFT                            (0x0000001BU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAUSE_EOP_RESETVAL                         (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAUSE_EOP_MAX                              (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_MASK                                  (0x00800000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_SHIFT                                 (0x00000017U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_RESETVAL                              (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_MAX                                   (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TD_FAIL_MASK                          (0x00040000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TD_FAIL_SHIFT                         (0x00000012U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TD_FAIL_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TD_FAIL_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TIMEOUT_MASK                          (0x00020000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TIMEOUT_SHIFT                         (0x00000011U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TIMEOUT_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_TIMEOUT_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_COMPLETE_MASK                         (0x00010000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_COMPLETE_SHIFT                        (0x00000010U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_COMPLETE_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_PAIR_COMPLETE_MAX                          (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_ERROR_MASK                                 (0x00000001U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_ERROR_SHIFT                                (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_ERROR_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_ERROR_MAX                                  (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CTL_RESETVAL                                   (0x00000000U)

/* CFG */

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_PAUSE_ON_ERR_MASK                          (0x80000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_PAUSE_ON_ERR_SHIFT                         (0x0000001FU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_PAUSE_ON_ERR_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_PAUSE_ON_ERR_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_EINFO_MASK                            (0x40000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_EINFO_SHIFT                           (0x0000001EU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_EINFO_RESETVAL                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_EINFO_MAX                             (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_EINFO_VAL_PASS                        (0x0U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_EINFO_VAL_FILT                        (0x1U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_PSWORDS_MASK                          (0x20000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_PSWORDS_SHIFT                         (0x0000001DU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_PSWORDS_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_PSWORDS_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_PSWORDS_VAL_PASS                      (0x0U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_FILT_PSWORDS_VAL_FILT                      (0x1U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_CHAN_TYPE_MASK                             (0x000F0000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_CHAN_TYPE_SHIFT                            (0x00000010U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_CHAN_TYPE_RESETVAL                         (0x00000002U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_CHAN_TYPE_MAX                              (0x0000000FU)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_CHAN_TYPE_VAL_UNUSED                       (0x0U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_CHAN_TYPE_VAL_PBR_PKT                      (0x2U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_CHAN_TYPE_VAL_PBR_SBP                      (0x3U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_IGNORE_LONG_MASK                           (0x00004000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_IGNORE_LONG_SHIFT                          (0x0000000EU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_IGNORE_LONG_RESETVAL                       (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_IGNORE_LONG_MAX                            (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_BURST_SIZE_MASK                            (0x00000C00U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_BURST_SIZE_SHIFT                           (0x0000000AU)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_BURST_SIZE_RESETVAL                        (0x00000001U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_BURST_SIZE_MAX                             (0x00000003U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_TDTYPE_MASK                                (0x00000200U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_TDTYPE_SHIFT                               (0x00000009U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_TDTYPE_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_TDTYPE_MAX                                 (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_NOTDPKT_MASK                               (0x00000100U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_NOTDPKT_SHIFT                              (0x00000008U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_NOTDPKT_RESETVAL                           (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_NOTDPKT_MAX                                (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_CFG_RESETVAL                                   (0x00020400U)

/* STATUS0 */

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_RING_PEND_MASK                         (0x80000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_RING_PEND_SHIFT                        (0x0000001FU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_RING_PEND_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_RING_PEND_MAX                          (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_Q_PEND_MASK                            (0x40000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_Q_PEND_SHIFT                           (0x0000001EU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_Q_PEND_RESETVAL                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_Q_PEND_MAX                             (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_PKTID_AVAIL_MASK                       (0x20000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_PKTID_AVAIL_SHIFT                      (0x0000001DU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_PKTID_AVAIL_RESETVAL                   (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_PKTID_AVAIL_MAX                        (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_PKTID_BUSY_MASK                        (0x10000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_PKTID_BUSY_SHIFT                       (0x0000001CU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_PKTID_BUSY_RESETVAL                    (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_PKTID_BUSY_MAX                         (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_BUSY_MASK                              (0x02000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_BUSY_SHIFT                             (0x00000019U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_BUSY_RESETVAL                          (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_BUSY_MAX                               (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TRANSBUSY_MASK                         (0x01000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TRANSBUSY_SHIFT                        (0x00000018U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TRANSBUSY_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TRANSBUSY_MAX                          (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_IN_PACKET_MASK                         (0x00800000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_IN_PACKET_SHIFT                        (0x00000017U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_IN_PACKET_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_IN_PACKET_MAX                          (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_OK_MASK                                (0x00400000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_OK_SHIFT                               (0x00000016U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_OK_RESETVAL                            (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_OK_MAX                                 (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_WAVAIL_MASK                            (0x00200000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_WAVAIL_SHIFT                           (0x00000015U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_WAVAIL_RESETVAL                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_WAVAIL_MAX                             (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TDOWN_MSG_PEND_MASK                    (0x00040000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TDOWN_MSG_PEND_SHIFT                   (0x00000012U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TDOWN_MSG_PEND_RESETVAL                (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TDOWN_MSG_PEND_MAX                     (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TX_REQ_MASK                            (0x00020000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TX_REQ_SHIFT                           (0x00000011U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TX_REQ_RESETVAL                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_TX_REQ_MAX                             (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_ERR_EVENT_REQS_MASK                    (0x00010000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_ERR_EVENT_REQS_SHIFT                   (0x00000010U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_ERR_EVENT_REQS_RESETVAL                (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_ERR_EVENT_REQS_MAX                     (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS0_RESETVAL                               (0x00000000U)

/* STATUS1 */

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_REQS_MASK                              (0x80000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_REQS_SHIFT                             (0x0000001FU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_REQS_RESETVAL                          (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_REQS_MAX                               (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_SOP_WAVAVIL_MASK                       (0x04000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_SOP_WAVAVIL_SHIFT                      (0x0000001AU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_SOP_WAVAVIL_RESETVAL                   (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_SOP_WAVAVIL_MAX                        (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_FIFO_PEND_MASK                         (0x02000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_FIFO_PEND_SHIFT                        (0x00000019U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_FIFO_PEND_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_FIFO_PEND_MAX                          (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_FIFO_BUSY_MASK                         (0x01000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_FIFO_BUSY_SHIFT                        (0x00000018U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_FIFO_BUSY_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_FIFO_BUSY_MAX                          (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_TDNULL_MASK                            (0x00000100U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_TDNULL_SHIFT                           (0x00000008U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_TDNULL_RESETVAL                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_TDNULL_MAX                             (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_CHANNEL_OKAY_MASK                      (0x00000080U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_CHANNEL_OKAY_SHIFT                     (0x00000007U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_CHANNEL_OKAY_RESETVAL                  (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_CHANNEL_OKAY_MAX                       (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_CHANNEL_BUSY_MASK                      (0x00000040U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_CHANNEL_BUSY_SHIFT                     (0x00000006U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_CHANNEL_BUSY_RESETVAL                  (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_CHANNEL_BUSY_MAX                       (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_IN_PACKET_ARRAY_MASK                   (0x00000008U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_IN_PACKET_ARRAY_SHIFT                  (0x00000003U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_IN_PACKET_ARRAY_RESETVAL               (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_IN_PACKET_ARRAY_MAX                    (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATUS1_RESETVAL                               (0x00000000U)

/* PRI_CTRL */

#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL_PRIORITY_MASK                         (0x70000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL_PRIORITY_SHIFT                        (0x0000001CU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL_PRIORITY_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL_PRIORITY_MAX                          (0x00000007U)

#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL_ORDERID_MASK                          (0x0000000FU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL_ORDERID_SHIFT                         (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL_ORDERID_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL_ORDERID_MAX                           (0x0000000FU)

#define CSL_PKTDMA_CHRT_V2_CHAN_PRI_CTRL_RESETVAL                              (0x00000000U)

/* THREAD */

#define CSL_PKTDMA_CHRT_V2_CHAN_THREAD_ID_MASK                                 (0x0000FFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_THREAD_ID_SHIFT                                (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_THREAD_ID_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_THREAD_ID_MAX                                  (0x0000FFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_THREAD_RESETVAL                                (0x00000000U)

/* FIFO_DEPTH */

#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_DEPTH_FDEPTH_MASK                         (0x000000FFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_DEPTH_FDEPTH_SHIFT                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_DEPTH_FDEPTH_RESETVAL                     (0x000000C0U)
#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_DEPTH_FDEPTH_MAX                          (0x000000FFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_DEPTH_RESETVAL                            (0x000000C0U)

/* TST_SCHED */

#define CSL_PKTDMA_CHRT_V2_CHAN_TST_SCHED_PRIORITY_MASK                        (0x00000003U)
#define CSL_PKTDMA_CHRT_V2_CHAN_TST_SCHED_PRIORITY_SHIFT                       (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_TST_SCHED_PRIORITY_RESETVAL                    (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_TST_SCHED_PRIORITY_MAX                         (0x00000003U)

#define CSL_PKTDMA_CHRT_V2_CHAN_TST_SCHED_RESETVAL                             (0x00000000U)

/* STDATA */

#define CSL_PKTDMA_CHRT_V2_CHAN_STDATA_STATE_INFO_MASK                         (0xFFFFFFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STDATA_STATE_INFO_SHIFT                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STDATA_STATE_INFO_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STDATA_STATE_INFO_MAX                          (0xFFFFFFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_STDATA_RESETVAL                                (0x00000000U)

/* STDATAW */

#define CSL_PKTDMA_CHRT_V2_CHAN_STDATAW_STATE_INFO_MASK                        (0xFFFFFFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STDATAW_STATE_INFO_SHIFT                       (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STDATAW_STATE_INFO_RESETVAL                    (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STDATAW_STATE_INFO_MAX                         (0xFFFFFFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_STDATAW_RESETVAL                               (0x00000000U)

/* PCNT */

#define CSL_PKTDMA_CHRT_V2_CHAN_PCNT_PCNT_MASK                                 (0xFFFFFFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PCNT_PCNT_SHIFT                                (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PCNT_PCNT_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PCNT_PCNT_MAX                                  (0xFFFFFFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_PCNT_RESETVAL                                  (0x00000000U)

/* DCNT */

#define CSL_PKTDMA_CHRT_V2_CHAN_DCNT_DCNT_MASK                                 (0xFFFFFFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_DCNT_DCNT_SHIFT                                (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_DCNT_DCNT_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_DCNT_DCNT_MAX                                  (0xFFFFFFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_DCNT_RESETVAL                                  (0x00000000U)

/* BCNT */

#define CSL_PKTDMA_CHRT_V2_CHAN_BCNT_BCNT_MASK                                 (0xFFFFFFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_BCNT_BCNT_SHIFT                                (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_BCNT_BCNT_RESETVAL                             (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_BCNT_BCNT_MAX                                  (0xFFFFFFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_BCNT_RESETVAL                                  (0x00000000U)

/* SBCNT */

#define CSL_PKTDMA_CHRT_V2_CHAN_SBCNT_SBCNT_MASK                               (0xFFFFFFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_SBCNT_SBCNT_SHIFT                              (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_SBCNT_SBCNT_RESETVAL                           (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_SBCNT_SBCNT_MAX                                (0xFFFFFFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_SBCNT_RESETVAL                                 (0x00000000U)

/* STATIC_TR_XY */

#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_BURST_MASK                        (0x80000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_BURST_SHIFT                       (0x0000001FU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_BURST_RESETVAL                    (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_BURST_MAX                         (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_ACC32_MASK                        (0x40000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_ACC32_SHIFT                       (0x0000001EU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_ACC32_RESETVAL                    (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_ACC32_MAX                         (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_X_MASK                            (0x07000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_X_SHIFT                           (0x00000018U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_X_RESETVAL                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_X_MAX                             (0x00000007U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_Y_MASK                            (0x00000FFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_Y_SHIFT                           (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_Y_RESETVAL                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_Y_MAX                             (0x00000FFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_XY_RESETVAL                          (0x00000000U)

/* STATIC_TR_Z */

#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z_EOL_MASK                           (0x80000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z_EOL_SHIFT                          (0x0000001FU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z_EOL_RESETVAL                       (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z_EOL_MAX                            (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z_Z_MASK                             (0x00FFFFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z_Z_SHIFT                            (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z_Z_RESETVAL                         (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z_Z_MAX                              (0x00FFFFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_STATIC_TR_Z_RESETVAL                           (0x00000000U)

/* PDMA_LCNTS */

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS_Z_MASK                              (0xFFFF0000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS_Z_SHIFT                             (0x00000010U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS_Z_RESETVAL                          (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS_Z_MAX                               (0x0000FFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS_Y_MASK                              (0x0000FFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS_Y_SHIFT                             (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS_Y_RESETVAL                          (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS_Y_MAX                               (0x0000FFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_LCNTS_RESETVAL                            (0x00000000U)

/* PDMA_STATE */

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_INEVT_MASK                          (0x80000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_INEVT_SHIFT                         (0x0000001FU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_INEVT_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_INEVT_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_TDOWN_MASK                          (0x40000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_TDOWN_SHIFT                         (0x0000001EU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_TDOWN_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_TDOWN_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_PAUSE_MASK                          (0x20000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_PAUSE_SHIFT                         (0x0000001DU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_PAUSE_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_PAUSE_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_SPACE_MASK                          (0x10000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_SPACE_SHIFT                         (0x0000001CU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_SPACE_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_SPACE_MAX                           (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_XPSPACE_MASK                        (0x08000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_XPSPACE_SHIFT                       (0x0000001BU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_XPSPACE_RESETVAL                    (0x00000001U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_XPSPACE_MAX                         (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_BUF_MASK                            (0x04000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_BUF_SHIFT                           (0x0000001AU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_BUF_RESETVAL                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_BUF_MAX                             (0x00000001U)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_STATE_MASK                          (0x00F00000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_STATE_SHIFT                         (0x00000014U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_STATE_RESETVAL                      (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_STATE_MAX                           (0x0000000FU)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_ECNT_MASK                           (0x000F0000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_ECNT_SHIFT                          (0x00000010U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_ECNT_RESETVAL                       (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_ECNT_MAX                            (0x0000000FU)

#define CSL_PKTDMA_CHRT_V2_CHAN_PDMA_STATE_RESETVAL                            (0x08000000U)

/* PERIPH_BCNT */

#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_BCNT_BYTES_MASK                         (0x7FFFFFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_BCNT_BYTES_SHIFT                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_BCNT_BYTES_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_BCNT_BYTES_MAX                          (0x7FFFFFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_BCNT_RESETVAL                           (0x00000000U)

/* FIFO_SEL */

#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_SEL_FIFO_MASK                             (0x0000000FU)
#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_SEL_FIFO_SHIFT                            (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_SEL_FIFO_RESETVAL                         (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_SEL_FIFO_MAX                              (0x0000000FU)

#define CSL_PKTDMA_CHRT_V2_CHAN_FIFO_SEL_RESETVAL                              (0x00000000U)

/* PERIPH_FZCNT */

#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_FZCNT_CURR_MASK                         (0xFFFFFFFFU)
#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_FZCNT_CURR_SHIFT                        (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_FZCNT_CURR_RESETVAL                     (0x00000000U)
#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_FZCNT_CURR_MAX                          (0xFFFFFFFFU)

#define CSL_PKTDMA_CHRT_V2_CHAN_PERIPH_FZCNT_RESETVAL                          (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif

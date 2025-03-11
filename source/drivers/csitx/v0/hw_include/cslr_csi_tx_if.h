/********************************************************************
 * Copyright (C) 2020-25 Texas Instruments Incorporated.
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
 *  Name        : cslr_csi_tx_if.h
*/
#ifndef CSLR_CSI_TX_IF_H_
#define CSLR_CSI_TX_IF_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t DMACNTX;                   /* DMA Channel Context */
    volatile uint32_t L2L_DELAY;                 /* delay in main clock cycles from start of one line to start of another line */
    volatile uint32_t BYTECNT;                   /* number of bytes for a line */
    volatile uint32_t L2F_DELAY;                 /* delay in main clock cycles from end of one line to end of frame */
    volatile uint8_t  Resv_32[16];
} CSL_csi_tx_ifRegs_cntl;


typedef struct {
    volatile uint32_t CSITX_ID;                  /* PID */
    volatile uint32_t COLOR_CNTL;                /* color bar control register */
    volatile uint32_t COLOR_PARAM;               /* color bar frame parameters */
    volatile uint32_t COLOR_START_DELAY;         /* delay from starting first line after enabling */
    volatile uint8_t  Resv_32[16];
    volatile uint32_t COLOR_LINE_DELAY;          /* last line start to next line start delay */
    volatile uint32_t COLOR_FRAME_DELAY;         /* line start to next frame start delay */
    volatile uint8_t  Resv_44[4];
    volatile uint32_t CONTROL1;                  /* control register for csi tx wrapper */
    volatile uint8_t  Resv_64[16];
    volatile uint32_t F2F_DELAY[16];             /* delay in number of main clock cyles from start of last frame line to start of next frame first line */
    volatile uint8_t  Resv_256[128];
    CSL_csi_tx_ifRegs_cntl CNTL[32];
} CSL_csi_tx_ifRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CSI_TX_IF_CSITX_ID                                              (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_CNTL                                            (0x00000004U)
#define CSL_CSI_TX_IF_COLOR_PARAM                                           (0x00000008U)
#define CSL_CSI_TX_IF_COLOR_START_DELAY                                     (0x0000000CU)
#define CSL_CSI_TX_IF_COLOR_LINE_DELAY                                      (0x00000020U)
#define CSL_CSI_TX_IF_COLOR_FRAME_DELAY                                     (0x00000024U)
#define CSL_CSI_TX_IF_CONTROL1                                              (0x0000002CU)
#define CSL_CSI_TX_IF_F2F_DELAY(F2F_DELAY)                                  (0x00000040U+((F2F_DELAY)*0x4U))
#define CSL_CSI_TX_IF_CNTL_DMACNTX(CNTL)                                    (0x00000100U+((CNTL)*0x20U))
#define CSL_CSI_TX_IF_CNTL_L2L_DELAY(CNTL)                                  (0x00000104U+((CNTL)*0x20U))
#define CSL_CSI_TX_IF_CNTL_BYTECNT(CNTL)                                    (0x00000108U+((CNTL)*0x20U))
#define CSL_CSI_TX_IF_CNTL_L2F_DELAY(CNTL)                                  (0x0000010CU+((CNTL)*0x20U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* DMACNTX */

#define CSL_CSI_TX_IF_CNTL_DMACNTX_YUV422_MODE_CFG_MASK                     (0x0C000000U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_YUV422_MODE_CFG_SHIFT                    (0x0000001AU)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_YUV422_MODE_CFG_RESETVAL                 (0x00000003U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_YUV422_MODE_CFG_MAX                      (0x00000003U)

#define CSL_CSI_TX_IF_CNTL_DMACNTX_PACK12_CFG_MASK                          (0x00800000U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_PACK12_CFG_SHIFT                         (0x00000017U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_PACK12_CFG_RESETVAL                      (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_PACK12_CFG_MAX                           (0x00000001U)

#define CSL_CSI_TX_IF_CNTL_DMACNTX_SIZE_CFG_MASK                            (0x00300000U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_SIZE_CFG_SHIFT                           (0x00000014U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_SIZE_CFG_RESETVAL                        (0x00000002U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_SIZE_CFG_MAX                             (0x00000003U)

#define CSL_CSI_TX_IF_CNTL_DMACNTX_VIRTCH_CFG_MASK                          (0x000003C0U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_VIRTCH_CFG_SHIFT                         (0x00000006U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_VIRTCH_CFG_RESETVAL                      (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_VIRTCH_CFG_MAX                           (0x0000000FU)

#define CSL_CSI_TX_IF_CNTL_DMACNTX_DATATYPE_CFG_MASK                        (0x0000003FU)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_DATATYPE_CFG_SHIFT                       (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_DATATYPE_CFG_RESETVAL                    (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_DMACNTX_DATATYPE_CFG_MAX                         (0x0000003FU)

#define CSL_CSI_TX_IF_CNTL_DMACNTX_RESETVAL                                 (0x0C200000U)

/* L2L_DELAY */

#define CSL_CSI_TX_IF_CNTL_L2L_DELAY_DELAY_MASK                             (0xFFFFFFFFU)
#define CSL_CSI_TX_IF_CNTL_L2L_DELAY_DELAY_SHIFT                            (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_L2L_DELAY_DELAY_RESETVAL                         (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_L2L_DELAY_DELAY_MAX                              (0xFFFFFFFFU)

#define CSL_CSI_TX_IF_CNTL_L2L_DELAY_RESETVAL                               (0x00000000U)

/* BYTECNT */

#define CSL_CSI_TX_IF_CNTL_BYTECNT_BYTECNT_MASK                             (0x0000FFFFU)
#define CSL_CSI_TX_IF_CNTL_BYTECNT_BYTECNT_SHIFT                            (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_BYTECNT_BYTECNT_RESETVAL                         (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_BYTECNT_BYTECNT_MAX                              (0x0000FFFFU)

#define CSL_CSI_TX_IF_CNTL_BYTECNT_RESETVAL                                 (0x00000000U)

/* L2F_DELAY */

#define CSL_CSI_TX_IF_CNTL_L2F_DELAY_DELAY_MASK                             (0xFFFFFFFFU)
#define CSL_CSI_TX_IF_CNTL_L2F_DELAY_DELAY_SHIFT                            (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_L2F_DELAY_DELAY_RESETVAL                         (0x00000000U)
#define CSL_CSI_TX_IF_CNTL_L2F_DELAY_DELAY_MAX                              (0xFFFFFFFFU)

#define CSL_CSI_TX_IF_CNTL_L2F_DELAY_RESETVAL                               (0x00000000U)

/* CSITX_ID */

#define CSL_CSI_TX_IF_CSITX_ID_SCHEME_MASK                                  (0xC0000000U)
#define CSL_CSI_TX_IF_CSITX_ID_SCHEME_SHIFT                                 (0x0000001EU)
#define CSL_CSI_TX_IF_CSITX_ID_SCHEME_RESETVAL                              (0x00000001U)
#define CSL_CSI_TX_IF_CSITX_ID_SCHEME_MAX                                   (0x00000003U)

#define CSL_CSI_TX_IF_CSITX_ID_BU_MASK                                      (0x30000000U)
#define CSL_CSI_TX_IF_CSITX_ID_BU_SHIFT                                     (0x0000001CU)
#define CSL_CSI_TX_IF_CSITX_ID_BU_RESETVAL                                  (0x00000002U)
#define CSL_CSI_TX_IF_CSITX_ID_BU_MAX                                       (0x00000003U)

#define CSL_CSI_TX_IF_CSITX_ID_FUNC_MASK                                    (0x0FFF0000U)
#define CSL_CSI_TX_IF_CSITX_ID_FUNC_SHIFT                                   (0x00000010U)
#define CSL_CSI_TX_IF_CSITX_ID_FUNC_RESETVAL                                (0x00000478U)
#define CSL_CSI_TX_IF_CSITX_ID_FUNC_MAX                                     (0x00000FFFU)

#define CSL_CSI_TX_IF_CSITX_ID_RTLVER_MASK                                  (0x0000F800U)
#define CSL_CSI_TX_IF_CSITX_ID_RTLVER_SHIFT                                 (0x0000000BU)
#define CSL_CSI_TX_IF_CSITX_ID_RTLVER_RESETVAL                              (0x00000003U)
#define CSL_CSI_TX_IF_CSITX_ID_RTLVER_MAX                                   (0x0000001FU)

#define CSL_CSI_TX_IF_CSITX_ID_MAJREV_MASK                                  (0x00000700U)
#define CSL_CSI_TX_IF_CSITX_ID_MAJREV_SHIFT                                 (0x00000008U)
#define CSL_CSI_TX_IF_CSITX_ID_MAJREV_RESETVAL                              (0x00000002U)
#define CSL_CSI_TX_IF_CSITX_ID_MAJREV_MAX                                   (0x00000007U)

#define CSL_CSI_TX_IF_CSITX_ID_CUSTOM_MASK                                  (0x000000C0U)
#define CSL_CSI_TX_IF_CSITX_ID_CUSTOM_SHIFT                                 (0x00000006U)
#define CSL_CSI_TX_IF_CSITX_ID_CUSTOM_RESETVAL                              (0x00000000U)
#define CSL_CSI_TX_IF_CSITX_ID_CUSTOM_MAX                                   (0x00000003U)

#define CSL_CSI_TX_IF_CSITX_ID_MINREV_MASK                                  (0x0000003FU)
#define CSL_CSI_TX_IF_CSITX_ID_MINREV_SHIFT                                 (0x00000000U)
#define CSL_CSI_TX_IF_CSITX_ID_MINREV_RESETVAL                              (0x00000000U)
#define CSL_CSI_TX_IF_CSITX_ID_MINREV_MAX                                   (0x0000003FU)

#define CSL_CSI_TX_IF_CSITX_ID_RESETVAL                                     (0x64781A00U)

/* COLOR_CNTL */

#define CSL_CSI_TX_IF_COLOR_CNTL_EN_MASK                                    (0x00000001U)
#define CSL_CSI_TX_IF_COLOR_CNTL_EN_SHIFT                                   (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_CNTL_EN_RESETVAL                                (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_CNTL_EN_MAX                                     (0x00000001U)

#define CSL_CSI_TX_IF_COLOR_CNTL_DTYPE_MASK                                 (0x00000700U)
#define CSL_CSI_TX_IF_COLOR_CNTL_DTYPE_SHIFT                                (0x00000008U)
#define CSL_CSI_TX_IF_COLOR_CNTL_DTYPE_RESETVAL                             (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_CNTL_DTYPE_MAX                                  (0x00000007U)

#define CSL_CSI_TX_IF_COLOR_CNTL_VCHNL_MASK                                 (0x000F0000U)
#define CSL_CSI_TX_IF_COLOR_CNTL_VCHNL_SHIFT                                (0x00000010U)
#define CSL_CSI_TX_IF_COLOR_CNTL_VCHNL_RESETVAL                             (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_CNTL_VCHNL_MAX                                  (0x0000000FU)

#define CSL_CSI_TX_IF_COLOR_CNTL_RESETVAL                                   (0x00000000U)

/* COLOR_PARAM */

#define CSL_CSI_TX_IF_COLOR_PARAM_IH_CFG_MASK                               (0x1FFF0000U)
#define CSL_CSI_TX_IF_COLOR_PARAM_IH_CFG_SHIFT                              (0x00000010U)
#define CSL_CSI_TX_IF_COLOR_PARAM_IH_CFG_RESETVAL                           (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_PARAM_IH_CFG_MAX                                (0x00001FFFU)

#define CSL_CSI_TX_IF_COLOR_PARAM_IW_CFG_MASK                               (0x00001FFFU)
#define CSL_CSI_TX_IF_COLOR_PARAM_IW_CFG_SHIFT                              (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_PARAM_IW_CFG_RESETVAL                           (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_PARAM_IW_CFG_MAX                                (0x00001FFFU)

#define CSL_CSI_TX_IF_COLOR_PARAM_RESETVAL                                  (0x00000000U)

/* COLOR_START_DELAY */

#define CSL_CSI_TX_IF_COLOR_START_DELAY_LINE_DELAY_MASK                     (0xFFFFFFFFU)
#define CSL_CSI_TX_IF_COLOR_START_DELAY_LINE_DELAY_SHIFT                    (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_START_DELAY_LINE_DELAY_RESETVAL                 (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_START_DELAY_LINE_DELAY_MAX                      (0xFFFFFFFFU)

#define CSL_CSI_TX_IF_COLOR_START_DELAY_RESETVAL                            (0x00000000U)

/* COLOR_LINE_DELAY */

#define CSL_CSI_TX_IF_COLOR_LINE_DELAY_LINE_DELAY_MASK                      (0xFFFFFFFFU)
#define CSL_CSI_TX_IF_COLOR_LINE_DELAY_LINE_DELAY_SHIFT                     (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_LINE_DELAY_LINE_DELAY_RESETVAL                  (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_LINE_DELAY_LINE_DELAY_MAX                       (0xFFFFFFFFU)

#define CSL_CSI_TX_IF_COLOR_LINE_DELAY_RESETVAL                             (0x00000000U)

/* COLOR_FRAME_DELAY */

#define CSL_CSI_TX_IF_COLOR_FRAME_DELAY_FRAME_DELAY_MASK                    (0xFFFFFFFFU)
#define CSL_CSI_TX_IF_COLOR_FRAME_DELAY_FRAME_DELAY_SHIFT                   (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_FRAME_DELAY_FRAME_DELAY_RESETVAL                (0x00000000U)
#define CSL_CSI_TX_IF_COLOR_FRAME_DELAY_FRAME_DELAY_MAX                     (0xFFFFFFFFU)

#define CSL_CSI_TX_IF_COLOR_FRAME_DELAY_RESETVAL                            (0x00000000U)

/* CONTROL1 */

#define CSL_CSI_TX_IF_CONTROL1_PIXEL_RESET_MASK                             (0x00000001U)
#define CSL_CSI_TX_IF_CONTROL1_PIXEL_RESET_SHIFT                            (0x00000000U)
#define CSL_CSI_TX_IF_CONTROL1_PIXEL_RESET_RESETVAL                         (0x00000000U)
#define CSL_CSI_TX_IF_CONTROL1_PIXEL_RESET_MAX                              (0x00000001U)

#define CSL_CSI_TX_IF_CONTROL1_STREAM0_IDLE_MASK                            (0x00000100U)
#define CSL_CSI_TX_IF_CONTROL1_STREAM0_IDLE_SHIFT                           (0x00000008U)
#define CSL_CSI_TX_IF_CONTROL1_STREAM0_IDLE_RESETVAL                        (0x00000001U)
#define CSL_CSI_TX_IF_CONTROL1_STREAM0_IDLE_MAX                             (0x00000001U)

#define CSL_CSI_TX_IF_CONTROL1_STREAM1_IDLE_MASK                            (0x00000200U)
#define CSL_CSI_TX_IF_CONTROL1_STREAM1_IDLE_SHIFT                           (0x00000009U)
#define CSL_CSI_TX_IF_CONTROL1_STREAM1_IDLE_RESETVAL                        (0x00000001U)
#define CSL_CSI_TX_IF_CONTROL1_STREAM1_IDLE_MAX                             (0x00000001U)

#define CSL_CSI_TX_IF_CONTROL1_STRM_SEL_MASK                                (0x00010000U)
#define CSL_CSI_TX_IF_CONTROL1_STRM_SEL_SHIFT                               (0x00000010U)
#define CSL_CSI_TX_IF_CONTROL1_STRM_SEL_RESETVAL                            (0x00000000U)
#define CSL_CSI_TX_IF_CONTROL1_STRM_SEL_MAX                                 (0x00000001U)

#define CSL_CSI_TX_IF_CONTROL1_RESETVAL                                     (0x00000300U)

/* F2F_DELAY */

#define CSL_CSI_TX_IF_F2F_DELAY_DELAY_MASK                                  (0xFFFFFFFFU)
#define CSL_CSI_TX_IF_F2F_DELAY_DELAY_SHIFT                                 (0x00000000U)
#define CSL_CSI_TX_IF_F2F_DELAY_DELAY_RESETVAL                              (0x00000000U)
#define CSL_CSI_TX_IF_F2F_DELAY_DELAY_MAX                                   (0xFFFFFFFFU)

#define CSL_CSI_TX_IF_F2F_DELAY_RESETVAL                                    (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif

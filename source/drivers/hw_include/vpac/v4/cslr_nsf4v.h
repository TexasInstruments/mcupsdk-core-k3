/********************************************************************
 * Copyright (C) 2023 Texas Instruments Incorporated.
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
 *  Name        : cslr_nsf4v.h
*/
#ifndef CSLR_NSF4V_H_
#define CSLR_NSF4V_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : VPAC VISS Noise Supression Filter for Human Vision 4 Memory Mapped Register
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t TN0;                       /* T_n Part0  */
    volatile uint32_t TN1;                       /* T_n Part1  */
} CSL_nsf4vRegs_color_TnSeg;


typedef struct {
    CSL_nsf4vRegs_color_TnSeg TNSEG[12];
} CSL_nsf4vRegs_color;


typedef struct {
    volatile uint32_t LSCCCURVE0;                /* LSCC Curve Part0  */
    volatile uint32_t LSCCCURVE1;                /* LSCC Curve Part1  */
} CSL_nsf4vRegs_set_LSCCseg;


typedef struct {
    CSL_nsf4vRegs_set_LSCCseg LSCCSEG[16];
} CSL_nsf4vRegs_set;


typedef struct {
    volatile uint32_t DWBCURVE0;                 /* DWB Curve Part0  */
    volatile uint32_t DWBCURVE1;                 /* DWB Curve Part1  */
} CSL_nsf4vRegs_color_WB_DWBSeg;


typedef struct {
    CSL_nsf4vRegs_color_WB_DWBSeg DWBSEG[8];
} CSL_nsf4vRegs_color_WB;


typedef struct {
    volatile uint32_t DWB_WGHT01;                /* DWB weight 0 & 1 */
    volatile uint32_t DWB_WGHT23;                /* DWB weight 2 & 3 */
    volatile uint32_t DWB_WGHT45;                /* DWB weight 4 & 5 */
} CSL_nsf4vRegs_line;


typedef struct {
    volatile uint32_t START;                     /* ROI_x Start Pixel */
    volatile uint32_t END;                       /* ROI_x End Pixel */
} CSL_nsf4vRegs_Hist_Roi;


typedef struct {
    volatile uint8_t  Resv_4[4];
    volatile uint32_t DBG;                       /* Diagnostic Register */
    volatile uint32_t CTRL;                      /* control register */
    volatile uint32_t DIM;                       /* Input Output Frame dimension */
    volatile uint32_t LSCC;                      /* Lens Shading Correction Compensation */
    volatile uint32_t LSCC_CENT;                 /* Lens Shading Correction Compensation Center */
    volatile uint8_t  Resv_28[4];
    volatile uint32_t TN_SCALE;                  /* Tn Scaling Factor  */
    volatile uint32_t U_KNEE;                    /* U suppression curve knee  */
    volatile uint32_t WHITEBAL0;                 /* White Balance Gain (Part0)  */
    volatile uint32_t WHITEBAL1;                 /* White Balance Gain (Part0)  */
    volatile uint8_t  Resv_96[52];
    CSL_nsf4vRegs_color COLOR[4];
    volatile uint8_t  Resv_512[32];
    CSL_nsf4vRegs_set SET[2];
    volatile uint8_t  Resv_1008[240];
    volatile uint32_t DWB_CNTL;                  /* Dynamic White Balance Control Register */
    volatile uint8_t  Resv_1024[12];
    CSL_nsf4vRegs_color_WB COLOR_WB[4];
    CSL_nsf4vRegs_line LINE[2];
    volatile uint8_t  Resv_1520[216];
    volatile uint32_t HIST_CTRL;                 /* Histogram Control Register */
    volatile uint8_t  Resv_1536[12];
    CSL_nsf4vRegs_Hist_Roi HIST_ROI[8];
} CSL_nsf4vRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_NSF4V_DBG                                                          (0x00000004U)
#define CSL_NSF4V_CTRL                                                         (0x00000008U)
#define CSL_NSF4V_DIM                                                          (0x0000000CU)
#define CSL_NSF4V_LSCC                                                         (0x00000010U)
#define CSL_NSF4V_LSCC_CENT                                                    (0x00000014U)
#define CSL_NSF4V_TN_SCALE                                                     (0x0000001CU)
#define CSL_NSF4V_U_KNEE                                                       (0x00000020U)
#define CSL_NSF4V_WHITEBAL0                                                    (0x00000024U)
#define CSL_NSF4V_WHITEBAL1                                                    (0x00000028U)
#define CSL_NSF4V_COLOR_TNSEG_TN0(COLOR, TNSEG)                                (0x00000060U+((COLOR)*0x60U)+((TNSEG)*0x8U))
#define CSL_NSF4V_COLOR_TNSEG_TN1(COLOR, TNSEG)                                (0x00000064U+((COLOR)*0x60U)+((TNSEG)*0x8U))
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE0(SET, LSCCSEG)                         (0x00000200U+((SET)*0x80U)+((LSCCSEG)*0x8U))
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE1(SET, LSCCSEG)                         (0x00000204U+((SET)*0x80U)+((LSCCSEG)*0x8U))
#define CSL_NSF4V_DWB_CNTL                                                     (0x000003F0U)
#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE0(COLOR_WB, DWBSEG)                  (0x00000400U+((COLOR_WB)*0x40U)+((DWBSEG)*0x8U))
#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE1(COLOR_WB, DWBSEG)                  (0x00000404U+((COLOR_WB)*0x40U)+((DWBSEG)*0x8U))
#define CSL_NSF4V_LINE_DWB_WGHT01(LINE)                                        (0x00000500U+((LINE)*0xCU))
#define CSL_NSF4V_LINE_DWB_WGHT23(LINE)                                        (0x00000504U+((LINE)*0xCU))
#define CSL_NSF4V_LINE_DWB_WGHT45(LINE)                                        (0x00000508U+((LINE)*0xCU))
#define CSL_NSF4V_HIST_CTRL                                                    (0x000005F0U)
#define CSL_NSF4V_HIST_ROI_START(HIST_ROI)                                     (0x00000600U+((HIST_ROI)*0x8U))
#define CSL_NSF4V_HIST_ROI_END(HIST_ROI)                                       (0x00000604U+((HIST_ROI)*0x8U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* TN0 */

#define CSL_NSF4V_COLOR_TNSEG_TN0_Y_CFG_MASK                                   (0x7FFF0000U)
#define CSL_NSF4V_COLOR_TNSEG_TN0_Y_CFG_SHIFT                                  (0x00000010U)
#define CSL_NSF4V_COLOR_TNSEG_TN0_Y_CFG_MAX                                    (0x00007FFFU)

#define CSL_NSF4V_COLOR_TNSEG_TN0_X_CFG_MASK                                   (0x0000FFFFU)
#define CSL_NSF4V_COLOR_TNSEG_TN0_X_CFG_SHIFT                                  (0x00000000U)
#define CSL_NSF4V_COLOR_TNSEG_TN0_X_CFG_MAX                                    (0x0000FFFFU)

/* TN1 */

#define CSL_NSF4V_COLOR_TNSEG_TN1_S_CFG_MASK                                   (0x0000FFFFU)
#define CSL_NSF4V_COLOR_TNSEG_TN1_S_CFG_SHIFT                                  (0x00000000U)
#define CSL_NSF4V_COLOR_TNSEG_TN1_S_CFG_MAX                                    (0x0000FFFFU)

/* LSCCCURVE0 */

#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE0_Y_CFG_MASK                            (0x01FF0000U)
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE0_Y_CFG_SHIFT                           (0x00000010U)
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE0_Y_CFG_MAX                             (0x000001FFU)

#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE0_X_CFG_MASK                            (0x0000FFFFU)
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE0_X_CFG_SHIFT                           (0x00000000U)
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE0_X_CFG_MAX                             (0x0000FFFFU)

/* LSCCCURVE1 */

#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE1_RSVD_MASK                             (0xFFFF0000U)
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE1_RSVD_SHIFT                            (0x00000010U)
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE1_RSVD_MAX                              (0x0000FFFFU)

#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE1_S_CFG_MASK                            (0x0000FFFFU)
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE1_S_CFG_SHIFT                           (0x00000000U)
#define CSL_NSF4V_SET_LSCCSEG_LSCCCURVE1_S_CFG_MAX                             (0x0000FFFFU)

/* DWBCURVE0 */

#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE0_Y_CFG_MASK                         (0x0FFF0000U)
#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE0_Y_CFG_SHIFT                        (0x00000010U)
#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE0_Y_CFG_MAX                          (0x00000FFFU)

#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE0_X_CFG_MASK                         (0x0000FFFFU)
#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE0_X_CFG_SHIFT                        (0x00000000U)
#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE0_X_CFG_MAX                          (0x0000FFFFU)

/* DWBCURVE1 */

#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE1_S_CFG_MASK                         (0x0000FFFFU)
#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE1_S_CFG_SHIFT                        (0x00000000U)
#define CSL_NSF4V_COLOR_WB_DWBSEG_DWBCURVE1_S_CFG_MAX                          (0x0000FFFFU)

/* DWB_WGHT01 */

#define CSL_NSF4V_LINE_DWB_WGHT01_W1_MASK                                      (0x01FF0000U)
#define CSL_NSF4V_LINE_DWB_WGHT01_W1_SHIFT                                     (0x00000010U)
#define CSL_NSF4V_LINE_DWB_WGHT01_W1_MAX                                       (0x000001FFU)

#define CSL_NSF4V_LINE_DWB_WGHT01_W0_MASK                                      (0x000001FFU)
#define CSL_NSF4V_LINE_DWB_WGHT01_W0_SHIFT                                     (0x00000000U)
#define CSL_NSF4V_LINE_DWB_WGHT01_W0_MAX                                       (0x000001FFU)

/* DWB_WGHT23 */

#define CSL_NSF4V_LINE_DWB_WGHT23_W3_MASK                                      (0x01FF0000U)
#define CSL_NSF4V_LINE_DWB_WGHT23_W3_SHIFT                                     (0x00000010U)
#define CSL_NSF4V_LINE_DWB_WGHT23_W3_MAX                                       (0x000001FFU)

#define CSL_NSF4V_LINE_DWB_WGHT23_W2_MASK                                      (0x000001FFU)
#define CSL_NSF4V_LINE_DWB_WGHT23_W2_SHIFT                                     (0x00000000U)
#define CSL_NSF4V_LINE_DWB_WGHT23_W2_MAX                                       (0x000001FFU)

/* DWB_WGHT45 */

#define CSL_NSF4V_LINE_DWB_WGHT45_W5_MASK                                      (0x01FF0000U)
#define CSL_NSF4V_LINE_DWB_WGHT45_W5_SHIFT                                     (0x00000010U)
#define CSL_NSF4V_LINE_DWB_WGHT45_W5_MAX                                       (0x000001FFU)

#define CSL_NSF4V_LINE_DWB_WGHT45_W4_MASK                                      (0x000001FFU)
#define CSL_NSF4V_LINE_DWB_WGHT45_W4_SHIFT                                     (0x00000000U)
#define CSL_NSF4V_LINE_DWB_WGHT45_W4_MAX                                       (0x000001FFU)

/* START */

#define CSL_NSF4V_HIST_ROI_START_STARTY_MASK                                   (0x1FFF0000U)
#define CSL_NSF4V_HIST_ROI_START_STARTY_SHIFT                                  (0x00000010U)
#define CSL_NSF4V_HIST_ROI_START_STARTY_MAX                                    (0x00001FFFU)

#define CSL_NSF4V_HIST_ROI_START_STARTX_MASK                                   (0x00001FFFU)
#define CSL_NSF4V_HIST_ROI_START_STARTX_SHIFT                                  (0x00000000U)
#define CSL_NSF4V_HIST_ROI_START_STARTX_MAX                                    (0x00001FFFU)

/* END */

#define CSL_NSF4V_HIST_ROI_END_ENDY_MASK                                       (0x1FFF0000U)
#define CSL_NSF4V_HIST_ROI_END_ENDY_SHIFT                                      (0x00000010U)
#define CSL_NSF4V_HIST_ROI_END_ENDY_MAX                                        (0x00001FFFU)

#define CSL_NSF4V_HIST_ROI_END_ENDX_MASK                                       (0x00001FFFU)
#define CSL_NSF4V_HIST_ROI_END_ENDX_SHIFT                                      (0x00000000U)
#define CSL_NSF4V_HIST_ROI_END_ENDX_MAX                                        (0x00001FFFU)

/* DBG */

#define CSL_NSF4V_DBG_RAM_MUX_CFG_MASK                                         (0x0000003FU)
#define CSL_NSF4V_DBG_RAM_MUX_CFG_SHIFT                                        (0x00000000U)
#define CSL_NSF4V_DBG_RAM_MUX_CFG_MAX                                          (0x0000003FU)

/* CTRL */

#define CSL_NSF4V_CTRL_LSCC_EN_CFG_MASK                                        (0x00001000U)
#define CSL_NSF4V_CTRL_LSCC_EN_CFG_SHIFT                                       (0x0000000CU)
#define CSL_NSF4V_CTRL_LSCC_EN_CFG_MAX                                         (0x00000001U)

#define CSL_NSF4V_CTRL_LSCC_SETSEL_CFG_MASK                                    (0x00000F00U)
#define CSL_NSF4V_CTRL_LSCC_SETSEL_CFG_SHIFT                                   (0x00000008U)
#define CSL_NSF4V_CTRL_LSCC_SETSEL_CFG_MAX                                     (0x0000000FU)

#define CSL_NSF4V_CTRL_TN_MODE_CFG_MASK                                        (0x00000010U)
#define CSL_NSF4V_CTRL_TN_MODE_CFG_SHIFT                                       (0x00000004U)
#define CSL_NSF4V_CTRL_TN_MODE_CFG_MAX                                         (0x00000001U)

#define CSL_NSF4V_CTRL_U_MODE_CFG_MASK                                         (0x0000000FU)
#define CSL_NSF4V_CTRL_U_MODE_CFG_SHIFT                                        (0x00000000U)
#define CSL_NSF4V_CTRL_U_MODE_CFG_MAX                                          (0x0000000FU)

/* DIM */

#define CSL_NSF4V_DIM_IH_CFG_MASK                                              (0x1FFF0000U)
#define CSL_NSF4V_DIM_IH_CFG_SHIFT                                             (0x00000010U)
#define CSL_NSF4V_DIM_IH_CFG_MAX                                               (0x00001FFFU)

#define CSL_NSF4V_DIM_IW_CFG_MASK                                              (0x00001FFFU)
#define CSL_NSF4V_DIM_IW_CFG_SHIFT                                             (0x00000000U)
#define CSL_NSF4V_DIM_IW_CFG_MAX                                               (0x00001FFFU)

/* LSCC */

#define CSL_NSF4V_LSCC_GMAX_CFG_MASK                                           (0x1FF00000U)
#define CSL_NSF4V_LSCC_GMAX_CFG_SHIFT                                          (0x00000014U)
#define CSL_NSF4V_LSCC_GMAX_CFG_MAX                                            (0x000001FFU)

#define CSL_NSF4V_LSCC_T_CFG_MASK                                              (0x000F0000U)
#define CSL_NSF4V_LSCC_T_CFG_SHIFT                                             (0x00000010U)
#define CSL_NSF4V_LSCC_T_CFG_MAX                                               (0x0000000FU)

#define CSL_NSF4V_LSCC_KV_CFG_MASK                                             (0x0000FF00U)
#define CSL_NSF4V_LSCC_KV_CFG_SHIFT                                            (0x00000008U)
#define CSL_NSF4V_LSCC_KV_CFG_MAX                                              (0x000000FFU)

#define CSL_NSF4V_LSCC_KH_CFG_MASK                                             (0x000000FFU)
#define CSL_NSF4V_LSCC_KH_CFG_SHIFT                                            (0x00000000U)
#define CSL_NSF4V_LSCC_KH_CFG_MAX                                              (0x000000FFU)

/* LSCC_CENT */

#define CSL_NSF4V_LSCC_CENT_Y_CFG_MASK                                         (0x3FFF0000U)
#define CSL_NSF4V_LSCC_CENT_Y_CFG_SHIFT                                        (0x00000010U)
#define CSL_NSF4V_LSCC_CENT_Y_CFG_MAX                                          (0x00003FFFU)

#define CSL_NSF4V_LSCC_CENT_X_CFG_MASK                                         (0x00003FFFU)
#define CSL_NSF4V_LSCC_CENT_X_CFG_SHIFT                                        (0x00000000U)
#define CSL_NSF4V_LSCC_CENT_X_CFG_MAX                                          (0x00003FFFU)

/* TN_SCALE */

#define CSL_NSF4V_TN_SCALE_TN3_CFG_MASK                                        (0x00FF0000U)
#define CSL_NSF4V_TN_SCALE_TN3_CFG_SHIFT                                       (0x00000010U)
#define CSL_NSF4V_TN_SCALE_TN3_CFG_MAX                                         (0x000000FFU)

#define CSL_NSF4V_TN_SCALE_TN2_CFG_MASK                                        (0x0000FF00U)
#define CSL_NSF4V_TN_SCALE_TN2_CFG_SHIFT                                       (0x00000008U)
#define CSL_NSF4V_TN_SCALE_TN2_CFG_MAX                                         (0x000000FFU)

#define CSL_NSF4V_TN_SCALE_TN1_CFG_MASK                                        (0x000000FFU)
#define CSL_NSF4V_TN_SCALE_TN1_CFG_SHIFT                                       (0x00000000U)
#define CSL_NSF4V_TN_SCALE_TN1_CFG_MAX                                         (0x000000FFU)

/* U_KNEE */

#define CSL_NSF4V_U_KNEE_U_KNEE_CFG_MASK                                       (0x0000003FU)
#define CSL_NSF4V_U_KNEE_U_KNEE_CFG_SHIFT                                      (0x00000000U)
#define CSL_NSF4V_U_KNEE_U_KNEE_CFG_MAX                                        (0x0000003FU)

/* WHITEBAL0 */

#define CSL_NSF4V_WHITEBAL0_GAIN1_CFG_MASK                                     (0x1FFF0000U)
#define CSL_NSF4V_WHITEBAL0_GAIN1_CFG_SHIFT                                    (0x00000010U)
#define CSL_NSF4V_WHITEBAL0_GAIN1_CFG_MAX                                      (0x00001FFFU)

#define CSL_NSF4V_WHITEBAL0_GAIN0_CFG_MASK                                     (0x00001FFFU)
#define CSL_NSF4V_WHITEBAL0_GAIN0_CFG_SHIFT                                    (0x00000000U)
#define CSL_NSF4V_WHITEBAL0_GAIN0_CFG_MAX                                      (0x00001FFFU)

/* WHITEBAL1 */

#define CSL_NSF4V_WHITEBAL1_GAIN3_CFG_MASK                                     (0x1FFF0000U)
#define CSL_NSF4V_WHITEBAL1_GAIN3_CFG_SHIFT                                    (0x00000010U)
#define CSL_NSF4V_WHITEBAL1_GAIN3_CFG_MAX                                      (0x00001FFFU)

#define CSL_NSF4V_WHITEBAL1_GAIN2_CFG_MASK                                     (0x00001FFFU)
#define CSL_NSF4V_WHITEBAL1_GAIN2_CFG_SHIFT                                    (0x00000000U)
#define CSL_NSF4V_WHITEBAL1_GAIN2_CFG_MAX                                      (0x00001FFFU)

/* DWB_CNTL */

#define CSL_NSF4V_DWB_CNTL_DWB_EN_MASK                                         (0x00000001U)
#define CSL_NSF4V_DWB_CNTL_DWB_EN_SHIFT                                        (0x00000000U)
#define CSL_NSF4V_DWB_CNTL_DWB_EN_MAX                                          (0x00000001U)

/* HIST_CTRL */

#define CSL_NSF4V_HIST_CTRL_HIST_EN_MASK                                       (0x00000001U)
#define CSL_NSF4V_HIST_CTRL_HIST_EN_SHIFT                                      (0x00000000U)
#define CSL_NSF4V_HIST_CTRL_HIST_EN_MAX                                        (0x00000001U)

#define CSL_NSF4V_HIST_CTRL_PHASESEL_MASK                                      (0x0000001EU)
#define CSL_NSF4V_HIST_CTRL_PHASESEL_SHIFT                                     (0x00000001U)
#define CSL_NSF4V_HIST_CTRL_PHASESEL_MAX                                       (0x0000000FU)

#define CSL_NSF4V_HIST_CTRL_BANK_MASK                                          (0x00000020U)
#define CSL_NSF4V_HIST_CTRL_BANK_SHIFT                                         (0x00000005U)
#define CSL_NSF4V_HIST_CTRL_BANK_MAX                                           (0x00000001U)

#define CSL_NSF4V_HIST_CTRL_LUT_EN_MASK                                        (0x00000100U)
#define CSL_NSF4V_HIST_CTRL_LUT_EN_SHIFT                                       (0x00000008U)
#define CSL_NSF4V_HIST_CTRL_LUT_EN_MAX                                         (0x00000001U)

#define CSL_NSF4V_HIST_CTRL_INBITWDTH_MASK                                     (0x00003E00U)
#define CSL_NSF4V_HIST_CTRL_INBITWDTH_SHIFT                                    (0x00000009U)
#define CSL_NSF4V_HIST_CTRL_INBITWDTH_MAX                                      (0x0000001FU)

#define CSL_NSF4V_HIST_CTRL_ROI_EN_MASK                                        (0x00FF0000U)
#define CSL_NSF4V_HIST_CTRL_ROI_EN_SHIFT                                       (0x00000010U)
#define CSL_NSF4V_HIST_CTRL_ROI_EN_MAX                                         (0x000000FFU)

/**************************************************************************
* Hardware Region  : MMR MEM Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t DBG_MEM[2048];             /* diag_mem_ram */
} CSL_nsf4v_memRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_NSF4V_MEM_DBG_MEM(DBG_MEM)                                         (0x00000000U+((DBG_MEM)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* DBG_MEM */

#define CSL_NSF4V_MEM_DBG_MEM_DATA_MASK                                        (0xFFFFFFFFU)
#define CSL_NSF4V_MEM_DBG_MEM_DATA_SHIFT                                       (0x00000000U)
#define CSL_NSF4V_MEM_DBG_MEM_DATA_MAX                                         (0xFFFFFFFFU)

/**************************************************************************
* Hardware Region  : histogram 16 to 12-bit conversion LUT. Partial word write is not allowed due to ECC implementation
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t HIST_LUT[320];
} CSL_rawhist_lutRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWHIST_LUT_HIST_LUT(HIST_LUT)                                     (0x00000000U+((HIST_LUT)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* HIST_LUT */

#define CSL_RAWHIST_LUT_HIST_LUT_LUT_1_MASK                                    (0x0FFF0000U)
#define CSL_RAWHIST_LUT_HIST_LUT_LUT_1_SHIFT                                   (0x00000010U)
#define CSL_RAWHIST_LUT_HIST_LUT_LUT_1_MAX                                     (0x00000FFFU)

#define CSL_RAWHIST_LUT_HIST_LUT_LUT_0_MASK                                    (0x00000FFFU)
#define CSL_RAWHIST_LUT_HIST_LUT_LUT_0_SHIFT                                   (0x00000000U)
#define CSL_RAWHIST_LUT_HIST_LUT_LUT_0_MAX                                     (0x00000FFFU)

/**************************************************************************
* Hardware Region  : Histogram Data on Raw Domain
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t HIST[128];                 /* Hist Mem */
} CSL_rawhist_dataRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWHIST_DATA_HIST(HIST)                                            (0x00000000U+((HIST)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* HIST */

#define CSL_RAWHIST_DATA_HIST_HIST_VAL_MASK                                    (0x003FFFFFU)
#define CSL_RAWHIST_DATA_HIST_HIST_VAL_SHIFT                                   (0x00000000U)
#define CSL_RAWHIST_DATA_HIST_HIST_VAL_MAX                                     (0x003FFFFFU)

#ifdef __cplusplus
}
#endif
#endif

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
 *  Name        : cslr_flexcc.h
*/
#ifndef CSLR_FLEXCC_H_
#define CSLR_FLEXCC_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : MMR Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t W_0_1;                    /* CCM Weights */
    volatile uint32_t W_2_3;                    /* CCM Weights */
    volatile uint32_t OFFSET;                   /* CCM Offset */
} CSL_flexcc_CCMCoeff;
typedef struct {
    volatile uint32_t W0;                       /* RGBYUV Weights */
    volatile uint32_t W1;                       /* RGBYUV Weights/Offset */
} CSL_flexcc_RGB2YUVCoeff;
typedef struct {
    volatile uint32_t CFG_0;                     /* Config_0 */
    volatile uint32_t CFG_1;                     /* Config_1 */
    volatile uint32_t CFG_2;                     /* Config_2 */
    volatile uint32_t CFG_HIST_1;                /* Config Hist */
    volatile uint32_t CFG_HIST_2;                /* Config Hist */
    CSL_flexcc_CCMCoeff CCM[3U];                 /* CCM Coefficients */
    CSL_flexcc_RGB2YUVCoeff RGB2YUV[3U];         /* RGB2YUV Coefficients */
    volatile uint32_t RGBHSV_W0;                 /* RGBHSV Weights */
    volatile uint32_t RGBHSV_W1;                 /* RGBHSV Weights/Offset */
    volatile uint32_t RGBHSV_WB_LINLOGTHR_1;     /* THR0/THR1 */
    volatile uint32_t RGBHSV_WB_LINLOGTHR_2;     /* THR2/SatMinThr */
    volatile uint32_t RGBHSV_OFF1;               /* RGBHSV Offset1&2 */
    volatile uint32_t RGBHSV_OFF2;               /* RGBHSV Offset 3 */
    volatile uint32_t FLEXCC_INT_STATUS;         /* Int status/clear reg */
    volatile uint8_t  Resv_256[148];
    volatile uint32_t DEBUG_CTL;                 /* Debug control */
    volatile uint32_t DEBUG_STATUS;              /* Debug Event Status */
    volatile uint32_t DEBUG_RAW;                 /* Debug RAW Mode */
} CSL_flexcc_cfgRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXCC_CFG_CFG_0                                                   (0x00000000U)
#define CSL_FLEXCC_CFG_CFG_1                                                   (0x00000004U)
#define CSL_FLEXCC_CFG_CFG_2                                                   (0x00000008U)
#define CSL_FLEXCC_CFG_CFG_HIST_1                                              (0x0000000CU)
#define CSL_FLEXCC_CFG_CFG_HIST_2                                              (0x00000010U)
#define CSL_FLEXCC_CFG_CCM_W0_0_1                                              (0x00000014U)
#define CSL_FLEXCC_CFG_CCM_W0_2_3                                              (0x00000018U)
#define CSL_FLEXCC_CFG_CCM_OFFSET_0                                            (0x0000001CU)
#define CSL_FLEXCC_CFG_CCM_W1_0_1                                              (0x00000020U)
#define CSL_FLEXCC_CFG_CCM_W1_2_3                                              (0x00000024U)
#define CSL_FLEXCC_CFG_CCM_OFFSET_1                                            (0x00000028U)
#define CSL_FLEXCC_CFG_CCM_W2_0_1                                              (0x0000002CU)
#define CSL_FLEXCC_CFG_CCM_W2_2_3                                              (0x00000030U)
#define CSL_FLEXCC_CFG_CCM_OFFSET_2                                            (0x00000034U)
#define CSL_FLEXCC_CFG_RGBYUV_W01                                              (0x00000038U)
#define CSL_FLEXCC_CFG_RGBYUV_W02                                              (0x0000003CU)
#define CSL_FLEXCC_CFG_RGBYUV_W11                                              (0x00000040U)
#define CSL_FLEXCC_CFG_RGBYUV_W12                                              (0x00000044U)
#define CSL_FLEXCC_CFG_RGBYUV_W21                                              (0x00000048U)
#define CSL_FLEXCC_CFG_RGBYUV_W22                                              (0x0000004CU)
#define CSL_FLEXCC_CFG_RGBHSV_W0                                               (0x00000050U)
#define CSL_FLEXCC_CFG_RGBHSV_W1                                               (0x00000054U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1                                   (0x00000058U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2                                   (0x0000005CU)
#define CSL_FLEXCC_CFG_RGBHSV_OFF1                                             (0x00000060U)
#define CSL_FLEXCC_CFG_RGBHSV_OFF2                                             (0x00000064U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS                                       (0x00000068U)
#define CSL_FLEXCC_CFG_DEBUG_CTL                                               (0x00000100U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS                                            (0x00000104U)
#define CSL_FLEXCC_CFG_DEBUG_RAW                                               (0x00000108U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CFG_0 */

#define CSL_FLEXCC_CFG_CFG_0_HEIGHT_MASK                                       (0x1FFF0000U)
#define CSL_FLEXCC_CFG_CFG_0_HEIGHT_SHIFT                                      (0x00000010U)
#define CSL_FLEXCC_CFG_CFG_0_HEIGHT_MAX                                        (0x00001FFFU)

#define CSL_FLEXCC_CFG_CFG_0_RSVD_0_MASK                                       (0x0000E000U)
#define CSL_FLEXCC_CFG_CFG_0_RSVD_0_SHIFT                                      (0x0000000DU)
#define CSL_FLEXCC_CFG_CFG_0_RSVD_0_MAX                                        (0x00000007U)

#define CSL_FLEXCC_CFG_CFG_0_WIDTH_MASK                                        (0x00001FFFU)
#define CSL_FLEXCC_CFG_CFG_0_WIDTH_SHIFT                                       (0x00000000U)
#define CSL_FLEXCC_CFG_CFG_0_WIDTH_MAX                                         (0x00001FFFU)

/* CFG_1 */

#define CSL_FLEXCC_CFG_CFG_1_RSVD_3_MASK                                       (0xF0000000U)
#define CSL_FLEXCC_CFG_CFG_1_RSVD_3_SHIFT                                      (0x0000001CU)
#define CSL_FLEXCC_CFG_CFG_1_RSVD_3_MAX                                        (0x0000000FU)

#define CSL_FLEXCC_CFG_CFG_1_CHROMA_MODE_MASK                                  (0x08000000U)
#define CSL_FLEXCC_CFG_CFG_1_CHROMA_MODE_SHIFT                                 (0x0000001BU)
#define CSL_FLEXCC_CFG_CFG_1_CHROMA_MODE_MAX                                   (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_MUX_V_MASK                              (0x04000000U)
#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_MUX_V_SHIFT                             (0x0000001AU)
#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_MUX_V_MAX                               (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_H2_MASK                                 (0x02000000U)
#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_H2_SHIFT                                (0x00000019U)
#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_H2_MAX                                  (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_H1_MASK                                 (0x01000000U)
#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_H1_SHIFT                                (0x00000018U)
#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_H1_MAX                                  (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_1_RSVD_2_MASK                                       (0x00F00000U)
#define CSL_FLEXCC_CFG_CFG_1_RSVD_2_SHIFT                                      (0x00000014U)
#define CSL_FLEXCC_CFG_CFG_1_RSVD_2_MAX                                        (0x0000000FU)

#define CSL_FLEXCC_CFG_CFG_1_S8B8OUTEN_MASK                                    (0x000C0000U)
#define CSL_FLEXCC_CFG_CFG_1_S8B8OUTEN_SHIFT                                   (0x00000012U)
#define CSL_FLEXCC_CFG_CFG_1_S8B8OUTEN_MAX                                     (0x00000003U)

#define CSL_FLEXCC_CFG_CFG_1_C8G8OUTEN_MASK                                    (0x00030000U)
#define CSL_FLEXCC_CFG_CFG_1_C8G8OUTEN_SHIFT                                   (0x00000010U)
#define CSL_FLEXCC_CFG_CFG_1_C8G8OUTEN_MAX                                     (0x00000003U)

#define CSL_FLEXCC_CFG_CFG_1_Y8R8OUTEN_MASK                                    (0x0000C000U)
#define CSL_FLEXCC_CFG_CFG_1_Y8R8OUTEN_SHIFT                                   (0x0000000EU)
#define CSL_FLEXCC_CFG_CFG_1_Y8R8OUTEN_MAX                                     (0x00000003U)

#define CSL_FLEXCC_CFG_CFG_1_C12OUTEN_MASK                                     (0x00003000U)
#define CSL_FLEXCC_CFG_CFG_1_C12OUTEN_SHIFT                                    (0x0000000CU)
#define CSL_FLEXCC_CFG_CFG_1_C12OUTEN_MAX                                      (0x00000003U)

#define CSL_FLEXCC_CFG_CFG_1_Y12OUTEN_MASK                                     (0x00000800U)
#define CSL_FLEXCC_CFG_CFG_1_Y12OUTEN_SHIFT                                    (0x0000000BU)
#define CSL_FLEXCC_CFG_CFG_1_Y12OUTEN_MAX                                      (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_1_RSVD_0_MASK                                       (0x00000780U)
#define CSL_FLEXCC_CFG_CFG_1_RSVD_0_SHIFT                                      (0x00000007U)
#define CSL_FLEXCC_CFG_CFG_1_RSVD_0_MAX                                        (0x0000000FU)

#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_MASK                                    (0x00000040U)
#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_SHIFT                                   (0x00000006U)
#define CSL_FLEXCC_CFG_CFG_1_MUXRGBHSV_MAX                                     (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_1_MUXY8_OUT_MASK                                    (0x00000030U)
#define CSL_FLEXCC_CFG_CFG_1_MUXY8_OUT_SHIFT                                   (0x00000004U)
#define CSL_FLEXCC_CFG_CFG_1_MUXY8_OUT_MAX                                     (0x00000003U)

#define CSL_FLEXCC_CFG_CFG_1_MUXY12_OUT_MASK                                   (0x0000000CU)
#define CSL_FLEXCC_CFG_CFG_1_MUXY12_OUT_SHIFT                                  (0x00000002U)
#define CSL_FLEXCC_CFG_CFG_1_MUXY12_OUT_MAX                                    (0x00000003U)

#define CSL_FLEXCC_CFG_CFG_1_MUXC1_4_MASK                                      (0x00000003U)
#define CSL_FLEXCC_CFG_CFG_1_MUXC1_4_SHIFT                                     (0x00000000U)
#define CSL_FLEXCC_CFG_CFG_1_MUXC1_4_MAX                                       (0x00000003U)

/* CFG_2 */

#define CSL_FLEXCC_CFG_CFG_2_RSVD_1_MASK                                       (0xFFFE0000U)
#define CSL_FLEXCC_CFG_CFG_2_RSVD_1_SHIFT                                      (0x00000011U)
#define CSL_FLEXCC_CFG_CFG_2_RSVD_1_MAX                                        (0x00007FFFU)

#define CSL_FLEXCC_CFG_CFG_2_Y8INBITWIDTH_MASK                                 (0x0001E000U)
#define CSL_FLEXCC_CFG_CFG_2_Y8INBITWIDTH_SHIFT                                (0x0000000DU)
#define CSL_FLEXCC_CFG_CFG_2_Y8INBITWIDTH_MAX                                  (0x0000000FU)

#define CSL_FLEXCC_CFG_CFG_2_CONTRASTBITCLIP_MASK                              (0x00001E00U)
#define CSL_FLEXCC_CFG_CFG_2_CONTRASTBITCLIP_SHIFT                             (0x00000009U)
#define CSL_FLEXCC_CFG_CFG_2_CONTRASTBITCLIP_MAX                               (0x0000000FU)

#define CSL_FLEXCC_CFG_CFG_2_CONTRASTEN_MASK                                   (0x00000100U)
#define CSL_FLEXCC_CFG_CFG_2_CONTRASTEN_SHIFT                                  (0x00000008U)
#define CSL_FLEXCC_CFG_CFG_2_CONTRASTEN_MAX                                    (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_2_RSVD_0_MASK                                       (0x00000080U)
#define CSL_FLEXCC_CFG_CFG_2_RSVD_0_SHIFT                                      (0x00000007U)
#define CSL_FLEXCC_CFG_CFG_2_RSVD_0_MAX                                        (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_2_HSVSATMODE_MASK                                   (0x00000040U)
#define CSL_FLEXCC_CFG_CFG_2_HSVSATMODE_SHIFT                                  (0x00000006U)
#define CSL_FLEXCC_CFG_CFG_2_HSVSATMODE_MAX                                    (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_2_HSVSATDIVMODE_MASK                                (0x00000030U)
#define CSL_FLEXCC_CFG_CFG_2_HSVSATDIVMODE_SHIFT                               (0x00000004U)
#define CSL_FLEXCC_CFG_CFG_2_HSVSATDIVMODE_MAX                                 (0x00000003U)

#define CSL_FLEXCC_CFG_CFG_2_SATLUTEN_MASK                                     (0x00000008U)
#define CSL_FLEXCC_CFG_CFG_2_SATLUTEN_SHIFT                                    (0x00000003U)
#define CSL_FLEXCC_CFG_CFG_2_SATLUTEN_MAX                                      (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_2_RGB8LUTEN_MASK                                    (0x00000004U)
#define CSL_FLEXCC_CFG_CFG_2_RGB8LUTEN_SHIFT                                   (0x00000002U)
#define CSL_FLEXCC_CFG_CFG_2_RGB8LUTEN_MAX                                     (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_2_Y8LUTEN_MASK                                      (0x00000002U)
#define CSL_FLEXCC_CFG_CFG_2_Y8LUTEN_SHIFT                                     (0x00000001U)
#define CSL_FLEXCC_CFG_CFG_2_Y8LUTEN_MAX                                       (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_2_C8LUTEN_MASK                                      (0x00000001U)
#define CSL_FLEXCC_CFG_CFG_2_C8LUTEN_SHIFT                                     (0x00000000U)
#define CSL_FLEXCC_CFG_CFG_2_C8LUTEN_MAX                                       (0x00000001U)

/* CFG_HIST_1 */

#define CSL_FLEXCC_CFG_CFG_HIST_1_RSVD_1_MASK                                  (0xE0000000U)
#define CSL_FLEXCC_CFG_CFG_HIST_1_RSVD_1_SHIFT                                 (0x0000001DU)
#define CSL_FLEXCC_CFG_CFG_HIST_1_RSVD_1_MAX                                   (0x00000007U)

#define CSL_FLEXCC_CFG_CFG_HIST_1_HISTSTARTY_MASK                              (0x1FFF0000U)
#define CSL_FLEXCC_CFG_CFG_HIST_1_HISTSTARTY_SHIFT                             (0x00000010U)
#define CSL_FLEXCC_CFG_CFG_HIST_1_HISTSTARTY_MAX                               (0x00001FFFU)

#define CSL_FLEXCC_CFG_CFG_HIST_1_RSVD_0_MASK                                  (0x00008000U)
#define CSL_FLEXCC_CFG_CFG_HIST_1_RSVD_0_SHIFT                                 (0x0000000FU)
#define CSL_FLEXCC_CFG_CFG_HIST_1_RSVD_0_MAX                                   (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_HIST_1_BANK_MASK                                    (0x00004000U)
#define CSL_FLEXCC_CFG_CFG_HIST_1_BANK_SHIFT                                   (0x0000000EU)
#define CSL_FLEXCC_CFG_CFG_HIST_1_BANK_MAX                                     (0x00000001U)

#define CSL_FLEXCC_CFG_CFG_HIST_1_HISTSTARTX_MASK                              (0x00003FFEU)
#define CSL_FLEXCC_CFG_CFG_HIST_1_HISTSTARTX_SHIFT                             (0x00000001U)
#define CSL_FLEXCC_CFG_CFG_HIST_1_HISTSTARTX_MAX                               (0x00001FFFU)

#define CSL_FLEXCC_CFG_CFG_HIST_1_HISTEN_MASK                                  (0x00000001U)
#define CSL_FLEXCC_CFG_CFG_HIST_1_HISTEN_SHIFT                                 (0x00000000U)
#define CSL_FLEXCC_CFG_CFG_HIST_1_HISTEN_MAX                                   (0x00000001U)

/* CFG_HIST_2 */

#define CSL_FLEXCC_CFG_CFG_HIST_2_RSVD_0_MASK                                  (0xE0000000U)
#define CSL_FLEXCC_CFG_CFG_HIST_2_RSVD_0_SHIFT                                 (0x0000001DU)
#define CSL_FLEXCC_CFG_CFG_HIST_2_RSVD_0_MAX                                   (0x00000007U)

#define CSL_FLEXCC_CFG_CFG_HIST_2_HISTSIZEY_MASK                               (0x1FFF0000U)
#define CSL_FLEXCC_CFG_CFG_HIST_2_HISTSIZEY_SHIFT                              (0x00000010U)
#define CSL_FLEXCC_CFG_CFG_HIST_2_HISTSIZEY_MAX                                (0x00001FFFU)

#define CSL_FLEXCC_CFG_CFG_HIST_2_HISTMODE_MASK                                (0x0000E000U)
#define CSL_FLEXCC_CFG_CFG_HIST_2_HISTMODE_SHIFT                               (0x0000000DU)
#define CSL_FLEXCC_CFG_CFG_HIST_2_HISTMODE_MAX                                 (0x00000007U)

#define CSL_FLEXCC_CFG_CFG_HIST_2_HISTSIZEX_MASK                               (0x00001FFFU)
#define CSL_FLEXCC_CFG_CFG_HIST_2_HISTSIZEX_SHIFT                              (0x00000000U)
#define CSL_FLEXCC_CFG_CFG_HIST_2_HISTSIZEX_MAX                                (0x00001FFFU)

/* CCM_W0_0_1 */

#define CSL_FLEXCC_CFG_CCM_W0_0_1_RSVD_1_MASK                                  (0xF0000000U)
#define CSL_FLEXCC_CFG_CCM_W0_0_1_RSVD_1_SHIFT                                 (0x0000001CU)
#define CSL_FLEXCC_CFG_CCM_W0_0_1_RSVD_1_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W0_0_1_W_1_MASK                                     (0x0FFF0000U)
#define CSL_FLEXCC_CFG_CCM_W0_0_1_W_1_SHIFT                                    (0x00000010U)
#define CSL_FLEXCC_CFG_CCM_W0_0_1_W_1_MAX                                      (0x00000FFFU)

#define CSL_FLEXCC_CFG_CCM_W0_0_1_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_CCM_W0_0_1_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_CCM_W0_0_1_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W0_0_1_W_0_MASK                                     (0x00000FFFU)
#define CSL_FLEXCC_CFG_CCM_W0_0_1_W_0_SHIFT                                    (0x00000000U)
#define CSL_FLEXCC_CFG_CCM_W0_0_1_W_0_MAX                                      (0x00000FFFU)

/* CCM_W0_2_3 */

#define CSL_FLEXCC_CFG_CCM_W0_2_3_RSVD_1_MASK                                  (0xF0000000U)
#define CSL_FLEXCC_CFG_CCM_W0_2_3_RSVD_1_SHIFT                                 (0x0000001CU)
#define CSL_FLEXCC_CFG_CCM_W0_2_3_RSVD_1_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W0_2_3_W_3_MASK                                     (0x0FFF0000U)
#define CSL_FLEXCC_CFG_CCM_W0_2_3_W_3_SHIFT                                    (0x00000010U)
#define CSL_FLEXCC_CFG_CCM_W0_2_3_W_3_MAX                                      (0x00000FFFU)

#define CSL_FLEXCC_CFG_CCM_W0_2_3_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_CCM_W0_2_3_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_CCM_W0_2_3_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W0_2_3_W_2_MASK                                     (0x00000FFFU)
#define CSL_FLEXCC_CFG_CCM_W0_2_3_W_2_SHIFT                                    (0x00000000U)
#define CSL_FLEXCC_CFG_CCM_W0_2_3_W_2_MAX                                      (0x00000FFFU)

/* CCM_OFFSET_0 */

#define CSL_FLEXCC_CFG_CCM_OFFSET_0_RSVD_0_MASK                                (0xFFFFE000U)
#define CSL_FLEXCC_CFG_CCM_OFFSET_0_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_FLEXCC_CFG_CCM_OFFSET_0_RSVD_0_MAX                                 (0x0007FFFFU)

#define CSL_FLEXCC_CFG_CCM_OFFSET_0_OFFSET_0_MASK                              (0x00001FFFU)
#define CSL_FLEXCC_CFG_CCM_OFFSET_0_OFFSET_0_SHIFT                             (0x00000000U)
#define CSL_FLEXCC_CFG_CCM_OFFSET_0_OFFSET_0_MAX                               (0x00001FFFU)

/* CCM_W1_0_1 */

#define CSL_FLEXCC_CFG_CCM_W1_0_1_RSVD_1_MASK                                  (0xF0000000U)
#define CSL_FLEXCC_CFG_CCM_W1_0_1_RSVD_1_SHIFT                                 (0x0000001CU)
#define CSL_FLEXCC_CFG_CCM_W1_0_1_RSVD_1_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W1_0_1_W_1_MASK                                     (0x0FFF0000U)
#define CSL_FLEXCC_CFG_CCM_W1_0_1_W_1_SHIFT                                    (0x00000010U)
#define CSL_FLEXCC_CFG_CCM_W1_0_1_W_1_MAX                                      (0x00000FFFU)

#define CSL_FLEXCC_CFG_CCM_W1_0_1_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_CCM_W1_0_1_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_CCM_W1_0_1_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W1_0_1_W_0_MASK                                     (0x00000FFFU)
#define CSL_FLEXCC_CFG_CCM_W1_0_1_W_0_SHIFT                                    (0x00000000U)
#define CSL_FLEXCC_CFG_CCM_W1_0_1_W_0_MAX                                      (0x00000FFFU)

/* CCM_W1_2_3 */

#define CSL_FLEXCC_CFG_CCM_W1_2_3_RSVD_1_MASK                                  (0xF0000000U)
#define CSL_FLEXCC_CFG_CCM_W1_2_3_RSVD_1_SHIFT                                 (0x0000001CU)
#define CSL_FLEXCC_CFG_CCM_W1_2_3_RSVD_1_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W1_2_3_W_3_MASK                                     (0x0FFF0000U)
#define CSL_FLEXCC_CFG_CCM_W1_2_3_W_3_SHIFT                                    (0x00000010U)
#define CSL_FLEXCC_CFG_CCM_W1_2_3_W_3_MAX                                      (0x00000FFFU)

#define CSL_FLEXCC_CFG_CCM_W1_2_3_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_CCM_W1_2_3_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_CCM_W1_2_3_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W1_2_3_W_2_MASK                                     (0x00000FFFU)
#define CSL_FLEXCC_CFG_CCM_W1_2_3_W_2_SHIFT                                    (0x00000000U)
#define CSL_FLEXCC_CFG_CCM_W1_2_3_W_2_MAX                                      (0x00000FFFU)

/* CCM_OFFSET_1 */

#define CSL_FLEXCC_CFG_CCM_OFFSET_1_RSVD_0_MASK                                (0xFFFFE000U)
#define CSL_FLEXCC_CFG_CCM_OFFSET_1_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_FLEXCC_CFG_CCM_OFFSET_1_RSVD_0_MAX                                 (0x0007FFFFU)

#define CSL_FLEXCC_CFG_CCM_OFFSET_1_OFFSET_1_MASK                              (0x00001FFFU)
#define CSL_FLEXCC_CFG_CCM_OFFSET_1_OFFSET_1_SHIFT                             (0x00000000U)
#define CSL_FLEXCC_CFG_CCM_OFFSET_1_OFFSET_1_MAX                               (0x00001FFFU)

/* CCM_W2_0_1 */

#define CSL_FLEXCC_CFG_CCM_W2_0_1_RSVD_1_MASK                                  (0xF0000000U)
#define CSL_FLEXCC_CFG_CCM_W2_0_1_RSVD_1_SHIFT                                 (0x0000001CU)
#define CSL_FLEXCC_CFG_CCM_W2_0_1_RSVD_1_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W2_0_1_W_1_MASK                                     (0x0FFF0000U)
#define CSL_FLEXCC_CFG_CCM_W2_0_1_W_1_SHIFT                                    (0x00000010U)
#define CSL_FLEXCC_CFG_CCM_W2_0_1_W_1_MAX                                      (0x00000FFFU)

#define CSL_FLEXCC_CFG_CCM_W2_0_1_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_CCM_W2_0_1_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_CCM_W2_0_1_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W2_0_1_W_0_MASK                                     (0x00000FFFU)
#define CSL_FLEXCC_CFG_CCM_W2_0_1_W_0_SHIFT                                    (0x00000000U)
#define CSL_FLEXCC_CFG_CCM_W2_0_1_W_0_MAX                                      (0x00000FFFU)

/* CCM_W2_2_3 */

#define CSL_FLEXCC_CFG_CCM_W2_2_3_RSVD_1_MASK                                  (0xF0000000U)
#define CSL_FLEXCC_CFG_CCM_W2_2_3_RSVD_1_SHIFT                                 (0x0000001CU)
#define CSL_FLEXCC_CFG_CCM_W2_2_3_RSVD_1_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W2_2_3_W_3_MASK                                     (0x0FFF0000U)
#define CSL_FLEXCC_CFG_CCM_W2_2_3_W_3_SHIFT                                    (0x00000010U)
#define CSL_FLEXCC_CFG_CCM_W2_2_3_W_3_MAX                                      (0x00000FFFU)

#define CSL_FLEXCC_CFG_CCM_W2_2_3_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_CCM_W2_2_3_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_CCM_W2_2_3_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_CCM_W2_2_3_W_2_MASK                                     (0x00000FFFU)
#define CSL_FLEXCC_CFG_CCM_W2_2_3_W_2_SHIFT                                    (0x00000000U)
#define CSL_FLEXCC_CFG_CCM_W2_2_3_W_2_MAX                                      (0x00000FFFU)

/* CCM_OFFSET_2 */

#define CSL_FLEXCC_CFG_CCM_OFFSET_2_RSVD_0_MASK                                (0xFFFFE000U)
#define CSL_FLEXCC_CFG_CCM_OFFSET_2_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_FLEXCC_CFG_CCM_OFFSET_2_RSVD_0_MAX                                 (0x0007FFFFU)

#define CSL_FLEXCC_CFG_CCM_OFFSET_2_OFFSET_2_MASK                              (0x00001FFFU)
#define CSL_FLEXCC_CFG_CCM_OFFSET_2_OFFSET_2_SHIFT                             (0x00000000U)
#define CSL_FLEXCC_CFG_CCM_OFFSET_2_OFFSET_2_MAX                               (0x00001FFFU)

/* RGBYUV_W01 */

#define CSL_FLEXCC_CFG_RGBYUV_W01_RSVD_1_MASK                                  (0xF0000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W01_RSVD_1_SHIFT                                 (0x0000001CU)
#define CSL_FLEXCC_CFG_RGBYUV_W01_RSVD_1_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBYUV_W01_W_02_MASK                                    (0x0FFF0000U)
#define CSL_FLEXCC_CFG_RGBYUV_W01_W_02_SHIFT                                   (0x00000010U)
#define CSL_FLEXCC_CFG_RGBYUV_W01_W_02_MAX                                     (0x00000FFFU)

#define CSL_FLEXCC_CFG_RGBYUV_W01_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBYUV_W01_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBYUV_W01_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBYUV_W01_W_01_MASK                                    (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBYUV_W01_W_01_SHIFT                                   (0x00000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W01_W_01_MAX                                     (0x00000FFFU)

/* RGBYUV_W02 */

#define CSL_FLEXCC_CFG_RGBYUV_W02_RSVD_1_MASK                                  (0xE0000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W02_RSVD_1_SHIFT                                 (0x0000001DU)
#define CSL_FLEXCC_CFG_RGBYUV_W02_RSVD_1_MAX                                   (0x00000007U)

#define CSL_FLEXCC_CFG_RGBYUV_W02_OFFSET_0_MASK                                (0x1FFF0000U)
#define CSL_FLEXCC_CFG_RGBYUV_W02_OFFSET_0_SHIFT                               (0x00000010U)
#define CSL_FLEXCC_CFG_RGBYUV_W02_OFFSET_0_MAX                                 (0x00001FFFU)

#define CSL_FLEXCC_CFG_RGBYUV_W02_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBYUV_W02_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBYUV_W02_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBYUV_W02_W_03_MASK                                    (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBYUV_W02_W_03_SHIFT                                   (0x00000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W02_W_03_MAX                                     (0x00000FFFU)

/* RGBYUV_W11 */

#define CSL_FLEXCC_CFG_RGBYUV_W11_RSVD_1_MASK                                  (0xF0000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W11_RSVD_1_SHIFT                                 (0x0000001CU)
#define CSL_FLEXCC_CFG_RGBYUV_W11_RSVD_1_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBYUV_W11_W_12_MASK                                    (0x0FFF0000U)
#define CSL_FLEXCC_CFG_RGBYUV_W11_W_12_SHIFT                                   (0x00000010U)
#define CSL_FLEXCC_CFG_RGBYUV_W11_W_12_MAX                                     (0x00000FFFU)

#define CSL_FLEXCC_CFG_RGBYUV_W11_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBYUV_W11_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBYUV_W11_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBYUV_W11_W_11_MASK                                    (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBYUV_W11_W_11_SHIFT                                   (0x00000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W11_W_11_MAX                                     (0x00000FFFU)

/* RGBYUV_W12 */

#define CSL_FLEXCC_CFG_RGBYUV_W12_RSVD_1_MASK                                  (0xE0000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W12_RSVD_1_SHIFT                                 (0x0000001DU)
#define CSL_FLEXCC_CFG_RGBYUV_W12_RSVD_1_MAX                                   (0x00000007U)

#define CSL_FLEXCC_CFG_RGBYUV_W12_OFFSET_1_MASK                                (0x1FFF0000U)
#define CSL_FLEXCC_CFG_RGBYUV_W12_OFFSET_1_SHIFT                               (0x00000010U)
#define CSL_FLEXCC_CFG_RGBYUV_W12_OFFSET_1_MAX                                 (0x00001FFFU)

#define CSL_FLEXCC_CFG_RGBYUV_W12_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBYUV_W12_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBYUV_W12_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBYUV_W12_W_13_MASK                                    (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBYUV_W12_W_13_SHIFT                                   (0x00000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W12_W_13_MAX                                     (0x00000FFFU)

/* RGBYUV_W21 */

#define CSL_FLEXCC_CFG_RGBYUV_W21_RSVD_1_MASK                                  (0xF0000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W21_RSVD_1_SHIFT                                 (0x0000001CU)
#define CSL_FLEXCC_CFG_RGBYUV_W21_RSVD_1_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBYUV_W21_W_22_MASK                                    (0x0FFF0000U)
#define CSL_FLEXCC_CFG_RGBYUV_W21_W_22_SHIFT                                   (0x00000010U)
#define CSL_FLEXCC_CFG_RGBYUV_W21_W_22_MAX                                     (0x00000FFFU)

#define CSL_FLEXCC_CFG_RGBYUV_W21_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBYUV_W21_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBYUV_W21_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBYUV_W21_W_21_MASK                                    (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBYUV_W21_W_21_SHIFT                                   (0x00000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W21_W_21_MAX                                     (0x00000FFFU)

/* RGBYUV_W22 */

#define CSL_FLEXCC_CFG_RGBYUV_W22_RSVD_1_MASK                                  (0xE0000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W22_RSVD_1_SHIFT                                 (0x0000001DU)
#define CSL_FLEXCC_CFG_RGBYUV_W22_RSVD_1_MAX                                   (0x00000007U)

#define CSL_FLEXCC_CFG_RGBYUV_W22_OFFSET_2_MASK                                (0x1FFF0000U)
#define CSL_FLEXCC_CFG_RGBYUV_W22_OFFSET_2_SHIFT                               (0x00000010U)
#define CSL_FLEXCC_CFG_RGBYUV_W22_OFFSET_2_MAX                                 (0x00001FFFU)

#define CSL_FLEXCC_CFG_RGBYUV_W22_RSVD_0_MASK                                  (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBYUV_W22_RSVD_0_SHIFT                                 (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBYUV_W22_RSVD_0_MAX                                   (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBYUV_W22_W_23_MASK                                    (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBYUV_W22_W_23_SHIFT                                   (0x00000000U)
#define CSL_FLEXCC_CFG_RGBYUV_W22_W_23_MAX                                     (0x00000FFFU)

/* RGBHSV_W0 */

#define CSL_FLEXCC_CFG_RGBHSV_W0_RSVD_1_MASK                                   (0xF0000000U)
#define CSL_FLEXCC_CFG_RGBHSV_W0_RSVD_1_SHIFT                                  (0x0000001CU)
#define CSL_FLEXCC_CFG_RGBHSV_W0_RSVD_1_MAX                                    (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBHSV_W0_W12_MASK                                      (0x0FFF0000U)
#define CSL_FLEXCC_CFG_RGBHSV_W0_W12_SHIFT                                     (0x00000010U)
#define CSL_FLEXCC_CFG_RGBHSV_W0_W12_MAX                                       (0x00000FFFU)

#define CSL_FLEXCC_CFG_RGBHSV_W0_RSVD_0_MASK                                   (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBHSV_W0_RSVD_0_SHIFT                                  (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBHSV_W0_RSVD_0_MAX                                    (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBHSV_W0_W11_MASK                                      (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBHSV_W0_W11_SHIFT                                     (0x00000000U)
#define CSL_FLEXCC_CFG_RGBHSV_W0_W11_MAX                                       (0x00000FFFU)

/* RGBHSV_W1 */

#define CSL_FLEXCC_CFG_RGBHSV_W1_RSVD_1_MASK                                   (0xE0000000U)
#define CSL_FLEXCC_CFG_RGBHSV_W1_RSVD_1_SHIFT                                  (0x0000001DU)
#define CSL_FLEXCC_CFG_RGBHSV_W1_RSVD_1_MAX                                    (0x00000007U)

#define CSL_FLEXCC_CFG_RGBHSV_W1_OFFSET_1_MASK                                 (0x1FFF0000U)
#define CSL_FLEXCC_CFG_RGBHSV_W1_OFFSET_1_SHIFT                                (0x00000010U)
#define CSL_FLEXCC_CFG_RGBHSV_W1_OFFSET_1_MAX                                  (0x00001FFFU)

#define CSL_FLEXCC_CFG_RGBHSV_W1_RSVD_0_MASK                                   (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBHSV_W1_RSVD_0_SHIFT                                  (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBHSV_W1_RSVD_0_MAX                                    (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBHSV_W1_W13_MASK                                      (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBHSV_W1_W13_SHIFT                                     (0x00000000U)
#define CSL_FLEXCC_CFG_RGBHSV_W1_W13_MAX                                       (0x00000FFFU)

/* RGBHSV_WB_LINLOGTHR_1 */

#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_RSVD_1_MASK                       (0xF0000000U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_RSVD_1_SHIFT                      (0x0000001CU)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_RSVD_1_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_THR_1_MASK                        (0x0FFF0000U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_THR_1_SHIFT                       (0x00000010U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_THR_1_MAX                         (0x00000FFFU)

#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_RSVD_0_MASK                       (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_RSVD_0_SHIFT                      (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_RSVD_0_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_THR_0_MASK                        (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_THR_0_SHIFT                       (0x00000000U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_1_THR_0_MAX                         (0x00000FFFU)

/* RGBHSV_WB_LINLOGTHR_2 */

#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_RSVD_1_MASK                       (0xF0000000U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_RSVD_1_SHIFT                      (0x0000001CU)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_RSVD_1_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_SATMINTHR_MASK                    (0x0FFF0000U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_SATMINTHR_SHIFT                   (0x00000010U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_SATMINTHR_MAX                     (0x00000FFFU)

#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_RSVD_0_MASK                       (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_RSVD_0_SHIFT                      (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_RSVD_0_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_THR_2_MASK                        (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_THR_2_SHIFT                       (0x00000000U)
#define CSL_FLEXCC_CFG_RGBHSV_WB_LINLOGTHR_2_THR_2_MAX                         (0x00000FFFU)

/* RGBHSV_OFF1 */

#define CSL_FLEXCC_CFG_RGBHSV_OFF1_RSVD_1_MASK                                 (0xF0000000U)
#define CSL_FLEXCC_CFG_RGBHSV_OFF1_RSVD_1_SHIFT                                (0x0000001CU)
#define CSL_FLEXCC_CFG_RGBHSV_OFF1_RSVD_1_MAX                                  (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBHSV_OFF1_OFFSET_2_MASK                               (0x0FFF0000U)
#define CSL_FLEXCC_CFG_RGBHSV_OFF1_OFFSET_2_SHIFT                              (0x00000010U)
#define CSL_FLEXCC_CFG_RGBHSV_OFF1_OFFSET_2_MAX                                (0x00000FFFU)

#define CSL_FLEXCC_CFG_RGBHSV_OFF1_RSVD_0_MASK                                 (0x0000F000U)
#define CSL_FLEXCC_CFG_RGBHSV_OFF1_RSVD_0_SHIFT                                (0x0000000CU)
#define CSL_FLEXCC_CFG_RGBHSV_OFF1_RSVD_0_MAX                                  (0x0000000FU)

#define CSL_FLEXCC_CFG_RGBHSV_OFF1_OFFSET_1_MASK                               (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBHSV_OFF1_OFFSET_1_SHIFT                              (0x00000000U)
#define CSL_FLEXCC_CFG_RGBHSV_OFF1_OFFSET_1_MAX                                (0x00000FFFU)

/* RGBHSV_OFF2 */

#define CSL_FLEXCC_CFG_RGBHSV_OFF2_RSVD_0_MASK                                 (0xFFFFE000U)
#define CSL_FLEXCC_CFG_RGBHSV_OFF2_RSVD_0_SHIFT                                (0x0000000DU)
#define CSL_FLEXCC_CFG_RGBHSV_OFF2_RSVD_0_MAX                                  (0x0007FFFFU)

#define CSL_FLEXCC_CFG_RGBHSV_OFF2_OFFSET_3_MASK                               (0x00000FFFU)
#define CSL_FLEXCC_CFG_RGBHSV_OFF2_OFFSET_3_SHIFT                              (0x00000000U)
#define CSL_FLEXCC_CFG_RGBHSV_OFF2_OFFSET_3_MAX                                (0x00000FFFU)

/* FLEXCC_INT_STATUS */

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_RSVD_0_MASK                           (0xFFFFF000U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_RSVD_0_SHIFT                          (0x0000000CU)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_RSVD_0_MAX                            (0x000FFFFFU)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_HIST_READ_ERR_MASK                    (0x00000800U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_HIST_READ_ERR_SHIFT                   (0x0000000BU)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_HIST_READ_ERR_MAX                     (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_LUT_12TO82_CFG_ERR_MASK               (0x00000400U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_LUT_12TO82_CFG_ERR_SHIFT              (0x0000000AU)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_LUT_12TO82_CFG_ERR_MAX                (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_LUT_12TO81_CFG_ERR_MASK               (0x00000200U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_LUT_12TO81_CFG_ERR_SHIFT              (0x00000009U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_LUT_12TO81_CFG_ERR_MAX                (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_LUT_12TO80_CFG_ERR_MASK               (0x00000100U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_LUT_12TO80_CFG_ERR_SHIFT              (0x00000008U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_LUT_12TO80_CFG_ERR_MAX                (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_CONTRAST2_CFG_ERR_MASK                (0x00000080U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_CONTRAST2_CFG_ERR_SHIFT               (0x00000007U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_CONTRAST2_CFG_ERR_MAX                 (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_CONTRAST1_CFG_ERR_MASK                (0x00000040U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_CONTRAST1_CFG_ERR_SHIFT               (0x00000006U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_CONTRAST1_CFG_ERR_MAX                 (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_CONTRAST0_CFG_ERR_MASK                (0x00000020U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_CONTRAST0_CFG_ERR_SHIFT               (0x00000005U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_CONTRAST0_CFG_ERR_MAX                 (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_S8B8_MASK                 (0x00000010U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_S8B8_SHIFT                (0x00000004U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_S8B8_MAX                  (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_C8G8_MASK                 (0x00000008U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_C8G8_SHIFT                (0x00000003U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_C8G8_MAX                  (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_Y8R8_MASK                 (0x00000004U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_Y8R8_SHIFT                (0x00000002U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_Y8R8_MAX                  (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_UV12_MASK                 (0x00000002U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_UV12_SHIFT                (0x00000001U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_UV12_MAX                  (0x00000001U)

#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_Y12_MASK                  (0x00000001U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_Y12_SHIFT                 (0x00000000U)
#define CSL_FLEXCC_CFG_FLEXCC_INT_STATUS_OVERFLOW_IF_Y12_MAX                   (0x00000001U)

/* DEBUG_CTL */

#define CSL_FLEXCC_CFG_DEBUG_CTL_RSVD_0_MASK                                   (0xFFFFE000U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_RSVD_0_SHIFT                                  (0x0000000DU)
#define CSL_FLEXCC_CFG_DEBUG_CTL_RSVD_0_MAX                                    (0x0007FFFFU)

#define CSL_FLEXCC_CFG_DEBUG_CTL_FLEXCC_EOP_EN_MASK                            (0x00001000U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_FLEXCC_EOP_EN_SHIFT                           (0x0000000CU)
#define CSL_FLEXCC_CFG_DEBUG_CTL_FLEXCC_EOP_EN_MAX                             (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_S8B8_EN_MASK                           (0x00000800U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_S8B8_EN_SHIFT                          (0x0000000BU)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_S8B8_EN_MAX                            (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_S8B8_EN_MASK                           (0x00000400U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_S8B8_EN_SHIFT                          (0x0000000AU)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_S8B8_EN_MAX                            (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_C8G8_EN_MASK                           (0x00000200U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_C8G8_EN_SHIFT                          (0x00000009U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_C8G8_EN_MAX                            (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_C8G8_EN_MASK                           (0x00000100U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_C8G8_EN_SHIFT                          (0x00000008U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_C8G8_EN_MAX                            (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_Y8R8_EN_MASK                           (0x00000080U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_Y8R8_EN_SHIFT                          (0x00000007U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_Y8R8_EN_MAX                            (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_Y8R8_EN_MASK                           (0x00000040U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_Y8R8_EN_SHIFT                          (0x00000006U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_Y8R8_EN_MAX                            (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_UV12_EN_MASK                           (0x00000020U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_UV12_EN_SHIFT                          (0x00000005U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_UV12_EN_MAX                            (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_UV12_EN_MASK                           (0x00000010U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_UV12_EN_SHIFT                          (0x00000004U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_UV12_EN_MAX                            (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_Y12_EN_MASK                            (0x00000008U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_Y12_EN_SHIFT                           (0x00000003U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOF_IF_Y12_EN_MAX                             (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_Y12_EN_MASK                            (0x00000004U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_Y12_EN_SHIFT                           (0x00000002U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_EOL_IF_Y12_EN_MAX                             (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_STALL_EN_MASK                                 (0x00000002U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_STALL_EN_SHIFT                                (0x00000001U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_STALL_EN_MAX                                  (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_CTL_DBG_EN_MASK                                   (0x00000001U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_DBG_EN_SHIFT                                  (0x00000000U)
#define CSL_FLEXCC_CFG_DEBUG_CTL_DBG_EN_MAX                                    (0x00000001U)

/* DEBUG_STATUS */

#define CSL_FLEXCC_CFG_DEBUG_STATUS_RSVD_0_MASK                                (0xFFFFE000U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_RSVD_0_MAX                                 (0x0007FFFFU)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_FLEXCC_EOP_EVENT_MASK                      (0x00001000U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_FLEXCC_EOP_EVENT_SHIFT                     (0x0000000CU)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_FLEXCC_EOP_EVENT_MAX                       (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_S8B8_EVENT_MASK                     (0x00000800U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_S8B8_EVENT_SHIFT                    (0x0000000BU)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_S8B8_EVENT_MAX                      (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_S8B8_EVENT_MASK                     (0x00000400U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_S8B8_EVENT_SHIFT                    (0x0000000AU)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_S8B8_EVENT_MAX                      (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_C8G8_EVENT_MASK                     (0x00000200U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_C8G8_EVENT_SHIFT                    (0x00000009U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_C8G8_EVENT_MAX                      (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_C8G8_EVENT_MASK                     (0x00000100U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_C8G8_EVENT_SHIFT                    (0x00000008U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_C8G8_EVENT_MAX                      (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_Y8R8_EVENT_MASK                     (0x00000080U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_Y8R8_EVENT_SHIFT                    (0x00000007U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_Y8R8_EVENT_MAX                      (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_Y8R8_EVENT_MASK                     (0x00000040U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_Y8R8_EVENT_SHIFT                    (0x00000006U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_Y8R8_EVENT_MAX                      (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_UV12_EVENT_MASK                     (0x00000020U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_UV12_EVENT_SHIFT                    (0x00000005U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_UV12_EVENT_MAX                      (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_UV12_EVENT_MASK                     (0x00000010U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_UV12_EVENT_SHIFT                    (0x00000004U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_UV12_EVENT_MAX                      (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_Y12_EVENT_MASK                      (0x00000008U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_Y12_EVENT_SHIFT                     (0x00000003U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOF_IF_Y12_EVENT_MAX                       (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_Y12_EVENT_MASK                      (0x00000004U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_Y12_EVENT_SHIFT                     (0x00000002U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_EOL_IF_Y12_EVENT_MAX                       (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_STALL_EVENT_MASK                           (0x00000002U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_STALL_EVENT_SHIFT                          (0x00000001U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_STALL_EVENT_MAX                            (0x00000001U)

#define CSL_FLEXCC_CFG_DEBUG_STATUS_RSVD_MASK                                  (0x00000001U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_RSVD_SHIFT                                 (0x00000000U)
#define CSL_FLEXCC_CFG_DEBUG_STATUS_RSVD_MAX                                   (0x00000001U)

/* DEBUG_RAW */

#define CSL_FLEXCC_CFG_DEBUG_RAW_DBG_RAW_MODE_MASK                             (0x00000001U)
#define CSL_FLEXCC_CFG_DEBUG_RAW_DBG_RAW_MODE_SHIFT                            (0x00000000U)
#define CSL_FLEXCC_CFG_DEBUG_RAW_DBG_RAW_MODE_MAX                              (0x00000001U)

/**************************************************************************
* Hardware Region  : contrast memory
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT_CONTRASTC1[257];       /* contrast memory */
} CSL_flexcc_contrastc1Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1(LUT_CONTRASTC1)                   (0x00000000U+((LUT_CONTRASTC1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT_CONTRASTC1 */

#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_RSVD_1_MASK                       (0xF0000000U)
#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_RSVD_1_SHIFT                      (0x0000001CU)
#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_RSVD_1_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_LUT_1_MASK                        (0x0FFF0000U)
#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_LUT_1_SHIFT                       (0x00000010U)
#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_LUT_1_MAX                         (0x00000FFFU)

#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_RSVD_0_MASK                       (0x0000F000U)
#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_RSVD_0_SHIFT                      (0x0000000CU)
#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_RSVD_0_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_LUT_0_MASK                        (0x00000FFFU)
#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_LUT_0_SHIFT                       (0x00000000U)
#define CSL_FLEXCC_CONTRASTC1_LUT_CONTRASTC1_LUT_0_MAX                         (0x00000FFFU)

/**************************************************************************
* Hardware Region  : contrast memory
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT_CONTRASTC2[257];       /* contrast memory */
} CSL_flexcc_contrastc2Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2(LUT_CONTRASTC2)                   (0x00000000U+((LUT_CONTRASTC2)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT_CONTRASTC2 */

#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_RSVD_1_MASK                       (0xF0000000U)
#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_RSVD_1_SHIFT                      (0x0000001CU)
#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_RSVD_1_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_LUT_1_MASK                        (0x0FFF0000U)
#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_LUT_1_SHIFT                       (0x00000010U)
#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_LUT_1_MAX                         (0x00000FFFU)

#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_RSVD_0_MASK                       (0x0000F000U)
#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_RSVD_0_SHIFT                      (0x0000000CU)
#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_RSVD_0_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_LUT_0_MASK                        (0x00000FFFU)
#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_LUT_0_SHIFT                       (0x00000000U)
#define CSL_FLEXCC_CONTRASTC2_LUT_CONTRASTC2_LUT_0_MAX                         (0x00000FFFU)

/**************************************************************************
* Hardware Region  : contrast memory
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT_CONTRASTC3[257];       /* contrast memory */
} CSL_flexcc_contrastc3Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3(LUT_CONTRASTC3)                   (0x00000000U+((LUT_CONTRASTC3)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT_CONTRASTC3 */

#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_RSVD_1_MASK                       (0xF0000000U)
#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_RSVD_1_SHIFT                      (0x0000001CU)
#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_RSVD_1_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_LUT_1_MASK                        (0x0FFF0000U)
#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_LUT_1_SHIFT                       (0x00000010U)
#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_LUT_1_MAX                         (0x00000FFFU)

#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_RSVD_0_MASK                       (0x0000F000U)
#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_RSVD_0_SHIFT                      (0x0000000CU)
#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_RSVD_0_MAX                        (0x0000000FU)

#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_LUT_0_MASK                        (0x00000FFFU)
#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_LUT_0_SHIFT                       (0x00000000U)
#define CSL_FLEXCC_CONTRASTC3_LUT_CONTRASTC3_LUT_0_MAX                         (0x00000FFFU)

/**************************************************************************
* Hardware Region  : 12 to 8 LUT
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT_Y8R8[257];             /* 12to8 Mem */
} CSL_flexcc_y8r8Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXCC_Y8R8_LUT_Y8R8(LUT_Y8R8)                                     (0x00000000U+((LUT_Y8R8)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT_Y8R8 */

#define CSL_FLEXCC_Y8R8_LUT_Y8R8_RSVD_1_MASK                                   (0xFF000000U)
#define CSL_FLEXCC_Y8R8_LUT_Y8R8_RSVD_1_SHIFT                                  (0x00000018U)
#define CSL_FLEXCC_Y8R8_LUT_Y8R8_RSVD_1_MAX                                    (0x000000FFU)

#define CSL_FLEXCC_Y8R8_LUT_Y8R8_LUT_1_MASK                                    (0x00FF0000U)
#define CSL_FLEXCC_Y8R8_LUT_Y8R8_LUT_1_SHIFT                                   (0x00000010U)
#define CSL_FLEXCC_Y8R8_LUT_Y8R8_LUT_1_MAX                                     (0x000000FFU)

#define CSL_FLEXCC_Y8R8_LUT_Y8R8_RSVD_0_MASK                                   (0x0000FF00U)
#define CSL_FLEXCC_Y8R8_LUT_Y8R8_RSVD_0_SHIFT                                  (0x00000008U)
#define CSL_FLEXCC_Y8R8_LUT_Y8R8_RSVD_0_MAX                                    (0x000000FFU)

#define CSL_FLEXCC_Y8R8_LUT_Y8R8_LUT_0_MASK                                    (0x000000FFU)
#define CSL_FLEXCC_Y8R8_LUT_Y8R8_LUT_0_SHIFT                                   (0x00000000U)
#define CSL_FLEXCC_Y8R8_LUT_Y8R8_LUT_0_MAX                                     (0x000000FFU)

/**************************************************************************
* Hardware Region  : 12 to 8 LUT
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT_C8G8[257];             /* 12to8 Mem */
} CSL_flexcc_c8g8Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXCC_C8G8_LUT_C8G8(LUT_C8G8)                                     (0x00000000U+((LUT_C8G8)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT_C8G8 */

#define CSL_FLEXCC_C8G8_LUT_C8G8_RSVD_1_MASK                                   (0xFF000000U)
#define CSL_FLEXCC_C8G8_LUT_C8G8_RSVD_1_SHIFT                                  (0x00000018U)
#define CSL_FLEXCC_C8G8_LUT_C8G8_RSVD_1_MAX                                    (0x000000FFU)

#define CSL_FLEXCC_C8G8_LUT_C8G8_LUT_1_MASK                                    (0x00FF0000U)
#define CSL_FLEXCC_C8G8_LUT_C8G8_LUT_1_SHIFT                                   (0x00000010U)
#define CSL_FLEXCC_C8G8_LUT_C8G8_LUT_1_MAX                                     (0x000000FFU)

#define CSL_FLEXCC_C8G8_LUT_C8G8_RSVD_0_MASK                                   (0x0000FF00U)
#define CSL_FLEXCC_C8G8_LUT_C8G8_RSVD_0_SHIFT                                  (0x00000008U)
#define CSL_FLEXCC_C8G8_LUT_C8G8_RSVD_0_MAX                                    (0x000000FFU)

#define CSL_FLEXCC_C8G8_LUT_C8G8_LUT_0_MASK                                    (0x000000FFU)
#define CSL_FLEXCC_C8G8_LUT_C8G8_LUT_0_SHIFT                                   (0x00000000U)
#define CSL_FLEXCC_C8G8_LUT_C8G8_LUT_0_MAX                                     (0x000000FFU)

/**************************************************************************
* Hardware Region  : 12 to 8 LUT
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT_S8B8[257];             /* 12to8 Mem */
} CSL_flexcc_s8b8Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXCC_S8B8_LUT_S8B8(LUT_S8B8)                                     (0x00000000U+((LUT_S8B8)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT_S8B8 */

#define CSL_FLEXCC_S8B8_LUT_S8B8_RSVD_1_MASK                                   (0xFF000000U)
#define CSL_FLEXCC_S8B8_LUT_S8B8_RSVD_1_SHIFT                                  (0x00000018U)
#define CSL_FLEXCC_S8B8_LUT_S8B8_RSVD_1_MAX                                    (0x000000FFU)

#define CSL_FLEXCC_S8B8_LUT_S8B8_LUT_1_MASK                                    (0x00FF0000U)
#define CSL_FLEXCC_S8B8_LUT_S8B8_LUT_1_SHIFT                                   (0x00000010U)
#define CSL_FLEXCC_S8B8_LUT_S8B8_LUT_1_MAX                                     (0x000000FFU)

#define CSL_FLEXCC_S8B8_LUT_S8B8_RSVD_0_MASK                                   (0x0000FF00U)
#define CSL_FLEXCC_S8B8_LUT_S8B8_RSVD_0_SHIFT                                  (0x00000008U)
#define CSL_FLEXCC_S8B8_LUT_S8B8_RSVD_0_MAX                                    (0x000000FFU)

#define CSL_FLEXCC_S8B8_LUT_S8B8_LUT_0_MASK                                    (0x000000FFU)
#define CSL_FLEXCC_S8B8_LUT_S8B8_LUT_0_SHIFT                                   (0x00000000U)
#define CSL_FLEXCC_S8B8_LUT_S8B8_LUT_0_MAX                                     (0x000000FFU)

/**************************************************************************
* Hardware Region  : Hist Mem
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t HIST[256];                 /* Hist Mem */
} CSL_flexcc_histRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXCC_HIST_HIST(HIST)                                             (0x00000000U+((HIST)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* HIST */

#define CSL_FLEXCC_HIST_HIST_RSVD_0_MASK                                       (0xFFF00000U)
#define CSL_FLEXCC_HIST_HIST_RSVD_0_SHIFT                                      (0x00000014U)
#define CSL_FLEXCC_HIST_HIST_RSVD_0_MAX                                        (0x00000FFFU)

#define CSL_FLEXCC_HIST_HIST_HIST_VAL_MASK                                     (0x000FFFFFU)
#define CSL_FLEXCC_HIST_HIST_HIST_VAL_SHIFT                                    (0x00000000U)
#define CSL_FLEXCC_HIST_HIST_HIST_VAL_MAX                                      (0x000FFFFFU)

/**************************************************************************
* Hardware Region  : line memory
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LINE_MEM[4096];            /* line memory */
} CSL_flexcc_lineRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXCC_LINE_LINE_MEM(LINE_MEM)                                     (0x00000000U+((LINE_MEM)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LINE_MEM */

#define CSL_FLEXCC_LINE_LINE_MEM_RSVD_1_MASK                                   (0xF0000000U)
#define CSL_FLEXCC_LINE_LINE_MEM_RSVD_1_SHIFT                                  (0x0000001CU)
#define CSL_FLEXCC_LINE_LINE_MEM_RSVD_1_MAX                                    (0x0000000FU)

#define CSL_FLEXCC_LINE_LINE_MEM_LINE_1_MASK                                   (0x0FFF0000U)
#define CSL_FLEXCC_LINE_LINE_MEM_LINE_1_SHIFT                                  (0x00000010U)
#define CSL_FLEXCC_LINE_LINE_MEM_LINE_1_MAX                                    (0x00000FFFU)

#define CSL_FLEXCC_LINE_LINE_MEM_RSVD_0_MASK                                   (0x0000F000U)
#define CSL_FLEXCC_LINE_LINE_MEM_RSVD_0_SHIFT                                  (0x0000000CU)
#define CSL_FLEXCC_LINE_LINE_MEM_RSVD_0_MAX                                    (0x0000000FU)

#define CSL_FLEXCC_LINE_LINE_MEM_LINE_0_MASK                                   (0x00000FFFU)
#define CSL_FLEXCC_LINE_LINE_MEM_LINE_0_SHIFT                                  (0x00000000U)
#define CSL_FLEXCC_LINE_LINE_MEM_LINE_0_MAX                                    (0x00000FFFU)

#ifdef __cplusplus
}
#endif
#endif

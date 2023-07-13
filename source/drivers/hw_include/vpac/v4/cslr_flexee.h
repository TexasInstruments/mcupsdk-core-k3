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
 *  Name        : cslr_flexee.h
*/
#ifndef CSLR_FLEXEE_H_
#define CSLR_FLEXEE_H_

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
    volatile uint32_t EE_CFG_0;                  /* Config_Size */
    volatile uint32_t EE_CFG_1;                  /* EE route config */
    volatile uint32_t EE_ENABLE;                 /* EE Enable */
    volatile uint32_t YEE_SHIFT;                 /* YEE Shift */
    volatile uint32_t YEE_COEF_R0_C0;            /* YEE Coefficient Row 0 Column 0 */
    volatile uint32_t YEE_COEF_R0_C1;            /* YEE Coefficient Row 0 Column 1 */
    volatile uint32_t YEE_COEF_R0_C2;            /* YEE Coefficient Row 0 Column 2 */
    volatile uint8_t  Resv_32[4];
    volatile uint32_t YEE_COEF_R1_C0;            /* YEE Coefficient Row 1 Column 0 */
    volatile uint32_t YEE_COEF_R1_C1;            /* YEE Coefficient Row 1 Column 1 */
    volatile uint32_t YEE_COEF_R1_C2;            /* YEE Coefficient Row 1 Column 2 */
    volatile uint8_t  Resv_48[4];
    volatile uint32_t YEE_COEF_R2_C0;            /* YEE Coefficient Row 2 Column 0 */
    volatile uint32_t YEE_COEF_R2_C1;            /* YEE Coefficient Row 2 Column 1 */
    volatile uint32_t YEE_COEF_R2_C2;            /* YEE Coefficient Row 2 Column 2 */
    volatile uint8_t  Resv_64[4];
    volatile uint32_t YEE_E_THR;                 /* YEE E Thresh */
    volatile uint32_t YEE_MERGESEL;              /* YEE Merge Select */
    volatile uint32_t YES_E_HAL;                 /* YES E Hal */
    volatile uint32_t YES_G_GAIN;                /* YES Gradient Gain */
    volatile uint32_t YES_E_GAIN;                /* YES E Gain */
    volatile uint32_t YES_E_THR1;                /* YES E Thresh 1 */
    volatile uint32_t YES_E_THR2;                /* YES E Thresh 2 */
    volatile uint32_t YES_G_OFT;                 /* YES G Ofset */
    volatile uint8_t  Resv_256[160];
    volatile uint32_t INT_STATUS;                /* Int Status/Clear register */
    volatile uint8_t  Resv_4104[3844];
    volatile uint32_t LINE_SEL;                  /* Line Select */
    volatile uint8_t  Resv_8192[4084];
    volatile uint32_t EELUT_RAM[2048];           /* EELUT RAM */
    volatile uint32_t PIXEL_RAM[2048];           /* Pixel RAM */
} CSL_flexeeRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FLEXEE_EE_CFG_0                                                    (0x00000000U)
#define CSL_FLEXEE_EE_CFG_1                                                    (0x00000004U)
#define CSL_FLEXEE_EE_ENABLE                                                   (0x00000008U)
#define CSL_FLEXEE_YEE_SHIFT                                                   (0x0000000CU)
#define CSL_FLEXEE_YEE_COEF_R0_C0                                              (0x00000010U)
#define CSL_FLEXEE_YEE_COEF_R0_C1                                              (0x00000014U)
#define CSL_FLEXEE_YEE_COEF_R0_C2                                              (0x00000018U)
#define CSL_FLEXEE_YEE_COEF_R1_C0                                              (0x00000020U)
#define CSL_FLEXEE_YEE_COEF_R1_C1                                              (0x00000024U)
#define CSL_FLEXEE_YEE_COEF_R1_C2                                              (0x00000028U)
#define CSL_FLEXEE_YEE_COEF_R2_C0                                              (0x00000030U)
#define CSL_FLEXEE_YEE_COEF_R2_C1                                              (0x00000034U)
#define CSL_FLEXEE_YEE_COEF_R2_C2                                              (0x00000038U)
#define CSL_FLEXEE_YEE_E_THR                                                   (0x00000040U)
#define CSL_FLEXEE_YEE_MERGESEL                                                (0x00000044U)
#define CSL_FLEXEE_YES_E_HAL                                                   (0x00000048U)
#define CSL_FLEXEE_YES_G_GAIN                                                  (0x0000004CU)
#define CSL_FLEXEE_YES_E_GAIN                                                  (0x00000050U)
#define CSL_FLEXEE_YES_E_THR1                                                  (0x00000054U)
#define CSL_FLEXEE_YES_E_THR2                                                  (0x00000058U)
#define CSL_FLEXEE_YES_G_OFT                                                   (0x0000005CU)
#define CSL_FLEXEE_INT_STATUS                                                  (0x00000100U)
#define CSL_FLEXEE_LINE_SEL                                                    (0x00001008U)
#define CSL_FLEXEE_EELUT_RAM(EELUT_RAM)                                        (0x00002000U+((EELUT_RAM)*0x4U))
#define CSL_FLEXEE_PIXEL_RAM(PIXEL_RAM)                                        (0x00004000U+((PIXEL_RAM)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* EE_CFG_0 */

#define CSL_FLEXEE_EE_CFG_0_HEIGHT_MASK                                        (0x1FFF0000U)
#define CSL_FLEXEE_EE_CFG_0_HEIGHT_SHIFT                                       (0x00000010U)
#define CSL_FLEXEE_EE_CFG_0_HEIGHT_MAX                                         (0x00001FFFU)

#define CSL_FLEXEE_EE_CFG_0_WIDTH_MASK                                         (0x00001FFFU)
#define CSL_FLEXEE_EE_CFG_0_WIDTH_SHIFT                                        (0x00000000U)
#define CSL_FLEXEE_EE_CFG_0_WIDTH_MAX                                          (0x00001FFFU)

/* EE_CFG_1 */

#define CSL_FLEXEE_EE_CFG_1_YUV12_CL_ALIGN_MASK                                (0x10000000U)
#define CSL_FLEXEE_EE_CFG_1_YUV12_CL_ALIGN_SHIFT                               (0x0000001CU)
#define CSL_FLEXEE_EE_CFG_1_YUV12_CL_ALIGN_MAX                                 (0x00000001U)

#define CSL_FLEXEE_EE_CFG_1_YUV8_CL_ALIGN_MASK                                 (0x01000000U)
#define CSL_FLEXEE_EE_CFG_1_YUV8_CL_ALIGN_SHIFT                                (0x00000018U)
#define CSL_FLEXEE_EE_CFG_1_YUV8_CL_ALIGN_MAX                                  (0x00000001U)

#define CSL_FLEXEE_EE_CFG_1_EE_FE_MUX_SEL_MASK                                 (0x00400000U)
#define CSL_FLEXEE_EE_CFG_1_EE_FE_MUX_SEL_SHIFT                                (0x00000016U)
#define CSL_FLEXEE_EE_CFG_1_EE_FE_MUX_SEL_MAX                                  (0x00000001U)

#define CSL_FLEXEE_EE_CFG_1_SHIFTLEFT_NUM_MASK                                 (0x000C0000U)
#define CSL_FLEXEE_EE_CFG_1_SHIFTLEFT_NUM_SHIFT                                (0x00000012U)
#define CSL_FLEXEE_EE_CFG_1_SHIFTLEFT_NUM_MAX                                  (0x00000003U)

#define CSL_FLEXEE_EE_CFG_1_SHIFTRIGHT_NUM_MASK                                (0x00030000U)
#define CSL_FLEXEE_EE_CFG_1_SHIFTRIGHT_NUM_SHIFT                               (0x00000010U)
#define CSL_FLEXEE_EE_CFG_1_SHIFTRIGHT_NUM_MAX                                 (0x00000003U)

#define CSL_FLEXEE_EE_CFG_1_LLSE12_MUX_SEL_MASK                                (0x00001000U)
#define CSL_FLEXEE_EE_CFG_1_LLSE12_MUX_SEL_SHIFT                               (0x0000000CU)
#define CSL_FLEXEE_EE_CFG_1_LLSE12_MUX_SEL_MAX                                 (0x00000001U)

#define CSL_FLEXEE_EE_CFG_1_CLSE12_MUX_SEL_MASK                                (0x00000100U)
#define CSL_FLEXEE_EE_CFG_1_CLSE12_MUX_SEL_SHIFT                               (0x00000008U)
#define CSL_FLEXEE_EE_CFG_1_CLSE12_MUX_SEL_MAX                                 (0x00000001U)

#define CSL_FLEXEE_EE_CFG_1_LLSE8_MUX_SEL_MASK                                 (0x00000010U)
#define CSL_FLEXEE_EE_CFG_1_LLSE8_MUX_SEL_SHIFT                                (0x00000004U)
#define CSL_FLEXEE_EE_CFG_1_LLSE8_MUX_SEL_MAX                                  (0x00000001U)

#define CSL_FLEXEE_EE_CFG_1_CLSE8_MUX_SEL_MASK                                 (0x00000001U)
#define CSL_FLEXEE_EE_CFG_1_CLSE8_MUX_SEL_SHIFT                                (0x00000000U)
#define CSL_FLEXEE_EE_CFG_1_CLSE8_MUX_SEL_MAX                                  (0x00000001U)

/* EE_ENABLE */

#define CSL_FLEXEE_EE_ENABLE_YEE_ENABLE_MASK                                   (0x00000001U)
#define CSL_FLEXEE_EE_ENABLE_YEE_ENABLE_SHIFT                                  (0x00000000U)
#define CSL_FLEXEE_EE_ENABLE_YEE_ENABLE_MAX                                    (0x00000001U)

/* YEE_SHIFT */

#define CSL_FLEXEE_YEE_SHIFT_YEE_SHIFT_MASK                                    (0x0000003FU)
#define CSL_FLEXEE_YEE_SHIFT_YEE_SHIFT_SHIFT                                   (0x00000000U)
#define CSL_FLEXEE_YEE_SHIFT_YEE_SHIFT_MAX                                     (0x0000003FU)

/* YEE_COEF_R0_C0 */

#define CSL_FLEXEE_YEE_COEF_R0_C0_YEE_COEF_R0_C0_MASK                          (0x000003FFU)
#define CSL_FLEXEE_YEE_COEF_R0_C0_YEE_COEF_R0_C0_SHIFT                         (0x00000000U)
#define CSL_FLEXEE_YEE_COEF_R0_C0_YEE_COEF_R0_C0_MAX                           (0x000003FFU)

/* YEE_COEF_R0_C1 */

#define CSL_FLEXEE_YEE_COEF_R0_C1_YEE_COEF_R0_C1_MASK                          (0x000003FFU)
#define CSL_FLEXEE_YEE_COEF_R0_C1_YEE_COEF_R0_C1_SHIFT                         (0x00000000U)
#define CSL_FLEXEE_YEE_COEF_R0_C1_YEE_COEF_R0_C1_MAX                           (0x000003FFU)

/* YEE_COEF_R0_C2 */

#define CSL_FLEXEE_YEE_COEF_R0_C2_YEE_COEF_R0_C2_MASK                          (0x000003FFU)
#define CSL_FLEXEE_YEE_COEF_R0_C2_YEE_COEF_R0_C2_SHIFT                         (0x00000000U)
#define CSL_FLEXEE_YEE_COEF_R0_C2_YEE_COEF_R0_C2_MAX                           (0x000003FFU)

/* YEE_COEF_R1_C0 */

#define CSL_FLEXEE_YEE_COEF_R1_C0_YEE_COEF_R1_C0_MASK                          (0x000003FFU)
#define CSL_FLEXEE_YEE_COEF_R1_C0_YEE_COEF_R1_C0_SHIFT                         (0x00000000U)
#define CSL_FLEXEE_YEE_COEF_R1_C0_YEE_COEF_R1_C0_MAX                           (0x000003FFU)

/* YEE_COEF_R1_C1 */

#define CSL_FLEXEE_YEE_COEF_R1_C1_YEE_COEF_R1_C1_MASK                          (0x000003FFU)
#define CSL_FLEXEE_YEE_COEF_R1_C1_YEE_COEF_R1_C1_SHIFT                         (0x00000000U)
#define CSL_FLEXEE_YEE_COEF_R1_C1_YEE_COEF_R1_C1_MAX                           (0x000003FFU)

/* YEE_COEF_R1_C2 */

#define CSL_FLEXEE_YEE_COEF_R1_C2_YEE_COEF_R1_C2_MASK                          (0x000003FFU)
#define CSL_FLEXEE_YEE_COEF_R1_C2_YEE_COEF_R1_C2_SHIFT                         (0x00000000U)
#define CSL_FLEXEE_YEE_COEF_R1_C2_YEE_COEF_R1_C2_MAX                           (0x000003FFU)

/* YEE_COEF_R2_C0 */

#define CSL_FLEXEE_YEE_COEF_R2_C0_YEE_COEF_R2_C0_MASK                          (0x000003FFU)
#define CSL_FLEXEE_YEE_COEF_R2_C0_YEE_COEF_R2_C0_SHIFT                         (0x00000000U)
#define CSL_FLEXEE_YEE_COEF_R2_C0_YEE_COEF_R2_C0_MAX                           (0x000003FFU)

/* YEE_COEF_R2_C1 */

#define CSL_FLEXEE_YEE_COEF_R2_C1_YEE_COEF_R2_C1_MASK                          (0x000003FFU)
#define CSL_FLEXEE_YEE_COEF_R2_C1_YEE_COEF_R2_C1_SHIFT                         (0x00000000U)
#define CSL_FLEXEE_YEE_COEF_R2_C1_YEE_COEF_R2_C1_MAX                           (0x000003FFU)

/* YEE_COEF_R2_C2 */

#define CSL_FLEXEE_YEE_COEF_R2_C2_YEE_COEF_R2_C2_MASK                          (0x000003FFU)
#define CSL_FLEXEE_YEE_COEF_R2_C2_YEE_COEF_R2_C2_SHIFT                         (0x00000000U)
#define CSL_FLEXEE_YEE_COEF_R2_C2_YEE_COEF_R2_C2_MAX                           (0x000003FFU)

/* YEE_E_THR */

#define CSL_FLEXEE_YEE_E_THR_YEE_E_THR_MASK                                    (0x000003FFU)
#define CSL_FLEXEE_YEE_E_THR_YEE_E_THR_SHIFT                                   (0x00000000U)
#define CSL_FLEXEE_YEE_E_THR_YEE_E_THR_MAX                                     (0x000003FFU)

/* YEE_MERGESEL */

#define CSL_FLEXEE_YEE_MERGESEL_YEE_MERGESEL_MASK                              (0x00000001U)
#define CSL_FLEXEE_YEE_MERGESEL_YEE_MERGESEL_SHIFT                             (0x00000000U)
#define CSL_FLEXEE_YEE_MERGESEL_YEE_MERGESEL_MAX                               (0x00000001U)

/* YES_E_HAL */

#define CSL_FLEXEE_YES_E_HAL_YES_E_HAL_MASK                                    (0x00000001U)
#define CSL_FLEXEE_YES_E_HAL_YES_E_HAL_SHIFT                                   (0x00000000U)
#define CSL_FLEXEE_YES_E_HAL_YES_E_HAL_MAX                                     (0x00000001U)

/* YES_G_GAIN */

#define CSL_FLEXEE_YES_G_GAIN_YES_G_GAIN_MASK                                  (0x000000FFU)
#define CSL_FLEXEE_YES_G_GAIN_YES_G_GAIN_SHIFT                                 (0x00000000U)
#define CSL_FLEXEE_YES_G_GAIN_YES_G_GAIN_MAX                                   (0x000000FFU)

/* YES_E_GAIN */

#define CSL_FLEXEE_YES_E_GAIN_YES_E_GAIN_MASK                                  (0x00000FFFU)
#define CSL_FLEXEE_YES_E_GAIN_YES_E_GAIN_SHIFT                                 (0x00000000U)
#define CSL_FLEXEE_YES_E_GAIN_YES_E_GAIN_MAX                                   (0x00000FFFU)

/* YES_E_THR1 */

#define CSL_FLEXEE_YES_E_THR1_YES_E_THR1_MASK                                  (0x0000FFFFU)
#define CSL_FLEXEE_YES_E_THR1_YES_E_THR1_SHIFT                                 (0x00000000U)
#define CSL_FLEXEE_YES_E_THR1_YES_E_THR1_MAX                                   (0x0000FFFFU)

/* YES_E_THR2 */

#define CSL_FLEXEE_YES_E_THR2_YES_E_THR2_MASK                                  (0x000003FFU)
#define CSL_FLEXEE_YES_E_THR2_YES_E_THR2_SHIFT                                 (0x00000000U)
#define CSL_FLEXEE_YES_E_THR2_YES_E_THR2_MAX                                   (0x000003FFU)

/* YES_G_OFT */

#define CSL_FLEXEE_YES_G_OFT_YES_G_OFT_MASK                                    (0x000003FFU)
#define CSL_FLEXEE_YES_G_OFT_YES_G_OFT_SHIFT                                   (0x00000000U)
#define CSL_FLEXEE_YES_G_OFT_YES_G_OFT_MAX                                     (0x000003FFU)

/* INT_STATUS */

#define CSL_FLEXEE_INT_STATUS_EE_HZ_ALIGN8_MASK                                (0x00000008U)
#define CSL_FLEXEE_INT_STATUS_EE_HZ_ALIGN8_SHIFT                               (0x00000003U)
#define CSL_FLEXEE_INT_STATUS_EE_HZ_ALIGN8_MAX                                 (0x00000001U)

#define CSL_FLEXEE_INT_STATUS_EE_HZ_ALIGN12_MASK                               (0x00000004U)
#define CSL_FLEXEE_INT_STATUS_EE_HZ_ALIGN12_SHIFT                              (0x00000002U)
#define CSL_FLEXEE_INT_STATUS_EE_HZ_ALIGN12_MAX                                (0x00000001U)

#define CSL_FLEXEE_INT_STATUS_EE_PIX_ERR_MASK                                  (0x00000002U)
#define CSL_FLEXEE_INT_STATUS_EE_PIX_ERR_SHIFT                                 (0x00000001U)
#define CSL_FLEXEE_INT_STATUS_EE_PIX_ERR_MAX                                   (0x00000001U)

#define CSL_FLEXEE_INT_STATUS_EELUT_CFG_ERR_MASK                               (0x00000001U)
#define CSL_FLEXEE_INT_STATUS_EELUT_CFG_ERR_SHIFT                              (0x00000000U)
#define CSL_FLEXEE_INT_STATUS_EELUT_CFG_ERR_MAX                                (0x00000001U)

/* LINE_SEL */

#define CSL_FLEXEE_LINE_SEL_LINE_SELECTOR_MASK                                 (0x00000007U)
#define CSL_FLEXEE_LINE_SEL_LINE_SELECTOR_SHIFT                                (0x00000000U)
#define CSL_FLEXEE_LINE_SEL_LINE_SELECTOR_MAX                                  (0x00000007U)

/* EELUT_RAM */

#define CSL_FLEXEE_EELUT_RAM_EELUT_ENTRY_LO_MASK                               (0x00001FFFU)
#define CSL_FLEXEE_EELUT_RAM_EELUT_ENTRY_LO_SHIFT                              (0x00000000U)
#define CSL_FLEXEE_EELUT_RAM_EELUT_ENTRY_LO_MAX                                (0x00001FFFU)

#define CSL_FLEXEE_EELUT_RAM_EELUT_ENTRY_HI_MASK                               (0x1FFF0000U)
#define CSL_FLEXEE_EELUT_RAM_EELUT_ENTRY_HI_SHIFT                              (0x00000010U)
#define CSL_FLEXEE_EELUT_RAM_EELUT_ENTRY_HI_MAX                                (0x00001FFFU)

/* PIXEL_RAM */

#define CSL_FLEXEE_PIXEL_RAM_PIXEL_LO_MASK                                     (0x00000FFFU)
#define CSL_FLEXEE_PIXEL_RAM_PIXEL_LO_SHIFT                                    (0x00000000U)
#define CSL_FLEXEE_PIXEL_RAM_PIXEL_LO_MAX                                      (0x00000FFFU)

#define CSL_FLEXEE_PIXEL_RAM_PIXEL_HI_MASK                                     (0x0FFF0000U)
#define CSL_FLEXEE_PIXEL_RAM_PIXEL_HI_SHIFT                                    (0x00000010U)
#define CSL_FLEXEE_PIXEL_RAM_PIXEL_HI_MAX                                      (0x00000FFFU)

#ifdef __cplusplus
}
#endif
#endif

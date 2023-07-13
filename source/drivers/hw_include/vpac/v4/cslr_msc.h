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
 *  Name        : cslr_msc.h
*/
#ifndef CSLR_MSC_H_
#define CSLR_MSC_H_

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
    volatile uint32_t CFG;                       /* FILT[a]_CFG */
    volatile uint32_t SRC_ROI;                   /* FILT[a]_SRC_ROI */
    volatile uint32_t OUT_SIZE;                  /* FILT[a]_OUT_SIZE */
    volatile uint32_t FIRINC;                    /* FILT[a]_FIRINC */
    volatile uint32_t ACC_INIT;                  /* FILT[a]_ACC_INIT */
    volatile uint8_t  Resv_32[12];
} CSL_mscRegs_filt;


typedef struct {
    volatile uint32_t C210;                      /* COEF_SP[a]_C210 */
    volatile uint32_t C43;                       /* COEF_SP[a]_C43 */
} CSL_mscRegs_coef_sp;


typedef struct {
    volatile uint32_t C210;                      /* COEF_MP[a]_PH[b]_C210 */
    volatile uint32_t C43;                       /* COEF_MP[a]_PH[b]_C43 */
} CSL_mscRegs_coef_mp_ph;


typedef struct {
    CSL_mscRegs_coef_mp_ph PH[32];
} CSL_mscRegs_coef_mp;


typedef struct {
    volatile uint32_t REVISION;                  /* revision */
    volatile uint32_t CONTROL;                   /* control */
    volatile uint8_t  Resv_16[8];
    CSL_mscRegs_filt FILT[10];
    volatile uint8_t  Resv_384[48];
    CSL_mscRegs_coef_sp COEF_SP[2];
    volatile uint8_t  Resv_512[112];
    CSL_mscRegs_coef_mp COEF_MP[4];
} CSL_mscRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MSC_REVISION                                                       (0x00000000U)
#define CSL_MSC_CONTROL                                                        (0x00000004U)
#define CSL_MSC_FILT_CFG(FILT)                                                 (0x00000010U+((FILT)*0x20U))
#define CSL_MSC_FILT_SRC_ROI(FILT)                                             (0x00000014U+((FILT)*0x20U))
#define CSL_MSC_FILT_OUT_SIZE(FILT)                                            (0x00000018U+((FILT)*0x20U))
#define CSL_MSC_FILT_FIRINC(FILT)                                              (0x0000001CU+((FILT)*0x20U))
#define CSL_MSC_FILT_ACC_INIT(FILT)                                            (0x00000020U+((FILT)*0x20U))
#define CSL_MSC_COEF_SP_C210(COEF_SP)                                          (0x00000180U+((COEF_SP)*0x8U))
#define CSL_MSC_COEF_SP_C43(COEF_SP)                                           (0x00000184U+((COEF_SP)*0x8U))
#define CSL_MSC_COEF_MP_PH_C210(COEF_MP, PH)                                   (0x00000200U+((COEF_MP)*0x100U)+((PH)*0x8U))
#define CSL_MSC_COEF_MP_PH_C43(COEF_MP, PH)                                    (0x00000204U+((COEF_MP)*0x100U)+((PH)*0x8U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CFG */

#define CSL_MSC_FILT_CFG_SIGNED_DATA_MASK                                      (0x00400000U)
#define CSL_MSC_FILT_CFG_SIGNED_DATA_SHIFT                                     (0x00000016U)
#define CSL_MSC_FILT_CFG_SIGNED_DATA_MAX                                       (0x00000001U)

#define CSL_MSC_FILT_CFG_COEF_SHIFT_MASK                                       (0x003C0000U)
#define CSL_MSC_FILT_CFG_COEF_SHIFT_SHIFT                                      (0x00000012U)
#define CSL_MSC_FILT_CFG_COEF_SHIFT_MAX                                        (0x0000000FU)

#define CSL_MSC_FILT_CFG_UV_MODE_MASK                                          (0x00020000U)
#define CSL_MSC_FILT_CFG_UV_MODE_SHIFT                                         (0x00000011U)
#define CSL_MSC_FILT_CFG_UV_MODE_MAX                                           (0x00000001U)

#define CSL_MSC_FILT_CFG_SAT_MODE_MASK                                         (0x00010000U)
#define CSL_MSC_FILT_CFG_SAT_MODE_SHIFT                                        (0x00000010U)
#define CSL_MSC_FILT_CFG_SAT_MODE_MAX                                          (0x00000001U)

#define CSL_MSC_FILT_CFG_SP_VS_COEF_SEL_MASK                                   (0x0000F000U)
#define CSL_MSC_FILT_CFG_SP_VS_COEF_SEL_SHIFT                                  (0x0000000CU)
#define CSL_MSC_FILT_CFG_SP_VS_COEF_SEL_MAX                                    (0x0000000FU)

#define CSL_MSC_FILT_CFG_SP_VS_COEF_SRC_MASK                                   (0x00000800U)
#define CSL_MSC_FILT_CFG_SP_VS_COEF_SRC_SHIFT                                  (0x0000000BU)
#define CSL_MSC_FILT_CFG_SP_VS_COEF_SRC_MAX                                    (0x00000001U)

#define CSL_MSC_FILT_CFG_SP_HS_COEF_SEL_MASK                                   (0x00000780U)
#define CSL_MSC_FILT_CFG_SP_HS_COEF_SEL_SHIFT                                  (0x00000007U)
#define CSL_MSC_FILT_CFG_SP_HS_COEF_SEL_MAX                                    (0x0000000FU)

#define CSL_MSC_FILT_CFG_SP_HS_COEF_SRC_MASK                                   (0x00000040U)
#define CSL_MSC_FILT_CFG_SP_HS_COEF_SRC_SHIFT                                  (0x00000006U)
#define CSL_MSC_FILT_CFG_SP_HS_COEF_SRC_MAX                                    (0x00000001U)

#define CSL_MSC_FILT_CFG_VS_COEF_SEL_MASK                                      (0x00000030U)
#define CSL_MSC_FILT_CFG_VS_COEF_SEL_SHIFT                                     (0x00000004U)
#define CSL_MSC_FILT_CFG_VS_COEF_SEL_MAX                                       (0x00000003U)

#define CSL_MSC_FILT_CFG_HS_COEF_SEL_MASK                                      (0x0000000CU)
#define CSL_MSC_FILT_CFG_HS_COEF_SEL_SHIFT                                     (0x00000002U)
#define CSL_MSC_FILT_CFG_HS_COEF_SEL_MAX                                       (0x00000003U)

#define CSL_MSC_FILT_CFG_PHASE_MODE_MASK                                       (0x00000002U)
#define CSL_MSC_FILT_CFG_PHASE_MODE_SHIFT                                      (0x00000001U)
#define CSL_MSC_FILT_CFG_PHASE_MODE_MAX                                        (0x00000001U)

#define CSL_MSC_FILT_CFG_FILTER_MODE_MASK                                      (0x00000001U)
#define CSL_MSC_FILT_CFG_FILTER_MODE_SHIFT                                     (0x00000000U)
#define CSL_MSC_FILT_CFG_FILTER_MODE_MAX                                       (0x00000001U)

/* SRC_ROI */

#define CSL_MSC_FILT_SRC_ROI_Y_OFFSET_MASK                                     (0x1FFF0000U)
#define CSL_MSC_FILT_SRC_ROI_Y_OFFSET_SHIFT                                    (0x00000010U)
#define CSL_MSC_FILT_SRC_ROI_Y_OFFSET_MAX                                      (0x00001FFFU)

#define CSL_MSC_FILT_SRC_ROI_X_OFFSET_MASK                                     (0x00001FFFU)
#define CSL_MSC_FILT_SRC_ROI_X_OFFSET_SHIFT                                    (0x00000000U)
#define CSL_MSC_FILT_SRC_ROI_X_OFFSET_MAX                                      (0x00001FFFU)

/* OUT_SIZE */

#define CSL_MSC_FILT_OUT_SIZE_HEIGHT_MASK                                      (0x1FFF0000U)
#define CSL_MSC_FILT_OUT_SIZE_HEIGHT_SHIFT                                     (0x00000010U)
#define CSL_MSC_FILT_OUT_SIZE_HEIGHT_MAX                                       (0x00001FFFU)

#define CSL_MSC_FILT_OUT_SIZE_WIDTH_MASK                                       (0x00001FFFU)
#define CSL_MSC_FILT_OUT_SIZE_WIDTH_SHIFT                                      (0x00000000U)
#define CSL_MSC_FILT_OUT_SIZE_WIDTH_MAX                                        (0x00001FFFU)

/* FIRINC */

#define CSL_MSC_FILT_FIRINC_VS_MASK                                            (0x7FFF0000U)
#define CSL_MSC_FILT_FIRINC_VS_SHIFT                                           (0x00000010U)
#define CSL_MSC_FILT_FIRINC_VS_MAX                                             (0x00007FFFU)

#define CSL_MSC_FILT_FIRINC_HS_MASK                                            (0x00007FFFU)
#define CSL_MSC_FILT_FIRINC_HS_SHIFT                                           (0x00000000U)
#define CSL_MSC_FILT_FIRINC_HS_MAX                                             (0x00007FFFU)

/* ACC_INIT */

#define CSL_MSC_FILT_ACC_INIT_VS_MASK                                          (0x0FFF0000U)
#define CSL_MSC_FILT_ACC_INIT_VS_SHIFT                                         (0x00000010U)
#define CSL_MSC_FILT_ACC_INIT_VS_MAX                                           (0x00000FFFU)

#define CSL_MSC_FILT_ACC_INIT_HS_MASK                                          (0x00000FFFU)
#define CSL_MSC_FILT_ACC_INIT_HS_SHIFT                                         (0x00000000U)
#define CSL_MSC_FILT_ACC_INIT_HS_MAX                                           (0x00000FFFU)

/* C210 */

#define CSL_MSC_COEF_SP_C210_FIR_C2_MASK                                       (0x3FF00000U)
#define CSL_MSC_COEF_SP_C210_FIR_C2_SHIFT                                      (0x00000014U)
#define CSL_MSC_COEF_SP_C210_FIR_C2_MAX                                        (0x000003FFU)

#define CSL_MSC_COEF_SP_C210_FIR_C1_MASK                                       (0x000FFC00U)
#define CSL_MSC_COEF_SP_C210_FIR_C1_SHIFT                                      (0x0000000AU)
#define CSL_MSC_COEF_SP_C210_FIR_C1_MAX                                        (0x000003FFU)

#define CSL_MSC_COEF_SP_C210_FIR_C0_MASK                                       (0x000003FFU)
#define CSL_MSC_COEF_SP_C210_FIR_C0_SHIFT                                      (0x00000000U)
#define CSL_MSC_COEF_SP_C210_FIR_C0_MAX                                        (0x000003FFU)

/* C43 */

#define CSL_MSC_COEF_SP_C43_FIR_C4_MASK                                        (0x000FFC00U)
#define CSL_MSC_COEF_SP_C43_FIR_C4_SHIFT                                       (0x0000000AU)
#define CSL_MSC_COEF_SP_C43_FIR_C4_MAX                                         (0x000003FFU)

#define CSL_MSC_COEF_SP_C43_FIR_C3_MASK                                        (0x000003FFU)
#define CSL_MSC_COEF_SP_C43_FIR_C3_SHIFT                                       (0x00000000U)
#define CSL_MSC_COEF_SP_C43_FIR_C3_MAX                                         (0x000003FFU)

/* C210 */

#define CSL_MSC_COEF_MP_PH_C210_FIR_C2_MASK                                    (0x3FF00000U)
#define CSL_MSC_COEF_MP_PH_C210_FIR_C2_SHIFT                                   (0x00000014U)
#define CSL_MSC_COEF_MP_PH_C210_FIR_C2_MAX                                     (0x000003FFU)

#define CSL_MSC_COEF_MP_PH_C210_FIR_C1_MASK                                    (0x000FFC00U)
#define CSL_MSC_COEF_MP_PH_C210_FIR_C1_SHIFT                                   (0x0000000AU)
#define CSL_MSC_COEF_MP_PH_C210_FIR_C1_MAX                                     (0x000003FFU)

#define CSL_MSC_COEF_MP_PH_C210_FIR_C0_MASK                                    (0x000003FFU)
#define CSL_MSC_COEF_MP_PH_C210_FIR_C0_SHIFT                                   (0x00000000U)
#define CSL_MSC_COEF_MP_PH_C210_FIR_C0_MAX                                     (0x000003FFU)

/* C43 */

#define CSL_MSC_COEF_MP_PH_C43_FIR_C4_MASK                                     (0x000FFC00U)
#define CSL_MSC_COEF_MP_PH_C43_FIR_C4_SHIFT                                    (0x0000000AU)
#define CSL_MSC_COEF_MP_PH_C43_FIR_C4_MAX                                      (0x000003FFU)

#define CSL_MSC_COEF_MP_PH_C43_FIR_C3_MASK                                     (0x000003FFU)
#define CSL_MSC_COEF_MP_PH_C43_FIR_C3_SHIFT                                    (0x00000000U)
#define CSL_MSC_COEF_MP_PH_C43_FIR_C3_MAX                                      (0x000003FFU)

/* REVISION */

#define CSL_MSC_REVISION_SCHEME_MASK                                           (0xC0000000U)
#define CSL_MSC_REVISION_SCHEME_SHIFT                                          (0x0000001EU)
#define CSL_MSC_REVISION_SCHEME_MAX                                            (0x00000003U)

#define CSL_MSC_REVISION_BU_MASK                                               (0x30000000U)
#define CSL_MSC_REVISION_BU_SHIFT                                              (0x0000001CU)
#define CSL_MSC_REVISION_BU_MAX                                                (0x00000003U)

#define CSL_MSC_REVISION_FUNC_MASK                                             (0x0FFF0000U)
#define CSL_MSC_REVISION_FUNC_SHIFT                                            (0x00000010U)
#define CSL_MSC_REVISION_FUNC_MAX                                              (0x00000FFFU)

#define CSL_MSC_REVISION_RTL_MASK                                              (0x0000F800U)
#define CSL_MSC_REVISION_RTL_SHIFT                                             (0x0000000BU)
#define CSL_MSC_REVISION_RTL_MAX                                               (0x0000001FU)

#define CSL_MSC_REVISION_MAJOR_MASK                                            (0x00000700U)
#define CSL_MSC_REVISION_MAJOR_SHIFT                                           (0x00000008U)
#define CSL_MSC_REVISION_MAJOR_MAX                                             (0x00000007U)

#define CSL_MSC_REVISION_CUSTOM_MASK                                           (0x000000C0U)
#define CSL_MSC_REVISION_CUSTOM_SHIFT                                          (0x00000006U)
#define CSL_MSC_REVISION_CUSTOM_MAX                                            (0x00000003U)

#define CSL_MSC_REVISION_MINOR_MASK                                            (0x0000003FU)
#define CSL_MSC_REVISION_MINOR_SHIFT                                           (0x00000000U)
#define CSL_MSC_REVISION_MINOR_MAX                                             (0x0000003FU)

/* CONTROL */

#define CSL_MSC_CONTROL_MSC_ENABLE_MASK                                        (0x00000001U)
#define CSL_MSC_CONTROL_MSC_ENABLE_SHIFT                                       (0x00000000U)
#define CSL_MSC_CONTROL_MSC_ENABLE_MAX                                         (0x00000001U)

#ifdef __cplusplus
}
#endif
#endif

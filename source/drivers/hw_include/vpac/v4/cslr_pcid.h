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
 *  Name        : cslr_pcid.h
*/
#ifndef CSLR_PCID_H_
#define CSLR_PCID_H_

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
    volatile uint8_t  Resv_4[4];
    volatile uint32_t CTRL;                      /* PCID Control Register */
    volatile uint32_t FRAMESZ;                   /* Frame Size Register */
    volatile uint32_t RBIRINTPCFG1;              /* Threshold Configuration for R/B/Ir interpoaltion processing */
    volatile uint32_t RBIRINTPCFG2;              /* Threshold Configuration for R/B/Ir interpoaltion processing */
    volatile uint32_t RBIRCOLORDIFFCFG;          /* Color difference interpolation configuration parameters */
    volatile uint32_t IRSUBCFG1;                 /* IR Subtraction Configuration Register1 */
    volatile uint32_t IRSUBCFG2;                 /* IR Subtraction Configuration1 Register2 */
    volatile uint32_t IRSUBDISTSCALELUT0;        /* City Block Distance based IR Subtraction Scale factor LUT */
    volatile uint32_t IRSUBDISTSCALELUT1;        /* Distance based IR Subtraction Scale factor LUT */
    volatile uint32_t IRSUBDISTSCALELUT2;        /* Distance based IR Subtraction Scale factor LUT */
    volatile uint32_t IRSUBSCALE0;               /* IR Subtraction Factor post Factor Filter */
    volatile uint32_t IRSUBSCALE1;               /* IR Subtraction Factor post Factor Filter */
    volatile uint8_t  Resv_128[76];
    volatile uint32_t INT_STAT;                  /* PCID Interrupt status */
    volatile uint8_t  Resv_256[124];
    volatile uint32_t DBG_CTL;                   /* PCID Debug Status Register  */
    volatile uint32_t DBG_STAT;                  /* PCID Debug event status */
} CSL_pcidRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_PCID_CTRL                                                          (0x00000004U)
#define CSL_PCID_FRAMESZ                                                       (0x00000008U)
#define CSL_PCID_RBIRINTPCFG1                                                  (0x0000000CU)
#define CSL_PCID_RBIRINTPCFG2                                                  (0x00000010U)
#define CSL_PCID_RBIRCOLORDIFFCFG                                              (0x00000014U)
#define CSL_PCID_IRSUBCFG1                                                     (0x00000018U)
#define CSL_PCID_IRSUBCFG2                                                     (0x0000001CU)
#define CSL_PCID_IRSUBDISTSCALELUT0                                            (0x00000020U)
#define CSL_PCID_IRSUBDISTSCALELUT1                                            (0x00000024U)
#define CSL_PCID_IRSUBDISTSCALELUT2                                            (0x00000028U)
#define CSL_PCID_IRSUBSCALE0                                                   (0x0000002CU)
#define CSL_PCID_IRSUBSCALE1                                                   (0x00000030U)
#define CSL_PCID_INT_STAT                                                      (0x00000080U)
#define CSL_PCID_DBG_CTL                                                       (0x00000100U)
#define CSL_PCID_DBG_STAT                                                      (0x00000104U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CTRL */

#define CSL_PCID_CTRL_BAYEROUTEN_MASK                                          (0x00000001U)
#define CSL_PCID_CTRL_BAYEROUTEN_SHIFT                                         (0x00000000U)
#define CSL_PCID_CTRL_BAYEROUTEN_MAX                                           (0x00000001U)

#define CSL_PCID_CTRL_IROUTEN_MASK                                             (0x00000002U)
#define CSL_PCID_CTRL_IROUTEN_SHIFT                                            (0x00000001U)
#define CSL_PCID_CTRL_IROUTEN_MAX                                              (0x00000001U)

#define CSL_PCID_CTRL_RBIRINTPMETHOD_MASK                                      (0x00000004U)
#define CSL_PCID_CTRL_RBIRINTPMETHOD_SHIFT                                     (0x00000002U)
#define CSL_PCID_CTRL_RBIRINTPMETHOD_MAX                                       (0x00000001U)

#define CSL_PCID_CTRL_RBINTPATIR_MASK                                          (0x00000008U)
#define CSL_PCID_CTRL_RBINTPATIR_SHIFT                                         (0x00000003U)
#define CSL_PCID_CTRL_RBINTPATIR_MAX                                           (0x00000001U)

#define CSL_PCID_CTRL_IRSUBTRACTEN_MASK                                        (0x00000010U)
#define CSL_PCID_CTRL_IRSUBTRACTEN_SHIFT                                       (0x00000004U)
#define CSL_PCID_CTRL_IRSUBTRACTEN_MAX                                         (0x00000001U)

#define CSL_PCID_CTRL_IRSUBTRACTFILTEN_MASK                                    (0x00000020U)
#define CSL_PCID_CTRL_IRSUBTRACTFILTEN_SHIFT                                   (0x00000005U)
#define CSL_PCID_CTRL_IRSUBTRACTFILTEN_MAX                                     (0x00000001U)

#define CSL_PCID_CTRL_BAYEROUTSEL_MASK                                         (0x00000040U)
#define CSL_PCID_CTRL_BAYEROUTSEL_SHIFT                                        (0x00000006U)
#define CSL_PCID_CTRL_BAYEROUTSEL_MAX                                          (0x00000001U)

#define CSL_PCID_CTRL_IRREMAPLUTEN_MASK                                        (0x00000100U)
#define CSL_PCID_CTRL_IRREMAPLUTEN_SHIFT                                       (0x00000008U)
#define CSL_PCID_CTRL_IRREMAPLUTEN_MAX                                         (0x00000001U)

#define CSL_PCID_CTRL_CFAFORMAT_MASK                                           (0x00007000U)
#define CSL_PCID_CTRL_CFAFORMAT_SHIFT                                          (0x0000000CU)
#define CSL_PCID_CTRL_CFAFORMAT_MAX                                            (0x00000007U)

/* FRAMESZ */

#define CSL_PCID_FRAMESZ_WIDTH_MASK                                            (0x00001FFFU)
#define CSL_PCID_FRAMESZ_WIDTH_SHIFT                                           (0x00000000U)
#define CSL_PCID_FRAMESZ_WIDTH_MAX                                             (0x00001FFFU)

#define CSL_PCID_FRAMESZ_HEIGHT_MASK                                           (0x1FFF0000U)
#define CSL_PCID_FRAMESZ_HEIGHT_SHIFT                                          (0x00000010U)
#define CSL_PCID_FRAMESZ_HEIGHT_MAX                                            (0x00001FFFU)

/* RBIRINTPCFG1 */

#define CSL_PCID_RBIRINTPCFG1_T1_MASK                                          (0x0000FFFFU)
#define CSL_PCID_RBIRINTPCFG1_T1_SHIFT                                         (0x00000000U)
#define CSL_PCID_RBIRINTPCFG1_T1_MAX                                           (0x0000FFFFU)

#define CSL_PCID_RBIRINTPCFG1_T2_MASK                                          (0xFFFF0000U)
#define CSL_PCID_RBIRINTPCFG1_T2_SHIFT                                         (0x00000010U)
#define CSL_PCID_RBIRINTPCFG1_T2_MAX                                           (0x0000FFFFU)

/* RBIRINTPCFG2 */

#define CSL_PCID_RBIRINTPCFG2_T3_MASK                                          (0x0000FFFFU)
#define CSL_PCID_RBIRINTPCFG2_T3_SHIFT                                         (0x00000000U)
#define CSL_PCID_RBIRINTPCFG2_T3_MAX                                           (0x0000FFFFU)

/* RBIRCOLORDIFFCFG */

#define CSL_PCID_RBIRCOLORDIFFCFG_GHFXFERFACTOR_MASK                           (0x000001FFU)
#define CSL_PCID_RBIRCOLORDIFFCFG_GHFXFERFACTOR_SHIFT                          (0x00000000U)
#define CSL_PCID_RBIRCOLORDIFFCFG_GHFXFERFACTOR_MAX                            (0x000001FFU)

#define CSL_PCID_RBIRCOLORDIFFCFG_GHFXFERFACTORIR_MASK                         (0x01FF0000U)
#define CSL_PCID_RBIRCOLORDIFFCFG_GHFXFERFACTORIR_SHIFT                        (0x00000010U)
#define CSL_PCID_RBIRCOLORDIFFCFG_GHFXFERFACTORIR_MAX                          (0x000001FFU)

/* IRSUBCFG1 */

#define CSL_PCID_IRSUBCFG1_CUTOFFTH_MASK                                       (0x0000FFFFU)
#define CSL_PCID_IRSUBCFG1_CUTOFFTH_SHIFT                                      (0x00000000U)
#define CSL_PCID_IRSUBCFG1_CUTOFFTH_MAX                                        (0x0000FFFFU)

/* IRSUBCFG2 */

#define CSL_PCID_IRSUBCFG2_TRANSITIONRANGE_MASK                                (0x000000FFU)
#define CSL_PCID_IRSUBCFG2_TRANSITIONRANGE_SHIFT                               (0x00000000U)
#define CSL_PCID_IRSUBCFG2_TRANSITIONRANGE_MAX                                 (0x000000FFU)

#define CSL_PCID_IRSUBCFG2_TRANSITIONRANGEINV_MASK                             (0x01FF0000U)
#define CSL_PCID_IRSUBCFG2_TRANSITIONRANGEINV_SHIFT                            (0x00000010U)
#define CSL_PCID_IRSUBCFG2_TRANSITIONRANGEINV_MAX                              (0x000001FFU)

/* IRSUBDISTSCALELUT0 */

#define CSL_PCID_IRSUBDISTSCALELUT0_D0SCALE_MASK                               (0x000001FFU)
#define CSL_PCID_IRSUBDISTSCALELUT0_D0SCALE_SHIFT                              (0x00000000U)
#define CSL_PCID_IRSUBDISTSCALELUT0_D0SCALE_MAX                                (0x000001FFU)

#define CSL_PCID_IRSUBDISTSCALELUT0_D1SCALE_MASK                               (0x01FF0000U)
#define CSL_PCID_IRSUBDISTSCALELUT0_D1SCALE_SHIFT                              (0x00000010U)
#define CSL_PCID_IRSUBDISTSCALELUT0_D1SCALE_MAX                                (0x000001FFU)

/* IRSUBDISTSCALELUT1 */

#define CSL_PCID_IRSUBDISTSCALELUT1_D2SCALE_MASK                               (0x000001FFU)
#define CSL_PCID_IRSUBDISTSCALELUT1_D2SCALE_SHIFT                              (0x00000000U)
#define CSL_PCID_IRSUBDISTSCALELUT1_D2SCALE_MAX                                (0x000001FFU)

#define CSL_PCID_IRSUBDISTSCALELUT1_D3SCALE_MASK                               (0x01FF0000U)
#define CSL_PCID_IRSUBDISTSCALELUT1_D3SCALE_SHIFT                              (0x00000010U)
#define CSL_PCID_IRSUBDISTSCALELUT1_D3SCALE_MAX                                (0x000001FFU)

/* IRSUBDISTSCALELUT2 */

#define CSL_PCID_IRSUBDISTSCALELUT2_D4SCALE_MASK                               (0x000001FFU)
#define CSL_PCID_IRSUBDISTSCALELUT2_D4SCALE_SHIFT                              (0x00000000U)
#define CSL_PCID_IRSUBDISTSCALELUT2_D4SCALE_MAX                                (0x000001FFU)

/* IRSUBSCALE0 */

#define CSL_PCID_IRSUBSCALE0_SUBFACTSCALE00_MASK                               (0x000001FFU)
#define CSL_PCID_IRSUBSCALE0_SUBFACTSCALE00_SHIFT                              (0x00000000U)
#define CSL_PCID_IRSUBSCALE0_SUBFACTSCALE00_MAX                                (0x000001FFU)

#define CSL_PCID_IRSUBSCALE0_SUBFACTSCALE01_MASK                               (0x01FF0000U)
#define CSL_PCID_IRSUBSCALE0_SUBFACTSCALE01_SHIFT                              (0x00000010U)
#define CSL_PCID_IRSUBSCALE0_SUBFACTSCALE01_MAX                                (0x000001FFU)

/* IRSUBSCALE1 */

#define CSL_PCID_IRSUBSCALE1_SUBFACTSCALE10_MASK                               (0x000001FFU)
#define CSL_PCID_IRSUBSCALE1_SUBFACTSCALE10_SHIFT                              (0x00000000U)
#define CSL_PCID_IRSUBSCALE1_SUBFACTSCALE10_MAX                                (0x000001FFU)

#define CSL_PCID_IRSUBSCALE1_SUBFACTSCALE11_MASK                               (0x01FF0000U)
#define CSL_PCID_IRSUBSCALE1_SUBFACTSCALE11_SHIFT                              (0x00000010U)
#define CSL_PCID_IRSUBSCALE1_SUBFACTSCALE11_MAX                                (0x000001FFU)

/* INT_STAT */

#define CSL_PCID_INT_STAT_LUT_CFG_ERR_MASK                                     (0x00000001U)
#define CSL_PCID_INT_STAT_LUT_CFG_ERR_SHIFT                                    (0x00000000U)
#define CSL_PCID_INT_STAT_LUT_CFG_ERR_MAX                                      (0x00000001U)

/* DBG_CTL */

#define CSL_PCID_DBG_CTL_LINEMEM_SEL_MASK                                      (0x00001F00U)
#define CSL_PCID_DBG_CTL_LINEMEM_SEL_SHIFT                                     (0x00000008U)
#define CSL_PCID_DBG_CTL_LINEMEM_SEL_MAX                                       (0x0000001FU)

#define CSL_PCID_DBG_CTL_IR_EOF_EN_MASK                                        (0x00000040U)
#define CSL_PCID_DBG_CTL_IR_EOF_EN_SHIFT                                       (0x00000006U)
#define CSL_PCID_DBG_CTL_IR_EOF_EN_MAX                                         (0x00000001U)

#define CSL_PCID_DBG_CTL_IR_EOL_EN_MASK                                        (0x00000020U)
#define CSL_PCID_DBG_CTL_IR_EOL_EN_SHIFT                                       (0x00000005U)
#define CSL_PCID_DBG_CTL_IR_EOL_EN_MAX                                         (0x00000001U)

#define CSL_PCID_DBG_CTL_BAYER_EOF_EN_MASK                                     (0x00000010U)
#define CSL_PCID_DBG_CTL_BAYER_EOF_EN_SHIFT                                    (0x00000004U)
#define CSL_PCID_DBG_CTL_BAYER_EOF_EN_MAX                                      (0x00000001U)

#define CSL_PCID_DBG_CTL_BAYER_EOL_EN_MASK                                     (0x00000008U)
#define CSL_PCID_DBG_CTL_BAYER_EOL_EN_SHIFT                                    (0x00000003U)
#define CSL_PCID_DBG_CTL_BAYER_EOL_EN_MAX                                      (0x00000001U)

#define CSL_PCID_DBG_CTL_SOF_EN_MASK                                           (0x00000004U)
#define CSL_PCID_DBG_CTL_SOF_EN_SHIFT                                          (0x00000002U)
#define CSL_PCID_DBG_CTL_SOF_EN_MAX                                            (0x00000001U)

#define CSL_PCID_DBG_CTL_SOL_EN_MASK                                           (0x00000002U)
#define CSL_PCID_DBG_CTL_SOL_EN_SHIFT                                          (0x00000001U)
#define CSL_PCID_DBG_CTL_SOL_EN_MAX                                            (0x00000001U)

#define CSL_PCID_DBG_CTL_DBG_EN_MASK                                           (0x00000001U)
#define CSL_PCID_DBG_CTL_DBG_EN_SHIFT                                          (0x00000000U)
#define CSL_PCID_DBG_CTL_DBG_EN_MAX                                            (0x00000001U)

/* DBG_STAT */

#define CSL_PCID_DBG_STAT_IR_EOF_MASK                                          (0x00000040U)
#define CSL_PCID_DBG_STAT_IR_EOF_SHIFT                                         (0x00000006U)
#define CSL_PCID_DBG_STAT_IR_EOF_MAX                                           (0x00000001U)

#define CSL_PCID_DBG_STAT_IR_EOL_MASK                                          (0x00000020U)
#define CSL_PCID_DBG_STAT_IR_EOL_SHIFT                                         (0x00000005U)
#define CSL_PCID_DBG_STAT_IR_EOL_MAX                                           (0x00000001U)

#define CSL_PCID_DBG_STAT_BAYER_EOF_MASK                                       (0x00000010U)
#define CSL_PCID_DBG_STAT_BAYER_EOF_SHIFT                                      (0x00000004U)
#define CSL_PCID_DBG_STAT_BAYER_EOF_MAX                                        (0x00000001U)

#define CSL_PCID_DBG_STAT_BAYER_EOL_MASK                                       (0x00000008U)
#define CSL_PCID_DBG_STAT_BAYER_EOL_SHIFT                                      (0x00000003U)
#define CSL_PCID_DBG_STAT_BAYER_EOL_MAX                                        (0x00000001U)

#define CSL_PCID_DBG_STAT_SOF_MASK                                             (0x00000004U)
#define CSL_PCID_DBG_STAT_SOF_SHIFT                                            (0x00000002U)
#define CSL_PCID_DBG_STAT_SOF_MAX                                              (0x00000001U)

#define CSL_PCID_DBG_STAT_SOL_MASK                                             (0x00000002U)
#define CSL_PCID_DBG_STAT_SOL_SHIFT                                            (0x00000001U)
#define CSL_PCID_DBG_STAT_SOL_MAX                                              (0x00000001U)

/**************************************************************************
* Hardware Region  : IR gamma Remap LUT
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT[320];                  /* pcid Remap LUT  */
} CSL_irremap_lutRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_IRREMAP_LUT_LUT(LUT)                                               (0x00000000U+((LUT)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT */

#define CSL_IRREMAP_LUT_LUT_LUT_ENTRY_LO_MASK                                  (0x0000FFFFU)
#define CSL_IRREMAP_LUT_LUT_LUT_ENTRY_LO_SHIFT                                 (0x00000000U)
#define CSL_IRREMAP_LUT_LUT_LUT_ENTRY_LO_MAX                                   (0x0000FFFFU)

#define CSL_IRREMAP_LUT_LUT_LUT_ENTRY_HI_MASK                                  (0xFFFF0000U)
#define CSL_IRREMAP_LUT_LUT_LUT_ENTRY_HI_SHIFT                                 (0x00000010U)
#define CSL_IRREMAP_LUT_LUT_LUT_ENTRY_HI_MAX                                   (0x0000FFFFU)

/**************************************************************************
* Hardware Region  : pcid Line memory
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t MEM[2048];                 /* pcid Line memory */
} CSL_pcid_linememRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_PCID_LINEMEM_MEM(MEM)                                              (0x00000000U+((MEM)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* MEM */

#define CSL_PCID_LINEMEM_MEM_PIXD_MASK                                         (0xFFFFFFFFU)
#define CSL_PCID_LINEMEM_MEM_PIXD_SHIFT                                        (0x00000000U)
#define CSL_PCID_LINEMEM_MEM_PIXD_MAX                                          (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#endif

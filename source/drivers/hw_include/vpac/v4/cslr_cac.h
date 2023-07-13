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
 *  Name        : cslr_cac.h
*/
#ifndef CSLR_CAC_H_
#define CSLR_CAC_H_

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
    volatile uint32_t CTRL;                      /* CAC Control Register */
    volatile uint32_t FRAMESZ;                   /* Frame Size Register */
    volatile uint32_t BLOCKSZ;                   /* LUT Block size */
    volatile uint32_t BLOCKCNT;                  /* LUT Grid size */
    volatile uint8_t  Resv_128[108];
    volatile uint32_t INT_STAT;                  /* CAC Interrupt status */
    volatile uint8_t  Resv_256[124];
    volatile uint32_t DBG_CTL;                   /* CAC Debug Status Register  */
    volatile uint32_t DBG_STAT;                  /* CAC Debug event status */
} CSL_cacRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CAC_CTRL                                                           (0x00000004U)
#define CSL_CAC_FRAMESZ                                                        (0x00000008U)
#define CSL_CAC_BLOCKSZ                                                        (0x0000000CU)
#define CSL_CAC_BLOCKCNT                                                       (0x00000010U)
#define CSL_CAC_INT_STAT                                                       (0x00000080U)
#define CSL_CAC_DBG_CTL                                                        (0x00000100U)
#define CSL_CAC_DBG_STAT                                                       (0x00000104U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CTRL */

#define CSL_CAC_CTRL_COLOR_EN_MASK                                             (0x00000F00U)
#define CSL_CAC_CTRL_COLOR_EN_SHIFT                                            (0x00000008U)
#define CSL_CAC_CTRL_COLOR_EN_MAX                                              (0x0000000FU)

/* FRAMESZ */

#define CSL_CAC_FRAMESZ_WIDTH_MASK                                             (0x00001FFFU)
#define CSL_CAC_FRAMESZ_WIDTH_SHIFT                                            (0x00000000U)
#define CSL_CAC_FRAMESZ_WIDTH_MAX                                              (0x00001FFFU)

#define CSL_CAC_FRAMESZ_HEIGHT_MASK                                            (0x1FFF0000U)
#define CSL_CAC_FRAMESZ_HEIGHT_SHIFT                                           (0x00000010U)
#define CSL_CAC_FRAMESZ_HEIGHT_MAX                                             (0x00001FFFU)

/* BLOCKSZ */

#define CSL_CAC_BLOCKSZ_SIZE_MASK                                              (0x000000FFU)
#define CSL_CAC_BLOCKSZ_SIZE_SHIFT                                             (0x00000000U)
#define CSL_CAC_BLOCKSZ_SIZE_MAX                                               (0x000000FFU)

/* BLOCKCNT */

#define CSL_CAC_BLOCKCNT_HCNT_MASK                                             (0x000003FFU)
#define CSL_CAC_BLOCKCNT_HCNT_SHIFT                                            (0x00000000U)
#define CSL_CAC_BLOCKCNT_HCNT_MAX                                              (0x000003FFU)

#define CSL_CAC_BLOCKCNT_VCNT_MASK                                             (0x03FF0000U)
#define CSL_CAC_BLOCKCNT_VCNT_SHIFT                                            (0x00000010U)
#define CSL_CAC_BLOCKCNT_VCNT_MAX                                              (0x000003FFU)

/* INT_STAT */

#define CSL_CAC_INT_STAT_LUT_CFG_ERR_MASK                                      (0x00000001U)
#define CSL_CAC_INT_STAT_LUT_CFG_ERR_SHIFT                                     (0x00000000U)
#define CSL_CAC_INT_STAT_LUT_CFG_ERR_MAX                                       (0x00000001U)

/* DBG_CTL */

#define CSL_CAC_DBG_CTL_LINEMEM_SEL_MASK                                       (0x00000F00U)
#define CSL_CAC_DBG_CTL_LINEMEM_SEL_SHIFT                                      (0x00000008U)
#define CSL_CAC_DBG_CTL_LINEMEM_SEL_MAX                                        (0x0000000FU)

#define CSL_CAC_DBG_CTL_EOF_EN_MASK                                            (0x00000010U)
#define CSL_CAC_DBG_CTL_EOF_EN_SHIFT                                           (0x00000004U)
#define CSL_CAC_DBG_CTL_EOF_EN_MAX                                             (0x00000001U)

#define CSL_CAC_DBG_CTL_EOL_EN_MASK                                            (0x00000008U)
#define CSL_CAC_DBG_CTL_EOL_EN_SHIFT                                           (0x00000003U)
#define CSL_CAC_DBG_CTL_EOL_EN_MAX                                             (0x00000001U)

#define CSL_CAC_DBG_CTL_SOF_EN_MASK                                            (0x00000004U)
#define CSL_CAC_DBG_CTL_SOF_EN_SHIFT                                           (0x00000002U)
#define CSL_CAC_DBG_CTL_SOF_EN_MAX                                             (0x00000001U)

#define CSL_CAC_DBG_CTL_SOL_EN_MASK                                            (0x00000002U)
#define CSL_CAC_DBG_CTL_SOL_EN_SHIFT                                           (0x00000001U)
#define CSL_CAC_DBG_CTL_SOL_EN_MAX                                             (0x00000001U)

#define CSL_CAC_DBG_CTL_DBG_EN_MASK                                            (0x00000001U)
#define CSL_CAC_DBG_CTL_DBG_EN_SHIFT                                           (0x00000000U)
#define CSL_CAC_DBG_CTL_DBG_EN_MAX                                             (0x00000001U)

/* DBG_STAT */

#define CSL_CAC_DBG_STAT_EOF_MASK                                              (0x00000010U)
#define CSL_CAC_DBG_STAT_EOF_SHIFT                                             (0x00000004U)
#define CSL_CAC_DBG_STAT_EOF_MAX                                               (0x00000001U)

#define CSL_CAC_DBG_STAT_EOL_MASK                                              (0x00000008U)
#define CSL_CAC_DBG_STAT_EOL_SHIFT                                             (0x00000003U)
#define CSL_CAC_DBG_STAT_EOL_MAX                                               (0x00000001U)

#define CSL_CAC_DBG_STAT_SOF_MASK                                              (0x00000004U)
#define CSL_CAC_DBG_STAT_SOF_SHIFT                                             (0x00000002U)
#define CSL_CAC_DBG_STAT_SOF_MAX                                               (0x00000001U)

#define CSL_CAC_DBG_STAT_SOL_MASK                                              (0x00000002U)
#define CSL_CAC_DBG_STAT_SOL_SHIFT                                             (0x00000001U)
#define CSL_CAC_DBG_STAT_SOL_MAX                                               (0x00000001U)

/**************************************************************************
* Hardware Region  : CAC displacement LUT
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT[2048];                 /* CAC displacement LUT */
} CSL_cac_lutRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CAC_LUT_LUT(LUT)                                                   (0x00000000U+((LUT)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT */

#define CSL_CAC_LUT_LUT_EVEN_DX_MASK                                           (0x000000FFU)
#define CSL_CAC_LUT_LUT_EVEN_DX_SHIFT                                          (0x00000000U)
#define CSL_CAC_LUT_LUT_EVEN_DX_MAX                                            (0x000000FFU)

#define CSL_CAC_LUT_LUT_EVEN_DY_MASK                                           (0x0000FF00U)
#define CSL_CAC_LUT_LUT_EVEN_DY_SHIFT                                          (0x00000008U)
#define CSL_CAC_LUT_LUT_EVEN_DY_MAX                                            (0x000000FFU)

#define CSL_CAC_LUT_LUT_ODD_DX_MASK                                            (0x00FF0000U)
#define CSL_CAC_LUT_LUT_ODD_DX_SHIFT                                           (0x00000010U)
#define CSL_CAC_LUT_LUT_ODD_DX_MAX                                             (0x000000FFU)

#define CSL_CAC_LUT_LUT_ODD_DY_MASK                                            (0xFF000000U)
#define CSL_CAC_LUT_LUT_ODD_DY_SHIFT                                           (0x00000018U)
#define CSL_CAC_LUT_LUT_ODD_DY_MAX                                             (0x000000FFU)

/**************************************************************************
* Hardware Region  : CAC Line memory
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t MEM[2048];                 /* CAC Line memory */
} CSL_cac_linememRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CAC_LINEMEM_MEM(MEM)                                               (0x00000000U+((MEM)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* MEM */

#define CSL_CAC_LINEMEM_MEM_PIXD_MASK                                          (0xFFFFFFFFU)
#define CSL_CAC_LINEMEM_MEM_PIXD_SHIFT                                         (0x00000000U)
#define CSL_CAC_LINEMEM_MEM_PIXD_MAX                                           (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#endif

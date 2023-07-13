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
 *  Name        : cslr_rawfe.h
*/
#ifndef CSLR_RAWFE_H_
#define CSLR_RAWFE_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[320];                 /* image cfg  */
} CSL_rawfe_pwl_lut3_ramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_PWL_LUT3_RAM_RAM1(RAM1)                                      (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_PWL_LUT3_RAM_RAM1_DATA_L_MASK                                (0x0000FFFFU)
#define CSL_RAWFE_PWL_LUT3_RAM_RAM1_DATA_L_SHIFT                               (0x00000000U)
#define CSL_RAWFE_PWL_LUT3_RAM_RAM1_DATA_L_MAX                                 (0x0000FFFFU)

#define CSL_RAWFE_PWL_LUT3_RAM_RAM1_DATA_U_MASK                                (0xFFFF0000U)
#define CSL_RAWFE_PWL_LUT3_RAM_RAM1_DATA_U_SHIFT                               (0x00000010U)
#define CSL_RAWFE_PWL_LUT3_RAM_RAM1_DATA_U_MAX                                 (0x0000FFFFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[320];                 /* image cfg  */
} CSL_rawfe_pwl_lut2_ramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_PWL_LUT2_RAM_RAM1(RAM1)                                      (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_PWL_LUT2_RAM_RAM1_DATA_L_MASK                                (0x0000FFFFU)
#define CSL_RAWFE_PWL_LUT2_RAM_RAM1_DATA_L_SHIFT                               (0x00000000U)
#define CSL_RAWFE_PWL_LUT2_RAM_RAM1_DATA_L_MAX                                 (0x0000FFFFU)

#define CSL_RAWFE_PWL_LUT2_RAM_RAM1_DATA_U_MASK                                (0xFFFF0000U)
#define CSL_RAWFE_PWL_LUT2_RAM_RAM1_DATA_U_SHIFT                               (0x00000010U)
#define CSL_RAWFE_PWL_LUT2_RAM_RAM1_DATA_U_MAX                                 (0x0000FFFFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[320];                 /* image cfg  */
} CSL_rawfe_pwl_lut1_ramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_PWL_LUT1_RAM_RAM1(RAM1)                                      (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_PWL_LUT1_RAM_RAM1_DATA_L_MASK                                (0x0000FFFFU)
#define CSL_RAWFE_PWL_LUT1_RAM_RAM1_DATA_L_SHIFT                               (0x00000000U)
#define CSL_RAWFE_PWL_LUT1_RAM_RAM1_DATA_L_MAX                                 (0x0000FFFFU)

#define CSL_RAWFE_PWL_LUT1_RAM_RAM1_DATA_U_MASK                                (0xFFFF0000U)
#define CSL_RAWFE_PWL_LUT1_RAM_RAM1_DATA_U_SHIFT                               (0x00000010U)
#define CSL_RAWFE_PWL_LUT1_RAM_RAM1_DATA_U_MAX                                 (0x0000FFFFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[320];                 /* image cfg  */
} CSL_rawfe_wdr_lut_ramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_WDR_LUT_RAM_RAM1(RAM1)                                       (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_WDR_LUT_RAM_RAM1_DATA_L_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_WDR_LUT_RAM_RAM1_DATA_L_SHIFT                                (0x00000000U)
#define CSL_RAWFE_WDR_LUT_RAM_RAM1_DATA_L_MAX                                  (0x0000FFFFU)

#define CSL_RAWFE_WDR_LUT_RAM_RAM1_DATA_U_MASK                                 (0xFFFF0000U)
#define CSL_RAWFE_WDR_LUT_RAM_RAM1_DATA_U_SHIFT                                (0x00000010U)
#define CSL_RAWFE_WDR_LUT_RAM_RAM1_DATA_U_MAX                                  (0x0000FFFFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[320];                 /* image cfg  */
} CSL_rawfe_h3a_lut_ramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_H3A_LUT_RAM_RAM1(RAM1)                                       (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_H3A_LUT_RAM_RAM1_DATA_L_MASK                                 (0x000003FFU)
#define CSL_RAWFE_H3A_LUT_RAM_RAM1_DATA_L_SHIFT                                (0x00000000U)
#define CSL_RAWFE_H3A_LUT_RAM_RAM1_DATA_L_MAX                                  (0x000003FFU)

#define CSL_RAWFE_H3A_LUT_RAM_RAM1_DATA_U_MASK                                 (0x03FF0000U)
#define CSL_RAWFE_H3A_LUT_RAM_RAM1_DATA_U_SHIFT                                (0x00000010U)
#define CSL_RAWFE_H3A_LUT_RAM_RAM1_DATA_U_MAX                                  (0x000003FFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[256];                 /* image cfg  */
} CSL_rawfe_dpc_lut_ramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_DPC_LUT_RAM_RAM1(RAM1)                                       (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_DPC_LUT_RAM_RAM1_DATA_MASK                                   (0x1FFFFFFFU)
#define CSL_RAWFE_DPC_LUT_RAM_RAM1_DATA_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_DPC_LUT_RAM_RAM1_DATA_MAX                                    (0x1FFFFFFFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[2048];                /* image cfg  */
} CSL_rawfe_dpc_lramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_DPC_LRAM_RAM1(RAM1)                                          (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_DPC_LRAM_RAM1_DATA_MASK                                      (0xFFFFFFFFU)
#define CSL_RAWFE_DPC_LRAM_RAM1_DATA_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_DPC_LRAM_RAM1_DATA_MAX                                       (0xFFFFFFFFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[5248];                /* image cfg  */
} CSL_rawfe_lsc_lut_ramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_LSC_LUT_RAM_RAM1(RAM1)                                       (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_LSC_LUT_RAM_RAM1_DATA_MASK                                   (0xFFFFFFFFU)
#define CSL_RAWFE_LSC_LUT_RAM_RAM1_DATA_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_LSC_LUT_RAM_RAM1_DATA_MAX                                    (0xFFFFFFFFU)

/**************************************************************************
* Hardware Region  : MMR Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t IMAGE_CFG;                 /* image cfg  */
    volatile uint32_t SHADOW_CFG;                /* shadow configuration */
    volatile uint32_t PWL1_MASK_SH;              /* PWL1 mask and shift */
    volatile uint32_t PWL1_EN;                   /* PWL1 enable */
    volatile uint32_t PWL1_THRX12;               /* PWL1 threshold X1 and X2 */
    volatile uint32_t PWL1_THRX3;                /* PWL1 threshold X3 */
    volatile uint32_t PWL1_THRY1;                /* PWL1 threshold Y1 */
    volatile uint32_t PWL1_THRY2;                /* PWL1 threshold Y2 */
    volatile uint32_t PWL1_THRY3;                /* PWL1 threshold Y3 */
    volatile uint32_t PWL1_SLP12;                /* PWL1 slope 1 and 2 */
    volatile uint32_t PWL1_SLP34;                /* PWL1 slope 3 and 4 */
    volatile uint32_t PWL1_SLPSH_CLIP;           /* PWL1 slope shift and clip */
    volatile uint32_t PWL1_OFF1;                 /* PWL1 Offset0 */
    volatile uint32_t PWL1_OFF2;                 /* PWL1  Offset0 */
    volatile uint32_t PWL1_OFF3;                 /* PWL1  Offset0 */
    volatile uint32_t PWL1_OFF4;                 /* PWL1  Offset0 */
    volatile uint32_t PWL1_WB_GAIN12;            /* PWL1 WB gain 1 and 2 */
    volatile uint32_t PWL1_WB_GAIN34;            /* PWL1 WB gain 3 and 4 */
    volatile uint32_t PWL1_LUT;                  /* PWL1 LUT configuration */
    volatile uint32_t PWL1_LUTCLIP;              /* PWL1 LUT output clip value */
    volatile uint32_t PWL2_MASK_SH;              /* PWL2 mask and shift */
    volatile uint32_t PWL2_EN;                   /* PWL2 enable */
    volatile uint32_t PWL2_THRX12;               /* PWL2 threshold X1 and X2 */
    volatile uint32_t PWL2_THRX3;                /* PWL2 threshold X3 */
    volatile uint32_t PWL2_THRY1;                /* PWL2 threshold Y1 */
    volatile uint32_t PWL2_THRY2;                /* PWL2 threshold Y2 */
    volatile uint32_t PWL2_THRY3;                /* PWL2 threshold Y3 */
    volatile uint32_t PWL2_SLP12;                /* PWL2 slope 1 and 2 */
    volatile uint32_t PWL2_SLP34;                /* PWL2 slope 3 and 4 */
    volatile uint32_t PWL2_SLPSH_CLIP;           /* PWL2 slope shift and clip */
    volatile uint32_t PWL2_LUT;                  /* PWL2 LUT configuration */
    volatile uint32_t PWL2_LUTCLIP;              /* PWL2 LUT output clip value */
    volatile uint32_t PWL2_OFF1;                 /* PWL2 WB Offset0 */
    volatile uint32_t PWL2_OFF2;                 /* PWL2  Offset0 */
    volatile uint32_t PWL2_OFF3;                 /* PWL2  Offset0 */
    volatile uint32_t PWL2_OFF4;                 /* PWL2  Offset0 */
    volatile uint32_t PWL2_WB_GAIN12;            /* PWL2 WB gain 1 and 2 */
    volatile uint32_t PWL2_WB_GAIN34;            /* PWL2 WB gain 3 and 4 */
    volatile uint32_t PWL3_MASK_SH;              /* PWL3 mask and shift */
    volatile uint32_t PWL3_EN;                   /* PWL3 enable */
    volatile uint32_t PWL3_THRX12;               /* PWL3 threshold X1 and X2 */
    volatile uint32_t PWL3_THRX3;                /* PWL3 threshold X3 */
    volatile uint32_t PWL3_THRY1;                /* PWL3 threshold Y1 */
    volatile uint32_t PWL3_THRY2;                /* PWL3 threshold Y2 */
    volatile uint32_t PWL3_THRY3;                /* PWL3 threshold Y3 */
    volatile uint32_t PWL3_SLP12;                /* PWL3 slope 1 and 2 */
    volatile uint32_t PWL3_SLP34;                /* PWL3 slope 3 and 4 */
    volatile uint32_t PWL3_SLPSH_CLIP;           /* PWL3 slope shift and clip */
    volatile uint32_t PWL3_LUT;                  /* PWL3 LUT configuration */
    volatile uint32_t PWL3_LUTCLIP;              /* PWL3 LUT output clip value */
    volatile uint32_t PWL3_OFF1;                 /* PWL3  Offset0 */
    volatile uint32_t PWL3_OFF2;                 /* PWL3  Offset0 */
    volatile uint32_t PWL3_OFF3;                 /* PWL3  Offset0 */
    volatile uint32_t PWL3_OFF4;                 /* PWL3  Offset0 */
    volatile uint32_t PWL3_WB_GAIN12;            /* PWL3 WB gain 1 and 2 */
    volatile uint32_t PWL3_WB_GAIN34;            /* PWL3 WB gain 3 and 4 */
    volatile uint32_t WDRMRG1_CFG;               /* WDR merge1 configuration */
    volatile uint32_t WDRMRG1_GAIN;              /* WDR merge1 gain */
    volatile uint32_t WDRMRG1_LBLK12;            /* WDR merge1 black level 1 and 2 */
    volatile uint32_t WDRMRG1_LBLK34;            /* WDR merge1 black level 3 and 4 */
    volatile uint32_t WDRMRG1_SBLK12;            /* WDR merge1 black level 1 and 2 */
    volatile uint32_t WDRMRG1_SBLK34;            /* WDR merge1 black level 3 and 4 */
    volatile uint32_t WDRMRG1_LWB12;             /* WDR merge1 WB gain 1 and 2 */
    volatile uint32_t WDRMRG1_LWB34;             /* WDR merge1 WB gain 3 and 4 */
    volatile uint32_t WDRMRG1_SWB12;             /* WDR merge1 WB gain 1 and 2 */
    volatile uint32_t WDRMRG1_SWB34;             /* WDR merge1 WB gain 3 and 4 */
    volatile uint32_t WDRMRG1_WDRTHR_BF;         /* WDR merge1 WDRTHR and BF */
    volatile uint32_t WDRMRG1_AF;                /* WDR merge1 AF */
    volatile uint32_t WDRMRG1_MA;                /* WDR merge1 MA */
    volatile uint32_t WDRMRG1_CLIP_SFT;          /* WDR merge1 clip and shift */
    volatile uint32_t WDRMRG2_CFG;               /* WDR merge2 configuration */
    volatile uint32_t WDRMRG2_GAIN;              /* WDR merge2 gain */
    volatile uint32_t WDRMRG2_LBLK12;            /* WDR merge2 black level 1 and 2 */
    volatile uint32_t WDRMRG2_LBLK34;            /* WDR merge2 black level 3 and 4 */
    volatile uint32_t WDRMRG2_SBLK12;            /* WDR merge2 black level 1 and 2 */
    volatile uint32_t WDRMRG2_SBLK34;            /* WDR merge2 black level 3 and 4 */
    volatile uint32_t WDRMRG2_LWB12;             /* WDR merge2 WB gain 1 and 2 */
    volatile uint32_t WDRMRG2_LWB34;             /* WDR merge2 WB gain 3 and 4 */
    volatile uint32_t WDRMRG2_SWB12;             /* WDR merge2 WB gain 1 and 2 */
    volatile uint32_t WDRMRG2_SWB34;             /* WDR merge2 WB gain 3 and 4 */
    volatile uint32_t WDRMRG2_WDRTHR_BF;         /* WDR merge2 WDRTHR and BF */
    volatile uint32_t WDRMRG2_AF;                /* WDR merge2 AF */
    volatile uint32_t WDRMRG2_MA;                /* WDR merge2 MA */
    volatile uint32_t WDRMRG2_CLIP_SFT;          /* WDR merge2 clip and shift */
    volatile uint32_t MRGLUT_CFG;                /* Merge LUT configuration */
    volatile uint32_t LUTDPC_CFG;                /* LUTDPC configuration */
    volatile uint32_t OTFDPC_EN;                 /* OTFDPC enable */
    volatile uint32_t OTFDPC_THRSLP1;            /* OTFDPC threshold and slope 1 */
    volatile uint32_t OTFDPC_THRSLP2;            /* OTFDPC threshold and slope 2 */
    volatile uint32_t OTFDPC_THRSLP3;            /* OTFDPC threshold and slope 3 */
    volatile uint32_t OTFDPC_THRSLP4;            /* OTFDPC threshold and slope 4 */
    volatile uint32_t OTFDPC_THRSLP5;            /* OTFDPC threshold and slope 5 */
    volatile uint32_t OTFDPC_THRSLP6;            /* OTFDPC threshold and slope 6 */
    volatile uint32_t OTFDPC_THRSLP7;            /* OTFDPC threshold and slope 7 */
    volatile uint32_t OTFDPC_THRSLP8;            /* OTFDPC threshold and slope 8 */
    volatile uint32_t LSC_CFG;                   /* LSC configuration */
    volatile uint32_t WB2_OFFSET12;              /* WB2 offset 1 and 2 */
    volatile uint32_t WB2_OFFSET34;              /* WB2 offset 3 and 4 */
    volatile uint32_t WB2_GAIN12;                /* WB2 gain 1 and 2 */
    volatile uint32_t WB2_GAIN34;                /* WB2 gain 3 and 4 */
    volatile uint32_t H3AMUX_CFG;                /* H3A MUX configuration */
    volatile uint32_t H3ALUT_CFG;                /* H3A LUT configuration */
    volatile uint32_t RAWFE_INT_STAT;            /* status/clear register for rawfe interrupts */
    volatile uint8_t  Resv_512[100];
    volatile uint32_t DBG_CTL;                   /* debug event control register */
    volatile uint32_t DBG_HWBP;                  /* x,y position for event match */
    volatile uint32_t DBG_STAT1;                 /* status/clear register for debug events */
    volatile uint32_t DBG_STAT2;                 /* x,y position for event match */
    volatile uint32_t DBG_STAT3;                 /* internal state status */
    volatile uint32_t DBG_STAT4;                 /* internal state status */
    volatile uint8_t  Resv_544[8];
    volatile uint32_t CFA_CFG;                   /* RAWFE CFA cfg register */
    volatile uint32_t OTFDPC_THRX12;             /* OTFDPC threshold 1 and 2 x-position */
    volatile uint32_t OTFDPC_THRX34;             /* OTFDPC threshold 3 and 4 x-position */
    volatile uint32_t OTFDPC_THRX56;             /* OTFDPC threshold 5 and 6 x-position */
    volatile uint32_t OTFDPC_THRX78;             /* OTFDPC threshold 7 and 8 x-position */
    volatile uint32_t OTFDPC_LUT2_THRSLP1;       /* OTFDPC LUT2 threshold and slope 1 */
    volatile uint32_t OTFDPC_LUT2_THRSLP2;       /* OTFDPC LUT2 threshold and slope 2 */
    volatile uint32_t OTFDPC_LUT2_THRSLP3;       /* OTFDPC LUT2 threshold and slope 3 */
    volatile uint32_t OTFDPC_LUT2_THRSLP4;       /* OTFDPC LUT2 threshold and slope 4 */
    volatile uint32_t OTFDPC_LUT2_THRSLP5;       /* OTFDPC LUT2 threshold and slope 5 */
    volatile uint32_t OTFDPC_LUT2_THRSLP6;       /* OTFDPC LUT2 threshold and slope 6 */
    volatile uint32_t OTFDPC_LUT2_THRSLP7;       /* OTFDPC LUT2 threshold and slope 7 */
    volatile uint32_t OTFDPC_LUT2_THRSLP8;       /* OTFDPC LUT2 threshold and slope 8 */
    volatile uint32_t OTFDPC_LUT2_THRX12;        /* OTFDPC LUT2 threshold 1 and 2 x-position */
    volatile uint32_t OTFDPC_LUT2_THRX34;        /* OTFDPC LUT2 threshold 3 and 4 x-position */
    volatile uint32_t OTFDPC_LUT2_THRX56;        /* OTFDPC LUT2 threshold 5 and 6 x-position */
    volatile uint32_t OTFDPC_LUT2_THRX78;        /* OTFDPC LUT2 threshold 7 and 8 x-position */
    volatile uint32_t OTFDPC_COUNT;              /* OTFDPC detected defect pixel count */
    volatile uint32_t LSC_LUT_MAP07;             /* LSC LUT  MAP 0 to 7  */
    volatile uint32_t LSC_LUT_MAP815;            /* LSC LUT  MAP 8 to 15  */
} CSL_rawfe_cfgRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_CFG_IMAGE_CFG                                                (0x00000000U)
#define CSL_RAWFE_CFG_SHADOW_CFG                                               (0x00000004U)
#define CSL_RAWFE_CFG_PWL1_MASK_SH                                             (0x00000008U)
#define CSL_RAWFE_CFG_PWL1_EN                                                  (0x0000000CU)
#define CSL_RAWFE_CFG_PWL1_THRX12                                              (0x00000010U)
#define CSL_RAWFE_CFG_PWL1_THRX3                                               (0x00000014U)
#define CSL_RAWFE_CFG_PWL1_THRY1                                               (0x00000018U)
#define CSL_RAWFE_CFG_PWL1_THRY2                                               (0x0000001CU)
#define CSL_RAWFE_CFG_PWL1_THRY3                                               (0x00000020U)
#define CSL_RAWFE_CFG_PWL1_SLP12                                               (0x00000024U)
#define CSL_RAWFE_CFG_PWL1_SLP34                                               (0x00000028U)
#define CSL_RAWFE_CFG_PWL1_SLPSH_CLIP                                          (0x0000002CU)
#define CSL_RAWFE_CFG_PWL1_OFF1                                                (0x00000030U)
#define CSL_RAWFE_CFG_PWL1_OFF2                                                (0x00000034U)
#define CSL_RAWFE_CFG_PWL1_OFF3                                                (0x00000038U)
#define CSL_RAWFE_CFG_PWL1_OFF4                                                (0x0000003CU)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN12                                           (0x00000040U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN34                                           (0x00000044U)
#define CSL_RAWFE_CFG_PWL1_LUT                                                 (0x00000048U)
#define CSL_RAWFE_CFG_PWL1_LUTCLIP                                             (0x0000004CU)
#define CSL_RAWFE_CFG_PWL2_MASK_SH                                             (0x00000050U)
#define CSL_RAWFE_CFG_PWL2_EN                                                  (0x00000054U)
#define CSL_RAWFE_CFG_PWL2_THRX12                                              (0x00000058U)
#define CSL_RAWFE_CFG_PWL2_THRX3                                               (0x0000005CU)
#define CSL_RAWFE_CFG_PWL2_THRY1                                               (0x00000060U)
#define CSL_RAWFE_CFG_PWL2_THRY2                                               (0x00000064U)
#define CSL_RAWFE_CFG_PWL2_THRY3                                               (0x00000068U)
#define CSL_RAWFE_CFG_PWL2_SLP12                                               (0x0000006CU)
#define CSL_RAWFE_CFG_PWL2_SLP34                                               (0x00000070U)
#define CSL_RAWFE_CFG_PWL2_SLPSH_CLIP                                          (0x00000074U)
#define CSL_RAWFE_CFG_PWL2_LUT                                                 (0x00000078U)
#define CSL_RAWFE_CFG_PWL2_LUTCLIP                                             (0x0000007CU)
#define CSL_RAWFE_CFG_PWL2_OFF1                                                (0x00000080U)
#define CSL_RAWFE_CFG_PWL2_OFF2                                                (0x00000084U)
#define CSL_RAWFE_CFG_PWL2_OFF3                                                (0x00000088U)
#define CSL_RAWFE_CFG_PWL2_OFF4                                                (0x0000008CU)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN12                                           (0x00000090U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN34                                           (0x00000094U)
#define CSL_RAWFE_CFG_PWL3_MASK_SH                                             (0x00000098U)
#define CSL_RAWFE_CFG_PWL3_EN                                                  (0x0000009CU)
#define CSL_RAWFE_CFG_PWL3_THRX12                                              (0x000000A0U)
#define CSL_RAWFE_CFG_PWL3_THRX3                                               (0x000000A4U)
#define CSL_RAWFE_CFG_PWL3_THRY1                                               (0x000000A8U)
#define CSL_RAWFE_CFG_PWL3_THRY2                                               (0x000000ACU)
#define CSL_RAWFE_CFG_PWL3_THRY3                                               (0x000000B0U)
#define CSL_RAWFE_CFG_PWL3_SLP12                                               (0x000000B4U)
#define CSL_RAWFE_CFG_PWL3_SLP34                                               (0x000000B8U)
#define CSL_RAWFE_CFG_PWL3_SLPSH_CLIP                                          (0x000000BCU)
#define CSL_RAWFE_CFG_PWL3_LUT                                                 (0x000000C0U)
#define CSL_RAWFE_CFG_PWL3_LUTCLIP                                             (0x000000C4U)
#define CSL_RAWFE_CFG_PWL3_OFF1                                                (0x000000C8U)
#define CSL_RAWFE_CFG_PWL3_OFF2                                                (0x000000CCU)
#define CSL_RAWFE_CFG_PWL3_OFF3                                                (0x000000D0U)
#define CSL_RAWFE_CFG_PWL3_OFF4                                                (0x000000D4U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN12                                           (0x000000D8U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN34                                           (0x000000DCU)
#define CSL_RAWFE_CFG_WDRMRG1_CFG                                              (0x000000E0U)
#define CSL_RAWFE_CFG_WDRMRG1_GAIN                                             (0x000000E4U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK12                                           (0x000000E8U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK34                                           (0x000000ECU)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK12                                           (0x000000F0U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK34                                           (0x000000F4U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB12                                            (0x000000F8U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB34                                            (0x000000FCU)
#define CSL_RAWFE_CFG_WDRMRG1_SWB12                                            (0x00000100U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB34                                            (0x00000104U)
#define CSL_RAWFE_CFG_WDRMRG1_WDRTHR_BF                                        (0x00000108U)
#define CSL_RAWFE_CFG_WDRMRG1_AF                                               (0x0000010CU)
#define CSL_RAWFE_CFG_WDRMRG1_MA                                               (0x00000110U)
#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT                                         (0x00000114U)
#define CSL_RAWFE_CFG_WDRMRG2_CFG                                              (0x00000118U)
#define CSL_RAWFE_CFG_WDRMRG2_GAIN                                             (0x0000011CU)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK12                                           (0x00000120U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK34                                           (0x00000124U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK12                                           (0x00000128U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK34                                           (0x0000012CU)
#define CSL_RAWFE_CFG_WDRMRG2_LWB12                                            (0x00000130U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB34                                            (0x00000134U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB12                                            (0x00000138U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB34                                            (0x0000013CU)
#define CSL_RAWFE_CFG_WDRMRG2_WDRTHR_BF                                        (0x00000140U)
#define CSL_RAWFE_CFG_WDRMRG2_AF                                               (0x00000144U)
#define CSL_RAWFE_CFG_WDRMRG2_MA                                               (0x00000148U)
#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT                                         (0x0000014CU)
#define CSL_RAWFE_CFG_MRGLUT_CFG                                               (0x00000150U)
#define CSL_RAWFE_CFG_LUTDPC_CFG                                               (0x00000154U)
#define CSL_RAWFE_CFG_OTFDPC_EN                                                (0x00000158U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP1                                           (0x0000015CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP2                                           (0x00000160U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP3                                           (0x00000164U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP4                                           (0x00000168U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP5                                           (0x0000016CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP6                                           (0x00000170U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP7                                           (0x00000174U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP8                                           (0x00000178U)
#define CSL_RAWFE_CFG_LSC_CFG                                                  (0x0000017CU)
#define CSL_RAWFE_CFG_WB2_OFFSET12                                             (0x00000180U)
#define CSL_RAWFE_CFG_WB2_OFFSET34                                             (0x00000184U)
#define CSL_RAWFE_CFG_WB2_GAIN12                                               (0x00000188U)
#define CSL_RAWFE_CFG_WB2_GAIN34                                               (0x0000018CU)
#define CSL_RAWFE_CFG_H3AMUX_CFG                                               (0x00000190U)
#define CSL_RAWFE_CFG_H3ALUT_CFG                                               (0x00000194U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT                                           (0x00000198U)
#define CSL_RAWFE_CFG_DBG_CTL                                                  (0x00000200U)
#define CSL_RAWFE_CFG_DBG_HWBP                                                 (0x00000204U)
#define CSL_RAWFE_CFG_DBG_STAT1                                                (0x00000208U)
#define CSL_RAWFE_CFG_DBG_STAT2                                                (0x0000020CU)
#define CSL_RAWFE_CFG_DBG_STAT3                                                (0x00000210U)
#define CSL_RAWFE_CFG_DBG_STAT4                                                (0x00000214U)
#define CSL_RAWFE_CFG_CFA_CFG                                                  (0x00000220U)
#define CSL_RAWFE_CFG_OTFDPC_THRX12                                            (0x00000224U)
#define CSL_RAWFE_CFG_OTFDPC_THRX34                                            (0x00000228U)
#define CSL_RAWFE_CFG_OTFDPC_THRX56                                            (0x0000022CU)
#define CSL_RAWFE_CFG_OTFDPC_THRX78                                            (0x00000230U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1                                      (0x00000234U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2                                      (0x00000238U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3                                      (0x0000023CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4                                      (0x00000240U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5                                      (0x00000244U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6                                      (0x00000248U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7                                      (0x0000024CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8                                      (0x00000250U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX12                                       (0x00000254U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX34                                       (0x00000258U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX56                                       (0x0000025CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX78                                       (0x00000260U)
#define CSL_RAWFE_CFG_OTFDPC_COUNT                                             (0x00000264U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07                                            (0x00000268U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815                                           (0x0000026CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* IMAGE_CFG */

#define CSL_RAWFE_CFG_IMAGE_CFG_RSVD_1_MASK                                    (0xE0000000U)
#define CSL_RAWFE_CFG_IMAGE_CFG_RSVD_1_SHIFT                                   (0x0000001DU)
#define CSL_RAWFE_CFG_IMAGE_CFG_RSVD_1_MAX                                     (0x00000007U)

#define CSL_RAWFE_CFG_IMAGE_CFG_HEIGHT_MASK                                    (0x1FFF0000U)
#define CSL_RAWFE_CFG_IMAGE_CFG_HEIGHT_SHIFT                                   (0x00000010U)
#define CSL_RAWFE_CFG_IMAGE_CFG_HEIGHT_MAX                                     (0x00001FFFU)

#define CSL_RAWFE_CFG_IMAGE_CFG_RSVD_0_MASK                                    (0x0000E000U)
#define CSL_RAWFE_CFG_IMAGE_CFG_RSVD_0_SHIFT                                   (0x0000000DU)
#define CSL_RAWFE_CFG_IMAGE_CFG_RSVD_0_MAX                                     (0x00000007U)

#define CSL_RAWFE_CFG_IMAGE_CFG_WIDTH_MASK                                     (0x00001FFFU)
#define CSL_RAWFE_CFG_IMAGE_CFG_WIDTH_SHIFT                                    (0x00000000U)
#define CSL_RAWFE_CFG_IMAGE_CFG_WIDTH_MAX                                      (0x00001FFFU)

/* SHADOW_CFG */

#define CSL_RAWFE_CFG_SHADOW_CFG_LUT3_SHDW_EN_MASK                             (0x00000001U)
#define CSL_RAWFE_CFG_SHADOW_CFG_LUT3_SHDW_EN_SHIFT                            (0x00000000U)
#define CSL_RAWFE_CFG_SHADOW_CFG_LUT3_SHDW_EN_MAX                              (0x00000001U)

/* PWL1_MASK_SH */

#define CSL_RAWFE_CFG_PWL1_MASK_SH_RSVD_MASK                                   (0xFFF00000U)
#define CSL_RAWFE_CFG_PWL1_MASK_SH_RSVD_SHIFT                                  (0x00000014U)
#define CSL_RAWFE_CFG_PWL1_MASK_SH_RSVD_MAX                                    (0x00000FFFU)

#define CSL_RAWFE_CFG_PWL1_MASK_SH_SHIFT_MASK                                  (0x000F0000U)
#define CSL_RAWFE_CFG_PWL1_MASK_SH_SHIFT_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL1_MASK_SH_SHIFT_MAX                                   (0x0000000FU)

#define CSL_RAWFE_CFG_PWL1_MASK_SH_MASK_MASK                                   (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL1_MASK_SH_MASK_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_MASK_SH_MASK_MAX                                    (0x0000FFFFU)

/* PWL1_EN */

#define CSL_RAWFE_CFG_PWL1_EN_RSVD_MASK                                        (0xFFFFFFFEU)
#define CSL_RAWFE_CFG_PWL1_EN_RSVD_SHIFT                                       (0x00000001U)
#define CSL_RAWFE_CFG_PWL1_EN_RSVD_MAX                                         (0x7FFFFFFFU)

#define CSL_RAWFE_CFG_PWL1_EN_ENABLE_MASK                                      (0x00000001U)
#define CSL_RAWFE_CFG_PWL1_EN_ENABLE_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_EN_ENABLE_MAX                                       (0x00000001U)

/* PWL1_THRX12 */

#define CSL_RAWFE_CFG_PWL1_THRX12_THR_X2_MASK                                  (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL1_THRX12_THR_X2_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL1_THRX12_THR_X2_MAX                                   (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL1_THRX12_THR_X1_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL1_THRX12_THR_X1_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_THRX12_THR_X1_MAX                                   (0x0000FFFFU)

/* PWL1_THRX3 */

#define CSL_RAWFE_CFG_PWL1_THRX3_RSVD_MASK                                     (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL1_THRX3_RSVD_SHIFT                                    (0x00000010U)
#define CSL_RAWFE_CFG_PWL1_THRX3_RSVD_MAX                                      (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL1_THRX3_THR_X3_MASK                                   (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL1_THRX3_THR_X3_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_THRX3_THR_X3_MAX                                    (0x0000FFFFU)

/* PWL1_THRY1 */

#define CSL_RAWFE_CFG_PWL1_THRY1_RSVD_MASK                                     (0xFF000000U)
#define CSL_RAWFE_CFG_PWL1_THRY1_RSVD_SHIFT                                    (0x00000018U)
#define CSL_RAWFE_CFG_PWL1_THRY1_RSVD_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_PWL1_THRY1_THR_Y1_MASK                                   (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL1_THRY1_THR_Y1_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_THRY1_THR_Y1_MAX                                    (0x00FFFFFFU)

/* PWL1_THRY2 */

#define CSL_RAWFE_CFG_PWL1_THRY2_RSVD_MASK                                     (0xFF000000U)
#define CSL_RAWFE_CFG_PWL1_THRY2_RSVD_SHIFT                                    (0x00000018U)
#define CSL_RAWFE_CFG_PWL1_THRY2_RSVD_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_PWL1_THRY2_THR_Y2_MASK                                   (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL1_THRY2_THR_Y2_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_THRY2_THR_Y2_MAX                                    (0x00FFFFFFU)

/* PWL1_THRY3 */

#define CSL_RAWFE_CFG_PWL1_THRY3_RSVD_MASK                                     (0xFF000000U)
#define CSL_RAWFE_CFG_PWL1_THRY3_RSVD_SHIFT                                    (0x00000018U)
#define CSL_RAWFE_CFG_PWL1_THRY3_RSVD_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_PWL1_THRY3_THR_Y3_MASK                                   (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL1_THRY3_THR_Y3_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_THRY3_THR_Y3_MAX                                    (0x00FFFFFFU)

/* PWL1_SLP12 */

#define CSL_RAWFE_CFG_PWL1_SLP12_SLOPE_2_MASK                                  (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL1_SLP12_SLOPE_2_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL1_SLP12_SLOPE_2_MAX                                   (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL1_SLP12_SLOPE_1_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL1_SLP12_SLOPE_1_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_SLP12_SLOPE_1_MAX                                   (0x0000FFFFU)

/* PWL1_SLP34 */

#define CSL_RAWFE_CFG_PWL1_SLP34_SLOPE_4_MASK                                  (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL1_SLP34_SLOPE_4_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL1_SLP34_SLOPE_4_MAX                                   (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL1_SLP34_SLOPE_3_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL1_SLP34_SLOPE_3_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_SLP34_SLOPE_3_MAX                                   (0x0000FFFFU)

/* PWL1_SLPSH_CLIP */

#define CSL_RAWFE_CFG_PWL1_SLPSH_CLIP_CLIP_MASK                                (0xFFFFFF00U)
#define CSL_RAWFE_CFG_PWL1_SLPSH_CLIP_CLIP_SHIFT                               (0x00000008U)
#define CSL_RAWFE_CFG_PWL1_SLPSH_CLIP_CLIP_MAX                                 (0x00FFFFFFU)

#define CSL_RAWFE_CFG_PWL1_SLPSH_CLIP_SLOPE_SHIFT_MASK                         (0x000000FFU)
#define CSL_RAWFE_CFG_PWL1_SLPSH_CLIP_SLOPE_SHIFT_SHIFT                        (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_SLPSH_CLIP_SLOPE_SHIFT_MAX                          (0x000000FFU)

/* PWL1_OFF1 */

#define CSL_RAWFE_CFG_PWL1_OFF1_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL1_OFF1_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL1_OFF1_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL1_OFF1_OFST00_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL1_OFF1_OFST00_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_OFF1_OFST00_MAX                                     (0x00FFFFFFU)

/* PWL1_OFF2 */

#define CSL_RAWFE_CFG_PWL1_OFF2_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL1_OFF2_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL1_OFF2_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL1_OFF2_OFST01_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL1_OFF2_OFST01_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_OFF2_OFST01_MAX                                     (0x00FFFFFFU)

/* PWL1_OFF3 */

#define CSL_RAWFE_CFG_PWL1_OFF3_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL1_OFF3_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL1_OFF3_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL1_OFF3_OFST10_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL1_OFF3_OFST10_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_OFF3_OFST10_MAX                                     (0x00FFFFFFU)

/* PWL1_OFF4 */

#define CSL_RAWFE_CFG_PWL1_OFF4_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL1_OFF4_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL1_OFF4_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL1_OFF4_OFST11_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL1_OFF4_OFST11_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_OFF4_OFST11_MAX                                     (0x00FFFFFFU)

/* PWL1_WB_GAIN12 */

#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_RSVD_1_MASK                               (0xE0000000U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_RSVD_1_SHIFT                              (0x0000001DU)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_RSVD_1_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_WB_GAIN01_MASK                            (0x1FFF0000U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_WB_GAIN01_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_WB_GAIN01_MAX                             (0x00001FFFU)

#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_RSVD_0_MASK                               (0x0000E000U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_RSVD_0_SHIFT                              (0x0000000DU)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_RSVD_0_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_WB_GAIN00_MASK                            (0x00001FFFU)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_WB_GAIN00_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN12_WB_GAIN00_MAX                             (0x00001FFFU)

/* PWL1_WB_GAIN34 */

#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_RSVD_1_MASK                               (0xE0000000U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_RSVD_1_SHIFT                              (0x0000001DU)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_RSVD_1_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_WB_GAIN11_MASK                            (0x1FFF0000U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_WB_GAIN11_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_WB_GAIN11_MAX                             (0x00001FFFU)

#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_RSVD_0_MASK                               (0x0000E000U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_RSVD_0_SHIFT                              (0x0000000DU)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_RSVD_0_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_WB_GAIN10_MASK                            (0x00001FFFU)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_WB_GAIN10_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_WB_GAIN34_WB_GAIN10_MAX                             (0x00001FFFU)

/* PWL1_LUT */

#define CSL_RAWFE_CFG_PWL1_LUT_RSVD_MASK                                       (0xFFFFFFC0U)
#define CSL_RAWFE_CFG_PWL1_LUT_RSVD_SHIFT                                      (0x00000006U)
#define CSL_RAWFE_CFG_PWL1_LUT_RSVD_MAX                                        (0x03FFFFFFU)

#define CSL_RAWFE_CFG_PWL1_LUT_LUT_BITS_MASK                                   (0x0000003EU)
#define CSL_RAWFE_CFG_PWL1_LUT_LUT_BITS_SHIFT                                  (0x00000001U)
#define CSL_RAWFE_CFG_PWL1_LUT_LUT_BITS_MAX                                    (0x0000001FU)

#define CSL_RAWFE_CFG_PWL1_LUT_LUT_EN_MASK                                     (0x00000001U)
#define CSL_RAWFE_CFG_PWL1_LUT_LUT_EN_SHIFT                                    (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_LUT_LUT_EN_MAX                                      (0x00000001U)

/* PWL1_LUTCLIP */

#define CSL_RAWFE_CFG_PWL1_LUTCLIP_RSVD_MASK                                   (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL1_LUTCLIP_RSVD_SHIFT                                  (0x00000010U)
#define CSL_RAWFE_CFG_PWL1_LUTCLIP_RSVD_MAX                                    (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL1_LUTCLIP_LUTCLIP_MASK                                (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL1_LUTCLIP_LUTCLIP_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_PWL1_LUTCLIP_LUTCLIP_MAX                                 (0x0000FFFFU)

/* PWL2_MASK_SH */

#define CSL_RAWFE_CFG_PWL2_MASK_SH_RSVD_MASK                                   (0xFFF00000U)
#define CSL_RAWFE_CFG_PWL2_MASK_SH_RSVD_SHIFT                                  (0x00000014U)
#define CSL_RAWFE_CFG_PWL2_MASK_SH_RSVD_MAX                                    (0x00000FFFU)

#define CSL_RAWFE_CFG_PWL2_MASK_SH_SHIFT_MASK                                  (0x000F0000U)
#define CSL_RAWFE_CFG_PWL2_MASK_SH_SHIFT_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL2_MASK_SH_SHIFT_MAX                                   (0x0000000FU)

#define CSL_RAWFE_CFG_PWL2_MASK_SH_MASK_MASK                                   (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL2_MASK_SH_MASK_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_MASK_SH_MASK_MAX                                    (0x0000FFFFU)

/* PWL2_EN */

#define CSL_RAWFE_CFG_PWL2_EN_RSVD_MASK                                        (0xFFFFFFFEU)
#define CSL_RAWFE_CFG_PWL2_EN_RSVD_SHIFT                                       (0x00000001U)
#define CSL_RAWFE_CFG_PWL2_EN_RSVD_MAX                                         (0x7FFFFFFFU)

#define CSL_RAWFE_CFG_PWL2_EN_ENABLE_MASK                                      (0x00000001U)
#define CSL_RAWFE_CFG_PWL2_EN_ENABLE_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_EN_ENABLE_MAX                                       (0x00000001U)

/* PWL2_THRX12 */

#define CSL_RAWFE_CFG_PWL2_THRX12_THR_X2_MASK                                  (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL2_THRX12_THR_X2_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL2_THRX12_THR_X2_MAX                                   (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL2_THRX12_THR_X1_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL2_THRX12_THR_X1_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_THRX12_THR_X1_MAX                                   (0x0000FFFFU)

/* PWL2_THRX3 */

#define CSL_RAWFE_CFG_PWL2_THRX3_RSVD_MASK                                     (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL2_THRX3_RSVD_SHIFT                                    (0x00000010U)
#define CSL_RAWFE_CFG_PWL2_THRX3_RSVD_MAX                                      (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL2_THRX3_THR_X3_MASK                                   (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL2_THRX3_THR_X3_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_THRX3_THR_X3_MAX                                    (0x0000FFFFU)

/* PWL2_THRY1 */

#define CSL_RAWFE_CFG_PWL2_THRY1_RSVD_MASK                                     (0xFF000000U)
#define CSL_RAWFE_CFG_PWL2_THRY1_RSVD_SHIFT                                    (0x00000018U)
#define CSL_RAWFE_CFG_PWL2_THRY1_RSVD_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_PWL2_THRY1_THR_Y1_MASK                                   (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL2_THRY1_THR_Y1_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_THRY1_THR_Y1_MAX                                    (0x00FFFFFFU)

/* PWL2_THRY2 */

#define CSL_RAWFE_CFG_PWL2_THRY2_RSVD_MASK                                     (0xFF000000U)
#define CSL_RAWFE_CFG_PWL2_THRY2_RSVD_SHIFT                                    (0x00000018U)
#define CSL_RAWFE_CFG_PWL2_THRY2_RSVD_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_PWL2_THRY2_THR_Y2_MASK                                   (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL2_THRY2_THR_Y2_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_THRY2_THR_Y2_MAX                                    (0x00FFFFFFU)

/* PWL2_THRY3 */

#define CSL_RAWFE_CFG_PWL2_THRY3_RSVD_MASK                                     (0xFF000000U)
#define CSL_RAWFE_CFG_PWL2_THRY3_RSVD_SHIFT                                    (0x00000018U)
#define CSL_RAWFE_CFG_PWL2_THRY3_RSVD_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_PWL2_THRY3_THR_Y3_MASK                                   (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL2_THRY3_THR_Y3_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_THRY3_THR_Y3_MAX                                    (0x00FFFFFFU)

/* PWL2_SLP12 */

#define CSL_RAWFE_CFG_PWL2_SLP12_SLOPE_2_MASK                                  (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL2_SLP12_SLOPE_2_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL2_SLP12_SLOPE_2_MAX                                   (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL2_SLP12_SLOPE_1_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL2_SLP12_SLOPE_1_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_SLP12_SLOPE_1_MAX                                   (0x0000FFFFU)

/* PWL2_SLP34 */

#define CSL_RAWFE_CFG_PWL2_SLP34_SLOPE_4_MASK                                  (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL2_SLP34_SLOPE_4_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL2_SLP34_SLOPE_4_MAX                                   (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL2_SLP34_SLOPE_3_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL2_SLP34_SLOPE_3_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_SLP34_SLOPE_3_MAX                                   (0x0000FFFFU)

/* PWL2_SLPSH_CLIP */

#define CSL_RAWFE_CFG_PWL2_SLPSH_CLIP_CLIP_MASK                                (0xFFFFFF00U)
#define CSL_RAWFE_CFG_PWL2_SLPSH_CLIP_CLIP_SHIFT                               (0x00000008U)
#define CSL_RAWFE_CFG_PWL2_SLPSH_CLIP_CLIP_MAX                                 (0x00FFFFFFU)

#define CSL_RAWFE_CFG_PWL2_SLPSH_CLIP_SLOPE_SHIFT_MASK                         (0x000000FFU)
#define CSL_RAWFE_CFG_PWL2_SLPSH_CLIP_SLOPE_SHIFT_SHIFT                        (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_SLPSH_CLIP_SLOPE_SHIFT_MAX                          (0x000000FFU)

/* PWL2_LUT */

#define CSL_RAWFE_CFG_PWL2_LUT_RSVD_MASK                                       (0xFFFFFFC0U)
#define CSL_RAWFE_CFG_PWL2_LUT_RSVD_SHIFT                                      (0x00000006U)
#define CSL_RAWFE_CFG_PWL2_LUT_RSVD_MAX                                        (0x03FFFFFFU)

#define CSL_RAWFE_CFG_PWL2_LUT_LUT_BITS_MASK                                   (0x0000003EU)
#define CSL_RAWFE_CFG_PWL2_LUT_LUT_BITS_SHIFT                                  (0x00000001U)
#define CSL_RAWFE_CFG_PWL2_LUT_LUT_BITS_MAX                                    (0x0000001FU)

#define CSL_RAWFE_CFG_PWL2_LUT_LUT_EN_MASK                                     (0x00000001U)
#define CSL_RAWFE_CFG_PWL2_LUT_LUT_EN_SHIFT                                    (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_LUT_LUT_EN_MAX                                      (0x00000001U)

/* PWL2_LUTCLIP */

#define CSL_RAWFE_CFG_PWL2_LUTCLIP_RSVD_MASK                                   (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL2_LUTCLIP_RSVD_SHIFT                                  (0x00000010U)
#define CSL_RAWFE_CFG_PWL2_LUTCLIP_RSVD_MAX                                    (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL2_LUTCLIP_LUTCLIP_MASK                                (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL2_LUTCLIP_LUTCLIP_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_LUTCLIP_LUTCLIP_MAX                                 (0x0000FFFFU)

/* PWL2_OFF1 */

#define CSL_RAWFE_CFG_PWL2_OFF1_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL2_OFF1_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL2_OFF1_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL2_OFF1_OFST00_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL2_OFF1_OFST00_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_OFF1_OFST00_MAX                                     (0x00FFFFFFU)

/* PWL2_OFF2 */

#define CSL_RAWFE_CFG_PWL2_OFF2_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL2_OFF2_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL2_OFF2_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL2_OFF2_OFST01_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL2_OFF2_OFST01_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_OFF2_OFST01_MAX                                     (0x00FFFFFFU)

/* PWL2_OFF3 */

#define CSL_RAWFE_CFG_PWL2_OFF3_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL2_OFF3_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL2_OFF3_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL2_OFF3_OFST10_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL2_OFF3_OFST10_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_OFF3_OFST10_MAX                                     (0x00FFFFFFU)

/* PWL2_OFF4 */

#define CSL_RAWFE_CFG_PWL2_OFF4_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL2_OFF4_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL2_OFF4_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL2_OFF4_OFST11_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL2_OFF4_OFST11_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_OFF4_OFST11_MAX                                     (0x00FFFFFFU)

/* PWL2_WB_GAIN12 */

#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_RSVD_1_MASK                               (0xE0000000U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_RSVD_1_SHIFT                              (0x0000001DU)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_RSVD_1_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_WB_GAIN01_MASK                            (0x1FFF0000U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_WB_GAIN01_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_WB_GAIN01_MAX                             (0x00001FFFU)

#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_RSVD_0_MASK                               (0x0000E000U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_RSVD_0_SHIFT                              (0x0000000DU)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_RSVD_0_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_WB_GAIN00_MASK                            (0x00001FFFU)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_WB_GAIN00_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN12_WB_GAIN00_MAX                             (0x00001FFFU)

/* PWL2_WB_GAIN34 */

#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_RSVD_1_MASK                               (0xE0000000U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_RSVD_1_SHIFT                              (0x0000001DU)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_RSVD_1_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_WB_GAIN11_MASK                            (0x1FFF0000U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_WB_GAIN11_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_WB_GAIN11_MAX                             (0x00001FFFU)

#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_RSVD_0_MASK                               (0x0000E000U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_RSVD_0_SHIFT                              (0x0000000DU)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_RSVD_0_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_WB_GAIN10_MASK                            (0x00001FFFU)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_WB_GAIN10_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_PWL2_WB_GAIN34_WB_GAIN10_MAX                             (0x00001FFFU)

/* PWL3_MASK_SH */

#define CSL_RAWFE_CFG_PWL3_MASK_SH_RSVD_MASK                                   (0xFFF00000U)
#define CSL_RAWFE_CFG_PWL3_MASK_SH_RSVD_SHIFT                                  (0x00000014U)
#define CSL_RAWFE_CFG_PWL3_MASK_SH_RSVD_MAX                                    (0x00000FFFU)

#define CSL_RAWFE_CFG_PWL3_MASK_SH_SHIFT_MASK                                  (0x000F0000U)
#define CSL_RAWFE_CFG_PWL3_MASK_SH_SHIFT_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL3_MASK_SH_SHIFT_MAX                                   (0x0000000FU)

#define CSL_RAWFE_CFG_PWL3_MASK_SH_MASK_MASK                                   (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL3_MASK_SH_MASK_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_MASK_SH_MASK_MAX                                    (0x0000FFFFU)

/* PWL3_EN */

#define CSL_RAWFE_CFG_PWL3_EN_RSVD_MASK                                        (0xFFFFFFFEU)
#define CSL_RAWFE_CFG_PWL3_EN_RSVD_SHIFT                                       (0x00000001U)
#define CSL_RAWFE_CFG_PWL3_EN_RSVD_MAX                                         (0x7FFFFFFFU)

#define CSL_RAWFE_CFG_PWL3_EN_ENABLE_MASK                                      (0x00000001U)
#define CSL_RAWFE_CFG_PWL3_EN_ENABLE_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_EN_ENABLE_MAX                                       (0x00000001U)

/* PWL3_THRX12 */

#define CSL_RAWFE_CFG_PWL3_THRX12_THR_X2_MASK                                  (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL3_THRX12_THR_X2_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL3_THRX12_THR_X2_MAX                                   (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL3_THRX12_THR_X1_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL3_THRX12_THR_X1_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_THRX12_THR_X1_MAX                                   (0x0000FFFFU)

/* PWL3_THRX3 */

#define CSL_RAWFE_CFG_PWL3_THRX3_RSVD_MASK                                     (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL3_THRX3_RSVD_SHIFT                                    (0x00000010U)
#define CSL_RAWFE_CFG_PWL3_THRX3_RSVD_MAX                                      (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL3_THRX3_THR_X3_MASK                                   (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL3_THRX3_THR_X3_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_THRX3_THR_X3_MAX                                    (0x0000FFFFU)

/* PWL3_THRY1 */

#define CSL_RAWFE_CFG_PWL3_THRY1_RSVD_MASK                                     (0xFF000000U)
#define CSL_RAWFE_CFG_PWL3_THRY1_RSVD_SHIFT                                    (0x00000018U)
#define CSL_RAWFE_CFG_PWL3_THRY1_RSVD_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_PWL3_THRY1_THR_Y1_MASK                                   (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL3_THRY1_THR_Y1_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_THRY1_THR_Y1_MAX                                    (0x00FFFFFFU)

/* PWL3_THRY2 */

#define CSL_RAWFE_CFG_PWL3_THRY2_RSVD_MASK                                     (0xFF000000U)
#define CSL_RAWFE_CFG_PWL3_THRY2_RSVD_SHIFT                                    (0x00000018U)
#define CSL_RAWFE_CFG_PWL3_THRY2_RSVD_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_PWL3_THRY2_THR_Y2_MASK                                   (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL3_THRY2_THR_Y2_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_THRY2_THR_Y2_MAX                                    (0x00FFFFFFU)

/* PWL3_THRY3 */

#define CSL_RAWFE_CFG_PWL3_THRY3_RSVD_MASK                                     (0xFF000000U)
#define CSL_RAWFE_CFG_PWL3_THRY3_RSVD_SHIFT                                    (0x00000018U)
#define CSL_RAWFE_CFG_PWL3_THRY3_RSVD_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_PWL3_THRY3_THR_Y3_MASK                                   (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL3_THRY3_THR_Y3_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_THRY3_THR_Y3_MAX                                    (0x00FFFFFFU)

/* PWL3_SLP12 */

#define CSL_RAWFE_CFG_PWL3_SLP12_SLOPE_2_MASK                                  (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL3_SLP12_SLOPE_2_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL3_SLP12_SLOPE_2_MAX                                   (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL3_SLP12_SLOPE_1_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL3_SLP12_SLOPE_1_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_SLP12_SLOPE_1_MAX                                   (0x0000FFFFU)

/* PWL3_SLP34 */

#define CSL_RAWFE_CFG_PWL3_SLP34_SLOPE_4_MASK                                  (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL3_SLP34_SLOPE_4_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_PWL3_SLP34_SLOPE_4_MAX                                   (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL3_SLP34_SLOPE_3_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL3_SLP34_SLOPE_3_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_SLP34_SLOPE_3_MAX                                   (0x0000FFFFU)

/* PWL3_SLPSH_CLIP */

#define CSL_RAWFE_CFG_PWL3_SLPSH_CLIP_CLIP_MASK                                (0xFFFFFF00U)
#define CSL_RAWFE_CFG_PWL3_SLPSH_CLIP_CLIP_SHIFT                               (0x00000008U)
#define CSL_RAWFE_CFG_PWL3_SLPSH_CLIP_CLIP_MAX                                 (0x00FFFFFFU)

#define CSL_RAWFE_CFG_PWL3_SLPSH_CLIP_SLOPE_SHIFT_MASK                         (0x000000FFU)
#define CSL_RAWFE_CFG_PWL3_SLPSH_CLIP_SLOPE_SHIFT_SHIFT                        (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_SLPSH_CLIP_SLOPE_SHIFT_MAX                          (0x000000FFU)

/* PWL3_LUT */

#define CSL_RAWFE_CFG_PWL3_LUT_RSVD_MASK                                       (0xFFFFFFC0U)
#define CSL_RAWFE_CFG_PWL3_LUT_RSVD_SHIFT                                      (0x00000006U)
#define CSL_RAWFE_CFG_PWL3_LUT_RSVD_MAX                                        (0x03FFFFFFU)

#define CSL_RAWFE_CFG_PWL3_LUT_LUT_BITS_MASK                                   (0x0000003EU)
#define CSL_RAWFE_CFG_PWL3_LUT_LUT_BITS_SHIFT                                  (0x00000001U)
#define CSL_RAWFE_CFG_PWL3_LUT_LUT_BITS_MAX                                    (0x0000001FU)

#define CSL_RAWFE_CFG_PWL3_LUT_LUT_EN_MASK                                     (0x00000001U)
#define CSL_RAWFE_CFG_PWL3_LUT_LUT_EN_SHIFT                                    (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_LUT_LUT_EN_MAX                                      (0x00000001U)

/* PWL3_LUTCLIP */

#define CSL_RAWFE_CFG_PWL3_LUTCLIP_RSVD_MASK                                   (0xFFFF0000U)
#define CSL_RAWFE_CFG_PWL3_LUTCLIP_RSVD_SHIFT                                  (0x00000010U)
#define CSL_RAWFE_CFG_PWL3_LUTCLIP_RSVD_MAX                                    (0x0000FFFFU)

#define CSL_RAWFE_CFG_PWL3_LUTCLIP_LUTCLIP_MASK                                (0x0000FFFFU)
#define CSL_RAWFE_CFG_PWL3_LUTCLIP_LUTCLIP_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_LUTCLIP_LUTCLIP_MAX                                 (0x0000FFFFU)

/* PWL3_OFF1 */

#define CSL_RAWFE_CFG_PWL3_OFF1_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL3_OFF1_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL3_OFF1_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL3_OFF1_OFST00_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL3_OFF1_OFST00_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_OFF1_OFST00_MAX                                     (0x00FFFFFFU)

/* PWL3_OFF2 */

#define CSL_RAWFE_CFG_PWL3_OFF2_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL3_OFF2_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL3_OFF2_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL3_OFF2_OFST01_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL3_OFF2_OFST01_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_OFF2_OFST01_MAX                                     (0x00FFFFFFU)

/* PWL3_OFF3 */

#define CSL_RAWFE_CFG_PWL3_OFF3_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL3_OFF3_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL3_OFF3_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL3_OFF3_OFST10_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL3_OFF3_OFST10_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_OFF3_OFST10_MAX                                     (0x00FFFFFFU)

/* PWL3_OFF4 */

#define CSL_RAWFE_CFG_PWL3_OFF4_RSVD_MASK                                      (0xFF000000U)
#define CSL_RAWFE_CFG_PWL3_OFF4_RSVD_SHIFT                                     (0x00000018U)
#define CSL_RAWFE_CFG_PWL3_OFF4_RSVD_MAX                                       (0x000000FFU)

#define CSL_RAWFE_CFG_PWL3_OFF4_OFST11_MASK                                    (0x00FFFFFFU)
#define CSL_RAWFE_CFG_PWL3_OFF4_OFST11_SHIFT                                   (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_OFF4_OFST11_MAX                                     (0x00FFFFFFU)

/* PWL3_WB_GAIN12 */

#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_RSVD_1_MASK                               (0xE0000000U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_RSVD_1_SHIFT                              (0x0000001DU)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_RSVD_1_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_WB_GAIN01_MASK                            (0x1FFF0000U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_WB_GAIN01_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_WB_GAIN01_MAX                             (0x00001FFFU)

#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_RSVD_0_MASK                               (0x0000E000U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_RSVD_0_SHIFT                              (0x0000000DU)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_RSVD_0_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_WB_GAIN00_MASK                            (0x00001FFFU)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_WB_GAIN00_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN12_WB_GAIN00_MAX                             (0x00001FFFU)

/* PWL3_WB_GAIN34 */

#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_RSVD_1_MASK                               (0xE0000000U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_RSVD_1_SHIFT                              (0x0000001DU)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_RSVD_1_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_WB_GAIN11_MASK                            (0x1FFF0000U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_WB_GAIN11_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_WB_GAIN11_MAX                             (0x00001FFFU)

#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_RSVD_0_MASK                               (0x0000E000U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_RSVD_0_SHIFT                              (0x0000000DU)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_RSVD_0_MAX                                (0x00000007U)

#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_WB_GAIN10_MASK                            (0x00001FFFU)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_WB_GAIN10_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_PWL3_WB_GAIN34_WB_GAIN10_MAX                             (0x00001FFFU)

/* WDRMRG1_CFG */

#define CSL_RAWFE_CFG_WDRMRG1_CFG_RSVD_MASK                                    (0xFFFF8000U)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_RSVD_SHIFT                                   (0x0000000FU)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_RSVD_MAX                                     (0x0001FFFFU)

#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_WGT_SEL_MASK                             (0x00004000U)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_WGT_SEL_SHIFT                            (0x0000000EU)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_WGT_SEL_MAX                              (0x00000001U)

#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_SBIT_MASK                                (0x00003C00U)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_SBIT_SHIFT                               (0x0000000AU)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_SBIT_MAX                                 (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_LBIT_MASK                                (0x000003C0U)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_LBIT_SHIFT                               (0x00000006U)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_LBIT_MAX                                 (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_DST_MASK                                 (0x0000003EU)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_DST_SHIFT                                (0x00000001U)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_DST_MAX                                  (0x0000001FU)

#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_EN_MASK                                  (0x00000001U)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_EN_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_CFG_CFG_EN_MAX                                   (0x00000001U)

/* WDRMRG1_GAIN */

#define CSL_RAWFE_CFG_WDRMRG1_GAIN_GSHORT_MASK                                 (0xFFFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_GAIN_GSHORT_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_GAIN_GSHORT_MAX                                  (0x0000FFFFU)

#define CSL_RAWFE_CFG_WDRMRG1_GAIN_GLONG_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_WDRMRG1_GAIN_GLONG_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_GAIN_GLONG_MAX                                   (0x0000FFFFU)

/* WDRMRG1_LBLK12 */

#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_RSVD_1_MASK                               (0xF0000000U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_RSVD_1_SHIFT                              (0x0000001CU)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_RSVD_1_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_LBK01_MASK                                (0x0FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_LBK01_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_LBK01_MAX                                 (0x00000FFFU)

#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_RSVD_0_MASK                               (0x0000F000U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_RSVD_0_SHIFT                              (0x0000000CU)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_RSVD_0_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_LBK00_MASK                                (0x00000FFFU)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_LBK00_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK12_LBK00_MAX                                 (0x00000FFFU)

/* WDRMRG1_LBLK34 */

#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_RSVD_1_MASK                               (0xF0000000U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_RSVD_1_SHIFT                              (0x0000001CU)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_RSVD_1_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_LBK11_MASK                                (0x0FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_LBK11_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_LBK11_MAX                                 (0x00000FFFU)

#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_RSVD_0_MASK                               (0x0000F000U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_RSVD_0_SHIFT                              (0x0000000CU)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_RSVD_0_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_LBK10_MASK                                (0x00000FFFU)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_LBK10_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_LBLK34_LBK10_MAX                                 (0x00000FFFU)

/* WDRMRG1_SBLK12 */

#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_RSVD_1_MASK                               (0xF0000000U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_RSVD_1_SHIFT                              (0x0000001CU)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_RSVD_1_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_SBK01_MASK                                (0x0FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_SBK01_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_SBK01_MAX                                 (0x00000FFFU)

#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_RSVD_0_MASK                               (0x0000F000U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_RSVD_0_SHIFT                              (0x0000000CU)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_RSVD_0_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_SBK00_MASK                                (0x00000FFFU)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_SBK00_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK12_SBK00_MAX                                 (0x00000FFFU)

/* WDRMRG1_SBLK34 */

#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_RSVD_1_MASK                               (0xF0000000U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_RSVD_1_SHIFT                              (0x0000001CU)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_RSVD_1_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_SBK11_MASK                                (0x0FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_SBK11_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_SBK11_MAX                                 (0x00000FFFU)

#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_RSVD_0_MASK                               (0x0000F000U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_RSVD_0_SHIFT                              (0x0000000CU)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_RSVD_0_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_SBK10_MASK                                (0x00000FFFU)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_SBK10_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_SBLK34_SBK10_MAX                                 (0x00000FFFU)

/* WDRMRG1_LWB12 */

#define CSL_RAWFE_CFG_WDRMRG1_LWB12_RSVD_1_MASK                                (0xE0000000U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB12_RSVD_1_SHIFT                               (0x0000001DU)
#define CSL_RAWFE_CFG_WDRMRG1_LWB12_RSVD_1_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG1_LWB12_WB01_MASK                                  (0x1FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB12_WB01_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB12_WB01_MAX                                   (0x00001FFFU)

#define CSL_RAWFE_CFG_WDRMRG1_LWB12_RSVD_0_MASK                                (0x0000E000U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB12_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_RAWFE_CFG_WDRMRG1_LWB12_RSVD_0_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG1_LWB12_WB00_MASK                                  (0x00001FFFU)
#define CSL_RAWFE_CFG_WDRMRG1_LWB12_WB00_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB12_WB00_MAX                                   (0x00001FFFU)

/* WDRMRG1_LWB34 */

#define CSL_RAWFE_CFG_WDRMRG1_LWB34_RSVD_1_MASK                                (0xE0000000U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB34_RSVD_1_SHIFT                               (0x0000001DU)
#define CSL_RAWFE_CFG_WDRMRG1_LWB34_RSVD_1_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG1_LWB34_WB11_MASK                                  (0x1FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB34_WB11_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB34_WB11_MAX                                   (0x00001FFFU)

#define CSL_RAWFE_CFG_WDRMRG1_LWB34_RSVD_0_MASK                                (0x0000E000U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB34_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_RAWFE_CFG_WDRMRG1_LWB34_RSVD_0_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG1_LWB34_WB10_MASK                                  (0x00001FFFU)
#define CSL_RAWFE_CFG_WDRMRG1_LWB34_WB10_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_LWB34_WB10_MAX                                   (0x00001FFFU)

/* WDRMRG1_SWB12 */

#define CSL_RAWFE_CFG_WDRMRG1_SWB12_RSVD_1_MASK                                (0xE0000000U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB12_RSVD_1_SHIFT                               (0x0000001DU)
#define CSL_RAWFE_CFG_WDRMRG1_SWB12_RSVD_1_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG1_SWB12_WB01_MASK                                  (0x1FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB12_WB01_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB12_WB01_MAX                                   (0x00001FFFU)

#define CSL_RAWFE_CFG_WDRMRG1_SWB12_RSVD_0_MASK                                (0x0000E000U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB12_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_RAWFE_CFG_WDRMRG1_SWB12_RSVD_0_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG1_SWB12_WB00_MASK                                  (0x00001FFFU)
#define CSL_RAWFE_CFG_WDRMRG1_SWB12_WB00_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB12_WB00_MAX                                   (0x00001FFFU)

/* WDRMRG1_SWB34 */

#define CSL_RAWFE_CFG_WDRMRG1_SWB34_RSVD_1_MASK                                (0xE0000000U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB34_RSVD_1_SHIFT                               (0x0000001DU)
#define CSL_RAWFE_CFG_WDRMRG1_SWB34_RSVD_1_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG1_SWB34_WB11_MASK                                  (0x1FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB34_WB11_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB34_WB11_MAX                                   (0x00001FFFU)

#define CSL_RAWFE_CFG_WDRMRG1_SWB34_RSVD_0_MASK                                (0x0000E000U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB34_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_RAWFE_CFG_WDRMRG1_SWB34_RSVD_0_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG1_SWB34_WB10_MASK                                  (0x00001FFFU)
#define CSL_RAWFE_CFG_WDRMRG1_SWB34_WB10_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_SWB34_WB10_MAX                                   (0x00001FFFU)

/* WDRMRG1_WDRTHR_BF */

#define CSL_RAWFE_CFG_WDRMRG1_WDRTHR_BF_BF_MASK                                (0xFFFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_WDRTHR_BF_BF_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_WDRTHR_BF_BF_MAX                                 (0x0000FFFFU)

#define CSL_RAWFE_CFG_WDRMRG1_WDRTHR_BF_WDRTHR_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_WDRMRG1_WDRTHR_BF_WDRTHR_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_WDRTHR_BF_WDRTHR_MAX                             (0x0000FFFFU)

/* WDRMRG1_AF */

#define CSL_RAWFE_CFG_WDRMRG1_AF_RSVD_MASK                                     (0xFFC00000U)
#define CSL_RAWFE_CFG_WDRMRG1_AF_RSVD_SHIFT                                    (0x00000016U)
#define CSL_RAWFE_CFG_WDRMRG1_AF_RSVD_MAX                                      (0x000003FFU)

#define CSL_RAWFE_CFG_WDRMRG1_AF_AFE_MASK                                      (0x003F0000U)
#define CSL_RAWFE_CFG_WDRMRG1_AF_AFE_SHIFT                                     (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_AF_AFE_MAX                                       (0x0000003FU)

#define CSL_RAWFE_CFG_WDRMRG1_AF_AFM_MASK                                      (0x0000FFFFU)
#define CSL_RAWFE_CFG_WDRMRG1_AF_AFM_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_AF_AFM_MAX                                       (0x0000FFFFU)

/* WDRMRG1_MA */

#define CSL_RAWFE_CFG_WDRMRG1_MA_MAS_MASK                                      (0xFFFF0000U)
#define CSL_RAWFE_CFG_WDRMRG1_MA_MAS_SHIFT                                     (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG1_MA_MAS_MAX                                       (0x0000FFFFU)

#define CSL_RAWFE_CFG_WDRMRG1_MA_MAD_MASK                                      (0x0000FFFFU)
#define CSL_RAWFE_CFG_WDRMRG1_MA_MAD_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_MA_MAD_MAX                                       (0x0000FFFFU)

/* WDRMRG1_CLIP_SFT */

#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT_RSVD_MASK                               (0xFF800000U)
#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT_RSVD_SHIFT                              (0x00000017U)
#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT_RSVD_MAX                                (0x000001FFU)

#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT_WTSFT_MASK                              (0x00700000U)
#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT_WTSFT_SHIFT                             (0x00000014U)
#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT_WTSFT_MAX                               (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT_CLIP_MASK                               (0x000FFFFFU)
#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT_CLIP_SHIFT                              (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG1_CLIP_SFT_CLIP_MAX                                (0x000FFFFFU)

/* WDRMRG2_CFG */

#define CSL_RAWFE_CFG_WDRMRG2_CFG_RSVD_MASK                                    (0xFFFF8000U)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_RSVD_SHIFT                                   (0x0000000FU)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_RSVD_MAX                                     (0x0001FFFFU)

#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_WGT_SEL_MASK                             (0x00004000U)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_WGT_SEL_SHIFT                            (0x0000000EU)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_WGT_SEL_MAX                              (0x00000001U)

#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_SBIT_MASK                                (0x00003C00U)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_SBIT_SHIFT                               (0x0000000AU)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_SBIT_MAX                                 (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_LBIT_MASK                                (0x000003C0U)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_LBIT_SHIFT                               (0x00000006U)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_LBIT_MAX                                 (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_DST_MASK                                 (0x0000003EU)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_DST_SHIFT                                (0x00000001U)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_DST_MAX                                  (0x0000001FU)

#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_EN_MASK                                  (0x00000001U)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_EN_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_CFG_CFG_EN_MAX                                   (0x00000001U)

/* WDRMRG2_GAIN */

#define CSL_RAWFE_CFG_WDRMRG2_GAIN_GSHORT_MASK                                 (0xFFFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_GAIN_GSHORT_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_GAIN_GSHORT_MAX                                  (0x0000FFFFU)

#define CSL_RAWFE_CFG_WDRMRG2_GAIN_GLONG_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_WDRMRG2_GAIN_GLONG_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_GAIN_GLONG_MAX                                   (0x0000FFFFU)

/* WDRMRG2_LBLK12 */

#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_RSVD_1_MASK                               (0xF0000000U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_RSVD_1_SHIFT                              (0x0000001CU)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_RSVD_1_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_LBK01_MASK                                (0x0FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_LBK01_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_LBK01_MAX                                 (0x00000FFFU)

#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_RSVD_0_MASK                               (0x0000F000U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_RSVD_0_SHIFT                              (0x0000000CU)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_RSVD_0_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_LBK00_MASK                                (0x00000FFFU)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_LBK00_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK12_LBK00_MAX                                 (0x00000FFFU)

/* WDRMRG2_LBLK34 */

#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_RSVD_1_MASK                               (0xF0000000U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_RSVD_1_SHIFT                              (0x0000001CU)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_RSVD_1_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_LBK11_MASK                                (0x0FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_LBK11_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_LBK11_MAX                                 (0x00000FFFU)

#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_RSVD_0_MASK                               (0x0000F000U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_RSVD_0_SHIFT                              (0x0000000CU)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_RSVD_0_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_LBK10_MASK                                (0x00000FFFU)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_LBK10_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_LBLK34_LBK10_MAX                                 (0x00000FFFU)

/* WDRMRG2_SBLK12 */

#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_RSVD_1_MASK                               (0xF0000000U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_RSVD_1_SHIFT                              (0x0000001CU)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_RSVD_1_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_SBK01_MASK                                (0x0FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_SBK01_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_SBK01_MAX                                 (0x00000FFFU)

#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_RSVD_0_MASK                               (0x0000F000U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_RSVD_0_SHIFT                              (0x0000000CU)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_RSVD_0_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_SBK00_MASK                                (0x00000FFFU)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_SBK00_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK12_SBK00_MAX                                 (0x00000FFFU)

/* WDRMRG2_SBLK34 */

#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_RSVD_1_MASK                               (0xF0000000U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_RSVD_1_SHIFT                              (0x0000001CU)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_RSVD_1_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_SBK11_MASK                                (0x0FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_SBK11_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_SBK11_MAX                                 (0x00000FFFU)

#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_RSVD_0_MASK                               (0x0000F000U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_RSVD_0_SHIFT                              (0x0000000CU)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_RSVD_0_MAX                                (0x0000000FU)

#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_SBK10_MASK                                (0x00000FFFU)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_SBK10_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_SBLK34_SBK10_MAX                                 (0x00000FFFU)

/* WDRMRG2_LWB12 */

#define CSL_RAWFE_CFG_WDRMRG2_LWB12_RSVD_1_MASK                                (0xE0000000U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB12_RSVD_1_SHIFT                               (0x0000001DU)
#define CSL_RAWFE_CFG_WDRMRG2_LWB12_RSVD_1_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG2_LWB12_WB01_MASK                                  (0x1FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB12_WB01_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB12_WB01_MAX                                   (0x00001FFFU)

#define CSL_RAWFE_CFG_WDRMRG2_LWB12_RSVD_0_MASK                                (0x0000E000U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB12_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_RAWFE_CFG_WDRMRG2_LWB12_RSVD_0_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG2_LWB12_WB00_MASK                                  (0x00001FFFU)
#define CSL_RAWFE_CFG_WDRMRG2_LWB12_WB00_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB12_WB00_MAX                                   (0x00001FFFU)

/* WDRMRG2_LWB34 */

#define CSL_RAWFE_CFG_WDRMRG2_LWB34_RSVD_1_MASK                                (0xE0000000U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB34_RSVD_1_SHIFT                               (0x0000001DU)
#define CSL_RAWFE_CFG_WDRMRG2_LWB34_RSVD_1_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG2_LWB34_WB11_MASK                                  (0x1FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB34_WB11_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB34_WB11_MAX                                   (0x00001FFFU)

#define CSL_RAWFE_CFG_WDRMRG2_LWB34_RSVD_0_MASK                                (0x0000E000U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB34_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_RAWFE_CFG_WDRMRG2_LWB34_RSVD_0_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG2_LWB34_WB10_MASK                                  (0x00001FFFU)
#define CSL_RAWFE_CFG_WDRMRG2_LWB34_WB10_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_LWB34_WB10_MAX                                   (0x00001FFFU)

/* WDRMRG2_SWB12 */

#define CSL_RAWFE_CFG_WDRMRG2_SWB12_RSVD_1_MASK                                (0xE0000000U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB12_RSVD_1_SHIFT                               (0x0000001DU)
#define CSL_RAWFE_CFG_WDRMRG2_SWB12_RSVD_1_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG2_SWB12_WB01_MASK                                  (0x1FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB12_WB01_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB12_WB01_MAX                                   (0x00001FFFU)

#define CSL_RAWFE_CFG_WDRMRG2_SWB12_RSVD_0_MASK                                (0x0000E000U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB12_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_RAWFE_CFG_WDRMRG2_SWB12_RSVD_0_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG2_SWB12_WB00_MASK                                  (0x00001FFFU)
#define CSL_RAWFE_CFG_WDRMRG2_SWB12_WB00_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB12_WB00_MAX                                   (0x00001FFFU)

/* WDRMRG2_SWB34 */

#define CSL_RAWFE_CFG_WDRMRG2_SWB34_RSVD_1_MASK                                (0xE0000000U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB34_RSVD_1_SHIFT                               (0x0000001DU)
#define CSL_RAWFE_CFG_WDRMRG2_SWB34_RSVD_1_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG2_SWB34_WB11_MASK                                  (0x1FFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB34_WB11_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB34_WB11_MAX                                   (0x00001FFFU)

#define CSL_RAWFE_CFG_WDRMRG2_SWB34_RSVD_0_MASK                                (0x0000E000U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB34_RSVD_0_SHIFT                               (0x0000000DU)
#define CSL_RAWFE_CFG_WDRMRG2_SWB34_RSVD_0_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG2_SWB34_WB10_MASK                                  (0x00001FFFU)
#define CSL_RAWFE_CFG_WDRMRG2_SWB34_WB10_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_SWB34_WB10_MAX                                   (0x00001FFFU)

/* WDRMRG2_WDRTHR_BF */

#define CSL_RAWFE_CFG_WDRMRG2_WDRTHR_BF_BF_MASK                                (0xFFFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_WDRTHR_BF_BF_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_WDRTHR_BF_BF_MAX                                 (0x0000FFFFU)

#define CSL_RAWFE_CFG_WDRMRG2_WDRTHR_BF_WDRTHR_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_WDRMRG2_WDRTHR_BF_WDRTHR_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_WDRTHR_BF_WDRTHR_MAX                             (0x0000FFFFU)

/* WDRMRG2_AF */

#define CSL_RAWFE_CFG_WDRMRG2_AF_RSVD_MASK                                     (0xFFC00000U)
#define CSL_RAWFE_CFG_WDRMRG2_AF_RSVD_SHIFT                                    (0x00000016U)
#define CSL_RAWFE_CFG_WDRMRG2_AF_RSVD_MAX                                      (0x000003FFU)

#define CSL_RAWFE_CFG_WDRMRG2_AF_AFE_MASK                                      (0x003F0000U)
#define CSL_RAWFE_CFG_WDRMRG2_AF_AFE_SHIFT                                     (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_AF_AFE_MAX                                       (0x0000003FU)

#define CSL_RAWFE_CFG_WDRMRG2_AF_AFM_MASK                                      (0x0000FFFFU)
#define CSL_RAWFE_CFG_WDRMRG2_AF_AFM_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_AF_AFM_MAX                                       (0x0000FFFFU)

/* WDRMRG2_MA */

#define CSL_RAWFE_CFG_WDRMRG2_MA_MAS_MASK                                      (0xFFFF0000U)
#define CSL_RAWFE_CFG_WDRMRG2_MA_MAS_SHIFT                                     (0x00000010U)
#define CSL_RAWFE_CFG_WDRMRG2_MA_MAS_MAX                                       (0x0000FFFFU)

#define CSL_RAWFE_CFG_WDRMRG2_MA_MAD_MASK                                      (0x0000FFFFU)
#define CSL_RAWFE_CFG_WDRMRG2_MA_MAD_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_MA_MAD_MAX                                       (0x0000FFFFU)

/* WDRMRG2_CLIP_SFT */

#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT_RSVD_MASK                               (0xFF800000U)
#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT_RSVD_SHIFT                              (0x00000017U)
#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT_RSVD_MAX                                (0x000001FFU)

#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT_WTSFT_MASK                              (0x00700000U)
#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT_WTSFT_SHIFT                             (0x00000014U)
#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT_WTSFT_MAX                               (0x00000007U)

#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT_CLIP_MASK                               (0x000FFFFFU)
#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT_CLIP_SHIFT                              (0x00000000U)
#define CSL_RAWFE_CFG_WDRMRG2_CLIP_SFT_CLIP_MAX                                (0x000FFFFFU)

/* MRGLUT_CFG */

#define CSL_RAWFE_CFG_MRGLUT_CFG_CLIP_MASK                                     (0xFFFF0000U)
#define CSL_RAWFE_CFG_MRGLUT_CFG_CLIP_SHIFT                                    (0x00000010U)
#define CSL_RAWFE_CFG_MRGLUT_CFG_CLIP_MAX                                      (0x0000FFFFU)

#define CSL_RAWFE_CFG_MRGLUT_CFG_RSVD_MASK                                     (0x0000FFC0U)
#define CSL_RAWFE_CFG_MRGLUT_CFG_RSVD_SHIFT                                    (0x00000006U)
#define CSL_RAWFE_CFG_MRGLUT_CFG_RSVD_MAX                                      (0x000003FFU)

#define CSL_RAWFE_CFG_MRGLUT_CFG_BITS_MASK                                     (0x0000003EU)
#define CSL_RAWFE_CFG_MRGLUT_CFG_BITS_SHIFT                                    (0x00000001U)
#define CSL_RAWFE_CFG_MRGLUT_CFG_BITS_MAX                                      (0x0000001FU)

#define CSL_RAWFE_CFG_MRGLUT_CFG_EN_MASK                                       (0x00000001U)
#define CSL_RAWFE_CFG_MRGLUT_CFG_EN_SHIFT                                      (0x00000000U)
#define CSL_RAWFE_CFG_MRGLUT_CFG_EN_MAX                                        (0x00000001U)

/* LUTDPC_CFG */

#define CSL_RAWFE_CFG_LUTDPC_CFG_RSVD_MASK                                     (0xFFFFFC00U)
#define CSL_RAWFE_CFG_LUTDPC_CFG_RSVD_SHIFT                                    (0x0000000AU)
#define CSL_RAWFE_CFG_LUTDPC_CFG_RSVD_MAX                                      (0x003FFFFFU)

#define CSL_RAWFE_CFG_LUTDPC_CFG_SIZE_MASK                                     (0x000003FCU)
#define CSL_RAWFE_CFG_LUTDPC_CFG_SIZE_SHIFT                                    (0x00000002U)
#define CSL_RAWFE_CFG_LUTDPC_CFG_SIZE_MAX                                      (0x000000FFU)

#define CSL_RAWFE_CFG_LUTDPC_CFG_SEL_MASK                                      (0x00000002U)
#define CSL_RAWFE_CFG_LUTDPC_CFG_SEL_SHIFT                                     (0x00000001U)
#define CSL_RAWFE_CFG_LUTDPC_CFG_SEL_MAX                                       (0x00000001U)

#define CSL_RAWFE_CFG_LUTDPC_CFG_EN_MASK                                       (0x00000001U)
#define CSL_RAWFE_CFG_LUTDPC_CFG_EN_SHIFT                                      (0x00000000U)
#define CSL_RAWFE_CFG_LUTDPC_CFG_EN_MAX                                        (0x00000001U)

/* OTFDPC_EN */

#define CSL_RAWFE_CFG_OTFDPC_EN_RSVD_MASK                                      (0xFFFFFF00U)
#define CSL_RAWFE_CFG_OTFDPC_EN_RSVD_SHIFT                                     (0x00000008U)
#define CSL_RAWFE_CFG_OTFDPC_EN_RSVD_MAX                                       (0x00FFFFFFU)

#define CSL_RAWFE_CFG_OTFDPC_EN_LUT_MAP_MASK                                   (0x000000F0U)
#define CSL_RAWFE_CFG_OTFDPC_EN_LUT_MAP_SHIFT                                  (0x00000004U)
#define CSL_RAWFE_CFG_OTFDPC_EN_LUT_MAP_MAX                                    (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_EN_DETECT_ONLY_MASK                               (0x00000008U)
#define CSL_RAWFE_CFG_OTFDPC_EN_DETECT_ONLY_SHIFT                              (0x00000003U)
#define CSL_RAWFE_CFG_OTFDPC_EN_DETECT_ONLY_MAX                                (0x00000001U)

#define CSL_RAWFE_CFG_OTFDPC_EN_STATS_CFG_MASK                                 (0x00000006U)
#define CSL_RAWFE_CFG_OTFDPC_EN_STATS_CFG_SHIFT                                (0x00000001U)
#define CSL_RAWFE_CFG_OTFDPC_EN_STATS_CFG_MAX                                  (0x00000003U)

#define CSL_RAWFE_CFG_OTFDPC_EN_EN_MASK                                        (0x00000001U)
#define CSL_RAWFE_CFG_OTFDPC_EN_EN_SHIFT                                       (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_EN_EN_MAX                                         (0x00000001U)

/* OTFDPC_THRSLP1 */

#define CSL_RAWFE_CFG_OTFDPC_THRSLP1_RSVD_MASK                                 (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP1_RSVD_SHIFT                                (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP1_RSVD_MAX                                  (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP1_SLP1_MASK                                 (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP1_SLP1_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP1_SLP1_MAX                                  (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP1_THR1_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP1_THR1_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP1_THR1_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRSLP2 */

#define CSL_RAWFE_CFG_OTFDPC_THRSLP2_RSVD_MASK                                 (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP2_RSVD_SHIFT                                (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP2_RSVD_MAX                                  (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP2_SLP1_MASK                                 (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP2_SLP1_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP2_SLP1_MAX                                  (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP2_THR1_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP2_THR1_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP2_THR1_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRSLP3 */

#define CSL_RAWFE_CFG_OTFDPC_THRSLP3_RSVD_MASK                                 (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP3_RSVD_SHIFT                                (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP3_RSVD_MAX                                  (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP3_SLP1_MASK                                 (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP3_SLP1_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP3_SLP1_MAX                                  (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP3_THR1_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP3_THR1_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP3_THR1_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRSLP4 */

#define CSL_RAWFE_CFG_OTFDPC_THRSLP4_RSVD_MASK                                 (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP4_RSVD_SHIFT                                (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP4_RSVD_MAX                                  (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP4_SLP1_MASK                                 (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP4_SLP1_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP4_SLP1_MAX                                  (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP4_THR1_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP4_THR1_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP4_THR1_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRSLP5 */

#define CSL_RAWFE_CFG_OTFDPC_THRSLP5_RSVD_MASK                                 (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP5_RSVD_SHIFT                                (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP5_RSVD_MAX                                  (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP5_SLP1_MASK                                 (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP5_SLP1_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP5_SLP1_MAX                                  (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP5_THR1_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP5_THR1_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP5_THR1_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRSLP6 */

#define CSL_RAWFE_CFG_OTFDPC_THRSLP6_RSVD_MASK                                 (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP6_RSVD_SHIFT                                (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP6_RSVD_MAX                                  (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP6_SLP1_MASK                                 (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP6_SLP1_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP6_SLP1_MAX                                  (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP6_THR1_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP6_THR1_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP6_THR1_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRSLP7 */

#define CSL_RAWFE_CFG_OTFDPC_THRSLP7_RSVD_MASK                                 (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP7_RSVD_SHIFT                                (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP7_RSVD_MAX                                  (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP7_SLP1_MASK                                 (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP7_SLP1_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP7_SLP1_MAX                                  (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP7_THR1_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP7_THR1_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP7_THR1_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRSLP8 */

#define CSL_RAWFE_CFG_OTFDPC_THRSLP8_RSVD_MASK                                 (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP8_RSVD_SHIFT                                (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP8_RSVD_MAX                                  (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP8_SLP1_MASK                                 (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP8_SLP1_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP8_SLP1_MAX                                  (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRSLP8_THR1_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP8_THR1_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRSLP8_THR1_MAX                                  (0x0000FFFFU)

/* LSC_CFG */

#define CSL_RAWFE_CFG_LSC_CFG_RSVD_1_MASK                                      (0xFFFE0000U)
#define CSL_RAWFE_CFG_LSC_CFG_RSVD_1_SHIFT                                     (0x00000011U)
#define CSL_RAWFE_CFG_LSC_CFG_RSVD_1_MAX                                       (0x00007FFFU)

#define CSL_RAWFE_CFG_LSC_CFG_DISABLE_LUT_CFG_ERR_MASK                         (0x00010000U)
#define CSL_RAWFE_CFG_LSC_CFG_DISABLE_LUT_CFG_ERR_SHIFT                        (0x00000010U)
#define CSL_RAWFE_CFG_LSC_CFG_DISABLE_LUT_CFG_ERR_MAX                          (0x00000001U)

#define CSL_RAWFE_CFG_LSC_CFG_RSVD_0_MASK                                      (0x0000F000U)
#define CSL_RAWFE_CFG_LSC_CFG_RSVD_0_SHIFT                                     (0x0000000CU)
#define CSL_RAWFE_CFG_LSC_CFG_RSVD_0_MAX                                       (0x0000000FU)

#define CSL_RAWFE_CFG_LSC_CFG_CHN_MODE_MASK                                    (0x00000C00U)
#define CSL_RAWFE_CFG_LSC_CFG_CHN_MODE_SHIFT                                   (0x0000000AU)
#define CSL_RAWFE_CFG_LSC_CFG_CHN_MODE_MAX                                     (0x00000003U)

#define CSL_RAWFE_CFG_LSC_CFG_GAIN_FORMAT_MASK                                 (0x00000380U)
#define CSL_RAWFE_CFG_LSC_CFG_GAIN_FORMAT_SHIFT                                (0x00000007U)
#define CSL_RAWFE_CFG_LSC_CFG_GAIN_FORMAT_MAX                                  (0x00000007U)

#define CSL_RAWFE_CFG_LSC_CFG_MODE_N_MASK                                      (0x00000070U)
#define CSL_RAWFE_CFG_LSC_CFG_MODE_N_SHIFT                                     (0x00000004U)
#define CSL_RAWFE_CFG_LSC_CFG_MODE_N_MAX                                       (0x00000007U)

#define CSL_RAWFE_CFG_LSC_CFG_MODE_M_MASK                                      (0x0000000EU)
#define CSL_RAWFE_CFG_LSC_CFG_MODE_M_SHIFT                                     (0x00000001U)
#define CSL_RAWFE_CFG_LSC_CFG_MODE_M_MAX                                       (0x00000007U)

#define CSL_RAWFE_CFG_LSC_CFG_EN_MASK                                          (0x00000001U)
#define CSL_RAWFE_CFG_LSC_CFG_EN_SHIFT                                         (0x00000000U)
#define CSL_RAWFE_CFG_LSC_CFG_EN_MAX                                           (0x00000001U)

/* WB2_OFFSET12 */

#define CSL_RAWFE_CFG_WB2_OFFSET12_WB_OFST01_MASK                              (0xFFFF0000U)
#define CSL_RAWFE_CFG_WB2_OFFSET12_WB_OFST01_SHIFT                             (0x00000010U)
#define CSL_RAWFE_CFG_WB2_OFFSET12_WB_OFST01_MAX                               (0x0000FFFFU)

#define CSL_RAWFE_CFG_WB2_OFFSET12_WB_OFST00_MASK                              (0x0000FFFFU)
#define CSL_RAWFE_CFG_WB2_OFFSET12_WB_OFST00_SHIFT                             (0x00000000U)
#define CSL_RAWFE_CFG_WB2_OFFSET12_WB_OFST00_MAX                               (0x0000FFFFU)

/* WB2_OFFSET34 */

#define CSL_RAWFE_CFG_WB2_OFFSET34_WB_OFST11_MASK                              (0xFFFF0000U)
#define CSL_RAWFE_CFG_WB2_OFFSET34_WB_OFST11_SHIFT                             (0x00000010U)
#define CSL_RAWFE_CFG_WB2_OFFSET34_WB_OFST11_MAX                               (0x0000FFFFU)

#define CSL_RAWFE_CFG_WB2_OFFSET34_WB_OFST10_MASK                              (0x0000FFFFU)
#define CSL_RAWFE_CFG_WB2_OFFSET34_WB_OFST10_SHIFT                             (0x00000000U)
#define CSL_RAWFE_CFG_WB2_OFFSET34_WB_OFST10_MAX                               (0x0000FFFFU)

/* WB2_GAIN12 */

#define CSL_RAWFE_CFG_WB2_GAIN12_RSVD_1_MASK                                   (0xE0000000U)
#define CSL_RAWFE_CFG_WB2_GAIN12_RSVD_1_SHIFT                                  (0x0000001DU)
#define CSL_RAWFE_CFG_WB2_GAIN12_RSVD_1_MAX                                    (0x00000007U)

#define CSL_RAWFE_CFG_WB2_GAIN12_WB_GAIN01_MASK                                (0x1FFF0000U)
#define CSL_RAWFE_CFG_WB2_GAIN12_WB_GAIN01_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WB2_GAIN12_WB_GAIN01_MAX                                 (0x00001FFFU)

#define CSL_RAWFE_CFG_WB2_GAIN12_RSVD_0_MASK                                   (0x0000E000U)
#define CSL_RAWFE_CFG_WB2_GAIN12_RSVD_0_SHIFT                                  (0x0000000DU)
#define CSL_RAWFE_CFG_WB2_GAIN12_RSVD_0_MAX                                    (0x00000007U)

#define CSL_RAWFE_CFG_WB2_GAIN12_WB_GAIN00_MASK                                (0x00001FFFU)
#define CSL_RAWFE_CFG_WB2_GAIN12_WB_GAIN00_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WB2_GAIN12_WB_GAIN00_MAX                                 (0x00001FFFU)

/* WB2_GAIN34 */

#define CSL_RAWFE_CFG_WB2_GAIN34_RSVD_1_MASK                                   (0xE0000000U)
#define CSL_RAWFE_CFG_WB2_GAIN34_RSVD_1_SHIFT                                  (0x0000001DU)
#define CSL_RAWFE_CFG_WB2_GAIN34_RSVD_1_MAX                                    (0x00000007U)

#define CSL_RAWFE_CFG_WB2_GAIN34_WB_GAIN11_MASK                                (0x1FFF0000U)
#define CSL_RAWFE_CFG_WB2_GAIN34_WB_GAIN11_SHIFT                               (0x00000010U)
#define CSL_RAWFE_CFG_WB2_GAIN34_WB_GAIN11_MAX                                 (0x00001FFFU)

#define CSL_RAWFE_CFG_WB2_GAIN34_RSVD_0_MASK                                   (0x0000E000U)
#define CSL_RAWFE_CFG_WB2_GAIN34_RSVD_0_SHIFT                                  (0x0000000DU)
#define CSL_RAWFE_CFG_WB2_GAIN34_RSVD_0_MAX                                    (0x00000007U)

#define CSL_RAWFE_CFG_WB2_GAIN34_WB_GAIN10_MASK                                (0x00001FFFU)
#define CSL_RAWFE_CFG_WB2_GAIN34_WB_GAIN10_SHIFT                               (0x00000000U)
#define CSL_RAWFE_CFG_WB2_GAIN34_WB_GAIN10_MAX                                 (0x00001FFFU)

/* H3AMUX_CFG */

#define CSL_RAWFE_CFG_H3AMUX_CFG_RSVD_1_MASK                                   (0xFFFFFE00U)
#define CSL_RAWFE_CFG_H3AMUX_CFG_RSVD_1_SHIFT                                  (0x00000009U)
#define CSL_RAWFE_CFG_H3AMUX_CFG_RSVD_1_MAX                                    (0x007FFFFFU)

#define CSL_RAWFE_CFG_H3AMUX_CFG_PCIDSEL_MASK                                  (0x00000100U)
#define CSL_RAWFE_CFG_H3AMUX_CFG_PCIDSEL_SHIFT                                 (0x00000008U)
#define CSL_RAWFE_CFG_H3AMUX_CFG_PCIDSEL_MAX                                   (0x00000001U)

#define CSL_RAWFE_CFG_H3AMUX_CFG_RSVD_0_MASK                                   (0x000000C0U)
#define CSL_RAWFE_CFG_H3AMUX_CFG_RSVD_0_SHIFT                                  (0x00000006U)
#define CSL_RAWFE_CFG_H3AMUX_CFG_RSVD_0_MAX                                    (0x00000003U)

#define CSL_RAWFE_CFG_H3AMUX_CFG_SHIFT_MASK                                    (0x0000003CU)
#define CSL_RAWFE_CFG_H3AMUX_CFG_SHIFT_SHIFT                                   (0x00000002U)
#define CSL_RAWFE_CFG_H3AMUX_CFG_SHIFT_MAX                                     (0x0000000FU)

#define CSL_RAWFE_CFG_H3AMUX_CFG_SEL_MASK                                      (0x00000003U)
#define CSL_RAWFE_CFG_H3AMUX_CFG_SEL_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_H3AMUX_CFG_SEL_MAX                                       (0x00000003U)

/* H3ALUT_CFG */

#define CSL_RAWFE_CFG_H3ALUT_CFG_RSVD_2_MASK                                   (0xFC000000U)
#define CSL_RAWFE_CFG_H3ALUT_CFG_RSVD_2_SHIFT                                  (0x0000001AU)
#define CSL_RAWFE_CFG_H3ALUT_CFG_RSVD_2_MAX                                    (0x0000003FU)

#define CSL_RAWFE_CFG_H3ALUT_CFG_CLIP_MASK                                     (0x03FF0000U)
#define CSL_RAWFE_CFG_H3ALUT_CFG_CLIP_SHIFT                                    (0x00000010U)
#define CSL_RAWFE_CFG_H3ALUT_CFG_CLIP_MAX                                      (0x000003FFU)

#define CSL_RAWFE_CFG_H3ALUT_CFG_RSVD_MASK                                     (0x0000FFC0U)
#define CSL_RAWFE_CFG_H3ALUT_CFG_RSVD_SHIFT                                    (0x00000006U)
#define CSL_RAWFE_CFG_H3ALUT_CFG_RSVD_MAX                                      (0x000003FFU)

#define CSL_RAWFE_CFG_H3ALUT_CFG_BITS_MASK                                     (0x0000003EU)
#define CSL_RAWFE_CFG_H3ALUT_CFG_BITS_SHIFT                                    (0x00000001U)
#define CSL_RAWFE_CFG_H3ALUT_CFG_BITS_MAX                                      (0x0000001FU)

#define CSL_RAWFE_CFG_H3ALUT_CFG_EN_MASK                                       (0x00000001U)
#define CSL_RAWFE_CFG_H3ALUT_CFG_EN_SHIFT                                      (0x00000000U)
#define CSL_RAWFE_CFG_H3ALUT_CFG_EN_MAX                                        (0x00000001U)

/* RAWFE_INT_STAT */

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LUT1_CFG_ERR_MASK                         (0x00000001U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LUT1_CFG_ERR_SHIFT                        (0x00000000U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LUT1_CFG_ERR_MAX                          (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LUT2_CFG_ERR_MASK                         (0x00000002U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LUT2_CFG_ERR_SHIFT                        (0x00000001U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LUT2_CFG_ERR_MAX                          (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LUT3_CFG_ERR_MASK                         (0x00000004U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LUT3_CFG_ERR_SHIFT                        (0x00000002U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LUT3_CFG_ERR_MAX                          (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_WDR_LUT_CFG_ERR_MASK                      (0x00000008U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_WDR_LUT_CFG_ERR_SHIFT                     (0x00000003U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_WDR_LUT_CFG_ERR_MAX                       (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_H3A_LUT_CFG_ERR_MASK                      (0x00000010U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_H3A_LUT_CFG_ERR_SHIFT                     (0x00000004U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_H3A_LUT_CFG_ERR_MAX                       (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_H3A_LINE_CFG_ERR_MASK                     (0x00000020U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_H3A_LINE_CFG_ERR_SHIFT                    (0x00000005U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_H3A_LINE_CFG_ERR_MAX                      (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_H3A_ACCM_CFG_ERR_MASK                     (0x00000040U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_H3A_ACCM_CFG_ERR_SHIFT                    (0x00000006U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_H3A_ACCM_CFG_ERR_MAX                      (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_DPC_LUT_CFG_ERR_MASK                      (0x00000080U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_DPC_LUT_CFG_ERR_SHIFT                     (0x00000007U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_DPC_LUT_CFG_ERR_MAX                       (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_DPC_LINE_CFG_ERR_MASK                     (0x00000100U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_DPC_LINE_CFG_ERR_SHIFT                    (0x00000008U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_DPC_LINE_CFG_ERR_MAX                      (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LSC_CFG_ERR_MASK                          (0x00000200U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LSC_CFG_ERR_SHIFT                         (0x00000009U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_LSC_CFG_ERR_MAX                           (0x00000001U)

#define CSL_RAWFE_CFG_RAWFE_INT_STAT_DPC_STATS_READ_ERR_MASK                   (0x00000400U)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_DPC_STATS_READ_ERR_SHIFT                  (0x0000000AU)
#define CSL_RAWFE_CFG_RAWFE_INT_STAT_DPC_STATS_READ_ERR_MAX                    (0x00000001U)

/* DBG_CTL */

#define CSL_RAWFE_CFG_DBG_CTL_DBG_EN_MASK                                      (0x00000001U)
#define CSL_RAWFE_CFG_DBG_CTL_DBG_EN_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_DBG_CTL_DBG_EN_MAX                                       (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_X_Y_EN_HALT_MASK                                 (0x00000002U)
#define CSL_RAWFE_CFG_DBG_CTL_X_Y_EN_HALT_SHIFT                                (0x00000001U)
#define CSL_RAWFE_CFG_DBG_CTL_X_Y_EN_HALT_MAX                                  (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_X_Y_EN_EVENT_MASK                                (0x00000004U)
#define CSL_RAWFE_CFG_DBG_CTL_X_Y_EN_EVENT_SHIFT                               (0x00000002U)
#define CSL_RAWFE_CFG_DBG_CTL_X_Y_EN_EVENT_MAX                                 (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_VS_EN_EVENT_MASK                                 (0x00000008U)
#define CSL_RAWFE_CFG_DBG_CTL_VS_EN_EVENT_SHIFT                                (0x00000003U)
#define CSL_RAWFE_CFG_DBG_CTL_VS_EN_EVENT_MAX                                  (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_VE_EN_EVENT_MASK                                 (0x00000010U)
#define CSL_RAWFE_CFG_DBG_CTL_VE_EN_EVENT_SHIFT                                (0x00000004U)
#define CSL_RAWFE_CFG_DBG_CTL_VE_EN_EVENT_MAX                                  (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_HS_EN_EVENT_MASK                                 (0x00000020U)
#define CSL_RAWFE_CFG_DBG_CTL_HS_EN_EVENT_SHIFT                                (0x00000005U)
#define CSL_RAWFE_CFG_DBG_CTL_HS_EN_EVENT_MAX                                  (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_HE_EN_EVENT_MASK                                 (0x00000040U)
#define CSL_RAWFE_CFG_DBG_CTL_HE_EN_EVENT_SHIFT                                (0x00000006U)
#define CSL_RAWFE_CFG_DBG_CTL_HE_EN_EVENT_MAX                                  (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_LSE_SLV_STALL_EN_EVENT_MASK                      (0x00000080U)
#define CSL_RAWFE_CFG_DBG_CTL_LSE_SLV_STALL_EN_EVENT_SHIFT                     (0x00000007U)
#define CSL_RAWFE_CFG_DBG_CTL_LSE_SLV_STALL_EN_EVENT_MAX                       (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_LSE_MST_STALL_EN_EVENT_MASK                      (0x00000100U)
#define CSL_RAWFE_CFG_DBG_CTL_LSE_MST_STALL_EN_EVENT_SHIFT                     (0x00000008U)
#define CSL_RAWFE_CFG_DBG_CTL_LSE_MST_STALL_EN_EVENT_MAX                       (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_LSE_INTF_STALL_EN_EVENT_MASK                     (0x00000200U)
#define CSL_RAWFE_CFG_DBG_CTL_LSE_INTF_STALL_EN_EVENT_SHIFT                    (0x00000009U)
#define CSL_RAWFE_CFG_DBG_CTL_LSE_INTF_STALL_EN_EVENT_MAX                      (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_DPC_OTF_CORR_EN_EVENT_MASK                       (0x00000400U)
#define CSL_RAWFE_CFG_DBG_CTL_DPC_OTF_CORR_EN_EVENT_SHIFT                      (0x0000000AU)
#define CSL_RAWFE_CFG_DBG_CTL_DPC_OTF_CORR_EN_EVENT_MAX                        (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_PIPE_ADV_EN_EVENT_MASK                           (0x00000800U)
#define CSL_RAWFE_CFG_DBG_CTL_PIPE_ADV_EN_EVENT_SHIFT                          (0x0000000BU)
#define CSL_RAWFE_CFG_DBG_CTL_PIPE_ADV_EN_EVENT_MAX                            (0x00000001U)

#define CSL_RAWFE_CFG_DBG_CTL_DPC_LINE_SEL_MASK                                (0x00007000U)
#define CSL_RAWFE_CFG_DBG_CTL_DPC_LINE_SEL_SHIFT                               (0x0000000CU)
#define CSL_RAWFE_CFG_DBG_CTL_DPC_LINE_SEL_MAX                                 (0x00000007U)

/* DBG_HWBP */

#define CSL_RAWFE_CFG_DBG_HWBP_Y_POS_MASK                                      (0x1FFF0000U)
#define CSL_RAWFE_CFG_DBG_HWBP_Y_POS_SHIFT                                     (0x00000010U)
#define CSL_RAWFE_CFG_DBG_HWBP_Y_POS_MAX                                       (0x00001FFFU)

#define CSL_RAWFE_CFG_DBG_HWBP_X_POS_MASK                                      (0x00001FFFU)
#define CSL_RAWFE_CFG_DBG_HWBP_X_POS_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_CFG_DBG_HWBP_X_POS_MAX                                       (0x00001FFFU)

/* DBG_STAT1 */

#define CSL_RAWFE_CFG_DBG_STAT1_X_Y_HALT_MASK                                  (0x00000002U)
#define CSL_RAWFE_CFG_DBG_STAT1_X_Y_HALT_SHIFT                                 (0x00000001U)
#define CSL_RAWFE_CFG_DBG_STAT1_X_Y_HALT_MAX                                   (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_X_Y_EVENT_MASK                                 (0x00000004U)
#define CSL_RAWFE_CFG_DBG_STAT1_X_Y_EVENT_SHIFT                                (0x00000002U)
#define CSL_RAWFE_CFG_DBG_STAT1_X_Y_EVENT_MAX                                  (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_VS_EVENT_MASK                                  (0x00000008U)
#define CSL_RAWFE_CFG_DBG_STAT1_VS_EVENT_SHIFT                                 (0x00000003U)
#define CSL_RAWFE_CFG_DBG_STAT1_VS_EVENT_MAX                                   (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_VE_EVENT_MASK                                  (0x00000010U)
#define CSL_RAWFE_CFG_DBG_STAT1_VE_EVENT_SHIFT                                 (0x00000004U)
#define CSL_RAWFE_CFG_DBG_STAT1_VE_EVENT_MAX                                   (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_HS_EVENT_MASK                                  (0x00000020U)
#define CSL_RAWFE_CFG_DBG_STAT1_HS_EVENT_SHIFT                                 (0x00000005U)
#define CSL_RAWFE_CFG_DBG_STAT1_HS_EVENT_MAX                                   (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_HE_EVENT_MASK                                  (0x00000040U)
#define CSL_RAWFE_CFG_DBG_STAT1_HE_EVENT_SHIFT                                 (0x00000006U)
#define CSL_RAWFE_CFG_DBG_STAT1_HE_EVENT_MAX                                   (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_LSE_SLV_STALL_EVENT_MASK                       (0x00000080U)
#define CSL_RAWFE_CFG_DBG_STAT1_LSE_SLV_STALL_EVENT_SHIFT                      (0x00000007U)
#define CSL_RAWFE_CFG_DBG_STAT1_LSE_SLV_STALL_EVENT_MAX                        (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_LSE_MST_STALL_EVENT_MASK                       (0x00000100U)
#define CSL_RAWFE_CFG_DBG_STAT1_LSE_MST_STALL_EVENT_SHIFT                      (0x00000008U)
#define CSL_RAWFE_CFG_DBG_STAT1_LSE_MST_STALL_EVENT_MAX                        (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_LSE_INTF_STALL_EVENT_MASK                      (0x00000200U)
#define CSL_RAWFE_CFG_DBG_STAT1_LSE_INTF_STALL_EVENT_SHIFT                     (0x00000009U)
#define CSL_RAWFE_CFG_DBG_STAT1_LSE_INTF_STALL_EVENT_MAX                       (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_DPC_OTF_CORR_EVENT_MASK                        (0x00000400U)
#define CSL_RAWFE_CFG_DBG_STAT1_DPC_OTF_CORR_EVENT_SHIFT                       (0x0000000AU)
#define CSL_RAWFE_CFG_DBG_STAT1_DPC_OTF_CORR_EVENT_MAX                         (0x00000001U)

#define CSL_RAWFE_CFG_DBG_STAT1_PIPE_ADV_EVENT_MASK                            (0x00000800U)
#define CSL_RAWFE_CFG_DBG_STAT1_PIPE_ADV_EVENT_SHIFT                           (0x0000000BU)
#define CSL_RAWFE_CFG_DBG_STAT1_PIPE_ADV_EVENT_MAX                             (0x00000001U)

/* DBG_STAT2 */

#define CSL_RAWFE_CFG_DBG_STAT2_Y_POS_MASK                                     (0x1FFF0000U)
#define CSL_RAWFE_CFG_DBG_STAT2_Y_POS_SHIFT                                    (0x00000010U)
#define CSL_RAWFE_CFG_DBG_STAT2_Y_POS_MAX                                      (0x00001FFFU)

#define CSL_RAWFE_CFG_DBG_STAT2_X_POS_MASK                                     (0x00001FFFU)
#define CSL_RAWFE_CFG_DBG_STAT2_X_POS_SHIFT                                    (0x00000000U)
#define CSL_RAWFE_CFG_DBG_STAT2_X_POS_MAX                                      (0x00001FFFU)

/* DBG_STAT3 */

#define CSL_RAWFE_CFG_DBG_STAT3_DPC_LINE_RAM_CTL_MASK                          (0x00000003U)
#define CSL_RAWFE_CFG_DBG_STAT3_DPC_LINE_RAM_CTL_SHIFT                         (0x00000000U)
#define CSL_RAWFE_CFG_DBG_STAT3_DPC_LINE_RAM_CTL_MAX                           (0x00000003U)

#define CSL_RAWFE_CFG_DBG_STAT3_DPC_MIRROR_STAT_MASK                           (0xFFFFFFFCU)
#define CSL_RAWFE_CFG_DBG_STAT3_DPC_MIRROR_STAT_SHIFT                          (0x00000002U)
#define CSL_RAWFE_CFG_DBG_STAT3_DPC_MIRROR_STAT_MAX                            (0x3FFFFFFFU)

/* DBG_STAT4 */

#define CSL_RAWFE_CFG_DBG_STAT4_LSC_DBG_STAT_MASK                              (0xFFFFFFFFU)
#define CSL_RAWFE_CFG_DBG_STAT4_LSC_DBG_STAT_SHIFT                             (0x00000000U)
#define CSL_RAWFE_CFG_DBG_STAT4_LSC_DBG_STAT_MAX                               (0xFFFFFFFFU)

/* CFA_CFG */

#define CSL_RAWFE_CFG_CFA_CFG_RSVD_MASK                                        (0xFFFFFFE0U)
#define CSL_RAWFE_CFG_CFA_CFG_RSVD_SHIFT                                       (0x00000005U)
#define CSL_RAWFE_CFG_CFA_CFG_RSVD_MAX                                         (0x07FFFFFFU)

#define CSL_RAWFE_CFG_CFA_CFG_PHASE_MASK                                       (0x0000001CU)
#define CSL_RAWFE_CFG_CFA_CFG_PHASE_SHIFT                                      (0x00000002U)
#define CSL_RAWFE_CFG_CFA_CFG_PHASE_MAX                                        (0x00000007U)

#define CSL_RAWFE_CFG_CFA_CFG_MODE_MASK                                        (0x00000003U)
#define CSL_RAWFE_CFG_CFA_CFG_MODE_SHIFT                                       (0x00000000U)
#define CSL_RAWFE_CFG_CFA_CFG_MODE_MAX                                         (0x00000003U)

/* OTFDPC_THRX12 */

#define CSL_RAWFE_CFG_OTFDPC_THRX12_THRX2_MASK                                 (0xFFFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRX12_THRX2_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRX12_THRX2_MAX                                  (0x0000FFFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRX12_THRX1_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRX12_THRX1_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRX12_THRX1_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRX34 */

#define CSL_RAWFE_CFG_OTFDPC_THRX34_THRX4_MASK                                 (0xFFFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRX34_THRX4_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRX34_THRX4_MAX                                  (0x0000FFFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRX34_THRX3_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRX34_THRX3_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRX34_THRX3_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRX56 */

#define CSL_RAWFE_CFG_OTFDPC_THRX56_THRX6_MASK                                 (0xFFFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRX56_THRX6_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRX56_THRX6_MAX                                  (0x0000FFFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRX56_THRX5_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRX56_THRX5_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRX56_THRX5_MAX                                  (0x0000FFFFU)

/* OTFDPC_THRX78 */

#define CSL_RAWFE_CFG_OTFDPC_THRX78_THRX8_MASK                                 (0xFFFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_THRX78_THRX8_SHIFT                                (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_THRX78_THRX8_MAX                                  (0x0000FFFFU)

#define CSL_RAWFE_CFG_OTFDPC_THRX78_THRX7_MASK                                 (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_THRX78_THRX7_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_THRX78_THRX7_MAX                                  (0x0000FFFFU)

/* OTFDPC_LUT2_THRSLP1 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1_RSVD_MASK                            (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1_RSVD_SHIFT                           (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1_RSVD_MAX                             (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1_SLP1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1_SLP1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1_SLP1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1_THR1_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1_THR1_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP1_THR1_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRSLP2 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2_RSVD_MASK                            (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2_RSVD_SHIFT                           (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2_RSVD_MAX                             (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2_SLP1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2_SLP1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2_SLP1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2_THR1_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2_THR1_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP2_THR1_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRSLP3 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3_RSVD_MASK                            (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3_RSVD_SHIFT                           (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3_RSVD_MAX                             (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3_SLP1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3_SLP1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3_SLP1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3_THR1_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3_THR1_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP3_THR1_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRSLP4 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4_RSVD_MASK                            (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4_RSVD_SHIFT                           (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4_RSVD_MAX                             (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4_SLP1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4_SLP1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4_SLP1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4_THR1_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4_THR1_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP4_THR1_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRSLP5 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5_RSVD_MASK                            (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5_RSVD_SHIFT                           (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5_RSVD_MAX                             (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5_SLP1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5_SLP1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5_SLP1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5_THR1_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5_THR1_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP5_THR1_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRSLP6 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6_RSVD_MASK                            (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6_RSVD_SHIFT                           (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6_RSVD_MAX                             (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6_SLP1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6_SLP1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6_SLP1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6_THR1_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6_THR1_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP6_THR1_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRSLP7 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7_RSVD_MASK                            (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7_RSVD_SHIFT                           (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7_RSVD_MAX                             (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7_SLP1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7_SLP1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7_SLP1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7_THR1_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7_THR1_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP7_THR1_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRSLP8 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8_RSVD_MASK                            (0xF0000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8_RSVD_SHIFT                           (0x0000001CU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8_RSVD_MAX                             (0x0000000FU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8_SLP1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8_SLP1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8_SLP1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8_THR1_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8_THR1_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRSLP8_THR1_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRX12 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX12_THRX2_MASK                            (0xFFFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX12_THRX2_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX12_THRX2_MAX                             (0x0000FFFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX12_THRX1_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX12_THRX1_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX12_THRX1_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRX34 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX34_THRX4_MASK                            (0xFFFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX34_THRX4_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX34_THRX4_MAX                             (0x0000FFFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX34_THRX3_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX34_THRX3_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX34_THRX3_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRX56 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX56_THRX6_MASK                            (0xFFFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX56_THRX6_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX56_THRX6_MAX                             (0x0000FFFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX56_THRX5_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX56_THRX5_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX56_THRX5_MAX                             (0x0000FFFFU)

/* OTFDPC_LUT2_THRX78 */

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX78_THRX8_MASK                            (0xFFFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX78_THRX8_SHIFT                           (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX78_THRX8_MAX                             (0x0000FFFFU)

#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX78_THRX7_MASK                            (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX78_THRX7_SHIFT                           (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_LUT2_THRX78_THRX7_MAX                             (0x0000FFFFU)

/* OTFDPC_COUNT */

#define CSL_RAWFE_CFG_OTFDPC_COUNT_RSVD_MASK                                   (0xFFFF0000U)
#define CSL_RAWFE_CFG_OTFDPC_COUNT_RSVD_SHIFT                                  (0x00000010U)
#define CSL_RAWFE_CFG_OTFDPC_COUNT_RSVD_MAX                                    (0x0000FFFFU)

#define CSL_RAWFE_CFG_OTFDPC_COUNT_COUNT_MASK                                  (0x0000FFFFU)
#define CSL_RAWFE_CFG_OTFDPC_COUNT_COUNT_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_OTFDPC_COUNT_COUNT_MAX                                   (0x0000FFFFU)

/* LSC_LUT_MAP07 */

#define CSL_RAWFE_CFG_LSC_LUT_MAP07_RSVD_MASK                                  (0xFF000000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_RSVD_SHIFT                                 (0x00000018U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_RSVD_MAX                                   (0x000000FFU)

#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP7_MASK                                  (0x00E00000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP7_SHIFT                                 (0x00000015U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP7_MAX                                   (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP6_MASK                                  (0x001C0000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP6_SHIFT                                 (0x00000012U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP6_MAX                                   (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP5_MASK                                  (0x00038000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP5_SHIFT                                 (0x0000000FU)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP5_MAX                                   (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP4_MASK                                  (0x00007000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP4_SHIFT                                 (0x0000000CU)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP4_MAX                                   (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP3_MASK                                  (0x00000E00U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP3_SHIFT                                 (0x00000009U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP3_MAX                                   (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP2_MASK                                  (0x000001C0U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP2_SHIFT                                 (0x00000006U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP2_MAX                                   (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP1_MASK                                  (0x00000038U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP1_SHIFT                                 (0x00000003U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP1_MAX                                   (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP0_MASK                                  (0x00000007U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP0_SHIFT                                 (0x00000000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP07_MAP0_MAX                                   (0x00000007U)

/* LSC_LUT_MAP815 */

#define CSL_RAWFE_CFG_LSC_LUT_MAP815_RSVD_MASK                                 (0xFF000000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_RSVD_SHIFT                                (0x00000018U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_RSVD_MAX                                  (0x000000FFU)

#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP15_MASK                                (0x00E00000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP15_SHIFT                               (0x00000015U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP15_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP14_MASK                                (0x001C0000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP14_SHIFT                               (0x00000012U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP14_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP13_MASK                                (0x00038000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP13_SHIFT                               (0x0000000FU)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP13_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP12_MASK                                (0x00007000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP12_SHIFT                               (0x0000000CU)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP12_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP11_MASK                                (0x00000E00U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP11_SHIFT                               (0x00000009U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP11_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP10_MASK                                (0x000001C0U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP10_SHIFT                               (0x00000006U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP10_MAX                                 (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP9_MASK                                 (0x00000038U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP9_SHIFT                                (0x00000003U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP9_MAX                                  (0x00000007U)

#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP8_MASK                                 (0x00000007U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP8_SHIFT                                (0x00000000U)
#define CSL_RAWFE_CFG_LSC_LUT_MAP815_MAP8_MAX                                  (0x00000007U)

/**************************************************************************
* Hardware Region  :  h3a register descriptions
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t PID;
    volatile uint32_t PCR;
    volatile uint32_t AFPAX1;
    volatile uint32_t AFPAX2;
    volatile uint32_t AFPAXSTART;
    volatile uint32_t AFIIRSH;
    volatile uint32_t AFBUFST;
    volatile uint32_t AFCOEF010;
    volatile uint32_t AFCOEF032;
    volatile uint32_t AFCOEF054;
    volatile uint32_t AFCOEF076;
    volatile uint32_t AFCOEF098;
    volatile uint32_t AFCOEF0010;
    volatile uint32_t AFCOEF110;
    volatile uint32_t AFCOEF132;
    volatile uint32_t AFCOEF154;
    volatile uint32_t AFCOEF176;
    volatile uint32_t AFCOEF198;
    volatile uint32_t AFCOEF1010;
    volatile uint32_t AEWWIN1;
    volatile uint32_t AEWINSTART;
    volatile uint32_t AEWINBLK;
    volatile uint32_t AEWSUBWIN;
    volatile uint32_t AEWBUFST;
    volatile uint32_t AEWCFG;
    volatile uint32_t LINE_START;
    volatile uint32_t VFV_CFG1;
    volatile uint32_t VFV_CFG2;
    volatile uint32_t VFV_CFG3;
    volatile uint32_t VFV_CFG4;
    volatile uint32_t HVF_THR;
    volatile uint32_t ADVANCED;
} CSL_rawfe_h3a_cfgRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_H3A_CFG_PID                                              (0x00000000U)
#define CSL_RAWFE_H3A_CFG_PCR                                              (0x00000004U)
#define CSL_RAWFE_H3A_CFG_AFPAX1                                           (0x00000008U)
#define CSL_RAWFE_H3A_CFG_AFPAX2                                           (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFPAXSTART                                       (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFIIRSH                                          (0x00000014U)
#define CSL_RAWFE_H3A_CFG_AFBUFST                                          (0x00000018U)
#define CSL_RAWFE_H3A_CFG_AFCOEF010                                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF032                                        (0x00000020U)
#define CSL_RAWFE_H3A_CFG_AFCOEF054                                        (0x00000024U)
#define CSL_RAWFE_H3A_CFG_AFCOEF076                                        (0x00000028U)
#define CSL_RAWFE_H3A_CFG_AFCOEF098                                        (0x0000002CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF0010                                       (0x00000030U)
#define CSL_RAWFE_H3A_CFG_AFCOEF110                                        (0x00000034U)
#define CSL_RAWFE_H3A_CFG_AFCOEF132                                        (0x00000038U)
#define CSL_RAWFE_H3A_CFG_AFCOEF154                                        (0x0000003CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF176                                        (0x00000040U)
#define CSL_RAWFE_H3A_CFG_AFCOEF198                                        (0x00000044U)
#define CSL_RAWFE_H3A_CFG_AFCOEF1010                                       (0x00000048U)
#define CSL_RAWFE_H3A_CFG_AEWWIN1                                          (0x0000004CU)
#define CSL_RAWFE_H3A_CFG_AEWINSTART                                       (0x00000050U)
#define CSL_RAWFE_H3A_CFG_AEWINBLK                                         (0x00000054U)
#define CSL_RAWFE_H3A_CFG_AEWSUBWIN                                        (0x00000058U)
#define CSL_RAWFE_H3A_CFG_AEWBUFST                                         (0x0000005CU)
#define CSL_RAWFE_H3A_CFG_AEWCFG                                           (0x00000060U)
#define CSL_RAWFE_H3A_CFG_LINE_START                                       (0x00000064U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG1                                         (0x00000068U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG2                                         (0x0000006CU)
#define CSL_RAWFE_H3A_CFG_VFV_CFG3                                         (0x00000070U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG4                                         (0x00000074U)
#define CSL_RAWFE_H3A_CFG_HVF_THR                                          (0x00000078U)
#define CSL_RAWFE_H3A_CFG_ADVANCED                                         (0x0000007CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* H3A_PID */

#define CSL_RAWFE_H3A_CFG_PID_MINOR_MASK                                   (0x0000003FU)
#define CSL_RAWFE_H3A_CFG_PID_MINOR_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_H3A_CFG_PID_MINOR_MAX                                    (0x0000003FU)

#define CSL_RAWFE_H3A_CFG_PID_MAJOR_MASK                                   (0x00000700U)
#define CSL_RAWFE_H3A_CFG_PID_MAJOR_SHIFT                                  (0x00000008U)
#define CSL_RAWFE_H3A_CFG_PID_MAJOR_MAX                                    (0x00000007U)

#define CSL_RAWFE_H3A_CFG_PID_RTL_MASK                                     (0x0000F800U)
#define CSL_RAWFE_H3A_CFG_PID_RTL_SHIFT                                    (0x0000000BU)
#define CSL_RAWFE_H3A_CFG_PID_RTL_MAX                                      (0x0000001FU)

#define CSL_RAWFE_H3A_CFG_PID_FUNC_MASK                                    (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_PID_FUNC_SHIFT                                   (0x00000010U)
#define CSL_RAWFE_H3A_CFG_PID_FUNC_MAX                                     (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_PID_SCHEME_MASK                                  (0xC0000000U)
#define CSL_RAWFE_H3A_CFG_PID_SCHEME_SHIFT                                 (0x0000001EU)
#define CSL_RAWFE_H3A_CFG_PID_SCHEME_MAX                                   (0x00000003U)

#define CSL_RAWFE_H3A_CFG_PID_RESERVED_MASK                                (0x000000C0U)
#define CSL_RAWFE_H3A_CFG_PID_RESERVED_SHIFT                               (0x00000006U)
#define CSL_RAWFE_H3A_CFG_PID_RESERVED_MAX                                 (0x00000003U)

#define CSL_RAWFE_H3A_CFG_PID_RESERVED1_MASK                               (0x30000000U)
#define CSL_RAWFE_H3A_CFG_PID_RESERVED1_SHIFT                              (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_PID_RESERVED1_MAX                                (0x00000003U)

/* H3A_PCR */

#define CSL_RAWFE_H3A_CFG_PCR_AF_EN_MASK                                   (0x00000001U)
#define CSL_RAWFE_H3A_CFG_PCR_AF_EN_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_H3A_CFG_PCR_AF_EN_MAX                                    (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_AF_ALAW_EN_MASK                              (0x00000002U)
#define CSL_RAWFE_H3A_CFG_PCR_AF_ALAW_EN_SHIFT                             (0x00000001U)
#define CSL_RAWFE_H3A_CFG_PCR_AF_ALAW_EN_MAX                               (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_AF_MED_EN_MASK                               (0x00000004U)
#define CSL_RAWFE_H3A_CFG_PCR_AF_MED_EN_SHIFT                              (0x00000002U)
#define CSL_RAWFE_H3A_CFG_PCR_AF_MED_EN_MAX                                (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_MED_TH_MASK                                  (0x000007F8U)
#define CSL_RAWFE_H3A_CFG_PCR_MED_TH_SHIFT                                 (0x00000003U)
#define CSL_RAWFE_H3A_CFG_PCR_MED_TH_MAX                                   (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_PCR_FVMODE_MASK                                  (0x00004000U)
#define CSL_RAWFE_H3A_CFG_PCR_FVMODE_SHIFT                                 (0x0000000EU)
#define CSL_RAWFE_H3A_CFG_PCR_FVMODE_MAX                                   (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_BUSYAF_MASK                                  (0x00008000U)
#define CSL_RAWFE_H3A_CFG_PCR_BUSYAF_SHIFT                                 (0x0000000FU)
#define CSL_RAWFE_H3A_CFG_PCR_BUSYAF_MAX                                   (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_AEW_EN_MASK                                  (0x00010000U)
#define CSL_RAWFE_H3A_CFG_PCR_AEW_EN_SHIFT                                 (0x00000010U)
#define CSL_RAWFE_H3A_CFG_PCR_AEW_EN_MAX                                   (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_AEW_ALAW_EN_MASK                             (0x00020000U)
#define CSL_RAWFE_H3A_CFG_PCR_AEW_ALAW_EN_SHIFT                            (0x00000011U)
#define CSL_RAWFE_H3A_CFG_PCR_AEW_ALAW_EN_MAX                              (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_BUSYAEAWB_MASK                               (0x00040000U)
#define CSL_RAWFE_H3A_CFG_PCR_BUSYAEAWB_SHIFT                              (0x00000012U)
#define CSL_RAWFE_H3A_CFG_PCR_BUSYAEAWB_MAX                                (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_AEW_MED_EN_MASK                              (0x00080000U)
#define CSL_RAWFE_H3A_CFG_PCR_AEW_MED_EN_SHIFT                             (0x00000013U)
#define CSL_RAWFE_H3A_CFG_PCR_AEW_MED_EN_MAX                               (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_AF_VF_EN_MASK                                (0x00100000U)
#define CSL_RAWFE_H3A_CFG_PCR_AF_VF_EN_SHIFT                               (0x00000014U)
#define CSL_RAWFE_H3A_CFG_PCR_AF_VF_EN_MAX                                 (0x00000001U)

#define CSL_RAWFE_H3A_CFG_PCR_AVE2LMT_MASK                                 (0xFFC00000U)
#define CSL_RAWFE_H3A_CFG_PCR_AVE2LMT_SHIFT                                (0x00000016U)
#define CSL_RAWFE_H3A_CFG_PCR_AVE2LMT_MAX                                  (0x000003FFU)

#define CSL_RAWFE_H3A_CFG_PCR_RGBPOS_MASK                                  (0x00003800U)
#define CSL_RAWFE_H3A_CFG_PCR_RGBPOS_SHIFT                                 (0x0000000BU)
#define CSL_RAWFE_H3A_CFG_PCR_RGBPOS_MAX                                   (0x00000007U)

#define CSL_RAWFE_H3A_CFG_PCR_OVF_MASK                                     (0x00200000U)
#define CSL_RAWFE_H3A_CFG_PCR_OVF_SHIFT                                    (0x00000015U)
#define CSL_RAWFE_H3A_CFG_PCR_OVF_MAX                                      (0x00000001U)

/* H3A_AFPAX1 */

#define CSL_RAWFE_H3A_CFG_AFPAX1_PAXH_MASK                                 (0x000000FFU)
#define CSL_RAWFE_H3A_CFG_AFPAX1_PAXH_SHIFT                                (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFPAX1_PAXH_MAX                                  (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_AFPAX1_PAXW_MASK                                 (0x00FF0000U)
#define CSL_RAWFE_H3A_CFG_AFPAX1_PAXW_SHIFT                                (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFPAX1_PAXW_MAX                                  (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_AFPAX1_RESERVED_MASK                             (0x0000FF00U)
#define CSL_RAWFE_H3A_CFG_AFPAX1_RESERVED_SHIFT                            (0x00000008U)
#define CSL_RAWFE_H3A_CFG_AFPAX1_RESERVED_MAX                              (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_AFPAX1_RESERVED1_MASK                            (0xFF000000U)
#define CSL_RAWFE_H3A_CFG_AFPAX1_RESERVED1_SHIFT                           (0x00000018U)
#define CSL_RAWFE_H3A_CFG_AFPAX1_RESERVED1_MAX                             (0x000000FFU)

/* H3A_AFPAX2 */

#define CSL_RAWFE_H3A_CFG_AFPAX2_PAXHC_MASK                                (0x0000003FU)
#define CSL_RAWFE_H3A_CFG_AFPAX2_PAXHC_SHIFT                               (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFPAX2_PAXHC_MAX                                 (0x0000003FU)

#define CSL_RAWFE_H3A_CFG_AFPAX2_PAXVC_MASK                                (0x00001FC0U)
#define CSL_RAWFE_H3A_CFG_AFPAX2_PAXVC_SHIFT                               (0x00000006U)
#define CSL_RAWFE_H3A_CFG_AFPAX2_PAXVC_MAX                                 (0x0000007FU)

#define CSL_RAWFE_H3A_CFG_AFPAX2_AFINCV_MASK                               (0x0001E000U)
#define CSL_RAWFE_H3A_CFG_AFPAX2_AFINCV_SHIFT                              (0x0000000DU)
#define CSL_RAWFE_H3A_CFG_AFPAX2_AFINCV_MAX                                (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFPAX2_AFINCH_MASK                               (0x001E0000U)
#define CSL_RAWFE_H3A_CFG_AFPAX2_AFINCH_SHIFT                              (0x00000011U)
#define CSL_RAWFE_H3A_CFG_AFPAX2_AFINCH_MAX                                (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFPAX2_RESERVED_MASK                             (0xFFE00000U)
#define CSL_RAWFE_H3A_CFG_AFPAX2_RESERVED_SHIFT                            (0x00000015U)
#define CSL_RAWFE_H3A_CFG_AFPAX2_RESERVED_MAX                              (0x000007FFU)

/* H3A_AFPAXSTART */

#define CSL_RAWFE_H3A_CFG_AFPAXSTART_PAXSV_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFPAXSTART_PAXSV_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFPAXSTART_PAXSV_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFPAXSTART_PAXSH_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFPAXSTART_PAXSH_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFPAXSTART_PAXSH_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFPAXSTART_RESERVED_MASK                         (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFPAXSTART_RESERVED_SHIFT                        (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFPAXSTART_RESERVED_MAX                          (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFPAXSTART_RESERVED1_MASK                        (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFPAXSTART_RESERVED1_SHIFT                       (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFPAXSTART_RESERVED1_MAX                         (0x0000000FU)

/* H3A_AFIIRSH */

#define CSL_RAWFE_H3A_CFG_AFIIRSH_IIRSH_MASK                               (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFIIRSH_IIRSH_SHIFT                              (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFIIRSH_IIRSH_MAX                                (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFIIRSH_RESERVED_MASK                            (0xFFFFF000U)
#define CSL_RAWFE_H3A_CFG_AFIIRSH_RESERVED_SHIFT                           (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFIIRSH_RESERVED_MAX                             (0x000FFFFFU)

/* H3A_AFBUFST */

#define CSL_RAWFE_H3A_CFG_AFBUFST_AFBUFST_MASK                             (0xFFFFFFE0U)
#define CSL_RAWFE_H3A_CFG_AFBUFST_AFBUFST_SHIFT                            (0x00000005U)
#define CSL_RAWFE_H3A_CFG_AFBUFST_AFBUFST_MAX                              (0x07FFFFFFU)

#define CSL_RAWFE_H3A_CFG_AFBUFST_RESERVED_MASK                            (0x0000001FU)
#define CSL_RAWFE_H3A_CFG_AFBUFST_RESERVED_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFBUFST_RESERVED_MAX                             (0x0000001FU)

/* H3A_AFCOEF010 */

#define CSL_RAWFE_H3A_CFG_AFCOEF010_COEFF0_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF010_COEFF0_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF010_COEFF0_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF010_COEFF1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF010_COEFF1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF010_COEFF1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF010_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF010_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF010_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF010_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF010_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF010_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF032 */

#define CSL_RAWFE_H3A_CFG_AFCOEF032_COEFF2_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF032_COEFF2_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF032_COEFF2_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF032_COEFF3_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF032_COEFF3_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF032_COEFF3_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF032_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF032_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF032_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF032_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF032_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF032_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF054 */

#define CSL_RAWFE_H3A_CFG_AFCOEF054_COEFF4_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF054_COEFF4_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF054_COEFF4_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF054_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF054_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF054_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF054_COEFF5_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF054_COEFF5_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF054_COEFF5_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF054_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF054_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF054_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF076 */

#define CSL_RAWFE_H3A_CFG_AFCOEF076_COEFF6_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF076_COEFF6_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF076_COEFF6_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF076_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF076_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF076_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF076_COEFF7_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF076_COEFF7_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF076_COEFF7_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF076_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF076_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF076_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF098 */

#define CSL_RAWFE_H3A_CFG_AFCOEF098_COEFF8_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF098_COEFF8_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF098_COEFF8_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF098_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF098_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF098_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF098_COEFF9_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF098_COEFF9_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF098_COEFF9_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF098_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF098_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF098_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF0010 */

#define CSL_RAWFE_H3A_CFG_AFCOEF0010_COEFF10_MASK                          (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF0010_COEFF10_SHIFT                         (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF0010_COEFF10_MAX                           (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF0010_RESERVED_MASK                         (0xFFFFF000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF0010_RESERVED_SHIFT                        (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF0010_RESERVED_MAX                          (0x000FFFFFU)

/* H3A_AFCOEF110 */

#define CSL_RAWFE_H3A_CFG_AFCOEF110_COEFF0_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF110_COEFF0_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF110_COEFF0_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF110_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF110_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF110_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF110_COEFF1_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF110_COEFF1_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF110_COEFF1_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF110_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF110_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF110_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF132 */

#define CSL_RAWFE_H3A_CFG_AFCOEF132_COEFF2_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF132_COEFF2_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF132_COEFF2_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF132_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF132_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF132_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF132_COEFF3_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF132_COEFF3_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF132_COEFF3_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF132_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF132_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF132_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF154 */

#define CSL_RAWFE_H3A_CFG_AFCOEF154_COEFF4_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF154_COEFF4_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF154_COEFF4_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF154_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF154_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF154_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF154_COEFF5_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF154_COEFF5_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF154_COEFF5_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF154_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF154_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF154_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF176 */

#define CSL_RAWFE_H3A_CFG_AFCOEF176_COEFF6_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF176_COEFF6_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF176_COEFF6_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF176_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF176_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF176_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF176_COEFF7_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF176_COEFF7_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF176_COEFF7_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF176_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF176_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF176_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF198 */

#define CSL_RAWFE_H3A_CFG_AFCOEF198_COEFF8_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF198_COEFF8_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF198_COEFF8_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF198_RESERVED_MASK                          (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF198_RESERVED_SHIFT                         (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF198_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AFCOEF198_COEFF9_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF198_COEFF9_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AFCOEF198_COEFF9_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF198_RESERVED1_MASK                         (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF198_RESERVED1_SHIFT                        (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF198_RESERVED1_MAX                          (0x0000000FU)

/* H3A_AFCOEF1010 */

#define CSL_RAWFE_H3A_CFG_AFCOEF1010_COEFF10_MASK                          (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AFCOEF1010_COEFF10_SHIFT                         (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF1010_COEFF10_MAX                           (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AFCOEF1010_RESERVED_MASK                         (0xFFFFF000U)
#define CSL_RAWFE_H3A_CFG_AFCOEF1010_RESERVED_SHIFT                        (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AFCOEF1010_RESERVED_MAX                          (0x000FFFFFU)

/* H3A_AEWWIN1 */

#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINHC_MASK                               (0x0000003FU)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINHC_SHIFT                              (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINHC_MAX                                (0x0000003FU)

#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINVC_MASK                               (0x00001FC0U)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINVC_SHIFT                              (0x00000006U)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINVC_MAX                                (0x0000007FU)

#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINW_MASK                                (0x001FE000U)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINW_SHIFT                               (0x0000000DU)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINW_MAX                                 (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINH_MASK                                (0xFF000000U)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINH_SHIFT                               (0x00000018U)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_WINH_MAX                                 (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_AEWWIN1_RESERVED_MASK                            (0x00E00000U)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_RESERVED_SHIFT                           (0x00000015U)
#define CSL_RAWFE_H3A_CFG_AEWWIN1_RESERVED_MAX                             (0x00000007U)

/* H3A_AEWINSTART */

#define CSL_RAWFE_H3A_CFG_AEWINSTART_WINSH_MASK                            (0x00000FFFU)
#define CSL_RAWFE_H3A_CFG_AEWINSTART_WINSH_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AEWINSTART_WINSH_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AEWINSTART_WINSV_MASK                            (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AEWINSTART_WINSV_SHIFT                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AEWINSTART_WINSV_MAX                             (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AEWINSTART_RESERVED_MASK                         (0x0000F000U)
#define CSL_RAWFE_H3A_CFG_AEWINSTART_RESERVED_SHIFT                        (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AEWINSTART_RESERVED_MAX                          (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AEWINSTART_RESERVED1_MASK                        (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AEWINSTART_RESERVED1_SHIFT                       (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AEWINSTART_RESERVED1_MAX                         (0x0000000FU)

/* H3A_AEWINBLK */

#define CSL_RAWFE_H3A_CFG_AEWINBLK_WINH_MASK                               (0x0000007FU)
#define CSL_RAWFE_H3A_CFG_AEWINBLK_WINH_SHIFT                              (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AEWINBLK_WINH_MAX                                (0x0000007FU)

#define CSL_RAWFE_H3A_CFG_AEWINBLK_WINSV_MASK                              (0x0FFF0000U)
#define CSL_RAWFE_H3A_CFG_AEWINBLK_WINSV_SHIFT                             (0x00000010U)
#define CSL_RAWFE_H3A_CFG_AEWINBLK_WINSV_MAX                               (0x00000FFFU)

#define CSL_RAWFE_H3A_CFG_AEWINBLK_RESERVED1_MASK                          (0xF0000000U)
#define CSL_RAWFE_H3A_CFG_AEWINBLK_RESERVED1_SHIFT                         (0x0000001CU)
#define CSL_RAWFE_H3A_CFG_AEWINBLK_RESERVED1_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AEWINBLK_RESERVED_MASK                           (0x0000FF80U)
#define CSL_RAWFE_H3A_CFG_AEWINBLK_RESERVED_SHIFT                          (0x00000007U)
#define CSL_RAWFE_H3A_CFG_AEWINBLK_RESERVED_MAX                            (0x000001FFU)

/* H3A_AEWSUBWIN */

#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_AEWINCH_MASK                           (0x0000000FU)
#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_AEWINCH_SHIFT                          (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_AEWINCH_MAX                            (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_AEWINCV_MASK                           (0x00000F00U)
#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_AEWINCV_SHIFT                          (0x00000008U)
#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_AEWINCV_MAX                            (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_RESERVED_MASK                          (0x000000F0U)
#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_RESERVED_SHIFT                         (0x00000004U)
#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_RESERVED_MAX                           (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_RESERVED1_MASK                         (0xFFFFF000U)
#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_RESERVED1_SHIFT                        (0x0000000CU)
#define CSL_RAWFE_H3A_CFG_AEWSUBWIN_RESERVED1_MAX                          (0x000FFFFFU)

/* H3A_AEWBUFST */

#define CSL_RAWFE_H3A_CFG_AEWBUFST_AEWBUFST_MASK                           (0xFFFFFFE0U)
#define CSL_RAWFE_H3A_CFG_AEWBUFST_AEWBUFST_SHIFT                          (0x00000005U)
#define CSL_RAWFE_H3A_CFG_AEWBUFST_AEWBUFST_MAX                            (0x07FFFFFFU)

#define CSL_RAWFE_H3A_CFG_AEWBUFST_RESERVED_MASK                           (0x0000001FU)
#define CSL_RAWFE_H3A_CFG_AEWBUFST_RESERVED_SHIFT                          (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AEWBUFST_RESERVED_MAX                            (0x0000001FU)

/* H3A_AEWCFG */

#define CSL_RAWFE_H3A_CFG_AEWCFG_SUMSHFT_MASK                              (0x0000000FU)
#define CSL_RAWFE_H3A_CFG_AEWCFG_SUMSHFT_SHIFT                             (0x00000000U)
#define CSL_RAWFE_H3A_CFG_AEWCFG_SUMSHFT_MAX                               (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AEWCFG_AEFMT_MASK                                (0x00000300U)
#define CSL_RAWFE_H3A_CFG_AEWCFG_AEFMT_SHIFT                               (0x00000008U)
#define CSL_RAWFE_H3A_CFG_AEWCFG_AEFMT_MAX                                 (0x00000003U)

#define CSL_RAWFE_H3A_CFG_AEWCFG_RESERVED_MASK                             (0x000000F0U)
#define CSL_RAWFE_H3A_CFG_AEWCFG_RESERVED_SHIFT                            (0x00000004U)
#define CSL_RAWFE_H3A_CFG_AEWCFG_RESERVED_MAX                              (0x0000000FU)

#define CSL_RAWFE_H3A_CFG_AEWCFG_RESERVED1_MASK                            (0xFFFFFC00U)
#define CSL_RAWFE_H3A_CFG_AEWCFG_RESERVED1_SHIFT                           (0x0000000AU)
#define CSL_RAWFE_H3A_CFG_AEWCFG_RESERVED1_MAX                             (0x003FFFFFU)

/* H3A_LINE_START */

#define CSL_RAWFE_H3A_CFG_LINE_START_LINE_START_MASK                       (0x0000FFFFU)
#define CSL_RAWFE_H3A_CFG_LINE_START_LINE_START_SHIFT                      (0x00000000U)
#define CSL_RAWFE_H3A_CFG_LINE_START_LINE_START_MAX                        (0x0000FFFFU)

#define CSL_RAWFE_H3A_CFG_LINE_START_SLV_MASK                              (0xFFFF0000U)
#define CSL_RAWFE_H3A_CFG_LINE_START_SLV_SHIFT                             (0x00000010U)
#define CSL_RAWFE_H3A_CFG_LINE_START_SLV_MAX                               (0x0000FFFFU)

/* H3A_VFV_CFG1 */

#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_3_MASK                           (0xFF000000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_3_SHIFT                          (0x00000018U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_3_MAX                            (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_2_MASK                           (0x00FF0000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_2_SHIFT                          (0x00000010U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_2_MAX                            (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_1_MASK                           (0x0000FF00U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_1_SHIFT                          (0x00000008U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_1_MAX                            (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_0_MASK                           (0x000000FFU)
#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_0_SHIFT                          (0x00000000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG1_VCOEF1_0_MAX                            (0x000000FFU)

/* H3A_VFV_CFG2 */

#define CSL_RAWFE_H3A_CFG_VFV_CFG2_VCOEF1_4_MASK                           (0x000000FFU)
#define CSL_RAWFE_H3A_CFG_VFV_CFG2_VCOEF1_4_SHIFT                          (0x00000000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG2_VCOEF1_4_MAX                            (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG2_VTHR1_MASK                              (0xFFFF0000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG2_VTHR1_SHIFT                             (0x00000010U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG2_VTHR1_MAX                               (0x0000FFFFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG2_RESERVED_MASK                           (0x0000FF00U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG2_RESERVED_SHIFT                          (0x00000008U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG2_RESERVED_MAX                            (0x000000FFU)

/* H3A_VFV_CFG3 */

#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_3_MASK                           (0xFF000000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_3_SHIFT                          (0x00000018U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_3_MAX                            (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_2_MASK                           (0x00FF0000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_2_SHIFT                          (0x00000010U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_2_MAX                            (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_1_MASK                           (0x0000FF00U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_1_SHIFT                          (0x00000008U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_1_MAX                            (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_0_MASK                           (0x000000FFU)
#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_0_SHIFT                          (0x00000000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG3_VCOEF2_0_MAX                            (0x000000FFU)

/* H3A_VFV_CFG4 */

#define CSL_RAWFE_H3A_CFG_VFV_CFG4_VCOEF2_4_MASK                           (0x000000FFU)
#define CSL_RAWFE_H3A_CFG_VFV_CFG4_VCOEF2_4_SHIFT                          (0x00000000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG4_VCOEF2_4_MAX                            (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG4_RESERVED_MASK                           (0x0000FF00U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG4_RESERVED_SHIFT                          (0x00000008U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG4_RESERVED_MAX                            (0x000000FFU)

#define CSL_RAWFE_H3A_CFG_VFV_CFG4_VTHR2_MASK                              (0xFFFF0000U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG4_VTHR2_SHIFT                             (0x00000010U)
#define CSL_RAWFE_H3A_CFG_VFV_CFG4_VTHR2_MAX                               (0x0000FFFFU)

/* H3A_HVF_THR */

#define CSL_RAWFE_H3A_CFG_HVF_THR_HTHR1_MASK                               (0x0000FFFFU)
#define CSL_RAWFE_H3A_CFG_HVF_THR_HTHR1_SHIFT                              (0x00000000U)
#define CSL_RAWFE_H3A_CFG_HVF_THR_HTHR1_MAX                                (0x0000FFFFU)

#define CSL_RAWFE_H3A_CFG_HVF_THR_HTHR2_MASK                               (0xFFFF0000U)
#define CSL_RAWFE_H3A_CFG_HVF_THR_HTHR2_SHIFT                              (0x00000010U)
#define CSL_RAWFE_H3A_CFG_HVF_THR_HTHR2_MAX                                (0x0000FFFFU)

/* H3A_ADVANCED */

#define CSL_RAWFE_H3A_CFG_ADVANCED_AF_MODE_MASK                            (0x00000001U)
#define CSL_RAWFE_H3A_CFG_ADVANCED_AF_MODE_SHIFT                           (0x00000000U)
#define CSL_RAWFE_H3A_CFG_ADVANCED_AF_MODE_MAX                             (0x00000001U)

#define CSL_RAWFE_H3A_CFG_ADVANCED_ID_MASK                                 (0xFFFF0000U)
#define CSL_RAWFE_H3A_CFG_ADVANCED_ID_SHIFT                                (0x00000010U)
#define CSL_RAWFE_H3A_CFG_ADVANCED_ID_MAX                                  (0x0000FFFFU)

#define CSL_RAWFE_H3A_CFG_ADVANCED_RESERVED_MASK                           (0x0000000EU)
#define CSL_RAWFE_H3A_CFG_ADVANCED_RESERVED_SHIFT                          (0x00000001U)
#define CSL_RAWFE_H3A_CFG_ADVANCED_RESERVED_MAX                            (0x00000007U)

#define CSL_RAWFE_H3A_CFG_ADVANCED_AEW_MODE_MASK                           (0x00000010U)
#define CSL_RAWFE_H3A_CFG_ADVANCED_AEW_MODE_SHIFT                          (0x00000004U)
#define CSL_RAWFE_H3A_CFG_ADVANCED_AEW_MODE_MAX                            (0x00000001U)

#define CSL_RAWFE_H3A_CFG_ADVANCED_RESERVED1_MASK                          (0x0000FFE0U)
#define CSL_RAWFE_H3A_CFG_ADVANCED_RESERVED1_SHIFT                         (0x00000005U)
#define CSL_RAWFE_H3A_CFG_ADVANCED_RESERVED1_MAX                           (0x000007FFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[2048];                /* image cfg  */
} CSL_rawfe_h3a_lramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_H3A_LRAM_RAM1(RAM1)                                          (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_H3A_LRAM_RAM1_DATA_MASK                                      (0x000FFFFFU)
#define CSL_RAWFE_H3A_LRAM_RAM1_DATA_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_H3A_LRAM_RAM1_DATA_MAX                                       (0x000FFFFFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[2048];                /* image cfg  */
} CSL_rawfe_h3a_aramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_H3A_ARAM_RAM1(RAM1)                                          (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_H3A_ARAM_RAM1_DATA_MASK                                      (0xFFFFFFFFU)
#define CSL_RAWFE_H3A_ARAM_RAM1_DATA_SHIFT                                     (0x00000000U)
#define CSL_RAWFE_H3A_ARAM_RAM1_DATA_MAX                                       (0xFFFFFFFFU)

/**************************************************************************
* Hardware Region  : RAM
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM1[2048];                /* image cfg  */
} CSL_rawfe_dpc_statramRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RAWFE_DPC_STATRAM_RAM1(RAM1)                                       (0x00000000U+((RAM1)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM1 */

#define CSL_RAWFE_DPC_STATRAM_RAM1_DATA_MASK                                   (0xFFFFFFFFU)
#define CSL_RAWFE_DPC_STATRAM_RAM1_DATA_SHIFT                                  (0x00000000U)
#define CSL_RAWFE_DPC_STATRAM_RAM1_DATA_MAX                                    (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#endif

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
 *  Name        : cslr_ldc.h
*/
#ifndef CSLR_LDC_H_
#define CSLR_LDC_H_

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
    volatile uint32_t CTRL;                      /* Region Control Register */
    volatile uint32_t OUT_BLKSZ;                 /* Region Output Block size parameter */
} CSL_ldc_coreRegs_region;


typedef struct {
    volatile uint32_t REVISION_REG;              /* PID */
    volatile uint32_t PRIVATE_MEMSIZE;           /* LDC private memory size in KBytes */
    volatile uint32_t CTRL;                      /* LDC Control Register */
    volatile uint32_t CFG;                       /* CFG Register */
    volatile uint32_t MESHTABLE_CFG;             /* MESHTABLE_CFG Register */
    volatile uint32_t MESH_FRSZ;                 /* Mesh Frame Size Register */
    volatile uint32_t COMPUTE_FRSZ;              /* Output Compute FRAME_SIZE Register */
    volatile uint32_t INITXY;                    /* INITXY Register */
    volatile uint32_t INPUT_FRSZ;                /* Input FRAME_SIZE Register */
    volatile uint32_t OUT_BLKSZ;                 /* Output BLOCK Parameter Register */
    volatile uint32_t AFF_AB;                    /* AFF_AB Register */
    volatile uint32_t AFF_CD;                    /* AFF_CD Register */
    volatile uint32_t AFF_EF;                    /* AFF_EF Register */
    volatile uint32_t PWARP_GH;                  /* PWARP_GH Register */
    volatile uint32_t MESH_BASE_H;               /* MESH_BASE_H Register */
    volatile uint32_t MESH_BASE_L;               /* MESH_BASE_L Register */
    volatile uint32_t MESH_OFST;                 /* MESH_OFST  Register */
    volatile uint32_t RD_BASE_H;                 /* RD_BASE_H  Register */
    volatile uint32_t RD_BASE_L;                 /* RD_BASE_L Register */
    volatile uint32_t RD_420C_BASE_H;            /* RD_420C_BASE_H  Register */
    volatile uint32_t RD_420C_BASE_L;            /* RD_420C_BASE_L Register */
    volatile uint32_t RD_OFST;                   /* RD_OFST Register */
    volatile uint32_t CH_RD_OFST;                /* Chroma RD_OFST Register */
    volatile uint32_t VBUSMR_CFG;                /* VBUSMR_CFG Register */
    volatile uint32_t COREOUT_CHANCFG;           /* LDC Core to LSE output channel config  */
    volatile uint32_t DUALOUT_CFG;               /* Dual Luma and Chroma output configuration */
    volatile uint32_t IBUF_PIX_START;            /* Start co-ordinate of pixel data stored in input buffer */
    volatile uint32_t HYBD_CBUFF_PARAM;          /* Input Frame window stored in Circular buffer in hybrid addressing mode */
    volatile uint32_t HYBD_CBUFF_BA_H;           /* Hybrid CBUFF Base Address Register */
    volatile uint32_t HYBD_CBUFF_BA_L;           /* Hybrid CBUFF Base Address Register */
    volatile uint32_t HYBD_BUFF2_BA_H;           /* Hybrid addr mode second linear buffer base address Register */
    volatile uint32_t HYBD_BUFF2_BA_L;           /* Hybrid addr mode second linear buffer base address Register */
    volatile uint32_t HYBD_CHCBUFF_PARAM;        /* Input Frame window stored in Chroma Circular buffer in hybrid addressing mode */
    volatile uint32_t HYBD_CHCBUFF_BA_H;         /* Hybrid Chroma CBUFF Base Address Register */
    volatile uint32_t HYBD_CHCBUFF_BA_L;         /* Hybrid Chroma CBUFF Base Address Register */
    volatile uint32_t HYBD_CHBUFF2_BA_H;         /* Hybrid addr mode chroma second linear buffer base address Register */
    volatile uint32_t HYBD_CHBUFF2_BA_L;         /* Hybrid addr mode chroma second linear buffer base address Register */
    volatile uint8_t  Resv_224[76];
    volatile uint32_t REGN_W12_SZ;               /* Width of horizontal slice1 and slice2 */
    volatile uint32_t REGN_W3_SZ;                /* Width of horizontal slice3 */
    volatile uint32_t REGN_H12_SZ;               /* Height of vertical slice1 and slice2 */
    volatile uint32_t REGN_H3_SZ;                /* Height of vertical slice3 */
    volatile uint8_t  Resv_256[16];
    CSL_ldc_coreRegs_region REGION[9];
    volatile uint8_t  Resv_512[184];
    volatile uint32_t ERR_STATUS;                /* Error Status Register */
    volatile uint32_t DEBUG_CTRL;                /* LDC Debug Status Register  */
    volatile uint32_t DEBUG_STATUS;              /* LDC Debug Status Register */
    volatile uint32_t FR_PDFTCH;                 /* Total Pixel bytes fetched for frame */
    volatile uint32_t FR_MDFTCH;                 /* Total Mesh bytes fetched for frame */
    volatile uint32_t PIXMEMOVF_BLK;             /* Start Co-ordinates first pixel memory overflow block */
    volatile uint32_t MESHMEMOVF_BLK;            /* Start Co-ordinates  first mesh memory overflow block */
    volatile uint32_t OUTOFBOUND_BLK;            /* Start Co-ordinates first pixel out of bound block */
} CSL_ldc_coreRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LDC_CORE_REVISION_REG                                              (0x00000000U)
#define CSL_LDC_CORE_PRIVATE_MEMSIZE                                           (0x00000004U)
#define CSL_LDC_CORE_CTRL                                                      (0x00000008U)
#define CSL_LDC_CORE_CFG                                                       (0x0000000CU)
#define CSL_LDC_CORE_MESHTABLE_CFG                                             (0x00000010U)
#define CSL_LDC_CORE_MESH_FRSZ                                                 (0x00000014U)
#define CSL_LDC_CORE_COMPUTE_FRSZ                                              (0x00000018U)
#define CSL_LDC_CORE_INITXY                                                    (0x0000001CU)
#define CSL_LDC_CORE_INPUT_FRSZ                                                (0x00000020U)
#define CSL_LDC_CORE_OUT_BLKSZ                                                 (0x00000024U)
#define CSL_LDC_CORE_AFF_AB                                                    (0x00000028U)
#define CSL_LDC_CORE_AFF_CD                                                    (0x0000002CU)
#define CSL_LDC_CORE_AFF_EF                                                    (0x00000030U)
#define CSL_LDC_CORE_PWARP_GH                                                  (0x00000034U)
#define CSL_LDC_CORE_MESH_BASE_H                                               (0x00000038U)
#define CSL_LDC_CORE_MESH_BASE_L                                               (0x0000003CU)
#define CSL_LDC_CORE_MESH_OFST                                                 (0x00000040U)
#define CSL_LDC_CORE_RD_BASE_H                                                 (0x00000044U)
#define CSL_LDC_CORE_RD_BASE_L                                                 (0x00000048U)
#define CSL_LDC_CORE_RD_420C_BASE_H                                            (0x0000004CU)
#define CSL_LDC_CORE_RD_420C_BASE_L                                            (0x00000050U)
#define CSL_LDC_CORE_RD_OFST                                                   (0x00000054U)
#define CSL_LDC_CORE_CH_RD_OFST                                                (0x00000058U)
#define CSL_LDC_CORE_VBUSMR_CFG                                                (0x0000005CU)
#define CSL_LDC_CORE_COREOUT_CHANCFG                                           (0x00000060U)
#define CSL_LDC_CORE_DUALOUT_CFG                                               (0x00000064U)
#define CSL_LDC_CORE_IBUF_PIX_START                                            (0x00000068U)
#define CSL_LDC_CORE_HYBD_CBUFF_PARAM                                          (0x0000006CU)
#define CSL_LDC_CORE_HYBD_CBUFF_BA_H                                           (0x00000070U)
#define CSL_LDC_CORE_HYBD_CBUFF_BA_L                                           (0x00000074U)
#define CSL_LDC_CORE_HYBD_BUFF2_BA_H                                           (0x00000078U)
#define CSL_LDC_CORE_HYBD_BUFF2_BA_L                                           (0x0000007CU)
#define CSL_LDC_CORE_HYBD_CHCBUFF_PARAM                                        (0x00000080U)
#define CSL_LDC_CORE_HYBD_CHCBUFF_BA_H                                         (0x00000084U)
#define CSL_LDC_CORE_HYBD_CHCBUFF_BA_L                                         (0x00000088U)
#define CSL_LDC_CORE_HYBD_CHBUFF2_BA_H                                         (0x0000008CU)
#define CSL_LDC_CORE_HYBD_CHBUFF2_BA_L                                         (0x00000090U)
#define CSL_LDC_CORE_REGN_W12_SZ                                               (0x000000E0U)
#define CSL_LDC_CORE_REGN_W3_SZ                                                (0x000000E4U)
#define CSL_LDC_CORE_REGN_H12_SZ                                               (0x000000E8U)
#define CSL_LDC_CORE_REGN_H3_SZ                                                (0x000000ECU)
#define CSL_LDC_CORE_REGION_CTRL(REGION)                                       (0x00000100U+((REGION)*0x8U))
#define CSL_LDC_CORE_REGION_OUT_BLKSZ(REGION)                                  (0x00000104U+((REGION)*0x8U))
#define CSL_LDC_CORE_ERR_STATUS                                                (0x00000200U)
#define CSL_LDC_CORE_DEBUG_CTRL                                                (0x00000204U)
#define CSL_LDC_CORE_DEBUG_STATUS                                              (0x00000208U)
#define CSL_LDC_CORE_FR_PDFTCH                                                 (0x0000020CU)
#define CSL_LDC_CORE_FR_MDFTCH                                                 (0x00000210U)
#define CSL_LDC_CORE_PIXMEMOVF_BLK                                             (0x00000214U)
#define CSL_LDC_CORE_MESHMEMOVF_BLK                                            (0x00000218U)
#define CSL_LDC_CORE_OUTOFBOUND_BLK                                            (0x0000021CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CTRL */

#define CSL_LDC_CORE_REGION_CTRL_ENABLE_MASK                                   (0x00000001U)
#define CSL_LDC_CORE_REGION_CTRL_ENABLE_SHIFT                                  (0x00000000U)
#define CSL_LDC_CORE_REGION_CTRL_ENABLE_MAX                                    (0x00000001U)

/* OUT_BLKSZ */

#define CSL_LDC_CORE_REGION_OUT_BLKSZ_PIXPAD_MASK                              (0x000F0000U)
#define CSL_LDC_CORE_REGION_OUT_BLKSZ_PIXPAD_SHIFT                             (0x00000010U)
#define CSL_LDC_CORE_REGION_OUT_BLKSZ_PIXPAD_MAX                               (0x0000000FU)

#define CSL_LDC_CORE_REGION_OUT_BLKSZ_OBH_MASK                                 (0x0000FF00U)
#define CSL_LDC_CORE_REGION_OUT_BLKSZ_OBH_SHIFT                                (0x00000008U)
#define CSL_LDC_CORE_REGION_OUT_BLKSZ_OBH_MAX                                  (0x000000FFU)

#define CSL_LDC_CORE_REGION_OUT_BLKSZ_OBW_MASK                                 (0x000000FFU)
#define CSL_LDC_CORE_REGION_OUT_BLKSZ_OBW_SHIFT                                (0x00000000U)
#define CSL_LDC_CORE_REGION_OUT_BLKSZ_OBW_MAX                                  (0x000000FFU)

/* REVISION_REG */

#define CSL_LDC_CORE_REVISION_REG_SCHEME_MASK                                  (0xC0000000U)
#define CSL_LDC_CORE_REVISION_REG_SCHEME_SHIFT                                 (0x0000001EU)
#define CSL_LDC_CORE_REVISION_REG_SCHEME_MAX                                   (0x00000003U)

#define CSL_LDC_CORE_REVISION_REG_BU_MASK                                      (0x30000000U)
#define CSL_LDC_CORE_REVISION_REG_BU_SHIFT                                     (0x0000001CU)
#define CSL_LDC_CORE_REVISION_REG_BU_MAX                                       (0x00000003U)

#define CSL_LDC_CORE_REVISION_REG_FUNC_MASK                                    (0x0FFF0000U)
#define CSL_LDC_CORE_REVISION_REG_FUNC_SHIFT                                   (0x00000010U)
#define CSL_LDC_CORE_REVISION_REG_FUNC_MAX                                     (0x00000FFFU)

#define CSL_LDC_CORE_REVISION_REG_RTL_MASK                                     (0x0000F800U)
#define CSL_LDC_CORE_REVISION_REG_RTL_SHIFT                                    (0x0000000BU)
#define CSL_LDC_CORE_REVISION_REG_RTL_MAX                                      (0x0000001FU)

#define CSL_LDC_CORE_REVISION_REG_MAJOR_MASK                                   (0x00000700U)
#define CSL_LDC_CORE_REVISION_REG_MAJOR_SHIFT                                  (0x00000008U)
#define CSL_LDC_CORE_REVISION_REG_MAJOR_MAX                                    (0x00000007U)

#define CSL_LDC_CORE_REVISION_REG_CUSTOM_MASK                                  (0x000000C0U)
#define CSL_LDC_CORE_REVISION_REG_CUSTOM_SHIFT                                 (0x00000006U)
#define CSL_LDC_CORE_REVISION_REG_CUSTOM_MAX                                   (0x00000003U)

#define CSL_LDC_CORE_REVISION_REG_MINOR_MASK                                   (0x0000003FU)
#define CSL_LDC_CORE_REVISION_REG_MINOR_SHIFT                                  (0x00000000U)
#define CSL_LDC_CORE_REVISION_REG_MINOR_MAX                                    (0x0000003FU)

/* PRIVATE_MEMSIZE */

#define CSL_LDC_CORE_PRIVATE_MEMSIZE_MESH_MASK                                 (0x00FF0000U)
#define CSL_LDC_CORE_PRIVATE_MEMSIZE_MESH_SHIFT                                (0x00000010U)
#define CSL_LDC_CORE_PRIVATE_MEMSIZE_MESH_MAX                                  (0x000000FFU)

#define CSL_LDC_CORE_PRIVATE_MEMSIZE_CHROMA_MASK                               (0x0000FF00U)
#define CSL_LDC_CORE_PRIVATE_MEMSIZE_CHROMA_SHIFT                              (0x00000008U)
#define CSL_LDC_CORE_PRIVATE_MEMSIZE_CHROMA_MAX                                (0x000000FFU)

#define CSL_LDC_CORE_PRIVATE_MEMSIZE_LUMA_MASK                                 (0x000000FFU)
#define CSL_LDC_CORE_PRIVATE_MEMSIZE_LUMA_SHIFT                                (0x00000000U)
#define CSL_LDC_CORE_PRIVATE_MEMSIZE_LUMA_MAX                                  (0x000000FFU)

/* CTRL */

#define CSL_LDC_CORE_CTRL_HYBD_ADDREN_MASK                                     (0x01000000U)
#define CSL_LDC_CORE_CTRL_HYBD_ADDREN_SHIFT                                    (0x00000018U)
#define CSL_LDC_CORE_CTRL_HYBD_ADDREN_MAX                                      (0x00000001U)

#define CSL_LDC_CORE_CTRL_CH_IP_DFMT_MASK                                      (0x00060000U)
#define CSL_LDC_CORE_CTRL_CH_IP_DFMT_SHIFT                                     (0x00000011U)
#define CSL_LDC_CORE_CTRL_CH_IP_DFMT_MAX                                       (0x00000003U)

#define CSL_LDC_CORE_CTRL_CH_CHANCTRL_EN_MASK                                  (0x00010000U)
#define CSL_LDC_CORE_CTRL_CH_CHANCTRL_EN_SHIFT                                 (0x00000010U)
#define CSL_LDC_CORE_CTRL_CH_CHANCTRL_EN_MAX                                   (0x00000001U)

#define CSL_LDC_CORE_CTRL_REGMODE_EN_MASK                                      (0x00004000U)
#define CSL_LDC_CORE_CTRL_REGMODE_EN_SHIFT                                     (0x0000000EU)
#define CSL_LDC_CORE_CTRL_REGMODE_EN_MAX                                       (0x00000001U)

#define CSL_LDC_CORE_CTRL_OP_DATAMODE_MASK                                     (0x00002000U)
#define CSL_LDC_CORE_CTRL_OP_DATAMODE_SHIFT                                    (0x0000000DU)
#define CSL_LDC_CORE_CTRL_OP_DATAMODE_MAX                                      (0x00000001U)

#define CSL_LDC_CORE_CTRL_IP_HTS_ROWSYNC_MASK                                  (0x00001000U)
#define CSL_LDC_CORE_CTRL_IP_HTS_ROWSYNC_SHIFT                                 (0x0000000CU)
#define CSL_LDC_CORE_CTRL_IP_HTS_ROWSYNC_MAX                                   (0x00000001U)

#define CSL_LDC_CORE_CTRL_IP_CIRCEN_MASK                                       (0x00000800U)
#define CSL_LDC_CORE_CTRL_IP_CIRCEN_SHIFT                                      (0x0000000BU)
#define CSL_LDC_CORE_CTRL_IP_CIRCEN_MAX                                        (0x00000001U)

#define CSL_LDC_CORE_CTRL_ALIGN_12BIT_MASK                                     (0x00000400U)
#define CSL_LDC_CORE_CTRL_ALIGN_12BIT_SHIFT                                    (0x0000000AU)
#define CSL_LDC_CORE_CTRL_ALIGN_12BIT_MAX                                      (0x00000001U)

#define CSL_LDC_CORE_CTRL_PWARPEN_MASK                                         (0x00000200U)
#define CSL_LDC_CORE_CTRL_PWARPEN_SHIFT                                        (0x00000009U)
#define CSL_LDC_CORE_CTRL_PWARPEN_MAX                                          (0x00000001U)

#define CSL_LDC_CORE_CTRL_IP_DFMT_MASK                                         (0x00000180U)
#define CSL_LDC_CORE_CTRL_IP_DFMT_SHIFT                                        (0x00000007U)
#define CSL_LDC_CORE_CTRL_IP_DFMT_MAX                                          (0x00000003U)

#define CSL_LDC_CORE_CTRL_IP_DATAMODE_MASK                                     (0x00000078U)
#define CSL_LDC_CORE_CTRL_IP_DATAMODE_SHIFT                                    (0x00000003U)
#define CSL_LDC_CORE_CTRL_IP_DATAMODE_MAX                                      (0x0000000FU)

#define CSL_LDC_CORE_CTRL_BUSY_MASK                                            (0x00000004U)
#define CSL_LDC_CORE_CTRL_BUSY_SHIFT                                           (0x00000002U)
#define CSL_LDC_CORE_CTRL_BUSY_MAX                                             (0x00000001U)

#define CSL_LDC_CORE_CTRL_LDMAPEN_MASK                                         (0x00000002U)
#define CSL_LDC_CORE_CTRL_LDMAPEN_SHIFT                                        (0x00000001U)
#define CSL_LDC_CORE_CTRL_LDMAPEN_MAX                                          (0x00000001U)

#define CSL_LDC_CORE_CTRL_LDC_EN_MASK                                          (0x00000001U)
#define CSL_LDC_CORE_CTRL_LDC_EN_SHIFT                                         (0x00000000U)
#define CSL_LDC_CORE_CTRL_LDC_EN_MAX                                           (0x00000001U)

/* CFG */

#define CSL_LDC_CORE_CFG_YINT_TYP_MASK                                         (0x00000040U)
#define CSL_LDC_CORE_CFG_YINT_TYP_SHIFT                                        (0x00000006U)
#define CSL_LDC_CORE_CFG_YINT_TYP_MAX                                          (0x00000001U)

#define CSL_LDC_CORE_CFG_CNTU_MODE_MASK                                        (0x00000004U)
#define CSL_LDC_CORE_CFG_CNTU_MODE_SHIFT                                       (0x00000002U)
#define CSL_LDC_CORE_CFG_CNTU_MODE_MAX                                         (0x00000001U)

#define CSL_LDC_CORE_CFG_CLKCG_OVERIDE_MASK                                    (0x00000002U)
#define CSL_LDC_CORE_CFG_CLKCG_OVERIDE_SHIFT                                   (0x00000001U)
#define CSL_LDC_CORE_CFG_CLKCG_OVERIDE_MAX                                     (0x00000001U)

/* MESHTABLE_CFG */

#define CSL_LDC_CORE_MESHTABLE_CFG_M_MASK                                      (0x00000007U)
#define CSL_LDC_CORE_MESHTABLE_CFG_M_SHIFT                                     (0x00000000U)
#define CSL_LDC_CORE_MESHTABLE_CFG_M_MAX                                       (0x00000007U)

/* MESH_FRSZ */

#define CSL_LDC_CORE_MESH_FRSZ_H_MASK                                          (0x3FFF0000U)
#define CSL_LDC_CORE_MESH_FRSZ_H_SHIFT                                         (0x00000010U)
#define CSL_LDC_CORE_MESH_FRSZ_H_MAX                                           (0x00003FFFU)

#define CSL_LDC_CORE_MESH_FRSZ_W_MASK                                          (0x00003FFFU)
#define CSL_LDC_CORE_MESH_FRSZ_W_SHIFT                                         (0x00000000U)
#define CSL_LDC_CORE_MESH_FRSZ_W_MAX                                           (0x00003FFFU)

/* COMPUTE_FRSZ */

#define CSL_LDC_CORE_COMPUTE_FRSZ_H_MASK                                       (0x3FFF0000U)
#define CSL_LDC_CORE_COMPUTE_FRSZ_H_SHIFT                                      (0x00000010U)
#define CSL_LDC_CORE_COMPUTE_FRSZ_H_MAX                                        (0x00003FFFU)

#define CSL_LDC_CORE_COMPUTE_FRSZ_W_MASK                                       (0x00003FFFU)
#define CSL_LDC_CORE_COMPUTE_FRSZ_W_SHIFT                                      (0x00000000U)
#define CSL_LDC_CORE_COMPUTE_FRSZ_W_MAX                                        (0x00003FFFU)

/* INITXY */

#define CSL_LDC_CORE_INITXY_INITY_MASK                                         (0x1FFF0000U)
#define CSL_LDC_CORE_INITXY_INITY_SHIFT                                        (0x00000010U)
#define CSL_LDC_CORE_INITXY_INITY_MAX                                          (0x00001FFFU)

#define CSL_LDC_CORE_INITXY_INITX_MASK                                         (0x00001FFFU)
#define CSL_LDC_CORE_INITXY_INITX_SHIFT                                        (0x00000000U)
#define CSL_LDC_CORE_INITXY_INITX_MAX                                          (0x00001FFFU)

/* INPUT_FRSZ */

#define CSL_LDC_CORE_INPUT_FRSZ_H_MASK                                         (0x3FFF0000U)
#define CSL_LDC_CORE_INPUT_FRSZ_H_SHIFT                                        (0x00000010U)
#define CSL_LDC_CORE_INPUT_FRSZ_H_MAX                                          (0x00003FFFU)

#define CSL_LDC_CORE_INPUT_FRSZ_W_MASK                                         (0x00003FFFU)
#define CSL_LDC_CORE_INPUT_FRSZ_W_SHIFT                                        (0x00000000U)
#define CSL_LDC_CORE_INPUT_FRSZ_W_MAX                                          (0x00003FFFU)

/* OUT_BLKSZ */

#define CSL_LDC_CORE_OUT_BLKSZ_PIXPAD_MASK                                     (0x000F0000U)
#define CSL_LDC_CORE_OUT_BLKSZ_PIXPAD_SHIFT                                    (0x00000010U)
#define CSL_LDC_CORE_OUT_BLKSZ_PIXPAD_MAX                                      (0x0000000FU)

#define CSL_LDC_CORE_OUT_BLKSZ_OBH_MASK                                        (0x0000FF00U)
#define CSL_LDC_CORE_OUT_BLKSZ_OBH_SHIFT                                       (0x00000008U)
#define CSL_LDC_CORE_OUT_BLKSZ_OBH_MAX                                         (0x000000FFU)

#define CSL_LDC_CORE_OUT_BLKSZ_OBW_MASK                                        (0x000000FFU)
#define CSL_LDC_CORE_OUT_BLKSZ_OBW_SHIFT                                       (0x00000000U)
#define CSL_LDC_CORE_OUT_BLKSZ_OBW_MAX                                         (0x000000FFU)

/* AFF_AB */

#define CSL_LDC_CORE_AFF_AB_B_MASK                                             (0xFFFF0000U)
#define CSL_LDC_CORE_AFF_AB_B_SHIFT                                            (0x00000010U)
#define CSL_LDC_CORE_AFF_AB_B_MAX                                              (0x0000FFFFU)

#define CSL_LDC_CORE_AFF_AB_A_MASK                                             (0x0000FFFFU)
#define CSL_LDC_CORE_AFF_AB_A_SHIFT                                            (0x00000000U)
#define CSL_LDC_CORE_AFF_AB_A_MAX                                              (0x0000FFFFU)

/* AFF_CD */

#define CSL_LDC_CORE_AFF_CD_D_MASK                                             (0xFFFF0000U)
#define CSL_LDC_CORE_AFF_CD_D_SHIFT                                            (0x00000010U)
#define CSL_LDC_CORE_AFF_CD_D_MAX                                              (0x0000FFFFU)

#define CSL_LDC_CORE_AFF_CD_C_MASK                                             (0x0000FFFFU)
#define CSL_LDC_CORE_AFF_CD_C_SHIFT                                            (0x00000000U)
#define CSL_LDC_CORE_AFF_CD_C_MAX                                              (0x0000FFFFU)

/* AFF_EF */

#define CSL_LDC_CORE_AFF_EF_F_MASK                                             (0xFFFF0000U)
#define CSL_LDC_CORE_AFF_EF_F_SHIFT                                            (0x00000010U)
#define CSL_LDC_CORE_AFF_EF_F_MAX                                              (0x0000FFFFU)

#define CSL_LDC_CORE_AFF_EF_E_MASK                                             (0x0000FFFFU)
#define CSL_LDC_CORE_AFF_EF_E_SHIFT                                            (0x00000000U)
#define CSL_LDC_CORE_AFF_EF_E_MAX                                              (0x0000FFFFU)

/* PWARP_GH */

#define CSL_LDC_CORE_PWARP_GH_H_MASK                                           (0xFFFF0000U)
#define CSL_LDC_CORE_PWARP_GH_H_SHIFT                                          (0x00000010U)
#define CSL_LDC_CORE_PWARP_GH_H_MAX                                            (0x0000FFFFU)

#define CSL_LDC_CORE_PWARP_GH_G_MASK                                           (0x0000FFFFU)
#define CSL_LDC_CORE_PWARP_GH_G_SHIFT                                          (0x00000000U)
#define CSL_LDC_CORE_PWARP_GH_G_MAX                                            (0x0000FFFFU)

/* MESH_BASE_H */

#define CSL_LDC_CORE_MESH_BASE_H_ADDR_MASK                                     (0x0000FFFFU)
#define CSL_LDC_CORE_MESH_BASE_H_ADDR_SHIFT                                    (0x00000000U)
#define CSL_LDC_CORE_MESH_BASE_H_ADDR_MAX                                      (0x0000FFFFU)

/* MESH_BASE_L */

#define CSL_LDC_CORE_MESH_BASE_L_ADDR_MASK                                     (0xFFFFFFFFU)
#define CSL_LDC_CORE_MESH_BASE_L_ADDR_SHIFT                                    (0x00000000U)
#define CSL_LDC_CORE_MESH_BASE_L_ADDR_MAX                                      (0xFFFFFFFFU)

/* MESH_OFST */

#define CSL_LDC_CORE_MESH_OFST_OFST_MASK                                       (0x0000FFFFU)
#define CSL_LDC_CORE_MESH_OFST_OFST_SHIFT                                      (0x00000000U)
#define CSL_LDC_CORE_MESH_OFST_OFST_MAX                                        (0x0000FFFFU)

/* RD_BASE_H */

#define CSL_LDC_CORE_RD_BASE_H_ADDR_MASK                                       (0x0000FFFFU)
#define CSL_LDC_CORE_RD_BASE_H_ADDR_SHIFT                                      (0x00000000U)
#define CSL_LDC_CORE_RD_BASE_H_ADDR_MAX                                        (0x0000FFFFU)

/* RD_BASE_L */

#define CSL_LDC_CORE_RD_BASE_L_ADDR_MASK                                       (0xFFFFFFFFU)
#define CSL_LDC_CORE_RD_BASE_L_ADDR_SHIFT                                      (0x00000000U)
#define CSL_LDC_CORE_RD_BASE_L_ADDR_MAX                                        (0xFFFFFFFFU)

/* RD_420C_BASE_H */

#define CSL_LDC_CORE_RD_420C_BASE_H_ADDR_MASK                                  (0x0000FFFFU)
#define CSL_LDC_CORE_RD_420C_BASE_H_ADDR_SHIFT                                 (0x00000000U)
#define CSL_LDC_CORE_RD_420C_BASE_H_ADDR_MAX                                   (0x0000FFFFU)

/* RD_420C_BASE_L */

#define CSL_LDC_CORE_RD_420C_BASE_L_ADDR_MASK                                  (0xFFFFFFFFU)
#define CSL_LDC_CORE_RD_420C_BASE_L_ADDR_SHIFT                                 (0x00000000U)
#define CSL_LDC_CORE_RD_420C_BASE_L_ADDR_MAX                                   (0xFFFFFFFFU)

/* RD_OFST */

#define CSL_LDC_CORE_RD_OFST_MOD_MASK                                          (0x3FFF0000U)
#define CSL_LDC_CORE_RD_OFST_MOD_SHIFT                                         (0x00000010U)
#define CSL_LDC_CORE_RD_OFST_MOD_MAX                                           (0x00003FFFU)

#define CSL_LDC_CORE_RD_OFST_OFST_MASK                                         (0x0000FFFFU)
#define CSL_LDC_CORE_RD_OFST_OFST_SHIFT                                        (0x00000000U)
#define CSL_LDC_CORE_RD_OFST_OFST_MAX                                          (0x0000FFFFU)

/* CH_RD_OFST */

#define CSL_LDC_CORE_CH_RD_OFST_MOD_MASK                                       (0x3FFF0000U)
#define CSL_LDC_CORE_CH_RD_OFST_MOD_SHIFT                                      (0x00000010U)
#define CSL_LDC_CORE_CH_RD_OFST_MOD_MAX                                        (0x00003FFFU)

#define CSL_LDC_CORE_CH_RD_OFST_OFST_MASK                                      (0x0000FFFFU)
#define CSL_LDC_CORE_CH_RD_OFST_OFST_SHIFT                                     (0x00000000U)
#define CSL_LDC_CORE_CH_RD_OFST_OFST_MAX                                       (0x0000FFFFU)

/* VBUSMR_CFG */

#define CSL_LDC_CORE_VBUSMR_CFG_BW_CTRL_MASK                                   (0x0FFF0000U)
#define CSL_LDC_CORE_VBUSMR_CFG_BW_CTRL_SHIFT                                  (0x00000010U)
#define CSL_LDC_CORE_VBUSMR_CFG_BW_CTRL_MAX                                    (0x00000FFFU)

#define CSL_LDC_CORE_VBUSMR_CFG_TAG_CNT_MASK                                   (0x000000F8U)
#define CSL_LDC_CORE_VBUSMR_CFG_TAG_CNT_SHIFT                                  (0x00000003U)
#define CSL_LDC_CORE_VBUSMR_CFG_TAG_CNT_MAX                                    (0x0000001FU)

#define CSL_LDC_CORE_VBUSMR_CFG_MAX_BURSTLEN_MASK                              (0x00000006U)
#define CSL_LDC_CORE_VBUSMR_CFG_MAX_BURSTLEN_SHIFT                             (0x00000001U)
#define CSL_LDC_CORE_VBUSMR_CFG_MAX_BURSTLEN_MAX                               (0x00000003U)

/* COREOUT_CHANCFG */

#define CSL_LDC_CORE_COREOUT_CHANCFG_CH3_EN_MASK                               (0x00000008U)
#define CSL_LDC_CORE_COREOUT_CHANCFG_CH3_EN_SHIFT                              (0x00000003U)
#define CSL_LDC_CORE_COREOUT_CHANCFG_CH3_EN_MAX                                (0x00000001U)

#define CSL_LDC_CORE_COREOUT_CHANCFG_CH2_EN_MASK                               (0x00000004U)
#define CSL_LDC_CORE_COREOUT_CHANCFG_CH2_EN_SHIFT                              (0x00000002U)
#define CSL_LDC_CORE_COREOUT_CHANCFG_CH2_EN_MAX                                (0x00000001U)

#define CSL_LDC_CORE_COREOUT_CHANCFG_RSRV_CH1_MASK                             (0x00000002U)
#define CSL_LDC_CORE_COREOUT_CHANCFG_RSRV_CH1_SHIFT                            (0x00000001U)
#define CSL_LDC_CORE_COREOUT_CHANCFG_RSRV_CH1_MAX                              (0x00000001U)

#define CSL_LDC_CORE_COREOUT_CHANCFG_RSRV_CH0_MASK                             (0x00000001U)
#define CSL_LDC_CORE_COREOUT_CHANCFG_RSRV_CH0_SHIFT                            (0x00000000U)
#define CSL_LDC_CORE_COREOUT_CHANCFG_RSRV_CH0_MAX                              (0x00000001U)

/* DUALOUT_CFG */

#define CSL_LDC_CORE_DUALOUT_CFG_COUT_BITDPTH_MASK                             (0x01E00000U)
#define CSL_LDC_CORE_DUALOUT_CFG_COUT_BITDPTH_SHIFT                            (0x00000015U)
#define CSL_LDC_CORE_DUALOUT_CFG_COUT_BITDPTH_MAX                              (0x0000000FU)

#define CSL_LDC_CORE_DUALOUT_CFG_CIN_BITDPTH_MASK                              (0x001E0000U)
#define CSL_LDC_CORE_DUALOUT_CFG_CIN_BITDPTH_SHIFT                             (0x00000011U)
#define CSL_LDC_CORE_DUALOUT_CFG_CIN_BITDPTH_MAX                               (0x0000000FU)

#define CSL_LDC_CORE_DUALOUT_CFG_CLUT_EN_MASK                                  (0x00010000U)
#define CSL_LDC_CORE_DUALOUT_CFG_CLUT_EN_SHIFT                                 (0x00000010U)
#define CSL_LDC_CORE_DUALOUT_CFG_CLUT_EN_MAX                                   (0x00000001U)

#define CSL_LDC_CORE_DUALOUT_CFG_YOUT_BITDPTH_MASK                             (0x000001E0U)
#define CSL_LDC_CORE_DUALOUT_CFG_YOUT_BITDPTH_SHIFT                            (0x00000005U)
#define CSL_LDC_CORE_DUALOUT_CFG_YOUT_BITDPTH_MAX                              (0x0000000FU)

#define CSL_LDC_CORE_DUALOUT_CFG_YIN_BITDPTH_MASK                              (0x0000001EU)
#define CSL_LDC_CORE_DUALOUT_CFG_YIN_BITDPTH_SHIFT                             (0x00000001U)
#define CSL_LDC_CORE_DUALOUT_CFG_YIN_BITDPTH_MAX                               (0x0000000FU)

#define CSL_LDC_CORE_DUALOUT_CFG_YLUT_EN_MASK                                  (0x00000001U)
#define CSL_LDC_CORE_DUALOUT_CFG_YLUT_EN_SHIFT                                 (0x00000000U)
#define CSL_LDC_CORE_DUALOUT_CFG_YLUT_EN_MAX                                   (0x00000001U)

/* IBUF_PIX_START */

#define CSL_LDC_CORE_IBUF_PIX_START_STARTY_MASK                                (0x1FFF0000U)
#define CSL_LDC_CORE_IBUF_PIX_START_STARTY_SHIFT                               (0x00000010U)
#define CSL_LDC_CORE_IBUF_PIX_START_STARTY_MAX                                 (0x00001FFFU)

#define CSL_LDC_CORE_IBUF_PIX_START_STARTX_MASK                                (0x00001FFFU)
#define CSL_LDC_CORE_IBUF_PIX_START_STARTX_SHIFT                               (0x00000000U)
#define CSL_LDC_CORE_IBUF_PIX_START_STARTX_MAX                                 (0x00001FFFU)

/* HYBD_CBUFF_PARAM */

#define CSL_LDC_CORE_HYBD_CBUFF_PARAM_STARTLINE_MASK                           (0x1FFF0000U)
#define CSL_LDC_CORE_HYBD_CBUFF_PARAM_STARTLINE_SHIFT                          (0x00000010U)
#define CSL_LDC_CORE_HYBD_CBUFF_PARAM_STARTLINE_MAX                            (0x00001FFFU)

#define CSL_LDC_CORE_HYBD_CBUFF_PARAM_ENDLINE_MASK                             (0x00001FFFU)
#define CSL_LDC_CORE_HYBD_CBUFF_PARAM_ENDLINE_SHIFT                            (0x00000000U)
#define CSL_LDC_CORE_HYBD_CBUFF_PARAM_ENDLINE_MAX                              (0x00001FFFU)

/* HYBD_CBUFF_BA_H */

#define CSL_LDC_CORE_HYBD_CBUFF_BA_H_ADDR_MASK                                 (0x0000FFFFU)
#define CSL_LDC_CORE_HYBD_CBUFF_BA_H_ADDR_SHIFT                                (0x00000000U)
#define CSL_LDC_CORE_HYBD_CBUFF_BA_H_ADDR_MAX                                  (0x0000FFFFU)

/* HYBD_CBUFF_BA_L */

#define CSL_LDC_CORE_HYBD_CBUFF_BA_L_ADDR_MASK                                 (0xFFFFFFFFU)
#define CSL_LDC_CORE_HYBD_CBUFF_BA_L_ADDR_SHIFT                                (0x00000000U)
#define CSL_LDC_CORE_HYBD_CBUFF_BA_L_ADDR_MAX                                  (0xFFFFFFFFU)

/* HYBD_BUFF2_BA_H */

#define CSL_LDC_CORE_HYBD_BUFF2_BA_H_ADDR_MASK                                 (0x0000FFFFU)
#define CSL_LDC_CORE_HYBD_BUFF2_BA_H_ADDR_SHIFT                                (0x00000000U)
#define CSL_LDC_CORE_HYBD_BUFF2_BA_H_ADDR_MAX                                  (0x0000FFFFU)

/* HYBD_BUFF2_BA_L */

#define CSL_LDC_CORE_HYBD_BUFF2_BA_L_ADDR_MASK                                 (0xFFFFFFFFU)
#define CSL_LDC_CORE_HYBD_BUFF2_BA_L_ADDR_SHIFT                                (0x00000000U)
#define CSL_LDC_CORE_HYBD_BUFF2_BA_L_ADDR_MAX                                  (0xFFFFFFFFU)

/* HYBD_CHCBUFF_PARAM */

#define CSL_LDC_CORE_HYBD_CHCBUFF_PARAM_STARTLINE_MASK                         (0x1FFF0000U)
#define CSL_LDC_CORE_HYBD_CHCBUFF_PARAM_STARTLINE_SHIFT                        (0x00000010U)
#define CSL_LDC_CORE_HYBD_CHCBUFF_PARAM_STARTLINE_MAX                          (0x00001FFFU)

#define CSL_LDC_CORE_HYBD_CHCBUFF_PARAM_ENDLINE_MASK                           (0x00001FFFU)
#define CSL_LDC_CORE_HYBD_CHCBUFF_PARAM_ENDLINE_SHIFT                          (0x00000000U)
#define CSL_LDC_CORE_HYBD_CHCBUFF_PARAM_ENDLINE_MAX                            (0x00001FFFU)

/* HYBD_CHCBUFF_BA_H */

#define CSL_LDC_CORE_HYBD_CHCBUFF_BA_H_ADDR_MASK                               (0x0000FFFFU)
#define CSL_LDC_CORE_HYBD_CHCBUFF_BA_H_ADDR_SHIFT                              (0x00000000U)
#define CSL_LDC_CORE_HYBD_CHCBUFF_BA_H_ADDR_MAX                                (0x0000FFFFU)

/* HYBD_CHCBUFF_BA_L */

#define CSL_LDC_CORE_HYBD_CHCBUFF_BA_L_ADDR_MASK                               (0xFFFFFFFFU)
#define CSL_LDC_CORE_HYBD_CHCBUFF_BA_L_ADDR_SHIFT                              (0x00000000U)
#define CSL_LDC_CORE_HYBD_CHCBUFF_BA_L_ADDR_MAX                                (0xFFFFFFFFU)

/* HYBD_CHBUFF2_BA_H */

#define CSL_LDC_CORE_HYBD_CHBUFF2_BA_H_ADDR_MASK                               (0x0000FFFFU)
#define CSL_LDC_CORE_HYBD_CHBUFF2_BA_H_ADDR_SHIFT                              (0x00000000U)
#define CSL_LDC_CORE_HYBD_CHBUFF2_BA_H_ADDR_MAX                                (0x0000FFFFU)

/* HYBD_CHBUFF2_BA_L */

#define CSL_LDC_CORE_HYBD_CHBUFF2_BA_L_ADDR_MASK                               (0xFFFFFFFFU)
#define CSL_LDC_CORE_HYBD_CHBUFF2_BA_L_ADDR_SHIFT                              (0x00000000U)
#define CSL_LDC_CORE_HYBD_CHBUFF2_BA_L_ADDR_MAX                                (0xFFFFFFFFU)

/* REGN_W12_SZ */

#define CSL_LDC_CORE_REGN_W12_SZ_W2_MASK                                       (0x3FFF0000U)
#define CSL_LDC_CORE_REGN_W12_SZ_W2_SHIFT                                      (0x00000010U)
#define CSL_LDC_CORE_REGN_W12_SZ_W2_MAX                                        (0x00003FFFU)

#define CSL_LDC_CORE_REGN_W12_SZ_W1_MASK                                       (0x00003FFFU)
#define CSL_LDC_CORE_REGN_W12_SZ_W1_SHIFT                                      (0x00000000U)
#define CSL_LDC_CORE_REGN_W12_SZ_W1_MAX                                        (0x00003FFFU)

/* REGN_W3_SZ */

#define CSL_LDC_CORE_REGN_W3_SZ_W3_MASK                                        (0x00003FFFU)
#define CSL_LDC_CORE_REGN_W3_SZ_W3_SHIFT                                       (0x00000000U)
#define CSL_LDC_CORE_REGN_W3_SZ_W3_MAX                                         (0x00003FFFU)

/* REGN_H12_SZ */

#define CSL_LDC_CORE_REGN_H12_SZ_H2_MASK                                       (0x3FFF0000U)
#define CSL_LDC_CORE_REGN_H12_SZ_H2_SHIFT                                      (0x00000010U)
#define CSL_LDC_CORE_REGN_H12_SZ_H2_MAX                                        (0x00003FFFU)

#define CSL_LDC_CORE_REGN_H12_SZ_H1_MASK                                       (0x00003FFFU)
#define CSL_LDC_CORE_REGN_H12_SZ_H1_SHIFT                                      (0x00000000U)
#define CSL_LDC_CORE_REGN_H12_SZ_H1_MAX                                        (0x00003FFFU)

/* REGN_H3_SZ */

#define CSL_LDC_CORE_REGN_H3_SZ_H3_MASK                                        (0x00003FFFU)
#define CSL_LDC_CORE_REGN_H3_SZ_H3_SHIFT                                       (0x00000000U)
#define CSL_LDC_CORE_REGN_H3_SZ_H3_MAX                                         (0x00003FFFU)

/* ERR_STATUS */

#define CSL_LDC_CORE_ERR_STATUS_VBUSMR_ERR_MASK                                (0x00000700U)
#define CSL_LDC_CORE_ERR_STATUS_VBUSMR_ERR_SHIFT                               (0x00000008U)
#define CSL_LDC_CORE_ERR_STATUS_VBUSMR_ERR_MAX                                 (0x00000007U)

#define CSL_LDC_CORE_ERR_STATUS_INT_SZOVF_MASK                                 (0x00000020U)
#define CSL_LDC_CORE_ERR_STATUS_INT_SZOVF_SHIFT                                (0x00000005U)
#define CSL_LDC_CORE_ERR_STATUS_INT_SZOVF_MAX                                  (0x00000001U)

#define CSL_LDC_CORE_ERR_STATUS_M_IBLK_MEMOVF_MASK                             (0x00000010U)
#define CSL_LDC_CORE_ERR_STATUS_M_IBLK_MEMOVF_SHIFT                            (0x00000004U)
#define CSL_LDC_CORE_ERR_STATUS_M_IBLK_MEMOVF_MAX                              (0x00000001U)

#define CSL_LDC_CORE_ERR_STATUS_P_IBLK_MEMOVF_MASK                             (0x00000008U)
#define CSL_LDC_CORE_ERR_STATUS_P_IBLK_MEMOVF_SHIFT                            (0x00000003U)
#define CSL_LDC_CORE_ERR_STATUS_P_IBLK_MEMOVF_MAX                              (0x00000001U)

#define CSL_LDC_CORE_ERR_STATUS_IFRAME_OUTB_MASK                               (0x00000004U)
#define CSL_LDC_CORE_ERR_STATUS_IFRAME_OUTB_SHIFT                              (0x00000002U)
#define CSL_LDC_CORE_ERR_STATUS_IFRAME_OUTB_MAX                                (0x00000001U)

#define CSL_LDC_CORE_ERR_STATUS_M_IBLK_OUTB_MASK                               (0x00000002U)
#define CSL_LDC_CORE_ERR_STATUS_M_IBLK_OUTB_SHIFT                              (0x00000001U)
#define CSL_LDC_CORE_ERR_STATUS_M_IBLK_OUTB_MAX                                (0x00000001U)

#define CSL_LDC_CORE_ERR_STATUS_P_IBLK_OUTB_MASK                               (0x00000001U)
#define CSL_LDC_CORE_ERR_STATUS_P_IBLK_OUTB_SHIFT                              (0x00000000U)
#define CSL_LDC_CORE_ERR_STATUS_P_IBLK_OUTB_MAX                                (0x00000001U)

/* DEBUG_CTRL */

#define CSL_LDC_CORE_DEBUG_CTRL_CFG_MEMACC_SEL_MASK                            (0x00000001U)
#define CSL_LDC_CORE_DEBUG_CTRL_CFG_MEMACC_SEL_SHIFT                           (0x00000000U)
#define CSL_LDC_CORE_DEBUG_CTRL_CFG_MEMACC_SEL_MAX                             (0x00000001U)

/* DEBUG_STATUS */

#define CSL_LDC_CORE_DEBUG_STATUS_PROC_STATUS_MASK                             (0x01000000U)
#define CSL_LDC_CORE_DEBUG_STATUS_PROC_STATUS_SHIFT                            (0x00000018U)
#define CSL_LDC_CORE_DEBUG_STATUS_PROC_STATUS_MAX                              (0x00000001U)

#define CSL_LDC_CORE_DEBUG_STATUS_FETCH_RESPSTATE_MASK                         (0x00070000U)
#define CSL_LDC_CORE_DEBUG_STATUS_FETCH_RESPSTATE_SHIFT                        (0x00000010U)
#define CSL_LDC_CORE_DEBUG_STATUS_FETCH_RESPSTATE_MAX                          (0x00000007U)

#define CSL_LDC_CORE_DEBUG_STATUS_FETCH_REQSTATE_MASK                          (0x00001F00U)
#define CSL_LDC_CORE_DEBUG_STATUS_FETCH_REQSTATE_SHIFT                         (0x00000008U)
#define CSL_LDC_CORE_DEBUG_STATUS_FETCH_REQSTATE_MAX                           (0x0000001FU)

#define CSL_LDC_CORE_DEBUG_STATUS_CTRL_STATE_MASK                              (0x0000000FU)
#define CSL_LDC_CORE_DEBUG_STATUS_CTRL_STATE_SHIFT                             (0x00000000U)
#define CSL_LDC_CORE_DEBUG_STATUS_CTRL_STATE_MAX                               (0x0000000FU)

/* FR_PDFTCH */

#define CSL_LDC_CORE_FR_PDFTCH_PBYTES_MASK                                     (0xFFFFFFFFU)
#define CSL_LDC_CORE_FR_PDFTCH_PBYTES_SHIFT                                    (0x00000000U)
#define CSL_LDC_CORE_FR_PDFTCH_PBYTES_MAX                                      (0xFFFFFFFFU)

/* FR_MDFTCH */

#define CSL_LDC_CORE_FR_MDFTCH_MBYTES_MASK                                     (0xFFFFFFFFU)
#define CSL_LDC_CORE_FR_MDFTCH_MBYTES_SHIFT                                    (0x00000000U)
#define CSL_LDC_CORE_FR_MDFTCH_MBYTES_MAX                                      (0xFFFFFFFFU)

/* PIXMEMOVF_BLK */

#define CSL_LDC_CORE_PIXMEMOVF_BLK_Y_MASK                                      (0x1FFF0000U)
#define CSL_LDC_CORE_PIXMEMOVF_BLK_Y_SHIFT                                     (0x00000010U)
#define CSL_LDC_CORE_PIXMEMOVF_BLK_Y_MAX                                       (0x00001FFFU)

#define CSL_LDC_CORE_PIXMEMOVF_BLK_X_MASK                                      (0x00001FFFU)
#define CSL_LDC_CORE_PIXMEMOVF_BLK_X_SHIFT                                     (0x00000000U)
#define CSL_LDC_CORE_PIXMEMOVF_BLK_X_MAX                                       (0x00001FFFU)

/* MESHMEMOVF_BLK */

#define CSL_LDC_CORE_MESHMEMOVF_BLK_Y_MASK                                     (0x1FFF0000U)
#define CSL_LDC_CORE_MESHMEMOVF_BLK_Y_SHIFT                                    (0x00000010U)
#define CSL_LDC_CORE_MESHMEMOVF_BLK_Y_MAX                                      (0x00001FFFU)

#define CSL_LDC_CORE_MESHMEMOVF_BLK_X_MASK                                     (0x00001FFFU)
#define CSL_LDC_CORE_MESHMEMOVF_BLK_X_SHIFT                                    (0x00000000U)
#define CSL_LDC_CORE_MESHMEMOVF_BLK_X_MAX                                      (0x00001FFFU)

/* OUTOFBOUND_BLK */

#define CSL_LDC_CORE_OUTOFBOUND_BLK_Y_MASK                                     (0x1FFF0000U)
#define CSL_LDC_CORE_OUTOFBOUND_BLK_Y_SHIFT                                    (0x00000010U)
#define CSL_LDC_CORE_OUTOFBOUND_BLK_Y_MAX                                      (0x00001FFFU)

#define CSL_LDC_CORE_OUTOFBOUND_BLK_X_MASK                                     (0x00001FFFU)
#define CSL_LDC_CORE_OUTOFBOUND_BLK_X_SHIFT                                    (0x00000000U)
#define CSL_LDC_CORE_OUTOFBOUND_BLK_X_MAX                                      (0x00001FFFU)

/**************************************************************************
* Hardware Region  : Width conversion LUT
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT[257];                  /* dualy width conversion LUT  */
} CSL_ldc_dualylutRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LDC_DUALYLUT_LUT(LUT)                                              (0x00000000U+((LUT)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT */

#define CSL_LDC_DUALYLUT_LUT_LUT_1_MASK                                        (0x0FFF0000U)
#define CSL_LDC_DUALYLUT_LUT_LUT_1_SHIFT                                       (0x00000010U)
#define CSL_LDC_DUALYLUT_LUT_LUT_1_MAX                                         (0x00000FFFU)

#define CSL_LDC_DUALYLUT_LUT_LUT_0_MASK                                        (0x00000FFFU)
#define CSL_LDC_DUALYLUT_LUT_LUT_0_SHIFT                                       (0x00000000U)
#define CSL_LDC_DUALYLUT_LUT_LUT_0_MAX                                         (0x00000FFFU)

/**************************************************************************
* Hardware Region  : Width conversion LUT
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t LUT[257];                  /* dualc width conversion LUT  */
} CSL_ldc_dualclutRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LDC_DUALCLUT_LUT(LUT)                                              (0x00000000U+((LUT)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* LUT */

#define CSL_LDC_DUALCLUT_LUT_LUT_1_MASK                                        (0x0FFF0000U)
#define CSL_LDC_DUALCLUT_LUT_LUT_1_SHIFT                                       (0x00000010U)
#define CSL_LDC_DUALCLUT_LUT_LUT_1_MAX                                         (0x00000FFFU)

#define CSL_LDC_DUALCLUT_LUT_LUT_0_MASK                                        (0x00000FFFU)
#define CSL_LDC_DUALCLUT_LUT_LUT_0_SHIFT                                       (0x00000000U)
#define CSL_LDC_DUALCLUT_LUT_LUT_0_MAX                                         (0x00000FFFU)

/**************************************************************************
* Hardware Region  : Config mapped mesh Memory
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM[1280];                 /*  mesh memory  */
} CSL_ldc_meshmemRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LDC_MESHMEM_RAM(RAM)                                               (0x00000000U+((RAM)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM */

#define CSL_LDC_MESHMEM_RAM_MEM_MASK                                           (0xFFFFFFFFU)
#define CSL_LDC_MESHMEM_RAM_MEM_SHIFT                                          (0x00000000U)
#define CSL_LDC_MESHMEM_RAM_MEM_MAX                                            (0xFFFFFFFFU)

/**************************************************************************
* Hardware Region  : Config mapped y Memory
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM[7168];                 /*  y memory  */
} CSL_ldc_ymemRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LDC_YMEM_RAM(RAM)                                                  (0x00000000U+((RAM)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM */

#define CSL_LDC_YMEM_RAM_RESERVED_MASK                                         (0xFF000000U)
#define CSL_LDC_YMEM_RAM_RESERVED_SHIFT                                        (0x00000018U)
#define CSL_LDC_YMEM_RAM_RESERVED_MAX                                          (0x000000FFU)

#define CSL_LDC_YMEM_RAM_MEM_MASK                                              (0x00FFFFFFU)
#define CSL_LDC_YMEM_RAM_MEM_SHIFT                                             (0x00000000U)
#define CSL_LDC_YMEM_RAM_MEM_MAX                                               (0x00FFFFFFU)

/**************************************************************************
* Hardware Region  : Config mapped cbcr Memory
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t RAM[7168];                 /*  cbcr memory  */
} CSL_ldc_cbcrmemRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LDC_CBCRMEM_RAM(RAM)                                               (0x00000000U+((RAM)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* RAM */

#define CSL_LDC_CBCRMEM_RAM_RESERVED_MASK                                      (0xFF000000U)
#define CSL_LDC_CBCRMEM_RAM_RESERVED_SHIFT                                     (0x00000018U)
#define CSL_LDC_CBCRMEM_RAM_RESERVED_MAX                                       (0x000000FFU)

#define CSL_LDC_CBCRMEM_RAM_MEM_MASK                                           (0x00FFFFFFU)
#define CSL_LDC_CBCRMEM_RAM_MEM_SHIFT                                          (0x00000000U)
#define CSL_LDC_CBCRMEM_RAM_MEM_MAX                                            (0x00FFFFFFU)

#ifdef __cplusplus
}
#endif
#endif

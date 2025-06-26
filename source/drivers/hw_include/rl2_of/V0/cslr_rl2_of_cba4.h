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
 *  Name        : cslr_rl2_of_cba4.h
 *  VPVERSION   : 3.0.378 - 2025.01.18.21.29.00
 *  VPREV       : 1.0.0.0
*/
#ifndef CSLR_RL2_OF_CBA4_H_
#define CSLR_RL2_OF_CBA4_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_RL2_OF_CBA4_REGS_BASE                                              (0x00000000U)


/**************************************************************************
* Hardware Region  : RL2_OF_CBA4 registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t ADR;                       /* REMote 'n' Address LSW */
    volatile uint32_t ADR_MSW;                   /* REMote 'n' Address MSW */
    volatile uint32_t LEN;                       /* REMote 'n' length */
    volatile uint8_t  Resv_16[4];
} CSL_rl2_of_cba4Regs_rem;


typedef struct {
    volatile uint32_t LO;                        /* FLC Lo address 'n' */
    volatile uint32_t LO_MSW;                    /* FLC Lo MSW address 'n' */
    volatile uint32_t HI;                        /* FLC High address 'n' */
    volatile uint32_t HI_MSW;                    /* FLC Hi MSW address 'n' */
    volatile uint32_t RA;                        /* FLC Remote Address 'n' */
    volatile uint32_t RA_MSW;                    /* FLC Remote Address 'n' */
    volatile uint32_t CTL;                       /* FLC Control 'n' */
    volatile uint8_t  Resv_32[4];
} CSL_rl2_of_cba4Regs_flc;


typedef struct {
    volatile uint32_t MOD_VER;                   /* Module and Version */
    volatile uint32_t L2_CTRL;                   /* Control Register */
    volatile uint32_t L2_STS;                    /* Status */
    volatile uint8_t  Resv_16[4];
    volatile uint32_t L2_LO_LSW;                 /* L2 Lo address LSW */
    volatile uint32_t L2_LO_MSW;                 /* L2 Lo address MSW */
    volatile uint32_t L2_HI;                     /* L2 Hi address LSW */
    volatile uint32_t L2_HI_MSW;                 /* L2 Hi address MSW */
    CSL_rl2_of_cba4Regs_rem REM;
    volatile uint8_t  Resv_120[72];
    volatile uint32_t L2HC;                      /* L2 HIT Counter register */
    volatile uint32_t L2MC;                      /* L2 MISS Counter register */
    volatile uint32_t IRQSTATUS_RAW;             /* Interrupt Raw Status Register */
    volatile uint32_t IRQSTATUS_MSK;             /* Interrupt Masked Status Register */
    volatile uint32_t IRQENABLE_SET;             /* Interrupt Enable Set Register */
    volatile uint32_t IRQENABLE_CLR;             /* Interrupt Enable Clear Register */
    volatile uint8_t  Resv_260[116];
    volatile uint32_t FLC_CFG;                   /* FLC Config Register */
    volatile uint32_t FLC_STS;                   /* FLC Status Register */
    volatile uint8_t  Resv_272[4];
    volatile uint32_t FLC_DBG0;                  /* FLC Debug 0 Register */
    volatile uint32_t FLC_DBG1;                  /* FLC Debug 1 Register */
    volatile uint32_t FLC_DBG2;                  /* FLC Debug 2 Register */
    volatile uint8_t  Resv_288[4];
    CSL_rl2_of_cba4Regs_flc FLC[4];
    volatile uint8_t  Resv_516[100];
    volatile uint32_t RAT_CFG;                   /* RAT Config Register */
    volatile uint8_t  Resv_768[248];
    volatile uint32_t TRK0_LO;                   /* Track Lo address 0 */
    volatile uint32_t TRK0_LO_MSW;               /* TRK Lo MSW address 0 */
    volatile uint32_t TRK0_HI;                   /* Track Hi address 0 */
    volatile uint32_t TRK0_HI_MSW;               /* TRK Hi MSW address 0 */
    volatile uint32_t TRK0_CTL;                  /* Track Control 0 */
} CSL_rl2_of_cba4Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_RL2_OF_CBA4_MOD_VER                                                (0x00000000U)
#define CSL_RL2_OF_CBA4_L2_CTRL                                                (0x00000004U)
#define CSL_RL2_OF_CBA4_L2_STS                                                 (0x00000008U)
#define CSL_RL2_OF_CBA4_L2_LO_LSW                                              (0x00000010U)
#define CSL_RL2_OF_CBA4_L2_LO_MSW                                              (0x00000014U)
#define CSL_RL2_OF_CBA4_L2_HI                                                  (0x00000018U)
#define CSL_RL2_OF_CBA4_L2_HI_MSW                                              (0x0000001CU)
#define CSL_RL2_OF_CBA4_REM_ADR                                                (0x00000020U)
#define CSL_RL2_OF_CBA4_REM_ADR_MSW                                            (0x00000024U)
#define CSL_RL2_OF_CBA4_REM_LEN                                                (0x00000028U)
#define CSL_RL2_OF_CBA4_L2HC                                                   (0x00000078U)
#define CSL_RL2_OF_CBA4_L2MC                                                   (0x0000007CU)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW                                          (0x00000080U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK                                          (0x00000084U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET                                          (0x00000088U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR                                          (0x0000008CU)
#define CSL_RL2_OF_CBA4_FLC_CFG                                                (0x00000104U)
#define CSL_RL2_OF_CBA4_FLC_STS                                                (0x00000108U)
#define CSL_RL2_OF_CBA4_FLC_DBG0                                               (0x00000110U)
#define CSL_RL2_OF_CBA4_FLC_DBG1                                               (0x00000114U)
#define CSL_RL2_OF_CBA4_FLC_DBG2                                               (0x00000118U)
#define CSL_RL2_OF_CBA4_FLC_LO(FLC)                                            (0x00000120U+((FLC)*0x20U))
#define CSL_RL2_OF_CBA4_FLC_LO_MSW(FLC)                                        (0x00000124U+((FLC)*0x20U))
#define CSL_RL2_OF_CBA4_FLC_HI(FLC)                                            (0x00000128U+((FLC)*0x20U))
#define CSL_RL2_OF_CBA4_FLC_HI_MSW(FLC)                                        (0x0000012CU+((FLC)*0x20U))
#define CSL_RL2_OF_CBA4_FLC_RA(FLC)                                            (0x00000130U+((FLC)*0x20U))
#define CSL_RL2_OF_CBA4_FLC_RA_MSW(FLC)                                        (0x00000134U+((FLC)*0x20U))
#define CSL_RL2_OF_CBA4_FLC_CTL(FLC)                                           (0x00000138U+((FLC)*0x20U))
#define CSL_RL2_OF_CBA4_RAT_CFG                                                (0x00000204U)
#define CSL_RL2_OF_CBA4_TRK0_LO                                                (0x00000300U)
#define CSL_RL2_OF_CBA4_TRK0_LO_MSW                                            (0x00000304U)
#define CSL_RL2_OF_CBA4_TRK0_HI                                                (0x00000308U)
#define CSL_RL2_OF_CBA4_TRK0_HI_MSW                                            (0x0000030CU)
#define CSL_RL2_OF_CBA4_TRK0_CTL                                               (0x00000310U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* ADR */

#define CSL_RL2_OF_CBA4_REM_ADR_ADR_LSW_MASK                                   (0xFFFFF800U)
#define CSL_RL2_OF_CBA4_REM_ADR_ADR_LSW_SHIFT                                  (0x0000000BU)
#define CSL_RL2_OF_CBA4_REM_ADR_ADR_LSW_MAX                                    (0x001FFFFFU)


/* ADR_MSW */

#define CSL_RL2_OF_CBA4_REM_ADR_MSW_ADR_MSW_MASK                               (0x0000FFFFU)
#define CSL_RL2_OF_CBA4_REM_ADR_MSW_ADR_MSW_SHIFT                              (0x00000000U)
#define CSL_RL2_OF_CBA4_REM_ADR_MSW_ADR_MSW_MAX                                (0x0000FFFFU)


/* LEN */

#define CSL_RL2_OF_CBA4_REM_LEN_LEN_MASK                                       (0x0007FFC0U)
#define CSL_RL2_OF_CBA4_REM_LEN_LEN_SHIFT                                      (0x00000006U)
#define CSL_RL2_OF_CBA4_REM_LEN_LEN_MAX                                        (0x00001FFFU)


/* LO */

#define CSL_RL2_OF_CBA4_FLC_LO_ADR_LO_LSW_MASK                                 (0xFFFFF000U)
#define CSL_RL2_OF_CBA4_FLC_LO_ADR_LO_LSW_SHIFT                                (0x0000000CU)
#define CSL_RL2_OF_CBA4_FLC_LO_ADR_LO_LSW_MAX                                  (0x000FFFFFU)


/* LO_MSW */

#define CSL_RL2_OF_CBA4_FLC_LO_MSW_ADR_LO_MSW_MASK                             (0x0000FFFFU)
#define CSL_RL2_OF_CBA4_FLC_LO_MSW_ADR_LO_MSW_SHIFT                            (0x00000000U)
#define CSL_RL2_OF_CBA4_FLC_LO_MSW_ADR_LO_MSW_MAX                              (0x0000FFFFU)


/* HI */

#define CSL_RL2_OF_CBA4_FLC_HI_ADR_HI_LSW_MASK                                 (0xFFFFF000U)
#define CSL_RL2_OF_CBA4_FLC_HI_ADR_HI_LSW_SHIFT                                (0x0000000CU)
#define CSL_RL2_OF_CBA4_FLC_HI_ADR_HI_LSW_MAX                                  (0x000FFFFFU)


/* HI_MSW */

#define CSL_RL2_OF_CBA4_FLC_HI_MSW_ADR_HI_MSW_MASK                             (0x0000FFFFU)
#define CSL_RL2_OF_CBA4_FLC_HI_MSW_ADR_HI_MSW_SHIFT                            (0x00000000U)
#define CSL_RL2_OF_CBA4_FLC_HI_MSW_ADR_HI_MSW_MAX                              (0x0000FFFFU)


/* RA */

#define CSL_RL2_OF_CBA4_FLC_RA_RADR_LSW_MASK                                   (0xFFFFF000U)
#define CSL_RL2_OF_CBA4_FLC_RA_RADR_LSW_SHIFT                                  (0x0000000CU)
#define CSL_RL2_OF_CBA4_FLC_RA_RADR_LSW_MAX                                    (0x000FFFFFU)


/* RA_MSW */

#define CSL_RL2_OF_CBA4_FLC_RA_MSW_RADR_MSW_MASK                               (0x0000FFFFU)
#define CSL_RL2_OF_CBA4_FLC_RA_MSW_RADR_MSW_SHIFT                              (0x00000000U)
#define CSL_RL2_OF_CBA4_FLC_RA_MSW_RADR_MSW_MAX                                (0x0000FFFFU)


/* CTL */

#define CSL_RL2_OF_CBA4_FLC_CTL_FENABLE_MASK                                   (0x80000000U)
#define CSL_RL2_OF_CBA4_FLC_CTL_FENABLE_SHIFT                                  (0x0000001FU)
#define CSL_RL2_OF_CBA4_FLC_CTL_FENABLE_MAX                                    (0x00000001U)

#define CSL_RL2_OF_CBA4_FLC_CTL_FCOPIED_MASK                                   (0x10000000U)
#define CSL_RL2_OF_CBA4_FLC_CTL_FCOPIED_SHIFT                                  (0x0000001CU)
#define CSL_RL2_OF_CBA4_FLC_CTL_FCOPIED_MAX                                    (0x00000001U)


/* MOD_VER */

#define CSL_RL2_OF_CBA4_MOD_VER_SCHEME_MASK                                    (0xC0000000U)
#define CSL_RL2_OF_CBA4_MOD_VER_SCHEME_SHIFT                                   (0x0000001EU)
#define CSL_RL2_OF_CBA4_MOD_VER_SCHEME_MAX                                     (0x00000003U)

#define CSL_RL2_OF_CBA4_MOD_VER_BU_MASK                                        (0x30000000U)
#define CSL_RL2_OF_CBA4_MOD_VER_BU_SHIFT                                       (0x0000001CU)
#define CSL_RL2_OF_CBA4_MOD_VER_BU_MAX                                         (0x00000003U)

#define CSL_RL2_OF_CBA4_MOD_VER_MODULE_ID_MASK                                 (0x0FFF0000U)
#define CSL_RL2_OF_CBA4_MOD_VER_MODULE_ID_SHIFT                                (0x00000010U)
#define CSL_RL2_OF_CBA4_MOD_VER_MODULE_ID_MAX                                  (0x00000FFFU)

#define CSL_RL2_OF_CBA4_MOD_VER_RTL_VERSION_MASK                               (0x0000F800U)
#define CSL_RL2_OF_CBA4_MOD_VER_RTL_VERSION_SHIFT                              (0x0000000BU)
#define CSL_RL2_OF_CBA4_MOD_VER_RTL_VERSION_MAX                                (0x0000001FU)

#define CSL_RL2_OF_CBA4_MOD_VER_MAJOR_REVISION_MASK                            (0x00000700U)
#define CSL_RL2_OF_CBA4_MOD_VER_MAJOR_REVISION_SHIFT                           (0x00000008U)
#define CSL_RL2_OF_CBA4_MOD_VER_MAJOR_REVISION_MAX                             (0x00000007U)

#define CSL_RL2_OF_CBA4_MOD_VER_CUSTOM_REVISION_MASK                           (0x000000C0U)
#define CSL_RL2_OF_CBA4_MOD_VER_CUSTOM_REVISION_SHIFT                          (0x00000006U)
#define CSL_RL2_OF_CBA4_MOD_VER_CUSTOM_REVISION_MAX                            (0x00000003U)

#define CSL_RL2_OF_CBA4_MOD_VER_MINOR_REVISION_MASK                            (0x0000003FU)
#define CSL_RL2_OF_CBA4_MOD_VER_MINOR_REVISION_SHIFT                           (0x00000000U)
#define CSL_RL2_OF_CBA4_MOD_VER_MINOR_REVISION_MAX                             (0x0000003FU)


/* L2_CTRL */

#define CSL_RL2_OF_CBA4_L2_CTRL_ENABLE_MASK                                    (0x80000000U)
#define CSL_RL2_OF_CBA4_L2_CTRL_ENABLE_SHIFT                                   (0x0000001FU)
#define CSL_RL2_OF_CBA4_L2_CTRL_ENABLE_MAX                                     (0x00000001U)

#define CSL_RL2_OF_CBA4_L2_CTRL_SIZE_MASK                                      (0x00000007U)
#define CSL_RL2_OF_CBA4_L2_CTRL_SIZE_SHIFT                                     (0x00000000U)
#define CSL_RL2_OF_CBA4_L2_CTRL_SIZE_MAX                                       (0x00000007U)


/* L2_STS */

#define CSL_RL2_OF_CBA4_L2_STS_OK_TO_GO_MASK                                   (0x80000000U)
#define CSL_RL2_OF_CBA4_L2_STS_OK_TO_GO_SHIFT                                  (0x0000001FU)
#define CSL_RL2_OF_CBA4_L2_STS_OK_TO_GO_MAX                                    (0x00000001U)


/* L2_LO_LSW */

#define CSL_RL2_OF_CBA4_L2_LO_LSW_ADDRESS_LO_LSW_MASK                          (0xFFFFF800U)
#define CSL_RL2_OF_CBA4_L2_LO_LSW_ADDRESS_LO_LSW_SHIFT                         (0x0000000BU)
#define CSL_RL2_OF_CBA4_L2_LO_LSW_ADDRESS_LO_LSW_MAX                           (0x001FFFFFU)


/* L2_LO_MSW */

#define CSL_RL2_OF_CBA4_L2_LO_MSW_ADDRESS_LO_MSW_MASK                          (0x0000FFFFU)
#define CSL_RL2_OF_CBA4_L2_LO_MSW_ADDRESS_LO_MSW_SHIFT                         (0x00000000U)
#define CSL_RL2_OF_CBA4_L2_LO_MSW_ADDRESS_LO_MSW_MAX                           (0x0000FFFFU)


/* L2_HI */

#define CSL_RL2_OF_CBA4_L2_HI_ADDRESS_HI_LSW_MASK                              (0xFFFFF800U)
#define CSL_RL2_OF_CBA4_L2_HI_ADDRESS_HI_LSW_SHIFT                             (0x0000000BU)
#define CSL_RL2_OF_CBA4_L2_HI_ADDRESS_HI_LSW_MAX                               (0x001FFFFFU)


/* L2_HI_MSW */

#define CSL_RL2_OF_CBA4_L2_HI_MSW_ADDRESS_HI_MSW_MASK                          (0x0000FFFFU)
#define CSL_RL2_OF_CBA4_L2_HI_MSW_ADDRESS_HI_MSW_SHIFT                         (0x00000000U)
#define CSL_RL2_OF_CBA4_L2_HI_MSW_ADDRESS_HI_MSW_MAX                           (0x0000FFFFU)


/* L2HC */

#define CSL_RL2_OF_CBA4_L2HC_HIT_MASK                                          (0xFFFFFFFFU)
#define CSL_RL2_OF_CBA4_L2HC_HIT_SHIFT                                         (0x00000000U)
#define CSL_RL2_OF_CBA4_L2HC_HIT_MAX                                           (0xFFFFFFFFU)


/* L2MC */

#define CSL_RL2_OF_CBA4_L2MC_MISS_MASK                                         (0xFFFFFFFFU)
#define CSL_RL2_OF_CBA4_L2MC_MISS_SHIFT                                        (0x00000000U)
#define CSL_RL2_OF_CBA4_L2MC_MISS_MAX                                          (0xFFFFFFFFU)


/* IRQSTATUS_RAW */

#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MASK                             (0x00000010U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_SHIFT                            (0x00000004U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MAX                              (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_WRERR_MASK                           (0x00000008U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_WRERR_SHIFT                          (0x00000003U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_WRERR_MAX                            (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_RDERR_MASK                           (0x00000004U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_RDERR_SHIFT                          (0x00000002U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_RDERR_MAX                            (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_WR_HIT_MASK                              (0x00000002U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_WR_HIT_SHIFT                             (0x00000001U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_WR_HIT_MAX                               (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_WR_ERR_MASK                              (0x00000001U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_WR_ERR_SHIFT                             (0x00000000U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_RAW_WR_ERR_MAX                               (0x00000001U)


/* IRQSTATUS_MSK */

#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_DON_MASK                             (0x00000010U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_DON_SHIFT                            (0x00000004U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_DON_MAX                              (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_WRERR_MASK                           (0x00000008U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_WRERR_SHIFT                          (0x00000003U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_WRERR_MAX                            (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_RDERR_MASK                           (0x00000004U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_RDERR_SHIFT                          (0x00000002U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_RDERR_MAX                            (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_WR_HIT_MASK                              (0x00000002U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_WR_HIT_SHIFT                             (0x00000001U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_WR_HIT_MAX                               (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_WR_ERR_MASK                              (0x00000001U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_WR_ERR_SHIFT                             (0x00000000U)
#define CSL_RL2_OF_CBA4_IRQSTATUS_MSK_WR_ERR_MAX                               (0x00000001U)


/* IRQENABLE_SET */

#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_FLC_DON_MASK                          (0x00000010U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_FLC_DON_SHIFT                         (0x00000004U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_FLC_DON_MAX                           (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_FLC_WRERR_MASK                        (0x00000008U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_FLC_WRERR_SHIFT                       (0x00000003U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_FLC_WRERR_MAX                         (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_FLC_RDERR_MASK                        (0x00000004U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_FLC_RDERR_SHIFT                       (0x00000002U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_FLC_RDERR_MAX                         (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_WR_HIT_MASK                           (0x00000002U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_WR_HIT_SHIFT                          (0x00000001U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_WR_HIT_MAX                            (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_WR_ERR_MASK                           (0x00000001U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_WR_ERR_SHIFT                          (0x00000000U)
#define CSL_RL2_OF_CBA4_IRQENABLE_SET_EN_WR_ERR_MAX                            (0x00000001U)


/* IRQENABLE_CLR */

#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_FLC_DON_MASK                          (0x00000010U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_FLC_DON_SHIFT                         (0x00000004U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_FLC_DON_MAX                           (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_FLC_WRERR_MASK                        (0x00000008U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_FLC_WRERR_SHIFT                       (0x00000003U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_FLC_WRERR_MAX                         (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_FLC_RDERR_MASK                        (0x00000004U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_FLC_RDERR_SHIFT                       (0x00000002U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_FLC_RDERR_MAX                         (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_WR_HIT_MASK                           (0x00000002U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_WR_HIT_SHIFT                          (0x00000001U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_WR_HIT_MAX                            (0x00000001U)

#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_WR_ERR_MASK                           (0x00000001U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_WR_ERR_SHIFT                          (0x00000000U)
#define CSL_RL2_OF_CBA4_IRQENABLE_CLR_EN_WR_ERR_MAX                            (0x00000001U)


/* FLC_CFG */

#define CSL_RL2_OF_CBA4_FLC_CFG_FIFO_BYPASS_MASK                               (0x80000000U)
#define CSL_RL2_OF_CBA4_FLC_CFG_FIFO_BYPASS_SHIFT                              (0x0000001FU)
#define CSL_RL2_OF_CBA4_FLC_CFG_FIFO_BYPASS_MAX                                (0x00000001U)

#define CSL_RL2_OF_CBA4_FLC_CFG_FLC_EXCNT_MASK                                 (0x07000000U)
#define CSL_RL2_OF_CBA4_FLC_CFG_FLC_EXCNT_SHIFT                                (0x00000018U)
#define CSL_RL2_OF_CBA4_FLC_CFG_FLC_EXCNT_MAX                                  (0x00000007U)

#define CSL_RL2_OF_CBA4_FLC_CFG_ASMNUM_MASK                                    (0x0000FF00U)
#define CSL_RL2_OF_CBA4_FLC_CFG_ASMNUM_SHIFT                                   (0x00000008U)
#define CSL_RL2_OF_CBA4_FLC_CFG_ASMNUM_MAX                                     (0x000000FFU)

#define CSL_RL2_OF_CBA4_FLC_CFG_RANGES_MASK                                    (0x000000FFU)
#define CSL_RL2_OF_CBA4_FLC_CFG_RANGES_SHIFT                                   (0x00000000U)
#define CSL_RL2_OF_CBA4_FLC_CFG_RANGES_MAX                                     (0x000000FFU)


/* FLC_STS */

#define CSL_RL2_OF_CBA4_FLC_STS_CPYCMP_MASK                                    (0x0000000FU)
#define CSL_RL2_OF_CBA4_FLC_STS_CPYCMP_SHIFT                                   (0x00000000U)
#define CSL_RL2_OF_CBA4_FLC_STS_CPYCMP_MAX                                     (0x0000000FU)


/* FLC_DBG0 */

#define CSL_RL2_OF_CBA4_FLC_DBG0_FLCIF_MASK                                    (0x80000000U)
#define CSL_RL2_OF_CBA4_FLC_DBG0_FLCIF_SHIFT                                   (0x0000001FU)
#define CSL_RL2_OF_CBA4_FLC_DBG0_FLCIF_MAX                                     (0x00000001U)

#define CSL_RL2_OF_CBA4_FLC_DBG0_FLC_OUT_CNT_MASK                              (0x07000000U)
#define CSL_RL2_OF_CBA4_FLC_DBG0_FLC_OUT_CNT_SHIFT                             (0x00000018U)
#define CSL_RL2_OF_CBA4_FLC_DBG0_FLC_OUT_CNT_MAX                               (0x00000007U)

#define CSL_RL2_OF_CBA4_FLC_DBG0_CURFLC_MASK                                   (0x00000003U)
#define CSL_RL2_OF_CBA4_FLC_DBG0_CURFLC_SHIFT                                  (0x00000000U)
#define CSL_RL2_OF_CBA4_FLC_DBG0_CURFLC_MAX                                    (0x00000003U)


/* FLC_DBG1 */

#define CSL_RL2_OF_CBA4_FLC_DBG1_FLCADR_LO_MASK                                (0xFFFFFFFFU)
#define CSL_RL2_OF_CBA4_FLC_DBG1_FLCADR_LO_SHIFT                               (0x00000000U)
#define CSL_RL2_OF_CBA4_FLC_DBG1_FLCADR_LO_MAX                                 (0xFFFFFFFFU)


/* FLC_DBG2 */

#define CSL_RL2_OF_CBA4_FLC_DBG2_FLCADR_HI_MASK                                (0x0000FFFFU)
#define CSL_RL2_OF_CBA4_FLC_DBG2_FLCADR_HI_SHIFT                               (0x00000000U)
#define CSL_RL2_OF_CBA4_FLC_DBG2_FLCADR_HI_MAX                                 (0x0000FFFFU)


/* RAT_CFG */

#define CSL_RL2_OF_CBA4_RAT_CFG_ADDR_WIDTH_MASK                                (0x00FF0000U)
#define CSL_RL2_OF_CBA4_RAT_CFG_ADDR_WIDTH_SHIFT                               (0x00000010U)
#define CSL_RL2_OF_CBA4_RAT_CFG_ADDR_WIDTH_MAX                                 (0x000000FFU)

#define CSL_RL2_OF_CBA4_RAT_CFG_REGIONS_MASK                                   (0x000000FFU)
#define CSL_RL2_OF_CBA4_RAT_CFG_REGIONS_SHIFT                                  (0x00000000U)
#define CSL_RL2_OF_CBA4_RAT_CFG_REGIONS_MAX                                    (0x000000FFU)


/* TRK0_LO */

#define CSL_RL2_OF_CBA4_TRK0_LO_TRK0_ADR_LO_LSW_MASK                           (0xFFFFF000U)
#define CSL_RL2_OF_CBA4_TRK0_LO_TRK0_ADR_LO_LSW_SHIFT                          (0x0000000CU)
#define CSL_RL2_OF_CBA4_TRK0_LO_TRK0_ADR_LO_LSW_MAX                            (0x000FFFFFU)


/* TRK0_LO_MSW */

#define CSL_RL2_OF_CBA4_TRK0_LO_MSW_TRK0_ADR_LO_MSW_MASK                       (0x0000FFFFU)
#define CSL_RL2_OF_CBA4_TRK0_LO_MSW_TRK0_ADR_LO_MSW_SHIFT                      (0x00000000U)
#define CSL_RL2_OF_CBA4_TRK0_LO_MSW_TRK0_ADR_LO_MSW_MAX                        (0x0000FFFFU)


/* TRK0_HI */

#define CSL_RL2_OF_CBA4_TRK0_HI_TRK0_ADR_HI_LSW_MASK                           (0xFFFFF000U)
#define CSL_RL2_OF_CBA4_TRK0_HI_TRK0_ADR_HI_LSW_SHIFT                          (0x0000000CU)
#define CSL_RL2_OF_CBA4_TRK0_HI_TRK0_ADR_HI_LSW_MAX                            (0x000FFFFFU)


/* TRK0_HI_MSW */

#define CSL_RL2_OF_CBA4_TRK0_HI_MSW_TRK0_ADR_HI_MSW_MASK                       (0x0000FFFFU)
#define CSL_RL2_OF_CBA4_TRK0_HI_MSW_TRK0_ADR_HI_MSW_SHIFT                      (0x00000000U)
#define CSL_RL2_OF_CBA4_TRK0_HI_MSW_TRK0_ADR_HI_MSW_MAX                        (0x0000FFFFU)


/* TRK0_CTL */

#define CSL_RL2_OF_CBA4_TRK0_CTL_TRK0_FENABLE_MASK                             (0x80000000U)
#define CSL_RL2_OF_CBA4_TRK0_CTL_TRK0_FENABLE_SHIFT                            (0x0000001FU)
#define CSL_RL2_OF_CBA4_TRK0_CTL_TRK0_FENABLE_MAX                              (0x00000001U)


#ifdef __cplusplus
}
#endif
#endif

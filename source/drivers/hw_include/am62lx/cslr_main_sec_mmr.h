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
 *  Name        : cslr_main_sec_mmr.h
*/
#ifndef CSLR_MAIN_SEC_MMR_H_
#define CSLR_MAIN_SEC_MMR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_MAIN_SEC_MMR_CFG0_REGS_BASE                                   (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG1_REGS_BASE                                   (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG2_REGS_BASE                                   (0x00000000U)


/**************************************************************************
* Hardware Region  : MMRs in region 0
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t PID;                       /* PID register */
    volatile uint8_t  Resv_16[12];
    volatile uint32_t CLSTR0_CTRL;
    volatile uint8_t  Resv_24[4];
    volatile uint32_t CLSTR0_STAT;
    volatile uint8_t  Resv_32[4];
    volatile uint32_t CLSTR0_PM_CTRL;
    volatile uint32_t CLSTR0_PM_STAT;
    volatile uint8_t  Resv_256[216];
    volatile uint32_t CLSTR0_CORE0_CTRL;
    volatile uint32_t CLSTR0_CORE0_STAT;
    volatile uint8_t  Resv_268[4];
    volatile uint32_t CLSTR0_CORE0_BOOTVECT;
    volatile uint32_t CLSTR0_CORE1_CTRL;
    volatile uint32_t CLSTR0_CORE1_STAT;
    volatile uint8_t  Resv_284[4];
    volatile uint32_t CLSTR0_CORE1_BOOTVECT;
} CSL_main_sec_mmr_cfg0Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_SEC_MMR_CFG0_PID                                         (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL                                 (0x00000010U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_STAT                                 (0x00000018U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL                              (0x00000020U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT                              (0x00000024U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_CTRL                           (0x00000100U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_STAT                           (0x00000104U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_BOOTVECT                       (0x0000010CU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_CTRL                           (0x00000110U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_STAT                           (0x00000114U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_BOOTVECT                       (0x0000011CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MINOR_MASK                          (0x0000003FU)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MINOR_SHIFT                         (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MINOR_MAX                           (0x0000003FU)

#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_CUSTOM_MASK                         (0x000000C0U)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_CUSTOM_SHIFT                        (0x00000006U)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_CUSTOM_MAX                          (0x00000003U)

#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MAJOR_MASK                          (0x00000700U)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MAJOR_SHIFT                         (0x00000008U)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MAJOR_MAX                           (0x00000007U)

#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MISC_MASK                           (0x0000F800U)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MISC_SHIFT                          (0x0000000BU)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MISC_MAX                            (0x0000001FU)

#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MSB16_MASK                          (0xFFFF0000U)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MSB16_SHIFT                         (0x00000010U)
#define CSL_MAIN_SEC_MMR_CFG0_PID_PID_MSB16_MAX                           (0x0000FFFFU)

/* CLSTR0_CTRL */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE0_AA64NAA32_MASK            (0x00000001U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE0_AA64NAA32_SHIFT           (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE0_AA64NAA32_MAX             (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE1_AA64NAA32_MASK            (0x00000002U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE1_AA64NAA32_SHIFT           (0x00000001U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE1_AA64NAA32_MAX             (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE0_CFGTE_MASK                (0x00000010U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE0_CFGTE_SHIFT               (0x00000004U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE0_CFGTE_MAX                 (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE1_CFGTE_MASK                (0x00000020U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE1_CFGTE_SHIFT               (0x00000005U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE1_CFGTE_MAX                 (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE0_CP15SDISABLE_MASK         (0x00001000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE0_CP15SDISABLE_SHIFT        (0x0000000CU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE0_CP15SDISABLE_MAX          (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE1_CP15SDISABLE_MASK         (0x00002000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE1_CP15SDISABLE_SHIFT        (0x0000000DU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_CORE1_CP15SDISABLE_MAX          (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_DBGL1RSTDISABLE_MASK            (0x00010000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_DBGL1RSTDISABLE_SHIFT           (0x00000010U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CTRL_DBGL1RSTDISABLE_MAX             (0x00000001U)

/* CLSTR0_STAT */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_STAT_RSV_MASK                        (0xFFFFFFFFU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_STAT_RSV_SHIFT                       (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_STAT_RSV_MAX                         (0xFFFFFFFFU)

/* CLSTR0_PM_CTRL */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_AINCTS_MASK                  (0x00000002U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_AINCTS_SHIFT                 (0x00000001U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_AINCTS_MAX                   (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_L2FLUSHREQ_MASK              (0x00000020U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_L2FLUSHREQ_SHIFT             (0x00000005U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_L2FLUSHREQ_MAX               (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_CLREXMONREQ_MASK             (0x00000040U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_CLREXMONREQ_SHIFT            (0x00000006U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_CLREXMONREQ_MAX              (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_CORE0_DBGPWRDUP_MASK         (0x00000100U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_CORE0_DBGPWRDUP_SHIFT        (0x00000008U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_CORE0_DBGPWRDUP_MAX          (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_CORE1_DBGPWRDUP_MASK         (0x00000200U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_CORE1_DBGPWRDUP_SHIFT        (0x00000009U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_CORE1_DBGPWRDUP_MAX          (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_L2RSTDISABLE_MASK            (0x00001000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_L2RSTDISABLE_SHIFT           (0x0000000CU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_CTRL_L2RSTDISABLE_MAX             (0x00000001U)

/* CLSTR0_PM_STAT */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE0_WFI_MASK               (0x00000001U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE0_WFI_SHIFT              (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE0_WFI_MAX                (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE1_WFI_MASK               (0x00000002U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE1_WFI_SHIFT              (0x00000001U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE1_WFI_MAX                (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE0_WFE_MASK               (0x00000010U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE0_WFE_SHIFT              (0x00000004U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE0_WFE_MAX                (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE1_WFE_MASK               (0x00000020U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE1_WFE_SHIFT              (0x00000005U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE1_WFE_MAX                (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE0_SMPEN_MASK             (0x00000100U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE0_SMPEN_SHIFT            (0x00000008U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE0_SMPEN_MAX              (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE1_SMPEN_MASK             (0x00000200U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE1_SMPEN_SHIFT            (0x00000009U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CORE1_SMPEN_MAX              (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_L2FLUSHDONE_MASK             (0x00001000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_L2FLUSHDONE_SHIFT            (0x0000000CU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_L2FLUSHDONE_MAX              (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_STANDBYWFIL2_MASK            (0x00002000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_STANDBYWFIL2_SHIFT           (0x0000000DU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_STANDBYWFIL2_MAX             (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CLREXMONACK_MASK             (0x00004000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CLREXMONACK_SHIFT            (0x0000000EU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_PM_STAT_CLREXMONACK_MAX              (0x00000001U)

/* CLSTR0_CORE0_CTRL */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_CTRL_RSV_MASK                  (0xFFFFFFFFU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_CTRL_RSV_SHIFT                 (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_CTRL_RSV_MAX                   (0xFFFFFFFFU)

/* CLSTR0_CORE0_STAT */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_STAT_RSV_MASK                  (0xFFFFFFFFU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_STAT_RSV_SHIFT                 (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_STAT_RSV_MAX                   (0xFFFFFFFFU)

/* CLSTR0_CORE0_BOOTVECT */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_BOOTVECT_VECT_ADDR_MASK        (0xFFFFFFFFU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_BOOTVECT_VECT_ADDR_SHIFT       (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE0_BOOTVECT_VECT_ADDR_MAX         (0xFFFFFFFFU)

/* CLSTR0_CORE1_CTRL */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_CTRL_RSV_MASK                  (0xFFFFFFFFU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_CTRL_RSV_SHIFT                 (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_CTRL_RSV_MAX                   (0xFFFFFFFFU)

/* CLSTR0_CORE1_STAT */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_STAT_RSV_MASK                  (0xFFFFFFFFU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_STAT_RSV_SHIFT                 (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_STAT_RSV_MAX                   (0xFFFFFFFFU)

/* CLSTR0_CORE1_BOOTVECT */

#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_BOOTVECT_VECT_ADDR_MASK        (0xFFFFFFFFU)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_BOOTVECT_VECT_ADDR_SHIFT       (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG0_CLSTR0_CORE1_BOOTVECT_VECT_ADDR_MAX         (0xFFFFFFFFU)

/**************************************************************************
* Hardware Region  : MMRs in region 1
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t GIC_CONFIG_CLSTR0;
} CSL_main_sec_mmr_cfg1Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_SEC_MMR_CFG1_GIC_CONFIG_CLSTR0                           (0x00000000U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* GIC_CONFIG_CLSTR0 */

#define CSL_MAIN_SEC_MMR_CFG1_GIC_CONFIG_CLSTR0_CORE0_ACTIVE_MASK         (0x00000001U)
#define CSL_MAIN_SEC_MMR_CFG1_GIC_CONFIG_CLSTR0_CORE0_ACTIVE_SHIFT        (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG1_GIC_CONFIG_CLSTR0_CORE0_ACTIVE_MAX          (0x00000001U)

#define CSL_MAIN_SEC_MMR_CFG1_GIC_CONFIG_CLSTR0_CORE1_ACTIVE_MASK         (0x00000002U)
#define CSL_MAIN_SEC_MMR_CFG1_GIC_CONFIG_CLSTR0_CORE1_ACTIVE_SHIFT        (0x00000001U)
#define CSL_MAIN_SEC_MMR_CFG1_GIC_CONFIG_CLSTR0_CORE1_ACTIVE_MAX          (0x00000001U)

/**************************************************************************
* Hardware Region  : MMRs in region 2
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CLSTR0_CORE0_DBG_CFG;
    volatile uint8_t  Resv_64[60];
    volatile uint32_t CLSTR0_CORE1_DBG_CFG;
} CSL_main_sec_mmr_cfg2Regs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG                        (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG                        (0x00000040U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CLSTR0_CORE0_DBG_CFG */

#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_DBGEN_MASK             (0x0000000FU)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_DBGEN_SHIFT            (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_DBGEN_MAX              (0x0000000FU)

#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_NIDEN_MASK             (0x000000F0U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_NIDEN_SHIFT            (0x00000004U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_NIDEN_MAX              (0x0000000FU)

#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_SPIDEN_MASK            (0x00000F00U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_SPIDEN_SHIFT           (0x00000008U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_SPIDEN_MAX             (0x0000000FU)

#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_SPNIDEN_MASK           (0x0000F000U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_SPNIDEN_SHIFT          (0x0000000CU)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE0_DBG_CFG_SPNIDEN_MAX            (0x0000000FU)

/* CLSTR0_CORE1_DBG_CFG */

#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_DBGEN_MASK             (0x0000000FU)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_DBGEN_SHIFT            (0x00000000U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_DBGEN_MAX              (0x0000000FU)

#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_NIDEN_MASK             (0x000000F0U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_NIDEN_SHIFT            (0x00000004U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_NIDEN_MAX              (0x0000000FU)

#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_SPIDEN_MASK            (0x00000F00U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_SPIDEN_SHIFT           (0x00000008U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_SPIDEN_MAX             (0x0000000FU)

#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_SPNIDEN_MASK           (0x0000F000U)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_SPNIDEN_SHIFT          (0x0000000CU)
#define CSL_MAIN_SEC_MMR_CFG2_CLSTR0_CORE1_DBG_CFG_SPNIDEN_MAX            (0x0000000FU)

#ifdef __cplusplus
}
#endif
#endif
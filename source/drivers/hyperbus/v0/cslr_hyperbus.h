/********************************************************************
*
*  Copyright (C) 2019 Texas Instruments Incorporated.
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
*  Name    : cslr_hyperbus.h
*
*/
#ifndef CSLR_HYPERBUS_H_
#define CSLR_HYPERBUS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : hyperbus_dat0
**************************************************************************/

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
   volatile uint32_t                         HPB_DATA_MEM[67108864];
} CSL_hyperbus_dat0Regs;

/************************************************************************
* Register Macros
**************************************************************************/

#define CSL_HYPERBUS_DAT0_HPB_DATA_MEM(IDX)                           ( 0x0U +  ((IDX)*0x4U) )

/************************************************************************
* Field Definition Macros
**************************************************************************/

/* HPB_DATA_MEM */

#define CSL_HYPERBUS_DAT0_HPB_DATA_MEM_HPB_DATA_MASK                       (0xffffffffU)
#define CSL_HYPERBUS_DAT0_HPB_DATA_MEM_HPB_DATA_SHIFT                      (0x0U)
#define CSL_HYPERBUS_DAT0_HPB_DATA_MEM_HPB_DATA_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_DAT0_HPB_DATA_MEM_RESETVAL                            0x0
/**************************************************************************
* Hardware Region  : hyperbus_dat1
**************************************************************************/

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
   volatile uint32_t                         HPB_DATA_MEM[67108864];
} CSL_hyperbus_dat1Regs;

/************************************************************************
* Register Macros
**************************************************************************/

#define CSL_HYPERBUS_DAT1_HPB_DATA_MEM(IDX)                           ( 0x0U +  ((IDX)*0x4U) )

/************************************************************************
* Field Definition Macros
**************************************************************************/

/* HPB_DATA_MEM */

#define CSL_HYPERBUS_DAT1_HPB_DATA_MEM_HPB_DATA_MASK                       (0xffffffffU)
#define CSL_HYPERBUS_DAT1_HPB_DATA_MEM_HPB_DATA_SHIFT                      (0x0U)
#define CSL_HYPERBUS_DAT1_HPB_DATA_MEM_HPB_DATA_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_DAT1_HPB_DATA_MEM_RESETVAL                            0x0
/**************************************************************************
* Hardware Region  : hyperbus_syscfg
**************************************************************************/

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
   volatile uint32_t                         REVISION_REG;
   volatile uint32_t                         DLL_STAT_REG;
   volatile uint32_t                         RAM_STAT_REG;
} CSL_hyperbus_syscfgRegs;

/************************************************************************
* Register Macros
**************************************************************************/

#define CSL_FSS0_CFG_BASE                                             (0x47000000U)
#define CSL_FSS0_HPB_SS_CFG_BASE                                      (0x47030000U)
#define CSL_FSS0_HPB_CTRL_BASE                                        (0x47034000U)
#define CSL_FSS0_HPB_ECC_AGGR_BASE                                    (0x47060000U)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG                              (0x00000000U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG                              (0x00000004U)
#define CSL_HYPERBUS_SYSCFG_RAM_STAT_REG                              (0x00000008U)

#define CSL_MCU_RAT_CFG_BASE                                          (0x40F90000U)

/************************************************************************
* Field Definition Macros
**************************************************************************/

/* REVISION_REG */

#define CSL_HYPERBUS_SYSCFG_REVISION_REG_MODID_MASK                        (0xffff0000U)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_MODID_SHIFT                       (0x10U)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_MODID_RESETVAL                    (0x1accU)

#define CSL_HYPERBUS_SYSCFG_REVISION_REG_REVRTL_MASK                       (0xf800U)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_REVRTL_SHIFT                      (0xbU)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_REVRTL_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_SYSCFG_REVISION_REG_REVMAJ_MASK                       (0x700U)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_REVMAJ_SHIFT                      (0x8U)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_REVMAJ_RESETVAL                   (0x1U)

#define CSL_HYPERBUS_SYSCFG_REVISION_REG_CUSTOM_MASK                       (0xc0U)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_CUSTOM_SHIFT                      (0x6U)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_CUSTOM_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_SYSCFG_REVISION_REG_REVMIN_MASK                       (0x3fU)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_REVMIN_SHIFT                      (0x0U)
#define CSL_HYPERBUS_SYSCFG_REVISION_REG_REVMIN_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_SYSCFG_REVISION_REG_RESETVAL                          0x1acc0100
/* DLL_STAT_REG */

#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_RSVD04_MASK                       (0xfffff800U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_RSVD04_SHIFT                      (0xbU)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_RSVD04_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_CODE_MASK                    (0x7fcU)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_CODE_SHIFT                   (0x2U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_CODE_RESETVAL                (0x0U)

#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_CODE_VALID_MASK              (0x2U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_CODE_VALID_SHIFT             (0x1U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_CODE_VALID_RESETVAL          (0x0U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_SDL_LOCK_MASK                     (0x00000002U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_SDL_LOCK_SHIFT                    (0x00000001U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_SDL_LOCK_MAX                      (0x00000001U)

#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_LOCK_MASK                    (0x1U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_LOCK_SHIFT                   (0x0U)
#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_MDLL_LOCK_RESETVAL                (0x0U)

#define CSL_HYPERBUS_SYSCFG_DLL_STAT_REG_RESETVAL                          (0x0U)
/* RAM_STAT_REG */

#define CSL_HYPERBUS_SYSCFG_RAM_STAT_REG_INIT_DONE_MASK                    (0x00000001U)
#define CSL_HYPERBUS_SYSCFG_RAM_STAT_REG_INIT_DONE_SHIFT                   (0x00000000U)
#define CSL_HYPERBUS_SYSCFG_RAM_STAT_REG_INIT_DONE_MAX                     (0x00000001U)

/**************************************************************************
* Hardware Region  : hyperbus_core
**************************************************************************/

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
   volatile uint32_t                         CSR;
   volatile uint32_t                         IER;
   volatile uint32_t                         ISR;
   volatile uint8_t                          Rsvd0[4];
   volatile uint32_t                         MBAR[2];
   volatile uint8_t                          Rsvd1[8];
   volatile uint32_t                         MCR[2];
   volatile uint8_t                          Rsvd2[8];
   volatile uint32_t                         MTR[2];
   volatile uint8_t                          Rsvd3[8];
   volatile uint32_t                         GPOR;
   volatile uint32_t                         WPR;
   volatile uint32_t                         LBR;
} CSL_hyperbus_coreRegs;

/************************************************************************
* Register Macros
**************************************************************************/

#define CSL_HYPERBUS_CORE_CSR                                         ( 0x0U )
#define CSL_HYPERBUS_CORE_IER                                         ( 0x0U + 0x4U )
#define CSL_HYPERBUS_CORE_ISR                                         ( 0x0U + 0x8U )
#define CSL_HYPERBUS_CORE_MBAR(IDX)                                   ( 0x0U +  (0x10U + ((IDX)*0x4U)) )
#define CSL_HYPERBUS_CORE_MCR(IDX)                                    ( 0x0U +  (0x20U + ((IDX)*0x4U)) )
#define CSL_HYPERBUS_CORE_MTR(IDX)                                    ( 0x0U +  (0x30U + ((IDX)*0x4U)) )
#define CSL_HYPERBUS_CORE_GPOR                                        ( 0x0U + 0x40U )
#define CSL_HYPERBUS_CORE_WPR                                         ( 0x0U + 0x44U )
#define CSL_HYPERBUS_CORE_LBR                                         ( 0x0U + 0x48U )

/************************************************************************
* Field Definition Macros
**************************************************************************/

/* CSR */

#define CSL_HYPERBUS_CORE_CSR_RACT_MASK                                    (0x1U)
#define CSL_HYPERBUS_CORE_CSR_RACT_SHIFT                                   (0x0U)
#define CSL_HYPERBUS_CORE_CSR_RACT_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_CSR_RFU0_MASK                                    (0xfeU)
#define CSL_HYPERBUS_CORE_CSR_RFU0_SHIFT                                   (0x1U)
#define CSL_HYPERBUS_CORE_CSR_RFU0_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_CSR_RDECERR_MASK                                 (0x100U)
#define CSL_HYPERBUS_CORE_CSR_RDECERR_SHIFT                                (0x8U)
#define CSL_HYPERBUS_CORE_CSR_RDECERR_RESETVAL                             (0x0U)

#define CSL_HYPERBUS_CORE_CSR_RTRSERR_MASK                                 (0x200U)
#define CSL_HYPERBUS_CORE_CSR_RTRSERR_SHIFT                                (0x9U)
#define CSL_HYPERBUS_CORE_CSR_RTRSERR_RESETVAL                             (0x0U)

#define CSL_HYPERBUS_CORE_CSR_RRSTOERR_MASK                                (0x400U)
#define CSL_HYPERBUS_CORE_CSR_RRSTOERR_SHIFT                               (0xaU)
#define CSL_HYPERBUS_CORE_CSR_RRSTOERR_RESETVAL                            (0x0U)

#define CSL_HYPERBUS_CORE_CSR_RDSSTALL_MASK                                (0x800U)
#define CSL_HYPERBUS_CORE_CSR_RDSSTALL_SHIFT                               (0xbU)
#define CSL_HYPERBUS_CORE_CSR_RDSSTALL_RESETVAL                            (0x0U)

#define CSL_HYPERBUS_CORE_CSR_RFU1_MASK                                    (0xf000U)
#define CSL_HYPERBUS_CORE_CSR_RFU1_SHIFT                                   (0xcU)
#define CSL_HYPERBUS_CORE_CSR_RFU1_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_CSR_WACT_MASK                                    (0x10000U)
#define CSL_HYPERBUS_CORE_CSR_WACT_SHIFT                                   (0x10U)
#define CSL_HYPERBUS_CORE_CSR_WACT_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_CSR_RFU2_MASK                                    (0xfe0000U)
#define CSL_HYPERBUS_CORE_CSR_RFU2_SHIFT                                   (0x11U)
#define CSL_HYPERBUS_CORE_CSR_RFU2_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_CSR_WDECERR_MASK                                 (0x1000000U)
#define CSL_HYPERBUS_CORE_CSR_WDECERR_SHIFT                                (0x18U)
#define CSL_HYPERBUS_CORE_CSR_WDECERR_RESETVAL                             (0x0U)

#define CSL_HYPERBUS_CORE_CSR_WTRSERR_MASK                                 (0x2000000U)
#define CSL_HYPERBUS_CORE_CSR_WTRSERR_SHIFT                                (0x19U)
#define CSL_HYPERBUS_CORE_CSR_WTRSERR_RESETVAL                             (0x0U)

#define CSL_HYPERBUS_CORE_CSR_WRSTOERR_MASK                                (0x4000000U)
#define CSL_HYPERBUS_CORE_CSR_WRSTOERR_SHIFT                               (0x1aU)
#define CSL_HYPERBUS_CORE_CSR_WRSTOERR_RESETVAL                            (0x0U)

#define CSL_HYPERBUS_CORE_CSR_RFU3_MASK                                    (0xf8000000U)
#define CSL_HYPERBUS_CORE_CSR_RFU3_SHIFT                                   (0x1bU)
#define CSL_HYPERBUS_CORE_CSR_RFU3_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_CSR_RESETVAL                                     0x0
/* IER */

#define CSL_HYPERBUS_CORE_IER_RPCINTE_MASK                                 (0x1U)
#define CSL_HYPERBUS_CORE_IER_RPCINTE_SHIFT                                (0x0U)
#define CSL_HYPERBUS_CORE_IER_RPCINTE_RESETVAL                             (0x0U)

#define CSL_HYPERBUS_CORE_IER_RFU4_MASK                                    (0x7ffffffeU)
#define CSL_HYPERBUS_CORE_IER_RFU4_SHIFT                                   (0x1U)
#define CSL_HYPERBUS_CORE_IER_RFU4_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_IER_INTP_MASK                                    (0x80000000U)
#define CSL_HYPERBUS_CORE_IER_INTP_SHIFT                                   (0x1fU)
#define CSL_HYPERBUS_CORE_IER_INTP_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_IER_RESETVAL                                     0x0
/* ISR */

#define CSL_HYPERBUS_CORE_ISR_RPCINTS_MASK                                 (0x1U)
#define CSL_HYPERBUS_CORE_ISR_RPCINTS_SHIFT                                (0x0U)
#define CSL_HYPERBUS_CORE_ISR_RPCINTS_RESETVAL                             (0x0U)

#define CSL_HYPERBUS_CORE_ISR_RFU5_MASK                                    (0xfffffffeU)
#define CSL_HYPERBUS_CORE_ISR_RFU5_SHIFT                                   (0x1U)
#define CSL_HYPERBUS_CORE_ISR_RFU5_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_ISR_RESETVAL                                     0x0
/* MBAR */

#define CSL_HYPERBUS_CORE_MBAR_A_LSB_MASK                                  (0xffffffU)
#define CSL_HYPERBUS_CORE_MBAR_A_LSB_SHIFT                                 (0x0U)
#define CSL_HYPERBUS_CORE_MBAR_A_LSB_RESETVAL                              (0x0U)

#define CSL_HYPERBUS_CORE_MBAR_A_MSB_MASK                                  (0xff000000U)
#define CSL_HYPERBUS_CORE_MBAR_A_MSB_SHIFT                                 (0x18U)
#define CSL_HYPERBUS_CORE_MBAR_A_MSB_RESETVAL                              (0x0U)

#define CSL_HYPERBUS_CORE_MBAR_RESETVAL                                    0x0
/* MCR */

#define CSL_HYPERBUS_CORE_MCR_WRAPSIZE_MASK                                (0x3U)
#define CSL_HYPERBUS_CORE_MCR_WRAPSIZE_SHIFT                               (0x0U)
#define CSL_HYPERBUS_CORE_MCR_WRAPSIZE_RESETVAL                            (0x3U)

#define CSL_HYPERBUS_CORE_MCR_RFU6_MASK                                    (0xcU)
#define CSL_HYPERBUS_CORE_MCR_RFU6_SHIFT                                   (0x2U)
#define CSL_HYPERBUS_CORE_MCR_RFU6_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_MCR_DEVTYPE_MASK                                 (0x10U)
#define CSL_HYPERBUS_CORE_MCR_DEVTYPE_SHIFT                                (0x4U)
#define CSL_HYPERBUS_CORE_MCR_DEVTYPE_RESETVAL                             (0x0U)

#define CSL_HYPERBUS_CORE_MCR_CRT_MASK                                     (0x20U)
#define CSL_HYPERBUS_CORE_MCR_CRT_SHIFT                                    (0x5U)
#define CSL_HYPERBUS_CORE_MCR_CRT_RESETVAL                                 (0x0U)

#define CSL_HYPERBUS_CORE_MCR_RFU7_MASK                                    (0xffc0U)
#define CSL_HYPERBUS_CORE_MCR_RFU7_SHIFT                                   (0x6U)
#define CSL_HYPERBUS_CORE_MCR_RFU7_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_MCR_ACS_MASK                                     (0x10000U)
#define CSL_HYPERBUS_CORE_MCR_ACS_SHIFT                                    (0x10U)
#define CSL_HYPERBUS_CORE_MCR_ACS_RESETVAL                                 (0x0U)

#define CSL_HYPERBUS_CORE_MCR_TCMO_MASK                                    (0x20000U)
#define CSL_HYPERBUS_CORE_MCR_TCMO_SHIFT                                   (0x11U)
#define CSL_HYPERBUS_CORE_MCR_TCMO_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_MCR_MAXLEN_MASK                                  (0x7fc0000U)
#define CSL_HYPERBUS_CORE_MCR_MAXLEN_SHIFT                                 (0x12U)
#define CSL_HYPERBUS_CORE_MCR_MAXLEN_RESETVAL                              (0x0U)

#define CSL_HYPERBUS_CORE_MCR_RFU8_MASK                                    (0x78000000U)
#define CSL_HYPERBUS_CORE_MCR_RFU8_SHIFT                                   (0x1bU)
#define CSL_HYPERBUS_CORE_MCR_RFU8_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_MCR_MAXEN_MASK                                   (0x80000000U)
#define CSL_HYPERBUS_CORE_MCR_MAXEN_SHIFT                                  (0x1fU)
#define CSL_HYPERBUS_CORE_MCR_MAXEN_RESETVAL                               (0x0U)

#define CSL_HYPERBUS_CORE_MCR_RESETVAL                                     0x3
/* MTR */

#define CSL_HYPERBUS_CORE_MTR_LTCY_MASK                                    (0xfU)
#define CSL_HYPERBUS_CORE_MTR_LTCY_SHIFT                                   (0x0U)
#define CSL_HYPERBUS_CORE_MTR_LTCY_RESETVAL                                (0x1U)

#define CSL_HYPERBUS_CORE_MTR_RFU12_MASK                                   (0xf0U)
#define CSL_HYPERBUS_CORE_MTR_RFU12_SHIFT                                  (0x4U)
#define CSL_HYPERBUS_CORE_MTR_RFU12_RESETVAL                               (0x0U)

#define CSL_HYPERBUS_CORE_MTR_WCSH_MASK                                    (0xf00U)
#define CSL_HYPERBUS_CORE_MTR_WCSH_SHIFT                                   (0x8U)
#define CSL_HYPERBUS_CORE_MTR_WCSH_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_MTR_RCSH_MASK                                    (0xf000U)
#define CSL_HYPERBUS_CORE_MTR_RCSH_SHIFT                                   (0xcU)
#define CSL_HYPERBUS_CORE_MTR_RCSH_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_MTR_WCSS_MASK                                    (0xf0000U)
#define CSL_HYPERBUS_CORE_MTR_WCSS_SHIFT                                   (0x10U)
#define CSL_HYPERBUS_CORE_MTR_WCSS_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_MTR_RCSS_MASK                                    (0xf00000U)
#define CSL_HYPERBUS_CORE_MTR_RCSS_SHIFT                                   (0x14U)
#define CSL_HYPERBUS_CORE_MTR_RCSS_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_MTR_WCSHI_MASK                                   (0xf000000U)
#define CSL_HYPERBUS_CORE_MTR_WCSHI_SHIFT                                  (0x18U)
#define CSL_HYPERBUS_CORE_MTR_WCSHI_RESETVAL                               (0x0U)

#define CSL_HYPERBUS_CORE_MTR_RCSHI_MASK                                   (0xf0000000U)
#define CSL_HYPERBUS_CORE_MTR_RCSHI_SHIFT                                  (0x1cU)
#define CSL_HYPERBUS_CORE_MTR_RCSHI_RESETVAL                               (0x0U)

#define CSL_HYPERBUS_CORE_MTR_RESETVAL                                     0x1
/* GPOR */

#define CSL_HYPERBUS_CORE_GPOR_GPO_MASK                                    (0x3U)
#define CSL_HYPERBUS_CORE_GPOR_GPO_SHIFT                                   (0x0U)
#define CSL_HYPERBUS_CORE_GPOR_GPO_RESETVAL                                (0x0U)

#define CSL_HYPERBUS_CORE_GPOR_RFU14_MASK                                  (0xfffffffcU)
#define CSL_HYPERBUS_CORE_GPOR_RFU14_SHIFT                                 (0x2U)
#define CSL_HYPERBUS_CORE_GPOR_RFU14_RESETVAL                              (0x0U)

#define CSL_HYPERBUS_CORE_GPOR_RESETVAL                                    0x0
/* WPR */

#define CSL_HYPERBUS_CORE_WPR_WP_MASK                                      (0x1U)
#define CSL_HYPERBUS_CORE_WPR_WP_SHIFT                                     (0x0U)
#define CSL_HYPERBUS_CORE_WPR_WP_RESETVAL                                  (0x0U)

#define CSL_HYPERBUS_CORE_WPR_RFU15_MASK                                   (0xfffffffeU)
#define CSL_HYPERBUS_CORE_WPR_RFU15_SHIFT                                  (0x1U)
#define CSL_HYPERBUS_CORE_WPR_RFU15_RESETVAL                               (0x0U)

#define CSL_HYPERBUS_CORE_WPR_RESETVAL                                     0x0
/* LBR */

#define CSL_HYPERBUS_CORE_LBR_LOOPBACK_MASK                                (0x1U)
#define CSL_HYPERBUS_CORE_LBR_LOOPBACK_SHIFT                               (0x0U)
#define CSL_HYPERBUS_CORE_LBR_LOOPBACK_RESETVAL                            (0x0U)

#define CSL_HYPERBUS_CORE_LBR_RFU16_MASK                                   (0xfffffffeU)
#define CSL_HYPERBUS_CORE_LBR_RFU16_SHIFT                                  (0x1U)
#define CSL_HYPERBUS_CORE_LBR_RFU16_RESETVAL                               (0x0U)

#define CSL_HYPERBUS_CORE_LBR_RESETVAL                                     0x0
/**************************************************************************
* Hardware Region  : ecc_aggr
**************************************************************************/

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
   volatile uint32_t                         REV;
   volatile uint8_t                          Rsvd0[4];
   volatile uint32_t                         VECTOR;
   volatile uint32_t                         STAT;
   volatile uint32_t                         WRAP_REV;
   volatile uint32_t                         CTRL;
   volatile uint32_t                         ERR_CTRL1;
   volatile uint32_t                         ERR_CTRL2;
   volatile uint32_t                         ERR_STAT1;
   volatile uint32_t                         ERR_STAT2;
   volatile uint32_t                         ERR_STAT3;
   volatile uint8_t                          Rsvd1[16];
   volatile uint32_t                         SEC_EOI_REG;
   volatile uint32_t                         SEC_STATUS_REG0;
   volatile uint8_t                          Rsvd2[60];
   volatile uint32_t                         SEC_ENABLE_SET_REG0;
   volatile uint8_t                          Rsvd3[60];
   volatile uint32_t                         SEC_ENABLE_CLR_REG0;
   volatile uint8_t                          Rsvd4[120];
   volatile uint32_t                         DED_EOI_REG;
   volatile uint32_t                         DED_STATUS_REG0;
   volatile uint8_t                          Rsvd5[60];
   volatile uint32_t                         DED_ENABLE_SET_REG0;
   volatile uint8_t                          Rsvd6[60];
   volatile uint32_t                         DED_ENABLE_CLR_REG0;
   volatile uint8_t                          Rsvd7[60];
   volatile uint32_t                         AGGR_ENABLE_SET;
   volatile uint32_t                         AGGR_ENABLE_CLR;
   volatile uint32_t                         AGGR_STATUS_SET;
   volatile uint32_t                         AGGR_STATUS_CLR;
} CSL_hyperbus_ecc_aggrRegs;

/************************************************************************
* Register Macros
**************************************************************************/

#define CSL_HYPERBUS_ECC_AGGR_REV                                     ( 0x0U )
#define CSL_HYPERBUS_ECC_AGGR_VECTOR                                  ( 0x0U + 0x8U )
#define CSL_HYPERBUS_ECC_AGGR_STAT                                    ( 0x0U + 0xcU )
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV                                ( 0x0U + 0x10U )
#define CSL_HYPERBUS_ECC_AGGR_CTRL                                    ( 0x0U + 0x14U )
#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL1                               ( 0x0U + 0x18U )
#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL2                               ( 0x0U + 0x1cU )
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1                               ( 0x0U + 0x20U )
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT2                               ( 0x0U + 0x24U )
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3                               ( 0x0U + 0x28U )
#define CSL_HYPERBUS_ECC_AGGR_SEC_EOI_REG                             ( 0x0U + 0x3cU )
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0                         ( 0x0U + 0x40U )
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0                     ( 0x0U + 0x80U )
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0                     ( 0x0U + 0xc0U )
#define CSL_HYPERBUS_ECC_AGGR_DED_EOI_REG                             ( 0x0U + 0x13cU )
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0                         ( 0x0U + 0x140U )
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0                     ( 0x0U + 0x180U )
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0                     ( 0x0U + 0x1c0U )
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_SET                         ( 0x0U + 0x200U )
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_CLR                         ( 0x0U + 0x204U )
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_SET                         ( 0x0U + 0x208U )
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_CLR                         ( 0x0U + 0x20cU )

/************************************************************************
* Field Definition Macros
**************************************************************************/

/* REV */

#define CSL_HYPERBUS_ECC_AGGR_REV_SCHEME_MASK                              (0xc0000000U)
#define CSL_HYPERBUS_ECC_AGGR_REV_SCHEME_SHIFT                             (0x1eU)
#define CSL_HYPERBUS_ECC_AGGR_REV_SCHEME_RESETVAL                          (0x1U)

#define CSL_HYPERBUS_ECC_AGGR_REV_BU_MASK                                  (0x30000000U)
#define CSL_HYPERBUS_ECC_AGGR_REV_BU_SHIFT                                 (0x1cU)
#define CSL_HYPERBUS_ECC_AGGR_REV_BU_RESETVAL                              (0x2U)

#define CSL_HYPERBUS_ECC_AGGR_REV_MODULE_ID_MASK                           (0xfff0000U)
#define CSL_HYPERBUS_ECC_AGGR_REV_MODULE_ID_SHIFT                          (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_REV_MODULE_ID_RESETVAL                       (0x6U)

#define CSL_HYPERBUS_ECC_AGGR_REV_REVRTL_MASK                              (0xf800U)
#define CSL_HYPERBUS_ECC_AGGR_REV_REVRTL_SHIFT                             (0xbU)
#define CSL_HYPERBUS_ECC_AGGR_REV_REVRTL_RESETVAL                          (0x3U)

#define CSL_HYPERBUS_ECC_AGGR_REV_REVMAJ_MASK                              (0x700U)
#define CSL_HYPERBUS_ECC_AGGR_REV_REVMAJ_SHIFT                             (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_REV_REVMAJ_RESETVAL                          (0x3U)

#define CSL_HYPERBUS_ECC_AGGR_REV_CUSTOM_MASK                              (0xc0U)
#define CSL_HYPERBUS_ECC_AGGR_REV_CUSTOM_SHIFT                             (0x6U)
#define CSL_HYPERBUS_ECC_AGGR_REV_CUSTOM_RESETVAL                          (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_REV_REVMIN_MASK                              (0x3fU)
#define CSL_HYPERBUS_ECC_AGGR_REV_REVMIN_SHIFT                             (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_REV_REVMIN_RESETVAL                          (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_REV_RESETVAL                                 0x60061b00
/* VECTOR */

#define CSL_HYPERBUS_ECC_AGGR_VECTOR_ECC_VECTOR_MASK                       (0x7ffU)
#define CSL_HYPERBUS_ECC_AGGR_VECTOR_ECC_VECTOR_SHIFT                      (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_VECTOR_ECC_VECTOR_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RD_SVBUS_MASK                         (0x8000U)
#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RD_SVBUS_SHIFT                        (0xfU)
#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RD_SVBUS_RESETVAL                     (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RD_SVBUS_ADDRESS_MASK                 (0xff0000U)
#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RD_SVBUS_ADDRESS_SHIFT                (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RD_SVBUS_ADDRESS_RESETVAL             (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RD_SVBUS_DONE_MASK                    (0x1000000U)
#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RD_SVBUS_DONE_SHIFT                   (0x18U)
#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RD_SVBUS_DONE_RESETVAL                (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_VECTOR_RESETVAL                              0x0
/* STAT */

#define CSL_HYPERBUS_ECC_AGGR_STAT_NUM_RAMS_MASK                           (0x7ffU)
#define CSL_HYPERBUS_ECC_AGGR_STAT_NUM_RAMS_SHIFT                          (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_STAT_NUM_RAMS_RESETVAL                       (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_STAT_RESETVAL                                0x0
/* WRAP_REV */

#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_SCHEME_MASK                         (0xc0000000U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_SCHEME_SHIFT                        (0x1eU)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_SCHEME_RESETVAL                     (0x1U)

#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_BU_MASK                             (0x30000000U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_BU_SHIFT                            (0x1cU)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_BU_RESETVAL                         (0x2U)

#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_MODULE_ID_MASK                      (0xfff0000U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_MODULE_ID_SHIFT                     (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_MODULE_ID_RESETVAL                  (0x6U)

#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_REVRTL_MASK                         (0xf800U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_REVRTL_SHIFT                        (0xbU)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_REVRTL_RESETVAL                     (0x3U)

#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_REVMAJ_MASK                         (0x700U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_REVMAJ_SHIFT                        (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_REVMAJ_RESETVAL                     (0x1U)

#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_CUSTOM_MASK                         (0xc0U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_CUSTOM_SHIFT                        (0x6U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_CUSTOM_RESETVAL                     (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_REVMIN_MASK                         (0x3fU)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_REVMIN_SHIFT                        (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_REVMIN_RESETVAL                     (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_WRAP_REV_RESETVAL                            0x60061900
/* CTRL */

#define CSL_HYPERBUS_ECC_AGGR_CTRL_ECC_ENABLE_MASK                         (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_ECC_ENABLE_SHIFT                        (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_ECC_ENABLE_RESETVAL                     (0x1U)

#define CSL_HYPERBUS_ECC_AGGR_CTRL_ECC_CHECK_MASK                          (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_ECC_CHECK_SHIFT                         (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_ECC_CHECK_RESETVAL                      (0x1U)

#define CSL_HYPERBUS_ECC_AGGR_CTRL_ENABLE_RMW_MASK                         (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_ENABLE_RMW_SHIFT                        (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_ENABLE_RMW_RESETVAL                     (0x1U)

#define CSL_HYPERBUS_ECC_AGGR_CTRL_FORCE_SEC_MASK                          (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_FORCE_SEC_SHIFT                         (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_FORCE_SEC_RESETVAL                      (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_CTRL_FORCE_DED_MASK                          (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_FORCE_DED_SHIFT                         (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_FORCE_DED_RESETVAL                      (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_CTRL_FORCE_N_ROW_MASK                        (0x20U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_FORCE_N_ROW_SHIFT                       (0x5U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_FORCE_N_ROW_RESETVAL                    (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_CTRL_ERROR_ONCE_MASK                         (0x40U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_ERROR_ONCE_SHIFT                        (0x6U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_ERROR_ONCE_RESETVAL                     (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_CTRL_CHECK_PARITY_MASK                       (0x80U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_CHECK_PARITY_SHIFT                      (0x7U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_CHECK_PARITY_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_CTRL_CHECK_SVBUS_TIMEOUT_MASK                (0x100U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_CHECK_SVBUS_TIMEOUT_SHIFT               (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_CTRL_CHECK_SVBUS_TIMEOUT_RESETVAL            (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_CTRL_RESETVAL                                0x7
/* ERR_CTRL1 */

#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL1_ECC_ROW_MASK                       (0xffffffffU)
#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL1_ECC_ROW_SHIFT                      (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL1_ECC_ROW_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL1_RESETVAL                           0x0
/* ERR_CTRL2 */

#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL2_ECC_BIT1_MASK                      (0xffffU)
#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL2_ECC_BIT1_SHIFT                     (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL2_ECC_BIT1_RESETVAL                  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL2_ECC_BIT2_MASK                      (0xffff0000U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL2_ECC_BIT2_SHIFT                     (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL2_ECC_BIT2_RESETVAL                  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_CTRL2_RESETVAL                           0x0
/* ERR_STAT1 */

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_SEC_MASK                       (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_SEC_SHIFT                      (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_SEC_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_DED_MASK                       (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_DED_SHIFT                      (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_DED_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_OTHER_MASK                     (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_OTHER_SHIFT                    (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_OTHER_RESETVAL                 (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_PARITY_ERR_MASK                    (0x60U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_PARITY_ERR_SHIFT                   (0x5U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_PARITY_ERR_RESETVAL                (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CTR_REG_ERR_MASK                   (0x80U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CTR_REG_ERR_SHIFT                  (0x7U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CTR_REG_ERR_RESETVAL               (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_ECC_SEC_MASK                   (0x300U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_ECC_SEC_SHIFT                  (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_ECC_SEC_RESETVAL               (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_ECC_DED_MASK                   (0xc00U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_ECC_DED_SHIFT                  (0xaU)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_ECC_DED_RESETVAL               (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_ECC_OTHER_MASK                 (0x1000U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_ECC_OTHER_SHIFT                (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_ECC_OTHER_RESETVAL             (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_PARITY_ERR_MASK                (0x6000U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_PARITY_ERR_SHIFT               (0xdU)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_PARITY_ERR_RESETVAL            (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_CTRL_REG_ERR_MASK              (0x8000U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_CTRL_REG_ERR_SHIFT             (0xfU)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_CLR_CTRL_REG_ERR_RESETVAL          (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_BIT1_MASK                      (0xffff0000U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_BIT1_SHIFT                     (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_ECC_BIT1_RESETVAL                  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT1_RESETVAL                           0x0
/* ERR_STAT2 */

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT2_ECC_ROW_MASK                       (0xffffffffU)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT2_ECC_ROW_SHIFT                      (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT2_ECC_ROW_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT2_RESETVAL                           0x0
/* ERR_STAT3 */

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_WB_PEND_MASK                       (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_WB_PEND_SHIFT                      (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_WB_PEND_RESETVAL                   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_SVBUS_TIMEOUT_ERR_MASK             (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_SVBUS_TIMEOUT_ERR_SHIFT            (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_SVBUS_TIMEOUT_ERR_RESETVAL         (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_CLR_SVBUS_TIMEOUT_ERR_MASK         (0x200U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_CLR_SVBUS_TIMEOUT_ERR_SHIFT        (0x9U)
#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_CLR_SVBUS_TIMEOUT_ERR_RESETVAL     (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_ERR_STAT3_RESETVAL                           0x0
/* SEC_EOI_REG */

#define CSL_HYPERBUS_ECC_AGGR_SEC_EOI_REG_EOI_WR_MASK                      (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_EOI_REG_EOI_WR_SHIFT                     (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_EOI_REG_EOI_WR_RESETVAL                  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_EOI_REG_RESETVAL                         0x0
/* SEC_STATUS_REG0 */

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_ADR_FIFO_PEND_MASK       (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_ADR_FIFO_PEND_SHIFT      (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_ADR_FIFO_PEND_RESETVAL   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WDAT0_FIFO_PEND_MASK     (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WDAT0_FIFO_PEND_SHIFT    (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WDAT0_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WDAT1_FIFO_PEND_MASK     (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WDAT1_FIFO_PEND_SHIFT    (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WDAT1_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_BDAT0_FIFO_PEND_MASK     (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_BDAT0_FIFO_PEND_SHIFT    (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_BDAT0_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_BDAT1_FIFO_PEND_MASK     (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_BDAT1_FIFO_PEND_SHIFT    (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_BDAT1_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_RDAT_FIFO_PEND_MASK      (0x20U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_RDAT_FIFO_PEND_SHIFT     (0x5U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_RDAT_FIFO_PEND_RESETVAL  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_RX_FIFO_PEND_MASK        (0x40U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_RX_FIFO_PEND_SHIFT       (0x6U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_RX_FIFO_PEND_RESETVAL    (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AW0_FIFO_PEND_MASK       (0x80U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AW0_FIFO_PEND_SHIFT      (0x7U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AW0_FIFO_PEND_RESETVAL   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WID0_FIFO_PEND_MASK      (0x100U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WID0_FIFO_PEND_SHIFT     (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WID0_FIFO_PEND_RESETVAL  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AWID0_FIFO_PEND_MASK     (0x200U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AWID0_FIFO_PEND_SHIFT    (0x9U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AWID0_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AW1_FIFO_PEND_MASK       (0x400U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AW1_FIFO_PEND_SHIFT      (0xaU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AW1_FIFO_PEND_RESETVAL   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WID1_FIFO_PEND_MASK      (0x800U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WID1_FIFO_PEND_SHIFT     (0xbU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_WID1_FIFO_PEND_RESETVAL  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AWID1_FIFO_PEND_MASK     (0x1000U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AWID1_FIFO_PEND_SHIFT    (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AWID1_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AR_FIFO_PEND_MASK        (0x2000U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AR_FIFO_PEND_SHIFT       (0xdU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_AR_FIFO_PEND_RESETVAL    (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_ARID_FIFO_PEND_MASK      (0x4000U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_ARID_FIFO_PEND_SHIFT     (0xeU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_MEM_ARID_FIFO_PEND_RESETVAL  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_STATUS_REG0_RESETVAL                     0x0
/* SEC_ENABLE_SET_REG0 */

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_ADR_FIFO_ENABLE_SET_MASK (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_ADR_FIFO_ENABLE_SET_SHIFT (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_ADR_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WDAT0_FIFO_ENABLE_SET_MASK (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WDAT0_FIFO_ENABLE_SET_SHIFT (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WDAT0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WDAT1_FIFO_ENABLE_SET_MASK (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WDAT1_FIFO_ENABLE_SET_SHIFT (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WDAT1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_BDAT0_FIFO_ENABLE_SET_MASK (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_BDAT0_FIFO_ENABLE_SET_SHIFT (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_BDAT0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_BDAT1_FIFO_ENABLE_SET_MASK (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_BDAT1_FIFO_ENABLE_SET_SHIFT (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_BDAT1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_RDAT_FIFO_ENABLE_SET_MASK (0x20U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_RDAT_FIFO_ENABLE_SET_SHIFT (0x5U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_RDAT_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_RX_FIFO_ENABLE_SET_MASK (0x40U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_RX_FIFO_ENABLE_SET_SHIFT (0x6U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_RX_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AW0_FIFO_ENABLE_SET_MASK (0x80U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AW0_FIFO_ENABLE_SET_SHIFT (0x7U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AW0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WID0_FIFO_ENABLE_SET_MASK (0x100U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WID0_FIFO_ENABLE_SET_SHIFT (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WID0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AWID0_FIFO_ENABLE_SET_MASK (0x200U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AWID0_FIFO_ENABLE_SET_SHIFT (0x9U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AWID0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AW1_FIFO_ENABLE_SET_MASK (0x400U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AW1_FIFO_ENABLE_SET_SHIFT (0xaU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AW1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WID1_FIFO_ENABLE_SET_MASK (0x800U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WID1_FIFO_ENABLE_SET_SHIFT (0xbU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_WID1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AWID1_FIFO_ENABLE_SET_MASK (0x1000U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AWID1_FIFO_ENABLE_SET_SHIFT (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AWID1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AR_FIFO_ENABLE_SET_MASK (0x2000U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AR_FIFO_ENABLE_SET_SHIFT (0xdU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_AR_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_ARID_FIFO_ENABLE_SET_MASK (0x4000U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_ARID_FIFO_ENABLE_SET_SHIFT (0xeU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_MEM_ARID_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_SET_REG0_RESETVAL                 0x0
/* SEC_ENABLE_CLR_REG0 */

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_ADR_FIFO_ENABLE_CLR_MASK (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_ADR_FIFO_ENABLE_CLR_SHIFT (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_ADR_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WDAT0_FIFO_ENABLE_CLR_MASK (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WDAT0_FIFO_ENABLE_CLR_SHIFT (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WDAT0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WDAT1_FIFO_ENABLE_CLR_MASK (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WDAT1_FIFO_ENABLE_CLR_SHIFT (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WDAT1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_BDAT0_FIFO_ENABLE_CLR_MASK (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_BDAT0_FIFO_ENABLE_CLR_SHIFT (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_BDAT0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_BDAT1_FIFO_ENABLE_CLR_MASK (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_BDAT1_FIFO_ENABLE_CLR_SHIFT (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_BDAT1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_RDAT_FIFO_ENABLE_CLR_MASK (0x20U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_RDAT_FIFO_ENABLE_CLR_SHIFT (0x5U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_RDAT_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_RX_FIFO_ENABLE_CLR_MASK (0x40U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_RX_FIFO_ENABLE_CLR_SHIFT (0x6U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_RX_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AW0_FIFO_ENABLE_CLR_MASK (0x80U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AW0_FIFO_ENABLE_CLR_SHIFT (0x7U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AW0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WID0_FIFO_ENABLE_CLR_MASK (0x100U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WID0_FIFO_ENABLE_CLR_SHIFT (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WID0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AWID0_FIFO_ENABLE_CLR_MASK (0x200U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AWID0_FIFO_ENABLE_CLR_SHIFT (0x9U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AWID0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AW1_FIFO_ENABLE_CLR_MASK (0x400U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AW1_FIFO_ENABLE_CLR_SHIFT (0xaU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AW1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WID1_FIFO_ENABLE_CLR_MASK (0x800U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WID1_FIFO_ENABLE_CLR_SHIFT (0xbU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_WID1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AWID1_FIFO_ENABLE_CLR_MASK (0x1000U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AWID1_FIFO_ENABLE_CLR_SHIFT (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AWID1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AR_FIFO_ENABLE_CLR_MASK (0x2000U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AR_FIFO_ENABLE_CLR_SHIFT (0xdU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_AR_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_ARID_FIFO_ENABLE_CLR_MASK (0x4000U)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_ARID_FIFO_ENABLE_CLR_SHIFT (0xeU)
#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_MEM_ARID_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_SEC_ENABLE_CLR_REG0_RESETVAL                 0x0
/* DED_EOI_REG */

#define CSL_HYPERBUS_ECC_AGGR_DED_EOI_REG_EOI_WR_MASK                      (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_DED_EOI_REG_EOI_WR_SHIFT                     (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_DED_EOI_REG_EOI_WR_RESETVAL                  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_EOI_REG_RESETVAL                         0x0
/* DED_STATUS_REG0 */

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_ADR_FIFO_PEND_MASK       (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_ADR_FIFO_PEND_SHIFT      (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_ADR_FIFO_PEND_RESETVAL   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WDAT0_FIFO_PEND_MASK     (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WDAT0_FIFO_PEND_SHIFT    (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WDAT0_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WDAT1_FIFO_PEND_MASK     (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WDAT1_FIFO_PEND_SHIFT    (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WDAT1_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_BDAT0_FIFO_PEND_MASK     (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_BDAT0_FIFO_PEND_SHIFT    (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_BDAT0_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_BDAT1_FIFO_PEND_MASK     (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_BDAT1_FIFO_PEND_SHIFT    (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_BDAT1_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_RDAT_FIFO_PEND_MASK      (0x20U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_RDAT_FIFO_PEND_SHIFT     (0x5U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_RDAT_FIFO_PEND_RESETVAL  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_RX_FIFO_PEND_MASK        (0x40U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_RX_FIFO_PEND_SHIFT       (0x6U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_RX_FIFO_PEND_RESETVAL    (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AW0_FIFO_PEND_MASK       (0x80U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AW0_FIFO_PEND_SHIFT      (0x7U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AW0_FIFO_PEND_RESETVAL   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WID0_FIFO_PEND_MASK      (0x100U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WID0_FIFO_PEND_SHIFT     (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WID0_FIFO_PEND_RESETVAL  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AWID0_FIFO_PEND_MASK     (0x200U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AWID0_FIFO_PEND_SHIFT    (0x9U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AWID0_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AW1_FIFO_PEND_MASK       (0x400U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AW1_FIFO_PEND_SHIFT      (0xaU)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AW1_FIFO_PEND_RESETVAL   (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WID1_FIFO_PEND_MASK      (0x800U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WID1_FIFO_PEND_SHIFT     (0xbU)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_WID1_FIFO_PEND_RESETVAL  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AWID1_FIFO_PEND_MASK     (0x1000U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AWID1_FIFO_PEND_SHIFT    (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AWID1_FIFO_PEND_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AR_FIFO_PEND_MASK        (0x2000U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AR_FIFO_PEND_SHIFT       (0xdU)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_AR_FIFO_PEND_RESETVAL    (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_ARID_FIFO_PEND_MASK      (0x4000U)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_ARID_FIFO_PEND_SHIFT     (0xeU)
#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_MEM_ARID_FIFO_PEND_RESETVAL  (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_STATUS_REG0_RESETVAL                     0x0
/* DED_ENABLE_SET_REG0 */

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_ADR_FIFO_ENABLE_SET_MASK (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_ADR_FIFO_ENABLE_SET_SHIFT (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_ADR_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WDAT0_FIFO_ENABLE_SET_MASK (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WDAT0_FIFO_ENABLE_SET_SHIFT (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WDAT0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WDAT1_FIFO_ENABLE_SET_MASK (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WDAT1_FIFO_ENABLE_SET_SHIFT (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WDAT1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_BDAT0_FIFO_ENABLE_SET_MASK (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_BDAT0_FIFO_ENABLE_SET_SHIFT (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_BDAT0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_BDAT1_FIFO_ENABLE_SET_MASK (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_BDAT1_FIFO_ENABLE_SET_SHIFT (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_BDAT1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_RDAT_FIFO_ENABLE_SET_MASK (0x20U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_RDAT_FIFO_ENABLE_SET_SHIFT (0x5U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_RDAT_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_RX_FIFO_ENABLE_SET_MASK (0x40U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_RX_FIFO_ENABLE_SET_SHIFT (0x6U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_RX_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AW0_FIFO_ENABLE_SET_MASK (0x80U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AW0_FIFO_ENABLE_SET_SHIFT (0x7U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AW0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WID0_FIFO_ENABLE_SET_MASK (0x100U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WID0_FIFO_ENABLE_SET_SHIFT (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WID0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AWID0_FIFO_ENABLE_SET_MASK (0x200U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AWID0_FIFO_ENABLE_SET_SHIFT (0x9U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AWID0_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AW1_FIFO_ENABLE_SET_MASK (0x400U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AW1_FIFO_ENABLE_SET_SHIFT (0xaU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AW1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WID1_FIFO_ENABLE_SET_MASK (0x800U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WID1_FIFO_ENABLE_SET_SHIFT (0xbU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_WID1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AWID1_FIFO_ENABLE_SET_MASK (0x1000U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AWID1_FIFO_ENABLE_SET_SHIFT (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AWID1_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AR_FIFO_ENABLE_SET_MASK (0x2000U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AR_FIFO_ENABLE_SET_SHIFT (0xdU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_AR_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_ARID_FIFO_ENABLE_SET_MASK (0x4000U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_ARID_FIFO_ENABLE_SET_SHIFT (0xeU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_MEM_ARID_FIFO_ENABLE_SET_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_SET_REG0_RESETVAL                 0x0
/* DED_ENABLE_CLR_REG0 */

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_ADR_FIFO_ENABLE_CLR_MASK (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_ADR_FIFO_ENABLE_CLR_SHIFT (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_ADR_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WDAT0_FIFO_ENABLE_CLR_MASK (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WDAT0_FIFO_ENABLE_CLR_SHIFT (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WDAT0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WDAT1_FIFO_ENABLE_CLR_MASK (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WDAT1_FIFO_ENABLE_CLR_SHIFT (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WDAT1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_BDAT0_FIFO_ENABLE_CLR_MASK (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_BDAT0_FIFO_ENABLE_CLR_SHIFT (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_BDAT0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_BDAT1_FIFO_ENABLE_CLR_MASK (0x10U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_BDAT1_FIFO_ENABLE_CLR_SHIFT (0x4U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_BDAT1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_RDAT_FIFO_ENABLE_CLR_MASK (0x20U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_RDAT_FIFO_ENABLE_CLR_SHIFT (0x5U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_RDAT_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_RX_FIFO_ENABLE_CLR_MASK (0x40U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_RX_FIFO_ENABLE_CLR_SHIFT (0x6U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_RX_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AW0_FIFO_ENABLE_CLR_MASK (0x80U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AW0_FIFO_ENABLE_CLR_SHIFT (0x7U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AW0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WID0_FIFO_ENABLE_CLR_MASK (0x100U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WID0_FIFO_ENABLE_CLR_SHIFT (0x8U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WID0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AWID0_FIFO_ENABLE_CLR_MASK (0x200U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AWID0_FIFO_ENABLE_CLR_SHIFT (0x9U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AWID0_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AW1_FIFO_ENABLE_CLR_MASK (0x400U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AW1_FIFO_ENABLE_CLR_SHIFT (0xaU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AW1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WID1_FIFO_ENABLE_CLR_MASK (0x800U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WID1_FIFO_ENABLE_CLR_SHIFT (0xbU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_WID1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AWID1_FIFO_ENABLE_CLR_MASK (0x1000U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AWID1_FIFO_ENABLE_CLR_SHIFT (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AWID1_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AR_FIFO_ENABLE_CLR_MASK (0x2000U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AR_FIFO_ENABLE_CLR_SHIFT (0xdU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_AR_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_ARID_FIFO_ENABLE_CLR_MASK (0x4000U)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_ARID_FIFO_ENABLE_CLR_SHIFT (0xeU)
#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_MEM_ARID_FIFO_ENABLE_CLR_RESETVAL (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_DED_ENABLE_CLR_REG0_RESETVAL                 0x0
/* AGGR_ENABLE_SET */

#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_SET_PARITY_MASK                  (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_SET_PARITY_SHIFT                 (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_SET_PARITY_RESETVAL              (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_SET_TIMEOUT_MASK                 (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_SET_TIMEOUT_SHIFT                (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_SET_TIMEOUT_RESETVAL             (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_SET_RESETVAL                     0x0
/* AGGR_ENABLE_CLR */

#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_CLR_PARITY_MASK                  (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_CLR_PARITY_SHIFT                 (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_CLR_PARITY_RESETVAL              (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_CLR_TIMEOUT_MASK                 (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_CLR_TIMEOUT_SHIFT                (0x1U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_CLR_TIMEOUT_RESETVAL             (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_AGGR_ENABLE_CLR_RESETVAL                     0x0
/* AGGR_STATUS_SET */

#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_SET_PARITY_MASK                  (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_SET_PARITY_SHIFT                 (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_SET_PARITY_RESETVAL              (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_SET_TIMEOUT_MASK                 (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_SET_TIMEOUT_SHIFT                (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_SET_TIMEOUT_RESETVAL             (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_SET_RESETVAL                     0x0
/* AGGR_STATUS_CLR */

#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_CLR_PARITY_MASK                  (0x3U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_CLR_PARITY_SHIFT                 (0x0U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_CLR_PARITY_RESETVAL              (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_CLR_TIMEOUT_MASK                 (0xcU)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_CLR_TIMEOUT_SHIFT                (0x2U)
#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_CLR_TIMEOUT_RESETVAL             (0x0U)

#define CSL_HYPERBUS_ECC_AGGR_AGGR_STATUS_CLR_RESETVAL                     0x0

#ifdef __cplusplus
}
#endif
#endif /*CSLR_HYPERBUS_H_ */

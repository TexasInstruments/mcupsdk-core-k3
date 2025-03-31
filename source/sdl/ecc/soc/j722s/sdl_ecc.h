/*
 *  Copyright (C) 2024-25 Texas Instruments Incorporated
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
 */

/**
 * \file  sdl_ecc.h
 *
 * \brief
 *  Header file contains enumerations, structure definitions and function
 *  declarations for SDL ECC interface.
 *  ============================================================================
 */

#ifndef INCLUDE_SDL_SOC_ECC_H_
#define INCLUDE_SDL_SOC_ECC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>

#include <sdl/ecc/sdl_ip_ecc.h>
#include <sdl/sdl_ecc.h>
#include <sdl/esm/sdl_esm.h>
#include <sdl/include/j722s/soc_config.h>
#include <sdl/include/j722s/sdlr_soc_baseaddress.h>
#include <sdl/include/j722s/sdlr_soc_ecc_aggr.h>
#include <sdl/esm/soc/sdl_esm_soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @addtogroup SDL_ECC_AGGR_ENUM
 *  @{
 *
 */

/* ========================================================================== */
/*                           Macros and Typedefs                              */
/* ========================================================================== */

#define SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR                                                                         (0U)
#define SDL_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR                                                                              (1U)
#define SDL_DSS_DSI0_K3_DSS_DSI_DSI_TOP_ECC_AGGR_SYS                                                                    (2U)
#define SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR                                                                             (3U)
#define SDL_PSRAMECC1_PSRAM256X32E_ECC_AGGR                                                                             (4U)
#define SDL_WKUP_ECC_AGGR2                                                                                              (5U)
#define SDL_DMPAC0_SAM67_DMPAC_WRAP_DMPAC_TOP_DOF_INFRA_DMPAC_BASE_KSDW_ECC_AGGR                                        (6U)
#define SDL_ECC_AGGR0_SAM67_SEC_HSM_ECC_AGGR                                                                            (7U)
#define SDL_MCU_MSRAM_256K1_MSRAM32KX64E_ECC_AGGR                                                                       (8U)
#define SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR                                                                              (9U)
#define SDL_WKUP_ECC_AGGR1                                                                                              (10U)
#define SDL_FSS0_FSS_UL_OSPI0_OSPI_WRAP_ECC_AGGR                                                                        (11U)
#define SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR                                                                         (12U)
#define SDL_GICSS0_GIC500SS_1_4_ECC_AGGR                                                                                (13U)
#define SDL_CPSW0_CPSW_3GUSS_AM67_CORE_ECC_CPSW_ECC_AGGR                                                                (14U)
#define SDL_CSI_RX_IF3_CSI_RX_IF_ECC_AGGR                                                                               (15U)
#define SDL_CSI_RX_IF1_CSI_RX_IF_ECC_AGGR                                                                               (16U)
#define SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR                                                                               (17U)
#define SDL_PSCSS0_SAM67_MAIN_PSC_WRAP_ECC_AGGR                                                                         (18U)
#define SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_RXMEM                                                                             (19U)
#define SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_TXMEM                                                                             (20U)
#define SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR                                                                            (21U)
#define SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR                                                                          (22U)
#define SDL_MSRAM8KX256E0_MSRAM8KX256E_ECC_AGGR                                                                         (23U)
#define SDL_CSI_TX_IF0_CSI_TX_IF_V2_ECC_AGGR                                                                            (24U)
#define SDL_CSI_TX_IF0_CSI_TX_IF_V2_ECC_AGGR_BYTE                                                                       (25U)
#define SDL_WKUP_ECC_AGGR0                                                                                              (26U)
#define SDL_DMASS0_ECC_AGGR_0                                                                                           (27U)
#define SDL_PDMA0_SAM67_PDMA_SPI_ECCAGGR                                                                                (28U)
#define SDL_MCU_ECC_AGGR1_SAM62A_MCU_PULSAR_UL_ECC_AGGR                                                                 (29U)
#define SDL_USB0_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR                                                                      (30U)
#define SDL_MCU_MSRAM_256K0_MSRAM32KX64E_ECC_AGGR                                                                       (31U)
#define SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_RXMEM                                                                             (32U)
#define SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_TXMEM                                                                             (33U)
#define SDL_USB1_USB3P0SS64_16FFC_USB3P0SS64_CORE_A_ECC_AGGR                                                            (34U)
#define SDL_VPAC0_SAM67_VPAC_WRAP_IVPAC_TOP_0_PAC_BASE_KSDW_ECC_AGGR                                                    (35U)
#define SDL_VPAC0_SAM67_VPAC_WRAP_IVPAC_TOP_0_VPAC_LDC0_KSDW_ECC_AGGR                                                   (36U)
#define SDL_VPAC0_SAM67_VPAC_WRAP_IVPAC_TOP_0_VPAC_VISS0_KSDW_ECC_AGGR                                                  (37U)
#define SDL_WKUP_PSRAMECC_8K0_PSRAM8KX32E_ECC_AGGR                                                                      (38U)
#define SDL_C7X256V0_SAM67_C7XV_WRAP_ECC_AGGR                                                                           (39U)
#define SDL_PDMA1_SAM62_PDMA_UART_ECCAGGR                                                                               (40U)
#define SDL_C7X256V1_SAM67_C7XV_WRAP_ECC_AGGR                                                                           (41U)
#define SDL_MCU_ECC_AGGR0                                                                                               (42U)
#define SDL_CSI_RX_IF2_CSI_RX_IF_ECC_AGGR                                                                               (43U)
#define SDL_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR                                                                           (44U)
#define SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR                                                                           (45U)
#define SDL_MMCSD0_EMMC8SS_16FFC_ECC_AGGR_TXMEM                                                                         (46U)
#define SDL_MMCSD0_EMMC8SS_16FFC_ECC_AGGR_RXMEM                                                                         (47U)
#define SDL_DMASS1_DMSS_CSI_AM67_ECCAGGR                                                                                (48U)
#define SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE0      (49U)
#define SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE1      (50U)
#define SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE2      (51U)
#define SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE3      (52U)
#define SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_COREPAC    (53U)
#define SDL_MCU_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR                                                                       (54U)
#define SDL_MCU_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR                                                                       (55U)
#define SDL_PCIE0_PCIE_G2X1_64_CORE_AXI_ECC_AGGR                                                                        (56U)
#define SDL_PCIE0_PCIE_G2X1_64_CORE_CORE_ECC_AGGR                                                                       (57U)
#define SDL_ECC_MEMTYPE_MAX                                                                                             (SDL_PCIE0_PCIE_G2X1_64_CORE_CORE_ECC_AGGR + 1U)

/** \brief Select memory subtype ATCM0 BANK0 */
#define SDL_ECC_R5F_MEM_SUBTYPE_ATCM0_BANK0_VECTOR_ID                                                                   (SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_ATCM0_BANK0_RAM_ID)
/** \brief Select memory subtype ATCM0 BANK1 */
#define SDL_ECC_R5F_MEM_SUBTYPE_ATCM0_BANK1_VECTOR_ID                                                                   (SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_ATCM0_BANK1_RAM_ID)
/** \brief Select memory subtype B0TCM0 BANK0 */
#define SDL_ECC_R5F_MEM_SUBTYPE_B0TCM0_BANK0_VECTOR_ID                                                                  (SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B0TCM0_BANK0_RAM_ID)
/** \brief Select memory subtype B0TCM0 BANK1 */
#define SDL_ECC_R5F_MEM_SUBTYPE_B0TCM0_BANK1_VECTOR_ID                                                                  (SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B0TCM0_BANK1_RAM_ID)
/** \brief Select memory subtype B1TCM0 BANK0 */
#define SDL_ECC_R5F_MEM_SUBTYPE_B1TCM0_BANK0_VECTOR_ID                                                                  (SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B1TCM0_BANK0_RAM_ID)
/** \brief Select memory subtype B1TCM0 BANK1 */
#define SDL_ECC_R5F_MEM_SUBTYPE_B1TCM0_BANK1_VECTOR_ID                                                                  (SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_PULSAR_ULS_B1TCM0_BANK1_RAM_ID)
/** \brief Select memory subtype VIM RAM */
#define SDL_ECC_R5F_MEM_SUBTYPE_KS_VIM_RAM_VECTOR_ID                                                                    (SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR_CPU0_KS_VIM_RAMECC_RAM_ID)

/** @} */

#define SDL_ECC_MEM_TYPE                                                                                                SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR

/** /brief Format of VIM DED vector function */
typedef void (*SDL_ECC_VIMDEDVector_t) (void);

/** ---------------------------------------------------------------------------
 * \brief This enumerator indicates ECC memory type
 *
 * ----------------------------------------------------------------------------
 */
typedef uint32_t SDL_ECC_MemType;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** ---------------------------------------------------------------------------
 * \brief This structure defines the elements of ECC Group checker for Interconnect
 * SDL_ECC_RamIdType
 * ----------------------------------------------------------------------------
 */
typedef struct SDL_GrpChkConfig_s
{
    uint32_t checkerType;
    uint32_t dataWidth;
    /**< Length of memory bus covered in bits */
}  SDL_GrpChkConfig_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** ============================================================================
 *
 * \brief   Register Handler for VIM DED ECC error
 *
 * \param  VIMDEDHandler: This is function to be called when an Double bit ECC
 *                        error happens on the VIM RAM. NOTE: That the regular
 *                        vector load will be replaced with this registered
 *                        function.
 *
 */
void SDL_ECC_registerVIMDEDHandler(SDL_ECC_VIMDEDVector_t VIMDEDHandler);

#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* INCLUDE_SDL_SOC_ECC_H_*/
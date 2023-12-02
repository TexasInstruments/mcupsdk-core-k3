/********************************************************************
*
* ESM0 INTERRUPT MAP. header file
*
* Copyright (C) 2023 Texas Instruments Incorporated.
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
*/
#ifndef SDLR_ESM0_INTERRUPT_MAP_H_
#define SDLR_ESM0_INTERRUPT_MAP_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*
* List of intr sources for receiver: ESM0
*/

#define SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_COMMON_0_CSI_ERR_IRQ_0                                  (0U)
#define SDLR_ESM0_ESM_LVL_EVENT_ECC_AGGR0_SAM62_SEC_ECC_AGGR_UNCORR_LEVEL_0                        (1U)
#define SDLR_ESM0_ESM_LVL_EVENT_ECC_AGGR0_SAM62_SEC_ECC_AGGR_CORR_LEVEL_0                          (2U)
#define SDLR_ESM0_ESM_LVL_EVENT_CPSW0_ECC_SEC_PEND_0                                               (3U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RAT_0_EXP_INTR_0                                              (4U)
#define SDLR_ESM0_ESM_LVL_EVENT_DDR16SS0_DDRSS_DRAM_ECC_CORR_ERR_LVL_0                             (6U)
#define SDLR_ESM0_ESM_LVL_EVENT_PLLFRACF_SSMOD17_LOCKLOSS_IPCFG_0                                  (7U)
#define SDLR_ESM0_ESM_LVL_EVENT_PLLFRACF_SSMOD16_LOCKLOSS_IPCFG_0                                  (8U)
#define SDLR_ESM0_ESM_LVL_EVENT_DMASS0_ECC_AGGR_0_ECC_CORRECTED_ERR_LEVEL_0                        (9U)
#define SDLR_ESM0_ESM_LVL_EVENT_DMASS0_ECC_AGGR_0_ECC_UNCORRECTED_ERR_LEVEL_0                      (10U)
#define SDLR_ESM0_ESM_LVL_EVENT_FSS0_OSPI_0_OSPI_ECC_CORR_LVL_INTR_0                               (11U)
#define SDLR_ESM0_ESM_LVL_EVENT_GICSS0_GIC500SS_1_4_ECC_AGGR_ECC_AGGR_CORR_LEVEL_0                 (12U)
#define SDLR_ESM0_ESM_LVL_EVENT_ICSSM0_ICSS_M_CORE_BORG_ECC_AGGR_PR1_ECC_SEC_ERR_PEND_0            (13U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RAT_1_EXP_INTR_0                                              (14U)
#define SDLR_ESM0_ESM_LVL_EVENT_PDMA0_SAM62_PDMA_SPI_ECCAGGR_ECC_SEC_PEND_0                        (15U)
#define SDLR_ESM0_ESM_LVL_EVENT_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR_MCANSS_ECC_CORR_LVL_INT_0        (16U)
#define SDLR_ESM0_ESM_LVL_EVENT_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR_ECC_CORR_LEVEL_0               (18U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_ECC_AGGR0_SAM62_DM_ECC_AGGR_CORR_LEVEL_0                      (20U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_ECC_AGGR0_SAM62_DM_ECC_AGGR_UNCORR_LEVEL_0                    (21U)
#define SDLR_ESM0_ESM_LVL_EVENT_PSC0_ECC_AGGR_0_FW_CH_BR_ECC_AGGR_CORR_LEVEL_0                     (22U)
#define SDLR_ESM0_ESM_LVL_EVENT_PSC0_ECC_AGGR_0_FW_CH_BR_ECC_AGGR_UNCORR_LEVEL_0                   (23U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR0_CORRECTED_ERR_LEVEL_0                          (24U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR1_CORRECTED_ERR_LEVEL_0                          (25U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR_COREPAC_CORRECTED_ERR_LEVEL_0                   (26U)
#define SDLR_ESM0_ESM_LVL_EVENT_PDMA1_SAM62_PDMA_UART_ECCAGGR_ECC_SEC_PEND_0                       (28U)
#define SDLR_ESM0_ESM_LVL_EVENT_PSRAMECC0_PSRAM256X32E_ECC_AGGR_ECC_CORR_LEVEL_0                   (29U)
#define SDLR_ESM0_ESM_LVL_EVENT_R5FSS0_CORE0_ECC_CORRECTED_LEVEL_0                                 (30U)
#define SDLR_ESM0_ESM_LVL_EVENT_USB0_COMMON_0_HOST_SYSTEM_ERROR_0                                  (32U)
#define SDLR_ESM0_ESM_LVL_EVENT_USB1_COMMON_0_HOST_SYSTEM_ERROR_0                                  (33U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD2_EMMCSD4SS_ECC_AGGR_RXMEM_EMMCSDSS_RXMEM_CORR_ERR_LVL_0      (34U)
#define SDLR_ESM0_ESM_LVL_EVENT_USB0_USB2SSC_USB2SS_CORE_ECC_AGGR_A_ECC_AGGR_CORRECTED_ERR_LEVEL_0 (35U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD2_EMMCSD4SS_ECC_AGGR_RXMEM_EMMCSDSS_RXMEM_UNCORR_ERR_LVL_0    (36U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_ESM0_ESM_INT_CFG_LVL_0                                        (37U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_ESM0_ESM_INT_HI_LVL_0                                         (38U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_ESM0_ESM_INT_LOW_LVL_0                                        (39U)
#define SDLR_ESM0_ESM_LVL_EVENT_R5FSS0_COMMON0_ECC_DE_TO_ESM_0_0                                   (40U)
#define SDLR_ESM0_ESM_LVL_EVENT_R5FSS0_COMMON0_ECC_SE_TO_ESM_0_0                                   (42U)
#define SDLR_ESM0_ESM_LVL_EVENT_COMPUTE_CLUSTER0_PBIST_0_DFT_PBIST_SAFETY_ERROR_0                  (44U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR2_CORRECTED_ERR_LEVEL_0                          (45U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR2_UNCORRECTED_ERR_LEVEL_0                        (46U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR3_CORRECTED_ERR_LEVEL_0                          (47U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR3_UNCORRECTED_ERR_LEVEL_0                        (48U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD2_EMMCSD4SS_ECC_AGGR_TXMEM_EMMCSDSS_TXMEM_CORR_ERR_LVL_0      (49U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_DMTIMER_0_INTR_PEND_0                                         (50U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_DMTIMER_1_INTR_PEND_0                                         (51U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_DMTIMER_2_INTR_PEND_0                                         (52U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_DMTIMER_3_INTR_PEND_0                                         (53U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD0_EMMCSD8SS_ECC_AGGR_RXMEM_EMMCSDSS_RXMEM_CORR_ERR_LVL_0      (54U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD0_EMMCSD8SS_ECC_AGGR_RXMEM_EMMCSDSS_RXMEM_UNCORR_ERR_LVL_0    (55U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD0_EMMCSD8SS_ECC_AGGR_TXMEM_EMMCSDSS_TXMEM_CORR_ERR_LVL_0      (56U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD0_EMMCSD8SS_ECC_AGGR_TXMEM_EMMCSDSS_TXMEM_UNCORR_ERR_LVL_0    (57U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD1_EMMCSD4SS_ECC_AGGR_RXMEM_EMMCSDSS_RXMEM_CORR_ERR_LVL_0      (58U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD1_EMMCSD4SS_ECC_AGGR_RXMEM_EMMCSDSS_RXMEM_UNCORR_ERR_LVL_0    (59U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD1_EMMCSD4SS_ECC_AGGR_TXMEM_EMMCSDSS_TXMEM_CORR_ERR_LVL_0      (60U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD1_EMMCSD4SS_ECC_AGGR_TXMEM_EMMCSDSS_TXMEM_UNCORR_ERR_LVL_0    (61U)
#define SDLR_ESM0_ESM_LVL_EVENT_MMCSD2_EMMCSD4SS_ECC_AGGR_TXMEM_EMMCSDSS_TXMEM_UNCORR_ERR_LVL_0    (65U)
#define SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR_CORR_LEVEL_0                         (66U)
#define SDLR_ESM0_ESM_LVL_EVENT_CPSW0_ECC_DED_PEND_0                                               (67U)
#define SDLR_ESM0_ESM_LVL_EVENT_ICSSM0_COMMON_0_PR1_EDIO0_WD_TRIIG_0                               (68U)
#define SDLR_ESM0_ESM_LVL_EVENT_DDR16SS0_DDRSS_DRAM_ECC_UNCORR_ERR_LVL_0                           (69U)
#define SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_COMMON_0_CSI_FATAL_0                                    (70U)
#define SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_COMMON_0_CSI_NONFATAL_0                                 (71U)
#define SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_COMMON_0_CSI_LEVEL_0                                    (72U)
#define SDLR_ESM0_ESM_LVL_EVENT_FSS0_OSPI_0_OSPI_ECC_UNCORR_LVL_INTR_0                             (74U)
#define SDLR_ESM0_ESM_LVL_EVENT_GICSS0_GIC500SS_1_4_ECC_AGGR_ECC_AGGR_UNCORR_LEVEL_0               (75U)
#define SDLR_ESM0_ESM_LVL_EVENT_ICSSM0_ICSS_M_CORE_BORG_ECC_AGGR_PR1_ECC_DED_ERR_PEND_0            (76U)
#define SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR_UNCORR_LEVEL_0                       (77U)
#define SDLR_ESM0_ESM_LVL_EVENT_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR_MCANSS_ECC_UNCORR_LVL_INT_0      (78U)
#define SDLR_ESM0_ESM_LVL_EVENT_DCC6_INTR_ERR_LEVEL_0                                              (79U)
#define SDLR_ESM0_ESM_LVL_EVENT_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR_ECC_UNCORR_LEVEL_0             (80U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_1_WDG_INTR_0                                              (81U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_1_WDG_INTR_1                                              (82U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_1_WDG_INTR_2                                              (83U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_1_WDG_INTR_3                                              (84U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_1_WDG_INTR_4                                              (85U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_0_WDG_INTR_0                                              (87U)
#define SDLR_ESM0_ESM_LVL_EVENT_PDMA0_SAM62_PDMA_SPI_ECCAGGR_ECC_DED_PEND_0                        (88U)
#define SDLR_ESM0_ESM_LVL_EVENT_PDMA1_SAM62_PDMA_UART_ECCAGGR_ECC_DED_PEND_0                       (89U)
#define SDLR_ESM0_ESM_LVL_EVENT_PSRAMECC0_PSRAM256X32E_ECC_AGGR_ECC_UNCORR_LEVEL_0                 (90U)
#define SDLR_ESM0_ESM_LVL_EVENT_R5FSS0_CORE0_ECC_UNCORRECTED_LEVEL_0                               (91U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_0_WDG_INTR_1                                              (92U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR1_UNCORRECTED_ERR_LEVEL_0                        (93U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR0_UNCORRECTED_ERR_LEVEL_0                        (94U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_ECC_ECCAGGR_COREPAC_UNCORRECTED_ERR_LEVEL_0                 (95U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_0_WDG_INTR_2                                              (96U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_0_WDG_INTR_3                                              (97U)
#define SDLR_ESM0_ESM_LVL_EVENT_DFTSS0_DFT_SAFETY_123_0                                            (98U)
#define SDLR_ESM0_ESM_LVL_EVENT_DFTSS0_DFT_SAFETY_MULTI_0                                          (99U)
#define SDLR_ESM0_ESM_LVL_EVENT_DFTSS0_DFT_SAFETY_ONE_0                                            (100U)
#define SDLR_ESM0_ESM_LVL_EVENT_MCU_MCU0_VDD_CORE_GLDTC_STAT_THRESH_HI_FLAG_IPCFG_0                (101U)
#define SDLR_ESM0_ESM_LVL_EVENT_MCU_MCU0_VDD_CORE_GLDTC_STAT_THRESH_LOW_FLAG_IPCFG_0               (102U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_RTI_0_WDG_INTR_4                                              (103U)
#define SDLR_ESM0_ESM_LVL_EVENT_DDR16SS0_DDRSS_V2A_OTHER_ERR_LVL_0                                 (110U)
#define SDLR_ESM0_ESM_LVL_EVENT_USB0_USB2SSC_USB2SS_CORE_ECC_AGGR_A_ECC_AGGR_UNCORRECTED_ERR_LEVEL_0 (111U)
#define SDLR_ESM0_ESM_LVL_EVENT_DCC0_INTR_ERR_LEVEL_0                                              (112U)
#define SDLR_ESM0_ESM_LVL_EVENT_DCC1_INTR_ERR_LEVEL_0                                              (113U)
#define SDLR_ESM0_ESM_LVL_EVENT_DCC2_INTR_ERR_LEVEL_0                                              (114U)
#define SDLR_ESM0_ESM_LVL_EVENT_DCC3_INTR_ERR_LEVEL_0                                              (115U)
#define SDLR_ESM0_ESM_LVL_EVENT_DCC4_INTR_ERR_LEVEL_0                                              (116U)
#define SDLR_ESM0_ESM_LVL_EVENT_DCC5_INTR_ERR_LEVEL_0                                              (117U)
#define SDLR_ESM0_ESM_LVL_EVENT_SA3_SS0_DMSS_ECCAGGR_0_DMSS_ECC_DED_PEND_0                         (118U)
#define SDLR_ESM0_ESM_LVL_EVENT_SA3_SS0_DMSS_ECCAGGR_0_DMSS_ECC_SEC_PEND_0                         (119U)
#define SDLR_ESM0_ESM_LVL_EVENT_SA3_SS0_SA_UL_0_SA_UL_ECC_CORR_LEVEL_0                             (120U)
#define SDLR_ESM0_ESM_LVL_EVENT_SA3_SS0_SA_UL_0_SA_UL_ECC_UNCORR_LEVEL_0                           (121U)
#define SDLR_ESM0_ESM_LVL_EVENT_R5FSS0_CORE0_EXP_INTR_0                                            (124U)
#define SDLR_ESM0_ESM_LVL_EVENT_PLLFRACF_SSMOD0_LOCKLOSS_IPCFG_0                                   (128U)
#define SDLR_ESM0_ESM_LVL_EVENT_PLLFRACF_SSMOD1_LOCKLOSS_IPCFG_0                                   (129U)
#define SDLR_ESM0_ESM_LVL_EVENT_PLLFRACF_SSMOD2_LOCKLOSS_IPCFG_0                                   (130U)
#define SDLR_ESM0_ESM_LVL_EVENT_PLLFRACF_SSMOD8_LOCKLOSS_IPCFG_0                                   (131U)
#define SDLR_ESM0_ESM_LVL_EVENT_PLLFRACF_SSMOD12_LOCKLOSS_IPCFG_0                                  (132U)
#define SDLR_ESM0_ESM_LVL_EVENT_PLLFRACF_SSMOD15_LOCKLOSS_IPCFG_0                                  (133U)
#define SDLR_ESM0_ESM_LVL_EVENT_MCU_PLLFRACF_SSMOD0_LOCKLOSS_IPCFG_0                               (134U)
#define SDLR_ESM0_ESM_LVL_EVENT_GLUELOGIC_HFOSC0_CLKLOSS_GLUE_REF_CLK_LOSS_DETECT_OUT_0            (135U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_VTM0_COMMON_0_THERM_LVL_LT_TH0_INTR_0                         (136U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_VTM0_COMMON_0_THERM_LVL_GT_TH1_INTR_0                         (137U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_VTM0_COMMON_0_THERM_LVL_GT_TH2_INTR_0                         (138U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_VTM0_K3VTM_NC_ECCAGGR_CORR_LEVEL_0                            (139U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_VTM0_K3VTM_NC_ECCAGGR_UNCORR_LEVEL_0                          (140U)
#define SDLR_ESM0_ESM_LVL_EVENT_FSS0_FSAS_0_ECC_INTR_ERR_PEND_0                                    (141U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_EXTERRIRQ_0                                                 (144U)
#define SDLR_ESM0_ESM_LVL_EVENT_A53SS0_INTERRIRQ_0                                                 (145U)
#define SDLR_ESM0_ESM_LVL_EVENT_USB1_USB2SSC_USB2SS_CORE_ECC_AGGR_A_ECC_AGGR_CORRECTED_ERR_LEVEL_0 (146U)
#define SDLR_ESM0_ESM_LVL_EVENT_USB1_USB2SSC_USB2SS_CORE_ECC_AGGR_A_ECC_AGGR_UNCORRECTED_ERR_LEVEL_0 (147U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_ECC_AGGR_1_ECC_CORRECTED_LEVEL_0                              (150U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_ECC_AGGR_1_ECC_UNCORRECTED_LEVEL_0                            (151U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_ECC_AGGR_0_ECC_CORRECTED_LEVEL_0                              (153U)
#define SDLR_ESM0_ESM_LVL_EVENT_SMS0_ECC_AGGR_0_ECC_UNCORRECTED_LEVEL_0                            (154U)
#define SDLR_ESM0_ESM_LVL_EVENT_PBIST1_DFT_PBIST_SAFETY_ERROR_0                                    (156U)
#define SDLR_ESM0_ESM_LVL_EVENT_PBIST0_DFT_PBIST_SAFETY_ERROR_0                                    (157U)
#define SDLR_ESM0_ESM_LVL_EVENT_WKUP_PBIST0_DFT_PBIST_SAFETY_ERROR_0                               (158U)
#define SDLR_ESM0_ESM_PLS_EVENT0_RTI0_INTR_WWD_0                                                   (160U)
#define SDLR_ESM0_ESM_PLS_EVENT1_RTI0_INTR_WWD_0                                                   (160U)
#define SDLR_ESM0_ESM_PLS_EVENT2_RTI0_INTR_WWD_0                                                   (160U)
#define SDLR_ESM0_ESM_PLS_EVENT0_RTI1_INTR_WWD_0                                                   (161U)
#define SDLR_ESM0_ESM_PLS_EVENT1_RTI1_INTR_WWD_0                                                   (161U)
#define SDLR_ESM0_ESM_PLS_EVENT2_RTI1_INTR_WWD_0                                                   (161U)
#define SDLR_ESM0_ESM_PLS_EVENT0_RTI15_INTR_WWD_0                                                  (162U)
#define SDLR_ESM0_ESM_PLS_EVENT1_RTI15_INTR_WWD_0                                                  (162U)
#define SDLR_ESM0_ESM_PLS_EVENT2_RTI15_INTR_WWD_0                                                  (162U)
#define SDLR_ESM0_ESM_PLS_EVENT0_WKUP_RTI0_INTR_WWD_0                                              (163U)
#define SDLR_ESM0_ESM_PLS_EVENT1_WKUP_RTI0_INTR_WWD_0                                              (163U)
#define SDLR_ESM0_ESM_PLS_EVENT2_WKUP_RTI0_INTR_WWD_0                                              (163U)
#define SDLR_ESM0_ESM_PLS_EVENT0_PBIST0_DFT_PBIST_CPU_0                                            (164U)
#define SDLR_ESM0_ESM_PLS_EVENT1_PBIST0_DFT_PBIST_CPU_0                                            (164U)
#define SDLR_ESM0_ESM_PLS_EVENT2_PBIST0_DFT_PBIST_CPU_0                                            (164U)
#define SDLR_ESM0_ESM_PLS_EVENT0_PBIST1_DFT_PBIST_CPU_0                                            (165U)
#define SDLR_ESM0_ESM_PLS_EVENT1_PBIST1_DFT_PBIST_CPU_0                                            (165U)
#define SDLR_ESM0_ESM_PLS_EVENT2_PBIST1_DFT_PBIST_CPU_0                                            (165U)
#define SDLR_ESM0_ESM_PLS_EVENT0_GICSS0_COMMON_0_AXIM_ERR_0                                        (166U)
#define SDLR_ESM0_ESM_PLS_EVENT1_GICSS0_COMMON_0_AXIM_ERR_0                                        (166U)
#define SDLR_ESM0_ESM_PLS_EVENT2_GICSS0_COMMON_0_AXIM_ERR_0                                        (166U)
#define SDLR_ESM0_ESM_PLS_EVENT0_GICSS0_COMMON_0_ECC_FATAL_0                                       (167U)
#define SDLR_ESM0_ESM_PLS_EVENT1_GICSS0_COMMON_0_ECC_FATAL_0                                       (167U)
#define SDLR_ESM0_ESM_PLS_EVENT2_GICSS0_COMMON_0_ECC_FATAL_0                                       (167U)
#define SDLR_ESM0_ESM_PLS_EVENT0_WKUP_PBIST0_DFT_PBIST_CPU_0                                       (170U)
#define SDLR_ESM0_ESM_PLS_EVENT1_WKUP_PBIST0_DFT_PBIST_CPU_0                                       (170U)
#define SDLR_ESM0_ESM_PLS_EVENT2_WKUP_PBIST0_DFT_PBIST_CPU_0                                       (170U)
#define SDLR_ESM0_ESM_PLS_EVENT0_COMPUTE_CLUSTER0_PBIST_0_DFT_PBIST_CPU_0                          (176U)
#define SDLR_ESM0_ESM_PLS_EVENT1_COMPUTE_CLUSTER0_PBIST_0_DFT_PBIST_CPU_0                          (176U)
#define SDLR_ESM0_ESM_PLS_EVENT2_COMPUTE_CLUSTER0_PBIST_0_DFT_PBIST_CPU_0                          (176U)
#define SDLR_ESM0_ESM_PLS_EVENT0_RTI2_INTR_WWD_0                                                   (177U)
#define SDLR_ESM0_ESM_PLS_EVENT1_RTI2_INTR_WWD_0                                                   (177U)
#define SDLR_ESM0_ESM_PLS_EVENT2_RTI2_INTR_WWD_0                                                   (177U)
#define SDLR_ESM0_ESM_PLS_EVENT0_RTI3_INTR_WWD_0                                                   (178U)
#define SDLR_ESM0_ESM_PLS_EVENT1_RTI3_INTR_WWD_0                                                   (178U)
#define SDLR_ESM0_ESM_PLS_EVENT2_RTI3_INTR_WWD_0                                                   (178U)

#ifdef __cplusplus
}
#endif
#endif /* SDLR_ESM0_INTERRUPT_MAP_H_ */
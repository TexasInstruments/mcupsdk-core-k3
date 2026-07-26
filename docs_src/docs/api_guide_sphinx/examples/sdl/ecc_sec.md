# SDL ECC SEC
## Introduction

This example takes an aggregator index as input from the user and performs single bit error test for the corresponding aggregator.  It involves the following steps:

* Setup of an ESM application callback to receive Single Error Correction (SEC) and setup of ECC Aggregators in general
* Triggering of ECC events for all the RAM IDs, including Interconnect type and Wrapper type
* Printing out error information within the ECC callback upon reception of ECC events

## Aggregators Supported

The following aggregators can be tested using this example.


::::{only} SOC_AM62AX

| Aggregator Index | ECC Aggregator |
|---|---|
| 0 | SDL_PSCSS0_SAM62A_MAIN_PSC_WRAP_ECC_AGGR |
| 1 | SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR |
| 2 | SDL_PSRAMECC1_PSRAM256X32E_ECC_AGGR |
| 3 | SDL_MSRAM_64K0_MSRAM2KX256E_ECC_AGGR |
| 4 | SDL_WKUP_ECC_AGGR1_SAM62A_DM_MCU_ECC_AGGR |
| 5 | SDL_DMASS1_DMSS_CSI_AM62A_ECCAGGR |
| 6 | SDL_MCU_MSRAM_256K1_MSRAM32KX64E_ECC_AGGR |
| 7 | SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR |
| 8 | SDL_FSS0_FSS_UL_OSPI0_OSPI_WRAP_ECC_AGGR |
| 9 | SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR |
| 10 | SDL_CPSW0_CPSW_3GUSS_CORE_ECC_CPSW_ECC_AGGR |
| 11 | SDL_MCU_MSRAM_256K0_MSRAM32KX64E_ECC_AGGR |
| 12 | SDL_GICSS0_GIC500SS_1_4_ECC_AGGR |
| 13 | SDL_ECC_AGGR1_SAM62A_SEC_MCU_ECC_AGGR |
| 14 | SDL_DMASS0_DMSS_AM62A_ECCAGGR |
| 15 | SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR |
| 16 | SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_RXMEM |
| 17 | SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_TXMEM |
| 18 | SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_RXMEM |
| 19 | SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_TXMEM |
| 20 | SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_TXMEM |
| 21 | SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_RXMEM |
| 22 | SDL_MCU_ECC_AGGR0_SAM62A_MCU_MCU_ECC_AGGR |
| 23 | SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR |
| 24 | SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR |
| 25 | SDL_WKUP_ECC_AGGR2_SAM62A_WKUP_SAFE_ECC_AGGR |
| 26 | SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR |
| 27 | SDL_SMS0_SMS_HSM_ECC |
| 28 | SDL_SMS0_SMS_TIFS_ECC |
| 29 | SDL_VPAC0_SAM62A_VPAC_WRAP_IVPAC_TOP_0_PAC_BASE_KSDW_ECC_AGGR |
| 30 | SDL_VPAC0_SAM62A_VPAC_WRAP_IVPAC_TOP_0_VPAC_LDC0_KSDW_ECC_AGGR |
| 31 | SDL_VPAC0_SAM62A_VPAC_WRAP_IVPAC_TOP_0_VPAC_VISS0_KSDW_ECC_AGGR |
| 32 | SDL_MCU_ECC_AGGR1_SAM62A_MCU_PULSAR_UL_ECC_AGGR |
| 33 | SDL_C7X256V0_SAM62A_C7XV_WRAP_ECC_AGGR |
| 34 | SDL_USB1_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR |
| 35 | SDL_USB0_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR |
| 36 | SDL_WKUP_PSRAMECC_8K0_PSRAM8KX32E_ECC_AGGR |
| 37 | SDL_PDMA0_SAM62_PDMA_SPI_ECCAGGR |
| 38 | SDL_WKUP_ECC_AGGR0_SAM62A_DM_DM_ECC_AGGR |
| 39 | SDL_PDMA1_SAM62_PDMA_UART_ECCAGGR |
| 40 | SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 41 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE0 |
| 42 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE1 |
| 43 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE2 |
| 44 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE3 |
| 45 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_COREPAC |
| 46 | SDL_MCU_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 47 | SDL_MCU_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 48 | SDL_ECC_AGGR0_SAM62A_SEC_HSM_ECC_AGGR |

::::


::::{only} SOC_AM62PX

| Aggregator Index | ECC Aggregator |
|---|---|
| 0 | SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR |
| 1 | SDL_DSS_DSI0_K3_DSS_DSI_DSI_TOP_ECC_AGGR_SYS |
| 2 | SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR |
| 3 | SDL_PSRAMECC1_PSRAM256X32E_ECC_AGGR |
| 4 | SDL_MSRAM_64K0_MSRAM2KX256E_ECC_AGGR |
| 5 | SDL_WKUP_ECC_AGGR2 |
| 6 | SDL_ECC_AGGR0_SAM67_SEC_HSM_ECC_AGGR |
| 7 | SDL_DMASS1_DMSS_CSI_AM62A_ECCAGGR |
| 8 | SDL_MCU_MSRAM_256K1_MSRAM32KX64E_ECC_AGGR |
| 9 | SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR |
| 10 | SDL_WKUP_ECC_AGGR1 |
| 11 | SDL_FSS0_FSS_UL_OSPI0_OSPI_WRAP_ECC_AGGR |
| 12 | SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR |
| 13 | SDL_GICSS0_GIC500SS_1_4_ECC_AGGR |
| 14 | SDL_CPSW0_CPSW_3GUSS_AM67_CORE_ECC_CPSW_ECC_AGGR |
| 15 | SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR |
| 16 | SDL_PSCSS0_SAM67_MAIN_PSC_WRAP_ECC_AGGR |
| 17 | SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_RXMEM |
| 18 | SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_TXMEM |
| 19 | SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR |
| 20 | SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR |
| 21 | SDL_MCU_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 22 | SDL_WKUP_ECC_AGGR0 |
| 23 | SDL_DMASS0_ECC_AGGR_0 |
| 24 | SDL_PDMA0_SAM67_PDMA_SPI_ECCAGGR |
| 25 | SDL_MCU_ECC_AGGR1_SAM62A_MCU_PULSAR_UL_ECC_AGGR |
| 26 | SDL_USB1_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR |
| 27 | SDL_USB0_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR |
| 28 | SDL_MCU_MSRAM_256K0_MSRAM32KX64E_ECC_AGGR |
| 29 | SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_RXMEM |
| 30 | SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_TXMEM |
| 31 | SDL_WKUP_PSRAMECC_8K0_PSRAM8KX32E_ECC_AGGR |
| 32 | SDL_PDMA1_SAM62_PDMA_UART_ECCAGGR |
| 33 | SDL_MCU_ECC_AGGR0 |
| 34 | SDL_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 35 | SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 36 | SDL_MMCSD0_EMMC8SS_16FFC_ECC_AGGR_TXMEM |
| 37 | SDL_MMCSD0_EMMC8SS_16FFC_ECC_AGGR_RXMEM |
| 38 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE0 |
| 39 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE1 |
| 40 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE2 |
| 41 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE3 |
| 42 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_COREPAC |
| 43 | SDL_MCU_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR |

::::


::::{only} SOC_AM62DX

| Aggregator Index | ECC Aggregator |
|---|---|
| 0 | SDL_PSCSS0_SAM62A_MAIN_PSC_WRAP_ECC_AGGR |
| 1 | SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR |
| 2 | SDL_PSRAMECC1_PSRAM256X32E_ECC_AGGR |
| 3 | SDL_MSRAM_64K0_MSRAM2KX256E_ECC_AGGR |
| 4 | SDL_WKUP_ECC_AGGR1_SAM62A_DM_MCU_ECC_AGGR |
| 5 | SDL_DMASS1_DMSS_CSI_AM62A_ECCAGGR |
| 6 | SDL_MCU_MSRAM_256K1_MSRAM32KX64E_ECC_AGGR |
| 7 | SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR |
| 8 | SDL_FSS0_FSS_UL_OSPI0_OSPI_WRAP_ECC_AGGR |
| 9 | SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR |
| 10 | SDL_CPSW0_CPSW_3GUSS_CORE_ECC_CPSW_ECC_AGGR |
| 11 | SDL_MCU_MSRAM_256K0_MSRAM32KX64E_ECC_AGGR |
| 12 | SDL_GICSS0_GIC500SS_1_4_ECC_AGGR |
| 13 | SDL_ECC_AGGR1_SAM62A_SEC_MCU_ECC_AGGR |
| 14 | SDL_DMASS0_DMSS_AM62A_ECCAGGR |
| 15 | SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_RXMEM |
| 16 | SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_TXMEM |
| 17 | SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_RXMEM |
| 18 | SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_TXMEM |
| 19 | SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_TXMEM |
| 20 | SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_RXMEM |
| 21 | SDL_MCU_ECC_AGGR0_SAM62A_MCU_MCU_ECC_AGGR |
| 22 | SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR |
| 23 | SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR |
| 24 | SDL_WKUP_ECC_AGGR2_SAM62A_WKUP_SAFE_ECC_AGGR |
| 25 | SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR |
| 26 | SDL_SMS0_SMS_HSM_ECC |
| 27 | SDL_SMS0_SMS_TIFS_ECC |
| 28 | SDL_MCU_ECC_AGGR1_SAM62A_MCU_PULSAR_UL_ECC_AGGR |
| 29 | SDL_C7X256V0_SAM62A_C7XV_WRAP_ECC_AGGR |
| 30 | SDL_USB1_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR |
| 31 | SDL_USB0_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR |
| 32 | SDL_WKUP_PSRAMECC_8K0_PSRAM8KX32E_ECC_AGGR |
| 33 | SDL_PDMA0_SAM62_PDMA_SPI_ECCAGGR |
| 34 | SDL_WKUP_ECC_AGGR0_SAM62A_DM_DM_ECC_AGGR |
| 35 | SDL_PDMA1_SAM62_PDMA_UART_ECCAGGR |
| 36 | SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 37 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE0 |
| 38 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE1 |
| 39 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE2 |
| 40 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE3 |
| 41 | SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_COREPAC |
| 42 | SDL_MCU_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 43 | SDL_MCU_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 44 | SDL_ECC_AGGR0_SAM62A_SEC_HSM_ECC_AGGR |

::::


::::{only} SOC_AM62X

| Aggregator Index | ECC Aggregator |
|---|---|
| 0 | SDL_COMPUTE_CLUSTER0_SAM62_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE0 |
| 1 | SDL_COMPUTE_CLUSTER0_SAM62_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE1 |
| 2 | SDL_COMPUTE_CLUSTER0_SAM62_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE2 |
| 3 | SDL_COMPUTE_CLUSTER0_SAM62_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE3 |
| 4 | SDL_COMPUTE_CLUSTER0_SAM62_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_COREPAC |
| 5 | SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR |
| 6 | SDL_DMASS0_DMSS_AM62_ECCAGGR |
| 7 | SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR |
| 8 | SDL_FSS0_FSS_UL_OSPI0_OSPI_WRAP_ECC_AGGR |
| 9 | SDL_GICSS0_GIC500SS_1_4_ECC_AGGR |
| 10 | SDL_ICSSM0_ICSS_M_CORE_BORG_ECC_AGGR |
| 11 | SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 12 | SDL_MCU_ECC_AGGR0_SAM62_MCU_ECC_AGGR |
| 13 | SDL_MCU_M4FSS0_BLAZAR_ECC |
| 14 | SDL_MCU_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 15 | SDL_MCU_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 16 | SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_RXMEM |
| 17 | SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_TXMEM |
| 18 | SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_RXMEM |
| 19 | SDL_MMCSD1_EMMCSD4SS_ECC_AGGR_TXMEM |
| 20 | SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_RXMEM |
| 21 | SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_TXMEM |
| 22 | SDL_PDMA0_SAM62_PDMA_SPI_ECCAGGR |
| 23 | SDL_PDMA1_SAM62_PDMA_UART_ECCAGGR |
| 24 | SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR |
| 25 | SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR |
| 26 | SDL_SA3_SS0_SA3SS_AM62_DMSS_ECCAGGR |
| 27 | SDL_SA3_SS0_SA3SS_AM62_SA_UL_ECC_AGGR |
| 28 | SDL_SMS0_SMS_HSM_ECC |
| 29 | SDL_SMS0_SMS_TIFS_ECC |
| 30 | SDL_USB0_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR |
| 31 | SDL_USB1_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR |
| 32 | SDL_WKUP_ECC_AGGR0_SAM62_DM_ECC_AGGR |
| 33 | SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR |
| 34 | SDL_WKUP_SAFE_ECC_AGGR0_SAM62_WKUP_SAFE_ECC_AGGR |
| 35 | SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR |
| 36 | SDL_CPSW0_CPSW_3GUSS_CORE_ECC_CPSW_ECC_AGGR |

::::


::::{only} SOC_AM275X

| Aggregator Index | ECC Aggregator |
|---|---|
| 0 | SDL_C7X256V1_ECC_AGGR |
| 1 | SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR |
| 2 | SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR |
| 3 | SDL_IDOM0_PULSAR_PLL_ECC_AGGR10 |
| 4 | SDL_IDOM0_PULSAR_PLL_ECC_AGGR8 |
| 5 | SDL_MSRAM_1MB4_MSRAM32KX256E_ECC_AGGR |
| 6 | SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR |
| 7 | SDL_FSS1_FSS_HB_WRAP_ECC_AGGR |
| 8 | SDL_FSS1_FSS_OSPI0_OSPI_WRAP_ECC_AGGR |
| 9 | SDL_FSS1_FSS_OSPI1_OSPI_WRAP_ECC_AGGR |
| 10 | SDL_ECC_AGGR3_AM275_R5_MAIN_IP_ECC_AGGR |
| 11 | SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR |
| 12 | SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR |
| 13 | SDL_MSRAM_1MB2_MSRAM32KX256E_ECC_AGGR |
| 14 | SDL_MSRAM_1MB1_MSRAM32KX256E_ECC_AGGR |
| 15 | SDL_C7X256V0_ECC_AGGR |
| 16 | SDL_MSRAM_1MB0_MSRAM32KX256E_ECC_AGGR |
| 17 | SDL_CPSW0_CPSW_3GUSS_AM62L_CORE_ECC_CPSW_ECC_AGGR |
| 18 | SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_TXMEM |
| 19 | SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_RXMEM |
| 20 | SDL_PDMA4_AM275_PDMA_SPI1_ECCAGGR |
| 21 | SDL_ECC_AGGR0_AM275_SEC_HSM_ECC_AGGR |
| 22 | SDL_IDOM0_MAIN_PLL_ECC_AGGR6_IDOM0_MAIN_PLL_ECC_AGGR |
| 23 | SDL_IDOM0_MAIN_PLL_ECC_AGGR4_IDOM0_MAIN_PLL_ECC_AGGR |
| 24 | SDL_SMS0_SMS_HSM_ECC |
| 25 | SDL_SMS0_SMS_TIFS_ECC |
| 26 | SDL_FSS0_FSS_OF_UL_FSAS_FOTA_FSS_OF_UL_FOTA_ACC_ECC_AGGR |
| 27 | SDL_FSS0_FSS_OF_UL_OSPI0_OSPI_WRAP_ECC_AGGR |
| 28 | SDL_MSRAM_1MB3_MSRAM32KX256E_ECC_AGGR |
| 29 | SDL_USB0_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR |
| 30 | SDL_WKUP_PSRAMECC_8K0_PSRAM8KX32E_ECC_AGGR |
| 31 | SDL_MLB0_MLBSS2P0_MLBDIM_WRAP_ECC_AGGR |
| 32 | SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 33 | SDL_ADC12FCC0_ADC12FC_16FFC_ADC12_CORE_FIFO_RAM_ECC_AGGR |
| 34 | SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR |
| 35 | SDL_R5FSS0_PULSAR_SL_CPU1_ECC_AGGR |
| 36 | SDL_R5FSS1_PULSAR_SL_CPU0_ECC_AGGR |
| 37 | SDL_R5FSS1_PULSAR_SL_CPU1_ECC_AGGR |
| 38 | SDL_WKUP_ECC_AGGR1_AM275_DM_MCU_ECC_AGGR |
| 39 | SDL_WKUP_ECC_AGGR0_AM275_DM_DM_ECC_AGGR |
| 40 | SDL_PDMA1_SAM62_PDMA_UART_ECCAGGR |
| 41 | SDL_MSRAM_1MB5_MSRAM32KX256E_ECC_AGGR |
| 42 | SDL_PDMA0_SAM67_PDMA_SPI_ECCAGGR |
| 43 | SDL_IDOM1_MAIN_PLL_ECC_AGGR5_IDOM1_MAIN_PLL_ECC_AGGR |
| 44 | SDL_IDOM1_MAIN_PLL_ECC_AGGR7_IDOM1_MAIN_PLL_ECC_AGGR |
| 45 | SDL_MCAN3_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 46 | SDL_MCAN2_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 47 | SDL_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 48 | SDL_DMASS0_ECC_AGGR_0 |
| 49 | SDL_MCAN4_MCANSS_MSGMEM_WRAP_ECC_AGGR |
| 50 | SDL_IDOM1_PULSAR_PLL_ECC_AGGR9 |
| 51 | SDL_IDOM1_PULSAR_PLL_ECC_AGGR11 |
| 52 | SDL_WKUP_ECC_AGGR2_AM275_WKUP_SAFE_ECC_AGGR |
| 53 | SDL_WKUP_PSRAM2KX32E0_PSRAM2KX32E_ECC_AGGR |
| 54 | SDL_ECC_AGGR2_AM275_MAIN_SYS_IP_ECC_AGGR |

::::

## Supported Combinations
::::{only} SOC_AM62X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/ecc_sec/ |


::::


::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/ecc_sec/ |


::::


::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/ecc_sec/ |


::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
## Sample Output

Shown below is a sample output when the application is run for a couple of aggregators,


::::{only} SOC_AM62X

```
[MAIN_Cortex_R5_0_0] Sciclient direct init..... SUCCESS

ECC Example Application

ECC_Test_init: Init MCU ESM complete

ECC_Test_init: Init MAIN ESM complete

ECC_Test_init: ECC Callback Init complete for MCU ESM

ECC_Test_init: ECC Callback Init complete for Main ESM

ECC SDL API tests: starting

Refer the User Guide for the aggregator information

Select the memory to test...
14

...selected 14

ecc_aggrtest: [14] single bit error self test: SDL_MCU_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR starting

ECC_Memory_init: [14] SDL_MCU_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR ECC Init complete

Self test started accessable RamId 0  starting

Self Test completed for accessable RamId 0

Self test started RamId 1  starting

Self test started RamId 1  completed

Select the memory to test...
20

...selected 20

ecc_aggrtest: [20] single bit error self test: SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_RXMEM starting

ECC_Memory_init: [20] SDL_MMCSD2_EMMCSD4SS_ECC_AGGR_RXMEM ECC Init complete

Inject test started not accessable RamId 0 starting

Injected ECC error and got ESM Interrupt

Select the memory to test...
```

::::


::::{only} SOC_AM62PX

```
[MCU_R5FSS0_0]
ECC Example Application

ECC_Test_init: Init MCU ESM complete

ECC_Test_init: Init MAIN ESM complete

ECC_Test_init: ECC Callback Init complete for MCU ESM

ECC_Test_init: ECC Callback Init complete for Main ESM

ECC SDL API tests: starting

Refer the User Guide for the aggregator information

Select the memory to test...

...selected 4

ecc_aggrtest: [4] single bit error self test: SDL_MSRAM_64K0_MSRAM2KX256E_ECC_AGGR starting

ECC_Memory_init: [4] SDL_MSRAM_64K0_MSRAM2KX256E_ECC_AGGR ECC Init complete

Self test started accessable RamId 0  starting

Self Test completed for accessable RamId 0

Select the memory to test...
10

...selected 10

ecc_aggrtest: [10] single bit error self test: SDL_WKUP_ECC_AGGR1 starting

ECC_Memory_init: [10] SDL_WKUP_ECC_AGGR1 ECC Init complete

Self test started RamId 0  starting

Self test started RamId 0  completed

Self test started RamId 1  starting

Self test started RamId 1  completed

Self test started RamId 2  starting

Self test started RamId 2  completed

Self test started RamId 3  starting

Self test started RamId 3  completed

Self test started RamId 4  starting

Self test started RamId 4  completed

Self test started RamId 5  starting

Self test started RamId 5  completed

Self test started RamId 6  starting

Self test started RamId 6  completed

Select the memory to test...
```

::::


::::{only} SOC_AM62AX

   ECC Example Application

   ECC_Test_init: Init MCU ESM complete

   ECC_Test_init: Init MAIN ESM complete

   ECC_Test_init: ECC Callback Init complete for MCU ESM

   ECC_Test_init: ECC Callback Init complete for Main ESM

   ECC SDL API tests: starting

   Select the memory to test...
   0

   ...selected 0

   ecc_aggrtest: [0] single bit error self test: SDL_PSCSS0_SAM62A_MAIN_PSC_WRAP_ECC_AGGR starting


   ECC_Memory_init: [0] SDL_PSCSS0_SAM62A_MAIN_PSC_WRAP_ECC_AGGR ECC Init complete

   Inject test started not accessable RamId 0 starting

   Injected ECC error and got ESM Interrupt

   Select the memory to test...
   4

   ...selected 4

   ecc_aggrtest: [4] single bit error self test: SDL_WKUP_ECC_AGGR1_SAM62A_DM_MCU_ECC_AGGR starting


   ECC_Memory_init: [4] SDL_WKUP_ECC_AGGR1_SAM62A_DM_MCU_ECC_AGGR ECC Init complete

   Self test started RamId 0  starting

   Self test started RamId 0  completed

   Self test started RamId 1  starting

   Self test started RamId 1  completed

   Self test started RamId 2  starting

   Self test started RamId 2  completed

   Self test started RamId 3  starting

   Self test started RamId 3  completed

   Select the memory to test...
   ::::


::::{only} SOC_AM62DX

   ECC Example Application

   ECC_Test_init: Init MCU ESM complete

   ECC_Test_init: Init MAIN ESM complete

   ECC_Test_init: ECC Callback Init complete for MCU ESM

   ECC_Test_init: ECC Callback Init complete for Main ESM

   ECC SDL API tests: starting

   Select the memory to test...

   4
   ...selected 4

   ecc_aggrtest: [4] single bit error self test: SDL_WKUP_ECC_AGGR1_SAM62A_DM_MCU_ECC_AGGR starting


   ECC_Memory_init: [4] SDL_WKUP_ECC_AGGR1_SAM62A_DM_MCU_ECC_AGGR ECC Init complete

   Self test started RamId 0  starting

   Self test started RamId 0  completed

   Self test started RamId 1  starting

   Self test started RamId 1  completed

   Self test started RamId 2  starting

   Self test started RamId 2  completed

   Self test started RamId 3  starting

   Self test started RamId 3  completed

   Select the memory to test...

   5

   ecc_aggrtest: [5] single bit error self test: SDL_DMASS1_DMSS_CSI_AM62A_ECCAGGR starting


   ECC_Memory_init: [5] SDL_DMASS1_DMSS_CSI_AM62A_ECCAGGR ECC Init complete

   Inject test started not accessable RamId 0 starting

   Injected ECC error and got ESM Interrupt

   Inject test started not accessable RamId 1 starting

   Injected ECC error and got ESM Interrupt

   Inject test started not accessable RamId 2 starting

   Injected ECC error and got ESM Interrupt

   Inject test started not accessable RamId 3 starting

   Injected ECC error and got ESM Interrupt

   Inject test started not accessable RamId 4 starting

   Injected ECC error and got ESM Interrupt

   Inject test started not accessable RamId 5 starting

   Injected ECC error and got ESM Interrupt

   Inject test started not accessable RamId 6 starting

   Injected ECC error and got ESM Interrupt

   Inject test started not accessable RamId 7 starting

   Injected ECC error and got ESM Interrupt

   Inject test started not accessable RamId 8 starting

   Injected ECC error and got ESM Interrupt

   Select the memory to test...

   ::::


::::{only} SOC_AM275X

   ECC Example Application

   ECC_Test_init: Init MCU ESM complete

   ECC_Test_init: Init MAIN ESM complete

   ECC_Test_init: ECC Callback Init complete for MCU ESM

   ECC_Test_init: ECC Callback Init complete for Main ESM

   ECC SDL API tests: starting

   Select the memory to test...

   1

   ...selected 1

   ecc_aggrtest: [1] single bit error self test: SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR starting


   ECC_Memory_init: [1] SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR ECC Init complete

   Self test started RamId 0  starting

   Self test started RamId 0  completed

   Self test started RamId 1  starting

   Self test started RamId 1  completed

   Self test started RamId 2  starting

   Self test started RamId 2  completed

   Self test started RamId 3  starting

   Self test started RamId 3  completed

   Select the memory to test...
   5

   ...selected 5

   ecc_aggrtest: [5] single bit error self test: SDL_MSRAM_1MB4_MSRAM32KX256E_ECC_AGGR starting


   ECC_Memory_init: [5] SDL_MSRAM_1MB4_MSRAM32KX256E_ECC_AGGR ECC Init complete

   Inject test started not accessable RamId 0 starting

   Injected ECC error and got ESM Interrupt

   Select the memory to test...
   ::::


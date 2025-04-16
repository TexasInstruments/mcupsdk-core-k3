/*
 *  Copyright (C) 2023-25 Texas Instruments Incorporated
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
 *  \file j722s/udma_soc.h
 *
 *  \brief UDMA Low Level Driver J722S SOC specific file.
 */

#ifndef UDMA_SOC_H_
#define UDMA_SOC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \anchor Udma_InstanceIdSoc
 *  \name UDMA Instance ID specific to SOC
 *
 *  UDMA instance ID - BCDMA/PKTDMA
 *
 *  @{
 */
/** \brief BCDMA instance */
#define UDMA_INST_ID_BCDMA_0             (UDMA_INST_ID_2)
/** \brief PKTDMA instance */
#define UDMA_INST_ID_PKTDMA_0            (UDMA_INST_ID_3)
/** \brief BCDMA(CSI) instance */
#define UDMA_INST_ID_BCDMA_1             (UDMA_INST_ID_4)

/** \brief Start of UDMA instance */
#define UDMA_INST_ID_START               (UDMA_INST_ID_2)
/** \brief Maximum number of UDMA instance */
#define UDMA_INST_ID_MAX                 (UDMA_INST_ID_4)
/** \brief Total number of UDMA instances */
#define UDMA_NUM_INST_ID                 (UDMA_INST_ID_MAX - UDMA_INST_ID_START + 1U)
/** @} */

/**
 *  \anchor Udma_SocCfg
 *  \name UDMA SOC Configuration
 *
 *  UDMA Soc Cfg - Flags to indicate the presnce of various SOC specific modules.
 *
 *  @{
 */
/** \brief Flag to indicate LCDMA module is present or not in the SOC*/
#define UDMA_SOC_CFG_LCDMA_PRESENT      (1U)

/** \brief Flag to indicate LCDMA RA is present or not in the SOC*/
#define UDMA_SOC_CFG_RA_LCDMA_PRESENT   (1U)

#define UDMA_SOC_CFG_UDMAP_PRESENT               (0U)

/** \brief Flag to indicate Proxy is present or not in the SOC*/
#define UDMA_SOC_CFG_PROXY_PRESENT               (0U)

/** \brief Flag to indicate Clec is present or not in the SOC*/
#define UDMA_SOC_CFG_CLEC_PRESENT                (0U)

/** \brief Flag to indicate Normal RA is present or not in the SOC*/
#define UDMA_SOC_CFG_RA_NORMAL_PRESENT           (0U)

/** \brief Flag to indicate Ring Monitor is present or not in the SOC*/
#define UDMA_SOC_CFG_RING_MON_PRESENT            (0U)

/** \brief Flag to indicate the SOC needs ring reset workaround */
#define UDMA_SOC_CFG_APPLY_RING_WORKAROUND       (0U)

/** @} */

 /**
 *  \anchor Udma_TxChFdepth
 *  \name UDMA Tx Channels FDEPTH
 *
 *  UDMA Tx Ch Fdepth - Fdepth of various types of channels present in the SOC.
 *
 *  @{
 */
/** \brief Tx Ultra High Capacity Channel FDEPTH*/
#define UDMA_TX_UHC_CHANS_FDEPTH        (0U)
/** \brief Tx High Capacity Channel FDEPTH*/
#define UDMA_TX_HC_CHANS_FDEPTH         (0U)
/** \brief Tx Normal Channel FDEPTH*/
#define UDMA_TX_CHANS_FDEPTH            (192U)
/** @} */

/**
 *  \anchor Udma_RingAccAselEndpointSoc
 *  \name UDMA Ringacc address select (asel) endpoint
 *
 *  List of all valid address select (asel) endpoints in the SOC.
 *
 *  @{
 */
/** \brief Physical address (normal) */
#define UDMA_RINGACC_ASEL_ENDPOINT_PHYSADDR          ((uint32_t) 0U)
/** \brief PCIE0 */
#define UDMA_RINGACC_ASEL_ENDPOINT_PCIE0             ((uint32_t) 1U)
/** \brief ARM ACP port: write-allocate cacheable, bufferable */
#define UDMA_RINGACC_ASEL_ENDPOINT_ACP_WR_ALLOC      ((uint32_t) 14U)
/** \brief ARM ACP port: read-allocate, cacheable, bufferable */
#define UDMA_RINGACC_ASEL_ENDPOINT_ACP_RD_ALLOC      ((uint32_t) 15U)
/** @} */

/** \brief Number of Mapped TX Group */
#define UDMA_NUM_MAPPED_TX_GROUP        (4U)
/**
 *  \anchor Udma_MappedTxGrpSoc
 *  \name Mapped TX Group specific to a SOC
 *
 *  List of all mapped TX groups present in the SOC.
 *
 *  @{
 */
#define UDMA_MAPPED_TX_GROUP_CPSW       (UDMA_MAPPED_GROUP0)
#define UDMA_MAPPED_TX_GROUP_SAUL       (UDMA_MAPPED_GROUP1)
#define UDMA_MAPPED_TX_GROUP_ICSSG_0    (UDMA_MAPPED_GROUP2)
#define UDMA_MAPPED_TX_GROUP_ICSSG_1    (UDMA_MAPPED_GROUP3)
/** @} */

/** \brief Number of Mapped RX Group */
#define UDMA_NUM_MAPPED_RX_GROUP        (4U)
/**
 *  \anchor Udma_MappedRxGrpSoc
 *  \name Mapped RX Group specific to a SOC
 *
 *  List of all mapped RX groups present in the SOC.
 *
 *  @{
 */
#define UDMA_MAPPED_RX_GROUP_CPSW       (UDMA_MAPPED_GROUP4)
#define UDMA_MAPPED_RX_GROUP_SAUL       (UDMA_MAPPED_GROUP5)
#define UDMA_MAPPED_RX_GROUP_ICSSG_0    (UDMA_MAPPED_GROUP6)
#define UDMA_MAPPED_RX_GROUP_ICSSG_1    (UDMA_MAPPED_GROUP7)
/** @} */

/**
 *  \anchor Udma_UtcType
 *  \name UDMA UTC Type
 *
 *  This represents the various types of UTC present in the SOC.
 *
 *  @{
 */
#define UDMA_UTC_TYPE_DRU                                                   (0U)
#define UDMA_UTC_TYPE_DRU_VHWA                                              (1U)
#define UDMA_DEFAULT_UTC_CH_BUS_PRIORITY                                    (4U)
#define UDMA_DEFAULT_UTC_CH_BUS_QOS                                         (4U)
#define UDMA_DEFAULT_UTC_CH_BUS_ORDERID                                     (0U)
#define CSL_NAVSS_UTC_MSMC_DRU_QUEUE_CNT                                    ((uint32_t) 0x0005U)
#define CSL_NAVSS_UTC_VPAC_TC0_QUEUE_CNT                                    ((uint32_t) 0x0005U)

#define CSL_NAVSS_UTC_DMPAC_TC0_QUEUE_CNT                                   ((uint32_t) 0x0005U)
#define CSL_PSILCFG_NAVSS_MAIN_DMPAC_TC0_CC_PSILS_THREAD_CNT                (32U)

#define UDMA_DEFAULT_UTC_CH_DMA_PRIORITY                                    (TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_MEDHIGH)
/** \brief Default DRU queue ID */
#define UDMA_DEFAULT_UTC_DRU_QUEUE_ID                                       (CSL_DRU_QUEUE_ID_3)

#define UDMA_NUM_UTC_INSTANCE               (3U)

/**
 *  \anchor Udma_UtcIdSoc
 *  \name UTC ID specific to a SOC
 *
 *  List of all UTC's present in the SOC.
 *
 *  @{
 */
#define UDMA_UTC_ID_MSMC_DRU0               (UDMA_UTC_ID0)
#define UDMA_UTC_ID_VPAC_TC0                (UDMA_UTC_ID1)
#define UDMA_UTC_ID_DMPAC_TC0               (UDMA_UTC_ID2)
/** @} */
/** @} */

/** \brief External start channel of DRU0 UTC */
#define UDMA_UTC_START_CH_DRU0              (0U)
/** \brief Number of channels present in DRU0 UTC */
#define UDMA_UTC_NUM_CH_DRU0                (32U)
/** \brief Start thread ID of DRU0 UTC */
#define UDMA_UTC_START_THREAD_ID_DRU0       (0U)
/** \brief External start channel of VPAC TC0 UTC */
#define UDMA_UTC_START_CH_VPAC_TC0          (0U)
/** \brief Number of channels present in VPAC TC0 UTC */
#define UDMA_UTC_NUM_CH_VPAC_TC0            (32U)
/** \brief Start thread ID of VPAC TC0 UTC */
#define UDMA_UTC_START_THREAD_ID_VPAC_TC0   (0U)

/** \brief External start channel of DMPAC TC0 UTC */
#define UDMA_UTC_START_CH_DMPAC_TC0         (0U)
/** \brief Number of channels present in DMPAC TC0 UTC */
#define UDMA_UTC_NUM_CH_DMPAC_TC0           (32U)
/** \brief Start thread ID of DMPAC TC0 UTC */
#define UDMA_UTC_START_THREAD_ID_DMPAC_TC0  (CSL_PSILCFG_NAVSS_MAIN_DMPAC_TC0_CC_PSILD_THREAD_OFFSET)

/** \brief DRU0 UTC baseaddress */
#define UDMA_UTC_BASE_DRU0                  (CSL_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_BASE)
#define UDMA_UTC_DMPAC_BASE_DRU0            (CSL_DMPAC0_DMPAC_TOP_CFG_SLV_DRU_UTC_DMPAC0_DRU_MMR_CFG_DRU_DRU_BASE)

/**
 *  \anchor Udma_CoreId
 *  \name Core ID specific to a SOC
 *
 *  List of all cores present in the SOC.
 *
 *  @{
 */
/*
 * Locally used core ID to define default RM configuration.
 * Not to be used by caller
 */
#define UDMA_CORE_ID_MPU1_0             (0U)
#define UDMA_CORE_ID_MCU2_0             (1U)
#define UDMA_CORE_ID_MCU2_1             (2U)
#define UDMA_CORE_ID_MCU1_0             (3U)
#define UDMA_CORE_ID_MCU1_1             (4U)
#define UDMA_CORE_ID_C7X_1              (5U)
#define UDMA_CORE_ID_C7X_2              (6U)
/* Total number of cores */
#define UDMA_NUM_C7X_CORE               (2U)
#define UDMA_NUM_CORE                   (5U)
/** @} */

/**
 *  \anchor Udma_DruSubmitCoreId
 *  \name DRU core ID register to use for direct TR submission.
 *   Each CPU should have a unique submit register to avoid corrupting
 *   submit word when SW is running from multiple CPU at the same time.
 *
 *   Note: Since only 3 submit register set is present, we need to share some
 *   of them across cores. This means that Direct TR from these cores can't
 *   run simultaneously.
 *   In this case C7x and C66x are provided unique ID which are more likely to
 *   use direct TR mode and other cores share the same core ID.
 *
 *  List of all DRU cores ID to use for all the CPUs present in the SOC.
 *
 *  @{
 */
#define UDMA_DRU_CORE_ID_MPU1_0         (CSL_DRU_CORE_ID_2)
#define UDMA_DRU_CORE_ID_MCU2_0         (CSL_DRU_CORE_ID_2)
#define UDMA_DRU_CORE_ID_MCU2_1         (CSL_DRU_CORE_ID_2)
#define UDMA_DRU_CORE_ID_MCU3_0         (CSL_DRU_CORE_ID_2)
#define UDMA_DRU_CORE_ID_MCU3_1         (CSL_DRU_CORE_ID_2)
#define UDMA_DRU_CORE_ID_C7X_1          (CSL_DRU_CORE_ID_0)
#define UDMA_DRU_CORE_ID_C66X_1         (CSL_DRU_CORE_ID_1)
#define UDMA_DRU_CORE_ID_C66X_2         (CSL_DRU_CORE_ID_2)
#define UDMA_DRU_CORE_ID_MCU1_0         (CSL_DRU_CORE_ID_2)
#define UDMA_DRU_CORE_ID_MCU1_1         (CSL_DRU_CORE_ID_2)
/** @} */

/**
 *  \anchor Udma_RmResId
 *  \name UDMA Resources ID
 *
 *  List of all UDMA Resources Id's.
 *
 *  @{
 */
/** \brief Ultra High Capacity Block Copy Channels */
#define UDMA_RM_RES_ID_BC_UHC                   (0U)
/** \brief High Capacity Block Copy Channels */
#define UDMA_RM_RES_ID_BC_HC                    (1U)
/** \brief Normal Capacity Block Copy Channels */
#define UDMA_RM_RES_ID_BC                       (2U)
/** \brief Ultra High Capacity TX Channels */
#define UDMA_RM_RES_ID_TX_UHC                   (3U)
/** \brief High Capacity TX Channels */
#define UDMA_RM_RES_ID_TX_HC                    (4U)
/** \brief Normal Capacity TX Channels */
#define UDMA_RM_RES_ID_TX                       (5U)
/** \brief Ultra High Capacity RX Channels */
#define UDMA_RM_RES_ID_RX_UHC                   (6U)
/** \brief High Capacity RX Channels */
#define UDMA_RM_RES_ID_RX_HC                    (7U)
/** \brief Normal Capacity RX Channels */
#define UDMA_RM_RES_ID_RX                       (8U)
/** \brief Global Event */
#define UDMA_RM_RES_ID_GLOBAL_EVENT             (9U)
/** \brief Virtual Interrupts */
#define UDMA_RM_RES_ID_VINTR                    (10U)
/** \brief [Pktdma Only] Mapped TX Channels for CPSW */
#define UDMA_RM_RES_ID_MAPPED_TX_CPSW           (11U)
/** \brief [Pktdma Only] Mapped TX Channels for SAUL_0 */
#define UDMA_RM_RES_ID_MAPPED_TX_SAUL_0         (12U)
/** \brief [Pktdma Only] Mapped TX Channels for SAUL_1 */
#define UDMA_RM_RES_ID_MAPPED_TX_SAUL_1         (13U)
/** \brief [Pktdma Only] Mapped TX Channels for ICSSG_0 */
#define UDMA_RM_RES_ID_MAPPED_TX_ICSSG_0        (14U)
/** \brief [Pktdma Only] Mapped TX Channels for ICSSG_1 */
#define UDMA_RM_RES_ID_MAPPED_TX_ICSSG_1        (15U)
/** \brief [Pktdma Only] Mapped RX Channels for CPSW */
#define UDMA_RM_RES_ID_MAPPED_RX_CPSW           (16U)
/** \brief [Pktdma Only] Mapped RX Channels for SAUL_0 */
#define UDMA_RM_RES_ID_MAPPED_RX_SAUL_0         (17U)
/** \brief [Pktdma Only] Mapped RX Channels for SAUL_1 */
#define UDMA_RM_RES_ID_MAPPED_RX_SAUL_1         (18U)
/** \brief [Pktdma Only] Mapped RX Channels for SAUL_2 */
#define UDMA_RM_RES_ID_MAPPED_RX_SAUL_2         (19U)
/** \brief [Pktdma Only] Mapped RX Channels for SAUL_3 */
#define UDMA_RM_RES_ID_MAPPED_RX_SAUL_3         (20U)
/** \brief [Pktdma Only] Mapped RX Channels for ICSSG_0 */
#define UDMA_RM_RES_ID_MAPPED_RX_ICSSG_0        (21U)
/** \brief [Pktdma Only] Mapped RX Channels for ICSSG_1 */
#define UDMA_RM_RES_ID_MAPPED_RX_ICSSG_1        (22U)
/** \brief [Pktdma Only] Mapped TX Rings for CPSW */
#define UDMA_RM_RES_ID_MAPPED_TX_RING_CPSW      (23U)
/** \brief [Pktdma Only] Mapped TX Rings for SAUL_0 */
#define UDMA_RM_RES_ID_MAPPED_TX_RING_SAUL_0    (24U)
/** \brief [Pktdma Only] Mapped TX Rings for SAUL_1 */
#define UDMA_RM_RES_ID_MAPPED_TX_RING_SAUL_1    (25U)
/** \brief [Pktdma Only] Mapped TX Rings for ICSSG_0 */
#define UDMA_RM_RES_ID_MAPPED_TX_RING_ICSSG_0   (26U)
/** \brief [Pktdma Only] Mapped TX Rings for ICSSG_1 */
#define UDMA_RM_RES_ID_MAPPED_TX_RING_ICSSG_1   (27U)
/** \brief [Pktdma Only] Mapped RX Rings for CPSW */
#define UDMA_RM_RES_ID_MAPPED_RX_RING_CPSW      (28U)
/** \brief [Pktdma Only] Mapped RX Rings for SAUL_0 */
#define UDMA_RM_RES_ID_MAPPED_RX_RING_SAUL_0    (29U)
/** \brief [Pktdma Only] Mapped RX Rings for SAUL_1 */
#define UDMA_RM_RES_ID_MAPPED_RX_RING_SAUL_1    (30U)
/** \brief [Pktdma Only] Mapped RX Rings for SAUL_2 */
#define UDMA_RM_RES_ID_MAPPED_RX_RING_SAUL_2    (31U)
/** \brief [Pktdma Only] Mapped RX Rings for SAUL_3 */
#define UDMA_RM_RES_ID_MAPPED_RX_RING_SAUL_3    (32U)
/** \brief [Pktdma Only] Mapped RX Rings for ICSSG_0 */
#define UDMA_RM_RES_ID_MAPPED_RX_RING_ICSSG_0   (33U)
/** \brief [Pktdma Only] Mapped RX Rings for ICSSG_1 */
#define UDMA_RM_RES_ID_MAPPED_RX_RING_ICSSG_1   (34U)
/** \brief Total number of BCDMA resources */
#define UDMA_RM_NUM_BCDMA_RES                   (11U)
/** \brief Total number of PKTDMA resources */
#define UDMA_RM_NUM_PKTDMA_RES                  (35U)
/** \brief Total number of resources */
#define UDMA_RM_NUM_RES                         (35U)
/** @} */

/** \brief Total number of shared resources -
 *  Global_Event/IR Intr */
#define UDMA_RM_NUM_SHARED_RES                  (2U)
/** \brief Maximum no.of instances to split a shared resource.
 *  This should be max(UDMA_NUM_CORE,UDMA_NUM_INST_ID) */
#define UDMA_RM_SHARED_RES_MAX_INST             (UDMA_NUM_CORE)

/** \brief Destination thread offset */
#define UDMA_PSIL_DEST_THREAD_OFFSET    (0x8000U)

/**
 *  \anchor Udma_PsilCh
 *  \name PSIL Channels
 *
 *  List of all PSIL channels and the corresponding counts
 *
 *  @{
 */

#define UDMA_PSIL_CH_CPSW2_RX           (CSL_PSILCFG_DMSS_CPSW2_PSILS_THREAD_OFFSET)
#define UDMA_PSIL_CH_SAUL0_RX           (CSL_PSILCFG_DMSS_SAUL0_PSILS_THREAD_OFFSET)
#define UDMA_PSIL_CH_CSI_RX             (CSL_PSILCFG_DMSS_CSI_PSILS_THREAD_OFFSET)

#define UDMA_PSIL_CH_CPSW2_TX           (UDMA_PSIL_CH_CPSW2_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PSIL_CH_SAUL0_TX           (UDMA_PSIL_CH_SAUL0_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PSIL_CH_CSI_TX             (CSL_PSILCFG_DMSS_CSI_PSILD_THREAD_OFFSET)

#define UDMA_PSIL_CH_CPSW2_TX_CNT       (CSL_PSILCFG_DMSS_CPSW2_PSILD_THREAD_CNT)
#define UDMA_PSIL_CH_SAUL0_TX_CNT       (CSL_PSILCFG_DMSS_SAUL0_PSILD_THREAD_CNT)
#define UDMA_PSIL_CH_CSI_TX_CNT         (CSL_PSILCFG_DMSS_CSI_PSILD_THREAD_CNT)

#define UDMA_PSIL_CH_CPSW2_RX_CNT       (CSL_PSILCFG_DMSS_CPSW2_PSILS_THREAD_CNT)
#define UDMA_PSIL_CH_SAUL0_RX_CNT       (CSL_PSILCFG_DMSS_SAUL0_PSILS_THREAD_CNT)
#define UDMA_PSIL_CH_CSI_RX_CNT         (CSL_PSILCFG_DMSS_CSI_PSILS_THREAD_CNT)

/** @} */


/**
 *  \anchor Udma_PdmaCh
 *  \name PDMA Channels
 *
 *  List of all PDMA channels across dmss domain
 *
 *  @{
 */

/**
 *  \anchor Udma_PdmaChMain0Rx
 *  \name Main0 RX PDMA Channels
 *
 *  List of all Main0 PDMA RX channels
 *
 *  @{
 */

/*
 * PDMA MAIN0 MCSPI RX Channels
 */
#define UDMA_PDMA_CH_MAIN0_MCSPI0_CH0_RX    (CSL_PDMA_CH_MCSPI0_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI0_CH1_RX    (CSL_PDMA_CH_MCSPI0_CH1_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI0_CH2_RX    (CSL_PDMA_CH_MCSPI0_CH2_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI0_CH3_RX    (CSL_PDMA_CH_MCSPI0_CH3_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI1_CH0_RX    (CSL_PDMA_CH_MCSPI1_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI1_CH1_RX    (CSL_PDMA_CH_MCSPI1_CH1_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI1_CH2_RX    (CSL_PDMA_CH_MCSPI1_CH2_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI1_CH3_RX    (CSL_PDMA_CH_MCSPI1_CH3_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI2_CH0_RX    (CSL_PDMA_CH_MCSPI2_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI2_CH1_RX    (CSL_PDMA_CH_MCSPI2_CH1_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI2_CH2_RX    (CSL_PDMA_CH_MCSPI2_CH2_RX)
#define UDMA_PDMA_CH_MAIN0_MCSPI2_CH3_RX    (CSL_PDMA_CH_MCSPI2_CH3_RX)
/*
 * PDMA MAIN0 UART RX Channels
 */
#define UDMA_PDMA_CH_MAIN0_UART0_RX         (CSL_PDMA_CH_UART0_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_UART1_RX         (CSL_PDMA_CH_UART1_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_UART2_RX         (CSL_PDMA_CH_UART2_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_UART3_RX         (CSL_PDMA_CH_UART3_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_UART4_RX         (CSL_PDMA_CH_UART4_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_UART5_RX         (CSL_PDMA_CH_UART5_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_UART6_RX         (CSL_PDMA_CH_UART6_CH0_RX)

/*
 * PDMA MAIN0 MCASP RX Channels
 */
#define UDMA_PDMA_CH_MAIN0_MCASP0_RX        (CSL_PDMA_CH_MCASP0_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_MCASP1_RX        (CSL_PDMA_CH_MCASP1_CH0_RX)
#define UDMA_PDMA_CH_MAIN0_MCASP2_RX        (CSL_PDMA_CH_MCASP2_CH0_RX)

/** @} */

/**
 *  \anchor Udma_PdmaChMain0Tx
 *  \name Main0 TX PDMA Channels
 *
 *  List of all Main0 PDMA TX channels
 *
 *  @{
 */

/*
 * PDMA MAIN0 MCSPI TX Channels
 */
#define UDMA_PDMA_CH_MAIN0_MCSPI0_CH0_TX    (UDMA_PDMA_CH_MAIN0_MCSPI0_CH0_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI0_CH1_TX    (UDMA_PDMA_CH_MAIN0_MCSPI0_CH1_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI0_CH2_TX    (UDMA_PDMA_CH_MAIN0_MCSPI0_CH2_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI0_CH3_TX    (UDMA_PDMA_CH_MAIN0_MCSPI0_CH3_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI1_CH0_TX    (UDMA_PDMA_CH_MAIN0_MCSPI1_CH0_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI1_CH1_TX    (UDMA_PDMA_CH_MAIN0_MCSPI1_CH1_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI1_CH2_TX    (UDMA_PDMA_CH_MAIN0_MCSPI1_CH2_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI1_CH3_TX    (UDMA_PDMA_CH_MAIN0_MCSPI1_CH3_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI2_CH0_TX    (UDMA_PDMA_CH_MAIN0_MCSPI2_CH0_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI2_CH1_TX    (UDMA_PDMA_CH_MAIN0_MCSPI2_CH1_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI2_CH2_TX    (UDMA_PDMA_CH_MAIN0_MCSPI2_CH2_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCSPI2_CH3_TX    (UDMA_PDMA_CH_MAIN0_MCSPI2_CH3_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
/*
 * PDMA MAIN0 UART TX Channels
 */
#define UDMA_PDMA_CH_MAIN0_UART0_TX         (UDMA_PDMA_CH_MAIN0_UART0_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_UART1_TX         (UDMA_PDMA_CH_MAIN0_UART1_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_UART2_TX         (UDMA_PDMA_CH_MAIN0_UART2_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_UART3_TX         (UDMA_PDMA_CH_MAIN0_UART3_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_UART4_TX         (UDMA_PDMA_CH_MAIN0_UART4_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_UART5_TX         (UDMA_PDMA_CH_MAIN0_UART5_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_UART6_TX         (UDMA_PDMA_CH_MAIN0_UART6_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
/*
 * PDMA MAIN0 MCASP TX Channels
 */
#define UDMA_PDMA_CH_MAIN0_MCASP0_TX        (UDMA_PDMA_CH_MAIN0_MCASP0_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCASP1_TX        (UDMA_PDMA_CH_MAIN0_MCASP1_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
#define UDMA_PDMA_CH_MAIN0_MCASP2_TX        (UDMA_PDMA_CH_MAIN0_MCASP2_RX | UDMA_PSIL_DEST_THREAD_OFFSET)
/** @} */

/* Channel information for local DRU channels */
/** \brief Start channel of DRU UTC */
#define UDMA_UTC_START_CH_DRU              (0U)
/** \brief Number of channels present in DRU UTC */
#define UDMA_UTC_NUM_CH_DRU                (32U)

/* Start of C7x events associated to CLEC that UDMA Driver will manage */
#define UDMA_C7X_CORE_INTR_OFFSET               (32U)
/* Number of C7x Events available for UDMA */
#define UDMA_C7X_CORE_NUM_INTR                  (16)

/* CLEC offset for VINT */
#define UDMA_VINT_CLEC_OFFSET                   (192)

/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Returns TRUE if the memory is cache coherent
 *
 *  \return TRUE/FALSE
 */
uint32_t Udma_isCacheCoherent(void);

/**
 *  \brief Returns the core ID
 *
 *  \return Core ID \ref Udma_CoreId
 */
uint32_t Udma_getCoreId(void);

/**
 *  \brief Returns TRUE if the given UDMA Instance ID is valid for this
 *         SoC
 *
 *  \return TRUE/TRUE
 */
uint8_t Udma_isValidInstance(uint32_t instId);

/**
 *  \brief Updates DRU Registers
 */
void inline Udma_updateDruRegs(uint32_t instId, void *pDruNrt, void *pDruRt);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef UDMA_SOC_H_ */

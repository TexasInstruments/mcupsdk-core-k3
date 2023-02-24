/*
 *  Copyright (c) 2020-2021 Texas Instruments Incorporated
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
 */

#ifndef CSLR_DMSS_DEFINES_H_
#define CSLR_DMSS_DEFINES_H_

/**
 *  \anchor CSL_Dmss
 *  \name Configuration parameters for dmss
 *
 *  List of configuration parameters for dmss
 *
 *  @{
 */

/**
 *  \anchor CSL_DmssBcdma
 *  \name DMSS BCDMA (Block Copy DMA) configuration parameters
 *
 *  List of bcdma module configuration parameters for dmss
 *
 *  @{
 */
#define CSL_DMSS_BCDMA_NUM_BC_CHANS                                     ((uint32_t) 32U)    /* Number of block-copy channels */
#define CSL_DMSS_BCDMA_NUM_TX_CHANS                                     ((uint32_t) 22U)    /* Number of split-tx channels (includes HC and UC channel counts) */
#define CSL_DMSS_BCDMA_NUM_RX_CHANS                                     ((uint32_t) 28U)    /* Number of split-rx channels (includes HC and UC channel counts) */
#define CSL_DMSS_BCDMA_NUM_TX_HC_CHANS                                  ((uint32_t) 0U)     /* Number of split-tx high capacity (HC) channels (includes UC channel count) */
#define CSL_DMSS_BCDMA_NUM_RX_HC_CHANS                                  ((uint32_t) 6U)     /* Number of split-rx high capacity (HC) channels (includes UC channel count) */
#define CSL_DMSS_BCDMA_NUM_TX_UC_CHANS                                  ((uint32_t) 0U)     /* Number of split-tx ultra high capacity (UC) channels */
#define CSL_DMSS_BCDMA_NUM_RX_UC_CHANS                                  ((uint32_t) 0U)     /* Number of split-rx ultra high capacity (UC) channels */
#define CSL_DMSS_BCDMA_NUM_EXT_CHANS                                    ((uint32_t) 0U)
#define CSL_DMSS_BCDMA_NUM_SECURE_CHANS                                 ((uint32_t) 0U)

#define CSL_DMSS_BCDMA_NUM_RX_FLOWS                                     (CSL_DMSS_BCDMA_NUM_BC_CHANS+CSL_DMSS_BCDMA_NUM_TX_CHANS+CSL_DMSS_BCDMA_NUM_RX_CHANS)    /* 0-31: block-copy channels, 32-53: split-tx channels, 54-81: split-rx channels */
#define CSL_DMSS_BCDMA_RX_FLOWS_BC_CHANS_START                          ((uint32_t) 0U)
#define CSL_DMSS_BCDMA_RX_FLOWS_BC_CHANS_CNT                            (CSL_DMSS_BCDMA_NUM_BC_CHANS)
#define CSL_DMSS_BCDMA_RX_FLOWS_TX_CHANS_START                          (CSL_DMSS_BCDMA_NUM_BC_CHANS)
#define CSL_DMSS_BCDMA_RX_FLOWS_TX_CHANS_CNT                            (CSL_DMSS_BCDMA_NUM_TX_CHANS)
#define CSL_DMSS_BCDMA_RX_FLOWS_RX_CHANS_START                          (CSL_DMSS_BCDMA_NUM_BC_CHANS+CSL_DMSS_BCDMA_NUM_TX_CHANS)
#define CSL_DMSS_BCDMA_RX_FLOWS_RX_CHANS_CNT                            (CSL_DMSS_BCDMA_NUM_RX_CHANS)

#define CSL_DMSS_UDMAP_TX_CHANS_FDEPTH                                  ((uint32_t) 192U)
#define CSL_DMSS_UDMAP_TX_HC_CHANS_FDEPTH                               ((uint32_t) 0U)
#define CSL_DMSS_UDMAP_TX_UHC_CHANS_FDEPTH                              ((uint32_t) 0U)
/* @} */

/**
 *  \anchor CSL_DmssPktdma
 *  \name DMSS PKTDMA (Packet DMA) configuration parameters
 *
 *  List of pktdma module configuration parameters for dmss
 *
 *  @{
 */
#define CSL_DMSS_PKTDMA_NUM_TX_CHANS                                    ((uint32_t) 29U)    /* Number of tx channels */
#define CSL_DMSS_PKTDMA_NUM_RX_CHANS                                    ((uint32_t) 24U)    /* Number of rx channels */
#define CSL_DMSS_PKTDMA_NUM_TX_HC_CHANS                                 ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_RX_HC_CHANS                                 ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_TX_UC_CHANS                                 ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_RX_UC_CHANS                                 ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_EXT_CHANS                                   ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_SECURE_CHANS                                ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_RX_FLOWS                                    ((uint32_t) 51U)
#define CSL_DMSS_PKTDMA_NUM_TX_FLOWS                                    ((uint32_t) 99U)

#define CSL_DMSS_PKTDMA_TX_CHANS_FDEPTH                                 ((uint32_t) 192U)
#define CSL_DMSS_PKTDMA_TX_HC_CHANS_FDEPTH                              ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_TX_UHC_CHANS_FDEPTH                             ((uint32_t) 0U)

#define CSL_DMSS_PKTDMA_TX_CHANS_UNMAPPED_START                         ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_TX_CHANS_UNMAPPED_CNT                           ((uint32_t) 19U)
#define CSL_DMSS_PKTDMA_TX_CHANS_CPSW_START                             ((uint32_t) 19U)
#define CSL_DMSS_PKTDMA_TX_CHANS_CPSW_CNT                               ((uint32_t) 8U)
#define CSL_DMSS_PKTDMA_TX_CHANS_SAUL0_START                            ((uint32_t) 27U)
#define CSL_DMSS_PKTDMA_TX_CHANS_SAUL0_CNT                              ((uint32_t) 1U)
#define CSL_DMSS_PKTDMA_TX_CHANS_SAUL1_START                            ((uint32_t) 28U)
#define CSL_DMSS_PKTDMA_TX_CHANS_SAUL1_CNT                              ((uint32_t) 1U)

#define CSL_DMSS_PKTDMA_RX_CHANS_UNMAPPED_START                         ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_RX_CHANS_UNMAPPED_CNT                           ((uint32_t) 19U)
#define CSL_DMSS_PKTDMA_RX_CHANS_CPSW_START                             ((uint32_t) 19U)
#define CSL_DMSS_PKTDMA_RX_CHANS_CPSW_CNT                               ((uint32_t) 1U)
#define CSL_DMSS_PKTDMA_RX_CHANS_SAUL0_START                            ((uint32_t) 20U)
#define CSL_DMSS_PKTDMA_RX_CHANS_SAUL0_CNT                              ((uint32_t) 1U)
#define CSL_DMSS_PKTDMA_RX_CHANS_SAUL1_START                            ((uint32_t) 21U)
#define CSL_DMSS_PKTDMA_RX_CHANS_SAUL1_CNT                              ((uint32_t) 1U)
#define CSL_DMSS_PKTDMA_RX_CHANS_SAUL2_START                            ((uint32_t) 22U)
#define CSL_DMSS_PKTDMA_RX_CHANS_SAUL2_CNT                              ((uint32_t) 1U)
#define CSL_DMSS_PKTDMA_RX_CHANS_SAUL3_START                            ((uint32_t) 23U)
#define CSL_DMSS_PKTDMA_RX_CHANS_SAUL3_CNT                              ((uint32_t) 1U)

#define CSL_DMSS_PKTDMA_TX_FLOWS_UNMAPPED_START                         ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_UNMAPPED_CNT                           ((uint32_t) 19U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_CPSW_START                             ((uint32_t) 19U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_CPSW_CNT                               ((uint32_t) 64U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_SAUL0_START                            ((uint32_t) 83U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_SAUL0_CNT                              ((uint32_t) 8U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_SAUL1_START                            ((uint32_t) 91U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_SAUL1_CNT                              ((uint32_t) 8U)

#define CSL_DMSS_PKTDMA_RX_FLOWS_UNMAPPED_START                         ((uint32_t) 99U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_UNMAPPED_CNT                           ((uint32_t) 19U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_CPSW_START                             ((uint32_t) 118U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_CPSW_CNT                               ((uint32_t) 16U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_SAUL0_START                            ((uint32_t) 134U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_SAUL0_CNT                              ((uint32_t) 8U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_SAUL1_START                            ((uint32_t) 134U)   /* SAUL1 RX flows are shared with SAUL0 */
#define CSL_DMSS_PKTDMA_RX_FLOWS_SAUL1_CNT                              ((uint32_t) 8U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_SAUL2_START                            ((uint32_t) 142U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_SAUL2_CNT                              ((uint32_t) 8U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_SAUL3_START                            ((uint32_t) 142U)   /* SAUL3 RX flows are shared with SAUL2 */
#define CSL_DMSS_PKTDMA_RX_FLOWS_SAUL3_CNT                              ((uint32_t) 8U)

/* @} */

/**
 *  \anchor CSL_DmssSecProxy
 *  \name Secure Proxy configuration parameters
 *
 *  List of Secure Proxy module configuration parameters for dmss
 *
 *  @{
 */
#define CSL_DMSS_SEC_PROXY_NUM_PROXIES                                  ((uint32_t) 76U)
#define CSL_DMSS_SEC_PROXY_MSG_SIZE_BYTES                               ((uint32_t) 64)
#define CSL_DMSS_SEC_PROXY_NUM_TARGETS                                  ((uint32_t) 1U)
#define CSL_DMSS_SEC_PROXY_TARGET_RINGACC0_ADDR                         ((uintptr_t) 0x00004E000000U)
#define CSL_DMSS_SEC_PROXY_TARGET_RINGACC0_NUM_CHANNELS                 ((uint32_t) 20U)
#define CSL_DMSS_SEC_PROXY_TARGET_RINGACC0_NUM_CHANNEL_SIZE_BYTES       ((uint32_t) 4096U)

/* @} */

/**
 *  \anchor CSL_DmssRingacc
 *  \name Ring Accelerator configuration parameters
 *
 *  List of Ring Accelerator module configuration parameters for dmss
 *
 *  @{
 */
#define CSL_DMSS_RINGACC_RING_CNT                                       ((uint32_t) 20U)
#define CSL_DMSS_RINGACC_NUM_MONITORS                                   ((uint32_t) 0U)
#define CSL_DMSS_RINGACC_IS_TRACE_SUPPORTED                             ((uint32_t) 1U)

/* @} */

/**
 *  \anchor CSL_DmssGlobalEventMap
 *  \name DMSS Global Event map
 *
 *  List of global event offsets
 *
 *  @{
 */
#define CSL_DMSS_GEM_INTA0_SEVI_OFFSET                                  ((uint32_t) 0x0000U)
#define CSL_DMSS_GEM_INTA0_MEVI_OFFSET                                  ((uint32_t) 0x2000U)
#define CSL_DMSS_GEM_INTA0_GEVI_OFFSET                                  ((uint32_t) 0x2800U)
#define CSL_DMSS_GEM_DMSC_INTA_SEVI_OFFSET                              ((uint32_t) 0x4800U)
#define CSL_DMSS_GEM_INTA0_LEVI_OFFSET                                  ((uint32_t) 0x8000U)
#define CSL_DMSS_GEM_PDMA_MAIN0_LEVI_OFFSET                             ((uint32_t) 0xA400U)
#define CSL_DMSS_GEM_PDMA_MAIN1_LEVI_OFFSET                             ((uint32_t) 0xA480U)
#define CSL_DMSS_GEM_BCDMA_TRIGGER_OFFSET                               ((uint32_t) 0xC400U)
/* @} */

/**
 *  \anchor CSL_DmssUtc
 *  \name UTC configuration parameters
 *
 *  List of UTC module configuration parameters
 *
 *  @{
 */
#define CSL_DMSS_UTC_CNT                                                (0x0000U)
#define CSL_DMSS_UTC_MSMC_DRU_QUEUE_CNT                                 ((uint32_t) 0x0000U)
#define CSL_DMSS_UTC_VPAC_TC0_QUEUE_CNT                                 ((uint32_t) 0x0000U)
#define CSL_DMSS_UTC_VPAC_TC1_QUEUE_CNT                                 ((uint32_t) 0x0000U)
#define CSL_DMSS_UTC_DMPAC_QUEUE_CNT                                    ((uint32_t) 0x0000U)
/* @} */

/* @} */

#endif

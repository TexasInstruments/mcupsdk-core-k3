/*
 *  Copyright (c) 2025 Texas Instruments Incorporated
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
#define CSL_DMSS_BCDMA_NUM_BC_CHANS                                     ((uint32_t) 16U)    /* Number of block-copy channels */
#define CSL_DMSS_BCDMA_NUM_TX_CHANS                                     ((uint32_t) 26U)    /* Number of split-tx channels (includes HC and UC channel counts) */
#define CSL_DMSS_BCDMA_NUM_RX_CHANS                                     ((uint32_t) 26U)    /* Number of split-rx channels (includes HC and UC channel counts) */
#define CSL_DMSS_BCDMA_NUM_TX_HC_CHANS                                  ((uint32_t) 0U)     /* Number of split-tx high capacity (HC) channels (includes UC channel count) */
#define CSL_DMSS_BCDMA_NUM_RX_HC_CHANS                                  ((uint32_t) 0U)     /* Number of split-rx high capacity (HC) channels (includes UC channel count) */
#define CSL_DMSS_BCDMA_NUM_TX_UC_CHANS                                  ((uint32_t) 0U)     /* Number of split-tx ultra high capacity (UC) channels */
#define CSL_DMSS_BCDMA_NUM_RX_UC_CHANS                                  ((uint32_t) 0U)     /* Number of split-rx ultra high capacity (UC) channels */
#define CSL_DMSS_BCDMA_NUM_EXT_CHANS                                    ((uint32_t) 0U)
#define CSL_DMSS_BCDMA_NUM_SECURE_CHANS                                 ((uint32_t) 0U)
#define CSL_DMSS_BCDMA_MAX_NUM_RINGS                                    ((uint32_t) 158U)        

#define CSL_DMSS_BCDMA_NUM_RX_FLOWS                                     (0U)    /* 0-31: block-copy channels, 32-53: split-tx channels, 54-81: split-rx channels */
#define CSL_DMSS_BCDMA_RX_FLOWS_BC_CHANS_START                          ((uint32_t) 128U)
#define CSL_DMSS_BCDMA_RX_FLOWS_BC_CHANS_CNT                            (CSL_DMSS_BCDMA_NUM_BC_CHANS)
#define CSL_DMSS_BCDMA_RX_FLOWS_TX_CHANS_START                          (1U)
#define CSL_DMSS_BCDMA_RX_FLOWS_TX_CHANS_CNT                            (CSL_DMSS_BCDMA_NUM_TX_CHANS)
#define CSL_DMSS_BCDMA_RX_FLOWS_RX_CHANS_START                          (0U)
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
#define CSL_DMSS_PKTDMA_NUM_TX_CHANS                                    ((uint32_t) 31U)    /* Number of tx channels */
#define CSL_DMSS_PKTDMA_NUM_RX_CHANS                                    ((uint32_t) 24U)    /* Number of rx channels */
#define CSL_DMSS_PKTDMA_NUM_TX_HC_CHANS                                 ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_RX_HC_CHANS                                 ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_TX_UC_CHANS                                 ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_RX_UC_CHANS                                 ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_EXT_CHANS                                   ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_SECURE_CHANS                                ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_NUM_RX_FLOWS                                    ((uint32_t) 39U)
#define CSL_DMSS_PKTDMA_NUM_TX_FLOWS                                    ((uint32_t) 39U)
#define CSL_DMSS_PKTDMA_MAX_NUM_RINGS                                   ((uint32_t) 112U)  

#define CSL_DMSS_PKTDMA_TX_CHANS_FDEPTH                                 ((uint32_t) 192U)
#define CSL_DMSS_PKTDMA_TX_HC_CHANS_FDEPTH                              ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_TX_UHC_CHANS_FDEPTH                             ((uint32_t) 0U)

#define CSL_DMSS_PKTDMA_TX_CHANS_UNMAPPED_START                         ((uint32_t) 1U)
#define CSL_DMSS_PKTDMA_TX_CHANS_UNMAPPED_CNT                           ((uint32_t) 8U)
#define CSL_DMSS_PKTDMA_TX_CHANS_CPSW_START                             ((uint32_t) 64U)
#define CSL_DMSS_PKTDMA_TX_CHANS_CPSW_CNT                               ((uint32_t) 8U)

#define CSL_DMSS_PKTDMA_RX_CHANS_UNMAPPED_START                         ((uint32_t) 0U)
#define CSL_DMSS_PKTDMA_RX_CHANS_UNMAPPED_CNT                           ((uint32_t) 1U)
#define CSL_DMSS_PKTDMA_RX_CHANS_CPSW_START                             ((uint32_t) 96U)
#define CSL_DMSS_PKTDMA_RX_CHANS_CPSW_CNT                               ((uint32_t) 1U)


#define CSL_DMSS_PKTDMA_TX_FLOWS_UNMAPPED_START                         ((uint32_t) 64U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_UNMAPPED_CNT                           ((uint32_t) 16U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_CPSW_START                             ((uint32_t) 64U)
#define CSL_DMSS_PKTDMA_TX_FLOWS_CPSW_CNT                               ((uint32_t) 16U)

#define CSL_DMSS_PKTDMA_RX_FLOWS_UNMAPPED_START                         ((uint32_t) 96U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_UNMAPPED_CNT                           ((uint32_t) 16U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_CPSW_START                             ((uint32_t) 96U)
#define CSL_DMSS_PKTDMA_RX_FLOWS_CPSW_CNT                               ((uint32_t) 16U)


#endif

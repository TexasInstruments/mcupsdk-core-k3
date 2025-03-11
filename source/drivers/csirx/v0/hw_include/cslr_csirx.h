/********************************************************************
 * Copyright (C) 2018-25 Texas Instruments Incorporated.
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
 *  Name        : cslr_csirx.h
*/
#ifndef CSLR_CSIRX_H_
#define CSLR_CSIRX_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : CSI2RX MMRs  CSI2RX is the core module of CSI_RX_IF
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t DEVICE_CONFIG;
    volatile uint32_t SOFT_RESET;
    volatile uint32_t STATIC_CFG;
    volatile uint8_t  Resv_16[4];
    volatile uint32_t ERROR_BYPASS_CFG;
    volatile uint8_t  Resv_24[4];
    volatile uint32_t MONITOR_IRQS;
    volatile uint32_t MONITOR_IRQS_MASK_CFG;
    volatile uint32_t INFO_IRQS;
    volatile uint32_t INFO_IRQS_MASK_CFG;
    volatile uint32_t ERROR_IRQS;
    volatile uint32_t ERROR_IRQS_MASK_CFG;
    volatile uint8_t  Resv_64[16];
    volatile uint32_t DPHY_LANE_CONTROL;
    volatile uint8_t  Resv_72[4];
    volatile uint32_t DPHY_STATUS;
    volatile uint32_t DPHY_ERR_STATUS_IRQ;
    volatile uint32_t DPHY_ERR_IRQ_MASK_CFG;
    volatile uint8_t  Resv_96[12];
    volatile uint32_t INTEGRATION_DEBUG;
    volatile uint8_t  Resv_116[16];
    volatile uint32_t ERROR_DEBUG;
    volatile uint8_t  Resv_128[8];
    volatile uint32_t TEST_GENERIC;
    volatile uint8_t  Resv_256[124];
    volatile uint32_t STREAM0_CTRL;
    volatile uint32_t STREAM0_STATUS;
    volatile uint32_t STREAM0_DATA_CFG;
    volatile uint32_t STREAM0_CFG;
    volatile uint32_t STREAM0_MONITOR_CTRL;
    volatile uint32_t STREAM0_MONITOR_FRAME;
    volatile uint32_t STREAM0_MONITOR_LB;
    volatile uint32_t STREAM0_TIMER;
    volatile uint32_t STREAM0_FCC_CFG;
    volatile uint32_t STREAM0_FCC_CTRL;
    volatile uint32_t STREAM0_FIFO_FILL_LVL;
    volatile uint8_t  Resv_512[212];
    volatile uint32_t STREAM1_CTRL;
    volatile uint32_t STREAM1_STATUS;
    volatile uint32_t STREAM1_DATA_CFG;
    volatile uint32_t STREAM1_CFG;
    volatile uint32_t STREAM1_MONITOR_CTRL;
    volatile uint32_t STREAM1_MONITOR_FRAME;
    volatile uint32_t STREAM1_MONITOR_LB;
    volatile uint32_t STREAM1_TIMER;
    volatile uint32_t STREAM1_FCC_CFG;
    volatile uint32_t STREAM1_FCC_CTRL;
    volatile uint32_t STREAM1_FIFO_FILL_LVL;
    volatile uint8_t  Resv_768[212];
    volatile uint32_t STREAM2_CTRL;
    volatile uint32_t STREAM2_STATUS;
    volatile uint32_t STREAM2_DATA_CFG;
    volatile uint32_t STREAM2_CFG;
    volatile uint32_t STREAM2_MONITOR_CTRL;
    volatile uint32_t STREAM2_MONITOR_FRAME;
    volatile uint32_t STREAM2_MONITOR_LB;
    volatile uint32_t STREAM2_TIMER;
    volatile uint32_t STREAM2_FCC_CFG;
    volatile uint32_t STREAM2_FCC_CTRL;
    volatile uint32_t STREAM2_FIFO_FILL_LVL;
    volatile uint8_t  Resv_1024[212];
    volatile uint32_t STREAM3_CTRL;
    volatile uint32_t STREAM3_STATUS;
    volatile uint32_t STREAM3_DATA_CFG;
    volatile uint32_t STREAM3_CFG;
    volatile uint32_t STREAM3_MONITOR_CTRL;
    volatile uint32_t STREAM3_MONITOR_FRAME;
    volatile uint32_t STREAM3_MONITOR_LB;
    volatile uint32_t STREAM3_TIMER;
    volatile uint32_t STREAM3_FCC_CFG;
    volatile uint32_t STREAM3_FCC_CTRL;
    volatile uint32_t STREAM3_FIFO_FILL_LVL;
    volatile uint8_t  Resv_2304[1236];
    volatile uint32_t ASF_INT_STATUS;
    volatile uint32_t ASF_INT_RAW_STATUS;
    volatile uint32_t ASF_INT_MASK;
    volatile uint32_t ASF_INT_TEST;
    volatile uint32_t ASF_FATAL_NONFATAL_SELECT;
    volatile uint8_t  Resv_2336[12];
    volatile uint32_t ASF_SRAM_CORR_FAULT_STATUS;
    volatile uint32_t ASF_SRAM_UNCORR_FAULT_STATUS;
    volatile uint32_t ASF_SRAM_FAULT_STATS;
    volatile uint8_t  Resv_2352[4];
    volatile uint32_t ASF_TRANS_TO_CTRL;
    volatile uint32_t ASF_TRANS_TO_FAULT_MASK;
    volatile uint32_t ASF_TRANS_TO_FAULT_STATUS;
    volatile uint8_t  Resv_2368[4];
    volatile uint32_t ASF_PROTOCOL_FAULT_MASK;
    volatile uint32_t ASF_PROTOCOL_FAULT_STATUS;
    volatile uint8_t  Resv_4092[1716];
    volatile uint32_t ID_PROD_VER;
} CSL_csirxRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CSIRX_DEVICE_CONFIG                                                (0x00000000U)
#define CSL_CSIRX_SOFT_RESET                                                   (0x00000004U)
#define CSL_CSIRX_STATIC_CFG                                                   (0x00000008U)
#define CSL_CSIRX_ERROR_BYPASS_CFG                                             (0x00000010U)
#define CSL_CSIRX_MONITOR_IRQS                                                 (0x00000018U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG                                        (0x0000001CU)
#define CSL_CSIRX_INFO_IRQS                                                    (0x00000020U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG                                           (0x00000024U)
#define CSL_CSIRX_ERROR_IRQS                                                   (0x00000028U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG                                          (0x0000002CU)
#define CSL_CSIRX_DPHY_LANE_CONTROL                                            (0x00000040U)
#define CSL_CSIRX_DPHY_STATUS                                                  (0x00000048U)
#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ                                          (0x0000004CU)
#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG                                        (0x00000050U)
#define CSL_CSIRX_INTEGRATION_DEBUG                                            (0x00000060U)
#define CSL_CSIRX_ERROR_DEBUG                                                  (0x00000074U)
#define CSL_CSIRX_TEST_GENERIC                                                 (0x00000080U)
#define CSL_CSIRX_STREAM0_CTRL                                                 (0x00000100U)
#define CSL_CSIRX_STREAM0_STATUS                                               (0x00000104U)
#define CSL_CSIRX_STREAM0_DATA_CFG                                             (0x00000108U)
#define CSL_CSIRX_STREAM0_CFG                                                  (0x0000010CU)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL                                         (0x00000110U)
#define CSL_CSIRX_STREAM0_MONITOR_FRAME                                        (0x00000114U)
#define CSL_CSIRX_STREAM0_MONITOR_LB                                           (0x00000118U)
#define CSL_CSIRX_STREAM0_TIMER                                                (0x0000011CU)
#define CSL_CSIRX_STREAM0_FCC_CFG                                              (0x00000120U)
#define CSL_CSIRX_STREAM0_FCC_CTRL                                             (0x00000124U)
#define CSL_CSIRX_STREAM0_FIFO_FILL_LVL                                        (0x00000128U)
#define CSL_CSIRX_STREAM1_CTRL                                                 (0x00000200U)
#define CSL_CSIRX_STREAM1_STATUS                                               (0x00000204U)
#define CSL_CSIRX_STREAM1_DATA_CFG                                             (0x00000208U)
#define CSL_CSIRX_STREAM1_CFG                                                  (0x0000020CU)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL                                         (0x00000210U)
#define CSL_CSIRX_STREAM1_MONITOR_FRAME                                        (0x00000214U)
#define CSL_CSIRX_STREAM1_MONITOR_LB                                           (0x00000218U)
#define CSL_CSIRX_STREAM1_TIMER                                                (0x0000021CU)
#define CSL_CSIRX_STREAM1_FCC_CFG                                              (0x00000220U)
#define CSL_CSIRX_STREAM1_FCC_CTRL                                             (0x00000224U)
#define CSL_CSIRX_STREAM1_FIFO_FILL_LVL                                        (0x00000228U)
#define CSL_CSIRX_STREAM2_CTRL                                                 (0x00000300U)
#define CSL_CSIRX_STREAM2_STATUS                                               (0x00000304U)
#define CSL_CSIRX_STREAM2_DATA_CFG                                             (0x00000308U)
#define CSL_CSIRX_STREAM2_CFG                                                  (0x0000030CU)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL                                         (0x00000310U)
#define CSL_CSIRX_STREAM2_MONITOR_FRAME                                        (0x00000314U)
#define CSL_CSIRX_STREAM2_MONITOR_LB                                           (0x00000318U)
#define CSL_CSIRX_STREAM2_TIMER                                                (0x0000031CU)
#define CSL_CSIRX_STREAM2_FCC_CFG                                              (0x00000320U)
#define CSL_CSIRX_STREAM2_FCC_CTRL                                             (0x00000324U)
#define CSL_CSIRX_STREAM2_FIFO_FILL_LVL                                        (0x00000328U)
#define CSL_CSIRX_STREAM3_CTRL                                                 (0x00000400U)
#define CSL_CSIRX_STREAM3_STATUS                                               (0x00000404U)
#define CSL_CSIRX_STREAM3_DATA_CFG                                             (0x00000408U)
#define CSL_CSIRX_STREAM3_CFG                                                  (0x0000040CU)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL                                         (0x00000410U)
#define CSL_CSIRX_STREAM3_MONITOR_FRAME                                        (0x00000414U)
#define CSL_CSIRX_STREAM3_MONITOR_LB                                           (0x00000418U)
#define CSL_CSIRX_STREAM3_TIMER                                                (0x0000041CU)
#define CSL_CSIRX_STREAM3_FCC_CFG                                              (0x00000420U)
#define CSL_CSIRX_STREAM3_FCC_CTRL                                             (0x00000424U)
#define CSL_CSIRX_STREAM3_FIFO_FILL_LVL                                        (0x00000428U)
#define CSL_CSIRX_ASF_INT_STATUS                                               (0x00000900U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS                                           (0x00000904U)
#define CSL_CSIRX_ASF_INT_MASK                                                 (0x00000908U)
#define CSL_CSIRX_ASF_INT_TEST                                                 (0x0000090CU)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT                                    (0x00000910U)
#define CSL_CSIRX_ASF_SRAM_CORR_FAULT_STATUS                                   (0x00000920U)
#define CSL_CSIRX_ASF_SRAM_UNCORR_FAULT_STATUS                                 (0x00000924U)
#define CSL_CSIRX_ASF_SRAM_FAULT_STATS                                         (0x00000928U)
#define CSL_CSIRX_ASF_TRANS_TO_CTRL                                            (0x00000930U)
#define CSL_CSIRX_ASF_TRANS_TO_FAULT_MASK                                      (0x00000934U)
#define CSL_CSIRX_ASF_TRANS_TO_FAULT_STATUS                                    (0x00000938U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK                                      (0x00000940U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS                                    (0x00000944U)
#define CSL_CSIRX_ID_PROD_VER                                                  (0x00000FFCU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* DEVICE_CONFIG */

#define CSL_CSIRX_DEVICE_CONFIG_MAX_LANE_NB_MASK                               (0x00000007U)
#define CSL_CSIRX_DEVICE_CONFIG_MAX_LANE_NB_SHIFT                              (0x00000000U)
#define CSL_CSIRX_DEVICE_CONFIG_MAX_LANE_NB_MAX                                (0x00000007U)

#define CSL_CSIRX_DEVICE_CONFIG_CDNS_PHY_PRESENT_MASK                          (0x00000008U)
#define CSL_CSIRX_DEVICE_CONFIG_CDNS_PHY_PRESENT_SHIFT                         (0x00000003U)
#define CSL_CSIRX_DEVICE_CONFIG_CDNS_PHY_PRESENT_MAX                           (0x00000001U)

#define CSL_CSIRX_DEVICE_CONFIG_NUM_STREAMS_MASK                               (0x00000070U)
#define CSL_CSIRX_DEVICE_CONFIG_NUM_STREAMS_SHIFT                              (0x00000004U)
#define CSL_CSIRX_DEVICE_CONFIG_NUM_STREAMS_MAX                                (0x00000007U)

#define CSL_CSIRX_DEVICE_CONFIG_DATAPATH_SIZE_MASK                             (0x00000180U)
#define CSL_CSIRX_DEVICE_CONFIG_DATAPATH_SIZE_SHIFT                            (0x00000007U)
#define CSL_CSIRX_DEVICE_CONFIG_DATAPATH_SIZE_MAX                              (0x00000003U)

#define CSL_CSIRX_DEVICE_CONFIG_VCX_CONFIG_MASK                                (0x00000200U)
#define CSL_CSIRX_DEVICE_CONFIG_VCX_CONFIG_SHIFT                               (0x00000009U)
#define CSL_CSIRX_DEVICE_CONFIG_VCX_CONFIG_MAX                                 (0x00000001U)

#define CSL_CSIRX_DEVICE_CONFIG_ASF_CONFIG_MASK                                (0x00000400U)
#define CSL_CSIRX_DEVICE_CONFIG_ASF_CONFIG_SHIFT                               (0x0000000AU)
#define CSL_CSIRX_DEVICE_CONFIG_ASF_CONFIG_MAX                                 (0x00000001U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM0_FIFO_MODE_MASK                         (0x00003000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM0_FIFO_MODE_SHIFT                        (0x0000000CU)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM0_FIFO_MODE_MAX                          (0x00000003U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM0_NUM_PIXELS_MASK                        (0x0000C000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM0_NUM_PIXELS_SHIFT                       (0x0000000EU)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM0_NUM_PIXELS_MAX                         (0x00000003U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM0_MONITOR_PRESENT_MASK                   (0x00010000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM0_MONITOR_PRESENT_SHIFT                  (0x00000010U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM0_MONITOR_PRESENT_MAX                    (0x00000001U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM1_FIFO_MODE_MASK                         (0x00060000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM1_FIFO_MODE_SHIFT                        (0x00000011U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM1_FIFO_MODE_MAX                          (0x00000003U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM1_NUM_PIXELS_MASK                        (0x00180000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM1_NUM_PIXELS_SHIFT                       (0x00000013U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM1_NUM_PIXELS_MAX                         (0x00000003U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM1_MONITOR_PRESENT_MASK                   (0x00200000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM1_MONITOR_PRESENT_SHIFT                  (0x00000015U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM1_MONITOR_PRESENT_MAX                    (0x00000001U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM2_FIFO_MODE_MASK                         (0x00C00000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM2_FIFO_MODE_SHIFT                        (0x00000016U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM2_FIFO_MODE_MAX                          (0x00000003U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM2_NUM_PIXELS_MASK                        (0x03000000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM2_NUM_PIXELS_SHIFT                       (0x00000018U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM2_NUM_PIXELS_MAX                         (0x00000003U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM2_MONITOR_PRESENT_MASK                   (0x04000000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM2_MONITOR_PRESENT_SHIFT                  (0x0000001AU)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM2_MONITOR_PRESENT_MAX                    (0x00000001U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM3_FIFO_MODE_MASK                         (0x18000000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM3_FIFO_MODE_SHIFT                        (0x0000001BU)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM3_FIFO_MODE_MAX                          (0x00000003U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM3_NUM_PIXELS_MASK                        (0x60000000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM3_NUM_PIXELS_SHIFT                       (0x0000001DU)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM3_NUM_PIXELS_MAX                         (0x00000003U)

#define CSL_CSIRX_DEVICE_CONFIG_STREAM3_MONITOR_PRESENT_MASK                   (0x80000000U)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM3_MONITOR_PRESENT_SHIFT                  (0x0000001FU)
#define CSL_CSIRX_DEVICE_CONFIG_STREAM3_MONITOR_PRESENT_MAX                    (0x00000001U)

/* SOFT_RESET */

#define CSL_CSIRX_SOFT_RESET_FRONT_MASK                                        (0x00000001U)
#define CSL_CSIRX_SOFT_RESET_FRONT_SHIFT                                       (0x00000000U)
#define CSL_CSIRX_SOFT_RESET_FRONT_MAX                                         (0x00000001U)

#define CSL_CSIRX_SOFT_RESET_PROTOCOL_MASK                                     (0x00000002U)
#define CSL_CSIRX_SOFT_RESET_PROTOCOL_SHIFT                                    (0x00000001U)
#define CSL_CSIRX_SOFT_RESET_PROTOCOL_MAX                                      (0x00000001U)

/* STATIC_CFG */

#define CSL_CSIRX_STATIC_CFG_SEL_MASK                                          (0x00000003U)
#define CSL_CSIRX_STATIC_CFG_SEL_SHIFT                                         (0x00000000U)
#define CSL_CSIRX_STATIC_CFG_SEL_MAX                                           (0x00000003U)

#define CSL_CSIRX_STATIC_CFG_V2P0_SUPPORT_ENABLE_MASK                          (0x00000010U)
#define CSL_CSIRX_STATIC_CFG_V2P0_SUPPORT_ENABLE_SHIFT                         (0x00000004U)
#define CSL_CSIRX_STATIC_CFG_V2P0_SUPPORT_ENABLE_MAX                           (0x00000001U)

#define CSL_CSIRX_STATIC_CFG_LANE_NB_MASK                                      (0x00000700U)
#define CSL_CSIRX_STATIC_CFG_LANE_NB_SHIFT                                     (0x00000008U)
#define CSL_CSIRX_STATIC_CFG_LANE_NB_MAX                                       (0x00000007U)

#define CSL_CSIRX_STATIC_CFG_DL0_MAP_MASK                                      (0x00070000U)
#define CSL_CSIRX_STATIC_CFG_DL0_MAP_SHIFT                                     (0x00000010U)
#define CSL_CSIRX_STATIC_CFG_DL0_MAP_MAX                                       (0x00000007U)

#define CSL_CSIRX_STATIC_CFG_DL1_MAP_MASK                                      (0x00700000U)
#define CSL_CSIRX_STATIC_CFG_DL1_MAP_SHIFT                                     (0x00000014U)
#define CSL_CSIRX_STATIC_CFG_DL1_MAP_MAX                                       (0x00000007U)

#define CSL_CSIRX_STATIC_CFG_DL2_MAP_MASK                                      (0x07000000U)
#define CSL_CSIRX_STATIC_CFG_DL2_MAP_SHIFT                                     (0x00000018U)
#define CSL_CSIRX_STATIC_CFG_DL2_MAP_MAX                                       (0x00000007U)

#define CSL_CSIRX_STATIC_CFG_DL3_MAP_MASK                                      (0x70000000U)
#define CSL_CSIRX_STATIC_CFG_DL3_MAP_SHIFT                                     (0x0000001CU)
#define CSL_CSIRX_STATIC_CFG_DL3_MAP_MAX                                       (0x00000007U)

/* ERROR_BYPASS_CFG */

#define CSL_CSIRX_ERROR_BYPASS_CFG_CRC_MASK                                    (0x00000001U)
#define CSL_CSIRX_ERROR_BYPASS_CFG_CRC_SHIFT                                   (0x00000000U)
#define CSL_CSIRX_ERROR_BYPASS_CFG_CRC_MAX                                     (0x00000001U)

#define CSL_CSIRX_ERROR_BYPASS_CFG_ECC_MASK                                    (0x00000002U)
#define CSL_CSIRX_ERROR_BYPASS_CFG_ECC_SHIFT                                   (0x00000001U)
#define CSL_CSIRX_ERROR_BYPASS_CFG_ECC_MAX                                     (0x00000001U)

#define CSL_CSIRX_ERROR_BYPASS_CFG_DATA_ID_MASK                                (0x00000004U)
#define CSL_CSIRX_ERROR_BYPASS_CFG_DATA_ID_SHIFT                               (0x00000002U)
#define CSL_CSIRX_ERROR_BYPASS_CFG_DATA_ID_MAX                                 (0x00000001U)

/* MONITOR_IRQS */

#define CSL_CSIRX_MONITOR_IRQS_STREAM0_TIMER_IRQ_MASK                          (0x00000001U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_TIMER_IRQ_SHIFT                         (0x00000000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_TIMER_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM0_LB_IRQ_MASK                             (0x00000002U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_LB_IRQ_SHIFT                            (0x00000001U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_LB_IRQ_MAX                              (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FRAME_IRQ_MASK                          (0x00000004U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FRAME_IRQ_SHIFT                         (0x00000002U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FRAME_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FCC_START_IRQ_MASK                      (0x00000008U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FCC_START_IRQ_SHIFT                     (0x00000003U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FCC_START_IRQ_MAX                       (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FCC_STOP_IRQ_MASK                       (0x00000010U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FCC_STOP_IRQ_SHIFT                      (0x00000004U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FCC_STOP_IRQ_MAX                        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FRAME_CNT_ERROR_IRQ_MASK                (0x00000020U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FRAME_CNT_ERROR_IRQ_SHIFT               (0x00000005U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FRAME_CNT_ERROR_IRQ_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FRAME_MISMATCH_IRQ_MASK                 (0x00000040U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FRAME_MISMATCH_IRQ_SHIFT                (0x00000006U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_FRAME_MISMATCH_IRQ_MAX                  (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM0_LINE_CNT_ERROR_IRQ_MASK                 (0x00000080U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_LINE_CNT_ERROR_IRQ_SHIFT                (0x00000007U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM0_LINE_CNT_ERROR_IRQ_MAX                  (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM1_TIMER_IRQ_MASK                          (0x00000100U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_TIMER_IRQ_SHIFT                         (0x00000008U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_TIMER_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM1_LB_IRQ_MASK                             (0x00000200U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_LB_IRQ_SHIFT                            (0x00000009U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_LB_IRQ_MAX                              (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FRAME_IRQ_MASK                          (0x00000400U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FRAME_IRQ_SHIFT                         (0x0000000AU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FRAME_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FCC_START_IRQ_MASK                      (0x00000800U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FCC_START_IRQ_SHIFT                     (0x0000000BU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FCC_START_IRQ_MAX                       (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FCC_STOP_IRQ_MASK                       (0x00001000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FCC_STOP_IRQ_SHIFT                      (0x0000000CU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FCC_STOP_IRQ_MAX                        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FRAME_CNT_ERROR_IRQ_MASK                (0x00002000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FRAME_CNT_ERROR_IRQ_SHIFT               (0x0000000DU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FRAME_CNT_ERROR_IRQ_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FRAME_MISMATCH_IRQ_MASK                 (0x00004000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FRAME_MISMATCH_IRQ_SHIFT                (0x0000000EU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_FRAME_MISMATCH_IRQ_MAX                  (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM1_LINE_CNT_ERROR_IRQ_MASK                 (0x00008000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_LINE_CNT_ERROR_IRQ_SHIFT                (0x0000000FU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM1_LINE_CNT_ERROR_IRQ_MAX                  (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM2_TIMER_IRQ_MASK                          (0x00010000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_TIMER_IRQ_SHIFT                         (0x00000010U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_TIMER_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM2_LB_IRQ_MASK                             (0x00020000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_LB_IRQ_SHIFT                            (0x00000011U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_LB_IRQ_MAX                              (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FRAME_IRQ_MASK                          (0x00040000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FRAME_IRQ_SHIFT                         (0x00000012U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FRAME_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FCC_START_IRQ_MASK                      (0x00080000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FCC_START_IRQ_SHIFT                     (0x00000013U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FCC_START_IRQ_MAX                       (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FCC_STOP_IRQ_MASK                       (0x00100000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FCC_STOP_IRQ_SHIFT                      (0x00000014U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FCC_STOP_IRQ_MAX                        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FRAME_CNT_ERROR_IRQ_MASK                (0x00200000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FRAME_CNT_ERROR_IRQ_SHIFT               (0x00000015U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FRAME_CNT_ERROR_IRQ_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FRAME_MISMATCH_IRQ_MASK                 (0x00400000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FRAME_MISMATCH_IRQ_SHIFT                (0x00000016U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_FRAME_MISMATCH_IRQ_MAX                  (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM2_LINE_CNT_ERROR_IRQ_MASK                 (0x00800000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_LINE_CNT_ERROR_IRQ_SHIFT                (0x00000017U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM2_LINE_CNT_ERROR_IRQ_MAX                  (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM3_TIMER_IRQ_MASK                          (0x01000000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_TIMER_IRQ_SHIFT                         (0x00000018U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_TIMER_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM3_LB_IRQ_MASK                             (0x02000000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_LB_IRQ_SHIFT                            (0x00000019U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_LB_IRQ_MAX                              (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FRAME_IRQ_MASK                          (0x04000000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FRAME_IRQ_SHIFT                         (0x0000001AU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FRAME_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FCC_START_IRQ_MASK                      (0x08000000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FCC_START_IRQ_SHIFT                     (0x0000001BU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FCC_START_IRQ_MAX                       (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FCC_STOP_IRQ_MASK                       (0x10000000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FCC_STOP_IRQ_SHIFT                      (0x0000001CU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FCC_STOP_IRQ_MAX                        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FRAME_CNT_ERROR_IRQ_MASK                (0x20000000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FRAME_CNT_ERROR_IRQ_SHIFT               (0x0000001DU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FRAME_CNT_ERROR_IRQ_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FRAME_MISMATCH_IRQ_MASK                 (0x40000000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FRAME_MISMATCH_IRQ_SHIFT                (0x0000001EU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_FRAME_MISMATCH_IRQ_MAX                  (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_STREAM3_LINE_CNT_ERROR_IRQ_MASK                 (0x80000000U)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_LINE_CNT_ERROR_IRQ_SHIFT                (0x0000001FU)
#define CSL_CSIRX_MONITOR_IRQS_STREAM3_LINE_CNT_ERROR_IRQ_MAX                  (0x00000001U)

/* MONITOR_IRQS_MASK_CFG */

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_TIMER_IRQM_MASK                (0x00000001U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_TIMER_IRQM_SHIFT               (0x00000000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_TIMER_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_LB_IRQM_MASK                   (0x00000002U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_LB_IRQM_SHIFT                  (0x00000001U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_LB_IRQM_MAX                    (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FRAME_IRQM_MASK                (0x00000004U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FRAME_IRQM_SHIFT               (0x00000002U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FRAME_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FCC_START_IRQM_MASK            (0x00000008U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FCC_START_IRQM_SHIFT           (0x00000003U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FCC_START_IRQM_MAX             (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FCC_STOP_IRQM_MASK             (0x00000010U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FCC_STOP_IRQM_SHIFT            (0x00000004U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FCC_STOP_IRQM_MAX              (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FRAME_CNT_ERROR_IRQM_MASK      (0x00000020U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FRAME_CNT_ERROR_IRQM_SHIFT     (0x00000005U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FRAME_CNT_ERROR_IRQM_MAX       (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FRAME_MISMATCH_IRQM_MASK       (0x00000040U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FRAME_MISMATCH_IRQM_SHIFT      (0x00000006U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_FRAME_MISMATCH_IRQM_MAX        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_LINE_CNT_ERROR_IRQM_MASK       (0x00000080U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_LINE_CNT_ERROR_IRQM_SHIFT      (0x00000007U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM0_LINE_CNT_ERROR_IRQM_MAX        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_TIMER_IRQM_MASK                (0x00000100U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_TIMER_IRQM_SHIFT               (0x00000008U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_TIMER_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_LB_IRQM_MASK                   (0x00000200U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_LB_IRQM_SHIFT                  (0x00000009U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_LB_IRQM_MAX                    (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FRAME_IRQM_MASK                (0x00000400U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FRAME_IRQM_SHIFT               (0x0000000AU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FRAME_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FCC_START_IRQM_MASK            (0x00000800U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FCC_START_IRQM_SHIFT           (0x0000000BU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FCC_START_IRQM_MAX             (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FCC_STOP_IRQM_MASK             (0x00001000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FCC_STOP_IRQM_SHIFT            (0x0000000CU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FCC_STOP_IRQM_MAX              (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FRAME_CNT_ERROR_IRQM_MASK      (0x00002000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FRAME_CNT_ERROR_IRQM_SHIFT     (0x0000000DU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FRAME_CNT_ERROR_IRQM_MAX       (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FRAME_MISMATCH_IRQM_MASK       (0x00004000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FRAME_MISMATCH_IRQM_SHIFT      (0x0000000EU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_FRAME_MISMATCH_IRQM_MAX        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_LINE_CNT_ERROR_IRQM_MASK       (0x00008000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_LINE_CNT_ERROR_IRQM_SHIFT      (0x0000000FU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM1_LINE_CNT_ERROR_IRQM_MAX        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_TIMER_IRQM_MASK                (0x00010000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_TIMER_IRQM_SHIFT               (0x00000010U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_TIMER_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_LB_IRQM_MASK                   (0x00020000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_LB_IRQM_SHIFT                  (0x00000011U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_LB_IRQM_MAX                    (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FRAME_IRQM_MASK                (0x00040000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FRAME_IRQM_SHIFT               (0x00000012U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FRAME_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FCC_START_IRQM_MASK            (0x00080000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FCC_START_IRQM_SHIFT           (0x00000013U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FCC_START_IRQM_MAX             (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FCC_STOP_IRQM_MASK             (0x00100000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FCC_STOP_IRQM_SHIFT            (0x00000014U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FCC_STOP_IRQM_MAX              (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FRAME_CNT_ERROR_IRQM_MASK      (0x00200000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FRAME_CNT_ERROR_IRQM_SHIFT     (0x00000015U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FRAME_CNT_ERROR_IRQM_MAX       (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FRAME_MISMATCH_IRQM_MASK       (0x00400000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FRAME_MISMATCH_IRQM_SHIFT      (0x00000016U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_FRAME_MISMATCH_IRQM_MAX        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_LINE_CNT_ERROR_IRQM_MASK       (0x00800000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_LINE_CNT_ERROR_IRQM_SHIFT      (0x00000017U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM2_LINE_CNT_ERROR_IRQM_MAX        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_TIMER_IRQM_MASK                (0x01000000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_TIMER_IRQM_SHIFT               (0x00000018U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_TIMER_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_LB_IRQM_MASK                   (0x02000000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_LB_IRQM_SHIFT                  (0x00000019U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_LB_IRQM_MAX                    (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FRAME_IRQM_MASK                (0x04000000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FRAME_IRQM_SHIFT               (0x0000001AU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FRAME_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FCC_START_IRQM_MASK            (0x08000000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FCC_START_IRQM_SHIFT           (0x0000001BU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FCC_START_IRQM_MAX             (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FCC_STOP_IRQM_MASK             (0x10000000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FCC_STOP_IRQM_SHIFT            (0x0000001CU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FCC_STOP_IRQM_MAX              (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FRAME_CNT_ERROR_IRQM_MASK      (0x20000000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FRAME_CNT_ERROR_IRQM_SHIFT     (0x0000001DU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FRAME_CNT_ERROR_IRQM_MAX       (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FRAME_MISMATCH_IRQM_MASK       (0x40000000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FRAME_MISMATCH_IRQM_SHIFT      (0x0000001EU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_FRAME_MISMATCH_IRQM_MAX        (0x00000001U)

#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_LINE_CNT_ERROR_IRQM_MASK       (0x80000000U)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_LINE_CNT_ERROR_IRQM_SHIFT      (0x0000001FU)
#define CSL_CSIRX_MONITOR_IRQS_MASK_CFG_STREAM3_LINE_CNT_ERROR_IRQM_MAX        (0x00000001U)

/* INFO_IRQS */

#define CSL_CSIRX_INFO_IRQS_SP_RCVD_IRQ_MASK                                   (0x00000001U)
#define CSL_CSIRX_INFO_IRQS_SP_RCVD_IRQ_SHIFT                                  (0x00000000U)
#define CSL_CSIRX_INFO_IRQS_SP_RCVD_IRQ_MAX                                    (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_LP_RCVD_IRQ_MASK                                   (0x00000002U)
#define CSL_CSIRX_INFO_IRQS_LP_RCVD_IRQ_SHIFT                                  (0x00000001U)
#define CSL_CSIRX_INFO_IRQS_LP_RCVD_IRQ_MAX                                    (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_SLEEP_IRQ_MASK                                     (0x00000004U)
#define CSL_CSIRX_INFO_IRQS_SLEEP_IRQ_SHIFT                                    (0x00000002U)
#define CSL_CSIRX_INFO_IRQS_SLEEP_IRQ_MAX                                      (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_WAKEUP_IRQ_MASK                                    (0x00000008U)
#define CSL_CSIRX_INFO_IRQS_WAKEUP_IRQ_SHIFT                                   (0x00000003U)
#define CSL_CSIRX_INFO_IRQS_WAKEUP_IRQ_MAX                                     (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_ECC_SPARES_NONZERO_IRQ_MASK                        (0x00000010U)
#define CSL_CSIRX_INFO_IRQS_ECC_SPARES_NONZERO_IRQ_SHIFT                       (0x00000004U)
#define CSL_CSIRX_INFO_IRQS_ECC_SPARES_NONZERO_IRQ_MAX                         (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_DESKEW_ENTRY_IRQ_MASK                              (0x00000020U)
#define CSL_CSIRX_INFO_IRQS_DESKEW_ENTRY_IRQ_SHIFT                             (0x00000005U)
#define CSL_CSIRX_INFO_IRQS_DESKEW_ENTRY_IRQ_MAX                               (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_SP_GENERIC_RCVD_IRQ_MASK                           (0x00000040U)
#define CSL_CSIRX_INFO_IRQS_SP_GENERIC_RCVD_IRQ_SHIFT                          (0x00000006U)
#define CSL_CSIRX_INFO_IRQS_SP_GENERIC_RCVD_IRQ_MAX                            (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_STREAM0_STOP_IRQ_MASK                              (0x00000080U)
#define CSL_CSIRX_INFO_IRQS_STREAM0_STOP_IRQ_SHIFT                             (0x00000007U)
#define CSL_CSIRX_INFO_IRQS_STREAM0_STOP_IRQ_MAX                               (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_STREAM0_ABORT_IRQ_MASK                             (0x00000100U)
#define CSL_CSIRX_INFO_IRQS_STREAM0_ABORT_IRQ_SHIFT                            (0x00000008U)
#define CSL_CSIRX_INFO_IRQS_STREAM0_ABORT_IRQ_MAX                              (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_STREAM1_STOP_IRQ_MASK                              (0x00000200U)
#define CSL_CSIRX_INFO_IRQS_STREAM1_STOP_IRQ_SHIFT                             (0x00000009U)
#define CSL_CSIRX_INFO_IRQS_STREAM1_STOP_IRQ_MAX                               (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_STREAM1_ABORT_IRQ_MASK                             (0x00000400U)
#define CSL_CSIRX_INFO_IRQS_STREAM1_ABORT_IRQ_SHIFT                            (0x0000000AU)
#define CSL_CSIRX_INFO_IRQS_STREAM1_ABORT_IRQ_MAX                              (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_STREAM2_STOP_IRQ_MASK                              (0x00000800U)
#define CSL_CSIRX_INFO_IRQS_STREAM2_STOP_IRQ_SHIFT                             (0x0000000BU)
#define CSL_CSIRX_INFO_IRQS_STREAM2_STOP_IRQ_MAX                               (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_STREAM2_ABORT_IRQ_MASK                             (0x00001000U)
#define CSL_CSIRX_INFO_IRQS_STREAM2_ABORT_IRQ_SHIFT                            (0x0000000CU)
#define CSL_CSIRX_INFO_IRQS_STREAM2_ABORT_IRQ_MAX                              (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_STREAM3_STOP_IRQ_MASK                              (0x00002000U)
#define CSL_CSIRX_INFO_IRQS_STREAM3_STOP_IRQ_SHIFT                             (0x0000000DU)
#define CSL_CSIRX_INFO_IRQS_STREAM3_STOP_IRQ_MAX                               (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_STREAM3_ABORT_IRQ_MASK                             (0x00004000U)
#define CSL_CSIRX_INFO_IRQS_STREAM3_ABORT_IRQ_SHIFT                            (0x0000000EU)
#define CSL_CSIRX_INFO_IRQS_STREAM3_ABORT_IRQ_MAX                              (0x00000001U)

/* INFO_IRQS_MASK_CFG */

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_SP_RCVD_IRQM_MASK                         (0x00000001U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_SP_RCVD_IRQM_SHIFT                        (0x00000000U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_SP_RCVD_IRQM_MAX                          (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_LP_RCVD_IRQM_MASK                         (0x00000002U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_LP_RCVD_IRQM_SHIFT                        (0x00000001U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_LP_RCVD_IRQM_MAX                          (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_SLEEP_IRQM_MASK                           (0x00000004U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_SLEEP_IRQM_SHIFT                          (0x00000002U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_SLEEP_IRQM_MAX                            (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_WAKEUP_IRQM_MASK                          (0x00000008U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_WAKEUP_IRQM_SHIFT                         (0x00000003U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_WAKEUP_IRQM_MAX                           (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_ECC_SPARES_NONZERO_IRQM_MASK              (0x00000010U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_ECC_SPARES_NONZERO_IRQM_SHIFT             (0x00000004U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_ECC_SPARES_NONZERO_IRQM_MAX               (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_DESKEW_ENTRY_IRQM_MASK                    (0x00000020U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_DESKEW_ENTRY_IRQM_SHIFT                   (0x00000005U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_DESKEW_ENTRY_IRQM_MAX                     (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_SP_GENERIC_RCVD_IRQM_MASK                 (0x00000040U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_SP_GENERIC_RCVD_IRQM_SHIFT                (0x00000006U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_SP_GENERIC_RCVD_IRQM_MAX                  (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM0_STOP_IRQM_MASK                    (0x00000080U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM0_STOP_IRQM_SHIFT                   (0x00000007U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM0_STOP_IRQM_MAX                     (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM0_ABORT_IRQM_MASK                   (0x00000100U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM0_ABORT_IRQM_SHIFT                  (0x00000008U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM0_ABORT_IRQM_MAX                    (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM1_STOP_IRQM_MASK                    (0x00000200U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM1_STOP_IRQM_SHIFT                   (0x00000009U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM1_STOP_IRQM_MAX                     (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM1_ABORT_IRQM_MASK                   (0x00000400U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM1_ABORT_IRQM_SHIFT                  (0x0000000AU)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM1_ABORT_IRQM_MAX                    (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM2_STOP_IRQM_MASK                    (0x00000800U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM2_STOP_IRQM_SHIFT                   (0x0000000BU)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM2_STOP_IRQM_MAX                     (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM2_ABORT_IRQM_MASK                   (0x00001000U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM2_ABORT_IRQM_SHIFT                  (0x0000000CU)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM2_ABORT_IRQM_MAX                    (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM3_STOP_IRQM_MASK                    (0x00002000U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM3_STOP_IRQM_SHIFT                   (0x0000000DU)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM3_STOP_IRQM_MAX                     (0x00000001U)

#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM3_ABORT_IRQM_MASK                   (0x00004000U)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM3_ABORT_IRQM_SHIFT                  (0x0000000EU)
#define CSL_CSIRX_INFO_IRQS_MASK_CFG_STREAM3_ABORT_IRQM_MAX                    (0x00000001U)

/* ERROR_IRQS */

#define CSL_CSIRX_ERROR_IRQS_FRONT_FIFO_OVERFLOW_IRQ_MASK                      (0x00000001U)
#define CSL_CSIRX_ERROR_IRQS_FRONT_FIFO_OVERFLOW_IRQ_SHIFT                     (0x00000000U)
#define CSL_CSIRX_ERROR_IRQS_FRONT_FIFO_OVERFLOW_IRQ_MAX                       (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_PAYLOAD_CRC_IRQ_MASK                              (0x00000010U)
#define CSL_CSIRX_ERROR_IRQS_PAYLOAD_CRC_IRQ_SHIFT                             (0x00000004U)
#define CSL_CSIRX_ERROR_IRQS_PAYLOAD_CRC_IRQ_MAX                               (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_HEADER_ECC_IRQ_MASK                               (0x00000020U)
#define CSL_CSIRX_ERROR_IRQS_HEADER_ECC_IRQ_SHIFT                              (0x00000005U)
#define CSL_CSIRX_ERROR_IRQS_HEADER_ECC_IRQ_MAX                                (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_HEADER_CORRECTED_ECC_IRQ_MASK                     (0x00000040U)
#define CSL_CSIRX_ERROR_IRQS_HEADER_CORRECTED_ECC_IRQ_SHIFT                    (0x00000006U)
#define CSL_CSIRX_ERROR_IRQS_HEADER_CORRECTED_ECC_IRQ_MAX                      (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_DATA_ID_IRQ_MASK                                  (0x00000080U)
#define CSL_CSIRX_ERROR_IRQS_DATA_ID_IRQ_SHIFT                                 (0x00000007U)
#define CSL_CSIRX_ERROR_IRQS_DATA_ID_IRQ_MAX                                   (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_INVALID_ACCESS_IRQ_MASK                           (0x00000100U)
#define CSL_CSIRX_ERROR_IRQS_INVALID_ACCESS_IRQ_SHIFT                          (0x00000008U)
#define CSL_CSIRX_ERROR_IRQS_INVALID_ACCESS_IRQ_MAX                            (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_SP_INVALID_RCVD_IRQ_MASK                          (0x00000200U)
#define CSL_CSIRX_ERROR_IRQS_SP_INVALID_RCVD_IRQ_SHIFT                         (0x00000009U)
#define CSL_CSIRX_ERROR_IRQS_SP_INVALID_RCVD_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_FRONT_LP_NO_PAYLOAD_IRQ_MASK                      (0x00000400U)
#define CSL_CSIRX_ERROR_IRQS_FRONT_LP_NO_PAYLOAD_IRQ_SHIFT                     (0x0000000AU)
#define CSL_CSIRX_ERROR_IRQS_FRONT_LP_NO_PAYLOAD_IRQ_MAX                       (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_PROT_TRUNCATED_PACKET_IRQ_MASK                    (0x00000800U)
#define CSL_CSIRX_ERROR_IRQS_PROT_TRUNCATED_PACKET_IRQ_SHIFT                   (0x0000000BU)
#define CSL_CSIRX_ERROR_IRQS_PROT_TRUNCATED_PACKET_IRQ_MAX                     (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_FRONT_TRUNC_HDR_IRQ_MASK                          (0x00001000U)
#define CSL_CSIRX_ERROR_IRQS_FRONT_TRUNC_HDR_IRQ_SHIFT                         (0x0000000CU)
#define CSL_CSIRX_ERROR_IRQS_FRONT_TRUNC_HDR_IRQ_MAX                           (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_STREAM0_FIFO_OVERFLOW_IRQ_MASK                    (0x00010000U)
#define CSL_CSIRX_ERROR_IRQS_STREAM0_FIFO_OVERFLOW_IRQ_SHIFT                   (0x00000010U)
#define CSL_CSIRX_ERROR_IRQS_STREAM0_FIFO_OVERFLOW_IRQ_MAX                     (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_STREAM1_FIFO_OVERFLOW_IRQ_MASK                    (0x00020000U)
#define CSL_CSIRX_ERROR_IRQS_STREAM1_FIFO_OVERFLOW_IRQ_SHIFT                   (0x00000011U)
#define CSL_CSIRX_ERROR_IRQS_STREAM1_FIFO_OVERFLOW_IRQ_MAX                     (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_STREAM2_FIFO_OVERFLOW_IRQ_MASK                    (0x00040000U)
#define CSL_CSIRX_ERROR_IRQS_STREAM2_FIFO_OVERFLOW_IRQ_SHIFT                   (0x00000012U)
#define CSL_CSIRX_ERROR_IRQS_STREAM2_FIFO_OVERFLOW_IRQ_MAX                     (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_STREAM3_FIFO_OVERFLOW_IRQ_MASK                    (0x00080000U)
#define CSL_CSIRX_ERROR_IRQS_STREAM3_FIFO_OVERFLOW_IRQ_SHIFT                   (0x00000013U)
#define CSL_CSIRX_ERROR_IRQS_STREAM3_FIFO_OVERFLOW_IRQ_MAX                     (0x00000001U)

/* ERROR_IRQS_MASK_CFG */

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_FRONT_FIFO_OVERFLOW_IRQM_MASK            (0x00000001U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_FRONT_FIFO_OVERFLOW_IRQM_SHIFT           (0x00000000U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_FRONT_FIFO_OVERFLOW_IRQM_MAX             (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_PAYLOAD_CRC_IRQM_MASK                    (0x00000010U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_PAYLOAD_CRC_IRQM_SHIFT                   (0x00000004U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_PAYLOAD_CRC_IRQM_MAX                     (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_HEADER_ECC_IRQM_MASK                     (0x00000020U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_HEADER_ECC_IRQM_SHIFT                    (0x00000005U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_HEADER_ECC_IRQM_MAX                      (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_HEADER_CORRECTED_ECC_IRQM_MASK           (0x00000040U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_HEADER_CORRECTED_ECC_IRQM_SHIFT          (0x00000006U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_HEADER_CORRECTED_ECC_IRQM_MAX            (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_DATA_ID_IRQM_MASK                        (0x00000080U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_DATA_ID_IRQM_SHIFT                       (0x00000007U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_DATA_ID_IRQM_MAX                         (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_INVALID_ACCESS_IRQM_MASK                 (0x00000100U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_INVALID_ACCESS_IRQM_SHIFT                (0x00000008U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_INVALID_ACCESS_IRQM_MAX                  (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_SP_INVALID_RCVD_IRQM_MASK                (0x00000200U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_SP_INVALID_RCVD_IRQM_SHIFT               (0x00000009U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_SP_INVALID_RCVD_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_FRONT_LP_NO_PAYLOAD_IRQM_MASK            (0x00000400U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_FRONT_LP_NO_PAYLOAD_IRQM_SHIFT           (0x0000000AU)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_FRONT_LP_NO_PAYLOAD_IRQM_MAX             (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_PROT_TRUNCATED_PACKET_IRQM_MASK          (0x00000800U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_PROT_TRUNCATED_PACKET_IRQM_SHIFT         (0x0000000BU)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_PROT_TRUNCATED_PACKET_IRQM_MAX           (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_FRONT_TRUNC_HDR_IRQM_MASK                (0x00001000U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_FRONT_TRUNC_HDR_IRQM_SHIFT               (0x0000000CU)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_FRONT_TRUNC_HDR_IRQM_MAX                 (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM0_FIFO_OVERFLOW_IRQM_MASK          (0x00010000U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM0_FIFO_OVERFLOW_IRQM_SHIFT         (0x00000010U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM0_FIFO_OVERFLOW_IRQM_MAX           (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM1_FIFO_OVERFLOW_IRQM_MASK          (0x00020000U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM1_FIFO_OVERFLOW_IRQM_SHIFT         (0x00000011U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM1_FIFO_OVERFLOW_IRQM_MAX           (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM2_FIFO_OVERFLOW_IRQM_MASK          (0x00040000U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM2_FIFO_OVERFLOW_IRQM_SHIFT         (0x00000012U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM2_FIFO_OVERFLOW_IRQM_MAX           (0x00000001U)

#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM3_FIFO_OVERFLOW_IRQM_MASK          (0x00080000U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM3_FIFO_OVERFLOW_IRQM_SHIFT         (0x00000013U)
#define CSL_CSIRX_ERROR_IRQS_MASK_CFG_STREAM3_FIFO_OVERFLOW_IRQM_MAX           (0x00000001U)

/* DPHY_LANE_CONTROL */

#define CSL_CSIRX_DPHY_LANE_CONTROL_DL0_ENABLE_MASK                            (0x00000001U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL0_ENABLE_SHIFT                           (0x00000000U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL0_ENABLE_MAX                             (0x00000001U)

#define CSL_CSIRX_DPHY_LANE_CONTROL_DL1_ENABLE_MASK                            (0x00000002U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL1_ENABLE_SHIFT                           (0x00000001U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL1_ENABLE_MAX                             (0x00000001U)

#define CSL_CSIRX_DPHY_LANE_CONTROL_DL2_ENABLE_MASK                            (0x00000004U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL2_ENABLE_SHIFT                           (0x00000002U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL2_ENABLE_MAX                             (0x00000001U)

#define CSL_CSIRX_DPHY_LANE_CONTROL_DL3_ENABLE_MASK                            (0x00000008U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL3_ENABLE_SHIFT                           (0x00000003U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL3_ENABLE_MAX                             (0x00000001U)

#define CSL_CSIRX_DPHY_LANE_CONTROL_CL_ENABLE_MASK                             (0x00000010U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_CL_ENABLE_SHIFT                            (0x00000004U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_CL_ENABLE_MAX                              (0x00000001U)

#define CSL_CSIRX_DPHY_LANE_CONTROL_DL0_RESET_MASK                             (0x00001000U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL0_RESET_SHIFT                            (0x0000000CU)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL0_RESET_MAX                              (0x00000001U)

#define CSL_CSIRX_DPHY_LANE_CONTROL_DL1_RESET_MASK                             (0x00002000U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL1_RESET_SHIFT                            (0x0000000DU)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL1_RESET_MAX                              (0x00000001U)

#define CSL_CSIRX_DPHY_LANE_CONTROL_DL2_RESET_MASK                             (0x00004000U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL2_RESET_SHIFT                            (0x0000000EU)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL2_RESET_MAX                              (0x00000001U)

#define CSL_CSIRX_DPHY_LANE_CONTROL_DL3_RESET_MASK                             (0x00008000U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL3_RESET_SHIFT                            (0x0000000FU)
#define CSL_CSIRX_DPHY_LANE_CONTROL_DL3_RESET_MAX                              (0x00000001U)

#define CSL_CSIRX_DPHY_LANE_CONTROL_CL_RESET_MASK                              (0x00010000U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_CL_RESET_SHIFT                             (0x00000010U)
#define CSL_CSIRX_DPHY_LANE_CONTROL_CL_RESET_MAX                               (0x00000001U)

/* DPHY_STATUS */

#define CSL_CSIRX_DPHY_STATUS_CL_STOPSTATE_MASK                                (0x00000001U)
#define CSL_CSIRX_DPHY_STATUS_CL_STOPSTATE_SHIFT                               (0x00000000U)
#define CSL_CSIRX_DPHY_STATUS_CL_STOPSTATE_MAX                                 (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_CL_ULPSACTIVENOT_MASK                            (0x00000002U)
#define CSL_CSIRX_DPHY_STATUS_CL_ULPSACTIVENOT_SHIFT                           (0x00000001U)
#define CSL_CSIRX_DPHY_STATUS_CL_ULPSACTIVENOT_MAX                             (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_CL_RXULPSCLKNOT_MASK                             (0x00000004U)
#define CSL_CSIRX_DPHY_STATUS_CL_RXULPSCLKNOT_SHIFT                            (0x00000002U)
#define CSL_CSIRX_DPHY_STATUS_CL_RXULPSCLKNOT_MAX                              (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL0_STOPSTATE_MASK                               (0x00000100U)
#define CSL_CSIRX_DPHY_STATUS_DL0_STOPSTATE_SHIFT                              (0x00000008U)
#define CSL_CSIRX_DPHY_STATUS_DL0_STOPSTATE_MAX                                (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL0_ULPSACTIVENOT_MASK                           (0x00000200U)
#define CSL_CSIRX_DPHY_STATUS_DL0_ULPSACTIVENOT_SHIFT                          (0x00000009U)
#define CSL_CSIRX_DPHY_STATUS_DL0_ULPSACTIVENOT_MAX                            (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL0_RXULPSESC_MASK                               (0x00000400U)
#define CSL_CSIRX_DPHY_STATUS_DL0_RXULPSESC_SHIFT                              (0x0000000AU)
#define CSL_CSIRX_DPHY_STATUS_DL0_RXULPSESC_MAX                                (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL1_STOPSTATE_MASK                               (0x00001000U)
#define CSL_CSIRX_DPHY_STATUS_DL1_STOPSTATE_SHIFT                              (0x0000000CU)
#define CSL_CSIRX_DPHY_STATUS_DL1_STOPSTATE_MAX                                (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL1_ULPSACTIVENOT_MASK                           (0x00002000U)
#define CSL_CSIRX_DPHY_STATUS_DL1_ULPSACTIVENOT_SHIFT                          (0x0000000DU)
#define CSL_CSIRX_DPHY_STATUS_DL1_ULPSACTIVENOT_MAX                            (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL1_RXULPSESC_MASK                               (0x00004000U)
#define CSL_CSIRX_DPHY_STATUS_DL1_RXULPSESC_SHIFT                              (0x0000000EU)
#define CSL_CSIRX_DPHY_STATUS_DL1_RXULPSESC_MAX                                (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL2_STOPSTATE_MASK                               (0x00010000U)
#define CSL_CSIRX_DPHY_STATUS_DL2_STOPSTATE_SHIFT                              (0x00000010U)
#define CSL_CSIRX_DPHY_STATUS_DL2_STOPSTATE_MAX                                (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL2_ULPSACTIVENOT_MASK                           (0x00020000U)
#define CSL_CSIRX_DPHY_STATUS_DL2_ULPSACTIVENOT_SHIFT                          (0x00000011U)
#define CSL_CSIRX_DPHY_STATUS_DL2_ULPSACTIVENOT_MAX                            (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL2_RXULPSESC_MASK                               (0x00040000U)
#define CSL_CSIRX_DPHY_STATUS_DL2_RXULPSESC_SHIFT                              (0x00000012U)
#define CSL_CSIRX_DPHY_STATUS_DL2_RXULPSESC_MAX                                (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL3_STOPSTATE_MASK                               (0x00100000U)
#define CSL_CSIRX_DPHY_STATUS_DL3_STOPSTATE_SHIFT                              (0x00000014U)
#define CSL_CSIRX_DPHY_STATUS_DL3_STOPSTATE_MAX                                (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL3_ULPSACTIVENOT_MASK                           (0x00200000U)
#define CSL_CSIRX_DPHY_STATUS_DL3_ULPSACTIVENOT_SHIFT                          (0x00000015U)
#define CSL_CSIRX_DPHY_STATUS_DL3_ULPSACTIVENOT_MAX                            (0x00000001U)

#define CSL_CSIRX_DPHY_STATUS_DL3_RXULPSESC_MASK                               (0x00400000U)
#define CSL_CSIRX_DPHY_STATUS_DL3_RXULPSESC_SHIFT                              (0x00000016U)
#define CSL_CSIRX_DPHY_STATUS_DL3_RXULPSESC_MAX                                (0x00000001U)

/* DPHY_ERR_STATUS_IRQ */

#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL0_ERRSOTHS_IRQ_MASK                    (0x00000100U)
#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL0_ERRSOTHS_IRQ_SHIFT                   (0x00000008U)
#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL0_ERRSOTHS_IRQ_MAX                     (0x00000001U)

#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL1_ERRSOTHS_IRQ_MASK                    (0x00001000U)
#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL1_ERRSOTHS_IRQ_SHIFT                   (0x0000000CU)
#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL1_ERRSOTHS_IRQ_MAX                     (0x00000001U)

#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL2_ERRSOTHS_IRQ_MASK                    (0x00010000U)
#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL2_ERRSOTHS_IRQ_SHIFT                   (0x00000010U)
#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL2_ERRSOTHS_IRQ_MAX                     (0x00000001U)

#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL3_ERRSOTHS_IRQ_MASK                    (0x00100000U)
#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL3_ERRSOTHS_IRQ_SHIFT                   (0x00000014U)
#define CSL_CSIRX_DPHY_ERR_STATUS_IRQ_DL3_ERRSOTHS_IRQ_MAX                     (0x00000001U)

/* DPHY_ERR_IRQ_MASK_CFG */

#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL0_ERRSOTHS_IRQM_MASK                 (0x00000100U)
#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL0_ERRSOTHS_IRQM_SHIFT                (0x00000008U)
#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL0_ERRSOTHS_IRQM_MAX                  (0x00000001U)

#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL1_ERRSOTHS_IRQM_MASK                 (0x00001000U)
#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL1_ERRSOTHS_IRQM_SHIFT                (0x0000000CU)
#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL1_ERRSOTHS_IRQM_MAX                  (0x00000001U)

#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL2_ERRSOTHS_IRQM_MASK                 (0x00010000U)
#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL2_ERRSOTHS_IRQM_SHIFT                (0x00000010U)
#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL2_ERRSOTHS_IRQM_MAX                  (0x00000001U)

#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL3_ERRSOTHS_IRQM_MASK                 (0x00100000U)
#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL3_ERRSOTHS_IRQM_SHIFT                (0x00000014U)
#define CSL_CSIRX_DPHY_ERR_IRQ_MASK_CFG_DL3_ERRSOTHS_IRQM_MAX                  (0x00000001U)

/* INTEGRATION_DEBUG */

#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_WORD_COUNT_MASK                       (0x0000FFFFU)
#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_WORD_COUNT_SHIFT                      (0x00000000U)
#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_WORD_COUNT_MAX                        (0x0000FFFFU)

#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_DT_MASK                               (0x003F0000U)
#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_DT_SHIFT                              (0x00000010U)
#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_DT_MAX                                (0x0000003FU)

#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_VC_MASK                               (0x03C00000U)
#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_VC_SHIFT                              (0x00000016U)
#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_VC_MAX                                (0x0000000FU)

#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_FSM_STATE_MASK                        (0xF0000000U)
#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_FSM_STATE_SHIFT                       (0x0000001CU)
#define CSL_CSIRX_INTEGRATION_DEBUG_PROT_FSM_STATE_MAX                         (0x0000000FU)

/* ERROR_DEBUG */

#define CSL_CSIRX_ERROR_DEBUG_DT_MASK                                          (0x0000003FU)
#define CSL_CSIRX_ERROR_DEBUG_DT_SHIFT                                         (0x00000000U)
#define CSL_CSIRX_ERROR_DEBUG_DT_MAX                                           (0x0000003FU)

#define CSL_CSIRX_ERROR_DEBUG_VC_MASK                                          (0x000003C0U)
#define CSL_CSIRX_ERROR_DEBUG_VC_SHIFT                                         (0x00000006U)
#define CSL_CSIRX_ERROR_DEBUG_VC_MAX                                           (0x0000000FU)

#define CSL_CSIRX_ERROR_DEBUG_DATA_FIELD_MASK                                  (0xFFFF0000U)
#define CSL_CSIRX_ERROR_DEBUG_DATA_FIELD_SHIFT                                 (0x00000010U)
#define CSL_CSIRX_ERROR_DEBUG_DATA_FIELD_MAX                                   (0x0000FFFFU)

/* TEST_GENERIC */

#define CSL_CSIRX_TEST_GENERIC_CTRL_MASK                                       (0x0000FFFFU)
#define CSL_CSIRX_TEST_GENERIC_CTRL_SHIFT                                      (0x00000000U)
#define CSL_CSIRX_TEST_GENERIC_CTRL_MAX                                        (0x0000FFFFU)

#define CSL_CSIRX_TEST_GENERIC_STATUS_MASK                                     (0xFFFF0000U)
#define CSL_CSIRX_TEST_GENERIC_STATUS_SHIFT                                    (0x00000010U)
#define CSL_CSIRX_TEST_GENERIC_STATUS_MAX                                      (0x0000FFFFU)

/* STREAM0_CTRL */

#define CSL_CSIRX_STREAM0_CTRL_START_MASK                                      (0x00000001U)
#define CSL_CSIRX_STREAM0_CTRL_START_SHIFT                                     (0x00000000U)
#define CSL_CSIRX_STREAM0_CTRL_START_MAX                                       (0x00000001U)

#define CSL_CSIRX_STREAM0_CTRL_STOP_MASK                                       (0x00000002U)
#define CSL_CSIRX_STREAM0_CTRL_STOP_SHIFT                                      (0x00000001U)
#define CSL_CSIRX_STREAM0_CTRL_STOP_MAX                                        (0x00000001U)

#define CSL_CSIRX_STREAM0_CTRL_ABORT_MASK                                      (0x00000004U)
#define CSL_CSIRX_STREAM0_CTRL_ABORT_SHIFT                                     (0x00000002U)
#define CSL_CSIRX_STREAM0_CTRL_ABORT_MAX                                       (0x00000001U)

#define CSL_CSIRX_STREAM0_CTRL_SOFT_RST_MASK                                   (0x00000010U)
#define CSL_CSIRX_STREAM0_CTRL_SOFT_RST_SHIFT                                  (0x00000004U)
#define CSL_CSIRX_STREAM0_CTRL_SOFT_RST_MAX                                    (0x00000001U)

/* STREAM0_STATUS */

#define CSL_CSIRX_STREAM0_STATUS_PROTOCOL_FSM_MASK                             (0x00000003U)
#define CSL_CSIRX_STREAM0_STATUS_PROTOCOL_FSM_SHIFT                            (0x00000000U)
#define CSL_CSIRX_STREAM0_STATUS_PROTOCOL_FSM_MAX                              (0x00000003U)

#define CSL_CSIRX_STREAM0_STATUS_STREAM_FSM_MASK                               (0x000000F0U)
#define CSL_CSIRX_STREAM0_STATUS_STREAM_FSM_SHIFT                              (0x00000004U)
#define CSL_CSIRX_STREAM0_STATUS_STREAM_FSM_MAX                                (0x0000000FU)

#define CSL_CSIRX_STREAM0_STATUS_READY_STATE_MASK                              (0x00000100U)
#define CSL_CSIRX_STREAM0_STATUS_READY_STATE_SHIFT                             (0x00000008U)
#define CSL_CSIRX_STREAM0_STATUS_READY_STATE_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM0_STATUS_RUNNING_MASK                                  (0x80000000U)
#define CSL_CSIRX_STREAM0_STATUS_RUNNING_SHIFT                                 (0x0000001FU)
#define CSL_CSIRX_STREAM0_STATUS_RUNNING_MAX                                   (0x00000001U)

/* STREAM0_DATA_CFG */

#define CSL_CSIRX_STREAM0_DATA_CFG_DATATYPE_SELECT0_MASK                       (0x0000003FU)
#define CSL_CSIRX_STREAM0_DATA_CFG_DATATYPE_SELECT0_SHIFT                      (0x00000000U)
#define CSL_CSIRX_STREAM0_DATA_CFG_DATATYPE_SELECT0_MAX                        (0x0000003FU)

#define CSL_CSIRX_STREAM0_DATA_CFG_ENABLE_DT0_MASK                             (0x00000080U)
#define CSL_CSIRX_STREAM0_DATA_CFG_ENABLE_DT0_SHIFT                            (0x00000007U)
#define CSL_CSIRX_STREAM0_DATA_CFG_ENABLE_DT0_MAX                              (0x00000001U)

#define CSL_CSIRX_STREAM0_DATA_CFG_DATATYPE_SELECT1_MASK                       (0x00003F00U)
#define CSL_CSIRX_STREAM0_DATA_CFG_DATATYPE_SELECT1_SHIFT                      (0x00000008U)
#define CSL_CSIRX_STREAM0_DATA_CFG_DATATYPE_SELECT1_MAX                        (0x0000003FU)

#define CSL_CSIRX_STREAM0_DATA_CFG_ENABLE_DT1_MASK                             (0x00008000U)
#define CSL_CSIRX_STREAM0_DATA_CFG_ENABLE_DT1_SHIFT                            (0x0000000FU)
#define CSL_CSIRX_STREAM0_DATA_CFG_ENABLE_DT1_MAX                              (0x00000001U)

#define CSL_CSIRX_STREAM0_DATA_CFG_VC_SELECT_MASK                              (0xFFFF0000U)
#define CSL_CSIRX_STREAM0_DATA_CFG_VC_SELECT_SHIFT                             (0x00000010U)
#define CSL_CSIRX_STREAM0_DATA_CFG_VC_SELECT_MAX                               (0x0000FFFFU)

/* STREAM0_CFG */

#define CSL_CSIRX_STREAM0_CFG_INTERFACE_MODE_MASK                              (0x00000001U)
#define CSL_CSIRX_STREAM0_CFG_INTERFACE_MODE_SHIFT                             (0x00000000U)
#define CSL_CSIRX_STREAM0_CFG_INTERFACE_MODE_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM0_CFG_LS_LE_MODE_MASK                                  (0x00000002U)
#define CSL_CSIRX_STREAM0_CFG_LS_LE_MODE_SHIFT                                 (0x00000001U)
#define CSL_CSIRX_STREAM0_CFG_LS_LE_MODE_MAX                                   (0x00000001U)

#define CSL_CSIRX_STREAM0_CFG_NUM_PIXELS_MASK                                  (0x00000030U)
#define CSL_CSIRX_STREAM0_CFG_NUM_PIXELS_SHIFT                                 (0x00000004U)
#define CSL_CSIRX_STREAM0_CFG_NUM_PIXELS_MAX                                   (0x00000003U)

#define CSL_CSIRX_STREAM0_CFG_FIFO_MODE_MASK                                   (0x00000300U)
#define CSL_CSIRX_STREAM0_CFG_FIFO_MODE_SHIFT                                  (0x00000008U)
#define CSL_CSIRX_STREAM0_CFG_FIFO_MODE_MAX                                    (0x00000003U)

#define CSL_CSIRX_STREAM0_CFG_BPP_BYPASS_MASK                                  (0x00007000U)
#define CSL_CSIRX_STREAM0_CFG_BPP_BYPASS_SHIFT                                 (0x0000000CU)
#define CSL_CSIRX_STREAM0_CFG_BPP_BYPASS_MAX                                   (0x00000007U)

#define CSL_CSIRX_STREAM0_CFG_FIFO_FILL_MASK                                   (0xFFFF0000U)
#define CSL_CSIRX_STREAM0_CFG_FIFO_FILL_SHIFT                                  (0x00000010U)
#define CSL_CSIRX_STREAM0_CFG_FIFO_FILL_MAX                                    (0x0000FFFFU)

/* STREAM0_MONITOR_CTRL */

#define CSL_CSIRX_STREAM0_MONITOR_CTRL_LB_VC_MASK                              (0x0000000FU)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_LB_VC_SHIFT                             (0x00000000U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_LB_VC_MAX                               (0x0000000FU)

#define CSL_CSIRX_STREAM0_MONITOR_CTRL_LB_EN_MASK                              (0x00000010U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_LB_EN_SHIFT                             (0x00000004U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_LB_EN_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM0_MONITOR_CTRL_TIMER_VC_MASK                           (0x000001E0U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_TIMER_VC_SHIFT                          (0x00000005U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_TIMER_VC_MAX                            (0x0000000FU)

#define CSL_CSIRX_STREAM0_MONITOR_CTRL_TIMER_EN_MASK                           (0x00000200U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_TIMER_EN_SHIFT                          (0x00000009U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_TIMER_EN_MAX                            (0x00000001U)

#define CSL_CSIRX_STREAM0_MONITOR_CTRL_TIMER_EOF_MASK                          (0x00000400U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_TIMER_EOF_SHIFT                         (0x0000000AU)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_TIMER_EOF_MAX                           (0x00000001U)

#define CSL_CSIRX_STREAM0_MONITOR_CTRL_FRAME_MON_VC_MASK                       (0x00007800U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_FRAME_MON_VC_SHIFT                      (0x0000000BU)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_FRAME_MON_VC_MAX                        (0x0000000FU)

#define CSL_CSIRX_STREAM0_MONITOR_CTRL_FRAME_MON_EN_MASK                       (0x00008000U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_FRAME_MON_EN_SHIFT                      (0x0000000FU)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_FRAME_MON_EN_MAX                        (0x00000001U)

#define CSL_CSIRX_STREAM0_MONITOR_CTRL_FRAME_LENGTH_MASK                       (0xFFFF0000U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_FRAME_LENGTH_SHIFT                      (0x00000010U)
#define CSL_CSIRX_STREAM0_MONITOR_CTRL_FRAME_LENGTH_MAX                        (0x0000FFFFU)

/* STREAM0_MONITOR_FRAME */

#define CSL_CSIRX_STREAM0_MONITOR_FRAME_NB_MASK                                (0x0000FFFFU)
#define CSL_CSIRX_STREAM0_MONITOR_FRAME_NB_SHIFT                               (0x00000000U)
#define CSL_CSIRX_STREAM0_MONITOR_FRAME_NB_MAX                                 (0x0000FFFFU)

#define CSL_CSIRX_STREAM0_MONITOR_FRAME_PACKET_SIZE_MASK                       (0xFFFF0000U)
#define CSL_CSIRX_STREAM0_MONITOR_FRAME_PACKET_SIZE_SHIFT                      (0x00000010U)
#define CSL_CSIRX_STREAM0_MONITOR_FRAME_PACKET_SIZE_MAX                        (0x0000FFFFU)

/* STREAM0_MONITOR_LB */

#define CSL_CSIRX_STREAM0_MONITOR_LB_BYTE_COUNT_MASK                           (0x0000FFFFU)
#define CSL_CSIRX_STREAM0_MONITOR_LB_BYTE_COUNT_SHIFT                          (0x00000000U)
#define CSL_CSIRX_STREAM0_MONITOR_LB_BYTE_COUNT_MAX                            (0x0000FFFFU)

#define CSL_CSIRX_STREAM0_MONITOR_LB_LINE_COUNT_MASK                           (0xFFFF0000U)
#define CSL_CSIRX_STREAM0_MONITOR_LB_LINE_COUNT_SHIFT                          (0x00000010U)
#define CSL_CSIRX_STREAM0_MONITOR_LB_LINE_COUNT_MAX                            (0x0000FFFFU)

/* STREAM0_TIMER */

#define CSL_CSIRX_STREAM0_TIMER_COUNT_MASK                                     (0x01FFFFFFU)
#define CSL_CSIRX_STREAM0_TIMER_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CSIRX_STREAM0_TIMER_COUNT_MAX                                      (0x01FFFFFFU)

/* STREAM0_FCC_CFG */

#define CSL_CSIRX_STREAM0_FCC_CFG_FRAME_COUNT_START_MASK                       (0x0000FFFFU)
#define CSL_CSIRX_STREAM0_FCC_CFG_FRAME_COUNT_START_SHIFT                      (0x00000000U)
#define CSL_CSIRX_STREAM0_FCC_CFG_FRAME_COUNT_START_MAX                        (0x0000FFFFU)

#define CSL_CSIRX_STREAM0_FCC_CFG_FRAME_COUNT_STOP_MASK                        (0xFFFF0000U)
#define CSL_CSIRX_STREAM0_FCC_CFG_FRAME_COUNT_STOP_SHIFT                       (0x00000010U)
#define CSL_CSIRX_STREAM0_FCC_CFG_FRAME_COUNT_STOP_MAX                         (0x0000FFFFU)

/* STREAM0_FCC_CTRL */

#define CSL_CSIRX_STREAM0_FCC_CTRL_FCC_EN_MASK                                 (0x00000001U)
#define CSL_CSIRX_STREAM0_FCC_CTRL_FCC_EN_SHIFT                                (0x00000000U)
#define CSL_CSIRX_STREAM0_FCC_CTRL_FCC_EN_MAX                                  (0x00000001U)

#define CSL_CSIRX_STREAM0_FCC_CTRL_FCC_VC_MASK                                 (0x0000001EU)
#define CSL_CSIRX_STREAM0_FCC_CTRL_FCC_VC_SHIFT                                (0x00000001U)
#define CSL_CSIRX_STREAM0_FCC_CTRL_FCC_VC_MAX                                  (0x0000000FU)

#define CSL_CSIRX_STREAM0_FCC_CTRL_FRAME_COUNTER_MASK                          (0xFFFF0000U)
#define CSL_CSIRX_STREAM0_FCC_CTRL_FRAME_COUNTER_SHIFT                         (0x00000010U)
#define CSL_CSIRX_STREAM0_FCC_CTRL_FRAME_COUNTER_MAX                           (0x0000FFFFU)

/* STREAM0_FIFO_FILL_LVL */

#define CSL_CSIRX_STREAM0_FIFO_FILL_LVL_COUNT_MASK                             (0x000003FFU)
#define CSL_CSIRX_STREAM0_FIFO_FILL_LVL_COUNT_SHIFT                            (0x00000000U)
#define CSL_CSIRX_STREAM0_FIFO_FILL_LVL_COUNT_MAX                              (0x000003FFU)

#define CSL_CSIRX_STREAM0_FIFO_FILL_LVL_MODE_MASK                              (0x00003000U)
#define CSL_CSIRX_STREAM0_FIFO_FILL_LVL_MODE_SHIFT                             (0x0000000CU)
#define CSL_CSIRX_STREAM0_FIFO_FILL_LVL_MODE_MAX                               (0x00000003U)

/* STREAM1_CTRL */

#define CSL_CSIRX_STREAM1_CTRL_START_MASK                                      (0x00000001U)
#define CSL_CSIRX_STREAM1_CTRL_START_SHIFT                                     (0x00000000U)
#define CSL_CSIRX_STREAM1_CTRL_START_MAX                                       (0x00000001U)

#define CSL_CSIRX_STREAM1_CTRL_STOP_MASK                                       (0x00000002U)
#define CSL_CSIRX_STREAM1_CTRL_STOP_SHIFT                                      (0x00000001U)
#define CSL_CSIRX_STREAM1_CTRL_STOP_MAX                                        (0x00000001U)

#define CSL_CSIRX_STREAM1_CTRL_ABORT_MASK                                      (0x00000004U)
#define CSL_CSIRX_STREAM1_CTRL_ABORT_SHIFT                                     (0x00000002U)
#define CSL_CSIRX_STREAM1_CTRL_ABORT_MAX                                       (0x00000001U)

#define CSL_CSIRX_STREAM1_CTRL_SOFT_RST_MASK                                   (0x00000010U)
#define CSL_CSIRX_STREAM1_CTRL_SOFT_RST_SHIFT                                  (0x00000004U)
#define CSL_CSIRX_STREAM1_CTRL_SOFT_RST_MAX                                    (0x00000001U)

/* STREAM1_STATUS */

#define CSL_CSIRX_STREAM1_STATUS_PROTOCOL_FSM_MASK                             (0x00000003U)
#define CSL_CSIRX_STREAM1_STATUS_PROTOCOL_FSM_SHIFT                            (0x00000000U)
#define CSL_CSIRX_STREAM1_STATUS_PROTOCOL_FSM_MAX                              (0x00000003U)

#define CSL_CSIRX_STREAM1_STATUS_STREAM_FSM_MASK                               (0x000000F0U)
#define CSL_CSIRX_STREAM1_STATUS_STREAM_FSM_SHIFT                              (0x00000004U)
#define CSL_CSIRX_STREAM1_STATUS_STREAM_FSM_MAX                                (0x0000000FU)

#define CSL_CSIRX_STREAM1_STATUS_READY_STATE_MASK                              (0x00000100U)
#define CSL_CSIRX_STREAM1_STATUS_READY_STATE_SHIFT                             (0x00000008U)
#define CSL_CSIRX_STREAM1_STATUS_READY_STATE_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM1_STATUS_RUNNING_MASK                                  (0x80000000U)
#define CSL_CSIRX_STREAM1_STATUS_RUNNING_SHIFT                                 (0x0000001FU)
#define CSL_CSIRX_STREAM1_STATUS_RUNNING_MAX                                   (0x00000001U)

/* STREAM1_DATA_CFG */

#define CSL_CSIRX_STREAM1_DATA_CFG_DATATYPE_SELECT0_MASK                       (0x0000003FU)
#define CSL_CSIRX_STREAM1_DATA_CFG_DATATYPE_SELECT0_SHIFT                      (0x00000000U)
#define CSL_CSIRX_STREAM1_DATA_CFG_DATATYPE_SELECT0_MAX                        (0x0000003FU)

#define CSL_CSIRX_STREAM1_DATA_CFG_ENABLE_DT0_MASK                             (0x00000080U)
#define CSL_CSIRX_STREAM1_DATA_CFG_ENABLE_DT0_SHIFT                            (0x00000007U)
#define CSL_CSIRX_STREAM1_DATA_CFG_ENABLE_DT0_MAX                              (0x00000001U)

#define CSL_CSIRX_STREAM1_DATA_CFG_DATATYPE_SELECT1_MASK                       (0x00003F00U)
#define CSL_CSIRX_STREAM1_DATA_CFG_DATATYPE_SELECT1_SHIFT                      (0x00000008U)
#define CSL_CSIRX_STREAM1_DATA_CFG_DATATYPE_SELECT1_MAX                        (0x0000003FU)

#define CSL_CSIRX_STREAM1_DATA_CFG_ENABLE_DT1_MASK                             (0x00008000U)
#define CSL_CSIRX_STREAM1_DATA_CFG_ENABLE_DT1_SHIFT                            (0x0000000FU)
#define CSL_CSIRX_STREAM1_DATA_CFG_ENABLE_DT1_MAX                              (0x00000001U)

#define CSL_CSIRX_STREAM1_DATA_CFG_VC_SELECT_MASK                              (0xFFFF0000U)
#define CSL_CSIRX_STREAM1_DATA_CFG_VC_SELECT_SHIFT                             (0x00000010U)
#define CSL_CSIRX_STREAM1_DATA_CFG_VC_SELECT_MAX                               (0x0000FFFFU)

/* STREAM1_CFG */

#define CSL_CSIRX_STREAM1_CFG_INTERFACE_MODE_MASK                              (0x00000001U)
#define CSL_CSIRX_STREAM1_CFG_INTERFACE_MODE_SHIFT                             (0x00000000U)
#define CSL_CSIRX_STREAM1_CFG_INTERFACE_MODE_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM1_CFG_LS_LE_MODE_MASK                                  (0x00000002U)
#define CSL_CSIRX_STREAM1_CFG_LS_LE_MODE_SHIFT                                 (0x00000001U)
#define CSL_CSIRX_STREAM1_CFG_LS_LE_MODE_MAX                                   (0x00000001U)

#define CSL_CSIRX_STREAM1_CFG_NUM_PIXELS_MASK                                  (0x00000030U)
#define CSL_CSIRX_STREAM1_CFG_NUM_PIXELS_SHIFT                                 (0x00000004U)
#define CSL_CSIRX_STREAM1_CFG_NUM_PIXELS_MAX                                   (0x00000003U)

#define CSL_CSIRX_STREAM1_CFG_FIFO_MODE_MASK                                   (0x00000300U)
#define CSL_CSIRX_STREAM1_CFG_FIFO_MODE_SHIFT                                  (0x00000008U)
#define CSL_CSIRX_STREAM1_CFG_FIFO_MODE_MAX                                    (0x00000003U)

#define CSL_CSIRX_STREAM1_CFG_BPP_BYPASS_MASK                                  (0x00007000U)
#define CSL_CSIRX_STREAM1_CFG_BPP_BYPASS_SHIFT                                 (0x0000000CU)
#define CSL_CSIRX_STREAM1_CFG_BPP_BYPASS_MAX                                   (0x00000007U)

#define CSL_CSIRX_STREAM1_CFG_FIFO_FILL_MASK                                   (0xFFFF0000U)
#define CSL_CSIRX_STREAM1_CFG_FIFO_FILL_SHIFT                                  (0x00000010U)
#define CSL_CSIRX_STREAM1_CFG_FIFO_FILL_MAX                                    (0x0000FFFFU)

/* STREAM1_MONITOR_CTRL */

#define CSL_CSIRX_STREAM1_MONITOR_CTRL_LB_VC_MASK                              (0x0000000FU)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_LB_VC_SHIFT                             (0x00000000U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_LB_VC_MAX                               (0x0000000FU)

#define CSL_CSIRX_STREAM1_MONITOR_CTRL_LB_EN_MASK                              (0x00000010U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_LB_EN_SHIFT                             (0x00000004U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_LB_EN_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM1_MONITOR_CTRL_TIMER_VC_MASK                           (0x000001E0U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_TIMER_VC_SHIFT                          (0x00000005U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_TIMER_VC_MAX                            (0x0000000FU)

#define CSL_CSIRX_STREAM1_MONITOR_CTRL_TIMER_EN_MASK                           (0x00000200U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_TIMER_EN_SHIFT                          (0x00000009U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_TIMER_EN_MAX                            (0x00000001U)

#define CSL_CSIRX_STREAM1_MONITOR_CTRL_TIMER_EOF_MASK                          (0x00000400U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_TIMER_EOF_SHIFT                         (0x0000000AU)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_TIMER_EOF_MAX                           (0x00000001U)

#define CSL_CSIRX_STREAM1_MONITOR_CTRL_FRAME_MON_VC_MASK                       (0x00007800U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_FRAME_MON_VC_SHIFT                      (0x0000000BU)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_FRAME_MON_VC_MAX                        (0x0000000FU)

#define CSL_CSIRX_STREAM1_MONITOR_CTRL_FRAME_MON_EN_MASK                       (0x00008000U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_FRAME_MON_EN_SHIFT                      (0x0000000FU)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_FRAME_MON_EN_MAX                        (0x00000001U)

#define CSL_CSIRX_STREAM1_MONITOR_CTRL_FRAME_LENGTH_MASK                       (0xFFFF0000U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_FRAME_LENGTH_SHIFT                      (0x00000010U)
#define CSL_CSIRX_STREAM1_MONITOR_CTRL_FRAME_LENGTH_MAX                        (0x0000FFFFU)

/* STREAM1_MONITOR_FRAME */

#define CSL_CSIRX_STREAM1_MONITOR_FRAME_NB_MASK                                (0x0000FFFFU)
#define CSL_CSIRX_STREAM1_MONITOR_FRAME_NB_SHIFT                               (0x00000000U)
#define CSL_CSIRX_STREAM1_MONITOR_FRAME_NB_MAX                                 (0x0000FFFFU)

#define CSL_CSIRX_STREAM1_MONITOR_FRAME_PACKET_SIZE_MASK                       (0xFFFF0000U)
#define CSL_CSIRX_STREAM1_MONITOR_FRAME_PACKET_SIZE_SHIFT                      (0x00000010U)
#define CSL_CSIRX_STREAM1_MONITOR_FRAME_PACKET_SIZE_MAX                        (0x0000FFFFU)

/* STREAM1_MONITOR_LB */

#define CSL_CSIRX_STREAM1_MONITOR_LB_BYTE_COUNT_MASK                           (0x0000FFFFU)
#define CSL_CSIRX_STREAM1_MONITOR_LB_BYTE_COUNT_SHIFT                          (0x00000000U)
#define CSL_CSIRX_STREAM1_MONITOR_LB_BYTE_COUNT_MAX                            (0x0000FFFFU)

#define CSL_CSIRX_STREAM1_MONITOR_LB_LINE_COUNT_MASK                           (0xFFFF0000U)
#define CSL_CSIRX_STREAM1_MONITOR_LB_LINE_COUNT_SHIFT                          (0x00000010U)
#define CSL_CSIRX_STREAM1_MONITOR_LB_LINE_COUNT_MAX                            (0x0000FFFFU)

/* STREAM1_TIMER */

#define CSL_CSIRX_STREAM1_TIMER_COUNT_MASK                                     (0x01FFFFFFU)
#define CSL_CSIRX_STREAM1_TIMER_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CSIRX_STREAM1_TIMER_COUNT_MAX                                      (0x01FFFFFFU)

/* STREAM1_FCC_CFG */

#define CSL_CSIRX_STREAM1_FCC_CFG_FRAME_COUNT_START_MASK                       (0x0000FFFFU)
#define CSL_CSIRX_STREAM1_FCC_CFG_FRAME_COUNT_START_SHIFT                      (0x00000000U)
#define CSL_CSIRX_STREAM1_FCC_CFG_FRAME_COUNT_START_MAX                        (0x0000FFFFU)

#define CSL_CSIRX_STREAM1_FCC_CFG_FRAME_COUNT_STOP_MASK                        (0xFFFF0000U)
#define CSL_CSIRX_STREAM1_FCC_CFG_FRAME_COUNT_STOP_SHIFT                       (0x00000010U)
#define CSL_CSIRX_STREAM1_FCC_CFG_FRAME_COUNT_STOP_MAX                         (0x0000FFFFU)

/* STREAM1_FCC_CTRL */

#define CSL_CSIRX_STREAM1_FCC_CTRL_FCC_EN_MASK                                 (0x00000001U)
#define CSL_CSIRX_STREAM1_FCC_CTRL_FCC_EN_SHIFT                                (0x00000000U)
#define CSL_CSIRX_STREAM1_FCC_CTRL_FCC_EN_MAX                                  (0x00000001U)

#define CSL_CSIRX_STREAM1_FCC_CTRL_FCC_VC_MASK                                 (0x0000001EU)
#define CSL_CSIRX_STREAM1_FCC_CTRL_FCC_VC_SHIFT                                (0x00000001U)
#define CSL_CSIRX_STREAM1_FCC_CTRL_FCC_VC_MAX                                  (0x0000000FU)

#define CSL_CSIRX_STREAM1_FCC_CTRL_FRAME_COUNTER_MASK                          (0xFFFF0000U)
#define CSL_CSIRX_STREAM1_FCC_CTRL_FRAME_COUNTER_SHIFT                         (0x00000010U)
#define CSL_CSIRX_STREAM1_FCC_CTRL_FRAME_COUNTER_MAX                           (0x0000FFFFU)

/* STREAM1_FIFO_FILL_LVL */

#define CSL_CSIRX_STREAM1_FIFO_FILL_LVL_COUNT_MASK                             (0x000003FFU)
#define CSL_CSIRX_STREAM1_FIFO_FILL_LVL_COUNT_SHIFT                            (0x00000000U)
#define CSL_CSIRX_STREAM1_FIFO_FILL_LVL_COUNT_MAX                              (0x000003FFU)

#define CSL_CSIRX_STREAM1_FIFO_FILL_LVL_MODE_MASK                              (0x00003000U)
#define CSL_CSIRX_STREAM1_FIFO_FILL_LVL_MODE_SHIFT                             (0x0000000CU)
#define CSL_CSIRX_STREAM1_FIFO_FILL_LVL_MODE_MAX                               (0x00000003U)

/* STREAM2_CTRL */

#define CSL_CSIRX_STREAM2_CTRL_START_MASK                                      (0x00000001U)
#define CSL_CSIRX_STREAM2_CTRL_START_SHIFT                                     (0x00000000U)
#define CSL_CSIRX_STREAM2_CTRL_START_MAX                                       (0x00000001U)

#define CSL_CSIRX_STREAM2_CTRL_STOP_MASK                                       (0x00000002U)
#define CSL_CSIRX_STREAM2_CTRL_STOP_SHIFT                                      (0x00000001U)
#define CSL_CSIRX_STREAM2_CTRL_STOP_MAX                                        (0x00000001U)

#define CSL_CSIRX_STREAM2_CTRL_ABORT_MASK                                      (0x00000004U)
#define CSL_CSIRX_STREAM2_CTRL_ABORT_SHIFT                                     (0x00000002U)
#define CSL_CSIRX_STREAM2_CTRL_ABORT_MAX                                       (0x00000001U)

#define CSL_CSIRX_STREAM2_CTRL_SOFT_RST_MASK                                   (0x00000010U)
#define CSL_CSIRX_STREAM2_CTRL_SOFT_RST_SHIFT                                  (0x00000004U)
#define CSL_CSIRX_STREAM2_CTRL_SOFT_RST_MAX                                    (0x00000001U)

/* STREAM2_STATUS */

#define CSL_CSIRX_STREAM2_STATUS_PROTOCOL_FSM_MASK                             (0x00000003U)
#define CSL_CSIRX_STREAM2_STATUS_PROTOCOL_FSM_SHIFT                            (0x00000000U)
#define CSL_CSIRX_STREAM2_STATUS_PROTOCOL_FSM_MAX                              (0x00000003U)

#define CSL_CSIRX_STREAM2_STATUS_STREAM_FSM_MASK                               (0x000000F0U)
#define CSL_CSIRX_STREAM2_STATUS_STREAM_FSM_SHIFT                              (0x00000004U)
#define CSL_CSIRX_STREAM2_STATUS_STREAM_FSM_MAX                                (0x0000000FU)

#define CSL_CSIRX_STREAM2_STATUS_READY_STATE_MASK                              (0x00000100U)
#define CSL_CSIRX_STREAM2_STATUS_READY_STATE_SHIFT                             (0x00000008U)
#define CSL_CSIRX_STREAM2_STATUS_READY_STATE_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM2_STATUS_RUNNING_MASK                                  (0x80000000U)
#define CSL_CSIRX_STREAM2_STATUS_RUNNING_SHIFT                                 (0x0000001FU)
#define CSL_CSIRX_STREAM2_STATUS_RUNNING_MAX                                   (0x00000001U)

/* STREAM2_DATA_CFG */

#define CSL_CSIRX_STREAM2_DATA_CFG_DATATYPE_SELECT0_MASK                       (0x0000003FU)
#define CSL_CSIRX_STREAM2_DATA_CFG_DATATYPE_SELECT0_SHIFT                      (0x00000000U)
#define CSL_CSIRX_STREAM2_DATA_CFG_DATATYPE_SELECT0_MAX                        (0x0000003FU)

#define CSL_CSIRX_STREAM2_DATA_CFG_ENABLE_DT0_MASK                             (0x00000080U)
#define CSL_CSIRX_STREAM2_DATA_CFG_ENABLE_DT0_SHIFT                            (0x00000007U)
#define CSL_CSIRX_STREAM2_DATA_CFG_ENABLE_DT0_MAX                              (0x00000001U)

#define CSL_CSIRX_STREAM2_DATA_CFG_DATATYPE_SELECT1_MASK                       (0x00003F00U)
#define CSL_CSIRX_STREAM2_DATA_CFG_DATATYPE_SELECT1_SHIFT                      (0x00000008U)
#define CSL_CSIRX_STREAM2_DATA_CFG_DATATYPE_SELECT1_MAX                        (0x0000003FU)

#define CSL_CSIRX_STREAM2_DATA_CFG_ENABLE_DT1_MASK                             (0x00008000U)
#define CSL_CSIRX_STREAM2_DATA_CFG_ENABLE_DT1_SHIFT                            (0x0000000FU)
#define CSL_CSIRX_STREAM2_DATA_CFG_ENABLE_DT1_MAX                              (0x00000001U)

#define CSL_CSIRX_STREAM2_DATA_CFG_VC_SELECT_MASK                              (0xFFFF0000U)
#define CSL_CSIRX_STREAM2_DATA_CFG_VC_SELECT_SHIFT                             (0x00000010U)
#define CSL_CSIRX_STREAM2_DATA_CFG_VC_SELECT_MAX                               (0x0000FFFFU)

/* STREAM2_CFG */

#define CSL_CSIRX_STREAM2_CFG_INTERFACE_MODE_MASK                              (0x00000001U)
#define CSL_CSIRX_STREAM2_CFG_INTERFACE_MODE_SHIFT                             (0x00000000U)
#define CSL_CSIRX_STREAM2_CFG_INTERFACE_MODE_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM2_CFG_LS_LE_MODE_MASK                                  (0x00000002U)
#define CSL_CSIRX_STREAM2_CFG_LS_LE_MODE_SHIFT                                 (0x00000001U)
#define CSL_CSIRX_STREAM2_CFG_LS_LE_MODE_MAX                                   (0x00000001U)

#define CSL_CSIRX_STREAM2_CFG_NUM_PIXELS_MASK                                  (0x00000030U)
#define CSL_CSIRX_STREAM2_CFG_NUM_PIXELS_SHIFT                                 (0x00000004U)
#define CSL_CSIRX_STREAM2_CFG_NUM_PIXELS_MAX                                   (0x00000003U)

#define CSL_CSIRX_STREAM2_CFG_FIFO_MODE_MASK                                   (0x00000300U)
#define CSL_CSIRX_STREAM2_CFG_FIFO_MODE_SHIFT                                  (0x00000008U)
#define CSL_CSIRX_STREAM2_CFG_FIFO_MODE_MAX                                    (0x00000003U)

#define CSL_CSIRX_STREAM2_CFG_BPP_BYPASS_MASK                                  (0x00007000U)
#define CSL_CSIRX_STREAM2_CFG_BPP_BYPASS_SHIFT                                 (0x0000000CU)
#define CSL_CSIRX_STREAM2_CFG_BPP_BYPASS_MAX                                   (0x00000007U)

#define CSL_CSIRX_STREAM2_CFG_FIFO_FILL_MASK                                   (0xFFFF0000U)
#define CSL_CSIRX_STREAM2_CFG_FIFO_FILL_SHIFT                                  (0x00000010U)
#define CSL_CSIRX_STREAM2_CFG_FIFO_FILL_MAX                                    (0x0000FFFFU)

/* STREAM2_MONITOR_CTRL */

#define CSL_CSIRX_STREAM2_MONITOR_CTRL_LB_VC_MASK                              (0x0000000FU)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_LB_VC_SHIFT                             (0x00000000U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_LB_VC_MAX                               (0x0000000FU)

#define CSL_CSIRX_STREAM2_MONITOR_CTRL_LB_EN_MASK                              (0x00000010U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_LB_EN_SHIFT                             (0x00000004U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_LB_EN_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM2_MONITOR_CTRL_TIMER_VC_MASK                           (0x000001E0U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_TIMER_VC_SHIFT                          (0x00000005U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_TIMER_VC_MAX                            (0x0000000FU)

#define CSL_CSIRX_STREAM2_MONITOR_CTRL_TIMER_EN_MASK                           (0x00000200U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_TIMER_EN_SHIFT                          (0x00000009U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_TIMER_EN_MAX                            (0x00000001U)

#define CSL_CSIRX_STREAM2_MONITOR_CTRL_TIMER_EOF_MASK                          (0x00000400U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_TIMER_EOF_SHIFT                         (0x0000000AU)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_TIMER_EOF_MAX                           (0x00000001U)

#define CSL_CSIRX_STREAM2_MONITOR_CTRL_FRAME_MON_VC_MASK                       (0x00007800U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_FRAME_MON_VC_SHIFT                      (0x0000000BU)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_FRAME_MON_VC_MAX                        (0x0000000FU)

#define CSL_CSIRX_STREAM2_MONITOR_CTRL_FRAME_MON_EN_MASK                       (0x00008000U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_FRAME_MON_EN_SHIFT                      (0x0000000FU)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_FRAME_MON_EN_MAX                        (0x00000001U)

#define CSL_CSIRX_STREAM2_MONITOR_CTRL_FRAME_LENGTH_MASK                       (0xFFFF0000U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_FRAME_LENGTH_SHIFT                      (0x00000010U)
#define CSL_CSIRX_STREAM2_MONITOR_CTRL_FRAME_LENGTH_MAX                        (0x0000FFFFU)

/* STREAM2_MONITOR_FRAME */

#define CSL_CSIRX_STREAM2_MONITOR_FRAME_NB_MASK                                (0x0000FFFFU)
#define CSL_CSIRX_STREAM2_MONITOR_FRAME_NB_SHIFT                               (0x00000000U)
#define CSL_CSIRX_STREAM2_MONITOR_FRAME_NB_MAX                                 (0x0000FFFFU)

#define CSL_CSIRX_STREAM2_MONITOR_FRAME_PACKET_SIZE_MASK                       (0xFFFF0000U)
#define CSL_CSIRX_STREAM2_MONITOR_FRAME_PACKET_SIZE_SHIFT                      (0x00000010U)
#define CSL_CSIRX_STREAM2_MONITOR_FRAME_PACKET_SIZE_MAX                        (0x0000FFFFU)

/* STREAM2_MONITOR_LB */

#define CSL_CSIRX_STREAM2_MONITOR_LB_BYTE_COUNT_MASK                           (0x0000FFFFU)
#define CSL_CSIRX_STREAM2_MONITOR_LB_BYTE_COUNT_SHIFT                          (0x00000000U)
#define CSL_CSIRX_STREAM2_MONITOR_LB_BYTE_COUNT_MAX                            (0x0000FFFFU)

#define CSL_CSIRX_STREAM2_MONITOR_LB_LINE_COUNT_MASK                           (0xFFFF0000U)
#define CSL_CSIRX_STREAM2_MONITOR_LB_LINE_COUNT_SHIFT                          (0x00000010U)
#define CSL_CSIRX_STREAM2_MONITOR_LB_LINE_COUNT_MAX                            (0x0000FFFFU)

/* STREAM2_TIMER */

#define CSL_CSIRX_STREAM2_TIMER_COUNT_MASK                                     (0x01FFFFFFU)
#define CSL_CSIRX_STREAM2_TIMER_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CSIRX_STREAM2_TIMER_COUNT_MAX                                      (0x01FFFFFFU)

/* STREAM2_FCC_CFG */

#define CSL_CSIRX_STREAM2_FCC_CFG_FRAME_COUNT_START_MASK                       (0x0000FFFFU)
#define CSL_CSIRX_STREAM2_FCC_CFG_FRAME_COUNT_START_SHIFT                      (0x00000000U)
#define CSL_CSIRX_STREAM2_FCC_CFG_FRAME_COUNT_START_MAX                        (0x0000FFFFU)

#define CSL_CSIRX_STREAM2_FCC_CFG_FRAME_COUNT_STOP_MASK                        (0xFFFF0000U)
#define CSL_CSIRX_STREAM2_FCC_CFG_FRAME_COUNT_STOP_SHIFT                       (0x00000010U)
#define CSL_CSIRX_STREAM2_FCC_CFG_FRAME_COUNT_STOP_MAX                         (0x0000FFFFU)

/* STREAM2_FCC_CTRL */

#define CSL_CSIRX_STREAM2_FCC_CTRL_FCC_EN_MASK                                 (0x00000001U)
#define CSL_CSIRX_STREAM2_FCC_CTRL_FCC_EN_SHIFT                                (0x00000000U)
#define CSL_CSIRX_STREAM2_FCC_CTRL_FCC_EN_MAX                                  (0x00000001U)

#define CSL_CSIRX_STREAM2_FCC_CTRL_FCC_VC_MASK                                 (0x0000001EU)
#define CSL_CSIRX_STREAM2_FCC_CTRL_FCC_VC_SHIFT                                (0x00000001U)
#define CSL_CSIRX_STREAM2_FCC_CTRL_FCC_VC_MAX                                  (0x0000000FU)

#define CSL_CSIRX_STREAM2_FCC_CTRL_FRAME_COUNTER_MASK                          (0xFFFF0000U)
#define CSL_CSIRX_STREAM2_FCC_CTRL_FRAME_COUNTER_SHIFT                         (0x00000010U)
#define CSL_CSIRX_STREAM2_FCC_CTRL_FRAME_COUNTER_MAX                           (0x0000FFFFU)

/* STREAM2_FIFO_FILL_LVL */

#define CSL_CSIRX_STREAM2_FIFO_FILL_LVL_COUNT_MASK                             (0x000003FFU)
#define CSL_CSIRX_STREAM2_FIFO_FILL_LVL_COUNT_SHIFT                            (0x00000000U)
#define CSL_CSIRX_STREAM2_FIFO_FILL_LVL_COUNT_MAX                              (0x000003FFU)

#define CSL_CSIRX_STREAM2_FIFO_FILL_LVL_MODE_MASK                              (0x00003000U)
#define CSL_CSIRX_STREAM2_FIFO_FILL_LVL_MODE_SHIFT                             (0x0000000CU)
#define CSL_CSIRX_STREAM2_FIFO_FILL_LVL_MODE_MAX                               (0x00000003U)

/* STREAM3_CTRL */

#define CSL_CSIRX_STREAM3_CTRL_START_MASK                                      (0x00000001U)
#define CSL_CSIRX_STREAM3_CTRL_START_SHIFT                                     (0x00000000U)
#define CSL_CSIRX_STREAM3_CTRL_START_MAX                                       (0x00000001U)

#define CSL_CSIRX_STREAM3_CTRL_STOP_MASK                                       (0x00000002U)
#define CSL_CSIRX_STREAM3_CTRL_STOP_SHIFT                                      (0x00000001U)
#define CSL_CSIRX_STREAM3_CTRL_STOP_MAX                                        (0x00000001U)

#define CSL_CSIRX_STREAM3_CTRL_ABORT_MASK                                      (0x00000004U)
#define CSL_CSIRX_STREAM3_CTRL_ABORT_SHIFT                                     (0x00000002U)
#define CSL_CSIRX_STREAM3_CTRL_ABORT_MAX                                       (0x00000001U)

#define CSL_CSIRX_STREAM3_CTRL_SOFT_RST_MASK                                   (0x00000010U)
#define CSL_CSIRX_STREAM3_CTRL_SOFT_RST_SHIFT                                  (0x00000004U)
#define CSL_CSIRX_STREAM3_CTRL_SOFT_RST_MAX                                    (0x00000001U)

/* STREAM3_STATUS */

#define CSL_CSIRX_STREAM3_STATUS_PROTOCOL_FSM_MASK                             (0x00000003U)
#define CSL_CSIRX_STREAM3_STATUS_PROTOCOL_FSM_SHIFT                            (0x00000000U)
#define CSL_CSIRX_STREAM3_STATUS_PROTOCOL_FSM_MAX                              (0x00000003U)

#define CSL_CSIRX_STREAM3_STATUS_STREAM_FSM_MASK                               (0x000000F0U)
#define CSL_CSIRX_STREAM3_STATUS_STREAM_FSM_SHIFT                              (0x00000004U)
#define CSL_CSIRX_STREAM3_STATUS_STREAM_FSM_MAX                                (0x0000000FU)

#define CSL_CSIRX_STREAM3_STATUS_READY_STATE_MASK                              (0x00000100U)
#define CSL_CSIRX_STREAM3_STATUS_READY_STATE_SHIFT                             (0x00000008U)
#define CSL_CSIRX_STREAM3_STATUS_READY_STATE_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM3_STATUS_RUNNING_MASK                                  (0x80000000U)
#define CSL_CSIRX_STREAM3_STATUS_RUNNING_SHIFT                                 (0x0000001FU)
#define CSL_CSIRX_STREAM3_STATUS_RUNNING_MAX                                   (0x00000001U)

/* STREAM3_DATA_CFG */

#define CSL_CSIRX_STREAM3_DATA_CFG_DATATYPE_SELECT0_MASK                       (0x0000003FU)
#define CSL_CSIRX_STREAM3_DATA_CFG_DATATYPE_SELECT0_SHIFT                      (0x00000000U)
#define CSL_CSIRX_STREAM3_DATA_CFG_DATATYPE_SELECT0_MAX                        (0x0000003FU)

#define CSL_CSIRX_STREAM3_DATA_CFG_ENABLE_DT0_MASK                             (0x00000080U)
#define CSL_CSIRX_STREAM3_DATA_CFG_ENABLE_DT0_SHIFT                            (0x00000007U)
#define CSL_CSIRX_STREAM3_DATA_CFG_ENABLE_DT0_MAX                              (0x00000001U)

#define CSL_CSIRX_STREAM3_DATA_CFG_DATATYPE_SELECT1_MASK                       (0x00003F00U)
#define CSL_CSIRX_STREAM3_DATA_CFG_DATATYPE_SELECT1_SHIFT                      (0x00000008U)
#define CSL_CSIRX_STREAM3_DATA_CFG_DATATYPE_SELECT1_MAX                        (0x0000003FU)

#define CSL_CSIRX_STREAM3_DATA_CFG_ENABLE_DT1_MASK                             (0x00008000U)
#define CSL_CSIRX_STREAM3_DATA_CFG_ENABLE_DT1_SHIFT                            (0x0000000FU)
#define CSL_CSIRX_STREAM3_DATA_CFG_ENABLE_DT1_MAX                              (0x00000001U)

#define CSL_CSIRX_STREAM3_DATA_CFG_VC_SELECT_MASK                              (0xFFFF0000U)
#define CSL_CSIRX_STREAM3_DATA_CFG_VC_SELECT_SHIFT                             (0x00000010U)
#define CSL_CSIRX_STREAM3_DATA_CFG_VC_SELECT_MAX                               (0x0000FFFFU)

/* STREAM3_CFG */

#define CSL_CSIRX_STREAM3_CFG_INTERFACE_MODE_MASK                              (0x00000001U)
#define CSL_CSIRX_STREAM3_CFG_INTERFACE_MODE_SHIFT                             (0x00000000U)
#define CSL_CSIRX_STREAM3_CFG_INTERFACE_MODE_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM3_CFG_LS_LE_MODE_MASK                                  (0x00000002U)
#define CSL_CSIRX_STREAM3_CFG_LS_LE_MODE_SHIFT                                 (0x00000001U)
#define CSL_CSIRX_STREAM3_CFG_LS_LE_MODE_MAX                                   (0x00000001U)

#define CSL_CSIRX_STREAM3_CFG_NUM_PIXELS_MASK                                  (0x00000030U)
#define CSL_CSIRX_STREAM3_CFG_NUM_PIXELS_SHIFT                                 (0x00000004U)
#define CSL_CSIRX_STREAM3_CFG_NUM_PIXELS_MAX                                   (0x00000003U)

#define CSL_CSIRX_STREAM3_CFG_FIFO_MODE_MASK                                   (0x00000300U)
#define CSL_CSIRX_STREAM3_CFG_FIFO_MODE_SHIFT                                  (0x00000008U)
#define CSL_CSIRX_STREAM3_CFG_FIFO_MODE_MAX                                    (0x00000003U)

#define CSL_CSIRX_STREAM3_CFG_BPP_BYPASS_MASK                                  (0x00007000U)
#define CSL_CSIRX_STREAM3_CFG_BPP_BYPASS_SHIFT                                 (0x0000000CU)
#define CSL_CSIRX_STREAM3_CFG_BPP_BYPASS_MAX                                   (0x00000007U)

#define CSL_CSIRX_STREAM3_CFG_FIFO_FILL_MASK                                   (0xFFFF0000U)
#define CSL_CSIRX_STREAM3_CFG_FIFO_FILL_SHIFT                                  (0x00000010U)
#define CSL_CSIRX_STREAM3_CFG_FIFO_FILL_MAX                                    (0x0000FFFFU)

/* STREAM3_MONITOR_CTRL */

#define CSL_CSIRX_STREAM3_MONITOR_CTRL_LB_VC_MASK                              (0x0000000FU)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_LB_VC_SHIFT                             (0x00000000U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_LB_VC_MAX                               (0x0000000FU)

#define CSL_CSIRX_STREAM3_MONITOR_CTRL_LB_EN_MASK                              (0x00000010U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_LB_EN_SHIFT                             (0x00000004U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_LB_EN_MAX                               (0x00000001U)

#define CSL_CSIRX_STREAM3_MONITOR_CTRL_TIMER_VC_MASK                           (0x000001E0U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_TIMER_VC_SHIFT                          (0x00000005U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_TIMER_VC_MAX                            (0x0000000FU)

#define CSL_CSIRX_STREAM3_MONITOR_CTRL_TIMER_EN_MASK                           (0x00000200U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_TIMER_EN_SHIFT                          (0x00000009U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_TIMER_EN_MAX                            (0x00000001U)

#define CSL_CSIRX_STREAM3_MONITOR_CTRL_TIMER_EOF_MASK                          (0x00000400U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_TIMER_EOF_SHIFT                         (0x0000000AU)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_TIMER_EOF_MAX                           (0x00000001U)

#define CSL_CSIRX_STREAM3_MONITOR_CTRL_FRAME_MON_VC_MASK                       (0x00007800U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_FRAME_MON_VC_SHIFT                      (0x0000000BU)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_FRAME_MON_VC_MAX                        (0x0000000FU)

#define CSL_CSIRX_STREAM3_MONITOR_CTRL_FRAME_MON_EN_MASK                       (0x00008000U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_FRAME_MON_EN_SHIFT                      (0x0000000FU)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_FRAME_MON_EN_MAX                        (0x00000001U)

#define CSL_CSIRX_STREAM3_MONITOR_CTRL_FRAME_LENGTH_MASK                       (0xFFFF0000U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_FRAME_LENGTH_SHIFT                      (0x00000010U)
#define CSL_CSIRX_STREAM3_MONITOR_CTRL_FRAME_LENGTH_MAX                        (0x0000FFFFU)

/* STREAM3_MONITOR_FRAME */

#define CSL_CSIRX_STREAM3_MONITOR_FRAME_NB_MASK                                (0x0000FFFFU)
#define CSL_CSIRX_STREAM3_MONITOR_FRAME_NB_SHIFT                               (0x00000000U)
#define CSL_CSIRX_STREAM3_MONITOR_FRAME_NB_MAX                                 (0x0000FFFFU)

#define CSL_CSIRX_STREAM3_MONITOR_FRAME_PACKET_SIZE_MASK                       (0xFFFF0000U)
#define CSL_CSIRX_STREAM3_MONITOR_FRAME_PACKET_SIZE_SHIFT                      (0x00000010U)
#define CSL_CSIRX_STREAM3_MONITOR_FRAME_PACKET_SIZE_MAX                        (0x0000FFFFU)

/* STREAM3_MONITOR_LB */

#define CSL_CSIRX_STREAM3_MONITOR_LB_BYTE_COUNT_MASK                           (0x0000FFFFU)
#define CSL_CSIRX_STREAM3_MONITOR_LB_BYTE_COUNT_SHIFT                          (0x00000000U)
#define CSL_CSIRX_STREAM3_MONITOR_LB_BYTE_COUNT_MAX                            (0x0000FFFFU)

#define CSL_CSIRX_STREAM3_MONITOR_LB_LINE_COUNT_MASK                           (0xFFFF0000U)
#define CSL_CSIRX_STREAM3_MONITOR_LB_LINE_COUNT_SHIFT                          (0x00000010U)
#define CSL_CSIRX_STREAM3_MONITOR_LB_LINE_COUNT_MAX                            (0x0000FFFFU)

/* STREAM3_TIMER */

#define CSL_CSIRX_STREAM3_TIMER_COUNT_MASK                                     (0x01FFFFFFU)
#define CSL_CSIRX_STREAM3_TIMER_COUNT_SHIFT                                    (0x00000000U)
#define CSL_CSIRX_STREAM3_TIMER_COUNT_MAX                                      (0x01FFFFFFU)

/* STREAM3_FCC_CFG */

#define CSL_CSIRX_STREAM3_FCC_CFG_FRAME_COUNT_START_MASK                       (0x0000FFFFU)
#define CSL_CSIRX_STREAM3_FCC_CFG_FRAME_COUNT_START_SHIFT                      (0x00000000U)
#define CSL_CSIRX_STREAM3_FCC_CFG_FRAME_COUNT_START_MAX                        (0x0000FFFFU)

#define CSL_CSIRX_STREAM3_FCC_CFG_FRAME_COUNT_STOP_MASK                        (0xFFFF0000U)
#define CSL_CSIRX_STREAM3_FCC_CFG_FRAME_COUNT_STOP_SHIFT                       (0x00000010U)
#define CSL_CSIRX_STREAM3_FCC_CFG_FRAME_COUNT_STOP_MAX                         (0x0000FFFFU)

/* STREAM3_FCC_CTRL */

#define CSL_CSIRX_STREAM3_FCC_CTRL_FCC_EN_MASK                                 (0x00000001U)
#define CSL_CSIRX_STREAM3_FCC_CTRL_FCC_EN_SHIFT                                (0x00000000U)
#define CSL_CSIRX_STREAM3_FCC_CTRL_FCC_EN_MAX                                  (0x00000001U)

#define CSL_CSIRX_STREAM3_FCC_CTRL_FCC_VC_MASK                                 (0x0000001EU)
#define CSL_CSIRX_STREAM3_FCC_CTRL_FCC_VC_SHIFT                                (0x00000001U)
#define CSL_CSIRX_STREAM3_FCC_CTRL_FCC_VC_MAX                                  (0x0000000FU)

#define CSL_CSIRX_STREAM3_FCC_CTRL_FRAME_COUNTER_MASK                          (0xFFFF0000U)
#define CSL_CSIRX_STREAM3_FCC_CTRL_FRAME_COUNTER_SHIFT                         (0x00000010U)
#define CSL_CSIRX_STREAM3_FCC_CTRL_FRAME_COUNTER_MAX                           (0x0000FFFFU)

/* STREAM3_FIFO_FILL_LVL */

#define CSL_CSIRX_STREAM3_FIFO_FILL_LVL_COUNT_MASK                             (0x000003FFU)
#define CSL_CSIRX_STREAM3_FIFO_FILL_LVL_COUNT_SHIFT                            (0x00000000U)
#define CSL_CSIRX_STREAM3_FIFO_FILL_LVL_COUNT_MAX                              (0x000003FFU)

#define CSL_CSIRX_STREAM3_FIFO_FILL_LVL_MODE_MASK                              (0x00003000U)
#define CSL_CSIRX_STREAM3_FIFO_FILL_LVL_MODE_SHIFT                             (0x0000000CU)
#define CSL_CSIRX_STREAM3_FIFO_FILL_LVL_MODE_MAX                               (0x00000003U)

/* ASF_INT_STATUS */

#define CSL_CSIRX_ASF_INT_STATUS_ASF_SRAM_CORR_ERR_MASK                        (0x00000001U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_SRAM_CORR_ERR_SHIFT                       (0x00000000U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_SRAM_CORR_ERR_MAX                         (0x00000001U)

#define CSL_CSIRX_ASF_INT_STATUS_ASF_SRAM_UNCORR_ERR_MASK                      (0x00000002U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_SRAM_UNCORR_ERR_SHIFT                     (0x00000001U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_SRAM_UNCORR_ERR_MAX                       (0x00000001U)

#define CSL_CSIRX_ASF_INT_STATUS_ASF_DAP_ERR_MASK                              (0x00000004U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_DAP_ERR_SHIFT                             (0x00000002U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_DAP_ERR_MAX                               (0x00000001U)

#define CSL_CSIRX_ASF_INT_STATUS_ASF_CSR_ERR_MASK                              (0x00000008U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_CSR_ERR_SHIFT                             (0x00000003U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_CSR_ERR_MAX                               (0x00000001U)

#define CSL_CSIRX_ASF_INT_STATUS_ASF_TRANS_TO_ERR_MASK                         (0x00000010U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_TRANS_TO_ERR_SHIFT                        (0x00000004U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_TRANS_TO_ERR_MAX                          (0x00000001U)

#define CSL_CSIRX_ASF_INT_STATUS_ASF_PROTOCOL_ERR_MASK                         (0x00000020U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_PROTOCOL_ERR_SHIFT                        (0x00000005U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_PROTOCOL_ERR_MAX                          (0x00000001U)

#define CSL_CSIRX_ASF_INT_STATUS_ASF_INTEGRITY_ERR_MASK                        (0x00000040U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_INTEGRITY_ERR_SHIFT                       (0x00000006U)
#define CSL_CSIRX_ASF_INT_STATUS_ASF_INTEGRITY_ERR_MAX                         (0x00000001U)

#define CSL_CSIRX_ASF_INT_STATUS_RESERVED_31_7_MASK                            (0xFFFFFF80U)
#define CSL_CSIRX_ASF_INT_STATUS_RESERVED_31_7_SHIFT                           (0x00000007U)
#define CSL_CSIRX_ASF_INT_STATUS_RESERVED_31_7_MAX                             (0x01FFFFFFU)

/* ASF_INT_RAW_STATUS */

#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_SRAM_CORR_ERR_MASK                    (0x00000001U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_SRAM_CORR_ERR_SHIFT                   (0x00000000U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_SRAM_CORR_ERR_MAX                     (0x00000001U)

#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_SRAM_UNCORR_ERR_MASK                  (0x00000002U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_SRAM_UNCORR_ERR_SHIFT                 (0x00000001U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_SRAM_UNCORR_ERR_MAX                   (0x00000001U)

#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_DAP_ERR_MASK                          (0x00000004U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_DAP_ERR_SHIFT                         (0x00000002U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_DAP_ERR_MAX                           (0x00000001U)

#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_CSR_ERR_MASK                          (0x00000008U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_CSR_ERR_SHIFT                         (0x00000003U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_CSR_ERR_MAX                           (0x00000001U)

#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_TRANS_TO_ERR_MASK                     (0x00000010U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_TRANS_TO_ERR_SHIFT                    (0x00000004U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_TRANS_TO_ERR_MAX                      (0x00000001U)

#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_PROTOCOL_ERR_MASK                     (0x00000020U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_PROTOCOL_ERR_SHIFT                    (0x00000005U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_PROTOCOL_ERR_MAX                      (0x00000001U)

#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_INTEGRITY_ERR_MASK                    (0x00000040U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_INTEGRITY_ERR_SHIFT                   (0x00000006U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_ASF_INTEGRITY_ERR_MAX                     (0x00000001U)

#define CSL_CSIRX_ASF_INT_RAW_STATUS_RESERVED_31_7_MASK                        (0xFFFFFF80U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_RESERVED_31_7_SHIFT                       (0x00000007U)
#define CSL_CSIRX_ASF_INT_RAW_STATUS_RESERVED_31_7_MAX                         (0x01FFFFFFU)

/* ASF_INT_MASK */

#define CSL_CSIRX_ASF_INT_MASK_ASF_SRAM_CORR_ERR_MASK_MASK                     (0x00000001U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_SRAM_CORR_ERR_MASK_SHIFT                    (0x00000000U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_SRAM_CORR_ERR_MASK_MAX                      (0x00000001U)

#define CSL_CSIRX_ASF_INT_MASK_ASF_SRAM_UNCORR_ERR_MASK_MASK                   (0x00000002U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_SRAM_UNCORR_ERR_MASK_SHIFT                  (0x00000001U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_SRAM_UNCORR_ERR_MASK_MAX                    (0x00000001U)

#define CSL_CSIRX_ASF_INT_MASK_ASF_DAP_ERR_MASK_MASK                           (0x00000004U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_DAP_ERR_MASK_SHIFT                          (0x00000002U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_DAP_ERR_MASK_MAX                            (0x00000001U)

#define CSL_CSIRX_ASF_INT_MASK_ASF_CSR_ERR_MASK_MASK                           (0x00000008U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_CSR_ERR_MASK_SHIFT                          (0x00000003U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_CSR_ERR_MASK_MAX                            (0x00000001U)

#define CSL_CSIRX_ASF_INT_MASK_ASF_TRANS_TO_ERR_MASK_MASK                      (0x00000010U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_TRANS_TO_ERR_MASK_SHIFT                     (0x00000004U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_TRANS_TO_ERR_MASK_MAX                       (0x00000001U)

#define CSL_CSIRX_ASF_INT_MASK_ASF_PROTOCOL_ERR_MASK_MASK                      (0x00000020U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_PROTOCOL_ERR_MASK_SHIFT                     (0x00000005U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_PROTOCOL_ERR_MASK_MAX                       (0x00000001U)

#define CSL_CSIRX_ASF_INT_MASK_ASF_INTEGRITY_ERR_MASK_MASK                     (0x00000040U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_INTEGRITY_ERR_MASK_SHIFT                    (0x00000006U)
#define CSL_CSIRX_ASF_INT_MASK_ASF_INTEGRITY_ERR_MASK_MAX                      (0x00000001U)

#define CSL_CSIRX_ASF_INT_MASK_RESERVED_31_7_MASK                              (0xFFFFFF80U)
#define CSL_CSIRX_ASF_INT_MASK_RESERVED_31_7_SHIFT                             (0x00000007U)
#define CSL_CSIRX_ASF_INT_MASK_RESERVED_31_7_MAX                               (0x01FFFFFFU)

/* ASF_INT_TEST */

#define CSL_CSIRX_ASF_INT_TEST_ASF_SRAM_CORR_ERR_TEST_MASK                     (0x00000001U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_SRAM_CORR_ERR_TEST_SHIFT                    (0x00000000U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_SRAM_CORR_ERR_TEST_MAX                      (0x00000001U)

#define CSL_CSIRX_ASF_INT_TEST_ASF_SRAM_UNCORR_ERR_TEST_MASK                   (0x00000002U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_SRAM_UNCORR_ERR_TEST_SHIFT                  (0x00000001U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_SRAM_UNCORR_ERR_TEST_MAX                    (0x00000001U)

#define CSL_CSIRX_ASF_INT_TEST_ASF_DAP_ERR_TEST_MASK                           (0x00000004U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_DAP_ERR_TEST_SHIFT                          (0x00000002U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_DAP_ERR_TEST_MAX                            (0x00000001U)

#define CSL_CSIRX_ASF_INT_TEST_ASF_CSR_ERR_TEST_MASK                           (0x00000008U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_CSR_ERR_TEST_SHIFT                          (0x00000003U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_CSR_ERR_TEST_MAX                            (0x00000001U)

#define CSL_CSIRX_ASF_INT_TEST_ASF_TRANS_TO_ERR_TEST_MASK                      (0x00000010U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_TRANS_TO_ERR_TEST_SHIFT                     (0x00000004U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_TRANS_TO_ERR_TEST_MAX                       (0x00000001U)

#define CSL_CSIRX_ASF_INT_TEST_ASF_PROTOCOL_ERR_TEST_MASK                      (0x00000020U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_PROTOCOL_ERR_TEST_SHIFT                     (0x00000005U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_PROTOCOL_ERR_TEST_MAX                       (0x00000001U)

#define CSL_CSIRX_ASF_INT_TEST_ASF_INTEGRITY_ERR_TEST_MASK                     (0x00000040U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_INTEGRITY_ERR_TEST_SHIFT                    (0x00000006U)
#define CSL_CSIRX_ASF_INT_TEST_ASF_INTEGRITY_ERR_TEST_MAX                      (0x00000001U)

#define CSL_CSIRX_ASF_INT_TEST_RESERVED_31_7_MASK                              (0xFFFFFF80U)
#define CSL_CSIRX_ASF_INT_TEST_RESERVED_31_7_SHIFT                             (0x00000007U)
#define CSL_CSIRX_ASF_INT_TEST_RESERVED_31_7_MAX                               (0x01FFFFFFU)

/* ASF_FATAL_NONFATAL_SELECT */

#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_SRAM_CORR_ERR_MASK             (0x00000001U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_SRAM_CORR_ERR_SHIFT            (0x00000000U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_SRAM_CORR_ERR_MAX              (0x00000001U)

#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_SRAM_UNCORR_ERR_MASK           (0x00000002U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_SRAM_UNCORR_ERR_SHIFT          (0x00000001U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_SRAM_UNCORR_ERR_MAX            (0x00000001U)

#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_DAP_ERR_MASK                   (0x00000004U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_DAP_ERR_SHIFT                  (0x00000002U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_DAP_ERR_MAX                    (0x00000001U)

#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_CSR_ERR_MASK                   (0x00000008U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_CSR_ERR_SHIFT                  (0x00000003U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_CSR_ERR_MAX                    (0x00000001U)

#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_TRANS_TO_ERR_MASK              (0x00000010U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_TRANS_TO_ERR_SHIFT             (0x00000004U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_TRANS_TO_ERR_MAX               (0x00000001U)

#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_PROTOCOL_ERR_MASK              (0x00000020U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_PROTOCOL_ERR_SHIFT             (0x00000005U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_PROTOCOL_ERR_MAX               (0x00000001U)

#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_INTEGRITY_ERR_MASK             (0x00000040U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_INTEGRITY_ERR_SHIFT            (0x00000006U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_ASF_INTEGRITY_ERR_MAX              (0x00000001U)

#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_RESERVED_31_7_MASK                 (0xFFFFFF80U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_RESERVED_31_7_SHIFT                (0x00000007U)
#define CSL_CSIRX_ASF_FATAL_NONFATAL_SELECT_RESERVED_31_7_MAX                  (0x01FFFFFFU)

/* ASF_SRAM_CORR_FAULT_STATUS */

#define CSL_CSIRX_ASF_SRAM_CORR_FAULT_STATUS_ASF_SRAM_CORR_FAULT_ADDR_MASK     (0x00FFFFFFU)
#define CSL_CSIRX_ASF_SRAM_CORR_FAULT_STATUS_ASF_SRAM_CORR_FAULT_ADDR_SHIFT    (0x00000000U)
#define CSL_CSIRX_ASF_SRAM_CORR_FAULT_STATUS_ASF_SRAM_CORR_FAULT_ADDR_MAX      (0x00FFFFFFU)

#define CSL_CSIRX_ASF_SRAM_CORR_FAULT_STATUS_ASF_SRAM_CORR_FAULT_INST_MASK     (0xFF000000U)
#define CSL_CSIRX_ASF_SRAM_CORR_FAULT_STATUS_ASF_SRAM_CORR_FAULT_INST_SHIFT    (0x00000018U)
#define CSL_CSIRX_ASF_SRAM_CORR_FAULT_STATUS_ASF_SRAM_CORR_FAULT_INST_MAX      (0x000000FFU)

/* ASF_SRAM_UNCORR_FAULT_STATUS */

#define CSL_CSIRX_ASF_SRAM_UNCORR_FAULT_STATUS_ASF_SRAM_UNCORR_FAULT_ADDR_MASK (0x00FFFFFFU)
#define CSL_CSIRX_ASF_SRAM_UNCORR_FAULT_STATUS_ASF_SRAM_UNCORR_FAULT_ADDR_SHIFT (0x00000000U)
#define CSL_CSIRX_ASF_SRAM_UNCORR_FAULT_STATUS_ASF_SRAM_UNCORR_FAULT_ADDR_MAX  (0x00FFFFFFU)

#define CSL_CSIRX_ASF_SRAM_UNCORR_FAULT_STATUS_ASF_SRAM_UNCORR_FAULT_INST_MASK (0xFF000000U)
#define CSL_CSIRX_ASF_SRAM_UNCORR_FAULT_STATUS_ASF_SRAM_UNCORR_FAULT_INST_SHIFT (0x00000018U)
#define CSL_CSIRX_ASF_SRAM_UNCORR_FAULT_STATUS_ASF_SRAM_UNCORR_FAULT_INST_MAX  (0x000000FFU)

/* ASF_SRAM_FAULT_STATS */

#define CSL_CSIRX_ASF_SRAM_FAULT_STATS_ASF_SRAM_FAULT_CORR_STATS_MASK          (0x0000FFFFU)
#define CSL_CSIRX_ASF_SRAM_FAULT_STATS_ASF_SRAM_FAULT_CORR_STATS_SHIFT         (0x00000000U)
#define CSL_CSIRX_ASF_SRAM_FAULT_STATS_ASF_SRAM_FAULT_CORR_STATS_MAX           (0x0000FFFFU)

#define CSL_CSIRX_ASF_SRAM_FAULT_STATS_RESERVED_31_16_MASK                     (0xFFFF0000U)
#define CSL_CSIRX_ASF_SRAM_FAULT_STATS_RESERVED_31_16_SHIFT                    (0x00000010U)
#define CSL_CSIRX_ASF_SRAM_FAULT_STATS_RESERVED_31_16_MAX                      (0x0000FFFFU)

/* ASF_TRANS_TO_CTRL */

#define CSL_CSIRX_ASF_TRANS_TO_CTRL_ASF_TRANS_TO_CTRL_MASK                     (0x0000FFFFU)
#define CSL_CSIRX_ASF_TRANS_TO_CTRL_ASF_TRANS_TO_CTRL_SHIFT                    (0x00000000U)
#define CSL_CSIRX_ASF_TRANS_TO_CTRL_ASF_TRANS_TO_CTRL_MAX                      (0x0000FFFFU)

#define CSL_CSIRX_ASF_TRANS_TO_CTRL_ASF_TRANS_TO_EN_MASK                       (0x80000000U)
#define CSL_CSIRX_ASF_TRANS_TO_CTRL_ASF_TRANS_TO_EN_SHIFT                      (0x0000001FU)
#define CSL_CSIRX_ASF_TRANS_TO_CTRL_ASF_TRANS_TO_EN_MAX                        (0x00000001U)

/* ASF_TRANS_TO_FAULT_MASK */

#define CSL_CSIRX_ASF_TRANS_TO_FAULT_MASK_ASF_TRANS_TO_FAULT_0_MASK_MASK       (0x00000001U)
#define CSL_CSIRX_ASF_TRANS_TO_FAULT_MASK_ASF_TRANS_TO_FAULT_0_MASK_SHIFT      (0x00000000U)
#define CSL_CSIRX_ASF_TRANS_TO_FAULT_MASK_ASF_TRANS_TO_FAULT_0_MASK_MAX        (0x00000001U)

/* ASF_TRANS_TO_FAULT_STATUS */

#define CSL_CSIRX_ASF_TRANS_TO_FAULT_STATUS_ASF_TRANS_TO_FAULT_0_STATUS_MASK   (0x00000001U)
#define CSL_CSIRX_ASF_TRANS_TO_FAULT_STATUS_ASF_TRANS_TO_FAULT_0_STATUS_SHIFT  (0x00000000U)
#define CSL_CSIRX_ASF_TRANS_TO_FAULT_STATUS_ASF_TRANS_TO_FAULT_0_STATUS_MAX    (0x00000001U)

/* ASF_PROTOCOL_FAULT_MASK */

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_0_MASK_MASK       (0x00000001U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_0_MASK_SHIFT      (0x00000000U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_0_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_1_MASK_MASK       (0x00000002U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_1_MASK_SHIFT      (0x00000001U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_1_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_2_MASK_MASK       (0x00000004U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_2_MASK_SHIFT      (0x00000002U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_2_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_3_MASK_MASK       (0x00000008U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_3_MASK_SHIFT      (0x00000003U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_3_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_4_MASK_MASK       (0x00000010U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_4_MASK_SHIFT      (0x00000004U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_4_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_5_MASK_MASK       (0x00000020U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_5_MASK_SHIFT      (0x00000005U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_5_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_6_MASK_MASK       (0x00000040U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_6_MASK_SHIFT      (0x00000006U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_6_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_7_MASK_MASK       (0x00000080U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_7_MASK_SHIFT      (0x00000007U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_7_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_8_MASK_MASK       (0x00000100U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_8_MASK_SHIFT      (0x00000008U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_8_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_9_MASK_MASK       (0x00000200U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_9_MASK_SHIFT      (0x00000009U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_9_MASK_MAX        (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_10_MASK_MASK      (0x00000400U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_10_MASK_SHIFT     (0x0000000AU)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_10_MASK_MAX       (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_11_MASK_MASK      (0x00000800U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_11_MASK_SHIFT     (0x0000000BU)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_11_MASK_MAX       (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_12_MASK_MASK      (0x00001000U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_12_MASK_SHIFT     (0x0000000CU)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_12_MASK_MAX       (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_13_MASK_MASK      (0x00002000U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_13_MASK_SHIFT     (0x0000000DU)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_MASK_ASF_PROTOCOL_FAULT_13_MASK_MAX       (0x00000001U)

/* ASF_PROTOCOL_FAULT_STATUS */

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_0_STATUS_MASK   (0x00000001U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_0_STATUS_SHIFT  (0x00000000U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_0_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_1_STATUS_MASK   (0x00000002U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_1_STATUS_SHIFT  (0x00000001U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_1_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_2_STATUS_MASK   (0x00000004U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_2_STATUS_SHIFT  (0x00000002U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_2_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_3_STATUS_MASK   (0x00000008U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_3_STATUS_SHIFT  (0x00000003U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_3_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_4_STATUS_MASK   (0x00000010U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_4_STATUS_SHIFT  (0x00000004U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_4_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_5_STATUS_MASK   (0x00000020U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_5_STATUS_SHIFT  (0x00000005U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_5_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_6_STATUS_MASK   (0x00000040U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_6_STATUS_SHIFT  (0x00000006U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_6_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_7_STATUS_MASK   (0x00000080U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_7_STATUS_SHIFT  (0x00000007U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_7_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_8_STATUS_MASK   (0x00000100U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_8_STATUS_SHIFT  (0x00000008U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_8_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_9_STATUS_MASK   (0x00000200U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_9_STATUS_SHIFT  (0x00000009U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_9_STATUS_MAX    (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_10_STATUS_MASK  (0x00000400U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_10_STATUS_SHIFT (0x0000000AU)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_10_STATUS_MAX   (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_11_STATUS_MASK  (0x00000800U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_11_STATUS_SHIFT (0x0000000BU)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_11_STATUS_MAX   (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_12_STATUS_MASK  (0x00001000U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_12_STATUS_SHIFT (0x0000000CU)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_12_STATUS_MAX   (0x00000001U)

#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_13_STATUS_MASK  (0x00002000U)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_13_STATUS_SHIFT (0x0000000DU)
#define CSL_CSIRX_ASF_PROTOCOL_FAULT_STATUS_ASF_PROTOCOL_FAULT_13_STATUS_MAX   (0x00000001U)

/* ID_PROD_VER */

#define CSL_CSIRX_ID_PROD_VER_VERSION_ID_MASK                                  (0x0000FFFFU)
#define CSL_CSIRX_ID_PROD_VER_VERSION_ID_SHIFT                                 (0x00000000U)
#define CSL_CSIRX_ID_PROD_VER_VERSION_ID_MAX                                   (0x0000FFFFU)

#define CSL_CSIRX_ID_PROD_VER_PRODUCT_ID_MASK                                  (0xFFFF0000U)
#define CSL_CSIRX_ID_PROD_VER_PRODUCT_ID_SHIFT                                 (0x00000010U)
#define CSL_CSIRX_ID_PROD_VER_PRODUCT_ID_MAX                                   (0x0000FFFFU)

#ifdef __cplusplus
}
#endif
#endif

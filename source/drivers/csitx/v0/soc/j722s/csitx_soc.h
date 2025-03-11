/*
 *  Copyright (c) Texas Instruments Incorporated 2020-2025
 *  All rights reserved.
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
 *  \ingroup DRV_CSITX_MODULE
 *  \defgroup DRV_CSITX_SOC_MODULE CSITX SoC Config
 *            This is CSITX documentation specific to J7ES SoC
 *
 *  @{
 */

/**
 *  \file csitx_soc.h
 *
 *  \brief CSITX Low Level Driver SOC specific file.
 */

#ifndef CSITX_SOC_H_
#define CSITX_SOC_H_

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
 *  \anchor CSITX_InstanceId
 *  \name   CSITX Module Instance ID
 *  \brief  Different instances of CSI Tx Module instances.
 *
 *  @{
 */
/** \brief CSITX Module Instance ID: CSI2TX Module 0 */
#define CSITX_INSTANCE_ID_0               ((uint32_t) 0x0U)

/** \brief Maximum value of CSITX Module Instance */
#define CSITX_INSTANCE_ID_MAX             ((uint32_t)CSITX_INSTANCE_ID_0 + 1U)
/* @} */

/**
 *  \anchor CSITX_SocDetails
 *  \name   CSITX SoC integration details
 *  \brief  Different instances of CSI Tx transmit module supported in the Instance
 *          and their configuration/integration supported in the Instance.
 *
 *  @{
 */
/** \brief Total number of transmit processing streams available in the Instance. */
#define CSITX_NUM_STRMS_TX                       ((uint32_t) 1U)
/** \brief Total number of COLORBAR streams available in the Instance.
  *  Note: COLORBAR stream is only supported on 'CSITX_INSTANCE_ID_0' only. */
#define CSITX_NUM_STRMS_COLORBAR                 ((uint32_t) 1U)
/** \brief Total number of Loop-back streams available in the Instance. */
#define CSITX_NUM_STRMS_LPBK                     ((uint32_t) 1U)
/** \brief Number of transmit channels per CSITX instance */
#define CSITX_NUM_CH_TX                          ((uint32_t) 32U)
/** \brief Number of transmit channels per CSITX instance */
#define CSITX_NUM_CH_LPBK                        ((uint32_t) 4U)
/** \brief Number of transmit channels that can run in parallel in the Instance */
#define CSITX_NUM_CH_TX_MAX                      ((uint32_t) (CSITX_NUM_CH_TX *\
                                                        CSITX_INSTANCE_ID_MAX))
/** \brief Number of COLORBAR channels that can run in parallel in the Instance */
#define CSITX_NUM_CH_COLORBAR_MAX                ((uint32_t) 1U)
/** \brief Number of Loop-back channels that can run in parallel in the Instance.
  *  Note: Though each CSI instance have one loop-back stream,
  *        only one can be used in the Instance which can be configured
  *        on any instance. */
#define CSITX_NUM_CH_LPBK_MAX                    ((uint32_t) (CSITX_NUM_CH_LPBK * \
                                                             CSITX_NUM_STRMS_LPBK))
/** \brief Maximum number of channels that can be processed per CSITX module
  *        These many valid channel configurations can exists
  *        per CSITX DRV instance */
#define CSITX_NUM_CH_MAX         ((uint32_t) (CSITX_NUM_CH_TX +\
                                              CSITX_NUM_CH_COLORBAR_MAX +\
                                              CSITX_NUM_CH_LPBK_MAX))
/** \brief Defines total number of physical data lanes that can be used per
 *         CSITX instance */
#define CSITX_TX_DATA_LANES_MAX                  ((uint32_t)4U)
/** \brief Defines total number of physical clock lanes that can be used per
 *         CSITX instance */
#define CSITX_TX_CLK_LANES_MAX                   ((uint32_t)1U)
/** \brief Defines total number of VC configurations available CSITX instance */
#define CSITX_TX_VC_CFG_MAX                      ((uint32_t)16U)
/** \brief Defines total number of DT configurations available CSITX instance */
#define CSITX_TX_DT_CFG_MAX                      ((uint32_t)16U)
/** \brief Defines total number of streams available CSITX instance */
#define CSITX_TX_STRM_NUM_MAX                    ((uint32_t)4U)
/** \brief Defines total number of words for stream FIFO fill level
 *         1920 RAW12 format, 1920 * 12 / 32 = 720. */
#define CSITX_TX_STRM_FIFO_FILL_LVL              ((uint32_t)720U)
/** \brief Tx Stream ID */
#define CSITX_NUM_STRMS_TX_ID                    ((uint32_t) 0U)
/** \brief Color-bar Stream ID */
#define CSITX_NUM_STRMS_TX_COLORBAR              ((uint32_t) 1U)
/** \brief Re-transmit Stream 0 ID */
#define CSITX_NUM_STRMS_TX_RETRANS_0             ((uint32_t) 2U)
/** \brief Re-transmit Stream 1 ID */
#define CSITX_NUM_STRMS_TX_RETRANS_1             ((uint32_t) 3U)
/* @} */

#define CSI_TX_IF0_VBUS2APBCSI2TX_BASE      (CSL_CSI_TX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2TX_V2_BASE)
#define CSI_TX_IF0_TX_SHIM_CSI2TXIF_BASE    (CSL_CSI_TX_IF0_TX_SHIM_VBUSP_MMR_CSI2TXIF_V2_BASE)
#define CSI_TX_IF1_VBUS2APBCSI2TX_BASE      (CSL_CSI_TX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2TX_V2_BASE)
#define CSI_TX_IF1_TX_SHIM_CSI2TXIF_BASE    (CSL_CSI_TX_IF0_TX_SHIM_VBUSP_MMR_CSI2TXIF_V2_BASE)

/**
 *  \anchor Csitx_LaneBandSpeed
 *  \name   CSITX D-PHY lane band speed
 *  \brief  Lane band speed options for CSITX D-PHY.
 *
 *  @{
 */
/** \brief Lane Band Speed: 80 Mbps to 100 Mbps */
#define CSITX_LANE_BAND_SPEED_80_TO_100_MBPS              ((uint32_t) 0x00U)
/** \brief Lane Band Speed: 100 Mbps to 120 Mbps */
#define CSITX_LANE_BAND_SPEED_100_TO_120_MBPS             ((uint32_t) 0x01U)
/** \brief Lane Band Speed: 120 Mbps to 160 Mbps */
#define CSITX_LANE_BAND_SPEED_120_TO_160_MBPS             ((uint32_t) 0x02U)
/** \brief Lane Band Speed: 160 Mbps to 200 Mbps */
#define CSITX_LANE_BAND_SPEED_160_TO_200_MBPS             ((uint32_t) 0x03U)
/** \brief Lane Band Speed: 200 Mbps to 240 Mbps */
#define CSITX_LANE_BAND_SPEED_200_TO_240_MBPS             ((uint32_t) 0x04U)
/** \brief Lane Band Speed: 240 Mbps to 320 Mbps */
#define CSITX_LANE_BAND_SPEED_240_TO_320_MBPS             ((uint32_t) 0x05U)
/** \brief Lane Band Speed: 320 Mbps to 390 Mbps */
#define CSITX_LANE_BAND_SPEED_320_TO_390_MBPS             ((uint32_t) 0x06U)
/** \brief Lane Band Speed: 390 Mbps to 450 Mbps */
#define CSITX_LANE_BAND_SPEED_390_TO_450_MBPS             ((uint32_t) 0x07U)
/** \brief Lane Band Speed: 450 Mbps to 520 Mbps */
#define CSITX_LANE_BAND_SPEED_450_TO_510_MBPS             ((uint32_t) 0x08U)
/** \brief Lane Band Speed: 510 Mbps to 560 Mbps */
#define CSITX_LANE_BAND_SPEED_510_TO_560_MBPS             ((uint32_t) 0x09U)
/** \brief Lane Band Speed: 560 Mbps to 640 Mbps */
#define CSITX_LANE_BAND_SPEED_560_TO_640_MBPS             ((uint32_t) 0x0AU)
/** \brief Lane Band Speed: 640 Mbps to 690 Mbps */
#define CSITX_LANE_BAND_SPEED_640_TO_690_MBPS             ((uint32_t) 0x0BU)
/** \brief Lane Band Speed: 690 Mbps to 770 Mbps */
#define CSITX_LANE_BAND_SPEED_690_TO_770_MBPS             ((uint32_t) 0x0CU)
/** \brief Lane Band Speed: 770 Mbps to 870 Mbps */
#define CSITX_LANE_BAND_SPEED_770_TO_870_MBPS             ((uint32_t) 0x0DU)
/** \brief Lane Band Speed: 870 Mbps to 950 Mbps */
#define CSITX_LANE_BAND_SPEED_870_TO_950_MBPS             ((uint32_t) 0x0EU)
/** \brief Lane Band Speed: 950 Mbps to 1000 Mbps */
#define CSITX_LANE_BAND_SPEED_950_TO_1000_MBPS            ((uint32_t) 0x0FU)
/** \brief Lane Band Speed: 1000 Mbps to 1200 Mbps */
#define CSITX_LANE_BAND_SPEED_1000_TO_1200_MBPS           ((uint32_t) 0x10U)
/** \brief Lane Band Speed: 1200 Mbps to 1400 Mbps */
#define CSITX_LANE_BAND_SPEED_1200_TO_1400_MBPS           ((uint32_t) 0x11U)
/** \brief Lane Band Speed: 1400 Mbps to 1600 Mbps */
#define CSITX_LANE_BAND_SPEED_1400_TO_1600_MBPS           ((uint32_t) 0x12U)
/** \brief Lane Band Speed: 1600 Mbps to 1800 Mbps */
#define CSITX_LANE_BAND_SPEED_1600_TO_1800_MBPS           ((uint32_t) 0x13U)
/** \brief Lane Band Speed: 1800 Mbps to 2000 Mbps */
#define CSITX_LANE_BAND_SPEED_1800_TO_2000_MBPS           ((uint32_t) 0x14U)
/** \brief Lane Band Speed: 2000 Mbps to 2200 Mbps */
#define CSITX_LANE_BAND_SPEED_2000_TO_2200_MBPS           ((uint32_t) 0x15U)
/** \brief Lane Band Speed: 2200 Mbps to 2500 Mbps */
#define CSITX_LANE_BAND_SPEED_2200_TO_2500_MBPS           ((uint32_t) 0x16U)
/** \brief Lane Band Speed: Reserved */
#define CSITX_LANE_BAND_SPEED_RESERVED                    ((uint32_t) 0x17U)
/* @} */

/**
 *  \anchor Csitx_ClkMode
 *  \name   CSITX D-PHY clock mode
 *  \brief  clock mode for CSITX D-PHY.
 *
 *  @{
 */
/** \brief DPHY Clock Mode: Continuous */
#define CSITX_CLK_MODE_CONTINUOUS                         ((uint32_t) 0x0U)
/** \brief DPHY Clock Mode: Non-continuous */
#define CSITX_CLK_MODE_NON_CONTINUOUS                     ((uint32_t) 0x1U)
/* @} */

/**
 *  \anchor Csitx_DphyMode
 *  \name   CSITX D-PHY mode
 *  \brief  Operational mode for CSITX D-PHY lanes.
 *
 *  @{
 */
/** \brief DPHY Clock Mode: ultra low power */
#define CSITX_DPHY_MODE_ULP                               ((uint32_t) 0x0U)
/** \brief DPHY Clock Mode: high speed */
#define CSITX_DPHY_MODE_HIGH_SPEED                        ((uint32_t) 0x1U)
/** \brief DPHY Clock Mode: low power stop state*/
#define CSITX_DPHY_MODE_LOW_POWER                         ((uint32_t) 0x2U)
/* @} */

/** \brief CSITX DRV Numbers: Number of stream per CSI TX module */
#define CSITX_NUM_STREAM                             (1U)

/**
 *  \anchor CSITX_CoreIntrNum
 *  \name   CSITX Module Core Interrupts Numbers
 *  \brief  Interrupts numbers for CSI RX events.
 *
 *  @{
 */
/** \brief CSITX Module Core Interrupt Number: Module 0 Error Interrupt */
#define CSITX_CORE_INTR_NUM_MOD_0_TX_INTR                (CSLR_R5FSS0_CORE0_INTR_CSI_TX_IF0_CSI_INTERRUPT_0)
/** \brief CSITX Module Core Interrupt Number: Module 0 Info Interrupt */
#define CSITX_CORE_INTR_NUM_MOD_0_LVL_INTR               (CSLR_R5FSS0_CORE0_INTR_CSI_TX_IF0_CSI_LEVEL_0)

/* @} */

/**
 *  \anchor CSITX_StreamId
 *  \name   CSITX Stream ID
 *  \brief  CSI2 TX streams are hw entities that processes incoming frames and
 *          sends it to particular destination like DDR, VISS/VP and CSI2 TX.
 *          Mapping of streams to destination is fixed in the design and
 *          can not be changes runtime.
 *
 *  @{
 */
/** \brief CSITX Instance ID: transmit stream0 0 on CSI2TX Module 0 */
#define CSITX_STREAM_ID_INST_0_STRM_0                      ((uint32_t) 0x0U)
/** \brief CSITX Instance ID: Color-bar stream on CSI2TX Module 0 */
#define CSITX_STREAM_ID_INST_0_STRM_1                      ((uint32_t) 0x1U)
/** \brief CSITX Instance ID: CSI2RX loop-back 0 on CSI2TX Module 0 */
#define CSITX_STREAM_ID_INST_0_STRM_2                      ((uint32_t) 0x2U)
/** \brief CSITX Instance ID: CSI2RX loop-back 1 on CSI2TX Module 0 */
#define CSITX_STREAM_ID_INST_0_STRM_3                      ((uint32_t) 0x3U)
/** \brief CSITX Instance ID: transmit stream0 0 on CSI2TX Module 1 */
#define CSITX_STREAM_ID_INST_1_STRM_0                      ((uint32_t) 0x4U)
/** \brief CSITX Instance ID: Color-bar stream on CSI2TX Module 1 */
#define CSITX_STREAM_ID_INST_1_STRM_1                      ((uint32_t) 0x5U)
/** \brief CSITX Instance ID: CSI2RX loop-back 0 on CSI2TX Module 1 */
#define CSITX_STREAM_ID_INST_1_STRM_2                      ((uint32_t) 0x6U)
/** \brief CSITX Instance ID: CSI2RX loop-back 1 on CSI2TX Module 1 */
#define CSITX_STREAM_ID_INST_1_STRM_3                      ((uint32_t) 0x7U)

/* @} */
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  \brief D-PHY configuration structure.
 */
typedef struct
{
    uint32_t inst;
    /**< CSITX istance.
     *   See \ref CSITX_InstanceId for details */
    uint32_t psmClkFreqDiv;
    /**< PMA state machine clock frequency divider control.
     *   Valid values: 1 to 255 */
    uint32_t pllByteClkDiv;
    /**< Selects the byte clock divider value, by driving the
     *   cmnda_pll_byteclk_div signal to the analog.
     *   Valid values:
     *   0x01: Div 1
     *   0x02: Div 2
     *   0x04: Div 4
     *   0x08: Div 8
     *   0x10: Div 16
     *   0x20: Div 32 */
    uint32_t pwmCtrlDivLow;
    /**< Low division value setting for the gm PWM control divider.
     *   Valid values: 1 to 1023 */
    uint32_t pwmCtrlDivHigh;
    /**< High division value setting for the gm PWM control divider.
     *   Valid values: 1 to 1023 */
    uint32_t pllLockThreshold;
    /**< pllcnt lock threshold value for PLL lock detect module.
     *   Valid values: 1 to 65535 */
    uint32_t pllLockStart;
    /**< pllcnt start value for PLL lock detect module.
     *   Valid values: 1 to 65535 */
    uint32_t pllIpDiv;
    /**< PLL IP Divider value.
     *   This value is calculated in the driver. */
    uint32_t pllOpDiv;
    /**< PLL OP Divider value.
     *   This value is calculated in the driver */
    uint32_t pllFbDiv;
    /**< PLL IP Divider value.
     *   This value is calculated in the driver */
    uint32_t pllPd;
    /**< PLL PD value.
     *   0: Disable and 1: Enable */
    uint32_t laneBandSpeed;
    /**< Data rates for lane band control.
     *   This parameter is optional if valid value for 'laneSpeedMbps' is provided
     *   by the application i.e. 'laneSpeedMbps' is updated by the application
     *   after init to a valid value.
     *   See \ref Csitx_LaneBandSpeed for details */
    uint32_t waitBurstTime;
    /**< Tx clock exit time - Number of tx_byte_clk cycles corresponding to
     *   the HS clock exit time.
     *   Valid values: 1 to 255 */
    uint32_t txClkExitTime;
    /**< Wait Burst Time - Number of tx_byte_clk cycles corresponding to
     *   the inter HS burst gap.
     *   Valid values: 1 to 255 */
    uint32_t dlWkupTime;
    /**< D-PHY data lane wakeup time in ppi_tx_esc_clk cycles.
     *   Valid values: 1 to 65535 */
    uint32_t clWkupTime;
    /**< D-PHY clock lane wakeup time in ppi_tx_esc_clk cycles.
     *   Valid values: 1 to 65535 */
    uint32_t clkMode;
    /**< DPHY Clock Mode.
     *   See \ref Csitx_ClkMode for details */
    uint32_t dphyMode;
    /**< DPHY Mode.
     *   See \ref Csitx_DphyMode for details
     *   This parameter is only valid when 'clkMode' is
     *   'CSITX_CLK_MODE_NON_CONTINUOUS'. */
    uint32_t clSlewRateCtrl;
    /**< Slew Rate: Slew rate control for clock lane. Range [0-31]
     *   Slew Rate Control Values:
     *   value 0 is for minimum slew cap i.e faster slew rate
     *   value 31 is for maximum slew cap i.e slowest slew rate
     *   Default Slew Rate Control Values:
     *   For 80M to 1Gbps       : 27
     *   For 1Gbps to 1.5Gbps   : 7
     *   For 1.5Gbps to 2.5Gbps : 1 */
    uint32_t dlSlewRateCtrl;
    /**< Slew Rate: Slew rate control for data lane. Range [0-31]
     *   Slew Rate Control Values:
     *   value 0 is for minimum slew cap i.e faster slew rate
     *   value 31 is for maximum slew cap i.e slowest slew rate
     *   Default Slew Rate Control Values:
     *   For 80M to 1Gbps       : 27
     *   For 1Gbps to 1.5Gbps   : 7
     *   For 1.5Gbps to 2.5Gbps : 1 */
    uint32_t laneSpeedMbps;
    /**< Exact DPHY lane speed from the selected speed band in Megabits per sec.
     *   This parameter is set to default value during init time.
     *   If updated in the application after init, newly set value will be used
     *   for DPHY clock configurations.
     *   If this parameter is set by the application, then application
     *   need not to set 'laneBandSpeed' parameter as it will be auto-calculated
     *   in the driver during create time.
     */
} Csitx_DPhyCfg;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief Csitx_DPhyCfg structure init function.
 *
 *  \param dphyCfg          [IN] Pointer to #Csitx_DPhyCfg structure.
 *
 *  Note: If given 'dphyCfg.laneBandSpeed' does no match with pre-defined
 *        configurations, this API will default the DPHY parameters for 800 Mbps.
 *        Application should change the DPHY parameters (if needed) prior
 *        to calling 'Fvid2_create()'.
 *        Pre-defined configurations are supported for following lane-speeds:
 *        1. CSITX_LANE_BAND_SPEED_770_TO_870_MBPS
 *        2. CSITX_LANE_BAND_SPEED_1000_TO_1200_MBPS
 *        3. CSITX_LANE_BAND_SPEED_1400_TO_1600_MBPS
 *        4. CSITX_LANE_BAND_SPEED_2200_TO_2500_MBPS
 */
void Csitx_initDPhyCfgParams(Csitx_DPhyCfg *dphyCfg);
/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSITX_SOC_H_ */

/* @} */

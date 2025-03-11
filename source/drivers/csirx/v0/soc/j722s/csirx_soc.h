/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2025
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
 *  \ingroup DRV_CSIRX_MODULE
 *  \defgroup DRV_CSIRX_SOC_MODULE CSIRX SoC Config
 *            This is CSIRX documentation specific to J7ES SoC
 *
 *  @{
 */

/**
 *  \file csirx_soc.h
 *
 *  \brief CSIRX Low Level Driver SOC specific file.
 */

#ifndef CSIRX_SOC_H_
#define CSIRX_SOC_H_

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
 *  \anchor CSIRX_InstanceId
 *  \name   CSIRX Module Instance ID
 *  \brief  Different instances of CSI Rx Module instances.
 *
 *  @{
 */
/** \brief CSIRX Module Instance ID: CSI2RX Module 0 */
#define CSIRX_INSTANCE_ID_0                         ((uint32_t) 0x0U)
/** \brief CSIRX Module Instance ID: CSI2RX Module 1 */
#define CSIRX_INSTANCE_ID_1                         ((uint32_t) 0x1U)
/** \brief CSIRX Module Instance ID: CSI2RX Module 2 */
#define CSIRX_INSTANCE_ID_2                         ((uint32_t) 0x2U)
/** \brief CSIRX Module Instance ID: CSI2RX Module 4 */
#define CSIRX_INSTANCE_ID_3                         ((uint32_t) 0x3U)
/** \brief Maximum value of CSIRX Module Instance */
#define CSIRX_INSTANCE_ID_MAX                       ((uint32_t) 0x4U)

/* @} */

/** \brief CSIRX DRV Virtual Context: Number of virtual contexts per CSI RX port */
#define CSIRX_NUM_VIRTUAL_CONTEXT                   (8U)

/** \brief CSIRX DRV Numbers: Number of stream per CSI RX module */
/* TODO: This should be 'CSIRX_MAX_NUM_OF_STREAMS' when OTF is supported*/
/* Capture and Loop-back streams are supported */
#define CSIRX_NUM_STREAM                             (2U)
#define CSIRX_NUM_STREAM_MAX                         (4U)

/**
 *  \anchor CSIRX_SocDetails
 *  \name   CSIRX SoC integration details
 *  \brief  Different instances of CSI Rx capture module supported in the SoC
 *          and their configuration/integration supported in the SoC.
 *
 *  @{
 */
/** \brief Total number of capture processing streams available in the SoC. */
#define CSIRX_NUM_STRMS_CAPT                     CSIRX_INSTANCE_ID_MAX
/** \brief Total number of OTF(VP/VISS) streams available in the SoC.
  *  Note: OTF stream is only supported on 'CSIRX_INSTANCE_ID_0' only. */
#define CSIRX_NUM_STRMS_OTF                      ((uint32_t) 1U)
/** \brief Total number of Loop-back streams available in the SoC. */
#define CSIRX_NUM_STRMS_LPBK                     CSIRX_INSTANCE_ID_MAX
/** \brief Number of capture channels per CSIRX instance */
#define CSIRX_NUM_CH_CAPT                        ((uint32_t) 32U)
/** \brief Number of capture channels that can run in parallel in the SoC */
#define CSIRX_NUM_CH_CAPT_MAX         ((uint32_t) (CSIRX_NUM_CH_CAPT *\
                                                        CSIRX_INSTANCE_ID_MAX))
/** \brief Number of OTF channels that can run in parallel in the SoC */
#define CSIRX_NUM_CH_OTF_MAX                   ((uint32_t) 1U)
/** \brief Number of Loop-back channels that can run in parallel in the SoC.
  *  Note: Though each CSI instance have one loop-back stream,
  *        only one can be used in the SoC which can be configured
  *        on any instance. */
#define CSIRX_NUM_CH_LPBK_MAX                  ((uint32_t) 4U)
/** \brief Maximum number of channels that can be processed per CSIRX module
  *        These many valid channel configurations can exists
  *        per CSIRX DRV instance */
#define CSIRX_NUM_CH_MAX         ((uint32_t) (CSIRX_NUM_CH_CAPT +\
                                              CSIRX_NUM_CH_OTF_MAX +\
                                              CSIRX_NUM_CH_LPBK_MAX))
/** \brief Defines total number of physical data lanes that can be used per
 *         CSIRX instance */
#define CSIRX_CAPT_DATA_LANES_MAX                  ((uint32_t)4U)
/* @} */

/**
 *  \anchor Csirx_LaneBandSpeed
 *  \name   CSIRX D-PHY lane band speed
 *  \brief  Lane band speed options for CSIRX D-PHY.
 *
 *  @{
 */
/** \brief Lane Band Speed: 80 Mbps to 100 Mbps */
#define CSIRX_LANE_BAND_SPEED_80_TO_100_MBPS              ((uint32_t) 0x00U)
/** \brief Lane Band Speed: 100 Mbps to 120 Mbps */
#define CSIRX_LANE_BAND_SPEED_100_TO_120_MBPS             ((uint32_t) 0x01U)
/** \brief Lane Band Speed: 120 Mbps to 160 Mbps */
#define CSIRX_LANE_BAND_SPEED_120_TO_160_MBPS             ((uint32_t) 0x02U)
/** \brief Lane Band Speed: 160 Mbps to 200 Mbps */
#define CSIRX_LANE_BAND_SPEED_160_TO_200_MBPS             ((uint32_t) 0x03U)
/** \brief Lane Band Speed: 200 Mbps to 240 Mbps */
#define CSIRX_LANE_BAND_SPEED_200_TO_240_MBPS             ((uint32_t) 0x04U)
/** \brief Lane Band Speed: 240 Mbps to 280 Mbps */
#define CSIRX_LANE_BAND_SPEED_240_TO_280_MBPS             ((uint32_t) 0x05U)
/** \brief Lane Band Speed: 280 Mbps to 320 Mbps */
#define CSIRX_LANE_BAND_SPEED_280_TO_320_MBPS             ((uint32_t) 0x06U)
/** \brief Lane Band Speed: 320 Mbps to 360 Mbps */
#define CSIRX_LANE_BAND_SPEED_320_TO_360_MBPS             ((uint32_t) 0x07U)
/** \brief Lane Band Speed: 360 Mbps to 400 Mbps */
#define CSIRX_LANE_BAND_SPEED_360_TO_400_MBPS             ((uint32_t) 0x08U)
/** \brief Lane Band Speed: 400 Mbps to 480 Mbps */
#define CSIRX_LANE_BAND_SPEED_400_TO_480_MBPS             ((uint32_t) 0x09U)
/** \brief Lane Band Speed: 480 Mbps to 560 Mbps */
#define CSIRX_LANE_BAND_SPEED_480_TO_560_MBPS             ((uint32_t) 0x0AU)
/** \brief Lane Band Speed: 560 Mbps to 640 Mbps */
#define CSIRX_LANE_BAND_SPEED_560_TO_640_MBPS             ((uint32_t) 0x0BU)
/** \brief Lane Band Speed: 640 Mbps to 720 Mbps */
#define CSIRX_LANE_BAND_SPEED_640_TO_720_MBPS             ((uint32_t) 0x0CU)
/** \brief Lane Band Speed: 720 Mbps to 800 Mbps */
#define CSIRX_LANE_BAND_SPEED_720_TO_800_MBPS             ((uint32_t) 0x0DU)
/** \brief Lane Band Speed: 800 Mbps to 880 Mbps */
#define CSIRX_LANE_BAND_SPEED_800_TO_880_MBPS             ((uint32_t) 0x0EU)
/** \brief Lane Band Speed: 880 Mbps to 1040 Mbps */
#define CSIRX_LANE_BAND_SPEED_880_TO_1040_MBPS            ((uint32_t) 0x0FU)
/** \brief Lane Band Speed: 1040 Mbps to 1200 Mbps */
#define CSIRX_LANE_BAND_SPEED_1040_TO_1200_MBPS           ((uint32_t) 0x10U)
/** \brief Lane Band Speed: 1200 Mbps to 1350 Mbps */
#define CSIRX_LANE_BAND_SPEED_1200_TO_1350_MBPS           ((uint32_t) 0x11U)
/** \brief Lane Band Speed: 1350 Mbps to 1500 Mbps */
#define CSIRX_LANE_BAND_SPEED_1350_TO_1500_MBPS           ((uint32_t) 0x12U)
/** \brief Lane Band Speed: 1500 Mbps to 1750 Mbps */
#define CSIRX_LANE_BAND_SPEED_1500_TO_1750_MBPS           ((uint32_t) 0x13U)
/** \brief Lane Band Speed: 1750 Mbps to 2000 Mbps */
#define CSIRX_LANE_BAND_SPEED_1750_TO_2000_MBPS           ((uint32_t) 0x14U)
/** \brief Lane Band Speed: 2000 Mbps to 2250 Mbps */
#define CSIRX_LANE_BAND_SPEED_2000_TO_2250_MBPS           ((uint32_t) 0x15U)
/** \brief Lane Band Speed: 2250 Mbps to 2500 Mbps */
#define CSIRX_LANE_BAND_SPEED_2250_TO_2500_MBPS           ((uint32_t) 0x16U)
/** \brief Lane Band Speed: Reserved */
#define CSIRX_LANE_BAND_SPEED_RESERVED                    ((uint32_t) 0x17U)
/* @} */

/**
 *  \anchor CSIRX_CoreIntrNum
 *  \name   CSIRX Module Core Interrupts Numbers
 *  \brief  Interrupts numbers for CSI RX events.
 *
 *  @{
 */
/** \brief CSIRX Module Core Interrupt Number: Module 0 Error Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_0_ERR_INTR                \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF0_CSI_ERR_IRQ_0)
/** \brief CSIRX Module Core Interrupt Number: Module 0 Info Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_0_INFO_INTR               \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF0_CSI_IRQ_0)
/** \brief CSIRX Module Core Interrupt Number: Module 0 Level Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_0_LEVEL_INTR              \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF0_CSI_LEVEL_0)
/** \brief CSIRX Module Core Interrupt Number: Module 1 Error Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_1_ERR_INTR                \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF1_CSI_ERR_IRQ_0)
/** \brief CSIRX Module Core Interrupt Number: Module 1 Info Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_1_INFO_INTR               \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF1_CSI_IRQ_0)
/** \brief CSIRX Module Core Interrupt Number: Module 1 Level Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_1_LEVEL_INTR              \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF1_CSI_LEVEL_0)
/** \brief CSIRX Module Core Interrupt Number: Module 2 Error Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_2_ERR_INTR                \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF2_CSI_ERR_IRQ_0)
/** \brief CSIRX Module Core Interrupt Number: Module 2 Info Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_2_INFO_INTR               \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF2_CSI_IRQ_0)
/** \brief CSIRX Module Core Interrupt Number: Module 2 Level Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_2_LEVEL_INTR              \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF2_CSI_LEVEL_0)
/** \brief CSIRX Module Core Interrupt Number: Module 2 Error Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_3_ERR_INTR                \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF3_CSI_ERR_IRQ_0)
/** \brief CSIRX Module Core Interrupt Number: Module 2 Info Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_3_INFO_INTR               \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF3_CSI_IRQ_0)
/** \brief CSIRX Module Core Interrupt Number: Module 2 Level Interrupt */
#define CSIRX_CORE_INTR_NUM_MOD_3_LEVEL_INTR              \
                            (CSLR_R5FSS0_CORE0_INTR_CSI_RX_IF3_CSI_LEVEL_0)

/* @} */


/** \brief Output bus width from CSIRX core in bits */
#define CSIRX_CORE_PIXEL_OUTPUT_BUS_WIDTH                    (32U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  \brief D-PHY configuration structure.
 */
typedef struct
{
    uint32_t inst;
    /**< CSIRX istance.
     *   See \ref CSIRX_InstanceId for details */
    uint32_t psmClkFreqDiv;
    /**< PMA state machine clock frequency divider control.
     *   Valid values: 1 to 255 */
    uint32_t leftLaneBandSpeed;
    /**< Data rates for left lane band control.
     *   See \ref Csirx_LaneBandSpeed for details */
    uint32_t rightLaneBandSpeed;
    /**< Data rates for left lane band control.
     *   See \ref Csirx_LaneBandSpeed for details */
    uint32_t bandGapTimerVal;
    /**< PMA state machine clock frequency divider control.
     *   Valid values: 0 to 255 */
} Csirx_DPhyCfg;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief Csirx_DPhyCfg structure init function. Called through
 *         'IOCTL_CSIRX_SET_DPHY_CONFIG' IOCTL.
 *
 *  \param dphyCfg          [IN] Pointer to #Csirx_DPhyCfg structure.
 *
 */
static inline void Csirx_initDPhyCfg(Csirx_DPhyCfg *dphyCfg);

void CsirxDrv_dphyrxWrapPsmClockConfig(uint32_t addr, uint32_t value);

void CsirxDrv_dphyrxCorePpiClockConfig(uint32_t addr,
                                       const Csirx_DPhyCfg *dphyCfg);

void CsirxDrv_dphyrxCoreLaneReady(uint32_t addr, uint32_t numLanes);

void CsirxDrv_dphyrxCoreCommonReady(uint32_t addr);

int32_t CsirxDrv_checkDphyrxConfig(const Csirx_DPhyCfg *programmedCfg,
                                   const Csirx_DPhyCfg *newCfg);

void CsirxDrv_dphyrxPsoDisable(uint32_t addr, uint32_t value);

void CsirxDrv_dphyCommonReset(uint32_t addr, uint32_t value);

void CsirxDrv_dphyrxSetLaneBandSpeed(uint32_t addr,
                                     const Csirx_DPhyCfg *dphyCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */
static inline void Csirx_initDPhyCfg(Csirx_DPhyCfg *dphyCfg)
{
    dphyCfg->inst               = CSIRX_INSTANCE_ID_0;
    dphyCfg->psmClkFreqDiv      = 0x53;
    dphyCfg->leftLaneBandSpeed  = CSIRX_LANE_BAND_SPEED_1350_TO_1500_MBPS;
    dphyCfg->rightLaneBandSpeed = CSIRX_LANE_BAND_SPEED_1350_TO_1500_MBPS;
    dphyCfg->bandGapTimerVal     = 0x14;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSIRX_SOC_H_ */

/* @} */

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
 *  \file csirx_soc.c
 *
 *  \brief File containing the SOC related configuration functions for CSIRX.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/csirx.h>
#include "csirx_socPriv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief DPHY configuration related macros: Register offsets */
#define DPHYRX_WRAP_REGS_LANE		                          ((uint32_t)0)
#define	DPHYRX_PCS_TX_DIG_TBIT0                               ((uint32_t)0xb00)
#define	DPHYRX_PCS_TX_DIG_TBIT2                               ((uint32_t)0xb08)
#define	DPHYRX_PCS_TX_DIG_TBIT3                               ((uint32_t)0xb0c)
#define	DPHYRX_CMN0_CMN_DIG_TBIT2                             ((uint32_t)0x20)
#define	DPHYRX_ISO_PHY_ISO_CL_CNTRL_L                         ((uint32_t)0xc10)
#define	DPHYRX_ISO_PHY_ISO_DL_CTRL_L0                         ((uint32_t)0xc14)
#define	DPHYRX_ISO_PHY_ISO_DL_CTRL_L1                         ((uint32_t)0xc20)
#define	DPHYRX_ISO_LDD_PHY_ISO_DL_CTRL_L2                     ((uint32_t)0xc30)
#define	DPHYRX_ISO_LDD_PHY_ISO_DL_CTRL_L3                     ((uint32_t)0xc3c)
#define	DPHYRX_CMN0_CMN_DIG_TBIT56                            ((uint32_t)0xF0)
#define	DPHYRX_CMN0_CMN_DIG_TBIT35                            ((uint32_t)0xA4)
#define	DPHYRX_CMN0_CMN_DIG_TBIT36                            ((uint32_t)0xA8)

/** \brief DPHY configuration related macros:
           Register bit-field shifts and masks */
#define DPHYRX_WRAP_REGS_LANE_PSM_CLK_FREQ_MSB                ((uint32_t)23U)
#define DPHYRX_WRAP_REGS_LANE_PSM_CLK_FREQ_LSB                ((uint32_t)16U)
#define	DPHYRX_CMN0_CMN_DIG_TBIT2_STARTUP_SM_EN_SHIFT         ((uint32_t)0U)
#define	DPHYRX_CMN0_CMN_DIG_TBIT2_BANDGAP_TIMER_SHIFT         ((uint32_t)1U)
#define	DPHYRX_CMN0_CMN_DIG_TBIT2_TX_SM_EN_SHIFT              ((uint32_t)9U)
#define	DPHYRX_CMN0_CMN_DIG_TBIT2_RX_SM_EN_SHIFT              ((uint32_t)10U)
#define	DPHYRX_PCS_TX_DIG_TBIT0_LEFT_BAND_SHIFT               ((uint32_t)0U)
#define	DPHYRX_PCS_TX_DIG_TBIT0_RIGHT_BAND_SHIFT              ((uint32_t)5U)
#define	DPHYRX_CMN0_CMN_DIG_TBIT36_OSC_RATE_SHIFT             ((uint32_t)1U)
#define	DPHYRX_CMN0_CMN_DIG_TBIT35_1P5G_CNT_START_VAL_SHIFT   ((uint32_t)0U)
#define	DPHYRX_CMN0_CMN_DIG_TBIT35_1P5G_CNT_START_VAL_SHIFT   ((uint32_t)0U)
#define	DPHYRX_CMN0_CMN_DIG_TBIT35_1P5G_CNT_START_VAL_MAX     ((uint32_t)0xFFFU)
#define	DPHYRX_CMN0_CMN_DIG_TBIT35_2P5G_CNT_START_VAL_SHIFT   ((uint32_t)12U)
#define	DPHYRX_CMN0_CMN_DIG_TBIT35_2P5G_CNT_START_VAL_MAX     ((uint32_t)0xFFFU)
#define	DPHYRX_PCS_TX_DIG_TBIT3_CLK_LANE_LEFT_SHIFT           ((uint32_t)0U)
#define	DPHYRX_PCS_TX_DIG_TBIT3_CLK_LANE_LEFT_MASK            ((uint32_t)0xFU)
#define	DPHYRX_PCS_TX_DIG_TBIT3_CLK_LANE_RIGHT_SHIFT          ((uint32_t)4U)
#define	DPHYRX_PCS_TX_DIG_TBIT3_CLK_LANE_RIGHT_MASK           ((uint32_t)0xFU)

/* DPHY WRAP Register details */
#define	CSL_DPHY_RX_MMR_SLV                                   ((uint32_t)0x1000U)
#define	CSL_DPHY_RX_MMR_SLV_LANE                              ((uint32_t)0x0U)
#define	CSL_DPHY_RX_MMR_SLV_LANE_CMN_READY_SHIFT              ((uint32_t)30U)
#define	CSL_DPHY_RX_MMR_SLV_LANE_CMN_READY_MASK               ((uint32_t)0x40000000U)
#define	CSL_DPHY_RX_MMR_SLV_LANE_LANE_RSTB_CMN_SHIFT          ((uint32_t)23U)
#define	CSL_DPHY_RX_MMR_SLV_LANE_LANE_RSTB_CMN_MASK           ((uint32_t)0x00800000U)

#define	DPHYRX_1_LANES_READY_CHECK             \
                  (CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_CL_CNTRL_L) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_DL_CTRL_L0) & \
                    0x1U)
#define	DPHYRX_2_LANES_READY_CHECK             \
                  (CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_CL_CNTRL_L) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_DL_CTRL_L0) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_DL_CTRL_L1) & \
                    0x1U)
#define	DPHYRX_3_LANES_READY_CHECK             \
                  (CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_CL_CNTRL_L) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_DL_CTRL_L0) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_DL_CTRL_L1) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_LDD_PHY_ISO_DL_CTRL_L2) & \
                    0x1U)
#define	DPHYRX_4_LANES_READY_CHECK             \
                  (CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_CL_CNTRL_L) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_DL_CTRL_L0) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_PHY_ISO_DL_CTRL_L1) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_LDD_PHY_ISO_DL_CTRL_L2) & \
                    CSL_REG32_RD(addr + DPHYRX_ISO_LDD_PHY_ISO_DL_CTRL_L3) & \
                    0x1U)

#define	DPHYRX_PCS_TX_DIG_TBIT2_PRG_VAL               ((uint32_t)0xAAAAAAAAU)
#define	DPHYRX_PCS_TX_DIG_TBIT3_PRG_VAL               ((uint32_t)0x2AAU)

/* Configure Rx Osc calibration feedback clock counter start values */
/* It is 500MHz / 6 */
#define	DPHYRX_PSM_CLK_FREQ_MHZ                      (83.33f)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Done */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void CsirxDrv_initPlatData(Csirx_PlatformData *platformData)
{
    uint32_t loopCnt = 0U, instId = 0U, strmId = 0U;

    platformData->numInstances = CSIRX_INSTANCE_ID_MAX;
    platformData->numCaptCh = CSIRX_NUM_CH_CAPT_MAX;
    platformData->numOtfCh = CSIRX_NUM_CH_OTF_MAX;
    platformData->numLpbkfCh = CSIRX_NUM_CH_LPBK_MAX;
    platformData->numCaptStrms = CSIRX_NUM_STRMS_CAPT;
    platformData->numOtfStrms = CSIRX_NUM_STRMS_OTF;
    platformData->numLpbkfStrms = CSIRX_NUM_STRMS_LPBK;
    /* Initialize type and support status to default for all streams */
    for (instId = 0U ; instId < CSIRX_INSTANCE_ID_MAX ; instId++)
    {
        for (loopCnt = 0U ; loopCnt < CSIRX_MAX_NUM_OF_STREAMS ; loopCnt++)
        {
            platformData->strmStatus[instId][loopCnt] =
                                            CSIRX_STRM_SUPPORT_NOT_SUPPORTED;
            platformData->strmType[instId][loopCnt] = CSIRX_CH_TYPE_CAPT;
        }
    }
    /* Update info only for supported streams: instance 0 */
    instId = 0U;
    for (strmId = 0U ; strmId < CSIRX_NUM_STREAM ; strmId++)
    {
        switch (strmId)
        {

            case 0U:
                platformData->strmStatus[instId][strmId] =
                                            CSIRX_STRM_SUPPORT_SUPPORTED;
                platformData->strmType[instId][strmId] = CSIRX_CH_TYPE_CAPT;
            break;
            case 1U:
                platformData->strmStatus[instId][strmId] =
                                            CSIRX_STRM_SUPPORT_SUPPORTED;
                platformData->strmType[instId][strmId] = CSIRX_CH_TYPE_LPBK;
            break;
            case 2U:
                platformData->strmStatus[instId][strmId] =
                                            CSIRX_STRM_SUPPORT_SUPPORTED;
                platformData->strmType[instId][strmId] = CSIRX_CH_TYPE_OTF;
            break;
            case 3U:
                platformData->strmStatus[instId][strmId] =
                                            CSIRX_STRM_SUPPORT_NOT_SUPPORTED;
                platformData->strmType[instId][strmId] = CSIRX_CH_TYPE_CAPT;
            break;
            default:
                platformData->strmStatus[instId][strmId] =
                                            CSIRX_STRM_SUPPORT_NOT_SUPPORTED;
                platformData->strmType[instId][strmId] = CSIRX_CH_TYPE_CAPT;
		    break;
        }
    }

    /* Update register base addresses: instance 0 */
    platformData->modAddr[instId] =
                        (uint32_t)CSL_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE;
    platformData->shimAddr[instId] =
                        (uint32_t)CSL_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_BASE;
    platformData->dPhyWrapAddr[instId] =
                        (uint32_t)CSL_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_BASE;
    platformData->dPhyCoreAddr[instId] =
                        (uint32_t)CSL_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_BASE;
    platformData->psilThreadIdStart[instId] = (uint32_t)CSL_PSIL_CSI_RX0_CH0;
    /* Update info only for supported streams: instance 1 */
    instId = 1U;
    platformData->strmStatus[instId][0U] = CSIRX_STRM_SUPPORT_SUPPORTED;
    platformData->strmType[instId][0U] = CSIRX_CH_TYPE_CAPT;
    platformData->strmStatus[instId][1U] = CSIRX_STRM_SUPPORT_SUPPORTED;
    platformData->strmType[instId][1U] = CSIRX_CH_TYPE_LPBK;
    /* Update register base addresses: instance 1 */
    platformData->modAddr[instId] =
                        (uint32_t)CSL_CSI_RX_IF1_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE;
    platformData->shimAddr[instId] =
                        (uint32_t)CSL_CSI_RX_IF1_RX_SHIM_VBUSP_MMR_CSI2RXIF_BASE;
    platformData->dPhyWrapAddr[instId] =
                        (uint32_t)CSL_DPHY_RX1_MMR_SLV_K3_DPHY_WRAP_BASE;
    platformData->dPhyCoreAddr[instId] =
                        (uint32_t)CSL_DPHY_RX1_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_BASE;
    platformData->psilThreadIdStart[instId] = (uint32_t)CSL_PSIL_CSI_RX1_CH0;

    /* Update info only for supported streams: instance 2 */
    instId = 2U;
    platformData->strmStatus[instId][0U] = CSIRX_STRM_SUPPORT_SUPPORTED;
    platformData->strmType[instId][0U] = CSIRX_CH_TYPE_CAPT;
    platformData->strmStatus[instId][1U] = CSIRX_STRM_SUPPORT_SUPPORTED;
    platformData->strmType[instId][1U] = CSIRX_CH_TYPE_LPBK;
    /* Update register base addresses: instance 2 */
    platformData->modAddr[instId] =
                        (uint32_t)CSL_CSI_RX_IF2_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE;
    platformData->shimAddr[instId] =
                        (uint32_t)CSL_CSI_RX_IF2_RX_SHIM_VBUSP_MMR_CSI2RXIF_BASE;
    platformData->dPhyWrapAddr[instId] =
                        (uint32_t)CSL_DPHY_RX2_MMR_SLV_K3_DPHY_WRAP_BASE;
    platformData->dPhyCoreAddr[instId] =
                        (uint32_t)CSL_DPHY_RX2_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_BASE;
    platformData->psilThreadIdStart[instId] = (uint32_t)CSL_PSIL_CSI_RX2_CH0;


    /* Update info only for supported streams: instance 3 */
    instId = 3U;
    platformData->strmStatus[instId][0U] = CSIRX_STRM_SUPPORT_SUPPORTED;
    platformData->strmType[instId][0U] = CSIRX_CH_TYPE_CAPT;
    platformData->strmStatus[instId][1U] = CSIRX_STRM_SUPPORT_SUPPORTED;
    platformData->strmType[instId][1U] = CSIRX_CH_TYPE_LPBK;

    /* Update register base addresses: instance 3 */
    platformData->modAddr[instId] =
                        (uint32_t)CSL_CSI_RX_IF3_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE;
    platformData->shimAddr[instId] =
                        (uint32_t)CSL_CSI_RX_IF3_RX_SHIM_VBUSP_MMR_CSI2RXIF_BASE;
    platformData->dPhyWrapAddr[instId] =
                        (uint32_t)CSL_DPHY_RX3_MMR_SLV_K3_DPHY_WRAP_BASE;
    platformData->dPhyCoreAddr[instId] =
                        (uint32_t)CSL_DPHY_RX3_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_BASE;
    platformData->psilThreadIdStart[instId] = (uint32_t)CSL_PSIL_CSI_RX3_CH0;

}

void CsirxDrv_dphyrxWrapPsmClockConfig(uint32_t addr, uint32_t value)
{
	/* PSM clock frequency divider control */
	/* This signal specifies a divider value used to create an internal
       divided clock that is a function of the psm_clock clock */
	/* This signal must be driven with a value such that the
       frequency of the divided clock is 1 MHz */
	CSL_FINSR(*(volatile uint32_t *)(addr + DPHYRX_WRAP_REGS_LANE),
                                     DPHYRX_WRAP_REGS_LANE_PSM_CLK_FREQ_MSB,
                                     DPHYRX_WRAP_REGS_LANE_PSM_CLK_FREQ_LSB,
                                     value);
}

void CsirxDrv_dphyrxSetLaneBandSpeed(uint32_t addr,
                                     const Csirx_DPhyCfg *dphyCfg)
{
    uint32_t regVal = 0U;

    /* PHY BAND control */
    regVal |= (dphyCfg->leftLaneBandSpeed <<
                                DPHYRX_PCS_TX_DIG_TBIT0_LEFT_BAND_SHIFT);
    regVal |= (dphyCfg->rightLaneBandSpeed <<
                                DPHYRX_PCS_TX_DIG_TBIT0_RIGHT_BAND_SHIFT);
    CSL_REG32_WR(addr + DPHYRX_PCS_TX_DIG_TBIT0, regVal);
}

void CsirxDrv_dphyrxCorePpiClockConfig(uint32_t addr,
                                       const Csirx_DPhyCfg *dphyCfg)
{
    uint32_t regVal = 0U;
    Float32 psmClkFreqMHz, psmPinVal, toVal;
    uint32_t tempVar;

	/* PHY BAND control */
    regVal |= (dphyCfg->leftLaneBandSpeed <<
                                DPHYRX_PCS_TX_DIG_TBIT0_LEFT_BAND_SHIFT);
    regVal |= (dphyCfg->rightLaneBandSpeed <<
                                DPHYRX_PCS_TX_DIG_TBIT0_RIGHT_BAND_SHIFT);
	CSL_REG32_WR(addr + DPHYRX_PCS_TX_DIG_TBIT0, regVal);

	/* Enable CMN startup state machine, CMN rx mode en,
       wait time for calibrations enable after bandgap is enabled */
    regVal = (dphyCfg->bandGapTimerVal <<
              DPHYRX_CMN0_CMN_DIG_TBIT2_BANDGAP_TIMER_SHIFT);
    regVal |= (1U << DPHYRX_CMN0_CMN_DIG_TBIT2_STARTUP_SM_EN_SHIFT);
    regVal |= ((uint32_t)1U << DPHYRX_CMN0_CMN_DIG_TBIT2_RX_SM_EN_SHIFT);
	CSL_REG32_WR(addr + DPHYRX_CMN0_CMN_DIG_TBIT2, regVal);

    /* Configure Rx Osc calibration feedback clock counter start values */
    /* It is 500MHz / 6 */
    psmClkFreqMHz = DPHYRX_PSM_CLK_FREQ_MHZ;
    /* Integer value only */
    psmPinVal = DPHYRX_PSM_CLK_FREQ_MHZ;
    if (psmClkFreqMHz == psmPinVal)
    {
        /* No need to program psm clock frequency is integral and
           default/reset values will work */
    }
    else
    {
        /* formula: ROUND ((PSM clock period) * (psm_clock_freq pin value) /
                           (Oscillator clock period * 8)) */
        regVal = 0U;
        /* calculate and program timeout value for 1.5 Gbps = 1500 Mhz */
        toVal = psmPinVal / psmClkFreqMHz;
        toVal *= (Float32)1500;
        toVal /= (Float32)8;
        tempVar = (uint32_t)toVal;
        regVal |= ((tempVar & DPHYRX_CMN0_CMN_DIG_TBIT35_1P5G_CNT_START_VAL_MAX) <<
                   DPHYRX_CMN0_CMN_DIG_TBIT35_1P5G_CNT_START_VAL_SHIFT);
        /* calculate and program timeout value for 2.5 Gbps = 2500 Mhz */
        toVal = psmPinVal / psmClkFreqMHz;
        toVal *= (Float32)2500;
        toVal /= (Float32)8;
        tempVar = (uint32_t)toVal;
        regVal |= ((tempVar & DPHYRX_CMN0_CMN_DIG_TBIT35_2P5G_CNT_START_VAL_MAX) <<
                   DPHYRX_CMN0_CMN_DIG_TBIT35_2P5G_CNT_START_VAL_SHIFT);
        CSL_REG32_WR(addr + DPHYRX_CMN0_CMN_DIG_TBIT35, regVal);
    }
    /* Set the required power island phase 2 time.
       Set the register to 32’hAAAAAAAA. This is mandated by DPHY specs. */
    CSL_REG32_WR(addr + DPHYRX_PCS_TX_DIG_TBIT2,
                 DPHYRX_PCS_TX_DIG_TBIT2_PRG_VAL);
    /* Set the required power island phase 2 time.
       Set the register to 8’hAA. This is mandated by DPHY specs. */
    CSL_REG32_WR(addr + DPHYRX_PCS_TX_DIG_TBIT3,
                 DPHYRX_PCS_TX_DIG_TBIT3_PRG_VAL);
}

void CsirxDrv_dphyrxCoreLaneReady(uint32_t addr, uint32_t numLanes)
{
	uint32_t value;

    switch (numLanes)
    {
        case 1U:
            /* Capture over 1 lane */
            value = DPHYRX_1_LANES_READY_CHECK;
            while(value != 0x1U)
            {
                value = DPHYRX_1_LANES_READY_CHECK;
            }
        break;
        case 2U:
            /* Capture over 2 lanes */
            value = DPHYRX_2_LANES_READY_CHECK;
            while(value != 0x1U)
            {
                value = DPHYRX_2_LANES_READY_CHECK;
            }
        break;
        case 3U:
            /* Capture over 3 lanes */
            value = DPHYRX_3_LANES_READY_CHECK;
            while(value != 0x1U)
            {
                value = DPHYRX_3_LANES_READY_CHECK;
            }
        break;
        default:
            /* Capture over 4 lanes */
            value = DPHYRX_4_LANES_READY_CHECK;
            while(value != 0x1U)
            {
                value = DPHYRX_4_LANES_READY_CHECK;
            }
        break;
    }

}

void CsirxDrv_dphyrxCoreCommonReady(uint32_t addr)
{
    uint32_t	value;

    {
        /* SR 1.1 and future silicon revisions */
        /* On J721E PG1.1 and future devices, common module reset will be routed to
           DPHY_RX_MMR_SLV_LANE[23] LANE_RSTB_CMN ,
           this will allow proper reset SW sequence to be executed. */
        /* Release DPHY_RX_MMR_SLV_LANE[23] LANE_RSTB_CMN from reset */
        CSL_REG32_FINS((addr + CSL_DPHY_RX_MMR_SLV + CSL_DPHY_RX_MMR_SLV_LANE),
                        DPHY_RX_MMR_SLV_LANE_LANE_RSTB_CMN,
                        1U);
        /* wait for CMN_READY to be driven to 1 */
        while (0U ==
                (CSL_REG32_FEXT((addr + CSL_DPHY_RX_MMR_SLV +
                                CSL_DPHY_RX_MMR_SLV_LANE),
                                DPHY_RX_MMR_SLV_LANE_CMN_READY)))
        {
            /* wait here till CMN becomes ready */
        }
    }

    /* Wait for CMN to be ready from TBIT56 register */
	value = CSL_REG32_RD(addr + DPHYRX_CMN0_CMN_DIG_TBIT56) & 0x1U;
	while(value != 0x1U)
	{
		value = CSL_REG32_RD(addr + DPHYRX_CMN0_CMN_DIG_TBIT56) & 0x1U;
	}
}

int32_t CsirxDrv_checkDphyrxConfig(const Csirx_DPhyCfg *programmedCfg,
                                   const Csirx_DPhyCfg *newCfg)
{
    int32_t retVal = FVID2_SOK;

    if ((programmedCfg->inst               == newCfg->inst) &&
        (programmedCfg->psmClkFreqDiv      == newCfg->psmClkFreqDiv) &&
        (programmedCfg->leftLaneBandSpeed  == newCfg->leftLaneBandSpeed) &&
        (programmedCfg->rightLaneBandSpeed == newCfg->rightLaneBandSpeed) &&
        (programmedCfg->bandGapTimerVal    == newCfg->bandGapTimerVal))
    {
        /* configuration matches */
    }
    else
    {
        /* configuration does not match */
        retVal = FVID2_WNON_RECOMMENDED_PARAMS;
    }

    return retVal;
}

void CsirxDrv_dphyrxPsoDisable(uint32_t addr, uint32_t val)
{
    uint32_t value;

    value = CSL_REG32_RD(addr + 0x1000U);
    if (val != 0U)
    {
        value |= ((uint32_t)0x1U << 26);
    }
    else
    {
        value &= ~((uint32_t)0x1U << 26);
    }
    CSL_REG32_WR(addr + 0x1000U, value);
}

void CsirxDrv_dphyCommonReset(uint32_t addr, uint32_t value)
{
#if defined(SOC_J721E)
    uint32_t    siliconRev;

    siliconRev = CSL_REG32_FEXT((CSL_WKUP_CTRL_MMR0_CFG0_BASE +
                                 CSL_WKUP_CTRL_MMR_CFG0_JTAGID),
                                 WKUP_CTRL_MMR_CFG0_JTAGID_VARIANT);
    if (siliconRev == 0U)
    {
        /* SR 1.0 devices */
        /* Do nothing here*/
    }
    else
#endif
    {
        /* SR 1.1 and future silicon revisions */
        /* On J721E PG1.1 and future devices, common module reset will be routed to
           DPHY_RX_MMR_SLV_LANE[23] LANE_RSTB_CMN ,
           this will allow proper reset SW sequence to be executed. */
        /* Release DPHY_RX_MMR_SLV_LANE[23] LANE_RSTB_CMN from reset */
        CSL_REG32_FINS((addr + CSL_DPHY_RX_MMR_SLV + CSL_DPHY_RX_MMR_SLV_LANE),
                        DPHY_RX_MMR_SLV_LANE_LANE_RSTB_CMN,
                        value);
    }
}


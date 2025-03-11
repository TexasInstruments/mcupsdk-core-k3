/*
 *  Copyright (c) Texas Instruments Incorporated 2023-2025
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
 *  \file csitx_soc.c
 *
 *  \brief File containing the SOC related configuration functions for CSITX.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/csitx.h>
#include <drivers/csitx/v0/include/csitx_drvPriv.h>
#include <drivers/soc.h>
#include "cslr_wiz16b8m4cdt.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief DPHY configuration related macros */
#define CSITX_DPHY_PSM_DIV_MAX       		           ((uint32_t)256U)
#define CSITX_DPHY_WAIT_BURST_TIME_MAX		           ((uint32_t)256U)
#define CSITX_DPHY_TX_CLK_EXIT_TIME_MAX		           ((uint32_t)256U)
#define CSITX_DPHY_DL_WKUP_TIME_MAX		               ((uint32_t)65536U)
#define CSITX_DPHY_CL_WKUP_TIME_MAX		               ((uint32_t)65536U)
#define CSITX_DPHY_CFG_REG_RESET_MASK   		       ((uint32_t)0x0001F000U)
#define LANE_READY_TIMEOUT_COUNTER                     ((int32_t)5000)

/** \brief DPHY default configuration related macros */
#define CSITX_DPHY_PSM_CLK_FREQ_DIV_DEF       (0x14U)
#define CSITX_DPHY_PLL_BYTE_CLK_DIV_DEF       (0x8U)
#define CSITX_DPHY_PWM_CTRL_DIV_LOW_DEF       (0x1FFU)
#define CSITX_DPHY_PWM_CTRL_DIV_HIGH_DEF      (0x00EU)
#define CSITX_DPHY_PLL_LOCK_THRESHOLD_DEF     (0x04U)
#define CSITX_DPHY_PLL_LOCK_START_DEF         (0xC8U)
#define CSITX_DPHY_PLL_IPDIV_DEF              (0x02U)
#define CSITX_DPHY_PLL_OPDIV_DEF              (0x02U)
#define CSITX_DPHY_PLL_FBDIV_DEF              (0x14DU)
#define CSITX_DPHY_PLL_PD_DEF                 (0U)
#define CSITX_DPHY_WAIT_BURSTTIME_DEF         (0xAU)
#define CSITX_DPHY_TX_CLK_EXITTIME_DEF        (0x5U)
#define CSITX_DPHY_DL_WKUPTIME_DEF            (0x5140U)
#define CSITX_DPHY_CL_WKUPTIME_DEF            (0x5140U)
#define CSITX_DPHY_CLK_MODE_DEF               (CSITX_CLK_MODE_CONTINUOUS)
#define CSITX_DPHY_DPHY_MODE_DEF              (CSITX_DPHY_MODE_HIGH_SPEED)
#define CSITX_DPHY_CL_SLEWRATECTRL_80M_1G     (27U)
#define CSITX_DPHY_DL_SLEWRATECTRL_80M_1G     (27U)
#define CSITX_DPHY_CL_SLEWRATECTRL_1G_1_5G    (7U)
#define CSITX_DPHY_DL_SLEWRATECTRL_1G_1_5G    (7U)
#define CSITX_DPHY_CL_SLEWRATECTRL_1_5G_2_5G  (1U)
#define CSITX_DPHY_DL_SLEWRATECTRL_1_5G_2_5G  (1U)

/* Setting this to invalid default value. This is done to maintain backward
   compatibility */
#define CSITX_DPHY_LANE_SPEED_MBPS_DEF        (0xFFFFFFFFU)
/* Setting this to invalid default value. This is done so that application set this
   as per need. If not overwritten by application then will be calculated in the driver */
#define CSITX_DPHY_SLEWRATECTRL_DEF           (0xFFFFFFFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief Csitx_DPhyCfg structure init function. Called through
 *         'IOCTL_CSITX_SET_DPHY_CONFIG' IOCTL.
 *
 *  \param dphyCfg          [IN] Pointer to #Csitx_DPhyCfg structure.
 *  \param status           [OUT] Status of the check.
 *
 */
static int32_t Csitx_checkDphyCfg(const Csitx_DPhyCfg *dphyCfg);
static int32_t Csitx_setDphyCfg(Csitx_DPhyCfg *dphyCfg);
static void CsitxDrv_dphytxSelectSrc(uint32_t instId);
static void CsitxDrv_dphytxPsmClkConfig(uint32_t addr, uint32_t value);
static int32_t CsitxDrv_dphytxWaitBurstTimeCfg(CsitxDrv_InstObj *instObj,
                                               const Csitx_DPhyCfg *dphyCfg);
static int32_t CsitxDrv_dphytxLaneEanable(uint32_t addr,
                                          const Csitx_DPhyCfg *dphyCfg,
                                          CsitxDrv_InstObj *instObj);
static void CsitxDrv_dphytxByteClkConfig(uint32_t addr,
                                         const Csitx_DPhyCfg *dphyCfg);
static void CsitxDrv_dphytxPllLockReady(uint32_t addr);
static void CsitxDrv_dphytxCmnReady(uint32_t addr);
static int32_t CsitxDrv_dphytxLaneReset(uint32_t addr,
                                        CsitxDrv_InstObj *instObj);
static int32_t CsitxDrv_dphytxLaneReady(uint32_t addr,
                                     CsitxDrv_InstObj *instObj);
static int32_t CsitxDrv_dphytxSlewRateCfg(uint32_t addr,
                                          const Csitx_DPhyCfg *dphyCfg);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
Csitx_PlatformData gSocInfo =
{
    CSITX_INSTANCE_ID_MAX, /* numInstances */
    {
        /* instInfo - Instance 0  */
        {
            CSITX_NUM_STREAM, /* numStrms */
            /* strmInfo - stream 0 */
            {
                {
                    CSITX_STRM_SUPPORT_SUPPORTED,
                    CSITX_NUM_CH_TX,
                    CSITX_STRM_CH_TYPE_TX | CSITX_STRM_CH_TYPE_LPBK
                }
            },
            CSI_TX_IF0_VBUS2APBCSI2TX_BASE, /* modAddr */
            CSI_TX_IF0_TX_SHIM_CSI2TXIF_BASE, /* shimAddr */
            CSL_DPHY_TX0_BASE /* dPhyCoreAddr */
        }
    },
    CSITX_ENABLE_SERIAL_TRANS_ENABLE
};

/* This contains information of the PLL input divider value for DPHY
   rangeMin and rangeMax is in KHz */

Csitx_DphyRangeData gIpDivInfo[] =
{
    {
        .rangeMin = 9600U,
        .rangeMax = 19200U,
        .progVal  = 1U,
    },
    {
        .rangeMin = 19200U,
        .rangeMax = 38400U,
        .progVal  = 2U,
    },
    {
        .rangeMin = 38400U,
        .rangeMax = 76800U,
        .progVal  = 4U,
    },
    {
        .rangeMin = 76800U,
        .rangeMax = 150000U,
        .progVal  = 8U,
    },
};

/* This contains information of the PLL output divider value for DPHY
   rangeMin and rangeMax is in Mbps */
Csitx_DphyRangeData gOpDivInfo[] =
{
    {
        .rangeMin = 1250U,
        .rangeMax = 2500U,
        .progVal  = 1U,
    },
    {
        .rangeMin = 630U,
        .rangeMax = 1240U,
        .progVal  = 2U,
    },
    {
        .rangeMin = 320U,
        .rangeMax = 620U,
        .progVal  = 4U,
    },
    {
        .rangeMin = 160U,
        .rangeMax = 310U,
        .progVal  = 8U,
    },
    {
        .rangeMin = 80U,
        .rangeMax = 150U,
        .progVal  = 16U,
    },
};

/* This contains information of the PLL output divider value for DPHY
   rangeMin and rangeMax is in Mbps */
Csitx_DphyRangeData gLaneSpeedBandInfo[] =
{
    {
        .rangeMin = 80U,
        .rangeMax = 100U,
        .progVal  = CSITX_LANE_BAND_SPEED_80_TO_100_MBPS,
    },
    {
        .rangeMin = 100U,
        .rangeMax = 120U,
        .progVal  = CSITX_LANE_BAND_SPEED_100_TO_120_MBPS,
    },
    {
        .rangeMin = 120U,
        .rangeMax = 160U,
        .progVal  = CSITX_LANE_BAND_SPEED_120_TO_160_MBPS,
    },
    {
        .rangeMin = 160U,
        .rangeMax = 200U,
        .progVal  = CSITX_LANE_BAND_SPEED_160_TO_200_MBPS,
    },
    {
        .rangeMin = 200U,
        .rangeMax = 240U,
        .progVal  = CSITX_LANE_BAND_SPEED_200_TO_240_MBPS,
    },
    {
        .rangeMin = 240U,
        .rangeMax = 320U,
        .progVal  = CSITX_LANE_BAND_SPEED_240_TO_320_MBPS,
    },
    {
        .rangeMin = 320U,
        .rangeMax = 390U,
        .progVal  = CSITX_LANE_BAND_SPEED_320_TO_390_MBPS,
    },
    {
        .rangeMin = 390U,
        .rangeMax = 450U,
        .progVal  = CSITX_LANE_BAND_SPEED_390_TO_450_MBPS,
    },
    {
        .rangeMin = 450U,
        .rangeMax = 510U,
        .progVal  = CSITX_LANE_BAND_SPEED_450_TO_510_MBPS,
    },
    {
        .rangeMin = 510U,
        .rangeMax = 560U,
        .progVal  = CSITX_LANE_BAND_SPEED_510_TO_560_MBPS,
    },
    {
        .rangeMin = 560U,
        .rangeMax = 640U,
        .progVal  = CSITX_LANE_BAND_SPEED_560_TO_640_MBPS,
    },
    {
        .rangeMin = 640U,
        .rangeMax = 690U,
        .progVal  = CSITX_LANE_BAND_SPEED_640_TO_690_MBPS,
    },
    {
        .rangeMin = 690U,
        .rangeMax = 770U,
        .progVal  = CSITX_LANE_BAND_SPEED_690_TO_770_MBPS,
    },
    {
        .rangeMin = 770U,
        .rangeMax = 870U,
        .progVal  = CSITX_LANE_BAND_SPEED_770_TO_870_MBPS,
    },
    {
        .rangeMin = 870U,
        .rangeMax = 950U,
        .progVal  = CSITX_LANE_BAND_SPEED_870_TO_950_MBPS,
    },
    {
        .rangeMin = 950U,
        .rangeMax = 1000U,
        .progVal  = CSITX_LANE_BAND_SPEED_950_TO_1000_MBPS,
    },
    {
        .rangeMin = 1000U,
        .rangeMax = 1200U,
        .progVal  = CSITX_LANE_BAND_SPEED_1000_TO_1200_MBPS,
    },
    {
        .rangeMin = 1200U,
        .rangeMax = 1400U,
        .progVal  = CSITX_LANE_BAND_SPEED_1200_TO_1400_MBPS,
    },
    {
        .rangeMin = 1400U,
        .rangeMax = 1600U,
        .progVal  = CSITX_LANE_BAND_SPEED_1400_TO_1600_MBPS,
    },
    {
        .rangeMin = 1600U,
        .rangeMax = 1800U,
        .progVal  = CSITX_LANE_BAND_SPEED_1600_TO_1800_MBPS,
    },
    {
        .rangeMin = 1800U,
        .rangeMax = 2000U,
        .progVal  = CSITX_LANE_BAND_SPEED_1800_TO_2000_MBPS,
    },
    {
        .rangeMin = 2000U,
        .rangeMax = 2200U,
        .progVal  = CSITX_LANE_BAND_SPEED_2000_TO_2200_MBPS,
    },
    {
        .rangeMin = 2200U,
        .rangeMax = 2500U,
        .progVal  = CSITX_LANE_BAND_SPEED_2200_TO_2500_MBPS,
    },
};

/* Default speed for speed band - [0U]: Lane Band Speed, [1]: Default Speed */
uint32_t gLaneBandDefaultSpeedInfo[CSITX_LANE_BAND_SPEED_RESERVED][2] =
{
    { CSITX_LANE_BAND_SPEED_80_TO_100_MBPS, 100U, },
    { CSITX_LANE_BAND_SPEED_100_TO_120_MBPS, 120U, },
    { CSITX_LANE_BAND_SPEED_120_TO_160_MBPS, 150U, },
    { CSITX_LANE_BAND_SPEED_160_TO_200_MBPS, 200U, },
    { CSITX_LANE_BAND_SPEED_200_TO_240_MBPS, 220U, },
    { CSITX_LANE_BAND_SPEED_240_TO_320_MBPS, 300U, },
    { CSITX_LANE_BAND_SPEED_320_TO_390_MBPS, 350U, },
    { CSITX_LANE_BAND_SPEED_390_TO_450_MBPS, 400U, },
    { CSITX_LANE_BAND_SPEED_450_TO_510_MBPS, 500U, },
    { CSITX_LANE_BAND_SPEED_510_TO_560_MBPS, 550U, },
    { CSITX_LANE_BAND_SPEED_560_TO_640_MBPS, 600U, },
    { CSITX_LANE_BAND_SPEED_640_TO_690_MBPS, 650U, },
    { CSITX_LANE_BAND_SPEED_690_TO_770_MBPS, 700U, },
    { CSITX_LANE_BAND_SPEED_770_TO_870_MBPS, 800U, },
    { CSITX_LANE_BAND_SPEED_870_TO_950_MBPS, 900U, },
    { CSITX_LANE_BAND_SPEED_950_TO_1000_MBPS, 1000U, },
    { CSITX_LANE_BAND_SPEED_1000_TO_1200_MBPS, 1188U, },
    { CSITX_LANE_BAND_SPEED_1200_TO_1400_MBPS, 1300U, },
    { CSITX_LANE_BAND_SPEED_1400_TO_1600_MBPS, 1500U, },
    { CSITX_LANE_BAND_SPEED_1600_TO_1800_MBPS, 1600U, },
    { CSITX_LANE_BAND_SPEED_1800_TO_2000_MBPS, 1800U, },
    { CSITX_LANE_BAND_SPEED_2000_TO_2200_MBPS, 2000U, },
    { CSITX_LANE_BAND_SPEED_2200_TO_2500_MBPS, 2500U, },
};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void CsitxDrv_initPlatData(Csitx_PlatformData *platformData)
{
    /* Copy platform data */
    Fvid2Utils_memcpy(platformData, &gSocInfo, sizeof (Csitx_PlatformData));
}

int32_t Csitx_dphyConfig(void *instHandle)
{
    int32_t retVal = FVID2_SOK;
    CsitxDrv_InstObj *instObj;
    Csitx_DPhyCfg *dphyCfg;

    GT_assert(CsitxTrace, (instHandle != NULL));
    instObj = (CsitxDrv_InstObj *)instHandle;
    /* First select the DPHY source as CSITX as CSITX and DSI TX shares same PHY */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 1);
    CsitxDrv_dphytxSelectSrc(instObj->drvInstId);
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, 1);
    dphyCfg = &instObj->dphyCfg;
    /* Check DPHY params before programming */
    retVal = Csitx_checkDphyCfg(&instObj->createParams.instCfg.dphyCfg);
    if (retVal == FVID2_SOK)
    {
        /* Calculate DPHY clock configurations like dividers */
        retVal = Csitx_setDphyCfg(dphyCfg);
    }
    if (retVal == FVID2_SOK)
    {
        retVal = CsitxDrv_dphytxLaneReset(instObj->dPhyCoreAddr, instObj);
    }
    if (retVal == FVID2_SOK)
    {
        /* DPHYTX psm clock setup */
        CsitxDrv_dphytxPsmClkConfig(instObj->dPhyCoreAddr, dphyCfg->psmClkFreqDiv);

        retVal += CsitxDrv_dphytxWaitBurstTimeCfg(instObj, dphyCfg);
        retVal += CsitxDrv_dphytxLaneEanable(instObj->dPhyCoreAddr,
                                            dphyCfg,
                                            instObj);
    }
    if (retVal == FVID2_SOK)
    {
        CsitxDrv_dphytxByteClkConfig(instObj->dPhyCoreAddr, dphyCfg);
        CsitxDrv_dphytxPllLockReady(instObj->dPhyCoreAddr);
        CsitxDrv_dphytxCmnReady(instObj->dPhyCoreAddr);
    }
    if (retVal == FVID2_SOK)
    {
        retVal = CsitxDrv_dphytxLaneReady(instObj->dPhyCoreAddr, instObj);
    }
    if(retVal == FVID2_SOK)
    {
        retVal = CsitxDrv_dphytxSlewRateCfg(instObj->dPhyCoreAddr,
                                            dphyCfg);
    }

    return retVal;
}

static void CsitxDrv_dphytxSelectSrc(uint32_t instId)
{
    /* Select source to DPHY as CSI-TX */
    /* CSITX and DSITX shares same PHY */
    /* Select CSITX0 as the source for DPHYTX0 */
    if(CSITX_INSTANCE_ID_0 == instId)
    {
        CSL_REG32_WR(CSL_CTRL_MMR0_CFG0_BASE +
                 CSL_MAIN_CTRL_MMR_CFG0_DPHY_TX0_CTRL,
                 0x1);
    }
    else
    {
        /* Either of the above two conditions must hit*/
    }
}

int32_t CsirtxDrv_lpbkSel(uint32_t instId, uint32_t lpbkSel)
{
    int32_t retVal = FVID2_SOK;

    /* Select loopback source for CSI-TX */
    /* 0b00 for CSIRX0, 0b01 for CSIRX1, 0b10 for CSIRX2(Incase of J784S4) */
    if(CSITX_INSTANCE_ID_0 == instId)
    {
        CSL_REG32_WR(CSL_CTRL_MMR0_CFG0_BASE +
                 CSL_MAIN_CTRL_MMR_CFG0_CSI_RX_LOOPBACK,
                 (lpbkSel << CSL_MAIN_CTRL_MMR_CFG0_CSI_RX_LOOPBACK_CSITX0_LB_SEL_SHIFT) & (CSL_MAIN_CTRL_MMR_CFG0_CSI_RX_LOOPBACK_CSITX0_LB_SEL_MASK));
    }
    else
    {
        /* Either of the above two conditions must hit*/
        retVal = FVID2_EFAIL;
    }

    return retVal;
}

static void CsitxDrv_dphytxPsmClkConfig(uint32_t addr, uint32_t value)
{
	/* PSM clock frequency divider control */
	/* This signal specifies a divider value used to create an internal
       divided clock that is a function of the psm_clock clock */
	/* This signal must be driven with a value such that the
       frequency of the divided clock is 1 MHz */
	CSL_REG32_FINS(((volatile uint32_t *)
                    (addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_PSM_FREQ)),
                     WIZ16B8M4CDT_WIZ_CONFIG_PSM_FREQ_PSM_CLOCK_FREQ,
                     value);
}

static int32_t CsitxDrv_dphytxWaitBurstTimeCfg(CsitxDrv_InstObj *instObj,
                                        const Csitx_DPhyCfg *dphyCfg)
{
    int32_t retVal = FVID2_SOK;
    CSITX_WaitBurstTimeConfig cfg;

    cfg.txClockExitTime  = (uint8_t)dphyCfg->txClkExitTime;
    cfg.waitBurstTimeCnt = (uint8_t)dphyCfg->waitBurstTime;

    if (CSITX_SetRegWaitBurstTime(&instObj->cslObj.cslCfgData, &cfg) != CDN_EOK)
    {
        retVal = FVID2_EFAIL;
    }

    return retVal;
}

static int32_t CsitxDrv_dphytxLaneEanable(uint32_t addr,
                                   const Csitx_DPhyCfg *dphyCfg,
                                   CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    CSITX_DphyConfig  cslDphyCfg;
    Csitx_CreateParams *createPrms;
    uint32_t regVal = 0U, stopModeVal = 0U, swapPolVal = 0U;
    uint32_t swapClkPol = 0U;
    uint32_t loopCnt;

    createPrms = &instObj->createParams;
    /* Enable Clock Lane */
    cslDphyCfg.dphyClkEnable = 1U;
    cslDphyCfg.dphyReset     = 1U;
    switch (createPrms->instCfg.numDataLanes)
    {
        case 1U:
            cslDphyCfg.dphyLn0Enable = 1U;
        break;
        case 2U:
            cslDphyCfg.dphyLn0Enable = 1U;
            cslDphyCfg.dphyLn1Enable = 1U;
        break;
        case 3U:
            cslDphyCfg.dphyLn0Enable = 1U;
            cslDphyCfg.dphyLn1Enable = 1U;
            cslDphyCfg.dphyLn2Enable = 1U;
        break;
        default:
            /* Default mode is 4 lanes enabled */
            cslDphyCfg.dphyLn0Enable = 1U;
            cslDphyCfg.dphyLn1Enable = 1U;
            cslDphyCfg.dphyLn2Enable = 1U;
            cslDphyCfg.dphyLn3Enable = 1U;
        break;
    }
    /* Clock mode: continuous mode */
    cslDphyCfg.dphyClockMode = dphyCfg->clkMode;
    /* DPHY mode: High Speed mode */
    cslDphyCfg.dphyMode      = dphyCfg->dphyMode;
    /* Enable calibration  only if lane speed is more than 1.5 Gbps */
    if (dphyCfg->laneBandSpeed > CSITX_LANE_BAND_SPEED_1400_TO_1600_MBPS)
    {
        cslDphyCfg.dphyCalEnable = 1U;
    }
    else
    {
        cslDphyCfg.dphyCalEnable = 0U;
    }
    /* Configure DPHY parameters */
    if (CSITX_SetDphyConfig(&instObj->cslObj.cslCfgData, &cslDphyCfg) !=
                                                            CDN_EOK)
    {
        retVal = FVID2_EFAIL;
    }
    if (retVal == FVID2_SOK)
    {
        /* This is not supported in current CSL-FL hence direct
           register programming */
        /* for 'stopModeVal', 'swapPolVal', and 'powerDownVal', bit 0 is for data lane 0 and
           bit 1 is for data lane 1 and so on */
        swapPolVal   = 0U;
        /* setting 'stopModeVal' and 'powerDownVal' to '0' cause no power down is needed */
        stopModeVal  = 0U;

        /* Configure DPHY lane invert polarity controls */
        for(loopCnt = 0U ;
            loopCnt < (CSITX_TX_DATA_LANES_MAX + CSITX_TX_CLK_LANES_MAX) ;
            loopCnt++)
        {
            switch (loopCnt)
            {
                case 0U:
                    swapClkPol = createPrms->instCfg.lanePolarityCtrl[loopCnt];
                break;
                case 1U:
                    swapPolVal = (createPrms->instCfg.lanePolarityCtrl[loopCnt] << 0U);
                break;
                case 2U:
                    swapPolVal = (createPrms->instCfg.lanePolarityCtrl[loopCnt] << 1U);
                break;
                case 3U:
                    swapPolVal = (createPrms->instCfg.lanePolarityCtrl[loopCnt] << 2U);
                break;
                case 4U:
                    swapPolVal = (createPrms->instCfg.lanePolarityCtrl[loopCnt] << 3U);
                break;
                default:
                    /* Error */
                    retVal = FVID2_EFAIL;
                break;
            }
        }
        regVal = 0U;
        /* combine all the bit-field into single 32 bit register */
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
                       CSITX_DPHY_CFG1_FORCE_STOP_MODE_LN_0,
                       stopModeVal);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
                       CSITX_DPHY_CFG1_FORCE_STOP_MODE_LN_1,
                       stopModeVal);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
                       CSITX_DPHY_CFG1_FORCE_STOP_MODE_LN_2,
                       stopModeVal);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
                       CSITX_DPHY_CFG1_FORCE_STOP_MODE_LN_3,
                       stopModeVal);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
                       CSITX_DPHY_CFG1_DPHY_DIFF_INVERT_LN_0,
                       swapPolVal);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
                       CSITX_DPHY_CFG1_DPHY_DIFF_INVERT_LN_1,
                       swapPolVal);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
                       CSITX_DPHY_CFG1_DPHY_DIFF_INVERT_LN_2,
                       swapPolVal);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
                       CSITX_DPHY_CFG1_DPHY_DIFF_INVERT_LN_3,
                       swapPolVal);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
                       CSITX_DPHY_CFG1_DPHY_DIFF_INVERT_C,
                       swapClkPol);
        if(CSITX_INSTANCE_ID_0 == instObj->drvInstId)
        {
            CSL_REG32_WR((CSI_TX_IF0_VBUS2APBCSI2TX_BASE +
                      CSL_CSITX_DPHY_CFG1),
                      regVal);
        }
    }

    if (retVal == FVID2_SOK)
    {
        if (CSITX_SetDphyClkWakeup(&instObj->cslObj.cslCfgData,
                                   dphyCfg->clWkupTime) !=
                                                                CDN_EOK)
        {
            retVal = FVID2_EFAIL;
        }
    }
    if (retVal == FVID2_SOK)
    {
        if (CSITX_SetDphyUlpsWakeup(&instObj->cslObj.cslCfgData,
                                    dphyCfg->dlWkupTime) !=
                                                                CDN_EOK)
        {
            retVal = FVID2_EFAIL;
        }
    }

    return retVal;
}

static void CsitxDrv_dphytxByteClkConfig(uint32_t addr,
                                  const Csitx_DPhyCfg *dphyCfg)
{
    uint32_t regVal = 0U;

    /* PWM control divider */
    CSL_REG32_FINS((volatile uint32_t *)&regVal,
        WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_BYTECLK_DIV,
        dphyCfg->pllByteClkDiv);
    CSL_REG32_FINS((volatile uint32_t *)&regVal,
        WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_LOW,
        dphyCfg->pwmCtrlDivLow);
    CSL_REG32_FINS((volatile uint32_t *)&regVal,
        WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_HIGH,
        dphyCfg->pwmCtrlDivHigh);
    CSL_REG32_WR(addr + CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10, regVal);

    /* PLL Lock counter start and threshold value configuration */
    regVal = 0U;
    CSL_REG32_FINS((volatile uint32_t *)&regVal,
        WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_LOCK_THR_VALUE,
        dphyCfg->pllLockThreshold);
    CSL_REG32_FINS((volatile uint32_t *)&regVal,
        WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_START_VALUE,
        dphyCfg->pllLockStart);
    CSL_REG32_WR(addr + CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7, regVal);

    /* Enable CMN startup state machine and Tx mode */
    CSL_REG32_FINS((volatile uint32_t *)(addr + CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2),
        WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_SSM_EN,
        1U);
    CSL_REG32_FINS((volatile uint32_t *)(addr + CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2),
        WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT2_CMN0_O_CMN_TX_MODE_EN,
        1U);

    /* Lane Reset Control */
    CSL_REG32_FINS((volatile uint32_t *)(addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_RST_CTRL),
        WIZ16B8M4CDT_WIZ_CONFIG_RST_CTRL_LANE_RSTB_CMN,
        1U);
    /* PLL Programming */
    CSL_REG32_FINS((volatile uint32_t *)(addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL),
        WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_IPDIV,
        dphyCfg->pllIpDiv);
    CSL_REG32_FINS((volatile uint32_t *)(addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL),
        WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_OPDIV,
        dphyCfg->pllOpDiv);
    /* value = ROUND((Data Rate * 2 * pll_opdiv * pll_ipdiv) / PLL reference clock frequency) */
    CSL_REG32_FINS((volatile uint32_t *)(addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL),
        WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_FBDIV,
        dphyCfg->pllFbDiv);
    CSL_REG32_FINS((volatile uint32_t *)(addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL),
        WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_PD,
        dphyCfg->pllPd);
	/* PHY BAND control */
    regVal = 0U;
    CSL_REG32_FINS((volatile uint32_t *)&regVal,
        WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_L,
        dphyCfg->laneBandSpeed);
    CSL_REG32_FINS((volatile uint32_t *)&regVal,
        WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0_PCS_BAND_CTL_REG_R,
        dphyCfg->laneBandSpeed);
	CSL_REG32_WR(addr + CSL_WIZ16B8M4CDT_DPHYTX_PCS_TX_DIG_TBIT0, regVal);
}

static void CsitxDrv_dphytxPllLockReady(uint32_t addr)
{
    uint32_t regVal;

    regVal = CSL_REG32_FEXT((volatile uint32_t *)(addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL),
                            WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_LOCK);
    while (regVal != CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_LOCK_MAX)
    {
        regVal = CSL_REG32_FEXT((volatile uint32_t *)
                                (addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL),
                                WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_LOCK);
    }
}

static int32_t CsitxDrv_dphytxLaneReady(uint32_t addr,
                              CsitxDrv_InstObj *instObj)
{
	uint32_t value, cl, dl0, dl1, dl2, dl3;
    int32_t retVal = FVID2_SOK, timer = LANE_READY_TIMEOUT_COUNTER;
    cl = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L, WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_LANE_READY_CL_L));
    dl0 = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0, WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_LANE_READY_DL_L_0));
    dl1 = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1, WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_LANE_READY_DL_L_1));
    dl2 = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2, WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_LANE_READY_DL_L_2));
    dl3 = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3, WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_LANE_READY_DL_L_3));

    if (instObj->createParams.instCfg.numDataLanes == 1U)
    {
        value = cl & dl0;
    }
    else if (instObj->createParams.instCfg.numDataLanes == 2U)
    {
        value = cl & dl0 & dl1;
    }
    else if (instObj->createParams.instCfg.numDataLanes == 3U)
    {
        value = cl & dl0 & dl1 & dl2;
    }
    else
    {
        /* Default for 4 number of lanes */
        value = cl & dl0 & dl1 & dl2 & dl3;
    }

    while((value != 0x1) && (timer > 0))
    {
        cl = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L, WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_CL_CNTRL_L_ISO_LANE_READY_CL_L));
        dl0 = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0, WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L0_ISO_LANE_READY_DL_L_0));
        dl1 = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1, WIZ16B8M4CDT_DPHYTX_ISO_PHY_ISO_DL_CTRL_L1_ISO_LANE_READY_DL_L_1));
        dl2 = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2, WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L2_ISO_LANE_READY_DL_L_2));
        dl3 = (CSL_REG32_FEXT(addr + CSL_WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3, WIZ16B8M4CDT_DPHYTX_ISO_LDD_PHY_ISO_DL_CTRL_L3_ISO_LANE_READY_DL_L_3));

        if (instObj->createParams.instCfg.numDataLanes == 1U)
        {
            value = cl & dl0;
        }
        else if (instObj->createParams.instCfg.numDataLanes == 2U)
        {
            value = cl & dl0 & dl1;
        }
        else if (instObj->createParams.instCfg.numDataLanes == 3U)
        {
            value = cl & dl0 & dl1 & dl2;
        }
		else
        {
            /* Default for 4 number of lanes */
            value = cl & dl0 & dl1 & dl2 & dl3;
        }
        timer--;
    }
    if(timer <= 0)
    {
        retVal = FVID2_EFAIL;
    }
    return retVal;
}

static void CsitxDrv_dphytxCmnReady(uint32_t addr)
{
    uint32_t regVal;

    regVal = CSL_REG32_FEXT((volatile uint32_t *)(addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS),
                            WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_CMN_READY);
    while (regVal != CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_CMN_READY_MAX)
    {
        regVal = CSL_REG32_FEXT((volatile uint32_t *)
                                (addr + CSL_WIZ16B8M4CDT_WIZ_CONFIG_STATUS),
                                WIZ16B8M4CDT_WIZ_CONFIG_STATUS_O_CMN_READY);
    }
}

static int32_t CsitxDrv_dphytxLaneReset(uint32_t addr,
                                 CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    CSITX_DphyConfig cslDphyCfg;
    uint32_t regVal;

    if (CSITX_GetDphyConfig(&instObj->cslObj.cslCfgData, &cslDphyCfg) !=
                                                                CDN_EOK)
    {
        retVal = FVID2_EFAIL;
    }
    if (retVal == FVID2_SOK)
    {
        /* Reset PHY lanes */
        cslDphyCfg.dphyReset = 1U;
        if (CSITX_SetDphyConfig(&instObj->cslObj.cslCfgData, &cslDphyCfg) !=
                                                            CDN_EOK)
        {
            retVal = FVID2_EFAIL;
        }
    }
    /* Explicitly writing this value as current version of CSL-FL does support
       programming of all the bits for lane and clock reset */
    if(CSITX_INSTANCE_ID_0 == instObj->drvInstId)
    {
        regVal = CSL_REG32_RD(CSI_TX_IF0_VBUS2APBCSI2TX_BASE +
                            CSL_CSITX_DPHY_CFG);
        regVal |= CSITX_DPHY_CFG_REG_RESET_MASK;
        CSL_REG32_WR((CSI_TX_IF0_VBUS2APBCSI2TX_BASE +
                    CSL_CSITX_DPHY_CFG),
                    regVal);
    }

    return retVal;
}

void Csitx_initDPhyCfgParams(Csitx_DPhyCfg *dphyCfg)
{
    dphyCfg->inst             = CSITX_INSTANCE_ID_0,
    dphyCfg->psmClkFreqDiv    = CSITX_DPHY_PSM_CLK_FREQ_DIV_DEF;
    dphyCfg->pllByteClkDiv    = CSITX_DPHY_PLL_BYTE_CLK_DIV_DEF;
    dphyCfg->pwmCtrlDivLow    = CSITX_DPHY_PWM_CTRL_DIV_LOW_DEF;
    dphyCfg->pwmCtrlDivHigh   = CSITX_DPHY_PWM_CTRL_DIV_HIGH_DEF;
    dphyCfg->pllLockThreshold = CSITX_DPHY_PLL_LOCK_THRESHOLD_DEF;
    dphyCfg->pllLockStart     = CSITX_DPHY_PLL_LOCK_START_DEF;
    dphyCfg->pllIpDiv         = CSITX_DPHY_PLL_IPDIV_DEF;
    dphyCfg->pllOpDiv         = CSITX_DPHY_PLL_OPDIV_DEF;
    dphyCfg->pllFbDiv         = CSITX_DPHY_PLL_FBDIV_DEF;
    dphyCfg->pllPd            = CSITX_DPHY_PLL_PD_DEF;
    dphyCfg->laneBandSpeed    = CSITX_LANE_BAND_SPEED_770_TO_870_MBPS,
    dphyCfg->waitBurstTime    = CSITX_DPHY_WAIT_BURSTTIME_DEF;
    dphyCfg->txClkExitTime    = CSITX_DPHY_TX_CLK_EXITTIME_DEF;
    dphyCfg->dlWkupTime       = CSITX_DPHY_DL_WKUPTIME_DEF;
    dphyCfg->clWkupTime       = CSITX_DPHY_CL_WKUPTIME_DEF;
    dphyCfg->clkMode          = CSITX_DPHY_CLK_MODE_DEF;
    dphyCfg->dphyMode         = CSITX_DPHY_DPHY_MODE_DEF;
    dphyCfg->clSlewRateCtrl   = CSITX_DPHY_SLEWRATECTRL_DEF;
    dphyCfg->dlSlewRateCtrl   = CSITX_DPHY_SLEWRATECTRL_DEF;
    dphyCfg->laneSpeedMbps    = CSITX_DPHY_LANE_SPEED_MBPS_DEF;
}

static int32_t Csitx_checkDphyCfg(const Csitx_DPhyCfg *dphyCfg)
{
    int32_t retVal = FVID2_EFAIL;

    /* Check parameters values */
    if ((dphyCfg->inst < CSITX_INSTANCE_ID_MAX) &&
        (dphyCfg->psmClkFreqDiv < CSITX_DPHY_PSM_DIV_MAX) &&
        (dphyCfg->pwmCtrlDivLow <
            CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_LOW_MAX) &&
        (dphyCfg->pwmCtrlDivHigh <
            CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT10_CMN0_O_ANA_PLL_GM_PWM_DIV_HIGH_MAX) &&
        (dphyCfg->pllLockThreshold <
            CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_LOCK_THR_VALUE_MAX) &&
        (dphyCfg->pllLockStart <
            CSL_WIZ16B8M4CDT_DPHYTX_CMN0_CMN_DIG_TBIT7_CMN0_O_LOCKDET_PLLCNT_START_VALUE_MAX) &&
        (dphyCfg->pllIpDiv <
            CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_IPDIV_MAX) &&
        (dphyCfg->pllOpDiv <
            CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_OPDIV_MAX) &&
        (dphyCfg->pllFbDiv <
            CSL_WIZ16B8M4CDT_WIZ_CONFIG_PLL_CTRL_PLL_FBDIV_MAX) &&
        (dphyCfg->waitBurstTime < CSITX_DPHY_WAIT_BURST_TIME_MAX) &&
        (dphyCfg->txClkExitTime < CSITX_DPHY_TX_CLK_EXIT_TIME_MAX) &&
        (dphyCfg->dlWkupTime < CSITX_DPHY_DL_WKUP_TIME_MAX) &&
        (dphyCfg->clWkupTime < CSITX_DPHY_CL_WKUP_TIME_MAX) &&
        (((dphyCfg->laneBandSpeed < CSITX_LANE_BAND_SPEED_RESERVED) &&
          (dphyCfg->laneSpeedMbps == CSITX_DPHY_LANE_SPEED_MBPS_DEF)) ||
          ((dphyCfg->laneSpeedMbps >= gLaneSpeedBandInfo[0U].rangeMin) &&
           (dphyCfg->laneSpeedMbps <=
            gLaneSpeedBandInfo[((sizeof(gLaneSpeedBandInfo) / sizeof(Csitx_DphyRangeData)) - 1U)].rangeMax))))
    {
        retVal = FVID2_SOK;
    }

    return retVal;
}

static int32_t CsitxDrv_dphytxSlewRateCfg(uint32_t addr,
                                          const Csitx_DPhyCfg *dphyCfg)
{
    int32_t retVal = FVID2_SOK;
    uint32_t regVal = 0U;

    if ((dphyCfg->clSlewRateCtrl <
            CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MAX) &&
        (dphyCfg->dlSlewRateCtrl <
            CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL_MAX))
    {
        /* Slew rate control for Clock lane */
        regVal = CSL_REG32_RD(addr + CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL,
            dphyCfg->clSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL,
            dphyCfg->clSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL,
            dphyCfg->clSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0_1_G_OVRRIDE_EN,
            1U);
        CSL_REG32_WR((addr + CSL_WIZ16B8M4CDT_DPHYTX_CLK0_TX_ANA_TBIT0),
                     regVal);

        /* Slew rate control for data lane 0 */
        regVal = CSL_REG32_RD(addr + CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0_1_G_OVRRIDE_EN,
            1U);
        CSL_REG32_WR((addr + CSL_WIZ16B8M4CDT_DPHYTX_DL0_TX_ANA_TBIT0),
                     regVal);

        /* Slew rate control for data lane 1 */
        regVal = CSL_REG32_RD(addr + CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0_1_G_OVRRIDE_EN,
            1U);
        CSL_REG32_WR((addr + CSL_WIZ16B8M4CDT_DPHYTX_DL1_TX_ANA_TBIT0),
                     regVal);

            /* Slew rate control for data lane 2 */
        regVal = CSL_REG32_RD(addr + CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0_1_G_OVRRIDE_EN,
            1U);
        CSL_REG32_WR((addr + CSL_WIZ16B8M4CDT_DPHYTX_DL2_TX_ANA_TBIT0),
                     regVal);

            /* Slew rate control for data lane 3 */
        regVal = CSL_REG32_RD(addr + CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_2_5_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_5_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_G_OVRRIDE_VAL,
            dphyCfg->dlSlewRateCtrl);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_2_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_5_G_OVRRIDE_EN,
            1U);
        CSL_REG32_FINS((volatile uint32_t *)&regVal,
            WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0_1_G_OVRRIDE_EN,
            1U);
        CSL_REG32_WR((addr + CSL_WIZ16B8M4CDT_DPHYTX_DL3_TX_ANA_TBIT0),
                     regVal);
    }
    else
    {
        /* Invalid slew rate control value is provided */
        retVal = FVID2_EINVALID_PARAMS;
    }

    return retVal;
}

static int32_t Csitx_setDphyCfg(Csitx_DPhyCfg *dphyCfg)
{
    int32_t retVal = FVID2_SOK;
    uint32_t idx = 0U;
    uint64_t laneClkKbps, tempResult, refClkKHz, refClk = 0U;

    /* Calculate configurations only if provided configurations are different than default
       This is done to maintain backward compatibility where 'laneBandSpeed' parameter was not
       present and passing 'laneBandSpeed' alone was sufficient */
    if (dphyCfg->laneSpeedMbps != CSITX_DPHY_LANE_SPEED_MBPS_DEF)
    {
        /* Get speed band for given lane speed */
        for (idx = 0U ;
             idx < (sizeof(gLaneSpeedBandInfo) / sizeof(Csitx_DphyRangeData));
             idx++)
        {
            if ((dphyCfg->laneSpeedMbps >= gLaneSpeedBandInfo[idx].rangeMin) &&
                (dphyCfg->laneSpeedMbps <= gLaneSpeedBandInfo[idx].rangeMax))
            {
                break;
            }

        }
        if (idx < (sizeof(gLaneSpeedBandInfo) / sizeof(Csitx_DphyRangeData)))
        {
            dphyCfg->laneBandSpeed = gLaneSpeedBandInfo[idx].progVal;
        }
        else
        {
            retVal = FVID2_EFAIL;
        }
    }
    else
    {
        /* Get default lane speed for given lane band speed */
        for (idx = 0U ; idx < CSITX_LANE_BAND_SPEED_RESERVED ; idx++)
        {
            if (dphyCfg->laneBandSpeed == gLaneBandDefaultSpeedInfo[idx][0U])
            {
                break;
            }

        }
        if (idx < CSITX_LANE_BAND_SPEED_RESERVED)
        {
            dphyCfg->laneSpeedMbps = gLaneBandDefaultSpeedInfo[idx][1U];
        }
        else
        {
            retVal = FVID2_EFAIL;
        }
    }

    if (retVal == FVID2_SOK)
    {
        if ((dphyCfg->clSlewRateCtrl == CSITX_DPHY_SLEWRATECTRL_DEF) ||
            (dphyCfg->dlSlewRateCtrl == CSITX_DPHY_SLEWRATECTRL_DEF))
        {
            /* Calculate slew-rate only if not overwritten by application */
            /* No need to check lower limit here as this is unsigned variable and lower value is '0' */
            if (dphyCfg->laneBandSpeed <= CSITX_LANE_BAND_SPEED_950_TO_1000_MBPS)
            {
                /* For 80M to 1Gbps */
                dphyCfg->clSlewRateCtrl   = CSITX_DPHY_CL_SLEWRATECTRL_80M_1G;
                dphyCfg->dlSlewRateCtrl   = CSITX_DPHY_DL_SLEWRATECTRL_80M_1G;
            }
            else if ((dphyCfg->laneBandSpeed >= CSITX_LANE_BAND_SPEED_1000_TO_1200_MBPS) &&
                (dphyCfg->laneBandSpeed <= CSITX_LANE_BAND_SPEED_1400_TO_1600_MBPS))
            {
                /* For 1Gbps to 1.5Gbps */
                dphyCfg->clSlewRateCtrl   = CSITX_DPHY_CL_SLEWRATECTRL_1G_1_5G;
                dphyCfg->dlSlewRateCtrl   = CSITX_DPHY_CL_SLEWRATECTRL_1G_1_5G;
            }
            else if ((dphyCfg->laneBandSpeed >= CSITX_LANE_BAND_SPEED_1600_TO_1800_MBPS) &&
                (dphyCfg->laneBandSpeed <= CSITX_LANE_BAND_SPEED_2200_TO_2500_MBPS))
            {
                /* For 1.5Gbps to 2.5Gbps */
                dphyCfg->clSlewRateCtrl   = CSITX_DPHY_CL_SLEWRATECTRL_1_5G_2_5G;
                dphyCfg->dlSlewRateCtrl   = CSITX_DPHY_CL_SLEWRATECTRL_1_5G_2_5G;
            }
            else
            {
                retVal = FVID2_EFAIL;
            }
        }
    }

    if (retVal == FVID2_SOK)
    {
        laneClkKbps = (dphyCfg->laneSpeedMbps * 1000U);
        /*Read the clock runtime through sciclient APIs */
        if(CSITX_INSTANCE_ID_0 == dphyCfg->inst)
        {

            retVal += Sciclient_pmGetModuleClkFreq(TISCI_DEV_DPHY_TX0,
                                      TISCI_DEV_DPHY_TX0_DPHY_REF_CLK,
                                      &refClk,SystemP_WAIT_FOREVER);
        }
        else
        {
            retVal = FVID2_EFAIL;
        }
        /* Calculate DPHY ipdiv - PLL input divider */
        if (retVal == FVID2_SOK)
        {
            /*converting into KHz*/
            refClkKHz = ((refClk) / 1000U);
            for (idx = 0U ;
                 idx < (sizeof(gIpDivInfo) / sizeof(Csitx_DphyRangeData));
                 idx++)
            {
                if ((refClkKHz >= gIpDivInfo[idx].rangeMin) &&
                    (refClkKHz < gIpDivInfo[idx].rangeMax))
                {
                    break;
                }

            }
            if (idx < (sizeof(gIpDivInfo) / sizeof(Csitx_DphyRangeData)))
            {
                dphyCfg->pllIpDiv = gIpDivInfo[idx].progVal;
            }
            else
            {
                retVal = FVID2_EFAIL;
            }
        }
        /* Calculate DPHY opdiv - PLL output divider */
        if (retVal == FVID2_SOK)
        {
            for (idx = 0U ;
                 idx < (sizeof(gOpDivInfo) / sizeof(Csitx_DphyRangeData));
                 idx++)
            {
                if ((dphyCfg->laneSpeedMbps >= gOpDivInfo[idx].rangeMin) &&
                    (dphyCfg->laneSpeedMbps <= gOpDivInfo[idx].rangeMax))
                {
                    break;
                }
            }
            if (idx < (sizeof(gOpDivInfo) / sizeof(Csitx_DphyRangeData)))
            {
                dphyCfg->pllOpDiv = gOpDivInfo[idx].progVal;
            }
            else
            {
                retVal = FVID2_EFAIL;
            }
        }
        /* Calculate DPHY fbdiv - PLL feedback divider */
        if (retVal == FVID2_SOK)
        {
            tempResult = (((uint64_t)laneClkKbps) *
                          ((uint64_t)2U) *
                          ((uint64_t)dphyCfg->pllIpDiv) *
                          ((uint64_t)dphyCfg->pllOpDiv));
            tempResult /= (uint64_t)refClkKHz;

            dphyCfg->pllFbDiv = (uint32_t)tempResult;
        }
    }

    return retVal;
}


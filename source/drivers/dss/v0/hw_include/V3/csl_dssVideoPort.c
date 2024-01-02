/*
 *  Copyright (c) Texas Instruments Incorporated 2023
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
 *  \file csl_dssVideoPort.c
 *
 *  \brief File containing the DSS Video Port CSL FL APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/csl_dss.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CSL_DSS_VP_NUM_ENTRIES_WIDTH_FORMAT_TABLE \
    (sizeof (gDssVpWidthFmt) / sizeof (gDssVpWidthFmt[0]))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Video interface widths are defined separately by FVID2 and DSS. This
 *         structure defines different values for a particular width
 */
typedef struct
{
    uint32_t fvid2Width;
    /**< FVID2 Width. Refer #Fvid2_VideoIfWidth for values */
    uint32_t dssWidth;
    /**< DSS Width */
} CSL_DssVpWidthFmt;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void CSL_dssVpSetVideoFormatConfig(CSL_dss_vpRegs *vpRegs,
                                          uint32_t dvoFormat,
                                          uint32_t cscRange);

static void CSL_dssVpSetVideoIfWidth(CSL_dss_vpRegs *vpRegs,
                                     uint32_t fvid2Width);

static void CSL_dssVpGetTdmHblankFact(const CSL_dss_vpRegs *vpRegs,
                                      uint32_t *hBlankMultFact,
                                      uint32_t *hBlankDivFact);

static int32_t CSL_dssVpValidateLcdBlankTiming(
                            const CSL_DssVpLcdBlankTimingCfg *lcdBlankTimingCfg,
                            uint32_t hBlankMultFact,
                            uint32_t hBlankDivFact);

static int32_t CSL_dssVpSetDiscSyncBlanking(
                                    CSL_dss_vpRegs *vpRegs,
                                    const CSL_DssVpLcdBlankTimingCfg *blankCfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Fvid2_ModeInfo gVpStdModeInfo[] = {
    {FVID2_STD_1080P_60,       1920, 1080, FVID2_SF_PROGRESSIVE, 148500, 60,
     88, 148, 44, 4, 36, 5},
    {FVID2_STD_1080P_50,       1920, 1080, FVID2_SF_PROGRESSIVE, 74250,  50,
    528, 148, 44, 4, 36, 5},
    {FVID2_STD_1080P_30,       1920, 1080, FVID2_SF_PROGRESSIVE, 74250,  30,
     88, 148, 44, 4, 36, 5},
    {FVID2_STD_720P_60,        1280, 720,  FVID2_SF_PROGRESSIVE, 74250,  60,
     110, 220, 40, 5, 20, 5},
    {FVID2_STD_720P_50,        1280, 720,  FVID2_SF_PROGRESSIVE, 74250,  50,
     440, 220, 40, 5, 20, 5},
    {FVID2_STD_XGA_60,         1024, 768,  FVID2_SF_PROGRESSIVE, 65000,  60,
     136, 160, 24, 3, 29, 6},
    {FVID2_STD_XGA_DSS_TDM_60, 1024, 768,  FVID2_SF_PROGRESSIVE, 64000,  60,
     136, 160, 24, 3, 29, 6},
    {FVID2_STD_XGA_75,         1024, 768,  FVID2_SF_PROGRESSIVE, 78750,  75,
     16, 176, 96, 1, 28, 3},
    {FVID2_STD_SXGA_60,        1280, 1024, FVID2_SF_PROGRESSIVE, 108000, 60,
     48, 248, 112, 1, 38, 3},
    {FVID2_STD_SXGA_75,        1280, 1024, FVID2_SF_PROGRESSIVE, 135000, 75,
     16, 248, 144, 1, 38, 3},
    {FVID2_STD_UXGA_60,        1600, 1200, FVID2_SF_PROGRESSIVE, 162000, 60,
     64, 304, 192, 1, 46, 3},
    {FVID2_STD_1080I_60,       1920, 540,  FVID2_SF_INTERLACED,  74250,  30,
     88, 148, 44, 2, 15, 5},
    {FVID2_STD_1080I_50,       1920, 540,  FVID2_SF_INTERLACED,  74250,  30,
     528, 148, 44, 2, 15, 5},
    {FVID2_STD_480P,           720,  480,  FVID2_SF_PROGRESSIVE, 27000,  60,
     16, 60, 62, 9, 30, 6},
    {FVID2_STD_576P,           720,  576,  FVID2_SF_PROGRESSIVE, 27000,  50,
     12, 68, 64, 5, 39, 5},
    {FVID2_STD_576I,           720,  288,  FVID2_SF_INTERLACED,  27000,  25,
     12, 69, 63, 2, 19, 3},
    {FVID2_STD_480I,           720,  240,  FVID2_SF_INTERLACED,  27000,  30,
     19, 57, 62, 4, 15, 3},
    {FVID2_STD_NTSC,           720,  240,  FVID2_SF_INTERLACED,  27000,  30,
     19, 57, 62, 4, 15, 3},
    {FVID2_STD_PAL,            720,  288,  FVID2_SF_INTERLACED,  27000,  25,
     12, 69, 63, 2, 19, 3},
    {FVID2_STD_WXGA_60,        1280, 800,  FVID2_SF_PROGRESSIVE, 83500,  60,
     128, 200, 72, 3, 22, 6},
};

/* Coefficients for RGB to BT-601 YUV conversion */
static const CSL_DssCscCoeff gVpCscLimtedRangeCoeff = {
    CSL_DSS_CSC_RANGE_LIMITED,
      77,  150,  29,
     -44,  -87, 131,
     131, -110, -21,
       0,    0,   0,
     256, 2048, 2048
};

static const CSL_DssCscCoeff gVpCscFullRangeCoeff = {
    CSL_DSS_CSC_RANGE_FULL,
      66,  129,  25,
     -38,  -74, 112,
     112,  -94, -18,
       0,    0,   0,
       0, 2048, 2048
};

/* Table containing FVID2 video interface width and corresponding DSS width */
static const CSL_DssVpWidthFmt gDssVpWidthFmt[] = {
    {FVID2_VIFW_12BIT , CSL_DSS_VP1_CONTROL_DATALINES_VAL_OALSB12B},
    {FVID2_VIFW_16BIT , CSL_DSS_VP1_CONTROL_DATALINES_VAL_OALSB16B},
    {FVID2_VIFW_18BIT , CSL_DSS_VP1_CONTROL_DATALINES_VAL_OALSB18B},
    {FVID2_VIFW_24BIT , CSL_DSS_VP1_CONTROL_DATALINES_VAL_OALSB24B},
    {FVID2_VIFW_30BIT , CSL_DSS_VP1_CONTROL_DATALINES_VAL_OALSB30B},
    {FVID2_VIFW_36BIT , CSL_DSS_VP1_CONTROL_DATALINES_VAL_OALSB36B}
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CSL_dssVpEnable(CSL_dss_vpRegs *vpRegs, uint32_t enable)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&vpRegs->CONTROL);
    CSL_FINS(regVal,
             DSS_VP1_CONTROL_ENABLE,
             enable);
    CSL_REG32_WR(&vpRegs->CONTROL, regVal);
}

void CSL_dssVpSetGoBit(CSL_dss_vpRegs *vpRegs)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&vpRegs->CONTROL);
    CSL_FINS(regVal,
             DSS_VP1_CONTROL_GOBIT,
             CSL_DSS_VP1_CONTROL_GOBIT_VAL_UFPSR);
    CSL_REG32_WR(&vpRegs->CONTROL, regVal);
}

void CSL_dssVpSetLcdTdmConfig(CSL_dss_vpRegs *vpRegs,
                              const CSL_DssVpLcdTdmCfg *lcdTdmCfg)
{
    uint32_t regVal;

    /* Write Data Cycle 0 fields */
    regVal = CSL_REG32_RD(&vpRegs->DATA_CYCLE_0);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_0_NBBITSPIXEL1,
             lcdTdmCfg->numBitsPixel1Cycle0);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_0_BITALIGNMENTPIXEL1,
             lcdTdmCfg->bitAlignPixel1Cycle0);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_0_NBBITSPIXEL2,
             lcdTdmCfg->numBitsPixel2Cycle0);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_0_BITALIGNMENTPIXEL2,
             lcdTdmCfg->bitAlignPixel1Cycle0);
    CSL_REG32_WR(&vpRegs->DATA_CYCLE_0, regVal);

    /* Write Data Cycle 1 fields */
    regVal = CSL_REG32_RD(&vpRegs->DATA_CYCLE_1);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_1_NBBITSPIXEL1,
             lcdTdmCfg->numBitsPixel1Cycle1);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_1_BITALIGNMENTPIXEL1,
             lcdTdmCfg->bitAlignPixel1Cycle1);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_1_NBBITSPIXEL2,
             lcdTdmCfg->numBitsPixel2Cycle1);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_1_BITALIGNMENTPIXEL2,
             lcdTdmCfg->bitAlignPixel1Cycle1);
    CSL_REG32_WR(&vpRegs->DATA_CYCLE_1, regVal);

    /* Write Data Cycle 2 fields */
    regVal = CSL_REG32_RD(&vpRegs->DATA_CYCLE_2);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_2_NBBITSPIXEL1,
             lcdTdmCfg->numBitsPixel1Cycle2);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_2_BITALIGNMENTPIXEL1,
             lcdTdmCfg->bitAlignPixel1Cycle2);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_2_NBBITSPIXEL2,
             lcdTdmCfg->numBitsPixel2Cycle2);
    CSL_FINS(regVal,
             DSS_VP1_DATA_CYCLE_2_BITALIGNMENTPIXEL2,
             lcdTdmCfg->bitAlignPixel1Cycle2);
    CSL_REG32_WR(&vpRegs->DATA_CYCLE_2, regVal);

    /* Write Control fields */
    regVal = CSL_REG32_RD(&vpRegs->CONTROL);
    CSL_FINS(regVal,
             DSS_VP1_CONTROL_TDMUNUSEDBITS,
             lcdTdmCfg->tdmUnusedBitsLevel);
    CSL_FINS(regVal,
             DSS_VP1_CONTROL_TDMCYCLEFORMAT,
             lcdTdmCfg->tdmCycleFormat);
    CSL_FINS(regVal,
             DSS_VP1_CONTROL_TDMPARALLELMODE,
             lcdTdmCfg->tdmParallelMode);
    CSL_FINS(regVal,
             DSS_VP1_CONTROL_TDMENABLE,
             lcdTdmCfg->tdmEnable);
    CSL_REG32_WR(&vpRegs->CONTROL, regVal);
}

void CSL_dssVpSetLcdLineNum(CSL_dss_vpRegs *vpRegs,
                            uint32_t lineNum)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&vpRegs->LINE_NUMBER);
    CSL_FINS(regVal, DSS_VP1_LINE_NUMBER_LINENUMBER, lineNum);
    CSL_REG32_WR(&vpRegs->LINE_NUMBER, regVal);
}

int32_t CSL_dssVpSetLcdOpTimingConfig(CSL_dss_vpRegs *vpRegs,
                                      const CSL_DssVpLcdOpTimingCfg *lcdCfg)
{
    int32_t retVal = CSL_PASS;
    uint32_t regVal, numStdModes, modeCnt, scanFormat, scanFormatVal;
    CSL_DssVpLcdBlankTimingCfg lcdBlankTimingCfg;
    uint32_t width, height, isCustomTiming = TRUE;

    if((NULL == vpRegs) || (NULL == lcdCfg))
    {
        retVal = CSL_EBADARGS;
    }
    if(CSL_PASS == retVal)
    {
        if (FVID2_STD_CUSTOM != lcdCfg->mInfo.standard)
        {
            numStdModes = sizeof (gVpStdModeInfo) / sizeof (Fvid2_ModeInfo);

            for (modeCnt = 0U; modeCnt < numStdModes; modeCnt++)
            {
                if (lcdCfg->mInfo.standard ==
                                            gVpStdModeInfo[modeCnt].standard)
                {
                    isCustomTiming = FALSE;
                    width  = gVpStdModeInfo[modeCnt].width;
                    height = gVpStdModeInfo[modeCnt].height;
                    lcdBlankTimingCfg.hFrontPorch =
                        gVpStdModeInfo[modeCnt].hFrontPorch;
                    lcdBlankTimingCfg.hBackPorch =
                        gVpStdModeInfo[modeCnt].hBackPorch;
                    lcdBlankTimingCfg.hSyncLen =
                        gVpStdModeInfo[modeCnt].hSyncLen;
                    lcdBlankTimingCfg.vFrontPorch =
                        gVpStdModeInfo[modeCnt].vFrontPorch;
                    lcdBlankTimingCfg.vBackPorch =
                        gVpStdModeInfo[modeCnt].vBackPorch;
                    lcdBlankTimingCfg.vSyncLen =
                        gVpStdModeInfo[modeCnt].vSyncLen;
                    scanFormatVal = gVpStdModeInfo[modeCnt].scanFormat;
                    if (FVID2_SF_INTERLACED ==
                                            gVpStdModeInfo[modeCnt].scanFormat)
                    {
                        scanFormat =
                                CSL_DSS_VP1_CONFIG_OUTPUTMODEENABLE_VAL_ENABLE;
                    }
                    else
                    {
                        scanFormat =
                                CSL_DSS_VP1_CONFIG_OUTPUTMODEENABLE_VAL_DISABLE;
                    }
                    break;
                }
            }
            if (modeCnt == numStdModes)
            {
                retVal = CSL_EBADARGS;
            }
        }
        else
        {
            width  = lcdCfg->mInfo.width;
            height = lcdCfg->mInfo.height;
            lcdBlankTimingCfg.hFrontPorch = lcdCfg->mInfo.hFrontPorch;
            lcdBlankTimingCfg.hBackPorch  = lcdCfg->mInfo.hBackPorch;
            lcdBlankTimingCfg.hSyncLen    = lcdCfg->mInfo.hSyncLen;
            lcdBlankTimingCfg.vFrontPorch = lcdCfg->mInfo.vFrontPorch;
            lcdBlankTimingCfg.vBackPorch  = lcdCfg->mInfo.vBackPorch;
            lcdBlankTimingCfg.vSyncLen    = lcdCfg->mInfo.vSyncLen;
            scanFormatVal                 = lcdCfg->mInfo.scanFormat;
            if (FVID2_SF_INTERLACED == lcdCfg->mInfo.scanFormat)
            {
                scanFormat = CSL_DSS_VP1_CONFIG_OUTPUTMODEENABLE_VAL_ENABLE;
            }
            else
            {
                scanFormat = CSL_DSS_VP1_CONFIG_OUTPUTMODEENABLE_VAL_DISABLE;
            }
        }
    }

    if(CSL_PASS == retVal)
    {
        /* Write blank timing fields */
        retVal = CSL_dssVpSetLcdBlankTiming(vpRegs,
                                            &lcdBlankTimingCfg,
                                            lcdCfg->dvoFormat,
                                            scanFormatVal,
                                            isCustomTiming);

        /* Write width, height and delta lines per panel */
        regVal = CSL_REG32_RD(&vpRegs->SIZE_SCREEN);
        if(FVID2_SF_INTERLACED == lcdCfg->mInfo.scanFormat)
        {
            CSL_FINS(regVal,
                     DSS_VP1_SIZE_SCREEN_LPP,
                     ((height/2U) - 1U));
        }
        else
        {
            CSL_FINS(regVal, DSS_VP1_SIZE_SCREEN_LPP, (height - 1U));
        }
        CSL_FINS(regVal, DSS_VP1_SIZE_SCREEN_PPL, (width - 1U));
        CSL_FINS(regVal,
                 DSS_VP1_SIZE_SCREEN_DELTA_LPP,
                 lcdCfg->deltaLinesPerPanel);
        CSL_REG32_WR(&vpRegs->SIZE_SCREEN, regVal);

        /* Set scan format and field first */
        regVal = CSL_REG32_RD(&vpRegs->CONFIG);
        CSL_FINS(regVal,
                 DSS_VP1_CONFIG_OUTPUTMODEENABLE,
                 scanFormat);
        CSL_FINS(regVal,
                 DSS_VP1_CONFIG_FIDFIRST,
                 lcdCfg->fidFirst);
        CSL_REG32_WR(&vpRegs->CONFIG, regVal);
    }

    if(CSL_PASS == retVal)
    {
        /* Set Video Interface Width */
        CSL_dssVpSetVideoIfWidth(vpRegs, lcdCfg->videoIfWidth);

        /* Set Video Format */
        if(FVID2_DV_BT656_EMBSYNC == lcdCfg->dvoFormat)
        {
            CSL_dssVpSetVideoFormatConfig(vpRegs,
                                          FVID2_DV_BT656_EMBSYNC,
                                          lcdCfg->cscRange);
        }
        else if(FVID2_DV_BT1120_EMBSYNC == lcdCfg->dvoFormat)
        {
            CSL_dssVpSetVideoFormatConfig(vpRegs,
                                          FVID2_DV_BT1120_EMBSYNC,
                                          lcdCfg->cscRange);
        }
        else  /* FVID2_DV_GENERIC_DISCSYNC == lcdCfg->dvoFormat */
        {
            CSL_dssVpSetVideoFormatConfig(vpRegs,
                                          FVID2_DV_GENERIC_DISCSYNC,
                                          lcdCfg->cscRange);
        }
    }

    return (retVal);
}

int32_t CSL_dssVpSetLcdBlankTiming(CSL_dss_vpRegs *vpRegs,
                                   const CSL_DssVpLcdBlankTimingCfg *blankCfg,
                                   uint32_t dvoFormat,
                                   uint32_t scanFormat,
                                   uint32_t isCustomTiming)
{
    uint32_t regVal;
    int32_t retVal = CSL_PASS;
    uint32_t hSyncVal, vSyncVal;

    if(FVID2_DV_GENERIC_DISCSYNC == dvoFormat)
    {
        retVal = CSL_dssVpSetDiscSyncBlanking(vpRegs, blankCfg);
    }
    else /* Embedded Sync */
    {
        if(TRUE == isCustomTiming)
        {
            hSyncVal = blankCfg->hSyncLen & 0xFFU;
            vSyncVal = (blankCfg->hSyncLen >> 8U) & 0xFU;

            regVal = CSL_REG32_RD(&vpRegs->TIMING_H);
            if(FVID2_SF_INTERLACED == scanFormat)
            {
                CSL_FINS(regVal, DSS_VP1_TIMING_H_HBP, blankCfg->hBackPorch);
                CSL_FINS(regVal, DSS_VP1_TIMING_H_HFP, blankCfg->hFrontPorch);
            }
            CSL_FINS(regVal, DSS_VP1_TIMING_H_HSW, hSyncVal);
            CSL_REG32_WR(&vpRegs->TIMING_H, regVal);

            regVal = CSL_REG32_RD(&vpRegs->TIMING_V);
            CSL_FINS(regVal, DSS_VP1_TIMING_V_VBP, blankCfg->vBackPorch);
            CSL_FINS(regVal, DSS_VP1_TIMING_V_VFP, blankCfg->vFrontPorch);
            CSL_FINS(regVal, DSS_VP1_TIMING_V_VSW, vSyncVal);
            CSL_REG32_WR(&vpRegs->TIMING_V, regVal);
        }
        else
        {
            retVal = CSL_EFAIL;
        }
    }

    return (retVal);
}

void CSL_dssVpSetLcdAdvSignalConfig(
                            CSL_dss_vpRegs *vpRegs,
                            const CSL_DssVpLcdAdvSignalCfg *advSignalCfg)
{
    uint32_t regVal, hVClkRiseFallVal;

    /* FVID2 defines rising edge polarity as 0 whereas HW defines as 1, hence modify
     * the values accordingly */
    if(FVID2_EDGE_POL_RISING == advSignalCfg->hVClkRiseFall)
    {
        hVClkRiseFallVal = CSL_DSS_VP1_POL_FREQ_RF_VAL_DRIEDPCK;
    }
    else
    {
        hVClkRiseFallVal = CSL_DSS_VP1_POL_FREQ_RF_VAL_DFEDPCK;
    }
    /* Set POL_FREQ fields */
    regVal = CSL_REG32_RD(&vpRegs->POL_FREQ);
    CSL_FINS(regVal, DSS_VP1_POL_FREQ_ALIGN, advSignalCfg->hVAlign);
    CSL_FINS(regVal, DSS_VP1_POL_FREQ_ONOFF, advSignalCfg->hVClkControl);
    CSL_FINS(regVal, DSS_VP1_POL_FREQ_RF, hVClkRiseFallVal);
    CSL_FINS(regVal, DSS_VP1_POL_FREQ_ACBI, advSignalCfg->acBI);
    CSL_FINS(regVal, DSS_VP1_POL_FREQ_ACB, advSignalCfg->acB);
    CSL_REG32_WR(&vpRegs->POL_FREQ, regVal);

    /* Set CONFIG fields */
    regVal = CSL_REG32_RD(&vpRegs->CONFIG);
    CSL_FINS(regVal, DSS_VP1_CONFIG_VSYNCGATED, advSignalCfg->vSyncGated);
    CSL_FINS(regVal, DSS_VP1_CONFIG_HSYNCGATED, advSignalCfg->hSyncGated);
    CSL_FINS(regVal,
             DSS_VP1_CONFIG_PIXELCLOCKGATED,
             advSignalCfg->pixelClockGated);
    CSL_FINS(regVal,
             DSS_VP1_CONFIG_PIXELDATAGATED,
             advSignalCfg->pixelDataGated);
    CSL_FINS(regVal, DSS_VP1_CONFIG_PIXELGATED, advSignalCfg->pixelGated);
    CSL_REG32_WR(&vpRegs->CONFIG, regVal);
}

void CSL_dssVpSetLcdSignalPolarityConfig(
                            CSL_dss_vpRegs *vpRegs,
                            const CSL_DssVpLcdSignalPolarityCfg *polarityCfg)
{
    uint32_t regVal;
    uint32_t dvoActVidPolarityVal, hsPolarityVal, vsPolarityVal;

    /* FVID2 defines low polarity as 0 whereas HW defines as 1, hence modify
     * the values accordingly */
    if(FVID2_POL_HIGH == polarityCfg->actVidPolarity)
    {
        dvoActVidPolarityVal = CSL_DSS_VP1_POL_FREQ_IEO_VAL_ACBAHIGH;
    }
    else
    {
        dvoActVidPolarityVal = CSL_DSS_VP1_POL_FREQ_IEO_VAL_ACBALOW;
    }
    if(FVID2_POL_HIGH == polarityCfg->hsPolarity)
    {
        hsPolarityVal = CSL_DSS_VP1_POL_FREQ_IHS_VAL_LCKPINAH;
    }
    else
    {
        hsPolarityVal = CSL_DSS_VP1_POL_FREQ_IHS_VAL_LCKPINAL;
    }
    if(FVID2_POL_HIGH == polarityCfg->vsPolarity)
    {
        vsPolarityVal = CSL_DSS_VP1_POL_FREQ_IVS_VAL_FCKPINAH;
    }
    else
    {
        vsPolarityVal = CSL_DSS_VP1_POL_FREQ_IVS_VAL_FCKPINAL;
    }

    /* Set POL_FREQ fields */
    regVal = CSL_REG32_RD(&vpRegs->POL_FREQ);
    CSL_FINS(regVal,
             DSS_VP1_POL_FREQ_IEO,
             dvoActVidPolarityVal);
    CSL_FINS(regVal,
             DSS_VP1_POL_FREQ_IPC,
             polarityCfg->pixelClkPolarity);
    CSL_FINS(regVal,
             DSS_VP1_POL_FREQ_IHS,
             hsPolarityVal);
    CSL_FINS(regVal,
             DSS_VP1_POL_FREQ_IVS,
             vsPolarityVal);
    CSL_REG32_WR(&vpRegs->POL_FREQ, regVal);
}

void CSL_dssVpEnableTvGamma(CSL_dss_vpRegs *vpRegs,
                            const CSL_DssVpGammaCfg *gammaCfg)
{
    uint32_t regVal, index;

    if(TRUE == gammaCfg->gammaEnable)
    {
        for (index = 0U; index < CSL_DSS_NUM_LUT_ENTRIES; index++)
        {
            regVal = (index << 24U) |
                     (gammaCfg->gammaData[index] & 0x00FFFFFFU);
            CSL_REG32_WR(&vpRegs->GAMMA_TABLE_0, regVal);
        }

        regVal = CSL_REG32_RD(&vpRegs->CONFIG);
        CSL_FINS(regVal,
                 DSS_VP1_CONFIG_GAMMAENABLE,
                 CSL_DSS_VP1_CONFIG_GAMMAENABLE_VAL_GAMMAENB);
        CSL_REG32_WR(&vpRegs->CONFIG, regVal);
    }
    else
    {
        regVal = CSL_REG32_RD(&vpRegs->CONFIG);
        CSL_FINS(regVal,
                 DSS_VP1_CONFIG_GAMMAENABLE,
                 CSL_DSS_VP1_CONFIG_GAMMAENABLE_VAL_GAMMADIS);
        CSL_REG32_WR(&vpRegs->CONFIG, regVal);
    }
}

void CSL_dssVpSetCSCCoeff(CSL_dss_vpRegs *vpRegs,
                          const CSL_DssCscCoeff *cscCoeff,
                          uint32_t cscPos,
                          uint32_t cscEnable)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&vpRegs->CSC_COEF0);
    CSL_FINS(regVal, DSS_VP1_CSC_COEF0_C00, ((uint32_t) cscCoeff->c00));
    CSL_FINS(regVal, DSS_VP1_CSC_COEF0_C01, ((uint32_t) cscCoeff->c01));
    CSL_REG32_WR(&vpRegs->CSC_COEF0, regVal);

    regVal = CSL_REG32_RD(&vpRegs->CSC_COEF1);
    CSL_FINS(regVal, DSS_VP1_CSC_COEF1_C02, ((uint32_t) cscCoeff->c02));
    CSL_FINS(regVal, DSS_VP1_CSC_COEF1_C10, ((uint32_t) cscCoeff->c10));
    CSL_REG32_WR(&vpRegs->CSC_COEF1, regVal);

    regVal = CSL_REG32_RD(&vpRegs->CSC_COEF2);
    CSL_FINS(regVal, DSS_VP1_CSC_COEF2_C11, ((uint32_t) cscCoeff->c11));
    CSL_FINS(regVal, DSS_VP1_CSC_COEF2_C12, ((uint32_t) cscCoeff->c12));
    CSL_REG32_WR(&vpRegs->CSC_COEF2, regVal);

    regVal = CSL_REG32_RD(&vpRegs->CSC_COEF3);
    CSL_FINS(regVal, DSS_VP1_CSC_COEF3_C20, ((uint32_t) cscCoeff->c20));
    CSL_FINS(regVal, DSS_VP1_CSC_COEF3_C21, ((uint32_t) cscCoeff->c21));
    CSL_REG32_WR(&vpRegs->CSC_COEF3, regVal);

    regVal = CSL_REG32_RD(&vpRegs->CSC_COEF4);
    CSL_FINS(regVal, DSS_VP1_CSC_COEF4_C22, ((uint32_t) cscCoeff->c22));
    CSL_REG32_WR(&vpRegs->CSC_COEF4, regVal);

    regVal = CSL_REG32_RD(&vpRegs->CSC_COEF5);
    CSL_FINS(regVal,
             DSS_VP1_CSC_COEF5_PREOFFSET1,
             ((uint32_t) cscCoeff->preOffset1));
    CSL_FINS(regVal,
             DSS_VP1_CSC_COEF5_PREOFFSET2,
             ((uint32_t) cscCoeff->preOffset2));
    CSL_REG32_WR(&vpRegs->CSC_COEF5, regVal);

    regVal = CSL_REG32_RD(&vpRegs->CSC_COEF6);
    CSL_FINS(regVal,
             DSS_VP1_CSC_COEF6_PREOFFSET3,
             ((uint32_t) cscCoeff->preOffset3));
    CSL_FINS(regVal,
             DSS_VP1_CSC_COEF6_POSTOFFSET1,
             ((uint32_t) cscCoeff->postOffset1));
    CSL_REG32_WR(&vpRegs->CSC_COEF6, regVal);

    regVal = CSL_REG32_RD(&vpRegs->CSC_COEF7);
    CSL_FINS(regVal,
             DSS_VP1_CSC_COEF7_POSTOFFSET2,
             ((uint32_t) cscCoeff->postOffset2));
    CSL_FINS(regVal,
             DSS_VP1_CSC_COEF7_POSTOFFSET3,
             ((uint32_t) cscCoeff->postOffset3));
    CSL_REG32_WR(&vpRegs->CSC_COEF7, regVal);

    regVal = CSL_REG32_RD(&vpRegs->CONFIG);
    CSL_FINS(regVal, DSS_VP1_CONFIG_COLORCONVPOS, cscPos);
    CSL_FINS(regVal, DSS_VP1_CONFIG_FULLRANGE, cscCoeff->cscRange);
    CSL_FINS(regVal, DSS_VP1_CONFIG_COLORCONVENABLE, cscEnable);
    CSL_REG32_WR(&vpRegs->CONFIG, regVal);
}

void CSL_dssVpSetSafetySignSeedVal(CSL_dss_vpRegs *vpRegs,
                                   uint32_t signSeedVal)
{
    uint32_t regVal;

   regVal = CSL_REG32_RD(&vpRegs->SAFETY_LFSR_SEED);
   CSL_FINS(regVal, DSS_VP1_SAFETY_LFSR_SEED_SEED, signSeedVal);
   CSL_REG32_WR(&vpRegs->SAFETY_LFSR_SEED, regVal);
}

void CSL_dssVpSetSafetyReferenceSign(CSL_dss_vpRegs *vpRegs,
                                     uint32_t referenceSign,
                                     uint32_t regionId)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&vpRegs->SAFETY_REF_SIGNATURE[regionId]);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_REF_SIGNATURE_SIGNATURE,
             referenceSign);
    CSL_REG32_WR(&vpRegs->SAFETY_REF_SIGNATURE[regionId], regVal);
}

void CSL_dssVpSetSafetyChkConfig(CSL_dss_vpRegs *vpRegs,
                                 const CSL_DssSafetyChkCfg *safetyCfg,
                                 uint32_t regionId)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&vpRegs->SAFETY_POSITION[regionId]);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_POSITION_POSX,
             safetyCfg->regionPos.startX);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_POSITION_POSY,
             safetyCfg->regionPos.startY);
    CSL_REG32_WR(&vpRegs->SAFETY_POSITION[regionId], regVal);

    regVal = CSL_REG32_RD(&vpRegs->SAFETY_SIZE[regionId]);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_SIZE_SIZEX,
             safetyCfg->regionSize.width);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_SIZE_SIZEY,
             safetyCfg->regionSize.height);
    CSL_REG32_WR(&vpRegs->SAFETY_SIZE[regionId], regVal);

    regVal = CSL_REG32_RD(&vpRegs->SAFETY_ATTRIBUTES[regionId]);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_ATTRIBUTES_CAPTUREMODE,
             safetyCfg->safetyChkMode);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_ATTRIBUTES_SEEDSELECT,
             safetyCfg->seedSelectEnable);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_ATTRIBUTES_THRESHOLD,
             safetyCfg->thresholdValue);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_ATTRIBUTES_FRAMESKIP,
             safetyCfg->frameSkip);
    CSL_FINS(regVal,
             DSS_VP1_SAFETY_ATTRIBUTES_ENABLE,
             safetyCfg->safetyChkEnable);
    CSL_REG32_WR(&vpRegs->SAFETY_ATTRIBUTES[regionId], regVal);
}

uint32_t CSL_dssVpGetSafetySign(const CSL_dss_vpRegs *vpRegs,
                                uint32_t regionId)
{
    uint32_t regVal, signatureVal;

    regVal = CSL_REG32_RD(&vpRegs->SAFETY_CAPT_SIGNATURE[regionId]);
    signatureVal = CSL_FEXT(regVal,
                           DSS_VP1_SAFETY_CAPT_SIGNATURE_SIGNATURE);
   return signatureVal;
}

void CSL_dssVpOldiReset(const CSL_dss_vpRegs *vpRegs)
{
    uint32_t regVal;

    /* OLDI Soft Reset */
    regVal = CSL_REG32_RD(&vpRegs->DSS_OLDI_CFG);
    CSL_FINS(regVal,
             DSS_VP1_DSS_OLDI_CFG_SOFTRST,
             (uint32_t) CSL_DSS_VP1_DSS_OLDI_CFG_SOFTRST_VAL_DEASSERT);
    CSL_REG32_WR(&vpRegs->DSS_OLDI_CFG, regVal);
}

void CSL_dssVpSetOldiConfig(CSL_dss_vpRegs *vpRegs,
                            const CSL_DssVpOldiCfg *oldiCfg)
{
    uint32_t regVal, dePolarityVal;

    if(FVID2_POL_HIGH == oldiCfg->dataEnablePolarity)
    {
        dePolarityVal = CSL_DSS_VP1_DSS_OLDI_CFG_DEPOL_VAL_HIGH;
    }
    else
    {
        dePolarityVal = CSL_DSS_VP1_DSS_OLDI_CFG_DEPOL_VAL_LOW;
    }

    regVal = CSL_REG32_RD(&vpRegs->DSS_OLDI_CFG);
    CSL_FINS(regVal,
             DSS_VP1_DSS_OLDI_CFG_MAP,
             oldiCfg->oldiMapType);
    CSL_FINS(regVal,
             DSS_VP1_DSS_OLDI_CFG_DEPOL,
             dePolarityVal);
    CSL_FINS(regVal,
             DSS_VP1_DSS_OLDI_CFG_MSB,
             oldiCfg->dssBitDepth);
    CSL_FINS(regVal,
             DSS_VP1_DSS_OLDI_CFG_DUALMODESYNC,
             oldiCfg->dualModeSync);
    CSL_REG32_WR(&vpRegs->DSS_OLDI_CFG, regVal);
}

void CSL_dssVpOldiEnable(CSL_dss_vpRegs *vpRegs, uint32_t enable)
{
    uint32_t regVal;

    /* OLDI Enable */
    regVal = CSL_REG32_RD(&vpRegs->DSS_OLDI_CFG);
    CSL_FINS(regVal,
             DSS_VP1_DSS_OLDI_CFG_ENABLE,
             enable);
    CSL_REG32_WR(&vpRegs->DSS_OLDI_CFG, regVal);
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static void CSL_dssVpSetVideoFormatConfig(CSL_dss_vpRegs *vpRegs,
                                          uint32_t dvoFormat,
                                          uint32_t cscRange)
{
    uint32_t regVal, isCscNeeded;

    if((FVID2_DV_BT656_EMBSYNC == dvoFormat) ||
       (FVID2_DV_BT1120_EMBSYNC == dvoFormat))
    {
        isCscNeeded = TRUE;
    }
    else
    {
        isCscNeeded = FALSE;
    }

    if(TRUE == isCscNeeded)
    {
        if (CSL_DSS_CSC_RANGE_LIMITED == cscRange)
        {
            CSL_dssVpSetCSCCoeff(vpRegs,
                                 &gVpCscLimtedRangeCoeff,
                                 CSL_DSS_VP_CSC_POS_AFTER_GAMMA,
                                 TRUE);
        }
        else
        {
            CSL_dssVpSetCSCCoeff(vpRegs,
                                 &gVpCscFullRangeCoeff,
                                 CSL_DSS_VP_CSC_POS_AFTER_GAMMA,
                                 TRUE);
        }
        regVal = CSL_REG32_RD(&vpRegs->CONFIG);
        if(FVID2_DV_BT656_EMBSYNC == dvoFormat)
        {
            CSL_FINS(regVal, DSS_VP1_CONFIG_BT656ENABLE,  (uint32_t) TRUE);
            CSL_FINS(regVal, DSS_VP1_CONFIG_BT1120ENABLE, (uint32_t) FALSE);
        }
        else /* FVID2_DV_BT1120_EMBSYNC = dvoFormat */
        {
            CSL_FINS(regVal, DSS_VP1_CONFIG_BT656ENABLE,  (uint32_t) FALSE);
            CSL_FINS(regVal, DSS_VP1_CONFIG_BT1120ENABLE, (uint32_t) TRUE);
        }
        CSL_REG32_WR(&vpRegs->CONFIG, regVal);
    }
    else
    {
        regVal = CSL_REG32_RD(&vpRegs->CONFIG);
        CSL_FINS(regVal, DSS_VP1_CONFIG_BT656ENABLE,     (uint32_t) FALSE);
        CSL_FINS(regVal, DSS_VP1_CONFIG_BT1120ENABLE,    (uint32_t) FALSE);
        CSL_FINS(regVal, DSS_VP1_CONFIG_COLORCONVENABLE, (uint32_t) FALSE);
        CSL_REG32_WR(&vpRegs->CONFIG, regVal);
    }
}

static void CSL_dssVpSetVideoIfWidth(CSL_dss_vpRegs *vpRegs,
                                     uint32_t fvid2Width)
{
    uint32_t regVal, index = 0U;
    uint32_t dssWidth = FVID2_VIFW_24BIT;

    for(index = 0U;
        index <  CSL_DSS_VP_NUM_ENTRIES_WIDTH_FORMAT_TABLE;
        index++)
    {
        if(fvid2Width == gDssVpWidthFmt[index].fvid2Width)
        {
            dssWidth = gDssVpWidthFmt[index].dssWidth;
            break;
        }
    }

    regVal = CSL_REG32_RD(&vpRegs->CONTROL);
    CSL_FINS(regVal, DSS_VP1_CONTROL_DATALINES, dssWidth);
    CSL_REG32_WR(&vpRegs->CONTROL, regVal);
}

static void CSL_dssVpGetTdmHblankFact(const CSL_dss_vpRegs *vpRegs,
                                      uint32_t *hBlankMultFact,
                                      uint32_t *hBlankDivFact)
{
    uint32_t tdmRegVal, tdmCycleFormat, tdmEnable;

    /* If TDM mode is enabled The H Blank timing parameters should be
     * modified based on TDM Cycle format */
    tdmRegVal = CSL_REG32_RD(&vpRegs->CONTROL);
    tdmEnable = CSL_FEXT(tdmRegVal, DSS_VP1_CONTROL_TDMENABLE);
    if (TRUE == tdmEnable)
    {
        tdmCycleFormat = CSL_FEXT(tdmRegVal,
                                  DSS_VP1_CONTROL_TDMCYCLEFORMAT);

        if (CSL_DSS_VP_TDM_CYCLE_2PERPIXEL == tdmCycleFormat)
        {
            /* 2 Cycles for 1 Pixel: Multiply HBlank by 2 */
            *hBlankMultFact = 2U;
            *hBlankDivFact  = 1U;
        }
        else if (CSL_DSS_VP_TDM_CYCLE_3PERPIXEL == tdmCycleFormat)
        {
            /* 3 Cycles for 1 Pixel: Multiply HBlank by 3 */
            *hBlankMultFact = 3U;
            *hBlankDivFact  = 1U;
        }
        else if (CSL_DSS_VP_TDM_CYCLE_3PER2PIXEL == tdmCycleFormat)
        {
            /* 3 Cycles for 2 Pixel: Multiply HBlank by 1.5 */
            *hBlankMultFact = 3U;
            *hBlankDivFact  = 2U;
        }
        else /* CSL_DSS_VP_TDM_CYCLE_1PERPIXEL == tdmCycleFormat */
        {
            /* Default to 1 cycle for 1 pixel: Don't modify HBlank */
            *hBlankMultFact = 1U;
            *hBlankDivFact  = 1U;
        }
    }
    else
    {
        /* TDM is disabled: Don't modify HBlank */
        *hBlankMultFact = 1U;
        *hBlankDivFact  = 1U;
    }
}

static int32_t CSL_dssVpValidateLcdBlankTiming(
                            const CSL_DssVpLcdBlankTimingCfg *lcdBlankTimingCfg,
                            uint32_t hBlankMultFact,
                            uint32_t hBlankDivFact)
{
    int32_t retVal = CSL_PASS;


    /* Check HBlank timing */
    if ((((lcdBlankTimingCfg->hBackPorch * hBlankMultFact)
           / hBlankDivFact) > CSL_DSS_VP1_TIMING_H_HBP_MAX) ||
        (((lcdBlankTimingCfg->hFrontPorch * hBlankMultFact)
           / hBlankDivFact) > CSL_DSS_VP1_TIMING_H_HFP_MAX) ||
        (((lcdBlankTimingCfg->hSyncLen * hBlankMultFact)
           / hBlankDivFact) > CSL_DSS_VP1_TIMING_H_HSW_MAX))
    {
        retVal = CSL_EBADARGS;
    }

    /* Check VBlank timing */
    if ((lcdBlankTimingCfg->vBackPorch > CSL_DSS_VP1_TIMING_V_VBP_MAX) ||
        (lcdBlankTimingCfg->vFrontPorch > CSL_DSS_VP1_TIMING_V_VFP_MAX) ||
        (lcdBlankTimingCfg->vSyncLen > CSL_DSS_VP1_TIMING_V_VSW_MAX))
    {
        retVal = CSL_EBADARGS;
    }

    return (retVal);
}

static int32_t CSL_dssVpSetDiscSyncBlanking(
                                    CSL_dss_vpRegs *vpRegs,
                                    const CSL_DssVpLcdBlankTimingCfg *blankCfg)
{
    int32_t retVal = CSL_PASS;
    uint32_t regVal;
    uint32_t hBlankMultFact, hBlankDivFact;

    CSL_dssVpGetTdmHblankFact(vpRegs,
                              &hBlankMultFact,
                              &hBlankDivFact);
    retVal = CSL_dssVpValidateLcdBlankTiming(blankCfg,
                                             hBlankMultFact,
                                             hBlankDivFact);

    if(CSL_PASS == retVal)
    {
        regVal = CSL_REG32_RD(&vpRegs->TIMING_H);
        CSL_FINS(regVal,
                 DSS_VP1_TIMING_H_HBP,
                 (((blankCfg->hBackPorch * hBlankMultFact) /
                    hBlankDivFact)- 1U));
        CSL_FINS(regVal,
                 DSS_VP1_TIMING_H_HFP,
                 (((blankCfg->hFrontPorch * hBlankMultFact) /
                    hBlankDivFact)- 1U));
        CSL_FINS(regVal,
                 DSS_VP1_TIMING_H_HSW,
                 (((blankCfg->hSyncLen * hBlankMultFact) /
                    hBlankDivFact)- 1U));
        CSL_REG32_WR(&vpRegs->TIMING_H, regVal);

        regVal = CSL_REG32_RD(&vpRegs->TIMING_V);
        CSL_FINS(regVal, DSS_VP1_TIMING_V_VBP, blankCfg->vBackPorch);
        CSL_FINS(regVal, DSS_VP1_TIMING_V_VFP, blankCfg->vFrontPorch);
        CSL_FINS(regVal, DSS_VP1_TIMING_V_VSW, blankCfg->vSyncLen - 1);
        CSL_REG32_WR(&vpRegs->TIMING_V, regVal);
    }

    return (retVal);
}

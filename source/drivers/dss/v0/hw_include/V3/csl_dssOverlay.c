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
 *  \file csl_dssOverlay.c
 *
 *  \brief File containing the DSS Overlay CSL FL APIs.
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

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void CSL_dssOverlaySetPanelColorKey(CSL_dss_overlayRegs *overlayRegs,
                                           uint32_t colorKeyEnable,
                                           uint32_t colorKeySel);

static void CSL_dssOverlaySetTransColorKey(CSL_dss_overlayRegs *overlayRegs,
                                           uint32_t transColorKeyMin,
                                           uint32_t transColorKeyMax);

static void CSL_dssOverlaySetBgColor(CSL_dss_overlayRegs *overlayRegs,
                                     uint32_t bgColor);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CSL_dssOverlaySetConfig(CSL_dss_overlayRegs *overlayRegs,
                             const CSL_DssOverlayCfg *overlayCfg)
{

    CSL_dssOverlaySetPanelColorKey(overlayRegs,
                                   overlayCfg->colorKeyEnable,
                                   overlayCfg->colorKeySel);
    CSL_dssOverlaySetTransColorKey(overlayRegs,
                                   overlayCfg->transColorKeyMin,
                                   overlayCfg->transColorKeyMax);
    CSL_dssOverlaySetBgColor(overlayRegs, overlayCfg->backGroundColor);
}

void CSL_dssOverlayColorBarEnable(CSL_dss_overlayRegs *overlayRegs,
                                  uint32_t enable)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&overlayRegs->CONFIG);
    CSL_FINS(regVal,
             DSS_OVR1_CONFIG_COLORBAREN,
             enable);
    CSL_REG32_WR(&overlayRegs->CONFIG, regVal);
}

void CSL_dssOverlaySetLayerConfig(CSL_dss_overlayRegs *overlayRegs,
                                  const CSL_DssOverlayLayerCfg *layerCfg)
{
    uint32_t regVal;
    /* The maximum value for the width and height of resolution is 16384U(2^14) according to spec, and we need to program `value - 1`. */
    const Fvid2_PosConfig maxPosCfg = {.startX = 16383U, .startY = 16383U};
    const CSL_DssOverlayPipePosCfg maxPipePosCfg = {.layerPos = maxPosCfg};

    regVal = CSL_REG32_RD(&overlayRegs->ATTRIBUTES[layerCfg->layerNum]);
    CSL_FINS(regVal,
             DSS_OVR1_ATTRIBUTES_CHANNELIN,
             layerCfg->inputPipe);
    CSL_FINS(regVal,
             DSS_OVR1_ATTRIBUTES_ENABLE,
             layerCfg->layerEnable);
    if ((uint32_t)FALSE == layerCfg->layerEnable)
    {
        /* Need to hide the layer from visible range, before disabling it. */
        CSL_dssOverlaySetPipePosConfig(overlayRegs, &maxPipePosCfg, layerCfg->layerNum);
    }

    CSL_REG32_WR(&overlayRegs->ATTRIBUTES[layerCfg->layerNum], regVal);
}

void CSL_dssOverlaySetPipePosConfig(CSL_dss_overlayRegs *overlayRegs,
                                    const CSL_DssOverlayPipePosCfg *pipePosCfg,
                                    uint32_t layerNum)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&overlayRegs->ATTRIBUTES[layerNum]);
    CSL_FINS(regVal,
             DSS_OVR1_ATTRIBUTES_POSX,
             pipePosCfg->layerPos.startX);
    CSL_FINS(regVal,
             DSS_OVR1_ATTRIBUTES_POSY,
             pipePosCfg->layerPos.startY);
    CSL_REG32_WR(&overlayRegs->ATTRIBUTES[layerNum], regVal);
}

uint32_t CSL_dssOverlayGetEnabledPipeLayerNum(
                                        const CSL_dss_overlayRegs *overlayRegs,
                                        uint32_t pipeId)
{
    uint32_t regVal, i, enable, inputPipe;
    uint32_t layerNum = CSL_DSS_OVERLAY_LAYER_INVALID;
    for(i=0U; i<CSL_DSS_VID_PIPE_ID_MAX; i++)
    {
        regVal = CSL_REG32_RD(&overlayRegs->ATTRIBUTES[i]);
        enable = CSL_FEXT(regVal, DSS_OVR1_ATTRIBUTES_ENABLE);
        inputPipe = CSL_FEXT(regVal, DSS_OVR1_ATTRIBUTES_CHANNELIN);
        if(((uint32_t)TRUE == enable) && (pipeId == inputPipe))
        {
            layerNum = i;
            break;
        }
    }

    return layerNum;
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static void CSL_dssOverlaySetPanelColorKey(CSL_dss_overlayRegs *overlayRegs,
                                           uint32_t colorKeyEnable,
                                           uint32_t colorKeySel)
{
    uint32_t regVal;

    regVal = CSL_REG32_RD(&overlayRegs->CONFIG);
    CSL_FINS(regVal, DSS_OVR1_CONFIG_TCKLCDSELECTION, colorKeySel);
    CSL_FINS(regVal, DSS_OVR1_CONFIG_TCKLCDENABLE, colorKeyEnable);
    CSL_REG32_WR(&overlayRegs->CONFIG, regVal);
}

static void CSL_dssOverlaySetTransColorKey(CSL_dss_overlayRegs *overlayRegs,
                                           uint32_t transColorKeyMin,
                                           uint32_t transColorKeyMax)
{
    uint32_t transColorKeyMin0, transColorKeyMin1;
    uint32_t transColorKeyMax0, transColorKeyMax1;
    uint32_t transColorBComp, transColorGComp, transColorRComp;

    /* Convert 8-bit depth to 12-bit color depth*/
    transColorBComp = ((transColorKeyMin & 0xFFU) << 0x4U);
    transColorGComp = (((transColorKeyMin & 0xFF00U) >> 8) << 0x4U);
    transColorRComp = (((transColorKeyMin & 0xFF0000U) >> 16) << 0x4U);

    transColorKeyMin0 = ((transColorRComp & 0xFFU) << 24) |
                        (transColorGComp << 12) |
                        (transColorBComp);
    transColorKeyMin1 = ((transColorRComp & 0xF00U) >> 8);
    CSL_REG32_WR(&overlayRegs->TRANS_COLOR_MIN, transColorKeyMin0);
    CSL_REG32_WR(&overlayRegs->TRANS_COLOR_MIN2, transColorKeyMin1);

    /* Convert 8-bit depth to 12-bit color depth*/
    transColorBComp = ((transColorKeyMax & 0xFFU) << 0x4U);
    transColorGComp = (((transColorKeyMax & 0xFF00U) >> 8) << 0x4U);
    transColorRComp = (((transColorKeyMax & 0xFF0000U) >> 16) << 0x4U);

    /* Last Four Bits are set for MAX color */
    transColorRComp |= 0xFU;
    transColorGComp |= 0xFU;
    transColorBComp |= 0xFU;

    transColorKeyMax0 = ((transColorRComp & 0xFFU) << 24) |
                        (transColorGComp << 12) |
                        (transColorBComp);
    transColorKeyMax1 = ((transColorRComp & 0xF00U) >> 8);

    CSL_REG32_WR(&overlayRegs->TRANS_COLOR_MAX, transColorKeyMax0);
    CSL_REG32_WR(&overlayRegs->TRANS_COLOR_MAX2, transColorKeyMax1);
}

static void CSL_dssOverlaySetBgColor(CSL_dss_overlayRegs *overlayRegs,
                                     uint32_t bgColor)
{
    uint32_t bgColor0, bgColor1;
    uint32_t bgRComp, bgGComp, bgBComp;

    bgBComp = ((bgColor & 0xFFU) << 4);
    bgGComp = (((bgColor & 0xFF00U) >> 8) << 4);
    bgRComp = (((bgColor & 0xFF0000U) >> 16) << 4);

    bgColor0 = ((bgRComp & 0xFFU) << 24) | (bgGComp << 12) | (bgBComp);
    bgColor1 = ((bgRComp & 0xF00U) >> 8);

    CSL_REG32_WR(&overlayRegs->DEFAULT_COLOR, bgColor0);
    CSL_REG32_WR(&overlayRegs->DEFAULT_COLOR2, bgColor1);
}

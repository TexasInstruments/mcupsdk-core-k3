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
 *  \ingroup CSL_DSS
 *  \defgroup CSL_DSSOVERLAY DSS Overlay Hardware Layer
 *
 * This is hardware include layer for DSS overlay region.
 *  @{
 */

/**
 *  \file csl_dssOverlay.h
 *
 *  \brief DSS Overlay layer interface file.
 */

#ifndef CSL_DSSOVERLAY_H_
#define CSL_DSSOVERLAY_H_

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

/** \brief DSS Overlay Registers
 *
 *  DSS7 UL has two identical Overlay blocks, hence define a generic structure
 *  to have common APIs
 */
typedef CSL_dss_ovr1Regs CSL_dss_overlayRegs;

/**
 *  \anchor CSL_DssOverlayTransColor
 *  \name DSS Overlay Transparency Color Key Selection
 *
 *  @{
 */
/** \brief Destination transparency color key selected */
#define CSL_DSS_OVERLAY_TRANS_COLOR_DEST             \
                    ((uint32_t) CSL_DSS_OVR1_CONFIG_TCKLCDSELECTION_VAL_GDTK)
/** \brief Source transparency color key selected */
#define CSL_DSS_OVERLAY_TRANS_COLOR_SRC              \
                    ((uint32_t) CSL_DSS_OVR1_CONFIG_TCKLCDSELECTION_VAL_VSTK)
/** @} */

/**
 *  \anchor CSL_DssOverlayLayerNum
 *  \name DSS Overlay Layer Number
 *
 *  @{
 */
/** \brief Overlay Layer 0 */
#define CSL_DSS_OVERLAY_LAYER_NUM_0                     ((uint32_t) 0x0U)
/** \brief Overlay Layer 1 */
#define CSL_DSS_OVERLAY_LAYER_NUM_1                     ((uint32_t) 0x1U)
/** \brief Maximum overlay layers */
#define CSL_DSS_OVERLAY_LAYER_MAX                       ((uint32_t) 0x2U)
/** \brief Invalid Overlay Layer */
#define CSL_DSS_OVERLAY_LAYER_INVALID                   ((uint32_t) 0xFFU)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Configuration for DSS Overlay
 */
typedef struct
{
    uint32_t colorKeyEnable;
    /**< Enable Transparency Color Key
     *   FALSE: Disable Color Key
     *   TRUE:  Enable Color Key */
    uint32_t colorKeySel;
    /**< Transparency Color Key Selection. For valid values
     *   see \ref CSL_DssOverlayTransColor */
    uint32_t transColorKeyMin;
    /**< Minimum Transparency color key value in 24 bit RGB format
     *   31-----24 23-----16 15------8 7-------0
     *     Unused      R          G        B      */
    uint32_t transColorKeyMax;
    /**< Maximum Transparency color key value in 24 bit RGB format
     *   31-----24 23-----16 15------8 7-------0
     *     Unused      R          G        B      */
    uint32_t backGroundColor;
    /**< Background color value in 24 bit RGB format
     *   31-----24 23-----16 15------8 7-------0
     *     Unused      R          G        B      */
} CSL_DssOverlayCfg;

/**
 *  \brief Configuration for selecting overlay input layers
 */
typedef struct
{
    uint32_t layerEnable;
    /**< Overlay Layer Enable
     *   FALSE: Disable Overlay Layer
     *   TRUE: Enable Overlay Layer */
    uint32_t layerNum;
    /**< Overlay Layer Number. Refer \ref CSL_DssOverlayLayerNum for
     *   valid values */
    uint32_t inputPipe;
    /**< Video Pipe Id connected to Overlay. For valid values see
     *   \ref CSL_DssVidPipeId */
} CSL_DssOverlayLayerCfg;

/**
 *  \brief Video Pipe Position Configuration in Overlay
 */
typedef struct
{
    Fvid2_PosConfig layerPos;
    /**< Position of the layer described using #Fvid2_PosConfig
     *
     *   <b>startX</b>:<br>
     *   X position of the layer
     *   The first pixel on the left of the screen has the X-position 0 <br>
     *
     *   <b>startY</b>:<br>
     *   Y position of the layer
     *   The line at the top has the Y-position 0 <br>
     */
} CSL_DssOverlayPipePosCfg;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Configure the Overlay Params
 *
 *  \param overlayRegs     Pointer to a #CSL_dss_overlayRegs structure
 *                         containing the overlay configuration
 *  \param overlayCfg      Pointer to the #CSL_DssOverlayCfg structure.
 *                         This parameter should not be NULL
 *
 */
void CSL_dssOverlaySetConfig(CSL_dss_overlayRegs *overlayRegs,
                             const CSL_DssOverlayCfg *overlayCfg);

/**
 *  \brief Enable the Color Bar in DSS Overlay
 *
 *  \param overlayRegs     Pointer to a #CSL_dss_overlayRegs structure
 *                         containing the overlay configuration
 *  \param enable          Enable or disable the color bar
 *
 */
void CSL_dssOverlayColorBarEnable(CSL_dss_overlayRegs *overlayRegs,
                                  uint32_t enable);

/**
 *  \brief Configure the Overlay input selection
 *
 *  \param overlayRegs     Pointer to a #CSL_dss_overlayRegs structure
 *                         containing the overlay configuration
 *  \param layerCfg        Pointer to #CSL_DssOverlayLayerCfg structure.
 *                         This parameter should not be NULL
 *
 */
void CSL_dssOverlaySetLayerConfig(CSL_dss_overlayRegs *overlayRegs,
                                  const CSL_DssOverlayLayerCfg *layerCfg);

/**
 *  \brief Configure the Video Pipe Position in Overlay
 *
 *  \param overlayRegs     Pointer to a #CSL_dss_overlayRegs structure
 *                         containing the overlay configuration
 *  \param pipePosCfg      Pointer to #CSL_DssOverlayPipePosCfg structure.
 *                         This parameter should not be NULL
 *  \param layerNum        Layer Number
 *
 */
void CSL_dssOverlaySetPipePosConfig(CSL_dss_overlayRegs *overlayRegs,
                                    const CSL_DssOverlayPipePosCfg *pipePosCfg,
                                    uint32_t layerNum);

/**
 *  \brief Get the layer number where a particular Video Pipe is connected
 *
 *  \param overlayRegs     Pointer to a #CSL_dss_overlayRegs structure
 *                         containing the overlay configuration
 *  \param pipeId          Pipe Id. Refer to \ref CSL_DssVidPipeId for values
 *
 *  \return \ref CSL_DssOverlayLayerNum Layer Number to which pipe is connected.
 *               API returns CSL_DSS_OVERLAY_LAYER_INVALID if pipe is not
 *               connected to any overlay layer
 */
uint32_t CSL_dssOverlayGetEnabledPipeLayerNum(
                                        const CSL_dss_overlayRegs *overlayRegs,
                                        uint32_t pipeId);

/* ========================================================================== */
/*                      Static Function Declarations                          */
/* ========================================================================== */

/**
 *  \brief  CSL_DssOverlayCfg structure init function
 *
 *  \param  overlayCfg Pointer to #CSL_DssOverlayCfg structure
 *
 */
static inline void CSL_dssOverlayCfgInit(
    CSL_DssOverlayCfg *overlayCfg);

/**
 *  \brief  CSL_DssOverlayLayerCfg structure init function
 *
 *  \param  layerCfg Pointer to #CSL_DssOverlayLayerCfg structure
 *
 */
static inline void CSL_dssOverlayLayerCfgInit(
    CSL_DssOverlayLayerCfg *layerCfg);

/**
 *  \brief  CSL_DssOverlayPipePosCfg structure init function
 *
 *  \param  pipePosCfg Pointer to #CSL_DssOverlayPipePosCfg structure
 *
 */
static inline void CSL_dssOverlayPipePosCfgInit(
    CSL_DssOverlayPipePosCfg *pipePosCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void CSL_dssOverlayCfgInit(
    CSL_DssOverlayCfg *overlayCfg)
{
    if(NULL != overlayCfg)
    {
        overlayCfg->colorKeyEnable = FALSE;
        overlayCfg->colorKeySel = CSL_DSS_OVERLAY_TRANS_COLOR_DEST;
        overlayCfg->transColorKeyMin = 0x0U;
        overlayCfg->transColorKeyMax = 0x0U;
        overlayCfg->backGroundColor = 0x0U;
    }
}

static inline void CSL_dssOverlayLayerCfgInit(
    CSL_DssOverlayLayerCfg *layerCfg)
{
    if(NULL != layerCfg)
    {
        layerCfg->layerEnable = FALSE;
        layerCfg->inputPipe = CSL_DSS_VID_PIPE_ID_VID1;
        layerCfg->layerNum = CSL_DSS_OVERLAY_LAYER_NUM_0;
    }
}

static inline void CSL_dssOverlayPipePosCfgInit(
    CSL_DssOverlayPipePosCfg *pipePosCfg)
{
    if(NULL != pipePosCfg)
    {
        Fvid2PosConfig_init(&pipePosCfg->layerPos);
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSL_DSSOVERLAY_H_ */

/** @} */

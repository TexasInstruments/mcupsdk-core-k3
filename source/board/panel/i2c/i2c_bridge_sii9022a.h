/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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
 *  \file bridge_sii9022a.h
 *
 *  \brief SII9022a bridge header file.
 */

#ifndef I2C_BRIDGE_SII9022A_H_
#define I2C_BRIDGE_SII9022A_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/fvid2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define I2C_BRIDGE_SII9022A_OBJ_STATE_UNUSED       (uint32_t) (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define I2C_BRIDGE_SII9022A_OBJ_STATE_IDLE         (uint32_t) (1U)
/** \brief Device state - Not initialized. */
#define I2C_BRIDGE_SII9022A_NOT_INITED             (uint32_t) (0U)
/** \brief Device state - initialized successfully. */
#define I2C_BRIDGE_SII9022A_INITED                 (uint32_t) (1U)

/**
 *  \brief Panel commands used to control panel.
 *  @{
 */

/**
 *  \brief Query hot plug detect (HPD) for HDMI cable connect or disconnect.
 */
#define I2C_BRIDGE_SII9022A_GET_DETAILED_CHIP_ID        (uint32_t)(0x0A00U)

/**
 *  \brief Query Hot Plug Detect status
 *
 */
#define I2C_BRIDGE_SII9022A_QUERY_HPD                   (uint32_t)(0x0A01U)

/**
 *  \brief Set mode configuration in HDMI 9022A
 *
 */
#define I2C_BRIDGE_SII9022A_ENC_SET_MODE                (uint32_t)(0x0A02U)

/**
 * \brief Enum defining output type
 */
typedef enum
{
    BRIDGE_SII9022A_HDMI_RGB = 0,
    /**< Output format is RGB over HDMI interface */
    BRIDGE_SII9022A_HDMI_YUV444,
    /**< Output format is YUV444 over HDMI interface */
    BRIDGE_SII9022A_HDMI_YUV422,
    /**< Output format is YUV422 over HDMI interface */
    BRIDGE_SII9022A_DVI_RGB,
    /**< Output format is RGB over DVI interface */
    BRIDGE_SII9022A_MAX_FORMAT
    /**< Max output format */
} BridgeSii9022a_OutputFormat;

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure for getting detailed HDMI chip Id.
 */
typedef struct
{
    uint32_t deviceId;
    /**< Device Id TPI. */
    uint32_t deviceProdRevId;
    /**< Device Production Revision Id TPI. */
    uint32_t tpiRevId;
    /**< TPI Revision Id TPI. */
    uint32_t hdcpRevTpi;
    /**< HDCP revision TPI. */
} BridgeSii9022a_HdmiChipId;

/**
 *  \brief Structure for hot plug detection parameters.
 *
 */
typedef struct
{
    uint32_t hpdEvtPending;
    /**< Hot Plug Connection Event Pending. */
    uint32_t busError;
    /**< Receiver Sense Event Pending or CTRL Bus Error. */
    uint32_t hpdStatus;
    /**< Hot Plug Pin Current Status. */
} BridgeSii9022a_HpdParams;

typedef struct
{
    Fvid2_Standard standard;
    uint32_t         modeCode;
    uint32_t         pixClk;
    uint32_t         vFreq;
    uint32_t         pixels;
    uint32_t         lines;
    struct
    {
        uint32_t hBitToHSync;
        uint32_t field2Offset;
        uint32_t hWidth;
        uint32_t vBitToVSync;
        uint32_t vWidth;
    } embSyncPrms;
    struct
    {
        uint32_t deDelay;
        /**< Width of the area to the left of the active display */
        uint32_t deTop;
        /**< Height of the area to the top of the active display */
        uint32_t deCnt;
        /**< Width of the active display */
        uint32_t deLine;
        /**< Height of the active display */
    } extSyncPrms;
} BridgeSii9022a_ModeInfo;

/**
 *  \brief SII9022A driver handle object.
 */
typedef struct
{
    uint32_t                  hpd;
    /**< HDMI Hot plug detect. */
    uint8_t                   syncCfgReg;
    /**< Sync Configuration Register. */
    uint8_t                   syncPolarityReg;
    /**< Sync polarity Register. */
    uint32_t                  isRgbOutput;
    /**< Is output RGB. */
    uint32_t                  inBusCfg;
    /**< Input bus config. */
    uint32_t                  outputFormat;
    /**< Type of the OUTPUT i.e. HDMI of DVI. */
    /**< SII9022A params */
    BridgeSii9022a_HdmiChipId hdmiChipId;
    /**< HDMI Chip id. */
    BridgeSii9022a_ModeInfo   modeInfo;
    /**< Bridge mode information. */
} BridgeSii9022a_Object;

/* ========================================================================== */
/*                          Global Variables                                  */
/* ========================================================================== */

extern Panel_Fxns gPanelBridgeSii9022aFxns;

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef I2C_BRIDGE_SII9022A_H_ */
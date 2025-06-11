/**********************************************************************
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.00.31660be
 *          Do not edit it manually.
 **********************************************************************
 * Cadence Core Driver for MIPI DSITX Host Controller
 **********************************************************************/

/* parasoft-begin-suppress METRICS-18-3 "Follow the Cyclomatic Complexity limit of 10" */
/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions" */
/* parasoft-begin-suppress METRICS-39-3 "The value of VOCF metric for a function should not be higher than 4" */
/* parasoft-begin-suppress METRICS-41-3 "Number of blocks of comments per statement" */
/* parasoft-begin-suppress MISRA2012-RULE-8_7 "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit" */

/**
 * This file contains sanity API functions. The purpose of sanity functions
 * is to check input parameters validity. They take the same parameters as
 * original API functions and return 0 on success or CDN_EINVAL on wrong parameter
 * value(s).
 */

#include <drivers/dss/v1/hw_include/dsi/csl_dsi.h>
#include <drivers/dss/v1/hw_include/dsi/include/dsitx_priv.h>
#include "dsitx_sanity.h"

/**
 * Function to validate struct DphyPwrRstConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_DphyPwrRstConfigSF(const DSITX_DphyPwrRstConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->dphyDRstb > (0xFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dphyDPdn > (0xFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct DphyConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_DphyConfigSF(const DSITX_DphyConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->clkDivisionRatio > (0xBU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->hstxTimeout > (0x3FFFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->lprxTimeout > (0x3FFFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->clkLaneUlpTimeout > (0x1FFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->dataLaneUlpTimeout > (0x1FFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct DataPathConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_DataPathConfigSF(const DSITX_DataPathConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->interfaceMode != DSITX_IF_MODE_COMMAND) &&
            (obj->interfaceMode != DSITX_IF_MODE_VIDEO)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->videoIfSelect != DSITX_VID_IF_SELECT_IF1) &&
            (obj->videoIfSelect != DSITX_VID_IF_SELECT_IF2) &&
            (obj->videoIfSelect != DSITX_VID_IF_SELECT_IF3)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PhyConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_PhyConfigSF(const DSITX_PhyConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if ((obj->waitBurstTime < (0x1U)) || (obj->waitBurstTime > (0xFU)))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct Video3dConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_Video3dConfigSF(const DSITX_Video3dConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->vidSync3dMode != DSITX_VIDEO_MODE_2D) &&
            (obj->vidSync3dMode != DSITX_VIDEO_MODE_PORTRAIT) &&
            (obj->vidSync3dMode != DSITX_VIDEO_MODE_LANDSCAPE)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->vidSync3dFormat != DSITX_VIDEO_FORMAT_LINE) &&
            (obj->vidSync3dFormat != DSITX_VIDEO_FORMAT_FRAME) &&
            (obj->vidSync3dFormat != DSITX_VIDEO_FORMAT_PIXEL)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->vidVsync3dLr != DSITX_VIDEO_START_LEFT) &&
            (obj->vidVsync3dLr != DSITX_VIDEO_START_RIGHT)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct CommandModeSettings
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_CommandModeSettingsSF(const DSITX_CommandModeSettings *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->vcIdIf1 > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->vcIdIf3 > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->teTimeout > (0x0FFFU))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->arbPriority != DSITX_CMD_ARB_PRIORITY_INIT) &&
            (obj->arbPriority != DSITX_CMD_ARB_PRIORITY_SDI) &&
            (obj->arbPriority != DSITX_CMD_ARB_PRIORITY_DSC)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->arbMode != DSITX_CMD_ARBITRATION_MODE_FIXED) &&
            (obj->arbMode != DSITX_CMD_ARBITRATION_MODE_ROUND_ROBIN)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct VideoSize
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_VideoSizeSF(const DSITX_VideoSize *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if ((obj->vsa < (0x1U)) || (obj->vsa > (0x3FU)))
        {
            ret = CDN_EINVAL;
        }
        if (obj->vbp > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->vfp < (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if ((obj->vact < (0x1U)) || (obj->vact > (0x1FFFU)))
        {
            ret = CDN_EINVAL;
        }
        if (obj->hsa > (0x3FFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->hfp > (0x7FFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->rgb > (0x7FFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->blkEolPacket > (0x7FFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->blkLineEventPacket > (0x7FFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->blkLinePulsePacket > (0x7FFFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct VcaConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_VcaConfigSF(const DSITX_VcaConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct VideoModeSettings
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_VideoModeSettingsSF(const DSITX_VideoModeSettings *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->startMode != DSITX_VID_START_MODE_START_ON_VSYNC)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->stopMode != DSITX_VID_STOP_MODE_STOP_INIT) &&
            (obj->stopMode != DSITX_VID_STOP_MODE_STOP_JUST_BEFORE_VSYNC)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->vidId > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->vidIdSdfd > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->header != DSITX_VID_DATA_TYPE_DEFAULT) &&
            (obj->header != DSITX_VID_DATA_TYPE_YCBCR_20) &&
            (obj->header != DSITX_VID_DATA_TYPE_YCBCR_24) &&
            (obj->header != DSITX_VID_DATA_TYPE_YCBCR_16) &&
            (obj->header != DSITX_VID_DATA_TYPE_RGB_30) &&
            (obj->header != DSITX_VID_DATA_TYPE_RGB_36) &&
            (obj->header != DSITX_VID_DATA_TYPE_YCBCR_12) &&
            (obj->header != DSITX_VID_DATA_TYPE_RGB_16) &&
            (obj->header != DSITX_VID_DATA_TYPE_RGB_18) &&
            (obj->header != DSITX_VID_DATA_TYPE_RGB_18_LOOSELY) &&
            (obj->header != DSITX_VID_DATA_TYPE_RGB_24)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_RGB_16) &&
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_RGB_18) &&
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_RGB_18_LOOSELY) &&
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_RGB_24) &&
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_RGB_30) &&
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_RGB_36) &&
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_YCBCR_12) &&
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_YCBCR_16) &&
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_YCBCR_20) &&
            (obj->vidPixelMode != DSITX_VID_PIXEL_MODE_YCBCR_24)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->blkLineMode != DSITX_VID_BLK_MODE_NULL_PACKET) &&
            (obj->blkLineMode != DSITX_VID_BLK_MODE_BLANKING_PACKET) &&
            (obj->blkLineMode != DSITX_VID_BLK_MODE_LP)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->blkEolMode != DSITX_VID_BLK_MODE_NULL_PACKET) &&
            (obj->blkEolMode != DSITX_VID_BLK_MODE_BLANKING_PACKET) &&
            (obj->blkEolMode != DSITX_VID_BLK_MODE_LP)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->recoveryMode != DSITX_CONTINUE_TILL_NEXT_HSYNC) &&
            (obj->recoveryMode != DSITX_CONTINUE_UNTIL_NEXT_STOP_POINT) &&
            (obj->recoveryMode != DSITX_CONTINUE_TILL_NEXT_VSYNC)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->fieldSwitch > (0x1U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->blkEolDuration > (0x7FFFU))
        {
            ret = CDN_EINVAL;
        }
        if (DSITX_ErrorColorSF(&obj->errColor) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (obj->regWakeupTime > (0x7FFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->regLineDuration > (0x1FFFFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct TestVideoModeConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_TestVideoModeConfigSF(const DSITX_TestVideoModeConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (
            (obj->stripeSize != DSITX_TVG_STRIPE_SIZE_1) &&
            (obj->stripeSize != DSITX_TVG_STRIPE_SIZE_2) &&
            (obj->stripeSize != DSITX_TVG_STRIPE_SIZE_4) &&
            (obj->stripeSize != DSITX_TVG_STRIPE_SIZE_8) &&
            (obj->stripeSize != DSITX_TVG_STRIPE_SIZE_16) &&
            (obj->stripeSize != DSITX_TVG_STRIPE_SIZE_32) &&
            (obj->stripeSize != DSITX_TVG_STRIPE_SIZE_64) &&
            (obj->stripeSize != DSITX_TVG_STRIPE_SIZE_128)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->displayMode != DSITX_TVG_MODE_SINGLE_COLOR) &&
            (obj->displayMode != DSITX_TVG_MODE_VERTICAL_STRIPES) &&
            (obj->displayMode != DSITX_TVG_MODE_HORIZONTAL_STRIPES)
        )
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->stopMode != DSITX_TVG_STOP_MODE_AT_END_OF_FRAME) &&
            (obj->stopMode != DSITX_TVG_STOP_MODE_AT_END_OF_LINE) &&
            (obj->stopMode != DSITX_TVG_STOP_MODE_IMMEDIATE)
        )
        {
            ret = CDN_EINVAL;
        }
        if (obj->linesPerFrame > (0x1FFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->bytesPerLine > (0x7FFFU))
        {
            ret = CDN_EINVAL;
        }
        if (DSITX_ColorSF(&obj->color1) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
        if (DSITX_ColorSF(&obj->color2) == CDN_EINVAL)
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct DsiLinkConfig
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_DsiLinkConfigSF(const DSITX_DsiLinkConfig *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct DirectCommandRequest
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_DirectCommandRequestSF(const DSITX_DirectCommandRequest *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->vcId > (0x3U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->cmdSize > (0x10U))
        {
            ret = CDN_EINVAL;
        }
        if (obj->head > (0x3FU))
        {
            ret = CDN_EINVAL;
        }
        if (
            (obj->type != DSITX_DCR_TYPE_WRITE) &&
            (obj->type != DSITX_DCR_TYPE_READ) &&
            (obj->type != DSITX_DCR_TYPE_TE) &&
            (obj->type != DSITX_DCR_TYPE_TRIGGER) &&
            (obj->type != DSITX_DCR_TYPE_BTA)
        )
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct TestGeneric
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_TestGenericSF(const DSITX_TestGeneric *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * Function to validate struct Config
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_ConfigSF(const DSITX_Config *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if ((obj->numOfLanes < (0x1U)) || (obj->numOfLanes > (0x4U)))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct PrivateData
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_PrivateDataSF(const DSITX_PrivateData *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->numOfLanes > (0x4U))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct Color
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_ColorSF(const DSITX_Color *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->r > (0xFFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->g > (0xFFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->b > (0xFFFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * Function to validate struct ErrorColor
 *
 * @param[in] obj pointer to struct to be verified
 * @returns 0 for valid
 * @returns CDN_EINVAL for invalid
 */
uint32_t DSITX_ErrorColorSF(const DSITX_ErrorColor *obj)
{
    uint32_t ret = 0;

    if (obj == NULL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        if (obj->r > (0xFFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->g > (0xFFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->b > (0xFFFU))
        {
            ret = CDN_EINVAL;
        }
        if (obj->padValue > (0xFFFU))
        {
            ret = CDN_EINVAL;
        }
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] config Proposed driver/hardware configuration.
 * @param[out] sysReq Returns the memory requirements for given configuration in field privDataSize.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction1(const DSITX_Config* config, const DSITX_SysReq* sysReq)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (sysReq == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Specifies driver/hardware configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction2(const DSITX_PrivateData* pD, const DSITX_Config* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_ConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver instance data filled by init.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction3(const DSITX_PrivateData* pD)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure which specifies DPHY configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction7(const DSITX_PrivateData* pD, const DSITX_DphyConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_DphyConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which DPHY configuration will be written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction8(const DSITX_PrivateData* pD, const DSITX_DphyConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing Data Path configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction9(const DSITX_PrivateData* pD, const DSITX_DataPathConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_DataPathConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which Data Path configuration will be written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction10(const DSITX_PrivateData* pD, const DSITX_DataPathConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing PHY configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction11(const DSITX_PrivateData* pD, const DSITX_PhyConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PhyConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which PHY configuration will be written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction12(const DSITX_PrivateData* pD, const DSITX_PhyConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] cfg Pointer to structure containing configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction13(const DSITX_PrivateData* pD, const DSITX_DphyPwrRstConfig* cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_DphyPwrRstConfigSF(cfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] cfg Pointer to structure to which DPHY Power and Reset Control
 *    configuration will be written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction14(const DSITX_PrivateData* pD, const DSITX_DphyPwrRstConfig* cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (cfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing DSITX Link configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction15(const DSITX_PrivateData* pD, const DSITX_DsiLinkConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_DsiLinkConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which DSITX Link setup will be stored.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction16(const DSITX_PrivateData* pD, const DSITX_DsiLinkConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which DSITX IP configuration will be stored.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction17(const DSITX_PrivateData* pD, const DSITX_IpConf* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] id Pointer to structure where DSITX version information will be stored.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction18(const DSITX_PrivateData* pD, const DSITX_HwIdAndVersion* id)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (id == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] cmdMode Pointer to structure containing detailed information about
 *    Command Mode configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction19(const DSITX_PrivateData* pD, const DSITX_CommandModeSettings* cmdMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_CommandModeSettingsSF(cmdMode) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] cmdMode Pointer to structure to which detailed information about
 *    Command Mode configuration will be written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction20(const DSITX_PrivateData* pD, const DSITX_CommandModeSettings* cmdMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (cmdMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] vidMode Pointer to structure containing Video Mode configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction21(const DSITX_PrivateData* pD, const DSITX_VideoModeSettings* vidMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_VideoModeSettingsSF(vidMode) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] vidMode Pointer to structure to which Video Mode configuration will be written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction22(const DSITX_PrivateData* pD, const DSITX_VideoModeSettings* vidMode)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (vidMode == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] vca Pointer to structure containing Video Command Arbiter configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction23(const DSITX_PrivateData* pD, const DSITX_VcaConfig* vca)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_VcaConfigSF(vca) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] vca Pointer to structure to which Video Command Arbiter configuration will be written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction24(const DSITX_PrivateData* pD, const DSITX_VcaConfig* vca)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (vca == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] vidSize Pointer to structure containing Video Size configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction25(const DSITX_PrivateData* pD, const DSITX_VideoSize* vidSize)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_VideoSizeSF(vidSize) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] vidSize Pointer to structure to which Video Size configuration will be written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction26(const DSITX_PrivateData* pD, const DSITX_VideoSize* vidSize)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (vidSize == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing Test Video Generator configuration.
 *    Value of the enabled field is ignored. Use startTvg function to enable TVG.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction27(const DSITX_PrivateData* pD, const DSITX_TestVideoModeConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_TestVideoModeConfigSF(config) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which received Test Video Generator
 *    configuration will be written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction28(const DSITX_PrivateData* pD, const DSITX_TestVideoModeConfig* config)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (config == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] dcr Pointer to structure containing detailed information about command.
 *    This structure will be updated by Core Driver during command
 *    execution. After passing it to Core Driver user shall not make
 *    any changes to its content until dcr status is set to completed
 *    or it is presented in callback function.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction31(const DSITX_PrivateData* pD, const DSITX_DirectCommandRequest* dcr)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_DirectCommandRequestSF(dcr) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] test Pointer to structure containing control configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction38(const DSITX_PrivateData* pD, const DSITX_TestGeneric* test)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_TestGenericSF(test) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] test Pointer to structure to which control configuration will be
 *    written.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction39(const DSITX_PrivateData* pD, const DSITX_TestGeneric* test)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (test == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] cfg Video 3D configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction40(const DSITX_PrivateData* pD, const DSITX_Video3dConfig* cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_Video3dConfigSF(cfg) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] cfg Video 3D configuration.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction41(const DSITX_PrivateData* pD, const DSITX_Video3dConfig* cfg)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (cfg == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}


/**
 * A common function to check the validity of API functions with
 * following parameter types
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] asfInfo Pointer to ASF information structure.
 * @return 0 success
 * @return CDN_EINVAL invalid parameters
 */
uint32_t DSITX_SanityFunction42(const DSITX_PrivateData* pD, const DSITX_AsfInfo* asfInfo)
{
    /* Declaring return variable */
    uint32_t ret = 0;

    if (asfInfo == NULL)
    {
        ret = CDN_EINVAL;
    }
    else if (DSITX_PrivateDataSF(pD) == CDN_EINVAL)
    {
        ret = CDN_EINVAL;
    }
    else
    {
        /*
         * All 'if ... else if' constructs shall be terminated with an 'else' statement
         * (MISRA2012-RULE-15_7-3)
         */
    }

    return ret;
}

/* parasoft-end-suppress MISRA2012-RULE-8_7 */
/* parasoft-end-suppress METRICS-41-3 */
/* parasoft-end-suppress METRICS-39-3 */
/* parasoft-end-suppress METRICS-36-3 */
/* parasoft-end-suppress METRICS-18-3 */

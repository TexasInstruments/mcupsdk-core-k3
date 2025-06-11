/******************************************************************************
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
 *
 * This file contains DSITX Core Driver API implementation.
 *
 *****************************************************************************/

#include <drivers/dss/v1/hw_include/dsi/csl_dsi.h>

#include <drivers/dss/v1/hw_include/dsi/include/dsitx_priv.h>
#include "dsitx_sanity.h"
#include "dsitx_utils.h"
#include "dsitx_cfg.h"

#define REG_POOL_TIMEOUT 10000
#define DIRECT_CMD_TIMEOUT 10000

// parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions"

/**
 * Returns 1U or 0U depending on a received flag in the type of bool.
 */
static inline uint32_t boolToVal(bool state)
{
    return ((state == true) ? 1U : 0U);
}

/**
 * Returns true or false depending on a received uint32_t value.
 */
static inline bool valToBool(uint32_t value)
{
    return ((value != 0U) ? (bool)true : (bool)false);
}

#ifndef min
/**
 * Returns the lower value of two variables.
 */
static inline uint32_t min(uint32_t A, uint32_t B)
{
    return (((A) < (B)) ? (A) : (B));
}
#endif

/* Structures with dsitx regs macros needed for iteration during access to fields
grouped into arrays inside driver structures */
static const struct {
    uint32_t datLaneEnabled_mask;
    uint32_t datLaneEnabled_shift;
    uint32_t datLaneInUlpMode_mask;
    uint32_t datLaneInUlpMode_shift;
} dsiLinkConfig_defs[DSITX_MAX_LANE_NUMBER] = {
    [0U].datLaneEnabled_mask = DSITX__MCTL_MAIN_EN__DAT1_EN_MASK,
    [0U].datLaneEnabled_shift = DSITX__MCTL_MAIN_EN__DAT1_EN_SHIFT,
    [0U].datLaneInUlpMode_mask = DSITX__MCTL_MAIN_EN__DAT1_ULPM_REQ_MASK,
    [0U].datLaneInUlpMode_shift = DSITX__MCTL_MAIN_EN__DAT1_ULPM_REQ_SHIFT,

    [1U].datLaneEnabled_mask = DSITX__MCTL_MAIN_EN__DAT2_EN_MASK,
    [1U].datLaneEnabled_shift = DSITX__MCTL_MAIN_EN__DAT2_EN_SHIFT,
    [1U].datLaneInUlpMode_mask = DSITX__MCTL_MAIN_EN__DAT2_ULPM_REQ_MASK,
    [1U].datLaneInUlpMode_shift = DSITX__MCTL_MAIN_EN__DAT2_ULPM_REQ_SHIFT,

    [2U].datLaneEnabled_mask = DSITX__MCTL_MAIN_EN__DAT3_EN_MASK,
    [2U].datLaneEnabled_shift = DSITX__MCTL_MAIN_EN__DAT3_EN_SHIFT,
    [2U].datLaneInUlpMode_mask = DSITX__MCTL_MAIN_EN__DAT3_ULPM_REQ_MASK,
    [2U].datLaneInUlpMode_shift = DSITX__MCTL_MAIN_EN__DAT3_ULPM_REQ_SHIFT,

    [3U].datLaneEnabled_mask = DSITX__MCTL_MAIN_EN__DAT4_EN_MASK,
    [3U].datLaneEnabled_shift = DSITX__MCTL_MAIN_EN__DAT4_EN_SHIFT,
    [3U].datLaneInUlpMode_mask = DSITX__MCTL_MAIN_EN__DAT4_ULPM_REQ_MASK,
    [3U].datLaneInUlpMode_shift = DSITX__MCTL_MAIN_EN__DAT4_ULPM_REQ_SHIFT,
};

static const struct {
    uint32_t laneUlpMode_mask;
    uint32_t laneUlpMode_shift;
} phyConfig_defs[DSITX_MAX_LANE_NUMBER] = {
    [0U].laneUlpMode_mask = DSITX__MCTL_MAIN_PHY_CTL__DAT1_ULPM_EN_MASK,
    [0U].laneUlpMode_shift = DSITX__MCTL_MAIN_PHY_CTL__DAT1_ULPM_EN_SHIFT,

    [1U].laneUlpMode_mask = DSITX__MCTL_MAIN_PHY_CTL__DAT2_ULPM_EN_MASK,
    [1U].laneUlpMode_shift = DSITX__MCTL_MAIN_PHY_CTL__DAT2_ULPM_EN_SHIFT,

    [2U].laneUlpMode_mask = DSITX__MCTL_MAIN_PHY_CTL__DAT3_ULPM_EN_MASK,
    [2U].laneUlpMode_shift = DSITX__MCTL_MAIN_PHY_CTL__DAT3_ULPM_EN_SHIFT,

    [3U].laneUlpMode_mask = DSITX__MCTL_MAIN_PHY_CTL__DAT4_ULPM_EN_MASK,
    [3U].laneUlpMode_shift = DSITX__MCTL_MAIN_PHY_CTL__DAT4_ULPM_EN_SHIFT,
};

/* internal function */
static uint32_t getTvgStripeSizeEnum(const uint32_t val, DSITX_TvgStripeSize *enumVal)
{
    #define TVG_STRIP_SIZE_ENUMS_CNT 8U

    uint32_t i;
    uint32_t status = CDN_EINVAL;

    const DSITX_TvgStripeSize tvgStripeSizeEnums[TVG_STRIP_SIZE_ENUMS_CNT] = {
        [0U] = DSITX_TVG_STRIPE_SIZE_1,
        [1U] = DSITX_TVG_STRIPE_SIZE_2,
        [2U] = DSITX_TVG_STRIPE_SIZE_4,
        [3U] = DSITX_TVG_STRIPE_SIZE_8,
        [4U] = DSITX_TVG_STRIPE_SIZE_16,
        [5U] = DSITX_TVG_STRIPE_SIZE_32,
        [6U] = DSITX_TVG_STRIPE_SIZE_64,
        [7U] = DSITX_TVG_STRIPE_SIZE_128,
    };

    /* converts uint32_t to enum */
    for (i = 0U; i < TVG_STRIP_SIZE_ENUMS_CNT; ++i) {
        if ((uint32_t)tvgStripeSizeEnums[i] == val) {
            *enumVal = tvgStripeSizeEnums[i];
            status = CDN_EOK;
            break;
        }
    }

    return status;
}

/* internal function */
static uint32_t getHeaderEnum(const uint32_t val, DSITX_VideoDataType *enumVal)
{
    #define HEADER_ENUMS_CNT 11U

    uint32_t i;
    uint32_t status = CDN_EINVAL;

    const DSITX_VideoDataType headerEnums[HEADER_ENUMS_CNT] = {
        [0U] = DSITX_VID_DATA_TYPE_DEFAULT,
        [1U] = DSITX_VID_DATA_TYPE_YCBCR_20,
        [2U] = DSITX_VID_DATA_TYPE_YCBCR_24,
        [3U] = DSITX_VID_DATA_TYPE_YCBCR_16,
        [4U] = DSITX_VID_DATA_TYPE_RGB_30,
        [5U] = DSITX_VID_DATA_TYPE_RGB_36,
        [6U] = DSITX_VID_DATA_TYPE_YCBCR_12,
        [7U] = DSITX_VID_DATA_TYPE_RGB_16,
        [8U] = DSITX_VID_DATA_TYPE_RGB_18,
        [9U] = DSITX_VID_DATA_TYPE_RGB_18_LOOSELY,
        [10U] = DSITX_VID_DATA_TYPE_RGB_24,
    };

    /* converts uint32_t to enum */
    for (i = 0U; i < HEADER_ENUMS_CNT; ++i) {
        if ((uint32_t)headerEnums[i] == val) {
            *enumVal = headerEnums[i];
            status = CDN_EOK;
            break;
        }
    }

    return status;
}

/* internal function */
static uint32_t getVidSync3dModeEnum(const uint32_t val, DSITX_Video3dMode *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_VIDEO_MODE_2D == val) {
        *enumVal = DSITX_VIDEO_MODE_2D;
    } else if ((uint32_t)DSITX_VIDEO_MODE_PORTRAIT == val) {
        *enumVal = DSITX_VIDEO_MODE_PORTRAIT;
    } else if ((uint32_t)DSITX_VIDEO_MODE_LANDSCAPE == val) {
        *enumVal = DSITX_VIDEO_MODE_LANDSCAPE;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getVidSync3dFormatEnum(const uint32_t val, DSITX_Video3dFormat *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_VIDEO_FORMAT_LINE == val) {
        *enumVal = DSITX_VIDEO_FORMAT_LINE;
    } else if ((uint32_t)DSITX_VIDEO_FORMAT_FRAME == val) {
        *enumVal = DSITX_VIDEO_FORMAT_FRAME;
    } else if ((uint32_t)DSITX_VIDEO_FORMAT_PIXEL == val) {
        *enumVal = DSITX_VIDEO_FORMAT_PIXEL;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getVideoIfSelectEnum(const uint32_t val, DSITX_VideoInterfaceSelection *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_VID_IF_SELECT_IF1 == val) {
        *enumVal = DSITX_VID_IF_SELECT_IF1;
    } else if ((uint32_t)DSITX_VID_IF_SELECT_IF2 == val) {
        *enumVal = DSITX_VID_IF_SELECT_IF2;
    } else if ((uint32_t)DSITX_VID_IF_SELECT_IF3 == val) {
        *enumVal = DSITX_VID_IF_SELECT_IF3;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getVidVsync3dLrEnum(const uint32_t val, DSITX_Video3dFirstSide *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_VIDEO_START_LEFT == val) {
        *enumVal = DSITX_VIDEO_START_LEFT;
    }
    else if ((uint32_t)DSITX_VIDEO_START_RIGHT == val) {
        *enumVal = DSITX_VIDEO_START_RIGHT;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getInterfaceModeEnum(const uint32_t val, DSITX_InterfaceMode *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_IF_MODE_COMMAND == val) {
        *enumVal = DSITX_IF_MODE_COMMAND;
    }
    else if ((uint32_t)DSITX_IF_MODE_VIDEO == val) {
        *enumVal = DSITX_IF_MODE_VIDEO;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getCmdArbitrationPriorityEnum(const uint32_t val, DSITX_CmdArbitrationPriority *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_CMD_ARB_PRIORITY_INIT == val) {
        *enumVal = DSITX_CMD_ARB_PRIORITY_INIT;
    } else if ((uint32_t)DSITX_CMD_ARB_PRIORITY_SDI == val) {
        *enumVal = DSITX_CMD_ARB_PRIORITY_SDI;
    } else if ((uint32_t)DSITX_CMD_ARB_PRIORITY_DSC == val) {
        *enumVal = DSITX_CMD_ARB_PRIORITY_DSC;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getCommandArbitrationModeEnum(const uint32_t val, DSITX_CmdArbitrationMode *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_CMD_ARBITRATION_MODE_FIXED == val) {
        *enumVal = DSITX_CMD_ARBITRATION_MODE_FIXED;
    }
    else if ((uint32_t)DSITX_CMD_ARBITRATION_MODE_ROUND_ROBIN == val) {
        *enumVal = DSITX_CMD_ARBITRATION_MODE_ROUND_ROBIN;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getTvgStopModeEnum(const uint32_t val, DSITX_TvgStopMode *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_TVG_STOP_MODE_AT_END_OF_FRAME == val) {
        *enumVal = DSITX_TVG_STOP_MODE_AT_END_OF_FRAME;
    }
    else if ((uint32_t)DSITX_TVG_STOP_MODE_AT_END_OF_LINE == val) {
        *enumVal = DSITX_TVG_STOP_MODE_AT_END_OF_LINE;
    }
    else if ((uint32_t)DSITX_TVG_STOP_MODE_IMMEDIATE == val) {
        *enumVal = DSITX_TVG_STOP_MODE_IMMEDIATE;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getVideoBlankingModeEnum(const uint32_t val, DSITX_VideoBlankingMode *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_VID_BLK_MODE_NULL_PACKET == val) {
        *enumVal = DSITX_VID_BLK_MODE_NULL_PACKET;
    }
    else if ((uint32_t)DSITX_VID_BLK_MODE_BLANKING_PACKET == val) {
        *enumVal = DSITX_VID_BLK_MODE_BLANKING_PACKET;
    }
    else if ((uint32_t)DSITX_VID_BLK_MODE_LP == val) {
        *enumVal = DSITX_VID_BLK_MODE_LP;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t  getVideoStartModeEnum(const uint32_t val, DSITX_VideoStartMode *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_VID_START_MODE_START_ON_VSYNC == val) {
        *enumVal = DSITX_VID_START_MODE_START_ON_VSYNC;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getVideoStopModeEnum(const uint32_t val, DSITX_VideoStopMode *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_VID_STOP_MODE_STOP_JUST_BEFORE_VSYNC == val) {
        *enumVal = DSITX_VID_STOP_MODE_STOP_JUST_BEFORE_VSYNC;
    } else if ((uint32_t)DSITX_VID_STOP_MODE_STOP_INIT == val) {
        *enumVal = DSITX_VID_STOP_MODE_STOP_INIT;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getVideoPixelModeEnum(const uint32_t val, DSITX_VideoPixelMode *enumVal)
{
    #define VID_STOP_PIXEL_MODE_ENUMS_CNT 10U

    uint32_t status = CDN_EINVAL;
    uint32_t i;

    const DSITX_VideoPixelMode videoPixelModeEnums[VID_STOP_PIXEL_MODE_ENUMS_CNT] = {
        [0U] = DSITX_VID_PIXEL_MODE_RGB_16,
        [1U] = DSITX_VID_PIXEL_MODE_RGB_18,
        [2U] = DSITX_VID_PIXEL_MODE_RGB_18_LOOSELY,
        [3U] = DSITX_VID_PIXEL_MODE_RGB_24,
        [4U] = DSITX_VID_PIXEL_MODE_RGB_30,
        [5U] = DSITX_VID_PIXEL_MODE_RGB_36,
        [6U] = DSITX_VID_PIXEL_MODE_YCBCR_12,
        [7U] = DSITX_VID_PIXEL_MODE_YCBCR_16,
        [8U] = DSITX_VID_PIXEL_MODE_YCBCR_20,
        [9U] = DSITX_VID_PIXEL_MODE_YCBCR_24,
    };

    /* converts uint32_t to enum */
    for (i = 0U; i < VID_STOP_PIXEL_MODE_ENUMS_CNT; ++i) {
        if ((uint32_t)videoPixelModeEnums[i] == val) {
            *enumVal = videoPixelModeEnums[i];
            status = CDN_EOK;
            break;
        }
    }

    return status;
}

/* internal function */
static uint32_t getVideoRecoveryModeEnum(const uint32_t val, DSITX_VideoRecoveryMode *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_CONTINUE_TILL_NEXT_HSYNC == val) {
        *enumVal = DSITX_CONTINUE_TILL_NEXT_HSYNC;
    }
    else if ((uint32_t)DSITX_CONTINUE_UNTIL_NEXT_STOP_POINT == val) {
        *enumVal = DSITX_CONTINUE_UNTIL_NEXT_STOP_POINT;
    }
    else if ((uint32_t)DSITX_CONTINUE_TILL_NEXT_VSYNC == val) {
        *enumVal = DSITX_CONTINUE_TILL_NEXT_VSYNC;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}

/* internal function */
static uint32_t getTvgDisplayModeEnum(const uint32_t val, DSITX_TvgDisplayMode *enumVal)
{
    uint32_t status = CDN_EOK;

    /* converts uint32_t to enum */
    if ((uint32_t)DSITX_TVG_MODE_SINGLE_COLOR == val) {
        *enumVal = DSITX_TVG_MODE_SINGLE_COLOR;
    }
    else if ((uint32_t)DSITX_TVG_MODE_VERTICAL_STRIPES == val) {
        *enumVal = DSITX_TVG_MODE_VERTICAL_STRIPES;
    }
    else if ((uint32_t)DSITX_TVG_MODE_HORIZONTAL_STRIPES == val) {
        *enumVal = DSITX_TVG_MODE_HORIZONTAL_STRIPES;
    } else {
        status = CDN_EINVAL;
    }

    return status;
}
/**
*   END OF THE CONVERSION FUNCTION BLOCK
*/

/* internal function */
static uint32_t readDCRData(DSITX_PrivateData *pD, DSITX_DirectCommandRequest *dcr)
{
    uint32_t regVal;
    uint8_t *ptr;
    uint8_t index = 0U;
    uint32_t size;
    uint32_t status = CDN_EOK;

    if (dcr->recData == NULL) {
        status = CDN_EINVAL;
    } else {
        /* read register */
        regVal = CPS_REG_READ(&pD->regBase->direct_cmd_rd_property);

        /* get DCR info */
        dcr->dcsPk = valToBool(CPS_FLD_READ(DSITX__DIRECT_CMD_RD_PROPERTY, RD_DCSNOTGENERIC, regVal));
        dcr->vcId  = (uint8_t)CPS_FLD_READ(DSITX__DIRECT_CMD_RD_PROPERTY, RD_ID, regVal);
        dcr->recDataSize = (uint16_t)CPS_FLD_READ(DSITX__DIRECT_CMD_RD_PROPERTY, RD_SIZE, regVal);

        dcr->rdStatus = CPS_REG_READ(&pD->regBase->direct_cmd_rd_sts);

        size = dcr->recDataSize;
        ptr = dcr->recData;

        /* read data and store in buffer */
        while (size != 0U) {
            regVal = CPS_REG_READ(&pD->regBase->direct_cmd_rddat);
            WriteToBuff32le(&ptr[index], size, regVal);

            index += 4U;
            size -= min(size, 4U);
        }
    }
    return status;
}

/**
 * Reads information about DSITX version.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] id Pointer to structure where DSITX version information will be stored.
 * @return CDN_EINVAL If pD or id is NULL.
 * @return CDN_EOK If information is successfully obtained.
 */
uint32_t DSITX_GetHwIdAndVersion(DSITX_PrivateData* pD, DSITX_HwIdAndVersion* id)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_GetHwIdAndVersionSF(pD, id) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register */
        regVal = CPS_REG_READ(&pD->regBase->id_reg);
        /* extract version information */
        id->vendorId = (uint16_t)CPS_FLD_READ(DSITX__ID_REG, REV_VENDOR_ID, regVal);
        id->productId = (uint8_t)CPS_FLD_READ(DSITX__ID_REG, REV_PRODUCT_ID, regVal);
        id->revisionNumber = (uint8_t)CPS_FLD_READ(DSITX__ID_REG, REV_HARDWARE, regVal);
        id->majorRevision = (uint8_t)CPS_FLD_READ(DSITX__ID_REG, REV_X, regVal);
        id->minorRevision = (uint8_t)CPS_FLD_READ(DSITX__ID_REG, REV_Y, regVal);

        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static void getIpConfSizes(DSITX_IpConf* config, uint32_t regVal)
{
    /* 0 - 32-bit, 1 - 16-bit, 3 - 8-bit */
    if (CPS_FLD_READ(DSITX__IP_CONF, DATAPATH_SIZE, regVal) < 0x4U) {
        config->datapathSize = (uint8_t)((uint8_t)32 >> CPS_FLD_READ(DSITX__IP_CONF, DATAPATH_SIZE, regVal));
    } else {
        config->datapathSize = 8;
    }

    /* 0 - 16-bit, 1 - 32-bit */
    if (CPS_FLD_READ(DSITX__IP_CONF, INTERFACE_DATASIZE, regVal) < 0x4U) {
        config->sdiIfDataBusSize = (uint8_t)((uint8_t)16 << (CPS_FLD_READ(DSITX__IP_CONF, INTERFACE_DATASIZE, regVal)));
    }
}

/* internal function */
static void getIpConfDepths(DSITX_IpConf* config, uint32_t regVal)
{
    /* Depths are 2^regval */
    if ((CPS_FLD_READ(DSITX__IP_CONF, VRS_FIFO_DEPTH, regVal)) < (0x8U)) {
        config->vrsBlockFifoDepth = (uint8_t)((uint8_t)1 << CPS_FLD_READ(DSITX__IP_CONF, VRS_FIFO_DEPTH, regVal));
    }

    if(CPS_FLD_READ(DSITX__IP_CONF, SP_LP_FIFO_DEPTH, regVal) < 0x8U) {
        config->lpFifoDepth = (uint8_t)((uint8_t)1 << (CPS_FLD_READ(DSITX__IP_CONF, SP_LP_FIFO_DEPTH, regVal)));
    }
    if(CPS_FLD_READ(DSITX__IP_CONF, SP_HS_FIFO_DEPTH, regVal) < 0x8U) {
        config->hsFifoDepth = (uint8_t)((uint8_t)1 << CPS_FLD_READ(DSITX__IP_CONF, SP_HS_FIFO_DEPTH, regVal));
    }
}

/**
 * Obtains IP configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which DSITX IP configuration will be stored.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetIpConf(DSITX_PrivateData* pD, DSITX_IpConf* config)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_GetIpConfSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register */
        regVal = CPS_REG_READ(&pD->regBase->ip_conf);

        getIpConfSizes(config, regVal);

        config->rxFifoDepth = (uint8_t)CPS_FLD_READ(DSITX__IP_CONF, RX_FIFO_DEPTH, regVal);
        /* num = regval+1 */
        config->maxLaneNumber = (uint8_t)(CPS_FLD_READ(DSITX__IP_CONF, MAX_LANE_NB, regVal) + 1U);
        config->sdiIfNumber = (uint8_t)(CPS_FLD_READ(DSITX__IP_CONF, NUM_INTERFACE, regVal) + 1U);

        /* Direct Command FIFO size = 2^(regval+2) */
        if ((CPS_FLD_READ(DSITX__IP_CONF, DIRCMD_FIFO_DEPTH, regVal) + 2U) < 0xFU) {
            config->directCmdFifoDepth = (uint16_t)((uint16_t)1 << (CPS_FLD_READ(DSITX__IP_CONF, DIRCMD_FIFO_DEPTH, regVal) + 2U));
        }
        getIpConfDepths(config, regVal);
        status = CDN_EOK;
    }
    return status;
}

/**
 * Obtains DSITX Link configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which DSITX Link setup will be stored.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetDsiLinkConfig(DSITX_PrivateData* pD, DSITX_DsiLinkConfig* config)
{
    uint32_t status;
    uint32_t regVal;
    uint32_t i;

    /* check params */
    if (DSITX_GetDsiLinkConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register */
        regVal = CPS_REG_READ(&pD->regBase->mctl_main_en);
        /* get PLL/CLK status */
        config->pllEnabled =  valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_EN, PLL_START, regVal));
        config->clkLaneEnabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_EN, CKLANE_EN, regVal));

        /* get lane status */
        for (i = 0U; i < ((uint32_t)DSITX_MAX_LANE_NUMBER); ++i) {
            config->datLaneEnabled[i] = valToBool(CPS_FldRead(dsiLinkConfig_defs[i].datLaneEnabled_mask, dsiLinkConfig_defs[i].datLaneEnabled_shift, regVal));
        }

        config->clkLaneInUlpMode = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_EN, CLKLANE_ULPM_REQ, regVal));

        for (i = 0U; i < ((uint32_t)DSITX_MAX_LANE_NUMBER); ++i) {
            config->datLaneInUlpMode[i] = valToBool(CPS_FldRead(dsiLinkConfig_defs[i].datLaneInUlpMode_mask, dsiLinkConfig_defs[i].datLaneInUlpMode_shift, regVal));
        }

        config->if1Enabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_EN, IF1_EN, regVal));
        config->if2Enabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_EN, IF2_EN, regVal));
        config->if3Enabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_EN, IF3_EN, regVal));

        config->clkForceStop = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_EN, CLK_FORCE_STOP, regVal));
        config->forceStopMode = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_EN, FORCE_STOP_MODE, regVal));

        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static uint32_t checkMagicNumber(const DSITX_Config *config) {
    uint32_t ret = CDN_EOK;
    uint32_t volatile *id_reg_addr = &((DSITX_Regs volatile*)config->regBase)->id_reg;
    uint32_t idRegValue = CPS_REG_READ(id_reg_addr);
    uint32_t vendor_id = CPS_FLD_READ(DSITX__ID_REG, REV_VENDOR_ID, idRegValue);
    uint32_t product_id = CPS_FLD_READ(DSITX__ID_REG, REV_PRODUCT_ID, idRegValue);
    uint32_t magicNumber = (vendor_id << DSITX__ID_REG__REV_PRODUCT_ID_WIDTH) | product_id;
    if (magicNumber != DSITX_MAGIC_NUMBER) {
        ret = CDN_EINVAL;
    }
    return ret;
}

/**
 * Obtains the driver's memory requirements to support the given
 * configuration.
 * @param[in] config Proposed driver/hardware configuration.
 * @param[out] sysReq Returns the memory requirements for given configuration in field privDataSize.
 * @return CDN_EOK On success (requirements struct filled).
 * @return CDN_EINVAL If config contains invalid values or not supported configuration.
 */
uint32_t DSITX_Probe(const DSITX_Config* config, DSITX_SysReq* sysReq)
{
    uint32_t maxLanes;
    uint32_t result;

    /* check params */
    if ((DSITX_ProbeSF(config, sysReq) != CDN_EOK) || (checkMagicNumber(config) != CDN_EOK)) {
        result = CDN_EINVAL;
    } else {
        uint32_t volatile *ip_conf_addr = &((DSITX_Regs volatile*)config->regBase)->ip_conf;

        /* check lanes info */
        maxLanes = CPS_FLD_READ(DSITX__IP_CONF, MAX_LANE_NB, CPS_REG_READ(ip_conf_addr)) + 1U;
        if (maxLanes < (uint32_t)config->numOfLanes) {
            result = CDN_EINVAL;
        } else {
            sysReq->privDataSize = (uint32_t)(sizeof(DSITX_PrivateData));
            result = CDN_EOK;
        }
    }
    return result;
}

/* internal function */
static uint32_t setDsiLinkConfigDataLanes(const DSITX_DsiLinkConfig* config, uint32_t regValue)
{
    uint32_t i;
    uint32_t regVal = regValue;

    /* convert array to register value */
    for (i = 0U; i < ((uint32_t)DSITX_MAX_LANE_NUMBER); ++i) {
        regVal = CPS_FldWrite(dsiLinkConfig_defs[i].datLaneEnabled_mask, dsiLinkConfig_defs[i].datLaneEnabled_shift, regVal, boolToVal(config->datLaneEnabled[i]));
    }

    for (i = 0U; i < ((uint32_t)DSITX_MAX_LANE_NUMBER); ++i) {
        regVal = CPS_FldWrite(dsiLinkConfig_defs[i].datLaneInUlpMode_mask, dsiLinkConfig_defs[i].datLaneInUlpMode_shift, regVal, boolToVal(config->datLaneInUlpMode[i]));
    }

    return regVal;
}

/**
 * Sets DSITX Link configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing DSITX Link configuration.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If configuration is successfully set.
 */
uint32_t DSITX_SetDsiLinkConfig(DSITX_PrivateData* pD, const DSITX_DsiLinkConfig* config)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_SetDsiLinkConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = 0U;
        regVal = setDsiLinkConfigDataLanes(config, regVal);

        /* build register value */
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_EN, PLL_START, regVal, boolToVal(config->pllEnabled));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_EN, CKLANE_EN, regVal, boolToVal(config->clkLaneEnabled));

        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_EN, CLKLANE_ULPM_REQ, regVal, boolToVal(config->clkLaneInUlpMode));

        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_EN, IF1_EN, regVal, boolToVal(config->if1Enabled));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_EN, IF2_EN, regVal, boolToVal(config->if2Enabled));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_EN, IF3_EN, regVal, boolToVal(config->if3Enabled));

        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_EN, CLK_FORCE_STOP, regVal, boolToVal(config->clkForceStop));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_EN, FORCE_STOP_MODE,regVal, boolToVal(config->forceStopMode));

        /* write to register */
        CPS_REG_WRITE(&pD->regBase->mctl_main_en, regVal);

        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static uint32_t setDataPathConfigDisp(const DSITX_DataPathConfig* config, uint32_t regValue)
{
    uint32_t regVal = regValue;

    /* set display fields */
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, DISP_GEN_ECC, regVal, boolToVal(config->dispGenEcc));
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, DISP_GEN_CHECKSUM, regVal, boolToVal(config->dispGenChecksum));
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, DISP_EOT_GEN, regVal, boolToVal(config->dispEotGen));

    return (regVal);
}

/* internal function */
static uint32_t setDataPathConfigTe(const DSITX_DataPathConfig* config, uint32_t regValue)
{
    uint32_t regVal = regValue;

    /* set tie fields */
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, IF1_TE_EN, regVal, boolToVal(config->if1TeEnabled));
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, REG_TE_EN, regVal, boolToVal(config->regTeEnabled));
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, TE_HW_POLLING_EN, regVal, boolToVal(config->teHwPolling));
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, TE_MIPI_POLLING_EN, regVal, boolToVal(config->teMipiPolling));

    return (regVal);
}

/* internal function */
static uint32_t setDataPathConfigVid(const DSITX_DataPathConfig* config, uint32_t regValue)
{
    uint32_t regVal = regValue;

    /* set vid/tvg fields */
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, SDI_IF_VID_MODE, regVal, config->interfaceMode);
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, VID_IF_SELECT, regVal, config->videoIfSelect);
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, VID_EN, regVal, boolToVal(config->videoStreamGenEnabled));
    regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, TVG_SEL, regVal, boolToVal(config->tvgEnabled));

    return (regVal);
}

/* internal function */
static uint32_t setDataPathConfigMod(const DSITX_DataPathConfig* config, uint32_t regValue)
{
    uint32_t regVal = regValue;
    const DSITX_DataPathConfig* cfg = config;

    regVal = setDataPathConfigVid(cfg, regVal);
    regVal = setDataPathConfigTe(cfg, regVal);
    regVal = setDataPathConfigDisp(cfg, regVal);

    return (regVal);
}

/**
 * Sets Data Path configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing Data Path configuration.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If configuration is successfully set.
 */
uint32_t DSITX_SetDataPathConfig(DSITX_PrivateData* pD, const DSITX_DataPathConfig* config)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_SetDataPathConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        status = CDN_EOK;
    }

    if (status == CDN_EOK) {
        /* read register */
        regVal = CPS_REG_READ(&pD->regBase->mctl_main_data_ctl);
        /* call helper function */
        regVal = setDataPathConfigMod(config, regVal);
        /* add more fields */
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, HOST_EOT_GEN, regVal, boolToVal(config->hostEotGen));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, LINK_EN, regVal, boolToVal(config->linkEnabled));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, READ_EN, regVal, boolToVal(config->readOpEnabled));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_DATA_CTL, BTA_EN, regVal, boolToVal(config->btaEnabled));
        /* write to register */
        CPS_REG_WRITE(&pD->regBase->mctl_main_data_ctl, regVal);
    }
    return status;
}

/**
 * Sets PHY main configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing PHY configuration.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If configuration is successfully set.
 */
uint32_t DSITX_SetPhyConfig(DSITX_PrivateData* pD, const DSITX_PhyConfig* config)
{
    uint32_t regVal;
    uint32_t status;
    uint32_t i;

    /* check params */
    if (DSITX_SetPhyConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        regVal = 0;

        /* build register value */
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_PHY_CTL, LANE2_EN, regVal, boolToVal(config->lane2Enabled));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_PHY_CTL, LANE3_EN, regVal, boolToVal(config->lane3Enabled));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_PHY_CTL, LANE4_EN, regVal, boolToVal(config->lane4Enabled));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_PHY_CTL, CLK_CONTINUOUS, regVal, boolToVal(config->laneClkContinous));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_PHY_CTL, CLK_ULPM_EN, regVal, boolToVal(config->laneClkUlpMode));

        /* set fields accordingly to array value */
        for (i = 0U; i < ((uint32_t)DSITX_MAX_LANE_NUMBER); ++i) {
            regVal = CPS_FldWrite(phyConfig_defs[i].laneUlpMode_mask, phyConfig_defs[i].laneUlpMode_shift, regVal, boolToVal(config->laneUlpMode[i]));
        }

        regVal = CPS_FLD_WRITE(DSITX__MCTL_MAIN_PHY_CTL, WAIT_BURST_TIME, regVal, config->waitBurstTime);

        /* write to register */
        CPS_REG_WRITE(&pD->regBase->mctl_main_phy_ctl, regVal);

        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static uint32_t setDphyPwrAndRstCtrlPdn(DSITX_DphyPwrRstConfig const *cfg, uint32_t regValue)
{
    uint32_t regVal = regValue;

    /* build register value */
    regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_CFG0, DPHY_PLL_PDN, regVal, boolToVal(cfg->dphyPllPdn));
    regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_CFG0, DPHY_CMN_PDN, regVal, boolToVal(cfg->dphyCmnPdn));
    regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_CFG0, DPHY_C_PDN, regVal, boolToVal(cfg->dphyCPdn));
    regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_CFG0, DPHY_D_PDN, regVal, cfg->dphyDPdn);

    return regVal;
}

/**
 * Sets the DPHY Power and Reset Control configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] cfg Pointer to structure containing configuration.
 * @return CDN_EINVAL If pD or cfg is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_SetDphyPwrAndRstCtrl(DSITX_PrivateData *pD, DSITX_DphyPwrRstConfig const *cfg)
{
    uint32_t status = CDN_EOK;

    /* check params */
    if (DSITX_SetDphyPwrAndRstCtrlSF(pD, cfg) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* build register value */
        uint32_t regVal = 0;
        regVal = setDphyPwrAndRstCtrlPdn(cfg, regVal);
        regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_CFG0, DPHY_C_RSTB, regVal, boolToVal(cfg->dphyCRstb));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_CFG0, DPHY_D_RSTB, regVal, cfg->dphyDRstb);
        regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_CFG0, DPHY_PLL_PSO, regVal, boolToVal(cfg->dphyPllPso));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_CFG0, DPHY_CMN_PSO, regVal, boolToVal(cfg->dphyCmnPso));
        /* write to register */
        CPS_REG_WRITE(&pD->regBase->mctl_dphy_cfg0, regVal);
    }
    return status;
}

/**
 * Obtains the DPHY Power and Reset Control configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] cfg Pointer to structure to which DPHY Power and Reset Control
 *    configuration will be written.
 * @return CDN_EINVAL If pD or cfg is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_GetDphyPwrAndRstCtrl(DSITX_PrivateData *pD, DSITX_DphyPwrRstConfig *cfg)
{

    uint32_t status = CDN_EOK;

    /* check params */
    if (DSITX_GetDphyPwrAndRstCtrlSF(pD, cfg) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register */
        uint32_t regVal = CPS_REG_READ(&pD->regBase->mctl_dphy_cfg0);
        /* extract fields */
        cfg->dphyCRstb = valToBool(CPS_FLD_READ(DSITX__MCTL_DPHY_CFG0, DPHY_C_RSTB, regVal));
        cfg->dphyDRstb = (uint8_t) CPS_FLD_READ(DSITX__MCTL_DPHY_CFG0, DPHY_D_RSTB, regVal);
        cfg->dphyPllPdn = valToBool(CPS_FLD_READ(DSITX__MCTL_DPHY_CFG0, DPHY_PLL_PDN, regVal));
        cfg->dphyCmnPdn = valToBool(CPS_FLD_READ(DSITX__MCTL_DPHY_CFG0, DPHY_CMN_PDN, regVal));
        cfg->dphyCPdn = valToBool(CPS_FLD_READ(DSITX__MCTL_DPHY_CFG0, DPHY_C_PDN, regVal));
        cfg->dphyDPdn = (uint8_t) CPS_FLD_READ(DSITX__MCTL_DPHY_CFG0, DPHY_D_PDN, regVal);
        cfg->dphyPllPso = valToBool(CPS_FLD_READ(DSITX__MCTL_DPHY_CFG0, DPHY_PLL_PSO, regVal));
        cfg->dphyCmnPso = valToBool(CPS_FLD_READ(DSITX__MCTL_DPHY_CFG0, DPHY_CMN_PSO, regVal));
    }
    return status;
}

/* internal function */
static uint32_t setInitialConfiguration( DSITX_PrivateData* pD, const DSITX_Config* config)
{
    uint32_t result = CDN_EOK;
    /* reg base is taken from config */
    DSITX_Regs* regBase = config->regBase;

    /* set given params */
    pD->regBase = regBase;
    pD->numOfLanes = config->numOfLanes;
    pD->interruptsEnabled = false;
    pD->processingDcr = false;
    pD->dcr = NULL;

    /* disable callbacks */
    pD->fnDcrEventCallback = config->dirCmdEventHandler;
    pD->fnInitDispCallback = config->initDisplay;
    pD->fnDsiLinkCallback = NULL;
    pD->fnCmdModeCallback = NULL;
    pD->fnVidModeCallback = NULL;
    pD->fnTvgCallback = NULL;
    pD->fnDphyErrCallback = NULL;

    /* set default statuses */
    pD->enDsiLinkStsBits = (uint32_t)DSITX_LINK_STATUS_BITS_INIT;
    pD->enCmdModeStsBits = (uint32_t)DSITX_CMD_MODE_STATUS_BITS_INIT;
    pD->enVidModeStsBits = (uint32_t)DSITX_VID_MODE_STATUS_BITS_INIT;
    pD->enTvgStsBits = (uint32_t)DSITX_TVG_STATUS_BITS_INIT;
    pD->enDphyErrBits = (uint32_t)DSITX_DPHY_ERROR_BITS_INIT;

    /* Disable all interrupts */
    CPS_REG_WRITE(&regBase->mctl_main_sts_ctl, 0);
    CPS_REG_WRITE(&regBase->cmd_mode_sts_ctl, 0);
    CPS_REG_WRITE(&regBase->direct_cmd_sts_ctl, 0);
    CPS_REG_WRITE(&regBase->direct_cmd_rd_sts_ctl, 0);
    CPS_REG_WRITE(&regBase->vid_mode_sts_ctl, 0);
    CPS_REG_WRITE(&regBase->tvg_sts_ctl, 0);
    CPS_REG_WRITE(&regBase->mctl_dphy_err_ctl1, 0);
    CPS_REG_WRITE(&regBase->mctl_dphy_err_ctl2, 0);

    return result;
}

/* internal function */
static uint32_t initializeDisplay(DSITX_PrivateData* pD)
{
    uint32_t result = CDN_EOK;

    if (pD->fnInitDispCallback != NULL) {
        result = pD->fnInitDispCallback(pD); /* Let client app initialize Display */
    }

    return result;
}

/* internal function */
static inline uint32_t getLanesReadyMask(const DSITX_PrivateData* pD)
{
    /* data lanes + clk lane */
    uint8_t numOfLanes = pD->numOfLanes + 1U;
    uint8_t i;
    uint32_t lanesMask = 0U;

    const uint32_t lanesReadyMasks[] = {
        DSITX__MCTL_MAIN_STS__CLKLANE_READY_MASK,
        DSITX__MCTL_MAIN_STS__DAT1_READY_MASK,
        DSITX__MCTL_MAIN_STS__DAT2_READY_MASK,
        DSITX__MCTL_MAIN_STS__DAT3_READY_MASK,
        DSITX__MCTL_MAIN_STS__DAT4_READY_MASK
    };

    for (i = 0U; i < numOfLanes; ++i) {
        lanesMask |= lanesReadyMasks[i];
    }

    return lanesMask;
}

/**
 * Checks if lanes are ready.
 * @param[in] pD Pointer to driver's private data object.
 * @param[in] repeatCount status checking repeat count
 * @return CDN_EINVAL If pD is NULL.
 * @return CDN_EIO when lanes are not ready.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_CheckLanesState(const DSITX_PrivateData* pD, uint32_t repeatCount)
{
    uint32_t result = CDN_EOK;
    uint32_t regValue;

    if (DSITX_CheckLanesStateSF(pD) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        uint32_t repeatCountValue = repeatCount;
        uint32_t lanesMask = getLanesReadyMask(pD);
        do {
            regValue = CPS_REG_READ(&pD->regBase->mctl_main_sts);
            --repeatCountValue;
        } while (((regValue & lanesMask) != lanesMask) && (repeatCountValue > 0U));

        if (repeatCountValue == 0U) {
            /* Lanes not ready */
            result = CDN_EIO;
        }
    }
    return result;
}

/**
 * Waits for PLL lock event.
 * @param[in] pD Pointer to driver's private data object.
 * @param[in] repeatCount status checking repeat count
 * @return CDN_EINVAL If pD is NULL.
 * @return CDN_EIO when timeout occurs.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_WaitForPllLock(const DSITX_PrivateData* pD, uint32_t repeatCount)
{
    uint32_t result = CDN_EOK;
    uint32_t regVal;

    /* check params */
    if (DSITX_WaitForPllLockSF(pD) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        uint32_t repeatCountValue = repeatCount;

        /* wait for bit PLL_LCK */
        do {
            regVal = CPS_REG_READ(&pD->regBase->mctl_main_sts);
            --repeatCountValue;
        } while (((CPS_FLD_READ(DSITX__MCTL_MAIN_STS, PLL_LCK, regVal)) == (0U)) && ((repeatCountValue) > (0U)));

        /* mark timeout */
        if (repeatCountValue == 0U) {
            result = CDN_EIO;
        }
    }
    return result;
  }

/**
 * Initializes the Driver and the DSITX Host as specified in the
 * config structure.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Specifies driver/hardware configuration.
 * @return CDN_EOK On success
 * @return CDN_EINVAL If illegal/inconsistent values in 'config' doesn't support feature(s) required by 'config' parameters.
 */
uint32_t DSITX_Init(DSITX_PrivateData* pD, const DSITX_Config* config)
{
     uint32_t result = CDN_EOK;

    /* check params */
    if (DSITX_InitSF(pD, config) != CDN_EOK) {
        result = CDN_EINVAL;
    } else {
        result = setInitialConfiguration(pD, config);
    }

    /* get configuration of IP */
    if (result == CDN_EOK) {
        result = DSITX_GetIpConf(pD, &pD->ip);
    }

    /* initialize display subsystem */
    if (result == CDN_EOK) {
        result = initializeDisplay(pD);
    }

    return result;
}

/* internal function */
static void isrMctl(DSITX_PrivateData* pD)
{
    uint32_t flagRegVal = CPS_REG_READ(&pD->regBase->mctl_main_sts_flag);

    if ((pD->fnDsiLinkCallback != NULL) && (flagRegVal != 0U)) {
        if ((flagRegVal & pD->enDsiLinkStsBits)!= 0U) {
            pD->fnDsiLinkCallback(pD, flagRegVal);
        }
    }

    CPS_REG_WRITE(&pD->regBase->mctl_main_sts_clr, flagRegVal);
}

/* internal function */
static void isrCommandMode(DSITX_PrivateData* pD, uint32_t flagRegVal)
{
    if (pD->fnCmdModeCallback != NULL) {
        if ((flagRegVal & pD->enCmdModeStsBits) != 0U) {
            pD->fnCmdModeCallback(pD, flagRegVal);
        }
    }

    CPS_REG_WRITE(&pD->regBase->cmd_mode_sts_clr, flagRegVal);
}

/* internal function */
static void isrVideoMode(DSITX_PrivateData* pD)
{
    uint32_t flagRegVal = CPS_REG_READ(&pD->regBase->vid_mode_sts_flag);

    if ((pD->fnVidModeCallback != NULL) && (flagRegVal != 0U)) {
        if ((flagRegVal & pD->enVidModeStsBits) != 0U) {
            pD->fnVidModeCallback(pD, flagRegVal);
        }
    }
    CPS_REG_WRITE(&pD->regBase->vid_mode_sts_clr, flagRegVal);
}

/* internal function */
static void isrTvg(DSITX_PrivateData* pD)
{
    uint32_t flagRegVal = CPS_REG_READ(&pD->regBase->tg_sts_flag);

    if ((pD->fnTvgCallback != NULL) && (flagRegVal != 0U)) {
        if ((flagRegVal & pD->enTvgStsBits) != 0U) {
            pD->fnTvgCallback(pD, flagRegVal);
        }
    }
    CPS_REG_WRITE(&pD->regBase->tg_sts_clr, flagRegVal);
}

/* internal function */
static void isrDphy(DSITX_PrivateData* pD)
{
    uint32_t flagRegVal = CPS_REG_READ(&pD->regBase->mctl_dphy_err_flag);

    if ((pD->fnDphyErrCallback != NULL) && (flagRegVal != 0U)) {
        if ((flagRegVal & pD->enDphyErrBits) != 0U) {
            pD->fnDphyErrCallback(pD, flagRegVal);
        }
    }
    CPS_REG_WRITE(&pD->regBase->mctl_dphy_err_clr, flagRegVal);
}

/* internal function */
static void isrDpi(DSITX_PrivateData* pD)
{
    uint32_t flagRegVal = CPS_REG_READ(&pD->regBase->dpi_irq_sts);

    if ((pD->fnDpiCallback != NULL) && (flagRegVal != 0U)) {
        if ((flagRegVal & pD->enDpiStsBits) != 0U) {
            pD->fnDpiCallback(pD, flagRegVal);
        }
    }
    CPS_REG_WRITE(&pD->regBase->dpi_irq_clr, flagRegVal);
}

/* internal function */
static bool canProcessDcr(const DSITX_PrivateData* pD, const uint8_t cmdInt)
{
    return ((cmdInt != 0U)
            && (pD->dcr != NULL)
            && (pD->dcr->wait == false)
            && (pD->fnDcrEventCallback != NULL));
}

/* internal function */
static uint8_t isrProcessDcrInt(DSITX_PrivateData* pD)
{
    uint8_t cmdInt = 0;
    uint32_t flagRegVal = 0;

    DSITX_Regs* regBase = pD->regBase;
    flagRegVal = CPS_REG_READ(&regBase->cmd_mode_sts_flag);
    if (flagRegVal != 0U) {
        isrCommandMode(pD, flagRegVal);
    }

    flagRegVal = CPS_REG_READ(&regBase->direct_cmd_sts_flag);
    if (flagRegVal != 0U) {
        /* Direct Command Interrupt */
        cmdInt = 1;
    }

    flagRegVal = CPS_REG_READ(&regBase->direct_cmd_rd_sts_flag);
    if (flagRegVal != 0U) {
        /* Direct Command Read Interrupt */
        cmdInt = 1;
    }

    return (cmdInt);
}

/* internal function */
static inline void isrProcessDcrCheck(DSITX_PrivateData* pD)
{
    if (pD->fnDcrEventCallback(pD, pD->dcr) == DSITX_DCR_RESULT_FINISHED) {
        pD->processingDcr = false;
        CPS_REG_WRITE(&pD->regBase->direct_cmd_sts_ctl, 0);
        CPS_REG_WRITE(&pD->regBase->direct_cmd_rd_sts_ctl, 0);
    }
}

/* internal function */
static void isrProcessDcr(DSITX_PrivateData* pD)
{
    const uint8_t cmdInt = isrProcessDcrInt(pD);

    if (canProcessDcr(pD, cmdInt)) {
        DSITX_DirectCommandRequest *dcr = pD->dcr;

        uint32_t regVal = CPS_REG_READ(&pD->regBase->direct_cmd_sts);
        dcr->status = regVal & dcr->enEvents;

        regVal = CPS_REG_READ(&pD->regBase->direct_cmd_rd_sts);
        dcr->rdStatus = regVal & dcr->enRdEvents;

        dcr->ackVal = (uint16_t)CPS_FLD_READ(DSITX__DIRECT_CMD_STS, ACK_VAL, dcr->status);
        /* Remove ACK value from status bits; may be removed in case of performance drop */
        dcr->status = dcr->status & (~DSITX__DIRECT_CMD_STS__ACK_VAL_MASK);

        if (dcr->type == DSITX_DCR_TYPE_READ) {
            /* erros connected to read should be handled using status registers */
            (void)readDCRData(pD, dcr);
        }

        isrProcessDcrCheck(pD);
    }
}

/**
 * Driver ISR. Platform-specific code is responsible for ensuring this
 * gets called when the corresponding hardware's interrupt is
 * asserted. Registering the ISR should be done after calling init,
 * and before calling start. The driver's ISR will not attempt to lock
 * any locks, but will perform client callbacks. If the client wishes
 * to defer processing to non-interrupt time, it is responsible for
 * doing so. This function must not be called after calling destroy
 * and releasing private data memory.
 * @param[in] pD Driver instance data filled by init.
 */
void DSITX_Isr(DSITX_PrivateData* pD)
{
    /* check params */
    if ( (DSITX_IsrSF(pD) == CDN_EOK) &&
        (pD->interruptsEnabled != 0U) ) {
            /* call interrupts for each group of features */
            isrProcessDcr(pD);
            isrMctl(pD);
            isrVideoMode(pD);
            isrTvg(pD);
            isrDphy(pD);
                isrDpi(pD);
    }
}

/**
 * DSITX_Start function declaration.
 * See start function of the DSITX_OBJ structure documentation for details.
 */
void DSITX_Start(DSITX_PrivateData* pD)
{
    /* check params */
    if (DSITX_StartSF(pD) == CDN_EOK) {
        pD->interruptsEnabled = 1;
    }
}

/**
 * DSITX_Stop function declaration.
 * See stop function of the DSITX_OBJ structure documentation for details.
 */
void DSITX_Stop(DSITX_PrivateData* pD)
{
    /* check params */
    if (DSITX_StopSF(pD) == CDN_EOK) {
        pD->interruptsEnabled = 0;
    }
}

/**
 * DSITX_Destroy function declaration.
 * See destroy function of the DSITX_OBJ structure documentation for details.
 */
void DSITX_Destroy(DSITX_PrivateData* pD)
{
    /* check params */
    if (DSITX_DestroySF(pD) == CDN_EOK) {
        DSITX_Stop(pD);
    }
}

/**
 * Sets DPHY configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure which specifies DPHY configuration.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If configuration is successfully set.
 */
uint32_t DSITX_SetDphyConfig(const DSITX_PrivateData* pD, const DSITX_DphyConfig* config)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_SetDphyConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* write timing/timeout settings */
        regVal = 0U;
        DSITX_Regs* regBase = pD->regBase;
        regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_TIMEOUT1, CLK_DIV, regVal, config->clkDivisionRatio);
        regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_TIMEOUT1, HSTX_TO_VAL, regVal, config->hstxTimeout);
        CPS_REG_WRITE(&regBase->mctl_dphy_timeout1, regVal);

        regVal = 0;
        regVal = CPS_FLD_WRITE(DSITX__MCTL_DPHY_TIMEOUT2, LPRX_TO_VAL, regVal, config->lprxTimeout);
        CPS_REG_WRITE(&regBase->mctl_dphy_timeout2, regVal);

        /* DSITX_UlpTimeout Structure that specify time to leave ULP mode. */
        regVal = 0;
        regVal = CPS_FLD_WRITE(DSITX__MCTL_ULPOUT_TIME, CKLANE_ULPOUT_TIME, regVal, config->clkLaneUlpTimeout);
        regVal = CPS_FLD_WRITE(DSITX__MCTL_ULPOUT_TIME, DATA_ULPOUT_TIME, regVal, config->dataLaneUlpTimeout);
        CPS_REG_WRITE(&regBase->mctl_ulpout_time, regVal);

        status = CDN_EOK;
    }
    return status;
}

/**
 * Obtains DPHY configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which DPHY configuration will be written.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetDphyConfig(DSITX_PrivateData* pD, DSITX_DphyConfig* config)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_GetDphyConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read timing/clock settings */
        regVal = CPS_REG_READ(&pD->regBase->mctl_dphy_timeout1);
        config->clkDivisionRatio = (uint8_t)CPS_FLD_READ(DSITX__MCTL_DPHY_TIMEOUT1, CLK_DIV, regVal);
        config->hstxTimeout = (uint32_t)CPS_FLD_READ(DSITX__MCTL_DPHY_TIMEOUT1, HSTX_TO_VAL, regVal);

        regVal = CPS_REG_READ(&pD->regBase->mctl_dphy_timeout2);
        config->lprxTimeout = (uint32_t)CPS_FLD_READ(DSITX__MCTL_DPHY_TIMEOUT2, LPRX_TO_VAL, regVal);

        regVal = CPS_REG_READ(&pD->regBase->mctl_ulpout_time);
        config->clkLaneUlpTimeout = (uint16_t)CPS_FLD_READ(DSITX__MCTL_ULPOUT_TIME, CKLANE_ULPOUT_TIME, regVal);
        config->dataLaneUlpTimeout = (uint16_t)CPS_FLD_READ(DSITX__MCTL_ULPOUT_TIME, DATA_ULPOUT_TIME, regVal);

        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static inline void getDataPathConfigTe(DSITX_DataPathConfig* config, uint32_t regValue)
{
    uint32_t regVal = regValue;

    config->teHwPolling = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, TE_HW_POLLING_EN, regVal));
    config->teMipiPolling = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, TE_MIPI_POLLING_EN, regVal));
    config->if1TeEnabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, IF1_TE_EN, regVal));
    config->regTeEnabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, REG_TE_EN, regVal));
}

/* internal function */
static inline void getDataPathConfigDisp(DSITX_DataPathConfig* config, uint32_t regValue)
{
    uint32_t regVal = regValue;

    config->dispGenEcc = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, DISP_GEN_ECC, regVal));
    config->dispGenChecksum = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, DISP_GEN_CHECKSUM, regVal));
    config->dispEotGen = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, DISP_EOT_GEN, regVal));
}

/* internal function */
static uint32_t getDataPathConfigVid(DSITX_DataPathConfig* config, uint32_t regValue)
{
    uint32_t status;

    status = getInterfaceModeEnum(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, SDI_IF_VID_MODE, regValue), &config->interfaceMode);
    status |= getVideoIfSelectEnum(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, VID_IF_SELECT, regValue), &config->videoIfSelect);
    config->videoStreamGenEnabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, VID_EN, regValue));

    return status;
}

/**
 * Obtains Data Path configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which Data Path configuration will be written.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetDataPathConfig(DSITX_PrivateData* pD, DSITX_DataPathConfig* config)
{
    uint32_t regVal;
    uint32_t status = CDN_EOK;

    /* check params */
    if (DSITX_GetDataPathConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read value from register */
        regVal = CPS_REG_READ(&pD->regBase->mctl_main_data_ctl);

        /* call helper functions */
        status = getDataPathConfigVid(config, regVal);
        getDataPathConfigTe(config, regVal);
        getDataPathConfigDisp(config, regVal);

        /* extract fields from value */
        config->linkEnabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, LINK_EN, regVal));
        config->tvgEnabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, TVG_SEL, regVal));
        config->readOpEnabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, READ_EN, regVal));
        config->btaEnabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, BTA_EN, regVal));
        config->hostEotGen = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_DATA_CTL, HOST_EOT_GEN, regVal));
    }
    return status;
}

/**
 * Obtains PHY configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which PHY configuration will be written.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If configuration is successfully obtained.
 */
uint32_t DSITX_GetPhyConfig(DSITX_PrivateData* pD, DSITX_PhyConfig* config)
{
    uint32_t regVal;
    uint32_t status;
    uint32_t i;

    /* check params */
    if (DSITX_GetPhyConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register and split it to fields */
        regVal = CPS_REG_READ(&pD->regBase->mctl_main_phy_ctl);
        config->lane2Enabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_PHY_CTL, LANE2_EN, regVal));
        config->lane3Enabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_PHY_CTL, LANE3_EN, regVal));
        config->lane4Enabled = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_PHY_CTL, LANE4_EN, regVal));
        config->laneClkContinous = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_PHY_CTL, CLK_CONTINUOUS, regVal));
        config->laneClkUlpMode = valToBool(CPS_FLD_READ(DSITX__MCTL_MAIN_PHY_CTL, CLK_ULPM_EN, regVal));

        /* convert lane ulp mode from register value to array */
        for (i = 0U; i < ((uint32_t)DSITX_MAX_LANE_NUMBER); ++i) {
            config->laneUlpMode[i] = valToBool(CPS_FldRead(phyConfig_defs[i].laneUlpMode_mask, phyConfig_defs[i].laneUlpMode_shift, regVal));
        }

        config->waitBurstTime = (uint8_t)(CPS_FLD_READ(DSITX__MCTL_MAIN_PHY_CTL, WAIT_BURST_TIME, regVal));

        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static void setCommandModeCtl(DSITX_PrivateData* pD, const DSITX_CommandModeSettings* cmdMode)
{
    uint32_t regVal = 0U;

    /* build write value */
    regVal = CPS_FLD_WRITE(DSITX__CMD_MODE_CTL, IF1_ID, regVal, cmdMode->vcIdIf1);
    regVal = CPS_FLD_WRITE(DSITX__CMD_MODE_CTL, IF3_ID, regVal, cmdMode->vcIdIf3);
    regVal = CPS_FLD_WRITE(DSITX__CMD_MODE_CTL, IF1_LP_EN, regVal, boolToVal(cmdMode->sendFromInt1InLp));
    regVal = CPS_FLD_WRITE(DSITX__CMD_MODE_CTL, IF3_LP_EN, regVal, boolToVal(cmdMode->sendFromInt3InLp));
    CPS_REG_WRITE(&pD->regBase->cmd_mode_ctl, regVal);
}

/* internal function */
static void setCommandModeCtl2(DSITX_PrivateData* pD, const DSITX_CommandModeSettings* cmdMode)
{
    uint32_t regVal = 0U;

    /* build write value */
    regVal = CPS_FLD_WRITE(DSITX__CMD_MODE_CTL2, ARB_MODE, regVal, (uint32_t)cmdMode->arbMode);
    regVal = CPS_FLD_WRITE(DSITX__CMD_MODE_CTL2, ARB_PRI, regVal, (uint32_t)cmdMode->arbPriority);
    regVal = CPS_FLD_WRITE(DSITX__CMD_MODE_CTL2, FIL_VALUE, regVal, cmdMode->fillValue);
    regVal = CPS_FLD_WRITE(DSITX__CMD_MODE_CTL2, TE_TIMEOUT, regVal, cmdMode->teTimeout);
    CPS_REG_WRITE(&pD->regBase->cmd_mode_ctl2, regVal);
}

/**
 * Sets Command Mode configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] cmdMode Pointer to structure containing detailed information about
 *    Command Mode configuration.
 * @return CDN_EINVAL If cmdMode contains invalid values.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_SetCommandMode(DSITX_PrivateData* pD, const DSITX_CommandModeSettings* cmdMode)
{
    uint32_t status;

    /* check params */
    if (DSITX_SetCommandModeSF(pD, cmdMode) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        setCommandModeCtl(pD, cmdMode);
        setCommandModeCtl2(pD, cmdMode);

        status = CDN_EOK;
    }
    return status;
}

/**
 * Reads Command Mode configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] cmdMode Pointer to structure to which detailed information about
 *    Command Mode configuration will be written.
 * @return CDN_EINVAL If pD or cmdMode is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_GetCommandMode(DSITX_PrivateData* pD, DSITX_CommandModeSettings* cmdMode)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_GetCommandModeSF(pD, cmdMode) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register */
        regVal = CPS_REG_READ(&pD->regBase->cmd_mode_ctl);
        /* extract fields */
        cmdMode->vcIdIf1 = (uint8_t)CPS_FLD_READ(DSITX__CMD_MODE_CTL, IF1_ID, regVal);
        cmdMode->vcIdIf3 = (uint8_t)CPS_FLD_READ(DSITX__CMD_MODE_CTL, IF3_ID, regVal);
        cmdMode->sendFromInt1InLp = valToBool(CPS_FLD_READ(DSITX__CMD_MODE_CTL, IF1_LP_EN, regVal));
        cmdMode->sendFromInt3InLp = valToBool(CPS_FLD_READ(DSITX__CMD_MODE_CTL, IF3_LP_EN, regVal));

        /* read register */
        regVal = CPS_REG_READ(&pD->regBase->cmd_mode_ctl2);
        /* extract fields */
        status = getCommandArbitrationModeEnum(CPS_FLD_READ(DSITX__CMD_MODE_CTL2, ARB_MODE, regVal), &cmdMode->arbMode);
        status |= getCmdArbitrationPriorityEnum(CPS_FLD_READ(DSITX__CMD_MODE_CTL2, ARB_PRI, regVal), &cmdMode->arbPriority);
        cmdMode->fillValue = (uint8_t)CPS_FLD_READ(DSITX__CMD_MODE_CTL2, FIL_VALUE, regVal);
        cmdMode->teTimeout = (uint16_t)CPS_FLD_READ(DSITX__CMD_MODE_CTL2, TE_TIMEOUT, regVal);
    }
    return status;
}

/* internal function */
static uint32_t setVideoModeMainCtl1(const DSITX_VideoModeSettings* vidMode, uint32_t regValue)
{
    uint32_t regVal = regValue;

    /* build value for register */
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, START_MODE, regVal, vidMode->startMode);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, STOP_MODE, regVal, vidMode->stopMode);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, VID_ID, regVal, vidMode->vidId);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, VID_ID_SDFD, regVal, vidMode->vidIdSdfd);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, VID_PIXEL_MODE, regVal, vidMode->vidPixelMode);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, BURST_MODE, regVal, boolToVal(vidMode->burstMode));
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, SYNC_PULSE_ACTIVE, regVal, boolToVal(vidMode->syncPulseActive));

    return regVal;
}

/* internal function */
static uint32_t setVideoModeMainCtl2(const DSITX_VideoModeSettings* vidMode, uint32_t regValue)
{
    uint32_t regVal = regValue;

    /* build value for register */
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, SYNC_PULSE_HORIZONTAL, regVal, boolToVal(vidMode->syncPulseHorizontal));
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, REG_BLKLINE_MODE, regVal, vidMode->blkLineMode);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, REG_BLKEOL_MODE, regVal, vidMode->blkEolMode);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, RECOVERY_MODE, regVal, vidMode->recoveryMode);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, VID_INTERLACED_EN, regVal, boolToVal(vidMode->interlancedVideoModeEnabled));
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, VID_FIELD_SW, regVal, vidMode->fieldSwitch);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, HEADER, regVal, vidMode->header);
    regVal = CPS_FLD_WRITE(DSITX__VID_MAIN_CTL, VID_IGNORE_MISS_VSYNC, regVal, boolToVal(vidMode->ignoreMissVsync));

    return regVal;
}

/* internal function */
static void setVideoModeCfgColors(DSITX_Regs* regBase, const DSITX_VideoModeSettings* vidMode)
{
    uint32_t regVal = 0U;

    /* set error colors */
    regVal = CPS_FLD_WRITE(DSITX__VID_ERR_COLOR1, COL_RED, regVal, vidMode->errColor.r);
    regVal = CPS_FLD_WRITE(DSITX__VID_ERR_COLOR1, COL_GREEN, regVal, vidMode->errColor.g);
    CPS_REG_WRITE(&regBase->vid_err_color1, regVal);

    regVal = 0U;
    regVal = CPS_FLD_WRITE(DSITX__VID_ERR_COLOR2, COL_BLUE, regVal, vidMode->errColor.b);
    regVal = CPS_FLD_WRITE(DSITX__VID_ERR_COLOR2, PAD_VALUE, regVal, vidMode->errColor.padValue);
    CPS_REG_WRITE(&regBase->vid_err_color2, regVal);
}

/* internal function */
static void setVideoModeCfg(const DSITX_PrivateData* pD, const DSITX_VideoModeSettings* vidMode)
{
    uint32_t regVal;
    DSITX_Regs* regBase = pD->regBase;

    /* write timing parameters */
    regVal = 0;
    regVal = CPS_FLD_WRITE(DSITX__VID_PCK_TIME, BLKEOL_DURATION, regVal, vidMode->blkEolDuration);
    CPS_REG_WRITE(&regBase->vid_pck_time, regVal);

    regVal = 0;
    regVal = CPS_FLD_WRITE(DSITX__VID_DPHY_TIME, REG_WAKEUP_TIME, regVal, vidMode->regWakeupTime);
    regVal = CPS_FLD_WRITE(DSITX__VID_DPHY_TIME, REG_LINE_DURATION, regVal, vidMode->regLineDuration);
    CPS_REG_WRITE(&regBase->vid_dphy_time, regVal);

    /* set video parameters */
    regVal = 0U;
    regVal = setVideoModeMainCtl1(vidMode, regVal);
    regVal = setVideoModeMainCtl2(vidMode, regVal);
    CPS_REG_WRITE(&regBase->vid_main_ctl, regVal);

    /* set error colors */
    setVideoModeCfgColors(regBase, vidMode);
}

/**
 * Sets Video Mode configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] vidMode Pointer to structure containing Video Mode configuration.
 * @return CDN_EINVAL If provided configuration contains invalid values.
 * @return CDN_EOK If configuration is successfully set.
 */
uint32_t DSITX_SetVideoMode(const DSITX_PrivateData* pD, const DSITX_VideoModeSettings* vidMode)
{
    uint32_t status;

    /* check params */
    if (DSITX_SetVideoModeSF(pD, vidMode) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* perform setting */
        setVideoModeCfg(pD, vidMode);
        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static uint32_t getVideoModeMainCtl1(DSITX_VideoModeSettings* vidMode, uint32_t regValue)
{
    uint32_t regVal = regValue;
    uint32_t status;

    /* convert field value to enum */
    status = getVideoPixelModeEnum(CPS_FLD_READ(DSITX__VID_MAIN_CTL, VID_PIXEL_MODE, regVal), &vidMode->vidPixelMode);
    status |= getHeaderEnum(CPS_FLD_READ(DSITX__VID_MAIN_CTL, HEADER, regVal), &vidMode->header);
    status |= getVideoStopModeEnum(CPS_FLD_READ(DSITX__VID_MAIN_CTL, STOP_MODE, regVal), &vidMode->stopMode);
    status |= getVideoStartModeEnum(CPS_FLD_READ(DSITX__VID_MAIN_CTL, START_MODE, regVal), &vidMode->startMode);

    if (CDN_EOK == status) {
        /* convert flags to boolean */
        vidMode->vidId = (uint8_t)CPS_FLD_READ(DSITX__VID_MAIN_CTL, VID_ID, regVal);
        vidMode->vidIdSdfd = (uint8_t)CPS_FLD_READ(DSITX__VID_MAIN_CTL, VID_ID_SDFD, regVal);
        vidMode->burstMode = valToBool(CPS_FLD_READ(DSITX__VID_MAIN_CTL, BURST_MODE, regVal));
    }

    return status;
}

/* internal function */
static uint32_t getVideoModeMainCtl2(DSITX_VideoModeSettings* vidMode, uint32_t regValue)
{
    uint32_t regVal = regValue;
    uint32_t status;

    /* convert field value to enum */
    status = getVideoRecoveryModeEnum(CPS_FLD_READ(DSITX__VID_MAIN_CTL, RECOVERY_MODE, regVal), &vidMode->recoveryMode);
    status |= getVideoBlankingModeEnum(CPS_FLD_READ(DSITX__VID_MAIN_CTL, REG_BLKLINE_MODE, regVal), &vidMode->blkLineMode);
    status |= getVideoBlankingModeEnum(CPS_FLD_READ(DSITX__VID_MAIN_CTL, REG_BLKEOL_MODE, regVal), &vidMode->blkEolMode);

    if (CDN_EOK == status) {
        /* convert flags to boolean */
        vidMode->syncPulseActive = valToBool(CPS_FLD_READ(DSITX__VID_MAIN_CTL, SYNC_PULSE_ACTIVE, regVal));
        vidMode->syncPulseHorizontal = valToBool(CPS_FLD_READ(DSITX__VID_MAIN_CTL, SYNC_PULSE_HORIZONTAL, regVal));
        vidMode->interlancedVideoModeEnabled = valToBool(CPS_FLD_READ(DSITX__VID_MAIN_CTL, VID_INTERLACED_EN, regVal));
        vidMode->fieldSwitch = (uint8_t)CPS_FLD_READ(DSITX__VID_MAIN_CTL, VID_FIELD_SW, regVal);
		vidMode->ignoreMissVsync = valToBool(CPS_FLD_READ(DSITX__VID_MAIN_CTL, VID_IGNORE_MISS_VSYNC, regVal));
    }
    return status;
}

/* internal function */
static void getVideoModeErrColors(DSITX_Regs* regBase, DSITX_VideoModeSettings* vidMode)
{
    uint32_t regVal;

    /* read RGB values from registers */
    regVal = CPS_REG_READ(&regBase->vid_err_color1);
    vidMode->errColor.r = (uint16_t)CPS_FLD_READ(DSITX__VID_ERR_COLOR1, COL_RED, regVal);
    vidMode->errColor.g = (uint16_t)CPS_FLD_READ(DSITX__VID_ERR_COLOR1, COL_GREEN, regVal);

    regVal = CPS_REG_READ(&regBase->vid_err_color2);
    vidMode->errColor.b = (uint16_t)CPS_FLD_READ(DSITX__VID_ERR_COLOR2, COL_BLUE, regVal);
    vidMode->errColor.padValue = (uint16_t)CPS_FLD_READ(DSITX__VID_ERR_COLOR2, PAD_VALUE, regVal);
}

/* internal function */
static uint32_t getVideoModeCfg(const DSITX_PrivateData* pD, DSITX_VideoModeSettings* vidMode)
{
    uint32_t regVal;
    uint32_t status;
    DSITX_Regs* regBase = pD->regBase;

    regVal = CPS_REG_READ(&pD->regBase->vid_main_ctl);

    /* get registers */
    status = getVideoModeMainCtl2(vidMode, regVal);
    status |= getVideoModeMainCtl1(vidMode, regVal);

    if (CDN_EOK == status) {
        /* get error colors */
        getVideoModeErrColors(regBase, vidMode);

        /* get rest parameters */
        regVal = CPS_REG_READ(&regBase->vid_pck_time);
        vidMode->blkEolDuration = (uint16_t)CPS_FLD_READ(DSITX__VID_PCK_TIME, BLKEOL_DURATION, regVal);

        regVal = CPS_REG_READ(&regBase->vid_dphy_time);
        vidMode->regWakeupTime = (uint16_t)CPS_FLD_READ(DSITX__VID_DPHY_TIME, REG_WAKEUP_TIME, regVal);
        vidMode->regLineDuration = (uint16_t)CPS_FLD_READ(DSITX__VID_DPHY_TIME, REG_LINE_DURATION, regVal);
    }
    return status;
}

/**
 * Reads Video Mode configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] vidMode Pointer to structure to which Video Mode configuration will be written.
 * @return CDN_EINVAL If pD or vidMode is NULL.
 * @return CDN_EOK If configuration was successfully read.
 */
uint32_t DSITX_GetVideoMode(const DSITX_PrivateData* pD, DSITX_VideoModeSettings* vidMode)
{
    uint32_t status;

    if (DSITX_GetVideoModeSF(pD, vidMode) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        status = getVideoModeCfg(pD, vidMode);
    }

    return status;
}

/**
 * Sets Video Command Arbiter configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] vca Pointer to structure containing Video Command Arbiter configuration.
 * @return CDN_EINVAL If provided configuration contains invalid values.
 * @return CDN_EOK If configuration is successfully set.
 */
uint32_t DSITX_SetVcaConfig(DSITX_PrivateData* pD, const DSITX_VcaConfig* vca)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_SetVcaConfigSF(pD, vca) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* set first register */
        regVal = 0;
        regVal = CPS_FLD_WRITE(DSITX__VID_VCA_SETTING1, MAX_BURST_LIMIT, regVal, vca->maxBurstLimit);
        regVal = CPS_FLD_WRITE(DSITX__VID_VCA_SETTING1, BURST_LP, regVal, boolToVal(vca->burstLp));
        CPS_REG_WRITE(&pD->regBase->vid_vca_setting1, regVal);

        /* set second register */
        regVal = 0;
        regVal = CPS_FLD_WRITE(DSITX__VID_VCA_SETTING2, EXACT_BURST_LIMIT, regVal, vca->exactBurstLimit);
        regVal = CPS_FLD_WRITE(DSITX__VID_VCA_SETTING2, MAX_LINE_LIMIT, regVal, vca->maxLineLimit);
        CPS_REG_WRITE(&pD->regBase->vid_vca_setting2, regVal);

        status = CDN_EOK;
    }
    return status;
}

/**
 * Reads Video Command Arbiter configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] vca Pointer to structure to which Video Command Arbiter configuration will be written.
 * @return CDN_EINVAL If pD or vca is NULL.
 * @return CDN_EOK If size is successfully set.
 */
uint32_t DSITX_GetVcaConfig(DSITX_PrivateData* pD, DSITX_VcaConfig* vca)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_GetVcaConfigSF(pD, vca) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read first register */
        regVal = CPS_REG_READ(&pD->regBase->vid_vca_setting1);
        vca->maxBurstLimit = (uint16_t)CPS_FLD_READ(DSITX__VID_VCA_SETTING1, MAX_BURST_LIMIT, regVal);
        vca->burstLp = valToBool(CPS_FLD_READ(DSITX__VID_VCA_SETTING1, BURST_LP, regVal));

        /* read second register */
        regVal = CPS_REG_READ(&pD->regBase->vid_vca_setting2);
        vca->exactBurstLimit = (uint16_t)CPS_FLD_READ(DSITX__VID_VCA_SETTING2, EXACT_BURST_LIMIT, regVal);
        vca->maxLineLimit = (uint16_t)CPS_FLD_READ(DSITX__VID_VCA_SETTING2, MAX_LINE_LIMIT, regVal);

        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static void setVideoSizeVertical(DSITX_PrivateData* pD, const DSITX_VideoSize* vidSize)
{
    uint32_t regVal;

    /* set video vertical parameters */
    regVal = 0;
    regVal = CPS_FLD_WRITE(DSITX__VID_VSIZE1, VSA_LENGTH, regVal, vidSize->vsa);
    regVal = CPS_FLD_WRITE(DSITX__VID_VSIZE1, VBP_LENGTH, regVal, vidSize->vbp);
    regVal = CPS_FLD_WRITE(DSITX__VID_VSIZE1, VFP_LENGTH, regVal, vidSize->vfp);
    CPS_REG_WRITE(&pD->regBase->vid_vsize1, regVal);

    regVal = 0;
    regVal = CPS_FLD_WRITE(DSITX__VID_VSIZE2, VACT_LENGTH, regVal, vidSize->vact);
    CPS_REG_WRITE(&pD->regBase->vid_vsize2, regVal);
}

/* internal function */
static void setVideoSizeHorizontal(DSITX_PrivateData* pD, const DSITX_VideoSize* vidSize)
{
    uint32_t regVal;

    /* set video horizontal parameters */
    regVal = 0;
    regVal = CPS_FLD_WRITE(DSITX__VID_HSIZE1, HSA_LENGTH, regVal, vidSize->hsa);
    regVal = CPS_FLD_WRITE(DSITX__VID_HSIZE1, HBP_LENGTH, regVal, vidSize->hbp);
    CPS_REG_WRITE(&pD->regBase->vid_hsize1, regVal);

    regVal = 0;
    regVal = CPS_FLD_WRITE(DSITX__VID_HSIZE2, HFP_LENGTH, regVal, vidSize->hfp);
    regVal = CPS_FLD_WRITE(DSITX__VID_HSIZE2, RGB_SIZE, regVal, vidSize->rgb);
    CPS_REG_WRITE(&pD->regBase->vid_hsize2, regVal);
}

/**
 * Sets Video size configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] vidSize Pointer to structure containing Video Size configuration.
 * @return CDN_EINVAL If provided configuration contains invalid values.
 * @return CDN_EOK If configuration is successfully set.
 */
uint32_t DSITX_SetVideoSize(DSITX_PrivateData* pD, const DSITX_VideoSize* vidSize)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_SetVideoSizeSF(pD, vidSize) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* set size parameters */
        setVideoSizeVertical(pD, vidSize);
        setVideoSizeHorizontal(pD, vidSize);

        /* set additional parameters */
        regVal = 0;
        regVal = CPS_FLD_WRITE(DSITX__VID_BLKSIZE1, BLKEOL_PCK, regVal, vidSize->blkEolPacket);
        regVal = CPS_FLD_WRITE(DSITX__VID_BLKSIZE1, BLKLINE_EVENT_PCK, regVal, vidSize->blkLineEventPacket);
        CPS_REG_WRITE(&pD->regBase->vid_blksize1, regVal);

        regVal = 0;
        regVal = CPS_FLD_WRITE(DSITX__VID_BLKSIZE2, BLKLINE_PULSE_PCK, regVal, vidSize->blkLinePulsePacket);
        CPS_REG_WRITE(&pD->regBase->vid_blksize2, regVal);

        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static void getVideoSizeVertical(DSITX_PrivateData* pD, DSITX_VideoSize* vidSize)
{
    uint32_t regVal;

    /* read video vertical parameters */
    regVal = CPS_REG_READ(&pD->regBase->vid_vsize1);
    vidSize->vsa = (uint8_t)CPS_FLD_READ(DSITX__VID_VSIZE1, VSA_LENGTH, regVal);
    vidSize->vbp = (uint8_t)CPS_FLD_READ(DSITX__VID_VSIZE1, VBP_LENGTH, regVal);
    vidSize->vfp = (uint8_t)CPS_FLD_READ(DSITX__VID_VSIZE1, VFP_LENGTH, regVal);

    regVal = CPS_REG_READ(&pD->regBase->vid_vsize2);
    vidSize->vact = (uint16_t)CPS_FLD_READ(DSITX__VID_VSIZE2, VACT_LENGTH, regVal);
}

/* internal function */
static void getVideoSizeHorizontal(DSITX_PrivateData* pD, DSITX_VideoSize* vidSize)
{
    uint32_t regVal;

    /* read video horizontal parameters */
    regVal = CPS_REG_READ(&pD->regBase->vid_hsize1);
    vidSize->hsa = (uint16_t)CPS_FLD_READ(DSITX__VID_HSIZE1, HSA_LENGTH, regVal);
    vidSize->hbp = (uint16_t)CPS_FLD_READ(DSITX__VID_HSIZE1, HBP_LENGTH, regVal);

    regVal = CPS_REG_READ(&pD->regBase->vid_hsize2);
    vidSize->rgb = (uint16_t)CPS_FLD_READ(DSITX__VID_HSIZE2, RGB_SIZE, regVal);
    vidSize->hfp = (uint16_t)CPS_FLD_READ(DSITX__VID_HSIZE2, HFP_LENGTH, regVal);
}

/**
 * Reads Video size configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] vidSize Pointer to structure to which Video Size configuration will be written.
 * @return CDN_EINVAL If pD or vidSize is NULL.
 * @return CDN_EOK If size is successfully set.
 */
uint32_t DSITX_GetVideoSize(DSITX_PrivateData* pD, DSITX_VideoSize* vidSize)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_GetVideoSizeSF(pD, vidSize) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get size parameters */
        getVideoSizeVertical(pD, vidSize);
        getVideoSizeHorizontal(pD, vidSize);

        /* get additional parameters */
        regVal = CPS_REG_READ(&pD->regBase->vid_blksize1);
        vidSize->blkEolPacket = (uint16_t)CPS_FLD_READ(DSITX__VID_BLKSIZE1, BLKEOL_PCK, regVal);
        vidSize->blkLineEventPacket = (uint16_t)CPS_FLD_READ(DSITX__VID_BLKSIZE1, BLKLINE_EVENT_PCK, regVal);

        regVal = CPS_REG_READ(&pD->regBase->vid_blksize2);
        vidSize->blkLinePulsePacket = (uint16_t)CPS_FLD_READ(DSITX__VID_BLKSIZE2, BLKLINE_PULSE_PCK, regVal);

        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static void setTvgConfigColor1rgb(const DSITX_PrivateData* pD, const DSITX_TestVideoModeConfig* config)
{
    uint32_t regVal = 0U;
    const DSITX_Color* col1 = &config->color1;
    DSITX_Regs* regBase = pD->regBase;

    /* write palette for first color */
    regVal = CPS_FLD_WRITE(DSITX__TVG_COLOR1, COL1_RED, regVal, col1->r);
    regVal = CPS_FLD_WRITE(DSITX__TVG_COLOR1, COL1_GREEN, regVal, col1->g);
    CPS_REG_WRITE(&regBase->tvg_color1, regVal);

    regVal = 0U;
    regVal = CPS_FLD_WRITE(DSITX__TVG_COLOR1_BIS, COL1_BLUE, regVal, col1->b);
    CPS_REG_WRITE(&regBase->tvg_color1_bis, regVal);
}

/* internal function */
static void setTvgConfigColor2rgb(const DSITX_PrivateData* pD, const DSITX_TestVideoModeConfig* config)
{
    uint32_t regVal = 0U;
    const DSITX_Color* col2 = &config->color2;
    DSITX_Regs* regBase = pD->regBase;

    /* write palette for second color */
    regVal = CPS_FLD_WRITE(DSITX__TVG_COLOR2, COL2_RED, regVal, col2->r);
    regVal = CPS_FLD_WRITE(DSITX__TVG_COLOR2, COL2_GREEN, regVal, col2->g);
    CPS_REG_WRITE(&regBase->tvg_color2, regVal);

    regVal = 0U;
    regVal = CPS_FLD_WRITE(DSITX__TVG_COLOR2_BIS, COL2_BLUE, regVal, col2->b);
    CPS_REG_WRITE(&regBase->tvg_color2_bis, regVal);
}

/**
 * Configures Test Video Generator using provided configuration. This
 * function ignores value of 'enabled' field in config structure. New
 * configuration can be applied only if Test Video Generator is not
 * running.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] config Pointer to structure containing Test Video Generator configuration.
 *    Value of the enabled field is ignored. Use startTvg function to enable TVG.
 * @return CDN_EINVAL If provided configuration contains invalid values.
 * @return CDN_EPERM If Test Video Generator is enabled.
 * @return CDN_EOK If Test Video Generator was successfully started.
 */
uint32_t DSITX_SetTvgConfig(const DSITX_PrivateData* pD, const DSITX_TestVideoModeConfig* config)
{
    uint32_t status;

    /* check params */
    if (DSITX_SetTvgConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else if (config->enabled != 0U) {
        status = CDN_EINVAL;
    } else {
        DSITX_Regs* regBase = pD->regBase;

        uint32_t regVal = CPS_REG_READ(&regBase->tvg_sts);

        if ((CPS_FLD_READ(DSITX__TVG_STS, TVG_RUNNING, regVal)) != 0U) {
            /* TVG is running. Configuration was not set. */
            status = CDN_EPERM;
        } else {
            /* set image parameters */
            regVal = 0;
            regVal = CPS_FLD_WRITE(DSITX__TVG_IMG_SIZE, TVG_LINE_SIZE, regVal, config->bytesPerLine);
            regVal = CPS_FLD_WRITE(DSITX__TVG_IMG_SIZE, TVG_NBLINE, regVal, config->linesPerFrame);
            CPS_REG_WRITE(&regBase->tvg_img_size, regVal);

            /* set both colors */
            setTvgConfigColor1rgb(pD, config);
            setTvgConfigColor2rgb(pD, config);

            /* set pattern */
            regVal = 0;
            regVal = CPS_FLD_WRITE(DSITX__TVG_CTL, TVG_STRIPE_SIZE, regVal, (uint32_t)config->stripeSize);
            regVal = CPS_FLD_WRITE(DSITX__TVG_CTL, TVG_MODE, regVal, (uint32_t)config->displayMode);
            regVal = CPS_FLD_WRITE(DSITX__TVG_CTL, TVG_STOPMODE, regVal, (uint32_t)config->stopMode);
            CPS_REG_WRITE(&regBase->tvg_ctl, regVal);

            status = CDN_EOK;
        }
    }
    return status;
}

/* internal function */
static void getTvgConfigColor1rgb(DSITX_PrivateData* pD, DSITX_TestVideoModeConfig* config)
{
    uint32_t regVal;

    /* read palette for 1st colour */
    regVal = CPS_REG_READ(&pD->regBase->tvg_color1);
    config->color1.r = (uint16_t)CPS_FLD_READ(DSITX__TVG_COLOR1, COL1_RED, regVal);
    config->color1.g = (uint16_t)CPS_FLD_READ(DSITX__TVG_COLOR1, COL1_GREEN, regVal);

    regVal = CPS_REG_READ(&pD->regBase->tvg_color1_bis);
    config->color1.b = (uint16_t)CPS_FLD_READ(DSITX__TVG_COLOR1_BIS, COL1_BLUE, regVal);
}

/* internal function */
static void getTvgConfigColor2rgb(DSITX_PrivateData* pD, DSITX_TestVideoModeConfig* config)
{
    uint32_t regVal;

    /* read palette for 2nd colour */
    regVal = CPS_REG_READ(&pD->regBase->tvg_color2);
    config->color2.r = (uint16_t)CPS_FLD_READ(DSITX__TVG_COLOR2, COL2_RED, regVal);
    config->color2.g = (uint16_t)CPS_FLD_READ(DSITX__TVG_COLOR2, COL2_GREEN, regVal);

    regVal = CPS_REG_READ(&pD->regBase->tvg_color2_bis);
    config->color2.b = (uint16_t)CPS_FLD_READ(DSITX__TVG_COLOR2_BIS, COL2_BLUE, regVal);
}

/* internal function */
static uint32_t getTvgConfigCtl(DSITX_PrivateData* pD, DSITX_TestVideoModeConfig* config)
{
    uint32_t regVal;
    uint32_t status;

    /* read TVG settings from register */
    regVal = CPS_REG_READ(&pD->regBase->tvg_ctl);

    status = getTvgDisplayModeEnum(CPS_FLD_READ(DSITX__TVG_CTL, TVG_MODE, regVal), &config->displayMode);
    status |= getTvgStripeSizeEnum(CPS_FLD_READ(DSITX__TVG_CTL, TVG_STRIPE_SIZE, regVal), &config->stripeSize);
    status |= getTvgStopModeEnum(CPS_FLD_READ(DSITX__TVG_CTL, TVG_STOPMODE, regVal), &config->stopMode);

    config->enabled = valToBool(CPS_FLD_READ(DSITX__TVG_CTL, TVG_RUN, regVal));

    return status;
}

/**
 * Reads Test Video Generator configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] config Pointer to structure to which received Test Video Generator
 *    configuration will be written.
 * @return CDN_EINVAL If pD or config is NULL.
 * @return CDN_EOK If Test Video Generator configuration was successfully read.
 */
uint32_t DSITX_GetTvgConfig(DSITX_PrivateData* pD, DSITX_TestVideoModeConfig* config)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_GetTvgConfigSF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* get config */
        status = getTvgConfigCtl(pD, config);

        if (CDN_EOK == status) {
            /* get palette for both tvg colors */
            getTvgConfigColor1rgb(pD, config);
            getTvgConfigColor2rgb(pD, config);

            /* extract image parameters */
            regVal = CPS_REG_READ(&pD->regBase->tvg_img_size);
            config->bytesPerLine = (uint16_t)CPS_FLD_READ(DSITX__TVG_IMG_SIZE, TVG_LINE_SIZE, regVal);
            config->linesPerFrame = (uint16_t)CPS_FLD_READ(DSITX__TVG_IMG_SIZE, TVG_NBLINE, regVal);
        }
    }
    return status;
}

/**
 * Enables Test Video Generator.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] wait Determines if function will wait until Test Video Generator is started
 *    (true) or will exit immediately (false) and raise TVG Event (if enabled)
 *    when TVG starts.
 * @return CDN_EINVAL If pD is NULL.
 * @return CDN_EIO On timeout.
 * @return CDN_EOK If operation was successful.
 */
uint32_t DSITX_StartTvg(DSITX_PrivateData* pD, bool wait)
{
    uint32_t regVal;
    uint32_t timeout = REG_POOL_TIMEOUT;
    uint32_t status;

    if (DSITX_StartTvgSF(pD) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* Enabling TVG */
        if (CPS_FLD_READ(DSITX__MCTL_MAIN_EN, IF1_EN, CPS_REG_READ(&pD->regBase->mctl_main_en)) != 0U) {
            /* TVG cannot be enabled while Video Interface is running */
            status = CDN_EINVAL;
        } else {

            regVal = CPS_REG_READ(&pD->regBase->tvg_ctl);
            regVal = CPS_FLD_WRITE(DSITX__TVG_CTL, TVG_RUN, regVal, 1);
            CPS_REG_WRITE(&pD->regBase->tvg_ctl, regVal);

            status = CDN_EOK;

            if (wait != 0U) { /* add watchdog in case of TBG never starting? */
                /* Waiting for TVG to start. */
                do {
                    regVal = CPS_REG_READ(&pD->regBase->tvg_sts);
                    --timeout;
                } while ((CPS_FLD_READ(DSITX__TVG_STS, TVG_RUNNING, regVal) == 0U) && (timeout != 0U));

                if (timeout == 0U) {
                    /* Failed to start TVG */
                    status = CDN_EIO;
                }
            }
        }
    }
    return status;
}

/**
 * Stops Test Video Generator. If stop mode is 'stop immediate' then
 * the VSG needs to be stopped and video system restarted.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] wait Determines if function will wait until Test Video Generator is in
 *    stopped state (true) or will exit immediately (false).
 * @return CDN_EINVAL If pD is NULL.
 * @return CDN_EPERM If TVG stop mode is set to 'stop immediate'.
 * @return CDN_EIO On timeout.
 * @return CDN_EOK If operation was successful.
 */
uint32_t DSITX_StopTvg(DSITX_PrivateData* pD, bool wait)
{
    uint32_t regVal = 0;
    uint32_t timeout = REG_POOL_TIMEOUT;
    uint32_t status = CDN_EOK;

    if (DSITX_StopTvgSF(pD) != CDN_EOK) {
        status = CDN_EINVAL;
    }

    if (status == CDN_EOK) {
        regVal = CPS_REG_READ(&pD->regBase->tvg_ctl);

        if ((CPS_FLD_READ(DSITX__TVG_CTL, TVG_STOPMODE, regVal) == (uint32_t)DSITX_TVG_STOP_MODE_IMMEDIATE)) {
            /* In current stop mode (immediate) */
            /*  whole video system needs to be restarted in order to stop TVG */
            status = CDN_EPERM;
        }
    }

    if (status == CDN_EOK) {
        /* Disabling TVG */
        regVal = CPS_REG_READ(&pD->regBase->tvg_ctl);
        regVal = CPS_FLD_WRITE(DSITX__TVG_CTL, TVG_RUN, regVal, 0);
        CPS_REG_WRITE(&pD->regBase->tvg_ctl, regVal);

        if (wait != 0U) {
            /* Waiting for TVG to stop */
            do {
                regVal = CPS_REG_READ(&pD->regBase->tvg_sts);
                --timeout;
            } while ((CPS_FLD_READ(DSITX__TVG_STS, TVG_RUNNING, regVal) != 0U) && (timeout != 0U));

            if (timeout == 0U) {
                /* Failed to stop TVG */
                status = CDN_EIO;
            }
        }
    }
    return status;
}

static uint8_t clampDcrCmdSize(const DSITX_PrivateData* pD, const DSITX_DirectCommandRequest* dcr)
{
    /* Direct Command size limits are described in the Table 31 of User Guide */
    uint8_t size = dcr->cmdSize;

    if ((dcr->type == DSITX_DCR_TYPE_WRITE) && (size > pD->ip.directCmdFifoDepth)) {
        /* CMD size too large. Setting to directCmdFifoDepth */
        size = (uint8_t) pD->ip.directCmdFifoDepth;
    } else if (((dcr->type) == (DSITX_DCR_TYPE_READ)) && (size > 2U)) {
        /* CMD size too large. Setting to 2 */
        size = 2;
    } else {
        /* size was within range - don't modify it */
    }
    return size;
}

static uint32_t sendDirectCmdReadWrite(DSITX_PrivateData* pD, DSITX_DirectCommandRequest* dcr, uint32_t* regVal)
{
    uint32_t status = CDN_EOK;

    dcr->cmdSize = clampDcrCmdSize(pD, dcr);

    uint8_t* ptr = dcr->cmdData;
    uint32_t size = dcr->cmdSize;

    if ((size != 0U) && (ptr == NULL)) {
        /* No command data provided */
        status = CDN_EINVAL;
    }

    if (status == CDN_EOK) {
        /* Set common R/W cmd parameters */
        *regVal = CPS_FLD_WRITE(DSITX__DIRECT_CMD_MAIN_SETTINGS, CMD_HEAD, *regVal, dcr->head);
        *regVal = CPS_FLD_WRITE(DSITX__DIRECT_CMD_MAIN_SETTINGS, CMD_ID, *regVal, dcr->vcId);
        *regVal = CPS_FLD_WRITE(DSITX__DIRECT_CMD_MAIN_SETTINGS, CMD_SIZE, *regVal, dcr->cmdSize);

        /* Reset FIFO write pointer */
        CPS_REG_WRITE(&pD->regBase->direct_cmd_fifo_rst, 1);
        uint32_t data;
        uint8_t index = 0;
        while (size != 0U) {
            data = ReadFromBuff32le(&ptr[index], size);
            CPS_REG_WRITE(&pD->regBase->direct_cmd_wrdat, data);
            index += 4U;
            size -= min(size, (uint32_t) (sizeof(uint32_t)));
        };

        if (dcr->type == DSITX_DCR_TYPE_READ) {
            if (dcr->recData == NULL) {
                /* No buffer for storing data */
                status = CDN_EINVAL;
            } else {
                if (dcr->wait != 0U) {
                    /* Disable read interrupts/events and wait for STS */
                    CPS_REG_WRITE(&pD->regBase->direct_cmd_rd_sts_ctl, 0);
                } else {
                    /* Enable read interrupts/events required by user */
                    CPS_REG_WRITE(&pD->regBase->direct_cmd_rd_sts_ctl, dcr->enRdEvents);
                }
            }
        }
    }
    return status;
}

/* internal function */
static uint32_t sendDirectCmdTrigger(const DSITX_DirectCommandRequest* dcr, uint32_t* regVal)
{
    uint32_t status = CDN_EOK;

    if ((((uint32_t)dcr->triggerValue) & ((uint32_t)dcr->triggerValue - 1U)) != 0U) {
        /* Only one of the Trigger Value bits can be set */
        status = CDN_EINVAL;
    } else {
        *regVal = CPS_FLD_WRITE(DSITX__DIRECT_CMD_MAIN_SETTINGS, TRIGGER_VAL, *regVal, (uint32_t)dcr->triggerValue);
    }
    return status;
}

/* internal function */
static uint32_t sendDirectCmdFinalStatus(DSITX_PrivateData* pD, DSITX_DirectCommandRequest* dcr)
{
    uint32_t status = CDN_EOK;
    uint32_t timeout = DIRECT_CMD_TIMEOUT;

    /* wait for bit DCR_STS_TRANSMISSION */
    do {
        dcr->status = CPS_REG_READ(&pD->regBase->direct_cmd_sts);
        --timeout;
    } while (((dcr->status & (uint32_t)DSITX_DCR_STS_TRANSMISSION) == 1U) && (timeout != 0U));

    pD->processingDcr = false;

    if (timeout != 0U) {
        dcr->ackVal = (uint8_t)CPS_FLD_READ(DSITX__DIRECT_CMD_STS, ACK_VAL, dcr->status);
        /* Remove ACK value from status bits; may be removed in case of performance drop */
        dcr->status = dcr->status & (~DSITX__DIRECT_CMD_STS__ACK_VAL_MASK);
        if (dcr->type == DSITX_DCR_TYPE_READ) {
            status = readDCRData(pD, dcr);
        }
    } else {
        status = CDN_EIO;
    }
    return status;
}

/* internal function */
static uint32_t validateSendDcrPrecndtns(const DSITX_PrivateData* pD, const DSITX_DirectCommandRequest* dcr)
{
    uint32_t status;

    if (pD->processingDcr != 0U) {
        /* Cannot send request before previous completes. */
        status = CDN_EINPROGRESS;
    } else if ((dcr->lpMode == 0U) && ((CPS_FLD_READ(DSITX__MCTL_MAIN_EN, PLL_START, CPS_REG_READ(&pD->regBase->mctl_main_en))) == 0U)) {
        /* HS mode requires enabled PLL, return CDN_EINVAL if PLL is not enabled */
        status = CDN_EINVAL;
    } else {
        status = CDN_EOK;
    }
    return status;
}

/* internal function */
static uint32_t sendDirectCmdCfg(DSITX_PrivateData* pD, DSITX_DirectCommandRequest* dcr)
{
    uint32_t status;

    dcr->status = (uint32_t)DSITX_DIRECT_COMMAND_STATUS_BITS_INIT;
    dcr->rdStatus = (uint32_t)DSITX_DIRECT_COMMAND_READ_STATUS_BITS_INIT;
    pD->dcr = dcr;
    pD->processingDcr = true;

    DSITX_DirectCommandType dcrType = dcr->type;
    DSITX_Regs* regBase = pD->regBase;
    uint32_t regVal = 0;

    /* Clear all status bits by setting up all bits in clr registers to 1. */
    CPS_REG_WRITE(&regBase->direct_cmd_sts_clr, ~DSITX__DIRECT_CMD_STS_CLR_WRITE_MASK);
    CPS_REG_WRITE(&regBase->direct_cmd_rd_sts_clr, ~DSITX__DIRECT_CMD_RD_STS_CLR_WRITE_MASK);

    /* Set common configuration */
    regVal = CPS_FLD_WRITE(DSITX__DIRECT_CMD_MAIN_SETTINGS, CMD_NAT, regVal, (uint32_t)dcrType);
    regVal = CPS_FLD_WRITE(DSITX__DIRECT_CMD_MAIN_SETTINGS, CMD_LP_EN, regVal, boolToVal(dcr->lpMode));
    regVal = CPS_FLD_WRITE(DSITX__DIRECT_CMD_MAIN_SETTINGS, CMD_LONGNOTSHORT, regVal, boolToVal(dcr->longPacket));

    /* for various command types call appropriate function */
    if ((dcrType == DSITX_DCR_TYPE_WRITE) || (dcrType == DSITX_DCR_TYPE_READ)) {
        status = sendDirectCmdReadWrite(pD, dcr, &regVal);
    } else if ((dcrType == DSITX_DCR_TYPE_TRIGGER) != 0U) {
        status = sendDirectCmdTrigger(dcr, &regVal);
    } else {
        /* skip this operation for other types */
        status = CDN_EOK;
    }

    CPS_REG_WRITE(&regBase->direct_cmd_main_settings, regVal);

    return status;
}

/* internal function */
static uint32_t sendDirectCmdIrq(DSITX_PrivateData* pD, DSITX_DirectCommandRequest* dcr)
{
    uint32_t status = CDN_EOK;

    if (dcr->wait != 0U) {
        /* Disable interrupts/events */
        CPS_REG_WRITE(&pD->regBase->direct_cmd_sts_ctl, 0);
    } else {
        /* Enable interrupts/events required by user */
        CPS_REG_WRITE(&pD->regBase->direct_cmd_sts_ctl, dcr->enEvents);
    }

    /* Start Direct Command */
    CPS_REG_WRITE(&pD->regBase->direct_cmd_send, 1);
    if (dcr->wait != 0U) {
        status = sendDirectCmdFinalStatus(pD, dcr);
    }

    return status;
}

/**
 * Sends Direct Command Request. Only one request can be sent at a
 * time. After sending command request user shall not make changes to
 * request structure unless request structure is provided to user in
 * the callback function.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] dcr Pointer to structure containing detailed information about command.
 *    This structure will be updated by Core Driver during command
 *    execution. After passing it to Core Driver user shall not make
 *    any changes to its content until dcr status is set to completed
 *    or it is presented in callback function.
 * @return CDN_EINVAL If pD NULL.
 * @return CDN_EPERM If dcr cannot be sent due to state of the DSITX link (e.g. TVG enabled).
 * @return CDN_EINPROGRESS If processing of other request has not yet been completed.
 * @return CDN_EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SendDirectCmd(DSITX_PrivateData* pD, DSITX_DirectCommandRequest* dcr)
{
    uint32_t status;

    /* check params */
    if (DSITX_SendDirectCmdSF(pD, dcr) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        status = validateSendDcrPrecndtns(pD, dcr);
        /* if dcr is correct set configuration */
        if (status == CDN_EOK) {
            status = sendDirectCmdCfg(pD, dcr);
        }

        /* if set config finished successfully set interrupts */
        if (status == CDN_EOK) {
            status = sendDirectCmdIrq(pD, dcr);
        }
    }

    return status;
}

/**
 * Sets DSITX Link Event Handler function and informs Core Driver
 * which events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which DSITX Link events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when event occurs.
 *    When value of this pointer is set to NULL then all events for
 *    DSITX Link will be disabled and value of the events argument is ignored.
 */
uint32_t DSITX_SetDsiLinkEventHandler(DSITX_PrivateData *pD, uint32_t enabledEvents, DSITX_DsiLinkEventHandler callback)
{
    uint32_t regVal = 0U;
    uint32_t status = CDN_EOK;

    /* check params */
    if (DSITX_SetDsiLinkEventHandlerSF(pD) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        pD->fnDsiLinkCallback = callback;
        pD->enDsiLinkStsBits = enabledEvents;

        if (callback != NULL) {
            /* if callback is provided build new settings */
            regVal = CPS_REG_READ(&pD->regBase->mctl_main_sts_ctl)
                | (enabledEvents & 0x0000FFFFU);
        }
        /* write link event settings to register */
        CPS_REG_WRITE(&pD->regBase->mctl_main_sts_ctl, regVal);
    }
    return status;
}

/**
 * Sets Command Mode Event Handler function and informs Core Driver
 * which events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which Command Mode events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when Command Mode event occurs.
 *    When value of this pointer is set to NULL then all events for
 *    Command Mode will be disabled and value of the events argument is ignored.
 * @return CDN_EINVAL If pD NULL.
 * @return CDN_EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetCmdModeEventHandler(DSITX_PrivateData *pD, uint32_t enabledEvents, DSITX_CmdModeEventHandler callback)
{
    uint32_t regVal = 0U;
    uint32_t status = CDN_EOK;

    /* check params */
    if (DSITX_SetCmdModeEventHandlerSF(pD) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        pD->fnCmdModeCallback = callback;
        pD->enCmdModeStsBits = enabledEvents;

        if (callback != NULL) {
            /* if callback is provided build new settings */
            const uint32_t cmdModeStsCtl = CPS_REG_READ(&pD->regBase->cmd_mode_sts_ctl);
            regVal = cmdModeStsCtl
                | (enabledEvents & 0x0000FFFFU);
        }
        /* write command mode event settings to register */
        CPS_REG_WRITE(&pD->regBase->cmd_mode_sts_ctl, regVal);
    }
    return status;
}

/**
 * Sets Video Mode Event Handler function and informs Core Driver
 * which events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which Video Mode events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when Video Mode event occurs.
 *    When value of this pointer is set to NULL then all events for
 *    Video Mode will be disabled and value of the events argument is ignored.
 * @return CDN_EINVAL If pD NULL.
 * @return CDN_EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetVidModeEventHandler(DSITX_PrivateData *pD, uint32_t enabledEvents, DSITX_VidModeEventHandler callback)
{
    uint32_t regVal = 0U;
    uint32_t status = CDN_EOK;

    /* check params */
    if (DSITX_SetVidModeEventHandlerSF(pD) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        pD->fnVidModeCallback = callback;
        pD->enVidModeStsBits = enabledEvents;

        if (callback != NULL) {
            /* if callback is provided build new settings */
            const uint32_t vidModeStsCtl = CPS_REG_READ(&pD->regBase->vid_mode_sts_ctl);
            regVal = vidModeStsCtl
                | (enabledEvents & 0x0000FFFFU);
        }
        /* write video mode event settings to register */
        CPS_REG_WRITE(&pD->regBase->vid_mode_sts_ctl, regVal);
    }
    return status;
}

/**
 * Sets Test Video Generator Event Handler function and informs Core
 * Driver which events should be reported to the user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which Test Video Generator events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when Test Video Generator event occurs.
 *    When value of this pointer is set to NULL then all events for
 *    Test Video Generator will be disabled and value of events argument is ignored.
 * @return CDN_EINVAL If pD NULL.
 * @return CDN_EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetTvgEventHandler(DSITX_PrivateData *pD, uint32_t enabledEvents, DSITX_TvgEventHandler callback)
{
    uint32_t regVal;
    uint32_t status = CDN_EOK;

    /* check params */
    if (DSITX_SetTvgEventHandlerSF(pD) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        pD->fnTvgCallback = callback;
        pD->enTvgStsBits = enabledEvents;

        /* read current settings */
        regVal = CPS_REG_READ(&pD->regBase->tvg_sts_ctl);

        /* new settings accordingly to callback */
        if (callback != NULL) {
            regVal |= enabledEvents & 0x0000FFFFU;
        } else {
            regVal &= ~(DSITX__TVG_STS_CTL__TVG_STS_EN_MASK | DSITX__TVG_STS_CTL__TVG_STS_EDGE_MASK);
        }
        /* write settings to register */
        CPS_REG_WRITE(&pD->regBase->tvg_sts_ctl, regVal);
    }
    return status;
}

/**
 * Sets DPHY Error Event Handler function and informs Core Driver
 * which events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which DPHY errors should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when DPHY error occurs.
 *    When value of this pointer is set to NULL then all error events for
 *    DPHY will be disabled and value of the events argument is ignored.
 * @return CDN_EINVAL If pD NULL.
 * @return CDN_EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetDphyErrorEventHandler(DSITX_PrivateData *pD, uint32_t enabledEvents, DSITX_DphyErrorEventHandler callback)
{
    uint32_t regVal = 0U;
    uint32_t status = CDN_EOK;

    /* check params */
    if (DSITX_SetDphyErrorEventHandlSF(pD) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        pD->fnDphyErrCallback = callback;
        pD->enDphyErrBits = enabledEvents;

        /* write new settings to registers */
        if (callback == NULL) {
            /* if collback is not given, disable error reporting */
            CPS_REG_WRITE(&pD->regBase->mctl_dphy_err_ctl1, regVal);
            CPS_REG_WRITE(&pD->regBase->mctl_dphy_err_ctl2, regVal);
        } else {
            /* otherwise enable elements */
            const uint32_t mctlDphyErrCtl1 = CPS_REG_READ(&pD->regBase->mctl_dphy_err_ctl1);
            regVal = mctlDphyErrCtl1 | (enabledEvents);
            CPS_REG_WRITE(&pD->regBase->mctl_dphy_err_ctl1, regVal);
        }
    }
    return status;
}

/**
 * Sets DPI Event Handler function and informs Core Driver which
 * events should be reported to user.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] enabledEvents Specifies which DPI events should be reported by Core Driver.
 * @param[in] callback Pointer to function that will be called when DPI interrupt occurs.
 *    When value of this pointer is set to NULL then all events for DPI
 *    will be disabled and value of the events argument is ignored.
 * @return CDN_EINVAL If pD NULL.
 * @return CDN_EOK If Direct Command is accepted and pending execution.
 */
uint32_t DSITX_SetDpiEventHandler(DSITX_PrivateData* pD, uint32_t enabledEvents, DSITX_DpiEventHandler callback)
{
    uint32_t regVal = 0U;
    uint32_t status = CDN_EOK;

    /* check params */
    if (DSITX_SetDpiEventHandlerSF(pD) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        pD->fnDpiCallback = callback;
        pD->enDpiStsBits = enabledEvents;

        /* if callback is given, build register value */
        if (callback != NULL) {
            const uint32_t dpiIrqEn = CPS_REG_READ(&pD->regBase->dpi_irq_en);
            regVal = dpiIrqEn | enabledEvents;
        }

        /* write value to the register */
        CPS_REG_WRITE(&pD->regBase->dpi_irq_en, regVal);
    }
    return status;
}

/**
 * Sets DSITX Test register.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] test Pointer to structure containing control configuration.
 * @return CDN_EINVAL If pD NULL.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_SetTestGeneric(DSITX_PrivateData *pD, DSITX_TestGeneric const *test)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_SetTestGenericSF(pD, test) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* combine structure fields to register */
        regVal = 0;
        regVal = CPS_FLD_WRITE(DSITX__TEST_GENERIC, CTRL, regVal, (uint32_t)test->ctrl);
        /* write register */
        CPS_REG_WRITE(&pD->regBase->test_generic, regVal);
        status = CDN_EOK;
    }
    return status;
}

/**
 * Obtains DSITX Test register value.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] test Pointer to structure to which control configuration will be
 *    written.
 * @return CDN_EINVAL If pD NULL.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_GetTestGeneric(DSITX_PrivateData *pD, DSITX_TestGeneric *test)
{
    uint32_t regVal;
    uint32_t status;

    /* check params */
    if (DSITX_GetTestGenericSF(pD, test) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register */
        regVal = CPS_REG_READ(&pD->regBase->test_generic);

        /* split register value to structure fields */
        test->ctrl = (uint16_t) CPS_FLD_READ(DSITX__TEST_GENERIC, CTRL, regVal);
        test->status = (uint16_t) CPS_FLD_READ(DSITX__TEST_GENERIC, STATUS, regVal);

        status = CDN_EOK;
    }
    return status;
}



/**
 * Sets Video 3D configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[in] cfg Video 3D configuration.
 * @return CDN_EINVAL If pD or value is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_SetVideo3dConfig(DSITX_PrivateData *pD, const DSITX_Video3dConfig *cfg)
{
    uint32_t status = CDN_EOK;
    uint32_t regVal;

    /* check params */
    if ((DSITX_SetVideo3dConfigSF(pD, cfg)) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* build register value from structure fields */
        regVal = CPS_REG_READ(&pD->regBase->mctl_3dvideo_ctl);
        regVal = CPS_FLD_WRITE(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3DMODE, regVal, cfg->vidSync3dMode);
        regVal = CPS_FLD_WRITE(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3DFORMAT, regVal, cfg->vidSync3dFormat);
        regVal = CPS_FLD_WRITE(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3D_SECOND_EN, regVal, boolToVal(cfg->vidVsync3dSecondEnable));
        regVal = CPS_FLD_WRITE(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3D_LR, regVal, cfg->vidVsync3dLr);
        regVal = CPS_FLD_WRITE(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3D_EN, regVal, boolToVal(cfg->vidVsync3dEnable));
        /* write calculated regVal to appropriate register */
        CPS_REG_WRITE(&pD->regBase->mctl_3dvideo_ctl, regVal);
    }
    return status;
}

/**
 * Gets Video 3D configuration.
 * @param[in] pD Driver state info specific to this instance.
 * @param[out] cfg Video 3D configuration.
 * @return CDN_EINVAL If pD or value is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_GetVideo3dConfig(DSITX_PrivateData *pD, DSITX_Video3dConfig *cfg)
{
    uint32_t status = CDN_EOK;

    /* check params */
    if ((DSITX_GetVideo3dConfigSF(pD, cfg)) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register value */
        uint32_t regVal = CPS_REG_READ(&pD->regBase->mctl_3dvideo_ctl);
        /* split value to stucture fields */
        status = getVidSync3dModeEnum(CPS_FLD_READ(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3DMODE, regVal), &cfg->vidSync3dMode);
        status |= getVidVsync3dLrEnum(CPS_FLD_READ(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3D_LR, regVal), &cfg->vidVsync3dLr);
        status |= getVidSync3dFormatEnum(CPS_FLD_READ(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3DFORMAT, regVal), &cfg->vidSync3dFormat);

        cfg->vidVsync3dSecondEnable = valToBool(CPS_FLD_READ(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3D_SECOND_EN , regVal));
        cfg->vidVsync3dEnable = valToBool(CPS_FLD_READ(DSITX__MCTL_3DVIDEO_CTL, VID_VSYNC_3D_EN, regVal));
    }
    return status;
}

/**
 * Retrieves ASF information from DSITX controller.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] asfInfo Pointer to ASF information structure.
 * @return CDN_EINVAL If pD or asfInfo is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DSITX_GetAsfInfo(const DSITX_PrivateData *pD, DSITX_AsfInfo* asfInfo)
{
   uint32_t status = CDN_EOK;

    if (DSITX_GetAsfInfoSF(pD, asfInfo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        asfInfo->regBase = &(pD->regBase->asf_int_status);
    }
   return status;
}

// parasoft-end-suppress METRICS-36-3

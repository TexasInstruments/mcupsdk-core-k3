/******************************************************************************
 * Copyright (C) 2012-2019 Cadence Design Systems, Inc.
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
 * This file contains CSI2TX Core Driver API implementation.
 *
 *****************************************************************************/

#include <drivers/hw_include/csl_csitx.h>
#include "cps_drv.h"
#include "csitx_sanity.h"

static const struct {
    size_t cfg;
    size_t format;
} dtOffsetsArray[16] = {
    [0U].cfg = offsetof(CSITX_Regs, dt0_cfg),
    [0U].format = offsetof(CSITX_Regs, dt0_format),
    [1U].cfg = offsetof(CSITX_Regs, dt1_cfg),
    [1U].format = offsetof(CSITX_Regs, dt1_format),
    [2U].cfg = offsetof(CSITX_Regs, dt2_cfg),
    [2U].format = offsetof(CSITX_Regs, dt2_format),
    [3U].cfg = offsetof(CSITX_Regs, dt3_cfg),
    [3U].format = offsetof(CSITX_Regs, dt3_format),
    [4U].cfg = offsetof(CSITX_Regs, dt4_cfg),
    [4U].format = offsetof(CSITX_Regs, dt4_format),
    [5U].cfg = offsetof(CSITX_Regs, dt5_cfg),
    [5U].format = offsetof(CSITX_Regs, dt5_format),
    [6U].cfg = offsetof(CSITX_Regs, dt6_cfg),
    [6U].format = offsetof(CSITX_Regs, dt6_format),
    [7U].cfg = offsetof(CSITX_Regs, dt7_cfg),
    [7U].format = offsetof(CSITX_Regs, dt7_format),
    [8U].cfg = offsetof(CSITX_Regs, dt8_cfg),
    [8U].format = offsetof(CSITX_Regs, dt8_format),
    [9U].cfg = offsetof(CSITX_Regs, dt9_cfg),
    [9U].format = offsetof(CSITX_Regs, dt9_format),
    [10U].cfg = offsetof(CSITX_Regs, dt10_cfg),
    [10U].format = offsetof(CSITX_Regs, dt10_format),
    [11U].cfg = offsetof(CSITX_Regs, dt11_cfg),
    [11U].format = offsetof(CSITX_Regs, dt11_format),
    [12U].cfg = offsetof(CSITX_Regs, dt12_cfg),
    [12U].format = offsetof(CSITX_Regs, dt12_format),
    [13U].cfg = offsetof(CSITX_Regs, dt13_cfg),
    [13U].format = offsetof(CSITX_Regs, dt13_format),
    [14U].cfg = offsetof(CSITX_Regs, dt14_cfg),
    [14U].format = offsetof(CSITX_Regs, dt14_format),
    [15U].cfg = offsetof(CSITX_Regs, dt15_cfg),
    [15U].format = offsetof(CSITX_Regs, dt15_format)
};

static const size_t vcOffsetsArray[16] = {
    offsetof(CSITX_Regs, vc0_cfg),
    offsetof(CSITX_Regs, vc1_cfg),
    offsetof(CSITX_Regs, vc2_cfg),
    offsetof(CSITX_Regs, vc3_cfg),
    offsetof(CSITX_Regs, vc4_cfg),
    offsetof(CSITX_Regs, vc5_cfg),
    offsetof(CSITX_Regs, vc6_cfg),
    offsetof(CSITX_Regs, vc7_cfg),
    offsetof(CSITX_Regs, vc8_cfg),
    offsetof(CSITX_Regs, vc9_cfg),
    offsetof(CSITX_Regs, vc10_cfg),
    offsetof(CSITX_Regs, vc11_cfg),
    offsetof(CSITX_Regs, vc12_cfg),
    offsetof(CSITX_Regs, vc13_cfg),
    offsetof(CSITX_Regs, vc14_cfg),
    offsetof(CSITX_Regs, vc15_cfg)
};

static const size_t streamOffsetsArray[4] = {
    offsetof(CSITX_Regs, stream_if_0_cfg),
    offsetof(CSITX_Regs, stream_if_1_cfg),
    offsetof(CSITX_Regs, stream_if_2_cfg),
    offsetof(CSITX_Regs, stream_if_3_cfg)
};

/* parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions", DRV-4663 */

/* Returns 1U or 0U depending on a received flag in the type of bool. */
static inline uint32_t boolToVal(bool state) {
    return ((state == true) ? 1U : 0U);
}

/* internal function */
static inline uint32_t* getRegAddress(const CSITX_PrivateData* pD,
                                      size_t                   offset) {
    /* parasoft-begin-suppress MISRA2012-RULE-11_4-4  "Cast pointer to integral and vice-versa, DRV-4381" */
    return ((uint32_t*) (((uintptr_t) ((pD->cfg).regBase)) + offset));
    /* parasoft-end-suppress MISRA2012-RULE-11_4-4 */
}

/* Checks if a given IF is available in the HW */
static uint32_t checkStreamNum(const CSITX_PrivateData* pD, CSITX_IfNumber number) {
    uint32_t result = CDN_EOK;
    if ((uint8_t) (number) >= pD->deviceConfig.numStreams) {
        result = CDN_ENOTSUP;
    }
    return result;
}
/* parasoft-end-suppress METRICS-36-3 */

/* Checks if a given VC is available in the HW */
static uint32_t checkVcNum(const CSITX_PrivateData* pD, CSITX_VcNumber number) {
    uint32_t result = CDN_EOK;
    if ((uint8_t) (number) >= pD->deviceConfig.numVcs) {
        result = CDN_ENOTSUP;
    }
    return result;
}

/* Checks if a given DT is available in the HW */
static uint32_t checkDtNum(const CSITX_PrivateData* pD, CSITX_DtNumber number) {
    uint32_t result = CDN_EOK;
    if ((uint8_t) (number) >= pD->deviceConfig.numDts) {
        result = CDN_ENOTSUP;
    }
    return result;
}

/**
 * Enables or disables interrupts. Note that in order to generate
 * interrupts the IRQ_MASK register must be configured first. If in
 * the driver initialization stage the 'CSITX_Config.enableInterrupts
 * = true', then the IRQ_MASK is configured that all interrupts are
 * generated.
 * @param[in] pD Driver instance data
 * @param[in] enable True to enable interrupts, false to disable
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetInterruptsEnable(CSITX_PrivateData* pD, bool enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_SetInterruptsEnableSF(pD);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        if (enable != 0U) {
            value = CPS_FLD_SET(CSITX__TX_CONF, IRQ_ENABLE, value);
        } else {
            value = CPS_FLD_CLEAR(CSITX__TX_CONF, IRQ_ENABLE, value);
        }
        CPS_REG_WRITE(&pD->cfg.regBase->tx_conf, value);
    }
    return (result);
}

/**
 * Gets value of the interrupts.
 * @param[in] pD Driver instance data
 * @param[out] enable 'irq_enable' bit from the CONFIG register If true interrupts are enabled, false otherwise.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetInterruptsEnable(CSITX_PrivateData* pD, bool *enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_GetInterruptsEnableSF(pD, enable);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        *enable = ((CSITX__TX_CONF__IRQ_ENABLE_MASK & value) != 0U);
    }
    return (result);
}

/**
 * Enables or disables Configuration Request.
 * @param[in] pD Driver instance data
 * @param[in] enable True to enable Configuration Request, false to disable
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetConfigurationMode(CSITX_PrivateData* pD, uint32_t enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_SetConfigurationModeSF(pD);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        value = CPS_FLD_WRITE(CSITX__TX_CONF, CONFIGURATION_REQUEST, value, enable);
        CPS_REG_WRITE(&pD->cfg.regBase->tx_conf, value);
    }
    return (result);
}

/**
 * Gets value of the Configuration request
 * @param[in] pD Driver instance data
 * @param[out] enable 'configuration_request' bit from the CONFIG register is tested. If true Configuration Request is enabled, false otherwise.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetConfigurationMode(CSITX_PrivateData* pD, uint32_t *enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_GetConfigurationModeSF(pD, enable);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        *enable = CPS_FLD_READ(CSITX__TX_CONF, CONFIGURATION_REQUEST, value);
    }
    return (result);
}

/* internal function */
static void setDphyConfigModeLnEnable(const CSITX_DphyConfig *config, uint32_t *value)
{
    uint32_t tmpValue = *value;
    /* prepare register value */
    tmpValue = CPS_FLD_WRITE(CSITX__DPHY_CFG, DPHY_LN_0_ENABLE, tmpValue, boolToVal(config->dphyLn0Enable));
    tmpValue = CPS_FLD_WRITE(CSITX__DPHY_CFG, DPHY_LN_1_ENABLE, tmpValue, boolToVal(config->dphyLn1Enable));
    tmpValue = CPS_FLD_WRITE(CSITX__DPHY_CFG, DPHY_LN_2_ENABLE, tmpValue, boolToVal(config->dphyLn2Enable));
    tmpValue = CPS_FLD_WRITE(CSITX__DPHY_CFG, DPHY_LN_3_ENABLE, tmpValue, boolToVal(config->dphyLn3Enable));
    tmpValue = CPS_FLD_WRITE(CSITX__DPHY_CFG, DPHY_CLK_ENABLE, tmpValue, boolToVal(config->dphyClkEnable));
    *value = tmpValue;
}

/**
 * Performs DPHY configuration
 * @param[in] pD Driver instance data
 * @param[in] config Configuration to applied to DPHY
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetDphyConfig(CSITX_PrivateData* pD, const CSITX_DphyConfig *config)
{
    uint32_t result = CSITX_SetDphyConfigSF(pD, config);

    if (result == CDN_EOK) {
        uint32_t value = CPS_REG_READ(&pD->cfg.regBase->dphy_cfg);
        setDphyConfigModeLnEnable(config, &value);
        /* low reset for each lane */
        value = CPS_FLD_WRITE(CSITX__DPHY_CFG, DPHY_RESET_N, value, boolToVal(config->dphyReset));
        /* D-PHY calibration enable */
        value = CPS_FLD_WRITE(CSITX__DPHY_CFG, DPHY_CAL_ENABLE, value, boolToVal(config->dphyCalEnable));
        /* D-PHY clock mode */
        value = CPS_FLD_WRITE(CSITX__DPHY_CFG, DPHY_CLOCK_MODE, value, config->dphyClockMode);
        /* D-PHY mode */
        value = CPS_FLD_WRITE(CSITX__DPHY_CFG, DPHY_MODE, value, config->dphyMode);
        CPS_REG_WRITE(&pD->cfg.regBase->dphy_cfg, value);
    }
    return result;
}

/* internal function */
static void getDphyConfigEnable(CSITX_DphyConfig *config, uint32_t value)
{
    /* check values for each lane */
    config->dphyLn0Enable = (CPS_FLD_READ(CSITX__DPHY_CFG, DPHY_LN_0_ENABLE, value) != 0U);
    config->dphyLn1Enable = (CPS_FLD_READ(CSITX__DPHY_CFG, DPHY_LN_1_ENABLE, value) != 0U);
    config->dphyLn2Enable = (CPS_FLD_READ(CSITX__DPHY_CFG, DPHY_LN_2_ENABLE, value) != 0U);
    config->dphyLn3Enable = (CPS_FLD_READ(CSITX__DPHY_CFG, DPHY_LN_3_ENABLE, value) != 0U);
    config->dphyClkEnable = (CPS_FLD_READ(CSITX__DPHY_CFG, DPHY_CLK_ENABLE, value) != 0U);
}

/**
 * Reads the DPHY configuration
 * @param[in] pD Driver instance data
 * @param[out] config DPHY config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDphyConfig(CSITX_PrivateData* pD, CSITX_DphyConfig *config)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_GetDphyConfigSF(pD, config);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->dphy_cfg);

        getDphyConfigEnable(config, value);
        config->dphyReset = (CPS_FLD_READ(CSITX__DPHY_CFG, DPHY_RESET_N, value) != 0U);
        config->dphyMode = (uint8_t) CPS_FLD_READ(CSITX__DPHY_CFG, DPHY_MODE, value);
        config->dphyClockMode = (uint8_t) CPS_FLD_READ(CSITX__DPHY_CFG, DPHY_CLOCK_MODE, value);
        config->dphyCalEnable = (CPS_FLD_READ(CSITX__DPHY_CFG, DPHY_CAL_ENABLE, value) != 0U);
    }
    return result;
}

/* internal function */
static uint32_t setDphyCfg1ForceStopMode(const CSITX_DphyConfig1 *config,
                                         uint32_t                 value)
{
    uint32_t val = value;
    /* prepare register value */
    val = CPS_FLD_WRITE(CSITX__DPHY_CFG1, FORCE_STOP_MODE_LN_0, val, boolToVal(config->forceStopModeLn0));
    val = CPS_FLD_WRITE(CSITX__DPHY_CFG1, FORCE_STOP_MODE_LN_1, val, boolToVal(config->forceStopModeLn1));
    val = CPS_FLD_WRITE(CSITX__DPHY_CFG1, FORCE_STOP_MODE_LN_2, val, boolToVal(config->forceStopModeLn2));
    val = CPS_FLD_WRITE(CSITX__DPHY_CFG1, FORCE_STOP_MODE_LN_3, val, boolToVal(config->forceStopModeLn3));
    return val;
}

/* internal function */
static uint32_t setDphyCfg1DiffInvert(const CSITX_DphyConfig1 *config,
                                      uint32_t                 value)
{
    uint32_t val = value;
    /* prepare register value */
    val = CPS_FLD_WRITE(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_LN_0, val, boolToVal(config->diffInvertLn0));
    val = CPS_FLD_WRITE(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_LN_1, val, boolToVal(config->diffInvertLn1));
    val = CPS_FLD_WRITE(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_LN_2, val, boolToVal(config->diffInvertLn2));
    val = CPS_FLD_WRITE(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_LN_3, val, boolToVal(config->diffInvertLn3));
    val = CPS_FLD_WRITE(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_C, val, boolToVal(config->diffInvertClock));
    return val;
}

/**
 * Performs DPHY configuration (DPHY CFG1)
 * @param[in] pD Driver instance data
 * @param[in] config Configuration to applied to DPHY CFG1
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetDphyConfig1(CSITX_PrivateData* pD, const CSITX_DphyConfig1 *config)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_SetDphyConfig1SF(pD, config);

    if (result == CDN_EOK) {
        value = setDphyCfg1ForceStopMode(config, value);
        value = setDphyCfg1DiffInvert(config, value);
        CPS_REG_WRITE(&pD->cfg.regBase->dphy_cfg1, value);
    }
    return result;
}

/* internal function */
static void getDphyCfg1ForceStopMode(CSITX_DphyConfig1 *config, uint32_t value)
{
    /* set the structure fields from a value */
    config->forceStopModeLn0 = (CPS_FLD_READ(CSITX__DPHY_CFG1, FORCE_STOP_MODE_LN_0, value) != 0U);
    config->forceStopModeLn1 = (CPS_FLD_READ(CSITX__DPHY_CFG1, FORCE_STOP_MODE_LN_1, value) != 0U);
    config->forceStopModeLn2 = (CPS_FLD_READ(CSITX__DPHY_CFG1, FORCE_STOP_MODE_LN_2, value) != 0U);
    config->forceStopModeLn3 = (CPS_FLD_READ(CSITX__DPHY_CFG1, FORCE_STOP_MODE_LN_3, value) != 0U);
}

/* internal function */
static void getDphyCfg1DiffInvert(CSITX_DphyConfig1 *config, uint32_t value) {
    /* set the structure fields from a value */
    config->diffInvertLn0 = (CPS_FLD_READ(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_LN_0, value) != 0U);
    config->diffInvertLn1 = (CPS_FLD_READ(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_LN_1, value) != 0U);
    config->diffInvertLn2 = (CPS_FLD_READ(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_LN_2, value) != 0U);
    config->diffInvertLn3 = (CPS_FLD_READ(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_LN_3, value) != 0U);
    config->diffInvertClock = (CPS_FLD_READ(CSITX__DPHY_CFG1, DPHY_DIFF_INVERT_C, value) != 0U);
}

/**
 * Reads DPHY configuration (DPHY CFG1)
 * @param[in] pD Driver instance data
 * @param[out] config DPHY CFG1 config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDphyConfig1(CSITX_PrivateData* pD, CSITX_DphyConfig1 *config)
{

    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_GetDphyConfig1SF(pD, config);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->dphy_cfg1);
        getDphyCfg1ForceStopMode(config, value);
        getDphyCfg1DiffInvert(config, value);
    }
    return result;
}

/**
 * Writes a virtual channel configuration.
 * @param[in] pD Driver instance data
 * @param[in] config Virtual channel configuration
 * @param[in] number Number of the Virtual channel to configure
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetVirtualChannelConfig(const CSITX_PrivateData* pD, const CSITX_VirtualChannelConfig* config, CSITX_VcNumber number)
{
    uint32_t cfg = 0U;
    /* check params */
    uint32_t result = CSITX_SetVirtualChannelConfiSF(pD, config, number);

    if (result == CDN_EOK) {
        result = checkVcNum(pD, number);
    }
    if (result == CDN_EOK) {
        cfg = CPS_FLD_WRITE(CSITX__VC0_CFG, VC_0_FRAME_COUNT_EN, cfg, config->frameCountEnable);
        cfg = CPS_FLD_WRITE(CSITX__VC0_CFG, VC_0_MAX_FRAME_NUMBER, cfg, config->maxFrameNumber);
        CPS_REG_WRITE(getRegAddress(pD, vcOffsetsArray[number]), cfg);
    }
    return result;
}

/**
 * Reads a virtual channel configuration.
 * @param[in] pD Driver instance data
 * @param[out] config Virtual channel configuration
 * @param[in] number Number of the virtual channel
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_GetVirtualChannelConfig(const CSITX_PrivateData* pD, CSITX_VirtualChannelConfig* config, CSITX_VcNumber number)
{
    uint32_t cfg = 0U;
    /* check params */
    uint32_t result = CSITX_GetVirtualChannelConfiSF(pD, config, number);

    if (result == CDN_EOK) {
        result = checkVcNum(pD, number);
    }
    if (result == CDN_EOK) {
        cfg = CPS_REG_READ(getRegAddress(pD, vcOffsetsArray[number]));
        config->frameCountEnable = CPS_FLD_READ(CSITX__VC0_CFG, VC_0_FRAME_COUNT_EN, cfg);
        config->maxFrameNumber = (uint16_t) CPS_FLD_READ(CSITX__VC0_CFG, VC_0_MAX_FRAME_NUMBER, cfg);
    }
    return result;
}

/**
 * Writes a stream configuration.
 * @param[in] pD Driver instance data
 * @param[in] config Stream fill level value
 * @param[in] number Pixel interface number
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetStreamConfig(const CSITX_PrivateData* pD, const CSITX_StreamConfig *config, CSITX_IfNumber number)
{
    uint32_t stream_cfg = 0U;
    /* check params */
    uint32_t result = CSITX_SetStreamConfigSF(pD, config, number);

    if (result == CDN_EOK) {
        result = checkStreamNum(pD, number);
    }
    if (result == CDN_EOK) {
        if (((uint32_t)number == (uint32_t)CSITX_PIXEL_IF0) && (config->slaveMode != 0U)) {
            result = CDN_EINVAL;
        } else {
            stream_cfg = CPS_FLD_WRITE(CSITX__STREAM_IF_0_CFG, STREAM_IF_0_FILL_LEVEL, stream_cfg, config->fillLevel);
            /* stream 0 doesn't support slaveMode */
            if ((uint32_t)number != (uint32_t)CSITX_PIXEL_IF0) {
                stream_cfg = CPS_FLD_WRITE(CSITX__STREAM_IF_1_CFG, STREAM_IF_1_SLAVE_MODE, stream_cfg, config->slaveMode);
            }
            CPS_REG_WRITE(getRegAddress(pD, streamOffsetsArray[number]), stream_cfg);
        }
    }
    return result;
}

/**
 * Reads a stream configuration.
 * @param[in] pD Driver instance data
 * @param[out] config Stream fill level value
 * @param[in] number Pixel interface number
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_GetStreamConfig(const CSITX_PrivateData* pD,
                               CSITX_StreamConfig *config, CSITX_IfNumber number)
{
    uint32_t stream_cfg = 0U;
    /* check params */
    uint32_t result = CSITX_GetStreamConfigSF(pD, config, number);

    if (result == CDN_EOK) {
        result = checkStreamNum(pD, number);
    }
    if (result == CDN_EOK) {
        stream_cfg = CPS_REG_READ(getRegAddress(pD, streamOffsetsArray[number]));
        config->fillLevel = (uint16_t) CPS_FLD_READ(CSITX__STREAM_IF_0_CFG, STREAM_IF_0_FILL_LEVEL, stream_cfg);
        config->slaveMode = CPS_FLD_READ(CSITX__STREAM_IF_1_CFG, STREAM_IF_1_SLAVE_MODE, stream_cfg);
    }
    return (result);
}

/**
 * Writes a data type configuration.
 * @param[in] pD Driver instance data
 * @param[in] config Data type configuration
 * @param[in] number Number of the Data type to configure
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetDataTypeConfig(const CSITX_PrivateData* pD,
                                 const CSITX_DataTypeConfig* config, CSITX_DtNumber number)
{
    uint32_t dt_cfg = 0U;
    uint32_t dt_format = 0U;

    /* check params */
    uint32_t result = (uint32_t)CSITX_SetDataTypeConfigSF(pD, config, number);

    if (result == CDN_EOK) {
        result = checkDtNum(pD, number);
    }
    if (result == CDN_EOK) {
        /* build fields values */
        dt_cfg = CPS_FLD_WRITE(CSITX__DT0_CFG, DT_0_LINE_COUNT_EN, dt_cfg, config->lineCountEnable);
        dt_cfg = CPS_FLD_WRITE(CSITX__DT0_CFG, DT_0_LSLE_GENERATION_EN, dt_cfg, config->lineStartEndEnable);
        dt_cfg = CPS_FLD_WRITE(CSITX__DT0_CFG, DT_0_DATA_TYPE, dt_cfg, config->dataType);
        dt_cfg = CPS_FLD_WRITE(CSITX__DT0_CFG, DT_0_EXTD_DATA_TYPE, dt_cfg, config->extendedDataType);

        dt_format = CPS_FLD_WRITE(CSITX__DT0_FORMAT, DT_0_MAX_LINE_NUMBER, dt_format, config->maxLineNumber);
        dt_format = CPS_FLD_WRITE(CSITX__DT0_FORMAT, DT_0_BYTES_LINE_NUMBER, dt_format, config->bytesPerLine);

        /* write registers */
        CPS_REG_WRITE(getRegAddress(pD, dtOffsetsArray[number].cfg), dt_cfg);
        CPS_REG_WRITE(getRegAddress(pD, dtOffsetsArray[number].format), dt_format);
    }
    return result;
}

/**
 * Reads a data type configuration.
 * @param[in] pD Driver instance data
 * @param[out] config Data type configuration
 * @param[in] number Number of the data type
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_GetDataTypeConfig(const CSITX_PrivateData* pD, CSITX_DataTypeConfig* config, CSITX_DtNumber number)
{
    uint32_t dt_cfg = 0U;
    uint32_t dt_format = 0U;

    /* check params */
    uint32_t result = (uint32_t)CSITX_GetDataTypeConfigSF(pD, config, number);

    if (result == CDN_EOK) {
        result = checkDtNum(pD, number);
    }
    if (result == CDN_EOK) {
        /* read registers */
        dt_cfg = CPS_REG_READ(getRegAddress(pD, dtOffsetsArray[number].cfg));
        dt_format = CPS_REG_READ(getRegAddress(pD, dtOffsetsArray[number].format));

        /* extract fields */
        config->lineCountEnable = CPS_FLD_READ(CSITX__DT0_CFG, DT_0_LINE_COUNT_EN, dt_cfg);
        config->lineStartEndEnable = CPS_FLD_READ(CSITX__DT0_CFG, DT_0_LSLE_GENERATION_EN, dt_cfg);
        config->dataType =  (uint8_t) CPS_FLD_READ(CSITX__DT0_CFG, DT_0_DATA_TYPE, dt_cfg);
        config->extendedDataType = CPS_FLD_READ(CSITX__DT0_CFG, DT_0_EXTD_DATA_TYPE, dt_cfg);

        config->maxLineNumber = (uint16_t) CPS_FLD_READ(CSITX__DT0_FORMAT, DT_0_MAX_LINE_NUMBER, dt_format);
        config->bytesPerLine = (uint16_t) CPS_FLD_READ(CSITX__DT0_FORMAT, DT_0_BYTES_LINE_NUMBER, dt_format);
    }
    return result;
}

/**
 * Enables or disables Bypass Mode request.
 * @param[in] pD Driver instance data
 * @param[in] enable True to enable Bypass mode, false to disable
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetBypassModeEnable(CSITX_PrivateData* pD, bool enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = (uint32_t)CSITX_SetBypassModeEnableSF(pD);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        if (enable != 0U) {
            value = CPS_FLD_SET(CSITX__TX_CONF, BYPASS_MODE_ENABLE, value);
        } else {
            value = CPS_FLD_CLEAR(CSITX__TX_CONF, BYPASS_MODE_ENABLE, value);
        }
        CPS_REG_WRITE(&pD->cfg.regBase->tx_conf, value);
    }
    return (result);
}

/**
 * Gets value of the Bypass Mode Enable request.
 * @param[in] pD Driver instance data
 * @param[out] enable 'bypass_mode_enable' bit from the CONFIG register is tested. If true Bypass Mode Enable is enabled, false otherwise.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetBypassModeEnable(CSITX_PrivateData* pD, bool *enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = (uint32_t)CSITX_GetBypassModeEnableSF(pD, enable);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        *enable = ((CSITX__TX_CONF__BYPASS_MODE_ENABLE_MASK & value) != 0U);
    }
    return (result);
}

/**
 * Enables or disables soft reset request.
 * @param[in] pD Driver instance data
 * @param[in] enable True to enable soft reset request false to disable
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetSoftResetRequest(CSITX_PrivateData* pD, bool enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_SetSoftResetRequestSF(pD);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        if (enable != 0U) {
            value = CPS_FLD_SET(CSITX__TX_CONF, SOFT_RESET_REQUEST, value);
        } else {
            value = CPS_FLD_CLEAR(CSITX__TX_CONF, SOFT_RESET_REQUEST, value);
        }
        CPS_REG_WRITE(&pD->cfg.regBase->tx_conf, value);
    }
    return result;
}

/**
 * Gets value of the soft reset request.
 * @param[in] pD Driver instance data
 * @param[out] enable 'soft_reset_request' bit from the CONFIG register is tested. If true soft reset request is enabled, false otherwise.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetSoftResetRequest(CSITX_PrivateData* pD, bool *enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_GetSoftResetRequestSF(pD, enable);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        *enable = ((CSITX__TX_CONF__SOFT_RESET_REQUEST_MASK & value) != 0U);
    }
    return result;
}

/**
 * Enables or disables Scrambler mode
 * @param[in] pD Driver instance data
 * @param[in] enable True to enable scrambler mode, false to disable
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetScramblerMode(CSITX_PrivateData* pD, bool enable) {
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_SetScramblerModeSF(pD);

    if (result == CDN_EOK) {
        if (pD->deviceConfig.scramblerPresent != 0U) {
            value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
            value = CPS_FLD_WRITE(CSITX__TX_CONF, SCRAMBLER_ENABLE, value, boolToVal(enable));
            CPS_REG_WRITE(&pD->cfg.regBase->tx_conf, value);
        } else {
            result = CDN_ENOTSUP;
        }
    }
    return result;
}

/**
 * Gets value of the scrambler mode.
 * @param[in] pD Driver instance data
 * @param[out] scrambler mode status
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetScramblerMode(CSITX_PrivateData* pD, bool *enable) {
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_GetScramblerModeSF(pD, enable);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        *enable = ((CSITX__TX_CONF__SCRAMBLER_ENABLE_MASK & value) != 0U);
    }
    return result;
}

/**
 * Set CSIRX compatibility features.
 * @param[in] pD Driver instance data
 * @param[out] config CSIRX compatibility configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetRxCompatibility(CSITX_PrivateData* pD, CSITX_RxCompatibilityConfig *config) {
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_GetRxCompatibilitySF(pD, config);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
        config->rxCompEnable = ((CSITX__TX_CONF__RX_COMP_ENABLE_MASK & value) != 0U);
        config->rxMapping = ((CSITX__TX_CONF__RX_V1_3_MAPPING_MASK & value) != 0U);
    }
    return result;
}

/**
 * Set CSIRX compatibility features.
 * @param[in] pD Driver instance data
 * @param[out] config CSIRX compatibility configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetRxCompatibility(CSITX_PrivateData* pD, CSITX_RxCompatibilityConfig *config) {
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_SetRxCompatibilitySF(pD, config);

    if (result == CDN_EOK) {
        if (pD->deviceConfig.rxCompatibilityMode != 0U) {
            value = CPS_REG_READ(&pD->cfg.regBase->tx_conf);
            value = CPS_FLD_WRITE(CSITX__TX_CONF, RX_COMP_ENABLE, value, boolToVal(config->rxCompEnable));
            value = CPS_FLD_WRITE(CSITX__TX_CONF, RX_V1_3_MAPPING, value, boolToVal(config->rxMapping));
            CPS_REG_WRITE(&pD->cfg.regBase->tx_conf, value);
        } else {
            result = CDN_ENOTSUP;
        }
    }
    return result;
}

/**
 * Reads STATUS register value.
 * @param[in] pD Driver instance data
 * @param[out] value Contents of the STATUS register
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetStatusRegister(CSITX_PrivateData* pD, uint32_t *value)
{
    /* check params */
    uint32_t result = CSITX_GetStatusRegisterSF(pD, value);

    if (result == CDN_EOK) {
        *value = CPS_REG_READ(&pD->cfg.regBase->status);
    }
    return (result);
}

/**
 * Reads STATUS register value.
 * @param[in] pD Driver instance data
 * @param[out] value Contents of the DPHY_STATUS register
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDphyStatusRegister(CSITX_PrivateData* pD, uint32_t *value)
{
    /* check params */
    uint32_t result = CSITX_GetDphyStatusRegisterSF(pD, value);

    if (result == CDN_EOK) {
        *value = CPS_REG_READ(&pD->cfg.regBase->dphy_status);
    }
    return (result);
}

/**
 * Sets test_generic_ctrl field of the GENERIC Register
 * @param[in] pD Driver instance data
 * @param[in] value Test generic_ctrl value
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid parameter
 */
uint32_t CSITX_SetTestGenericCtrl(CSITX_PrivateData* pD, uint16_t value)
{
    /* check params */
    uint32_t result = CSITX_SetTestGenericCtrlSF(pD);
    uint32_t tmp = 0U;

    if (result == CDN_EOK) {
        tmp = CPS_FLD_WRITE(CSITX__TEST_GENERIC_CTRL, CTRL, tmp, value);
        CPS_REG_WRITE(&pD->cfg.regBase->test_generic_ctrl, tmp);
    }
    return (result);
}

/**
 * Gets test_generic_ctrl field of the TEST_GENERIC Register
 * @param[in] pD Driver instance data
 * @param[out] value DPHY config
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetTestGenericCtrl(CSITX_PrivateData* pD, uint16_t *value)
{
    /* check params */
    uint32_t result = CSITX_GetTestGenericCtrlSF(pD, value);
    uint32_t tmp = 0U;

    if (result == CDN_EOK) {
        tmp = CPS_REG_READ(&pD->cfg.regBase->test_generic_ctrl);
        *value = (uint16_t) CPS_FLD_READ(CSITX__TEST_GENERIC_CTRL, CTRL, tmp);
    }
    return (result);
}

/**
 * Reads test_generic_status field of the TEST_GENERIC register
 * @param[in] pD Driver instance data
 * @param[out] value Contents of the test_generic_status field
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetTestGenericStatus(CSITX_PrivateData* pD, uint16_t *value)
{
    /* check params */
    uint32_t result = CSITX_GetTestGenericStatusSF(pD, value);
    uint32_t tmp = 0U;

    if (result == CDN_EOK) {
        tmp = CPS_REG_READ(&pD->cfg.regBase->test_generic_status);
        *value = (uint16_t) CPS_FLD_READ(CSITX__TEST_GENERIC_STATUS, STATUS, tmp);
    }
    return (result);
}

/* ADD COMMENT */
uint32_t CSITX_SetRegWaitBurstTime(CSITX_PrivateData* pD, CSITX_WaitBurstTimeConfig* config)
{
    /* check params */
    uint32_t result = CSITX_SetRegWaitBurstTimeSF(pD, config);

    if (result == CDN_EOK) {
        uint32_t regValue = CPS_REG_READ(&pD->cfg.regBase->wait_burst_time);
        regValue = CPS_FLD_WRITE(CSITX__WAIT_BURST_TIME, TX_CLOCK_EXIT_TIME, regValue, config->txClockExitTime);
        regValue = CPS_FLD_WRITE(CSITX__WAIT_BURST_TIME, WAIT_BURST_TIME_CNT, regValue, config->waitBurstTimeCnt);
        CPS_REG_WRITE(&pD->cfg.regBase->wait_burst_time, regValue);
    }
    return (result);
}

/**
 * Reads DPHY Wait Time Configuration.
 * @param[in] pD Driver instance data.
 * @param[out] config DPHY Wait Time Configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetRegWaitBurstTime(CSITX_PrivateData* pD, CSITX_WaitBurstTimeConfig* config)
{
    /* check params */
    uint32_t result = CSITX_GetRegWaitBurstTimeSF(pD, config);

    if (result == CDN_EOK) {
        uint32_t regValue = CPS_REG_READ(&pD->cfg.regBase->wait_burst_time);
        config->txClockExitTime = (uint8_t) CPS_FLD_READ(CSITX__WAIT_BURST_TIME, TX_CLOCK_EXIT_TIME, regValue);
        config->waitBurstTimeCnt = (uint8_t) CPS_FLD_READ(CSITX__WAIT_BURST_TIME, WAIT_BURST_TIME_CNT, regValue);
    }
    return (result);
}

/**
 * Writes DPHY Wait Time Configuration.
 * @param[in] pD Driver instance data.
 * @param[in] config DPHY Wait Time Configuration.
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetDphyClkWakeup(CSITX_PrivateData* pD, uint16_t value)
{
    /* check params */
    uint32_t result = CSITX_SetDphyClkWakeupSF(pD);

    if (result == CDN_EOK) {
        CPS_REG_WRITE(&pD->cfg.regBase->dphy_clk_wakeup, value);
    }
    return (result);
}

/**
 * Reads DPHY_CLK_WAKEUP register value.
 * @param[in] pD Driver instance data
 * @param[out] value Contents of the DPHY_CLK_WAKEUP register
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDphyClkWakeup(CSITX_PrivateData* pD, uint16_t *value)
{
    /* check params */
    uint32_t result = CSITX_GetDphyClkWakeupSF(pD, value);

    if (result == CDN_EOK) {
        *value = (uint16_t)(CPS_REG_READ(&pD->cfg.regBase->dphy_clk_wakeup));
    }
    return (result);
}

/**
 * Writes DPHY_ULPS_WAKEUP register with value.
 * @param[in] pD Driver instance data
 * @param[in] value Value to write to the DPHY_ULPS_WAKEUP register
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetDphyUlpsWakeup(CSITX_PrivateData* pD, uint16_t value)
{
    /* check params */
    uint32_t result = CSITX_SetDphyUlpsWakeupSF(pD);

    if (result == CDN_EOK) {
        CPS_REG_WRITE(&pD->cfg.regBase->dphy_ulps_wakeup, value);
    }
    return (result);
}

/**
 * Reads DPHY_ULPS_WAKEUP register value.
 * @param[in] pD Driver instance data
 * @param[out] value Contents of the DPHY_ULPS_WAKEUP register
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDphyUlpsWakeup(CSITX_PrivateData* pD, uint16_t *value)
{
    /* check params */
    uint32_t result = CSITX_GetDphyUlpsWakeupSF(pD, value);

    if (result == CDN_EOK) {
        *value = (uint16_t)(CPS_REG_READ(&pD->cfg.regBase->dphy_ulps_wakeup));
    }
    return (result);
}

/**
 * Enables or disables CSITX debugging functionality.
 * @param[in] pD Driver instance data
 * @param[in] enable True to enable debugging functionality, false to disable
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetDebugEnable(CSITX_PrivateData* pD, bool enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_SetDebugEnableSF(pD);

    if (result == CDN_EOK) {
        if (enable != 0U) {
            value = CPS_FLD_SET(CSITX__DEBUG_CFG, DBG_EN, value);
        } else {
            value = CPS_FLD_CLEAR(CSITX__DEBUG_CFG, DBG_EN, value);
        }
        CPS_REG_WRITE(&pD->cfg.regBase->debug_cfg, value);
    }
    return (result);
}

/**
 * Reads status of the core debug functionality.
 * @param[in] pD Driver instance data
 * @param[out] enable True if the the core debug functionality is enabled false otherwise
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugEnable(CSITX_PrivateData* pD, bool *enable)
{
    uint32_t value = 0U;
    /* check params */
    uint32_t result = CSITX_GetDebugEnableSF(pD, enable);

    if (result == CDN_EOK) {
        value = CPS_REG_READ(&pD->cfg.regBase->debug_cfg);
        *enable = (CPS_FLD_READ(CSITX__DEBUG_CFG, DBG_EN, value) != 0U);
    }
    return (result);
}

/**
 * Reads debug register for a given Pixel pixel interface.
 * @param[in] pD Driver instance data
 * @param[out] value Contents of the DEBUG_PROT_FSM register
 * @param[in] number Number of the Pixel interface
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugProtFsm(CSITX_PrivateData* pD, uint32_t *value, CSITX_IfNumber number)
{
    const struct {
        size_t cfg;
    } debugProtFsmOffsetsArray[4U] = {
        [0U].cfg = offsetof(CSITX_Regs, debug_prot0_fsm),
        [1U].cfg = offsetof(CSITX_Regs, debug_prot1_fsm),
        [2U].cfg = offsetof(CSITX_Regs, debug_prot2_fsm),
        [3U].cfg = offsetof(CSITX_Regs, debug_prot3_fsm),
    };

    /* check params */
    uint32_t result = CSITX_GetDebugProtFsmSF(pD, value, number);

    if (result == CDN_EOK) {
        result = checkStreamNum(pD, number);
    }
    if (result == CDN_EOK) {
        *value = CPS_REG_READ(getRegAddress(pD, debugProtFsmOffsetsArray[number].cfg));
    }
    return result;
}

/**
 * Reads DEBUG_LN_FSM register register value.
 * @param[in] pD Driver instance data
 * @param[out] value Contents of the DEBUG_LN_FSM register
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugLnFsm(CSITX_PrivateData* pD, uint32_t *value)
{
    /* check params */
    uint32_t result = CSITX_GetDebugLnFsmSF(pD, value);

    if (result == CDN_EOK) {
        *value = CPS_REG_READ(&pD->cfg.regBase->debug_ln_fsm);
    }
    return (result);
}

/**
 * Reads DEBUG_CLK_LN_FSM register register value.
 * @param[in] pD Driver instance data
 * @param[out] value Contents of the DEBUG_CLK_LN_FSM register
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugClkLnFsm(CSITX_PrivateData* pD, uint32_t *value)
{
    /* check params */
    uint32_t result = CSITX_GetDebugClkLnFsmSF(pD, value);

    if (result == CDN_EOK) {
        *value = CPS_REG_READ(&pD->cfg.regBase->debug_clk_ln_fsm);
    }
    return (result);
}

/**
 * Reads DEBUG_DATA_LN_FSM register register value.
 * @param[in] pD Driver instance data
 * @param[out] value Contents of the DEBUG_DATA_LN_FSM register
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetDebugDataLnFsm(CSITX_PrivateData* pD, uint32_t *value)
{
    /* check params */
    uint32_t result = CSITX_GetDebugDataLnFsmSF(pD, value);

    if (result == CDN_EOK) {
        *value = CPS_REG_READ(&pD->cfg.regBase->debug_data_ln_fsm);
    }
    return (result);
}

/**
 * Writes EPD configuration.
 * @param[in] pD Driver instance data
 * @param[in] config EPD configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_SetEpdConfig(CSITX_PrivateData* pD, const CSITX_EpdConfig *config) {
    /* check params */
    uint32_t result = CSITX_SetEpdConfigSF(pD, config);

    if (result == CDN_EOK) {
        uint32_t value = CPS_REG_READ(&pD->cfg.regBase->epd_en_ssp);
        value = CPS_FLD_WRITE(CSITX__EPD_EN_SSP, EPD_SP_SPACERS, value, config->spSpacers);
        value = CPS_FLD_WRITE(CSITX__EPD_EN_SSP, EPD_ENABLE, value, config->enable);
        CPS_REG_WRITE(&pD->cfg.regBase->epd_en_ssp, value);

        value = CPS_REG_READ(&pD->cfg.regBase->epd_op_slp);
        value = CPS_FLD_WRITE(CSITX__EPD_OP_SLP, EPD_LP_SPACERS, value, config->lpSpacers);
        value = CPS_FLD_WRITE(CSITX__EPD_OP_SLP, EPD_OPTION, value, config->option);
        CPS_REG_WRITE(&pD->cfg.regBase->epd_op_slp, value);
    }
    return result;
}

/**
 * Reads EPD configuration.
 * @param[in] pD Driver instance data
 * @param[out] config EPD configuration
 * @return CDN_EOK on success
 * @return CDN_EINVAL for invalid pointer
 */
uint32_t CSITX_GetEpdConfig(CSITX_PrivateData* pD, CSITX_EpdConfig *config) {
    /* check params */
    uint32_t result = CSITX_GetEpdConfigSF(pD, config);

    if (result == CDN_EOK) {
        uint32_t value = CPS_REG_READ(&pD->cfg.regBase->epd_en_ssp);
        config->spSpacers = (uint16_t) CPS_FLD_READ(CSITX__EPD_EN_SSP, EPD_SP_SPACERS, value);
        config->enable = CPS_FLD_READ(CSITX__EPD_EN_SSP, EPD_ENABLE, value);

        value = CPS_REG_READ(&pD->cfg.regBase->epd_op_slp);
        config->lpSpacers = (uint16_t) CPS_FLD_READ(CSITX__EPD_OP_SLP, EPD_LP_SPACERS, value);
        config->option = CPS_FLD_READ(CSITX__EPD_OP_SLP, EPD_OPTION, value);
    }
    return result;
}

/* internal function */
static uint32_t checkMagicNumber(const CSITX_Config *config) {
    uint32_t result = CDN_EOK;
    uint32_t volatile *idRegAddr = &((CSITX_Regs volatile*)config->regBase)->id_prod_ver;
    uint32_t magicNumber = CPS_REG_READ(idRegAddr);

    if (magicNumber != CSITX_MAGIC_NUMBER) {
        result = CDN_ENOTSUP;
    }
    return result;
}

/**
 * Get the driver's memory requirements to support the given
 * configuration.
 * @param[in] config Driver/hardware configuration required
 * @param[out] memReq Returns the size of memory allocations required
 * @return CDN_EOK on success (requirements struct filled).
 * @return CDN_ENOTSUP if magic number does not match.
 * @return CDN_EINVAL if config or memReq is NULL.
 */
uint32_t CSITX_Probe(const CSITX_Config *config, CSITX_SysReq *memReq)
{
    uint32_t result = CDN_EOK;

    /* check params */
    result = CSITX_ProbeSF(config, memReq);
    if (result == CDN_EOK) {
        result = checkMagicNumber(config);
        /* check magic number correctness */
        if (result == CDN_EOK) {
            memReq->privDataSize = (uint32_t) sizeof(CSITX_PrivateData);
        }
    }
    return result;
}

/**
 * Initialise the driver instance and state, configure the CSITX as
 * specified in the 'config' settings. The function enables the
 * datapath.
 * @param[in] pD Driver state info specific to this instance
 * @param[in] config Specifies driver/hardware configuration
 * @param[in] callbacks Client-supplied callback functions
 * @return CDN_EOK on success.
 * @return CDN_EINVAL if illegal/inconsistent values in 'config' doesn't support feature(s) required by 'config' parameters.
 */
uint32_t CSITX_Init(CSITX_PrivateData* pD, const CSITX_Config *config, const CSITX_Callbacks *callbacks)
{
    /* check params */
    uint32_t result = CSITX_InitSF(pD, config, callbacks);

    if (result == CDN_EOK) {

        /* Copy config & callbacks into private data */
        pD->cfg = *config;
        /* Copy callbacks with checking */
        if (config->enableInterrupts != 0U) {
            ((CSITX_PrivateData *)pD)->cb = *callbacks;
            if (callbacks->event == NULL) {
                result = CDN_EINVAL;
            }
        }
        /* get configuration of IP */
        if (result == CDN_EOK) {
            result = CSITX_GetDeviceConfig(pD, &pD->deviceConfig);
        }
    }
    return result;
}

/**
 * Driver ISR.  Platform-specific code is responsible for ensuring
 * this gets called when the corresponding hardware's interrupt is
 * asserted. Registering the ISR should be done after calling init,
 * and before calling start. The driver's ISR will not attempt to lock
 * any locks, but will perform client callbacks. If the client wishes
 * to defer processing to non-interrupt time, it is responsible for
 * doing so.
 * @param[in] pD Driver instance data filled by init
 */
void CSITX_Isr(CSITX_PrivateData* pD)
{
    uint32_t irq_status = 0U;
    uint32_t dphy_irq_status = 0U;

    /* check params */
    if (CSITX_IsrSF(pD) == CDN_EOK) {
        irq_status = CPS_REG_READ(&pD->cfg.regBase->irq);
        dphy_irq_status = CPS_REG_READ(&pD->cfg.regBase->dphy_irq);

        /* Clearing interrupts */
        CPS_REG_WRITE(&pD->cfg.regBase->irq, irq_status);
        CPS_REG_WRITE(&pD->cfg.regBase->dphy_irq, dphy_irq_status);

        /* calling user callback for interrupt events */
        if ((irq_status > 0U) || (dphy_irq_status > 0U)) {
            ((CSITX_PrivateData *) pD)->cb.event(pD, irq_status, dphy_irq_status);
        }
    }
}

/**
 * Start the CSITX driver, enabling interrupts. This is called after
 * the client has successfully initialized the driver and hooked the
 * driver's ISR (the isr member of this struct) to the IRQ.
 * @param[in] pD Driver state info specific to this instance
 */
void CSITX_Start(CSITX_PrivateData* pD)
{
    /* check params */
    if (CSITX_StartSF(pD) == CDN_EOK) {
        /* enabling interrupts */
        if (pD->cfg.enableInterrupts != 0U) {
            (void)CSITX_SetInterruptsEnable(pD, 1U); /* global interrupt flag */
            /* unmasking all CSITX interrupts */
            CPS_REG_WRITE(&pD->cfg.regBase->irq_mask, CSITX__IRQ_WRITE_MASK);
            CPS_REG_WRITE(&pD->cfg.regBase->dphy_irq_mask, CSITX__DPHY_IRQ_WRITE_MASK);
        }
    }
}

/**
 * Stop the CSITX driver, disabling interrupts.
 * @param[in] pD Driver state info specific to this instance
 */
void CSITX_Stop(CSITX_PrivateData* pD)
{
    /* check params */
    if (CSITX_StopSF(pD) == CDN_EOK) {

        /* disabling interrupts */
        if (pD->cfg.enableInterrupts != 0U) {
            (void)CSITX_SetInterruptsEnable(pD, 0U); /* global interrupt flag */
            /* masking all CSITX interrupts */
            CPS_REG_WRITE(&pD->cfg.regBase->irq_mask, 0x0U);
            CPS_REG_WRITE(&pD->cfg.regBase->dphy_irq_mask, 0x0U);
        }
    }
}

/**
 * Destructor for the driver.
 */
void CSITX_Destroy(void)
{
    return;
}

/**
 * Retrieves ASF information from CSITX controller.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] asfInfo Pointer to ASF information structure.
 * @return CDN_EINVAL If pD or asfInfo is NULL.
 * @return CDN_EOK On success.
 */
uint32_t CSITX_GetAsfInfo(const CSITX_PrivateData *pD, CSITX_AsfInfo* asfInfo)
{
    uint32_t status = CDN_EOK;

    /* check params */
    if (CSITX_GetAsfInfoSF(pD, asfInfo) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        if (pD->deviceConfig.asfPresent != 0U) {
            asfInfo->regBase = &(pD->cfg.regBase->asf_int_status);
        } else {
            status = CDN_ENOTSUP;
        }
    }
    return status;
}

/**
 * getter for DeviceConfig
 * @param[in] pD Pointer to the private data initialized by init
 * @param[out] value output struct
 * @return CDN_EOK on success
 * @return CDN_EINVAL if any pointer parameters are NULL
 */
uint32_t CSITX_GetDeviceConfig(const CSITX_PrivateData *pD,
                               CSITX_DeviceConfig *     value) {
    uint32_t status = CDN_EOK;

    /* check parameters */
    if (CSITX_GetDeviceConfigSF(pD, value) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t regVal = 0U;
        /* get information related to the current configuration of the controller */
        regVal = CPS_REG_READ(&pD->cfg.regBase->device_config);
        value->v1p3FeaturesEnable = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, V1_3_FEATURES, regVal));
        value->rxCompatibilityMode = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, RX_COMP_MODE_PRESENT, regVal));
        value->scramblerPresent = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, SCRAMBLER_PRESENT, regVal));
        value->asfPresent = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, ASF_PRESENT, regVal));
        value->numDts = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, NUM_DTS, regVal));
        value->numVcs = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, NUM_VCS, regVal));
        value->datapathSize = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, DATAPATH_SIZE, regVal));
        value->numStreams = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, NUM_STREAMS, regVal));
        value->cdnsPhyPresent = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, CDNS_PHY_PRESENT, regVal));
        value->numLanes = (uint8_t)(CPS_FLD_READ(CSITX__DEVICE_CONFIG, MAX_LANE_NB, regVal));
    }
    return status;
}

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
 *  \file bridge_sii9022a.c
 *
 *  \brief SII9022A bridge API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <board/panel.h>
#include <drivers/fvid2.h>
#include <drivers/i2c.h>
#include "i2c_bridge_sii9022a.h"
#include <board/panel/panel_i2c.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define I2C_BRIDGE_SII9022A_INPUTBUS_PIXEL_REP_BIT4_MASK            (0x10U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t BridgeSii9022a_open(Panel_Config *config, Panel_Params *params);
static void BridgeSii9022a_close(Panel_Config *config, Panel_Params *params);
static int32_t BridgeSii9022a_control(Panel_Config *config,
                                      Panel_Params *params,
                                      uint32_t cmd,
                                      void *cmdArgs);
static int32_t BridgeSii9022a_setBridgeMode(const Panel_Config *config,
                                            const Panel_Params *params);
static int32_t BridgeSii9022a_getHotPlugData(const Panel_Config *config,
                                             const Panel_Params *params,
                                             BridgeSii9022a_HpdParams *hpdParams);
static int32_t BridgeSii9022a_startDeviceOutput(const Panel_Config *config,
                                                const Panel_Params *params);
static int32_t BridgeSii9022a_stopDeviceOutput(const Panel_Config *config,
                                               const Panel_Params *params);
static int32_t BridgeSii9022a_initDevice(const Panel_Config *config,
                                         const Panel_Params *params);
static int32_t BridgeSii9022a_reset(Panel_Config *config,
                                    Panel_Params *params);
static int32_t BridgeSii9022a_enableDevice(const Panel_Config *config,
                                           const Panel_Params *params);
static int32_t BridgeSii9022a_powerUpTransmitter(const Panel_Config *config,
                                                 const Panel_Params *params);
static int32_t BridgeSii9022a_configureInputBus(const Panel_Config *config,
                                                const Panel_Params *params);
static int32_t BridgeSii9022a_configureYcMuxMode(const Panel_Config *config,
                                                 const Panel_Params *params);
static int32_t BridgeSii9022a_configureSyncMode(const Panel_Config *config,
                                                const Panel_Params *params);
static int32_t BridgeSii9022a_getHdmiChipId(const Panel_Config *config,
                                            const Panel_Params *params,
                                            BridgeSii9022a_HdmiChipId *hdmiChipId);
static int32_t BridgeSii9022a_prgmExtSyncTimingInfo(const Panel_Config *config,
                                                    const Panel_Params *params);
static int32_t BridgeSii9022a_prgmEmbSyncTimingInfo(const Panel_Config *config,
                                                    const Panel_Params *params);
static int32_t BridgeSii9022a_prgmAvInfoFrame(const Panel_Config *config,
                                              const Panel_Params *params);
static int32_t BridgeSii9022a_progmModeResetRegs(const Panel_Config *config,
                                                 const Panel_Params *params);
static void BridgeSii9022a_calculateCRC(uint8_t *regAddr,
                                        uint8_t *regValue,
                                        uint32_t *numRegs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief SII9022A driver function pointer. */
Panel_Fxns gPanelBridgeSii9022aFxns =
{
    .openFxn = BridgeSii9022a_open,
    .closeFxn = BridgeSii9022a_close,
    .controlFxn = BridgeSii9022a_control,
    .resetFxn = BridgeSii9022a_reset,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static int32_t BridgeSii9022a_open(Panel_Config *config, Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    BridgeSii9022a_Object *object = NULL;
    object = (BridgeSii9022a_Object *)(config->object);

    if (object != NULL)
    {
        object->outputFormat = params->bridgeParams.outputFormat;

        /* These settings are for Embedded sync, in SET_MODE IOCTL according to
         * the Video infetface mode it will be set accordingly. */
        object->syncCfgReg = 0x04U;
        object->inBusCfg = 0x70U;

        /* FALSE to latch data on falling clock edge. Rising edge otherwise */
        /* Bit 4 of of TPI Input bus and pixel repetation */
        if (params->bridgeParams.clkEdge == FALSE)
        {
            object->inBusCfg &= ~((uint32_t)I2C_BRIDGE_SII9022A_INPUTBUS_PIXEL_REP_BIT4_MASK);
        }
        else
        {
            object->inBusCfg |= I2C_BRIDGE_SII9022A_INPUTBUS_PIXEL_REP_BIT4_MASK;
        }

        /* Enable DE in syncpolarity register at 0x63 */
        object->syncPolarityReg = 0x40U;

        status = BridgeSii9022a_reset(config, params);

        status += BridgeSii9022a_initDevice(config, params);

        status += BridgeSii9022a_setBridgeMode(config, params);

        status += BridgeSii9022a_startDeviceOutput(config, params);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static void BridgeSii9022a_close(Panel_Config *config, Panel_Params *params)
{
    BridgeSii9022a_Object *object = NULL;
    object = (BridgeSii9022a_Object *)(config->object);

    if(object != NULL)
    {
        BridgeSii9022a_stopDeviceOutput(config, params);
    }

    return;
}

static int32_t BridgeSii9022a_control(Panel_Config *config,
                                      Panel_Params *params,
                                      uint32_t cmd,
                                      void *cmdArgs)
{
    int32_t status = SystemP_SUCCESS;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if(object != NULL)
    {
        switch (cmd)
        {
            case I2C_BRIDGE_SII9022A_GET_DETAILED_CHIP_ID:
            {
                status = BridgeSii9022a_getHdmiChipId(config, params,
                                        (BridgeSii9022a_HdmiChipId *)cmdArgs);
                break;
            }
            case I2C_BRIDGE_SII9022A_QUERY_HPD:
            {
                status = BridgeSii9022a_setBridgeMode(config, params);
                break;
            }
            case I2C_BRIDGE_SII9022A_ENC_SET_MODE:
            {
                status = BridgeSii9022a_getHotPlugData(config, params,
                                        (BridgeSii9022a_HpdParams *)cmdArgs);
                break;
            }
            default:
            {
                status = SystemP_FAILURE;
                break;
            }

        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_setBridgeMode(const Panel_Config *config,
                                            const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if(object != NULL)
    {
        if (params->vidOutParams.videoIfMode == FVID2_VIFM_SCH_ES)
        {
            if ((params->vidOutParams.videoIfWidth == FVID2_VIFW_8BIT) ||
                (params->vidOutParams.videoIfWidth == FVID2_VIFW_10BIT))
            {
                /* Set YC mux mode for 8 and 10-bit interfaces. */
                object->syncCfgReg = 0xA4U;
            }
            else
            {
                object->syncCfgReg = 0x84U;
            }

            status += BridgeSii9022a_configureSyncMode(config, params);
            status += BridgeSii9022a_prgmEmbSyncTimingInfo(config, params);
            status += BridgeSii9022a_prgmAvInfoFrame(config, params);
            status += BridgeSii9022a_progmModeResetRegs(config, params);
        }
        else if (params->vidOutParams.videoIfMode == \
                 FVID2_VIFM_SCH_DS_AVID_VSYNC)
        {
            object->syncCfgReg = 0x04U;
            status = BridgeSii9022a_configureSyncMode(config, params);
            if (status == SystemP_SUCCESS)
            {
                status = BridgeSii9022a_prgmExtSyncTimingInfo(config, \
                                                              params);
                status += BridgeSii9022a_prgmAvInfoFrame(config, params);
            }
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_getHotPlugData(const Panel_Config *config,
                                             const Panel_Params *params,
                                             BridgeSii9022a_HpdParams *hpdParams)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regValue = 0U;
    uint8_t regAddr;
    uint32_t numRegs = 1U;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if (object != NULL && hpdParams != NULL)
    {
        regAddr = 0x3DU;
        status = Panel_i2cBridgeRead(params->bridgeParams.deviceI2cInstId,
                                     params->bridgeParams.deviceI2cAddr,
                                     &regAddr,
                                     &regValue,
                                     numRegs);
        if (status == SystemP_SUCCESS)
        {
            hpdParams->hpdEvtPending = ((uint32_t)regValue & 0x01U);
            hpdParams->busError = ((uint32_t)regValue & 0x02U);
            hpdParams->hpdStatus = ((uint32_t)regValue & 0x04U);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_startDeviceOutput(const Panel_Config *config,
                                                const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regValue = 0U;
    uint8_t regAddr;
    uint32_t numRegs = 1U;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if(object != NULL)
    {
        /* Enable TMDS output */
        regAddr = 0x1AU;
        status = Panel_i2cBridgeRead(params->bridgeParams.deviceI2cInstId,
                                     params->bridgeParams.deviceI2cAddr,
                                     &regAddr,
                                     &regValue,
                                     numRegs);
        if(status == SystemP_SUCCESS)
        {
            /* Enable HDMI output */
            regValue |= 0x01U;
            /* Enable Output TMDS */
            regValue &= 0xEFU;

            status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                          params->bridgeParams.deviceI2cAddr,
                                          &regAddr,
                                          &regValue,
                                          numRegs);

            status += BridgeSii9022a_configureInputBus(config, params);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_stopDeviceOutput(const Panel_Config *config,
                                               const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regValue = 0U;
    uint8_t regAddr;
    uint32_t numRegs = 1U;

    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if(object != NULL)
    {
        /* Disable TMDS output */
        regAddr = 0x1AU;
        status = Panel_i2cBridgeRead(params->bridgeParams.deviceI2cInstId,
                                     params->bridgeParams.deviceI2cAddr,
                                     &regAddr,
                                     &regValue,
                                     numRegs);
        if(status == SystemP_SUCCESS)
        {
            /* Enable HDMI output */
            regValue |= 0x01U;
            /* Power Down Output TMDS Clock */
            regValue |= 0x10U;

            status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                          params->bridgeParams.deviceI2cAddr,
                                          &regAddr,
                                          &regValue,
                                          numRegs);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_initDevice(const Panel_Config *config,
                                         const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;

    if (config != NULL)
    {
        BridgeSii9022a_Object *object = \
                                    (BridgeSii9022a_Object *)(config->object);

        if (BridgeSii9022a_getHdmiChipId(config, params, &(object->hdmiChipId))\
                                         != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }

        if (BridgeSii9022a_powerUpTransmitter(config, params) \
                                              != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }

        if (BridgeSii9022a_enableDevice(config, params) != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }

        if (BridgeSii9022a_configureInputBus(config, params) != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }

        if (BridgeSii9022a_configureYcMuxMode(config, params) != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }

        if (BridgeSii9022a_configureSyncMode(config, params) != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_reset(Panel_Config *config,
                                    Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regAddr[4U];
    uint8_t regValue[4U];
    uint8_t numRegs;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if (object != NULL)
    {
        numRegs = (uint8_t)0U;
        regAddr[numRegs] = (uint8_t)0xC7U;
        regValue[numRegs] = (uint8_t)0x00U;
        numRegs++;

        status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      regAddr,
                                      regValue,
                                      numRegs);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_enableDevice(const Panel_Config *config,
                                           const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regAddr[4];
    uint8_t regValue[4];
    uint32_t numRegs;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if (object != NULL)
    {
        numRegs = 0U;
        regAddr[numRegs] = 0xBCU;
        regValue[numRegs] = 0x01U;
        numRegs++;

        regAddr[numRegs] = 0xBDU;
        regValue[numRegs] = 0x82U;
        numRegs++;

        status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      regAddr,
                                      regValue,
                                      numRegs);

        if (status == SystemP_SUCCESS)
        {
            numRegs = 0U;
            regAddr[numRegs] = 0xBEU;
            regValue[numRegs] = 0x01U;
            numRegs++;

            status = Panel_i2cBridgeRead(params->bridgeParams.deviceI2cInstId,
                                         params->bridgeParams.deviceI2cAddr,
                                         regAddr,
                                         regValue,
                                         numRegs);
            if (status == SystemP_SUCCESS)
            {
                regValue[0U] |= 0x01U;

                status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                              params->bridgeParams.deviceI2cAddr,
                                              regAddr,
                                              regValue,
                                              numRegs);
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_powerUpTransmitter(const Panel_Config *config,
                                                 const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regAddr;
    uint8_t regValue = 0U;
    uint32_t numRegs = 1U;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if (object != NULL)
    {
        regAddr = 0x1EU;

        status = Panel_i2cBridgeRead(params->bridgeParams.deviceI2cInstId,
                                     params->bridgeParams.deviceI2cAddr,
                                     &regAddr,
                                     &regValue,
                                     numRegs);
        if (status == SystemP_SUCCESS)
        {
            regValue &= 0xFCU;

            status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                          params->bridgeParams.deviceI2cAddr,
                                          &regAddr,
                                          &regValue,
                                          numRegs);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_configureInputBus(const Panel_Config *config,
                                                const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regAddr;
    uint8_t regValue;
    uint32_t numRegs = 1U;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if (object != NULL)
    {
        /* Configure Input Bus and pixel repetation. */
        regAddr = 0x08U;
        regValue = (uint8_t) object->inBusCfg;
        status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      &regAddr,
                                      &regValue,
                                      numRegs);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_configureYcMuxMode(const Panel_Config *config,
                                                 const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regAddr;
    uint8_t regValue;
    uint32_t numRegs = 1U;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if (object != NULL)
    {
        /* Configure YC Mode. */
        regAddr = 0x0BU;
        regValue = 0x00U;
        status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      &regAddr,
                                      &regValue,
                                      numRegs);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_configureSyncMode(const Panel_Config *config,
                                                const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regAddr;
    uint8_t regValue;
    uint32_t numRegs = 1U;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if (object != NULL)
    {
        /* Configure Sync Mode. */
        regAddr = 0x60U;
        regValue = object->syncCfgReg;
        status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      &regAddr,
                                      &regValue,
                                      numRegs);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_getHdmiChipId(const Panel_Config *config,
                                            const Panel_Params *params,
                                            BridgeSii9022a_HdmiChipId *hdmiChipId)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regAddr[8U];
    uint8_t regValue[8U];
    uint8_t numRegs;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if (object != NULL)
    {
        /* Get TP5158 chip ID, revision ID and firmware patch ID. */
        numRegs = 0;
        regAddr[numRegs] = 0x1BU;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs] = 0x1CU;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs] = 0x1DU;
        regValue[numRegs] = 0;
        numRegs++;

        regAddr[numRegs] = 0x30U;
        regValue[numRegs] = 0;
        numRegs++;

        status = Panel_i2cBridgeRead(params->bridgeParams.deviceI2cInstId,
                                     params->bridgeParams.deviceI2cAddr,
                                     regAddr,
                                     regValue,
                                     numRegs);
        if (status == SystemP_SUCCESS)
        {
            hdmiChipId->deviceId = regValue[0];
            hdmiChipId->deviceProdRevId = regValue[1];
            hdmiChipId->tpiRevId = regValue[2];
            hdmiChipId->hdcpRevTpi = regValue[3];
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_prgmExtSyncTimingInfo(const Panel_Config *config,
                                                    const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regValue[20U];
    uint8_t regAddr[20U];
    uint32_t numRegs;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    /* Program Timing information for the separate sync input. */
    if(object != NULL)
    {
        numRegs = 0;
        regAddr[numRegs] = 0x62U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.extSyncPrms.deDelay & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x63U;
        object->syncPolarityReg &= (uint8_t) ~(0x03U);
        object->syncPolarityReg |=
            ((object->modeInfo.extSyncPrms.deDelay & 0x300U) >> 8);
        regValue[numRegs] = (uint8_t)(object->syncPolarityReg & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x64U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.extSyncPrms.deTop & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x66U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.extSyncPrms.deCnt & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x67U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.extSyncPrms.deCnt & 0xF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x68U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.extSyncPrms.deLine & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x69U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.extSyncPrms.deLine & 0x700U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x00U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.pixClk & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x01U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.pixClk & 0xFF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x02U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.vFreq & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x03U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.vFreq & 0xFF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x04U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.pixels & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x05U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.pixels & 0xFF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x06U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.lines & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x07U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.lines & 0xFF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x08U;
        regValue[numRegs] = (uint8_t) object->inBusCfg;
        numRegs++;

        regAddr[numRegs] = 0x09U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x0AU;

        switch (object->outputFormat)
        {
            case BRIDGE_SII9022A_HDMI_RGB:
                regValue[numRegs] = 0x10U;
                object->isRgbOutput = 1;
                break;

            case BRIDGE_SII9022A_HDMI_YUV444:
                regValue[numRegs] = 0x11U;
                object->isRgbOutput = 0;
                break;

            case BRIDGE_SII9022A_HDMI_YUV422:
                regValue[numRegs] = 0x12U;
                object->isRgbOutput = 0;
                break;

            case BRIDGE_SII9022A_DVI_RGB:
                regValue[numRegs] = 0x13U;
                object->isRgbOutput = 1;
                break;

            default:
                break;
        }

        numRegs++;

        status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      regAddr,
                                      regValue,
                                      numRegs);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_prgmEmbSyncTimingInfo(const Panel_Config *config,
                                                    const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regValue[20U];
    uint8_t regAddr[20U];
    uint32_t numRegs;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if(object != NULL)
    {
        numRegs = 0;
        regAddr[numRegs] = 0x62U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.embSyncPrms.hBitToHSync & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x63U;
        object->syncPolarityReg &= ((uint8_t) ~(0x03U));
        object->syncPolarityReg |=
            ((object->modeInfo.embSyncPrms.hBitToHSync & 0x300U) >> 8);
        regValue[numRegs] = (uint8_t)(object->syncPolarityReg & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x64U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.embSyncPrms.field2Offset & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x65U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.embSyncPrms.field2Offset & 0xF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x66U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.embSyncPrms.hWidth & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x67U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.embSyncPrms.hWidth & 0x300U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x68U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.embSyncPrms.vBitToVSync & 0x3FU);
        numRegs++;

        regAddr[numRegs] = 0x69U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.embSyncPrms.vWidth & 0x3FU);
        numRegs++;

        regAddr[numRegs] = 0x00U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.pixClk & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x01U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.pixClk & 0xFF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x02U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.vFreq & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x03U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.vFreq & 0xFF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x04U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.pixels & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x05U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.pixels & 0xFF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x06U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.lines & 0xFFU);
        numRegs++;

        regAddr[numRegs] = 0x07U;
        regValue[numRegs] = (uint8_t)((object->modeInfo.lines & 0xFF00U) >> 8);
        numRegs++;

        regAddr[numRegs] = 0x08U;
        regValue[numRegs] = (uint8_t) object->inBusCfg;
        numRegs++;

        regAddr[numRegs] = 0x09U;
        regValue[numRegs] = 0x02U;
        numRegs++;

        regAddr[numRegs] = 0x0AU;
        switch (object->outputFormat)
        {
            case BRIDGE_SII9022A_HDMI_RGB:
                regValue[numRegs] = 0x10U;
                object->isRgbOutput = 1;
                break;

            case BRIDGE_SII9022A_HDMI_YUV444:
                regValue[numRegs] = 0x11U;
                object->isRgbOutput = 0;
                break;

            case BRIDGE_SII9022A_HDMI_YUV422:
                regValue[numRegs] = 0x12U;
                object->isRgbOutput = 0;
                break;

            case BRIDGE_SII9022A_DVI_RGB:
                regValue[numRegs] = 0x13U;
                object->isRgbOutput = 1;
                break;

            default:
                break;
        }
        numRegs++;

        status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      regAddr,
                                      regValue,
                                      numRegs);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_prgmAvInfoFrame(const Panel_Config *config,
                                              const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regValue[15U];
    uint8_t regAddr[15U];
    uint32_t numRegs;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if(object != NULL)
    {
        numRegs = 0;
        regAddr[numRegs] = 0x0DU;
        if (object->isRgbOutput)
        {
            regValue[numRegs] = 0x01U;
        }
        else
        {
            regValue[numRegs] = 0x21U;
        }
        numRegs++;

        regAddr[numRegs] = 0x0EU;
        regValue[numRegs] = 0xA0U;
        numRegs++;

        regAddr[numRegs] = 0x0FU;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x10U;
        regValue[numRegs] = (uint8_t)(object->modeInfo.modeCode & 0x7FU);
        numRegs++;

        regAddr[numRegs] = 0x11U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x12U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x13U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x14U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x15U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x16U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x17U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x18U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        regAddr[numRegs] = 0x19U;
        regValue[numRegs] = 0x00U;
        numRegs++;

        if(status == SystemP_SUCCESS)
        {
            BridgeSii9022a_calculateCRC(regAddr, regValue, &numRegs);
            if(object->outputFormat == BRIDGE_SII9022A_DVI_RGB)
            {
                memset(regValue, 0x0U, sizeof(regValue));
            }

            status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                          params->bridgeParams.deviceI2cAddr,
                                          regAddr,
                                          regValue,
                                          numRegs);
        }
        regAddr[0] = 0x19U;
        regValue[0] = 0x00U;
        status += Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      regAddr,
                                      regValue,
                                      1U);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t BridgeSii9022a_progmModeResetRegs(const Panel_Config *config,
                                                 const Panel_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t regAddr;
    uint8_t regValue;
    uint32_t numRegs = 1U;
    BridgeSii9022a_Object *object = (BridgeSii9022a_Object *)(config->object);

    if(object != NULL)
    {
        regAddr = 0x63U;
        regValue = object->syncPolarityReg;
        status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      &regAddr,
                                      &regValue,
                                      numRegs);

        regAddr = 0x60U;
        regValue = object->syncCfgReg;
        status += Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                      params->bridgeParams.deviceI2cAddr,
                                      &regAddr,
                                      &regValue,
                                      numRegs);
        if (status == SystemP_SUCCESS)
        {
            /* Sleep to be added for 5 ms if requried. */
            regAddr = 0x61U;
            status = Panel_i2cBridgeRead(params->bridgeParams.deviceI2cInstId,
                                         params->bridgeParams.deviceI2cAddr,
                                         &regAddr,
                                         &regValue,
                                         numRegs);

            if (status == SystemP_SUCCESS)
            {
                uint32_t tempSyncPolarityReg;
                uint32_t regValue32;
                /* Set the same sync polarity in 0x63U register */
                regValue32 = (uint32_t)regValue;
                tempSyncPolarityReg = (uint32_t)object->syncPolarityReg;
                tempSyncPolarityReg &= (~(0x30U));
                tempSyncPolarityReg |= ((regValue32 & 0x03U) << 4U);
                object->syncPolarityReg = (uint8_t)tempSyncPolarityReg;

                regAddr = 0x63U;
                regValue = object->syncPolarityReg;
                status = Panel_i2cBridgeWrite(params->bridgeParams.deviceI2cInstId,
                                              params->bridgeParams.deviceI2cAddr,
                                              &regAddr,
                                              &regValue,
                                              numRegs);
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static void BridgeSii9022a_calculateCRC(uint8_t *regAddr,
                                        uint8_t *regValue,
                                        uint32_t *numRegs)
{
    uint32_t sum = 0U;

    for (uint32_t count = 0U; count < *numRegs; count++)
    {
        sum += regValue[count];
    }

    sum += (0x82U + 0x02U + 13U);
    sum &= 0xFFU;
    regValue[*numRegs] = (uint8_t)(0x100U - sum);
    regAddr[*numRegs] = 0x0CU;
    (*numRegs)++;

    return;
}

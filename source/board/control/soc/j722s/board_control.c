/*
 *  Copyright (C) 2023-2026 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <board/board_control.h>
#include <drivers/hw_include/csl_types.h>
#include <board/ioexp/ioexp_tca6424.h>
#include <drivers/i2c.h>
#include <kernel/dpl/ClockP.h>
#include <board/ioexp/ioexp_tca6416.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BOARD_CSI_IOEXP_ADDR                (0x23)
#define BOARD_CSI_IOEXP_PIN_NUM             (0x0)
#define I2C_TRANSACTION_TIMEOUT             (2000U)
#define BOARD_DSI2DP_IOEXP_ADDR             (0x20U)
#define BOARD_DSI2DP_IOEXP_PIN_NUM          (0x1U)
#define BOARD_HDMI_IOEXP_ADDR               (0x20U)
#define BOARD_HDMI_IOEXP_PIN_IND            (0x4U)
#define BOARD_HDMI_LS_OE_IND                (0x5U)

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

static uint8_t gHdmiCfgBuf_1080p[][2] = {
{0xC7, 0x00},
{0x1E, 0x02},
{0x00, 0x02},
{0x01, 0x3A},
{0x02, 0x3C},
{0x03, 0x00},
{0x04, 0x80},
{0x05, 0x07},
{0x06, 0x38},
{0x07, 0x04},
{0x6a, 0x98},
{0x6b, 0x08},
{0x6c, 0x65},
{0x6d, 0x04},
{0x08, 0x60},
{0x09, 0x00},
{0x0A, 0x10},
{0x1A, 0x10},
{0x1E, 0x00},
{0x1A, 0x01},
{0x2A, 0x00}
};

/* TODO: This is just a placeholder for 720p support. Config need to be updated */
static uint8_t gHdmiCfgBuf_720p[][2] = {
{0x1E, 0x02},
{0x00, 0x00},
{0x01, 0x00},
{0x02, 0x3C},
{0x03, 0x00},
{0x04, 0x00},
{0x05, 0x00},
{0x06, 0x00},
{0x07, 0x00},
{0x08, 0x60},
{0x09, 0x00},
{0x0A, 0x10},
{0x1A, 0x10},
{0x1E, 0x00},
{0x1A, 0x01},
{0x2A, 0x00}
};

uint8_t gI2cDsiBridgeCfg720p[][2] = {
{0xFF, 0x7},
{0x16, 0x1},
{0xFF, 0x0},
{0x0A, 0x2},
{0x10, 0x36},
{0x12, 0x4C},
{0x13, 0x4C},
{0x94, 0x80},
{0x0D, 0x1},
{0x5A, 0x4},
{0x5F, 0x28},
{0x93, 0x10},
{0x96, 0x0A},
{0x20, 0x00},
{0x21, 0x05},
{0x22, 0x0},
{0x23, 0x0},
{0x24, 0xD0},
{0x25, 0x02},
{0x2C, 0x22},
{0x2D, 0x00},
{0x30, 0x0A},
{0x31, 0x00},
{0x34, 0x1E},
{0x36, 0x0A},
{0x38, 0x2D},
{0x3A, 0x0A},
{0x5B, 0x0},
{0x3C, 0x00},
{0x5A, 0x0C},
};

uint8_t gI2cDsiBridgeCfg1080p[][2] = {
{0xFF, 0x7},
{0x16, 0x1},
{0xFF, 0x0},
{0x0A, 0x2},
{0x10, 0x26},
{0x12, 0x4F},
{0x13, 0x4C},
{0x94, 0x80},
{0x0D, 0x1},
{0x5A, 0x4},
{0x5F, 0x28},
{0x93, 0x20},
{0x96, 0x0A},
{0x20, 0x80},
{0x21, 0x07},
{0x22, 0x0},
{0x23, 0x0},
{0x24, 0x38},
{0x25, 0x04},
{0x2C, 0x3C},
{0x2D, 0x00},
{0x30, 0x37},
{0x31, 0x00},
{0x34, 0x28},
{0x36, 0x37},
{0x38, 0x08},
{0x3A, 0x3C},
{0x5B, 0x0},
{0x3C, 0x00},
{0x5A, 0x0C},
};

static TCA6416_Config gTCA6416BrdCtrlConfig;
static TCA6424_Config gTCA6424CsiCfg;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Board_enableCSII2c(uint32_t i2cInstance)
{
    int32_t status = SystemP_SUCCESS;
    TCA6424_Params tca6424Params;

    TCA6424_Params_init(&tca6424Params);
    tca6424Params.i2cInstance = i2cInstance;
    tca6424Params.i2cAddress = BOARD_CSI_IOEXP_ADDR;

    status = TCA6424_open(&gTCA6424CsiCfg, &tca6424Params);
    if(status == SystemP_SUCCESS)
    {
        status += TCA6424_config(&gTCA6424CsiCfg,
                     BOARD_CSI_IOEXP_PIN_NUM,
                     TCA6424_MODE_OUTPUT);
        status += TCA6424_setOutput(&gTCA6424CsiCfg,
                        BOARD_CSI_IOEXP_PIN_NUM,
                        TCA6424_OUT_STATE_LOW);
    }

    return status;
}

static int32_t Board_enableDSI2EDPBridge(uint32_t i2cInstance)
{
    int32_t         status = SystemP_SUCCESS;
    TCA6416_Params  tca6416Params;

    TCA6416_Params_init(&tca6416Params);
    tca6416Params.i2cInstance =  i2cInstance;
    tca6416Params.i2cAddress  = BOARD_DSI2DP_IOEXP_ADDR;

    status = TCA6416_open(&gTCA6416BrdCtrlConfig, &tca6416Params);
    if(status == SystemP_SUCCESS)
    {
        /* Configure as output  */
        status += TCA6416_config(
                        &gTCA6416BrdCtrlConfig,
                        BOARD_DSI2DP_IOEXP_PIN_NUM,
                        TCA6416_MODE_OUTPUT);

        status += TCA6416_setOutput(
                        &gTCA6416BrdCtrlConfig,
                        BOARD_DSI2DP_IOEXP_PIN_NUM,
                        TCA6416_OUT_STATE_HIGH);

        TCA6416_close(&gTCA6416BrdCtrlConfig);
    }

    return status;
}

static int32_t Board_enableHdmi(BOARD_HdmiCfg_t *hdmiCfg)
{
    int32_t         status = SystemP_SUCCESS;
    TCA6416_Params  tca6416Params;

    TCA6416_Params_init(&tca6416Params);
    tca6416Params.i2cInstance = hdmiCfg->i2cInstance;
    tca6416Params.i2cAddress = BOARD_HDMI_IOEXP_ADDR;

    status = TCA6416_open(&gTCA6416BrdCtrlConfig, &tca6416Params);
    if(status == SystemP_SUCCESS)
    {
        /* Configure as output  */
        status += TCA6416_config(
                        &gTCA6416BrdCtrlConfig,
                        BOARD_HDMI_IOEXP_PIN_IND,
                        TCA6416_MODE_OUTPUT);
        status += TCA6416_config(
                        &gTCA6416BrdCtrlConfig,
                        BOARD_HDMI_LS_OE_IND,
                        TCA6416_MODE_OUTPUT);

        status += TCA6416_setOutput(
                        &gTCA6416BrdCtrlConfig,
                        BOARD_HDMI_IOEXP_PIN_IND,
                        TCA6416_OUT_STATE_HIGH);
        status += TCA6416_setOutput(
                        &gTCA6416BrdCtrlConfig,
                        BOARD_HDMI_LS_OE_IND,
                        TCA6416_OUT_STATE_HIGH);

        TCA6416_close(&gTCA6416BrdCtrlConfig);
    }

    return status;
}

/**
 * \brief Configures DSI to DP bridge
 *
 *  \return   SystemP_SUCCESS in case of success or appropriate error code.
 *
 */
static int32_t Board_configDSI2DPBridge(BOARD_DSI2DPBridgeCfg_t *dsiBridgeConfig)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i2cInstance = dsiBridgeConfig->i2cInstance;
    I2C_Handle i2cHandle = dsiBridgeConfig->i2cHandle;
    uint8_t (*pDsiBridgeCfgBuf)[2];
    uint32_t dsiCfgSize = sizeof(gI2cDsiBridgeCfg1080p)/sizeof(gI2cDsiBridgeCfg1080p[0]);
    uint64_t startTime, endTime, timeout = 4000000  /* 4 seconds */;

    /* Enable the DSI to eDP bridge. */
    status = Board_enableDSI2EDPBridge(i2cInstance);
    ClockP_usleep(1000000); /* 1s delay */

    if (SystemP_SUCCESS == status)
    {
        DebugP_log("DSI to EDP bridge is enabled...\r\n");
    }
    else
    {
        DebugP_log("DSI to EDP bridge could not be enabled !!\r\n");
    }

    /* Clearing the error status registers.*/
    uint8_t readVal, wrVal = 0xFF, i;
    for(i = 0xF0; i < 0xF9; i++)
    {
        Board_i2c8BitRegWr(i2cHandle,
                            0x2C,
                            i & 0xFF,
                            &wrVal,
                            1,
                            I2C_TRANSACTION_TIMEOUT);
    }

    if (dsiBridgeConfig->resolution == BOARD_CTRL_DSI_BRIDGE_1080P)
    {
        pDsiBridgeCfgBuf = &(gI2cDsiBridgeCfg1080p[0]);
    }
    else
    {
        pDsiBridgeCfgBuf = &(gI2cDsiBridgeCfg720p[0]);
    }

    for(i = 0; i < dsiCfgSize; i++)
    {
        /* Read the value at bridge address. */
        Board_i2c8BitRegWr(i2cHandle,
                            0x2C,
                            pDsiBridgeCfgBuf[i][0] & 0xFF,
                            &pDsiBridgeCfgBuf[i][1],
                            1,
                            I2C_TRANSACTION_TIMEOUT);
        ClockP_usleep(200000); /* 200ms delay. */
        /* Wait untill the DP_PLL has been locked. */
        if (0x0D == pDsiBridgeCfgBuf[i][0])
        {
            do {
                Board_i2c8BitRegRd(i2cHandle,
                            0x2C,
                            0x0A,
                            &readVal,
                            1,
                            I2C_TRANSACTION_TIMEOUT);
            } while (0x00 == (readVal & 0x80));
        }

        /* Main link should not be off. So keep waiting as long as the main links are off. */
        if (0x96 == pDsiBridgeCfgBuf[i][0])
        {
            startTime = ClockP_getTimeUsec();
            do {
                Board_i2c8BitRegRd(i2cHandle,
                            0x2C,
                            0x96,
                            &readVal,
                            1,
                            I2C_TRANSACTION_TIMEOUT);
                endTime = ClockP_getTimeUsec();
            } while (0x00 == (readVal) && ((endTime - startTime) < timeout));
        }
    }
    Board_DSIBridgeErrorRegRead(i2cHandle);
    if ((endTime - startTime) >= timeout)
    {
        DebugP_log("DSI to EDP bridge configuration failed !!! \r\n");
    }

    return (status);
}

/**
 * \brief Configures HDMI transmitter
 *
 *  \return   Board_SOK in case of success or appropriate error code.
 *
 */
static int32_t Board_configHdmi(BOARD_HdmiCfg_t *hdmiCfg)
{
    uint32_t index;
    uint32_t hdmiCfgSize;
    int32_t status = SystemP_SUCCESS;
    I2C_Handle i2cHandle;
    I2C_Transaction i2cTransaction;
    uint8_t (*pHdmiCfgBuf)[2];

    status = Board_enableHdmi(hdmiCfg);
    i2cHandle = hdmiCfg->i2cHandle;
    if((SystemP_SUCCESS == status) && (i2cHandle != NULL))
    {
        if(hdmiCfg->resolution == BOARD_CTRL_HDMI_RES_720P)
        {
            pHdmiCfgBuf = gHdmiCfgBuf_720p;
            hdmiCfgSize = sizeof(gHdmiCfgBuf_720p)/sizeof(gHdmiCfgBuf_720p[0]);
        }
        else
        {
            pHdmiCfgBuf = gHdmiCfgBuf_1080p;
            hdmiCfgSize = sizeof(gHdmiCfgBuf_1080p)/sizeof(gHdmiCfgBuf_1080p[0]);

        }

        /* Set default transaction parameters */
        I2C_Transaction_init(&i2cTransaction);

        /* Override with required transaction parameters */
        i2cTransaction.writeCount   = 2U;
        i2cTransaction.targetAddress = BOARD_CTRL_HDMI_I2C_ADDR;

        for(index = 0; index < hdmiCfgSize; index++)
        {
            i2cTransaction.writeBuf = &pHdmiCfgBuf[index][0];
            status += I2C_transfer(i2cHandle, &i2cTransaction);
            ClockP_usleep(50);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return (status);
}

void Board_fpdUb960GetI2CAddr(uint8_t *i2cAddr,
                              uint32_t csiInst)
{
    if (csiInst == 0)
    {
        *i2cAddr = 0x3DU;
    }
    else if (csiInst == 1)
    {
        *i2cAddr = 0x36U;
    }
}

void Board_fpdUb9702GetI2CAddr(uint8_t *i2cAddr,
                             uint32_t csiInst)
{
    if (csiInst == 0U)
    {
        *i2cAddr = 0x3DU;
    }
    else if (csiInst == 1U)
    {
        *i2cAddr = 0x30U;
    }
    else if(csiInst == 2U)
    {
        *i2cAddr = 0x32U;
    }
    else
    {
        DebugP_log("Enter a correct hub instance");
    }
}

int32_t Board_i2c8BitRegWr(void *handle,
                           uint32_t slaveAddr,
                           uint8_t regAddr,
                           uint8_t *regData,
                           uint8_t numOfBytes,
                           uint32_t i2cTimeout)
{
    uint8_t tx[5];
    uint8_t *txPtr = NULL;
    int32_t status=0;

    I2C_Transaction transaction;

    I2C_Handle i2cHandle = (I2C_Handle)handle;

    /* Initializes the I2C transaction structure with default values */
    I2C_Transaction_init(&transaction);

    transaction.targetAddress = slaveAddr;
    transaction.writeBuf     = &tx[0];
    transaction.writeCount   = 2;
    transaction.readBuf      = NULL;
    transaction.readCount    = 0;
    transaction.timeout      = i2cTimeout;

    tx[0] = regAddr;
    txPtr = &tx[1];
    /* regData to be sent */
    while(numOfBytes)
    {
        *txPtr = *regData;
        txPtr++;
        regData++;
        numOfBytes--;
    }

    status = I2C_transfer(i2cHandle, &transaction);

    return status;
}

int32_t Board_i2c8BitRegRd(void *handle,
                           uint32_t slaveAddr,
                           uint8_t regAddr,
                           uint8_t *regData,
                           uint8_t numOfBytes,
                           uint32_t i2cTimeout)
{
    uint8_t tx[5];
    int32_t status=0;

    I2C_Transaction transaction;

    I2C_Handle i2cHandle = (I2C_Handle)handle;

    /* Initializes the I2C transaction structure with default values */
    I2C_Transaction_init(&transaction);

    transaction.targetAddress = slaveAddr;
    transaction.writeBuf     = &tx[0];
    transaction.writeCount   = 1;
    transaction.readBuf      = &tx[1];
    transaction.readCount    = 1;
    transaction.timeout      = i2cTimeout;

    tx[0] = regAddr;

    status = I2C_transfer(i2cHandle, &transaction);
    *regData     = tx[1];

    return status;
}

int32_t Board_i2c8BitRegWrSingle(void *handle,
                                 uint32_t slaveAddr,
                                 uint8_t *regData,
                                 uint32_t i2cTimeout)
{
    uint8_t tx[5];
    int32_t status=0;

    I2C_Transaction transaction;

    I2C_Handle i2cHandle = (I2C_Handle)handle;

    /* Initializes the I2C transaction structure with default values */
    I2C_Transaction_init(&transaction);

    transaction.targetAddress = slaveAddr;
    transaction.writeBuf     = &tx[0];
    transaction.writeCount   = 1;
    transaction.readBuf      = NULL;
    transaction.readCount    = 0;
    transaction.timeout      = i2cTimeout;

    tx[0] = *regData;

    status = I2C_transfer(i2cHandle, &transaction);

    return status;
}

int32_t Board_i2c8BitRegRdSingle(void *handle,
                                 uint32_t slaveAddr,
                                 uint8_t *regData,
                                 uint32_t i2cTimeout)
{
    uint8_t tx[5];
    int32_t status=0;

    I2C_Transaction transaction;

    I2C_Handle i2cHandle = (I2C_Handle)handle;

    /* Initializes the I2C transaction structure with default values */
    I2C_Transaction_init(&transaction);

    transaction.targetAddress = slaveAddr;
    transaction.writeBuf     = NULL;
    transaction.writeCount   = 0;
    transaction.readBuf      = &tx[0];
    transaction.readCount    = 1;
    transaction.timeout      = i2cTimeout;

    status = I2C_transfer(i2cHandle, &transaction);
    *regData = tx[0];

    return status;
}

int32_t Board_i2c16BitRegWr(void *handle,
                            uint32_t slaveAddr,
                            uint16_t regAddr,
                            uint8_t *regData,
                            uint8_t numOfBytes,
                            uint8_t byteOrdSel,
                            uint32_t i2cTimeout)
{
    uint8_t tx[6];
    uint8_t *txPtr = NULL;
    int32_t status=0;

    I2C_Transaction transaction;

    I2C_Handle i2cHandle = (I2C_Handle)handle;

    /* Initializes the I2C transaction structure with default values */
    I2C_Transaction_init(&transaction);

    transaction.targetAddress = slaveAddr;
    transaction.writeBuf     = &tx[0];
    transaction.writeCount   = (numOfBytes + 2);
    transaction.readBuf      = NULL;
    transaction.readCount    = 0;
    transaction.timeout      = i2cTimeout;

    /* 16-bit regAddr data to be sent */
    {
        tx[0] = (uint8_t)((regAddr & 0xFF00) >> 8);
        tx[1] = (uint8_t)(regAddr & 0x00FF);
    }

    txPtr = &tx[2];
    /* regData to be sent */
    while(numOfBytes)
    {
        *txPtr = *regData;
        txPtr++;
        regData++;
        numOfBytes--;
    }

    status =   I2C_transfer(i2cHandle, &transaction);

    return status;
}

int32_t Board_i2c16BitRegRd(void   *handle,
                                 uint32_t slaveAddr,
                                 uint16_t regAddr,
                                 uint8_t *regData,
                                 uint8_t numOfBytes,
                                 uint8_t byteOrdSel,
                                 uint32_t i2cTimeout)
{
    int32_t ret = 0;
    I2C_Transaction transaction;
    uint8_t tx[2];

    I2C_Handle i2cHandle = (I2C_Handle)handle;

    /* Initializes the I2C transaction structure with default values */
    I2C_Transaction_init(&transaction);

    transaction.targetAddress = slaveAddr;
    transaction.writeBuf     = &tx[0];
    transaction.writeCount   = 2;
    transaction.readBuf      = NULL;
    transaction.readCount    = 0;
    transaction.timeout      = i2cTimeout;

    /* 16-bit regAddr data to be sent */
    if(byteOrdSel == BOARD_I2C_REG_ADDR_MSB_FIRST)
    {
        tx[0] = (uint8_t)((regAddr & 0xFF00) >> 8);
        tx[1] = (uint8_t)(regAddr & 0x00FF);
    }
    else
    {
        tx[0] = (uint8_t)(regAddr & 0x00FF);
        tx[1] = (uint8_t)((regAddr & 0xFF00) >> 8);
    }

    ret = I2C_transfer(i2cHandle, &transaction);
    if(ret != I2C_STS_SUCCESS)
    {
        DebugP_log("Failing while transmitting the rd reg addr with error code - %d\n", ret);
        ret = -1;
    }

    if (ret == I2C_STS_SUCCESS)
    {
        transaction.writeBuf     = NULL;
        transaction.writeCount   = 0;
        transaction.readBuf      = regData;
        transaction.readCount    = numOfBytes;

        ret = I2C_transfer(i2cHandle, &transaction);
        if(ret != I2C_STS_SUCCESS)
        {
            DebugP_log("Failing while reading the register data by returning - %d\n", ret);
            ret = -1;
        }
    }
    return ret;
}

void Board_DSIBridgeErrorRegRead(I2C_Handle i2cHandle)
{
    int i = 0;
    uint8_t readVal;

    for(i = 0xF0; i < 0xF8; i++)
    {
        Board_i2c8BitRegRd(i2cHandle,
                           0x2C,
                           i & 0xFF,
                           &readVal,
                           1,
                           I2C_TRANSACTION_TIMEOUT);
        if (0 != readVal)
        {
            DebugP_log("Status at 0x%x in the SN65DSI bridge is 0x%x...\n", i, readVal);
        }
    }
}

/**
 * \brief Board control function
 *
 * \param   cmd  [IN]  Board control command
 * \param   arg  [IN]  Control command argument.
 *                     Changes based on the command
 *
 * \return   0 if the given operation detected else -1.
 *
 */
int32_t Board_control(uint32_t cmd, void *arg)
{
    int32_t status;

    switch (cmd)
    {
        case BOARD_CTRL_CMD_CFG_HDMI:
            status = Board_configHdmi((BOARD_HdmiCfg_t *)arg);
            break;

        case BOARD_CTRL_CMD_CFG_DSI2DP_BRIDGE:
            status = Board_configDSI2DPBridge((BOARD_DSI2DPBridgeCfg_t *)arg);
            break;

        default:
            status = -1;
            break;
    }

    return (status);
}
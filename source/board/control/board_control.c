/*
 *  Copyright (C) 2023-25 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BOARD_CSI_IOEXP_ADDR                (0x23)
#define BOARD_CSI_IOEXP_PIN_NUM             (0x0)
#define I2C_TRANSACTION_TIMEOUT             (2000U)

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

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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <drivers/hw_include/csl_types.h>
#include <kernel/dpl/ClockP.h>
#include <board/pmic/pmic_i2c.h>

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PMIC_i2cRead(Pmic_CoreHandle_t  *pmicCorehandle,
                          uint8_t             instType,
                          uint16_t            regAddr,
                          uint8_t            *pRxBuf,
                          uint8_t             bufLen)
{
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[PMIC_IO_BUF_SIZE + 1];
    int32_t status = SystemP_SUCCESS;
    uint32_t slaveAdd = 0U;
    I2C_Handle i2cCommHandle = NULL;

    if(pmicCorehandle == NULL)
    {
        return PMIC_ST_ERR_INV_HANDLE;
    }

    if(bufLen == 0)
    {
        return PMIC_ST_ERR_INV_PARAM;
    }

    if(pRxBuf == NULL)
    {
        return PMIC_ST_ERR_NULL_PARAM;
    }

    if (0U != (regAddr & PMIC_WDG_PAGEADDR))
    {
        /* Update watchdog register address */
        regAddr = (regAddr & PMIC_WDG_PAGEADDR_MASK);
        instType = PMIC_QA_INST;
    }

    if(instType == PMIC_MAIN_INST)
    {
        slaveAdd = pmicCorehandle->slaveAddr;
        i2cCommHandle = (I2C_Handle)pmicCorehandle->pCommHandle;
    }
    else if (instType == PMIC_NVM_INST)
    {
        slaveAdd = pmicCorehandle->nvmSlaveAddr;
        i2cCommHandle = (I2C_Handle)pmicCorehandle->pCommHandle;

    }
    else if (instType == PMIC_QA_INST)
    {
        slaveAdd = pmicCorehandle->qaSlaveAddr;
        if (pmicCorehandle->commMode == PMIC_INTF_DUAL_I2C)
        {
            i2cCommHandle = (I2C_Handle)pmicCorehandle->pQACommHandle;
        }
        else
        {
            i2cCommHandle = (I2C_Handle)pmicCorehandle->pCommHandle;
        }
    }
    else
    {
        return PMIC_ST_ERR_INV_PARAM;
    }

    /* Send the register address to be read */
    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.writeCount = 1U;
    i2cTransaction.targetAddress = slaveAdd;
    txBuffer[0] = (uint8_t)(regAddr);
    status = I2C_transfer(i2cCommHandle, &i2cTransaction);
    if(status == SystemP_SUCCESS)
    {
        /* Read the register */
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.readBuf = pRxBuf;
        i2cTransaction.readCount = bufLen;
        i2cTransaction.targetAddress = slaveAdd;
        status = I2C_transfer(i2cCommHandle, &i2cTransaction);
    }

    if(status != SystemP_SUCCESS)
    {
        return PMIC_ST_ERR_I2C_COMM_FAIL;
    }
    else
    {
        return PMIC_ST_SUCCESS;
    }
}

int32_t PMIC_i2cWrite(Pmic_CoreHandle_t  *pmicCorehandle,
                           uint8_t             instType,
                           uint16_t            regAddr,
                           uint8_t            *pTxBuf,
                           uint8_t             bufLen)
{

    int32_t  status = SystemP_SUCCESS;
    I2C_Transaction i2cTransaction;
    uint8_t         txBuffer[PMIC_IO_BUF_SIZE + 1] = {0};
    uint32_t slaveAdd = 0U;
    I2C_Handle i2cCommHandle = NULL;

    if(pmicCorehandle == NULL)
    {
        return PMIC_ST_ERR_INV_HANDLE;
    }

    if(bufLen == 0)
    {
        return PMIC_ST_ERR_INV_PARAM;
    }

    if(pTxBuf == NULL)
    {
        return PMIC_ST_ERR_NULL_PARAM;
    }

    if (0U != (regAddr & PMIC_WDG_PAGEADDR))
    {
        /* Update watchdog register address */
        regAddr = (regAddr & PMIC_WDG_PAGEADDR_MASK);
        instType = PMIC_QA_INST;
    }

    if(instType == PMIC_MAIN_INST)
    {
        slaveAdd = pmicCorehandle->slaveAddr;
        i2cCommHandle = (I2C_Handle)pmicCorehandle->pCommHandle;
    }
    else if (instType == PMIC_NVM_INST)
    {
        slaveAdd = pmicCorehandle->nvmSlaveAddr;
        i2cCommHandle = (I2C_Handle)pmicCorehandle->pCommHandle;

    }
    else if (instType == PMIC_QA_INST)
    {
        slaveAdd = pmicCorehandle->qaSlaveAddr;
        if (pmicCorehandle->commMode == PMIC_INTF_DUAL_I2C)
        {
            i2cCommHandle = (I2C_Handle)pmicCorehandle->pQACommHandle;
        }
        else
        {
            i2cCommHandle = (I2C_Handle)pmicCorehandle->pCommHandle;
        }
    }
    else
    {
        return PMIC_ST_ERR_INV_PARAM;
    }

    /* Send the register address and data to be written */
    I2C_Transaction_init(&i2cTransaction);
    txBuffer[0] = (uint8_t)(regAddr);
    memcpy(&txBuffer[1U], pTxBuf, bufLen);
    i2cTransaction.writeBuf     = txBuffer;
    i2cTransaction.writeCount   = bufLen + 1U; /* data length + 1-byte register address */
    i2cTransaction.readCount    = 0U;
    i2cTransaction.readBuf      = NULL;
    i2cTransaction.targetAddress = slaveAdd;

    status = I2C_transfer(i2cCommHandle, &i2cTransaction);
    if(status != SystemP_SUCCESS)
    {
        return PMIC_ST_ERR_I2C_COMM_FAIL;
    }
    else
    {
        return PMIC_ST_SUCCESS;
    }
}

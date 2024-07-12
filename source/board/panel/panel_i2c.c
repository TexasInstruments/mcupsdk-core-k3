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
 *  \file panel_i2c.c
 *
 *  \brief Panel API file to read and write using I2C interface.
 *
 */


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <board/panel.h>
#include <drivers/i2c.h>

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

int32_t Panel_i2cBridgeWrite(uint32_t instanceIndex, uint32_t i2cAddr,
                             const uint8_t *regAddr, const uint8_t* regVal,
                             uint32_t numRegs)
{
    int32_t status = SystemP_SUCCESS;
    I2C_Transaction i2cTransaction;
    I2C_Handle i2cInstHandle = NULL;
    uint8_t writeBuf[2] = {0U};

    i2cInstHandle = I2C_getHandle(instanceIndex);

    if(i2cInstHandle != NULL)
    {
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.writeBuf = writeBuf;
        i2cTransaction.writeCount = sizeof(writeBuf);
        i2cTransaction.targetAddress = i2cAddr;

        for(uint32_t count = 0U; count < numRegs; count++)
        {
            writeBuf[0] = regAddr[count];
            writeBuf[1] = regVal[count];

            status = I2C_transfer(i2cInstHandle, &i2cTransaction);

            if(status != SystemP_SUCCESS)
            {
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

int32_t Panel_i2cBridgeRead(uint32_t instanceIndex, uint32_t i2cAddr,
                             const uint8_t *regAddr, const uint8_t* regVal,
                             uint32_t numRegs)
{
    int32_t status = SystemP_SUCCESS;
    I2C_Transaction i2cTransaction;
    I2C_Handle i2cInstHandle = NULL;
    uint8_t writeBuf = 0U;

    i2cInstHandle = I2C_getHandle(instanceIndex);

    if(i2cInstHandle != NULL)
    {
        for(uint32_t count = 0U; count < numRegs; count++)
        {
            I2C_Transaction_init(&i2cTransaction);
            i2cTransaction.writeBuf = &writeBuf;
            i2cTransaction.writeCount = sizeof(writeBuf);
            i2cTransaction.targetAddress = i2cAddr;
            writeBuf = regAddr[count];

            status = I2C_transfer(i2cInstHandle, &i2cTransaction);

            if(status == SystemP_SUCCESS)
            {
                I2C_Transaction_init(&i2cTransaction);
                i2cTransaction.targetAddress = i2cAddr;
                i2cTransaction.readBuf = (void*)&regVal[count];
                i2cTransaction.readCount = 1U;
                status = I2C_transfer(i2cInstHandle, &i2cTransaction);
            }

            if(status != SystemP_SUCCESS)
            {
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
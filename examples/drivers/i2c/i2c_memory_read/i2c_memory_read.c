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

#include <drivers/i2c.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

extern uint32_t Board_i2cGetEepromDeviceAddr(void);
extern uint16_t Board_i2cGetEepromMemAddr(void);

#define I2C_MEM_READ_APP_READ_LEN                    (1U)
#define I2C_MEM_READ_APP_WRITE_LEN                   (3U)
#define I2C_MEM_READ_APP_SAMPLE_DATA                 (0x10)

void i2c_memory_read_main(void *arg)
{
    int32_t         status;
    uint32_t        i2cDeviceAddr;
    uint32_t        i2cEepromMemAddr;

    uint8_t         txBuffer[I2C_MEM_READ_APP_WRITE_LEN];
    uint8_t         rxBuffer[I2C_MEM_READ_APP_READ_LEN];

    uint32_t        count = 0;

    I2C_Handle      i2cHandle;
    I2C_Transaction i2cTransaction;

    i2cDeviceAddr = Board_i2cGetEepromDeviceAddr();
    i2cEepromMemAddr = (uint32_t)Board_i2cGetEepromMemAddr();

    i2cHandle = gI2cHandle[CONFIG_I2C0];

    DebugP_log("[I2C] Writing data to EEPROM ... !!!\r\n");

    /* Set default transaction parameters */
    I2C_Transaction_init(&i2cTransaction);

    /* Override with required transaction parameters */
    i2cTransaction.targetAddress = i2cDeviceAddr;
    i2cTransaction.writeBuf     = txBuffer;
    i2cTransaction.writeCount   = I2C_MEM_READ_APP_WRITE_LEN;

    txBuffer[0] = (uint8_t)((i2cEepromMemAddr & (uint32_t)0xFF00) >> 8U);
    txBuffer[1] = (uint8_t)(i2cEepromMemAddr & (uint32_t)0x00FF);
    txBuffer[2] = I2C_MEM_READ_APP_SAMPLE_DATA;

    /* Initiate memory write transfer operation */
    status = I2C_transfer(i2cHandle, &i2cTransaction);

    ClockP_usleep(4000);

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("[I2C] Reading data from EEPROM ... !!!\r\n");

        /* Set default transaction parameters */
        I2C_Transaction_init(&i2cTransaction);

        /* Override with required transaction parameters */
        i2cTransaction.targetAddress = i2cDeviceAddr;
        i2cTransaction.writeBuf     = txBuffer;
        i2cTransaction.writeCount   = I2C_MEM_READ_APP_WRITE_LEN-1;
        i2cTransaction.readBuf      = rxBuffer;
        i2cTransaction.readCount    = I2C_MEM_READ_APP_READ_LEN;

        txBuffer[0] = (uint8_t)((i2cEepromMemAddr & (uint32_t)0xFF00) >> 8U);
        txBuffer[1] = (uint8_t)(i2cEepromMemAddr & (uint32_t)0x00FF);

        /* Initiate memory read transfer operation */
        status = I2C_transfer(i2cHandle, &i2cTransaction);
    }

    if(status == SystemP_SUCCESS)
    {
        for(count = 0; count < I2C_MEM_READ_APP_READ_LEN; count++)
        {
            DebugP_log("[I2C] Data at address 0x%x : 0x%x \r\n", (i2cEepromMemAddr), rxBuffer[count]);

            if (rxBuffer[count] == I2C_MEM_READ_APP_SAMPLE_DATA)
            {
                status = I2C_STS_SUCCESS;
            }
            else
            {
                status = I2C_STS_ERR;
            }
        }
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    return;
}

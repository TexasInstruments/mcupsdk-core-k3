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

#include <board/ioexp/ioexp_tca6424.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct {
    uint8_t reg;
    uint8_t val;
} Adc_RegCfg;

typedef struct {
    uint8_t reg;
    uint8_t val;
} Dac_RegCfg;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Dac_RegCfg gPcm6240Reg[] =
{
    /* Page select 0 */
    {0x00, 0x00},
    /* Reset */
    {0x01, 0x01},
    /* Page select 0 */
    {0x00, 0x00},
    /* Disable sleep */
    {0x02, 0x81},
    /* 1 BCLK delay between FSYNC and data */
    {0x08, 0x01},
    /* Set BCLK/FSYNC ratio. 48KHz */
    {0x14, 0x46},
    /* GPIO1 config */
    {0x21, 0x02},
    /* GPIO2 config */
    {0x22, 0x02},
    /* GPIO3 config */
    {0x23, 0x02},
    /* Set micbias to 5v */
    {0x3b, 0x70},
    /* CH1 Microphone input */
    {0x3c, 0x80},
    /* CH2 Microphone input */
    {0x41, 0x80},
    /* CH3 Microphone input */
    {0x46, 0x80},
    /* CH4 Microphone input */
    {0x4b, 0x80},
    /* Input channel enable */
    {0x74, 0xf0},
    /* Power up micbias and power up all ADC channels */
    {0x75, 0xc0},
};

Adc_RegCfg gTad5212Reg[] =
{
    /* Page select 0 */
    {0x00, 0x00},
    /* Reset */
    {0x00, 0x01},
    {0x7F, 0x00},
    /* Disable sleep mode */
    {0x02, 0x01},
    /* I2S, 32b mode */
    {0x1A, 0x70},
    /* 1b delay between FSYNC and data */
    {0x26, 0x01},
    /* CH1 - Input from DAC, Mono single ended output at OUT1M */
    {0x64, 0x28},
    /* CH1 - Headphone with 4ohm impedence, 0dB gain */
    {0x65, 0x60},
    /* CH1 - +27dB gain */
    {0x67, 0xFF},
    /* CH2 - Input from DAC, Mono single ended output at OUT1M */
    {0x6B, 0x28},
    /* CH2 - Headphone with 4ohm impedence, 0dB gain */
    {0x6C, 0x60},
    /* CH2 - +27dB gain */
    {0x6E, 0xFF},
    /* Enable output CH1 CH2 */
    {0x76, 0x0C},
    /* Page select 1 */
    {0x00, 0x01},
    {0x0a, 0x10},
    {0x1a, 0x40},
    {0x24, 0x06},
    {0x2d, 0x05},
    {0x2f, 0x07},
    {0x30, 0x07},
    {0x47, 0x00},
    {0x48, 0x00},
    {0x4a, 0xb0},
    {0x53, 0x80},
    /* Page Select 3 */
    {0x00, 0x03},
    {0x38, 0x24},
    {0x39, 0x28},
    {0x3a, 0x26},
    {0x3b, 0x20},
    {0x3c, 0x00},
    {0x3d, 0x00},
    {0x3e, 0x09},
    {0x48, 0x01},
    {0x49, 0x01},
};

/* ========================================================================== */
/*                          Function Declerations                             */
/* ========================================================================== */

/* Configure PCM6240 */
int32_t Board_adcConfig(I2C_Handle handle, uint8_t devAddr);
/* Configure TAD5212 */
int32_t Board_dacConfig(I2C_Handle handle, uint8_t devAddr);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Board_codecConfig(void)
{
    int32_t status = SystemP_SUCCESS;
    TCA6424_Config TCA6424_IOexp_config;

#if 0
    /* Configure TAD5212 instances */
    {
        I2C_Handle      i2cHandle;
        i2cHandle = gI2cHandle[CONFIG_I2C0];

        status = Board_dacConfig(i2cHandle, 0x50);
        DebugP_assert(status == SystemP_SUCCESS);

        status = Board_dacConfig(i2cHandle, 0x51);
        DebugP_assert(status == SystemP_SUCCESS);

        status = Board_dacConfig(i2cHandle, 0x52);
        DebugP_assert(status == SystemP_SUCCESS);

        status = Board_dacConfig(i2cHandle, 0x53);
        DebugP_assert(status == SystemP_SUCCESS);
    }

    /* Configure PCM6240 instances */
    {
        I2C_Handle      i2cHandle;
        i2cHandle = gI2cHandle[CONFIG_I2C0];

        status = Board_adcConfig(i2cHandle, 0x90);
        DebugP_assert(status == SystemP_SUCCESS);

        status = Board_adcConfig(i2cHandle, 0x92);
        DebugP_assert(status == SystemP_SUCCESS);
    }
#endif

    /* Route mcasp signals to header */
    TCA6424_Params  tca6424Params;
    TCA6424_Params_init(&tca6424Params);
    tca6424Params.i2cInstance = 0;
    tca6424Params.i2cAddress = 0x22;
    status = TCA6424_open(&TCA6424_IOexp_config, &tca6424Params);

    status += TCA6424_config(&TCA6424_IOexp_config, 21, TCA6424_MODE_OUTPUT);

    status += TCA6424_setOutput(&TCA6424_IOexp_config, 21, TCA6424_OUT_STATE_LOW);

    return status;
}

int32_t Board_dacConfig(I2C_Handle handle, uint8_t devAddr)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t count = sizeof(gTad5212Reg)/sizeof(Adc_RegCfg);
    uint32_t i = 0;
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[2];

    status = I2C_probe(handle, devAddr);
    DebugP_assert(status == SystemP_SUCCESS);

    for(i = 0; i < count; i++)
    {
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.writeBuf   = txBuffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.slaveAddress = devAddr;
        txBuffer[0] = gTad5212Reg[i].reg;
        txBuffer[1] = gTad5212Reg[i].val;
        status = I2C_transfer(handle, &i2cTransaction);

        if(status != SystemP_SUCCESS)
        {
            break;
        }

        ClockP_usleep(10);
    }

    return status;
}

int32_t Board_adcConfig(I2C_Handle handle, uint8_t devAddr)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t count = sizeof(gPcm6240Reg)/sizeof(Dac_RegCfg);
    uint32_t i = 0;
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[2];

    status = I2C_probe(handle, devAddr);
    DebugP_assert(status == SystemP_SUCCESS);

    for(i = 0; i < count; i++)
    {
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.writeBuf   = txBuffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.slaveAddress = devAddr;
        txBuffer[0] = gPcm6240Reg[i].reg;
        txBuffer[1] = gPcm6240Reg[i].val;
        status = I2C_transfer(handle, &i2cTransaction);

        if(status != SystemP_SUCCESS)
        {
            break;
        }

        ClockP_usleep(10);
    }

    return status;
}

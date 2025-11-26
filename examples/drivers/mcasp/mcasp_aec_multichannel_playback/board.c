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

#include <kernel/dpl/ClockP.h>
#include "ti_drivers_open_close.h"
#include <drivers/pinmux.h>
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TAS0_DEVICE_ADDRESS (0x70U)
#define TAS1_DEVICE_ADDRESS (0x71U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct {
    uint8_t reg;
    uint8_t val;
} Amp_RegCfg;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Amp_RegCfg gTas6754Reg_TAS0[] =
{
    /* Book 0x00 */
    {0x00, 0x00},
    {0x7f, 0x00},
    {0x00, 0x00},

    /* Clock Polarity */
    {0x20, 0x00},

    /* TDM Mode */
    {0x21, 0x14},

    /* Clear Fault */
    {0x01, 0x08},

    /* Input Word Length */
    {0x23, 0x0f},

    /* Output Word Length */
    {0x25, 0x0f},

    /* MSB offset of input audio */
    {0x27, 0x10},

    /* LSB offset of Ch1-4 */
    {0x28, 0x00},

    /* LSB offset of LL Ch1-4 */
    {0x29, 0xff},

    /* MSB offset of output audio */
    {0x2c, 0xf0},

    /* V-predict LSB offset */
    {0x2d, 0xff},

    /* ISense LSB offset */
    {0x2e, 0xff},

    /* Output data type in SDOUT */
    {0x31, 0x00},

    /* LL path enable/disable */
    {0x32, 0x00},

    /* Digital Volume control */
    {0x43, 0x60},
    {0x42, 0x60},
    {0x41, 0x60},
    {0x40, 0x60},

    /* Enable fault warnings */
    {0x7c, 0x0f},
    {0x92, 0x7e},
    {0x94, 0xf3},

    /* BCK Detection */
    {0x1e, 0x74},

    /* Configure GPIO */
    {0x95, 0x00},
    {0x96, 0x00},

    /* Disable DC Detect */
    {0x06, 0x01},

    /* Configure CH1,CH2.CH3,CH4 to PLAY state */
    {0x03, 0x44},
    {0x04, 0x44},
};

Amp_RegCfg gTas6754Reg_TAS1[] =
{
    /* Book 0x00 */
    {0x00, 0x00},
    {0x7f, 0x00},
    {0x00, 0x00},

    /* Clock Polarity */
    {0x20, 0x00},

    /* TDM Mode */
    {0x21, 0x14},

    /* Clear Fault */
    {0x01, 0x08},

    /* Input Word Length */
    {0x23, 0x0f},

    /* Output Word Length */
    {0x25, 0x0f},

    /* MSB offset of input audio */
    {0x27, 0x10},

    /* LSB offset of Ch1-4 */
    {0x28, 0x80},

    /* LSB offset of LL Ch1-4 */
    {0x29, 0xff},

    /* MSB offset of output audio */
    {0x2c, 0xf0},

    /* V-predict LSB offset */
    {0x2d, 0xff},

    /* ISense LSB offset */
    {0x2e, 0xff},

    /* Output data type in SDOUT */
    {0x31, 0x00},

    /* LL path enable/disable */
    {0x32, 0x00},

    /* Digital Volume control */
    {0x43, 0x60},
    {0x42, 0x60},
    {0x41, 0x60},
    {0x40, 0x60},

    /* Enable fault warnings */
    {0x7c, 0x0f},
    {0x92, 0x7e},
    {0x94, 0xf3},

    /* BCK Detection */
    {0x1e, 0x74},

    /* Configure GPIO */
    {0x95, 0x00},
    {0x96, 0x00},

    /* Disable DC Detect */
    {0x06, 0x01},

    /* Configure CH1,CH2.CH3,CH4 to PLAY state */
    {0x03, 0x44},
    {0x04, 0x44},
};

uint8_t txBuffer[2];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Configure TAS6754 */
static int32_t Board_ampConfig(I2C_Handle handle, uint8_t devAddr);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Board_codecConfig(void)
{
    int32_t status = SystemP_SUCCESS;
    I2C_Handle      i2cHandle;
    uint32_t    gpioBaseAddr, pinNum;

    /* Configure AEC1 - TAS6754 instances */
    {
        /* Drive STBY Pins on AEC1 to be HIGH using GPIO */

        gpioBaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(GPIO_STBY_AEC1_TAS0_BASE_ADDR);
        pinNum       = GPIO_STBY_AEC1_TAS0_PIN;
        GPIO_setDirMode(gpioBaseAddr, pinNum, GPIO_STBY_AEC1_TAS0_DIR);
        GPIO_pinWriteHigh(gpioBaseAddr, pinNum);

        gpioBaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(GPIO_STBY_AEC1_TAS1_BASE_ADDR);
        pinNum       = GPIO_STBY_AEC1_TAS1_PIN;
        GPIO_setDirMode(gpioBaseAddr, pinNum, GPIO_STBY_AEC1_TAS1_DIR);
        GPIO_pinWriteHigh(gpioBaseAddr, pinNum);

        i2cHandle = gI2cHandle[CONFIG_I2C0];

        /*Configure TAS0*/
        status = Board_ampConfig(i2cHandle, TAS0_DEVICE_ADDRESS);

        /*Configure TAS1*/
        status = Board_ampConfig(i2cHandle, TAS1_DEVICE_ADDRESS);

        DebugP_assert(status == SystemP_SUCCESS);
    }

    /* Configure AEC2 - TAS6754 instances */
    {
        /* Drive STBY Pins on AEC2 to be HIGH using GPIO */

        gpioBaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(GPIO_STBY_AEC2_TAS0_BASE_ADDR);
        pinNum       = GPIO_STBY_AEC2_TAS0_PIN;
        GPIO_setDirMode(gpioBaseAddr, pinNum, GPIO_STBY_AEC2_TAS0_DIR);
        GPIO_pinWriteHigh(gpioBaseAddr, pinNum);

        gpioBaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(GPIO_STBY_AEC2_TAS1_BASE_ADDR);
        pinNum       = GPIO_STBY_AEC2_TAS1_PIN;
        GPIO_setDirMode(gpioBaseAddr, pinNum, GPIO_STBY_AEC2_TAS1_DIR);
        GPIO_pinWriteHigh(gpioBaseAddr, pinNum);

        i2cHandle = gI2cHandle[CONFIG_I2C1];

        /*Configure TAS0*/
        status = Board_ampConfig(i2cHandle, TAS0_DEVICE_ADDRESS);

        /*Configure TAS1*/
        status = Board_ampConfig(i2cHandle, TAS1_DEVICE_ADDRESS);

        DebugP_assert(status == SystemP_SUCCESS);
    }

    return status;
}

static int32_t Board_ampConfig(I2C_Handle handle, uint8_t devAddr)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i = 0;

    uint32_t count = sizeof(gTas6754Reg_TAS0)/sizeof(Amp_RegCfg);
    I2C_Transaction i2cTransaction;
    status = I2C_probe(handle, devAddr);
    DebugP_assert(status == SystemP_SUCCESS);

    I2C_Transaction_init(&i2cTransaction);

   /*Configure TAS6754*/
    for(i = 0; i < count; i++)
    {
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.writeBuf   = txBuffer;
        i2cTransaction.writeCount = 2;
        i2cTransaction.targetAddress = devAddr;

        if(devAddr == TAS0_DEVICE_ADDRESS)
        {
            txBuffer[0] = gTas6754Reg_TAS0[i].reg;
            txBuffer[1] = gTas6754Reg_TAS0[i].val;
        }
        else if(devAddr == TAS1_DEVICE_ADDRESS)
        {
            txBuffer[0] = gTas6754Reg_TAS1[i].reg;
            txBuffer[1] = gTas6754Reg_TAS1[i].val;
        }

        status = I2C_transfer(handle, &i2cTransaction);

        if(status != SystemP_SUCCESS)
        {
            break;
        }

        ClockP_usleep(100);
    }

    DebugP_assert(status == SystemP_SUCCESS);

    return status;
}

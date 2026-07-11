/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct {
    uint16_t reg;
    uint16_t val;
} Clockgen_RegCfg;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* CDCE6214 Clock Generator Configuration for 96 kHz output
 * Generates 96 kHz sampling frequency for AASRC external clock test
 * Configuration uses internal PLL and output dividers to produce the target frequency
 */
Clockgen_RegCfg gCdce6214Reg[] = {
    /* Reserved */
    {0x55, 0x0000},
    {0x54, 0x0000},
    {0x53, 0x0000},
    {0x52, 0x0000},
    /* Masks Analog Lock Detect */
    {0x51, 0x0004},
    /* Reserved */
    {0x50, 0x0000},
    /* Slew rate Control */
    {0x4F, 0x0208},
    /* Disable CMOS output on OUT0 */
    {0x4E, 0x1000},
    /* Channel 4 LVDS common-mode trim decrement */
    {0x4D, 0x0000},
    /* Channel 4 differential buffer current bias */
    {0x4C, 0x0008},
    /* Diables LVDS & CMOS Output */
    {0x4B, 0x0008},
    /* Reserved */
    {0x4A, 0xA181},
    /* Enables LP-HCSL output buffer for Channel OUT4 */
    {0x49, 0x2000},
    /* CH4 Divider */
    {0x48, 0x0006},
    /* Channel 3 differential buffer current bias */
    {0x47, 0x0000},
    /* Disables LVDS output on OUT3 */
    {0x46, 0x0008},
    /* Reserved */
    {0x45, 0xA181},
    /* Disable CH3 Output Sync */
    {0x44, 0x2000},
    /* Integer Divider Division Value of Channel OUT3 */
    {0x43, 0x0006},
    /* Channel 2 differential buffer current bias trim */
    {0x42, 0x0000},
    /* Channel 2 LVDS common-mode trim decrement */
    {0x41, 0x0008},
    /* Reserved */
    {0x40, 0xA181},
    /* Disable CH2 Output Sync */
    {0x3F, 0x2000},
    /* CH2 Divider */
    {0x3E, 0x0006},
    /* Reserved */
    {0x3D, 0x0000},
    /* Channel 1 differential buffer current bias trim */
    {0x3C, 0x6008},
    /* Enables LVDS output on OUT1 */
    {0x3B, 0x8008},
    /* Reserved */
    {0x3A, 0x502C},
    /* Disable CH1 Output Sync */
    {0x39, 0x1000},
    /* CH1 Divider */
    {0x38, 0x0020},
    /* PLL Loop filter 3rd Order Pole Cap - 1.2 pF and Res to 0 kOhm */
    {0x37, 0x001E},
    /* Reserved */
    {0x36, 0x3400},
    /* Disables charge pump */
    {0x35, 0x0069},
    /* Reserved */
    {0x34, 0x5000},
    /* Dual PFD Type */
    {0x33, 0x40C0},
    /* PLL Lock detect time to 8.9 ns */
    {0x32, 0x01C0},
    /* Configure PLL Loop filter zero capacitor */
    {0x31, 0x0013},
    /* Configure PLL Loop filter resistor and capacitor */
    {0x30, 0x1A14},
    /* Configure down current of PLL_CP */
    {0x2F, 0x0A00},
    /* Reserved */
    {0x2E, 0x0000},
    {0x2D, 0x4F80},
    {0x2C, 0x0318},
    /* Frequency Step size of DCO Mode */
    {0x2B, 0x0051},
    /* SSC Profile - 25 MHz PFD, 0.5% spread*/
    {0x2A, 0x0002},
    /* Disables SSC */
    {0x29, 0x0000},
    /* Reserved */
    {0x28, 0x0000},
    {0x27, 0x0000},
    {0x26, 0x0000},
    {0x25, 0x0000},
    {0x24, 0x0000},
    {0x23, 0x0000},
    /* MSB of sigma delta denominator */
    {0x22, 0x0000},
    /* LSB of sigma delta denominator */
    {0x21, 0x2710},
    /* MSB of sigma delta numerator */
    {0x20, 0x0000},
    /* LSB of sigma delta numerator */
    {0x1F, 0x0000},
    /* PLL-N Divider */
    {0x1E, 0x0030},
    /* Reserved */
    {0x1D, 0x0000},
    {0x1C, 0x0000},
    /* Sigma Delta Modulator in Integer Mode */
    {0x1B, 0x0005},
    /* Reserved */
    {0x1A, 0x0000},
    /* Clock Mux */
    {0x19, 0x0400},
    /* Nominal Gm of XO to 884 uA */
    {0x18, 0x0024},
    /* Reserved */
    {0x17, 0x0000},
    {0x16, 0x0000},
    {0x15, 0x0000},
    {0x14, 0x0000},
    {0x13, 0x0000},
    {0x12, 0x0000},
    {0x11, 0x26C4},
    {0x10, 0x921F},
    /* Mute Output during calibration */
    {0x0F, 0xA037},
    /* NVM Write Data */
    {0x0E, 0x0000},
    /* NVM Write Address */
    {0x0D, 0x0000},
    /* NVM Read Data */
    {0x0C, 0x0000},
    /* NVM Read Address */
    {0x0B, 0x0000},
    /* Stored CRC Value */
    {0x0A, 0x0000},
    /* Live CRC Byte */
    {0x09, 0x0000},
    /* Reserved */
    {0x08, 0x0000},
    /* NVM CRC Error Status */
    {0x07, 0x0000},
    /* Reserved */
    {0x06, 0x0000},
    /* Configure Prescalar */
    {0x05, 0x0008},
    /* Control CH1-LDO Power Up and remaining down */
    {0x04, 0x00E0},
    /* CRC & NVM Config */
    {0x03, 0x0000},
    /* Reference clock selection */
    {0x02, 0x0002},
    /* GPIO input selection */
    {0x01, 0x2310},
    /* GPIO1 as output and re-calibrate the PLL */
    {0x00, 0x1010},
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Board_clockgenConfig(I2C_Handle handle, uint8_t devAddr)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t count = sizeof(gCdce6214Reg)/sizeof(Clockgen_RegCfg);
    uint32_t i = 0;
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[4];

    if(handle != NULL)
    {
        status = I2C_probe(handle, devAddr);
        DebugP_assert(status == SystemP_SUCCESS);

        for(i = 0; i < count; i++)
        {
            I2C_Transaction_init(&i2cTransaction);
            i2cTransaction.writeBuf   = (uint8_t *)txBuffer;
            i2cTransaction.writeCount = 4;
            i2cTransaction.targetAddress = devAddr;
            txBuffer[0] = (uint8_t)((gCdce6214Reg[i].reg >> 8) & 0xFF);
            txBuffer[1] = (uint8_t)(gCdce6214Reg[i].reg & 0xFF);
            txBuffer[2] = (uint8_t)((gCdce6214Reg[i].val >> 8) & 0xFF);
            txBuffer[3] = (uint8_t)(gCdce6214Reg[i].val & 0xFF);
            status = I2C_transfer(handle, &i2cTransaction);

            if(status != SystemP_SUCCESS)
            {
                break;
            }

            ClockP_usleep(10);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}


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

#include <kernel/dpl/DebugP.h>
#include <board/ioexp/ioexp_tca6424.h>

/* I2C address for IO expander */
#define IO_EXP_ADDR             (0x22U)

/* MCAN STB pins from I/O expander */
#define IO_EXP_MCAN0_STB_PIN  (0x14U)
#define IO_EXP_MCAN1_STB_PIN  (0x15U)

void mcan_enableTransceiver(void)
{
    int32_t status = SystemP_SUCCESS;

    TCA6424_Params TCA6424_IOexp_params =
    {
        .i2cInstance = 0,
        .i2cAddress = IO_EXP_ADDR
    };

    TCA6424_Config TCA6424_IOexp_config;

    status = TCA6424_open(&TCA6424_IOexp_config, &TCA6424_IOexp_params);

    /* Configure MCAN0_STB (P24) as output pin */
    if (status == SystemP_SUCCESS)
    {
        status = TCA6424_config(&TCA6424_IOexp_config, IO_EXP_MCAN0_STB_PIN,
                                TCA6424_MODE_OUTPUT);
    }

    /* Set MCAN0_STB level to LOW for normal mode operation of transceiver */
    if (status == SystemP_SUCCESS)
    {
        status = TCA6424_setOutput(&TCA6424_IOexp_config, IO_EXP_MCAN0_STB_PIN,
                                   TCA6424_OUT_STATE_LOW);
    }

    /*Configure MCAN1_STB (P25) as output pin */
    if (status == SystemP_SUCCESS)
    {
        status = TCA6424_config(&TCA6424_IOexp_config, IO_EXP_MCAN1_STB_PIN,
                                TCA6424_MODE_OUTPUT);
    }

    /* Set MCAN1_STB level to LOW for normal mode operation of transceiver */
    if (status == SystemP_SUCCESS)
    {
        status = TCA6424_setOutput(&TCA6424_IOexp_config, IO_EXP_MCAN1_STB_PIN,
                                   TCA6424_OUT_STATE_LOW);
    }

}
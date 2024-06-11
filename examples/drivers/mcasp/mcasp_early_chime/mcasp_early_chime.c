/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
#include <drivers/i2c.h>
#include <drivers/mcasp.h>
#include <board/ioexp/ioexp_tca6424.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "audio_sample.h"
#include "FreeRTOS.h"
#include "task.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined (SOC_AM62AX) || (SOC_AM62PX)
/* AM62Ax CODEC I2C address */
#define APP_MCASP_CODEC_ADDR    (0x1BU)

/* I2C address for IO expander */
#define IO_EXP_ADDR             (0x22U)

/* Codec reset pin for I/O expander */
#define IO_EXP_CODEC_RESET_PIN  (0x8U)
#endif

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */
#define AIC31_PAGE_SEL_REG                  (0x0U)
#define AIC31_INTERFACE_REG                 (0x9U)

#define AIC31_CODEC_DATA_PATH_REG           (0x7U)
#define AIC32_CLK_SRC_REG                   (0x8U)
#define AIC_OP_POWER_REG                    (0x25U)
#define AIC_DAC_OP_SWITCH_CTRL_REG          (0x29U)
#define AIC_LDAC_VOL_CTRL                   (0x2BU)
#define AIC_RDAC_VOL_CTRL                   (0x2CU)
#define AIC_DAC_L1_HPLOUT_VOL_CTRL_REG      (0x2FU)
#define AIC_HP_LOUT_LEVEL_CTRL_REG          (0x33U)
#define AIC_DAC_R1_HPROUT_VOL_CTRL_REG      (0x40U)
#define AIC_HPROUT_LEVEL_CTRL_REG           (0x41U)

/* ========================================================================== */
/*                        Static Function Declaration                         */
/* ========================================================================== */
/* Reset codec */
static int32_t mcasp_codec_reset(void);
/* Configure codec TLV320AIC31 */
static void mcasp_aic31_codec_config(void);
/* I2C register write for Codec */
static void I2C_writeReg(I2C_Handle handle, uint8_t devAddr, uint8_t reg,
                                    uint8_t val);

MCASP_Transaction txTxn;

static SemaphoreP_Object gSemAudioChime;

void mcasp_chime(void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Handle mcaspHandle;

    SemaphoreP_constructBinary(&gSemAudioChime, 0);

    mcasp_aic31_codec_config();

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    txTxn.buf = (void *)audio_sample;
    txTxn.count = audio_sample_size;
    txTxn.timeout = 0xFFFFFF;
    MCASP_submitTx(mcaspHandle, &txTxn);

    DebugP_log("Starting Chime \r\n");

    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_pend(&gSemAudioChime, SystemP_WAIT_FOREVER);

    DebugP_log("Chime completed\r\n");

    MCASP_Transaction *transaction;
    do {
        transaction = MCASP_withdrawRx(mcaspHandle);
    }while (transaction != NULL);

    MCASP_stopTransferTx(mcaspHandle);
}


static int32_t mcasp_codec_reset(void)
{
    int32_t status = SystemP_SUCCESS;

    TCA6424_Params TCA6424_IOexp_params =
	{
		.i2cInstance = 0,
		.i2cAddress = IO_EXP_ADDR
	};

    TCA6424_Config TCA6424_IOexp_config;

    status = TCA6424_open(&TCA6424_IOexp_config, &TCA6424_IOexp_params);

    if(status == SystemP_SUCCESS)
    {
        status = TCA6424_config(&TCA6424_IOexp_config, IO_EXP_CODEC_RESET_PIN,
                                    TCA6424_MODE_OUTPUT);
    }

    if(status == SystemP_SUCCESS)
    {
        status = TCA6424_setOutput(&TCA6424_IOexp_config, IO_EXP_CODEC_RESET_PIN,
                                    TCA6424_OUT_STATE_LOW);
    }

    /* Wait for codec to reset */
    ClockP_usleep(1);

    if(status == SystemP_SUCCESS)
    {
        status = TCA6424_setOutput(&TCA6424_IOexp_config, IO_EXP_CODEC_RESET_PIN,
                                    TCA6424_OUT_STATE_HIGH);
    }

    return status;
}

static void mcasp_aic31_codec_config(void)
{
    int32_t status = SystemP_FAILURE;
    I2C_Handle      i2cHandle;
    i2cHandle = gI2cHandle[CONFIG_I2C0];
    uint8_t deviceAddress = 0x1B;

    status = mcasp_codec_reset();
    DebugP_assert(status == SystemP_SUCCESS);

    status = I2C_probe(i2cHandle, deviceAddress);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Select Page0 */
    I2C_writeReg(i2cHandle, deviceAddress, AIC31_PAGE_SEL_REG, 0U);

    /* Select codec to be in master mode for FS and BCLK */
    I2C_writeReg(i2cHandle, deviceAddress, AIC32_CLK_SRC_REG, (1U << 6U) | (1U << 7U));

    /* I2S interface */
    I2C_writeReg(i2cHandle, deviceAddress, AIC31_INTERFACE_REG, (0x0U << 6U) | (0x3 << 4U));

    /* Configure data path */
    /* Left DAC datapath plays left and Right path datapath plays right */
    I2C_writeReg(i2cHandle, deviceAddress, AIC31_CODEC_DATA_PATH_REG, 0xA);

    /* DAC setup */
    {
        /* Power up Left and Right DAC with HPLCOM single ended o/p */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_OP_POWER_REG, 0xC0);

        /* Right DAC volume follows left channel control register */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_DAC_OP_SWITCH_CTRL_REG, 0x02);

        /* DAC L1 routed to HPLOUT with HPLOUT gain -8dB */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_DAC_L1_HPLOUT_VOL_CTRL_REG, 0x90);

        /* Unmute HPLOUT and power up HPLOUT. HPLOUT is high impedance when powered down */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_HP_LOUT_LEVEL_CTRL_REG, 0x0D);

        /* DAC R1 routed to HPROUT with HPLOUT gain -8dB */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_DAC_R1_HPROUT_VOL_CTRL_REG, 0x90);

        /* Unmute HPROUT and power up HPROUT. HPROUT is high impedance when powered down */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_HPROUT_LEVEL_CTRL_REG, 0x0D);

        /* Unmute Left DAC with gain -36 dB */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_LDAC_VOL_CTRL, 0x48);

        /* Unmute Right DAC with gain -36 dB */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_RDAC_VOL_CTRL, 0x48);
    }
}

static void I2C_writeReg(I2C_Handle handle, uint8_t devAddr, uint8_t reg,
                                    uint8_t val)
{
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[2];

    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.targetAddress = devAddr;
    txBuffer[0] = reg;
    txBuffer[1] = val;
    I2C_transfer(handle, &i2cTransaction);
}


void mcasp_txcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    SemaphoreP_post(&gSemAudioChime);
}

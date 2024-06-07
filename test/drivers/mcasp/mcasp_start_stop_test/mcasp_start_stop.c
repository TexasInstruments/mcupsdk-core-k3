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
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/i2c.h>
#include <drivers/gpio.h>
#include <drivers/mcasp.h>
#include <board/ioexp/ioexp_tca6424.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Audio buffer settings */
#define APP_MCASP_AUDIO_BUFF_SIZE   (48000U * 5U * 8U)

#if defined (SOC_AM62AX) || defined (SOC_AM62X) || defined (SOC_AM62DX)
/* AM62Ax CODEC I2C address */
#define APP_MCASP_CODEC_ADDR    (0x1BU)

/* I2C address for IO expander */
#define IO_EXP_ADDR             (0x22U)

/* Codec reset pin for I/O expander */
#define IO_EXP_CODEC_RESET_PIN  (0x8U)
#endif

/***************************** Codec Register address *************************/
#define AIC31_PAGE_SEL_REG                  (0x0U)
#define AIC31_INTERFACE_REG                 (0x9U)
#define AIC31_CODEC_DATA_PATH_REG           (0x7U)
#define AIC31_LEFT_PGA_REG                  (0xFU)
#define AIC31_RIGHT_PGA_REG                 (0x10U)
#define AIC31_MIC3_LEFT_ADC_REG             (0x11U)
#define AIC31_MIC3_RIGHT_ADC_REG            (0x12U)
#define AIC31_MICBIAS_CTRL_REG              (0x19U)
#define AIC_LINE1L_TO_LEFT_ADC_REG          (0x13U)
#define AIC_LINE1R_TO_RIGHT_ADC_REG         (0x16U)
#define AIC_OP_POWER_REG                    (0x25U)
#define AIC_DAC_OP_SWITCH_CTRL_REG          (0x29U)
#define AIC_LDAC_VOL_CTRL                   (0x2BU)
#define AIC_RDAC_VOL_CTRL                   (0x2CU)
#define AIC_DAC_L1_HPLOUT_VOL_CTRL_REG      (0x2FU)
#define AIC_HP_LOUT_LEVEL_CTRL_REG          (0x33U)
#define AIC_DAC_R1_HPROUT_VOL_CTRL_REG      (0x40U)
#define AIC_HPROUT_LEVEL_CTRL_REG           (0x41U)

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* Create transaction objects for transmit and Receive */
MCASP_Transaction   gMcaspAudioTxnTx;
MCASP_Transaction   gMcaspAudioTxnRx;

/* Rx received sem */
static SemaphoreP_Object gRxSem;

/* Tx received sem */
static SemaphoreP_Object gTxSem;

uint8_t gMcaspRxBuffer[APP_MCASP_AUDIO_BUFF_SIZE] __attribute__((aligned(256)));

/* ========================================================================== */
/*                        Static Function Declaration                         */
/* ========================================================================== */
/* Reset codec */
static void mcasp_codec_reset(void);
/* Configure codec TLV320AIC31 */
static void mcasp_aic31_codec_config(void);
/* I2C register write for Codec */
static void I2C_writeReg(I2C_Handle handle, uint8_t devAddr, uint8_t reg,
                                    uint8_t val);

void mcasp_start_stop_main(void *args)
{
    int32_t         status = SystemP_SUCCESS;
    MCASP_Handle    mcaspHandle;
    char            valueChar;

    mcasp_aic31_codec_config();

    DebugP_log("[MCASP] Audio stop restart example started.\r\n");

    SemaphoreP_constructBinary(&gRxSem, 0);
    SemaphoreP_constructBinary(&gTxSem, 0);

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    do
    {
        DebugP_log("\r\nStart 5s audio recording? (y/n) : ");
        status = DebugP_scanf("%c", &valueChar);
        DebugP_assert(status == SystemP_SUCCESS);
    } while (valueChar != 'y');

    DebugP_log("Starting recording for 5s  !!!!!\r\n");

    gMcaspAudioTxnRx.buf = (void*) &gMcaspRxBuffer[0];
    gMcaspAudioTxnRx.count = APP_MCASP_AUDIO_BUFF_SIZE/4;
    gMcaspAudioTxnRx.timeout = 0xFFFFFF;
    MCASP_submitRx(mcaspHandle, &gMcaspAudioTxnRx);

    /* Trigger McASP receive operation */
    status = MCASP_startTransferRx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_pend(&gRxSem, SystemP_WAIT_FOREVER);

    MCASP_stopTransferRx(mcaspHandle);

    DebugP_log("5s audio data received !!!!!!\r\n");

    do
    {
        DebugP_log("\r\nStart playback of 5s audio received? (y/n) : ");
        status = DebugP_scanf("%c", &valueChar);
        DebugP_assert(status == SystemP_SUCCESS);
    } while (valueChar != 'y');

    DebugP_log("\r\n\r\n");

    DebugP_log("Playing Back .... \r\n");

    gMcaspAudioTxnTx.buf = (void*) &gMcaspRxBuffer[0];
    gMcaspAudioTxnTx.count = APP_MCASP_AUDIO_BUFF_SIZE/4;
    gMcaspAudioTxnTx.timeout = 0xFFFFFF;
    MCASP_submitTx(mcaspHandle, &gMcaspAudioTxnTx);

    /* Trigger McASP Trasmit operation */
    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_pend(&gTxSem, SystemP_WAIT_FOREVER);

    /* Stop McASP Trasmit operation */
    status = MCASP_stopTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    do
    {
        DebugP_log("\r\nRestart audio recording for 5s? (y/n) : ");
        status = DebugP_scanf("%c", &valueChar);
        DebugP_assert(status == SystemP_SUCCESS);
    } while (valueChar != 'y');

    DebugP_log("Restarting receive now !!!\r\n");

    gMcaspAudioTxnRx.buf = (void*) &gMcaspRxBuffer[0];
    gMcaspAudioTxnRx.count = APP_MCASP_AUDIO_BUFF_SIZE/4;
    gMcaspAudioTxnRx.timeout = 0xFFFFFF;
    MCASP_submitRx(mcaspHandle, &gMcaspAudioTxnRx);

    /* Trigger McASP receive operation */
    status = MCASP_startTransferRx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_pend(&gRxSem, SystemP_WAIT_FOREVER);

    DebugP_log("5s audio received !!!!!!\r\n");

    do
    {
        DebugP_log("\r\nRestart playback of 5s audio received? (y/n) : ");
        status = DebugP_scanf("%c", &valueChar);
        DebugP_assert(status == SystemP_SUCCESS);
    } while (valueChar != 'y');

    DebugP_log("Playing Back \r\n");

    gMcaspAudioTxnTx.buf = (void*) &gMcaspRxBuffer[0];
    gMcaspAudioTxnTx.count = APP_MCASP_AUDIO_BUFF_SIZE/4;
    gMcaspAudioTxnTx.timeout = 0xFFFFFF;
    MCASP_submitTx(mcaspHandle, &gMcaspAudioTxnTx);

    /* Trigger McASP Trasmit operation */
    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_pend(&gTxSem, SystemP_WAIT_FOREVER);

    /* Stop McASP Trasmit operation */
    status = MCASP_stopTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    DebugP_log("Playback completed !!!!\r\n");

    DebugP_log("Exiting demo\r\n");

}

static void I2C_writeReg(I2C_Handle handle, uint8_t devAddr, uint8_t reg,
                                    uint8_t val)
{
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[2];

    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.slaveAddress = devAddr;
    txBuffer[0] = reg;
    txBuffer[1] = val;
    I2C_transfer(handle, &i2cTransaction);
}

static void mcasp_codec_reset(void)
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
}

static void mcasp_aic31_codec_config(void)
{
    int32_t status = SystemP_FAILURE;
    I2C_Handle      i2cHandle;
    i2cHandle = gI2cHandle[CONFIG_I2C0];
    uint8_t deviceAddress = 0x1B;

    mcasp_codec_reset();

    status = I2C_probe(i2cHandle, deviceAddress);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Select Page0 */
    I2C_writeReg(i2cHandle, deviceAddress, AIC31_PAGE_SEL_REG, 0U);

    /* Select codec to be in master mode for FS and BCLK */
    I2C_writeReg(i2cHandle, deviceAddress, 8, (1 << 6) | (1 << 7));

    /* I2S interface */
    I2C_writeReg(i2cHandle, deviceAddress, AIC31_INTERFACE_REG, (0x0U << 6U) | (3 << 4));

    /* Configure data path */
    /* Left DAC datapath plays left and Right path datapath plays right */
    I2C_writeReg(i2cHandle, deviceAddress, AIC31_CODEC_DATA_PATH_REG, 0xA);

    /* ADC/Mic config */
    {
        /* Unmute left PGA and set gain */
        I2C_writeReg(i2cHandle, deviceAddress, AIC31_LEFT_PGA_REG, 0);

        /* Unmute right PGA and set gain */
        I2C_writeReg(i2cHandle, deviceAddress, AIC31_RIGHT_PGA_REG, 0);

        /* Set level control gain to Left ADC */
        I2C_writeReg(i2cHandle, deviceAddress, AIC31_MIC3_LEFT_ADC_REG, 0xF0);

        /* Set level control gain to Right ADC */
        I2C_writeReg(i2cHandle, deviceAddress, AIC31_MIC3_RIGHT_ADC_REG, 0xF0);

        /* Set Mic bias voltage = 2.0V */
        I2C_writeReg(i2cHandle, deviceAddress, AIC31_MICBIAS_CTRL_REG, 0x40);

        /* Set level control gain for Left ADC */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_LINE1L_TO_LEFT_ADC_REG, 0xFC);

        /* Set level control gain for Right ADC */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_LINE1R_TO_RIGHT_ADC_REG, 0xFC);
    }

    /* DAC setup */
    {
        /* Power up Left and Right DAC */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_OP_POWER_REG, 0xE0);

        /* Right DAC volume follows left channel control register */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_DAC_OP_SWITCH_CTRL_REG, 0x02);

        /* DAC L1 routed to HPLOUT */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_DAC_L1_HPLOUT_VOL_CTRL_REG, 0x80);

        /* Unmute HPLOUT and power up HPLOUT */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_HP_LOUT_LEVEL_CTRL_REG, 0x09);

        /* DAC R1 routed to HPROUT */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_DAC_R1_HPROUT_VOL_CTRL_REG, 0x80);

        /* Unmute HPROUT and power up HPROUT */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_HPROUT_LEVEL_CTRL_REG, 0x09);

        /* Unmute Left DAC with gain 0 dB */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_LDAC_VOL_CTRL, 0x00);

        /* Unmute Right DAC with gain 0 dB */
        I2C_writeReg(i2cHandle, deviceAddress, AIC_RDAC_VOL_CTRL, 0x00);
    }
}

void mcasp_txcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    SemaphoreP_post(&gTxSem);
}

void mcasp_rxcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    SemaphoreP_post(&gRxSem);
}

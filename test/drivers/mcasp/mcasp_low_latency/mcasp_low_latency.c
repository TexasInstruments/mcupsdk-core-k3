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

#if defined (SOC_AM275X)
#include "board/ioexp/ioexp_tca6416.h"
#endif /* SOC_AM275X */

/******************************************************************************/
/*                             AM62A Test Setup                               */
/******************************************************************************/
/*
 * This is a test to validate low latency use case of mcasp. For low latency the mcasp
 * FIFOs needs to be turned off(from syscfg). And the buffer length is limited to 16bytes
 * (4, 32b txns).
 *
 * For validating the test case we needs to probe test points TP56, TP52, TP57 and TP51.
 * The signal can be decoded using logic analyzer. For validation of low latency
 * performance the timestamps of tx and rx signals can be compared and validated to be
 * less than 1ms.
 */
/******************************************************************************/

/******************************************************************************/
/*                             AM275 Test Setup                               */
/******************************************************************************/
/*
 * To test MCASP audio latency:
 * 1. Connect PIN 2 of header J28 (GPIO) to MCASP RX serialiser PIN 6 of header J28.
 * 2. The MCASP TX serialiser will be brought out at PIN 8 of header J28.
 * 3. In the application, turn a GPIO pin high after a delay and measure the time
 *    from the RX pin to the TX pin.
 * 4. The time delay of the GPIO rising edge from PIN 2 to PIN 8 will indicate
 *    the MCASP audio latency.
 */
/******************************************************************************/

/******************************************************************************/
/*                             AM62D Test Setup                               */
/******************************************************************************/
/*
 * To test MCASP audio latency:
 * 1. Connect PIN 29 of Audio expansion header 1 to MCASP RX serialiser PIN 29 of
 *    Audio expansion header 1.
 * 2. The MCASP TX serialiser will be brought out at PIN 27 of audio expansion
 *    header 1.
 * 3. In the application, turn a GPIO pin high after a delay and measure the time
 *    from the RX pin to the TX pin.
 * 4. The time delay of the GPIO rising edge from PIN 27 to PIN 29 will indicate
 *    the MCASP audio latency.
 */
/******************************************************************************/

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Audio buffer settings */
#define APP_MCASP_AUDIO_BUFF_COUNT  (3U)
#define APP_MCASP_AUDIO_BUFF_SIZE   (16U)

#if defined (SOC_AM62AX)
/* AM62Ax CODEC I2C address */
#define APP_MCASP_CODEC_ADDR    (0x1BU)

/* I2C address for IO expander */
#define IO_EXP_ADDR             (0x22U)

/* Codec reset pin for I/O expander */
#define IO_EXP_CODEC_RESET_PIN  (0x8U)

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

#endif /* defined (SOC_AM62AX) */

#if defined (SOC_AM275X)

/* IO expander address */
#define APP_IO_EXP_ADDR             (0x20U)

/* PIN for FET SEL to select MCASP4 mux */
#define APP_IO_EXP_MCASP_FET_SEL    (0x3U)

#endif /* defined (SOC_AM275X) */


/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* Create buffers for transmit and Receive */
uint8_t gMcaspAudioBufferTx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE] __attribute__((aligned(256)));
uint8_t gMcaspAudioBufferRx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE] __attribute__((aligned(256)));

/* Create transaction objects for transmit and Receive */
MCASP_Transaction   gMcaspAudioTxnTx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};
MCASP_Transaction   gMcaspAudioTxnRx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};

#if defined (SOC_AM275X)
static TCA6416_Config  gTCA6416_Config;
#endif

/* ========================================================================== */
/*                        Static Function Declaration                         */
/* ========================================================================== */

#if defined (SOC_AM62AX)
/* Reset codec */
static void mcasp_codec_reset(void);
/* Configure codec TLV320AIC31 */
static void mcasp_aic31_codec_config(void);
/* I2C register write for Codec */
static void I2C_writeReg(I2C_Handle handle, uint8_t devAddr, uint8_t reg,
                                    uint8_t val);
#endif /* SOC_AM62AX */

#if defined (SOC_AM275X)
/* Board level configuration for necessary signal routing */
static int32_t mcasp_board_config(void);
#endif

void mcasp_low_latency_main(void *args)
{
    int32_t         status = SystemP_SUCCESS;
    uint32_t        i;
    MCASP_Handle    mcaspHandle;
    char            valueChar;

#if defined (SOC_AM62AX)
    mcasp_aic31_codec_config();
#endif /* SOC_AM62AX */

#if defined (SOC_AM275X)
    status = mcasp_board_config();
    DebugP_assert(status == SystemP_SUCCESS);
#endif /* SOC_AM275X */

    DebugP_log("[MCASP] Low latency udio playback example started.\r\n");

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    /* Prepare and submit audio transaction transmit objects */
    for (i = 0U; i < APP_MCASP_AUDIO_BUFF_COUNT; i++)
    {
        gMcaspAudioTxnTx[i].buf = (void*) &gMcaspAudioBufferTx[i][0];
        gMcaspAudioTxnTx[i].count = APP_MCASP_AUDIO_BUFF_SIZE/4;
        gMcaspAudioTxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(mcaspHandle, &gMcaspAudioTxnTx[i]);
    }

    /* Prepare and submit audio transaction receive objects */
    for (i = 0U; i < APP_MCASP_AUDIO_BUFF_COUNT; i++)
    {
        gMcaspAudioTxnRx[i].buf = (void*) &gMcaspAudioBufferRx[i][0];
        gMcaspAudioTxnRx[i].count = APP_MCASP_AUDIO_BUFF_SIZE/4;
        gMcaspAudioTxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(mcaspHandle, &gMcaspAudioTxnRx[i]);
    }

    /* Trigger McASP receive operation */
    status = MCASP_startTransferRx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Trigger McASP transmit operation */
    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

#if defined (SOC_AM275X) || defined (SOC_AM62DX)
    DebugP_log("Toglging GPIO high in 3seconds\r\n");

    ClockP_sleep(3);

    GPIO_pinWriteHigh(CONFIG_GPIO0_BASE_ADDR, CONFIG_GPIO0_PIN);
#endif /* SOC_AM275X || SOC_AM62DX */
    DebugP_log("Enter your response on UART terminal");

    do
    {
        DebugP_log("\r\nStop the demo? (y/n) : ");
        status = DebugP_scanf("%c", &valueChar);
        DebugP_assert(status == SystemP_SUCCESS);
    } while (valueChar != 'y');

    DebugP_log("Exiting demo\r\n");

}

#if defined (SOC_AM62AX)

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

#endif /* SOC_AM62AX */

#if defined (SOC_AM275X)
static int32_t mcasp_board_config(void)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t pinNum = APP_IO_EXP_MCASP_FET_SEL;

    TCA6416_Params  tca6416Params;
    TCA6416_Params_init(&tca6416Params);
    tca6416Params.i2cInstance = CONFIG_I2C0;
    tca6416Params.i2cAddress = APP_IO_EXP_ADDR;
    TCA6416_open(&gTCA6416_Config, &tca6416Params);

    status += TCA6416_setOutput(
                    &gTCA6416_Config,
                    pinNum,
                    TCA6416_OUT_STATE_LOW);

    /* Configure as output  */
    status += TCA6416_config(
                    &gTCA6416_Config,
                    pinNum,
                    TCA6416_MODE_OUTPUT);

    status += TCA6416_setOutput(
                    &gTCA6416_Config,
                    pinNum,
                    TCA6416_OUT_STATE_HIGH);

    return status;
}
#endif /* SOC_AM275X */

void mcasp_txcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    MCASP_submitRx(handle, transaction);
}

void mcasp_rxcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    MCASP_submitTx(handle, transaction);
}

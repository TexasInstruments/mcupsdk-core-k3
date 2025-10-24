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

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <drivers/mcasp.h>
#include <unity.h>
#include <drivers/pinmux.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Audio buffer settings */
#define APP_MCASP_AUDIO_BUFF_COUNT  (4U)
#define APP_MCASP_AUDIO_BUFF_SIZE   (2048U)

#define APP_MCASP_TXN_CNT           (20U)

#ifdef SOC_AM275X

#define APP_MCASP_RX_FREQ          (300U)
#define APP_MCASP_TX_FREQ          (48000U)

#define APP_MCASP_RX_SLOT_COUNT    (2U)
#define APP_MCASP_TX_SLOT_COUNT    (2U)

#endif

#define APP_MCASP_RXCB_PERIOD_US         ((APP_MCASP_AUDIO_BUFF_SIZE/(sizeof(uint32_t)*\
                                            APP_MCASP_RX_SLOT_COUNT))*1000000)/(APP_MCASP_RX_FREQ)
#define APP_MCASP_TXCB_PERIOD_US         ((APP_MCASP_AUDIO_BUFF_SIZE/(sizeof(uint32_t)*\
                                            APP_MCASP_TX_SLOT_COUNT))*1000000)/(APP_MCASP_TX_FREQ)

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* Create buffers for transmit and Receive */
uint8_t gMcaspAudioBufferTx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE] __attribute__((aligned(256)));
uint8_t gMcaspAudioBufferRx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE] __attribute__((aligned(256)));

/* Create transaction objects for transmit and Receive */
MCASP_Transaction   gMcaspAudioTxnTx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};
MCASP_Transaction   gMcaspAudioTxnRx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};

static SemaphoreP_Object gTxDoneSem, gRxDoneSem;

uint64_t gTxAvgPeriod = 0;
uint64_t gRxAvgPeriod = 0;

uint32_t gTxTxnCnt = 0;
uint32_t gRxTxnCnt = 0;

/* ========================================================================== */
/*                        Extern Function Declaration                         */
/* ========================================================================== */
int32_t Board_clockgenConfig(I2C_Handle handle, uint8_t devAddr);

void mcasp_300Hz_main(void *args)
{
    UNITY_BEGIN();

    int32_t status = SystemP_SUCCESS;
    uint32_t count = 0;

    MCASP_Handle mcaspHandle;

    I2C_Handle      i2cHandle;
    i2cHandle = gI2cHandle[CONFIG_I2C0];

    Pinmux_PerCfg_t pinmuxConfig[] =
    {
        {
            PIN_GPIO1_72,
            ( PIN_MODE(1) | PIN_INPUT_ENABLE | PIN_PULL_DIRECTION  )
        },
        {PINMUX_END, 0U}
    };

    Pinmux_config(pinmuxConfig, PINMUX_DOMAIN_ID_MAIN);

    SemaphoreP_constructBinary(&gTxDoneSem, 0);
    SemaphoreP_constructBinary(&gRxDoneSem, 0);

    status = Board_clockgenConfig(i2cHandle, 0x68);
    DebugP_assert(status == SystemP_SUCCESS);

    ClockP_usleep(100);

    /* Open MCASP driver after enabling the HCLK */
    gMcaspHandle[0] = MCASP_open(0, &gMcaspOpenParams[0]);
    if(NULL == gMcaspHandle[0])
    {
        DebugP_logError("MCASP open failed for instance 0 !!!\r\n");
        DebugP_assert(false);
    }

    DebugP_log("[MCASP] Test to validate 300Hz sample rate started.\r\n");

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    /* Prepare and submit audio transaction transmit objects */
    for (count = 0U; count < APP_MCASP_AUDIO_BUFF_COUNT; count++)
    {
        gMcaspAudioTxnTx[count].buf = (void*) &gMcaspAudioBufferTx[count][0];
        gMcaspAudioTxnTx[count].count = APP_MCASP_AUDIO_BUFF_SIZE/4;
        gMcaspAudioTxnTx[count].timeout = 0xFFFFFF;
        MCASP_submitTx(mcaspHandle, &gMcaspAudioTxnTx[count]);
    }

    /* Prepare and submit audio transaction receive objects */
    for (count = 0U; count < APP_MCASP_AUDIO_BUFF_COUNT; count++)
    {
        gMcaspAudioTxnRx[count].buf = (void*) &gMcaspAudioBufferRx[count][0];
        gMcaspAudioTxnRx[count].count = APP_MCASP_AUDIO_BUFF_SIZE/4;
        gMcaspAudioTxnRx[count].timeout = 0xFFFFFF;
        MCASP_submitRx(mcaspHandle, &gMcaspAudioTxnRx[count]);
    }

    /* Trigger McASP receive operation */
    status = MCASP_startTransferRx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Trigger McASP transmit operation */
    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
    DebugP_log("Average Tx Frame Sync Period -> %d us\r\n", gTxAvgPeriod);

    MCASP_stopTransferTx(mcaspHandle);

    SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);
    DebugP_log("Average Rx Frame Sync Period -> %d us\r\n", gRxAvgPeriod);

    MCASP_stopTransferRx(mcaspHandle);

    DebugP_log("Average Tx Frame Sync Period Expected -> %d us\r\n", APP_MCASP_TXCB_PERIOD_US);
    DebugP_log("Average Rx Frame Sync Period Expected -> %d us\r\n", APP_MCASP_RXCB_PERIOD_US);

    TEST_ASSERT_UINT64_WITHIN(APP_MCASP_RXCB_PERIOD_US/100, APP_MCASP_RXCB_PERIOD_US, gRxAvgPeriod);
    TEST_ASSERT_UINT64_WITHIN(APP_MCASP_TXCB_PERIOD_US/100, APP_MCASP_TXCB_PERIOD_US, gTxAvgPeriod);

    UNITY_END();
}

void mcasp_txcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    static uint64_t timestamp = 0;
    uint64_t timePeriod = 0;

    if(timestamp != 0)
    {
        gTxTxnCnt++;

        timePeriod = ClockP_getTimeUsec() - timestamp;

        if(gTxAvgPeriod != 0)
        {
            gTxAvgPeriod = (timePeriod+gTxAvgPeriod)/2;
        }
        else
        {
            gTxAvgPeriod = timePeriod;
        }
    }

    timestamp = ClockP_getTimeUsec();

    MCASP_submitTx(handle, transaction);

    if(gTxTxnCnt == APP_MCASP_TXN_CNT)
    {
        SemaphoreP_post(&gTxDoneSem);
    }
}

void mcasp_rxcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    static uint64_t timestamp = 0;
    uint64_t timePeriod = 0;

    if(timestamp != 0)
    {
        gRxTxnCnt++;

        timePeriod = ClockP_getTimeUsec() - timestamp;

        if(gRxAvgPeriod != 0)
        {
            gRxAvgPeriod = (timePeriod+gRxAvgPeriod)/2;
        }
        else
        {
            gRxAvgPeriod = timePeriod;
        }
    }

    timestamp = ClockP_getTimeUsec();

    MCASP_submitRx(handle, transaction);

    if(gRxTxnCnt == APP_MCASP_TXN_CNT)
    {
        SemaphoreP_post(&gRxDoneSem);
    }
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

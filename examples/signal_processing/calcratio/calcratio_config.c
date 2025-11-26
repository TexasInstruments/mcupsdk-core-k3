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
#include <drivers/pinmux.h>
#include <signal_processing/calcratio/calcratio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "calcratio_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Audio buffer settings */
#define APP_MCASP_AUDIO_BUFF_COUNT  (4U)
#define APP_MCASP_AUDIO_BUFF_SIZE   (2048U)

/* CalcRatio module instance configuration */
#define CALC_RATIO_INST             (4U)    /* Total number of independent CalcRatio instances */

/* Instance identifiers for CalcRatio array */
#define CALCRATIO_INST_0            (0U)    /* Index for CalcRatio instance 0 */
#define CALCRATIO_INST_1            (1U)    /* Index for CalcRatio instance 1 */
#define CALCRATIO_INST_2            (2U)    /* Index for CalcRatio instance 2 */
#define CALCRATIO_INST_3            (3U)    /* Index for CalcRatio instance 3 */

/* Test parameters */
#define TEST_ITERATIONS             (300U) /* Number of iterations in ratio convergence test */
#define RATIO_TOLERANCE             (0.005) /* Max allowed relative error (±0.5%) for a "good" sample */
#define RATIO_GOOD_FRACTION         (0.98)  /* Minimum fraction (98%) of samples that must pass tolerance */
/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* Create buffers for transmit and Receive */
uint8_t gMcaspAudioBufferTx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE] __attribute__((aligned(256)));
uint8_t gMcaspAudioBufferRx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE] __attribute__((aligned(256)));

/* Create transaction objects for transmit and Receive */
MCASP_Transaction   gMcaspAudioTxnTx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};
MCASP_Transaction   gMcaspAudioTxnRx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};

MCASP_Handle    mcaspHandle;

/* Array of CalcRatio instances */
CalcRatio_t CALC_RATIO[CALC_RATIO_INST];

/* Semaphore create for Timer callback*/
SemaphoreP_Object gBinarySem;

/* Count of completed TX DMA transfers (buffers sent) */
volatile uint32_t gTxDmaCount   = 0;
/* Count of completed RX DMA transfers (buffers received) */
volatile uint32_t gRxDmaCount   = 0;
/* TX sample count (for ratio tracking) */
double Tx_Counter   = 0;
/* RX sample count (for ratio tracking) */
double Rx_Counter   = 0;
/* Actaul ratio */
double actualRatio = 0;

/* For PASS/FAIL decision */
static uint32_t gGoodCount   = 0;
static uint32_t gTotalCount  = 0;

/* ========================================================================== */
/*                        Extern Function Declaration                         */
/* ========================================================================== */
int32_t Board_codecConfig(void);
int32_t Board_clockgenConfig(I2C_Handle handle, uint8_t devAddr);
static void test_conclude(bool pass);

void mcasp_calcratio_main(void *args)
{
    int32_t     status = SystemP_SUCCESS;
    uint32_t    i;

    I2C_Handle      i2cHandle;
    i2cHandle = gI2cHandle[CONFIG_I2C0];

#if defined (SOC_AM275X)
    Pinmux_PerCfg_t i2cPinmuxConfig[] =
    {
        {
            PIN_GPIO1_72,
            ( PIN_MODE(1) | PIN_INPUT_ENABLE | PIN_PULL_DIRECTION  )
        },
        {PINMUX_END, 0U}
    };

    Pinmux_config(i2cPinmuxConfig, PINMUX_DOMAIN_ID_MAIN);
#endif

    /* Configure clock generator for getting the external HCLK */
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

    ClockP_usleep(100);


    /* Configure codec */
    status = Board_codecConfig();
    DebugP_assert(status == SystemP_SUCCESS);

    DebugP_log("[CALCRATIO] DMA Couter based example started.\r\n");

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    /* Calcratio Init */
    status = calcRatio_init(&CALC_RATIO[CALCRATIO_INST_0],
            INPUT_FRAME_SYNC_CLOCK,
            OUTPUT_FRAME_SYNC_CLOCK
            );

    DebugP_assert(status == SystemP_SUCCESS);

    /* Create semaphore for DMA Counter */
    SemaphoreP_constructBinary(&gBinarySem, 0);

    /* Timer start */
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER0]);

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

    while(1)
    {
        /* Wait indefinitely for the binary semaphore posted by the timer callback to signal new DMA data is ready. */
        SemaphoreP_pend(&gBinarySem, SystemP_WAIT_FOREVER);

        /* Execute the ratio calculation using current TX/RX counters and configuration for instance 0. */
        status = calcRatio_exec(&CALC_RATIO[CALCRATIO_INST_0],&Tx_Counter,&Rx_Counter);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Get the actual ratio from the first CALC_RATIO instance */
        actualRatio = calcRatio_getActualratio(&CALC_RATIO[CALCRATIO_INST_0]);

        /* Log the computed actual ratio with input and output sample rates for monitoring and debugging. */
        DebugP_log("ActualRatio for %dHz to %dHz = %f\r\n",INPUT_FRAME_SYNC_CLOCK,OUTPUT_FRAME_SYNC_CLOCK,actualRatio);

        /* ---- TESTING LOGIC ---- */
        /* Count total samples processed */
        gTotalCount++;

        /* Check if the actual ratio is within the specified tolerance */
        double actual = actualRatio;
        double error = actual - CALC_RATIO[0].target_ratio;
        double diff = (error >= 0.0) ? error : -error;

        /* Count as "good" if within tolerance */
        if (diff <= RATIO_TOLERANCE * CALC_RATIO[0].target_ratio)
        {
            gGoodCount++;
        }

        /* After the specified number of iterations, conclude the test with PASS/FAIL based on good sample fraction */
        if (gTotalCount >= TEST_ITERATIONS)
        {
            double fraction = (double)gGoodCount / (double)gTotalCount;
            bool pass = (fraction >= RATIO_GOOD_FRACTION);
            /* Conclude the test and exit */
            test_conclude(pass);
        }
    }

}

void mcasp_txcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    /* Increment the global TX DMA transfer counter to track transmitted
        samples for ratio calculation. */
    gTxDmaCount++;

    /* Re-submit the same TX transaction to the McASP driver to enable
        continuous DMA transmission. */
    MCASP_submitTx(handle, transaction);
}

void mcasp_rxcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    /* Increment the global TX DMA transfer counter to track transmitted
        samples for ratio calculation. */
    gRxDmaCount++;

    /* Re-submit the same TX transaction to the McASP driver to enable
        continuous DMA transmission. */
    MCASP_submitRx(handle, transaction);
}

/**
 * \brief Timer callback function executed periodically to sample DMA transfer counts.
 *
 * This function is invoked by the timer hardware or RTOS at regular intervals.
 * It captures the current TX/RX DMA transfer counts, resets the counters, and
 * posts a binary semaphore to wake up a waiting task for data processing.
 *
 */
void timercallback(uintptr_t arg)
{
    /* Post the binary semaphore to signal the waiting task that fresh
       DMA statistics are available for processing in the current interval. */
    SemaphoreP_post(&gBinarySem);

    /* Capture the accumulated TX DMA transfer count into a double-precision
       variable for accurate throughput and bandwidth calculations. */
    Tx_Counter = (double)gTxDmaCount;

    /* Capture the accumulated RX DMA transfer count into a double-precision
       variable for accurate throughput and bandwidth calculations. */
    Rx_Counter = (double)gRxDmaCount;

    /* Reset the TX DMA counter to zero after sampling to begin tracking
       transfers for the next timer interval. */
    gTxDmaCount = 0;

    /* Reset the RX DMA counter to zero after sampling to begin tracking
       transfers for the next timer interval. */
    gRxDmaCount = 0;
}

static void test_conclude(bool pass)
{
    /* Stop the timer to halt further ratio calculations */
    TimerP_stop(gTimerBaseAddr[CONFIG_TIMER0]);

    /* Print final test result */
    if (pass)
    {
        DebugP_log("Ratio Tracking Accuracy Test Pass (%.2f%% good)\r\n",(double)gGoodCount * 100.0 / (double)gTotalCount);
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_log("Ratio Tracking Accuracy Test Fail (only %.2f%% good)\r\n",(double)gGoodCount * 100.0 / (double)gTotalCount);
    }

    /* Stop McASP transfers */
    MCASP_stopTransferRx(mcaspHandle);
    MCASP_stopTransferTx(mcaspHandle);

    DebugP_log("Exiting demo\r\n");
}

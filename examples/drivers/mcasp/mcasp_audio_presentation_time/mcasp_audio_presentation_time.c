/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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

#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/gpio.h>
#include <drivers/mcasp.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

#if defined (SOC_AM275X)
#include "board/ioexp/ioexp_tca6416.h"
#endif /* SOC_AM275X */

/******************************************************************************/
/*                             AM275 Test Setup                               */
/******************************************************************************/
/*
 * To test presentation time:
 * 1. The GPIO pin is PIN 2 of header J28.
 * 2. The MCASP TX serialiser will be brought out at PIN 6 of header J28.
 * 3. In the application, turn a GPIO pin high after a delay and measure the time
 *    from the GPIO pin to the TX pin.
 * 4. The time delay of the GPIO rising edge from PIN 2 to PIN 6 will indicate
 *    the presentation time.
 * Note: Ensure J29 2-3 are connected for voltage selection
 */
/******************************************************************************/

/******************************************************************************/
/*                             AM62D Test Setup                               */
/******************************************************************************/
/*
 * To test presentation time:
 * 1. The PIN 51 of Audio expansion header 1 is GPIO pin.
 * 2. The MCASP TX serialiser will be brought out at PIN 27 of audio expansion
 *    header 1.
 * 3. In the application, turn a GPIO pin high after a delay and measure the time
 *    from the RX pin to the TX pin.
 * 4. The time delay of the GPIO rising edge from PIN 51 to PIN 27 will indicate
 *    the presentation time.
 */
/******************************************************************************/

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_MCASP_TEST_BUFF_SIZE    (2048U)

/*
 * Number of silence buffers submitted before TX start.
 * These are primed into TRPD slots by MCASP_startTransferTx.
 */
#define NUM_ZERO_BUFS              (4U)

/*
 * Sleep duration after TX start to let DMA consume some silence buffers.
 * This exercises the real-time bytes case: some user bytes are already
 * in-flight when getTxPresentationTime is called.
 */
#define APP_SLEEP_BEFORE_MEASURE_US (1000U)

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* TX buffers: all-zeros (silence) and all-FFs (marker burst) */
uint8_t gMcaspTxBufZeros[APP_MCASP_TEST_BUFF_SIZE] __attribute__((aligned(256)));
uint8_t gMcaspTxBufFFs[APP_MCASP_TEST_BUFF_SIZE]   __attribute__((aligned(256)));

/* Silence transaction objects (one per pre-start buffer) */
MCASP_Transaction gMcaspTxnZeros[NUM_ZERO_BUFS];
MCASP_Transaction gMcaspTxnFF;

/* Posted by FF callback to unblock main */
static SemaphoreP_Object gFFSem;

/* ========================================================================== */
/*                        Callback Functions                                  */
/* ========================================================================== */

void mcasp_txcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    if (transaction == &gMcaspTxnFF)
    {
        SemaphoreP_post(&gFFSem);
    }
}

void mcasp_rxcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
}

#if defined (SOC_AM275X)

static TCA6416_Config  gTCA6416_Config;

#define APP_IO_EXP_ADDR             (0x20U)

#define APP_IO_EXP_MCASP_FET_SEL    (0x3U)

static int32_t mcasp_board_config(void)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t pinNum = APP_IO_EXP_MCASP_FET_SEL;

    TCA6416_Params  tca6416Params;
    TCA6416_Params_init(&tca6416Params);
    tca6416Params.i2cInstance = CONFIG_I2C0;
    tca6416Params.i2cAddress = APP_IO_EXP_ADDR;
    TCA6416_open(&gTCA6416_Config, &tca6416Params);

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

/* ========================================================================== */
/*                        Main Function                                       */
/* ========================================================================== */

void mcasp_audio_presentation_time_main(void *args)
{
    int32_t             status;
    uint32_t            i;
    MCASP_Handle        mcaspHandle;
    MCASP_PresentationTime txTime;

    DebugP_log("[MCASP] Presentation Time \r\n");
    DebugP_log("==============================\r\n");

#if defined (SOC_AM275X)
    status = mcasp_board_config();
    DebugP_assert(status == SystemP_SUCCESS);
#endif /* SOC_AM275X */

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    memset(gMcaspTxBufZeros, 0x00U, sizeof(gMcaspTxBufZeros));
    CacheP_wb(gMcaspTxBufZeros, sizeof(gMcaspTxBufZeros), CacheP_TYPE_ALL);
    memset(gMcaspTxBufFFs,   0xFFU, sizeof(gMcaspTxBufFFs));
    CacheP_wb(gMcaspTxBufFFs,   sizeof(gMcaspTxBufFFs),   CacheP_TYPE_ALL);

    /* Queue silence buffers before TX start.
     * MCASP_startTransferTx loads them into the DMA TRPD ring at start. */
    for (i = 0U; i < NUM_ZERO_BUFS; i++)
    {
        gMcaspTxnZeros[i].buf     = (void *)gMcaspTxBufZeros;
        gMcaspTxnZeros[i].count   = APP_MCASP_TEST_BUFF_SIZE / 4U;
        gMcaspTxnZeros[i].timeout = 0xFFFFFFU;
        MCASP_submitTx(mcaspHandle, &gMcaspTxnZeros[i]);
    }

    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    /*
     * Sleep to let DMA consume some of the pre-start silence buffers.
     * This is the real-time bytes case: getTxPresentationTime is called
     * while audio is actively playing, not from a cold start.
     */
    ClockP_usleep(APP_SLEEP_BEFORE_MEASURE_US);

    /* Measure presentation time of the FF buffer about to be submitted */
    SemaphoreP_constructBinary(&gFFSem, 0U);
    gMcaspTxnFF.buf     = (void *)gMcaspTxBufFFs;
    gMcaspTxnFF.count   = APP_MCASP_TEST_BUFF_SIZE / 4U;
    gMcaspTxnFF.timeout = 0xFFFFFFU;

    status = MCASP_getTxPresentationTime(mcaspHandle, &txTime);

    /* GPIO HIGH marks the software submission instant */
    GPIO_pinWriteHigh(CONFIG_GPIO0_BASE_ADDR, CONFIG_GPIO0_PIN);
    MCASP_submitTx(mcaspHandle, &gMcaspTxnFF);

    /* Wait for FF to complete (semaphore posted from callback) */
    SemaphoreP_pend(&gFFSem, SystemP_WAIT_FOREVER);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("API estimate at FF submission:\r\n");
        DebugP_log("  presentationTime = %u us\r\n", txTime.offsetUs);
        DebugP_log("  samplesRemaining = %u\r\n",    txTime.samplesRemaining);
    }

    MCASP_stopTransferTx(mcaspHandle);

    DebugP_log("Done.\r\n");
}

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
#include <drivers/pinmux.h>
#include <signal_processing/calcratio/calcratio.h>
#include "FreeRTOS.h"
#include "task.h"
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/SemaphoreP.h>
#include "AUDIOLIB_asrc.h"
#include "swasrc_config.h"
#include <dsplib.h>

/* ========================================================================== */
/*                             Semaphore Objects                              */
/* ========================================================================== */

/* gBinarySem semaphore used to main loop to update SW_ASRC calcratio on
 *  timer event
 */
SemaphoreP_Object gBinarySem;

/* ========================================================================== */
/*                        Rx/TX FIFO State Variables                          */
/* ========================================================================== */
/*
 * rx_head         : Write pointer — updated by McASP RX DMA when new samples arrive
 * rx_tail         : Read pointer  — updated by SW_ASRC when consuming input samples
 * bufferFilled_rx : Number of valid bytes currently in RX FIFO
 */
volatile int32_t rx_head = 0, rx_tail = 0, bufferFilled_rx = 0;

/*
 * tx_head         : Write pointer — updated by SW_ASRC when producing output samples
 * tx_tail         : Read pointer  — updated by McASP TX DMA when sending samples
 * bufferFilled_tx    : Number of valid bytes currently in TX FIFO
 */
volatile int32_t tx_head = 0, tx_tail = 0, bufferFilled_tx = 0;

/* ========================================================================== */
/*                          Algorithm Execution State                         */
/* ========================================================================== */

/* Indicates whether the audio processing pipeline (RX → SWASRC → TX)
 * has been started.
 * Set to 1 after the first initialization or trigger event, ensuring
 * continuous audio data processing in subsequent cycles.
 */
volatile uint8_t  audioPipelineStarted = 0;

/* ========================================================================== */
/*                          Semaphore Objects for McASP                       */
/* ========================================================================== */
/* semaphores for thread-safe access to McASP RX/TX buffers.
 * rxLock: protects audioBuffer_rx during DMA and SW_ASRC access
 * txLock: protects audioBuffer_tx during SW_ASRC and TX DMA access
 */
static SemaphoreP_Object rxLock;
static SemaphoreP_Object txLock;

/* ========================================================================== */
/*                       SW_SRC Ratio & DMA Transfer Counters                 */
/* ========================================================================== */

/* Count of completed TX DMA transfers (buffers sent) */
volatile uint32_t gTxDmaCount   = 0;
/* Count of completed RX DMA transfers (buffers received) */
volatile uint32_t gRxDmaCount   = 0;
/* TX sample count (for ratio tracking) */
double Tx_Counter   = 0;
/* RX sample count (for ratio tracking) */
double Rx_Counter   = 0;
/* Smoothed ratio from calcratio */
double actualRatio = 0;
/* Flags to indicate that RX and TX data is ready for processing in timercallback */
int32_t Flag_rx = 0;
int32_t Flag_tx = 0;
/* SWASRC calculated sample rate ratio */
static inline sample_rate_t rate_to_enum(uint32_t hz)
{
    switch (hz) {
        case 32000: return SAMPLE_RATE_32000;
        case 44100: return SAMPLE_RATE_44100;
        case 48000: return SAMPLE_RATE_48000;
        default:    return SAMPLE_RATE_NA;
    }
}

/* ========================================================================== */
/*                     SW_ASRC FIFO Buffer Configuration                      */
/* ========================================================================== */

/* Audio buffer configuration for the SW_ASRC system.
 * Defines the size and layout of input/output FIFO buffers
 * used during software-based asynchronous sample rate conversion.
 */
#define BUFFER_HALF       (4U)
#define BUFFER_FRAMES     (8192U)
#define BUFFER_SIZE       (BUFFER_FRAMES * BUFFER_HALF)

/* McASP Receive FIFO Buffer (Input Buffer)
 * Stores incoming audio samples captured by McASP RX DMA.
 * Data flow: Filled by RX DMA → Read by SW_ASRC processing task.
 */
__attribute__((section(".sw_asrc")))
static uint8_t  audioBuffer_rx[BUFFER_SIZE];

/* ASRC Transmit FIFO Buffer (Output Buffer)
 * Stores converted audio samples produced by the SW_ASRC algorithm.
 * Data flow: Filled by SW_ASRC → Read by McASP TX DMA for playback.
 */
__attribute__((section(".sw_asrc")))
static uint8_t  audioBuffer_tx[BUFFER_SIZE];

/* ========================================================================== */
/*                          SWASRC Algorithm Interal Pointers                 */
/* ========================================================================== */
/* Pointers used internally by the SWASRC processing functions.
 * These point to various buffers and coefficient arrays required
 * for sample rate conversion operations.
 */
float *nonInterleavedData;
float *in;
float *out;
float *filterRembuf;
float *filtCoeffs;

/* ========================================================================== */
/*                           MCASP Init Params                                */
/* ========================================================================== */
/* Audio buffer settings */
#define APP_MCASP_AUDIO_BUFF_COUNT      (4U)
#define APP_MCASP_AUDIO_BUFF_SIZE_RX    (1024U)
#define APP_MCASP_AUDIO_BUFF_SIZE_TX    (1024U)


/* Create buffers for transmit and Receive */
__attribute__((aligned(256)))
uint8_t gMcaspAudioBufferTx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE_TX] ={0};
__attribute__((aligned(256)))
uint8_t gMcaspAudioBufferRx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE_RX] ={0};

/* Create transaction objects for transmit and Receive */
MCASP_Transaction   gMcaspAudioTxnTx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};
MCASP_Transaction   gMcaspAudioTxnRx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};

/* MCASP open parameters */
MCASP_Handle    mcaspHandle;

/* MCASP Buffer Index Variables  */
volatile int mcasptx_writeindex = (APP_MCASP_AUDIO_BUFF_COUNT - 1);
volatile int mcasprx_readindex = 0;

/* CalcRatio module instance configuration */
#define CALC_RATIO_INST             (4U)    /* Total number of independent CalcRatio instances */

/* Instance identifiers for CalcRatio array */
#define CALCRATIO_INST_0            (0U)    /* Index for CalcRatio instance 0 */
#define CALCRATIO_INST_1            (1U)    /* Index for CalcRatio instance 1 */
#define CALCRATIO_INST_2            (2U)    /* Index for CalcRatio instance 2 */
#define CALCRATIO_INST_3            (3U)    /* Index for CalcRatio instance 3 */

/* Array of CalcRatio instances */
CalcRatio_t CALC_RATIO[CALC_RATIO_INST];

/* ========================================================================== */
/*                        Extern Function Declaration                         */
/* ========================================================================== */
int32_t Board_codecConfig(void);
int32_t Board_clockgenConfig(I2C_Handle handle, uint8_t devAddr);

void swasrc_main(void *args)
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

    DebugP_log("[SWASRC] Audio playback example started.\r\n");

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    /* Initialize FIFO buffers and pointers */
    buffer_init();

    /* Calcratio Init*/
    status = calcRatio_init(&CALC_RATIO[CALCRATIO_INST_0],
        INPUT_FRAME_SYNC_CLOCK,
        OUTPUT_FRAME_SYNC_CLOCK
        );

    /* Create semaphore for calcratio */
    SemaphoreP_constructBinary(&gBinarySem, 0);

    /* Prepare and submit audio transaction transmit objects */
    for (i = 0U; i < APP_MCASP_AUDIO_BUFF_COUNT; i++)
    {
        gMcaspAudioTxnTx[i].buf = (void*) &gMcaspAudioBufferTx[i][0];
        gMcaspAudioTxnTx[i].count = APP_MCASP_AUDIO_BUFF_SIZE_TX/4;
        gMcaspAudioTxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(mcaspHandle, &gMcaspAudioTxnTx[i]);
    }

    /* Prepare and submit audio transaction receive objects */
    for (i = 0U; i < APP_MCASP_AUDIO_BUFF_COUNT; i++)
    {
        gMcaspAudioTxnRx[i].buf = (void*) &gMcaspAudioBufferRx[i][0];
        gMcaspAudioTxnRx[i].count = APP_MCASP_AUDIO_BUFF_SIZE_RX/4;
        gMcaspAudioTxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(mcaspHandle, &gMcaspAudioTxnRx[i]);
    }

    /* Start the timer to generate periodic events for calcratio calculation */
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER0]);

    /* Trigger McASP receiver operation */
    status = MCASP_startTransferRx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Trigger McASP transmit operation */
    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    while(1)
    {
        /* Wait for timer event to trigger ratio calculation */
        SemaphoreP_pend(&gBinarySem, SystemP_WAIT_FOREVER);

        /* Calcatio execution */
        status = calcRatio_exec(&CALC_RATIO[CALCRATIO_INST_0],&Tx_Counter,&Rx_Counter);
        DebugP_assert(status == SystemP_SUCCESS);

        /* This will be used to adjust the SWASRC processing rate */
        /* Get the actual ratio from the first CALC_RATIO instance */
        actualRatio = calcRatio_getActualratio(&CALC_RATIO[CALCRATIO_INST_0]);

        /* Configure ASRC mode and ratio (sets target resampling rate) */
        status = AUDIOLIB_asrc_set(handle, AUDIOLIB_ASRC_MODE_SET, actualRatio, nonInterleavedData, in);
        DebugP_assert(status == SystemP_SUCCESS);


        if(audioPipelineStarted == 0)
        {
            /* Initialize RX buffer pointers to match first block size */
            tx_head             = (INPUT_BLOCKSIZE * NUM_CHANNLES * BYTES_PER_SAMPLE_ASRC);
            /* Set initial fill level to ensure enough data for first processing block */
            bufferFilled_tx     = (INPUT_BLOCKSIZE * NUM_CHANNLES * BYTES_PER_SAMPLE_ASRC);
            /* Reset TX tail pointer to start of buffer */
            tx_tail             = 0;

            /* Initialize RX buffer pointers to match first block size */
            rx_head             = 0;
            /* Set initial fill level to ensure enough data for first processing block */
            bufferFilled_rx     = 0;
            /* Reset RX tail pointer to start of buffer */
            rx_tail             = 0;

            /* Mark the audio processing pipeline as started */
            audioPipelineStarted = 1;
        }

    }
}

/* ========================================================================== */
/*                        FIFO Buffer Initialization                          */
/* ========================================================================== */
void buffer_init(void)
{
    /* Initialize semaphores for thread-safe access to RX and TX buffers */
    SemaphoreP_constructBinary(&rxLock, 0);
    SemaphoreP_constructBinary(&txLock, 0);
    SemaphoreP_post(&rxLock);
    SemaphoreP_post(&txLock);
}

/* ========================================================================== */
/*                        FIFO Utility Functions                              */
/* ========================================================================== */
int32_t mcasp_get_filled_space_rx(void)
{
    SemaphoreP_pend(&rxLock, SystemP_WAIT_FOREVER);
    int32_t filled_space = bufferFilled_rx;
    SemaphoreP_post(&rxLock);
    return filled_space;
}

int32_t mcasp_tx_buffer_freespace(void)
{
    SemaphoreP_pend(&txLock, SystemP_WAIT_FOREVER);
    int32_t free_space = BUFFER_SIZE - bufferFilled_tx;
    SemaphoreP_post(&txLock);
    return free_space;
}

/* ========================================================================== */
/*  McASP RX Callback -> Store Captured Input Samples in audioBuffer_rx       */
/* ========================================================================== */
void mcasp_storeRxSamples(int32_t sampleSize, uint8_t *sample)
{
    SemaphoreP_pend(&rxLock, SystemP_WAIT_FOREVER);

    if (bufferFilled_rx + sampleSize > BUFFER_SIZE) {
        SemaphoreP_post(&rxLock);
        return;  /* overflow */
    }

    uint32_t spaceToEnd = BUFFER_SIZE - rx_head;

    if (sampleSize <= spaceToEnd) {
        memcpy(&audioBuffer_rx[rx_head], sample, sampleSize);
        rx_head += sampleSize;
    } else {
        memcpy(&audioBuffer_rx[rx_head], sample, spaceToEnd);
        memcpy(audioBuffer_rx, sample + spaceToEnd, sampleSize - spaceToEnd);
        rx_head = sampleSize - spaceToEnd;
    }

    // Wrap-around protection
    if (rx_head >= BUFFER_SIZE) rx_head -= BUFFER_SIZE;

    bufferFilled_rx += sampleSize;
    if (bufferFilled_rx > BUFFER_SIZE) bufferFilled_rx = BUFFER_SIZE;

    SemaphoreP_post(&rxLock);
}

/* ============================================================ */
/*       SWASRC input copy -> get samples from audioBuffer_rx   */
/* ============================================================ */
int32_t mcasp_getRxSamples(int32_t totalSamplesToProcess, uint8_t *ptr)
{
    int32_t status;
    SemaphoreP_pend(&rxLock, SystemP_WAIT_FOREVER);

    if (bufferFilled_rx < totalSamplesToProcess) {
        SemaphoreP_post(&rxLock);
        status = 0; /* underflow */
    }
    else
    {
        uint32_t spaceToEnd = BUFFER_SIZE - rx_tail;

        if (totalSamplesToProcess <= spaceToEnd) {
            memcpy(ptr, &audioBuffer_rx[rx_tail], totalSamplesToProcess);
            rx_tail += totalSamplesToProcess;
        } else {
            memcpy(ptr, &audioBuffer_rx[rx_tail], spaceToEnd);
            memcpy(ptr + spaceToEnd, audioBuffer_rx, totalSamplesToProcess - spaceToEnd);
            rx_tail = totalSamplesToProcess - spaceToEnd;
        }

        // Wrap-around protection
        if (rx_tail >= BUFFER_SIZE) rx_tail -= BUFFER_SIZE;

        bufferFilled_rx -= totalSamplesToProcess;
        if (bufferFilled_rx < 0) bufferFilled_rx = 0;

        SemaphoreP_post(&rxLock);
        status = 1;
    }

    return status;
}

/* ======================================================================= */
/*  SWASRC output copy -> Store Captured Output Samples in audioBuffer_tx  */
/* ======================================================================= */
void mcasp_storeTxSamples(int32_t sampleSize, uint8_t *sample)
{
    SemaphoreP_pend(&txLock, SystemP_WAIT_FOREVER);

    if (bufferFilled_tx + sampleSize > BUFFER_SIZE) {
        SemaphoreP_post(&txLock);
        return;  /* overflow */
    }

    uint32_t spaceToEnd = BUFFER_SIZE - tx_head;

    if (sampleSize <= spaceToEnd) {
        memcpy(&audioBuffer_tx[tx_head], sample, sampleSize);
        tx_head += sampleSize;
    } else {
        memcpy(&audioBuffer_tx[tx_head], sample, spaceToEnd);
        memcpy(audioBuffer_tx, sample + spaceToEnd, sampleSize - spaceToEnd);
        tx_head = sampleSize - spaceToEnd;
    }

    // Wrap-around protection
    if (tx_head >= BUFFER_SIZE) tx_head -= BUFFER_SIZE;

    bufferFilled_tx += sampleSize;
    if (bufferFilled_tx > BUFFER_SIZE) bufferFilled_tx = BUFFER_SIZE;

    SemaphoreP_post(&txLock);
}

/* ============================================================ */
/*  McASP Txcallback -> provide output samples to Tx DMA buffer */
/* ============================================================ */
void mcasp_getTxSamples(int32_t totalSamplesToProcess, uint8_t *ptr)
{
    SemaphoreP_pend(&txLock, SystemP_WAIT_FOREVER);

    if (bufferFilled_tx < totalSamplesToProcess) {
        SemaphoreP_post(&txLock);
        return;  /* underflow */
    }

    uint32_t spaceToEnd = BUFFER_SIZE - tx_tail;

    if (totalSamplesToProcess <= spaceToEnd) {
        memcpy(ptr, &audioBuffer_tx[tx_tail], totalSamplesToProcess);
        tx_tail += totalSamplesToProcess;
    } else {
        memcpy(ptr, &audioBuffer_tx[tx_tail], spaceToEnd);
        memcpy(ptr + spaceToEnd, audioBuffer_tx, totalSamplesToProcess - spaceToEnd);
        tx_tail = totalSamplesToProcess - spaceToEnd;
    }

    // Wrap-around protection
    if (tx_tail >= BUFFER_SIZE) tx_tail -= BUFFER_SIZE;

    bufferFilled_tx -= totalSamplesToProcess;
    if (bufferFilled_tx < 0) bufferFilled_tx = 0;

    SemaphoreP_post(&txLock);
}

/* ============================================================ */
/*                    McASP DMA Txcallback                      */
/* ============================================================ */
void mcasp_txcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{

    /* Increments output sample counter for SW_ASRC input-to-output ratio calculation. */
    gTxDmaCount++;

    /* Fills next TX buffer with processed samples from the algorithm's output FIFO. */
    if(audioPipelineStarted == 1)
    mcasp_getTxSamples(APP_MCASP_AUDIO_BUFF_SIZE_TX, (uint8_t *)&gMcaspAudioBufferTx[mcasptx_writeindex]);

    /* Writes back CPU cache to RAM so DMA reads latest audio data. */
    CacheP_wb(gMcaspAudioBufferTx[mcasptx_writeindex], APP_MCASP_AUDIO_BUFF_SIZE_TX, CacheP_TYPE_ALL);

    /* Re-submits TX transaction to start DMA transfer of next buffer. */
    MCASP_submitTx(handle, transaction);

    /* Advances write index to next buffer in circular array. */
    mcasptx_writeindex = (mcasptx_writeindex + 1) % APP_MCASP_AUDIO_BUFF_COUNT;

}

/* ============================================================ */
/*                    McASP DMA Rxcallback                      */
/* ============================================================ */
void mcasp_rxcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{

    /* Increments input sample counter for SW_ASRC input-to-output ratio calculation. */
    gRxDmaCount++;

    /* Invalidate cache for fresh DMA RX data */
    CacheP_inv(gMcaspAudioBufferRx[mcasprx_readindex], APP_MCASP_AUDIO_BUFF_SIZE_RX, CacheP_TYPE_ALL);

    /* If algorithm is running, feeds fresh RX samples into the processing input FIFO. */
    if(audioPipelineStarted == 1)
    mcasp_storeRxSamples(APP_MCASP_AUDIO_BUFF_SIZE_RX, (uint8_t *)&gMcaspAudioBufferRx[mcasprx_readindex]);

    /* Restart DMA for next buffer */
    MCASP_submitRx(handle, transaction);

    /* Advances the read index to point to the next buffer in the circular array. */
    mcasprx_readindex = (mcasprx_readindex + 1) % APP_MCASP_AUDIO_BUFF_COUNT;

}

/* ============================================================ */
/*                   Timer callback function                    */
/* ============================================================ */
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
/* ============================================================ */
/*           SWASRC initialization function                     */
/* ============================================================ */

void swasrc_init (void *args)
{

    /* SWASRC handle */
    AUDIOLIB_asrc_InitArgs kerInitArgs  = {0};
    int32_t outFrameLength;

    /* Allocate memory for SWASRC handle and matrix transpose handle */
    int32_t handleSize = AUDIOLIB_asrc_getHandleSize(&kerInitArgs);
    handle = malloc(handleSize);

    /* Init properties param */
    uint32_t fsin                   = INPUT_SAMPLE_RATE;
    uint32_t fsout                  = OUTPUT_SAMPLE_RATE;
    uint32_t maxSampleCountPerBlock = INPUT_BLOCKSIZE;
    uint32_t frameModuloFactor      = FRAME_MODULOFACTOR;
    uint32_t sampleDataType         = AUDIOLIB_FLOAT32;
    uint8_t  dataFormat             = AUDIOLIB_DATA_FORMAT_INTERLEAVED;

    /* Sample rate enums */
    sample_rate_t inputsamplerate  = rate_to_enum(INPUT_SAMPLE_RATE);
    sample_rate_t ouputsamplerate = rate_to_enum(OUTPUT_SAMPLE_RATE);

    /* Calculate output frame length based on input/output sample rates */
    outFrameLength = AUDIOLIB_asrc_getOutBufferLength(inputsamplerate, ouputsamplerate, maxSampleCountPerBlock);
    kerInitArgs.inputSampleRate        = inputsamplerate;
    kerInitArgs.outputSampleRate       = ouputsamplerate;
    filtCoeffs          = &audiolib_asrc_filter_coeff[0];

    /* Buffer params */
    AUDIOLIB_bufParams2D_t bufParamsIn = {sampleDataType, NUM_CHANNLES, maxSampleCountPerBlock,NUM_CHANNLES * sizeof(float)};

    AUDIOLIB_bufParams2D_t bufParamsOut = {sampleDataType, NUM_CHANNLES, outFrameLength, NUM_CHANNLES * sizeof(float)};

    /* Pointer allocation */
    nonInterleavedData  = &nonInterleavedDatabuf[0];
    in                  = &inbuf[0];
    out                 = &outbuf[0];
    filterRembuf        = &filterRembuffer[0];

    /*  Kernel handle */
    kerInitArgs.funcStyle              = AUDIOLIB_FUNCTION;
    kerInitArgs.maxSampleCountPerBlock = maxSampleCountPerBlock;
    kerInitArgs.sampleDataType         = sampleDataType;
    kerInitArgs.numChannels            = NUM_CHANNLES;
    kerInitArgs.dataFormat             = dataFormat;
    kerInitArgs.frameModuloFactor      = frameModuloFactor;

    /* Check init params */
    AUDIOLIB_status = AUDIOLIB_asrc_init_checkParams(handle, &bufParamsIn, &bufParamsOut, &kerInitArgs);
    DebugP_assert(AUDIOLIB_status == SystemP_SUCCESS);

    /* Init kernel*/
    AUDIOLIB_status = AUDIOLIB_asrc_init(handle, &bufParamsIn, &bufParamsOut, &kerInitArgs);
    DebugP_assert(AUDIOLIB_status == SystemP_SUCCESS);

    /* Reset state */
    AUDIOLIB_status = AUDIOLIB_asrc_set(handle, AUDIOLIB_ASRC_MODE_RESET, (double) fsout / fsin, nonInterleavedData, in);
    DebugP_assert(AUDIOLIB_status == SystemP_SUCCESS);
}
/* ============================================================ */
/*                  SWASRC processing task                      */
/* ============================================================ */
void swasrc_RxTask(void *args)
{
    int32_t status_free_space   = SystemP_SUCCESS;
    int32_t status_filled_space = SystemP_SUCCESS;

    /* Wait for the audio pipeline to be fully started and initialized before beginning processing */
    while(audioPipelineStarted == 0)
    {
        /* Empty loop - blocks task execution until audioPipelineStarted flag is set */
    }
    while(1)
    {
        /* Check if enough data is available in RX buffer and enough space in TX buffer */
        status_free_space   = mcasp_tx_buffer_freespace();
        /* Get filled space in RX buffer */
        status_filled_space  = mcasp_get_filled_space_rx();
        /* If sufficient data is available, retrieve samples and execute SWASRC processing */
        if((status_filled_space >= (INPUT_BLOCKSIZE*NUM_CHANNLES*BYTES_PER_SAMPLE_ASRC)) && (status_free_space >= ((INPUT_BLOCKSIZE*NUM_CHANNLES*BYTES_PER_SAMPLE_ASRC)*actualRatio)+1))
        {
            /* Get RX samples from McASP RX buffer */
            mcasp_getRxSamples((INPUT_BLOCKSIZE*NUM_CHANNLES*BYTES_PER_SAMPLE_ASRC), (uint8_t *)local_buf_rx_tx);
            /* Execute SWASRC processing on the retrieved samples */
            swasrc_exec(local_buf_rx_tx);
        }
        else
        {
            /* Brief delay to prevent busy-waiting when insufficient data/space */
            ClockP_usleep(50);
        }
    }
}
/* ============================================================ */
/*                   SWASRC execution function                  */
/* ============================================================ */
void swasrc_exec(int32_t *g_inbuf)
{
    int32_t     status = SystemP_SUCCESS;
    uint32_t i = 0;

    uint32_t sampleCount_rx = (INPUT_BLOCKSIZE*NUM_CHANNLES*BYTES_PER_SAMPLE_ASRC) / sizeof(int32_t);

    /* Convert Q31 fixed-point input samples to float in range [-1.0, +1.0] */
    for (i = 0; i < sampleCount_rx; i++)
    {
        int32_t input = (int32_t)g_inbuf[i];
        in[i] = (float)input / Q31_TO_FLOAT_SCALE;
    }


    /* sw-asrc exec */
    if (AUDIOLIB_status == AUDIOLIB_SUCCESS)
    {

        /* Validate input/output parameters before execution */
        status = AUDIOLIB_asrc_exec_checkParams(handle, in, nonInterleavedData, filtCoeffs,
                                                filterRembuf, out, &execInArgs, &execOutArgs);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Execute ASRC processing: convert input to output at adjusted rate */
        status = AUDIOLIB_asrc_exec(handle, in, nonInterleavedData, filtCoeffs, filterRembuf, out, &execInArgs, &execOutArgs);
        DebugP_assert(status == SystemP_SUCCESS);

    }

    /* Total number of output samples produced by ASRC */
    uint32_t words = execOutArgs.outputSampleCount * NUM_CHANNLES;

    /* Clip and convert float output [-1.0, +1.0] to Q31 fixed-point format */
    for (i = 0; i < words; i++)
    {
       float output = out[i];
       if (output > 1.0f) output = 1.0f;
       if (output < -1.0f) output = -1.0f;
        g_inbuf[i] = (int32_t)(output * FLOAT_TO_Q31_SCALE); // float back to Q31
    }

    /* Store processed samples into McASP TX buffer for playback */
    mcasp_storeTxSamples(words*4, (uint8_t *)g_inbuf);
}


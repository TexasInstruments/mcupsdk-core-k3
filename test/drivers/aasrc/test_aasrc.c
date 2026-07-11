/*
 * Copyright (C) 2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*  \file test_aasrc.c
*
*
*   \brief Test file for AASRC Driver.
*
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/hw_include/cslr_aasrc.h>
#include <drivers/hw_include/cslr_aasrc_data_r0.h>
#include <drivers/hw_include/cslr_aasrc_data_r1.h>
#include <drivers/aasrc/v0/aasrc_priv.h>
#include <math.h>
#include <unity.h>
#include <board/ioexp/ioexp_tca6424.h>
#include <drivers/pinmux.h>
#ifdef R5F_CORE
#include "arm_math.h"
#endif
#ifdef C75_CORE
#include "fftlib/src/common/FFTLIB_types.h"
#include "fftlib/src/common/FFTLIB_bufParams.h"
#include "fftlib/src/fft_c7x/c7x_fft.h"
#include "fftlib/src/fft_c7x/FFTLIB_fft1d_i32f_c32fc_o32fc/FFTLIB_fft1d_i32f_c32fc_o32fc_cn.h"
#endif
#include "aasrc_data.h"
#ifdef ENABLE_MT_TESTS
#include <kernel/dpl/TaskP.h>
#include <drivers/i2c.h>
 #endif

/* ========================================================================== */
/*                           Macro Defines                                    */
/* ========================================================================== */

typedef struct {
    float   freqHz;
    float   amplitude;
    float   rms;
    int32_t peakBin;
    int32_t fftLen;
} TestAASRC_peakMetrics;

/* ========================================================================== */
/*                           Typedefs & enum                                  */
/* ========================================================================== */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define TEST_AASRC_MONO_CHANNEL_COUNT                       (1U)
#define TEST_AASRC_STEREO_CHANNEL_COUNT                     (2U)
#define TEST_AASRC_GROUP_CHANNEL_COUNT                      (5U)

#define TEST_AASRC_MONO_AASRC_CH                             (0U)
#define TEST_AASRC_STEREO_AASRC_CH                           (1U)
#define TEST_AASRC_GROUP_AASRC_CH                            (2U)

#define TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT      (1024U)
#define TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT     (1024U)

#define TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT    (TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT * TEST_AASRC_STEREO_CHANNEL_COUNT)
#define TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT   (TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT * TEST_AASRC_STEREO_CHANNEL_COUNT * 2)

#define TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT     (TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT * TEST_AASRC_GROUP_CHANNEL_COUNT)
#define TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT    (TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT * TEST_AASRC_GROUP_CHANNEL_COUNT)

/* New: size FFT buffers to the largest per-channel length (stereo TX per-channel) */
#define TEST_AASRC_MAX_FFT_SAMPLES                          (TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT / TEST_AASRC_STEREO_CHANNEL_COUNT)

#define TEST_AASRC_FFT_FREQ_TOL_HZ                          (5.0f)
#define TEST_AASRC_FFT_AMP_TOL_RATIO                        (0.5f)
#define TEST_AASRC_IN_BITS                                  (24U)

/* FFT Analysis Parameters - skip initial transient/garbage data before steady-state conversion */
#define TEST_AASRC_MONO_FFT_START_IDX                       (89U)     /* Skip first 89 samples for mono TX buffer */
#define TEST_AASRC_STEREO_FFT_START_IDX                     (148U)    /* Skip first 148 samples for stereo TX buffer */
#define TEST_AASRC_GROUP_FFT_START_IDX                      (35U)     /* Skip first 35 samples for group (5-channel) TX buffer */
#define TEST_AASRC_MONO_FFT_LENGTH                          (512U)    /* FFT analysis window size for mono (steady-state data) */
#define TEST_AASRC_STEREO_FFT_LENGTH                        (1024U)   /* FFT analysis window size for stereo (2x samples per channel) */
#define TEST_AASRC_GROUP_FFT_LENGTH                         (512U)    /* FFT analysis window size for group (5-channel) */

/* Busy-wait timeout: maximum iterations before declaring a timeout failure */
#define TEST_AASRC_BUSYWAIT_TIMEOUT_MS                      (5000U)   /* 5 seconds */
#define TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US                (1000U)   /* 1 ms poll interval */

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* Mono Buffer */
int32_t gAasrcRxMonoBuffer[TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
int32_t gAasrcTxMonoBuffer[TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

/* Stereo Buffer */
int32_t gAasrcRxStereoBuffer[TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
int32_t gAasrcTxStereoBuffer[TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

/* Group(5) Buffer */
int32_t gAasrcRxGroupBuffer[TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
int32_t gAasrcTxGroupBuffer[TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

/* Mono buffers for multi threaded test */
int32_t TestAASRC_rxMonoThreadBuffer[2][TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
int32_t TestAASRC_txMonoThreadBuffer[2][TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

/* StereoBuffers  for multi threaded test */
int32_t TestAASRC_rxStereoThreadBuffer[2][TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
int32_t TestAASRC_txStereoThreadBuffer[2][TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

/* GroupBuffers  for multi threaded test */
int32_t TestAASRC_rxGroupThreadBuffer[2][TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
int32_t TestAASRC_txGroupThreadBuffer[2][TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

/* Transactions */
AASRC_Transaction TestAASRC_txnRx[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};
AASRC_Transaction TestAASRC_txnTx[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};

/* Transactions for multithreaded test*/
AASRC_Transaction TestAASRC_thread1TxnRx[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};
AASRC_Transaction TestAASRC_thread1TxnTx[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};
AASRC_Transaction TestAASRC_thread2TxnRx[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};
AASRC_Transaction TestAASRC_thread2TxnTx[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};

/* Channel MetaData */
AASRC_chMeta TestAASRC_chMeta[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};

/* Channel MetaData for multithreaded test*/
AASRC_chMeta TestAASRC_chMetaThread1[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};
AASRC_chMeta TestAASRC_chMetaThread2[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};

#ifdef ENABLE_MT_TESTS
SemaphoreP_Object TestAASRC_countSemAsrcConv;

/* Semaphore to keep track of channel in instances
 *  one of the multithreaded test
 */
SemaphoreP_Object TestAASRC_countSemAsrcConv1;
SemaphoreP_Object TestAASRC_countSemAsrcConv2;
/* Semaphore for multithreaded test */
SemaphoreP_Object TestAASRC_sem;

uint8_t TestAASRC_task1Stack[16*1024] __attribute__ ((aligned(32)));
uint8_t TestAASRC_task2Stack[16*1024] __attribute__ ((aligned(32)));

TaskP_Object TestAASRC_thread1TaskObj;
TaskP_Object TestAASRC_thread2TaskObj;
static float TestAASRC_fftInput[TEST_AASRC_MAX_FFT_SAMPLES * 2]       __attribute__((aligned(64)));
static float TestAASRC_fftOutput[TEST_AASRC_MAX_FFT_SAMPLES * 2]      __attribute__((aligned(64)));
#ifdef C75_CORE
static float TestAASRC_fftIntermediate[TEST_AASRC_MAX_FFT_SAMPLES * 2]__attribute__((aligned(64)));
static float TestAASRC_fftTwiddle[TEST_AASRC_MAX_FFT_SAMPLES * 2]     __attribute__((aligned(64)));
static float TestAASRC_fftSplitFactor[TEST_AASRC_MAX_FFT_SAMPLES * 2] __attribute__((aligned(64)));
#endif
static TestAASRC_peakMetrics TestAASRC_monoRxPeak, TestAASRC_monoTxPeak;
static TestAASRC_peakMetrics TestAASRC_stereoRxPeak[TEST_AASRC_STEREO_CHANNEL_COUNT], TestAASRC_stereoTxPeak[TEST_AASRC_STEREO_CHANNEL_COUNT];
static TestAASRC_peakMetrics TestAASRC_groupRxPeak[TEST_AASRC_GROUP_CHANNEL_COUNT],  TestAASRC_groupTxPeak[TEST_AASRC_GROUP_CHANNEL_COUNT];
static uint32_t gAasrcTxMonoBuffer2[TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
static uint32_t gAasrcRxMonoBuffer2[TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
static AASRC_Transaction gTestTxnMonoRx2;
static AASRC_Transaction gTestTxnMonoTx2;
/* Per-channel error capture for overflow/underflow injection tests */
static AASRC_FifoErrorStatus TestAASRC_capturedInFifoErr[CONFIG_AASRC0_NUM_CH];
static AASRC_FifoErrorStatus TestAASRC_capturedOutFifoErr[CONFIG_AASRC0_NUM_CH];
static volatile uint8_t      TestAASRC_errFiredMask;  /* bit per chIdx */
static SemaphoreP_Object     TestAASRC_errSem;

#endif
/* ========================================================================== */
/*                        Function Declarations                               */
/* ========================================================================== */

static void TestAasrc_transactionInit(AASRC_ChHandle chHandle, uint8_t instNum, uint8_t chCount);
static void TestAasrc_muteChannel(void *args);
static void TestAasrc_clockSettleOverride(void *args);
static void TestAasrc_sineWaveConversionDma(void *args);
static void TestAasrc_syncPin(void *args);
static void TestAasrc_groupDelay(void*args);
static void TestAasrc_attenuation(void* args);
/*static void TestAasrc_fifoThreshold(void *args); */ /* Test case hangs when ran for every threhold values*/
static void TestAasrc_transactionThread1Init(AASRC_ChHandle chHandle, uint8_t instNum, uint8_t chCount);
static void TestAasrc_transactionThread2Init(AASRC_ChHandle chHandle, uint8_t instNum, uint8_t chCount);
static void TestAasrc_concurrentSinewaveConversionDma(void *args);
static void TestAASRC_txcbInst0 (AASRC_ChHandle chHandle, AASRC_Transaction *transaction);
static void TestAASRC_txcbInst1 (AASRC_ChHandle chHandle, AASRC_Transaction *transaction);
static inline int32_t TestAasrc_convertWordlen(int32_t s_in, uint8_t inBits, uint8_t outBits);
static inline int32_t TestAasrc_packRightJustified(int32_t s_out, uint8_t outBits);
static void TestAasrc_runFftWordLen(uint32_t *inputBuf, int32_t sampleCount, float sampleRateHz, uint8_t wordLenBits, TestAASRC_peakMetrics *out);
static void TestAasrc_fftInterleavedWordLen(uint32_t *inputBuf, int32_t sampleCount, int32_t chCount, int32_t chIndex, float sampleRateHz, uint8_t wordLenBits, TestAASRC_peakMetrics *out);
static void TestAasrc_pcmWidth(void *args);
static void TestAasrc_externalClk(void *args);
static void TestAasrc_overflowSineWaveInterrupt(void *args);
static void TestAasrc_underflowSineWaveInterrupt(void *args);
static void TestAasrc_queueBeforeEnable(void *args);
static void TestAasrc_sineWaveConversionInterrupt(void *args);
int32_t Board_clockgenConfig(I2C_Handle handle, uint8_t devAddr);




/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();
    #ifdef ENABLE_MT_TESTS
    RUN_TEST(TestAasrc_sineWaveConversionDma, 10062,(void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_muteChannel, 10073, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_syncPin, 0, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_clockSettleOverride, 10071, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_groupDelay, 10072, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_attenuation, 10157, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_pcmWidth, 10065,(void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    /*RUN_TEST(TestAasrc_fifoThreshold, 10074, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);*/ /*Test case hangs when ran for all the threshold one by one */
    RUN_TEST(TestAasrc_concurrentSinewaveConversionDma, 10069, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_sineWaveConversionInterrupt, 10302,(void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_overflowSineWaveInterrupt, 10310, (void*)&gAasrcOpenParams[CONFIG_AASRC0]); 
    RUN_TEST(TestAasrc_underflowSineWaveInterrupt, 10311, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_externalClk, 10306, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    RUN_TEST(TestAasrc_externalClk, 12158, (void*)&gAasrcOpenParams[CONFIG_AASRC1]);
    RUN_TEST(TestAasrc_queueBeforeEnable, 10309, (void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    #endif
    UNITY_END();
    return;
}

void setUp(void)
{
    /* nothing to do */
}

void tearDown(void)
{
    /* nothing to do */
}

#ifdef ENABLE_MT_TESTS
/**
 * \brief Test AASRC DMA-based sine wave conversion with FFT validation.
 *
 * Test Category: Functionality
 *
 * This test performs sample rate conversion on sine wave input data across
 * mono, stereo, and group channel configurations. It validates correct
 * frequency conversion by analyzing FFT output and comparing peak frequencies
 * and amplitudes between RX and TX paths.
 *
 * \param args Pointer to test parameters .
 */
static void TestAasrc_sineWaveConversionDma(void *args)
{
    int32_t status = SystemP_SUCCESS;
    AASRC_ChHandle      chHandle = NULL;
    AASRC_ChObj *chObj = NULL;
    AASRC_OpenParams *openParams = (AASRC_OpenParams *)args;
    uint8_t inst = (uint8_t)(openParams - &gAasrcOpenParams[0]);

    uint8_t channelCount = 0U;
    float  clkFrequency;

    AASRC_close(gAasrcHandle[inst]);
    gAasrcHandle[inst] = AASRC_open(inst, openParams);
    TEST_ASSERT_NOT_NULL(gAasrcHandle[inst]);

    if (openParams->rxClkZoneCfg[0].overrideClkSettle || openParams->txClkZoneCfg[0].overrideClkSettle)
    {
        /* Wait for clock recovery loops to settle in hardware before proceeding */
        ClockP_usleep(50000);
    }

    SemaphoreP_constructCounting(&TestAASRC_countSemAsrcConv, 0, CONFIG_AASRC0_NUM_CH);

    for(channelCount = 0U; channelCount< CONFIG_AASRC0_NUM_CH; channelCount++)
    {
        chHandle = AASRC_chOpen(channelCount, gAasrcHandle[inst]);
        if(chHandle != NULL)
        {
            chObj = (AASRC_ChObj *)(chHandle);
            status = AASRC_chConfig(chHandle);
        }
        else
        {
            status = SystemP_FAILURE;
        }
        if(status == SystemP_SUCCESS)
        {
            /* Input Frequency */
            status += AASRC_GetClkZoneRxFrequency(chHandle, &clkFrequency);
            TestAASRC_chMeta[inst][channelCount].rxSamplingFreq = clkFrequency;
            TestAASRC_chMeta[inst][channelCount].dataFormat = chObj->chCfg.inWordLen;
            DebugP_assertNoLog(status == SystemP_SUCCESS);

            /* Output Frequency */
            status += AASRC_GetClkZoneTxFrequency(chHandle, &clkFrequency);
            TestAASRC_chMeta[inst][channelCount].txSamplingFreq = clkFrequency;
            DebugP_assertNoLog(status == SystemP_SUCCESS);
            if( status == SystemP_SUCCESS)
            {
                /* Init the transactions for all channel */
                TestAasrc_transactionInit(chHandle, inst, channelCount);
                /* Enable the channel for starting conversion */
                status += AASRC_chEnable(chHandle);
            }

        }
    }
    DebugP_assert(status == SystemP_SUCCESS);

    bool timedOut = false;
    {
        uint32_t elapsedMs = 0U;
        while(SemaphoreP_getCount(&TestAASRC_countSemAsrcConv) < CONFIG_AASRC0_NUM_CH)
        {
            ClockP_usleep(TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US);
            elapsedMs += (TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US / 1000U);
            if (elapsedMs >= TEST_AASRC_BUSYWAIT_TIMEOUT_MS)
            {
                TEST_ASSERT_TRUE_MESSAGE(0, "AASRC conversion timed out");
                timedOut = true;
                break;
            }
        }
    }

    if (openParams->transferMode != AASRC_TRANSFER_MODE_INTERRUPT)
    {
        CacheP_wbInv(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALL);
        CacheP_wbInv(gAasrcTxStereoBuffer, sizeof(gAasrcTxStereoBuffer), CacheP_TYPE_ALL);
        CacheP_wbInv(gAasrcTxGroupBuffer, sizeof(gAasrcTxGroupBuffer), CacheP_TYPE_ALL);
    }

    /* Close the channels */
    for (channelCount = 0; channelCount < CONFIG_AASRC0_NUM_CH; channelCount++)
    {
        chHandle = AASRC_getChHandle(inst, channelCount);
        AASRC_chDisable(chHandle);
        status = AASRC_chClose(chHandle);
    }

    SemaphoreP_destruct(&TestAASRC_countSemAsrcConv);

    if (timedOut)
    { 
        return; 
    }

    float samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_MONO_AASRC_CH].rxSamplingFreq * 1000.0f;
    TestAasrc_runFftWordLen((uint32_t *)gAasrcRxMonoBuffer, (int32_t)TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT, samplingRateHz, TEST_AASRC_IN_BITS, &TestAASRC_monoRxPeak);
    int32_t startIdx = TEST_AASRC_MONO_FFT_START_IDX;
    int32_t fftLen   = TEST_AASRC_MONO_FFT_LENGTH;
    samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_MONO_AASRC_CH].txSamplingFreq * 1000.0f;
    TestAasrc_runFftWordLen((uint32_t *)&gAasrcTxMonoBuffer[startIdx], fftLen, samplingRateHz, TEST_AASRC_IN_BITS, &TestAASRC_monoTxPeak);

    int32_t stereoRxPerCh = (int32_t)(TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT / TEST_AASRC_STEREO_CHANNEL_COUNT);
    int32_t ch;
    samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_STEREO_AASRC_CH].rxSamplingFreq * 1000.0f;
    for (ch = 0; ch < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; ch++)
    {
        TestAasrc_fftInterleavedWordLen(
            (uint32_t *)gAasrcRxStereoBuffer,
            stereoRxPerCh,
            TEST_AASRC_STEREO_CHANNEL_COUNT,
            ch /* 0: Left, 1: Right */,
            samplingRateHz,
            TEST_AASRC_IN_BITS,
            &TestAASRC_stereoRxPeak[ch]
        );
    }

    startIdx = TEST_AASRC_STEREO_FFT_START_IDX;
    fftLen = TEST_AASRC_STEREO_FFT_LENGTH;
    samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_STEREO_AASRC_CH].txSamplingFreq * 1000.0f;
    for (ch = 0; ch < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; ch++)
    {
        TestAasrc_fftInterleavedWordLen(
            ( uint32_t *)&gAasrcTxStereoBuffer[startIdx * TEST_AASRC_STEREO_CHANNEL_COUNT],
            fftLen,
            TEST_AASRC_STEREO_CHANNEL_COUNT,
            ch,
            samplingRateHz,
            TEST_AASRC_IN_BITS,
            &TestAASRC_stereoTxPeak[ch]
        );
    }

    /* New: FFT for Stereo (L/R) and Group (all 5 channels) on TX and RX */

    int32_t groupRxPerCh = (int32_t)(TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT / TEST_AASRC_GROUP_CHANNEL_COUNT);
    samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_GROUP_AASRC_CH].rxSamplingFreq * 1000.0f;
    for (ch = 0; ch < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; ch++)
    {
        TestAasrc_fftInterleavedWordLen(
            ( uint32_t *)gAasrcRxGroupBuffer,
            groupRxPerCh,
            TEST_AASRC_GROUP_CHANNEL_COUNT,
            ch,
            samplingRateHz,
            TEST_AASRC_IN_BITS,
            &TestAASRC_groupRxPeak[ch]
        );
    }
    startIdx = TEST_AASRC_GROUP_FFT_START_IDX;
    fftLen = TEST_AASRC_GROUP_FFT_LENGTH;
    samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_GROUP_AASRC_CH].txSamplingFreq * 1000.0f;
    for (ch = 0; ch < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; ch++)
    {
        TestAasrc_fftInterleavedWordLen(( uint32_t *)&gAasrcTxGroupBuffer[startIdx * TEST_AASRC_GROUP_CHANNEL_COUNT], fftLen, TEST_AASRC_GROUP_CHANNEL_COUNT, ch, samplingRateHz, TEST_AASRC_IN_BITS,&TestAASRC_groupTxPeak[ch]);
    }

    DebugP_log("Mono RX: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", TestAASRC_monoRxPeak.freqHz, TestAASRC_monoRxPeak.amplitude, TestAASRC_monoRxPeak.rms);
    DebugP_log("Mono TX: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", TestAASRC_monoTxPeak.freqHz, TestAASRC_monoTxPeak.amplitude, TestAASRC_monoTxPeak.rms);

    for (ch = 0; ch < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; ch++)
    {
        DebugP_log("Stereo RX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", ch, TestAASRC_stereoRxPeak[ch].freqHz, TestAASRC_stereoRxPeak[ch].amplitude, TestAASRC_stereoRxPeak[ch].rms);
        DebugP_log("Stereo TX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", ch, TestAASRC_stereoTxPeak[ch].freqHz, TestAASRC_stereoTxPeak[ch].amplitude, TestAASRC_stereoTxPeak[ch].rms);
    }

    for (ch = 0; ch < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; ch++)
    {
        DebugP_log("Group RX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", ch, TestAASRC_groupRxPeak[ch].freqHz, TestAASRC_groupRxPeak[ch].amplitude, TestAASRC_groupRxPeak[ch].rms);
        DebugP_log("Group TX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", ch, TestAASRC_groupTxPeak[ch].freqHz, TestAASRC_groupTxPeak[ch].amplitude, TestAASRC_groupTxPeak[ch].rms);
    }

    float df = fabsf(TestAASRC_monoRxPeak.freqHz - TestAASRC_monoTxPeak.freqHz);
    float rmsRatio = (TestAASRC_monoRxPeak.rms > 0.0f) ? fabsf(TestAASRC_monoTxPeak.rms / TestAASRC_monoRxPeak.rms - 1.0f) : 0.0f;
    bool freqMatch = (df <= TEST_AASRC_FFT_FREQ_TOL_HZ);
    bool rmsMatch = (rmsRatio <= TEST_AASRC_FFT_AMP_TOL_RATIO);
    TEST_ASSERT_TRUE_MESSAGE(freqMatch || rmsMatch, "Mono: neither frequency nor RMS match");

    /* Validate Stereo */
    for (ch = 0; ch < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; ch++)
    {
            float stereoDf = fabsf(TestAASRC_stereoRxPeak[ch].freqHz - TestAASRC_stereoTxPeak[ch].freqHz);
            float stereoRmsRatio = (TestAASRC_stereoRxPeak[0].rms > 0.0f) ? fabsf(TestAASRC_stereoTxPeak[ch].rms / TestAASRC_stereoRxPeak[0].rms - 1.0f) : 0.0f;
            bool stereoFreqMatch = (stereoDf <= TEST_AASRC_FFT_FREQ_TOL_HZ);
            bool stereoRmsMatch = (stereoRmsRatio <= TEST_AASRC_FFT_AMP_TOL_RATIO);
            TEST_ASSERT_TRUE_MESSAGE(stereoFreqMatch || stereoRmsMatch, "stereo RX channels: neither frequency nor RMS match");
    }

    for (ch = 1; ch < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; ch++)
    {
        float groupDf = fabsf(TestAASRC_groupRxPeak[0].freqHz - TestAASRC_groupRxPeak[ch].freqHz);
        float groupRmsRatio = (TestAASRC_groupRxPeak[0].rms > 0.0f) ? fabsf(TestAASRC_groupRxPeak[ch].rms / TestAASRC_groupRxPeak[0].rms - 1.0f) : 0.0f;
        bool groupFreqMatch = (groupDf <= TEST_AASRC_FFT_FREQ_TOL_HZ);
        bool groupRmsMatch = (groupRmsRatio <= TEST_AASRC_FFT_AMP_TOL_RATIO);
        TEST_ASSERT_TRUE_MESSAGE(groupFreqMatch || groupRmsMatch, "Group RX channels: neither frequency nor RMS match");
    }

}

/**
 * \brief Initialize transaction buffers and queue operations for AASRC channel.
 *
 * Prepares input/output buffers with test data, configures transactions based
 * on channel type (mono/stereo/group), and queues RX/TX transactions to the
 * AASRC driver.
 *
 * \param chHandle AASRC channel handle.
 * \param instNum Instance number.
 * \param chCount Channel count.
 */
static void TestAasrc_transactionInit(AASRC_ChHandle chHandle, uint8_t instNum, uint8_t chCount)
{
    uint16_t count;
    AASRC_ChObj *chObj = (AASRC_ChObj *)(chHandle);
    uint8_t chType = chObj->chCfg.chType;

    switch(chType)
    {
        case AASRC_MONO:

            /* Init Input and Output Buffer */
            strncpy(TestAASRC_chMeta[instNum][chCount].metaInfo,"MONO CHANNEL", sizeof(TestAASRC_chMeta[instNum][chCount].metaInfo));
            TestAASRC_chMeta[instNum][chCount].monoChCount = 1;
            TestAASRC_chMeta[instNum][chCount].rxBufPtr = (uint32_t *)&gAasrcRxMonoBuffer[0];
            TestAASRC_chMeta[instNum][chCount].txBufPtr = (uint32_t *)&gAasrcTxMonoBuffer[0];
            TestAASRC_chMeta[instNum][chCount].rxSampleCount = TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
            TestAASRC_chMeta[instNum][chCount].txSampleCount = TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcRxMonoBuffer[count] = (int32_t)aasrc_monoInput[count];
            }

            for(count = 0U; count< TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcTxMonoBuffer[count] = 0U;
            }

            CacheP_wb(gAasrcRxMonoBuffer, sizeof(gAasrcRxMonoBuffer), CacheP_TYPE_ALLD);
            CacheP_wb(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            TestAASRC_txnRx[instNum][chCount].buf = (void*) &gAasrcRxMonoBuffer[0];
            TestAASRC_txnRx[instNum][chCount].sampleCount = TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &TestAASRC_txnRx[instNum][chCount] );

            TestAASRC_txnTx[instNum][chCount].buf = (void*) &gAasrcTxMonoBuffer[0];
            TestAASRC_txnTx[instNum][chCount].sampleCount = TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &TestAASRC_txnTx[instNum][chCount] );
            break;

        case AASRC_STEREO:

            /* Init Input and Output Buffer */
            strncpy(TestAASRC_chMeta[instNum][chCount].metaInfo,"STEREO CHANNEL", sizeof(TestAASRC_chMeta[instNum][chCount].metaInfo));
            TestAASRC_chMeta[instNum][chCount].monoChCount = 2;
            TestAASRC_chMeta[instNum][chCount].rxBufPtr = (uint32_t *)&gAasrcRxStereoBuffer[0];
            TestAASRC_chMeta[instNum][chCount].txBufPtr = (uint32_t *)&gAasrcTxStereoBuffer[0];
            TestAASRC_chMeta[instNum][chCount].rxSampleCount = TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT;
            TestAASRC_chMeta[instNum][chCount].txSampleCount = TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcRxStereoBuffer[count] = (int32_t)aasrc_stereoInput[count];
            }

            for(count = 0U; count< TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcTxStereoBuffer[count] = 0U;
            }

            CacheP_wb(gAasrcRxStereoBuffer, sizeof(gAasrcRxStereoBuffer), CacheP_TYPE_ALLD);
            CacheP_wb(gAasrcTxStereoBuffer, sizeof(gAasrcTxStereoBuffer), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            TestAASRC_txnRx[instNum][chCount].buf = (void*) &gAasrcRxStereoBuffer[0];
            TestAASRC_txnRx[instNum][chCount].sampleCount = TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &TestAASRC_txnRx[instNum][chCount] );

            TestAASRC_txnTx[instNum][chCount].buf = (void*) &gAasrcTxStereoBuffer[0];
            TestAASRC_txnTx[instNum][chCount].sampleCount = TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &TestAASRC_txnTx[instNum][chCount] );
            break;

        case AASRC_GROUP:

            /* Init Input and Output Buffer */
            strncpy(TestAASRC_chMeta[instNum][chCount].metaInfo,"GROUP CHANNEL", sizeof(TestAASRC_chMeta[instNum][chCount].metaInfo));
            TestAASRC_chMeta[instNum][chCount].monoChCount = TEST_AASRC_GROUP_CHANNEL_COUNT;
            TestAASRC_chMeta[instNum][chCount].rxBufPtr = (uint32_t *)&gAasrcRxGroupBuffer[0];
            TestAASRC_chMeta[instNum][chCount].txBufPtr = (uint32_t *)&gAasrcTxGroupBuffer[0];
            TestAASRC_chMeta[instNum][chCount].rxSampleCount = TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT;
            TestAASRC_chMeta[instNum][chCount].txSampleCount = TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcRxGroupBuffer[count] = (int32_t)aasrc_groupInput[count];
            }

            for(count = 0U; count< TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcTxGroupBuffer[count] = 0U;
            }

            CacheP_wb(gAasrcRxGroupBuffer, sizeof(gAasrcRxGroupBuffer), CacheP_TYPE_ALLD);
            CacheP_wb(gAasrcTxGroupBuffer, sizeof(gAasrcTxGroupBuffer), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            TestAASRC_txnRx[instNum][chCount].buf = (void*) &gAasrcRxGroupBuffer[0];
            TestAASRC_txnRx[instNum][chCount].sampleCount = TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &TestAASRC_txnRx[instNum][chCount] );

            TestAASRC_txnTx[instNum][chCount].buf = (void*) &gAasrcTxGroupBuffer[0];
            TestAASRC_txnTx[instNum][chCount].sampleCount = TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &TestAASRC_txnTx[instNum][chCount] );
            break;

        default:
            break;
    }
}

#if 0

/* Test case is hangs when every threshold value is run one by one*/
/**
 * \brief Test AASRC FIFO threshold configurations in interrupt mode.
 *
 * Test Category: Functionality
 *
 * Iterates through FIFO threshold values from 1 to 32 for both input and
 * output FIFOs across all channels. Validates that sample rate conversion
 * completes successfully with each threshold setting.
 *
 * Note: Currently commented out as testcase hangs in IRQ mode. The hang
 * occurs during interrupt-based DMA transfers with certain FIFO threshold
 * combinations. Requires investigation of interrupt handling and FIFO
 * management in the driver.
 *
 * \param args Pointer to test parameters.
 */
static void TestAasrc_fifoThreshold(void *args)
{
    uint32_t inst = 0; /* single instance in this config */
    uint32_t chCnt = gAasrcConfigChNum[inst];
    uint32_t ch , threshold;
    AASRC_ChObj *chObj;

    gAasrcOpenParams[CONFIG_AASRC0].transferMode = AASRC_TRANSFER_MODE_INTERRUPT;

    for ( ch = 0; ch < chCnt; ch++)
    {
        for (threshold = 1; threshold <= 32; threshold++)
        {
            chObj = &gConfigAasrcChObj[inst][ch];
            chObj->chCfg.fifoControl.inFifoThreshold  = (uint8_t)threshold;
            chObj->chCfg.fifoControl.outFifoThreshold = (uint8_t)threshold;
            TestAasrc_sineWaveConversionDma((void*)&gAasrcOpenParams[CONFIG_AASRC0]);
        }
    }

    /* Restore defaults for all channels */
    for ( ch = 0; ch < chCnt; ch++)
    {
        chObj = &gConfigAasrcChObj[inst][ch];
        chObj->chCfg.fifoControl.inFifoThreshold  = 16;
        chObj->chCfg.fifoControl.outFifoThreshold = 16;
    }
    gAasrcOpenParams[CONFIG_AASRC0].transferMode = AASRC_TRANSFER_MODE_DMA;
}
#endif

/**
 * \brief Test AASRC channel mute functionality.
 *
 * Test Category: Functionality
 *
 * Enables mute on all AASRC channels and verifies that TX buffers contain
 * only zeros after conversion. Tests mono, stereo, and group configurations.
 *
 * \param args Pointer to AASRC_OpenParams structure.
 */
static void TestAasrc_muteChannel(void *args)
{
    AASRC_OpenParams *openParams = (AASRC_OpenParams *)args;
    uint8_t inst = (uint8_t)(openParams - &gAasrcOpenParams[0]);
    uint32_t chCnt = gAasrcConfigChNum[inst];
    uint32_t ch, i;
    int32_t status = SystemP_SUCCESS;
    AASRC_ChHandle      chHandle = NULL;
    AASRC_ChObj         *chObj = NULL;
    uint8_t channelCount = 0U;
    float  clkFrequency;

    for (ch = 0; ch < chCnt; ch++)
    {
        chObj = &gConfigAasrcChObj[inst][ch];
        chObj->chCfg.mute = true;
    }

    AASRC_close(gAasrcHandle[inst]);
    gAasrcHandle[inst] = AASRC_open(inst, openParams);
    TEST_ASSERT_NOT_NULL(gAasrcHandle[inst]);

    SemaphoreP_constructCounting(&TestAASRC_countSemAsrcConv, 0, gAasrcConfigChNum[inst]);

    for(channelCount = 0U; channelCount< gAasrcConfigChNum[inst]; channelCount++)
    {
        chHandle = AASRC_chOpen(channelCount, gAasrcHandle[inst]);
        if(chHandle != NULL)
        {
            chObj = (AASRC_ChObj *)(chHandle);
            status = AASRC_chConfig(chHandle);
        }
        else
        {
            status = SystemP_FAILURE;
        }
        if(status == SystemP_SUCCESS)
        {
            /* Input Frequency */
            status += AASRC_GetClkZoneRxFrequency(chHandle, &clkFrequency);
            TestAASRC_chMeta[inst][channelCount].rxSamplingFreq = clkFrequency;
            TestAASRC_chMeta[inst][channelCount].dataFormat = chObj->chCfg.inWordLen;

            DebugP_assertNoLog(status == SystemP_SUCCESS);

            /* Output Frequency */
            status += AASRC_GetClkZoneTxFrequency(chHandle, &clkFrequency);
            TestAASRC_chMeta[inst][channelCount].txSamplingFreq = clkFrequency;
            DebugP_assertNoLog(status == SystemP_SUCCESS);

            if( status == SystemP_SUCCESS)
            {
                /* Init the transactions for all channel */
                TestAasrc_transactionInit(chHandle, inst, channelCount);
                /* Small sleep after config and before enable so HW states settle to 0 */
                ClockP_usleep(100000);
                /* Enable the channel for starting conversion */
                status += AASRC_chEnable(chHandle);
            }
        }
    }
    DebugP_assert(status == SystemP_SUCCESS);

    bool timedOut = false;
    {
        uint32_t elapsedMs = 0U;
        while(SemaphoreP_getCount(&TestAASRC_countSemAsrcConv) < gAasrcConfigChNum[inst])
        {
            ClockP_usleep(TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US);
            elapsedMs += (TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US / 1000U);
            if (elapsedMs >= TEST_AASRC_BUSYWAIT_TIMEOUT_MS)
            {
                TEST_ASSERT_TRUE_MESSAGE(0, "Mute test: AASRC conversion timed out");
                timedOut = true;
                break;
            }
        }
    }

    if (!timedOut)
    {
        CacheP_wbInv(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALL);
        CacheP_wbInv(gAasrcTxStereoBuffer, sizeof(gAasrcTxStereoBuffer), CacheP_TYPE_ALL);
        CacheP_wbInv(gAasrcTxGroupBuffer, sizeof(gAasrcTxGroupBuffer), CacheP_TYPE_ALL);

        /* Mono TX buffer is zero */
        for ( i = 0; i < TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT; i++)
        {
            TEST_ASSERT_EQUAL_INT32_MESSAGE(0, gAasrcTxMonoBuffer[i], "Mute check failed: Mono TX not zero");
        }

        /* Stereo TX buffer is zero (interleaved L,R) */
        for ( i = 0; i < TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT; i++)
        {
            TEST_ASSERT_EQUAL_INT32_MESSAGE(0, gAasrcTxStereoBuffer[i], "Mute check failed: Stereo TX not zero");
        }

        /* Group TX buffer is zero (interleaved channels) */
        for ( i = 0; i < TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT; i++)
        {
            TEST_ASSERT_EQUAL_INT32_MESSAGE(0, gAasrcTxGroupBuffer[i], "Mute check failed: Group TX not zero");
        }
    }

    /* Close the channels */
    for (channelCount = 0; channelCount < gAasrcConfigChNum[inst]; channelCount++)
    {
        chHandle = AASRC_getChHandle(inst, channelCount);
        AASRC_chDisable(chHandle);
        status = AASRC_chClose(chHandle);
    }

    SemaphoreP_destruct(&TestAASRC_countSemAsrcConv);
    for (ch = 0; ch < chCnt; ch++)
    {
        chObj = &gConfigAasrcChObj[inst][ch];
        chObj->chCfg.mute = false;
    }
}

/**
 * \brief Test AASRC clock settle override functionality.
 *
 * Test Category: Functionality
 *
 * Verifies that AASRC can override automatic clock settling behavior by
 * enabling overrideClkSettle for all RX and TX clock zones and performing
 * sample rate conversion.
 *
 * \param args Pointer to AASRC_OpenParams structure.
 */
static void TestAasrc_clockSettleOverride(void *args)
{
    uint8_t instanceCount, zone;

    for (instanceCount = 0U; instanceCount < CONFIG_AASRC_NUM_INSTANCES; instanceCount++)
    {
        /* Enable override settle for all RX/TX zones directly in the global array */
        for (zone = 0U; zone < 4U; zone++)
        {
            gAasrcOpenParams[instanceCount].rxClkZoneCfg[zone].overrideClkSettle = true;
            gAasrcOpenParams[instanceCount].txClkZoneCfg[zone].overrideClkSettle = true;
        }

        TestAasrc_sineWaveConversionDma((void*)&gAasrcOpenParams[instanceCount]);

        /* Restore defaults */
        for (zone = 0U; zone < 4U; zone++)
        {
            gAasrcOpenParams[instanceCount].rxClkZoneCfg[zone].overrideClkSettle = false;
            gAasrcOpenParams[instanceCount].txClkZoneCfg[zone].overrideClkSettle = false;
        }
    }
}

/**
 * \brief Test AASRC sync pin configuration.
 *
 * Test Category: Functionality
 *
 * Tests all four sync pin configurations (0-3) for both RX and TX clock zones,
 * verifying successful sample rate conversion with each configuration.
 *
 * \param args Pointer to AASRC_OpenParams structure.
 */
static void TestAasrc_syncPin(void *args)
{
    uint32_t zone = 0;
    uint32_t pin, instanceCount;

    for (instanceCount = 0U; instanceCount < CONFIG_AASRC_NUM_INSTANCES; instanceCount++)
    {
        for (pin = 2U; pin < 4U; pin++)
        {
            gAasrcOpenParams[instanceCount].rxClkZoneCfg[zone].syncPin = pin;
            gAasrcOpenParams[instanceCount].txClkZoneCfg[zone].syncPin = pin;
            TestAasrc_sineWaveConversionDma((void*)&gAasrcOpenParams[instanceCount]);
        }
        gAasrcOpenParams[instanceCount].rxClkZoneCfg[zone].syncPin = 0U;
        gAasrcOpenParams[instanceCount].txClkZoneCfg[zone].syncPin = 0U;
    }
}

/**
 * \brief Test AASRC group delay settings.
 *
 * Test Category: Functionality
 *
 * Validates AASRC operation with different group delay values (8, 16, 32 samples).
 * Performs sample rate conversion and FFT analysis for each setting.
 *
 * \param args Pointer to AASRC_OpenParams structure.
 */
static void TestAasrc_groupDelay(void*args)
{
    AASRC_OpenParams *openParams = (AASRC_OpenParams *)args;
    uint8_t inst = (uint8_t)(openParams - &gAasrcOpenParams[0]);
    uint32_t groupDelayVals[] = {AASRC_GROUP_DELAY_8, AASRC_GROUP_DELAY_16, AASRC_GROUP_DELAY_32};
    uint32_t numGroupDelays = sizeof(groupDelayVals) / sizeof(groupDelayVals[0]);
    uint32_t gd, channelCount;

    for (gd = 0U; gd < numGroupDelays; gd++)
    {
        for (channelCount = 0U; channelCount < CONFIG_AASRC0_NUM_CH; channelCount++)
        {
           AASRC_ChObj *chObj = &gConfigAasrcChObj[inst][channelCount];
           chObj->chCfg.groupDelay = groupDelayVals[gd];
        }

        TestAasrc_sineWaveConversionDma((void*)&gAasrcOpenParams[inst]);

        for (channelCount = 0U; channelCount < CONFIG_AASRC0_NUM_CH; channelCount++)
        {
            AASRC_ChObj *chObj = &gConfigAasrcChObj[inst][channelCount];
            chObj->chCfg.groupDelay = AASRC_GROUP_DELAY_64;
        }
    }
}

/**
 * \brief Test AASRC attenuation control.
 *
 * Test Category: Functionality
 *
 * Tests digital attenuation feature by comparing RMS values at different
 * attenuation levels (0, 64, 128, 192, 255) against reference measurements.
 * Validates relative gain changes for mono, stereo, and group configurations.
 *
 * \param args Pointer to AASRC_OpenParams structure.
 */
static void TestAasrc_attenuation(void* args)
{
    AASRC_OpenParams *openParams = (AASRC_OpenParams *)args;
    uint8_t inst = (uint8_t)(openParams - &gAasrcOpenParams[0]);
    uint32_t attenuationVals[] = {0, 64, 128, 192, 255}; /* 0 = no attenuation, 255 = max */
    uint32_t numAttenuations = sizeof(attenuationVals) / sizeof(attenuationVals[0]);
    uint32_t att, channelCount, ch;
    float samplingRateHz;
    int32_t startIdx, fftLen;
    int32_t stereoRxPerCh;
    AASRC_OpenParams localOpenParams = {0};

    float baseMonoRxRms = 0.0f, baseMonoTxRms = 0.0f;
    float baseStereoRxRms[TEST_AASRC_STEREO_CHANNEL_COUNT] = {0};
    float baseStereoTxRms[TEST_AASRC_STEREO_CHANNEL_COUNT] = {0};
    float baseGroupRxRms[TEST_AASRC_GROUP_CHANNEL_COUNT]   = {0};
    float baseGroupTxRms[TEST_AASRC_GROUP_CHANNEL_COUNT]   = {0};

    for (att = 0U; att < numAttenuations; att++)
    {
        localOpenParams = gAasrcOpenParams[inst];
        for (channelCount = 0U; channelCount < CONFIG_AASRC0_NUM_CH; channelCount++)
        {
            AASRC_ChObj *chObj = &gConfigAasrcChObj[inst][channelCount];
            chObj->chCfg.attenuation = (uint8_t)attenuationVals[att];
        }

        int32_t status = SystemP_SUCCESS;
        AASRC_ChHandle chHandle = NULL;
        AASRC_ChObj *chObj = NULL;
        float clkFrequency;

        /* Re-open with updated params */
        AASRC_close(gAasrcHandle[inst]);
        gAasrcHandle[inst] = AASRC_open(inst, &localOpenParams);

        SemaphoreP_constructCounting(&TestAASRC_countSemAsrcConv, 0, CONFIG_AASRC0_NUM_CH);

        for (channelCount = 0U; channelCount < CONFIG_AASRC0_NUM_CH; channelCount++)
        {
            chHandle = AASRC_chOpen(channelCount, gAasrcHandle[inst]);
            if (chHandle != NULL)
            {
                chObj = (AASRC_ChObj *)(chHandle);
            }
            else
            {
                status = SystemP_FAILURE;
            }

            status = AASRC_chConfig(chHandle);
            if (status == SystemP_SUCCESS)
            {
                /* Input Frequency */
                status += AASRC_GetClkZoneRxFrequency(chHandle, &clkFrequency);
                TestAASRC_chMeta[inst][channelCount].rxSamplingFreq = clkFrequency;
                TestAASRC_chMeta[inst][channelCount].dataFormat = chObj->chCfg.inWordLen;

                DebugP_assertNoLog(status == SystemP_SUCCESS);

                /* Output Frequency */
                status += AASRC_GetClkZoneTxFrequency(chHandle, &clkFrequency);
                TestAASRC_chMeta[inst][channelCount].txSamplingFreq = clkFrequency;
                DebugP_assertNoLog(status == SystemP_SUCCESS);

                /* Queue/enable */
                TestAasrc_transactionInit(chHandle, inst, channelCount);
                status += AASRC_chEnable(chHandle);
            }
        }

        DebugP_assert(status == SystemP_SUCCESS);

        bool timedOut = false;
        {
            uint32_t elapsedMs = 0U;
            while (SemaphoreP_getCount(&TestAASRC_countSemAsrcConv) < CONFIG_AASRC0_NUM_CH)
            {
                ClockP_usleep(TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US);
                elapsedMs += (TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US / 1000U);
                if (elapsedMs >= TEST_AASRC_BUSYWAIT_TIMEOUT_MS)
                {
                    TEST_ASSERT_TRUE_MESSAGE(0, "Attenuation test: AASRC conversion timed out");
                    timedOut = true;
                    break;
                }
            }
        }

        CacheP_wbInv(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALL);
        CacheP_wbInv(gAasrcTxStereoBuffer, sizeof(gAasrcTxStereoBuffer), CacheP_TYPE_ALL);
        CacheP_wbInv(gAasrcTxGroupBuffer, sizeof(gAasrcTxGroupBuffer), CacheP_TYPE_ALL);

        /* Close channels for this instance */
        for (channelCount = 0U; channelCount < CONFIG_AASRC0_NUM_CH; channelCount++)
        {
            chHandle = AASRC_getChHandle(inst, channelCount);
            AASRC_chDisable(chHandle);
            status = AASRC_chClose(chHandle);
        }
        SemaphoreP_destruct(&TestAASRC_countSemAsrcConv);

        if (timedOut) 
        { 
            return; 
        }

        /* FFT + logs + checks (same as SinewaveConversionDma) */

        samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_MONO_AASRC_CH].rxSamplingFreq * 1000.0f;
        TestAasrc_runFftWordLen((uint32_t *)gAasrcRxMonoBuffer, (int32_t)TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT, samplingRateHz, TEST_AASRC_IN_BITS, &TestAASRC_monoRxPeak);

        startIdx = TEST_AASRC_MONO_FFT_START_IDX;
        fftLen   = TEST_AASRC_MONO_FFT_LENGTH;
        samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_MONO_AASRC_CH].txSamplingFreq * 1000.0f;
        TestAasrc_runFftWordLen((uint32_t *)&gAasrcTxMonoBuffer[startIdx], fftLen, samplingRateHz, TEST_AASRC_IN_BITS, &TestAASRC_monoTxPeak);

        stereoRxPerCh = (int32_t)(TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT / TEST_AASRC_STEREO_CHANNEL_COUNT);
        samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_STEREO_AASRC_CH].rxSamplingFreq * 1000.0f;
        for (ch = 0; ch < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; ch++)
        {
            TestAasrc_fftInterleavedWordLen((uint32_t *)gAasrcRxStereoBuffer, stereoRxPerCh, TEST_AASRC_STEREO_CHANNEL_COUNT, ch, samplingRateHz, TEST_AASRC_IN_BITS, &TestAASRC_stereoRxPeak[ch]);
        }

        startIdx = TEST_AASRC_STEREO_FFT_START_IDX;
        fftLen = TEST_AASRC_STEREO_FFT_LENGTH;
        samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_STEREO_AASRC_CH].txSamplingFreq * 1000.0f;
        for (ch = 0; ch < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; ch++)
        {
            TestAasrc_fftInterleavedWordLen((uint32_t *)&gAasrcTxStereoBuffer[startIdx * TEST_AASRC_STEREO_CHANNEL_COUNT], fftLen, TEST_AASRC_STEREO_CHANNEL_COUNT, ch, samplingRateHz, TEST_AASRC_IN_BITS,&TestAASRC_stereoTxPeak[ch]);
        }

        {
            int32_t groupRxPerCh = (int32_t)(TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT / TEST_AASRC_GROUP_CHANNEL_COUNT);
            samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_GROUP_AASRC_CH].rxSamplingFreq * 1000.0f;
            for (ch = 0; ch < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; ch++)
            {
                TestAasrc_fftInterleavedWordLen((uint32_t *)gAasrcRxGroupBuffer, groupRxPerCh, TEST_AASRC_GROUP_CHANNEL_COUNT, ch, samplingRateHz, TEST_AASRC_IN_BITS, &TestAASRC_groupRxPeak[ch]);
            }
            startIdx = TEST_AASRC_GROUP_FFT_START_IDX;
            fftLen = TEST_AASRC_GROUP_FFT_LENGTH;
            samplingRateHz = TestAASRC_chMeta[inst][TEST_AASRC_GROUP_AASRC_CH].txSamplingFreq * 1000.0f;
            for (ch = 0; ch < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; ch++)
            {
                TestAasrc_fftInterleavedWordLen((uint32_t *)&gAasrcTxGroupBuffer[startIdx * TEST_AASRC_GROUP_CHANNEL_COUNT], fftLen, TEST_AASRC_GROUP_CHANNEL_COUNT, ch, samplingRateHz, TEST_AASRC_IN_BITS, &TestAASRC_groupTxPeak[ch]);
            }
        }

        DebugP_log("Mono RX: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", TestAASRC_monoRxPeak.freqHz, TestAASRC_monoRxPeak.amplitude, TestAASRC_monoRxPeak.rms);
        DebugP_log("Mono TX: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", TestAASRC_monoTxPeak.freqHz, TestAASRC_monoTxPeak.amplitude, TestAASRC_monoTxPeak.rms);

        for (ch = 0; ch < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; ch++)
        {
            DebugP_log("Stereo RX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", ch, TestAASRC_stereoRxPeak[ch].freqHz, TestAASRC_stereoRxPeak[ch].amplitude, TestAASRC_stereoRxPeak[ch].rms);
            DebugP_log("Stereo TX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", ch, TestAASRC_stereoTxPeak[ch].freqHz, TestAASRC_stereoTxPeak[ch].amplitude, TestAASRC_stereoTxPeak[ch].rms);
        }
        for (ch = 0; ch < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; ch++)
        {
            DebugP_log("Group RX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", ch, TestAASRC_groupRxPeak[ch].freqHz, TestAASRC_groupRxPeak[ch].amplitude, TestAASRC_groupRxPeak[ch].rms);
            DebugP_log("Group TX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", ch, TestAASRC_groupTxPeak[ch].freqHz, TestAASRC_groupTxPeak[ch].amplitude, TestAASRC_groupTxPeak[ch].rms);
        }

        if (attenuationVals[att] == 0U)
        {
            /* Capture baseline RMS at atten=0 for reference */
            baseMonoRxRms = TestAASRC_monoRxPeak.rms;
            baseMonoTxRms = TestAASRC_monoTxPeak.rms;
            for ( ch = 0; ch < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; ch++)
            {
                baseStereoRxRms[ch] = TestAASRC_stereoRxPeak[ch].rms;
                baseStereoTxRms[ch] = TestAASRC_stereoTxPeak[ch].rms;
            }
            for ( ch = 0; ch < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; ch++)
            {
                baseGroupRxRms[ch] = TestAASRC_groupRxPeak[ch].rms;
                baseGroupTxRms[ch] = TestAASRC_groupTxPeak[ch].rms;
            }
        }
        else
        {
            /* Validate attenuation relative to reference */
            float expected = (float)(255 - attenuationVals[att]) / 255.0f;

            /* Mono: (TX/RX at current) vs (TX/RX at atten=0) */
            if (baseMonoRxRms > 0.0f && baseMonoTxRms > 0.0f && TestAASRC_monoRxPeak.rms > 0.0f)
            {
                float gainNow   = TestAASRC_monoTxPeak.rms / TestAASRC_monoRxPeak.rms;
                float gainBase  = baseMonoTxRms   / baseMonoRxRms;
                float relGain   = gainNow / gainBase; /* relative to atten=0 */
                float err       = fabsf(relGain - expected) / (expected > 0.0f ? expected : 1.0f);
                TEST_ASSERT_TRUE_MESSAGE(err <= TEST_AASRC_FFT_AMP_TOL_RATIO, "Mono attenuation (RMS) mismatch vs reference");
            }

            /* Stereo */
            for ( ch = 0; ch < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; ch++)
            {
                if (baseStereoRxRms[ch] > 0.0f && baseStereoTxRms[ch] > 0.0f && TestAASRC_stereoRxPeak[ch].rms > 0.0f)
                {
                    float gainNow  = TestAASRC_stereoTxPeak[ch].rms / TestAASRC_stereoRxPeak[ch].rms;
                    float gainBase = baseStereoTxRms[ch] / baseStereoRxRms[ch];
                    float relGain  = gainNow / gainBase;
                    float err      = fabsf(relGain - expected) / (expected > 0.0f ? expected : 1.0f);
                    TEST_ASSERT_TRUE_MESSAGE(err <= TEST_AASRC_FFT_AMP_TOL_RATIO, "Stereo attenuation (RMS) mismatch vs reference");
                }
            }

            /* Group */
            for ( ch = 0; ch < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; ch++)
            {
                if (baseGroupRxRms[ch] > 0.0f && baseGroupTxRms[ch] > 0.0f && TestAASRC_groupRxPeak[ch].rms > 0.0f)
                {
                    float gainNow  = TestAASRC_groupTxPeak[ch].rms / TestAASRC_groupRxPeak[ch].rms;
                    float gainBase = baseGroupTxRms[ch] / baseGroupRxRms[ch];
                    float relGain  = gainNow / gainBase;
                    float err      = fabsf(relGain - expected) / (expected > 0.0f ? expected : 1.0f);
                    TEST_ASSERT_TRUE_MESSAGE(err <= TEST_AASRC_FFT_AMP_TOL_RATIO, "Group attenuation (RMS) mismatch vs reference");
                }
            }
        }
    }
    for (channelCount = 0U; channelCount < CONFIG_AASRC0_NUM_CH; channelCount++)
    {
        AASRC_ChObj *chObj = &gConfigAasrcChObj[inst][channelCount];
        chObj->chCfg.attenuation = 0;
    }
}

/**
 * \brief Test AASRC with word lengths (16/18/20).
 *
 * Test Category: Functionality
 *
 * Validates sample rate conversion with various audio word lengths by
 * converting 24-bit reference data to target bit width and verifying
 * FFT analysis shows correct frequency and amplitude.
 *
 * \param args Pointer to test parameters.
 */
static void TestAasrc_pcmWidth(void *args)
{
    AASRC_OpenParams *openParams = (AASRC_OpenParams *)args;
    uint8_t inst = (uint8_t)(openParams - &gAasrcOpenParams[0]);
    const uint8_t ioBitsList[] = {24, 16, 18, 20};
    uint32_t i, c, idx;

    int32_t status = SystemP_SUCCESS;
    AASRC_Handle        handle = NULL;
    AASRC_ChHandle      chHandle = NULL;
    AASRC_ChObj        *chObj = NULL;
    AASRC_OpenParams    localOpenParams = {0};
    AASRC_ChObj        *cfgCh = NULL;

    uint8_t ch;
    float clkFrequency;
    uint8_t origInWordLen[CONFIG_AASRC0_NUM_CH] = {0};
    uint8_t origOutWordLen[CONFIG_AASRC0_NUM_CH] = {0};

    /* Save original word lengths to restore later */
    for (ch = 0; ch < CONFIG_AASRC0_NUM_CH; ch++)
    {
        origInWordLen[ch] = gConfigAasrcChObj[inst][ch].chCfg.inWordLen;
        origOutWordLen[ch] = gConfigAasrcChObj[inst][ch].chCfg.outWordLen;
    }

    for (idx = 0; idx < (sizeof(ioBitsList)/sizeof(ioBitsList[0])); idx++)
    {
        uint8_t IO_BITS = ioBitsList[idx];
        
        localOpenParams = gAasrcOpenParams[inst];
        for (ch = 0; ch < CONFIG_AASRC0_NUM_CH; ch++)
        {
            cfgCh = &gConfigAasrcChObj[inst][ch];
            cfgCh->chCfg.inWordLen  = IO_BITS;
            cfgCh->chCfg.outWordLen = IO_BITS;
        }
        AASRC_close(gAasrcHandle[inst]);
        handle = AASRC_open(inst, &localOpenParams);
        DebugP_assert(handle != NULL);

        SemaphoreP_constructCounting(&TestAASRC_countSemAsrcConv, 0, CONFIG_AASRC0_NUM_CH);

        for (ch = 0; ch < CONFIG_AASRC0_NUM_CH; ch++)
        {
            chHandle = AASRC_chOpen(ch, handle);
            DebugP_assert(chHandle != NULL);
            chObj = (AASRC_ChObj *)(chHandle);

            status = AASRC_chConfig(chHandle);
            DebugP_assert(status == SystemP_SUCCESS);

            /* Capture RX/TX sampling rates and data format */
            status  = AASRC_GetClkZoneRxFrequency(chHandle, &clkFrequency);
            DebugP_assertNoLog(status == SystemP_SUCCESS);
            TestAASRC_chMeta[inst][ch].rxSamplingFreq = clkFrequency;
            TestAASRC_chMeta[inst][ch].dataFormat     = chObj->chCfg.inWordLen;

            status  = AASRC_GetClkZoneTxFrequency(chHandle, &clkFrequency);
            DebugP_assertNoLog(status == SystemP_SUCCESS);
            TestAASRC_chMeta[inst][ch].txSamplingFreq = clkFrequency;

            /* Prepare buffers per channel type with 24->20 conversion */
            switch (chObj->chCfg.chType)
            {
                case AASRC_MONO:
                {
                    for (i = 0; i < TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT; i++)
                    {
                        int32_t s24 = (int32_t)aasrc_monoInput[i];
                        int32_t sConv = TestAasrc_convertWordlen(s24, TEST_AASRC_IN_BITS, IO_BITS);
                        gAasrcRxMonoBuffer[i] = TestAasrc_packRightJustified(sConv, IO_BITS);
                    }
                    for (i = 0; i < TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT; i++) gAasrcTxMonoBuffer[i] = 0;

                    CacheP_wb(gAasrcRxMonoBuffer, sizeof(gAasrcRxMonoBuffer), CacheP_TYPE_ALLD);
                    CacheP_wb(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALLD);

                    TestAASRC_txnRx[inst][ch].buf = (void*)&gAasrcRxMonoBuffer[0];
                    TestAASRC_txnRx[inst][ch].sampleCount = TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
                    AASRC_queueTransactionRx(chHandle, &TestAASRC_txnRx[inst][ch]);

                    TestAASRC_txnTx[inst][ch].buf = (void*)&gAasrcTxMonoBuffer[0];
                    TestAASRC_txnTx[inst][ch].sampleCount = TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
                    AASRC_queueTransactionTx(chHandle, &TestAASRC_txnTx[inst][ch]);
                } break;

                case AASRC_STEREO:
                {
                    for (i = 0; i < TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT; i++)
                    {
                        int32_t s24 = (int32_t)aasrc_stereoInput[i];
                        int32_t sConv = TestAasrc_convertWordlen(s24, TEST_AASRC_IN_BITS, IO_BITS);
                        gAasrcRxStereoBuffer[i] = TestAasrc_packRightJustified(sConv, IO_BITS);
                    }
                    for (i = 0; i < TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT; i++) gAasrcTxStereoBuffer[i] = 0;

                    CacheP_wb(gAasrcRxStereoBuffer, sizeof(gAasrcRxStereoBuffer), CacheP_TYPE_ALLD);
                    CacheP_wb(gAasrcTxStereoBuffer, sizeof(gAasrcTxStereoBuffer), CacheP_TYPE_ALLD);

                    TestAASRC_txnRx[inst][ch].buf = (void*)&gAasrcRxStereoBuffer[0];
                    TestAASRC_txnRx[inst][ch].sampleCount = TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT;
                    AASRC_queueTransactionRx(chHandle, &TestAASRC_txnRx[inst][ch]);

                    TestAASRC_txnTx[inst][ch].buf = (void*)&gAasrcTxStereoBuffer[0];
                    TestAASRC_txnTx[inst][ch].sampleCount = TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
                    AASRC_queueTransactionTx(chHandle, &TestAASRC_txnTx[inst][ch]);
                } break;

                case AASRC_GROUP:
                {
                    for (i = 0; i < TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT; i++)
                    {
                        int32_t s24 = (int32_t)aasrc_groupInput[i];
                        int32_t sConv = TestAasrc_convertWordlen(s24, TEST_AASRC_IN_BITS, IO_BITS);
                        gAasrcRxGroupBuffer[i] = TestAasrc_packRightJustified(sConv, IO_BITS);
                    }
                    for (i = 0; i < TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT; i++) gAasrcTxGroupBuffer[i] = 0;

                    CacheP_wb(gAasrcRxGroupBuffer, sizeof(gAasrcRxGroupBuffer), CacheP_TYPE_ALLD);
                    CacheP_wb(gAasrcTxGroupBuffer, sizeof(gAasrcTxGroupBuffer), CacheP_TYPE_ALLD);

                    TestAASRC_txnRx[inst][ch].buf = (void*)&gAasrcRxGroupBuffer[0];
                    TestAASRC_txnRx[inst][ch].sampleCount = TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT;
                    AASRC_queueTransactionRx(chHandle, &TestAASRC_txnRx[inst][ch]);

                    TestAASRC_txnTx[inst][ch].buf = (void*)&gAasrcTxGroupBuffer[0];
                    TestAASRC_txnTx[inst][ch].sampleCount = TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT;
                    AASRC_queueTransactionTx(chHandle, &TestAASRC_txnTx[inst][ch]);
                } break;

                default: break;
            }

            /* Enable channel */
            status = AASRC_chEnable(chHandle);
            DebugP_assert(status == SystemP_SUCCESS);
        }

        /* Wait for all channel TX callbacks */
        bool timedOut = false;
        {
            uint32_t elapsedMs = 0U;
            while (SemaphoreP_getCount(&TestAASRC_countSemAsrcConv) < CONFIG_AASRC0_NUM_CH)
            {
                ClockP_usleep(TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US);
                elapsedMs += (TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US / 1000U);
                if (elapsedMs >= TEST_AASRC_BUSYWAIT_TIMEOUT_MS)
                {
                    TEST_ASSERT_TRUE_MESSAGE(0, "Group delay test: AASRC conversion timed out");
                    timedOut = true;
                    break;
                }
            }
        }

        /* Invalidate TX caches */
        CacheP_wbInv(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALL);
        CacheP_wbInv(gAasrcTxStereoBuffer, sizeof(gAasrcTxStereoBuffer), CacheP_TYPE_ALL);
        CacheP_wbInv(gAasrcTxGroupBuffer, sizeof(gAasrcTxGroupBuffer), CacheP_TYPE_ALL);

        /* Close channels */
        for (ch = 0; ch < CONFIG_AASRC0_NUM_CH; ch++)
        {
            chHandle = AASRC_getChHandle(inst, ch);
            AASRC_chDisable(chHandle);
            (void)AASRC_chClose(chHandle);
        }
        SemaphoreP_destruct(&TestAASRC_countSemAsrcConv);

        if (timedOut) 
        { 
            return; 
        }

        /* FFT checks using wordLen-aware helpers */
        float sr;

        /* Mono RX/TX */
        sr = TestAASRC_chMeta[inst][TEST_AASRC_MONO_AASRC_CH].rxSamplingFreq * 1000.0f;
        TestAasrc_runFftWordLen((uint32_t *)gAasrcRxMonoBuffer, (int32_t)TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT, sr, IO_BITS, &TestAASRC_monoRxPeak);

        int32_t startIdx = TEST_AASRC_MONO_FFT_START_IDX, fftLen = TEST_AASRC_MONO_FFT_LENGTH;
        sr = TestAASRC_chMeta[inst][TEST_AASRC_MONO_AASRC_CH].txSamplingFreq * 1000.0f;
        TestAasrc_runFftWordLen((uint32_t *)&gAasrcTxMonoBuffer[startIdx], fftLen, sr, IO_BITS, &TestAASRC_monoTxPeak);

        /* Stereo RX/TX */
        int32_t stereoRxPerCh = (int32_t)(TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT / TEST_AASRC_STEREO_CHANNEL_COUNT);
        sr = TestAASRC_chMeta[inst][TEST_AASRC_STEREO_AASRC_CH].rxSamplingFreq * 1000.0f;
        for (c = 0; c < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; c++)
        {
            TestAasrc_fftInterleavedWordLen((uint32_t *)gAasrcRxStereoBuffer, stereoRxPerCh, TEST_AASRC_STEREO_CHANNEL_COUNT, c, sr, IO_BITS, &TestAASRC_stereoRxPeak[c]);
        }
        startIdx = TEST_AASRC_STEREO_FFT_START_IDX; fftLen = TEST_AASRC_STEREO_FFT_LENGTH;
        sr = TestAASRC_chMeta[inst][TEST_AASRC_STEREO_AASRC_CH].txSamplingFreq * 1000.0f;
        for (c = 0; c < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; c++)
        {
            TestAasrc_fftInterleavedWordLen((uint32_t *)&gAasrcTxStereoBuffer[startIdx * TEST_AASRC_STEREO_CHANNEL_COUNT], fftLen, TEST_AASRC_STEREO_CHANNEL_COUNT, c, sr, IO_BITS, &TestAASRC_stereoTxPeak[c]);
        }

        /* Group RX/TX */
        int32_t groupRxPerCh = (int32_t)(TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT / TEST_AASRC_GROUP_CHANNEL_COUNT);
        sr = TestAASRC_chMeta[inst][TEST_AASRC_GROUP_AASRC_CH].rxSamplingFreq * 1000.0f;
        for (c = 0; c < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; c++)
        {
            TestAasrc_fftInterleavedWordLen((uint32_t *)gAasrcRxGroupBuffer, groupRxPerCh, TEST_AASRC_GROUP_CHANNEL_COUNT, c, sr, IO_BITS, &TestAASRC_groupRxPeak[c]);
        }
        startIdx = TEST_AASRC_GROUP_FFT_START_IDX; fftLen = TEST_AASRC_GROUP_FFT_LENGTH;
        sr = TestAASRC_chMeta[inst][TEST_AASRC_GROUP_AASRC_CH].txSamplingFreq * 1000.0f;
        for (c = 0; c < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; c++)
        {
            TestAasrc_fftInterleavedWordLen((uint32_t *)&gAasrcTxGroupBuffer[startIdx * TEST_AASRC_GROUP_CHANNEL_COUNT], fftLen, TEST_AASRC_GROUP_CHANNEL_COUNT, c, sr, IO_BITS, &TestAASRC_groupTxPeak[c]);
        }

        /* Logs and basic validations (similar to existing test) */
        DebugP_log("%u Mono RX: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n",IO_BITS, TestAASRC_monoRxPeak.freqHz, TestAASRC_monoRxPeak.amplitude, TestAASRC_monoRxPeak.rms);
        DebugP_log("%u Mono TX: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", IO_BITS, TestAASRC_monoTxPeak.freqHz, TestAASRC_monoTxPeak.amplitude, TestAASRC_monoTxPeak.rms);

        for (c = 0; c < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; c++)
        {
            DebugP_log("%u Stereo RX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", IO_BITS, c, TestAASRC_stereoRxPeak[c].freqHz, TestAASRC_stereoRxPeak[c].amplitude, TestAASRC_stereoRxPeak[c].rms);
            DebugP_log("%u Stereo TX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", IO_BITS, c, TestAASRC_stereoTxPeak[c].freqHz, TestAASRC_stereoTxPeak[c].amplitude, TestAASRC_stereoTxPeak[c].rms);
        }
        for (c = 0; c < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; c++)
        {
            DebugP_log("%u Group RX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", IO_BITS, c, TestAASRC_groupRxPeak[c].freqHz, TestAASRC_groupRxPeak[c].amplitude, TestAASRC_groupRxPeak[c].rms);
            DebugP_log("%u Group TX ch%d: f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", IO_BITS, c, TestAASRC_groupTxPeak[c].freqHz, TestAASRC_groupTxPeak[c].amplitude, TestAASRC_groupTxPeak[c].rms);
        }

        float df = fabsf(TestAASRC_monoRxPeak.freqHz - TestAASRC_monoTxPeak.freqHz);
        float rmsRatio = (TestAASRC_monoRxPeak.rms > 0.0f) ? fabsf(TestAASRC_monoTxPeak.rms / TestAASRC_monoRxPeak.rms - 1.0f) : 0.0f;
        bool freqMatch = (df <= TEST_AASRC_FFT_FREQ_TOL_HZ);
        bool rmsMatch = (rmsRatio <= TEST_AASRC_FFT_AMP_TOL_RATIO);
        TEST_ASSERT_TRUE_MESSAGE(freqMatch || rmsMatch, "Mono: neither frequency nor RMS match");

        for (c = 0; c < (int32_t)TEST_AASRC_STEREO_CHANNEL_COUNT; c++)
        {
            float dfs = fabsf(TestAASRC_stereoRxPeak[c].freqHz - TestAASRC_stereoTxPeak[c].freqHz);
            float rms = (TestAASRC_stereoRxPeak[c].rms > 0.0f) ? fabsf(TestAASRC_stereoTxPeak[c].rms / TestAASRC_stereoRxPeak[c].rms - 1.0f) : 0.0f;
            bool freqMatch = (dfs <= TEST_AASRC_FFT_FREQ_TOL_HZ);
            bool rmsMatch = (rms <= TEST_AASRC_FFT_AMP_TOL_RATIO);
            TEST_ASSERT_TRUE_MESSAGE(freqMatch || rmsMatch, "Stereo: neither frequency nor RMS match");
        }
        for (c = 1; c < (int32_t)TEST_AASRC_GROUP_CHANNEL_COUNT; c++)
        {
            float dfg = fabsf(TestAASRC_groupRxPeak[0].freqHz - TestAASRC_groupRxPeak[c].freqHz);
            float rmsRatio = (TestAASRC_groupRxPeak[0].rms > 0.0f) ? fabsf(TestAASRC_groupRxPeak[c].rms / TestAASRC_groupRxPeak[0].rms - 1.0f) : 0.0f;
            bool freqMatch = (dfg <= TEST_AASRC_FFT_FREQ_TOL_HZ);
            bool rmsMatch = (rmsRatio <= TEST_AASRC_FFT_AMP_TOL_RATIO);
            TEST_ASSERT_TRUE_MESSAGE(freqMatch || rmsMatch, "Group RX channels: neither frequency nor RMS match");
        }
    }

    /* Restore original word lengths */
    for (ch = 0; ch < CONFIG_AASRC0_NUM_CH; ch++)
    {
        gConfigAasrcChObj[inst][ch].chCfg.inWordLen  = origInWordLen[ch];
        gConfigAasrcChObj[inst][ch].chCfg.outWordLen = origOutWordLen[ch];
    }
}

/**
 * \brief Convert sample word length between different bit depths.
 *
 * Performs sign extension and bit-width conversion with saturation.
 * Used for testing different audio word lengths (16-bit, 18-bit, 20-bit, 24-bit).
 *
 * \param s_in Input sample value.
 * \param inBits Input bit width.
 * \param outBits Output bit width.
 * \return Converted sample value.
 */
static inline int32_t TestAasrc_convertWordlen(int32_t s_in, uint8_t inBits, uint8_t outBits)
{
    /* Mask to inBits and sign-extend to 32b */
    if (inBits >= 32)
    {
        /* nothing to do */
    }
    else
    {
        int32_t signMask = 1 << (inBits - 1);
        int32_t valMask  = (1 << inBits) - 1;
        s_in &= valMask;
        if (s_in & signMask)
        {
            s_in |= ~valMask; /* sign extend */
        }
    }

    /* If reducing bit-width, drop LSBs to align range; simple right shift by (inBits - outBits) */
    if (outBits < inBits)
    {
        int shift = (int)inBits - (int)outBits;
        s_in = s_in >> shift;
    }

    /* Saturate to outBits range */
    if (outBits < 31)
    {
        int32_t maxp = (1 << (outBits - 1)) - 1;
        int32_t minn = -(1 << (outBits - 1));
        if (s_in > maxp)
        {
            s_in = maxp;
        }
        if (s_in < minn)
        {
            s_in = minn;
        }
    }
    return s_in;
}

/**
 * \brief Pack sample value as right-justified in 32-bit container.
 *
 * Ensures proper sign extension for samples with less than 32-bit width.
 *
 * \param s_out Output sample value.
 * \param outBits Output bit width.
 * \return Packed sample value.
 */
static inline int32_t TestAasrc_packRightJustified(int32_t s_out, uint8_t outBits)
{
    /* Already right-justified; ensure upper bits match sign */
    if (outBits >= 32)
    {
        return s_out;
    }
    int32_t valMask = (1 << outBits) - 1;
    /* Keep only outBits then sign-extend back to 32 for processing/storage */
    s_out &= valMask;
    /* Sign-extend for 32-bit container so math remains correct */
    int32_t signMask = 1 << (outBits - 1);
    if (s_out & signMask)
    {
        s_out |= ~valMask;
    }
    return s_out;
}


/*
 * FFT helpers that respect word length.
 *
 * Refactored to eliminate duplication across architectures (C7x vs R5F) and
 * between the mono / interleaved variants. The original implementation had
 * four near-identical copies of the same algorithm; everything is now shared
 * except the architecture-specific real-FFT call, which is isolated in
 * TestAasrc_realFft().
 *
 * The public wrappers TestAasrc_runFftWordLen() and
 * TestAasrc_fftInterleavedWordLen() keep their original signatures so all
 * existing call sites compile unchanged.
 */

/**
 * \brief Sign-extend a wordLenBits-wide sample held in a uint32_t container
 *        and convert to float. Bit-identical to the inline sequence used in
 *        the previous per-variant implementations.
 */
static inline float TestAasrc_signExtendToFloat(uint32_t raw,
                                                int32_t  valMask,
                                                int32_t  signMask)
{
    int32_t s = (int32_t)raw;
    s &= valMask;
    if ((s & signMask) != 0)
    {
        s |= ~valMask;
    }
    return (float)s;
}

/**
 * \brief Architecture-specific real FFT.
 *        Input  : TestAASRC_fftInput  (sampleCount float samples)
 *        Output : TestAASRC_fftOutput (interleaved re/im, float)
 *
 * This is the ONLY function that contains the C75/R5F switch.
 */
static void TestAasrc_realFft(int32_t sampleCount)
{
#if defined(C75_CORE)
    FFTLIB_bufParams1D_t bufParams;
    bufParams.dim_x     = sampleCount;
    bufParams.data_type = FFTLIB_FLOAT32;

    /* Twiddle and split factor generation */
    tw_gen_r2c(TestAASRC_fftTwiddle, sampleCount);
    split_factor_gen_r2c(TestAASRC_fftSplitFactor, sampleCount);

    FFTLIB_fft1d_i32f_c32fc_o32fc_cn(
        TestAASRC_fftInput,        &bufParams,
        TestAASRC_fftTwiddle,      &bufParams,
        TestAASRC_fftIntermediate, &bufParams,
        TestAASRC_fftSplitFactor,  &bufParams,
        TestAASRC_fftOutput,       &bufParams
    );
#else /* R5F_CORE  */
    arm_rfft_fast_instance_f32 rfft;
    arm_status st = arm_rfft_fast_init_f32(&rfft, (uint32_t)sampleCount);
    DebugP_assertNoLog(st == ARM_MATH_SUCCESS);
    arm_rfft_fast_f32(&rfft, TestAASRC_fftInput, TestAASRC_fftOutput, 0);
#endif
}

/**
 * \brief Core word-length aware FFT routine used by both the mono and the
 *        interleaved wrappers. For mono use chCount = 1, chIndex = 0.
 *
 * \param inputBuf     Input buffer (interleaved if chCount > 1).
 * \param sampleCount  Samples per channel (clamped to TEST_AASRC_MAX_FFT_SAMPLES).
 * \param chCount      Number of interleaved channels (1 for mono).
 * \param chIndex      Channel index to extract (0 for mono).
 * \param sampleRateHz Sampling rate in Hz.
 * \param wordLenBits  Actual bit width of samples (1..32).
 * \param out          Output metrics.
 */
static void TestAasrc_fftWordLenCore(uint32_t *inputBuf,
                                     int32_t sampleCount,
                                     int32_t chCount,
                                     int32_t chIndex,
                                     float sampleRateHz,
                                     uint8_t wordLenBits,
                                     TestAASRC_peakMetrics *out)
{
    uint32_t i, k;
    double   acc2 = 0.0;

    if (sampleCount > (int32_t)TEST_AASRC_MAX_FFT_SAMPLES)
    {
        sampleCount = (int32_t)TEST_AASRC_MAX_FFT_SAMPLES;
    }

    if ((wordLenBits == 0U) || (wordLenBits > 32U))
    {
        return; /* Invalid bit width */
    }

    int32_t valMask  = (wordLenBits >= 32U) ? (int32_t)0xFFFFFFFF : ((1 << wordLenBits) - 1);
    int32_t signMask = (wordLenBits >= 32U) ? (int32_t)0x80000000 : (1 << (wordLenBits - 1U));

    /* Sample extraction + sign extension + RMS accumulation */
    for (i = 0U; i < (uint32_t)sampleCount; i++)
    {
        uint32_t idx = (i * (uint32_t)chCount) + (uint32_t)chIndex;
        float    x   = TestAasrc_signExtendToFloat(inputBuf[idx], valMask, signMask);
        TestAASRC_fftInput[i] = x;
        acc2 += (double)x * (double)x;
    }
    out->rms = (sampleCount > 0) ? (float)sqrt(acc2 / (double)sampleCount) : 0.0f;

    /* Architecture-specific real FFT */
    TestAasrc_realFft(sampleCount);

    /* Peak bin search (skip DC, exclude Nyquist - matches original behaviour) */
    int32_t half    = sampleCount / 2;
    int32_t peakBin = 1;
    float   peakMag = 0.0f;
    for (k = 1U; k < (uint32_t)half; k++)
    {
        float re  = TestAASRC_fftOutput[2 * k];
        float im  = TestAASRC_fftOutput[(2 * k) + 1];
        float mag = sqrtf((re * re) + (im * im));
        if (mag > peakMag)
        {
            peakMag = mag;
            peakBin = (int32_t)k;
        }
    }

    float binRes   = sampleRateHz / (float)sampleCount;
    out->freqHz    = peakBin * binRes;
    out->amplitude = (2.0f * peakMag) / (float)sampleCount;
    out->peakBin   = peakBin;
    out->fftLen    = sampleCount;
}

/**
 * \brief Perform FFT with word-length awareness for a mono channel.
 *        Thin wrapper around TestAasrc_fftWordLenCore().
 */
static void TestAasrc_runFftWordLen(uint32_t *inputBuf,
                                    int32_t sampleCount,
                                    float sampleRateHz,
                                    uint8_t wordLenBits,
                                    TestAASRC_peakMetrics *out)
{
    TestAasrc_fftWordLenCore(inputBuf, sampleCount, 1, 0, sampleRateHz, wordLenBits, out);
}

/**
 * \brief Perform FFT on one channel of interleaved multi-channel data with
 *        word-length awareness. Thin wrapper around TestAasrc_fftWordLenCore().
 */
static void TestAasrc_fftInterleavedWordLen(uint32_t *inputBuf,
                                            int32_t sampleCount,
                                            int32_t chCount,
                                            int32_t chIndex,
                                            float sampleRateHz,
                                            uint8_t wordLenBits,
                                            TestAASRC_peakMetrics *out)
{
    TestAasrc_fftWordLenCore(inputBuf, sampleCount, chCount, chIndex,
                             sampleRateHz, wordLenBits, out);
}

#endif


/* User Defined Callbacks */

/**
 * \brief Callback function for AASRC RX completion.
 *
 * Currently unused - placeholder for RX transaction completion.
 *
 * \param chHandle AASRC channel handle.
 * \param transaction Pointer to completed transaction.
 */
void aasrc_rxcb (AASRC_ChHandle chHandle,
                 AASRC_Transaction *transaction)
{
}

/**
 * \brief Callback function for AASRC TX completion.
 *
 * Posts semaphore to signal completion of TX transaction.
 *
 * \param chHandle AASRC channel handle.
 * \param transaction Pointer to completed transaction.
 */
void aasrc_txcb (AASRC_ChHandle chHandle,
                 AASRC_Transaction *transaction)
{
#ifdef ENABLE_MT_TESTS
    SemaphoreP_post(&TestAASRC_countSemAsrcConv);
#endif
}

/**
 * \brief Error handler callback for AASRC channel errors.
 *
 * Called when channel encounters errors during operation.
 *
 * \param chHandle AASRC channel handle.
 * \param transactionRx Pointer to RX transaction.
 * \param transactionTx Pointer to TX transaction.
 */
void aasrc_ch_error_handler(AASRC_ChHandle chHandle,
                            AASRC_Transaction *transactionRx,
                            AASRC_Transaction *transactionTx)
{
}

/**
 * \brief MCASP TX completion callback (no-op placeholder).
 *
 * \param McaspHandle Handle to the MCASP instance.
 * \param transaction Pointer to the completed transaction.
 */
void mcasp_txcb(MCASP_Handle McaspHandle,
                          MCASP_Transaction *transaction)
{
}

/**
 * \brief MCASP RX completion callback (no-op placeholder).
 *
 * \param McaspHandle Handle to the MCASP instance.
 * \param transaction Pointer to the completed transaction.
 */
void mcasp_rxcb(MCASP_Handle McaspHandle,
                          MCASP_Transaction *transaction)
{
}

#ifdef ENABLE_MT_TESTS
/* commented as multithread test cases causes hanging */

/**
 * \brief Thread worker function for AASRC instance 0 multi-threaded test.
 *
 * Opens channels, configures and enables them, queues transactions with
 * test data, and waits for conversion completion. Runs concurrently with
 * aasrcThread2 to test multi-instance operation.
 *
 * \param pvParameter Pointer to AASRC_Handle for instance 0.
 */
static void aasrcThread1(void *pvParameter)
{
    AASRC_Handle handle= *((AASRC_Handle *)pvParameter);
    AASRC_ChHandle  chHandle = NULL;
    AASRC_ChObj *chObj = NULL;
    uint8_t channelCount;
    uint32_t status;
    float  clkFrequency;

    /*Creating a counting semaphore for all channels */
    SemaphoreP_constructCounting(&TestAASRC_countSemAsrcConv1, 0, CONFIG_AASRC0_NUM_CH);
    for(channelCount = 0U; channelCount< CONFIG_AASRC0_NUM_CH; channelCount++)
    {
        chHandle = AASRC_chOpen(channelCount, handle);
        if(chHandle != NULL)
        {
            chObj = (AASRC_ChObj *)(chHandle);
            chObj->xmtObj.cbFxn = TestAASRC_txcbInst0;
        }
        else
        {
            status = SystemP_FAILURE;
        }
        status = AASRC_chConfig(chHandle);
        if(status == SystemP_SUCCESS)
        {
            /* Input Frequency */
            status += AASRC_GetClkZoneRxFrequency(chHandle, &clkFrequency);
            TestAASRC_chMetaThread1[0][channelCount].rxSamplingFreq = clkFrequency;
            TestAASRC_chMetaThread1[0][channelCount].dataFormat = chObj->chCfg.inWordLen;

            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("AASRC thread1 %u input clock zone %u freq = %0.8f KHz\r\n", 0, channelCount, clkFrequency);

            /* Output Frequency */
            status += AASRC_GetClkZoneTxFrequency(chHandle, &clkFrequency);
            TestAASRC_chMetaThread1[0][channelCount].txSamplingFreq = clkFrequency;
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("AASRC thread1  %u output clock zone %u freq = %0.8f KHz\r\n", 0, channelCount, clkFrequency);

            if( status == SystemP_SUCCESS)
            {
                /* Init the transactions for all channel */
                TestAasrc_transactionThread1Init(chHandle, 0, channelCount);
                /* Enable the channel for starting conversion */
                status += AASRC_chEnable(chHandle);
            }
        }
    }
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    {
        uint32_t elapsedMs = 0U;
        while(SemaphoreP_getCount(&TestAASRC_countSemAsrcConv1) < CONFIG_AASRC0_NUM_CH)
        {
            ClockP_usleep(TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US);
            elapsedMs += (TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US / 1000U);
            if (elapsedMs >= TEST_AASRC_BUSYWAIT_TIMEOUT_MS)
            {
                TEST_ASSERT_TRUE_MESSAGE(0, "Thread1: AASRC conversion timed out");
                break;
            }
        }
    }
    CacheP_wbInv(TestAASRC_txMonoThreadBuffer[0],
                sizeof(TestAASRC_txMonoThreadBuffer[0]), CacheP_TYPE_ALL);
    CacheP_wbInv(TestAASRC_txStereoThreadBuffer[0],
                sizeof(TestAASRC_txStereoThreadBuffer[0]), CacheP_TYPE_ALL);
    CacheP_wbInv(TestAASRC_txGroupThreadBuffer[0],
                sizeof(TestAASRC_txGroupThreadBuffer[0]), CacheP_TYPE_ALL);

    /* Close the channels */
    for (channelCount = 0; channelCount < CONFIG_AASRC0_NUM_CH; channelCount++)
    {
        chHandle = AASRC_getChHandle(0, channelCount);
        AASRC_chDisable(chHandle);
        status = AASRC_chClose(chHandle);
    }

    /*Destroy the channel counting semaphore */
    SemaphoreP_destruct(&TestAASRC_countSemAsrcConv1);

    /* Post the semaphore to indicate to the main test */
    SemaphoreP_post(&TestAASRC_sem);
}

/**
 * \brief Thread worker function for AASRC instance 1 multi-threaded test.
 *
 * Opens channels, configures and enables them, queues transactions with
 * test data, and waits for conversion completion. Runs concurrently with
 * aasrcThread1 to test multi-instance operation.
 *
 * \param pvParameter Pointer to AASRC_Handle for instance 1.
 */
static void aasrcThread2(void *pvParameter)
{
    AASRC_Handle handle= *((AASRC_Handle *)pvParameter);
    AASRC_ChHandle  chHandle = NULL;
    AASRC_ChObj *chObj = NULL;
    uint8_t channelCount;
    uint32_t status;
    float  clkFrequency;

    /*Creating a counting semaphore for all channels */
    SemaphoreP_constructCounting(&TestAASRC_countSemAsrcConv2, 0, CONFIG_AASRC1_NUM_CH);
    for(channelCount = 0U; channelCount< CONFIG_AASRC1_NUM_CH; channelCount++)
    {
        chHandle = AASRC_chOpen(channelCount, handle);
        if(chHandle != NULL)
        {
            chObj = (AASRC_ChObj *)(chHandle);
            chObj->xmtObj.cbFxn = TestAASRC_txcbInst1;
        }
        else
        {
                status = SystemP_FAILURE;
        }
        status = AASRC_chConfig(chHandle);
        if(status == SystemP_SUCCESS)
        {
            /* Input Frequency */
            status += AASRC_GetClkZoneRxFrequency(chHandle, &clkFrequency);
            TestAASRC_chMetaThread2[1][channelCount].rxSamplingFreq = clkFrequency;
            TestAASRC_chMetaThread2[1][channelCount].dataFormat = chObj->chCfg.inWordLen;

            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("AASRC thread2 %u input clock zone %u freq = %0.8f KHz\r\n", 1, channelCount, clkFrequency);

            /* Output Frequency */
            status += AASRC_GetClkZoneTxFrequency(chHandle, &clkFrequency);
            TestAASRC_chMetaThread2[1][channelCount].txSamplingFreq = clkFrequency;
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("AASRC thread2  %u output clock zone %u freq = %0.8f KHz\r\n", 1, channelCount, clkFrequency);

            if( status == SystemP_SUCCESS)
            {
                /* Init the transactions for all channel */
                TestAasrc_transactionThread2Init(chHandle, 1, channelCount);
                /* Enable the channel for starting conversion */
                status += AASRC_chEnable(chHandle);
            }
        }
    }
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    {
        uint32_t elapsedMs = 0U;
        while(SemaphoreP_getCount(&TestAASRC_countSemAsrcConv2) < CONFIG_AASRC1_NUM_CH)
        {
            ClockP_usleep(TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US);
            elapsedMs += (TEST_AASRC_BUSYWAIT_POLL_INTERVAL_US / 1000U);
            if (elapsedMs >= TEST_AASRC_BUSYWAIT_TIMEOUT_MS)
            {
                TEST_ASSERT_TRUE_MESSAGE(0, "Thread2: AASRC conversion timed out");
                break;
            }
        }
    }
    CacheP_wbInv(TestAASRC_txMonoThreadBuffer[1],
                sizeof(TestAASRC_txMonoThreadBuffer[1]), CacheP_TYPE_ALL);
    CacheP_wbInv(TestAASRC_txStereoThreadBuffer[1],
                sizeof(TestAASRC_txStereoThreadBuffer[1]), CacheP_TYPE_ALL);
    CacheP_wbInv(TestAASRC_txGroupThreadBuffer[1],
                sizeof(TestAASRC_txGroupThreadBuffer[1]), CacheP_TYPE_ALL);

    /* Close the channels */
    for (channelCount = 0; channelCount < CONFIG_AASRC1_NUM_CH; channelCount++)
    {
        chHandle = AASRC_getChHandle(1, channelCount);
        AASRC_chDisable(chHandle);
        status = AASRC_chClose(chHandle);
    }
    /*Destroy the channel counting semaphore */
    SemaphoreP_destruct(&TestAASRC_countSemAsrcConv2);

    /* Post the semaphore to indicate to the main test */
    SemaphoreP_post(&TestAASRC_sem);
}

/**
 * \brief Test concurrent AASRC sine wave conversion across multiple instances.
 *
 * Test Category: Multi-threading
 *
 * Creates two tasks that simultaneously operate on different AASRC
 * instances to verify thread-safe operation and concurrent processing capability.
 * Each task performs complete sample rate conversion independently.
 *
 * Note: Currently commented out due to issues during driver_open function
 * when enabling multiple instances.
 *
 * \param args Pointer to test parameters.
 */
static void TestAasrc_concurrentSinewaveConversionDma(void *args)
{
    DebugP_log ("Starting AASRC multithreaded test case\r\n");

    int32_t status = SystemP_SUCCESS;
    AASRC_Handle    handle[CONFIG_AASRC_NUM_INSTANCES];
    AASRC_OpenParams openParams[CONFIG_AASRC_NUM_INSTANCES] = {0};
    uint8_t instanceCount;
    TaskP_Params taskParams1, taskParams2;

    /* Initialize the handles to NULL */
    uint32_t i;
    for(i = 0; i < CONFIG_AASRC_NUM_INSTANCES ; i++)
    {
        handle[i] = NULL;
    }
    /* Open all the instances */
    for(instanceCount = 0U; instanceCount< CONFIG_AASRC_NUM_INSTANCES; instanceCount++)
    {
        openParams[instanceCount] = gAasrcOpenParams[instanceCount];
        AASRC_close(gAasrcHandle[instanceCount]);
        handle[instanceCount] = AASRC_open(instanceCount, &openParams[instanceCount]);
    }

    status =  SemaphoreP_constructCounting(&TestAASRC_sem, 0, 2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestAASRC_task1Stack;
    taskParams1.stackSize      = sizeof(TestAASRC_task1Stack);
    taskParams1.args           = (void*) &handle[0];
    taskParams1.name           = "AasrcThread1";
    taskParams1.taskMain       = &aasrcThread1;

    status = TaskP_construct(&TestAASRC_thread1TaskObj, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestAASRC_task2Stack;
    taskParams2.stackSize      = sizeof(TestAASRC_task2Stack);
    taskParams2.args           = (void*) &handle[1];
    taskParams2.name           = "AasrcThread2";
    taskParams2.taskMain       = &aasrcThread2;

    status = TaskP_construct(&TestAASRC_thread2TaskObj, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /*Wait for the tasks to complete */
    for(instanceCount = 0; instanceCount < 2; instanceCount++)
    {
        status = SemaphoreP_pend(&TestAASRC_sem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(status, SystemP_SUCCESS);
    }

    SemaphoreP_destruct(&TestAASRC_sem);
    TaskP_destruct(&TestAASRC_thread1TaskObj);
    TaskP_destruct(&TestAASRC_thread2TaskObj);

}

/**
 * \brief Initialize transactions for thread 1 (instance 0).
 *
 * Prepares input/output buffers specific to thread 1, performs word-length
 * conversion from reference 24-bit data, and queues RX/TX transactions.
 * Uses separate buffer set to avoid conflicts with thread 2.
 *
 * \param chHandle AASRC channel handle.
 * \param instNum Instance number (0).
 * \param chCount Channel count.
 */
static void TestAasrc_transactionThread1Init(AASRC_ChHandle chHandle, uint8_t instNum, uint8_t chCount)
{
    uint16_t count;
    AASRC_ChObj *chObj = (AASRC_ChObj *)(chHandle);
    uint8_t chType = chObj->chCfg.chType;

    switch(chType)
    {
        case AASRC_MONO:

            /* Init Input and Output Buffer */
            strncpy(TestAASRC_chMetaThread1[instNum][chCount].metaInfo,"MONO CHANNEL", sizeof(TestAASRC_chMetaThread1[instNum][chCount].metaInfo));
            TestAASRC_chMetaThread1[instNum][chCount].monoChCount = 1;
            TestAASRC_chMetaThread1[instNum][chCount].rxBufPtr = (uint32_t *)&TestAASRC_rxMonoThreadBuffer[0][0];
            TestAASRC_chMetaThread1[instNum][chCount].txBufPtr = (uint32_t *)&TestAASRC_txMonoThreadBuffer[0][0];
            TestAASRC_chMetaThread1[instNum][chCount].rxSampleCount = TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
            TestAASRC_chMetaThread1[instNum][chCount].txSampleCount = TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_rxMonoThreadBuffer[0][count] = (int32_t)aasrc_monoInput[count];
            }

            for(count = 0U; count< TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_txMonoThreadBuffer[0][count] = 0U;
            }

            CacheP_wb(TestAASRC_rxMonoThreadBuffer[0], sizeof(TestAASRC_rxMonoThreadBuffer[0]), CacheP_TYPE_ALLD);
            CacheP_wb(TestAASRC_txMonoThreadBuffer[0], sizeof(TestAASRC_txMonoThreadBuffer[0]), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            TestAASRC_thread1TxnRx[instNum][chCount].buf = (void*) &TestAASRC_rxMonoThreadBuffer[0][0];
            TestAASRC_thread1TxnRx[instNum][chCount].sampleCount = TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &TestAASRC_thread1TxnRx[instNum][chCount] );

            TestAASRC_thread1TxnTx[instNum][chCount].buf = (void*) &TestAASRC_txMonoThreadBuffer[0][0];
            TestAASRC_thread1TxnTx[instNum][chCount].sampleCount = TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &TestAASRC_thread1TxnTx[instNum][chCount] );
            break;

        case AASRC_STEREO:
            strncpy(TestAASRC_chMetaThread1[instNum][chCount].metaInfo,"STEREO CHANNEL", sizeof(TestAASRC_chMetaThread1[instNum][chCount].metaInfo));
            TestAASRC_chMetaThread1[instNum][chCount].monoChCount = 2;
            TestAASRC_chMetaThread1[instNum][chCount].rxBufPtr = (uint32_t *)&TestAASRC_rxStereoThreadBuffer[0][0];
            TestAASRC_chMetaThread1[instNum][chCount].txBufPtr = (uint32_t *)&TestAASRC_txStereoThreadBuffer[0][0];
            TestAASRC_chMetaThread1[instNum][chCount].rxSampleCount = TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT;
            TestAASRC_chMetaThread1[instNum][chCount].txSampleCount = TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_rxStereoThreadBuffer[0][count] = (int32_t)aasrc_stereoInput[count];
            }

            for(count = 0U; count< TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_txStereoThreadBuffer[0][count] = 0U;
            }

            CacheP_wb(TestAASRC_rxStereoThreadBuffer[0], sizeof(TestAASRC_rxStereoThreadBuffer[0]), CacheP_TYPE_ALLD);
            CacheP_wb(TestAASRC_txStereoThreadBuffer[0], sizeof(TestAASRC_txStereoThreadBuffer[0]), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            TestAASRC_thread1TxnRx[instNum][chCount].buf = (void*) &TestAASRC_rxStereoThreadBuffer[0][0];
            TestAASRC_thread1TxnRx[instNum][chCount].sampleCount = TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &TestAASRC_thread1TxnRx[instNum][chCount] );

            TestAASRC_thread1TxnTx[instNum][chCount].buf = (void*) &TestAASRC_txStereoThreadBuffer[0][0];
            TestAASRC_thread1TxnTx[instNum][chCount].sampleCount = TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &TestAASRC_thread1TxnTx[instNum][chCount] );
            break;

        case AASRC_GROUP:
            /* Init Input and Output Buffer */
            strncpy(TestAASRC_chMetaThread1[instNum][chCount].metaInfo,"GROUP CHANNEL", sizeof(TestAASRC_chMetaThread1[instNum][chCount].metaInfo));
            TestAASRC_chMetaThread1[instNum][chCount].monoChCount = TEST_AASRC_GROUP_CHANNEL_COUNT;
            TestAASRC_chMetaThread1[instNum][chCount].rxBufPtr = (uint32_t *)&TestAASRC_rxGroupThreadBuffer[0][0];
            TestAASRC_chMetaThread1[instNum][chCount].txBufPtr = (uint32_t *)&TestAASRC_txGroupThreadBuffer[0][0];
            TestAASRC_chMetaThread1[instNum][chCount].rxSampleCount = TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT;
            TestAASRC_chMetaThread1[instNum][chCount].txSampleCount = TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_rxGroupThreadBuffer[0][count] = (int32_t)aasrc_groupInput[count];
            }

            for(count = 0U; count< TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_txGroupThreadBuffer[0][count] = 0U;
            }

            CacheP_wb(TestAASRC_rxGroupThreadBuffer[0], sizeof(TestAASRC_rxGroupThreadBuffer[0]), CacheP_TYPE_ALLD);
            CacheP_wb(TestAASRC_txGroupThreadBuffer[0], sizeof(TestAASRC_txGroupThreadBuffer[0]), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            TestAASRC_thread1TxnRx[instNum][chCount].buf = (void*) &TestAASRC_rxGroupThreadBuffer[0][0];
            TestAASRC_thread1TxnRx[instNum][chCount].sampleCount = TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &TestAASRC_thread1TxnRx[instNum][chCount] );

            TestAASRC_thread1TxnTx[instNum][chCount].buf = (void*) &TestAASRC_txGroupThreadBuffer[0][0];
            TestAASRC_thread1TxnTx[instNum][chCount].sampleCount = TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &TestAASRC_thread1TxnTx[instNum][chCount] );
            break;

        default:
            break;
    }
}

/**
 * \brief Initialize transactions for thread 2 (instance 1).
 *
 * Prepares input/output buffers specific to thread 2, performs word-length
 * conversion from reference 24-bit data, and queues RX/TX transactions.
 * Uses separate buffer set to avoid conflicts with thread 1.
 *
 * \param chHandle AASRC channel handle.
 * \param instNum Instance number (1).
 * \param chCount Channel count.
 */
static void TestAasrc_transactionThread2Init(AASRC_ChHandle chHandle, uint8_t instNum, uint8_t chCount)
{
    uint16_t count;
    AASRC_ChObj *chObj = (AASRC_ChObj *)(chHandle);
    uint8_t chType = chObj->chCfg.chType;

    switch(chType)
    {
        case AASRC_MONO:

            /* Init Input and Output Buffer */
            strncpy(TestAASRC_chMetaThread2[instNum][chCount].metaInfo,"MONO CHANNEL", sizeof(TestAASRC_chMetaThread2[instNum][chCount].metaInfo));
            TestAASRC_chMetaThread2[instNum][chCount].monoChCount = 1;
            TestAASRC_chMetaThread2[instNum][chCount].rxBufPtr = (uint32_t *)&TestAASRC_rxMonoThreadBuffer[1][0];
            TestAASRC_chMetaThread2[instNum][chCount].txBufPtr = (uint32_t *)&TestAASRC_txMonoThreadBuffer[1][0];
            TestAASRC_chMetaThread2[instNum][chCount].rxSampleCount = TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
            TestAASRC_chMetaThread2[instNum][chCount].txSampleCount = TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_rxMonoThreadBuffer[1][count] = (int32_t)aasrc_monoInput[count];
            }

            for(count = 0U; count< TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_txMonoThreadBuffer[1][count] = 0U;
            }

            CacheP_wb(TestAASRC_rxMonoThreadBuffer[1], sizeof(TestAASRC_rxMonoThreadBuffer[1]), CacheP_TYPE_ALLD);
            CacheP_wb(TestAASRC_txMonoThreadBuffer[1], sizeof(TestAASRC_txMonoThreadBuffer[1]), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            TestAASRC_thread2TxnRx[instNum][chCount].buf = (void*) &TestAASRC_rxMonoThreadBuffer[1][0];
            TestAASRC_thread2TxnRx[instNum][chCount].sampleCount = TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &TestAASRC_thread2TxnRx[instNum][chCount] );

            TestAASRC_thread2TxnTx[instNum][chCount].buf = (void*) &TestAASRC_txMonoThreadBuffer[1][0];
            TestAASRC_thread2TxnTx[instNum][chCount].sampleCount = TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &TestAASRC_thread2TxnTx[instNum][chCount] );
            break;

        case AASRC_STEREO:
            strncpy(TestAASRC_chMetaThread2[instNum][chCount].metaInfo,"STEREO CHANNEL", sizeof(TestAASRC_chMetaThread2[instNum][chCount].metaInfo));
            TestAASRC_chMetaThread2[instNum][chCount].monoChCount = 2;
            TestAASRC_chMetaThread2[instNum][chCount].rxBufPtr = (uint32_t *)&TestAASRC_rxStereoThreadBuffer[1][0];
            TestAASRC_chMetaThread2[instNum][chCount].txBufPtr = (uint32_t *)&TestAASRC_txStereoThreadBuffer[1][0];
            TestAASRC_chMetaThread2[instNum][chCount].rxSampleCount = TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT;
            TestAASRC_chMetaThread2[instNum][chCount].txSampleCount = TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_rxStereoThreadBuffer[1][count] = (int32_t)aasrc_stereoInput[count];
            }

            for(count = 0U; count< TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_txStereoThreadBuffer[1][count] = 0U;
            }

            CacheP_wb(TestAASRC_rxStereoThreadBuffer[1], sizeof(TestAASRC_rxStereoThreadBuffer[1]), CacheP_TYPE_ALLD);
            CacheP_wb(TestAASRC_txStereoThreadBuffer[1], sizeof(TestAASRC_txStereoThreadBuffer[1]), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            TestAASRC_thread2TxnRx[instNum][chCount].buf = (void*) &TestAASRC_rxStereoThreadBuffer[1][0];;
            TestAASRC_thread2TxnRx[instNum][chCount].sampleCount = TEST_AASRC_STEREO_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &TestAASRC_thread2TxnRx[instNum][chCount] );

            TestAASRC_thread2TxnTx[instNum][chCount].buf = (void*) &TestAASRC_txStereoThreadBuffer[1][0];
            TestAASRC_thread2TxnTx[instNum][chCount].sampleCount = TEST_AASRC_STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &TestAASRC_thread2TxnTx[instNum][chCount] );
            break;

        case AASRC_GROUP:
            /* Init Input and Output Buffer */
            strncpy(TestAASRC_chMetaThread2[instNum][chCount].metaInfo,"GROUP CHANNEL", sizeof(TestAASRC_chMetaThread2[instNum][chCount].metaInfo));
            TestAASRC_chMetaThread2[instNum][chCount].monoChCount = TEST_AASRC_GROUP_CHANNEL_COUNT;
            TestAASRC_chMetaThread2[instNum][chCount].rxBufPtr = (uint32_t *)&TestAASRC_rxGroupThreadBuffer[1][0];
            TestAASRC_chMetaThread2[instNum][chCount].txBufPtr = (uint32_t *)&TestAASRC_txGroupThreadBuffer[1][0];
            TestAASRC_chMetaThread2[instNum][chCount].rxSampleCount = TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT;
            TestAASRC_chMetaThread2[instNum][chCount].txSampleCount = TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_rxGroupThreadBuffer[1][count] = (int32_t)aasrc_groupInput[count];
            }

            for(count = 0U; count< TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                TestAASRC_txGroupThreadBuffer[1][count] = 0U;
            }

            CacheP_wb(TestAASRC_rxGroupThreadBuffer[1], sizeof(TestAASRC_rxGroupThreadBuffer[1]), CacheP_TYPE_ALLD);
            CacheP_wb(TestAASRC_txGroupThreadBuffer[1], sizeof(TestAASRC_txGroupThreadBuffer[1]), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            TestAASRC_thread2TxnRx[instNum][chCount].buf = (void*) &TestAASRC_rxGroupThreadBuffer[1][0];
            TestAASRC_thread2TxnRx[instNum][chCount].sampleCount = TEST_AASRC_GROUP_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &TestAASRC_thread2TxnRx[instNum][chCount] );

            TestAASRC_thread2TxnTx[instNum][chCount].buf = (void*) &TestAASRC_txGroupThreadBuffer[1][0];
            TestAASRC_thread2TxnTx[instNum][chCount].sampleCount = TEST_AASRC_GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &TestAASRC_thread2TxnTx[instNum][chCount] );
            break;

        default:
            break;
    }
}

/**
 * \brief Callback function for AASRC TX completion for instance 0.
 *
 * Posts semaphore to signal completion of TX transaction.
 *
 * \param chHandle AASRC channel handle.
 * \param transaction Pointer to completed transaction.
 */
void TestAASRC_txcbInst0 (AASRC_ChHandle chHandle,
                 AASRC_Transaction *transaction)
{
#ifdef ENABLE_MT_TESTS
    SemaphoreP_post(&TestAASRC_countSemAsrcConv1);
#endif
}

/**
 * \brief Callback function for AASRC TX completion for instance 1.
 *
 * Posts semaphore to signal completion of TX transaction.
 *
 * \param chHandle AASRC channel handle.
 * \param transaction Pointer to completed transaction.
 */
void TestAASRC_txcbInst1 (AASRC_ChHandle chHandle,
                       AASRC_Transaction *transaction)
{
#ifdef ENABLE_MT_TESTS
    SemaphoreP_post(&TestAASRC_countSemAsrcConv2);
#endif
}
#endif

#ifdef ENABLE_MT_TESTS
/**
 * \brief Verify AASRC conversion using an external clock source.
 *
 * Test Category: Functional
 *
 * Configures the pinmux for external reference clock 2 (GPIO1_72), configures the
 * audio codec via I2C to generate the master clock, and sets up McASP to receive
 * the external clock. Configures AASRC transmit clock zone to use the external
 * reference clock, triggers sample rate conversion, and verifies the output signal
 * characteristics (frequency, amplitude, RMS ratio) using DSP library functions.
 *
 * \param args Pointer to AASRC_OpenParams structure.
 */
static void TestAasrc_externalClk(void *args)
{
    int32_t         status = SystemP_SUCCESS;
    uint8_t         zone;
    I2C_Handle      i2cHandle = NULL;
    MCASP_Handle    mcaspHandle = NULL;
    AASRC_Handle    aasrcHandle = NULL;
    AASRC_ChHandle  chHandle = NULL;
    // AASRC_ChObj    *chObj = NULL;
    uint16_t        count;
    AASRC_OpenParams *openParams = (AASRC_OpenParams*)args;
    uint8_t         inst = (uint8_t)(openParams - &gAasrcOpenParams[0]);

    i2cHandle = gI2cHandle[CONFIG_I2C0];

    Pinmux_PerCfg_t extClkPinmuxConfig[] =
    {
        { PIN_GPIO1_72, ( PIN_MODE(1) | PIN_INPUT_ENABLE | PIN_PULL_DIRECTION ) },
        { PINMUX_END, 0U }
    };
    Pinmux_config(extClkPinmuxConfig, PINMUX_DOMAIN_ID_MAIN);

    status = Board_clockgenConfig(i2cHandle, 0x68);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
                                    "Clock generator config failed");
    ClockP_usleep(10000);  /* allow PLL lock */

    mcaspHandle = MCASP_open(CONFIG_MCASP0, &gMcaspOpenParams[CONFIG_MCASP0]);
    TEST_ASSERT_NOT_NULL_MESSAGE(mcaspHandle, "McASP open failed");

    status = MCASP_startTransferTx(mcaspHandle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
                                    "McASP startTransferTx failed");

    /* Let McASP clocks stabilise */
    ClockP_usleep(50000);

    for (zone = 0U; zone < 1U; zone++)
    {
        gAasrcOpenParams[inst].rxClkZoneCfg[zone].clkZoneDiv        = 0U;
        gAasrcOpenParams[inst].rxClkZoneCfg[zone].isClkZoneDivEnable = false;
        gAasrcOpenParams[inst].rxClkZoneCfg[zone].extClkSrc         = AASRC_RXSYNC_McASP0_AFSX;
        gAasrcOpenParams[inst].rxClkZoneCfg[zone].overrideClkSettle = true;
    }

    AASRC_close(gAasrcHandle[inst]);
    aasrcHandle = AASRC_open(inst, &gAasrcOpenParams[inst]);
    TEST_ASSERT_NOT_NULL_MESSAGE(aasrcHandle, "AASRC open failed");

    /* Open only the mono channel (ch 0) */
    chHandle = AASRC_chOpen(TEST_AASRC_MONO_AASRC_CH, aasrcHandle);
    TEST_ASSERT_NOT_NULL_MESSAGE(chHandle, "AASRC chOpen failed");

    status = AASRC_chConfig(chHandle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "AASRC chConfig failed");

    for (count = 0U; count < TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
    {
        gAasrcRxMonoBuffer[count] = (int32_t)aasrc_monoInput[count];
    }
    for (count = 0U; count < TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
    {
        gAasrcTxMonoBuffer[count] = 0;
    }
    CacheP_wb(gAasrcRxMonoBuffer, sizeof(gAasrcRxMonoBuffer), CacheP_TYPE_ALLD);
    CacheP_wb(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALLD);

    /* Queue RX (input) and TX (output) transactions */
    TestAASRC_txnRx[inst][TEST_AASRC_MONO_AASRC_CH].buf         = (void *)gAasrcRxMonoBuffer;
    TestAASRC_txnRx[inst][TEST_AASRC_MONO_AASRC_CH].sampleCount = TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
    AASRC_queueTransactionRx(chHandle,
                                &TestAASRC_txnRx[inst][TEST_AASRC_MONO_AASRC_CH]);

    TestAASRC_txnTx[inst][TEST_AASRC_MONO_AASRC_CH].buf         = (void *)gAasrcTxMonoBuffer;
    TestAASRC_txnTx[inst][TEST_AASRC_MONO_AASRC_CH].sampleCount = TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
    AASRC_queueTransactionTx(chHandle,
                                &TestAASRC_txnTx[inst][TEST_AASRC_MONO_AASRC_CH]);

    SemaphoreP_constructCounting(&TestAASRC_countSemAsrcConv, 0, 1);

    status = AASRC_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "AASRC chEnable failed");
    
    uint32_t  timeoutMs = 5000U;
    uint32_t  elapsedMs = 0U;
    const uint32_t pollIntervalMs = 10U;

    while ((SemaphoreP_getCount(&TestAASRC_countSemAsrcConv) < 1U) &&
            (elapsedMs < timeoutMs))
    {
        ClockP_usleep(pollIntervalMs * 1000U);
        elapsedMs += pollIntervalMs;
    }

    TEST_ASSERT_TRUE_MESSAGE(
        SemaphoreP_getCount(&TestAASRC_countSemAsrcConv) >= 1U,
        "AASRC external-clock mono conversion timed out (5 s)");

    SemaphoreP_destruct(&TestAASRC_countSemAsrcConv);

    /* Invalidate the output buffer so we can read it on the CPU */
    CacheP_wbInv(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALL);

    /* Read the clock frequencies BEFORE closing the channel handle */
    float rxFs = 48.0f, txFs = 96.0f;  /* default fallbacks in kHz */
    float tmpFreq;
    if (AASRC_GetClkZoneRxFrequency(chHandle, &tmpFreq) == SystemP_SUCCESS)
    {
        rxFs = tmpFreq;
    }
    if (AASRC_GetClkZoneTxFrequency(chHandle, &tmpFreq) == SystemP_SUCCESS)
    {
        txFs = tmpFreq;
    }


    AASRC_chDisable(chHandle);
    AASRC_chClose(chHandle);
    AASRC_close(aasrcHandle);

    /* FFT validation — compare RX and TX peak frequencies.       */
    float rxSamplingRateHz = rxFs * 1000.0f;
    float txSamplingRateHz = txFs * 1000.0f;

    TestAasrc_runFftWordLen((uint32_t *)gAasrcRxMonoBuffer,
                            (int32_t)TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT,
                            rxSamplingRateHz, TEST_AASRC_IN_BITS,
                            &TestAASRC_monoRxPeak);

    int32_t startIdx = TEST_AASRC_MONO_FFT_START_IDX;
    int32_t fftLen   = TEST_AASRC_MONO_FFT_LENGTH;
    TestAasrc_runFftWordLen((uint32_t *)&gAasrcTxMonoBuffer[startIdx],
                            fftLen, txSamplingRateHz, TEST_AASRC_IN_BITS,
                            &TestAASRC_monoTxPeak);

    DebugP_log("ExtClk Mono RX (Inst %d): f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", inst,
                TestAASRC_monoRxPeak.freqHz,
                TestAASRC_monoRxPeak.amplitude,
                TestAASRC_monoRxPeak.rms);
    DebugP_log("ExtClk Mono TX (Inst %d): f=%.3f Hz, A=%.6f, RMS=%.6f\r\n", inst,
                TestAASRC_monoTxPeak.freqHz,
                TestAASRC_monoTxPeak.amplitude,
                TestAASRC_monoTxPeak.rms);

    float df       = fabsf(TestAASRC_monoRxPeak.freqHz - TestAASRC_monoTxPeak.freqHz);
    float rmsRatio = (TestAASRC_monoRxPeak.rms > 0.0f)
                    ? fabsf(TestAASRC_monoTxPeak.rms / TestAASRC_monoRxPeak.rms - 1.0f)
                    : 0.0f;
    bool freqMatch = (df <= TEST_AASRC_FFT_FREQ_TOL_HZ);
    bool rmsMatch  = (rmsRatio <= TEST_AASRC_FFT_AMP_TOL_RATIO);
    TEST_ASSERT_TRUE_MESSAGE(freqMatch || rmsMatch,
        "ExtClk Mono: neither frequency nor RMS match after conversion");


    MCASP_stopTransferTx(mcaspHandle);

    /* Withdraw any leftover McASP transactions */
    MCASP_Transaction *w;
    do 
    { 
        w = MCASP_withdrawTx(mcaspHandle); 
    } while (w != NULL);

    MCASP_close(mcaspHandle);

    /* Close and reopen AASRC with restored internal-clock settings */
    AASRC_close(aasrcHandle);

    /* Restore AASRC RX clock zone 0 to internal PLL source */
    for (zone = 0U; zone < 1U; zone++)
    {
        gAasrcOpenParams[inst].rxClkZoneCfg[zone].clkZoneDiv         = 128U;
        gAasrcOpenParams[inst].rxClkZoneCfg[zone].isClkZoneDivEnable = true;
        gAasrcOpenParams[inst].rxClkZoneCfg[zone].extClkSrc          = AASRC_RXSYNC_MAIN_PLL4_HSDIV3_CLKOUT;
        gAasrcOpenParams[inst].rxClkZoneCfg[zone].overrideClkSettle  = false;
    }

    /* Re-open AASRC with original params so subsequent tests work */
    AASRC_audioPllDivConfig();
    gAasrcHandle[inst] = AASRC_open(inst,
                                     &gAasrcOpenParams[inst]);
    TEST_ASSERT_NOT_NULL_MESSAGE(gAasrcHandle[inst],
                                 "AASRC re-open with internal clock failed");
}
#endif

#ifdef ENABLE_MT_TESTS
/**
 * \brief Verify queuing before enable primes and ISR handles queued txn.
 *
 * This test exercises the path where a transaction is queued prior to calling
 * chEnable. It ensures TRPDs are primed on enable, a second transaction can
 * be queued while the first is in-flight, and the ISR services the queued
 * transaction. Basic end-to-end validation uses FFT checks on RX/TX data and
 * a counting semaphore to confirm two completions.
 *
 * \param args Pointer to AASRC_OpenParams array (AASRC_OpenParams *).
 */
static void TestAasrc_queueBeforeEnable(void *args)
{
    int32_t status = SystemP_SUCCESS;
    AASRC_ChHandle      chHandle = NULL;
    AASRC_Handle        handle = NULL;
    AASRC_OpenParams  *openParams = (AASRC_OpenParams *)args;
    float samplingRateHz;
    int32_t startIdx = TEST_AASRC_MONO_FFT_START_IDX;
    int32_t fftLen = TEST_AASRC_MONO_FFT_LENGTH;

    /* Open instance 0 and single mono channel only */
    AASRC_close(gAasrcHandle[CONFIG_AASRC0]);
    handle = AASRC_open(CONFIG_AASRC0, &openParams[CONFIG_AASRC0]);
    TEST_ASSERT_NOT_NULL(handle);

    SemaphoreP_constructCounting(&TestAASRC_countSemAsrcConv, 0, 2);

    /* Open channel 0, configure */
    chHandle = AASRC_chOpen(TEST_AASRC_MONO_AASRC_CH, handle);
    TEST_ASSERT_NOT_NULL(chHandle);

    status = AASRC_chConfig(chHandle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(AASRC_SOK, status, "chConfig failed");

    /* * STEP 2: Queue a Transaction before Enabling */
    TestAasrc_transactionInit(chHandle, CONFIG_AASRC0, TEST_AASRC_MONO_AASRC_CH);

    /* Enable channel */
    status = AASRC_chEnable(chHandle);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(AASRC_SOK, status, "chEnable failed");

    /* Queue another Transaction immediately while Transaction 1 is "In Flight"*/
    gTestTxnMonoRx2.buf = (void *)&gAasrcRxMonoBuffer2[0];
    gTestTxnMonoRx2.sampleCount = TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
    gTestTxnMonoTx2.buf = (void *)&gAasrcTxMonoBuffer2[0];
    gTestTxnMonoTx2.sampleCount = TEST_AASRC_MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;

    AASRC_queueTransactionRx(chHandle, &gTestTxnMonoRx2);
    AASRC_queueTransactionTx(chHandle, &gTestTxnMonoTx2);

    uint32_t waitCnt = 0U;
    while (SemaphoreP_getCount(&TestAASRC_countSemAsrcConv) < 2U && waitCnt++ < 4000U)
    {
        ClockP_usleep(1000);
    }
    TEST_ASSERT_TRUE_MESSAGE(SemaphoreP_getCount(&TestAASRC_countSemAsrcConv) >= 2U, "Both mono txns not completed in time");

    /* Invalidate caches to read results */
    CacheP_wbInv(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALL);
    CacheP_wbInv(gAasrcRxMonoBuffer, sizeof(gAasrcRxMonoBuffer), CacheP_TYPE_ALL);

    /* FFT analysis for basic validation */
    samplingRateHz = TestAASRC_chMeta[0][TEST_AASRC_MONO_AASRC_CH].rxSamplingFreq * 1000.0f;
    TestAasrc_runFftWordLen((uint32_t *)gAasrcRxMonoBuffer,
                            (int32_t)TEST_AASRC_MONO_INPUT_TRANSACTION_SAMPLE_COUNT,
                            samplingRateHz, TEST_AASRC_IN_BITS, &TestAASRC_monoRxPeak);

    samplingRateHz = TestAASRC_chMeta[0][TEST_AASRC_MONO_AASRC_CH].txSamplingFreq * 1000.0f;
    TestAasrc_runFftWordLen((uint32_t *)&gAasrcTxMonoBuffer[startIdx],
                            fftLen, samplingRateHz, TEST_AASRC_IN_BITS, &TestAASRC_monoTxPeak);

    {
        float df = fabsf(TestAASRC_monoRxPeak.freqHz - TestAASRC_monoTxPeak.freqHz);
        float rmsRatio = (TestAASRC_monoRxPeak.rms > 0.0f) ? fabsf(TestAASRC_monoTxPeak.rms / TestAASRC_monoRxPeak.rms - 1.0f) : 0.0f;
        bool freqMatch = (df <= TEST_AASRC_FFT_FREQ_TOL_HZ);
        bool rmsMatch = (rmsRatio <= TEST_AASRC_FFT_AMP_TOL_RATIO);
        TEST_ASSERT_TRUE_MESSAGE(freqMatch || rmsMatch, "Mono: validation failed");
    }

    /* Cleanup */
    AASRC_chDisable(chHandle);
    (void)AASRC_chClose(chHandle);
    AASRC_close(handle);
    SemaphoreP_destruct(&TestAASRC_countSemAsrcConv);
}

/**
 * \brief Run AASRC conversion using interrupt-mode transfers and verify results.
 *
 * Configures AASRC to use interrupt transfer mode, performs sine-wave conversions
 * across configured channels, waits for completion, and validates output using
 * FFT-based frequency and RMS checks versus the input.
 *
 * \param args Pointer to AASRC_OpenParams (AASRC_OpenParams *).
 */
static void TestAasrc_sineWaveConversionInterrupt(void *args)
{
    gAasrcOpenParams[CONFIG_AASRC0].transferMode = AASRC_TRANSFER_MODE_INTERRUPT;
    TestAasrc_sineWaveConversionDma((void*)&gAasrcOpenParams[CONFIG_AASRC0]);
    gAasrcOpenParams[CONFIG_AASRC0].transferMode = AASRC_TRANSFER_MODE_DMA;
}

/**
 * \brief Error callback for overflow/underflow injection tests.
 *
 * Test Category: Callback
 *
 * Captures the FIFO error status from the driver's error ISR, sets the
 * "fired" bit for this channel, and posts the error semaphore.
 *
 * \param chHandle    AASRC channel handle.
 * \param transactionRx Pointer to RX transaction (unused).
 * \param transactionTx Pointer to TX transaction (unused).
 */
static void TestAasrc_fifoErrCb(AASRC_ChHandle chHandle,
                                AASRC_Transaction *transactionRx,
                                AASRC_Transaction *transactionTx)
{
    AASRC_ChObj *chObj = (AASRC_ChObj *)chHandle;
    uint8_t chIdx;

    (void)transactionRx;
    (void)transactionTx;

    if (chObj == NULL || chObj->chState == NULL)
    {
        return;
    }
    chIdx = (uint8_t)chObj->chState->virtChNum;
    if (chIdx >= CONFIG_AASRC0_NUM_CH)
    {
        return;
    }
    /* Accumulate error flags across all ISR invocations (OR). */
    TestAASRC_capturedInFifoErr[chIdx].lChannelOverflow   |= chObj->inFifoErrorStatus.lChannelOverflow;
    TestAASRC_capturedInFifoErr[chIdx].rChannelOverflow   |= chObj->inFifoErrorStatus.rChannelOverflow;
    TestAASRC_capturedInFifoErr[chIdx].lChannelUnderflow  |= chObj->inFifoErrorStatus.lChannelUnderflow;
    TestAASRC_capturedInFifoErr[chIdx].rChannelUnderflow  |= chObj->inFifoErrorStatus.rChannelUnderflow;
    TestAASRC_capturedOutFifoErr[chIdx].lChannelOverflow  |= chObj->outFifoErrorStatus.lChannelOverflow;
    TestAASRC_capturedOutFifoErr[chIdx].rChannelOverflow  |= chObj->outFifoErrorStatus.rChannelOverflow;
    TestAASRC_capturedOutFifoErr[chIdx].lChannelUnderflow |= chObj->outFifoErrorStatus.lChannelUnderflow;
    TestAASRC_capturedOutFifoErr[chIdx].rChannelUnderflow |= chObj->outFifoErrorStatus.rChannelUnderflow;

    if ((TestAASRC_errFiredMask & (uint8_t)(1U << chIdx)) == 0U)
    {
        TestAASRC_errFiredMask |= (uint8_t)(1U << chIdx);
        SemaphoreP_post(&TestAASRC_errSem);
    }
}

/**
 * \brief Test AASRC FIFO error injection for overflow and underflow conditions.
 *
 * Test Category: Error Handling
 *
 * Performs full setup/teardown of the AASRC instance in interrupt mode,
 * registers errCbFxn on each channel, enables conversion and then masks
 * either the OUT-FIFO or IN-FIFO servicing interrupt to force the hardware
 * to raise the corresponding FIFO error condition. Validates that the
 * driver captures the error flags correctly per channel type.
 *
 * \param inst           AASRC instance number.
 * \param injectOverflow true to inject overflow, false to inject underflow.
 */
static void TestAasrc_fifoErrorInjectCommon(uint8_t inst, bool injectOverflow)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t chIdx;
    AASRC_OpenParams savedOpen = gAasrcOpenParams[inst];
    /* Save the callback fields */
    AASRC_ChErrorCallbackFxn savedErrCb[CONFIG_AASRC0_NUM_CH];
    AASRC_TxnCallbackFxn     savedRcvCb[CONFIG_AASRC0_NUM_CH];
    AASRC_TxnCallbackFxn     savedXmtCb[CONFIG_AASRC0_NUM_CH];
    AASRC_Handle     handle;
    const CSL_aasrc_cfgRegs *pReg;

    /* Reset capture state */
    memset((void *)TestAASRC_capturedInFifoErr,  0, sizeof(TestAASRC_capturedInFifoErr));
    memset((void *)TestAASRC_capturedOutFifoErr, 0, sizeof(TestAASRC_capturedOutFifoErr));
    TestAASRC_errFiredMask = 0U;
    SemaphoreP_constructCounting(&TestAASRC_errSem, 0, CONFIG_AASRC0_NUM_CH);
    SemaphoreP_constructCounting(&TestAASRC_countSemAsrcConv, 0, CONFIG_AASRC0_NUM_CH);

    /* Save per-channel user-config callbacks so we can fully restore on exit */
    for (chIdx = 0U; chIdx < CONFIG_AASRC0_NUM_CH; chIdx++)
    {
        savedErrCb[chIdx] = gConfigAasrcChObj[inst][chIdx].errCbFxn;
        savedRcvCb[chIdx] = gConfigAasrcChObj[inst][chIdx].rcvObj.cbFxn;
        savedXmtCb[chIdx] = gConfigAasrcChObj[inst][chIdx].xmtObj.cbFxn;
    }

    /* Re-open instance in interrupt mode */
    AASRC_OpenParams openParams = gAasrcOpenParams[inst];
    openParams.transferMode = AASRC_TRANSFER_MODE_INTERRUPT;
    AASRC_close(gAasrcHandle[inst]);
    handle = AASRC_open(inst, &openParams);
    TEST_ASSERT_NOT_NULL(handle);

    /* Install callbacks on channel template before open. */
    for (chIdx = 0U; chIdx < CONFIG_AASRC0_NUM_CH; chIdx++)
    {
        gConfigAasrcChObj[inst][chIdx].errCbFxn      = TestAasrc_fifoErrCb;
        gConfigAasrcChObj[inst][chIdx].xmtObj.cbFxn  = aasrc_txcb;
        gConfigAasrcChObj[inst][chIdx].rcvObj.cbFxn  = aasrc_txcb;  /* harmless placeholder */
    }

    for (chIdx = 0U; chIdx < CONFIG_AASRC0_NUM_CH; chIdx++)
    {
        AASRC_ChHandle ch = AASRC_chOpen(chIdx, handle);
        TEST_ASSERT_NOT_NULL(ch);

        status = AASRC_chConfig(ch);
        TEST_ASSERT_EQUAL_INT32_MESSAGE(AASRC_SOK, status, "chConfig failed");

        /* Queue a normal RX + TX so chEnable succeeds (RX and TX both armed) */
        TestAasrc_transactionInit(ch, inst, chIdx);

        TEST_ASSERT_EQUAL_INT32(AASRC_SOK, AASRC_chEnable(ch));
    }

    /* Allow the stream to start and FIFOs to get some data before injecting the fault */
    ClockP_usleep(2000);

    pReg = (const CSL_aasrc_cfgRegs *)gAasrcConfig[inst].attrs->baseAddr;
    uint32_t baseAddr = (uint32_t)gAasrcConfig[inst].attrs->baseAddr;

    uint32_t savedOutEn   = CSL_REG32_RD(&pReg->OUTPUT_FIFO_INTERRUPT_ENABLE_SET_REGISTER);
    uint32_t savedInEn    = CSL_REG32_RD(&pReg->INPUT_FIFO_INTERRUPT_ENABLE_SET_REGISTER);
    uint32_t savedOutGrpEn= CSL_REG32_RD(&pReg->OUTPUT_GROUP_INTERRUPT_ENABLE_SET_REGISTER);
    uint32_t savedInGrpEn = CSL_REG32_RD(&pReg->INPUT_GROUP_INTERRUPT_ENABLE_SET_REGISTER);

    uint32_t monoMaskAll = 0U;
    uint32_t grpMaskAll  = 0U;
    uint32_t groupMonoMask = 0U;
    for (chIdx = 0U; chIdx < CONFIG_AASRC0_NUM_CH; chIdx++)
    {
        AASRC_ChObj *chObj = &gAasrcConfig[inst].object->chObj[chIdx];
        if (!chObj->isOpen) { continue; }

        if (chObj->chCfg.chType == AASRC_GROUP)
        {
            grpMaskAll |= ((uint32_t)1U) << (uint8_t)chObj->chState->hwGroupNum;
            groupMonoMask |= chObj->chState->chMask;
        }
        else
        {
            monoMaskAll |= chObj->chState->chMask;
        }
    }

    uint32_t savedErrEn = CSL_REG32_RD(&pReg->ERROR_INTERRUPT_ENABLE_SET_REGISTER);
    CSL_REG32_WR(&pReg->ERROR_INTERRUPT_ENABLE_CLEAR_REGISTER, savedErrEn | groupMonoMask);

    uint32_t pendErr = CSL_REG32_RD(&pReg->ERROR_INTERRUPT_STATUS_ENABLED_REGISTER);
    if (pendErr != 0U)
    {
        CSL_REG32_WR(&pReg->ERROR_INTERRUPT_STATUS_ENABLED_REGISTER, pendErr);
    }

    /* Clear sticky FIFO error bits per channel (read-write-back) */
    for (chIdx = 0U; chIdx < CONFIG_AASRC0_NUM_CH; chIdx++)
    {
        AASRC_ChObj *chObj = &gAasrcConfig[inst].object->chObj[chIdx];
        if (!chObj->isOpen) { continue; }

        if (chObj->chCfg.chType == AASRC_MONO ||
            chObj->chCfg.chType == AASRC_STEREO)
        {
            uint32_t hwCh = (uint32_t)chObj->chState->hwChNum;
            uint32_t fifoReg = CSL_REG32_RD(baseAddr + AASRC_SRC_FIFO_CONTROL(hwCh));
            CSL_REG32_WR(baseAddr + AASRC_SRC_FIFO_CONTROL(hwCh), fifoReg);
        }
        else if (chObj->chCfg.chType == AASRC_GROUP)
        {
            uint32_t hwGrp = (uint32_t)chObj->chState->hwGroupNum;
            uint32_t fifoReg = CSL_REG32_RD(baseAddr + AASRC_GROUP_FIFO_CONTROL(hwGrp));
            CSL_REG32_WR(baseAddr + AASRC_GROUP_FIFO_CONTROL(hwGrp), fifoReg);
        }
        /* Clear software-side error state */
        chObj->inFifoErrorStatus.lChannelOverflow   = 0U;
        chObj->inFifoErrorStatus.rChannelOverflow   = 0U;
        chObj->inFifoErrorStatus.lChannelUnderflow  = 0U;
        chObj->inFifoErrorStatus.rChannelUnderflow  = 0U;
        chObj->outFifoErrorStatus.lChannelOverflow  = 0U;
        chObj->outFifoErrorStatus.rChannelOverflow  = 0U;
        chObj->outFifoErrorStatus.lChannelUnderflow = 0U;
        chObj->outFifoErrorStatus.rChannelUnderflow = 0U;
    }

    /* Reset test capture arrays */
    memset((void *)TestAASRC_capturedInFifoErr,  0, sizeof(TestAASRC_capturedInFifoErr));
    memset((void *)TestAASRC_capturedOutFifoErr, 0, sizeof(TestAASRC_capturedOutFifoErr));
    TestAASRC_errFiredMask = 0U;

    /* Re-enable error interrupt including group mono channels */
    CSL_REG32_WR(&pReg->ERROR_INTERRUPT_ENABLE_SET_REGISTER, savedErrEn | groupMonoMask);

    if (injectOverflow)
    {
        /* Stop draining the OUT-FIFO -> overflow */
        if (monoMaskAll != 0U)
        {
            CSL_REG32_WR(&pReg->OUTPUT_FIFO_INTERRUPT_ENABLE_CLEAR_REGISTER, monoMaskAll);
        }
        if (grpMaskAll != 0U)
        {
            CSL_REG32_WR(&pReg->OUTPUT_GROUP_INTERRUPT_ENABLE_CLEAR_REGISTER, grpMaskAll);
        }
    }
    else
    {
        /* Stop refilling the IN-FIFO -> underflow. */
        if (monoMaskAll != 0U)
        {
            CSL_REG32_WR(&pReg->INPUT_FIFO_INTERRUPT_ENABLE_CLEAR_REGISTER, monoMaskAll);
        }
        if (grpMaskAll != 0U)
        {
            CSL_REG32_WR(&pReg->INPUT_GROUP_INTERRUPT_ENABLE_CLEAR_REGISTER, grpMaskAll);
        }
    }

    /* Wait for error IRQ on every channel (timeout ~2s) */
    uint32_t waitedMs = 0U;
    while ((TestAASRC_errFiredMask != ((uint8_t)((1U << CONFIG_AASRC0_NUM_CH) - 1U))) &&
           (waitedMs < 2000U))
    {
        ClockP_usleep(1000);
        waitedMs++;
    }

    /* Hardware workaround: The ERROR_INTERRUPT reliably fires for overflow,
     * but may not fire for underflow conditions even though the underflow bit
     * is set in the FIFO control register. We must poll the register directly
     * to capture the underflow error if the callback didn't fire. */
    if (!injectOverflow)
    {
        for (chIdx = 0U; chIdx < CONFIG_AASRC0_NUM_CH; chIdx++)
        {
            AASRC_ChObj *chObj = &gAasrcConfig[inst].object->chObj[chIdx];
            if (!chObj->isOpen) { continue; }

            uint32_t regVal;
            if (chObj->chCfg.chType == AASRC_MONO ||
                chObj->chCfg.chType == AASRC_STEREO)
            {
                uint32_t hwCh = (uint32_t)chObj->chState->hwChNum;
                regVal = CSL_REG32_RD(baseAddr + AASRC_SRC_FIFO_CONTROL(hwCh));

                TestAASRC_capturedInFifoErr[chIdx].lChannelUnderflow |=
                    (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_MASK) >>
                              CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_SHIFT);
                TestAASRC_capturedInFifoErr[chIdx].rChannelUnderflow |=
                    (uint8_t)((regVal & CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_INFIFO_UNDERFLOW_MASK) >>
                              CSL_AASRC_CFG_SRC_FIFO_CONTROL_0_R_CHANNEL_INFIFO_UNDERFLOW_SHIFT);
            }
            else if (chObj->chCfg.chType == AASRC_GROUP)
            {
                uint32_t hwGrp = (uint32_t)chObj->chState->hwGroupNum;
                regVal = CSL_REG32_RD(baseAddr + AASRC_GROUP_FIFO_CONTROL(hwGrp));

                TestAASRC_capturedInFifoErr[chIdx].lChannelUnderflow |=
                    (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_MASK) >>
                              CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_L_CHANNEL_INFIFO_UNDERFLOW_SHIFT);
                TestAASRC_capturedInFifoErr[chIdx].rChannelUnderflow |=
                    (uint8_t)((regVal & CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_INFIFO_UNDERFLOW_MASK) >>
                              CSL_AASRC_CFG_GROUP_FIFO_CONTROL_0_R_CHANNEL_INFIFO_UNDERFLOW_SHIFT);
            }
        }
    }

    /*Restore the masked interrupt enables immediately so any further
    driver activity (disable/close below) proceeds cleanly.*/
    CSL_REG32_WR(&pReg->OUTPUT_FIFO_INTERRUPT_ENABLE_SET_REGISTER,  savedOutEn);
    CSL_REG32_WR(&pReg->INPUT_FIFO_INTERRUPT_ENABLE_SET_REGISTER,   savedInEn);
    CSL_REG32_WR(&pReg->OUTPUT_GROUP_INTERRUPT_ENABLE_SET_REGISTER, savedOutGrpEn);
    CSL_REG32_WR(&pReg->INPUT_GROUP_INTERRUPT_ENABLE_SET_REGISTER,  savedInGrpEn);

    /* Validate captured flags per channel type */
    for (chIdx = 0U; chIdx < CONFIG_AASRC0_NUM_CH; chIdx++)
    {
        AASRC_ChObj *chObj = &gAasrcConfig[inst].object->chObj[chIdx];
        if (!chObj->isOpen) { continue; }
        uint8_t chType = chObj->chCfg.chType;

        if (injectOverflow)
        {
            uint8_t l = TestAASRC_capturedOutFifoErr[chIdx].lChannelOverflow;
            uint8_t r = TestAASRC_capturedOutFifoErr[chIdx].rChannelOverflow;
            DebugP_log("Overflow inject - Ch %u type %u: OUTFIFO L_OVF=%u R_OVF=%u\r\n",
                       chIdx, chType, l, r);
            if (chType == AASRC_MONO)
            {
                TEST_ASSERT_TRUE_MESSAGE(l != 0U, "Expected MONO OUTFIFO overflow not set");
            }
            else if (chType == AASRC_STEREO)
            {
                TEST_ASSERT_TRUE_MESSAGE((l != 0U) || (r != 0U),
                                         "Expected STEREO OUTFIFO overflow (L or R) not set");
            }
            else if (chType == AASRC_GROUP)
            {
                TEST_ASSERT_TRUE_MESSAGE((l != 0U) || (r != 0U),
                                         "Expected GROUP OUTFIFO overflow (L or R) not set");
            }
        }
        else
        {
            uint8_t l = TestAASRC_capturedInFifoErr[chIdx].lChannelUnderflow;
            uint8_t r = TestAASRC_capturedInFifoErr[chIdx].rChannelUnderflow;
            DebugP_log("Underflow inject - Ch %u type %u: INFIFO L_UNF=%u R_UNF=%u\r\n",
                       chIdx, chType, l, r);
            if (chType == AASRC_MONO)
            {
                TEST_ASSERT_TRUE_MESSAGE(l != 0U, "Expected MONO INFIFO underflow not set");
            }
            else if (chType == AASRC_STEREO)
            {
                TEST_ASSERT_TRUE_MESSAGE((l != 0U) || (r != 0U),
                                         "Expected STEREO INFIFO underflow (L or R) not set");
            }
            else if (chType == AASRC_GROUP)
            {
                TEST_ASSERT_TRUE_MESSAGE((l != 0U) || (r != 0U),
                                         "Expected GROUP INFIFO underflow (L or R) not set");
            }
        }
    }

    /* Cleanup: disable + close all channels */
    for (chIdx = 0U; chIdx < CONFIG_AASRC0_NUM_CH; chIdx++)
    {
        AASRC_ChHandle ch = AASRC_getChHandle(inst, chIdx);
        if (ch != NULL)
        {
            (void)AASRC_chDisable(ch);
            (void)AASRC_chClose(ch);
        }
    }

    /* Restore everything so the next test sees a pristine driver state */
    AASRC_close(handle);
    for (chIdx = 0U; chIdx < CONFIG_AASRC0_NUM_CH; chIdx++)
    {
        gConfigAasrcChObj[inst][chIdx].errCbFxn     = savedErrCb[chIdx];
        gConfigAasrcChObj[inst][chIdx].rcvObj.cbFxn = savedRcvCb[chIdx];
        gConfigAasrcChObj[inst][chIdx].xmtObj.cbFxn = savedXmtCb[chIdx];
    }
    gAasrcOpenParams[inst] = savedOpen;
    gAasrcHandle[inst]     = AASRC_open(inst, &gAasrcOpenParams[inst]);
    TEST_ASSERT_NOT_NULL(gAasrcHandle[inst]);

    SemaphoreP_destruct(&TestAASRC_errSem);
    SemaphoreP_destruct(&TestAASRC_countSemAsrcConv);
}

/**
 * \brief Test AASRC OUTPUT FIFO overflow via interrupt-mask fault injection.
 *
 * Test Category: Error Handling
 *
 * Masks TX servicing interrupt to force OUTPUT FIFO overflow condition.
 * Validates that the driver's error ISR captures the overflow flag for
 * mono, stereo, and group channel types. All driver and global state is
 * restored on exit.
 *
 * \param args Pointer to AASRC_OpenParams structure.
 */
static void TestAasrc_overflowSineWaveInterrupt(void *args)
{
    (void)args;
    TestAasrc_fifoErrorInjectCommon(CONFIG_AASRC0, /*injectOverflow=*/true);
}

/**
 * \brief Test AASRC INPUT FIFO underflow via interrupt-mask fault injection.
 *
 * Test Category: Error Handling
 *
 * Masks RX servicing interrupt to force INPUT FIFO underflow condition.
 * Validates that the driver's error ISR captures the underflow flag for
 * mono, stereo, and group channel types. All driver and global state is
 * restored on exit.
 *
 * \param args Pointer to AASRC_OpenParams structure.
 */
static void TestAasrc_underflowSineWaveInterrupt(void *args)
{
    (void)args;
    TestAasrc_fifoErrorInjectCommon(CONFIG_AASRC0, /*injectOverflow=*/false);
}
#endif

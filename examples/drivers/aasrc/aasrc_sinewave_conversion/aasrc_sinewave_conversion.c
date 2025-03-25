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

#include <stdio.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "aasrc_config.h"
#include <drivers/hw_include/cslr_aasrc.h>
#include <drivers/hw_include/cslr_aasrc_data_r0.h>
#include <drivers/hw_include/cslr_aasrc_data_r1.h>
#include "aasrc_data.h"
#include "FreeRTOS.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define MONO_CHANNEL_COUNT                       (1U)
#define STEREO_CHANNEL_COUNT                     (2U)
#define GROUP_CHANNEL_COUNT                      (5U)

#define MONO_INPUT_TRANSACTION_SAMPLE_COUNT      (1024U)
#define MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT     (1024U)

#define STEREO_INPUT_TRANSACTION_SAMPLE_COUNT    (MONO_INPUT_TRANSACTION_SAMPLE_COUNT * STEREO_CHANNEL_COUNT)
#define STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT   (MONO_INPUT_TRANSACTION_SAMPLE_COUNT * STEREO_CHANNEL_COUNT * 2)

#define GROUP_INPUT_TRANSACTION_SAMPLE_COUNT     (MONO_INPUT_TRANSACTION_SAMPLE_COUNT * GROUP_CHANNEL_COUNT)
#define GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT    (MONO_INPUT_TRANSACTION_SAMPLE_COUNT * GROUP_CHANNEL_COUNT)

#define INPUT_TRANSACTION_COUNT                  (8U)

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* Mono Buffer */
int32_t gAasrcRxMonoBuffer[MONO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
int32_t gAasrcTxMonoBuffer[MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

/* Stereo Buffer */
int32_t gAasrcRxStereoBuffer[STEREO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
int32_t gAasrcTxStereoBuffer[STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

/* Group(5) Buffer */
int32_t gAasrcRxGroupBuffer[GROUP_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
int32_t gAasrcTxGroupBuffer[GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

/* Transactions */
AASRC_Transaction txnRx[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};
AASRC_Transaction txnTx[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};

/* Channel MetaData */
AASRC_chMeta chMeta[CONFIG_AASRC_NUM_INSTANCES][CONFIG_AASRC0_NUM_CH] = {0};

SemaphoreP_Object gCountSemAsrcConv;


/* ========================================================================== */
/*                        Function Declarations                               */
/* ========================================================================== */
void aasrc_transactionInit(AASRC_ChHandle chHandle, uint8_t instNum, uint8_t chCount);
void aasrc_printOutput(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void aasrc_sinewave_conversion_main(void *args)
{
    int32_t status = SystemP_SUCCESS;
    AASRC_ChHandle      chHandle = NULL;
    AASRC_ChObj *chObj = NULL;

    uint8_t instanceCount = 0U;
    uint8_t channelCount = 0U;
    float  clkFrequency;

    SemaphoreP_constructCounting(&gCountSemAsrcConv, 0, CONFIG_AASRC0_NUM_CH);

    DebugP_log("[AASRC] Sin wave sampling frequency conversion example started\r\n");

    for(instanceCount = 0U; instanceCount< CONFIG_AASRC_NUM_INSTANCES; instanceCount++)
    {
        for(channelCount = 0U; channelCount< CONFIG_AASRC0_NUM_CH; channelCount++)
        {
            chHandle = AASRC_getChHandle(instanceCount, channelCount);
            if(chHandle != NULL)
            {
                chObj = (AASRC_ChObj *)(chHandle);
            }
            else
            {
                status = SystemP_FAILURE;
            }

            if(status == SystemP_SUCCESS)
            {
                /* Input Frequency */
                ClockP_usleep(5000);
                status += AASRC_GetClkZoneRxFrequency(chHandle, &clkFrequency);
                chMeta[instanceCount][channelCount].dataFormat = chObj->chCfg.inWordLen;

                DebugP_assertNoLog(status == SystemP_SUCCESS);
                DebugP_log("AASRC %u input clock zone %u freq = %0.8f KHz\r\n", instanceCount, channelCount, clkFrequency);

                /* Output Frequency */
                status += AASRC_GetClkZoneTxFrequency(chHandle, &clkFrequency);
                DebugP_assertNoLog(status == SystemP_SUCCESS);
                DebugP_log("AASRC %u output clock zone %u freq = %0.8f KHz\r\n", instanceCount, channelCount, clkFrequency);

                if( status == SystemP_SUCCESS)
                {
                    /* Init the transactions for all channel */
                    aasrc_transactionInit(chHandle, instanceCount, channelCount);

                    /* Enable the channel for starting conversion */
                    status += AASRC_chEnable(chHandle);
                }

            }
        }
    }
    DebugP_assert(status == SystemP_SUCCESS);

    while(SemaphoreP_getCount(&gCountSemAsrcConv) < CONFIG_AASRC0_NUM_CH)
    {
        /* Wait fot completion */
    }
    CacheP_wb(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALL);
    CacheP_wb(gAasrcTxStereoBuffer, sizeof(gAasrcTxStereoBuffer), CacheP_TYPE_ALL);
    CacheP_wb(gAasrcTxGroupBuffer, sizeof(gAasrcTxGroupBuffer), CacheP_TYPE_ALL);

    /* Close the channels */
    for (instanceCount = 0; instanceCount < CONFIG_AASRC_NUM_INSTANCES; instanceCount++)
    {
        for (channelCount = 0; channelCount < CONFIG_AASRC0_NUM_CH; channelCount++)
        {
            chHandle = AASRC_getChHandle(instanceCount, channelCount);
            status = AASRC_chClose(chHandle);
        }
    }

    /* Print the output */
    aasrc_printOutput();

}

void aasrc_transactionInit(AASRC_ChHandle chHandle, uint8_t instNum, uint8_t chCount)
{
    uint16_t count;
    AASRC_ChObj *chObj = (AASRC_ChObj *)(chHandle);
    uint8_t chType = chObj->chCfg.chType;

    switch(chType)
    {
        case AASRC_MONO:

            /* Init Input and Output Buffer */
            strncpy(chMeta[instNum][chCount].metaInfo,"MONO CHANNEL", sizeof(chMeta[instNum][chCount].metaInfo));
            chMeta[instNum][chCount].rxSamplingFreq = INPUT_SIGNAL_FREQUENCY;
            chMeta[instNum][chCount].monoChCount = 1;
            chMeta[instNum][chCount].rxBufPtr = (uint32_t *)&gAasrcRxMonoBuffer[0];
            chMeta[instNum][chCount].txBufPtr = (uint32_t *)&gAasrcTxMonoBuffer[0];
            chMeta[instNum][chCount].rxSampleCount = MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
            chMeta[instNum][chCount].txSampleCount = MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< MONO_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcRxMonoBuffer[count] = (int32_t)aasrc_monoInput[count];
            }

            for(count = 0U; count< MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcTxMonoBuffer[count] = 0U;
            }

            CacheP_wb(gAasrcRxMonoBuffer, sizeof(gAasrcRxMonoBuffer), CacheP_TYPE_ALLD);
            CacheP_wb(gAasrcTxMonoBuffer, sizeof(gAasrcTxMonoBuffer), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            txnRx[instNum][chCount].buf = (void*) &gAasrcRxMonoBuffer[0];
            txnRx[instNum][chCount].sampleCount = MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &txnRx[instNum][chCount] );

            txnTx[instNum][chCount].buf = (void*) &gAasrcTxMonoBuffer[0];
            txnTx[instNum][chCount].sampleCount = MONO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &txnTx[instNum][chCount] );
            break;

        case AASRC_STEREO:

            /* Init Input and Output Buffer */
            strncpy(chMeta[instNum][chCount].metaInfo,"STEREO CHANNEL", sizeof(chMeta[instNum][chCount].metaInfo));
            chMeta[instNum][chCount].rxSamplingFreq = INPUT_SIGNAL_FREQUENCY;
            chMeta[instNum][chCount].monoChCount = 2;
            chMeta[instNum][chCount].rxBufPtr = (uint32_t *)&gAasrcRxStereoBuffer[0];
            chMeta[instNum][chCount].txBufPtr = (uint32_t *)&gAasrcTxStereoBuffer[0];
            chMeta[instNum][chCount].rxSampleCount = STEREO_INPUT_TRANSACTION_SAMPLE_COUNT;
            chMeta[instNum][chCount].txSampleCount = STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< STEREO_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcRxStereoBuffer[count] = (int32_t)aasrc_stereoInput[count];
            }

            for(count = 0U; count< STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcTxStereoBuffer[count] = 0U;
            }

            CacheP_wb(gAasrcRxStereoBuffer, sizeof(gAasrcRxStereoBuffer), CacheP_TYPE_ALLD);
            CacheP_wb(gAasrcTxStereoBuffer, sizeof(gAasrcTxStereoBuffer), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            txnRx[instNum][chCount].buf = (void*) &gAasrcRxStereoBuffer[0];
            txnRx[instNum][chCount].sampleCount = STEREO_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &txnRx[instNum][chCount] );

            txnTx[instNum][chCount].buf = (void*) &gAasrcTxStereoBuffer[0];
            txnTx[instNum][chCount].sampleCount = STEREO_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &txnTx[instNum][chCount] );
            break;

        case AASRC_GROUP:

            /* Init Input and Output Buffer */
            strncpy(chMeta[instNum][chCount].metaInfo,"GROUP CHANNEL", sizeof(chMeta[instNum][chCount].metaInfo));
            chMeta[instNum][chCount].rxSamplingFreq = INPUT_SIGNAL_FREQUENCY;
            chMeta[instNum][chCount].monoChCount = GROUP_CHANNEL_COUNT;
            chMeta[instNum][chCount].rxBufPtr = (uint32_t *)&gAasrcRxGroupBuffer[0];
            chMeta[instNum][chCount].txBufPtr = (uint32_t *)&gAasrcTxGroupBuffer[0];
            chMeta[instNum][chCount].rxSampleCount = GROUP_INPUT_TRANSACTION_SAMPLE_COUNT;
            chMeta[instNum][chCount].txSampleCount = GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT;

            for(count = 0U; count< GROUP_INPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcRxGroupBuffer[count] = (int32_t)aasrc_groupInput[count];
            }

            for(count = 0U; count< GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT; count++)
            {
                gAasrcTxGroupBuffer[count] = 0U;
            }

            CacheP_wb(gAasrcRxGroupBuffer, sizeof(gAasrcRxGroupBuffer), CacheP_TYPE_ALLD);
            CacheP_wb(gAasrcTxGroupBuffer, sizeof(gAasrcTxGroupBuffer), CacheP_TYPE_ALLD);

            /* Queue the rxTransaction  and txTransaction */
            txnRx[instNum][chCount].buf = (void*) &gAasrcRxGroupBuffer[0];
            txnRx[instNum][chCount].sampleCount = GROUP_INPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionRx( chHandle, &txnRx[instNum][chCount] );

            txnTx[instNum][chCount].buf = (void*) &gAasrcTxGroupBuffer[0];
            txnTx[instNum][chCount].sampleCount = GROUP_OUTPUT_TRANSACTION_SAMPLE_COUNT;
            AASRC_queueTransactionTx( chHandle, &txnTx[instNum][chCount] );
            break;

        default:
            break;
    }
}

void aasrc_printOutput(void)
{
    uint32_t chCount = 0U;
    uint8_t instanceCount = 0U;
    uint8_t monoChCount = 0U;
    uint32_t sampleCount = 0U;
    uint8_t monoChannelTot = 0U;

    for(instanceCount = 0U; instanceCount< CONFIG_AASRC_NUM_INSTANCES; instanceCount++)
    {
        for(chCount = 0U; chCount < CONFIG_AASRC0_NUM_CH; chCount++)
        {
            monoChannelTot = chMeta[instanceCount][chCount].monoChCount;

            for(monoChCount = 0U; monoChCount < monoChannelTot; monoChCount++)
            {
                DebugP_log("Data Start\r\n");
                DebugP_log("%s : %d \r\n", chMeta[instanceCount][chCount].metaInfo, monoChCount);
                DebugP_log("Signal Frequency: %0.8f KHz \r\n", chMeta[instanceCount][chCount].rxSamplingFreq);
                DebugP_log("Data Format: %d Bits \r\n", chMeta[instanceCount][chCount].dataFormat);

                DebugP_log("Input Buffer Sending\r\n");


                for (sampleCount = 0; sampleCount < chMeta[instanceCount][chCount].rxSampleCount; sampleCount+=monoChannelTot)
                {
                    DebugP_log("%x", chMeta[instanceCount][chCount].rxBufPtr[sampleCount]);
                    DebugP_log("\r\n");
                }

                DebugP_log("Input Buffer Over\r\n");

                DebugP_log("Output Buffer Sending\r\n");

                for (sampleCount = 0; sampleCount < chMeta[instanceCount][chCount].txSampleCount; sampleCount+=monoChannelTot)
                {
                    DebugP_log("%x", chMeta[instanceCount][chCount].txBufPtr[sampleCount]);
                    DebugP_log("\r\n");
                }

                DebugP_log("Output Buffer Over\r\n");
                DebugP_log("Data End\r\n");
            }
        }
    }
    DebugP_log("All Over\r\n");
}

/* User Defined Callbacks */

void aasrc_rxcb (AASRC_ChHandle chHandle,
                 AASRC_Transaction *transaction)
{
}

void aasrc_txcb (AASRC_ChHandle chHandle,
                 AASRC_Transaction *transaction)
{
    SemaphoreP_post(&gCountSemAsrcConv);
    AASRC_chDisable(chHandle);
}

void aasrc_ch_error_handler(AASRC_ChHandle chHandle,
                            AASRC_Transaction *transactionRx,
                            AASRC_Transaction *transactionTx)
{
}

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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sigchain_dsp_mcasp.h"
#include "sigchain_platform.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* semaphore for audio processing */
SemaphoreP_Object semTx;
SemaphoreP_Object semRx;

/* semaphore used for packet processing */
SemaphoreP_Object semCmdPkt;

/* mcasp process task */
StackType_t gMcaspProcessTaskStack[MCASP_PROCESS_TASK_STACKSIZE];
StaticTask_t gMcaspProcessTaskObj;
TaskHandle_t gMcaspProcessTask;

uint32_t gMcaspTxCnt = 0;
uint32_t gMcaspRxCnt = 0;
uint32_t gMcaspErrCnt = 0;
uint32_t total_frames_sent = 0;

volatile int rxFrameIndex = (NUM_BUFS - 1);
volatile int txFrameIndex = (NUM_BUFS - 1);

uint8_t rxbuf[NUM_BUFS][DMA_RX_BUF_SIZE]
    __attribute__((section("sigchain_mcasp_buffer"), aligned(BUFALIGN)));
uint8_t txbuf[NUM_BUFS][DMA_TX_BUF_SIZE]
    __attribute__((section("sigchain_mcasp_buffer"), aligned(BUFALIGN)));

uint8_t sigBuf[SIGCHAIN_BUF_SIZE]
    __attribute__((section("sigchain_mcasp_buffer"), aligned(BUFALIGN)));

int32_t chPlotData[BUFSIZE_PER_CHANNEL];
uint32_t gNewChnlData = 0;
uint32_t gPlotChnl = 0;
uint32_t gPlotCaptureMode = 0;

MCASP_Transaction rxFrame[NUM_BUFS];
MCASP_Transaction txFrame[NUM_BUFS];

/* temporary buffer for tisp */
uint8_t data_buffer[DMA_RX_BUF_SIZE];
void *gSpGraph = NULL;
RtInfo gRtInfo;

void SigchainDSP_Cmdproc_createIdleTask();

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void mcasp1_rxcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    gMcaspRxCnt++;
    SemaphoreP_post(&semRx);
}

void mcasp1_txcb(MCASP_Handle handle, MCASP_Transaction *transaction)
{
    gMcaspTxCnt++;
    SemaphoreP_post(&semTx);
}

uint32_t graphError = 0;

/* by default, 8ch in and 8ch out from signal chain */
uint32_t srcStride = DAC_STRIDE;
uint8_t chmap[8] = {0, 1, 2, 3, 4, 5, 6, 7};

void SigchainDSP_McASP_copyChannelSample(int32_t *restrict pBuf,
                                         uint32_t stride)
{
    uint32_t i;

    for (i = 0; i < AUDIO_BLOCK_SIZE; i++)
    {
        chPlotData[i] = pBuf[stride * i + gPlotChnl];
    }
    gNewChnlData = BUFSIZE_PER_CHANNEL;
}

void SigchainDSP_McASP_copyAudioSamples8Ch(int32_t *restrict pSigBuf,
                                           int32_t *restrict pDacBuf)
{
    uint32_t i, j = 0;
    int32_t *tx = pDacBuf;
    int32_t *rx = pSigBuf;

    for (i = 0; i < AUDIO_BLOCK_SIZE; i++)
    {
        j = 0;
        tx[DAC_STRIDE * i + 0] = rx[srcStride * i + chmap[j++]];
        tx[DAC_STRIDE * i + 1] = rx[srcStride * i + chmap[j++]];

        tx[DAC_STRIDE * i + 2] = rx[srcStride * i + chmap[j++]];
        tx[DAC_STRIDE * i + 3] = rx[srcStride * i + chmap[j++]];

        tx[DAC_STRIDE * i + 4] = rx[srcStride * i + chmap[j++]];
        tx[DAC_STRIDE * i + 5] = rx[srcStride * i + chmap[j++]];

        tx[DAC_STRIDE * i + 6] = rx[srcStride * i + chmap[j++]];
        tx[DAC_STRIDE * i + 7] = rx[srcStride * i + chmap[j++]];
    }
}

void SigchainDSP_McASP_copyAudioSamples8Ch12Ch(int32_t *restrict pIn,
                                               int32_t *restrict pOut)
{
    uint32_t i, j = 0;
    int32_t *tx = pIn;
    int32_t *rx = pOut;
    uint32_t stride = 12;

    for (i = 0; i < AUDIO_BLOCK_SIZE; i++)
    {
        j = 0;
        rx[stride * i + 0] = tx[DAC_STRIDE * i + j];
        rx[stride * i + 8] = tx[DAC_STRIDE * i + j++];

        rx[stride * i + 1] = tx[DAC_STRIDE * i + j];
        rx[stride * i + 9] = tx[DAC_STRIDE * i + j++];

        rx[stride * i + 2] = rx[stride * i + j];
        rx[stride * i + 10] = tx[DAC_STRIDE * i + j++];

        rx[stride * i + 3] = tx[DAC_STRIDE * i + j];
        rx[stride * i + 11] = tx[DAC_STRIDE * i + j++];

        rx[stride * i + 4] = tx[DAC_STRIDE * i + j++];
        rx[stride * i + 5] = tx[DAC_STRIDE * i + j++];

        rx[stride * i + 6] = tx[DAC_STRIDE * i + j++];
        rx[stride * i + 7] = tx[DAC_STRIDE * i + j++];
    }
}

void SigchainDSP_McASP_processAudioSamples()
{
    MCASP_Handle mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);
    uint8_t *pTxBuf;
    uint8_t *pRxBuf;

    pTxBuf = &txbuf[txFrameIndex][0];
    pRxBuf = &rxbuf[rxFrameIndex][0];

    CacheP_inv((void *) pRxBuf, DMA_RX_BUF_SIZE, CacheP_TYPE_ALL);

    if (gSpGraph != NULL)
    {
        uint32_t start_cycle;
        int32_t *pIn = (int32_t *) pRxBuf;
        int32_t *pOut = (int32_t *) pTxBuf;

        if (srcStride == DAC_STRIDE)
        {
            start_cycle = CycleCounterP_getCount32();
            execute_graph(gSpGraph, pIn, (int32_t *) sigBuf);
            SigchainDSP_McASP_copyAudioSamples8Ch((int32_t *) sigBuf, pOut);
            gRtInfo.cycleCount = CycleCounterP_getCount32() - start_cycle;
        }
        else
        {
            start_cycle = CycleCounterP_getCount32();
            execute_graph(gSpGraph, pIn, (int32_t *) sigBuf);
            gRtInfo.cycleCount = CycleCounterP_getCount32() - start_cycle;
            SigchainDSP_McASP_copyAudioSamples8Ch((int32_t *) sigBuf, pOut);
        }

        if (gPlotCaptureMode == 1)
        {
            SigchainDSP_McASP_copyChannelSample(pOut, srcStride);
        }
    }
    else
    {
        graphError++;
        memset((void *) pTxBuf, 0x00, DMA_TX_BUF_SIZE);
    }

    CacheP_wb((void *) pTxBuf, DMA_TX_BUF_SIZE, CacheP_TYPE_ALL);

    MCASP_submitTx(mcaspHandle, &txFrame[txFrameIndex]);
    txFrameIndex = ((txFrameIndex + 1) % NUM_BUFS);

    rxFrameIndex = ((rxFrameIndex + 1) % NUM_BUFS);
    MCASP_submitRx(mcaspHandle, &rxFrame[rxFrameIndex]);

    total_frames_sent++;
}

void SigchainDSP_McASP_audioStart()
{
    int status;
    MCASP_Handle mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    /* Trigger McASP receive operation */
    status = MCASP_startTransferRx(mcaspHandle);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("MCASP_startTransferRx failed, error 0x%X\r\n", status);
    }

    /* Trigger McASP transmit operation */
    status = MCASP_startTransferTx(mcaspHandle);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("MCASP_startTransferTx failed, error 0x%X\r\n", status);
    }
}

void SigchainDSP_McASP_setup()
{
    MCASP_Handle mcaspHandle;

#ifndef SIG_CHAIN_LINUX_HOST
    /* Open MCASP driver after enabling the HCLK */
    mcaspHandle = MCASP_open(0, &gMcaspOpenParams[0]);
    if (NULL == mcaspHandle)
    {
        DebugP_logError("MCASP open failed for instance 0 !!!\r\n");
        DebugP_assert(false);
    }
#else
    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);
#endif

    /* Overwrite the Audio block Buffer Size */
    MCASP_setTxTxnCount(mcaspHandle, DMA_TX_BUF_SIZE / DMA_AUDIO_SAMPLE_SIZE);
    MCASP_setRxTxnCount(mcaspHandle, DMA_RX_BUF_SIZE / DMA_AUDIO_SAMPLE_SIZE);
}

void SigchainDSP_McASP_prime()
{
    int32_t count = 0;

    MCASP_Handle mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    for (count = 0; count < NUM_BUFS; count++)
    {
        /* Issue the first & second empty buffers to the input stream */
        memset((uint8_t *) &rxbuf[count][0], 0x00, DMA_RX_BUF_SIZE);

        /* RX frame processing */
        rxFrame[count].buf = (void *) &rxbuf[count][0];
        rxFrame[count].count = DMA_RX_BUF_SIZE / 4;
        rxFrame[count].timeout = 0xFFFFFF;

        /* Submit McASP packet for Rx */
        MCASP_submitRx(mcaspHandle, &rxFrame[count]);
    }

    for (count = 0; count < (NUM_BUFS); count++)
    {
        memset((uint8_t *) &txbuf[count][0], 0x00, DMA_TX_BUF_SIZE);

        /* TX frame processing */
        txFrame[count].buf = (void *) &txbuf[count][0];
        txFrame[count].count = DMA_TX_BUF_SIZE / 4;
        txFrame[count].timeout = 0xFFFFFF;

        /* Submit McASP packet for Tx */
        MCASP_submitTx(mcaspHandle, &txFrame[count]);
    }
}

void SigchainDSP_McASP_process(void *arg)
{
    int32_t done = 0;

    /* create semephore object for MCASP RX callback */
    SemaphoreP_constructCounting(&semTx, 0, NUM_BUFS);
    SemaphoreP_constructCounting(&semRx, 0, NUM_BUFS);

    CycleCounterP_reset();

    SigchainDSP_McASP_setup();
    SigchainDSP_McASP_prime();
    SigchainDSP_McASP_audioStart();

    DebugP_log("DSP : num of buffers = %d\r\n", NUM_BUFS);
    DebugP_log("DSP : DMA size = %d\r\n", DMA_TX_BUF_SIZE);

    gSpGraph = create_graph((int32_t *) data_buffer, &srcStride);

    while (!done)
    {
        /* Wait for MCASP RX callback */
        SemaphoreP_pend(&semTx, SystemP_WAIT_FOREVER);
        SemaphoreP_pend(&semRx, SystemP_WAIT_FOREVER);

        SigchainDSP_McASP_processAudioSamples();

    } /* While done loop*/

    vTaskDelete(NULL);
}

void SigchainDSP_McASP_setupAudioIO()
{
    gMcaspProcessTask = xTaskCreateStatic(
        SigchainDSP_McASP_process, "McASP_Process",
        MCASP_PROCESS_TASK_STACKSIZE, NULL, MCASP_PROCESS_TASK_PRI,
        gMcaspProcessTaskStack, &gMcaspProcessTaskObj);
    configASSERT(gMcaspProcessTask != NULL);
}

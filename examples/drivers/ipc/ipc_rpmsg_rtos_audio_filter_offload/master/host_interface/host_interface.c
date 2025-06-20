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

 /**
 * @file host_interface.c
 * @brief Host communication interface for master core to host using TCP.
 *
 * This file implements the functionality for transmitting data
 * and logs from the master core to the host system over a TCP connection.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "lwip/api.h"
#include "enet_apputils.h"
#include "network/network_tcpserver.h"
#include "host_interface.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct __attribute__((packed)) {
    uint32_t data_buffer;
    uint32_t params_buffer;
    uint32_t data_size;
    uint32_t params_size;
    uint32_t graph_id;
} AppIPC_DspMsg;

typedef struct __attribute__((packed)) {
    float   dspLoad;
    int32_t lengthZeroRFFT;
    float   gain_treble;
} AppIPC_DspParam;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

int8_t send_InBuffer[APP_HOSTIF_FLUSH_BUFFER_SIZE];
int8_t send_OutBuffer[APP_HOSTIF_FLUSH_BUFFER_SIZE];
uint32_t log_Head = 0, log_Tail = 0;
AppHostIf_LogEntry log_Queue[APP_HOSTIF_LOG_QUEUE_SIZE];
AppHostIf_LogSummaryParams logSummaryParams;
uint32_t inDataOffset = 0;
uint32_t outDataOffset = 0;
static const char FILTER_TOGGLE_COMMAND[] = "SET FFT FILTER";
extern TCP_NetconnSockets tcpSockets;
extern int16_t gInputAudioBuf[APP_HOSTIF_BUFFER_SIZE_IN_SAMPLES];
extern int16_t gOutputAudioBuf[APP_HOSTIF_BUFFER_SIZE_IN_SAMPLES];
extern AppIPC_DspMsg gDspMsg;
extern AppIPC_DspParam gDspParams;
extern SemaphoreP_Object gSemIPCLog;
extern SemaphoreP_Object gSemIPCLogAvail;

/* ========================================================================== */
/*                         Function Declaration                               */
/* ========================================================================== */

void AppHostIf_flushLogBuffer(void *arg);
void AppHostIf_enqueInData(const char *tag, uint32_t dataSize);
void AppHostIf_enqueOutData(const char *tag, uint32_t dataSize);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Log Input Audio */
void AppHostIf_logInputAudio(void *arg)
{
    uint32_t inQueueDataSize = APP_HOSTIF_QUEUE_BUFFER_SIZE;
    char tag[] = "INPT";
    AppHostIf_enqueInData(&tag[0], inQueueDataSize);
}

/* Log Output Audio */
void AppHostIf_logOutputAudio(void *arg)
{
    uint32_t outQueueDataSize = APP_HOSTIF_QUEUE_BUFFER_SIZE;
    char tag[] = "OUTP";
    AppHostIf_enqueOutData(&tag[0], outQueueDataSize);
}

/* Flush Input Buffer Data to Client */
void AppHostIf_flushInputBuffer(void *arg)
{
	if(tcpSockets.pClientSocketInp >= 0)
	{
		if (inDataOffset > 0)
        {
            err_t err = netconn_write(tcpSockets.pClientSocketInp, &send_InBuffer[0], inDataOffset, NETCONN_COPY);

            if (err < ERR_OK)
            {
                DebugP_log("Unable to flush Input Buffer: errno %d\r\n", err);
            }

			inDataOffset = 0;
		}
	}
	else
    {
		inDataOffset = 0;
    }
}

/* Flush Output Buffer Data to Client */
void AppHostIf_flushOutputBuffer(void *arg)
{
	if(tcpSockets.pClientSocketOut >= 0)
	{
		if (outDataOffset > 0)
        {
            err_t err = netconn_write(tcpSockets.pClientSocketOut, &send_OutBuffer[0], outDataOffset, NETCONN_COPY);

            if (err < ERR_OK)
            {
                DebugP_log("Unable to flush Output Buffer: errno %d\r\n", err);
            }

			outDataOffset = 0;
		}
	}
	else
    {
		outDataOffset = 0;
    }
}

/* Queue Input Frame of Audio Data into input send buffer */
void AppHostIf_enqueInData(const char *tag, uint32_t dataSize)
{
    uint32_t tagSize = strlen(tag);
    uint32_t index = 0U;
    int16_t *srcPtr , *destPtr = NULL;

    if(inDataOffset + tagSize + dataSize >= APP_HOSTIF_FLUSH_BUFFER_SIZE)
    {
        AppHostIf_flushInputBuffer(NULL);
    }

    memcpy(&send_InBuffer[inDataOffset], &tag[0], tagSize);
    inDataOffset +=  tagSize;

    for(index = 0U; index < APP_HOSTIF_NUMBER_OF_FRAMES; index++)
    {
        srcPtr = (int16_t *)( (uint32_t)(&gInputAudioBuf[0]) + \
                ( ((uint32_t)index * APP_HOSTIF_PER_FRAME_SIZE_IN_BYTES) + (APP_HOSTIF_CURR_CHANNEL * APP_HOSTIF_PER_CHANNEL_SAMPLE_SIZE_IN_BYTES) ) );
        destPtr = (int16_t *)( ((uint32_t )(&send_InBuffer[0])) + \
                inDataOffset + (APP_HOSTIF_PER_CHANNEL_SAMPLE_SIZE_IN_BYTES * index) );

        *destPtr = *srcPtr;
    }

    inDataOffset += dataSize;
}

/* Queue Output Frame of Audio Data into output send buffer */
void AppHostIf_enqueOutData(const char *tag, uint32_t dataSize)
{
    uint32_t tagSize = strlen(tag);
    uint32_t index = 0U;
    int16_t *srcPtr , *destPtr = NULL;

    if(outDataOffset + tagSize + dataSize >= APP_HOSTIF_FLUSH_BUFFER_SIZE)
    {
        AppHostIf_flushOutputBuffer(NULL);
    }

    memcpy(&send_OutBuffer[outDataOffset], &tag[0], tagSize);
    outDataOffset += tagSize;

    for(index = 0U; index < APP_HOSTIF_NUMBER_OF_FRAMES; index++)
    {
        srcPtr = (int16_t *)( (uint32_t)(&gOutputAudioBuf[0]) +  ( ((uint32_t)index * APP_HOSTIF_PER_FRAME_SIZE_IN_BYTES) + (APP_HOSTIF_CURR_CHANNEL * APP_HOSTIF_PER_CHANNEL_SAMPLE_SIZE_IN_BYTES) ) );
        destPtr = (int16_t *)( ((uint32_t )(&send_OutBuffer[0])) + outDataOffset + (APP_HOSTIF_PER_CHANNEL_SAMPLE_SIZE_IN_BYTES * index) );

        *destPtr = *srcPtr;
    }

    outDataOffset += dataSize;
}

/* Queue logs into log buffer */
void AppHostIf_enqueueframeLog(const char *msg)
{
    SemaphoreP_pend(&gSemIPCLog, SystemP_WAIT_FOREVER);
	if(tcpSockets.pClientSocketLog >= 0) {
		snprintf(log_Queue[log_Tail].log, sizeof(log_Queue[log_Tail].log), "%s", msg);
		log_Tail = (log_Tail + 1) % APP_HOSTIF_LOG_QUEUE_SIZE;
	}
    SemaphoreP_post(&gSemIPCLogAvail);
    SemaphoreP_post(&gSemIPCLog);
}

/* Format & queue the metrics log into log buffer */
void AppHostIf_logFrameMetrics(AppHostIf_LogSummaryParams *logSummaryParams)
{
	char logbuf[256];

    snprintf(logbuf, sizeof(logbuf),
            "Frame %d: AvgAmp=%.2f, Latency=%.2fms, Mode=%s CPULoad=%.1f%% DSPLoad=%.1f%%", \
            logSummaryParams->frames, logSummaryParams->amp, logSummaryParams->latency, \
            "DSP", logSummaryParams->cpu, logSummaryParams->dsp);

    AppHostIf_enqueueframeLog(logbuf);
}

/* Flush the log to host */
void AppHostIf_flushLogBuffer(void *arg)
{
	if(tcpSockets.pClientSocketLog >= 0)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "%s\n", log_Queue[log_Head].log);
        size_t msg_len = strlen(msg);

        log_Head = (log_Head + 1) % APP_HOSTIF_LOG_QUEUE_SIZE;

        err_t err = netconn_write(tcpSockets.pClientSocketLog, &msg[0], msg_len, NETCONN_COPY);

        if (err < ERR_OK)
        {
            DebugP_log("Unable to flush Log Buffer: errno %d\r\n", err);
        }
    }
}

/* Format and queue the summary logs to logs buffer */
void AppHostIf_logSummary(AppHostIf_LogSummaryParams *logSummaryParams)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "[Live Summary] Frames: %d", logSummaryParams->frames);
    AppHostIf_enqueueframeLog(buf);
    snprintf(buf, sizeof(buf), "[Live Summary] Latency (ms): Min: %.2f, Max: %.2f, Avg: %.2f",
    logSummaryParams->minLatency, logSummaryParams->maxLatency, logSummaryParams->totalLatency / logSummaryParams->frames);
    AppHostIf_enqueueframeLog(buf);
    snprintf(buf, sizeof(buf), "[Live Summary] Amp: Min: %.2f, Max: %.2f, Avg: %.2f",
    logSummaryParams->minAmp, logSummaryParams->maxAmp, logSummaryParams->totalAmp / logSummaryParams->frames);
    AppHostIf_enqueueframeLog(buf);
    snprintf(buf, sizeof(buf), "[Live Summary] CPU Load (%%): Min: %.1f, Max: %.1f, Avg: %.1f",
    logSummaryParams->minCpu, logSummaryParams->maxCpu, logSummaryParams->totalCpu / logSummaryParams->frames);
    AppHostIf_enqueueframeLog(buf);
    snprintf(buf, sizeof(buf), "[Live Summary] DSP Load (%%): Min: %.1f, Max: %.1f, Avg: %.1f",
    logSummaryParams->minDsp, logSummaryParams->maxDsp, logSummaryParams->totalDsp / logSummaryParams->frames);
    AppHostIf_enqueueframeLog(buf);
}

/* Update the summary metrics */
void AppHostIf_updateMetrics(AppHostIf_LogSummaryParams *logSummaryParams)
{
    logSummaryParams->frames++;

    /* Update Latency Metrics */
    logSummaryParams->totalLatency += logSummaryParams->latency;

    if (logSummaryParams->latency < logSummaryParams->minLatency)
    {
        logSummaryParams->minLatency = logSummaryParams->latency;
    }
    if (logSummaryParams->latency > logSummaryParams->maxLatency)
    {
        logSummaryParams->maxLatency = logSummaryParams->latency;
    }

    /* Update Amplitude Metrics */
    logSummaryParams->totalAmp += logSummaryParams->amp;
    if (logSummaryParams->amp < logSummaryParams->minAmp)
    {
        logSummaryParams->minAmp = logSummaryParams->amp;
    }
    if (logSummaryParams->amp > logSummaryParams->maxAmp)
    {
        logSummaryParams->maxAmp = logSummaryParams->amp;
    }

    /* Update CPU Load Metrics */
    logSummaryParams->totalCpu += logSummaryParams->cpu;
    if (logSummaryParams->cpu < logSummaryParams->minCpu)
    {
        logSummaryParams->minCpu = logSummaryParams->cpu;
    }
    if (logSummaryParams->cpu > logSummaryParams->maxCpu)
    {
        logSummaryParams->maxCpu = logSummaryParams->cpu;
    }

    /* Update DSP Load Metrics */
    logSummaryParams->totalDsp += logSummaryParams->dsp;
    if (logSummaryParams->dsp < logSummaryParams->minDsp)
    {
        logSummaryParams->minDsp = logSummaryParams->dsp;
    }
    if (logSummaryParams->dsp > logSummaryParams->maxDsp)
    {
        logSummaryParams->maxDsp = logSummaryParams->dsp;
    }
}

/* Task for sending logs to host utility */
void AppHostIf_logTask(void *arg)
{
    while (1)
    {
        /* Check the log is available or not */
        /* If available flush the log or else wait till becomes available */
        SemaphoreP_pend(&gSemIPCLog, SystemP_WAIT_FOREVER);

        /* Log is available to flush */
        while (log_Head == log_Tail)
        {
            SemaphoreP_post(&gSemIPCLog);
            SemaphoreP_pend(&gSemIPCLogAvail, SystemP_WAIT_FOREVER);
        }
        AppHostIf_flushLogBuffer(NULL);
        SemaphoreP_post(&gSemIPCLog);
    }
}

/* Task for listening for commands from host utility */
void AppHostIf_cmdTask(void *arg)
{
    err_t err;
    struct netbuf *buf;
    void *data;
    u16_t len;
    uint8_t filterValue = 0U;

    uint8_t cmdLen = strlen(&FILTER_TOGGLE_COMMAND[0]);

    while(1)
    {
        if(tcpSockets.pClientSocketCmd >= 0)
        {
            err = netconn_recv(tcpSockets.pClientSocketCmd, &buf);
            if (err != ERR_OK)
            {
                printf("tcpecho: netconn_read: error \"%s\"\r\n", lwip_strerr(err));
            }

            do
            {
                netbuf_data(buf, &data, &len);

                /* Peek at the last character, it's the filter value! */
                /* Expected format: "SET FFT FILTER 0" or "SET FFT FILTER 1" */

                if(memcmp(data, FILTER_TOGGLE_COMMAND, cmdLen) == 0)
                {
                    filterValue = (((uint8_t*)data)[cmdLen + 1]);
                    if(filterValue == APP_HOSTIF_FILTER_RESET)
                    {
                        gDspParams.lengthZeroRFFT = APP_HOSTIF_FILTER_DISABLE;
                    }
                    else if(filterValue == APP_HOSTIF_FILTER_SET)
                    {
                        gDspParams.lengthZeroRFFT = APP_HOSTIF_FILTER_ENABLE;
                    }
                }
                else
                {
                    DebugP_log("Unknown field \n");
                }
            } while (netbuf_next(buf) >= 0);
        }
    }
}

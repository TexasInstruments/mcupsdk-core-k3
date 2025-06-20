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

#ifndef _HOST_INTERFACE_H_
#define _HOST_INTERFACE_H_


/* ========================================================================== */
/*                              Macros                                        */
/* ========================================================================== */

#define APP_HOSTIF_NUMBER_OF_CHANNELS_PER_FRAME                (8U)
#define APP_HOSTIF_PER_CHANNEL_SAMPLE_SIZE_IN_BYTES            (2U)
#define APP_HOSTIF_NUMBER_OF_FRAMES                            (256U)
#define APP_HOSTIF_PER_FRAME_SIZE_IN_BYTES                     ( (APP_HOSTIF_NUMBER_OF_CHANNELS_PER_FRAME) * (APP_HOSTIF_PER_CHANNEL_SAMPLE_SIZE_IN_BYTES) )
#define APP_HOSTIF_DATA_BUFFER_SIZE_IN_BYTES                   ( (APP_HOSTIF_NUMBER_OF_FRAMES) * (APP_HOSTIF_PER_FRAME_SIZE_IN_BYTES) )
#define APP_HOSTIF_BUFFER_SIZE_IN_SAMPLES                      ( (APP_HOSTIF_NUMBER_OF_FRAMES) * (APP_HOSTIF_NUMBER_OF_CHANNELS_PER_FRAME) )

#define APP_HOSTIF_FLUSH_BUFFER_SIZE                           (8192U)
#define APP_HOSTIF_QUEUE_BUFFER_SIZE                           ( (APP_HOSTIF_NUMBER_OF_FRAMES) * (APP_HOSTIF_PER_CHANNEL_SAMPLE_SIZE_IN_BYTES) )

#define APP_HOSTIF_LOG_QUEUE_SIZE                              (1024U)
#define APP_HOSTIF_CURR_CHANNEL                                (3U)

#define APP_HOSTIF_FILTER_RESET                                ('0')
#define APP_HOSTIF_FILTER_SET                                  ('1')
#define APP_HOSTIF_FILTER_DISABLE                              (0U)
#define APP_HOSTIF_FILTER_ENABLE                               (1U)

/* ========================================================================== */
/*                            Typedefs                                        */
/* ========================================================================== */

typedef struct {
	char log[1024];
} AppHostIf_LogEntry;

typedef struct {
    int frames;
    float latency;
    float amp;
    float cpu;
    float dsp;
    double totalLatency;
    double minLatency;
    double maxLatency;
    double totalAmp;
    double minAmp;
    double maxAmp;
    double totalCpu;
    double minCpu;
    double maxCpu;
    double totalDsp;
    double minDsp;
    double maxDsp;
} AppHostIf_LogSummaryParams;

/* ========================================================================== */
/*                         Function Declaration                               */
/* ========================================================================== */

void AppHostIf_logSummary(AppHostIf_LogSummaryParams *logSummaryParams);
void AppHostIf_updateMetrics(AppHostIf_LogSummaryParams *logSummaryParams);
void AppHostIf_logFrameMetrics(AppHostIf_LogSummaryParams *logSummaryParams);
void AppHostIf_logInputAudio(void *arg);
void AppHostIf_logOutputAudio(void *arg);
void AppHostIf_logTask(void *arg);
void AppHostIf_cmdTask(void *arg);

#endif /* _HOST_INTERFACE_H_ */

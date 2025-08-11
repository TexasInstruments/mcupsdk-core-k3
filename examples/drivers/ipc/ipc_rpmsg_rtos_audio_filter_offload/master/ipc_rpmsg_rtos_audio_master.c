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
 * @file ipc_rpmsg_rtos_audio_master.c
 * @brief Master core IPC implementation for DSP offloading
 *
 * This example demonstrates DSP offloading between the MCU-R5 and C7x cores.
 *
 * The MCU-R5 core acts as the 'main' core, while the C7x core serves as the 'remote' core.
 *
 * The main core reads a dataset from the SD card, initiates IPC communication with the remote core,
 * and sends a message containing a pointer to the dataset along with filtering requirements.
 * The remote core processes the dataset by applying the specified filters and returns the filtered
 * output to the main core.
 *
 * This process is repeated until the entire dataset is processed.
 *
 * The given audio sample has slot count of 8 channels, slot width of 16 bits, and 256 frames
 * used for each processing cycle.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/QueueP.h>
#include "host_interface/host_interface.h"

 /* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_IPC_INPUT_AUDIO_FILE_NAME           ("/sd0/input.wav")
#define APP_IPC_RPMESSAGE_MAX_MSG_SIZE          (496u)

/* Main core ack reply end point
 *
 * pick any unique value on that core between 0..RPMESSAGE_MAX_LOCAL_ENDPT-1
 * the value need not be unique across cores
 */
#define APP_IPC_MAIN_CORE_ACK_REPLY_END_PT      (12U)

/* Maximum size that message can have in this example */
#define APP_IPC_MAX_MSG_SIZE                    (64u)

#define APP_IPC_TASK_PRI_LOG_THREAD             (configMAX_PRIORITIES-1)
#define APP_IPC_LOG_TASK_SIZE                   (16384U/sizeof(configSTACK_DEPTH_TYPE))

#define APP_IPC_TASK_PRI_CMD_THREAD             (configMAX_PRIORITIES-1)
#define APP_IPC_CMD_TASK_SIZE                   (16384U/sizeof(configSTACK_DEPTH_TYPE))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* Header of a WAV audio file in PCM format */
typedef struct __attribute__((packed)) {
    char chunkID[4];         /* "RIFF" */
    uint32_t chunkSize;      /* Size of the file minus 8 bytes */
    char format[4];          /* "WAVE" */
    char subchunk1ID[4];     /* "fmt " */
    uint32_t subchunk1Size;  /* Size of the format chunk (usually 16 for PCM) */
    uint16_t audioFormat;    /* Audio format (1 for PCM) */
    uint16_t numChannels;    /* Number of channels (1 for mono, 2 for stereo) */
    uint32_t sampleRate;     /* Sampling rate (e.g., 44100 Hz) */
    uint32_t byteRate;       /* Byte rate = SampleRate * NumChannels * BitsPerSample / 8 */
    uint16_t blockAlign;     /* Block align = NumChannels * BitsPerSample / 8 */
    uint16_t bitsPerSample;  /* Bits per sample (e.g., 16 bits) */
    char subchunk2ID[4];     /* "data" */
    uint32_t subchunk2Size;  /* Size of the data chunk */
} AppIPC_WavHeader;

/**
 *    DSP parameters used in IPC communication.
 */
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
/*                            Global Variables                                */
/* ========================================================================== */

char gIPCMsg[APP_IPC_RPMESSAGE_MAX_MSG_SIZE + 1];

/* Main Core ID */
#if defined (SOC_AM62DX)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

#if defined (SOC_AM275X)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
#endif

/* Remote Core ID */
/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
#if defined (SOC_AM62DX)
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined (SOC_AM275X)
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

/*
* Remote core service end point
*
* pick any unique value on that core between 0..RPMESSAGE_MAX_LOCAL_ENDPT-1
* the value need not be unique across cores
*/
uint16_t gRemoteServiceEndPt = 13u;

RPMessage_Object gAckReplyMsgObject;
int16_t gInputAudioBuf[APP_HOSTIF_BUFFER_SIZE_IN_SAMPLES] __attribute__((aligned(128), section(".bss.filebuf")));
int16_t gOutputAudioBuf[APP_HOSTIF_BUFFER_SIZE_IN_SAMPLES] __attribute__((aligned(128), section(".bss.filebuf")));
AppIPC_DspMsg gDspMsg __attribute__((aligned(128), section(".bss.dspmsg")));
AppIPC_DspParam gDspParams __attribute__((aligned(128), section(".bss.dspparams")));

SemaphoreP_Object gSemIPCLog;
SemaphoreP_Object gSemIPCLogAvail;

StackType_t gIPCLogTaskStack[APP_IPC_LOG_TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gIPCLogTaskObj;
TaskHandle_t gIPCLogTask;

StackType_t gIPCCmdTaskStack[APP_IPC_CMD_TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gIPCCmdTaskObj;
TaskHandle_t gIPCCmdTask;

/* ========================================================================== */
/*                        Extern Function Declaration                         */
/* ========================================================================== */

int App_setupServer(void *args);
void App_shutdownNetworkStack();

/* ========================================================================== */
/*                         Function Definitions                               */
/* ========================================================================== */

void AppIPC_readWavHeader(FF_FILE *inputFp, AppIPC_WavHeader *header)
{
    /* Read the header into the structure */
    ff_fread(header, sizeof(AppIPC_WavHeader), 1, inputFp);

    /* Print header information for debugging */
    DebugP_log("==========================\r\n");
    DebugP_log("   WAV FILE META DATA \r\n");
    DebugP_log("==========================\r\n");
    DebugP_log("ChunkID: %.4s\r\n", header->chunkID);
    DebugP_log("ChunkSize: %u\r\n", header->chunkSize);
    DebugP_log("Format: %.4s\r\n", header->format);
    DebugP_log("Subchunk1ID: %.4s\r\n", header->subchunk1ID);
    DebugP_log("Subchunk1Size: %u\r\n", header->subchunk1Size);
    DebugP_log("AudioFormat: %u\r\n", header->audioFormat);
    DebugP_log("NumChannels: %u\r\n", header->numChannels);
    DebugP_log("SampleRate: %u\r\n", header->sampleRate);
    DebugP_log("ByteRate: %u\r\n", header->byteRate);
    DebugP_log("BlockAlign: %u\r\n", header->blockAlign);
    DebugP_log("BitsPerSample: %u\r\n", header->bitsPerSample);
    DebugP_log("Subchunk2ID: %.4s\r\n", header->subchunk2ID);
    DebugP_log("Subchunk2Size: %u\r\n", header->subchunk2Size);

    /* Seek to the start of the data section */
    ff_fseek(inputFp, sizeof(AppIPC_WavHeader), FF_SEEK_SET);
}

void ipc_rpmsg_rtos_audio_master_main(void *args)
{
    int32_t status;
    uint16_t remoteCoreId;
    uint16_t frameSize;
    uint32_t remoteCoreEndPt;
    uint16_t recvMsgSize;
    uint64_t pDspMsg;
    AppIPC_WavHeader header;
    uint64_t ampSum = 0U;
    float curTimeT1, curTimeT2;

    SemaphoreP_constructBinary(&gSemIPCLog, 1);
    SemaphoreP_constructBinary(&gSemIPCLogAvail, 0);

    AppHostIf_LogSummaryParams logSummaryParams = {
        .totalLatency = 0,
        .minLatency = 1e6,
        .maxLatency = 0,
        .totalAmp = 0.0,
        .minAmp = 1e9,
        .maxAmp = -1e9,
        .totalCpu = 0.0,
        .minCpu = 1e9,
        .maxCpu = -1e9,
        .totalDsp = 0.0,
        .minDsp = 1e9,
        .maxDsp = -1e9,
    };

    DebugP_log("Starting IPC RPMSG DSP OFFLOAD example on main core %d\r\n", gMainCoreId);

    /* Setup Server & establish connection with client */
    App_setupServer(NULL);

    /* Read the .wav file from SD Card for the input dataset to be filtered */
    FF_FILE *inputFp;

    const char *fileName = APP_IPC_INPUT_AUDIO_FILE_NAME;
    inputFp = ff_fopen(fileName, "rb");

    if(inputFp == NULL)
    {
        DebugP_log("Failed to open input file %s\r\n", fileName);
        return;
    }
    else
    {
        /* Read and parse WAV header */
        AppIPC_readWavHeader(inputFp, &header);

        if(header.numChannels != APP_HOSTIF_NUMBER_OF_CHANNELS_PER_FRAME)
        {
            DebugP_logError("Unsupported number of channels: %d. Expected: %d\r\n",
                            header.numChannels, APP_HOSTIF_NUMBER_OF_CHANNELS_PER_FRAME);
            ff_fclose(inputFp);
            return;
        }

        frameSize = APP_HOSTIF_BUFFER_SIZE_IN_SAMPLES;

        gDspMsg.data_buffer         = (uintptr_t)(&gOutputAudioBuf[0]);
        gDspMsg.data_size           = frameSize;
        gDspMsg.params_buffer       = (uintptr_t)&gDspParams;
        gDspMsg.params_size         = sizeof(gDspParams);
        gDspMsg.graph_id            = 0;
        gDspParams.lengthZeroRFFT   = APP_HOSTIF_FILTER_ENABLE;

        CacheP_wbInv((void *) (&gDspMsg), sizeof(gDspMsg), CacheP_TYPE_ALLD);
        CacheP_wbInv((void *) (&gDspParams), sizeof(gDspParams), CacheP_TYPE_ALLD);

        pDspMsg= (uint64_t)&gDspMsg;
        memcpy(gIPCMsg, &pDspMsg, sizeof(pDspMsg));

        /* Read a frame from the file (256*8*16 Bits), send the frame to C7x using IPC,
           receive back the filtered data C7x gave back, Plot the data and ready to
           send again */

        RPMessage_CreateParams createParams;

        RPMessage_CreateParams_init(&createParams);
        createParams.localEndPt = APP_IPC_MAIN_CORE_ACK_REPLY_END_PT;
        status = RPMessage_construct(&gAckReplyMsgObject, &createParams);
        DebugP_assert(status==SystemP_SUCCESS);

        /* wait for all cores to be ready */
        IpcNotify_syncAll(SystemP_WAIT_FOREVER);

        DebugP_log("[IPC] Cores are in sync ...\r\n");

        /* Task for sending logs */
        gIPCLogTask = xTaskCreateStatic(AppHostIf_logTask, "AppHostIf_logTask", APP_IPC_LOG_TASK_SIZE, NULL, APP_IPC_TASK_PRI_LOG_THREAD, gIPCLogTaskStack, &gIPCLogTaskObj);
        configASSERT(gIPCLogTask != NULL);

        /* Task for listening commands */
        gIPCCmdTask = xTaskCreateStatic(AppHostIf_cmdTask, "AppHostIf_cmdTask", APP_IPC_CMD_TASK_SIZE, NULL, APP_IPC_TASK_PRI_CMD_THREAD, gIPCCmdTaskStack, &gIPCCmdTaskObj);
        configASSERT(gIPCCmdTask != NULL);

        while(!ff_feof(inputFp))
        {
            memset(gInputAudioBuf, 0, sizeof(gInputAudioBuf));
            memset(gOutputAudioBuf, 0, sizeof(gOutputAudioBuf));

            /* Read the file into RAM buffer */
            ff_fread(gInputAudioBuf, frameSize, 1, inputFp);
            memcpy(&gOutputAudioBuf[0], &gInputAudioBuf[0], sizeof(gInputAudioBuf));

            curTimeT1 = ClockP_getTimeUsec();

            /* Send to DSP for processing */
            status = RPMessage_send(&gIPCMsg[0], sizeof(pDspMsg),
                                    gRemoteCoreId[0], gRemoteServiceEndPt,
                                    RPMessage_getLocalEndPt(&gAckReplyMsgObject),
                                    SystemP_WAIT_FOREVER);

            DebugP_assert(status==SystemP_SUCCESS);

            recvMsgSize = APP_IPC_RPMESSAGE_MAX_MSG_SIZE;

            /* Wait for response from DSP */
            status = RPMessage_recv(&gAckReplyMsgObject,
                                    &gIPCMsg[0], &recvMsgSize,
                                    &remoteCoreId, &remoteCoreEndPt,
                                    SystemP_WAIT_FOREVER);

            curTimeT2 = ClockP_getTimeUsec();

            logSummaryParams.latency = (curTimeT2 - curTimeT1)/1000;

            /* Log Frame Metrics */
            for (uint32_t i = 0; i < APP_HOSTIF_NUMBER_OF_FRAMES; i++)
            {
                ampSum += abs(gOutputAudioBuf[(i * APP_HOSTIF_NUMBER_OF_CHANNELS_PER_FRAME) + APP_HOSTIF_CURR_CHANNEL]);
            }

            logSummaryParams.amp = (float)(ampSum / (APP_HOSTIF_NUMBER_OF_FRAMES * APP_HOSTIF_NUMBER_OF_CHANNELS_PER_FRAME));
            ampSum = 0U;

            logSummaryParams.cpu = TaskP_loadGetTotalCpuLoad() / 100;
            logSummaryParams.dsp = gDspParams.dspLoad;

            AppHostIf_updateMetrics(&logSummaryParams);

            AppHostIf_logFrameMetrics(&logSummaryParams);

            /* Log Input Audio Data */
            AppHostIf_logInputAudio(NULL);

            /* Log Output Audio Data */
            AppHostIf_logOutputAudio(NULL);

            if (logSummaryParams.frames % 10 == 0)
            {
                AppHostIf_logSummary(&logSummaryParams);
            }

            DebugP_assert(status==SystemP_SUCCESS);
        }
    }

    /* Close the file */
    ff_fclose(inputFp);

    /* Delete the tasks */
    vTaskDelete(gIPCLogTask);
    vTaskDelete(gIPCCmdTask);

    /* Close Network Stack */
    App_shutdownNetworkStack();
}

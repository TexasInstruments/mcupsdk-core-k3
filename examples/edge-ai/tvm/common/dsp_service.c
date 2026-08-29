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

/*
 * DSP Service for TISP and other tasks
 */

#include <stdio.h>
#include <string.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/ipc_rpmsg.h>
#include <drivers/hw_include/cslr_soc.h>
#include <FreeRTOS.h>
#include <task.h>
#include "dsp_service.h"
#include "model_config.h"
#include "stft_istft_handler.h"
#include "utils_handler.h"

/* DSP service implementation */

/* Service state */
static RPMessage_Object gDspRpmsgObj;
static volatile bool gDspServiceRunning = false;
static volatile bool gDspStopRequested = false;

/* Message buffers */
static uint8_t gDspRecvBuf[C7X_MAX_MSG_SIZE] __attribute__((aligned(32)));
static uint8_t gDspSendBuf[C7X_MAX_MSG_SIZE] __attribute__((aligned(32)));

/* API Implementation */
int32_t dsp_service_init(void)
{
    int32_t status;
    RPMessage_CreateParams rpmsgParams;

    if (gDspServiceRunning)
    {
        return SystemP_FAILURE;  /* Already initialized */
    }

    /* Create RPMessage endpoint */
    RPMessage_CreateParams_init(&rpmsgParams);
    rpmsgParams.localEndPt = C7X_SERVICE_ENDPOINT_GENERIC;

    status = RPMessage_construct(&gDspRpmsgObj, &rpmsgParams);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[DSP] Failed to create RPMessage endpoint: %d\r\n", status);
        return status;
    }

    /* Announce service to Linux */
    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, C7X_SERVICE_ENDPOINT_GENERIC, "rpmsg_chrdev");
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[DSP] Failed to announce service: %d\r\n", status);
        RPMessage_destruct(&gDspRpmsgObj);
        return status;
    }

    DebugP_log("[DSP] Service announced on endpoint %d\r\n", C7X_SERVICE_ENDPOINT_GENERIC);

    gDspStopRequested = false;
    gDspServiceRunning = true;

    return SystemP_SUCCESS;
}

void dsp_service_run(void)
{
    int32_t status;
    uint16_t recvMsgSize;
    uint16_t remoteCoreId;
    uint32_t remoteCoreEndPt;

    if (!gDspServiceRunning)
    {
        DebugP_log("[DSP] Service not initialized\r\n");
        return;
    }

    while (!gDspStopRequested)
    {
        /* Set receive buffer size before each call */
        recvMsgSize = C7X_MAX_MSG_SIZE;

        /* Receive message */
        status = RPMessage_recv(&gDspRpmsgObj,
                               gDspRecvBuf, &recvMsgSize,
                               &remoteCoreId, &remoteCoreEndPt,
                               1000000);  /* 1 second timeout in microseconds */

        if (gDspStopRequested)
        {
            DebugP_log("[DSP] Shutdown signal received\r\n");
            break;
        }

        if (status == SystemP_TIMEOUT)
        {
            continue;  /* Check stop flag and retry */
        }

        if (status != SystemP_SUCCESS)
        {
            DebugP_log("[DSP] RPMessage_recv failed: %d\r\n", status);
            continue;
        }

        /* Process message */
        struct c7x_msg_hdr *reqHdr = (struct c7x_msg_hdr *)gDspRecvBuf;
        struct c7x_msg_hdr *respHdr = (struct c7x_msg_hdr *)gDspSendBuf;
        uint16_t respLen = sizeof(struct c7x_msg_hdr);

        /* Default response */
        respHdr->type = reqHdr->type + 0x1000;  /* Response = Request + 0x1000 */
        respHdr->seq = reqHdr->seq;
        respHdr->len = respLen;
        respHdr->status = C7X_STATUS_ERR_OP;  /* Unknown operation by default */

        /* Dispatch by message type */
        switch (reqHdr->type)
        {
            case C7X_MSG_STFT_ANALYZE:
                status = stft_analyze_handler((struct stft_istft_msg *)gDspRecvBuf,
                                             (struct stft_istft_msg *)gDspSendBuf);
                respLen = sizeof(struct stft_istft_msg);
                break;

            case C7X_UTILS_MSG_ANALYZE:
                status = utils_handler_msg((struct utils_handler *)gDspRecvBuf,
                                             (struct utils_handler *)gDspSendBuf);
                respLen = sizeof(struct utils_handler);
                break;

            case C7X_MSG_ISTFT_SYNTHESIZE:
                status = istft_synthesize_handler((struct stft_istft_msg *)gDspRecvBuf,
                                                 (struct stft_istft_msg *)gDspSendBuf);
                respLen = sizeof(struct stft_istft_msg);
                break;

            default:
                DebugP_log("[DSP] Unknown message type: 0x%04x\r\n", reqHdr->type);
                /* respHdr already set to ERR_OP above */
                status = SystemP_SUCCESS;
                break;
        }

        /* Send response */
        status = RPMessage_send(gDspSendBuf, respLen,
                               remoteCoreId, remoteCoreEndPt,
                               RPMessage_getLocalEndPt(&gDspRpmsgObj),
                               SystemP_WAIT_FOREVER);
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("[DSP] Failed to send response: %d\r\n", status);
        }
    }

    DebugP_log("[DSP] Message loop exited\r\n");
}

void dsp_service_stop(void)
{
    DebugP_log("[DSP] Stop requested\r\n");
    gDspStopRequested = true;

    /* Unblock RPMessage_recv to allow graceful exit from message loop */
    if (gDspServiceRunning)
    {
        RPMessage_unblock(&gDspRpmsgObj);
    }
}

/*
 * =============================================================================
 * DSP Service Task Entry Point
 * =============================================================================
 */

void dsp_service_main(void *args)
{
    int32_t status;

    /* Initialize dsp service */
    status = dsp_service_init();
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[DSP] Failed to initialize dsp service: %d\r\n", status);
        vTaskDelete(NULL);
        return;
    }

    /* Run dsp service message loop */
    dsp_service_run();

    DebugP_log("[DSP] Task exiting\r\n");
    vTaskDelete(NULL);
}

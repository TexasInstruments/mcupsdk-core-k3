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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include "dsp_offload.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "drivers/uart.h"
#include "ti_drivers_config.h"
#include <kernel/dpl/TaskP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define IPC_RPMESSAGE_MAX_MSG_SIZE (496U)

#if defined(SOC_AM275X) /* Core IDs for AM275x */
#define MAIN_CORE_ID CSL_CORE_ID_R5FSS0_0
#define REMOTE_CORE_ID CSL_CORE_ID_C75SS0_0
#endif

#if defined(SOC_AM62DX) /* Core IDs for AM62dx */
#define MAIN_CORE_ID CSL_CORE_ID_MCU_R5FSS0_0
#define REMOTE_CORE_ID CSL_CORE_ID_C75SS0_0
#endif

/* RPMessage endpoints */
#define MAIN_CORE_ACK_REPLY_END_PT (12U)
#define REMOTE_SERVICE_END_PT (13U)

#define APP_IPC_TIMEOUT_IN_US (1000000U) /* 1 second */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* RPMessage_Object MUST be global or static */
RPMessage_Object gRecvMsgObject;
char gRecvMsg[IPC_RPMESSAGE_MAX_MSG_SIZE + 1];
void *myGraph = NULL;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void *create_graph(void *input_ptr);
void execute_graph(void *myGraph, params_t *params);
void delete_graph(void *myGraph);

void fft2d_dsp_main(void *args);

extern uint64_t SOC_phyToVirtFxnC7x(const void *virtAddr);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void fft2d_dsp_main(void *args)
{
    /* Initialize RPMessage */
    RPMessage_CreateParams createParams;
    int32_t status;
    uint16_t recvMsgSize;
    uint16_t remoteCoreId = 0;
    uint32_t remoteCoreEndPt;

    ipcMsgBuf_t *msg;
    params_t *params;

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = REMOTE_SERVICE_END_PT;
    status = RPMessage_construct(&gRecvMsgObject, &createParams);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Synchronize with main core */
    IpcNotify_sendSync(MAIN_CORE_ID);
    IpcNotify_waitSync(MAIN_CORE_ID, SystemP_WAIT_FOREVER);

    recvMsgSize = IPC_RPMESSAGE_MAX_MSG_SIZE;

    status = RPMessage_recv(
        &gRecvMsgObject,
        (char *)&gRecvMsg, &recvMsgSize,
        &remoteCoreId, &remoteCoreEndPt,
        SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    msg = (ipcMsgBuf_t *)(&gRecvMsg[0]);
#if defined(SOC_AM275X)
    msg->dataBuffer = SOC_phyToVirtFxnC7x((const void *)msg->dataBuffer);
    params = (params_t *)SOC_phyToVirtFxnC7x((const void *)msg->paramsBuffer);
#endif
#if defined(SOC_AM62DX)
    params = (params_t *)(msg->paramsBuffer);
#endif
    myGraph = create_graph((void *)msg->dataBuffer);
    while (1U)
    {
        CacheP_inv((void *)msg->dataBuffer, msg->dataSize * sizeof(float), CacheP_TYPE_ALLD);
        CacheP_inv((void *)params, sizeof(params_t), CacheP_TYPE_ALLD);

        execute_graph(myGraph, params);
        params->dspLoad = TaskP_loadGetTotalCpuLoad() / 100;

        CacheP_wb((void *)msg->dataBuffer, msg->dataSize * sizeof(float), CacheP_TYPE_ALLD);
        CacheP_wb((void *)params, sizeof(params_t), CacheP_TYPE_ALLD);

        /* Send the output message struct to R5F */
        status = RPMessage_send(
            (char *)&gRecvMsg, sizeof(ipcMsgBuf_t),
            MAIN_CORE_ID, MAIN_CORE_ACK_REPLY_END_PT,
            RPMessage_getLocalEndPt(&gRecvMsgObject),
            SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);

        status = RPMessage_recv(
            &gRecvMsgObject,
            (char *)&gRecvMsg, &recvMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            ClockP_usecToTicks(APP_IPC_TIMEOUT_IN_US)); /* 1 second timeout */
        if (status == SystemP_TIMEOUT)
        {
            break;
        }
    }
    delete_graph(myGraph);
}
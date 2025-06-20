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
 * @file ipc_rpmsg_rtos_audio_remote.c
 * @brief Remote core IPC implementation for DSP offloading
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "FreeRTOS.h"
#include "TISP_test.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <kernel/dpl/TaskP.h>
#include "tisp/dsp_offload.hpp"

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

#define APP_IPC_RPMESSAGE_MAX_MSG_SIZE      (496u)

/* Main core ack reply end point
 *
 * pick any unique value on that core between 0..RPMESSAGE_MAX_LOCAL_ENDPT-1
 * the value need not be unique across cores
 */
#define APP_IPC_MAIN_CORE_ACK_REPLY_END_PT      (12U)
#define APP_IPC_TIMEOUT_IN_US                   (1000000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

char gIPCMsg[APP_IPC_RPMESSAGE_MAX_MSG_SIZE + 1];

/*
* Remote core service end point
*
* pick any unique value on that core between 0..RPMESSAGE_MAX_LOCAL_ENDPT-1
* the value need not be unique across cores
*/
uint16_t gRemoteServiceEndPt = 13u;

/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};

RPMessage_Object gRecvMsgObject;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void ipc_rpmsg_rtos_audio_remote_main(void *args)
{
    CascadeBiquadFIR cascadeBiquadFir;

    /* Wait for receiving message from master core, do the filtering and send back the data */
    int32_t status;
    uint64_t gDspBufPtr;
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;
    void        *spGraph = NULL;
    bool filter = true;

    RPMessage_CreateParams createParams;

    DebugP_log("Starting IPC RPMSG DSP OFFLOAD example on DSP core\r\n");

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gRemoteServiceEndPt;
    status = RPMessage_construct(&gRecvMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    /* wait for all cores to be ready */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    recvMsgSize = APP_IPC_RPMESSAGE_MAX_MSG_SIZE;

    status = RPMessage_recv(&gRecvMsgObject, gIPCMsg, &recvMsgSize, &remoteCoreId, &remoteCoreEndPt, SystemP_WAIT_FOREVER);

    memcpy(&gDspBufPtr, gIPCMsg, recvMsgSize);

    dsp_msg_t   *msg;
    dsp_param_t *param;

    msg   = (dsp_msg_t *) (gDspBufPtr);
    param = (dsp_param_t *) msg->params_buffer;

    spGraph = cascadeBiquadFir.create_graph((int16_t *) msg->data_buffer);

    /* wait for messages forever in a loop */
    while(1)
    {
        if(param->lengthZeroRFFT > 0)
        {
            filter = true;
        }
        else
        {
            filter = false;
        }

        cascadeBiquadFir.execute_graph(spGraph, (int16_t *) msg->data_buffer, (bool)filter);

        param->dspLoad =  TaskP_loadGetTotalCpuLoad() / 100;

        /* Send back the results */
        recvMsgSize = sizeof(gDspBufPtr);

        status = RPMessage_send(
                                &gIPCMsg[0], recvMsgSize,
                                remoteCoreId, remoteCoreEndPt,
                                RPMessage_getLocalEndPt(&gRecvMsgObject),
                                SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);

        recvMsgSize = APP_IPC_RPMESSAGE_MAX_MSG_SIZE;

        status = RPMessage_recv(&gRecvMsgObject,
                                &gIPCMsg[0], &recvMsgSize,
                                &remoteCoreId, &remoteCoreEndPt,
                                ClockP_usecToTicks(APP_IPC_TIMEOUT_IN_US));

        if(status==SystemP_TIMEOUT)
        {
            break;
        }
    }

    /* Timeout and data ended */
    DebugP_log("\nDeleting graph\n");
    cascadeBiquadFir.delete_graph(spGraph);

    /* Deinit system */
    System_deinit();
}

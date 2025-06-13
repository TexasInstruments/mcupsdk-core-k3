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

#include "FreeRTOS.h"
#include "ipc_fw_version.h"
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include "dsp_offload.hpp"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define IPC_RPMESSAGE_MAX_MSG_SIZE (496u)
#define IPC_RPMESSAGE_SERVICE_AUDIO "rpmsg_chrdev"
#define IPC_RPMESSAGE_ENDPT_AUDIO_APP (14U)

typedef struct __attribute__((packed)) {
    uint32_t data_buffer;
    uint32_t params_buffer;
    uint32_t data_size;
    uint32_t params_size;
    uint32_t graph_id;
} Dsp_Msg;

typedef struct __attribute__((packed)) {
    float   dspLoad;
    int32_t lengthZeroRFFT;
    float   gain_treble;
} Dsp_Param;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile uint8_t gbShutdownRemotecoreID = 0u;
volatile uint8_t gbShutdown             = 0u;
RPMessage_Object gIpcRecvMsgObject;
char             gRecvMsg[IPC_RPMESSAGE_MAX_MSG_SIZE + 1];
void            *gSpGraph = NULL;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void ipc_trigger_shutdown();
static void ipc_rp_mbox_callback(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args);
static void ipc_core_shutdown();

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void ipc_trigger_shutdown()
{
    gbShutdown = 1u;
    RPMessage_unblock(&gIpcRecvMsgObject);
}

static void ipc_rp_mbox_callback(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args)
{
    if (clientId == IPC_NOTIFY_CLIENT_ID_RP_MBOX) {
        if (msgValue == IPC_NOTIFY_RP_MBOX_SHUTDOWN) /* Shutdown request from the remoteproc */
        {
            gbShutdownRemotecoreID = remoteCoreId;
            ipc_trigger_shutdown();
        }
    }
}

static void ipc_core_shutdown()
{
    /* Follow the sequence for graceful shutdown for the last recv task */
    DebugP_log("[IPC RPMSG ECHO] Closing all drivers and going to WFI ... !!!\r\n");

    /* Close the drivers */
    Drivers_close();

    /* deinit system */
    System_deinit();

    if (gbShutdownRemotecoreID) {
        /* ACK the shutdown message */
        IpcNotify_sendMsg(gbShutdownRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX, IPC_NOTIFY_RP_MBOX_SHUTDOWN_ACK, 1u);
    }

#if (__ARM_ARCH_PROFILE == 'R') || (__ARM_ARCH_PROFILE == 'M')
    /* For ARM R and M cores*/
    __asm__ __volatile__("wfi"
                        "\n\t"
                        :
                        :
                        : "memory");
#endif
#if defined(BUILD_C7X)
    asm("    IDLE");
#endif
}

void ipc_rpmsg_linux_audio_main(void *args)
{
    CascadeBiquadFIR cascadeBiquadFir;

    int32_t  status;
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;

    RPMessage_CreateParams createParams;
    RPMessage_Object      *pRpmsgObj = &gIpcRecvMsgObject;

    Dsp_Msg   *msg;
    Dsp_Param *param;

    DebugP_log("Audio signal chain test [IPC RPMSG DSP OFFLOAD ] Version: %s (%s %s):  \r\n", IPC_FW_VERSION, __DATE__,
               __TIME__);

    /* This API MUST be called by applications when its ready to talk to Linux */
    status = RPMessage_waitForLinuxReady(SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = IPC_RPMESSAGE_ENDPT_AUDIO_APP;
    status                  = RPMessage_construct(&gIpcRecvMsgObject, &createParams);
    DebugP_assert(status == SystemP_SUCCESS);

    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, IPC_RPMESSAGE_ENDPT_AUDIO_APP, IPC_RPMESSAGE_SERVICE_AUDIO);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Register a callback for the RP_MBOX messages from the Linux remoteproc driver*/
    IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX, &ipc_rp_mbox_callback, NULL);

    recvMsgSize = IPC_RPMESSAGE_MAX_MSG_SIZE;

    status = RPMessage_recv(pRpmsgObj, gRecvMsg, &recvMsgSize, &remoteCoreId, &remoteCoreEndPt, SystemP_WAIT_FOREVER);

    if (gbShutdown == 1u)
    {
        ipc_core_shutdown();
    }

    msg   = (Dsp_Msg *) (&gRecvMsg[0]);
    param = (Dsp_Param *) msg->params_buffer;

    gSpGraph = cascadeBiquadFir.create_graph((int16_t *) msg->data_buffer);
    bool filter = true;

    while (1U)
    {
        msg   = (Dsp_Msg *) (&gRecvMsg[0]);
        param = (Dsp_Param *) msg->params_buffer;

        CacheP_inv((void *) msg->data_buffer, msg->data_size, CacheP_TYPE_ALLD);
        CacheP_inv((void *) msg->params_buffer, 128, CacheP_TYPE_ALLD);

        if(param->lengthZeroRFFT > 0)
        {
            filter = true;
        }
        else
        {
            filter = false;
        }

        cascadeBiquadFir.execute_graph(gSpGraph, (int16_t *) msg->data_buffer, (bool)filter);
        param->dspLoad =  TaskP_loadGetTotalCpuLoad() / 100;;
        CacheP_wb((void *) msg->params_buffer, msg->params_size, CacheP_TYPE_ALLD);
        CacheP_wb((void *) msg->data_buffer, msg->data_size, CacheP_TYPE_ALLD);

        /* send ack to sender CPU at the sender end point */
        status = RPMessage_send(gRecvMsg, recvMsgSize, remoteCoreId, remoteCoreEndPt, RPMessage_getLocalEndPt(pRpmsgObj),
                              SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);

        recvMsgSize = IPC_RPMESSAGE_MAX_MSG_SIZE;

        status = RPMessage_recv(pRpmsgObj, gRecvMsg, &recvMsgSize, &remoteCoreId, &remoteCoreEndPt, SystemP_WAIT_FOREVER);
        if (gbShutdown == 1u)
        {
            DebugP_log("\nDeleting graph\n");
            cascadeBiquadFir.delete_graph(gSpGraph);
            ipc_core_shutdown();
        }
    }
}

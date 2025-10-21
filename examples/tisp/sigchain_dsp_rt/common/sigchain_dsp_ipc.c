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

/* RPMessage_Object MUST be global or static */
RPMessage_Object g_rpmsgRecvObject;
uint8_t g_rpmsgBuf[IPC_RPMESSAGE_MAX_MSG_SIZE + 1];

/* dsp ipc process task */
StackType_t g_dspIpcTaskStack[DSP_IPC_TASK_SIZE];
StaticTask_t g_dspIpcTaskObj;
TaskHandle_t g_dspIpcTask;

uint32_t gCmdAddr;
uint32_t gCmdSize;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#ifdef SIG_CHAIN_LINUX_HOST
volatile uint8_t gbShutdownRemotecoreID = 0u;
volatile uint8_t gbShutdown = 0u;

void SigchainDSP_IPC_triggerShutdown()
{
    gbShutdown = 1U;
    RPMessage_unblock(&g_rpmsgRecvObject);
}

void SigchainDSP_IPC_shutdownCore()
{
    /* Follow the sequence for graceful shutdown for the last recv task */
    DebugP_log(
        "[DSP Signal Chain] Closing all drivers and going to WFI ... !!!\r\n");

    /* Close the drivers */
    Drivers_close();

    /* deinit system */
    System_deinit();

    if (gbShutdownRemotecoreID)
    {
        /* ACK the shutdown message */
        IpcNotify_sendMsg(gbShutdownRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                          IPC_NOTIFY_RP_MBOX_SHUTDOWN_ACK, 1u);
    }

    asm("    IDLE");
}

void SigchainDSP_IPC_rpmsgCB(uint16_t remoteCoreId, uint16_t clientId,
                             uint32_t msgValue, void *args)
{
    if (clientId == IPC_NOTIFY_CLIENT_ID_RP_MBOX)
    {
        if (msgValue ==
            IPC_NOTIFY_RP_MBOX_SHUTDOWN) /* Shutdown request from the remoteproc */
        {
            gbShutdownRemotecoreID = remoteCoreId;
            SigchainDSP_IPC_triggerShutdown();
        }
    }
}

#endif

void SigchainDSP_IPC_checkShutdownMsg()
{
#ifdef SIG_CHAIN_LINUX_HOST
    if (gbShutdown == 1u)
    {
        SigchainDSP_IPC_shutdownCore();
    }
#endif
}

void SigchainDSP_IPC_recvTask(void *arg)
{
    int32_t done = 0;
    uint32_t recvMsgSize;
    ipcMsgBuf_t *msg;

    DebugP_log("sigchain_dsp_ipc_recvtask : waiting for msg ...\r\n");

    while (!done)
    {
        recvMsgSize = IPC_RPMESSAGE_MAX_MSG_SIZE;

        /* Wait for IPC packet from gateway */
        SigchainDSP_IPC_recv(g_rpmsgBuf, &recvMsgSize);

        /* DebugP_log("sigchain_dsp_ipc_recvtask : received message...\r\n"); */

        msg = (ipcMsgBuf_t *) g_rpmsgBuf;

#if defined(SOC_AM275X)
        msg->dataBuffer = SOC_phyToVirtFxnC7x((const void *) msg->dataBuffer);
#endif

        CacheP_inv((void *) msg->dataBuffer, msg->dataSize, CacheP_TYPE_ALLD);

        gCmdAddr = msg->dataBuffer;
        gCmdSize = msg->dataSize;

        /* process the command in idle thread */
        SemaphoreP_post(&semCmdPkt);

    } /* While done loop*/

    vTaskDelete(NULL);
}

void SigchainDSP_IPC_syncRemote()
{
#ifndef SIG_CHAIN_LINUX_HOST
    /* Synchronize with main core */
    IpcNotify_sendSync(MAIN_CORE_ID);
    IpcNotify_waitSync(MAIN_CORE_ID, SystemP_WAIT_FOREVER);
#else
    int32_t status = SystemP_SUCCESS;
    /* This API MUST be called by applications when its ready to talk to Linux */
    status = RPMessage_waitForLinuxReady(SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);
#endif
}

void SigchainDSP_IPC_init()
{
    /* Initialize RPMessage */
    RPMessage_CreateParams createParams;
    int32_t status = SystemP_SUCCESS;

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = REMOTE_SERVICE_END_PT;

    status = RPMessage_construct(&g_rpmsgRecvObject, &createParams);
    DebugP_assert(status == SystemP_SUCCESS);

#ifdef SIG_CHAIN_LINUX_HOST
    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, SIGCHAIN_ENDPT_APP,
                                SIGCHAIN_RPMESSAGE_SERVICE);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Register a callback for the RP_MBOX messages from the Linux remoteproc driver*/
    IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                             &SigchainDSP_IPC_rpmsgCB, NULL);
#endif

    g_dspIpcTask =
        xTaskCreateStatic(SigchainDSP_IPC_recvTask, "SigchainDSP_IPC_recvTask",
                          DSP_IPC_TASK_SIZE, NULL, DSP_IPC_TASK_PRI,
                          g_dspIpcTaskStack, &g_dspIpcTaskObj);
    configASSERT(g_dspIpcTask != NULL);
}

int32_t SigchainDSP_IPC_send(uint8_t *buf, uint32_t bufSize)
{
    int32_t status = SystemP_SUCCESS;

    /* Send the message to C7x */
    status = RPMessage_send(
        (char *) buf, bufSize, MAIN_CORE_ID, MAIN_CORE_ACK_REPLY_END_PT,
        RPMessage_getLocalEndPt(&g_rpmsgRecvObject), SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);
    /* DebugP_log("sigchain_dsp_ipc_send, message sent to main\r\n"); */
    return status;
}

int32_t SigchainDSP_IPC_recv(uint8_t *buf, uint32_t *bufSize)
{
    uint16_t remoteCoreId;
    uint32_t remoteCoreEndPt;

    int32_t status =
        RPMessage_recv(&g_rpmsgRecvObject, (char *) buf, (uint16_t *) bufSize,
                       &remoteCoreId, &remoteCoreEndPt, SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Check shutdown message */
    SigchainDSP_IPC_checkShutdownMsg();

    return status;
}

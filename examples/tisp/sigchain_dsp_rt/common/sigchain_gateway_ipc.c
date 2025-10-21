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

#include "sigchain_gateway.h"

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
RPMessage_Object gAckReplyMsgObject;
uint8_t g_rpmsgBuf[IPC_RPMESSAGE_MAX_MSG_SIZE + 1];

/* gateway ipc process task */
StackType_t g_ipcTaskStack[IPC_TASK_SIZE];
StaticTask_t g_ipcTaskObj;
TaskHandle_t g_ipcTask;

__attribute__((section(".ddrData"), aligned(128)))
uint8_t Cmd_Packet[MAX_ALPHA_CMD_BUFFER];
ipcMsgBuf_t g_ipcMsg;

int32_t SigchainGatewayIPC_recv(uint8_t *buf, uint32_t *bufSize);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SigchainGatewayIPC_recvTask(void *arg)
{
    int32_t done = 0;
    uint32_t recvDataSize = 0;
    ipcMsgBuf_t *msg;

    DebugP_log("sigchain_gateway_ipc_recvtask\r\n");

    while (!done)
    {
        recvDataSize = IPC_RPMESSAGE_MAX_MSG_SIZE;

        /* Wait for IPC packet from dsp */
        SigchainGatewayIPC_recv((uint8_t *) g_rpmsgBuf, &recvDataSize);
        msg = (ipcMsgBuf_t *) g_rpmsgBuf;

#if defined(SOC_AM275X)
        msg->dataBuffer = SOC_phyToVirtFxn(msg->dataBuffer);
#endif

        CacheP_inv((void *) msg->dataBuffer, msg->dataSize, CacheP_TYPE_ALLD);

        /* send packet to com layer */
        SigchainGatewayUART_sendPacket((uint8_t *) (msg->dataBuffer),
                                       msg->dataSize);

    } /* While done loop*/

    vTaskDelete(NULL);
}

void SigchainGatewayIPC_syncRemote()
{
    /* Synchronize with remote core */
    IpcNotify_sendSync(REMOTE_CORE_ID);
    IpcNotify_waitSync(REMOTE_CORE_ID, SystemP_WAIT_FOREVER);
}

void SigchainGatewayIPC_init()
{
    /* Initialize RPMessage */
    RPMessage_CreateParams createParams;
    int32_t status = SystemP_SUCCESS;

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = MAIN_CORE_ACK_REPLY_END_PT;

    status = RPMessage_construct(&gAckReplyMsgObject, &createParams);
    DebugP_assert(status == SystemP_SUCCESS);

    g_ipcTask = xTaskCreateStatic(
        SigchainGatewayIPC_recvTask, "SigchainGatewayIPC_recvTask",
        IPC_TASK_SIZE, NULL, IPC_TASK_PRI, g_ipcTaskStack, &g_ipcTaskObj);
    configASSERT(g_ipcTask != NULL);
}

int32_t SigchainGatewayIPC_send(uint8_t *buf, uint32_t bufSize)
{
    int32_t status = SystemP_SUCCESS;

    memcpy(Cmd_Packet, buf, bufSize);

    /* pointer to input data buffer */
    g_ipcMsg.dataBuffer = (uint32_t) (uintptr_t) Cmd_Packet;
    g_ipcMsg.dataSize = bufSize;

    /* pointer to params buffer (if any) */
    g_ipcMsg.paramsBuffer = 0;
    g_ipcMsg.paramsSize = 0;

    CacheP_wb((void *) g_ipcMsg.dataBuffer, bufSize, CacheP_TYPE_ALLD);

    /* Send the message to C7x */
    status = RPMessage_send((char *) &g_ipcMsg, sizeof(g_ipcMsg),
                            REMOTE_CORE_ID, REMOTE_SERVICE_END_PT,
                            RPMessage_getLocalEndPt(&gAckReplyMsgObject),
                            SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    /* DebugP_log("sigchain_gateway_ipc_send: sending message to dsp...\r\n"); */

    return status;
}

int32_t SigchainGatewayIPC_recv(uint8_t *buf, uint32_t *bufSize)
{
    uint16_t remoteCoreId;
    uint32_t remoteCoreEndPt;

    int32_t status =
        RPMessage_recv(&gAckReplyMsgObject, (char *) buf, (uint16_t *) bufSize,
                       &remoteCoreId, &remoteCoreEndPt, SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    return status;
}

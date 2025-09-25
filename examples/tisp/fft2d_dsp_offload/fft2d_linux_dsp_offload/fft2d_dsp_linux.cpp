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
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include <kernel/dpl/TaskP.h>
#include "dsp_offload.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define IPC_RPMESSAGE_MAX_MSG_SIZE (496U)

/* RPMessage endpoints */
#define FFT2D_RPMESSAGE_SERVICE "rpmsg_chrdev"
#define FFT2D_ENDPT_APP (14U)

#define APP_IPC_TIMEOUT_IN_US (1000000U) // 1 second

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile uint8_t gbShutdownRemotecoreID = 0u;
volatile uint8_t gbShutdown = 0u;

/* RPMessage_Object MUST be global or static */
RPMessage_Object gAckReplyMsgObject;
static RPMessage_Object gRecvMsgObject;

char gRecvMsg[IPC_RPMESSAGE_MAX_MSG_SIZE + 1];
void *myGraph = NULL;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*TISP Functions*/
void *create_graph(void *input_ptr);
void execute_graph(void *myGraph, params_t *params);
void delete_graph(void *myGraph);

static void fft2d_triggerShutdown();
static void fft2d_ipcRPMsgCB(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args);
static void fft2d_coreShutdown();

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void fft2d_triggerShutdown()
{
    gbShutdown = 1u;
    RPMessage_unblock(&gRecvMsgObject);
}

static void fft2d_ipcRPMsgCB(uint16_t remoteCoreId, uint16_t clientId, uint32_t msgValue, void *args)
{
    if (clientId == IPC_NOTIFY_CLIENT_ID_RP_MBOX)
    {
        if (msgValue == IPC_NOTIFY_RP_MBOX_SHUTDOWN) /* Shutdown request from the remoteproc */
        {
            gbShutdownRemotecoreID = remoteCoreId;
            fft2d_triggerShutdown();
        }
    }
}

static void fft2d_coreShutdown()
{
    /* Follow the sequence for graceful shutdown for the last recv task */
    DebugP_log("[2D FFT DSP OFFLOAD] Closing all drivers and going to WFI ... !!!\r\n");

    /* Close the drivers */
    Drivers_close();

    /* deinit system */
    System_deinit();

    if (gbShutdownRemotecoreID)
    {
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

void fft2d_dsp_linux_main(void *args)
{
    /* Initialize RPMessage */
    RPMessage_CreateParams createParams;
    int32_t status;
    uint16_t recvMsgSize;
    uint16_t remoteCoreId = 0;
    uint32_t remoteCoreEndPt;

    /* Message buffer and parameters */
    ipcMsgBuf_t *msg;
    params_t *params;

    DebugP_log("2D FFT Linux signal chain test [2D FFT DSP OFFLOAD] (%s %s)\r\n", __DATE__, __TIME__);

    /* This API MUST be called by applications when its ready to talk to Linux */
    status = RPMessage_waitForLinuxReady(SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = FFT2D_ENDPT_APP;
    status = RPMessage_construct(&gRecvMsgObject, &createParams);
    DebugP_assert(status == SystemP_SUCCESS);

    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, FFT2D_ENDPT_APP, FFT2D_RPMESSAGE_SERVICE);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Register a callback for the RP_MBOX messages from the Linux remoteproc driver*/
    IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX, &fft2d_ipcRPMsgCB, NULL);

    recvMsgSize = IPC_RPMESSAGE_MAX_MSG_SIZE;

    status = RPMessage_recv(
        &gRecvMsgObject,
        (char *)&gRecvMsg, &recvMsgSize,
        &remoteCoreId, &remoteCoreEndPt,
        SystemP_WAIT_FOREVER);

    if (gbShutdown == 1u)
    {
        fft2d_coreShutdown();
    }

    msg = (ipcMsgBuf_t *)(&gRecvMsg[0]);
    params = (params_t *)(msg->paramsBuffer);

    DebugP_log("Creating graph....\r\n");
    myGraph = create_graph((void *)msg->dataBuffer);

    while (1U)
    {
        CacheP_inv((void *)msg->dataBuffer, msg->dataSize * sizeof(float), CacheP_TYPE_ALLD);
        CacheP_inv((void *)params, msg->paramsSize, CacheP_TYPE_ALLD);

        /* Log 5 input data samples in a+ib form */
        DebugP_log("Input data samples\r\n");
        for (int i = 0; i < 5; i++)
        {
            float real = ((float *)msg->dataBuffer)[i * 2];
            float imag = ((float *)msg->dataBuffer)[i * 2 + 1];
            DebugP_log("%.2f + %.2fj\r\n", real, imag);
        }

        DebugP_log("Executing graph....\r\n");
        execute_graph(myGraph, params);
        params->dspLoad = TaskP_loadGetTotalCpuLoad()/100;

        CacheP_wb((void *)msg->dataBuffer, msg->dataSize * sizeof(float), CacheP_TYPE_ALLD);
        CacheP_wb((void *)params, sizeof(params_t), CacheP_TYPE_ALLD);

        /* Log 5 output data samples in a+ib form */
        DebugP_log("Output data samples after Processing (a+ib)\r\n");
        for (int i = 0; i < 5; i++)
        {
            float real = ((float *)msg->dataBuffer)[i * 2];
            float imag = ((float *)msg->dataBuffer)[i * 2 + 1];
            DebugP_log("%.2f + %.2fj\r\n", real, imag);
        }
        DebugP_log("\r\n");

        DebugP_log("\r\n=========FFT Performance Results=========\r\n");
        DebugP_log("  DSP Load           : %d\r\n", params->dspLoad);
        DebugP_log("  Cycle Count        : %d\r\n", params->cycleCount);
        DebugP_log("  Mem Throughput     : %.2f GB/s\r\n\n", params->ddrThroughput);

        /* Send the output message struct to Linux core */
        status = RPMessage_send(
            (char *)&gRecvMsg, sizeof(ipcMsgBuf_t),
            remoteCoreId, remoteCoreEndPt,
            RPMessage_getLocalEndPt(&gRecvMsgObject),
            SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);
        DebugP_log("Sent processed data to Primary Core\r\n");

        status = RPMessage_recv(
            &gRecvMsgObject,
            (char *)&gRecvMsg, &recvMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            SystemP_WAIT_FOREVER); /*wait till the next data pointer*/
        if (gbShutdown == 1u)
        {
            DebugP_log("Deleting graph....\r\n");
            delete_graph(myGraph);
            fft2d_coreShutdown();
        }
    }
}

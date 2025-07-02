/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include <kernel/dpl/TaskP.h>
/* This example shows message exchange between multiple cores.
 *
 * One of the core is designated as the 'main' core
 * and other cores are designated as `remote` cores.
 *
 * The main core initiates IPC with remote core's by sending it a message.
 * The remote cores echo the same message to the main core.
 *
 * The main core repeats this for gMsgEchoCount iterations.
 *
 * In each iteration of message exchange, the message value is incremented.
 *
 * When iteration count reaches gMsgEchoCount, the example is completed.
 *
 */
#if defined (CONFIG_MULTI_ENDPOINT)

#define IPC_RPMESSAGE_NUM_RECV_TASKS         (3u)
#define IPC_RPMESSAGE_TASK_PRI               (8U)

/* RPMessage object used to recvice messages */
RPMessage_Object gIpcRecvMsgObject[IPC_RPMESSAGE_NUM_RECV_TASKS];
#define IPC_RPMESSAGE_TASK_STACK_SIZE  (8*1024U)

uint8_t gIpcTaskStack[IPC_RPMESSAGE_NUM_RECV_TASKS][IPC_RPMESSAGE_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gIpcTask[IPC_RPMESSAGE_NUM_RECV_TASKS];

#endif
/* number of iterations of message exchange to do */
uint32_t gMsgEchoCount = 10u;

#if defined(SOC_AM243X)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_M4FSS0_0,
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_R5FSS1_0,
    CSL_CORE_ID_R5FSS1_1,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined (SOC_AM263X)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_R5FSS1_0,
    CSL_CORE_ID_R5FSS1_1,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined(SOC_AM64X)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_M4FSS0_0,
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_R5FSS1_0,
    CSL_CORE_ID_R5FSS1_1,
    CSL_CORE_ID_A53SS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined(SOC_AM273X) || defined(SOC_AWR294X)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_C66SS0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined (SOC_AM62X)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_A53SS0_0;
/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_M4FSS0_0,
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined (SOC_AM62AX)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_A53SS0_0;
/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_MCU_R5FSS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined (SOC_AM62PX)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_A53SS0_0;
/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_WKUP_R5FSS0_0,
    CSL_CORE_ID_MCU_R5FSS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined(SOC_J722S)
/* main core that starts the message exchange */
uint32_t gMainCoreId = CSL_CORE_ID_A53SS0_0;
/* remote cores that echo messages from main core, make sure to NOT list main core in this list */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_WKUP_R5FSS0_0,
    CSL_CORE_ID_MCU_R5FSS0_0,
    CSL_CORE_ID_MAIN_R5FSS0_0,
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_C75SS1_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

/*
 * Remote core service end point
 *
 * pick any unique value on that core between 0..RPMESSAGE_MAX_LOCAL_ENDPT-1
 * the value need not be unique across cores
 */
#if defined (CONFIG_MULTI_ENDPOINT)
#if defined (SOC_AM62AX)
uint16_t gRemoteServiceEndPt = 21u,gRemoteServiceEndPt1 = 22U, gRemoteServiceEndPt2 =23U;
#else
uint16_t gRemoteServiceEndPt = 13u,gRemoteServiceEndPt1 = 14U, gRemoteServiceEndPt2 =15U;
#endif
#else
uint16_t gRemoteServiceEndPt = 13u;
#endif

/* maximum size that message can have in this example */
#define MAX_MSG_SIZE        (64u)

/* Main core ack reply end point
 *
 * pick any unique value on that core between 0..RPMESSAGE_MAX_LOCAL_ENDPT-1
 * the value need not be unique across cores
 */
#define MAIN_CORE_ACK_REPLY_END_PT  (12U)

/* RPMessage_Object MUST be global or static */
RPMessage_Object gAckReplyMsgObject;

void ipc_rpmsg_echo_multiendpt_test();
void ipc_recv_task_main(void *args);

void ipc_rpmsg_echo_main_core_start()
{
    RPMessage_CreateParams createParams;
    uint32_t msg, i, numRemoteCores;
    uint64_t curTime;
    char msgBuf[MAX_MSG_SIZE];
    int32_t status;
    uint16_t remoteCoreId, msgSize;
    uint32_t remoteCoreEndPt;

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = MAIN_CORE_ACK_REPLY_END_PT;
    status = RPMessage_construct(&gAckReplyMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    numRemoteCores = 0;
    for(i=0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++)
    {
        numRemoteCores++;
    }

    /* wait for all cores to be ready */
    //IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    ClockP_usleep(500*1000); /* wait for log messages from remote cores to be flushed, otherwise this delay is not needed */

    DebugP_log("[IPC RPMSG ECHO] Message exchange started by main core !!!\r\n");

    curTime = ClockP_getTimeUsec();

    for(msg=0; msg<gMsgEchoCount; msg++)
    {
        snprintf(msgBuf, MAX_MSG_SIZE-1, "%d", msg);
        msgBuf[MAX_MSG_SIZE-1] = 0;
        msgSize = strlen(msgBuf) + 1; /* count the terminating char as well */

        /* send the same messages to all cores */
        for(i=0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++ )
        {
            DebugP_log("Main: Sending Message %d\n", msg);
            status = RPMessage_send(
                msgBuf, msgSize,
                gRemoteCoreId[i], gRemoteServiceEndPt,
                RPMessage_getLocalEndPt(&gAckReplyMsgObject),
                SystemP_WAIT_FOREVER);
            DebugP_assert(status==SystemP_SUCCESS);
        }
        /* wait for response from all cores */
        for(i=0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++ )
        {
            /* set 'msgSize' to size of recv buffer,
            * after return `msgSize` contains actual size of valid data in recv buffer
            */
            msgSize = sizeof(msgBuf);
            status = RPMessage_recv(&gAckReplyMsgObject,
                msgBuf, &msgSize,
                &remoteCoreId, &remoteCoreEndPt,
                SystemP_WAIT_FOREVER);
            DebugP_assert(status==SystemP_SUCCESS);
            DebugP_log("Main: Received acknoledgement for msg %d\n", msg);
        }
    }

    curTime = ClockP_getTimeUsec() - curTime;

    DebugP_log("[IPC RPMSG ECHO] All echoed messages received by main core from %d remote cores !!!\r\n", numRemoteCores);
    DebugP_log("[IPC RPMSG ECHO] Messages sent to each core = %d \r\n", gMsgEchoCount);
    DebugP_log("[IPC RPMSG ECHO] Number of remote cores = %d \r\n", numRemoteCores);
    DebugP_log("[IPC RPMSG ECHO] Total execution time = %" PRId64 " usecs\r\n", curTime);
    DebugP_log("[IPC RPMSG ECHO] One way message latency = %" PRId32 " nsec\r\n",
        (uint32_t)(curTime*1000u/(gMsgEchoCount*numRemoteCores*2)));

    RPMessage_destruct(&gAckReplyMsgObject);

    DebugP_log("All tests have passed!!\r\n");
}

/* RPMessage_Object MUST be global or static */
static RPMessage_Object gRecvMsgObject;
#if defined (CONFIG_MULTI_ENDPOINT)
void ipc_rpmsg_echo_remote_core_start(void *args)
#else
void ipc_rpmsg_echo_remote_core_start()
#endif
{
    int32_t status;
    RPMessage_CreateParams createParams;
    char recvMsg[MAX_MSG_SIZE];
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;
    volatile int i = 0;

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gRemoteServiceEndPt;
    status = RPMessage_construct(&gRecvMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);


    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, gRemoteServiceEndPt, "ti.ipc4.ping-pong");
    DebugP_assert(status==SystemP_SUCCESS);

    DebugP_log("[IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!\r\n");

    /* wait for messages forever in a loop */
    while(1)
    {
        /* set 'recvMsgSize' to size of recv buffer,
        * after return `recvMsgSize` contains actual size of valid data in recv buffer
        */
        recvMsgSize = sizeof(recvMsg);
        status = RPMessage_recv(&gRecvMsgObject,
            recvMsg, &recvMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);
        DebugP_log("Remote: Message %d received\n", i);
        /* echo the same message string as reply */

        /* send ack to sender CPU at the sender end point */
        DebugP_log("Remote: Acknowledged %d \n", i++);
        status = RPMessage_send(
            recvMsg, recvMsgSize,
            remoteCoreId, remoteCoreEndPt,
            RPMessage_getLocalEndPt(&gRecvMsgObject),
            SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);
    }
    /* This loop will never exit */
}

void ipc_rpmsg_echo_main_qnx(void *args)
{

    if(IpcNotify_getSelfCoreId()==gMainCoreId)
    {
        ipc_rpmsg_echo_main_core_start();
    }
    else
    {
#if defined (CONFIG_MULTI_ENDPOINT)
        ipc_rpmsg_echo_multiendpt_test();
#else
        ipc_rpmsg_echo_remote_core_start();
#endif
    }

}

#if defined (CONFIG_MULTI_ENDPOINT)
/* Creating tasks for each endpoint */
void ipc_rpmsg_echo_multiendpt_test()
{
    TaskP_Params taskParams;

    int32_t status;
    RPMessage_CreateParams createParams;

    /* Create the tasks which will handle the ping service */
    TaskP_Params_init(&taskParams);
    taskParams.name = "RPMESSAGE_PING_PONG";
    taskParams.stackSize = IPC_RPMESSAGE_TASK_STACK_SIZE;
    taskParams.stack = gIpcTaskStack[0];
    taskParams.priority = IPC_RPMESSAGE_TASK_PRI;
    /* we use the same task function for echo but pass the appropiate rpmsg handle to it, to echo messages */
    taskParams.args = &gIpcRecvMsgObject[0];
    taskParams.taskMain = ipc_rpmsg_echo_remote_core_start;
    DebugP_log("Remote: Creating task 1 for ping-pong service \r\n");

    status = TaskP_construct(&gIpcTask[0], &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Create task which checks data integrity*/
    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gRemoteServiceEndPt1;
    status = RPMessage_construct(&gIpcRecvMsgObject[1], &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, gRemoteServiceEndPt1, "ti.ipc4.test-data");
    DebugP_assert(status==SystemP_SUCCESS);

    TaskP_Params_init(&taskParams);
    taskParams.name = "RPMESSAGE_IPC_TEST";
    taskParams.stackSize = IPC_RPMESSAGE_TASK_STACK_SIZE;
    taskParams.stack = gIpcTaskStack[1];
    taskParams.priority = IPC_RPMESSAGE_TASK_PRI;
    /* we use the same task function for echo but pass the appropiate rpmsg handle to it, to echo messages */
    taskParams.args = &gIpcRecvMsgObject[1];
    taskParams.taskMain = ipc_recv_task_main;
    DebugP_log("Remote: Creating task 2 echo service \r\n");

    status = TaskP_construct(&gIpcTask[1], &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gRemoteServiceEndPt2;
    status = RPMessage_construct(&gIpcRecvMsgObject[2], &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, gRemoteServiceEndPt2, "ti.ipc4.echo-test-data");
    DebugP_assert(status==SystemP_SUCCESS);

    TaskP_Params_init(&taskParams);
    taskParams.name = "RPMESSAGE_IPC_ECHO_TEST";
    taskParams.stackSize = IPC_RPMESSAGE_TASK_STACK_SIZE;
    taskParams.stack = gIpcTaskStack[2];
    taskParams.priority = IPC_RPMESSAGE_TASK_PRI;
    /* we use the same task function for echo but pass the appropiate rpmsg handle to it, to echo messages */
    taskParams.args = &gIpcRecvMsgObject[2];
    taskParams.taskMain = ipc_recv_task_main;
    DebugP_log("Remote: Creating task 3 for echo service \r\n");

    status = TaskP_construct(&gIpcTask[2], &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);
}
void ipc_recv_task_main(void *args)
{
    int32_t status;
    char recvMsg[MAX_MSG_SIZE]; /* +1 for NULL char in worst case */
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;
    RPMessage_Object *pRpmsgObj = (RPMessage_Object *)args;

    /* wait for messages forever in a loop */
    while(1)
    {
        /* set 'recvMsgSize' to size of recv buffer,
        * after return `recvMsgSize` contains actual size of valid data in recv buffer
        */
        recvMsgSize = sizeof(recvMsg);
        status = RPMessage_recv(pRpmsgObj,
            recvMsg, &recvMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);

        DebugP_log("Remote: Message received at endpoint %d\r\n", RPMessage_getLocalEndPt(pRpmsgObj));

        DebugP_log("Remote: Received message %s \r\n",recvMsg);

        /* send ack to sender CPU at the sender end point */
        DebugP_log("Remote: Echo back the same data received\r\n");
        status = RPMessage_send(
            recvMsg, recvMsgSize,
            remoteCoreId, remoteCoreEndPt,
            RPMessage_getLocalEndPt(pRpmsgObj),
            SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);

    }
}
#endif

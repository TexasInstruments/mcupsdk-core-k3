/*
 *  Copyright (C) 2023-2024 Texas Instruments Incorporated
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
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include <FreeRTOS.h>
#include <task.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#if defined(SOC_J722S)
#include <drivers/ipc_rpmsg/ipc_rpmsg_priv.h>
#endif

/* number of iterations of message exchange to do, this is only used by some tests */
uint32_t gMsgEchoCount = 10000;

#if defined(SOC_AM64X)
/* main core that checks the test pass/fail */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_R5FSS1_0,
    CSL_CORE_ID_R5FSS1_1,
    CSL_CORE_ID_M4FSS0_0,
    CSL_CORE_ID_A53SS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined(SOC_AM243X)
/* main core that checks the test pass/fail */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_R5FSS1_0,
    CSL_CORE_ID_R5FSS1_1,
    CSL_CORE_ID_M4FSS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined(SOC_AM263X)
/* main core that checks the test pass/fail */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_R5FSS1_0,
    CSL_CORE_ID_R5FSS1_1,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined(SOC_AM273X) || defined(SOC_AWR294X)
/* main core that checks the test pass/fail */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_C66SS0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined (SOC_AM62X)
/* main core that checks the test pass/fail */
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_M4FSS0_0,
    CSL_CORE_ID_A53SS0_0,
    CSL_CORE_ID_A53SS0_1,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined (SOC_AM62AX) || defined (SOC_AM62DX)

#if defined(BUILD_MCU_R5F_AS_MASTER)
uint32_t gMainCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
#elif defined(BUILD_C7X_AS_MASTER)
uint32_t gMainCoreId = CSL_CORE_ID_C75SS0_0;
#elif defined(BUILD_A53_AS_MASTER)
uint32_t gMainCoreId = CSL_CORE_ID_A53SS0_0;
#else
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;
#endif

/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_MCU_R5FSS0_0,
    CSL_CORE_ID_A53SS0_0,
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined (SOC_AM62PX)
/* main core that checks the test pass/fail */
uint32_t gMainCoreId = CSL_CORE_ID_WKUP_R5FSS0_0;
/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_WKUP_R5FSS0_0,
    CSL_CORE_ID_MCU_R5FSS0_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

#if defined (SOC_AM275X)

/* main core that checks the test pass/fail */
#if defined(BUILD_C7X_AS_MASTER)
uint32_t gMainCoreId = CSL_CORE_ID_C75SS0_0;

/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_R5FSS1_0,
    CSL_CORE_ID_R5FSS1_1,
    CSL_CORE_ID_C75SS1_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#else
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;

/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_R5FSS1_0,
    CSL_CORE_ID_R5FSS1_1,
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_C75SS1_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif
#endif

#if defined (SOC_J722S)
/* main core that checks the test pass/fail */
uint32_t gMainCoreId = CSL_CORE_ID_WKUP_R5FSS0_0;
/* All cores that participate in the IPC */
uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_WKUP_R5FSS0_0,
    CSL_CORE_ID_MCU_R5FSS0_0,
    CSL_CORE_ID_MAIN_R5FSS0_0,
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_C75SS1_0,
    CSL_CORE_ID_MAX /* this value indicates the end of the array */
};
#endif

/* max size of message that will be ever sent */
#define MAX_MSG_SIZE    (128u)

/* Invalid size to induce errors */
#define BUFFER_OVERSIZE_MARGIN 512
#define INVALID_MSG_SIZE (MAX_MSG_SIZE + BUFFER_OVERSIZE_MARGIN)

/* name of server that is annoucned */
#define SERVER_NAME "rpmsg.server"

/* Temporary define for RPMsg send timeout(2 seconds) to fix code hang issue */
#define RPMSG_SEND_TIMEOUT (2 * 1000000)

/* semaphore that is set from callback handler when all sent messages in back to back mode are ack'ed */
SemaphoreP_Object gAckDoneSem;
/* semaphore that is set from callback handler when all sent messages in rx notify callback mode are ack'ed */
SemaphoreP_Object gRxNotifyAckDoneSem;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)

/* Semaphore usesd to indicate that all the variable messages are ack'ed in the receive callback */
SemaphoreP_Object TestIpcRPMsg_varMsgDoneSem;

/* Semaphores used to indicate acknowledgements from multiple endpoints */
SemaphoreP_Object  TestIpcRPMsg_multipleEndptDoneSem1;
SemaphoreP_Object  TestIpcRPMsg_multipleEndptDoneSem2;
SemaphoreP_Object  TestIpcRPMsg_multipleEndptDoneSem3;

/* Counting semaphore used for multi threaded tests */
SemaphoreP_Object  TestIpcRPMsg_sem;
#endif

#define RPMESSAGE_CONTROL_ENDPT (53)

/* server task related properties, like priority, stack size, stack memory, task object handles */
#define SERVER_TASK_PRI (2u)
#if defined(__C7504__) || defined(__C7524__)
#define SERVER_TASK_SIZE (1024*32u)
#else
#define SERVER_TASK_SIZE (16*1024/sizeof(StackType_t))
#endif
StackType_t  gServerTaskStack[SERVER_TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gServerTaskObj;
TaskHandle_t gServerTask;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)

/* Stack for receive tasks */
uint8_t TestIpcRPMsg_recvTasksStack[2][8*1024U] __attribute__((aligned(32)));

/* Stack for send tasks */
uint8_t TestIpcRPMsg_sndTasksStack[2][8*1024U] __attribute__((aligned(32)));

/* Task handle for receiver tasks spawning */
TaskP_Object TestIpcRPMsg_recvTasks[2];

/* Task handle for sender tasks spawning */
TaskP_Object TestIpcRPMsg_sndTasks[2];
#endif

/* RPMessage objects to receive messages */
RPMessage_Object gServerMsgObject;
/* RPMessage objects to receive ack messages */
RPMessage_Object gClientMsgObject;
/* RPMessage objects to receive ack messages in back to back mode */
RPMessage_Object gAckMsgObject;
/* No messages are sent or received to this object, its used for error check tests */
RPMessage_Object gNullRpmsgObj;
/* RPMessage objects to receive ack messages in rx notify callback mode */
RPMessage_Object gRxNotifyAckMsgObject;
/* RPMessage objects for send error check messages */
RPMessage_Object gSendErrorCheckMsgObject;
/* RPMessage objects for recv error check messages */
RPMessage_Object gRecvErrorCheckMsgObject;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)

/* RPMessage objects for mutiple endpoints test case */
RPMessage_Object TestIpcRPMsg_multipleEndptRcvObject1;
RPMessage_Object TestIpcRPMsg_multipleEndptRcvObject2;
RPMessage_Object TestIpcRPMsg_multipleEndptRcvObject3;

/* RPMessage object for send/recv of variable sized messages */
RPMessage_Object TestIpcRPMsg_varMsgRcvObject;

/* RPMessage objects for mutiple receive tasks with different endpoints */
RPMessage_Object TestIpcRpmsg_hostMsgObject;
RPMessage_Object TestIpcRPMsg_recvTaskObjects[2];
RPMessage_Object TestIpcRPMsg_sndTaskObjects[2];
#endif

/* RPMessage end points for server, server acks, server acks in back to back mode */
uint32_t gServerEndPt = 10;
uint16_t gClientEndPt = 11;
uint16_t gAckEndPt    = 12;
uint16_t gNullEndPt   = 13; /* this end point is not created is used for error tests */
uint16_t gRxNotifyAckEndPt = 14;
uint16_t gSendErrorCheckEndPt = 15;
uint16_t gRecvErrorCheckEndPt = 16;
#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)

uint16_t TestIpcRPMsg_varMsgRcvEndPt = 17;
uint16_t TestIpcRPMsg_multipleEndpt1 = 18;
uint16_t TestIpcRPMsg_multipleEndpt2 = 19;
uint16_t TestIpcRPMsg_multipleEndpt3 = 20;
uint16_t TestIpcRpmsg_hostEndPt = 21;
uint16_t TestIpcRpmsg_remoteServiceEndPt1 = 22;
uint16_t TestIpcRpmsg_remoteServiceEndPt2 = 23;

/* Enpoints for send in muti threaded test cases */
uint16_t TestIpcRpmsg_hostClientEndPt1 = 24;
uint16_t TestIpcRpmsg_hostClientEndPt2 = 25;
#endif

/* one to one test args */
typedef struct {
    uint16_t remoteCoreId; /* core to test message exchange with */
    uint16_t msgSize;   /* size of message to exchange */
    uint32_t echoMsgCount; /* number of messages to exchange */
} Test_Args;

/* message that is sent in back to back test */
typedef struct {

    uint32_t curCount;
    uint32_t maxCount;

} Msg_BackToBack;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)

/* Structure used to send variable size message  */
typedef struct 
{
    uint8_t msgSize;
    uint8_t msgIndx;
    uint8_t *msgBuf;
}TestIpcRPMsg_varMsg;

/* Buffer used to create variable sized buffers */
uint8_t TestIpcRPMsg_varSndBuf[112];

/* Buffer used to create variable sized buffers */
uint8_t TestIpcRPMsg_varRcvBuf[112];

/* Message patterns of variable size test */
uint8_t TestIpcRPMsg_varMsgPatterns[3] = {0xAA, 0xCC, 0xFF};

/* Sizes to be used for variable message transfer */
uint8_t TestIpcRPMsg_varMsgSizes[3] = {32, 64, 112};

/* Buffer used for mutiple endpoint IPC notify */
uint8_t TestIpcRPMsg_notifySndBuf[32];

/* Buffer used for mutiple endpoint IPC notify */
uint8_t TestIpcRPMsg_notifyRcvBuf[32];
#endif

typedef struct {

    uint16_t remoteEndPt;
    char remoteServiceName[32];

} ControlEndPt_Info;

ControlEndPt_Info gControlEndPt_info[CSL_CORE_ID_MAX];

/*Empty resource table to induce errors for coverage*/
RPMessage_ResourceTable gRPMessage_linuxResourceTable =
{
    {
        1U,         /* we're the first version that implements this */
        0U,         /* number of entries, MUST be 2 */
        { 0U, 0U, } /* reserved, must be zero */
    },
};

/* Performance is calculated for 4 msg lengths (4,32,64,112) and from all remote cores */
#define MAX_IPC_RPMSG_PERF_CNT      ((CSL_CORE_ID_MAX-1) * 4)
typedef struct ipcPerfObj_s {
uint32_t remoteCoreId;
uint32_t msgSize;
uint32_t msgCount;
uint64_t msgLatency;
uint64_t maxLatency;
} ipcPerfObj_t;
ipcPerfObj_t gIpcPerfObj[MAX_IPC_RPMSG_PERF_CNT] = {0};
uint32_t     gIpcPerfCnt = 0;

void test_rpmsgRxNotifyHandler(RPMessage_Object *obj, void *arg);
#if defined(SOC_J722S)
static void test_rpmsgValidParams(void *args);
#endif

#if defined(SOC_AM275X) || defined(SOC_AM62AX) || defined(SOC_AM62DX)
void TestIpcRpmsg_multiplEndPointRecvTask(void *arg);
void TestIpcRPMsg_varMsgRxNotifyHandler(RPMessage_Object *obj, void *arg);
void TestIpcRPMsg_multipleEndptRxNotifyHandler1(RPMessage_Object *obj, void *arg);
void TestIpcRPMsg_multipleEndptRxNotifyHandler2(RPMessage_Object *obj, void *arg);
void TestIpcRPMsg_multipleEndptRxNotifyHandler3(RPMessage_Object *obj, void *arg);
#endif

/* handle announcement messages and store in a global, these are checked later on */
void test_rpmsgControlEndPtCallback(void *arg,
    uint16_t remoteCoreId, uint16_t remoteEndPt, const char *remoteServiceName)
{
    ControlEndPt_Info *obj = (ControlEndPt_Info *)arg;

    if(remoteCoreId < CSL_CORE_ID_MAX)
    {
        obj[remoteCoreId].remoteEndPt = remoteEndPt;
        strncpy(obj[remoteCoreId].remoteServiceName, remoteServiceName, 32);
    }
}

/* Ack message handler when messages are sent back to back, here after required messages are received semaphore is posted */
void test_rpmsgAckHandler(RPMessage_Object *obj, void *arg, void *data, uint16_t dataLen, uint16_t remoteCoreId, uint16_t remoteEndPt)
{
    Msg_BackToBack *pMsg = (Msg_BackToBack*)data;

    if(pMsg->curCount == (pMsg->maxCount-1) )
    {
        SemaphoreP_Object *pDoneSem = (SemaphoreP_Object *)arg;

        SemaphoreP_post(pDoneSem);
    }
}


/* server task which simply echos the receive message back to the sender */
void test_rpmsgServerMain(void *args)
{
    int32_t status;
    static char recvMsg[MAX_MSG_SIZE];
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;

    /* wait for messages forever in a loop */
    while(1)
    {
        /* set 'recvMsgSize' to size of recv buffer,
        * after return `recvMsgSize` contains actual size of valid data in recv buffer
        */
        recvMsgSize = sizeof(recvMsg);
        status = RPMessage_recv(&gServerMsgObject,
            recvMsg, &recvMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);

        /* echo the same message as reply */

        /* send ack to sender CPU at the sender end point */
        status = RPMessage_send(
            recvMsg, recvMsgSize,
            remoteCoreId, remoteCoreEndPt,
            RPMessage_getLocalEndPt(&gServerMsgObject),
            SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);
    }
    /* This loop will never exit */
}

/* create semaphores, rpmessage objects and tasks as needed */
void test_rpmsgCreateObjects()
{
    int32_t status;
    RPMessage_CreateParams createParams;

#if defined(SOC_AM275X) || defined(SOC_AM62AX) || defined(SOC_AM62DX)

    /* Create two tasks to receive messages */
    TaskP_Params taskParams1;
    TaskP_Params taskParams2;

    RPMessage_CreateParams createTaskParams1;
    RPMessage_CreateParams createTaskParams2;

    status = SemaphoreP_constructBinary(&TestIpcRPMsg_multipleEndptDoneSem1, 0);
    DebugP_assert(status==SystemP_SUCCESS);

    status = SemaphoreP_constructBinary(&TestIpcRPMsg_multipleEndptDoneSem2, 0);
    DebugP_assert(status==SystemP_SUCCESS);

    status = SemaphoreP_constructBinary(&TestIpcRPMsg_multipleEndptDoneSem3, 0);
    DebugP_assert(status==SystemP_SUCCESS);

    status =  SemaphoreP_constructCounting(&TestIpcRPMsg_varMsgDoneSem, 0, 3);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
#endif

    status = SemaphoreP_constructBinary(&gAckDoneSem, 0);
    DebugP_assert(status==SystemP_SUCCESS);

    status = SemaphoreP_constructBinary(&gRxNotifyAckDoneSem, 0);
    DebugP_assert(status==SystemP_SUCCESS);
    

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gServerEndPt;
    status = RPMessage_construct(&gServerMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gAckEndPt;
    createParams.recvCallback = test_rpmsgAckHandler;
    createParams.recvCallbackArgs = &gAckDoneSem;
    status = RPMessage_construct(&gAckMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gRxNotifyAckEndPt;
    createParams.recvNotifyCallback = test_rpmsgRxNotifyHandler;
    createParams.recvNotifyCallbackArgs = &gRxNotifyAckDoneSem;
    status = RPMessage_construct(&gRxNotifyAckMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)
    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = TestIpcRPMsg_varMsgRcvEndPt;
    createParams.recvNotifyCallback = TestIpcRPMsg_varMsgRxNotifyHandler;
    createParams.recvNotifyCallbackArgs = &TestIpcRPMsg_varMsgDoneSem;
    status = RPMessage_construct(&TestIpcRPMsg_varMsgRcvObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = TestIpcRPMsg_multipleEndpt1;
    createParams.recvNotifyCallback = TestIpcRPMsg_multipleEndptRxNotifyHandler1;
    createParams.recvNotifyCallbackArgs = &TestIpcRPMsg_multipleEndptDoneSem1;
    status = RPMessage_construct(&TestIpcRPMsg_multipleEndptRcvObject1, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = TestIpcRPMsg_multipleEndpt2;
    createParams.recvNotifyCallback = TestIpcRPMsg_multipleEndptRxNotifyHandler2;
    createParams.recvNotifyCallbackArgs = &TestIpcRPMsg_multipleEndptDoneSem2;
    status = RPMessage_construct(&TestIpcRPMsg_multipleEndptRcvObject2, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = TestIpcRPMsg_multipleEndpt3;
    createParams.recvNotifyCallback = TestIpcRPMsg_multipleEndptRxNotifyHandler3;
    createParams.recvNotifyCallbackArgs = &TestIpcRPMsg_multipleEndptDoneSem3;
    status = RPMessage_construct(&TestIpcRPMsg_multipleEndptRcvObject3, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);
#endif

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gClientEndPt;
    status = RPMessage_construct(&gClientMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gSendErrorCheckEndPt;
    status = RPMessage_construct(&gSendErrorCheckMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gRecvErrorCheckEndPt;
    status = RPMessage_construct(&gRecvErrorCheckMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    memset(&gControlEndPt_info[0], 0, sizeof(ControlEndPt_Info));
    RPMessage_controlEndPtCallback(test_rpmsgControlEndPtCallback, &gControlEndPt_info[0]);

    gServerTask = xTaskCreateStatic(test_rpmsgServerMain,
                                  "test_rpmsgServerMain",
                                  SERVER_TASK_SIZE,
                                  NULL,
                                  SERVER_TASK_PRI,
                                  gServerTaskStack,
                                  &gServerTaskObj);
    configASSERT(gServerTask != NULL);

#if defined(SOC_AM275X) || defined(SOC_AM62AX) || defined(SOC_AM62DX)

    /* Create the  receiver tasks with two endpoints */
#if defined (SOC_AM275X)
    if ((IpcNotify_getSelfCoreId() != CSL_CORE_ID_C75SS0_0) && ((IpcNotify_getSelfCoreId() != CSL_CORE_ID_C75SS1_0)))
#else
    if ((IpcNotify_getSelfCoreId() != CSL_CORE_ID_C75SS0_0))
#endif
    {
        RPMessage_CreateParams_init(&createTaskParams1);
        createTaskParams1.localEndPt = TestIpcRpmsg_remoteServiceEndPt1;
        status = RPMessage_construct(&TestIpcRPMsg_recvTaskObjects[0], &createTaskParams1);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

        TaskP_Params_init(&taskParams1);
        taskParams1.name = "RECEIVE_TASK1";
        taskParams1.stackSize = 8 * 1024;
        taskParams1.stack = TestIpcRPMsg_recvTasksStack[0];
        taskParams1.priority = 8U;
        taskParams1.args = &TestIpcRPMsg_recvTaskObjects[0]; 
        taskParams1.taskMain = TestIpcRpmsg_multiplEndPointRecvTask; 
        DebugP_log("Creating Receive task 1 for mutiple endpoint test\r\n");
    
        status = TaskP_construct(&TestIpcRPMsg_recvTasks[0], &taskParams1);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    
        /* RPMessage object for second receiver task */
        RPMessage_CreateParams_init(&createTaskParams2);
        createTaskParams2.localEndPt = TestIpcRpmsg_remoteServiceEndPt2;
        status = RPMessage_construct(&TestIpcRPMsg_recvTaskObjects[1], &createTaskParams2); 
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

        TaskP_Params_init(&taskParams2);
        taskParams2.name = "RECEIVE_TASK2";
        taskParams2.stackSize = 8 * 1024;
        taskParams2.stack = TestIpcRPMsg_recvTasksStack[1];
        taskParams2.priority = 8U;
        taskParams2.args = &TestIpcRPMsg_recvTaskObjects[1]; 
        taskParams2.taskMain = TestIpcRpmsg_multiplEndPointRecvTask; 
        DebugP_log("Creating Receive task 2 for mutiple endpoint test \r\n");

        status = TaskP_construct(&TestIpcRPMsg_recvTasks[1], &taskParams2);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }
#endif
    /* wait for all cores to be ready */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    DebugP_log("[TEST IPC RPMSG] Ready for IPC !!!\r\n");
}

/* delete all objects created in test_rpmsgCreateObjects
 * Note, on core other than main cores the server task never exists so objects are never deleted
 */
void test_rpmsgDestructObjects()
{
    vTaskDelete(gServerTask);
    RPMessage_destruct(&gServerMsgObject);
    RPMessage_destruct(&gAckMsgObject);
    RPMessage_destruct(&gRxNotifyAckMsgObject);
    RPMessage_destruct(&gClientMsgObject);
    RPMessage_destruct(&gSendErrorCheckMsgObject);
    RPMessage_destruct(&gRecvErrorCheckMsgObject);

#if defined(SOC_AM275X) || defined(SOC_AM62AX) || defined(SOC_AM62DX)
    RPMessage_destruct(&TestIpcRPMsg_varMsgRcvObject);
    RPMessage_destruct(&TestIpcRPMsg_recvTaskObjects[0]);
    RPMessage_destruct(&TestIpcRPMsg_recvTaskObjects[1]);
    
    SemaphoreP_destruct(&gAckDoneSem);
    SemaphoreP_destruct(&gRxNotifyAckDoneSem);
    SemaphoreP_destruct(&TestIpcRPMsg_varMsgDoneSem);
    SemaphoreP_destruct(&TestIpcRPMsg_multipleEndptDoneSem1);
    SemaphoreP_destruct(&TestIpcRPMsg_multipleEndptDoneSem2);
    SemaphoreP_destruct(&TestIpcRPMsg_multipleEndptDoneSem3);

    TaskP_destruct(&TestIpcRPMsg_recvTasks[0]);
    TaskP_destruct(&TestIpcRPMsg_recvTasks[1]);
#endif

}

void test_rpmsgControlEndPt(void *args)
{
    uint32_t remoteCoreId, i;

    /* wait a while we should definitely get annoucments within this time */
    ClockP_usleep(10*1000);

    /* validate server end pt annoucements */
    for(i=0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++ )
    {
        remoteCoreId = gRemoteCoreId[i];
        if(remoteCoreId != IpcNotify_getSelfCoreId())
        {
            TEST_ASSERT_EQUAL_UINT16(gServerEndPt, gControlEndPt_info[remoteCoreId].remoteEndPt);
            TEST_ASSERT_EQUAL_UINT32( 0, strcmp(gControlEndPt_info[remoteCoreId].remoteServiceName, SERVER_NAME) );
        }
    }
}

void test_rpmsgAnyToAny(void *args)
{
    uint32_t msg, i;
    static char msgBuf[MAX_MSG_SIZE];
    static char ackMsgBuf[MAX_MSG_SIZE];
    int32_t status;
    uint16_t remoteCoreId, msgSize, ackMsgSize;
    uint32_t remoteCoreEndPt;

    for(msg=0; msg<gMsgEchoCount; msg++)
    {
        snprintf(msgBuf, MAX_MSG_SIZE-1, "%d", msg);
        msgBuf[MAX_MSG_SIZE-1] = 0;
        msgSize = strlen(msgBuf) + 1; /* count the terminating char as well */

        /* send the same message to all cores */
        for(i=0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++ )
        {
            if(gRemoteCoreId[i] != IpcNotify_getSelfCoreId())
            {
                /*
                 * Temporary fix for code hang issue.
                 * Replaced "SystemP_WAIT_FOREVER" with 2 second timeout.
                 */
                status = RPMessage_send(
                    msgBuf, msgSize,
                    gRemoteCoreId[i], gServerEndPt,
                    RPMessage_getLocalEndPt(&gClientMsgObject),
                    ClockP_usecToTicks(RPMSG_SEND_TIMEOUT));
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
            }
        }
        /* wait for response from all cores */
        for(i=0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++ )
        {
            if(gRemoteCoreId[i] != IpcNotify_getSelfCoreId())
            {
                /* set 'ackMsgSize' to size of recv buffer,
                * after return `msgSize` contains actual size of valid data in recv buffer
                */
                ackMsgSize = sizeof(ackMsgBuf);
                ackMsgBuf[0] = 0;
                status = RPMessage_recv(&gClientMsgObject,
                    ackMsgBuf, &ackMsgSize,
                    &remoteCoreId, &remoteCoreEndPt,
                    SystemP_WAIT_FOREVER);
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
                TEST_ASSERT_EQUAL_UINT16(gServerEndPt, remoteCoreEndPt);
                TEST_ASSERT_EQUAL_UINT16(msgSize, ackMsgSize);
                TEST_ASSERT_EQUAL_INT32( 0, strcmp(ackMsgBuf, msgBuf));
            }
        }
    }

    /* wait for all cores to have executed upto this point
     * if we dont get sync from cores then message exchange between some core's has failed
     */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);
}

/* message exchange with one core, this is used to measure message exchange latency */
void test_rpmsgOneToOne(void *args)
{
    Test_Args *pTestArgs = (Test_Args*)args;
    uint16_t remoteCoreId = pTestArgs->remoteCoreId;
    uint16_t msgSize = pTestArgs->msgSize;
    uint32_t echoMsgCount = pTestArgs->echoMsgCount;
    uint64_t curTime, totalTime = 0U;
    uint32_t msg;
    static char msgBuf[MAX_MSG_SIZE];
    static char ackMsgBuf[MAX_MSG_SIZE];
    int32_t status;
    uint16_t ackMsgSize;
    uint32_t remoteCoreEndPt;

    TEST_ASSERT_LESS_OR_EQUAL_UINT16(MAX_MSG_SIZE, msgSize);

    /* fill with known data, we dont check data integrity in this test since
     * we want to focus on performance here
     *
     * Data integrity is tested in test_rpmsgAnyToAny
     */
    memset(msgBuf, 0xAA, MAX_MSG_SIZE);

    for(msg=0; msg<echoMsgCount; msg++)
    {
        curTime = ClockP_getTimeUsec();
        status = RPMessage_send(
            msgBuf, msgSize,
            remoteCoreId, gServerEndPt,
            RPMessage_getLocalEndPt(&gClientMsgObject),
            SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        ackMsgSize = sizeof(ackMsgBuf);
        status = RPMessage_recv(&gClientMsgObject,
            ackMsgBuf, &ackMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        TEST_ASSERT_EQUAL_UINT16(msgSize, ackMsgSize);
        curTime = ClockP_getTimeUsec() - curTime;

        if(curTime > gIpcPerfObj[gIpcPerfCnt].maxLatency)
        {
            gIpcPerfObj[gIpcPerfCnt].maxLatency = curTime;
        }
        totalTime += curTime;
    }

    gIpcPerfObj[gIpcPerfCnt].remoteCoreId = remoteCoreId;
    gIpcPerfObj[gIpcPerfCnt].msgSize = msgSize;
    gIpcPerfObj[gIpcPerfCnt].msgLatency = totalTime;
    gIpcPerfObj[gIpcPerfCnt].msgCount = echoMsgCount;
    gIpcPerfCnt++;
    DebugP_assert(gIpcPerfCnt < MAX_IPC_RPMSG_PERF_CNT);

}

/* In this test
    - we do message exchange with one core,
    - we send message back to back without waiting for ack
    - ack received in the callback mode
    - this tests fifo full and wait conditions
    - and test also callback mode of IPC
 */
void test_rpmsgOneToOneBackToBack(void *args)
{
    Test_Args *pTestArgs = (Test_Args*)args;
    uint16_t remoteCoreId = pTestArgs->remoteCoreId;
    uint32_t echoMsgCount = pTestArgs->echoMsgCount;
    uint64_t curTime;
    uint32_t msg, oldDebugLogZone;
    int32_t status;

    /* disable warning logs since we are testing for those, so it will clutter the output */
    oldDebugLogZone = DebugP_logZoneDisable(DebugP_LOG_ZONE_WARN);

    curTime = ClockP_getTimeUsec();

    for(msg=0; msg<echoMsgCount; msg++)
    {
        Msg_BackToBack msgObj;

        msgObj.curCount = msg;
        msgObj.maxCount = echoMsgCount;
        status = RPMessage_send(
            &msgObj, sizeof(msgObj),
            remoteCoreId, gServerEndPt,
            RPMessage_getLocalEndPt(&gAckMsgObject),
            SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
    status = SemaphoreP_pend(&gAckDoneSem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    curTime = ClockP_getTimeUsec() - curTime;

    DebugP_logZoneRestore(oldDebugLogZone);

    DebugP_log("[TEST IPC RPMSG] Messages sent = %d, remote core = %s \r\n",
                    echoMsgCount, SOC_getCoreName(remoteCoreId));
    DebugP_log("[TEST IPC RPMSG] Total execution time = %" PRId64 " usecs\r\n", curTime);
    DebugP_log("[TEST IPC RPMSG] Avg one-way message latency = %" PRId32 " nsec\r\n",
        (uint32_t)(curTime*1000u/(echoMsgCount*2)));
}


/* In this test
    - we check multiple error conditions for RPMsgSend by
    - 1. Sending more messages than freeQ can hold
    - 2. Sending message with size more than vRing size to check for warnings
    - 3. Sending message to a remote core which is not enabled
    - 4. Send messages more than numBuffer to induce timeout errors
*/

void test_rpmsgSendErrorChecks(void *args)
{
    Test_Args *pTestArgs = (Test_Args*)args;
    uint16_t remoteCoreId = pTestArgs->remoteCoreId;
    uint16_t msgSize = pTestArgs->msgSize;
    uint32_t echoMsgCount = pTestArgs->echoMsgCount;
    uint32_t msg, oldDebugLogZone, msgSent;
    uint32_t timeout = 1;
    static char msgBuf[INVALID_MSG_SIZE];
    static char ackMsgBuf[INVALID_MSG_SIZE];
    int32_t status;
    uint16_t ackMsgSize;
    uint32_t remoteCoreEndPt;

    /* Disable error and warning logs to avoid clutter during test cases */
    oldDebugLogZone = DebugP_logZoneDisable(DebugP_LOG_ZONE_WARN | DebugP_LOG_ZONE_ERROR);
    memset(msgBuf, 0xAA, 8);
    ackMsgSize = sizeof(ackMsgBuf);

    /* 1.Send more messages than freeQ can hold */
    for(msg = 0; msg<2048; msg++)
    {
        status = RPMessage_send(msgBuf,
                                4,
                                remoteCoreId,
                                gServerEndPt,
                                RPMessage_getLocalEndPt(&gSendErrorCheckMsgObject),
                                timeout);
        if(status == SystemP_TIMEOUT)
        {
            break;
        }
    }

    msgSent = msg;

    for(msg = 0; msg<msgSent; msg++)
    {
        status = RPMessage_recv(&gSendErrorCheckMsgObject,
                            ackMsgBuf,
                            &ackMsgSize,
                            &remoteCoreId,
                            &remoteCoreEndPt,
                            timeout);
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);


    /* 2. Send oversized message to trigger truncate warning */
    memset(msgBuf, 0xAA, INVALID_MSG_SIZE);
    status = RPMessage_send(msgBuf,
                            msgSize,
                            remoteCoreId,
                            gServerEndPt,
                            RPMessage_getLocalEndPt(&gSendErrorCheckMsgObject),
                            SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ackMsgSize = sizeof(ackMsgBuf);
    status = RPMessage_recv(&gSendErrorCheckMsgObject,
                            ackMsgBuf,
                            &ackMsgSize,
                            &remoteCoreId,
                            &remoteCoreEndPt,
                            SystemP_WAIT_FOREVER);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    /* Message will be truncated, so the actual message receieved would be the max buffer size */
    TEST_ASSERT_EQUAL_UINT16(MAX_MSG_SIZE, ackMsgSize);

    /*Send messgaes to control endPoint with different condition for better coverage*/
    memset(msgBuf, 0x4A, 8);

    status = RPMessage_send(&msgBuf,
                            4,
                            remoteCoreId,
                            gServerEndPt,
                            RPMESSAGE_CONTROL_ENDPT,
                            SystemP_WAIT_FOREVER); /* wait until message is put in VRING */

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(1);

    /*Set RPMessage_controlEndPtCallback to NULL*/
    RPMessage_controlEndPtCallback(NULL, NULL);
    status = RPMessage_send(&msgBuf,
                            4,
                            remoteCoreId,gServerEndPt, /* control end point on remote side */
                            RPMESSAGE_CONTROL_ENDPT, /* reply or local end point, set also to control end point */
                            SystemP_WAIT_FOREVER); /* wait until message is put in VRING */

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RPMessage_send(&msgBuf,
                            4,
                            remoteCoreId,
                            gServerEndPt, /* control end point on remote side */
                            RPMESSAGE_MAX_LOCAL_ENDPT, /* reply or local end point, set also to control end point */
                            SystemP_WAIT_FOREVER); /* wait until message is put in VRING */

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* 3. Send message to a remote core which is not enabled*/
    status = RPMessage_send(msgBuf,
                            msgSize,
                            CSL_CORE_ID_HSM_M4FSS0_0,
                            gServerEndPt,
                            RPMessage_getLocalEndPt(&gSendErrorCheckMsgObject),
                            SystemP_WAIT_FOREVER);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = RPMessage_send(NULL,
                            msgSize,
                            CSL_CORE_ID_HSM_M4FSS0_0,
                            gServerEndPt,
                            RPMessage_getLocalEndPt(&gSendErrorCheckMsgObject),
                            SystemP_WAIT_FOREVER);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = RPMessage_send(msgBuf,
                            0,
                            CSL_CORE_ID_HSM_M4FSS0_0,
                            gServerEndPt,
                            RPMessage_getLocalEndPt(&gSendErrorCheckMsgObject),
                            SystemP_WAIT_FOREVER);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = RPMessage_send(NULL,
                            0,
                            CSL_CORE_ID_HSM_M4FSS0_0,
                            gServerEndPt,
                            RPMessage_getLocalEndPt(&gSendErrorCheckMsgObject),
                            SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /*4. Send message > numBuffer to induce timeout errors*/
    msg = 0;
    for(msg = 0; msg<echoMsgCount; msg++)
    {
    status = RPMessage_send(msgBuf,
                            4,
                            remoteCoreId,
                            gServerEndPt,
                            RPMessage_getLocalEndPt(&gSendErrorCheckMsgObject),
                            timeout);
    }
    DebugP_logZoneRestore(oldDebugLogZone);
}

/* In this test
    - we check the error conditions for recieve by
    - 1. Using a smaller buffer to trigger warnings
    - 2. Inducing a receive timeout
    - 3. Receiving with NULL remote endpoint to trigger errors
    - 4. Using invalid parameters to generate errors
*/
void test_rpmsgRecvErrorChecks(void *args)
{
    Test_Args *pTestArgs = (Test_Args*)args;
    uint16_t remoteCoreId = pTestArgs->remoteCoreId;
    uint16_t sendMsgSize = pTestArgs->msgSize;
    uint16_t recvMsgSize = 4;
    char sendMsgBuf[sendMsgSize];
    char recvMsgBuf[recvMsgSize];
    int32_t status;
    uint32_t timeout = 1;
    uint16_t actRecvMsgSize;
    uint32_t remoteCoreEndPt;

    memset(sendMsgBuf, 0xAA, sendMsgSize);

    /* 1. Message will be truncated, so the actual message receieved would be the max buffer size */
    status = RPMessage_send(sendMsgBuf,
                            sendMsgSize,
                            remoteCoreId,
                            gServerEndPt,
                            RPMessage_getLocalEndPt(&gRecvErrorCheckMsgObject),
                            SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    actRecvMsgSize = sizeof(recvMsgBuf);
    status = RPMessage_recv(&gRecvErrorCheckMsgObject,
                            recvMsgBuf,
                            &actRecvMsgSize,
                            &remoteCoreId,
                            &remoteCoreEndPt,
                            SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT16(actRecvMsgSize, recvMsgSize);


    /* 2. Recieve timeout */
    /* Try to receieve with a timeout without sending anything */
    status = RPMessage_recv(&gRecvErrorCheckMsgObject,
                            recvMsgBuf,&actRecvMsgSize,
                            &remoteCoreId,
                            &remoteCoreEndPt,
                            timeout);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* 3. Receieve with NULL remote end point */
    status = RPMessage_recv(&gRecvErrorCheckMsgObject,
                            recvMsgBuf,
                            &actRecvMsgSize,
                            &remoteCoreId,
                            NULL,
                            SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* 4. Receieve with invalid parameters */
    status = RPMessage_recv(&gAckMsgObject,
                            recvMsgBuf,
                            &actRecvMsgSize,
                            &remoteCoreId,
                            NULL,
                            SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}

/* Ack message handler when messages are sent with rx notify handler registered, here after required messages are received semaphore is posted */
void test_rpmsgRxNotifyHandler(RPMessage_Object *obj, void *arg)
{
    Msg_BackToBack msg;
    uint16_t dataLen = sizeof(msg);
    uint16_t remoteCoreId;
    uint32_t remoteEndPt;
    int32_t status;

    status = RPMessage_recv(obj, &msg, &dataLen, &remoteCoreId, &remoteEndPt, 0);
    DebugP_assertNoLog(status == SystemP_SUCCESS);
    DebugP_assertNoLog(dataLen == sizeof(Msg_BackToBack));
    DebugP_assertNoLog(remoteEndPt == gServerEndPt);

    if(msg.curCount == (msg.maxCount-1) )
    {
        SemaphoreP_Object *pDoneSem = (SemaphoreP_Object *)arg;

        SemaphoreP_post(pDoneSem);
    }
}

/* In this test
    - we do message exchange with one core,
    - we use rx notify callback and see if it is getting invoked
    - we also test calling RPMessage_recv within the callback itself
 */
void test_rpmsgRxNotifyCallback(void *args)
{
    Test_Args *pTestArgs = (Test_Args*)args;
    uint16_t remoteCoreId = pTestArgs->remoteCoreId;
    uint32_t echoMsgCount = pTestArgs->echoMsgCount;
    uint32_t msg;
    int32_t status;

    for(msg=0; msg<echoMsgCount; msg++)
    {
        Msg_BackToBack msgObj;

        msgObj.curCount = msg;
        msgObj.maxCount = echoMsgCount;
        status = RPMessage_send(
            &msgObj, sizeof(msgObj),
            remoteCoreId, gServerEndPt,
            RPMessage_getLocalEndPt(&gRxNotifyAckMsgObject),
            SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    status = SemaphoreP_pend(&gRxNotifyAckDoneSem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)

/* Sender Task 1 for multi threaded test */
void TestIpcRpmsg_multipleEndPtSndTask1(void *args)
{
    char msgBuf[MAX_MSG_SIZE];
    char ackMsgBuf[MAX_MSG_SIZE];
    int32_t status; 
    uint32_t remoteCoreEndPt;
    uint16_t remoteCoreId, msgSize, ackMsgSize;
    uint32_t i;

    RPMessage_Object *pRpmsgObj = (RPMessage_Object *)args;
    snprintf(msgBuf, MAX_MSG_SIZE - 1, "A");
    msgBuf[MAX_MSG_SIZE - 1] = '\0';
    msgSize = strlen(msgBuf) + 1;

    /*Send message to the end point */
    DebugP_log("TestIpcRpmsg_concurrentEndptXfer: Sending data from task 1\r\n");
    for(i = 0; gRemoteCoreId[i] != CSL_CORE_ID_MAX; i++)
    {
#if defined(SOC_AM275X)

        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0) &&
            (gRemoteCoreId[i] != CSL_CORE_ID_C75SS1_0))
#else
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0))
#endif
        {
            status = RPMessage_send(
                    msgBuf, msgSize,
                    gRemoteCoreId[i], TestIpcRpmsg_remoteServiceEndPt1,
                    RPMessage_getLocalEndPt(pRpmsgObj),
                    ClockP_usecToTicks(RPMSG_SEND_TIMEOUT));
            TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
        }
    }
    DebugP_log("TestIpcRpmsg_concurrentEndptXfer: Receiving data at task 1\r\n");
    for(i = 0; gRemoteCoreId[i] != CSL_CORE_ID_MAX; i++)
    {
#if defined(SOC_AM275X)
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0) &&
            (gRemoteCoreId[i] != CSL_CORE_ID_C75SS1_0))
#else
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0))
#endif
        {
            ackMsgSize = sizeof(ackMsgBuf);
            status = RPMessage_recv(pRpmsgObj,
                                    ackMsgBuf, &ackMsgSize,
                                    &remoteCoreId, &remoteCoreEndPt,
                                    SystemP_WAIT_FOREVER);
            TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
            TEST_ASSERT_EQUAL_UINT16(TestIpcRpmsg_remoteServiceEndPt1, remoteCoreEndPt);
            TEST_ASSERT_EQUAL_UINT16(msgSize, ackMsgSize);
            TEST_ASSERT_EQUAL_INT32(0, strcmp(ackMsgBuf, msgBuf)); 
        }
    }
    SemaphoreP_post(&TestIpcRPMsg_sem);
}

/* Sender Task2 for multi threaded test */
void TestIpcRpmsg_multipleEndPtSndTask2(void *args)
{
    char msgBuf[MAX_MSG_SIZE];
    char ackMsgBuf[MAX_MSG_SIZE];
    int32_t status;
    uint32_t  remoteCoreEndPt;
    uint16_t remoteCoreId, msgSize, ackMsgSize;
    uint32_t i;

    RPMessage_Object *pRpmsgObj = (RPMessage_Object *)args;
    snprintf(msgBuf, MAX_MSG_SIZE - 1, "B");
    msgBuf[MAX_MSG_SIZE - 1] = '\0';
    msgSize = strlen(msgBuf) + 1;

    DebugP_log("TestIpcRpmsg_concurrentEndptXfer: Sending data from task 2\r\n");
    /*Send message to the end point */
    for(i = 0; gRemoteCoreId[i] != CSL_CORE_ID_MAX; i++)
    {
#if defined(SOC_AM275X)
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0) &&
            (gRemoteCoreId[i] != CSL_CORE_ID_C75SS1_0))
#else
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0))
#endif
        {
            status = RPMessage_send(
                    msgBuf, msgSize,
                    gRemoteCoreId[i], TestIpcRpmsg_remoteServiceEndPt2,
                    RPMessage_getLocalEndPt(pRpmsgObj),
                    ClockP_usecToTicks(RPMSG_SEND_TIMEOUT));
            TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
        }
    }
    DebugP_log("TestIpcRpmsg_concurrentEndptXfer: Receiving data at task 2\r\n");
    for(i = 0; gRemoteCoreId[i] != CSL_CORE_ID_MAX; i++)
    {
#if defined(SOC_AM275X)
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0) &&
            (gRemoteCoreId[i] != CSL_CORE_ID_C75SS1_0))
#else
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0))
#endif
        {
            ackMsgSize = sizeof(ackMsgBuf);
            status = RPMessage_recv(pRpmsgObj,
                                    ackMsgBuf, &ackMsgSize,
                                    &remoteCoreId, &remoteCoreEndPt,
                                    SystemP_WAIT_FOREVER);
            TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
            TEST_ASSERT_EQUAL_UINT16(TestIpcRpmsg_remoteServiceEndPt2, remoteCoreEndPt);
            TEST_ASSERT_EQUAL_UINT16(msgSize, ackMsgSize);
            TEST_ASSERT_EQUAL_INT32(0, strcmp(ackMsgBuf, msgBuf)); 
        }
    }
    SemaphoreP_post(&TestIpcRPMsg_sem);
}

/* This is the receiver task to echo back the data for mutiple enpoint tests */
void TestIpcRpmsg_multiplEndPointRecvTask(void *args)
{
    int32_t status;
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;
    char recvMsg[MAX_MSG_SIZE];
    RPMessage_Object *pRpmsgObj = (RPMessage_Object *)args;
    
    while(1)
    {
        recvMsgSize = sizeof(recvMsg);
        status = RPMessage_recv(pRpmsgObj,
            recvMsg, &recvMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            SystemP_WAIT_FOREVER);

        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
        DebugP_log("Remote: Message received at endpoint %d\r\n", 
                    RPMessage_getLocalEndPt(pRpmsgObj));

        DebugP_log("Remote: Echo back the same data received\r\n");
        status = RPMessage_send(
            recvMsg, recvMsgSize,
            remoteCoreId, remoteCoreEndPt,
            RPMessage_getLocalEndPt(pRpmsgObj),
            SystemP_WAIT_FOREVER);
    
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }
}

/* Notify handler 1 for 'TestIpcRpmsg_multipleEndpointsSnd' test */ 
void TestIpcRPMsg_multipleEndptRxNotifyHandler1(RPMessage_Object *obj, void *arg)
{   
    SemaphoreP_Object *pDoneSem = (SemaphoreP_Object *)arg;
    uint16_t remoteCoreId;
    uint16_t dataLen = (uint16_t) sizeof(TestIpcRPMsg_varRcvBuf);
    uint32_t remoteEndPt;
    int32_t status;

    status = RPMessage_recv(obj, TestIpcRPMsg_notifyRcvBuf, &dataLen, &remoteCoreId, &remoteEndPt, 0);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    TEST_ASSERT_EQUAL(remoteEndPt, gServerEndPt);

    /* Make sure that the last byte matches */
    TEST_ASSERT_EQUAL(TestIpcRPMsg_notifyRcvBuf[dataLen - 1], TestIpcRPMsg_varMsgPatterns[0]);
    SemaphoreP_post(pDoneSem);
}

/* Notify handler 2 for 'TestIpcRpmsg_multipleEndpointsSnd' test */ 
void TestIpcRPMsg_multipleEndptRxNotifyHandler2(RPMessage_Object *obj, void *arg)
{   
    SemaphoreP_Object *pDoneSem = (SemaphoreP_Object *)arg;
    uint16_t remoteCoreId;
    uint16_t dataLen = (uint16_t) sizeof(TestIpcRPMsg_varRcvBuf);
    uint32_t remoteEndPt;
    int32_t status;

    status = RPMessage_recv(obj, TestIpcRPMsg_notifyRcvBuf, &dataLen, &remoteCoreId, &remoteEndPt, 0);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    TEST_ASSERT_EQUAL(remoteEndPt, gServerEndPt);

    /* Make sure that the last byte matches */
    TEST_ASSERT_EQUAL(TestIpcRPMsg_notifyRcvBuf[dataLen - 1], TestIpcRPMsg_varMsgPatterns[1]);
    SemaphoreP_post(pDoneSem);
}

/* Notify handler 3 for 'TestIpcRpmsg_multipleEndpointsSnd' test */ 
void TestIpcRPMsg_multipleEndptRxNotifyHandler3(RPMessage_Object *obj, void *arg)
{   
    SemaphoreP_Object *pDoneSem = (SemaphoreP_Object *)arg;
    uint16_t remoteCoreId;
    uint16_t dataLen = (uint16_t) sizeof(TestIpcRPMsg_varRcvBuf);
    uint32_t remoteEndPt;
    int32_t status;

    status = RPMessage_recv(obj, TestIpcRPMsg_notifyRcvBuf, &dataLen, &remoteCoreId, &remoteEndPt, 0);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    TEST_ASSERT_EQUAL(remoteEndPt, gServerEndPt);

    /* Make sure that the last byte matches */
    TEST_ASSERT_EQUAL(TestIpcRPMsg_notifyRcvBuf[dataLen - 1], TestIpcRPMsg_varMsgPatterns[2]);
    SemaphoreP_post(pDoneSem);
}

/* Notify handler to read variable message of variable lengths */
void TestIpcRPMsg_varMsgRxNotifyHandler(RPMessage_Object *obj, void *arg)
{
    TestIpcRPMsg_varMsg msg;
    SemaphoreP_Object *pDoneSem = (SemaphoreP_Object *)arg;
    uint16_t remoteCoreId;
    uint16_t dataLen = (uint16_t) sizeof(TestIpcRPMsg_varMsg);
    uint32_t remoteEndPt;
    int32_t status;

    status = RPMessage_recv(obj, &msg, &dataLen, &remoteCoreId, &remoteEndPt, 0);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    TEST_ASSERT_EQUAL(remoteEndPt, gServerEndPt);

    /* Make sure that the last byte matches */
    TEST_ASSERT_EQUAL(msg.msgBuf[msg.msgSize - 1], TestIpcRPMsg_varMsgPatterns[msg.msgIndx]);
    SemaphoreP_post(pDoneSem);
}

/**
 * \brief Tests for concurrent sending and receiving 
 *  of data
 *
 * Test Category: Functionality
 *
 * This test spawns two sender tasks which sends data
 * data to the receiving endpoints(2 endpoints) on the
 * remote core. Upon receiving data the remote core echoes
 * the data back to the sending endpoint which then compares
 * the echoed back data and the original data
 *
 * The test ensures that the the IPC communication works for
 * multiple endpoints created on the same remote core.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters.
 *
 * \return None.
 */
void TestIpcRpmsg_concurrentEndptXfer(void *args)
{
    /* Create two tasks to receive messages */
    TaskP_Params taskParams1;
    TaskP_Params taskParams2;
    int32_t status;
    int32_t loopVar;
    
    /* Two rpmsg params to initialize the sender tasks */
    RPMessage_CreateParams createTaskParams1;
    RPMessage_CreateParams createTaskParams2;
   
    status =  SemaphoreP_constructCounting(&TestIpcRPMsg_sem, 0, 2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createTaskParams1);
    createTaskParams1.localEndPt = TestIpcRpmsg_hostClientEndPt1;
    status = RPMessage_construct(&TestIpcRPMsg_sndTaskObjects[0], &createTaskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams1);
    taskParams1.name = "MT_SEND_TASK1";
    taskParams1.stackSize = 8 * 1024;
    taskParams1.stack = TestIpcRPMsg_sndTasksStack[0];
    taskParams1.priority = 8U;
    taskParams1.args = &TestIpcRPMsg_sndTaskObjects[0];
    taskParams1.taskMain = TestIpcRpmsg_multipleEndPtSndTask1;
    DebugP_log("Creating sender task 1 for multithreaded test\r\n");

    status = TaskP_construct(&TestIpcRPMsg_sndTasks[0], &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createTaskParams2);
    createTaskParams2.localEndPt = TestIpcRpmsg_hostClientEndPt2;
    status = RPMessage_construct(&TestIpcRPMsg_sndTaskObjects[1], &createTaskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.name = "MT_SEND_TASK2";
    taskParams2.stackSize = 8 * 1024;
    taskParams2.stack = TestIpcRPMsg_sndTasksStack[1];
    taskParams2.priority = 8U;
    taskParams2.args = &TestIpcRPMsg_sndTaskObjects[1];
    taskParams2.taskMain = TestIpcRpmsg_multipleEndPtSndTask2;
    DebugP_log("Creating sender task 2 for multithreaded test\r\n");

    status = TaskP_construct(&TestIpcRPMsg_sndTasks[1], &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Create a counting semaphore to signal between the sending 
     * tasks and the test 
     */

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        status = SemaphoreP_pend(&TestIpcRPMsg_sem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(status, SystemP_SUCCESS);
        
    }

    SemaphoreP_destruct(&TestIpcRPMsg_sem);
    TaskP_destruct(&TestIpcRPMsg_sndTasks[0]);
    TaskP_destruct(&TestIpcRPMsg_sndTasks[1]);
}

/**
 * \brief Tests for sequential sending and receiving 
 *  of data
 *
 * Test Category: Functionality
 *
 * This test sends data to the remote endpoint one 
 * after the othe. Upon receiving data the remote core echoes
 * the data back to the sending endpoint which then compares
 * the echoed back data and the original data
 *
 * The test ensures that the the IPC communication works for
 * multiple endpoints created on the same remote core.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters.
 *
 * \return None.
 */
void TestIpcRPMsg_sndMsgToTasks(void *args)
{
    RPMessage_CreateParams createParams;
    char msgBuf[2][MAX_MSG_SIZE];
    char ackMsgBuf[2][MAX_MSG_SIZE];
    int32_t status;
    uint16_t remoteCoreId, msgSize, ackMsgSize;
    uint32_t remoteCoreEndPt;
    uint32_t i;
    
    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = TestIpcRpmsg_hostEndPt;
    status = RPMessage_construct(&TestIpcRpmsg_hostMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);
    
    snprintf(msgBuf[0], MAX_MSG_SIZE - 1, "A");
    msgBuf[0][MAX_MSG_SIZE - 1] = '\0';
    msgSize = strlen(msgBuf[0]) + 1;

    /* Send message to the first endpoint */
    for(i = 0; gRemoteCoreId[i] != CSL_CORE_ID_MAX; i++)
    {
#if defined(SOC_AM275X)
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0) &&
            (gRemoteCoreId[i] != CSL_CORE_ID_C75SS1_0))
#else
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0))
#endif
        {
            status = RPMessage_send(
                    msgBuf[0], msgSize,
                    gRemoteCoreId[i], TestIpcRpmsg_remoteServiceEndPt1,
                    RPMessage_getLocalEndPt(&TestIpcRpmsg_hostMsgObject),
                    ClockP_usecToTicks(RPMSG_SEND_TIMEOUT));
            TEST_ASSERT_EQUAL(SystemP_SUCCESS, status); 
        }
    }
    /* Wait for the reponses from the first endpoints */
    for(i = 0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++)
    {
#if defined(SOC_AM275X)
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0) &&
            (gRemoteCoreId[i] != CSL_CORE_ID_C75SS1_0))
#else
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0))
#endif
        {
            ackMsgSize = sizeof(ackMsgBuf[0]);
            status = RPMessage_recv(&TestIpcRpmsg_hostMsgObject,
                                ackMsgBuf[0], &ackMsgSize,
                                &remoteCoreId, &remoteCoreEndPt,
                                SystemP_WAIT_FOREVER);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
            TEST_ASSERT_EQUAL_UINT16(TestIpcRpmsg_remoteServiceEndPt1, remoteCoreEndPt);
            TEST_ASSERT_EQUAL_UINT16(msgSize, ackMsgSize);
            TEST_ASSERT_EQUAL_INT32( 0, strcmp(ackMsgBuf[0], msgBuf[0]));
        }
    }
    
    snprintf(msgBuf[1], MAX_MSG_SIZE, "B");
    msgBuf[1][MAX_MSG_SIZE - 1] = '\0';
    msgSize = strlen(msgBuf[1]) + 1;

    /* Send message to the second endpoint */
    for(i = 0; gRemoteCoreId[i] != CSL_CORE_ID_MAX; i++)
    {
#if defined(SOC_AM275X)
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0) &&
            (gRemoteCoreId[i] != CSL_CORE_ID_C75SS1_0))
#else
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0))
#endif
        {
            status = RPMessage_send(
                    msgBuf[1], msgSize,
                    gRemoteCoreId[i], TestIpcRpmsg_remoteServiceEndPt2,
                    RPMessage_getLocalEndPt(&TestIpcRpmsg_hostMsgObject),
                    ClockP_usecToTicks(RPMSG_SEND_TIMEOUT));
            TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
                    
        }
    }
    /* Wait for the reponses from the first endpoints */
    for(i = 0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++)
    {
#if defined(SOC_AM275X)
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0) &&
            (gRemoteCoreId[i] != CSL_CORE_ID_C75SS1_0))
#else
        if((gRemoteCoreId[i] != IpcNotify_getSelfCoreId()) && (gRemoteCoreId[i] != CSL_CORE_ID_C75SS0_0))
#endif
        {
            ackMsgSize = sizeof(ackMsgBuf[1]);
            status = RPMessage_recv(&TestIpcRpmsg_hostMsgObject,
                                ackMsgBuf[1], &ackMsgSize,
                                &remoteCoreId, &remoteCoreEndPt,
                                SystemP_WAIT_FOREVER);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
            TEST_ASSERT_EQUAL_UINT16(TestIpcRpmsg_remoteServiceEndPt2, remoteCoreEndPt);
            TEST_ASSERT_EQUAL_UINT16(msgSize, ackMsgSize);
            TEST_ASSERT_EQUAL_INT32( 0, strcmp(ackMsgBuf[1], msgBuf[1]));
        }
    }
}

/**
 * \brief Tests for mutiple endpoint send and receive
 * using noify callabck
 *
 * Test Category: Functionality
 *
 * This test sends data to the remote endpoint one 
 * after the other. Upon receiving data the remote core
 * will compare the last byte.
 *
 * The test ensures that the the IPC communication works for
 * multiple endpoints created on the same remote core.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters.
 *
 * \return None.
 */
void TestIpcRpmsg_multipleEndpointsSnd(void *args)
{
    Test_Args *pTestArg = (Test_Args *)args;
    uint16_t remoteCoreId = pTestArg->remoteCoreId;
    int32_t status, oldDebugLogZone;
    uint16_t dataLen;

    /* Disable warning logs since we are testing for those, so it will clutter the output */
    oldDebugLogZone = DebugP_logZoneDisable(DebugP_LOG_ZONE_WARN);

    memset(TestIpcRPMsg_notifySndBuf, TestIpcRPMsg_varMsgPatterns[0], sizeof(TestIpcRPMsg_notifySndBuf));
    dataLen = (uint16_t)sizeof(TestIpcRPMsg_notifySndBuf);
    
    status = RPMessage_send(
        TestIpcRPMsg_notifySndBuf, dataLen,
        remoteCoreId, gServerEndPt,
        RPMessage_getLocalEndPt(&TestIpcRPMsg_multipleEndptRcvObject1),
        ClockP_usecToTicks(RPMSG_SEND_TIMEOUT));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_pend(&TestIpcRPMsg_multipleEndptDoneSem1, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    memset(TestIpcRPMsg_notifySndBuf, TestIpcRPMsg_varMsgPatterns[1], sizeof(TestIpcRPMsg_notifySndBuf));
    dataLen = (uint16_t)sizeof(TestIpcRPMsg_notifySndBuf);
    
    status = RPMessage_send(
        TestIpcRPMsg_notifySndBuf, dataLen,
        remoteCoreId, gServerEndPt,
        RPMessage_getLocalEndPt(&TestIpcRPMsg_multipleEndptRcvObject2),
        ClockP_usecToTicks(RPMSG_SEND_TIMEOUT));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_pend(&TestIpcRPMsg_multipleEndptDoneSem2, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    memset(TestIpcRPMsg_notifySndBuf, TestIpcRPMsg_varMsgPatterns[2], sizeof(TestIpcRPMsg_notifySndBuf));
    dataLen = (uint16_t)sizeof(TestIpcRPMsg_notifySndBuf);
    
    status = RPMessage_send(
        TestIpcRPMsg_notifySndBuf, dataLen,
        remoteCoreId, gServerEndPt,
        RPMessage_getLocalEndPt(&TestIpcRPMsg_multipleEndptRcvObject3),
        ClockP_usecToTicks(RPMSG_SEND_TIMEOUT));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    
    status = SemaphoreP_pend(&TestIpcRPMsg_multipleEndptDoneSem3, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_logZoneRestore(oldDebugLogZone);
}

/**
 * \brief Tests for variable message size send and receive
 *
 * Test Category: Functionality
 *
 * This test sends data to the remote endpoint one 
 * after the other of varying message sizes.
 * Upon receiving data the remote core will compare the last byte.
 *
 * The test ensures that the the IPC communication works for
 * thr specified remote enpoint endpoints on the remote core.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters.
 *
 * \return None.
 */
void TestIpcRpmsg_variableMsgSizeSnd(void *args)
{
    Test_Args *pTestArgs = (Test_Args*)args;
    TestIpcRPMsg_varMsg varMsgObj;
    uint16_t remoteCoreId = pTestArgs->remoteCoreId;
    uint32_t echoMsgCount = pTestArgs->echoMsgCount;
    uint32_t msg, oldDebugLogZone;
    int32_t status;

    /* Disable warning logs since we are testing for those, so it will clutter the output */
    oldDebugLogZone = DebugP_logZoneDisable(DebugP_LOG_ZONE_WARN);

    for(msg = 0; msg < echoMsgCount; msg++)
    {
        if(msg == 0)
        {
            varMsgObj.msgBuf = &TestIpcRPMsg_varSndBuf[80];
        }
        else if(msg == 1)
        {
            varMsgObj.msgBuf = &TestIpcRPMsg_varSndBuf[48];
        }
        else
        {
            varMsgObj.msgBuf = TestIpcRPMsg_varSndBuf;
        }
        memset(varMsgObj.msgBuf, TestIpcRPMsg_varMsgPatterns[msg], TestIpcRPMsg_varMsgSizes[msg]);
        varMsgObj.msgSize = TestIpcRPMsg_varMsgSizes[msg];
        varMsgObj.msgIndx = msg;

        status = RPMessage_send(
            &varMsgObj, sizeof(TestIpcRPMsg_varMsg),
            remoteCoreId, gServerEndPt,
            RPMessage_getLocalEndPt(&TestIpcRPMsg_varMsgRcvObject),
            SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /*Wait for the semaphore to bbe released after each iteration */
        status = SemaphoreP_pend(&TestIpcRPMsg_varMsgDoneSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }
    DebugP_logZoneRestore(oldDebugLogZone);
}
#endif
#if !defined(SOC_AM62X) &&  !defined(SOC_AM62PX) && !defined(SOC_J722S)
void test_rpmsgErrorChecks(void *args)
{
    int32_t status;
    uint32_t msg, fifoFullCount, msgCount, oldDebugLogZone;
    uint16_t msgSize, remoteCoreId;
    uint32_t remoteEndPt;
    uint32_t txDataBuff[100];
    uint32_t rxDataBuff[100];
    RPMessage_CreateParams rpmsgPrm;
    RPMessage_Params rpmsgParams;
    Msg_BackToBack msgObj;

    /* disable error and warning logs since we are testing for those, so it will clutter the output */
    oldDebugLogZone = DebugP_logZoneDisable(DebugP_LOG_ZONE_WARN | DebugP_LOG_ZONE_ERROR);

    /* message to send, set values such ack callback wont post a semaphore */
    msgObj.curCount = 0;
    msgObj.maxCount = 10;

    /* invalid local end point */
    RPMessage_CreateParams_init(&rpmsgPrm);
    rpmsgPrm.localEndPt = RPMESSAGE_MAX_LOCAL_ENDPT;
    status = RPMessage_construct(&gNullRpmsgObj, &rpmsgPrm);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* already created end point */
    RPMessage_CreateParams_init(&rpmsgPrm);
    rpmsgPrm.localEndPt = gServerEndPt;
    status = RPMessage_construct(&gNullRpmsgObj, &rpmsgPrm);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* annouce to invalid core ID */
    status = RPMessage_announce(CSL_CORE_ID_MAX, 0, "test");
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* send to invalid core ID */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_MAX,
                    gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    #if !defined(SOC_AM62AX) && !defined(SOC_AM62DX) && !defined(SOC_AM62X) && !defined(SOC_AM62PX) && !defined(SOC_J722S)
    /* send with NULL data */
    status = RPMessage_send(NULL, sizeof(msgObj), CSL_CORE_ID_R5FSS0_1,
                    gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* send with zero size data  */
    status = RPMessage_send(&msgObj, 0, CSL_CORE_ID_R5FSS0_1,
                    gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* send to end pt that is not created on remote,
       this is allowed, recevied message is dropped */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_R5FSS0_1,
                    gNullEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    /* set reply to end pt that is not created on local,
       this is allowed, ack message is dropped */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_R5FSS0_1,
                    gServerEndPt, gNullEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* send back to back messages without waiting, there should be timeout conditon
       due to queue full many times
     */
    fifoFullCount = 0;
    msgCount = 1000;
    for(msg=0; msg<msgCount; msg++)
    {
        status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_R5FSS0_1,
                        gServerEndPt, gAckEndPt, SystemP_NO_WAIT);
        if(status == SystemP_TIMEOUT)
        {
            fifoFullCount++;
        }
    }
    /* send one message waiting for space in FIFO just to check a success case after failure */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_R5FSS0_1,
                        gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("[TEST IPC RPMSG] Messages sent = %d \r\n", msgCount);
    DebugP_log("[TEST IPC RPMSG] FIFO Full count = %d \r\n", fifoFullCount);

    TEST_ASSERT_GREATER_OR_EQUAL_UINT32(0, fifoFullCount);

    #elif defined(SOC_AM62AX) || defined(SOC_AM62DX)
    /* send with NULL data */
    status = RPMessage_send(NULL, sizeof(msgObj), CSL_CORE_ID_A53SS0_0,
                    gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* send with zero size data  */
    status = RPMessage_send(&msgObj, 0, CSL_CORE_ID_A53SS0_0,
                    gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* send to end pt that is not created on remote,
       this is allowed, recevied message is dropped */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_A53SS0_0,
                    gNullEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    /* set reply to end pt that is not created on local,
       this is allowed, ack message is dropped */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_A53SS0_0,
                    gServerEndPt, gNullEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* send back to back messages without waiting, there should be timeout conditon
       due to queue full many times
     */
    fifoFullCount = 0;
    msgCount = 1000;
    for(msg=0; msg<msgCount; msg++)
    {
        status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_A53SS0_0,
                        gServerEndPt, gAckEndPt, SystemP_NO_WAIT);
        if(status == SystemP_TIMEOUT)
        {
            fifoFullCount++;
        }
    }
    /* send one message waiting for space in FIFO just to check a success case after failure */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_A53SS0_0,
                        gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("[TEST IPC RPMSG] Messages sent = %d \r\n", msgCount);
    DebugP_log("[TEST IPC RPMSG] FIFO Full count = %d \r\n", fifoFullCount);

    TEST_ASSERT_GREATER_OR_EQUAL_UINT32(0, fifoFullCount);
    #elif defined(SOC_AM62PX)
    /* send with NULL data */
    status = RPMessage_send(NULL, sizeof(msgObj), CSL_CORE_ID_MCU_R5FSS0_0,
                    gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* send with zero size data  */
    status = RPMessage_send(&msgObj, 0, CSL_CORE_ID_MCU_R5FSS0_0,
                    gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* send to end pt that is not created on remote,
       this is allowed, recevied message is dropped */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_MCU_R5FSS0_0,
                    gNullEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    /* set reply to end pt that is not created on local,
       this is allowed, ack message is dropped */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_MCU_R5FSS0_0,
                    gServerEndPt, gNullEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* send back to back messages without waiting, there should be timeout conditon
       due to queue full many times
     */
    fifoFullCount = 0;
    msgCount = 1000;
    for(msg=0; msg<msgCount; msg++)
    {
        status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_MCU_R5FSS0_0,
                        gServerEndPt, gAckEndPt, SystemP_NO_WAIT);
        if(status == SystemP_TIMEOUT)
        {
            fifoFullCount++;
        }
    }
    /* send one message waiting for space in FIFO just to check a success case after failure */
    status = RPMessage_send(&msgObj, sizeof(msgObj), CSL_CORE_ID_MCU_R5FSS0_0,
                        gServerEndPt, gAckEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("[TEST IPC RPMSG] Messages sent = %d \r\n", msgCount);
    DebugP_log("[TEST IPC RPMSG] FIFO Full count = %d \r\n", fifoFullCount);

    TEST_ASSERT_GREATER_OR_EQUAL_UINT32(0, fifoFullCount);
    #endif


     /* use recv API on a end point which is created in handler mode */
    status = RPMessage_recv(&gAckMsgObject, &msgObj, &msgSize, &remoteCoreId, &remoteEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* recv error checks, first create rpmsg object */
    RPMessage_CreateParams_init(&rpmsgPrm);
    rpmsgPrm.localEndPt = gNullEndPt;
    status = RPMessage_construct(&gNullRpmsgObj, &rpmsgPrm);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* parameter checks */
    status = RPMessage_recv(&gNullRpmsgObj, NULL, &msgSize, &remoteCoreId, &remoteEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    status = RPMessage_recv(&gNullRpmsgObj, &msgObj, NULL, &remoteCoreId, &remoteEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    status = RPMessage_recv(&gNullRpmsgObj, &msgObj, &msgSize, NULL, &remoteEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    status = RPMessage_recv(&gNullRpmsgObj, &msgObj, &msgSize, &remoteCoreId, NULL, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    /* timeout check */
    status = RPMessage_recv(&gNullRpmsgObj, &msgObj, &msgSize, &remoteCoreId, &remoteEndPt, 10);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);
    status = RPMessage_recv(&gNullRpmsgObj, &msgObj, &msgSize, &remoteCoreId, &remoteEndPt, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* unblock test, post unblock and then waitforever, it should return with a timeout status */
    RPMessage_unblock(&gNullRpmsgObj);
    status = RPMessage_recv(&gNullRpmsgObj, &msgObj, &msgSize, &remoteCoreId, &remoteEndPt, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /*De-init properly initilaized RPMsg Object*/
    RPMessage_deInit();

    /*Re-initialize again with faulty parameter*/
    RPMessage_Params_init(&rpmsgParams);
#if !defined(SOC_AM275X)
    rpmsgParams.vringTxBaseAddr[CSL_CORE_ID_A53SS0_0] = (uintptr_t)&txDataBuff;
    rpmsgParams.vringRxBaseAddr[CSL_CORE_ID_A53SS0_0] = (uintptr_t)&rxDataBuff;
#else
    rpmsgParams.vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)&txDataBuff;
    rpmsgParams.vringRxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)&rxDataBuff;
#endif
    rpmsgParams.vringSize = 1;

    status = RPMessage_init(&rpmsgParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /*De-init properly initilaized RPMsg Object*/
    RPMessage_deInit();

    /*Re-initialize again with faulty parameter*/
    RPMessage_Params_init(&rpmsgParams);

#if !defined(SOC_AM275X)
    rpmsgParams.vringTxBaseAddr[CSL_CORE_ID_A53SS0_0] = (uintptr_t)&txDataBuff;
#else
    rpmsgParams.vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)&txDataBuff;
#endif
    rpmsgParams.vringTxBaseAddr[gMainCoreId] = (uintptr_t)&txDataBuff;
    rpmsgParams.vringRxBaseAddr[gMainCoreId] = (uintptr_t)&rxDataBuff;

    status = RPMessage_init(&rpmsgParams);

    RPMessage_deInit();

    rpmsgParams.vringTxBaseAddr[CSL_CORE_ID_HSM_M4FSS0_0] = (uintptr_t)&txDataBuff;
    rpmsgParams.vringRxBaseAddr[CSL_CORE_ID_HSM_M4FSS0_0] = (uintptr_t)&rxDataBuff;

    status = RPMessage_init(&rpmsgParams);

    RPMessage_deInit();

    rpmsgParams.vringTxBaseAddr[gMainCoreId] = (uintptr_t)&txDataBuff;
    status = RPMessage_init(&rpmsgParams);

    /*This will timeout*/
    RPMessage_deInit();
#if !defined(SOC_AM275X)
    uint32_t timeout = 10;
    /*For better bracnh coverage*/
    /*Calling this API without any resource table linked*/

    status = RPMessage_waitForLinuxReady(timeout);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    rpmsgParams.linuxResourceTable = &gRPMessage_linuxResourceTable;
    rpmsgParams.linuxCoreId = CSL_CORE_ID_A53SS0_0;
    RPMessage_init(&rpmsgParams);
    status = RPMessage_waitForLinuxReady(timeout);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);
#endif
    /* Dynamic analysis test - Calling RPMsg Destruct with faulty parameters*/
    RPMessage_Object faultyMsgObject;

    /* Setting faultyMsgObject to 0x4A to induce the failure
    localEndPt > RPMESSAGE_MAX_LOCAL_ENDPT from RPMessage_destruct*/
    memset(&faultyMsgObject, 0x4A, sizeof(faultyMsgObject));
    RPMessage_destruct(&faultyMsgObject);

    /* cleanup */
    RPMessage_destruct(&gNullRpmsgObj);

    DebugP_logZoneRestore(oldDebugLogZone);
}
#endif

/*
 * In this test
 * - This test_rpmsgValidParams is to validate RPMessage by passing the valid parameters to
 *   the function and executing the neccessary conditions for statement and branch coverage
 * - Passing invalid parameters to fail the message core end point
 */
#if defined(SOC_J722S)
static void test_rpmsgValidParams(void *args)
{
    int data = 0U;
    void* ptrdata = &data;
    RPMessage_Core *coreObj = &gIpcRpmsgCtrl.coreObj[0];
    RPMessage_Vring *vringObj = &coreObj->vringTxObj;

    /* Passing valid parameters with vringObj->lastAvailIdx and vringObj->avail->idx by
    setting zero to get the added buffer */
    vringObj->lastAvailIdx = 0U;
    vringObj->avail->idx = 0U;
    RPMessage_vringGetEmptyTxBuf(0U, NULL, 0U);

    /* Passing valid parameters with vringObj->lastAvailIdx and vringObj->avail->idx by
    setting zero to make isNewEmptyBuf to zero */
    RPMessage_vringCheckEmptyTxBuf(0U);

    /* Passing the NULL parameter with coreObj->freeQ by setting zero
    to make coreObj->freeQAllocPending to one*/
    coreObj->freeQ = (RPMessage_Queue){0U};
    RPMessage_allocEndPtMsg(0U);

    /* Passing valid parameters to satisfy the if condition and to execute the RPMessage_vringGet */
    RPMessage_send(ptrdata, 512U, 2U, 0U, 0U, 0U);

    /* Passing invalid parameters to fail the message core end point  */
    RPMessage_send(ptrdata, 512U, CSL_CORE_ID_MAX, 0U, 0U, 0U);
}
#endif

/* This code executes on remote core, i.e not on main core */
void test_ipc_remote_core_start()
{
    UNITY_BEGIN();

    /* announce endpt to main core, this is need for annouce test */
    RPMessage_announce(gMainCoreId, RPMessage_getLocalEndPt(&gServerMsgObject), SERVER_NAME);

    /* Run any to any test */
    test_rpmsgAnyToAny(NULL);

    /* wait for ever, now onwards main core will initaite all requests
     * to the server task, which will simply echo the messages
     */
    ClockP_sleep(SystemP_WAIT_FOREVER);

    UNITY_END();
}

/* This code executes on main core, i.e not on remote core */
void test_ipc_main_core_start()
{

    Test_Args testArgs;

    #if defined(BUILD_C7X_AS_MASTER)
    DebugP_log("This test is build with c7x as master\n\r");
    #endif

    #if defined(BUILD_MCU_R5F_AS_MASTER)
    DebugP_log("This test is build with MCU R5F as master\n\r");
    #endif

    #if defined(BUILD_A53_AS_MASTER)
    DebugP_log("This test is build with A53 as master\n\r");
    #endif

    UNITY_BEGIN();

    /* These MUST be the first tests to run */
    RUN_TEST(test_rpmsgControlEndPt, 2458, NULL);
    RUN_TEST(test_rpmsgAnyToAny, 2463, NULL);

    /* now you can comment tests if needed to debug a specific test */
    testArgs.echoMsgCount = 1000; /* this value is used by all later tests */
    /* performance test with minimum payload size */
    testArgs.msgSize = 4;

    #if !defined(SOC_AM62AX) && !defined(SOC_AM62DX) && !defined(SOC_AM62X) && !defined(SOC_AM62PX) && !defined(SOC_AM275X) && !defined(SOC_J722S)
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    RUN_TEST(test_rpmsgOneToOne, 298, &testArgs);
    #endif

    #if defined(SOC_AM64X) || defined(SOC_AM243X) || defined(SOC_AM263X)
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_0;
    RUN_TEST(test_rpmsgOneToOne, 300, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_1;
    RUN_TEST(test_rpmsgOneToOne, 301, &testArgs);
    #endif

    #if defined(SOC_AM64X) || defined(SOC_AM243X) || defined(SOC_AM62X)
    testArgs.remoteCoreId = CSL_CORE_ID_M4FSS0_0;
    RUN_TEST(test_rpmsgOneToOne, 2465, &testArgs);
    #endif

    #if defined(SOC_AM64X) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62X)
#if !defined(BUILD_A53_AS_MASTER)
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
#endif
    #endif

    #if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)
    testArgs.echoMsgCount = 3;
#if !defined(SOC_AM275X)

    /* Test cases for am62ax and am62dx */
#if defined(BUILD_MCU_R5F_AS_MASTER)

    /* Variable Message send test with MCU R5F as master */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0; 
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9736, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9737, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9738, &testArgs);
#elif defined(BUILD_C7X_AS_MASTER)

    /* Variable message send test with C7x as master */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0; 
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9733, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9734, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9735, &testArgs);
#elif defined(BUILD_A53_AS_MASTER)

    /* Variable message send test with A53 as master */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0; 
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9813, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9814, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9815, &testArgs);
#else

    /* Variable message send test with R5F as master */
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9726, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9727, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9728, &testArgs);
#endif
#else
    
    /* Test cases for AM275X */
#if !defined(BUILD_C7X_AS_MASTER)

    /* Test cases with R5FSS0_0 as master */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9825, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9826, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_1;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9827, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9828, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS1_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9829, &testArgs);
#else

    /* Test cases with C75SS0_0 as master */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9830, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9831, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_1;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9832, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9833, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS1_0;
    RUN_TEST(TestIpcRpmsg_variableMsgSizeSnd, 9834, &testArgs);
#endif
#endif

    /* The following test cases works in AM62AX but fails in AM62DX 
     * and AM275X
     */
#if !defined(SOC_AM275X)
    RUN_TEST(TestIpcRPMsg_sndMsgToTasks, 9730, &testArgs);
#endif
#if !defined(SOC_AM62DX) && !defined(SOC_AM275X)
    RUN_TEST(TestIpcRpmsg_concurrentEndptXfer, 9731, &testArgs);
#endif

    /* This test case hangs when executed
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    RUN_TEST(TestIpcRpmsg_multipleEndpointsSnd, 9729, &testArgs);
    */
    #endif

    #if defined(SOC_AM62X)
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_1;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    #endif

    #if defined(SOC_AM273X) || defined(SOC_AWR294X)
    testArgs.remoteCoreId = CSL_CORE_ID_C66SS0;
    RUN_TEST(test_rpmsgOneToOne, 300, &testArgs);
    #endif

    /* performance test with varying payload size */
    #if !defined(SOC_AM62AX) &&  !defined(SOC_AM62DX) && !defined(SOC_AM62X) && !defined(SOC_AM62PX) && !defined(SOC_AM275X) && !defined(SOC_J722S)
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 6230, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 6225, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 6232, &testArgs);
    #endif

    #if defined(SOC_AM64X) || defined(SOC_AM243X) || defined(SOC_AM62X)
    /* performance test with varying payload size */
    testArgs.remoteCoreId = CSL_CORE_ID_M4FSS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 2466, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_M4FSS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 2467, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_M4FSS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 2468, &testArgs);
    #endif

    #if defined(SOC_AM64X) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62X)
    /* performance test with varying payload size */

#if !defined(BUILD_A53_AS_MASTER)
    /* These tests should only run A53 is not master */
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 2464, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 2732, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 2734, &testArgs);
#endif
    #endif

    #if defined(SOC_AM62X)
    /* performance test with varying payload size */
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_1;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 2464, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_1;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 2732, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_1;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 2734, &testArgs);
    #endif

    #if defined(SOC_AM62AX) || defined(SOC_AM62DX)
#if defined(BUILD_MCU_R5F_AS_MASTER)
    
    /* MCU R5F as master and R5F as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9739, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9740, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9741, &testArgs);

    /* MCU R5F as master and C7x as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9742, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9743, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9744, &testArgs);

    /* MCU R5F as master and A53 as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9745, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9746, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9747, &testArgs);
#elif defined(BUILD_C7X_AS_MASTER)

    /* C7x as master and R5F as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9748, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9749, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9750, &testArgs);

    /* C7x as master and MCU R5F as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9751, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9752, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9753, &testArgs);

    /* C7x as master and MCU A53 as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9754, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9755, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9756, &testArgs);
#elif defined(BUILD_A53_AS_MASTER)

    /* A53 as master and R5F as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9816, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9817, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9818, &testArgs);

    /* A53 as master and MCU R5F as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9819, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9820, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9821, &testArgs);

    /* A53 as master and C75 as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9822, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9823, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9824, &testArgs);
#else 

    /* R5F as master and MCU R5F as remote */
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 2713, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 2712, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 2711, &testArgs);
#endif
    #endif

    #if defined(SOC_AM62PX)
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 2713, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 2712, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 2711, &testArgs);
    #endif

    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    testArgs.msgSize = 128;
    testArgs.echoMsgCount = 1;
#if defined(BUILD_MCU_R5F_AS_MASTER)
    
    /* Test error checks with MCU R5F as master */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    RUN_TEST(test_rpmsgRecvErrorChecks, 8030, &testArgs);
#else

    /* Test error checks with R5F as master */
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    RUN_TEST(test_rpmsgRecvErrorChecks, 5671, &testArgs);
#endif
    #endif

    #if defined(SOC_J722S)
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 128;
    testArgs.echoMsgCount = 1;
    RUN_TEST(test_rpmsgRecvErrorChecks, 18761, &testArgs);
    #endif

    #if !defined(SOC_AM62AX) && !defined(SOC_AM62DX) && !defined(SOC_AM62X) && !defined(SOC_AM62PX) && !defined(SOC_AM275X) && !defined(SOC_J722S)
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 4;
    RUN_TEST(test_rpmsgOneToOneBackToBack, 305, &testArgs);
    #endif

    #if defined(SOC_AM275X)
#if !defined(BUILD_C7X_AS_MASTER)

    /* Test cases with R5F as master */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 6224, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 6225, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 6226, &testArgs);

    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 6227, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 6228, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 6229, &testArgs);

    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_1;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 6230, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_1;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 6231, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_1;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 6232, &testArgs);

    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 6233, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 6234, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 6235, &testArgs);

    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS1_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 6236, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS1_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 6237, &testArgs);
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS1_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 6238, &testArgs);
#else

    /* Test cases with C7X as master */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9835, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9836, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9837, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9838, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9839, &testArgs);
    
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9840, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9841, &testArgs);
    
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9842, &testArgs);
    
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9843, &testArgs);
    
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_1;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9844, &testArgs);
   
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_1;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9845, &testArgs);
  
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS1_1;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9846, &testArgs); 

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS1_0;
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 9847, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS1_0;
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 9848, &testArgs);

    testArgs.remoteCoreId = CSL_CORE_ID_C75SS1_0;
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 9849, &testArgs);
#endif
    #endif

    #if defined(SOC_AM64X) || defined(SOC_AM243X)
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_M4FSS0_0;
    testArgs.msgSize = 4;
    RUN_TEST(test_rpmsgOneToOneBackToBack, 1823, &testArgs);
    #endif

    #if defined(SOC_AM64X) || defined(SOC_AM62AX) || defined(SOC_AM62DX)

    /* back to back message send and handler mode rx tests */
    testArgs.msgSize = 4;
#if defined(BUILD_A53_AS_MASTER)
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    RUN_TEST(test_rpmsgOneToOneBackToBack, 8000, &testArgs);
#elif defined(BUILD_C7X_AS_MASTER)
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    RUN_TEST(test_rpmsgOneToOneBackToBack, 8000, &testArgs);
#elif defined(BUILD_MCU_R5F_AS_MASTER)
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    RUN_TEST(test_rpmsgOneToOneBackToBack, 8000, &testArgs);
#else
    testArgs.remoteCoreId = CSL_CORE_ID_A53SS0_0;
    RUN_TEST(test_rpmsgOneToOneBackToBack, 1874, &testArgs);
#endif
    #endif

    #if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    /* back to back message send and handler mode rx tests */
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 4;
    //RUN_TEST(test_rpmsgOneToOneBackToBack, 1874, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 4;
    //RUN_TEST(test_rpmsgOneToOneBackToBack, 1874, &testArgs);
    #endif

    #if !defined(SOC_AM62AX) && !defined(SOC_AM62DX) && !defined(SOC_AM62X) && !defined(SOC_AM62PX) && !defined(SOC_AM275X) && !defined(SOC_J722S)
    /* rx notify callback tests */
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_1;
    testArgs.msgSize = 4;
    testArgs.echoMsgCount = 1000;
    RUN_TEST(test_rpmsgRxNotifyCallback, 2464, &testArgs);
    #endif

    #if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62PX)
    /* rx notify callback tests */
#if !defined(BUILD_MCU_R5F_AS_MASTER)
    testArgs.msgSize = 4;
    testArgs.echoMsgCount = 1;
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    RUN_TEST(test_rpmsgRxNotifyCallback, 2464, &testArgs);
#endif
    #endif

    #if defined(SOC_AM62X)
    /* rx notify callback tests */
    testArgs.remoteCoreId = CSL_CORE_ID_M4FSS0_0;
    testArgs.msgSize = 4;
    testArgs.echoMsgCount = 1000;
    //RUN_TEST(test_rpmsgRxNotifyCallback, 2464, &testArgs);
    #endif

    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    testArgs.msgSize = INVALID_MSG_SIZE;
    testArgs.echoMsgCount = 512;
#if defined(BUILD_MCU_R5F_AS_MASTER)
    testArgs.remoteCoreId = CSL_CORE_ID_R5FSS0_0;
    RUN_TEST(test_rpmsgSendErrorChecks, 8000, &testArgs);
#else
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    RUN_TEST(test_rpmsgSendErrorChecks, 5649, &testArgs);
#endif
    #endif

    #if defined(SOC_J722S)
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = INVALID_MSG_SIZE;
    testArgs.echoMsgCount = 512;
    RUN_TEST(test_rpmsgSendErrorChecks, 18760, &testArgs);
    #endif

    #if !defined(SOC_AM62X) && !defined(SOC_AM62PX) && !defined(SOC_J722S)

    /* error condition checks */
#if !defined(BUILD_A53_AS_MASTER)
#if !defined(SOC_AM275X) && !defined(BUILD_C75X_AS_MASTER)
    RUN_TEST(test_rpmsgErrorChecks, 2456, NULL);
#endif
#endif
    #endif

    #if defined(SOC_J722S)
    testArgs.remoteCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    testArgs.msgSize = 4;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_MAIN_R5FSS0_0;
    testArgs.msgSize = 4;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS0_0;
    testArgs.msgSize = 4;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.remoteCoreId = CSL_CORE_ID_C75SS1_0;
    testArgs.msgSize = 4;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 32;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 64;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    testArgs.msgSize = 112;
    RUN_TEST(test_rpmsgOneToOne, 1870, &testArgs);
    RUN_TEST(test_rpmsgValidParams, 18765, NULL);
    #endif

#if defined(BUILD_C7X_AS_MASTER) && defined(SOC_AM275X)
    DebugP_log("\n[TEST IPC RPMSG] End of test\r\n\n");
#else
    /* Print performance numbers. */
    uint32_t i;
    DebugP_log("\n[TEST IPC RPMSG] Performance Numbers Print Start\r\n\n");
    DebugP_log("Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count\r\n");
    DebugP_log("------------|-------------|--------------|------------------------------|------------------|--------------\r\n");
    for (i=0; i<gIpcPerfCnt; i++) {
        DebugP_log("%12s|%13s|%14d|%30.3f|%18" PRId64 "|%13d\r\n", SOC_getCoreName(gMainCoreId), SOC_getCoreName(gIpcPerfObj[i].remoteCoreId),
            gIpcPerfObj[i].msgSize,
            ((float)(gIpcPerfObj[i].msgLatency*1000/(gIpcPerfObj[i].msgCount*2))/1000),
            gIpcPerfObj[i].maxLatency / 2,
            gIpcPerfObj[i].msgCount);
    }
    DebugP_log("\n[TEST IPC RPMSG] Performance Numbers Print End\r\n\n");
#endif

    /* delete objects test, this MUST be the last test */
    test_rpmsgDestructObjects();

    UNITY_END();
}

void test_main(void *args)
{
    test_rpmsgCreateObjects();
    if(IpcNotify_getSelfCoreId()==gMainCoreId)
    {
        test_ipc_main_core_start();
    }
    else
    {
        test_ipc_remote_core_start();
    }
}

void setUp(void)
{
}

void tearDown(void)
{
}

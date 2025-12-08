/*
 *  Copyright (C) 2021-25 Texas Instruments Incorporated
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
 *  \file test_ipcNotify_multithread.c
 *
 *  \brief File containing IPC Notify Driver test cases for version V0.
 *
 */

 /* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "test_ipcNotify_common.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define IPC_MT_NUM_THREADS 2
#if defined(BUILD_C7X_AS_MASTER)
#define TEST_IPC_NOTIFY_TASK_STACK_SIZE (2048 * 16)
#else
#define TEST_IPC_NOTIFY_TASK_STACK_SIZE (2048)
#endif
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct {
    uint32_t threadIdx;
    uint32_t coreId;
} IpcMtThreadArg;

typedef struct {
    uint32_t msgCount[IPC_MT_NUM_THREADS];
    SemaphoreP_Object *threadSems[IPC_MT_NUM_THREADS];
} BackToBackHandlerCtx;

typedef struct {
    uint32_t threadMsgCount[IPC_MT_NUM_THREADS];  /* Tracks message count per thread */
    SemaphoreP_Object *threadSems[IPC_MT_NUM_THREADS];
} OneToOneHandlerCtx;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* External semaphores defined in test_ipc_notify.c */
extern SemaphoreP_Object gRxDoneSem;
extern SemaphoreP_Object RxMultiEndPointSem[TEST_IPC_NOTIFY_ONETOMANY_ENDPOINTS];

uint8_t TestIpcNotify_TaskStack[IPC_MT_NUM_THREADS][TEST_IPC_NOTIFY_TASK_STACK_SIZE];
SemaphoreP_Object ipcMtSem[IPC_MT_NUM_THREADS];
TaskP_Object ipcMtTaskObjs[IPC_MT_NUM_THREADS];
SemaphoreP_Object ipcMtTestSem;


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#ifdef IPC_NOTIFY_MULTITHREAD_TEST
/**
 * @brief Client handler for multithreaded many-to-one test.
 * Checks received value and posts the thread's semaphore.
 *
 * @param remoteCoreId   Remote core ID that sent the message.
 * @param localClientId  Local client ID on which the message was received.
 * @param msgValue       Message value (should match threadIdx).
 * @param args           Pointer to thread's semaphore.
 */
void TestIpcNotify_clientMsghandler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args)
{
    uint32_t expectedValue = localClientId - gClientId; /* threadIdx */
    TEST_ASSERT_EQUAL_UINT32(expectedValue, msgValue);  /* Confirm data integrity */

    SemaphoreP_Object *pDoneSem = (SemaphoreP_Object *)args;
    SemaphoreP_post(pDoneSem);
}

/* client handler on main core core, it sends a message back to server until gMsgEchoCount
 * messages have been exchanged and then posts a semaphore to indicate done to main core
 * This version supports single-threaded message exchange only
 */
void TestIpc_notifyClientMsgHandler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args)
{
    int32_t status;

    /* increment msgValue and send it back until gMsgEchoCount iterations are done */
    if(msgValue != (gMsgEchoCount-1))
    {
        /* send new message to remote core, that echoed our message */
        msgValue++;
        status = IpcNotify_sendMsg(remoteCoreId, gServerClientId, msgValue, 1);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }
    else
    {
        SemaphoreP_Object *pDoneSem = (SemaphoreP_Object *)args;

        SemaphoreP_post(pDoneSem);
    }
}

/* client handler for multithreaded one-to-one test
 * Tracks per-thread message counts to handle interleaved messages from multiple threads
 */
void TestIpc_notifyClientOneToOneMultithread(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args)
{
    int32_t status;
    OneToOneHandlerCtx *ctx = (OneToOneHandlerCtx *)args;

    /* For simplicity in this test: use msgValue directly as thread identifier in upper bits
     * if threads encode their ID in the message, otherwise just count received messages */
    if(msgValue != (gMsgEchoCount-1))
    {
        /* send new message to remote core, that echoed our message */
        msgValue++;
        status = IpcNotify_sendMsg(remoteCoreId, gServerClientId, msgValue, 1);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }
    else
    {
        /* All threads have completed their message exchanges - wake all waiting threads */
        int32_t i;
        for (i = 0; i < IPC_MT_NUM_THREADS; i++)
        {
            SemaphoreP_post(ctx->threadSems[i]);
        }
    }
}

/* client handler on main core core, when gMsgEchoCount
 * messages have been exchanged it posts a semaphore to indicate done to main core
 */
void TestIpc_notifyClientbackTobackMsgHandler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args)
{
    BackToBackHandlerCtx *ctx = (BackToBackHandlerCtx *)args;

    /* Extract threadIdx from upper 16 bits and msgIdx from lower 16 bits */
    uint32_t threadIdx = (msgValue >> 16) & 0xFFFF;
    uint32_t msgIdx = msgValue & 0xFFFF;

    if(msgIdx != (gMsgEchoCount-1))
    {
        /* no nothing, until gMsgEchoCount iterations are done */
    }
    else
    {
        /* Post the semaphore for this thread when its last message arrives */
        SemaphoreP_post(ctx->threadSems[threadIdx]);
    }
}

/**
 * @brief Thread function for many-to-one multithreaded test.
 * Each thread registers a unique client ID, sends a message, and waits for a reply.
 *
 * @param arg Pointer to IpcMtThreadArg structure.
 */
void IpcNotify_threadManyToOne(void *arg)
{
    IpcMtThreadArg *threadArg = (IpcMtThreadArg *)arg;
    uint32_t threadIdx = threadArg->threadIdx;
    uint32_t coreId = threadArg->coreId;
    int32_t status, clientId;
    SemaphoreP_Object *mySem = &ipcMtSem[threadIdx];

    SemaphoreP_constructBinary(mySem, 0);
    clientId = gClientId + threadIdx;
    DebugP_log("Registering client %d for thread %d\r\n", clientId, threadIdx);
    status = IpcNotify_registerClient(clientId, TestIpcNotify_clientMsghandler, mySem);
    DebugP_assert(status == SystemP_SUCCESS);

    uint32_t packedMsg = ((clientId) << 16) | (threadIdx & 0xFFFF);
    DebugP_log("Thread %u: Sending message to coreId=%u, ServerClientId=%u, packedMsg=0x%08x\r\n",
               threadIdx, coreId, ServerClientId, packedMsg);
    status = IpcNotify_sendMsg(coreId, ServerClientId, packedMsg, 1);
    DebugP_assert(status == SystemP_SUCCESS);

    status = SemaphoreP_pend(mySem, SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    IpcNotify_unregisterClient(gClientId + threadIdx);
    SemaphoreP_destruct(mySem);

    SemaphoreP_post(&ipcMtTestSem);

    TaskP_exit();
}

/**
 * @brief Multithreaded test: many threads on main core, each with unique client ID, send to one remote server.
 *
 * @param args Pointer to remote core ID (cast to uint32_t).
 */
void TestIpcNotify_multithreadManyToOne(void *args)
{
    TaskP_Params taskParams;
    int32_t i, status;
    uint32_t coreId = (uint32_t)args;
    IpcMtThreadArg threadArgs[IPC_MT_NUM_THREADS];

    SemaphoreP_constructCounting(&ipcMtTestSem, 0, IPC_MT_NUM_THREADS);

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.priority = 3U;
        taskParams.stackSize = sizeof(TestIpcNotify_TaskStack[i]);
        taskParams.stack = TestIpcNotify_TaskStack[i];
        threadArgs[i].threadIdx = i;
        threadArgs[i].coreId = coreId;
        taskParams.args = &threadArgs[i];
        taskParams.name = "IpcNotify_sharedClientIdThread";
        taskParams.taskMain = IpcNotify_threadManyToOne;
        status = TaskP_construct(&ipcMtTaskObjs[i], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        status = SemaphoreP_pend(&ipcMtTestSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        TaskP_destruct(&ipcMtTaskObjs[i]);
    }
    SemaphoreP_destruct(&ipcMtTestSem);
}

/**
 * @brief Thread function for multithreaded one-to-one test with shared client ID.
 * Each thread sends a message and waits for a reply using the shared client ID and semaphore.
 *
 * @param arg Pointer to remote core ID (cast to uint32_t).
 */
void IpcNotify_sharedClientIdThread(void *arg)
{
    IpcMtThreadArg *threadArg = (IpcMtThreadArg *)arg;
    uint32_t remoteCoreId = threadArg->coreId;
    uint32_t threadIdx = threadArg->threadIdx;
    int32_t status;

    DebugP_log("IpcNotify_sharedClientIdThread: Started, remoteCoreId=%u, threadIdx=%u\r\n", remoteCoreId, threadIdx);

    status = IpcNotify_sendMsg(remoteCoreId, gServerClientId, 0, 1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    DebugP_log("IpcNotify_sharedClientIdThread: Thread %u waiting for completion\r\n", threadIdx);
    status = SemaphoreP_pend(&ipcMtSem[threadIdx], SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    SemaphoreP_post(&ipcMtTestSem);

    TaskP_exit();
}

/**
 * @brief Multithreaded test: main core and remote core exchange messages using a shared client ID.
 *
 * @param args Pointer to remote core ID (cast to uint32_t).
 */
void TestIpcNotify_multithreadOneToOne(void *args)
{
    TaskP_Params taskParams;
    IpcMtThreadArg threadArgs[IPC_MT_NUM_THREADS];
    OneToOneHandlerCtx handlerCtx;
    uint32_t remoteCoreId = (uint32_t)args;
    int32_t i, status;

    SemaphoreP_constructCounting(&ipcMtTestSem, 0, IPC_MT_NUM_THREADS);

    /* Initialize per-thread semaphores */
    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        SemaphoreP_constructBinary(&ipcMtSem[i], 0);
        handlerCtx.threadSems[i] = &ipcMtSem[i];
    }

    /* Register the handler ONCE for the shared client ID with context for all threads */
    status = IpcNotify_registerClient(gClientId, TestIpc_notifyClientOneToOneMultithread, &handlerCtx);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.priority = 3U;
        taskParams.stackSize = sizeof(TestIpcNotify_TaskStack[i]);
        taskParams.stack = TestIpcNotify_TaskStack[i];
        threadArgs[i].threadIdx = i;
        threadArgs[i].coreId = remoteCoreId;
        taskParams.args = &threadArgs[i];
        taskParams.name = "IpcNotify_sharedClientIdThread";
        taskParams.taskMain = IpcNotify_sharedClientIdThread;
        status = TaskP_construct(&ipcMtTaskObjs[i], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        status = SemaphoreP_pend(&ipcMtTestSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    }

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        TaskP_destruct(&ipcMtTaskObjs[i]);
    }

    IpcNotify_unregisterClient(gClientId);
    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        SemaphoreP_destruct(&ipcMtSem[i]);
    }
    SemaphoreP_destruct(&ipcMtTestSem);
}

/**
 * @brief Multithreaded test: main core sends messages to multiple remote endpoints using threads.
 *
 * @param args Pointer to remote core ID (cast to uint32_t).
 */
void IpcNotify_threadOneToManyEndpoint(void *arg)
{
    IpcMtThreadArg *threadArg = (IpcMtThreadArg *)arg;
    uint32_t threadIdx = threadArg->threadIdx;
    uint32_t coreId = threadArg->coreId;
    int32_t status;
    SemaphoreP_Object *mySem = &RxMultiEndPointSem[threadIdx];

    SemaphoreP_constructBinary(mySem, 0);

    /* Each thread sends to a unique remote endpoint */
    uint16_t remoteEndpoint = remoteEndpoints[threadIdx];
    DebugP_log("IpcNotify_threadOneToManyEndpoint: Thread %u sending to remoteEndpoint=%u\r\n", threadIdx, remoteEndpoint);
    status = IpcNotify_sendMsg(coreId, remoteEndpoint, remoteEndpoint, 1);
    DebugP_assert(status == SystemP_SUCCESS);

    DebugP_log("IpcNotify_threadOneToManyEndpoint: Thread %u waiting for semaphore\r\n", threadIdx);
    status = SemaphoreP_pend(mySem, SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_destruct(mySem);

    SemaphoreP_post(&ipcMtTestSem);

    TaskP_exit();
}

/**
 * @brief Thread function for multithreaded one-to-many endpoint test.
 * Each thread sends a message to a unique remote endpoint and waits for a reply.
 *
 * @param arg Pointer to IpcMtThreadArg structure.
 */
void TestIpcNotify_multithreadOneToManyEndpoint(void *args)
{
    TaskP_Params taskParams;
    int32_t i, status;
    uint32_t coreId = (uint32_t)args;
    IpcMtThreadArg threadArgs[IPC_MT_NUM_THREADS];

    SemaphoreP_constructCounting(&ipcMtTestSem, 0, IPC_MT_NUM_THREADS);

    /* Register the handler ONCE for the main core's client ID */
    status = IpcNotify_registerClient(gClientId, testIpcNotify_oneToManyHandler, RxMultiEndPointSem);
    DebugP_assert(status == SystemP_SUCCESS);

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.priority = 3U;
        taskParams.stackSize = sizeof(TestIpcNotify_TaskStack[i]);
        taskParams.stack = TestIpcNotify_TaskStack[i];
        threadArgs[i].threadIdx = i;
        threadArgs[i].coreId = coreId;
        taskParams.args = &threadArgs[i];
        taskParams.name = "IpcNotify_OneToManyEndpointThread";
        taskParams.taskMain = IpcNotify_threadOneToManyEndpoint;
        status = TaskP_construct(&ipcMtTaskObjs[i], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        status = SemaphoreP_pend(&ipcMtTestSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        TaskP_destruct(&ipcMtTaskObjs[i]);
    }

    IpcNotify_unregisterClient(gClientId);
    SemaphoreP_destruct(&ipcMtTestSem);
}

/**
 * @brief Thread function for multithreaded back-to-back test.
 * Each thread sends gMsgEchoCount messages back-to-back to the remote core,
 * then waits for the completion semaphore.
 *
 * @param arg Pointer to IpcMtThreadArg structure.
 */
void IpcNotify_threadBackToBack(void *arg)
{
    IpcMtThreadArg *threadArg = (IpcMtThreadArg *)arg;
    uint32_t threadIdx = threadArg->threadIdx;
    uint32_t coreId    = threadArg->coreId;
    int32_t status, i;
    SemaphoreP_Object *mySem = &ipcMtSem[threadIdx];

    DebugP_log("BackToBack T%u: sending %u messages to core=%u, clientId=%u\r\n", threadIdx, gMsgEchoCount, coreId, gClientId);

    for(i = 0; i < gMsgEchoCount; i++)
    {
        /* Encode threadIdx in upper 16 bits, message index in lower 16 bits */
        uint32_t msgValue = (threadIdx << 16) | (i & 0xFFFF);
        status = IpcNotify_sendMsg(coreId, gServerClientId, msgValue, 1);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    /* Wait for this thread's completion */
    status = SemaphoreP_pend(mySem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    SemaphoreP_post(&ipcMtTestSem);
    TaskP_exit();
}

/**
 * @brief Multithreaded back-to-back send test.
 *        Launches multiple threads, each sending gMsgEchoCount messages back-to-back
 *        to the same remote core using the same client/server IDs and message logic.
 *
 * @param args Pointer to remote core ID (cast to uint32_t).
 */
void TestIpcNotify_multithreadBackToBack(void *args)
{
    TaskP_Params taskParams;
    IpcMtThreadArg threadArgs[IPC_MT_NUM_THREADS];
    BackToBackHandlerCtx handlerCtx;
    uint32_t coreId = (uint32_t)args;
    int32_t status, i;

    SemaphoreP_constructCounting(&ipcMtTestSem, 0, IPC_MT_NUM_THREADS);

    /* Initialize per-thread semaphores for the handler */
    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        SemaphoreP_constructBinary(&ipcMtSem[i], 0);
        handlerCtx.threadSems[i] = &ipcMtSem[i];
    }

    status = IpcNotify_registerClient(gClientId, TestIpc_notifyClientbackTobackMsgHandler, &handlerCtx);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.priority  = 3U;
        taskParams.stackSize = sizeof(TestIpcNotify_TaskStack[i]);
        taskParams.stack     = TestIpcNotify_TaskStack[i];
        threadArgs[i].threadIdx = i;
        threadArgs[i].coreId    = coreId;
        taskParams.args      = &threadArgs[i];
        taskParams.name      = "IpcNotify_B2BThread";
        taskParams.taskMain  = IpcNotify_threadBackToBack;

        status = TaskP_construct(&ipcMtTaskObjs[i], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        status = SemaphoreP_pend(&ipcMtTestSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        TaskP_destruct(&ipcMtTaskObjs[i]);
    }
    IpcNotify_unregisterClient(gClientId);
    for (i = 0; i < IPC_MT_NUM_THREADS; i++)
    {
        SemaphoreP_destruct(&ipcMtSem[i]);
    }
    SemaphoreP_destruct(&ipcMtTestSem);
}

#endif

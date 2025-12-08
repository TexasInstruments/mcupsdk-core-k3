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
 *  \file test_ipcNotify_common.h
 *
 *  \brief File containing IPC Notify Driver test cases for version V0.
 *
 */

 /* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifndef TEST_IPC_NOTIFY_COMMON_H
#define TEST_IPC_NOTIFY_COMMON_H
#include <stdio.h>
#include <inttypes.h>
#include <drivers/soc.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/ipc_notify.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include <kernel/dpl/TaskP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_IPC_NOTIFY_ONETOMANY_ENDPOINTS 4
#define TEST_IPC_NOTIFY_SYNC_ALL_DELAY 1000
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* number of iterations of message exchange to do */
extern uint32_t gMsgEchoCount;

/* client ID used on remote core that is used to receive and echo messages to main more */
extern uint32_t gServerClientId;

/* client ID on main core that is used to receive ACK messages from remote core server */
extern uint32_t gClientId;

/* client ID used on remote core that is used to receive and echo messages to main more */
extern uint32_t ServerClientId;

extern uint16_t remoteEndpoints[TEST_IPC_NOTIFY_ONETOMANY_ENDPOINTS];

/* semaphore used to indicate a core has received all messages in Any to Any test, and client=server tests */
extern SemaphoreP_Object gRxDoneSem;

/* semaphore array for multi-endpoint tests */
extern SemaphoreP_Object RxMultiEndPointSem[TEST_IPC_NOTIFY_ONETOMANY_ENDPOINTS];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void test_ipc_notify_client_msg_handler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args);
void testIpcNotify_oneToManyHandler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args);
void test_ipc_notify_client_back_to_back_msg_handler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args);
void TestIpcNotify_multithreadManyToOne(void *args);
void TestIpcNotify_multithreadOneToOne(void *args);
void TestIpcNotify_multithreadOneToManyEndpoint(void *args);
void TestIpcNotify_multithreadBackToBack(void *args);
#endif

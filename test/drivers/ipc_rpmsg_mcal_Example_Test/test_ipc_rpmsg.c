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
#include <kernel/dpl/CacheP.h>
#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <drivers/ipc_rpmsg.h>
#include <FreeRTOS.h>
#include <task.h>
#include <unity.h>
#include "ti_drivers_open_close.h"

/* number of iterations per test round */
uint32_t gMsgEchoCount = 10;

/* Save RPMessage parameters for deInit/init cycles */
static RPMessage_Params gSavedRpmsgParams;

/* External vring memory from system config - declare without 2nd dimension */
extern uint8_t gRPMessageVringMem[];

/* Helper function to populate vring addresses based on core-specific config.
 * vringNumBuf  - number of buffers per vring (e.g. 8 for initial, 4 for reconfigured)
 * vringMsgSize - size of each message buffer in bytes (e.g. 512)
 *
 * vringSlotSize = 2 * vringNumBuf * vringMsgSize is the memory stride between
 * consecutive vring slots in gRPMessageVringMem.  Using pointer arithmetic
 * instead of a fixed-width 2D array cast ensures addresses scale correctly
 * when vringNumBuf (and hence vringSlotSize) changes at runtime.
 */
static void populate_vring_addresses(RPMessage_Params *params,
                                     uint32_t vringNumBuf,
                                     uint32_t vringMsgSize)
{
    uint32_t selfCoreId = IpcNotify_getSelfCoreId();
    /* Slot size changes with vringNumBuf: slot[N] starts at gRPMessageVringMem + N*vringSlotSize */
    uint32_t vringSlotSize = 2U * vringNumBuf * vringMsgSize;

#if defined(SOC_AM275X)
    if(selfCoreId == CSL_CORE_ID_R5FSS0_0)
    {
        /* Main core (R5FSS0_0) vring mapping - VRING slots: TX{r5fss0_1:0, r5fss1_0:1, r5fss1_1:2, c75ss0_0:3, c75ss1_0:4} RX{r5fss0_1:5, r5fss1_0:10, r5fss1_1:15, c75ss0_0:20, c75ss1_0:25} */
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem +  0U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem +  1U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem +  2U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem +  3U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem +  4U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem +  5U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem + 10U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem + 15U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 20U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem + 25U * vringSlotSize);
    }
    else if(selfCoreId == CSL_CORE_ID_R5FSS0_1)
    {
        /* Remote core (R5FSS0_1) vring mapping - VRING slots: TX{r5fss0_0:5, r5fss1_0:6, r5fss1_1:7, c75ss0_0:8, c75ss1_0:9} RX{r5fss0_0:0, r5fss1_0:11, r5fss1_1:16, c75ss0_0:21, c75ss1_0:26} */
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem +  5U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem +  6U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem +  7U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem +  8U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem +  9U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem +  0U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem + 11U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem + 16U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 21U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem + 26U * vringSlotSize);
    }
    else if(selfCoreId == CSL_CORE_ID_R5FSS1_0)
    {
        /* Remote core (R5FSS1_0) vring mapping - VRING slots: TX{r5fss0_0:10, r5fss0_1:11, r5fss1_1:12, c75ss0_0:13, c75ss1_0:14} RX{r5fss0_0:1, r5fss0_1:6, r5fss1_1:17, c75ss0_0:22, c75ss1_0:27} */
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 10U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem + 11U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem + 12U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 13U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem + 14U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem +  1U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem +  6U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem + 17U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 22U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem + 27U * vringSlotSize);
    }
    else if(selfCoreId == CSL_CORE_ID_R5FSS1_1)
    {
        /* Remote core (R5FSS1_1) vring mapping - VRING slots: TX{r5fss0_0:15, r5fss0_1:16, r5fss1_0:17, c75ss0_0:18, c75ss1_0:19} RX{r5fss0_0:2, r5fss0_1:7, r5fss1_0:12, c75ss0_0:23, c75ss1_0:28} */
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 15U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem + 16U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem + 17U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 18U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem + 19U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem +  2U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem +  7U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem + 12U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 23U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem + 28U * vringSlotSize);
    }
    else if(selfCoreId == CSL_CORE_ID_C75SS0_0)
    {
        /* Remote core (C75SS0_0) vring mapping - VRING slots: TX{r5fss0_0:20, r5fss0_1:21, r5fss1_0:22, r5fss1_1:23, c75ss1_0:24} RX{r5fss0_0:3, r5fss0_1:8, r5fss1_0:13, r5fss1_1:18, c75ss1_0:29} */
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 20U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem + 21U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem + 22U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem + 23U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem + 24U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem +  3U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem +  8U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem + 13U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem + 18U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS1_0] = (uintptr_t)(gRPMessageVringMem + 29U * vringSlotSize);
    }
    else if(selfCoreId == CSL_CORE_ID_C75SS1_0)
    {
        /* Remote core (C75SS1_0) vring mapping - VRING slots: TX{r5fss0_0:25, r5fss0_1:26, r5fss1_0:27, r5fss1_1:28, c75ss0_0:29} RX{r5fss0_0:4, r5fss0_1:9, r5fss1_0:14, r5fss1_1:19, c75ss0_0:24} */
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 25U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem + 26U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem + 27U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem + 28U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 29U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem +  4U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_1] = (uintptr_t)(gRPMessageVringMem +  9U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_0] = (uintptr_t)(gRPMessageVringMem + 14U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS1_1] = (uintptr_t)(gRPMessageVringMem + 19U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 24U * vringSlotSize);
    }

#elif defined (SOC_AM62DX) || defined (SOC_AM62AX)
    if(selfCoreId == CSL_CORE_ID_C75SS0_0)
    {
        /* Remote core (C75SS0_0) vring mapping - VRING slots: TX{mcu_r5fss0_0:9, r5fss0_0:10, a53ss0_0:11} RX{mcu_r5fss0_0:2, r5fss0_0:5, a53ss0_0:8} */
        params->vringTxBaseAddr[CSL_CORE_ID_MCU_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 9U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 10U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_A53SS0_0] = (uintptr_t)(gRPMessageVringMem + 11U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_MCU_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 2U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 5U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_A53SS0_0] = (uintptr_t)(gRPMessageVringMem + 8U * vringSlotSize);
    }
    else if(selfCoreId == CSL_CORE_ID_MCU_R5FSS0_0)
    {
        /* MCU core (MCU_R5FSS0_0) vring mapping - VRING slots: TX{r5fss0_0:0, a53ss0_0:1, c75ss0_0:2} RX{r5fss0_0:3, a53ss0_0:6, c75ss0_0:9} */
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 0U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_A53SS0_0] = (uintptr_t)(gRPMessageVringMem + 1U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 2U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 3U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_A53SS0_0] = (uintptr_t)(gRPMessageVringMem + 6U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 9U * vringSlotSize);
    }
    else if(selfCoreId == CSL_CORE_ID_R5FSS0_0)
    {
        /* Main core (R5FSS0_0) vring mapping - VRING slots: TX{mcu_r5fss0_0:3, a53ss0_0:4, c75ss0_0:5} RX{mcu_r5fss0_0:0, a53ss0_0:7, c75ss0_0:10} */
        params->vringTxBaseAddr[CSL_CORE_ID_MCU_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 3U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_A53SS0_0] = (uintptr_t)(gRPMessageVringMem + 4U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 5U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_MCU_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 0U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_A53SS0_0] = (uintptr_t)(gRPMessageVringMem + 7U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 10U * vringSlotSize);
    }
    else if(selfCoreId == CSL_CORE_ID_A53SS0_0)
    {
        /* A53 core (A53SS0_0) vring mapping - VRING slots: TX{mcu_r5fss0_0:6, r5fss0_0:7, c75ss0_0:8} RX{mcu_r5fss0_0:1, r5fss0_0:4, c75ss0_0:11} */
        params->vringTxBaseAddr[CSL_CORE_ID_MCU_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 6U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 7U * vringSlotSize);
        params->vringTxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 8U * vringSlotSize);

        params->vringRxBaseAddr[CSL_CORE_ID_MCU_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 1U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_R5FSS0_0] = (uintptr_t)(gRPMessageVringMem + 4U * vringSlotSize);
        params->vringRxBaseAddr[CSL_CORE_ID_C75SS0_0] = (uintptr_t)(gRPMessageVringMem + 11U * vringSlotSize);
    }

#endif

    /* Common vring properties derived from the passed-in parameters */
    params->vringNumBuf      = vringNumBuf;
    params->vringMsgSize     = vringMsgSize;
    params->vringSize        = vringSlotSize;   /* 2 * vringNumBuf * vringMsgSize */
    params->vringAllocationPDK = 1u;

    /* Force compiler to commit all writes to params structure in release mode.
     * Without this, aggressive compiler optimizations can remove the address assignments
     * thinking they're not used, causing vringTxBaseAddr/vringRxBaseAddr to remain uninitialized. */
    volatile RPMessage_Params *volatile_params = (volatile RPMessage_Params *)params;
    (void)volatile_params; /* Prevent compiler from removing the volatile alias */
}

#if defined (SOC_AM275X)
uint32_t gMainCoreId = CSL_CORE_ID_R5FSS0_0;

uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_1,
    CSL_CORE_ID_R5FSS1_0,
    CSL_CORE_ID_R5FSS1_1,
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_C75SS1_0,
    CSL_CORE_ID_MAX
};

#if defined (SOC_AM275X)
static uint32_t gExcludeC75SS1_0 = 2; /* 2 = C75SS1_0 enabled, 1 = disabled, 0 = auto-detect */
#endif

static uint16_t getServerEndPtForCore(uint32_t remoteCoreId)
{
    switch(remoteCoreId)
    {
        case CSL_CORE_ID_R5FSS0_1:
            return 15;
        case CSL_CORE_ID_R5FSS1_0:
            return 14;
        case CSL_CORE_ID_R5FSS1_1:
            return 16;
        case CSL_CORE_ID_C75SS0_0:
            return 13;
#if defined (SOC_AM275X)
        case CSL_CORE_ID_C75SS1_0:
            return 17;
#endif
        default:
            return 10;
    }
}
#elif defined (SOC_AM62DX) || defined (SOC_AM62AX)
uint32_t gMainCoreId = CSL_CORE_ID_MCU_R5FSS0_0;

uint32_t gRemoteCoreId[] = {
    CSL_CORE_ID_R5FSS0_0,
    CSL_CORE_ID_A53SS0_0,
    CSL_CORE_ID_C75SS0_0,
    CSL_CORE_ID_MAX
};

static uint16_t getServerEndPtForCore(uint32_t remoteCoreId)
{
    switch(remoteCoreId)
    {
        case CSL_CORE_ID_R5FSS0_0:
            return 13;
        case CSL_CORE_ID_A53SS0_0:
            return 14;
        case CSL_CORE_ID_C75SS0_0:
            return 15;
        default:
            return 10;
    }
}
#endif

#define MAX_MSG_SIZE    (496u)
#define RPMSG_SEND_TIMEOUT (2 * 1000000)

SemaphoreP_Object gAckDoneSem;

#define SERVER_TASK_PRI (2u)
#if defined(__C7504__) || defined(__C7524__)
#define SERVER_TASK_SIZE (1024*32u)
#else
#define SERVER_TASK_SIZE (16*1024/sizeof(StackType_t))
#endif
StackType_t  gServerTaskStack[SERVER_TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gServerTaskObj;
TaskHandle_t gServerTask;

RPMessage_Object gServerMsgObject;
RPMessage_Object gClientMsgObject;
RPMessage_Object gAckMsgObject;

uint16_t gClientEndPt = 11;
uint16_t gAckEndPt    = 12;

void test_rpmsgAckHandler(RPMessage_Object *obj, void *arg, void *data, uint16_t dataLen, uint16_t remoteCoreId, uint16_t remoteEndPt)
{
    SemaphoreP_Object *pDoneSem = (SemaphoreP_Object *)arg;
    SemaphoreP_post(pDoneSem);
}

void test_rpmsgServerMain(void *args)
{
    int32_t status;
    static char recvMsg[MAX_MSG_SIZE];
    uint16_t recvMsgSize, remoteCoreId;
    uint32_t remoteCoreEndPt;
    uint32_t msgCount = 0u;

    /* Wait for all cores to be ready before message exchange */
    // IpcNotify_syncAll(SystemP_WAIT_FOREVER);
    // ClockP_sleep(1000);

    while(1)
    {
        // ClockP_sleep(1);
        recvMsgSize = sizeof(recvMsg);
        status = RPMessage_recv(&gServerMsgObject,
            recvMsg, &recvMsgSize,
            &remoteCoreId, &remoteCoreEndPt,
            SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);

        status = RPMessage_send(
            recvMsg, recvMsgSize,
            remoteCoreId, remoteCoreEndPt,
            RPMessage_getLocalEndPt(&gServerMsgObject),
            SystemP_WAIT_FOREVER);
        DebugP_assert(status==SystemP_SUCCESS);
        msgCount++;

        if (msgCount >= gMsgEchoCount)
        {
            break;
        }
    }
}

void test_rpmsgCreateObjects()
{
    int32_t status;
    RPMessage_CreateParams createParams;

#if defined (SOC_AM275X)
    if (gExcludeC75SS1_0 == 0)
    {
        int32_t testStatus;
        char testBuf[] = "test";

        testStatus = RPMessage_send(
            testBuf, sizeof(testBuf),
            CSL_CORE_ID_C75SS1_0, 17,
            RPMessage_getLocalEndPt(&gClientMsgObject),
            0);

        if (testStatus != SystemP_SUCCESS)
        {
            gExcludeC75SS1_0 = 1;
            // DebugP_log("[IPC] C75SS1_0 excluded - Using 4-core configuration\r\n");
        }
        else
        {
            gExcludeC75SS1_0 = 2;
            // DebugP_log("[IPC] C75SS1_0 available - Using 6-core configuration\r\n");
        }
    }
#endif

    // DebugP_log("[IPC] Core %s: Creating semaphores...\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()));
    status = SemaphoreP_constructBinary(&gAckDoneSem, 0);
    DebugP_assert(status==SystemP_SUCCESS);

    // DebugP_log("[IPC] Core %s: Creating RPMessage endpoints...\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()));
    // DebugP_log("[IPC] Core %s: Server endpoint = %u\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()), getServerEndPtForCore(IpcNotify_getSelfCoreId()));
    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = getServerEndPtForCore(IpcNotify_getSelfCoreId());
    status = RPMessage_construct(&gServerMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gClientEndPt;
    status = RPMessage_construct(&gClientMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = gAckEndPt;
    createParams.recvCallback = test_rpmsgAckHandler;
    createParams.recvCallbackArgs = &gAckDoneSem;
    status = RPMessage_construct(&gAckMsgObject, &createParams);
    DebugP_assert(status==SystemP_SUCCESS);

    // DebugP_log("[IPC] Core %s: Creating server task...\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()));
    gServerTask = xTaskCreateStatic(test_rpmsgServerMain,
                                  "test_rpmsgServerMain",
                                  SERVER_TASK_SIZE,
                                  NULL,
                                  SERVER_TASK_PRI,
                                  gServerTaskStack,
                                  &gServerTaskObj);
    configASSERT(gServerTask != NULL);

    // DebugP_log("[TEST IPC RPMSG] Ready for IPC !!!\r\n");
}

void test_rpmsgDestructObjects()
{
    vTaskDelete(gServerTask);
    RPMessage_destruct(&gServerMsgObject);
    RPMessage_destruct(&gAckMsgObject);
    RPMessage_destruct(&gClientMsgObject);
    SemaphoreP_destruct(&gAckDoneSem);
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
        msgSize = strlen(msgBuf) + 1;

        for(i=0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++ )
        {
#if defined (SOC_AM275X)
            if ((gExcludeC75SS1_0 == 1) && (gRemoteCoreId[i] == CSL_CORE_ID_C75SS1_0))
            {
                continue;
            }
#endif

            if(gRemoteCoreId[i] != IpcNotify_getSelfCoreId())
            {
                status = RPMessage_send(
                    msgBuf, msgSize,
                    gRemoteCoreId[i], getServerEndPtForCore(gRemoteCoreId[i]),
                    RPMessage_getLocalEndPt(&gClientMsgObject),
                    ClockP_usecToTicks(RPMSG_SEND_TIMEOUT));
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
            }
        }
        for(i=0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++ )
        {
#if defined (SOC_AM275X)
            if ((gExcludeC75SS1_0 == 1) && (gRemoteCoreId[i] == CSL_CORE_ID_C75SS1_0))
            {
                continue;
            }
#endif

            if(gRemoteCoreId[i] != IpcNotify_getSelfCoreId())
            {
                ackMsgSize = sizeof(ackMsgBuf);
                ackMsgBuf[0] = 0;
                status = RPMessage_recv(&gClientMsgObject,
                    ackMsgBuf, &ackMsgSize,
                    &remoteCoreId, &remoteCoreEndPt,
                    SystemP_WAIT_FOREVER);
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
                TEST_ASSERT_EQUAL_UINT16(getServerEndPtForCore(remoteCoreId), remoteCoreEndPt);
                TEST_ASSERT_EQUAL_UINT16(msgSize, ackMsgSize);
                TEST_ASSERT_EQUAL_INT32( 0, strcmp(ackMsgBuf, msgBuf));
            }
        }
    }
}

void test_ipc_remote_core_start()
{
    UNITY_BEGIN();

    RPMessage_Params rpmsgParams;
    int32_t status;

    /* Now destruct them to test deInit/init cycle */
    test_rpmsgDestructObjects();

    /* DeInit immediately */
    RPMessage_deInit();

    /* Phase 0: Re-init with vringNumBuf=8 to match main core's Phase 0 stability check */
    // DebugP_log("[PHASE 0] Core %s: Calling RPMessage_init() with vringNumBuf=8...\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()));
    RPMessage_Params_init(&rpmsgParams);

    /* Populate TX/RX vring addresses with vringNumBuf=8 to match main core Phase 0.
     * Slot stride = 2*8*512 = 8192 bytes, same as the initial syscfg configuration. */
#if defined (SOC_AM275X)
    populate_vring_addresses(&rpmsgParams, 16U, 512U);
#elif defined (SOC_AM62DX) || defined (SOC_AM62AX)
    populate_vring_addresses(&rpmsgParams, 256U, 512U);
#endif

    status = RPMessage_init(&rpmsgParams);

    if(status == SystemP_SUCCESS)
    {

        /* Create objects again */
        // DebugP_log("[PHASE 0] Core %s: Creating RPMessage objects...\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()));
        test_rpmsgCreateObjects();
    }
    else
    {
        DebugP_log("[PHASE 0] Core %s: ERROR: RPMessage_init() failed with status=%d\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()), status);
        DebugP_log("[PHASE 0] Core %s: FAILURE: deInit/init not working properly\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()));
        UNITY_END();
        return;
    }

    /* TEST ROUND 1: serve messages from main core running with vringNumBuf=8 */
    test_rpmsgServerMain(NULL);

    // uint32_t bufferConfigs[] = {4U, 2U, 16U};
    // uint32_t numConfigs = sizeof(bufferConfigs) / sizeof(bufferConfigs[0]);
    // uint32_t configIdx;

    // /* Phase 2: Test runtime reconfiguration with multiple buffer configurations */
    // for (configIdx = 0U; configIdx < numConfigs; configIdx++)
    // {
    //     // ClockP_sleep(1);

    //     uint32_t numBuffers = bufferConfigs[configIdx];

    //     /* Now destruct them to test deInit/init cycle */
    //     test_rpmsgDestructObjects();

    //     /* DeInit immediately */
    //     RPMessage_deInit();

    //     RPMessage_Params_init(&rpmsgParams);

    //     /* Populate TX/RX vring addresses with updated vringNumBuf.
    //      * Slot stride = 2*numBuffers*512 bytes */
    //     populate_vring_addresses(&rpmsgParams, numBuffers, 512U);

    //     status = RPMessage_init(&rpmsgParams);

    //     if(status == SystemP_SUCCESS)
    //     {
    //         test_rpmsgCreateObjects();
    //     }
    //     else
    //     {
    //         DebugP_log("[PHASE 1] Core %s: ERROR: RPMessage_init() failed with status=%d\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()), status);
    //         DebugP_log("[PHASE 1] Core %s: FAILURE: deInit/init not working properly\r\n", SOC_getCoreName(IpcNotify_getSelfCoreId()));
    //         UNITY_END();
    //         return;
    //     }

    //     test_rpmsgServerMain(NULL);
    // }

    UNITY_END();
}

void test_ipc_main_core_start()
{
    // volatile uint16_t p=1;
    // while(p){

    // }
    UNITY_BEGIN();

    DebugP_log("[TEST IPC RPMSG] MCAL IPC test mode\r\n");
    DebugP_log("[TEST IPC RPMSG] Remote cores initialized and ready for IPC\r\n");
    DebugP_log("[TEST IPC RPMSG] MCAL on R5FSS0_0 will initiate communication\r\n");

    /* Phase 0: Verify deInit/init stability before starting main tests */
    DebugP_log("\n[PHASE 0] Verifying deInit/init stability...\r\n");

    /* Save current RPMessage parameters for later use.
     * Use populate_vring_addresses with vringNumBuf=8 (initial/default config)
     * so all addresses and properties are set consistently via the same helper. */
    DebugP_log("[PHASE 0] Saving RPMessage parameters...\r\n");
    RPMessage_Params_init(&gSavedRpmsgParams);
    populate_vring_addresses(&gSavedRpmsgParams, 8U, 512U);

    /* Destruct endpoints before deInit */
    test_rpmsgDestructObjects();

    /* Wait for stabilization */
    DebugP_log("[PHASE 0] Waiting 500ms for stabilization...\r\n");
    ClockP_sleep(ClockP_usecToTicks(500000));

    /* DeInit */
    RPMessage_deInit();
    DebugP_log("[PHASE 0] RPMessage_deInit() completed\r\n");

    /* Wait before re-init */
    DebugP_log("[PHASE 0] Waiting 500ms before re-initialization...\r\n");
    ClockP_sleep(ClockP_usecToTicks(500000));

    /* Re-initialize with saved parameters */
    DebugP_log("[PHASE 0] Calling RPMessage_init() with saved parameters...\r\n");
    int32_t status = RPMessage_init(&gSavedRpmsgParams);

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("[PHASE 0] RPMessage_init() succeeded\r\n");

        /* Create objects again */
        DebugP_log("[PHASE 0] Creating RPMessage objects again...\r\n");
        test_rpmsgCreateObjects();

        /* Wait for cores to be ready */
        DebugP_log("[PHASE 0] Waiting 500ms for cores to stabilize...\r\n");
        ClockP_sleep(ClockP_usecToTicks(500000));

        DebugP_log("[PHASE 0] SUCCESS: deInit/init is stable, proceeding with main tests\r\n");
    }
    else
    {
        DebugP_log("[PHASE 0] ERROR: RPMessage_init() failed with status=%d\r\n", status);
        DebugP_log("[PHASE 0] FAILURE: deInit/init not working properly - aborting tests\r\n");
        return;
    }

    /* Test 1: Run with initial vringNumBuf (8) */
    DebugP_log("\n[TEST ROUND 1] Running with vringNumBuf=8\r\n");
    test_rpmsgAnyToAny(NULL);
    DebugP_log("[TEST ROUND 1] Completed successfully with vringNumBuf=8\r\n");

    /* Phase 2: Test runtime deInit/init with vringNumBuf change to 4 */
    DebugP_log("\n[PHASE 2] Testing runtime reconfiguration...\r\n");
    DebugP_log("[PHASE 2] Calling RPMessage_deInit()...\r\n");

    /* Destruct endpoints before deInit */
    test_rpmsgDestructObjects();

    /* Wait for all cores to complete destructing */
    DebugP_log("[PHASE 2] Waiting 500ms for all cores to stabilize...\r\n");
    ClockP_sleep(ClockP_usecToTicks(500000));

    /* DeInit RPMessage driver */
    RPMessage_deInit();
    DebugP_log("[PHASE 2] RPMessage_deInit() completed\r\n");

    /* Critical: Clear vring memory to remove stale Phase 1 data */
    memset((void*)gRPMessageVringMem, 0, 20U * 2U * 8U * 512U);
    DebugP_log("[PHASE 2] Cleared vring memory\r\n");

    /* Wait before reinitializing */
    DebugP_log("[PHASE 2] Waiting 500ms before re-initialization...\r\n");
    ClockP_sleep(ClockP_usecToTicks(500000));

    /* Re-initialize with vringNumBuf=4.
     * populate_vring_addresses recomputes all TX/RX base addresses with the
     * new slot stride (2*4*512 = 4096) so they match the remote cores. */
    DebugP_log("[PHASE 2] Calling RPMessage_init() with vringNumBuf=4...\r\n");
    RPMessage_Params rpmsgParams2;
    RPMessage_Params_init(&rpmsgParams2);
    populate_vring_addresses(&rpmsgParams2, 4U, 512U);

    int32_t status2 = RPMessage_init(&rpmsgParams2);

    /* Critical: Invalidate vring cache after re-init to see MCAL's updates in Phase 2 */
    if(status2 == SystemP_SUCCESS)
    {
        CacheP_inv((void*)gRPMessageVringMem, 20U * 2U * 4U * 512U, CacheP_TYPE_ALL);
        DebugP_log("[PHASE 2] Cache invalidated for vring memory\r\n");
    }

    if(status2 == SystemP_SUCCESS)
    {
        DebugP_log("[PHASE 2] RPMessage_init() succeeded with vringNumBuf=4\r\n");

        /* Recreate objects for Phase 2 test */
        DebugP_log("[PHASE 2] Creating new RPMessage objects...\r\n");
        test_rpmsgCreateObjects();

        /* Wait for cores to recreate objects */
        DebugP_log("[PHASE 2] Waiting 500ms for all cores to be ready...\r\n");
        ClockP_sleep(ClockP_usecToTicks(500000));

        /* Run test with new buffer configuration */
        DebugP_log("\n[TEST ROUND 2] Running with vringNumBuf=4\r\n");
        test_rpmsgAnyToAny(NULL);
        DebugP_log("[TEST ROUND 2] Completed with vringNumBuf=4\r\n");

        DebugP_log("[PHASE 2] SUCCESS: Runtime reconfiguration test passed!\r\n");
        DebugP_log("[PHASE 2] vringNumBuf successfully changed from 8 to 4 at runtime\r\n");

        /* Cleanup */
        test_rpmsgDestructObjects();
    }
    else
    {
        DebugP_log("[PHASE 2] ERROR: RPMessage_init() failed with status=%d\r\n", status2);
        DebugP_log("[PHASE 2] FAILURE: Could not reconfigure vringNumBuf at runtime\r\n");
    }

    DebugP_log("[TEST IPC RPMSG] All tests completed\r\n");

    UNITY_END();
}

void test_main(void *args)
{
    test_rpmsgCreateObjects();
    // volatile uint16_t p=1;
    // while(p){

    // }
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

/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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
#include <inttypes.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/ipc_notify.h>

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct {
    uint32_t primCore;
    uint32_t secCore;
} CoreCombos;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* number of iterations of message exchange to do */
uint32_t gMsgEchoCount = 10000;
/* client ID that is used to send and receive messages */
uint32_t gClientId = 4u;

/* semaphore used to indicate a remote core has finished all message xchange */
SemaphoreP_Object gRemoteDoneSem;

/* Flag to indicate if primary core */
uint8_t gIsPrimCore = 0;

CoreCombos gCoreCombos[] =
{
    {
        .primCore = CSL_CORE_ID_MCU_R5FSS0_0,
        .secCore = CSL_CORE_ID_C75SS0_0,
    },
    {
        .primCore = CSL_CORE_ID_MCU_R5FSS0_0,
        .secCore = CSL_CORE_ID_A53SS0_0,
    },
    {
        .primCore = CSL_CORE_ID_A53SS0_0,
        .secCore = CSL_CORE_ID_C75SS0_0,
    },
    {
        .primCore = CSL_CORE_ID_MCU_R5FSS0_0,
        .secCore = CSL_CORE_ID_R5FSS0_0,
    },
    {
        .primCore = CSL_CORE_ID_C75SS0_0,
        .secCore = CSL_CORE_ID_R5FSS0_0,
    },
    {
        .primCore = CSL_CORE_ID_A53SS0_0,
        .secCore = CSL_CORE_ID_R5FSS0_0,
    },
    {
        .primCore = CSL_CORE_ID_MAX,
        .secCore = CSL_CORE_ID_MAX,
    }
};

uint32_t gLoggingCore = CSL_CORE_ID_MCU_R5FSS0_0;

uint32_t gTimeInNs[sizeof(gCoreCombos)/sizeof(gCoreCombos[0]) - 1];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void ipc_notify_msg_handler_remote_core(uint16_t remoteCoreId, uint16_t localClientId,
                                            uint32_t msgValue, void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t gRemoteCoreId = (uint32_t)(-1);

void ipc_notify_msg_handler_remote_core(uint16_t remoteCoreId, uint16_t localClientId,
                                            uint32_t msgValue, void *args)
{
    uint32_t remoteCoreIdArg = *((uint32_t *)args);

    if(remoteCoreId == remoteCoreIdArg)
    {
        IpcNotify_sendMsg(remoteCoreId, localClientId, msgValue+1, 1);

        if((msgValue == gMsgEchoCount-1) || (msgValue == gMsgEchoCount))
        {
            SemaphoreP_post(&gRemoteDoneSem);
        }
    }
}

void ipc_benchmark_start()
{
    int32_t status;
    uint32_t count = 0;
    uint64_t curTime  = 0;

    SemaphoreP_constructBinary(&gRemoteDoneSem, 0);

    while (gCoreCombos[count].primCore != CSL_CORE_ID_MAX)
    {
        if(IpcNotify_getSelfCoreId() == gCoreCombos[count].primCore)
        {
            gRemoteCoreId = gCoreCombos[count].secCore;
            status = IpcNotify_registerClient(gClientId, ipc_notify_msg_handler_remote_core, &gRemoteCoreId);
            DebugP_assert(status==SystemP_SUCCESS);

            IpcNotify_sendSync(gCoreCombos[count].secCore);
            IpcNotify_waitSync(gCoreCombos[count].secCore, SystemP_WAIT_FOREVER);

            uint32_t msgValue = 0;
            curTime = ClockP_getTimeUsec();
            status = IpcNotify_sendMsg(gCoreCombos[count].secCore, gClientId, msgValue, 1);
            SemaphoreP_pend(&gRemoteDoneSem, SystemP_WAIT_FOREVER);
            curTime = ClockP_getTimeUsec() - curTime;

            /* unregister handlers */
            IpcNotify_unregisterClient(gClientId);

            DebugP_log(" %s\t| %s\t| %" PRId32 "ns\r\n", SOC_getCoreName(gCoreCombos[count].primCore),
                                            SOC_getCoreName(gCoreCombos[count].secCore), (uint32_t)(curTime*1000u/(gMsgEchoCount)));
            gTimeInNs[count] = (uint32_t)(curTime*1000u/(gMsgEchoCount));
        }
        else if(IpcNotify_getSelfCoreId() == gCoreCombos[count].secCore)
        {
            gRemoteCoreId = gCoreCombos[count].primCore;
            status = IpcNotify_registerClient(gClientId, ipc_notify_msg_handler_remote_core, &gRemoteCoreId);

            IpcNotify_sendSync(gCoreCombos[count].primCore);
            IpcNotify_waitSync(gCoreCombos[count].primCore, SystemP_WAIT_FOREVER);

            SemaphoreP_pend(&gRemoteDoneSem, SystemP_WAIT_FOREVER);

            /* unregister handlers */
            IpcNotify_unregisterClient(gClientId);
        }
        count++;
    }

    IpcNotify_syncAll(SystemP_WAIT_FOREVER);
}

void test_main(void *args)
{
    ipc_benchmark_start();

    if(IpcNotify_getSelfCoreId() == gLoggingCore)
    {
        DebugP_log("All tests passed \r\n");
    }
}

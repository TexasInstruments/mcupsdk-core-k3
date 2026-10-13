/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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

/* Independent echo endpoint for the unmodified Linux rpmsg_char_simple. */
#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/ipc_rpmsg.h>
#include <drivers/hw_include/cslr_soc.h>
#include "rpmsg_echo_service.h"

#define RPMSG_ECHO_ENDPOINT       (14U)
#define RPMSG_ECHO_MAX_MSG_SIZE   (496U)
/* Convert to DPL clock ticks before passing to RPMessage. */
#define RPMSG_ECHO_TIMEOUT_US     (100000U)

static RPMessage_Object gEchoObj;
static uint8_t gEchoBuf[RPMSG_ECHO_MAX_MSG_SIZE]
    __attribute__((aligned(32)));
static volatile bool gEchoStopRequested = false;
static volatile bool gEchoStopped = false;

void rpmsg_echo_service_stop(void)
{
    /* Do not unblock/destruct an object concurrently with task init/cleanup.
     * Bounded receive/send waits let the task observe this flag. */
    gEchoStopRequested = true;
}

bool rpmsg_echo_service_is_stopped(void)
{
    return gEchoStopped;
}

void rpmsg_echo_service_main(void *args)
{
    RPMessage_CreateParams params;
    int32_t status;
    uint16_t recvSize;
    uint16_t remoteCoreId;
    uint32_t remoteEndPt;
    uint32_t timeoutTicks = (uint32_t)ClockP_usecToTicks(RPMSG_ECHO_TIMEOUT_US);

    if (timeoutTicks == 0U)
    {
        timeoutTicks = 1U;
    }

    (void)args;
    /* The orchestrator has already waited for Linux readiness. Do not reset
     * the stop flag: shutdown may arrive before this task first runs. */
    if (gEchoStopRequested)
    {
        goto task_exit;
    }

    RPMessage_CreateParams_init(&params);
    params.localEndPt = RPMSG_ECHO_ENDPOINT;
    status = RPMessage_construct(&gEchoObj, &params);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[ECHO] Endpoint construction failed: %d\r\n", status);
        goto task_exit;
    }

    if (gEchoStopRequested)
    {
        goto endpoint_exit;
    }
    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0,
                               RPMSG_ECHO_ENDPOINT, "rpmsg_chrdev");
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("[ECHO] Service announcement failed: %d\r\n", status);
        goto endpoint_exit;
    }

    DebugP_log("[ECHO] Service ready on endpoint %u\r\n",
               RPMSG_ECHO_ENDPOINT);
    while (!gEchoStopRequested)
    {
        recvSize = sizeof(gEchoBuf);
        status = RPMessage_recv(&gEchoObj, gEchoBuf, &recvSize,
                                &remoteCoreId, &remoteEndPt,
                                timeoutTicks);
        if (gEchoStopRequested)
        {
            break;
        }
        if (status == SystemP_TIMEOUT)
        {
            continue;
        }
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("[ECHO] Receive failed: %d\r\n", status);
            vTaskDelay(pdMS_TO_TICKS(10));
            continue;
        }

        /* Echo exactly the received bytes, including their original length.
         * Linux allocates its local endpoint dynamically; reply to the sender. */
        do
        {
            status = RPMessage_send(gEchoBuf, recvSize,
                                    remoteCoreId, remoteEndPt,
                                    RPMessage_getLocalEndPt(&gEchoObj),
                                    timeoutTicks);
        } while (status == SystemP_TIMEOUT && !gEchoStopRequested);
        if (status != SystemP_SUCCESS && !gEchoStopRequested)
        {
            DebugP_log("[ECHO] Reply failed: %d\r\n", status);
        }
    }

endpoint_exit:
    RPMessage_destruct(&gEchoObj);
task_exit:
    gEchoStopped = true;
    vTaskDelete(NULL);
}

/*
 *  Copyright (c) Texas Instruments Incorporated 2026
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

/*!
 * \file sigchain_dsp_ipc_linux.c
 *
 * \brief Linux-specific IPC implementation with shared memory and MCASP control.
 *        This file contains Linux-only modifications to avoid breaking other examples.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <drivers/soc.h>
#include "sigchain_platform.h"
#include "sigchain_ipc.h"
#include "sigchain_dsp_mcasp.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Shared memory polling and metrics constants */
#define STATS_UPDATE_FREQUENCY          1000U        /* Update stats every N calls (~1 second) */
#define AUDIO_FRAME_SIZE_BYTES          2048.0f      /* Audio frame size in bytes */
#define BYTES_TO_KB                     1024.0f      /* Conversion factor */
#define MCASP_PAUSE_DELAY_US            1000U        /* Sleep delay when MCASP paused (microseconds) */

/* CMA memory region validation constants */
#define CMA_BASE_ADDRESS                0xC0000000U  /* CMA memory region base address */
#define CMA_REGION_SIZE                 0x1000000U   /* CMA memory region size (16MB) */
#define CMA_END_ADDRESS                 (CMA_BASE_ADDRESS + CMA_REGION_SIZE - 1U)

/* ========================================================================== */
/*                            Global Variables                               */
/* ========================================================================== */

/* MCASP shared memory control variables (Linux-specific) */
volatile uint8_t gbMcaspPaused = 1u;  /* Start paused by default */
static uint32_t call_count = 0;

/* Global CMA buffer pointer for shared memory polling (Linux-specific) */
static RtInfo *g_cmaRtBuffer = NULL;

/* External variables from original IPC */
extern uint8_t g_rpmsgBuf[IPC_RPMESSAGE_MAX_MSG_SIZE];
extern RPMessage_Object g_rpmsgRecvObject;
extern volatile uint8_t gbShutdown;

/* External shutdown variables */
extern volatile uint8_t gbShutdownRemotecoreID;

/* Linux-specific IPC task variables */
StackType_t gIpcTaskStack[DSP_IPC_TASK_SIZE];
StaticTask_t gIpcTaskObj;

/* ========================================================================== */
/*                          Function Definitions                             */
/* ========================================================================== */

/**
 * @brief Linux-specific IPC setup task for shared memory initialization
 *
 * This is a one-time setup task that:
 * - Receives shared memory buffer address from Linux
 * - Configures shared memory polling for MCASP control
 * - Sends setup completion acknowledgment
 * - Exits after setup (continuous operations handled by audio task)
 */
void SigchainDSP_Linux_IPC_recvTask(void *arg)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t recvMsgSize;
    uint16_t remoteCoreId;
    uint32_t remoteCoreEndPt;

    recvMsgSize = IPC_RPMESSAGE_MAX_MSG_SIZE;
    DebugP_log("[IPC] Ready to receive message...\r\n");

    status = RPMessage_recv(&g_rpmsgRecvObject, (char *) g_rpmsgBuf, (uint16_t *) &recvMsgSize,
                           &remoteCoreId, &remoteCoreEndPt, SystemP_WAIT_FOREVER);

    if (status != SystemP_SUCCESS || gbShutdown == 1u) {
        /* Determine and log specific exit reason */
        if (gbShutdown == 1u) {
            DebugP_log("[IPC] Early shutdown requested - task exiting\r\n");
        } else {
            DebugP_log("[IPC] Failed to receive message (status=%d) - task exiting\r\n", status);
        }
        return;
    }

    /* Process the setup message from Linux */
    if (recvMsgSize == sizeof(ipcMsgBuf_t))
    {
        ipcMsgBuf_t *cmaMsg = (ipcMsgBuf_t *) g_rpmsgBuf;

        DebugP_log("[IPC] CMA setup request\r\n", cmaMsg->paramsBuffer);

        if (cmaMsg->paramsBuffer != 0 && cmaMsg->paramsSize > 0)
        {
            /* Validate that paramsBuffer address is within the expected CMA memory region */
            uint32_t bufferAddr = cmaMsg->paramsBuffer;

            /* Check for integer overflow in buffer size calculation */
            if (cmaMsg->paramsSize == 0 || cmaMsg->paramsSize > CMA_REGION_SIZE ||
                bufferAddr > (UINT32_MAX - cmaMsg->paramsSize + 1))
            {
                DebugP_log("[CMA_SETUP] Invalid buffer size or potential overflow detected\r\n");
                g_cmaRtBuffer = NULL;
            }
            else
            {
                uint32_t bufferEnd = bufferAddr + cmaMsg->paramsSize - 1;

                if (bufferAddr >= CMA_BASE_ADDRESS && bufferAddr <= CMA_END_ADDRESS &&
                    bufferEnd >= CMA_BASE_ADDRESS && bufferEnd <= CMA_END_ADDRESS &&
                    cmaMsg->paramsSize >= sizeof(RtInfo))
                {
                    /* Address validation passed - safe to use */
                    g_cmaRtBuffer = (RtInfo*)(uintptr_t)cmaMsg->paramsBuffer;
                    DebugP_log("[CMA_SETUP] CMA buffer setup completed\r\n");
                }
                else
                {
                    DebugP_log("[CMA_SETUP] Invalid buffer address or size outside allowed CMA region\r\n");
                    g_cmaRtBuffer = NULL;  /* Reject invalid address */
                }
            }

            /* Send setup completion response */
            RPMessage_send((char *) g_rpmsgBuf, recvMsgSize, remoteCoreId, remoteCoreEndPt,
                          RPMessage_getLocalEndPt(&g_rpmsgRecvObject), SystemP_WAIT_FOREVER);

            DebugP_log("[IPC] Setup complete\r\n");
        }
    }
    else
    {
        DebugP_log("[ERROR] Message size mismatch! Received=%d, Expected=%d\r\n",
                   recvMsgSize, sizeof(ipcMsgBuf_t));
    }

    /* Setup complete*/
    DebugP_log("[IPC] Setup task completed - exiting\r\n");
    vTaskDelete(NULL);
}

/**
 * @brief Linux-specific IPC initialization wrapper
 *
 * Similar to SigchainDSP_IPC_init() but with key differences:
 * - Creates Linux-specific one-time setup task instead of continuous command processor
 *
 * This function should be called instead of SigchainDSP_IPC_init()
 * when SIG_CHAIN_LINUX_HOST is defined.
 */
void SigchainDSP_Linux_IPC_init()
{
    DebugP_log("[LINUX_IPC] Initializing Linux-specific IPC...\r\n");

    RPMessage_CreateParams createParams;
    int32_t status = SystemP_SUCCESS;

    RPMessage_CreateParams_init(&createParams);
    createParams.localEndPt = REMOTE_SERVICE_END_PT;

    status = RPMessage_construct(&g_rpmsgRecvObject, &createParams);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Announce using Linux endpoint */
    status = RPMessage_announce(CSL_CORE_ID_A53SS0_0, REMOTE_SERVICE_END_PT,
                                SIGCHAIN_RPMESSAGE_SERVICE);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Register a callback for the RP_MBOX messages from the Linux remoteproc driver*/
    IpcNotify_registerClient(IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                             &SigchainDSP_IPC_rpmsgCB, NULL);

    DebugP_log("[LINUX_IPC] Creating Linux-specific IPC receive task...\r\n");

    /* Create Linux-specific one-time setup task */
    TaskHandle_t linuxIpcTask = xTaskCreateStatic(
        SigchainDSP_Linux_IPC_recvTask, "Linux_IPC_recvTask",
        DSP_IPC_TASK_SIZE, NULL, DSP_IPC_TASK_PRI,
        gIpcTaskStack, &gIpcTaskObj);
    configASSERT(linuxIpcTask != NULL);

    DebugP_log("[LINUX_IPC] Linux IPC receive task created successfully\r\n");
}


/**
 * @brief Check shared memory for MCASP commands (Linux-specific function)
 *
 * This function updates DSP statistics and handles command processing.
 */
void SigchainDSP_checkSharedMemoryCommands(void)
{
    if (g_cmaRtBuffer == NULL) {
        call_count++;
        return;  /* Shared memory not initialized yet */
    }

    call_count++;

    /* Invalidate cache before reading commands from Linux */
    CacheP_inv((void*)g_cmaRtBuffer, sizeof(RtInfo), CacheP_TYPE_ALL);

    /* Check for MCASP commands from Linux */
    McaspCommand_e mcaspCmd = (McaspCommand_e)g_cmaRtBuffer->mcaspCommand;
    if (mcaspCmd != MCASP_CMD_NO_CHANGE) {
        if (mcaspCmd == MCASP_CMD_START) {
            gbMcaspPaused = 0;
        }
        else if (mcaspCmd == MCASP_CMD_STOP) {
            gbMcaspPaused = 1;
        }
    }

    /* Update DSP statistics continuously (every N calls = ~1 second) */
    if (call_count % STATS_UPDATE_FREQUENCY == 0) {

        /* Update ONLY DSP-owned fields individually */
        g_cmaRtBuffer->dspLoad = TaskP_loadGetTotalCpuLoad();  /* Raw value (e.g., 2534 = 25.34%) */
        g_cmaRtBuffer->cycleCount = gbMcaspPaused ? 0 : gRtInfo.cycleCount;  /* REAL CPU cycles from graph execution */

        /* Calculate REAL throughput: frames per second * frame size = processing capability */
        uint32_t localCycleCount = gRtInfo.cycleCount;
        if (gbMcaspPaused == 0 && localCycleCount > 0) {
            /* Real throughput based on DSP cycles: frame size scaled by processing efficiency */
            /* Get actual C7x clock frequency dynamically */
            float frames_per_second = (float)SOC_getSelfCpuClk() / (float)localCycleCount;
            g_cmaRtBuffer->throughput = (frames_per_second * AUDIO_FRAME_SIZE_BYTES) / (BYTES_TO_KB * BYTES_TO_KB);  /* MB/s */
        } else {
            g_cmaRtBuffer->throughput = 0.0f;  /* Zero when stopped */
        }

        /* Reset load counters for next measurement */
        TaskP_loadResetAll();

    }

    /* Update MCASP status for Linux */
    g_cmaRtBuffer->mcaspRunning = (gbMcaspPaused == 0) ? MCASP_STATE_RUNNING : MCASP_STATE_STOPPED;

    /* Write back to shared memory */
    CacheP_wb((void*)g_cmaRtBuffer, sizeof(RtInfo), CacheP_TYPE_ALL);
}

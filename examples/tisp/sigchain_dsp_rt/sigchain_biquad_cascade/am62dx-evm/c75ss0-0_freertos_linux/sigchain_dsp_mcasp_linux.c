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
 * \file sigchain_dsp_mcasp_linux.c
 *
 * \brief Linux-specific MCASP implementation with gRtInfo metrics and shared memory control.
 *        This file contains Linux-only modifications to avoid breaking other examples.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include "sigchain_platform.h"
#include "sigchain_dsp_mcasp.h"
#include "sigchain_ipc.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MCASP_PAUSE_DELAY_US            1000U        /* Sleep delay when MCASP paused (microseconds) */

/* ========================================================================== */
/*                          Function Declarations                            */
/* ========================================================================== */

/* MCASP helper function declarations */
void SigchainDSP_McASP_setup(void);
void SigchainDSP_McASP_prime(void);
void SigchainDSP_McASP_audioStart(void);
void SigchainDSP_McASP_processAudioSamples(void);

/* TISP graph function */
void *create_graph(int32_t *data_buffer, uint32_t *srcStride);

/* Linux-specific MCASP functions */
void SigchainDSP_Linux_McASP_process(void *arg);
void SigchainDSP_Linux_McASP_setupAudioIO(void);

/* ========================================================================== */
/*                            Global Variables                               */
/* ========================================================================== */


/* External variables from other files (not declared in headers) */
extern volatile uint8_t gbShutdown;
extern volatile uint8_t gbShutdownRemotecoreID;
extern uint8_t sigBuf[];
extern uint32_t gPlotCaptureMode;
extern uint32_t graphError;
extern SemaphoreP_Object semTx, semRx;
extern uint32_t srcStride;
extern uint8_t data_buffer[];

/* FreeRTOS task variables */
extern TaskHandle_t gMcaspProcessTask;
extern StaticTask_t gMcaspProcessTaskObj;
extern StackType_t gMcaspProcessTaskStack[];

/* ========================================================================== */
/*                          Function Definitions                             */
/* ========================================================================== */

/**
 * @brief Linux-specific MCASP processing task with shared memory control
 *
 * This function is the Linux variant that includes:
 * - Shared memory command checking for MCASP control
 * - Proper shutdown coordination
 * - TISP metrics integration
 */
void SigchainDSP_Linux_McASP_process(void *arg)
{
    volatile uint8_t done = 0;

    /* Initialize MCASP semaphores */
    SemaphoreP_constructCounting(&semTx, 0, NUM_BUFS);
    SemaphoreP_constructCounting(&semRx, 0, NUM_BUFS);

    /* Initialize gRtInfo for TISP metrics */
    memset(&gRtInfo, 0, sizeof(RtInfo));
    gRtInfo.dspLoad = 0;         /* Integer */
    gRtInfo.cycleCount = 0;
    gRtInfo.throughput = 0.0f;

    /* Standard MCASP setup */
    SigchainDSP_McASP_setup();
    SigchainDSP_McASP_prime();
    SigchainDSP_McASP_audioStart();

    /* Initialize TISP signal processing graph */
    gSpGraph = create_graph((int32_t *) data_buffer, &srcStride);

    DebugP_log("[TISP_GRAPH] Signal processing graph initialized: %s\r\n",
               gSpGraph ? "SUCCESS" : "FAILED");

    while (!done)
    {
        /* Check for shutdown request from Linux */
        if (gbShutdown == 1u)
        {
            DebugP_log("[AUDIO TASK] Shutdown requested, stopping audio processing...\r\n");
            done = 1;
            break;
        }

        /* Check for MCASP commands*/
        SigchainDSP_checkSharedMemoryCommands();

        /* Only wait for MCASP callbacks if MCASP is supposed to be running */
        if (gbMcaspPaused == 0) {
            /* Wait for MCASP RX callback - but only if we should be running */
            SemaphoreP_pend(&semTx, SystemP_WAIT_FOREVER);
            SemaphoreP_pend(&semRx, SystemP_WAIT_FOREVER);

            /* Process audio samples */
            SigchainDSP_McASP_processAudioSamples();
        } else {
            /* Add small delay to prevent busy-waiting */
            ClockP_usleep(MCASP_PAUSE_DELAY_US);
        }
    }

    /* Cleanup when shutting down */
    if (gbShutdown == 1u)
    {
        MCASP_Handle mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

        /* Stop MCASP transfers cleanly */
        MCASP_stopTransferTx(mcaspHandle);
        MCASP_stopTransferRx(mcaspHandle);

        Drivers_close();
        DebugP_log("[DSP Signal Chain] Drivers closed\r\n");

        System_deinit();
        DebugP_log("[DSP Signal Chain] System_deinit() completed\r\n");

        /* Send ACK using proper remoteproc mechanism */
        if (gbShutdownRemotecoreID) {
            IpcNotify_sendMsg(gbShutdownRemotecoreID, IPC_NOTIFY_CLIENT_ID_RP_MBOX,
                              IPC_NOTIFY_RP_MBOX_SHUTDOWN_ACK, 1u);
            DebugP_log("[DSP Signal Chain] Shutdown ACK sent successfully\r\n");
        }

        __asm(" IDLE");
    }
}

/**
 * @brief Linux-specific audio I/O setup function
 *
 * Creates the Linux-specific MCASP processing task instead of the original one.
 * This function should be called instead of SigchainDSP_McASP_setupAudioIO()
 * when SIG_CHAIN_LINUX_HOST is defined.
 */
void SigchainDSP_Linux_McASP_setupAudioIO()
{
    /* Create the Linux-specific MCASP processing task */
    gMcaspProcessTask = xTaskCreateStatic(
        SigchainDSP_Linux_McASP_process, "Linux_McASP_Process",
        MCASP_PROCESS_TASK_STACKSIZE, NULL, MCASP_PROCESS_TASK_PRI,
        gMcaspProcessTaskStack, &gMcaspProcessTaskObj);
    configASSERT(gMcaspProcessTask != NULL);

}

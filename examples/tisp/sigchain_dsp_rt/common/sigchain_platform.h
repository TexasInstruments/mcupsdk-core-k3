/*
 *  Copyright (C) 2013-2025 Texas Instruments Incorporated
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

#ifndef __SIGCHAIN_PLATFORM_H__
#define __SIGCHAIN_PLATFORM_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <drivers/gpio.h>
#include <drivers/mcasp.h>
#include <drivers/pinmux.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/TaskP.h>
#include <strings.h>

#include "sigchain_ipc.h"
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

#include "FreeRTOS.h"
#include "task.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MAIN_TASK_PRI (configMAX_PRIORITIES - 1)
#define MAIN_TASK_SIZE (65536U / sizeof(configSTACK_DEPTH_TYPE))

#define SIGCHAIN_IDLE_TASK_PRI (tskIDLE_PRIORITY)
#define SIGCHAIN_IDLE_TASK_STACKSIZE (65536U / sizeof(configSTACK_DEPTH_TYPE))

#define DSP_IPC_TASK_PRI (configMAX_PRIORITIES - 1)
#define DSP_IPC_TASK_SIZE (65536U / sizeof(configSTACK_DEPTH_TYPE))

#if defined(SOC_AM62DX)
#define SOC_NAME "am62dx"
#define CORE_NAME "C7504"
#endif

#if defined(SOC_AM275X)
#define SOC_NAME "am275x"
#define CORE_NAME "C7524"
#endif

#define SAMPL_RATE (48000U)
#define AUDIO_BLOCK_SIZE (64U)

#define DAC_STRIDE (8U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct __attribute__((__packed__))
{
    uint32_t dspLoad;
    uint32_t cycleCount;
    float throughput;
} RtInfo;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern uint32_t Sigchain_Alpha_Cmd_Packet[MAX_ALPHA_CMD_BUFFER];
extern SemaphoreP_Object semCmdPkt;
extern SemaphoreP_Object gSemExit;
extern uint32_t gCmdAddr;
extern uint32_t gCmdSize;
extern void *gSpGraph;
extern RtInfo gRtInfo;
extern uint8_t chmap[8];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void SigchainDSP_IPC_init();
int32_t SigchainDSP_IPC_recv(uint8_t *buf, uint32_t *bufSize);
int32_t SigchainDSP_IPC_send(uint8_t *buf, uint32_t bufSize);

void SigchainDSP_IPC_syncRemote();
void SigchainDSP_McASP_setupAudioIO();
void SigchainDSP_Cmdproc_createIdleTask();

#if defined(__cplusplus)
}
#endif

#endif /* __SIGCHAIN_PLATFORM_H__ */

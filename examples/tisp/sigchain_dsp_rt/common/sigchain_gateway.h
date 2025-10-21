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

#ifndef __SIGCHAIN_GATEWAY_H__
#define __SIGCHAIN_GATEWAY_H__

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

#define UART_MAX_BUFSIZE (1056U)
#define SIGCHAIN_UART_STX (0x02)
#define SIGCHAIN_UART_ETX (0x03)
#define SIGCHAIN_UART_OVERHEAD (0x04)

#define MAIN_TASK_PRI (configMAX_PRIORITIES - 1)
#define MAIN_TASK_SIZE (16384U / sizeof(configSTACK_DEPTH_TYPE))

#define UART_TASK_PRI (configMAX_PRIORITIES - 1)
#define UART_TASK_SIZE (16384U / sizeof(configSTACK_DEPTH_TYPE))

#define IPC_TASK_PRI (configMAX_PRIORITIES - 1)
#define IPC_TASK_SIZE (16384U / sizeof(configSTACK_DEPTH_TYPE))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern uint8_t Cmd_Packet[MAX_ALPHA_CMD_BUFFER];
extern SemaphoreP_Object gSemExit;

#define SIGCHAIN_CMD_GET_CMD(x) *(uint16_t *) &x[3]
#define SIGCHAIN_CMD_EXIT_RESP (0x2900U)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void SigchainGateway_main(void *args);

int32_t configure_codec(void);
int32_t Board_clockgenConfig(I2C_Handle handle, uint8_t devAddr);

/* ipc send/recv public functions */
void SigchainGatewayIPC_syncRemote();
void SigchainGatewayIPC_init();
int32_t SigchainGatewayIPC_send(uint8_t *buf, uint32_t bufSize);

/* uart public functions */
void SigchainGatewayUART_init();
int32_t SigchainGatewayUART_send(uint8_t *buf, uint32_t bufSize);
int32_t SigchainGatewayUART_recvPkt();
void SigchainGatewayUART_sendPacket(uint8_t *buf, uint16_t bufLen);

#if defined(__cplusplus)
}
#endif

#endif /* __SIGCHAIN_GATEWAY_H__ */

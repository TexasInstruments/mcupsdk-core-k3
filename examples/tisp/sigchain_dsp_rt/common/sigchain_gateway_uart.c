/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

#include "sigchain_gateway.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

SemaphoreP_Object g_semUartTx;
SemaphoreP_Object g_semUartRx;

uint32_t g_uartTxBytesCnt = 0;
uint32_t g_uartRxBytesCnt = 0;
UART_Transaction g_transRx;
UART_Transaction g_transTx;

uint8_t UART_Buf[UART_MAX_BUFSIZE];
uint8_t UART_Resp[UART_MAX_BUFSIZE];
uint8_t g_rcvdByte = 0;

/* uart process task */
StackType_t g_uartTaskStack[UART_TASK_SIZE];
StaticTask_t g_uartTaskObj;
TaskHandle_t g_uartTask;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SigchainGatewayUART_txCB(UART_Handle handle, UART_Transaction *trans)
{
    g_uartTxBytesCnt = trans->count;
    SemaphoreP_post(&g_semUartTx);
}

void SigchainGatewayUART_rxCB(UART_Handle handle, UART_Transaction *trans)
{
    g_uartRxBytesCnt = trans->count;
    SemaphoreP_post(&g_semUartRx);
}

void SigchainGatewayUART_print(uint8_t *buf, uint32_t bufLen)
{
    uint32_t i;
    DebugP_log("UART Packet:\r\n");
    for (i = 0; i < bufLen; i++)
    {
        DebugP_log("0x%02X ", buf[i]);
        if ((i + 1) % 16 == 0)
        {
            DebugP_log("\r\n");
        }
    }
    DebugP_log("\r\n");
}

void SigchainGatewayUART_task(void *arg)
{
    int32_t done = 0;
    uint8_t *buf = NULL;
    uint16_t bufLen;

    DebugP_log("sigchain_gateway_uart_task\r\n");

    while (!done)
    {
        /* Wait for UART packet */
        SigchainGatewayUART_recvPkt();

        /* send packet to dsp */
        memcpy(&bufLen, &UART_Buf[1], sizeof(uint16_t));
        buf = (uint8_t *) &UART_Buf[3];
        SigchainGatewayIPC_send(buf, bufLen);

    } /* While done loop*/

    vTaskDelete(NULL);
}

void SigchainGatewayUART_init()
{
    int32_t status = SystemP_SUCCESS;

    status = SemaphoreP_constructBinary(&g_semUartTx, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    status = SemaphoreP_constructBinary(&g_semUartRx, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    g_uartTask = xTaskCreateStatic(
        SigchainGatewayUART_task, "SigchainGatewayUART_task", UART_TASK_SIZE,
        NULL, UART_TASK_PRI, g_uartTaskStack, &g_uartTaskObj);
    configASSERT(g_uartTask != NULL);
}

int32_t SigchainGatewayUART_send(uint8_t *buf, uint32_t bufSize)
{
    int32_t status = SystemP_SUCCESS;
    UART_Handle uartHandle = gUartHandle[CONFIG_UART_TUNER];

    UART_Transaction_init(&g_transTx);

    g_uartTxBytesCnt = 0U;
    g_transTx.buf = buf;
    g_transTx.count = bufSize;
    status = UART_write(uartHandle, &g_transTx);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Wait for write completion */
    SemaphoreP_pend(&g_semUartTx, SystemP_WAIT_FOREVER);
    DebugP_assert(g_uartTxBytesCnt == bufSize);

    if (SIGCHAIN_CMD_GET_CMD(buf) == SIGCHAIN_CMD_EXIT_RESP)
    {
        SemaphoreP_post(&gSemExit);
    }

    return status;
}

int32_t SigchainGatewayUART_recv(uint8_t *buf, uint32_t bufSize)
{
    int32_t status = SystemP_SUCCESS;
    UART_Handle uartHandle = gUartHandle[CONFIG_UART_TUNER];

    g_uartRxBytesCnt = 0U;
    UART_Transaction_init(&g_transRx);
    g_transRx.buf = buf;
    g_transRx.count = bufSize;
    status = UART_read(uartHandle, &g_transRx);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Wait for read completion */
    SemaphoreP_pend(&g_semUartRx, SystemP_WAIT_FOREVER);

    DebugP_assert(g_uartRxBytesCnt == bufSize);

    return status;
}

uint8_t SigchainGatewayUART_checkSum(uint8_t *buf, uint16_t bufSize)
{
    uint32_t chksum = 0;
    uint32_t i = 0;

    for (i = 0; i < bufSize; i++)
    {
        chksum += buf[i];
    }

    return (uint8_t) (chksum % 256);
}

int32_t SigchainGatewayUART_recvPkt()
{
    uint8_t pos = 0;
    uint16_t pktLen = 0;
    int32_t status = SystemP_SUCCESS;
    uint8_t startByte = 0;

    do
    {
        SigchainGatewayUART_recv(&startByte, 1);
    } while (startByte != SIGCHAIN_UART_STX);

    memset(UART_Buf, 0, UART_MAX_BUFSIZE);
    /* received STX, proceed further */
    UART_Buf[pos] = startByte;
    pos++;

    SigchainGatewayUART_recv(&UART_Buf[pos], sizeof(uint16_t));
    memcpy(&pktLen, &UART_Buf[pos], sizeof(uint16_t));

    pos += sizeof(uint16_t);
    if (pktLen <= UART_MAX_BUFSIZE)
    {
        SigchainGatewayUART_recv(&UART_Buf[pos], pktLen);
        pos += pktLen;

        SigchainGatewayUART_recv(&UART_Buf[pos], 1);
        if (UART_Buf[pos] !=
            SigchainGatewayUART_checkSum(UART_Buf, pktLen + 3))
        {
            DebugP_log("Data read error ....\r\n");
        }
        else
        {
            /* valid packet, now read ETX */
            pos++;
            status = SigchainGatewayUART_recv(&UART_Buf[pos], 1);
            DebugP_assert(UART_Buf[pos] == SIGCHAIN_UART_ETX);

        }
    }

    return status;
}

void SigchainGatewayUART_sendPacket(uint8_t *buf, uint16_t bufLen)
{
    uint16_t pos = 0;

    /* initialize UART buffer */
    memset(UART_Resp, 0, UART_MAX_BUFSIZE);

    UART_Resp[pos++] = SIGCHAIN_UART_STX;
    memcpy(&UART_Resp[pos], &bufLen, sizeof(uint16_t));
    pos += sizeof(uint16_t);

    if (bufLen > 0)
    {
        memcpy(&UART_Resp[pos], buf, bufLen);
        pos += bufLen;
    }

    UART_Resp[pos++] = SigchainGatewayUART_checkSum(UART_Resp, bufLen + 3);
    UART_Resp[pos++] = SIGCHAIN_UART_ETX;

    SigchainGatewayUART_send(UART_Resp, pos);
}

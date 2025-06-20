/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

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
#include <string.h>
#include <stdio.h>
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"
#include <kernel/dpl/ClockP.h>
#include "enet_apputils.h"
#include "FreeRTOS.h"
#include "task.h"
#include "network_tcpserver.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define APP_SERVER_PORT_LOG  (8888U)
#define APP_SERVER_PORT_CMD  (8889U)
#define APP_SERVER_PORT_INP  (8890U)
#define APP_SERVER_PORT_OUT  (8891U)
#define APP_SOCK_PORT_CNT    (4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

SemaphoreP_Object gCountSemSockStats;
SemaphoreP_Object gPrintSemConnStats;

TCP_NetconnSockets tcpSockets = {
    .pServerSocketCmd = NULL,
    .pClientSocketCmd = NULL,
    .pServerSocketLog = NULL,
    .pClientSocketLog = NULL,
    .pServerSocketInp = NULL,
    .pClientSocketInp = NULL,
    .pServerSocketOut = NULL,
    .pClientSocketOut = NULL
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Task for listening and accepting connections for Command */

static void AppTcp_ServerTaskCmd(void *arg)
{
    err_t err;
    LWIP_UNUSED_ARG(arg);

    tcpSockets.pServerSocketCmd = netconn_new(NETCONN_TCP);
    netconn_bind(tcpSockets.pServerSocketCmd, IP_ADDR_ANY, APP_SERVER_PORT_CMD);
    LWIP_ERROR("[CMD] Tcpecho: invalid conn\r\n", (tcpSockets.pServerSocketCmd != NULL), return;);

    /* Tell connection to go into listening mode. */
    netconn_listen(tcpSockets.pServerSocketCmd);

    /* Grab new connection. */
    err = netconn_accept(tcpSockets.pServerSocketCmd, &tcpSockets.pClientSocketCmd);

    SemaphoreP_pend(&gPrintSemConnStats, SystemP_WAIT_FOREVER);
    printf("[CMD] Accepted new connection %p\r\n", tcpSockets.pClientSocketCmd);

    /* Process the new connection. */
    if (err < ERR_OK)
    {
        DebugP_log("[CMD] Unable to accept connection: errno %d\r\n", err);
    }
    SemaphoreP_post(&gPrintSemConnStats);

    SemaphoreP_post(&gCountSemSockStats);

    vTaskDelete( NULL);
}

/* Task for listening and accepting connections for Log */

static void AppTcp_ServerTaskLog(void *arg)
{
    err_t err;
    LWIP_UNUSED_ARG(arg);

    tcpSockets.pServerSocketLog = netconn_new(NETCONN_TCP);
    netconn_bind(tcpSockets.pServerSocketLog, IP_ADDR_ANY, APP_SERVER_PORT_LOG);
    LWIP_ERROR("[LOG] Tcpecho: invalid conn\r\n", (tcpSockets.pServerSocketLog != NULL), return;);

    /* Tell connection to go into listening mode. */
    netconn_listen(tcpSockets.pServerSocketLog);

    /* Grab new connection. */
    err = netconn_accept(tcpSockets.pServerSocketLog, &tcpSockets.pClientSocketLog);

    SemaphoreP_pend(&gPrintSemConnStats, SystemP_WAIT_FOREVER);
    printf("[LOG] Accepted new connection %p\r\n", tcpSockets.pClientSocketLog);

    /* Process the new connection. */
    if (err < ERR_OK)
    {
        DebugP_log("[LOG] Unable to accept connection: errno %d\r\n", err);
    }
    SemaphoreP_post(&gPrintSemConnStats);

    SemaphoreP_post(&gCountSemSockStats);

    vTaskDelete( NULL);
}

/* Task for listening and accepting connections for Input Data*/

static void AppTcp_ServerTaskInp(void *arg)
{
    err_t err;
    LWIP_UNUSED_ARG(arg);

    tcpSockets.pServerSocketInp = netconn_new(NETCONN_TCP);
    netconn_bind(tcpSockets.pServerSocketInp, IP_ADDR_ANY, APP_SERVER_PORT_INP);
    LWIP_ERROR("[INP] Tcpecho: invalid conn\r\n", (tcpSockets.pServerSocketInp != NULL), return;);

    /* Tell connection to go into listening mode. */
    netconn_listen(tcpSockets.pServerSocketInp);

    /* Grab new connection. */
    err = netconn_accept(tcpSockets.pServerSocketInp, &tcpSockets.pClientSocketInp);

    SemaphoreP_pend(&gPrintSemConnStats, SystemP_WAIT_FOREVER);
    printf("[INP] Accepted new connection %p\r\n", tcpSockets.pClientSocketInp);

    /* Process the new connection. */
    if (err < ERR_OK)
    {
        DebugP_log("[INP] Unable to accept connection: errno %d\r\n", err);
    }
    SemaphoreP_post(&gPrintSemConnStats);

    SemaphoreP_post(&gCountSemSockStats);

    vTaskDelete( NULL);
}

/* Task for listening and accepting connections for Output Data */

static void AppTcp_ServerTaskOut(void *arg)
{
    err_t err;
    LWIP_UNUSED_ARG(arg);

    tcpSockets.pServerSocketOut = netconn_new(NETCONN_TCP);
    netconn_bind(tcpSockets.pServerSocketOut, IP_ADDR_ANY, APP_SERVER_PORT_OUT);
    LWIP_ERROR("[OUT] Tcpecho: invalid conn\r\n", (tcpSockets.pServerSocketOut != NULL), return;);

    /* Tell connection to go into listening mode. */
    netconn_listen(tcpSockets.pServerSocketOut);

    /* Grab new connection. */
    err = netconn_accept(tcpSockets.pServerSocketOut, &tcpSockets.pClientSocketOut);

    SemaphoreP_pend(&gPrintSemConnStats, SystemP_WAIT_FOREVER);
    printf("[OUT] Accepted new connection %p\r\n", tcpSockets.pClientSocketOut);

    /* Process the new connection. */
    if (err < ERR_OK)
    {
        DebugP_log("[OUT] Unable to accept connection: errno %d\r\n", err);
    }
    SemaphoreP_post(&gPrintSemConnStats);

    SemaphoreP_post(&gCountSemSockStats);

    vTaskDelete( NULL);
}

void AppTcp_startServer()
{
    SemaphoreP_constructCounting(&gCountSemSockStats, 0, APP_SOCK_PORT_CNT);
    SemaphoreP_constructBinary(&gPrintSemConnStats, 1);

    /* Tasks for establishing server-client connection */
    sys_thread_new("AppTcp_ServerTaskLog", AppTcp_ServerTaskLog, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
    sys_thread_new("AppTcp_ServerTaskCmd", AppTcp_ServerTaskCmd, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
    sys_thread_new("AppTcp_ServerTaskInp", AppTcp_ServerTaskInp, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
    sys_thread_new("AppTcp_ServerTaskOut", AppTcp_ServerTaskOut, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);

    while(SemaphoreP_getCount(&gCountSemSockStats) < APP_SOCK_PORT_CNT)
    {
        /* Wait fot completion */
        ClockP_sleep(5);
    }

    SemaphoreP_destruct(&gPrintSemConnStats);
    SemaphoreP_destruct(&gCountSemSockStats);

    DebugP_log("All Connections are Up ...\r\n");
}

void App_closeServer(void *arg)
{
    /* Close connection and discard connection identifier. */
    netconn_close(tcpSockets.pClientSocketCmd);
    netconn_delete(tcpSockets.pClientSocketCmd);
    netconn_close(tcpSockets.pClientSocketInp);
    netconn_delete(tcpSockets.pClientSocketInp);
    netconn_close(tcpSockets.pClientSocketLog);
    netconn_delete(tcpSockets.pClientSocketLog);
    netconn_close(tcpSockets.pClientSocketOut);
    netconn_delete(tcpSockets.pClientSocketOut);
}
/*-----------------------------------------------------------------------------------*/

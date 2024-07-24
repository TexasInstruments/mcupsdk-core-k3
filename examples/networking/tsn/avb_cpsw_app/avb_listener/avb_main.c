/*
 *  Copyright (c) Texas Instruments Incorporated 2022-23
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
 * \file  tsnapp_main.c
 *
 * \brief This file contains the implementation of the Enet TSN example entry
 *        point
 */

/* ========================================================================== */
/*                              Include Files                                 */
/* ========================================================================== */

/* lwIP core includes */
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"

#include "ti_board_config.h"
#include "ti_board_open_close.h"
#include "ti_drivers_open_close.h"
#include "ti_enet_config.h"
#include "nrt_flow/app_tcpserver.h"
#include "ti_enet_lwipif.h"
#include "nrt_flow/dataflow.h"
#include "debug_log.h"
#include "tsninit.h"
#include "enetapp_cpsw.h"
#include "avb_listener.h"
#include "ShdMemCircularBufferP_nortos.h"

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/* dhcp struct for the ethernet netif */
static struct dhcp g_netifDhcp[ENET_SYSCFG_NETIF_COUNT];
static struct netif *g_pNetif[ENET_SYSCFG_NETIF_COUNT];

/* Handle to the Application interface for the LwIPIf Layer
 */
LwipifEnetApp_Handle hlwipIfApp = NULL;

static void EnetApp_allocateIPAddress()
{
    sys_lock_tcpip_core();
    for (uint32_t  netifIdx = 0U; netifIdx < ENET_SYSCFG_NETIF_COUNT; netifIdx++)
    {
        dhcp_set_struct(g_pNetif[NETIF_INST_ID0 + netifIdx], &g_netifDhcp[NETIF_INST_ID0 + netifIdx]);

        const err_t err = dhcp_start(g_pNetif[NETIF_INST_ID0 + netifIdx]);
        EnetAppUtils_assert(err == ERR_OK);
    }
    sys_unlock_tcpip_core();
    return;
}

static void EnetApp_netifStatusChangeCb(struct netif *pNetif)
{
    if (netif_is_up(pNetif))
    {
        DebugP_log("[%d]Enet IF UP Event. Local interface IP:%s\r\n",
                    pNetif->num, ip4addr_ntoa(netif_ip4_addr(pNetif)));
    }
    else
    {
        DebugP_log("[%d]Enet IF DOWN Event\r\n", pNetif->num);
    }
    return;
}

static void EnetApp_netifLinkChangeCb(struct netif *pNetif)
{
    if (netif_is_link_up(pNetif))
    {
        DebugP_log("[%d]Network Link UP Event\r\n", pNetif->num);
    }
    else
    {
        DebugP_log("[%d]Network Link DOWN Event\r\n", pNetif->num);
    }
    return;
}

static void EnetApp_setupNetif()
{
    ip4_addr_t ipaddr, netmask, gw;

    ip4_addr_set_zero(&gw);
    ip4_addr_set_zero(&ipaddr);
    ip4_addr_set_zero(&netmask);

    DebugP_log("Starting lwIP, local interface IP is dhcp-enabled\r\n");
    hlwipIfApp = LwipifEnetApp_getHandle();
    for (uint32_t netifIdx = 0U; netifIdx < ENET_SYSCFG_NETIF_COUNT; netifIdx++)
    {
        /* Open the netif and get it populated*/
        g_pNetif[netifIdx] = LwipifEnetApp_netifOpen(hlwipIfApp, NETIF_INST_ID0 + netifIdx, &ipaddr, &netmask, &gw);
        netif_set_status_callback(g_pNetif[netifIdx], EnetApp_netifStatusChangeCb);
        netif_set_link_callback(g_pNetif[netifIdx], EnetApp_netifLinkChangeCb);
        netif_set_up(g_pNetif[NETIF_INST_ID0 + netifIdx]);
    }
    LwipifEnetApp_startSchedule(hlwipIfApp, g_pNetif[ENET_SYSCFG_DEFAULT_NETIF_IDX]);
}

static void EnetApp_tcpipInitCompleteCb(void *pArg)
{
    sys_sem_t *pSem = (sys_sem_t*)pArg;
    EnetAppUtils_assert(pArg != NULL);

    /* init randomizer again (seed per thread) */
    srand((unsigned int)sys_now()/1000);

    EnetApp_setupNetif();

    EnetApp_allocateIPAddress();

    sys_sem_signal(pSem);
}

static void EnetApp_setupNetworkStack()
{
    sys_sem_t pInitSem;
    const err_t err = sys_sem_new(&pInitSem, 0);
    EnetAppUtils_assert(err == ERR_OK);

    tcpip_init(EnetApp_tcpipInitCompleteCb, &pInitSem);

    /* wait for TCP/IP initialization to complete */
    sys_sem_wait(&pInitSem);
    sys_sem_free(&pInitSem);

    return;
}

static void EnetApp_shutdownNetworkStack()
{
    for (uint32_t netifIdx = 0U; netifIdx < ENET_SYSCFG_NETIF_COUNT; netifIdx++)
    {
        LwipifEnetApp_netifClose(hlwipIfApp, NETIF_INST_ID0 + netifIdx);
    }
    return;
}

static int32_t EnetApp_isNetworkUp(struct netif* netif_)
{
    return (netif_is_up(netif_) && netif_is_link_up(netif_) && !ip4_addr_isany_val(*netif_ip4_addr(netif_)));
}

extern EnetApp_Cfg gEnetAppCfg;

/* client ID that is used to send and receive messages */
uint32_t gClientId = 4u;

void ipc_notify_msg_handler_main_core(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args)
{
    SemaphoreP_post(&gEnetAppCfg.startListnerSemObj);
}

void EnetApp_mainTask(void *args)
{
    EnetPer_AttachCoreOutArgs attachCoreOutArgs;
    EnetApp_HandleInfo handleInfo;
    EnetApp_GetMacAddrOutArgs outArgs;
    int32_t status;
    uint32_t shmElemSize = 1536U;
    uint32_t shmElemCount = 32U;
    void *pShdMemBuffStartAdd = (void *)0xA3000000;

    DebugP_log("==========================\r\n");
    DebugP_log("       TSN CPSW App       \r\n");
    DebugP_log("==========================\r\n");

    status = SemaphoreP_constructBinary(&gEnetAppCfg.startListnerSemObj, 0);
    DebugP_assert(SystemP_SUCCESS == status);
    status = IpcNotify_registerClient(gClientId, ipc_notify_msg_handler_main_core, NULL);
    DebugP_assert(status==SystemP_SUCCESS);
    EnetApp_initAppCfg(&attachCoreOutArgs, &handleInfo);
    EnetApp_getMacAddress(ENET_DMA_RX_CH0, &outArgs);
    EnetAppUtils_assert(outArgs.macAddressCnt == 1);
    EnetUtils_copyMacAddr(gEnetAppCfg.macAddr, outArgs.macAddr[outArgs.macAddressCnt - 1]);
    EnetApp_addBroadcastEntry();
    if (EnetApp_initTsn())
    {
        DebugP_log("EnetApp_initTsn failed\r\n");
    }
    else
    {
        gEnetAppCfg.hShmListenerQ = ShdMemCircularBufferP_create(&gEnetAppCfg.shmQObjMem,
                                                                (const void*)pShdMemBuffStartAdd,
                                                                shmElemCount,
                                                                shmElemSize);
        EnetAppUtils_assert(gEnetAppCfg.hShmListenerQ != NULL);
        ShdMemCircularBufferP_initQ(gEnetAppCfg.hShmListenerQ, 0U, shmElemCount);
        avbListener_createTask();
        IpcNotify_syncAll(SystemP_WAIT_FOREVER);

        EnetApp_setupNetworkStack();

        uint32_t netupMask = 0;
        /* wait for atleast one Network Interface to get IP */
        while (netupMask == 0)
        {
            for(uint32_t netifIdx = 0; netifIdx < ENET_SYSCFG_NETIF_COUNT; netifIdx++)
            {
                if (EnetApp_isNetworkUp(g_pNetif[netifIdx]))
                {
                    netupMask |= (1 << netifIdx);
                }
                else
                {
                    DebugP_log("[%d]Waiting for network UP ...\r\n",g_pNetif[netifIdx]->num);
                }
                ClockP_sleep(2);
            }
        }

        DebugP_log("Network is UP ...\r\n");
        ClockP_sleep(2);
        AppTcp_startServer();
        while (BTRUE)
        {
            // Print CPU load
            ClockP_usleep(1000);
            EnetApp_printCpuLoad();
            TaskP_yield();
        }
        EnetApp_stopTsn();
        EnetApp_deInitTsn();
        EnetApp_shutdownNetworkStack();
    }
}

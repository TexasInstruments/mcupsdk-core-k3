/*
 *  Copyright (c) Texas Instruments Incorporated 2023
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
/*                              Include Files                                 */
/* ========================================================================== */
#include <tsn_uniconf/yangs/yang_db_runtime.h>
#include <tsn_uniconf/yangs/yang_modules.h>
#include <tsn_uniconf/yangs/ietf-interfaces_access.h>
#include <tsn_uniconf/ucman.h>
#include <tsn_uniconf/uc_dbal.h>
#include <xmrpd/xmrpdconf/mrpgcfg.h>
#include <xmrpd/mrpman.h>
#include <xmrpd/mrp_map.h>
#include "debug_log.h"
#include "tsninit.h"
#include "common.h"

#include "avtp_xmrpd.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define AVTPD_TASK_PRIORITY     (2)
#define TALKER_TASK_PRIORITY    (2)
#define LISTENER_TASK_PRIORITY  (2)
#define XMRPD_TASK_PRIORITY     (2)
#define XMRPC_TASK_PRIORITY     (2)

// Currently MRP is working with 1 talker/1 listener
#define AVTPD_TASK_NAME         "avtpd_task"
#define TALKER_TASK_NAME        "talker_task"
#define LISTENER_TASK_NAME      "listener_task"
#define XMRPD_TASK_NAME         "xmrpd_task"
#define XMRP_CLIENT_TASK_NAME   "xmrpd_client_task"

#define MVRP_APPS_NO            1
#define MSRP_DOMAINS_NO         1
#define MSRP_TA_NO              1

#define PROTOCOL_ENABLE_STR "/excelfore-tsn-remote/tsn-remote/instances/instance|instance-index:%d|/external-control-man/control-objects|port:%s|protocol:%s/mrp-protocol|/external-control"
#define TC_CLASS_NODE       "/ietf-interfaces/interfaces/interface|name:%s|/bridge-port/traffic-class/"
#define TC_NUM_STR          TC_CLASS_NODE"traffic-class-table/number-of-traffic-classes"
#define TC_PRIORITY_STR     TC_CLASS_NODE"traffic-class-table/priority%d"
#define TC_LQUEUE_STR       TC_CLASS_NODE"tc-data|tc:%d|/lqueue"
#define TC_PQUEUE_NO_STR    TC_CLASS_NODE"number-of-pqueues"
#define TC_PQUEUE_MAP_STR   TC_CLASS_NODE"pqueue-map|pqueue:%d|/lqueue"
#define TC_MAX_FRAME_SZ_STR TC_CLASS_NODE"tc-data|tc:%d|/max-frame-size"
#define TC_CBS_ENABLED_STR  TC_CLASS_NODE"cbs-enabled"
#define TC_AD_SLOPE_STR     TC_CLASS_NODE"tc-data|tc:%d|/admin-idleslope"

#define DOT1Q_BRIDGE_COMPONENT "/ieee802-dot1q-bridge/bridges/bridge|name:%s|/component|name:%s|/"
#define DOT1Q_BRIDGE_PORTS_NO_STR DOT1Q_BRIDGE_COMPONENT"ports"
#define DOT1Q_BRIDGE_PORTS_BRPORT_STR DOT1Q_BRIDGE_COMPONENT"bridge-port"

#define BASE_VID 100
#define XMRPD_LINKSEMNAME "/xmrplinksem"

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct
{
    char* tcNum;                  // traffic-class/traffic-class-table/number-of-traffic-classes
    char* priorities[8];          // traffic-class/traffic-class-table/priority0
    char* tcLqueue[8];            // traffic-class/tc-data|tc:0|/lqueue
    char* pQueueNum;              // traffic-class/number-of-pqueues
    char* pQueueMap[8];           // traffic-class/pqueue-map|pqueue:0|/lqueue
    char* tcMaxFrameSize[2];      // traffic-class/tc-data|tc:1|/max-frame-size
    char* cbsEnable;              // traffic-class/cbs-enabled
    char* tcAdminIdleSlope[2];    // traffic-class/tc-data|tc:2|/admin-idleslope
} EnetApp_TrafficClassCfg_t;
/* ========================================================================== */
/*                            Local Variables                                */
/* ========================================================================== */
extern EnetApp_Ctx_t gAppCtx;
extern CB_SEM_T g_avtpd_ready_sem;

static uint8_t gAvtpdStackBuf[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));
static uint8_t gMrpdStackBuf[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));
static uint8_t gMrpCliStackBuf[TSN_TSK_STACK_SIZE] __attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));

EnetApp_TrafficClassCfg_t gTcCfg =
{
    .tcNum = "3",
    .priorities = {"0", "0", "1", "2", "0", "0", "0", "0"},
    .tcLqueue = {"2", "1", "0", "2", "2", "2", "2", "2"},
    .pQueueNum = "4",
    .pQueueMap = {"0", "1", "2", "2", "0", "0", "0", "0"},
    .tcMaxFrameSize = {"1500", "1500"},
    .cbsEnable = "1",
    .tcAdminIdleSlope = {"48448000", "98688000"}
};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
extern int AVTPD_MAIN(int argc, char *argv[]);
extern int XMRPD_MAIN(int argc, char *argv[]);
static int EnetApp_xmrpdDbInit(EnetApp_ModuleCtx_t* modCtx, EnetApp_dbArgs *dbargs);
static void *EnetApp_avtpdTask(void *arg);
static void *EnetApp_xmrpdTask(void *arg);
static void *EnetApp_xmrpcTask(void *arg);

#define AVTPD_TASK_ENTRY \
    [ENETAPP_AVTPD_TASK_IDX]={ \
        .enable = true, \
        .stopFlag = true, \
        .taskPriority = AVTPD_TASK_PRIORITY, \
        .taskName = AVTPD_TASK_NAME, \
        .stackBuffer = gAvtpdStackBuf, \
        .stackSize = sizeof(gAvtpdStackBuf), \
        .onModuleDBInit = NULL, \
        .onModuleRunner = EnetApp_avtpdTask, \
        .appCtx = &gAppCtx \
    }

#define XMRPD_TASK_ENTRY \
	[ENETAPP_XMRPD_TASK_IDX]={ \
        .enable = true, \
        .stopFlag = true, \
        .taskPriority = XMRPD_TASK_PRIORITY, \
        .taskName = XMRPD_TASK_NAME, \
        .stackBuffer = gMrpdStackBuf, \
        .stackSize = sizeof(gMrpdStackBuf), \
        .onModuleDBInit = EnetApp_xmrpdDbInit, \
        .onModuleRunner = EnetApp_xmrpdTask, \
        .appCtx = &gAppCtx \
    }

#define XMRPC_TASK_ENTRY \
	[ENETAPP_XMRPC_TASK_IDX]={ \
        .enable = true, \
        .stopFlag = true, \
        .taskPriority = XMRPC_TASK_PRIORITY, \
        .taskName = XMRP_CLIENT_TASK_NAME, \
        .stackBuffer = gMrpCliStackBuf, \
        .stackSize = sizeof(gMrpCliStackBuf), \
        .onModuleDBInit = NULL, \
        .onModuleRunner = EnetApp_xmrpcTask, \
        .appCtx = &gAppCtx \
    }

/// @brief AVTPD task
/// @param arg 
/// @return 
static void *EnetApp_avtpdTask(void *arg)
{
    char *argv[]={"avtpd", "-n", NULL};
    int timeout_ms = 3000;
    int res;

    res = uniconf_ready(NULL, UC_CALLMODE_THREAD, timeout_ms);
    if (res)
    {
        DPRINT("The uniconf must be run first !");
    }
    else
    {
        AVTPD_MAIN(2, argv);
    }
    return NULL;
}

int EnetApp_addMrpconfModCtx(EnetApp_ModuleCtx_t *modCtxTbl)
{
    int i;

    EnetApp_ModuleCtx_t mrpModCtx[ENETAPP_MAX_TASK_IDX] =
    {
        AVTPD_TASK_ENTRY,
        XMRPD_TASK_ENTRY,
        XMRPC_TASK_ENTRY
    };

    for (i = 0; i < ENETAPP_MAX_TASK_IDX; i++)
    {
        if (mrpModCtx[i].enable == true)
        {
            memcpy(&modCtxTbl[i], &mrpModCtx[i], sizeof(EnetApp_ModuleCtx_t));
        }
    }
    return 0;
}

#define YANGDB_RUNTIME_WRITE(key,val) do {                              \
        err = yang_db_runtime_put_oneline(ydrd, key, val, YANG_DB_ONHW_NOACTION); \
        DebugP_assert(err == 0);                                        \
    } while (0)

void EnetApp_registerIdleSlope(yang_db_runtime_dataq_t *ydrd, uc_notice_data_t* ucntd, const char* ndev)
{
    char buffer[MAX_KEY_SIZE];
    int err;
    for (int i=0; i<2; i++)
    {
        snprintf(buffer, sizeof(buffer), TC_MAX_FRAME_SZ_STR , ndev, i+1);
        YANGDB_RUNTIME_WRITE(buffer, gTcCfg.tcMaxFrameSize[i]);

        snprintf(buffer, sizeof(buffer), TC_AD_SLOPE_STR , ndev, i+1);
        YANGDB_RUNTIME_WRITE(buffer, gTcCfg.tcAdminIdleSlope[i]);

        err = yang_db_runtime_askaction(ydrd, ucntd);
        if (err != 0)
        {
            DPRINT("%s, Failed to trigger uniconf to write idleSlope", __func__);
        }
    }
}

static int EnetApp_setMrpExtControlConfig(yang_db_runtime_dataq_t *ydrd, uc_notice_data_t* ucntd, EnetApp_Ctx_t *appCtx)
{
    char buffer[MAX_KEY_SIZE];
    int ndev;
    int err;

    for (ndev = 0; ndev < appCtx->netdevSize; ndev++)
    {
        snprintf(buffer, sizeof(buffer), PROTOCOL_ENABLE_STR, 0, appCtx->netdev[ndev], "mvrp");
        YANGDB_RUNTIME_WRITE(buffer, "true");

        snprintf(buffer, sizeof(buffer), PROTOCOL_ENABLE_STR, 0, appCtx->netdev[ndev], "msrp");
        YANGDB_RUNTIME_WRITE(buffer, "true");

        // snprintf(buffer, sizeof(buffer), "/ietf-interfaces/interfaces/interface|name:%s|/bridge-port/traffic-class/traffic-class-table/number-of-traffic-classes", appCtx->netdev[ndev]);
        snprintf(buffer, sizeof(buffer), TC_NUM_STR, appCtx->netdev[ndev]);
        YANGDB_RUNTIME_WRITE(buffer, gTcCfg.tcNum);

        for (int i=0; i<8; i++)
        {
            snprintf(buffer, sizeof(buffer), TC_PRIORITY_STR , appCtx->netdev[ndev], i);
            YANGDB_RUNTIME_WRITE(buffer, gTcCfg.priorities[i]);

            snprintf(buffer, sizeof(buffer), TC_LQUEUE_STR , appCtx->netdev[ndev], i);
            YANGDB_RUNTIME_WRITE(buffer, gTcCfg.tcLqueue[i]);
        }

        snprintf(buffer, sizeof(buffer), TC_PQUEUE_NO_STR, appCtx->netdev[ndev]);
        YANGDB_RUNTIME_WRITE(buffer, gTcCfg.pQueueNum);

        for (int i=0; i<4; i++)
        {
            snprintf(buffer, sizeof(buffer), TC_PQUEUE_MAP_STR , appCtx->netdev[ndev], i);
            YANGDB_RUNTIME_WRITE(buffer, gTcCfg.pQueueMap[i]);
        }
    }

    snprintf(buffer, sizeof(buffer), TC_CBS_ENABLED_STR , appCtx->netdev[ndev]);
    YANGDB_RUNTIME_WRITE(buffer, gTcCfg.cbsEnable);

    snprintf(buffer, sizeof(buffer), DOT1Q_BRIDGE_PORTS_BRPORT_STR, "br0", "cmp00");
    YANGDB_RUNTIME_WRITE(buffer, appCtx->netdev[ndev]);

    snprintf(buffer, sizeof(buffer), DOT1Q_BRIDGE_PORTS_NO_STR, "br0", "cmp00");
    YANGDB_RUNTIME_WRITE(buffer, "1");
    
    DPRINT("%s", __func__);

    return 0;
}

static int EnetApp_xmrpdDbInit(EnetApp_ModuleCtx_t* modCtx, EnetApp_dbArgs *dbargs)
{
    if (g_avtpd_ready_sem != NULL)
    {
        return 0;
    }
    
    if (CB_SEM_INIT(&g_avtpd_ready_sem, 0, 0) < 0)
    {
        DPRINT("Failed to initialize g_avtpd_ready_sem!");
        return -1;
    }

    return 0;
}

static void *EnetApp_xmrpdTask(void *arg)
{
    EnetApp_ModuleCtx_t *modCtx = (EnetApp_ModuleCtx_t *)arg;
    // EnetApp_Ctx_t *appCtx = modCtx->appCtx;
    int res = -1;
    int timeout_ms = 3000;
    mrpmand_t *mrpmand;

    res = uniconf_ready(NULL, UC_CALLMODE_THREAD, timeout_ms);
    if (res)
    {
        DPRINT("The uniconf must be run first !");
    }
    else
    {
        mrpmand=mrpman_init(0, modCtx->appCtx->dbName, NULL, true);
        res=mrpman_open(mrpmand);
        if (res==0)
        {
            uint8_t ready=1;
            res=YDBI_SET_ITEM(nymrk1vk0, 0, XL4_EXTMOD_XL4MRP_XMRPD_READY,
			                            YDBI_STATUS, &ready, 1, YDBI_NO_NOTICE);
            if(res!=0)
            {
                DPRINT("failed to set XMRPD_READY");
            }
            else
            {
                DPRINT("xmrpd ready");
                res=mrpman_eloop(mrpmand, &modCtx->stopFlag); // blocking
            }
        }
        else
        {
            DPRINT("[%s] Cannot init mrpman. Exiting!!!", __func__);
        }

        mrpman_close(mrpmand);
    }
    return NULL;
}

static uint8_t to_priority_rank_reserved(uint8_t pcp, uint8_t rank)
{
    uint8_t priority_rank_reserved = 0;
	priority_rank_reserved|=(pcp<<5);
	
    priority_rank_reserved&=0xef;
	priority_rank_reserved|=(rank<<4)&0x10;

    // debug
    DPRINT("%s: Input pcp/rank[%d/%d] Extracted pcp/rank[%d/%d]", __func__, pcp, rank, (priority_rank_reserved>>5), (priority_rank_reserved>>4)&1);

    return priority_rank_reserved;
}

#if XMRPD_LISTENER_ENABLE==1
mode_type mrp_modes[MAX_AVB_APP]={LISTENER_MODE, LISTENER_MODE, LISTENER_MODE, LISTENER_MODE, LISTENER_MODE, LISTENER_MODE, LISTENER_MODE};
#else
mode_type mrp_modes[MAX_AVB_APP]={TALKER_MODE, TALKER_MODE, TALKER_MODE, TALKER_MODE, TALKER_MODE, TALKER_MODE, TALKER_MODE};
#endif
ub_bytearray8_t base_streamid={0x01, 0x02, 0x03, 0x04, 0x05,0x06, 0x00, 0x00};
ub_bytearray6_t dst_mac={0x91, 0xE0, 0xF0, 0x00, 0xFE,0x00};

static void EnetApp_initMrpCfg(xmrpd_app_data_t* xmrpd_app_info, uint8_t appno)
{
    mrp_data_t *mrp_data=&xmrpd_app_info->mrp_data[appno];
    
    mrp_data->vid=BASE_VID;
    mrp_data->mbps=1.0;
    mrp_data->mode=mrp_modes[appno];
    mrp_data->rec_tagged=false;

    mrp_data->domain_info.srclass_id = MSRP_SRClassID_B;
    mrp_data->domain_info.srclass_priority = MSRP_Priority_ClassB;
    mrp_data->domain_info.srclass_vid = BASE_VID;

    memcpy(mrp_data->stream_info.stream_id, base_streamid, sizeof(mrp_data->stream_info.stream_id));
    mrp_data->stream_info.stream_id[7] = appno;

    memset(mrp_data->sstream_id, 0, sizeof(mrp_data->sstream_id));
    bsid2ssid(mrp_data->stream_info.stream_id, mrp_data->sstream_id);

    memcpy(mrp_data->stream_info.destmac, dst_mac, sizeof(mrp_data->stream_info.destmac));
    mrp_data->stream_info.destmac[5] = appno;
    mrp_data->stream_info.vlan_id = BASE_VID;
    mrp_data->stream_info.max_frame_size = 1500;
    mrp_data->stream_info.max_intv_frames = 1;
    mrp_data->stream_info.priority_rank_reserved = to_priority_rank_reserved(MSRP_Priority_ClassB, MSRP_Rank_NonEmergency);
    mrp_data->stream_info.accum_latency = 100000;
    mrp_data->stream_info.failure_code = 0;

    mrp_data->stream_available = false;
}

static int EnetApp_registerUpDownNotice(EnetApp_Ctx_t *ctx, xmrpd_app_data_t* xmrpd_app_info)
{
    UC_NOTICE_SIG_T *sem=NULL;
    int res;

    (void)sprintf(xmrpd_app_info->semname, "%s%16"PRIx64, XMRPD_LINKSEMNAME, ub_rt_gettime64());
    for (int ndev = 0; ndev < ctx->netdevSize; ndev++)
    {
        if(sem==NULL){
            res=ydbi_set_ifupdown_ucnotice(ydbi_access_handle(), ctx->netdev[ndev], &sem, xmrpd_app_info->semname);
            if(!res && !xmrpd_app_info->linksem){xmrpd_app_info->linksem=sem;}
        }else{
            res=ydbi_set_ifupdown_ucnotice(ydbi_access_handle(), ctx->netdev[ndev], NULL, xmrpd_app_info->semname);
        }

        if(res!=0){
            DPRINT("%s:error in uc_nc_notice_register, %s\n", __func__, ctx->netdev[ndev]);
        }else{
            DPRINT("%s:uc_nc_notice_register, %s\n", __func__, ctx->netdev[ndev]);
        }
    }

    if(!xmrpd_app_info->linksem){
        DPRINT("%s:no semaphore is registered\n", __func__);
        return -1;
    }

    return 0;
}

static void *EnetApp_xmrpcTask(void *arg)
{
    EnetApp_ModuleCtx_t *modCtx = (EnetApp_ModuleCtx_t *)arg;
    EnetApp_Ctx_t *ctx = modCtx->appCtx;

    xmrpd_app_data_t xmrpd_app_info;
    xmrpd_app_info.dbname = modCtx->appCtx->dbName;
    xmrpd_app_info.avb_app_num = MRP_APP_NO;
    xmrpd_app_info.linksem = NULL;
    xmrpd_app_info.netdev = &ctx->netdev[0][0]; // tilld0

    if (EnetApp_registerUpDownNotice(ctx, &xmrpd_app_info) == -1)
    {
        return NULL;
    }

    // Init DB in here
    yang_db_item_access_t *ydbi = ydbi_access_handle();
    yang_db_runtime_dataq_t *ydrd;
    uc_notice_data_t* ucntd;
    ucntd = uc_notice_init(UC_CALLMODE_THREAD, xmrpd_app_info.dbname);
    ydrd = yang_db_runtime_init(ydbi->dbald, NULL);
    EnetApp_setMrpExtControlConfig(ydrd, ucntd, ctx);
    //

    xmrpd_app_info.dbald = ydbi->dbald;
    xmrpd_app_info.ucntd = ucntd;
    xmrpd_app_info.ydrd = ydrd;

    for (uint8_t i=0; i<xmrpd_app_info.avb_app_num; i++)
    {
        EnetApp_initMrpCfg(&xmrpd_app_info, i);
        xmrpd_app_info.mrp_data[i].netdev=&ctx->netdev[0][0]; // make a copy
    }

    /* Doesn't return */
	run_xmrpd_app(&xmrpd_app_info);

    return NULL;
}

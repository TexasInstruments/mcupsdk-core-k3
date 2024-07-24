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

#include <stdint.h>
#include <stdbool.h>
#include <tsn_unibase/unibase.h>
#include <tsn_combase/combase.h>
#include <tsn_combase/cb_tmevent.h>
#include <tsn_gptp/tilld/lld_gptp_private.h>
#include <tsn_unibase/unibase_binding.h>
#include <tsn_uniconf/yangs/yang_db_runtime.h>
#include <tsn_uniconf/yangs/yang_modules.h>
#include <tsn_uniconf/ucman.h>
#include <tsn_uniconf/uc_dbal.h>
#include <tsn_gptp/gptpmasterclock.h>
#include <core/enet_mod_tas.h>
#include <core/enet_types.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <enet_apputils.h>
#include <enet_ethutils.h>

#include "debug_log.h"
#include "tsninit.h"
#include "common.h"
#include "qosapp_misc.h"

/*============================================================================*/
/*                          Macros and Constants                              */
/*============================================================================*/

#define CBSAPP_TASK_PRIORITY   (1)
#define CBSAPP_TASK_NAME       "cbsapp_task"
#define CBSAPP_TALKER_NAME     "cbsapp_talker"
#define CBSAPP_LISTENER_NAME   "cbsapp_listener"

#define MAX_BANDWIDTH_BPS    (1000000000ULL)

typedef struct EnetCbsPerQueueParam
{
    uint8_t tc;        //!< Traffic class;
    uint8_t priority;  //!< HW queue priority
    uint16_t maxFrameSize; //!< Max payload size (without L2 header) in bytes
    uint32_t bitRateKbps;  //!< Sending bitrate for this traffic classs.
    uint64_t idleSlope;    //!< idle slope in bit per second unit.
} EnetCbsPerQueueParam_t;

typedef struct EnetCbsParam
{
    EnetCbsPerQueueParam_t cbsparams[8u]; //!< List of parameters to be configured for each queue.
    int length; //!< How many elements in the list of the parameters.
} EnetCbsParam_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void *EnetApp_cbsAppTask(void *arg);
static int EnetApp_cbsAppDbInit(EnetApp_ModuleCtx_t* mdctx,
                                EnetApp_dbArgs *dbargs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static uint8_t gEnetCbsAppStackBuf[TSN_TSK_STACK_SIZE]
__attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));

static uint8_t gEnetCbsAppTalkerStackBuf[TSN_TSK_STACK_SIZE]
__attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));

static uint8_t gEnetCbsAppListenerStackBuf[TSN_TSK_STACK_SIZE]
__attribute__ ((aligned(TSN_TSK_STACK_ALIGN)));

extern EnetApp_ModuleCtx_t gModCtxTable[ENETAPP_MAX_TASK_IDX];
extern EnetApp_Ctx_t gAppCtx;

static EnetQoSApp_AppCtx_t gEnetCbsAppCtx;

#define MBPS          (1000000ULL)
#define KBPS          (1000U)

/* If bitRatekbps of any stream is equal to 0, talker will not
 * send data for that stream
 */
static EnetCbsParam_t gCbsTestList[] = {
    {
        .cbsparams =
        {
            /* Initial test program to initialize bandwidth for all queues.
             * The order for setting idleSlope must be stared from highest
             * priority queue 7 and next lower priority queue in decending
             * order.
             */
            {
                .tc = 7, .priority = 7, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 1*KBPS
            },
            {
                .tc = 6, .priority = 6, .maxFrameSize = 1500,
                .bitRateKbps = 0U,
                .idleSlope = 1*KBPS
            },
            {
                .tc = 5, .priority = 5, .maxFrameSize = 1500,
                .bitRateKbps = 0U,
                .idleSlope = 1*KBPS
            },
            {
                .tc = 4, .priority = 4, .maxFrameSize = 1500,
                .bitRateKbps = 0U,
                .idleSlope = 1*KBPS
            },
            {
                .tc = 3, .priority = 3, .maxFrameSize = 1500,
                .bitRateKbps = 0U,
                .idleSlope = 1*KBPS
            },
            {
                .tc = 2, .priority = 2, .maxFrameSize = 1500,
                .bitRateKbps = 0U,
                .idleSlope = 1*KBPS
            },
            {
                .tc = 1, .priority = 0, .maxFrameSize = 1500,
                .bitRateKbps = 0U,
                .idleSlope = 1*KBPS
            },
            {
                .tc = 0, .priority = 1, .maxFrameSize = 1500,
                .bitRateKbps = 0U,
                .idleSlope =  1*KBPS
            },
        },
        .length = 8U,
    },
    {
        .cbsparams =
        {
            /** Disable CBS by setting a value 0 for the idleSlope,
             * and it must configured from the lowest to highest
             * priority queue in ascending order.
             */
            {
                .tc = 1, .priority = 0, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 0, .priority = 1, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 2, .priority = 2, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 3, .priority = 3, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 4, .priority = 4, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 5, .priority = 5, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 6, .priority = 6, .maxFrameSize = 1500,
                .bitRateKbps = 0U,
                .idleSlope = 0
            },
            {
                .tc = 7, .priority = 7, .maxFrameSize = 1500,
                .bitRateKbps = 30000,
                .idleSlope =  0
            },
        },
        .length = 8U,
    },
    {
        /**
         * Enable CBS for queue 7 with sufficient bandwidth.
         */
        .cbsparams =
        {
            {
                .tc = 7, .priority = 7, .maxFrameSize = 1500,
                .bitRateKbps = 30000,
                .idleSlope =  45*MBPS
            },
            {
                .tc = 0, .priority = 1, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 1, .priority = 0, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 2, .priority = 2, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 3, .priority = 3, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 4, .priority = 4, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 5, .priority = 5, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 6, .priority = 6, .maxFrameSize = 1500,
                .bitRateKbps = 0U,
                .idleSlope =  0
            },
        },
        .length = 8U,
    },
    {
        /**
         * Enable CBS for queue 7 with insufficient bandwidth.
         */
        .cbsparams =
        {
            {
                .tc = 7, .priority = 7, .maxFrameSize = 1500,
                .bitRateKbps = 30000,
                .idleSlope =  20*MBPS
            },
            {
                .tc = 0, .priority = 1, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 1, .priority = 0, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0,
            },
            {
                .tc = 2, .priority = 2, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0,
            },
            {
                .tc = 3, .priority = 3, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 4, .priority = 4, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
            {
                .tc = 5, .priority = 5, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0,
            },
            {
                .tc = 6, .priority = 6, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 0
            },
        },
        .length = 8U,
    },
    {
        /**
         * Enable CBS for all queues, sending 6 streams to 6 distint queues.
         */
        .cbsparams =
        {
            {
                .tc = 7, .priority = 7, .maxFrameSize = 1500,
                .bitRateKbps = 5000,
                .idleSlope = 8*MBPS
            },
            {
                .tc = 6, .priority = 6, .maxFrameSize = 1500,
                .bitRateKbps = 5000,
                .idleSlope = 8*MBPS
            },
            {
                .tc = 5, .priority = 5, .maxFrameSize = 1500,
                .bitRateKbps = 5000,
                .idleSlope = 8*MBPS
            },
            {
                .tc = 4, .priority = 4, .maxFrameSize = 1500,
                .bitRateKbps = 5000,
                .idleSlope = 8*MBPS
            },
            {
                .tc = 3, .priority = 3, .maxFrameSize = 1500,
                .bitRateKbps = 5000,
                .idleSlope = 8*MBPS
            },
            {
                .tc = 2, .priority = 2, .maxFrameSize = 1500,
                .bitRateKbps = 5000,
                .idleSlope = 8*MBPS
            },
            {
                .tc = 1, .priority = 0, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope = 8*MBPS
            },
            {
                .tc = 0, .priority = 1, .maxFrameSize = 1500,
                .bitRateKbps = 0,
                .idleSlope =  8*MBPS
            },
        },
        .length = 8U,
    },
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int EnetApp_addCbsAppModCtx(EnetApp_ModuleCtx_t *modCtxTbl)
{
    EnetApp_ModuleCtx_t cbsAppModCtx = {
        .enable = BTRUE,
        .stopFlag = BTRUE,
        .taskPriority = CBSAPP_TASK_PRIORITY,
        .taskName = CBSAPP_TASK_NAME,
        .stackBuffer = gEnetCbsAppStackBuf,
        .stackSize = sizeof(gEnetCbsAppStackBuf),
        .onModuleDBInit = EnetApp_cbsAppDbInit,
        .onModuleRunner = EnetApp_cbsAppTask,
        .appCtx = &gAppCtx
    };
    memcpy(&modCtxTbl[ENETAPP_CBS_TASK_IDX], &cbsAppModCtx,
           sizeof(EnetApp_ModuleCtx_t));
    return 0;
}

static int EnetApp_cbsAppDbInit(EnetApp_ModuleCtx_t* mdctx,
                                EnetApp_dbArgs *dbargs)
{
    // Do nothing.
    return 0;
}

static void EnetCbsApp_rxPacketHandler(void *arg,
                                       EnetQoSApp_Packet_t *pkt)
{
    // Do nothing
}

static void EnetCbsApp_startListener(EnetQoSApp_AppCtx_t *ctx)
{
    EnetQoSApp_TaskCfg_t cfg = {
        .name = CBSAPP_LISTENER_NAME,
        .priority  = QOSAPP_TASK_PRIORITY,
        .stackBuffer = gEnetCbsAppListenerStackBuf,
        .stackBufferSize = sizeof(gEnetCbsAppListenerStackBuf),
    };
    return EnetQoSApp_startListener(ctx, &cfg);
}

static void EnetCbsApp_showCbsTestCases(void)
{
    DPRINT("Please select one test case from the following:");
    DPRINT(" '1'-TestCase#1 1 stream@30Mbps without CBS configuration");
    DPRINT(" '2'-TestCase#2 1 stream@30Mbps with CBS configuration, reserve full bandwidth");
    DPRINT(" '3'-TestCase#3 1 stream@30Mbps with CBS configuration, reserve only 20Mbps");
    DPRINT(" '4'-TestCase#4 6 streams,each@5Mbps with CBS configuration, reserve full bandwidth ");
}

static void EnetCbsApp_showTestMenu(void)
{
    DPRINT("Please select one of the following options:");
    DPRINT(" 't'  -  Show all CBS test cases ");
    DPRINT(" 's'  -  Show stats info for all mac and host ports ");
    DPRINT(" 'S'  -  Reset stats info ");
}

static int EnetCbsApp_setCbsParam(EnetCbsParam_t *cbsPrm, char *ifname,
                                  EnetApp_dbArgs *dbarg, bool syncFlag)
{

    uc_dbald *dbald = dbarg->dbald;
    yang_db_runtime_dataq_t *ydrd = dbarg->ydrd;
    uc_notice_data_t *ucntd = dbarg->ucntd;
    int i, err = 0;
    char buffer[MAX_KEY_SIZE];
    char val[MAX_VAL_SIZE];
    char sem_name[64];
    uint32_t ksize;
    char key[UC_MAX_KEYSIZE];
    UC_NOTICE_SIG_T *sem = NULL;

    snprintf(buffer, sizeof(buffer),
             TRAFFIC_CLASS_NODE"/cbs-enabled",
             ifname);
    strcpy(val, "1");
    YANGDB_RUNTIME_WRITE(buffer, val);
    err = yang_db_runtime_askaction(ydrd, ucntd);
    if (err != 0)
    {
        DPRINT("%s, Failed to trigger uniconf to write idleSlope",
               __func__);
    }
    for (i = 0; i < cbsPrm->length; i++)
    {
        snprintf(buffer, sizeof(buffer),
                 TRAFFIC_CLASS_DATA_NODE"|tc:%d|/lqueue",
                 ifname, cbsPrm->cbsparams[i].tc);
        snprintf(val, sizeof(val), "%d", cbsPrm->cbsparams[i].tc);
        YANGDB_RUNTIME_WRITE(buffer, val);

        snprintf(buffer, sizeof(buffer),
                 TRAFFIC_CLASS_DATA_NODE"|tc:%d|/admin-idleslope",
                 ifname, cbsPrm->cbsparams[i].tc);
        if (syncFlag)
        {
            /*
             * We want to register a semaphore for a notification
             * on completing of admin-idleslope seeting at HW side
             * before going to the next TC's idle slope to make sure
             * the idleSlope of highest priority queue must be configured
             * first before going for the lower priority queue.
             * This restriction is only required at the initial time.
             * In the run time configuration, since all priority queues
             * have been configured, setting idle slope of any queue will
             * work fine.
             */
            snprintf(sem_name, sizeof(sem_name), "/cbs_wait_sem_%d",
                     cbsPrm->cbsparams[i].tc);
            /* The semaphore is created by the following API */
            err = yang_db_runtime_notice_register(ydrd, ucntd, buffer,
                                                  sem_name, &sem);
            if (err != 0)
            {
                DPRINT("%s, Failed to register semaphore for a notice",
                       __func__);
            }
        }
        /* Write the admin-idleslope to the DB */
        snprintf(val, sizeof(val), "%lld", cbsPrm->cbsparams[i].idleSlope);
        YANGDB_RUNTIME_WRITE(buffer, val);

        err = yang_db_runtime_askaction(ydrd, ucntd);
        if (err != 0)
        {
            DPRINT("%s, Failed to trigger uniconf to write idleSlope",
                   __func__);
            if (sem)
            {
                (void)uc_nc_notice_deregister_all(ucntd, dbald, sem_name);
            }
            break;
        }
        if (sem)
        {
            /* Waiting for setting completed at the HW with the timeout */
            if (uc_notice_sig_check(BTRUE, sem, 200, __func__))
            {
                DPRINT("%s, Failed to get a notice from the uniconf",
                       __func__);
            } else
            {
                err = uc_nc_get_notice_act(ucntd, dbald,
                                           sem_name, key, &ksize);
                if (err)
                {
                    DPRINT("There is no notice from the uniconf");
                }
            }
            /* Release the semaphore */
            err = uc_nc_notice_deregister_all(ucntd, dbald, sem_name);
            if (err != 0)
            {
                DPRINT("Failed to unregister sempahore");
                break;
            }
            sem = NULL;
        }
    }
    return err;
}

static void EnetCbsApp_runOneTestCase(EnetQoSApp_AppCtx_t *ctx,
                                      int tc, bool syncFlag)
{
    bool openDBSuccess = BFALSE;
    EnetApp_dbArgs dbarg;
    EnetApp_Ctx_t *ectx = (EnetApp_Ctx_t *)ctx->ectx;
    int idx = tc;
    int nValidStreams = 0;
    int err = 0, i;
    QoSAppStreamConfigParam_t stParam;

    stParam.nStreams = gCbsTestList[idx].length;
    for (i = 0; i < stParam.nStreams; i++)
    {
        stParam.streamParams[i].bitRateKbps = gCbsTestList[idx].cbsparams[i].bitRateKbps;
        if (stParam.streamParams[i].bitRateKbps)
        {
            nValidStreams++;
        }
        stParam.streamParams[i].payloadLen = gCbsTestList[idx].cbsparams[i].maxFrameSize;
        stParam.streamParams[i].tc = gCbsTestList[idx].cbsparams[i].tc;
        stParam.streamParams[i].priority = gCbsTestList[idx].cbsparams[i].priority;
    }

    do
    {
        err = EnetQoSApp_openDB(&dbarg, ectx->dbName, "w");
        if (err)
        {
            DPRINT("Failed to open DB!");
            break;
        }

        openDBSuccess = BTRUE;
        QoSAppCommonParam_t prm = {
            .netdev = ctx->netdev[ctx->ifidx],
            /* initialize with invalid TC value */
            {-1, -1, -1, -1, -1, -1, -1, -1},
            .nTCs = stParam.nStreams,
            .nQueues = QOSAPP_PRIORITY_MAX,
        };
        for (i = 0; i < prm.nTCs; i++)
        {
            prm.priority2TcMapping[gCbsTestList[idx].cbsparams[i].priority] =
                gCbsTestList[idx].cbsparams[i].tc;
        }
        err = EnetQoSApp_setCommonParam(&prm, &dbarg);
        if (err)
        {
            DPRINT("Failed to set common param!");
            break;
        }
        err = EnetCbsApp_setCbsParam(&gCbsTestList[idx],
                                     ctx->netdev[ctx->ifidx],
                                     &dbarg, syncFlag);
        if (err)
        {
            DPRINT("Failed to set CBS parameters !");
            break;
        }
    } while (0);
    if (openDBSuccess)
    {
        EnetQoSApp_closeDB(&dbarg);
    }
    if (err == 0 && nValidStreams > 0)
    {
        /* Stop the talker if it is running */
        EnetQoSApp_pauseTalker(ctx);

        /* Stark talker */
        EnetQoSApp_TaskCfg_t cfg =
        {
            .name = CBSAPP_TALKER_NAME,
            .priority  = QOSAPP_TASK_PRIORITY,
            .stackBuffer = gEnetCbsAppTalkerStackBuf,
            .stackBufferSize = sizeof(gEnetCbsAppTalkerStackBuf),
        };
        EnetQoSApp_startTalker(ctx, &cfg, &stParam);
    }
}

static void EnetCbsApp_runTestCases(EnetQoSApp_AppCtx_t *ctx)
{
    uint32_t num = 0;

    while (1)
    {
        EnetCbsApp_showCbsTestCases();
        DPRINT("Please input a number for testcase!");
        num =  EnetTsnApp_getNum();
        if (num > 0  && num <  sizeof(gCbsTestList)/sizeof(gCbsTestList[0]))
        {
            DPRINT("You choose the test case number: %d", num);
            break;
        }
        DPRINT("Invalid number for test case!");
    }
    if (num > 0)
    {
        bool syncFlag = (num == 1)? BFALSE: BTRUE;
        EnetCbsApp_runOneTestCase(ctx, num, syncFlag);
    }
}

// Return 1 if link up; 0: If link down
// Other than the above will be error.
static int EnetApp_getLinkStatus(EnetQoSApp_AppCtx_t *ctx)
{
    int res = -1;
    char sem_name[] = "/linkup_sem";
    EnetApp_dbArgs dbarg;
    int err;
    EnetApp_Ctx_t *ectx = (EnetApp_Ctx_t *)ctx->ectx;
    uint32_t ksize;
    char key[UC_MAX_KEYSIZE];
    uint32_t vsize;
    void *value = NULL;
    bool isDBOpened = BFALSE;

    if (!ctx->notice_sem)
    {
        err = ydbi_set_ifupdown_ucnotice(ydbi_access_handle(),
                                         ctx->netdev[ctx->ifidx],
                                         &ctx->notice_sem, sem_name);
        DebugP_assert(err == 0);
    }

    do
    {
        if (uc_notice_sig_check(BTRUE, ctx->notice_sem, 100, __func__))
        {
            break;
        }
        err = EnetQoSApp_openDB(&dbarg, ectx->dbName, "w");
        if (err)
        {
            DPRINT("Failed to open DB!");
            break;
        }
        isDBOpened = BTRUE;
        err = uc_nc_get_notice_act(dbarg.ucntd, dbarg.dbald,
                                 sem_name, key, &ksize);
        if(err != 0)
        {
            DPRINT("%s:failed in uc_nc_get_notice_act, err=%d",
                   __func__, err);
            break;
        }
        if ((ksize<5u) || (key[3]!=IETF_INTERFACES_OPER_STATUS))
        {
            DPRINT("%s: not expected notice", __func__);
            break;
        }
        err = uc_dbal_get(dbarg.dbald, key, ksize, &value, &vsize);
        if (err != 0)
        {
            DPRINT("%s: can't read oper-status", __func__);
            break;
        }
        if (memcmp(ctx->netdev[ctx->ifidx],
                   &key[6], strlen(ctx->netdev[ctx->ifidx])) == 0)
        {
            if (*((uint32_t*)value) == 1) {
                res = 1;
            } else
            {
                res = 0;
            }
        }
        (void)uc_dbal_get_release(dbarg.dbald, key,
                                  ksize, value, vsize);
    } while (0);

    if (res == 1)
    {
        /* We got what we want, no need the semaphore anymore, release it*/
        uc_nc_notice_deregister_all(dbarg.ucntd, dbarg.dbald, sem_name);
        ctx->notice_sem = NULL;
    }
    if (isDBOpened)
    {
        EnetQoSApp_closeDB(&dbarg);
    }
    return res;
}

static void *EnetApp_cbsAppTask(void *arg)
{
    int32_t status;
    EnetApp_ModuleCtx_t *modCtx = (EnetApp_ModuleCtx_t *)arg;
    EnetQoSApp_AppCtx_t *ctx =  &gEnetCbsAppCtx;

    status = EnetQoSApp_initialize(ctx, modCtx,
                                   EnetCbsApp_rxPacketHandler);
    DebugP_assert(status == 0);
    while (EnetApp_getLinkStatus(ctx) != 1)
    {
        DPRINT("Waiting for link UP on port: %s...",
               ctx->netdev[ctx->ifidx]);
        CB_USLEEP(UB_SEC_US);
    }
    /* Run the initial test case to initialize CBS of all queues */
    EnetCbsApp_runOneTestCase(ctx, 0, BTRUE);

    while (modCtx->enable)
    {
        char option = ' ';
        status = DebugP_scanf("%c", &option);
        switch(option)
        {
        case 's':
            EnetQoSApp_printStats(ctx);
            break;
        case 'S':
            EnetQoSApp_resetStats(ctx);
            break;
        case 't':
            EnetCbsApp_runTestCases(ctx);
            break;
        case 'l':
            EnetCbsApp_startListener(ctx);
            break;
        default:
            EnetCbsApp_showTestMenu();
            break;
        }
        TaskP_yield();
    }
    TaskP_exit();
    return NULL;
}

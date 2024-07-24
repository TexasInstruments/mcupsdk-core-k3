/*
 * avtp_testappli.c
 * test program to use l2 layer
 *
 * Copyright (C) 2016 Excelfore Corporation
 * Author: Shiro Ninomiya (shiro@excelfore.com)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "FreeRTOS.h"
#include <kernel/dpl/TaskP.h>
#include <task.h>
#include "tsn_gptp/gptpmasterclock.h"
#include "avbclient_utils.h"
#include "common.h"
#include "debug_log.h"
#include "avb_listener.h"
#include "enetapp_cpsw.h"
#include "kernel/dpl/HwiP.h"
#include "kernel/dpl/TimerP.h"
#include "kernel/dpl/SemaphoreP.h"
#include "ti_dpl_config.h"
#include "ShdMemCircularBufferP_nortos.h"

extern EnetApp_Ctx_t gAppCtx;
extern EnetApp_Cfg gEnetAppCfg;

static uint8_t gListnerStackBuf[8U * 1024U] \
__attribute__ ((aligned(32U)));

/* when we run multiple 'avtp_testclient' in threads,
 * because 'avtp_running' is a static variable, calling stop_testclient stop all of
 * them.  It is likely an intended operatin, should be okay.
 */
static bool avtp_running;

uint32_t g_Countwrite = 0U;
static bool duration_ended(uint64_t start_time, int test_duration)
{
    if (test_duration == -1) {return false;}
    if (ub_mt_gettime64() - start_time >= (uint64_t)test_duration * UB_SEC_NS){
        UB_LOG(UBL_INFO,"%s:ended\n",__func__);
        return true;
    }
    return false;
}

static int receive_data(uint8_t *payload, int payload_size,
            avbtp_rcv_cb_info_t *cbinfo, void *cbdata)
{
    avtptc_data_t *avtptcd=(avtptc_data_t *)cbdata;
    avbtp_sd_info_t *rsdinfo=&cbinfo->u.rsdinfo;
    uint32_t dataLenArr[1U];
    void *pDataArr[1U];
    uint64_t ts;
    ShdMemCircularBufferStatus shmStatus;

    // The packet size should not change per one avb session for the fix data test
    avtptcd->mpsize = payload_size;

    if(!rsdinfo->current_timestamp){
        ts=gptpmasterclock_getts64();
    }else{
        ts=rsdinfo->current_timestamp;
    }

    if(rsdinfo->seqn_diff!=1) {
        UB_LOG(UBL_INFO,"%s:seqn_diff=%d\n",__func__,rsdinfo->seqn_diff);
        if (rsdinfo->seqn_diff > 0 && avtptcd->total_rx_packets) {
            avtptcd->total_lost_packets += (rsdinfo->seqn_diff-1);
        }
    }
    avtptcd->total_rx_packets++;

    dataLenArr[0] = payload_size;
    pDataArr[0] = (void *)payload;
    shmStatus = ShdMemCircularBufferP_writeElem(gEnetAppCfg.hShmListenerQ, 1U, pDataArr, dataLenArr);
    if(shmStatus != SHDMEM_CIRCULAR_BUFFER_STATUS_OK)
    {
        if (shmStatus == SHDMEM_CIRCULAR_BUFFER_STATUS_ERR_FULL)
        {
            UB_LOG(UBL_INFO,"%s:SHM buffer full \n",__func__);
        }
        else
        {
            UB_LOG(UBL_INFO,"%s:SHM buffer error %d \n",__func__, shmStatus);
        }
    }
    else
    {
        g_Countwrite++;
    }

    if(rsdinfo->timestamp_valid && !rsdinfo->timestamp_uncertain){
        int64_t ts_diff=ts-rsdinfo->timestamp;

        // Count number of high latency values
        if (ts_diff >= ((int64_t)avtptcd->wthres_latency*UB_USEC_NS)) {
            avtptcd->high_latency_count++;
        }

        if(avtptcd->prts && avtptcd->recv_last_ts!=rsdinfo->timestamp){
            UB_CONSOLE_PRINT("system time=%"PRIu64", timestamp=%"PRIu64
                             ", ts=%"PRIu64"\n",
                             ub_rt_gettime64(), rsdinfo->timestamp, ts);
            avtptcd->recv_last_ts=rsdinfo->timestamp;
        }
        cb_rate_reporter_update_latency(&avtptcd->rate_reporter, ts_diff);
    }

    cb_rate_reporter_recv_update_bytes(&avtptcd->rate_reporter, payload_size);
    if (avtptcd->test_duration == -1){
        avtp_brater_period_print(avtptcd, false, payload_size);
    }
    cb_rate_reporter_period_reset(&avtptcd->rate_reporter);

    ub_log_flush();
    return 0;
}

static int start_listener(avtptc_data_t *avtptcd)
{
    client_connect_request_t ccr;
    uint64_t start_ts;
    avtp_running = true;

    UB_LOG(UBL_INFO,"%s:\n",__func__);
    avtptcd->avtpc=avtpc_init(avtptcd->shsuf);
    if(!avtptcd->avtpc){return -1;}
    memset(&ccr, 0, sizeof(ccr));
    set_ccr(&ccr, avtptcd);
    avtpc_set_rcv_cb(avtptcd->avtpc, receive_data, avtptcd);
    if(avtpc_connection_request(avtptcd->avtpc, &ccr)){return -1;}
    cb_rate_reporter_init(&avtptcd->rate_reporter, avtptcd->report_interval * UB_SEC_NS);
    UB_LOG(UBL_INFO,"%s:start\n",__func__);
    start_ts = ub_mt_gettime64();
    while(avtp_running && !duration_ended(start_ts, avtptcd->test_duration)){
        CB_USLEEP(10000);
    }
    UB_LOG(UBL_INFO,"%s:closing\n",__func__);
    avtp_show_final_report(avtptcd, false, avtptcd->mpsize);
    avtpc_close(avtptcd->avtpc);
    return 0;
}

static void EnetApp_ListenerTask(void *arg)
{
    avtptc_data_t avtptcd;
    char *stream_id = "00:01:02:03:04:05:00:02";
    EnetApp_Ctx_t *ctx = (EnetApp_Ctx_t *)arg;
    char *argv[]={"avtp_testclient", "-d", &ctx->netdev[0][0],
        "-m", "l", "-B", "10000", "-v", "110", "-C", "-c", "-F", "-N",
        "-S", stream_id, "-u", NULL};  /* '-u' must be the last opt 8 */

    DPRINT("avtp_testclient:talker sid=%s start", stream_id);
    SemaphoreP_pend(&gEnetAppCfg.startListnerSemObj, SystemP_WAIT_FOREVER);
    avtp_clientinit(&avtptcd, GetArgc(argv), argv);
    start_listener(&avtptcd);
}

void avbListener_createTask()
{
    TaskP_Params taskParams;
    int32_t status;

    TaskP_Params_init(&taskParams);
    taskParams.priority       = 2U;
    taskParams.stack          = gListnerStackBuf;
    taskParams.stackSize      = sizeof(gListnerStackBuf);
    taskParams.args           = (void*)&gAppCtx;
    taskParams.name           = "AVB Listener Task";
    taskParams.taskMain       = &EnetApp_ListenerTask;

    status = TaskP_construct(&gEnetAppCfg.listenerTaskObj, &taskParams);
    DebugP_assert(SystemP_SUCCESS == status);
}

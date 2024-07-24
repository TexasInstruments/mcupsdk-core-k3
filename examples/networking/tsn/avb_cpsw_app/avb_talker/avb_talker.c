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
#include "avb_talker.h"
#include "enetapp_cpsw.h"
#include "kernel/dpl/HwiP.h"
#include "kernel/dpl/TimerP.h"
#include "ti_dpl_config.h"

extern EnetApp_Ctx_t gAppCtx;
extern EnetApp_Cfg gEnetAppCfg;

static uint8_t gTalkerStackBuf[8U * 1024U] \
__attribute__ ((aligned(32U)));

static bool duration_ended(uint64_t start_time, int test_duration);

/* when we run multiple 'avtp_testclient' in threads,
 * because 'avtp_running' is a static variable, calling stop_testclient stop all of
 * them.  It is likely an intended operatin, should be okay.
 */
static bool avtp_running;

SemaphoreP_Object gTimerSem;

static void fill_test_data(uint8_t *data, size_t data_size)
{
    if(data_size < 8) {
        UB_LOG(UBL_WARN, "%s():test data buffer too small\n",__func__);
        return;
    }

    // Fill the first 8 bytes with a fixed valid mjpeg header data
    memset(data, 0, data_size);
    data[4] = 0x01; //MJPEG TYPE: 1 (1 byte)
    data[5] = 0xFF; //MJPEG Q: 255 (1 byte)
    data[6] = 0x50; //MJPEG Width: 80 (1 byte)
    data[7] = 0x3C; //MJPEG Height: 60 (1 byte)

    // fill the rest of the payload with fixed data
    for(int i=4;i<(int)(data_size/2);i++){
        data[2*i]=(i>>8)&0xff;
        data[2*i+1]=i&0xff;
    }
}

static int send_traffic(avtptc_data_t *avtptcd)
{
    client_connect_request_t ccr;
    int64_t ts;
    uint16_t packetSize;
    ShdMemCircularBufferStatus shmStatus = SHDMEM_CIRCULAR_BUFFER_STATUS_OK;

    avtp_running = true;
    fill_test_data(avtptcd->data, sizeof(avtptcd->data));
    UB_LOG(UBL_INFO,"%s:\n",__func__);
    avtptcd->avtpc=avtpc_init(avtptcd->shsuf);
    if(!avtptcd->avtpc){return -1;}
    memset(&ccr, 0, sizeof(ccr));
    set_ccr(&ccr, avtptcd);
    ccr.send_ahead_ts=avtptcd->send_ahead_ts;
    avtptcd->mpsize=avtptcd->max_frame_size - sizeof(avbtp_cm_stream_header_t);

    if(avtpc_connection_request(avtptcd->avtpc, &ccr)){return -1;}

    avtptcd->ssize=0;
    UB_LOG(UBL_INFO,"%s:start\n",__func__);
    if (avtptcd->runber>0){
        UB_LOG(UBL_INFO,"%s:Simulate error bits: %d bits/%d seconds...\n",
               __func__, avtptcd->runber, avtptcd->report_interval);
    }
    UB_LOG(UBL_INFO,"%s:Report interval: %d seconds. Please wait...\n",
           __func__, avtptcd->report_interval);

    cb_rate_reporter_init(&avtptcd->rate_reporter, avtptcd->report_interval * UB_SEC_NS);

    uint64_t start_ts = ub_mt_gettime64();
    while(avtp_running && !duration_ended(start_ts, avtptcd->test_duration)){
        SemaphoreP_pend(&gTimerSem, SystemP_WAIT_FOREVER);
        shmStatus = ShdMemCircularBufferP_readElem(gEnetAppCfg.hShmListenerQ, &packetSize, avtptcd->data);
        if(shmStatus == SHDMEM_CIRCULAR_BUFFER_STATUS_OK)
        {
            ts=gptpmasterclock_getts64()+avtptcd->tsoffset*UB_USEC_NS;
            avtpc_write_sd_packet(avtptcd->avtpc, (int)packetSize, avtptcd->data, ts);
        }
    }
    avtptcd->rate_reporter.last_ts=ub_mt_gettime64();

    avtp_show_final_report(avtptcd, true, avtptcd->mpsize);
    UB_LOG(UBL_INFO,"%s:closing\n",__func__);
    CB_USLEEP(10000);
    avtpc_close(avtptcd->avtpc);
    return 0;
}

static bool duration_ended(uint64_t start_time, int test_duration)
{
    if (test_duration == -1) {return false;}
    if (ub_mt_gettime64() - start_time >= (uint64_t)test_duration * UB_SEC_NS){
        UB_LOG(UBL_INFO,"%s:ended\n",__func__);
        return true;
    }
    return false;
}

static void EnetApp_talkerTask(void *arg)
{
    avtptc_data_t avtptcd;
    char *stream_id = "00:01:02:03:04:05:00:02";
    EnetApp_Ctx_t *ctx = (EnetApp_Ctx_t *)arg;
    char *argv[]={"avtp_testclient", "-d", &ctx->netdev[0][0],
        "-m", "t", "-B", "1000", "-v", "110", "-C", "-c",
        "-S", stream_id, "-b", "5", "-u", NULL}; /* '-u' must be the last opt */

    DPRINT("avtp_testclient:talker sid=%s start", stream_id);
    SemaphoreP_pend(&gEnetAppCfg.startTalkerSemObj, SystemP_WAIT_FOREVER);
    avtp_clientinit(&avtptcd, GetArgc(argv), argv);
    send_traffic(&avtptcd);
}

void avbTalker_createTask()
{
    TaskP_Params taskParams;
    int32_t status;

    TaskP_Params_init(&taskParams);
    taskParams.priority       = 2U;
    taskParams.stack          = gTalkerStackBuf;
    taskParams.stackSize      = sizeof(gTalkerStackBuf);
    taskParams.args           = (void*)&gAppCtx;
    taskParams.name           = "AVB Talker Task";
    taskParams.taskMain       = &EnetApp_talkerTask;

    status = TaskP_construct(&gEnetAppCfg.talkerTaskObj, &taskParams);
    DebugP_assert(SystemP_SUCCESS == status);
    status = SemaphoreP_constructBinary(&gTimerSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER0]);
}

void avbTimerIsr(void)
{
    SemaphoreP_post(&gTimerSem);
}

/******************************************************************************
 * Copyright (c) 2024 Texas Instruments Incorporated
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
 *
 *****************************************************************************/

/** \file ddr_perf.c
 *
 *   \brief This file contains DDR performance APIs.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "ddr_perf.h"
#include <string.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/HwiP.h>
#include <drivers/ddr/v0/csl_emif.h>
#include <drivers/ddr/v1/csl_emif.h>
#include <drivers/hw_include/cslr_soc.h>

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

#define DDR_STATS_CTR0_VAL         (0x00) /* A value of 0x00 configures counter 0 to return number of write transactions  */
#define DDR_STATS_CTR1_VAL         (0x01) /* A value of 0x01 configures counter 1 to return number of read transactions   */
/* Use counter 2 and 3 to provide stats other than read/write transactions */
#define DDR_STATS_CTR2_VAL         (0x03) /* A value of 0x03 configures counter 3 to return number of command activations */
#define DDR_STATS_CTR3_VAL         (0x1C) /* A value of 0x1C configures counter 4 to return number of queue full states   */

#define DDR_SSCFG_PERF_CNTSEL_REG                                   CSL_EMIF_SSCFG_PERF_CNT_SEL_REG
#define DDR_SSCFG_PERF_CNT1_REG                                     CSL_EMIF_SSCFG_PERF_CNT1_REG
#define DDR_SSCFG_PERF_CNT2_REG                                     CSL_EMIF_SSCFG_PERF_CNT2_REG
#define DDR_SSCFG_PERF_CNT3_REG                                     CSL_EMIF_SSCFG_PERF_CNT3_REG
#define DDR_SSCFG_PERF_CNT4_REG                                     CSL_EMIF_SSCFG_PERF_CNT4_REG
#define DDR_NUM_INSTANCES      (1U)

/* Specify the duration for with counter2 and counter3 values are to be accumulated before printing */
#define DDR_SNAPSHOT_WINDOW_WIDTH (500000 * 4) /* Configured for 2 seconds */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void DDR_statsReadCounters(uint32_t *val0, uint32_t *val1, uint32_t *val2, uint32_t *val3, uint32_t raw);

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

static DDR_StatsDdrLoad gDdrStatsLoadObj;


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void DDR_copyDdrPerfStats(DDR_StatsDdrLoad *ddrLoadObj)
{
    uint32_t cookie;
    cookie = HwiP_disable();
    memcpy(ddrLoadObj,&gDdrStatsLoadObj,sizeof(DDR_StatsDdrLoad));
    HwiP_restore(cookie);
}

void DDR_statsResetDdrLoadCalcAll(void)
{
    DDR_StatsDdrLoad *ddrLoad = &gDdrStatsLoadObj;
    uint32_t cookie;

    cookie = HwiP_disable();

    ddrLoad->ddrStats.readBwAverage = 0;
    ddrLoad->ddrStats.writeBwAverage = 0;
    ddrLoad->ddrStats.readBwPeak = 0;
    ddrLoad->ddrStats.writeBwPeak = 0;
    ddrLoad->ddrStats.totalAvailableBw = DDR_MHZ*DDR_BUS_WIDTH*DDR_NUM_INSTANCES*2/8;
    ddrLoad->totalTime = 0;
    ddrLoad->totalRead = 0;
    ddrLoad->totalWrite = 0;
    ddrLoad->lastTimestamp = ClockP_getTimeUsec();
    ddrLoad->snapshotCount = DDR_SNAPSHOT_WINDOW_WIDTH;
    ddrLoad->ddrStats.counter0Total = 0;
    ddrLoad->ddrStats.counter1Total = 0;
    ddrLoad->ddrStats.counter2Total = 0;
    ddrLoad->ddrStats.counter3Total = 0;
    HwiP_restore(cookie);
}

/* read EMIF counter and calculate read and write bytes since last read */
static void DDR_statsReadCounters(uint32_t *val0, uint32_t *val1, uint32_t *val2, uint32_t *val3, uint32_t raw)
{
    static uint32_t isFirstTime = 1;
    static volatile uint32_t *cntSel[DDR_NUM_INSTANCES];
    static volatile uint32_t *cnt0[DDR_NUM_INSTANCES];
    static volatile uint32_t *cnt1[DDR_NUM_INSTANCES];
    static volatile uint32_t *cnt2[DDR_NUM_INSTANCES];
    static volatile uint32_t *cnt3[DDR_NUM_INSTANCES];

    static volatile uint32_t lastCnt0 = 0, lastCnt1 = 0, lastCnt2 = 0, lastCnt3 = 0;
    volatile uint32_t curCnt0 = 0, curCnt1 = 0, curCnt2 = 0, curCnt3 = 0;
    uint32_t diffCnt0, diffCnt1, diffCnt2, diffCnt3, ddrInst;

    cntSel[0] = (volatile uint32_t *)(DDR_SS_CFG_BASE + DDR_SSCFG_PERF_CNTSEL_REG);
    cnt0[0]   = (volatile uint32_t *)(DDR_SS_CFG_BASE + DDR_SSCFG_PERF_CNT1_REG);
    cnt1[0]   = (volatile uint32_t *)(DDR_SS_CFG_BASE + DDR_SSCFG_PERF_CNT2_REG);
    cnt2[0]   = (volatile uint32_t *)(DDR_SS_CFG_BASE + DDR_SSCFG_PERF_CNT3_REG);
    cnt3[0]   = (volatile uint32_t *)(DDR_SS_CFG_BASE + DDR_SSCFG_PERF_CNT4_REG);

    if(isFirstTime)
    {
        isFirstTime = 0;

        for (ddrInst = 0; ddrInst < DDR_NUM_INSTANCES; ddrInst++)
        {
            /* cnt0 is counting reads, cnt1 is counting writes, cnt2, cnt3 not used */
            *cntSel[ddrInst] = (DDR_STATS_CTR0_VAL <<  0U) |
                       (DDR_STATS_CTR1_VAL <<  8U) |
                       (DDR_STATS_CTR2_VAL << 16U) |
                       (DDR_STATS_CTR3_VAL << 24U);

            lastCnt0 += *cnt0[ddrInst];
            lastCnt1 += *cnt1[ddrInst];
            lastCnt2 += *cnt2[ddrInst];
            lastCnt3 += *cnt3[ddrInst];
        }
    }

    for (ddrInst = 0; ddrInst < DDR_NUM_INSTANCES; ddrInst++)
    {
        curCnt0 += *cnt0[ddrInst];
        curCnt1 += *cnt1[ddrInst];
        curCnt2 += *cnt2[ddrInst];
        curCnt3 += *cnt3[ddrInst];
    }

    if(raw)
    {
        *val0 = (uint32_t)curCnt0;
        *val1 = (uint32_t)curCnt1;
        *val2 = (uint32_t)curCnt2;
        *val3 = (uint32_t)curCnt3;
        return;
    }

    if(curCnt0 < lastCnt0)
    {
        /* wrap around case */
        diffCnt0 = (0xFFFFFFFFU - lastCnt0) + curCnt0;
    }
    else
    {
        diffCnt0 = curCnt0 - lastCnt0;
    }

    if(curCnt1 < lastCnt1)
    {
        /* wrap around case */
        diffCnt1 = (0xFFFFFFFFU - lastCnt1) + curCnt1;
    }
    else
    {
        diffCnt1 = curCnt1 - lastCnt1;
    }

    if(curCnt2 < lastCnt2)
    {
        /* wrap around case */
        diffCnt2 = (0xFFFFFFFFU - lastCnt2) + curCnt2;
    }
    else
    {
        diffCnt2 = curCnt2 - lastCnt2;
    }

    if(curCnt3 < lastCnt3)
    {
        /* wrap around case */
        diffCnt3 = (0xFFFFFFFFU - lastCnt3) + curCnt3;
    }
    else
    {
        diffCnt3 = curCnt3 - lastCnt3;
    }

    lastCnt0 = curCnt0;
    lastCnt1 = curCnt1;
    lastCnt2 = curCnt2;
    lastCnt3 = curCnt3;

    *val0 = (uint32_t)diffCnt0;
    *val1 = (uint32_t)diffCnt1;
    *val2 = (uint32_t)diffCnt2;
    *val3 = (uint32_t)diffCnt3;
}

void DDR_perfStatsAccumulate(void)
{
    DDR_StatsDdrLoad *ddrLoad = &gDdrStatsLoadObj;
    uint32_t cookie;
    uint32_t val0 = 0, val1 = 0, val2 = 0, val3 = 0;
    uint64_t curTime;
    uint32_t elapsedTime;
    uint64_t writeBytes,readBytes;
    uint32_t readBwPeak,writeBwPeak;

    cookie = HwiP_disable();

    curTime = ClockP_getTimeUsec();

    if(curTime > ddrLoad->lastTimestamp)
    {
        elapsedTime = curTime - ddrLoad->lastTimestamp;
        if(elapsedTime==0)
        {
            elapsedTime = 1; /* to avoid divide by 0 */
        }
        ddrLoad->totalTime += elapsedTime;

        DDR_statsReadCounters(&val0, &val1, &val2, &val3, 0);

        writeBytes = val0 * DDR_BURST_SIZE_BYTES;
        readBytes  = val1 * DDR_BURST_SIZE_BYTES;

        ddrLoad->totalRead += readBytes;
        ddrLoad->totalWrite += writeBytes;
        ddrLoad->ddrStats.readBwAverage = (ddrLoad->totalRead/ddrLoad->totalTime); /* in MB/s */
        ddrLoad->ddrStats.writeBwAverage = (ddrLoad->totalWrite/ddrLoad->totalTime); /* in MB/s */

        readBwPeak = readBytes/elapsedTime; /* in MB/s */
        writeBwPeak = writeBytes/elapsedTime; /* in MB/s */
        if(readBwPeak > ddrLoad->ddrStats.readBwPeak)
        {
            ddrLoad->ddrStats.readBwPeak = readBwPeak;
        }
        if(writeBwPeak > ddrLoad->ddrStats.writeBwPeak)
        {
            ddrLoad->ddrStats.writeBwPeak = writeBwPeak;
        }

        ddrLoad->ddrStats.counter0Total += val2;
        ddrLoad->ddrStats.counter1Total += val3;
        ddrLoad->snapshotCount -= elapsedTime;

        if(ddrLoad->snapshotCount <= 0)
        {
            ddrLoad->ddrStats.counter0Total = 0;
            ddrLoad->ddrStats.counter1Total = 0;

            ddrLoad->snapshotCount = DDR_SNAPSHOT_WINDOW_WIDTH;
        }
    }

    ddrLoad->lastTimestamp = curTime;
    HwiP_restore(cookie);
}
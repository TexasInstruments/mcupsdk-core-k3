/*
 *  Copyright (C) 2021-2025 Texas Instruments Incorporated
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

/**
 *  \file hyperRam_xip_benchmark.c
 *
 *  \brief File containing BENCHMARK_FIR and BENCHMARK_MEMCPY.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/ipc_notify/v0/ipc_notify_v0.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* define below to '0' run the CPUs asynchronously,
 * when defined all the CPUs will run the benchmark at the same time
 * thus causing maximum simultaneous access to the flash in XIP mode
 */
#define ENABLE_CPU_SYNC (0U)

/* number of iterations to run the benchmark */
#define NUM_ITERATIONS   (10U)

/* benchmark ID's */
#define BENCHMARK_NONE     (0U)
#define BENCHMARK_FIR      (1U)
#define BENCHMARK_MEMCPY   (2U)
#define BENCHMARK_MAX      (3U)


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* application control structure, mainly holds benchmark statistics */
typedef struct {

    uint32_t maxCycles;
    uint32_t minCycles;
    uint64_t totalCycles;
    uint32_t iterationCount;

} App_Ctrl;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

const char *gBenchmarkName[BENCHMARK_MAX] = {
    "NONE",
    "FIR",
    "MEMCPY",
};

App_Ctrl gAppCtrl;

/* shared memory variable which is used to sync all CPUs with r5fss0-0 to start at the same time
 * when ENABLE_CPU_SYNC is 1
 */
volatile uint32_t gAppSyncStart __attribute__((aligned(128), section(".bss.user_shared_mem"))) = BENCHMARK_NONE;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void hyperRam_xip_benchmark_app_resetStats()
{
    gAppCtrl.totalCycles = 0;
    gAppCtrl.maxCycles = 0;
    gAppCtrl.minCycles = (uint32_t)-1;
    gAppCtrl.iterationCount = 0;
}

void hyperRam_xip_benchmark_app_updateStats(uint32_t cycles)
{
    if(cycles>gAppCtrl.maxCycles)
    {
        gAppCtrl.maxCycles = cycles;
    }

    if(cycles<gAppCtrl.minCycles)
    {
        gAppCtrl.minCycles = cycles;
    }

    gAppCtrl.totalCycles += cycles;
    gAppCtrl.iterationCount++;
}

void hyperRam_xip_benchmark_app_printStats(const char *tag)
{
    uint32_t avg = gAppCtrl.totalCycles/gAppCtrl.iterationCount;

    DebugP_log("%s: \r\n %6d cycles (code/data fully cached) ,\r\n %6d cycles (code/data not cached) ,\r\n %6d cycles (code/data not-cached 1 of %d iterations)\r\n",
        tag,
        gAppCtrl.minCycles,
        gAppCtrl.maxCycles,
        avg,
        gAppCtrl.iterationCount
        );
}

void hyperRam_xip_benchmark_app_syncCpus(uint32_t syncCpus, uint32_t benchmarkId)
{
    if(IpcNotify_getSelfCoreId() == CSL_CORE_ID_R5FSS0_0)
    {
        /* wait for prints from other cores to get printed and for the other CPUs to hit the sync while loop */
        ClockP_usleep(500*1000);

        if(syncCpus)
        {
            DebugP_log("Sync-ing CPUs\r\n\r\n");

            gAppSyncStart = benchmarkId;
            __asm__ __volatile__  ("  dsb"   "\n\t": : : "memory" );
        }
    }
    else
    {
        if(syncCpus)
        {
            while(gAppSyncStart!=benchmarkId)
                ;
        }
    }
}

void hyperRam_xip_benchmark_app_runBenchmark(uint32_t benchmarkId)
{
    uint32_t hyperRam_xip_firBench();
    uint32_t hyperRam_xip_memcpyBench();

    uint32_t cycles;
    uint32_t i;

    /* reset stats counters */
    hyperRam_xip_benchmark_app_resetStats();
    /* sync with all CPUs */
    hyperRam_xip_benchmark_app_syncCpus(ENABLE_CPU_SYNC, benchmarkId);

    for(i = 0U; i < NUM_ITERATIONS; i++)
    {
        if(benchmarkId == BENCHMARK_FIR)
        {
            cycles = hyperRam_xip_firBench();
        }

        if(benchmarkId==BENCHMARK_MEMCPY)
        {
            cycles = hyperRam_xip_memcpyBench();
        }

        hyperRam_xip_benchmark_app_updateStats(cycles);
    }

    /* print the stats, we print for one core only, all other cores will exit their task and do "wfi" */
    hyperRam_xip_benchmark_app_printStats(gBenchmarkName[benchmarkId]);
}

void hyperRam_xip_benchmark_main(void *args)
{

    DebugP_log("### HYPERRAM XIP benchmark ###\r\n");

    /* run the benchmark and print results */
    hyperRam_xip_benchmark_app_runBenchmark(BENCHMARK_FIR);
    hyperRam_xip_benchmark_app_runBenchmark(BENCHMARK_MEMCPY);

    DebugP_log("All tests have passed!!\r\n");

}

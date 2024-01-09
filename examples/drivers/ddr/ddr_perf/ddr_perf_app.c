/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

 /** \file ddr_perf_app.c
 *
 *   \brief This file contains example for testing DDR performance.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/ddr/ddr_perf.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

#define DDR_PERF_APP_DATA_SIZE                (256U) /* has to be 256 B aligned */
#define DDR_PERF_APP_1KB_SIZE                 (256*4U)
#define DDR_PERF_APP_2KB_SIZE                 (DDR_PERF_APP_1KB_SIZE*2U)
#define DDR_PERF_APP_4KB_SIZE                 (DDR_PERF_APP_1KB_SIZE*4U)
#define DDR_PERF_APP_1MB_SIZE                 (DDR_PERF_APP_1KB_SIZE*DDR_PERF_APP_1KB_SIZE)
#define DDR_PERF_APP_5MB_SIZE                 (DDR_PERF_APP_1MB_SIZE*5U)
#define DDR_PERF_APP_10MB_SIZE                (DDR_PERF_APP_1MB_SIZE*10U)
#define DDR_PERF_APP_MAX_TEST_SIZE            (DDR_PERF_APP_10MB_SIZE)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void DdrPerfApp_performanceStatusPrint(void);

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

uint8_t gDdrTestTxBuf[DDR_PERF_APP_DATA_SIZE] = {0};
uint8_t gDdrTestTxBulkBuf[DDR_PERF_APP_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
uint8_t gDdrTestRxBuf[DDR_PERF_APP_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
static DDR_StatsDdrLoad gDdrStatsDdrLoadObj;
static volatile uint64_t gIdleCounter = 0;
static volatile uint8_t gFirstTimeRun = 1;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void DdrPerfApp_performanceStatusPrint(void)
{
    DDR_copyDdrPerfStats(&gDdrStatsDdrLoadObj);
    DebugP_log("DDR performance statistics\r\n");
    DebugP_log("==========================\r\n");

    DebugP_log("DDR: READ  BW: AVG = %6d MiB/s\r\n",
        gDdrStatsDdrLoadObj.ddrStats.readBwAverage);
    DebugP_log("DDR: WRITE BW: AVG = %6d MiB/s\r\n",
        gDdrStatsDdrLoadObj.ddrStats.writeBwAverage);
    DebugP_log("DDR: TOTAL BW: AVG = %6d MiB/s\r\n",
        gDdrStatsDdrLoadObj.ddrStats.readBwAverage + gDdrStatsDdrLoadObj.ddrStats.writeBwAverage);
}

void ddr_perf_app_main(void *args)
{
    for(uint16_t testBufIndex = 0; testBufIndex < DDR_PERF_APP_DATA_SIZE; testBufIndex++)
    {
        gDdrTestTxBuf[testBufIndex] = (uint8_t)testBufIndex;
    }
    /* The contents of buffer "gDdrTestTxBuf" are copied at incremental offsets of 'DDR_PERF_APP_DATA_SIZE'
     * until gDdrTestTxBulkBuf buffer is full
     */
    for(uint32_t txChunkCnt = 0; txChunkCnt < DDR_PERF_APP_MAX_TEST_SIZE/DDR_PERF_APP_DATA_SIZE; txChunkCnt++)
    {
        memcpy(gDdrTestTxBulkBuf + txChunkCnt*sizeof(gDdrTestTxBuf) , gDdrTestTxBuf , sizeof(gDdrTestTxBuf));
    }

    DDR_statsResetDdrLoadCalcAll();
    DDR_perfStatsAccumulate();

    memcpy(gDdrTestRxBuf,gDdrTestTxBulkBuf,DDR_PERF_APP_10MB_SIZE);

    DDR_perfStatsAccumulate();
    DdrPerfApp_performanceStatusPrint();
}

/* This function is called when configUSE_IDLE_HOOK is 1 in FreeRTOSConfig.h */
void vApplicationIdleHook( void )
{
#if (configLOAD_UPDATE_IN_IDLE==1)
    void vApplicationLoadHook();

    vApplicationLoadHook();
#endif
  if(gFirstTimeRun){
    DDR_statsResetDdrLoadCalcAll();
    gFirstTimeRun=0;
  }

   DDR_perfStatsAccumulate();
   gIdleCounter++;

   __asm__ __volatile__ ("wfi"   "\n\t": : : "memory");

}
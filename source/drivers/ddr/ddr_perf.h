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

/** \file ddr_perf.h
 *
 *   \brief This file contains DDR performance APIs.
 */

#ifndef DDR_PERF_DRIVER_H_
#define DDR_PERF_DRIVER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drivers/hw_include/soc_config.h>

#if defined (DRV_VERSION_DDR_V0)
#include <drivers/ddr/v0/soc/ddr_soc.h>
#endif

#if defined (DRV_VERSION_DDR_V1)
#include <drivers/ddr/v1/soc/ddr_soc.h>
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Data structure for DDR perf stats
 *
 */
typedef struct {
    /**< avg bytes read per second, in units of MB/s */
    uint32_t readBwAverage;
    /**< avg bytes written per second, in units of in MB/s */
    uint32_t writeBwAverage;
    /**< peak bytes read in a sampling period, in units of MB/s */
    uint32_t readBwPeak;
    /**< peak bytes read in a sampling period, in units of MB/s */
    uint32_t writeBwPeak;
    /**< theoritical bw available to system, in units of MB/s */
    uint32_t totalAvailableBw;
    /**< sum total of counter0 values aggregated over time as defined by DDR_SNAPSHOT_WINDOW_WIDTH */
    uint32_t counter0Total;
    /**< sum total of counter1 values aggregated over time as defined by DDR_SNAPSHOT_WINDOW_WIDTH */
    uint32_t counter1Total;
    /**< sum total of counter2 values aggregated over time as defined by DDR_SNAPSHOT_WINDOW_WIDTH */
    uint32_t counter2Total;
    /**< sum total of counter3 values aggregated over time as defined by DDR_SNAPSHOT_WINDOW_WIDTH */
    uint32_t counter3Total;
} DDR_PerfStats;

/**
 *  \brief Data structure for accumulated DDR perf stats
 *
 */
typedef struct {
    /**< Structure object to update DDR perf stats */
    DDR_PerfStats ddrStats;
    /**< Total time counter*/
    uint64_t totalTime;
    /**< Previous timestamp when DDR perf counters were updated*/
    uint64_t lastTimestamp;
    /**< Total read bytes for calculating bandwidth*/
    uint64_t totalRead;
    /**< Total write bytes for calculating bandwidth*/
    uint64_t totalWrite;
    /**< variable for tracking snapshot count*/
    int32_t snapshotCount;

} DDR_StatsDdrLoad;

/* ========================================================================== */
/*                       Function Declarations                                */
/* ========================================================================== */

 /**
 *  \brief  Function to copy DDR perf stats into paramenter given by the application
 *
 *  \param  ddrLoadObj      Pointer to DDR perf stats
 */
void DDR_copyDdrPerfStats(DDR_StatsDdrLoad *ddrLoadObj);

 /**
 *  \brief  Function to reset DDR perf stats global structure variable
 *
 *  \param None
 *
 *  \return None
 */
void DDR_statsResetDdrLoadCalcAll(void);

 /**
 *  \brief  Function to accumulate DDR perf stats
 *
 *  \param None
 *
 *  \return None
 */
void DDR_perfStatsAccumulate(void);


#ifdef __cplusplus
}
#endif

#endif  /* #ifndef DDR_PERF_DRIVER_H_ */
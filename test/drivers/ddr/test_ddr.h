/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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

/** \file test_ddr.h
 *
 *  \brief This file contains DDR test case declarations and macros.
 */

#ifndef TEST_DDR_H_
#define TEST_DDR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

void *test_ddr_main(void *args);

#if !defined(MCU_R5)
void TestDdr_initWithValidParams(void *arg);
void TestDdr_initVerifyMemoryAccessPostInit(void *arg);
void TestDdr_initSequentialWriteReadFullRange(void *arg);
void TestDdr_reinitAfterAlreadyInitialized(void *arg);
#endif

void TestDdr_boundaryAccessTest(void *arg);
void TestDdr_alternatingPatternTest(void *arg);
void TestDdr_walking1sPattern(void *arg);
void TestDdr_walking0sPattern(void *arg);
void TestDdr_allOnesAllZerosPattern(void *arg);
void TestDdr_addressBusTest(void *arg);
void TestDdr_checkerboardPattern(void *arg);
void TestDdr_randomDataPattern(void *arg);
void TestDdr_byteAccessGranularity(void *arg);

#if !defined(MCU_R5)
void TestDdr_inlineEccEnableSingleRegion(void *arg);
void TestDdr_inlineEccEnableMultipleRegions(void *arg);
void TestDdr_inlineEccRegion1OnlyPriming(void *arg);
void TestDdr_inlineEccRegion2OnlyPriming(void *arg);
void TestDdr_largeMemoryPriming(void *arg);
void TestDdr_smallMemoryPriming(void *arg);
#endif
void TestDdr_inlineEccMemoryPrimingBist(void *arg);
void TestDdr_memoryPriming(void *arg);

void TestDdr_inlineEccReEnable(void *arg);

void TestDdr_inlineEccDisable(void *arg);
void TestDdr_eccSingleBitErrorDetection(void *arg);
void TestDdr_eccDoubleBitErrorDetection(void *arg);
void TestDdr_eccSingleBitErrorCorrection(void *arg);
void TestDdr_eccErrorInfoRetrieval(void *arg);
void TestDdr_clearSingleBitEccError(void *arg);
void TestDdr_clearDoubleBitEccError(void *arg);
void TestDdr_clearAllEccErrors(void *arg);
void TestDdr_eccErrorThresholdInterrupt(void *arg);
void TestDdr_eccInterruptStatusClear(void *arg);

void TestDdr_eccInterruptEnableDisable(void *arg);

/* Frequency tests */
#if !defined(MCU_R5)
#if !defined(SOC_AM62PX)
void TestDdr_frequencySetAtInit(void *arg);
#endif
void TestDdr_lpddr4FrequencyHandshake(void *arg);
#endif

/* Performance counter tests */
#if !defined(MCU_R5)
void TestDdr_perfCountersReadWriteBandwidth(void *arg);
void TestDdr_perfStatsReset(void *arg);
void TestDdr_perfPeakBandwidthTracking(void *arg);
void TestDdr_perfCounterAccumulation(void *arg);
void TestDdr_perfSnapshotWindowExpiry(void *arg);
void TestDdr_perfWindowCountDown(void *arg);
void TestDdr_perfWindowExpirationAndReset(void *arg);
void TestDdr_readAccumulation(void *arg);
void TestDdr_writeAccumulation(void *arg);
void TestDdr_timeAccumulation(void *arg);
void TestDdr_counterTotals(void *arg);
void TestDdr_counterTotalsQueueFull(void *arg);
void TestDdr_readBandwidth(void *arg);
void TestDdr_writeBandwidth(void *arg);
void TestDdr_avgBandwidth(void *arg);
void TestDdr_peakBwTracking(void *arg);
void TestDdr_zeroTraffic(void *arg);
void TestDdr_divideByZeroProtection(void *arg);
void TestDdr_deltaModeCounterReading(void *arg);
void TestDdr_rawModeCounterReading(void *arg);
void TestDdr_counterWrapAround(void *arg);
void TestDdr_noWrapAroundDelta(void *arg);
void TestDdr_multipleCounterSimultaneous(void *arg);
#endif

/* EMIF subsystem and configuration tests */
void TestDdr_emifSubsystemRevisionRead(void *arg);

#if !defined(MCU_R5)
void TestDdr_sdramIndexConfiguration(void *arg);
#endif

/* Stress and concurrent access tests */
void TestDdr_sustainedWriteReadStress(void *arg);
void TestDdr_eccUnderSustainedTraffic(void *arg);

/* Boundary and region access tests */
void TestDdr_accessAtStartAddress(void *arg);
void TestDdr_accessAtEndAddress(void *arg);

/* Init-done polling tests */
#if !defined(MCU_R5)
void TestDdr_initDonePollingWithEcc(void *arg);
void TestDdr_initDoneWithoutEcc(void *arg);
#endif

void TestDdr_getEccErrorInfoWithNullPtr(void *arg);

/* CSL EMIF NULL-pointer tests */
#if !defined(MCU_R5)
void TestDdr_cslEmifNullRegs(void *arg);
#endif

/* Multi-threaded tests */
#ifdef ENABLE_MT_TESTS
void TestDdr_mtConcurrentReadFromMultipleTasks(void *arg);
void TestDdr_mtConcurrentWriteFromMultipleTasks(void *arg);
void TestDdr_mtConcurrentReadWriteSameRegion(void *arg);
void TestDdr_mtConcurrentReadWriteDifferentRegions(void *arg);
void TestDdr_mtConcurrentEccEnableDisable(void *arg);
#endif

#if !defined(MCU_R5)
void TestDdr_initNullParam(void *arg);
void TestDdr_inlineEccAllRegionsUnused(void *arg);
#endif

void TestDdr_cslEmifConfigEccDisabled(void *arg);
void TestDdr_cslEmifClearEccErrorDefaultCase(void *arg);

#ifdef __cplusplus
}
#endif

#endif /* TEST_DDR_H_ */
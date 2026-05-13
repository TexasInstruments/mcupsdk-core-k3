/*
 *  Copyright (C) 2025-2026 Texas Instruments Incorporated
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

#ifndef __TEST_OPTIFLASH__H__
#define __TEST_OPTIFLASH__H__

#define TRANSFERSIZE (4*1024)

extern uint8_t __attribute__((aligned(4*1024), section(".data.flashSrcBuffer"))) sourceBuffer[TRANSFERSIZE];
extern uint8_t __attribute__((aligned(4*1024), section(".data.flashDestBuffer"))) destBuffer[TRANSFERSIZE];

void *test_flc_configuration(void*);
void *test_flc_runtimeconfig(void*);
void *test_flc_interrupt(void*);
void *test_flc_enable_disable(void*);
void *test_rl2_config(void *);
void *test_rat_config(void *);
void *TestOptiflash_configAllFlcRegions(void*);
void *TestOptiflash_validateFlcDataIntegrity(void*);
void *TestOptiflash_concurrentFlcRegionCopy(void*);
void *TestOptiflash_flcReadErrorDetection(void*);
void *TestOptiflash_flcWriteErrorDetection(void *args);
void *TestOptiflash_disableFlcRegion(void*);
void *TestOptiflash_flcReadIRQMaskValidation(void*);
void *TestOptiflash_flcReadIRQStatusValidation(void*);
void *TestOptiflash_configureRL2Cache(void*);
void *TestOptiflash_rL2CacheSizeSelection(void*);
void *TestOptiflash_rl2SafeReconfigureBehavior(void*);
void *TestOptiflash_integrationFlcWithRl2CacheCoherency(void*);
void *TestOptiflash_flcStartWhileBusy(void*);
void *TestOptiflash_flcZeroLengthTransfer(void*);
void *TestOptiflash_flcBackToBackTransfers(void*);
void *TestOptiflash_rl2DisableDuringActiveAccess(void *args);
void *TestOptiflash_flcNullPointerHandling(void *args);
void *TestOptiflash_flcIllegalRegionId(void *args);
void *TestOptiflash_rl2NullPointerHandling(void *args);
void *TestOptiflash_rl2UnknownCacheSize(void *args);
void *TestOptiflash_rl2UnknownInterruptType(void *args);
void *TestOptiflash_flcMisalignedAddress(void *args);
void *TestOptiflash_flcUnknownInterruptType(void *args);
void *TestOptiflash_flcCpuCacheCoherencyAfterTransfer(void *args);
void *TestOptiflash_flcOverlappingRegions(void *args);
void *TestOptiflash_EnableRL2Cache(void *args);
void *TestOptiflash_DisableRL2Cache(void *args);
void *TestOptiflash_flcThroughputComparison(void *args);
void *TestOptiflash_rl2RemoteLengthEncoding(void *args);
void *TestOptiflash_rl2SetInterruptWriteHitAndWriteError(void *args);
void *TestOptiflash_rl2ClearInterruptWriteHitAndWriteError(void *args);
void *TestOptiflash_rl2ReadIRQStatusRaw(void *args);
void *TestOptiflash_rl2IRQMaskApiValidation(void *args);
void *TestOptiflash_rL2CacheMissBehavior(void *args);
void *TestOptiflash_rL2CacheHitBehavior(void *args);
void *TestOptiflash_RL2WriteHitInterrupt(void *args);
void *TestOptiflash_RL2WriteErrorInterrupt(void *args);
void *TestOptiflash_rl2IRQMaskValidationFunc(void *args);
void *TestOptiflash_rl2ReadIRQStatusValidation(void *args);
void *TestOptiflash_rl2CacheLineReplacementPolicy(void *args);
void *TestOptiflash_rl2ReenableAfterDisable(void *args);
void *TestOptiflash_flcTransferAbortMidOperation(void *args);
void *TestOptiflash_flcDacModeRobustness(void *args);
void *TestOptiflash_flcInvalidBaseAddress(void *args);
#if defined ENABLE_MT_TESTS
void *TestOptiflash_multithreadFlcIndependentRegions(void *args);
void *TestOptiflash_multithreadFlcSameRegionAccess(void *args);
void *TestOptiflash_multithreadFlcInterruptHandling(void *args);
void *TestOptiflash_multithreadRl2ConcurrentAccess(void *args);
void *TestOptiflash_multithreadRl2InterruptAndFlcTransfer(void *args);
#endif

#endif

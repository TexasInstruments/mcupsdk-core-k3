/*
 * Copyright (C) 2025-26 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "memory_latency_benchmark.h"

#define NUMBER_OF_INSTRUCTIONS      (32U)
#define APP_32BITS_SIZE             (4U) /* 32 bits size in bytes*/
#define APP_64BITS_SIZE             (8U) /* 64 bits size in bytes*/
#define APP_SECONDS_IN_NANO_SECONDS (1000*1000*1000)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

benchmark_t latencyCalculate_Read32(uint32_t address)
{
    double startCount = 0, stopCount = 0;
    benchmark_t perf;
    volatile uint32_t *writePtrAddr = (uint32_t *)address;

    /* Suppress unused variable warning - variable is used in inline assembly */
    (void)writePtrAddr;

#if defined (R5F_CORE)
    startCount = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
#elif defined (C7_CORE)
    startCount = CycleCounterP_getCount32();
#endif

    /* Read 32 bytes of data */
#if defined (R5F_CORE)
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldr r7, %[value]": : [value] "m" (*writePtrAddr) : "r7");
#elif defined (C7_CORE)
    /* Call the C7x assembly function for 32-bit reads */
    c7x_Read32((uint32_t)writePtrAddr);
#endif

#if defined (R5F_CORE)
    stopCount = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
#elif defined (C7_CORE)
    stopCount = CycleCounterP_getCount32();
#endif

    perf.cycles = (stopCount - startCount)/(NUMBER_OF_INSTRUCTIONS * APP_32BITS_SIZE);

    return perf;
}

benchmark_t latencyCalculate_Read64(uint32_t address)
{
    double startCount = 0, stopCount = 0;
    benchmark_t perf;
    volatile uint64_t *writePtrAddr = (uint64_t *)address;

    /* Suppress unused variable warning - variable is used in inline assembly */
    (void)writePtrAddr;

#if defined (R5F_CORE)
    startCount = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
#elif defined (C7_CORE)
    startCount = CycleCounterP_getCount32();
#endif

    /* Read 64 bytes of data */
#if defined (R5F_CORE)
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
    __asm__ __volatile__( "ldrd r7, r8, %[value]": : [value] "m" (*writePtrAddr) : "r7");
#elif defined (C7_CORE)
    /* Call the C7x assembly function for 64-bit reads */
    c7x_Read64((uint32_t)writePtrAddr);
#endif

#if defined (R5F_CORE)
    stopCount = PmuP_ReadCounter(PmuP_PMU_CYCLE_COUNTER_NUM);
#elif defined (C7_CORE)
    stopCount = CycleCounterP_getCount32();
#endif

    perf.cycles = (stopCount - startCount)/(NUMBER_OF_INSTRUCTIONS * APP_64BITS_SIZE);

    return perf;
}

/*
 * This is a latency project provided to calculate the latency of
 * read access.
 */
void memory_latency_benchmark_main(void *args)
{
    benchmark_t perf;
#if defined (R5F_CORE)
    DebugP_log("BENCHMARK START - ARM R5F - Memory Access latency\r\n\n");
#elif defined (C7_CORE)
    DebugP_log("BENCHMARK START - C7x - Memory Access latency\r\n\n");
#endif

    /* 32 BIT Read access */
#if defined (R5F_CORE)
    perf = latencyCalculate_Read32(SELF_TCM_READ_ADDRESS);
    DebugP_log("[32-BIT READ] Self TCM Access Average Latency Per Byte: %f ns\r\n", ((perf.cycles) * (APP_SECONDS_IN_NANO_SECONDS / SOC_getSelfCpuClk())));
#elif defined (C7_CORE)
    perf = latencyCalculate_Read32(L2RAM_READ_ADDRESS);
    DebugP_log("[32-BIT READ] L2RAM Access Average Latency Per Byte: %f ns\r\n", ((perf.cycles) * (APP_SECONDS_IN_NANO_SECONDS / SOC_getSelfCpuClk())));
#endif

    perf = latencyCalculate_Read32(SRAM_READ_ADDRESS);
    DebugP_log("[32-BIT READ] MSRAM Access Average Latency Per Byte: %f ns\r\n", ((perf.cycles) * (APP_SECONDS_IN_NANO_SECONDS / SOC_getSelfCpuClk())));

#if defined (R5F_CORE)
    perf = latencyCalculate_Read32(NON_SELF_TCM_ACCESS_ADDRESS);
    DebugP_log("[32-BIT READ] Non-Self TCM Access Average Latency Per Byte: %f ns\r\n", ((perf.cycles) * (APP_SECONDS_IN_NANO_SECONDS / SOC_getSelfCpuClk())));
#endif

    ClockP_sleep(1U);

    /* 64 BIT Read access */
#if defined (R5F_CORE)
    perf = latencyCalculate_Read64(SELF_TCM_READ_ADDRESS);
    DebugP_log("\n[64-BIT READ] Self TCM Access Average Latency Per Byte: %f ns\r\n", ((perf.cycles) * (APP_SECONDS_IN_NANO_SECONDS / SOC_getSelfCpuClk())));
#elif defined (C7_CORE)
    perf = latencyCalculate_Read64(L2RAM_READ_ADDRESS);
    DebugP_log("\n[64-BIT READ] L2RAM Access Average Latency Per Byte: %f ns\r\n", ((perf.cycles) * (APP_SECONDS_IN_NANO_SECONDS / SOC_getSelfCpuClk())));
#endif

    perf = latencyCalculate_Read64(SRAM_READ_ADDRESS);
    DebugP_log("[64-BIT READ] MSRAM Access Average Latency Per Byte: %f ns\r\n", ((perf.cycles) * (APP_SECONDS_IN_NANO_SECONDS / SOC_getSelfCpuClk())));

#if defined (R5F_CORE)
    perf = latencyCalculate_Read64(NON_SELF_TCM_ACCESS_ADDRESS);
    DebugP_log("[64-BIT READ] Non-Self TCM Access Average Latency Per Byte: %f ns\r\n", ((perf.cycles) * (APP_SECONDS_IN_NANO_SECONDS / SOC_getSelfCpuClk())));
#endif

    DebugP_log("BENCHMARK END\r\n");

    DebugP_log("All tests have passed!!\r\n\r\n");
}

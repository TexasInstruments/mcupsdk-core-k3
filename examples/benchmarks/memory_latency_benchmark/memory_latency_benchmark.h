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

#ifndef MEMORY_LATENCY_BENCHMARK_H_
#define MEMORY_LATENCY_BENCHMARK_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/pmu.h>
#include <drivers/soc.h>
#include <kernel/dpl/DebugP.h>
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#if defined (R5F_CORE)

#define SELF_TCM_READ_ADDRESS           (0x00001000U)
#define SELF_TCM_WRITE_ADDRESS          (0x00007F00U)
#define SELF_TCM_WRITE_ADDRESS1         (0x00007F08U)
#define SRAM_READ_ADDRESS               (0x72080000U)
#define SRAM_WRITE_ADDRESS              (0x72080000U)
#define SRAM_WRITE_ADDRESS1             (0x72080000U)
#define NON_SELF_TCM_ACCESS_ADDRESS     (0x05E00000U)
#define NON_SELF_TCM_ACCESS_ADDRESS1    (0x05E00008U)

#elif defined (C7_CORE)

#define SRAM_READ_ADDRESS               (0x80200000U)
#define L2RAM_READ_ADDRESS              (0x7E000000U)

#endif

typedef struct {
    double cycles;
} benchmark_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

benchmark_t latencyCalculate_Read32(uint32_t address);

benchmark_t latencyCalculate_Read64(uint32_t address);

#if defined(C7_CORE)
void c7x_Read32(uint32_t address);
void c7x_Read64(uint32_t address);
#endif

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_LATENCY_BENCHMARK_H_ */

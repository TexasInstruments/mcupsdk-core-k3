/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#if __C7X_VEC_SIZE_BITS__ == 512
#include <ti/csl/arch/c7x/cslr_C7X_CPU.h>
#include <ti/csl/csl_clec.h>
#else
#include <drivers/hw_include/csl_clec.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if SOC == AM275
#define NUM_POINTS (128)
#define NUM_CHANNELS (128)
#else
#define NUM_POINTS (128)
#define NUM_CHANNELS (128)
#endif

#define BLOCK_WIDTH (NUM_POINTS << 1)
#define BLOCK_HEIGHT (16)

#define L2SRAM_SIZE (800 * 1024) /* 800 KB */
#define DDR_SIZE (1024 * 1024)   /*  1 MB */


__attribute__((section(".l2sramData"), aligned(128))) uint8_t l2Buffer[L2SRAM_SIZE];
__attribute__((section(".ddrData"), aligned(128))) uint8_t ddrBuffer[DDR_SIZE];


#define DDR_ADDR ((FFTLIB_F32 *)(ddrBuffer))
#define TEMP_OUT_ADDR ((DDR_ADDR + (NUM_POINTS * NUM_CHANNELS * 2)))

#define INPUT_BLOCK_ADDR (float *)l2Buffer
#define TEMP_BLOCK_ADDR (INPUT_BLOCK_ADDR + 2 * BLOCK_HEIGHT * BLOCK_WIDTH)
#define OUT_BLOCK_ADDR (TEMP_BLOCK_ADDR + 2 * BLOCK_HEIGHT * BLOCK_WIDTH)
#define TW_ADDR (OUT_BLOCK_ADDR + 2 * BLOCK_HEIGHT * BLOCK_WIDTH)
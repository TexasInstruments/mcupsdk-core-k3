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

#include <dsplib.h>
#include <stdint.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define L2SRAM_SIZE (512 * 1024) /* 512 KB */

__attribute__((section(".l2sramData"), aligned(128)))
uint8_t l2Buffer[L2SRAM_SIZE];

#define NUM_CHANNELS (8)
#define NUM_CHANNELS_OUT (NUM_CHANNELS)
#define BLOCK_SIZE (64)

#define INPUT_SIZE (BLOCK_SIZE * NUM_CHANNELS)
#define OUTPUT_SIZE (BLOCK_SIZE * NUM_CHANNELS_OUT)

#define INPUT_ADDR (float *) l2Buffer

#define INT_TO_FLOAT_ADDR (INPUT_ADDR + INPUT_SIZE)

// For cascadeBiquad
#define CASCADE_FORM (DSPLIB_NUM_STATE_VARS_DF1)
#define CASCADE_NUM_STAGES (3)
#define CASCADE_FILTER_SIZE (CASCADE_NUM_STAGES * 5)
#define CASCADE_FILTER_VAR_SIZE                                               \
    (CASCADE_NUM_STAGES * CASCADE_FORM * NUM_CHANNELS)

#define CASCADE0_COEFF_ADDR (INT_TO_FLOAT_ADDR + INPUT_SIZE)
#define CASCADE0_FILTER_VAR_ADDR (CASCADE0_COEFF_ADDR + CASCADE_FILTER_SIZE)
#define CASCADE0_OUT_ADDR (CASCADE0_FILTER_VAR_ADDR + CASCADE_FILTER_VAR_SIZE)

// For gainNCh
#define GAIN_NCH_TARGET_ADDR (CASCADE0_OUT_ADDR + INPUT_SIZE)
#define GAIN_NCH_OUT_ADDR (GAIN_NCH_TARGET_ADDR + NUM_CHANNELS)

// For muteNCh
#define MUTE_NCH_INITIAL_GAIN_ADDR (GAIN_NCH_OUT_ADDR + INPUT_SIZE)
#define MUTE_NCH_TARGET_GAIN_ADDR (MUTE_NCH_INITIAL_GAIN_ADDR + NUM_CHANNELS)
// Ensure proper alignment for int32_t array
#define MUTE_NCH_IS_MUTE_ADDR                                                 \
    (MUTE_NCH_TARGET_GAIN_ADDR + NUM_CHANNELS + (NUM_CHANNELS % 2))
#define MUTE_NCH_OUT_ADDR                                                     \
    (MUTE_NCH_IS_MUTE_ADDR + NUM_CHANNELS * sizeof(int32_t) / sizeof(float) + \
     (NUM_CHANNELS % 2))

// For final typeConversion
#define FLOAT_TO_INT_ADDR (MUTE_NCH_OUT_ADDR + INPUT_SIZE)

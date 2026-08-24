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

/*
 * Memory map for the YAMNET logmel_spectrum signal-chain example.
 *
 * TISP equivalent of the YAMNET analysis/synthesis framing (the YAMNET model itself
 * is a documented gap to be ported by the AI team).  Mirrors the TISP_11_02 signal
 * chain in spirit (hand-mapped L2 buffers, one opVec, block-by-block execution), but
 * uses individually-declared 128-byte-aligned L2 arrays (correct-by-construction)
 * instead of one bump-partitioned buffer.
 *
 * The STFT setup follows the YAMNET-style parameters from the reference model:
 * n_fft=512, hop=256, win_length=512, and a sqrt-Hann window. The resulting
 * spectrum is arranged in the layout expected by the downstream graph.
 *
 * NOTE: the reference YAMNET flow uses center=True padding, while the TISP STFT node
 * uses center=False, so this chain is interior-equivalent rather than bit-exact at
 * the signal boundaries.
 */
#pragma once

#include <audiolib.h>
#include <stdint.h>

/* ---- YAMNET STFT/ISTFT parameters ------------------------------------------------ */
#define YAMNET_FS_HZ (16000)
#define YAMNET_NUM_CHANNELS (1)
#define YAMNET_FFT_SIZE (512)
#define YAMNET_HOP_SIZE (160)
#define YAMNET_WINDOW_LENGTH (400)         /* 25ms sqrt-Hann window, zero-padded into the 512-point FFT */
#define YAMNET_ONESIDED (1)
#define YAMNET_WINDOW_TYPE (1)             /* TISP::WindowType::Hann              */
#define YAMNET_WINDOW_ALIGN (0)            /* kCenter (irrelevant, winLen == fftSize)  */
#define YAMNET_WINDOW_PERIODIC (1)         /* torch.hann_window default periodic=True  */
#define YAMNET_FMIN      (125)
#define YAMNET_FMAX      (7500)
#define YAMNET_NUM_BLOCKS (1)
#define YAMNET_IS_INTERLEAVED (1)
#define YAMNET_INPUT_SAMPLES (160)      /* Input block size used by this example */
/* Derived constants for the configured frame layout. These values are kept here to
 * size the analysis and synthesis buffers consistently with the selected FFT, hop,
 * and window parameters. */
#define YAMNET_NUM_BINS (257)              /* One-sided FFT bins for a 512-point spectrum */
#define YAMNET_OUT_BINS (514)              /* Complex values stored as interleaved real/imag pairs */
#define YAMNET_MEL_BINS (64)                /* mel bands*/
#define YAMNET_MEL_SCALE (0)                /*kHtk*/
#define YAMNET_MEL_NORM (0)
#define YAMNET_NUM_WINDOWS (1)             /* Number of STFT frames produced for the input block */
#define YAMNET_STFT_OVERLAP (352)          /* Overlap state size for the STFT path */
#define YAMNET_POWER     (1)
#define YAMNET_LOG_EPS   0.001f
/* Scratch capacities in float elements for the STFT nodes used here. */
#define YAMNET_STFT_SCRATCH_ELEMS (1888)
/* Per-block element counts used by the analysis and synthesis buffers. */
#define YAMNET_MODEL_ELEMS (YAMNET_MEL_BINS * YAMNET_NUM_WINDOWS) /* Mel bins per frame */
#define YAMNET_OUTPUT_SAMPLES (YAMNET_NUM_WINDOWS * YAMNET_HOP_SIZE) /* Samples produced for the output block */

/* Explicit byte counts for buffers that carry state across calls
 * (must be re-zeroed by create_pre_graph() on every activation)
 * State buffers are allocated in the arena, not static. */
#define YAMNET_STFT_STATE_BYTES (YAMNET_STFT_OVERLAP * YAMNET_NUM_CHANNELS * sizeof(float))

/* Buffer addresses: allocated from one-time STFT arena on first IPC message
 * (see stft_signal_chain_yamnet.cpp for arena initialization pattern).
 * These macros are defined in the .cpp file to reference arena buffers. */


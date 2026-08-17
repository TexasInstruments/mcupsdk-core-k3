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
 * Memory map for the GTCRN STFT/ISTFT signal-chain example.
 *
 * TISP equivalent of the gtcrn analysis/synthesis framing (the GTCRN model itself
 * is a documented gap to be ported by the AI team).  Mirrors the TISP_11_02 signal
 * chain in spirit (hand-mapped L2 buffers, one opVec, block-by-block execution), but
 * uses individually-declared 128-byte-aligned L2 arrays (correct-by-construction)
 * instead of one bump-partitioned buffer.
 *
 * The STFT setup follows the GTCRN-style parameters from the reference model:
 * n_fft=512, hop=256, win_length=512, and a sqrt-Hann window. The resulting
 * spectrum is arranged in the layout expected by the downstream graph.
 *
 * NOTE: the reference GTCRN flow uses center=True padding, while the TISP STFT node
 * uses center=False, so this chain is interior-equivalent rather than bit-exact at
 * the signal boundaries.
 */
#pragma once

#include <audiolib.h>
#include <stdint.h>

/* ------------------------------ gtcrn STFT/ISTFT parameters ----------------------- */
#define GTCRN_FS_HZ (16000)
#define GTCRN_NUM_CHANNELS (1)
#define GTCRN_FFT_SIZE (512)
#define GTCRN_HOP_SIZE (256)
#define GTCRN_WINDOW_LENGTH (512)         /* sqrt-Hann spans the full fftSize         */
#define GTCRN_ONESIDED (1)
#define GTCRN_WINDOW_TYPE (6)             /* TISP::WindowType::kSqrtHann              */
#define GTCRN_WINDOW_ALIGN (0)            /* kCenter (irrelevant, winLen == fftSize)  */
#define GTCRN_WINDOW_PERIODIC (1)         /* torch.hann_window default periodic=True  */

/* One STFT/ISTFT execution processes one input block per channel. */
#define GTCRN_INPUT_SAMPLES (256)        /* Input block size used by this example */
#define GTCRN_TOTAL_SAMPLES (GTCRN_INPUT_SAMPLES) /* 512 samples per channel */

/* Derived constants for the configured frame layout. These values are kept here to
 * size the analysis and synthesis buffers consistently with the selected FFT, hop,
 * and window parameters. */
#define GTCRN_NUM_BINS (257)              /* One-sided FFT bins for a 512-point spectrum */
#define GTCRN_OUT_BINS (514)              /* Complex values stored as interleaved real/imag pairs */
#define GTCRN_NUM_WINDOWS (1)             /* Number of STFT frames produced for the input block */
#define GTCRN_STFT_OVERLAP (256)          /* Overlap state size for the STFT path */
#define GTCRN_ISTFT_OLA (256)             /* Overlap-add state size for the ISTFT path */

/* Scratch capacities in float elements for the STFT and ISTFT nodes used here. */
#define GTCRN_STFT_SCRATCH_ELEMS (1024)
#define GTCRN_ISTFT_SCRATCH_ELEMS (2048)

/* Per-block element counts used by the analysis and synthesis buffers. */
#define GTCRN_SPEC_ELEMS (GTCRN_NUM_WINDOWS * GTCRN_OUT_BINS)  /* Frame-major spectrum storage */
#define GTCRN_MODEL_ELEMS (GTCRN_NUM_BINS * GTCRN_NUM_WINDOWS * 2) /* Real and imaginary values per bin/frame */
#define GTCRN_OUTPUT_SAMPLES (GTCRN_NUM_WINDOWS * GTCRN_HOP_SIZE)  /* Samples produced for the output block */
#define GTCRN_IS_INTERLEAVED (1)

#if defined(HOST_EMULATION)
#define L2_ATTR
#else
#define L2_ATTR __attribute__((section(".l2sramData"), aligned(128)))
#endif
#define GTCRN_STFT_STATE_BYTES (GTCRN_STFT_OVERLAP * GTCRN_NUM_CHANNELS * sizeof(float))
#define GTCRN_ISTFT_OLA_BYTES  (GTCRN_ISTFT_OLA * GTCRN_NUM_CHANNELS * sizeof(float))

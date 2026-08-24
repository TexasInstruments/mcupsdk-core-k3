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
 * Memory map for the vggish logmel_spectrum signal-chain example.
 *
 * TISP equivalent of the vggish analysis framing  Mirrors the TISP_11_02 signal
 * chain in spirit (hand-mapped L2 buffers, one opVec, block-by-block execution), but
 * uses individually-declared 128-byte-aligned L2 arrays (correct-by-construction)
 * instead of one bump-partitioned buffer.
 *
 * The logmel-spec setup follows the vggish-style parameters from the reference model:
 * n_fft=1024, hop=512, win_length=1024, and a Hann window.
 */
#pragma once

#include <audiolib.h>
#include <stdint.h>

/* ----vggish STFT/ISTFT parameters ------------------------------------------------ */
#define VGGISH_FS_HZ (16000)
#define VGGISH_NUM_CHANNELS (1)
#define VGGISH_FFT_SIZE (1024)
#define VGGISH_HOP_SIZE (512)
#define VGGISH_WINDOW_LENGTH (1024)         /* Hann spans the full fftSize        */
#define VGGISH_ONESIDED (1)
#define VGGISH_WINDOW_TYPE (1)             /* TISP::WindowType::Hann              */
#define VGGISH_WINDOW_ALIGN (0)            /* kCenter (irrelevant, winLen == fftSize)  */          
#define VGGISH_WINDOW_PERIODIC (1)         /* torch.hann_window default periodic=True  */
#define VGGISH_fmin             (0)
#define VGGISH_fmax             (8000)

/* One STFT/ISTFT execution processes one input block per channel. */
#define VGGISH_NUM_BLOCKS (1)
#define VGGISH_INPUT_SAMPLES (512)      /* Input block size used by this example */

/* Derived constants for the configured frame layout. These values are kept here to
 * size the analysis and synthesis buffers consistently with the selected FFT, hop,
 * and window parameters. */
#define VGGISH_NUM_BINS (513)              /* One-sided FFT bins for a 513-point spectrum */
#define VGGISH_OUT_BINS (1026)              /* Complex values stored as interleaved real/imag pairs */
#define VGGISH_MEL_BINS (64)                /* mel bands*/
#define VGGISH_MEL_SCALE (0)               /*kHtk*/
#define VGGISH_MEL_NORM (0)
#define VGGISH_NUM_WINDOWS (1)             /* Number of STFT frames produced for the input block */
#define VGGISH_STFT_OVERLAP (512)          /* Overlap state size for the STFT path */
#define VGGISH_power            (2)
#define VGGISH_log              (1e-9f)
/* Scratch capacities in float elements for the STFT  nodes used here. */
#define VGGISH_STFT_SCRATCH_ELEMS (3608)


/* Per-block element counts used by the analysis and synthesis buffers. */
#define VGGISH_MODEL_ELEMS ( VGGISH_MEL_BINS * VGGISH_NUM_WINDOWS ) /* Mel bins per frame */
#define VGGISH_OUTPUT_SAMPLES ( VGGISH_NUM_WINDOWS * VGGISH_HOP_SIZE)  /* Samples produced for the output block */
#define VGGISH_IS_INTERLEAVED (1)

/* Explicit byte counts for buffers that carry state across calls
 * (must be re-zeroed by create_pre_graph() on every activation)
 * State buffers are allocated in the arena, not static. */
#define VGGISH_STFT_STATE_BYTES (VGGISH_STFT_OVERLAP * VGGISH_NUM_CHANNELS * sizeof(float))

/* Buffer addresses: allocated from one-time STFT arena on first IPC message
 * (see stft_signal_chain_vggish.cpp for arena initialization pattern).
 * These macros are defined in the .cpp file to reference arena buffers. */



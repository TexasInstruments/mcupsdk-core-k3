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
 * Memory map for the DCCRN STFT/ISTFT signal-chain example.
 *
 * This file describes the TISP buffer layout used by the pre/post-processing
 * graphs that prepare DCCRN model inputs and reconstruct waveform samples after
 * the model output is produced.
 *
 * The framing follows the DCCRN-style ConvSTFT/ConviSTFT parameters
 * (window length 400, hop 100, FFT size 512, Hann window). The 400-sample window is
 * left-aligned in the 512-point FFT frame, and the input is padded by 300 samples on
 * each side to mirror the DCCRN-style overlap layout.
 *
 * NOTE: TISP Stft uses center=False (no edge pad), so the implementation applies the
 *       equivalent 300-sample pre-padding on each side. The pre-processing graph then
 *       splits the complex spectrum into separate real/imaginary planes with a
 *       MatTrans + Deinterleave sequence, while the post-processing graph reassembles
 *       them with Interleave + MatTrans before the ISTFT stage.
 */
#pragma once

#include <audiolib.h>
#include <stdint.h>

/* ---- DCCRN STFT/ISTFT parameters ------------------------------------------------ */
#define DCCRN_FS_HZ (16000)
#define DCCRN_NUM_CHANNELS (1)
#define DCCRN_FFT_SIZE (512)
#define DCCRN_HOP_SIZE (100)
#define DCCRN_WINDOW_LENGTH (400)         /* < fftSize -> left-aligned in the 512-pt frame */
#define DCCRN_ONESIDED (1)
#define DCCRN_WINDOW_TYPE (1)             /* TISP::WindowType::kHann                       */
#define DCCRN_WINDOW_ALIGN (1)            /* kLeft (DCCRN ConvSTFT left-aligns the window)  */
#define DCCRN_WINDOW_PERIODIC (1)         /* get_window(..., fftbins=True) -> periodic      */

/* Input pre-padding to match the DCCRN-style ConvSTFT framing: the input is padded
 * by 300 samples on each side so the effective analysis window can slide across the
 * centered frame without introducing edge padding from TISP STFT. */
#define DCCRN_PAD (300)                   /* Zero-padding applied on each side of the input chunk */
#define DCCRN_INPUT_SAMPLES (100)         /* Input chunk size used by this example */
#define DCCRN_NUM_BLOCKS (1)              /* Single block per message in this example */
#define DCCRN_TOTAL_SAMPLES (DCCRN_INPUT_SAMPLES * DCCRN_NUM_BLOCKS) /* 600 samples per message */

/* Derived constants for the configured STFT/ISTFT frame layout. The example uses
 * 6 analysis frames for the 600-sample input chunk with the 400-sample window and
 * 100-sample hop configured here. */
#define DCCRN_NUM_BINS (257)              /* FFT bins for a one-sided 512-point spectrum */
#define DCCRN_OUT_BINS (514)              /* Real/imag interleaved complex values: 2 * 257 */
#define DCCRN_NUM_WINDOWS (1)             /* Number of STFT frames produced for the input chunk */
#define DCCRN_STFT_OVERLAP (500)          /* STFT overlap state size: fftSize - hopSize */
#define DCCRN_ISTFT_OLA (500)             /* ISTFT overlap-add state size: fftSize - hopSize */

/* Scratch capacities (in float elements) for the TISP STFT/ISTFT nodes used by
 * the DCCRN preprocessing chain. These values are sized for the configured FFT,
 * hop, and frame count rather than for a generic one-size-fits-all case. */
#define DCCRN_STFT_SCRATCH_ELEMS (1024)
#define DCCRN_ISTFT_SCRATCH_ELEMS (2050)

#define DCCRN_SPEC_ELEMS (DCCRN_NUM_WINDOWS * DCCRN_OUT_BINS)        /* 6 frames * 514 values per frame */
#define DCCRN_MODEL_ELEMS (DCCRN_NUM_BINS * DCCRN_NUM_WINDOWS * 2)   /* Real + imag for all bins and frames */
#define DCCRN_OUTPUT_SAMPLES (DCCRN_NUM_WINDOWS * DCCRN_HOP_SIZE)    /* 6 frames * 100-sample hop = 600 samples */

#define DCCRN_IS_INTERLEAVED (1)

#if defined(HOST_EMULATION)
#define L2_ATTR
#else
#define L2_ATTR __attribute__((section(".l2sramData"), aligned(128)))
#endif
#define DCCRN_STFT_STATE_BYTES (DCCRN_STFT_OVERLAP * DCCRN_NUM_CHANNELS * sizeof(float))
#define DCCRN_ISTFT_OLA_BYTES  (DCCRN_ISTFT_OLA * DCCRN_NUM_CHANNELS * sizeof(float))

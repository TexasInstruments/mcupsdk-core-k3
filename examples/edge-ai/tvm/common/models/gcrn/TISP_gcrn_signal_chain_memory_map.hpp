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
 * Memory map for the GCRN STFT/ISTFT signal-chain example.
 *
 * TISP equivalent of the GCRN STFT framing (the GCRN model itself is a documented gap,
 * ported later by the AI team).
 *
 * GCRN (gcrn-complex-ti_dev): win_size = 320, hop_size = 160 (20ms/10ms @ 16 kHz),
 *   161 freq bins, Hamming analysis window (scipy sym=True -> symmetric), input zero-padded
 *   (win-hop)=160 each side.  Model input tensor is (B, channels(re/im)=2, time_frames, freq) i.e.
 *   TIME-major with re/im as separate planes -> NO transpose is needed (the STFT frame-major
 *   [T x F] complex output is already time x freq); a de-interleave adapter at the model
 *   boundary splits the (re,im) pairs into the 2 planes.
 *
 * NON-POWER-OF-2 FFT (fftSize=320): historically the TISP Stft/Istft nodes required a
 *   power-of-2 fftSize (radix-2 RFFT); non-pow2 RFFT support has since landed in fftlib, so
 *   fftSize=320 now constructs and runs correctly.
 * NOTE: TISP Stft is center=False -> interior-equivalent to gcrn's 160-sample zero-pad.
 *       GCRN's inverse uses NO synthesis window (+ OLA(w^1) normalization); this framing
 *       uses the Hamming window for ISTFT and the node's OLA(w^2) normalization (placeholder).
 */
#pragma once

#include <audiolib.h>
#include <stdint.h>

/* ---- GCRN STFT/ISTFT parameters ------------------------------------------------- */
#define GCRN_FS_HZ (16000)  /* test input: pure 1 kHz sine at 16 kHz (STFT framing is sample-based) */
#define GCRN_NUM_CHANNELS (1)
#define GCRN_FFT_SIZE (320)               /* NON-power-of-2; supported via non-pow2 RFFT in fftlib */
#define GCRN_WINDOW_LENGTH (320)          /* == GCRN_FFT_SIZE */
#define GCRN_WINDOW_TYPE (2)              /* Hamming */
#define GCRN_WINDOW_ALIGN (0)             /* Center */
#define GCRN_WINDOW_PERIODIC (0)
#define GCRN_SYNTH_WINDOW_TYPE (2)        /* Hamming -- must match GCRN_WINDOW_TYPE */
#define GCRN_ONESIDED (1)
#define GCRN_IS_INTERLEAVED (1)

/* Input pre-padding: GCRN ConvSTFT pads win_len-hop=160 each side.  The Stft node's
 * zero-init overlap state already supplies the LEADING 160; we add an explicit TRAILING
 * 160-sample zero pad so the frame count T matches the model exactly (fftSize==win_len==320,
 * so there is NO n_fft-vs-win_len stride mismatch like DCCRN). */
#define GCRN_TRAIL_PAD (160)              /* = win_len - hop (trailing; leading = node overlap) */
#define GCRN_INPUT_SAMPLES (160)        /* F per block: multiple of hop=160, >= fftSize=320 */
/* derived (must match TISP::AUDIOLIB::Stft<float>::calc* ) for one GCRN_INPUT_SAMPLES=160 block:
 *   the node's 160-sample overlap state (leading pad) + this block's 160 new samples = 320
 *   buffered samples == fftSize -> exactly one window is produced per block (numWindows=1). */
#define GCRN_OUT_BINS (322)              /* onesided complex-interleaved floats = N+2       */
#define GCRN_NUM_BINS (161)              /* onesided complex bins = N/2 + 1                 */
#define GCRN_NUM_WINDOWS (1)             /* number of STFT frames produced for the input block */
#define GCRN_STFT_OVERLAP (160)
#define GCRN_ISTFT_OLA (160)              /* fftSize - hopSize                              */
/* Scratch capacities in float elements for the STFT and ISTFT nodes used here. */
#define GCRN_STFT_SCRATCH_ELEMS (640)
#define GCRN_ISTFT_SCRATCH_ELEMS (1282)
#define GCRN_HOP_SIZE (160)
#define GCRN_OUTPUT_SAMPLES (GCRN_NUM_WINDOWS * GCRN_HOP_SIZE)  /* 1*160 = 160 samples per block */
#define GCRN_MODEL_ELEMS (GCRN_NUM_WINDOWS * GCRN_NUM_BINS*2)  /* 1*322 = 322 floats per block */
/* GCRN is time-major (B,2,T,F): no transpose, so the model boundary IS the STFT frame-major
 * output [T x OUT_BINS] (and the ISTFT input).  MODEL elems == SPEC elems. */
#define GCRN_SPEC_ELEMS (GCRN_NUM_WINDOWS * GCRN_OUT_BINS)   /* 1*322 = 322, frame-major (= model layout) */

#if defined(HOST_EMULATION)
#define L2_ATTR
#else
#define L2_ATTR __attribute__((section(".l2sramData"), aligned(128)))
#endif
#define GCRN_STFT_STATE_BYTES (GCRN_STFT_OVERLAP * GCRN_NUM_CHANNELS * sizeof(float))
#define GCRN_ISTFT_OLA_BYTES  (GCRN_ISTFT_OLA * GCRN_NUM_CHANNELS * sizeof(float))


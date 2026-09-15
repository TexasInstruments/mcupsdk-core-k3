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
 * Model Identifiers - Multi-Model Support
 *
 * All supported signal chains (DCCRN, GTCRN, GCRN, VGGish, YAMNet) are
 * compiled into the application. The active model is selected at RUNTIME
 * via the `selected_model` field of the IPC message (see stft_istft_handler.h),
 * not at build time.
 *
 * Each model's own STFT/ISTFT parameters (FFT size, hop size, window
 * type, ...) live in that model's memory-map header
 * (models/<model>/TISP_<model>_signal_chain_memory_map.hpp) under a
 * <MODEL>_* prefix, and are exposed to the runtime dispatcher as a
 * ModelConfig entry (see signal_chain_dispatch.h). This header only
 * defines the shared identifier used to select between them.
 *
 * DCCRN:  Deep Complex Convolution Recurrent Network
 * GTCRN:  Graph-based Time-Frequency Recurrent Network
 * GCRN:   Graph-based Complex Recurrent Network
 * VGGish: VGGish Log-Mel Spectrogram Feature Extractor (analysis-only)
 * YAMNet: YAMNet Log-Mel Spectrogram Feature Extractor (analysis-only)
 */

#ifndef MODEL_CONFIG_H
#define MODEL_CONFIG_H

/* ============================================================================
   Model Selection - Runtime IPC-based
   ============================================================================ */

typedef enum
{
    MODEL_DCCRN = 0,    /* Deep Complex Convolution Recurrent Network */
    MODEL_GTCRN = 1,    /* Graph-based Time-Frequency Recurrent Network */
    MODEL_GCRN  = 2,    /* Graph-based Complex Recurrent Network */
    MODEL_VGGISH = 3,   /* VGGish Log-Mel Spectrogram Feature Extractor (analysis-only) */
    MODEL_YAMNET = 4,   /* YAMNet Log-Mel Spectrogram Feature Extractor (analysis-only) */
    MODEL_COUNT = 5
} ModelId;

#endif /* MODEL_CONFIG_H */

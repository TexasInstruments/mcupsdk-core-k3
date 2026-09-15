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
 * YAMNET Signal Chain Implementation
 *
 * Log-mel spectrogram feature extraction for YAMNet model
 */

#include "stft_signal_chain_yamnet.hpp"
#include "TISP_yamnet_signal_chain_memory_map.hpp"
#include "model_config.h"
#include "signal_chain_dispatch.h"
#include "signal_chain_arena.hpp"
#include <memory>
#include <tisp.hpp>
#include "TISP_window_gen.hpp"
#include "TISP_mel_fbank_gen.hpp"

/* ============================================================================
   STFT Arena - One-time buffer partition over host-provided IPC memory
   ============================================================================ */

enum
{
    YAMNET_STFT_IDX_TYPECONV = 0,
    YAMNET_STFT_IDX_WINDOW,
    YAMNET_STFT_IDX_STATE,
    YAMNET_STFT_IDX_SCRATCH,
    YAMNET_STFT_IDX_MEL_SPEC,
    YAMNET_STFT_IDX_OUTPUT,
    YAMNET_STFT_NUM_BUFS
};

/* Buffer specifications for arena allocation
 * Order must match enum indices above */
static const ArenaBufferSpec kYamnetStftSpecs[YAMNET_STFT_NUM_BUFS] =
{
    {"yamnet_stft_typeconv",  (uint32_t)(YAMNET_INPUT_SAMPLES * YAMNET_NUM_CHANNELS * sizeof(float))},
    {"yamnet_stft_window",    (uint32_t)(YAMNET_FFT_SIZE * sizeof(float))},
    {"yamnet_stft_state",     (uint32_t)YAMNET_STFT_STATE_BYTES},
    {"yamnet_stft_scratch",   (uint32_t)(YAMNET_STFT_SCRATCH_ELEMS * sizeof(float))},
    {"yamnet_stft_mel_spec",  (uint32_t)(YAMNET_NUM_BINS * YAMNET_MEL_BINS * sizeof(float))},
    {"yamnet_stft_output",    (uint32_t)(YAMNET_MODEL_ELEMS * YAMNET_NUM_CHANNELS * sizeof(float))},
};

static SignalChainArenaState g_yamnet_stft_arena;

#define YAMNET_STFT_BUF(idx, type) ((type *)g_yamnet_stft_arena.buffers[idx].addr)

/* STFT-side (create_pre_graph / execute_pre_graph) address macros
 * All allocated from g_yamnet_stft_arena on first message; reused thereafter */
#define TYPECONV_OUT_ADDR    YAMNET_STFT_BUF(YAMNET_STFT_IDX_TYPECONV, float)
#define WINDOW_ADDR          YAMNET_STFT_BUF(YAMNET_STFT_IDX_WINDOW, float)
#define STFT_STATE_ADDR      YAMNET_STFT_BUF(YAMNET_STFT_IDX_STATE, float)
#define STFT_SCRATCH_ADDR    YAMNET_STFT_BUF(YAMNET_STFT_IDX_SCRATCH, float)
#define MEL_SPEC_ADDR        YAMNET_STFT_BUF(YAMNET_STFT_IDX_MEL_SPEC, float)
#define STFT_OUTPUT_ADDR     YAMNET_STFT_BUF(YAMNET_STFT_IDX_OUTPUT, float)

/* ============================================================================
   YAMNET Signal Chain Implementation
   ============================================================================ */

void *StftSignalChainYAMNET::create_pre_graph(int16_t *input_addr)
{
    /* One-time arena initialization on first call; cached thereafter */
    if (!signal_chain_arena_ensure(&g_yamnet_stft_arena, kYamnetStftSpecs, YAMNET_STFT_NUM_BUFS, "YAMNET STFT"))
    {
        return NULL;
    }

    TISP::ErrorCtxt errorCtx;
    TISP::WindowType winType = static_cast<TISP::WindowType>(YAMNET_WINDOW_TYPE);
    TISP::WindowAlign winAlign = static_cast<TISP::WindowAlign>(YAMNET_WINDOW_ALIGN);

    TISP::windowGen<float>(WINDOW_ADDR, YAMNET_FFT_SIZE, YAMNET_WINDOW_LENGTH,
                          winType, (YAMNET_WINDOW_PERIODIC != 0), winAlign);

    TISP::melFbankGen<float>(MEL_SPEC_ADDR, YAMNET_NUM_BINS, YAMNET_MEL_BINS,
                           YAMNET_FS_HZ, YAMNET_FMIN, YAMNET_FMAX,
                           static_cast<TISP::MelScale>(YAMNET_MEL_SCALE),
                           static_cast<TISP::MelNorm>(YAMNET_MEL_NORM));

    memset(STFT_STATE_ADDR, 0, YAMNET_STFT_STATE_BYTES);

    auto preVec = new TISP::opVec();

    if (errorCtx.isSuccess())
    {
        auto k0 = std::make_unique<TISP::AUDIOLIB::TypeConversion<int16_t, float>>(
            input_addr, TYPECONV_OUT_ADDR, YAMNET_NUM_CHANNELS, YAMNET_INPUT_SAMPLES,
            YAMNET_NUM_CHANNELS * sizeof(int16_t), YAMNET_NUM_CHANNELS * sizeof(float),
            YAMNET_IS_INTERLEAVED, "TypeConversion (i16->f32)", 0, errorCtx);
        if (errorCtx.isSuccess()) preVec->push_back(std::move(k0));
    }

    if (errorCtx.isSuccess())
    {
        auto k1 = std::make_unique<TISP::AUDIOLIB::LogMelSpectrum<float>>(
            TYPECONV_OUT_ADDR, STFT_OUTPUT_ADDR, WINDOW_ADDR, MEL_SPEC_ADDR, STFT_STATE_ADDR,
            STFT_SCRATCH_ADDR, YAMNET_FFT_SIZE, YAMNET_HOP_SIZE, YAMNET_NUM_CHANNELS,
            YAMNET_INPUT_SAMPLES, YAMNET_MEL_BINS, YAMNET_POWER, YAMNET_LOG_EPS, errorCtx);
        if (errorCtx.isSuccess()) preVec->push_back(std::move(k1));
    }

    if (!errorCtx.isSuccess() || preVec->size() != 2U)
    {
        delete preVec;
        return NULL;
    }

    return preVec;
}


int32_t StftSignalChainYAMNET::execute_pre_graph(void *pre_graph, int16_t *input_addr)
{
    TISP::opVec *graph=static_cast<TISP::opVec *>(pre_graph);
    if (graph == NULL || graph->size() == 0U) return -1;
    TISP::SetAddr_t     kAddr;
    kAddr.src[0]=static_cast<void *>(input_addr);
   (*graph)[0]->setAddr(kAddr,  TISP::kAddrModeIn);
    TISP::execute::graph(graph);
    return 0;
}



void StftSignalChainYAMNET::delete_pre_graph(void *pre_graph)
{
    if (pre_graph != NULL) delete static_cast<TISP::opVec *>(pre_graph);
}

/* ============================================================================
   Runtime Dispatch: ops table for this model (self-contained in this TU so
   the static arena state and memory-map are never visible outside this
   translation unit)
   ============================================================================ */

static StftSignalChainYAMNET g_yamnet_impl;

static void *yamnet_create_pre_graph(int16_t *input_addr)
{
    return g_yamnet_impl.create_pre_graph(input_addr);
}

static int32_t yamnet_execute_pre_graph(void *graph, int16_t *input_addr)
{
    return g_yamnet_impl.execute_pre_graph(graph, input_addr);
}

static void yamnet_delete_pre_graph(void *graph)
{
    g_yamnet_impl.delete_pre_graph(graph);
}

static float *yamnet_get_preprocess_buf(void)
{
    return STFT_OUTPUT_ADDR;
}
static void yamnet_reset_arenas(void)
{
    /* YAMNet is analysis-only: only the STFT arena needs to be reset. */
    signal_chain_arena_reset_ready(&g_yamnet_stft_arena);
}

static const ModelConfig yamnet_config =
{
    .input_samples = YAMNET_INPUT_SAMPLES,
    .model_elems = YAMNET_MODEL_ELEMS,
    .output_samples = YAMNET_OUTPUT_SAMPLES,
    .batch_n = 64
};

static const SignalChainOps kYamnetOps =
{
    .name = "YAMNET",
    .config = &yamnet_config,
    .create_pre_graph = yamnet_create_pre_graph,
    .create_post_graph = NULL,      /* Analysis-only, no synthesis */
    .execute_pre_graph = yamnet_execute_pre_graph,
    .execute_post_graph = NULL,     /* Analysis-only */
    .delete_pre_graph = yamnet_delete_pre_graph,
    .delete_post_graph = NULL,      /* Analysis-only */
    .get_preprocess_buf = yamnet_get_preprocess_buf,
    .get_postprocess_buf = NULL,    /* Output is preprocess_buf (log-mel spectrogram) */
    .reset_arenas = yamnet_reset_arenas
};

extern "C" const SignalChainOps *yamnet_get_ops(void)
{
    return &kYamnetOps;
}

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
 * DCCRN Signal Chain Implementation
 *
 * This implements the TISP pre/post-processing graph used to prepare
 * complex spectra for the DCCRN model and reconstruct audio samples after
 * the model output has been produced.
 */

#include "stft_signal_chain_dccrn.hpp"
#include "TISP_dccrn_signal_chain_memory_map.hpp"
#include "model_config.h"
#include "signal_chain_dispatch.h"
#include "signal_chain_arena.hpp"
#include <memory>
#include <tisp.hpp>
#include "TISP_window_gen.hpp"

/* ============================================================================
   STFT / ISTFT arenas
   One-time buffer partition over host-provided IPC memory (see
   signal_chain_arena.hpp). STFT and ISTFT never share a buffer -- every
   role that used to be reused between create_pre_graph and create_post_graph
   (TypeConvOut, Window, and the two transpose intermediates) has its own
   independent copy per arena.
   ============================================================================ */

enum
{
    DCCRN_STFT_IDX_TYPECONV = 0,
    DCCRN_STFT_IDX_WINDOW,
    DCCRN_STFT_IDX_STATE,
    DCCRN_STFT_IDX_SCRATCH,
    DCCRN_STFT_IDX_TRANSPOSE1,
    DCCRN_STFT_IDX_OUTPUT,
    DCCRN_STFT_NUM_BUFS
};

enum
{
    DCCRN_ISTFT_IDX_TYPECONV = 0,
    DCCRN_ISTFT_IDX_WINDOW,
    DCCRN_ISTFT_IDX_OLA,
    DCCRN_ISTFT_IDX_SCRATCH,
    DCCRN_ISTFT_IDX_OUTPUT,
    DCCRN_ISTFT_NUM_BUFS
};

/* Order must match the DCCRN_STFT_IDX_* enum above. */
static const ArenaBufferSpec kDccrnStftSpecs[DCCRN_STFT_NUM_BUFS] =
{
    {"dccrn_stft_typeconv",   (uint32_t)(DCCRN_INPUT_SAMPLES * DCCRN_NUM_CHANNELS * sizeof(float))},
    {"dccrn_stft_window",     (uint32_t)(DCCRN_FFT_SIZE * sizeof(float))},
    {"dccrn_stft_state",      (uint32_t)DCCRN_STFT_STATE_BYTES},
    {"dccrn_stft_scratch",    (uint32_t)(DCCRN_STFT_SCRATCH_ELEMS * sizeof(float))},
    {"dccrn_stft_transpose1", (uint32_t)(DCCRN_SPEC_ELEMS * DCCRN_NUM_CHANNELS * sizeof(float))},
    {"dccrn_stft_output",     (uint32_t)(DCCRN_MODEL_ELEMS * DCCRN_NUM_CHANNELS * sizeof(float))},
};

/* Order must match the DCCRN_ISTFT_IDX_* enum above. */
static const ArenaBufferSpec kDccrnIstftSpecs[DCCRN_ISTFT_NUM_BUFS] =
{
    {"dccrn_istft_typeconv",   (uint32_t)(DCCRN_INPUT_SAMPLES * DCCRN_NUM_CHANNELS * sizeof(float))},
    {"dccrn_istft_window",     (uint32_t)(DCCRN_FFT_SIZE * sizeof(float))},
    {"dccrn_istft_ola",        (uint32_t)DCCRN_ISTFT_OLA_BYTES},
    {"dccrn_istft_scratch",    (uint32_t)(DCCRN_ISTFT_SCRATCH_ELEMS * sizeof(float))},
    {"dccrn_istft_output",     (uint32_t)(DCCRN_OUTPUT_SAMPLES * DCCRN_NUM_CHANNELS * sizeof(int16_t))},
};

static SignalChainArenaState g_dccrn_stft_arena;
static SignalChainArenaState g_dccrn_istft_arena;

#define DCCRN_STFT_BUF(idx, type)  ((type *)g_dccrn_stft_arena.buffers[idx].addr)
#define DCCRN_ISTFT_BUF(idx, type) ((type *)g_dccrn_istft_arena.buffers[idx].addr)

/* STFT-side (create_pre_graph / execute_pre_graph) address macros
 * MatTrans and Deinterleave have been moved to separate utility signal chains */
#define TYPECONV_OUT_ADDR   DCCRN_STFT_BUF(DCCRN_STFT_IDX_TYPECONV, float)
#define STFT_WINDOW_ADDR     DCCRN_STFT_BUF(DCCRN_STFT_IDX_WINDOW, float)
#define STFT_STATE_ADDR     DCCRN_STFT_BUF(DCCRN_STFT_IDX_STATE, float)
#define STFT_SCRATCH_ADDR   DCCRN_STFT_BUF(DCCRN_STFT_IDX_SCRATCH, float)
#define STFT_OUT_ADDR       DCCRN_STFT_BUF(DCCRN_STFT_IDX_TRANSPOSE1, float)   /* [T x F] complex-interleaved, frame-major */
#define DCCRN_STFT_OUTPUT_ADDR DCCRN_STFT_BUF(DCCRN_STFT_IDX_OUTPUT, float)

/* ISTFT-side (create_post_graph / execute_post_graph) address macros
 * Interleave and MatTrans have been moved to separate utility signal chains */
#define ISTFT_TYPECONV_OUT_ADDR DCCRN_ISTFT_BUF(DCCRN_ISTFT_IDX_TYPECONV, float)
#define ISTFT_WINDOW_ADDR       DCCRN_ISTFT_BUF(DCCRN_ISTFT_IDX_WINDOW, float)
#define ISTFT_OLA_ADDR          DCCRN_ISTFT_BUF(DCCRN_ISTFT_IDX_OLA, float)
#define ISTFT_SCRATCH_ADDR      DCCRN_ISTFT_BUF(DCCRN_ISTFT_IDX_SCRATCH, float)
#define DCCRN_ISTFT_OUTPUT_ADDR DCCRN_ISTFT_BUF(DCCRN_ISTFT_IDX_OUTPUT, int16_t)

/* ============================================================================
   DCCRN Signal Chain Implementation
   ============================================================================ */

void *StftSignalChainDCCRN::create_pre_graph(int16_t *input_addr)
{
    if (!signal_chain_arena_ensure(&g_dccrn_stft_arena, kDccrnStftSpecs, DCCRN_STFT_NUM_BUFS, "STFT"))
    {
        return NULL;
    }

    TISP::ErrorCtxt errorCtx;
    TISP::WindowType winType = static_cast<TISP::WindowType>(DCCRN_WINDOW_TYPE);
    TISP::WindowAlign winAlign = static_cast<TISP::WindowAlign>(DCCRN_WINDOW_ALIGN);

    TISP::windowGen<float>(STFT_WINDOW_ADDR, DCCRN_FFT_SIZE, DCCRN_WINDOW_LENGTH,
                          winType, (DCCRN_WINDOW_PERIODIC != 0), winAlign);
    memset(STFT_STATE_ADDR, 0, DCCRN_STFT_STATE_BYTES);

    auto preVec = new TISP::opVec();

    if (errorCtx.isSuccess())
    {
        auto k0 = std::make_unique<TISP::AUDIOLIB::TypeConversion<int16_t, float>>(
            input_addr, TYPECONV_OUT_ADDR, DCCRN_NUM_CHANNELS, DCCRN_INPUT_SAMPLES,
            DCCRN_NUM_CHANNELS * sizeof(int16_t), DCCRN_NUM_CHANNELS * sizeof(float),
            DCCRN_IS_INTERLEAVED, "TypeConversion (i16->f32)", 0, errorCtx);
        if (errorCtx.isSuccess()) preVec->push_back(std::move(k0));
    }

    if (errorCtx.isSuccess())
    {
        auto k1 = std::make_unique<TISP::AUDIOLIB::Stft<float>>(
            TYPECONV_OUT_ADDR, STFT_OUT_ADDR, STFT_WINDOW_ADDR, STFT_STATE_ADDR,
            STFT_SCRATCH_ADDR, DCCRN_FFT_SIZE, DCCRN_HOP_SIZE, DCCRN_NUM_CHANNELS,
            DCCRN_INPUT_SAMPLES, (DCCRN_ONESIDED != 0), "Stft", 1, errorCtx);
        if (errorCtx.isSuccess()) preVec->push_back(std::move(k1));
    }

    if (!errorCtx.isSuccess() || preVec->size() != 2U)
    {
        delete preVec;
        return NULL;
    }
    return preVec;
}

void *StftSignalChainDCCRN::create_post_graph(float *model_out)
{
    if (!signal_chain_arena_ensure(&g_dccrn_istft_arena, kDccrnIstftSpecs, DCCRN_ISTFT_NUM_BUFS, "ISTFT"))
    {
        return NULL;
    }

    TISP::ErrorCtxt errorCtx;
    TISP::WindowType winType = static_cast<TISP::WindowType>(DCCRN_WINDOW_TYPE);
    TISP::WindowAlign winAlign = static_cast<TISP::WindowAlign>(DCCRN_WINDOW_ALIGN);

    TISP::windowGen<float>(ISTFT_WINDOW_ADDR, DCCRN_FFT_SIZE, DCCRN_WINDOW_LENGTH,
                          winType, (DCCRN_WINDOW_PERIODIC != 0), winAlign);
    memset(ISTFT_OLA_ADDR, 0, DCCRN_ISTFT_OLA_BYTES);

    auto postVec = new TISP::opVec();

    if (errorCtx.isSuccess())
    {
        auto k2 = std::make_unique<TISP::AUDIOLIB::Istft<float>>(
            model_out, ISTFT_TYPECONV_OUT_ADDR, ISTFT_WINDOW_ADDR, ISTFT_OLA_ADDR,
            ISTFT_SCRATCH_ADDR, DCCRN_FFT_SIZE, DCCRN_HOP_SIZE, DCCRN_NUM_CHANNELS,
            DCCRN_NUM_WINDOWS, (DCCRN_ONESIDED != 0), "Istft", 2, errorCtx);
        if (errorCtx.isSuccess()) postVec->push_back(std::move(k2));
    }

    if (errorCtx.isSuccess())
    {
        auto k3 = std::make_unique<TISP::AUDIOLIB::TypeConversion<float, int16_t>>(
            ISTFT_TYPECONV_OUT_ADDR, DCCRN_ISTFT_OUTPUT_ADDR, DCCRN_NUM_CHANNELS, DCCRN_OUTPUT_SAMPLES,
            DCCRN_NUM_CHANNELS * sizeof(float), DCCRN_NUM_CHANNELS * sizeof(int16_t),
            DCCRN_IS_INTERLEAVED, "TypeConversion (f32->i16)", 3, errorCtx);
        if (errorCtx.isSuccess()) postVec->push_back(std::move(k3));
    }
    if (!errorCtx.isSuccess() || postVec->size() != 2U)
    {
        delete postVec;
        return NULL;
    }
    return postVec;
}

int32_t StftSignalChainDCCRN::execute_pre_graph(void *pre_graph, int16_t *input_addr)
{
    TISP::opVec *graph = static_cast<TISP::opVec *>(pre_graph);
    if (graph == NULL || graph->size() == 0U) return -1;
    TISP::SetAddr_t     kAddr;
    kAddr.src[0]=static_cast<void *>(input_addr);
   (*graph)[0]->setAddr(kAddr,  TISP::kAddrModeIn);
    TISP::execute::graph(graph);
    return 0;
}

int32_t StftSignalChainDCCRN::execute_post_graph(void *post_graph, float *input_addr)
{
    TISP::opVec *graph = static_cast<TISP::opVec *>(post_graph);
    if (graph == NULL || graph->size() == 0U) return -1;
    TISP::SetAddr_t     kAddr;
    kAddr.src[0]=static_cast<void *>(input_addr);
    (*graph)[0]->setAddr(kAddr,  TISP::kAddrModeIn);
    TISP::execute::graph(graph);
    return 0;
}

void StftSignalChainDCCRN::delete_pre_graph(void *pre_graph)
{
    if (pre_graph != NULL) delete static_cast<TISP::opVec *>(pre_graph);
}

void StftSignalChainDCCRN::delete_post_graph(void *post_graph)
{
    if (post_graph != NULL) delete static_cast<TISP::opVec *>(post_graph);
}

/* ============================================================================
   Runtime Dispatch: ops table for this model (self-contained in this TU so
   the static arena state / memory-map buffers never need to be visible
   outside this translation unit)
   ============================================================================ */

static StftSignalChainDCCRN g_dccrn_impl;

static void *dccrn_create_pre_graph(int16_t *input_addr)
{
    return g_dccrn_impl.create_pre_graph(input_addr);
}
static void *dccrn_create_post_graph(float *model_out)
{
    return g_dccrn_impl.create_post_graph(model_out);
}
static int32_t dccrn_execute_pre_graph(void *graph, int16_t *input_addr)
{
    return g_dccrn_impl.execute_pre_graph(graph, input_addr);
}
static int32_t dccrn_execute_post_graph(void *graph, float *input_addr)
{
    return g_dccrn_impl.execute_post_graph(graph, input_addr);
}
static void dccrn_delete_pre_graph(void *graph)
{
    g_dccrn_impl.delete_pre_graph(graph);
}
static void dccrn_delete_post_graph(void *graph)
{
    g_dccrn_impl.delete_post_graph(graph);
}
static float *dccrn_get_preprocess_buf(void)
{
    /* STFT operator writes its frame-major complex output into STFT_OUT_ADDR
     * (the transpose1 buffer). The model's preprocess buffer should point
     * to that STFT output, not the separate DCCRN_STFT_OUTPUT_ADDR which is
     * reserved for post-model output. Return STFT_OUT_ADDR here so callers
     * see the actual STFT results. */
    return STFT_OUT_ADDR;
}
static int16_t *dccrn_get_postprocess_buf(void)
{
    return DCCRN_ISTFT_OUTPUT_ADDR;
}

static void dccrn_reset_arenas(void)
{
    /* Reset both arenas so the next DCCRN activation re-partitions its
     * workspace from the new ARM-provided buffer. */
    signal_chain_arena_reset_ready(&g_dccrn_stft_arena);
    signal_chain_arena_reset_ready(&g_dccrn_istft_arena);
}

static const ModelConfig dccrn_config =
{
    .input_samples = DCCRN_INPUT_SAMPLES,
    .model_elems = DCCRN_MODEL_ELEMS,
    .output_samples = DCCRN_OUTPUT_SAMPLES,
    .batch_n = 30
};

static const SignalChainOps kDccrnOps =
{
    .name = "DCCRN",
    .config = &dccrn_config,
    .create_pre_graph = dccrn_create_pre_graph,
    .create_post_graph = dccrn_create_post_graph,
    .execute_pre_graph = dccrn_execute_pre_graph,
    .execute_post_graph = dccrn_execute_post_graph,
    .delete_pre_graph = dccrn_delete_pre_graph,
    .delete_post_graph = dccrn_delete_post_graph,
    .get_preprocess_buf = dccrn_get_preprocess_buf,
    .get_postprocess_buf = dccrn_get_postprocess_buf,
    .reset_arenas = dccrn_reset_arenas
};

extern "C" const SignalChainOps *dccrn_get_ops(void)
{
    return &kDccrnOps;
}

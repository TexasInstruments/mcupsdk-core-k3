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
 * GTCRN Signal Chain Implementation
 *
 * Graph-based Time-Frequency Recurrent Network
 * STFT/ISTFT processing for GTCRN model
 */

#include "stft_signal_chain_gtcrn.hpp"
#include "TISP_gtcrn_signal_chain_memory_map.hpp"
#include "model_config.h"
#include "signal_chain_dispatch.h"
#include "signal_chain_arena.hpp"
#include <memory>
#include <tisp.hpp>
#include "TISP_window_gen.hpp"

/* ============================================================================
   STFT / ISTFT arenas
   One-time buffer partition over host-provided IPC memory (see
   signal_chain_arena.hpp). GTCRN has no separate transpose-intermediate
   stage (its MatTrans writes straight into the output buffer), so unlike
   DCCRN there is no "transpose2" role here.
   ============================================================================ */

enum {
    GTCRN_STFT_IDX_TYPECONV = 0,
    GTCRN_STFT_IDX_WINDOW,
    GTCRN_STFT_IDX_STATE,
    GTCRN_STFT_IDX_SCRATCH,
    GTCRN_STFT_IDX_TRANSPOSE1,
    GTCRN_STFT_IDX_OUTPUT,
    GTCRN_STFT_NUM_BUFS
};

enum {
    GTCRN_ISTFT_IDX_TYPECONV = 0,
    GTCRN_ISTFT_IDX_WINDOW,
    GTCRN_ISTFT_IDX_OLA,
    GTCRN_ISTFT_IDX_SCRATCH,
    GTCRN_ISTFT_IDX_TRANSPOSE1,
    GTCRN_ISTFT_IDX_OUTPUT,
    GTCRN_ISTFT_NUM_BUFS
};

/* Order must match the GTCRN_STFT_IDX_* enum above. */
static const ArenaBufferSpec kGtcrnStftSpecs[GTCRN_STFT_NUM_BUFS] = {
    {"gtcrn_stft_typeconv",   (uint32_t)(GTCRN_INPUT_SAMPLES * GTCRN_NUM_CHANNELS * sizeof(float))},
    {"gtcrn_stft_window",     (uint32_t)(GTCRN_FFT_SIZE * sizeof(float))},
    {"gtcrn_stft_state",      (uint32_t)GTCRN_STFT_STATE_BYTES},
    {"gtcrn_stft_scratch",    (uint32_t)(GTCRN_STFT_SCRATCH_ELEMS * sizeof(float))},
    {"gtcrn_stft_transpose1", (uint32_t)(GTCRN_SPEC_ELEMS * GTCRN_NUM_CHANNELS * sizeof(float))},
    {"gtcrn_stft_output",     (uint32_t)(GTCRN_MODEL_ELEMS * GTCRN_NUM_CHANNELS * sizeof(float))},
};

/* Order must match the GTCRN_ISTFT_IDX_* enum above. */
static const ArenaBufferSpec kGtcrnIstftSpecs[GTCRN_ISTFT_NUM_BUFS] = {
    {"gtcrn_istft_typeconv",   (uint32_t)(GTCRN_INPUT_SAMPLES * GTCRN_NUM_CHANNELS * sizeof(float))},
    {"gtcrn_istft_window",     (uint32_t)(GTCRN_FFT_SIZE * sizeof(float))},
    {"gtcrn_istft_ola",        (uint32_t)GTCRN_ISTFT_OLA_BYTES},
    {"gtcrn_istft_scratch",    (uint32_t)(GTCRN_ISTFT_SCRATCH_ELEMS * sizeof(float))},
    {"gtcrn_istft_transpose1", (uint32_t)(GTCRN_SPEC_ELEMS * GTCRN_NUM_CHANNELS * sizeof(float))},
    {"gtcrn_istft_output",     (uint32_t)(GTCRN_OUTPUT_SAMPLES * GTCRN_NUM_CHANNELS * sizeof(int16_t))},
};

static SignalChainArenaState g_gtcrn_stft_arena;
static SignalChainArenaState g_gtcrn_istft_arena;

#define GTCRN_STFT_BUF(idx, type)  ((type *)g_gtcrn_stft_arena.buffers[idx].addr)
#define GTCRN_ISTFT_BUF(idx, type) ((type *)g_gtcrn_istft_arena.buffers[idx].addr)

/* STFT-side (create_pre_graph / execute_pre_graph) address macros */
#define TYPECONV_OUT_ADDR    GTCRN_STFT_BUF(GTCRN_STFT_IDX_TYPECONV, float)
#define WINDOW_ADDR          GTCRN_STFT_BUF(GTCRN_STFT_IDX_WINDOW, float)
#define STFT_STATE_ADDR      GTCRN_STFT_BUF(GTCRN_STFT_IDX_STATE, float)
#define STFT_SCRATCH_ADDR    GTCRN_STFT_BUF(GTCRN_STFT_IDX_SCRATCH, float)
#define STFT_ISTFT_OUT_ADDR  GTCRN_STFT_BUF(GTCRN_STFT_IDX_TRANSPOSE1, float)
// #define GTCRN_STFT_OUTPUT_ADDR GTCRN_STFT_BUF(GTCRN_STFT_IDX_OUTPUT, float)

/* ISTFT-side (create_post_graph / execute_post_graph) address macros --
 * independent copies, never the same underlying memory as the STFT-side ones. */
#define ISTFT_TYPECONV_OUT_ADDR GTCRN_ISTFT_BUF(GTCRN_ISTFT_IDX_TYPECONV, float)
#define ISTFT_WINDOW_ADDR       GTCRN_ISTFT_BUF(GTCRN_ISTFT_IDX_WINDOW, float)
#define ISTFT_OLA_ADDR          GTCRN_ISTFT_BUF(GTCRN_ISTFT_IDX_OLA, float)
#define ISTFT_SCRATCH_ADDR      GTCRN_ISTFT_BUF(GTCRN_ISTFT_IDX_SCRATCH, float)
#define ISTFT_STFT_OUT_ADDR     GTCRN_ISTFT_BUF(GTCRN_ISTFT_IDX_TRANSPOSE1, float)
#define GTCRN_ISTFT_OUTPUT_ADDR GTCRN_ISTFT_BUF(GTCRN_ISTFT_IDX_OUTPUT, int16_t)

/* ============================================================================
   GTCRN Signal Chain Implementation
   ============================================================================ */

void *StftSignalChainGTCRN::create_pre_graph(int16_t *input_addr)
{
    if (!signal_chain_arena_ensure(&g_gtcrn_stft_arena, kGtcrnStftSpecs, GTCRN_STFT_NUM_BUFS, "STFT")) {
        return NULL;
    }

    TISP::ErrorCtxt errorCtx;
    TISP::WindowType winType = static_cast<TISP::WindowType>(GTCRN_WINDOW_TYPE);
    TISP::WindowAlign winAlign = static_cast<TISP::WindowAlign>(GTCRN_WINDOW_ALIGN);

    TISP::windowGen<float>(WINDOW_ADDR, GTCRN_FFT_SIZE, GTCRN_WINDOW_LENGTH,
                          winType, (GTCRN_WINDOW_PERIODIC != 0), winAlign);
    memset(STFT_STATE_ADDR, 0, GTCRN_STFT_STATE_BYTES);

    auto preVec = new TISP::opVec();

    if (errorCtx.isSuccess()) {
        auto k0 = std::make_unique<TISP::AUDIOLIB::TypeConversion<int16_t, float>>(
            input_addr, TYPECONV_OUT_ADDR, GTCRN_NUM_CHANNELS, GTCRN_INPUT_SAMPLES,
            GTCRN_NUM_CHANNELS * sizeof(int16_t), GTCRN_NUM_CHANNELS * sizeof(float),
            GTCRN_IS_INTERLEAVED, "TypeConversion (i16->f32)", 0, errorCtx);
        if (errorCtx.isSuccess()) preVec->push_back(std::move(k0));
    }

    if (errorCtx.isSuccess()) {
        auto k1 = std::make_unique<TISP::AUDIOLIB::Stft<float>>(
            TYPECONV_OUT_ADDR, STFT_ISTFT_OUT_ADDR, WINDOW_ADDR, STFT_STATE_ADDR,
            STFT_SCRATCH_ADDR, GTCRN_FFT_SIZE, GTCRN_HOP_SIZE, GTCRN_NUM_CHANNELS,
            GTCRN_INPUT_SAMPLES, (GTCRN_ONESIDED != 0), "Stft", 1, errorCtx);
        if (errorCtx.isSuccess()) preVec->push_back(std::move(k1));
    }

    if (!errorCtx.isSuccess() || preVec->size() != 2U) {
        delete preVec;
        return NULL;
    }

    return preVec;
}

void *StftSignalChainGTCRN::create_post_graph(float *model_out)
{
    if (!signal_chain_arena_ensure(&g_gtcrn_istft_arena, kGtcrnIstftSpecs, GTCRN_ISTFT_NUM_BUFS, "ISTFT")) {
        return NULL;
    }

    TISP::ErrorCtxt errorCtx;
    TISP::WindowType winType = static_cast<TISP::WindowType>(GTCRN_WINDOW_TYPE);
    TISP::WindowAlign winAlign = static_cast<TISP::WindowAlign>(GTCRN_WINDOW_ALIGN);

    TISP::windowGen<float>(ISTFT_WINDOW_ADDR, GTCRN_FFT_SIZE, GTCRN_WINDOW_LENGTH,
                          winType, (GTCRN_WINDOW_PERIODIC != 0), winAlign);
    memset(ISTFT_OLA_ADDR, 0, GTCRN_ISTFT_OLA_BYTES);

    auto postVec = new TISP::opVec();

    if (errorCtx.isSuccess()) {
        auto k2 = std::make_unique<TISP::AUDIOLIB::Istft<float>>(
            model_out, ISTFT_TYPECONV_OUT_ADDR, ISTFT_WINDOW_ADDR, ISTFT_OLA_ADDR,
            ISTFT_SCRATCH_ADDR, GTCRN_FFT_SIZE, GTCRN_HOP_SIZE, GTCRN_NUM_CHANNELS,
            GTCRN_NUM_WINDOWS, (GTCRN_ONESIDED != 0), "Istft", 2, errorCtx);
        if (errorCtx.isSuccess()) postVec->push_back(std::move(k2));
    }

    if (errorCtx.isSuccess()) {
        auto k3 = std::make_unique<TISP::AUDIOLIB::TypeConversion<float, int16_t>>(
            ISTFT_TYPECONV_OUT_ADDR, GTCRN_ISTFT_OUTPUT_ADDR, GTCRN_NUM_CHANNELS, GTCRN_OUTPUT_SAMPLES,
            GTCRN_NUM_CHANNELS * sizeof(float), GTCRN_NUM_CHANNELS * sizeof(int16_t),
            GTCRN_IS_INTERLEAVED, "TypeConversion (f32->i16)", 3, errorCtx);
        if (errorCtx.isSuccess()) postVec->push_back(std::move(k3));
    }

    if (!errorCtx.isSuccess() || postVec->size() != 2U) {
        delete postVec;
        return NULL;
    }

    return postVec;
}

int32_t StftSignalChainGTCRN::execute_pre_graph(void *pre_graph, int16_t *input_addr)
{
    TISP::opVec *graph = static_cast<TISP::opVec *>(pre_graph);
    if (graph == NULL || graph->size() == 0U) return -1;
    TISP::SetAddr_t     kAddr;
    kAddr.src[0]=static_cast<void *>(input_addr);
   (*graph)[0]->setAddr(kAddr,  TISP::kAddrModeIn);
    TISP::execute::graph(graph);
    return 0;
}

int32_t StftSignalChainGTCRN::execute_post_graph(void *post_graph, float *input_addr)
{
    TISP::opVec *graph = static_cast<TISP::opVec *>(post_graph);
    if (graph == NULL || graph->size() == 0U) return -1;
    TISP::SetAddr_t     kAddr;
    kAddr.src[0]=static_cast<void *>(input_addr);
    (*graph)[0]->setAddr(kAddr,  TISP::kAddrModeIn);
    TISP::execute::graph(graph);
    return 0;
}

void StftSignalChainGTCRN::delete_pre_graph(void *pre_graph)
{
    if (pre_graph != NULL) delete static_cast<TISP::opVec *>(pre_graph);
}

void StftSignalChainGTCRN::delete_post_graph(void *post_graph)
{
    if (post_graph != NULL) delete static_cast<TISP::opVec *>(post_graph);
}

/* ============================================================================
   Runtime Dispatch: ops table for this model (self-contained in this TU so
   the static arena state / memory-map buffers never need to be visible
   outside this translation unit)
   ============================================================================ */

static StftSignalChainGTCRN g_gtcrn_impl;

static void *gtcrn_create_pre_graph(int16_t *input_addr) {
    return g_gtcrn_impl.create_pre_graph(input_addr);
}
static void *gtcrn_create_post_graph(float *model_out) {
    return g_gtcrn_impl.create_post_graph(model_out);
}
static int32_t gtcrn_execute_pre_graph(void *graph, int16_t *input_addr) {
    return g_gtcrn_impl.execute_pre_graph(graph, input_addr);
}
static int32_t gtcrn_execute_post_graph(void *graph, float *input_addr) {
    return g_gtcrn_impl.execute_post_graph(graph, input_addr);
}
static void gtcrn_delete_pre_graph(void *graph) {
    g_gtcrn_impl.delete_pre_graph(graph);
}
static void gtcrn_delete_post_graph(void *graph) {
    g_gtcrn_impl.delete_post_graph(graph);
}
static float *gtcrn_get_preprocess_buf(void) {
    return STFT_ISTFT_OUT_ADDR;
}
static int16_t *gtcrn_get_postprocess_buf(void) {
    return GTCRN_ISTFT_OUTPUT_ADDR;
}

static void gtcrn_reset_arenas(void) {
    /* Reset both arenas so the next GTCRN activation re-partitions its
     * workspace from the new ARM-provided buffer. */
    signal_chain_arena_reset_ready(&g_gtcrn_stft_arena);
    signal_chain_arena_reset_ready(&g_gtcrn_istft_arena);
}

static const ModelConfig gtcrn_config = {
    .input_samples = GTCRN_INPUT_SAMPLES,
    .model_elems = GTCRN_MODEL_ELEMS,
    .output_samples = GTCRN_OUTPUT_SAMPLES,
    .batch_n = 30
};

static const SignalChainOps kGtcrnOps = {
    .name = "GTCRN",
    .config = &gtcrn_config,
    .create_pre_graph = gtcrn_create_pre_graph,
    .create_post_graph = gtcrn_create_post_graph,
    .execute_pre_graph = gtcrn_execute_pre_graph,
    .execute_post_graph = gtcrn_execute_post_graph,
    .delete_pre_graph = gtcrn_delete_pre_graph,
    .delete_post_graph = gtcrn_delete_post_graph,
    .get_preprocess_buf = gtcrn_get_preprocess_buf,
    .get_postprocess_buf = gtcrn_get_postprocess_buf,
    .reset_arenas = gtcrn_reset_arenas
};

extern "C" const SignalChainOps *gtcrn_get_ops(void) {
    return &kGtcrnOps;
}

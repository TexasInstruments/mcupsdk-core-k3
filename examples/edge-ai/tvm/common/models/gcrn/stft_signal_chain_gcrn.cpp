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
 * GCRN Signal Chain Implementation
 *
 * Graph-based Complex Recurrent Network
 * STFT/ISTFT processing for GCRN model
 */

#include "stft_signal_chain_gcrn.hpp"
#include "TISP_gcrn_signal_chain_memory_map.hpp"
#include "model_config.h"
#include "signal_chain_dispatch.h"
#include "signal_chain_arena.hpp"
#include <tisp.hpp>
#include <memory>
#include <kernel/dpl/DebugP.h>
#include "TISP_window_gen.hpp"

/* ============================================================================
   STFT / ISTFT arenas
   One-time buffer partition over host-provided IPC memory (see
   signal_chain_arena.hpp). GCRN has no transpose-intermediate stage at all
   (its Stft node writes straight into the output buffer) and already keeps
   analysis/synthesis windows as two distinct roles, so the only buffer that
   needs duplicating for hard STFT/ISTFT separation is typeconv.
   ============================================================================ */

enum {
    GCRN_STFT_IDX_TYPECONV = 0,
    GCRN_STFT_IDX_WINDOW,
    GCRN_STFT_IDX_STATE,
    GCRN_STFT_IDX_SCRATCH,
    GCRN_STFT_IDX_OUTPUT,
    GCRN_STFT_NUM_BUFS
};

enum {
    GCRN_ISTFT_IDX_TYPECONV = 0,
    GCRN_ISTFT_IDX_WINDOW,
    GCRN_ISTFT_IDX_OLA,
    GCRN_ISTFT_IDX_SCRATCH,
    GCRN_ISTFT_IDX_OUTPUT,
    GCRN_ISTFT_NUM_BUFS
};

/* Order must match the GCRN_STFT_IDX_* enum above. */
static const ArenaBufferSpec kGcrnStftSpecs[GCRN_STFT_NUM_BUFS] = {
    {"gcrn_stft_typeconv", (uint32_t)(GCRN_INPUT_SAMPLES * GCRN_NUM_CHANNELS * sizeof(float))},
    {"gcrn_stft_window",   (uint32_t)(GCRN_FFT_SIZE * sizeof(float))},
    {"gcrn_stft_state",    (uint32_t)GCRN_STFT_STATE_BYTES},
    {"gcrn_stft_scratch",  (uint32_t)(GCRN_STFT_SCRATCH_ELEMS * sizeof(float))},
    {"gcrn_stft_output",   (uint32_t)(GCRN_MODEL_ELEMS * GCRN_NUM_CHANNELS * sizeof(float))},
};

/* Order must match the GCRN_ISTFT_IDX_* enum above. */
static const ArenaBufferSpec kGcrnIstftSpecs[GCRN_ISTFT_NUM_BUFS] = {
    {"gcrn_istft_typeconv", (uint32_t)(GCRN_INPUT_SAMPLES * GCRN_NUM_CHANNELS * sizeof(float))},
    {"gcrn_istft_window",   (uint32_t)(GCRN_FFT_SIZE * sizeof(float))},
    {"gcrn_istft_ola",      (uint32_t)GCRN_ISTFT_OLA_BYTES},
    {"gcrn_istft_scratch",  (uint32_t)(GCRN_ISTFT_SCRATCH_ELEMS * sizeof(float))},
    {"gcrn_istft_output",   (uint32_t)(GCRN_OUTPUT_SAMPLES * GCRN_NUM_CHANNELS * sizeof(int16_t))},
};

static SignalChainArenaState g_gcrn_stft_arena;
static SignalChainArenaState g_gcrn_istft_arena;

#define GCRN_STFT_BUF(idx, type)  ((type *)g_gcrn_stft_arena.buffers[idx].addr)
#define GCRN_ISTFT_BUF(idx, type) ((type *)g_gcrn_istft_arena.buffers[idx].addr)

/* STFT-side (create_pre_graph / execute_pre_graph) address macros */
#define TYPECONV_OUT_ADDR    GCRN_STFT_BUF(GCRN_STFT_IDX_TYPECONV, float)
#define STFT_WINDOW_ADDR     GCRN_STFT_BUF(GCRN_STFT_IDX_WINDOW, float)
#define STFT_STATE_ADDR      GCRN_STFT_BUF(GCRN_STFT_IDX_STATE, float)
#define STFT_SCRATCH_ADDR    GCRN_STFT_BUF(GCRN_STFT_IDX_SCRATCH, float)
#define GCRN_STFT_OUTPUT_ADDR GCRN_STFT_BUF(GCRN_STFT_IDX_OUTPUT, float)

/* ISTFT-side (create_post_graph / execute_post_graph) address macros --
 * independent copies, never the same underlying memory as the STFT-side ones. */
#define ISTFT_TYPECONV_OUT_ADDR GCRN_ISTFT_BUF(GCRN_ISTFT_IDX_TYPECONV, float)
#define ISTFT_WINDOW_ADDR       GCRN_ISTFT_BUF(GCRN_ISTFT_IDX_WINDOW, float)
#define ISTFT_OLA_ADDR          GCRN_ISTFT_BUF(GCRN_ISTFT_IDX_OLA, float)
#define ISTFT_SCRATCH_ADDR      GCRN_ISTFT_BUF(GCRN_ISTFT_IDX_SCRATCH, float)
#define GCRN_ISTFT_OUTPUT_ADDR  GCRN_ISTFT_BUF(GCRN_ISTFT_IDX_OUTPUT, int16_t)

/* ======================== Graph creation (pre / post) ======================== */

/* Build the pre-processing (analysis) graph: i16 in -> ... -> gModelIn (2,T,F), and prepare its
 * symmetric-Hamming analysis window + STFT overlap state.  Returns the new opVec (empty/partial
 * if errorCtx already failed); never NULL.  fftSize=320 is non-pow2, supported via non-pow2 RFFT
 * in fftlib. */
void *StftSignalChainGCRN::create_pre_graph(int16_t *input_addr)
{
   if (!signal_chain_arena_ensure(&g_gcrn_stft_arena, kGcrnStftSpecs, GCRN_STFT_NUM_BUFS, "STFT")) {
      return NULL;
   }

   TISP::ErrorCtxt errorCtx;
   /* analysis (STFT) window: symmetric Hamming */
   TISP::WindowType  winType  = static_cast<TISP::WindowType>(GCRN_WINDOW_TYPE);
   TISP::WindowAlign winAlign = static_cast<TISP::WindowAlign>(GCRN_WINDOW_ALIGN);
   TISP::windowGen<float>(STFT_WINDOW_ADDR, GCRN_FFT_SIZE, GCRN_WINDOW_LENGTH, winType,
                          (GCRN_WINDOW_PERIODIC != 0), winAlign);
   memset(STFT_STATE_ADDR, 0, GCRN_STFT_STATE_BYTES);

   auto preVec = new TISP::opVec();

   /* 1. TypeConversion int16 -> float */
   if (errorCtx.isSuccess()) {
      auto k0 = std::make_unique<TISP::AUDIOLIB::TypeConversion<int16_t, float>>(
          input_addr, TYPECONV_OUT_ADDR, GCRN_NUM_CHANNELS, GCRN_INPUT_SAMPLES,
          GCRN_NUM_CHANNELS * sizeof(int16_t), GCRN_NUM_CHANNELS * sizeof(float), GCRN_IS_INTERLEAVED,
          "TypeConversion (i16->f32)", 0, errorCtx);
      if (errorCtx.isSuccess()) { preVec->push_back(std::move(k0)); }
      else { DebugP_log("[DSP] Error: Node 0 TypeConversion(i16->f32): %s\r\n", errorCtx.getMessage()); }
   }

   /* 2. STFT (writes gStftOut, frame-major [T x 322]) -- fftSize=320 is non-pow2 */
   if (errorCtx.isSuccess()) {
      auto k1 = std::make_unique<TISP::AUDIOLIB::Stft<float>>(
          TYPECONV_OUT_ADDR, GCRN_STFT_OUTPUT_ADDR, STFT_WINDOW_ADDR, STFT_STATE_ADDR, STFT_SCRATCH_ADDR,
          GCRN_FFT_SIZE, GCRN_HOP_SIZE, GCRN_NUM_CHANNELS, GCRN_INPUT_SAMPLES, (GCRN_ONESIDED != 0),
          "Stft", 1, errorCtx);
      if (errorCtx.isSuccess()) { preVec->push_back(std::move(k1)); }
      else { DebugP_log("[DSP] Error: Node 1 Stft (fftSize=320): %s\r\n", errorCtx.getMessage()); }
   }
    if (!errorCtx.isSuccess() || preVec->size() != 2U) {
        delete preVec;
        return NULL;
    }

   return preVec;
}

/* Build the post-processing (synthesis) graph: gModelOut (2,T,F) -> ... -> i16 out, and prepare
 * its synthesis window + ISTFT overlap-add state (and clear the model output buffer).  Returns
 * the new opVec (empty/partial if errorCtx already failed); never NULL. */
void *StftSignalChainGCRN::create_post_graph(float *model_out)
{
   if (!signal_chain_arena_ensure(&g_gcrn_istft_arena, kGcrnIstftSpecs, GCRN_ISTFT_NUM_BUFS, "ISTFT")) {
      return NULL;
   }

   TISP::ErrorCtxt errorCtx;
   /* synthesis (ISTFT) window: its own buffer, same symmetric Hamming as the analysis window.
    * The TISP Istft computes OLA(f*w)/OLA(w^2), so an analysis-matched window makes it exactly
    * librosa.istft -- the reconstruction validated in gcrn_target_demo.ipynb.  The periodic flag
    * MUST track the analysis side: a periodic window here would normalize by OLA(periodic w^2)
    * while the frames were analyzed with the symmetric one. */
   TISP::windowGen<float>(ISTFT_WINDOW_ADDR, GCRN_FFT_SIZE, GCRN_WINDOW_LENGTH,
                          static_cast<TISP::WindowType>(GCRN_SYNTH_WINDOW_TYPE),
                          (GCRN_WINDOW_PERIODIC != 0), static_cast<TISP::WindowAlign>(GCRN_WINDOW_ALIGN));
   memset(ISTFT_OLA_ADDR, 0, GCRN_ISTFT_OLA_BYTES);
   auto postVec = new TISP::opVec();


   /* 3. ISTFT (reads gIstftIn, frame-major) -- fftSize=320 is non-pow2 */
   if (errorCtx.isSuccess()) {
      auto k2 = std::make_unique<TISP::AUDIOLIB::Istft<float>>(
          model_out, ISTFT_TYPECONV_OUT_ADDR, ISTFT_WINDOW_ADDR, ISTFT_OLA_ADDR, ISTFT_SCRATCH_ADDR,
          GCRN_FFT_SIZE, GCRN_HOP_SIZE, GCRN_NUM_CHANNELS, GCRN_NUM_WINDOWS, (GCRN_ONESIDED != 0),
          "Istft", 4, errorCtx);
      if (errorCtx.isSuccess()) { postVec->push_back(std::move(k2)); }
      else { DebugP_log("[DSP] Error: Node 4 Istft (fftSize=320): %s\r\n", errorCtx.getMessage()); }
   }

   /* 4. TypeConversion float -> int16 */
   if (errorCtx.isSuccess()) {
      auto k3 = std::make_unique<TISP::AUDIOLIB::TypeConversion<float, int16_t>>(
          ISTFT_TYPECONV_OUT_ADDR, GCRN_ISTFT_OUTPUT_ADDR, GCRN_NUM_CHANNELS, GCRN_OUTPUT_SAMPLES,
          GCRN_NUM_CHANNELS * sizeof(float), GCRN_NUM_CHANNELS * sizeof(int16_t), GCRN_IS_INTERLEAVED,
          "TypeConversion (f32->i16)", 5, errorCtx);
      if (errorCtx.isSuccess()) { postVec->push_back(std::move(k3)); }
      else { DebugP_log("[DSP] Error: Node 5 TypeConversion(f32->i16): %s\r\n", errorCtx.getMessage()); }
   }
    if (!errorCtx.isSuccess() || postVec->size() != 2U) {
        delete postVec;
        return NULL;
    }

   return postVec;
}

/* ======================== Graph execution (pre / post) ======================== */

/* Run the pre-processing (analysis) graph for ALL blocks: per block load the i16 input, execute
 * the analysis graph, and accumulate its gModelIn output into gModelInCapture (the full-spectrum
 * model input).  The STFT overlap state streams across blocks. */
int32_t StftSignalChainGCRN::execute_pre_graph(void *pre_graph, int16_t *input_addr)
{
   TISP::opVec *graph=static_cast<TISP::opVec *>(pre_graph);
   if (graph == NULL || graph->size() == 0U) return -1;
    TISP::SetAddr_t     kAddr;
    kAddr.src[0]=static_cast<void *>(input_addr);
   (*graph)[0]->setAddr(kAddr,  TISP::kAddrModeIn);
    TISP::execute::graph(graph);
    return 0;
}

/* Run the post-processing (synthesis) graph for ALL blocks: per block stage the model output for
 * that block into gModelOut, rebind the i16 output to the block's slot, execute the synthesis
 * graph, and capture the ISTFT float output.  The ISTFT OLA state streams across blocks. */
int32_t StftSignalChainGCRN::execute_post_graph(void *post_graph,float *input_addr)
{

    TISP::opVec *graph=static_cast<TISP::opVec *>(post_graph);
   if (graph == NULL || graph->size() == 0U) return -1;
    TISP::SetAddr_t     kAddr;
    kAddr.src[0]=static_cast<void *>(input_addr);
    (*graph)[0]->setAddr(kAddr,  TISP::kAddrModeIn);
    TISP::execute::graph(graph);
    return 0;
}

void StftSignalChainGCRN::delete_pre_graph(void *pre_graph)
{
    if (pre_graph != NULL) delete static_cast<TISP::opVec *>(pre_graph);
}

void StftSignalChainGCRN::delete_post_graph(void *post_graph)
{
    if (post_graph != NULL) delete static_cast<TISP::opVec *>(post_graph);
}

/* ============================================================================
   Runtime Dispatch: ops table for this model (self-contained in this TU so
   the static arena state / memory-map buffers never need to be visible
   outside this translation unit). GCRN additionally exposes the
   deinterleave/interleave operations, which no other model supports.
   ============================================================================ */

static StftSignalChainGCRN g_gcrn_impl;

static void *gcrn_create_pre_graph(int16_t *input_addr) {
    return g_gcrn_impl.create_pre_graph(input_addr);
}
static void *gcrn_create_post_graph(float *model_out) {
    return g_gcrn_impl.create_post_graph(model_out);
}
static int32_t gcrn_execute_pre_graph(void *graph, int16_t *input_addr) {
    return g_gcrn_impl.execute_pre_graph(graph, input_addr);
}
static int32_t gcrn_execute_post_graph(void *graph, float *input_addr) {
    return g_gcrn_impl.execute_post_graph(graph, input_addr);
}
static void gcrn_delete_pre_graph(void *graph) {
    g_gcrn_impl.delete_pre_graph(graph);
}
static void gcrn_delete_post_graph(void *graph) {
    g_gcrn_impl.delete_post_graph(graph);
}
static float *gcrn_get_preprocess_buf(void) {
    return GCRN_STFT_OUTPUT_ADDR;
}
static int16_t *gcrn_get_postprocess_buf(void) {
    return GCRN_ISTFT_OUTPUT_ADDR;
}

static void gcrn_reset_arenas(void) {
    /* Reset both arenas so the next GCRN activation re-partitions its
     * workspace from the new ARM-provided buffer. */
    signal_chain_arena_reset_ready(&g_gcrn_stft_arena);
    signal_chain_arena_reset_ready(&g_gcrn_istft_arena);
}

static const ModelConfig gcrn_config = {
    .input_samples = GCRN_INPUT_SAMPLES,
    .model_elems = GCRN_MODEL_ELEMS,
    .output_samples = GCRN_OUTPUT_SAMPLES,
    .batch_n = 64
};

static const SignalChainOps kGcrnOps = {
    .name = "GCRN",
    .config = &gcrn_config,
    .create_pre_graph = gcrn_create_pre_graph,
    .create_post_graph = gcrn_create_post_graph,
    .execute_pre_graph = gcrn_execute_pre_graph,
    .execute_post_graph = gcrn_execute_post_graph,
    .delete_pre_graph = gcrn_delete_pre_graph,
    .delete_post_graph = gcrn_delete_post_graph,
    .get_preprocess_buf = gcrn_get_preprocess_buf,
    .get_postprocess_buf = gcrn_get_postprocess_buf,
    .reset_arenas = gcrn_reset_arenas
};

extern "C" const SignalChainOps *gcrn_get_ops(void) {
    return &kGcrnOps;
}

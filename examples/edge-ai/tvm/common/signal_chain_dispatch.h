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
 * Signal Chain Runtime Dispatcher
 *
 * Maps ModelId to the appropriate signal-chain implementation
 * (DCCRN, GTCRN, GCRN, VGGish, YAMNet) at runtime via function-pointer
 * tables. All implementations are always compiled in; the active model is
 * selected by the IPC message, not the Makefile.
 */

#ifndef SIGNAL_CHAIN_DISPATCH_H
#define SIGNAL_CHAIN_DISPATCH_H

#include <stdint.h>
#include "model_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
   Model Configuration (replaces compile-time STFT_* macros)
   ============================================================================ */

typedef struct
{
    uint32_t input_samples;   /* STFT_INPUT_SAMPLES equivalent per model */
    uint32_t model_elems;     /* STFT_MODEL_ELEMS equivalent per model */
    uint32_t output_samples;  /* STFT_OUTPUT_SAMPLES equivalent per model */
    uint32_t batch_n;         /* max frames per batch */
} ModelConfig;

/* ============================================================================
   Signal Chain Operations Table
   ============================================================================ */

typedef struct
{
    const char         *name;
    const ModelConfig  *config;

    /* Core STFT/ISTFT operations.
     * create_pre_graph/create_post_graph run exactly once per model activation
     * (cached by the caller) -- arena partitioning uses the fixed DDR memory region
     * (see signal_chain_arena.hpp). */
    void    *(*create_pre_graph)(int16_t *input_addr);
    void    *(*create_post_graph)(float *model_out);
    int32_t  (*execute_pre_graph)(void *graph, int16_t *input_addr);
    int32_t  (*execute_post_graph)(void *graph, float *input_addr);
    void     (*delete_pre_graph)(void *graph);
    void     (*delete_post_graph)(void *graph);

    /* Buffer accessors */
    float   *(*get_preprocess_buf)(void);
    int16_t *(*get_postprocess_buf)(void);

    /* Model deactivation: reset STFT/ISTFT arena ready flags so the next
     * activation of this model re-partitions its workspace from the new
     * ARM-provided buffer (fixes stale addresses on model round-trip).
     * Called by stft_deinit() while this model is still the active one. */
    void     (*reset_arenas)(void);
} SignalChainOps;

/* ============================================================================
   Dispatcher API
   ============================================================================ */

/**
 * Get the operations table for a given model ID.
 * @param id  A valid ModelId (see model_config.h: MODEL_DCCRN=0 .. MODEL_YAMNET=4)
 * @return    Pointer to the SignalChainOps table, or NULL if id is invalid or
 *            out of range
 */
const SignalChainOps *signal_chain_get_ops(ModelId id);

/**
 * Set the single process-wide active model. There is exactly one active
 * model at a time (this firmware processes one IPC message at a time via a
 * single service task loop), shared by every StftSignalChain instance.
 * @param id  ModelId to activate
 * @return    1 on success, 0 if id is invalid (prior active model unchanged)
 */
int32_t signal_chain_set_active(ModelId id);

/**
 * Get the currently active model.
 * @return  The active ModelId, or MODEL_COUNT if none has been selected yet.
 */
ModelId signal_chain_get_active(void);

#ifdef __cplusplus
}
#endif

#endif /* SIGNAL_CHAIN_DISPATCH_H */

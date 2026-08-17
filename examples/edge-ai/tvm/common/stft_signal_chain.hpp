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
 * STFT Signal Chain Class Header - Runtime Model Selection
 *
 * Provides a stable public interface to all signal chains
 * (DCCRN, GTCRN, GCRN, VGGish, YAMNet)
 * for core STFT/ISTFT processing. The active model is a single process-wide
 * selection (see signal_chain_dispatch.h); every StftSignalChain instance
 * forwards to whichever model is currently active, so multiple instances
 * (e.g. one per handler file) always agree on which model is live.
 * This class itself holds no per-instance state.
 *
 * NOTE: Deinterleave/Interleave and MatTrans are separate, model-agnostic code
 * paths (different IPC message type, C7X_UTILS_MSG_ANALYZE). Use
 * DeinterleaveSignalChain / MatTransSignalChain directly; they are not part
 * of this interface.
 *
 * Usage pattern:
 *   1. select_model(MODEL_GCRN)         - pick active model (process-wide)
 *   2. create_pre_graph(input_addr)     - called on first message per activation
 *   3. execute_pre_graph(graph, ...)    - called per message in loop
 *   4. delete_pre_graph(graph)          - called on shutdown / deactivation
 */

#ifndef STFT_SIGNAL_CHAIN_HPP
#define STFT_SIGNAL_CHAIN_HPP

#include <stdint.h>
#include <stddef.h>
#include "model_config.h"
#include "signal_chain_dispatch.h"

#ifdef __cplusplus
extern "C" {
#endif

class StftSignalChain
{
public:
    /**
     * Select the active model at runtime.
     * Returns false and leaves the active model unchanged if the id is invalid.
     */
    bool select_model(ModelId id);

    /**
     * Get the configuration (input/output sizes, batch limit) of the active model.
     * Returns NULL if no model is currently selected.
     */
    const ModelConfig *config() const;

    /**
     * Create pre-processing (STFT analysis) graph.
     * Called on the first STFT_ANALYZE message per model activation.
     * The model's STFT arena is partitioned over the fixed DDR memory region
     * (see signal_chain_arena.hpp). Ignored on every later call for the same
     * activation. After a model switch and re-activation the arena is reset
     * (see reset_arenas()), so this is called again on the next message.
     *
     * @param input_addr Input buffer address (for graph initialization)
     * @return Pre-graph pointer (opaque handle), NULL on error
     */
    void *create_pre_graph(int16_t *input_addr);

    /**
     * Create post-processing (ISTFT synthesis) graph
     * Called on first ISTFT_SYNTHESIZE message. Same one-time-only arena 
     * partitioning over the fixed DDR region, independent ISTFT arena.
     *
     * @param model_out Output buffer address for graph sink node
     * @return Post-graph pointer (opaque handle), NULL on error
     */
    void *create_post_graph(float *model_out);

    /**
     * Execute pre-processing graph (STFT analysis)
     *
     * @param pre_graph  Pre-graph pointer from create_pre_graph()
     * @param input_addr Input buffer address
     * @return 0 on success, <0 on error
     */
    int32_t execute_pre_graph(void *pre_graph, int16_t *input_addr);

    /**
     * Execute post-processing graph (ISTFT synthesis)
     *
     * @param post_graph  Post-graph pointer from create_post_graph()
     * @param input_addr  Input buffer address
     * @return 0 on success, <0 on error
     */
    int32_t execute_post_graph(void *post_graph, float *input_addr);

    /**
     * Delete pre-processing graph (called on shutdown)
     *
     * @param pre_graph Pre-graph pointer from create_pre_graph()
     */
    void delete_pre_graph(void *pre_graph);

    /**
     * Delete post-processing graph (called on shutdown)
     *
     * @param post_graph Post-graph pointer from create_post_graph()
     */
    void delete_post_graph(void *post_graph);

    /**
     * Get the preprocess buffer for the active model.
     * Returns NULL if no model is selected.
     */
    float *get_preprocess_buf();

    /**
     * Get the postprocess buffer for the active model.
     * Returns NULL if no model is selected.
     */
    int16_t *get_postprocess_buf();

    /**
     * Reset the STFT/ISTFT arena ready flags for the currently active model.
     * Must be called during stft_deinit() while the old model is still active,
     * so the next activation of that model re-partitions its workspace from
     * the new ARM-provided buffer instead of reusing stale addresses.
     */
    void reset_arenas();
};

#ifdef __cplusplus
}
#endif

#endif /* STFT_SIGNAL_CHAIN_HPP */

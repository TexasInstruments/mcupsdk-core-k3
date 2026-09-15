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
 * STFT Signal Chain - Runtime Model Selection Implementation
 *
 * Stateless dispatch shim: every call looks up the current process-wide
 * active model (signal_chain_get_active()) and forwards through its ops
 * table. This keeps every StftSignalChain instance in agreement about
 * which model is active, no matter which handler file created it.
 */

#include "stft_signal_chain.hpp"
#include "signal_chain_dispatch.h"
#include <kernel/dpl/DebugP.h>

bool StftSignalChain::select_model(ModelId id)
{
    if (!signal_chain_set_active(id))
    {
        DebugP_log("[STFT] ERROR: Invalid model id: %u\r\n", id);
        return false;
    }
    const SignalChainOps *ops = signal_chain_get_ops(id);
#ifdef SIGNAL_CHAIN_VERBOSE_LOG
    DebugP_log("[STFT] Model selected: %s\r\n", ops->name);
#endif
    return true;
}

const ModelConfig *StftSignalChain::config() const
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    return ops ? ops->config : nullptr;
}

void *StftSignalChain::create_pre_graph(int16_t *input_addr)
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    if (!ops)
    {
        DebugP_log("[STFT] ERROR: No model selected\r\n");
        return nullptr;
    }
    return ops->create_pre_graph(input_addr);
}

void *StftSignalChain::create_post_graph(float *model_out)
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    if (!ops)
    {
        DebugP_log("[STFT] ERROR: No model selected\r\n");
        return nullptr;
    }
    return ops->create_post_graph(model_out);
}

int32_t StftSignalChain::execute_pre_graph(void *pre_graph, int16_t *input_addr)
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    if (!ops)
    {
        DebugP_log("[STFT] ERROR: No model selected\r\n");
        return -1;
    }
    return ops->execute_pre_graph(pre_graph, input_addr);
}

int32_t StftSignalChain::execute_post_graph(void *post_graph, float *input_addr)
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    if (!ops)
    {
        DebugP_log("[STFT] ERROR: No model selected\r\n");
        return -1;
    }
    return ops->execute_post_graph(post_graph, input_addr);
}

void StftSignalChain::delete_pre_graph(void *pre_graph)
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    if (ops)
    {
        ops->delete_pre_graph(pre_graph);
    }
}

void StftSignalChain::delete_post_graph(void *post_graph)
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    if (ops)
    {
        ops->delete_post_graph(post_graph);
    }
}

float *StftSignalChain::get_preprocess_buf()
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    return ops ? ops->get_preprocess_buf() : nullptr;
}

int16_t *StftSignalChain::get_postprocess_buf()
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    return ops ? ops->get_postprocess_buf() : nullptr;
}

void StftSignalChain::reset_arenas()
{
    const SignalChainOps *ops = signal_chain_get_ops(signal_chain_get_active());
    if (ops && ops->reset_arenas)
    {
        ops->reset_arenas();
    }
}

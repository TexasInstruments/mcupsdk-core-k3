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
 * Signal Chain Runtime Dispatcher - Implementation
 *
 * Each model's ops table (trampolines, config, buffer accessors) is built
 * inside that model's own translation unit (see models/<model>/stft_signal_chain_<model>.cpp),
 * where its static buffers and memory-map macros are already safely scoped.
 * This file only maps ModelId -> the corresponding model's ops table, so
 * no per-model header ever needs to be included here (avoiding duplicate
 * static-buffer definitions if multiple memory-map headers were pulled
 * into a single translation unit).
 */

#include "signal_chain_dispatch.h"
#include "model_config.h"

extern "C" const SignalChainOps *dccrn_get_ops(void);
extern "C" const SignalChainOps *gtcrn_get_ops(void);
extern "C" const SignalChainOps *gcrn_get_ops(void);
extern "C" const SignalChainOps *vggish_get_ops(void);
extern "C" const SignalChainOps *yamnet_get_ops(void);

static ModelId g_active_model = MODEL_COUNT;

const SignalChainOps *signal_chain_get_ops(ModelId id)
{
    switch (id) {
        case MODEL_DCCRN:  return dccrn_get_ops();
        case MODEL_GTCRN:  return gtcrn_get_ops();
        case MODEL_GCRN:   return gcrn_get_ops();
        case MODEL_VGGISH: return vggish_get_ops();
        case MODEL_YAMNET: return yamnet_get_ops();
        default:           return nullptr;
    }
}

int32_t signal_chain_set_active(ModelId id)
{
    if (signal_chain_get_ops(id) == nullptr) {
        return 0;
    }
    g_active_model = id;
    return 1;
}

ModelId signal_chain_get_active(void)
{
    return g_active_model;
}

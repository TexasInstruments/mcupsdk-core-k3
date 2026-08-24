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
 * Graph-based Time-Frequency Recurrent Network
 * STFT/ISTFT processing for YAMNET model
 */

#ifndef STFT_SIGNAL_CHAIN_YAMNET_HPP
#define STFT_SIGNAL_CHAIN_YAMNET_HPP

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* YAMNET-specific interface (analysis-only, no synthesis stage) */
class StftSignalChainYAMNET
{
public:
    /* One-time arena initialization on first call; cached thereafter
     * @param input_addr      Input buffer address (for graph initialization)
     * @param input_size      Size in bytes of the actual input sample region at input_addr
     * @param total_size      Size in bytes of the whole host-provided buffer at input_addr
     * @return                Pre-graph pointer (opaque handle), NULL on error
     */
    void *create_pre_graph(int16_t *input_addr);

    /**
     * Execute pre-processing graph (log-mel spectrogram extraction)
     * @param pre_graph       Pre-graph pointer from create_pre_graph()
     * @param input_addr      Input buffer address (raw i16 audio samples)
     * @return                0 on success, <0 on error
     */
    int32_t execute_pre_graph(void *pre_graph, int16_t *input_addr);

    /**
     * Delete pre-processing graph (called on shutdown or model change)
     * @param pre_graph       Pre-graph pointer from create_pre_graph()
     */
    void delete_pre_graph(void *pre_graph);

};

#ifdef __cplusplus
}
#endif

#endif /* STFT_SIGNAL_CHAIN_YAMNET_HPP */

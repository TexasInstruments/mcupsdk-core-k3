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
 * Mat Transpose Signal Chain Implementation
 *
 * Graph-based Mat Transpose Signal Chain
 */

#ifndef MATTRANS_SIGNAL_CHAIN_HPP
#define MATTRANS_SIGNAL_CHAIN_HPP

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MatTrans-specific interface */
class MatTransSignalChain
{
public:
    void *create_mattrans_pre_graph(float *input_addr, float *output_addr,
                                        int32_t width, int32_t height, int32_t inpitch, int32_t outpitch);
    void *create_mattrans_post_graph(float *model_out, float *output_addr,
                                       int32_t width, int32_t height, int32_t inpitch, int32_t outpitch);

    int32_t execute_pre_graph(void *pre_graph, float *input_addr);
    int32_t execute_post_graph(void *post_graph, float *input_addr);

    void delete_pre_graph(void *pre_graph);
    void delete_post_graph(void *post_graph);
};

#ifdef __cplusplus
}
#endif

#endif /* MATTRANS_SIGNAL_CHAIN_HPP */


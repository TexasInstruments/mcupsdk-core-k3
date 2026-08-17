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

#include "mattrans_signal_chain.hpp"
#include "model_config.h"
#include <tisp.hpp>
#include <memory>
#include <kernel/dpl/DebugP.h>

/* ======================== Graph creation (pre / post) ======================== */

/* Build the pre-processing graph: To convert whole blocks of stft ouput
 into matrix form for model expected. */


void *MatTransSignalChain::create_mattrans_pre_graph(float *input_addr, float *output_addr,
                                                         int32_t width, int32_t height, int32_t inpitch, int32_t outpitch)
{
   TISP::ErrorCtxt errorCtx;
   auto preVec = new TISP::opVec();
   if (errorCtx.isSuccess()) {
      auto k1 = std::make_unique<TISP::DSPLIB::MatTrans<double>>(
           reinterpret_cast<double *>(input_addr),  reinterpret_cast<double *>(output_addr), width,height,inpitch,outpitch,"MatTrans (re/im split)", 0, errorCtx);
      if (errorCtx.isSuccess()) { preVec->push_back(std::move(k1)); }
      else { DebugP_log("[DSP] Error: Node MatTrans: %s\r\n", errorCtx.getMessage()); }
   }
    if (!errorCtx.isSuccess() || preVec->size() != 1U) {
        delete preVec;
        return NULL;
    }

   return preVec;
}

/* Build the post-processing graph: To convert matrix model output back to matrix form for further processing */
void *MatTransSignalChain::create_mattrans_post_graph(float *model_out,float *output_addr, int32_t width, int32_t height, int32_t inpitch, int32_t outpitch)
{
   TISP::ErrorCtxt errorCtx;
   auto postVec = new TISP::opVec();
   if (errorCtx.isSuccess()) {
      auto k2 = std::make_unique<TISP::DSPLIB::MatTrans<double>>(
          reinterpret_cast<double *>(model_out), reinterpret_cast<double *>(output_addr), width, height, inpitch, outpitch, "MatTrans (re/im merge)", 1, errorCtx);
      if (errorCtx.isSuccess()) { postVec->push_back(std::move(k2)); }
      else { DebugP_log("[DSP] Error: Node MatTrans: %s\r\n", errorCtx.getMessage()); }
   }
    if (!errorCtx.isSuccess() || postVec->size() != 1U) {
        delete postVec;
        return NULL;
    }

   return postVec;
}

/* ======================== Graph execution (pre / post) ======================== */
int32_t MatTransSignalChain::execute_pre_graph(void *pre_graph, float *input_addr)
{
   TISP::opVec *graph=static_cast<TISP::opVec *>(pre_graph);
   if (graph == NULL || graph->size() == 0U) return -1;
    TISP::SetAddr_t     kAddr;
    kAddr.src[0]=static_cast<void *>(input_addr);
   (*graph)[0]->setAddr(kAddr,  TISP::kAddrModeIn);
    TISP::execute::graph(graph);
    return 0;
}
int32_t MatTransSignalChain::execute_post_graph(void *post_graph,float *input_addr)
{

    TISP::opVec *graph=static_cast<TISP::opVec *>(post_graph);
   if (graph == NULL || graph->size() == 0U) return -1;
    TISP::SetAddr_t     kAddr;
    kAddr.src[0]=static_cast<void *>(input_addr);
    (*graph)[0]->setAddr(kAddr,  TISP::kAddrModeIn);
    TISP::execute::graph(graph);
    return 0;
}

void MatTransSignalChain::delete_pre_graph(void *pre_graph)
{
    if (pre_graph != NULL) delete static_cast<TISP::opVec *>(pre_graph);
}

void MatTransSignalChain::delete_post_graph(void *post_graph)
{
    if (post_graph != NULL) delete static_cast<TISP::opVec *>(post_graph);
}

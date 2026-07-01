/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "TISP_parametericEq_memory_map.hpp"
#include <TISP_test.h>
#include <TISP_types.hpp>
#include <cstdint>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tisp.hpp>
#include <vector>
#include <kernel/dpl/DebugP.h>
#include <TISP_ErrorCtxt.hpp>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TISP_NUM_REPS (1)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

__attribute__((section(".staticData")))
const float cascadeBiquad0CoeffCase1[] = {
1.9824839419765201, -3.903213147986163, 1.9216763845040938, -1.9560043675342487, 0.9569515460286996, 
0.9871155565127219, -1.9573412921733744, 0.9871155565127219, -1.9573412921733744, 0.9742311130254435, 
1.0800128988543187, -1.1228083303108325, 0.3991335361452531, -1.174843353140289, 0.4271114121701155, 

};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#ifdef __cplusplus
extern "C"
{
#endif

void *create_graph(int32_t *pIn, uint32_t *outStride)
{
    /* TypeConversion pointers */
    float *pIntToFloat = INT_TO_FLOAT_ADDR;

    /* CascadeBiquad pointers */
    float *pCascade0Coeff = CASCADE0_COEFF_ADDR;
    float *pCascade0FilterVar = CASCADE0_FILTER_VAR_ADDR;
    float *pCascade0Out = CASCADE0_OUT_ADDR;

    uint32_t nodeId = 1000;

    /* Copy cascade biquad coefficients */
    for (auto i = 0; i < CASCADE_FILTER_SIZE; i++)
    {
        pCascade0Coeff[i] = cascadeBiquad0CoeffCase1[i];
    }

    /* Initialize cascade biquad filter variables */
    for (auto i = 0; i < CASCADE_FILTER_VAR_SIZE; i++)
    {
        pCascade0FilterVar[i] = 0;
    }

    /* Create operation vector and add all operations */
    auto myOpVec = new TISP::opVec();
    TISP::ErrorCtxt errorCtx;

    /* Create the signal chain */
    /* 1. TypeConversion: int32_t to float */
    auto k0 =
        std::make_unique<TISP::AUDIOLIB::TypeConversion<int32_t, float>>(
            (int32_t *) pIn, (float *) pIntToFloat, NUM_CHANNELS,
            BLOCK_SIZE, NUM_CHANNELS * sizeof(int32_t),
            NUM_CHANNELS * sizeof(float), true,
            "TyperConversion: IntToFloat", nodeId++, errorCtx);
    if (errorCtx.isSuccess()) {
        myOpVec->push_back(std::move(k0)); /* typeconversion (int32_t to float) */
    } else {
        DebugP_log("Error: Failed to create TypeConversion Node (k0): %s\n", errorCtx.getMessage());
    }

    /* 2. CascadeBiquad: Apply parametric EQ */
    if (errorCtx.isSuccess()) {
        auto k1 = std::make_unique<TISP::DSPLIB::CascadeBiquad<float>>(
            (float *) pIntToFloat, (float *) pCascade0Coeff,
            (float *) pCascade0FilterVar, (float *) pCascade0Out, BLOCK_SIZE,
            NUM_CHANNELS, CASCADE_NUM_STAGES, DSPLIB_BIQUAD_DF1,
            (NUM_CHANNELS) * sizeof(float), (NUM_CHANNELS) * sizeof(float),
            NUM_CHANNELS * sizeof(float), false, "CascadeBiquad0", nodeId++, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k1)); /* cascadebiquad */
        } else {
            DebugP_log("Error: Failed to create CascadeBiquad Node (k1): %s\n", errorCtx.getMessage());
        }
    }

    /* 3. TypeConversion: float to int32_t */
    if (errorCtx.isSuccess()) {
        auto k2 =
            std::make_unique<TISP::AUDIOLIB::TypeConversion<float, int32_t>>(
                (float *) pCascade0Out, (int32_t *) pIn, NUM_CHANNELS,
                BLOCK_SIZE, NUM_CHANNELS * sizeof(float),
                NUM_CHANNELS * sizeof(int32_t), true,
                "TyperConversion: FloatToInt", nodeId++, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k2)); /* typeconversion (float to int32_t) */
        } else {
            DebugP_log("Error: Failed to create TypeConversion Node (k2): %s\n", errorCtx.getMessage());
        }
    }

    if (!errorCtx.isSuccess()) {
        delete myOpVec;
        return nullptr;
    }

    void *myGraph = myOpVec;
    *outStride = NUM_CHANNELS;

    return myGraph;
}

void execute_graph(void *myGraph, int32_t *pIn, int32_t *pOut)
{
    TISP::opVec *myOpVec = static_cast<TISP::opVec *>(myGraph);
    size_t length = myOpVec->size();

    TISP::SetAddr_t addrIn, addrOut;

    addrIn.src[0] = static_cast<void *>(pIn);
    addrOut.dst[0] = static_cast<void *>(pOut);

    (*myOpVec)[0]->setAddr(addrIn, TISP::kAddrModeIn);
    (*myOpVec)[length - 1]->setAddr(addrOut, TISP::kAddrModeOut);

    TISP::execute::graph(myOpVec);
}

void delete_graph(void *myGraph)
{
    TISP::opVec *myOpVec = static_cast<TISP::opVec *>(myGraph);
    delete (myOpVec);
}

uint32_t get_graph_length(void *myGraph)
{
    uint32_t length = 0;
    TISP::opVec *myOpVec = static_cast<TISP::opVec *>(myGraph);
    if (myOpVec)
    {
        length = (uint32_t) myOpVec->size();
    }

    return length;
}

int32_t getNodeInfo(void *myGraph, uint32_t nodeIndex, uint32_t *nodeId,
                    char *name, char *param)
{
    int32_t retVal = -1;
    TISP::opVec *myOpVec = static_cast<TISP::opVec *>(myGraph);

    if (myOpVec)
    {
        strcpy(name, (*myOpVec)[nodeIndex]->getNodeName());
        strcpy(param, (*myOpVec)[nodeIndex]->getNodeParams());
        *nodeId = (*myOpVec)[nodeIndex]->getNodeId();
        retVal = 0;
    }
    return retVal;
}

#ifdef __cplusplus
}
#endif

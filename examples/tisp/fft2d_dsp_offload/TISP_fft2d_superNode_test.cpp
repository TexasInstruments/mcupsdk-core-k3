/*
 *  Copyright (C) 2018-2025 Texas Instruments Incorporated
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

#include "TISP_blockCopy.hpp"
#include "TISP_fft2d_superNode_memory_map.hpp"
#include "TISP_superNode.hpp"
#include "TISP_test.h"
#include "TISP_util.hpp"
#include <cstdint>
#include <stdint.h>
#include <stdio.h>
#include <tisp.hpp>
#include <kernel/dpl/DebugP.h>
#include "dsp_offload.h"
#include <vector>

using namespace std;

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TOTAL_DMA_CHANNELS (2)

/* Below cycle count assume flat memory model, i.e, no memory-related stalls */
#define FFTLIB_FFT1DBATCHED_16X512_CYCLES (12904)
#define FFTLIB_FFT1DATCHED_512X512_CYCLES (FFTLIB_FFT1DBATCHED_16X512_CYCLES) * (512 / 16)
#define DSPLIB_MAT_TRANS_CYCLES ((NUM_POINTS * NUM_CHANNELS) / 4)
#define ESITMATED_TOTAL_CYCLE_COUNT ((2 * FFTLIB_FFT1DATCHED_512X512_CYCLES) + DSPLIB_MAT_TRANS_CYCLES)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Data buffers from L2SRAM */
float *pInputBlock = INPUT_BLOCK_ADDR;
float *pTempBlock = TEMP_BLOCK_ADDR;
float *pOutputBlock = OUT_BLOCK_ADDR;

uint32_t numPoints;
uint32_t numChannels;
uint32_t blockWidth;
uint32_t blockHeight;

float *input;
float *tempOut;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void *create_graph(void *input_ptr)
{

#if __C7X_VEC_SIZE_BITS__ == 512
    int32_t retVal = 0;
    Sciclient_ConfigPrms_t sciClientCfg;
    Sciclient_configPrmsInit(&sciClientCfg);
    retVal = Sciclient_init(&sciClientCfg);
    if (retVal != 0)
    {
        printf("Sciclient Init Failed \n");
    }

    TISP::test_sciclientDmscGetVersion(NULL, 0);
    TISP::appC7xClecInitDru();
#else
    App_dmautilsClecInitDru();
#endif
    numPoints = NUM_POINTS;
    numChannels = NUM_CHANNELS;
    input = (float *)(input_ptr);
    tempOut = TEMP_OUT_ADDR;
    blockWidth = numPoints << 1;
    blockHeight = BLOCK_HEIGHT;

    auto k0 = std::make_unique<TISP::FFTLIB::FFT1dBatched<float>>(pInputBlock, pTempBlock, numPoints, blockHeight);

    auto k1 = std::make_unique<TISP::DSPLIB::MatTrans<double>>(
        (double *)pTempBlock, (double *)pOutputBlock, blockWidth >> 1, blockHeight, blockWidth * sizeof(double) >> 1,
        blockHeight * sizeof(double));

    auto myOpVec0 = make_unique<TISP::opVec>();

    myOpVec0->push_back(std::move(k0));
    myOpVec0->push_back(std::move(k1));

    auto s0 = std::make_unique<TISP::SuperNode::I2dToO2dTranspose<double, double>>(
        std::move(myOpVec0), (double *)input, (double *)tempOut, (double *)pInputBlock, (double *)pOutputBlock,
        numPoints, numChannels, blockWidth >> 1, blockHeight, (numPoints) * sizeof(double), numChannels * sizeof(double),
        (TOTAL_DMA_CHANNELS));

    auto k2 = std::make_unique<TISP::FFTLIB::FFT1dBatched<float>>(pInputBlock, pOutputBlock, numChannels, blockHeight);

    auto myOpVec1 = std::make_unique<TISP::opVec>();

    myOpVec1->push_back(std::move(k2));

    auto s1 = std::make_unique<TISP::SuperNode::I2dToO2d<float, float>>(
        std::move(myOpVec1), tempOut, input, pInputBlock, pOutputBlock, numChannels << 1, numPoints, numChannels << 1,
        blockHeight, (numChannels << 1) * sizeof(float), (numChannels << 1) * sizeof(float), (TOTAL_DMA_CHANNELS));

    auto mySuperNodeVec = new TISP::SuperNode::superNodeVec();

    mySuperNodeVec->push_back(std::move(s0));
    mySuperNodeVec->push_back(std::move(s1));

    /* C-callable pointer to mySuperNodeVec that has
    all the info about the graph and prevents usage of smart pointer */
    void *myGraph = mySuperNodeVec;

    return myGraph;
}

void execute_graph(void *myGraph, params_t *params)
{

    TISP::SuperNode::superNodeVec *mySuperNodeVec = static_cast<TISP::SuperNode::superNodeVec *>(myGraph);

    uint64_t startTime, endTime;
    startTime = (__get_GTSC(1), __STSC);

    TISP::execute::graph(mySuperNodeVec);

    endTime = (__get_GTSC(1), __STSC);
    uint64_t totalTime = (endTime - startTime);

    if (params != NULL)
    {
        params->cycleCount = (uint32_t)totalTime;
        params->ddrThroughput = (float)((8 * NUM_POINTS * NUM_CHANNELS * 2) / ((float)totalTime));
    }
}

void delete_graph(void *myGraph)
{

    TISP::SuperNode::superNodeVec *mySuperNodeVec = static_cast<TISP::SuperNode::superNodeVec *>(myGraph);

    delete (mySuperNodeVec);

    return;
}
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

#include <cstdint>
#include <kernel/dpl/DebugP.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tisp.hpp>
#include <vector>
#include "dsp_offload.hpp"
#include "TISP_cascadeBiquad_FIR_memory_map.hpp"
#include <TISP_ErrorCtxt.hpp>

/* ========================================================================== */
/*                          Static Variables                                  */
/* ========================================================================== */

__attribute__((section(".staticData"))) static const float filterCoeffCase5[64] = {
0.000808,0.000429,-0.000480,-0.001121,-0.000672,0.000816,0.001995,0.001218,-0.001481,
-0.003579,-0.002148,0.002561,0.006067,0.003571,-0.004181,-0.009747,-0.005658,0.006550,0.015134,0.008734,
-0.010084,-0.023325,-0.013535,0.015798,0.037201,0.022183,-0.026964,-0.067462,-0.044178,0.062708,
0.210955,0.317885,0.317885,0.210955,0.062708,-0.044178,-0.067462,-0.026964,0.022183,0.037201,0.015798,
-0.013535,-0.023325,-0.010084,0.008734,0.015134,0.006550,-0.005658,-0.009747,-0.004181,0.003571,0.006067,
0.002561,-0.002148,-0.003579,-0.001481,0.001218,0.001995,0.000816,-0.000672,-0.001121,-0.000480,0.000429,0.000808,
};

__attribute__((section(".staticData"))) static const float cascadeBiquad0CoeffCase5[] = {
0.012515570545493047, 0.025085119455190003, 0.012569783383088968, -0.2677882507954173, 0.03465434968027205,
1.0, 2.000020548710341, 1.0000018586026858, -0.30756635979221025, 0.1883451608840448,
1.0, 1.9956665544858267, 0.9956852001842296, -0.41411047216403296, 0.5999999999999989,
};

__attribute__((section(".staticData"))) static const float cascadeBiquad1CoeffCase5[] = {
0.6019393389814026, -1.2074368469268795, 0.6055045371868447, -1.5454813220578387, 0.5999999999970064,
1.0, -1.9941195463961223, 0.9941310429220142, -1.6329931618618372, 0.6905989232462557,
1.0, -1.9999692782849627, 0.9999808654377201, -1.8105666824734503, 0.8744365594089779,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void *CascadeBiquadFIR::create_graph(int16_t* pIn)
{
    TISP::ErrorCtxt errorCtx;
    float *pIntToFloat = INT_TO_FLOAT_ADDR;

    float *pMatTransOut0 = MAT_TRANS_OUT0_ADDR;

    float *pCascade0Coeff     = CASCADE0_COEFF_ADDR;
    float *pCascade0FilterVar = CASCADE0_FILTER_VAR_ADDR;
    float *pCascade0Out       = CASCADE0_OUT_ADDR;

    float *pCascade1Coeff     = CASCADE1_COEFF_ADDR;
    float *pCascade1FilterVar = CASCADE1_FILTER_VAR_ADDR;
    float *pCascade1Out       = CASCADE1_OUT_ADDR;

    float *pFIRCoeff = FIR_COEFF_ADDR;
    float *pFIRState = FIR_STATE_ADDR;
    float *pFIROut   = FIR_OUT_ADDR;

    float *pFFT_temp = FFT_TEMP_ADDR;
    float *pOutFFT   = FFT_OUT_ADDR;

    float *pIFFT_temp = IFFT_TEMP_ADDR;
    float *pOutIFFT   = IFFT_OUT_ADDR;

    float *pMatTransOut1 = MAT_TRANS_OUT1_ADDR;

    for (auto i = 0; i < (BLOCK_SIZE + NUM_FIR_TAPS - 1) * NUM_CHANNELS; i++)
    {
        pFIRState[i] = 0;
    }

    for (auto i = 0; i < NUM_FIR_TAPS; i++)
    {
        pFIRCoeff[i] = filterCoeffCase5[i];
    }

    for (auto i = 0; i < CASCADE_FILTER_SIZE; i++)
    {
        pCascade0Coeff[i] = cascadeBiquad0CoeffCase5[i];
        pCascade1Coeff[i] = cascadeBiquad1CoeffCase5[i];
    }

    for (auto i = 0; i < CASCADE_FILTER_VAR_SIZE; i++)
    {
        pCascade0FilterVar[i] = 0;
        pCascade1FilterVar[i] = 0;
    }

#if defined(TISP_DEBUGPRINT)
    DebugP_log("\n-------------------------------------------------");
    DebugP_log("\n  Audio Filtering  Demo using TISP");
    DebugP_log("\n-------------------------------------------------\n");

    DebugP_log("\nCreating Graph:\n");

    DebugP_log("\nL2-->shortToFloat->DSPLIB_cascadeBiquad->DSPLIB_cascadeBiquad->DSPLIB_matTrans->DSPLIB_FIR->FFTLIB_"
            "RFFT->FFTLIB_IFFTR->floatToShort-->L2\n");
#endif

    auto myOpVec = new TISP::opVec();

    auto k0 = std::make_unique<TISP::misc::DataConvert<int16_t, float>>(
        pIn, pIntToFloat, NUM_CHANNELS, BLOCK_SIZE, (NUM_CHANNELS * sizeof(int16_t)), (NUM_CHANNELS * sizeof(float)), errorCtx);
    if (errorCtx.isSuccess()) {
        myOpVec->push_back(std::move(k0));
    } else {
        DebugP_log("Error: Failed to create DataConvert Node (k0): %s\n", errorCtx.getMessage());
    }

    if (errorCtx.isSuccess()) {
        auto k1 = std::make_unique<TISP::DSPLIB::CascadeBiquad<float>>(
            (float *) pIntToFloat, (float *) pCascade0Coeff, (float *) pCascade0FilterVar, (float *) pCascade0Out,
            BLOCK_SIZE, NUM_CHANNELS, CASCADE_NUM_STAGES, DSPLIB_BIQUAD_DF1, (NUM_CHANNELS) * sizeof(float),
            (NUM_CHANNELS) * sizeof(float), NUM_CHANNELS * sizeof(float), false, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k1));
        } else {
            DebugP_log("Error: Failed to create CascadeBiquad Node (k1): %s\n", errorCtx.getMessage());
        }
    }

    if (errorCtx.isSuccess()) {
        auto k2 = std::make_unique<TISP::DSPLIB::CascadeBiquad<float>>(
            (float *) pCascade0Out, (float *) pCascade1Coeff, (float *) pCascade1FilterVar, (float *) pCascade1Out,
            BLOCK_SIZE, NUM_CHANNELS, CASCADE_NUM_STAGES, DSPLIB_BIQUAD_DF1, (NUM_CHANNELS) * sizeof(float),
            (NUM_CHANNELS) * sizeof(float), NUM_CHANNELS * sizeof(float), false, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k2));
        } else {
            DebugP_log("Error: Failed to create CascadeBiquad Node (k2): %s\n", errorCtx.getMessage());
        }
    }

    if (errorCtx.isSuccess()) {
        auto k3 = std::make_unique<TISP::DSPLIB::MatTrans<float>>(pCascade1Out, pMatTransOut0, NUM_CHANNELS, BLOCK_SIZE,
                                                                 NUM_CHANNELS * sizeof(float), BLOCK_SIZE * sizeof(float), errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k3));
        } else {
            DebugP_log("Error: Failed to create MatTrans Node (k3): %s\n", errorCtx.getMessage());
        }
    }

    if (errorCtx.isSuccess()) {
        auto k4 = std::make_unique<TISP::DSPLIB::Fir<float>>(
            (float *) pMatTransOut0, (float *) pFIRState, (float *) pFIRCoeff, (float *) pFIROut, BLOCK_SIZE, NUM_FIR_TAPS,
            (BLOCK_SIZE + NUM_FIR_TAPS - 1), NUM_CHANNELS, BLOCK_SIZE * sizeof(float),
            (BLOCK_SIZE + NUM_FIR_TAPS - 1) * sizeof(float), NUM_FIR_TAPS * sizeof(float), BLOCK_SIZE * sizeof(float), false,
            false, false, 0, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k4));
        } else {
            DebugP_log("Error: Failed to create Fir Node (k4): %s\n", errorCtx.getMessage());
        }
    }

    if (errorCtx.isSuccess()) {
        auto k5 =
            std::make_unique<TISP::FFTLIB::RFFT1dBatched<float>>(pFIROut, pFFT_temp, pOutFFT, BLOCK_SIZE, NUM_CHANNELS, 1, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k5));
        } else {
            DebugP_log("Error: Failed to create RFFT1dBatched Node (k5): %s\n", errorCtx.getMessage());
        }
    }

    if (errorCtx.isSuccess()) {
        auto k6 =
          std::make_unique<TISP::FFTLIB::IFFTR1dBatched<float>>(pOutFFT, pIFFT_temp, pOutIFFT, BLOCK_SIZE, NUM_CHANNELS,1, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k6));
        } else {
            DebugP_log("Error: Failed to create IFFTR1dBatched Node (k6): %s\n", errorCtx.getMessage());
        }
    }

    if (errorCtx.isSuccess()) {
        auto k7 = std::make_unique<TISP::DSPLIB::MatTrans<float>>(pOutIFFT, pMatTransOut1, BLOCK_SIZE, NUM_CHANNELS,
                                                                 BLOCK_SIZE * sizeof(float), NUM_CHANNELS * sizeof(float), errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k7));
        } else {
            DebugP_log("Error: Failed to create MatTrans Node (k7): %s\n", errorCtx.getMessage());
        }
    }

    if (errorCtx.isSuccess()) {
        auto k8 = std::make_unique<TISP::misc::DataConvert<float, int16_t>>(
            pMatTransOut1, pIn, NUM_CHANNELS, BLOCK_SIZE, (NUM_CHANNELS * sizeof(float)), (NUM_CHANNELS * sizeof(int16_t)), errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k8));
        } else {
            DebugP_log("Error: Failed to create DataConvert Node (k8): %s\n", errorCtx.getMessage());
        }
    }

    if (!errorCtx.isSuccess()) {
        delete myOpVec;
        return nullptr;
    }

    void *myGraph = myOpVec;

    return myGraph;
}

void CascadeBiquadFIR::execute_graph(void *myGraph, int16_t *pIn, bool enableFiltering)
{
    TISP::opVec *myOpVec = static_cast<TISP::opVec *>(myGraph);

#if defined(TISP_DEBUGPRINT)
    DebugP_log("\nBefore processing pIn:\n");

    for (auto i = 0; i < 128; i++)
    {
        DebugP_log("%d, ", pIn[i * NUM_CHANNELS + 7]);
    }

    DebugP_log("\n\n");
#endif

    size_t          length = myOpVec->size();
    TISP::SetAddr_t addr;

    if (enableFiltering == false)
    {
        addr.src[0] = static_cast<void *>(INT_TO_FLOAT_ADDR);
        (*myOpVec)[length - 1]->setAddr(addr, TISP::kAddrModeIn);
    }
    else
    {
        addr.src[0] = static_cast<void *>(MAT_TRANS_OUT1_ADDR);
        (*myOpVec)[length - 1]->setAddr(addr, TISP::kAddrModeIn);
    }

    TISP::execute::graph(myOpVec);

#if defined(TISP_DEBUGPRINT)
    DebugP_log("\nAfter pocessing in DSP pIn:\n");

    for (auto i = 0; i < 128; i++)
    {
        DebugP_log("%d, ", pIn[i * NUM_CHANNELS + 7]);
    }

    DebugP_log("\n\n");
#endif
}

void CascadeBiquadFIR::delete_graph(void *myGraph)
{
    TISP::opVec *myOpVec = static_cast<TISP::opVec *>(myGraph);
    delete (myOpVec);
}

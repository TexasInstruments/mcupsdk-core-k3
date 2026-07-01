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

#include "TISP_profiler.hpp"
#include "TISP_router_8ch_12ch_memory_map.hpp"
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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

__attribute__((section(".staticData"))) const float filterCoeffCase5[64] = {
    -0.000158, -0.000478, -0.000802, -0.001103, -0.001322, -0.001362,
    -0.001112, -0.000477, 0.000580,  0.001995,  0.003585,  0.005041,
    0.005970,  0.005959,  0.004662,  0.001908,  -0.002215, -0.007303,
    -0.012626, -0.017191, -0.019848, -0.019460, -0.015090, -0.006185,
    0.007282,  0.024733,  0.044991,  0.066390,  0.086951,  0.104634,
    0.117598,  0.124453,  0.124453,  0.117598,  0.104634,  0.086951,
    0.066390,  0.044991,  0.024733,  0.007282,  -0.006185, -0.015090,
    -0.019460, -0.019848, -0.017191, -0.012626, -0.007303, -0.002215,
    0.001908,  0.004662,  0.005959,  0.005970,  0.005041,  0.003585,
    0.001995,  0.000580,  -0.000477, -0.001112, -0.001362, -0.001322,
    -0.001103, -0.000802, -0.000478, -0.000158,
};

__attribute__((section(".staticData")))
const float cascadeBiquad0CoeffCase5[] = {
    0.00041948939301750265,
    0.0008407880004973959,
    0.00042130646641852786,
    -0.9991739983888562,
    0.2594312617654552,

    1.0,
    1.9956665544858267,
    0.9956852001842296,
    -1.1092287926183546,
    0.39815229392140655,

    1.0,
    2.000020548710341,
    1.0000018586026858,
    -1.3707349773490773,
    0.727773625867477,

};

__attribute__((section(".staticData")))
const float cascadeBiquad1CoeffCase5[] = {
    0.8812023306672565,
    -1.7662051960365488,
    0.8850193742849135,
    -1.8771309052928467,
    0.8811586102850746,

    1.0,
    -2.0000205487100913,
    1.0000018586025619,
    -1.9075016261036066,
    0.9115944967006698,

    1.0,
    -1.9956665545013221,
    0.9956852001995965,
    -1.9624975218487957,
    0.9667083954633344,

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

    /* FIR pointers */
    float *pFIRCoeff = FIR_COEFF_ADDR;
    float *pFIRState = FIR_STATE_ADDR;
    float *pFIROut = FIR_OUT_ADDR;

    /* MatrixTranspose pointers */
    float *pMatTransOut0 = MAT_TRANS_OUT0_ADDR;
    float *pMatTransOut1 = MAT_TRANS_OUT1_ADDR;

    /* CascadeBiquad0 pointers */
    float *pCascade0Coeff = CASCADE0_COEFF_ADDR;
    float *pCascade0FilterVar = CASCADE0_FILTER_VAR_ADDR;
    float *pCascade0Out = CASCADE0_OUT_ADDR;

    /* CascadeBiquad1 pointers */
    float *pCascade1Coeff = CASCADE1_COEFF_ADDR;
    float *pCascade1FilterVar = CASCADE1_FILTER_VAR_ADDR;
    float *pCascade1Out = CASCADE1_OUT_ADDR;

    /* FFT pointers */
    float *pFFT_temp = FFT_TEMP_ADDR;
    float *pOutFFT = FFT_OUT_ADDR;

    /* IFFT pointers */
    float *pIFFT_temp = IFFT_TEMP_ADDR;
    float *pOutIFFT = IFFT_OUT_ADDR;

    /* Router pointers */
    int32_t *pConfigRouter = (int32_t *) ROUTER_CONFIG_ADDR;
    float *pScratchRouter = ROUTER_SCRATCH_ADDR;
    float *pOutRouter = ROUTER_OUT_ADDR;

    /* Copy router configuration */
    /* pConfigRouter = {0,1,2,3,4,5,6,7,0,1,2,3} (8ch->12ch routing) */
    for (auto i = 0; i < NUM_CHANNELS_OUT; i++)
    {
        if (i >= 8)
        {
            pConfigRouter[i] = i - 8;
        }
        else
        {
            pConfigRouter[i] = i;
        }
    }

    /* Initialize FIR filter state */
    for (auto i = 0; i < (BLOCK_SIZE + NUM_FIR_TAPS - 1) * NUM_CHANNELS;
         i++)
    {
        pFIRState[i] = 0;
    }

    /* Copy FIR filter coefficients */
    for (auto i = 0; i < NUM_FIR_TAPS; i++)
    {
        pFIRCoeff[i] = filterCoeffCase5[i];
    }

    /* Copy cascade biquad coefficients for both filters */
    for (auto i = 0; i < CASCADE_FILTER_SIZE; i++)
    {
        pCascade0Coeff[i] = cascadeBiquad0CoeffCase5[i];
        pCascade1Coeff[i] = cascadeBiquad1CoeffCase5[i];
    }

    /* Initialize cascade biquad filter variables for both filters */
    for (auto i = 0; i < CASCADE_FILTER_VAR_SIZE; i++)
    {
        pCascade0FilterVar[i] = 0;
        pCascade1FilterVar[i] = 0;
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
            "TyperConversion: IntToFloat", 0, errorCtx);
    if (errorCtx.isSuccess()) {
        myOpVec->push_back(std::move(k0));
    } else {
        DebugP_log("Error: Failed to create TypeConversion Node (k0): %s\n", errorCtx.getMessage());
    }

    /* 2. CascadeBiquad0: First biquad filter */
    if (errorCtx.isSuccess()) {
        auto k1 = std::make_unique<TISP::DSPLIB::CascadeBiquad<float>>(
            (float *) pIntToFloat, (float *) pCascade0Coeff,
            (float *) pCascade0FilterVar, (float *) pCascade0Out, BLOCK_SIZE,
            NUM_CHANNELS, CASCADE_NUM_STAGES, DSPLIB_BIQUAD_DF1,
            (NUM_CHANNELS) * sizeof(float), (NUM_CHANNELS) * sizeof(float),
            NUM_CHANNELS * sizeof(float), false, "CascadeBiquad0", 1, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k1));
        } else {
            DebugP_log("Error: Failed to create CascadeBiquad Node (k1): %s\n", errorCtx.getMessage());
        }
    }

    /* 3. CascadeBiquad1: Second biquad filter */
    if (errorCtx.isSuccess()) {
        auto k2 = std::make_unique<TISP::DSPLIB::CascadeBiquad<float>>(
            (float *) pCascade0Out, (float *) pCascade1Coeff,
            (float *) pCascade1FilterVar, (float *) pCascade1Out, BLOCK_SIZE,
            NUM_CHANNELS, CASCADE_NUM_STAGES, DSPLIB_BIQUAD_DF1,
            (NUM_CHANNELS) * sizeof(float), (NUM_CHANNELS) * sizeof(float),
            NUM_CHANNELS * sizeof(float), false, "CascadeBiquad1", 2, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k2));
        } else {
            DebugP_log("Error: Failed to create CascadeBiquad Node (k2): %s\n", errorCtx.getMessage());
        }
    }

    /* 4. MatrixTranspose: Transpose for FIR processing */
    if (errorCtx.isSuccess()) {
        auto k3 = std::make_unique<TISP::DSPLIB::MatTrans<float>>(
            pCascade1Out, pMatTransOut1, NUM_CHANNELS, BLOCK_SIZE,
            NUM_CHANNELS * sizeof(float), BLOCK_SIZE * sizeof(float),
            "MatTrans0", 3, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k3));
        } else {
            DebugP_log("Error: Failed to create MatTrans Node (k3): %s\n", errorCtx.getMessage());
        }
    }

    /* 5. FIR: Apply FIR filter */
    if (errorCtx.isSuccess()) {
        auto k4 = std::make_unique<TISP::DSPLIB::Fir<float>>(
            (float *) pMatTransOut1, (float *) pFIRState, (float *) pFIRCoeff,
            (float *) pFIROut, BLOCK_SIZE, NUM_FIR_TAPS,
            (BLOCK_SIZE + NUM_FIR_TAPS - 1), NUM_CHANNELS,
            BLOCK_SIZE * sizeof(float),
            (BLOCK_SIZE + NUM_FIR_TAPS - 1) * sizeof(float),
            NUM_FIR_TAPS * sizeof(float), BLOCK_SIZE * sizeof(float), false,
            false, false, 0, "FIR", 4, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k4));
        } else {
            DebugP_log("Error: Failed to create FIR Node (k4): %s\n", errorCtx.getMessage());
        }
    }

    /* 6. RFFT: Real FFT (1D batched) */
    if (errorCtx.isSuccess()) {
        auto k5 = std::make_unique<TISP::FFTLIB::RFFT1dBatched<float>>(
            pFIROut, pFFT_temp, pOutFFT, BLOCK_SIZE, NUM_CHANNELS, 1, "RFFT",
            5, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k5));
        } else {
            DebugP_log("Error: Failed to create RFFT1dBatched Node (k5): %s\n", errorCtx.getMessage());
        }
    }

    /* 7. IFFTR: Inverse real FFT (1D batched) */
    if (errorCtx.isSuccess()) {
        auto k6 = std::make_unique<TISP::FFTLIB::IFFTR1dBatched<float>>(
            pOutFFT, pIFFT_temp, pOutIFFT, BLOCK_SIZE, NUM_CHANNELS, 1,
            "IFFTR", 6, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k6));
        } else {
            DebugP_log("Error: Failed to create IFFTR1dBatched Node (k6): %s\n", errorCtx.getMessage());
        }
    }

    /* 8. MatrixTranspose: Transpose back after IFFT */
    if (errorCtx.isSuccess()) {
        auto k7 = std::make_unique<TISP::DSPLIB::MatTrans<float>>(
            pOutIFFT, pMatTransOut0, BLOCK_SIZE, NUM_CHANNELS,
            BLOCK_SIZE * sizeof(float), NUM_CHANNELS * sizeof(float),
            "MatTrans1", 7, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k7));
        } else {
            DebugP_log("Error: Failed to create MatTrans Node (k7): %s\n", errorCtx.getMessage());
        }
    }

    /* 9. Router: Route 8 channels to 12 channels */
    if (errorCtx.isSuccess()) {
        auto k8 = std::make_unique<TISP::AUDIOLIB::Router<float>>(
            pMatTransOut0, (float *) pConfigRouter, (float *) pScratchRouter,
            (float *) pOutRouter, NUM_CHANNELS, BLOCK_SIZE, NUM_CHANNELS_OUT,
            NUM_CHANNELS * sizeof(float), NUM_CHANNELS_OUT * sizeof(float),
            true, "Router", 8, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k8));
        } else {
            DebugP_log("Error: Failed to create Router Node (k8): %s\n", errorCtx.getMessage());
        }
    }

    /* 10. TypeConversion: float to int32_t */
    if (errorCtx.isSuccess()) {
        auto k9 =
            std::make_unique<TISP::AUDIOLIB::TypeConversion<float, int32_t>>(
                pOutRouter, pIn, NUM_CHANNELS_OUT, BLOCK_SIZE,
                (NUM_CHANNELS_OUT * sizeof(float)),
                (NUM_CHANNELS_OUT * sizeof(int32_t)), true,
                "TyperConversion: FloatToInt", 9, errorCtx);
        if (errorCtx.isSuccess()) {
            myOpVec->push_back(std::move(k9));
        } else {
            DebugP_log("Error: Failed to create TypeConversion Node (k9): %s\n", errorCtx.getMessage());
        }
    }

    if (!errorCtx.isSuccess()) {
        delete myOpVec;
        return nullptr;
    }

    void *myGraph = myOpVec;
    *outStride = NUM_CHANNELS_OUT;

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

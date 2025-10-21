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

#include "TISP_8ch_to_12ch_audio_chain_memory_map.hpp"
#include <TISP_profile.hpp>
#include <TISP_test.h>
#include <TISP_types.hpp>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tisp.hpp>
#include <vector>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DEBUG (0)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

__attribute__((section(".staticData")))
const float cascadeBiquadHPFCoeff[] = {
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


__attribute__((section(".staticData")))
const float cascadeBiquadPEqCoeff[] = {
    1.1208233836671753,  -2.2013304720124425, 1.0812194694329536,
    -1.9618991129360017, 0.9626114940236884,

    0.9871155565127219,  -1.9573412921733744, 0.9871155565127219,
    -1.9573412921733744, 0.9742311130254435,

    1.0800128988543187,  -1.1228083303108325, 0.3991335361452531,
    -1.174843353140289,  0.4271114121701155,

};

__attribute__((section(".staticData"))) const float targetGain1[8] = {
    0.500000, 0.500000, 0.500000, 0.500000,
    0.500000, 0.500000, 0.500000, 0.500000,
};

__attribute__((section(".staticData"))) const float channelGains1[12] = {
    0.900000, 0.900000, 0.900000, 0.900000, 0.900000, 0.900000,
    0.900000, 0.900000, 0.900000, 0.900000, 0.900000, 0.900000,
};

__attribute__((section(".staticData"))) const float threshold_dB1[12] = {
    -3.000000, -3.000000, -3.000000, -3.000000, -3.000000, -3.000000,
    -3.000000, -3.000000, -3.000000, -3.000000, -3.000000, -3.000000,
};

__attribute__((section(".staticData"))) const float kneeWidth_dB1[12] = {
    6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
    6.000000, 6.000000, 6.000000, 6.000000, 6.000000, 6.000000,
};

__attribute__((section(".staticData"))) const float attackCoeff1[12] = {
    0.900000, 0.900000, 0.900000, 0.900000, 0.900000, 0.900000,
    0.900000, 0.900000, 0.900000, 0.900000, 0.900000, 0.900000,
};

__attribute__((section(".staticData"))) const float releaseCoeff1[12] = {
    0.900000, 0.900000, 0.900000, 0.900000, 0.900000, 0.900000,
    0.900000, 0.900000, 0.900000, 0.900000, 0.900000, 0.900000,
};

__attribute__((section(".staticData"))) const int32_t delaySizes1[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

__attribute__((section(".staticData")))
const float balanceFaderFloatParams1[5] = {
    0.200000, 0.100000, 0.800000, 0.600000, 0.700000,
};

__attribute__((section(".staticData")))
const int32_t balanceFaderIntParams1[2] = {
    1,
    2,
};

__attribute__((section(".staticData")))
const int32_t balanceFaderChannelConfig1[12] = {
    1, 5, 8, 9, 10, 11, 12, 13, 2, 6, 14, 15,
};

__attribute__((section(".staticData"))) const int32_t routerConfig1[12] = {
    0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3,
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
    float *pTypeConvInOut = TYPE_CONV_IN_OUT_ADDR;

    /* GainNCh pointers */
    float *pGainNChTarget = GAIN_NCH_TARGET_ADDR;
    float *pGainNChOut = GAIN_NCH_OUT_ADDR;

    /* CascadeBiquad pointers */
    float *pCascadeHPFCoeff = CASCADE_HPF_COEFF_ADDR;    
    float *pCascadeFilterVar = CASCADE_FILTER_VAR_ADDR;
    float *pCascadeOut = CASCADE_OUT_ADDR;

    /* Router pointers */
    int32_t *pRouterConfig = (int32_t *) ROUTER_OUT_CHANNELS_ADDR;
    float *pRouterScratch = ROUTER_SCRATCH_ADDR;
    float *pRouterOut = ROUTER_OUT_ADDR;

    /* Parametric EQ pointers (using CascadeBiquad implementation) */
    float *pCascadeCoeff = CASCADE_COEFF_ADDR;    
    float *pParamEqFilterVar = PARAM_EQ_FILTER_VAR_ADDR;
    float *pParamEqOut = PARAM_EQ_OUT_ADDR;

    /* DelayNCh pointers */
    int32_t *pDelayNChSizes = (int32_t *) DELAY_NCH_SIZES_ADDR;
    float *pDelayNChBuffer = DELAY_NCH_BUFFER_ADDR;
    float *pDelayNChScratch = DELAY_NCH_SCRATCH_ADDR;
    float *pDelayNChOut = DELAY_NCH_OUT_ADDR;

    /* BalanceFader pointers */
    float *pBalanceFaderGain = BALANCE_FADER_GAIN_ADDR;
    int32_t *pBalanceFaderChannelConfig =
        (int32_t *) BALANCE_FADER_CHANNEL_CONFIG_ADDR;
    float *pBalanceFaderOut = BALANCE_FADER_OUT_ADDR;

    /* GainNChTrim pointers */
    float *pGainNChTrimChannelGains = GAIN_NCH_TRIM_CHANNEL_GAINS_ADDR;
    float *pGainNChTrimMasterGain = GAIN_NCH_TRIM_MASTER_GAIN_ADDR;
    float *pGainNChTrimOut = GAIN_NCH_TRIM_OUT_ADDR;

    /* Limiter pointers */
    float *pLimiterGain = LIMITER_GAIN_ADDR;
    float *pLimiterScratch = LIMITER_SCRATCH_ADDR;
    float *pLimiterThreshold = LIMITER_THRESHOLD_ADDR;
    float *pLimiterKneeWidth = LIMITER_KNEE_WIDTH_ADDR;
    float *pLimiterAttackCoeff = LIMITER_ATTACK_COEFF_ADDR;
    float *pLimiterReleaseCoeff = LIMITER_RELEASE_COEFF_ADDR;
    float *pLimiterOut = LIMITER_OUT_ADDR;

    /* MuteNCh pointers */
    int32_t *pMuteNChIsMute = (int32_t *) MUTE_NCH_IS_MUTE_ADDR;
    float *pMuteNChOut = MUTE_NCH_OUT_ADDR;

    /* Final output pointer */
    int32_t *pFloatToInt = FLOAT_TO_INT_ADDR;

    /* Copy cascade biquad coefficients */
    for (auto i = 0; i < CASCADE_FILTER_SIZE; i++)
    {
        pCascadeHPFCoeff[i] = cascadeBiquadHPFCoeff[i];
	pCascadeCoeff[i] = cascadeBiquadPEqCoeff[i];        
    }

    /* Initialize cascade biquad filter variables */
    for (auto i = 0; i < CASCADE_FILTER_VAR_SIZE; i++)
    {
        pCascadeFilterVar[i] = 0;
    }

    /* Initialize parametric EQ filter variables */
    for (auto i = 0; i < PARAM_EQ_FILTER_VAR_SIZE; i++)
    {
        pParamEqFilterVar[i] = 0;
    }

    /* Copy gain values for gainNCh */
    for (auto i = 0; i < NUM_CHANNELS_IN; i++)
    {
        pGainNChTarget[i] = targetGain1[i];
    }

    /* Copy router configuration */
    for (auto i = 0; i < NUM_CHANNELS_OUT; i++)
    {
        pRouterConfig[i] = routerConfig1[i];
    }

    /* Delay sizes */
    for (auto i = 0; i < NUM_CHANNELS_OUT; i++)
    {
        pDelayNChSizes[i] = delaySizes1[i];
    }

    /* Set up channel gains for gainNChTrim */
    for (auto i = 0; i < NUM_CHANNELS_OUT; i++)
    {
        pGainNChTrimChannelGains[i] = channelGains1[i];
    }
    
    /* Set master gain for gainNChTrim */
    pGainNChTrimMasterGain[0] = 0.95f;

    /* Set up limiter parameters */
    for (auto i = 0; i < NUM_CHANNELS_OUT; i++)
    {
        pLimiterThreshold[i] = threshold_dB1[i];
        pLimiterKneeWidth[i] = kneeWidth_dB1[i];
        pLimiterAttackCoeff[i] = attackCoeff1[i];
        pLimiterReleaseCoeff[i] = releaseCoeff1[i];
    }

    /* Set up balanceFader parameters */
    for (auto i = 0; i < NUM_CHANNELS_OUT; i++)
    {
        pBalanceFaderChannelConfig[i] = balanceFaderChannelConfig1[i];
        pBalanceFaderGain[i] =
            1.0f; /* Initialize gains to 1.0 (unity gain) instead of 0 */
    }

    /* Copy gain values for muteNCh */
    for (auto i = 0; i < NUM_CHANNELS_OUT; i++)
    {
        pMuteNChIsMute[i] = 0; // 0 = unmuted, 1 = muted
    }

    /* Create the signal chain */
    /* 1. TypeConversion: int32_t to float */
    auto k0 =
        std::make_unique<TISP::AUDIOLIB::TypeConversion<int32_t, float>>(
            pIn, pTypeConvInOut, NUM_CHANNELS_IN, BLOCK_SIZE,
            NUM_CHANNELS_IN * sizeof(int32_t),
            NUM_CHANNELS_IN * sizeof(float), IS_INTERLEAVED,
            "TypeConversion (i32->f32)", 0);

    /* 2. GainNCh */
    auto k1 = std::make_unique<TISP::AUDIOLIB::GainNCh<float>>(
        pTypeConvInOut, pGainNChTarget, pGainNChOut, NUM_CHANNELS_IN,
        BLOCK_SIZE, NUM_CHANNELS_IN, NUM_CHANNELS_IN * sizeof(float),
        NUM_CHANNELS_IN * sizeof(float), IS_INTERLEAVED, "GainNCh", 1);

    /* 3. CascadeBiquad */
    auto k2 = std::make_unique<TISP::DSPLIB::CascadeBiquad<float>>(
        pGainNChOut, pCascadeHPFCoeff, pCascadeFilterVar, pCascadeOut,
        BLOCK_SIZE, NUM_CHANNELS_IN, CASCADE_NUM_STAGES, DSPLIB_BIQUAD_DF1,
        NUM_CHANNELS_IN * sizeof(float), NUM_CHANNELS_IN * sizeof(float),
        NUM_CHANNELS_IN * sizeof(float), false, "CascadeBiquad (HPF)", 2);

    /* 4. Router */
    auto k3 = std::make_unique<TISP::AUDIOLIB::Router<float>>(
        pCascadeOut, (float *) pRouterConfig, (float *) pRouterScratch,
        (float *) pRouterOut, NUM_CHANNELS_IN, BLOCK_SIZE,
        NUM_CHANNELS_OUT, NUM_CHANNELS_IN * sizeof(float),
        NUM_CHANNELS_OUT * sizeof(float), IS_INTERLEAVED,
        "Router (8ch->12ch)", 3);

    /* 5. Parametric EQ (using CascadeBiquad) */
    auto k4 = std::make_unique<TISP::DSPLIB::CascadeBiquad<float>>(
        pRouterOut, pCascadeCoeff, pParamEqFilterVar, pParamEqOut,
        BLOCK_SIZE, NUM_CHANNELS_OUT, CASCADE_NUM_STAGES,
        DSPLIB_BIQUAD_DF1, NUM_CHANNELS_OUT * sizeof(float),
        NUM_CHANNELS_OUT * sizeof(float), NUM_CHANNELS_OUT * sizeof(float),
        false, "CascadeBiquad (Speaker EQ)", 4);

    /* 6. DelayNCh */
    auto k5 = std::make_unique<TISP::AUDIOLIB::DelayNChannel<float>>(
        pParamEqOut, pDelayNChBuffer, pDelayNChScratch, pDelayNChOut,
        NUM_CHANNELS_OUT, BLOCK_SIZE, DELAY_MAX_DELAY,
        NUM_CHANNELS_OUT, // width=BLOCK_SIZE, height=NUM_CHANNELS_OUT, widthD=DELAY_MAX_DELAY+1,
        // heightD=NUM_CHANNELS_OUT
        NUM_CHANNELS_OUT * sizeof(float),
        (DELAY_MAX_DELAY + 1) * sizeof(float),
        NUM_CHANNELS_OUT *
            sizeof(float), // inPitchBytes, delayBytes, outPitchBytes
        IS_INTERLEAVED, DELAY_NCH_LINEAR_MODE, (uint32_t *) pDelayNChSizes,
        DELAY_MAX_DELAY, "DelayNChannel",
        5); // interleave=IS_INTERLEAVED, mode=0, pDelaySize, maxDelay=DELAY_MAX_DELAY

    /* 7. BalanceFader */
    auto k6 = std::make_unique<TISP::AUDIOLIB::BalanceFader<float>>(
        pDelayNChOut, pBalanceFaderGain, pBalanceFaderOut,
        NUM_CHANNELS_OUT, BLOCK_SIZE,
        NUM_CHANNELS_OUT, // gWidthIn set to NUM_CHANNELS_OUT
        NUM_CHANNELS_OUT * sizeof(float), NUM_CHANNELS_OUT * sizeof(float),
        IS_INTERLEAVED, // isInterleave=IS_INTERLEAVED
        balanceFaderFloatParams1[0], balanceFaderFloatParams1[1],
        pBalanceFaderChannelConfig, balanceFaderFloatParams1[2],
        balanceFaderFloatParams1[3], balanceFaderFloatParams1[4],
        balanceFaderIntParams1[0], balanceFaderIntParams1[1],
        "BalanceFader", 6);

    /* 8. GainNChTrim */
    auto k7 = std::make_unique<TISP::AUDIOLIB::GainNChTrim<float>>(
        pBalanceFaderOut, pGainNChTrimChannelGains, pGainNChTrimMasterGain,
        pGainNChTrimOut, NUM_CHANNELS_OUT, BLOCK_SIZE,
        NUM_CHANNELS_OUT, // gHeight = NUM_CHANNELS_OUT
        NUM_CHANNELS_OUT * sizeof(float), NUM_CHANNELS_OUT * sizeof(float),
        IS_INTERLEAVED, "GainNChTrim", 7);

    /* 9. Limiter */
    auto k8 = std::make_unique<TISP::AUDIOLIB::Limiter<float>>(
        pGainNChTrimOut, pLimiterGain, pLimiterScratch, pLimiterOut,
        pLimiterThreshold, pLimiterKneeWidth, pLimiterAttackCoeff,
        pLimiterReleaseCoeff, NUM_CHANNELS_OUT, BLOCK_SIZE,
        NUM_CHANNELS_OUT * sizeof(float), NUM_CHANNELS_OUT * sizeof(float),
        MUTE_NCH_STRIDE_ELEM * sizeof(float), IS_INTERLEAVED, "Limiter",
        8); // isInterleaved=IS_INTERLEAVED

    /* 10. MuteNCh */
    auto k9 = std::make_unique<TISP::AUDIOLIB::Mutench<float>>(
        pLimiterOut, pMuteNChOut, NUM_CHANNELS_OUT, BLOCK_SIZE,
        NUM_CHANNELS_OUT, MUTE_NCH_STRIDE_ELEM * sizeof(float),
        MUTE_NCH_STRIDE_ELEM * sizeof(float), IS_INTERLEAVED,
        SAMPLING_RATE_HZ, pMuteNChIsMute, MUTE_NCH_FADE_TIME,
        MUTE_NCH_FADE_HARD_TYPE, "MuteNCh", 9);

    /* 11. TypeConversion: float to int32_t */
    auto k10 =
        std::make_unique<TISP::AUDIOLIB::TypeConversion<float, int32_t>>(
            pMuteNChOut, pFloatToInt, NUM_CHANNELS_OUT, BLOCK_SIZE,
            MUTE_NCH_STRIDE_ELEM * sizeof(float),
            NUM_CHANNELS_OUT * sizeof(int32_t), IS_INTERLEAVED,
            "TypeConversion (f32->i32)", 10);

    /* Create operation vector and add all operations */
    auto myOpVec = new TISP::opVec();

    /* Create the signal chain in the specified order: */
    /* typeconversion --> gainNCh --> cascadebiquad --> 8ch to 12ch router --> parametric eq --> delayNCh --> */
    /* balanceFader --> gainNchTrim --> muteNCh --> typeconversion */
    myOpVec->push_back(std::move(k0)); /* typeconversion (int32_t to float) */
    myOpVec->push_back(std::move(k1)); /* gainNCh */
    myOpVec->push_back(std::move(k2)); /* cascadebiquad */
    myOpVec->push_back(std::move(k3)); /* router */
    myOpVec->push_back(std::move(k4)); /* parametric eq */
    myOpVec->push_back(std::move(k5)); /* delayNCh */
    myOpVec->push_back(std::move(k6)); /* balanceFader */
    myOpVec->push_back(std::move(k7)); /* gainNchTrim */
    myOpVec->push_back(std::move(k8)); /* limiter */
    myOpVec->push_back(std::move(k9)); /* muteNCh */
    myOpVec->push_back(
        std::move(k10)); /* typeConversion (float to int32_t) */

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
        strcpy(param, (*myOpVec)[nodeIndex]->getParams());
        *nodeId = (*myOpVec)[nodeIndex]->getNodeId();
        retVal = 0;
    }
    return retVal;
}

#ifdef __cplusplus
}
#endif

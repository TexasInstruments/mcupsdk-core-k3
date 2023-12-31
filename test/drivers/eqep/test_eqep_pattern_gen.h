/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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

#ifndef EQEP_PATTERN_GEN_H_
#define EQEP_PATTERN_GEN_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EqepAppPatternParams_s
{
    uint32_t eqepClockFreq;
/** \brief EQEP Input Signal Frequency */
    uint32_t direction;
/** \brief EQEP Direction */
    uint32_t idxEvtCnt;
/** \brief EQEP Index Count */
    uint32_t loopCnt;
/** \brief Application loop count to generate eqep pattern */
    uint32_t generateIdxPulse;
/** \brief Enable/Disable Index Pulse */
}EqepAppPatternParams;

void App_eqepGeneratePattern(EqepAppPatternParams *patParam);
void App_eqepReadPinValue(uint32_t *pEqepAPin,
                          uint32_t *pEqepBPin,
                          uint32_t *pEqepIPin,
                          uint32_t *pEqepSPin);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef EQEP_PATTERN_GEN_H_ */

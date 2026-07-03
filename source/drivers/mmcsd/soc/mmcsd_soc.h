/*
 *  Copyright (C) 2025-26 Texas Instruments Incorporated
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

/**
 *  \file mmcsd_soc.h
 *
 *  \brief MMCSD Driver SOC file containing SOC specific APIs.
 *
 */

#ifndef MMCSD_SOC_H_
#define MMCSD_SOC_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/hw_include/soc_config.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief This API returns if HS400 mode is supported
 *
 *  \param  None
 *
 *  \return True or False
 */
bool MMCSD_socIsHS400Supported(void);

/**
 *  \brief This API gives the correct Tap values for a particular phyMode.
 *
 *  \param  outputTapDelaySel [OUT] Pointer to Output Tap Delay Select Value.
 *  \param  outputTapDelayVal [OUT] Pointer to Output Tap Delay Value.
 *  \param  inputTapDelaySel [OUT] Pointer to Input Tap Delay Select Value.
 *  \param  inputTapDelayVal [OUT] Pointer to Input Tap Delay Value.
 *  \param  phyMode [IN] The Operating PHY Mode whose tap values are needed.
 *  \param  tunedItap [IN] The calculated tuned ITAP to be set for certain phyModes.
 *
 */
void MMCSD_phyGetTapValues(uint32_t *outputTapDelaySel, uint32_t *outputTapDelayVal,
    uint32_t *inputTapDelaySel, uint32_t *inputTapDelayVal, uint32_t phyMode, uint8_t tunedItap,
    uint32_t cardType, uint32_t vddCoreVoltage);

#ifdef __cplusplus
}
#endif

#endif

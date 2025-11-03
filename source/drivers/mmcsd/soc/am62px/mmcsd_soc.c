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

/**
 *  \file mmcsd_soc.c
 *
 *  \brief File containing the operating mode support APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdbool.h>
#include <drivers/soc.h>
#include <drivers/mmcsd.h>
#include <drivers/mmcsd/soc/mmcsd_soc.h>

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

bool MMCSD_socIsHS400Supported(void)
{
    bool result = FALSE;
    uint32_t siliconRev = SOC_getSiliconRevisionVersion();

    /* Silicon revision less than 1.2 do not support HS400 mode. */
    if(siliconRev == SOC_SILICON_REVISION_1_2)
    {
        result = TRUE;
    }

    return result;
}

void MMCSD_phyGetTapValues(uint32_t *outputTapDelaySel, uint32_t *outputTapDelayVal,
    uint32_t *inputTapDelaySel, uint32_t *inputTapDelayVal, uint32_t phyMode, uint8_t tunedItap)
{
    switch(phyMode) {
        case MMCSD_PHY_MODE_SDR25:
            *outputTapDelaySel = 1U;
            *outputTapDelayVal = 1U;
            *inputTapDelaySel = 1U;
            *inputTapDelayVal = 16U;
            break;
        case MMCSD_PHY_MODE_SDR50:
            *outputTapDelaySel = 1U;
            *outputTapDelayVal = 8U;
            *inputTapDelaySel = 0U;
            *inputTapDelayVal = 0U;
            break;
        case MMCSD_PHY_MODE_HSSDR50:
            *outputTapDelaySel = 1U;
            *outputTapDelayVal = 1U;
            *inputTapDelaySel = 1U;
            *inputTapDelayVal = 10U;
            break;
        case MMCSD_PHY_MODE_HS200:
            *outputTapDelaySel = 1U;
            *outputTapDelayVal = 8U;
            *inputTapDelaySel = 1U;
            *inputTapDelayVal = tunedItap;
            break;
        case MMCSD_PHY_MODE_SDR104:
            *outputTapDelaySel = 1U;
            *outputTapDelayVal = 8U;
            *inputTapDelaySel = 1U;
            *inputTapDelayVal = 0U;
            break;
        case MMCSD_PHY_MODE_HSDDR50:
            *outputTapDelaySel = 1U;
            *outputTapDelayVal = 6U;
            *inputTapDelaySel = 1U;
            *inputTapDelayVal = 3U;
            break;
        case MMCSD_PHY_MODE_HS400:
            *outputTapDelaySel = 1U;
            /* Output tap delay value for 0.85V Core Voltage */
            *outputTapDelayVal = MMCSD_OTAPDLYSEL_MMC_HS400_0_85V;
            *inputTapDelaySel = 1U;
            *inputTapDelayVal = tunedItap;
            break;
        case MMCSD_PHY_MODE_DS:
        case MMCSD_PHY_MODE_HS:
            *outputTapDelaySel = 0U;
            *outputTapDelayVal = 0U;
            *inputTapDelaySel = 0U;
            *inputTapDelayVal = 0U;
            break;
        default:
            break;
    }

}


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
 *
 */

/**
 *  \file   dm_ut_clocks.c
 *
 *  \brief  Implementation of clock test functions for DM Unit Test.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/hw_include/csl_types.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/sciclient.h>
#include <dm_ut_clocks.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Clock frequency is not supported by C7X and A72 core */
#define DM_APP_UNSUPPORTED_CLOCK_FREQ                ((uint64_t) 0U)
/* Initial clock test frequency for C7X and A72 core is 500MHz */
#define DM_APP_INITIAL_CLOCK_TEST_FREQ               ((uint64_t) 500000000U)
/* Frequency step size for C7X and A72 core is 0.5MHz */
#define DM_APP_FREQ_STEP_SIZE                        ((uint64_t) 500000U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const uint32_t gDMAppProcessorClocks[][3];
extern uint32_t gDMAppProcessorClocksSize;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Function Declarations                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Internal Function Declarations                       */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Tests all the C7X and A72 core clocks for respective SOC
 * by setting frequency of each clock from 500MHz upto their
 * Max frequency supported by core in 0.5MHz increments
 */
int32_t DMApp_clockTest()
{
    int32_t checkstatus = CSL_PASS;
    uint64_t reqFreqHz = 0U;
    uint64_t respFreqHz = 0U;
    int32_t status = CSL_PASS;
    uint32_t i = 0;

    for(i = 0; i < gDMAppProcessorClocksSize; i++)
    {
        uint32_t moduleId = gDMAppProcessorClocks[i][0];
        uint32_t clockId = gDMAppProcessorClocks[i][1];
        uint64_t j = DM_APP_INITIAL_CLOCK_TEST_FREQ;

        for(j = DM_APP_INITIAL_CLOCK_TEST_FREQ; j < gDMAppProcessorClocks[i][2]; j = j+DM_APP_FREQ_STEP_SIZE)
        {
            reqFreqHz = j;
            status = Sciclient_pmQueryModuleClkFreq(moduleId, clockId, reqFreqHz, &respFreqHz, SystemP_WAIT_FOREVER);

            if(DM_APP_UNSUPPORTED_CLOCK_FREQ == respFreqHz)
            {
                /* This frequency is not supported by the clock */
                continue;
            }

            reqFreqHz = respFreqHz;

            if(CSL_PASS == status)
            {
                status = Sciclient_pmSetModuleClkFreq(moduleId, clockId, reqFreqHz, 0, SystemP_WAIT_FOREVER);

                if(CSL_PASS == status)
                {
                    status = Sciclient_pmGetModuleClkFreq(moduleId, clockId, &respFreqHz, SystemP_WAIT_FOREVER);

                    if(CSL_PASS == status)
                    {

                        if((respFreqHz < (reqFreqHz - 1)) || (respFreqHz > (reqFreqHz + 1)))
                        {
                            DebugP_log("Failed to set clock frequency of %u Hz for device %u with clock %u\n",
                                        (uint32_t)reqFreqHz,
                                        moduleId,
                                        clockId);
                            checkstatus = CSL_EFAIL;
                        }
                    }
                    else
                    {
                        DebugP_log("Sciclient_pmGetModuleClkFreq failed for device %u with clock %u of frequency %u\n",
                                    moduleId,
                                    clockId,
                                    (uint32_t)reqFreqHz);
                        checkstatus = CSL_EFAIL;
                    }
                }
                else
                {
                    DebugP_log("Sciclient_pmSetModuleClkFreq failed for device %u with clock %u of frequency %u\n",
                                moduleId,
                                clockId,
                                (uint32_t)reqFreqHz);
                    checkstatus = CSL_EFAIL;
                }

            }
            else
            {
                DebugP_log("Sciclient_pmQueryModuleClkFreq failed for device %u with clock %u of frequency %u\n",
                            moduleId,
                            clockId,
                            (uint32_t)reqFreqHz);
                checkstatus = CSL_EFAIL;
            }
        }
    }

    return checkstatus;
}

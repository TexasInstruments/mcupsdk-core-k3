/*
 *  Copyright (c) Texas Instruments Incorporated 2019-25
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
 *  \file csirx_test_misc.c
 *
 *  \brief CSIRX other misc test case file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "csirx_test.h"
#include "imx390.h"
#include <kernel/dpl/ClockP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CSIRX_TEST_OSAL_NUM_FXNS         (11U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/** \brief Log enable for CSIRX Unit Test  application */
extern uint32_t gAppTrace;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void App_wait(uint32_t wait_in_ms)
{
    ClockP_usleep(wait_in_ms*1000);
}

uint32_t App_getCurTimeInMsec(void)
{
    uint64_t curTimeMsec, curTimeUsec;

    curTimeUsec = ClockP_getTimeUsec();
    curTimeMsec = (curTimeUsec / 1000U);

    return ((uint32_t) curTimeMsec);
}

uint32_t App_getElapsedTimeInMsec(uint32_t startTime)
{
    uint32_t     elapsedTimeMsec = 0U, currTime;

    currTime = App_getCurTimeInMsec();
    if (currTime < startTime)
    {
        /* Counter overflow occured */
        elapsedTimeMsec = (0xFFFFFFFFU - startTime) + currTime + 1U;
    }
    else
    {
        elapsedTimeMsec = currTime - startTime;
    }

    return (elapsedTimeMsec);
}

/*
 *  Copyright (c) 2026 Texas Instruments Incorporated 2025
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
 *  \file dm_ut_testcases.h
 *
 *  \brief This file defines the various test cases for DM Unit Test.
 */

#ifndef DM_UT_TESTCASES_H_
#define DM_UT_TESTCASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <dm_ut_testparams.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

DMApp_TestParams gDmAppUnitTestCases[] =
{
    {
        .enableTest        = DM_APP_TEST_ENABLE,
        .testcaseId        = 1U,
        .testCaseName      = "Device Unit Test",
    },
    {
        .enableTest        = DM_APP_TEST_ENABLE,
        .testcaseId        = 2U,
        .testCaseName      = "Clock Unit Test",
    }
};

/* Number of test cases for DM APP UNIT TEST */
uint32_t gDMAppNumTests = (sizeof(gDmAppUnitTestCases)/sizeof(DMApp_TestParams));

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

/* None */

#endif /* DM_UT_TESTCASES_H_ */

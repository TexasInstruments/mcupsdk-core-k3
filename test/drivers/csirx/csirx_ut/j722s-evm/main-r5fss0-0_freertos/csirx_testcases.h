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
 *  \file csirx_testcases.h
 *
 *  \brief This file defines the test cases for CSIRX UT.
 */

#ifndef CSIRX_TEST_CASES_H_
#define CSIRX_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "csirx_test.h"
#include "csirx_testconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CSIRX_TEST_NUM_TESTCASES         ((sizeof (gCsirxTestCases)) / \
                                         (sizeof (CsirxTestParams)))
#ifndef KB
#define KB                              (1024U)
#endif

#ifndef MB
#define MB                              (KB * KB)
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various CSIRX test cases. */
static CsirxTestParams gCsirxTestCases[] =
{
    /*{
        .enableTest       = TEST_DISABLE,
        .tcId             = 0U,
        .tcName           = "Test case name",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = CSIRX_TEST_DEF_ITERATION_CNT,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId          = {
                                TASK_CFG_ID_1CH_RGB888,
                            },
    },*/
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 1U,
        .tcName           = "Single Channel RGB888 Capture",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 1U,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_1CH_RGB888,
                            },
    },
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 3531U,
        .tcName           = "IMX390: 4 Channels RAW12 Capture",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 1U,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_4CH_RAW12,
                            },
    },
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 3638U,
        .tcName           = "4 Channel RAW12 Capture, multiple create-delete sequences",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 10U,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_4CH_RAW12,
                            },
    },
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 3533U,
        .tcName           = "CSI2RX DRV Test: data on N lanes support",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 1U,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_1CH_RGB888,
                            },
    },
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 3532U,
        .tcName           = "Single Channel YUV422-8bit Capture",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 1U,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_1CH_YUV422_8BIT,
                            },
    },
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 3643U,
        .tcName           = "CSI2RX DRV Test: truncated/elongated frame detection",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 1U,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_2CH_RAW12_TRUNC_ENL_FRM,
                            },
    },
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 3639U,
        .tcName           = "Multi(2 CH) channel capture: RGB888, RAW12 ",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 1U,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_2CH_RGB888_RAW12,
                            },
    },
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 3640U,
        .tcName           = "CSI2RX DRV Test: multiple driver instances running simultaneously ",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 1U,
        .numTasks         = 2U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_1CH_RGB888,
                                TASK_CFG_ID_1CH_RGB888_INST_1,
                            },
    },
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 3541U,
        .tcName           = "CSI2RX DRV Test: Stream FIFO overflow detection",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 1U,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_2CH_RAW12_STRM_FIFO_OVERFLOW,
                            },
    },
    {
        .enableTest       = TEST_ENABLE,
        .tcId             = 3542U,
        .tcName           = "Single Channel YUV422-8bit dual pixel mode",
        .disableInfo      = NULL,
        .printEnable      = PRINT_DISABLE,
        .profilingEnable  = PRF_DISABLE,
        .tcType           = (CSIRX_TCT_SANITY | CSIRX_TCT_FUNCTIONAL),
        .dcEnable         = DATA_CHECK_DISABLE,
        .iterationCnt     = 1U,
        .numTasks         = 1U,
        .testType         = {
                                CSIRX_TEST_TYPE_CAPTURE_ONLY,
                            },
        .taskCfgId        = {
                                TASK_CFG_ID_1CH_YUV422_8BIT_DUAL_PIXEL,
                            },
    },
};

#ifdef __cplusplus
}
#endif

#endif  /* CSIRX_TEST_CASES_H_ */

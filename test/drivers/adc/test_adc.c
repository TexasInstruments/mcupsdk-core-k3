/*
 * Copyright (C) 2021-26 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file test_adc.c
 * \brief Main test runner for ADC driver test cases.
 */

/*===================================================================*/
/*                          Include Files                            */
/*===================================================================*/

#include "test_adc.h"
#include "test_adc_testCases.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/*===================================================================*/
/*                          Macro Defines                            */
/*===================================================================*/

/* None */

/*===================================================================*/
/*                          Typedefs                                 */
/*===================================================================*/

/* None */

/*===================================================================*/
/*                         Global Variables                          */
/*===================================================================*/

static test_adc_testcaseParams_t *TestAdc_testParams;

/*===================================================================*/
/*                         Function Declarations                     */
/*===================================================================*/

void TestAdc_runTestcase(void *args);
void TestAdc_tcResultInit(void);

/*===================================================================*/
/*                      Function Definitions                        */
/*===================================================================*/

/**
 * \brief  Main RTOS task entry point for ADC test suite.
 *
 *  Test Category: Functionality
 *
 *   Initialises Unity, resets all test-case results, then iterates over
 *   the global test-case table and dispatches each test through
 *   TestAdc_runTestcase via RUN_TEST.
 *
 *  \param args  Task argument (unused)
 *
 * \return None.
 */
void test_main(void *args)
{
    int32_t  testcaseIdx;

    UNITY_BEGIN();

    /* Initialization for tests */
    TestAdc_tcResultInit();

    /* Run all tests */
    for(testcaseIdx = 0; testcaseIdx < ADC_NUM_TESTCASES; testcaseIdx++)
    {
        TestAdc_testParams = &gADCTestcaseParams[testcaseIdx];
        RUN_TEST(TestAdc_runTestcase, TestAdc_testParams->testcaseId, NULL);
    }

    UNITY_END();

    return;
}

/* Unity framework required information */
void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * \brief  Unity test runner callback that dispatches a single ADC test case.
 *
 *  Test Category: Functionality
 *
 *   Logs the test ID and description, then routes execution to the
 *   appropriate mode-specific main function based on adcConfigParams.testMode
 *   and testCaseName string matching.
 *
 *  \param args  Unused argument
 *
 * \return None.
 */
void TestAdc_runTestcase(void *args)
{
    DebugP_log("\r\nTest ID : MCU-SDK %u \r\n", TestAdc_testParams->testcaseId);
    DebugP_log("Test Description : %s \r\n", TestAdc_testParams->testCaseName);

    if(TestAdc_testParams->adcConfigParams.testMode == ADC_TEST_MODE_CPU)
    {
        TestAdc_cpuMode_main(TestAdc_testParams);
    }
    else if(TestAdc_testParams->adcConfigParams.testMode == ADC_TEST_MODE_POLLING)
    {
        TestAdc_pollingMode_main(TestAdc_testParams);
    }
#ifdef SOC_AM275X
    else if(TestAdc_testParams->adcConfigParams.testMode == ADC_TEST_MODE_API)
    {
        /* Route API tests based on test name */
        if (strstr(TestAdc_testParams->testCaseName, "setStepParams") != NULL ||
            strstr(TestAdc_testParams->testCaseName, "stepEnable") != NULL ||
            strstr(TestAdc_testParams->testCaseName, "clearAllSteps") != NULL ||
            strstr(TestAdc_testParams->testCaseName, "ADC start EN=") != NULL ||
            strstr(TestAdc_testParams->testCaseName, "stepIdTagEnable") != NULL ||
            strstr(TestAdc_testParams->testCaseName, "change step params while active") != NULL)
        {
            TestAdc_testParams->testResult = TestAdc_stepControl_main(TestAdc_testParams);
        }
        else if (strstr(TestAdc_testParams->testCaseName, "getFIFOData") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "getFIFOWordCount") != NULL ||
                 (strstr(TestAdc_testParams->testCaseName, "threshold") != NULL &&
                  strstr(TestAdc_testParams->testCaseName, "below minimum") == NULL &&
                  strstr(TestAdc_testParams->testCaseName, "above maximum") == NULL) ||
                 strstr(TestAdc_testParams->testCaseName, "DMA access") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "change threshold while active") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "CPU poll overflow") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "CPU poll underflow") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "DMA overflow") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "DMA underflow") != NULL)
        {
            TestAdc_testParams->testResult = TestAdc_fifoDma_main(TestAdc_testParams);
        }
        else if (strstr(TestAdc_testParams->testCaseName, "enableIntr") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "disableIntr") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "getIntrStatus") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "clearIntrStatus") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "writeEOI") != NULL)
        {
            TestAdc_testParams->testResult = TestAdc_intrEoi_main(TestAdc_testParams);
        }
        else if (strstr(TestAdc_testParams->testCaseName, "setGetRange") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "setRange") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "range violation") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "getSequencerStatus") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "change range while active") != NULL)
        {
            TestAdc_testParams->testResult = TestAdc_rangeStatus_main(TestAdc_testParams);
        }
        else if (strstr(TestAdc_testParams->testCaseName, "get CPU FIFO threshold") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "get DMA FIFO threshold") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "DMA line config") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "FIFO data read sequential") != NULL ||
                 strstr(TestAdc_testParams->testCaseName, "DMA transfer completion") != NULL)
        {
            TestAdc_testParams->testResult = TestAdc_fifoDma_main(TestAdc_testParams);
        }
        else if (strstr(TestAdc_testParams->testCaseName, "idle mode") != NULL)
        {
            TestAdc_testParams->testResult = TestAdc_powerInit_main(TestAdc_testParams);
        }
        else
        {
            TestAdc_testParams->testResult = TestAdc_powerInit_main(TestAdc_testParams);
        }
    }
#endif /* #ifdef SOC_AM275X */
    else
    {
        TestAdc_pollingMode_main(TestAdc_testParams);
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestAdc_testParams->testResult);
}

/**
 * \brief  Initialises all test-case result fields to SystemP_FAILURE.
 *
 *  Test Category: Functionality
 *
 *   Iterates over the global test-case table and sets each testResult
 *   to SystemP_FAILURE so that any test not explicitly run is reported
 *   as failed.
 *
 *  \param None
 *
 * \return None.
 */
void TestAdc_tcResultInit(void)
{
    uint32_t loopCnt;
    test_adc_testcaseParams_t * testParams;

    for(loopCnt = 0 ; loopCnt < ADC_NUM_TESTCASES; loopCnt++)
    {
        testParams              = &gADCTestcaseParams[loopCnt];
        testParams->testResult  = SystemP_FAILURE;
    }
}

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
 */

/**
 *  \file  dm_ut_testparser.c
 *
 *  \brief Implementation of parser functions used by the DM_UT applications.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <drivers/hw_include/csl_types.h>
#include <kernel/dpl/DebugP.h>
#include <dm_ut_devices.h>
#include <dm_ut_clocks.h>
#include <dm_ut_testparser.h>
#include <dm_ut_testcases.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DM_APP_PRINT_BUFFER_SIZE   (256U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Function Declarations                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                     Internal Function Declarations                         */
/* ========================================================================== */

/**
 * \brief   Print main menu.
 *
 * \param   None.
 *
 * \return  None
 */
static void DMApp_showMainMenu(void);

/**
 * \brief   Fetch testcase number to be run from user.
 *
 * \param   None.
 *
 * \return  Testcase number to be run.
 */
static uint32_t DMApp_getTestNum(void);

/**
 * \brief   Get the index of the testcase in gDmAppUnitTestCases to run from respective DM application.
 *
 * \param   testcaseId        Testcase Id to run.
 *
 * \return  testcaseIdx       Testcase index to run
 */
static int32_t DMApp_getIndex(uint32_t testcaseId);

/**
 * \brief   Prints info and summary of each testcase.
 *
 * \param   testParams        Structure to details of testcase to be run.
 *
 * \return  None.
 */
static void DMApp_run(DMApp_TestParams *testParams);

/**
 * \brief   Run the testcase.
 *
 * \param   testParams        Structure to details of testcase to be run.
 *
 * \return  None.
 */
static int32_t DMApp_testMain(DMApp_TestParams *testParams);

/**
 * \brief   Print DM testcase names.
 *
 * \param   None.
 *
 * \return  None
 */
static void DMApp_printTestName(void);

/**
 * \brief   Print DM testcase details.
 *
 * \param   testId        TestcaseID for which details are to be printed.
 *
 * \return  None
 */
static void DMApp_printTestDetails(uint32_t testId);

/**
 * \brief   Initialize the details of DM testcase results.
 *
 * \param   None.
 *
 * \return  None
 */
static void DMApp_resultInit(void);

/**
 * \brief   Print DM Test Case Results.
 *
 * \param   None.
 *
 * \return  None
 */
static void DMApp_printResults(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void DMApp_parser(void)
{
    uint32_t testcaseId;
    uint32_t numTCPass, numTCFail, totalTCRun, done = 0U;
    int32_t  testcaseIdx, testId;
    char  option = '1';
    DMApp_TestParams *testParams;
    DMApp_resultInit();

    while(1U != done)
    {
        DMApp_showMainMenu();
        DebugP_log("\nEnter your choice: ");
        DebugP_scanf("%c", &option);
        DebugP_log("%c\n", option);
        numTCPass  = 0U;
        numTCFail  = 0U;
        totalTCRun = 0U;
        switch(option)
        {
            case DM_APP_RUN_TEST_ID:
                DMApp_printTestName();
                DebugP_log("\nEnter testcase ID to run: ");
                testId      = DMApp_getTestNum();
                testcaseIdx = DMApp_getIndex(testId);

                if(testcaseIdx < 0)
                {
                    DebugP_log("Invalid test case Id.\n");
                }
                else if(DM_APP_TEST_ENABLE == gDmAppUnitTestCases[testcaseIdx].enableTest)
                {
                    testParams = &gDmAppUnitTestCases[testcaseIdx];
                    totalTCRun++;
                    DMApp_run(testParams);

                    if(CSL_PASS == testParams->testResult)
                    {
                        numTCPass++;
                    }
                    else
                    {
                        numTCFail++;
                    }
                }

                DebugP_log("\nDM_UT: Total Testcases run:%u/%u\n", totalTCRun, gDMAppNumTests);
                DebugP_log("DM_UT: Number of Testcases Passed:%u\n", numTCPass);
                DebugP_log("DM_UT: Number of Testcases Failed:%u\n", numTCFail);

                if((numTCFail == 0U) && (numTCPass != 0U))
                {
                    DebugP_log("\nAll tests have PASSED.\n");
                }
                else if((numTCPass == 0U) && (numTCFail == 0U))
                {
                    DebugP_log("\nThis testcase is not enabled.\n");
                }
                else
                {
                    DebugP_log("\nSome of the Test-cases have FAILED.\n");
                }

                break;

            case DM_APP_RUN_TESTS_ALL:

                for(testcaseId = 0U; testcaseId < gDMAppNumTests; testcaseId++)
                {
                    testParams = &gDmAppUnitTestCases[testcaseId];

                    if(DM_APP_TEST_ENABLE == testParams->enableTest)
                    {
                        totalTCRun++;
                        DMApp_run(testParams);

                        if(CSL_PASS == testParams->testResult)
                        {
                            numTCPass++;
                        }
                        else
                        {
                            numTCFail++;
                        }
                    }
                }

                DebugP_log("\nDM_UT: Total Testcases run:%u/%u\n", totalTCRun, gDMAppNumTests);
                DebugP_log("DM_UT: Number of Testcases Passed:%u\n", numTCPass);
                DebugP_log("DM_UT: Number of Testcases Failed:%u\n", numTCFail);
                DMApp_printResults();

                if((numTCFail == 0U) && (numTCPass != 0U))
                {
                    DebugP_log("\nAll tests have PASSED.\n");
                }
                else if((numTCPass == 0U) && (numTCFail == 0U))
                {
                    DebugP_log("\nTestcase are not enabled.\n");
                }
                else
                {
                    DebugP_log("\nSome of the Test-cases have FAILED.\n");
                }
                done = 1U;
                break;

            case DM_APP_PRINT_ALL_TESTS:
                DMApp_printTestName();
                break;

            case DM_APP_PRINT_TEST_ID:
                DebugP_log("\nEnter testcase ID: ");
                testId      = DMApp_getTestNum();
                testcaseIdx = DMApp_getIndex(testId);

                if(testcaseIdx < 0U)
                {
                    DebugP_log("Invalid test case Id.");
                }
                else
                {
                    DMApp_printTestDetails(testcaseIdx);
                }

                break;

            case DM_APP_PRINT_RESULTS:
                DMApp_printResults();
                break;

            case DM_APP_PARSER_QUIT:
                DebugP_log("Exiting DM_UT Test application.\n");
                done = 1U;
                break;

            default:
                DebugP_log("Unsupported Option. Please try again.\n");
                break;
        }
    }
}

/* ========================================================================== */
/*                        Internal Function Definitions                       */
/* ========================================================================== */

static void DMApp_resultInit(void)
{
    uint32_t loopCnt;
    DMApp_TestParams *testParams;

    for(loopCnt = 0U; loopCnt < gDMAppNumTests; loopCnt++)
    {
        testParams             = &gDmAppUnitTestCases[loopCnt];
        testParams->isRun      = CSL_EFAIL;
        testParams->testResult = CSL_EFAIL;
    }
}

static void DMApp_showMainMenu(void)
{
    DebugP_log("\n=====================\n");
    DebugP_log("DM UT Select\n");
    DebugP_log("=======================\n");
    DebugP_log("\nDM UT main menu:\n");
    DebugP_log("1: Manual testing (select specific test case to run)\n");
    DebugP_log("2. Complete testing.\n");
    DebugP_log("d: Display test cases.\n");
    DebugP_log("t: Display test case Details.\n");
    DebugP_log("g: Generate test report.\n");
    DebugP_log("q: Quit.\n");
}

static uint32_t DMApp_getTestNum(void)
{
    uint32_t number = 0U;
    DebugP_scanf("%u", &number);
    return number;
}

static int32_t DMApp_getIndex(uint32_t testcaseId)
{
    int32_t  testcaseIdx = -1;
    uint32_t testCnt;
    const DMApp_TestParams *testParams;
    testParams = &gDmAppUnitTestCases[0];

    for(testCnt = 0U; testCnt < gDMAppNumTests; testCnt++)
    {
        if(testcaseId == testParams[testCnt].testcaseId)
        {
            testcaseIdx = testCnt;
            break;
        }
    }

    return testcaseIdx;
}

static void DMApp_run(DMApp_TestParams *testParams)
{
    DebugP_log( "\n|TEST START|:: %u ::\n", testParams->testcaseId);
    DebugP_log( "|TEST PARAM|:: %s ::\n", testParams->testCaseName);
    DebugP_log("--------------------------------------------------------------\n");
    DebugP_log("=========================RUNNING==============================\n");
    DMApp_testMain(testParams);
    testParams->isRun = CSL_PASS;
    DebugP_log("\n======================FINISHED==========================\n");

    if(0U == testParams->testResult)
    {
        DebugP_log( "|TEST RESULT|PASS|%u|\n", testParams->testcaseId);
    }
    else
    {
        DebugP_log( "|TEST RESULT|FAIL|%u|\n", testParams->testcaseId);
    }

    DebugP_log( "|TEST INFO|:: %s ::\n", testParams->testCaseName);
    DebugP_log( "|TEST END|:: %u ::\n", testParams->testcaseId);
}

static int32_t DMApp_testMain(DMApp_TestParams *testParams)
{
    switch(testParams->testcaseId)
    {
        case DM_APP_DEVICE_TEST:
            testParams->testResult = DMApp_deviceTest();
            break;

        case DM_APP_CLOCK_TEST:
            testParams->testResult = DMApp_clockTest();
            break;

        default:
            testParams->testResult = CSL_EFAIL;
            break;
    }

    return 0;
}

static void DMApp_printResults(void)
{
    uint32_t loopCnt;
    int32_t  testcaseIdx;
    DMApp_TestParams *testParams;
    char  testResult[10];
    DebugP_log("-----------------------------------------------------------------------------------------------------------\r\n");
    DebugP_log("ID\t         Description\t\t\t                         Status\r\n");
    DebugP_log("-----------------------------------------------------------------------------------------------------------\r\n");

    for(loopCnt = 0U; loopCnt < gDMAppNumTests; loopCnt++)
    {
        testParams  = &gDmAppUnitTestCases[loopCnt];
        testcaseIdx = testParams->testcaseId;

        if(CSL_PASS == testParams->testResult)
        {
            strcpy(testResult, "PASS");
        }
        else if(CSL_PASS == testParams->isRun)
        {
            strcpy(testResult, "FAIL");
        }
        else
        {
            strcpy(testResult, "NRY");
        }

        DebugP_log("%d\t         %s\t                         ",testcaseIdx, testParams->testCaseName);
        DebugP_log("%s\r\n", testResult);
    }

    DebugP_log("\n-----------------------------------------------------------------------------------------------------------\r\n");
}

static void DMApp_printTestName(void)
{
    uint32_t loopCnt;
    const DMApp_TestParams *testParams;
    DebugP_log( "DM_UT Testcase:\n");
    DebugP_log("--------------------------------------------------------------\n");
    DebugP_log( "TC Id\tTC name\n");
    DebugP_log("--------------------------------------------------------------\n");

    for(loopCnt = 0U; loopCnt < gDMAppNumTests; loopCnt++)
    {
        testParams = &gDmAppUnitTestCases[loopCnt];
        DebugP_log( "%d\t%s\n", testParams->testcaseId, testParams->testCaseName);
    }

    DebugP_log("--------------------------------------------------------------\n");
}

static void DMApp_printTestDetails(uint32_t testId)
{
    const DMApp_TestParams *testParams;
    testParams = &gDmAppUnitTestCases[testId];
    DebugP_log("\nTestcase Id : %d\n", testParams->testcaseId);
    DebugP_log("Testcase Name : %s", testParams->testCaseName);
    DebugP_log("\nTestcase Enabled(0-Disabled/1-Enabled) : %d", testParams->enableTest);
}

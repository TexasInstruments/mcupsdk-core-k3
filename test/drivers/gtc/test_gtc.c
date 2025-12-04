/*
 *  Copyright (C) 2018-2026 Texas Instruments Incorporated
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

 /*===================================================================*/
 /* 					Include Files 					              */
 /*===================================================================*/

#include "test_gtc.h"

/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/


/*===================================================================*/
/* 					Function Declarations		                     */
/*===================================================================*/

/* Main function running the single threaded test case */
static void TestGtc_stTestcase(void);

/* Testcase to verify GTC count functionality */
static void test_gtc_count(void *args);
#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)
/* Testcase to verify long duration jitter */
static void TestGtc_longDurationJitter(void *args);
#endif

/*===================================================================*/
/* 					Function Definitions		                     */
/*===================================================================*/

/**
 * @brief Main GTC driver unit test entry point.
 *
 * Initializes the Unity test framework, runs all registered Global Timer Counter (GTC)
 * API validation tests, and finalizes the Unity framework. This includes single-threaded
 * tests for counter accuracy and long duration jitter, and optionally multithreaded tests
 * if enabled. The function serves as the main dispatcher for GTC test execution.
 *
 * @param[in] args Optional user argument (unused in current implementation).
 *
 * @return void
 */
void test_main(void *args)
{
    UNITY_BEGIN();

    TestGtc_stTestcase();
#if defined(ENABLE_MT_TESTS)
    TestGtc_mtTestcase();
#endif

    UNITY_END();

    return;
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
    /*Nothing to setup*/
}

void tearDown(void)
{
    /*Nothing to tear down*/
}

/**
 * @brief Main single-threaded GTC test dispatcher.
 *
 * Runs all single-threaded Global Timer Counter (GTC) unit tests using the Unity framework.
 * This includes tests for counter accuracy and long duration jitter. Each test is invoked
 * with a unique test case ID and optional arguments. Results are reported through Unity.
 *
 * Test Steps:
 * 1. Run the GTC counter accuracy test.
 * 2. Run the long duration jitter test.
 *
 * @return void
 */
static void TestGtc_stTestcase(void)
{
    RUN_TEST(test_gtc_count, 2096, NULL);
#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)
    RUN_TEST(TestGtc_longDurationJitter, 9400, NULL);
#endif
}

/**
 * @brief Single-threaded GTC counter accuracy test.
 *
 * Initializes the Global Timer Counter (GTC), retrieves the GTC clock frequency,
 * samples the counter before and after a 1-second sleep, and verifies that the
 * observed increment is within an acceptable tolerance of the expected value
 * based on the clock rate.
 *
 * Test Steps:
 * 1. Initialize the GTC module.
 * 2. Retrieve the GTC clock frequency.
 * 3. Record the initial 64-bit GTC counter value.
 * 4. Sleep for 1 second.
 * 5. Record the final 64-bit GTC counter value.
 * 6. Verify that the difference is within tolerance of the expected increment (clkRate).
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void test_gtc_count(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint64_t gtccount1, gtccount2;
    uint64_t clkRate = 0;

    retVal = GTC_init();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

#if defined(SOC_AM62LX)
    retVal = SOC_moduleGetClockFrequency(AM62LX_DEV_WKUP_GTC0, AM62LX_DEV_WKUP_GTC0_GTC_CLK, &clkRate);
#else
    retVal = SOC_moduleGetClockFrequency(TISCI_DEV_WKUP_GTC0, TISCI_DEV_WKUP_GTC0_GTC_CLK, &clkRate);
#endif
   TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    gtccount1 = GTC_getCount64();
    ClockP_sleep(1);
    gtccount2 = GTC_getCount64();

    TEST_ASSERT_UINT32_WITHIN( 1000000, clkRate, gtccount2 - gtccount1);
}

#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)
/**
 * @brief Single-threaded GTC long duration jitter test.
 *
 * This test case measures the Global Timer Counter (GTC) value over a long duration
 * (60 seconds) and verifies that the counter increments as expected based on the
 * known clock rate. The test checks that the difference between the initial and final
 * counter values is within an acceptable range of the expected increment, accounting
 * for potential jitter.
 *
 * Test Steps:
 * 1. Initialize the GTC module.
 * 2. Retrieve the GTC clock frequency.
 * 3. Record the initial GTC counter value.
 * 4. Sleep for 60 seconds.
 * 5. Record the final GTC counter value.
 * 6. Verify that the difference between the final and initial counter values
 *    is within an acceptable range of the expected increment based on the clock rate.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestGtc_longDurationJitter(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint64_t gtcCount0 = 0;
    uint64_t gtcCount1 = 0;
    uint64_t clkRate = 0;

    /* Init GTC module */
    retVal = GTC_init();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Get GTC clock frequency */
    retVal = SOC_moduleGetClockFrequency(TISCI_DEV_WKUP_GTC0, TISCI_DEV_WKUP_GTC0_GTC_CLK, &clkRate);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Record initial GTC counter value */
    gtcCount0 = GTC_getCount64();
    ClockP_sleep(60);
    /* Record final GTC counter value */
    gtcCount1 = GTC_getCount64();

    /* Verify counter increment is within expected range */
    TEST_ASSERT_UINT32_WITHIN(1000000, clkRate * 60, gtcCount1 - gtcCount0);
}

#endif


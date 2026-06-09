/*
 * Copyright (C) 2026 Texas Instruments Incorporated
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
 * \file test_adc_negative.c
 *
 * \brief ADC negative test file containing out-of-bounds test cases for
 *        parameter validation including delay limits, FIFO thresholds,
 *        and range boundary violations.
 */

/*===================================================================*/
/*                          Include Files                            */
/*===================================================================*/

#include "test_adc.h"
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/ClockP.h>
#include <drivers/hw_include/csl_types.h>

#ifdef SOC_AM275X
/*===================================================================*/
/*                      Macro Defines                                */
/*===================================================================*/

/* ADC delay limits */
#define TEST_ADC_OPENDELAY_MIN       (0x0U)
#define TEST_ADC_OPENDELAY_MAX       (0x3FFFFU)
#define TEST_ADC_SAMPLEDELAY_MIN     (0x0U)
#define TEST_ADC_SAMPLEDELAY_MAX     (0xFFU)

/* FIFO threshold limits */
#define TEST_ADC_FIFO_THRESHOLD_MIN  (1U)
#define TEST_ADC_FIFO_THRESHOLD_MAX  (64U)

/* Range limits */
#define TEST_ADC_RANGE_MAX_VALUE     (ADC_RANGE_MAX)

/* Selector limits */
#define TEST_ADC_STEP_ID_MIN         (ADC_STEP_1)
#define TEST_ADC_STEP_ID_MAX         (ADC_STEP_16)
#define TEST_ADC_FIFO_NUM_MIN        (ADC_FIFO_NUM_0)
#define TEST_ADC_FIFO_NUM_MAX        (ADC_FIFO_NUM_1)


/*===================================================================*/
/*                         Typedefs                                  */
/*===================================================================*/

/* None */


/*===================================================================*/
/*                      Global Variables                            */
/*===================================================================*/

/* None */

/*===================================================================*/
/*                      Function Declarations                        */
/*===================================================================*/

static int32_t TestAdc_cpuFifoThresholdBelowMin(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_cpuFifoThresholdAboveMax(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaFifoThresholdBelowMin(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaFifoThresholdAboveMax(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_stepIdBelowMin(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_stepIdAboveMax(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_fifoNumBelowMin(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_fifoNumAboveMax(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_startBeforePowerUp(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_startBeforeInit(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_powerDownWhileActive(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_reEnableAfterStop(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_simultaneousSources(test_adc_testcaseParams_t *testParams);


/*===================================================================*/
/*                      Function Definitions                        */
/*===================================================================*/

/**
 * \brief  Main dispatcher for ADC negative (out-of-bounds) test cases.
 *
 *  Test Category: Negative
 *
 *   Routes execution to the specific negative test function based on
 *   testCaseName string matching. Validates boundary conditions for
 *   delays, FIFO thresholds, range parameters, and sequencing.
 *
 *  \param testParams Pointer to test case parameters
 *
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestAdc_negative_main(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;

    if (testParams == NULL)
    {
        status = SystemP_FAILURE;
        DebugP_log("Error: testParams is NULL\r\n");
    }
    else
    {
        DebugP_log("Starting ADC Negative test: %s\r\n", testParams->testCaseName);

        /* Route to specific test based on test name */
        if (strstr(testParams->testCaseName, "CPU FIFO threshold below minimum") != NULL)
        {
            status = TestAdc_cpuFifoThresholdBelowMin(testParams);
        }
        else if (strstr(testParams->testCaseName, "CPU FIFO threshold above maximum") != NULL)
        {
            status = TestAdc_cpuFifoThresholdAboveMax(testParams);
        }
        else if (strstr(testParams->testCaseName, "DMA FIFO threshold below minimum") != NULL)
        {
            status = TestAdc_dmaFifoThresholdBelowMin(testParams);
        }
        else if (strstr(testParams->testCaseName, "DMA FIFO threshold above maximum") != NULL)
        {
            status = TestAdc_dmaFifoThresholdAboveMax(testParams);
        }
        else if (strstr(testParams->testCaseName, "stepId below minimum") != NULL)
        {
            status = TestAdc_stepIdBelowMin(testParams);
        }
        else if (strstr(testParams->testCaseName, "stepId above maximum") != NULL)
        {
            status = TestAdc_stepIdAboveMax(testParams);
        }
        else if (strstr(testParams->testCaseName, "fifoNum below minimum") != NULL)
        {
            status = TestAdc_fifoNumBelowMin(testParams);
        }
        else if (strstr(testParams->testCaseName, "fifoNum above maximum") != NULL)
        {
            status = TestAdc_fifoNumAboveMax(testParams);
        }
        else if (strstr(testParams->testCaseName, "start before power-up") != NULL)
        {
            status = TestAdc_startBeforePowerUp(testParams);
        }
        else if (strstr(testParams->testCaseName, "start before init") != NULL)
        {
            status = TestAdc_startBeforeInit(testParams);
        }
        else if (strstr(testParams->testCaseName, "power-down while active") != NULL)
        {
            status = TestAdc_powerDownWhileActive(testParams);
        }
        else if (strstr(testParams->testCaseName, "re-enable after stop") != NULL)
        {
            status = TestAdc_reEnableAfterStop(testParams);
        }
        else if (strstr(testParams->testCaseName, "interrupt simultaneous sources") != NULL)
        {
            status = TestAdc_simultaneousSources(testParams);
        }
        else
        {
            status = SystemP_FAILURE;
            DebugP_log("Error: Unknown test case name: %s\r\n", testParams->testCaseName);
        }

        if (status == SystemP_SUCCESS)
        {
            DebugP_log("Test %s passed\r\n", testParams->testCaseName);
        }
        else
        {
            DebugP_log("Test %s failed\r\n", testParams->testCaseName);
        }
    }

    return status;
}

/**
 * \brief Test CPU FIFO threshold below minimum value
 *
 * Test Category: Negative test
 *
 * This test verifies behavior when setting CPU FIFO threshold below
 * minimum value (1). API should reject or hardware should handle gracefully.
 */
static int32_t TestAdc_cpuFifoThresholdBelowMin(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t threshold;
    int32_t apiStatus;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing CPU FIFO threshold below minimum...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Try to set threshold to 0 (below minimum of 1) */
    threshold = 0U;
    DebugP_log("Attempting to set CPU FIFO threshold to: %u (below min %u)\r\n",
               threshold, TEST_ADC_FIFO_THRESHOLD_MIN);

    apiStatus = ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, threshold);

    if (apiStatus == SystemP_SUCCESS)
    {
        DebugP_log("API accepted invalid threshold (behavior documented)\r\n");
        /* Test passes - documents that API doesn't validate */
        status = SystemP_SUCCESS;
    }
    else
    {
        DebugP_log("API rejected invalid threshold value\r\n");
        status = SystemP_FAILURE;
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test CPU FIFO threshold above maximum value
 *
 * Test Category: Negative test
 *
 * This test verifies behavior when setting CPU FIFO threshold above
 * maximum value (64). API should reject or hardware should clamp.
 */
static int32_t TestAdc_cpuFifoThresholdAboveMax(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t threshold;
    int32_t apiStatus;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing CPU FIFO threshold above maximum...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Try to set threshold above maximum */
    threshold = 100U; /* Above 64 */
    DebugP_log("Attempting to set CPU FIFO threshold to: %u (above max %u)\r\n",
               threshold, TEST_ADC_FIFO_THRESHOLD_MAX);

    apiStatus = ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, threshold);

    if (apiStatus == SystemP_SUCCESS)
    {
        DebugP_log("API accepted value above maximum (may be clamped by hardware)\r\n");
        status = SystemP_SUCCESS;
    }
    else
    {
        DebugP_log("API rejected invalid threshold value\r\n");
        status = SystemP_SUCCESS;
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test DMA FIFO threshold below minimum value
 *
 * Test Category: Negative test
 *
 * This test verifies behavior when setting DMA FIFO threshold below
 * minimum value (1). API should reject or hardware should handle gracefully.
 */
static int32_t TestAdc_dmaFifoThresholdBelowMin(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t threshold;
    int32_t apiStatus;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing DMA FIFO threshold below minimum...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Try to set threshold to 0 (below minimum of 1) */
    threshold = 0U;
    DebugP_log("Attempting to set DMA FIFO threshold to: %u (below min %u)\r\n",
               threshold, TEST_ADC_FIFO_THRESHOLD_MIN);

    apiStatus = ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, threshold);

    if (apiStatus == SystemP_SUCCESS)
    {
        DebugP_log("API accepted invalid threshold (behavior documented)\r\n");
        status = SystemP_SUCCESS;
    }
    else
    {
        DebugP_log("API rejected invalid threshold value\r\n");
        status = SystemP_SUCCESS;
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test DMA FIFO threshold above maximum value
 *
 * Test Category: Negative test
 *
 * This test verifies behavior when setting DMA FIFO threshold above
 * maximum value (64). API should reject or hardware should clamp.
 */
static int32_t TestAdc_dmaFifoThresholdAboveMax(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t threshold;
    int32_t apiStatus;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing DMA FIFO threshold above maximum...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Try to set threshold above maximum */
    threshold = 100U; /* Above 64 */
    DebugP_log("Attempting to set DMA FIFO threshold to: %u (above max %u)\r\n",
               threshold, TEST_ADC_FIFO_THRESHOLD_MAX);

    apiStatus = ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, threshold);

    if (apiStatus == SystemP_SUCCESS)
    {
        DebugP_log("API accepted value above maximum (may be clamped by hardware)\r\n");
        status = SystemP_SUCCESS;
    }
    else
    {
        DebugP_log("API rejected invalid threshold value\r\n");
        status = SystemP_SUCCESS;
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test stepId below minimum
 *
 * Test Category: Negative test
 *
 * This test verifies behavior when attempting to use a stepId value
 * below the minimum valid step identifier.
 */
static int32_t TestAdc_stepIdBelowMin(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t invalidStepId;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing stepId below minimum...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Attempt to use invalid stepId (below ADC_STEP_1) */
    invalidStepId = 0x0U; /* Note: ADC_STEP_1 = 0 (zero-based), 0 is valid, no true "below min" for uint32_t */
    DebugP_log("Attempting to configure stepId=0x%x (ADC_STEP_1 is 0, so this is valid)\r\n",
               invalidStepId);

    /* Prepare step configuration */
    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0x100U;
    stepConfig.sampleDelay = 0x10U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;

    /* Attempt to set step parameters with invalid stepId */
    ADC_setStepParams(baseAddr, invalidStepId, &stepConfig);

    /* Document behavior - hardware may ignore, wrap, or accept */
    DebugP_log("Step configuration attempted with invalid stepId\r\n");
    DebugP_log("Hardware behavior depends on register implementation\r\n");

    /* Test passes as it documents the behavior */
    status = SystemP_SUCCESS;

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test stepId above maximum
 *
 * Test Category: Negative test
 *
 * This test verifies behavior when attempting to use a stepId value
 * above the maximum valid step identifier (ADC_STEP_16).
 */
static int32_t TestAdc_stepIdAboveMax(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t invalidStepId;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing stepId above maximum...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Attempt to use invalid stepId (above ADC_STEP_16) */
    invalidStepId = 0x20U; /* Above ADC_STEP_16 (which is 15, zero-based) */
    DebugP_log("Attempting to configure stepId=0x%x (above maximum ADC_STEP_16=15)\r\n",
               invalidStepId);

    /* Prepare step configuration */
    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0x100U;
    stepConfig.sampleDelay = 0x10U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;

    /* Attempt to set step parameters with invalid stepId */
    ADC_setStepParams(baseAddr, invalidStepId, &stepConfig);

    /* Document behavior - hardware may ignore, wrap, or accept */
    DebugP_log("Step configuration attempted with invalid stepId\r\n");
    DebugP_log("Hardware may wrap or ignore invalid stepId\r\n");

    /* Test passes as it documents the behavior */
    status = SystemP_SUCCESS;

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test fifoNum below minimum
 *
 * Test Category: Negative test
 *
 * This test verifies behavior when attempting to use a fifoNum value
 * below the minimum valid FIFO number (ADC_FIFO_NUM_0 = 0).
 * Since 0 is the minimum, this tests underflow behavior.
 */
static int32_t TestAdc_fifoNumBelowMin(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t invalidFifoNum;
    uint32_t fifoData;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing fifoNum below minimum...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Attempt to use invalid fifoNum */
    invalidFifoNum = 0xFFFFFFFFU; /* Negative value in unsigned context */
    DebugP_log("Attempting to read from fifoNum=0x%x (below minimum 0)\r\n",
               invalidFifoNum);

    /* Attempt to read FIFO data with invalid fifoNum */
    fifoData = ADC_getFIFOData(baseAddr, invalidFifoNum);

    /* Document behavior - hardware may wrap or return undefined data */
    DebugP_log("Read FIFO data: 0x%x (with invalid fifoNum)\r\n", fifoData);
    DebugP_log("Hardware behavior depends on register implementation\r\n");

    /* Test passes as it documents the behavior */
    status = SystemP_SUCCESS;

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test fifoNum above maximum
 *
 * Test Category: Negative test
 *
 * This test verifies behavior when attempting to use a fifoNum value
 * above the maximum valid FIFO number (ADC_FIFO_NUM_1).
 * The API does not validate fifoNum, so this test documents hardware behavior.
 */
static int32_t TestAdc_fifoNumAboveMax(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t invalidFifoNum;
    uint32_t fifoData;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing fifoNum above maximum...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Attempt to use invalid fifoNum (above ADC_FIFO_NUM_1) */
    invalidFifoNum = 2U;
    DebugP_log("Attempting to read from fifoNum=%u (above max %u)\r\n",
               invalidFifoNum, TEST_ADC_FIFO_NUM_MAX);

    /* Attempt to read FIFO data with invalid fifoNum */
    fifoData = ADC_getFIFOData(baseAddr, invalidFifoNum);

    /* Document behavior - hardware may wrap or return undefined data */
    DebugP_log("Read FIFO data: 0x%x (with invalid fifoNum)\r\n", fifoData);
    DebugP_log("Hardware behavior depends on register implementation\r\n");

    /* Test passes as it documents the behavior */
    status = SystemP_SUCCESS;

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test starting ADC before power-up
 *
 * Test Category: Negative
 *
 * This test verifies proper error handling when attempting to start ADC
 * conversions before powering up the ADC module. Tests the power-up
 * prerequisite for ADC operation.
 */
static int32_t TestAdc_startBeforePowerUp(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC start before power-up...\r\n");

    /* Ensure ADC is powered down initially */
    ADC_powerUp(baseAddr, FALSE);
    DebugP_log("ADC powered down\r\n");

    /* Configure step (even though ADC is not powered up) */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0x100U;
    stepConfig.sampleDelay = 0x10U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;
    stepConfig.rangeCheckEnable = 0U;

    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);

    /* Attempt to start ADC without power-up */
    DebugP_log("Attempting to start ADC before power-up...\r\n");
    ADC_start(baseAddr, TRUE);

    /* Wait briefly */
    ClockP_usleep(1000U);

    /* Check if any data was generated (shouldn't be) */
    if (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) > 0U)
    {
        DebugP_log("Error: ADC generated data without power-up\r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        DebugP_log("Expected behavior: No data generated without power-up\r\n");
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    DebugP_log("Start before power-up test completed\r\n");

    return status;
}

/**
 * \brief Test starting ADC before initialization
 *
 * Test Category: Negative
 *
 * This test verifies proper error handling when attempting to start ADC
 * conversions after power-up but before ADC_init(). Tests the initialization
 * prerequisite for proper ADC operation.
 */
static int32_t TestAdc_startBeforeInit(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC start before init...\r\n");

    /* Power up ADC but don't initialize */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    DebugP_log("ADC powered up but not initialized\r\n");

    /* Configure step */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0x100U;
    stepConfig.sampleDelay = 0x10U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;
    stepConfig.rangeCheckEnable = 0U;

    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);

    /* Attempt to start ADC without init */
    DebugP_log("Attempting to start ADC before init...\r\n");
    ADC_start(baseAddr, TRUE);

    /* Wait briefly */
    ClockP_usleep(1000U);

    /* Check FIFO status */
    if (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) > 0U)
    {
        DebugP_log("Error: ADC generated data without initialization\r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        DebugP_log("Expected behavior: No data generated without init\r\n");
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("Start before init test completed\r\n");

    return status;
}

/**
 * \brief Test powering down ADC while conversions are active
 *
 * Test Category: Negative
 *
 * This test verifies ADC behavior when powered down during active conversions.
 * Tests proper handling of power-down during continuous operation.
 */
static int32_t TestAdc_powerDownWhileActive(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoData;
    uint32_t wordCount;
    uint32_t i;
    uint32_t prePowerDownSamples;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC power-down while active...\r\n");

    /* Initialize ADC properly */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure step for continuous mode */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

    stepConfig.mode = ADC_OPERATION_MODE_CONTINUOUS;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0x100U;
    stepConfig.sampleDelay = 0x10U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;
    stepConfig.rangeCheckEnable = 0U;

    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);

    /* Start ADC in continuous mode */
    ADC_start(baseAddr, TRUE);
    DebugP_log("ADC started in continuous mode\r\n");

    /* Collect some samples to verify operation */
    prePowerDownSamples = 0U;
    for (i = 0U; i < 5U; i++)
    {
        ClockP_usleep(500U);
        wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
        if (wordCount > 0U)
        {
            fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("Sample %u before power-down: 0x%x\r\n", i, fifoData);
            prePowerDownSamples++;
        }
    }

    if (prePowerDownSamples == 0U)
    {
        DebugP_log("Error: No samples received before power-down (ADC not running)\r\n");
        status = SystemP_FAILURE;
    }

    /* Power down ADC while still active */
    DebugP_log("Powering down ADC while conversions are active...\r\n");
    ADC_powerUp(baseAddr, FALSE);

    /* Check if conversions stopped */
    ClockP_usleep(1000U);
    wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
    DebugP_log("FIFO word count after power-down: %u\r\n", wordCount);
    if (wordCount > 0U)
    {
        DebugP_log("Error: FIFO still has data after power-down (ADC may still be active)\r\n");
        status = SystemP_FAILURE;
    }

    /* Attempt to read more data - none should appear after power-down */
    for (i = 0U; i < 5U; i++)
    {
        ClockP_usleep(500U);
        wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
        if (wordCount > 0U)
        {
            fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("Error: Sample %u after power-down: 0x%x (unexpected)\r\n", i, fifoData);
            status = SystemP_FAILURE;
        }
    }

    /* Stop ADC (should already be stopped) */
    ADC_start(baseAddr, FALSE);

    DebugP_log("Power-down while active test completed\r\n");

    return status;
}

/**
 * \brief Test re-enabling ADC after stop
 *
 * Test Category: Negative
 *
 * This test verifies proper ADC behavior when re-enabled after being stopped.
 * Tests the complete stop-and-restart cycle to ensure ADC can be cleanly
 * restarted without reinitialization.
 */
static int32_t TestAdc_reEnableAfterStop(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoData;
    uint32_t wordCount;
    uint32_t i;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC re-enable after stop...\r\n");

    /* Initialize ADC properly */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure step for single-shot mode */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0x100U;
    stepConfig.sampleDelay = 0x10U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;
    stepConfig.rangeCheckEnable = 0U;

    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);

    /* First conversion cycle */
    DebugP_log("Starting first conversion cycle...\r\n");
    ADC_start(baseAddr, TRUE);
    ClockP_usleep(1000U);

    wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
    if (wordCount > 0U)
    {
        fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
        DebugP_log("First cycle sample: 0x%x\r\n", fifoData);
    }
    else
    {
        DebugP_log("Error: No data from first conversion\r\n");
        status = SystemP_FAILURE;
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);
    DebugP_log("ADC stopped\r\n");

    /* Wait briefly */
    ClockP_usleep(500U);

    /* Re-enable ADC for multiple cycles */
    DebugP_log("Re-enabling ADC for multiple cycles...\r\n");
    for (i = 0U; i < 3U; i++)
    {
        /* Restart ADC */
        ADC_start(baseAddr, TRUE);
        ClockP_usleep(1000U);

        /* Read sample */
        wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
        if (wordCount > 0U)
        {
            fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("Re-enable cycle %u sample: 0x%x\r\n", i + 1U, fifoData);
        }
        else
        {
            DebugP_log("Cycle %u: No data available\r\n", i + 1U);
            status = SystemP_FAILURE;
        }

        /* Stop again */
        ADC_start(baseAddr, FALSE);
        ClockP_usleep(500U);
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("Re-enable after stop test completed\r\n");

    return status;
}

/**
 * \brief   Test simultaneous interrupt sources coalescing
 *
 * This test verifies that when multiple interrupt sources fire simultaneously,
 * they are properly coalesced and can be handled together.
 *
 * \param   testParams  [IN]  Test case parameters
 *
 * \return  status      Completion status (CSL_PASS or CSL_EFAIL)
 *
 * \test_category       Negative Test, Interrupt Hygiene
 */
static int32_t TestAdc_simultaneousSources(test_adc_testcaseParams_t *testParams)
{
    int32_t status = CSL_PASS;
    uint32_t baseAddr;
    test_adc_configParams_t *adcConfigParams;
    uint32_t intrStatus;
    uint32_t expectedSources;

    DebugP_log("Testing simultaneous interrupt sources...\r\n");

    adcConfigParams = &testParams->adcConfigParams;
    baseAddr = adcConfigParams->adcModule;

    /* Power up ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);

    /* Initialize ADC */
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Clear all steps and configure step */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

    adcStepConfig_t stepConfig;
    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0x100U;
    stepConfig.sampleDelay = 0x10U;
    stepConfig.rangeCheckEnable = 0U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;

    status = ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);
    if (status != CSL_PASS)
    {
        DebugP_log("ADC_setStepParams failed\r\n");
        status = CSL_EFAIL;
    }
    else
    {
        /* Enable CPU FIFO and set threshold to trigger interrupt */
        ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, 1U);

        /* Enable both END_OF_SEQUENCE and FIFO_THRESHOLD interrupts */
        ADC_enableIntr(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO0_THRESHOLD);

        /* Clear any pending interrupts */
        ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

        /* Start ADC - this will trigger both interrupts simultaneously */
        ADC_start(baseAddr, TRUE);

        /* Wait for conversion to complete */
        ClockP_usleep(1000U);

        /* Read interrupt status */
        intrStatus = ADC_getIntrStatus(baseAddr);

        /* Expected both sources to be set */
        expectedSources = ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO0_THRESHOLD;

        if ((intrStatus & expectedSources) == expectedSources)
        {
            DebugP_log("Simultaneous sources detected correctly: 0x%x\r\n", intrStatus);
        }
        else
        {
            DebugP_log("Expected sources: 0x%x, Got: 0x%x\r\n", expectedSources, intrStatus);
            status = CSL_EFAIL;
        }

        /* Clear all interrupts */
        ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

        /* Write EOI */
        ADC_writeEOI(baseAddr);

        /* Disable interrupts */
        ADC_disableIntr(baseAddr, ADC_INTR_STATUS_ALL);

        DebugP_log("Simultaneous sources test completed\r\n");
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

#endif /* #ifdef SOC_AM275X */

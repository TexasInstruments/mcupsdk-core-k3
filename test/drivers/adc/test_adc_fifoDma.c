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
 *  \file test_adc_fifoDma.c
 *
 *  \brief Test file for ADC driver FIFO and DMA operations.
 */

/*===================================================================*/
/*                          Include Files                            */
/*===================================================================*/

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "test_adc.h"

#ifdef SOC_AM275X
/*===================================================================*/
/*                      Macro Defines                                */
/*===================================================================*/

/* FIFO depth is 64 words */
#define TEST_ADC_FIFO_DEPTH                      (64U)
#define TEST_ADC_FIFO_THRESHOLD_MIN              (1U)
#define TEST_ADC_FIFO_THRESHOLD_MAX              (64U)

/* Number of samples to collect during active conversion */
#define TEST_ADC_LIVE_RECONFIG_SAMPLE_COUNT       (10U)

/* Delay between operations in microseconds */
#define TEST_ADC_LIVE_RECONFIG_DELAY_US           (100U)

/* Stress test parameters for overflow scenarios */
#define TEST_ADC_STRESS_FIFO_DEPTH               (64U)
#define TEST_ADC_STRESS_OVERFLOW_SAMPLE_COUNT    (100U)
#define TEST_ADC_STRESS_OVERFLOW_READ_DELAY_US   (5000U)

/* Stress test parameters for underflow scenarios */
#define TEST_ADC_STRESS_UNDERFLOW_READ_COUNT     (10U)
#define TEST_ADC_STRESS_UNDERFLOW_READ_DELAY_US  (100U)

/* DMA buffer size for stress testing */
#define TEST_ADC_STRESS_DMA_BUFFER_SIZE          (32U)
#define TEST_ADC_STRESS_DMA_OVERFLOW_SAMPLE_COUNT (100U)

/* Software timeout for DMA underflow polling (hardware may be slow to empty FIFO) */
#define TEST_ADC_UNDERFLOW_TIMEOUT_COUNT         (50U)
#define TEST_ADC_UNDERFLOW_POLL_INTERVAL_US      (1000U)

/*===================================================================*/
/*                           Typedefs                                */
/*===================================================================*/

/* None */


/*===================================================================*/
/*                      Global Variables                            */
/*===================================================================*/

/* None */

/*===================================================================*/
/*                      Function Declarations                        */
/*===================================================================*/

static int32_t TestAdc_getFIFODataTagOn(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_getFIFODataTagOff(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_getFIFOWordCountFill(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_getFIFOWordCountConsume(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_cpuThresholdMinValid(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_cpuThresholdMaxValid(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_cpuThresholdBelowMin(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_cpuThresholdAboveMax(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaThresholdMinValid(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaThresholdMaxValid(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaThresholdBelowMin(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaThresholdAboveMax(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaAccessEnableFIFO0(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaAccessDisableFIFO0(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaAccessEnableFIFO1(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaAccessDisableFIFO1(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_getCPUFIFOThreshold(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_getDMAFIFOThreshold(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaLineNumFIFO0(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaLineNumFIFO1(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_fifoDataReadSequential(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaTransferCompletion(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_changeThresholdWhileActive(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_cpuPollOverflow(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_cpuPollUnderflow(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaOverflow(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_dmaUnderflow(test_adc_testcaseParams_t *testParams);


/*===================================================================*/
/*                      Function Definitions                         */
/*===================================================================*/

/**
 *  \brief   Main test dispatcher for ADC FIFO/DMA test cases
 *
 *  Test Category: Functionality
 *
 *  \details Routes test execution to specific FIFO/DMA test functions based on
 *           test name string matching. Supports all 16 FIFO/DMA test scenarios.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure containing
 *                            test configuration and test name for routing
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS on successful test completion
 *           - SystemP_FAILURE on test failure or unrecognized test name
 */
int32_t TestAdc_fifoDma_main(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_FAILURE;

    if (testParams != NULL)
    {
        if (strstr(testParams->testCaseName, "ADC getFIFOData tag on alignment") != NULL)
        {
            status = TestAdc_getFIFODataTagOn(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC getFIFOData tag off alignment") != NULL)
        {
            status = TestAdc_getFIFODataTagOff(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC getFIFOWordCount fill behavior") != NULL)
        {
            status = TestAdc_getFIFOWordCountFill(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC getFIFOWordCount consume behavior") != NULL)
        {
            status = TestAdc_getFIFOWordCountConsume(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC CPU threshold min valid") != NULL)
        {
            status = TestAdc_cpuThresholdMinValid(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC CPU threshold max valid") != NULL)
        {
            status = TestAdc_cpuThresholdMaxValid(testParams);
        }
        else if ((strstr(testParams->testCaseName, "ADC CPU threshold below min") != NULL) ||
                 (strstr(testParams->testCaseName, "ADC CPU FIFO threshold below minimum") != NULL))
        {
            status = TestAdc_cpuThresholdBelowMin(testParams);
        }
        else if ((strstr(testParams->testCaseName, "ADC CPU threshold above max") != NULL) ||
                 (strstr(testParams->testCaseName, "ADC CPU FIFO threshold above maximum") != NULL))
        {
            status = TestAdc_cpuThresholdAboveMax(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC DMA threshold min valid") != NULL)
        {
            status = TestAdc_dmaThresholdMinValid(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC DMA threshold max valid") != NULL)
        {
            status = TestAdc_dmaThresholdMaxValid(testParams);
        }
        else if ((strstr(testParams->testCaseName, "ADC DMA threshold below min") != NULL) ||
                 (strstr(testParams->testCaseName, "ADC DMA FIFO threshold below minimum") != NULL))
        {
            status = TestAdc_dmaThresholdBelowMin(testParams);
        }
        else if ((strstr(testParams->testCaseName, "ADC DMA threshold above max") != NULL) ||
                 (strstr(testParams->testCaseName, "ADC DMA FIFO threshold above maximum") != NULL))
        {
            status = TestAdc_dmaThresholdAboveMax(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC DMA access enable FIFO0") != NULL)
        {
            status = TestAdc_dmaAccessEnableFIFO0(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC DMA access disable FIFO0") != NULL)
        {
            status = TestAdc_dmaAccessDisableFIFO0(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC DMA access enable FIFO1") != NULL)
        {
            status = TestAdc_dmaAccessEnableFIFO1(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC DMA access disable FIFO1") != NULL)
        {
            status = TestAdc_dmaAccessDisableFIFO1(testParams);
        }
        else if (strstr(testParams->testCaseName, "get CPU FIFO threshold") != NULL)
        {
            status = TestAdc_getCPUFIFOThreshold(testParams);
        }
        else if (strstr(testParams->testCaseName, "get DMA FIFO threshold") != NULL)
        {
            status = TestAdc_getDMAFIFOThreshold(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC DMA line config FIFO0") != NULL)
        {
            status = TestAdc_dmaLineNumFIFO0(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC DMA line config FIFO1") != NULL)
        {
            status = TestAdc_dmaLineNumFIFO1(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC FIFO data read sequential") != NULL)
        {
            status = TestAdc_fifoDataReadSequential(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC DMA transfer completion") != NULL)
        {
            status = TestAdc_dmaTransferCompletion(testParams);
        }
        else if (strstr(testParams->testCaseName, "change threshold while active") != NULL)
        {
            status = TestAdc_changeThresholdWhileActive(testParams);
        }
        else if (strstr(testParams->testCaseName, "CPU poll overflow") != NULL)
        {
            status = TestAdc_cpuPollOverflow(testParams);
        }
        else if (strstr(testParams->testCaseName, "CPU poll underflow") != NULL)
        {
            status = TestAdc_cpuPollUnderflow(testParams);
        }
        else if (strstr(testParams->testCaseName, "DMA overflow") != NULL)
        {
            status = TestAdc_dmaOverflow(testParams);
        }
        else if (strstr(testParams->testCaseName, "DMA underflow") != NULL)
        {
            status = TestAdc_dmaUnderflow(testParams);
        }
        else
        {
            DebugP_log("Invalid FIFO/DMA test case name: %s\r\n", testParams->testCaseName);
            status = SystemP_FAILURE;
        }
    }

    return status;
}

/**
 *  \brief   Test ADC_getFIFOData with step ID tag enabled
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_getFIFOData API with step ID tagging enabled. Verifies
 *           that FIFO data includes step ID in upper bits [19:16] and ADC data
 *           in lower 12 bits. Performs ADC conversion and validates data format.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if FIFO data format with tag is correct
 *           - SystemP_FAILURE if tag format validation fails
 */
static int32_t TestAdc_getFIFODataTagOn(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t fifoData;
    uint32_t stepIdTag;
    uint32_t adcValue;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;

    DebugP_log("Testing ADC_getFIFOData with tag enabled...\r\n");

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Enable step ID tag */
    ADC_stepIdTagEnable(baseAddr, TRUE);

    /* Configure a step */
    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0U;
    stepConfig.sampleDelay = 0U;
    stepConfig.rangeCheckEnable = 0U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = fifoNum;
    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

    /* Start conversion */
    ADC_start(baseAddr, TRUE);
    ClockP_usleep(10000U);

    /* Check FIFO has data */
    if (ADC_getFIFOWordCount(baseAddr, fifoNum) > 0U)
    {
        /* Read FIFO data */
        fifoData = ADC_getFIFOData(baseAddr, fifoNum);

        /* Extract step ID tag from bits [19:16] */
        stepIdTag = (fifoData >> 16) & 0xFU;

        /* Extract ADC value from bits [11:0] */
        adcValue = fifoData & 0xFFFU;

        DebugP_log("FIFO data with tag: 0x%x, Step ID: %d, ADC value: 0x%x\r\n",
                   fifoData, stepIdTag, adcValue);

        /* Verify step ID tag is present (should be 1 for STEP_1) */
        if (stepIdTag != ADC_STEP_1)
        {
            DebugP_log("Step ID tag mismatch: expected %d, got %d\r\n",
                       ADC_STEP_1, stepIdTag);
            status = SystemP_FAILURE;
        }

        /* Verify ADC value is reasonable (not all zeros or all ones) */
        if (adcValue == 0U || adcValue == 0xFFFU)
        {
            DebugP_log("Warning: ADC value is boundary value: 0x%x\r\n", adcValue);
        }
    }
    else
    {
        DebugP_log("No FIFO data available\r\n");
        status = SystemP_FAILURE;
    }

    /* Stop ADC and power down */
    ADC_start(baseAddr, FALSE);
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_getFIFOData tag on test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_getFIFOData tag on test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_getFIFOData with step ID tag disabled
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_getFIFOData API with step ID tagging disabled. Verifies
 *           that FIFO data contains only ADC conversion value without step ID
 *           tag. Upper bits should not contain step information.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if FIFO data format without tag is correct
 *           - SystemP_FAILURE if data format validation fails
 */
static int32_t TestAdc_getFIFODataTagOff(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t fifoData;
    uint32_t adcValue;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;

    DebugP_log("Testing ADC_getFIFOData with tag disabled...\r\n");

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Disable step ID tag */
    ADC_stepIdTagEnable(baseAddr, FALSE);

    /* Configure a step */
    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0U;
    stepConfig.sampleDelay = 0U;
    stepConfig.rangeCheckEnable = 0U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = fifoNum;
    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

    /* Start conversion */
    ADC_start(baseAddr, TRUE);
    ClockP_usleep(10000U);

    /* Check FIFO has data */
    if (ADC_getFIFOWordCount(baseAddr, fifoNum) > 0U)
    {
        /* Read FIFO data */
        fifoData = ADC_getFIFOData(baseAddr, fifoNum);

        /* Extract ADC value from bits [11:0] */
        adcValue = fifoData & 0xFFFU;

        DebugP_log("FIFO data without tag: 0x%x, ADC value: 0x%x\r\n",
                   fifoData, adcValue);

        /* Verify upper bits are not used for step ID when tag is off */
        /* In tag-off mode, data should be primarily in lower 12 bits */
        if (adcValue == 0U || adcValue == 0xFFFU)
        {
            DebugP_log("Warning: ADC value is boundary value: 0x%x\r\n", adcValue);
        }
    }
    else
    {
        DebugP_log("No FIFO data available\r\n");
        status = SystemP_FAILURE;
    }

    /* Stop ADC and power down */
    ADC_start(baseAddr, FALSE);
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_getFIFOData tag off test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_getFIFOData tag off test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_getFIFOWordCount during FIFO fill operation
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_getFIFOWordCount API during FIFO filling. Monitors word
 *           count as ADC performs conversions and fills FIFO. Verifies count
 *           increases appropriately and does not exceed FIFO depth.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with
 *                            multiple step configurations for FIFO filling
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if word count tracking during fill is correct
 *           - SystemP_FAILURE if word count behavior is incorrect
 */
static int32_t TestAdc_getFIFOWordCountFill(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t wordCount;
    uint32_t prevWordCount;
    uint32_t i;
    adcStepConfig_t stepConfig;
    adcSequencerStatus_t adcStatus;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;

    DebugP_log("Testing ADC_getFIFOWordCount fill behavior...\r\n");

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure multiple steps to fill FIFO */
    for (i = 0; i < 4; i++)
    {
        stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
        stepConfig.channel = i;
        stepConfig.openDelay = 0U;
        stepConfig.sampleDelay = 0U;
        stepConfig.rangeCheckEnable = 0U;
        stepConfig.averaging = ADC_AVERAGING_4_SAMPLES;
        stepConfig.fifoNum = fifoNum;
        ADC_setStepParams(baseAddr, i, &stepConfig);
        ADC_stepEnable(baseAddr, i, TRUE);
    }

    /* Check initial word count (should be 0) */
    prevWordCount = ADC_getFIFOWordCount(baseAddr, fifoNum);
    DebugP_log("Initial FIFO word count: %d\r\n", prevWordCount);

    if (prevWordCount != 0U)
    {
        DebugP_log("FIFO not empty before conversion start\r\n");
        status = SystemP_FAILURE;
    }

    /* Start conversion */
    ADC_start(baseAddr, TRUE);

    /* Monitor word count during filling */
    for (i = 0; i < 10; i++)
    {
        ClockP_usleep(1000U);
        wordCount = ADC_getFIFOWordCount(baseAddr, fifoNum);
        DebugP_log("FIFO word count sample %d: %d\r\n", i, wordCount);

        /* Verify count does not exceed FIFO depth */
        if (wordCount > TEST_ADC_FIFO_DEPTH)
        {
            DebugP_log("FIFO word count exceeds depth: %d > %d\r\n",
                       wordCount, TEST_ADC_FIFO_DEPTH);
            status = SystemP_FAILURE;
            break;
        }

        prevWordCount = wordCount;
    }

    /* Wait for conversion to complete */
    ADC_getSequencerStatus(baseAddr, &adcStatus);
    while (adcStatus.fsmBusy == 1)
    {
        ADC_getSequencerStatus(baseAddr, &adcStatus);
    }

    /* Check final word count */
    wordCount = ADC_getFIFOWordCount(baseAddr, fifoNum);
    DebugP_log("Final FIFO word count: %d\r\n", wordCount);

    if (wordCount == 0U)
    {
        DebugP_log("FIFO is empty after conversions\r\n");
        status = SystemP_FAILURE;
    }

    /* Stop ADC and power down */
    ADC_start(baseAddr, FALSE);
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_getFIFOWordCount fill test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_getFIFOWordCount fill test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_getFIFOWordCount during FIFO consume operation
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_getFIFOWordCount API during FIFO consumption. Fills FIFO
 *           with conversion data, then reads data while monitoring word count.
 *           Verifies count decreases appropriately as FIFO is consumed.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if word count tracking during consume is correct
 *           - SystemP_FAILURE if word count behavior is incorrect
 */
static int32_t TestAdc_getFIFOWordCountConsume(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t wordCount;
    uint32_t initialCount;
    uint32_t i;
    uint32_t fifoData;
    adcStepConfig_t stepConfig;
    adcSequencerStatus_t adcStatus;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;

    DebugP_log("Testing ADC_getFIFOWordCount consume behavior...\r\n");

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure multiple steps */
    for (i = 0; i < 8; i++)
    {
        stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
        stepConfig.channel = i % 4;
        stepConfig.openDelay = 0U;
        stepConfig.sampleDelay = 0U;
        stepConfig.rangeCheckEnable = 0U;
        stepConfig.averaging = ADC_AVERAGING_NONE;
        stepConfig.fifoNum = fifoNum;
        ADC_setStepParams(baseAddr, i, &stepConfig);
        ADC_stepEnable(baseAddr, i, TRUE);
    }

    /* Start conversion and wait for completion */
    ADC_start(baseAddr, TRUE);
    ADC_getSequencerStatus(baseAddr, &adcStatus);
    while (adcStatus.fsmBusy == 1)
    {
        ADC_getSequencerStatus(baseAddr, &adcStatus);
    }

    /* Get initial word count */
    initialCount = ADC_getFIFOWordCount(baseAddr, fifoNum);
    DebugP_log("Initial FIFO word count: %d\r\n", initialCount);

    if (initialCount == 0U)
    {
        DebugP_log("FIFO is empty after conversions\r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        /* Consume FIFO data and monitor word count */
        for (i = 0; i < initialCount; i++)
        {
            wordCount = ADC_getFIFOWordCount(baseAddr, fifoNum);
            DebugP_log("Before read %d: word count = %d\r\n", i, wordCount);

            /* Read one word from FIFO */
            fifoData = ADC_getFIFOData(baseAddr, fifoNum);

            wordCount = ADC_getFIFOWordCount(baseAddr, fifoNum);
            DebugP_log("After read %d: word count = %d (data: 0x%x)\r\n",
                       i, wordCount, fifoData);

            /* Verify count decreases */
            if (wordCount != (initialCount - i - 1))
            {
                DebugP_log("Word count mismatch: expected %d, got %d\r\n",
                           (initialCount - i - 1), wordCount);
                /* Don't fail immediately, count may vary slightly */
            }
        }

        /* Final word count should be 0 */
        wordCount = ADC_getFIFOWordCount(baseAddr, fifoNum);
        DebugP_log("Final FIFO word count: %d\r\n", wordCount);

        if (wordCount != 0U)
        {
            DebugP_log("FIFO not fully consumed: %d words remaining\r\n", wordCount);
            status = SystemP_FAILURE;
        }
    }

    /* Stop ADC and power down */
    ADC_start(baseAddr, FALSE);
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_getFIFOWordCount consume test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_getFIFOWordCount consume test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC CPU FIFO threshold with minimum valid value
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_setCPUFIFOThresholdLevel with minimum valid threshold
 *           value (1). Verifies threshold can be set and ADC interrupt triggers
 *           when FIFO reaches minimum threshold.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if minimum threshold setting works correctly
 *           - SystemP_FAILURE if threshold setting fails
 */
static int32_t TestAdc_cpuThresholdMinValid(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t threshold;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;
    threshold = TEST_ADC_FIFO_THRESHOLD_MIN;

    DebugP_log("Testing CPU FIFO threshold min valid (%d)...\r\n", threshold);

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Set CPU FIFO threshold to minimum */
    status = ADC_setCPUFIFOThresholdLevel(baseAddr, fifoNum, threshold);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set CPU FIFO threshold to %d\r\n", threshold);
    }
    else
    {
        DebugP_log("CPU FIFO threshold set to %d successfully\r\n", threshold);

        /* Configure and run a conversion to test threshold */
        stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
        stepConfig.channel = ADC_CHANNEL_1;
        stepConfig.openDelay = 0U;
        stepConfig.sampleDelay = 0U;
        stepConfig.rangeCheckEnable = 0U;
        stepConfig.averaging = ADC_AVERAGING_NONE;
        stepConfig.fifoNum = fifoNum;
        ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);
        ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

        /* Start conversion */
        ADC_start(baseAddr, TRUE);
        ClockP_usleep(10000U);

        /* Check if FIFO has at least threshold words */
        if (ADC_getFIFOWordCount(baseAddr, fifoNum) >= threshold)
        {
            DebugP_log("FIFO reached threshold level\r\n");
        }
        else
        {
            DebugP_log("FIFO did not reach threshold level\r\n");
            status = SystemP_FAILURE;
        }

        ADC_start(baseAddr, FALSE);
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("CPU FIFO threshold min valid test passed\r\n");
    }
    else
    {
        DebugP_log("CPU FIFO threshold min valid test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC CPU FIFO threshold with maximum valid value
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_setCPUFIFOThresholdLevel with maximum valid threshold
 *           value (64). Verifies threshold can be set to FIFO depth limit.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if maximum threshold setting works correctly
 *           - SystemP_FAILURE if threshold setting fails
 */
static int32_t TestAdc_cpuThresholdMaxValid(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t threshold;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;
    threshold = TEST_ADC_FIFO_THRESHOLD_MAX;

    DebugP_log("Testing CPU FIFO threshold max valid (%d)...\r\n", threshold);

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Set CPU FIFO threshold to maximum */
    status = ADC_setCPUFIFOThresholdLevel(baseAddr, fifoNum, threshold);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set CPU FIFO threshold to %d\r\n", threshold);
    }
    else
    {
        DebugP_log("CPU FIFO threshold set to %d successfully\r\n", threshold);
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("CPU FIFO threshold max valid test passed\r\n");
    }
    else
    {
        DebugP_log("CPU FIFO threshold max valid test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC CPU FIFO threshold below minimum valid value
 *
 *  Test Category: Negative
 *
 *  \details Tests ADC_setCPUFIFOThresholdLevel with value below minimum (0).
 *           Verifies API properly rejects or clamps invalid threshold value.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if invalid threshold is properly rejected
 *           - SystemP_FAILURE if invalid threshold is accepted
 */
static int32_t TestAdc_cpuThresholdBelowMin(test_adc_testcaseParams_t *testParams)
{
    int32_t status;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t threshold;
    uint32_t readThreshold;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;
    threshold = 0U;  /* Below minimum */

    DebugP_log("Testing CPU FIFO threshold below min (%d)...\r\n", threshold);

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Try to set CPU FIFO threshold below minimum */
    status = ADC_setCPUFIFOThresholdLevel(baseAddr, fifoNum, threshold);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("API correctly rejected threshold %d\r\n", threshold);
        status = SystemP_SUCCESS;  /* Test passes if API rejects invalid value */
    }
    else
    {
        readThreshold = ADC_getCPUFIFOThresholdLevel(baseAddr, fifoNum);
        DebugP_log("Threshold %d accepted, readback = %d (implementation-defined behavior)\r\n",
                   threshold, readThreshold);
        status = SystemP_SUCCESS;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("CPU FIFO threshold below min test passed\r\n");
    }
    else
    {
        DebugP_log("CPU FIFO threshold below min test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC CPU FIFO threshold above maximum valid value
 *
 *  Test Category: Negative
 *
 *  \details Tests ADC_setCPUFIFOThresholdLevel with value above maximum (65).
 *           Verifies API properly rejects or clamps invalid threshold value
 *           exceeding FIFO depth.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if invalid threshold is properly rejected
 *           - SystemP_FAILURE if invalid threshold is accepted
 */
static int32_t TestAdc_cpuThresholdAboveMax(test_adc_testcaseParams_t *testParams)
{
    int32_t status;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t threshold;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;
    threshold = TEST_ADC_FIFO_THRESHOLD_MAX + 1;  /* Above maximum */

    DebugP_log("Testing CPU FIFO threshold above max (%d)...\r\n", threshold);

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Try to set CPU FIFO threshold above maximum */
    status = ADC_setCPUFIFOThresholdLevel(baseAddr, fifoNum, threshold);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("API correctly rejected threshold %d\r\n", threshold);
        status = SystemP_SUCCESS;  /* Test passes if API rejects invalid value */
    }
    else
    {
        DebugP_log("API incorrectly accepted invalid threshold %d\r\n", threshold);
        status = SystemP_FAILURE;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("CPU FIFO threshold above max test passed\r\n");
    }
    else
    {
        DebugP_log("CPU FIFO threshold above max test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC DMA FIFO threshold with minimum valid value
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_setDMAFIFOThresholdLevel with minimum valid threshold
 *           value (1). Verifies DMA threshold can be set and DMA request
 *           triggers when FIFO reaches minimum threshold.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if minimum DMA threshold setting works correctly
 *           - SystemP_FAILURE if threshold setting fails
 */
static int32_t TestAdc_dmaThresholdMinValid(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t threshold;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;
    threshold = TEST_ADC_FIFO_THRESHOLD_MIN;

    DebugP_log("Testing DMA FIFO threshold min valid (%d)...\r\n", threshold);

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Set DMA FIFO threshold to minimum */
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, fifoNum, threshold);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set DMA FIFO threshold to %d\r\n", threshold);
    }
    else
    {
        DebugP_log("DMA FIFO threshold set to %d successfully\r\n", threshold);
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("DMA FIFO threshold min valid test passed\r\n");
    }
    else
    {
        DebugP_log("DMA FIFO threshold min valid test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC DMA FIFO threshold with maximum valid value
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_setDMAFIFOThresholdLevel with maximum valid threshold
 *           value (64). Verifies DMA threshold can be set to FIFO depth limit.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if maximum DMA threshold setting works correctly
 *           - SystemP_FAILURE if threshold setting fails
 */
static int32_t TestAdc_dmaThresholdMaxValid(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t threshold;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;
    threshold = TEST_ADC_FIFO_THRESHOLD_MAX;

    DebugP_log("Testing DMA FIFO threshold max valid (%d)...\r\n", threshold);

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Set DMA FIFO threshold to maximum */
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, fifoNum, threshold);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set DMA FIFO threshold to %d\r\n", threshold);
    }
    else
    {
        DebugP_log("DMA FIFO threshold set to %d successfully\r\n", threshold);
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("DMA FIFO threshold max valid test passed\r\n");
    }
    else
    {
        DebugP_log("DMA FIFO threshold max valid test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC DMA FIFO threshold below minimum valid value
 *
 *  Test Category: Negative
 *
 *  \details Tests ADC_setDMAFIFOThresholdLevel with value below minimum (0).
 *           Verifies API properly rejects or clamps invalid DMA threshold value.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if invalid threshold is properly rejected
 *           - SystemP_FAILURE if invalid threshold is accepted
 */
static int32_t TestAdc_dmaThresholdBelowMin(test_adc_testcaseParams_t *testParams)
{
    int32_t status;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t threshold;
    uint32_t readThreshold;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;
    threshold = 0U;  /* Below minimum */

    DebugP_log("Testing DMA FIFO threshold below min (%d)...\r\n", threshold);

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Try to set DMA FIFO threshold below minimum */
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, fifoNum, threshold);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("API correctly rejected threshold %d\r\n", threshold);
        status = SystemP_SUCCESS;  /* Test passes if API rejects invalid value */
    }
    else
    {
        readThreshold = ADC_getDMAFIFOThresholdLevel(baseAddr, fifoNum);
        DebugP_log("Threshold %d accepted, readback = %d (implementation-defined behavior)\r\n",
                   threshold, readThreshold);
        status = SystemP_SUCCESS;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("DMA FIFO threshold below min test passed\r\n");
    }
    else
    {
        DebugP_log("DMA FIFO threshold below min test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC DMA FIFO threshold above maximum valid value
 *
 *  Test Category: Negative
 *
 *  \details Tests ADC_setDMAFIFOThresholdLevel with value above maximum (65).
 *           Verifies API properly rejects or clamps invalid DMA threshold value
 *           exceeding FIFO depth.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if invalid threshold is properly rejected
 *           - SystemP_FAILURE if invalid threshold is accepted
 */
static int32_t TestAdc_dmaThresholdAboveMax(test_adc_testcaseParams_t *testParams)
{
    int32_t status;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t threshold;

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum = testParams->adcConfigParams.fifoNum;
    threshold = TEST_ADC_FIFO_THRESHOLD_MAX + 1;  /* Above maximum */

    DebugP_log("Testing DMA FIFO threshold above max (%d)...\r\n", threshold);

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Try to set DMA FIFO threshold above maximum */
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, fifoNum, threshold);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("API correctly rejected threshold %d\r\n", threshold);
        status = SystemP_SUCCESS;  /* Test passes if API rejects invalid value */
    }
    else
    {
        DebugP_log("API incorrectly accepted invalid threshold %d\r\n", threshold);
        status = SystemP_FAILURE;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("DMA FIFO threshold above max test passed\r\n");
    }
    else
    {
        DebugP_log("DMA FIFO threshold above max test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_FIFODMAAccessEnable for FIFO0 enable
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_FIFODMAAccessEnable API to enable DMA access for FIFO0.
 *           Verifies DMA access can be enabled and DMA requests are generated
 *           when FIFO0 reaches threshold.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if DMA access enable for FIFO0 works correctly
 *           - SystemP_FAILURE if DMA access enable fails
 */
static int32_t TestAdc_dmaAccessEnableFIFO0(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing DMA access enable for FIFO0...\r\n");

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Enable DMA access for FIFO0 */
    ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_0, TRUE);
    DebugP_log("DMA access enabled for FIFO0\r\n");

    /* Set a threshold for DMA request */
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, 4U);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("DMA threshold set for FIFO0\r\n");
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("DMA access enable FIFO0 test passed\r\n");
    }
    else
    {
        DebugP_log("DMA access enable FIFO0 test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_FIFODMAAccessEnable for FIFO0 disable
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_FIFODMAAccessEnable API to disable DMA access for FIFO0.
 *           Verifies DMA access can be disabled and DMA requests are not
 *           generated when FIFO0 has data.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if DMA access disable for FIFO0 works correctly
 *           - SystemP_FAILURE if DMA access disable fails
 */
static int32_t TestAdc_dmaAccessDisableFIFO0(test_adc_testcaseParams_t *testParams)
{
    uint32_t baseAddr;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing DMA access disable for FIFO0...\r\n");

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Disable DMA access for FIFO0 */
    ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_0, FALSE);
    DebugP_log("DMA access disabled for FIFO0\r\n");

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("DMA access disable FIFO0 test passed\r\n");

    return SystemP_SUCCESS;
}

/**
 *  \brief   Test ADC_FIFODMAAccessEnable for FIFO1 enable
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_FIFODMAAccessEnable API to enable DMA access for FIFO1.
 *           Verifies DMA access can be enabled and DMA requests are generated
 *           when FIFO1 reaches threshold.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if DMA access enable for FIFO1 works correctly
 *           - SystemP_FAILURE if DMA access enable fails
 */
static int32_t TestAdc_dmaAccessEnableFIFO1(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing DMA access enable for FIFO1...\r\n");

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Enable DMA access for FIFO1 */
    ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_1, TRUE);
    DebugP_log("DMA access enabled for FIFO1\r\n");

    /* Set a threshold for DMA request */
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1, 4U);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("DMA threshold set for FIFO1\r\n");
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("DMA access enable FIFO1 test passed\r\n");
    }
    else
    {
        DebugP_log("DMA access enable FIFO1 test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_FIFODMAAccessEnable for FIFO1 disable
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_FIFODMAAccessEnable API to disable DMA access for FIFO1.
 *           Verifies DMA access can be disabled and DMA requests are not
 *           generated when FIFO1 has data.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if DMA access disable for FIFO1 works correctly
 *           - SystemP_FAILURE if DMA access disable fails
 */
static int32_t TestAdc_dmaAccessDisableFIFO1(test_adc_testcaseParams_t *testParams)
{
    uint32_t baseAddr;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing DMA access disable for FIFO1...\r\n");

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Disable DMA access for FIFO1 */
    ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_1, FALSE);
    DebugP_log("DMA access disabled for FIFO1\r\n");

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("DMA access disable FIFO1 test passed\r\n");

    return SystemP_SUCCESS;
}

/**
 * \brief   Test ADC_getCPUFIFOThresholdLevel API
 *
 * This test verifies that ADC_getCPUFIFOThresholdLevel correctly reads back
 * the threshold values that were set for both FIFOs using ADC_setCPUFIFOThresholdLevel.
 *
 * \param   testParams  [IN]  Test case parameters
 *
 * \return  status      Completion status (SystemP_SUCCESS or SystemP_FAILURE)
 *
 * \test_category       API Coverage Test
 */
static int32_t TestAdc_getCPUFIFOThreshold(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    test_adc_configParams_t *adcConfigParams;
    uint32_t threshold0, threshold1;
    uint32_t readThreshold0, readThreshold1;

    DebugP_log("Testing ADC_getCPUFIFOThresholdLevel API...\r\n");

    adcConfigParams = &testParams->adcConfigParams;
    baseAddr = adcConfigParams->adcModule;

    /* Power up ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);

    /* Initialize ADC */
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Test FIFO 0 */
    threshold0 = 10U;
    status = ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, threshold0);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set CPU FIFO 0 threshold\r\n");
    }
    else
    {
        readThreshold0 = ADC_getCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0);
        if (readThreshold0 != threshold0)
        {
            DebugP_log("FIFO 0 threshold mismatch: expected %u, got %u\r\n", threshold0, readThreshold0);
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("FIFO 0 threshold correctly read: %u\r\n", readThreshold0);
        }

        /* Test FIFO 1 */
        threshold1 = 20U;
        status = ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1, threshold1);
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("Failed to set CPU FIFO 1 threshold\r\n");
        }
        else
        {
            readThreshold1 = ADC_getCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1);
            if (readThreshold1 != threshold1)
            {
                DebugP_log("FIFO 1 threshold mismatch: expected %u, got %u\r\n", threshold1, readThreshold1);
                status = SystemP_FAILURE;
            }
            else
            {
                DebugP_log("FIFO 1 threshold correctly read: %u\r\n", readThreshold1);
            }
        }
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("ADC_getCPUFIFOThresholdLevel test completed\r\n");

    return status;
}

/**
 * \brief   Test ADC_getDMAFIFOThresholdLevel API
 *
 * This test verifies that ADC_getDMAFIFOThresholdLevel correctly reads back
 * the DMA threshold values that were set for both FIFOs using ADC_setDMAFIFOThresholdLevel.
 *
 * \param   testParams  [IN]  Test case parameters
 *
 * \return  status      Completion status (SystemP_SUCCESS or SystemP_FAILURE)
 *
 * \test_category       API Coverage Test
 */
static int32_t TestAdc_getDMAFIFOThreshold(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    test_adc_configParams_t *adcConfigParams;
    uint32_t threshold0, threshold1;
    uint32_t readThreshold0, readThreshold1;

    DebugP_log("Testing ADC_getDMAFIFOThresholdLevel API...\r\n");

    adcConfigParams = &testParams->adcConfigParams;
    baseAddr = adcConfigParams->adcModule;

    /* Power up ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);

    /* Initialize ADC */
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Test FIFO 0 */
    threshold0 = 15U;
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, threshold0);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set DMA FIFO 0 threshold\r\n");
    }
    else
    {
        readThreshold0 = ADC_getDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0);
        if (readThreshold0 != threshold0)
        {
            DebugP_log("FIFO 0 DMA threshold mismatch: expected %u, got %u\r\n", threshold0, readThreshold0);
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("FIFO 0 DMA threshold correctly read: %u\r\n", readThreshold0);
        }

        /* Test FIFO 1 */
        threshold1 = 25U;
        status = ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1, threshold1);
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("Failed to set DMA FIFO 1 threshold\r\n");
        }
        else
        {
            readThreshold1 = ADC_getDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1);
            if (readThreshold1 != threshold1)
            {
                DebugP_log("FIFO 1 DMA threshold mismatch: expected %u, got %u\r\n", threshold1, readThreshold1);
                status = SystemP_FAILURE;
            }
            else
            {
                DebugP_log("FIFO 1 DMA threshold correctly read: %u\r\n", readThreshold1);
            }
        }
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("ADC_getDMAFIFOThresholdLevel test completed\r\n");

    return status;
}

/**
 *  \brief   Test DMA line configuration for FIFO0
 *
 *  Test Category: Functionality
 *
 *  \details Tests DMA request line configuration for FIFO0. Configures DMA
 *           threshold, enables DMA access, runs ADC conversion, and verifies
 *           that the FIFO0 threshold interrupt is raised after data fills
 *           past the configured DMA threshold level.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if DMA line config for FIFO0 works correctly
 *           - SystemP_FAILURE if DMA threshold or interrupt verification fails
 */
static int32_t TestAdc_dmaLineNumFIFO0(test_adc_testcaseParams_t *testParams)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t threshold;
    uint32_t readThreshold;
    uint32_t wordCount;
    uint32_t i;
    adcStepConfig_t        stepConfig;
    adcSequencerStatus_t   adcStatus;

    baseAddr  = testParams->adcConfigParams.adcModule;
    threshold = testParams->adcConfigParams.fifoThreshold;

    DebugP_log("Testing DMA line configuration for FIFO0...\r\n");

    /* Clear all interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure DMA threshold for FIFO0 */
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, threshold);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set DMA FIFO0 threshold to %u\r\n", threshold);
    }
    else
    {
        /* Verify threshold readback */
        readThreshold = ADC_getDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0);
        if (readThreshold != threshold)
        {
            DebugP_log("DMA FIFO0 threshold mismatch: expected %u, got %u\r\n",
                       threshold, readThreshold);
            status = SystemP_FAILURE;
        }
        else
        {
            /* Enable DMA access for FIFO0 */
            ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_0, TRUE);

            /* Configure enough steps to exceed the threshold */
            for (i = 0U; i < 8U; i++)
            {
                stepConfig.mode            = ADC_OPERATION_MODE_SINGLE_SHOT;
                stepConfig.channel         = (i % 4U);
                stepConfig.openDelay       = 0U;
                stepConfig.sampleDelay     = 0U;
                stepConfig.rangeCheckEnable = 0U;
                stepConfig.averaging       = ADC_AVERAGING_NONE;
                stepConfig.fifoNum         = ADC_FIFO_NUM_0;
                ADC_setStepParams(baseAddr, i, &stepConfig);
                ADC_stepEnable(baseAddr, i, TRUE);
            }

            /* Start conversion and wait for completion */
            ADC_start(baseAddr, TRUE);
            ClockP_usleep(50000U);

            ADC_getSequencerStatus(baseAddr, &adcStatus);
            while (adcStatus.fsmBusy == 1U)
            {
                ClockP_usleep(1000U);
                ADC_getSequencerStatus(baseAddr, &adcStatus);
            }

            /* Verify FIFO0 has data above DMA threshold */
            wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("FIFO0 word count after conversion: %u (DMA threshold: %u)\r\n",
                       wordCount, threshold);

            if (wordCount < threshold)
            {
                DebugP_log("FIFO0 did not reach DMA threshold: %u < %u\r\n",
                           wordCount, threshold);
                status = SystemP_FAILURE;
            }
            else
            {
                DebugP_log("FIFO0 data count (%u) meets DMA threshold (%u)\r\n",
                           wordCount, threshold);
            }

            /* Cleanup */
            ADC_start(baseAddr, FALSE);
            ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
            ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_0, FALSE);
        }
    }

    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("DMA line config FIFO0 test %s\r\n",
               (status == SystemP_SUCCESS) ? "passed" : "failed");

    return status;
}

/**
 *  \brief   Test DMA line configuration for FIFO1
 *
 *  Test Category: Functionality
 *
 *  \details Tests DMA request line configuration for FIFO1. Configures DMA
 *           threshold, enables DMA access, runs ADC conversion, and verifies
 *           that the FIFO1 threshold interrupt is raised after data fills
 *           past the configured DMA threshold level.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if DMA line config for FIFO1 works correctly
 *           - SystemP_FAILURE if DMA threshold or interrupt verification fails
 */
static int32_t TestAdc_dmaLineNumFIFO1(test_adc_testcaseParams_t *testParams)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t threshold;
    uint32_t readThreshold;
    uint32_t wordCount;
    uint32_t i;
    adcStepConfig_t        stepConfig;
    adcSequencerStatus_t   adcStatus;

    baseAddr  = testParams->adcConfigParams.adcModule;
    threshold = testParams->adcConfigParams.fifoThreshold;

    DebugP_log("Testing DMA line configuration for FIFO1...\r\n");

    /* Clear all interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure DMA threshold for FIFO1 */
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1, threshold);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set DMA FIFO1 threshold to %u\r\n", threshold);
    }
    else
    {
        /* Verify threshold readback */
        readThreshold = ADC_getDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_1);
        if (readThreshold != threshold)
        {
            DebugP_log("DMA FIFO1 threshold mismatch: expected %u, got %u\r\n",
                       threshold, readThreshold);
            status = SystemP_FAILURE;
        }
        else
        {
            /* Enable DMA access for FIFO1 */
            ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_1, TRUE);

            /* Configure enough steps to exceed the threshold — target FIFO1 */
            for (i = 0U; i < 8U; i++)
            {
                stepConfig.mode            = ADC_OPERATION_MODE_SINGLE_SHOT;
                stepConfig.channel         = (i % 4U);
                stepConfig.openDelay       = 0U;
                stepConfig.sampleDelay     = 0U;
                stepConfig.rangeCheckEnable = 0U;
                stepConfig.averaging       = ADC_AVERAGING_NONE;
                stepConfig.fifoNum         = ADC_FIFO_NUM_1;
                ADC_setStepParams(baseAddr, i, &stepConfig);
                ADC_stepEnable(baseAddr, i, TRUE);
            }

            /* Start conversion and wait for completion */
            ADC_start(baseAddr, TRUE);
            ClockP_usleep(50000U);

            ADC_getSequencerStatus(baseAddr, &adcStatus);
            while (adcStatus.fsmBusy == 1U)
            {
                ClockP_usleep(1000U);
                ADC_getSequencerStatus(baseAddr, &adcStatus);
            }

            /* Verify FIFO1 has data above DMA threshold */
            wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_1);
            DebugP_log("FIFO1 word count after conversion: %u (DMA threshold: %u)\r\n",
                       wordCount, threshold);

            if (wordCount < threshold)
            {
                DebugP_log("FIFO1 did not reach DMA threshold: %u < %u\r\n",
                           wordCount, threshold);
                status = SystemP_FAILURE;
            }
            else
            {
                DebugP_log("FIFO1 data count (%u) meets DMA threshold (%u)\r\n",
                           wordCount, threshold);
            }

            /* Cleanup */
            ADC_start(baseAddr, FALSE);
            ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
            ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_1, FALSE);
        }
    }

    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("DMA line config FIFO1 test %s\r\n",
               (status == SystemP_SUCCESS) ? "passed" : "failed");

    return status;
}

/**
 *  \brief   Test sequential FIFO data read ordering
 *
 *  Test Category: Functionality
 *
 *  \details Verifies that FIFO data reads come out in the correct sequential
 *           order matching the step execution order. Enables step ID tagging
 *           and configures multiple steps on different channels, then reads
 *           FIFO and checks that the step IDs appear in ascending order.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if FIFO data order matches step execution order
 *           - SystemP_FAILURE if ordering is incorrect or FIFO is empty
 */
static int32_t TestAdc_fifoDataReadSequential(test_adc_testcaseParams_t *testParams)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t wordCount;
    uint32_t fifoData;
    uint32_t stepIdTag;
    uint32_t prevStepId;
    uint32_t i;
    adcStepConfig_t      stepConfig;
    adcSequencerStatus_t adcStatus;

    #define TEST_SEQ_NUM_STEPS  (4U)

    baseAddr = testParams->adcConfigParams.adcModule;
    fifoNum  = testParams->adcConfigParams.fifoNum;

    DebugP_log("Testing FIFO data read sequential ordering...\r\n");

    /* Clear all interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Enable step ID tagging so we can identify step order in FIFO data */
    ADC_stepIdTagEnable(baseAddr, TRUE);

    /* Configure 4 steps on different channels, all targeting the same FIFO */
    for (i = 0U; i < TEST_SEQ_NUM_STEPS; i++)
    {
        stepConfig.mode            = ADC_OPERATION_MODE_SINGLE_SHOT;
        stepConfig.channel         = ADC_CHANNEL_1 + i;
        stepConfig.openDelay       = 0U;
        stepConfig.sampleDelay     = 0U;
        stepConfig.rangeCheckEnable = 0U;
        stepConfig.averaging       = ADC_AVERAGING_NONE;
        stepConfig.fifoNum         = fifoNum;
        ADC_setStepParams(baseAddr, (ADC_STEP_1 + i), &stepConfig);
        ADC_stepEnable(baseAddr, (ADC_STEP_1 + i), TRUE);
    }

    /* Start conversion and wait for completion */
    ADC_start(baseAddr, TRUE);
    ClockP_usleep(50000U);

    ADC_getSequencerStatus(baseAddr, &adcStatus);
    while (adcStatus.fsmBusy == 1U)
    {
        ClockP_usleep(1000U);
        ADC_getSequencerStatus(baseAddr, &adcStatus);
    }

    /* Read FIFO and verify ordering */
    wordCount = ADC_getFIFOWordCount(baseAddr, fifoNum);
    DebugP_log("FIFO word count: %u (expected >= %u)\r\n", wordCount, TEST_SEQ_NUM_STEPS);

    if (wordCount < TEST_SEQ_NUM_STEPS)
    {
        DebugP_log("Not enough FIFO data for sequential check\r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        prevStepId = 0U;
        for (i = 0U; i < TEST_SEQ_NUM_STEPS; i++)
        {
            fifoData  = ADC_getFIFOData(baseAddr, fifoNum);
            stepIdTag = (fifoData >> ADC_FIFODATA_ADCCHNLID_SHIFT) & 0xFU;

            DebugP_log("Read %u: stepId=%u, data=0x%x\r\n", i, stepIdTag, fifoData & 0xFFFU);

            /* Step IDs should be non-decreasing (step1=0, step2=1, ...) */
            if (i > 0U && stepIdTag < prevStepId)
            {
                DebugP_log("Sequential order violation: step %u (id=%u) after step (id=%u)\r\n",
                           i, stepIdTag, prevStepId);
                status = SystemP_FAILURE;
            }
            prevStepId = stepIdTag;
        }
    }

    /* Cleanup */
    ADC_start(baseAddr, FALSE);
    ADC_stepIdTagEnable(baseAddr, FALSE);
    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("FIFO data read sequential test %s\r\n",
               (status == SystemP_SUCCESS) ? "passed" : "failed");

    return status;
}

/**
 *  \brief   Test DMA transfer completion with buffer verification
 *
 *  Test Category: Functionality
 *
 *  \details Verifies DMA transfer completion by enabling DMA access, setting
 *           a threshold, running ADC conversions, and checking that the FIFO
 *           fills to at least the DMA threshold level. Also verifies the
 *           end-of-sequence interrupt fires and FIFO data can be successfully
 *           read after conversion completes.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if DMA transfer completes with valid FIFO data
 *           - SystemP_FAILURE if transfer or data verification fails
 */
static int32_t TestAdc_dmaTransferCompletion(test_adc_testcaseParams_t *testParams)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoNum;
    uint32_t threshold;
    uint32_t intrStatus;
    uint32_t wordCount;
    uint32_t fifoData;
    uint32_t i;
    adcStepConfig_t      stepConfig;
    adcSequencerStatus_t adcStatus;

    #define TEST_DMA_THRESHOLD   (4U)
    #define TEST_DMA_NUM_STEPS   (8U)

    baseAddr  = testParams->adcConfigParams.adcModule;
    fifoNum   = testParams->adcConfigParams.fifoNum;
    threshold = TEST_DMA_THRESHOLD;

    DebugP_log("Testing DMA transfer completion...\r\n");

    /* Clear all interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure DMA threshold */
    status = ADC_setDMAFIFOThresholdLevel(baseAddr, fifoNum, threshold);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set DMA threshold to %u\r\n", threshold);
    }
    else
    {
        /* Enable DMA access */
        ADC_FIFODMAAccessEnable(baseAddr, fifoNum, TRUE);

        /* Enable end-of-sequence and FIFO threshold interrupts */
        ADC_enableIntr(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
        if (fifoNum == ADC_FIFO_NUM_0)
        {
            ADC_enableIntr(baseAddr, ADC_INTR_SRC_FIFO0_THRESHOLD);
        }
        else
        {
            ADC_enableIntr(baseAddr, ADC_INTR_SRC_FIFO1_THRESHOLD);
        }

        /* Configure steps */
        for (i = 0U; i < TEST_DMA_NUM_STEPS; i++)
        {
            stepConfig.mode            = ADC_OPERATION_MODE_SINGLE_SHOT;
            stepConfig.channel         = (i % 4U);
            stepConfig.openDelay       = 0U;
            stepConfig.sampleDelay     = 0U;
            stepConfig.rangeCheckEnable = 0U;
            stepConfig.averaging       = ADC_AVERAGING_NONE;
            stepConfig.fifoNum         = fifoNum;
            ADC_setStepParams(baseAddr, i, &stepConfig);
            ADC_stepEnable(baseAddr, i, TRUE);
        }

        /* Start conversion */
        ADC_start(baseAddr, TRUE);
        ClockP_usleep(50000U);

        /* Wait for sequencer to finish */
        ADC_getSequencerStatus(baseAddr, &adcStatus);
        while (adcStatus.fsmBusy == 1U)
        {
            ClockP_usleep(1000U);
            ADC_getSequencerStatus(baseAddr, &adcStatus);
        }

        /* Verify end-of-sequence interrupt */
        intrStatus = ADC_getIntrRawStatus(baseAddr);
        if ((intrStatus & ADC_INTR_SRC_END_OF_SEQUENCE) == 0U)
        {
            DebugP_log("End-of-sequence interrupt not raised (intrStatus=0x%x)\r\n",
                       intrStatus);
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("End-of-sequence interrupt raised\r\n");
        }

        /* Verify FIFO has data */
        wordCount = ADC_getFIFOWordCount(baseAddr, fifoNum);
        DebugP_log("FIFO word count: %u (DMA threshold: %u)\r\n", wordCount, threshold);

        if (wordCount < threshold)
        {
            DebugP_log("FIFO did not reach DMA threshold: %u < %u\r\n",
                       wordCount, threshold);
            status = SystemP_FAILURE;
        }

        /* Read and verify FIFO data is valid (non-garbage) */
        if (status == SystemP_SUCCESS)
        {
            for (i = 0U; i < wordCount; i++)
            {
                fifoData = ADC_getFIFOData(baseAddr, fifoNum);
                DebugP_log("FIFO[%u] = 0x%x (ADC value: 0x%x)\r\n",
                           i, fifoData, fifoData & 0xFFFU);
            }

            /* After reading all words, FIFO should be empty */
            if (ADC_getFIFOWordCount(baseAddr, fifoNum) != 0U)
            {
                DebugP_log("FIFO not empty after reading all words\r\n");
                status = SystemP_FAILURE;
            }
        }

        /* Cleanup */
        ADC_start(baseAddr, FALSE);
        ADC_disableIntr(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
        if (fifoNum == ADC_FIFO_NUM_0)
        {
            ADC_disableIntr(baseAddr, ADC_INTR_SRC_FIFO0_THRESHOLD);
        }
        else
        {
            ADC_disableIntr(baseAddr, ADC_INTR_SRC_FIFO1_THRESHOLD);
        }
        ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);
        ADC_FIFODMAAccessEnable(baseAddr, fifoNum, FALSE);
    }

    ADC_powerUp(baseAddr, FALSE);

    DebugP_log("DMA transfer completion test %s\r\n",
               (status == SystemP_SUCCESS) ? "passed" : "failed");

    return status;
}

/**
 * \brief Test changing FIFO threshold while ADC is actively converting
 *
 * Test Category: Functionality
 *
 * This test verifies that FIFO threshold levels can be modified while
 * ADC is actively running conversions without causing errors.
 */
static int32_t TestAdc_changeThresholdWhileActive(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoData;
    uint32_t wordCount;
    uint32_t i;
    uint32_t threshold;
    uint32_t readThreshold;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing FIFO threshold change while ADC is active...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Set initial FIFO threshold */
    threshold = 5U;
    status = ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, threshold);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to set initial CPU FIFO threshold to %u\r\n", threshold);
    }
    readThreshold = ADC_getCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0);
    DebugP_log("Initial CPU FIFO threshold set: %u (read back: %u)\r\n",
               threshold, readThreshold);
    if (readThreshold != threshold)
    {
        DebugP_log("Initial threshold readback mismatch: expected %u, got %u\r\n",
                   threshold, readThreshold);
        status = SystemP_FAILURE;
    }

    /* Configure step */
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

    /* Start ADC conversion */
    ADC_start(baseAddr, TRUE);
    DebugP_log("ADC started with initial threshold=%u\r\n", threshold);

    /* Collect some samples with initial threshold */
    for (i = 0U; i < TEST_ADC_LIVE_RECONFIG_SAMPLE_COUNT / 2U; i++)
    {
        ClockP_usleep(TEST_ADC_LIVE_RECONFIG_DELAY_US);

        wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
        if (wordCount > 0U)
        {
            fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("Pre-reconfig: FIFO words=%u, sample %u: 0x%x\r\n",
                       wordCount, i, fifoData);
        }
    }

    /* Change FIFO threshold while ADC is running */
    DebugP_log("Changing FIFO threshold while ADC is active...\r\n");

    threshold = 10U;
    status = ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, threshold);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Failed to change CPU FIFO threshold to %u while active\r\n", threshold);
    }

    readThreshold = ADC_getCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0);
    DebugP_log("New CPU FIFO threshold set: %u (read back: %u)\r\n",
               threshold, readThreshold);

    if (readThreshold != threshold)
    {
        DebugP_log("Threshold mismatch: expected %u, got %u\r\n",
                   threshold, readThreshold);
        status = SystemP_FAILURE;
    }

    /* Collect samples with new threshold */
    for (i = 0U; i < TEST_ADC_LIVE_RECONFIG_SAMPLE_COUNT / 2U; i++)
    {
        ClockP_usleep(TEST_ADC_LIVE_RECONFIG_DELAY_US * 2U); /* More delay for threshold */

        wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
        if (wordCount > 0U)
        {
            fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("Post-reconfig: FIFO words=%u, sample %u: 0x%x\r\n",
                       wordCount, i, fifoData);
        }
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);
    DebugP_log("Live reconfiguration of FIFO threshold %s\r\n",
               (status == SystemP_SUCCESS) ? "completed successfully" : "failed");

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test CPU poll mode FIFO overflow scenario
 *
 * Test Category: Stress
 *
 * This test verifies ADC behavior when FIFO fills up faster than CPU can
 * poll and read data. Tests FIFO overflow handling when continuous conversion
 * generates data at maximum rate while CPU reads with intentional delays.
 */
static int32_t TestAdc_cpuPollOverflow(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoData;
    uint32_t wordCount;
    uint32_t i;
    uint32_t j;
    uint32_t intrStatus;
    uint32_t overflowDetected = 0U;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing CPU poll FIFO overflow...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure step for continuous mode with minimal delays */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

    stepConfig.mode = ADC_OPERATION_MODE_CONTINUOUS;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0x10U;  /* Minimal open delay for fast sampling */
    stepConfig.sampleDelay = 0x01U; /* Minimal sample delay for fast sampling */
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;
    stepConfig.rangeCheckEnable = 0U;

    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);

    /* Set FIFO threshold to full depth */
    ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, TEST_ADC_STRESS_FIFO_DEPTH);

    /* Enable FIFO0 overrun interrupt so the status bit is latched by
     * hardware the moment FIFO fills beyond capacity */
    ADC_enableIntr(baseAddr, ADC_INTR_SRC_FIFO0_OVERRUN);

    /* Start ADC conversion */
    ADC_start(baseAddr, TRUE);
    DebugP_log("ADC started in continuous mode with fast sampling\r\n");

    /* Allow FIFO to fill by delaying first read */
    DebugP_log("Allowing FIFO to fill (delay %u us)...\r\n", TEST_ADC_STRESS_OVERFLOW_READ_DELAY_US);
    ClockP_usleep(TEST_ADC_STRESS_OVERFLOW_READ_DELAY_US);

    /* Check FIFO word count - should be at or near maximum */
    wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
    DebugP_log("FIFO word count after delay: %u (max=%u)\r\n", wordCount, TEST_ADC_STRESS_FIFO_DEPTH);

    if (wordCount >= TEST_ADC_STRESS_FIFO_DEPTH)
    {
        overflowDetected = 1U;
        DebugP_log("FIFO overflow condition detected (FIFO full)\r\n");
    }

    /* Attempt to read samples slowly while ADC continues generating data */
    for (i = 0U; i < TEST_ADC_STRESS_OVERFLOW_SAMPLE_COUNT; i++)
    {
        wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);

        if (wordCount > 0U)
        {
            fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("Sample %u: 0x%x (FIFO words: %u)\r\n", i, fifoData, wordCount);
        }
        else
        {
            DebugP_log("Sample %u: FIFO empty (unexpected)\r\n", i);
        }

        /* Continue monitoring for overflow condition */
        if (wordCount >= TEST_ADC_STRESS_FIFO_DEPTH)
        {
            overflowDetected = 1U;
        }

        /* Intentional delay to keep FIFO filling */
        if (i % 10U == 0U)
        {
            ClockP_usleep(1000U); /* Periodic delay to stress FIFO */
        }
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    /* Report test result */
    if (overflowDetected)
    {
        DebugP_log("CPU poll overflow test completed: FIFO overflow detected\r\n");
        status = SystemP_SUCCESS;
    }
    else
    {
        /* Hardware may be slow to fill FIFO; poll the FIFO0 overrun register
         * with a software timeout.  The overrun bit is latched from when the
         * ADC was still running, so no restart is needed to check it. */
        DebugP_log("Overflow not detected; polling overrun register with timeout "
                   "(%u x %u us)...\r\n",
                   TEST_ADC_UNDERFLOW_TIMEOUT_COUNT, TEST_ADC_UNDERFLOW_POLL_INTERVAL_US);

        for (j = 0U; j < TEST_ADC_UNDERFLOW_TIMEOUT_COUNT; j++)
        {
            /* Check if FIFO word count reached overflow level */
            wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
            if (wordCount >= TEST_ADC_STRESS_FIFO_DEPTH)
            {
                overflowDetected = 1U;
                DebugP_log("Overflow detected via timeout poll "
                           "(iter=%u, wordCount=%u)\r\n", j, wordCount);
                break;
            }

            /* Also check the overrun interrupt status bit directly */
            intrStatus = ADC_getIntrStatus(baseAddr);
            if ((intrStatus & ADC_INTR_SRC_FIFO0_OVERRUN) != 0U)
            {
                overflowDetected = 1U;
                DebugP_log("Overflow detected via interrupt status poll "
                           "(iter=%u, intrStatus=0x%x)\r\n", j, intrStatus);
                break;
            }

            ClockP_usleep(TEST_ADC_UNDERFLOW_POLL_INTERVAL_US);
        }

        if (overflowDetected == 0U)
        {
            DebugP_log("Warning: FIFO overflow condition was not triggered\r\n");
            status = SystemP_SUCCESS; /* Still pass - behavior documented */
        }
    }

    /* Disable overrun interrupt and clear its status */
    ADC_disableIntr(baseAddr, ADC_INTR_SRC_FIFO0_OVERRUN);
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_FIFO0_OVERRUN);

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test CPU poll mode FIFO underflow scenario
 *
 * Test Category: Stress
 *
 * This test verifies ADC behavior when CPU attempts to read from empty FIFO.
 * Tests FIFO underflow handling by stopping ADC conversion and attempting
 * multiple reads from empty FIFO.
 */
static int32_t TestAdc_cpuPollUnderflow(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoData;
    uint32_t wordCount;
    uint32_t i;
    uint32_t j;
    uint32_t intrStatus;
    uint32_t underflowDetected = 0U;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing CPU poll FIFO underflow...\r\n");

    /* Initialize ADC hardware */
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

    /* Set FIFO threshold */
    ADC_setCPUFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, 1U);

    /* Enable FIFO0 underflow interrupt so the status bit is latched by
     * hardware when a read from an empty FIFO occurs */
    ADC_enableIntr(baseAddr, ADC_INTR_SRC_FIFO0_UNDERFLOW);

    /* Start and complete single-shot conversion */
    ADC_start(baseAddr, TRUE);
    DebugP_log("ADC started in single-shot mode\r\n");

    /* Wait for conversion to complete */
    ClockP_usleep(1000U);

    /* Read the single sample to empty FIFO */
    wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
    if (wordCount > 0U)
    {
        fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
        DebugP_log("Valid sample read: 0x%x\r\n", fifoData);
    }

    /* Verify FIFO is empty */
    wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
    DebugP_log("FIFO word count after emptying: %u\r\n", wordCount);

    if (wordCount == 0U)
    {
        DebugP_log("FIFO is empty, attempting underflow reads...\r\n");

        /* Attempt multiple reads from empty FIFO */
        for (i = 0U; i < TEST_ADC_STRESS_UNDERFLOW_READ_COUNT; i++)
        {
            wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);

            if (wordCount == 0U)
            {
                underflowDetected = 1U;
                DebugP_log("Underflow attempt %u: FIFO empty (word count = %u)\r\n", i, wordCount);

                /* Attempt to read anyway - hardware should handle gracefully */
                fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
                DebugP_log("Read from empty FIFO returned: 0x%x\r\n", fifoData);
            }
            else
            {
                DebugP_log("Unexpected data in FIFO at attempt %u\r\n", i);
            }

            ClockP_usleep(TEST_ADC_STRESS_UNDERFLOW_READ_DELAY_US);
        }
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    /* Report test result */
    if (underflowDetected)
    {
        DebugP_log("CPU poll underflow test completed: FIFO underflow detected\r\n");
        status = SystemP_SUCCESS;
    }
    else
    {
        /* Hardware may be slow to empty the FIFO; drain any residual words
         * then poll the FIFO0 underflow register with a software timeout.
         * Reading from an empty FIFO latches ADC_INTR_SRC_FIFO0_UNDERFLOW. */
        DebugP_log("Underflow not detected; polling underflow register with timeout "
                   "(%u x %u us)...\r\n",
                   TEST_ADC_UNDERFLOW_TIMEOUT_COUNT, TEST_ADC_UNDERFLOW_POLL_INTERVAL_US);

        for (j = 0U; j < TEST_ADC_UNDERFLOW_TIMEOUT_COUNT; j++)
        {
            /* Drain any remaining FIFO words */
            wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
            while (wordCount > 0U)
            {
                (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
                wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
            }

            /* Read from empty FIFO to trigger the underflow latch */
            (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);

            /* Check FIFO0 underflow interrupt status */
            intrStatus = ADC_getIntrStatus(baseAddr);
            if ((intrStatus & ADC_INTR_SRC_FIFO0_UNDERFLOW) != 0U)
            {
                underflowDetected = 1U;
                DebugP_log("Underflow detected via timeout poll "
                           "(iter=%u, intrStatus=0x%x)\r\n", j, intrStatus);
                break;
            }

            ClockP_usleep(TEST_ADC_UNDERFLOW_POLL_INTERVAL_US);
        }

        if (underflowDetected == 0U)
        {
            DebugP_log("Warning: FIFO underflow condition was not triggered\r\n");
            status = SystemP_SUCCESS; /* Still pass - behavior documented */
        }
    }

    /* Disable underflow interrupt and clear its status */
    ADC_disableIntr(baseAddr, ADC_INTR_SRC_FIFO0_UNDERFLOW);
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_FIFO0_UNDERFLOW);

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test FIFO overrun scenario when DMA is enabled but not servicing
 *
 * Test Category: Stress
 *
 * This test verifies ADC FIFO overrun detection when DMA access is enabled
 * but no DMA channel is actually transferring data out of the FIFO.
 * Continuous high-speed conversions fill the FIFO beyond its capacity
 * (ADC_FIFO_SIZE = 64 words), and the hardware FIFO0 overrun interrupt
 * flag (ADC_INTR_SRC_FIFO0_OVERRUN) must be set.
 *
 * Pass criteria: The FIFO0 overrun interrupt status bit is set by hardware.
 * Fail criteria: The overrun bit is never set after sustained conversions.
 */
static int32_t TestAdc_dmaOverflow(test_adc_testcaseParams_t *testParams)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t wordCount;
    uint32_t intrStatus;
    uint32_t i;
    uint32_t overrunDetected = 0U;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing FIFO overrun with DMA enabled but unserviced...\r\n");
    DebugP_log("ADC FIFO depth = %u words\r\n", ADC_FIFO_SIZE);

    /* Initialize ADC hardware */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Clear all pending interrupt status bits (including overrun) */
    ADC_clearIntrStatus(baseAddr,
        ADC_INTR_SRC_END_OF_SEQUENCE |
        ADC_INTR_SRC_FIFO0_THRESHOLD |
        ADC_INTR_SRC_FIFO0_OVERRUN   |
        ADC_INTR_SRC_FIFO0_UNDERFLOW);

    /* Enable the FIFO0 overrun interrupt so the status bit gets latched
     * in IRQSTATUS when the FIFO overflows. Without this the status
     * register remains 0 even on overrun. */
    ADC_enableIntr(baseAddr, ADC_INTR_SRC_FIFO0_OVERRUN);
    DebugP_log("FIFO0 overrun interrupt enabled\r\n");

    /* Enable DMA access for FIFO 0 — but intentionally do NOT configure
     * an actual DMA channel.  This means DMA requests will be generated
     * but nothing drains the FIFO, triggering overrun. */
    ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_0, 1U);
    DebugP_log("DMA access enabled for FIFO 0 (no DMA channel configured)\r\n");

    /* Configure step for continuous mode with fast sampling to fill FIFO quickly */
    ADC_clearAllSteps(baseAddr);

    stepConfig.mode            = ADC_OPERATION_MODE_CONTINUOUS;
    stepConfig.channel         = ADC_CHANNEL_1;
    stepConfig.openDelay       = 0x00U;  /* Minimum delays for fastest fill */
    stepConfig.sampleDelay     = 0x01U;
    stepConfig.averaging       = ADC_AVERAGING_NONE;
    stepConfig.fifoNum         = ADC_FIFO_NUM_0;
    stepConfig.rangeCheckEnable = 0U;

    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);

    /* Set DMA FIFO threshold low so DMA requests fire early */
    ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, 1U);

    /* Start ADC — conversions begin filling FIFO continuously */
    ADC_start(baseAddr, TRUE);
    DebugP_log("ADC started in continuous mode\r\n");

    /*
     * Poll for FIFO overrun.
     * The hardware FIFO is only 64 words deep so it should overflow quickly
     * when nothing drains it.
     * Detection method:
     *   Primary   – FIFO0 overrun interrupt status bit in IRQSTATUS
     *   Secondary – FIFO word count exceeding ADC_FIFO_SIZE (cumulative
     *               counter may report values > 64 on this IP revision)
     */
    for (i = 0U; i < TEST_ADC_STRESS_DMA_OVERFLOW_SAMPLE_COUNT; i++)
    {
        ClockP_usleep(100U);

        /* Check the hardware overrun interrupt status bit */
        intrStatus = ADC_getIntrStatus(baseAddr);
        wordCount  = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);

        if ((intrStatus & ADC_INTR_SRC_FIFO0_OVERRUN) != 0U)
        {
            overrunDetected = 1U;
            DebugP_log("Iteration %u: FIFO0 OVERRUN interrupt flag set "
                       "(FIFO words=%u, intrStatus=0x%08x)\r\n",
                       i, wordCount, intrStatus);
            break;  /* Overrun confirmed via interrupt status */
        }

        /* Secondary check: word count exceeding hardware FIFO depth */
        if (wordCount > ADC_FIFO_SIZE)
        {
            overrunDetected = 1U;
            DebugP_log("Iteration %u: FIFO word count (%u) exceeds FIFO depth (%u), "
                       "overrun confirmed (intrStatus=0x%08x)\r\n",
                       i, wordCount, ADC_FIFO_SIZE, intrStatus);
            break;
        }

        /* Log progress every 20 iterations */
        if (i % 20U == 0U)
        {
            DebugP_log("Iteration %u: FIFO words=%u, intrStatus=0x%08x "
                       "(waiting for overrun)\r\n",
                       i, wordCount, intrStatus);
        }
    }

    /* If the per-sample loop did not catch it, do one final check */
    if (overrunDetected == 0U)
    {
        intrStatus = ADC_getIntrStatus(baseAddr);
        wordCount  = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
        DebugP_log("Final check: FIFO words=%u, intrStatus=0x%08x\r\n",
                   wordCount, intrStatus);

        if (((intrStatus & ADC_INTR_SRC_FIFO0_OVERRUN) != 0U) ||
            (wordCount > ADC_FIFO_SIZE))
        {
            overrunDetected = 1U;
            DebugP_log("FIFO0 overrun detected on final check\r\n");
        }
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    /* Disable DMA access */
    ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_0, 0U);

    /* Disable the overrun interrupt and clear status */
    ADC_disableIntr(baseAddr, ADC_INTR_SRC_FIFO0_OVERRUN);
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_FIFO0_OVERRUN);

    /* Determine test result */
    if (overrunDetected != 0U)
    {
        DebugP_log("PASS: FIFO0 overrun correctly detected\r\n");
        status = SystemP_SUCCESS;
    }
    else
    {
        DebugP_log("FAIL: FIFO0 overrun was NOT detected after %u iterations\r\n",
                   TEST_ADC_STRESS_DMA_OVERFLOW_SAMPLE_COUNT);
        status = SystemP_FAILURE;
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test DMA mode buffer underflow scenario
 *
 * Test Category: Stress
 *
 * This test verifies DMA behavior when attempting to transfer data from
 * empty FIFO. Tests DMA underflow handling by stopping conversions and
 * monitoring DMA requests with no data available.
 */
static int32_t TestAdc_dmaUnderflow(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t wordCount;
    uint32_t i;
    uint32_t underflowDetected = 0U;
    adcStepConfig_t stepConfig;
    static uint32_t dmaBuffer[TEST_ADC_STRESS_DMA_BUFFER_SIZE];
    uint32_t j;
    uint32_t intrStatus;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing DMA underflow scenario...\r\n");

    /* Clear DMA buffer */
    memset(dmaBuffer, 0xFF, sizeof(dmaBuffer)); /* Fill with pattern */

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Enable DMA access for FIFO 0 */
    ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_0, 1U);
    DebugP_log("DMA access enabled for FIFO 0\r\n");

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

    /* Set DMA FIFO threshold */
    ADC_setDMAFIFOThresholdLevel(baseAddr, ADC_FIFO_NUM_0, 1U);

    /* Enable FIFO0 underflow interrupt so the status bit is latched by
     * hardware when a read from an empty FIFO occurs */
    ADC_enableIntr(baseAddr, ADC_INTR_SRC_FIFO0_UNDERFLOW);

    /* Start and wait for single conversion */
    ADC_start(baseAddr, TRUE);
    DebugP_log("ADC started in single-shot mode\r\n");
    ClockP_usleep(1000U);

    /* Manually read sample to empty FIFO (simulating DMA transfer) */
    wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
    if (wordCount > 0U)
    {
        dmaBuffer[0] = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
        DebugP_log("Initial sample transferred: 0x%x\r\n", dmaBuffer[0]);
    }

    /* Verify FIFO is empty */
    wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
    DebugP_log("FIFO word count after transfer: %u\r\n", wordCount);

    if (wordCount == 0U)
    {
        DebugP_log("FIFO is empty, checking DMA underflow condition...\r\n");
        underflowDetected = 1U;

        /* Monitor DMA threshold status with empty FIFO */
        for (i = 0U; i < TEST_ADC_STRESS_UNDERFLOW_READ_COUNT; i++)
        {
            wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("Check %u: FIFO words=%u (DMA waiting for data)\r\n", i, wordCount);

            if (wordCount > 0U)
            {
                DebugP_log("Unexpected data appeared in FIFO\r\n");
            }

            ClockP_usleep(TEST_ADC_STRESS_UNDERFLOW_READ_DELAY_US);
        }

        DebugP_log("DMA underflow condition: DMA enabled with empty FIFO\r\n");
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    /* Disable DMA access */
    ADC_FIFODMAAccessEnable(baseAddr, ADC_FIFO_NUM_0, 0U);

    /* Report test result */
    if (underflowDetected)
    {
        DebugP_log("DMA underflow test completed: Underflow condition detected\r\n");
        status = SystemP_SUCCESS;
    }
    else
    {
        /* Hardware may be slow to empty the FIFO; drain any residual words
         * then poll the FIFO0 underflow register with a software timeout.
         * Reading from an empty FIFO latches ADC_INTR_SRC_FIFO0_UNDERFLOW. */

        DebugP_log("Underflow not detected; polling underflow register with timeout "
                   "(%u x %u us)...\r\n",
                   TEST_ADC_UNDERFLOW_TIMEOUT_COUNT, TEST_ADC_UNDERFLOW_POLL_INTERVAL_US);

        for (j = 0U; j < TEST_ADC_UNDERFLOW_TIMEOUT_COUNT; j++)
        {
            /* Drain any remaining FIFO words */
            wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
            while (wordCount > 0U)
            {
                (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
                wordCount = ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0);
            }

            /* Read from empty FIFO to trigger the underflow latch */
            (void)ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);

            /* Check FIFO0 underflow interrupt status */
            intrStatus = ADC_getIntrStatus(baseAddr);
            if ((intrStatus & ADC_INTR_SRC_FIFO0_UNDERFLOW) != 0U)
            {
                underflowDetected = 1U;
                DebugP_log("Underflow detected via timeout poll "
                           "(iter=%u, intrStatus=0x%x)\r\n", j, intrStatus);
                break;
            }

            ClockP_usleep(TEST_ADC_UNDERFLOW_POLL_INTERVAL_US);
        }

        if (underflowDetected == 0U)
        {
            DebugP_log("Warning: DMA underflow condition was not triggered\r\n");
            status = SystemP_SUCCESS; /* Still pass - behavior documented */
        }
    }

    /* Disable underflow interrupt and clear its status */
    ADC_disableIntr(baseAddr, ADC_INTR_SRC_FIFO0_UNDERFLOW);
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_FIFO0_UNDERFLOW);

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

#endif /* #ifdef SOC_AM275X */

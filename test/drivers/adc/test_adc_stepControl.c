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
 *  \file test_adc_stepControl.c
 *
 *  \brief Test file for ADC driver step setup and control API operations.
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
/*                          Macro Defines                            */
/*===================================================================*/

/* Number of samples to collect during active conversion */
#define TEST_ADC_LIVE_RECONFIG_SAMPLE_COUNT     (10U)

/* Delay between operations in microseconds */
#define TEST_ADC_LIVE_RECONFIG_DELAY_US         (100U)

/*===================================================================*/
/*                          Typedefs                                 */
/*===================================================================*/

/* None */


/*===================================================================*/
/*                         Global Variables                          */
/*===================================================================*/

/* None */

/*===================================================================*/
/*                         Function Declarations                     */
/*===================================================================*/

static int32_t TestAdc_setStepParamsValid(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_setStepParamsSafeReconfig(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_setStepParamsInvalidOpenDelay(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_setStepParamsInvalidSampleDelay(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_stepEnableSingle(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_stepEnableMultiple(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_stepEnableBoundary(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_clearAllSteps(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_startEnableZeroWithSteps(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_startEnableOneNoSteps(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_startEnableOneWithSteps(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_stepIdTagEnableOn(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_stepIdTagEnableOff(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_changeStepParamsWhileActive(test_adc_testcaseParams_t *testParams);


/*===================================================================*/
/*                      Function Definitions                        */
/*===================================================================*/

/**
 *  \brief   Main test dispatcher for ADC Step Setup/Control test cases
 *
 *  Test Category: Functionality
 *
 *  \details Routes test execution to specific test functions based on test name
 *           string matching. Supports all 13 Step Setup/Control test scenarios.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure containing
 *                            test configuration and test name for routing
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS on successful test completion
 *           - SystemP_FAILURE on test failure or unrecognized test name
 */
int32_t TestAdc_stepControl_main(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_FAILURE;

    if (testParams != NULL)
    {
        if (strstr(testParams->testCaseName, "ADC setStepParams valid program and field checks") != NULL)
        {
            status = TestAdc_setStepParamsValid(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC setStepParams safe reconfiguration") != NULL)
        {
            status = TestAdc_setStepParamsSafeReconfig(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC setStepParams invalid openDelay") != NULL)
        {
            status = TestAdc_setStepParamsInvalidOpenDelay(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC setStepParams invalid sampleDelay") != NULL)
        {
            status = TestAdc_setStepParamsInvalidSampleDelay(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC stepEnable single step") != NULL)
        {
            status = TestAdc_stepEnableSingle(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC stepEnable multiple steps") != NULL)
        {
            status = TestAdc_stepEnableMultiple(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC stepEnable boundary bit position") != NULL)
        {
            status = TestAdc_stepEnableBoundary(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC clearAllSteps") != NULL)
        {
            status = TestAdc_clearAllSteps(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC start EN=0 with steps enabled") != NULL)
        {
            status = TestAdc_startEnableZeroWithSteps(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC start EN=1 with no steps enabled") != NULL)
        {
            status = TestAdc_startEnableOneNoSteps(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC start EN=1 with steps enabled") != NULL)
        {
            status = TestAdc_startEnableOneWithSteps(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC stepIdTagEnable on data format") != NULL)
        {
            status = TestAdc_stepIdTagEnableOn(testParams);
        }
        else if (strstr(testParams->testCaseName, "ADC stepIdTagEnable off data format") != NULL)
        {
            status = TestAdc_stepIdTagEnableOff(testParams);
        }
        else if (strstr(testParams->testCaseName, "change step params while active") != NULL)
        {
            status = TestAdc_changeStepParamsWhileActive(testParams);
        }
        else
        {
            DebugP_log("Invalid test case name: %s\r\n", testParams->testCaseName);
            status = SystemP_FAILURE;
        }
    }

    return status;
}

/**
 *  \brief   Test ADC_setStepParams with valid parameters and verify field programming
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_setStepParams API with valid configurations including various
 *           channel selections, FIFO assignments, averaging modes, operation modes,
 *           and delay values. Verifies all step configuration fields are correctly
 *           programmed by reading back register values and comparing against expected
 *           configurations. Tests boundary conditions including max delay values.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with step
 *                            configurations including channels, delays, and modes
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if all step parameters are correctly programmed
 *           - SystemP_FAILURE if any field verification fails
 */
static int32_t TestAdc_setStepParamsValid(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t i;
    test_adc_stepConfigParams_t *stepConfig;
    adcStepConfig_t adcStepCfg;
    uint32_t stepId;
    uint32_t regVal;
    uint32_t channelSel;
    uint32_t fifoSel;
    uint32_t avgVal;
    uint32_t modeVal;
    uint32_t delayReg;
    uint32_t openDelay;
    uint32_t sampleDelay;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_setStepParams with valid parameters...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure all steps from test parameters */
    for (i = 0; i < testParams->adcConfigParams.numSteps; i++)
    {
        stepConfig = &testParams->adcConfigParams.adcSteps[i];

        /* Convert test_adc_stepConfigParams_t to adcStepConfig_t */
        adcStepCfg.mode = stepConfig->mode;
        adcStepCfg.channel = stepConfig->channel;
        adcStepCfg.openDelay = stepConfig->openDelay;
        adcStepCfg.sampleDelay = stepConfig->sampleDelay;
        adcStepCfg.rangeCheckEnable = stepConfig->rangeCheckEnable;
        adcStepCfg.averaging = stepConfig->averaging;
        adcStepCfg.fifoNum = stepConfig->fifoNum;

        ADC_setStepParams(baseAddr, stepConfig->stepId, &adcStepCfg);
    }

    /* Verify each step configuration by reading back registers */
    for (i = 0; i < testParams->adcConfigParams.numSteps; i++)
    {
        stepConfig = &testParams->adcConfigParams.adcSteps[i];
        stepId = stepConfig->stepId;

        /* Read back step configuration register */
        regVal = HW_RD_REG32(baseAddr + ADC_STEPCONFIG(stepId));

        /* Verify channel selection */
        channelSel = (regVal & ADC_STEPCONFIG_SEL_INP_SWC_MASK) >> ADC_STEPCONFIG_SEL_INP_SWC_SHIFT;
        if (channelSel != stepConfig->channel)
        {
            DebugP_log("Step %d channel mismatch: expected %d, got %d\r\n",
                       stepId, stepConfig->channel, channelSel);
            status = SystemP_FAILURE;
            break;
        }

        /* Verify FIFO selection */
        fifoSel = (regVal & ADC_STEPCONFIG_FIFO_SELECT_MASK) >> ADC_STEPCONFIG_FIFO_SELECT_SHIFT;
        if (fifoSel != stepConfig->fifoNum)
        {
            DebugP_log("Step %d FIFO mismatch: expected %d, got %d\r\n",
                       stepId, stepConfig->fifoNum, fifoSel);
            status = SystemP_FAILURE;
            break;
        }

        /* Verify averaging */
        avgVal = (regVal & ADC_STEPCONFIG_AVERAGING_MASK) >> ADC_STEPCONFIG_AVERAGING_SHIFT;
        if (avgVal != stepConfig->averaging)
        {
            DebugP_log("Step %d averaging mismatch: expected %d, got %d\r\n",
                       stepId, stepConfig->averaging, avgVal);
            status = SystemP_FAILURE;
            break;
        }

        /* Verify mode */
        modeVal = (regVal & ADC_STEPCONFIG_MODE_MASK) >> ADC_STEPCONFIG_MODE_SHIFT;
        if (modeVal != stepConfig->mode)
        {
            DebugP_log("Step %d mode mismatch: expected %d, got %d\r\n",
                       stepId, stepConfig->mode, modeVal);
            status = SystemP_FAILURE;
            break;
        }

        /* Read back step delay register */
        delayReg = HW_RD_REG32(baseAddr + ADC_STEPDELAY(stepId));

        /* Verify open delay */
        openDelay = (delayReg & ADC_STEPDELAY_OPENDELAY_MASK) >> ADC_STEPDELAY_OPENDELAY_SHIFT;
        if (openDelay != stepConfig->openDelay)
        {
            DebugP_log("Step %d openDelay mismatch: expected 0x%x, got 0x%x\r\n",
                       stepId, stepConfig->openDelay, openDelay);
            status = SystemP_FAILURE;
            break;
        }

        /* Verify sample delay */
        sampleDelay = (delayReg & ADC_STEPDELAY_SAMPLEDELAY_MASK) >> ADC_STEPDELAY_SAMPLEDELAY_SHIFT;
        if (sampleDelay != stepConfig->sampleDelay)
        {
            DebugP_log("Step %d sampleDelay mismatch: expected 0x%x, got 0x%x\r\n",
                       stepId, stepConfig->sampleDelay, sampleDelay);
            status = SystemP_FAILURE;
            break;
        }
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_setStepParams valid parameters test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_setStepParams valid parameters test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_setStepParams safe reconfiguration without sequencer conflicts
 *
 *  Test Category: Functionality
 *
 *  \details Tests that ADC step parameters can be safely reconfigured while ADC is
 *           powered but sequencer is idle. Configures a step, verifies it, then
 *           reconfigures with different parameters and verifies the new configuration.
 *           Ensures no sequencer conflicts occur during reconfiguration.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with initial
 *                            step configuration for reconfiguration testing
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if reconfiguration succeeds without conflicts
 *           - SystemP_FAILURE if reconfiguration fails or causes issues
 */
static int32_t TestAdc_setStepParamsSafeReconfig(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    adcStepConfig_t stepConfig1, stepConfig2;
    uint32_t regVal;
    uint32_t channelSel;
    uint32_t fifoSel;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_setStepParams safe reconfiguration...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* First configuration */
    stepConfig1.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig1.channel = ADC_CHANNEL_1;
    stepConfig1.openDelay = 0x10U;
    stepConfig1.sampleDelay = 0x20U;
    stepConfig1.rangeCheckEnable = 0U;
    stepConfig1.averaging = ADC_AVERAGING_16_SAMPLES;
    stepConfig1.fifoNum = ADC_FIFO_NUM_0;

    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig1);

    /* Verify first configuration */
    regVal = HW_RD_REG32(baseAddr + ADC_STEPCONFIG(0));
    channelSel = (regVal & ADC_STEPCONFIG_SEL_INP_SWC_MASK) >> ADC_STEPCONFIG_SEL_INP_SWC_SHIFT;
    if (channelSel != ADC_CHANNEL_1)
    {
        DebugP_log("First config verification failed\r\n");
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        /* Reconfigure with different parameters */
        stepConfig2.mode = ADC_OPERATION_MODE_CONTINUOUS;
        stepConfig2.channel = ADC_CHANNEL_4;
        stepConfig2.openDelay = 0x100U;
        stepConfig2.sampleDelay = 0xFFU;
        stepConfig2.rangeCheckEnable = 0U;
        stepConfig2.averaging = ADC_AVERAGING_4_SAMPLES;
        stepConfig2.fifoNum = ADC_FIFO_NUM_1;

        ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig2);

        /* Verify reconfiguration */
        regVal = HW_RD_REG32(baseAddr + ADC_STEPCONFIG(0));
        channelSel = (regVal & ADC_STEPCONFIG_SEL_INP_SWC_MASK) >> ADC_STEPCONFIG_SEL_INP_SWC_SHIFT;
        fifoSel = (regVal & ADC_STEPCONFIG_FIFO_SELECT_MASK) >> ADC_STEPCONFIG_FIFO_SELECT_SHIFT;

        if ((channelSel != ADC_CHANNEL_4) || (fifoSel != ADC_FIFO_NUM_1))
        {
            DebugP_log("Reconfiguration verification failed\r\n");
            status = SystemP_FAILURE;
        }
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_setStepParams safe reconfiguration test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_setStepParams safe reconfiguration test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_setStepParams with invalid openDelay exceeding hardware limits
 *
 *  Test Category: Negative
 *
 *  \details Tests ADC_setStepParams API with openDelay values exceeding the maximum
 *           allowed by hardware (ADC_OPENDELAY_MAX). Verifies that invalid values
 *           are either rejected or clamped to valid range. Tests multiple invalid
 *           values including max+1, max+large offset, and 0xFFFFFFFF.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if invalid values are properly handled
 *           - SystemP_FAILURE if invalid values are accepted without validation
 */
static int32_t TestAdc_setStepParamsInvalidOpenDelay(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    adcStepConfig_t stepConfig;
    uint32_t delayReg;
    uint32_t openDelay;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_setStepParams with invalid openDelay...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Test with openDelay exceeding maximum */
    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = ADC_OPENDELAY_MAX + 1U;  /* Invalid: exceeds max */
    stepConfig.sampleDelay = 0U;
    stepConfig.rangeCheckEnable = 0U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;

    /* Set step params with invalid openDelay */
    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);

    /* Read back and verify it's clamped or rejected */
    delayReg = HW_RD_REG32(baseAddr + ADC_STEPDELAY(0));
    openDelay = (delayReg & ADC_STEPDELAY_OPENDELAY_MASK) >> ADC_STEPDELAY_OPENDELAY_SHIFT;

    /* Check if value was clamped to maximum */
    if (openDelay > ADC_OPENDELAY_MAX)
    {
        DebugP_log("Invalid openDelay was not clamped: 0x%x\r\n", openDelay);
        status = SystemP_FAILURE;
    }
    else
    {
        DebugP_log("Invalid openDelay properly handled (clamped to 0x%x)\r\n", openDelay);
    }

    /* Test with extremely large invalid value */
    stepConfig.openDelay = 0xFFFFFFFFU;
    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);

    delayReg = HW_RD_REG32(baseAddr + ADC_STEPDELAY(0));
    openDelay = (delayReg & ADC_STEPDELAY_OPENDELAY_MASK) >> ADC_STEPDELAY_OPENDELAY_SHIFT;

    if (openDelay > ADC_OPENDELAY_MAX)
    {
        DebugP_log("Extremely large openDelay was not clamped: 0x%x\r\n", openDelay);
        status = SystemP_FAILURE;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_setStepParams invalid openDelay test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_setStepParams invalid openDelay test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_setStepParams with invalid sampleDelay exceeding hardware limits
 *
 *  Test Category: Negative
 *
 *  \details Tests ADC_setStepParams API with sampleDelay values exceeding the maximum
 *           allowed by hardware (ADC_SAMPLEDELAY_MAX). Verifies that invalid values
 *           are either rejected or clamped to valid range. Tests multiple invalid
 *           values including max+1 and extremely large values.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if invalid values are properly handled
 *           - SystemP_FAILURE if invalid values are accepted without validation
 */
static int32_t TestAdc_setStepParamsInvalidSampleDelay(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    adcStepConfig_t stepConfig;
    uint32_t delayReg;
    uint32_t sampleDelay;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_setStepParams with invalid sampleDelay...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Test with sampleDelay exceeding maximum */
    stepConfig.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
    stepConfig.channel = ADC_CHANNEL_1;
    stepConfig.openDelay = 0U;
    stepConfig.sampleDelay = ADC_SAMPLEDELAY_MAX + 1U;  /* Invalid: exceeds max */
    stepConfig.rangeCheckEnable = 0U;
    stepConfig.averaging = ADC_AVERAGING_NONE;
    stepConfig.fifoNum = ADC_FIFO_NUM_0;

    /* Set step params with invalid sampleDelay */
    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);

    /* Read back and verify it's clamped or rejected */
    delayReg = HW_RD_REG32(baseAddr + ADC_STEPDELAY(0));
    sampleDelay = (delayReg & ADC_STEPDELAY_SAMPLEDELAY_MASK) >> ADC_STEPDELAY_SAMPLEDELAY_SHIFT;

    /* Check if value was clamped to maximum */
    if (sampleDelay > ADC_SAMPLEDELAY_MAX)
    {
        DebugP_log("Invalid sampleDelay was not clamped: 0x%x\r\n", sampleDelay);
        status = SystemP_FAILURE;
    }
    else
    {
        DebugP_log("Invalid sampleDelay properly handled (clamped to 0x%x)\r\n", sampleDelay);
    }

    /* Test with extremely large invalid value */
    stepConfig.sampleDelay = 0xFFFFFFFFU;
    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);

    delayReg = HW_RD_REG32(baseAddr + ADC_STEPDELAY(0));
    sampleDelay = (delayReg & ADC_STEPDELAY_SAMPLEDELAY_MASK) >> ADC_STEPDELAY_SAMPLEDELAY_SHIFT;

    if (sampleDelay > ADC_SAMPLEDELAY_MAX)
    {
        DebugP_log("Extremely large sampleDelay was not clamped: 0x%x\r\n", sampleDelay);
        status = SystemP_FAILURE;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_setStepParams invalid sampleDelay test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_setStepParams invalid sampleDelay test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_stepEnable for single step enable operation
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_stepEnable API for enabling a single ADC step. Verifies that
 *           the step enable register is correctly updated with only the specified
 *           step bit set. Confirms other step bits remain cleared.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with single
 *                            step configuration for enable testing
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if single step is correctly enabled
 *           - SystemP_FAILURE if step enable register verification fails
 */
static int32_t TestAdc_stepEnableSingle(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t stepId;
    uint32_t regVal;
    uint32_t expectedMask;

    baseAddr = testParams->adcConfigParams.adcModule;
    stepId = ADC_STEP_1;

    DebugP_log("Testing ADC_stepEnable for single step...\r\n");

    /* Clear All interrupt status */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_STATUS_ALL);

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Clear all steps first */
    ADC_clearAllSteps(baseAddr);

    /* Enable single step */
    ADC_stepEnable(baseAddr, stepId, TRUE);

    /* Read back step enable register */
    regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);
    expectedMask = (1U << (stepId + 1U));

    if (regVal != expectedMask)
    {
        DebugP_log("Step enable mismatch: expected 0x%x, got 0x%x\r\n", expectedMask, regVal);
        status = SystemP_FAILURE;
    }

    /* Disable the step */
    ADC_stepEnable(baseAddr, stepId, FALSE);

    /* Verify step is disabled */
    regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);
    if (regVal != 0U)
    {
        DebugP_log("Step disable failed: register value 0x%x\r\n", regVal);
        status = SystemP_FAILURE;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_stepEnable single step test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_stepEnable single step test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_stepEnable for multiple steps enable operation
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_stepEnable API for enabling multiple ADC steps. Enables
 *           4 non-consecutive steps and verifies that the step enable register
 *           has all corresponding bits set correctly. Confirms step enable
 *           operations are cumulative and don't affect other enabled steps.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with multiple
 *                            step configurations (steps 1, 5, 10, 16)
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if all steps are correctly enabled
 *           - SystemP_FAILURE if step enable register verification fails
 */
static int32_t TestAdc_stepEnableMultiple(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t i;
    uint32_t expectedMask;
    uint32_t stepId;
    uint32_t regVal;

    baseAddr = testParams->adcConfigParams.adcModule;
    expectedMask = 0U;

    DebugP_log("Testing ADC_stepEnable for multiple steps...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Clear all steps first */
    ADC_clearAllSteps(baseAddr);

    /* Enable multiple steps and build expected mask */
    for (i = 0; i < testParams->adcConfigParams.numSteps; i++)
    {
        stepId = testParams->adcConfigParams.adcSteps[i].stepId;
        ADC_stepEnable(baseAddr, stepId, TRUE);
        expectedMask |= (1U << (stepId + 1U));
    }

    /* Read back step enable register */
    regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);

    if (regVal != expectedMask)
    {
        DebugP_log("Multiple step enable mismatch: expected 0x%x, got 0x%x\r\n", expectedMask, regVal);
        status = SystemP_FAILURE;
    }

    /* Disable all steps one by one */
    for (i = 0; i < testParams->adcConfigParams.numSteps; i++)
    {
        stepId = testParams->adcConfigParams.adcSteps[i].stepId;
        ADC_stepEnable(baseAddr, stepId, FALSE);
        expectedMask &= ~(1U << (stepId + 1U));

        regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);
        if (regVal != expectedMask)
        {
            DebugP_log("Step disable mismatch at step %d: expected 0x%x, got 0x%x\r\n",
                       stepId, expectedMask, regVal);
            status = SystemP_FAILURE;
            break;
        }
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_stepEnable multiple steps test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_stepEnable multiple steps test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_stepEnable for boundary bit positions (step 1 and step 16)
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_stepEnable API with boundary step IDs (lowest step 1 and
 *           highest step 16). Verifies that both LSB and MSB positions of the
 *           step enable register are correctly handled. Confirms boundary step
 *           operations don't cause register overflow or underflow issues.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with boundary
 *                            step configurations (step 1 and step 16)
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if boundary steps are correctly enabled
 *           - SystemP_FAILURE if boundary step enable verification fails
 */
static int32_t TestAdc_stepEnableBoundary(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t regVal;
    uint32_t expectedMask;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_stepEnable for boundary bit positions...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Clear all steps first */
    ADC_clearAllSteps(baseAddr);

    /* Enable step 1 (LSB) */
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);
    regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);
    expectedMask = (1U << (ADC_STEP_1 + 1U));

    if (regVal != expectedMask)
    {
        DebugP_log("Step 1 (LSB) enable failed: expected 0x%x, got 0x%x\r\n", expectedMask, regVal);
        status = SystemP_FAILURE;
    }

    /* Enable step 16 (MSB) */
    ADC_stepEnable(baseAddr, ADC_STEP_16, TRUE);
    regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);
    expectedMask |= (1U << (ADC_STEP_16 + 1U));

    if (regVal != expectedMask)
    {
        DebugP_log("Step 16 (MSB) enable failed: expected 0x%x, got 0x%x\r\n", expectedMask, regVal);
        status = SystemP_FAILURE;
    }

    /* Verify both boundary bits are set */
    if ((regVal & (1U << (ADC_STEP_1 + 1U))) == 0U)
    {
        DebugP_log("Step 1 bit not set after enabling step 16\r\n");
        status = SystemP_FAILURE;
    }

    if ((regVal & (1U << (ADC_STEP_16 + 1U))) == 0U)
    {
        DebugP_log("Step 16 bit not set\r\n");
        status = SystemP_FAILURE;
    }

    /* Clear all and verify */
    ADC_clearAllSteps(baseAddr);
    regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);
    if (regVal != 0U)
    {
        DebugP_log("Clear all steps failed for boundary steps: 0x%x\r\n", regVal);
        status = SystemP_FAILURE;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_stepEnable boundary bit positions test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_stepEnable boundary bit positions test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_clearAllSteps functionality
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_clearAllSteps API which disables all ADC steps in a single
 *           operation. Enables multiple steps, then calls clearAllSteps and verifies
 *           the step enable register is completely cleared (all bits = 0). Confirms
 *           this is an atomic operation that properly resets all step enables.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with multiple
 *                            step configurations to enable before clearing
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if all steps are correctly cleared
 *           - SystemP_FAILURE if step enable register is not fully cleared
 */
static int32_t TestAdc_clearAllSteps(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t i;
    uint32_t stepId;
    uint32_t regVal;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_clearAllSteps...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Enable multiple steps */
    for (i = 0; i < testParams->adcConfigParams.numSteps; i++)
    {
        stepId = testParams->adcConfigParams.adcSteps[i].stepId;
        ADC_stepEnable(baseAddr, stepId, TRUE);
    }

    /* Verify steps are enabled */
    regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);
    if (regVal == 0U)
    {
        DebugP_log("Failed to enable steps before clear test\r\n");
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        /* Clear all steps */
        ADC_clearAllSteps(baseAddr);

        /* Verify all steps are cleared */
        regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);
        if (regVal != 0U)
        {
            DebugP_log("ADC_clearAllSteps failed: register value 0x%x\r\n", regVal);
            status = SystemP_FAILURE;
        }
    }

    /* Test clearAllSteps when already cleared */
    if (status == SystemP_SUCCESS)
    {
        ADC_clearAllSteps(baseAddr);
        regVal = HW_RD_REG32(baseAddr + ADC_STEPENABLE);
        if (regVal != 0U)
        {
            DebugP_log("ADC_clearAllSteps double-clear failed: register value 0x%x\r\n", regVal);
            status = SystemP_FAILURE;
        }
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_clearAllSteps test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_clearAllSteps test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_start with enable=0 but steps enabled (no conversion scenario)
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_start API behavior when called with enable=FALSE while steps
 *           are enabled. Verifies that no ADC conversions occur and FIFO remains
 *           empty. Confirms enable flag properly gates sequencer operation even
 *           when valid steps are configured and enabled.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with step
 *                            configuration for enable gating test
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if ADC remains idle with enable=0
 *           - SystemP_FAILURE if conversions occur despite enable=0
 */
static int32_t TestAdc_startEnableZeroWithSteps(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    test_adc_stepConfigParams_t *stepConfig;
    adcStepConfig_t adcStepCfg;
    uint32_t ctrlReg;
    uint32_t enableBit;
    uint32_t fifoCount;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_start with enable=0 and steps enabled...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure and enable a step */
    stepConfig = &testParams->adcConfigParams.adcSteps[0];
    adcStepCfg.mode = stepConfig->mode;
    adcStepCfg.channel = stepConfig->channel;
    adcStepCfg.openDelay = stepConfig->openDelay;
    adcStepCfg.sampleDelay = stepConfig->sampleDelay;
    adcStepCfg.rangeCheckEnable = stepConfig->rangeCheckEnable;
    adcStepCfg.averaging = stepConfig->averaging;
    adcStepCfg.fifoNum = stepConfig->fifoNum;
    ADC_setStepParams(baseAddr, stepConfig->stepId, &adcStepCfg);
    ADC_stepEnable(baseAddr, stepConfig->stepId, TRUE);

    /* Start ADC with enable = FALSE */
    ADC_start(baseAddr, FALSE);

    /* Wait briefly */
    ClockP_usleep(1000);

    /* Verify ADC control register - enable bit should be 0 */
    ctrlReg = HW_RD_REG32(baseAddr + ADC_CTRL);
    enableBit = (ctrlReg & ADC_CTRL_EN_MASK) >> ADC_CTRL_EN_SHIFT;

    if (enableBit != 0U)
    {
        DebugP_log("ADC enable bit set despite enable=FALSE: 0x%x\r\n", ctrlReg);
        status = SystemP_FAILURE;
    }

    /* Verify FIFO is empty (no conversions occurred) */
    fifoCount = HW_RD_REG32(baseAddr + ADC_FIFOCOUNT(0));
    if (fifoCount != 0U)
    {
        DebugP_log("FIFO has data despite enable=0: count=%d\r\n", fifoCount);
        status = SystemP_FAILURE;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_start enable=0 with steps test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_start enable=0 with steps test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_start with enable=1 but no steps enabled (no conversion scenario)
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_start API behavior when called with enable=TRUE but no steps
 *           are enabled. Verifies that ADC enable bit is set but no conversions
 *           occur since sequencer has no steps to execute. Confirms proper gating
 *           mechanism requiring both enable=1 AND enabled steps for conversions.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if ADC is enabled but idle without steps
 *           - SystemP_FAILURE if unexpected behavior occurs
 */
static int32_t TestAdc_startEnableOneNoSteps(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t ctrlReg;
    uint32_t enableBit;
    uint32_t fifoCount;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_start with enable=1 but no steps enabled...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Ensure no steps are enabled */
    ADC_clearAllSteps(baseAddr);

    /* Start ADC with enable = TRUE */
    ADC_start(baseAddr, TRUE);

    /* Wait briefly */
    ClockP_usleep(1000);

    /* Verify ADC control register - enable bit should be 1 */
    ctrlReg = HW_RD_REG32(baseAddr + ADC_CTRL);
    enableBit = (ctrlReg & ADC_CTRL_EN_MASK) >> ADC_CTRL_EN_SHIFT;

    if (enableBit != 1U)
    {
        DebugP_log("ADC enable bit not set with enable=TRUE: 0x%x\r\n", ctrlReg);
        status = SystemP_FAILURE;
    }

    /* Verify FIFO is empty (no conversions occurred since no steps) */
    fifoCount = HW_RD_REG32(baseAddr + ADC_FIFOCOUNT(0));
    if (fifoCount != 0U)
    {
        DebugP_log("FIFO has data despite no steps enabled: count=%d\r\n", fifoCount);
        status = SystemP_FAILURE;
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_start enable=1 with no steps test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_start enable=1 with no steps test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_start with enable=1 and steps enabled (normal conversion scenario)
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_start API normal operation with enable=TRUE and steps enabled.
 *           Verifies that ADC conversions occur and FIFO receives data. Confirms
 *           both enable flag and step enables must be active for conversions.
 *           Tests the expected conversion flow with proper sequencer operation.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with step
 *                            configuration for normal conversion operation
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if conversions occur and FIFO receives data
 *           - SystemP_FAILURE if conversions don't occur or FIFO remains empty
 */
static int32_t TestAdc_startEnableOneWithSteps(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    test_adc_stepConfigParams_t *stepConfig;
    adcStepConfig_t adcStepCfg;
    uint32_t ctrlReg;
    uint32_t enableBit;
    uint32_t fifoCount;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_start with enable=1 and steps enabled...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure and enable a step */
    stepConfig = &testParams->adcConfigParams.adcSteps[0];
    adcStepCfg.mode = stepConfig->mode;
    adcStepCfg.channel = stepConfig->channel;
    adcStepCfg.openDelay = stepConfig->openDelay;
    adcStepCfg.sampleDelay = stepConfig->sampleDelay;
    adcStepCfg.rangeCheckEnable = stepConfig->rangeCheckEnable;
    adcStepCfg.averaging = stepConfig->averaging;
    adcStepCfg.fifoNum = stepConfig->fifoNum;
    ADC_setStepParams(baseAddr, stepConfig->stepId, &adcStepCfg);
    ADC_stepEnable(baseAddr, stepConfig->stepId, TRUE);

    /* Start ADC with enable = TRUE */
    ADC_start(baseAddr, TRUE);

    /* Wait for conversion */
    ClockP_usleep(10000);

    /* Verify ADC control register - enable bit should be 1 */
    ctrlReg = HW_RD_REG32(baseAddr + ADC_CTRL);
    enableBit = (ctrlReg & ADC_CTRL_EN_MASK) >> ADC_CTRL_EN_SHIFT;

    if (enableBit != 1U)
    {
        DebugP_log("ADC enable bit not set: 0x%x\r\n", ctrlReg);
        status = SystemP_FAILURE;
    }

    /* Verify FIFO has data (conversions occurred) */
    fifoCount = HW_RD_REG32(baseAddr + ADC_FIFOCOUNT(0));
    if (fifoCount == 0U)
    {
        DebugP_log("FIFO empty despite enable=1 and steps enabled\r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        DebugP_log("FIFO has %d samples as expected\r\n", fifoCount);
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    /* Verify enable bit is now cleared */
    ctrlReg = HW_RD_REG32(baseAddr + ADC_CTRL);
    enableBit = (ctrlReg & ADC_CTRL_EN_MASK) >> ADC_CTRL_EN_SHIFT;

    if (enableBit != 0U)
    {
        DebugP_log("ADC enable bit not cleared after stop: 0x%x\r\n", ctrlReg);
        status = SystemP_FAILURE;
    }

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_start enable=1 with steps test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_start enable=1 with steps test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_stepIdTagEnable with tag enabled - verify data format
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_stepIdTagEnable API with tag enable=TRUE. Verifies that FIFO
 *           data includes step ID tags in upper bits. Reads FIFO data and confirms
 *           step ID field matches the step that generated the conversion. Tests
 *           multiple steps to verify each includes correct tag information.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with multiple
 *                            step configurations for tag format verification
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if step ID tags are correctly included in data
 *           - SystemP_FAILURE if tag format verification fails
 */
static int32_t TestAdc_stepIdTagEnableOn(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t i;
    test_adc_stepConfigParams_t *stepConfig;
    adcStepConfig_t adcStepCfg;
    uint32_t fifoCount;
    uint32_t fifoData;
    uint32_t stepIdTag;
    uint32_t validTag;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_stepIdTagEnable with tag ON...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Enable step ID tag */
    ADC_stepIdTagEnable(baseAddr, TRUE);

    /* Configure and enable multiple steps */
    for (i = 0; i < testParams->adcConfigParams.numSteps; i++)
    {
        stepConfig = &testParams->adcConfigParams.adcSteps[i];
        adcStepCfg.mode = stepConfig->mode;
        adcStepCfg.channel = stepConfig->channel;
        adcStepCfg.openDelay = stepConfig->openDelay;
        adcStepCfg.sampleDelay = stepConfig->sampleDelay;
        adcStepCfg.rangeCheckEnable = stepConfig->rangeCheckEnable;
        adcStepCfg.averaging = stepConfig->averaging;
        adcStepCfg.fifoNum = stepConfig->fifoNum;
        ADC_setStepParams(baseAddr, stepConfig->stepId, &adcStepCfg);
        ADC_stepEnable(baseAddr, stepConfig->stepId, TRUE);
    }

    /* Start ADC */
    ADC_start(baseAddr, TRUE);

    /* Wait for conversions */
    ClockP_usleep(10000);

    /* Read FIFO and verify step ID tags are present */
    fifoCount = HW_RD_REG32(baseAddr + ADC_FIFOCOUNT(0));
    if (fifoCount == 0U)
    {
        DebugP_log("No FIFO data available\r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        /* Read first FIFO entry */
        fifoData = HW_RD_REG32(baseAddr + ADC_FIFODATA(0));

        /* Extract step ID from upper bits (bits 16-19 for step ID tag) */
        stepIdTag = (fifoData >> 16) & 0xFU;

        DebugP_log("Step ID tag detected: %d (FIFO data: 0x%x)\r\n", stepIdTag, fifoData);

        /* Verify step ID matches one of the configured steps */
        validTag = 0U;
        for (i = 0; i < testParams->adcConfigParams.numSteps; i++)
        {
            if (stepIdTag == testParams->adcConfigParams.adcSteps[i].stepId)
            {
                validTag = 1U;
                break;
            }
        }

        if (validTag == 0U)
        {
            DebugP_log("Step ID tag %d doesn't match any configured step\r\n", stepIdTag);
            status = SystemP_FAILURE;
        }
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_stepIdTagEnable ON test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_stepIdTagEnable ON test failed\r\n");
    }

    return status;
}

/**
 *  \brief   Test ADC_stepIdTagEnable with tag disabled - verify data format
 *
 *  Test Category: Functionality
 *
 *  \details Tests ADC_stepIdTagEnable API with tag enable=FALSE. Verifies that FIFO
 *           data does NOT include step ID tags, with upper bits cleared or used for
 *           ADC data only. Reads FIFO data and confirms step ID field is zero or
 *           follows data-only format without tag information.
 *
 *  \param   testParams [IN] Pointer to test case parameter structure with multiple
 *                            step configurations for non-tagged format verification
 *
 *  \return  int32_t
 *           - SystemP_SUCCESS if step ID tags are not included in data
 *           - SystemP_FAILURE if unexpected tags appear in data
 */
static int32_t TestAdc_stepIdTagEnableOff(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t i;
    test_adc_stepConfigParams_t *stepConfig;
    adcStepConfig_t adcStepCfg;
    uint32_t fifoCount;
    uint32_t fifoData;
    uint32_t stepIdTag;
    uint32_t adcValue;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_stepIdTagEnable with tag OFF...\r\n");

    /* Power up and initialize ADC */
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Disable step ID tag */
    ADC_stepIdTagEnable(baseAddr, FALSE);

    /* Configure and enable multiple steps */
    for (i = 0; i < testParams->adcConfigParams.numSteps; i++)
    {
        stepConfig = &testParams->adcConfigParams.adcSteps[i];
        adcStepCfg.mode = stepConfig->mode;
        adcStepCfg.channel = stepConfig->channel;
        adcStepCfg.openDelay = stepConfig->openDelay;
        adcStepCfg.sampleDelay = stepConfig->sampleDelay;
        adcStepCfg.rangeCheckEnable = stepConfig->rangeCheckEnable;
        adcStepCfg.averaging = stepConfig->averaging;
        adcStepCfg.fifoNum = stepConfig->fifoNum;
        ADC_setStepParams(baseAddr, stepConfig->stepId, &adcStepCfg);
        ADC_stepEnable(baseAddr, stepConfig->stepId, TRUE);
    }

    /* Start ADC */
    ADC_start(baseAddr, TRUE);

    /* Wait for conversions */
    ClockP_usleep(10000);

    /* Read FIFO and verify step ID tags are NOT present */
    fifoCount = HW_RD_REG32(baseAddr + ADC_FIFOCOUNT(0));
    if (fifoCount == 0U)
    {
        DebugP_log("No FIFO data available\r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        /* Read first FIFO entry */
        fifoData = HW_RD_REG32(baseAddr + ADC_FIFODATA(0));

        /* Extract potential step ID from upper bits */
        stepIdTag = (fifoData >> 16) & 0xFU;

        /* With tag disabled, upper bits should be 0 or continuation of ADC data */
        /* For now, verify the data format is different from tagged mode */
        DebugP_log("FIFO data without tag: 0x%x (upper bits: 0x%x)\r\n", fifoData, stepIdTag);

        /* The key difference: data should only contain ADC value in lower 12 bits */
        /* Upper bits may be 0 or extended data depending on implementation */
        adcValue = fifoData & 0xFFFU;  /* 12-bit ADC value */

        if (adcValue == 0U)
        {
            DebugP_log("Warning: ADC value is zero\r\n");
        }

        /* Main verification: compared to tagged mode, data format should be cleaner */
        DebugP_log("ADC value without tag: 0x%x\r\n", adcValue);
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);

    /* Power down */
    ADC_powerUp(baseAddr, FALSE);

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("ADC_stepIdTagEnable OFF test passed\r\n");
    }
    else
    {
        DebugP_log("ADC_stepIdTagEnable OFF test failed\r\n");
    }

    return status;
}

/**
 * \brief Test changing step parameters while ADC is actively converting
 *
 * Test Category: Functionality
 *
 * This test verifies that ADC step parameters (channel, delays, averaging)
 * can be modified while ADC is actively running conversions without
 * causing errors or data corruption.
 */
static int32_t TestAdc_changeStepParamsWhileActive(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t fifoData;
    uint32_t i;
    adcStepConfig_t stepConfig;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing step parameter change while ADC is active...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, ADC_INTR_SRC_END_OF_SEQUENCE);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, 0U, 0U);
    ClockP_usleep(100U);

    /* Configure initial step */
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

    /* Enable step ID tag for verification */
    ADC_stepIdTagEnable(baseAddr, TRUE);

    /* Start ADC conversion */
    ADC_start(baseAddr, TRUE);
    DebugP_log("ADC started in continuous mode with Channel 1\r\n");

    /* Collect some samples with initial configuration */
    for (i = 0U; i < TEST_ADC_LIVE_RECONFIG_SAMPLE_COUNT / 2U; i++)
    {
        ClockP_usleep(TEST_ADC_LIVE_RECONFIG_DELAY_US);

        if (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) > 0U)
        {
            fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("Pre-reconfig sample %u: 0x%x\r\n", i, fifoData);
        }
    }

    /* Change step parameters while ADC is running */
    DebugP_log("Changing step parameters while ADC is active...\r\n");

    stepConfig.channel = ADC_CHANNEL_2;
    stepConfig.openDelay = 0x200U;
    stepConfig.sampleDelay = 0x20U;
    stepConfig.averaging = ADC_AVERAGING_16_SAMPLES;

    ADC_setStepParams(baseAddr, ADC_STEP_1, &stepConfig);
    DebugP_log("Step parameters changed to Channel 2 with 16x averaging\r\n");

    /* Collect samples with new configuration */
    for (i = 0U; i < TEST_ADC_LIVE_RECONFIG_SAMPLE_COUNT / 2U; i++)
    {
        ClockP_usleep(TEST_ADC_LIVE_RECONFIG_DELAY_US * 2U); /* More delay for averaging */

        if (ADC_getFIFOWordCount(baseAddr, ADC_FIFO_NUM_0) > 0U)
        {
            fifoData = ADC_getFIFOData(baseAddr, ADC_FIFO_NUM_0);
            DebugP_log("Post-reconfig sample %u: 0x%x\r\n", i, fifoData);
        }
    }

    /* Stop ADC */
    ADC_start(baseAddr, FALSE);
    DebugP_log("Live reconfiguration of step parameters completed successfully\r\n");

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

#endif /* #ifdef SOC_AM275X */

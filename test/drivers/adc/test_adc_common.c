/*
 * Copyright (C) 2021-26 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
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
 * \file test_adc_common.c
 * \brief Common utility functions for ADC driver test cases.
 */

/*===================================================================*/
/*                       Include Files                               */
/*===================================================================*/

#include "test_adc.h"

/*===================================================================*/
/*                      Macro Defines                                */
/*===================================================================*/

/* Reference voltage for ADC - should be given in mV */
#define TEST_ADC_REFERENCE_VOLTAGE_MV    (1800U)

/*===================================================================*/
/*                      Typedefs                                     */
/*===================================================================*/

/* None */

/*===================================================================*/
/*                      Global Variables                            */
/*===================================================================*/

/* None */

/*===================================================================*/
/*                      Function Declarations                        */
/*===================================================================*/

static int32_t TestAdc_getChannelId(test_adc_testcaseParams_t *testParams,
                                    uint32_t stepId, uint32_t *channelId);

/*===================================================================*/
/*                      Function Definitions                         */
/*===================================================================*/

/**
 * \brief  Initializes the ADC module.
 *
 *  Test Category: Functionality
 *
 *   Clears all interrupt status flags, powers up the AFE, waits for
 *   the required startup time, verifies the ADC is powered up, and
 *   performs internal calibration.
 *
 *  \param adcModule ADC module base address
 *
 * \return None.
 */
void TestAdc_moduleInit(uint32_t adcModule)
{
    uint32_t isPoweredUp = 0U;

    /* Clear All interrupt status */
    ADC_clearIntrStatus(adcModule, ADC_INTR_STATUS_ALL);

    /* Power up AFE */
    ADC_powerUp(adcModule, TRUE);

    /* Wait for 4us at least */
    ClockP_usleep(10U);

    /* Check whether ADC is powered up or not */
    isPoweredUp = Adc_isPoweredUp(adcModule);
    DebugP_assert(1U == isPoweredUp);

    /* Do the internal calibration */
    ADC_init(adcModule, FALSE, 0U, 0U);

    return;
}

/**
 * \brief  Starts the ADC sequencer.
 *
 *  Test Category: Functionality
 *
 *   Waits for the ADC FSM to reach IDLE state, then starts ADC
 *   conversion.
 *
 *  \param adcModule ADC module base address
 *
 * \return None.
 */
void TestAdc_moduleStart(uint32_t adcModule)
{
    adcSequencerStatus_t adcSeqStatus;

    /* Check if FSM is idle */
    ADC_getSequencerStatus(adcModule, &adcSeqStatus);
    while((ADC_ADCSTAT_FSM_BUSY_IDLE != adcSeqStatus.fsmBusy) &&
           ADC_ADCSTAT_STEP_ID_IDLE != adcSeqStatus.stepId)
    {
        ADC_getSequencerStatus(adcModule, &adcSeqStatus);
    }

    /* Start ADC conversion */
    ADC_start(adcModule, TRUE);

    return;
}

/**
 * \brief  Stops the ADC sequencer.
 *
 *  Test Category: Functionality
 *
 *   Disables all configured steps, waits for the FSM to go IDLE,
 *   stops ADC conversion, and waits again for FSM to reach IDLE.
 *
 *  \param testParams Pointer to test case parameters
 *
 * \return None.
 */
void TestAdc_moduleStop(test_adc_testcaseParams_t *testParams)
{
    uint32_t                loopCnt;
    uint32_t                adcModule;
    adcSequencerStatus_t    adcSeqStatus;

    adcModule = testParams->adcConfigParams.adcModule;

    /* step disable */
    for(loopCnt = 0U; loopCnt < testParams->adcConfigParams.numSteps; loopCnt++)
    {
        ADC_stepEnable(adcModule,
                       testParams->adcConfigParams.adcSteps[loopCnt].stepId,
                       FALSE);
    }

    /* Wait for FSM to go IDLE */
    ADC_getSequencerStatus(adcModule, &adcSeqStatus);
    while((ADC_ADCSTAT_FSM_BUSY_IDLE != adcSeqStatus.fsmBusy) &&
           ADC_ADCSTAT_STEP_ID_IDLE != adcSeqStatus.stepId)
    {
        ADC_getSequencerStatus(adcModule, &adcSeqStatus);
    }

    /* Stop ADC */
    ADC_start(adcModule, FALSE);

    /* Wait for FSM to go IDLE */
    ADC_getSequencerStatus(adcModule, &adcSeqStatus);
    while((ADC_ADCSTAT_FSM_BUSY_IDLE != adcSeqStatus.fsmBusy) &&
           ADC_ADCSTAT_STEP_ID_IDLE != adcSeqStatus.stepId)
    {
        ADC_getSequencerStatus(adcModule, &adcSeqStatus);
    }

    return;
}

/**
 * \brief  Configures ADC step parameters and enables steps.
 *
 *  Test Category: Functionality
 *
 *   Iterates over the configured steps and sets each step's parameters
 *   including channel, delays, averaging, and FIFO settings. Enables
 *   step ID tagging if configured, then enables all steps.
 *
 *  \param testParams Pointer to test case parameters
 *
 * \return SystemP_SUCCESS on success, error code otherwise.
 */
int32_t TestAdc_stepConfig(test_adc_testcaseParams_t *testParams)
{
    int32_t         status = SystemP_SUCCESS;
    uint32_t        loopCnt;
    adcStepConfig_t adcConfig;
    uint32_t        adcModule;

    adcModule = testParams->adcConfigParams.adcModule;
    for(loopCnt = 0; loopCnt < testParams->adcConfigParams.numSteps; loopCnt++)
    {
        test_adc_stepConfigParams_t *adcStepConfig = &(testParams->adcConfigParams.adcSteps[loopCnt]);
        adcConfig.channel           = adcStepConfig->channel;
        adcConfig.openDelay         = adcStepConfig->openDelay;
        adcConfig.sampleDelay       = adcStepConfig->sampleDelay;
        adcConfig.rangeCheckEnable  = adcStepConfig->rangeCheckEnable;
        adcConfig.averaging         = adcStepConfig->averaging;
        adcConfig.fifoNum           = testParams->adcConfigParams.fifoNum;
        adcConfig.mode              = testParams->adcConfigParams.adcSteps[loopCnt].mode;
        status  += ADC_setStepParams(
            adcModule,
            testParams->adcConfigParams.adcSteps[loopCnt].stepId,
            &adcConfig);
    }
    DebugP_assert(SystemP_SUCCESS == status);

    if(TRUE == testParams->adcConfigParams.stepIdTagEnable)
    {
        ADC_stepIdTagEnable(adcModule, TRUE);
    }
    else
    {
        ADC_stepIdTagEnable(adcModule, FALSE);
    }

    /* step enable */
    for(loopCnt = 0U; loopCnt < testParams->adcConfigParams.numSteps; loopCnt++)
    {
        ADC_stepEnable(adcModule,
                       testParams->adcConfigParams.adcSteps[loopCnt].stepId,
                       TRUE);
    }

    return status;
}

/**
 * \brief  Validates FIFO data from ADC conversion.
 *
 *  Test Category: Functionality
 *
 *   Iterates through the FIFO data buffer, extracts step ID and ADC
 *   data fields, converts raw ADC data to millivolts, and logs the
 *   channel ID and observed voltage for each sample.
 *
 *  \param testParams   Pointer to test case parameters
 *  \param adcDataBuff  Pointer to ADC FIFO data buffer
 *  \param numSamples   Number of samples to validate
 *
 * \return SystemP_SUCCESS on success, error code otherwise.
 */
int32_t TestAdc_validateFifoData(test_adc_testcaseParams_t *testParams,
                                 uint32_t *adcDataBuff, uint32_t numSamples)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t stepId, channelId, loopCnt;
    uint32_t fifoData, voltLvl;

    for(loopCnt = 0U; loopCnt < numSamples; loopCnt++)
    {
        fifoData = *adcDataBuff;
        stepId   = ((fifoData & ADC_FIFODATA_ADCCHNLID_MASK) >>
                    ADC_FIFODATA_ADCCHNLID_SHIFT);
        fifoData = ((fifoData & ADC_FIFODATA_ADCDATA_MASK) >>
                    ADC_FIFODATA_ADCDATA_SHIFT);
        voltLvl = ((fifoData * TEST_ADC_REFERENCE_VOLTAGE_MV) /
                   ADC_GET_RANGE(CONFIG_ADC0_NUM_BITS));
        if(SystemP_SUCCESS == TestAdc_getChannelId(testParams, stepId, &channelId))
        {
            DebugP_log("Step ID : %d Channel Id: %d Observed voltage: %dmV.\r\n",
                    (stepId + 1U), channelId, voltLvl);
        }
        adcDataBuff++;
    }

    return status;
}

/**
 * \brief  Retrieves the channel ID corresponding to a given step ID.
 *
 *  Test Category: Functionality
 *
 *   Searches through the configured steps to find the channel ID
 *   associated with the provided step ID.
 *
 *  \param testParams  Pointer to test case parameters
 *  \param stepId      Step ID to look up
 *  \param channelId   Pointer to store the found channel ID
 *
 * \return SystemP_SUCCESS if step ID found, SystemP_FAILURE otherwise.
 */
static int32_t TestAdc_getChannelId(test_adc_testcaseParams_t *testParams,
                                    uint32_t stepId, uint32_t *channelId)
{
    int32_t  retVal = SystemP_FAILURE;
    uint32_t loopCnt;

    for(loopCnt = 0U; loopCnt < testParams->adcConfigParams.numSteps; loopCnt++)
    {
        if(stepId == testParams->adcConfigParams.adcSteps[loopCnt].stepId)
        {
            *channelId = testParams->adcConfigParams.adcSteps[loopCnt].channel;
            retVal = SystemP_SUCCESS;
            break;
        }
    }

    return retVal;
}

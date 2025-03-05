/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "test_adc.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Reference voltage for ADC - should be given in mV*/
#define APP_ADC_REFERENCE_VOLTAGE_MV    (1800U)
#define APP_ADC_RANGE_MAX               (1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t App_adcGetChannelId(test_adc_testcaseParams_t *testParams,
                                  uint32_t stepId, uint32_t *channelId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_adc_moduleInit(uint32_t adcModule)
{
    uint32_t        isPoweredUp = 0U;

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

void test_adc_moduleStart(uint32_t adcModule)
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

void test_adc_moduleStop(test_adc_testcaseParams_t *testParams)
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

int32_t test_adc_stepConfig(test_adc_testcaseParams_t *testParams)
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

int32_t test_adc_validateFifoData(test_adc_testcaseParams_t *testParams, uint32_t *adcDataBuff, uint32_t numSamples)
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
        voltLvl = ((fifoData * APP_ADC_REFERENCE_VOLTAGE_MV) /
                   APP_ADC_RANGE_MAX);
        if(SystemP_SUCCESS == App_adcGetChannelId(testParams, stepId, &channelId))
        {
            DebugP_log("Step ID : %d Channel Id: %d Observed voltage: %dmV.\r\n",
                    (stepId + 1U), channelId, voltLvl);
        }
        adcDataBuff++;
    }

    return status;
}

static int32_t App_adcGetChannelId(test_adc_testcaseParams_t *testParams, uint32_t stepId, uint32_t *channelId)
{
    int32_t retVal = SystemP_FAILURE;
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

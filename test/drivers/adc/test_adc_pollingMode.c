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
 * \file test_adc_pollingMode.c
 * \brief Test file for ADC driver polling mode operations.
 */

/*===================================================================*/
/*                          Include Files                            */
/*===================================================================*/

#include "test_adc.h"

/*===================================================================*/
/*                          Macro Defines                            */
/*===================================================================*/

#define TEST_ADC_MAX_SAMPLES             (300U)

/*===================================================================*/
/*                         Global Variables                          */
/*===================================================================*/

static uint32_t             TestAdc_adcModule;
static uint64_t             TestAdc_timeStampBeforeAdc, TestAdc_timeStampAfterAdc;
/* Application Buffers */
uint32_t TestAdc_adcCpuDestBuf[TEST_ADC_MAX_SAMPLES];

/*===================================================================*/
/*                      Function Declarations                        */
/*===================================================================*/

static uint32_t TestAdc_extractFifoData(uint32_t fifoNum, uint32_t *dstBuff);

/*===================================================================*/
/*                      Function Definitions                        */
/*===================================================================*/

/**
 * \brief  Main entry point for ADC polling mode test.
 *
 *  Test Category: Functionality
 *
 *   Reads revision ID, initializes ADC module, configures FIFO threshold,
 *   starts conversion, polls the sequencer FSM until idle, reads and
 *   validates FIFO data, then stops and powers down the ADC.
 *
 *  \param testParams Pointer to test case parameters
 *
 * \return 0 on completion.
 */
int32_t TestAdc_pollingMode_main(test_adc_testcaseParams_t *testParams)
{
    int32_t              status;
    uint32_t             loopCnt, numElems;
    adcRevisionId_t      adcRevision;
    adcSequencerStatus_t adcStatus;

    /* Initialize ADC configuration params */
    TestAdc_adcModule = testParams->adcConfigParams.adcModule;

    /* Get and print revision ID */
    ADC_getRevisionId(TestAdc_adcModule, &adcRevision);
    DebugP_log("ADC Scheme : %d \r\n", adcRevision.scheme);
    DebugP_log("ADC Functional Release number : %d \r\n", adcRevision.func);
    DebugP_log("ADC Design Release number : %d \r\n", adcRevision.rtlRev);
    DebugP_log("ADC Major Revision number : %d \r\n", adcRevision.major);
    DebugP_log("ADC Custom Version number : %d \r\n", adcRevision.custom);
    DebugP_log("ADC Minor Version number : %d \r\n", adcRevision.minor);

    for(loopCnt = 0U; loopCnt < TEST_ADC_MAX_SAMPLES; loopCnt++)
    {
        TestAdc_adcCpuDestBuf[loopCnt] = 0U;
    }

    /* Initialize ADC module. */
    TestAdc_moduleInit(TestAdc_adcModule);

    /* Configure ADC step */
    status = TestAdc_stepConfig(testParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Enable ADC FIFO */
    if(testParams->adcConfigParams.fifoEnable == TRUE)
    {
        status = ADC_setCPUFIFOThresholdLevel(TestAdc_adcModule,
                    testParams->adcConfigParams.fifoNum,
                    testParams->adcConfigParams.fifoThreshold);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    TestAdc_timeStampBeforeAdc = ClockP_getTimeUsec();
    ADC_setRange(TestAdc_adcModule,
                testParams->adcConfigParams.highRange,
                testParams->adcConfigParams.lowRange);

    /* Start ADC conversion */
    TestAdc_moduleStart(TestAdc_adcModule);

    /* Poll for adc completion */
    ADC_getSequencerStatus(TestAdc_adcModule, &adcStatus);
    while(adcStatus.fsmBusy == 1)
    {
        ADC_getSequencerStatus(TestAdc_adcModule, &adcStatus);
    }

    TestAdc_timeStampAfterAdc = ClockP_getTimeUsec();

    /*Get FIFO data and Validate */
    numElems = TestAdc_extractFifoData(testParams->adcConfigParams.fifoNum,
                                     &TestAdc_adcCpuDestBuf[0]);
    if(numElems != 0U)
    {
        status =  TestAdc_validateFifoData(testParams, &TestAdc_adcCpuDestBuf[0], numElems);
    }

    /* Clear any enabled steps */
    ADC_clearAllSteps(TestAdc_adcModule);

    /* Stop ADC */
    TestAdc_moduleStop(testParams);

    /* Power down the ADC */
    ADC_powerUp(TestAdc_adcModule, FALSE);

    DebugP_log("Time taken for conversion is %d us.\n\r",
        (uint32_t) (TestAdc_timeStampAfterAdc - TestAdc_timeStampBeforeAdc));

    testParams->testResult = status;

    return 0;
}

/**
 * \brief  Reads all available data from the specified ADC FIFO into a buffer.
 *
 *  Test Category: Functionality
 *
 *   Queries the FIFO word count and reads each entry into the destination
 *   buffer sequentially.
 *
 *  \param fifoNum  FIFO number to read from
 *  \param dstBuff  Pointer to destination buffer
 *
 * \return Number of elements read.
 */
static uint32_t TestAdc_extractFifoData(uint32_t fifoNum, uint32_t *dstBuff)
{
    uint32_t loopCnt, numElems;
    numElems = ADC_getFIFOWordCount(TestAdc_adcModule, fifoNum);

    for(loopCnt = 0U; loopCnt < numElems; loopCnt++)
    {
        *dstBuff = ADC_getFIFOData(TestAdc_adcModule, fifoNum);
        dstBuff++;
    }
    return numElems;
}

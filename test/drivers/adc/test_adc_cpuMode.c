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
 * \file test_adc_cpuMode.c
 * \brief Test file for ADC driver CPU mode (interrupt-driven) operations.
 */

/*===================================================================*/
/*                          Include Files                            */
/*===================================================================*/

#include "test_adc.h"

/*===================================================================*/
/*                      Macro Defines                                */
/*===================================================================*/

#define TEST_ADC_MAX_SAMPLES             (300U)
#define TEST_ADC_DIV                     (8U)
#define TEST_ADC_VOLTAGE_ERR_OFFSET_MV       (100U)

/*===================================================================*/
/*                      Global Variables                            */
/*===================================================================*/

static uint32_t             TestAdc_adcModule;
static uint64_t             TestAdc_timeStampBeforeAdc, TestAdc_timeStampAfterAdc;
static uint32_t             TestAdc_outOfRange;
static HwiP_Object          TestAdc_hwiHandleDone;
static SemaphoreP_Object    TestAdc_adcSyncSemObject;

/* Application Buffers */
uint32_t TestAdc_adcCpuDestBuf[TEST_ADC_MAX_SAMPLES];

/*===================================================================*/
/*                      Function Declarations                        */
/*===================================================================*/

static void TestAdc_intrISR(void *handle);
static uint32_t TestAdc_extractFifoData(uint32_t fifoNum, uint32_t *dstBuff);

/**
 * \brief  Main entry point for ADC CPU (interrupt-driven) mode test.
 *
 *  Test Category: Functionality
 *
 *   Registers HWI, configures ADC steps, enables FIFO and interrupts,
 *   starts conversion, waits for completion, validates FIFO data,
 *   then cleans up all hardware and OS resources.
 *
 *  \param testParams Pointer to test case parameters
 *
 * \return 0 on completion.
 */
int32_t TestAdc_cpuMode_main(test_adc_testcaseParams_t *testParams)
{
    int32_t         status;
    uint32_t        loopCnt, numElems, numIter;
    HwiP_Params     hwiPrms;

    /* Construct Semaphore */
    status = SemaphoreP_constructCounting(&TestAdc_adcSyncSemObject, 0, 1);

    /* Number of iterations on configured steps */
    numIter = testParams->adcConfigParams.numIterations;
    TestAdc_outOfRange = 0U;

    /* Initialize buffer */
    for(loopCnt = 0U; loopCnt < TEST_ADC_MAX_SAMPLES; loopCnt++)
    {
        TestAdc_adcCpuDestBuf[loopCnt] = 0U;
    }

    /* Initialize ADC module. */
    TestAdc_adcModule = testParams->adcConfigParams.adcModule;
    TestAdc_moduleInit(TestAdc_adcModule);

    /* Register ADC interrupts */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum = CONFIG_ADC0_INTR;
    hwiPrms.callback = &TestAdc_intrISR;
    hwiPrms.priority = 1U;
    status = HwiP_construct(&TestAdc_hwiHandleDone, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

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

    /* Clear All interrupts */
    ADC_clearIntrStatus(TestAdc_adcModule, ADC_INTR_ALL);
    /* Enable interrupts */
    ADC_enableIntr(TestAdc_adcModule, testParams->adcConfigParams.intrEnable);

    /* Start ADC conversion */
    TestAdc_moduleStart(TestAdc_adcModule);

    /* wait for adc completion */
    while(numIter > 0)
    {
        SemaphoreP_pend(&TestAdc_adcSyncSemObject, SystemP_WAIT_FOREVER);
        numIter--;
    }

    /*Get FIFO data and Validate */
    numElems = TestAdc_extractFifoData(testParams->adcConfigParams.fifoNum, &TestAdc_adcCpuDestBuf[0]);
    if(numElems != 0U)
    {
        status =  TestAdc_validateFifoData(testParams, &TestAdc_adcCpuDestBuf[0], numElems);
    }

    /* Disable ADC interrupts */
    ADC_disableIntr(TestAdc_adcModule, testParams->adcConfigParams.intrEnable);

    /* Clear any enabled steps */
    ADC_clearAllSteps(TestAdc_adcModule);

    /* Stop ADC */
    TestAdc_moduleStop(testParams);

    /* Power down the ADC */
    ADC_powerUp(TestAdc_adcModule, FALSE);

    /* Disable Hwi and Semaphore */
    HwiP_destruct(&TestAdc_hwiHandleDone);
    SemaphoreP_destruct(&TestAdc_adcSyncSemObject);

    if(TestAdc_outOfRange == 1U)
    {
        DebugP_log("The converted values were out of range of the specified range.\n\r");
    }

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

/**
 * \brief  ADC interrupt service routine for CPU mode test.
 *
 *  Test Category: Functionality
 *
 *   Captures the post-conversion timestamp, checks for out-of-range
 *   interrupt status, clears interrupt flags, writes EOI, and signals
 *   the test semaphore.
 *
 *  \param handle  HWI handle (unused)
 *
 * \return None.
 */
static void TestAdc_intrISR(void *handle)
{
    uint32_t status;

    TestAdc_timeStampAfterAdc = ClockP_getTimeUsec();
    status = ADC_getIntrStatus(TestAdc_adcModule);
    if((status & ADC_INTR_SRC_OUT_OF_RANGE) > 0)
    {
        TestAdc_outOfRange = 1U;
    }
    ADC_clearIntrStatus(TestAdc_adcModule, ADC_getIntrRawStatus(TestAdc_adcModule));
    ADC_writeEOI(TestAdc_adcModule);
    SemaphoreP_post(&TestAdc_adcSyncSemObject);
}

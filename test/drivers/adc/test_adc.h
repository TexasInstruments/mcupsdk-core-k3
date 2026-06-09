/*
 * Copyright (C) 2021-25 Texas Instruments Incorporated
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

#ifndef TEST_ADC_H_
#define TEST_ADC_H_

/*===================================================================*/
/* Include Files                                                      */
/*===================================================================*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/CacheP.h>
#include <drivers/adc.h>
#include "ti_drivers_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*===================================================================*/
/* Macro Defines                                                      */
/*===================================================================*/

#define ADC_TEST_MODE_CPU               (0U)
#define ADC_TEST_MODE_POLLING           (2U)
#ifdef SOC_AM275X
#define ADC_TEST_MODE_API               (3U)
#ifdef ADC_TEST_FREERTOS
#define ADC_TEST_MODE_MULTITHREAD       (4U)
#endif
#endif

/*===================================================================*/
/* Typedefs                                               */
/*===================================================================*/

typedef struct
{
    uint32_t    stepId;
    uint32_t    channel;
    uint32_t    fifoNum;
    uint32_t    averaging;
    uint32_t    mode;
    uint32_t    rangeCheckEnable;
    uint32_t    openDelay;
    uint32_t    sampleDelay;
} test_adc_stepConfigParams_t;

/**
 * ADC configuration parameter structure.
 */
typedef struct
{
    /* ADC Module instance */
    uint32_t    adcModule;
    /* ADC Operational mode */
    uint32_t    adcMode;
    /* Interrupts to enable */
    uint32_t    intrEnable;
    /* Number of steps */
    uint32_t    numSteps;
    /* Number of iterations */
    uint32_t    numIterations;
    /* Steps to configure */
    test_adc_stepConfigParams_t adcSteps[16];
    /* CPU mode or DMA mode */
    uint32_t    testMode;
    /* Enable FIFO or not */
    uint32_t    fifoEnable;
    /* Fifo Threshold */
    uint32_t    fifoNum;
    /**< FIFO to be used to store the data.
     *  Refer enum #adcFIFONum_t.
     */
    uint32_t    fifoThreshold;
    /* Upper limit for conversion */
    uint32_t    highRange;
    /* Lower limit for conversion. */
    uint32_t    lowRange;
    /* Enable disable step tagging */
    uint32_t    stepIdTagEnable;
    /* Allowed error offset*/
    uint32_t    errOffset;
} test_adc_configParams_t;

/**
 *  Test case parameter structure.
 */
typedef struct
{
    /* Test case ID */
    uint32_t                testcaseId;
    /* Test case name */
    char                    *testCaseName;
    /* ADC Configuration parameters */
    test_adc_configParams_t    adcConfigParams;
    /* ADC Mode */
    uint32_t                adcMode;
    /* Test Result */
    int32_t                   testResult;
} test_adc_testcaseParams_t;

/*===================================================================*/
/* Function Declarations                                              */
/*===================================================================*/

int32_t TestAdc_parser(void);
int32_t TestAdc_cpuMode_main(test_adc_testcaseParams_t *testParams);
int32_t TestAdc_pollingMode_main(test_adc_testcaseParams_t *testParams);
#ifdef SOC_AM275X
int32_t TestAdc_powerInit_main(test_adc_testcaseParams_t *testParams);
int32_t TestAdc_stepControl_main(test_adc_testcaseParams_t *testParams);
int32_t TestAdc_fifoDma_main(test_adc_testcaseParams_t *testParams);
int32_t TestAdc_intrEoi_main(test_adc_testcaseParams_t *testParams);
int32_t TestAdc_rangeStatus_main(test_adc_testcaseParams_t *testParams);
#endif
int32_t TestAdc_validateFifoData(test_adc_testcaseParams_t *testParams, uint32_t *adcDataBuff, uint32_t numSamples);
int32_t TestAdc_stepConfig(test_adc_testcaseParams_t *testParams);
void TestAdc_moduleInit(uint32_t adcModule);
void TestAdc_moduleStart(uint32_t adcModule);
void TestAdc_moduleStop(test_adc_testcaseParams_t *testParams);

#ifdef __cplusplus
}
#endif /*extern "C" */

#endif

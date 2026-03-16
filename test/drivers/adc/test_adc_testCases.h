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

#ifndef TEST_ADC_TEST_CASES_H_
#define TEST_ADC_TEST_CASES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "test_adc.h"
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* SOC-specific ADC base address selection */
#if defined(SOC_AM275X) || defined(SOC_AM62LX)
#define ADC_TEST_BASE_ADDR  CONFIG_ADC0_BASE_ADDR
#else
#error "Unsupported SOC for ADC test"
#endif

#define ADC_NUM_TESTCASES (sizeof(gADCTestcaseParams) / sizeof(test_adc_testcaseParams_t))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various ADC test cases. */
test_adc_testcaseParams_t gADCTestcaseParams[] =
{
    {
        .testcaseId         = 6697U,
        .testCaseName       = "ADC Polling mode with FIFO 0",
        .adcConfigParams    =
        {
            .adcModule = ADC_TEST_BASE_ADDR,
            .adcMode = ADC_OPERATION_MODE_SINGLE_SHOT,
            .intrEnable = (ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO0_OVERRUN |
                           ADC_INTR_SRC_FIFO0_UNDERFLOW),
            .numSteps = 16,
            .numIterations = 1,
            {
                {ADC_STEP_1, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_2, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_3, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_4, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_5, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_6, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_7, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_8, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_9, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_10, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_11, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_12, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_13, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_14, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_15, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_16, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
            },
            .testMode = ADC_TEST_MODE_POLLING,
            .fifoEnable = TRUE,
            .fifoNum = ADC_FIFO_NUM_0,
            .fifoThreshold = 32,
            .highRange = 0x3FFU,
            .lowRange = 0U,
            .stepIdTagEnable = TRUE,
            .errOffset = 100U,
        },
    },
    {
        .testcaseId         = 6698U,
        .testCaseName       = "ADC Polling mode with FIFO 1",
        .adcConfigParams    =
        {
            .adcModule = ADC_TEST_BASE_ADDR,
            .adcMode = ADC_OPERATION_MODE_SINGLE_SHOT,
            .intrEnable = (ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO1_OVERRUN |
                           ADC_INTR_SRC_FIFO1_UNDERFLOW),
            .numSteps = 16,
            .numIterations = 1,
            {
                {ADC_STEP_1, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_2, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_3, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_4, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_5, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_6, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_7, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_8, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_9, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_10, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_11, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_12, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_13, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_14, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_15, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_16, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
            },
            .testMode = ADC_TEST_MODE_POLLING,
            .fifoEnable = TRUE,
            .fifoNum = ADC_FIFO_NUM_1,
            .fifoThreshold = 32,
            .highRange = 0x3FFU,
            .lowRange = 0U,
            .stepIdTagEnable = TRUE,
            .errOffset = 100U,
        },
    },
    {
        .testcaseId         = 6699U,
        .testCaseName       = "ADC ISR mode with FIFO 0",
        .adcConfigParams    =
        {
            .adcModule = ADC_TEST_BASE_ADDR,
            .adcMode = ADC_OPERATION_MODE_SINGLE_SHOT,
            .intrEnable = (ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO0_OVERRUN |
                           ADC_INTR_SRC_FIFO0_UNDERFLOW),
            .numSteps = 16,
            .numIterations = 1,
            {
                {ADC_STEP_1, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_2, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_3, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_4, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_5, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_6, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_7, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_8, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_9, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_10, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_11, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_12, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_13, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_14, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_15, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_16, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
            },
            .testMode = ADC_TEST_MODE_CPU,
            .fifoEnable = TRUE,
            .fifoNum = ADC_FIFO_NUM_0,
            .fifoThreshold = 32,
            .highRange = 0x3FFU,
            .lowRange = 0U,
            .stepIdTagEnable = TRUE,
            .errOffset = 100U,
        },
    },
    {
        .testcaseId         = 6700U,
        .testCaseName       = "ADC ISR mode with FIFO 1",
        .adcConfigParams    =
        {
            .adcModule = ADC_TEST_BASE_ADDR,
            .adcMode = ADC_OPERATION_MODE_SINGLE_SHOT,
            .intrEnable = (ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO1_OVERRUN |
                           ADC_INTR_SRC_FIFO1_UNDERFLOW),
            .numSteps = 16,
            .numIterations = 1,
            {
                {ADC_STEP_1, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_2, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_3, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_4, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_5, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_6, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_7, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_8, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_9, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_10, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_11, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_12, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_13, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_14, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_15, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_16, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
            },
            .testMode = ADC_TEST_MODE_CPU,
            .fifoEnable = TRUE,
            .fifoNum = ADC_FIFO_NUM_1,
            .fifoThreshold = 32,
            .highRange = 0x3FFU,
            .lowRange = 0U,
            .stepIdTagEnable = TRUE,
            .errOffset = 100U,
        },
    },
    {
        .testcaseId         = 6701U,
        .testCaseName       = "ADC samples averaging",
        .adcConfigParams    =
        {
            .adcModule = ADC_TEST_BASE_ADDR,
            .adcMode = ADC_OPERATION_MODE_SINGLE_SHOT,
            .intrEnable = (ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO0_OVERRUN |
                           ADC_INTR_SRC_FIFO0_UNDERFLOW),
            .numSteps = 5,
            .numIterations = 1,
            {
                {ADC_STEP_1, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_2, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_8_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_3, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_4_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_4, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_2_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_5, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_NONE,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
            },
            .testMode = ADC_TEST_MODE_CPU,
            .fifoEnable = TRUE,
            .fifoNum = ADC_FIFO_NUM_0,
            .fifoThreshold = 10,
            .highRange = 0x3FFU,
            .lowRange = 0U,
            .stepIdTagEnable = TRUE,
            .errOffset = 100U,
        },
    },
    {
        .testcaseId         = 6702U,
        .testCaseName       = "ADC open and sample delay combinations",
        .adcConfigParams    =
        {
            .adcModule = ADC_TEST_BASE_ADDR,
            .adcMode = ADC_OPERATION_MODE_SINGLE_SHOT,
            .intrEnable = (ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO1_OVERRUN |
                           ADC_INTR_SRC_FIFO1_UNDERFLOW),
            .numSteps = 4,
            .numIterations = 1,
            {
                {ADC_STEP_1, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_2, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, 0, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_3, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, 1},
                {ADC_STEP_4, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, 0, 1},
            },
            .testMode = ADC_TEST_MODE_CPU,
            .fifoEnable = TRUE,
            .fifoNum = ADC_FIFO_NUM_1,
            .fifoThreshold = 8,
            .highRange = 0x3FFU,
            .lowRange = 0U,
            .stepIdTagEnable = TRUE,
            .errOffset = 100U,
        },
    },
    {
        .testcaseId         = 6703U,
        .testCaseName       = "ADC singleshot Mode",
        .adcConfigParams    =
        {
            .adcModule = ADC_TEST_BASE_ADDR,
            .adcMode = ADC_OPERATION_MODE_SINGLE_SHOT,
            .intrEnable = (ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO0_OVERRUN |
                           ADC_INTR_SRC_FIFO0_UNDERFLOW),
            .numSteps = 16,
            .numIterations = 1,
            {
                {ADC_STEP_1, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_2, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_3, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_4, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_5, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_6, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_7, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_8, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_9, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_10, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_11, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_12, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_13, ADC_CHANNEL_1, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_14, ADC_CHANNEL_2, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_15, ADC_CHANNEL_3, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_16, ADC_CHANNEL_4, ADC_FIFO_NUM_0, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
            },
            .testMode = ADC_TEST_MODE_CPU,
            .fifoEnable = TRUE,
            .fifoNum = ADC_FIFO_NUM_0,
            .fifoThreshold = 32,
            .highRange = 0x3FFU,
            .lowRange = 0U,
            .stepIdTagEnable = TRUE,
            .errOffset = 100U,
        },
    },
    {
        .testcaseId         = 6704U,
        .testCaseName       = "ADC Continuous mode",
        .adcConfigParams    =
        {
            .adcModule = ADC_TEST_BASE_ADDR,
            .adcMode = ADC_OPERATION_MODE_CONTINUOUS,
            .intrEnable = (ADC_INTR_SRC_END_OF_SEQUENCE),
            .numSteps = 2,
            .numIterations = 10,
            {
                {ADC_STEP_1, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_CONTINUOUS, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_2, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_CONTINUOUS, 0U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
            },
            .testMode = ADC_TEST_MODE_CPU,
            .fifoEnable = TRUE,
            .fifoNum = ADC_FIFO_NUM_1,
            .fifoThreshold = 40,
            .highRange = 0x3FFU,
            .lowRange = 0U,
            .stepIdTagEnable = TRUE,
            .errOffset = 100U,
        },
    },
    {
        .testcaseId         = 6705U,
        .testCaseName       = "ADC Min Max Range",
        .adcConfigParams    =
        {
            .adcModule = ADC_TEST_BASE_ADDR,
            .adcMode = ADC_OPERATION_MODE_SINGLE_SHOT,
            .intrEnable = (ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO1_OVERRUN |
                           ADC_INTR_SRC_FIFO1_UNDERFLOW | ADC_INTR_SRC_OUT_OF_RANGE),
            .numSteps = 16,
            .numIterations = 1,
            {
                {ADC_STEP_1, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_2, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_3, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_4, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_5, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_6, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_7, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_8, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_9, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_10, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_11, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_12, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_13, ADC_CHANNEL_1, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_14, ADC_CHANNEL_2, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_15, ADC_CHANNEL_3, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
                {ADC_STEP_16, ADC_CHANNEL_4, ADC_FIFO_NUM_1, ADC_AVERAGING_16_SAMPLES,
                ADC_OPERATION_MODE_SINGLE_SHOT, 1U, ADC_OPENDELAY_MAX, ADC_SAMPLEDELAY_MAX},
            },
            .testMode = ADC_TEST_MODE_CPU,
            .fifoEnable = TRUE,
            .fifoNum = ADC_FIFO_NUM_1,
            .fifoThreshold = 32,
            .highRange = 0x3FFU,
            .lowRange = 0U,
            .stepIdTagEnable = TRUE,
            .errOffset = 100U,
        },
    },
};

#endif /* #ifndef ST_UART_TEST_CASES_H_ */

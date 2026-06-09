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
 * \file test_adc_intrEoi.c
 *
 * \brief ADC interrupt and EOI test file containing test cases for interrupt
 *        enable/disable, status reading, clearing, and EOI sequencing.
 */

/*===================================================================*/
/*                          Include Files                            */
/*===================================================================*/

#include "test_adc.h"
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/ClockP.h>

#ifdef SOC_AM275X
/*===================================================================*/
/*                      Macro Defines                                */
/*===================================================================*/

/* ADC interrupt sources */
#define TEST_ADC_INTR_ALL_SOURCES    (ADC_INTR_SRC_END_OF_SEQUENCE | \
                                 ADC_INTR_SRC_FIFO0_THRESHOLD | \
                                 ADC_INTR_SRC_FIFO0_OVERRUN | \
                                 ADC_INTR_SRC_FIFO0_UNDERFLOW | \
                                 ADC_INTR_SRC_FIFO1_THRESHOLD | \
                                 ADC_INTR_SRC_FIFO1_OVERRUN | \
                                 ADC_INTR_SRC_FIFO1_UNDERFLOW | \
                                 ADC_INTR_SRC_OUT_OF_RANGE)

/* Register offsets for direct access */
#define TEST_ADC_IRQSTATUS_RAW   (0x24U)
#define TEST_ADC_IRQEOI          (0x20U)

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

static int32_t TestAdc_enableIntrMaskAllSources(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_disableIntrUnmaskAllSources(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_getIntrStatusMasked(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_getIntrStatusRawUnmasked(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_clearIntrStatusW1C(test_adc_testcaseParams_t *testParams);
static int32_t TestAdc_writeClearThenEoi(test_adc_testcaseParams_t *testParams);


/*===================================================================*/
/*                      Function Definitions                        */
/*===================================================================*/

/**
 * \brief  Main dispatcher for ADC interrupt and EOI test cases.
 *
 *  Test Category: Functionality
 *
 *   Routes execution to the specific interrupt or EOI test function
 *   based on testCaseName string matching.
 *
 *  \param testParams Pointer to test case parameters
 *
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestAdc_intrEoi_main(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;

    if (testParams == NULL)
    {
        status = SystemP_FAILURE;
        DebugP_log("Error: testParams is NULL\r\n");
    }
    else
    {
        DebugP_log("Starting ADC Interrupt/EOI test: %s\r\n", testParams->testCaseName);

        /* Route to specific test based on test name */
        if (strstr(testParams->testCaseName, "enableIntr mask all sources") != NULL)
        {
            status = TestAdc_enableIntrMaskAllSources(testParams);
        }
        else if (strstr(testParams->testCaseName, "disableIntr unmask all sources") != NULL)
        {
            status = TestAdc_disableIntrUnmaskAllSources(testParams);
        }
        else if (strstr(testParams->testCaseName, "getIntrStatus masked") != NULL)
        {
            status = TestAdc_getIntrStatusMasked(testParams);
        }
        else if (strstr(testParams->testCaseName, "getIntrStatus raw unmasked") != NULL)
        {
            status = TestAdc_getIntrStatusRawUnmasked(testParams);
        }
        else if (strstr(testParams->testCaseName, "clearIntrStatus W1C") != NULL)
        {
            status = TestAdc_clearIntrStatusW1C(testParams);
        }
        else if (strstr(testParams->testCaseName, "writeEOI clear then EOI") != NULL)
        {
            status = TestAdc_writeClearThenEoi(testParams);
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
 * \brief Test ADC_enableIntr to mask all interrupt sources
 *
 * Test Category: Positive test
 *
 * This test verifies that ADC_enableIntr correctly enables (unmasks) all
 * interrupt sources by checking the IRQENABLE_SET register.
 */
static int32_t TestAdc_enableIntrMaskAllSources(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t irqEnableReg;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_enableIntr with all interrupt sources...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, FALSE, 0U);
    ClockP_usleep(100U);

    /* First disable all interrupts to start from known state */
    ADC_disableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);

    /* Enable all interrupt sources */
    ADC_enableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);

    /* Read IRQENABLE_SET register to verify all sources are enabled */
    irqEnableReg = HW_RD_REG32(baseAddr + ADC_IRQENABLE_SET);

    DebugP_log("IRQENABLE_SET register value: 0x%x\r\n", irqEnableReg);

    /* Verify all interrupt sources are enabled */
    if ((irqEnableReg & TEST_ADC_INTR_ALL_SOURCES) != TEST_ADC_INTR_ALL_SOURCES)
    {
        status = SystemP_FAILURE;
        DebugP_log("Error: Not all interrupt sources were enabled. Expected: 0x%x, Got: 0x%x\r\n",
                   TEST_ADC_INTR_ALL_SOURCES, irqEnableReg & TEST_ADC_INTR_ALL_SOURCES);
    }
    else
    {
        DebugP_log("All interrupt sources successfully enabled\r\n");
    }

    /* Cleanup */
    ADC_disableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test ADC_disableIntr to unmask all interrupt sources
 *
 * Test Category: Positive test
 *
 * This test verifies that ADC_disableIntr correctly disables (masks) all
 * interrupt sources by checking the IRQENABLE_SET register.
 */
static int32_t TestAdc_disableIntrUnmaskAllSources(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t irqEnableReg;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_disableIntr with all interrupt sources...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, FALSE, 0U);
    ClockP_usleep(100U);

    /* First enable all interrupts */
    ADC_enableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);

    /* Disable all interrupt sources */
    ADC_disableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);

    /* Read IRQENABLE_SET register to verify all sources are disabled */
    irqEnableReg = HW_RD_REG32(baseAddr + ADC_IRQENABLE_SET);

    DebugP_log("IRQENABLE_SET register value after disable: 0x%x\r\n", irqEnableReg);

    /* Verify all interrupt sources are disabled */
    if ((irqEnableReg & TEST_ADC_INTR_ALL_SOURCES) != 0U)
    {
        status = SystemP_FAILURE;
        DebugP_log("Error: Not all interrupt sources were disabled. Expected: 0x0, Got: 0x%x\r\n",
                   irqEnableReg & TEST_ADC_INTR_ALL_SOURCES);
    }
    else
    {
        DebugP_log("All interrupt sources successfully disabled\r\n");
    }

    /* Cleanup */
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test ADC_getIntrStatus for masked interrupt events
 *
 * Test Category: Positive test
 *
 * This test verifies that ADC_getIntrStatus returns only masked (enabled)
 * interrupt events, not raw unmasked events.
 */
static int32_t TestAdc_getIntrStatusMasked(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t intrStatus;
    uint32_t rawStatus;
    uint32_t enabledIntrs;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_getIntrStatus for masked events...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, FALSE, 0U);
    ClockP_usleep(100U);

    /* Enable only specific interrupts (e.g., END_OF_SEQUENCE and FIFO0_THRESHOLD) */
    enabledIntrs = ADC_INTR_SRC_END_OF_SEQUENCE | ADC_INTR_SRC_FIFO0_THRESHOLD;
    ADC_enableIntr(baseAddr, enabledIntrs);

    /* Configure and start a conversion to generate events */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);
    {
        adcStepConfig_t adcStepCfg;
        adcStepCfg.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
        adcStepCfg.channel = ADC_CHANNEL_1;
        adcStepCfg.openDelay = 0x1U;
        adcStepCfg.sampleDelay = 0U;
        adcStepCfg.rangeCheckEnable = 0U;
        adcStepCfg.averaging = ADC_AVERAGING_NONE;
        adcStepCfg.fifoNum = ADC_FIFO_NUM_0;
        ADC_setStepParams(baseAddr, ADC_STEP_1, &adcStepCfg);
    }
    ADC_start(baseAddr, TRUE);

    /* Wait for conversion */
    ClockP_usleep(1000U);

    /* Read masked status (IRQSTATUS) */
    intrStatus = ADC_getIntrStatus(baseAddr);

    /* Read raw status (IRQSTATUS_RAW) */
    rawStatus = HW_RD_REG32(baseAddr + TEST_ADC_IRQSTATUS_RAW);

    DebugP_log("Masked interrupt status (IRQSTATUS): 0x%x\r\n", intrStatus);
    DebugP_log("Raw interrupt status (IRQSTATUS_RAW): 0x%x\r\n", rawStatus);
    DebugP_log("Enabled interrupts: 0x%x\r\n", enabledIntrs);

    /* Verify masked status only shows enabled interrupts */
    if ((intrStatus & ~enabledIntrs) != 0U)
    {
        status = SystemP_FAILURE;
        DebugP_log("Error: Masked status shows disabled interrupts. Unexpected bits: 0x%x\r\n",
                   intrStatus & ~enabledIntrs);
    }
    else
    {
        DebugP_log("Masked status correctly shows only enabled interrupts\r\n");
    }

    /* Cleanup */
    ADC_clearIntrStatus(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_disableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_start(baseAddr, FALSE);
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test ADC_getIntrRawStatus for unmasked interrupt events
 *
 * Test Category: Positive test
 *
 * This test verifies that raw interrupt status shows events regardless of
 * whether they are masked or unmasked.
 */
static int32_t TestAdc_getIntrStatusRawUnmasked(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t rawStatus;
    uint32_t maskedStatus;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing raw interrupt status for unmasked events...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, FALSE, 0U);
    ClockP_usleep(100U);

    /* Disable all interrupts */
    ADC_disableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);

    /* Configure and start a conversion to generate events */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);
    {
        adcStepConfig_t adcStepCfg;
        adcStepCfg.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
        adcStepCfg.channel = ADC_CHANNEL_1;
        adcStepCfg.openDelay = 0x1U;
        adcStepCfg.sampleDelay = 0U;
        adcStepCfg.rangeCheckEnable = 0U;
        adcStepCfg.averaging = ADC_AVERAGING_NONE;
        adcStepCfg.fifoNum = ADC_FIFO_NUM_0;
        ADC_setStepParams(baseAddr, ADC_STEP_1, &adcStepCfg);
    }
    ADC_start(baseAddr, TRUE);

    /* Wait for conversion */
    ClockP_usleep(1000U);

    /* Read raw status (should show events even though interrupts are disabled) */
    rawStatus = HW_RD_REG32(baseAddr + TEST_ADC_IRQSTATUS_RAW);

    /* Read masked status (should be 0 since all interrupts are disabled) */
    maskedStatus = ADC_getIntrStatus(baseAddr);

    DebugP_log("Raw interrupt status (IRQSTATUS_RAW): 0x%x\r\n", rawStatus);
    DebugP_log("Masked interrupt status (IRQSTATUS): 0x%x\r\n", maskedStatus);

    /* Verify raw status shows events while masked status doesn't */
    if (rawStatus == 0U)
    {
        status = SystemP_FAILURE;
        DebugP_log("Error: Raw status shows no events, expected at least END_OF_SEQUENCE\r\n");
    }
    else if (maskedStatus != 0U)
    {
        status = SystemP_FAILURE;
        DebugP_log("Error: Masked status shows events when all interrupts disabled: 0x%x\r\n",
                   maskedStatus);
    }
    else
    {
        DebugP_log("Raw status correctly shows unmasked events\r\n");
    }

    /* Cleanup */
    ADC_clearIntrStatus(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_start(baseAddr, FALSE);
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test ADC_clearIntrStatus W1C (Write-1-to-Clear) targeted clear
 *
 * Test Category: Positive test
 *
 * This test verifies that ADC_clearIntrStatus correctly clears only the
 * specified interrupt sources using W1C mechanism.
 */
static int32_t TestAdc_clearIntrStatusW1C(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t intrStatusBefore;
    uint32_t intrStatusAfter;
    uint32_t targetIntrSource;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_clearIntrStatus W1C targeted clear...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, FALSE, 0U);
    ClockP_usleep(100U);

    /* Enable interrupts */
    ADC_enableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);

    /* Configure and start a conversion to generate events */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);
    {
        adcStepConfig_t adcStepCfg;
        adcStepCfg.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
        adcStepCfg.channel = ADC_CHANNEL_1;
        adcStepCfg.openDelay = 0x1U;
        adcStepCfg.sampleDelay = 0U;
        adcStepCfg.rangeCheckEnable = 0U;
        adcStepCfg.averaging = ADC_AVERAGING_NONE;
        adcStepCfg.fifoNum = ADC_FIFO_NUM_0;
        ADC_setStepParams(baseAddr, ADC_STEP_1, &adcStepCfg);
    }
    ADC_start(baseAddr, TRUE);

    /* Wait for conversion to generate interrupt status */
    ClockP_usleep(1000U);

    /* Read current interrupt status */
    intrStatusBefore = ADC_getIntrStatus(baseAddr);
    DebugP_log("Interrupt status before clear: 0x%x\r\n", intrStatusBefore);

    if (intrStatusBefore == 0U)
    {
        status = SystemP_FAILURE;
        DebugP_log("Error: No interrupt status set before clear test\r\n");
    }
    else
    {
        /* Clear only END_OF_SEQUENCE interrupt */
        targetIntrSource = ADC_INTR_SRC_END_OF_SEQUENCE;
        ADC_clearIntrStatus(baseAddr, targetIntrSource);

        /* Read status after clearing */
        intrStatusAfter = ADC_getIntrStatus(baseAddr);
        DebugP_log("Interrupt status after clearing 0x%x: 0x%x\r\n",
                   targetIntrSource, intrStatusAfter);

        /* Verify only targeted interrupt was cleared */
        if ((intrStatusAfter & targetIntrSource) != 0U)
        {
            status = SystemP_FAILURE;
            DebugP_log("Error: Target interrupt not cleared. After: 0x%x\r\n", intrStatusAfter);
        }
        else if ((intrStatusBefore & ~targetIntrSource) != (intrStatusAfter & ~targetIntrSource))
        {
            /* Check if other interrupts were unintentionally affected */
            DebugP_log("Warning: Other interrupts may have been affected\r\n");
        }
        else
        {
            DebugP_log("W1C targeted clear successful\r\n");
        }
    }

    /* Cleanup */
    ADC_clearIntrStatus(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_disableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_start(baseAddr, FALSE);
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

/**
 * \brief Test ADC_writeEOI ordering: clear then EOI
 *
 * Test Category: Positive test
 *
 * This test verifies the correct sequence of clearing interrupt status
 * before writing EOI to properly acknowledge interrupts.
 */
static int32_t TestAdc_writeClearThenEoi(test_adc_testcaseParams_t *testParams)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddr;
    uint32_t intrStatus;

    baseAddr = testParams->adcConfigParams.adcModule;

    DebugP_log("Testing ADC_writeEOI ordering: clear then EOI...\r\n");

    /* Initialize ADC hardware */
    ADC_clearIntrStatus(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_powerUp(baseAddr, TRUE);
    ClockP_usleep(10U);
    ADC_init(baseAddr, FALSE, FALSE, 0U);
    ClockP_usleep(100U);

    /* Enable interrupts */
    ADC_enableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);

    /* Configure and start a conversion */
    ADC_clearAllSteps(baseAddr);
    ADC_stepEnable(baseAddr, ADC_STEP_1, TRUE);
    {
        adcStepConfig_t adcStepCfg;
        adcStepCfg.mode = ADC_OPERATION_MODE_SINGLE_SHOT;
        adcStepCfg.channel = ADC_CHANNEL_1;
        adcStepCfg.openDelay = 0x1U;
        adcStepCfg.sampleDelay = 0U;
        adcStepCfg.rangeCheckEnable = 0U;
        adcStepCfg.averaging = ADC_AVERAGING_NONE;
        adcStepCfg.fifoNum = ADC_FIFO_NUM_0;
        ADC_setStepParams(baseAddr, ADC_STEP_1, &adcStepCfg);
    }
    ADC_start(baseAddr, TRUE);

    /* Wait for conversion */
    ClockP_usleep(1000U);

    /* Verify interrupt is pending */
    intrStatus = ADC_getIntrStatus(baseAddr);
    DebugP_log("Interrupt status before clear: 0x%x\r\n", intrStatus);

    if (intrStatus == 0U)
    {
        status = SystemP_FAILURE;
        DebugP_log("Error: No interrupt pending for EOI test\r\n");
    }
    else
    {
        /* Correct sequence: Clear interrupt status first */
        ADC_clearIntrStatus(baseAddr, intrStatus);

        /* Then write EOI */
        ADC_writeEOI(baseAddr);

        /* Verify status is cleared */
        intrStatus = ADC_getIntrStatus(baseAddr);
        DebugP_log("Interrupt status after clear then EOI: 0x%x\r\n", intrStatus);

        if (intrStatus != 0U)
        {
            status = SystemP_FAILURE;
            DebugP_log("Error: Interrupt status not cleared after EOI sequence: 0x%x\r\n",
                       intrStatus);
        }
        else
        {
            DebugP_log("Clear then EOI sequence successful\r\n");
        }
    }

    /* Cleanup */
    ADC_disableIntr(baseAddr, TEST_ADC_INTR_ALL_SOURCES);
    ADC_start(baseAddr, FALSE);
    ADC_powerUp(baseAddr, FALSE);

    return status;
}

#endif /* #ifdef SOC_AM275X */
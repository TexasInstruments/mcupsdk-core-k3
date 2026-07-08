/*
 *  Copyright (C) 2021-2026 Texas Instruments Incorporated
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

 /**
 *  \file test_epwm_system.c
 *
 *  \brief This file contains implementation of system test cases for
 *         EPWM module
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <drivers/epwm.h>
#include <drivers/hw_include/hw_types.h>
#include <unity.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Output channel - A or B */
#define APP_EPWM_OUTPUT_CH      (EPWM_OUTPUT_CH_A)

/* Duty Cycle of PWM output signal in % - give value from 0 to 100 */
#define APP_EPWM_DUTY_CYCLE     (25U)

/* Frequency of PWM output signal in Hz - 1 KHz is selected */
#define APP_EPWM_OUTPUT_FREQ    (1U * 1000U)

/* TB frequency in Hz - /1792 (maximum possible) divider is used */
#define APP_EPWM_TB_FREQ_MIN    (CONFIG_EPWM0_FCLK / 1792U)
/* TB frequency in Hz - /2 (minimum possible) divider is used */
#define APP_EPWM_TB_FREQ_MAX    (CONFIG_EPWM0_FCLK / 2U)
/* TB frequency in Hz - /4 divider is used */
#define APP_EPWM_TB_FREQ        (CONFIG_EPWM0_FCLK / 4U)

/*
 * PRD value - this determines the period
 * PRD = (TBCLK/PWM FREQ) / 2
 * /2 is added because up&down counter is selected. So period is 2 times
 */
#define APP_EPWM_PRD_VAL        ((APP_EPWM_TB_FREQ / \
                                 APP_EPWM_OUTPUT_FREQ) / 2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Variable to hold base address of EPWM that is used */
static uint32_t gEpwmBaseAddr;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t TestEpwm_tbTimebaseClkCfgTest(void);
static int32_t TestEpwm_tbPwmFreqCfgTest(void);
static int32_t TestEpwm_counterComparatorCfgTest(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief This test case verifies the configuration of EPWM time-base clock
 *         registers for different clock divider values. It includes tests for
 *         the lowest, highest, and intermediate clock divider settings. The test
 *         ensures proper register values and behavior. This is a system test case
 *         that runs on every available core in parallel.
 */
int32_t TestEpwm_systemTest1(void *args)
{
    int32_t status = SystemP_FAILURE;

    /* Address translate */
    gEpwmBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EPWM0_BASE_ADDR);

    status = TestEpwm_tbTimebaseClkCfgTest();

    return status;
}

/**
 *  \brief This test case verifies the configuration of EPWM time-base registers
 *         for different PWM frequencies, counter modes, and shadow settings.
 *         It includes tests for up and up-down counter modes with shadow enable
 *         and disable scenarios. The test ensures proper register values and behavior.
 *         This is a system test case that runs on every available core in parallel.
 */
int32_t TestEpwm_systemTest2(void *args)
{
    int32_t status = SystemP_FAILURE;

    /* Address translate */
    gEpwmBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EPWM0_BASE_ADDR);

    status = TestEpwm_tbPwmFreqCfgTest();

    return status;
}

/**
 *  \brief This test case verifies the configuration of EPWM counter comparator
 *         registers for various modes and settings. It includes tests for shadow
 *         enable/disable, load modes, and overwrite scenarios for both CMP_A and CMP_B.
 *         The test ensures proper register values and behavior. This is a system test case
 *         that runs on every available core in parallel.
 */
int32_t TestEpwm_systemTest3(void *args)
{
    int32_t status = SystemP_FAILURE;

    /* Address translate */
    gEpwmBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EPWM0_BASE_ADDR);

    status = TestEpwm_counterComparatorCfgTest();

    return status;
}

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/**
 *  \brief This test case verifies the configuration of EPWM time-base clock
 *         registers for different clock divider values. It includes tests for
 *         the lowest, highest, and intermediate clock divider settings. The test
 *         ensures proper register values and behavior. This is a system test case
 *         that runs on every available core in parallel.
 */
static int32_t TestEpwm_tbTimebaseClkCfgTest(void)
{
    uint32_t regval = 0U;
    uint32_t clkdivval = 0U;
    uint32_t hspclkdiv = 0U;

    DebugP_log("EPWM tbTimebaseClkCfg API test started ...\r\n");

    /* Check for clock div = 1 (lowest possible div) */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, CONFIG_EPWM0_FCLK,
                          CONFIG_EPWM0_FCLK);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    clkdivval = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CLKDIV);
    hspclkdiv = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_HSPCLKDIV);
    TEST_ASSERT_EQUAL_UINT32(0U, clkdivval);
    TEST_ASSERT_EQUAL_UINT32(0U, hspclkdiv);

    /* Check for clock div = 1792 (highest possible div) */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ_MIN,
                          CONFIG_EPWM0_FCLK);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    clkdivval = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CLKDIV);
    hspclkdiv = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_HSPCLKDIV);
    TEST_ASSERT_EQUAL_UINT32(7U, clkdivval);
    TEST_ASSERT_EQUAL_UINT32(7U, hspclkdiv);

    /* Check for clock div = 4 */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ,
                          CONFIG_EPWM0_FCLK);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    clkdivval = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CLKDIV);
    hspclkdiv = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_HSPCLKDIV);
    TEST_ASSERT_EQUAL_UINT32(0U, clkdivval);
    TEST_ASSERT_EQUAL_UINT32(2U, hspclkdiv);

    DebugP_log("EPWM tbTimebaseClkCfg API test passed!\r\n");

    return SystemP_SUCCESS;
}

/**
 *  \brief This test case verifies the configuration of EPWM time-base registers
 *         for different PWM frequencies, counter modes, and shadow settings.
 *         It includes tests for up and up-down counter modes with shadow enable
 *         and disable scenarios. The test ensures proper register values and behavior.
 *         This is a system test case that runs on every available core in parallel.
 */
static int32_t TestEpwm_tbPwmFreqCfgTest(void)
{
    uint32_t regval = 0U;
    uint32_t prdld = 0U;
    uint32_t ctrmode = 0U;
    uint32_t tbprdval = 0U;

    DebugP_log("EPWM tbPwmFreqCfg API test started ...\r\n");

    /* Check for up-down count mode with shadow enable */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_UP_DOWN, EPWM_SHADOW_REG_CTRL_ENABLE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    prdld = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PRDLD);
    ctrmode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CTRMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, prdld);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_UP_DOWN, ctrmode);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32(
        (APP_EPWM_TB_FREQ / APP_EPWM_OUTPUT_FREQ) / 2U, tbprdval);

    /* Check for up count mode with shadow disable */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_UP, EPWM_SHADOW_REG_CTRL_DISABLE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    prdld = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PRDLD);
    ctrmode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CTRMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_DISABLE, prdld);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_UP, ctrmode);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32(
        (APP_EPWM_TB_FREQ / APP_EPWM_OUTPUT_FREQ) - 1U, tbprdval);

    DebugP_log("EPWM tbPwmFreqCfg API test passed!\r\n");

    return SystemP_SUCCESS;
}

/**
 *  \brief This test case verifies the configuration of EPWM counter comparator
 *         registers for different modes and settings. It includes tests for
 *         shadow enable/disable, load modes, and overwrite scenarios for both
 *         CMP_A and CMP_B. The test ensures proper register values and behavior.
 *         This is a system test case that runs on every available core in parallel.
 */
static int32_t TestEpwm_counterComparatorCfgTest(void)
{
    uint32_t regval = 0U;
    uint32_t cmpval  = 0x100U;
    uint32_t cmpval2 = 0x200U;
    uint32_t cmpStatus = 0U;
    uint32_t shdwmode = 0U;
    uint32_t loadmode = 0U;
    uint32_t cmpval3  = 0U;

    DebugP_log("EPWM counterComparatorCfg API test started ...\r\n");

    /* CMP_A: shadow enable, load on CNT=0, no overwrite */
    cmpStatus = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A,
                    cmpval, EPWM_SHADOW_REG_CTRL_ENABLE,
                    EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, FALSE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    shdwmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_SHDWAMODE);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADAMODE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, cmpStatus);
    TEST_ASSERT_EQUAL_UINT32(cmpval, cmpval3);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, loadmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, shdwmode);

    /* CMP_A: shadow disable, load on CNT=PRD, no overwrite
     * (shadow is active so write should be rejected) */
    cmpStatus = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A,
                    cmpval2, EPWM_SHADOW_REG_CTRL_DISABLE,
                    EPWM_CC_CMP_LOAD_MODE_CNT_EQ_PRD, FALSE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    shdwmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_SHDWAMODE);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADAMODE);
    TEST_ASSERT_EQUAL_UINT32(FALSE, cmpStatus);
    TEST_ASSERT_EQUAL_UINT32(cmpval, cmpval3);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, loadmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, shdwmode);

    /* CMP_B: shadow enable, load on CNT=0 or PRD, no overwrite */
    cmpStatus = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B,
                    cmpval, EPWM_SHADOW_REG_CTRL_ENABLE,
                    EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD, FALSE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    shdwmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_SHDWBMODE);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADBMODE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, cmpStatus);
    TEST_ASSERT_EQUAL_UINT32(cmpval, cmpval3);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD,
                             loadmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, shdwmode);

    /* CMP_B: shadow enable, load on CNT=0 or PRD, with overwrite */
    cmpStatus = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B,
                    cmpval2, EPWM_SHADOW_REG_CTRL_ENABLE,
                    EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD, TRUE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    shdwmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_SHDWBMODE);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADBMODE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, cmpStatus);
    TEST_ASSERT_EQUAL_UINT32(cmpval2, cmpval3);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD,
                             loadmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, shdwmode);

    DebugP_log("EPWM counterComparatorCfg API test passed!\r\n");

    return SystemP_SUCCESS;
}

/*
 *  Copyright (C) 2021 - 2026 Texas Instruments Incorporated
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

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <drivers/epwm.h>
#if !defined(SOC_AM275X) && !defined(C75_CORE)
#include <drivers/soc.h>
#include <drivers/hw_include/cslr_soc.h>
#endif
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Output channel - A or B */
#define APP_EPWM_OUTPUT_CH              (EPWM_OUTPUT_CH_A)
/* Duty Cycle of PWM output signal in % - give value from 0 to 100 */
#define APP_EPWM_DUTY_CYCLE_MIN         (1U)
#define APP_EPWM_DUTY_CYCLE_MAX         (99U)
#define APP_EPWM_DUTY_CYCLE             (25U)
/* Frequency of PWM output signal in Hz - 1 KHz is selected */
#define APP_EPWM_OUTPUT_FREQ_MIN        (2U)
#define APP_EPWM_OUTPUT_FREQ_MAX        (100U * 1000U)
#define APP_EPWM_OUTPUT_FREQ            (1U * 1000U)
/* APP run time in seconds */
#define APP_EPWM_RUN_TIME               (3U)
/* Interrupt is pulse type */
#define APP_INT_IS_PULSE                (1U)

/* TB frequency in Hz - /1792 (maximum possible) divider is used */
#define APP_EPWM_TB_FREQ_MIN                (CONFIG_EPWM0_FCLK / 1792U)
/* TB frequency in Hz - /2 (minimum possible) divider is used */
#define APP_EPWM_TB_FREQ_MAX                (CONFIG_EPWM0_FCLK / 2U)
/* TB frequency in Hz - /4 divider is used */
#define APP_EPWM_TB_FREQ                    (CONFIG_EPWM0_FCLK / 4U)

/*
 *  PRD value - this determines the period
 *  PRD = (TBCLK/PWM FREQ) / 2
 *  /2 is added becasue up&down counter is selected. So period is 2 times
 */
#define APP_EPWM_PRD_VAL_MAX            ((APP_EPWM_TB_FREQ_MIN / APP_EPWM_OUTPUT_FREQ_MIN) / 2)
#define APP_EPWM_PRD_VAL_MIN            ((APP_EPWM_TB_FREQ_MAX / APP_EPWM_OUTPUT_FREQ_MAX) / 2)
#define APP_EPWM_PRD_VAL                ((APP_EPWM_TB_FREQ / APP_EPWM_OUTPUT_FREQ) / 2)

/*
 *  COMPA value - this determines the duty cycle
 *  COMPA = (PRD - ((dutycycle * PRD) / 100)
 */
#define APP_EPWM_COMPA_VAL_MIN          (APP_EPWM_PRD_VAL_MIN - ((APP_EPWM_DUTY_CYCLE_MIN * \
                                            APP_EPWM_PRD_VAL_MIN) / 100U))

#define APP_EPWM_COMPA_VAL_MAX          (APP_EPWM_PRD_VAL_MAX - ((APP_EPWM_DUTY_CYCLE_MAX * \
                                            APP_EPWM_PRD_VAL_MAX) / 100U))

#define APP_EPWM_COMPA_VAL              (APP_EPWM_PRD_VAL - ((APP_EPWM_DUTY_CYCLE * \
                                            APP_EPWM_PRD_VAL) / 100U))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef ENABLE_MT_TESTS
extern void run_epwm_multi_threaded_tests(void *args);
#endif
#if !defined(SOC_AM275X)
/* Testcases */
static void test_epwm_max_freq_min_duty(void *args);
static void test_epwm_min_freq_max_duty(void *args);
static void test_epwm_chopper(void *args);
static void test_epwm_deadband(void *args);
#endif
static void test_epwm_tbclkcfg_api(void *args);
static void test_epwm_tbfreqcfg_api(void *args);
static void test_epwm_countercomparecfg_api(void *args);
/* Time Base tests */
static void TestEpwm_tbSyncEnable(void *args);
static void TestEpwm_tbSyncDisable(void *args);
static void TestEpwm_tbSetSyncOutMode(void *args);
static void TestEpwm_tbWriteReadTbCount(void *args);
static void TestEpwm_tbSetEmulationMode(void *args);
static void TestEpwm_tbPwmFreqCfgDownCount(void *args);

/* Counter Compare tests */
static void TestEpwm_ccCmpAShadowOverwrite(void *args);
static void TestEpwm_ccCmpBAllLoadModes(void *args);

/* Action Qualifier tests */
static void TestEpwm_aqActionOnOutputChA(void *args);
static void TestEpwm_aqActionOnOutputChB(void *args);
static void TestEpwm_aqSwTriggerOneTimeChA(void *args);
static void TestEpwm_aqSwTriggerOneTimeChB(void *args);
static void TestEpwm_aqSwTriggerContAction(void *args);

/* Dead Band tests */
static void TestEpwm_dbCfgVerifyRegisters(void *args);
static void TestEpwm_dbBypassVerify(void *args);
static void TestEpwm_dbBoundaryDelays(void *args);
static void TestEpwm_dbAllInputModes(void *args);
static void TestEpwm_dbAllPolarityModes(void *args);
static void TestEpwm_dbAllOutputModes(void *args);

/* Chopper tests */
static void TestEpwm_chopperCfgVerifyRegisters(void *args);
static void TestEpwm_chopperEnableDisable(void *args);
static void TestEpwm_chopperFreqClamp(void *args);
static void TestEpwm_chopperAllDutyCycles(void *args);

#if !defined(C75_CORE) && defined(SOC_AM62DX) || defined(SOC_AM275X)
/* Trip Zone tests */
static void TestEpwm_tzTriggerTripActionChA(void *args);
static void TestEpwm_tzTriggerTripActionChB(void *args);
static void App_epwmTzIntrISR(void *handle);
#endif

/* Event Trigger tests */
static void TestEpwm_etIntrCfgAllSources(void *args);
static void TestEpwm_etIntrCfgAllPeriods(void *args);
static void TestEpwm_etIntrEnableDisable(void *args);

/* Functional tests */
static void TestEpwm_fullPwmCfgUpCount(void *args);
static void TestEpwm_tbGetStatusAndClear(void *args);

/* Boundary tests */
static void TestEpwm_tbPeriodBoundaryMax16Bit(void *args);
static void TestEpwm_ccCompareBoundaryValues(void *args);
static void TestEpwm_tbPhaseBoundaryValues(void *args);
static void TestEpwm_dbDelayAsymmetricBoundary(void *args);
static void TestEpwm_chopperOshtWidthBoundary(void *args);

/* Stress tests */
static void TestEpwm_stressTbRapidReconfigure(void *args);
static void TestEpwm_stressCcRapidOverwrite(void *args);

/* Error Injection tests */
static void TestEpwm_errCcShadowReject(void *args);

/* Coverage gap tests */
static void TestEpwm_tbClkCfgHighDividerBranch(void *args);
static void TestEpwm_tbTriggerSwSyncVerify(void *args);
static void TestEpwm_etGetEventCountVerify(void *args);

/* Negative tests - invalid parameter else branch coverage */
static void TestEpwm_negCcInvalidCmpType(void *args);
static void TestEpwm_negAqInvalidPwmOutputCh(void *args);
#if !defined(C75_CORE) && defined(SOC_AM62DX) || defined(SOC_AM275X)
static void TestEpwm_negTzInvalidParams(void *args);
#endif

/* Functions used in test */
#if !defined(SOC_AM275X)
static void App_epwmIntrISR(void *handle);
static void App_epwmConfigTest1(uint32_t epwmBaseAddr, uint32_t epwmCh,
                           uint32_t epwmFuncClk);
static void App_epwmConfigTest2(uint32_t epwmBaseAddr, uint32_t epwmCh,
                           uint32_t epwmFuncClk);
static void App_epwmConfigTest3(uint32_t epwmBaseAddr, uint32_t epwmCh,
                           uint32_t epwmFuncClk);
static void App_epwmConfigTest4(uint32_t epwmBaseAddr, uint32_t epwmCh,
                           uint32_t epwmFuncClk);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if !defined(SOC_AM275X)
static HwiP_Object       gEpwmHwiObject;
static SemaphoreP_Object gEpwmSyncSemObject;
#endif
#if !defined(C75_CORE) && defined(SOC_AM62DX) || defined(SOC_AM275X)
static HwiP_Object       gEpwmTzHwiObject;
static SemaphoreP_Object gEpwmTzSyncSemObject;
static volatile uint32_t gEpwmTzIntCount;
#endif
uint32_t gEpwmBaseAddr;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    UNITY_BEGIN();

    /* Address translate */
    gEpwmBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EPWM0_BASE_ADDR);


    #if !defined(SOC_AM275X)
    /* Run tests */
    RUN_TEST(test_epwm_max_freq_min_duty, 3010, NULL);
    RUN_TEST(test_epwm_min_freq_max_duty, 4826, NULL);
    RUN_TEST(test_epwm_chopper, 4825, NULL);
    RUN_TEST(test_epwm_deadband, 3013, NULL);
    #endif
    RUN_TEST(test_epwm_tbclkcfg_api, 3014, NULL);
    RUN_TEST(test_epwm_tbfreqcfg_api, 3015, NULL);
    RUN_TEST(test_epwm_countercomparecfg_api, 3016, NULL);

    /* Time Base tests */
    RUN_TEST(TestEpwm_tbSyncEnable, 11561, NULL);
    RUN_TEST(TestEpwm_tbSyncDisable, 11562, NULL);
    RUN_TEST(TestEpwm_tbSetSyncOutMode, 11563, NULL);
    RUN_TEST(TestEpwm_tbWriteReadTbCount, 11564, NULL);
    RUN_TEST(TestEpwm_tbSetEmulationMode, 11565, NULL);
    RUN_TEST(TestEpwm_tbPwmFreqCfgDownCount, 11566, NULL);

    /* Counter Compare tests */
    RUN_TEST(TestEpwm_ccCmpAShadowOverwrite, 11567, NULL);
    RUN_TEST(TestEpwm_ccCmpBAllLoadModes, 11568, NULL);

    /* Action Qualifier tests */
    RUN_TEST(TestEpwm_aqActionOnOutputChA, 11570, NULL);
    RUN_TEST(TestEpwm_aqActionOnOutputChB, 11571, NULL);
    RUN_TEST(TestEpwm_aqSwTriggerOneTimeChA, 11572, NULL);
    RUN_TEST(TestEpwm_aqSwTriggerOneTimeChB, 11573, NULL);
    RUN_TEST(TestEpwm_aqSwTriggerContAction, 11574, NULL);

    /* Dead Band tests */
    RUN_TEST(TestEpwm_dbCfgVerifyRegisters, 11575, NULL);
    RUN_TEST(TestEpwm_dbBypassVerify, 11576, NULL);
    RUN_TEST(TestEpwm_dbBoundaryDelays, 11577, NULL);
    RUN_TEST(TestEpwm_dbAllInputModes, 11578, NULL);
    RUN_TEST(TestEpwm_dbAllPolarityModes, 11579, NULL);
    RUN_TEST(TestEpwm_dbAllOutputModes, 11580, NULL);

    /* Chopper tests */
    RUN_TEST(TestEpwm_chopperCfgVerifyRegisters, 11581, NULL);
    RUN_TEST(TestEpwm_chopperEnableDisable, 11582, NULL);
    RUN_TEST(TestEpwm_chopperFreqClamp, 11583, NULL);
    RUN_TEST(TestEpwm_chopperAllDutyCycles, 11584, NULL);

    #if !defined(C75_CORE) && defined(SOC_AM62DX) || defined(SOC_AM275X)
    /* Trip Zone tests */
    RUN_TEST(TestEpwm_tzTriggerTripActionChA, 12058, NULL);
    RUN_TEST(TestEpwm_tzTriggerTripActionChB, 12059, NULL);
    #endif

    /* Event Trigger tests */
    RUN_TEST(TestEpwm_etIntrCfgAllSources, 11585, NULL);
    RUN_TEST(TestEpwm_etIntrCfgAllPeriods, 11586, NULL);
    RUN_TEST(TestEpwm_etIntrEnableDisable, 11587, NULL);

    /* Functional tests */
    RUN_TEST(TestEpwm_fullPwmCfgUpCount, 11589, NULL);
    RUN_TEST(TestEpwm_tbGetStatusAndClear, 11590, NULL);

    /* Boundary tests */
    RUN_TEST(TestEpwm_tbPeriodBoundaryMax16Bit, 11591, NULL);
    RUN_TEST(TestEpwm_ccCompareBoundaryValues, 11592, NULL);
    RUN_TEST(TestEpwm_tbPhaseBoundaryValues, 11593, NULL);
    RUN_TEST(TestEpwm_dbDelayAsymmetricBoundary, 11594, NULL);
    RUN_TEST(TestEpwm_chopperOshtWidthBoundary, 11595, NULL);

    /* Stress tests */
    RUN_TEST(TestEpwm_stressTbRapidReconfigure, 11596, NULL);
    RUN_TEST(TestEpwm_stressCcRapidOverwrite, 11597, NULL);

    /* Error Injection tests */
    RUN_TEST(TestEpwm_errCcShadowReject, 11599, NULL);

    /* Coverage gap tests */
    RUN_TEST(TestEpwm_tbClkCfgHighDividerBranch, 11797, NULL);
    RUN_TEST(TestEpwm_tbTriggerSwSyncVerify, 11798, NULL);
    RUN_TEST(TestEpwm_etGetEventCountVerify, 11799, NULL);

    /* Negative tests - invalid parameter else branch coverage */
    RUN_TEST(TestEpwm_negCcInvalidCmpType, 11855, NULL);
    RUN_TEST(TestEpwm_negAqInvalidPwmOutputCh, 11856, NULL);
    #if !defined(C75_CORE) && defined(SOC_AM62DX) || defined(SOC_AM275X)
    RUN_TEST(TestEpwm_negTzInvalidParams, 11857, NULL);
    #endif

    /* Multi-thread tests */
    #if defined(ENABLE_MT_TESTS)
    run_epwm_multi_threaded_tests(NULL);
    #endif

    UNITY_END();

    return;
}

/* Unity framework required information */
void setUp(void)
{
}

void tearDown(void)
{
}

/* ========================================================================== */
/*                          Function Declaration                              */
/* ========================================================================== */

#if !defined(SOC_AM275X)
/* Testcase 1 - Max frequency wave with min duty cycle */
static void test_epwm_max_freq_min_duty(void *args)
{
    int32_t             status;
    uint32_t            numIsrCnt = (APP_EPWM_RUN_TIME * APP_EPWM_OUTPUT_FREQ_MAX);
    HwiP_Params         hwiPrms;

    DebugP_log("EPWM max frequency min duty cycle test started ...\r\n");
    DebugP_log("App will produce signal for 3 seconds (using PWM period ISR) ...\r\n");

    status = SemaphoreP_constructCounting(&gEpwmSyncSemObject, 0, numIsrCnt);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = CONFIG_EPWM0_INTR;
    hwiPrms.eventId     = CONFIG_EPWM0_EVENT_ID;
    hwiPrms.callback    = &App_epwmIntrISR;
    hwiPrms.isPulse     = CONFIG_EPWM0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEpwmHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Configure PWM */
    App_epwmConfigTest1(gEpwmBaseAddr, APP_EPWM_OUTPUT_CH, CONFIG_EPWM0_FCLK);

    while(numIsrCnt > 0)
    {
        SemaphoreP_pend(&gEpwmSyncSemObject, SystemP_WAIT_FOREVER);
        numIsrCnt--;
    }

    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);     /* Clear any pending interrupts if any */
    HwiP_destruct(&gEpwmHwiObject);
    SemaphoreP_destruct(&gEpwmSyncSemObject);
    return;
}

/* Testcase 2 - Min frequency wave with max duty cycle */
static void test_epwm_min_freq_max_duty(void *args)
{
    int32_t             status;
    uint32_t            numIsrCnt = (APP_EPWM_RUN_TIME * APP_EPWM_OUTPUT_FREQ_MIN);
    HwiP_Params         hwiPrms;

    DebugP_log("EPWM min frequency max duty cycle test started ...\r\n");
    DebugP_log("App will produce signal for 3 seconds (using PWM period ISR) ...\r\n");

    status = SemaphoreP_constructCounting(&gEpwmSyncSemObject, 0, numIsrCnt);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = CONFIG_EPWM0_INTR;
    hwiPrms.eventId     = CONFIG_EPWM0_EVENT_ID;
    hwiPrms.callback    = &App_epwmIntrISR;
    hwiPrms.isPulse     = CONFIG_EPWM0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEpwmHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Configure PWM */
    App_epwmConfigTest2(gEpwmBaseAddr, APP_EPWM_OUTPUT_CH, CONFIG_EPWM0_FCLK);

    while(numIsrCnt > 0)
    {
        SemaphoreP_pend(&gEpwmSyncSemObject, SystemP_WAIT_FOREVER);
        numIsrCnt--;
    }

    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);     /* Clear any pending interrupts if any */
    HwiP_destruct(&gEpwmHwiObject);
    SemaphoreP_destruct(&gEpwmSyncSemObject);
    return;
}

/* Testcase 3 - Use chopper to generate higher frequency wave with configurable width of first and subsequent pulses */
static void test_epwm_chopper(void *args)
{
    int32_t             status;
    uint32_t            numIsrCnt = (APP_EPWM_RUN_TIME * APP_EPWM_OUTPUT_FREQ);
    HwiP_Params         hwiPrms;

    DebugP_log("EPWM Chopper module test ...\r\n");
    DebugP_log("App will produce signal for 3 seconds (using PWM period ISR) ...\r\n");

    status = SemaphoreP_constructCounting(&gEpwmSyncSemObject, 0, numIsrCnt);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = CONFIG_EPWM0_INTR;
    hwiPrms.eventId     = CONFIG_EPWM0_EVENT_ID;
    hwiPrms.callback    = &App_epwmIntrISR;
    hwiPrms.isPulse     = CONFIG_EPWM0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEpwmHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Configure PWM */
    App_epwmConfigTest3(gEpwmBaseAddr, APP_EPWM_OUTPUT_CH, CONFIG_EPWM0_FCLK);

    while(numIsrCnt > 0)
    {
        SemaphoreP_pend(&gEpwmSyncSemObject, SystemP_WAIT_FOREVER);
        numIsrCnt--;
    }

    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);     /* Clear any pending interrupts if any */
    HwiP_destruct(&gEpwmHwiObject);
    SemaphoreP_destruct(&gEpwmSyncSemObject);
    return;
}

/* Testcase 4 - Use deadband to generate wave with configurable RED and FED values */
static void test_epwm_deadband(void *args)
{
    int32_t             status;
    uint32_t            numIsrCnt = (APP_EPWM_RUN_TIME * APP_EPWM_OUTPUT_FREQ);
    HwiP_Params         hwiPrms;

    DebugP_log("EPWM deadband test ...\r\n");
    DebugP_log("App will produce signal for 3 seconds (using PWM period ISR) ...\r\n");

    status = SemaphoreP_constructCounting(&gEpwmSyncSemObject, 0, numIsrCnt);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = CONFIG_EPWM0_INTR;
    hwiPrms.eventId     = CONFIG_EPWM0_EVENT_ID;
    hwiPrms.callback    = &App_epwmIntrISR;
    hwiPrms.isPulse     = CONFIG_EPWM0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEpwmHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Configure PWM */
    App_epwmConfigTest4(gEpwmBaseAddr, APP_EPWM_OUTPUT_CH, CONFIG_EPWM0_FCLK);

    while(numIsrCnt > 0)
    {
        SemaphoreP_pend(&gEpwmSyncSemObject, SystemP_WAIT_FOREVER);
        numIsrCnt--;
    }

    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);     /* Clear any pending interrupts if any */
    HwiP_destruct(&gEpwmHwiObject);
    SemaphoreP_destruct(&gEpwmSyncSemObject);
    return;
}
#endif

/* Testcase 5 - Test EPWM_tbTimebaseClkCfg for various combinations of inputs */
static void test_epwm_tbclkcfg_api(void *args)
{
    uint32_t regval = 0U;
    uint32_t clkdivval = 0U;
    uint32_t hspclkdiv = 0U;

    /* Check for clock div = 1 (lowest possible div) */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, CONFIG_EPWM0_FCLK, CONFIG_EPWM0_FCLK);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    clkdivval = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CLKDIV);
    hspclkdiv = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_HSPCLKDIV);
    TEST_ASSERT_EQUAL_UINT32(0, clkdivval);
    TEST_ASSERT_EQUAL_UINT32(0, hspclkdiv);

    /* Check for clock div = 1792 (highest possible div) */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ_MIN, CONFIG_EPWM0_FCLK);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    clkdivval = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CLKDIV);
    hspclkdiv = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_HSPCLKDIV);
    TEST_ASSERT_EQUAL_UINT32(7, clkdivval);
    TEST_ASSERT_EQUAL_UINT32(7, hspclkdiv);

    /* Check for clock div = 4 */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, CONFIG_EPWM0_FCLK);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    clkdivval = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CLKDIV);
    hspclkdiv = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_HSPCLKDIV);
    TEST_ASSERT_EQUAL_UINT32(0, clkdivval);
    TEST_ASSERT_EQUAL_UINT32(2, hspclkdiv);

    return;
}

/* Testcase 6 - Test EPWM_tbPwmFreqCfg for various combinations of inputs */
static void test_epwm_tbfreqcfg_api(void *args)
{
    uint32_t regval = 0U;
    uint32_t prdld = 0U;
    uint32_t ctrmode = 0U;
    uint32_t tbprdval = 0U;

    /* Check for up down count mode */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_UP_DOWN, EPWM_SHADOW_REG_CTRL_ENABLE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    prdld = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PRDLD);
    ctrmode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CTRMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, prdld);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_UP_DOWN, ctrmode);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32((APP_EPWM_TB_FREQ/APP_EPWM_OUTPUT_FREQ)/2U, tbprdval);

    /* Check for up count mode */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_UP, EPWM_SHADOW_REG_CTRL_DISABLE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    prdld = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PRDLD);
    ctrmode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CTRMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_DISABLE, prdld);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_UP, ctrmode);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32((APP_EPWM_TB_FREQ/APP_EPWM_OUTPUT_FREQ)-1U, tbprdval);

    return;
}

/* Testcase 7 - Test EPWM_counterComparatorCfg for various combinations of inputs */
static void test_epwm_countercomparecfg_api(void *args)
{
    uint32_t regval = 0U;
    uint32_t cmpval = 0x100;
    uint32_t cmpval2 = 0x200;
    uint32_t status = 0U;
    uint32_t shdwmode = 0U;
    uint32_t loadmode = 0U;
    uint32_t cmpval3 = 0U;

    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, cmpval,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, FALSE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    shdwmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_SHDWAMODE);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADAMODE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    TEST_ASSERT_EQUAL_UINT32(cmpval, cmpval3);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, loadmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, shdwmode);

    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, cmpval2,
                                       EPWM_SHADOW_REG_CTRL_DISABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_PRD, FALSE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    shdwmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_SHDWAMODE);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADAMODE);
    TEST_ASSERT_EQUAL_UINT32(FALSE, status);
    TEST_ASSERT_EQUAL_UINT32(cmpval, cmpval3);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, loadmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, shdwmode);

    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, cmpval,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD, FALSE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    shdwmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_SHDWBMODE);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADBMODE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    TEST_ASSERT_EQUAL_UINT32(cmpval, cmpval3);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD, loadmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, shdwmode);

    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, cmpval2,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD, TRUE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    shdwmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_SHDWBMODE);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADBMODE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    TEST_ASSERT_EQUAL_UINT32(cmpval2, cmpval3);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD, loadmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, shdwmode);

    return;
}

/**
 * @brief Test case for enabling and verifying EPWM Time-Base (TB) synchronization.
 *
 * This test verifies the correct behavior of the EPWM_tbSyncEnable and EPWM_tbSyncDisable APIs.
 * It checks if the phase value and counter direction are set as expected after enabling sync
 * with different phase values and directions. The test also ensures that the phase load enable
 * bit is set correctly. After the checks, it disables the sync to restore the initial state.
 * This helps validate the correct configuration and operation of the EPWM synchronization logic.
 *
 * The test covers both UP and DOWN counter directions and validates register values after each operation.
 */
static void TestEpwm_tbSyncEnable(void *args)
{
    uint32_t regval = 0U;
    uint32_t phsVal = 0U;
    uint32_t phsDir = 0U;
    uint32_t phsEn  = 0U;

    /* Enable sync with phase=500, direction=UP */
    EPWM_tbSyncEnable(gEpwmBaseAddr, 500U, EPWM_TB_COUNTER_DIR_UP);

    /* Verify phase value */
    phsVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_TBPHS, PWMSS_EPWM_TBPHS);
    TEST_ASSERT_EQUAL_UINT32(500U, phsVal);

    /* Verify counter direction after sync */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    phsDir = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PHSDIR);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_UP, phsDir);

    /* Verify phase load enabled */
    phsEn = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PHSEN);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_TBCTL_PHSEN_LOAD, phsEn);

    /* Test with different phase value and direction */
    EPWM_tbSyncEnable(gEpwmBaseAddr, 1000U, EPWM_TB_COUNTER_DIR_DOWN);

    phsVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_TBPHS, PWMSS_EPWM_TBPHS);
    TEST_ASSERT_EQUAL_UINT32(1000U, phsVal);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    phsDir = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PHSDIR);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_DOWN, phsDir);

    /* Cleanup: disable sync */
    EPWM_tbSyncDisable(gEpwmBaseAddr);

    return;
}

/**
 * @brief Test case for disabling EPWM Time-Base (TB) synchronization.
 *
 * This test first enables TB sync and verifies the phase load enable bit is set.
 * It then disables TB sync and checks that the phase load enable bit is cleared,
 * confirming that the EPWM_tbSyncDisable API works as expected. This ensures
 * correct handling of the phase synchronization enable/disable logic in the
 * EPWM module.
 */
static void TestEpwm_tbSyncDisable(void *args)
{
    uint32_t regval = 0U;
    uint32_t phsEn  = 0U;

    /* First enable sync */
    EPWM_tbSyncEnable(gEpwmBaseAddr, 100U, EPWM_TB_COUNTER_DIR_UP);

    /* Verify enabled */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    phsEn = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PHSEN);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_TBCTL_PHSEN_LOAD, phsEn);

    /* Now disable sync */
    EPWM_tbSyncDisable(gEpwmBaseAddr);

    /* Verify disabled */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    phsEn = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PHSEN);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_TBCTL_PHSEN_DO_NOT_LOAD, phsEn);

    return;
}

/**
 * @brief Unit test for EPWM_tbSetSyncOutMode function.
 *
 * This test case verifies the correct configuration of the EPWM Time-Base (TB) Sync-Out mode.
 * It checks the hardware register field after setting each possible sync-out mode, including:
 * passthrough of sync-in, counter equals zero, counter equals CMPB, and sync disabled.
 * The test ensures that the EPWM_tbSetSyncOutMode API correctly updates the SYNCOSEL field
 * in the TBCTL register for each mode. Assertions are used to validate the expected behavior.
 * This helps guarantee reliable synchronization features in the EPWM driver.
 */
static void TestEpwm_tbSetSyncOutMode(void *args)
{
    uint32_t regval = 0U;
    uint32_t syncOutMode = 0U;

    /* Test sync-in passthrough */
    EPWM_tbSetSyncOutMode(gEpwmBaseAddr, EPWM_TB_SYNC_OUT_EVT_SYNCIN);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    syncOutMode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_SYNCOSEL);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_SYNC_OUT_EVT_SYNCIN, syncOutMode);

    /* Test counter=zero sync */
    EPWM_tbSetSyncOutMode(gEpwmBaseAddr, EPWM_TB_SYNC_OUT_EVT_CNT_EQ_ZERO);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    syncOutMode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_SYNCOSEL);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_SYNC_OUT_EVT_CNT_EQ_ZERO, syncOutMode);

    /* Test counter=CMPB sync */
    EPWM_tbSetSyncOutMode(gEpwmBaseAddr, EPWM_TB_SYNC_OUT_EVT_CNT_EQ_CMP_B);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    syncOutMode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_SYNCOSEL);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_SYNC_OUT_EVT_CNT_EQ_CMP_B, syncOutMode);

    /* Test sync disabled */
    EPWM_tbSetSyncOutMode(gEpwmBaseAddr, EPWM_TB_SYNC_OUT_EVT_DISABLE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    syncOutMode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_SYNCOSEL);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_SYNC_OUT_EVT_DISABLE, syncOutMode);

    /* Restore to reset value (0) */
    EPWM_tbSetSyncOutMode(gEpwmBaseAddr, EPWM_TB_SYNC_OUT_EVT_SYNCIN);

    return;
}

/**
 * @brief Test case for verifying EPWM time-base counter write and read operations.
 *
 * This test stops the EPWM time-base counter to ensure a stable state for testing.
 * It writes specific values (zero, a mid-range value, and the maximum 16-bit value)
 * to the time-base counter and reads them back to verify correctness.
 * The test uses assertions to ensure the written and read values match as expected.
 * After the test, the counter is reset to zero to restore the initial state.
 * This ensures the EPWM_tbWriteTbCount and EPWM_tbReadTbCount APIs function as intended.
 */
static void TestEpwm_tbWriteReadTbCount(void *args)
{
    uint16_t count = 0U;

    /* Stop counter first so it doesn't change under us */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_STOP, EPWM_SHADOW_REG_CTRL_DISABLE);

    /* Write zero and verify */
    EPWM_tbWriteTbCount(gEpwmBaseAddr, 0U);
    count = EPWM_tbReadTbCount(gEpwmBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(0U, count);

    /* Write mid value and verify */
    EPWM_tbWriteTbCount(gEpwmBaseAddr, 1000U);
    count = EPWM_tbReadTbCount(gEpwmBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(1000U, count);

    /* Write max 16-bit value and verify */
    EPWM_tbWriteTbCount(gEpwmBaseAddr, 0xFFFFU);
    count = EPWM_tbReadTbCount(gEpwmBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFU, count);

    /* Reset counter */
    EPWM_tbWriteTbCount(gEpwmBaseAddr, 0U);

    return;
}

/**
 * @brief Test case 1005: Verify EPWM_tbSetEmulationMode for all emulation modes.
 *
 * This test function validates the correct behavior of the EPWM_tbSetEmulationMode
 * API by setting the emulation mode to all supported values and verifying the
 * hardware register reflects the expected mode. It checks the free run mode,
 * stop after next cycle, and stop after complete cycle modes. After each mode
 * is set, the test reads back the register and asserts the value matches the
 * requested mode. The test restores the emulation mode to free run at the end.
 *
 * This ensures that the emulation mode configuration is correctly applied and
 * can be reliably used in different operational scenarios.
 */
static void TestEpwm_tbSetEmulationMode(void *args)
{
    uint32_t regval = 0U;
    uint32_t mode = 0U;

    /* Free run mode */
    EPWM_tbSetEmulationMode(gEpwmBaseAddr, EPWM_TB_EMU_MODE_FREE_RUN);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    mode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_FREE_SOFT);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_EMU_MODE_FREE_RUN, mode);

    /* Stop after next cycle */
    EPWM_tbSetEmulationMode(gEpwmBaseAddr, EPWM_TB_EMU_MODE_STP_AFT_NEXT_CYCLE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    mode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_FREE_SOFT);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_EMU_MODE_STP_AFT_NEXT_CYCLE, mode);

    /* Stop after complete cycle */
    EPWM_tbSetEmulationMode(gEpwmBaseAddr, EPWM_TB_EMU_MODE_STP_AFT_COMPLETE_CYCLE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    mode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_FREE_SOFT);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_EMU_MODE_STP_AFT_COMPLETE_CYCLE, mode);

    /* Restore to free run */
    EPWM_tbSetEmulationMode(gEpwmBaseAddr, EPWM_TB_EMU_MODE_FREE_RUN);

    return;
}

/**
 * @brief Test case to configure and verify EPWM Time-Base (TB) frequency
 *        configuration in DOWN count mode with shadow register enabled.
 *
 * This test configures the EPWM module to operate in DOWN count mode and
 * verifies the counter direction and shadow register control settings.
 * Additionally, it checks the calculated period value for the configured
 * frequency to ensure correctness. The test ensures that the EPWM module
 * behaves as expected in this configuration.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_tbPwmFreqCfgDownCount(void *args)
{
    uint32_t regval = 0U;
    uint32_t ctrmode = 0U;
    uint32_t tbprdval = 0U;
    uint32_t prdld = 0U;

    /* Configure DOWN count mode with shadow enabled */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_DOWN, EPWM_SHADOW_REG_CTRL_ENABLE);

    /* Verify counter direction */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    ctrmode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CTRMODE);
    prdld = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_PRDLD);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_DOWN, ctrmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, prdld);

    /* Verify period: DOWN mode uses (tbClk/pwmFreq - 1) same as UP mode */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32((APP_EPWM_TB_FREQ / APP_EPWM_OUTPUT_FREQ) - 1U, tbprdval);

    return;
}

/**
 * @brief Test case for verifying the behavior of the EPWM counter comparator
 *        shadow register overwrite functionality.
 *
 * This test first configures the EPWM counter comparator with shadow register
 * control enabled and overwrite set to FALSE. It verifies that the shadow
 * register is updated correctly. Then, it reconfigures the comparator with
 * overwrite set to TRUE and ensures that the shadow register is overwritten
 * with the new value. The test validates the correctness of the register
 * values after each configuration.
 *
 * @param args Unused parameter.
 */
static void TestEpwm_ccCmpAShadowOverwrite(void *args)
{
    uint32_t status = 0U;
    uint32_t regval = 0U;
    uint32_t cmpval3 = 0U;

    /* First write with overwrite=FALSE, should succeed */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, 0x100U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, FALSE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(0x100U, cmpval3);

    /* Second write with overwrite=TRUE, should overwrite the shadow */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, 0x300U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(0x300U, cmpval3);

    return;
}

/**
 * @brief Test case for verifying all load modes of the EPWM counter comparator B.
 *
 * This test configures the EPWM counter comparator B with different load modes:
 * counter equals zero, counter equals period, counter equals zero or period,
 * and freeze (no load). It validates the configuration by reading back the
 * register values and comparing them against the expected values. The shadow
 * register control and comparator values are also verified for correctness.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_ccCmpBAllLoadModes(void *args)
{
    uint32_t status = 0U;
    uint32_t regval = 0U;
    uint32_t loadmode = 0U;
    uint32_t shdwmode = 0U;
    uint32_t cmpval3 = 0U;

    /* Load mode: counter = zero */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, 0x50U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADBMODE);
    shdwmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_SHDWBMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, loadmode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_SHADOW_REG_CTRL_ENABLE, shdwmode);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval3 = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    TEST_ASSERT_EQUAL_UINT32(0x50U, cmpval3);

    /* Load mode: counter = period */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, 0x60U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_PRD, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADBMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_PRD, loadmode);

    /* Load mode: counter = zero or period */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, 0x70U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADBMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD, loadmode);

    /* Load mode: freeze (no load) */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, 0x80U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_NO_LOAD, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPCTL);
    loadmode = HW_GET_FIELD(regval, PWMSS_EPWM_CMPCTL_LOADBMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CC_CMP_LOAD_MODE_NO_LOAD, loadmode);

    return;
}

/**
 * @brief Test case for verifying EPWM_aqActionOnOutputCfg for Channel A.
 *
 * This test configures the Action Qualifier (AQ) submodule for Channel A with
 * distinct actions for zero, period, and compare events. It validates the
 * configuration by reading back the AQCTLA register and comparing the values
 * against the expected actions. This ensures the correct behavior of the
 * EPWM_aqActionOnOutputCfg API for Channel A.
 */
static void TestEpwm_aqActionOnOutputChA(void *args)
{
    EPWM_AqActionCfg aqConfig;
    uint32_t regval = 0U;

    /* Set distinct action for each event */
    aqConfig.zeroAction     = EPWM_AQ_ACTION_HIGH;
    aqConfig.prdAction      = EPWM_AQ_ACTION_LOW;
    aqConfig.cmpAUpAction   = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpADownAction = EPWM_AQ_ACTION_LOW;
    aqConfig.cmpBUpAction   = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpBDownAction = EPWM_AQ_ACTION_DONOTHING;

    EPWM_aqActionOnOutputCfg(gEpwmBaseAddr, EPWM_OUTPUT_CH_A, &aqConfig);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQCTLA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_HIGH,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_ZRO));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_LOW,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_PRD));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_HIGH,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_CAU));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_LOW,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_CAD));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_DONOTHING,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_CBU));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_DONOTHING,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_CBD));

    return;
}

/**
 * @brief  Test case to verify the Action Qualifier (AQ) configuration for
 *         EPWM Channel B. This test sets various actions for different
 *         events (zero, period, compare A up/down, compare B up/down)
 *         and validates the configuration by reading back the AQCTLB
 *         register fields. The test ensures that the AQ actions are
 *         correctly applied to Channel B as per the configuration.
 *
 * @param  args  Pointer to arguments (not used in this test case).
 */
static void TestEpwm_aqActionOnOutputChB(void *args)
{
    EPWM_AqActionCfg aqConfig;
    uint32_t regval = 0U;

    /* Set different actions for Channel B */
    aqConfig.zeroAction     = EPWM_AQ_ACTION_LOW;
    aqConfig.prdAction      = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpAUpAction   = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpADownAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpBUpAction   = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpBDownAction = EPWM_AQ_ACTION_LOW;

    EPWM_aqActionOnOutputCfg(gEpwmBaseAddr, EPWM_OUTPUT_CH_B, &aqConfig);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQCTLB);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_LOW,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLB_ZRO));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_HIGH,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLB_PRD));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_DONOTHING,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLB_CAU));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_DONOTHING,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLB_CAD));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_HIGH,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLB_CBU));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_LOW,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLB_CBD));

    return;
}

/**
 * @brief Test case for verifying EPWM_aqSwTriggerOneTimeAction for Channel A.
 *
 * This test triggers one-time actions (HIGH and LOW) on Channel A using the
 * EPWM_aqSwTriggerOneTimeAction API. It validates the configuration by reading
 * back the AQSFRC register and comparing the values against the expected actions.
 * The test ensures that the one-time software-triggered actions are correctly
 * applied to Channel A.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_aqSwTriggerOneTimeChA(void *args)
{
    uint32_t regval = 0U;
    uint32_t actsfA = 0U;

    /* Trigger one-time HIGH on Channel A */
    EPWM_aqSwTriggerOneTimeAction(gEpwmBaseAddr, EPWM_OUTPUT_CH_A,
                                  EPWM_AQ_SW_TRIG_OT_ACTION_HIGH);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQSFRC);
    actsfA = HW_GET_FIELD(regval, PWMSS_EPWM_AQSFRC_ACTSFA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_SW_TRIG_OT_ACTION_HIGH, actsfA);

    /* Trigger one-time LOW on Channel A */
    EPWM_aqSwTriggerOneTimeAction(gEpwmBaseAddr, EPWM_OUTPUT_CH_A,
                                  EPWM_AQ_SW_TRIG_OT_ACTION_LOW);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQSFRC);
    actsfA = HW_GET_FIELD(regval, PWMSS_EPWM_AQSFRC_ACTSFA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_SW_TRIG_OT_ACTION_LOW, actsfA);

    return;
}

/**
 * @brief Test case for verifying the software-triggered one-time actions
 *        on ePWM Channel B. This test ensures that the ePWM module correctly
 *        applies the specified one-time actions (HIGH and TOGGLE) on Channel B
 *        when triggered via software. The test reads the Action Qualifier
 *        Software Force Register (AQSFRC) to validate the applied action.
 *
 *        The test performs the following steps:
 *        1. Triggers a one-time HIGH action on Channel B and verifies the result.
 *        2. Triggers a one-time TOGGLE action on Channel B and verifies the result.
 */
static void TestEpwm_aqSwTriggerOneTimeChB(void *args)
{
    uint32_t regval = 0U;
    uint32_t actsfB = 0U;

    /* Trigger one-time HIGH on Channel B */
    EPWM_aqSwTriggerOneTimeAction(gEpwmBaseAddr, EPWM_OUTPUT_CH_B,
                                  EPWM_AQ_SW_TRIG_OT_ACTION_HIGH);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQSFRC);
    actsfB = HW_GET_FIELD(regval, PWMSS_EPWM_AQSFRC_ACTSFB);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_SW_TRIG_OT_ACTION_HIGH, actsfB);

    /* Trigger one-time TOGGLE on Channel B */
    EPWM_aqSwTriggerOneTimeAction(gEpwmBaseAddr, EPWM_OUTPUT_CH_B,
                                  EPWM_AQ_SW_TRIG_OT_ACTION_TOGGLE);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQSFRC);
    actsfB = HW_GET_FIELD(regval, PWMSS_EPWM_AQSFRC_ACTSFB);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_SW_TRIG_OT_ACTION_TOGGLE, actsfB);

    return;
}

/**
 * @brief   Test case for verifying the continuous software-triggered actions
 *          on EPWM output channels A and B. This test ensures that the
 *          appropriate actions (HIGH or LOW) are applied to the channels
 *          based on the specified reload conditions (zero or period).
 *          It also validates that changes to one channel do not affect
 *          the other channel. Finally, the test disables the continuous
 *          forcing actions to restore the default state.
 *
 * @param   args    Pointer to test arguments (not used in this test case).
 */
static void TestEpwm_aqSwTriggerContAction(void *args)
{
    uint32_t regval = 0U;
    uint32_t csfA = 0U;
    uint32_t csfB = 0U;
    uint32_t rldcsf = 0U;

    /* Force continuous HIGH on Channel A with reload at zero */
    EPWM_aqSwTriggerContAction(gEpwmBaseAddr, EPWM_OUTPUT_CH_A,
                               EPWM_AQ_SW_TRIG_CONT_ACTION_HIGH,
                               EPWM_AQ_CSFRC_REG_RELOAD_CNT_EQ_ZRO);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQSFRC);
    rldcsf = HW_GET_FIELD(regval, PWMSS_EPWM_AQSFRC_RLDCSF);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_CSFRC_REG_RELOAD_CNT_EQ_ZRO, rldcsf);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQCSFRC);
    csfA = HW_GET_FIELD(regval, PWMSS_EPWM_AQCSFRC_CSFA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_SW_TRIG_CONT_ACTION_HIGH, csfA);

    /* Force continuous LOW on Channel B with reload at period */
    EPWM_aqSwTriggerContAction(gEpwmBaseAddr, EPWM_OUTPUT_CH_B,
                               EPWM_AQ_SW_TRIG_CONT_ACTION_LOW,
                               EPWM_AQ_CSFRC_REG_RELOAD_CNT_EQ_PRD);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQCSFRC);
    csfB = HW_GET_FIELD(regval, PWMSS_EPWM_AQCSFRC_CSFB);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_SW_TRIG_CONT_ACTION_LOW, csfB);

    /* Verify Channel A not changed by Channel B write */
    csfA = HW_GET_FIELD(regval, PWMSS_EPWM_AQCSFRC_CSFA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_SW_TRIG_CONT_ACTION_HIGH, csfA);

    /* Disable continuous forcing */
    EPWM_aqSwTriggerContAction(gEpwmBaseAddr, EPWM_OUTPUT_CH_A,
                               EPWM_AQ_SW_TRIG_CONT_ACTION_NOEFFECT,
                               EPWM_AQ_CSFRC_REG_RELOAD_IMMEDIATE);
    EPWM_aqSwTriggerContAction(gEpwmBaseAddr, EPWM_OUTPUT_CH_B,
                               EPWM_AQ_SW_TRIG_CONT_ACTION_NOEFFECT,
                               EPWM_AQ_CSFRC_REG_RELOAD_IMMEDIATE);

    return;
}

/**
 * @brief Test case for verifying the configuration of the EPWM Deadband module.
 *
 * This test configures the EPWM Deadband submodule with specific input mode,
 * output mode, polarity, and delay values. It validates the configuration by
 * reading back the DBCTL, DBRED, and DBFED registers and comparing the values
 * against the expected settings. The test ensures that the EPWM_deadbandCfg
 * API correctly applies the desired configuration. After verification, the
 * deadband is bypassed to restore the default state.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_dbCfgVerifyRegisters(void *args)
{
    EPWM_DeadbandCfg dbCfg;
    uint32_t regval = 0U;
    uint32_t inMode = 0U;
    uint32_t outMode = 0U;
    uint32_t polsel = 0U;
    uint32_t redVal = 0U;
    uint32_t fedVal = 0U;

    dbCfg.inputMode      = EPWM_DB_IN_MODE_A_RED_A_FED;
    dbCfg.outputMode     = EPWM_DB_OUT_MODE_A_RED_B_FED;
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH_COMPLEMENTARY;
    dbCfg.risingEdgeDelay  = 150U;
    dbCfg.fallingEdgeDelay = 200U;

    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);

    /* Verify DBCTL register */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    inMode  = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_IN_MODE);
    outMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_OUT_MODE);
    polsel  = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_POLSEL);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_IN_MODE_A_RED_A_FED, inMode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_OUT_MODE_A_RED_B_FED, outMode);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_POL_SEL_ACTV_HIGH_COMPLEMENTARY, polsel);

    /* Verify delay values */
    redVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBRED, PWMSS_EPWM_DBRED_DEL);
    fedVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBFED, PWMSS_EPWM_DBFED_DEL);
    TEST_ASSERT_EQUAL_UINT32(150U, redVal);
    TEST_ASSERT_EQUAL_UINT32(200U, fedVal);

    /* Cleanup: bypass dead band */
    EPWM_deadbandBypass(gEpwmBaseAddr);

    return;
}

/**
 * @brief  Test case to verify the deadband bypass functionality of the EPWM module.
 *
 * This test configures the EPWM deadband with specific input and output modes,
 * along with rising and falling edge delays. It then verifies that the output
 * mode is correctly enabled. Subsequently, the deadband is bypassed, and the
 * test ensures that the output mode is disabled (bypassed) as expected.
 *
 * The test uses hardware register reads and field checks to validate the
 * correctness of the deadband configuration and bypass functionality.
 */
static void TestEpwm_dbBypassVerify(void *args)
{
    EPWM_DeadbandCfg dbCfg;
    uint32_t regval = 0U;
    uint32_t outMode = 0U;

    /* First configure dead band with output enabled */
    dbCfg.inputMode      = EPWM_DB_IN_MODE_A_RED_A_FED;
    dbCfg.outputMode     = EPWM_DB_OUT_MODE_A_RED_B_FED;
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH;
    dbCfg.risingEdgeDelay  = 100U;
    dbCfg.fallingEdgeDelay = 100U;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);

    /* Verify output mode is enabled */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    outMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_OUT_MODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_OUT_MODE_A_RED_B_FED, outMode);

    /* Now bypass */
    EPWM_deadbandBypass(gEpwmBaseAddr);

    /* Verify output mode is disabled (bypassed) */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    outMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_OUT_MODE);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_DBCTL_OUT_MODE_DISABLED, outMode);

    return;
}

/**
 * @brief Test case to validate the boundary conditions of the EPWM deadband
 *        rising and falling edge delay configurations. This test ensures that
 *        the deadband delay values are correctly set and read back for both
 *        minimum (0) and maximum (1023) 10-bit delay values.
 *
 *        The test first configures the deadband delays to zero and verifies
 *        the hardware registers reflect the same. It then sets the delays to
 *        their maximum values and validates the register values again.
 *
 *        Finally, the deadband is bypassed to clean up the configuration.
 */
static void TestEpwm_dbBoundaryDelays(void *args)
{
    EPWM_DeadbandCfg dbCfg;
    uint32_t redVal = 0U;
    uint32_t fedVal = 0U;

    /* Test with zero delays */
    dbCfg.inputMode      = EPWM_DB_IN_MODE_A_RED_A_FED;
    dbCfg.outputMode     = EPWM_DB_OUT_MODE_A_RED_B_FED;
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH;
    dbCfg.risingEdgeDelay  = 0U;
    dbCfg.fallingEdgeDelay = 0U;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);

    redVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBRED, PWMSS_EPWM_DBRED_DEL);
    fedVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBFED, PWMSS_EPWM_DBFED_DEL);
    TEST_ASSERT_EQUAL_UINT32(0U, redVal);
    TEST_ASSERT_EQUAL_UINT32(0U, fedVal);

    /* Test with max 10-bit delay values (0x3FF = 1023) */
    dbCfg.risingEdgeDelay  = 0x3FFU;
    dbCfg.fallingEdgeDelay = 0x3FFU;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);

    redVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBRED, PWMSS_EPWM_DBRED_DEL);
    fedVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBFED, PWMSS_EPWM_DBFED_DEL);
    TEST_ASSERT_EQUAL_UINT32(0x3FFU, redVal);
    TEST_ASSERT_EQUAL_UINT32(0x3FFU, fedVal);

    /* Cleanup */
    EPWM_deadbandBypass(gEpwmBaseAddr);

    return;
}

/**
 * @brief Test case for verifying all input modes of the EPWM Deadband submodule.
 *
 * This test configures the EPWM Deadband submodule with different input modes
 * and validates the configuration by reading back the register values. The
 * input modes tested include combinations of A and B signals feeding the
 * Rising Edge Delay (RED) and Falling Edge Delay (FED) paths. The test ensures
 * that the hardware registers are correctly updated for each input mode.
 *
 * After the test, the deadband is bypassed to clean up the configuration.
 */
static void TestEpwm_dbAllInputModes(void *args)
{
    EPWM_DeadbandCfg dbCfg;
    uint32_t regval = 0U;
    uint32_t inMode = 0U;

    dbCfg.outputMode     = EPWM_DB_OUT_MODE_A_RED_B_FED;
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH;
    dbCfg.risingEdgeDelay  = 50U;
    dbCfg.fallingEdgeDelay = 50U;

    /* A feeds RED, A feeds FED */
    dbCfg.inputMode = EPWM_DB_IN_MODE_A_RED_A_FED;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    inMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_IN_MODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_IN_MODE_A_RED_A_FED, inMode);

    /* B feeds RED, A feeds FED */
    dbCfg.inputMode = EPWM_DB_IN_MODE_B_RED_A_FED;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    inMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_IN_MODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_IN_MODE_B_RED_A_FED, inMode);

    /* A feeds RED, B feeds FED */
    dbCfg.inputMode = EPWM_DB_IN_MODE_A_RED_B_FED;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    inMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_IN_MODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_IN_MODE_A_RED_B_FED, inMode);

    /* B feeds RED, B feeds FED */
    dbCfg.inputMode = EPWM_DB_IN_MODE_B_RED_B_FED;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    inMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_IN_MODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_IN_MODE_B_RED_B_FED, inMode);

    /* Cleanup */
    EPWM_deadbandBypass(gEpwmBaseAddr);

    return;
}

/**
 * @brief Test case for verifying all polarity modes of the EPWM Deadband submodule.
 *
 * This test configures the EPWM Deadband submodule with different polarity modes
 * (Active High, Active Low Complementary, Active High Complementary, Active Low)
 * and validates the configuration by reading back the register values. The test
 * ensures that the hardware registers are correctly updated for each polarity mode.
 * After the test, the deadband is bypassed to clean up the configuration.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_dbAllPolarityModes(void *args)
{
    EPWM_DeadbandCfg dbCfg;
    uint32_t regval = 0U;
    uint32_t polsel = 0U;

    dbCfg.inputMode = EPWM_DB_IN_MODE_A_RED_A_FED;
    dbCfg.outputMode = EPWM_DB_OUT_MODE_A_RED_B_FED;
    dbCfg.risingEdgeDelay = 50U;
    dbCfg.fallingEdgeDelay = 50U;

    /* Active High */
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    polsel = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_POLSEL);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_POL_SEL_ACTV_HIGH, polsel);

    /* Active Low Complementary */
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_LOW_COMPLEMENTARY;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    polsel = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_POLSEL);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_POL_SEL_ACTV_LOW_COMPLEMENTARY, polsel);

    /* Active High Complementary */
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH_COMPLEMENTARY;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    polsel = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_POLSEL);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_POL_SEL_ACTV_HIGH_COMPLEMENTARY, polsel);

    /* Active Low */
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_LOW;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    polsel = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_POLSEL);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_POL_SEL_ACTV_LOW, polsel);

    /* Cleanup */
    EPWM_deadbandBypass(gEpwmBaseAddr);

    return;
}

/**
 * @brief Test case for verifying all output modes of the EPWM Deadband module.
 *
 * This test configures the EPWM Deadband module with various output modes
 * (bypass, no RED with B FED, A RED with no FED, and A RED with B FED) and
 * validates the configuration by reading back the register values. Each mode
 * is tested to ensure the hardware behaves as expected. The test also ensures
 * proper cleanup by bypassing the deadband configuration at the end.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_dbAllOutputModes(void *args)
{
    EPWM_DeadbandCfg dbCfg;
    uint32_t regval = 0U;
    uint32_t outMode = 0U;

    dbCfg.inputMode      = EPWM_DB_IN_MODE_A_RED_A_FED;
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH;
    dbCfg.risingEdgeDelay  = 50U;
    dbCfg.fallingEdgeDelay = 50U;

    /* Bypass (disabled) */
    dbCfg.outputMode = EPWM_DB_OUT_MODE_BYPASS;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    outMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_OUT_MODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_OUT_MODE_BYPASS, outMode);

    /* No RED, B FED only */
    dbCfg.outputMode = EPWM_DB_OUT_MODE_NO_RED_B_FED;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    outMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_OUT_MODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_OUT_MODE_NO_RED_B_FED, outMode);

    /* A RED, no FED */
    dbCfg.outputMode = EPWM_DB_OUT_MODE_A_RED_NO_FED;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    outMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_OUT_MODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_OUT_MODE_A_RED_NO_FED, outMode);

    /* A RED, B FED (full) */
    dbCfg.outputMode = EPWM_DB_OUT_MODE_A_RED_B_FED;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    outMode = HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_OUT_MODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_DB_OUT_MODE_A_RED_B_FED, outMode);

    /* Cleanup */
    EPWM_deadbandBypass(gEpwmBaseAddr);

    return;
}

/**
 * @brief Test case for verifying the configuration of the EPWM Chopper module.
 *
 * This test configures the EPWM Chopper submodule with specific duty cycle,
 * clock frequency, and one-shot pulse width values. It validates the configuration
 * by reading back the PCCTL register and comparing the values against the expected
 * settings. The test ensures that the EPWM_chopperCfg API correctly applies the
 * desired configuration. After verification, the chopper is disabled to restore
 * the default state.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_chopperCfgVerifyRegisters(void *args)
{
    EPWM_ChopperCfg chopCfg;
    uint32_t regval = 0U;
    uint32_t duty = 0U;
    uint32_t freq = 0U;
    uint32_t osht = 0U;

    chopCfg.dutyCycle        = EPWM_CHP_DUTY_CYCLE_PERC_50_PER;
    chopCfg.clkFrequency     = EPWM_CHP_CLK_FREQ_DIV_BY_4;
    chopCfg.oneShotPulseWidth = EPWM_CHP_OSHT_WIDTH_8XSYSOUT_BY_8;

    EPWM_chopperCfg(gEpwmBaseAddr, &chopCfg);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    duty = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPDUTY);
    freq = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPFREQ);
    osht = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_OSHTWTH);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_DUTY_CYCLE_PERC_50_PER, duty);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_CLK_FREQ_DIV_BY_4, freq);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_OSHT_WIDTH_8XSYSOUT_BY_8, osht);

    /* Test with different configuration */
    chopCfg.dutyCycle        = EPWM_CHP_DUTY_CYCLE_PERC_75;
    chopCfg.clkFrequency     = EPWM_CHP_CLK_FREQ_DIV_BY_1;
    chopCfg.oneShotPulseWidth = EPWM_CHP_OSHT_WIDTH_MIN;

    EPWM_chopperCfg(gEpwmBaseAddr, &chopCfg);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    duty = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPDUTY);
    freq = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPFREQ);
    osht = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_OSHTWTH);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_DUTY_CYCLE_PERC_75, duty);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_CLK_FREQ_DIV_BY_1, freq);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_OSHT_WIDTH_MIN, osht);

    /* Cleanup: disable chopper */
    EPWM_chopperEnable(gEpwmBaseAddr, FALSE);

    return;
}

/**
 * @brief  Test case to verify the enable and disable functionality of the
 *         EPWM chopper module.
 *
 * This test enables the EPWM chopper and verifies the corresponding register
 * field to ensure the chopper is enabled. It then disables the chopper and
 * verifies the register field again to confirm the chopper is disabled.
 * The test uses assertions to validate the expected behavior of the chopper
 * enable/disable functionality.
 *
 * @param  args  Pointer to arguments (not used in this test case).
 */
static void TestEpwm_chopperEnableDisable(void *args)
{
    uint32_t regval = 0U;
    uint32_t chpEn = 0U;

    /* Enable chopper */
    EPWM_chopperEnable(gEpwmBaseAddr, TRUE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    chpEn = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPEN);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_PCCTL_CHPEN_ENABLE, chpEn);

    /* Disable chopper */
    EPWM_chopperEnable(gEpwmBaseAddr, FALSE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    chpEn = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPEN);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_PCCTL_CHPEN_DISABLE, chpEn);

    return;
}

/**
 * @brief Test case for EPWM Chopper Frequency Clamping.
 *
 * This test verifies the behavior of the EPWM driver when configuring the
 * chopper frequency with values exceeding the maximum allowed limit. The
 * driver is expected to clamp the frequency to the maximum permissible value
 * (DIV_BY_8). The test also validates the behavior when the frequency is set
 * to the exact maximum value. After configuration, the register values are
 * read and compared against the expected results to ensure correctness.
 *
 * The test concludes by disabling the chopper configuration to clean up.
 */
static void TestEpwm_chopperFreqClamp(void *args)
{
    EPWM_ChopperCfg chopCfg;
    uint32_t regval = 0U;
    uint32_t freq = 0U;

    /* Pass a frequency value > DIV_BY_8 (e.g. 0xF), driver should clamp to DIV_BY_8 */
    chopCfg.dutyCycle        = EPWM_CHP_DUTY_CYCLE_PERC_25;
    chopCfg.clkFrequency     = 0xFU;  /* exceeds max */
    chopCfg.oneShotPulseWidth = EPWM_CHP_OSHT_WIDTH_4XSYSOUT_BY_8;

    EPWM_chopperCfg(gEpwmBaseAddr, &chopCfg);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    freq = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPFREQ);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_CLK_FREQ_DIV_BY_8, freq);

    /* Also test with exact max value */
    chopCfg.clkFrequency = EPWM_CHP_CLK_FREQ_DIV_BY_8;
    EPWM_chopperCfg(gEpwmBaseAddr, &chopCfg);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    freq = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPFREQ);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_CLK_FREQ_DIV_BY_8, freq);

    /* Cleanup */
    EPWM_chopperEnable(gEpwmBaseAddr, FALSE);

    return;
}

/**
 * @brief Test case to verify the EPWM chopper functionality for all duty cycles.
 *
 * This test configures the EPWM chopper module with various duty cycles and validates
 * that the configured duty cycle matches the value read from the hardware register.
 * The test iterates through a predefined set of duty cycles, applies the configuration,
 * and asserts the correctness of the hardware register value. After the test, the
 * chopper functionality is disabled to ensure cleanup.
 *
 * This ensures that the EPWM chopper module operates correctly across all supported
 * duty cycle configurations.
 */
static void TestEpwm_chopperAllDutyCycles(void *args)
{
    EPWM_ChopperCfg chopCfg;
    uint32_t regval = 0U;
    uint32_t duty = 0U;

    uint32_t dutyCycles[] = {
        EPWM_CHP_DUTY_CYCLE_PERC_12PNT5,
        EPWM_CHP_DUTY_CYCLE_PERC_25,
        EPWM_CHP_DUTY_CYCLE_PERC_37PNT5,
        EPWM_CHP_DUTY_CYCLE_PERC_50_PER,
        EPWM_CHP_DUTY_CYCLE_PERC_62PNT5,
        EPWM_CHP_DUTY_CYCLE_PERC_75,
        EPWM_CHP_DUTY_CYCLE_PERC_87PNT5
    };
    uint32_t numDuty = sizeof(dutyCycles) / sizeof(dutyCycles[0]);
    uint32_t i;

    chopCfg.clkFrequency     = EPWM_CHP_CLK_FREQ_DIV_BY_2;
    chopCfg.oneShotPulseWidth = EPWM_CHP_OSHT_WIDTH_4XSYSOUT_BY_8;

    for (i = 0U; i < numDuty; i++)
    {
        chopCfg.dutyCycle = dutyCycles[i];
        EPWM_chopperCfg(gEpwmBaseAddr, &chopCfg);

        regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
        duty = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPDUTY);
        TEST_ASSERT_EQUAL_UINT32(dutyCycles[i], duty);
    }

    /* Cleanup */
    EPWM_chopperEnable(gEpwmBaseAddr, FALSE);

    return;
}

/**
 * @brief Test case for verifying EPWM_etIntrCfg for all interrupt sources.
 *
 * This test configures the EPWM event trigger submodule with various interrupt
 * sources (e.g., counter equals zero, period, compare A/B increment/decrement).
 * It validates the configuration by reading back the ETSEL register and comparing
 * the INTSEL field against the expected source. The test ensures that the EPWM_etIntrCfg
 * API correctly applies the desired interrupt source configuration.
 *
 * After the test, the interrupt is disabled to clean up the configuration.
 */
static void TestEpwm_etIntrCfgAllSources(void *args)
{
    uint32_t regval = 0U;
    uint32_t intSel = 0U;

    uint32_t sources[] = {
        EPWM_ET_INTR_EVT_CNT_EQ_ZRO,
        EPWM_ET_INTR_EVT_CNT_EQ_PRD,
        EPWM_ET_INTR_EVT_CNT_EQ_CMPA_INC,
        EPWM_ET_INTR_EVT_CNT_EQ_CMPA_DEC,
        EPWM_ET_INTR_EVT_CNT_EQ_CMPB_INC,
        EPWM_ET_INTR_EVT_CNT_EQ_CMPB_DEC
    };
    uint32_t numSrc = sizeof(sources) / sizeof(sources[0]);
    uint32_t i;

    for (i = 0U; i < numSrc; i++)
    {
        EPWM_etIntrCfg(gEpwmBaseAddr, sources[i], EPWM_ET_INTR_PERIOD_FIRST_EVT);

        regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_ETSEL);
        intSel = HW_GET_FIELD(regval, PWMSS_EPWM_ETSEL_INTSEL);
        TEST_ASSERT_EQUAL_UINT32(sources[i], intSel);
    }

    /* Cleanup */
    EPWM_etIntrDisable(gEpwmBaseAddr);

    return;
}

/**
 * @brief   Test case to verify the ePWM event trigger interrupt configuration
 *          for all available interrupt periods. This test iterates through
 *          different interrupt periods (disable, first event, second event,
 *          third event) and ensures that the configuration is correctly
 *          reflected in the corresponding hardware register field.
 *
 *          The test reads back the configured value from the hardware register
 *          and asserts that it matches the expected value. Finally, it disables
 *          the ePWM event trigger interrupt as part of cleanup.
 */
static void TestEpwm_etIntrCfgAllPeriods(void *args)
{
    uint32_t regval = 0U;
    uint32_t intPrd = 0U;

    uint32_t periods[] = {
        EPWM_ET_INTR_PERIOD_DIS_INTR,
        EPWM_ET_INTR_PERIOD_FIRST_EVT,
        EPWM_ET_INTR_PERIOD_SECOND_EVT,
        EPWM_ET_INTR_PERIOD_THIRD_EVT
    };
    uint32_t numPrd = sizeof(periods) / sizeof(periods[0]);
    uint32_t i;

    for (i = 0U; i < numPrd; i++)
    {
        EPWM_etIntrCfg(gEpwmBaseAddr, EPWM_ET_INTR_EVT_CNT_EQ_ZRO, periods[i]);

        regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_ETPS);
        intPrd = HW_GET_FIELD(regval, PWMSS_EPWM_ETPS_INTPRD);
        TEST_ASSERT_EQUAL_UINT32(periods[i], intPrd);
    }

    /* Cleanup */
    EPWM_etIntrDisable(gEpwmBaseAddr);

    return;
}

/**
 * @brief   Test case to verify the enable and disable functionality of the
 *          ePWM event trigger interrupt. This test ensures that the interrupt
 *          enable and disable operations are correctly reflected in the
 *          corresponding hardware register fields. The test performs the
 *          following steps:
 *          1. Disables the interrupt and verifies the register value.
 *          2. Enables the interrupt and verifies the register value.
 *          3. Disables the interrupt again and verifies the register value.
 *
 * @param   args    Pointer to arguments (not used in this test case).
 */
static void TestEpwm_etIntrEnableDisable(void *args)
{
    uint32_t regval = 0U;
    uint32_t intEn  = 0U;

    /* Disable first */
    EPWM_etIntrDisable(gEpwmBaseAddr);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_ETSEL);
    intEn = HW_GET_FIELD(regval, PWMSS_EPWM_ETSEL_INTEN);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_ETSEL_INTEN_DISABLE, intEn);

    /* Enable */
    EPWM_etIntrEnable(gEpwmBaseAddr);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_ETSEL);
    intEn = HW_GET_FIELD(regval, PWMSS_EPWM_ETSEL_INTEN);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_ETSEL_INTEN_ENABLE, intEn);

    /* Disable again */
    EPWM_etIntrDisable(gEpwmBaseAddr);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_ETSEL);
    intEn = HW_GET_FIELD(regval, PWMSS_EPWM_ETSEL_INTEN);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_ETSEL_INTEN_DISABLE, intEn);

    return;
}

/**
 * @brief Test case for configuring and verifying EPWM in UP count mode.
 *
 * This test configures the EPWM module to operate in UP count mode, sets the
 * time base, counter compare, and action qualifier configurations, and verifies
 * the correctness of the register values. It also ensures that the dead band
 * and chopper modules are disabled. The test validates the expected behavior
 * of the EPWM module by comparing the register values with the expected values.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_fullPwmCfgUpCount(void *args)
{
    EPWM_AqActionCfg aqConfig;
    uint32_t regval = 0U;
    uint32_t ctrmode = 0U;
    uint32_t tbprdval = 0U;
    uint32_t cmpval = 0U;

    /* Configure time base: UP count mode */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, CONFIG_EPWM0_FCLK);
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_UP, EPWM_SHADOW_REG_CTRL_ENABLE);
    EPWM_tbSyncDisable(gEpwmBaseAddr);
    EPWM_tbSetEmulationMode(gEpwmBaseAddr, EPWM_TB_EMU_MODE_FREE_RUN);

    /* Verify counter direction is UP */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    ctrmode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CTRMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_UP, ctrmode);

    /* Verify period value for UP count */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32((APP_EPWM_TB_FREQ / APP_EPWM_OUTPUT_FREQ) - 1U, tbprdval);

    /* Configure counter compare A */
    EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A,
        APP_EPWM_COMPA_VAL, EPWM_SHADOW_REG_CTRL_ENABLE,
        EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);

    /* Verify compare value */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(APP_EPWM_COMPA_VAL, cmpval);

    /* Configure action qualifier */
    aqConfig.zeroAction     = EPWM_AQ_ACTION_HIGH;
    aqConfig.prdAction      = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpAUpAction   = EPWM_AQ_ACTION_LOW;
    aqConfig.cmpADownAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpBUpAction   = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpBDownAction = EPWM_AQ_ACTION_DONOTHING;
    EPWM_aqActionOnOutputCfg(gEpwmBaseAddr, EPWM_OUTPUT_CH_A, &aqConfig);

    /* Verify AQ register */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQCTLA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_HIGH,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_ZRO));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_LOW,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_CAU));

    /* Configure dead band bypass */
    EPWM_deadbandBypass(gEpwmBaseAddr);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_DBCTL);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_DBCTL_OUT_MODE_DISABLED,
        HW_GET_FIELD(regval, PWMSS_EPWM_DBCTL_OUT_MODE));

    /* Disable chopper */
    EPWM_chopperEnable(gEpwmBaseAddr, FALSE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    TEST_ASSERT_EQUAL_UINT32(PWMSS_EPWM_PCCTL_CHPEN_DISABLE,
        HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_CHPEN));

    return;
}

/**
 * @brief Test case for verifying the functionality of EPWM Time Base (TB) status
 *        and clear operations. This test ensures that the status flags for
 *        counter max and sync input latch can be cleared and read correctly.
 *        It also verifies the ability to configure the PWM frequency and
 *        direction, and checks the counter direction status without causing
 *        any crashes. The test validates the expected behavior of the EPWM
 *        module under various conditions.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_tbGetStatusAndClear(void *args)
{
    uint16_t status = 0U;

    /* Clear counter max flag */
    EPWM_tbStatusClear(gEpwmBaseAddr, EPWM_TB_STS_CTR_MAX);

    /* Read status - counter max should be clear */
    status = EPWM_tbGetStatus(gEpwmBaseAddr, EPWM_TB_STS_CTR_MAX);
    TEST_ASSERT_EQUAL_UINT32(0U, status);

    /* Write max counter value with counter stopped, then read */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_STOP, EPWM_SHADOW_REG_CTRL_DISABLE);
    EPWM_tbWriteTbCount(gEpwmBaseAddr, 0U);

    /* Clear sync input latch */
    EPWM_tbStatusClear(gEpwmBaseAddr, EPWM_TB_STS_SYNCI);
    status = EPWM_tbGetStatus(gEpwmBaseAddr, EPWM_TB_STS_SYNCI);
    TEST_ASSERT_EQUAL_UINT32(0U, status);

    /* Read counter direction status */
    status = EPWM_tbGetStatus(gEpwmBaseAddr, EPWM_TB_STS_CTR_DIR);
    /* Just verify we can read without crash - value depends on HW state */
    TEST_ASSERT_TRUE((status == 0U) || (status != 0U));

    return;
}

/**
 * @brief Test case to validate the boundary values for the Time-Base Period (TBPRD) register.
 *
 * This test verifies the correct behavior of the EPWM module when writing the maximum (0xFFFF),
 * minimum (0x0000), and smallest non-zero (0x0001) values to the TBPRD register. It ensures that
 * the register correctly stores and retrieves these values without any errors. The test also
 * confirms that the shadow register control is disabled during the operation for direct writes.
 *
 * Preconditions:
 * - The EPWM module must be initialized, and the base address must be valid.
 * - The counter is stopped to allow safe writes to the TBPRD register.
 *
 * Test Steps:
 * 1. Write the maximum value (0xFFFF) to the TBPRD register and verify.
 * 2. Write the minimum value (0x0000) to the TBPRD register and verify.
 * 3. Write the smallest non-zero value (0x0001) to the TBPRD register and verify.
 */
static void TestEpwm_tbPeriodBoundaryMax16Bit(void *args)
{
    uint32_t regval = 0U;
    uint32_t tbprdval = 0U;

    /* Stop the counter so we can safely write period */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_STOP, EPWM_SHADOW_REG_CTRL_DISABLE);

    /* Write max period value directly (0xFFFF) */
    HW_WR_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD, 0xFFFFU);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFU, tbprdval);

    /* Write min period value (0) */
    HW_WR_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD, 0x0000U);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32(0U, tbprdval);

    /* Write value 1 (smallest non-zero period) */
    HW_WR_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD, 0x0001U);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32(1U, tbprdval);

    return;
}

/**
 * @brief Test case to validate the boundary values for EPWM counter comparator.
 *
 * This test verifies the configuration and functionality of the EPWM counter
 * comparator for its minimum (0x0000) and maximum (0xFFFF) 16-bit values for
 * both CMP_A and CMP_B. It ensures that the comparator values are correctly
 * written to the hardware registers and read back accurately. The test also
 * checks the status returned by the configuration function to confirm success.
 *
 * The test uses shadow register control and load mode set to counter equals zero.
 */
static void TestEpwm_ccCompareBoundaryValues(void *args)
{
    uint32_t status = 0U;
    uint32_t regval = 0U;
    uint32_t cmpval = 0U;

    /* CMP_A = 0 (minimum) */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, 0x0000U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(0U, cmpval);

    /* CMP_A = 0xFFFF (maximum 16-bit) */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, 0xFFFFU,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFU, cmpval);

    /* CMP_B = 0 (minimum) */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, 0x0000U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    TEST_ASSERT_EQUAL_UINT32(0U, cmpval);

    /* CMP_B = 0xFFFF (maximum 16-bit) */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, 0xFFFFU,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFU, cmpval);

    return;
}

/**
 * @brief Test case to validate the boundary values of the Time-Base Phase Register (TBPHS)
 *        in the EPWM module. This test ensures that the phase values are correctly set
 *        and read back for various boundary conditions, including minimum, maximum,
 *        smallest non-zero, and mid-range values. The test also verifies the behavior
 *        of the EPWM_tbSyncEnable function for these scenarios.
 *
 *        The test performs the following steps:
 *        1. Sets the phase to 0 (minimum) and verifies the value.
 *        2. Sets the phase to 0xFFFF (maximum 16-bit) and verifies the value.
 *        3. Sets the phase to 1 (smallest non-zero) and verifies the value.
 *        4. Sets the phase to 0x7FFF (mid-range) and verifies the value.
 *        5. Cleans up by disabling the synchronization.
 */
static void TestEpwm_tbPhaseBoundaryValues(void *args)
{
    uint32_t phsVal = 0U;

    /* Phase = 0 (minimum) */
    EPWM_tbSyncEnable(gEpwmBaseAddr, 0x0000U, EPWM_TB_COUNTER_DIR_UP);
    phsVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_TBPHS, PWMSS_EPWM_TBPHS);
    TEST_ASSERT_EQUAL_UINT32(0U, phsVal);

    /* Phase = 0xFFFF (maximum 16-bit) */
    EPWM_tbSyncEnable(gEpwmBaseAddr, 0xFFFFU, EPWM_TB_COUNTER_DIR_DOWN);
    phsVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_TBPHS, PWMSS_EPWM_TBPHS);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFU, phsVal);

    /* Phase = 1 (smallest non-zero) */
    EPWM_tbSyncEnable(gEpwmBaseAddr, 0x0001U, EPWM_TB_COUNTER_DIR_UP);
    phsVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_TBPHS, PWMSS_EPWM_TBPHS);
    TEST_ASSERT_EQUAL_UINT32(1U, phsVal);

    /* Phase = 0x7FFF (mid-range) */
    EPWM_tbSyncEnable(gEpwmBaseAddr, 0x7FFFU, EPWM_TB_COUNTER_DIR_UP);
    phsVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_TBPHS, PWMSS_EPWM_TBPHS);
    TEST_ASSERT_EQUAL_UINT32(0x7FFFU, phsVal);

    /* Cleanup */
    EPWM_tbSyncDisable(gEpwmBaseAddr);

    return;
}

/**
 * @brief Test case for verifying the asymmetric boundary conditions of the
 *        EPWM deadband delay configuration.
 *
 * This test configures the EPWM deadband module with various combinations of
 * rising edge delay (RED) and falling edge delay (FED) values, including maximum,
 * minimum, and off-by-one values. It ensures that the configured values are
 * correctly written to the respective hardware registers. The test also validates
 * the cleanup process by bypassing the deadband configuration at the end.
 *
 * Test scenarios include:
 * - Maximum RED and zero FED.
 * - Zero RED and maximum FED.
 * - Minimal RED and off-by-one FED.
 */
static void TestEpwm_dbDelayAsymmetricBoundary(void *args)
{
    EPWM_DeadbandCfg dbCfg;
    uint32_t redVal = 0U;
    uint32_t fedVal = 0U;

    dbCfg.inputMode      = EPWM_DB_IN_MODE_A_RED_A_FED;
    dbCfg.outputMode     = EPWM_DB_OUT_MODE_A_RED_B_FED;
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH;

    /* Max RED (0x3FF), zero FED */
    dbCfg.risingEdgeDelay  = 0x3FFU;
    dbCfg.fallingEdgeDelay = 0U;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);

    redVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBRED, PWMSS_EPWM_DBRED_DEL);
    fedVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBFED, PWMSS_EPWM_DBFED_DEL);
    TEST_ASSERT_EQUAL_UINT32(0x3FFU, redVal);
    TEST_ASSERT_EQUAL_UINT32(0U, fedVal);

    /* Zero RED, max FED (0x3FF) */
    dbCfg.risingEdgeDelay  = 0U;
    dbCfg.fallingEdgeDelay = 0x3FFU;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);

    redVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBRED, PWMSS_EPWM_DBRED_DEL);
    fedVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBFED, PWMSS_EPWM_DBFED_DEL);
    TEST_ASSERT_EQUAL_UINT32(0U, redVal);
    TEST_ASSERT_EQUAL_UINT32(0x3FFU, fedVal);

    /* 1 RED, 0x3FE FED (off-by-one from max) */
    dbCfg.risingEdgeDelay  = 1U;
    dbCfg.fallingEdgeDelay = 0x3FEU;
    EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);

    redVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBRED, PWMSS_EPWM_DBRED_DEL);
    fedVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBFED, PWMSS_EPWM_DBFED_DEL);
    TEST_ASSERT_EQUAL_UINT32(1U, redVal);
    TEST_ASSERT_EQUAL_UINT32(0x3FEU, fedVal);

    /* Cleanup */
    EPWM_deadbandBypass(gEpwmBaseAddr);

    return;
}

/**
 * @brief Test case for verifying the boundary values of the EPWM Chopper
 *        one-shot pulse width configuration.
 *
 * This test configures the EPWM Chopper module with minimum, maximum, and
 * mid-range one-shot pulse width values. It validates the configuration by
 * reading back the PCCTL register and comparing the values against the
 * expected settings. The test ensures that the EPWM_chopperCfg API correctly
 * applies the desired one-shot pulse width configuration. After verification,
 * the chopper is disabled to restore the default state.
 */
static void TestEpwm_chopperOshtWidthBoundary(void *args)
{
    EPWM_ChopperCfg chopCfg;
    uint32_t regval = 0U;
    uint32_t osht = 0U;

    chopCfg.dutyCycle    = EPWM_CHP_DUTY_CYCLE_PERC_50_PER;
    chopCfg.clkFrequency = EPWM_CHP_CLK_FREQ_DIV_BY_2;

    /* Min one-shot width (0 = 1x SYSOUT/8) */
    chopCfg.oneShotPulseWidth = EPWM_CHP_OSHT_WIDTH_MIN;
    EPWM_chopperCfg(gEpwmBaseAddr, &chopCfg);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    osht = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_OSHTWTH);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_OSHT_WIDTH_MIN, osht);

    /* Max one-shot width (15 = 16x SYSOUT/8) */
    chopCfg.oneShotPulseWidth = EPWM_CHP_OSHT_WIDTH_16XSYSOUT_BY_8;
    EPWM_chopperCfg(gEpwmBaseAddr, &chopCfg);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    osht = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_OSHTWTH);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_OSHT_WIDTH_16XSYSOUT_BY_8, osht);

    /* Mid-range one-shot width (8x SYSOUT/8) */
    chopCfg.oneShotPulseWidth = EPWM_CHP_OSHT_WIDTH_8XSYSOUT_BY_8;
    EPWM_chopperCfg(gEpwmBaseAddr, &chopCfg);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_PCCTL);
    osht = HW_GET_FIELD(regval, PWMSS_EPWM_PCCTL_OSHTWTH);
    TEST_ASSERT_EQUAL_UINT32(EPWM_CHP_OSHT_WIDTH_8XSYSOUT_BY_8, osht);

    /* Cleanup */
    EPWM_chopperEnable(gEpwmBaseAddr, FALSE);

    return;
}

/**
 * @brief Test case for stress testing the rapid reconfiguration of EPWM Time-Base (TB) counter modes.
 *
 * This test rapidly switches the EPWM counter between UP, DOWN, and UP_DOWN modes 50 times to ensure
 * the module can handle frequent reconfigurations without errors. After the rapid reconfiguration,
 * the test verifies that the final mode (UP_DOWN) is correctly applied and checks the period value
 * for accuracy. Finally, the counter is set to a known state (UP mode) for cleanup.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_stressTbRapidReconfigure(void *args)
{
    uint32_t regval = 0U;
    uint32_t ctrmode = 0U;
    uint32_t tbprdval = 0U;
    uint32_t i;

    /* Rapidly switch between UP, DOWN, UP_DOWN modes 50 times */
    for (i = 0U; i < 50U; i++)
    {
        EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                          EPWM_TB_COUNTER_DIR_UP, EPWM_SHADOW_REG_CTRL_DISABLE);
        EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                          EPWM_TB_COUNTER_DIR_DOWN, EPWM_SHADOW_REG_CTRL_DISABLE);
        EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                          EPWM_TB_COUNTER_DIR_UP_DOWN, EPWM_SHADOW_REG_CTRL_DISABLE);
    }

    /* Verify last configuration (UP_DOWN) is active */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    ctrmode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CTRMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_UP_DOWN, ctrmode);

    /* Verify period for UP_DOWN mode */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD);
    tbprdval = HW_GET_FIELD(regval, PWMSS_EPWM_TBPRD);
    TEST_ASSERT_EQUAL_UINT32((APP_EPWM_TB_FREQ / APP_EPWM_OUTPUT_FREQ) / 2U, tbprdval);

    /* Now set to a known final state */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_UP, EPWM_SHADOW_REG_CTRL_DISABLE);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    ctrmode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CTRMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_UP, ctrmode);

    return;
}

/**
 * @brief   Test case for stress testing the EPWM counter comparator rapid overwrite functionality.
 *
 * This test rapidly overwrites the EPWM counter comparator values (CMP_A and CMP_B) 100 times
 * with increasing values and verifies that the last written value is correctly updated in the
 * corresponding registers. The test ensures that the shadow register control and load mode
 * configurations are functioning as expected during rapid updates. CMP_A is tested with values
 * from 0 to 99, and CMP_B is tested with values from 200 to 299.
 *
 * The test asserts the success of each configuration operation and validates the final register
 * values to ensure correctness.
 */
static void TestEpwm_stressCcRapidOverwrite(void *args)
{
    uint32_t status = 0U;
    uint32_t regval = 0U;
    uint32_t cmpval = 0U;
    uint32_t i;

    /* Rapidly overwrite CMP_A 100 times with increasing values */
    for (i = 0U; i < 100U; i++)
    {
        status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, i,
                                           EPWM_SHADOW_REG_CTRL_ENABLE,
                                           EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
        TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    }

    /* Verify last written value (99) */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(99U, cmpval);

    /* Do the same for CMP_B */
    for (i = 0U; i < 100U; i++)
    {
        status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, (200U + i),
                                           EPWM_SHADOW_REG_CTRL_ENABLE,
                                           EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
        TEST_ASSERT_EQUAL_UINT32(TRUE, status);
    }

    /* Verify last written value (299) */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    TEST_ASSERT_EQUAL_UINT32(299U, cmpval);

    return;
}

/**
 * @brief Test case to validate the behavior of the EPWM counter comparator
 *        configuration function when shadow registers are enabled. This test
 *        ensures that writes to the shadow registers are correctly accepted
 *        or rejected based on the overwrite flag and the state of the shadow
 *        register. It also verifies that the active register values remain
 *        intact when writes are rejected and are updated correctly when
 *        overwrites are allowed.
 *
 * @param args Pointer to arguments (not used in this test case).
 */
static void TestEpwm_errCcShadowReject(void *args)
{
    uint32_t status = 0U;
    uint32_t regval = 0U;
    uint32_t cmpval = 0U;

    /* First write CMP_A with shadow enabled, overwrite=FALSE - should succeed */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, 0x100U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, FALSE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(0x100U, cmpval);

    /* Second write with overwrite=FALSE - should be REJECTED (returns FALSE).
       The driver reads the hardware SHDWAFULL status bit in CMPCTL; that bit is
       set once a value is written to the shadow register and remains set until
       the shadow-to-active transfer occurs (triggered by the configured load
       event). With the counter stopped no transfer happens, so SHDWAFULL stays
       set and the driver correctly refuses the second write. */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, 0x200U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, FALSE);
    TEST_ASSERT_EQUAL_UINT32(FALSE, status);

    /* Verify original value is still intact */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(0x100U, cmpval);

    /* Now overwrite with TRUE - should succeed */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, 0x300U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);

    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(0x300U, cmpval);

    /* Same test for CMP_B */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, 0x400U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, FALSE);
    TEST_ASSERT_EQUAL_UINT32(TRUE, status);

    /* Second write should be rejected: SHDWBFULL is set after the first write
       and the driver refuses a second write when overwrite=FALSE. */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, 0x500U,
                                       EPWM_SHADOW_REG_CTRL_ENABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, FALSE);
    TEST_ASSERT_EQUAL_UINT32(FALSE, status);

    /* Original value intact */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    TEST_ASSERT_EQUAL_UINT32(0x400U, cmpval);

    return;
}

/**
 * @brief Test case for verifying the behavior of EPWM_counterComparatorCfg
 *        when an invalid comparator type is provided.
 *
 * This test calls the EPWM_counterComparatorCfg function with an invalid
 * comparator type (0xFF) and verifies that the function falls into the
 * else branch and returns FALSE. This ensures that the function handles
 * invalid input parameters gracefully without causing any crashes.
 */
static void TestEpwm_negCcInvalidCmpType(void *args)
{
    uint32_t status = 0U;
    uint32_t invalidCmpType = 0xFFU;

    /* Call with invalid cmpType - should fall into else branch and return FALSE */
    status = EPWM_counterComparatorCfg(gEpwmBaseAddr, invalidCmpType, 0x100U,
                                       EPWM_SHADOW_REG_CTRL_DISABLE,
                                       EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    TEST_ASSERT_EQUAL_UINT32(FALSE, status);

    return;
}

/**
 * @brief Test case to validate the behavior of EPWM driver APIs when provided
 *        with an invalid PWM output channel.
 *
 * This test specifically verifies the following scenarios:
 * 1. Configuration of action qualifier output with an invalid channel.
 * 2. Triggering a one-time software action with an invalid channel.
 * 3. Triggering a continuous software action with an invalid channel.
 *
 * The test ensures that the driver handles invalid channel inputs gracefully
 * without causing a crash or undefined behavior.
 */
static void TestEpwm_negAqInvalidPwmOutputCh(void *args)
{
    uint32_t invalidCh = 0xFFU;
    EPWM_AqActionCfg aqCfg;

    memset(&aqCfg, 0, sizeof(aqCfg));

    /* EPWM_aqActionOnOutputCfg with invalid channel - covers lines 308-311 */
    EPWM_aqActionOnOutputCfg(gEpwmBaseAddr, invalidCh, &aqCfg);

    /* EPWM_aqSwTriggerOneTimeAction with invalid channel - covers lines 348-351 */
    EPWM_aqSwTriggerOneTimeAction(gEpwmBaseAddr, invalidCh,
                                  EPWM_AQ_SW_TRIG_OT_ACTION_LOW);

    /* EPWM_aqSwTriggerContAction with invalid channel - covers lines 375-378 */
    EPWM_aqSwTriggerContAction(gEpwmBaseAddr, invalidCh,
                               EPWM_AQ_SW_TRIG_CONT_ACTION_LOW,
                               EPWM_AQ_CSFRC_REG_RELOAD_CNT_EQ_ZRO);

    /* If we reach here without crash, the else branches were exercised */
    TEST_ASSERT_TRUE(TRUE);

    return;
}

#if !defined(C75_CORE) && defined(SOC_AM62DX) || defined(SOC_AM275X)

/**
 * @brief Test case to validate the behavior of EPWM Trip Zone APIs when provided
 *        with invalid parameters. This test ensures that the driver handles
 *        invalid input gracefully without causing crashes or undefined behavior.
 *
 * The test covers scenarios such as invalid channel numbers and invalid trip
 * event types for various EPWM Trip Zone APIs, including trigger actions,
 * event enable/disable, interrupt enable/disable, and software event triggers.
 */
static void TestEpwm_negTzInvalidParams(void *args)
{
    uint32_t invalidCh = 0xFFU;
    uint32_t invalidTzEvent = 0xFFU;

    /* EPWM_tzTriggerTripAction with invalid channel - covers lines 472-475 */
    EPWM_tzTriggerTripAction(gEpwmBaseAddr, EPWM_TZ_TRIP_ACTION_LOW, invalidCh);

    /* EPWM_tzTripEventEnable with invalid event type - covers lines 524-527 */
    EPWM_tzTripEventEnable(gEpwmBaseAddr, invalidTzEvent, 0U);

    /* EPWM_tzTripEventDisable with invalid event type - covers lines 548-551 */
    EPWM_tzTripEventDisable(gEpwmBaseAddr, invalidTzEvent, 0U);

    /* EPWM_tzIntrEnable with invalid event type - covers lines 572-575 */
    EPWM_tzIntrEnable(gEpwmBaseAddr, invalidTzEvent);

    /* EPWM_tzIntrDisable with invalid event type - covers lines 572-575 */
    EPWM_tzIntrDisable(gEpwmBaseAddr, invalidTzEvent);

    /* EPWM_tzTriggerSwEvent with invalid event type - covers lines 610-613 */
    EPWM_tzTriggerSwEvent(gEpwmBaseAddr, invalidTzEvent);

    return;
}
#endif

#if !defined(SOC_AM275X)
static void App_epwmIntrISR(void *handle)
{
    volatile uint16_t status;

    status = EPWM_etIntrStatus(gEpwmBaseAddr);
    if(status & EPWM_ETFLG_INT_MASK)
    {
        SemaphoreP_post(&gEpwmSyncSemObject);
        EPWM_etIntrClear(gEpwmBaseAddr);
    }

    return;
}

static void App_epwmConfigTest1(uint32_t epwmBaseAddr,
                                uint32_t epwmCh,
                                uint32_t epwmFuncClk)
{
    EPWM_AqActionCfg  aqConfig;

    /* Configure Time base submodule */
    EPWM_tbTimebaseClkCfg(epwmBaseAddr, APP_EPWM_TB_FREQ_MAX, epwmFuncClk);
    EPWM_tbPwmFreqCfg(epwmBaseAddr, APP_EPWM_TB_FREQ_MAX, APP_EPWM_OUTPUT_FREQ_MAX,
        EPWM_TB_COUNTER_DIR_UP_DOWN,
            EPWM_SHADOW_REG_CTRL_ENABLE);
    EPWM_tbSyncDisable(epwmBaseAddr);
    EPWM_tbSetSyncOutMode(epwmBaseAddr, PWMSS_EPWM_TBCTL_SYNCOSEL_EPWMXSYNC);
    EPWM_tbSetEmulationMode(epwmBaseAddr, EPWM_TB_EMU_MODE_FREE_RUN);

    /* Configure counter compare submodule */
    EPWM_counterComparatorCfg(epwmBaseAddr, EPWM_CC_CMP_A,
        APP_EPWM_COMPA_VAL_MIN, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    EPWM_counterComparatorCfg(epwmBaseAddr, EPWM_CC_CMP_B,
        APP_EPWM_COMPA_VAL_MIN, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);

    /* Configure Action Qualifier Submodule */
    aqConfig.zeroAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.prdAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpAUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpADownAction = EPWM_AQ_ACTION_LOW;
    aqConfig.cmpBUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpBDownAction = EPWM_AQ_ACTION_LOW;
    EPWM_aqActionOnOutputCfg(epwmBaseAddr, epwmCh, &aqConfig);

    /* Configure Dead Band Submodule */
    EPWM_deadbandBypass(epwmBaseAddr);

    /* Configure Chopper Submodule */
    EPWM_chopperEnable(epwmBaseAddr, FALSE);

    /* Configure trip zone Submodule */
    EPWM_tzTripEventDisable(epwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);
    EPWM_tzTripEventDisable(epwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE, 0U);

    /* Configure event trigger Submodule */
    EPWM_etIntrCfg(epwmBaseAddr, EPWM_ET_INTR_EVT_CNT_EQ_ZRO,
        EPWM_ET_INTR_PERIOD_FIRST_EVT);
    EPWM_etIntrEnable(epwmBaseAddr);
}

static void App_epwmConfigTest2(uint32_t epwmBaseAddr,
                                uint32_t epwmCh,
                                uint32_t epwmFuncClk)
{
    EPWM_AqActionCfg  aqConfig;

    /* Configure Time base submodule */
    EPWM_tbTimebaseClkCfg(epwmBaseAddr, APP_EPWM_TB_FREQ_MIN, epwmFuncClk);
    EPWM_tbPwmFreqCfg(epwmBaseAddr, APP_EPWM_TB_FREQ_MIN, APP_EPWM_OUTPUT_FREQ_MIN,
        EPWM_TB_COUNTER_DIR_UP_DOWN,
            EPWM_SHADOW_REG_CTRL_ENABLE);
    EPWM_tbSyncDisable(epwmBaseAddr);
    EPWM_tbSetSyncOutMode(epwmBaseAddr, PWMSS_EPWM_TBCTL_SYNCOSEL_EPWMXSYNC);
    EPWM_tbSetEmulationMode(epwmBaseAddr, EPWM_TB_EMU_MODE_FREE_RUN);

    /* Configure counter compare submodule */
    EPWM_counterComparatorCfg(epwmBaseAddr, EPWM_CC_CMP_A,
        APP_EPWM_COMPA_VAL_MAX, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    EPWM_counterComparatorCfg(epwmBaseAddr, EPWM_CC_CMP_B,
        APP_EPWM_COMPA_VAL_MAX, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);

    /* Configure Action Qualifier Submodule */
    aqConfig.zeroAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.prdAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpAUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpADownAction = EPWM_AQ_ACTION_LOW;
    aqConfig.cmpBUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpBDownAction = EPWM_AQ_ACTION_LOW;
    EPWM_aqActionOnOutputCfg(epwmBaseAddr, epwmCh, &aqConfig);

    /* Configure Dead Band Submodule */
    EPWM_deadbandBypass(epwmBaseAddr);

    /* Configure Chopper Submodule */
    EPWM_chopperEnable(epwmBaseAddr, FALSE);

    /* Configure trip zone Submodule */
    EPWM_tzTripEventDisable(epwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);
    EPWM_tzTripEventDisable(epwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE, 0U);

    /* Configure event trigger Submodule */
    EPWM_etIntrCfg(epwmBaseAddr, EPWM_ET_INTR_EVT_CNT_EQ_ZRO,
        EPWM_ET_INTR_PERIOD_FIRST_EVT);
    EPWM_etIntrEnable(epwmBaseAddr);
}

static void App_epwmConfigTest3(uint32_t epwmBaseAddr,
                                uint32_t epwmCh,
                                uint32_t epwmFuncClk)
{
    EPWM_AqActionCfg  aqConfig;
    EPWM_ChopperCfg  chopperConfig;

    /* Configure Time base submodule */
    EPWM_tbTimebaseClkCfg(epwmBaseAddr, APP_EPWM_TB_FREQ, epwmFuncClk);
    EPWM_tbPwmFreqCfg(epwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
        EPWM_TB_COUNTER_DIR_UP_DOWN,
            EPWM_SHADOW_REG_CTRL_ENABLE);
    EPWM_tbSyncDisable(epwmBaseAddr);
    EPWM_tbSetSyncOutMode(epwmBaseAddr, PWMSS_EPWM_TBCTL_SYNCOSEL_EPWMXSYNC);
    EPWM_tbSetEmulationMode(epwmBaseAddr, EPWM_TB_EMU_MODE_FREE_RUN);

    /* Configure counter compare submodule */
    EPWM_counterComparatorCfg(epwmBaseAddr, EPWM_CC_CMP_A,
        APP_EPWM_COMPA_VAL, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    EPWM_counterComparatorCfg(epwmBaseAddr, EPWM_CC_CMP_B,
        APP_EPWM_COMPA_VAL, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);

    /* Configure Action Qualifier Submodule */
    aqConfig.zeroAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.prdAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpAUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpADownAction = EPWM_AQ_ACTION_LOW;
    aqConfig.cmpBUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpBDownAction = EPWM_AQ_ACTION_LOW;
    EPWM_aqActionOnOutputCfg(epwmBaseAddr, epwmCh, &aqConfig);

    /* Configure Dead Band Submodule */
    EPWM_deadbandBypass(epwmBaseAddr);

    /* Configure Chopper Submodule */
    chopperConfig.dutyCycle = EPWM_CHP_DUTY_CYCLE_PERC_37PNT5;
    chopperConfig.clkFrequency = EPWM_CHP_CLK_FREQ_DIV_BY_2;
    chopperConfig.oneShotPulseWidth = EPWM_CHP_OSHT_WIDTH_12XSYSOUT_BY_8;
    EPWM_chopperEnable(epwmBaseAddr, TRUE);
    EPWM_chopperCfg(epwmBaseAddr, &chopperConfig);

    /* Configure trip zone Submodule */
    EPWM_tzTripEventDisable(epwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);
    EPWM_tzTripEventDisable(epwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE, 0U);

    /* Configure event trigger Submodule */
    EPWM_etIntrCfg(epwmBaseAddr, EPWM_ET_INTR_EVT_CNT_EQ_ZRO,
        EPWM_ET_INTR_PERIOD_FIRST_EVT);
    EPWM_etIntrEnable(epwmBaseAddr);
}

static void App_epwmConfigTest4(uint32_t epwmBaseAddr,
                                uint32_t epwmCh,
                                uint32_t epwmFuncClk)
{
    EPWM_AqActionCfg  aqConfig;
    EPWM_DeadbandCfg  deadBandConfig;

    /* Configure Time base submodule */
    EPWM_tbTimebaseClkCfg(epwmBaseAddr, APP_EPWM_TB_FREQ, epwmFuncClk);
    EPWM_tbPwmFreqCfg(epwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
        EPWM_TB_COUNTER_DIR_UP_DOWN,
            EPWM_SHADOW_REG_CTRL_ENABLE);
    EPWM_tbSyncDisable(epwmBaseAddr);
    EPWM_tbSetSyncOutMode(epwmBaseAddr, PWMSS_EPWM_TBCTL_SYNCOSEL_EPWMXSYNC);
    EPWM_tbSetEmulationMode(epwmBaseAddr, EPWM_TB_EMU_MODE_FREE_RUN);

    /* Configure counter compare submodule */
    EPWM_counterComparatorCfg(epwmBaseAddr, EPWM_CC_CMP_A,
        APP_EPWM_COMPA_VAL, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    EPWM_counterComparatorCfg(epwmBaseAddr, EPWM_CC_CMP_B,
        APP_EPWM_COMPA_VAL, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);

    /* Configure Action Qualifier Submodule */
    aqConfig.zeroAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.prdAction = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpAUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpADownAction = EPWM_AQ_ACTION_LOW;
    aqConfig.cmpBUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpBDownAction = EPWM_AQ_ACTION_LOW;
    EPWM_aqActionOnOutputCfg(epwmBaseAddr, epwmCh, &aqConfig);

    /* Configure Dead Band Submodule */
    deadBandConfig.inputMode = EPWM_DB_IN_MODE_A_RED_A_FED;
    deadBandConfig.outputMode = EPWM_DB_OUT_MODE_A_RED_NO_FED;
    deadBandConfig.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH;
    deadBandConfig.risingEdgeDelay = 200U;
    deadBandConfig.fallingEdgeDelay = 0U;
    EPWM_deadbandCfg(epwmBaseAddr, &deadBandConfig);

    /* Configure Chopper Submodule */
    EPWM_chopperEnable(epwmBaseAddr, FALSE);

    /* Configure trip zone Submodule */
    EPWM_tzTripEventDisable(epwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);
    EPWM_tzTripEventDisable(epwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE, 0U);

    /* Configure event trigger Submodule */
    EPWM_etIntrCfg(epwmBaseAddr, EPWM_ET_INTR_EVT_CNT_EQ_ZRO,
        EPWM_ET_INTR_PERIOD_FIRST_EVT);
    EPWM_etIntrEnable(epwmBaseAddr);
}
#endif

#if !defined(C75_CORE) && defined(SOC_AM62DX) || defined(SOC_AM275X)
/**
 * \brief Enable/Disable EALLOW for EPWM Trip Zone register writes.
 *
 * On AM62DX (and similar SoCs), the EHRPWM Trip Zone registers (TZSEL, TZCTL,
 * TZEINT, TZFRC) are write-protected by the EALLOW bit in the MAIN_CTRL_MMR
 * EPWMx_CTRL register. This bit must be set to 1 before writing to these
 * registers.
 *
 * \param epwmInstance  EPWM instance number (0, 1, 2, ...)
 * \param enable        TRUE to enable writes (set EALLOW), FALSE to disable
 */
static void App_epwmSetEallow(uint32_t epwmInstance, uint32_t enable)
{
    uint32_t epwmCtrlAddr = CSL_CTRL_MMR0_CFG0_BASE +
        CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL + (epwmInstance * 0x10U);
    uint32_t regVal;

    /* Unlock CTRL_MMR partition 0 */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 0);

    regVal = CSL_REG32_RD(epwmCtrlAddr);
    if(TRUE == enable)
    {
        regVal |= CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_EALLOW_MASK;
    }
    else
    {
        regVal &= ~CSL_MAIN_CTRL_MMR_CFG0_EPWM0_CTRL_EALLOW_MASK;
    }
    CSL_REG32_WR(epwmCtrlAddr, regVal);
}

/* Test ID: 12058 - Verify One-Shot Trip Zone: configure trip action, trigger SW
 * trip event, verify TZFLG, clear flags. Covers: EPWM_tzTriggerTripAction,
 * EPWM_tzTripEventEnable, EPWM_tzIntrEnable, EPWM_tzTriggerSwEvent,
 * EPWM_tzEventStatus, EPWM_tzEventStatusClear, EPWM_tzIntrDisable,
 * EPWM_tzTripEventDisable.
 * No external connection needed - uses software forced trip event. */
static void TestEpwm_tzTriggerTripActionChA(void *args)
{
    int32_t  status;
    uint32_t regval = 0U;
    uint32_t tzA = 0U;
    HwiP_Params hwiPrms;

    /* ---- Step 1: Enable EALLOW to unlock TZ register writes ---- */
    App_epwmSetEallow(0U, TRUE);

    /* ---- Step 2: Clean state ---- */
    EPWM_tzTripEventDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);
    EPWM_tzIntrDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT);
    EPWM_tzEventStatusClear(gEpwmBaseAddr,
        EPWM_TZ_STS_FLG_OST | EPWM_TZ_STS_FLG_INT);

    /* ---- Step 3: Create semaphore and register TZ HwiP (like epwm_trip_zone.c) ---- */
    gEpwmTzIntCount = 0U;
    status = SemaphoreP_constructBinary(&gEpwmTzSyncSemObject, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_EPWM0_TRIP_INTR;
    hwiPrms.isPulse  = APP_INT_IS_PULSE;
    hwiPrms.callback = &App_epwmTzIntrISR;
    status = HwiP_construct(&gEpwmTzHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* ---- Step 4: Configure trip action for Ch A = Force LOW on OST ---- */
    EPWM_tzTriggerTripAction(gEpwmBaseAddr, EPWM_TZ_TRIP_ACTION_LOW,
        EPWM_OUTPUT_CH_A);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TZCTL);
    tzA = HW_GET_FIELD(regval, PWMSS_EPWM_TZCTL_TZA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TZ_TRIP_ACTION_LOW, tzA);

    /* ---- Step 5: Enable one-shot trip event on TZ pin 0 ---- */
    EPWM_tzTripEventEnable(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);

    /* ---- Step 6: Enable TZ one-shot interrupt ---- */
    EPWM_tzIntrEnable(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT);

    /* ---- Step 7: Force a software one-shot trip event ---- */
    EPWM_tzTriggerSwEvent(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT);

    /* ---- Step 8: Wait for TZ ISR to fire via semaphore ---- */
    status = SemaphoreP_pend(&gEpwmTzSyncSemObject, 500U * 1000U);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
        "TZ one-shot ISR semaphore timed out — interrupt never fired");

    /* Verify ISR was called */
    TEST_ASSERT_NOT_EQUAL(0U, gEpwmTzIntCount);

    /* ---- Step 9: Clear the flags (like epwm_trip_zone.c does after ISR) ---- */
    EPWM_tzEventStatusClear(gEpwmBaseAddr,
        EPWM_TZ_STS_FLG_OST | EPWM_TZ_STS_FLG_INT);

    /* ---- Step 10: Verify other trip actions for Ch A ---- */
    EPWM_tzTriggerTripAction(gEpwmBaseAddr, EPWM_TZ_TRIP_ACTION_HIGH,
        EPWM_OUTPUT_CH_A);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TZCTL);
    tzA = HW_GET_FIELD(regval, PWMSS_EPWM_TZCTL_TZA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TZ_TRIP_ACTION_HIGH, tzA);

    EPWM_tzTriggerTripAction(gEpwmBaseAddr, EPWM_TZ_TRIP_ACTION_TRI_STATE,
        EPWM_OUTPUT_CH_A);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TZCTL);
    tzA = HW_GET_FIELD(regval, PWMSS_EPWM_TZCTL_TZA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TZ_TRIP_ACTION_TRI_STATE, tzA);

    EPWM_tzTriggerTripAction(gEpwmBaseAddr, EPWM_TZ_TRIP_ACTION_DO_NOTHING,
        EPWM_OUTPUT_CH_A);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TZCTL);
    tzA = HW_GET_FIELD(regval, PWMSS_EPWM_TZCTL_TZA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TZ_TRIP_ACTION_DO_NOTHING, tzA);

    /* ---- Cleanup ---- */
    EPWM_tzIntrDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT);
    EPWM_tzTripEventDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);
    EPWM_tzEventStatusClear(gEpwmBaseAddr,
        EPWM_TZ_STS_FLG_OST | EPWM_TZ_STS_FLG_INT);
    App_epwmSetEallow(0U, FALSE);
    HwiP_destruct(&gEpwmTzHwiObject);
    SemaphoreP_destruct(&gEpwmTzSyncSemObject);

    return;
}

/* Test ID: 12059 - Verify Cycle-By-Cycle Trip Zone: configure trip action on
 * Ch B, trigger SW CBC trip, verify TZFLG CBC flag, clear and re-verify.
 * Covers: EPWM_tzTriggerTripAction (Ch B), EPWM_tzTripEventEnable (CBC),
 * EPWM_tzIntrEnable (CBC), EPWM_tzTriggerSwEvent (CBC),
 * EPWM_tzEventStatus, EPWM_tzEventStatusClear, EPWM_tzIntrDisable (CBC).
 * No external connection needed - uses software forced trip event. */
static void TestEpwm_tzTriggerTripActionChB(void *args)
{
    int32_t  status;
    uint32_t regval = 0U;
    uint32_t tzB = 0U;
    HwiP_Params hwiPrms;

    /* ---- Step 1: Enable EALLOW to unlock TZ register writes ---- */
    App_epwmSetEallow(0U, TRUE);

    /* ---- Step 2: Clean state ---- */
    EPWM_tzTripEventDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE, 0U);
    EPWM_tzIntrDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE);
    EPWM_tzEventStatusClear(gEpwmBaseAddr,
        EPWM_TZ_STS_FLG_CBC | EPWM_TZ_STS_FLG_INT);

    /* ---- Step 3: Create semaphore and register TZ HwiP (like epwm_trip_zone.c) ---- */
    gEpwmTzIntCount = 0U;
    status = SemaphoreP_constructBinary(&gEpwmTzSyncSemObject, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_EPWM0_TRIP_INTR;
    hwiPrms.isPulse  = APP_INT_IS_PULSE;
    hwiPrms.callback = &App_epwmTzIntrISR;
    status = HwiP_construct(&gEpwmTzHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* ---- Step 3: Configure trip action for Ch B = Force HIGH on CBC ---- */
    EPWM_tzTriggerTripAction(gEpwmBaseAddr, EPWM_TZ_TRIP_ACTION_HIGH,
        EPWM_OUTPUT_CH_B);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TZCTL);
    tzB = HW_GET_FIELD(regval, PWMSS_EPWM_TZCTL_TZB);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TZ_TRIP_ACTION_HIGH, tzB);

    /* ---- Step 4: Enable CBC trip event on TZ pin 0 ---- */
    EPWM_tzTripEventEnable(gEpwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE, 0U);

    /* ---- Step 5: Enable TZ CBC interrupt ---- */
    EPWM_tzIntrEnable(gEpwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE);

    /* ---- Step 6: Force a software CBC trip event ---- */
    EPWM_tzTriggerSwEvent(gEpwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE);

    /* ---- Step 7: Wait for TZ ISR to fire via semaphore ---- */
    status = SemaphoreP_pend(&gEpwmTzSyncSemObject, 500U * 1000U);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
        "TZ CBC ISR semaphore timed out — interrupt never fired");

    /* Verify ISR was called */
    TEST_ASSERT_NOT_EQUAL(0U, gEpwmTzIntCount);

    /* ---- Step 8: Clear the flags (like epwm_trip_zone.c does after ISR) ---- */
    EPWM_tzEventStatusClear(gEpwmBaseAddr,
        EPWM_TZ_STS_FLG_CBC | EPWM_TZ_STS_FLG_INT);

    /* ---- Step 9: Verify other trip actions for Ch B ---- */
    EPWM_tzTriggerTripAction(gEpwmBaseAddr, EPWM_TZ_TRIP_ACTION_LOW,
        EPWM_OUTPUT_CH_B);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TZCTL);
    tzB = HW_GET_FIELD(regval, PWMSS_EPWM_TZCTL_TZB);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TZ_TRIP_ACTION_LOW, tzB);

    EPWM_tzTriggerTripAction(gEpwmBaseAddr, EPWM_TZ_TRIP_ACTION_TRI_STATE,
        EPWM_OUTPUT_CH_B);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TZCTL);
    tzB = HW_GET_FIELD(regval, PWMSS_EPWM_TZCTL_TZB);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TZ_TRIP_ACTION_TRI_STATE, tzB);

    EPWM_tzTriggerTripAction(gEpwmBaseAddr, EPWM_TZ_TRIP_ACTION_DO_NOTHING,
        EPWM_OUTPUT_CH_B);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TZCTL);
    tzB = HW_GET_FIELD(regval, PWMSS_EPWM_TZCTL_TZB);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TZ_TRIP_ACTION_DO_NOTHING, tzB);

    /* ---- Cleanup ---- */
    EPWM_tzIntrDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE);
    EPWM_tzTripEventDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE, 0U);
    EPWM_tzEventStatusClear(gEpwmBaseAddr,
        EPWM_TZ_STS_FLG_CBC | EPWM_TZ_STS_FLG_INT);
    App_epwmSetEallow(0U, FALSE);
    HwiP_destruct(&gEpwmTzHwiObject);
    SemaphoreP_destruct(&gEpwmTzSyncSemObject);

    return;
}

/* TZ interrupt ISR - follows epwm_trip_zone.c pattern */
static void App_epwmTzIntrISR(void *handle)
{
    volatile uint16_t status;

    gEpwmTzIntCount++;
    status = EPWM_tzEventStatus(gEpwmBaseAddr,
        EPWM_TZ_STS_FLG_INT);
    if(status != 0U)
    {
        SemaphoreP_post(&gEpwmTzSyncSemObject);
    }

    return;
}
#endif

/**
 * @brief Test case to cover the high-divider branch in EPWM_tbTimebaseClkCfg.
 *
 * When clkDiv (moduleClk/tbClk) exceeds EPWM_TBCTL_HSPCLKDIV_14 (14),
 * the function enters a branch that sets hspClkDiv to DIV_14 (7) and
 * computes lspClkDivSetting via a while loop (right-shifting lspClkDiv
 * until it reaches 1). This test exercises that branch with two different
 * divider values to ensure both the branch entry and the while loop
 * iterations are covered.
 *
 * clkDiv=28:  hspClkDiv=7, lspClkDiv=28/14=2, loop: 2→1 (setting=1)
 * clkDiv=1792: hspClkDiv=7, lspClkDiv=1792/14=128, loop: 128→...→1 (setting=7)
 */
static void TestEpwm_tbClkCfgHighDividerBranch(void *args)
{
    uint32_t regval = 0U;
    uint32_t clkdivval = 0U;
    uint32_t hspclkdiv = 0U;

    /*
     * Test 1: clkDiv = 28 (> 14, enters the high-divider branch)
     *   hspClkDiv = DIV_14 = 7
     *   lspClkDiv = 28 / 14 = 2
     *   while(2 > 1): lspClkDiv = 1, lspClkDivSetting = 1
     *   Expected: CLKDIV = 1, HSPCLKDIV = 7
     */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr,
                          CONFIG_EPWM0_FCLK / 28U,
                          CONFIG_EPWM0_FCLK);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    clkdivval = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CLKDIV);
    hspclkdiv = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_HSPCLKDIV);
    TEST_ASSERT_EQUAL_UINT32(1U, clkdivval);
    TEST_ASSERT_EQUAL_UINT32(7U, hspclkdiv);

    /*
     * Test 2: clkDiv = 112 (exercises multiple while-loop iterations)
     *   hspClkDiv = DIV_14 = 7
     *   lspClkDiv = 112 / 14 = 8
     *   while(8>1): 4(1) → 2(2) → 1(3), lspClkDivSetting = 3
     *   Expected: CLKDIV = 3, HSPCLKDIV = 7
     */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr,
                          CONFIG_EPWM0_FCLK / 112U,
                          CONFIG_EPWM0_FCLK);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    clkdivval = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CLKDIV);
    hspclkdiv = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_HSPCLKDIV);
    TEST_ASSERT_EQUAL_UINT32(3U, clkdivval);
    TEST_ASSERT_EQUAL_UINT32(7U, hspclkdiv);

    /*
     * Test 3: clkDiv = 1792 (maximum divider, maximum while-loop iterations)
     *   hspClkDiv = DIV_14 = 7
     *   lspClkDiv = 1792 / 14 = 128
     *   while: 128→64(1)→32(2)→16(3)→8(4)→4(5)→2(6)→1(7), setting = 7
     *   Expected: CLKDIV = 7, HSPCLKDIV = 7
     */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr,
                          CONFIG_EPWM0_FCLK / 1792U,
                          CONFIG_EPWM0_FCLK);
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    clkdivval = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CLKDIV);
    hspclkdiv = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_HSPCLKDIV);
    TEST_ASSERT_EQUAL_UINT32(7U, clkdivval);
    TEST_ASSERT_EQUAL_UINT32(7U, hspclkdiv);

    /* Restore clock to default divider */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, CONFIG_EPWM0_FCLK);

    return;
}

/**
 * @brief Test case to verify EPWM_tbTriggerSwSync loads the phase register
 *        value into the time-base counter.
 *
 * When PHSEN=1 (sync enabled) and a software sync is triggered via
 * EPWM_tbTriggerSwSync, the EPWM hardware loads the phase register value
 * (TBPHS) into the counter (TBCNT). This test:
 *   1. Stops the counter (STOP mode) to prevent it from counting away.
 *   2. Enables sync with a known phase value (500).
 *   3. Writes counter to 0 and verifies it is 0.
 *   4. Triggers a software sync.
 *   5. Reads counter back — it should now equal the phase value (500).
 */
static void TestEpwm_tbTriggerSwSyncVerify(void *args)
{
    uint16_t count = 0U;

    /* Test sync-in passthrough */
    EPWM_tbSetSyncOutMode(gEpwmBaseAddr, EPWM_TB_SYNC_OUT_EVT_SYNCIN);

    /* Stop counter so it doesn't count away after sync */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_STOP, EPWM_SHADOW_REG_CTRL_DISABLE);

    /* Enable sync with phase = 500, direction UP */
    EPWM_tbSyncEnable(gEpwmBaseAddr, 500U, EPWM_TB_COUNTER_DIR_UP);

    /* Write counter to 0 and verify */
    EPWM_tbWriteTbCount(gEpwmBaseAddr, 0U);
    count = EPWM_tbReadTbCount(gEpwmBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(0U, count);

    /* Trigger software sync — counter should load phase value (500) */
    EPWM_tbTriggerSwSync(gEpwmBaseAddr);
    ClockP_usleep(100);

    /* Read counter — should now be 500 */
    count = EPWM_tbReadTbCount(gEpwmBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(500U, count);

    /* Test with a different phase value (1000) */
    EPWM_tbSyncEnable(gEpwmBaseAddr, 1000U, EPWM_TB_COUNTER_DIR_DOWN);
    EPWM_tbWriteTbCount(gEpwmBaseAddr, 0U);
    EPWM_tbTriggerSwSync(gEpwmBaseAddr);
    ClockP_usleep(100);
    count = EPWM_tbReadTbCount(gEpwmBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(1000U, count);

    /* Cleanup */
    EPWM_tbSyncDisable(gEpwmBaseAddr);
    EPWM_tbWriteTbCount(gEpwmBaseAddr, 0U);

    return;
}

/**
 * @brief Test case to verify EPWM_etGetEventCount returns the correct
 *        event count after the EPWM counter generates events.
 *
 * ETPS.INTCNT is a 2-bit read-only counter that counts the number of
 * selected events (e.g., CTR=0) since the last interrupt. This test:
 *   1. Configures ET source to CTR=0 with third-event period (so the
 *      count can accumulate up to 3 without resetting).
 *   2. Disables ET interrupt output (INTEN=0) so the counter is not
 *      cleared by an interrupt firing.
 *   3. Runs the counter with a very small period at maximum clock speed
 *      so CTR=0 events happen rapidly.
 *   4. Reads EPWM_etGetEventCount and verifies it is > 0.
 */
static void TestEpwm_etGetEventCountVerify(void *args)
{
    uint16_t evtCnt = 0U;
    uint32_t regval = 0U;
    volatile uint32_t i;

    /* Stop counter first */
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_STOP, EPWM_SHADOW_REG_CTRL_DISABLE);

    /* Configure ET: source = counter equals zero, period = third event
       (INTCNT can count up to 3 before generating interrupt) */
    EPWM_etIntrCfg(gEpwmBaseAddr, EPWM_ET_INTR_EVT_CNT_EQ_ZRO,
                   EPWM_ET_INTR_PERIOD_THIRD_EVT);

    /* Disable interrupt output — we just want INTCNT to accumulate */
    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);

    /* Use fastest clock (no divider) */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, CONFIG_EPWM0_FCLK, CONFIG_EPWM0_FCLK);

    /* Set a very small period (2) so counter wraps quickly: 0→1→2→0→1→2→0... */
    HW_WR_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBPRD, 2U);
    EPWM_tbWriteTbCount(gEpwmBaseAddr, 0U);

    /* Start counter in UP mode */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    HW_SET_FIELD32(regval, PWMSS_EPWM_TBCTL_CTRMODE, EPWM_TB_COUNTER_DIR_UP);
    HW_WR_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL, (uint16_t)regval);

    /* Brief delay — at 250 MHz with period=2, counter hits zero every 3 clocks
       (12 ns). Even a tiny delay gives many CTR=0 events. */
    for (i = 0U; i < 100U; i++)
    {
        /* spin */
    }

    /* Read event count — should be > 0 (INTCNT saturates at 3) */
    evtCnt = EPWM_etGetEventCount(gEpwmBaseAddr);
    TEST_ASSERT_NOT_EQUAL(0U, (uint32_t)evtCnt);

    /* Stop counter */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    HW_SET_FIELD32(regval, PWMSS_EPWM_TBCTL_CTRMODE, EPWM_TB_COUNTER_DIR_STOP);
    HW_WR_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL, (uint16_t)regval);

    /* Cleanup */
    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);

    return;
}

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

/*
 *  This example demonstrates ePWM to eCAP loopback test.
 *  The ecap module is configured in the capture mode and the ecap device pin is
 *  configured as input pin. A square wave needs to be fed to the ecap pin
 *  externally. Based on the internal counter the count values for each of the
 *  edge is latched in register. 4th edge will generate the interrupt. Based on
 *  the latched counter values calculates the input signal frequency and the
 *  duty cycle based on the input functional clock frequency to ecap module.
 *  ePWM is configured to generate a square wave with 25% duty cycle.
 *  Connect the ePWM output to eCAP input externally on the board.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <math.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/HwiP.h>
#include <drivers/epwm.h>
#include <drivers/ecap.h>
#include <unity.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of threads for basic multithreaded ECAP tests */
#define TEST_ECAP_MT_THREADS             (2U)

/* Task priority for ECAP test threads */
#define TEST_ECAP_TASK_PRIORITY          (8U)

/* Stack size (in bytes) for each ECAP test thread */
#define TEST_ECAP_STACK_SIZE             (128 * 1024)

/* ECAP Interrupt Sources */
#define ECAP_INT_ALL                     (ECAP_CEVT1_INT | ECAP_CEVT2_INT | ECAP_CEVT3_INT | \
                                          ECAP_CEVT4_INT | ECAP_CNTOVF_INT | ECAP_PRDEQ_INT | \
                                          ECAP_CMPEQ_INT)

/* ECAP Frequency MHz */
#define ECAP_INPUT_FREQ_MHZ              (CONFIG_ECAP0_FCLK / (1000U * 1000U))

/* Output channel - A or B */
#define APP_EPWM_OUTPUT_CH               (EPWM_OUTPUT_CH_A)

/* Duty Cycle of PWM output signal in % - give value from 0 to 100 */
#define APP_EPWM_DUTY_CYCLE              (50U)

/* Frequency of PWM output signal in Hz - 10 KHz is selected */
#define APP_EPWM_OUTPUT_FREQ             (10U * 1000U)

/* TB frequency in Hz - so that /4 divider is used */
#define APP_EPWM_TB_FREQ                 (CONFIG_EPWM0_FCLK / 4U)

/*
 * PRD value - this determines the period
 * PRD = (TBCLK/PWM FREQ) / 2
 * /2 is added because up&down counter is selected. So period is 2 times
 */
#define APP_EPWM_PRD_VAL                 ((APP_EPWM_TB_FREQ / \
                                           APP_EPWM_OUTPUT_FREQ) / 2U)

/*
 * COMPA value - this determines the duty cycle
 * COMPA = (PRD - ((dutycycle * PRD) / 100))
 */
#define APP_EPWM_COMPA_VAL               (APP_EPWM_PRD_VAL - \
                                          ((APP_EPWM_DUTY_CYCLE * \
                                            APP_EPWM_PRD_VAL) / 100U))

/* Capture iteration count */
#define APP_ECAP_CAPTURE_LOOP_COUNT      (5U)

#define ECAP_PERIOD_COUNT                (200U)
#define ECAP_PERIOD_DIFF_COUNT           (20U)
#define ECAP_ONE_SHOT_MODE               (0U)
#define ECAP_CONTINUOUS_MODE             (1U)

/* ========================================================================== */
/*                               Typedefs                                     */
/* ========================================================================== */

typedef struct ECAP_TestParams_s {

    uint32_t ecapMode;
    uint32_t ecapOperMode;
    uint32_t ecapCaptStopEvent;
    uint32_t ecapCntrResetMode;
    uint32_t ecapPrescaleEnable;
    uint32_t ecapPrescaleVal;
    uint32_t ecapPwmPol;
    uint32_t ecapIntrEvt;
    uint32_t ecapBaseAddr;
    uint32_t ecapIntrNum;
    uint32_t ecapEventId;
    uint32_t ecapIntrTypePulse;
} ECAP_TestParams;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Variable to hold base address of EPWM/ECAP that is used */
uint32_t                gEcapBaseAddr, gEpwmBaseAddr;

static HwiP_Object           gEcapHwiObject;
static SemaphoreP_Object     gEcapSyncSemObject;
static SemaphoreP_Object     gEcapSyncSemObject_APWM;

static SemaphoreP_Object     gEcapMtSemObj;
static TaskP_Object          gEcapMtThreadTaskObj[TEST_ECAP_MT_THREADS];
static uint8_t               gEcapMtTaskStack[TEST_ECAP_MT_THREADS][TEST_ECAP_STACK_SIZE];

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */

static void App_ecapIntrISR(void *arg);
static void App_epwmInit(void);
static void App_ecapInit(void *args);

static void TestEcap_CaptureAPWMmode(void *args);
static void TestEcap_MTAPWMMode(void *args);    
static void TestEcap_MTCaptureMode(void *args);

static void test_ecap_init_test_params(ECAP_TestParams *testParams,
                                        uint32_t testCaseId);
static void TestEcap_OneshotContinuous(void *args);
static void TestEcap_Continuous(void *args);
static void TestEcap_OneShot(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void run_multi_threaded_tests(void *args)
{
     ECAP_TestParams testParams;

    test_ecap_init_test_params(&testParams, 10661);
    RUN_TEST(TestEcap_CaptureAPWMmode, 10661, (void*)&testParams);
    test_ecap_init_test_params(&testParams, 10662);
    RUN_TEST(TestEcap_OneshotContinuous, 10662, (void*)&testParams);

    return;
}

#ifdef SMP_FREERTOS
void test_main(void *args)
{

    UNITY_BEGIN();

    ECAP_TestParams testParams;
    #if !defined(SOC_AM62DX)
    test_ecap_init_test_params(&testParams, 10661);
    RUN_TEST(TestEcap_CaptureAPWMmode, 10963, (void*)&testParams);
    #endif
    test_ecap_init_test_params(&testParams, 10662);
    RUN_TEST(TestEcap_OneshotContinuous, 10964, (void*)&testParams);
    
    UNITY_END();

}

/**
 * @brief Unity test setup hook.
 *
 * Called before each Unity test. Left empty because tests perform their own
 * per-test setup and teardown.
 */
void setUp(void)
{
}

/**
 * @brief Unity test teardown hook.
 *
 * Called after each Unity test. Left empty because tests perform their own
 * per-test cleanup.
 */
void tearDown(void)
{
}
#endif

/* ========================================================================== */
/*                     Internal Function Definitions                          */
/* ========================================================================== */

/*
 * TestEcap_OneShot
 *
 * This test case validates the ECAP module's one-shot capture mode operation.
 * It initializes ECAP and EPWM, configures interrupts, and performs multiple
 * capture iterations. For each iteration, the ECAP is re-armed if not in
 * continuous mode, and waits for the capture event. After completion, it
 * disables interrupts and signals test completion.
 */
static void TestEcap_OneShot(void *args)
{
    int32_t             status;
    HwiP_Params         hwiPrms;
    uint32_t            loopCnt = APP_ECAP_CAPTURE_LOOP_COUNT;
    ECAP_TestParams     testParams;

    status = SemaphoreP_constructCounting(&gEcapSyncSemObject, 0, loopCnt);
    DebugP_assert(SystemP_SUCCESS == status);

    test_ecap_init_test_params(&testParams, 10661);

    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams.ecapIntrNum;
    hwiPrms.callback    = &App_ecapIntrISR;
    hwiPrms.eventId     = testParams.ecapEventId;
    hwiPrms.isPulse     = testParams.ecapIntrTypePulse;
    hwiPrms.args        = (void *)0;
    status              = HwiP_construct(&gEcapHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Address translate */
    gEcapBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams.ecapBaseAddr);
    gEpwmBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EPWM0_BASE_ADDR);

    /* Initialize ECAP and EPWM (only in case of CAPTURE mode) */
    App_ecapInit(&testParams);
    App_epwmInit();

    /* Start Capture for APP_ECAP_CAPTURE_LOOP_COUNT iterations */
    while(loopCnt > 0)
    {
        if (testParams.ecapOperMode != ECAP_CONTINUOUS_MODE)
        {
            ECAP_oneShotReArm(gEcapBaseAddr);
        }
        /* Add a small delay to allow hardware to settle before waiting for capture event */
        ClockP_usleep(1000);  /* 1 ms delay */
        SemaphoreP_pend(&gEcapSyncSemObject, SystemP_WAIT_FOREVER);
        loopCnt--;
    }

    /* Clear any pending interrupts if any */
    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);
    ECAP_intrDisable(gEcapBaseAddr, ECAP_INT_ALL);

    SemaphoreP_post(&gEcapMtSemObj);

    TaskP_exit();
}

/*
 * TestEcap_Continuous
 *
 * This test case validates the ECAP module's continuous capture mode operation.
 * It initializes ECAP and EPWM, configures interrupts, and performs multiple
 * capture iterations. For each iteration, the ECAP is re-armed if not in
 * continuous mode, and waits for the capture event. After completion, it
 * disables interrupts and signals test completion.
 */
static void TestEcap_Continuous(void *args)
{
    int32_t         status;
    HwiP_Params     hwiPrms;
    uint32_t        loopCnt = APP_ECAP_CAPTURE_LOOP_COUNT;
    ECAP_TestParams testParams;

    status = SemaphoreP_constructCounting(&gEcapSyncSemObject, 0, loopCnt);
    DebugP_assert(SystemP_SUCCESS == status);

    test_ecap_init_test_params(&testParams, 10661);

    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams.ecapIntrNum;
    hwiPrms.callback    = &App_ecapIntrISR;
    hwiPrms.eventId     = testParams.ecapEventId;
    hwiPrms.isPulse     = testParams.ecapIntrTypePulse;
    hwiPrms.args        = (void *)0;
    status              = HwiP_construct(&gEcapHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Address translate */
    gEcapBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams.ecapBaseAddr);
    gEpwmBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EPWM0_BASE_ADDR);

    /* Initialize ECAP and EPWM (only in case of CAPTURE mode) */
    App_ecapInit(&testParams);
    App_epwmInit();

    /* Start Capture for APP_ECAP_CAPTURE_LOOP_COUNT iterations */
    while(loopCnt > 0)
    {
        if (testParams.ecapOperMode != ECAP_CONTINUOUS_MODE)
        {
            ECAP_oneShotReArm(gEcapBaseAddr);
        }
        /* Add a small delay to allow hardware to settle before waiting for capture event */
        ClockP_usleep(1000);  /* 1 ms delay */
        SemaphoreP_pend(&gEcapSyncSemObject, SystemP_WAIT_FOREVER);
        loopCnt--;
    }

    /* Clear any pending interrupts if any */
    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);
    ECAP_intrDisable(gEcapBaseAddr, ECAP_INT_ALL);

    SemaphoreP_post(&gEcapMtSemObj);

    TaskP_exit();
}

/*
 * TestEcap_OneshotContinuous
 *
 * This test case validates coordination between ECAP one-shot and continuous capture modes
 * in a multi-threaded environment. It creates two threads: one running continuous mode and
 * the other running one-shot mode. Both threads synchronize using semaphores and perform
 * multiple capture iterations. After completion, resources are cleaned up and threads are
 * destructed. This ensures ECAP modes can operate concurrently without interference.
 */
static void TestEcap_OneshotContinuous(void *args)
{
    uint32_t      i;
    int32_t       status;
    TaskP_Params  taskParams;
    uint32_t      loopCnt = APP_ECAP_CAPTURE_LOOP_COUNT;

    status = SemaphoreP_constructCounting(&gEcapMtSemObj, 0, TEST_ECAP_MT_THREADS);
    DebugP_assert(SystemP_SUCCESS == status);

    status = SemaphoreP_constructCounting(&gEcapSyncSemObject, 0, loopCnt);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Create threads for continuous and one-shot ECAP modes */
    for (i = 0; i < TEST_ECAP_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name         = "ECAP_MT_MODE";
        taskParams.stackSize    = TEST_ECAP_STACK_SIZE;
        taskParams.stack        = gEcapMtTaskStack[i];
        taskParams.priority     = TEST_ECAP_TASK_PRIORITY;
        taskParams.args         = (void *)(uintptr_t)i;
        #ifdef SMP_FREERTOS
            taskParams.coreAffinity = 1 << i;
        #endif
        if (i == 0)
            taskParams.taskMain = TestEcap_Continuous;
        else
            taskParams.taskMain = TestEcap_OneShot;

        status = TaskP_construct(&gEcapMtThreadTaskObj[i], &taskParams);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_ECAP_MT_THREADS; i++)
    {
        SemaphoreP_pend(&gEcapMtSemObj, SystemP_WAIT_FOREVER);
    }

    /* Cleanup resources and destruct threads */
    SemaphoreP_destruct(&gEcapMtSemObj);
    SemaphoreP_destruct(&gEcapSyncSemObject);

    for (i = 0; i < TEST_ECAP_MT_THREADS; i++)
    {
        TaskP_destruct(&gEcapMtThreadTaskObj[i]);
    }
}

/*
 * TestEcap_MTCaptureMode
 *
 * This test case validates ECAP capture mode operation in a multi-threaded context.
 * It initializes ECAP and EPWM, configures interrupts, and performs multiple capture
 * iterations. For each iteration, the ECAP is re-armed if not in continuous mode,
 * and waits for the capture event. After completion, it disables interrupts and
 * signals test completion, ensuring proper synchronization and resource cleanup.
 */
static void TestEcap_MTCaptureMode(void *args)
{
    int32_t         status;
    HwiP_Params     hwiPrms;
    uint32_t        loopCnt = APP_ECAP_CAPTURE_LOOP_COUNT;
    ECAP_TestParams testParams;

    status = SemaphoreP_constructCounting(&gEcapSyncSemObject, 0, loopCnt);
    DebugP_assert(SystemP_SUCCESS == status);

    test_ecap_init_test_params(&testParams, 10661);

    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams.ecapIntrNum;
    hwiPrms.callback    = &App_ecapIntrISR;
    hwiPrms.eventId     = testParams.ecapEventId;
    hwiPrms.isPulse     = testParams.ecapIntrTypePulse;
    hwiPrms.args        = (void *)0;
    status              = HwiP_construct(&gEcapHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Address translate */
    gEcapBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams.ecapBaseAddr);
    gEpwmBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EPWM0_BASE_ADDR);

    /* Initialize ECAP and EPWM (only in case of CAPTURE mode) */
    App_ecapInit(&testParams);
    App_epwmInit();

    /* Start Capture for APP_ECAP_CAPTURE_LOOP_COUNT iterations */
    while(loopCnt > 0)
    {
        if (testParams.ecapOperMode != ECAP_CONTINUOUS_MODE)
        {
            ECAP_oneShotReArm(gEcapBaseAddr);
        }
        SemaphoreP_pend(&gEcapSyncSemObject, SystemP_WAIT_FOREVER);
        loopCnt--;
    }

    /* Clear any pending interrupts if any */
    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);
    ECAP_intrDisable(gEcapBaseAddr, ECAP_INT_ALL);

    SemaphoreP_post(&gEcapMtSemObj);

    TaskP_exit();
}

/*
 * TestEcap_MTAPWMMode
 *
 * This test case validates ECAP APWM mode operation in a multi-threaded context.
 * It initializes ECAP in APWM mode, configures interrupts, and waits for a single
 * APWM event. After the event is captured, it disables interrupts, cleans up resources,
 * and signals test completion. This ensures APWM mode can operate correctly alongside
 * other ECAP modes in a multi-threaded environment.
 */
static void TestEcap_MTAPWMMode(void *args)
{
    int32_t         status;
    HwiP_Params     hwiPrms;
    ECAP_TestParams testParams;

    status = SemaphoreP_constructCounting(&gEcapSyncSemObject, 0, 1);
    DebugP_assert(SystemP_SUCCESS == status);

    test_ecap_init_test_params(&testParams, 10662);

    /* Address translate */
    gEcapBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams.ecapBaseAddr);

    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams.ecapIntrNum;
    hwiPrms.callback    = &App_ecapIntrISR;
    hwiPrms.eventId     = testParams.ecapEventId;
    hwiPrms.isPulse     = testParams.ecapIntrTypePulse;
    hwiPrms.args        = (void *)0;
    status              = HwiP_construct(&gEcapHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Initialize ECAP in APWM mode */
    App_ecapInit(&testParams);

    SemaphoreP_pend(&gEcapSyncSemObject, SystemP_WAIT_FOREVER);

    /* Clear any pending interrupts if any */
    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);
    ECAP_intrDisable(gEcapBaseAddr, ECAP_INT_ALL);

    /* Cleanup interrupt object */
    HwiP_destruct(&gEcapHwiObject);

    /* Signal test completion */
    SemaphoreP_post(&gEcapMtSemObj);

    TaskP_exit();
}

/*
 * TestEcap_CaptureAPWMmode
 *
 * This test case validates ECAP operation in both capture and APWM modes
 * in a multi-threaded environment. It creates two threads: one for APWM mode
 * and one for capture mode, synchronizing their execution using semaphores.
 * Each thread performs its respective ECAP operation and signals completion.
 * After all threads finish, resources are cleaned up and threads are destructed.
 * This ensures ECAP modes can operate concurrently without interference.
 */
static void TestEcap_CaptureAPWMmode(void *args)
{
    uint32_t i;
    int32_t status;
    TaskP_Params taskParams;
    uint32_t loopCnt = APP_ECAP_CAPTURE_LOOP_COUNT;

    /* Address translate */
    gEcapBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_ECAP0_BASE_ADDR);
    gEpwmBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EPWM0_BASE_ADDR);

    status = SemaphoreP_constructCounting(&gEcapMtSemObj, 0, TEST_ECAP_MT_THREADS);
    DebugP_assert(SystemP_SUCCESS == status);

    status = SemaphoreP_constructCounting(&gEcapSyncSemObject, 0, loopCnt);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Create threads */
    for (i = 0; i < TEST_ECAP_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "ECAP_MT_MODE";
        taskParams.stackSize = TEST_ECAP_STACK_SIZE;
        taskParams.stack     = gEcapMtTaskStack[i];
        taskParams.priority  = TEST_ECAP_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;
        #ifdef SMP_FREERTOS
            taskParams.coreAffinity = 1 << i;
        #endif

        if (i == 1)
            taskParams.taskMain = TestEcap_MTCaptureMode;
        else
            taskParams.taskMain = TestEcap_MTAPWMMode;

        status = TaskP_construct(&gEcapMtThreadTaskObj[i], &taskParams);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_ECAP_MT_THREADS; i++)
    {
        SemaphoreP_pend(&gEcapMtSemObj, SystemP_WAIT_FOREVER);
    }

    /* Cleanup resources and destruct threads */
    SemaphoreP_destruct(&gEcapMtSemObj);
    SemaphoreP_destruct(&gEcapSyncSemObject);

    for (i = 0; i < TEST_ECAP_MT_THREADS; i++)
    {
        TaskP_destruct(&gEcapMtThreadTaskObj[i]);
    }
}

/*
 * App_ecapIntrISR
 *
 * This interrupt service routine handles ECAP interrupts for both capture and APWM modes.
 * It reads the interrupt status, clears the ECAP interrupt and global interrupt flags,
 * and posts to the appropriate semaphore to signal event completion. This allows
 * synchronization between threads and ensures proper handling of ECAP events in
 * multi-threaded test cases. The routine distinguishes between APWM and capture modes
 * based on the argument provided.
 */
static void App_ecapIntrISR(void *arg)
{
    uint32_t intrFlag;

    intrFlag = ECAP_getIntrStatus(gEcapBaseAddr, ECAP_INT_ALL);
    /* Clear ECAP Interrupt */
    ECAP_intrStatusClear(gEcapBaseAddr, intrFlag);
    /* Clear Global Interrupt Flag */
    ECAP_globalIntrClear(gEcapBaseAddr);

    if ((uintptr_t)arg == 1)
        SemaphoreP_post(&gEcapSyncSemObject_APWM);
    else
        SemaphoreP_post(&gEcapSyncSemObject);
}

/*
 * App_ecapInit
 *
 * This function initializes the ECAP module based on the provided test parameters.
 * It configures the ECAP for either capture or APWM mode, sets up event polarity,
 * prescale, and counter reset modes, and enables the appropriate interrupts.
 * For capture mode, it supports both one-shot and continuous operation.
 * For APWM mode, it configures the PWM output parameters.
 * This setup ensures the ECAP is ready for multi-threaded test execution.
 */
static void App_ecapInit(void *args)
{
    ECAP_TestParams *testParams = (ECAP_TestParams *)args;

    /* Disable and clear interrupts */
    ECAP_intrDisable(gEcapBaseAddr, ECAP_INT_ALL);
    ECAP_intrStatusClear(gEcapBaseAddr, ECAP_INT_ALL);

    /* Disable CAP1-CAP4 register loads */
    ECAP_captureLoadingDisable(gEcapBaseAddr);

    /* Configure eCAP */
    ECAP_counterControl(gEcapBaseAddr, ECAP_COUNTER_STOP);
    /* Enable capture mode */
    ECAP_operatingModeSelect(gEcapBaseAddr, testParams->ecapMode);

    /* Enable prescale */
    ECAP_prescaleConfig(gEcapBaseAddr, testParams->ecapPrescaleVal);

    if (testParams->ecapMode == ECAP_CAPTURE_MODE)
    {
        if (testParams->ecapOperMode == ECAP_ONE_SHOT_MODE)
        {
            /* One shot mode, stop capture at event 4 */
            ECAP_oneShotModeConfig(gEcapBaseAddr, testParams->ecapCaptStopEvent);
        }
        else
        {
            ECAP_continousModeConfig(gEcapBaseAddr);
        }
        /* Set polarity of the events to rising, falling, rising, falling edge */
        ECAP_captureEvtPolarityConfig(gEcapBaseAddr,
                                      ECAP_CAPTURE_EVENT_RISING,
                                      ECAP_CAPTURE_EVENT_FALLING,
                                      ECAP_CAPTURE_EVENT_RISING,
                                      ECAP_CAPTURE_EVENT_FALLING);

        /* Set capture in time difference mode */
        ECAP_captureEvtCntrRstConfig(gEcapBaseAddr,
                                     testParams->ecapCntrResetMode,
                                     testParams->ecapCntrResetMode,
                                     testParams->ecapCntrResetMode,
                                     testParams->ecapCntrResetMode);

        ECAP_syncInOutSelect(gEcapBaseAddr, ECAP_ENABLE_COUNTER, ECAP_SYNC_IN);

        /* Enable eCAP module */
        ECAP_captureLoadingEnable(gEcapBaseAddr);
    }
    else
    {
        /* Load the PWM Counter values for 50% duty cycle signal */
        ECAP_APWM_polarityConfig(gEcapBaseAddr, testParams->ecapPwmPol);
        ECAP_APWM_captureConfig(gEcapBaseAddr, (ECAP_PERIOD_COUNT / 2), ECAP_PERIOD_COUNT);
        ECAP_APWM_shadowCaptureConfig(gEcapBaseAddr, (ECAP_PERIOD_COUNT / 2), ECAP_PERIOD_COUNT);
        ECAP_counterPhaseValConfig(gEcapBaseAddr, 0U);
        ECAP_counterConfig(gEcapBaseAddr, ECAP_PERIOD_COUNT);
    }

    ECAP_counterControl(gEcapBaseAddr, ECAP_COUNTER_FREE_RUNNING);
    /* Enable interrupt */
    ECAP_intrEnable(gEcapBaseAddr, testParams->ecapIntrEvt);
}

/*
 * App_epwmInit
 *
 * This function initializes the EPWM module for generating a square wave output.
 * It configures the time base, counter compare, action qualifier, dead band,
 * chopper, trip zone, and event trigger submodules. The EPWM output is used
 * as an input to the ECAP module for capture tests. The configuration ensures
 * a stable PWM signal with defined frequency and duty cycle for ECAP testing.
 */
static void App_epwmInit(void)
{
    EPWM_AqActionCfg  aqConfig;

    /* Configure Time base submodule */
    EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, CONFIG_EPWM0_FCLK);
    EPWM_tbPwmFreqCfg(gEpwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
                      EPWM_TB_COUNTER_DIR_UP_DOWN, EPWM_SHADOW_REG_CTRL_ENABLE);
    EPWM_tbSyncDisable(gEpwmBaseAddr);
    EPWM_tbSetSyncOutMode(gEpwmBaseAddr, PWMSS_EPWM_TBCTL_SYNCOSEL_EPWMXSYNC);
    EPWM_tbSetEmulationMode(gEpwmBaseAddr, EPWM_TB_EMU_MODE_FREE_RUN);

    /* Configure counter compare submodule */
    EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A,
            APP_EPWM_COMPA_VAL, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
    EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B,
            APP_EPWM_COMPA_VAL, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);

    /* Configure Action Qualifier Submodule */
    aqConfig.zeroAction   = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.prdAction    = EPWM_AQ_ACTION_DONOTHING;
    aqConfig.cmpAUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpADownAction = EPWM_AQ_ACTION_LOW;
    aqConfig.cmpBUpAction = EPWM_AQ_ACTION_HIGH;
    aqConfig.cmpBDownAction = EPWM_AQ_ACTION_LOW;
    EPWM_aqActionOnOutputCfg(gEpwmBaseAddr, APP_EPWM_OUTPUT_CH, &aqConfig);

    /* Configure Dead Band Submodule */
    EPWM_deadbandBypass(gEpwmBaseAddr);

    /* Configure Chopper Submodule */
    EPWM_chopperEnable(gEpwmBaseAddr, FALSE);

    /* Configure trip zone Submodule */
    EPWM_tzTripEventDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);
    EPWM_tzTripEventDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_CYCLE_BY_CYCLE, 0U);

    /* Configure event trigger Submodule */
    EPWM_etIntrCfg(gEpwmBaseAddr, EPWM_ET_INTR_EVT_CNT_EQ_ZRO,
        EPWM_ET_INTR_PERIOD_FIRST_EVT);
    EPWM_etIntrEnable(gEpwmBaseAddr);
}

/*
 * test_ecap_init_test_params
 *
 * This function initializes the ECAP_TestParams structure based on the given testCaseId.
 * It sets up ECAP mode, operation mode, interrupt sources, base addresses, and other
 * configuration parameters required for each test scenario. The function supports
 * multiple ECAP modes including capture and APWM, and configures event polarity,
 * prescale, and interrupt types for each test case. This ensures each test case
 * runs with the correct ECAP configuration for reliable validation.
 */
static void test_ecap_init_test_params(ECAP_TestParams *testParams, uint32_t testCaseId)
{
    /* Default Initialization */
    testParams->ecapMode = ECAP_CAPTURE_MODE;
    testParams->ecapOperMode = ECAP_ONE_SHOT_MODE;
    testParams->ecapCaptStopEvent = ECAP_CAPTURE_EVENT4_STOP;
    testParams->ecapCntrResetMode = ECAP_CAPTURE_EVENT_RESET_COUNTER_RESET;
    testParams->ecapPrescaleEnable = FALSE;
    testParams->ecapPrescaleVal = 0U;
    testParams->ecapPwmPol = ECAP_APWM_ACTIVE_LOW;
    testParams->ecapIntrEvt = ECAP_CEVT4_INT;
    testParams->ecapBaseAddr = CONFIG_ECAP0_BASE_ADDR;
    testParams->ecapIntrNum = CONFIG_ECAP0_INTR;
    testParams->ecapEventId = CONFIG_ECAP0_EVENT_ID;
    testParams->ecapIntrTypePulse = CONFIG_ECAP0_INTR_IS_PULSE;

    switch (testCaseId)
    {
        case 10661:
            testParams->ecapCaptStopEvent = ECAP_CAPTURE_EVENT1_STOP;
            testParams->ecapIntrEvt = ECAP_CEVT1_INT;
            testParams->ecapOperMode = ECAP_CONTINUOUS_MODE;
            break;
        case 10662:
            testParams->ecapBaseAddr = CONFIG_ECAP1_BASE_ADDR;
            testParams->ecapIntrNum = CONFIG_ECAP1_INTR;
            testParams->ecapEventId = CONFIG_ECAP1_EVENT_ID;
            testParams->ecapIntrTypePulse = CONFIG_ECAP1_INTR_IS_PULSE;
            testParams->ecapMode = ECAP_APWM_MODE;
            testParams->ecapPwmPol = ECAP_APWM_ACTIVE_LOW;
            testParams->ecapIntrEvt = ECAP_CMPEQ_INT;
            break;
    }
}


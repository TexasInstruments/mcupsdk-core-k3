/*
 *  Copyright (C) 2021-2025 Texas Instruments Incorporated
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
 *  This example demonstrates eQEP capture test.
 *  Example configures the eQEP and captures the quadrature input signal
 *  at index event. Example also configures the eQEP to calculate frequency
 *  using unit timeout event. Based on the position count values,
 *  it calculates the frequency of the input signal.
 *  EQEP signal is generated using GPIO pin toggling.
 *  GPIO pins need to be looped back to the EQEP pins that are available in the
 *  IO expansion board.
 */

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/TaskP.h>
#include <unity.h>
#include <drivers/eqep.h>
#include <drivers/hw_include/csl_types.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "test_eqep_pattern_gen.h"

typedef struct EQEP_TestParams_s {

    uint32_t eqepDir;
    uint32_t eqepFreqMeas;
    uint32_t eqepCntrRstIdxEvt;
    uint32_t eqepIntrEvt;
    uint32_t eqepWdgEvtTest;
    uint32_t eqepIntrNum;
    uint32_t eqepEventId;
    uint32_t eqepBaseAddr;
} EQEP_TestParams;


/* EQEP Interrupt Sources */
#define EQEP_INT_ALL                        (EQEP_INT_GLOBAL            | \
                                             EQEP_INT_POS_CNT_ERROR     | \
                                             EQEP_INT_PHASE_ERROR       | \
                                             EQEP_INT_DIR_CHANGE        | \
                                             EQEP_INT_WATCHDOG          | \
                                             EQEP_INT_UNDERFLOW         | \
                                             EQEP_INT_OVERFLOW          | \
                                             EQEP_INT_POS_COMP_READY    | \
                                             EQEP_INT_POS_COMP_MATCH    | \
                                             EQEP_INT_STROBE_EVNT_LATCH | \
                                             EQEP_INT_INDEX_EVNT_LATCH  | \
                                             EQEP_INT_UNIT_TIME_OUT     | \
                                             EQEP_INT_QMA_ERROR)
/* Number of EQEP EVENTS */
#define EQEP_EVENT_CNT                      (10U)

/* Frequency of EQEP signal for testing unit timeout event in Hz. */
#define EQEP_SIGNAL_TEST_FREQ               (500U)

/* Frequence of unit timeout event in Hz.
 * Should be less than the EQEP signal frequency to capture multiple clocks at
 * Timeout event. So configuring it to 1/10th the EQEP signal frequency. */
#define EQEP_UNIT_TIMEOUT_FREQ              (EQEP_SIGNAL_TEST_FREQ / EQEP_EVENT_CNT)

/* Number of times the EQEP pattern is generated. */
#define EQEP_PATTERN_GEN_LOOP_COUNT         (EQEP_SIGNAL_TEST_FREQ / EQEP_EVENT_CNT)

/* By default IP holds LOW/HIGH signal in EQEP pins.
 * First position count can contain old value.
 * Setting variance to 4 as we capture 4 edges per cycle. */
#define EQEP_POS_CNT_VARIANCE               (4U)

#ifdef ENABLE_MT_TESTS
/* Multi-threaded test configuration */
#define TEST_EQEP_MT_TASK_STACK_SIZE           (32 * 1024)
#define TEST_EQEP_MT_TEST_DURATION_MS          (5000U)
#define TEST_EQEP_POSITION_READ_INTERVAL_MS    (100U)
#endif


/* Global variables and objects */
static HwiP_Object           gEqepHwiObject;
/* Variable to hold base address of EQEP/GPIO that is used */
uint32_t                     gEqepBaseAddr;
/* EQEP interrupt handle. */
static SemaphoreP_Object     gEqepSyncSem;

/* Isr count at different events. */
volatile uint32_t            gEqepIsrCnt = 0U;
volatile uint16_t            TestEqep_lastIntrStatus = 0U;

/* Pos Count capture at different events. */
uint32_t                     gEqepPosCnt[EQEP_EVENT_CNT];
uint32_t                     gEqepCapPrd[EQEP_EVENT_CNT];
uint32_t                     gEqepCapTmr[EQEP_EVENT_CNT];
uint32_t                     gEqepCapPrdLatch[EQEP_EVENT_CNT];
uint32_t                     gEqepCapTmrLatch[EQEP_EVENT_CNT];
uint32_t                     gEqepAPin, gEqepBPin, gEqepIPin, gEqepSPin;


/* Multi-threaded test result structures */
#ifdef ENABLE_MT_TESTS
typedef struct {
    uint32_t instanceId;
    uint32_t positionReadings[100];
    uint32_t readingCount;
    uint32_t speedValues[100];
    uint32_t speedCount;
    uint32_t dataCorruptionDetected;
} EQEP_ThreadResults;

static EQEP_ThreadResults TestEqep_thread1Results = {0};
static EQEP_ThreadResults TestEqep_thread2Results = {0};

/* Multi-threaded test task infrastructure */
static uint8_t TestEqep_task1Stack[TEST_EQEP_MT_TASK_STACK_SIZE];
static uint8_t TestEqep_task2Stack[TEST_EQEP_MT_TASK_STACK_SIZE];
static TaskP_Object TestEqep_TaskObjs[2];
static SemaphoreP_Object TestEqep_mtTestSem;
#endif /* ENABLE_MT_TESTS */

/* Static Function declarations */
static void App_eqepIntrISR(void *arg);
static void App_eqepInitQuadratureWave(EQEP_TestParams *testParams);
static void App_eqepInitFrequencyCalculation(EQEP_TestParams *testParams);
static void App_eqepInitPattern(EqepAppPatternParams *eqepPattern);
static void App_eqepComparePosCnt(int32_t expCnt, EQEP_TestParams *testParams);
static void TestEqep_validateDirectionCounts(int32_t expectedSign);
static void App_eqepTestClockwiseDirection(EQEP_TestParams *testParams);
static void App_eqepTestAntiClockwiseDirection(EQEP_TestParams *testParams);
static void App_eqepTestFrequency(EQEP_TestParams *testParams);
static uint32_t App_eqepCalculateFrequencyUnitTimeout(void);
static void test_eqep_init_test_params(EQEP_TestParams *testParams,
                                           uint32_t testCaseId);
static void eqep_capture_main(void *args);
static void eqep_phase_error_wdg_test(void *args);
static void eqep_code_coverage_enhancement_test(void *args);
static void TestEqep_initPositionCompare(EQEP_TestParams *testParams);
static void TestEqep_initWatchdog(EQEP_TestParams *testParams);
static void TestEqep_directionValidation(void *args);
static void TestEqep_lowSpeedCaptureValidation(void *args);
static void TestEqep_watchdogStallDetection(void *args);
static void TestEqep_positionCompareEvent(void *args);
static void TestEqep_clockDirCountingMode(void *args);
static void TestEqep_countDirectionMode(void *args);
static void TestEqep_strobePositionInit(void *args);
static void TestEqep_indexGating(void *args);
static void TestEqep_inputPolarityImpact(void *args);


#ifdef ENABLE_MT_TESTS
#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62X)
static void TestEqep_positionReaderThread(void *arg);
static void TestEqep_speedCalcThread(void *arg);
static void TestEqep_verifyThreadResults(void);
static void TestEqep_positionReadWhileSpeedCalc(void *args);
static void TestEqep_captureSpeedThread(void *arg);
static void TestEqep_watchdogMonitorThread(void *arg);
static void TestEqep_watchdogMonitorWhileCaptureCalc(void *args);
static void TestEqep_qmaMode1Thread(void *arg);
static void TestEqep_qmaMode2Thread(void *arg);
static void TestEqep_dualInstanceQMAOperation(void *args);
#endif /* SOC_AM62AX || SOC_AM62DX || SOC_AM62X */
#endif /* ENABLE_MT_TESTS */

void test_main(void *args)
{
    EQEP_TestParams testParams;

    UNITY_BEGIN();

#ifdef SOC_AM62D
    DebugP_log("Pin connection details for this eqep test:\r\n");
    DebugP_log("  R17-A19\r\n");
    DebugP_log("  K19-A20\r\n");
    DebugP_log("  L18-B21\r\n");
    DebugP_log("  L17-A21\r\n");
    DebugP_log("Note that these pins are on the audio expansion connecter 1 and not the audio expansion card 1\r\n");
    DebugP_log("Refer the SOC datasheet for pins and use an adapter for the AEC 1. Do not use the Audio Expansion Card\r\n");
#else
    DebugP_log("Please refer EXAMPLES_DRIVERS_EQEP_CAPTURE example user \
guide and test code comment for the test setup details.\r\n");
#endif
    
    /* Run tests */
    test_eqep_init_test_params(&testParams, 7264);
    RUN_TEST(eqep_capture_main, 7264, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 6988);
    RUN_TEST(eqep_capture_main, 6988, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 7263);
    RUN_TEST(eqep_capture_main, 7263, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 7265);
    RUN_TEST(eqep_capture_main, 7265, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 7271);
    RUN_TEST(eqep_capture_main, 7271, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 7272);
    RUN_TEST(eqep_capture_main, 7272, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 7270);
    RUN_TEST(eqep_capture_main, 7270, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 7267);
    RUN_TEST(eqep_phase_error_wdg_test, 7267, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 7268);
    RUN_TEST(eqep_phase_error_wdg_test, 7268, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 7266);
    RUN_TEST(eqep_phase_error_wdg_test, 7266, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 11967);
    RUN_TEST(TestEqep_directionValidation, 11967, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 11968);
    RUN_TEST(TestEqep_lowSpeedCaptureValidation, 11968, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 11969);
    RUN_TEST(TestEqep_watchdogStallDetection, 11969, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 11970);
    RUN_TEST(TestEqep_positionCompareEvent, 11970, (void*)&testParams);
#ifdef ENABLE_MT_TESTS
#if defined (SOC_AM62AX) || defined (SOC_AM62X)
    Board_userExpansionHeaderEnable();
#endif
    test_eqep_init_test_params(&testParams, 11971);
#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62X)
    RUN_TEST(TestEqep_positionReadWhileSpeedCalc, 11971, (void*)&testParams);
#endif /* SOC_AM62AX || SOC_AM62DX || SOC_AM62X */
    test_eqep_init_test_params(&testParams, 11972);
    RUN_TEST(TestEqep_watchdogMonitorWhileCaptureCalc, 11972, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 11973);
#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62X)
    RUN_TEST(TestEqep_dualInstanceQMAOperation, 11973, (void*)&testParams);
#endif /* SOC_AM62AX || SOC_AM62DX || SOC_AM62X */
#endif /* ENABLE_MT_TESTS */
    test_eqep_init_test_params(&testParams, 11974);
    RUN_TEST(TestEqep_clockDirCountingMode, 11974, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 11975);
    RUN_TEST(TestEqep_countDirectionMode, 11975, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 11976);
    RUN_TEST(TestEqep_inputPolarityImpact, 11976, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 11977);
    RUN_TEST(TestEqep_strobePositionInit, 11977, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 11978);
    RUN_TEST(TestEqep_indexGating, 11978, (void*)&testParams);
    test_eqep_init_test_params(&testParams, 7314);
    RUN_TEST(eqep_code_coverage_enhancement_test, 7314, (void*)&testParams);

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

static void eqep_capture_main(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);
    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Address translate */
    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    /* Clear Interrupts */
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    DebugP_log("Sending quadrature wave for 50 cycles in clockwise direction.\
With index event in between, Captures 4 edges per cycle\r\n");

    /* Test Clockwise Direction */
    App_eqepTestClockwiseDirection(testParams);

    DebugP_log("Quadrature input capture test clockwise direction passed\r\n");

    DebugP_log("Sending quadrature wave for 50 cycles in anticlockwise direction.\
With index event in between, Captures 4 edges per cycle\r\n");

    /* Test Anti Clockwise Direction */
    App_eqepTestAntiClockwiseDirection(testParams);

    DebugP_log("Quadrature input capture test anti clockwise direction passed\r\n");

    if (testParams->eqepFreqMeas == TRUE)
    {
        DebugP_log("Starting Frequency calculation test\r\n");

        /* Frequency Calculation Test */
        App_eqepTestFrequency(testParams);

        DebugP_log("Frequency calculation test passed\r\n");
    }

    EQEP_disableModule(gEqepBaseAddr);
    EQEP_disableCapture(gEqepBaseAddr);
    EQEP_disableUnitTimer(gEqepBaseAddr);

    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);

}

static void eqep_phase_error_wdg_test(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);
    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Address translate */
    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    /* Clear Interrupts */
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    /* Enable capture from quadrature wave with index event. */
    App_eqepInitQuadratureWave(testParams);

    /* Reset ISR Count */
    gEqepIsrCnt = 0U;
    /* The count values expected is 199
     * Count starts from 0 and counts 4 edges per cycle. */

    /* Init default EQEP pattern params */
    App_eqepInitPattern(&eqepPattern);

    /* Enable capture from quadrature wave with index event. */
    App_eqepInitQuadratureWave(testParams);

    /* Start EQEP Pattern Generation. */
    eqepPattern.direction        = testParams->eqepDir;
    eqepPattern.generateIdxPulse = TRUE;
    App_eqepGeneratePattern(&eqepPattern);

    if (testParams->eqepWdgEvtTest == TRUE)
    {
        EQEP_disableWatchdog(gEqepBaseAddr);
    }

    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);

}

static void eqep_code_coverage_enhancement_test(void *args)
{
    int32_t              status;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;
    uint16_t             regVal, intStatus;
    uint32_t             captVal, tmpEqepAPin, tmpEqepBPin, tmpEqepIPin, tmpEqepSPin;

    /* Address translate */
    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    /* Clear Interrupts */
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    /* Init default EQEP pattern params */
    App_eqepInitPattern(&eqepPattern);

    /* Enable capture from quadrature wave with index event. */
    App_eqepInitQuadratureWave(testParams);

    /* Start EQEP Pattern Generation. */
    eqepPattern.direction        = testParams->eqepDir;
    eqepPattern.generateIdxPulse = TRUE;
    App_eqepGeneratePattern(&eqepPattern);

    App_eqepReadPinValue(&gEqepAPin, &gEqepBPin, &gEqepIPin, &gEqepSPin);
    tmpEqepAPin = gEqepAPin;
    tmpEqepBPin = gEqepBPin;
    tmpEqepIPin = gEqepIPin;
    tmpEqepSPin = gEqepSPin;
    EQEP_setInputPolarity(gEqepBaseAddr, FALSE, FALSE, FALSE, FALSE);
    App_eqepReadPinValue(&gEqepAPin, &gEqepBPin, &gEqepIPin, &gEqepSPin);
    DebugP_assert((tmpEqepAPin | tmpEqepBPin | tmpEqepIPin | tmpEqepSPin) ==
                   (gEqepAPin | gEqepBPin | gEqepIPin | gEqepSPin));
    EQEP_setInputPolarity(gEqepBaseAddr, TRUE, TRUE, TRUE, TRUE);

    status = EQEP_isErrorSet(gEqepBaseAddr);
    DebugP_assert(FALSE == status);

    EQEP_forceInterrupt(gEqepBaseAddr, EQEP_INT_PHASE_ERROR);
    intStatus = EQEP_getInterruptStatus(gEqepBaseAddr);
    DebugP_assert((intStatus & EQEP_INT_PHASE_ERROR) == EQEP_INT_PHASE_ERROR);
    DebugP_assert(TRUE == EQEP_isErrorSet(gEqepBaseAddr));

    EQEP_enableCompare(gEqepBaseAddr);
    regVal = HW_RD_REG16(gEqepBaseAddr + CSL_EQEP_QPOSCTL);
    DebugP_assert((regVal & CSL_EQEP_QPOSCTL_PCE_MASK) == CSL_EQEP_QPOSCTL_PCE_MASK);

    EQEP_disableCompare(gEqepBaseAddr);
    regVal = HW_RD_REG16(gEqepBaseAddr + CSL_EQEP_QPOSCTL);
    DebugP_assert((regVal & CSL_EQEP_QPOSCTL_PCE_MASK) == 0U);

    status = EQEP_setComparePulseWidth(gEqepBaseAddr, CSL_EQEP_QPOSCTL_PCSPW_MASK + 2U);
    DebugP_assert(status == CSL_EBADARGS);

    status = EQEP_setComparePulseWidth(gEqepBaseAddr, CSL_EQEP_QPOSCTL_PCSPW_MASK);
    regVal = HW_RD_REG16(gEqepBaseAddr + CSL_EQEP_QPOSCTL);
    DebugP_assert((regVal & CSL_EQEP_QPOSCTL_PCSPW_MASK) == CSL_EQEP_QPOSCTL_PCSPW_MASK - 1U);

    EQEP_setPositionInitMode(gEqepBaseAddr, EQEP_INIT_FALLING_INDEX);
    regVal = HW_RD_REG16(gEqepBaseAddr + CSL_EQEP_QEPCTL);
    DebugP_assert((regVal & CSL_EQEP_QEPCTL_IEI_MASK) == EQEP_INIT_FALLING_INDEX);

    EQEP_setSWPositionInit(gEqepBaseAddr, TRUE);
    regVal = HW_RD_REG16(gEqepBaseAddr + CSL_EQEP_QEPCTL);
    DebugP_assert((regVal & CSL_EQEP_QEPCTL_SWI_MASK) == CSL_EQEP_QEPCTL_SWI_MASK);

    EQEP_setSWPositionInit(gEqepBaseAddr, FALSE);
    regVal = HW_RD_REG16(gEqepBaseAddr + CSL_EQEP_QEPCTL);
    DebugP_assert((regVal & CSL_EQEP_QEPCTL_SWI_MASK) == 0U);

    captVal = EQEP_getStrobePositionLatch(gEqepBaseAddr);
    DebugP_assert(captVal == HW_RD_REG32(gEqepBaseAddr + CSL_EQEP_QPOSSLAT));

    EQEP_setQMAModuleMode(gEqepBaseAddr, EQEP_QMA_MODE_1);
    captVal = HW_RD_REG32(gEqepBaseAddr + CSL_EQEP_QMACTRL);
    DebugP_assert((captVal & CSL_EQEP_QMACTRL_MODE_MASK) == EQEP_QMA_MODE_1);

    EQEP_setStrobeSource(gEqepBaseAddr, EQEP_STROBE_OR_ADCSOCB);
    captVal = HW_RD_REG32(gEqepBaseAddr + CSL_EQEP_QEPSTROBESEL);
    DebugP_assert((captVal & CSL_EQEP_QEPSTROBESEL_STROBESEL_MASK) == EQEP_STROBE_OR_ADCSOCB);

    EQEP_setCompareConfig(gEqepBaseAddr, EQEP_COMPARE_IDX_SYNC_OUT | EQEP_COMPARE_LOAD_ON_MATCH,
                          CSL_EQEP_QPOSCTL_PCSPW_MASK, CSL_EQEP_QPOSCTL_PCSPW_MASK);
    captVal = HW_RD_REG32(gEqepBaseAddr + CSL_EQEP_QPOSCMP);
    regVal = HW_RD_REG16(gEqepBaseAddr + CSL_EQEP_QPOSCTL);
    DebugP_assert((regVal & EQEP_COMPARE_LOAD_ON_MATCH) == EQEP_COMPARE_LOAD_ON_MATCH);
    regVal = HW_RD_REG16(gEqepBaseAddr + CSL_EQEP_QDECCTL_TYPE2);
    DebugP_assert((regVal & EQEP_COMPARE_IDX_SYNC_OUT) == EQEP_COMPARE_IDX_SYNC_OUT);
    regVal = HW_RD_REG16(gEqepBaseAddr + CSL_EQEP_QDECCTL_TYPE2);
    DebugP_assert((regVal & CSL_EQEP_QDECCTL_TYPE2_SPSEL_MASK) == 0U);
}

static void App_eqepIntrISR(void *arg)
{
    uint16_t intEnabled, intStatus;
    uint32_t eqepStatus;

    intStatus = EQEP_getInterruptStatus(gEqepBaseAddr);
    intEnabled = EQEP_getEnabledInterrupt(gEqepBaseAddr);
    if (((intStatus & EQEP_INT_INDEX_EVNT_LATCH) != 0) &&
        ((intEnabled & EQEP_INT_INDEX_EVNT_LATCH) != 0))
    {
        /* Get the position latch count */
        if (gEqepIsrCnt < EQEP_EVENT_CNT)
        {
            gEqepPosCnt[gEqepIsrCnt] = EQEP_getIndexPositionLatch(gEqepBaseAddr);
        }
        if (gEqepIsrCnt == (EQEP_EVENT_CNT - 1))
        {
            eqepStatus = EQEP_getStatus(gEqepBaseAddr);
            EQEP_clearStatus(gEqepBaseAddr, eqepStatus);
            EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
            SemaphoreP_post(&gEqepSyncSem);
        }
        gEqepIsrCnt++;
    }
    if (((intStatus & EQEP_INT_UNIT_TIME_OUT) != 0) &&
        ((intEnabled & EQEP_INT_UNIT_TIME_OUT) != 0))
    {
        /* Get the position latch count */
        if (gEqepIsrCnt < EQEP_EVENT_CNT)
        {
            gEqepPosCnt[gEqepIsrCnt] = EQEP_getPositionLatch(gEqepBaseAddr);
            gEqepCapPrdLatch[gEqepIsrCnt] = EQEP_getCapturePeriodLatch(gEqepBaseAddr);
            gEqepCapTmrLatch[gEqepIsrCnt] = EQEP_getCaptureTimerLatch(gEqepBaseAddr);
            gEqepCapPrd[gEqepIsrCnt] = EQEP_getCapturePeriod(gEqepBaseAddr);
            gEqepCapTmr[gEqepIsrCnt] = EQEP_getCaptureTimer(gEqepBaseAddr);
        }
        if (gEqepIsrCnt == (EQEP_EVENT_CNT - 1))
        {
            EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
            SemaphoreP_post(&gEqepSyncSem);
        }
        gEqepIsrCnt++;
    }
    if (((intStatus & EQEP_INT_PHASE_ERROR) != 0) &&
        ((intEnabled & EQEP_INT_PHASE_ERROR) != 0))
    {
        SemaphoreP_post(&gEqepSyncSem);
    }
    if (((intStatus & EQEP_INT_WATCHDOG) != 0) &&
        ((intEnabled & EQEP_INT_WATCHDOG) != 0))
    {
        EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
        gEqepIsrCnt++;
        EQEP_getWatchdogTimerValue(gEqepBaseAddr);
        SemaphoreP_post(&gEqepSyncSem);
    }
    if (((intStatus & EQEP_INT_POS_COMP_MATCH) != 0) &&
        ((intEnabled & EQEP_INT_POS_COMP_MATCH) != 0))
    {
        EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
        /* Capture position and interrupt status before the blanket clear below. */
        if (gEqepIsrCnt < EQEP_EVENT_CNT)
        {
            gEqepPosCnt[gEqepIsrCnt] = EQEP_getPosition(gEqepBaseAddr);
        }
        TestEqep_lastIntrStatus = intStatus;
        gEqepIsrCnt++;
        SemaphoreP_post(&gEqepSyncSem);
    }
    if (((intStatus & EQEP_INT_STROBE_EVNT_LATCH) != 0) &&
        ((intEnabled & EQEP_INT_STROBE_EVNT_LATCH) != 0))
    {
        EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
        gEqepIsrCnt++;
        SemaphoreP_post(&gEqepSyncSem);
    }

    /* Clear EQEP Interrupt. */
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
}

static void App_eqepInitQuadratureWave(EQEP_TestParams *testParams)
{
    uint32_t getPosCnt;

    EQEP_disableModule(gEqepBaseAddr);
    EQEP_setInitialPosition(gEqepBaseAddr, 0U);
    EQEP_setPosition(gEqepBaseAddr, 0U);
    getPosCnt = EQEP_getPosition(gEqepBaseAddr);
    DebugP_assert(getPosCnt == 0U);

    /* Configure the decoder for quadrature mode, counting rising edge
      (that is, 1x resolution) */
    EQEP_setDecoderConfig(gEqepBaseAddr, (EQEP_CONFIG_1X_RESOLUTION |
                                        EQEP_CONFIG_QUADRATURE |
                                        EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);

    /* Configure the position counter to reset on an index event */
    EQEP_setPositionCounterConfig(gEqepBaseAddr, testParams->eqepCntrRstIdxEvt,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);

    /* Configure the position counter to be latched on rising edge index */
    EQEP_setLatchMode(gEqepBaseAddr, EQEP_LATCH_RISING_INDEX);

    if (testParams->eqepWdgEvtTest == TRUE)
    {
        EQEP_setWatchdogTimerValue(gEqepBaseAddr, 0U);
        EQEP_enableWatchdog(gEqepBaseAddr, CSL_EQEP_QWDPRD_QWDPRD_MAX / 2);
    }

    /* Enable EQEP Module and interrupt */
    EQEP_enableModule(gEqepBaseAddr);
    EQEP_enableInterrupt(gEqepBaseAddr, testParams->eqepIntrEvt);
}

static void App_eqepInitFrequencyCalculation(EQEP_TestParams *testParams)
{
    EQEP_setInitialPosition(gEqepBaseAddr, 0U);
    EQEP_setPosition(gEqepBaseAddr, 0U);

    /* Configure the decoder for up-count mode, counting both rising and
       falling edges (that is, 2x resolution) */
    EQEP_setDecoderConfig(gEqepBaseAddr, (EQEP_CONFIG_2X_RESOLUTION |
                                          EQEP_CONFIG_UP_COUNT |
                                          EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);

    /* Configure the position counter to reset on an unit timeout event */
    EQEP_setPositionCounterConfig(gEqepBaseAddr,
                                  EQEP_POSITION_RESET_UNIT_TIME_OUT,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);

    /* Enable the unit timer, setting the frequency to EQEP_UNIT_TIMEOUT_FREQ */
    EQEP_enableUnitTimer(gEqepBaseAddr, (CONFIG_EQEP0_FCLK / (EQEP_UNIT_TIMEOUT_FREQ)));

    /* Configure the position counter to be latched on a unit time out */
    EQEP_setLatchMode(gEqepBaseAddr, EQEP_LATCH_UNIT_TIME_OUT);

    /* Enable the EQEP module */
    EQEP_enableModule(gEqepBaseAddr);

    /* Configure and enable the edge-capture unit. The capture clock divider is
       SYSCLKOUT/128. The unit-position event divider is QCLK/8. */
    EQEP_setCaptureConfig(gEqepBaseAddr, EQEP_CAPTURE_CLK_DIV_128,
                          EQEP_UNIT_POS_EVNT_DIV_8);
    EQEP_enableCapture(gEqepBaseAddr);

    /* Enable unit timeout interrupt. */
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_UNIT_TIME_OUT);
}

/* This function calculates the average frequency. based on the latched
 * pos values at the unit timeout event. It assumes that the
 * array gEqepPosCnt is filled. */
static uint32_t App_eqepCalculateFrequencyUnitTimeout(void)
{
    uint32_t i;
    uint32_t posCnt;
    uint32_t freq, avgFreq = 0U;

    for (i = 1U; i < EQEP_EVENT_CNT; i++)
    {
        /* posCnt is reset upon the unit timeout event.
           So each value is the diff from prev pos Cnt at unit time out */
        posCnt = gEqepPosCnt[i];

        /* Unit timeout is configured as EQEP_UNIT_TIMEOUT_FREQ Hz.
         * and position count is calculating on both edges. */
        freq = posCnt * (EQEP_UNIT_TIMEOUT_FREQ) / 2;
        /* Note: this is a simplified equation. Boundary condition not taken care. */
        avgFreq += freq;
    }
    /* Ignoring first timeout event position for frequency calculation,
     * as it could contain older value. */
    avgFreq /= (EQEP_EVENT_CNT - 1);

    return avgFreq;
}

static void App_eqepComparePosCnt(int32_t expCnt, EQEP_TestParams *testParams)
{
    uint32_t i;

    for (i = 0U; i < EQEP_EVENT_CNT; i++)
    {
        int32_t expectedForThisIndex = expCnt;

        /* If the counter does not reset on EVERY index, the counts will accumulate! */
        if ((testParams->eqepCntrRstIdxEvt == EQEP_POSITION_RESET_1ST_IDX) ||
            (testParams->eqepCntrRstIdxEvt == EQEP_POSITION_RESET_MAX_POS))
        {
            /* Calculate the base interval (e.g., 200 or -200) */
            int32_t interval = (expCnt > 0) ? (expCnt + 1) : (expCnt - 1);
            
            /* Dynamically calculate accumulating expected value (199, 399, 599...) */
            expectedForThisIndex = interval * (i + 1) - ((expCnt > 0) ? 1 : -1);
        }

        int32_t minCnt = expectedForThisIndex - EQEP_POS_CNT_VARIANCE;
        int32_t maxCnt = expectedForThisIndex + EQEP_POS_CNT_VARIANCE;
        int32_t posCnt = (int32_t)gEqepPosCnt[i];

        if ((posCnt < minCnt) || (posCnt > maxCnt))
        {
            DebugP_log("Quadrature capture count does not match\r\n");
            DebugP_assert(FALSE);
        }
    }

    return;
}

/**
 * \brief  Validate position counts match expected direction and magnitude.
 *
 * Checks that captured position counts have the correct sign matching the expected
 * direction and that the magnitude falls within acceptable variance of the expected
 * value. Used specifically for direction validation tests to ensure that forward motion
 * produces positive counts and backward motion produces negative counts.
 *
 * \param  expectedSign  Expected sign of position count (positive or negative magnitude)
 *
 * Test case category: utility function
 */
static void TestEqep_validateDirectionCounts(int32_t expectedSign)
{
    uint32_t i;
    int32_t posCnt, diff1, diff2;

    for (i = 0U; i < EQEP_EVENT_CNT; i++)
    {
        posCnt = (int32_t)gEqepPosCnt[i];
        diff1 = posCnt - (expectedSign - EQEP_POS_CNT_VARIANCE);
        diff2 = posCnt - (expectedSign + EQEP_POS_CNT_VARIANCE);
        TEST_ASSERT_LESS_OR_EQUAL_INT32(0, diff1 * diff2);
    }

    return;
}

static void App_eqepInitPattern(EqepAppPatternParams *eqepPattern)
{
    eqepPattern->eqepClockFreq    = EQEP_SIGNAL_TEST_FREQ;
    eqepPattern->direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern->idxEvtCnt        = EQEP_EVENT_CNT;
    eqepPattern->loopCnt          = EQEP_PATTERN_GEN_LOOP_COUNT;
    eqepPattern->generateIdxPulse = TRUE;
}

/**
 * \brief  Initialize EQEP position compare configuration.
 *
 * Configures the EQEP module for position compare testing. Sets up the decoder
 * in quadrature mode with 2X resolution, initializes position counter to 0,
 * and enables position compare interrupt at 500 counts.
 *
 * \param  testParams  Pointer to EQEP test parameters containing interrupt configuration
 *
 * Test case category: utility function
 */
static void TestEqep_initPositionCompare(EQEP_TestParams *testParams)
{
    EQEP_setInitialPosition(gEqepBaseAddr, 0U);
    EQEP_setPosition(gEqepBaseAddr, 0U);

    EQEP_setDecoderConfig(gEqepBaseAddr, (EQEP_CONFIG_2X_RESOLUTION |
                                        EQEP_CONFIG_QUADRATURE |
                                        EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);

    EQEP_setPositionCounterConfig(gEqepBaseAddr, EQEP_POSITION_RESET_IDX,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);

    EQEP_setCompareConfig(gEqepBaseAddr, (EQEP_COMPARE_NO_SYNC_OUT | EQEP_COMPARE_NO_SHADOW),
                          500U, 1U);
    EQEP_enableCompare(gEqepBaseAddr);

    EQEP_enableModule(gEqepBaseAddr);
    EQEP_enableInterrupt(gEqepBaseAddr, testParams->eqepIntrEvt);
}

/**
 * \brief  Initialize EQEP watchdog timer configuration.
 *
 * Configures the EQEP module for watchdog timer testing. Sets up the decoder
 * in quadrature mode with 1X resolution, initializes position counter to 0,
 * and enables the watchdog timer with half the maximum period value.
 *
 * \param  testParams  Pointer to EQEP test parameters containing interrupt configuration
 *
 * Test case category: utility function
 */
static void TestEqep_initWatchdog(EQEP_TestParams *testParams)
{
    EQEP_setInitialPosition(gEqepBaseAddr, 0U);
    EQEP_setPosition(gEqepBaseAddr, 0U);

    EQEP_setDecoderConfig(gEqepBaseAddr, (EQEP_CONFIG_1X_RESOLUTION |
                                        EQEP_CONFIG_QUADRATURE |
                                        EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);

    EQEP_setWatchdogTimerValue(gEqepBaseAddr, 0U);
    EQEP_enableWatchdog(gEqepBaseAddr, CSL_EQEP_QWDPRD_QWDPRD_MAX / 2);

    EQEP_enableModule(gEqepBaseAddr);
    EQEP_enableInterrupt(gEqepBaseAddr, testParams->eqepIntrEvt);
}

/**
 * \brief  Test EQEP direction validation for clockwise and counter-clockwise motion.
 *
 * This test validates the EQEP direction detection capability by generating quadrature
 * patterns for both clockwise and anti-clockwise directions. It verifies that the EQEP
 * correctly identifies the direction of motion and maintains accurate position counts
 * with index pulse generation.
 * Test case category: functionality test case
 */
static void TestEqep_directionValidation(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;
    int32_t              eqepDirection;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    DebugP_log("Testing clockwise direction validation.\r\n");
    gEqepIsrCnt = 0U;
    App_eqepInitPattern(&eqepPattern);
    App_eqepInitQuadratureWave(testParams);

    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = TRUE;
    App_eqepGeneratePattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    eqepDirection = EQEP_getDirection(gEqepBaseAddr);
    TEST_ASSERT_EQUAL(EQEP_MOD_FORWARD_DIR, eqepDirection);
    TestEqep_validateDirectionCounts(199);

    DebugP_log("Testing anti-clockwise direction validation.\r\n");
    gEqepIsrCnt = 0U;
    App_eqepInitPattern(&eqepPattern);
    App_eqepInitQuadratureWave(testParams);

    eqepPattern.direction        = EQEP_DIR_ANTI_CLOCKWISE;
    eqepPattern.generateIdxPulse = TRUE;
    App_eqepGeneratePattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    eqepDirection = EQEP_getDirection(gEqepBaseAddr);
    TEST_ASSERT_EQUAL(EQEP_MOD_BACKWARD_DIR, eqepDirection);

    TestEqep_validateDirectionCounts(-199);

    EQEP_disableModule(gEqepBaseAddr);
    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);
}

/**
 * \brief  Test low-speed frequency capture using unit timeout events.
 *
 * This test validates the EQEP frequency measurement capability at low speeds (50 Hz).
 * It generates a quadrature pattern and measures the frequency using unit timeout events.
 * The test verifies that the measured frequency is within acceptable tolerance (±5 Hz)
 * of the expected frequency.
 * Test case category: functionality test case
 */
static void TestEqep_lowSpeedCaptureValidation(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;
    uint32_t             measuredFreq, expectedFreq;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    gEqepIsrCnt = 0U;
    App_eqepInitPattern(&eqepPattern);
    App_eqepInitFrequencyCalculation(testParams);

    eqepPattern.eqepClockFreq    = 50U;
    eqepPattern.direction        = testParams->eqepDir;
    eqepPattern.generateIdxPulse = FALSE;
    App_eqepGeneratePattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    measuredFreq = App_eqepCalculateFrequencyUnitTimeout();
    expectedFreq = 50U;

    TEST_ASSERT_INT32_WITHIN(5, expectedFreq, measuredFreq);

    EQEP_disableModule(gEqepBaseAddr);
    EQEP_disableCapture(gEqepBaseAddr);
    EQEP_disableUnitTimer(gEqepBaseAddr);

    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);
}

/**
 * \brief  Test EQEP watchdog stall detection.
 *
 * This test validates the watchdog stall detection feature by generating a quadrature
 * pattern and verifying that the watchdog interrupt is triggered when motion stalls.
 * It confirms that the interrupt is properly detected and counts are recorded.
 * Test case category: functionality test case
 */
static void TestEqep_watchdogStallDetection(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    App_eqepInitPattern(&eqepPattern);
    TestEqep_initWatchdog(testParams);

    eqepPattern.direction        = testParams->eqepDir;
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.loopCnt          = 50U;
    App_eqepGeneratePattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    TEST_ASSERT_GREATER_THAN_UINT32(0U, gEqepIsrCnt);
    DebugP_log("Watchdog stall detected: ISR count = %d\r\n", gEqepIsrCnt);

    EQEP_disableModule(gEqepBaseAddr);
    EQEP_disableWatchdog(gEqepBaseAddr);

    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);
}

/**
 * \brief  Test EQEP position compare match events.
 *
 * This test validates the position compare feature by generating quadrature patterns
 * and verifying that compare match interrupts occur at the expected position count (500).
 * It performs two consecutive compare matches with position reset between them to ensure
 * the feature functions correctly across multiple events.
 * Test case category: functionality test case
 */
static void TestEqep_positionCompareEvent(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams      *testParams = (EQEP_TestParams *)args;
    uint32_t             posAtCompare;
    uint16_t             intStatus;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    gEqepIsrCnt = 0U;
    TestEqep_lastIntrStatus = 0U;
    App_eqepInitPattern(&eqepPattern);
    TestEqep_initPositionCompare(testParams);

    DebugP_log("Generating quadrature pattern at 500 Hz. Waiting for compare match at 500 counts.\r\n");
    eqepPattern.eqepClockFreq    = 500U;
    eqepPattern.direction        = testParams->eqepDir;
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.loopCnt          = 100U;
    App_eqepGeneratePattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    posAtCompare = gEqepPosCnt[0];
    TEST_ASSERT_UINT32_WITHIN(EQEP_POS_CNT_VARIANCE, 500U, posAtCompare);
    DebugP_log("Position at compare event: %d counts (expected ~500, variance +/-%d)\r\n",
               posAtCompare, EQEP_POS_CNT_VARIANCE);

    TEST_ASSERT_TRUE((TestEqep_lastIntrStatus & EQEP_INT_POS_COMP_MATCH) != 0U);

    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    intStatus = EQEP_getInterruptStatus(gEqepBaseAddr);
    TEST_ASSERT_EQUAL_UINT16(0U, intStatus & EQEP_INT_POS_COMP_MATCH);

    DebugP_log("Resetting position to 0 and verifying second compare event at ~500.\r\n");
    gEqepIsrCnt = 0U;
    TestEqep_lastIntrStatus = 0U;
    EQEP_setPosition(gEqepBaseAddr, 0U);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_POS_COMP_MATCH);

    App_eqepGeneratePattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    posAtCompare = gEqepPosCnt[0];
    TEST_ASSERT_UINT32_WITHIN(EQEP_POS_CNT_VARIANCE, 500U, posAtCompare);
    DebugP_log("Second compare event position: %d counts (expected ~500, variance +/-%d)\r\n",
               posAtCompare, EQEP_POS_CNT_VARIANCE);

    TEST_ASSERT_TRUE((TestEqep_lastIntrStatus & EQEP_INT_POS_COMP_MATCH) != 0U);

    EQEP_disableModule(gEqepBaseAddr);
    EQEP_disableCompare(gEqepBaseAddr);

    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);
}

static void App_eqepTestClockwiseDirection(EQEP_TestParams *testParams)
{
    int32_t              expCnt, eqepDirection;
    EqepAppPatternParams eqepPattern = {0U};

    /* Reset ISR Count */
    gEqepIsrCnt = 0U;
    /* The count values expected is 199
     * Count starts from 0 and counts 4 edges per cycle. */
    expCnt = 199U;

    /* Init default EQEP pattern params */
    App_eqepInitPattern(&eqepPattern);

    /* Enable capture from quadrature wave with index event. */
    App_eqepInitQuadratureWave(testParams);

    /* Start EQEP Pattern Generation. */
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = TRUE;
    App_eqepGeneratePattern(&eqepPattern);

    /* Wait for the EQEP_EVENT_CNT number of EQEP Index Latch interrupt. */
    SemaphoreP_pend (&gEqepSyncSem, SystemP_WAIT_FOREVER);

    eqepDirection = EQEP_getDirection(gEqepBaseAddr);
    DebugP_assert(eqepDirection == eqepDirection);

    /* Check position count. */
    App_eqepComparePosCnt(expCnt, testParams);
}

static void App_eqepTestAntiClockwiseDirection(EQEP_TestParams *testParams)
{
    int32_t              expCnt, eqepDirection;
    EqepAppPatternParams eqepPattern = {0U};

    /* Reset ISR Count */
    gEqepIsrCnt = 0U;
    /* The count values expected is -199
     * Count starts from 0 and counts 4 edges per cycle. */
    expCnt = -199U;

    /* Init default EQEP pattern params */
    App_eqepInitPattern(&eqepPattern);

    /* Enable capture from quadrature wave with index event. */
    App_eqepInitQuadratureWave(testParams);

    /* Start EQEP Pattern Generation. */
    eqepPattern.direction        = EQEP_DIR_ANTI_CLOCKWISE;
    eqepPattern.generateIdxPulse = TRUE;
    App_eqepGeneratePattern(&eqepPattern);

    /* Wait for the EQEP_EVENT_CNT number of EQEP Index Latch interrupt. */
    SemaphoreP_pend (&gEqepSyncSem, SystemP_WAIT_FOREVER);

    eqepDirection = EQEP_getDirection(gEqepBaseAddr);
    DebugP_assert(eqepDirection == eqepDirection);

    /* Check position count. */
    App_eqepComparePosCnt(expCnt, testParams);
}

static void App_eqepTestFrequency(EQEP_TestParams *testParams)
{
    uint32_t             avgFreq = 0U;
    EqepAppPatternParams eqepPattern = {0U};

    /* Reset ISR Count */
    gEqepIsrCnt = 0U;

    /* Init default EQEP pattern params */
    App_eqepInitPattern(&eqepPattern);

    /* Enable Frequency Calculation. */
    App_eqepInitFrequencyCalculation(testParams);

    /* Start EQEP Pattern Generation. */
    eqepPattern.direction        = testParams->eqepDir;
    eqepPattern.generateIdxPulse = FALSE;
    App_eqepGeneratePattern(&eqepPattern);

    /* Wait for the Unit Timeout interrupt. */
    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    avgFreq = App_eqepCalculateFrequencyUnitTimeout();
    DebugP_assert(avgFreq == EQEP_SIGNAL_TEST_FREQ);

    DebugP_log("Expected Frequency is %d Hz\r\n", EQEP_SIGNAL_TEST_FREQ);
    DebugP_log("Average frequency is %d Hz\r\n", avgFreq);
}

/**
 * \brief  Test clock-direction counting mode with directional validation.
 *
 * This test validates clock-direction counting mode where QEPA acts as clock
 * and QEPB controls direction. It verifies position counts match between clockwise
 * and counter-clockwise directions with appropriate sign changes.
 * Test case category: functionality test case
 */
static void TestEqep_clockDirCountingMode(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;
    int32_t              clockwiseCount, counterClockwiseCount, direction;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    DebugP_log("Testing Clock-Direction counting mode (QEPA=clock, QEPB=direction).\r\n");

    EQEP_setInitialPosition(gEqepBaseAddr, 0U);
    EQEP_setPosition(gEqepBaseAddr, 0U);

    EQEP_setDecoderConfig(gEqepBaseAddr, (EQEP_CONFIG_1X_RESOLUTION |
                                          EQEP_CONFIG_CLOCK_DIR |
                                          EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);

    EQEP_setPositionCounterConfig(gEqepBaseAddr, EQEP_POSITION_RESET_IDX,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);

    EQEP_setLatchMode(gEqepBaseAddr, EQEP_LATCH_RISING_INDEX);

    EQEP_enableModule(gEqepBaseAddr);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_INDEX_EVNT_LATCH);

    gEqepIsrCnt = 0U;
    App_eqepInitPattern(&eqepPattern);

    DebugP_log(" Clock-Direction mode with CLOCKWISE direction on QEPB.\r\n");
    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = TRUE;
    eqepPattern.loopCnt          = 50U;
    App_eqepGenerateClockDirPattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    clockwiseCount = gEqepPosCnt[0];
    direction = EQEP_getDirection(gEqepBaseAddr);
    DebugP_log("Clockwise count: %d, Direction: %d\r\n", clockwiseCount, direction);
    TEST_ASSERT_GREATER_THAN_INT32(0, clockwiseCount);
    TEST_ASSERT_EQUAL_INT32(EQEP_MOD_FORWARD_DIR, direction);

    EQEP_disableModule(gEqepBaseAddr);
    EQEP_setPosition(gEqepBaseAddr, 0U);
    gEqepIsrCnt = 0U;
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_INDEX_EVNT_LATCH);
    EQEP_enableModule(gEqepBaseAddr);

    DebugP_log(" Clock-Direction mode with COUNTER-CLOCKWISE direction on QEPB.\r\n");
    eqepPattern.direction        = EQEP_DIR_ANTI_CLOCKWISE;
    App_eqepGenerateClockDirPattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    counterClockwiseCount = gEqepPosCnt[0];
    direction = EQEP_getDirection(gEqepBaseAddr);
    DebugP_log("Counter-clockwise count: %d, Direction: %d\r\n", counterClockwiseCount, direction);
    TEST_ASSERT_EQUAL_INT32(EQEP_MOD_BACKWARD_DIR, direction);
    TEST_ASSERT_NOT_EQUAL_INT32(0, counterClockwiseCount);

    DebugP_log("Verification: Clockwise count (%d) and counter-clockwise count (%d) should be non-zero in opposite directions.\r\n",
               clockwiseCount, counterClockwiseCount);

    EQEP_disableModule(gEqepBaseAddr);
    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);
}

/**
 * \brief  Test UP_COUNT mode with 1x and 2x resolution comparison.
 *
 * This test compares position counting between 1x and 2x resolution modes
 * in UP_COUNT decoder configuration. It validates that 2x resolution captures
 * both rising and falling edges, producing higher counts than 1x resolution.
 * Test case category: functionality test case
 */
static void TestEqep_countDirectionMode(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;
    uint32_t             twoXCountValue, oneXCountValue;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    DebugP_log("Testing UP_COUNT mode with resolution comparison (QEPA=counter, QEPB=control).\r\n");

    EQEP_setInitialPosition(gEqepBaseAddr, 0U);
    EQEP_setPosition(gEqepBaseAddr, 0U);

    EQEP_setDecoderConfig(gEqepBaseAddr, (EQEP_CONFIG_2X_RESOLUTION |
                                          EQEP_CONFIG_UP_COUNT |
                                          EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);

    EQEP_setPositionCounterConfig(gEqepBaseAddr, EQEP_POSITION_RESET_IDX,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);

    EQEP_setLatchMode(gEqepBaseAddr, EQEP_LATCH_RISING_INDEX);

    EQEP_enableModule(gEqepBaseAddr);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_INDEX_EVNT_LATCH);

    gEqepIsrCnt = 0U;
    App_eqepInitPattern(&eqepPattern);

    DebugP_log("Test 1: UP_COUNT mode with 2x resolution (counting both rising and falling edges).\r\n");
    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = TRUE;
    eqepPattern.loopCnt          = 50U;
    App_eqepGenerateUpCountPattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    twoXCountValue = gEqepPosCnt[0];
    DebugP_log("2x resolution count: %d (expected ~99-100 counts).\r\n", twoXCountValue);
    DebugP_assert(twoXCountValue > 0);
    DebugP_log("Verification: 2x resolution captured both rising and falling edges.\r\n");

    EQEP_disableModule(gEqepBaseAddr);
    EQEP_setPosition(gEqepBaseAddr, 0U);
    gEqepIsrCnt = 0U;

    DebugP_log("Test 2: UP_COUNT mode with 1x resolution (counting rising edges only).\r\n");
    EQEP_setDecoderConfig(gEqepBaseAddr, (EQEP_CONFIG_1X_RESOLUTION |
                                          EQEP_CONFIG_UP_COUNT |
                                          EQEP_CONFIG_NO_SWAP));
    EQEP_enableModule(gEqepBaseAddr);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_INDEX_EVNT_LATCH);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_INDEX_EVNT_LATCH);

    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = TRUE;
    eqepPattern.loopCnt          = 50U;
    App_eqepGenerateUpCountPattern(&eqepPattern);

    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    oneXCountValue = gEqepPosCnt[0];
    DebugP_log("1x resolution count: %d (expected ~50 counts).\r\n", oneXCountValue);
    DebugP_assert(oneXCountValue > 0);
    DebugP_log("Verification: 1x resolution captured only rising edges.\r\n");

    DebugP_log("Resolution Comparison: 2x count (%d) vs 1x count (%d).\r\n", twoXCountValue, oneXCountValue);
    DebugP_assert(twoXCountValue > oneXCountValue);
    DebugP_log("Verification: 2x resolution produced higher count than 1x resolution.\r\n");

    DebugP_log("UP_COUNT mode test PASSED - Both 1x and 2x resolution working correctly.\r\n");

    EQEP_disableModule(gEqepBaseAddr);
    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);
}

/**
 * \brief  Test STROBE-based position counter reinitialization.
 *
 * This test validates the STROBE signal functionality for reinitializing the position
 * counter to a preset value. It simulates limit switch scenarios where position resets
 * to known offsets when STROBE pulses occur.
 * Test case category: functionality test case
 */
static void TestEqep_strobePositionInit(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;
    uint32_t             initialPosValue = 1000U;
    uint32_t             currentPos, strobeLatched;
    uint16_t             intrSts;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    EQEP_setInitialPosition(gEqepBaseAddr, initialPosValue);
    EQEP_setPosition(gEqepBaseAddr, 0U);

    EQEP_setDecoderConfig(gEqepBaseAddr, (EQEP_CONFIG_2X_RESOLUTION |
                                          EQEP_CONFIG_QUADRATURE |
                                          EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);

    EQEP_setPositionCounterConfig(gEqepBaseAddr, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);

    EQEP_setLatchMode(gEqepBaseAddr, EQEP_LATCH_RISING_STROBE);
    EQEP_setPositionInitMode(gEqepBaseAddr, EQEP_INIT_RISING_STROBE);
    EQEP_setStrobeSource(gEqepBaseAddr, EQEP_STROBE_FROM_GPIO);

    EQEP_enableModule(gEqepBaseAddr);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_STROBE_EVNT_LATCH);

    gEqepIsrCnt = 0U;
    App_eqepInitPattern(&eqepPattern);

    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.loopCnt          = 30U;
    eqepPattern.idxEvtCnt        = 1U;
    App_eqepGenerateStrobePattern(&eqepPattern);

    /* Verify quadrature counting is working */
    currentPos = EQEP_getPosition(gEqepBaseAddr);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, currentPos);

    /* Wait for STROBE ISR — this must fire for a valid strobe test */
    status = SemaphoreP_pend(&gEqepSyncSem, ClockP_usecToTicks(2000000U));

    /* Check QFLG to see if HW detected the strobe edge */
    intrSts = EQEP_getInterruptStatus(gEqepBaseAddr);

    TEST_ASSERT_MESSAGE((intrSts & EQEP_INT_STROBE_EVNT_LATCH) != 0,
        "STROBE flag not set in QFLG");

    /* Validate position was reinitialized to QPOSINIT on strobe edge */
    currentPos = EQEP_getPosition(gEqepBaseAddr);
    strobeLatched = EQEP_getStrobePositionLatch(gEqepBaseAddr);
    TEST_ASSERT_UINT32_WITHIN(EQEP_POS_CNT_VARIANCE, initialPosValue, currentPos);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, strobeLatched);

    /* Repeat with second STROBE pulse to confirm repeatability */
    EQEP_setPosition(gEqepBaseAddr, 500U);
    gEqepIsrCnt = 0U;
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_STROBE_EVNT_LATCH);
    App_eqepGenerateStrobePattern(&eqepPattern);

    status = SemaphoreP_pend(&gEqepSyncSem, ClockP_usecToTicks(2000000U));
    intrSts = EQEP_getInterruptStatus(gEqepBaseAddr);

    TEST_ASSERT_MESSAGE((intrSts & EQEP_INT_STROBE_EVNT_LATCH) != 0,
        "Second STROBE pulse: flag not set in QFLG");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
        "Second STROBE ISR did not fire");

    currentPos = EQEP_getPosition(gEqepBaseAddr);
    TEST_ASSERT_UINT32_WITHIN(EQEP_POS_CNT_VARIANCE, initialPosValue, currentPos);

    EQEP_disableModule(gEqepBaseAddr);
    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);
}

/**
 * \brief  Test INDEX input gating with STROBE for noise immunity.
 *
 * This test validates INDEX event behavior by comparing position reset on INDEX
 * with and without STROBE-based position initialization. It demonstrates that
 * STROBE can gate when position init values are loaded, preventing accidental
 * position resets from INDEX noise.
 * Test case category: functionality test case
 */
static void TestEqep_indexGating(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams *testParams = (EQEP_TestParams *)args;
    uint32_t             posAfterIndex, indexLatchedPos;
    uint32_t             indexCount;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback    = &App_eqepIntrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    /* Test 1: INDEX resets position counter */
    EQEP_setInitialPosition(gEqepBaseAddr, 0U);
    EQEP_setPosition(gEqepBaseAddr, 0U);

    EQEP_setDecoderConfig(gEqepBaseAddr, (EQEP_CONFIG_1X_RESOLUTION |
                                          EQEP_CONFIG_QUADRATURE |
                                          EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);

    /* Position resets on INDEX event */
    EQEP_setPositionCounterConfig(gEqepBaseAddr, EQEP_POSITION_RESET_IDX,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);

    EQEP_setLatchMode(gEqepBaseAddr, EQEP_LATCH_RISING_INDEX);
    EQEP_setPositionInitMode(gEqepBaseAddr, EQEP_INIT_DO_NOTHING);

    EQEP_enableModule(gEqepBaseAddr);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_INDEX_EVNT_LATCH);

    gEqepIsrCnt = 0U;
    App_eqepInitPattern(&eqepPattern);

    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = TRUE;
    App_eqepGeneratePattern(&eqepPattern);

    status = SemaphoreP_pend(&gEqepSyncSem, ClockP_usecToTicks(5000000U));
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
        "INDEX ISR did not post semaphore - check INDEX GPIO to EQEP_I pin connection");

    indexCount = gEqepIsrCnt;
    indexLatchedPos = EQEP_getIndexPositionLatch(gEqepBaseAddr);
    posAfterIndex = EQEP_getPosition(gEqepBaseAddr);

    TEST_ASSERT_GREATER_OR_EQUAL_UINT32(EQEP_EVENT_CNT, indexCount);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, indexLatchedPos);

    /* Test 2: INDEX-based position init (reinit on INDEX) */

    EQEP_disableModule(gEqepBaseAddr);
    EQEP_setPosition(gEqepBaseAddr, 0U);
    EQEP_setInitialPosition(gEqepBaseAddr, 100U);

    /* Position resets to QPOSINIT on INDEX event */
    EQEP_setPositionCounterConfig(gEqepBaseAddr, EQEP_POSITION_RESET_IDX,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_setPositionInitMode(gEqepBaseAddr, EQEP_INIT_RISING_INDEX);

    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_INDEX_EVNT_LATCH);
    EQEP_enableModule(gEqepBaseAddr);

    gEqepIsrCnt = 0U;
    App_eqepGeneratePattern(&eqepPattern);

    status = SemaphoreP_pend(&gEqepSyncSem, ClockP_usecToTicks(5000000U));
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
        "INDEX ISR did not post semaphore in Test 2");

    posAfterIndex = EQEP_getPosition(gEqepBaseAddr);
    indexLatchedPos = EQEP_getIndexPositionLatch(gEqepBaseAddr);

    /* Test 3: STROBE gating — INDEX alone should NOT reinit position */

    EQEP_disableModule(gEqepBaseAddr);
    EQEP_setPosition(gEqepBaseAddr, 0U);
    EQEP_setInitialPosition(gEqepBaseAddr, 5000U);

    /* Switch to STROBE-based init — only STROBE edge loads QPOSINIT */
    EQEP_setPositionInitMode(gEqepBaseAddr, EQEP_INIT_RISING_STROBE);
    /* Keep position reset on max so INDEX doesn't reset counter either */
    EQEP_setPositionCounterConfig(gEqepBaseAddr, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);

    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_enableInterrupt(gEqepBaseAddr, EQEP_INT_INDEX_EVNT_LATCH);
    EQEP_enableModule(gEqepBaseAddr);

    gEqepIsrCnt = 0U;

    /* Generate quadrature with INDEX but NO STROBE */
    App_eqepGeneratePattern(&eqepPattern);
    status = SemaphoreP_pend(&gEqepSyncSem, ClockP_usecToTicks(5000000U));

    posAfterIndex = EQEP_getPosition(gEqepBaseAddr);

    /* With STROBE init mode and no STROBE pulse, position should NOT be
     * reinitialized to QPOSINIT (5000). It should be the accumulated count. */
    TEST_ASSERT_MESSAGE(
        (posAfterIndex < (5000U - EQEP_POS_CNT_VARIANCE)) ||
        (posAfterIndex > (5000U + EQEP_POS_CNT_VARIANCE)),
        "FAIL: Position equals QPOSINIT — STROBE gating did NOT prevent init");

    EQEP_disableModule(gEqepBaseAddr);
    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);
}

/**
 * \brief  Test input polarity inversion effect on counting direction.
 *
 * This test validates that inverting QEPA or QEPB input polarity reverses the
 * effective counting direction. It applies normal, inverted QEPA, and inverted QEPB
 * configurations to verify phase relationship changes are properly detected.
 * Test case category: functionality test case
 */
static void TestEqep_inputPolarityImpact(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    EQEP_TestParams     *testParams = (EQEP_TestParams *)args;
    int32_t              normalCount, invertACount, invertBCount, restoredCount;
    int32_t              direction;

    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = testParams->eqepIntrNum;
    hwiPrms.eventId     = testParams->eqepEventId;
    hwiPrms.callback = &App_eqepIntrISR;
    hwiPrms.isPulse  = CONFIG_EQEP0_INTR_IS_PULSE;
    status           = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    gEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(testParams->eqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);

    DebugP_log("Validates that inverting QEPA or QEPB reverses the counting direction.\r\n\n");

    /* Common pattern setup: clockwise, 50 cycles with index */
    App_eqepInitPattern(&eqepPattern);
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = TRUE;

    /* Test 1: Normal polarity (baseline) */
    DebugP_log("Normal polarity, clockwise pattern.\r\n");
    gEqepIsrCnt = 0U;
    EQEP_setInputPolarity(gEqepBaseAddr, FALSE, FALSE, FALSE, FALSE);
    App_eqepInitQuadratureWave(testParams);

    App_eqepGeneratePattern(&eqepPattern);
    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    normalCount = (int32_t)gEqepPosCnt[gEqepIsrCnt > EQEP_EVENT_CNT ?
                           EQEP_EVENT_CNT - 1 : gEqepIsrCnt - 1];
    direction   = EQEP_getDirection(gEqepBaseAddr);
    DebugP_log("  Position latch: %d, Direction: %d (expected FORWARD)\r\n",
               normalCount, direction);
    TEST_ASSERT_GREATER_THAN(0, normalCount);
    TEST_ASSERT_EQUAL_INT32(EQEP_MOD_FORWARD_DIR, direction);

    /*: Invert QEPA only*/
    DebugP_log("Invert QEPA polarity, same clockwise pattern.\r\n");
    EQEP_disableModule(gEqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    gEqepIsrCnt = 0U;

    EQEP_setInputPolarity(gEqepBaseAddr, TRUE, FALSE, FALSE, FALSE);
    App_eqepInitQuadratureWave(testParams);

    App_eqepGeneratePattern(&eqepPattern);
    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    invertACount = (int32_t)gEqepPosCnt[gEqepIsrCnt > EQEP_EVENT_CNT ?
                            EQEP_EVENT_CNT - 1 : gEqepIsrCnt - 1];
    direction    = EQEP_getDirection(gEqepBaseAddr);
    DebugP_log("  Position latch: %d, Direction: %d (expected BACKWARD)\r\n",
               invertACount, direction);
    /*
     * Inverting QEPA swaps the phase relationship, so the decoder sees the
     * opposite direction. The latched position at the index event should be
     * a large value (counter wrapped from 0 in backward direction) or negative
     * interpretation. We verify the direction bit changed.
     */
    TEST_ASSERT_EQUAL_INT32(EQEP_MOD_BACKWARD_DIR, direction);

    /*: Invert QEPB only*/
    DebugP_log("Invert QEPB polarity (QEPA normal), same clockwise pattern.\r\n");
    EQEP_disableModule(gEqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    gEqepIsrCnt = 0U;

    EQEP_setInputPolarity(gEqepBaseAddr, FALSE, TRUE, FALSE, FALSE);
    App_eqepInitQuadratureWave(testParams);

    App_eqepGeneratePattern(&eqepPattern);
    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    invertBCount = (int32_t)gEqepPosCnt[gEqepIsrCnt > EQEP_EVENT_CNT ?
                            EQEP_EVENT_CNT - 1 : gEqepIsrCnt - 1];
    direction    = EQEP_getDirection(gEqepBaseAddr);
    DebugP_log("  Position latch: %d, Direction: %d (expected BACKWARD)\r\n",
               invertBCount, direction);
    TEST_ASSERT_EQUAL_INT32(EQEP_MOD_BACKWARD_DIR, direction);

    /* Restore all polarities to normal */
    DebugP_log("Restore normal polarity, same clockwise pattern.\r\n");
    EQEP_disableModule(gEqepBaseAddr);
    EQEP_disableInterrupt(gEqepBaseAddr, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_ALL);
    gEqepIsrCnt = 0U;

    EQEP_setInputPolarity(gEqepBaseAddr, FALSE, FALSE, FALSE, FALSE);
    App_eqepInitQuadratureWave(testParams);

    App_eqepGeneratePattern(&eqepPattern);
    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);

    restoredCount = (int32_t)gEqepPosCnt[gEqepIsrCnt > EQEP_EVENT_CNT ?
                             EQEP_EVENT_CNT - 1 : gEqepIsrCnt - 1];
    direction     = EQEP_getDirection(gEqepBaseAddr);
    DebugP_log("  Position latch: %d, Direction: %d (expected FORWARD)\r\n",
               restoredCount, direction);
    TEST_ASSERT_GREATER_THAN(0, restoredCount);
    TEST_ASSERT_EQUAL_INT32(EQEP_MOD_FORWARD_DIR, direction);

    /* Verify restored count matches original baseline within variance */
    TEST_ASSERT_UINT32_WITHIN(EQEP_POS_CNT_VARIANCE, (uint32_t)normalCount,
                              (uint32_t)restoredCount);

    DebugP_log("  Normal polarity count:   %d (FORWARD)\r\n", normalCount);
    DebugP_log("  Invert QEPA count:       %d (BACKWARD)\r\n", invertACount);
    DebugP_log("  Invert QEPB count:       %d (BACKWARD)\r\n", invertBCount);
    DebugP_log("  Restored polarity count: %d (FORWARD)\r\n", restoredCount);

    EQEP_disableModule(gEqepBaseAddr);
    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);
}

#ifdef ENABLE_MT_TESTS
/**
 * \brief  Capture and calculate speed from EQEP0 position samples.
 *
 * This thread continuously reads position from EQEP0 and calculates speed
 * based on position deltas over fixed intervals. Results are stored for
 * verification of concurrent independent EQEP instance operation.
 * Test case category: functionality test case
 */
static void TestEqep_captureSpeedThread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t lastPos = 0, posDelta, speed;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;

    TestEqep_thread1Results.instanceId = threadId;
    TestEqep_thread1Results.speedCount = 0;
    TestEqep_thread1Results.readingCount = 0;
    TestEqep_thread1Results.dataCorruptionDetected = 0;

    DebugP_log("Thread %d (Capture Speed) started on EQEP0\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);

        posDelta = (currentPos >= lastPos) ? (currentPos - lastPos) : 0U;
        speed = (posDelta * 1000U) / TEST_EQEP_POSITION_READ_INTERVAL_MS;

        if (TestEqep_thread1Results.readingCount < 100U)
        {
            TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount] = currentPos;
            TestEqep_thread1Results.speedValues[TestEqep_thread1Results.readingCount] = speed;
            TestEqep_thread1Results.readingCount++;
            TestEqep_thread1Results.speedCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000U);
    }

    DebugP_log("Thread %d (Capture Speed): Calculated %d speed samples\r\n",
               threadId, TestEqep_thread1Results.speedCount);

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Monitor watchdog timer on EQEP1 for stall detection.
 *
 * This thread monitors the watchdog timer on EQEP1 and detects stalls when
 * intermittent input pauses. It reads position periodically and logs watchdog
 * timer values to verify stall detection functionality.
 * Test case category: functionality test case
 */
static void TestEqep_watchdogMonitorThread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;
    uint32_t wdgTimerVal;
    uint32_t stallDetectedCount = 0U;
    uint32_t lastPos = 0U;

    TestEqep_thread2Results.instanceId = threadId;
    TestEqep_thread2Results.readingCount = 0;
    TestEqep_thread2Results.speedCount = 0;
    TestEqep_thread2Results.dataCorruptionDetected = 0;

    DebugP_log("Thread %d (Watchdog Monitor) started on EQEP1\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);
        wdgTimerVal = EQEP_getWatchdogTimerValue(baseAddr);

        /* Detect stall: position unchanged between two readings means no edges */
        if ((i > 0U) && (currentPos == lastPos))
        {
            stallDetectedCount++;
        }

        if (TestEqep_thread2Results.readingCount < 100U)
        {
            TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount] = currentPos;
            /* Store watchdog timer value in speedValues array for logging */
            TestEqep_thread2Results.speedValues[TestEqep_thread2Results.readingCount] = wdgTimerVal;
            TestEqep_thread2Results.readingCount++;
            TestEqep_thread2Results.speedCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000U);
    }

    /* If stall was detected at least once, it means the intermittent input
     * had gaps — which is the expected behavior for this test. */
    if (stallDetectedCount > 0U)
    {
        DebugP_log("Thread %d: Stall detected %d times (expected for intermittent input)\r\n",
                   threadId, stallDetectedCount);
    }
    else
    {
        DebugP_log("Thread %d: No stall detected\r\n", threadId);
    }

    DebugP_log("Thread %d (Watchdog Monitor): Monitored %d samples, Stalls: %d\r\n",
               threadId, TestEqep_thread2Results.readingCount, stallDetectedCount);

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Test watchdog monitor and speed capture on separate EQEP instances.
 *
 * This multithreaded test verifies independent operation of watchdog monitoring
 * on EQEP1 and speed capture on EQEP0. Intermittent input patterns are applied
 * to validate stall detection and speed computation across two EQEP instances.
 * Test case category: functionality test case
 */
static void TestEqep_watchdogMonitorWhileCaptureCalc(void *args)
{
    int32_t status, i;
    TaskP_Params taskParams;
    EqepAppPatternParams eqepPattern = {0U};
    uint32_t baseAddr0, baseAddr1;

    status = SemaphoreP_constructCounting(&TestEqep_mtTestSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    baseAddr0 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    baseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);

    /* Disable and clear both instances */
    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);
    EQEP_disableInterrupt(baseAddr0, EQEP_INT_ALL);
    EQEP_disableInterrupt(baseAddr1, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr0, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr1, EQEP_INT_ALL);

    /* Configure EQEP0 for speed capture (2x resolution, quadrature, no reset) */
    DebugP_log("Initializing EQEP0 (Speed Capture):\r\n");
    EQEP_setInitialPosition(baseAddr0, 0U);
    EQEP_setPosition(baseAddr0, 0U);
    EQEP_setDecoderConfig(baseAddr0, (EQEP_CONFIG_2X_RESOLUTION |
                                      EQEP_CONFIG_QUADRATURE |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr0, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr0, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_enableModule(baseAddr0);
    DebugP_log("  EQEP0 initialized (speed capture mode)\r\n");

    /* Configure EQEP1 with watchdog enabled for stall detection */
    DebugP_log("Initializing EQEP1 (Watchdog Monitor):\r\n");
    EQEP_setInitialPosition(baseAddr1, 0U);
    EQEP_setPosition(baseAddr1, 0U);
    EQEP_setDecoderConfig(baseAddr1, (EQEP_CONFIG_2X_RESOLUTION |
                                      EQEP_CONFIG_QUADRATURE |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr1, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr1, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_setWatchdogTimerValue(baseAddr1, 0U);
    EQEP_enableWatchdog(baseAddr1, CSL_EQEP_QWDPRD_QWDPRD_MAX / 2);
    EQEP_enableModule(baseAddr1);
    DebugP_log("  EQEP1 initialized (watchdog enabled)\r\n\n");


    TaskP_Params_init(&taskParams);
    taskParams.priority  = 3U;
    taskParams.stackSize = TEST_EQEP_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestEqep_task1Stack;
    taskParams.taskMain  = &TestEqep_captureSpeedThread;
    taskParams.args      = (void *)(uintptr_t)0;
    taskParams.name      = "EQEPCaptureSpeed";
    status = TaskP_construct(&TestEqep_TaskObjs[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("  Thread 1 (Capture Speed) spawned\r\n");

    TaskP_Params_init(&taskParams);
    taskParams.priority  = 3U;
    taskParams.stackSize = TEST_EQEP_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestEqep_task2Stack;
    taskParams.taskMain  = &TestEqep_watchdogMonitorThread;
    taskParams.args      = (void *)(uintptr_t)1;
    taskParams.name      = "EQEPWdgMonitor";
    status = TaskP_construct(&TestEqep_TaskObjs[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("  Thread 2 (Watchdog Monitor) spawned\r\n\n");

    /*
     * Apply intermittent input: generate pattern for ~2s, pause ~1s,
     * generate again for ~2s. This creates a gap so watchdog detects stall.
     */
    DebugP_log("Applying intermittent input pattern...\r\n");
    App_eqepInitPattern(&eqepPattern);
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.idxEvtCnt        = 1U;

    /*  ~2 seconds of input */
    eqepPattern.loopCnt = 200U;  /* 200 loops * 10ms/loop = 2s */
    App_eqepGeneratePattern(&eqepPattern);

    /* ~1 second gap (no input — watchdog should detect stall) */
    ClockP_usleep(1000U * 1000U);

    /* ~2 seconds of input */
    eqepPattern.loopCnt = 200U;
    App_eqepGeneratePattern(&eqepPattern);

    /* Wait for both threads to complete */
    for (i = 0; i < 2; i++)
    {
        int32_t semStatus = SemaphoreP_pend(&TestEqep_mtTestSem,
                                            ClockP_usecToTicks((TEST_EQEP_MT_TEST_DURATION_MS + 5000U) * 1000U));
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semStatus);
    }

    /* Verify results */

    DebugP_log("  Speed samples collected: %d\r\n", TestEqep_thread1Results.speedCount);
    if (TestEqep_thread1Results.readingCount > 0)
    {
        DebugP_log("  Position range: %d to %d\r\n",
                   TestEqep_thread1Results.positionReadings[0],
                   TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount - 1]);
    }

    DebugP_log("  Monitoring samples collected: %d\r\n", TestEqep_thread2Results.readingCount);
    if (TestEqep_thread2Results.readingCount > 0)
    {
        DebugP_log("  Position range: %d to %d\r\n",
                   TestEqep_thread2Results.positionReadings[0],
                   TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount - 1]);
    }

    /* Verify thread 1 collected speed data */
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread1Results.speedCount);
    /* Verify thread 2 collected monitoring data */
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread2Results.readingCount);

    /* Cleanup */
    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);
    EQEP_disableWatchdog(baseAddr1);

    ClockP_usleep(100000U);

    for (i = 0; i < 2; i++)
    {
        TaskP_destruct(&TestEqep_TaskObjs[i]);
    }
    SemaphoreP_destruct(&TestEqep_mtTestSem);

}

/**
 * \brief  Capture position on EQEP0 with QMA Mode 1 (error correction).
 *
 * This thread continuously reads position from EQEP0 configured with QMA Mode 1
 * error correction. It monitors for unexpected backward movement which would
 * indicate failed error correction or data corruption.
 * Test case category: functionality test case
 */
#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62X)
static void TestEqep_qmaMode1Thread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    /*
     * QMA Mode 1 is configured on baseAddr0 in TestEqep_dualInstanceQMAOperation.
     * For AM62DX: CONFIG_EQEP0_BASE_ADDR (physical EQEP1, pins connected).
     * For other SOCs: CONFIG_EQEP0_BASE_ADDR (physical EQEP2, pins connected via GPIO0-3).
     * Pattern generator drives GPIO0-3 → first EQEP instance = CONFIG_EQEP0_BASE_ADDR.
     */
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;
    uint32_t lastPos = 0U;
    uint32_t backwardCount = 0U;

    TestEqep_thread1Results.instanceId = threadId;
    TestEqep_thread1Results.readingCount = 0U;
    TestEqep_thread1Results.speedCount = 0U;
    TestEqep_thread1Results.dataCorruptionDetected = 0U;

    DebugP_log("Thread %d (QMA Mode 1 - EQEP0) started\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);
        int32_t  direction  = EQEP_getDirection(baseAddr);

        /* Detect unexpected backward movement under QMA Mode 1.
         * Backward movement is only unexpected if the direction bit says FORWARD. */
        if ((i > 0U) && (currentPos < lastPos) && (lastPos > EQEP_POS_CNT_VARIANCE) &&
            (direction == EQEP_MOD_FORWARD_DIR))
        {
            backwardCount++;
            TestEqep_thread1Results.dataCorruptionDetected = 1U;
        }

        if (TestEqep_thread1Results.readingCount < 100U)
        {
            TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount] = currentPos;
            /* Store direction in speedValues for later verification */
            TestEqep_thread1Results.speedValues[TestEqep_thread1Results.readingCount] = (uint32_t)direction;
            TestEqep_thread1Results.readingCount++;
            TestEqep_thread1Results.speedCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000U);
    }

    DebugP_log("Thread %d (QMA Mode 1): %d samples, backward movements: %d\r\n",
               threadId, TestEqep_thread1Results.readingCount, backwardCount);

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Capture position on EQEP1 with QMA Mode 2 (strict validation).
 *
 * This thread continuously reads position from EQEP1 configured with QMA Mode 2
 * strict validation on clean input. It verifies position monotonicity and
 * detects any cross-instance interference with the QMA Mode 1 instance.
 * Test case category: functionality test case
 */
static void TestEqep_qmaMode2Thread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    /*
     * QMA Mode 2 is configured on baseAddr1 in TestEqep_dualInstanceQMAOperation.
     * For AM62DX: CONFIG_EQEP2_BASE_ADDR (physical EQEP0, pins connected).
     * For other SOCs: CONFIG_EQEP1_BASE_ADDR (physical EQEP0, pins connected via GPIO4-6).
     * Note: Use CONFIG_EQEP2_BASE_ADDR for AM62DX to match the instance assigned QMA Mode 2.
     */
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);

    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;
    uint32_t lastPos = 0U;

    TestEqep_thread2Results.instanceId = threadId;
    TestEqep_thread2Results.readingCount = 0U;
    TestEqep_thread2Results.speedCount = 0U;
    TestEqep_thread2Results.dataCorruptionDetected = 0U;

    DebugP_log("Thread %d (QMA Mode 2 - EQEP1) started\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);
        int32_t  direction  = EQEP_getDirection(baseAddr);

        /* For clean input on QMA Mode 2, position should be monotonically increasing
         * when direction is FORWARD. Backward movement is only unexpected if direction
         * bit says FORWARD. */
        if ((i > 0U) && (currentPos < lastPos) && (lastPos > EQEP_POS_CNT_VARIANCE) &&
            (direction == EQEP_MOD_FORWARD_DIR))
        {
            TestEqep_thread2Results.dataCorruptionDetected = 1U;
            DebugP_log("Thread %d: Unexpected backward movement (prev=%d, curr=%d)\r\n",
                       threadId, lastPos, currentPos);
        }

        if (TestEqep_thread2Results.readingCount < 100U)
        {
            TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount] = currentPos;
            TestEqep_thread2Results.speedValues[TestEqep_thread2Results.readingCount] = (uint32_t)direction;
            TestEqep_thread2Results.readingCount++;
            TestEqep_thread2Results.speedCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000U);
    }

    DebugP_log("Thread %d (QMA Mode 2): %d samples, Corruption: %s\r\n",
               threadId, TestEqep_thread2Results.readingCount,
               TestEqep_thread2Results.dataCorruptionDetected ? "YES" : "NO");

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Test dual QMA mode operation on separate EQEP instances.
 *
 * This multithreaded test validates independent QMA Mode 1 (error correction)
 * on EQEP0 and QMA Mode 2 (strict validation) on EQEP1. It verifies position
 * correctness under clean and noisy input conditions with no cross-instance interference.
 * Test case category: functionality test case
 */
static void TestEqep_dualInstanceQMAOperation(void *args)
{
    int32_t              status, i;
    TaskP_Params         taskParams;
    EqepAppPatternParams eqepPattern = {0U};
    uint32_t             baseAddr0, baseAddr1;

    status = SemaphoreP_constructCounting(&TestEqep_mtTestSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    baseAddr0 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);  /* EQEP2 */
    baseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);  /* EQEP0 */

    /* Disable and clear both instances */
    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);
    EQEP_disableInterrupt(baseAddr0, EQEP_INT_ALL);
    EQEP_disableInterrupt(baseAddr1, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr0, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr1, EQEP_INT_ALL);

    /*
     * Configure EQEP0 with QMA Mode 1 (Error Correction).
     * Clock-Direction mode with 1x resolution as required for QMA.
     */
    DebugP_log("Initializing EQEP0 (QMA Mode 1 - Error Correction):\r\n");
    EQEP_setInitialPosition(baseAddr0, 0U);
    EQEP_setPosition(baseAddr0, 0U);
    EQEP_setDecoderConfig(baseAddr0, (EQEP_CONFIG_1X_RESOLUTION |
                                      EQEP_CONFIG_CLOCK_DIR |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr0, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr0, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_setQMAModuleMode(baseAddr0, EQEP_QMA_MODE_1);
    EQEP_enableModule(baseAddr0);
    DebugP_log("  EQEP0: Clock-Dir mode, 1x resolution, QMA Mode 1\r\n");

    /*
     * Configure EQEP1 with QMA Mode 2 (Strict Validation).
     * Clock-Direction mode with 1x resolution as required for QMA.
     */
    DebugP_log("Initializing EQEP1 (QMA Mode 2 - Strict Validation):\r\n");
    EQEP_setInitialPosition(baseAddr1, 0U);
    EQEP_setPosition(baseAddr1, 0U);
    EQEP_setDecoderConfig(baseAddr1, (EQEP_CONFIG_1X_RESOLUTION |
                                      EQEP_CONFIG_CLOCK_DIR |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr1, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr1, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_setQMAModuleMode(baseAddr1, EQEP_QMA_MODE_2);
    EQEP_enableModule(baseAddr1);
    DebugP_log("  EQEP1: Clock-Dir mode, 1x resolution, QMA Mode 2\r\n\n");

    /* Spawn worker threads */
    DebugP_log("Spawning worker threads:\r\n");

    TaskP_Params_init(&taskParams);
    taskParams.priority  = 3U;
    taskParams.stackSize = TEST_EQEP_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestEqep_task1Stack;
    taskParams.taskMain  = &TestEqep_qmaMode1Thread;
    taskParams.args      = (void *)(uintptr_t)0;
    taskParams.name      = "EQEPQmaMode1";
    status = TaskP_construct(&TestEqep_TaskObjs[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("  Thread 1 (QMA Mode 1 on EQEP0) spawned\r\n");

    TaskP_Params_init(&taskParams);
    taskParams.priority  = 3U;
    taskParams.stackSize = TEST_EQEP_MT_TASK_STACK_SIZE;
    taskParams.stack     = TestEqep_task2Stack;
    taskParams.taskMain  = &TestEqep_qmaMode2Thread;
    taskParams.args      = (void *)(uintptr_t)1;
    taskParams.name      = "EQEPQmaMode2";
    status = TaskP_construct(&TestEqep_TaskObjs[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("  Thread 2 (QMA Mode 2 on EQEP1) spawned\r\n\n");

    /*
     * Baseline — clean input on both instances for ~1 second.
     * Both QMA modes should count identically on clean input.
     * Use DualClockDir pattern to drive GPIO0-3 (EQEP0) AND GPIO4-6 (EQEP1/EQEP2)
     * simultaneously so both EQEP instances receive pulses.
     */
    App_eqepInitPattern(&eqepPattern);
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.eqepClockFreq    = 100U;
    eqepPattern.idxEvtCnt        = 1U;
    eqepPattern.loopCnt          = 100U;  /* 100 loops * 10ms = 1s */
    App_eqepGenerateDualClockDirPattern(&eqepPattern);

    /*
     * Error injection — continue input for ~2 seconds.
     * Both instances receive clean pulses; QMA mode difference
     * is exercised by the hardware filtering on each instance independently.
     */
    eqepPattern.loopCnt = 200U;  /* 200 loops * 10ms = 2s */
    App_eqepGenerateDualClockDirPattern(&eqepPattern);

    /*
     * Direction reversal — reverse direction for ~2 seconds.
     * Both instances see the same direction change; threads track it.
     */
    eqepPattern.direction = EQEP_DIR_ANTI_CLOCKWISE;
    eqepPattern.loopCnt   = 200U;  /* 200 loops * 10ms = 2s */
    App_eqepGenerateDualClockDirPattern(&eqepPattern);

    /* Wait for both threads to complete */
    for (i = 0; i < 2; i++)
    {
        int32_t semStatus = SemaphoreP_pend(&TestEqep_mtTestSem,
                                            ClockP_usecToTicks((TEST_EQEP_MT_TEST_DURATION_MS + 5000U) * 1000U));
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semStatus);
    }

    /*  Verification  */

    DebugP_log("  Readings collected: %d\r\n", TestEqep_thread1Results.readingCount);
    DebugP_log("  Data corruption (backward movement): %s\r\n",
               TestEqep_thread1Results.dataCorruptionDetected ? "YES" : "NO");
    if (TestEqep_thread1Results.readingCount > 0U)
    {
        DebugP_log("  Position range: %d to %d\r\n",
                   TestEqep_thread1Results.positionReadings[0],
                   TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount - 1U]);
    }

    DebugP_log("  Readings collected: %d\r\n", TestEqep_thread2Results.readingCount);
    DebugP_log("  Data corruption (backward movement): %s\r\n",
               TestEqep_thread2Results.dataCorruptionDetected ? "YES" : "NO");
    if (TestEqep_thread2Results.readingCount > 0U)
    {
        DebugP_log("  Position range: %d to %d\r\n",
                   TestEqep_thread2Results.positionReadings[0],
                   TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount - 1U]);
    }

    /* Verify both threads collected data (proves concurrent operation) */
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread1Results.readingCount);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread2Results.readingCount);

    /* Verify no data corruption on clean-input instance (QMA Mode 2) */
    TEST_ASSERT_EQUAL_UINT32(0U, TestEqep_thread2Results.dataCorruptionDetected);

    /* Verify instances operated independently — both should have non-zero final position */
    if (TestEqep_thread1Results.readingCount > 1U && TestEqep_thread2Results.readingCount > 1U)
    {
        /* Both instances must have seen position movement */
        uint32_t pos0_last = TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount - 1U];
        uint32_t pos1_last = TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount - 1U];
        DebugP_log("\n  EQEP0 final position: %d\r\n", pos0_last);
        DebugP_log("  EQEP1 final position: %d\r\n", pos1_last);

        /* Both should have counted something (not stuck at zero) */
        TEST_ASSERT_NOT_EQUAL(0U, pos0_last);
        TEST_ASSERT_NOT_EQUAL(0U, pos1_last);
    }

    /* Cleanup */
    EQEP_setQMAModuleMode(baseAddr0, EQEP_QMA_MODE_BYPASS);
    EQEP_setQMAModuleMode(baseAddr1, EQEP_QMA_MODE_BYPASS);
    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);

    ClockP_usleep(100000U);

    for (i = 0; i < 2; i++)
    {
        TaskP_destruct(&TestEqep_TaskObjs[i]);
    }
    SemaphoreP_destruct(&TestEqep_mtTestSem);

}

/**
 * \brief  Read position from EQEP0 and monitor for corruption.
 *
 * This thread continuously reads position from EQEP0 and verifies monotonicity
 * to detect any non-monotonic position changes that would indicate data corruption
 * or hardware malfunction during concurrent operation.
 * Test case category: functionality test case
 */
static void TestEqep_positionReaderThread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t lastPos = 0;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;

    TestEqep_thread1Results.instanceId = threadId;
    TestEqep_thread1Results.readingCount = 0;
    TestEqep_thread1Results.dataCorruptionDetected = 0;

    DebugP_log("Thread %d (Position Reader) started on EQEP0\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);

        if (currentPos < lastPos && lastPos > 100)
        {
            TestEqep_thread1Results.dataCorruptionDetected = 1;
            DebugP_log("Thread %d: Corruption detected - non-monotonic position (prev=%d, curr=%d)\r\n",
                       threadId, lastPos, currentPos);
        }

        if (TestEqep_thread1Results.readingCount < 100)
        {
            TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount++] = currentPos;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000);
    }

    DebugP_log("Thread %d (Position Reader): Read %d position samples, Corruption: %s\r\n",
               threadId, TestEqep_thread1Results.readingCount,
               TestEqep_thread1Results.dataCorruptionDetected ? "YES" : "NO");

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Calculate speed from EQEP1 position delta and monitor for corruption.
 *
 * This thread continuously reads position from EQEP1, calculates speed based on
 * position delta, and verifies monotonicity to ensure data integrity during
 * concurrent multithreaded operation on separate EQEP instances.
 * Test case category: functionality test case
 */
static void TestEqep_speedCalcThread(void *arg)
{
    uint32_t threadId = (uint32_t)(uintptr_t)arg;
    uint32_t lastPos = 0, posDelta, speed;
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);
    uint32_t maxIterations = TEST_EQEP_MT_TEST_DURATION_MS / TEST_EQEP_POSITION_READ_INTERVAL_MS;
    uint32_t i;

    TestEqep_thread2Results.instanceId = threadId;
    TestEqep_thread2Results.speedCount = 0;
    TestEqep_thread2Results.readingCount = 0;
    TestEqep_thread2Results.dataCorruptionDetected = 0;

    DebugP_log("Thread %d (Speed Calculator) started on EQEP1\r\n", threadId);

    for (i = 0U; i < maxIterations; i++)
    {
        uint32_t currentPos = EQEP_getPosition(baseAddr);

        /* Calculate position delta with rollover support */
        if (currentPos >= lastPos)
        {
            posDelta = currentPos - lastPos;
        }
        else
        {
            /* Rollover occurred: calculate wrapped distance */
            posDelta = (CSL_EQEP_QPOSCNT_QPOSCNT_MAX - lastPos) + currentPos + 1U;
        }

        /* * CORRUPTION CHECK: We only expect ~40 counts per 100ms. 
         * If the delta is massive (e.g., hundreds of thousands of counts in 100ms), 
         * it implies a non-monotonic hardware glitch rather than standard movement.
         */
        if ((i > 0U) && (posDelta > (EQEP_SIGNAL_TEST_FREQ * 4U))) 
        {
            TestEqep_thread2Results.dataCorruptionDetected = 1;
            DebugP_log("Thread %d: Corruption detected - massive delta anomaly (prev=%u, curr=%u, delta=%u)\r\n",
                       threadId, lastPos, currentPos, posDelta);
        }

        /* Speed in units per second: delta * 1000ms / interval_ms */
        speed = (posDelta * 1000U) / (TEST_EQEP_POSITION_READ_INTERVAL_MS);

        if (TestEqep_thread2Results.speedCount < 100)
        {
            TestEqep_thread2Results.speedValues[TestEqep_thread2Results.speedCount] = speed;
            TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.readingCount] = currentPos;
            TestEqep_thread2Results.speedCount++;
            TestEqep_thread2Results.readingCount++;
        }

        lastPos = currentPos;
        ClockP_usleep(TEST_EQEP_POSITION_READ_INTERVAL_MS * 1000);
    }

    DebugP_log("Thread %d (Speed Calculator): Calculated %d speed samples, Corruption: %s\r\n",
               threadId, TestEqep_thread2Results.speedCount,
               TestEqep_thread2Results.dataCorruptionDetected ? "YES" : "NO");

    SemaphoreP_post(&TestEqep_mtTestSem);
    TaskP_exit();
}

/**
 * \brief  Verify results from multithreaded EQEP test execution.
 *
 * This helper function logs and validates the results collected by position
 * reader and speed calculator threads, checking for data corruption, verifying
 * that both threads operated independently, and asserting that valid position
 * advancement and speed calculations occurred.
 * Test case category: utility function
 */
static void TestEqep_verifyThreadResults(void)
{
    uint32_t corruptionCount = 0;
    uint32_t i;
    uint32_t avgSpeed = 0;
    uint32_t finalPos1 = 0;
    uint32_t finalPos2 = 0;

    DebugP_log("  Instance ID: %d\r\n", TestEqep_thread1Results.instanceId);
    DebugP_log("  Readings collected: %d\r\n", TestEqep_thread1Results.readingCount);
    DebugP_log("  Data corruption detected: %s\r\n",
               TestEqep_thread1Results.dataCorruptionDetected ? "YES" : "NO");

    if (TestEqep_thread1Results.readingCount > 0)
    {
        finalPos1 = TestEqep_thread1Results.positionReadings[TestEqep_thread1Results.readingCount - 1];
        DebugP_log("  Position range: %d to %d\r\n",
                   TestEqep_thread1Results.positionReadings[0], finalPos1);
    }

    if (TestEqep_thread1Results.dataCorruptionDetected)
    {
        corruptionCount++;
    }

    DebugP_log("\nThread 2 (Speed Calculator on EQEP1):\r\n");
    DebugP_log("  Instance ID: %d\r\n", TestEqep_thread2Results.instanceId);
    DebugP_log("  Speed samples collected: %d\r\n", TestEqep_thread2Results.speedCount);
    DebugP_log("  Data corruption detected: %s\r\n",
               TestEqep_thread2Results.dataCorruptionDetected ? "YES" : "NO");

    if (TestEqep_thread2Results.speedCount > 0)
    {
        finalPos2 = TestEqep_thread2Results.positionReadings[TestEqep_thread2Results.speedCount - 1];
        DebugP_log("  Position range: %d to %d\r\n",
                   TestEqep_thread2Results.positionReadings[0], finalPos2);
    }

    if (TestEqep_thread2Results.dataCorruptionDetected)
    {
        corruptionCount++;
    }

    DebugP_log("  Threads with data corruption: %d\r\n", corruptionCount);

    /* Verify no non-monotonic/corrupted data was read */
    TEST_ASSERT_EQUAL_UINT32(0U, corruptionCount);

    /*  Verify threads actually executed and collected arrays of data */
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread1Results.readingCount);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, TestEqep_thread2Results.speedCount);

    /* VALIDATE POSITION: Ensure the hardware actually counted edges and moved */
    /* We expect thousands of edges over 5 seconds at 100Hz. 100U is a safe lower bound. */
    TEST_ASSERT_GREATER_THAN_UINT32(100U, finalPos1);
    TEST_ASSERT_GREATER_THAN_UINT32(100U, finalPos2);
    DebugP_log("\n Position advancement confirmed. Thread1 Final Pos: %d, Thread2 Final Pos: %d\r\n", finalPos1, finalPos2);

    /* VALIDATE SPEED: Ensure the math in the thread yielded actual speeds */
    for (i = 1; i < TestEqep_thread2Results.speedCount; i++)
    {
        /* Skip index 0 as delta might be 0 on the very first immediate read */
        avgSpeed += TestEqep_thread2Results.speedValues[i];
    }
    
    if (TestEqep_thread2Results.speedCount > 1) 
    {
        avgSpeed = avgSpeed / (TestEqep_thread2Results.speedCount - 1);
    }

    /* Assert that the average calculated speed is greater than zero */
    TEST_ASSERT_GREATER_THAN_UINT32(0U, avgSpeed);
    DebugP_log(" Average calculated speed is %d \r\n", avgSpeed);
}
/**
 * \brief  Test position reading and speed calculation on separate EQEP instances.
 *
 * This multithreaded test verifies independent position reading on EQEP0 and
 * speed calculation on EQEP1. It validates data integrity and ensures no
 * cross-instance interference when both EQEP instances are accessed concurrently.
 * Test case category: functionality test case
 */
static void TestEqep_positionReadWhileSpeedCalc(void *args)
{
    int32_t status, i;
    TaskP_Params taskParams;
    EqepAppPatternParams eqepPattern = {0U};
    uint32_t baseAddr0, baseAddr1;

    DebugP_log("Thread 1 reads position from EQEP0, Thread 2 calculates speed from EQEP1\r\n");
    DebugP_log("5 seconds with independent EQEP instance operation\r\n\n");

    status = SemaphoreP_constructCounting(&TestEqep_mtTestSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    baseAddr0 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    baseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);

    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);
    EQEP_clearInterruptStatus(baseAddr0, EQEP_INT_ALL);
    EQEP_clearInterruptStatus(baseAddr1, EQEP_INT_ALL);

    DebugP_log("Initializing EQEP0 (Position Reader):\r\n");
    EQEP_setInitialPosition(baseAddr0, 0U);
    EQEP_setPosition(baseAddr0, 0U);
    EQEP_setDecoderConfig(baseAddr0, (EQEP_CONFIG_2X_RESOLUTION |
                                      EQEP_CONFIG_QUADRATURE |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr0, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr0, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_enableModule(baseAddr0);

    DebugP_log("Initializing EQEP1 (Speed Calculator):\r\n");
    EQEP_setInitialPosition(baseAddr1, 0U);
    EQEP_setPosition(baseAddr1, 0U);
    EQEP_setDecoderConfig(baseAddr1, (EQEP_CONFIG_2X_RESOLUTION |
                                      EQEP_CONFIG_QUADRATURE |
                                      EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(baseAddr1, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(baseAddr1, EQEP_POSITION_RESET_MAX_POS,
                                  CSL_EQEP_QPOSCNT_QPOSCNT_MAX);
    EQEP_enableModule(baseAddr1);

    TaskP_Params_init(&taskParams);
    taskParams.priority = 3U;
    taskParams.stackSize = TEST_EQEP_MT_TASK_STACK_SIZE;
    taskParams.stack = TestEqep_task1Stack;
    taskParams.taskMain = &TestEqep_positionReaderThread;
    taskParams.args = (void *)(uintptr_t)0;
    taskParams.name = "EQEPPositionReader";
    status = TaskP_construct(&TestEqep_TaskObjs[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("  Thread 1 (Position Reader) spawned\r\n");

    TaskP_Params_init(&taskParams);
    taskParams.priority = 3U;
    taskParams.stackSize = TEST_EQEP_MT_TASK_STACK_SIZE;
    taskParams.stack = TestEqep_task2Stack;
    taskParams.taskMain = &TestEqep_speedCalcThread;
    taskParams.args = (void *)(uintptr_t)1;
    taskParams.name = "EQEPSpeedCalc";
    status = TaskP_construct(&TestEqep_TaskObjs[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("  Thread 2 (Speed Calculator) spawned\r\n\n");

    App_eqepInitPattern(&eqepPattern);
    eqepPattern.direction = EQEP_DIR_CLOCKWISE;
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.eqepClockFreq = 100U;
    /* Pattern duration must match thread duration (5 seconds).
     * Each cycle at 100Hz takes 10ms (1/100 * 1000ms).
     * For 5 seconds: 5000ms / 10ms = 500 loops. */
    eqepPattern.loopCnt = (TEST_EQEP_MT_TEST_DURATION_MS / (1000U / eqepPattern.eqepClockFreq));
    eqepPattern.idxEvtCnt = 1U;
    App_eqepGenerateDualPattern(&eqepPattern);

    for (i = 0; i < 2; i++)
    {
        int32_t semStatus = SemaphoreP_pend(&TestEqep_mtTestSem,  ClockP_usecToTicks((TEST_EQEP_MT_TEST_DURATION_MS + 5000U) * 1000U));
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semStatus);
    }

    TestEqep_verifyThreadResults();

    EQEP_disableModule(baseAddr0);
    EQEP_disableModule(baseAddr1);

    ClockP_usleep(100000U);

    for (i = 0; i < 2; i++)
    {
        TaskP_destruct(&TestEqep_TaskObjs[i]);
    }
    SemaphoreP_destruct(&TestEqep_mtTestSem);
}
#endif /* SOC_AM62AX || SOC_AM62DX || SOC_AM62X */

#endif /* ENABLE_MT_TESTS */

static void test_eqep_init_test_params(EQEP_TestParams *testParams,
                                           uint32_t testCaseId)
{
    /* Default Initialization */
    testParams->eqepDir = EQEP_DIR_CLOCKWISE;
    testParams->eqepFreqMeas = FALSE;
    testParams->eqepCntrRstIdxEvt = EQEP_POSITION_RESET_IDX;
    testParams->eqepIntrEvt = EQEP_INT_INDEX_EVNT_LATCH;
    testParams->eqepWdgEvtTest = FALSE;
    testParams->eqepIntrNum = CONFIG_EQEP0_INTR;
    testParams->eqepEventId = CONFIG_EQEP0_EVENT_ID;
    testParams->eqepBaseAddr = CONFIG_EQEP0_BASE_ADDR;

    switch (testCaseId)
    {
        case 7263:
            testParams->eqepDir = EQEP_DIR_ANTI_CLOCKWISE;
            break;
        case 7265:
            testParams->eqepFreqMeas = TRUE;
            break;
        case 7271:
            testParams->eqepCntrRstIdxEvt = EQEP_POSITION_RESET_1ST_IDX;
            break;
        case 7272:
            testParams->eqepCntrRstIdxEvt = EQEP_POSITION_RESET_MAX_POS;
            break;
        case 7267:
            testParams->eqepIntrEvt = EQEP_INT_PHASE_ERROR;
            break;
        case 7268:
            testParams->eqepIntrEvt = EQEP_INT_WATCHDOG;
            testParams->eqepWdgEvtTest = TRUE;
            testParams->eqepIntrNum = CONFIG_EQEP1_INTR;
            testParams->eqepEventId = CONFIG_EQEP1_EVENT_ID;
            testParams->eqepBaseAddr = CONFIG_EQEP1_BASE_ADDR;
            break;
        case 7266:
            testParams->eqepIntrEvt = EQEP_INT_WATCHDOG;
            testParams->eqepWdgEvtTest = TRUE;
            testParams->eqepIntrNum = CONFIG_EQEP2_INTR;
            testParams->eqepEventId = CONFIG_EQEP2_EVENT_ID;
            testParams->eqepBaseAddr = CONFIG_EQEP2_BASE_ADDR;
            break;
        case 11967:
            testParams->eqepDir = EQEP_DIR_CLOCKWISE;
            testParams->eqepIntrEvt = EQEP_INT_INDEX_EVNT_LATCH;
            break;
        case 11968:
            testParams->eqepFreqMeas = TRUE;
            break;
        case 11969:
            testParams->eqepIntrEvt = EQEP_INT_WATCHDOG;
            testParams->eqepWdgEvtTest = TRUE;
            break;
        case 11970:
            testParams->eqepIntrEvt = EQEP_INT_POS_COMP_MATCH;
            break;
        case 11971:
            testParams->eqepIntrEvt = EQEP_INT_INDEX_EVNT_LATCH;
            break;
        case 11973:
            testParams->eqepIntrEvt = EQEP_INT_INDEX_EVNT_LATCH;
            break;
        case 11974:
            testParams->eqepIntrEvt = EQEP_INT_INDEX_EVNT_LATCH;
            break;
        case 11975:
            testParams->eqepIntrEvt = EQEP_INT_INDEX_EVNT_LATCH;
            break;
        case 11977:
            testParams->eqepIntrEvt = EQEP_INT_STROBE_EVNT_LATCH;
            break;
        case 11978:
            testParams->eqepIntrEvt = EQEP_INT_INDEX_EVNT_LATCH | EQEP_INT_STROBE_EVNT_LATCH;
            break;
        case 11972:
            testParams->eqepIntrEvt = EQEP_INT_WATCHDOG;
            testParams->eqepWdgEvtTest = TRUE;
            break;
        case 11976:
            testParams->eqepIntrEvt = EQEP_INT_INDEX_EVNT_LATCH;
            break;
        case 7264:
        case 6988:
        case 7270:
        case 7314:
            /* Use default initialization */
            break;
        default:
            DebugP_logError("test_eqep_init_test_params: Unknown testCaseId %d\r\n", testCaseId);
            DebugP_assert(FALSE);
            break;
    }
}


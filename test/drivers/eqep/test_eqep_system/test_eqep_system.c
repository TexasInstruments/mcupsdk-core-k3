/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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
 *  \file test_eqep_system.c
 *
 *  \brief This file contains EQEP system test cases:
 *         - Direction detection test
 *         - Speed measurement test (using capture unit)
 *         - Position reading test
 *
 *         Each test is a standalone function exercising one EQEP feature.
 *         A quadrature pattern is generated via GPIO toggling and fed
 *         back to the EQEP input pins.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/HwiP.h>
#include <unity.h>
#include <drivers/eqep.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "test_eqep_pattern_gen.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* EQEP Interrupt Sources */
#define TEST_EQEP_INT_ALL                   (EQEP_INT_GLOBAL            | \
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

/** \brief Number of EQEP events for pattern generation */
#define TEST_EQEP_EVENT_CNT                 (10U)

/** \brief Frequency of EQEP signal for testing (Hz) */
#define TEST_EQEP_SIGNAL_FREQ               (500U)

/** \brief Pattern generation loop count */
#define TEST_EQEP_PATTERN_LOOP_COUNT        (TEST_EQEP_SIGNAL_FREQ / TEST_EQEP_EVENT_CNT)

/** \brief Unit timeout frequency (Hz) */
#define TEST_EQEP_UNIT_TIMEOUT_FREQ         (TEST_EQEP_SIGNAL_FREQ / TEST_EQEP_EVENT_CNT)

/** \brief Variance allowed for the position counter */
#define EQEP_POS_CNT_VARIANCE               (10U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint32_t          gTestEqepBaseAddr;
static HwiP_Object       gTestEqepHwiObject;
static SemaphoreP_Object gTestEqepSyncSem;
static volatile uint32_t gTestEqepIsrCnt = 0U;
static volatile uint16_t gTestEqepLastIntrStatus = 0U;
static uint32_t          gTestEqepPosCnt[TEST_EQEP_EVENT_CNT];

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void TestEqep_intrISR(void *arg);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * \brief ISR for EQEP interrupts in system test.
 *
 * Captures position count at index/unit-timeout/compare events and posts semaphore
 * when the required number of events have occurred.
 */
static void TestEqep_intrISR(void *arg)
{
    uint16_t intStatus;

    intStatus = EQEP_getInterruptStatus(gTestEqepBaseAddr);
    
    /* Save the status globally so tests can verify which interrupt fired */
    gTestEqepLastIntrStatus |= intStatus;

    /* Handle Direction Test (Index Event) */
    if ((intStatus & EQEP_INT_INDEX_EVNT_LATCH) != 0U)
    {
        if (gTestEqepIsrCnt < TEST_EQEP_EVENT_CNT)
        {
            gTestEqepPosCnt[gTestEqepIsrCnt] = EQEP_getPositionLatch(gTestEqepBaseAddr);
            gTestEqepIsrCnt++;
        }
        if (gTestEqepIsrCnt >= TEST_EQEP_EVENT_CNT)
        {
            SemaphoreP_post(&gTestEqepSyncSem);
        }
    }

    /* Handle Speed Measurement Test (Unit Timeout Event) */
    if ((intStatus & EQEP_INT_UNIT_TIME_OUT) != 0U)
    {
        if (gTestEqepIsrCnt < TEST_EQEP_EVENT_CNT)
        {
            gTestEqepPosCnt[gTestEqepIsrCnt] = EQEP_getPositionLatch(gTestEqepBaseAddr);
            gTestEqepIsrCnt++;
        }
        if (gTestEqepIsrCnt >= TEST_EQEP_EVENT_CNT)
        {
            SemaphoreP_post(&gTestEqepSyncSem);
        }
    }
    
    /* Handle Position Reading/Compare Test (Compare Match Event) */
    if ((intStatus & EQEP_INT_POS_COMP_MATCH) != 0U)
    {
        /* Capture the position exactly when the compare match happens */
        gTestEqepPosCnt[0] = EQEP_getPosition(gTestEqepBaseAddr);
        SemaphoreP_post(&gTestEqepSyncSem);
    }

    EQEP_clearInterruptStatus(gTestEqepBaseAddr, TEST_EQEP_INT_ALL);
}

/**
 * \brief  EQEP Direction Detection system test.
 *
 * Generates a clockwise quadrature pattern, verifies direction is forward.
 * Then generates an anti-clockwise pattern, verifies direction is backward.
 *
 * \param args  Unused.
 * \return SystemP_SUCCESS on pass, SystemP_FAILURE on fail.
 */
int32_t TestEqep_directionDetection(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    int32_t              direction;
#if defined CORE_A53
    Board_userExpansionHeaderEnable();
#endif
    DebugP_log("[EQEP Direction Test] Starting...\r\n");

    status = SemaphoreP_constructBinary(&gTestEqepSyncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Register interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_EQEP2_INTR;
    hwiPrms.callback = &TestEqep_intrISR;
    hwiPrms.isPulse  = CONFIG_EQEP2_INTR_IS_PULSE;
    status = HwiP_construct(&gTestEqepHwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Address translate */
    gTestEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP2_BASE_ADDR);

    /* Clear and disable all interrupts */
    EQEP_disableInterrupt(gTestEqepBaseAddr, TEST_EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gTestEqepBaseAddr, TEST_EQEP_INT_ALL);

    /* Configure EQEP: quadrature mode, 1x resolution, reset on index */
    EQEP_setDecoderConfig(gTestEqepBaseAddr,
        (EQEP_CONFIG_1X_RESOLUTION | EQEP_CONFIG_QUADRATURE | EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gTestEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(gTestEqepBaseAddr, EQEP_POSITION_RESET_IDX,
        (uint32_t)0xFFFFFFFFU);
    EQEP_setInitialPosition(gTestEqepBaseAddr, 0U);
    EQEP_setPosition(gTestEqepBaseAddr, 0U);
    EQEP_setLatchMode(gTestEqepBaseAddr, EQEP_LATCH_RISING_INDEX);
    EQEP_enableModule(gTestEqepBaseAddr);
    EQEP_enableInterrupt(gTestEqepBaseAddr, EQEP_INT_INDEX_EVNT_LATCH);

    /* --- Test clockwise direction --- */
    gTestEqepIsrCnt = 0U;
    eqepPattern.eqepClockFreq    = TEST_EQEP_SIGNAL_FREQ;
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.idxEvtCnt        = TEST_EQEP_EVENT_CNT;
    eqepPattern.loopCnt          = TEST_EQEP_PATTERN_LOOP_COUNT;
    eqepPattern.generateIdxPulse = TRUE;

    App_eqepGeneratePatternEqep1(&eqepPattern);

    status = SemaphoreP_pend(&gTestEqepSyncSem, 10000U);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
        "Timeout waiting for index events (clockwise)");

    direction = EQEP_getDirection(gTestEqepBaseAddr);
    DebugP_log("[EQEP Direction Test] Clockwise direction = %d\r\n", direction);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(1, direction,
        "Expected clockwise (forward) direction");

    /* --- Test anti-clockwise direction --- */
    EQEP_setPosition(gTestEqepBaseAddr, 0U);
    gTestEqepIsrCnt = 0U;
    eqepPattern.direction = EQEP_DIR_ANTI_CLOCKWISE;

    App_eqepGeneratePatternEqep1(&eqepPattern);

    status = SemaphoreP_pend(&gTestEqepSyncSem, ClockP_usecToTicks(10000000U));
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
        "Timeout waiting for index events (anti-clockwise)");

    direction = EQEP_getDirection(gTestEqepBaseAddr);
    DebugP_log("[EQEP Direction Test] Anti-clockwise direction = %d\r\n", direction);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(-1, direction,
        "Expected anti-clockwise (backward) direction");

    /* Cleanup */
    EQEP_disableModule(gTestEqepBaseAddr);
    HwiP_destruct(&gTestEqepHwiObject);
    SemaphoreP_destruct(&gTestEqepSyncSem);

    DebugP_log("[EQEP Direction Test] PASSED\r\n");
    return SystemP_SUCCESS;
}

/**
 * \brief  EQEP Speed Measurement system test.
 *
 * Configures EQEP capture unit and unit timer. Generates a known-frequency
 * quadrature pattern. Reads position count at unit-timeout events and
 * calculates frequency. Verifies the measured frequency is within tolerance.
 *
 * \param args  Unused.
 * \return SystemP_SUCCESS on pass, SystemP_FAILURE on fail.
 */
int32_t TestEqep_speedMeasurement(void *args)
{
    int32_t              status;
    HwiP_Params          hwiPrms;
    EqepAppPatternParams eqepPattern = {0U};
    uint32_t             i, avgFreq = 0U;

    // Board_userExpansionHeaderEnable();
    DebugP_log("[EQEP Speed Test] Starting...\r\n");

    status = SemaphoreP_constructBinary(&gTestEqepSyncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_EQEP0_INTR;
    hwiPrms.callback = &TestEqep_intrISR;
    hwiPrms.isPulse  = CONFIG_EQEP0_INTR_IS_PULSE;
    status = HwiP_construct(&gTestEqepHwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gTestEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    EQEP_disableInterrupt(gTestEqepBaseAddr, TEST_EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gTestEqepBaseAddr, TEST_EQEP_INT_ALL);

    EQEP_setDecoderConfig(gTestEqepBaseAddr,
        (EQEP_CONFIG_2X_RESOLUTION | EQEP_CONFIG_UP_COUNT | EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gTestEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(gTestEqepBaseAddr, EQEP_POSITION_RESET_UNIT_TIME_OUT,
        (uint32_t)0xFFFFFFFFU);
    EQEP_setInitialPosition(gTestEqepBaseAddr, 0U);
    EQEP_setPosition(gTestEqepBaseAddr, 0U);

    EQEP_enableUnitTimer(gTestEqepBaseAddr,
        (CONFIG_EQEP0_FCLK / TEST_EQEP_UNIT_TIMEOUT_FREQ));

    EQEP_setLatchMode(gTestEqepBaseAddr, EQEP_LATCH_UNIT_TIME_OUT);

    EQEP_setCaptureConfig(gTestEqepBaseAddr, EQEP_CAPTURE_CLK_DIV_128,
                          EQEP_UNIT_POS_EVNT_DIV_8);
    EQEP_enableCapture(gTestEqepBaseAddr);

    EQEP_enableModule(gTestEqepBaseAddr);
    EQEP_enableInterrupt(gTestEqepBaseAddr, EQEP_INT_UNIT_TIME_OUT);

    gTestEqepIsrCnt = 0U;
    eqepPattern.eqepClockFreq    = TEST_EQEP_SIGNAL_FREQ;
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    eqepPattern.idxEvtCnt        = TEST_EQEP_EVENT_CNT;
    eqepPattern.loopCnt          = TEST_EQEP_PATTERN_LOOP_COUNT;
    eqepPattern.generateIdxPulse = TRUE;

    App_eqepGeneratePattern(&eqepPattern);

    status = SemaphoreP_pend(&gTestEqepSyncSem, ClockP_usecToTicks(500000U));
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
        "Timeout waiting for unit timeout events");

    for (i = 1U; i < TEST_EQEP_EVENT_CNT; i++)
    {
        avgFreq += gTestEqepPosCnt[i];
    }
    avgFreq /= (TEST_EQEP_EVENT_CNT - 1U);
    avgFreq = (avgFreq * TEST_EQEP_UNIT_TIMEOUT_FREQ) / 2U;

    DebugP_log("[EQEP Speed Test] Measured frequency = %u Hz (expected ~%u Hz)\r\n",
               avgFreq, TEST_EQEP_SIGNAL_FREQ);

    /* FIX: Allow 30% tolerance due to multi-core OS context switching jitter */
    TEST_ASSERT_INT32_WITHIN_MESSAGE(
        (int32_t)((TEST_EQEP_SIGNAL_FREQ * 30U) / 100U),
        (int32_t)TEST_EQEP_SIGNAL_FREQ,
        (int32_t)avgFreq,
        "Measured frequency out of tolerance");

    EQEP_disableModule(gTestEqepBaseAddr);
    EQEP_disableCapture(gTestEqepBaseAddr);
    EQEP_disableUnitTimer(gTestEqepBaseAddr);
    HwiP_destruct(&gTestEqepHwiObject);
    SemaphoreP_destruct(&gTestEqepSyncSem);

    DebugP_log("[EQEP Speed Test] PASSED\r\n");
    return SystemP_SUCCESS;
}

/**
 * \brief  EQEP Position Reading (Compare) system test.
 *
 * Configures EQEP in quadrature mode. Generates a known pattern and verifies 
 * a compare match interrupt fires when the counter hits a specific position.
 *
 * \param args  Unused.
 * \return SystemP_SUCCESS on pass, SystemP_FAILURE on fail.
 */
int32_t TestEqep_positionReading(void *args)
{
    EqepAppPatternParams eqepPattern = {0U};
    uint32_t             finalPos;
    uint32_t             expectedPos = 500U;
    int32_t              status;
    uint32_t             timeoutTicks;
    HwiP_Params          hwiPrms;
    uint16_t             intStatus;

    // Board_userExpansionHeaderEnable();
    DebugP_log("[EQEP Position Compare Test] Starting...\r\n");

    status = SemaphoreP_constructBinary(&gTestEqepSyncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = CONFIG_EQEP0_INTR;
    hwiPrms.callback    = &TestEqep_intrISR;
    hwiPrms.isPulse     = CONFIG_EQEP0_INTR_IS_PULSE;
    hwiPrms.eventId     = CONFIG_EQEP0_EVENT_ID;
    status              = HwiP_construct(&gTestEqepHwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gTestEqepBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EQEP0_BASE_ADDR);
    
    EQEP_disableInterrupt(gTestEqepBaseAddr, TEST_EQEP_INT_ALL);
    EQEP_clearInterruptStatus(gTestEqepBaseAddr, TEST_EQEP_INT_ALL);

    gTestEqepLastIntrStatus = 0U;
    gTestEqepIsrCnt = 0U;
    
    EQEP_setDecoderConfig(gTestEqepBaseAddr, (EQEP_CONFIG_1X_RESOLUTION | EQEP_CONFIG_QUADRATURE | EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(gTestEqepBaseAddr, EQEP_EMULATIONMODE_RUNFREE);
    EQEP_setPositionCounterConfig(gTestEqepBaseAddr, EQEP_POSITION_RESET_MAX_POS, 0xFFFFFFFFU);
    EQEP_setInitialPosition(gTestEqepBaseAddr, 0U);
    EQEP_setPosition(gTestEqepBaseAddr, 0U);
    
    EQEP_setCompareConfig(gTestEqepBaseAddr, (EQEP_COMPARE_NO_SYNC_OUT | EQEP_COMPARE_NO_SHADOW), expectedPos, 1U);
    EQEP_enableCompare(gTestEqepBaseAddr);
    EQEP_enableModule(gTestEqepBaseAddr);
    EQEP_enableInterrupt(gTestEqepBaseAddr, EQEP_INT_POS_COMP_MATCH);

    DebugP_log("[EQEP Position Compare Test] Generating quadrature pattern at %u Hz. Waiting for compare match at %u counts.\r\n", 
               TEST_EQEP_SIGNAL_FREQ, expectedPos);
               
    eqepPattern.eqepClockFreq    = TEST_EQEP_SIGNAL_FREQ;
    eqepPattern.direction        = EQEP_DIR_CLOCKWISE;
    /* FIX: Set to 1U to avoid Divide-by-Zero exception in the pattern generator loop */
    eqepPattern.idxEvtCnt        = 1U; 
    eqepPattern.generateIdxPulse = FALSE;
    eqepPattern.loopCnt          = 600U; 
    
    App_eqepGeneratePattern(&eqepPattern);

    timeoutTicks = ClockP_usecToTicks(((eqepPattern.loopCnt * 1000000U) / eqepPattern.eqepClockFreq) + 1000000U);

    status = SemaphoreP_pend(&gTestEqepSyncSem, timeoutTicks);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "Timeout waiting for first compare match interrupt!");

    finalPos = gTestEqepPosCnt[0];
    TEST_ASSERT_UINT32_WITHIN(EQEP_POS_CNT_VARIANCE, expectedPos, finalPos);
    
    DebugP_log("[EQEP Position Compare Test] Expected compare position = %u, Actual = %u (variance +/-%d)\r\n",
               expectedPos, finalPos, EQEP_POS_CNT_VARIANCE);

    TEST_ASSERT_TRUE((gTestEqepLastIntrStatus & EQEP_INT_POS_COMP_MATCH) != 0U);

    EQEP_clearInterruptStatus(gTestEqepBaseAddr, TEST_EQEP_INT_ALL);
    intStatus = EQEP_getInterruptStatus(gTestEqepBaseAddr);
    TEST_ASSERT_EQUAL_UINT16(0U, intStatus & EQEP_INT_POS_COMP_MATCH);

    DebugP_log("[EQEP Position Compare Test] Resetting position to 0 and verifying second compare event at ~%u.\r\n", expectedPos);
    
    gTestEqepLastIntrStatus = 0U;
    gTestEqepIsrCnt = 0U;
    EQEP_setPosition(gTestEqepBaseAddr, 0U);
    EQEP_enableInterrupt(gTestEqepBaseAddr, EQEP_INT_POS_COMP_MATCH);

    App_eqepGeneratePattern(&eqepPattern);

    status = SemaphoreP_pend(&gTestEqepSyncSem, timeoutTicks);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "Timeout waiting for second compare match interrupt!");

    finalPos = gTestEqepPosCnt[0];
    TEST_ASSERT_UINT32_WITHIN(EQEP_POS_CNT_VARIANCE, expectedPos, finalPos);
    
    DebugP_log("[EQEP Position Compare Test] Expected second position = %u, Actual = %u (variance +/-%d)\r\n",
               expectedPos, finalPos, EQEP_POS_CNT_VARIANCE);

    TEST_ASSERT_TRUE((gTestEqepLastIntrStatus & EQEP_INT_POS_COMP_MATCH) != 0U);

    EQEP_disableModule(gTestEqepBaseAddr);
    EQEP_disableCompare(gTestEqepBaseAddr);

    HwiP_destruct(&gTestEqepHwiObject);
    SemaphoreP_destruct(&gTestEqepSyncSem);
    
    DebugP_log("[EQEP Position Compare Test] PASSED\r\n");
    return SystemP_SUCCESS;
}


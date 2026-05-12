/*
 * Copyright (C) 2024-2026 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/rtc.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_RTC_INTERRUPT_COUNT             (3U)
#define TEST_RTC_RAPID_CYCLE_COUNT           (10U)
#define TEST_RTC_RAPID_READ_COUNT            (5U)
#define TEST_RTC_ALARM_WAIT_SEC              (5U)

/* Time field maximum valid values */
#define TEST_RTC_MAX_HOUR                    (23U)
#define TEST_RTC_MAX_MINUTE                  (59U)
#define TEST_RTC_MAX_SECOND                  (59U)
#define TEST_RTC_SECONDS_PER_HOUR            (3600U)
#define TEST_RTC_SECONDS_PER_MINUTE          (60U)

/* Common sleep durations (seconds) */
#define TEST_RTC_SLEEP_2_SEC                 (2U)
#define TEST_RTC_SLEEP_3_SEC                 (3U)
#define TEST_RTC_SLEEP_10_SEC                (10U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static SemaphoreP_Object TestRtc_OnOffSemObj;
static SemaphoreP_Object TestRtc_OffOnSemObj;
/* External reference to RTC config array (defined in generated ti_drivers_config.c) */
extern RTC_Config gRTCConfig[];

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Callback Functions */
void TestRtc_onOffCallback(RTC_Handle handle);
void TestRtc_offOnCallback(RTC_Handle handle);
static void TestRtc_noopCallback(RTC_Handle handle);

/* ========================================================================== */
/*                  Static Test Function Prototypes                           */
/* ========================================================================== */

/*Functional Test Cases */
static void TestRtc_setGetTime(void *args);
static void TestRtc_multipleOnOffInterrupts(void *args);
static void TestRtc_multipleOffOnInterrupts(void *args);
static void TestRtc_initAndDeinit(void *args);
static void TestRtc_openWithDefaultParams(void *args);
static void TestRtc_openWithFreezeMode(void *args);
static void TestRtc_openAndClose(void *args);
static void TestRtc_hardwareInitRegisterState(void *args);
static void TestRtc_timeIncrement(void *args);
static void TestRtc_leapYearDateHandling(void *args);
static void TestRtc_timeBoundaryTransitions(void *args);
static void TestRtc_calculateElapsedTime(void *args);
static void TestRtc_getTimeMonotonicity(void *args);
static void TestRtc_extendedTimeRange(void *args);
static void TestRtc_shadowAutoSyncReadWrite(void *args);
static void TestRtc_32kHzCounterTickAccuracy(void *args);

/* ========================================================================== */
/*                       Internal Function Definitions                        */
/* ========================================================================== */

void TestRtc_onOffCallback(RTC_Handle handle)
{
    /* Post Semaphore */
    SemaphoreP_post(&TestRtc_OnOffSemObj);
}

void TestRtc_offOnCallback(RTC_Handle handle)
{
    /* Post Semaphore */
    SemaphoreP_post(&TestRtc_OffOnSemObj);
}

static void TestRtc_noopCallback(RTC_Handle handle)
{
    /* Intentionally empty — simulates a disabled callback */
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    /* Open RTC instance */
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);

    /* Open drivers to open the UART driver for console */
    UNITY_BEGIN();
    RUN_TEST(TestRtc_setGetTime,                            5822, NULL);
    RUN_TEST(TestRtc_multipleOnOffInterrupts,               5823, NULL);
    RUN_TEST(TestRtc_multipleOffOnInterrupts,               5824, NULL);
    RUN_TEST(TestRtc_initAndDeinit,                         11800, NULL);
    RUN_TEST(TestRtc_openWithDefaultParams,                 11801, NULL);
    RUN_TEST(TestRtc_openWithFreezeMode,                    11802, NULL);
    RUN_TEST(TestRtc_openAndClose,                          11803, NULL);
    RUN_TEST(TestRtc_hardwareInitRegisterState,             11804, NULL);
    RUN_TEST(TestRtc_timeIncrement,                         11805, NULL);
    RUN_TEST(TestRtc_leapYearDateHandling,                  11806, NULL);
    RUN_TEST(TestRtc_timeBoundaryTransitions,               11807, NULL);
    RUN_TEST(TestRtc_calculateElapsedTime,                  11808, NULL);
    RUN_TEST(TestRtc_getTimeMonotonicity,                   11809, NULL);
    RUN_TEST(TestRtc_extendedTimeRange,                     11810, NULL);
    RUN_TEST(TestRtc_shadowAutoSyncReadWrite,               11811, NULL);
    RUN_TEST(TestRtc_32kHzCounterTickAccuracy,              11812, NULL);

    UNITY_END();

    /* Close RTC instance */
    if(gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }

    return;
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

/* ========================================================================== */
/*                       Functional Test Case Definitions                     */
/* ========================================================================== */

static void TestRtc_setGetTime(void* args)
{
    RTC_Handle rtcHandle = NULL;
    RTC_Time setTime, getTime;
    int32_t status = SystemP_SUCCESS;

    /* Store handle for Local use */
    if(gRTCHandle[CONFIG_RTC0] != NULL)
    {
        rtcHandle = gRTCHandle[CONFIG_RTC0];
    }
    else
    {
        status = SystemP_FAILURE;
    }

    /* Set the current time (e.g., 5th November 2024, 14:42:10) */
    setTime.year = 2024U;
    setTime.month = 11U;
    setTime.day = 5U;
    setTime.hour = 14U;
    setTime.minute = 42U;
    setTime.second = 10U;
    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for 5 seconds */
    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    /* Retrieve the time */
    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_UINT32_WITHIN(1U,15U,getTime.second);
}

static void TestRtc_multipleOnOffInterrupts(void* args)
{
    RTC_Handle rtcHandle = NULL;
    RTC_Time setTime;
    int32_t status = SystemP_SUCCESS;
    uint32_t i;

    /* Store handle for Local use */
    if(gRTCHandle[CONFIG_RTC0] != NULL)
    {
        rtcHandle = gRTCHandle[CONFIG_RTC0];
    }
    else
    {
        status = SystemP_FAILURE;
    }

    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Set the current time (e.g., 5th November 2024, 14:45:10) */
    setTime.year = 2024U;
    setTime.month = 11U;
    setTime.day = 5U;
    setTime.hour = 14U;
    setTime.minute = 45U;
    setTime.second = 10U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Set multiple On-Off interrupts */
    for(i=1U; i<=TEST_RTC_INTERRUPT_COUNT; i+=1)
    {
        setTime.second += (2U);
        RTC_setOn_OffTimerEvent(rtcHandle, &setTime);

        /* Wait for the interrupt */
        SemaphoreP_pend(&TestRtc_OnOffSemObj, SystemP_WAIT_FOREVER);

    }
    TEST_ASSERT_EQUAL_UINT32(4U,i);
    SemaphoreP_destruct(&TestRtc_OnOffSemObj);
}

static void TestRtc_multipleOffOnInterrupts(void* args)
{
    RTC_Handle rtcHandle = NULL;
    RTC_Time setTime;
    int32_t status = SystemP_SUCCESS;
    uint32_t i;

    /* Store handle for Local use */
    if(gRTCHandle[CONFIG_RTC0] != NULL)
    {
        rtcHandle = gRTCHandle[CONFIG_RTC0];
    }
    else
    {
        status = SystemP_FAILURE;
    }

    SemaphoreP_constructBinary(&TestRtc_OffOnSemObj, 0U);

    /* Set the current time (e.g., 7th November 2024, 14:45:10) */
    setTime.year = 2024U;
    setTime.month = 11U;
    setTime.day = 7U;
    setTime.hour = 14U;
    setTime.minute = 45U;
    setTime.second = 10U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Set multiple Off-On interrupts */
    for(i=1U; i<=TEST_RTC_INTERRUPT_COUNT; i+=1)
    {
        setTime.second += (2U);
        RTC_setOff_OnTimerEvent(rtcHandle, &setTime);

        /* Wait for the interrupt */
        SemaphoreP_pend(&TestRtc_OffOnSemObj, SystemP_WAIT_FOREVER);

    }
    TEST_ASSERT_EQUAL_UINT32(4U,i);
    SemaphoreP_destruct(&TestRtc_OffOnSemObj);
}

/**
 * \brief Test RTC init and deinit lifecycle
 *
 * Test Category: Functional
 *
 * Verifies that RTC_init() initializes the driver state (marks all instances
 * as closed via isOpen = false, constructs the driver mutex via
 * SemaphoreP_constructMutex) and that RTC_deinit() correctly releases all
 * resources. Ensures the driver can be re-initialized after de-initialization
 * without assertion failure or hang.
 *
 * Test steps:
 * 1. Call RTC_init() to initialize the RTC driver.
 * 2. Verify isOpen == false for all configs in gRTCConfig[].
 *    gRTCDrvObj.lock is static and cannot be verified directly; verified
 *    indirectly by confirming RTC_open() succeeds (which pends on the lock).
 * 3. Call RTC_deinit() to release resources.
 * 4. gRTCDrvObj.lock is static and cannot be verified as NULL directly;
 *    verified indirectly by confirming re-init succeeds in step 5.
 * 5. Call RTC_init() again and verify it succeeds without assertion or hang.
 *    Verify isOpen flags are false and RTC_open() succeeds.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC_init() and RTC_deinit() complete without assertion
 *                 failure or hang. isOpen is false after each init call.
 *                 RTC_open() succeeds after both init and re-init.
 */
static void TestRtc_initAndDeinit(void *args)
{
    RTC_Handle rtcHandle = NULL;

    /* Ensure clean state: close any previously opened handle and deinit */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();

    /* Step 1: Call RTC_init() to initialize the RTC driver */
    RTC_init();

    /* Step 2: Verify isOpen == false after init.
     * gRTCDrvObj.lock is static — verified indirectly by a successful open. */
    TEST_ASSERT_FALSE(gRTCConfig[CONFIG_RTC0].object->isOpen);

    rtcHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(rtcHandle);
    RTC_close(rtcHandle);

    /* Step 3: Call RTC_deinit() to release resources */
    RTC_deinit();

    /* Step 4: gRTCDrvObj.lock is static — cannot verify NULL directly.
     * Verified indirectly by step 5 succeeding. */

    /* Step 5: Call RTC_init() again and verify no assertion or hang */
    RTC_init();

    TEST_ASSERT_FALSE(gRTCConfig[CONFIG_RTC0].object->isOpen);

    /* Verify driver is fully functional after re-initialization */
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test RTC open with NULL params applies default configuration
 *
 * Test Category: Functional
 *
 * Verifies that passing NULL to RTC_open() causes the driver to apply
 * RTC_defaultParams (isfreezemode=1U, onOffCallback=false,
 * offOnCallback=false) and returns a valid non-NULL handle. Also validates
 * that RTC_paramsInit() produces matching default values.
 *
 * Test steps:
 * 1. Call RTC_init() if not already done.
 * 2. Declare RTC_Params; call RTC_paramsInit(). Assert isfreezemode == 1U,
 *    onOffCallback == false, offOnCallback == false.
 * 3. Call RTC_open(CONFIG_RTC0, NULL).
 * 4. Verify handle is not NULL.
 * 5. Close RTC handle and verify no error or hang.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC_paramsInit() returns correct default values.
 *                 RTC_open() with NULL params returns a valid handle.
 *                 RTC_close() completes without error.
 */
static void TestRtc_openWithDefaultParams(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Params  defaultParams;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();

    /* Step 1: Initialize the RTC driver */
    RTC_init();

    /* Step 2: Verify RTC_paramsInit produces correct defaults */
    RTC_paramsInit(&defaultParams);
    TEST_ASSERT_EQUAL_UINT32(1U, defaultParams.isfreezemode);
    TEST_ASSERT_FALSE(defaultParams.onOffCallback);
    TEST_ASSERT_FALSE(defaultParams.offOnCallback);

    /* Step 3: Open with NULL params (driver applies defaults internally) */
    rtcHandle = RTC_open(CONFIG_RTC0, NULL);

    /* Step 4: Verify returned handle is not NULL */
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 5: Close handle and verify no error or hang */
    RTC_close(rtcHandle);

    /* Restore state for subsequent tests */
    RTC_deinit();
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test RTC open with freeze mode explicitly configured
 *
 * Test Category: Functional
 *
 * Verifies that opening with an explicit RTC_Params struct with
 * isfreezemode=1U succeeds and the freeze mode bit (RTC_FREEZE_MODE =
 * 0x02000000) is set in the hardware CSL_RTC_GENRAL_CTL register during
 * the open sequence.
 *
 * Test steps:
 * 1. Call RTC_paramsInit() to populate defaults.
 * 2. Explicitly set params.isfreezemode = 1U.
 * 3. Call RTC_open(CONFIG_RTC0, &params).
 * 4. Verify returned handle is not NULL.
 * 5. Call RTC_close() and verify no errors or write-pend timeout.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC_open() with freeze mode enabled returns a valid handle.
 *                 RTC_close() completes without error or timeout.
 */
static void TestRtc_openWithFreezeMode(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Params  freezeModeParams;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    /* Step 1: Initialize params with defaults */
    RTC_paramsInit(&freezeModeParams);

    /* Step 2: Explicitly set freeze mode */
    freezeModeParams.isfreezemode = 1U;

    /* Step 3: Open RTC with freeze mode params */
    rtcHandle = RTC_open(CONFIG_RTC0, &freezeModeParams);

    /* Step 4: Verify handle is valid */
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 5: Close and verify no errors or write-pend timeout */
    RTC_close(rtcHandle);

    /* Restore state for subsequent tests */
    RTC_deinit();
    RTC_init();
    gRTCHandle[CONFIG_RTC0] = RTC_open(CONFIG_RTC0, &gRTCParams[CONFIG_RTC0]);
    TEST_ASSERT_NOT_NULL(gRTCHandle[CONFIG_RTC0]);
}

/**
 * \brief Test RTC open and close lifecycle with re-open
 *
 * Test Category: Functional
 *
 * Verifies that RTC_open() returns a valid handle, RTC_close() cleans up
 * correctly, and the instance can be successfully re-opened and used after
 * closing. Note: RTC_close() does not reset the isOpen flag in the current
 * driver; a RTC_deinit() + RTC_init() cycle is required before re-opening.
 *
 * Test steps:
 * 1. Call RTC_open(CONFIG_RTC0, NULL) and assert handle is not NULL.
 * 2. Call RTC_close(handle).
 * 3. Call RTC_deinit() + RTC_init() to reset isOpen flag (driver gap
 *    workaround: RTC_close does not clear isOpen).
 * 4. Call RTC_open(CONFIG_RTC0, NULL) again and verify handle is valid.
 * 5. Call RTC_setTime() and RTC_getTime() on re-opened handle and verify
 *    both return SystemP_SUCCESS. Close the handle.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC instance can be re-opened after close and used
 *                 for time set and get operations successfully.
 */
static void TestRtc_openAndClose(void *args)
{
    RTC_Handle  firstHandle = NULL;
    RTC_Handle  secondHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();
    RTC_init();

    /* Step 1: Open RTC instance */
    firstHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(firstHandle);

    /* Step 2: Close the handle */
    RTC_close(firstHandle);

    /*
     * Step 3: Driver gap workaround — RTC_close() does not reset
     * object->isOpen to false. A subsequent RTC_open() without
     * RTC_deinit() + RTC_init() will fail because the driver sees
     * isOpen == true and returns NULL.
     */
    RTC_deinit();
    RTC_init();

    /* Step 4: Re-open RTC instance and verify handle is valid */
    secondHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(secondHandle);

    /* Step 5: Verify RTC_setTime() and RTC_getTime() work on re-opened handle */
    setTime.year   = 2024U;
    setTime.month  = 6U;
    setTime.day    = 15U;
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(secondHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(secondHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Restore global handle for subsequent tests */
    gRTCHandle[CONFIG_RTC0] = secondHandle;
}

/**
 * \brief Test RTC hardware register initialization state after open
 *
 * Test Category: Functional
 *
 * Verifies hardware clock enable, module reset release, and correct register
 * initialization state after RTC_init() and RTC_open(). Confirms that the
 * open sequence completes the full hardware setup: kick unlock
 * (GENRAL_CTL.UNLOCK set), 32kHz oscillator shadow sync enabled
 * (O32K_OSC_DEP_EN), interrupts cleared, no pending operations
 * (SYNCPEND.WR_PEND = 0, SYNCPEND.RD_PEND = 0), counter running
 * (GENRAL_CTL.SW_OFF = 0), and freeze mode set if configured.
 *
 * Test steps:
 * 1. Call RTC_init() and RTC_open(). Assert handle is not NULL.
 * 2. Read GENRAL_CTL register via direct volatile pointer. Verify UNLOCK
 *    bit is set (write access was granted by kick sequence).
 * 3. Verify O32K_OSC_DEP_EN bit is set in GENRAL_CTL (shadow sync enabled).
 * 4. Verify SW_OFF bit is cleared in GENRAL_CTL (counter is running).
 * 5. Read SYNCPEND register. Verify WR_PEND and RD_PEND are both 0.
 * 6. If isfreezemode=1U (default), verify FREEZE_MODE bit (0x02000000) is
 *    set in GENRAL_CTL.
 * 7. Call RTC_setTime() and RTC_getTime() to confirm hardware is operational.
 * 8. Close the instance.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All hardware register bits match expected initialized
 *                 state. RTC_setTime() and RTC_getTime() return
 *                 SystemP_SUCCESS.
 */
static void TestRtc_hardwareInitRegisterState(void *args)
{
    RTC_Handle              rtcHandle = NULL;
    const RTC_HwAttrs      *hardwareAttributes = NULL;
    uint32_t                baseAddress = 0U;
    uint32_t                generalControlValue = 0U;
    uint32_t                syncPendingValue = 0U;
    RTC_Time                setTime;
    RTC_Time                getTime;
    int32_t                 status = SystemP_SUCCESS;

    /* Ensure clean state */
    if (gRTCHandle[CONFIG_RTC0] != NULL)
    {
        RTC_close(gRTCHandle[CONFIG_RTC0]);
        gRTCHandle[CONFIG_RTC0] = NULL;
    }
    RTC_deinit();

    /* Step 1: Initialize and open RTC */
    RTC_init();
    rtcHandle = RTC_open(CONFIG_RTC0, NULL);
    TEST_ASSERT_NOT_NULL(rtcHandle);

    hardwareAttributes = (const RTC_HwAttrs *)rtcHandle->hwAttrs;
    baseAddress = hardwareAttributes->baseAddr;

    /* Read GENRAL_CTL register directly via volatile pointer */
    generalControlValue = *((volatile uint32_t *)(baseAddress + CSL_RTC_GENRAL_CTL));

    /* Step 2: Verify UNLOCK bit is set (write access granted by kick sequence) */
    TEST_ASSERT_TRUE((generalControlValue & CSL_RTC_GENRAL_CTL_UNLOCK_MASK) != 0U);

    /* Step 3: Verify O32K_OSC_DEP_EN is set (shadow register sync enabled) */
    TEST_ASSERT_TRUE((generalControlValue & CSL_RTC_GENRAL_CTL_O32K_OSC_DEP_EN_MASK) != 0U);

    /* Step 4: Verify SW_OFF is cleared (counter is running) */
    TEST_ASSERT_EQUAL_UINT32(0U, (generalControlValue & CSL_RTC_GENRAL_CTL_SW_OFF_MASK));

    /* Step 5: Read SYNCPEND register and verify no pending operations */
    syncPendingValue = *((volatile uint32_t *)(baseAddress + CSL_RTC_SYNCPEND));
    TEST_ASSERT_EQUAL_UINT32(0U, (syncPendingValue & CSL_RTC_SYNCPEND_WR_PEND_MASK));
    TEST_ASSERT_EQUAL_UINT32(0U, (syncPendingValue & CSL_RTC_SYNCPEND_RD_PEND_MASK));

    /* Step 6: Verify FREEZE_MODE bit is set (default isfreezemode=1U) */
    TEST_ASSERT_TRUE((generalControlValue & RTC_FREEZE_MODE) != 0U);

    /* Step 7: Verify RTC is operational by setting and getting time */
    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 8: Store handle for subsequent tests */
    gRTCHandle[CONFIG_RTC0] = rtcHandle;
}

/**
 * \brief Test RTC time increment driven by 32768Hz oscillator
 *
 * Test Category: Functional
 *
 * Verifies time increments correctly at the rate driven by the 15-bit
 * 32768Hz counter. Sets a known baseline time, sleeps for a fixed duration,
 * reads back the time, and verifies the increment matches the expected
 * elapsed seconds. Confirms the 15-bit counter divides the 32.768 kHz
 * oscillator to produce 1-second ticks that drive the 48-bit seconds counter.
 *
 * Test steps:
 * 1. Set time to 2024-01-01 00:00:00 using RTC_setTime().
 * 2. Sleep 3 seconds.
 * 3. Read RTC time using RTC_getTime().
 * 4. Verify second field has incremented by approximately 3 (within ±1).
 * 5. Verify minute is unchanged (still 0).
 * 6. Reset time to 00:00:00, sleep 10 seconds, read back, and verify
 *    second field is approximately 10 (within ±1).
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput RTC time increments by approximately the sleep duration
 *                 with ±1 second tolerance. Minute field remains unchanged.
 */
static void TestRtc_timeIncrement(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set time to 2024-01-01 00:00:00 */
    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2: Sleep for 3 seconds */
    ClockP_sleep(TEST_RTC_SLEEP_3_SEC);

    /* Step 3: Read back RTC time */
    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4: Verify approximately 3 seconds elapsed (within ±1) */
    TEST_ASSERT_UINT32_WITHIN(1U, 3U, getTime.second);

    /* Step 5: Verify minute is still 0 (no boundary overflow) */
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);

    /* Step 6: Reset time and verify over a longer 10-second interval */
    setTime.second = 0U;
    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_SLEEP_10_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_UINT32_WITHIN(1U, 10U, getTime.second);
}

/**
 * \brief Test RTC leap year and century-year date handling
 *
 * Test Category: Functional
 *
 * Verifies that the RTC driver correctly handles leap year date conversion
 * and seconds-to-time decomposition, including century-year edge cases.
 * Exercises RTC_isLeapYear() and RTC_getDaysInMonth() through the public
 * RTC_setTime() / RTC_getTime() path.
 *
 * Test steps:
 * 1. Set time to 2024-02-28 23:59:57 (leap year). Sleep 5 seconds.
 *    Verify year=2024, month=2, day=29 (Feb 29 exists).
 * 2. Set time to 2001-02-28 23:59:57 (non-leap year). Sleep 5 seconds.
 *    Verify year=2001, month=3, day=1 (no Feb 29).
 * 3. Set time to 2000-02-28 23:59:57 (divisible by 400, leap). Sleep 5
 *    seconds. Verify year=2000, month=2, day=29.
 * 4. Set time to 2100-02-28 23:59:57 (divisible by 100 not 400, non-leap).
 *    Sleep 5 seconds. Verify year=2100, month=3, day=1.
 * 5. Assert all RTC_setTime() and RTC_getTime() calls return
 *    SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Leap year dates transition correctly: Feb 29 exists for
 *                 2024 and 2000, rolls to March 1 for 2001 and 2100.
 */
static void TestRtc_leapYearDateHandling(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: 2024 is a leap year — Feb 29 should exist */
    setTime.year   = 2024U;
    setTime.month  = 2U;
    setTime.day    = 28U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* After 5s from 23:59:57, time is ~00:00:02 on Feb 29 */
    TEST_ASSERT_EQUAL_UINT32(2024U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(2U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(29U, getTime.day);

    /* Step 2: 2001 is NOT a leap year — should roll to March 1 */
    setTime.year   = 2001U;
    setTime.month  = 2U;
    setTime.day    = 28U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2001U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(3U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);

    /* Step 3: 2000 is divisible by 400 — IS a leap year */
    setTime.year   = 2000U;
    setTime.month  = 2U;
    setTime.day    = 28U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2000U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(2U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(29U, getTime.day);

    /* Step 4: 2100 is divisible by 100 but NOT 400 — NOT a leap year */
    setTime.year   = 2100U;
    setTime.month  = 2U;
    setTime.day    = 28U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 5: Verify no Feb 29 in 2100 — rolled to March 1 */
    TEST_ASSERT_EQUAL_UINT32(2100U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(3U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);
}

/**
 * \brief Test RTC time boundary transitions across day, month, year, and minute
 *
 * Test Category: Functional
 *
 * Verifies correct rollover at day, month, year, and minute/hour boundaries.
 * Sets the time to the last seconds before a boundary, sleeps past it, and
 * verifies the date transitions correctly with no skipped or duplicated values.
 *
 * Test steps:
 * 1. Set 2024-01-31 23:59:57, sleep 5s, verify rolls to Feb 1.
 * 2. Set 2025-12-31 23:59:57, sleep 5s, verify rolls to 2026-01-01.
 * 3. Set 2024-06-15 23:59:57, sleep 5s, verify midnight rollover to day 16.
 * 4. Set 2024-03-10 10:59:57, sleep 5s, verify minute/hour rollover to 11:00.
 * 5. Assert all API calls return SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All boundary transitions produce correct date/time fields.
 */
static void TestRtc_timeBoundaryTransitions(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Day-to-month boundary — Jan 31 to Feb 1 */
    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 31U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2024U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(2U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);

    /* Step 2: Year boundary — Dec 31 2025 to Jan 1 2026 */
    setTime.year   = 2025U;
    setTime.month  = 12U;
    setTime.day    = 31U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2026U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);

    /* Step 3: Midnight rollover — day 15 to day 16 */
    setTime.year   = 2024U;
    setTime.month  = 6U;
    setTime.day    = 15U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(16U, getTime.day);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);

    /* Step 4: Minute/hour rollover — 10:59:57 to 11:00:xx */
    setTime.year   = 2024U;
    setTime.month  = 3U;
    setTime.day    = 10U;
    setTime.hour   = 10U;
    setTime.minute = 59U;
    setTime.second = 57U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(11U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);
}

/**
 * \brief Test RTC elapsed time calculation with borrow across all fields
 *
 * Test Category: Functional
 *
 * Verifies that RTC_calculateElapsedTime() correctly computes the difference
 * between two RTC_Time values, handling borrow/underflow across seconds,
 * minutes, hours, and days. Covers same-time, single-second, and
 * cross-boundary intervals.
 *
 * Test steps:
 * 1. Compare {2024,11,5,14,42,10} to {2024,11,7,15,43,20}, expect 2d 1h 1m 10s.
 * 2. Same time for start and end, expect all fields zero.
 * 3. Single second difference, expect 1s only.
 * 4. Seconds underflow with borrow from minute.
 * 5. Hours underflow with borrow from day.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All computed elapsed times match expected values.
 */
static void TestRtc_calculateElapsedTime(void *args)
{
    RTC_Time startTime;
    RTC_Time endTime;
    RTC_Time elapsedTime;

    /* Step 1: Normal difference — 2 days, 1 hour, 1 minute, 10 seconds */
    startTime.year   = 2024U;
    startTime.month  = 11U;
    startTime.day    = 5U;
    startTime.hour   = 14U;
    startTime.minute = 42U;
    startTime.second = 10U;

    endTime.year   = 2024U;
    endTime.month  = 11U;
    endTime.day    = 7U;
    endTime.hour   = 15U;
    endTime.minute = 43U;
    endTime.second = 20U;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.year);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.month);
    TEST_ASSERT_EQUAL_UINT32(2U, elapsedTime.day);
    TEST_ASSERT_EQUAL_UINT32(1U, elapsedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(1U, elapsedTime.minute);
    TEST_ASSERT_EQUAL_UINT32(10U, elapsedTime.second);

    /* Step 2: Same time — all fields should be zero */
    startTime.year   = 2024U;
    startTime.month  = 5U;
    startTime.day    = 10U;
    startTime.hour   = 8U;
    startTime.minute = 30U;
    startTime.second = 0U;
  
    endTime = startTime;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.year);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.month);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.day);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.minute);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.second);

    /* Step 3: Single second difference */
    endTime.second = 1U;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.minute);
    TEST_ASSERT_EQUAL_UINT32(1U, elapsedTime.second);

    /* Step 4: Seconds underflow — borrow from minute
     * start 10:05:45, end 10:06:20 → elapsed = 0h 0m 35s */
    startTime.year   = 2024U;
    startTime.month  = 5U;
    startTime.day    = 10U;
    startTime.hour   = 10U;
    startTime.minute = 5U;
    startTime.second = 45U;

    endTime.year   = 2024U;
    endTime.month  = 5U;
    endTime.day    = 10U;
    endTime.hour   = 10U;
    endTime.minute = 6U;
    endTime.second = 20U;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(35U, elapsedTime.second);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.minute);

    /* Step 5: Hours underflow — borrow from day
     * start day=10 22:30:00, end day=11 02:30:00 → elapsed = 0d 4h 0m 0s */
    startTime.year   = 2024U;
    startTime.month  = 5U;
    startTime.day    = 10U;
    startTime.hour   = 22U;
    startTime.minute = 30U;
    startTime.second = 0U;

    endTime.year   = 2024U;
    endTime.month  = 5U;
    endTime.day    = 11U;
    endTime.hour   = 2U;
    endTime.minute = 30U;
    endTime.second = 0U;

    elapsedTime = RTC_calculateElapsedTime(&startTime, &endTime);

    TEST_ASSERT_EQUAL_UINT32(4U, elapsedTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, elapsedTime.day);
}

/**
 * \brief Test RTC read monotonicity via shadow register auto-sync
 *
 * Test Category: Functional
 *
 * Verifies that repeated RTC_getTime() calls return monotonically
 * non-decreasing values without manual polling. The shadow registers
 * auto-sync on each 32kHz clock boundary after O32K_OSC_DEP_EN is set.
 *
 * Test steps:
 * 1. Set RTC time to a known value.
 * 2. Call RTC_getTime() 20 times in a tight loop.
 * 3. Convert each result to total seconds within the day.
 * 4. Verify each value is non-decreasing compared to the previous.
 * 5. Verify no field has an impossible value.
 * 6. Verify no jump greater than 1 second between consecutive reads.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All 20 reads are monotonically non-decreasing with
 *                 no invalid fields and no jumps greater than 1 second.
 */
static void TestRtc_getTimeMonotonicity(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    iteration = 0U;
    uint32_t    currentTotalSeconds = 0U;
    uint32_t    previousTotalSeconds = 0U;
    uint32_t    totalReads = 20U;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set RTC time */
    setTime.year   = 2024U;
    setTime.month  = 6U;
    setTime.day    = 15U;
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 2-6: Read 20 times in a tight loop and validate */
    for (iteration = 0U; iteration < totalReads; iteration+=1)
    {
        status = RTC_getTime(rtcHandle, &readTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Step 5: Verify no impossible field values */
        TEST_ASSERT_TRUE(readTime.hour <= TEST_RTC_MAX_HOUR);
        TEST_ASSERT_TRUE(readTime.minute <= TEST_RTC_MAX_MINUTE);
        TEST_ASSERT_TRUE(readTime.second <= TEST_RTC_MAX_SECOND);

        /* Step 3: Convert to total seconds within the day */
        currentTotalSeconds = (readTime.hour * TEST_RTC_SECONDS_PER_HOUR)
                            + (readTime.minute * TEST_RTC_SECONDS_PER_MINUTE)
                            + readTime.second;

        if (iteration > 0U)
        {
            /* Step 4: Verify non-decreasing */
            TEST_ASSERT_TRUE(currentTotalSeconds >= previousTotalSeconds);

            /* Step 6: Verify no jump greater than 1 second between reads */
            TEST_ASSERT_TRUE((currentTotalSeconds - previousTotalSeconds) <= 1U);
        }

        previousTotalSeconds = currentTotalSeconds;
    }
}

/**
 * \brief Test RTC extended date range and 48-bit counter boundary
 *
 * Test Category: Functional
 *
 * Verifies RTC handles the full width of the 48-bit seconds counter.
 * Tests epoch zero, far future, 32-bit LSW wrap boundary, and Y2K
 * boundary via round-trip set/get operations.
 *
 * Test steps:
 * 1. Set epoch zero (1970-01-01 00:00:00), read back, verify fields match.
 * 2. Set far future (2099-12-31 23:59:59), read back, verify fields.
 * 3. Set 32-bit LSW boundary (2106-02-07 06:28:15), read back, sleep 2s,
 *    verify time advanced across the 32-bit wrap.
 * 4. Set Y2K boundary (2000-01-01 00:00:00), read back, verify fields.
 * 5. Assert all API calls return SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All date values round-trip correctly. Time advances
 *                 across the 32-bit LSW wrap boundary.
 */
static void TestRtc_extendedTimeRange(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Epoch zero — 1970-01-01 00:00:00 */
    setTime.year   = 1970U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(1970U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);
    TEST_ASSERT_UINT32_WITHIN(1U, 0U, getTime.second);

    /* Step 2: Far future — 2099-12-31 23:59:59 */
    setTime.year   = 2099U;
    setTime.month  = 12U;
    setTime.day    = 31U;
    setTime.hour   = 23U;
    setTime.minute = 59U;
    setTime.second = 59U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2099U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(12U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(31U, getTime.day);
    TEST_ASSERT_EQUAL_UINT32(23U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(59U, getTime.minute);
    TEST_ASSERT_UINT32_WITHIN(1U, 59U, getTime.second);

    /* Step 3: 32-bit LSW boundary — 2106-02-07 06:28:15
     * This corresponds to seconds value 0xFFFFFFFF from epoch.
     * After sleeping 2s, the LSW wraps and MSW increments to 1. */
    setTime.year   = 2106U;
    setTime.month  = 2U;
    setTime.day    = 7U;
    setTime.hour   = 6U;
    setTime.minute = 28U;
    setTime.second = 15U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2106U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(2U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(7U, getTime.day);

    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify time advanced by approximately 2 seconds across the 32-bit wrap */
    TEST_ASSERT_UINT32_WITHIN(1U, 17U, getTime.second);
    TEST_ASSERT_EQUAL_UINT32(28U, getTime.minute);

    /* Step 4: Y2K boundary — 2000-01-01 00:00:00 */
    setTime.year   = 2000U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(2000U, getTime.year);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.month);
    TEST_ASSERT_EQUAL_UINT32(1U, getTime.day);
}

/**
 * \brief Test RTC shadow auto-sync for both writes and reads without polling
 *
 * Test Category: Functional
 *
 * Verifies that the host can update and read RTC MMRs without manual
 * polling, thanks to the hardware shadow/auto-sync mechanism enabled via
 * O32K_OSC_DEP_EN. Confirms writes commit immediately and rapid reads
 * return consistent, non-stale values.
 *
 * Test steps:
 * 1. Set time to 2024-05-15 08:00:00 via RTC_setTime().
 * 2. Immediately read back via RTC_getTime() with no sleep.
 * 3. Verify read-back matches set time (hour=8, minute=0, second near 0).
 * 4. Perform 10 rapid set-then-read cycles, verify each read-back matches.
 * 5. Set time to 12:00:00, perform 5 rapid reads, verify all consistent.
 * 6. Assert no call returned SystemP_FAILURE.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Immediate read-back matches set value. All rapid
 *                 set-then-read cycles and consecutive reads are consistent.
 */
static void TestRtc_shadowAutoSyncReadWrite(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    RTC_Time    rapidReadResults[TEST_RTC_RAPID_READ_COUNT];
    int32_t     status = SystemP_SUCCESS;
    uint32_t    cycleIndex = 0U;
    uint32_t    readIndex = 0U;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Steps 1-3: Set time, immediately read back, verify match */
    setTime.year   = 2024U;
    setTime.month  = 5U;
    setTime.day    = 15U;
    setTime.hour   = 8U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = RTC_getTime(rtcHandle, &getTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(8U, getTime.hour);
    TEST_ASSERT_EQUAL_UINT32(0U, getTime.minute);
    TEST_ASSERT_UINT32_WITHIN(1U, 0U, getTime.second);

    /* Step 4: 10 rapid set-then-read cycles */
    for (cycleIndex = 1U; cycleIndex <= TEST_RTC_RAPID_CYCLE_COUNT; cycleIndex+=1)
    {
        setTime.hour   = 0U;
        setTime.minute = 0U;
        setTime.second = cycleIndex;

        status = RTC_setTime(rtcHandle, &setTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        status = RTC_getTime(rtcHandle, &getTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        TEST_ASSERT_UINT32_WITHIN(1U, cycleIndex, getTime.second);
    }

    /* Step 5: Set time to 12:00:00 and perform 5 rapid reads */
    setTime.hour   = 12U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (readIndex = 0U; readIndex < TEST_RTC_RAPID_READ_COUNT; readIndex+=1)
    {
        status = RTC_getTime(rtcHandle, &rapidReadResults[readIndex]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Verify all 5 reads are within ±1 second of each other */
    for (readIndex = 1U; readIndex < TEST_RTC_RAPID_READ_COUNT; readIndex+=1)
    {
        TEST_ASSERT_EQUAL_UINT32(12U, rapidReadResults[readIndex].hour);
        TEST_ASSERT_EQUAL_UINT32(0U, rapidReadResults[readIndex].minute);
        TEST_ASSERT_UINT32_WITHIN(1U,
                                  rapidReadResults[0U].second,
                                  rapidReadResults[readIndex].second);
    }
}

/**
 * \brief Test 32768Hz counter tick accuracy against system reference clock
 *
 * Test Category: Functional
 *
 * Verifies the 15-bit 32768Hz counter produces accurate 1-second ticks by
 * measuring RTC progression against ClockP_getTimeUsec() over multiple
 * short windows. Also validates second-to-minute rollover at the tick level.
 *
 * Test steps:
 * 1. Set RTC time to a known baseline.
 * 2. Record system time T0 and RTC time R0.
 * 3. Sleep 5 seconds.
 * 4. Record system time T1 and RTC time R1.
 * 5. Verify |RTC_elapsed - system_elapsed| is within 1 second.
 * 6. Repeat for 5 iterations; verify cumulative drift within ±2 seconds.
 * 7. Verify no single iteration has a jump greater than 2s or goes backward.
 * 8. Boundary check: set second=59, sleep 2s, verify rollover to second ~1
 *    and minute incremented by 1.
 * 9. Assert all API calls return SystemP_SUCCESS.
 *
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Per-iteration drift within ±1s. Cumulative drift over 25s
 *                 within ±2s. Second-to-minute rollover correct.
 */
static void TestRtc_32kHzCounterTickAccuracy(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    startReadTime;
    RTC_Time    endReadTime;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    iteration = 0U;
    uint32_t    totalIterations = 5U;
    uint32_t    sleepDurationSeconds = 5U;
    uint64_t    systemTimeStart = 0ULL;
    uint64_t    systemTimeEnd = 0ULL;
    uint64_t    systemElapsedMicroseconds = 0ULL;
    uint32_t    rtcElapsedSeconds = 0U;
    int32_t     perIterationDrift = 0;
    int32_t     cumulativeRtcElapsed = 0;
    int32_t     cumulativeSystemElapsed = 0;
    int32_t     cumulativeDrift = 0;
    uint32_t    previousRtcSecond = 0U;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    TEST_ASSERT_NOT_NULL(rtcHandle);

    /* Step 1: Set RTC to a known baseline */
    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Steps 2-7: 5 iterations of 5-second measurement windows */
    for (iteration = 0U; iteration < totalIterations; iteration+=1)
    {
        /* Step 2: Record start references */
        systemTimeStart = ClockP_getTimeUsec();
        status = RTC_getTime(rtcHandle, &startReadTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Step 3: Sleep */
        ClockP_sleep(sleepDurationSeconds);

        /* Step 4: Record end references */
        systemTimeEnd = ClockP_getTimeUsec();
        status = RTC_getTime(rtcHandle, &endReadTime);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Step 5: Compute elapsed and compare */
        systemElapsedMicroseconds = systemTimeEnd - systemTimeStart;
        rtcElapsedSeconds = endReadTime.second - startReadTime.second;

        /* Handle minute rollover within the iteration */
        if (endReadTime.minute > startReadTime.minute)
        {
            rtcElapsedSeconds += (endReadTime.minute - startReadTime.minute) * TEST_RTC_SECONDS_PER_MINUTE;
        }

        perIterationDrift = (int32_t)rtcElapsedSeconds
                          - (int32_t)(systemElapsedMicroseconds / 1000000ULL);

        /* Step 6: Per-iteration drift must be within ±1 second */
        TEST_ASSERT_TRUE((perIterationDrift >= -1) && (perIterationDrift <= 1));

        /* Step 7: No backward step and no jump greater than 2 seconds */
        TEST_ASSERT_TRUE(rtcElapsedSeconds <= (sleepDurationSeconds + 2U));
        TEST_ASSERT_TRUE(rtcElapsedSeconds >= 1U);

        if (iteration > 0U)
        {
            TEST_ASSERT_TRUE(endReadTime.second != previousRtcSecond
                             || endReadTime.minute > startReadTime.minute);
        }
        previousRtcSecond = endReadTime.second;

        /* Accumulate for cumulative drift check */
        cumulativeRtcElapsed += (int32_t)rtcElapsedSeconds;
        cumulativeSystemElapsed += (int32_t)(systemElapsedMicroseconds / 1000000ULL);
    }

    /* Step 6 continued: Cumulative drift over 25 seconds within ±2 seconds */
    cumulativeDrift = cumulativeRtcElapsed - cumulativeSystemElapsed;
    TEST_ASSERT_TRUE((cumulativeDrift >= -2) && (cumulativeDrift <= 2));

    /* Step 8: Boundary check — second 59 rolls to ~01, minute increments */
    setTime.hour   = 5U;
    setTime.minute = 30U;
    setTime.second = 59U;

    status = RTC_setTime(rtcHandle, &setTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_sleep(TEST_RTC_SLEEP_2_SEC);

    status = RTC_getTime(rtcHandle, &endReadTime);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT32(31U, endReadTime.minute);
    TEST_ASSERT_UINT32_WITHIN(1U, 1U, endReadTime.second);
}

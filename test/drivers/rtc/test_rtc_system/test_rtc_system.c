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
 *  \file test_rtc_system.c
 *
 *  \brief This file contains implementation of all module test cases
 *         for RTC system tests across multiple cores.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <unity.h>
#include <drivers/rtc.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                               Macros                                       */
/* ========================================================================== */

#define TEST_RTC_ALARM_WAIT_SEC              (5U)
#define TEST_RTC_SCRATCH_REGISTER_COUNT      (8U)

#define TEST_RTC_MAX_HOUR                    (23U)
#define TEST_RTC_MAX_MINUTE                  (59U)
#define TEST_RTC_MAX_SECOND                  (59U)
#define TEST_RTC_SECONDS_PER_HOUR            (3600U)
#define TEST_RTC_SECONDS_PER_MINUTE          (60U)

#define TEST_RTC_SLEEP_2_SEC                 (2U)
#define TEST_RTC_SLEEP_3_SEC                 (3U)

#define TEST_RTC_PATTERN_ALL_ZEROS           (0x00000000U)
#define TEST_RTC_PATTERN_ALL_ONES            (0xFFFFFFFFU)
#define TEST_RTC_PATTERN_ALT_A               (0xAAAAAAAAU)
#define TEST_RTC_PATTERN_ALT_5               (0x55555555U)
#define TEST_RTC_PATTERN_DEAD_BASE           (0xDEAD0000U)

#define TEST_RTC_SEM_TIMEOUT_10_SEC          (10000000U)

#define TEST_RTC_MONOTONICITY_READS          (20U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static SemaphoreP_Object TestRtc_OnOffSemObj;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void TestRtc_onOffCallback(RTC_Handle handle);

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/**
 * \brief On-Off timer event callback function
 *
 * Posts the binary semaphore to signal the alarm event has fired.
 *
 * \param handle  RTC driver handle (unused)
 */
void TestRtc_onOffCallback(RTC_Handle handle)
{
    SemaphoreP_post(&TestRtc_OnOffSemObj);
}

/**
 * \brief Wait for all pending BBD writes to commit, then reload shadow registers.
 *
 * RTC_writeScratchRegister() writes to the battery-backed domain (BBD)
 * without waiting for WR_PEND. In freeze mode (the default after RTC_open),
 * the shadow registers are NOT auto-refreshed from BBD, so reading back a
 * scratch register immediately returns the STALE old BBD value.
 *
 * This helper mirrors what RTC_hwiFxn() does before reading any BBD register:
 *   1. Poll WR_PEND until all pending writes have committed to BBD.
 *   2. Trigger a one-shot RELOAD_FROM_BBD to pull current BBD values into shadow.
 *   3. Poll RD_PEND until the reload is complete.
 *
 * Call this between a write pass and the subsequent read pass in any test that
 * needs to verify scratch register contents.
 */
static void TestRtc_waitAndReloadBBD(void)
{
    volatile uint32_t *syncPend =
        (volatile uint32_t *)((uint32_t)RTC_BASEADDR + CSL_RTC_SYNCPEND);

    /* Step 1: wait for all pending BBD writes to complete */
    while ((*syncPend & WR_PEND_MASK) != 0U) {}

    /* Step 2: trigger a one-shot BBD → shadow reload */
    *syncPend |= CSL_RTC_SYNCPEND_RELOAD_FROM_BBD_MASK;

    /* Step 3: wait for the reload to complete */
    while ((*syncPend & RD_PEND_MASK) != 0U) {}
}

/**
 * \brief Test RTC set time and get time from each core
 *
 * Sets a known time on the shared RTC instance and reads it back after
 * a fixed delay. Verifies the time has advanced by approximately the
 * sleep duration. Each core runs this test independently against the
 * shared RTC hardware to validate multicore read/write access.
 *
 * \param args  Pointer to test arguments (unused)
 *
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise
 */
int32_t TestRtc_setGetTime(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    int32_t     status = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    if (rtcHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    /* Set the current time to 5th November 2024, 14:42:10 */
    setTime.year   = 2024U;
    setTime.month  = 11U;
    setTime.day    = 5U;
    setTime.hour   = 14U;
    setTime.minute = 42U;
    setTime.second = 10U;

    status = RTC_setTime(rtcHandle, &setTime);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Core[%d]: RTC_setTime failed\r\n", IpcNotify_getSelfCoreId());
        return SystemP_FAILURE;
    }

    /* Wait for 5 seconds */
    ClockP_sleep(TEST_RTC_ALARM_WAIT_SEC);

    /* In freeze mode (enabled by default in newer syscfg tool v1.24+), shadow
     * registers are NOT auto-updated from BBD. Reload explicitly so that
     * RTC_getTime reflects the BBD counter which kept running during sleep. */
    TestRtc_waitAndReloadBBD();

    /* Retrieve the time */
    status = RTC_getTime(rtcHandle, &getTime);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Core[%d]: RTC_getTime failed\r\n", IpcNotify_getSelfCoreId());
        return SystemP_FAILURE;
    }

    /* Verify elapsed time accounting for possible minute rollover */
    uint32_t setTotalSeconds = (setTime.minute * TEST_RTC_SECONDS_PER_MINUTE) + setTime.second;
    uint32_t getTotalSeconds = (getTime.minute * TEST_RTC_SECONDS_PER_MINUTE) + getTime.second;
    uint32_t elapsedSeconds;
    if (getTotalSeconds >= setTotalSeconds)
    {
        elapsedSeconds = getTotalSeconds - setTotalSeconds;
    }
    else
    {
        elapsedSeconds = (TEST_RTC_SECONDS_PER_HOUR + getTotalSeconds) - setTotalSeconds;
    }
    if ((elapsedSeconds < 4U) || (elapsedSeconds > 6U))
    {
        DebugP_log("Core[%d]: Unexpected elapsed seconds %u\r\n",
                   IpcNotify_getSelfCoreId(), elapsedSeconds);
        return SystemP_FAILURE;
    }

    DebugP_log("Core[%d]: TestRtc_setGetTime PASSED\r\n", IpcNotify_getSelfCoreId());
    return SystemP_SUCCESS;
}

/**
 * \brief Test RTC time increment and read monotonicity from each core
 *
 * Sets a known baseline time, sleeps for a fixed duration, and verifies
 * the time advanced correctly. Then performs multiple rapid consecutive
 * reads and verifies all returned values are monotonically non-decreasing
 * with no field containing impossible values.
 *
 * \param args  Pointer to test arguments (unused)
 *
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise
 */
int32_t TestRtc_timeIncrementAndMonotonicity(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    getTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    iteration = 0U;
    uint32_t    currentTotalSeconds = 0U;
    uint32_t    previousTotalSeconds = 0U;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    if (rtcHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    /* Set time to 2024-01-01 00:00:00 */
    setTime.year   = 2024U;
    setTime.month  = 1U;
    setTime.day    = 1U;
    setTime.hour   = 0U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    if (status != SystemP_SUCCESS)
    {
        return SystemP_FAILURE;
    }

    /* Sleep for 3 seconds */
    ClockP_sleep(TEST_RTC_SLEEP_3_SEC);

    /* Read back and verify approximately 3 seconds elapsed */
    status = RTC_getTime(rtcHandle, &getTime);
    if (status != SystemP_SUCCESS)
    {
        return SystemP_FAILURE;
    }

    if ((getTime.second < 2U) || (getTime.second > 4U))
    {
        DebugP_log("Core[%d]: Time increment check failed, second=%u\r\n",
                   IpcNotify_getSelfCoreId(), getTime.second);
        return SystemP_FAILURE;
    }

    /* Verify minute did not overflow */
    if (getTime.minute != 0U)
    {
        DebugP_log("Core[%d]: Unexpected minute overflow\r\n",
                   IpcNotify_getSelfCoreId());
        return SystemP_FAILURE;
    }

    /* Perform 20 rapid reads and verify monotonicity */
    for (iteration = 0U; iteration < TEST_RTC_MONOTONICITY_READS; iteration += 1)
    {
        status = RTC_getTime(rtcHandle, &readTime);
        if (status != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }

        /* Verify no impossible field values */
        if ((readTime.hour > TEST_RTC_MAX_HOUR) ||
            (readTime.minute > TEST_RTC_MAX_MINUTE) ||
            (readTime.second > TEST_RTC_MAX_SECOND))
        {
            DebugP_log("Core[%d]: Invalid time field detected\r\n",
                       IpcNotify_getSelfCoreId());
            return SystemP_FAILURE;
        }

        currentTotalSeconds = (readTime.hour * TEST_RTC_SECONDS_PER_HOUR)
                            + (readTime.minute * TEST_RTC_SECONDS_PER_MINUTE)
                            + readTime.second;

        if (iteration > 0U)
        {
            /* Verify non-decreasing */
            if (currentTotalSeconds < previousTotalSeconds)
            {
                DebugP_log("Core[%d]: Monotonicity violation at iteration %u\r\n",
                           IpcNotify_getSelfCoreId(), iteration);
                return SystemP_FAILURE;
            }

            /* Verify no jump greater than 1 second between reads */
            if ((currentTotalSeconds - previousTotalSeconds) > 1U)
            {
                DebugP_log("Core[%d]: Time jump detected at iteration %u\r\n",
                           IpcNotify_getSelfCoreId(), iteration);
                return SystemP_FAILURE;
            }
        }

        previousTotalSeconds = currentTotalSeconds;
    }

    DebugP_log("Core[%d]: TestRtc_timeIncrementAndMonotonicity PASSED\r\n",
               IpcNotify_getSelfCoreId());
    return SystemP_SUCCESS;
}

/**
 * \brief Test RTC scratch register read/write from each core
 *
 * Writes multiple patterns (all-zeros, all-ones, alternating, unique)
 * to all 8 scratch registers and reads them back to verify data
 * integrity. Also verifies independence between adjacent registers.
 * Each core exercises the shared scratch pad to validate multicore
 * register access.
 *
 * \param args  Pointer to test arguments (unused)
 *
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise
 */
int32_t TestRtc_scratchRegisterReadWrite(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    int32_t     status = SystemP_SUCCESS;
    uint32_t    registerIndex = 0U;
    uint32_t    readValue = 0U;
    uint32_t    totalRegisters = TEST_RTC_SCRATCH_REGISTER_COUNT;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    if (rtcHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    /* Write all zeros and verify */
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex += 1)
    {
        status = RTC_writeScratchRegister(rtcHandle, registerIndex, TEST_RTC_PATTERN_ALL_ZEROS);
        if (status != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }
    }
    /* Wait for BBD writes to commit then reload shadow registers before reading */
    TestRtc_waitAndReloadBBD();
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex += 1)
    {
        readValue = RTC_readScratchRegister(rtcHandle, registerIndex);
        if (readValue != TEST_RTC_PATTERN_ALL_ZEROS)
        {
            DebugP_log("Core[%d]: Scratch[%u] all-zeros mismatch: 0x%08X\r\n",
                       IpcNotify_getSelfCoreId(), registerIndex, readValue);
            return SystemP_FAILURE;
        }
    }

    /* Write all ones and verify */
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex += 1)
    {
        status = RTC_writeScratchRegister(rtcHandle, registerIndex, TEST_RTC_PATTERN_ALL_ONES);
        if (status != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }
    }
    /* Wait for BBD writes to commit then reload shadow registers before reading */
    TestRtc_waitAndReloadBBD();
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex += 1)
    {
        readValue = RTC_readScratchRegister(rtcHandle, registerIndex);
        if (readValue != TEST_RTC_PATTERN_ALL_ONES)
        {
            DebugP_log("Core[%d]: Scratch[%u] all-ones mismatch: 0x%08X\r\n",
                       IpcNotify_getSelfCoreId(), registerIndex, readValue);
            return SystemP_FAILURE;
        }
    }

    /* Write alternating patterns and verify */
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex += 1)
    {
        if ((registerIndex % 2U) == 0U)
        {
            status = RTC_writeScratchRegister(rtcHandle, registerIndex, TEST_RTC_PATTERN_ALT_A);
        }
        else
        {
            status = RTC_writeScratchRegister(rtcHandle, registerIndex, TEST_RTC_PATTERN_ALT_5);
        }
        if (status != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }
    }
    /* Wait for BBD writes to commit then reload shadow registers before reading */
    TestRtc_waitAndReloadBBD();
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex += 1)
    {
        readValue = RTC_readScratchRegister(rtcHandle, registerIndex);
        if ((registerIndex % 2U) == 0U)
        {
            if (readValue != TEST_RTC_PATTERN_ALT_A)
            {
                return SystemP_FAILURE;
            }
        }
        else
        {
            if (readValue != TEST_RTC_PATTERN_ALT_5)
            {
                return SystemP_FAILURE;
            }
        }
    }

    /* Write unique value per register and verify */
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex += 1)
    {
        status = RTC_writeScratchRegister(rtcHandle, registerIndex,
                                         TEST_RTC_PATTERN_DEAD_BASE + registerIndex);
        if (status != SystemP_SUCCESS)
        {
            return SystemP_FAILURE;
        }
    }
    /* Wait for BBD writes to commit then reload shadow registers before reading */
    TestRtc_waitAndReloadBBD();
    for (registerIndex = 0U; registerIndex < totalRegisters; registerIndex += 1)
    {
        readValue = RTC_readScratchRegister(rtcHandle, registerIndex);
        if (readValue != (TEST_RTC_PATTERN_DEAD_BASE + registerIndex))
        {
            DebugP_log("Core[%d]: Scratch[%u] unique mismatch: 0x%08X\r\n",
                       IpcNotify_getSelfCoreId(), registerIndex, readValue);
            return SystemP_FAILURE;
        }
    }

    DebugP_log("Core[%d]: TestRtc_scratchRegisterReadWrite PASSED\r\n",
               IpcNotify_getSelfCoreId());
    return SystemP_SUCCESS;
}

/**
 * \brief Test RTC alarm fires correctly with On-Off timer event
 *
 * Sets a known time, arms an On-Off alarm 5 seconds in the future,
 * and verifies the callback fires at the expected time via a binary
 * semaphore. Each core exercises the alarm mechanism to validate
 * multicore interrupt delivery.
 *
 * \param args  Pointer to test arguments (unused)
 *
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise
 */
int32_t TestRtc_alarmOnOffEvent(void *args)
{
    RTC_Handle  rtcHandle = NULL;
    RTC_Time    setTime;
    RTC_Time    alarmTime;
    RTC_Time    readTime;
    int32_t     status = SystemP_SUCCESS;
    int32_t     semaphoreStatus = SystemP_SUCCESS;

    rtcHandle = gRTCHandle[CONFIG_RTC0];
    if (rtcHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    /* Set RTC time to 2024-03-15 10:00:00 */
    setTime.year   = 2024U;
    setTime.month  = 3U;
    setTime.day    = 15U;
    setTime.hour   = 10U;
    setTime.minute = 0U;
    setTime.second = 0U;

    status = RTC_setTime(rtcHandle, &setTime);
    if (status != SystemP_SUCCESS)
    {
        return SystemP_FAILURE;
    }

    /* Construct binary semaphore */
    SemaphoreP_constructBinary(&TestRtc_OnOffSemObj, 0U);

    /* Arm On-Off alarm at 10:00:05 */
    alarmTime        = setTime;
    alarmTime.second = 5U;

    status = RTC_setOn_OffTimerEvent(rtcHandle, &alarmTime);
    if (status != SystemP_SUCCESS)
    {
        SemaphoreP_destruct(&TestRtc_OnOffSemObj);
        return SystemP_FAILURE;
    }

    /* Pend on semaphore with 10-second timeout */
    semaphoreStatus = SemaphoreP_pend(&TestRtc_OnOffSemObj,
                                      ClockP_usecToTicks(TEST_RTC_SEM_TIMEOUT_10_SEC));
    if (semaphoreStatus != SystemP_SUCCESS)
    {
        DebugP_log("Core[%d]: Alarm semaphore timed out\r\n",
                   IpcNotify_getSelfCoreId());
        SemaphoreP_destruct(&TestRtc_OnOffSemObj);
        return SystemP_FAILURE;
    }

    /* Verify RTC second field is approximately 5 */
    status = RTC_getTime(rtcHandle, &readTime);
    if (status != SystemP_SUCCESS)
    {
        SemaphoreP_destruct(&TestRtc_OnOffSemObj);
        return SystemP_FAILURE;
    }

    if ((readTime.second < 4U) || (readTime.second > 6U))
    {
        DebugP_log("Core[%d]: Alarm fired at unexpected second %u\r\n",
                   IpcNotify_getSelfCoreId(), readTime.second);
        SemaphoreP_destruct(&TestRtc_OnOffSemObj);
        return SystemP_FAILURE;
    }

    SemaphoreP_destruct(&TestRtc_OnOffSemObj);

    DebugP_log("Core[%d]: TestRtc_alarmOnOffEvent PASSED\r\n",
               IpcNotify_getSelfCoreId());
    return SystemP_SUCCESS;
}




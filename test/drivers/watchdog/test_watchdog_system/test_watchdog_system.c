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
 *  \file test_watchdog_system.c
 *
 *  \brief This file contains implementation of functional system test cases
 *         for the WATCHDOG driver across multiple cores.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <drivers/watchdog.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/DebugP.h>
#include "test_watchdog.h"

/* ========================================================================== */
/*                               Macros                                       */
/* ========================================================================== */

/** \brief Wait timeout helper: expiration ms to usec + margin */
#define TEST_WDT_SYS_WAIT_US(exp_ms) ((uint64_t)(exp_ms) * 1000ULL + 200000ULL)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void TestWatchdog_systemIsr(void *arg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile uint32_t TestWatchdog_SysIsrFlag = 0U;
extern Watchdog_Handle gWatchdogHandle[];

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/**
 * \brief Minimal Watchdog ISR: sets the flag when an NMI fires.
 */
static void TestWatchdog_systemIsr(void *arg)
{
    (void)arg;
    TestWatchdog_SysIsrFlag = 1U;
}

/* ========================================================================== */
/*                          Test Case Definitions                             */
/* ========================================================================== */

/**
 * \brief  Watchdog timeout triggers interrupt when not serviced.
 *
 *         Registers an NMI/ISR on the watchdog instance, clears the watchdog
 *         to start a fresh countdown and then *deliberately does not service*
 *         it. The test passes when the ISR fires within the configured
 *         expiration period + margin.
 *
 * \param  args  Unused.
 * \return SystemP_SUCCESS on pass, SystemP_FAILURE on fail.
 */
int32_t TestWatchdog_systemTimeoutDetection(void *args)
{
    int32_t     status;
    HwiP_Params hwiPrms;
    HwiP_Object hwiObject;
    uint64_t    timeStart;

    (void)args;

    /* Register ISR for watchdog NMI */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_WDT0_INTR;
    hwiPrms.eventId  = CONFIG_WDT0_EVENT_ID;
    hwiPrms.callback = &TestWatchdog_systemIsr;
    hwiPrms.isPulse  = 1U;

    TestWatchdog_SysIsrFlag = 0U;
    status = HwiP_construct(&hwiObject, &hwiPrms);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: HwiP_construct failed\r\n");
        status = SystemP_FAILURE;
    }

    /* Clear watchdog to start a fresh countdown period */
    Watchdog_clear(gWatchdogHandle[CONFIG_WDT0]);

    /* Wait for timeout — deliberately do NOT service the watchdog */
    timeStart = ClockP_getTimeUsec();
    while ((TestWatchdog_SysIsrFlag == 0U) &&
           ((ClockP_getTimeUsec() - timeStart) < TEST_WDT_SYS_WAIT_US(5000U)))
    {
        /* Poll */
    }

    HwiP_destruct(&hwiObject);

    if (TestWatchdog_SysIsrFlag != 1U)
    {
        DebugP_log("FAIL: Watchdog timeout ISR was not triggered\r\n");
        status = SystemP_FAILURE;
    }

    return status;
}




/*
 * Copyright (C) 2026 Texas Instruments Incorporated
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

/**
 *  \file test_watchdog_reset.c
 *
 *  \brief Watchdog reset mode test — This test validates watchdog reset
 *         functionality using a two-phase approach with flash-based marker.
 *
 *  Phase 1 (First Boot):
 *    - Writes magic marker to flash
 *    - Opens watchdog with Watchdog_RESET_ON
 *    - Lets the watchdog expire → system resets
 *
 *  Phase 2 (After Reset):
 *    - Reads magic marker from flash
 *    - Reads reset cause register, verifies WDT triggered reset
 *    - Erases marker from flash
 *    - Reports PASS
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <drivers/watchdog.h>
#include <drivers/soc.h>
#include <drivers/hw_include/cslr_soc.h>
#if defined(SOC_AM62DX)
#include <drivers/hw_include/am62dx/cslr_wkup_ctrl_mmr.h>
#elif defined(SOC_AM62AX)
#include <drivers/hw_include/am62ax/cslr_wkup_ctrl_mmr.h>
#endif
#include <board/flash.h>
#include <unity.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                                  Macros                                    */
/* ========================================================================== */

/** Magic value written to flash before triggering WDT reset */
#define TEST_WDT_RESET_MAGIC_MARKER          (0xDEAD1234U)

/** Watchdog expiration time in milliseconds */
#define TEST_WDT_RESET_EXPIRATION_MS         (1000U)

/** Convert ms to us */
#define TEST_WDT_WAIT_US(exp_ms)             ((uint64_t)(exp_ms) * 1000ULL)

/**
 * Expected reset cause bits (value 0x00402000):
 * - DM_WDT_RST  (bit 22) = 0x00400000
 * - WARM_OUT_RST (bit 13) = 0x00002000
 */
#define TEST_WDT_RESET_CAUSE_MASK            (0x00402000U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * Flash offset for the marker is computed at runtime to avoid the last block
 * which is RESERVED for OSPI PHY tuning (Flash_getPhyTuningOffset = flashSize - blockSize).
 * We use flashSize - 2*blockSize (the second-to-last block).
 */
static uint32_t TestWatchdog_FlashMarkerOffset = 0U;

/* ========================================================================== */
/*                      Function Declarations                                 */
/* ========================================================================== */

static void TestWatchdog_resetTimeout(void *args);
static void TestWatchdog_verifyResetCause(void *args);
static void TestWatchdog_initMarkerOffset(void);
static int32_t TestWatchdog_writeMarkerToFlash(uint32_t marker);
static uint32_t TestWatchdog_readMarkerFromFlash(void);
static void TestWatchdog_eraseMarkerFromFlash(void);

/* ========================================================================== */
/*                           Function Definitions                             */    
/* ========================================================================== */

/* Flash Marker Helpers */
/**
 * \brief Compute the safe flash marker offset .
 */
static void TestWatchdog_initMarkerOffset(void)
{
    Flash_Attrs *attrs = Flash_getAttrs(CONFIG_FLASH0);
    if (attrs != NULL)
    {
        /* Use second-to-last block: stay clear of PHY tuning area */
        TestWatchdog_FlashMarkerOffset = attrs->flashSize - (2U * attrs->blockSize);
    }
    else
    {
        DebugP_assert(0);
        return;
    }
    DebugP_log("Marker flash offset = 0x%08X (phyTuning @ 0x%08X)\r\n",
               TestWatchdog_FlashMarkerOffset,
               Flash_getPhyTuningOffset(gFlashHandle[CONFIG_FLASH0]));
}

static int32_t TestWatchdog_writeMarkerToFlash(uint32_t marker)
{
    int32_t  status;
    uint32_t blk, page;
    uint8_t  buf[4];

    buf[0] = (uint8_t)(marker & 0xFFU);
    buf[1] = (uint8_t)((marker >> 8U) & 0xFFU);
    buf[2] = (uint8_t)((marker >> 16U) & 0xFFU);
    buf[3] = (uint8_t)((marker >> 24U) & 0xFFU);

    /* Get block number for the offset */
    status = Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0],
                                   TestWatchdog_FlashMarkerOffset, &blk, &page);
    if (status != SystemP_SUCCESS)
    {
        return status;
    }

    /* Erase block before writing */
    status = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    if (status != SystemP_SUCCESS)
    {
        return status;
    }

    /* Write marker */
    status = Flash_write(gFlashHandle[CONFIG_FLASH0],
                         TestWatchdog_FlashMarkerOffset, buf, 4U);
    return status;
}

/**
 * \brief Read magic marker from flash at TEST_WDT_FLASH_MARKER_OFFSET.
 *
 * \return The 32-bit marker value read from flash.
 */
static uint32_t TestWatchdog_readMarkerFromFlash(void)
{
    uint8_t  buf[4] = {0U};
    uint32_t marker;

    (void)Flash_read(gFlashHandle[CONFIG_FLASH0],
                     TestWatchdog_FlashMarkerOffset, buf, 4U);

    marker = ((uint32_t)buf[0])        |
             ((uint32_t)buf[1] << 8U)  |
             ((uint32_t)buf[2] << 16U) |
             ((uint32_t)buf[3] << 24U);

    return marker;
}

/**
 * \brief Erase the flash marker (erase the block containing the marker).
 */
static void TestWatchdog_eraseMarkerFromFlash(void)
{
    uint32_t blk, page;

    if (Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0],
                              TestWatchdog_FlashMarkerOffset,
                              &blk, &page) == SystemP_SUCCESS)
    {
        (void)Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    }
}

/* ========================================================================== */
/*                    Unity Framework Setup Functions                         */
/* ========================================================================== */

void setUp(void)
{
    /* Do nothing */
}

void tearDown(void)
{
    /* Do nothing */
}

void test_watchdog_reset_main(void *args)
{
    UNITY_BEGIN();

    /* Compute safe flash offset (must be done after flash is open) */
    TestWatchdog_initMarkerOffset();

    if (TestWatchdog_readMarkerFromFlash() == TEST_WDT_RESET_MAGIC_MARKER)
    {
        /*
         * Phase 2: We are here after a watchdog-triggered reset.
         */
        RUN_TEST(TestWatchdog_verifyResetCause, 12124, NULL);
    }
    else
    {
        /*
         * Phase 1: First boot — trigger a watchdog reset.
         */
        RUN_TEST(TestWatchdog_resetTimeout, 12123, NULL);
    }

    UNITY_END();
}

/* ========================================================================== */
/*                          Test Case Definitions                             */
/* ========================================================================== */

/**
 * \brief Phase 2: Verify that the reset was caused by the watchdog.
 */
static void TestWatchdog_verifyResetCause(void *args)
{
    (void)args;

    /* Erase the marker from flash to prevent false positives */
    TestWatchdog_eraseMarkerFromFlash();

    /* Validate that the reset cause register shows a WDT reset */
    uint32_t resetCause = SOC_getWarmResetCauseMainDomain();
    DebugP_log("Phase 2: Reset cause register = 0x%08X\r\n", resetCause);

    TEST_ASSERT_NOT_EQUAL_UINT32_MESSAGE(
        0U,
        (resetCause & TEST_WDT_RESET_CAUSE_MASK),
        "Reset cause does not indicate watchdog reset");
}

/**
 * \brief Phase 1: Configure watchdog in reset mode, write magic marker,
 *        and let the watchdog expire to trigger a system reset.
 *
 * \param args Pointer to test arguments (unused).
 *
 * If successful, this function does NOT return — the board resets.
 * If the board fails to reset, the test fails with an assertion.
 */
static void TestWatchdog_resetTimeout(void *args)
{
    (void)args;
    Watchdog_Handle wdtHandle;
    Watchdog_Params params;
    uint32_t        staleCause;
    uint64_t        timeStart;
    int32_t         status;

    /* Clear any stale reset cause from previous runs */
    staleCause = SOC_getWarmResetCauseMainDomain();
    if (staleCause != 0U)
    {
        SOC_clearResetCauseMainMcuDomain(staleCause);
        DebugP_log("Cleared stale reset cause: 0x%08X\r\n", staleCause);
    }

    /* Close the instance opened by SysConfig/Drivers_open before re-opening */
    Watchdog_close(gWatchdogHandle[CONFIG_WDT0]);

    /* Configure watchdog in reset mode. */
    Watchdog_paramsInit(&params);
    params.resetMode      = Watchdog_RESET_ON;
    params.windowSize     = Watchdog_WINDOW_100_PERCENT;
    params.expirationTime = TEST_WDT_RESET_EXPIRATION_MS;

    wdtHandle = Watchdog_open(CONFIG_WDT0, &params);
    TEST_ASSERT_NOT_NULL(wdtHandle);

    /* Write magic marker to flash BEFORE starting WDT countdown */
    status = TestWatchdog_writeMarkerToFlash(TEST_WDT_RESET_MAGIC_MARKER);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status,
                                    "Failed to write marker to flash");

    /* Start the watchdog countdown */
    Watchdog_clear(wdtHandle);
    timeStart = ClockP_getTimeUsec();

    DebugP_log("Phase 1: Watchdog started in reset mode, expiration = %u ms\r\n",
               params.expirationTime);
    DebugP_log("         Waiting for watchdog to expire and reset the board...\r\n");

    /* Do NOT service the watchdog. Wait for board reset.
     * If we exit this loop, the reset did not happen. */
    while ((ClockP_getTimeUsec() - timeStart) <
           (TEST_WDT_WAIT_US(params.expirationTime) + 500000U))
    {
        ClockP_usleep(10000U);
    }

    /* If execution reaches here, the watchdog did NOT reset the board. */
    TEST_FAIL_MESSAGE("Board did not reset within expected watchdog timeout");
}
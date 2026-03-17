/*
 *  Copyright (C) 2025-2026 Texas Instruments Incorporated
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
 *  \file test_optiflash_system.c
 *
 *  \brief Functional test cases for OptiFlash (FLC + RL2) system tests
 *         across multiple R5F cores. */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <unity.h>
#include <drivers/optiflash.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/CacheP.h>
#include "system_test_utils.h"
#include "test_optiflash_system.h"

/* ========================================================================== */
/*                               Macros                                       */
/* ========================================================================== */

/** \brief Transfer buffer size used by data-integrity tests (4 KB) */
#define TEST_OPTIFLASH_XFER_SIZE          (4U * 1024U)

/** \brief Maximum poll iterations before declaring a timeout */
#define TEST_OPTIFLASH_MAX_POLL_ATTEMPTS  (1000000U)

/** \brief Maximum poll iterations with 1 ms sleep (~200 ms timeout) */
#define TEST_OPTIFLASH_MAX_POLL_MS        (200U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void     TestOptiflash_resetFlcRegion(FLC_RegionInfo *region);
static uint32_t TestOptiflash_getRl2IrqNum(uint32_t rl2Base);
static void     TestOptiflash_flcDoneIsr(void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * Source buffer residing in external flash (.flashSrcBuffer section).
 */
uint8_t TestOptiflash_SrcBuf[TEST_OPTIFLASH_XFER_SIZE]
    __attribute__((aligned(4096), section(".flashSrcBuffer")));

/** Destination buffer in SRAM for FLC copy verification */
static uint8_t TestOptiflash_DstBuf[TEST_OPTIFLASH_XFER_SIZE]
    __attribute__((aligned(4096)));

/** Binary semaphore posted by the FLC-DONE ISR */
static SemaphoreP_Object TestOptiflash_FlcDoneSem;

/** RAW IRQ status captured inside the FLC-DONE ISR */
static volatile uint32_t TestOptiflash_FlcIsrRawStatus;

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/**
 * \brief Reset a single FLC region: disable and clear all errors/interrupts.
 *
 * Test Category: Helper
 *
 * Disables the FLC region but also clears DONE, write-error, and read-error
 * interrupt flags so the region starts from a clean state.
 *
 * \param region  Pointer to the FLC region configuration to reset.
 */
static void TestOptiflash_resetFlcRegion(FLC_RegionInfo *region)
{
    FLC_disable(region);
    FLC_clearInterrupt(region, FLC_INTERRUPT_DONE);
    FLC_clearInterrupt(region, FLC_INTERRUPT_WRITE_ERROR);
    FLC_clearInterrupt(region, FLC_INTERRUPT_READ_ERROR);
    FLC_clearReadError(region);
    FLC_clearWriteError(region);
}

/**
 * \brief Map RL2 instance base address to the correct R5 IRQ number.
 *
 * Test Category: Helper
 *
 * IRQ numbers for RL2_OF_CBA4_[0..3]_ERR_LVL_0 are 89..92.
 * Returns the matching IRQ number, or 89 as a fallback.
 *
 * \param rl2Base  Base address of the RL2 instance.
 * \return IRQ number corresponding to the given RL2 base address.
 */
static uint32_t TestOptiflash_getRl2IrqNum(uint32_t rl2Base)
{
    if(rl2Base == CSL_RL2_OF_CBA4_0_RL2_OF_CBA4_BASE) return 89U;
    if(rl2Base == CSL_RL2_OF_CBA4_1_RL2_OF_CBA4_BASE) return 90U;
    if(rl2Base == CSL_RL2_OF_CBA4_2_RL2_OF_CBA4_BASE) return 91U;
    if(rl2Base == CSL_RL2_OF_CBA4_3_RL2_OF_CBA4_BASE) return 92U;
    return 89U; /* fallback */
}

/**
 * \brief ISR callback for the FLC DONE interrupt.
 *
 * Test Category: Helper
 *
 * Captures the RAW IRQ status register, clears the DONE interrupt flag,
 * disables the DONE interrupt source, and posts the binary semaphore so
 * that the blocked test thread can continue.
 *
 * \param args  Pointer to FLC_RegionInfo for the region that triggered the interrupt.
 */
static void TestOptiflash_flcDoneIsr(void *args)
{
    FLC_RegionInfo *region = (FLC_RegionInfo *)args;
    uint32_t raw = 0U;

    if(region == NULL)
    {
        region = &gFLCRegionConfig[0];
    }

    FLC_readIRQStatus(region, &raw);
    TestOptiflash_FlcIsrRawStatus = raw;

    FLC_clearInterrupt(region, FLC_INTERRUPT_DONE);
    FLC_disableInterrupt(region, FLC_INTERRUPT_DONE);

    SemaphoreP_post(&TestOptiflash_FlcDoneSem);
}

/* ========================================================================== */
/*                          Test Case Definitions                             */
/* ========================================================================== */

/**
 * \brief FLC Data Transfer and Data Integrity.
 *
 * Test Category: Functional
 *
 * Configures FLC region 0 to copy from flash source buffer to SRAM
 * destination, starts the transfer, polls for completion, then performs
 * a byte-by-byte data integrity check.
 *
 * \param args  Pointer to test arguments (unused).
 * \return SystemP_SUCCESS if the transfer completes and data matches, SystemP_FAILURE otherwise.
 * \expectedOutput FLC transfer completes within timeout and source/destination data match.
 */
int32_t TestOptiflash_flcDataTransfer(void *args)
{
    int32_t testStatus = SystemP_SUCCESS;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    FLC_RegionInfo savedConfig = gFLCRegionConfig[0];
    uint32_t cpyStatus = 0U;
    uint32_t attempts  = 0U;
    const uint32_t doneMask = (1U << region->regionId);
    uint32_t readErr = 0U, writeErr = 0U;

    /* Clean state */
    TestOptiflash_resetFlcRegion(region);

    /* Prepare destination with zeroes and flush cache */
    memset(TestOptiflash_DstBuf, 0, TEST_OPTIFLASH_XFER_SIZE);
    CacheP_wbInv(TestOptiflash_DstBuf, TEST_OPTIFLASH_XFER_SIZE, CacheP_TYPE_ALL);

    /* Configure FLC: copy TestOptiflash_SrcBuf (flash) -> TestOptiflash_DstBuf (SRAM) */
    region->sourceStartAddress      = (uint32_t)TestOptiflash_SrcBuf;
    region->sourceEndAddress        = (uint32_t)TestOptiflash_SrcBuf + TEST_OPTIFLASH_XFER_SIZE;
    region->destinationStartAddress = (uint32_t)TestOptiflash_DstBuf;

    if(FLC_API_STS_SUCCESS != FLC_configureRegion(region))
    {
        DebugP_log("Core[%d]: FLC configure failed\r\n",
                    IpcNotify_getSelfCoreId());
        testStatus = SystemP_FAILURE;
    }

    /* Start the transfer */
    if(SystemP_SUCCESS == testStatus &&
       FLC_API_STS_SUCCESS != FLC_startRegion(region))
    {
        DebugP_log("Core[%d]: FLC start failed\r\n",
                    IpcNotify_getSelfCoreId());
        testStatus = SystemP_FAILURE;
    }

    /* Poll for DONE */
    if(SystemP_SUCCESS == testStatus)
    {
        do {
            FLC_isRegionDone(region, &cpyStatus);
            attempts++;

            /* Check for read/write errors */
            FLC_wasReadError(region, &readErr);
            FLC_wasWriteError(region, &writeErr);
            if(readErr != 0U)
            {
                DebugP_log("Core[%d]: FLC read error detected\r\n",
                            IpcNotify_getSelfCoreId());
                testStatus = SystemP_FAILURE;
                break;
            }
            if(writeErr != 0U)
            {
                DebugP_log("Core[%d]: FLC write error detected\r\n",
                            IpcNotify_getSelfCoreId());
                testStatus = SystemP_FAILURE;
                break;
            }

            if(attempts > TEST_OPTIFLASH_MAX_POLL_ATTEMPTS)
            {
                DebugP_log("Core[%d]: FLC transfer timeout\r\n",
                            IpcNotify_getSelfCoreId());
                testStatus = SystemP_FAILURE;
                break;
            }
        } while((cpyStatus & doneMask) == 0U);
    }

    /* Invalidate CPU cache for destination and compare with source */
    if(SystemP_SUCCESS == testStatus)
    {
        CacheP_inv(TestOptiflash_DstBuf, TEST_OPTIFLASH_XFER_SIZE, CacheP_TYPE_ALL);
        if(0 != memcmp(TestOptiflash_SrcBuf, TestOptiflash_DstBuf, TEST_OPTIFLASH_XFER_SIZE))
        {
            DebugP_log("Core[%d]: FLC data mismatch after transfer\r\n",
                        IpcNotify_getSelfCoreId());
            testStatus = SystemP_FAILURE;
        }
    }

    /* Restore original FLC config */
    gFLCRegionConfig[0] = savedConfig;
    FLC_configureRegion(&gFLCRegionConfig[0]);

    return testStatus;
}

/**
 * \brief FLC Interrupt-Driven Transfer with Data Verification.
 *
 * Test Category: Functional
 *
 * Registers an HWI for the RL2 DONE interrupt, enables the interrupt,
 * starts a flash-to-SRAM transfer, waits on a semaphore (posted by ISR),
 * and verifies data integrity after the ISR signals completion.
 *
 * \param args  Pointer to test arguments (unused).
 * \return SystemP_SUCCESS if ISR fires, data matches, SystemP_FAILURE otherwise.
 * \expectedOutput FLC DONE ISR fires, semaphore is posted, and transferred data matches source.
 */
int32_t TestOptiflash_flcInterruptTransfer(void *args)
{
    int32_t testStatus = SystemP_SUCCESS;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    FLC_RegionInfo savedConfig = gFLCRegionConfig[0];
    HwiP_Params hwiPrms;
    HwiP_Object hwiObj;
    int32_t semStatus;

    /* Clean state and prepare semaphore */
    TestOptiflash_resetFlcRegion(region);
    TestOptiflash_FlcIsrRawStatus = 0U;
    SemaphoreP_constructBinary(&TestOptiflash_FlcDoneSem, 0U);

    /* Register HWI for the RL2 instance used by this core */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = TestOptiflash_getRl2IrqNum(region->baseAddress);
    hwiPrms.callback = &TestOptiflash_flcDoneIsr;
    hwiPrms.args     = (void *)region;
    hwiPrms.isPulse  = (uint8_t)0U;
    hwiPrms.priority = 4U;
    hwiPrms.isFIQ    = (uint8_t)0U;
    HwiP_construct(&hwiObj, &hwiPrms);

    /* Enable DONE interrupt */
    if(FLC_API_STS_SUCCESS != FLC_enableInterrupt(region, FLC_INTERRUPT_DONE))
    {
        DebugP_log("Core[%d]: FLC enable DONE interrupt failed\r\n",
                    IpcNotify_getSelfCoreId());
        testStatus = SystemP_FAILURE;
    }

    /* Prepare destination and configure FLC */
    if(SystemP_SUCCESS == testStatus)
    {
        memset(TestOptiflash_DstBuf, 0, TEST_OPTIFLASH_XFER_SIZE);
        CacheP_wbInv(TestOptiflash_DstBuf, TEST_OPTIFLASH_XFER_SIZE, CacheP_TYPE_ALL);

        region->sourceStartAddress      = (uint32_t)TestOptiflash_SrcBuf;
        region->sourceEndAddress        = (uint32_t)TestOptiflash_SrcBuf + TEST_OPTIFLASH_XFER_SIZE;
        region->destinationStartAddress = (uint32_t)TestOptiflash_DstBuf;

        if(FLC_API_STS_SUCCESS != FLC_configureRegion(region))
        {
            testStatus = SystemP_FAILURE;
        }
    }

    /* Start transfer */
    if(SystemP_SUCCESS == testStatus &&
       FLC_API_STS_SUCCESS != FLC_startRegion(region))
    {
        testStatus = SystemP_FAILURE;
    }

    /* Wait for ISR to signal completion (5 s timeout) */
    if(SystemP_SUCCESS == testStatus)
    {
        semStatus = SemaphoreP_pend(&TestOptiflash_FlcDoneSem, 5000U);
        if(semStatus != SystemP_SUCCESS)
        {
            DebugP_log("Core[%d]: FLC DONE ISR timeout\r\n",
                        IpcNotify_getSelfCoreId());
            testStatus = SystemP_FAILURE;
        }
    }

    /* Verify the ISR captured the DONE bit in RAW status */
    if(SystemP_SUCCESS == testStatus &&
       (TestOptiflash_FlcIsrRawStatus & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MASK) == 0U)
    {
        DebugP_log("Core[%d]: ISR did not capture DONE in RAW status\r\n",
                    IpcNotify_getSelfCoreId());
        testStatus = SystemP_FAILURE;
    }

    /* Data integrity check */
    if(SystemP_SUCCESS == testStatus)
    {
        CacheP_inv(TestOptiflash_DstBuf, TEST_OPTIFLASH_XFER_SIZE, CacheP_TYPE_ALL);
        if(0 != memcmp(TestOptiflash_SrcBuf, TestOptiflash_DstBuf, TEST_OPTIFLASH_XFER_SIZE))
        {
            DebugP_log("Core[%d]: Data mismatch after interrupt-driven transfer\r\n",
                        IpcNotify_getSelfCoreId());
            testStatus = SystemP_FAILURE;
        }
    }

    /* Clean up */
    HwiP_destruct(&hwiObj);
    SemaphoreP_destruct(&TestOptiflash_FlcDoneSem);

    /* Restore original FLC config */
    gFLCRegionConfig[0] = savedConfig;
    FLC_configureRegion(&gFLCRegionConfig[0]);

    return testStatus;
}

/**
 * \brief FLC Transfer with RL2 Cache Enabled (Integration).
 *
 * Test Category: Functional
 *
 * Configures and enables RL2 cache, performs an FLC copy from flash to
 * SRAM, invalidates CPU caches for the destination, and verifies data
 * integrity with the RL2 cache active throughout.
 *
 * \param args  Pointer to test arguments (unused).
 * \return SystemP_SUCCESS if RL2+FLC transfer succeeds and data matches, SystemP_FAILURE otherwise.
 * \expectedOutput FLC transfer with RL2 cache enabled completes and data integrity is maintained.
 */
int32_t TestOptiflash_flcRl2Integration(void *args)
{
    int32_t testStatus = SystemP_SUCCESS;
    RL2_Params rl2Cfg;
    RL2_API_STS_t rl2Sts;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    FLC_RegionInfo savedConfig = gFLCRegionConfig[0];
    uint32_t cpyStatus = 0U;
    uint32_t attempts  = 0U;
    const uint32_t doneMask = (1U << region->regionId);
    uint32_t irqMask = 0U;
    uint32_t readErr = 0U, writeErr = 0U;
    
    /* Configure and enable RL2 cache */
    rl2Sts = RL2_initparams(&rl2Cfg);
    if(rl2Sts != RL2_API_STS_SUCCESS)
    {
        testStatus = SystemP_FAILURE;
    }
    else
    {
        rl2Cfg.baseAddress = gRL2Config[0].baseAddress;
        rl2Cfg.rangeStart  = gRL2Config[0].rangeStart;
        rl2Cfg.rangeEnd    = gRL2Config[0].rangeEnd;
        rl2Cfg.cacheSize   = gRL2Config[0].cacheSize;
        rl2Cfg.l2Sram0Base = gRL2Config[0].l2Sram0Base;
        rl2Cfg.l2Sram0Len  = gRL2Config[0].l2Sram0Len;
    }

    if(SystemP_SUCCESS == testStatus)
    {
        rl2Sts = RL2_configure(&rl2Cfg);
        if(rl2Sts != RL2_API_STS_SUCCESS)
        {
            DebugP_log("Core[%d]: RL2_configure failed\r\n",
                        IpcNotify_getSelfCoreId());
            testStatus = SystemP_FAILURE;
        }
    }

    if(SystemP_SUCCESS == testStatus)
    {
        rl2Sts = RL2_enable(&rl2Cfg);
        if(rl2Sts != RL2_API_STS_SUCCESS)
        {
            DebugP_log("Core[%d]: RL2_enable failed\r\n",
                        IpcNotify_getSelfCoreId());
            testStatus = SystemP_FAILURE;
        }
    }

    /* Prepare FLC transfer */
    if(SystemP_SUCCESS == testStatus)
    {
        TestOptiflash_resetFlcRegion(region);

        memset(TestOptiflash_DstBuf, 0, TEST_OPTIFLASH_XFER_SIZE);
        CacheP_wbInv(TestOptiflash_DstBuf, TEST_OPTIFLASH_XFER_SIZE, CacheP_TYPE_ALL);

        region->sourceStartAddress      = (uint32_t)TestOptiflash_SrcBuf;
        region->sourceEndAddress        = (uint32_t)TestOptiflash_SrcBuf + TEST_OPTIFLASH_XFER_SIZE;
        region->destinationStartAddress = (uint32_t)TestOptiflash_DstBuf;

        if(FLC_API_STS_SUCCESS != FLC_configureRegion(region))
        {
            DebugP_log("Core[%d]: FLC configure failed (integration)\r\n",
                        IpcNotify_getSelfCoreId());
            testStatus = SystemP_FAILURE;
        }
    }

    /* Start transfer and wait */
    if(SystemP_SUCCESS == testStatus)
    {
        if(FLC_API_STS_SUCCESS != FLC_startRegion(region))
        {
            testStatus = SystemP_FAILURE;
        }
    }

    if(SystemP_SUCCESS == testStatus)
    {
        do {
            FLC_isRegionDone(region, &cpyStatus);

            /* Check for read/write errors */
            FLC_wasReadError(region, &readErr);
            FLC_wasWriteError(region, &writeErr);
            if(readErr != 0U)
            {
                DebugP_log("Core[%d]: FLC read error detected (integration)\r\n",
                            IpcNotify_getSelfCoreId());
                testStatus = SystemP_FAILURE;
                break;
            }
            if(writeErr != 0U)
            {
                DebugP_log("Core[%d]: FLC write error detected (integration)\r\n",
                            IpcNotify_getSelfCoreId());
                testStatus = SystemP_FAILURE;
                break;
            }

            if((cpyStatus & doneMask) == 0U)
            {
                ClockP_usleep(1000U);
                attempts++;
            }
        } while(((cpyStatus & doneMask) == 0U) && (attempts < TEST_OPTIFLASH_MAX_POLL_MS));

        if((cpyStatus & doneMask) == 0U)
        {
            DebugP_log("Core[%d]: FLC timeout (integration)\r\n",
                        IpcNotify_getSelfCoreId());
            testStatus = SystemP_FAILURE;
        }
    }

    /* Invalidate CPU cache and verify data integrity */
    if(SystemP_SUCCESS == testStatus)
    {
        CacheP_inv(TestOptiflash_DstBuf, TEST_OPTIFLASH_XFER_SIZE, CacheP_TYPE_ALL);
        if(0 != memcmp(TestOptiflash_SrcBuf, TestOptiflash_DstBuf, TEST_OPTIFLASH_XFER_SIZE))
        {
            DebugP_log("Core[%d]: Data mismatch (integration with RL2 enabled)\r\n",
                        IpcNotify_getSelfCoreId());
            testStatus = SystemP_FAILURE;
        }
    }

    /* Sanity: verify RL2 IRQ mask is still readable */
    if(SystemP_SUCCESS == testStatus)
    {
        rl2Sts = RL2_readIRQMask(&rl2Cfg, &irqMask);
        if(rl2Sts != RL2_API_STS_SUCCESS)
        {
            DebugP_log("Core[%d]: RL2_readIRQMask failed (integration)\r\n",
                        IpcNotify_getSelfCoreId());
            testStatus = SystemP_FAILURE;
        }
    }

    /* Clean up: disable RL2, restore FLC config */
    RL2_disable(&rl2Cfg);
    gFLCRegionConfig[0] = savedConfig;
    FLC_configureRegion(&gFLCRegionConfig[0]);

    return testStatus;
}

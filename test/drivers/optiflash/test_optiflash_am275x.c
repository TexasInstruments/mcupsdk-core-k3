/*
 * Copyright (C) 2025 - 2026 Texas Instruments Incorporated
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
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/optiflash.h>
#include <drivers/ospi.h>
#include <drivers/hw_include/am275x/cslr_soc_baseaddress.h>
#include "test_optiflash.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_OPTIFLASH_FLC_SRC_START_ADDR           (0x60000000U)
#define TEST_OPTIFLASH_DST_START_ADDR               (0x72080000U)
#define TEST_OPTIFLASH_FLC_REGION_SIZE              (0x00100000U)  /* 1 MB */
#define TEST_OPTIFLASH_FLC_DST_STRIDE               (0x00040000U)  /* 256 KB */
#define TEST_OPTIFLASH_FLC_NUM_REGIONS              (4U)

/* Unmapped destination address to trigger FLC write error in negative tests */
#define TEST_OPTIFLASH_UNMAPPED_DST_ADDR            (0x74000000U)

/* Small transfer size for error-injection tests (bytes) */
#define TEST_OPTIFLASH_ERROR_XFER_SIZE              (256U)

/* FLC / RL2 cache-line granularity (bytes) */
#define TEST_OPTIFLASH_CACHE_LINE_BYTES             (64U)

/* Destination buffer fill patterns */
#define TEST_OPTIFLASH_FILL_PATTERN_AA              (0xAAU)
#define TEST_OPTIFLASH_FILL_PATTERN_CD              (0xCDU)

/* Known data patterns for RL2 write-hit trigger and verification */
#define TEST_OPTIFLASH_RL2_REGION_FILL_PATTERN      (0xA5A5A5A5U)

#define TEST_OPTIFLASH_FLC_INVALID_SRC_ADDR         (0x74000000U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */


/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Callback Functions */
void test_optiflash_Callback(void);

static void test_optiflash_hwiFxn(void *args);
static uint32_t TestOptiflash_getRl2IrqNum(uint32_t rl2Base);
static void TestOptiflash_resetFlc(FLC_RegionInfo *region);
static void TestOptiflash_flcDoneIsr(void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static SemaphoreP_Object gSemObj;
static volatile uint32_t TestOptiflash_LastMaskedStatus;

/* ========================================================================== */
/*                         Internal Function Definitions                              */
/* ========================================================================== */

/* Map RL2 instance base address to the correct R5 IRQ number.
 * IRQ numbers for RL2_OF_CBA4_[0..3]_ERR_LVL_0 are 89..92 on all R5 cores. */
static uint32_t TestOptiflash_getRl2IrqNum(uint32_t rl2Base)
{
    if(rl2Base == CSL_RL2_OF_CBA4_0_RL2_OF_CBA4_BASE)
        return 89U; /* RL2_OF_CBA4_0 */
    if(rl2Base == CSL_RL2_OF_CBA4_1_RL2_OF_CBA4_BASE)
        return 90U; /* RL2_OF_CBA4_1 */
    if(rl2Base == CSL_RL2_OF_CBA4_2_RL2_OF_CBA4_BASE)
        return 91U; /* RL2_OF_CBA4_2 */
    if(rl2Base == CSL_RL2_OF_CBA4_3_RL2_OF_CBA4_BASE)
        return 92U; /* RL2_OF_CBA4_3 */
    /* Default to instance 0 if unknown */
    return 89U;
}

/* Bring FLC region to a known clean state: disable + clear errors/interrupts */
static void TestOptiflash_resetFlc(FLC_RegionInfo *region)
{
    FLC_disable(region);
    FLC_clearInterrupt(region, FLC_INTERRUPT_DONE);
    /* Best-effort clear both error latches */
    FLC_clearReadError(region);
    FLC_clearWriteError(region);
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Test cases
 */
void* test_flc_configuration(void* args)
{
    int32_t retval = SystemP_SUCCESS;
    CSL_rl2_of_cba4Regs * rl2_of_reg;
    rl2_of_reg = (CSL_rl2_of_cba4Regs *)gFLCRegionConfig[0].baseAddress;
    /*flc should be already configured by syscfg and not be configured else where in the program*/

    if(SystemP_SUCCESS == retval && (volatile uint32_t)0x60000000 != rl2_of_reg->FLC[0].LO )
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && rl2_of_reg->FLC[0].HI != (volatile uint32_t)(0x60100000))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && rl2_of_reg->FLC[0].RA != (volatile uint32_t)(0x72080000))
    {
        retval = SystemP_FAILURE;
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);

    return NULL;
}

void *test_flc_runtimeconfig(void *args)
{
    int32_t retval = SystemP_SUCCESS;
    CSL_rl2_of_cba4Regs * rl2_of_reg;
    rl2_of_reg = (CSL_rl2_of_cba4Regs *)gFLCRegionConfig[0].baseAddress;
    
    gFLCRegionConfig[0].sourceStartAddress = (uint32_t)sourceBuffer;
    gFLCRegionConfig[0].destinationStartAddress = (uint32_t)destBuffer;
    gFLCRegionConfig[0].sourceEndAddress = (uint32_t)sourceBuffer + TRANSFERSIZE;
    FLC_configureRegion(&gFLCRegionConfig[0]);
    FLC_startRegion(&gFLCRegionConfig[0]);
    {
        uint32_t cpy_status = 0;
        do
        {
            FLC_isRegionDone(&gFLCRegionConfig[FLC_REGION_FLC0], &cpy_status);
        } while ((cpy_status & (1<<FLC_REGION_FLC0)) == 0);
    }
    /* check if all the required configurations has been written to the correct configurations */
    if(SystemP_SUCCESS == retval && rl2_of_reg->FLC[0].LO != (volatile uint32_t)sourceBuffer)
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && rl2_of_reg->FLC[0].HI != (volatile uint32_t)((uint32_t)sourceBuffer + TRANSFERSIZE))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && rl2_of_reg->FLC[0].RA != (volatile uint32_t)(destBuffer))
    {
        retval = SystemP_FAILURE;
    }

    for(uint32_t  i = 0 ; i < TRANSFERSIZE; i++)
    {
        if(SystemP_SUCCESS == retval  && sourceBuffer[i] != destBuffer[i])
        {
            retval = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);

    return NULL;
}

void* test_flc_interrupt(void* args)
{
    int32_t retval = SystemP_SUCCESS;
    CSL_rl2_of_cba4Regs * rl2_of_reg;
    rl2_of_reg = (CSL_rl2_of_cba4Regs *)gFLCRegionConfig[0].baseAddress;
    
    HwiP_Params hwiPrms;
    HwiP_Object hwiobj;
    
    /* Initialize with defaults */
    HwiP_Params_init(&hwiPrms);
    /* Populate the interrupt parameters */
    /* Select the RL2 IRQ for the current core/instance based on base address */
    hwiPrms.intNum = TestOptiflash_getRl2IrqNum(gFLCRegionConfig[0].baseAddress);
    hwiPrms.args=(void*)args;
    hwiPrms.callback = &test_optiflash_hwiFxn;
    hwiPrms.isPulse = (uint8_t)0U;
    hwiPrms.priority = 4U;
    hwiPrms.isFIQ = (uint8_t)0U;
    /* Register interrupts */
    HwiP_construct(&hwiobj,&hwiPrms);

    FLC_disableInterrupt(&gFLCRegionConfig[0], FLC_INTERRUPT_DONE);
    FLC_clearInterrupt(&gFLCRegionConfig[0], FLC_INTERRUPT_DONE);
    if(SystemP_FAILURE == retval && rl2_of_reg->IRQSTATUS_RAW != 0)
    {
        retval = SystemP_FAILURE;
    }
    /* FLC done interrupt */

    SemaphoreP_constructBinary(&gSemObj, 0U);
    
    FLC_enableInterrupt(&gFLCRegionConfig[0], FLC_INTERRUPT_DONE);

    gFLCRegionConfig[0].sourceStartAddress = (uint32_t)sourceBuffer;
    gFLCRegionConfig[0].destinationStartAddress = (uint32_t)destBuffer;
    gFLCRegionConfig[0].sourceEndAddress = (uint32_t)sourceBuffer + TRANSFERSIZE;
    FLC_configureRegion(&gFLCRegionConfig[0]);
    FLC_startRegion(&gFLCRegionConfig[0]);
    
    if(SystemP_FAILURE == retval && (rl2_of_reg->IRQENABLE_SET & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MASK) == 0)
    {
        retval = SystemP_FAILURE;
    }

    /* Wait for the interrupt */
    SemaphoreP_pend(&gSemObj, SystemP_WAIT_FOREVER);

    if(SystemP_FAILURE == retval && (rl2_of_reg->IRQENABLE_SET & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MASK) == 0)
    {
        retval = SystemP_FAILURE;
    }

    SemaphoreP_destruct(&gSemObj);

    if(SystemP_FAILURE == retval && rl2_of_reg->IRQENABLE_SET != 0)
    {
        retval = SystemP_FAILURE;
    }

    HwiP_disable();
    
    /* FLC write interrupt */
    FLC_enableInterrupt(&gFLCRegionConfig[0], FLC_INTERRUPT_WRITE_ERROR);
    if(SystemP_FAILURE == retval && (rl2_of_reg->IRQENABLE_SET & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_WRERR_MASK) == 0)
    {
        retval = SystemP_FAILURE;
    }
    FLC_disableInterrupt(&gFLCRegionConfig[0], FLC_INTERRUPT_WRITE_ERROR);
    if(SystemP_FAILURE == retval && rl2_of_reg->IRQENABLE_SET != 0)
    {
        retval = SystemP_FAILURE;
    }
    /* FLC read interrupt*/
    FLC_enableInterrupt(&gFLCRegionConfig[0], FLC_INTERRUPT_READ_ERROR);
    if(SystemP_FAILURE == retval && (rl2_of_reg->IRQENABLE_SET & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_RDERR_MASK) == 0)
    {
        retval = SystemP_FAILURE;
    }
    FLC_disableInterrupt(&gFLCRegionConfig[0], FLC_INTERRUPT_READ_ERROR);
    if(SystemP_FAILURE == retval && rl2_of_reg->IRQENABLE_SET != 0)
    {
        retval = SystemP_FAILURE;
    }
    HwiP_enable();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

void *test_flc_enable_disable(void* args)
{
    int32_t retval = SystemP_SUCCESS;
    CSL_rl2_of_cba4Regs * rl2_of_reg;
    rl2_of_reg = (CSL_rl2_of_cba4Regs *)gFLCRegionConfig[0].baseAddress;

    /* enable FLC */
    FLC_startRegion(&gFLCRegionConfig[0]);
    if(SystemP_FAILURE == retval && (rl2_of_reg->FLC[0].CTL & CSL_RL2_OF_CBA4_FLC_CTL_FENABLE_MASK) == 0)
    {
        retval = SystemP_FAILURE;
    }
    FLC_disable(&gFLCRegionConfig[0]);
    if(SystemP_FAILURE == retval && (rl2_of_reg->FLC[0].CTL & CSL_RL2_OF_CBA4_FLC_CTL_FENABLE_MASK) != 0)
    {
        retval = SystemP_FAILURE;
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

void *test_rl2_config(void *args)
{
    int32_t retval = SystemP_SUCCESS;
    CSL_rl2_of_cba4Regs * rl2_of_reg;
    rl2_of_reg = (CSL_rl2_of_cba4Regs *)gRL2Config[0].baseAddress;

    uint32_t RA[10][3] =
    {
        {
            0x70000000, 128*1024,
            RL2_API_STS_SUCCESS
        },
        {
            0x70000000, 8*1024,
            RL2_API_STS_SUCCESS
        },
        {
            0x70000000, 16*1024,
            RL2_API_STS_SUCCESS
        },
        {
            0x70000000, 32*1024,
            RL2_API_STS_SUCCESS
        },
        {
            0x70000000, 64*1024,
            RL2_API_STS_SUCCESS
        },
        {
            0x70000000, 256*1024,
            RL2_API_STS_SUCCESS
        }
    };

    /* Save original gRL2Config[0] so it can be restored after this test. */
    RL2_Params savedConfig = gRL2Config[0];

    /* configure RL2 and check*/
    RL2_API_STS_t res = RL2_configure(&gRL2Config[0]);
    if(SystemP_SUCCESS == retval && RL2_API_STS_SUCCESS != res)
    {
        retval = SystemP_FAILURE;
    }

    for(unsigned int i = 0; i < 5; i++)
    {
        gRL2Config[0].l2Sram0Base = RA[i][0];
        gRL2Config[0].l2Sram0Len  = RA[i][1];
        res = RL2_configure(&gRL2Config[0]);
        if(SystemP_SUCCESS == retval && RA[i][2] != res)
        {
            retval = SystemP_FAILURE;
        }
        if(RL2_API_STS_SUCCESS == res)
        {
            if(SystemP_SUCCESS == retval && rl2_of_reg->REM.ADR != RA[i][0])
            {
                retval = SystemP_FAILURE;
            }
            if(SystemP_SUCCESS == retval && rl2_of_reg->REM.LEN != RA[i][1])
            {
                retval = SystemP_FAILURE;
            }
        }
    };

    /* Restore the original global config so later tests use correct values */
    gRL2Config[0] = savedConfig;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);

    return NULL;
}

/**
 * \brief Configure all FLC regions with unique flash/SRAM ranges.
 *
 * Test Category: Functional
 *
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput All regions program successfully and registers reflect configuration.
 */
void *TestOptiflash_configAllFlcRegions(void *args)
{
    int32_t retval = SystemP_SUCCESS;
    CSL_rl2_of_cba4Regs *regs = (CSL_rl2_of_cba4Regs *)gFLCRegionConfig[0].baseAddress;

    /* Unique ranges per region: 1MB each, contiguous flash blocks; SRAM spaced by 256KB */
    const uint32_t srcBase   = TEST_OPTIFLASH_FLC_SRC_START_ADDR;
    const uint32_t dstBase   = TEST_OPTIFLASH_DST_START_ADDR;
    const uint32_t regionSize = TEST_OPTIFLASH_FLC_REGION_SIZE;
    const uint32_t dstStride  = TEST_OPTIFLASH_FLC_DST_STRIDE;
    uint32_t srcStart;
    uint32_t srcEnd;
    uint32_t dstStart;
    FLC_API_STS_t sts;
    for(uint32_t r = 0U; r < TEST_OPTIFLASH_FLC_NUM_REGIONS; r++)
    {
        srcStart = srcBase + (r * regionSize);
        srcEnd   = srcStart + regionSize;
        dstStart = dstBase   + (r * dstStride);

        /* Program unique ranges into the SysCfg-provided region descriptors */
        gFLCRegionConfig[r].sourceStartAddress      = srcStart;
        gFLCRegionConfig[r].sourceEndAddress        = srcEnd;
        gFLCRegionConfig[r].destinationStartAddress = dstStart;

        sts = FLC_configureRegion(&gFLCRegionConfig[r]);
        if(SystemP_SUCCESS == retval && sts != FLC_API_STS_SUCCESS)
        {
            retval = SystemP_FAILURE;
        }

        /* Verify registers reflect the configuration for region r */
        if(SystemP_SUCCESS == retval && regs->FLC[r].LO != srcStart)
        {
            retval = SystemP_FAILURE;
        }
        if(SystemP_SUCCESS == retval && regs->FLC[r].HI != srcEnd)
        {
            retval = SystemP_FAILURE;
        }
        if(SystemP_SUCCESS == retval && regs->FLC[r].RA != dstStart)
        {
            retval = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Validate FLC copy data integrity for a single region.
 *
 * Test Category: Functional
 *
 * Uses a known source pattern, triggers an FLC copy to a destination buffer
 * and compares the buffers for exact match to validate data integrity and
 * cache coherency steps.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput Destination buffer equals source buffer after transfer.
 */
void *TestOptiflash_validateFlcDataIntegrity(void *args)
{
    int32_t retval = SystemP_SUCCESS;
    uint32_t cpy_status = 0U;
    uint32_t attempts   = 0U;
    const uint32_t maxAttempts = 1000000U;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];

    /* Ensure any prior test left no error/IRQ state */
    TestOptiflash_resetFlc(region);

    /* Prepare destination with a known state */
    memset(destBuffer, 0, TRANSFERSIZE);
    CacheP_wbInv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);

    /* Configure FLC region to copy source -> destination */
    region->sourceStartAddress      = (uint32_t)sourceBuffer;
    region->destinationStartAddress = (uint32_t)destBuffer;
    region->sourceEndAddress        = (uint32_t)sourceBuffer + TRANSFERSIZE;

    FLC_configureRegion(region);
    FLC_startRegion(region);

    /* Wait for completion */
    do {
        FLC_isRegionDone(region, &cpy_status);
        attempts++;
        if(attempts > maxAttempts)
        {
            DebugP_logError("FLC region copy timeout\r\n");
            retval = SystemP_FAILURE;
            break;
        }
    } while ((cpy_status & (1U << region->regionId)) == 0U);

    /* Compare buffers; expect exact match */
    if(SystemP_SUCCESS == retval)
    {
        /* Ensure CPU sees latest writes from FLC */
        CacheP_inv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);
        if(0 != memcmp(sourceBuffer, destBuffer, TRANSFERSIZE))
        {
            DebugP_logError("FLC region copy data mismatch\r\n");
            retval = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);

    return NULL;
}

/**
 * \brief Concurrent FLC copies using two regions and integrity check.
 *
 * Test Category: Functional
 *
 * Configures two FLC regions to copy distinct halves of the source buffer to
 * a single destination and waits for both to complete, validating each half
 * for correctness to ensure concurrent region operation is supported.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput Both halves of the destination match the corresponding source halves.
 */
void *TestOptiflash_concurrentFlcRegionCopy(void *args)
{
    int32_t retval = SystemP_SUCCESS;
    const uint32_t half = TRANSFERSIZE / 2U;
    uint32_t status = 0U;
    uint32_t attempts = 0U;
    const uint32_t maxAttempts = 1000000U;
    FLC_RegionInfo *r0 = &gFLCRegionConfig[0];
    FLC_RegionInfo *r1 = &gFLCRegionConfig[1];
    const uint32_t doneMask = (1U << r0->regionId) | (1U << r1->regionId);

    /* Prepare destination buffer */
    memset(destBuffer, 0, TRANSFERSIZE);
    CacheP_wbInv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);

    /* Configure two regions to copy distinct halves */
    r0->sourceStartAddress      = (uint32_t)sourceBuffer;
    r0->sourceEndAddress        = (uint32_t)sourceBuffer + half;
    r0->destinationStartAddress = (uint32_t)destBuffer;

    r1->sourceStartAddress      = (uint32_t)sourceBuffer + half;
    r1->sourceEndAddress        = (uint32_t)sourceBuffer + TRANSFERSIZE;
    r1->destinationStartAddress = (uint32_t)destBuffer + half;

    if(FLC_API_STS_SUCCESS != FLC_configureRegion(r0))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_configureRegion(r1))
    {
        retval = SystemP_FAILURE;
    }

    /* Start both regions */
    if(SystemP_SUCCESS == retval)
    {
        if(FLC_API_STS_SUCCESS != FLC_startRegion(r0))
        {
            retval = SystemP_FAILURE;
        }
        if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_startRegion(r1))
        {
            retval = SystemP_FAILURE;
        }
    }

    /* Poll completion bits until both regions complete.
     * FLC_isRegionDone reads the shared FLC_STS register; both r0 and r1
     * are polled explicitly so completion of each region is visible. */
    if(SystemP_SUCCESS == retval)
    {
        do {
            uint32_t status_r1 = 0U;
            FLC_isRegionDone(r0, &status);
            FLC_isRegionDone(r1, &status_r1);
            status |= status_r1;
            attempts++;
            if(attempts > maxAttempts)
            {
                DebugP_logError("Concurrent FLC copy timeout\r\n");
                retval = SystemP_FAILURE;
                break;
            }
        } while (((status & doneMask) != doneMask));
    }

    /* Validate data integrity for each half */
    if(SystemP_SUCCESS == retval)
    {
        CacheP_inv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);
        if(0 != memcmp(sourceBuffer, destBuffer, half))
        {
            DebugP_logError("Concurrent FLC copy mismatch in first half\r\n");
            retval = SystemP_FAILURE;
        }
        if(SystemP_SUCCESS == retval && 0 != memcmp(sourceBuffer + half, destBuffer + half, half))
        {
            DebugP_logError("Concurrent FLC copy mismatch in second half\r\n");
            retval = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Detect and clear FLC read errors via invalid source ranges.
 *
 * Test Category: Negative
 *
 * Intentionally configures a source address outside the valid XIP range to
 * trigger a read error, verifies the error is reported and can be cleared by
 * the API, and restores original region configuration.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput Read error is observed then cleared successfully.
 */
void *TestOptiflash_flcReadErrorDetection(void *args)
{
    int32_t retval = SystemP_SUCCESS;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    uint32_t rdErr = 0U;
    uint32_t attempts = 0U;
    const uint32_t maxAttempts = 1000000U;
    /* Save original configuration to restore later */
    FLC_RegionInfo origConfig = gFLCRegionConfig[0];

    /* Ensure clean FLC state before the error-injection test */
    TestOptiflash_resetFlc(region);

    /* Configure source address to a completely unmapped AXI region to trigger a read error. */
    region->sourceStartAddress      = TEST_OPTIFLASH_FLC_INVALID_SRC_ADDR;
    region->sourceEndAddress        = TEST_OPTIFLASH_FLC_INVALID_SRC_ADDR + TEST_OPTIFLASH_ERROR_XFER_SIZE;
    region->destinationStartAddress = (uint32_t)destBuffer;

    if(FLC_API_STS_SUCCESS != FLC_configureRegion(region))
    {
        retval = SystemP_FAILURE;
    }

    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_startRegion(region))
    {
        retval = SystemP_FAILURE;
    }

    /* Poll read error status */
    if(SystemP_SUCCESS == retval)
    {
        do {
            FLC_wasReadError(region, &rdErr);
            attempts++;
            if(attempts > maxAttempts)
            {
                DebugP_logError("FLC read error not observed\r\n");
                retval = SystemP_FAILURE;
                break;
            }
        } while (rdErr == 0U);

        if(SystemP_SUCCESS == retval && rdErr == 0U)
        {
            retval = SystemP_FAILURE;
        }
    }

    /* Clear read error and verify clear path returns success */
    if(SystemP_SUCCESS == retval)
    {
        if(FLC_API_STS_SUCCESS != FLC_clearReadError(region))
        {
            retval = SystemP_FAILURE;
        }
    }

    /* Also test FLC_clearInterrupt with FLC_INTERRUPT_READ_ERROR for coverage */
    if(SystemP_SUCCESS == retval)
    {
        if(FLC_API_STS_SUCCESS != FLC_clearInterrupt(region, FLC_INTERRUPT_READ_ERROR))
        {
            DebugP_logError("FLC_clearInterrupt(FLC_INTERRUPT_READ_ERROR) failed\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Return FLC to idle/clean state so subsequent tests are unaffected */
    TestOptiflash_resetFlc(region);

    /* Restore original configuration */
    gFLCRegionConfig[0] = origConfig;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Detect and clear FLC write errors via invalid destination ranges.
 *
 * Test Category: Negative
 *
 * Configures the destination address beyond the active RL2 SRAM window to
 * force a write error condition and verifies the driver reports and clears
 * the error appropriately.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput Write error is observed and cleared via API calls.
 */
void *TestOptiflash_flcWriteErrorDetection(void *args)
{
    int32_t retval = SystemP_SUCCESS;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    uint32_t wrErr = 0U;
    uint32_t attempts = 0U;
    const uint32_t maxAttempts = 1000000U;
    /* Save original configuration to restore later */
    FLC_RegionInfo origConfig = gFLCRegionConfig[0];

    /* Ensure clean FLC state */
    TestOptiflash_resetFlc(region);

    /* Use valid flash source from original config and
     * set the destination to an unmapped SRAM address to trigger a write error. */
    region->sourceStartAddress      = origConfig.sourceStartAddress;
    region->sourceEndAddress        = origConfig.sourceStartAddress + TEST_OPTIFLASH_ERROR_XFER_SIZE;
    region->destinationStartAddress = TEST_OPTIFLASH_UNMAPPED_DST_ADDR; /* unmapped – triggers FLC write error */

    if(FLC_API_STS_SUCCESS != FLC_configureRegion(region))
    {
        retval = SystemP_FAILURE;
    }

    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_startRegion(region))
    {
        retval = SystemP_FAILURE;
    }

    /* Poll write error status */
    if(SystemP_SUCCESS == retval)
    {
        do {
            FLC_wasWriteError(region, &wrErr);
            attempts++;
            if(attempts > maxAttempts)
            {
                DebugP_logError("FLC write error not observed\r\n");
                retval = SystemP_FAILURE;
                break;
            }
        } while (wrErr == 0U);

        if(SystemP_SUCCESS == retval && wrErr == 0U)
        {
            retval = SystemP_FAILURE;
        }
    }

    /* Clear write error and verify clear path returns success */
    if(SystemP_SUCCESS == retval)
    {
        if(FLC_API_STS_SUCCESS != FLC_clearWriteError(region))
        {
            retval = SystemP_FAILURE;
        }
    }

    /* Also test FLC_clearInterrupt with FLC_INTERRUPT_WRITE_ERROR for coverage */
    if(SystemP_SUCCESS == retval)
    {
        if(FLC_API_STS_SUCCESS != FLC_clearInterrupt(region, FLC_INTERRUPT_WRITE_ERROR))
        {
            DebugP_logError("FLC_clearInterrupt(FLC_INTERRUPT_WRITE_ERROR) failed\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Return FLC to idle/clean state so subsequent tests are unaffected */
    TestOptiflash_resetFlc(region);

    /* Restore original configuration */
    gFLCRegionConfig[0] = origConfig;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Abort in-flight FLC transfer by disabling region immediately.
 *
 * Test Category: Functional
 *
 * Starts a region transfer then immediately disables the region to ensure the
 * API and hardware allow aborting transfers; verifies DONE is not asserted
 * and that destination is not fully overwritten.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput Disable returns success and destination is not fully overwritten.
 */
void *TestOptiflash_disableFlcRegion(void *args)
{
    (void)args;
    uint32_t status = 0U;
    /* Use SysCfg-provided region info to ensure correct base per core */
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    region->sourceStartAddress      = (uint32_t)sourceBuffer;
    region->sourceEndAddress        = (uint32_t)sourceBuffer + (uint32_t)TRANSFERSIZE;
    region->destinationStartAddress = (uint32_t)destBuffer;

    /* Ensure destination buffer has a distinct pattern before copy */
    memset(destBuffer, TEST_OPTIFLASH_FILL_PATTERN_AA, TRANSFERSIZE);

    TEST_ASSERT_EQUAL_INT32(FLC_API_STS_SUCCESS, FLC_configureRegion(region));
    TEST_ASSERT_EQUAL_INT32(FLC_API_STS_SUCCESS, FLC_startRegion(region));

    /* Immediately disable the region to abort any ongoing transfer */
    TEST_ASSERT_EQUAL_INT32(FLC_API_STS_SUCCESS, FLC_disable(region));

    /* Poll DONE status multiple times and assert it does not get set */
    const uint32_t doneMask = (1U << (uint32_t)region->regionId);
    for (int i = 0; i < 20; i++)
    {
        TEST_ASSERT_EQUAL_INT32(FLC_API_STS_SUCCESS, FLC_isRegionDone(region, &status));
        TEST_ASSERT_FALSE_MESSAGE(((status & doneMask) != 0U), "DONE status set after FLC_disable()");
        ClockP_usleep(1000); /* 1 ms */
    }

    /* Confirm destination was not fully overwritten by source */
    int cmp = memcmp(destBuffer, sourceBuffer, TRANSFERSIZE);
    TEST_ASSERT_NOT_EQUAL(0, cmp);

    return NULL;
}

/**
 * \brief Validate FLC_readIRQMask reflects interrupt mask enable/disable.
 *
 * Test Category: Functional
 *
 * Registers an ISR, enables the DONE interrupt for the region, triggers a
 * transfer and verifies the masked status read in the ISR reflects the DONE
 * mask. Also verifies mask clears after disabling interrupt.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput Masked DONE status observed during ISR and cleared after disable.
 */
void *TestOptiflash_flcReadIRQMaskValidation(void *args)
{
    (void)args;

    int32_t retval = SystemP_SUCCESS;
    uint32_t mask = 0U;
    HwiP_Params hwiPrms;
    HwiP_Object hwiobj;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];

    /* Ensure clean state and prepare sync primitive */
    TestOptiflash_resetFlc(region);
    SemaphoreP_constructBinary(&gSemObj, 0U);

    /* Register RL2 DONE ISR for this instance */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = TestOptiflash_getRl2IrqNum(region->baseAddress);
    hwiPrms.args     = (void*)args;
    hwiPrms.callback = &TestOptiflash_flcDoneIsr;
    hwiPrms.isPulse  = (uint8_t)0U;
    hwiPrms.priority = 4U;
    hwiPrms.isFIQ    = (uint8_t)0U;
    HwiP_construct(&hwiobj, &hwiPrms);

    /* Enable DONE interrupt; masked status should be zero before any event */
    if(FLC_API_STS_SUCCESS != FLC_enableInterrupt(region, FLC_INTERRUPT_DONE))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_readIRQMask(region, &mask))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && (mask & CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_DON_MASK) != 0U)
    {
        retval = SystemP_FAILURE;
    }
    /* Configure a valid transfer and start it to exercise the ISR */
    memset(destBuffer, 0, TRANSFERSIZE);
    CacheP_wbInv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);
    region->sourceStartAddress      = (uint32_t)sourceBuffer;
    region->sourceEndAddress        = (uint32_t)sourceBuffer + TRANSFERSIZE;
    region->destinationStartAddress = (uint32_t)destBuffer;
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_configureRegion(region))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_startRegion(region))
    {
        retval = SystemP_FAILURE;
    }

    /* Wait for DONE ISR to signal completion */
    if(SystemP_SUCCESS == retval)
    {
        SemaphoreP_pend(&gSemObj, SystemP_WAIT_FOREVER);
    }

    /* Masked status captured in ISR should indicate DONE */
    if(SystemP_SUCCESS == retval && (TestOptiflash_LastMaskedStatus & CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_DON_MASK) == 0U)
    {
        retval = SystemP_FAILURE;
    }

    /* Data integrity check confirms transfer actually completed */
    if(SystemP_SUCCESS == retval)
    {
        CacheP_inv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);
        if(0 != memcmp(sourceBuffer, destBuffer, TRANSFERSIZE))
        {
            retval = SystemP_FAILURE;
        }
    }

    /* After ISR cleared interrupt, masked status should be zero */
    mask = 0U;
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_readIRQMask(region, &mask))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && (mask & CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_DON_MASK) != 0U)
    {
        retval = SystemP_FAILURE;
    }

    /* Disable interrupt and verify mask clears */
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_disableInterrupt(region, FLC_INTERRUPT_DONE))
    {
        retval = SystemP_FAILURE;
    }
    mask = 0U;
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_readIRQMask(region, &mask))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && (mask & CSL_RL2_OF_CBA4_IRQSTATUS_MSK_FLC_DON_MASK) != 0U)
    {
        retval = SystemP_FAILURE;
    }

    /* Clean-up sync primitive; ISR clear is handled in the HWI */
    SemaphoreP_destruct(&gSemObj);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Validate FLC_readIRQStatus RAW status set/clear semantics.
 *
 * Test Category: Functional
 *
 * Starts a transfer and polls RAW IRQ status for the DONE bit, verifies it's
 * set after completion and clears correctly after calling the clear API.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput RAW DONE observed post-completion and cleared by API.
 */
void *TestOptiflash_flcReadIRQStatusValidation(void *args)
{
    (void)args;

    int32_t retval = SystemP_SUCCESS;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    uint32_t raw = 0U;
    uint32_t doneReg = 0U;
    uint32_t attempts = 0U;
    const uint32_t donePollMaxAttempts = 1000000U;
    const uint32_t doneMask = (1U << region->regionId);
    const uint32_t rawIrqPollMaxAttempts = 5000U; /* up to ~5 ms */

    /* Clean state */
    TestOptiflash_resetFlc(region);

    /* Prevent any previously-registered HWI from clearing RAW: disable only the RL2 IRQ */
    uint32_t rl2Irq = TestOptiflash_getRl2IrqNum(region->baseAddress);
    uint32_t rl2IrqOldState = HwiP_disableInt(rl2Irq);

    /* Enable DONE interrupt */
    if(FLC_API_STS_SUCCESS != FLC_enableInterrupt(region, FLC_INTERRUPT_DONE))
    {
        retval = SystemP_FAILURE;
    }

    /* Configure and start a valid transfer */
    region->sourceStartAddress      = (uint32_t)sourceBuffer;
    region->sourceEndAddress        = (uint32_t)sourceBuffer + TRANSFERSIZE;
    region->destinationStartAddress = (uint32_t)destBuffer;
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_configureRegion(region))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_startRegion(region))
    {
        retval = SystemP_FAILURE;
    }

    /* Wait for transfer completion (poll FLC_STS) */
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS == FLC_isRegionDone(region, &doneReg))
    {
        attempts = 0U;
        while((doneReg & doneMask) == 0U)
        {
            attempts++;
            if(attempts > donePollMaxAttempts)
            {
                DebugP_logError("FLC DONE wait timeout\r\n");
                retval = SystemP_FAILURE;
                break;
            }
            FLC_isRegionDone(region, &doneReg);
        }
    }

    /* After completion, poll RAW IRQ status until DONE bit is observed */
    if(SystemP_SUCCESS == retval)
    {
        attempts = 0U;
        do {
            if(FLC_API_STS_SUCCESS != FLC_readIRQStatus(region, &raw))
            {
                retval = SystemP_FAILURE;
                break;
            }
            if((raw & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MASK) != 0U)
            {
                break; /* DONE observed in RAW */
            }
            ClockP_usleep(1000);
            attempts++;
        } while(attempts < rawIrqPollMaxAttempts);

        if(SystemP_SUCCESS == retval && (raw & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MASK) == 0U)
        {
            DebugP_logError("RAW DONE not observed after completion\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Clear interrupt and verify RAW status clears */
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_clearInterrupt(region, FLC_INTERRUPT_DONE))
    {
        retval = SystemP_FAILURE;
    }
    raw = 0U;
    if(SystemP_SUCCESS == retval && FLC_API_STS_SUCCESS != FLC_readIRQStatus(region, &raw))
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval && (raw & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MASK) != 0U)
    {
        retval = SystemP_FAILURE;
    }

    /* Disable interrupt to restore clean state */
    FLC_disableInterrupt(region, FLC_INTERRUPT_DONE);
    /* Restore the RL2 IRQ state now that RAW has been cleared */
    HwiP_restoreInt(rl2Irq, rl2IrqOldState);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Configure RL2 cache using SysCfg defaults and validate success.
 *
 * Test Category: Functional
 *
 * Initializes RL2 parameters from the SysCfg-generated `gRL2Config[0]` and
 * calls the RL2 configuration API to ensure success with the provided values.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput RL2_configure returns success for SysCfg-provided parameters.
 */
void *TestOptiflash_configureRL2Cache(void *args)
{
    (void)args;
    int32_t retval = SystemP_SUCCESS;
    RL2_Params params;
    RL2_API_STS_t sts;

    /* Initialize params with defaults */
    sts = RL2_initparams(&params);
    if(sts != RL2_API_STS_SUCCESS)
    {
        retval = SystemP_FAILURE;
    }

    /* Populate flash range, cache size, SRAM base/length and baseAddress */
    if(SystemP_SUCCESS == retval)
    {
        params.baseAddress  = gRL2Config[0].baseAddress;
        params.rangeStart   = gRL2Config[0].rangeStart;
        params.rangeEnd     = gRL2Config[0].rangeEnd;
        params.cacheSize    = gRL2Config[0].cacheSize;
        params.l2Sram0Base  = gRL2Config[0].l2Sram0Base;
        params.l2Sram0Len   = gRL2Config[0].l2Sram0Len;

        sts = RL2_configure(&params);
        if(sts != RL2_API_STS_SUCCESS)
        {
            retval = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Exercise RL2 cache size selection across supported sizes.
 *
 * Test Category: Functional
 *
 * Iterates through valid RL2 cache sizes (8K–256K), configures and enables
 * the cache for each size, and ensures enable/disable operations succeed.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput All cache sizes configure/enable/disable without error.
 */
void *TestOptiflash_rL2CacheSizeSelection(void *args)
{
    (void)args;
    int32_t retval = SystemP_SUCCESS;

    RL2_CacheSize sizes[] = {
        RL2_CACHESIZE_8K,
        RL2_CACHESIZE_16K,
        RL2_CACHESIZE_32K,
        RL2_CACHESIZE_64K,
        RL2_CACHESIZE_128K,
        RL2_CACHESIZE_256K,
    };

    for(unsigned int i = 0U; i < (sizeof(sizes)/sizeof(sizes[0])); i++)
    {
        RL2_Params params;
        RL2_API_STS_t sts;

        sts = RL2_initparams(&params);
        if(sts != RL2_API_STS_SUCCESS)
        {
            retval = SystemP_FAILURE;
            break;
        }

        params.baseAddress  = gRL2Config[0].baseAddress;
        params.rangeStart   = gRL2Config[0].rangeStart;
        params.rangeEnd     = gRL2Config[0].rangeEnd;
        params.l2Sram0Base  = gRL2Config[0].l2Sram0Base;
        params.l2Sram0Len   = gRL2Config[0].l2Sram0Len;
        params.cacheSize    = sizes[i];

        sts = RL2_configure(&params);
        if(sts != RL2_API_STS_SUCCESS)
        {
            retval = SystemP_FAILURE;
            break;
        }

        sts = RL2_enable(&params);
        if(sts != RL2_API_STS_SUCCESS)
        {
            retval = SystemP_FAILURE;
            break;
        }

        /* Clean up for next iteration */
        sts = RL2_disable(&params);
        if(sts != RL2_API_STS_SUCCESS)
        {
            retval = SystemP_FAILURE;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Safe RL2 reconfiguration while enabled.
 *
 * Test Category: Functional
 *
 * Configures RL2 with one cache size, enables it, then reconfigures to a
 * different cache size to ensure the RL2 API safely disables/reapplies
 * configuration and the control/status registers reflect the change.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput RL2 reconfiguration succeeds and control/status registers match new settings.
 */
void *TestOptiflash_rl2SafeReconfigureBehavior(void *args)
{
    (void)args;
    int32_t retval = SystemP_SUCCESS;
    RL2_Params params;
    RL2_API_STS_t sts;
    CSL_rl2_of_cba4Regs *regs = (CSL_rl2_of_cba4Regs *)gRL2Config[0].baseAddress;

    /* Cache sizes A and B for reconfiguration */
    const RL2_CacheSize sizeA = RL2_CACHESIZE_16K;
    const RL2_CacheSize sizeB = RL2_CACHESIZE_64K;

    /* Initialize params and seed from SysCfg-generated config */
    sts = RL2_initparams(&params);
    if(sts != RL2_API_STS_SUCCESS)
    {
        retval = SystemP_FAILURE;
    }
    if(SystemP_SUCCESS == retval)
    {
        params.baseAddress = gRL2Config[0].baseAddress;
        params.rangeStart  = gRL2Config[0].rangeStart;
        params.rangeEnd    = gRL2Config[0].rangeEnd;
        params.l2Sram0Base = gRL2Config[0].l2Sram0Base;
        params.l2Sram0Len  = gRL2Config[0].l2Sram0Len;
    }

    /* Configure RL2 with cache size A and enable */
    if(SystemP_SUCCESS == retval)
    {
        params.cacheSize = sizeA;
        sts = RL2_configure(&params);
        if(sts != RL2_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to configure RL2 with cache size A\r\n");
            retval = SystemP_FAILURE;
        }
    }
    if(SystemP_SUCCESS == retval)
    {
        sts = RL2_enable(&params);
        if(sts != RL2_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to enable RL2 with cache size A\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Confirm enable bit and size A set in L2_CTRL */
    if(SystemP_SUCCESS == retval)
    {
        uint32_t ctrl = regs->L2_CTRL;
        uint32_t enabled = (ctrl & CSL_RL2_OF_CBA4_L2_CTRL_ENABLE_MASK);
        uint32_t sizeFld = (ctrl & CSL_RL2_OF_CBA4_L2_CTRL_SIZE_MASK) >> CSL_RL2_OF_CBA4_L2_CTRL_SIZE_SHIFT;
        if((enabled == 0U) || (sizeFld != (uint32_t)sizeA))
        {
            DebugP_logError("RL2 control register does not reflect enabled state and cache size A\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Modify to cache size B and call RL2_configure(); RL2_configure safely disables internally */
    if(SystemP_SUCCESS == retval)
    {
        params.cacheSize = sizeB;
        sts = RL2_configure(&params);
        if(sts != RL2_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to reconfigure RL2 with cache size B\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Verify new cache size applied, RL2_STS OK_TO_GO and enable bit set */
    if(SystemP_SUCCESS == retval)
    {
        uint32_t ctrl = regs->L2_CTRL;
        uint32_t enabled = (ctrl & CSL_RL2_OF_CBA4_L2_CTRL_ENABLE_MASK);
        uint32_t sizeFld = (ctrl & CSL_RL2_OF_CBA4_L2_CTRL_SIZE_MASK) >> CSL_RL2_OF_CBA4_L2_CTRL_SIZE_SHIFT;
        if((enabled == 0U) || (sizeFld != (uint32_t)sizeB))
        {
            DebugP_logError("RL2 control register does not reflect enabled state and cache size B\r\n");
            retval = SystemP_FAILURE;
        }
        if(SystemP_SUCCESS == retval && regs->L2_STS != CSL_RL2_OF_CBA4_L2_STS_OK_TO_GO_MASK)
        {
            DebugP_logError("RL2 status register does not indicate OK_TO_GO\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Explicitly re-enable and confirm operational state remains enabled */
    if(SystemP_SUCCESS == retval)
    {
        sts = RL2_enable(&params);
        if(sts != RL2_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to re-enable RL2\r\n");
            retval = SystemP_FAILURE;
        }
        else
        {
            uint32_t ctrl = regs->L2_CTRL;
            if((ctrl & CSL_RL2_OF_CBA4_L2_CTRL_ENABLE_MASK) == 0U)
            {
                DebugP_logError("RL2 control register does not reflect enabled state\r\n");
                retval = SystemP_FAILURE;
            }
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Integration test: FLC transfer while RL2 cache enabled.
 *
 * Test Category: Integration
 *
 * Configures and enables RL2 cache, performs an FLC copy from flash to
 * destination, invalidates CPU caches for the destination and verifies data
 * integrity and RL2 IRQ mask read operations.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput FLC completes, destination equals source, and RL2 IRQ mask readable.
 */
void *TestOptiflash_integrationFlcWithRl2CacheCoherency(void *args)
{
    int32_t retval = SystemP_SUCCESS;
    uint32_t i;
    volatile uint32_t sink = 0U;
    FLC_API_STS_t flcSts;
    uint32_t sts = 0U;
    uint32_t doneMask;
    uint32_t attempts = 0U;
    const uint32_t maxAttempts = 200U; /* 200 x 1ms = ~200ms */
    uint32_t irqMask = 0U;
    /* Prepare RL2 configuration using SysCfg-provided defaults (flash XIP cache) */
    RL2_Params rl2Cfg;
    RL2_API_STS_t rl2Sts = RL2_initparams(&rl2Cfg);
    if(rl2Sts != RL2_API_STS_SUCCESS)
    {
        retval = SystemP_FAILURE;
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

    if(SystemP_SUCCESS == retval)
    {
        rl2Sts = RL2_configure(&rl2Cfg);
        if(rl2Sts != RL2_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to configure RL2 cache\r\n");
            retval = SystemP_FAILURE;
        }
    }

    if(SystemP_SUCCESS == retval)
    {
        rl2Sts = RL2_enable(&rl2Cfg);
        if(rl2Sts != RL2_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to enable RL2 cache\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* do NOT modify flash-backed sourceBuffer; clear destination */
    memset(destBuffer, 0, TRANSFERSIZE);

    /* Flush the dirty zero-filled cache lines to physical memory and
     * invalidate them so no dirty lines remain when FLC writes via DMA. */
    CacheP_wbInv((void*)destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);

    /* warm CPU cache for destBuffer via reads */
    for(i = 0U; i < TRANSFERSIZE; i++)
    {
        sink ^= destBuffer[i];
    }
    (void)sink;

    /* start FLC transfer source -> dest */
    TestOptiflash_resetFlc(&gFLCRegionConfig[0]);
    gFLCRegionConfig[0].sourceStartAddress      = (uint32_t)sourceBuffer;
    gFLCRegionConfig[0].destinationStartAddress = (uint32_t)destBuffer;
    gFLCRegionConfig[0].sourceEndAddress        = (uint32_t)sourceBuffer + TRANSFERSIZE;

    if(SystemP_SUCCESS == retval)
    {
        flcSts = FLC_configureRegion(&gFLCRegionConfig[0]);
        if(flcSts != FLC_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to configure FLC region\r\n");
            retval = SystemP_FAILURE;
        }
        else
        {
            flcSts = FLC_startRegion(&gFLCRegionConfig[0]);
            if(flcSts != FLC_API_STS_SUCCESS)
            {
                DebugP_logError("Failed to start FLC region\r\n");
                retval = SystemP_FAILURE;
            }
        }
    }

    /* Wait for completion with ~200ms timeout using usleep */
    if(SystemP_SUCCESS == retval)
    {
        doneMask = (1U << (gFLCRegionConfig[0].regionId & 0x3U));
        attempts = 0U;
        do {
            FLC_isRegionDone(&gFLCRegionConfig[0], &sts);
            if((sts & doneMask) == 0U)
            {
                ClockP_usleep(1000U);
                attempts++;
            }
        } while(((sts & doneMask) == 0U) && (attempts < maxAttempts));

        if((sts & doneMask) == 0U)
        {
            DebugP_logError("FLC region copy did not complete within timeout\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Keep RL2 enabled; invalidate CPU cache lines for dest range only */
    if(SystemP_SUCCESS == retval)
    {
        CacheP_inv((void*)destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);
    }

    /* Verify data */
    if(SystemP_SUCCESS == retval)
    {
        int cmp = memcmp(destBuffer, sourceBuffer, TRANSFERSIZE);
        if(cmp != 0)
        {
            DebugP_logError("Data mismatch between source and destination buffers after FLC transfer with RL2 cache enabled\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Basic SysCfg sanity: RL2 registers are readable */
    if(SystemP_SUCCESS == retval)
    {
        irqMask = 0U;
        rl2Sts = RL2_readIRQMask(&rl2Cfg, &irqMask);
        if(rl2Sts != RL2_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to read RL2 IRQ mask register\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* RL2 remains enabled during this test */

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Start-while-busy API robustness test.
 *
 * Test Category: Functional
 *
 * Starts an FLC region then immediately calls start again while hardware is
 * busy to ensure the API behaves safely (returns success) and hardware
 * completes the original transfer without data corruption or errors.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput Second start returns success; transfer completes and data matches.
 */
void *TestOptiflash_flcStartWhileBusy(void *args)
{
    (void)args;
    int32_t retval = SystemP_SUCCESS;
    FLC_API_STS_t flcSts;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    uint32_t status = 0U;
    FLC_API_STS_t flcSts2;
    uint32_t attempts = 0U;
    const uint32_t maxAttempts = 200U;
    uint32_t rdErr = 0U, wrErr = 0U;
    const uint32_t doneMask = (1U << (uint32_t)region->regionId);

    /* Clean state */
    TestOptiflash_resetFlc(region);

    /* Prepare destination and cache state */
    memset(destBuffer, 0, TRANSFERSIZE);
    CacheP_wbInv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);

    /* Configure a valid transfer */
    region->sourceStartAddress      = (uint32_t)sourceBuffer;
    region->sourceEndAddress        = (uint32_t)sourceBuffer + TRANSFERSIZE;
    region->destinationStartAddress = (uint32_t)destBuffer;
    flcSts = FLC_configureRegion(region);
    if(flcSts != FLC_API_STS_SUCCESS)
    {
        DebugP_logError("Failed to configure FLC region\r\n");
        retval = SystemP_FAILURE;
    }

    /* Start Region0 transfer */
    if(SystemP_SUCCESS == retval)
    {
        flcSts = FLC_startRegion(region);
        if(flcSts != FLC_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to start FLC region\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Immediately request start again while busy */
    if(SystemP_SUCCESS == retval)
    {
        flcSts2 = FLC_startRegion(region);
        /* Expect call to be safe; API returns success and hardware remains busy */
        if(flcSts2 != FLC_API_STS_SUCCESS)
        {
            DebugP_logError("FLC_startRegion() did not return success when called while busy\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Wait for completion with timeout (~200ms) */
    if(SystemP_SUCCESS == retval)
    {
        attempts = 0U;
        do {
            FLC_isRegionDone(region, &status);
            if((status & doneMask) == 0U)
            {
                ClockP_usleep(1000U);
                attempts++;
            }
        } while(((status & doneMask) == 0U) && (attempts < maxAttempts));

        if((status & doneMask) == 0U)
        {
            DebugP_logError("FLC did not complete after start-while-busy sequence\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Verify data */
    if(SystemP_SUCCESS == retval)
    {
        CacheP_inv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);
        if(0 != memcmp(sourceBuffer, destBuffer, TRANSFERSIZE))
        {
            DebugP_logError("Data mismatch after start-while-busy\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Ensure no read/write error latched */
    if(SystemP_SUCCESS == retval)
    {
        FLC_wasReadError(region, &rdErr);
        FLC_wasWriteError(region, &wrErr);
        if((rdErr != 0U) || (wrErr != 0U))
        {
            DebugP_logError("Unexpected FLC error after start-while-busy\r\n");
            retval = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Zero-length transfer behavior validation.
 *
 * Test Category: Functional
 *
 * Configures a transfer where sourceStart == sourceEnd to validate that the
 * hardware/driver handles zero-length or single-beat transfers gracefully and
 * does not produce widespread unintended writes.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput Transfer completes without errors; destination unchanged or only first beat modified.
 */
void *TestOptiflash_flcZeroLengthTransfer(void *args)
{
    (void)args;
    int32_t retval = SystemP_SUCCESS;
    FLC_API_STS_t flcSts;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    uint32_t status = 0U;
    uint32_t attempts = 0U;
    const uint32_t maxAttempts = 200U;
    const uint32_t beat = TEST_OPTIFLASH_CACHE_LINE_BYTES; /* typical cache line/granularity */
    uint32_t diffCount = 0U;
    uint32_t raw = 0U;
    const uint32_t doneMask = (1U << (uint32_t)region->regionId);

    /* Clean state */
    TestOptiflash_resetFlc(region);

    /* Prime destination with a known pattern and flush caches */
    memset(destBuffer, TEST_OPTIFLASH_FILL_PATTERN_CD, TRANSFERSIZE);
    CacheP_wbInv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);

    /* Configure zero-length transfer: sourceStart == sourceEnd */
    region->sourceStartAddress      = (uint32_t)sourceBuffer;
    region->sourceEndAddress        = (uint32_t)sourceBuffer; /* zero length */
    region->destinationStartAddress = (uint32_t)destBuffer;

    flcSts = FLC_configureRegion(region);
    if(flcSts != FLC_API_STS_SUCCESS)
    {
        DebugP_logError("Failed to configure FLC region for zero-length transfer\r\n");
        retval = SystemP_FAILURE;
    }

    /* Start transfer */
    if(SystemP_SUCCESS == retval)
    {
        flcSts = FLC_startRegion(region);
        if(flcSts != FLC_API_STS_SUCCESS)
        {
            DebugP_logError("Failed to start FLC region for zero-length transfer\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Poll DONE; expect graceful completion quickly */
    if(SystemP_SUCCESS == retval)
    {
        attempts = 0U;
        do {
            FLC_isRegionDone(region, &status);
            if((status & doneMask) == 0U)
            {
                ClockP_usleep(1000U);
                attempts++;
            }
        } while(((status & doneMask) == 0U) && (attempts < maxAttempts));

        if((status & doneMask) == 0U)
        {
            DebugP_logError("Zero-length transfer did not report DONE\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Verify destination unchanged OR only the first beat (e.g., 64B) was written.
     * Some implementations treat LO==HI as a single-beat transfer. Accept either
     * behavior as graceful (no errors) but flag unexpected widespread changes.
     */
    if(SystemP_SUCCESS == retval)
    {
        CacheP_inv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);
        diffCount = 0U;
        for(uint32_t i = 0U; i < TRANSFERSIZE; i++)
        {
            if(destBuffer[i] != (uint8_t)TEST_OPTIFLASH_FILL_PATTERN_CD)
            {
                diffCount++;
            }
        }
        if(diffCount == 0U)
        {
            /* strict no-modification behavior */
        }
        else if(diffCount <= beat)
        {
            /* Accept localized first-beat modification; ensure bytes beyond beat remain unchanged */
            for(uint32_t i = beat; i < TRANSFERSIZE; i++)
            {
                if(destBuffer[i] != (uint8_t)TEST_OPTIFLASH_FILL_PATTERN_CD)
                {
                    DebugP_logError("Bytes beyond first beat modified during zero-length transfer\r\n");
                    retval = SystemP_FAILURE;
                    break;
                }
            }
        }
        else
        {
            DebugP_logError("Destination modified beyond one beat during zero-length transfer\r\n");
            retval = SystemP_FAILURE;
        }
    }

    /* Verify no error interrupts latched */
    if(SystemP_SUCCESS == retval)
    {
        FLC_readIRQStatus(region, &raw);
        if(((raw & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_RDERR_MASK) != 0U) ||
           ((raw & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_WRERR_MASK) != 0U))
        {
            DebugP_logError("Error IRQ latched during zero-length transfer\r\n");
            retval = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Back-to-back FLC transfer stress test.
 *
 * Test Category: Stress
 *
 * Repeatedly reconfigures and starts transfers in quick succession to ensure
 * the driver and hardware remain stable across rapid reconfiguration/use
 * cycles and that no data corruption or errors occur.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput All cycles complete with correct data and no errors.
 */
void *TestOptiflash_flcBackToBackTransfers(void *args)
{
    (void)args;
    int32_t retval = SystemP_SUCCESS;
    FLC_RegionInfo *region = &gFLCRegionConfig[0];
    const uint32_t doneMask = (1U << (uint32_t)region->regionId);
    const uint32_t cycles = 5U;
    uint32_t status = 0U;
    uint32_t attempts = 0U;
    uint32_t len;
    uint32_t rdErr = 0U, wrErr = 0U;
    const uint32_t maxAttempts = 400U; /* allow more time across cycles */

    /* Start from a clean state */
    TestOptiflash_resetFlc(region);

    /* Ensure RL2 cache is disabled so FLC writes are observed deterministically */
    RL2_disable(&gRL2Config[0]);

    for(uint32_t c = 0U; (SystemP_SUCCESS == retval) && (c < cycles); c++)
    {
        /* Ensure FLC is clean before each reconfiguration */
        TestOptiflash_resetFlc(region);

        /* Alternate length: full vs half to exercise reconfiguration path */
        len = (c % 2U == 0U) ? TRANSFERSIZE : (TRANSFERSIZE / 2U);

        /* Prime destination with a known pattern beyond len to detect overflow */
        memset(destBuffer, TEST_OPTIFLASH_FILL_PATTERN_AA, TRANSFERSIZE);
        CacheP_wbInv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);

        /* Configure region for current cycle */
        region->sourceStartAddress      = (uint32_t)sourceBuffer;
        region->sourceEndAddress        = (uint32_t)sourceBuffer + len;
        region->destinationStartAddress = (uint32_t)destBuffer;

        if(FLC_API_STS_SUCCESS != FLC_configureRegion(region))
        {
            DebugP_logError("FLC configure failed in back-to-back cycle\r\n");
            retval = SystemP_FAILURE;
            break;
        }
        if(FLC_API_STS_SUCCESS != FLC_startRegion(region))
        {
            DebugP_logError("FLC start failed in back-to-back cycle\r\n");
            retval = SystemP_FAILURE;
            break;
        }

        /* Wait for completion */
        do {
            FLC_isRegionDone(region, &status);
            if((status & doneMask) == 0U)
            {
                ClockP_usleep(1000U);
                attempts++;
            }
        } while(((status & doneMask) == 0U) && (attempts < maxAttempts));

        if((status & doneMask) == 0U)
        {
            DebugP_logError("FLC did not complete in back-to-back cycle\r\n");
            retval = SystemP_FAILURE;
            break;
        }

        /* Give hardware a moment to drain writes before cache ops */
        ClockP_usleep(1000U);

        /* Verify no errors latched */
        FLC_wasReadError(region, &rdErr);
        FLC_wasWriteError(region, &wrErr);
        if((rdErr != 0U) || (wrErr != 0U))
        {
            DebugP_logError("Unexpected FLC error in back-to-back cycle\r\n");
            retval = SystemP_FAILURE;
            break;
        }

        /* Validate data integrity for the configured length */
        /* Invalidate source and entire destination to avoid partial-line staleness */
        CacheP_inv(sourceBuffer, len, CacheP_TYPE_ALL);
        CacheP_inv(destBuffer, TRANSFERSIZE, CacheP_TYPE_ALL);
        if(0 != memcmp(sourceBuffer, destBuffer, len))
        {
            DebugP_logError("Data mismatch in back-to-back cycle\r\n");
            retval = SystemP_FAILURE;
            break;
        }

        /* Ensure no writes occurred beyond len in this cycle */
        for(uint32_t i = len; i < TRANSFERSIZE; i++)
        {
            if(destBuffer[i] != (uint8_t)TEST_OPTIFLASH_FILL_PATTERN_AA)
            {
                DebugP_logError("Destination modified beyond expected length in back-to-back cycle\r\n");
                retval = SystemP_FAILURE;
                break;
            }
        }

        /* Small delay to allow hardware to fully settle before next cycle */
        if(SystemP_SUCCESS == retval)
        {
            ClockP_usleep(1000U);
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Disable RL2 while CPU is actively accessing cached region.
 *
 * Test Category: Stress
 *
 * Fills an RL2-cached region with a known pattern, continuously reads it
 * for multiple iterations, disables RL2 halfway through and continues reads
 * to verify no crash or data corruption occurs when RL2 is turned off during
 * active access.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput No data corruption detected before or after disabling RL2.
 */
void *TestOptiflash_rl2DisableDuringActiveAccess(void *args)
{
    RL2_API_STS_t retval;
    uint32_t i;
    int errors = 0;

    /* Use RL2 and FLC config from generated structures */
    RL2_Params rl2Params = gRL2Config[0];
    uint32_t *testRegion = (uint32_t *)gFLCRegionConfig[0].destinationStartAddress;
    uint32_t regionSize = gFLCRegionConfig[0].sourceEndAddress - gFLCRegionConfig[0].sourceStartAddress;
    uint32_t regionWords = regionSize / sizeof(uint32_t);
    uint32_t expected = TEST_OPTIFLASH_RL2_REGION_FILL_PATTERN;
    const uint32_t readIterations = regionWords * 4; /* 4x region size for stress test */

    /* Initialize and enable RL2 cache */
    retval = RL2_initparams(&rl2Params);
    TEST_ASSERT_EQUAL_INT32(RL2_API_STS_SUCCESS, retval);

    rl2Params.baseAddress = gRL2Config[0].baseAddress;
    rl2Params.cacheSize = gRL2Config[0].cacheSize;

    retval = RL2_configure(&rl2Params);
    TEST_ASSERT_EQUAL_INT32(RL2_API_STS_SUCCESS, retval);

    retval = RL2_enable(&rl2Params);
    TEST_ASSERT_EQUAL_INT32(RL2_API_STS_SUCCESS, retval);

    /* Fill region with known pattern */
    for (i = 0; i < regionWords; i++)
    {
        testRegion[i] = expected;
    }

    /* Flush cache to ensure data is written to memory */
    CacheP_wbInv((void *)testRegion, regionWords * sizeof(uint32_t), CacheP_TYPE_ALL);

    /* Continuous read loop, disable RL2 mid-way, continue reading */
    for (i = 0; i < readIterations; i++)
    {
        volatile uint32_t val = testRegion[i % regionWords];

        if (val != expected)
        {
            errors++;
            DebugP_logError("Data corruption detected at iteration %d: expected 0x%08X, got 0x%08X\r\n",
                       i, expected, val);
        }

        /* Disable RL2 cache mid-way through reads */
        if (i == (readIterations / 2))
        {
            retval = RL2_disable(&rl2Params);
            TEST_ASSERT_EQUAL_INT32(RL2_API_STS_SUCCESS, retval);
        }
    }

    /* Verify no data corruption occurred */
    TEST_ASSERT_EQUAL_INT32(0, errors);
    return NULL;
}

/**
 * \brief Validate FLC APIs return error for NULL pointer inputs.
 *
 * Test Category: Negative
 *
 * Calls multiple FLC APIs with NULL pointers (for region or status) and
 * verifies the driver returns `FLC_API_STS_ERROR_NULL_PTR` for each case.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput All NULL-pointer API calls return ERROR_NULL_PTR.
 */
void *TestOptiflash_flcNullPointerHandling(void *args)
{
    (void)args;
    int32_t retval = SystemP_SUCCESS;
    FLC_API_STS_t flcStatus;
    uint32_t dummyStatus;
    FLC_RegionInfo validRegion = gFLCRegionConfig[0];

    /* Test FLC_configureRegion with NULL */
    flcStatus = FLC_configureRegion(NULL);
    if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
    {
        DebugP_logError("FLC_configureRegion(NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
        retval = SystemP_FAILURE;
    }

    /* Test FLC_startRegion with NULL */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_startRegion(NULL);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_startRegion(NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_isRegionDone with NULL region */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_isRegionDone(NULL, &dummyStatus);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_isRegionDone(NULL, &status) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_isRegionDone with NULL status */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_isRegionDone(&validRegion, NULL);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_isRegionDone(&region, NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_wasReadError with NULL region */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_wasReadError(NULL, &dummyStatus);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_wasReadError(NULL, &status) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_wasReadError with NULL status */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_wasReadError(&validRegion, NULL);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_wasReadError(&region, NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_enableInterrupt with NULL */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_enableInterrupt(NULL, FLC_INTERRUPT_DONE);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_enableInterrupt(NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_disable with NULL */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_disable(NULL);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_disable(NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_wasWriteError with NULL region */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_wasWriteError(NULL, &dummyStatus);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_wasWriteError(NULL, &status) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_wasWriteError with NULL status */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_wasWriteError(&validRegion, NULL);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_wasWriteError(&region, NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_clearWriteError with NULL */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_clearWriteError(NULL);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_clearWriteError(NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_clearReadError with NULL */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_clearReadError(NULL);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_clearReadError(NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_readIRQMask with NULL region */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_readIRQMask(NULL, &dummyStatus);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_readIRQMask(NULL, &status) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_readIRQStatus with NULL region */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_readIRQStatus(NULL, &dummyStatus);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_readIRQStatus(NULL, &status) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_clearInterrupt with NULL */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_clearInterrupt(NULL, FLC_INTERRUPT_DONE);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_clearInterrupt(NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    /* Test FLC_disableInterrupt with NULL */
    if(SystemP_SUCCESS == retval)
    {
        flcStatus = FLC_disableInterrupt(NULL, FLC_INTERRUPT_DONE);
        if(flcStatus != FLC_API_STS_ERROR_NULL_PTR)
        {
            DebugP_logError("FLC_disableInterrupt(NULL) failed: expected ERROR_NULL_PTR, got %d\r\n", flcStatus);
            retval = SystemP_FAILURE;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/**
 * \brief Validate FLC configuration rejects illegal region IDs.
 *
 * Test Category: Negative
 *
 * Attempts to configure a region with `regionId == FLC_MAX_REGION` and with
 * regionId > FLC_MAX_REGION and expects the API to return
 * `FLC_API_STS_ERROR_ILLEGAL_REGION_ID`.
 * \param args Pointer to test arguments (unused).
 * \return NULL
 * \expectedOutput API returns ERROR_ILLEGAL_REGION_ID for invalid region IDs.
 */
void *TestOptiflash_flcIllegalRegionId(void *args)
{
    (void)args;
    int32_t retval = SystemP_SUCCESS;
    FLC_API_STS_t flcStatus;
    FLC_RegionInfo badRegion;

    /* Copy valid region and modify regionId to invalid value */
    badRegion = gFLCRegionConfig[0];
    badRegion.regionId = FLC_MAX_REGION; /* Invalid: equal to max */

    flcStatus = FLC_configureRegion(&badRegion);
    if(flcStatus != FLC_API_STS_ERROR_ILLEGAL_REGION_ID)
    {
        DebugP_logError("FLC_configureRegion with regionId=%u failed: expected ERROR_ILLEGAL_REGION_ID, got %d\r\n",
                       FLC_MAX_REGION, flcStatus);
        retval = SystemP_FAILURE;
    }

    /* Test with regionId > FLC_MAX_REGION */
    if(SystemP_SUCCESS == retval)
    {
        badRegion.regionId = FLC_MAX_REGION + 10U;
        flcStatus = FLC_configureRegion(&badRegion);
        if(flcStatus != FLC_API_STS_ERROR_ILLEGAL_REGION_ID)
        {
            DebugP_logError("FLC_configureRegion with regionId=%u failed: expected ERROR_ILLEGAL_REGION_ID, got %d\r\n",
                           FLC_MAX_REGION + 10U, flcStatus);
            retval = SystemP_FAILURE;
        }
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retval);
    return NULL;
}

/* ========================================================================== */
/*                     API ISR Function Definitions                           */
/* ========================================================================== */

/* HWI Function */
static void test_optiflash_hwiFxn(void *args)
{
    uint32_t isrRegVal = 0U;
    
    FLC_readIRQStatus(&gFLCRegionConfig[0], &isrRegVal);

    if((isrRegVal & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MASK) != 0U)
    {
        test_optiflash_Callback();
        FLC_clearInterrupt(&gFLCRegionConfig[0], FLC_INTERRUPT_DONE);
        FLC_readIRQMask(&gFLCRegionConfig[0], &isrRegVal);
    }

    return;
}

static void TestOptiflash_flcDoneIsr(void *args)
{
    uint32_t isrRegVal = 0U;
    uint32_t masked;

    FLC_readIRQStatus(&gFLCRegionConfig[0], &isrRegVal);

    if((isrRegVal & CSL_RL2_OF_CBA4_IRQSTATUS_RAW_FLC_DON_MASK) != 0U)
    {
        /* Capture masked status before clearing and signal completion */
        masked = 0U;
        FLC_readIRQMask(&gFLCRegionConfig[0], &masked);
        TestOptiflash_LastMaskedStatus = masked;
        test_optiflash_Callback();
        FLC_clearInterrupt(&gFLCRegionConfig[0], FLC_INTERRUPT_DONE);
    }

    return;
}

void test_optiflash_Callback(void)
{
    /* Post Semaphore */
    SemaphoreP_post(&gSemObj);
}


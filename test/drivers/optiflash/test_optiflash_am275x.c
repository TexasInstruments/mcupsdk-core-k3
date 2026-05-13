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

/* Destination buffer fill patterns */
#define TEST_OPTIFLASH_FILL_PATTERN_AA              (0xAAU)
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


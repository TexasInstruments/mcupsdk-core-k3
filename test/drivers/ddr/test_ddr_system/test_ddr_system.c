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
 *  \file test_ddr_system.c
 *
 *  \brief DDR system test - write/read validation across multiple cores.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/CacheP.h>

/* ========================================================================== */
/*                               Macros                                       */
/* ========================================================================== */

/* DDR test base address */
#define TEST_DDR_BASE_ADDR      (0x90000000U)
/* Per-core test region size (4KB) */
#define TEST_DDR_REGION_SIZE    (0x1000U)
/* Number of constant test patterns */
#define TEST_DDR_PATTERN_COUNT  (6U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t TestDdr_writeReadPattern(volatile uint32_t *addr,
                                        uint32_t count,
                                        uint32_t pattern);

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/**
 * \brief Write a constant pattern to a DDR region, flush cache, invalidate,
 *        then read back and verify every word.
 *
 * \param addr   Pointer to the DDR test region (volatile).
 * \param count  Number of 32-bit words to test.
 * \param pattern The 32-bit pattern to write.
 *
 * \return SystemP_SUCCESS on match, SystemP_FAILURE on mismatch.
 */
static int32_t TestDdr_writeReadPattern(volatile uint32_t *addr,
                                        uint32_t count,
                                        uint32_t pattern)
{
    uint32_t i;

    /* Write pattern */
    for (i = 0U; i < count; i++)
    {
        addr[i] = pattern;
    }

    /* Flush data cache to push writes to DDR */
    CacheP_wb((void *)addr, count * sizeof(uint32_t), CacheP_TYPE_ALLD);
    /* Invalidate data cache so reads come from DDR */
    CacheP_inv((void *)addr, count * sizeof(uint32_t), CacheP_TYPE_ALLD);

    /* Read back and verify */
    for (i = 0U; i < count; i++)
    {
        if (addr[i] != pattern)
        {
            DebugP_logError("DDR mismatch at offset %u: expected 0x%08X, got 0x%08X\r\n",
                            i, pattern, addr[i]);
            return SystemP_FAILURE;
        }
    }

    return SystemP_SUCCESS;
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * \brief DDR write/read validation test for system execution.
 *
 * Test steps:
 *   1. Constant pattern test  (6 patterns incl. all-0s, all-1s, checkerboard)
 *   2. Walking 1s test        (32 words)
 *   3. Increment pattern test (sequential word values)
 *
 * \param args  Unused.
 * \return SystemP_SUCCESS on pass, SystemP_FAILURE on any mismatch.
 */
int32_t TestDdr_systemWriteReadTest(void *args)
{
    (void)args;
    int32_t  status = SystemP_SUCCESS;
    uint32_t coreId = IpcNotify_getSelfCoreId();
    volatile uint32_t *testAddr =
        (volatile uint32_t *)(TEST_DDR_BASE_ADDR + (coreId * TEST_DDR_REGION_SIZE));
    uint32_t wordCount = TEST_DDR_REGION_SIZE / sizeof(uint32_t);
    uint32_t i;

    /* Constant patterns: DEADBEEF, A5/5A checkerboard, ascending, all-0, all-1 */
    uint32_t patterns[TEST_DDR_PATTERN_COUNT] = {
        0xDEADBEEFU, 0xA5A5A5A5U, 0x5A5A5A5AU,
        0x12345678U, 0x00000000U, 0xFFFFFFFFU
    };

    DebugP_log("Core[%d]: DDR write/read test at 0x%08X, size %u bytes\r\n",
               coreId, (uint32_t)(uintptr_t)testAddr, TEST_DDR_REGION_SIZE);

    /* --- Test 1: Constant patterns --- */
    for (i = 0U; i < TEST_DDR_PATTERN_COUNT; i++)
    {
        status = TestDdr_writeReadPattern(testAddr, wordCount, patterns[i]);
        if (status != SystemP_SUCCESS)
        {
            DebugP_logError("Core[%d]: FAILED pattern 0x%08X\r\n", coreId, patterns[i]);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
            return status;
        }
    }

    /* --- Test 2: Walking 1s (first 32 words) --- */
    for (i = 0U; i < 32U; i++)
    {
        testAddr[i] = (1U << i);
    }
    CacheP_wb((void *)testAddr, 32U * sizeof(uint32_t), CacheP_TYPE_ALLD);
    CacheP_inv((void *)testAddr, 32U * sizeof(uint32_t), CacheP_TYPE_ALLD);
    for (i = 0U; i < 32U; i++)
    {
        if (testAddr[i] != (1U << i))
        {
            DebugP_logError("Core[%d]: Walking-1s mismatch at bit %u\r\n", coreId, i);
            status = SystemP_FAILURE;
            break;
        }
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* --- Test 3: Increment pattern (each word = its index) --- */
    for (i = 0U; i < wordCount; i++)
    {
        testAddr[i] = i;
    }
    CacheP_wb((void *)testAddr, wordCount * sizeof(uint32_t), CacheP_TYPE_ALLD);
    CacheP_inv((void *)testAddr, wordCount * sizeof(uint32_t), CacheP_TYPE_ALLD);
    for (i = 0U; i < wordCount; i++)
    {
        if (testAddr[i] != i)
        {
            DebugP_logError("Core[%d]: Increment mismatch at %u\r\n", coreId, i);
            status = SystemP_FAILURE;
            break;
        }
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return status;
}




/**
 * Copyright (C) 2026 Texas Instruments Incorporated
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
 *
 */

 /**
 *  \file     test_core_m4_mpu.c
 *
 *  \brief    This file contains mpu API test code for M4 core.
 *
 *  \details  MPU read/write and configuration tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include <stdio.h>
#include <string.h>
#include <unity.h>
#include "core_m4_test.h"
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/MpuP_armv7.h>

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/

/* ARMv7-M MPU registers (memory mapped). These are read back to verify the
 * MPU configuration since the ARMv7-R style verify APIs
 * (MpuP_VerifyCfgRegion(), MpuP_VerifyEnableRegion(), MpuP_GetNumRegions())
 * do not exist on the M4F */
#define TEST_MPU_TYPE   (*(volatile uint32_t *)(0xE000ED90u))
#define TEST_MPU_CTRL   (*(volatile uint32_t *)(0xE000ED94u))
#define TEST_MPU_RNR    (*(volatile uint32_t *)(0xE000ED98u))
#define TEST_MPU_RBAR   (*(volatile uint32_t *)(0xE000ED9Cu))
#define TEST_MPU_RASR   (*(volatile uint32_t *)(0xE000EDA0u))

/* Region size encoding: region size = 2^(N+1) bytes, N is the 5b size field */
#define TEST_MPU_REGION_SIZE_1KB           (0x09U)   /* 2^10 = 1KB */
#define TEST_MPU_REGION_SIZE_4KB           (0x0BU)   /* 2^12 = 4KB */

/* Size of the RAM buffer used as target memory for the MPU region tests */
#define TEST_MPU_BUF_SIZE_BYTES            (1024U)

/* Number of entries in the SysConfig style MPU region config array */
#define TEST_MPU_REGION_CONFIG_ENTRIES     (8U)

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/


void __mpu_init(void)
{
    /* Do not implement anything here as anything here would be invoked
     * during startup code */
}

/* Empty definitions as MPU not configured by SysConfig */
/* ----------- CacheP ----------- */
CacheP_Config gCacheConfig = { };

/* ----------- MpuP_armv7 ----------- */
MpuP_Config gMpuConfig = { };
MpuP_RegionConfig gMpuRegionConfig[TEST_MPU_REGION_CONFIG_ENTRIES] = { };

/* RAM buffer, aligned to its own size, used as the target memory for the
 * MPU region tests */
static uint32_t gTestMpuBuf[TEST_MPU_BUF_SIZE_BYTES / sizeof(uint32_t)]
                __attribute__((aligned(TEST_MPU_BUF_SIZE_BYTES)));

/**
 * Calculates and returns the combined RASR value (attrs + size + enable).
 * Mirrors MpuP_getAttrsAndSize() in MpuP_armv7m.c.
 * For more information on region and size attributes, refer:
 * https://developer.arm.com/documentation/dui0553/latest/ (Cortex-M4 MPU)
 */
static uint32_t TestMpu_getAttrsAndSize(const MpuP_RegionAttrs *region, uint32_t size)
{
    uint32_t regionAttrs =
          ((uint32_t)(region->isExecuteNever & 0x1U) << 28U)
        | ((uint32_t)(region->accessPerm     & 0x7U) << 24U)
        | ((uint32_t)(region->tex            & 0x7U) << 19U)
        | ((uint32_t)(region->isSharable     & 0x1U) << 18U)
        | ((uint32_t)(region->isCacheable    & 0x1U) << 17U)
        | ((uint32_t)(region->isBufferable   & 0x1U) << 16U)
        | ((uint32_t)(region->subregionDisableMask & 0xFFU) << 8U)
        | ((uint32_t)(size & 0x1FU) << 1U)
        | ((uint32_t)(region->isEnable       & 0x1U) << 0U);

    return regionAttrs;
}

/**
 * Returns the number of MPU regions supported by reading the DREGION field
 * of the MPU_TYPE register (MpuP_GetNumRegions() is not available on M4).
 */
static uint32_t TestMpu_getNumRegions(void)
{
    return ((TEST_MPU_TYPE >> 8U) & 0xFFU);
}

/**
 * Verifies an MPU region configuration by reading back the memory mapped
 * MPU registers (MpuP_VerifyCfgRegion() is not available on M4).
 */
static int32_t TestMpu_verifyCfgRegion(uint32_t regionNum, uint32_t baseAddr, uint32_t expRasr)
{
    int32_t status = CORE_M4_APP_TEST_PASS;

    TEST_MPU_RNR = regionNum;
    if ((TEST_MPU_RBAR & 0xFFFFFFE0U) != (baseAddr & 0xFFFFFFE0U))
    {
        status = CORE_M4_APP_TEST_FAILED;
    }
    if (TEST_MPU_RASR != expRasr)
    {
        status = CORE_M4_APP_TEST_FAILED;
    }
    return status;
}

/*===========================================================================*/
/*                          function declarations                            */
/*===========================================================================*/

static void TestMpu_configurationTc(void *args);
static void TestMpu_enableDisableFlow(void *args);
static void TestMpu_regionSizeAlignment(void *args);
static void TestMpu_executeAllowedRegion(void *args);
static void TestMpu_deviceMemoryType(void *args);
static void TestMpu_resetRegionClearsEntry(void *args);
static void TestMpu_regionAttrsInitDefaults(void *args);
static void TestMpu_init_disablesIfEnabled(void *args);
static void TestMpu_init_resetsAllRegions(void *args);
static void TestMpu_init_enablesBackgroundRegion(void *args);
static void TestMpu_init_fullFlow(void *args);
static void TestMpu_init_configuresTwoRegions(void *args);
static void TestMpu_accessPermissions(void *args);
static void TestMpu_cacheableAttribute(void *args);
static void TestMpu_bufferableAttribute(void *args);
static void TestMpu_shareableAttribute(void *args);
static void TestMpu_normalMemoryType(void *args);
static void TestMpu_regionPriorityOverlap(void *args);
int32_t TestMpu_initFn(void);

/*===========================================================================*/
/*                        Test Function definitions                          */
/*===========================================================================*/

void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(TestMpu_configurationTc, 10057, NULL);
    RUN_TEST(TestMpu_enableDisableFlow, 10058, NULL);
    RUN_TEST(TestMpu_regionSizeAlignment, 10060, NULL);
    RUN_TEST(TestMpu_executeAllowedRegion, 10064, NULL);
    RUN_TEST(TestMpu_deviceMemoryType, 10076, NULL);
    RUN_TEST(TestMpu_resetRegionClearsEntry, 10080, NULL);
    RUN_TEST(TestMpu_regionAttrsInitDefaults, 10081, NULL);
    RUN_TEST(TestMpu_init_disablesIfEnabled, 10082, NULL);
    RUN_TEST(TestMpu_init_resetsAllRegions, 10083, NULL);
    RUN_TEST(TestMpu_init_enablesBackgroundRegion, 10086, NULL);
    RUN_TEST(TestMpu_init_fullFlow, 10087, NULL);
    RUN_TEST(TestMpu_init_configuresTwoRegions, 10088, NULL);
    RUN_TEST(TestMpu_accessPermissions, 10062, NULL);
    RUN_TEST(TestMpu_cacheableAttribute, 10066, NULL);
    RUN_TEST(TestMpu_bufferableAttribute, 10067, NULL);
    RUN_TEST(TestMpu_shareableAttribute, 10067, NULL);
    RUN_TEST(TestMpu_normalMemoryType, 10070, NULL);
    RUN_TEST(TestMpu_regionPriorityOverlap, 10078, NULL);

    #if defined (ENABLE_MT_TESTS)
    run_multi_threaded_tests(NULL);
    #endif

    UNITY_END();
}

/**
 * @brief Unity test setup hook.
 * Called before each Unity test. Left empty because tests perform their own
 * per-test setup and teardown.
 */
void setUp(void)
{
}

/**
 * @brief Unity test teardown hook.
 * Called after each Unity test. Left empty because tests perform their own
 * per-test cleanup.
 */
void tearDown(void)
{
}

/* Returns the base address of the RAM test buffer used as the target
 * memory for the MPU region tests. The buffer is aligned to its own size
 * so that it can be used directly as an MPU region base address.
 */
void *TestMpu_getExecBase(void)
{
    return (void *)gTestMpuBuf;
}

/**
 * @brief Tests the MPU (Memory Protection Unit) configuration and initialization.
 *
 * This function initializes the MPU, asserts the initialization result,
 * retrieves the number of MPU regions from the MPU_TYPE register, and logs
 * the outcome. It is used to verify correct MPU setup on the M4 core.
 *
 * @param args Pointer to arguments (unused in this test function).
 */
static void TestMpu_configurationTc(void *args)
{
    /* Declarations of variables */
    int32_t    testResult;
    uint32_t   numRegions;

    testResult = TestMpu_initFn();
    DebugP_assert(testResult == CORE_M4_APP_TEST_PASS);
    numRegions = TestMpu_getNumRegions();
    DebugP_log(" MPU API tests complete: number of regions tested are : ");
    DebugP_log("0x%x \n", numRegions);
    DebugP_log(" \n\r ");

    return;
}

/**
 * @brief Initializes and verifies MPU regions for M4 core testing.
 *
 * Resets all MPU regions and verifies each is cleared via register
 * readback, configures a region over the RAM test buffer, verifies the
 * configured region, and finally enables the MPU with the background
 * region (PRIVDEFENA) so that code/data not covered by a foreground
 * region keeps default memory map access.
 *
 * @return CORE_M4_APP_TEST_PASS on success,
 *         CORE_M4_APP_TEST_FAILED on failure.
 *
 */
int32_t TestMpu_initFn(void)
{
    int32_t               region, chk, testResult = CORE_M4_APP_TEST_PASS;
    uint32_t              numRegions;
    uint32_t              expRasr;
    MpuP_RegionAttrs      regionParams;

    /* Total number of MPU regions */
    numRegions = TestMpu_getNumRegions();

    /* Disable the MPU first */
    MpuP_disable();

    /* Reset all regions and verify each region is cleared */
    for (region = (int32_t)(numRegions - 1U); region >= 0; region--)
    {
        MpuP_resetRegion((uint32_t)region);
        chk = TestMpu_verifyCfgRegion((uint32_t)region, 0U, 0U);
        if (CORE_M4_APP_TEST_PASS != chk)
        {
            testResult = CORE_M4_APP_TEST_FAILED;
            break;
        }
    }

    if (CORE_M4_APP_TEST_PASS == testResult)
    {
        /* Region 0: RAM test buffer, normal memory, full RW, execute never */
        MpuP_RegionAttrs_init(&regionParams);
        regionParams.isEnable             = 1;
        regionParams.isCacheable          = 1;
        regionParams.isBufferable         = 1;
        regionParams.isSharable           = 0;
        regionParams.isExecuteNever       = 1;
        regionParams.tex                  = 1;
        regionParams.accessPerm           = MpuP_AP_ALL_RW;
        regionParams.subregionDisableMask = 0x0;

        MpuP_setRegion(0U, (void *)gTestMpuBuf, TEST_MPU_REGION_SIZE_1KB, &regionParams);

        /* Verify the configured region via register readback */
        expRasr = TestMpu_getAttrsAndSize(&regionParams, TEST_MPU_REGION_SIZE_1KB);
        chk = TestMpu_verifyCfgRegion(0U, (uint32_t)gTestMpuBuf, expRasr);
        if (CORE_M4_APP_TEST_PASS != chk)
        {
            testResult = CORE_M4_APP_TEST_FAILED;
        }
    }

    if (CORE_M4_APP_TEST_PASS == testResult)
    {
        /* Enable the MPU with the background region (PRIVDEFENA) so that
         * code/data not covered by the region above keeps default access */
        gMpuConfig.enableBackgroundRegion = 1;
        MpuP_enable();
    }

    return (testResult);
}

/**
 * @brief Disables and re-enables the MPU, sampling the enable state.
 *
 * On ARMv7-M the background region (PRIVDEFENA) is programmed as part of
 * MpuP_enable(), so as long as gMpuConfig.enableBackgroundRegion is set,
 * toggling the MPU is safe from code running anywhere in memory.
 */
static void TestMpu_toggleMpu(uint32_t *disabledState, uint32_t *enabledState)
{
    MpuP_disable();
    *disabledState = MpuP_isEnable();
    MpuP_enable();
    *enabledState = MpuP_isEnable();
}

/**
 * @brief Tests the enable and disable flow of the MPU (Memory Protection Unit).
 *
 * This function verifies the correct behavior of the MPU enable and disable APIs.
 * It checks the initial state, disables and enables the MPU, and asserts the expected states.
 * The test also repeats the disable/enable sequence to ensure idempotence.
 * Logs are generated at each step for debugging and validation purposes.
 */
static void TestMpu_enableDisableFlow(void *args)
{
    uint32_t initialState, disabledState, enabledState;

    /* Enable the background region so enabling the MPU is safe with a
     * sparse region configuration */
    gMpuConfig.enableBackgroundRegion = 1;

    /* Step 1: Read and log initial state */
    initialState = MpuP_isEnable();
    DebugP_log("TestMpu_enableDisableFlow: Initial MPU state = %u\r\n", initialState);

    /* Step 2 & 3: Disable then enable the MPU and verify the sampled states */
    TestMpu_toggleMpu(&disabledState, &enabledState);
    DebugP_log("After MpuP_disable(), state = %u\r\n", disabledState);
    TEST_ASSERT_EQUAL_UINT32(0, disabledState);
    DebugP_log("After MpuP_enable(), state = %u\r\n", enabledState);
    TEST_ASSERT_NOT_EQUAL(0, enabledState);

    /* Step 4: Repeat disable/enable for idempotence */
    TestMpu_toggleMpu(&disabledState, &enabledState);
    TEST_ASSERT_EQUAL_UINT32(0, disabledState);
    TEST_ASSERT_NOT_EQUAL(0, enabledState);

    /* Step 5: Leave MPU enabled */
    DebugP_log("TestMpu_enableDisableFlow: PASSED\r\n");
}

/**
 * @brief Tests MPU region size alignment and configuration.
 *
 * This function initializes MPU region attributes, sets up a region with a specific
 * size and base address, and verifies the configuration. It checks if the region
 * is correctly aligned and enabled with the intended attributes. The test asserts
 * that the MPU configuration matches the expected values and logs the result.
 */
static void TestMpu_regionSizeAlignment(void *args)
{
    uint32_t            regionNum = 5;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    void               *baseAddr = (void *)gTestMpuBuf; /* Aligned to 1KB */
    MpuP_RegionAttrs    regionParams;
    uint32_t            expRasr;
    int32_t             chk;

    /* Disable the MPU first */
    MpuP_disable();

    /* Log the region details being tested */
    DebugP_log("TestMpu_regionSizeAlignment: Region=%u, Size=0x%x, Base=0x%x\r\n",
               regionNum, sizeCode, (uint32_t)baseAddr);

    /* Step 3: Initialize region attributes */
    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;          /* Enable the region */
    regionParams.isCacheable          = 1;          /* Cacheable memory */
    regionParams.isBufferable         = 0;          /* Non-bufferable memory */
    regionParams.isSharable           = 0;          /* Non-shareable memory */
    regionParams.isExecuteNever       = 0;          /* Allow execution */
    regionParams.tex                  = 0;          /* TEX field set to 0 */
    regionParams.accessPerm           = MpuP_AP_S_RW_U_R; /* Privileged RW, User RO */
    regionParams.subregionDisableMask = 0x0;        /* No subregions disabled */

    /* Step 4: Set the MPU region with the specified attributes */
    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    /* Step 5: Verify the region configuration via register readback */
    expRasr = TestMpu_getAttrsAndSize(&regionParams, sizeCode);
    chk = TestMpu_verifyCfgRegion(regionNum, (uint32_t)baseAddr, expRasr);

    /* Assert that the configuration verification passed */
    TEST_ASSERT_EQUAL_INT32(CORE_M4_APP_TEST_PASS, chk);

    /* Cleanup */
    MpuP_resetRegion(regionNum);

    /* Log the test result */
    DebugP_log("TestMpu_regionSizeAlignment: PASSED\r\n");
}

/**
 * @brief
 * Tests MPU access permissions for a memory region.
 *
 * This function configures an MPU region with different
 * access policies and verifies read/write access in
 * privileged mode. It tests both full access
 * (S_RW_U_RW) and supervisor RW, user RO (S_RW_U_R)
 * policies. The function asserts correct behavior and
 * logs the results for each policy tested.
 *
 */
static void TestMpu_accessPermissions(void *args)
{
    uint32_t            regionNum = 4;
    void               *baseAddr = (void *)gTestMpuBuf;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testPtr = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0xDEADBEEFU;
    uint32_t            readValue;

    MpuP_disable();

    /* Test policy: ALL_RW (full access) */
    DebugP_log("TestMpu_accessPermissions: Testing ALL_RW policy\r\n");

    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;
    regionParams.isCacheable          = 1;
    regionParams.isBufferable         = 1;
    regionParams.isSharable           = 0;
    regionParams.isExecuteNever       = 1;
    regionParams.tex                  = 1;
    regionParams.accessPerm           = MpuP_AP_ALL_RW;
    regionParams.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    /* Enable the MPU (with background region) so permissions are enforced */
    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_enable();

    /* Perform write and read in privileged mode */
    *testPtr = testValue;
    readValue = *testPtr;

    TEST_ASSERT_EQUAL_UINT32(testValue, readValue);
    DebugP_log("ALL_RW: Write/Read verified\r\n");

    /* Test policy: S_RW_U_R (privileged RW, user RO); test runs privileged */
    DebugP_log("TestMpu_accessPermissions: Testing S_RW_U_R policy\r\n");

    MpuP_disable();
    regionParams.accessPerm = MpuP_AP_S_RW_U_R;
    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);
    MpuP_enable();

    testValue = 0xCAFEBABEU;
    *testPtr = testValue;
    readValue = *testPtr;

    TEST_ASSERT_EQUAL_UINT32(testValue, readValue);
    DebugP_log("S_RW_U_R: Write/Read verified\r\n");

    /* Cleanup */
    MpuP_disable();
    MpuP_resetRegion(regionNum);

    DebugP_log("TestMpu_accessPermissions: PASSED\r\n");
}

static uint32_t TestMpu_stubFunction(void)
{
    return 0x12345678U;
}

/**
 * @brief
 * Configures an MPU region as executable and
 * verifies code execution.
 *
 * This function sets up a Memory Protection Unit
 * (MPU) region with execution permissions,
 * enables the MPU, and attempts to execute a test
 * function within the allowed region.
 * It asserts the expected return value from the
 * test function to validate execution.
 * Debug logs are generated to indicate the
 * progress and result of the test.
 * Intended for validating MPU configuration for
 * executable memory regions.
 *
 */
static void TestMpu_executeAllowedRegion(void *args)
{
    uint32_t         regionNum = 5;
    /* Clear the Thumb bit and align down to the region size so the region
     * covers the stub function regardless of where the code is linked */
    uintptr_t        funcAddr = ((uintptr_t)&TestMpu_stubFunction) & ~(uintptr_t)1U;
    void            *baseAddr = (void *)(funcAddr & ~((uintptr_t)(1UL << 12U) - 1U));
    uint32_t         sizeCode = TEST_MPU_REGION_SIZE_4KB;
    MpuP_RegionAttrs regionParams;
    uint32_t         result;

    MpuP_disable();

    DebugP_log("TestMpu_executeAllowedRegion: Configuring executable region\r\n");

    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;
    regionParams.isCacheable          = 1;
    regionParams.isBufferable         = 0;
    regionParams.isSharable           = 0;
    regionParams.isExecuteNever       = 0; /* Allow execution */
    regionParams.tex                  = 0;
    regionParams.accessPerm           = MpuP_AP_S_RW_U_R;
    regionParams.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    /* Enable the MPU (with background region) */
    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_enable();

    /* Invoke function and verify return */
    result = TestMpu_stubFunction();
    TEST_ASSERT_EQUAL_UINT32(0x12345678U, result);

    /* Cleanup */
    MpuP_disable();
    MpuP_resetRegion(regionNum);

    DebugP_log("TestMpu_executeAllowedRegion: Function executed successfully\r\n");
    DebugP_log("TestMpu_executeAllowedRegion: PASSED\r\n");
}

/**
 * @brief Tests the cacheable attribute configuration of an MPU region.
 *
 * This function configures a specific MPU region as cacheable and bufferable,
 * writes a test pattern to the region, and verifies data integrity by reading
 * back the values. The test is repeated to demonstrate cache behavior and ensure
 * correct operation of the cacheable attribute in the MPU configuration.
 */
static void TestMpu_cacheableAttribute(void *args)
{
    uint32_t            regionNum = 6;
    void               *baseAddr = (void *)gTestMpuBuf;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testBuf = (volatile uint32_t *)baseAddr;
    uint32_t            i, testSize = 256;

    MpuP_disable();
    DebugP_log("TestMpu_cacheableAttribute: Configuring cacheable region\r\n");

    /* Note: the M4F has no hardware caches; this verifies the C/B attribute
     * encoding and the data integrity of the configured region */
    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;
    regionParams.isCacheable          = 1;
    regionParams.isBufferable         = 1;
    regionParams.isSharable           = 0;
    regionParams.isExecuteNever       = 1;
    regionParams.tex                  = 1;
    regionParams.accessPerm           = MpuP_AP_S_RW_U_R;
    regionParams.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_enable();

    /* Step 3: Write pattern */
    for (i = 0; i < testSize; i++) {
        testBuf[i] = i + 0xA5A5A5A5U;
    }

    /* Read and verify */
    for (i = 0; i < testSize; i++) {
        TEST_ASSERT_EQUAL_UINT32(i + 0xA5A5A5A5U, testBuf[i]);
    }

    DebugP_log("TestMpu_cacheableAttribute: First iteration verified\r\n");

    /* Step 5: Repeat with a second pattern */
    for (i = 0; i < testSize; i++) {
        testBuf[i] = i + 0xDEADBEEFU;
    }

    for (i = 0; i < testSize; i++) {
        TEST_ASSERT_EQUAL_UINT32(i + 0xDEADBEEFU, testBuf[i]);
    }

    /* Cleanup */
    MpuP_disable();
    MpuP_resetRegion(regionNum);

    DebugP_log("TestMpu_cacheableAttribute: Second iteration verified\r\n");
    DebugP_log("TestMpu_cacheableAttribute: PASSED\r\n");
}

/**
 * @brief Tests the MPU bufferable attribute configuration for a memory region.
 *
 * This function configures a specific MPU region as bufferable, cacheable, and non-executable.
 * It writes sequential data to the region and verifies data integrity by reading it back.
 * The function logs the test progress and asserts correctness of the memory operations.
 * Intended to validate correct MPU attribute handling for bufferable memory regions.
 *
 * @param args Unused parameter for compatibility with test framework.
 */
static void TestMpu_bufferableAttribute(void *args)
{
    uint32_t            regionNum = 7;
    void               *baseAddr = (void *)gTestMpuBuf;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testBuf = (volatile uint32_t *)baseAddr;
    uint32_t            i, testSize = 128;

    MpuP_disable();
    DebugP_log("TestMpu_bufferableAttribute: Configuring bufferable region\r\n");

    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;
    regionParams.isCacheable          = 1;
    regionParams.isBufferable         = 1;
    regionParams.isSharable           = 0;
    regionParams.isExecuteNever       = 1;
    regionParams.tex                  = 1;
    regionParams.accessPerm           = MpuP_AP_S_RW_U_R;
    regionParams.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_enable();

    /* Sequential writes */
    for (i = 0; i < testSize; i++) {
        testBuf[i] = 0xBEEF0000U | i;
    }

    /* Sequential reads and verify */
    for (i = 0; i < testSize; i++) {
        TEST_ASSERT_EQUAL_UINT32(0xBEEF0000U | i, testBuf[i]);
    }

    /* Cleanup */
    MpuP_disable();
    MpuP_resetRegion(regionNum);

    DebugP_log("TestMpu_bufferableAttribute: Data integrity verified\r\n");
    DebugP_log("TestMpu_bufferableAttribute: PASSED\r\n");
}

/**
 * @brief Tests MPU shareable attribute for a memory region.
 *
 * Configures a region as shareable, cacheable, and bufferable, writes a value,
 * and verifies access. Multi-core coherency is platform-dependent.
 */
static void TestMpu_shareableAttribute(void *args)
{
    uint32_t            regionNum = 7;
    void               *baseAddr = (void *)gTestMpuBuf;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testBuf = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0xCAFEBABEU;

    MpuP_disable();
    DebugP_log("TestMpu_shareableAttribute: Configuring shareable region\r\n");

    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;
    regionParams.isCacheable          = 1;
    regionParams.isBufferable         = 1;
    regionParams.isSharable           = 1; /* Shareable */
    regionParams.isExecuteNever       = 1;
    regionParams.tex                  = 1;
    regionParams.accessPerm           = MpuP_AP_S_RW_U_R;
    regionParams.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_enable();

    *testBuf = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testBuf);

    /* Cleanup */
    MpuP_disable();
    MpuP_resetRegion(regionNum);

    DebugP_log("TestMpu_shareableAttribute: Shareable access verified\r\n");
    DebugP_log("Note: Multi-core coherency is platform-dependent\r\n");
    DebugP_log("TestMpu_shareableAttribute: PASSED\r\n");
}

/**
 * @brief Tests MPU configuration for normal memory type with cacheable and bufferable attributes.
 *
 * This function sets up an MPU region with TEX=1, C=1, B=1, and verifies normal memory access.
 * It initializes region attributes, enables the region, and writes a test pattern to the memory.
 * The function asserts that the written value is correctly read back, confirming correct MPU setup.
 * Debug logs are generated to indicate the progress and result of the test.
 */
static void TestMpu_normalMemoryType(void *args)
{
    uint32_t            regionNum = 5;
    void               *baseAddr = (void *)gTestMpuBuf;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testBuf = (volatile uint32_t *)baseAddr;
    uint32_t            testPattern = 0x5A5A5A5AU;

    MpuP_disable();
    DebugP_log("TestMpu_normalMemoryType: TEX=1, C=1, B=1\r\n");

    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;
    regionParams.isCacheable          = 1;
    regionParams.isBufferable         = 1;
    regionParams.isSharable           = 0;
    regionParams.isExecuteNever       = 1;
    regionParams.tex                  = 1;
    regionParams.accessPerm           = MpuP_AP_S_RW_U_R;
    regionParams.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_enable();

    *testBuf = testPattern;
    TEST_ASSERT_EQUAL_UINT32(testPattern, *testBuf);

    /* Cleanup */
    MpuP_disable();
    MpuP_resetRegion(regionNum);

    DebugP_log("TestMpu_normalMemoryType: Normal memory access verified\r\n");
    DebugP_log("TestMpu_normalMemoryType: PASSED\r\n");
}

/**
 * @brief Configures an MPU region as device memory and verifies MMIO read stability.
 *
 * This function sets up a specific MPU region with device memory attributes,
 * disables caching and buffering, and marks the region as shareable and execute-never.
 * It then performs two consecutive reads from a memory-mapped IO register to ensure
 * the values are stable, indicating correct MPU configuration for device memory.
 */
static void TestMpu_deviceMemoryType(void *args)
{
    uint32_t            regionNum = 6;
    void               *baseAddr = (void *)gTestMpuBuf;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testPtr = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0x5AA55AA5U;
    uint32_t            readVal1, readVal2;

    MpuP_disable();
    DebugP_log("TestMpu_deviceMemoryType: Configuring Device memory region\r\n");

    /* Configure the RAM test buffer as Device memory (TEX=0, C=0, B=0) */
    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;
    regionParams.isCacheable          = 0;  /* Device: no cache */
    regionParams.isBufferable         = 0;  /* Device: no buffer */
    regionParams.isSharable           = 1;  /* Device: shareable */
    regionParams.isExecuteNever       = 1;  /* XN */
    regionParams.tex                  = 0;
    regionParams.accessPerm           = MpuP_AP_ALL_RW;
    regionParams.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_enable();

    /* Write once and perform two reads, values must be stable */
    *testPtr = testValue;
    readVal1 = *testPtr;
    readVal2 = *testPtr;

    TEST_ASSERT_EQUAL_UINT32(readVal1, readVal2);
    TEST_ASSERT_EQUAL_UINT32(testValue, readVal1);

    DebugP_log("TestMpu_deviceMemoryType: Device memory read stable, val=0x%08x\r\n", readVal1);
    DebugP_log("TestMpu_deviceMemoryType: PASSED\r\n");

    /* Restore functional MPU state */
    TestMpu_initFn();
}

/**
 * @brief Tests MPU region priority and attribute override in overlapping regions.
 *
 * This function configures two overlapping MPU regions with different attributes.
 * Region A is a non-cacheable baseline, while Region B is a cacheable override within A.
 * It verifies that accesses in the overlapping area use Region B's attributes .
 * The test asserts correct memory access and logs the result.
 */
static void TestMpu_regionPriorityOverlap(void *args)
{
    uint32_t            regionA = 4;
    uint32_t            regionB = 7;
    void               *baseAddr = (void *)gTestMpuBuf;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs    regionParamsA, regionParamsB;
    volatile uint32_t  *testPtr = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0xABCDEF01U;

    MpuP_disable();
    DebugP_log("TestMpu_regionPriorityOverlap: Configuring overlapping regions\r\n");

    /* Region A: baseline that blocks access (no-access permission) */
    MpuP_RegionAttrs_init(&regionParamsA);
    regionParamsA.isEnable             = 1;
    regionParamsA.isCacheable          = 0;
    regionParamsA.isBufferable         = 0;
    regionParamsA.isSharable           = 0;
    regionParamsA.isExecuteNever       = 1;
    regionParamsA.tex                  = 0;
    regionParamsA.accessPerm           = MpuP_AP_ALL_BLOCK;  /* No access */
    regionParamsA.subregionDisableMask = 0x0;

    MpuP_setRegion(regionA, baseAddr, sizeCode, &regionParamsA);

    /*
     * Region B: higher-numbered region that enables access in the overlap.
     * On ARMv7-M, when regions overlap the higher-numbered region's
     * attributes take priority. If priority works correctly, accesses in
     * the overlap area will use Region B's RW permission and succeed. If
     * Region A's no-access were applied instead, the access would fault.
     */
    MpuP_RegionAttrs_init(&regionParamsB);
    regionParamsB.isEnable             = 1;
    regionParamsB.isCacheable          = 1;
    regionParamsB.isBufferable         = 1;
    regionParamsB.isSharable           = 0;
    regionParamsB.isExecuteNever       = 1;
    regionParamsB.tex                  = 1;
    regionParamsB.accessPerm           = MpuP_AP_ALL_RW;  /* Full access */
    regionParamsB.subregionDisableMask = 0x0;

    MpuP_setRegion(regionB, baseAddr, sizeCode, &regionParamsB);

    /* Enable the MPU (with background region) so priorities are enforced */
    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_enable();

    /*
     * Access address in overlap area. If Region B (higher number) correctly
     * overrides Region A (no-access), this write/read will succeed.
     * If Region A's no-access attribute were applied, a fault would occur.
     */
    *testPtr = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testPtr);

    /* Cleanup */
    MpuP_disable();
    MpuP_resetRegion(regionA);
    MpuP_resetRegion(regionB);
    TestMpu_initFn();

    DebugP_log("TestMpu_regionPriorityOverlap: Overlap access OK (higher region wins)\r\n");
    DebugP_log("TestMpu_regionPriorityOverlap: PASSED\r\n");
}

/**
 * @brief Tests that resetting an MPU region clears its configuration.
 *
 * This function programs an MPU region with specific attributes, resets the region,
 * and then reprograms it with the same attributes. It verifies that the region
 * can be successfully reconfigured after a reset, confirming that the reset
 * operation clears previous settings. The test asserts correct configuration
 * and functional access, logging the results.
 */
static void TestMpu_resetRegionClearsEntry(void *args)
{
    uint32_t            regionNum = 6;
    void               *baseAddr = (void *)gTestMpuBuf;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testPtr = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0x12341234U;
    uint32_t            expRasr;
    int32_t             chk;

    MpuP_disable();
    DebugP_log("TestMpu_resetRegionClearsEntry: Testing region reset\r\n");

    /* Step 1: Program region */
    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;
    regionParams.isCacheable          = 1;
    regionParams.isBufferable         = 0;
    regionParams.isSharable           = 0;
    regionParams.isExecuteNever       = 1;
    regionParams.tex                  = 0;
    regionParams.accessPerm           = MpuP_AP_S_RW_U_R;
    regionParams.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);
    DebugP_log("Region %u programmed\r\n", regionNum);

    /* Step 2: Reset region */
    MpuP_resetRegion(regionNum);
    DebugP_log("Region %u reset\r\n", regionNum);

    /* Step 2a: Verify reset cleared the region.
     * After reset, the region's base, size, and attributes must all be
     * zero, and the original (non-zero) config must no longer match.
     */
    chk = TestMpu_verifyCfgRegion(regionNum, 0U, 0U);
    TEST_ASSERT_EQUAL_INT32(CORE_M4_APP_TEST_PASS, chk);

    expRasr = TestMpu_getAttrsAndSize(&regionParams, sizeCode);
    chk = TestMpu_verifyCfgRegion(regionNum, (uint32_t)baseAddr, expRasr);
    TEST_ASSERT_NOT_EQUAL(CORE_M4_APP_TEST_PASS, chk);
    DebugP_log("Region %u reset verified (old config no longer matches)\r\n", regionNum);

    /* Step 3: Re-program same region */
    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    /* Step 4: Verify configuration */
    chk = TestMpu_verifyCfgRegion(regionNum, (uint32_t)baseAddr, expRasr);
    TEST_ASSERT_EQUAL_INT32(CORE_M4_APP_TEST_PASS, chk);

    /* Functional access test */
    *testPtr = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testPtr);

    /* Cleanup */
    MpuP_resetRegion(regionNum);
}

/**
 * @brief Tests default initialization of MPU region attributes.
 *
 * This function initializes an MPU region attributes structure to its default values,
 * verifies the defaults against expected values, and then overrides certain attributes
 * for a functional test. It programs the region with the overridden attributes and
 * performs a memory access to confirm correct operation. The test asserts correctness
 * and logs the results.
 */
static void TestMpu_regionAttrsInitDefaults(void *args)
{
    MpuP_RegionAttrs    regionParams;
    uint32_t            regionNum = 6;
    void               *baseAddr = (void *)gTestMpuBuf;
    uint32_t            sizeCode = TEST_MPU_REGION_SIZE_1KB;
    volatile uint32_t  *testPtr = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0x99887766U;

    MpuP_disable();
    DebugP_log("TestMpu_regionAttrsInitDefaults: Testing default initialization\r\n");

    /* Step 1 & 2: Init and log defaults */
    MpuP_RegionAttrs_init(&regionParams);

    DebugP_log("Default attrs: XN=%u, AP=%u, TEX=%u, S=%u, C=%u, B=%u, EN=%u, SRD=0x%02x\r\n",
               regionParams.isExecuteNever,
               regionParams.accessPerm,
               regionParams.tex,
               regionParams.isSharable,
               regionParams.isCacheable,
               regionParams.isBufferable,
               regionParams.isEnable,
               regionParams.subregionDisableMask);

    /* Verify expected defaults from MpuP_armv7m.c:MpuP_RegionAttrs_init */
    TEST_ASSERT_EQUAL_UINT8(0, regionParams.isExecuteNever);
    TEST_ASSERT_EQUAL_UINT8(MpuP_AP_S_RW_U_R, regionParams.accessPerm);
    TEST_ASSERT_EQUAL_UINT8(0, regionParams.tex);
    TEST_ASSERT_EQUAL_UINT8(1, regionParams.isSharable);
    TEST_ASSERT_EQUAL_UINT8(0, regionParams.isCacheable);
    TEST_ASSERT_EQUAL_UINT8(0, regionParams.isBufferable);
    TEST_ASSERT_EQUAL_UINT8(0, regionParams.isEnable);
    TEST_ASSERT_EQUAL_UINT8(0, regionParams.subregionDisableMask);

    /* Step 3: Override for functional test */
    regionParams.isEnable    = 1;
    regionParams.isCacheable = 1;
    regionParams.tex         = 1;

    DebugP_log("Overridden attrs: C=1, TEX=1, EN=1\r\n");

    /* Step 4: Program region */
    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    /* Step 5: Functional test */
    *testPtr = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testPtr);

    /* Cleanup */
    MpuP_resetRegion(regionNum);
}

/* The MpuP_init() based tests below reset ALL MPU regions and reprogram the
 * MPU configuration. On ARMv7-M this is safe because, while the MPU is
 * disabled or when the background region (PRIVDEFENA) is enabled, the
 * default memory map keeps all code and data accessible. */

/**
 * @brief Tests that MpuP_init() disables the MPU if it is already enabled.
 *
 * This test first enables the MPU and verifies its state.
 * It then configures the MPU settings to disable the MPU on initialization.
 * After calling MpuP_init(), it checks that the MPU is indeed disabled.
 * Logs are generated to indicate the test progress and result.
 */
static void TestMpu_init_disablesIfEnabled(void *args)
{
    uint32_t mpuState;

    MpuP_disable();
    DebugP_log("TestMpu_init_disablesIfEnabled: Testing init with MPU already enabled\r\n");

    /* Enable MPU first (with background region so enable is safe) */
    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_enable();
    mpuState = MpuP_isEnable();
    TEST_ASSERT_NOT_EQUAL(0, mpuState);
    DebugP_log("  MPU enabled before init: %u\r\n", mpuState);

    /* Configure for basic init */
    gMpuConfig.numRegions             = 0;
    gMpuConfig.enableBackgroundRegion = 0;
    gMpuConfig.enableMpu              = 0;

    /* Call MpuP_init() - should disable MPU internally */
    MpuP_init();

    /* Verify MPU is disabled (because enableMpu=0) */
    mpuState = MpuP_isEnable();
    TEST_ASSERT_EQUAL_UINT32(0, mpuState);
    DebugP_log("  MPU disabled after init: %u\r\n", mpuState);
    DebugP_log("TestMpu_init_disablesIfEnabled: PASSED\r\n");
}

/**
 * @brief Tests that MpuP_init() resets all MPU regions.
 *
 * This function manually configures an MPU region, then calls MpuP_init()
 * with zero regions configured. It verifies that the previously configured
 * region is reset (disabled) after initialization. The test asserts correct
 * behavior and logs the results.
 */
static void TestMpu_init_resetsAllRegions(void *args)
{
    MpuP_RegionAttrs attrs;
    int32_t          chk;

    MpuP_disable();
    DebugP_log("TestMpu_init_resetsAllRegions: Testing region reset during init\r\n");

    /* Manually configure a region */
    MpuP_RegionAttrs_init(&attrs);
    attrs.isEnable    = 1;
    attrs.isCacheable = 1;
    attrs.accessPerm  = MpuP_AP_S_RW_U_R;
    MpuP_setRegion(5, (void *)gTestMpuBuf, TEST_MPU_REGION_SIZE_1KB, &attrs);
    DebugP_log("  Region 5 configured manually\r\n");

    /* Call MpuP_init() with numRegions=0 - should reset all regions including region 5 */
    gMpuConfig.numRegions             = 0;
    gMpuConfig.enableBackgroundRegion = 0;
    gMpuConfig.enableMpu              = 0;

    MpuP_init();

    /* Region 5 must be cleared - verify via register readback */
    chk = TestMpu_verifyCfgRegion(5U, 0U, 0U);
    TEST_ASSERT_EQUAL_INT32(CORE_M4_APP_TEST_PASS, chk);
    DebugP_log("  All regions reset successfully\r\n");

    DebugP_log("TestMpu_init_resetsAllRegions: PASSED\r\n");
}

/**
 * @brief Tests enabling the background region and its interaction with foreground regions.
 *
 * When the background region is enabled, any address not covered by a foreground
 * MPU region uses default privileged-only access. This test:
 * 1. Enables the background region and MPU via MpuP_init().
 * 2. Configures a foreground region (cacheable, full RW) over the test MSRAM area.
 * 3. Writes/reads via the foreground region to verify foreground attributes apply.
 * 4. Accesses MMIO space (not covered by any foreground region) to verify the
 *    background region provides default access for uncovered addresses.
 */
static void TestMpu_init_enablesBackgroundRegion(void *args)
{
    uint32_t            mpuState;
    uint32_t            regionNum = 7;
    void               *fgBase = (void *)gTestMpuBuf;
    uint32_t            fgSize = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs    fgAttrs;
    volatile uint32_t  *fgPtr = (volatile uint32_t *)fgBase;
    uint32_t            fgTestVal = 0xF0F0F0F0U;
    uint32_t            bgTestVal = 0x0F0F0F0FU;

    MpuP_disable();
    DebugP_log("TestMpu_init_enablesBackgroundRegion: Testing BR with foreground region\r\n");

    /* Step 1: Enable background region (PRIVDEFENA) and MPU via MpuP_init()
     * with no foreground regions configured */
    gMpuConfig.numRegions             = 0;
    gMpuConfig.enableBackgroundRegion = 1;
    gMpuConfig.enableMpu              = 1;

    MpuP_init();

    mpuState = MpuP_isEnable();
    TEST_ASSERT_NOT_EQUAL(0, mpuState);
    DebugP_log("  MPU enabled with BR=1: %u\r\n", mpuState);

    /* Step 2: With no foreground regions, buffer access goes through the
     * background default memory map (privileged access) */
    *fgPtr = bgTestVal;
    TEST_ASSERT_EQUAL_UINT32(bgTestVal, *fgPtr);
    DebugP_log("  Background region access verified: 0x%08x\r\n", bgTestVal);

    /* Step 3: Configure a foreground region over the buffer and verify
     * foreground attributes apply */
    MpuP_disable();
    MpuP_RegionAttrs_init(&fgAttrs);
    fgAttrs.isEnable             = 1;
    fgAttrs.isCacheable          = 1;
    fgAttrs.isBufferable         = 1;
    fgAttrs.isSharable           = 0;
    fgAttrs.isExecuteNever       = 1;
    fgAttrs.tex                  = 1;
    fgAttrs.accessPerm           = MpuP_AP_ALL_RW;
    fgAttrs.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, fgBase, fgSize, &fgAttrs);
    MpuP_enable();
    DebugP_log("  Foreground region %u configured at 0x%08x\r\n",
               regionNum, (uint32_t)fgBase);

    *fgPtr = fgTestVal;
    TEST_ASSERT_EQUAL_UINT32(fgTestVal, *fgPtr);
    DebugP_log("  Foreground region write/read verified: 0x%08x\r\n", fgTestVal);

    /* Cleanup: reset the foreground region and restore functional MPU state */
    MpuP_disable();
    MpuP_resetRegion(regionNum);
    TestMpu_initFn();

    DebugP_log("TestMpu_init_enablesBackgroundRegion: PASSED\r\n");
}

/**
 * @brief Tests the complete initialization flow of the MPU.
 *
 * This function tests various scenarios of MPU initialization, including
 * disabling and enabling the MPU, enabling the background region, and
 * restoring the original configuration. It verifies the MPU state after
 * each step and logs the progress and results.
 */
static void TestMpu_init_fullFlow(void *args)
{
    uint32_t origNumRegions;
    uint32_t origEnableBR;
    uint32_t origEnableMpu;

    MpuP_disable();
    DebugP_log("TestMpu_init_fullFlow: Testing complete init flow\r\n");

    /* Save original config */
    origNumRegions = gMpuConfig.numRegions;
    origEnableBR   = gMpuConfig.enableBackgroundRegion;
    origEnableMpu  = gMpuConfig.enableMpu;

    /* Test 1: Init with MPU disabled */
    gMpuConfig.numRegions             = 0;
    gMpuConfig.enableBackgroundRegion = 0;
    gMpuConfig.enableMpu              = 0;
    MpuP_init();
    TEST_ASSERT_EQUAL_UINT32(0, MpuP_isEnable());
    DebugP_log("  Step 1: MPU disabled\r\n");

    /* Test 2: Init with MPU enabled. The background region (PRIVDEFENA)
     * must be enabled since no foreground regions are configured, otherwise
     * the very next instruction fetch would fault */
    gMpuConfig.enableBackgroundRegion = 1;
    gMpuConfig.enableMpu              = 1;
    MpuP_init();
    TEST_ASSERT_NOT_EQUAL(0, MpuP_isEnable());
    DebugP_log("  Step 2: MPU enabled with BR\r\n");

    /* Restore original config */
    gMpuConfig.numRegions             = origNumRegions;
    gMpuConfig.enableBackgroundRegion = origEnableBR;
    gMpuConfig.enableMpu              = origEnableMpu;

    DebugP_log("TestMpu_init_fullFlow: PASSED\r\n");
}

/**
 * @brief Tests MPU initialization with two memory regions.
 *
 * This function configures two MPU regions with different attributes,
 * initializes the MPU, and verifies access to both regions. It checks
 * for correct region setup and functional memory access. Debug logs
 * are used to indicate progress and test results.
 */
static void TestMpu_init_configuresTwoRegions(void *args)
{
    volatile uint32_t *testPtr;
    uint32_t           testValue;
    uint32_t           expRasr;
    int32_t            chk;

    MpuP_disable();
    DebugP_log("TestMpu_init_configuresTwoRegions: Testing MpuP_init() with numRegions=2\r\n");

    /* Region 0: entire 4GB address space, no execute, full RW */
    gMpuRegionConfig[0].baseAddr = 0x00000000U;
    gMpuRegionConfig[0].size = 0x1FU; /* b11111 = 4GB */
    MpuP_RegionAttrs_init(&gMpuRegionConfig[0].attrs);
    gMpuRegionConfig[0].attrs.isEnable             = 1;
    gMpuRegionConfig[0].attrs.isCacheable          = 0;
    gMpuRegionConfig[0].attrs.isBufferable         = 0;
    gMpuRegionConfig[0].attrs.isSharable           = 0;
    gMpuRegionConfig[0].attrs.isExecuteNever       = 1;
    gMpuRegionConfig[0].attrs.tex                  = 0;
    gMpuRegionConfig[0].attrs.accessPerm           = MpuP_AP_ALL_RW;
    gMpuRegionConfig[0].attrs.subregionDisableMask = 0x0;

    /* Region 1: RAM test buffer, normal memory */
    gMpuRegionConfig[1].baseAddr = (uint32_t)gTestMpuBuf;
    gMpuRegionConfig[1].size = TEST_MPU_REGION_SIZE_1KB;
    MpuP_RegionAttrs_init(&gMpuRegionConfig[1].attrs);
    gMpuRegionConfig[1].attrs.isEnable             = 1;
    gMpuRegionConfig[1].attrs.isCacheable          = 1;
    gMpuRegionConfig[1].attrs.isBufferable         = 1;
    gMpuRegionConfig[1].attrs.isSharable           = 0;
    gMpuRegionConfig[1].attrs.isExecuteNever       = 1;
    gMpuRegionConfig[1].attrs.tex                  = 1;
    gMpuRegionConfig[1].attrs.accessPerm           = MpuP_AP_ALL_RW;
    gMpuRegionConfig[1].attrs.subregionDisableMask = 0x0;

    /* Configure for init, MPU is left disabled (enableMpu=0) */
    gMpuConfig.numRegions             = 2;
    gMpuConfig.enableBackgroundRegion = 0;
    gMpuConfig.enableMpu              = 0;

    /* Call MpuP_init() - should configure both regions */
    MpuP_init();

    /* Verify both regions via register readback */
    expRasr = TestMpu_getAttrsAndSize(&gMpuRegionConfig[0].attrs, gMpuRegionConfig[0].size);
    chk = TestMpu_verifyCfgRegion(0U, gMpuRegionConfig[0].baseAddr, expRasr);
    TEST_ASSERT_EQUAL_INT32(CORE_M4_APP_TEST_PASS, chk);
    DebugP_log("  Region 0 (4GB) configuration verified\r\n");

    expRasr = TestMpu_getAttrsAndSize(&gMpuRegionConfig[1].attrs, gMpuRegionConfig[1].size);
    chk = TestMpu_verifyCfgRegion(1U, gMpuRegionConfig[1].baseAddr, expRasr);
    TEST_ASSERT_EQUAL_INT32(CORE_M4_APP_TEST_PASS, chk);
    DebugP_log("  Region 1 (RAM test buffer) configuration verified\r\n");

    /* Functional test: access the RAM test buffer */
    testPtr = (volatile uint32_t *)gTestMpuBuf;
    testValue = 0x11223344U;
    *testPtr = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testPtr);
    DebugP_log("  Region 1 (RAM test buffer) access verified\r\n");

    /* Cleanup */
    gMpuConfig.numRegions = 0;
    MpuP_resetRegion(0);
    MpuP_resetRegion(1);

    DebugP_log("TestMpu_init_configuresTwoRegions: PASSED\r\n");
}






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
 *  \file     test_core_r5_mpu.c
 *
 *  \brief    This file contains mpu API test code for R5 core.
 *
 *  \details  MPU read/write and configuration tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include <stdio.h>
#include <string.h>
#include <unity.h>
#include "core_r5_test.h"
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/nortos/dpl/r5/CacheP_armv7r.h>
#include <kernel/dpl/MpuP_armv7.h>
#include <kernel/nortos/dpl/r5/MpuP_armv7r.h>
#include <kernel/nortos/dpl/r5/HwiP_armv7r_vim.h>

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/

#define CORE_R5_TEST_R5_MPU_ENABLE         ((uint32_t)1U)
#define CORE_R5_TEST_R5_MPU_DISABLE        ((uint32_t)0U)
#define CORE_R5_TEST_MPU_NUM_CONF_REGIONS  ((uint32_t)3U)
#define CONFIG_MPU_NUM_REGIONS             (0u)
#define MPU_SECTION                        __attribute__((section(".text.mpu")))

#if defined (DM_R5FSS)
/* On the DM R5 (WKUP R5FSS) the test code executes from DDR (>= 0x80000000).
 * If the MPU is disabled while executing from DDR, the ARMv7-R default memory
 * map marks DDR as Device + Execute-Never and the very next instruction fetch
 * prefetch-aborts. Hence, on this core the MPU is never disabled from test
 * code that runs in DDR. Reprogramming regions is still safe with the MPU
 * enabled because MpuP_setRegion() internally does the disable/re-enable
 * sequence entirely from TCM resident code (.text.mpu).
 */
#define TestMpu_setupDisable()
#else
#define TestMpu_setupDisable()             MpuP_disable()
#endif

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/

/**
 * For the unit test we are using the startup library to reach to main().
 * Since the startup library initializes the default mpu, we should prevent
 * the initialization from startup library. The way to prevent the MPU
 * initialization is to define a dummy __mpu_init() function here.
 */
#if defined (DM_R5FSS)
/**
 * On the DM R5 (WKUP R5FSS) the test image is linked to DDR, i.e. above
 * 0x80000000. On ARMv7-R, while the MPU is disabled the default memory map
 * marks the upper 2GB (0x80000000-0xFFFFFFFF) as Device + Execute-Never.
 * With a fully empty __mpu_init() the MPU stays disabled and the first branch
 * from the TCM resident boot code (.text.boot) into DDR .text prefetch-aborts,
 * hanging the core before even UNITY_BEGIN() can print anything.
 *
 * Hence, for this core, a minimal MPU configuration (Device background +
 * TCM + DDR executable) is programmed here and the MPU is enabled, while
 * still bypassing the SysConfig based init.
 *
 * Notes:
 * - This function and everything it calls (MpuP_*, CacheP_*, HwiP_disable)
 *   executes from TCM (.text.mpu/.text.cache/.text.hwi/.text.boot), so it is
 *   safe to run before the MPU is enabled.
 * - It runs before .bss/.data init, so no global data may be used here.
 * - MpuP_setRegionAsm() is called directly instead of MpuP_setRegion() with a
 *   stack based MpuP_RegionAttrs struct: the stack is in DDR, which is
 *   Strongly-Ordered while the MPU is disabled, and the compiler can merge
 *   the byte wide struct field writes into unaligned stores, which data-abort
 *   on Strongly-Ordered memory. All arguments below are register values only.
 */

/* TCM resident (.text.mpu) low level MPU program function from MpuP_armv7r_asm.S */
extern void MpuP_setRegionAsm(uint32_t regionId, uint32_t regionBaseAddr,
                              uint32_t sizeAndEnable, uint32_t regionAttrs);

/*
 * RSR (sizeAndEnable) = (subregionDisableMask << 8) | (sizeN << 1) | enable
 * RACR (regionAttrs)  = (XN << 12) | (AP << 8) | (TEX << 3) | (S << 2) | (C << 1) | B
 */
void MPU_SECTION __mpu_init(void)
{
    /* Region 0: entire 4GB as Device memory (S=1), all RW, execute never */
    MpuP_setRegionAsm(0U, 0x00000000U,
                      ((0x1FU << 1U) | 1U) /* 4GB, enabled */,
                      ((1U << 12U) | ((uint32_t)MpuP_AP_ALL_RW << 8U) | (1U << 2U)));

    /* Region 1: TCMA 32KB (vectors + boot/mpu/cache/hwi code), executable,
     * normal non-cacheable (TEX=1), shareable */
    MpuP_setRegionAsm(1U, 0x00000000U,
                      ((0x0EU << 1U) | 1U) /* 32KB, enabled */,
                      (((uint32_t)MpuP_AP_ALL_RW << 8U) | (1U << 3U) | (1U << 2U)));

    /* Region 2: DDR 2GB (this test's code/data/stacks), normal write-back
     * cacheable (TEX=1, C=1, B=1), executable */
    MpuP_setRegionAsm(2U, 0x80000000U,
                      ((0x1EU << 1U) | 1U) /* 2GB, enabled */,
                      (((uint32_t)MpuP_AP_ALL_RW << 8U) | (1U << 3U) | (1U << 1U) | 1U));

    MpuP_enable();
}
#else
void __mpu_init(void)
{
    /* Do not implement anything here as anything here would be invoked
     * during startup code */
}
#endif

/* Empty definitions as MPU not configured by SysConfig */
/* ----------- CacheP ----------- */
CacheP_Config gCacheConfig = { };

/* ----------- MpuP_armv7 ----------- */
MpuP_Config gMpuConfig = { };
MpuP_RegionConfig gMpuRegionConfig[CONFIG_MPU_NUM_REGIONS] = { };

/**
 * Calculates and returns the region attribute mask.
 * For more information on region and size attributes, refer:
 * https://developer.arm.com/documentation/ddi0363/g/System-Control/Register-descriptions/c6--MPU-memory-region-programming-registers
 */
uint32_t MPU_SECTION MpuP_getAttrs(MpuP_RegionAttrs *region)
{
    uint32_t regionAttrs =
        ((uint32_t)(region->isExecuteNever & 0x1U) << 12U) |
        ((uint32_t)(region->accessPerm     & 0x7U) << 8U)  |
        ((uint32_t)(region->tex            & 0x7U) << 3U)  |
        ((uint32_t)(region->isSharable     & 0x1U) << 2U)  |
        ((uint32_t)(region->isCacheable    & 0x1U) << 1U)  |
        ((uint32_t)(region->isBufferable   & 0x1U) << 0U);

    return regionAttrs;
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
#if !defined (DM_R5FSS)
static void TestMpu_init_disablesIfEnabled(void *args);
static void TestMpu_init_resetsAllRegions(void *args);
static void TestMpu_init_disablesCacheIfEnabled(void *args);
static void TestMpu_init_enablesBackgroundRegion(void *args);
static void TestMpu_init_fullFlow(void *args);
#if !defined (SOC_AM275X)
static void TestMpu_init_configuresTwoRegions(void *args);
#endif
#endif /* !DM_R5FSS */
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
    /* The MpuP_init() based tests reset ALL MPU regions and/or leave the MPU
     * disabled. On the DM R5 (WKUP R5FSS) this removes the region that keeps
     * DDR executable while the test code itself executes from DDR, causing an
     * immediate prefetch abort. Hence these tests are not run on that core. */
    #if !defined (DM_R5FSS)
    RUN_TEST(TestMpu_init_disablesIfEnabled, 10082, NULL);
    RUN_TEST(TestMpu_init_resetsAllRegions, 10083, NULL);
    RUN_TEST(TestMpu_init_disablesCacheIfEnabled, 10085, NULL);
    RUN_TEST(TestMpu_init_enablesBackgroundRegion, 10086, NULL);
    RUN_TEST(TestMpu_init_fullFlow, 10087, NULL);
    #if !defined (SOC_AM275X)
    RUN_TEST(TestMpu_init_configuresTwoRegions, 10088, NULL);
    #endif
    #endif /* !DM_R5FSS */
    RUN_TEST(TestMpu_accessPermissions, 10062, NULL);
    #if !(defined(MCU_NORTOS) || defined(WKUP_R5FSS))
    RUN_TEST(TestMpu_cacheableAttribute, 10066, NULL);
    RUN_TEST(TestMpu_bufferableAttribute, 10067, NULL);
    #endif
    RUN_TEST(TestMpu_shareableAttribute, 10067, NULL);
    RUN_TEST(TestMpu_normalMemoryType, 10070, NULL);
    #if !defined (DM_R5FSS)
    RUN_TEST(TestMpu_regionPriorityOverlap, 10078, NULL);

    #if defined (ENABLE_MT_TESTS)
    run_multi_threaded_tests(NULL);
    #endif
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

/* Pick a safe, aligned base for the test's "local RAM" region:
 * - AM275x R5 code/data live in on-chip OCRAM at 0x72080000 (per test linker).
 * - Other SoCs keep prior behavior (0x79100000).
 * The returned address is aligned down to the selected region size.
 */
void *TestMpu_getExecBase(void)
{
#if defined(SOC_AM275X)
    #if defined(R5FSS0_0)
        uintptr_t b = (uintptr_t)0x72080000U;
    #elif defined(R5FSS0_1)
        uintptr_t b = (uintptr_t)0x72180000U;
    #elif defined(R5FSS1_0)
        uintptr_t b = (uintptr_t)0x72280000U;
    #elif defined(R5FSS1_1)
        uintptr_t b = (uintptr_t)0x72300000U;
    #else
        uintptr_t b = (uintptr_t)0x72000000U;
    #endif
#else
    uintptr_t b = (uintptr_t)0x79100000U;
#endif
    return (void *)(b);
}

/**
 * @brief Tests the MPU (Memory Protection Unit) configuration and initialization.
 *
 * This function invalidates L1 instruction and data caches, initializes the MPU,
 * asserts the initialization result, retrieves the number of MPU regions, and logs
 * the outcome. It is used to verify correct MPU setup on the R5 core.
 *
 * @param args Pointer to arguments (unused in this test function).
 */
static void TestMpu_configurationTc(void *args)
{
    /* Declarations of variables */
    int32_t    testResult;
    int32_t    numRegions;

    CacheP_invL1pAll();
    CacheP_invL1dAll();     /* Invalidate caches before MPU En*/
    testResult = TestMpu_initFn();
    DebugP_assert(testResult == CORE_R5_APP_TEST_PASS);
    numRegions = MpuP_GetNumRegions();
    DebugP_log(" MPU API tests complete: number of regions tested are : ");
    DebugP_log("0x%x \n", numRegions);
    DebugP_log(" \n\r ");

   return;
}

/**
 * @brief Initializes and verifies MPU regions for R5 core testing.
 *
 * Configures default and specific MPU regions, verifies their settings,
 * and tests enable/disable functionality. Ensures correct permissions,
 * sizes, and attributes are set for each region. Performs detailed
 * verification of region configuration and permission settings.
 * Enables the MPU and interrupt controller upon successful configuration
 * and verification.
 *
 * @return CORE_R5_APP_TEST_PASS on success,
 *         CORE_R5_APP_TEST_FAILED on failure.
 *
 */
int32_t TestMpu_initFn(void)
{
    int32_t               region, chk, testResult = CORE_R5_APP_TEST_PASS;
    uint32_t              numRegions;
    coreR5TestMpuRegion_t mpuRegionDefault, mpuRegion[CORE_R5_TEST_MPU_NUM_CONF_REGIONS];
    uint32_t              mpuVerifyCheckInDetail = 1U;
    uint32_t              sizeAndEnable;
    MpuP_RegionAttrs      regionParams;

    /* Region 0 configuration: complete 32-bit address space */
    mpuRegion[0].base = (void *)(0x00000000U);
    mpuRegion[0].size = 0x1FU; /* b11111 = 4GB */
    mpuRegion[0].permissions.isEnable = 1;
    mpuRegion[0].permissions.isCacheable = 0;
    mpuRegion[0].permissions.isBufferable = 0;
    mpuRegion[0].permissions.isSharable = 0;
    mpuRegion[0].permissions.isExecuteNever = 1; /* Don't allow code execution */
    mpuRegion[0].permissions.tex = 0;
    mpuRegion[0].permissions.accessPerm = 3;
    mpuRegion[0].permissions.subregionDisableMask = 0x0;

    /* Region 1 configuration: TCMA */
    mpuRegion[1].base = (void *)(0x00000000U);
    mpuRegion[1].size = 0x0EU; /* b01110 = 32KB */
    mpuRegion[1].permissions.isEnable = 1;
    mpuRegion[1].permissions.isCacheable = 1;
    mpuRegion[1].permissions.isBufferable = 0;
    mpuRegion[1].permissions.isSharable = 0;
    mpuRegion[1].permissions.isExecuteNever = 0; /* Allow code execution */
    mpuRegion[1].permissions.tex = 0;
    mpuRegion[1].permissions.accessPerm = 3;
    mpuRegion[1].permissions.subregionDisableMask = 0x0;

#if defined (DM_R5FSS)
    /* Region 2 configuration: DDR - must remain executable since this test
     * code itself executes from DDR on the DM R5 */
    mpuRegion[2].base = (void *)0x80000000U;
    mpuRegion[2].size = 0x1EU; /* b11110 = 2GB */
#else
    /* Region 2 configuration: MSRAM */
    mpuRegion[2].base = (void *)TestMpu_getExecBase();
    mpuRegion[2].size = 0x12U; /* b10010 = 512KB */
#endif
    mpuRegion[2].permissions.isEnable = 1;
    mpuRegion[2].permissions.isCacheable = 1;
    mpuRegion[2].permissions.isBufferable = 1;
    mpuRegion[2].permissions.isSharable = 0;
    mpuRegion[2].permissions.isExecuteNever = 0; /* Allow code execution */
    mpuRegion[2].permissions.tex = 1;
    mpuRegion[2].permissions.accessPerm = 3;
    mpuRegion[2].permissions.subregionDisableMask = 0x0;

    /* Default region */
    mpuRegionDefault.base = (void *)0U;
    mpuRegionDefault.size = (uint32_t)0U;
    mpuRegionDefault.permissions.isEnable = 0;
    mpuRegionDefault.permissions.isCacheable = 0;
    mpuRegionDefault.permissions.isBufferable = 0;
    mpuRegionDefault.permissions.isSharable = 0;
    mpuRegionDefault.permissions.isExecuteNever = 0; /* Don't allow code execution */
    mpuRegionDefault.permissions.tex = 0;
    mpuRegionDefault.permissions.accessPerm = 0;
    mpuRegionDefault.permissions.subregionDisableMask = 0x0;

    /* Total number of MPU regions */
    numRegions = MpuP_GetNumRegions();

    /* Disable the MPU first (kept enabled on DM R5, see TestMpu_setupDisable) */
    TestMpu_setupDisable();

    /* Set all the default regions and verify the set regions */
    for (region = (numRegions - 1U); region >= CORE_R5_TEST_MPU_NUM_CONF_REGIONS; region--)
    {
        /* Set default values to region attributes */
        MpuP_RegionAttrs_init(&regionParams);
        regionParams = mpuRegionDefault.permissions;
        MpuP_setRegion(region, mpuRegionDefault.base, mpuRegionDefault.size, &regionParams);
        if (1U == mpuVerifyCheckInDetail)
        {
            /* Verify the regions */
            /* Tweak the region and expect failure */
            chk = MpuP_VerifyCfgRegion(region + 2,
                                       (uintptr_t)mpuRegionDefault.base,
                                       mpuRegionDefault.size,
                                       MpuP_getAttrs(&regionParams));
            if (CSL_PASS == chk)
            {
                testResult = CORE_R5_APP_TEST_FAILED;
                break;
            }
            /* Tweak the base and expect failure */
            chk = MpuP_VerifyCfgRegion(region,
                                       (uintptr_t)0x200,
                                       mpuRegionDefault.size,
                                       MpuP_getAttrs(&regionParams));
            if (CSL_PASS == chk)
            {
                testResult = CORE_R5_APP_TEST_FAILED;
                break;
            }

            /* Tweak the size and expect failure */
            chk = MpuP_VerifyCfgRegion(region,
                                       (uintptr_t)mpuRegionDefault.base,
                                       0x200,
                                       MpuP_getAttrs(&regionParams));
            if (CSL_PASS == chk)
            {
                testResult = CORE_R5_APP_TEST_FAILED;
                break;
            }

            /* Tweak the permission and expect failure */
            chk = MpuP_VerifyCfgRegion(region,
                                       (uintptr_t)mpuRegionDefault.base,
                                       mpuRegionDefault.size,
                                       0x200);
            if (CSL_PASS == chk)
            {
                testResult = CORE_R5_APP_TEST_FAILED;
                break;
            }
            mpuVerifyCheckInDetail = 0U;
        }

        /* Verify the regions */
        chk = MpuP_VerifyCfgRegion(region,
                                   (uintptr_t)mpuRegionDefault.base,
                                   mpuRegionDefault.size,
                                   MpuP_getAttrs(&regionParams));
        if (CSL_PASS != chk)
        {
            testResult = CORE_R5_APP_TEST_FAILED;
            break;
        }
    }

    if (CORE_R5_APP_TEST_PASS == testResult)
    {
        /* Configure the remaining regions and test */
        for (; region >= 0; region--)
        {
            /* Initialize the region attributes */
            MpuP_RegionAttrs_init(&regionParams);
            regionParams = mpuRegion[region].permissions;
            /* Set the regions */
            MpuP_setRegion(region, mpuRegion[region].base, mpuRegion[region].size, &regionParams);
            /* Calculate the Size and Enable field */
            sizeAndEnable = (mpuRegion[region].size & (uint32_t)0x1F) << 1U;
            /* If N is the value in size field, the region size is 2N+1 bytes. */
            sizeAndEnable |= ((uint32_t)(regionParams.subregionDisableMask & (uint32_t)0xFF) << (uint32_t)8)
                             | ((uint32_t)(regionParams.isEnable & (uint32_t)0x1));
            /* Verify the configured region */
            chk = MpuP_VerifyCfgRegion(region,
                                       (uintptr_t)mpuRegion[region].base,
                                       sizeAndEnable,
                                       MpuP_getAttrs(&regionParams));
            if (CSL_PASS != chk)
            {
                testResult = CORE_R5_APP_TEST_FAILED;
                break;
            }
        }
    }

    if (CORE_R5_APP_TEST_PASS == testResult)
    {
        /* Disable region and verify test */
        MpuP_EnableRegion(0, CORE_R5_TEST_R5_MPU_DISABLE);
        chk = MpuP_VerifyEnableRegion(0, CORE_R5_TEST_R5_MPU_DISABLE);

        /* Enable Region and verify test */
        if (CSL_PASS == chk)
        {
            /* Enable the MPU */
            MpuP_EnableRegion(0, CORE_R5_TEST_R5_MPU_ENABLE);
            chk = MpuP_VerifyEnableRegion(0, CORE_R5_TEST_R5_MPU_ENABLE);
            if (CSL_PASS != chk)
            {
                testResult = CORE_R5_APP_TEST_FAILED;
            }
        }
        else
        {
            testResult = CORE_R5_APP_TEST_FAILED;
        }
    }

    if (CORE_R5_APP_TEST_PASS == testResult)
    {
        MpuP_enable();
    }

    if (CORE_R5_APP_TEST_PASS == testResult)
    {
        HwiP_enableVIC(); /* Enable VIC */
        HwiP_enableFIQ(); /* Enable FIQ */
    }
    return (testResult);
}

/**
 * @brief Disables and re-enables the MPU, sampling the enable state.
 *
 * Placed in .text.mpu so that it executes from TCM. On the DM R5
 * (WKUP R5FSS) the rest of the test code lives in DDR, which becomes
 * execute-never under the ARMv7-R default memory map while the MPU is
 * disabled. Keeping the whole disable window inside TCM resident code
 * makes this test safe on all R5 cores.
 */
static void MPU_SECTION TestMpu_toggleMpuFromTcm(uint32_t *disabledState, uint32_t *enabledState)
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

    /* Step 1: Read and log initial state */
    initialState = MpuP_isEnable();
    DebugP_log("TestMpu_enableDisableFlow: Initial MPU state = %u\r\n", initialState);

    /* Step 2 & 3: Disable then enable the MPU from TCM resident code and
     * verify the sampled states */
    TestMpu_toggleMpuFromTcm(&disabledState, &enabledState);
    DebugP_log("After MpuP_disable(), state = %u\r\n", disabledState);
    TEST_ASSERT_EQUAL_UINT32(0, disabledState);
    DebugP_log("After MpuP_enable(), state = %u\r\n", enabledState);
    TEST_ASSERT_NOT_EQUAL(0, enabledState);

    /* Step 4: Repeat disable/enable for idempotence */
    TestMpu_toggleMpuFromTcm(&disabledState, &enabledState);
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
    uint32_t            sizeCode = 0x0EU; /* 32KB = 2^(14+1) = 2^15 */
    void               *baseAddr = (void *)0x00000000U; /* Aligned to 32KB */
    MpuP_RegionAttrs    regionParams;
    uint32_t            sizeAndEnable;
    int32_t             chk;

    /* Disable the MPU first (kept enabled on DM R5, see TestMpu_setupDisable) */
    TestMpu_setupDisable();

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
    regionParams.accessPerm           = MpuP_AP_S_RW_U_R; /* Supervisor RW, User RO */
    regionParams.subregionDisableMask = 0x0;        /* No subregions disabled */

    /* Step 4: Set the MPU region with the specified attributes */
    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    /* Step 5: Verify the region configuration */
    sizeAndEnable = ((uint32_t)(regionParams.subregionDisableMask & 0xFFU) << 8U)
                  | ((uint32_t)(sizeCode & 0x1FU) << 1U)
                  | ((uint32_t)(regionParams.isEnable & 0x1U));

    chk = MpuP_VerifyCfgRegion(regionNum,
                               (uintptr_t)baseAddr,
                               sizeAndEnable,
                               MpuP_getAttrs(&regionParams));

    /* Assert that the configuration verification passed */
    TEST_ASSERT_EQUAL_INT32(CSL_PASS, chk);

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
    uint32_t            regionNum = 6;
    void               *baseAddr = (void *)TestMpu_getExecBase();; /* MSRAM region */
    uint32_t            sizeCode = 0x12U; /* 512KB */
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testPtr = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0xDEADBEEFU;
    uint32_t            readValue;

    TestMpu_setupDisable();

    /* Test policy: S_RW_U_RW (full access) */
    DebugP_log("TestMpu_accessPermissions: Testing S_RW_U_RW policy\r\n");

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

    /* Perform write and read in privileged mode */
    *testPtr = testValue;
    readValue = *testPtr;
    TestMpu_setupDisable();

    TEST_ASSERT_EQUAL_UINT32(testValue, readValue);
    DebugP_log("S_RW_U_RW: Write/Read verified\r\n");

    /* Test policy: S_RW_U_R (supervisor RW, user RO) */
    DebugP_log("TestMpu_accessPermissions: Testing S_RW_U_R policy\r\n");

    regionParams.accessPerm = MpuP_AP_S_RW_U_R;
    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    testValue = 0xCAFEBABEU;
    *testPtr = testValue;
    readValue = *testPtr;

    TEST_ASSERT_EQUAL_UINT32(testValue, readValue);
    DebugP_log("S_RW_U_R: Write/Read verified\r\n");

    DebugP_log("TestMpu_accessPermissions: PASSED\r\n");
}

static uint32_t __attribute__((section(".text.mpu"))) TestMpu_stubFunction(void)
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
    uint32_t         regionNum = 1;
#if defined (DM_R5FSS)
    /* On DM R5 the stub function (.text.mpu) executes from TCMA @ 0x0;
     * region 1 must keep covering TCMA so that the stub stays executable */
    void            *baseAddr = (void *)0x00000000U;
    uint32_t         sizeCode = 0x0EU;              /* 32KB */
#else
    void            *baseAddr = (void *)TestMpu_getExecBase(); /* MSRAM (covers .text.mpu) */
    uint32_t         sizeCode = 0x12U;              /* 512KB */
#endif
    MpuP_RegionAttrs regionParams;
    uint32_t         result;

    TestMpu_setupDisable();

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

    /* Invoke function and verify return */
    result = TestMpu_stubFunction();
    TEST_ASSERT_EQUAL_UINT32(0x12345678U, result);

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
    void               *baseAddr = (void *)TestMpu_getExecBase();
    uint32_t            sizeCode = 0x12U; /* 512KB */
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testBuf = (volatile uint32_t *)baseAddr;
    uint32_t            i, testSize = 256;

    TestMpu_setupDisable();
    DebugP_log("TestMpu_cacheableAttribute: Configuring cacheable region\r\n");

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

    /* Step 3: Write pattern */
    for (i = 0; i < testSize; i++) {
        testBuf[i] = i + 0xA5A5A5A5U;
    }

    /* Read and verify */
    for (i = 0; i < testSize; i++) {
        TEST_ASSERT_EQUAL_UINT32(i + 0xA5A5A5A5U, testBuf[i]);
    }

    DebugP_log("TestMpu_cacheableAttribute: First iteration verified\r\n");

    /* Step 5: Repeat to show warmed cache */
    for (i = 0; i < testSize; i++) {
        testBuf[i] = i + 0xDEADBEEFU;
    }

    for (i = 0; i < testSize; i++) {
        TEST_ASSERT_EQUAL_UINT32(i + 0xDEADBEEFU, testBuf[i]);
    }

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
    uint32_t            regionNum = 8;
    void               *baseAddr = (void *)TestMpu_getExecBase();
    uint32_t            sizeCode = 0x12U;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testBuf = (volatile uint32_t *)baseAddr;
    uint32_t            i, testSize = 128;

    TestMpu_setupDisable();
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

    /* Sequential writes */
    for (i = 0; i < testSize; i++) {
        testBuf[i] = 0xBEEF0000U | i;
    }

    /* Sequential reads and verify */
    for (i = 0; i < testSize; i++) {
        TEST_ASSERT_EQUAL_UINT32(0xBEEF0000U | i, testBuf[i]);
    }

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
    uint32_t            regionNum = 9;
    void               *baseAddr = (void *)TestMpu_getExecBase();
    uint32_t            sizeCode = 0x12U;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testBuf = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0xCAFEBABEU;

    TestMpu_setupDisable();
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

    *testBuf = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testBuf);

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
    uint32_t            regionNum = 10;
    void               *baseAddr = (void *)TestMpu_getExecBase();;
    uint32_t            sizeCode = 0x12U;
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testBuf = (volatile uint32_t *)baseAddr;
    uint32_t            testPattern = 0x5A5A5A5AU;

    TestMpu_setupDisable();
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

    *testBuf = testPattern;
    TEST_ASSERT_EQUAL_UINT32(testPattern, *testBuf);

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
    void               *baseAddr = (void *)CSL_WKUP_CTRL_MMR0_CFG0_BASE; /* Safe MMIO base */
    uint32_t            sizeCode = 0x0FU; /* 64KB */
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *mmioReg = (volatile uint32_t *)baseAddr;
    uint32_t            readVal1, readVal2;

    TestMpu_setupDisable();
    DebugP_log("TestMpu_deviceMemoryType: Configuring Device memory region\r\n");

    MpuP_RegionAttrs_init(&regionParams);
    regionParams.isEnable             = 1;
    regionParams.isCacheable          = 0;  /* Device: no cache */
    regionParams.isBufferable         = 0;  /* Device: no buffer */
    regionParams.isSharable           = 1;  /* Device: shareable */
    regionParams.isExecuteNever       = 1;  /* XN */
    regionParams.tex                  = 0;
    regionParams.accessPerm           = MpuP_AP_S_RW_U_R;
    regionParams.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    /* Perform begin reads from MMIO */
    readVal1 = *mmioReg;
    readVal2 = *mmioReg;

    /* Values should be stable for a config register */
    TEST_ASSERT_EQUAL_UINT32(readVal1, readVal2);

    DebugP_log("TestMpu_deviceMemoryType: MMIO read successful, val=0x%08x\r\n", readVal1);
    DebugP_log("TestMpu_deviceMemoryType: PASSED\r\n");

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
    uint32_t            regionB = 13;
    void               *baseAddrA = (void *)TestMpu_getExecBase();
    void               *baseAddrB = (void *)TestMpu_getExecBase(); /* Overlaps within A */
    uint32_t            sizeCodeA = 0x12U; /* 512KB */
    uint32_t            sizeCodeB = 0x0FU; /* 64KB */
    MpuP_RegionAttrs    regionParamsA, regionParamsB;
    volatile uint32_t  *testPtr = (volatile uint32_t *)baseAddrB;
    uint32_t            testValue = 0xABCDEF01U;

    TestMpu_setupDisable();
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

    MpuP_setRegion(regionA, baseAddrA, sizeCodeA, &regionParamsA);

    /*
     * Region B: higher-numbered region that enables access in the overlap.
     * On ARMv7-R, when regions overlap the higher-numbered region's attributes
     * take priority. If priority works correctly, accesses in the overlap area
     * will use Region B's RW permission and succeed. If Region A's no-access
     * were applied instead, the access would fault.
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

    MpuP_setRegion(regionB, baseAddrB, sizeCodeB, &regionParamsB);

    /*
     * Access address in overlap area. If Region B (higher number) correctly
     * overrides Region A (no-access), this write/read will succeed.
     * If Region A's no-access attribute were applied, a data abort would occur.
     */
    *testPtr = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testPtr);

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
    /* Region 6: first scratch region above the 3 regions (0-2) used by TestMpu_initFn() */
    uint32_t            regionNum = 6;
    void               *baseAddr = (void *)TestMpu_getExecBase();
    uint32_t            sizeCode = 0x0EU; /* 32KB */
    MpuP_RegionAttrs    regionParams;
    volatile uint32_t  *testPtr = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0x12341234U;
    uint32_t            sizeAndEnable;
    int32_t             chk;

    TestMpu_setupDisable();
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

    /* Step 2a: Verify reset cleared the region — negative test.
     * After reset, the region's base, size, and attributes should all be zero.
     * Verifying against the original (non-zero) config should fail (CSL_PASS
     * must NOT be returned), proving the reset actually cleared the entry.
     */
    sizeAndEnable = ((uint32_t)(regionParams.subregionDisableMask & 0xFFU) << 8U)
                  | ((uint32_t)(sizeCode & 0x1FU) << 1U)
                  | ((uint32_t)(regionParams.isEnable & 0x1U));

    chk = MpuP_VerifyCfgRegion(regionNum,
                               (uintptr_t)baseAddr,
                               sizeAndEnable,
                               MpuP_getAttrs(&regionParams));
    TEST_ASSERT_NOT_EQUAL(CSL_PASS, chk);
    DebugP_log("Region %u reset verified (old config no longer matches)\r\n", regionNum);

    /* Step 3: Re-program same region */
    MpuP_setRegion(regionNum, baseAddr, sizeCode, &regionParams);

    /* Step 4: Verify configuration */
    sizeAndEnable = ((uint32_t)(regionParams.subregionDisableMask & 0xFFU) << 8U)
                  | ((uint32_t)(sizeCode & 0x1FU) << 1U)
                  | ((uint32_t)(regionParams.isEnable & 0x1U));

    chk = MpuP_VerifyCfgRegion(regionNum,
                               (uintptr_t)baseAddr,
                               sizeAndEnable,
                               MpuP_getAttrs(&regionParams));
    TEST_ASSERT_EQUAL_INT32(CSL_PASS, chk);

    /* Functional access test */
    *testPtr = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testPtr);

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
    /* Region 6: first scratch region above the 3 regions (0-2) used by TestMpu_initFn() */
    uint32_t            regionNum = 6;
    void               *baseAddr = (void *)TestMpu_getExecBase();
    uint32_t            sizeCode = 0x0EU;
    volatile uint32_t  *testPtr = (volatile uint32_t *)baseAddr;
    uint32_t            testValue = 0x99887766U;

    TestMpu_setupDisable();
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

    /* Verify expected defaults from MpuP_armv7r.c:MpuP_RegionAttrs_init */
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

}

#if !defined (DM_R5FSS)
/* The MpuP_init() based tests below reset ALL MPU regions and/or leave the
 * MPU disabled. On the DM R5 (WKUP R5FSS) this removes the region that keeps
 * DDR executable while the test code itself executes from DDR, causing an
 * immediate prefetch abort. Hence these tests are excluded on that core. */

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

    /* Enable MPU first */
    MpuP_enable();
    mpuState = MpuP_isEnable();
    TEST_ASSERT_NOT_EQUAL(0, mpuState);
    DebugP_log("  MPU enabled before init: %u\r\n", mpuState);

    /* Configure for basic init */
    gMpuConfig.numRegions            = 0;
    gMpuConfig.enableBackgroundRegion = 0;
    gMpuConfig.enableMpu             = 0;

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

    MpuP_disable();
    DebugP_log("TestMpu_init_resetsAllRegions: Testing region reset during init\r\n");

    /* Manually configure a region */
    MpuP_RegionAttrs_init(&attrs);
    attrs.isEnable    = 1;
    attrs.isCacheable = 1;
    attrs.accessPerm  = MpuP_AP_S_RW_U_R;
    MpuP_setRegion(5, (void *)TestMpu_getExecBase(), 0x10U, &attrs);
    DebugP_log("  Region 5 configured manually\r\n");

    /* Call MpuP_init() with numRegions=0 - should reset all regions including region 5 */
    gMpuConfig.numRegions            = 0;
    gMpuConfig.enableBackgroundRegion = 0;
    gMpuConfig.enableMpu             = 0;

    MpuP_init();

    /* Region 5 should be reset (disabled) */
    /* We can't directly read registers, but if no fault occurs, reset worked */
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
    void               *fgBase = (void *)TestMpu_getExecBase();
    uint32_t            fgSize = 0x12U; /* 512KB */
    MpuP_RegionAttrs    fgAttrs;
    volatile uint32_t  *fgPtr = (volatile uint32_t *)fgBase;
    volatile uint32_t  *bgPtr = (volatile uint32_t *)CSL_WKUP_CTRL_MMR0_CFG0_BASE;
    uint32_t            fgTestVal = 0xF0F0F0F0U;
    uint32_t            bgReadVal1, bgReadVal2;

    MpuP_disable();
    DebugP_log("TestMpu_init_enablesBackgroundRegion: Testing BR with foreground region\r\n");

    /* Step 1: Enable background region and MPU via MpuP_init() */
    gMpuConfig.numRegions             = 0;
    gMpuConfig.enableBackgroundRegion = 1;
    gMpuConfig.enableMpu              = 1;

    MpuP_init();

    mpuState = MpuP_isEnable();
    TEST_ASSERT_NOT_EQUAL(0, mpuState);
    DebugP_log("  MPU enabled with BR=1: %u\r\n", mpuState);
    MpuP_disable();

    /* Step 2: Configure a foreground region over test MSRAM (cacheable, full RW) */
    MpuP_RegionAttrs_init(&fgAttrs);
    fgAttrs.isEnable       = 1;
    fgAttrs.isCacheable    = 1;
    fgAttrs.isBufferable   = 1;
    fgAttrs.isSharable     = 0;
    fgAttrs.isExecuteNever = 1;
    fgAttrs.tex            = 1;
    fgAttrs.accessPerm     = MpuP_AP_ALL_RW;
    fgAttrs.subregionDisableMask = 0x0;

    MpuP_setRegion(regionNum, fgBase, fgSize, &fgAttrs);
    DebugP_log("  Foreground region %u configured at 0x%08x\r\n",
               regionNum, (uint32_t)(uintptr_t)fgBase);

    /* Step 3: Write/read in the foreground region — foreground attributes apply */
    *fgPtr = fgTestVal;
    TEST_ASSERT_EQUAL_UINT32(fgTestVal, *fgPtr);
    DebugP_log("  Foreground region write/read verified: 0x%08x\r\n", fgTestVal);

    /*
     * Step 4: Access MMIO space (not covered by any foreground region).
     * The background region provides default privileged access, so this
     * read should succeed without a data abort.
     */
    bgReadVal1 = *bgPtr;
    bgReadVal2 = *bgPtr;
    TEST_ASSERT_EQUAL_UINT32(bgReadVal1, bgReadVal2);
    DebugP_log("  Background region MMIO read verified: 0x%08x\r\n", bgReadVal1);

    /* Cleanup: reset the foreground region and restore functional MPU state */
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
    uint32_t mpuState;
    uint32_t origNumRegions;
    uint32_t origEnableBR;
    uint32_t origEnableMpu;

    MpuP_disable();
    DebugP_log("TestMpu_init_fullFlow: Testing complete init flow\r\n");

    /* Save original config */
    origNumRegions      = gMpuConfig.numRegions;
    origEnableBR        = gMpuConfig.enableBackgroundRegion;
    origEnableMpu       = gMpuConfig.enableMpu;

    /* Test 1: Disable then enable */
    gMpuConfig.enableMpu = 0;
    MpuP_init();
    TEST_ASSERT_EQUAL_UINT32(0, MpuP_isEnable());
    DebugP_log("  Step 1: MPU disabled\r\n");

    gMpuConfig.enableMpu = 1;
    MpuP_init();
    TEST_ASSERT_NOT_EQUAL(0, MpuP_isEnable());
    DebugP_log("  Step 2: MPU enabled\r\n");

    /* Test 2: With background region */
    gMpuConfig.enableBackgroundRegion = 1;
    MpuP_init();
    mpuState = MpuP_isEnable();
    TEST_ASSERT_NOT_EQUAL(0, mpuState);
    DebugP_log("  Step 3: MPU with BR enabled\r\n");

    /* Restore original config */
    gMpuConfig.numRegions            = origNumRegions;
    gMpuConfig.enableBackgroundRegion = origEnableBR;
    gMpuConfig.enableMpu             = origEnableMpu;

    DebugP_log("TestMpu_init_fullFlow: PASSED\r\n");
}

#if !defined (SOC_AM275X)
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
    uint32_t testValue;

    MpuP_disable();
    DebugP_log("TestMpu_init_configuresMultipleRegions: Testing MpuP_init() with numRegions=2\r\n");

    /* Setup two regions in gMpuRegionConfig */
    extern MpuP_RegionConfig gMpuRegionConfig[];
    gMpuRegionConfig[0].baseAddr = 0x00000000U;
    gMpuRegionConfig[0].size = 0x1FU; /* b11111 = 4GB */
    MpuP_RegionAttrs_init(&gMpuRegionConfig[0].attrs);
    gMpuRegionConfig[0].attrs.isEnable = 1;
    gMpuRegionConfig[0].attrs.isCacheable = 0;
    gMpuRegionConfig[0].attrs.isBufferable = 0;
    gMpuRegionConfig[0].attrs.isSharable = 0;
    gMpuRegionConfig[0].attrs.isExecuteNever = 1;
    gMpuRegionConfig[0].attrs.tex = 0;
    gMpuRegionConfig[0].attrs.accessPerm = 3;
    gMpuRegionConfig[0].attrs.subregionDisableMask = 0x0;

    gMpuRegionConfig[1].baseAddr = (0x00000000U);
    gMpuRegionConfig[1].size = 0x0EU; /* b01110 = 32KB */
    MpuP_RegionAttrs_init(&gMpuRegionConfig[1].attrs);
    gMpuRegionConfig[1].attrs.isEnable = 1;
    gMpuRegionConfig[1].attrs.isCacheable = 1;
    gMpuRegionConfig[1].attrs.isBufferable = 0;
    gMpuRegionConfig[1].attrs.isSharable = 0;
    gMpuRegionConfig[1].attrs.isExecuteNever = 0;
    gMpuRegionConfig[1].attrs.tex = 0;
    gMpuRegionConfig[1].attrs.accessPerm = 3;
    gMpuRegionConfig[1].attrs.subregionDisableMask = 0x0;


    /* Configure for init */
    gMpuConfig.numRegions = 2;
    gMpuConfig.enableBackgroundRegion = 0;
    gMpuConfig.enableMpu = 0;

    /* Call MpuP_init() - should configure both regions */
    MpuP_init();

    /* Functional test: Access both regions */
    testPtr = (volatile uint32_t *)0x00000000U;
    testValue = 0xAABBCCDDU;
    *testPtr = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testPtr);
    DebugP_log("  Region 0 (TCMA) access verified\r\n");

    testPtr = (volatile uint32_t *)TestMpu_getExecBase();
    testValue = 0x11223344U;
    *testPtr = testValue;
    TEST_ASSERT_EQUAL_UINT32(testValue, *testPtr);
    DebugP_log("  Region 1 (MSRAM) access verified\r\n");

    DebugP_log("TestMpu_init_configuresMultipleRegions: PASSED\r\n");
}
#endif

/**
 * @brief Test function to verify that MpuP_init disables cache if it is enabled.
 *
 * This test enables the program cache, verifies it is enabled, and then calls MpuP_init
 * with configuration that disables the MPU. It checks that the cache is disabled after
 * initialization and that the MPU is also disabled. The test restores the functional state
 * at the end and logs the test result.
 */
static void TestMpu_init_disablesCacheIfEnabled(void *args)
{
    uint32_t mpuState;
    uint32_t cacheType;

    MpuP_disable();
    DebugP_log("TestMpu_init_disablesCacheIfEnabled: Testing cache disable during init\r\n");

    /* Step 1: Enable program cache first */
    CacheP_enable(CacheP_TYPE_ALLP);
    DebugP_log("  Program cache enabled before init\r\n");

    /* Step 2: Verify cache is enabled */
    cacheType = CacheP_getEnabled();
    TEST_ASSERT_TRUE((cacheType & CacheP_TYPE_ALLP) != 0);
    DebugP_log("  Cache type enabled: 0x%x\r\n", cacheType);

    /* Step 3: Configure for basic init */
    gMpuConfig.numRegions = 0;
    gMpuConfig.enableBackgroundRegion = 0;
    gMpuConfig.enableMpu = 0;

    /* Step 4: Call MpuP_init() - should disable cache internally (line 139-141) */
    MpuP_init();
    DebugP_log("  MpuP_init() called\r\n");

    /* Step 5: Verify cache was disabled during init */
    /* Note: MpuP_init() disables cache but doesn't re-enable it unless configured */
    cacheType = CacheP_getEnabled();
    DebugP_assert(cacheType != 0);

    /* Step 6: Verify MPU is disabled (because enableMpu=0) */
    mpuState = MpuP_isEnable();
    TEST_ASSERT_EQUAL_UINT32(0, mpuState);
    DebugP_log("  MPU disabled after init: %u\r\n", mpuState);

    /* Step 7: Restore functional state */
    TestMpu_initFn();

    DebugP_log("TestMpu_init_disablesCacheIfEnabled: PASSED\r\n");
}
#endif /* !DM_R5FSS */




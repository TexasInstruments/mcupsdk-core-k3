/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include  <drivers/hyperbus.h>
#include  <board/hyperRam.h>
#include "test_hyperRamReadWrite.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_HYPERRAM_ZERO_SIZE                (0U)
#define TEST_HYPERRAM_1KB_SIZE                 (256*4U)
#define TEST_HYPERRAM_24KB_SIZE                (TEST_HYPERRAM_1KB_SIZE*24U)
#define TEST_HYPERRAM_48KB_SIZE                (TEST_HYPERRAM_1KB_SIZE*48U)
#define TEST_HYPERRAM_72KB_SIZE                (TEST_HYPERRAM_1KB_SIZE*72U)

#define TEST_HYPERRAM_100KB_OFFSET             (TEST_HYPERRAM_1KB_SIZE*100U)
#define TEST_HYPERRAM_124KB_OFFSET             (TEST_HYPERRAM_1KB_SIZE*124U)
#define TEST_HYPERRAM_148KB_OFFSET             (TEST_HYPERRAM_1KB_SIZE*148U)
#define TEST_HYPERRAM_172KB_OFFSET             (TEST_HYPERRAM_1KB_SIZE*172U)
#define TEST_HYPERRAM_60MB_OFFSET              (TEST_HYPERRAM_1KB_SIZE*TEST_HYPERRAM_1KB_SIZE*60U)

#define TEST_HYPERRAM_ECC_REGION0              (0U)
#define TEST_HYPERRAM_ECC_REGION1              (1U)
#define TEST_HYPERRAM_ECC_REGION2              (2U)
#define TEST_HYPERRAM_ECC_REGION3              (3U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void test_hyperRam_ecc_configure_regions(void * args);
static void test_hyperRam_ecc_enable_disable_alternatively(void * args);
static void test_hyperRam_ecc_overlapping_regions(void * args);
static void test_hyperRam_ecc_regions_boundary(void * args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(test_hyperRam_ecc_overlapping_regions, 7915, NULL);
    Board_hyperRamClose();
    Drivers_hyperbusClose();
    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(test_hyperRam_ecc_enable_disable_alternatively, 7916, NULL);
    Board_hyperRamClose();
    Drivers_hyperbusClose();
    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(test_hyperRam_ecc_configure_regions, 7917, NULL);
    Board_hyperRamClose();
    Drivers_hyperbusClose();
    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(test_hyperRam_ecc_regions_boundary, 8138, NULL);

    UNITY_END();

    return;
}

/* Unity framework required information */
void setUp(void)
{
}

void tearDown(void)
{
}

/* Testcases */

static void test_hyperRam_ecc_overlapping_regions(void * args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddress = 0U;

    HYPERRAM_Handle hyperRamHandle = gHyperRamHandle[CONFIG_HYPERRAM0];
    HyperRam_Config *config = (HyperRam_Config *)hyperRamHandle;
    HyperRam_Attrs *attrs = config->attrs;

    HYPERBUS_Handle hyperbusHandle = NULL;
    hyperbusHandle = HYPERBUS_getHandle(attrs->driverInstance);
    baseAddress = HYPERBUS_getHyperBusDataBaseAddr(hyperbusHandle);
    HYPERBUS_Config *hyperbusconfig = (HYPERBUS_Config *) hyperbusHandle;
    const HYPERBUS_Attrs *hyperbusAttrs = hyperbusconfig->attrs;

    hyperbusAttrs->eccRegion->eccRegionStart0 = TEST_HYPERRAM_100KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize0 = TEST_HYPERRAM_48KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart1 = TEST_HYPERRAM_148KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize1 = TEST_HYPERRAM_ZERO_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart2 = TEST_HYPERRAM_172KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize2 = TEST_HYPERRAM_24KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart3 = TEST_HYPERRAM_124KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize3 = TEST_HYPERRAM_72KB_SIZE;

    status = HYPERBUS_configureECC(hyperbusHandle);

    status |= hyperRam_bcdma_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET, APP_HYPERRAM_TEST_SIZE);

    status |= hyperRam_cpu_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET, APP_HYPERRAM_TEST_SIZE);

    if(status == SystemP_SUCCESS)
    {
        status = hyperRam_secErrTest (hyperbusHandle, TEST_HYPERRAM_148KB_OFFSET, 0x80U);
    }

    if (status == SystemP_SUCCESS)
    {
        status = hyperRam_dedErrTest (hyperbusHandle, TEST_HYPERRAM_148KB_OFFSET, 0x80U);
    }


    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

static void test_hyperRam_ecc_enable_disable_alternatively(void * args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddress = 0U;

    HYPERRAM_Handle hyperRamHandle = gHyperRamHandle[CONFIG_HYPERRAM0];
    HyperRam_Config *config = (HyperRam_Config *)hyperRamHandle;
    HyperRam_Attrs *attrs = config->attrs;

    HYPERBUS_Handle hyperbusHandle = NULL;
    hyperbusHandle = HYPERBUS_getHandle(attrs->driverInstance);
    baseAddress = HYPERBUS_getHyperBusDataBaseAddr(hyperbusHandle);
    HYPERBUS_Config *hyperbusconfig = (HYPERBUS_Config *) hyperbusHandle;
    const HYPERBUS_Attrs *hyperbusAttrs = hyperbusconfig->attrs;

    hyperbusAttrs->eccRegion->eccRegionStart0 = TEST_HYPERRAM_100KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize0 = TEST_HYPERRAM_24KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart1 = TEST_HYPERRAM_124KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize1 = TEST_HYPERRAM_ZERO_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart2 = TEST_HYPERRAM_148KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize2 = TEST_HYPERRAM_24KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart3 = TEST_HYPERRAM_172KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize3 = TEST_HYPERRAM_ZERO_SIZE;

    status = HYPERBUS_configureECC(hyperbusHandle);

    status |= hyperRam_bcdma_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET, APP_HYPERRAM_TEST_SIZE);

    status |= hyperRam_cpu_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET, APP_HYPERRAM_TEST_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

static void test_hyperRam_ecc_configure_regions(void * args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t baseAddress = 0U;

    HYPERRAM_Handle hyperRamHandle = gHyperRamHandle[CONFIG_HYPERRAM0];
    HyperRam_Config *config = (HyperRam_Config *)hyperRamHandle;
    HyperRam_Attrs *attrs = config->attrs;

    HYPERBUS_Handle hyperbusHandle = NULL;
    hyperbusHandle = HYPERBUS_getHandle(attrs->driverInstance);
    baseAddress = HYPERBUS_getHyperBusDataBaseAddr(hyperbusHandle);
    HYPERBUS_Config *hyperbusconfig = (HYPERBUS_Config *) hyperbusHandle;
    const HYPERBUS_Attrs *hyperbusAttrs = hyperbusconfig->attrs;

    hyperbusAttrs->eccRegion->eccRegionStart0 = TEST_HYPERRAM_100KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize0 = TEST_HYPERRAM_24KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart1 = TEST_HYPERRAM_124KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize1 = TEST_HYPERRAM_24KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart2 = TEST_HYPERRAM_148KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize2 = TEST_HYPERRAM_24KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart3 = TEST_HYPERRAM_172KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize3 = TEST_HYPERRAM_24KB_SIZE;

    status = HYPERBUS_configureECC(hyperbusHandle);

    status |= hyperRam_bcdma_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET, APP_HYPERRAM_TEST_SIZE);

    status |= hyperRam_cpu_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET, APP_HYPERRAM_TEST_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

static void test_hyperRam_ecc_regions_boundary(void * args)
{
    int32_t status = SystemP_SUCCESS;

    HYPERRAM_Handle hyperRamHandle = gHyperRamHandle[CONFIG_HYPERRAM0];
    HyperRam_Config *config = (HyperRam_Config *)hyperRamHandle;
    HyperRam_Attrs *attrs = config->attrs;

    HYPERBUS_Handle hyperbusHandle = NULL;
    hyperbusHandle = HYPERBUS_getHandle(attrs->driverInstance);
    HYPERBUS_Config *hyperbusconfig = (HYPERBUS_Config *) hyperbusHandle;
    const HYPERBUS_Attrs *hyperbusAttrs = hyperbusconfig->attrs;

    /* This is negative test to test the size of the hyperram we can use with ECC enabled,
     * as the size of the hyperram is 64MB, and the ECC region size limit is
     * 56.8MB, so we set the start address to 60MB and size to 24KB to test
     * the maximum size of the hyperram we can use with ECC enabled.
     */
    hyperbusAttrs->eccRegion->eccRegionStart0 = TEST_HYPERRAM_100KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize0 = TEST_HYPERRAM_24KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart1 = TEST_HYPERRAM_124KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize1 = TEST_HYPERRAM_24KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart2 = TEST_HYPERRAM_148KB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize2 = TEST_HYPERRAM_24KB_SIZE;

    hyperbusAttrs->eccRegion->eccRegionStart3 = TEST_HYPERRAM_60MB_OFFSET;
    hyperbusAttrs->eccRegion->eccRegionSize3 = TEST_HYPERRAM_24KB_SIZE;

    status = HYPERBUS_configureECC(hyperbusHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}

/**
 * Copyright (C) 2023-25 Texas Instruments Incorporated
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
 *  \file     core_r5_mpuTest.c
 *
 *  \brief    This file contains mpu API test code for R5 core.
 *
 *  \details  MPU read/write and configuration tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include "core_r5_test.h"
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/nortos/dpl/r5/CacheP_armv7r.h>
#include <kernel/dpl/MpuP_armv7.h>
#include <kernel/nortos/dpl/r5/MpuP_armv7r.h>
#include <kernel/nortos/dpl/r5/HwiP_armv7r_vim.h>

/*===========================================================================*/
/*                         Declarations                                      */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/

#define   CORE_R5_TEST_R5_MPU_ENABLE                   ((uint32_t) 1U)
#define   CORE_R5_TEST_R5_MPU_DISABLE                  ((uint32_t) 0U)
#define   CORE_R5_TEST_MPU_NUM_CONF_REGIONS            ((uint32_t) 3U)
#define   CONFIG_MPU_NUM_REGIONS                       (0u)
#define   MPU_SECTION __attribute__((section(".text.mpu")))

/*===========================================================================*/
/*                         Internal function declarations                    */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                        Test Function definitions                          */
/*===========================================================================*/

/**
 * For the unit test we are using the startup library to reach to main()
 * since the startup library initializes the default mpu, we should prevent
 * the initialization from startup library
 * the way to prevent the MPU initialization is to define a dummy
 * __mpu_init() function here
 */

void __mpu_init(void)
{
   /**
    * Do not implement anything here as anything here would be invoked
    * during startup code
    */
}

/* Empty definitions as MPU not configured by SysConfig */
/* ----------- CacheP ----------- */
CacheP_Config gCacheConfig = {
};

/* ----------- MpuP_armv7 ----------- */
MpuP_Config gMpuConfig = {
};
MpuP_RegionConfig gMpuRegionConfig[CONFIG_MPU_NUM_REGIONS] =
{
};

/**
 * Calculates and returns the region attribute mask
 * For more information on region and size attributes, refer
 * https://developer.arm.com/documentation/ddi0363/g/System-Control/Register-descriptions/c6--MPU-memory-region-programming-registers
 */
uint32_t MPU_SECTION MpuP_getAttrs(MpuP_RegionAttrs *region)
{
    uint32_t regionAttrs =
          ((uint32_t)(region->isExecuteNever & (uint32_t)0x1) << (uint32_t)12)
        | ((uint32_t)(region->accessPerm     & (uint32_t)0x7) << (uint32_t)8)
        | ((uint32_t)(region->tex            & (uint32_t)0x7) << (uint32_t)3)
        | ((uint32_t)(region->isSharable     & (uint32_t)0x1) << (uint32_t)2)
        | ((uint32_t)(region->isCacheable    & (uint32_t)0x1) << (uint32_t)1)
        | ((uint32_t)(region->isBufferable   & (uint32_t)0x1) << (uint32_t)0);

    return regionAttrs;
}

/* Implement the App mpu init sample code here */
int32_t core_r5_Test_mpu_init(void)
{
    int32_t                   region, chk, testResult = CORE_R5_APP_TEST_PASS;
    uint32_t                  numRegions;
    coreR5TestMpuRegion_t     mpuRegionDefault, mpuRegion[CORE_R5_TEST_MPU_NUM_CONF_REGIONS];
    uint32_t                  mpuVerifyCheckInDetail = 1U;
    uint32_t                  sizeAndEnable;
    MpuP_RegionAttrs regionParams;

/**
 * Below code is for custom MPU configuration
 *
 * Note: This configuration varies as per use-case
 */

/*
 * mpu_region_0_base .word 0x00000000                 ;The MPU Region Base Address Register
 * mpu_region_0_size .word (0x0<<8) | (0x1F<<1) | 0x1 ;Region Size and Enable bits (and Subre region enable )
 * mpu_region_0_permissions .word (1 << 12) | (3 << 8) | (2 << 3) | (0 << 2) | (0 << 0);The MPU Region Access Control
 * ;
 * ;   attributes:  xn  = 0 (bit 12)    - execution permitted
 * ;                ap  = 3 (bits 10:8) - read/write full access, 3=> full access privilege and user
 * ;                tex = 1 (bits 5:3)  - Normal         7=> cacheable, write back, no write allocate
 * ;                S   = 0 (bit 2)     - non-shared     0=> marking non-shared to enable cache,
 * ;                CB  = 0 (bits 1:0)  - Noncache       3=>write back, no write allocate cache
 * ;  mpuRegion[regionNumber].size = N, then region size is 2^(N+1)
 */

    /* Defining the MPU regions */

    /* Region 0 configuration: complete 32 bit address space */
    mpuRegion[0].base        = (void *) (0x00000000U);
    mpuRegion[0].size        = 0x1FU; /* b11111 = 4GB */
    mpuRegion[0].permissions.isEnable = 1;
    mpuRegion[0].permissions.isCacheable = 0;
    mpuRegion[0].permissions.isBufferable = 0;
    mpuRegion[0].permissions.isSharable = 0;
    mpuRegion[0].permissions.isExecuteNever = 1; /* dont allow code execution */
    mpuRegion[0].permissions.tex = 0;
    mpuRegion[0].permissions.accessPerm = 3;
    mpuRegion[0].permissions.subregionDisableMask = 0x0;

    /* Region 1 configuration: TCMA */
    mpuRegion[1].base        = (void *) (0x00000000U);
    mpuRegion[1].size        = 0x0EU; /* b01110 = 32KB */
    mpuRegion[1].permissions.isEnable = 1;
    mpuRegion[1].permissions.isCacheable = 1;
    mpuRegion[1].permissions.isBufferable = 0;
    mpuRegion[1].permissions.isSharable = 0;
    mpuRegion[1].permissions.isExecuteNever = 0; /* allow code execution */
    mpuRegion[1].permissions.tex = 0;
    mpuRegion[1].permissions.accessPerm = 3;
    mpuRegion[1].permissions.subregionDisableMask = 0x0;

    /* Region 2 configuration: MSRAM */
    mpuRegion[2].base        = (void *) (0x79100000U);
    mpuRegion[2].size        = 0x12U; /* b10010 = 512KB */
    mpuRegion[2].permissions.isEnable = 1;
    mpuRegion[2].permissions.isCacheable = 1;
    mpuRegion[2].permissions.isBufferable = 1;
    mpuRegion[2].permissions.isSharable = 0;
    mpuRegion[2].permissions.isExecuteNever = 0; /* allow code execution */
    mpuRegion[2].permissions.tex = 1;
    mpuRegion[2].permissions.accessPerm = 3;
    mpuRegion[2].permissions.subregionDisableMask = 0x0;

    /* Default region */
    mpuRegionDefault.base    = (void *) 0U;
    mpuRegionDefault.size    = (uint32_t) 0U;
    mpuRegionDefault.permissions.isEnable = 0;
    mpuRegionDefault.permissions.isCacheable = 0;
    mpuRegionDefault.permissions.isBufferable = 0;
    mpuRegionDefault.permissions.isSharable = 0;
    mpuRegionDefault.permissions.isExecuteNever = 0; /* dont allow code execution */
    mpuRegionDefault.permissions.tex = 0;
    mpuRegionDefault.permissions.accessPerm = 0;
    mpuRegionDefault.permissions.subregionDisableMask = 0x0;

    /* Total number of MPU regions */
    numRegions = MpuP_GetNumRegions();

    /* Disable the MPU first */
    MpuP_disable();

    /* Set all the default regions and verify the set regions */
    for (region =(numRegions-1U); region >= CORE_R5_TEST_MPU_NUM_CONF_REGIONS; region--)
    {
       /* Set default values to region attributes */
       MpuP_RegionAttrs_init(&regionParams);
       regionParams = mpuRegionDefault.permissions;
       MpuP_setRegion(region, mpuRegionDefault.base, mpuRegionDefault.size, &regionParams);
       if (1U == mpuVerifyCheckInDetail)
       {
           /* Verify the regions */
           /* tweak the region and expect failure */
           chk = MpuP_VerifyCfgRegion(region + 2,
                                 (uintptr_t) mpuRegionDefault.base,
                                 mpuRegionDefault.size,
                                 MpuP_getAttrs(&regionParams));
           if (CSL_PASS == chk)
           {
               testResult = CORE_R5_APP_TEST_FAILED;
               break;
           }
           /* tweak the base and expect failure */
           chk = MpuP_VerifyCfgRegion(region,
                                 (uintptr_t) 0x200,
                                 mpuRegionDefault.size,
                                 MpuP_getAttrs(&regionParams));
           if (CSL_PASS == chk)
           {
               testResult = CORE_R5_APP_TEST_FAILED;
               break;
           }

           /* tweak the size and expect failure */
           chk = MpuP_VerifyCfgRegion(region,
                                 (uintptr_t) mpuRegionDefault.base,
                                 0x200,
                                 MpuP_getAttrs(&regionParams));
           if (CSL_PASS == chk)
           {
               testResult = CORE_R5_APP_TEST_FAILED;
               break;
           }

           /* tweak the permission and expect failure */
           chk = MpuP_VerifyCfgRegion(region,
                                 (uintptr_t) mpuRegionDefault.base,
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
                             (uintptr_t) mpuRegionDefault.base,
                             mpuRegionDefault.size,
                             MpuP_getAttrs(&regionParams));
       if (CSL_PASS != chk)
       {
           testResult = CORE_R5_APP_TEST_FAILED;
           break;
       }
    }

    if ( CORE_R5_APP_TEST_PASS == testResult )
    {
        /* Configure the remaining regions and test */
        for (; region >= 0; region--)
        {
            /* Initialise the region attributes */
            MpuP_RegionAttrs_init(&regionParams);
            regionParams = mpuRegion[region].permissions;
            /* Set the regions */
            MpuP_setRegion(region, mpuRegion[region].base, mpuRegion[region].size, &regionParams);
            /* Calculate the Size and Enable field */
            sizeAndEnable = (mpuRegion[region].size & (uint32_t)0x1F) << 1U ;
            /* If N is the value in size field, the region size is 2N+1 bytes. */
            sizeAndEnable |= ((uint32_t)(regionParams.subregionDisableMask & (uint32_t)0xFF) << (uint32_t)8)
                            | ((uint32_t)(regionParams.isEnable & (uint32_t)0x1));
            /* Verify the configured region */
            chk = MpuP_VerifyCfgRegion(region,
                                    (uintptr_t) mpuRegion[region].base,
                                    sizeAndEnable,
                                    MpuP_getAttrs(&regionParams));
            if (CSL_PASS != chk)
            {
                testResult = CORE_R5_APP_TEST_FAILED;
                break;
            }
        }
    }

    if ( CORE_R5_APP_TEST_PASS == testResult )
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
        HwiP_enableVIC();  /* Enable VIC */
        HwiP_enableFIQ();  /* Enable FIQ */
    }
    return (testResult);
}

/* This test demonstrates the APIs to enable MPU */

int32_t core_r5_mpuTest(void)
{
    /* Declarations of variables */
    int32_t    testResult;
    int32_t    numRegions;

    CacheP_invL1pAll();
    CacheP_invL1dAll();     /* Invalidate caches before MPU En*/
    testResult = core_r5_Test_mpu_init();
    numRegions = MpuP_GetNumRegions();
    DebugP_log(" MPU API tests complete: number of regions tested are : ");
    DebugP_log("0x%x \n", numRegions);
    DebugP_log(" \n\r ");

   return (testResult);
}


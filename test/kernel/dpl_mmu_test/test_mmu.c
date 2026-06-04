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
 *  \file     test_mmu.c
 *
 *  \brief    This file contains mmu API test code for c75 and a53 core.
 *
 *  \details  MMU read/write and configuration tests
 **/

#include "test_mmu.h"

/* ========================================================================== */
/*                    Unity Framework Setup Functions                         */
/* ========================================================================== */

/* Setup function for Unity test framework */
void setUp(void)
{
   /* Cleaning */
   CacheP_wbInvAll(CacheP_TYPE_ALL);
   MmuP_disable();
   TestMmuP_barrier();
   TestMmuP_enableAndSync();
}

/* Teardown function for Unity test framework */
void tearDown(void)
{
    /* Restore a clean MMU/cache baseline between tests to avoid
     * cross-test alias/TLB/cache state leakage. */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();
    TestMmuP_enableAndSync();
}

/* ========================================================================== */
/*                          Main test function                                */
/* ========================================================================== */

void test_mmu_main(void *args)
{
    UNITY_BEGIN();
    /* Functional Tests */
    RUN_TEST(TestMmuP_enableDisableAndIsEnabled, 9984, NULL);
    RUN_TEST(TestMmuP_mapAligned4KbPage, 9989, NULL);
    RUN_TEST(TestMmuP_mapAligned8KbRegion, 9993, NULL);
    RUN_TEST(TestMmuP_mapAligned64KbRegion, 9995, NULL);
#if !defined(ENABLE_C75_CORE) /* exception dump/hang in c75 core  */
    RUN_TEST(TestMmuP_mapAligned2MbBlock, 9996, NULL);
    RUN_TEST(TestMmuP_mapAligned1GbBlock, 9997, NULL);
#endif /* !ENABLE_C75_CORE - exception dump/hang in c75 core  */
    RUN_TEST(TestMmuP_privilegedReadWriteUserNoAccess, 9998, NULL);
    RUN_TEST(TestMmuP_privilegedReadOnlyUserNoAccess, 9999, NULL);
    RUN_TEST(TestMmuP_privilegedAndUserReadWrite, 10000, NULL);
    RUN_TEST(TestMmuP_privilegedAndUserReadOnly, 10001, NULL);
#if !defined(ENABLE_C75_CORE) /* exception dump/hang in c75 core  */
    RUN_TEST(TestMmuP_executeAllowedForPrivilegedAndUser, 10002, NULL);
    RUN_TEST(TestMmuP_executePrivilegedOnly, 10003, NULL);
    RUN_TEST(TestMmuP_executeAcrossPageBoundary, 10004, NULL);
#endif /* !ENABLE_C75_CORE - exception dump/hang in c75 core  */
    RUN_TEST(TestMmuP_nonShareableSingleCoreReadWrite, 10005, NULL);
    RUN_TEST(TestMmuP_innerShareableSingleCoreReadWrite, 10006, NULL);
    RUN_TEST(TestMmuP_outerShareableSingleCoreReadWrite, 10007, NULL);
    RUN_TEST(TestMmuP_mairSlot0ReadWrite, 10008, NULL);
    RUN_TEST(TestMmuP_mairSlot1ReadWrite, 10009, NULL);
    RUN_TEST(TestMmuP_mairSlot2ReadWrite, 10010, NULL);
    RUN_TEST(TestMmuP_mairSlot3ReadWrite, 10013, NULL);
    RUN_TEST(TestMmuP_mairSlot4DeviceAccess, 10011, NULL);
    RUN_TEST(TestMmuP_mairSlot5ReadWrite, 10012, NULL);
    RUN_TEST(TestMmuP_globalMappingSingleContext, 10014, NULL);
    RUN_TEST(TestMmuP_nonGlobalMappingSingleContext, 10017, NULL);
    RUN_TEST(TestMmuP_overlappingSubsetReadBehavior, 10018, NULL);
    RUN_TEST(TestMmuP_nonOverlappingIndependentRegions, 10019, NULL);
    RUN_TEST(TestMmuP_overlappingReadOnlySubsetAndReadWriteOutside, 10020, NULL);

#if defined(ENABLE_MT_TESTS)/* Multithreaded Tests */
    RUN_TEST(TestMmuP_multithreadMappingOfAdjacentPages, 10094, NULL);
    RUN_TEST(TestMmuP_multithreadReadWriteWithinSinglePage, 10095, NULL);
    RUN_TEST(TestMmuP_multithreadPerTaskMapAttributeIsolation, 10096, NULL);
    RUN_TEST(TestMmuP_multithreadCacheMaintenanceOperations, 10097, NULL);
    RUN_TEST(TestMmuP_multithreadAliasCoherenceOnSamePA, 10098, NULL);
    RUN_TEST(TestMmuP_multithreadGlobalVsNonGlobalAliasAccess, 10099, NULL);
    RUN_TEST(TestMmuP_multithreadDeviceVsNormalAccessOrdering, 10100, NULL);
    RUN_TEST(TestMmuP_multithreadLargeBlockAccessAcrossPages, 10165, NULL);
    RUN_TEST(TestMmuP_multithreadOverlappingROSubsetVsRWOutside, 10166, NULL);
    RUN_TEST(TestMmuP_multithreadCacheMaintenanceAndAccess, 10167, NULL);
#endif

    UNITY_END();
}

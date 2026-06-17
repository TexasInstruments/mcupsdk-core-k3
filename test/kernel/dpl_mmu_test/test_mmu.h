/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/
#ifndef TEST_MMU_H
#define TEST_MMU_H

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/MmuP_armv8.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#if defined ENABLE_MT_TESTS
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>
#include "FreeRTOS.h"
#include "task.h"
#endif /* ENABLE_MT_TESTS */
#if defined ENABLE_C75_CORE
#include <kernel/nortos/dpl/c75/MmuP_c75.h>
#include <kernel/nortos/dpl/c75/CacheP_c75.h>
#endif /* ENABLE_C75_CORE */
#if defined ENABLE_A53_CORE
#include <kernel/nortos/dpl/a53/CacheP_armv8.h>
#endif /* ENABLE_A53_CORE */

/*===========================================================================*/
/*                               Macros                                      */
/*===========================================================================*/
/*
 * Test buffers used for MMU mapping tests. Align to 4KB so we can map pages cleanly.
 */
#define TEST_MMUP_PAGE_SIZE                             (4u * 1024u)
#define TEST_MMUP_8KB_SIZE                              (8u * 1024u)
#define TEST_MMUP_64KB_SIZE                             (64u * 1024u)
#define TEST_MMUP_2MB_SIZE                              (2u * 1024u * 1024u)
#define TEST_MMUP_1GB_SIZE                              (1u * 1024u * 1024u * 1024u)
#define TEST_MMUP_ALIGN_DOWN(val, align)                ((uintptr_t)(val) & ~((uintptr_t)(align) - 1u))
#define TEST_MMUP_EXEC_SIZE                             (TEST_MMUP_PAGE_SIZE)

/* Unique alias bases for new tests; keep 64KB aligned to be safe across cores */
#define TEST_MMUP_ALIAS_NONSHAREABLE_RW_4K              (0x90070000u)
#define TEST_MMUP_ALIAS_INNER_SHAREABLE_RW_4K           (0x90080000u)
#define TEST_MMUP_ALIAS_OUTER_SHAREABLE_RW_4K           (0x90090000u)
#define TEST_MMUP_ALIAS_MAIR0_RW_4K                     (0x900A0000u)
#define TEST_MMUP_ALIAS_MAIR1_RW_4K                     (0x900B0000u)
#define TEST_MMUP_ALIAS_MAIR2_RW_4K                     (0x900C0000u)
#define TEST_MMUP_ALIAS_MAIR3_RW_4K                     (0x900D0000u)
#define TEST_MMUP_ALIAS_DEVICE_MAIR4_RW_4K              (0x900E0000u)
#define TEST_MMUP_ALIAS_MAIR5_RW_4K                     (0x90160000u)
#define TEST_MMUP_ALIAS_NONGLOBAL_RW_4K                 (0x90170000u)
#define TEST_MMUP_ALIAS_DEVICE_PAIR_DEV_4K              (0x90180000u)
#define TEST_MMUP_ALIAS_OVERLAP_A_RW_8K                 (0x90190000u)
#define TEST_MMUP_ALIAS_OVERLAP_B_RW_4K                 (0x90198000u)
#define TEST_MMUP_ALIAS_NONOVERLAP_A_RW_4K              (0x901A0000u)
#define TEST_MMUP_ALIAS_NONOVERLAP_B_RW_64K             (0x901A8000u) /* non-overlapping 8KB apart */
#define TEST_MMUP_ALIAS_OVERLAP_RW_A_8K                 (0x901B0000u)
#define TEST_MMUP_ALIAS_OVERLAP_RO_B_4K                 (0x901B8000u) /* subset within A (4KB) */
#define TEST_MMUP_ALIAS_NORMAL_PAIR_NORM_4K             (0x901C0000u)
#define TEST_MMUP_ALIAS_SPARE_4K                        (0x901D0000u)
#define TEST_MMUP_ALIAS_ADJ_PAGE_A_4K                   (0x90100000u)
#define TEST_MMUP_ALIAS_ADJ_PAGE_B_4K                   (0x90121000u) /* adjacent 4KB page */
#define TEST_MMUP_ALIAS_SINGLE_PAGE_RW_4K               (0x90130000u)
#define TEST_MMUP_ALIAS_PER_TASK_A_4K                   (0x90140000u)
#define TEST_MMUP_ALIAS_PER_TASK_B_4K                   (0x90141000u)
#define TEST_MMUP_ALIAS_CACHE_MAINT_8K                  (0x90150000u)

#ifdef ENABLE_MT_TESTS
#define TEST_MMUP_MT_TASK_STACK_SIZE                    (128u * 1024u)
#define TEST_MMUP_MT_TASK_PRIO                          (2)
#endif /* ENABLE_MT_TESTS */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*
 * Test buffers used for MMU mapping tests. Align to 4KB so we can map pages cleanly.
 */
uint8_t TestMmuP_Buffer4K[TEST_MMUP_PAGE_SIZE] __attribute__((aligned(TEST_MMUP_PAGE_SIZE)));
uint8_t TestMmuP_Buffer8K[TEST_MMUP_8KB_SIZE] __attribute__((aligned(TEST_MMUP_PAGE_SIZE)));

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

inline void TestMmuP_barrier(void);

/* ========================================================================== */
/*                       Static Test Function Prototypes                      */
/* ========================================================================== */

/* Functional tests */
void TestMmuP_enableDisableAndIsEnabled(void *args);
void TestMmuP_mapAligned4KbPage(void *args);
void TestMmuP_mapAligned8KbRegion(void *args);
void TestMmuP_mapAligned64KbRegion(void *args);
void TestMmuP_mapAligned2MbBlock(void *args);
void TestMmuP_mapAligned1GbBlock(void *args);
void TestMmuP_privilegedReadWriteUserNoAccess(void *args);
#if !defined(ENABLE_C75_AM62AX)
void TestMmuP_privilegedReadOnlyUserNoAccess(void *args);
#endif
void TestMmuP_privilegedAndUserReadWrite(void *args);
#if !defined(ENABLE_C75_AM62AX)
void TestMmuP_privilegedAndUserReadOnly(void *args);
#endif

#if !defined(ENABLE_C75_CORE)
void TestMmuP_executeAllowedForPrivilegedAndUser(void *args);
void TestMmuP_executePrivilegedOnly(void *args);
void TestMmuP_executeAcrossPageBoundary(void *args);
#endif /* !ENABLE_C75_CORE */

void TestMmuP_nonShareableSingleCoreReadWrite(void *args);
void TestMmuP_innerShareableSingleCoreReadWrite(void *args);
void TestMmuP_outerShareableSingleCoreReadWrite(void *args);
void TestMmuP_mairSlot0ReadWrite(void *args);
void TestMmuP_mairSlot1ReadWrite(void *args);
void TestMmuP_mairSlot2ReadWrite(void *args);
void TestMmuP_mairSlot3ReadWrite(void *args);
void TestMmuP_mairSlot4DeviceAccess(void *args);
void TestMmuP_mairSlot5ReadWrite(void *args);
void TestMmuP_globalMappingSingleContext(void *args);
void TestMmuP_nonGlobalMappingSingleContext(void *args);
void TestMmuP_overlappingSubsetReadBehavior(void *args);
void TestMmuP_nonOverlappingIndependentRegions(void *args);
void TestMmuP_overlappingReadOnlySubsetAndReadWriteOutside(void *args);

#if defined(ENABLE_MT_TESTS)
/* Multithreaded tests */
void TestMmuP_multithreadMappingOfAdjacentPages(void *args);
void TestMmuP_multithreadReadWriteWithinSinglePage(void *args);
void TestMmuP_multithreadPerTaskMapAttributeIsolation(void *args);
void TestMmuP_multithreadCacheMaintenanceOperations(void *args);
void TestMmuP_multithreadAliasCoherenceOnSamePA(void *args);
void TestMmuP_multithreadGlobalVsNonGlobalAliasAccess(void *args);
void TestMmuP_multithreadDeviceVsNormalAccessOrdering(void *args);
void TestMmuP_multithreadLargeBlockAccessAcrossPages(void *args);
void TestMmuP_multithreadOverlappingROSubsetVsRWOutside(void *args);
void TestMmuP_multithreadCacheMaintenanceAndAccess(void *args);
#endif /* ENABLE_MT_TESTS */

/* Helper: Add a portable barrier helper to avoid AArch64 asm on C7x */
inline void TestMmuP_barrier(void)
{
#if defined(ENABLE_A53_CORE)
    __asm__ volatile ("dsb sy");
    __asm__ volatile ("isb");
#else
    CacheP_wbInvAll(CacheP_TYPE_ALL);
#endif
}

inline void TestMmuP_enableAndSync(void)
{
    MmuP_enable();
    TestMmuP_barrier();
#if defined(ENABLE_C75_CORE)
    /* C75: purge stale translations after descriptor changes */
    MmuP_tlbInvAll(0);
#endif
}

#endif /*TEST_MMU_H*/

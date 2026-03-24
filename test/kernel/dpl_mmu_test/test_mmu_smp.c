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
 * @file test_mmu_smp.c
 * @brief MMU SMP tests: verifies alias mappings, cache maintenance and
 *        per-task attribute isolation across both A53 cores.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <unity.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/MmuP_armv8.h>

/* ========================================================================== */
/*                                   Macros                                   */
/* ========================================================================== */

/* 4KB page size for alias mappings */
#define TEST_MMUP_SMP_PAGE_SIZE            (4U * 1024U)

/* SMP worker task parameters */
#define TEST_MMUP_SMP_TASK_STACK_SIZE      (256u * 1024U)
#define TEST_MMUP_SMP_TASK_PRIO            (2)

/* Virtual address alias window — must not overlap any existing mapping */
#define TEST_MMUP_SMP_ALIAS_PAGE_A         (0x90010000u) /* adjacent page A */
#define TEST_MMUP_SMP_ALIAS_PAGE_B         (0x90011000u) /* adjacent page B */
#define TEST_MMUP_SMP_ALIAS_SINGLE_PAGE    (0x90012000u) /* single 4KB page */
#define TEST_MMUP_SMP_ALIAS_PER_TASK_A     (0x90013000u) /* per-task attr alias A */
#define TEST_MMUP_SMP_ALIAS_PER_TASK_B     (0x90014000u) /* per-task attr alias B */
#define TEST_MMUP_SMP_ALIAS_CACHE_REGION   (0x90015000u) /* cache maintenance region */

/* ========================================================================== */
/*                        Internal Helper Declarations                        */
/* ========================================================================== */

static inline void TestMmuP_smpTlbiBarrier(void);
static void TestMmuP_smpWritePattern(volatile uint8_t *ptr, uint32_t size, uint8_t seed);
static void TestMmuP_smpVerifyPattern(volatile uint8_t *ptr, uint32_t size, uint8_t seed);

/* ========================================================================== */
/*                              Global Variables                              */
/* ========================================================================== */

/* Semaphore: main posts once per worker to release them simultaneously */
static SemaphoreP_Object TestMmuP_SmpStartSem;
/* Semaphore: each worker posts once when its work is complete */
static SemaphoreP_Object TestMmuP_SmpDoneSem;
/* Semaphore: workers block here after posting done, so TaskP_destruct is safe */
static SemaphoreP_Object TestMmuP_SmpParkSem;

/* Worker task objects and stacks */
static TaskP_Object TestMmuP_SmpWorkerTaskA;
static TaskP_Object TestMmuP_SmpWorkerTaskB;
static uint8_t TestMmuP_SmpWorkerStackA[TEST_MMUP_SMP_TASK_STACK_SIZE] __attribute__((aligned(32)));
static uint8_t TestMmuP_SmpWorkerStackB[TEST_MMUP_SMP_TASK_STACK_SIZE] __attribute__((aligned(32)));

/* Backing DDR buffers — physical pages mapped via alias VAs, aligned to 4KB */
static uint8_t TestMmuP_SmpAdjPageBuf[2U * TEST_MMUP_SMP_PAGE_SIZE] __attribute__((aligned(TEST_MMUP_SMP_PAGE_SIZE)));
static uint8_t TestMmuP_SmpSinglePageBuf[TEST_MMUP_SMP_PAGE_SIZE]    __attribute__((aligned(TEST_MMUP_SMP_PAGE_SIZE)));
static uint8_t TestMmuP_SmpPerTaskBufA[TEST_MMUP_SMP_PAGE_SIZE]      __attribute__((aligned(TEST_MMUP_SMP_PAGE_SIZE)));
static uint8_t TestMmuP_SmpPerTaskBufB[TEST_MMUP_SMP_PAGE_SIZE]      __attribute__((aligned(TEST_MMUP_SMP_PAGE_SIZE)));
static uint8_t TestMmuP_SmpCacheRegionBuf[TEST_MMUP_SMP_PAGE_SIZE]   __attribute__((aligned(TEST_MMUP_SMP_PAGE_SIZE)));

/* ========================================================================== */
/*                       Static Test Function Prototypes                      */
/* ========================================================================== */

static void TestMmuP_smpMappingOfAdjacentPages(void *args);
static void TestMmuP_smpReadWriteWithinSinglePage(void *args);
static void TestMmuP_smpPerTaskMapAttributeIsolation(void *args);
static void TestMmuP_smpCacheMaintenanceOperations(void *args);

/* ========================================================================== */
/*                           Worker Task Prototypes                           */
/* ========================================================================== */

static void TestMmuP_smpAdjacentPageWriterA(void *arg);
static void TestMmuP_smpAdjacentPageWriterB(void *arg);

static void TestMmuP_smpSinglePageLowerHalfWriter(void *arg);
static void TestMmuP_smpSinglePageUpperHalfWriter(void *arg);

static void TestMmuP_smpPerTaskAttrWriterA(void *arg);
static void TestMmuP_smpPerTaskAttrWriterB(void *arg);

static void TestMmuP_smpCacheRegionWriter(void *arg);
static void TestMmuP_smpCacheRegionReader(void *arg);

/* ========================================================================== */
/*                               Helper Functions                             */
/* ========================================================================== */

/**
 * Full TLB maintenance barrier: DSB+TLBI VMALLE1IS+DSB+ISB.
 * Ensures page-table writes are visible to both cores before any access.
 */
static inline void TestMmuP_smpTlbiBarrier(void)
{
    __asm__ volatile("dsb ishst");
    __asm__ volatile("tlbi vmalle1is");
    __asm__ volatile("dsb ish");
    __asm__ volatile("isb");
}

/** Write a deterministic incrementing pattern starting at seed into [ptr, ptr+size). */
static void TestMmuP_smpWritePattern(volatile uint8_t *ptr, uint32_t size, uint8_t seed)
{
    for (uint32_t i = 0; i < size; i+=1)
	 ptr[i] = (uint8_t)(seed + (uint8_t)(i & 0xFFu) + (uint8_t)((i >> 8) & 0xFFu));
}

/** Verify the deterministic pattern written by TestMmuP_smpWritePattern. */
static void TestMmuP_smpVerifyPattern(volatile uint8_t *ptr, uint32_t size, uint8_t seed)
{
    for (uint32_t i = 0; i < size; i+=1)
        TEST_ASSERT_EQUAL_UINT8((uint8_t)(seed + (uint8_t)(i & 0xFFu) + (uint8_t)((i >> 8) & 0xFFu)), ptr[i]);
}

/* ========================================================================== */
/*                        SMP Test: Adjacent Pages                            */
/* ========================================================================== */

static void TestMmuP_smpAdjacentPageWriterA(void *arg)
{
    (void)arg;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpStartSem, SystemP_WAIT_FOREVER));
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_PAGE_A;
    TestMmuP_smpWritePattern(va, TEST_MMUP_SMP_PAGE_SIZE, 0xA1u);
    SemaphoreP_post(&TestMmuP_SmpDoneSem);
    SemaphoreP_pend(&TestMmuP_SmpParkSem, SystemP_WAIT_FOREVER);
}

static void TestMmuP_smpAdjacentPageWriterB(void *arg)
{
    (void)arg;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpStartSem, SystemP_WAIT_FOREVER));
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_PAGE_B;
    TestMmuP_smpWritePattern(va, TEST_MMUP_SMP_PAGE_SIZE, 0xB1u);
    SemaphoreP_post(&TestMmuP_SmpDoneSem);
    SemaphoreP_pend(&TestMmuP_SmpParkSem, SystemP_WAIT_FOREVER);
}

static void TestMmuP_smpMappingOfAdjacentPages(void *args)
{
    (void)args;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpStartSem, 0, 2));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpDoneSem,  0, 2));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpParkSem,  0, 2));

    TaskP_Params pr;
    TaskP_Params_init(&pr);
    pr.priority  = TEST_MMUP_SMP_TASK_PRIO;
    pr.name      = "TestMmuP_smpAdjacentPageWriterA";
    pr.stack     = TestMmuP_SmpWorkerStackA;
    pr.stackSize = TEST_MMUP_SMP_TASK_STACK_SIZE;
    pr.taskMain  = TestMmuP_smpAdjacentPageWriterA;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SmpWorkerTaskA, &pr));

    TaskP_Params_init(&pr);
    pr.priority  = TEST_MMUP_SMP_TASK_PRIO;
    pr.name      = "TestMmuP_smpAdjacentPageWriterB";
    pr.stack     = TestMmuP_SmpWorkerStackB;
    pr.stackSize = TEST_MMUP_SMP_TASK_STACK_SIZE;
    pr.taskMain  = TestMmuP_smpAdjacentPageWriterB;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SmpWorkerTaskB, &pr));

    SemaphoreP_post(&TestMmuP_SmpStartSem);
    SemaphoreP_post(&TestMmuP_SmpStartSem);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpDoneSem, SystemP_WAIT_FOREVER));

    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_PAGE_A;
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_PAGE_B;
    TestMmuP_smpVerifyPattern(vaA, TEST_MMUP_SMP_PAGE_SIZE, 0xA1u);
    TestMmuP_smpVerifyPattern(vaB, TEST_MMUP_SMP_PAGE_SIZE, 0xB1u);


    SemaphoreP_post(&TestMmuP_SmpParkSem);
    SemaphoreP_post(&TestMmuP_SmpParkSem);
    TaskP_destruct(&TestMmuP_SmpWorkerTaskA);
    TaskP_destruct(&TestMmuP_SmpWorkerTaskB);
    SemaphoreP_destruct(&TestMmuP_SmpParkSem);
    SemaphoreP_destruct(&TestMmuP_SmpStartSem);
    SemaphoreP_destruct(&TestMmuP_SmpDoneSem);
}

/* ========================================================================== */
/*                    SMP Test: Single Page Split Write                       */
/* ========================================================================== */

static void TestMmuP_smpSinglePageLowerHalfWriter(void *arg)
{
    (void)arg;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpStartSem, SystemP_WAIT_FOREVER));
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_SINGLE_PAGE;
    uint32_t half = TEST_MMUP_SMP_PAGE_SIZE / 2U;
    TestMmuP_smpWritePattern(va, half, 0xC1u);
    SemaphoreP_post(&TestMmuP_SmpDoneSem);
    SemaphoreP_pend(&TestMmuP_SmpParkSem, SystemP_WAIT_FOREVER);
}

static void TestMmuP_smpSinglePageUpperHalfWriter(void *arg)
{
    (void)arg;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpStartSem, SystemP_WAIT_FOREVER));
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_SINGLE_PAGE;
    uint32_t half = TEST_MMUP_SMP_PAGE_SIZE / 2U;
    TestMmuP_smpWritePattern(va + half, half, 0xC2u);
    SemaphoreP_post(&TestMmuP_SmpDoneSem);
    SemaphoreP_pend(&TestMmuP_SmpParkSem, SystemP_WAIT_FOREVER);
}

static void TestMmuP_smpReadWriteWithinSinglePage(void *args)
{
    (void)args;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpStartSem, 0, 2));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpDoneSem,  0, 2));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpParkSem,  0, 2));

    TaskP_Params pr;
    TaskP_Params_init(&pr);
    pr.priority  = TEST_MMUP_SMP_TASK_PRIO;
    pr.name      = "TestMmuP_smpSinglePageLowerHalfWriter";
    pr.stack     = TestMmuP_SmpWorkerStackA;
    pr.stackSize = TEST_MMUP_SMP_TASK_STACK_SIZE;
    pr.taskMain  = TestMmuP_smpSinglePageLowerHalfWriter;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SmpWorkerTaskA, &pr));

    TaskP_Params_init(&pr);
    pr.priority  = TEST_MMUP_SMP_TASK_PRIO;
    pr.name      = "TestMmuP_smpSinglePageUpperHalfWriter";
    pr.stack     = TestMmuP_SmpWorkerStackB;
    pr.stackSize = TEST_MMUP_SMP_TASK_STACK_SIZE;
    pr.taskMain  = TestMmuP_smpSinglePageUpperHalfWriter;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SmpWorkerTaskB, &pr));

    SemaphoreP_post(&TestMmuP_SmpStartSem);
    SemaphoreP_post(&TestMmuP_SmpStartSem);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpDoneSem, SystemP_WAIT_FOREVER));

    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_SINGLE_PAGE;
    uint32_t half = TEST_MMUP_SMP_PAGE_SIZE / 2U;
    TestMmuP_smpVerifyPattern(va,        half, 0xC1u);
    TestMmuP_smpVerifyPattern(va + half, half, 0xC2u);

    SemaphoreP_post(&TestMmuP_SmpParkSem);
    SemaphoreP_post(&TestMmuP_SmpParkSem);
    TaskP_destruct(&TestMmuP_SmpWorkerTaskA);
    TaskP_destruct(&TestMmuP_SmpWorkerTaskB);
    SemaphoreP_destruct(&TestMmuP_SmpParkSem);
    SemaphoreP_destruct(&TestMmuP_SmpStartSem);
    SemaphoreP_destruct(&TestMmuP_SmpDoneSem);
}

/* ========================================================================== */
/*                 SMP Test: Per-Task Mapping Attribute Isolation             */
/* ========================================================================== */

static void TestMmuP_smpPerTaskAttrWriterA(void *arg)
{
    (void)arg;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpStartSem, SystemP_WAIT_FOREVER));
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_PER_TASK_A;
    TestMmuP_smpWritePattern(va, TEST_MMUP_SMP_PAGE_SIZE, 0xD1u);
    SemaphoreP_post(&TestMmuP_SmpDoneSem);
    SemaphoreP_pend(&TestMmuP_SmpParkSem, SystemP_WAIT_FOREVER);
}

static void TestMmuP_smpPerTaskAttrWriterB(void *arg)
{
    (void)arg;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpStartSem, SystemP_WAIT_FOREVER));
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_PER_TASK_B;
    TestMmuP_smpWritePattern(va, TEST_MMUP_SMP_PAGE_SIZE, 0xD2u);
    SemaphoreP_post(&TestMmuP_SmpDoneSem);
    SemaphoreP_pend(&TestMmuP_SmpParkSem, SystemP_WAIT_FOREVER);
}

static void TestMmuP_smpPerTaskMapAttributeIsolation(void *args)
{
    (void)args;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpStartSem, 0, 2));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpDoneSem,  0, 2));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpParkSem,  0, 2));

    TaskP_Params pr;
    TaskP_Params_init(&pr);
    pr.priority  = TEST_MMUP_SMP_TASK_PRIO;
    pr.name      = "TestMmuP_smpPerTaskAttrWriterA";
    pr.stack     = TestMmuP_SmpWorkerStackA;
    pr.stackSize = TEST_MMUP_SMP_TASK_STACK_SIZE;
    pr.taskMain  = TestMmuP_smpPerTaskAttrWriterA;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SmpWorkerTaskA, &pr));

    TaskP_Params_init(&pr);
    pr.priority  = TEST_MMUP_SMP_TASK_PRIO;
    pr.name      = "TestMmuP_smpPerTaskAttrWriterB";
    pr.stack     = TestMmuP_SmpWorkerStackB;
    pr.stackSize = TEST_MMUP_SMP_TASK_STACK_SIZE;
    pr.taskMain  = TestMmuP_smpPerTaskAttrWriterB;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SmpWorkerTaskB, &pr));

    SemaphoreP_post(&TestMmuP_SmpStartSem);
    SemaphoreP_post(&TestMmuP_SmpStartSem);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpDoneSem, SystemP_WAIT_FOREVER));

    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_PER_TASK_A;
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_PER_TASK_B;
    TestMmuP_smpVerifyPattern(vaA, TEST_MMUP_SMP_PAGE_SIZE, 0xD1u);
    TestMmuP_smpVerifyPattern(vaB, TEST_MMUP_SMP_PAGE_SIZE, 0xD2u);

    SemaphoreP_post(&TestMmuP_SmpParkSem);
    SemaphoreP_post(&TestMmuP_SmpParkSem);
    TaskP_destruct(&TestMmuP_SmpWorkerTaskA);
    TaskP_destruct(&TestMmuP_SmpWorkerTaskB);
    SemaphoreP_destruct(&TestMmuP_SmpParkSem);
    SemaphoreP_destruct(&TestMmuP_SmpStartSem);
    SemaphoreP_destruct(&TestMmuP_SmpDoneSem);
}

/* ========================================================================== */
/*                SMP Test: Cache Maintenance Operations                      */
/* ========================================================================== */

static void TestMmuP_smpCacheRegionWriter(void *arg)
{
    (void)arg;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpStartSem, SystemP_WAIT_FOREVER));
    void *va = (void *)TEST_MMUP_SMP_ALIAS_CACHE_REGION;
    TestMmuP_smpWritePattern((volatile uint8_t *)va, TEST_MMUP_SMP_PAGE_SIZE, 0xE1u);
    SemaphoreP_post(&TestMmuP_SmpDoneSem);
    SemaphoreP_pend(&TestMmuP_SmpParkSem, SystemP_WAIT_FOREVER);
}

static void TestMmuP_smpCacheRegionReader(void *arg)
{
    (void)arg;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpStartSem, SystemP_WAIT_FOREVER));
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_CACHE_REGION;
    /* Touch each cache line to exercise the mapping on this core */
    for (uint32_t i = 0; i < TEST_MMUP_SMP_PAGE_SIZE; i += 64U)
        (void)va[i];
    SemaphoreP_post(&TestMmuP_SmpDoneSem);
    SemaphoreP_pend(&TestMmuP_SmpParkSem, SystemP_WAIT_FOREVER);
}

static void TestMmuP_smpCacheMaintenanceOperations(void *args)
{
    (void)args;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpStartSem, 0, 2));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpDoneSem,  0, 2));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_SmpParkSem,  0, 2));

    TaskP_Params pr;
    TaskP_Params_init(&pr);
    pr.priority  = TEST_MMUP_SMP_TASK_PRIO;
    pr.name      = "TestMmuP_smpCacheRegionWriter";
    pr.stack     = TestMmuP_SmpWorkerStackA;
    pr.stackSize = TEST_MMUP_SMP_TASK_STACK_SIZE;
    pr.taskMain  = TestMmuP_smpCacheRegionWriter;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SmpWorkerTaskA, &pr));

    TaskP_Params_init(&pr);
    pr.priority  = TEST_MMUP_SMP_TASK_PRIO;
    pr.name      = "TestMmuP_smpCacheRegionReader";
    pr.stack     = TestMmuP_SmpWorkerStackB;
    pr.stackSize = TEST_MMUP_SMP_TASK_STACK_SIZE;
    pr.taskMain  = TestMmuP_smpCacheRegionReader;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SmpWorkerTaskB, &pr));

    SemaphoreP_post(&TestMmuP_SmpStartSem);
    SemaphoreP_post(&TestMmuP_SmpStartSem);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SmpDoneSem, SystemP_WAIT_FOREVER));

    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_SMP_ALIAS_CACHE_REGION;
    TestMmuP_smpVerifyPattern(va, TEST_MMUP_SMP_PAGE_SIZE, 0xE1u);

    SemaphoreP_post(&TestMmuP_SmpParkSem);
    SemaphoreP_post(&TestMmuP_SmpParkSem);
    TaskP_destruct(&TestMmuP_SmpWorkerTaskA);
    TaskP_destruct(&TestMmuP_SmpWorkerTaskB);
    SemaphoreP_destruct(&TestMmuP_SmpParkSem);
    SemaphoreP_destruct(&TestMmuP_SmpStartSem);
    SemaphoreP_destruct(&TestMmuP_SmpDoneSem);
}

/* ========================================================================== */
/*                        Unity Framework Functions                           */
/* ========================================================================== */

void setUp(void)
{
   TaskP_loadResetAll();
}

void tearDown(void)
{
    /* empty */
}

/**
 *  \brief   Main entry point for MMU SMP tests.
 *
 *  All MmuP_map calls are performed here before UNITY_BEGIN(), while only
 *  the main task is running.  MmuP_map modifies shared page tables with the
 *  per-core MMU disabled; calling it while the other core is running with its
 *  MMU enabled risks a synchronous fault on that core.  Mapping everything
 *  upfront — followed by a single broadcast TLBI — avoids this race entirely.
 *
 *  \param args  Unused argument passed by the FreeRTOS task wrapper.
 */
void test_mmu_smp_main(void *args)
{
    int32_t status;
    MmuP_MapAttrs attrs, attrsA, attrsB, attrsC;

    CacheP_wbInvAll(CacheP_TYPE_ALL);

    /* Common cacheable-normal inner-shareable attributes (tests 1, 2, 4) */
    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.attrIndx   = MMUP_ATTRINDX_MAIR4;
    attrs.shareable  = MMUP_SHARABLE_INNER;
    attrs.global     = 1;

    /* Test 1: adjacent pages */
    status = MmuP_map(TEST_MMUP_SMP_ALIAS_PAGE_A,
                      (uintptr_t)TestMmuP_SmpAdjPageBuf,
                      TEST_MMUP_SMP_PAGE_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = MmuP_map(TEST_MMUP_SMP_ALIAS_PAGE_B,
                      (uintptr_t)TestMmuP_SmpAdjPageBuf + TEST_MMUP_SMP_PAGE_SIZE,
                      TEST_MMUP_SMP_PAGE_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Test 2: single page split write */
    status = MmuP_map(TEST_MMUP_SMP_ALIAS_SINGLE_PAGE,
                      (uintptr_t)TestMmuP_SmpSinglePageBuf,
                      TEST_MMUP_SMP_PAGE_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Test 3: per-task attribute isolation — two different MAIR slots */
    MmuP_MapAttrs_init(&attrsA);
    attrsA.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrsA.attrIndx   = MMUP_ATTRINDX_MAIR4;
    attrsA.shareable  = MMUP_SHARABLE_INNER;
    attrsA.global     = 1;

    MmuP_MapAttrs_init(&attrsB);
    attrsB.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrsB.attrIndx   = MMUP_ATTRINDX_MAIR6;
    attrsB.shareable  = MMUP_SHARABLE_INNER;
    attrsB.global     = 1;

    MmuP_MapAttrs_init(&attrsC);
    attrsC.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrsC.attrIndx   = MMUP_ATTRINDX_MAIR0;  // ← CACHEABLE
    attrsC.shareable  = MMUP_SHARABLE_INNER;
    attrsC.global     = 1;

    status = MmuP_map(TEST_MMUP_SMP_ALIAS_PER_TASK_A,
                      (uintptr_t)TestMmuP_SmpPerTaskBufA,
                      TEST_MMUP_SMP_PAGE_SIZE, &attrsA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = MmuP_map(TEST_MMUP_SMP_ALIAS_PER_TASK_B,
                      (uintptr_t)TestMmuP_SmpPerTaskBufB,
                      TEST_MMUP_SMP_PAGE_SIZE, &attrsB);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Test 4: cache maintenance region */
    status = MmuP_map(TEST_MMUP_SMP_ALIAS_CACHE_REGION,
                      (uintptr_t)TestMmuP_SmpCacheRegionBuf,
                      TEST_MMUP_SMP_PAGE_SIZE, &attrsC);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    /*
     * Broadcast TLB invalidate to inner-shareable domain so that core 1
     * sees all new mappings before any worker task accesses the alias VAs.
     */
    TestMmuP_smpTlbiBarrier();

    UNITY_BEGIN();
    RUN_TEST(TestMmuP_smpMappingOfAdjacentPages,       11656, NULL);
    RUN_TEST(TestMmuP_smpReadWriteWithinSinglePage,    11657, NULL);
    RUN_TEST(TestMmuP_smpPerTaskMapAttributeIsolation, 11658, NULL);
    RUN_TEST(TestMmuP_smpCacheMaintenanceOperations,   11659, NULL);
    UNITY_END();
}

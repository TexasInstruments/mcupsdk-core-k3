#include "test_mmu.h"

#ifndef TEST_MULTI_THREAD_MMU
#define TEST_MULTI_THREAD_MMU

#if defined(ENABLE_MT_TESTS)
static uint8_t TestMmuP_Buffer64K[TEST_MMUP_64KB_SIZE] __attribute__((aligned(TEST_MMUP_64KB_SIZE)));

/* ========================================================================== */
/*                        Internal Function Definitions                       */
/* ========================================================================== */
/* Helper: write a deterministic byte pattern into a buffer */

static void TestMmuP_writePattern(volatile uint8_t *ptr, uint32_t size, uint8_t seed)
{
    uint32_t i;
    for (i = 0; i < size; i++)
    {
        ptr[i] = (uint8_t)(seed + (uint8_t)i);
    }
}

/* Helper: verify buffer contents match expected pattern */
static void TestMmuP_checkPattern(volatile uint8_t *ptr, uint32_t size, uint8_t seed)
{
    uint32_t i;
    for (i= 0; i < size; i++)
    {
        TEST_ASSERT_EQUAL_UINT8((uint8_t)(seed + (uint8_t)i), ptr[i]);
    }
}
#endif

#ifdef ENABLE_MT_TESTS
/* DPL-based synchronization and task objects */
static SemaphoreP_Object TestMmuP_PagePairTaskADoneSem, TestMmuP_PagePairTaskBDoneSem;
static SemaphoreP_Object TestMmuP_SinglePageHalfADoneSem, TestMmuP_SinglePageHalfBDoneSem;
static SemaphoreP_Object TestMmuP_PerTaskAttrDoneSem;              /* counting, initial 0, max 2 */
static SemaphoreP_Object TestMmuP_CacheMaintSyncSem, TestMmuP_CacheMaintDoneSem;
static SemaphoreP_Object TestMmuP_AliasCoherenceTaskADoneSem, TestMmuP_AliasCoherenceTaskBDoneSem;          /* alias coherence */
static SemaphoreP_Object TestMmuP_GlobalVsNonGlobalSyncSem;                  /* global vs non-global sync */
static SemaphoreP_Object TestMmuP_GlobalVsNonGlobalDoneSem;                  /* completion counting */
static SemaphoreP_Object TestMmuP_DeviceVsNormalSyncSem;                  /* device vs normal sync */
static SemaphoreP_Object TestMmuP_DeviceVsNormalDoneSem;                  /* completion counting */
static SemaphoreP_Object TestMmuP_OverlapSubsetROSemSync;       /* start reader after writer publishes */
static SemaphoreP_Object TestMmuP_OverlapSubsetROSemWriterDone; /* writer completion */
static SemaphoreP_Object TestMmuP_OverlapSubsetROSemReaderDone; /* reader completion */

static TaskP_Object TestMmuP_PagePairTaskA, TestMmuP_PagePairTaskB;
static TaskP_Object TestMmuP_SinglePageTaskA, TestMmuP_SinglePageTaskB;
static TaskP_Object TestMmuP_PerTaskAttrTaskA, TestMmuP_PerTaskAttrTaskB;
static TaskP_Object TestMmuP_CacheMaintTaskA, TestMmuP_CacheMaintTaskB;
static TaskP_Object TestMmuP_AliasCoherenceTaskA, TestMmuP_AliasCoherenceTaskB;
static TaskP_Object TestMmuP_GlobalWriterTask, TestMmuP_NonGlobalReaderTask;
static TaskP_Object TestMmuP_DeviceWriterTask, TestMmuP_NormalReaderTask;
static TaskP_Object TestMmuP_OverlapOutsideWriterTask, TestMmuP_OverlapSubsetReaderTask;

static uint8_t TestMmuP_PagePairTaskAStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
static uint8_t TestMmuP_PagePairTaskBStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));

static uint8_t TestMmuP_SinglePageTaskAStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
static uint8_t TestMmuP_SinglePageTaskBStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));

static uint8_t TestMmuP_PerTaskAttrTaskAStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
static uint8_t TestMmuP_PerTaskAttrTaskBStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));

static uint8_t TestMmuP_CacheMaintTaskAStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
static uint8_t TestMmuP_CacheMaintTaskBStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));

static uint8_t TestMmuP_OverlapOutsideWriterTaskStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
static uint8_t TestMmuP_OverlapSubsetReaderTaskStack[TEST_MMUP_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));

/* Reuse aliases for other MT tests to limit .bss */
#define TestMmuP_AliasCoherenceTaskAStack    TestMmuP_PagePairTaskAStack
#define TestMmuP_AliasCoherenceTaskBStack    TestMmuP_PagePairTaskBStack
#define TestMmuP_GlobalWriterTaskStack       TestMmuP_CacheMaintTaskAStack
#define TestMmuP_NonGlobalReaderTaskStack    TestMmuP_CacheMaintTaskBStack
#define TestMmuP_DeviceWriterTaskStack       TestMmuP_OverlapOutsideWriterTaskStack
#define TestMmuP_NormalReaderTaskStack       TestMmuP_OverlapSubsetReaderTaskStack
#define TestMmuP_LargeBlockTaskAStack        TestMmuP_PagePairTaskAStack
#define TestMmuP_LargeBlockTaskBStack        TestMmuP_PagePairTaskBStack
#define TestMmuP_CacheOpsTaskStack           TestMmuP_CacheMaintTaskAStack
#define TestMmuP_CacheAccessTaskStack        TestMmuP_CacheMaintTaskBStack
#endif /* ENABLE_MT_TESTS */

#if defined(ENABLE_MT_TESTS)
/* MT worker task entry points (non-test functions) */
static void TestMmuP_multithreadAdjacentPagesTaskA(void *arg);
static void TestMmuP_multithreadAdjacentPagesTaskB(void *arg);

static void TestMmuP_multithreadSinglePageHalvesTaskA(void *arg);
static void TestMmuP_multithreadSinglePageHalvesTaskB(void *arg);

static void TestMmuP_multithreadPerTaskAttrTaskA(void *arg);
static void TestMmuP_multithreadPerTaskAttrTaskB(void *arg);

static void TestMmuP_multithreadCacheMaintenanceTaskA(void *arg);
static void TestMmuP_multithreadCacheMaintenanceTaskB(void *arg);

static void TestMmuP_multithreadAliasCoherenceTaskA(void *arg);
static void TestMmuP_multithreadAliasCoherenceTaskB(void *arg);

static void TestMmuP_multithreadGlobalWriterTask(void *arg);
static void TestMmuP_multithreadNonGlobalReaderTask(void *arg);

static void TestMmuP_multithreadDeviceWriterTask(void *arg);
static void TestMmuP_multithreadNormalReaderTask(void *arg);

static void TestMmuP_multithreadLargeBlockTaskA(void *arg);
static void TestMmuP_multithreadLargeBlockTaskB(void *arg);

static void TestMmuP_multithreadOverlapOutsideWriterTask(void *arg);
static void TestMmuP_multithreadOverlapSubsetReaderTask(void *arg);

static void TestMmuP_multithreadCacheOpsTask(void *arg);
static void TestMmuP_multithreadCacheAccessTask(void *arg);
#endif /* ENABLE_MT_TESTS */


#if defined(ENABLE_MT_TESTS)
/* --- TC32 tasks (adjacent pages) --- */
static void TestMmuP_multithreadAdjacentPagesTaskA(void *arg)
{
    (void)arg;
    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_ALIAS_ADJ_PAGE_A_4K;
    uint32_t size = TEST_MMUP_PAGE_SIZE;

    TestMmuP_writePattern(vaA, size, 0xAAu);
    CacheP_wb((void *)vaA, size, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_PagePairTaskADoneSem);
    TaskP_exit();
}
static void TestMmuP_multithreadAdjacentPagesTaskB(void *arg)
{
    (void)arg;
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_ALIAS_ADJ_PAGE_B_4K;
    uint32_t size = TEST_MMUP_PAGE_SIZE;

    TestMmuP_writePattern(vaB, size, 0xBBu);
    CacheP_wb((void *)vaB, size, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_PagePairTaskBDoneSem);
    TaskP_exit();
}

/**
 * @brief Multi-thread: Verifies behavior when adjacent pages are accessed concurrently from different tasks.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Initialize mapping attributes for normal cacheable memory.
 * 3. Map two 4KB adjacent regions.
 * 4. Enable the MMU.
 * 5. Task A writes first page; Task B writes second page concurrently.
 * 6. Verify read/write within each page and boundary behavior.
 *
 * @param[in] args
 */
void TestMmuP_multithreadMappingOfAdjacentPages(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t paddrA = (uintptr_t)TestMmuP_Buffer8K;
    uintptr_t paddrB = (uintptr_t)TestMmuP_Buffer8K + TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;

    status = MmuP_map(TEST_MMUP_ALIAS_ADJ_PAGE_A_4K, paddrA, TEST_MMUP_PAGE_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MmuP_map(TEST_MMUP_ALIAS_ADJ_PAGE_B_4K, paddrB, TEST_MMUP_PAGE_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestMmuP_enableAndSync();

    /* Construct semaphores */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_PagePairTaskADoneSem, 0));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_PagePairTaskBDoneSem, 0));

    /* Create tasks via TaskP */
    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadAdjacentPagesTaskA";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_PagePairTaskAStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadAdjacentPagesTaskA;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_PagePairTaskA, &params));

    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadAdjacentPagesTaskB";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_PagePairTaskBStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadAdjacentPagesTaskB;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_PagePairTaskB, &params));

    /* Wait for completion */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_PagePairTaskADoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_PagePairTaskBDoneSem, SystemP_WAIT_FOREVER));

    /* Verify content */
    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_ALIAS_ADJ_PAGE_A_4K;
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_ALIAS_ADJ_PAGE_B_4K;
    CacheP_inv((void *)vaA, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaB, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaA, TEST_MMUP_PAGE_SIZE, 0xAAu);
    TestMmuP_checkPattern(vaB, TEST_MMUP_PAGE_SIZE, 0xBBu);

    /* Cleanup */
    TaskP_destruct(&TestMmuP_PagePairTaskA);
    TaskP_destruct(&TestMmuP_PagePairTaskB);
    SemaphoreP_destruct(&TestMmuP_PagePairTaskADoneSem);
    SemaphoreP_destruct(&TestMmuP_PagePairTaskBDoneSem);
}

static void TestMmuP_multithreadSinglePageHalvesTaskA(void *arg)
{
    (void)arg;
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_ALIAS_SINGLE_PAGE_RW_4K;     /* alias VA on A53 */
    uint32_t half = TEST_MMUP_PAGE_SIZE/2;
    TestMmuP_writePattern(va, half, 0xC1u);
    CacheP_wb((void *)va, half, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_SinglePageHalfADoneSem);
    TaskP_exit();
}

static void TestMmuP_multithreadSinglePageHalvesTaskB(void *arg)
{
    (void)arg;
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_ALIAS_SINGLE_PAGE_RW_4K;     /* alias VA on A53 */
    uint32_t half = TEST_MMUP_PAGE_SIZE/2;
    TestMmuP_writePattern(va + half, half, 0xC2u);
    CacheP_wb((void *)(va + half), half, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_SinglePageHalfBDoneSem);
    TaskP_exit();
}

/**
 * @brief Multi-thread: Verifies concurrent read/write within a single 4KB page by splitting halves.
 *
 * Long Description:
 * Maps one 4KB page and spawns two tasks. Task A writes the first 2KB with a known pattern,
 * Task B writes the second 2KB with a different pattern. The main thread waits for both
 * tasks to complete, invalidates caches, and verifies each half retains its expected data.
 *
 * Test Steps:
 * 1. Disable MMU and set Normal WB/WA, outer-shareable attributes for a single 4KB alias.
 * 2. Map the alias to the 4KB test buffer and enable MMU.
 * 3. Create two tasks: TaskA writes first half (0xC1 pattern), TaskB writes second half (0xC2 pattern).
 * 4. Wait on semaphores for both tasks to complete.
 * 5. Invalidate caches on the alias and verify both halves match their expected patterns.
 * 6. Cleanup tasks and semaphores.
 *
 * @param[in] args
 * @return void
 */
void TestMmuP_multithreadReadWriteWithinSinglePage(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;

    status = MmuP_map(TEST_MMUP_ALIAS_SINGLE_PAGE_RW_4K, paddr, TEST_MMUP_PAGE_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestMmuP_enableAndSync();

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_SinglePageHalfADoneSem, 0));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_SinglePageHalfBDoneSem, 0));

    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadSinglePageHalvesTaskA";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_SinglePageTaskAStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadSinglePageHalvesTaskA;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SinglePageTaskA, &params));

    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadSinglePageHalvesTaskB";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_SinglePageTaskBStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadSinglePageHalvesTaskB;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_SinglePageTaskB, &params));

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SinglePageHalfADoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_SinglePageHalfBDoneSem, SystemP_WAIT_FOREVER));

    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_ALIAS_SINGLE_PAGE_RW_4K;
    uint32_t half = TEST_MMUP_PAGE_SIZE/2;
    CacheP_inv((void *)va, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);

    TestMmuP_checkPattern(va, half, 0xC1u);
    TestMmuP_checkPattern((va + half), half, 0xC2u);

    ClockP_usleep(5000); /* Allow tasks to exit cleanly */
    TaskP_destruct(&TestMmuP_SinglePageTaskA);
    TaskP_destruct(&TestMmuP_SinglePageTaskB);
    SemaphoreP_destruct(&TestMmuP_SinglePageHalfADoneSem);
    SemaphoreP_destruct(&TestMmuP_SinglePageHalfBDoneSem);
}

/* --- TC34 tasks: each accesses its own mapped region (no MMU ops inside tasks) --- */
static void TestMmuP_multithreadPerTaskAttrTaskA(void *arg)
{
    (void)arg;
    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_ALIAS_PER_TASK_A_4K;
    TestMmuP_writePattern(vaA, TEST_MMUP_PAGE_SIZE, 0xD1u);
    CacheP_wb((void *)vaA, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_PerTaskAttrDoneSem);
    TaskP_exit();
}
static void TestMmuP_multithreadPerTaskAttrTaskB(void *arg)
{
    (void)arg;
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_ALIAS_PER_TASK_B_4K;
    TestMmuP_writePattern(vaB, TEST_MMUP_PAGE_SIZE, 0xD2u);
    CacheP_wb((void *)vaB, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_PerTaskAttrDoneSem);
    TaskP_exit();
}

/**
 * @brief Multi-thread: Verifies per-task attrs isolation; mappings are set up in main thread.
 *
 * @param[in] args
 */
void TestMmuP_multithreadPerTaskMapAttributeIsolation(void *args)
{
    (void)args;
    MmuP_MapAttrs attrsA, attrsB;
    int32_t status;

    /* Map both regions in the main test thread while MMU is disabled */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrsA);
    attrsA.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrsA.shareable = MMUP_SHARABLE_OUTER;
    attrsA.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    status = MmuP_map(TEST_MMUP_ALIAS_PER_TASK_A_4K, (uintptr_t)TestMmuP_Buffer4K, TEST_MMUP_PAGE_SIZE, &attrsA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_MapAttrs_init(&attrsB);
    attrsB.attrIndx  = MMUP_ATTRINDX_MAIR0; /* distinct MAIR slot */
    attrsB.shareable = MMUP_SHARABLE_NONE;
    attrsB.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    status = MmuP_map(TEST_MMUP_ALIAS_PER_TASK_B_4K, (uintptr_t)TestMmuP_Buffer8K, TEST_MMUP_PAGE_SIZE, &attrsB);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Enable MMU before spawning tasks; keep MMU enabled throughout the MT test */
    TestMmuP_enableAndSync();

    /* Counting semaphore (max 2, start 0) */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_PerTaskAttrDoneSem, 0, 2));

    /* Create tasks via TaskP */
    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadPerTaskAttrTaskA";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_PerTaskAttrTaskAStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadPerTaskAttrTaskA;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_PerTaskAttrTaskA, &params));

    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadPerTaskAttrTaskB";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_PerTaskAttrTaskBStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadPerTaskAttrTaskB;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_PerTaskAttrTaskB, &params));

    /* Wait both tasks */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_PerTaskAttrDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_PerTaskAttrDoneSem, SystemP_WAIT_FOREVER));

    /* Verify both regions are accessible and correct */
    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_ALIAS_PER_TASK_A_4K;
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_ALIAS_PER_TASK_B_4K;
    CacheP_inv((void *)vaA, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaB, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaA, TEST_MMUP_PAGE_SIZE, 0xD1u);
    TestMmuP_checkPattern(vaB, TEST_MMUP_PAGE_SIZE, 0xD2u);

    /* Cleanup */
    ClockP_usleep(5000); /* Allow tasks to exit cleanly */
    TaskP_destruct(&TestMmuP_PerTaskAttrTaskA);
    TaskP_destruct(&TestMmuP_PerTaskAttrTaskB);
    SemaphoreP_destruct(&TestMmuP_PerTaskAttrDoneSem);
}

/* --- TC35 tasks: concurrent cache maintenance --- */
static void TestMmuP_multithreadCacheMaintenanceTaskA(void *arg)
{
    (void)arg;
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_ALIAS_CACHE_MAINT_8K;
    uint32_t half = TEST_MMUP_8KB_SIZE/2;
    TestMmuP_writePattern(va, half, 0xE1u);
    CacheP_wb((void *)va, half, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_CacheMaintSyncSem);
    TaskP_exit();
}
static void TestMmuP_multithreadCacheMaintenanceTaskB(void *arg)
{
    (void)arg;
    uint32_t i;
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_ALIAS_CACHE_MAINT_8K;
    uint32_t half = TEST_MMUP_8KB_SIZE/2;
    CacheP_inv((void *)(va + half), half, CacheP_TYPE_ALL);
    /* Simple read pass */
    for (i = 0; i < half; i++) { (void)va[half + i]; }
    SemaphoreP_post(&TestMmuP_CacheMaintDoneSem);
    TaskP_exit();
}

/**
 * @brief Multi-thread: Verifies correct behavior when cache maintenance operations occur concurrently on a mapped region.
 *
 * @param[in] args
 */
void TestMmuP_multithreadCacheMaintenanceOperations(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer8K;

    /* Pre-fill second half */
    volatile uint8_t *buf = (volatile uint8_t *)TestMmuP_Buffer8K;
    TestMmuP_writePattern(buf + (TEST_MMUP_8KB_SIZE/2), (TEST_MMUP_8KB_SIZE/2), 0xE2u);

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;

    status = MmuP_map(TEST_MMUP_ALIAS_CACHE_MAINT_8K, paddr, TEST_MMUP_8KB_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestMmuP_enableAndSync();

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_CacheMaintSyncSem, 0));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_CacheMaintDoneSem, 0));

    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadCacheMaintenanceTaskA";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_CacheMaintTaskAStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadCacheMaintenanceTaskA;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_CacheMaintTaskA, &params));

    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadCacheMaintenanceTaskB";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_CacheMaintTaskBStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadCacheMaintenanceTaskB;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_CacheMaintTaskB, &params));

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_CacheMaintSyncSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_CacheMaintDoneSem, SystemP_WAIT_FOREVER));

    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_ALIAS_CACHE_MAINT_8K;
    CacheP_inv((void *)va, TEST_MMUP_8KB_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(va, (TEST_MMUP_8KB_SIZE/2), 0xE1u);
    TestMmuP_checkPattern(va + (TEST_MMUP_8KB_SIZE/2), (TEST_MMUP_8KB_SIZE/2), 0xE2u);

    ClockP_usleep(5000); /* Allow tasks to exit cleanly */
    TaskP_destruct(&TestMmuP_CacheMaintTaskA);
    TaskP_destruct(&TestMmuP_CacheMaintTaskB);
    SemaphoreP_destruct(&TestMmuP_CacheMaintSyncSem);
    SemaphoreP_destruct(&TestMmuP_CacheMaintDoneSem);
}

/* --- TC36 workers: concurrent aliases to same PA --- */
static void TestMmuP_multithreadAliasCoherenceTaskA(void *arg)
{
    (void)arg;
    volatile uint8_t *va0 = (volatile uint8_t *)TEST_MMUP_ALIAS_MAIR3_RW_4K; /* alias 0 */
    TestMmuP_writePattern(va0, TEST_MMUP_PAGE_SIZE, 0xCAu);
    CacheP_wb((void *)va0, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_AliasCoherenceTaskADoneSem);
    TaskP_exit();
}
static void TestMmuP_multithreadAliasCoherenceTaskB(void *arg)
{
    (void)arg;
    volatile uint8_t *va1 = (volatile uint8_t *)TEST_MMUP_ALIAS_DEVICE_MAIR4_RW_4K; /* alias 1 */
    TestMmuP_writePattern(va1, TEST_MMUP_PAGE_SIZE, 0xCBu);
    CacheP_wb((void *)va1, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_AliasCoherenceTaskBDoneSem);
    TaskP_exit();
}

/**
 * @brief Multithread: Verifies coherence when two aliases map to the same PA and tasks write/read concurrently.
 *
 * Test Steps:
 * 1. Disable MMU; map two 4KB alias VAs to the same PA (Normal WB/WA, outer-shareable).
 * 2. Enable MMU; create two tasks: TaskA writes pattern A via aliasVA0, TaskB writes pattern B via aliasVA1.
 * 3. Each task performs CacheP_wb/inv on its VA and signals completion.
 * 4. Main thread invalidates both aliases and verifies final pattern matches last writer deterministically via sync.
 *
 * @param[in] args
 */
void TestMmuP_multithreadAliasCoherenceOnSamePA(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;

    /* Map both aliases to same PA */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();
    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.attrIndx   = MMUP_ATTRINDX_MAIR7;
    attrs.shareable  = MMUP_SHARABLE_OUTER;
    attrs.global     = 1;
    status = MmuP_map(TEST_MMUP_ALIAS_MAIR3_RW_4K, paddr, TEST_MMUP_PAGE_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = MmuP_map(TEST_MMUP_ALIAS_DEVICE_MAIR4_RW_4K, paddr, TEST_MMUP_PAGE_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TestMmuP_enableAndSync();

    /* Semaphores: binary A/B */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_AliasCoherenceTaskADoneSem, 0));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_AliasCoherenceTaskBDoneSem, 0));

    /* Create tasks; reuse existing stacks to limit .bss */
    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadAliasCoherenceTaskA";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_AliasCoherenceTaskAStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadAliasCoherenceTaskA;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_AliasCoherenceTaskA, &params));

    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadAliasCoherenceTaskB";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_AliasCoherenceTaskBStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadAliasCoherenceTaskB;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_AliasCoherenceTaskB, &params));

    /* Wait both complete; ensure deterministic last-writer by ordering check */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_AliasCoherenceTaskADoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_AliasCoherenceTaskBDoneSem, SystemP_WAIT_FOREVER));

    /* Verify both aliases read back last writer (0xCB) */
    volatile uint8_t *va0 = (volatile uint8_t *)TEST_MMUP_ALIAS_MAIR3_RW_4K;
    volatile uint8_t *va1 = (volatile uint8_t *)TEST_MMUP_ALIAS_DEVICE_MAIR4_RW_4K;
    CacheP_inv((void *)va0, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)va1, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(va0, TEST_MMUP_PAGE_SIZE, 0xCBu);
    TestMmuP_checkPattern(va1, TEST_MMUP_PAGE_SIZE, 0xCBu);

    /* Cleanup */
    ClockP_usleep(5000); /* Allow tasks to exit cleanly */
    TaskP_destruct(&TestMmuP_AliasCoherenceTaskA);
    TaskP_destruct(&TestMmuP_AliasCoherenceTaskB);
    SemaphoreP_destruct(&TestMmuP_AliasCoherenceTaskADoneSem);
    SemaphoreP_destruct(&TestMmuP_AliasCoherenceTaskBDoneSem);
}

/* --- TC37 workers: global vs non-global alias to same PA --- */
static void TestMmuP_multithreadGlobalWriterTask(void *arg)
{
    (void)arg;
    volatile uint8_t *vaG = (volatile uint8_t *)TEST_MMUP_ALIAS_MAIR5_RW_4K;
    TestMmuP_writePattern(vaG, TEST_MMUP_PAGE_SIZE, 0xD1u);
    CacheP_wb((void *)vaG, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_GlobalVsNonGlobalSyncSem);  /* signal reader */
    SemaphoreP_post(&TestMmuP_GlobalVsNonGlobalDoneSem);  /* completion */
    TaskP_exit();
}
static void TestMmuP_multithreadNonGlobalReaderTask(void *arg)
{
    (void)arg;
    /* wait writer */
    (void)SemaphoreP_pend(&TestMmuP_GlobalVsNonGlobalSyncSem, SystemP_WAIT_FOREVER);
    volatile uint8_t *vaNG = (volatile uint8_t *)TEST_MMUP_ALIAS_NONGLOBAL_RW_4K;
    CacheP_inv((void *)vaNG, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    /* main thread will verify after completion */
    SemaphoreP_post(&TestMmuP_GlobalVsNonGlobalDoneSem);
    TaskP_exit();
}

/**
 * @brief Multithread: Verifies global vs non-global mappings access concurrently to the same PA remain consistent.
 *
 * Test Steps:
 * 1. Disable MMU; map aliasVA_global (global=1) and aliasVA_nonglobal (global=0) to same PA.
 * 2. Enable MMU; spawn TaskA (writes via global alias) and TaskB (reads/verifies via non-global alias).
 * 3. Use a counting semaphore to serialize write-then-read; ensure data matches across aliases.
 * 4. Cleanup tasks and semaphores.
 *
 * @param[in] args
 */
void TestMmuP_multithreadGlobalVsNonGlobalAliasAccess(void *args)
{
    (void)args;
    MmuP_MapAttrs attrsG, attrsNG;
    int32_t status;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;

    /* Map global and non-global aliases to same PA */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrsG);
    attrsG.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrsG.attrIndx   = MMUP_ATTRINDX_MAIR7;
    attrsG.shareable  = MMUP_SHARABLE_OUTER;
    attrsG.global     = 1;
    status = MmuP_map(TEST_MMUP_ALIAS_MAIR5_RW_4K, paddr, TEST_MMUP_PAGE_SIZE, &attrsG);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_MapAttrs_init(&attrsNG);
    attrsNG.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrsNG.attrIndx   = MMUP_ATTRINDX_MAIR7;
    attrsNG.shareable  = MMUP_SHARABLE_OUTER;
    attrsNG.global     = 0;
    status = MmuP_map(TEST_MMUP_ALIAS_NONGLOBAL_RW_4K, paddr, TEST_MMUP_PAGE_SIZE, &attrsNG);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestMmuP_enableAndSync();

    /* Semaphores: sync + counting done (max 2) */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_GlobalVsNonGlobalSyncSem, 0));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_GlobalVsNonGlobalDoneSem, 0, 2));

    /* Create writer (global) and reader (non-global) */
    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadGlobalWriterTask";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_GlobalWriterTaskStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadGlobalWriterTask;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_GlobalWriterTask, &params));

    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadNonGlobalReaderTask";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_NonGlobalReaderTaskStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadNonGlobalReaderTask;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_NonGlobalReaderTask, &params));

    /* Wait both done */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_GlobalVsNonGlobalDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_GlobalVsNonGlobalDoneSem, SystemP_WAIT_FOREVER));

    /* Verify non-global alias sees writer's data */
    volatile uint8_t *vaG  = (volatile uint8_t *)TEST_MMUP_ALIAS_MAIR5_RW_4K;
    volatile uint8_t *vaNG = (volatile uint8_t *)TEST_MMUP_ALIAS_NONGLOBAL_RW_4K;
    CacheP_inv((void *)vaG,  TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaNG, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaG,  TEST_MMUP_PAGE_SIZE, 0xD1u);
    TestMmuP_checkPattern(vaNG, TEST_MMUP_PAGE_SIZE, 0xD1u);

    /* Cleanup */
    TaskP_destruct(&TestMmuP_GlobalWriterTask);
    TaskP_destruct(&TestMmuP_NonGlobalReaderTask);
    SemaphoreP_destruct(&TestMmuP_GlobalVsNonGlobalSyncSem);
    SemaphoreP_destruct(&TestMmuP_GlobalVsNonGlobalDoneSem);
}

/* --- TC38 workers: device vs normal attributes to same PA --- */
static void TestMmuP_multithreadDeviceWriterTask(void *arg)
{
    (void)arg;
    volatile uint8_t *vaDev = (volatile uint8_t *)TEST_MMUP_ALIAS_DEVICE_PAIR_DEV_4K;
    TestMmuP_writePattern(vaDev, TEST_MMUP_PAGE_SIZE, 0xE1u);
    SemaphoreP_post(&TestMmuP_DeviceVsNormalSyncSem);   /* signal reader */
    SemaphoreP_post(&TestMmuP_DeviceVsNormalDoneSem);   /* completion */
    TaskP_exit();
}
static void TestMmuP_multithreadNormalReaderTask(void *arg)
{
    (void)arg;
    (void)SemaphoreP_pend(&TestMmuP_DeviceVsNormalSyncSem, SystemP_WAIT_FOREVER);
    volatile uint8_t *vaNorm = (volatile uint8_t *)TEST_MMUP_ALIAS_NORMAL_PAIR_NORM_4K;
    CacheP_inv((void *)vaNorm, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_DeviceVsNormalDoneSem);
    TaskP_exit();
}

/**
 * @brief Multithread: Verifies device (MAIR4) vs normal (MAIR7) attribute ordering to the same PA under concurrency.
 *
 * Test Steps:
 * 1. Disable MMU; map aliasVA_dev (MAIR4, device, ordered) and aliasVA_norm (MAIR7, Normal WB/WA) to same PA.
 * 2. Enable MMU; TaskA writes via device alias; TaskB immediately reads via normal alias.
 * 3. Ensure TaskB observes TaskA’s write (ordered visibility) with minimal cache use on device alias.
 * 4. Validate data and teardown.
 *
 * @param[in] args
 */
void TestMmuP_multithreadDeviceVsNormalAccessOrdering(void *args)
{
    (void)args;
    MmuP_MapAttrs attrsDev, attrsNorm;
    int32_t status;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;

    /* Map device and normal aliases to same PA */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrsDev);
    attrsDev.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrsDev.attrIndx   = MMUP_ATTRINDX_MAIR4;  /* device/non-cacheable */
    attrsDev.shareable  = MMUP_SHARABLE_OUTER;
    attrsDev.global     = 1;
    status = MmuP_map(TEST_MMUP_ALIAS_DEVICE_PAIR_DEV_4K, paddr, TEST_MMUP_PAGE_SIZE, &attrsDev);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_MapAttrs_init(&attrsNorm);
    attrsNorm.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrsNorm.attrIndx   = MMUP_ATTRINDX_MAIR7; /* normal WB/WA */
    attrsNorm.shareable  = MMUP_SHARABLE_OUTER;
    attrsNorm.global     = 1;
    status = MmuP_map(TEST_MMUP_ALIAS_NORMAL_PAIR_NORM_4K, paddr, TEST_MMUP_PAGE_SIZE, &attrsNorm);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestMmuP_enableAndSync();

    /* Semaphores: sync + counting done (max 2) */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_DeviceVsNormalSyncSem, 0));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructCounting(&TestMmuP_DeviceVsNormalDoneSem, 0, 2));

    /* Create writer (device) and reader (normal) */
    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadDeviceWriterTask";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_DeviceWriterTaskStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadDeviceWriterTask;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_DeviceWriterTask, &params));

    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadNormalReaderTask";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_NormalReaderTaskStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadNormalReaderTask;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_NormalReaderTask, &params));

    /* Wait both done */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_DeviceVsNormalDoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_DeviceVsNormalDoneSem, SystemP_WAIT_FOREVER));

    /* Verify normal alias observes device write */
    volatile uint8_t *vaDev  = (volatile uint8_t *)TEST_MMUP_ALIAS_DEVICE_PAIR_DEV_4K;
    volatile uint8_t *vaNorm = (volatile uint8_t *)TEST_MMUP_ALIAS_NORMAL_PAIR_NORM_4K;
    CacheP_inv((void *)vaDev,  TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaNorm, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaDev,  TEST_MMUP_PAGE_SIZE, 0xE1u);
    TestMmuP_checkPattern(vaNorm, TEST_MMUP_PAGE_SIZE, 0xE1u);

    /* Cleanup */
    ClockP_usleep(5000); /* Allow tasks to exit cleanly */
    TaskP_destruct(&TestMmuP_DeviceWriterTask);
    TaskP_destruct(&TestMmuP_NormalReaderTask);
    SemaphoreP_destruct(&TestMmuP_DeviceVsNormalSyncSem);
    SemaphoreP_destruct(&TestMmuP_DeviceVsNormalDoneSem);
}

/* --- TC39 workers: large 2MB block, adjacent pages --- */
static void TestMmuP_multithreadLargeBlockTaskA(void *arg)
{
    (void)arg;
    uintptr_t bufPA     = (uintptr_t)TestMmuP_Buffer64K;
    uintptr_t paddrBase = TEST_MMUP_ALIGN_DOWN(bufPA, TEST_MMUP_2MB_SIZE);
    uintptr_t vaddrBase = 0x00A00000u; /* 2MB-aligned alias base used in test */
    uintptr_t pageNVA   = vaddrBase + (bufPA - paddrBase);

    volatile uint8_t *va = (volatile uint8_t *)pageNVA;
    TestMmuP_writePattern(va, TEST_MMUP_PAGE_SIZE, 0xAAu);
    CacheP_wb((void *)va, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);

    SemaphoreP_post(&TestMmuP_PagePairTaskADoneSem);
    TaskP_exit();
}
static void TestMmuP_multithreadLargeBlockTaskB(void *arg)
{
    (void)arg;
    uintptr_t bufPA     = (uintptr_t)TestMmuP_Buffer64K;
    uintptr_t paddrBase = TEST_MMUP_ALIGN_DOWN(bufPA, TEST_MMUP_2MB_SIZE);
    uintptr_t vaddrBase = 0x00A00000u;
    uintptr_t pageNVA   = vaddrBase + (bufPA - paddrBase);
    uintptr_t pageN1VA  = pageNVA + TEST_MMUP_PAGE_SIZE;

    volatile uint8_t *va = (volatile uint8_t *)pageN1VA;
    TestMmuP_writePattern(va, TEST_MMUP_PAGE_SIZE, 0xBBu);
    CacheP_wb((void *)va, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);

    SemaphoreP_post(&TestMmuP_PagePairTaskBDoneSem);
    TaskP_exit();
}

/**
 * @brief Multithread: Verifies concurrent access across pages within a 2MB block mapping.
 *
 * Test Steps:
 * 1. Disable MMU; map a 2MB-aligned VA block to a 2MB-aligned PA base containing the test buffers.
 * 2. Enable MMU; TaskA accesses page N, TaskB accesses page N+1 with distinct patterns.
 * 3. Each task performs CacheP_wb/inv on its span and signals completion.
 * 4. Main thread verifies both pages retain correct, independent data.
 *
 * @param[in] args
 */
void TestMmuP_multithreadLargeBlockAccessAcrossPages(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t bufPA     = (uintptr_t)TestMmuP_Buffer64K;
    uintptr_t paddrBase = TEST_MMUP_ALIGN_DOWN(bufPA, TEST_MMUP_2MB_SIZE);
    uintptr_t vaddrBase = 0x00A00000u; /* 2MB-aligned */
    TEST_ASSERT_EQUAL_UINT32(0u, (vaddrBase & (TEST_MMUP_2MB_SIZE - 1u)));

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.shareable  = MMUP_SHARABLE_OUTER;
    attrs.attrIndx   = MMUP_ATTRINDX_MAIR7;
    attrs.global     = 1;

    status = MmuP_map(vaddrBase, paddrBase, TEST_MMUP_2MB_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestMmuP_enableAndSync();

    /* Semaphores for task completion */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_PagePairTaskADoneSem, 0));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_PagePairTaskBDoneSem, 0));

    /* Create tasks */
    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadLargeBlockTaskA";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_LargeBlockTaskAStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadLargeBlockTaskA;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_PagePairTaskA, &params));

    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadLargeBlockTaskB";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_LargeBlockTaskBStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadLargeBlockTaskB;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_PagePairTaskB, &params));

    /* Wait */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_PagePairTaskADoneSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_PagePairTaskBDoneSem, SystemP_WAIT_FOREVER));

    /* Verify both pages */
    volatile uint8_t *pageN   = (volatile uint8_t *)(vaddrBase + (bufPA - paddrBase));
    volatile uint8_t *pageN1  = (volatile uint8_t *)((uintptr_t)pageN + TEST_MMUP_PAGE_SIZE);
    CacheP_inv((void *)pageN,  TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)pageN1, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(pageN,  TEST_MMUP_PAGE_SIZE, 0xAAu);
    TestMmuP_checkPattern(pageN1, TEST_MMUP_PAGE_SIZE, 0xBBu);

    /* Cleanup */
    ClockP_usleep(5000); /* Allow tasks to exit cleanly */
    TaskP_destruct(&TestMmuP_PagePairTaskA);
    TaskP_destruct(&TestMmuP_PagePairTaskB);
    SemaphoreP_destruct(&TestMmuP_PagePairTaskADoneSem);
    SemaphoreP_destruct(&TestMmuP_PagePairTaskBDoneSem);
}

/* --- TC40 workers: overlapping RO subset vs RW outside --- */
static void TestMmuP_multithreadOverlapOutsideWriterTask(void *arg)
{
    (void)arg;
    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_ALIAS_OVERLAP_RW_A_8K; /* 8KB RW */
    /* Write outside the RO 4KB subset (offset +4KB) */
    volatile uint8_t *outside = vaA + TEST_MMUP_PAGE_SIZE;
    TestMmuP_writePattern(outside, TEST_MMUP_PAGE_SIZE, 0xDDu);
    CacheP_wb((void *)outside, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_barrier();
    SemaphoreP_post(&TestMmuP_OverlapSubsetROSemSync); /* sync reader start */
    SemaphoreP_post(&TestMmuP_OverlapSubsetROSemWriterDone); /* writer done */
    TaskP_exit();
}
static void TestMmuP_multithreadOverlapSubsetReaderTask(void *arg)
{
    (void)arg;
    /* wait for writer to publish */
    (void)SemaphoreP_pend(&TestMmuP_OverlapSubsetROSemSync, SystemP_WAIT_FOREVER);
#if defined(ENABLE_C75_CORE)
    /* Only invalidate on cores where alias B is cacheable */
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_ALIAS_OVERLAP_RO_B_4K; /* 4KB RO subset */
    CacheP_inv((void *)vaB, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
#endif
    /* main thread will verify contents */
    SemaphoreP_post(&TestMmuP_OverlapSubsetROSemReaderDone); /* reader done */
    TaskP_exit();
}

/**
 * @brief Multithread: Verifies overlapping RO subset and RW outside region under concurrent task access.
 *
 * Test Steps:
 * 1. Disable MMU; map 8KB RW region (aliasVA_A) and overlapping 4KB RO subset (aliasVA_B).
 * 2. Enable MMU; TaskA writes outside the RO subset via aliasVA_A; TaskB reads inside the RO subset via aliasVA_B.
 * 3. Synchronize to ensure ordering (write outside, read inside).
 * 4. Verify RO subset content is unchanged while RW outside reflects TaskA’s write.
 *
 * @param[in] args
 */
void TestMmuP_multithreadOverlappingROSubsetVsRWOutside(void *args)
{
    (void)args;
    MmuP_MapAttrs attrsA, attrsB;
    int32_t status;

    /* Pre-init buffer to known content for RO subset */
    TestMmuP_writePattern(TestMmuP_Buffer8K, TEST_MMUP_8KB_SIZE, 0xC3u);

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    /* Map 8KB RW region at alias A */
    MmuP_MapAttrs_init(&attrsA);
    attrsA.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrsA.attrIndx   = MMUP_ATTRINDX_MAIR7;
    attrsA.shareable  = MMUP_SHARABLE_OUTER;
    attrsA.global     = 1;

    status = MmuP_map(TEST_MMUP_ALIAS_OVERLAP_RW_A_8K, (uintptr_t)TestMmuP_Buffer8K, TEST_MMUP_8KB_SIZE, &attrsA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Map overlapping 4KB RO subset at alias B (same PA) */
    MmuP_MapAttrs_init(&attrsB);
    attrsB.accessPerm = MMUP_ACCESS_PERM_PRIV_RO_USER_RO;
#if defined(ENABLE_C75_CORE)
    attrsB.attrIndx   = MMUP_ATTRINDX_MAIR7;  /* cacheable on C75 */
#else
    attrsB.attrIndx   = MMUP_ATTRINDX_MAIR4;  /* non-cacheable on a53 */
#endif
    attrsB.shareable  = MMUP_SHARABLE_OUTER;
    attrsB.global     = 1;
    status = MmuP_map(TEST_MMUP_ALIAS_OVERLAP_RO_B_4K, (uintptr_t)TestMmuP_Buffer8K, TEST_MMUP_PAGE_SIZE, &attrsB);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestMmuP_enableAndSync();
    /* Semaphores: sync and done */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_OverlapSubsetROSemSync, 0)); /* sync */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_OverlapSubsetROSemWriterDone, 0)); /* writer done */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_OverlapSubsetROSemReaderDone, 0)); /* reader done */

    /* Create writer and reader */
    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadOverlapOutsideWriterTask";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_OverlapOutsideWriterTaskStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadOverlapOutsideWriterTask;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_OverlapOutsideWriterTask, &params));
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadOverlapSubsetReaderTask";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_OverlapSubsetReaderTaskStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadOverlapSubsetReaderTask;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_OverlapSubsetReaderTask, &params));
    /* Wait for both */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_OverlapSubsetROSemWriterDone, SystemP_WAIT_FOREVER)); /* writer */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_OverlapSubsetROSemReaderDone, SystemP_WAIT_FOREVER)); /* reader */    /* Verify: RO subset unchanged, outside reflects writer */
    volatile uint8_t *subsetRO  = (volatile uint8_t *)TEST_MMUP_ALIAS_OVERLAP_RO_B_4K;
    volatile uint8_t *outsideRW = (volatile uint8_t *)(TEST_MMUP_ALIAS_OVERLAP_RW_A_8K + TEST_MMUP_PAGE_SIZE);

#if defined(ENABLE_C75_CORE)
    /* C75: alias B is MAIR7 (cacheable) -> do inv on subsetRO */
    CacheP_inv((void *)subsetRO,  TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
#endif
    CacheP_inv((void *)outsideRW, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);

    TestMmuP_checkPattern(subsetRO,  TEST_MMUP_PAGE_SIZE, 0xC3u);
    TestMmuP_checkPattern(outsideRW, TEST_MMUP_PAGE_SIZE, 0xDDu);

    /* Cleanup */
    ClockP_usleep(5000); /* Allow tasks to exit cleanly */
    TaskP_destruct(&TestMmuP_OverlapOutsideWriterTask);
    TaskP_destruct(&TestMmuP_OverlapSubsetReaderTask);
    SemaphoreP_destruct(&TestMmuP_OverlapSubsetROSemSync);
    SemaphoreP_destruct(&TestMmuP_OverlapSubsetROSemWriterDone);
    SemaphoreP_destruct(&TestMmuP_OverlapSubsetROSemReaderDone);
}

/* --- TC41 workers: cache maintenance vs access on same alias --- */
static void TestMmuP_multithreadCacheOpsTask(void *arg)
{
    (void)arg;
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_ALIAS_NORMAL_PAIR_NORM_4K;
    CacheP_wb((void *)va, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)va, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_CacheMaintSyncSem); /* signal TaskB to proceed */
    SemaphoreP_post(&TestMmuP_CacheMaintDoneSem); /* TaskA done */
    TaskP_exit();
}
static void TestMmuP_multithreadCacheAccessTask(void *arg)
{
    (void)arg;
    (void)SemaphoreP_pend(&TestMmuP_CacheMaintSyncSem, SystemP_WAIT_FOREVER);
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_ALIAS_NORMAL_PAIR_NORM_4K;
    TestMmuP_writePattern(va, TEST_MMUP_PAGE_SIZE, 0xEEu);
    CacheP_wb((void *)va, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)va, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    SemaphoreP_post(&TestMmuP_PagePairTaskBDoneSem); /* TaskB done */
    TaskP_exit();
}

/**
 * @brief Multithread: Verifies concurrent cache maintenance and data access serialize correctly.
 *
 * Test Steps:
 * 1. Disable MMU; map a 4KB Normal WB/WA alias to a PA buffer.
 * 2. Enable MMU; TaskA performs CacheP_wb/inv on the alias; TaskB writes/reads pattern concurrently.
 * 3. Use semaphores to enforce maintenance-then-access order to avoid tearing.
 * 4. Validate final buffer content matches expected pattern.
 *
 * @param[in] args
 */
void TestMmuP_multithreadCacheMaintenanceAndAccess(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.attrIndx   = MMUP_ATTRINDX_MAIR7;
    attrs.shareable  = MMUP_SHARABLE_OUTER;
    attrs.global     = 1;

    status = MmuP_map(TEST_MMUP_ALIAS_NORMAL_PAIR_NORM_4K, (uintptr_t)TestMmuP_Buffer4K, TEST_MMUP_PAGE_SIZE, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TestMmuP_enableAndSync();

    /* Semaphores: sync and done */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_CacheMaintSyncSem, 0)); /* sync */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_CacheMaintDoneSem, 0)); /* TaskA done */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_constructBinary(&TestMmuP_PagePairTaskBDoneSem, 0)); /* TaskB done */

    /* Create tasks */
    TaskP_Params params;
    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadCacheOpsTask";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_CacheOpsTaskStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadCacheOpsTask;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_CacheMaintTaskA, &params));

    TaskP_Params_init(&params);
    params.name      = "TestMmuP_multithreadCacheAccessTask";
    params.priority  = TEST_MMUP_MT_TASK_PRIO;
    params.stack     = TestMmuP_CacheAccessTaskStack;
    params.stackSize = TEST_MMUP_MT_TASK_STACK_SIZE;
    params.taskMain  = TestMmuP_multithreadCacheAccessTask;
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestMmuP_CacheMaintTaskB, &params));

    /* Wait both done */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_CacheMaintDoneSem, SystemP_WAIT_FOREVER)); /* TaskA done */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestMmuP_PagePairTaskBDoneSem, SystemP_WAIT_FOREVER)); /* TaskB done */

    /* Verify final content */
    volatile uint8_t *va = (volatile uint8_t *)TEST_MMUP_ALIAS_NORMAL_PAIR_NORM_4K;
    CacheP_inv((void *)va, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(va, TEST_MMUP_PAGE_SIZE, 0xEEu);

    /* Cleanup */
    ClockP_usleep(5000); /* Allow tasks to exit cleanly */
    TaskP_destruct(&TestMmuP_CacheMaintTaskA);
    TaskP_destruct(&TestMmuP_CacheMaintTaskB);
    SemaphoreP_destruct(&TestMmuP_CacheMaintSyncSem);
    SemaphoreP_destruct(&TestMmuP_CacheMaintDoneSem);
    SemaphoreP_destruct(&TestMmuP_PagePairTaskBDoneSem);
}
#endif /* ENABLE_MT_TESTS */
#endif /*TEST_MULTI_THREAD_MMU*/

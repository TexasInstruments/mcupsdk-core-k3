#include "test_mmu.h"

#ifndef TEST_SINGLE_THREAD_MMU
#define TEST_SINGLE_THREAD_MMU

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

#if !defined(ENABLE_C75_CORE)
/* A53-side helpers for execute tests */
static inline void TestMmuP_syncI(uintptr_t vaddr, uint32_t size);
static int TestMmuP_executeStubFunction(void);
static int TestMmuP_executeStubBoundaryFunction(void);
#endif /* !ENABLE_C75_CORE */

/* Helper: Reset MMU to SysCfg baseline to avoid table fragmentation and VA synonyms */
static void TestMmuP_resetMMU(void)
{
    /* Preserve existing OCRAM mapping; just cycle MMU */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();
    TestMmuP_enableAndSync();
}

#if !defined(ENABLE_C75_CORE)
/* Helper: synchronize I-cache so instruction fetch sees recent writes */
static inline void TestMmuP_syncI(uintptr_t vaddr, uint32_t size)
{
#if defined(ENABLE_A53_CORE)
    __builtin___clear_cache((char *)vaddr, (char *)(vaddr + size));
    __asm__ volatile ("dsb sy");
    __asm__ volatile ("isb");
#else
    (void)vaddr;
    (void)size;
#endif
}

/* Helper: small stub used by execute-alias tests */
typedef int (*exec_stub_t)(void);
static int TestMmuP_executeStubFunction(void)
{
    return 0x1234ABCD;
}

#if defined(ENABLE_C75_CORE)
__attribute__((noinline))
#else
/* Place this function in its own section to increase placement stability.
   It may or may not straddle a 4KB boundary depending on link layout. */
__attribute__((noinline, section(".exec_boundary")))
#endif
/* Helper: stub placed near page boundary for cross-page execute test */
static int TestMmuP_executeStubBoundaryFunction(void)
{
    return 0xDEADBEEF;
}

#endif /* !ENABLE_C75_CORE - exception dump/hang in c75 core  */

/* ========================================================================== */
/*                               Test cases                                   */
/* ========================================================================== */

/**
 * @brief Verifies MMU enable/disable and MmuP_isEnabled() state.
 *
 * Long Description:
 * Ensures MmuP_enable() turns on translation, MmuP_disable() turns it off,
 * and MmuP_isEnabled() accurately reflects the current state.
 *
 * Test Steps:
 * 1. Initialize the MMU driver if not already initialized by boot.
 * 2. Disable the MMU and confirm MmuP_isEnabled() returns false.
 * 3. Enable the MMU and confirm MmuP_isEnabled() returns true.
 * 4. Disable the MMU again and confirm MmuP_isEnabled() returns false.
 *
 * @param[in] args
 * @return void
 */
void TestMmuP_enableDisableAndIsEnabled(void *args)
{
    /* Step 1: Optional init is typically done at boot; keep test self-contained */
    /* Step 2 */
    CacheP_disable(CacheP_TYPE_ALL);
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    TestMmuP_barrier();
    MmuP_disable();
    TestMmuP_barrier();
    TEST_ASSERT_FALSE(MmuP_isEnabled());

    /* Step 3 */
    MmuP_enable();
    TestMmuP_barrier();
    TEST_ASSERT_TRUE(MmuP_isEnabled());

    /* Step 4 */
    MmuP_disable();
    TestMmuP_barrier();
    TEST_ASSERT_FALSE(MmuP_isEnabled());
}

/**
 * @brief Maps a single 4KB page (Normal cacheable, outer-shareable) and verifies access.
 *
 * Long Description:
 * Maps a 4KB-aligned virtual address to a 4KB-aligned physical address of a test buffer
 * using Normal cacheable attributes, then performs read/write through the VA and verifies data.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Initialize mapping attributes for Normal cacheable, outer-shareable memory.
 * 3. Map a 4KB-aligned VA to a 4KB-aligned PA (identity mapping of TestMmuP_Buffer4K).
 * 4. Enable the MMU and perform read/write access through the VA.
 * 5. Verify written and read data match.
 *
 * @param[in] args
 * @return void
 */
void TestMmuP_mapAligned4KbPage(void *args)
{
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = (uintptr_t)TestMmuP_Buffer4K; /* identity-map */
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    /* Step 1 */
    /* Disable MMU and clean caches */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    /* Step 2 */
    MmuP_MapAttrs_init(&attrs);
    attrs.shareable = MMUP_SHARABLE_OUTER;
    /* Prefer Normal WB/WA cacheable if available */
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;

    /* Step 3 */
    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4 */
    MmuP_enable();
    TestMmuP_barrier();
    CacheP_inv((void *)vaddr, size, CacheP_TYPE_ALL);

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x5Au);
    /* Write-back after write */
    CacheP_wb((void *)vaddr, size, CacheP_TYPE_ALL);

    /* Invalidate before read */
    CacheP_inv((void *)vaddr, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x5Au);

    /* Leave MMU enabled state unchanged for subsequent tests */
}

/**
 * @brief Maps an 8KB region (two contiguous 4KB pages) and verifies access across pages.
 *
 * Long Description:
 * Maps two 4KB pages contiguously with Normal cacheable attributes. Performs read/write
 * across the full 8KB span, validating data integrity over the page boundary.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Initialize mapping attributes for Normal cacheable memory.
 * 3. Map an 8KB region using two contiguous 4KB pages (identity-map TestMmuP_Buffer8K).
 * 4. Enable the MMU and perform read/write across the full region.
 * 5. Verify data integrity across page boundaries.
 *
 * @param[in] args
 * @return void
 */
void TestMmuP_mapAligned8KbRegion(void *args)
{
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = (uintptr_t)TestMmuP_Buffer8K; /* identity-map */
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer8K;
    uint32_t  size  = TEST_MMUP_8KB_SIZE; /* 8KB */

    /* Step 1 */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    /* Step 2 */
    MmuP_MapAttrs_init(&attrs);
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7; /* Normal WB/WA */

    /* Step 3 */
    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Step 4 */
    MmuP_enable();
    TestMmuP_barrier();
    CacheP_inv((void *)vaddr, size, CacheP_TYPE_ALL);

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0xA5u);
    CacheP_wb((void *)vaddr, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaddr, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0xA5u);
}

/**
 * @brief Maps a 64KB-aligned region and verifies read/write across all pages.
 *
 * Long Description:
 * Identity-maps a 64KB-aligned buffer using Normal cacheable attributes and
 * performs read/write across the entire region to validate functional access.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Initialize mapping attributes for Normal cacheable memory.
 * 3. Map a 64KB-aligned region of size 64KB.
 * 4. Enable the MMU and perform read/write access across the entire region.
 * 5. Verify data integrity.
 *
 * @param[in] args
 * @return void
 */
void TestMmuP_mapAligned64KbRegion(void *args)
{
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = (uintptr_t)TestMmuP_Buffer64K; /* identity-map */
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer64K;
    uint32_t  size  = TEST_MMUP_64KB_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();
    CacheP_inv((void *)vaddr, size, CacheP_TYPE_ALL);

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x3Cu);
    CacheP_wb((void *)vaddr, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaddr, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x3Cu);
}

/**
 * @brief Maps a 2MB-aligned region (L2 block) and verifies functional access.
 *
 * Long Description:
 * Maps a 2MB-aligned VA to a 2MB-aligned PA base that contains the test buffer.
 * Access is verified at the offset corresponding to the buffer inside the 2MB block.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Initialize mapping attributes for Normal cacheable memory.
 * 3. Map a 2MB-aligned region of size 2MB.
 * 4. Enable the MMU and perform read/write access within the region.
 * 5. Verify correct data access.
 *
 * @param[in] args
 * @return void
 */
void TestMmuP_mapAligned2MbBlock(void *args)
{
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t bufPA      = (uintptr_t)TestMmuP_Buffer8K;
    uintptr_t paddrBase  = TEST_MMUP_ALIGN_DOWN(bufPA, TEST_MMUP_2MB_SIZE);
    uintptr_t vaddrBase  = 0x00A00000u; /* choose a 2MB-aligned VA base */
    uintptr_t vaOffset   = bufPA - paddrBase;
    uint32_t  mapSize    = TEST_MMUP_2MB_SIZE;

    /* Ensure chosen VA base is 2MB aligned */
    TEST_ASSERT_EQUAL_UINT32(0u, (vaddrBase & (TEST_MMUP_2MB_SIZE - 1u)));

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;

    status = MmuP_map(vaddrBase, paddrBase, mapSize, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vaPtr = (volatile uint8_t *)(vaddrBase + vaOffset);
    uint32_t testSize = TEST_MMUP_8KB_SIZE;

    CacheP_inv((void *)vaPtr, testSize, CacheP_TYPE_ALL);
    TestMmuP_writePattern(vaPtr, testSize, 0x6Du);
    CacheP_wb((void *)vaPtr, testSize, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaPtr, testSize, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaPtr, testSize, 0x6Du);
}

/**
 * @brief Maps a 1GB-aligned region (L1 block) and verifies functional access.
 *
 * Long Description:
 * Maps a 1GB-aligned VA to a 1GB-aligned PA base that contains a small test buffer.
 * Verifies read/write at the VA corresponding to the buffer offset within the 1GB block.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Initialize mapping attributes for Normal cacheable memory.
 * 3. Map a 1GB-aligned region of size 1GB.
 * 4. Enable the MMU and verify read/write access at multiple offsets.
 * 5. Confirm all accesses succeed.
 *
 * @param[in] args
 * @return void
 */
void TestMmuP_mapAligned1GbBlock(void *args)
{
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t bufPA      = (uintptr_t)TestMmuP_Buffer4K;
    uintptr_t paddrBase  = TEST_MMUP_ALIGN_DOWN(bufPA, TEST_MMUP_1GB_SIZE);
    uintptr_t vaddrBase  = 0x40000000u; /* 1GB-aligned VA base */
    uintptr_t vaOffset   = bufPA - paddrBase;
    uint32_t  mapSize    = TEST_MMUP_1GB_SIZE;

    TEST_ASSERT_EQUAL_UINT32(0u, (vaddrBase & (TEST_MMUP_1GB_SIZE - 1u)));

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;

    status = MmuP_map(vaddrBase, paddrBase, mapSize, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vaPtr = (volatile uint8_t *)(vaddrBase + vaOffset);
    uint32_t testSize = TEST_MMUP_PAGE_SIZE;

    /* Access at start of buffer offset */
    CacheP_inv((void *)vaPtr, testSize, CacheP_TYPE_ALL);
    TestMmuP_writePattern(vaPtr, testSize, 0x9Bu);
    CacheP_wb((void *)vaPtr, testSize, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaPtr, testSize, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaPtr, testSize, 0x9Bu);
}

/**
 * @brief Privileged RW, user no access — privileged read/write succeeds.
 *
 * Long Description:
 * Maps an alias VA to a buffer PA with AP=priv RW, user none. Performs privileged
 * read/write and verifies data integrity (positive functional check).
 *
 * Test Steps:
 * 1. Initialize a buffer using a privileged read/write mapping.
 * 2. Disable the MMU.
 * 3. Map an alias VA as privileged read/write, user no access.
 * 4. Enable the MMU and perform privileged read/write access.
 * 5. Verify data integrity.
 *
 * @param[in] args
 * @return void
 */
void TestMmuP_privilegedReadWriteUserNoAccess(void *args)
{
    volatile uint8_t *buf = (volatile uint8_t *)TestMmuP_Buffer4K;
    TestMmuP_writePattern(buf, TEST_MMUP_PAGE_SIZE, 0x11u);

    MmuP_MapAttrs attrs;
    int32_t status;

    /* Use 64KB-aligned alias VA to reduce splits */
    uintptr_t paddrBuf  = (uintptr_t)TestMmuP_Buffer4K;
    uintptr_t aliasVA   = 0x90000000u;     /* 64KB aligned */
    uint32_t  size      = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    TestMmuP_resetMMU();                    /* IMPORTANT: start clean */

    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_NONE;
    attrs.shareable  = MMUP_SHARABLE_OUTER;
    attrs.attrIndx   = MMUP_ATTRINDX_MAIR7;
    attrs.global     = 1;

    status = MmuP_map(aliasVA, paddrBuf, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vaPtr = (volatile uint8_t *)aliasVA;
    CacheP_inv((void *)vaPtr, size, CacheP_TYPE_ALL);

    TestMmuP_writePattern(vaPtr, size, 0x22u);
    CacheP_wb((void *)vaPtr, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaPtr, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaPtr, size, 0x22u);
}

/**
 * @brief Privileged RO, user no access — privileged read succeeds.
 *
 * Long Description:
 * Maps an alias VA to the buffer PA with AP=priv RO, user none. Performs privileged
 * read and verifies content matches pre-initialized data (no writes performed).
 *
 * Test Steps:
 * 1. Initialize buffer content using a writable mapping.
 * 2. Disable the MMU.
 * 3. Map an alias VA as privileged read-only, user no access.
 * 4. Enable the MMU and perform privileged read access.
 * 5. Verify read data matches expected content.
 *
 * @param[in] args
 * @return void
 */
void TestMmuP_privilegedReadOnlyUserNoAccess(void *args)
{
    volatile uint8_t *buf = (volatile uint8_t *)TestMmuP_Buffer8K;
    TestMmuP_writePattern(buf, TEST_MMUP_8KB_SIZE, 0x33u);

    /* Flush dirty lines before RO mapping */
    CacheP_wbInvAll(CacheP_TYPE_ALL);

    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t paddrBuf  = (uintptr_t)TestMmuP_Buffer8K;
    uintptr_t aliasVA   = 0x90010000u;     /* 64KB-aligned VA */
    uint32_t  size      = TEST_MMUP_8KB_SIZE;

    TestMmuP_resetMMU();                    /* start clean */

    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RO_USER_NONE;
#if defined(ENABLE_C75_CORE)
    attrs.attrIndx   = MMUP_ATTRINDX_MAIR7;  /* cacheable on C75 */
#else /* C75 and others */
    attrs.attrIndx   = MMUP_ATTRINDX_MAIR4;  /* non-cacheable on A53 */
#endif
    attrs.shareable  = MMUP_SHARABLE_OUTER;
    attrs.global     = 1;

    status = MmuP_map(aliasVA, paddrBuf, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vaPtr = (volatile uint8_t *)aliasVA;

#if defined(ENABLE_C75_CORE)
    /* C75: invalidate before reading cacheable RO alias */
    CacheP_inv((void *)vaPtr, size, CacheP_TYPE_ALL);
#endif
    TestMmuP_checkPattern(vaPtr, size, 0x33u);
}

/**
 * @brief Verifies privileged read/write succeeds when both privileged and user access are enabled.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Map a buffer with privileged and user read/write permissions.
 * 3. Enable the MMU and perform privileged read/write access.
 * 4. Verify data integrity.
 */
void TestMmuP_privilegedAndUserReadWrite(void *args)
{
    MmuP_MapAttrs attrs;
    int32_t status;
    uintptr_t vaddr = 0x90020000u;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t size = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.attrIndx = MMUP_ATTRINDX_MAIR7;
    attrs.global = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x44u);
    CacheP_wb((void *)vp, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x44u);
}

/**
 * @brief Verifies privileged read succeeds when both privileged and user access are read-only.
 *
 * Test Steps:
 * 1. Initialize buffer content using a writable mapping.
 * 2. Disable the MMU.
 * 3. Map an alias as read-only for both privileged and user access.
 * 4. Enable the MMU and perform privileged read access.
 * 5. Verify data integrity.
 */
void TestMmuP_privilegedAndUserReadOnly(void *args)
{
    volatile uint8_t *buf = (volatile uint8_t *)TestMmuP_Buffer8K;
    TestMmuP_writePattern(buf, TEST_MMUP_8KB_SIZE, 0x55u);

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_MapAttrs attrs;
    int32_t status;
    uintptr_t vaddr = 0x90030000u;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer8K;
    uint32_t size = TEST_MMUP_8KB_SIZE;

    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RO_USER_RO;
    attrs.shareable = MMUP_SHARABLE_OUTER;
#if defined(ENABLE_A53_CORE)
    attrs.attrIndx   = MMUP_ATTRINDX_MAIR4;        /* Normal non-cacheable on A53 */
#else /* C75 and others */
    attrs.attrIndx   = MMUP_ATTRINDX_MAIR7;        /* Normal WBWA on C75 */
#endif
    attrs.global = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
#if defined(ENABLE_C75_CORE)
    /* C75: keep alias cacheable, invalidate before read to avoid stale lines */
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
#endif
    TestMmuP_checkPattern(vp, size, 0x55u);
}

#if !defined(ENABLE_C75_CORE) /* exception dump/hang in c75 core  */
/* Execute allowed for privileged and user: alias VA -> real PA in .text */
void TestMmuP_executeAllowedForPrivilegedAndUser(void *args)
{
    (void)args;

    /* Compute page and offset of the function */
    uintptr_t funcVA    = (uintptr_t)TestMmuP_executeStubFunction;
    uintptr_t paddrPage = TEST_MMUP_ALIGN_DOWN(funcVA, TEST_MMUP_PAGE_SIZE);
    uint32_t  funcOff   = (uint32_t)(funcVA - paddrPage);


    const uintptr_t aliasVA = 0x90040000u; /* 64KB-aligned alias VA */
    const uint32_t  size    = TEST_MMUP_PAGE_SIZE;

    /* Sanity */
    TEST_ASSERT_EQUAL_UINT32(0u, (aliasVA & (TEST_MMUP_PAGE_SIZE - 1u)));
    TEST_ASSERT_TRUE(funcOff < TEST_MMUP_PAGE_SIZE);

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs attrs;
    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm  = MMUP_ACCESS_PERM_PRIV_RO_USER_RO; /* code: read-only */
    attrs.privExecute = 1;
    attrs.userExecute = 1;
    attrs.shareable   = MMUP_SHARABLE_OUTER;
    attrs.attrIndx    = MMUP_ATTRINDX_MAIR7;              /* Normal WBWA */
    attrs.global      = 1;
    int32_t status = MmuP_map(aliasVA, paddrPage, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();
    /* Optional: verify we can read code bytes via alias */
#if defined(ENABLE_C75_CORE)
    volatile uint32_t *alias32 = (volatile uint32_t *)(aliasVA + funcOff);
    CacheP_inv((void *)alias32, 64, CacheP_TYPE_ALL);
#endif /* ENABLE_C75_CORE */
    /* Ensure I-side sees new alias */
    TestMmuP_syncI(aliasVA + funcOff, 128);
    exec_stub_t aliasFn = (exec_stub_t)(aliasVA + funcOff);
    int retViaOrig  = TestMmuP_executeStubFunction();
    int retViaAlias = aliasFn();

    TEST_ASSERT_EQUAL_INT(0x1234ABCD, retViaOrig);
    TEST_ASSERT_EQUAL_INT(0x1234ABCD, retViaAlias);
}

/* Execute privileged only (user execute disabled) */
void TestMmuP_executePrivilegedOnly(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    /* Function VA, page-aligned PA, and entry offset */
    uintptr_t funcVA    = (uintptr_t)TestMmuP_executeStubFunction;
    uintptr_t paddrPage = TEST_MMUP_ALIGN_DOWN(funcVA, TEST_MMUP_PAGE_SIZE);
    uint32_t  funcOff   = (uint32_t)(funcVA - paddrPage);

    const uintptr_t aliasVA = 0x90050000u;      /* 4KB/64KB aligned alias */
    const uint32_t  size    = TEST_MMUP_PAGE_SIZE;

    /* Sanity */
    TEST_ASSERT_EQUAL_UINT32(0u, (aliasVA & (TEST_MMUP_PAGE_SIZE - 1u)));
    TEST_ASSERT_TRUE(funcOff < TEST_MMUP_PAGE_SIZE);

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm  = MMUP_ACCESS_PERM_PRIV_RO_USER_RO;
    attrs.privExecute = 1;
    attrs.userExecute = 0;                    /* user execute disabled */
    attrs.shareable   = MMUP_SHARABLE_OUTER;
    attrs.attrIndx    = MMUP_ATTRINDX_MAIR7;  /* Normal WBWA */
    attrs.global      = 1;

    status = MmuP_map(aliasVA, paddrPage, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    /* Optional: compare code word via alias vs original */
#if defined(ENABLE_C75_CORE)
    volatile uint32_t *alias32 = (volatile uint32_t *)(aliasVA + funcOff);
    CacheP_inv((void *)alias32, 64, CacheP_TYPE_ALL);
#endif

    /* I-side sync at the actual entry */
    TestMmuP_syncI(aliasVA + funcOff, 128);

    exec_stub_t aliasFn = (exec_stub_t)(aliasVA + funcOff);
    int result = aliasFn();
    TEST_ASSERT_EQUAL_INT(0x1234ABCD, result);
}

/* Execute across page boundary */
void TestMmuP_executeAcrossPageBoundary(void *args)
{
    (void)args;

    /* Compute page base and offset */
    uintptr_t funcVA    = (uintptr_t)TestMmuP_executeStubBoundaryFunction;
    uintptr_t basePage  = TEST_MMUP_ALIGN_DOWN(funcVA, TEST_MMUP_PAGE_SIZE);
    uint32_t  funcOff   = (uint32_t)(funcVA - basePage);

    /* Require that the entry is close enough to end of page to fetch next page.
       If not, skip instead of forcing unsafe memcpy relocation. */
    if (funcOff < (TEST_MMUP_PAGE_SIZE - 32u)) {
        TEST_IGNORE_MESSAGE("Boundary stub not placed near page end; skipping.");
        return;
    }

    const uintptr_t aliasVA = 0x90060000u;          /* 4KB/64KB aligned alias */
    const uint32_t  mapSz   = (2u * TEST_MMUP_PAGE_SIZE); /* map 8KB (two pages) */

    /* Sanity */
    TEST_ASSERT_EQUAL_UINT32(0u, (aliasVA & (TEST_MMUP_PAGE_SIZE - 1u)));

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs attrs;
    MmuP_MapAttrs_init(&attrs);
    attrs.accessPerm  = MMUP_ACCESS_PERM_PRIV_RO_USER_RO;
    attrs.privExecute = 1;
    attrs.userExecute = 1;
    attrs.shareable   = MMUP_SHARABLE_OUTER;
    attrs.attrIndx    = MMUP_ATTRINDX_MAIR7;
    attrs.global      = 1;

    /* Map both pages so fetch can cross the boundary safely */
    int32_t status = MmuP_map(aliasVA, basePage, mapSz, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    /* I-side sync at alias entry; include both pages */
    TestMmuP_syncI(aliasVA + funcOff, 2 * 128);

    exec_stub_t aliasFn = (exec_stub_t)(aliasVA + funcOff);
    int ret = aliasFn();
    TEST_ASSERT_EQUAL_INT(0xDEADBEEF, ret);
}
#endif /* !ENABLE_C75_CORE - exception dump/hang in c75 core  */

/**
 * @brief Verifies functional read/write access for a non-shareable Normal cacheable mapping on one core.
 *
 * Test Steps:
 * 1. Initialize mapping attributes; set shareable to non-shareable and MAIR index to MAIR7.
 * 2. Disable the MMU and disable caches (writeback+invalidate).
 * 3. Map the region using MmuP_map().
 * 4. Enable the MMU and enable caches (restore by MmuP_enable()).
 * 5. Write a pattern through the virtual address.
 * 6. Perform cache write-back and invalidate.
 * 7. Read back data and verify correctness.
 *
 * @param[in] args
 */
void TestMmuP_nonShareableSingleCoreReadWrite(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = TEST_MMUP_ALIAS_NONSHAREABLE_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.shareable = MMUP_SHARABLE_NONE;
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7; /* Normal WB/WA */
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.global    = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x71u);
    CacheP_wb((void *)vp, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x71u);
}

/**
 * @brief Verifies functional read/write access for an inner-shareable Normal cacheable mapping on one core.
 *
 * Test Steps:
 * 1. Initialize mapping attributes; set shareable to inner-shareable and MAIR index to MAIR7.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU and caches.
 * 5. Write a pattern and read back to verify.
 * 6. Perform cache maintenance and verify data again.
 *
 * @param[in] args
 */
void TestMmuP_innerShareableSingleCoreReadWrite(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = TEST_MMUP_ALIAS_INNER_SHAREABLE_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.shareable = MMUP_SHARABLE_INNER;
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.global    = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x72u);
    CacheP_wb((void *)vp, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x72u);
}

/**
 * @brief Verifies functional read/write access for an outer-shareable Normal cacheable mapping on one core.
 *
 * Test Steps:
 * 1. Initialize mapping attributes; set shareable to outer-shareable and MAIR index to MAIR7.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU and caches.
 * 5. Write and read data.
 * 6. Perform cache maintenance and verify correctness.
 *
 * @param[in] args
 */
void TestMmuP_outerShareableSingleCoreReadWrite(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = TEST_MMUP_ALIAS_OUTER_SHAREABLE_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.global    = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x73u);
    CacheP_wb((void *)vp, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x73u);
}

/**
 * @brief Verifies read/write data integrity using MAIR slot 0 attributes.
 *
 * Test Steps:
 * 1. Initialize mapping attributes with MAIR slot 0 and outer-shareable.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU.
 * 5. Write a pattern and read back.
 * 6. Verify data integrity.
 *
 * @param[in] args
 */
void TestMmuP_mairSlot0ReadWrite(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = TEST_MMUP_ALIAS_MAIR0_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR0;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.global    = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x80u);
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x80u);
}

/**
 * @brief Verifies read/write data integrity using MAIR slot 1 attributes.
 *
 * Test Steps:
 * 1. Initialize mapping attributes with MAIR slot 1.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU.
 * 5. Write and read data.
 * 6. Verify correctness.
 *
 * @param[in] args
 */
void TestMmuP_mairSlot1ReadWrite(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = TEST_MMUP_ALIAS_MAIR1_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR1;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.global    = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x81u);
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x81u);
}

/**
 * @brief Verifies read/write data integrity using MAIR slot 2 attributes.
 *
 * Test Steps:
 * 1. Initialize mapping attributes with MAIR slot 2.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU.
 * 5. Write and read data.
 * 6. Verify correctness.
 *
 * @param[in] args
 */
void TestMmuP_mairSlot2ReadWrite(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = TEST_MMUP_ALIAS_MAIR2_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR2;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.global    = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x82u);
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x82u);
}

/**
 * @brief Verifies read/write data integrity using MAIR slot 3 attributes.
 *
 * Test Steps:
 * 1. Initialize mapping attributes with MAIR slot 3.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU.
 * 5. Write and read data.
 * 6. Verify correctness.
 *
 * @param[in] args
 */
void TestMmuP_mairSlot3ReadWrite(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;

    uintptr_t vaddr = TEST_MMUP_ALIAS_MAIR3_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR3;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.global    = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x83u);
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x83u);
}

/**
 * @brief Verifies ordered and stable access for a device or non-cacheable MAIR slot 4 mapping.
 *
 * Test Steps:
 * 1. Initialize mapping attributes with MAIR slot 4.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU.
 * 5. Perform ordered write followed by immediate read.
 * 6. Verify read data matches written value.
 *
 * @param[in] args
 */
void TestMmuP_mairSlot4DeviceAccess(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;
    uint32_t i;

    uintptr_t vaddr = TEST_MMUP_ALIAS_DEVICE_MAIR4_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    /* For device mappings, avoid cache operations around the alias VA */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR4;    /* Device/non-cacheable attributes */
    attrs.shareable = MMUP_SHARABLE_OUTER;    /* Shareability ignored for device types on some cores */
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.global    = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    /* Ordered write then immediate read-back */
    for (i = 0; i < size; i++)
    {
        vp[i] = (uint8_t)(0x90u + (uint8_t)i);
        TEST_ASSERT_EQUAL_UINT8((uint8_t)(0x90u + (uint8_t)i), vp[i]);
    }
}

/**
 * @brief Verifies read/write data integrity using MAIR slot 5 attributes.
 *
 * Test Steps:
 * 1. Initialize mapping attributes with MAIR slot 5.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU.
 * 5. Write and read data.
 * 6. Verify correctness.
 *
 * @param[in] args
 */
void TestMmuP_mairSlot5ReadWrite(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;
    uintptr_t vaddr = TEST_MMUP_ALIAS_MAIR5_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR5;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    attrs.global    = 1;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vp = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(vp, size, 0x85u);
    CacheP_inv((void *)vp, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vp, size, 0x85u);
}

/**
 * @brief Verifies functional access for a global mapping across MMU disable/enable cycles.
 *
 * Test Steps:
 * 1. Initialize mapping attributes with global bit enabled.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU.
 * 5. Write and read data to verify access.
 * 6. Disable and re-enable the MMU.
 * 7. Write and read again to verify mapping persists.
 *
 * @param[in] args
 */
void TestMmuP_globalMappingSingleContext(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;
    uintptr_t vaddr = TEST_MMUP_ALIAS_NONGLOBAL_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer8K;
    uint32_t  size  = TEST_MMUP_8KB_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.global    = 1;
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* First enable and access */
    MmuP_enable();
    TestMmuP_barrier();
    volatile uint8_t *va = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(va, size, 0x91u);
    CacheP_wb((void *)va, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)va, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(va, size, 0x91u);
    
    /* Cycle MMU off/on, mapping should persist */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();
    MmuP_enable();
    TestMmuP_barrier();

    /* Access again */
    TestMmuP_writePattern(va, size, 0x92u);
    CacheP_wb((void *)va, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)va, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(va, size, 0x92u);
}

/**
 * @brief Verifies functional access for a non-global mapping in the current context.
 *
 * Test Steps:
 * 1. Initialize mapping attributes with global bit disabled.
 * 2. Disable the MMU.
 * 3. Map the region.
 * 4. Enable the MMU.
 * 5. Write and read data.
 * 6. Verify correctness.
 *
 * @param[in] args
 */
void TestMmuP_nonGlobalMappingSingleContext(void *args)
{
    (void)args;
    MmuP_MapAttrs attrs;
    int32_t status;
    uintptr_t vaddr = TEST_MMUP_ALIAS_NONGLOBAL_RW_4K;
    uintptr_t paddr = (uintptr_t)TestMmuP_Buffer4K;
    uint32_t  size  = TEST_MMUP_PAGE_SIZE;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrs);
    attrs.global    = 0;
    attrs.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrs.shareable = MMUP_SHARABLE_OUTER;
    attrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;

    status = MmuP_map(vaddr, paddr, size, &attrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *va = (volatile uint8_t *)vaddr;
    TestMmuP_writePattern(va, size, 0x93u);
    CacheP_wb((void *)va, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)va, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(va, size, 0x93u);

    /* Added extra MMU cycle */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();
    MmuP_enable();
    TestMmuP_barrier();

    /* Access should still work in same context */
    TestMmuP_writePattern(va, size, 0x94u);
    CacheP_wb((void *)va, size, CacheP_TYPE_ALL);
    CacheP_inv((void *)va, size, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(va, size, 0x94u);

    /* Cleanup so next tests start clean */
     CacheP_wbInvAll(CacheP_TYPE_ALL);
     MmuP_disable();
     TestMmuP_barrier();
     TestMmuP_enableAndSync();
}

/**
 * @brief Verifies correct read behavior for an overlapping subset region with different attributes.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Map region A as Normal cacheable and outer-shareable.
 * 3. Map overlapping subset region B with different attributes.
 * 4. Enable the MMU.
 * 5. Initialize memory through region A.
 * 6. Read through region B and non-overlapping region A.
 * 7. Verify data correctness in both cases.
 *
 * @param[in] args
 */
void TestMmuP_overlappingSubsetReadBehavior(void *args)
{
    (void)args;
    MmuP_MapAttrs attrsA, attrsB;
    int32_t status;

    /* Region A: 8KB; Region B: 4KB subset of same PA */
    uintptr_t paddrA = (uintptr_t)TestMmuP_Buffer8K;
    uintptr_t paddrB = (uintptr_t)TestMmuP_Buffer8K; /* subset at start */

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    /* Map A: Normal WB/WA, outer-shareable */
    MmuP_MapAttrs_init(&attrsA);
    attrsA.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrsA.shareable = MMUP_SHARABLE_OUTER;
    attrsA.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    status = MmuP_map(TEST_MMUP_ALIAS_OVERLAP_A_RW_8K, paddrA, TEST_MMUP_8KB_SIZE, &attrsA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Map B: Different attributes (e.g., inner-shareable) on 4KB subset */
    MmuP_MapAttrs_init(&attrsB);
    attrsB.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrsB.shareable = MMUP_SHARABLE_INNER;
    attrsB.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    status = MmuP_map(TEST_MMUP_ALIAS_OVERLAP_B_RW_4K, paddrB, TEST_MMUP_PAGE_SIZE, &attrsB);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    /* Initialize via region A */
    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_ALIAS_OVERLAP_A_RW_8K;
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_ALIAS_OVERLAP_B_RW_4K;
    TestMmuP_writePattern(vaA, TEST_MMUP_8KB_SIZE, 0xA1u);
    CacheP_wb((void *)vaA, TEST_MMUP_8KB_SIZE, CacheP_TYPE_ALL);

    /* Read through region B (subset) and remaining A */
    CacheP_inv((void *)vaB, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaB, TEST_MMUP_PAGE_SIZE, 0xA1u);
    CacheP_inv((void *)(vaA + TEST_MMUP_PAGE_SIZE), (TEST_MMUP_8KB_SIZE - TEST_MMUP_PAGE_SIZE), CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaA + TEST_MMUP_PAGE_SIZE, (TEST_MMUP_8KB_SIZE - TEST_MMUP_PAGE_SIZE), 0xA1u);
}

/**
 * @brief Verifies independent functional access to two non-overlapping regions.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Map region A with one set of attributes.
 * 3. Map region B with different attributes.
 * 4. Enable the MMU.
 * 5. Perform read/write access in both regions.
 * 6. Verify both operate independently and correctly.
 *
 * @param[in] args
 */
void TestMmuP_nonOverlappingIndependentRegions(void *args)
{
    (void)args;
    MmuP_MapAttrs attrsA, attrsB;
    int32_t status;

    uintptr_t paddrA = (uintptr_t)TestMmuP_Buffer4K;
    uintptr_t paddrB = (uintptr_t)TestMmuP_Buffer64K;

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();

    MmuP_MapAttrs_init(&attrsA);
    attrsA.attrIndx  = MMUP_ATTRINDX_MAIR7;
    attrsA.shareable = MMUP_SHARABLE_OUTER;
    attrsA.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    status = MmuP_map(TEST_MMUP_ALIAS_NONOVERLAP_A_RW_4K, paddrA, TEST_MMUP_PAGE_SIZE, &attrsA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_MapAttrs_init(&attrsB);
    attrsB.attrIndx  = MMUP_ATTRINDX_MAIR0; /* different MAIR */
    attrsB.shareable = MMUP_SHARABLE_NONE;
    attrsB.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    status = MmuP_map(TEST_MMUP_ALIAS_NONOVERLAP_B_RW_64K, paddrB, TEST_MMUP_64KB_SIZE, &attrsB);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_ALIAS_NONOVERLAP_A_RW_4K;
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_ALIAS_NONOVERLAP_B_RW_64K;
    TestMmuP_writePattern(vaA, TEST_MMUP_PAGE_SIZE, 0xB1u);
    TestMmuP_writePattern(vaB, TEST_MMUP_64KB_SIZE, 0xB2u);
    CacheP_wb((void *)vaA, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_wb((void *)vaB, TEST_MMUP_64KB_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaA, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    CacheP_inv((void *)vaB, TEST_MMUP_64KB_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaA, TEST_MMUP_PAGE_SIZE, 0xB1u);
    TestMmuP_checkPattern(vaB, TEST_MMUP_64KB_SIZE, 0xB2u);
}

/**
 * @brief Verifies read-only access in an overlapping subset and read/write access outside it.
 *
 * Test Steps:
 * 1. Disable the MMU.
 * 2. Map region A as read/write.
 * 3. Map overlapping subset region B as read-only.
 * 4. Enable the MMU.
 * 5. Read data within the read-only subset.
 * 6. Write and read data outside the subset.
 * 7. Verify all accesses behave as expected.
 *
 * @param[in] args
 */
void TestMmuP_overlappingReadOnlySubsetAndReadWriteOutside(void *args)
{
    (void)args;
    MmuP_MapAttrs attrsA, attrsB;
    int32_t status;

    uintptr_t paddrA = (uintptr_t)TestMmuP_Buffer8K;
    uintptr_t paddrB = (uintptr_t)TestMmuP_Buffer8K + TEST_MMUP_PAGE_SIZE; /* middle subset */

    /* Pre-clean everything, then start from a clean MMU state */
    CacheP_wbInvAll(CacheP_TYPE_ALL);
    TestMmuP_resetMMU();
    MmuP_disable();
    TestMmuP_barrier();

    /* A: RW over full 8KB (cacheable) */
    MmuP_MapAttrs_init(&attrsA);
    attrsA.attrIndx   = MMUP_ATTRINDX_MAIR7;              /* Normal WBWA */
    attrsA.shareable  = MMUP_SHARABLE_OUTER;
    attrsA.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_RW;
    status = MmuP_map(TEST_MMUP_ALIAS_OVERLAP_RW_A_8K, paddrA, TEST_MMUP_8KB_SIZE, &attrsA);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* B: RO over 4KB subset */
    MmuP_MapAttrs_init(&attrsB);
#if defined(ENABLE_A53_CORE)
    attrsB.attrIndx   = MMUP_ATTRINDX_MAIR4;              /* non-cacheable on A53 */
#else
    attrsB.attrIndx   = MMUP_ATTRINDX_MAIR7;              /* cacheable on C75 */
#endif
    attrsB.shareable  = MMUP_SHARABLE_OUTER;
    attrsB.accessPerm = MMUP_ACCESS_PERM_PRIV_RO_USER_RO;
    status = MmuP_map(TEST_MMUP_ALIAS_OVERLAP_RO_B_4K, paddrB, TEST_MMUP_PAGE_SIZE, &attrsB);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MmuP_enable();
    TestMmuP_barrier();

    volatile uint8_t *vaA = (volatile uint8_t *)TEST_MMUP_ALIAS_OVERLAP_RW_A_8K;
    volatile uint8_t *vaB = (volatile uint8_t *)TEST_MMUP_ALIAS_OVERLAP_RO_B_4K;

    /* Initialize entire region via A (writable alias) */
    TestMmuP_writePattern(vaA, TEST_MMUP_8KB_SIZE, 0xC1u);
    CacheP_wb((void *)vaA, TEST_MMUP_8KB_SIZE, CacheP_TYPE_ALL);

#if defined(ENABLE_C75_CORE)
    /* C75: invalidate RO alias before reading */
    CacheP_inv((void *)vaB, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
#endif
    TestMmuP_checkPattern(vaB, TEST_MMUP_PAGE_SIZE, 0xC1u);

    /* Write outside subset via A (first 4KB) */
    TestMmuP_writePattern(vaA, TEST_MMUP_PAGE_SIZE, 0xC2u);
    CacheP_wb((void *)vaA, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);

#if defined(ENABLE_C75_CORE)
    CacheP_inv((void *)vaB, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
#endif
    TestMmuP_checkPattern(vaB, TEST_MMUP_PAGE_SIZE, 0xC1u);

    /* Verify A: outside updated */
    CacheP_inv((void *)vaA, TEST_MMUP_PAGE_SIZE, CacheP_TYPE_ALL);
    TestMmuP_checkPattern(vaA, TEST_MMUP_PAGE_SIZE, 0xC2u);

    CacheP_wbInvAll(CacheP_TYPE_ALL);
    MmuP_disable();
    TestMmuP_barrier();
    TestMmuP_enableAndSync();
}

#endif /*TEST_SINGLE_THREAD_MMU*/

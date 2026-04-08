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

/** \file test_ddr_mt.c
 *
 *  \brief DDR multi-threaded (FreeRTOS) test cases.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/ddr.h>
#include <drivers/ddr/v1/csl_emif.h>
#include <drivers/soc.h>
#include "ti_drivers_open_close.h"
#include "test_ddr.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** DDR base address */
#define TEST_DDR_MT_BASE_ADDR            (0x80000000U)

/** Number of concurrent tasks */
#define TEST_DDR_MT_NUM_TASKS            (4U)

/** Per-task DDR region size: 1 MB */
#define TEST_DDR_MT_REGION_SIZE          (0x100000U)

/** Number of read iterations per task */
#define TEST_DDR_MT_READ_ITERATIONS      (10U)

/** Number of write iterations for stress loops */
#define TEST_DDR_MT_WRITE_ITERATIONS     (10U)

/** Number of ECC toggle iterations */
#define TEST_DDR_MT_ECC_TOGGLE_ITERS     (10U)

/** Task stack size */
#define TEST_DDR_MT_TASK_STACK_SIZE      (4U * 1024U)

/** Task priority */
#define TEST_DDR_MT_TASK_PRIORITY        (3U)

/** Test patterns per task */
#define TEST_DDR_MT_PATTERN_TASK0        (0xDEADBEEFU)
#define TEST_DDR_MT_PATTERN_TASK1        (0xA5A5A5A5U)
#define TEST_DDR_MT_PATTERN_TASK2        (0x5A5A5A5AU)
#define TEST_DDR_MT_PATTERN_TASK3        (0x12345678U)

/** Region base addresses for 4 non-overlapping regions.
 *  Each region is 1 MB offset from DDR base + 16 MB. */
#define TEST_DDR_MT_REGION_BASE          (TEST_DDR_MT_BASE_ADDR + 0x01000000U)
#define TEST_DDR_MT_REGION0_ADDR         (TEST_DDR_MT_REGION_BASE + (0U * TEST_DDR_MT_REGION_SIZE))
#define TEST_DDR_MT_REGION1_ADDR         (TEST_DDR_MT_REGION_BASE + (1U * TEST_DDR_MT_REGION_SIZE))
#define TEST_DDR_MT_REGION2_ADDR         (TEST_DDR_MT_REGION_BASE + (2U * TEST_DDR_MT_REGION_SIZE))
#define TEST_DDR_MT_REGION3_ADDR         (TEST_DDR_MT_REGION_BASE + (3U * TEST_DDR_MT_REGION_SIZE))

/** Shared region for mutex-protected read/write test */
#define TEST_DDR_MT_SHARED_REGION_ADDR   (TEST_DDR_MT_REGION_BASE + (4U * TEST_DDR_MT_REGION_SIZE))
#define TEST_DDR_MT_SHARED_REGION_SIZE   (0x10000U)  /* 64 KB */

/** ECC test region offsets */
#define TEST_DDR_MT_ECC_REGION_START     (0x00000000U)

/** Memory block for which ECC is calculated */
#define TEST_DDR_MT_ECC_MEM_BLOCK_SIZE   (0x200U)
/** ECC data size per block */
#define TEST_DDR_MT_ECC_DATA_PER_BLOCK   (0x40U)

/** ECC test address */
#define TEST_DDR_MT_ECC_TEST_ADDR        (TEST_DDR_MT_BASE_ADDR + TEST_DDR_MT_ECC_REGION_START \
                                     + TEST_DDR_MT_ECC_MEM_BLOCK_SIZE)

/** Task completion timeout */
#define TEST_DDR_MT_TASK_TIMEOUT_MS      (10000U)

/* ========================================================================== */
/*                          Structure Definitions                             */
/* ========================================================================== */

/** Per-task argument structure */
typedef struct TestDdr_MtTaskArg_s
{
    uint32_t            taskId;
    volatile uint32_t  *regionAddr;
    uint32_t            regionSize;
    uint32_t            pattern;
    uint32_t            iterations;
    volatile int32_t   *pPassCount;
    volatile int32_t   *pFailCount;
    SemaphoreP_Object  *pDoneSem;
    SemaphoreP_Object  *pMutex;
} TestDdr_MtTaskArg;

/* ========================================================================== */
/*                          Global Variables                                  */
/* ========================================================================== */

static uint8_t       TestDdr_MtTaskStack[TEST_DDR_MT_NUM_TASKS][TEST_DDR_MT_TASK_STACK_SIZE]
                     __attribute__((aligned(64)));

static SemaphoreP_Object TestDdr_MtDoneSem;
static SemaphoreP_Object TestDdr_MtMutex;
static volatile int32_t TestDdr_MtPassCount;
static volatile int32_t TestDdr_MtFailCount;

static TestDdr_MtTaskArg TestDdr_MtTaskArgs[TEST_DDR_MT_NUM_TASKS];

/** Patterns array indexed by task ID */
static const uint32_t TestDdr_MtPatterns[TEST_DDR_MT_NUM_TASKS] = {
    TEST_DDR_MT_PATTERN_TASK0,
    TEST_DDR_MT_PATTERN_TASK1,
    TEST_DDR_MT_PATTERN_TASK2,
    TEST_DDR_MT_PATTERN_TASK3,
};

/** Region addresses indexed by task ID */
static volatile uint32_t * const TestDdr_MtRegionAddrs[TEST_DDR_MT_NUM_TASKS] = {
    (volatile uint32_t *)TEST_DDR_MT_REGION0_ADDR,
    (volatile uint32_t *)TEST_DDR_MT_REGION1_ADDR,
    (volatile uint32_t *)TEST_DDR_MT_REGION2_ADDR,
    (volatile uint32_t *)TEST_DDR_MT_REGION3_ADDR,
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void TestDdr_mtFillRegion(volatile uint32_t *addr, uint32_t sizeBytes,
                                 uint32_t pattern);
static int32_t TestDdr_mtVerifyRegion(volatile uint32_t *addr, uint32_t sizeBytes,
                                      uint32_t pattern);
/* Task entry functions */
static void TestDdr_mtReadTask(void *arg);
static void TestDdr_mtWriteTask(void *arg);
static void TestDdr_mtReadWriteMutexTaskA(void *arg);
static void TestDdr_mtReadWriteMutexTaskB(void *arg);
static void TestDdr_mtWriteTaskDiffRegion(void *arg);
static void TestDdr_mtReadTaskDiffRegion(void *arg);
static void TestDdr_mtEccToggleTask(void *arg);
static void TestDdr_mtEccTrafficTask(void *arg);

/* ========================================================================== */
/*                 Internal Helper Function Definitions                       */
/* ========================================================================== */

/**
 * \brief Fill a DDR memory region with a 32-bit pattern.
 */
static void TestDdr_mtFillRegion(volatile uint32_t *addr, uint32_t sizeBytes,
                                 uint32_t pattern)
{
    uint32_t i;
    uint32_t count = sizeBytes / sizeof(uint32_t);

    for (i = 0U; i < count; i++)
    {
        addr[i] = pattern;
    }
    CacheP_wbInv((void *)addr, sizeBytes, CacheP_TYPE_ALL);
}

/**
 * \brief Verify a DDR memory region contains the expected 32-bit pattern.
 * \return SystemP_SUCCESS if all words match, SystemP_FAILURE otherwise.
 */
static int32_t TestDdr_mtVerifyRegion(volatile uint32_t *addr, uint32_t sizeBytes,
                                      uint32_t pattern)
{
    uint32_t i;
    uint32_t count = sizeBytes / sizeof(uint32_t);

    CacheP_inv((void *)addr, sizeBytes, CacheP_TYPE_ALL);

    for (i = 0U; i < count; i++)
    {
        if (addr[i] != pattern)
        {
            DebugP_log("DDR MT verify fail: addr=0x%08X, exp=0x%08X, got=0x%08X\r\n",
                       (uint32_t)(uintptr_t)&addr[i], pattern, addr[i]);
            return SystemP_FAILURE;
        }
    }
    return SystemP_SUCCESS;
}

/* ========================================================================== */
/*                     Task Entry Functions                                   */
/* ========================================================================== */

/**
 * \brief Task that reads and verifies a pre-written DDR region repeatedly.
 */
static void TestDdr_mtReadTask(void *arg)
{
    TestDdr_MtTaskArg *taskArg = (TestDdr_MtTaskArg *)arg;
    int32_t  status = SystemP_SUCCESS;
    uint32_t iter;

    for (iter = 0U; iter < taskArg->iterations; iter++)
    {
        status = TestDdr_mtVerifyRegion(taskArg->regionAddr, taskArg->regionSize,
                                        taskArg->pattern);
        if (status != SystemP_SUCCESS)
        {
            break;
        }
    }

    SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);
    if (status == SystemP_SUCCESS)
    {
        (*taskArg->pPassCount)++;
    }
    else
    {
        (*taskArg->pFailCount)++;
    }
    SemaphoreP_post(taskArg->pMutex);

    SemaphoreP_post(taskArg->pDoneSem);
    TaskP_exit();
}

/**
 * \brief Task that writes a unique pattern to its DDR region.
 */
static void TestDdr_mtWriteTask(void *arg)
{
    TestDdr_MtTaskArg *taskArg = (TestDdr_MtTaskArg *)arg;
    int32_t  status;

    TestDdr_mtFillRegion(taskArg->regionAddr, taskArg->regionSize, taskArg->pattern);

    /* Verify own write */
    status = TestDdr_mtVerifyRegion(taskArg->regionAddr, taskArg->regionSize,
                                    taskArg->pattern);

    SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);
    if (status == SystemP_SUCCESS)
    {
        (*taskArg->pPassCount)++;
    }
    else
    {
        (*taskArg->pFailCount)++;
    }
    SemaphoreP_post(taskArg->pMutex);

    SemaphoreP_post(taskArg->pDoneSem);
    TaskP_exit();
}

/**
 * \brief Task A for mutex-protected write/read to shared region.
 */
static void TestDdr_mtReadWriteMutexTaskA(void *arg)
{
    TestDdr_MtTaskArg *taskArg = (TestDdr_MtTaskArg *)arg;
    int32_t  status = SystemP_SUCCESS;
    uint32_t iter;

    for (iter = 0U; iter < taskArg->iterations; iter++)
    {
        SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);

        /* Write pattern */
        TestDdr_mtFillRegion(taskArg->regionAddr, taskArg->regionSize, taskArg->pattern);

        /* Read back and verify within mutex */
        status = TestDdr_mtVerifyRegion(taskArg->regionAddr, taskArg->regionSize,
                                        taskArg->pattern);

        SemaphoreP_post(taskArg->pMutex);

        if (status != SystemP_SUCCESS)
        {
            break;
        }
    }

    SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);
    if (status == SystemP_SUCCESS)
    {
        (*taskArg->pPassCount)++;
    }
    else
    {
        (*taskArg->pFailCount)++;
    }
    SemaphoreP_post(taskArg->pMutex);

    SemaphoreP_post(taskArg->pDoneSem);
    TaskP_exit();
}

/**
 * \brief Task B for mutex-protected write/read to shared region.
 */
static void TestDdr_mtReadWriteMutexTaskB(void *arg)
{
    TestDdr_MtTaskArg *taskArg = (TestDdr_MtTaskArg *)arg;
    int32_t  status = SystemP_SUCCESS;
    uint32_t iter;

    for (iter = 0U; iter < taskArg->iterations; iter++)
    {
        SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);

        /* Write pattern */
        TestDdr_mtFillRegion(taskArg->regionAddr, taskArg->regionSize, taskArg->pattern);

        /* Read back and verify within mutex */
        status = TestDdr_mtVerifyRegion(taskArg->regionAddr, taskArg->regionSize,
                                        taskArg->pattern);

        SemaphoreP_post(taskArg->pMutex);

        if (status != SystemP_SUCCESS)
        {
            break;
        }
    }

    SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);
    if (status == SystemP_SUCCESS)
    {
        (*taskArg->pPassCount)++;
    }
    else
    {
        (*taskArg->pFailCount)++;
    }
    SemaphoreP_post(taskArg->pMutex);

    SemaphoreP_post(taskArg->pDoneSem);
    TaskP_exit();
}

/**
 * \brief Task that writes a pattern to its own region .
 */
static void TestDdr_mtWriteTaskDiffRegion(void *arg)
{
    TestDdr_MtTaskArg *taskArg = (TestDdr_MtTaskArg *)arg;
    int32_t  status;

    TestDdr_mtFillRegion(taskArg->regionAddr, taskArg->regionSize, taskArg->pattern);

    /* Verify own write */
    status = TestDdr_mtVerifyRegion(taskArg->regionAddr, taskArg->regionSize,
                                    taskArg->pattern);

    SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);
    if (status == SystemP_SUCCESS)
    {
        (*taskArg->pPassCount)++;
    }
    else
    {
        (*taskArg->pFailCount)++;
    }
    SemaphoreP_post(taskArg->pMutex);

    SemaphoreP_post(taskArg->pDoneSem);
    TaskP_exit();
}

/**
 * \brief Task that reads and verifies pre-written data from its region.
 */
static void TestDdr_mtReadTaskDiffRegion(void *arg)
{
    TestDdr_MtTaskArg *taskArg = (TestDdr_MtTaskArg *)arg;
    int32_t  status;
    uint32_t iter;

    status = SystemP_SUCCESS;
    for (iter = 0U; iter < taskArg->iterations; iter++)
    {
        status = TestDdr_mtVerifyRegion(taskArg->regionAddr, taskArg->regionSize,
                                        taskArg->pattern);
        if (status != SystemP_SUCCESS)
        {
            break;
        }
    }

    SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);
    if (status == SystemP_SUCCESS)
    {
        (*taskArg->pPassCount)++;
    }
    else
    {
        (*taskArg->pFailCount)++;
    }
    SemaphoreP_post(taskArg->pMutex);

    SemaphoreP_post(taskArg->pDoneSem);
    TaskP_exit();
}

/**
 * \brief Task that toggles DDR_enableInlineECC on/off in a loop.
 */
static void TestDdr_mtEccToggleTask(void *arg)
{
    TestDdr_MtTaskArg *taskArg = (TestDdr_MtTaskArg *)arg;
    uint32_t iter;

    for (iter = 0U; iter < taskArg->iterations; iter++)
    {
        DDR_enableInlineECC(0U);
        ClockP_usleep(10U);
        DDR_enableInlineECC(1U);
        ClockP_usleep(10U);
    }

    SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);
    (*taskArg->pPassCount)++;
    SemaphoreP_post(taskArg->pMutex);

    SemaphoreP_post(taskArg->pDoneSem);
    TaskP_exit();
}

/**
 * \brief Task that performs DDR writes/reads in the ECC region.
 */
static void TestDdr_mtEccTrafficTask(void *arg)
{
    TestDdr_MtTaskArg *taskArg = (TestDdr_MtTaskArg *)arg;
    volatile uint32_t *regionAddr = taskArg->regionAddr;
    uint32_t iter;
    int32_t  status = SystemP_SUCCESS;
    volatile uint32_t readVal;

    for (iter = 0U; iter < taskArg->iterations; iter++)
    {
        /* Write a pattern */
        regionAddr[0] = taskArg->pattern + iter;
        CacheP_wbInv((void *)regionAddr, 4U, CacheP_TYPE_ALL);

        /* Read back */
        CacheP_inv((void *)regionAddr, 4U, CacheP_TYPE_ALL);
        readVal = regionAddr[0];
        (void)readVal;
    }

    SemaphoreP_pend(taskArg->pMutex, SystemP_WAIT_FOREVER);
    if (status == SystemP_SUCCESS)
    {
        (*taskArg->pPassCount)++;
    }
    else
    {
        (*taskArg->pFailCount)++;
    }
    SemaphoreP_post(taskArg->pMutex);

    SemaphoreP_post(taskArg->pDoneSem);
    TaskP_exit();
}

/* ========================================================================== */
/*                     Test Case Definitions                                  */
/* ========================================================================== */

/**
 * \brief Concurrent DDR read integrity test across multiple FreeRTOS tasks.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput All 4 tasks successfully read back their pre-written patterns
 *                 across 10 iterations without corruption. PassCount == 4, FailCount == 0.
 */
void TestDdr_mtConcurrentReadFromMultipleTasks(void *arg)
{
    uint32_t i;
    TaskP_Object taskObj[TEST_DDR_MT_NUM_TASKS];
    TaskP_Params tParams;

    /* Pre-fill each region with its pattern */
    for (i = 0U; i < TEST_DDR_MT_NUM_TASKS; i++)
    {
        TestDdr_mtFillRegion(TestDdr_MtRegionAddrs[i], TEST_DDR_MT_REGION_SIZE,
                             TestDdr_MtPatterns[i]);
    }

    /* Initialize synchronization */
    TestDdr_MtPassCount = 0;
    TestDdr_MtFailCount = 0;
    SemaphoreP_constructCounting(&TestDdr_MtDoneSem, 0, TEST_DDR_MT_NUM_TASKS);
    SemaphoreP_constructMutex(&TestDdr_MtMutex);

    /* Spawn read tasks */
    for (i = 0U; i < TEST_DDR_MT_NUM_TASKS; i++)
    {
        TestDdr_MtTaskArgs[i].taskId     = i;
        TestDdr_MtTaskArgs[i].regionAddr = TestDdr_MtRegionAddrs[i];
        TestDdr_MtTaskArgs[i].regionSize = TEST_DDR_MT_REGION_SIZE;
        TestDdr_MtTaskArgs[i].pattern    = TestDdr_MtPatterns[i];
        TestDdr_MtTaskArgs[i].iterations = TEST_DDR_MT_READ_ITERATIONS;
        TestDdr_MtTaskArgs[i].pPassCount = &TestDdr_MtPassCount;
        TestDdr_MtTaskArgs[i].pFailCount = &TestDdr_MtFailCount;
        TestDdr_MtTaskArgs[i].pDoneSem   = &TestDdr_MtDoneSem;
        TestDdr_MtTaskArgs[i].pMutex     = &TestDdr_MtMutex;

        TaskP_Params_init(&tParams);
        tParams.name      = (char *)"DdrMtReadTask";
        tParams.stackSize = TEST_DDR_MT_TASK_STACK_SIZE;
        tParams.stack     = TestDdr_MtTaskStack[i];
        tParams.priority  = TEST_DDR_MT_TASK_PRIORITY;
        tParams.args      = &TestDdr_MtTaskArgs[i];
        tParams.taskMain  = TestDdr_mtReadTask;
        TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskObj[i], &tParams));
    }

    /* Wait for all tasks with timeout */
    for (i = 0U; i < TEST_DDR_MT_NUM_TASKS; i++)
    {
        TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,
            SemaphoreP_pend(&TestDdr_MtDoneSem, TEST_DDR_MT_TASK_TIMEOUT_MS),
            "DDR MT read task timeout");
    }

    /* Verify all passed */
    TEST_ASSERT_EQUAL_INT32((int32_t)TEST_DDR_MT_NUM_TASKS, TestDdr_MtPassCount);
    TEST_ASSERT_EQUAL_INT32(0, TestDdr_MtFailCount);

    /* Cleanup */
    for (i = 0U; i < TEST_DDR_MT_NUM_TASKS; i++)
    {
        TaskP_destruct(&taskObj[i]);
    }
    SemaphoreP_destruct(&TestDdr_MtDoneSem);
    SemaphoreP_destruct(&TestDdr_MtMutex);
}

/**
 * \brief Concurrent DDR write isolation test across multiple FreeRTOS tasks.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Each task writes a unique pattern to its own non-overlapping
 *                 1 MB DDR region; all regions are verified from the main context
 *                 after all tasks complete without cross-region corruption.
 */
void TestDdr_mtConcurrentWriteFromMultipleTasks(void *arg)
{
    int32_t  status;
    uint32_t i;
    TaskP_Object taskObj[TEST_DDR_MT_NUM_TASKS];
    TaskP_Params tParams;

    /* Initialize synchronization */
    TestDdr_MtPassCount = 0;
    TestDdr_MtFailCount = 0;
    SemaphoreP_constructCounting(&TestDdr_MtDoneSem, 0, TEST_DDR_MT_NUM_TASKS);
    SemaphoreP_constructMutex(&TestDdr_MtMutex);

    /* Spawn write tasks */
    for (i = 0U; i < TEST_DDR_MT_NUM_TASKS; i++)
    {
        TestDdr_MtTaskArgs[i].taskId     = i;
        TestDdr_MtTaskArgs[i].regionAddr = TestDdr_MtRegionAddrs[i];
        TestDdr_MtTaskArgs[i].regionSize = TEST_DDR_MT_REGION_SIZE;
        TestDdr_MtTaskArgs[i].pattern    = TestDdr_MtPatterns[i];
        TestDdr_MtTaskArgs[i].iterations = 1U;
        TestDdr_MtTaskArgs[i].pPassCount = &TestDdr_MtPassCount;
        TestDdr_MtTaskArgs[i].pFailCount = &TestDdr_MtFailCount;
        TestDdr_MtTaskArgs[i].pDoneSem   = &TestDdr_MtDoneSem;
        TestDdr_MtTaskArgs[i].pMutex     = &TestDdr_MtMutex;

        TaskP_Params_init(&tParams);
        tParams.name      = (char *)"DdrMtWriteTask";
        tParams.stackSize = TEST_DDR_MT_TASK_STACK_SIZE;
        tParams.stack     = TestDdr_MtTaskStack[i];
        tParams.priority  = TEST_DDR_MT_TASK_PRIORITY;
        tParams.args      = &TestDdr_MtTaskArgs[i];
        tParams.taskMain  = TestDdr_mtWriteTask;
        TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskObj[i], &tParams));
    }

    /* Wait for all tasks with timeout */
    for (i = 0U; i < TEST_DDR_MT_NUM_TASKS; i++)
    {
        TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,
            SemaphoreP_pend(&TestDdr_MtDoneSem, TEST_DDR_MT_TASK_TIMEOUT_MS),
            "DDR MT write task timeout");
    }

    /* Verify each region from main context */
    for (i = 0U; i < TEST_DDR_MT_NUM_TASKS; i++)
    {
        status = TestDdr_mtVerifyRegion(TestDdr_MtRegionAddrs[i], TEST_DDR_MT_REGION_SIZE,
                                        TestDdr_MtPatterns[i]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Cleanup */
    for (i = 0U; i < TEST_DDR_MT_NUM_TASKS; i++)
    {
        TaskP_destruct(&taskObj[i]);
    }
    SemaphoreP_destruct(&TestDdr_MtDoneSem);
    SemaphoreP_destruct(&TestDdr_MtMutex);
}

/**
 * \brief Mutex-protected concurrent DDR read/write integrity test on the same region.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Both tasks complete successfully (PassCount == 2, FailCount == 0);
 *                 the shared region holds one of the two expected patterns with no
 *                 partial corruption; within each mutex-protected iteration the
 *                 write-then-read-back comparison always passes.
 */
void TestDdr_mtConcurrentReadWriteSameRegion(void *arg)
{
    TaskP_Object taskObjA, taskObjB;
    TaskP_Params tParams;
    volatile uint32_t *sharedPtr;
    uint32_t firstWord;
    int32_t  verStatus;

    /* Initialize synchronization */
    TestDdr_MtPassCount = 0;
    TestDdr_MtFailCount = 0;
    SemaphoreP_constructCounting(&TestDdr_MtDoneSem, 0, 2);
    SemaphoreP_constructMutex(&TestDdr_MtMutex);

    /* Task A: writes pattern 0 to shared region */
    TestDdr_MtTaskArgs[0].taskId     = 0U;
    TestDdr_MtTaskArgs[0].regionAddr = (volatile uint32_t *)TEST_DDR_MT_SHARED_REGION_ADDR;
    TestDdr_MtTaskArgs[0].regionSize = TEST_DDR_MT_SHARED_REGION_SIZE;
    TestDdr_MtTaskArgs[0].pattern    = TEST_DDR_MT_PATTERN_TASK0;
    TestDdr_MtTaskArgs[0].iterations = TEST_DDR_MT_WRITE_ITERATIONS;
    TestDdr_MtTaskArgs[0].pPassCount = &TestDdr_MtPassCount;
    TestDdr_MtTaskArgs[0].pFailCount = &TestDdr_MtFailCount;
    TestDdr_MtTaskArgs[0].pDoneSem   = &TestDdr_MtDoneSem;
    TestDdr_MtTaskArgs[0].pMutex     = &TestDdr_MtMutex;

    TaskP_Params_init(&tParams);
    tParams.name      = (char *)"DdrMtRwTaskA";
    tParams.stackSize = TEST_DDR_MT_TASK_STACK_SIZE;
    tParams.stack     = TestDdr_MtTaskStack[0];
    tParams.priority  = TEST_DDR_MT_TASK_PRIORITY;
    tParams.args      = &TestDdr_MtTaskArgs[0];
    tParams.taskMain  = TestDdr_mtReadWriteMutexTaskA;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskObjA, &tParams));

    /* Task B: writes pattern 1 to shared region */
    TestDdr_MtTaskArgs[1].taskId     = 1U;
    TestDdr_MtTaskArgs[1].regionAddr = (volatile uint32_t *)TEST_DDR_MT_SHARED_REGION_ADDR;
    TestDdr_MtTaskArgs[1].regionSize = TEST_DDR_MT_SHARED_REGION_SIZE;
    TestDdr_MtTaskArgs[1].pattern    = TEST_DDR_MT_PATTERN_TASK1;
    TestDdr_MtTaskArgs[1].iterations = TEST_DDR_MT_WRITE_ITERATIONS;
    TestDdr_MtTaskArgs[1].pPassCount = &TestDdr_MtPassCount;
    TestDdr_MtTaskArgs[1].pFailCount = &TestDdr_MtFailCount;
    TestDdr_MtTaskArgs[1].pDoneSem   = &TestDdr_MtDoneSem;
    TestDdr_MtTaskArgs[1].pMutex     = &TestDdr_MtMutex;

    TaskP_Params_init(&tParams);
    tParams.name      = (char *)"DdrMtRwTaskB";
    tParams.stackSize = TEST_DDR_MT_TASK_STACK_SIZE;
    tParams.stack     = TestDdr_MtTaskStack[1];
    tParams.priority  = TEST_DDR_MT_TASK_PRIORITY;
    tParams.args      = &TestDdr_MtTaskArgs[1];
    tParams.taskMain  = TestDdr_mtReadWriteMutexTaskB;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskObjB, &tParams));

    /* Wait for both tasks with timeout */
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDdr_MtDoneSem, TEST_DDR_MT_TASK_TIMEOUT_MS), "Task A timeout");
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDdr_MtDoneSem, TEST_DDR_MT_TASK_TIMEOUT_MS), "Task B timeout");

    /* Verify both tasks reported success */
    TEST_ASSERT_EQUAL_INT32(2, TestDdr_MtPassCount);
    TEST_ASSERT_EQUAL_INT32(0, TestDdr_MtFailCount);

    CacheP_inv((void *)TEST_DDR_MT_SHARED_REGION_ADDR, 4U, CacheP_TYPE_ALL);
    sharedPtr = (volatile uint32_t *)TEST_DDR_MT_SHARED_REGION_ADDR;
    firstWord = sharedPtr[0];

    TEST_ASSERT_TRUE((firstWord == TEST_DDR_MT_PATTERN_TASK0) ||
                        (firstWord == TEST_DDR_MT_PATTERN_TASK1));

    verStatus = TestDdr_mtVerifyRegion(sharedPtr, TEST_DDR_MT_SHARED_REGION_SIZE,
                                        firstWord);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, verStatus);

    /* Cleanup */
    TaskP_destruct(&taskObjA);
    TaskP_destruct(&taskObjB);
    SemaphoreP_destruct(&TestDdr_MtDoneSem);
    SemaphoreP_destruct(&TestDdr_MtMutex);
}

/**
 * \brief Concurrent DDR read and write to different non-overlapping regions.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Writer task fills region 0 with its pattern and verifies it;
 *                 reader task verifies region 1 (pre-filled) across 10 iterations;
 *                 both tasks pass (PassCount == 2, FailCount == 0) with no
 *                 cross-region interference.
 */
void TestDdr_mtConcurrentReadWriteDifferentRegions(void *arg)
{
    TaskP_Object taskObjA, taskObjB;
    TaskP_Params tParams;

    /* Pre-fill region-B (task 1 region) with pattern */
    TestDdr_mtFillRegion(TestDdr_MtRegionAddrs[1], TEST_DDR_MT_REGION_SIZE,
                         TEST_DDR_MT_PATTERN_TASK1);

    /* Initialize synchronization */
    TestDdr_MtPassCount = 0;
    TestDdr_MtFailCount = 0;
    SemaphoreP_constructCounting(&TestDdr_MtDoneSem, 0, 2);
    SemaphoreP_constructMutex(&TestDdr_MtMutex);

    /* Task A: writes to region 0 */
    TestDdr_MtTaskArgs[0].taskId     = 0U;
    TestDdr_MtTaskArgs[0].regionAddr = TestDdr_MtRegionAddrs[0];
    TestDdr_MtTaskArgs[0].regionSize = TEST_DDR_MT_REGION_SIZE;
    TestDdr_MtTaskArgs[0].pattern    = TEST_DDR_MT_PATTERN_TASK0;
    TestDdr_MtTaskArgs[0].iterations = 1U;
    TestDdr_MtTaskArgs[0].pPassCount = &TestDdr_MtPassCount;
    TestDdr_MtTaskArgs[0].pFailCount = &TestDdr_MtFailCount;
    TestDdr_MtTaskArgs[0].pDoneSem   = &TestDdr_MtDoneSem;
    TestDdr_MtTaskArgs[0].pMutex     = &TestDdr_MtMutex;

    TaskP_Params_init(&tParams);
    tParams.name      = (char *)"DdrMtWrDiffTask";
    tParams.stackSize = TEST_DDR_MT_TASK_STACK_SIZE;
    tParams.stack     = TestDdr_MtTaskStack[0];
    tParams.priority  = TEST_DDR_MT_TASK_PRIORITY;
    tParams.args      = &TestDdr_MtTaskArgs[0];
    tParams.taskMain  = TestDdr_mtWriteTaskDiffRegion;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskObjA, &tParams));

    /* Task B: reads from region 1 */
    TestDdr_MtTaskArgs[1].taskId     = 1U;
    TestDdr_MtTaskArgs[1].regionAddr = TestDdr_MtRegionAddrs[1];
    TestDdr_MtTaskArgs[1].regionSize = TEST_DDR_MT_REGION_SIZE;
    TestDdr_MtTaskArgs[1].pattern    = TEST_DDR_MT_PATTERN_TASK1;
    TestDdr_MtTaskArgs[1].iterations = TEST_DDR_MT_READ_ITERATIONS;
    TestDdr_MtTaskArgs[1].pPassCount = &TestDdr_MtPassCount;
    TestDdr_MtTaskArgs[1].pFailCount = &TestDdr_MtFailCount;
    TestDdr_MtTaskArgs[1].pDoneSem   = &TestDdr_MtDoneSem;
    TestDdr_MtTaskArgs[1].pMutex     = &TestDdr_MtMutex;

    TaskP_Params_init(&tParams);
    tParams.name      = (char *)"DdrMtRdDiffTask";
    tParams.stackSize = TEST_DDR_MT_TASK_STACK_SIZE;
    tParams.stack     = TestDdr_MtTaskStack[1];
    tParams.priority  = TEST_DDR_MT_TASK_PRIORITY;
    tParams.args      = &TestDdr_MtTaskArgs[1];
    tParams.taskMain  = TestDdr_mtReadTaskDiffRegion;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskObjB, &tParams));

    /* Wait for both tasks with timeout */
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDdr_MtDoneSem, TEST_DDR_MT_TASK_TIMEOUT_MS), "Writer task timeout");
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDdr_MtDoneSem, TEST_DDR_MT_TASK_TIMEOUT_MS), "Reader task timeout");

    /* Verify both passed */
    TEST_ASSERT_EQUAL_INT32(2, TestDdr_MtPassCount);
    TEST_ASSERT_EQUAL_INT32(0, TestDdr_MtFailCount);

    /* Cleanup */
    TaskP_destruct(&taskObjA);
    TaskP_destruct(&taskObjB);
    SemaphoreP_destruct(&TestDdr_MtDoneSem);
    SemaphoreP_destruct(&TestDdr_MtMutex);
}

/**
 * \brief Concurrent DDR inline ECC enable/disable toggle and ECC-region traffic test.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Both tasks complete without hang or crash (PassCount == 2,
 *                 FailCount == 0); ECC is re-enabled and all pending ECC errors
 *                 are cleared after the test.
 */
void TestDdr_mtConcurrentEccEnableDisable(void *arg)
{
    TaskP_Object taskObjA, taskObjB;
    TaskP_Params tParams;

    /* Initialize synchronization */
    TestDdr_MtPassCount = 0;
    TestDdr_MtFailCount = 0;
    SemaphoreP_constructCounting(&TestDdr_MtDoneSem, 0, 2);
    SemaphoreP_constructMutex(&TestDdr_MtMutex);

    /* Task A: Toggle ECC enable/disable */
    TestDdr_MtTaskArgs[0].taskId     = 0U;
    TestDdr_MtTaskArgs[0].regionAddr = NULL;
    TestDdr_MtTaskArgs[0].regionSize = 0U;
    TestDdr_MtTaskArgs[0].pattern    = 0U;
    TestDdr_MtTaskArgs[0].iterations = TEST_DDR_MT_ECC_TOGGLE_ITERS;
    TestDdr_MtTaskArgs[0].pPassCount = &TestDdr_MtPassCount;
    TestDdr_MtTaskArgs[0].pFailCount = &TestDdr_MtFailCount;
    TestDdr_MtTaskArgs[0].pDoneSem   = &TestDdr_MtDoneSem;
    TestDdr_MtTaskArgs[0].pMutex     = &TestDdr_MtMutex;

    TaskP_Params_init(&tParams);
    tParams.name      = (char *)"DdrMtEccToggle";
    tParams.stackSize = TEST_DDR_MT_TASK_STACK_SIZE;
    tParams.stack     = TestDdr_MtTaskStack[0];
    tParams.priority  = TEST_DDR_MT_TASK_PRIORITY;
    tParams.args      = &TestDdr_MtTaskArgs[0];
    tParams.taskMain  = TestDdr_mtEccToggleTask;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskObjA, &tParams));

    /* Task B: DDR traffic in ECC region */
    TestDdr_MtTaskArgs[1].taskId     = 1U;
    TestDdr_MtTaskArgs[1].regionAddr = (volatile uint32_t *)TEST_DDR_MT_ECC_TEST_ADDR;
    TestDdr_MtTaskArgs[1].regionSize = 4U;
    TestDdr_MtTaskArgs[1].pattern    = TEST_DDR_MT_PATTERN_TASK1;
    TestDdr_MtTaskArgs[1].iterations = TEST_DDR_MT_ECC_TOGGLE_ITERS;
    TestDdr_MtTaskArgs[1].pPassCount = &TestDdr_MtPassCount;
    TestDdr_MtTaskArgs[1].pFailCount = &TestDdr_MtFailCount;
    TestDdr_MtTaskArgs[1].pDoneSem   = &TestDdr_MtDoneSem;
    TestDdr_MtTaskArgs[1].pMutex     = &TestDdr_MtMutex;

    TaskP_Params_init(&tParams);
    tParams.name      = (char *)"DdrMtEccTraffic";
    tParams.stackSize = TEST_DDR_MT_TASK_STACK_SIZE;
    tParams.stack     = TestDdr_MtTaskStack[1];
    tParams.priority  = TEST_DDR_MT_TASK_PRIORITY;
    tParams.args      = &TestDdr_MtTaskArgs[1];
    tParams.taskMain  = TestDdr_mtEccTrafficTask;
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, TaskP_construct(&taskObjB, &tParams));

    /* Wait for both tasks with timeout */
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDdr_MtDoneSem, TEST_DDR_MT_TASK_TIMEOUT_MS), "ECC toggle task timeout");
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDdr_MtDoneSem, TEST_DDR_MT_TASK_TIMEOUT_MS), "ECC traffic task timeout");

    /* Ensure ECC is re-enabled after test */
    DDR_enableInlineECC(1U);
    DDR_clearECCError(DDR_ECC_ERR_ALL);

    /* Verify both passed */
    TEST_ASSERT_EQUAL_INT32(2, TestDdr_MtPassCount);
    TEST_ASSERT_EQUAL_INT32(0, TestDdr_MtFailCount);

    /* Cleanup */
    TaskP_destruct(&taskObjA);
    TaskP_destruct(&taskObjB);
    SemaphoreP_destruct(&TestDdr_MtDoneSem);
    SemaphoreP_destruct(&TestDdr_MtMutex);
}



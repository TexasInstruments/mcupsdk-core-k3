/*
 *  Copyright (C) 2021-2026 Texas Instruments Incorporated
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
 *  \file test_hyperbus_multi_thread.c
 *
 *  \brief File containing HyperBus driver test cases for multi-threaded
 *         use cases.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/hyperbus.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of threads used in the concurrent-open test */
#define TEST_HYPERBUS_MT_OPEN_THREADS       (2U)

/* Number of threads used in ECC enable/disable test */
#define TEST_HYPERBUS_MT_ECC_THREADS        (2U)

/* Number of threads used in memory-access test */
#define TEST_HYPERBUS_MT_MEM_THREADS        (2U)

/* Number of threads used in ECC configure + access test */
#define TEST_HYPERBUS_MT_ECCACC_THREADS     (2U)

/* FreeRTOS task priority for all test threads */
#define TEST_HYPERBUS_MT_TASK_PRIORITY      (8U)

/* Stack size for each test thread (bytes) */
#define TEST_HYPERBUS_MT_STACK_SIZE         (8U * 1024U)

/* Iterations per thread for ECC toggle and memory access loops */
#define TEST_HYPERBUS_MT_ITER_COUNT         (10U)

/* Non-ECC region: two non-overlapping 4 KB windows for the two memory threads */
#define TEST_HYPERBUS_MT_MEM_OFFSET_T0      (0x1000U)   /* thread 0: 4 KB */
#define TEST_HYPERBUS_MT_MEM_OFFSET_T1      (0x2000U)   /* thread 1: 8 KB */
#define TEST_HYPERBUS_MT_MEM_SIZE           (256U)       /* bytes per transfer */

/* ECC region offset (must be inside the primed region at 100 KB – 200 KB) */
#define TEST_HYPERBUS_MT_ECC_REGION_START   (0x19000U)   /* 100 KB */
#define TEST_HYPERBUS_MT_ECC_REGION_SIZE    (0x6000U)    /* 24 KB  */

/* ========================================================================== */
/*                               Typedefs                                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Counting semaphore used to wait for all threads to finish */
static SemaphoreP_Object gTestHyperbusMt_DoneSem;

/* Per-thread pass/fail flags written by task functions */
static volatile uint32_t gTestHyperbusMt_TaskResult[TEST_HYPERBUS_MT_MEM_THREADS];

static TaskP_Object gTestHyperbusMt_EccTaskObj[TEST_HYPERBUS_MT_ECC_THREADS];
static uint8_t      gTestHyperbusMt_EccStack[TEST_HYPERBUS_MT_ECC_THREADS][TEST_HYPERBUS_MT_STACK_SIZE]
    __attribute__((aligned(32U)));

static TaskP_Object gTestHyperbusMt_MemTaskObj[TEST_HYPERBUS_MT_MEM_THREADS];
static uint8_t      gTestHyperbusMt_MemStack[TEST_HYPERBUS_MT_MEM_THREADS][TEST_HYPERBUS_MT_STACK_SIZE]
    __attribute__((aligned(32U)));

static TaskP_Object gTestHyperbusMt_EccAccTaskObj[TEST_HYPERBUS_MT_ECCACC_THREADS];
static uint8_t      gTestHyperbusMt_EccAccStack[TEST_HYPERBUS_MT_ECCACC_THREADS][TEST_HYPERBUS_MT_STACK_SIZE]
    __attribute__((aligned(32U)));

/* Scratch buffers for the memory-access test (placed in MSRAM scratch section) */
static uint8_t gTestHyperbusMt_WriteBuf0[TEST_HYPERBUS_MT_MEM_SIZE]
    __attribute__((section(".globalScratchBuffer"), aligned(128U)));
static uint8_t gTestHyperbusMt_ReadBuf0[TEST_HYPERBUS_MT_MEM_SIZE]
    __attribute__((section(".globalScratchBuffer"), aligned(128U)));
static uint8_t gTestHyperbusMt_WriteBuf1[TEST_HYPERBUS_MT_MEM_SIZE]
    __attribute__((section(".globalScratchBuffer"), aligned(128U)));
static uint8_t gTestHyperbusMt_ReadBuf1[TEST_HYPERBUS_MT_MEM_SIZE]
    __attribute__((section(".globalScratchBuffer"), aligned(128U)));

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */

static void TestHyperBus_MultiThreadECCEnableDisable(void *args);
static void TestHyperBus_MultiThreadMemoryAccess(void *args);
static void TestHyperBus_MultiThreadECCConfigureAndAccess(void *args);

/* Task functions spawned by each test */
static void TestHyperbusMt_EccEnableTask(void *args);
static void TestHyperbusMt_EccDisableTask(void *args);
static void TestHyperbusMt_MemWriteTask(void *args);
static void TestHyperbusMt_MemReadTask(void *args);
static void TestHyperbusMt_EccConfigTask(void *args);
static void TestHyperbusMt_EccAccessTask(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void run_multi_threaded_tests(void *args)
{
    RUN_TEST(TestHyperBus_MultiThreadECCEnableDisable,        12281, NULL);
    RUN_TEST(TestHyperBus_MultiThreadMemoryAccess,            12282, NULL);
    RUN_TEST(TestHyperBus_MultiThreadECCConfigureAndAccess,   12283, NULL);

    return;
}

/* ========================================================================== */
/*                     Internal Function Definitions                          */
/* ========================================================================== */

/**
 * \brief This test case performs multi-threaded ECC enable operations on HyperBus.
 *        It repeatedly enables the Error Correcting Code (ECC) feature across multiple iterations.
 *        The test ensures that ECC enable operations complete successfully in a concurrent environment.
 *        Small delays between operations allow for system synchronization across threads.
 *        Task result is stored to track success or failure of the enable operations.
 *        The test validates the stability and reliability of ECC enable functionality under load.
 */
static void TestHyperbusMt_EccEnableTask(void *args)
{
    HYPERBUS_Handle handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t        i;
    int32_t         status = SystemP_SUCCESS;

    for (i = 0U; i < TEST_HYPERBUS_MT_ITER_COUNT; i++)
    {
        int32_t s = HYPERBUS_enableECC(handle,
                                       HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_ENABLE);
        if (s != SystemP_SUCCESS)
        {
            status = s;
        }
        ClockP_usleep(10U);
    }

    gTestHyperbusMt_TaskResult[0] = (status == SystemP_SUCCESS) ? 1U : 0U;

    SemaphoreP_post(&gTestHyperbusMt_DoneSem);
    TaskP_exit();
}

/**
 * \brief This test case performs multi-threaded ECC disable operations on HyperBus.
 *        It repeatedly disables the Error Correcting Code (ECC) feature across multiple iterations.
 *        The test ensures that ECC disable operations complete successfully in a concurrent environment.
 *        Small delays between operations allow for system synchronization across threads.
 *        Task result is stored to track success or failure of the disable operations.
 *        The test validates the stability and reliability of ECC disable functionality under load.
 */
static void TestHyperbusMt_EccDisableTask(void *args)
{
    HYPERBUS_Handle handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t        i;
    int32_t         status = SystemP_SUCCESS;

    for (i = 0U; i < TEST_HYPERBUS_MT_ITER_COUNT; i++)
    {
        int32_t s = HYPERBUS_enableECC(handle,
                                       HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_DISABLE);
        if (s != SystemP_SUCCESS)
        {
            status = s;
        }
        ClockP_usleep(10U);
    }

    gTestHyperbusMt_TaskResult[1] = (status == SystemP_SUCCESS) ? 1U : 0U;

    SemaphoreP_post(&gTestHyperbusMt_DoneSem);
    TaskP_exit();
}

/**
 * \brief This test case performs multi-threaded memory write operations on HyperBus.
 *        It fills a write buffer with a modulo-211 index pattern and writes it to HyperBus memory.
 *        Cache operations ensure data coherency across the system.
 *        Data is read back from HyperBus memory and compared against the original write buffer.
 *        The test validates data integrity across multiple iterations in a concurrent environment.
 *        Task result is stored and signaled when complete to synchronize with other threads.
 */
static void TestHyperbusMt_MemWriteTask(void *args)
{
    HYPERBUS_Handle  handle   = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t         baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    volatile uint8_t *memPtr  = (volatile uint8_t *)(uintptr_t)
                                 (baseAddr + TEST_HYPERBUS_MT_MEM_OFFSET_T0);
    uint32_t i;
    int32_t  status = SystemP_SUCCESS;

    /* Fill write buffer: byte i = i % 211 */
    for (i = 0U; i < TEST_HYPERBUS_MT_MEM_SIZE; i++)
    {
        gTestHyperbusMt_WriteBuf0[i] = (uint8_t)(i % 211U);
    }

    for (i = 0U; i < TEST_HYPERBUS_MT_ITER_COUNT; i++)
    {
        memcpy((void *)memPtr, gTestHyperbusMt_WriteBuf0, TEST_HYPERBUS_MT_MEM_SIZE);
        CacheP_wbInv((void *)memPtr, TEST_HYPERBUS_MT_MEM_SIZE, CacheP_TYPE_ALLD);
        memcpy(gTestHyperbusMt_ReadBuf0, (void *)memPtr, TEST_HYPERBUS_MT_MEM_SIZE);

        if (memcmp(gTestHyperbusMt_WriteBuf0, gTestHyperbusMt_ReadBuf0,
                   TEST_HYPERBUS_MT_MEM_SIZE) != 0)
        {
            status = SystemP_FAILURE;
            break;
        }
    }

    gTestHyperbusMt_TaskResult[0] = (status == SystemP_SUCCESS) ? 1U : 0U;

    SemaphoreP_post(&gTestHyperbusMt_DoneSem);
    TaskP_exit();
}

/**
 * \brief This test case performs multi-threaded memory read operations on HyperBus.
 *        It fills a write buffer with an inverted index pattern and writes it to HyperBus memory.
 *        Cache operations ensure data coherency across the system.
 *        Data is read back from HyperBus memory and compared against the original write buffer.
 *        The test validates data integrity across multiple iterations in a concurrent environment.
 *        Task result is stored and signaled when complete to synchronize with other threads.
 */
static void TestHyperbusMt_MemReadTask(void *args)
{
    HYPERBUS_Handle  handle   = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t         baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    volatile uint8_t *memPtr  = (volatile uint8_t *)(uintptr_t)
                                 (baseAddr + TEST_HYPERBUS_MT_MEM_OFFSET_T1);
    uint32_t i;
    int32_t  status = SystemP_SUCCESS;

    /* Fill write buffer: inverted index pattern */
    for (i = 0U; i < TEST_HYPERBUS_MT_MEM_SIZE; i++)
    {
        gTestHyperbusMt_WriteBuf1[i] = (uint8_t)(~i & 0xFFU);
    }

    for (i = 0U; i < TEST_HYPERBUS_MT_ITER_COUNT; i++)
    {
        memcpy((void *)memPtr, gTestHyperbusMt_WriteBuf1, TEST_HYPERBUS_MT_MEM_SIZE);
        CacheP_wbInv((void *)memPtr, TEST_HYPERBUS_MT_MEM_SIZE, CacheP_TYPE_ALLD);
        memcpy(gTestHyperbusMt_ReadBuf1, (void *)memPtr, TEST_HYPERBUS_MT_MEM_SIZE);

        if (memcmp(gTestHyperbusMt_WriteBuf1, gTestHyperbusMt_ReadBuf1,
                   TEST_HYPERBUS_MT_MEM_SIZE) != 0)
        {
            status = SystemP_FAILURE;
            break;
        }
    }

    gTestHyperbusMt_TaskResult[1] = (status == SystemP_SUCCESS) ? 1U : 0U;

    SemaphoreP_post(&gTestHyperbusMt_DoneSem);
    TaskP_exit();
}

/**
 * \brief This test case configures ECC memory regions in a multi-threaded environment.
 *        It sets up region 0 with a primed 24 KB window while disabling regions 1-3.
 *        The ECC configuration is applied repeatedly across multiple iterations to test consistency.
 *        Thread-safety of concurrent ECC configuration is validated through repeated cycles.
 *        The test ensures no configuration errors occur during parallel ECC setup operations.
 *        Multiple iterations verify that the configuration remains stable and consistent.
 */
static void TestHyperbusMt_EccConfigTask(void *args)
{
    HYPERBUS_Handle  handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    HYPERBUS_Config *cfg    = (HYPERBUS_Config *)handle;
    int32_t          status = SystemP_SUCCESS;
    uint32_t         i;

    for (i = 0U; i < TEST_HYPERBUS_MT_ITER_COUNT; i++)
    {
        /* Set region 0 to the primed 24 KB window */
        cfg->attrs->eccRegion->eccRegionStart0 = TEST_HYPERBUS_MT_ECC_REGION_START;
        cfg->attrs->eccRegion->eccRegionSize0  = TEST_HYPERBUS_MT_ECC_REGION_SIZE;
        /* Regions 1-3 disabled */
        cfg->attrs->eccRegion->eccRegionSize1  = 0U;
        cfg->attrs->eccRegion->eccRegionSize2  = 0U;
        cfg->attrs->eccRegion->eccRegionSize3  = 0U;

        int32_t s = HYPERBUS_configureECC(handle);
        if (s != SystemP_SUCCESS)
        {
            status = s;
            break;
        }
        ClockP_usleep(20U);
    }

    gTestHyperbusMt_TaskResult[0] = (status == SystemP_SUCCESS) ? 1U : 0U;

    SemaphoreP_post(&gTestHyperbusMt_DoneSem);
    TaskP_exit();
}

/**
 * \brief This test case validates ECC memory access operations in a multi-threaded environment.
 *        It performs read/write operations on a designated ECC region with cache management.
 *        The test verifies data integrity by writing known patterns and comparing read-back data.
 *        Multiple iterations ensure consistency of ECC-protected memory access.
 *        Thread-safety of concurrent memory access is validated through repeated cycles.
 *        The test ensures no data corruption occurs during parallel ECC operations.
 */
static void TestHyperbusMt_EccAccessTask(void *args)
{
    HYPERBUS_Handle  handle   = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t         baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    /* Use 256-byte window inside the ECC region, not at offset 0 to avoid
     * ECC overhead address collision with the start of the region */
    volatile uint8_t *memPtr  = (volatile uint8_t *)(uintptr_t)
                                 (baseAddr + TEST_HYPERBUS_MT_ECC_REGION_START + 0x200U);
    uint8_t  wbuf[TEST_HYPERBUS_MT_MEM_SIZE];
    uint8_t  rbuf[TEST_HYPERBUS_MT_MEM_SIZE];
    uint32_t i, j;
    int32_t  status = SystemP_SUCCESS;

    for (j = 0U; j < TEST_HYPERBUS_MT_MEM_SIZE; j++)
    {
        wbuf[j] = (uint8_t)(j * 3U + 5U);
    }

    for (i = 0U; i < TEST_HYPERBUS_MT_ITER_COUNT; i++)
    {
        memcpy((void *)memPtr, wbuf, TEST_HYPERBUS_MT_MEM_SIZE);
        CacheP_wbInv((void *)memPtr, TEST_HYPERBUS_MT_MEM_SIZE, CacheP_TYPE_ALLD);
        memcpy(rbuf, (void *)memPtr, TEST_HYPERBUS_MT_MEM_SIZE);

        if (memcmp(wbuf, rbuf, TEST_HYPERBUS_MT_MEM_SIZE) != 0)
        {
            status = SystemP_FAILURE;
            break;
        }
        ClockP_usleep(10U);
    }

    gTestHyperbusMt_TaskResult[1] = (status == SystemP_SUCCESS) ? 1U : 0U;

    SemaphoreP_post(&gTestHyperbusMt_DoneSem);
    TaskP_exit();
}

/**
 * \brief This test case validates ECC enable/disable operations in a multi-threaded environment.
 *        It spawns two concurrent tasks where one continuously enables ECC while the other
 *        continuously disables it on the HyperBus controller. The test verifies thread-safety
 *        of ECC control operations and ensures that concurrent enable/disable sequences do not
 *        cause system instability or data corruption. Upon completion, ECC is left in an
 *        enabled state for subsequent tests.
 */
static void TestHyperBus_MultiThreadECCEnableDisable(void *args)
{
    uint32_t     i;
    int32_t      status;
    TaskP_Params taskParams;

    for (i = 0U; i < TEST_HYPERBUS_MT_ECC_THREADS; i++)
    {
        gTestHyperbusMt_TaskResult[i] = 0U;
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&gTestHyperbusMt_DoneSem, 0,
                                     TEST_HYPERBUS_MT_ECC_THREADS));

    /* Thread 0: enable loop */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "HB_MT_ECCE";
    taskParams.stackSize = TEST_HYPERBUS_MT_STACK_SIZE;
    taskParams.stack     = gTestHyperbusMt_EccStack[0];
    taskParams.priority  = TEST_HYPERBUS_MT_TASK_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestHyperbusMt_EccEnableTask;
    status = TaskP_construct(&gTestHyperbusMt_EccTaskObj[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Thread 1: disable loop */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "HB_MT_ECCD";
    taskParams.stackSize = TEST_HYPERBUS_MT_STACK_SIZE;
    taskParams.stack     = gTestHyperbusMt_EccStack[1];
    taskParams.priority  = TEST_HYPERBUS_MT_TASK_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestHyperbusMt_EccDisableTask;
    status = TaskP_construct(&gTestHyperbusMt_EccTaskObj[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (i = 0U; i < TEST_HYPERBUS_MT_ECC_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&gTestHyperbusMt_DoneSem, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&gTestHyperbusMt_DoneSem);

    for (i = 0U; i < TEST_HYPERBUS_MT_ECC_THREADS; i++)
    {
        TaskP_destruct(&gTestHyperbusMt_EccTaskObj[i]);
        TEST_ASSERT_EQUAL_UINT32(1U, gTestHyperbusMt_TaskResult[i]);
    }

    /* Leave ECC in a known enabled state for subsequent tests */
    HYPERBUS_enableECC(HYPERBUS_getHandle(CONFIG_HYPERBUS0),
                       HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_ENABLE);

    DebugP_log("[HYPERBUS MT] MultiThreadECCEnableDisable: PASS\r\n");
}

/**
 * \brief This test case validates multi-threaded memory access operations on HyperBus.
 *        It spawns two concurrent tasks that perform simultaneous write and read operations
 *        on different memory regions. The test verifies that concurrent access patterns do
 *        not cause data corruption or synchronization issues. It ensures thread-safety of
 *        memory operations and validates that the HyperBus controller handles multiple
 *        simultaneous accesses without conflicts or data integrity violations.
 */
static void TestHyperBus_MultiThreadMemoryAccess(void *args)
{
    uint32_t     i;
    int32_t      status;
    TaskP_Params taskParams;

    for (i = 0U; i < TEST_HYPERBUS_MT_MEM_THREADS; i++)
    {
        gTestHyperbusMt_TaskResult[i] = 0U;
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&gTestHyperbusMt_DoneSem, 0,
                                     TEST_HYPERBUS_MT_MEM_THREADS));

    /* Thread 0: writes/reads window at offset T0 */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "HB_MT_WR0";
    taskParams.stackSize = TEST_HYPERBUS_MT_STACK_SIZE;
    taskParams.stack     = gTestHyperbusMt_MemStack[0];
    taskParams.priority  = TEST_HYPERBUS_MT_TASK_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestHyperbusMt_MemWriteTask;
    status = TaskP_construct(&gTestHyperbusMt_MemTaskObj[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Thread 1: writes/reads window at offset T1 */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "HB_MT_WR1";
    taskParams.stackSize = TEST_HYPERBUS_MT_STACK_SIZE;
    taskParams.stack     = gTestHyperbusMt_MemStack[1];
    taskParams.priority  = TEST_HYPERBUS_MT_TASK_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestHyperbusMt_MemReadTask;
    status = TaskP_construct(&gTestHyperbusMt_MemTaskObj[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (i = 0U; i < TEST_HYPERBUS_MT_MEM_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&gTestHyperbusMt_DoneSem, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&gTestHyperbusMt_DoneSem);

    for (i = 0U; i < TEST_HYPERBUS_MT_MEM_THREADS; i++)
    {
        TaskP_destruct(&gTestHyperbusMt_MemTaskObj[i]);
        TEST_ASSERT_EQUAL_UINT32(1U, gTestHyperbusMt_TaskResult[i]);
    }

    DebugP_log("[HYPERBUS MT] MultiThreadMemoryAccess: PASS\r\n");
}

/**
 * \brief This test case validates multi-threaded ECC configuration and memory access
 *        operations on HyperBus. It spawns two concurrent tasks: one to configure
 *        the ECC region and another to perform memory access within that region.
 *        The test verifies that both tasks execute successfully without conflicts
 *        and that ECC configuration is properly applied during concurrent access patterns.
 *        This ensures thread-safety and proper synchronization in HyperBus ECC handling.
 */
static void TestHyperBus_MultiThreadECCConfigureAndAccess(void *args)
{
    uint32_t     i;
    int32_t      status;
    TaskP_Params taskParams;

    for (i = 0U; i < TEST_HYPERBUS_MT_ECCACC_THREADS; i++)
    {
        gTestHyperbusMt_TaskResult[i] = 0U;
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&gTestHyperbusMt_DoneSem, 0,
                                     TEST_HYPERBUS_MT_ECCACC_THREADS));

    /* Thread 0: ECC region configuration */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "HB_MT_ECFG";
    taskParams.stackSize = TEST_HYPERBUS_MT_STACK_SIZE;
    taskParams.stack     = gTestHyperbusMt_EccAccStack[0];
    taskParams.priority  = TEST_HYPERBUS_MT_TASK_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestHyperbusMt_EccConfigTask;
    status = TaskP_construct(&gTestHyperbusMt_EccAccTaskObj[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Thread 1: memory access inside ECC region */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "HB_MT_EACC";
    taskParams.stackSize = TEST_HYPERBUS_MT_STACK_SIZE;
    taskParams.stack     = gTestHyperbusMt_EccAccStack[1];
    taskParams.priority  = TEST_HYPERBUS_MT_TASK_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestHyperbusMt_EccAccessTask;
    status = TaskP_construct(&gTestHyperbusMt_EccAccTaskObj[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for (i = 0U; i < TEST_HYPERBUS_MT_ECCACC_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&gTestHyperbusMt_DoneSem, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&gTestHyperbusMt_DoneSem);

    for (i = 0U; i < TEST_HYPERBUS_MT_ECCACC_THREADS; i++)
    {
        TaskP_destruct(&gTestHyperbusMt_EccAccTaskObj[i]);
        TEST_ASSERT_EQUAL_UINT32(1U, gTestHyperbusMt_TaskResult[i]);
    }

    DebugP_log("[HYPERBUS MT] MultiThreadECCConfigureAndAccess: PASS\r\n");
}




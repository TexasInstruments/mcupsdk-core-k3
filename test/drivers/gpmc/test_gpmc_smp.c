/*
 * Copyright (C) 2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
* @file  test_gpmc_smp.c
**/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <board/flash.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/gpmc.h>

/* ========================================================================== */
/*                             Macros Defines                                 */
/* ========================================================================== */

#define TEST_GPMC_TASK_STACK_SIZE          (8192U)
#define TEST_GPMC_FLASH_OFFSET_BASE        (0x200000U)
#define TEST_GPMC_1KB_SIZE                 (256*4U)
#define TEST_GPMC_BLOCK_SIZE               (TEST_GPMC_1KB_SIZE*256U)


/* ========================================================================== */
/*                         Function Declarations                             */
/* ========================================================================== */

static void TestGpmc_smpOpenTaskFunc(void *args);
static void TestGpmc_smpOpenContention(void *args);
static void TestGpmc_smpConcurrentReadTask(void *args);
static void TestGpmc_smpConcurrentReads(void *args);
static void TestGpmc_smpInterleavedWriteTask(void *args);
static void TestGpmc_smpInterleavedWriteRead(void *args);


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

typedef struct {
    uint32_t offset;
    uint8_t *buffer;
    uint32_t size;
    uint32_t iterations;
    GPMC_Handle handle;
    const char *taskName;
} GPMC_SmpMtTaskArgs;

static TaskP_Object TestGpmc_smpMtTask1;
static TaskP_Object TestGpmc_smpMtTask2;
static uint8_t TestGpmc_smpMtTaskStack1[TEST_GPMC_TASK_STACK_SIZE] __attribute__((aligned(128)));
static uint8_t TestGpmc_smpMtTaskStack2[TEST_GPMC_TASK_STACK_SIZE] __attribute__((aligned(128)));

static SemaphoreP_Object TestGpmc_smpMtStartSem;
static SemaphoreP_Object TestGpmc_smpMtDoneSem;
static SemaphoreP_Object TestGpmc_smpMtExitSem;
static SemaphoreP_Object TestGpmc_smpMtTeardownSem;

static GPMC_SmpMtTaskArgs TestGpmc_smpMtArgs1;
static GPMC_SmpMtTaskArgs TestGpmc_smpMtArgs2;
static uint8_t TestGpmc_smpMtBuf1[TEST_GPMC_1KB_SIZE] __attribute__((aligned(128)));
static uint8_t TestGpmc_smpMtBuf2[TEST_GPMC_1KB_SIZE] __attribute__((aligned(128)));

/* ========================================================================== */
/*                            Function Definitions                            */
/* ========================================================================== */

/**
 * \brief Task helper function for SMP GPMC_open contention testing.
 *
 * This is a worker task that participates in the SMP GPMC_open contention test. It waits
 * at a synchronization barrier, then calls GPMC_open concurrently with another task
 * on a different core to verify that only one task can successfully acquire the hardware.
 *
 * Test Category: Multithreading
 *
 * \param args Pointer to GPMC_SmpMtTaskArgs containing task-specific context.
 *
 * \return None (task loops forever for safe OS teardown).
 */
static void TestGpmc_smpOpenTaskFunc(void *args) 
{
    GPMC_SmpMtTaskArgs *pArgs = (GPMC_SmpMtTaskArgs *)args;
    
    ClockP_usleep(1000);
    
    /* Wait at the starting line */
    SemaphoreP_pend(&TestGpmc_smpMtStartSem, SystemP_WAIT_FOREVER);
    
    ClockP_usleep(1000);
    
    /* FIRE! Both tasks try to grab the GPMC hardware at the same time */
    pArgs->handle = GPMC_open(CONFIG_GPMC0, NULL);
    
    ClockP_usleep(1000);
    
    /* Cross the finish line */
    SemaphoreP_post(&TestGpmc_smpMtDoneSem);
    
    /* Park safely for teardown */
    SemaphoreP_pend(&TestGpmc_smpMtExitSem, SystemP_WAIT_FOREVER);
    SemaphoreP_post(&TestGpmc_smpMtTeardownSem);

    while(1)
    {
        TaskP_yield();
    }
}

/**
 * \brief Multithreaded SMP test for GPMC_open contention.
 *
 * This test constructs two tasks on different cores that attempt to open the GPMC 
 * driver simultaneously. It verifies that the driver's internal locking mechanisms 
 * correctly prevent concurrent access to the same GPMC instance, ensuring only 
 * one task succeeds while the other fails.
 *
 * Test Category: Multithreading
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_smpOpenContention(void *args) 
{
    TaskP_Params taskParams;
    
    /* Start with a clean slate for the GPMC driver */
    Drivers_gpmcClose(); 
    
    TestGpmc_smpMtArgs1.handle = NULL; 
    TestGpmc_smpMtArgs1.taskName = "smp_mt_task1";
    TestGpmc_smpMtArgs2.handle = NULL;
    TestGpmc_smpMtArgs2.taskName = "smp_mt_task2";

    SemaphoreP_constructCounting(&TestGpmc_smpMtStartSem, 0, 2); 
    SemaphoreP_constructCounting(&TestGpmc_smpMtDoneSem, 0, 2); 
    SemaphoreP_constructCounting(&TestGpmc_smpMtExitSem, 0, 2);
    SemaphoreP_constructCounting(&TestGpmc_smpMtTeardownSem, 0, 2);

    /* Construct Task 1 on Core 0 */
    TaskP_Params_init(&taskParams); 
    taskParams.priority = 4; 
    taskParams.taskMain = TestGpmc_smpOpenTaskFunc;
    
    taskParams.name = "smp_mt_task1"; 
    taskParams.stackSize = sizeof(TestGpmc_smpMtTaskStack1); 
    taskParams.stack = TestGpmc_smpMtTaskStack1; 
    taskParams.args = &TestGpmc_smpMtArgs1;
    taskParams.coreAffinity = (1U << 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestGpmc_smpMtTask1, &taskParams));

    /* Construct Task 2 on Core 1 */
    taskParams.name = "smp_mt_task2"; 
    taskParams.stackSize = sizeof(TestGpmc_smpMtTaskStack2); 
    taskParams.stack = TestGpmc_smpMtTaskStack2; 
    taskParams.args = &TestGpmc_smpMtArgs2;
    taskParams.coreAffinity = (1U << 1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TaskP_construct(&TestGpmc_smpMtTask2, &taskParams));

    /* Start both tasks simultaneously */
    SemaphoreP_post(&TestGpmc_smpMtStartSem); 
    SemaphoreP_post(&TestGpmc_smpMtStartSem);
    
    /* Wait for both tasks to finish opening */
    int32_t pend1 = SemaphoreP_pend(&TestGpmc_smpMtDoneSem, 10000); 
    int32_t pend2 = SemaphoreP_pend(&TestGpmc_smpMtDoneSem, 10000); 
    
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, pend1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, pend2);

    /* Verify exactly one succeeded */
    if (TestGpmc_smpMtArgs1.handle != NULL) 
    {
        TEST_ASSERT_NULL(TestGpmc_smpMtArgs2.handle); 
        GPMC_close(TestGpmc_smpMtArgs1.handle);
    } 
    else 
    {
        TEST_ASSERT_NOT_NULL(TestGpmc_smpMtArgs2.handle); 
        GPMC_close(TestGpmc_smpMtArgs2.handle);
    }

    /* Clean up OS objects safely */
    SemaphoreP_post(&TestGpmc_smpMtExitSem); 
    SemaphoreP_post(&TestGpmc_smpMtExitSem); 
    
    SemaphoreP_pend(&TestGpmc_smpMtTeardownSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&TestGpmc_smpMtTeardownSem, SystemP_WAIT_FOREVER);
    
    TaskP_destruct(&TestGpmc_smpMtTask1); 
    TaskP_destruct(&TestGpmc_smpMtTask2);
    SemaphoreP_destruct(&TestGpmc_smpMtStartSem); 
    SemaphoreP_destruct(&TestGpmc_smpMtDoneSem); 
    SemaphoreP_destruct(&TestGpmc_smpMtExitSem);
    SemaphoreP_destruct(&TestGpmc_smpMtTeardownSem);

    /* Restore for the next tests */
    Drivers_gpmcOpen(); 
}

/**
 * \brief Task helper function for SMP concurrent NAND reads.
 *
 * This is a worker task that performs continuous NAND read operations. It is used
 * to test the GPMC driver's stability and thread-safety when multiple tasks across
 * different cores attempt to read from the NAND flash concurrently.
 *
 * Test Category: Multithreading
 *
 * \param args Pointer to GPMC_SmpMtTaskArgs containing task-specific context.
 *
 * \return None (task loops forever for safe OS teardown).
 */
static void TestGpmc_smpConcurrentReadTask(void *args) 
{
    GPMC_SmpMtTaskArgs *taskArgs = (GPMC_SmpMtTaskArgs *)args;
    SemaphoreP_pend(&TestGpmc_smpMtStartSem, SystemP_WAIT_FOREVER);
    
    for (uint32_t i = 0; i < taskArgs->iterations; i++) 
    {
        Flash_read(gFlashHandle[CONFIG_FLASH0], taskArgs->offset, taskArgs->buffer, taskArgs->size);
        TaskP_yield(); 
    }
    
    SemaphoreP_post(&TestGpmc_smpMtDoneSem);
    SemaphoreP_pend(&TestGpmc_smpMtExitSem, SystemP_WAIT_FOREVER);
    SemaphoreP_post(&TestGpmc_smpMtTeardownSem);
    
    while(1) 
    {
        TaskP_yield();
    }
}

/**
 * \brief Multithreaded SMP test for concurrent NAND reads.
 *
 * This test verifies the thread-safety of the GPMC driver's read operations in an SMP 
 * environment. Two tasks on different cores perform continuous reads from different 
 * offsets. The test validates that the data read by each task matches the expected 
 * pattern without any corruption or driver hangs.
 *
 * Test Category: Multithreading
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_smpConcurrentReads(void *args) 
{
    TaskP_Params taskParams;
    int32_t status;
    uint32_t offset1 = TEST_GPMC_FLASH_OFFSET_BASE;
    uint32_t offset2 = TEST_GPMC_FLASH_OFFSET_BASE + TEST_GPMC_BLOCK_SIZE;
    uint32_t blk, page;

    Board_driversClose();
    status = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Pre-write patterns */
    memset(TestGpmc_smpMtBuf1, 0xAA, TEST_GPMC_1KB_SIZE); 
    memset(TestGpmc_smpMtBuf2, 0xBB, TEST_GPMC_1KB_SIZE);
    
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset1, &blk, &page); 
    status = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset2, &blk, &page); 
    status = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    
    status = Flash_write(gFlashHandle[CONFIG_FLASH0], offset1, TestGpmc_smpMtBuf1, TEST_GPMC_1KB_SIZE); 
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = Flash_write(gFlashHandle[CONFIG_FLASH0], offset2, TestGpmc_smpMtBuf2, TEST_GPMC_1KB_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Clear buffers for the actual test read */
    memset(TestGpmc_smpMtBuf1, 0, TEST_GPMC_1KB_SIZE); 
    memset(TestGpmc_smpMtBuf2, 0, TEST_GPMC_1KB_SIZE);
    
    SemaphoreP_constructCounting(&TestGpmc_smpMtStartSem, 0, 2); 
    SemaphoreP_constructCounting(&TestGpmc_smpMtDoneSem, 0, 2); 
    SemaphoreP_constructCounting(&TestGpmc_smpMtExitSem, 0, 2);
    SemaphoreP_constructCounting(&TestGpmc_smpMtTeardownSem, 0, 2);

    TestGpmc_smpMtArgs1.offset = offset1; TestGpmc_smpMtArgs1.buffer = TestGpmc_smpMtBuf1; 
    TestGpmc_smpMtArgs1.size = TEST_GPMC_1KB_SIZE; TestGpmc_smpMtArgs1.iterations = 10;
    
    TestGpmc_smpMtArgs2.offset = offset2; TestGpmc_smpMtArgs2.buffer = TestGpmc_smpMtBuf2; 
    TestGpmc_smpMtArgs2.size = TEST_GPMC_1KB_SIZE; TestGpmc_smpMtArgs2.iterations = 10;

    TaskP_Params_init(&taskParams); 
    taskParams.priority = 4; 
    taskParams.taskMain = TestGpmc_smpConcurrentReadTask;
    
    taskParams.name = "smp_mt_r1"; 
    taskParams.stackSize = sizeof(TestGpmc_smpMtTaskStack1); 
    taskParams.stack = TestGpmc_smpMtTaskStack1; 
    taskParams.args = &TestGpmc_smpMtArgs1;
    taskParams.coreAffinity = (1U << 0);
    TaskP_construct(&TestGpmc_smpMtTask1, &taskParams);
    
    taskParams.name = "smp_mt_r2"; 
    taskParams.stackSize = sizeof(TestGpmc_smpMtTaskStack2); 
    taskParams.stack = TestGpmc_smpMtTaskStack2; 
    taskParams.args = &TestGpmc_smpMtArgs2;
    taskParams.coreAffinity = (1U << 1);
    TaskP_construct(&TestGpmc_smpMtTask2, &taskParams);

    SemaphoreP_post(&TestGpmc_smpMtStartSem); 
    SemaphoreP_post(&TestGpmc_smpMtStartSem);
    
    SemaphoreP_pend(&TestGpmc_smpMtDoneSem, SystemP_WAIT_FOREVER); 
    SemaphoreP_pend(&TestGpmc_smpMtDoneSem, SystemP_WAIT_FOREVER);

    /* Verify correctness */
    for (uint32_t i = 0; i < TEST_GPMC_1KB_SIZE; i++) 
    {
        TEST_ASSERT_EQUAL_UINT8(0xAA, TestGpmc_smpMtBuf1[i]);
        TEST_ASSERT_EQUAL_UINT8(0xBB, TestGpmc_smpMtBuf2[i]);
    }

    SemaphoreP_post(&TestGpmc_smpMtExitSem); 
    SemaphoreP_post(&TestGpmc_smpMtExitSem); 
    
    SemaphoreP_pend(&TestGpmc_smpMtTeardownSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&TestGpmc_smpMtTeardownSem, SystemP_WAIT_FOREVER);
    
    TaskP_destruct(&TestGpmc_smpMtTask1); 
    TaskP_destruct(&TestGpmc_smpMtTask2);
    SemaphoreP_destruct(&TestGpmc_smpMtStartSem); 
    SemaphoreP_destruct(&TestGpmc_smpMtDoneSem); 
    SemaphoreP_destruct(&TestGpmc_smpMtExitSem);
    SemaphoreP_destruct(&TestGpmc_smpMtTeardownSem);
}

/**
 * \brief Task helper function for SMP interleaved NAND writes.
 *
 * This is a worker task that performs continuous NAND write operations. It is used
 * to test the GPMC driver's stability when write operations are interleaved with 
 * read operations from a different core.
 *
 * Test Category: Multithreading
 *
 * \param args Pointer to GPMC_SmpMtTaskArgs containing task-specific context.
 *
 * \return None (task loops forever for safe OS teardown).
 */
static void TestGpmc_smpInterleavedWriteTask(void *args) 
{
    GPMC_SmpMtTaskArgs *taskArgs = (GPMC_SmpMtTaskArgs *)args;
    SemaphoreP_pend(&TestGpmc_smpMtStartSem, SystemP_WAIT_FOREVER);
    
    for (uint32_t i = 0; i < taskArgs->iterations; i++) 
    {
        Flash_write(gFlashHandle[CONFIG_FLASH0], taskArgs->offset, taskArgs->buffer, taskArgs->size);
        TaskP_yield(); 
    }
    
    SemaphoreP_post(&TestGpmc_smpMtDoneSem);
    SemaphoreP_pend(&TestGpmc_smpMtExitSem, SystemP_WAIT_FOREVER);
    SemaphoreP_post(&TestGpmc_smpMtTeardownSem);
    
    while(1) 
    {
        TaskP_yield();
    }
}

/**
 * \brief Multithreaded SMP test for interleaved NAND write and read operations.
 *
 * This test verifies the thread-safety of the GPMC driver when writes and reads
 * are performed concurrently from different cores. One task continuously reads while 
 * another task writes. The test validates that the read operations are not corrupted
 * by the concurrent writes.
 *
 * Test Category: Multithreading
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_smpInterleavedWriteRead(void *args) 
{
    TaskP_Params taskParams;
    int32_t status;
    uint32_t readOffset = TEST_GPMC_FLASH_OFFSET_BASE;
    uint32_t writeOffset = TEST_GPMC_FLASH_OFFSET_BASE + TEST_GPMC_BLOCK_SIZE;
    uint32_t blk, page;

    Board_driversClose();
    status = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    memset(TestGpmc_smpMtBuf1, 0xCC, TEST_GPMC_1KB_SIZE);
    
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], readOffset, &blk, &page); 
    status = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = Flash_write(gFlashHandle[CONFIG_FLASH0], readOffset, TestGpmc_smpMtBuf1, TEST_GPMC_1KB_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], writeOffset, &blk, &page); 
    status = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Clear read buffer, prep write buffer */
    memset(TestGpmc_smpMtBuf1, 0, TEST_GPMC_1KB_SIZE); 
    memset(TestGpmc_smpMtBuf2, 0xDD, TEST_GPMC_1KB_SIZE); 
    
    SemaphoreP_constructCounting(&TestGpmc_smpMtStartSem, 0, 2); 
    SemaphoreP_constructCounting(&TestGpmc_smpMtDoneSem, 0, 2); 
    SemaphoreP_constructCounting(&TestGpmc_smpMtExitSem, 0, 2);
    SemaphoreP_constructCounting(&TestGpmc_smpMtTeardownSem, 0, 2);

    TestGpmc_smpMtArgs1.offset = readOffset; 
    TestGpmc_smpMtArgs1.buffer = TestGpmc_smpMtBuf1; 
    TestGpmc_smpMtArgs1.size = TEST_GPMC_1KB_SIZE; 
    TestGpmc_smpMtArgs1.iterations = 10;
    
    TestGpmc_smpMtArgs2.offset = writeOffset; 
    TestGpmc_smpMtArgs2.buffer = TestGpmc_smpMtBuf2; 
    TestGpmc_smpMtArgs2.size = TEST_GPMC_1KB_SIZE; 
    TestGpmc_smpMtArgs2.iterations = 10;

    TaskP_Params_init(&taskParams); 
    taskParams.priority = 4;
    
    taskParams.name = "smp_mt_read"; 
    taskParams.stackSize = sizeof(TestGpmc_smpMtTaskStack1); 
    taskParams.stack = TestGpmc_smpMtTaskStack1; 
    taskParams.taskMain = TestGpmc_smpConcurrentReadTask; 
    taskParams.args = &TestGpmc_smpMtArgs1;
    taskParams.coreAffinity = (1U << 0);
    TaskP_construct(&TestGpmc_smpMtTask1, &taskParams);
    
    taskParams.name = "smp_mt_write"; 
    taskParams.stackSize = sizeof(TestGpmc_smpMtTaskStack2); 
    taskParams.stack = TestGpmc_smpMtTaskStack2; 
    taskParams.taskMain = TestGpmc_smpInterleavedWriteTask; 
    taskParams.args = &TestGpmc_smpMtArgs2;
    taskParams.coreAffinity = (1U << 1);
    TaskP_construct(&TestGpmc_smpMtTask2, &taskParams);

    SemaphoreP_post(&TestGpmc_smpMtStartSem); 
    SemaphoreP_post(&TestGpmc_smpMtStartSem);
    
    SemaphoreP_pend(&TestGpmc_smpMtDoneSem, SystemP_WAIT_FOREVER); 
    SemaphoreP_pend(&TestGpmc_smpMtDoneSem, SystemP_WAIT_FOREVER);

    /* Verify read task was never corrupted by the interleaved writes */
    for (uint32_t i = 0; i < TEST_GPMC_1KB_SIZE; i++) 
    {
        TEST_ASSERT_EQUAL_UINT8(0xCC, TestGpmc_smpMtBuf1[i]);
    }

    SemaphoreP_post(&TestGpmc_smpMtExitSem); 
    SemaphoreP_post(&TestGpmc_smpMtExitSem); 
    
    SemaphoreP_pend(&TestGpmc_smpMtTeardownSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&TestGpmc_smpMtTeardownSem, SystemP_WAIT_FOREVER);
    
    TaskP_destruct(&TestGpmc_smpMtTask1); 
    TaskP_destruct(&TestGpmc_smpMtTask2);
    SemaphoreP_destruct(&TestGpmc_smpMtStartSem); 
    SemaphoreP_destruct(&TestGpmc_smpMtDoneSem); 
    SemaphoreP_destruct(&TestGpmc_smpMtExitSem);
    SemaphoreP_destruct(&TestGpmc_smpMtTeardownSem);
}

void test_gpmc_smp_main(void *args)
{
    UNITY_BEGIN();
    RUN_TEST(TestGpmc_smpOpenContention, 12442, args);
    RUN_TEST(TestGpmc_smpConcurrentReads, 12443, args);
    RUN_TEST(TestGpmc_smpInterleavedWriteRead, 12444, args);
    UNITY_END();
}

void setUp(void)
{
}

void tearDown(void)
{
}

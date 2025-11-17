/*
 * Copyright (C) 2025-2026 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "test_ospi.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#ifdef SMP_FREERTOS
/* Define buffers for SMP builds (test_ospi.c not linked in SMP) */
uint8_t gOspiTestTxBuf[TEST_OSPI_DATA_SIZE] =
{
    0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
    0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56,
    0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67,
    0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
    0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
uint8_t gOspiTestTxBulkBuf[TEST_OSPI_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
uint8_t gOspiTestRxBuf[TEST_OSPI_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
static uint8_t gOspiTestRxBuf2[TEST_OSPI_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
#else
extern uint8_t gOspiTestTxBuf[TEST_OSPI_DATA_SIZE];
extern uint8_t gOspiTestTxBulkBuf[TEST_OSPI_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
extern uint8_t gOspiTestRxBuf[TEST_OSPI_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
static uint8_t gOspiTestRxBuf2[TEST_OSPI_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));

#endif

static SemaphoreP_Object TestOSPI_writeSem; /* ordering: read waits for write */
static SemaphoreP_Object TestOSPI_readSem;  /* completion: main waits for reader */
static volatile int32_t TestOSPI_writerStatus = SystemP_FAILURE;
static volatile int32_t TestOSPI_readerStatus = SystemP_FAILURE;
static uint8_t TestOSPI_task1Stack[16384] __attribute__ ((aligned(32)));
static uint8_t TestOSPI_task2Stack[16384] __attribute__ ((aligned(32)));
static uint8_t TestOSPI_task3Stack[16384] __attribute__ ((aligned(32)));
static TaskP_Object TestOSPI_thread1TaskObj;
static TaskP_Object TestOSPI_thread2TaskObj;
static TaskP_Object TestOSPI_thread3TaskObj;
static volatile int32_t TestOSPI_thread3Status = SystemP_FAILURE;
static volatile int32_t TestOSPI_thread4Status = SystemP_FAILURE;
static SemaphoreP_Object TestOSPI_sync1Sem;
static SemaphoreP_Object TestOSPI_sync2Sem;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Test cases
 */

#if defined (OSPI_FREERTOS_ONLY_TEST)
/**
 * \brief Functional test for multi-threaded OSPI write operation
 *
 * Test Category: Functionality
 *
 * This test verifies that the OSPI driver can perform a write operation
 * from a separate thread in a multi-threaded environment. It erases a flash block,
 * writes a known data pattern to the flash, and signals completion to other threads.
 * The test is used in conjunction with multi-threaded read tests to validate
 * thread safety and data integrity during concurrent access.
 *
 * \param args
 *
 * \return None.
 */
void TestOspi_multithreadWrite(void *args)
{
    int32_t retVal;
    uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;
    uint32_t blk, page, testCnt;
    DebugP_log("[TEST OSPI] Writer thread: Starting write operation\r\n");

    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    /* Flash erase.*/
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("Flash erase failed in Multi-threaded Write-Read Test\r\n");
        TestOSPI_writerStatus = SystemP_FAILURE;
        SemaphoreP_post(&TestOSPI_writeSem); /* unblock reader so test can terminate */
        TaskP_exit();
    }

    for (testCnt = 0; testCnt < TEST_OSPI_2KB_SIZE/TEST_OSPI_DATA_SIZE; testCnt++)
    {
        memcpy(gOspiTestTxBulkBuf + testCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , sizeof(gOspiTestTxBuf));
    }
    /* Flash write.*/
    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("Flash write failed in Multi-threaded Write-Read Test\r\n");
        TestOSPI_writerStatus = SystemP_FAILURE;
        SemaphoreP_post(&TestOSPI_writeSem);
        TaskP_exit();
    }

    TestOSPI_writerStatus = SystemP_SUCCESS;
    SemaphoreP_post(&TestOSPI_writeSem); /* signal write complete */
    TaskP_exit();
}

/**
 * \brief Functional test for multi-threaded OSPI read operations
 *
 * Test Category: Functionality
 *
 * This test verifies that the OSPI driver supports concurrent read operations
 * from multiple threads without data corruption or race conditions. It launches
 * multiple threads, each performing read operations on the OSPI flash, and checks
 * that the data read by each thread matches the expected pattern.
 *
 * \param args
 *
 * \return None.
 */
void TestOspi_multithreadRead(void *args)
{
    int32_t retVal;
    uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;
    DebugP_log("[TEST OSPI] Reader thread: Waiting for write operation to complete\r\n");

    SemaphoreP_pend(&TestOSPI_writeSem, SystemP_WAIT_FOREVER);
    DebugP_log("[TEST OSPI] Reader thread: Write operation completed, starting read operation\r\n");

     /* Check if write was successful before attempting read */
    if (TestOSPI_writerStatus != SystemP_SUCCESS)
    {
        DebugP_log("[TEST OSPI] Reader thread: Write failed, skipping read operation\r\n");
        TestOSPI_readerStatus = SystemP_FAILURE;
        SemaphoreP_post(&TestOSPI_readSem); /* Signal completion to main thread */
        TaskP_exit();
    }

    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf, TEST_OSPI_2KB_SIZE);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("Flash read failed in Multi-threaded Write-Read Test\r\n");
        TestOSPI_readerStatus = SystemP_FAILURE;
        SemaphoreP_post(&TestOSPI_readSem);
        TaskP_exit();
    }

    retVal = memcmp(gOspiTestRxBuf, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);
    if (retVal != 0)
    {
        DebugP_log("Data mismatch in Multi-threaded Write-Read Test\r\n");
        TestOSPI_readerStatus = SystemP_FAILURE;
        SemaphoreP_post(&TestOSPI_readSem);
        TaskP_exit();
    }
    TestOSPI_readerStatus = SystemP_SUCCESS;
    SemaphoreP_post(&TestOSPI_readSem); /* success completion */
    TaskP_exit();
}

/**
 * \brief Functional test for multi-threaded OSPI write-read operations
 *
 * Test Category: Functionality
 *
 * This test verifies that the OSPI driver can safely perform concurrent write and read
 * operations from multiple threads. It launches a writer thread to erase and write a known
 * data pattern to flash, and a reader thread to read back and verify the data. The test
 * checks for data integrity and thread safety in a multi-threaded environment.
 *
 * \param args
 *
 * \return None.
 */
void TestOspi_multithreadWriteRead(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    TaskP_Params taskParams1, taskParams2;
    int32_t status;

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    DebugP_log("\r\n");
    DebugP_log("[TEST OSPI] Multi-threaded Write-Read Test Start \n\r");
    DebugP_log("\r\n");

    retVal = SemaphoreP_constructCounting(&TestOSPI_writeSem, 0, 1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = SemaphoreP_constructCounting(&TestOSPI_readSem, 0, 1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Initialize statuses pessimistically so success must be explicitly set */
    TestOSPI_writerStatus = SystemP_FAILURE;
    TestOSPI_readerStatus = SystemP_FAILURE;

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 2U;
    taskParams1.stack          = TestOSPI_task1Stack;
    taskParams1.stackSize      = sizeof(TestOSPI_task1Stack);
    taskParams1.name           = "Multithread Write";
    taskParams1.taskMain       = &TestOspi_multithreadWrite;
#ifdef SMP_FREERTOS
    taskParams1.coreAffinity   = (1U << 0);  /* Assign to core 0 for SMP */
#endif

    status = TaskP_construct(&TestOSPI_thread1TaskObj, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 2U;
    taskParams2.stack          = TestOSPI_task2Stack;
    taskParams2.stackSize      = sizeof(TestOSPI_task2Stack);
    taskParams2.name           = "Multithread Read";
    taskParams2.taskMain       = &TestOspi_multithreadRead;
#ifdef SMP_FREERTOS
    taskParams2.coreAffinity   = (1U << 1);  /* Assign to core 1 for SMP */
#endif

    DebugP_log("Multithread read write task created\r\n");

    status = TaskP_construct(&TestOSPI_thread2TaskObj, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    /* Wait for reader completion */
    SemaphoreP_pend(&TestOSPI_readSem, SystemP_WAIT_FOREVER);

    ClockP_usleep(10000);

    SemaphoreP_destruct(&TestOSPI_writeSem);
    SemaphoreP_destruct(&TestOSPI_readSem);
    TaskP_destruct(&TestOSPI_thread1TaskObj); /* Deleting the task */
    TaskP_destruct(&TestOSPI_thread2TaskObj); /* Deleting the task */

    Board_driversClose();

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_writerStatus);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_readerStatus);
}

#ifndef SOC_AM62DX
/*
 * Disabled: OSPI interrupt mode is not enabled
 *
 * \brief Functional test for multi-threaded OSPI write-read operations in interrupt mode
 *
 * Test Category: Functionality
 *
 * This test verifies that the OSPI driver can safely perform concurrent write and read
 * operations from multiple threads when interrupt mode is enabled. It launches a writer
 * thread to erase and write a known data pattern to flash, and a reader thread to read
 * back and verify the data. The test checks for data integrity and thread safety in a
 * multi-threaded environment with interrupts enabled.
 *
 * \param args
 *
 * \return None.
 */
#if 0
void TestOspi_multithreadIntrMode(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    int32_t status;
    OSPI_Attrs attrs;
    TaskP_Params taskParams1, taskParams2;
    OSPI_Handle ospiHandle = OSPI_getHandle(CONFIG_OSPI0);
    OSPI_Config *config = (OSPI_Config*)ospiHandle;
    const OSPI_Attrs *tempAttrs = config->attrs;

    /* Make a copy of the current OSPI attributes to modify */
    memcpy((void*)&attrs, config->attrs, sizeof(OSPI_Attrs));

    /* Close the OSPI driver to reconfigure */
    Drivers_ospiClose();

    /* Enable interrupt mode for this test */
    attrs.intrEnable = true;
    /* Temporarily replace the config attrs with our modified copy */
    config->attrs = &attrs;

    /* Reopen OSPI with interrupt mode enabled */
    Drivers_ospiOpen();

    DebugP_log("\r\n");
    DebugP_log("[TEST OSPI] Multi-threaded Write-Read Test in Interrupt Mode Start \n\r");
    DebugP_log("\r\n");

    retVal = Board_driversOpen();
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("[TEST OSPI] Board_driversOpen failed with status %d\r\n", retVal);
        config->attrs = tempAttrs;
        return;
    }

    retVal = SemaphoreP_constructCounting(&TestOSPI_writeSem, 0, 1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = SemaphoreP_constructCounting(&TestOSPI_readSem, 0, 1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    TestOSPI_writerStatus = SystemP_FAILURE;
    TestOSPI_readerStatus = SystemP_FAILURE;

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 2U;
    taskParams1.stack          = TestOSPI_task1Stack;
    taskParams1.stackSize      = sizeof(TestOSPI_task1Stack);
    taskParams1.name           = "Multithread Write";
    taskParams1.taskMain       = &TestOspi_multithreadWrite;

    status = TaskP_construct(&TestOSPI_thread1TaskObj, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 2U;
    taskParams2.stack          = TestOSPI_task2Stack;
    taskParams2.stackSize      = sizeof(TestOSPI_task2Stack);
    taskParams2.name           = "Multithread Read";
    taskParams2.taskMain       = &TestOspi_multithreadRead;

    status = TaskP_construct(&TestOSPI_thread2TaskObj, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    SemaphoreP_pend(&TestOSPI_readSem, SystemP_WAIT_FOREVER);

    ClockP_usleep(10000);

    SemaphoreP_destruct(&TestOSPI_writeSem);
    SemaphoreP_destruct(&TestOSPI_readSem);
    TaskP_destruct(&TestOSPI_thread1TaskObj); /* Deleting the task */
    TaskP_destruct(&TestOSPI_thread2TaskObj); /* Deleting the task */
    Board_driversClose();

    /* Restore the original attrs pointer before closing OSPI */
    config->attrs = tempAttrs;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_writerStatus);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_readerStatus);
}
#endif /* #if 0 */
#endif /* #ifndef SOC_AM62DX */
#endif /* #if defined (OSPI_FREERTOS_ONLY_TEST) */

/**
 * \brief Thread function for memory-mapped direct access mode reads
 *
 * Test Category: Functionality
 *
 * This thread performs reads using memory-mapped mode to test direct
 * access to flash memory and concurrent operations in DAC mode.
 *
 * \param args Thread arguments
 *
 * \return None.
 */
void TestOspi_dacModeReadThread(void *args)
{
    int32_t retVal;
    uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE + TEST_OSPI_8KB_SIZE;

    /* Wait for write to complete */
    SemaphoreP_pend(&TestOSPI_writeSem, SystemP_WAIT_FOREVER);

    if (TestOSPI_writerStatus != SystemP_SUCCESS)
    {
        DebugP_log("[DAC Thread] Write failed, skipping read\r\n");
        TestOSPI_thread3Status = SystemP_FAILURE;
        SemaphoreP_post(&TestOSPI_sync2Sem);
        TaskP_exit();
    }

    /* Perform DAC mode read into separate buffer to avoid data race with multithreadRead */
    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf2, TEST_OSPI_2KB_SIZE);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("[DAC Thread] Flash_read failed with status %d\r\n", retVal);
        TestOSPI_thread3Status = SystemP_FAILURE; /* Mark as failure to indicate test did not pass */
        SemaphoreP_post(&TestOSPI_sync2Sem);
        TaskP_exit();
    }

    /* Verify data against the correct region of the TX buffer (offset by 8KB) */
    retVal = memcmp(gOspiTestRxBuf2, gOspiTestTxBulkBuf + TEST_OSPI_8KB_SIZE, TEST_OSPI_2KB_SIZE);
    if (retVal != 0)
    {
        DebugP_log("[DAC Thread] Data mismatch in DAC mode read\r\n");
        TestOSPI_thread3Status = SystemP_FAILURE;
    }
    else
    {
        TestOSPI_thread3Status = SystemP_SUCCESS;
    }

    SemaphoreP_post(&TestOSPI_sync2Sem);
    TaskP_exit();
}

/**
 * \brief Functional test for multi-threaded OSPI operations with various I/O modes
 *
 * Test Category: Functionality
 *
 * This test verifies that the OSPI driver can handle concurrent operations
 * with different I/O modes (single, dual, quad, octal) including dual quad-SPI
 * mode for fast boot applications and memory-mapped direct access mode.
 *
 * \param args Test arguments
 *
 * \return None.
 */
void TestOspi_multithreadIOModes(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    int32_t status;
    uint32_t i;
    TaskP_Params taskParams1, taskParams3;
    uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;
    uint32_t blk, page;
    uint32_t writeSize;

    DebugP_log("\r\n[TEST OSPI] Multi-threaded I/O Modes Test Start\r\n");

    retVal = Board_driversOpen();
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("[TEST OSPI] Board_driversOpen failed with status %d\r\n", retVal);
        return;
    }

    /* Create semaphores */
    retVal = SemaphoreP_constructCounting(&TestOSPI_writeSem, 0, 4);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = SemaphoreP_constructCounting(&TestOSPI_readSem, 0, 1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = SemaphoreP_constructCounting(&TestOSPI_sync1Sem, 0, 1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = SemaphoreP_constructCounting(&TestOSPI_sync2Sem, 0, 1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Initialize test data - limit to actual buffer size */
    writeSize = (TEST_OSPI_10MB_SIZE < sizeof(gOspiTestTxBulkBuf)) ? TEST_OSPI_10MB_SIZE : sizeof(gOspiTestTxBulkBuf);
    for (i = 0; i < writeSize / TEST_OSPI_DATA_SIZE; i++)
    {
        memcpy(gOspiTestTxBulkBuf + i * sizeof(gOspiTestTxBuf), gOspiTestTxBuf, sizeof(gOspiTestTxBuf));
    }

    /* Erase and write test data */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("[TEST OSPI] Flash_eraseBlk failed with status %d\r\n", retVal);
        SemaphoreP_destruct(&TestOSPI_writeSem);
        SemaphoreP_destruct(&TestOSPI_readSem);
        SemaphoreP_destruct(&TestOSPI_sync1Sem);
        SemaphoreP_destruct(&TestOSPI_sync2Sem);
        Board_driversClose();
        return;
    }

    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, writeSize);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("[TEST OSPI] Flash_write failed with status %d\r\n", retVal);
        SemaphoreP_destruct(&TestOSPI_writeSem);
        SemaphoreP_destruct(&TestOSPI_readSem);
        SemaphoreP_destruct(&TestOSPI_sync1Sem);
        SemaphoreP_destruct(&TestOSPI_sync2Sem);
        Board_driversClose();
        return;
    }
    TestOSPI_writerStatus = SystemP_SUCCESS;
    TestOSPI_readerStatus = SystemP_FAILURE;
    TestOSPI_thread3Status = SystemP_FAILURE;
    TestOSPI_thread4Status = SystemP_FAILURE;

    /* Create standard read thread - assign to thread2 to match function's destruct call */
    TaskP_Params_init(&taskParams1);
    taskParams1.priority = 2U;
    taskParams1.stack = TestOSPI_task2Stack;
    taskParams1.stackSize = sizeof(TestOSPI_task2Stack);
    taskParams1.name = "Standard Read";
    taskParams1.taskMain = &TestOspi_multithreadRead;
#ifdef SMP_FREERTOS
    taskParams1.coreAffinity = (1U << 0);  /* Assign to core 0 for SMP */
#endif
    status = TaskP_construct(&TestOSPI_thread2TaskObj, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Create DAC mode read thread */
    TaskP_Params_init(&taskParams3);
    taskParams3.priority = 2U;
    taskParams3.stack = TestOSPI_task3Stack;
    taskParams3.stackSize = sizeof(TestOSPI_task3Stack);
    taskParams3.name = "DAC Mode Read";
    taskParams3.taskMain = &TestOspi_dacModeReadThread;
#ifdef SMP_FREERTOS
    taskParams3.coreAffinity = (1U << 1);  /* Assign to core 1 for SMP */
#endif
    status = TaskP_construct(&TestOSPI_thread3TaskObj, &taskParams3);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Signal all threads - need 2 posts for 2 threads */
    SemaphoreP_post(&TestOSPI_writeSem);
    SemaphoreP_post(&TestOSPI_writeSem);

    /* Wait for completion */
    SemaphoreP_pend(&TestOSPI_readSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&TestOSPI_sync2Sem, SystemP_WAIT_FOREVER);

    ClockP_usleep(10000);

    /* Cleanup */
    SemaphoreP_destruct(&TestOSPI_writeSem);
    SemaphoreP_destruct(&TestOSPI_readSem);
    SemaphoreP_destruct(&TestOSPI_sync1Sem);
    SemaphoreP_destruct(&TestOSPI_sync2Sem);
    TaskP_destruct(&TestOSPI_thread2TaskObj);
    TaskP_destruct(&TestOSPI_thread3TaskObj);

    Board_driversClose();

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_readerStatus);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_thread3Status);

    DebugP_log("[TEST OSPI] Multi-threaded I/O Modes Test Passed\r\n");
}

/**
 * \brief Functional test for multi-threaded direct read/write operations
 *
 * Test Category: Functionality
 *
 * This test verifies that the OSPI driver can handle concurrent direct
 * read and write operations where the OSPI controller directly controls
 * the flash without using memory-mapped access.
 *
 * \param args Test arguments
 *
 * \return None.
 */
void TestOspi_multithreadDirectReadWrite(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    int32_t status;
    TaskP_Params taskParams1, taskParams2;

    /* Use a local non-const copy of attrs to change readMode without UB */
    extern OSPI_Config gOspiConfig[];
    const OSPI_Attrs *origAttrs = gOspiConfig[CONFIG_OSPI0].attrs;
    OSPI_Attrs localAttrs = *origAttrs;
    localAttrs.readMode = OSPI_READ_MODE_DAC;
    gOspiConfig[CONFIG_OSPI0].attrs = &localAttrs;

    DebugP_log("\r\n[TEST OSPI] Multi-threaded Direct Read/Write Test Start\r\n");

    retVal = Board_driversOpen();
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("[TEST OSPI] Board_driversOpen failed with status %d\r\n", retVal);
        gOspiConfig[CONFIG_OSPI0].attrs = origAttrs;
        return;
    }

    /* Create semaphores */
    retVal = SemaphoreP_constructCounting(&TestOSPI_writeSem, 0, 1);
    if (retVal != SystemP_SUCCESS) 
        { gOspiConfig[CONFIG_OSPI0].attrs = origAttrs; }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = SemaphoreP_constructCounting(&TestOSPI_readSem, 0, 1);
    if (retVal != SystemP_SUCCESS) 
        { gOspiConfig[CONFIG_OSPI0].attrs = origAttrs; }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    TestOSPI_writerStatus = SystemP_FAILURE;
    TestOSPI_readerStatus = SystemP_FAILURE;

    /* Create write thread */
    TaskP_Params_init(&taskParams1);
    taskParams1.priority = 2U;
    taskParams1.stack = TestOSPI_task1Stack;
    taskParams1.stackSize = sizeof(TestOSPI_task1Stack);
    taskParams1.name = "Direct Write";
    taskParams1.taskMain = &TestOspi_multithreadWrite;
#ifdef SMP_FREERTOS
    taskParams1.coreAffinity = (1U << 0);  /* Assign to core 0 for SMP */
#endif
    status = TaskP_construct(&TestOSPI_thread1TaskObj, &taskParams1);
    if (status != SystemP_SUCCESS) 
        { gOspiConfig[CONFIG_OSPI0].attrs = origAttrs; }
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Create read thread */
    TaskP_Params_init(&taskParams2);
    taskParams2.priority = 2U;
    taskParams2.stack = TestOSPI_task2Stack;
    taskParams2.stackSize = sizeof(TestOSPI_task2Stack);
    taskParams2.name = "Direct Read";
    taskParams2.taskMain = &TestOspi_multithreadRead;
#ifdef SMP_FREERTOS
    taskParams2.coreAffinity = (1U << 1);  /* Assign to core 1 for SMP */
#endif
    status = TaskP_construct(&TestOSPI_thread2TaskObj, &taskParams2);
    if (status != SystemP_SUCCESS) 
        { gOspiConfig[CONFIG_OSPI0].attrs = origAttrs; }
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Wait for completion */
    SemaphoreP_pend(&TestOSPI_readSem, SystemP_WAIT_FOREVER);

    /* Cleanup */
    ClockP_usleep(10000);

    SemaphoreP_destruct(&TestOSPI_writeSem);
    SemaphoreP_destruct(&TestOSPI_readSem);
    TaskP_destruct(&TestOSPI_thread1TaskObj); /* Deleting the task */
    TaskP_destruct(&TestOSPI_thread2TaskObj); /* Deleting the task */
    Board_driversClose();

    /* Restore original const attrs */
    gOspiConfig[CONFIG_OSPI0].attrs = origAttrs;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_writerStatus);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_readerStatus);

    DebugP_log("[TEST OSPI] Multi-threaded Direct Read/Write Test Passed\r\n");
}



/**
 * \brief Functional test for multi-threaded indirect read/write operations
 *
 * Test Category: Functionality
 *
 * This test verifies that the OSPI driver can handle concurrent indirect
 * read and write operations using SRAM buffer for data staging between
 * the processor and flash memory.
 *
 * \param args Test arguments
 *
 * \return None.
 */
void TestOspi_multithreadIndirectReadWrite(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    int32_t status;
    TaskP_Params taskParams1, taskParams2;

    /* Set readMode to INDAC (indirect mode) for this test */
    extern OSPI_Config gOspiConfig[];
    const OSPI_Attrs *origAttrs = gOspiConfig[CONFIG_OSPI0].attrs;
    OSPI_Attrs localAttrs = *origAttrs;
    localAttrs.readMode = OSPI_READ_MODE_INDAC;
    gOspiConfig[CONFIG_OSPI0].attrs = &localAttrs;

    DebugP_log("\r\n[TEST OSPI] Multi-threaded Indirect Read/Write Test Start\r\n");

    retVal = Board_driversOpen();
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("[TEST OSPI] Board_driversOpen failed with status %d\r\n", retVal);
        gOspiConfig[CONFIG_OSPI0].attrs = origAttrs;
        return;
    }

    /* Create semaphores */
    retVal = SemaphoreP_constructCounting(&TestOSPI_writeSem, 0, 1);
    if (retVal != SystemP_SUCCESS) 
        { gOspiConfig[CONFIG_OSPI0].attrs = origAttrs; }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = SemaphoreP_constructCounting(&TestOSPI_readSem, 0, 1);
    if (retVal != SystemP_SUCCESS) 
        { gOspiConfig[CONFIG_OSPI0].attrs = origAttrs; }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    TestOSPI_writerStatus = SystemP_FAILURE;
    TestOSPI_readerStatus = SystemP_FAILURE;

    /* Create write thread */
    TaskP_Params_init(&taskParams1);
    taskParams1.priority = 2U;
    taskParams1.stack = TestOSPI_task1Stack;
    taskParams1.stackSize = sizeof(TestOSPI_task1Stack);
    taskParams1.name = "Indirect Write";
    taskParams1.taskMain = &TestOspi_multithreadWrite;
#ifdef SMP_FREERTOS
    taskParams1.coreAffinity = (1U << 0);  /* Assign to core 0 for SMP */
#endif
    status = TaskP_construct(&TestOSPI_thread1TaskObj, &taskParams1);
    if (status != SystemP_SUCCESS) { gOspiConfig[CONFIG_OSPI0].attrs = origAttrs; }
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Create read thread */
    TaskP_Params_init(&taskParams2);
    taskParams2.priority = 2U;
    taskParams2.stack = TestOSPI_task2Stack;
    taskParams2.stackSize = sizeof(TestOSPI_task2Stack);
    taskParams2.name = "Indirect Read";
    taskParams2.taskMain = &TestOspi_multithreadRead;
#ifdef SMP_FREERTOS
    taskParams2.coreAffinity = (1U << 1);  /* Assign to core 1 for SMP */
#endif
    status = TaskP_construct(&TestOSPI_thread2TaskObj, &taskParams2);
    if (status != SystemP_SUCCESS) { gOspiConfig[CONFIG_OSPI0].attrs = origAttrs; }
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Wait for completion */
    SemaphoreP_pend(&TestOSPI_readSem, SystemP_WAIT_FOREVER);

    /* Cleanup */
    ClockP_usleep(10000);

    SemaphoreP_destruct(&TestOSPI_writeSem);
    SemaphoreP_destruct(&TestOSPI_readSem);
    TaskP_destruct(&TestOSPI_thread1TaskObj); /* Deleting the task */
    TaskP_destruct(&TestOSPI_thread2TaskObj); /* Deleting the task */
    Board_driversClose();

    /* Restore original const attrs */
    gOspiConfig[CONFIG_OSPI0].attrs = origAttrs;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_writerStatus);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, TestOSPI_readerStatus);

    DebugP_log("[TEST OSPI] Multi-threaded Indirect Read/Write Test Passed\r\n");
}

/* ========================================================================== */
/*                          Unified Test Main                                 */
/* ========================================================================== */

#ifdef SMP_FREERTOS
/**
 * \brief SMP test main entry point
 *
 * This function runs all multithread test cases with SMP core affinity enabled
 * for OSPI driver in SMP FreeRTOS environment, testing concurrent access from
 * multiple cores.
 *
 * \param args Test arguments
 *
 * \return None.
 */
void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(TestOspi_multithreadWriteRead, 9607, NULL);

    RUN_TEST(TestOspi_multithreadDirectReadWrite, 9608, NULL);

    RUN_TEST(TestOspi_multithreadIndirectReadWrite, 9609, NULL);

    RUN_TEST(TestOspi_multithreadIOModes, 9610, NULL);

    UNITY_END();
}

/**
* @brief Unity test setup hook.
*
* Called before each Unity test. Left empty because tests perform their own
* per-test setup and teardown.
*/
void setUp(void)
{
}

/**
* @brief Unity test teardown hook.
*
* Called after each Unity test. Left empty because tests perform their own
* per-test cleanup.
*/
void tearDown(void)
{
}

#endif /* SMP_FREERTOS */

void test_ospi_multithread(void)
{
    RUN_TEST(TestOspi_multithreadWriteRead, 8263, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();

    /*Task taking unusually large memeory in intr mode. And its keeps getting failed and affecting future test cases.*/
#ifndef SOC_AM62DX
    /* Disabled: OSPI interrupt mode is not enabled */
    /* RUN_TEST(TestOspi_multithreadIntrMode, 8264, NULL); */
    /* Drivers_ospiClose(); */
    /* Drivers_ospiOpen(); */
#endif

    /* Test various I/O modes (single, dual, quad, octal) */
    RUN_TEST(TestOspi_multithreadIOModes, 9604, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();

    /* Test direct read/write operations */
    RUN_TEST(TestOspi_multithreadDirectReadWrite, 9605, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();

    /* Test indirect read/write operations */
    RUN_TEST(TestOspi_multithreadIndirectReadWrite, 9606, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();

    return;
}

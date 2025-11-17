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
 * @file test_mmcsd_fs_smp_test.c
 * @brief The following test aims at creating tasks for each A53 core.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>
#include "unity.h"

/* ========================================================================== */
/*                             Macros                                         */
/* ========================================================================== */

#define TEST_TIMEOUT_MS    ( 1000 )
#define TEST_MMCSD_FAT_PARTITION_SIZE    (128 * 1024U * 1024U)
#define TEST_MMCSD_SIZE_64K    (64 * 1024)

#if ( configNUMBER_OF_CORES < 2 )
    #error This test is for FreeRTOS SMP and therefore, requires at least 2 cores.
#endif /* if configNUMBER_OF_CORES != 2 */

#if ( configMAX_PRIORITIES <= ( configNUMBER_OF_CORES + 2 ) )
    #error configMAX_PRIORITIES must be larger than ( configNUMBER_OF_CORES + 2 ) to avoid scheduling idle tasks unexpectedly.
#endif /* if ( configMAX_PRIORITIES <= ( configNUMBER_OF_CORES + 2 ) ) */

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

static SemaphoreP_Object TestMMCSD_sem;

static uint8_t TestMMCSD_fatTask1Stack[4 * 1024] __attribute__ ((aligned(32)));
static uint8_t TestMMCSD_fatTask2Stack[4 * 1024] __attribute__ ((aligned(32)));

static TaskP_Object TestMMCSD_fatThread1TaskObj;
static TaskP_Object TestMMCSD_fatThread2TaskObj;

uint8_t TestMMCSD_task1Wbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U)));
uint8_t TestMMCSD_Task1Rbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U)));

uint8_t TestMMCSD_task2Wbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U)));
uint8_t TestMMCSD_task2Rbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U)));

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

static void TestMmcsd_initWrBuffer();
static void fatThread1(void * pvParameters);
static void fatThread2(void * pvParameters);

/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

static void TestMmcsd_initWrBuffer()
{
    for (uint32_t i = 0; i < TEST_MMCSD_SIZE_64K; i++)
    {
        TestMMCSD_task1Wbuf[i] = (i % 256);
        TestMMCSD_task2Wbuf[i] = ((i + 1) % 256);
    }
}

static void fatThread1(void * pvParameters)
{

    FF_FILE *testFp = NULL;
    const char *fileName = (const char *)pvParameters;
    int32_t bytesWritten, bytesRead;
    uint32_t loopVar;

    for(loopVar = 0; loopVar < 10; loopVar++)
    {
        memset(TestMMCSD_Task1Rbuf, 0, TEST_MMCSD_SIZE_64K);
        testFp = ff_fopen(fileName, "w+");
        TEST_ASSERT_NOT_NULL(testFp);

        bytesWritten = ff_fwrite(TestMMCSD_task1Wbuf, 1, TEST_MMCSD_SIZE_64K,  testFp);
        TEST_ASSERT_EQUAL(bytesWritten, TEST_MMCSD_SIZE_64K);

        ff_fclose(testFp);
        testFp = NULL;

        testFp = ff_fopen(fileName, "r");
        TEST_ASSERT_NOT_NULL(testFp);

        bytesRead = ff_fread(TestMMCSD_Task1Rbuf, 1, TEST_MMCSD_SIZE_64K, testFp);
        TEST_ASSERT_EQUAL(bytesRead, TEST_MMCSD_SIZE_64K);

        TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_Task1Rbuf, TestMMCSD_task1Wbuf , TEST_MMCSD_SIZE_64K);

        ff_fclose(testFp);
        ff_remove(fileName);
    }
    SemaphoreP_post(&TestMMCSD_sem);
}

static void fatThread2(void *pvParameters)
{
    FF_FILE *testFp = NULL;
    const char *fileName = (const char *)pvParameters;
    int32_t bytesWritten, bytesRead;
    uint32_t loopVar;

    for(loopVar = 0; loopVar < 10; loopVar++)
    {
        memset(TestMMCSD_task2Rbuf, 0, TEST_MMCSD_SIZE_64K);

        testFp = ff_fopen(fileName, "w+");
        TEST_ASSERT_NOT_NULL(testFp);

        bytesWritten = ff_fwrite(TestMMCSD_task2Wbuf, 1,  TEST_MMCSD_SIZE_64K, testFp);
        TEST_ASSERT_EQUAL(bytesWritten, TEST_MMCSD_SIZE_64K);

        ff_fclose(testFp);
        testFp = NULL;

        testFp = ff_fopen(fileName, "r");
        TEST_ASSERT_NOT_NULL(testFp);

        bytesRead = ff_fread(TestMMCSD_task2Rbuf, 1, TEST_MMCSD_SIZE_64K, testFp);
        TEST_ASSERT_EQUAL(bytesRead, TEST_MMCSD_SIZE_64K);

        TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_task2Rbuf, TestMMCSD_task2Wbuf, TEST_MMCSD_SIZE_64K);

        ff_fclose(testFp);
        ff_remove(fileName);
     }
     SemaphoreP_post(&TestMMCSD_sem);
}

/**
 * \brief Validates simultaneous  file I/O on eMMC and SD using
 * FreeRTOS+FAT and MMCSD driver.
 *
 * Test Category: Functionality
 *
 * This function tests filesystem operations on eMMC and SD card.
 * If no partition exists, it creates, formats, and mounts one
 * before running the file tests.
 *
 * The test iterates over a set of files, writes to the devices and
 * reads to confirm integrity.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */

void TestMmcsd_synchronousFatEmmcSdTransfer(void* args)
{
    int32_t status;
    uint32_t sdBlockSize;
    uint32_t emmcBlockSize;
    int32_t retVal = SystemP_SUCCESS;
    FF_MMCSD_PartitionDetails sd_partitionDetails;
    FF_MMCSD_PartitionDetails emmc_partitionDetails;
    TaskP_Params taskParams1, taskParams2;
    FF_Error_t errVal;
    int32_t loopVar;

    TestMmcsd_initWrBuffer();

    DebugP_log ("Starting MMCSD EMMC SD synchronous transfer test case\r\n");

    /* For SD card */
    FF_Disk_t *pSdDisk = &gFFDisks[FF_PARTITION_SD0];
    FF_MMCSDGetPartitionDetails(pSdDisk, &sd_partitionDetails);

    if (sd_partitionDetails.sectorCount == 0U)
    {
        sdBlockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / sdBlockSize;

        errVal = FF_MMCSDCreateAndFormatPartition(pSdDisk, partSectorCount);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDMountPartition(pSdDisk, "/sd0");
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDGetPartitionDetails(pSdDisk, &sd_partitionDetails);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        if (sd_partitionDetails.sectorCount == 0U)
        {
            retVal = SystemP_FAILURE;
        }
    }
    else
    {
        sdBlockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
    }
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* For EMMC */
    FF_Disk_t *pEmmcDisk = &gFFDisks[FF_PARTITION_EMMC0];
    FF_MMCSDGetPartitionDetails(pEmmcDisk, &emmc_partitionDetails);

    if (emmc_partitionDetails.sectorCount == 0U)
    {
        emmcBlockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / emmcBlockSize;

        errVal = FF_MMCSDCreateAndFormatPartition(pEmmcDisk, partSectorCount);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDMountPartition(pEmmcDisk, "/emmc0");
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDGetPartitionDetails(pEmmcDisk, &emmc_partitionDetails);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        if (emmc_partitionDetails.sectorCount == 0U)
        {
            retVal = SystemP_FAILURE;
        }
    }
    else
    {
        emmcBlockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);;
    }
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    status =  SemaphoreP_constructCounting(&TestMMCSD_sem, 0, 2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestMMCSD_fatTask1Stack;
    taskParams1.stackSize      = sizeof(TestMMCSD_fatTask1Stack);
    taskParams1.args           = (void*)"/sd0/test1.txt";
    taskParams1.name           = "FatSdThread1";
    taskParams1.taskMain       = &fatThread1;
    taskParams1.coreAffinity   = ( 1U << 0);

    status = TaskP_construct(&TestMMCSD_fatThread1TaskObj, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestMMCSD_fatTask2Stack;
    taskParams2.stackSize      = sizeof(TestMMCSD_fatTask2Stack);
    taskParams2.args           = (void*)"/emmc0/test2.txt";
    taskParams2.name           = "FatSdThread2";
    taskParams2.taskMain       = &fatThread2;
    taskParams2.coreAffinity   = ( 1U <<  1);

    status = TaskP_construct(&TestMMCSD_fatThread2TaskObj, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        status = SemaphoreP_pend(&TestMMCSD_sem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(retVal, SystemP_SUCCESS);
    }
    SemaphoreP_destruct(&TestMMCSD_sem);
    TaskP_destruct(&TestMMCSD_fatThread1TaskObj);
    TaskP_destruct(&TestMMCSD_fatThread2TaskObj);
}

/**
 * \brief Validates simultaneous file I/O transfer on SD card.
 *  and EMMC.
 *
 * Test Category: Functionality
 *
 * This function tests filesystem operations on eMMC and SD card.
 * If no partition exists, it creates, formats, and mounts one
 * before running the file tests.
 *
 * The test iterates over a set of files, writes to the SD card and
 * emmc and reads to confirm integrity while the EMMC is unmounted.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_synchronousFatEmmcBootSdUdaTransfer(void* args)
{
    int32_t status;
    uint32_t sdBlockSize;
    uint32_t emmcBlockSize;
    int32_t retVal = SystemP_SUCCESS;
    FF_MMCSD_PartitionDetails sd_partitionDetails;
    FF_MMCSD_PartitionDetails emmc_partitionDetails;
    TaskP_Params taskParams1, taskParams2;
    FF_Error_t errVal;
    int32_t loopVar;

    TestMmcsd_initWrBuffer();

    DebugP_log ("Starting MMCSD EMMC BOOT SD card UDA partitions transfer test case\r\n");

    /* For SD card */
    FF_Disk_t *pSdDisk = &gFFDisks[FF_PARTITION_SD0];
    FF_MMCSDGetPartitionDetails(pSdDisk, &sd_partitionDetails);

    if (sd_partitionDetails.sectorCount == 0U)
    {
        sdBlockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / sdBlockSize;

        errVal = FF_MMCSDCreateAndFormatPartition(pSdDisk, partSectorCount);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDMountPartition(pSdDisk, "/sd0");
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDGetPartitionDetails(pSdDisk, &sd_partitionDetails);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        if (sd_partitionDetails.sectorCount == 0U)
        {
            retVal = SystemP_FAILURE;
        }
    }
    else
    {
        sdBlockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
    }
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* For EMMC */
    FF_Disk_t *pEmmcDisk = &gFFDisks[FF_PARTITION_EMMC0];
    FF_MMCSDGetPartitionDetails(pEmmcDisk, &emmc_partitionDetails);

    if (emmc_partitionDetails.sectorCount == 0U)
    {
        emmcBlockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / emmcBlockSize;

        errVal = FF_MMCSDCreateAndFormatPartition(pEmmcDisk, partSectorCount);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDMountPartition(pEmmcDisk, "/emmc0");
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDGetPartitionDetails(pEmmcDisk, &emmc_partitionDetails);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        if (emmc_partitionDetails.sectorCount == 0U)
        {
            retVal = SystemP_FAILURE;
        }
    }
    else
    {
        emmcBlockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);;
    }
    /* Enable the boot0 partition for EMMC*/
    MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    TEST_ASSERT_NOT_NULL(handle);
    status = MMCSD_enableBootPartition(handle, 1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    status =  SemaphoreP_constructCounting(&TestMMCSD_sem, 0, 2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestMMCSD_fatTask1Stack;
    taskParams1.stackSize      = sizeof(TestMMCSD_fatTask1Stack);
    taskParams1.args           = (void*)"/sd0/test1.txt";
    taskParams1.name           = "FatSdThread1";
    taskParams1.taskMain       = &fatThread1;
    taskParams1.coreAffinity   = ( 1U << 0);

    status = TaskP_construct(&TestMMCSD_fatThread1TaskObj, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestMMCSD_fatTask2Stack;
    taskParams2.stackSize      = sizeof(TestMMCSD_fatTask2Stack);
    taskParams2.args           = (void*)"/emmc0/test2.txt";
    taskParams2.name           = "FatSdThread2";
    taskParams2.taskMain       = &fatThread2;
    taskParams2.coreAffinity   = ( 1U << 1);

    status = TaskP_construct(&TestMMCSD_fatThread2TaskObj, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        status = SemaphoreP_pend(&TestMMCSD_sem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(retVal, SystemP_SUCCESS);
    }
    status = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    SemaphoreP_destruct(&TestMMCSD_sem);
    TaskP_destruct(&TestMMCSD_fatThread1TaskObj);
    TaskP_destruct(&TestMMCSD_fatThread2TaskObj);
}

void setUp(void)
{

}

void tearDown(void)
{

}

/**
 * @brief Entry point for test runner to run schedule affinity test.
 */
void test_main(void* args)
{
    UNITY_BEGIN();

    RUN_TEST(TestMmcsd_synchronousFatEmmcSdTransfer, 8312, args );
    /* This test case hangs on execution
     *RUN_TEST(TestMmcsd_synchronousFatEmmcBootSdUdaTransfer, 8867, args );
     */

    UNITY_END();
}

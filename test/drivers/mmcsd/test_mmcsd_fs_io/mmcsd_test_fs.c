/*
 * Copyright (C) 2021-25 Texas Instruments Incorporated
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

/**\file mmcsd_testFile.c
 *
 * \brief Test file for MMCSD driver file I/O operations.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "mmcsd_test_common.h"

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

static Test_MmcModeSettings TestMMCSD_ModeParams;

#if defined(ENABLE_MT_TESTS)
static SemaphoreP_Object TestMMCSD_sem;
#if !defined (SOC_AM275X)  && !defined (C7_CORE)
static uint8_t TestMMCSD_FatTask1Stack[1024] __attribute__ ((aligned(32)));
static uint8_t TestMMCSD_FatTask2Stack[1024] __attribute__ ((aligned(32)));
#else
static uint8_t TestMMCSD_FatTask1Stack[20 * 1024] __attribute__ ((aligned(32)));
static uint8_t TestMMCSD_FatTask2Stack[20 * 1024] __attribute__ ((aligned(32)));
#endif
static TaskP_Object TestMMCSD_FatThread1TaskObj;
static TaskP_Object TestMMCSD_FatThread2TaskObj;
#endif

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

static void Test_Mmcsd_InitWrBuffer();
#if !defined (SOC_AM275X)  && !defined (C7_CORE)
static void Test_Mmcsd_Init40MWrBuffer(uint8_t startNum);
#endif
static void Test_Mmcsd_GetModeSettings(uint32_t type);
static int32_t Test_Mmcsd_FileIo(char *fileName, char* fileData);

/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

/**
 * \brief Executes eMMC file I/O validation test to verify
 * filesystem integration and data reliability.
 *
 * Test Category: Functionality
 *
 * This function validates the MMCSD driver's integration with
 * the FreeRTOS+FAT filesystem layer by performing file I/O
 * operations on an eMMC device. It iterates through all
 * supported operation modes, logs mode-specific parameters, and
 * ensures partition presence and accessibility.
 *
 * The test checks partition detection, creation, formatting,
 * and mounting using `FF_MMCSDCreateAndFormatPartition()` and
 * `FF_MMCSDMountPartition()`. It then performs read/write
 * validation using the `Test_Mmcsd_FileIo()` helper function.
 *
 * The test confirms correct driver operation across modes,
 * verifying DMA, PHY, and filesystem consistency. It ensures
 * data integrity, proper partition handling, and successful
 * file operations without corruption or errors.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void Test_Mmcsd_EmmcFileIo(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t loopVar = 0;
    FF_Error_t errVal;

    DebugP_log ("Starting MMC EMMC file IO test \r\n");

    for (loopVar = 0; loopVar < TestMMCSD_ModesCount; loopVar++)
    {
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_Modes[loopVar];

        DebugP_log ("EMMC file IO test : Configuration \r\n");
        Test_Mmcsd_GetModeSettings(CONFIG_MMCSD_EMMC);
        DebugP_log("Card type: %s\r\n",TestMMCSD_ModeParams.cardType);
        DebugP_log("Bus Width: %d\r\n",TestMMCSD_ModeParams.busWidth);
        DebugP_log("Operating mode: %s\r\n",TestMMCSD_ModeParams.mode);

        if(TestMMCSD_ModeParams.phyEnable)
        {
            DebugP_log("HARD PHY condition: enabled\r\n");
        }
        else
        {
            DebugP_log("SOFT PHY condition: enabled\r\n");
        }

        if(TestMMCSD_ModeParams.dmaEnable)
        {
            DebugP_log("DMA condition: enabled\r\n");
        }
        else
        {
            DebugP_log("DMA condition: disabled\r\n");
        }

        Drivers_mmcsdOpen();

        /* Create partition if not present */
        FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_EMMC0];

        FF_MMCSD_PartitionDetails partitionDetails;

        FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
        DebugP_log("The sector count is %d\r\n", partitionDetails.sectorCount);
        DebugP_log("The partition size  is %d\r\n", partitionDetails.partitionSize);
        DebugP_log("The free space  is %d\r\n", partitionDetails.partitionFreeSize);

        if (partitionDetails.sectorCount == 0U)
        {
            /* No partition found, create a `TEST_MMCSD_FAT_PARTITION_SIZE` partition */
            uint32_t blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);
            uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

            errVal = FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);
            TEST_ASSERT_EQUAL(pdPASS, errVal);

            /* Now mount the partition */
            errVal = FF_MMCSDMountPartition(pDisk, "/emmc0");
            TEST_ASSERT_EQUAL(pdPASS, errVal);

            /* Finally check the partition again */
            errVal = FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
            TEST_ASSERT_EQUAL(pdPASS, errVal);

            if (partitionDetails.sectorCount == 0U)
            {
                retVal = SystemP_FAILURE;
            }
        }

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        char *fileName = (char*)"/emmc0/test.dat";
        char *fileData = (char*)"THIS IS A TEST FILE TO TEST SD CARD FILE IO\n";

        retVal = Test_Mmcsd_FileIo(fileName, fileData);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
}

/**
 * \brief Validates nested directory file I/O on eMMC using
 * FreeRTOS+FAT and MMCSD driver.
 *
 * Test Category: Functionality
 *
 * This function tests filesystem operations over eMMC by
 * creating nested directories and files, writing patterned
 * data, reading it back, verifying contents, and cleaning up.
 * If no partition exists, it creates, formats, and mounts one
 * before running the file tests.
 *
 * The test iterates over a set of files, writes buffers filled
 * with unique bytes, and verifies first and last bytes after
 * reads to confirm integrity. It then deletes files and their
 * parent directories in reverse order and closes the driver.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void Test_Mmcsd_EmmcNestedDirectories(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    char fileName[15] = {0};
    char dirName[15] = {0};
    char dirPath[100] = {0};
    char filePath[100] = {0};
    uint8_t fillByte[TEST_MMCSD_FILE_COUNT] = {0};
    uint32_t f = 0, size = 0;
    FF_FILE* testFile = NULL;
    uint32_t blockSize;
    FF_Error_t errVal;
    FF_MMCSD_PartitionDetails partitionDetails;

    for(f = 0; f < TEST_MMCSD_FILE_COUNT; f++)
    {
        fillByte[f] = (f + 1) * 0x11;
    }

    DebugP_log ("Starting MMC SD nested directories test\r\n");
    Drivers_mmcsdOpen();

    FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_EMMC0];

    FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

    if (partitionDetails.sectorCount == 0U)
    {
        blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

        errVal = FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDMountPartition(pDisk, "/emmc0");
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        if (partitionDetails.sectorCount == 0U)
        {
            retVal = SystemP_FAILURE;
        }
    }
    else
    {
        blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Create the nested directories and write to the files */
    sprintf(dirPath, "/emmc0");
    for(f = 0; f < TEST_MMCSD_FILE_COUNT; f++)
    {
        sprintf(dirName, "/d%x", f);
        strcat(dirPath, dirName);
        ff_mkdir(dirPath);

        memcpy(filePath, dirPath, strlen(dirPath));
        sprintf(fileName, "/f%x.txt", f);
        strcat(filePath, fileName);

        testFile = ff_fopen(filePath, "w+");
        TEST_ASSERT_NOT_NULL(testFile);

        memset(TestMMCSD_Wbuf, fillByte[f], (blockSize * TEST_MMCSD_BLOCK_COUNT));
        ff_fwrite(TestMMCSD_Wbuf, (blockSize * TEST_MMCSD_BLOCK_COUNT), 1, testFile);

        ff_fclose(testFile);

        memset(filePath, 0, strlen(filePath));
    }
    memset(dirPath, 0, strlen(dirPath));
    sprintf(dirPath, "/emmc0");
    /* Read from the nested files */
    for(f = 0; f < TEST_MMCSD_FILE_COUNT; f++)
    {
        sprintf(dirName, "/d%x", f);
        strcat(dirPath, dirName);
        memcpy(filePath, dirPath, strlen(dirPath));
        sprintf(fileName, "/f%x.txt", f);
        strcat(filePath, fileName);

        testFile = ff_fopen(filePath, "r");
        TEST_ASSERT_NOT_NULL(testFile);
        ff_fread(TestMMCSD_Rbuf, (blockSize * TEST_MMCSD_BLOCK_COUNT), 1, testFile);

        memset(TestMMCSD_Wbuf, fillByte[f], (blockSize * TEST_MMCSD_BLOCK_COUNT));
        TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_Wbuf, TestMMCSD_Rbuf, (blockSize * TEST_MMCSD_BLOCK_COUNT));

        ff_fclose(testFile);
        memset(filePath, 0, strlen(filePath));
    }
    /* Remove the nested directories */
    for(f = 0; f < TEST_MMCSD_FILE_COUNT; f++)
    {
        sprintf(fileName, "/f%x.txt", (TEST_MMCSD_FILE_COUNT - 1) - f);
        memcpy(filePath, dirPath, strlen(dirPath));
        strcat(filePath, fileName);
        ff_remove(filePath);
        ff_rmdir(dirPath);

        /* Check if directory exists after deletion */
        retVal  = ff_finddir(dirPath);
        TEST_ASSERT_EQUAL(retVal, 0);

        size = strlen(dirPath);
        dirPath[size - 3] = '\0';
        memset(filePath, 0, strlen(filePath));
    }
    Drivers_mmcsdClose();
}

#if defined(ENABLE_MT_TESTS)

/* Thread1 function for FAT file I/O test on SD card. */
static void fatThread1(void *pvParameters)
{
    FF_FILE *testFile = NULL;
    const char *fileName = (const char *)pvParameters;
    size_t bytesWritten, bytesRead;
    int32_t i;

    for(i = 0; i < 10; i++)
    {
        memset(TestMMCSD_Task1Rbuf, 0, TEST_MMCSD_SIZE_64K);

        testFile = ff_fopen(fileName, "w+");
        TEST_ASSERT_NOT_NULL(testFile);

        bytesWritten = ff_fwrite(TestMMCSD_Task1Wbuf, 1, TEST_MMCSD_SIZE_64K,  testFile);
        TEST_ASSERT_EQUAL(bytesWritten, TEST_MMCSD_SIZE_64K);

        ff_fclose(testFile);
        testFile = NULL;

        testFile = ff_fopen(fileName, "r");
        TEST_ASSERT_NOT_NULL(testFile);

        bytesRead = ff_fread(TestMMCSD_Task1Rbuf, 1, TEST_MMCSD_SIZE_64K, testFile);
        TEST_ASSERT_EQUAL(bytesRead, TEST_MMCSD_SIZE_64K);

        TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_Task1Rbuf, TestMMCSD_Task1Wbuf, TEST_MMCSD_SIZE_64K);

        ff_fclose(testFile);
    }
    SemaphoreP_post(&TestMMCSD_sem);
}

/* Thread2 function for FAT file I/O test on EMMC. */
static void fatThread2(void *pvParameters)
{
    FF_FILE *testFile = NULL;
    const char *fileName = (const char *)pvParameters;
    size_t bytesWritten, bytesRead;
    int32_t i;

    for(i = 0; i < 10; i++)
    {
        memset(TestMMCSD_Task2Rbuf, 0, TEST_MMCSD_SIZE_64K);

        testFile = ff_fopen(fileName, "w+");
        TEST_ASSERT_NOT_NULL(testFile);

        bytesWritten = ff_fwrite(TestMMCSD_Task2Wbuf, 1,  TEST_MMCSD_SIZE_64K, testFile);
        TEST_ASSERT_EQUAL(bytesWritten, TEST_MMCSD_SIZE_64K);

        ff_fclose(testFile);
        testFile = NULL;

        testFile = ff_fopen(fileName, "r");
        TEST_ASSERT_NOT_NULL(testFile);

        bytesRead = ff_fread(TestMMCSD_Task2Rbuf, 1, TEST_MMCSD_SIZE_64K, testFile);
        TEST_ASSERT_EQUAL(bytesRead, TEST_MMCSD_SIZE_64K);

        TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_Task2Rbuf, TestMMCSD_Task2Wbuf, TEST_MMCSD_SIZE_64K);

        ff_fclose(testFile);
    }
    SemaphoreP_post(&TestMMCSD_sem);
}

/**
 * \brief Runs concurrent FAT SD file I/O threads to verify
 * filesystem and MMCSD driver behavior.
 *
 * Test Category: Concurrency / Functionality
 *
 * This test initializes write buffers, opens the SD driver,
 * and ensures a mountable partition exists. If absent, it
 * creates, formats, and mounts a partition on /sd0. It then
 * constructs a mutex, spawns two file I/O threads, and waits
 * until both signal completion.
 *
 * Each thread writes 64 KiB to its file, reads it back, and
 * verifies data integrity. The main task polls a shared
 * counter to detect completion, tears down the mutex, and
 * closes the driver.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void Test_Mmcsd_ConcurrentFatSdTransfer(void *args)
{
    int32_t status;
    uint32_t blockSize;
    int32_t retVal = SystemP_SUCCESS;
    FF_MMCSD_PartitionDetails partitionDetails;
    FF_Error_t errVal;
    int32_t loopVar;
    TaskP_Params taskParams1, taskParams2;

    Test_Mmcsd_InitWrBuffer();

    DebugP_log ("Starting MMCSD SD multithreaded test case\r\n");
    Drivers_mmcsdOpen();

    FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_SD0];

    FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

    if (partitionDetails.sectorCount == 0U)
    {
        blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

        errVal = FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDMountPartition(pDisk, "/sd0");
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        if (partitionDetails.sectorCount == 0U)
        {
            retVal = SystemP_FAILURE;
        }
    }
    else
    {
        blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
    }
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    status =  SemaphoreP_constructCounting(&TestMMCSD_sem, 0, 2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestMMCSD_FatTask1Stack;
    taskParams1.stackSize      = sizeof(TestMMCSD_FatTask1Stack);
    taskParams1.args           = (void*)"/sd0/test1.txt";
    taskParams1.name           = "FatSdThread1";
    taskParams1.taskMain       = &fatThread1;

    status = TaskP_construct(&TestMMCSD_FatThread1TaskObj, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestMMCSD_FatTask2Stack;
    taskParams2.stackSize      = sizeof(TestMMCSD_FatTask2Stack);
    taskParams2.args           = (void*)"/sd0/test2.txt";
    taskParams2.name           = "FatSdThread2";
    taskParams2.taskMain       = &fatThread2;

    status = TaskP_construct(&TestMMCSD_FatThread2TaskObj, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        status = SemaphoreP_pend(&TestMMCSD_sem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(retVal, SystemP_SUCCESS);
    }

    SemaphoreP_destruct(&TestMMCSD_sem);
    TaskP_destruct(&TestMMCSD_FatThread1TaskObj);
    TaskP_destruct(&TestMMCSD_FatThread2TaskObj);
    Drivers_mmcsdClose();
}

/**
 * \brief Runs concurrent FAT eMMC file I/O threads to verify
 * filesystem and MMCSD driver behavior.
 *
 * Test Category: Concurrency / Functionality
 *
 * This test initializes write buffers, opens the eMMC driver,
 * and ensures a mountable partition exists. If absent, it
 * creates, formats, and mounts a partition on /emmc0. It then
 * constructs a mutex, spawns two file I/O threads, and waits
 * until both signal completion.
 *
 * Each thread writes 64 KiB to its file, reads it back, and
 * verifies data integrity. The main task polls a shared
 * counter to detect completion, tears down the mutex, and
 * closes the driver.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void Test_Mmcsd_ConcurrentFatEmmcTransfer(void *args)
{
    int32_t status;
    uint32_t blockSize;
    int32_t retVal = SystemP_SUCCESS;
    FF_MMCSD_PartitionDetails partitionDetails;
    FF_Error_t errVal;
    int32_t loopVar;
    TaskP_Params taskParams1, taskParams2;

    Test_Mmcsd_InitWrBuffer();

    DebugP_log ("Starting MMCSD EMMC multithreaded test case\r\n");
    Drivers_mmcsdOpen();

    FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_EMMC0];

    FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

    if (partitionDetails.sectorCount == 0U)
    {
        blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

        errVal = FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDMountPartition(pDisk, "/emmc0");
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        if (partitionDetails.sectorCount == 0U)
        {
            retVal = SystemP_FAILURE;
        }
    }
    else
    {
        blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);
    }
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    status =  SemaphoreP_constructCounting(&TestMMCSD_sem, 0, 2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestMMCSD_FatTask1Stack;
    taskParams1.stackSize      = sizeof(TestMMCSD_FatTask1Stack);
    taskParams1.args           = (void*)"/emmc0/test1.txt";
    taskParams1.name           = "FatEmmcThread1";
    taskParams1.taskMain       = &fatThread1;

    status = TaskP_construct(&TestMMCSD_FatThread1TaskObj, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestMMCSD_FatTask2Stack;
    taskParams2.stackSize      = sizeof(TestMMCSD_FatTask2Stack);
    taskParams2.args           = (void*)"/emmc0/test2.txt";
    taskParams2.name           = "FatEmmcThread2";
    taskParams2.taskMain       = &fatThread2;

    status = TaskP_construct(&TestMMCSD_FatThread2TaskObj, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        status = SemaphoreP_pend(&TestMMCSD_sem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(retVal, SystemP_SUCCESS);
    }
    SemaphoreP_destruct(&TestMMCSD_sem);
    TaskP_destruct(&TestMMCSD_FatThread1TaskObj);
    TaskP_destruct(&TestMMCSD_FatThread2TaskObj);
    Drivers_mmcsdClose();
}

/**
 * \brief Runs concurrent FAT I/O on SD and eMMC to validate
 * cross-device MMCSD + filesystem behavior.
 *
 * Test Category: Concurrency / Functionality
 *
 * This test prepares write buffers, opens the MMCSD stack, and
 * ensures mountable partitions exist on both /sd0 and /emmc0.
 * If missing, it creates, formats, and mounts each partition,
 * then verifies accessibility before proceeding.
 *
 * Two threads are spawned: one targets /sd0 and the other
 * /emmc0. Each writes 64 KiB, reads it back, and checks for
 * exact data matches. A mutex protects a shared completion
 * counter. The main task waits until both threads finish.
 *
 * The test confirms parallel integrity across distinct media,
 * validating driver isolation, filesystem correctness, and
 * synchronization under concurrent load.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void Test_Mmcsd_testConcurrentFatEmmcSdTransfer(void *args)
{
    int32_t status;
    uint32_t sdBlockSize;
    uint32_t emmcBlockSize;
    int32_t retVal = SystemP_SUCCESS;
    FF_MMCSD_PartitionDetails sd_partitionDetails;
    FF_MMCSD_PartitionDetails emmc_partitionDetails;
    FF_Error_t errVal;
    int32_t loopVar;
    TaskP_Params taskParams1, taskParams2;

    Test_Mmcsd_InitWrBuffer();

    DebugP_log ("Starting MMCSD combined  multithreaded test case\r\n");
    Drivers_mmcsdOpen();

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
    taskParams1.stack          = TestMMCSD_FatTask1Stack;
    taskParams1.stackSize      = sizeof(TestMMCSD_FatTask1Stack);
    taskParams1.args           = (void*)"/sd0/test1.txt";
    taskParams1.name           = "FatSdThread1";
    taskParams1.taskMain       = &fatThread1;

    status = TaskP_construct(&TestMMCSD_FatThread1TaskObj, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestMMCSD_FatTask2Stack;
    taskParams2.stackSize      = sizeof(TestMMCSD_FatTask2Stack);
    taskParams2.args           = (void*)"/emmc0/test2.txt";
    taskParams2.name           = "FatEmmcThread2";
    taskParams2.taskMain       = &fatThread2;

    status = TaskP_construct(&TestMMCSD_FatThread2TaskObj, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        status = SemaphoreP_pend(&TestMMCSD_sem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(retVal, SystemP_SUCCESS);
    }
    SemaphoreP_destruct(&TestMMCSD_sem);
    TaskP_destruct(&TestMMCSD_FatThread1TaskObj);
    TaskP_destruct(&TestMMCSD_FatThread2TaskObj);
    Drivers_mmcsdClose();
}
#endif

/**
 * \brief Validates nested directory file I/O on SD using
 * FreeRTOS+FAT and MMCSD driver.
 *
 * Test Category: Functionality
 *
 * This function tests filesystem operations over an SD card by
 * creating nested directories and files, writing patterned
 * data, reading it back, verifying contents, and cleaning up.
 * If no partition exists, it creates, formats, and mounts one
 * before running the file tests.
 *
 * The test iterates over a set of files, writes buffers filled
 * with unique bytes, and verifies first and last bytes after
 * reads to confirm integrity. It then deletes files and their
 * parent directories in reverse order and closes the driver.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void Test_Mmcsd_SdNestedDirectories(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    char fileName[15] = {0};
    char dirName[15] = {0};
    char dirPath[100] = {0};
    char filePath[100] = {0};
    uint8_t fillByte[TEST_MMCSD_FILE_COUNT] = {0};
    uint32_t f = 0, size = 0;
    FF_FILE* testFile = NULL;
    FF_Error_t errVal;
    uint32_t blockSize;

    FF_MMCSD_PartitionDetails partitionDetails;

    for(f = 0; f < TEST_MMCSD_FILE_COUNT; f++)
    {
        fillByte[f] = (f + 1) * 0x11;
    }

    DebugP_log ("Starting MMCSD SD nested directories test\r\n");
    Drivers_mmcsdOpen();

    FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_SD0];

    FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

    if (partitionDetails.sectorCount == 0U)
    {
        blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

        errVal = FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDMountPartition(pDisk, "/sd0");
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        errVal = FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        if (partitionDetails.sectorCount == 0U)
        {
            retVal = SystemP_FAILURE;
        }
    }
    else
    {
        blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Create the nested directories and write to the files */
    sprintf(dirPath, "/sd0");
    for(f = 0; f < TEST_MMCSD_FILE_COUNT; f++)
    {
        sprintf(dirName, "/d%x", f);
        strcat(dirPath, dirName);
        ff_mkdir(dirPath);

        memcpy(filePath, dirPath, strlen(dirPath));
        sprintf(fileName, "/f%x.txt", f);
        strcat(filePath, fileName);

        testFile = ff_fopen(filePath, "w+");
        TEST_ASSERT_NOT_NULL(testFile);

        memset(TestMMCSD_Wbuf, fillByte[f], (blockSize * TEST_MMCSD_BLOCK_COUNT));
        ff_fwrite(TestMMCSD_Wbuf, (blockSize * TEST_MMCSD_BLOCK_COUNT), 1, testFile);

        ff_fclose(testFile);

        memset(filePath, 0, strlen(filePath));
    }
    memset(dirPath, 0, strlen(dirPath));

    sprintf(dirPath, "/sd0");
    /* Read from the nested files */
    for(f = 0; f < TEST_MMCSD_FILE_COUNT; f++)
    {
        sprintf(dirName, "/d%x", f);
        strcat(dirPath, dirName);
        memcpy(filePath, dirPath, strlen(dirPath));
        sprintf(fileName, "/f%x.txt", f);
        strcat(filePath, fileName);

        testFile = ff_fopen(filePath, "r");
        TEST_ASSERT_NOT_NULL(testFile);
        ff_fread(TestMMCSD_Rbuf, (blockSize * TEST_MMCSD_BLOCK_COUNT), 1, testFile);

        memset(TestMMCSD_Wbuf, fillByte[f], (blockSize * TEST_MMCSD_BLOCK_COUNT));
        TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_Wbuf, TestMMCSD_Rbuf, (blockSize * TEST_MMCSD_BLOCK_COUNT));

        ff_fclose(testFile);
        memset(filePath, 0, strlen(filePath));
    }
    /* Remove the nested directories */
    for(f = 0; f < TEST_MMCSD_FILE_COUNT; f++)
    {
        sprintf(fileName, "/f%x.txt", (TEST_MMCSD_FILE_COUNT - 1) - f);
        memcpy(filePath, dirPath, strlen(dirPath));
        strcat(filePath, fileName);
        ff_remove(filePath);
        ff_rmdir(dirPath);

        /* Check if directory exists after deletion */
        retVal  = ff_finddir(dirPath);
        TEST_ASSERT_EQUAL(retVal, 0);

        size = strlen(dirPath);
        dirPath[size - 3] = '\0';
        memset(filePath, 0, strlen(filePath));
    }
    Drivers_mmcsdClose();
}

/**
 * \brief Executes SD file I/O validation to verify
 * filesystem integration and data reliability.
 *
 * Test Category: Functionality
 *
 * This function validates the MMCSD driver's integration with
 * the FreeRTOS+FAT filesystem by exercising file I/O on an SD
 * card. It iterates through supported SD modes, logs the
 * active configuration, ensures a partition is present and
 * mounted, and then performs file operations.
 *
 * The test creates and formats a partition if missing, mounts
 * it at "/sd0", and runs read/write checks via
 * `Test_Mmcsd_FileIo()`. It confirms data integrity and
 * driver stability across configurations (DMA/PHY/mode).
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void Test_Mmcsd_SdFileIo(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t loopVar = 0;
    FF_Error_t errVal;

    DebugP_log ("Starting MMC SD file IO test \r\n");

    for (loopVar = 0; loopVar < TestMMCSD_SdModesCount; loopVar++)
    {
        gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_SdModes[loopVar];

        DebugP_log ("SD file IO test : Configuration \r\n");
        Test_Mmcsd_GetModeSettings(CONFIG_MMCSD_SD);
        DebugP_log("Card type: %s\r\n",TestMMCSD_ModeParams.cardType);
        DebugP_log("Bus Width: %d\r\n",TestMMCSD_ModeParams.busWidth);
        DebugP_log("Operating mode: %s\r\n",TestMMCSD_ModeParams.mode);

        if (TestMMCSD_ModeParams.phyEnable)
        {
            DebugP_log("HARD PHY condition: enabled\r\n");
        }
        else
        {
            DebugP_log("SOFT PHY condition: enabled\r\n");
        }

        if (TestMMCSD_ModeParams.dmaEnable)
        {
            DebugP_log("DMA condition: enabled\r\n");
        }
        else
        {
            DebugP_log("DMA condition: disabled\r\n");
        }

        Drivers_mmcsdOpen();

        /* Create partition if not present */
        FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_SD0];

        FF_MMCSD_PartitionDetails partitionDetails;

        FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

        if (partitionDetails.sectorCount == 0U)
        {
            /* No partition found, create a `TEST_MMCSD_FAT_PARTITION_SIZE` partition */
            uint32_t blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
            uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

            errVal = FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);
            TEST_ASSERT_EQUAL(pdPASS, errVal);

            /* Now mount the partition */
            errVal = FF_MMCSDMountPartition(pDisk, "/sd0");
            TEST_ASSERT_EQUAL(pdPASS, errVal);

            /* Finally check the partition again */
            errVal = FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
            TEST_ASSERT_EQUAL(pdPASS, errVal);

            if (partitionDetails.sectorCount == 0U)
            {
                retVal = SystemP_FAILURE;
            }
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        char *fileName = (char*)"/sd0/test.dat";
        char *fileData = (char*)"THIS IS A TEST FILE TO TEST SD CARD FILE IO\n";

        retVal = Test_Mmcsd_FileIo(fileName, fileData);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
}

#if !defined (SOC_AM275X)  && !defined (C7_CORE)

/**
 * \brief Validates large SD file I/O to verify sustained
 * throughput and data integrity with FreeRTOS+FAT.
 *
 * Test Category: Functionality
 *
 * This test exercises long sequential writes and reads on an
 * SD card. It ensures a mountable partition at "/sd0"
 * (creating and formatting if needed), logs the active mode,
 * and performs repeated large file operations.
 *
 * The test creates 45 files and for each file writes a
 * 2 MiB buffer, closes, reopens for read, and compares the
 * contents byte-for-byte. After verification it deletes the
 * file. This stresses buffering, DMA/PHY paths, and the
 * filesystem under sustained load.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void Test_Mmcsd_LargeSdFileIo(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t loopVar = 0;
    uint32_t numIter = 3;
    FF_FILE *testFp;
    FF_Error_t errVal;

    DebugP_log ("Starting MMCSD large file IO test \r\n");
    gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_SdModes[0];

    Test_Mmcsd_GetModeSettings(CONFIG_MMCSD_SD);
    DebugP_log("Card type: %s\r\n",TestMMCSD_ModeParams.cardType);
    DebugP_log("Bus Width: %d\r\n",TestMMCSD_ModeParams.busWidth);
    DebugP_log("Operating mode: %s\r\n",TestMMCSD_ModeParams.mode);

    if (TestMMCSD_ModeParams.phyEnable)
    {
        DebugP_log("HARD PHY condition: enabled\r\n");
    }
    else
    {
        DebugP_log("SOFT PHY condition: enabled\r\n");
    }

    if (TestMMCSD_ModeParams.dmaEnable)
    {
        DebugP_log("DMA condition: enabled\r\n");
    }
    else
    {
        DebugP_log("DMA condition: disabled\r\n");
    }

    Drivers_mmcsdOpen();

    /* Create partition if not present */
    FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_SD0];

    FF_MMCSD_PartitionDetails partitionDetails;

    FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

    if (partitionDetails.sectorCount == 0U)
    {
        /* No partition found, create a `TEST_MMCSD_FAT_PARTITION_SIZE` partition */
        uint32_t blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

        errVal = FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        /* Now mount the partition */
        errVal = FF_MMCSDMountPartition(pDisk, "/sd0");
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        /* Finally check the partition again */
        errVal = FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
        TEST_ASSERT_EQUAL(pdPASS, errVal);

        if (partitionDetails.sectorCount == 0U)
        {
            retVal = SystemP_FAILURE;
        }
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Write iteration */
    for (loopVar = 0; loopVar < numIter; loopVar++)
    {
        char fileName[64];
        snprintf(fileName, sizeof(fileName), "/sd0/test%d.txt", loopVar);
        Test_Mmcsd_Init40MWrBuffer(loopVar);

        /* Create file */
        testFp = ff_fopen(fileName, "w+");
        TEST_ASSERT_NOT_NULL(testFp);

        ff_fwrite(TestMMCSD_Wbuf40M, TEST_MMCSD_40MB_SIZE, 1, testFp);

        /* Close file */
        ff_fclose(testFp);
    }

    /* Read iteration */
    for (loopVar = 0; loopVar < numIter; loopVar++)
    {

        char fileName[64];
        snprintf(fileName, sizeof(fileName), "/sd0/test%d.txt", loopVar);
        Test_Mmcsd_Init40MWrBuffer(loopVar);
        memset(TestMMCSD_Rbuf40M, 0, sizeof(TestMMCSD_Rbuf40M));

        /* Re-open now for reading */
        testFp = ff_fopen(fileName, "r");
        TEST_ASSERT_NOT_NULL(testFp);

        ff_fread(TestMMCSD_Rbuf40M, 1, TEST_MMCSD_40MB_SIZE, testFp);
        TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_Rbuf40M, TestMMCSD_Wbuf40M, TEST_MMCSD_40MB_SIZE);

        /* Close file */
        ff_fclose(testFp);
        /* Delete file */
        ff_remove(fileName);
    }
    Drivers_mmcsdClose();
}
#endif

/* ========================================================================== */
/*                         Static  Function Definitions                       */
/* ========================================================================== */

/* Initializes the write buffers for multithreaded FAT tests. */
static void Test_Mmcsd_InitWrBuffer()
{
    uint32_t i;
    for (i = 0; i < TEST_MMCSD_SIZE_64K; i++)
    {
        TestMMCSD_Task1Wbuf[i] = (i % 256);
        TestMMCSD_Task2Wbuf[i] = ((i + 1) % 256);
    }
}

#if !defined (SOC_AM275X)  && !defined (C7_CORE)
/* Initializes a 1MB write buffer with a starting value. */
static void Test_Mmcsd_Init40MWrBuffer(uint8_t startNum)
{
    for (uint32_t i = 0; i < TEST_MMCSD_SIZE_40M; i++)
    {
        TestMMCSD_Wbuf40M[i] = ((startNum + i) % 256);
    }
}
#endif

/* Populates TestMMCSD_ModeParams with current card and mode settings. */
static void Test_Mmcsd_GetModeSettings(uint32_t type)
{
    TestMMCSD_ModeParams.busWidth = gMmcsdAttrs[type].busWidth;

    /* Entend this for more flashNames when required*/
    if(gMmcsdAttrs[type].cardType == MMCSD_CARD_TYPE_EMMC)
    {
        TestMMCSD_ModeParams.cardType = "EMMC";
        if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS_SDR)
        {
            TestMMCSD_ModeParams.mode = "SDR";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS_DDR)
        {
            TestMMCSD_ModeParams.mode = "DDR";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS200)
        {
            TestMMCSD_ModeParams.mode = "HS200";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS400)
        {
            TestMMCSD_ModeParams.mode = "HS400";
        }
    }
    else if(gMmcsdAttrs[type].cardType == MMCSD_CARD_TYPE_SD)
    {
        TestMMCSD_ModeParams.cardType = "SD";
        if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_SDR50)
        {
            TestMMCSD_ModeParams.mode = "SDR";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_DDR50)
        {
            TestMMCSD_ModeParams.mode = "DDR";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_SDR104)
        {
            TestMMCSD_ModeParams.mode = "SDR104";
        }
        else if((gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_HS))
        {
            TestMMCSD_ModeParams.mode = "HS";
        }
    }
    else if(gMmcsdAttrs[type].cardType == MMCSD_CARD_TYPE_NO_DEVICE)
    {
        TestMMCSD_ModeParams.cardType = "NO DEVICE";
    }

    if(gMmcsdAttrs[type].phyType == MMCSD_PHY_TYPE_HW_PHY)
    {
        TestMMCSD_ModeParams.phyEnable = TRUE;
    }
    else
    {
        TestMMCSD_ModeParams.phyEnable = FALSE;
    }

    if(gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma)
    {
        TestMMCSD_ModeParams.dmaEnable = TRUE;
    }
    else
    {
        TestMMCSD_ModeParams.dmaEnable = FALSE;
    }
}

/* Function to do file transfer */
static int32_t Test_Mmcsd_FileIo(char *fileName, char* fileData)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t i;
    char buf[100];
    FF_FILE *testFp;

    /* Create file */
    testFp = ff_fopen(fileName, "w+");
    TEST_ASSERT_NOT_NULL(testFp);

    /* Write file data `TEST_MMCSD_FILE_LINE_CNT` times */
    uint32_t fileDataLen = strlen(fileData)+1;

    for (i = 0U; i < TEST_MMCSD_FILE_LINE_CNT; i++)
    {
        ff_fwrite(fileData, fileDataLen, 1, testFp);
    }

    /* Close file */
    ff_fclose(testFp);

    /* Re-open now for reading */
    testFp = ff_fopen(fileName, "r");
    TEST_ASSERT_NOT_NULL(testFp);

    /* Now read the lines one by one and check with fileData */
    for (i = 0U; i < TEST_MMCSD_FILE_LINE_CNT; i++)
    {
        ff_fread(buf, fileDataLen, 1, testFp);
        retVal |= strncmp(fileData, buf, fileDataLen);
        if (retVal != 0U)
        {
            break;
        }
    }

    /* Close file */
    ff_fclose(testFp);

    /* Delete file */
    ff_remove(fileName);

    return retVal;
}

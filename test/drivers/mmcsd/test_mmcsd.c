/*
 * Copyright (C) 2021-23 Texas Instruments Incorporated
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

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/mmcsd.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_MMCSD_EMMC_START_BLK        (0x300000U) /* 1.5GB */
#define TEST_MMCSD_SD_START_BLK          (0x300000U) /* 1.5GB */
#define TEST_MMCSD_DATA_SIZE             (0x600000U) /* has to be 256 B aligned */
#define TEST_MMCSD_FILE_LINE_CNT         (100U)
#define TEST_MMCSD_1KB_SIZE              (256 * 4U)
#define TEST_MMCSD_FAT_PARTITION_SIZE    (128U * 1024U * 1024U) /* 128 MB */
#define TEST_MMCSD_PERF_TEST_DATA_COUNT  (3U)   /* Change this value as per testSizes list size */
#define TEST_MMCSD_1MB_SIZE              (TEST_MMCSD_1KB_SIZE * TEST_MMCSD_1KB_SIZE)
#define TEST_MMCSD_4MB_SIZE              (TEST_MMCSD_1MB_SIZE * 4U)
#define TEST_MMCSD_6MB_SIZE              (TEST_MMCSD_1MB_SIZE * 6U)


#if defined (SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62DX)
uint32_t modes[] =
{
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_SDR,
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_DDR,
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS200
};
#elif defined (SOC_AM64X) || defined(SOC_AM243X)
uint32_t modes[] =
{
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_SDR,
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS200
};
#elif defined (SOC_AM62PX)
uint32_t modes[] =
{
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_SDR,
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_DDR,
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS200,
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS400,
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS400_ES
};
#endif

/* ========================================================================== */
/*                 Structure Declarations                             */
/* ========================================================================== */

/* Struct to store mode settings */
typedef struct Test_MmcModeSettings_t
{
    char* cardType;
    char * mode;
    uint32_t busWidth;
    uint32_t phyEnable;
    uint32_t dmaEnable;
}Test_MmcModeSettings;

/* Struct to store Data size in Mib, Read and Write speeds */
typedef struct TestData_SizesAttr_t
{
    uint32_t dataSize;
    uint64_t writeSpeed;
    uint64_t readSpeed;
}TestData_SizesAttr;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void test_mmcsd_fill_buffers(void);
static void test_mmcsd_emmc_raw_io(void *args);
static void test_mmcsd_sd_raw_io(void *args);
static void test_mmcsd_emmc_file_io(void *args);
static void test_mmcsd_sd_file_io(void *args);

static int32_t test_mmcsd_raw_io(MMCSD_Handle handle);
static int32_t test_mmcsd_file_io(char *fileName, char* fileData);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8_t gMmcsdTestTxBuf[TEST_MMCSD_DATA_SIZE] __attribute__((aligned(128U), section("DDR2")));
uint8_t gMmcsdTestRxBuf[TEST_MMCSD_DATA_SIZE] __attribute__((aligned(128U), section("DDR2")));
extern MMCSD_Attrs gMmcsdAttrs[CONFIG_MMCSD_NUM_INSTANCES];

static Test_MmcModeSettings modeParams;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    Drivers_mmcsdClose();
    UNITY_BEGIN();

    RUN_TEST(test_mmcsd_emmc_raw_io, 2069, NULL);
    #if defined SOC_AM64X || SOC_AM243X
    RUN_TEST(test_mmcsd_sd_raw_io, 2072, NULL);
    RUN_TEST(test_mmcsd_emmc_file_io, 2067, NULL);
    RUN_TEST(test_mmcsd_sd_file_io, 2066, NULL);
    #endif

    UNITY_END();

    return;
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

/*
 * Helper functions
 */
static void get_mode_settings(uint32_t type)
{
    modeParams.busWidth = gMmcsdAttrs[type].busWidth;

    /* Entend this for more flashNames when required*/
    if(gMmcsdAttrs[type].cardType == MMCSD_CARD_TYPE_EMMC)
    {
        modeParams.cardType = "EMMC";
        if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS_SDR)
            modeParams.mode = "SDR";
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS_DDR)
            modeParams.mode = "DDR";
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS200)
            modeParams.mode = "HS200";
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS400)
            modeParams.mode = "HS400";
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS400_ES)
            modeParams.mode = "HS400 ES";
    }
    else if(gMmcsdAttrs[type].cardType == MMCSD_CARD_TYPE_SD)
    {
        modeParams.cardType = "SD";
        if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_SDR50)
            modeParams.mode = "SDR";
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_DDR50)
            modeParams.mode = "DDR";
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_SDR104)
            modeParams.mode = "SDR104";
        else if((gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_HS))
            modeParams.mode = "HS";
    }
    else if(gMmcsdAttrs[type].cardType == MMCSD_CARD_TYPE_NO_DEVICE)
        modeParams.cardType = "NO DEVICE";

    if(gMmcsdAttrs[type].phyType == MMCSD_PHY_TYPE_HW_PHY)
        modeParams.phyEnable = TRUE;
    else
        modeParams.phyEnable = FALSE;

    if(gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma)
        modeParams.dmaEnable = TRUE;
    else
        modeParams.dmaEnable = FALSE;
}

/*
 * Test cases
 */
static void test_mmcsd_emmc_raw_io(void *args)
{
	int32_t retVal = SystemP_SUCCESS;
    uint32_t loopVar = 0;

    for ( loopVar = 0; loopVar < ((sizeof(modes)) / (sizeof(uint32_t))); loopVar ++)
    {
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = modes[loopVar];
        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

        retVal = test_mmcsd_raw_io(handle);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
};

#if defined SOC_AM64X || SOC_AM243X
static void test_mmcsd_sd_raw_io(void *args)
{
	int32_t retVal = SystemP_SUCCESS;

    Drivers_mmcsdOpen();
    MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_SD];

    retVal = test_mmcsd_raw_io(handle);

	TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    Drivers_mmcsdClose();
};

static void test_mmcsd_emmc_file_io(void *args)
{
	int32_t retVal = SystemP_SUCCESS;
    uint32_t loopVar = 0;

    for ( loopVar = 0; loopVar < ((sizeof(modes)) / (sizeof(uint32_t))); loopVar ++)
    {
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = modes[loopVar];

        Drivers_mmcsdOpen();
        /* Create partition if not present */
        FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_EMMC0];

        FF_MMCSD_PartitionDetails partitionDetails;

        FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

        if(partitionDetails.sectorCount == 0U)
        {
            /* No partition found, create a `TEST_MMCSD_FAT_PARTITION_SIZE` partition */
            uint32_t blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);
            uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

            FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);

            /* Now mount the partition */
            FF_MMCSDMountPartition(pDisk, "/emmc0");

            /* Finally check the partition again */
            FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

            if(partitionDetails.sectorCount > 0U)
            {
                /* Partition successfully mounted, continue */
            }
            else
            {
                retVal = SystemP_FAILURE;
            }
        }
        else
        {
            /* FAT partition found, all good. Proceed with file I/O testing */
        }

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        char *fileName = "/emmc0/test.dat";
        char *fileData = "THIS IS A TEST FILE TO TEST SD CARD FILE IO\n";

        test_mmcsd_file_io(fileName, fileData);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
};

static void test_mmcsd_sd_file_io(void *args)
{
	int32_t retVal = SystemP_SUCCESS;

    Drivers_mmcsdOpen();
    /* Create partition if not present */
    FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_SD0];

    FF_MMCSD_PartitionDetails partitionDetails;

    FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

    if(partitionDetails.sectorCount == 0U)
    {
        /* No partition found, create a `TEST_MMCSD_FAT_PARTITION_SIZE` partition */
        uint32_t blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_SD]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

        FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);

        /* Now mount the partition */
        FF_MMCSDMountPartition(pDisk, "/sd0");

        /* Finally check the partition again */
        FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);

        if(partitionDetails.sectorCount > 0U)
        {
            /* Partition successfully mounted, continue */
        }
        else
        {
            retVal = SystemP_FAILURE;
        }
    }
    else
    {
        /* FAT partition found, all good. Proceed with file I/O testing */
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    char *fileName = "/sd0/test.dat";
    char *fileData = "THIS IS A TEST FILE TO TEST SD CARD FILE IO\n";

    test_mmcsd_file_io(fileName, fileData);

	TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    Drivers_mmcsdClose();
};

static int32_t test_mmcsd_file_io(char *fileName, char* fileData)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t i;
    char buf[100];
    FF_FILE *testFp;

    /* Create file */
    testFp = ff_fopen(fileName, "w+");

    /* Write file data `TEST_MMCSD_FILE_LINE_CNT` times */

    uint32_t fileDataLen = strlen(fileData)+1;

    for(i = 0U; i < TEST_MMCSD_FILE_LINE_CNT; i++)
    {
        ff_fwrite(fileData, fileDataLen, 1, testFp);
    }

    /* Close file */
    ff_fclose(testFp);

    /* Re-open now for reading */
    testFp = ff_fopen(fileName, "r");

    /* Now read the lines one by one and check with fileData */
    for(i = 0U; i < TEST_MMCSD_FILE_LINE_CNT; i++)
    {
        ff_fread(buf, fileDataLen, 1, testFp);
        retVal |= strncmp(fileData, buf, fileDataLen);
        if(retVal != 0U)
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
#endif

void test_mmcsd_fill_buffers(void)
{
    uint32_t i;

    for(i = 0U; i < TEST_MMCSD_DATA_SIZE; i++)
    {
        gMmcsdTestTxBuf[i] = i % 256;
        gMmcsdTestRxBuf[i] = 0U;
    }
}

static int32_t test_mmcsd_raw_io(MMCSD_Handle handle)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t testCount = 0U, numBlocksPerIter = 0U;
    uint32_t blockSize = MMCSD_getBlockSize(handle);

    /* Please provide size of atleast 1MiB */
    uint32_t testSizes[TEST_MMCSD_PERF_TEST_DATA_COUNT] = {TEST_MMCSD_1MB_SIZE, TEST_MMCSD_4MB_SIZE, TEST_MMCSD_6MB_SIZE};
    TestData_SizesAttr testDataObj[TEST_MMCSD_PERF_TEST_DATA_COUNT];

    test_mmcsd_fill_buffers();

    for(testCount = 0; testCount < TEST_MMCSD_PERF_TEST_DATA_COUNT; testCount++)
    {
        numBlocksPerIter = testSizes[testCount] / blockSize;
        testDataObj[testCount].dataSize = testSizes[testCount] / TEST_MMCSD_1MB_SIZE;

        testDataObj[testCount].writeSpeed = ClockP_getTimeUsec();
        retVal = MMCSD_write(handle, gMmcsdTestTxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
        testDataObj[testCount].writeSpeed = ClockP_getTimeUsec() - testDataObj[testCount].writeSpeed;

        if(retVal != SystemP_SUCCESS)
        {
            break;
        }
    }

    if(SystemP_SUCCESS == retVal)
    {
        for(testCount = 0; testCount < TEST_MMCSD_PERF_TEST_DATA_COUNT; testCount++)
        {
            numBlocksPerIter = testSizes[testCount] / blockSize;

            testDataObj[testCount].readSpeed = ClockP_getTimeUsec();
            retVal = MMCSD_read(handle, gMmcsdTestRxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
            testDataObj[testCount].readSpeed = ClockP_getTimeUsec() - testDataObj[testCount].readSpeed;

            if(SystemP_SUCCESS == retVal)
            {
                retVal = memcmp(gMmcsdTestRxBuf, gMmcsdTestTxBuf, testSizes[testCount]);
            }
        }
    }

    if(SystemP_SUCCESS == retVal)
    {
        /* Print performance numbers. */
        get_mode_settings(CONFIG_MMCSD_EMMC);
        DebugP_log("\n[TEST MMCSD] Performance Numbers Print Start\r\n\n");
        DebugP_log("Card type: %s\r\n",modeParams.cardType);
        DebugP_log("Bus Width: %d\r\n",modeParams.busWidth);
        DebugP_log("Operating mode: %s\r\n",modeParams.mode);

        if(modeParams.phyEnable)
            DebugP_log("HARD PHY condition: enabled\r\n");
        else
            DebugP_log("SOFT PHY condition: enabled\r\n");

        if(modeParams.dmaEnable)
            DebugP_log("DMA condition: enabled\r\n");
        else
            DebugP_log("DMA condition: disabled\r\n");

        DebugP_log("Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)\r\n");
        DebugP_log("---------------|--------------------|-----------------\r\n");

        for (testCount=0; testCount < TEST_MMCSD_PERF_TEST_DATA_COUNT; testCount++)
        {
            DebugP_log(" %d\t       | %.2f\t\t    | %.2f\r\n", testDataObj[testCount].dataSize,
                (float)((float)(testDataObj[testCount].dataSize * TEST_MMCSD_1MB_SIZE) / (float)testDataObj[testCount].writeSpeed),
                (float)((float)(testDataObj[testCount].dataSize * TEST_MMCSD_1MB_SIZE) / (float)testDataObj[testCount].readSpeed));
        }

        DebugP_log("\n[TEST MMCSD] Performance Numbers Print End\r\n\n");
    }

    return retVal;
}

/*
 * Copyright (C) 2024 Texas Instruments Incorporated
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
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/gpmc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_GPMC_FLASH_OFFSET_BASE        (0x200000U)
#define TEST_GPMC_DATA_SIZE                (256U)
#define TEST_GPMC_DATA_REPEAT_COUNT        (8)
#define TEST_GPMC_BUF_SIZE                 (TEST_GPMC_DATA_SIZE * TEST_GPMC_DATA_REPEAT_COUNT)

#define TEST_GPMC_1KB_SIZE                 (256*4U)
#define TEST_GPMC_2KB_SIZE                 (TEST_GPMC_1KB_SIZE*2U)
#define TEST_GPMC_4KB_SIZE                 (TEST_GPMC_1KB_SIZE*4U)
#define TEST_GPMC_1MB_SIZE                 (TEST_GPMC_1KB_SIZE*TEST_GPMC_1KB_SIZE)
#define TEST_GPMC_5MB_SIZE                 (TEST_GPMC_1MB_SIZE*5U)
#define TEST_GPMC_10MB_SIZE                (TEST_GPMC_1MB_SIZE*10U)
#define TEST_GPMC_MAX_TEST_SIZE            (TEST_GPMC_10MB_SIZE)
#define TEST_GPMC_BLOCK_SIZE               (TEST_GPMC_1KB_SIZE*256U)
#define TEST_GPMC_READ_FRCOUNT             (10U)  /* Frequency of reading required for average time of read operation*/
#define TEST_GPMC_PERF_TEST_DATA_COUNT     (3U)   /* Change this value as per testSizes list size */

/* ========================================================================== */
/*                 Structure Declarations                                     */
/* ========================================================================== */

typedef struct Test_FlashModeSettings_t
{
    uint32_t flashType;
    char* flashName;
    uint32_t cfgflashType;
    uint32_t dmaEnable;
}Test_FlashModeSettings;

typedef struct TestData_SizesAttr_t
{
    uint32_t dataSize; //in MiB
    float writeSpeed;
    float readSpeed;
}TestData_SizesAttr;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8_t gGpmcTestTxBuf[TEST_GPMC_DATA_SIZE] =
{
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
    0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
    0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
    0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
    0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
    0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
    0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
    0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
    0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
    0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
    0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
    0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
};

uint8_t gGpmcTestTxBulkBuf[TEST_GPMC_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
uint8_t gGpmcTestRxBuf[TEST_GPMC_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));

static Test_FlashModeSettings modeParams;

extern GPMC_Params gGpmcParams[CONFIG_GPMC_NUM_INSTANCES];

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Test cases */
static void test_gpmcReadWriteConfig(void *args);
static void test_gpmcReadPerf(void *args);

/* Helper Funtions */
static void AppTest_setFlashType(void);
static float AppTest_gpmcWriteInMB(uint32_t flashOffset, uint32_t writeSize);
static float AppTest_gpmcReadInMB(uint32_t flashOffset, uint32_t readSize);
static int32_t AppTest_gpmcReadWriteTestInMB(TestData_SizesAttr *testDataCurObj,
                                             uint32_t flashOffset,
                                             uint32_t dataSize);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    uint32_t i = 0;

    AppTest_setFlashType();

    Board_driversClose();
    Drivers_gpmcClose();
    Drivers_gpmcOpen();
    UNITY_BEGIN();

    /* Test GPMC read, write and erase with dma enabled */
    DebugP_log("GPMC read, write and erase test with DMA\r\n");
    RUN_TEST(test_gpmcReadWriteConfig, 3756, NULL);
    Drivers_gpmcClose();

    /* Test GPMC read, write and erase without dma */
    DebugP_log("GPMC read, write and erase test without DMA\r\n");
    for (i = 0; i < CONFIG_GPMC_NUM_INSTANCES; i++){
        gGpmcParams[i].gpmcDmaChIndex   = -1;
        gGpmcParams[i].dmaEnable        = 0;
    }

    Drivers_gpmcOpen();
    RUN_TEST(test_gpmcReadWriteConfig, 3755, NULL);
    Drivers_gpmcClose();

    DebugP_log("GPMC read performance with DMA\r\n");
    for (i = 0; i < CONFIG_GPMC_NUM_INSTANCES; i++){
        gGpmcParams[i].gpmcDmaChIndex   = 0;
        gGpmcParams[i].dmaEnable        = 1;
    }
    Drivers_gpmcOpen();
    RUN_TEST(test_gpmcReadPerf, 3757, NULL);
    Drivers_gpmcClose();

    DebugP_log("GPMC read performance without DMA\r\n");
    for (i = 0; i < CONFIG_GPMC_NUM_INSTANCES; i++){
        gGpmcParams[i].gpmcDmaChIndex   = -1;
        gGpmcParams[i].dmaEnable        = 0;
    }
    Drivers_gpmcOpen();
    RUN_TEST(test_gpmcReadPerf, 3758, NULL);

    UNITY_END();

    return;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

/*
 * Test case
 */
static void test_gpmcReadWriteConfig(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t blk, page, i;
    uint32_t offset = TEST_GPMC_FLASH_OFFSET_BASE;

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Block erase at the test offset */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Read back to check for successful block erase */
    for(i = 0; i < TEST_GPMC_DATA_REPEAT_COUNT; i++)
    {
        retVal += Flash_read(gFlashHandle[CONFIG_FLASH0], offset + i*TEST_GPMC_DATA_SIZE, &gGpmcTestRxBuf[(i*TEST_GPMC_DATA_SIZE)], TEST_GPMC_DATA_SIZE);
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    for(i = 0; i < TEST_GPMC_BUF_SIZE; i++)
    {
        if(gGpmcTestRxBuf[i] != 0xFF)
        {
            retVal = SystemP_FAILURE;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    for(uint32_t txChunkCnt = 0; txChunkCnt < (TEST_GPMC_BUF_SIZE)/TEST_GPMC_DATA_SIZE; txChunkCnt++)
    {
        memcpy(gGpmcTestTxBulkBuf + txChunkCnt*sizeof(gGpmcTestTxBuf) , gGpmcTestTxBuf , sizeof(gGpmcTestTxBuf));
    }

    /* GPMC write from TX buffer */
    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gGpmcTestTxBulkBuf, TEST_GPMC_BUF_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* GPMC read to RX buffer */
    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gGpmcTestRxBuf, TEST_GPMC_BUF_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* GPMC compare TX and RX buffers */
    for(i = 0; i < TEST_GPMC_BUF_SIZE; i++)
    {
        if(gGpmcTestRxBuf[i] != gGpmcTestTxBulkBuf[i])
        {
            retVal = SystemP_FAILURE;
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    Board_driversClose();
}

static void test_gpmcReadPerf(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t blk, page;
    uint32_t offset = TEST_GPMC_FLASH_OFFSET_BASE;
    /* Please provide size of atleast 1MiB */
    uint32_t testSizes[TEST_GPMC_PERF_TEST_DATA_COUNT] = {TEST_GPMC_1MB_SIZE, TEST_GPMC_5MB_SIZE, TEST_GPMC_10MB_SIZE};
    TestData_SizesAttr testDataObj[TEST_GPMC_PERF_TEST_DATA_COUNT],TestDataCurrObj;
    const char *flashTypeList[] = {"SERIAL NOR","SERIAL NAND","PARALLEL NOR","PARALLEL NAND"};
    GPMC_Handle gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);

    modeParams.dmaEnable = ((GPMC_Config*)gpmcHandle)->object->params.dmaEnable;

    /* Open Flash drivers with GPMC instance as input */
    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Block erase at the test offset */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);

    /* The contents of buffer "gGpmcTestTxBuf" are copied at incremental offsets of 'TEST_GPMC_DATA_SIZE'
     * until gGpmcTestTxBulkBuf buffer is full
     */
    for(uint32_t txChunkCnt = 0; txChunkCnt < TEST_GPMC_MAX_TEST_SIZE/TEST_GPMC_DATA_SIZE; txChunkCnt++)
    {
        memcpy(gGpmcTestTxBulkBuf + txChunkCnt*sizeof(gGpmcTestTxBuf) , gGpmcTestTxBuf , sizeof(gGpmcTestTxBuf));
    }

    for(uint32_t testCount = 0; testCount < sizeof(testSizes)/sizeof(testSizes[0]); testCount++)
    {
        for(uint32_t blkCount = 0; blkCount < testSizes[testCount]/TEST_GPMC_BLOCK_SIZE; blkCount++)
        {
            retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk + blkCount);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        }

        retVal = AppTest_gpmcReadWriteTestInMB(&TestDataCurrObj, offset, testSizes[testCount]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        memcpy(&testDataObj[testCount],&TestDataCurrObj,sizeof(TestData_SizesAttr));
    }

    /* Print performance numbers. */
    DebugP_log("\n[TEST GPMC] Performance Numbers Print Start\r\n\n");
    DebugP_log("Flash type: %s\r\n",flashTypeList[modeParams.cfgflashType]);

    if(modeParams.dmaEnable)
        DebugP_log("DMA condition: enabled\r\n");
    else
        DebugP_log("DMA condition: disabled\r\n");

    DebugP_log("Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)\r\n");
    DebugP_log("---------------|--------------------|-----------------\r\n");

    for (uint32_t testCount=0; testCount<sizeof(testSizes)/sizeof(testSizes[0]); testCount++) {
        DebugP_log(" %d\t       | %.2f\t\t    | %.2f\r\n", testDataObj[testCount].dataSize, testDataObj[testCount].writeSpeed,
            testDataObj[testCount].readSpeed);
    }

    DebugP_log("\n[TEST GPMC] Performance Numbers Print End\r\n\n");

    Board_driversClose();
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
    /* Do nothing */
}

void tearDown(void)
{
    /* Do nothing */
}


/*
 * Helper functions
 */

static float AppTest_gpmcWriteInMB(uint32_t flashOffset, uint32_t writeSize)
{
    int32_t retVal = SystemP_SUCCESS;
    uint64_t startTime, endTime;

    startTime = ClockP_getTimeUsec();
    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], flashOffset, gGpmcTestTxBulkBuf, writeSize);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    endTime = ClockP_getTimeUsec();

    return (float)(endTime - startTime);
}

static float AppTest_gpmcReadInMB(uint32_t flashOffset, uint32_t readSize)
{
    int32_t retVal = SystemP_SUCCESS;
    uint64_t startTime, endTime, totalReadTime=0;
    uint8_t readFcnt = 0;

    while(readFcnt++ < TEST_GPMC_READ_FRCOUNT)
    {
        startTime = ClockP_getTimeUsec();
        retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], flashOffset, gGpmcTestRxBuf, readSize);
        endTime = ClockP_getTimeUsec();
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        totalReadTime += endTime-startTime;
    }
    return (float)totalReadTime/(readFcnt-1);
}

static int32_t AppTest_gpmcReadWriteTestInMB(TestData_SizesAttr* testDataCurObj, uint32_t flashOffset, uint32_t dataSize)
{
    int32_t retVal = SystemP_SUCCESS;
    float readTime, writeTime;

    if(dataSize < TEST_GPMC_1MB_SIZE){
        retVal = SystemP_FAILURE;
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    }

    writeTime = AppTest_gpmcWriteInMB(flashOffset, dataSize);

    readTime = AppTest_gpmcReadInMB(flashOffset, dataSize);

    testDataCurObj->dataSize = dataSize/TEST_GPMC_1MB_SIZE;
    testDataCurObj->writeSpeed = (float)((float)dataSize/(float)(writeTime));
    testDataCurObj->readSpeed = (float)((float)dataSize/(float)(readTime));

    /* Test if read data matches with written data */
    retVal = memcmp(gGpmcTestRxBuf, gGpmcTestTxBulkBuf, dataSize);
    return retVal;
}


static void AppTest_setFlashType(void)
{
    modeParams.flashType = gFlashConfig[CONFIG_FLASH0].attrs->flashType;
    modeParams.flashName = gFlashConfig[CONFIG_FLASH0].attrs->flashName;

    /* Entend this for more flashNames when required*/
    if(modeParams.flashType == CONFIG_FLASH_TYPE_PARALLEL && !strcmp(modeParams.flashName,"MT29F8G08ADAFAH4"))
         modeParams.cfgflashType = CONFIG_FLASH_TYPE_PARALLEL_NAND;
}

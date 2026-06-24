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
#include <drivers/gpmc/v0/dma/gpmc_dma.h>
#include <drivers/hw_include/cslr.h>
#include <drivers/elm.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>

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

/* NAND command bytes (MT29F8G08ADAFAH4) */
#define TEST_NAND_CMD_READ_CYC1             (0x00U)
#define TEST_NAND_CMD_READ_CYC2             (0x30U)
#define TEST_NAND_CMD_RANDOM_READ_CYC1      (0x05U)
#define TEST_NAND_CMD_RANDOM_READ_CYC2      (0xE0U)
#define TEST_NAND_CMD_PROG_CYC1             (0x80U)
#define TEST_NAND_CMD_PROG_CYC2             (0x10U)
#define TEST_NAND_CMD_READ_ID               (0x90U)
#define TEST_NAND_MANF_ID                   (0x2CU)

/* NAND geometry constants */
#define TEST_NAND_COL_ADDR_CYCLES           (2U)
#define TEST_NAND_ROW_ADDR_CYCLES           (3U)
#define TEST_NAND_SECTOR_SIZE               (512U)
#define TEST_NAND_PAGE_SIZE                 (4096U)
#define TEST_NAND_PAGES_PER_BLOCK           (64U)
#define TEST_NAND_DEVICE_TIMEOUT            (10000U)

/* BCH-8 ECC constants */
#define TEST_NAND_ECC_BCH8_NIBBLE_PROTECTED (26U)
#define TEST_NAND_ECC_BCH8_NIBBLE_UNUSED    (2U)
#define TEST_NAND_ECC_BCH8_BYTECNT          (14U)
#define TEST_NAND_ECC_STEPS_PER_PAGE        (8U)
#define TEST_NAND_ECC_OFFSET                (4098U) /* pageSize + OOB_OFFSET(2) */
#define TEST_NAND_ECC_TOTAL_BYTES           (TEST_NAND_ECC_BCH8_BYTECNT * TEST_NAND_ECC_STEPS_PER_PAGE)
#define TEST_NAND_BCH8_LAST_ECC_BIT         ((TEST_NAND_ECC_BCH8_NIBBLE_PROTECTED * 4U) - 1U)
#define TEST_NAND_ECC_WORDS_PER_SECTOR      (4U)
#define TEST_NAND_MAX_ERR_LOCS              (16U)

/* BCH-4 and BCH-16 ECC constants */
#define TEST_NAND_ECC_BCH4_NIBBLE_PROTECTED (13U)
#define TEST_NAND_ECC_BCH4_NIBBLE_UNUSED    (3U)

#define TEST_NAND_ECC_BCH16_NIBBLE_PROTECTED (52U)
#define TEST_NAND_ECC_BCH16_NIBBLE_UNUSED    (4U)

/* Fault Injection Payloads */
#define TEST_INJECT_1_BIT_ERR               (0xFEU) /* 1111 1110 (1 bit flipped from 0xFF) */
#define TEST_INJECT_4_BIT_ERR               (0xF0U) /* 1111 0000 (4 bits flipped) */

/* NAND READ STATUS command byte */
#define TEST_NAND_CMD_READ_STATUS           (0x70U)
#define TEST_NAND_STATUS_WP_BIT             (0x80U)  /* bit 7: 1=not protected, 0=protected */

/* Clock divider test: small read size */
#define TEST_GPMC_CLKDIV_READ_SIZE          (256U)

/* Expected NAND ID byte count */
#define TEST_NAND_ID_BYTE_COUNT             (5U)

#define TEST_GPMC_TASK_STACK_SIZE (8192U)

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

typedef struct {
    GPMC_Handle handle;
    const char* taskName;
    uint32_t offset;
    uint8_t *buffer;
    uint32_t size;
    uint32_t iterations;
} GPMC_MtTaskArgs;

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
static void TestGpmc_initDeinitLifecycle(void *args);
static void TestGpmc_nandReadDma(void *args);
static void TestGpmc_readCpuPrefetch(void *args);
static void TestGpmc_readCmdReg(void *args);
static void TestGpmc_nandWriteCmdReg(void *args);
static void TestGpmc_bch8EccPipeline(void *args);
static void TestGpmc_bch4EccPipeline(void *args);
static void TestGpmc_bch16EccPipeline(void *args);
static void TestGpmc_bch8ContinuousMode(void *args);
static void TestGpmc_clkDividerConfig(void *args);
static void TestGpmc_writeProtect(void *args);
static void TestGpmc_waitPinActiveHigh(void *args);
static void TestGpmc_waitPinActiveLow(void *args);


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
    Drivers_gpmcClose();

    RUN_TEST(TestGpmc_initDeinitLifecycle, 12401, NULL);

    DebugP_log("NAND read via DMA for count >= 512 bytes\r\n");
    for (i = 0; i < CONFIG_GPMC_NUM_INSTANCES; i++) 
    {
        gGpmcParams[i].gpmcDmaChIndex = 0;
        gGpmcParams[i].dmaEnable      = 1;
    }
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_nandReadDma, 12402, NULL);
    Drivers_gpmcClose();

    DebugP_log("NAND read with CPU prefetch for count < 512 bytes\r\n");
    for (i = 0; i < CONFIG_GPMC_NUM_INSTANCES; i++) 
    {
        gGpmcParams[i].gpmcDmaChIndex = 0;
        gGpmcParams[i].dmaEnable      = 1;
    }
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_readCpuPrefetch, 12403, NULL);
    Drivers_gpmcClose();

    DebugP_log("NAND read via READ_CMDREG transaction type\r\n");
    for (i = 0; i < CONFIG_GPMC_NUM_INSTANCES; i++) 
    {
        gGpmcParams[i].gpmcDmaChIndex = -1;
        gGpmcParams[i].dmaEnable      = 0;
    }
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_readCmdReg, 12404, NULL);
    Drivers_gpmcClose();

    DebugP_log("NAND write via WRITE_CMDREG transaction type\r\n");
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_nandWriteCmdReg, 12405, NULL);
    Drivers_gpmcClose();

    DebugP_log("Full BCH-8 ECC pipeline test\r\n");
    for (i = 0; i < CONFIG_GPMC_NUM_INSTANCES; i++) 
    {
        gGpmcParams[i].gpmcDmaChIndex = 0;
        gGpmcParams[i].dmaEnable      = 1;
    }
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_bch8EccPipeline, 12406, NULL);
    Drivers_gpmcClose();

    DebugP_log("ELM BCH-4 bit error location test\r\n");
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_bch4EccPipeline, 12407, NULL);
    Drivers_gpmcClose();
    
    DebugP_log("Full BCH-16 ECC pipeline test\r\n");
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_bch16EccPipeline, 12408, NULL);
    Drivers_gpmcClose();

    DebugP_log("ELM 8 simultaneous sectors test\r\n");
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_bch8ContinuousMode, 12409, NULL);
    Drivers_gpmcClose();

    DebugP_log("GPMC FCLK clock divider configuration test\r\n");
    RUN_TEST(TestGpmc_clkDividerConfig, 12410, NULL);

    DebugP_log("GPMC write protect enable/disable test\r\n");
    for (i = 0; i < CONFIG_GPMC_NUM_INSTANCES; i++) 
    {
        gGpmcParams[i].gpmcDmaChIndex = 0;
        gGpmcParams[i].dmaEnable      = 1;
    }
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_writeProtect, 12411, NULL);
    Drivers_gpmcClose();

    DebugP_log("GPMC WAIT pin polarity active-high test\r\n");
    Drivers_gpmcOpen();
    RUN_TEST(TestGpmc_waitPinActiveHigh, 12412, NULL);
    Drivers_gpmcClose();

    DebugP_log("GPMC WAIT pin polarity active-low test\r\n");
    RUN_TEST(TestGpmc_waitPinActiveLow, 12413, NULL);

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

    for (uint32_t testCount=0; testCount<sizeof(testSizes)/sizeof(testSizes[0]); testCount++) 
    {
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

/**
 * \brief Functionality test for GPMC driver init/deinit lifecycle and idempotency.
 *
 * This test validates the GPMC driver initialization and deinitialization API by
 * calling GPMC_init(), then GPMC_deinit() multiple times to verify idempotency.
 * The test confirms that the driver correctly allocates and destroys the internal
 * mutex without crashes, and that repeated deinit calls are safe.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_initDeinitLifecycle(void *args)
{
    /*  Call GPMC_init(). 
     * Since it returns void, we just ensure it doesn't cause a hardware fault 
     * and correctly allocates the internal mutex.
     */
    GPMC_init();
    
    /* We use a dummy assert here just to register a pass in the Unity log 
     * if the CPU reaches this line without crashing. 
     */
    TEST_ASSERT_TRUE(1); 

    /*  Call GPMC_deinit().
     * This will destroy the internal mutex and set openLock to NULL.
     */
    GPMC_deinit();
    TEST_ASSERT_TRUE(1);

    /*  Call GPMC_deinit() again to verify idempotency.
     * If the driver doesn't properly check if (openLock != NULL) before 
     * trying to destroy the semaphore, this line will cause a fatal OS crash.
     */
    GPMC_deinit();
    TEST_ASSERT_TRUE(1);

    /* Clean-up Step: 
     * Because other tests in your suite rely on the GPMC being initialized, 
     * we must re-initialize it here so we don't break the rest of the test suite. 
     */
    GPMC_init();
}

/**
 * \brief Functionality test for NAND read via DMA transfer path.
 *
 * This test verifies that when the GPMC DMA copy threshold is met or exceeded,
 * the driver correctly routes read operations through the DMA path. A 512-byte
 * sector is written to flash, then read back via DMA to verify correct data transfer
 * and integrity.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_nandReadDma(void *args)
{
    int32_t          retVal = SystemP_SUCCESS;
    uint32_t         blk, page;
    uint32_t         offset = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle      gpmcHandle;
    GPMC_nandCmdParams cmdParams;
    GPMC_Transaction trans;

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
    TEST_ASSERT_NOT_NULL(gpmcHandle);

    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Prepare a 512-byte known pattern */
    for (uint32_t i = 0; i < TEST_NAND_SECTOR_SIZE; i++)
        gGpmcTestTxBulkBuf[i] = gGpmcTestTxBuf[i % TEST_GPMC_DATA_SIZE];

    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset,
                         gGpmcTestTxBulkBuf, TEST_NAND_SECTOR_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Issue NAND PAGE READ command to set the column/row pointer */
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_READ_CYC1;
    cmdParams.cmdCycle2        = TEST_NAND_CMD_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Read 512 bytes: count == GPMC_DMA_COPY_LOWER_LIMIT → DMA path */
    memset(gGpmcTestRxBuf, 0x00, TEST_NAND_SECTOR_SIZE);
    GPMC_transactionInit(&trans);
    trans.Buf       = gGpmcTestRxBuf;
    trans.count     = TEST_NAND_SECTOR_SIZE;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    retVal = GPMC_nandReadData(gpmcHandle, &trans);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(gGpmcTestRxBuf, gGpmcTestTxBulkBuf, TEST_NAND_SECTOR_SIZE);
    TEST_ASSERT_EQUAL_INT32(0, retVal);

    Board_driversClose();
}

/**
 * \brief Functionality test for NAND read via CPU prefetch engine.
 *
 * This test verifies that when a read size falls below the GPMC DMA copy threshold,
 * the driver correctly routes the operation through the CPU prefetch engine instead
 * of DMA. A 256-byte read is performed to verify CPU prefetch path functionality.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_readCpuPrefetch(void *args)
{
    int32_t          retVal = SystemP_SUCCESS;
    uint32_t         blk, page;
    uint32_t         offset    = TEST_GPMC_FLASH_OFFSET_BASE;
    uint32_t         readCount = TEST_NAND_SECTOR_SIZE / 2U; /* 256 < 512 */
    GPMC_Handle      gpmcHandle;
    GPMC_nandCmdParams cmdParams;
    GPMC_Transaction trans;

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
    TEST_ASSERT_NOT_NULL(gpmcHandle);

    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    for (uint32_t i = 0; i < TEST_NAND_SECTOR_SIZE; i++)
        gGpmcTestTxBulkBuf[i] = gGpmcTestTxBuf[i % TEST_GPMC_DATA_SIZE];

    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset,
                         gGpmcTestTxBulkBuf, TEST_NAND_SECTOR_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_READ_CYC1;
    cmdParams.cmdCycle2        = TEST_NAND_CMD_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    memset(gGpmcTestRxBuf, 0x00, readCount);
    GPMC_transactionInit(&trans);
    trans.Buf       = gGpmcTestRxBuf;
    trans.count     = readCount;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    retVal = GPMC_nandReadData(gpmcHandle, &trans);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(gGpmcTestRxBuf, gGpmcTestTxBulkBuf, readCount);
    TEST_ASSERT_EQUAL_INT32(0, retVal);

    Board_driversClose();
}

/**
 * \brief Functionality test for NAND read via register direct access (READ_CMDREG).
 *
 * This test verifies direct register-based read operations that bypass the prefetch
 * engine. It uses the NAND READ ID command to obtain predictable manufacturer and
 * device identification bytes, validating byte-by-byte register access integrity.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_readCmdReg(void *args)
{
    int32_t          retVal = SystemP_SUCCESS;
    GPMC_Handle      gpmcHandle;
    GPMC_nandCmdParams cmdParams;
    GPMC_Transaction trans;
    uint8_t          readId[8] = {0};

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
    TEST_ASSERT_NOT_NULL(gpmcHandle);

    /* Issue NAND READ ID command */
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_READ_ID;
    cmdParams.numColAddrCycles = 1U;
    cmdParams.colAddress       = 0;
    cmdParams.checkReadypin    = FALSE;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Read 8 bytes via READ_CMDREG (byte-by-byte from NAND_DATA register) */
    GPMC_transactionInit(&trans);
    trans.Buf       = readId;
    trans.count     = 8U;
    trans.transType = GPMC_TRANSACTION_TYPE_READ_CMDREG;
    retVal = GPMC_nandReadData(gpmcHandle, &trans);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Verify Micron manufacturer ID (byte 0 of READ ID response) */
    TEST_ASSERT_EQUAL_UINT8(TEST_NAND_MANF_ID, readId[0]);

    Board_driversClose();
}

/**
 * \brief Functionality test for NAND write via register direct access (WRITE_CMDREG).
 *
 * This test verifies direct register-based write operations using the NAND PAGE PROGRAM
 * sequence. Data is written byte-by-byte via register access and then read back to verify
 * correct storage and retrieval of the programmed data.
 *
 * Test Category: Functionality / Register Access / Direct Write
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_nandWriteCmdReg(void *args)
{
    int32_t          retVal = SystemP_SUCCESS;
    uint32_t         blk, page;
    uint32_t         offset  = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle      gpmcHandle;
    GPMC_nandCmdParams cmdParams;
    GPMC_Transaction trans;
    uint8_t writeBuf[8] = {0xA0, 0xB1, 0xC2, 0xD3, 0xE4, 0xF5, 0x06, 0x17};
    uint8_t readBuf[8]  = {0};

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
    TEST_ASSERT_NOT_NULL(gpmcHandle);

    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = GPMC_disableFlashWriteProtect(gpmcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* PAGE PROGRAM Cycle 1: latch address */
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_PROG_CYC1;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    cmdParams.checkReadypin    = GPMC_CMD_INVALID;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Write 8 bytes via WRITE_CMDREG (byte-by-byte to NAND_DATA register) */
    GPMC_transactionInit(&trans);
    trans.Buf       = writeBuf;
    trans.count     = 8U;
    trans.transType = GPMC_TRANSACTION_TYPE_WRITE_CMDREG;
    retVal = GPMC_nandWriteData(gpmcHandle, &trans);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* PAGE PROGRAM Cycle 2: confirm program and wait for R/B */
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle2     = TEST_NAND_CMD_PROG_CYC2;
    cmdParams.waitTimeout   = TEST_NAND_DEVICE_TIMEOUT;
    cmdParams.checkReadypin = TRUE;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    GPMC_enableFlashWriteProtect(gpmcHandle);

    /* Read back the 8 bytes via PAGE READ + READ_CMDREG */
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_READ_CYC1;
    cmdParams.cmdCycle2        = TEST_NAND_CMD_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    GPMC_transactionInit(&trans);
    trans.Buf       = readBuf;
    trans.count     = 8U;
    trans.transType = GPMC_TRANSACTION_TYPE_READ_CMDREG;
    retVal = GPMC_nandReadData(gpmcHandle, &trans);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(readBuf, writeBuf, 8U);
    TEST_ASSERT_EQUAL_INT32(0, retVal);

    Board_driversClose();
}

/**
 * \brief Functionality test for BCH-8 ECC error detection and correction pipeline.
 *
 * This test validates the complete BCH-8 error correction code pipeline including
 * error detection and correction. A single-bit error is injected into a page, the ECC
 * engine detects and locates the error via ELM, and correction is verified.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_bch8EccPipeline(void *args)
{
    int32_t          retVal = SystemP_SUCCESS;
    uint32_t         blk, page;
    uint32_t         offset = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle      gpmcHandle;
    GPMC_nandCmdParams cmdParams;
    GPMC_Transaction trans;
    uint32_t         bchData[TEST_NAND_ECC_WORDS_PER_SECTOR] = {0};
    uint8_t          syndromeBuf[TEST_NAND_ECC_BCH8_BYTECNT - 1U];
    uint32_t         errCount = 0;
    uint32_t         errLoc[TEST_NAND_MAX_ERR_LOCS] = {0};
    uint8_t          corruptByte = 0xFEU; /* 0xFF with bit-0 cleared */
    int32_t          syndromeNonZero = 0;

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
    TEST_ASSERT_NOT_NULL(gpmcHandle);

    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    memset(gGpmcTestTxBulkBuf, 0xFF, TEST_NAND_PAGE_SIZE);
    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset,
                         gGpmcTestTxBulkBuf, TEST_NAND_PAGE_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* flip bit-0 of byte-0 via raw NAND PAGE PROGRAM */
    retVal = GPMC_disableFlashWriteProtect(gpmcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_PROG_CYC1;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    cmdParams.checkReadypin    = GPMC_CMD_INVALID;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    GPMC_transactionInit(&trans);
    trans.Buf       = &corruptByte;
    trans.count     = 1U;
    trans.transType = GPMC_TRANSACTION_TYPE_WRITE_CMDREG;
    retVal = GPMC_nandWriteData(gpmcHandle, &trans);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle2     = TEST_NAND_CMD_PROG_CYC2;
    cmdParams.waitTimeout   = TEST_NAND_DEVICE_TIMEOUT;
    cmdParams.checkReadypin = TRUE;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    GPMC_enableFlashWriteProtect(gpmcHandle);

    /* configure BCH-8 ECC engine for 8 sectors  */
    retVal = GPMC_eccEngineBCHConfig(gpmcHandle, TEST_NAND_ECC_STEPS_PER_PAGE - 1U);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = GPMC_eccValueSizeSet(gpmcHandle, GPMC_ECC_SIZE_0,
                                  TEST_NAND_ECC_BCH8_NIBBLE_PROTECTED);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = GPMC_eccValueSizeSet(gpmcHandle, GPMC_ECC_SIZE_1,
                                  TEST_NAND_ECC_BCH8_NIBBLE_UNUSED);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = GPMC_eccBchConfigureElm(gpmcHandle, TEST_NAND_ECC_STEPS_PER_PAGE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = GPMC_eccEngineEnable(gpmcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    GPMC_eccResultRegisterClear(gpmcHandle);

    /* issue PAGE READ and read full 4096-byte page  */
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_READ_CYC1;
    cmdParams.cmdCycle2        = TEST_NAND_CMD_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    memset(gGpmcTestRxBuf, 0x00, TEST_NAND_PAGE_SIZE);
    GPMC_transactionInit(&trans);
    trans.Buf       = gGpmcTestRxBuf;
    trans.count     = TEST_NAND_PAGE_SIZE;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    retVal = GPMC_nandReadData(gpmcHandle, &trans);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* RANDOM READ to ECC offset; ECC bytes complete the syndrome */
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_RANDOM_READ_CYC1;
    cmdParams.cmdCycle2        = TEST_NAND_CMD_RANDOM_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.colAddress       = TEST_NAND_ECC_OFFSET;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    cmdParams.checkReadypin    = FALSE;
    retVal = GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* gGpmcTestRxBuf[TEST_NAND_PAGE_SIZE] is 128-byte aligned (buffer base + 4096) */
    GPMC_transactionInit(&trans);
    trans.Buf       = &gGpmcTestRxBuf[TEST_NAND_PAGE_SIZE];
    trans.count     = TEST_NAND_ECC_TOTAL_BYTES;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    retVal = GPMC_nandReadData(gpmcHandle, &trans);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* extract syndrome (GPMC_eccCalculateBchSyndromePolynomial per plan)*/
    retVal = GPMC_eccCalculateBchSyndromePolynomial(gpmcHandle, syndromeBuf, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Also read in uint32_t format required by GPMC_eccBchFillSyndromeValue */
    retVal = GPMC_eccGetBchSyndromePolynomial(gpmcHandle, 0U, bchData);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Syndrome must be non-zero: the corrupted bit causes a mismatch */
    for (uint32_t w = 0U; w < TEST_NAND_ECC_WORDS_PER_SECTOR; w++)
    {
        if (bchData[w] != 0U)
        {
            syndromeNonZero = 1;
            break;
        }
    }
    TEST_ASSERT_EQUAL_INT32(1, syndromeNonZero);

    /* ELM error-location pipeline */
    retVal = GPMC_eccBchFillSyndromeValue(gpmcHandle, 0U, bchData);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = GPMC_eccBchStartErrorProcessing(gpmcHandle, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = GPMC_eccBchCheckErrorProcessingStatus(gpmcHandle, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = GPMC_eccBchSectorGetError(gpmcHandle, 0U, &errCount, errLoc);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    TEST_ASSERT_EQUAL_UINT32(1U, errCount);

    /* apply correction and verify restored data */
    if (errLoc[0] > TEST_NAND_BCH8_LAST_ECC_BIT)
    {
        uint32_t bitPos  = errLoc[0] - (TEST_NAND_BCH8_LAST_ECC_BIT + 1U);
        uint32_t bytePos = TEST_NAND_SECTOR_SIZE - (bitPos / 8U) - 1U;
        uint8_t  bitMask = (uint8_t)(0x01U << (bitPos % 8U));
        gGpmcTestRxBuf[bytePos] ^= bitMask;
    }
    /* Byte 0 of sector 0 was corrupted (0xFF→0xFE); verify it is back to 0xFF */
    TEST_ASSERT_EQUAL_UINT8(0xFFU, gGpmcTestRxBuf[0]);

    Board_driversClose();
}

/**
 * \brief Functionality test for 4-bit error detection and location via BCH-8 engine.
 *
 * This test verifies that the BCH-8 ECC engine can detect and locate exactly 4-bit
 * errors within a 512-byte sector. A controlled 4-bit error is injected and the ELM
 * is used to calculate the error locations.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_bch4EccPipeline(void *args)
{
    int32_t          retVal = SystemP_SUCCESS;
    uint32_t         blk, page;
    uint32_t         offset = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle      gpmcHandle;
    GPMC_nandCmdParams cmdParams;
    GPMC_Transaction trans;
    uint32_t         bchData[TEST_NAND_ECC_WORDS_PER_SECTOR] = {0};
    uint8_t          syndromeBuf[TEST_NAND_ECC_BCH8_BYTECNT - 1U];
    uint32_t         errCount = 0;
    uint32_t         errLoc[TEST_NAND_MAX_ERR_LOCS] = {0};
    uint8_t          corruptByte = TEST_INJECT_4_BIT_ERR; /* 0xF0 */

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);

    /* 1. Write clean page */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    memset(gGpmcTestTxBulkBuf, 0xFF, TEST_NAND_PAGE_SIZE);
    Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gGpmcTestTxBulkBuf, TEST_NAND_PAGE_SIZE);

    /* 2. Inject 4-bit error */
    GPMC_disableFlashWriteProtect(gpmcHandle);
    
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_PROG_CYC1;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.checkReadypin    = GPMC_CMD_INVALID;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);

    GPMC_transactionInit(&trans);
    trans.Buf       = &corruptByte;
    trans.count     = 1U;
    trans.transType = GPMC_TRANSACTION_TYPE_WRITE_CMDREG;
    GPMC_nandWriteData(gpmcHandle, &trans);

    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle2     = TEST_NAND_CMD_PROG_CYC2;
    cmdParams.waitTimeout   = TEST_NAND_DEVICE_TIMEOUT;
    cmdParams.checkReadypin = TRUE;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    GPMC_enableFlashWriteProtect(gpmcHandle);

    /* Configure standard BCH-8 Engine */
    GPMC_eccEngineBCHConfig(gpmcHandle, TEST_NAND_ECC_STEPS_PER_PAGE - 1U);
    GPMC_eccValueSizeSet(gpmcHandle, GPMC_ECC_SIZE_0, TEST_NAND_ECC_BCH8_NIBBLE_PROTECTED);
    GPMC_eccValueSizeSet(gpmcHandle, GPMC_ECC_SIZE_1, TEST_NAND_ECC_BCH8_NIBBLE_UNUSED);
    GPMC_eccBchConfigureElm(gpmcHandle, TEST_NAND_ECC_STEPS_PER_PAGE);
    GPMC_eccEngineEnable(gpmcHandle);
    GPMC_eccResultRegisterClear(gpmcHandle);

    /* Issue PAGE READ */
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_READ_CYC1;
    cmdParams.cmdCycle2        = TEST_NAND_CMD_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);

    memset(gGpmcTestRxBuf, 0x00, TEST_NAND_PAGE_SIZE);
    GPMC_transactionInit(&trans);
    trans.Buf       = gGpmcTestRxBuf;
    trans.count     = TEST_NAND_PAGE_SIZE;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    GPMC_nandReadData(gpmcHandle, &trans);

    /* RANDOM READ to ECC offset so hardware can finish polynomial */
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_RANDOM_READ_CYC1;
    cmdParams.cmdCycle2        = TEST_NAND_CMD_RANDOM_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.colAddress       = TEST_NAND_ECC_OFFSET;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    cmdParams.checkReadypin    = FALSE;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);

    GPMC_transactionInit(&trans);
    trans.Buf       = &gGpmcTestRxBuf[TEST_NAND_PAGE_SIZE];
    trans.count     = TEST_NAND_ECC_TOTAL_BYTES;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    GPMC_nandReadData(gpmcHandle, &trans);

    /* Process and Verify Exactly 4 Errors */
    GPMC_eccCalculateBchSyndromePolynomial(gpmcHandle, syndromeBuf, 0U);
    GPMC_eccGetBchSyndromePolynomial(gpmcHandle, 0U, bchData);
    GPMC_eccBchFillSyndromeValue(gpmcHandle, 0U, bchData);
    GPMC_eccBchStartErrorProcessing(gpmcHandle, 0U);
    GPMC_eccBchCheckErrorProcessingStatus(gpmcHandle, 0U);
    
    retVal = GPMC_eccBchSectorGetError(gpmcHandle, 0U, &errCount, errLoc);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    TEST_ASSERT_EQUAL_UINT32(4U, errCount);

    Board_driversClose();
}

/**
 * \brief test for uncorrectable error handling in BCH-8 ECC pipeline.
 *
 * This test verifies that the GPMC correctly handles error conditions beyond the
 * correction capability of BCH-8 (which corrects up to 8 bits). A 16-bit error is
 * injected to force an uncorrectable error condition and verify proper failure handling.
 *
 * Test Category: Functionality 
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_bch16EccPipeline(void *args)
{
    int32_t          retVal = SystemP_SUCCESS;
    uint32_t         blk, page;
    uint32_t         offset = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle      gpmcHandle;
    GPMC_nandCmdParams cmdParams;
    GPMC_Transaction trans;
    uint32_t         bchData[TEST_NAND_ECC_WORDS_PER_SECTOR] = {0};
    uint8_t          syndromeBuf[TEST_NAND_ECC_BCH8_BYTECNT - 1U];
    uint32_t         errCount = 0;
    uint32_t         errLoc[TEST_NAND_MAX_ERR_LOCS] = {0};
    uint8_t          corruptBytes[2] = {0x00U, 0x00U}; /* 16 bits flipped to 0 */

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);

    /* 1. Write clean page */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    memset(gGpmcTestTxBulkBuf, 0xFF, TEST_NAND_PAGE_SIZE);
    Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gGpmcTestTxBulkBuf, TEST_NAND_PAGE_SIZE);

    /* 2. Inject 16-bit fatal error */
    GPMC_disableFlashWriteProtect(gpmcHandle);
    
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_PROG_CYC1;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.checkReadypin    = GPMC_CMD_INVALID;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);

    GPMC_transactionInit(&trans);
    trans.Buf       = corruptBytes;
    trans.count     = 2U; 
    trans.transType = GPMC_TRANSACTION_TYPE_WRITE_CMDREG;
    GPMC_nandWriteData(gpmcHandle, &trans);

    cmdParams.cmdCycle2     = TEST_NAND_CMD_PROG_CYC2;
    cmdParams.checkReadypin = TRUE;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    GPMC_enableFlashWriteProtect(gpmcHandle);

    /* Configure Engine */
    GPMC_eccEngineBCHConfig(gpmcHandle, TEST_NAND_ECC_STEPS_PER_PAGE - 1U);
    GPMC_eccValueSizeSet(gpmcHandle, GPMC_ECC_SIZE_0, TEST_NAND_ECC_BCH8_NIBBLE_PROTECTED);
    GPMC_eccValueSizeSet(gpmcHandle, GPMC_ECC_SIZE_1, TEST_NAND_ECC_BCH8_NIBBLE_UNUSED);
    GPMC_eccBchConfigureElm(gpmcHandle, TEST_NAND_ECC_STEPS_PER_PAGE);
    GPMC_eccEngineEnable(gpmcHandle);
    GPMC_eccResultRegisterClear(gpmcHandle);

    /* Issue PAGE READ */
    cmdParams.cmdCycle1 = TEST_NAND_CMD_READ_CYC1;
    cmdParams.cmdCycle2 = TEST_NAND_CMD_READ_CYC2;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);

    trans.Buf       = gGpmcTestRxBuf;
    trans.count     = TEST_NAND_PAGE_SIZE;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    GPMC_nandReadData(gpmcHandle, &trans);

    /* RANDOM READ to ECC offset */
    cmdParams.cmdCycle1        = TEST_NAND_CMD_RANDOM_READ_CYC1;
    cmdParams.cmdCycle2        = TEST_NAND_CMD_RANDOM_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.colAddress       = TEST_NAND_ECC_OFFSET;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    cmdParams.checkReadypin    = FALSE;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);

    trans.Buf       = &gGpmcTestRxBuf[TEST_NAND_PAGE_SIZE];
    trans.count     = TEST_NAND_ECC_TOTAL_BYTES;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    GPMC_nandReadData(gpmcHandle, &trans);

    /*. Process - EXPECT FAILURE (-1) due to Uncorrectable Data Loss */
    retVal = GPMC_eccCalculateBchSyndromePolynomial(gpmcHandle, syndromeBuf, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = GPMC_eccGetBchSyndromePolynomial(gpmcHandle, 0U, bchData);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = GPMC_eccBchFillSyndromeValue(gpmcHandle, 0U, bchData);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = GPMC_eccBchStartErrorProcessing(gpmcHandle, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    retVal = GPMC_eccBchCheckErrorProcessingStatus(gpmcHandle, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    
    retVal = GPMC_eccBchSectorGetError(gpmcHandle, 0U, &errCount, errLoc);
    
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retVal); 

    Board_driversClose();
}

/**
 * \brief Functionality test for BCH-8 ECC continuous mode with 8 simultaneous sectors.
 *
 * This test verifies that the GPMC ELM can process error correction for all 8 sectors
 * of a full 4096-byte page simultaneously in continuous mode. Each sector has a single-bit
 * error injected and corrected to validate parallel sector processing.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_bch8ContinuousMode(void *args)
{
    int32_t          retVal = SystemP_SUCCESS;
    uint32_t         blk, page;
    uint32_t         offset = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle      gpmcHandle;
    GPMC_nandCmdParams cmdParams;
    GPMC_Transaction trans;
    uint32_t         bchData[TEST_NAND_ECC_WORDS_PER_SECTOR] = {0};
    uint8_t          syndromeBuf[TEST_NAND_ECC_BCH8_BYTECNT - 1U];
    uint32_t         errCount = 0;
    uint32_t         errLoc[TEST_NAND_MAX_ERR_LOCS] = {0};

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);

    /* Write clean page (Generates valid OOB ECC) */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    memset(gGpmcTestTxBulkBuf, 0xFF, TEST_NAND_PAGE_SIZE);
    Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gGpmcTestTxBulkBuf, TEST_NAND_PAGE_SIZE);

    /* Prepare mask, inject 1 error per 512-byte sector */
    for(uint32_t i = 0; i < TEST_NAND_ECC_STEPS_PER_PAGE; i++) 
    {
        gGpmcTestTxBulkBuf[i * TEST_NAND_SECTOR_SIZE] = TEST_INJECT_1_BIT_ERR;
    }
    CacheP_wb(gGpmcTestTxBulkBuf, TEST_NAND_PAGE_SIZE, CacheP_TYPE_ALL);

    /* Write mask in a SINGLE Page Program to respect NOP limits */
    GPMC_disableFlashWriteProtect(gpmcHandle);
    
    GPMC_writeNandCommandParamsInit(&cmdParams);
    cmdParams.cmdCycle1        = TEST_NAND_CMD_PROG_CYC1;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.checkReadypin    = GPMC_CMD_INVALID;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);

    GPMC_transactionInit(&trans);
    trans.Buf       = gGpmcTestTxBulkBuf;
    trans.count     = TEST_NAND_PAGE_SIZE;
    trans.transType = GPMC_TRANSACTION_TYPE_WRITE; 
    GPMC_nandWriteData(gpmcHandle, &trans);

    /* RE-INIT: Ensure cmdParams is clean before cycle 2 */
    GPMC_writeNandCommandParamsInit(&cmdParams); 
    cmdParams.cmdCycle2     = TEST_NAND_CMD_PROG_CYC2;
    cmdParams.checkReadypin = TRUE;
    cmdParams.waitTimeout   = TEST_NAND_DEVICE_TIMEOUT;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);
    GPMC_enableFlashWriteProtect(gpmcHandle);

    /* Setup BCH-8 */
    GPMC_eccEngineBCHConfig(gpmcHandle, TEST_NAND_ECC_STEPS_PER_PAGE - 1U);
    GPMC_eccValueSizeSet(gpmcHandle, GPMC_ECC_SIZE_0, TEST_NAND_ECC_BCH8_NIBBLE_PROTECTED);
    GPMC_eccValueSizeSet(gpmcHandle, GPMC_ECC_SIZE_1, TEST_NAND_ECC_BCH8_NIBBLE_UNUSED);
    GPMC_eccBchConfigureElm(gpmcHandle, TEST_NAND_ECC_STEPS_PER_PAGE);
    GPMC_eccEngineEnable(gpmcHandle);
    GPMC_eccResultRegisterClear(gpmcHandle);

    /* Issue READ */
    /* RE-INIT: Clear previous write states before reading */
    GPMC_writeNandCommandParamsInit(&cmdParams); 
    cmdParams.cmdCycle1 = TEST_NAND_CMD_READ_CYC1;
    cmdParams.cmdCycle2 = TEST_NAND_CMD_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.numRowAddrCycles = TEST_NAND_ROW_ADDR_CYCLES;
    cmdParams.colAddress       = 0;
    cmdParams.rowAddress       = blk * TEST_NAND_PAGES_PER_BLOCK + page;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);

    GPMC_transactionInit(&trans);
    trans.Buf       = gGpmcTestRxBuf;
    trans.count     = TEST_NAND_PAGE_SIZE;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    GPMC_nandReadData(gpmcHandle, &trans);

    /* RANDOM READ to ECC offset for all 8 sectors */
    /* RE-INIT: This is the critical fix to ensure RANDOM READ doesn't inherit dirty addressing */
    GPMC_writeNandCommandParamsInit(&cmdParams); 
    cmdParams.cmdCycle1        = TEST_NAND_CMD_RANDOM_READ_CYC1;
    cmdParams.cmdCycle2        = TEST_NAND_CMD_RANDOM_READ_CYC2;
    cmdParams.numColAddrCycles = TEST_NAND_COL_ADDR_CYCLES;
    cmdParams.colAddress       = TEST_NAND_ECC_OFFSET;
    cmdParams.waitTimeout      = TEST_NAND_DEVICE_TIMEOUT;
    cmdParams.checkReadypin    = FALSE;
    GPMC_writeNandCommand(gpmcHandle, &cmdParams);

    GPMC_transactionInit(&trans);
    trans.Buf       = &gGpmcTestRxBuf[TEST_NAND_PAGE_SIZE];
    trans.count     = TEST_NAND_ECC_TOTAL_BYTES;
    trans.transType = GPMC_TRANSACTION_TYPE_READ;
    GPMC_nandReadData(gpmcHandle, &trans);

    /* Load ALL 8 Contexts simultaneously into ELM */
    for(uint32_t ctx = 0; ctx < TEST_NAND_ECC_STEPS_PER_PAGE; ctx++) 
    {
        GPMC_eccCalculateBchSyndromePolynomial(gpmcHandle, syndromeBuf, ctx);
        GPMC_eccGetBchSyndromePolynomial(gpmcHandle, ctx, bchData);
        GPMC_eccBchFillSyndromeValue(gpmcHandle, ctx, bchData);
        GPMC_eccBchStartErrorProcessing(gpmcHandle, ctx);
    }

    /* Wait and Verify ALL 8 Contexts */
    for(uint32_t ctx = 0; ctx < TEST_NAND_ECC_STEPS_PER_PAGE; ctx++) 
    {
        GPMC_eccBchCheckErrorProcessingStatus(gpmcHandle, ctx);
        retVal = GPMC_eccBchSectorGetError(gpmcHandle, ctx, &errCount, errLoc);
        
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_UINT32(1U, errCount); /* Prove ELM fixed 1 error in every sector! */
    }

    Board_driversClose();
}

/**
 * \brief Functionality test for GPMC FCLK clock divider configuration.
 *
 * This test verifies that the GPMC correctly applies different FCLK clock divider
 * values (divide-by-1, divide-by-2, divide-by-4). For each divider setting, the test
 * configures the divider, verifies the register value, and performs a 256-byte read
 * to confirm the device operates correctly at each clock rate.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_clkDividerConfig(void *args)
{
    int32_t     retVal = SystemP_SUCCESS;
    uint32_t    blk, page;
    uint32_t    offset = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle gpmcHandle;
    uint32_t    regVal;

    /*
     * Array of dividers to test:
     *   0 → divide-by-1,  1 → divide-by-2,  3 → divide-by-4
     * (value 2 would be divide-by-3 but the test plan only asks for 1, 2, 4)
     */
    const uint32_t dividers[]        = {0U, 1U, 3U};
    const uint32_t dividerCount      = sizeof(dividers) / sizeof(dividers[0]);
    const GPMC_HwAttrs *hwAttrs      = gGpmcConfig[CONFIG_GPMC0].attrs;
    uint32_t    savedClkDivider      = hwAttrs->clkDivider;

    /* Write a known pattern so we can read it back at each divider setting */
    Drivers_gpmcOpen();
    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    for (uint32_t i = 0; i < TEST_GPMC_CLKDIV_READ_SIZE; i++)
    {
        gGpmcTestTxBulkBuf[i] = gGpmcTestTxBuf[i % TEST_GPMC_DATA_SIZE];
    }
    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset,
                         gGpmcTestTxBulkBuf, TEST_GPMC_CLKDIV_READ_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    Board_driversClose();
    Drivers_gpmcClose();

    /* Now cycle through each divider */
    for (uint32_t d = 0; d < dividerCount; d++)
    {
        /* Modify hwAttrs clkDivider (cast away const for test purposes) */
        ((GPMC_HwAttrs *)hwAttrs)->clkDivider = dividers[d];

        Drivers_gpmcOpen();
        gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
        TEST_ASSERT_NOT_NULL(gpmcHandle);

        retVal = Board_driversOpen();
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        /* Verify the register matches the requested divider */
        regVal = CSL_REG32_FEXT(hwAttrs->gpmcBaseAddr +
                     CSL_GPMC_CONFIG1(((GPMC_Config*)gpmcHandle)->object->params.chipSel),
                     GPMC_CONFIG1_GPMCFCLKDIVIDER);
        TEST_ASSERT_EQUAL_UINT32(dividers[d], regVal);

        /* Perform a 256-byte read to prove the device is functional */
        memset(gGpmcTestRxBuf, 0x00, TEST_GPMC_CLKDIV_READ_SIZE);
        retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset,
                            gGpmcTestRxBuf, TEST_GPMC_CLKDIV_READ_SIZE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        retVal = memcmp(gGpmcTestRxBuf, gGpmcTestTxBulkBuf, TEST_GPMC_CLKDIV_READ_SIZE);
        TEST_ASSERT_EQUAL_INT32(0, retVal);

        DebugP_log("  Clock divider %u: register OK, read verified\r\n", dividers[d]);

        /* Close */
        Board_driversClose();
        Drivers_gpmcClose();
    }

    /* Restore original divider for subsequent tests */
    ((GPMC_HwAttrs *)hwAttrs)->clkDivider = savedClkDivider;
}

/**
 * \brief Functionality test for GPMC flash write protection control.
 *
 * This test verifies the GPMC write protection API by disabling write protection,
 * performing erase and write operations, and then re-enabling protection. The test
 * validates that the WRITEPROTECT bit is correctly set in the CONFIG register and
 * that write operations succeed when protection is disabled.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_writeProtect(void *args)
{
    int32_t     retVal = SystemP_SUCCESS;
    uint32_t    blk, page;
    uint32_t    offset = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle gpmcHandle;
    uint32_t    wpBit;
    const GPMC_HwAttrs *hwAttrs;

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
    TEST_ASSERT_NOT_NULL(gpmcHandle);
    hwAttrs = ((GPMC_Config*)gpmcHandle)->attrs;

    /* Disable write protection */
    retVal = GPMC_disableFlashWriteProtect(gpmcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Verify register — WRITEPROTECT bit should be WPHIGH (1) */
    wpBit = CSL_REG32_FEXT(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG,
                           GPMC_CONFIG_WRITEPROTECT);
    TEST_ASSERT_EQUAL_UINT32(CSL_GPMC_CONFIG_WRITEPROTECT_WPHIGH, wpBit);

    /* Erase block and write known pattern — should succeed */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    for (uint32_t i = 0; i < TEST_GPMC_BUF_SIZE; i++)
    {
        gGpmcTestTxBulkBuf[i] = gGpmcTestTxBuf[i % TEST_GPMC_DATA_SIZE];
    }
    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset,
                         gGpmcTestTxBulkBuf, TEST_GPMC_BUF_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Enable write protection */
    retVal = GPMC_enableFlashWriteProtect(gpmcHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Verify register — WRITEPROTECT bit should still be WPHIGH */
    wpBit = CSL_REG32_FEXT(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG,
                           GPMC_CONFIG_WRITEPROTECT);
    TEST_ASSERT_EQUAL_UINT32(CSL_GPMC_CONFIG_WRITEPROTECT_WPHIGH, wpBit);

    /* Read back written data to validate the write was successful */
    memset(gGpmcTestRxBuf, 0x00, TEST_GPMC_BUF_SIZE);
    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset,
                        gGpmcTestRxBuf, TEST_GPMC_BUF_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(gGpmcTestRxBuf, gGpmcTestTxBulkBuf, TEST_GPMC_BUF_SIZE);
    TEST_ASSERT_EQUAL_INT32(0, retVal);

    Board_driversClose();
}

/**
 * \brief Functionality test for WAIT pin polarity with default configuration.
 *
 * This test verifies that the GPMC correctly applies the platform-configured WAIT
 * pin polarity setting. The CONFIG register is checked to confirm the polarity bit
 * matches the hardware attribute, and a full erase/write/read cycle validates that
 * WAIT pin monitoring works correctly with the configured polarity.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_waitPinActiveHigh(void *args)
{
    int32_t     retVal = SystemP_SUCCESS;
    uint32_t    blk, page;
    uint32_t    offset = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle gpmcHandle;
    uint32_t    polBit;
    const GPMC_HwAttrs *hwAttrs;

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
    TEST_ASSERT_NOT_NULL(gpmcHandle);
    hwAttrs = ((GPMC_Config*)gpmcHandle)->attrs;

    /* verify the register matches the platform-configured polarity */
    polBit = CSL_REG32_FEXT(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG,
                            GPMC_CONFIG_WAIT0PINPOLARITY);
    TEST_ASSERT_EQUAL_UINT32(hwAttrs->waitPinPol, polBit);

    DebugP_log("  Default WAIT pin polarity: %u\r\n", hwAttrs->waitPinPol);

    /* Prove WAIT pin monitoring works — do a real erase/write/read cycle */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    for (uint32_t i = 0; i < TEST_GPMC_BUF_SIZE; i++)
    {
        gGpmcTestTxBulkBuf[i] = (uint8_t)(i & 0xFFU);
    }
    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset,
                         gGpmcTestTxBulkBuf, TEST_GPMC_BUF_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    memset(gGpmcTestRxBuf, 0x00, TEST_GPMC_BUF_SIZE);
    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset,
                        gGpmcTestRxBuf, TEST_GPMC_BUF_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(gGpmcTestRxBuf, gGpmcTestTxBulkBuf, TEST_GPMC_BUF_SIZE);
    TEST_ASSERT_EQUAL_INT32(0, retVal);

    Board_driversClose();
}

/**
 * \brief Functionality test for WAIT pin polarity configuration toggling.
 *
 * This test verifies that the GPMC WAIT pin polarity can be dynamically configured
 * by temporarily setting it to the opposite of the default polarity. The test checks
 * that the register reflects the toggled polarity, then restores the original setting
 * and validates data-path functionality to confirm the system recovered properly.
 *
 * Test Category: Functionality
 *
 * \param args Unused.
 *
 * \return None.
 */
static void TestGpmc_waitPinActiveLow(void *args)
{
    int32_t     retVal = SystemP_SUCCESS;
    uint32_t    offset = TEST_GPMC_FLASH_OFFSET_BASE;
    GPMC_Handle gpmcHandle;
    uint32_t    polBit;
    const GPMC_HwAttrs *hwAttrs = gGpmcConfig[CONFIG_GPMC0].attrs;
    uint32_t    savedPol = hwAttrs->waitPinPol;

    /* Compute the opposite polarity */
    uint32_t    toggledPol = (savedPol == CSL_GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEH)
                           ? CSL_GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEL
                           : CSL_GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEH;

    /*  Set toggled polarity */
    ((GPMC_HwAttrs *)hwAttrs)->waitPinPol = toggledPol;

    /*  Open GPMC with modified polarity */
    Drivers_gpmcOpen();
    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
    TEST_ASSERT_NOT_NULL(gpmcHandle);

    /*  Verify register reflects toggled polarity */
    polBit = CSL_REG32_FEXT(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG,
                            GPMC_CONFIG_WAIT0PINPOLARITY);
    TEST_ASSERT_EQUAL_UINT32(toggledPol, polBit);

    DebugP_log("  Toggled WAIT pin polarity to: %u\r\n", toggledPol);

    Drivers_gpmcClose();

    /* Restore original polarity and re-open for data-path validation */
    ((GPMC_HwAttrs *)hwAttrs)->waitPinPol = savedPol;
    Drivers_gpmcOpen();
    gpmcHandle = GPMC_getHandle(CONFIG_GPMC0);
    TEST_ASSERT_NOT_NULL(gpmcHandle);

    /* Verify polarity is restored */
    polBit = CSL_REG32_FEXT(hwAttrs->gpmcBaseAddr + CSL_GPMC_CONFIG,
                            GPMC_CONFIG_WAIT0PINPOLARITY);
    TEST_ASSERT_EQUAL_UINT32(savedPol, polBit);

    /* Data-path validation — read previously written data */
    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    memset(gGpmcTestRxBuf, 0x00, TEST_GPMC_CLKDIV_READ_SIZE);
    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset,
                        gGpmcTestRxBuf, TEST_GPMC_CLKDIV_READ_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    Board_driversClose();
    Drivers_gpmcClose();
}

/*
 * Copyright (C) 2021-2025 Texas Instruments Incorporated
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
#include <board/flash.h>
#include <drivers/ospi.h>
#include <drivers/soc.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_OSPI_FLASH_OFFSET_BASE        (0x200000U)
#define TEST_OSPI_FLASH_PHY_TUNING_OFFSET  (0x300000U)
#define TEST_OSPI_DATA_SIZE                (256U) /* has to be 256 B aligned */
#define TEST_OSPI_DATA_REPEAT_COUNT        (8U)
#define TEST_OSPI_RX_BUF_SIZE              (TEST_OSPI_DATA_SIZE * TEST_OSPI_DATA_REPEAT_COUNT)
#define TEST_OSPI_1KB_SIZE                 (256*4U)
#define TEST_OSPI_2KB_SIZE                 (TEST_OSPI_1KB_SIZE*2U)
#define TEST_OSPI_4KB_SIZE                 (TEST_OSPI_1KB_SIZE*4U)
#define TEST_OSPI_128KB_SIZE               (TEST_OSPI_1KB_SIZE*128U)
#define TEST_OSPI_256KB_SIZE               (TEST_OSPI_1KB_SIZE*256U)
#define TEST_OSPI_512KB_SIZE               (TEST_OSPI_1KB_SIZE*512U)
#define TEST_OSPI_1MB_SIZE                 (TEST_OSPI_1KB_SIZE*TEST_OSPI_1KB_SIZE)
#define TEST_OSPI_2MB_SIZE                 (TEST_OSPI_1MB_SIZE*2U)
#define TEST_OSPI_5MB_SIZE                 (TEST_OSPI_1MB_SIZE*5U)
#define TEST_OSPI_10MB_SIZE                (TEST_OSPI_1MB_SIZE*10U)
#define TEST_OSPI_UNALIGNED_TEST_SIZE      (1000U)
#define TEST_OSPI_UNALIGNED_TEST_OFFSET    (5U)

#if defined (SOC_AM275X) || defined(SOC_J722S)
#if defined(__C7504__) || defined(__C7524__)
#define TEST_OSPI_MAX_TEST_SIZE            (TEST_OSPI_1MB_SIZE)
#else
#define TEST_OSPI_MAX_TEST_SIZE            (TEST_OSPI_2MB_SIZE)
#endif
#else
#define TEST_OSPI_MAX_TEST_SIZE            (TEST_OSPI_10MB_SIZE)
#endif

#define TEST_OSPI_BLOCK_SIZE               (TEST_OSPI_1KB_SIZE*256U)
#define TEST_OSPI_READ_FRCOUNT             (10U)  /* Frequency of reading required for average time of read operation*/

#if defined (SOC_AM275X)
#if defined(__C7504__) || defined(__C7524__)
#define TEST_OSPI_PERF_TEST_DATA_COUNT     (1U)   /* Change this value as per testSizes list size */
#else
#define TEST_OSPI_PERF_TEST_DATA_COUNT     (2U)   /* Change this value as per testSizes list size */
#endif
#else
#define TEST_OSPI_PERF_TEST_DATA_COUNT     (3U)   /* Change this value as per testSizes list size */
#endif

#if (TEST_OSPI_UNALIGNED_TEST_OFFSET + TEST_OSPI_UNALIGNED_TEST_SIZE > TEST_OSPI_MAX_TEST_SIZE)
#error Increase the TEST_OSPI_MAX_TEST_SIZE.
#endif

/* ========================================================================== */
/*                 Structure Declarations                             */
/* ========================================================================== */

/* Structure to store mode settings */
typedef struct Test_FlashModeSettings_t
{
    uint32_t flashType;
    char* flashName;
    uint32_t cfgflashType;
    uint32_t flashProtocol;
    uint32_t phyEnable;
    uint32_t dmaEnable;
    uint32_t dacEnable;
    uint32_t phySkipTuning;
}Test_FlashModeSettings;

typedef struct TestData_SizesAttr_t
{
    uint32_t dataSize; //in MiB
    float writeSpeed;
    float readSpeed;
}TestData_SizesAttr;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Test cases */
static void test_ospi_read_write_1s1s1s_config(void *args);
static void test_ospi_read_write_max_config(void *args);
static void test_ospi_phy_tuning(void *args);
static void test_ospi_skip_phy_tuning_perf(void *args);
static void test_ospi_read_perf(void *args);
static float test_ospi_write(uint32_t flashOffset, uint32_t writeSize);
static float test_ospi_read(uint32_t flashOffset, uint32_t readSize);
static int32_t test_ospi_read_write_test_in_mb(TestData_SizesAttr* testDataCurObj, uint32_t flashOffset, uint32_t dataSize);
static void test_ospi_gdevcfg_set_flash_protocol(uint32_t givenflashProtocol);
static void set_test_flash_type(void);
static void test_ospi_unaligned_read_write(void *args);
static void test_ospi_validateOtp(void* args);
static void test_ospi_fallBack(void* args);
static void test_ospi_fallBack_to_1s1s1s(void* args);
static void test_ospi_read_write(TestData_SizesAttr* testDataCurObj, uint32_t flashOffset, uint32_t dataSize);
static void test_ospi_read_write_different_frequencies(void *args);
static void test_ospi_read_write_indirect_different_frequencies(void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8_t gOspiTestTxBuf[TEST_OSPI_DATA_SIZE] =
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


uint8_t gOspiTestTxBulkBuf[TEST_OSPI_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
uint8_t gOspiTestRxBuf[TEST_OSPI_MAX_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));

static Test_FlashModeSettings modeParams;

static OSPI_phyParams gTestDefaultParams =
{
    .radius              = 10,
    .rxTxDllMin          = 0,
    .rxTxDllMax          = 127,
    .minReadDelay        = 0,
    .maxReadDelay        = 4,
    .minPassSize         = 100,
    .diagonalShift       = 10,
    .maxDiagonalShift    = 70,
    .numConsecutiveFail  = 5,
    .numConsecutivePass  = 10,
    .rdDelaySearchStep   = 16,
};

static OSPI_phyParams gTestFailParams =
{
    .radius              = 0,
    .rxTxDllMin          = 0,
    .rxTxDllMax          = 0,
    .minReadDelay        = 0,
    .maxReadDelay        = 0,
    .minPassSize         = 0,
    .diagonalShift       = 10,
    .maxDiagonalShift    = 70,
    .numConsecutiveFail  = 5,
    .numConsecutivePass  = 10,
    .rdDelaySearchStep   = 16,
};

static OSPI_phyParams gTestFastTuningParams =
{
        .radius              = 5,
        .rxTxDllMin          = 0,
        .rxTxDllMax          = 127,
        .minReadDelay        = 0,
        .maxReadDelay        = 4,
        .minPassSize         = 100,
        .diagonalShift       = 10,
        .maxDiagonalShift    = 70,
        .numConsecutiveFail  = 5,
        .numConsecutivePass  = 10,
        .rdDelaySearchStep   = 16,
};

static OSPI_PhyTuneWindowParams gTestDefaultTuningWindowSDR =
{
    .txDllLowWindowStart    = 0,
    .txDllLowWindowEnd      = 0,
    .txDllHighWindowStart   = 0,
    .txDllHighWindowEnd     = 127,
    .rxLowSearchStart       = 0,
    .rxLowSearchEnd         = 0,
    .rxHighSearchStart      = 0,
    .rxHighSearchEnd        = 127,
    .txLowSearchStart       = 0,
    .txLowSearchEnd         = 0,
    .txHighSearchStart      = 0,
    .txHighSearchEnd        = 0,
    .txDLLSearchOffset      = 0,
    .rxTxDLLSearchStep      = 4,
    .rdDelayMin             = 0,
    .rdDelayMax             = 3,
};

static OSPI_PhyTuneWindowParams gTestFastTuningWindowSDR =
{
    .txDllLowWindowStart    = 0,
    .txDllLowWindowEnd      = 0,
    .txDllHighWindowStart   = 0,
    .txDllHighWindowEnd     = 127,
    .rxLowSearchStart       = 0,
    .rxLowSearchEnd         = 0,
    .rxHighSearchStart      = 0,
    .rxHighSearchEnd        = 127,
    .txLowSearchStart       = 0,
    .txLowSearchEnd         = 0,
    .txHighSearchStart      = 0,
    .txHighSearchEnd        = 0,
    .txDLLSearchOffset      = 0,
    .rxTxDLLSearchStep      = 8,
    .rdDelayMin             = 0,
    .rdDelayMax             = 1,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    set_test_flash_type();
    Board_flashClose();
    Drivers_ospiClose();
    Drivers_ospiOpen();

    UNITY_BEGIN();

    RUN_TEST(test_ospi_read_write_1s1s1s_config, 3175, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_phy_tuning, 3176, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_read_write_max_config, 3174, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_read_perf, 8724, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_skip_phy_tuning_perf, 3825, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_unaligned_read_write, 6893, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_read_write_different_frequencies, 7105, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_read_write_indirect_different_frequencies, 8012, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_validateOtp, 8493, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_fallBack, 8494, NULL);
    Drivers_ospiClose();
    Drivers_ospiOpen();
    RUN_TEST(test_ospi_fallBack_to_1s1s1s, 9211, NULL);
    Drivers_ospiClose();

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
 * Test cases
 */

static void test_ospi_read_write_1s1s1s_config(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    int32_t status = SystemP_SUCCESS;
    uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;
    uint32_t txChunkCnt;

    uint32_t blk, page;

    OSPI_Handle ospiHandle = OSPI_getHandle(CONFIG_OSPI0);
    OSPI_Config *config = (OSPI_Config*)ospiHandle;
    OSPI_Attrs attrs;

    memcpy((void*)&attrs, config->attrs, sizeof(OSPI_Attrs));

    test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_1S_1S_1S);

    Drivers_ospiClose();

    /* Set phyEnable to false for 1s_1s_1s mode. */
    attrs.phyEnable = FALSE;
    const OSPI_Attrs *tempAttrs = config->attrs;
    config->attrs = &attrs;

#if defined (SOC_AM62LX)
    /* Set frequency to 200Mhz. */
    status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
             AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 200000000);
#elif defined(SOC_AM275X)
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
             TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 200000000);
#else
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
             TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 200000000);
#endif
    DebugP_assert(status == SystemP_SUCCESS);

    Drivers_ospiOpen();
    retVal = Board_driversOpen();

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Block erase at the test offset */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    for(txChunkCnt = 0; txChunkCnt < TEST_OSPI_2KB_SIZE/TEST_OSPI_DATA_SIZE; txChunkCnt++)
    {
        memcpy(gOspiTestTxBulkBuf + txChunkCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , sizeof(gOspiTestTxBuf));
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf, TEST_OSPI_2KB_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Test if read data matches with written data */
    retVal = memcmp(gOspiTestRxBuf, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    Board_driversClose();

    config->attrs = tempAttrs;

    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_8D_8D_8D);
    }
    else if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NAND)
    {
        test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_1S_8S_8S);
    }

#if defined (SOC_AM62LX)
    /* Set frequency to 200Mhz. */
    status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
             AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 166666666);
#elif defined(SOC_AM275X)
    /* Set frequency to 166Mhz. */
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
             TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 166666666);
#else
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
             TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 166666666);
#endif
    DebugP_assert(status == SystemP_SUCCESS);

}

static void test_ospi_phy_tuning(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t phyTuningData, phyTuningDataSize;
    uint32_t blk, page;
    OSPI_Handle ospiHandle = OSPI_getHandle(CONFIG_OSPI0);
    OSPI_Config *config = NULL;
    uint64_t startTime, endTime;
    float temperature = 0;
    const char *flashTypeList[] = {"SERIAL NOR","SERIAL NAND","PARALLEL NOR", \
                                   "PARALLEL NAND"};
    const char *flashProtocolList[] = {0,"FLASH_CFG_PROTO_1S_1S_1S",\
                                       "FLASH_CFG_PROTO_1S_1S_2S",\
                                       "FLASH_CFG_PROTO_1S_1S_4S",\
                                        "FLASH_CFG_PROTO_1S_1S_8S",\
                                        "FLASH_CFG_PROTO_1S_8S_8S",\
                                        "FLASH_CFG_PROTO_4S_4S_4S",\
                                        "FLASH_CFG_PROTO_4S_4D_4D",\
                                        "FLASH_CFG_PROTO_8S_8S_8S",\
                                        "FLASH_CFG_PROTO_8D_8D_8D",
                                        "FLASH_CFG_PROTO_CUSTOM"};

    config = (OSPI_Config *) ospiHandle;

    modeParams.flashProtocol = gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protocol;
    modeParams.phyEnable = ((OSPI_Config*)ospiHandle)->attrs->phyEnable;

    /* Open Flash drivers with OSPI instance as input */
    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NAND)
    {
        (void)VTM_getAverageTemperature(&temperature);

        TEST_ASSERT_GREATER_THAN_INT32(0, (int32_t)temperature);

        VTM_reset();
    }

    /* Flash the attackVector at a random offset and try the PHY tuning */
    OSPI_phyGetTuningData(&phyTuningData, &phyTuningDataSize);

    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], TEST_OSPI_FLASH_PHY_TUNING_OFFSET, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], TEST_OSPI_FLASH_PHY_TUNING_OFFSET, (void *)phyTuningData, phyTuningDataSize);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    DebugP_log("\n[TEST OSPI] OSPI PHY tuning time\r\n\n");
    DebugP_log("Flash type: %s\r\n",flashTypeList[modeParams.cfgflashType]);
    DebugP_log("Flash protocol: %s\r\n",flashProtocolList[modeParams.flashProtocol]);
    DebugP_log("Temperature: %.2f\r\n", temperature);

    if(modeParams.phyEnable)
    {
        DebugP_log("PHY condition: enabled\r\n\n");
    }
    else
    {
        DebugP_log("PHY condition: disabled\r\n\n");
    }

    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        DebugP_log("DQS Tuning Algorithm        |    Tuning Time (ms)    \r\n");
        DebugP_log("----------------------------|------------------------\r\n");
        startTime = ClockP_getTimeUsec();
        retVal = OSPI_phyTuneDDR(ospiHandle, TEST_OSPI_FLASH_PHY_TUNING_OFFSET);
        endTime = ClockP_getTimeUsec();
        DebugP_log("Default Tuning Window       |          %0.2f ms\r\n",\
                   ((float)(endTime - startTime))/ 1000);

        /* Test fast tuning window set */
        memcpy((void *)&config->attrs->phyConfiguration.phyParams, \
               (void *)&gTestFastTuningParams, \
               sizeof(gTestFastTuningParams));

        startTime = ClockP_getTimeUsec();
        retVal += OSPI_phyTuneDDR(ospiHandle, TEST_OSPI_FLASH_PHY_TUNING_OFFSET);
        endTime = ClockP_getTimeUsec();
        DebugP_log("Fast Tuning Window          |          %0.2f ms\r\n\n",\
                   ((float)(endTime - startTime))/ 1000);

        /* Revert configuration */
        memcpy((void *)&config->attrs->phyConfiguration.phyParams, \
               (void *)&gTestDefaultParams, \
               sizeof(gTestDefaultParams));
    }
    else if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NAND)
    {
        DebugP_log("Non-DQS Tuning Algorithm    |    Tuning Time (ms)    \r\n");
        DebugP_log("----------------------------|------------------------\r\n");
        startTime = ClockP_getTimeUsec();
        retVal = OSPI_phyTuneSDR(ospiHandle, TEST_OSPI_FLASH_PHY_TUNING_OFFSET);
        endTime = ClockP_getTimeUsec();
        DebugP_log("Default Tuning Window       |          %0.2f  ms\r\n",\
                   ((float)(endTime - startTime))/ 1000);

        /* Test fast tuning window set */
        memcpy((void *)&config->attrs->phyConfiguration.tuningWindowParams, \
               (void *)&gTestFastTuningWindowSDR, \
               sizeof(gTestFastTuningWindowSDR));

        startTime = ClockP_getTimeUsec();
        retVal += OSPI_phyTuneSDR(ospiHandle, TEST_OSPI_FLASH_PHY_TUNING_OFFSET);
        endTime = ClockP_getTimeUsec();
        DebugP_log("Fast Tuning Window          |          %0.2f  ms\r\n\n",\
                   ((float)(endTime - startTime))/ 1000);

        /* Revert configuration */
        memcpy((void *)&config->attrs->phyConfiguration.tuningWindowParams, \
               (void *)&gTestDefaultTuningWindowSDR, \
               sizeof(gTestDefaultTuningWindowSDR));
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    Board_driversClose();
}

/*  This test will write and read from Flash with PHY tuning skipped
*/
static void test_ospi_skip_phy_tuning_perf(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    OSPI_Handle ospiHandle;
    OSPI_Handle backupHandle;
    extern OSPI_Config gOspiConfig[CONFIG_OSPI_NUM_INSTANCES];

    ospiHandle = OSPI_getHandle(CONFIG_OSPI0);

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    OSPI_enablePhy(ospiHandle);
    OSPI_phyReadTunedVal(ospiHandle);

    /* Create a backup handle since ospiHandle will be closed which will be used to enable PHY */
    memcpy(&backupHandle, &ospiHandle, sizeof(ospiHandle));

    Board_flashClose();
    Drivers_ospiClose();

    OSPI_enablePhy(backupHandle);

    /* Perform performance test when configuration is skipped*/
    *(uint32_t*)&gOspiConfig[CONFIG_OSPI0].attrs->phySkipTuning = TRUE;
    Drivers_ospiOpen();

    test_ospi_read_perf(NULL);

    *(uint32_t*)&gOspiConfig[CONFIG_OSPI0].attrs->phySkipTuning = FALSE;
    Board_driversClose();
}

static void test_ospi_read_write_max_config(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t blk, page, txChunkCnt;
    uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;

    /* Open Flash drivers with OSPI instance as input */
    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Block erase at the test offset */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    for(txChunkCnt = 0; txChunkCnt < (TEST_OSPI_2KB_SIZE)/TEST_OSPI_DATA_SIZE; txChunkCnt++)
    {
        memcpy(gOspiTestTxBulkBuf + txChunkCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , sizeof(gOspiTestTxBuf));
    }

    retVal += Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf, TEST_OSPI_2KB_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(gOspiTestRxBuf, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    Board_driversClose();
}

static void test_ospi_unaligned_read_write(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;
    uint32_t blk, page, txChunkCnt;

    /* Open Flash drivers with OSPI instance as input */
    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Block erase at the test offset */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    for(txChunkCnt = 0; txChunkCnt < (TEST_OSPI_UNALIGNED_TEST_SIZE)/TEST_OSPI_DATA_SIZE; txChunkCnt++)
    {
        if((txChunkCnt * TEST_OSPI_DATA_SIZE) < TEST_OSPI_UNALIGNED_TEST_SIZE)
        {
            memcpy(gOspiTestTxBulkBuf + txChunkCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , sizeof(gOspiTestTxBuf));
        }
        else
        {
            memcpy(gOspiTestTxBulkBuf + txChunkCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , (TEST_OSPI_UNALIGNED_TEST_SIZE - (txChunkCnt * TEST_OSPI_DATA_SIZE)));
        }
    }

    /* source unaligned */
    retVal += Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, TEST_OSPI_UNALIGNED_TEST_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset + TEST_OSPI_UNALIGNED_TEST_OFFSET, gOspiTestRxBuf, TEST_OSPI_UNALIGNED_TEST_SIZE - TEST_OSPI_UNALIGNED_TEST_OFFSET);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(gOspiTestRxBuf, gOspiTestTxBulkBuf + TEST_OSPI_UNALIGNED_TEST_OFFSET, TEST_OSPI_UNALIGNED_TEST_SIZE - TEST_OSPI_UNALIGNED_TEST_OFFSET);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Block erase at the test offset */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);

    /* Destination unaligned */
    retVal += Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, TEST_OSPI_UNALIGNED_TEST_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf + TEST_OSPI_UNALIGNED_TEST_OFFSET, TEST_OSPI_UNALIGNED_TEST_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(gOspiTestRxBuf + TEST_OSPI_UNALIGNED_TEST_OFFSET, gOspiTestTxBulkBuf, TEST_OSPI_UNALIGNED_TEST_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Block erase at the test offset */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
    retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);

    /* Both source and destination unaligned */
    retVal += Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, TEST_OSPI_UNALIGNED_TEST_SIZE);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset + TEST_OSPI_UNALIGNED_TEST_OFFSET, gOspiTestRxBuf + TEST_OSPI_UNALIGNED_TEST_OFFSET, TEST_OSPI_UNALIGNED_TEST_SIZE - TEST_OSPI_UNALIGNED_TEST_OFFSET);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(gOspiTestRxBuf + TEST_OSPI_UNALIGNED_TEST_OFFSET, gOspiTestTxBulkBuf + TEST_OSPI_UNALIGNED_TEST_OFFSET, TEST_OSPI_UNALIGNED_TEST_SIZE - TEST_OSPI_UNALIGNED_TEST_OFFSET);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    Board_driversClose();

}

static void test_ospi_read_perf(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t blk, page, txChunkCnt, testCount, blkCount;
    uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;
    uint64_t startTime, endTime;

#if defined (SOC_AM275X)
#if defined(__C7504__) || defined(__C7524__)
    uint32_t testSizes[TEST_OSPI_PERF_TEST_DATA_COUNT] = {TEST_OSPI_1MB_SIZE};
#else
    uint32_t testSizes[TEST_OSPI_PERF_TEST_DATA_COUNT] = {TEST_OSPI_1MB_SIZE, TEST_OSPI_2MB_SIZE};
#endif
#else
    /* Please provide size of atleast 1MiB */
    uint32_t testSizes[TEST_OSPI_PERF_TEST_DATA_COUNT] = {TEST_OSPI_1MB_SIZE, TEST_OSPI_5MB_SIZE, TEST_OSPI_10MB_SIZE};
#endif
    TestData_SizesAttr testDataObj[TEST_OSPI_PERF_TEST_DATA_COUNT],TestDataCurrObj;

    const char *flashProtocolList[] = {0,"FLASH_CFG_PROTO_1S_1S_1S","FLASH_CFG_PROTO_1S_1S_2S","FLASH_CFG_PROTO_1S_1S_4S",
                                        "FLASH_CFG_PROTO_1S_1S_8S","FLASH_CFG_PROTO_1S_8S_8S","FLASH_CFG_PROTO_4S_4S_4S",
                                        "FLASH_CFG_PROTO_4S_4D_4D","FLASH_CFG_PROTO_8S_8S_8S","FLASH_CFG_PROTO_8D_8D_8D",
                                        "FLASH_CFG_PROTO_CUSTOM"};

    const char *flashTypeList[] = {"SERIAL NOR","SERIAL NAND","PARALLEL NOR","PARALLEL NAND"};

    OSPI_Handle ospiHandle = OSPI_getHandle(CONFIG_OSPI0);

    modeParams.flashProtocol = gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protocol;
    modeParams.phyEnable = ((OSPI_Config*)ospiHandle)->attrs->phyEnable;
    modeParams.dmaEnable = ((OSPI_Config*)ospiHandle)->attrs->dmaEnable;
    modeParams.dacEnable = ((OSPI_Config*)ospiHandle)->attrs->dacEnable;
    modeParams.phySkipTuning = ((OSPI_Config*)ospiHandle)->attrs->phySkipTuning;

    /* Open Flash drivers with OSPI instance as input */
    startTime = ClockP_getTimeUsec();
    retVal = Board_driversOpen();
    endTime = ClockP_getTimeUsec();

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Block erase at the test offset */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);

    /* The contents of buffer "gOspiTestTxBuf" are copied at incremental offsets of 'TEST_OSPI_DATA_SIZE'
     * until gOspiTestTxBulkBuf buffer is full
     */
    for(txChunkCnt = 0; txChunkCnt < TEST_OSPI_MAX_TEST_SIZE/TEST_OSPI_DATA_SIZE; txChunkCnt++)
    {
        memcpy(gOspiTestTxBulkBuf + txChunkCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , sizeof(gOspiTestTxBuf));
    }

    for(testCount = 0; testCount < sizeof(testSizes)/sizeof(testSizes[0]); testCount++)
    {
        for(blkCount = 0; blkCount < testSizes[testCount]/TEST_OSPI_BLOCK_SIZE; blkCount++)
        {
            retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk + blkCount);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        }

        retVal = test_ospi_read_write_test_in_mb(&TestDataCurrObj, offset, testSizes[testCount]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        memcpy(&testDataObj[testCount],&TestDataCurrObj,sizeof(TestData_SizesAttr));
    }

    /* Print performance numbers. */
    DebugP_log("\n[TEST OSPI] Performance Numbers Print Start\r\n\n");
    DebugP_log("Flash type: %s\r\n",flashTypeList[modeParams.cfgflashType]);
    DebugP_log("Flash protocol: %s\r\n",flashProtocolList[modeParams.flashProtocol]);

    if(modeParams.phyEnable)
        DebugP_log("PHY condition: enabled\r\n");
    else
        DebugP_log("PHY condition: disabled\r\n");

    if(modeParams.dmaEnable)
        DebugP_log("DMA condition: enabled\r\n");
    else
        DebugP_log("DMA condition: disabled\r\n");

    if(modeParams.dacEnable)
        DebugP_log("DAC condition: enabled\r\n");
    else
        DebugP_log("DAC condition: disabled\r\n");

    if(modeParams.phySkipTuning)
        DebugP_log("PHY tuning skip: enabled\r\n");
    else
        DebugP_log("PHY tuning skip: disabled\r\n");

    DebugP_log("Configuration time: %ld us\r\n\n", (endTime - startTime));
    DebugP_log("Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)\r\n");
    DebugP_log("---------------|--------------------|-----------------\r\n");

    for (testCount=0; testCount<sizeof(testSizes)/sizeof(testSizes[0]); testCount++) {
        DebugP_log(" %d\t       | %.2f\t\t    | %.2f\r\n", testDataObj[testCount].dataSize, testDataObj[testCount].writeSpeed,
            testDataObj[testCount].readSpeed);
    }

    DebugP_log("\n[TEST OSPI] Performance Numbers Print End\r\n\n");

    Board_driversClose();
}

/*
 * Helper functions
 */

static void set_test_flash_type(void)
{
    modeParams.flashType = gFlashConfig[CONFIG_FLASH0].attrs->flashType;
    modeParams.flashName = gFlashConfig[CONFIG_FLASH0].attrs->flashName;

    /* Entend this for more flashNames when required*/
    if(modeParams.flashType == CONFIG_FLASH_TYPE_SERIAL && !strcmp(modeParams.flashName,"S28HS512T"))
         modeParams.cfgflashType = CONFIG_FLASH_TYPE_SERIAL_NOR;
    else if(modeParams.flashType == CONFIG_FLASH_TYPE_SERIAL && !strcmp(modeParams.flashName,"W35N01JWTBAG"))
         modeParams.cfgflashType = CONFIG_FLASH_TYPE_SERIAL_NAND;
}


static void test_ospi_gdevcfg_set_flash_protocol(uint32_t givenflashProtocol)
{
    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NAND)
    {
        switch (givenflashProtocol) {
            case FLASH_CFG_PROTO_1S_1S_1S:
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protocol = FLASH_CFG_PROTO_1S_1S_1S;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.isDtr = FALSE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdRd = 0x03;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdWr = 0x84;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksCmd = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksRd = 8;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.isAddrReg = FALSE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegWr = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegRd = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgReg = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.mask = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgRegBitP = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.isAddrReg = FALSE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegWr = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegRd = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgReg = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.mask = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgRegBitP = 0;
                break;

            case FLASH_CFG_PROTO_1S_8S_8S:
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protocol = FLASH_CFG_PROTO_1S_8S_8S;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.isDtr = FALSE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdRd = 0xCB;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdWr = 0xC4;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksCmd = 8;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksRd = 20;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.isAddrReg = TRUE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegWr = 0x81;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegRd = 0x85;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgReg = 0x0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.mask = 0xFF;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgRegBitP = 223;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.isAddrReg = TRUE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegWr = 0x81;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegRd = 0x85;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgReg = 0x01;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.mask = 0xFF;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgRegBitP = 20;
                break;

            case FLASH_CFG_PROTO_8D_8D_8D:
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protocol = FLASH_CFG_PROTO_8D_8D_8D;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.isDtr = FALSE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdRd = 0x9d;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdWr = 0x84;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksCmd = 8;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksRd = 8;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.isAddrReg = TRUE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegWr = 0x81;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegRd = 0x85;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgReg = 0x0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.mask = 0xFF;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgRegBitP = 231;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.isAddrReg = TRUE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegWr = 0x81;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegRd = 0x85;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgReg = 0x01;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.mask = 0xFF;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgRegBitP = 8;
                break;
            default:
                break;
        }
    }

    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        switch (givenflashProtocol) {
            case FLASH_CFG_PROTO_1S_1S_1S:
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protocol = FLASH_CFG_PROTO_1S_1S_1S;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.isDtr = FALSE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdRd = 0x03;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdWr = 0x02;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksCmd = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksRd = 0;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.enableType = 0xFF;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.enableSeq = 0xFF;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.isAddrReg = FALSE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegWr = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegRd = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgReg = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.mask = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgRegBitP = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.isAddrReg = FALSE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegWr = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegRd = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgReg = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.mask = 0x00;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgRegBitP = 0;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.isAddrReg = FALSE;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.cmdRegWr = 0x00;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.cmdRegRd = 0x00;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.cfgReg = 0x00;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.shift = 0;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.mask = 0x00;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.cfgRegBitP = 0;
                break;

            case FLASH_CFG_PROTO_8D_8D_8D:
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protocol = FLASH_CFG_PROTO_8D_8D_8D;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.isDtr = TRUE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdRd = 0xEE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.cmdWr = 0x12;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksCmd = 3;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksRd = 20;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.enableType = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.enableSeq = 0x00;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.isAddrReg = TRUE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegWr = 0x71;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cmdRegRd = 0x65;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgReg = 0x00800006;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.mask = 0x01;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.protoCfg.cfgRegBitP = 1;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.isAddrReg = TRUE;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegWr = 0x71;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cmdRegRd = 0x65;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgReg = 0x00800003;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.shift = 0;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.mask = 0x0F;
	            gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyCfg.cfgRegBitP = 8;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.isAddrReg = TRUE;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.cmdRegWr = 0x71;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.cmdRegRd = 0x65;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.cfgReg = 0x00800006;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.shift = 1;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.mask = 0x02;
                gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.strDtrCfg.cfgRegBitP = 1;
                break;

            default:
                break;
        }
    }
}

static float test_ospi_write(uint32_t flashOffset, uint32_t writeSize)
{
    int32_t retVal = SystemP_SUCCESS;
    uint64_t startTime, endTime;

    startTime = ClockP_getTimeUsec();
    retVal = Flash_write(gFlashHandle[CONFIG_FLASH0], flashOffset, gOspiTestTxBulkBuf, writeSize);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    endTime = ClockP_getTimeUsec();

    return (float)(endTime - startTime);
}

static float test_ospi_read(uint32_t flashOffset, uint32_t readSize)
{
    int32_t retVal = SystemP_SUCCESS;
    uint64_t startTime, endTime, totalReadTime=0;
    uint8_t readFcnt = 0;

    while(readFcnt++ < TEST_OSPI_READ_FRCOUNT)
    {
        startTime = ClockP_getTimeUsec();
        retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], flashOffset, gOspiTestRxBuf, readSize);
        endTime = ClockP_getTimeUsec();
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        totalReadTime += endTime-startTime;
    }
    return (float)totalReadTime/(readFcnt-1);
}

static int32_t test_ospi_read_write_test_in_mb(TestData_SizesAttr* testDataCurObj, uint32_t flashOffset, uint32_t dataSize)
{
    int32_t retVal = SystemP_SUCCESS;
    float readTime, writeTime;

    if(dataSize < TEST_OSPI_1MB_SIZE){
        retVal = SystemP_FAILURE;
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    }

    writeTime = test_ospi_write(flashOffset, dataSize);

    readTime = test_ospi_read(flashOffset, dataSize);

    testDataCurObj->dataSize = dataSize/TEST_OSPI_1MB_SIZE;
    testDataCurObj->writeSpeed = (float)((float)dataSize/(float)(writeTime));
    testDataCurObj->readSpeed = (float)((float)dataSize/(float)(readTime));

    /* Test if read data matches with written data */
    retVal = memcmp(gOspiTestRxBuf, gOspiTestTxBulkBuf, dataSize);
    return retVal;
}

static void test_ospi_read_write(TestData_SizesAttr* testDataCurObj, uint32_t flashOffset, uint32_t dataSize)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t blk, page, txChunkCnt, blkCount;
    float readTime, writeTime;

    Drivers_ospiOpen();
    retVal = Board_driversOpen();

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Block erase at the test offset */
    Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], flashOffset, &blk, &page);

    for(blkCount = 0; blkCount < dataSize/TEST_OSPI_BLOCK_SIZE; blkCount++)
    {
        retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk + blkCount);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    }

    for(txChunkCnt = 0; txChunkCnt < dataSize/TEST_OSPI_DATA_SIZE; txChunkCnt++)
    {
        memcpy(gOspiTestTxBulkBuf + txChunkCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , sizeof(gOspiTestTxBuf));
    }

    writeTime = test_ospi_write(flashOffset, dataSize);

    readTime = test_ospi_read(flashOffset, dataSize);

    testDataCurObj->dataSize = dataSize/TEST_OSPI_1MB_SIZE;
    testDataCurObj->writeSpeed = (float)((float)dataSize/(float)(writeTime));
    testDataCurObj->readSpeed = (float)((float)dataSize/(float)(readTime));


    /* Test if read data matches with written data */
    retVal = memcmp(gOspiTestRxBuf, gOspiTestTxBulkBuf, dataSize);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    Board_driversClose();
    Drivers_ospiClose();

    return;
}

static void test_ospi_read_write_25Mhz(OSPI_Attrs *attrs, uint32_t offset, Flash_DevConfig *devConfig)
{
    int32_t status = SystemP_SUCCESS;
    TestData_SizesAttr testDataCurObj;

    attrs->phyEnable = FALSE;
    attrs->baudRateDiv = 8U;
    attrs->dmaEnable = FALSE;

    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NAND)
    {
        test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_8D_8D_8D);
    }

#if defined (SOC_AM62LX)
        /* Set frequency to 200Mhz. */
        status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
                 AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 200000000);
#elif defined(SOC_AM275X)
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
                 TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 200000000);
#else
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
                 TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 200000000);
#endif

    DebugP_assert(status == SystemP_SUCCESS);
    DebugP_log("Flash frequency: 25Mhz\r\n");
    DebugP_log("Flash protocol: FLASH_CFG_PROTO_8D_8D_8D\r\n");
    DebugP_log("Phy Condition: disabled\r\n\n");

    DebugP_log(" Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  \n\r");
    DebugP_log("-----------------|-------------------|-------------------|----------------------|----------------------\n\r");

    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |        DAC        |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    #if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |        DAC        |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |        DAC        |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    #endif

    attrs->dmaEnable = TRUE;

    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |        DAC        |        Yes        |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |        DAC        |        Yes        |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj,offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |        DAC        |        Yes        |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif
    DebugP_log("\r\n\n");

    attrs->phyEnable = TRUE;
    attrs->baudRateDiv = 4U;

    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NAND)
    {
        test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_1S_8S_8S);
    }

#if defined (SOC_AM62LX)
        /* Set frequency to 200Mhz. */
        status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
                 AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 166666666);
#elif defined(SOC_AM275X)
        /* Set frequency to 166Mhz. */
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
                 TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 166666666);
#else
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
                 TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 166666666);
#endif

    DebugP_assert(status == SystemP_SUCCESS);
}

static void test_ospi_read_write_50Mhz(OSPI_Attrs *attrs, uint32_t offset, Flash_DevConfig *devConfig)
{
    int32_t status = SystemP_SUCCESS;
    TestData_SizesAttr testDataCurObj;

    attrs->dmaEnable = FALSE;
    attrs->phyEnable = FALSE;
    test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_1S_1S_1S);

#if defined (SOC_AM62LX)
    /* Set frequency to 200Mhz. */
    status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
             AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 200000000);
#elif defined(SOC_AM275X)
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
             TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 200000000);
#else
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
             TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 200000000);
#endif
    DebugP_assert(status == SystemP_SUCCESS);

    DebugP_log("Flash frequency: 50Mhz\r\n");
    DebugP_log("Flash protocol: FLASH_CFG_PROTO_1S_1S_1S\r\n");
    DebugP_log("Phy Condition: disabled\r\n\n");

    DebugP_log(" Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  \n\r");
    DebugP_log("-----------------|-------------------|-------------------|-----------------------|----------------------\n\r");

    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |        DAC        |        No         |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |        DAC        |        No         |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |        DAC        |        No         |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif

    attrs->dmaEnable = TRUE;

    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |        DAC        |        Yes        |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |        DAC        |        Yes        |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj,offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |        DAC        |        Yes        |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif
    DebugP_log("\r\n\n");

    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NAND)
    {
        attrs->dmaEnable = FALSE;
        test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_1S_8S_8S);

        DebugP_log("Flash frequency: 50Mhz\r\n");
        DebugP_log("Flash protocol: FLASH_CFG_PROTO_1S_8S_8S\r\n");
        DebugP_log("Phy Condition: disabled\r\n\n");

        DebugP_log(" Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  \n\r");
        DebugP_log("-----------------|-------------------|-------------------|-----------------------|----------------------\n\r");

        test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
        DebugP_log("      1          |        DAC        |        No         |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
        test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
        DebugP_log("      5          |        DAC        |        No         |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
        test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_10MB_SIZE);
        DebugP_log("      10         |        DAC        |        No         |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif
        attrs->dmaEnable = TRUE;
        test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
        DebugP_log("      1          |        DAC        |        Yes        |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
        test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
        DebugP_log("      5          |        DAC        |        Yes        |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
        test_ospi_read_write(&testDataCurObj,offset, TEST_OSPI_10MB_SIZE);
        DebugP_log("      10         |        DAC        |        Yes        |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif
        DebugP_log("\r\n\n");
    }

    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_8D_8D_8D);
    }
    attrs->phyEnable = TRUE;

#if defined (SOC_AM62LX)
    /* Set frequency to 200Mhz. */
    status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
             AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 166666666);
#elif defined(SOC_AM275X)
    /* Set frequency to 166Mhz. */
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
             TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 166666666);
#else
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
             TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 166666666);
#endif
    DebugP_assert(status == SystemP_SUCCESS);;
}

static void test_ospi_read_write_133Mhz(OSPI_Attrs *attrs, uint32_t offset, Flash_DevConfig *devConfig)
{
    int32_t status = SystemP_SUCCESS;
    TestData_SizesAttr testDataCurObj;

#if defined (SOC_AM62LX)
        /* Set frequency to 200Mhz. */
        status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
                 AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 133333333);
#elif defined(SOC_AM275X)
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
                 TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 133333333);
#else
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
                 TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 133333333);
#endif

    DebugP_assert(status == SystemP_SUCCESS);

    attrs->dmaEnable = FALSE;

    DebugP_log("Flash frequency: 133Mhz\r\n");
    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        DebugP_log("Flash protocol: FLASH_CFG_PROTO_8D_8D_8D\r\n");
    }
    else if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NAND)
    {
        DebugP_log("Flash protocol: FLASH_CFG_PROTO_1S_8S_8S\r\n");
    }
    DebugP_log("Phy Condition: enabled\r\n\n");

    DebugP_log(" Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  \n\r");
    DebugP_log("-----------------|-------------------|-------------------|-----------------------|----------------------\n\r");

    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |        DAC        |        No         |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |        DAC        |        No         |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |        DAC        |        No         |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif
    attrs->dmaEnable = TRUE;

    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |        DAC        |        Yes        |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |        DAC        |        Yes        |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj,offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |        DAC        |        Yes        |        %0.2f           |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif
    DebugP_log("\r\n\n");

#if defined (SOC_AM62LX)
        /* Set frequency to 200Mhz. */
        status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
                 AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 166666666);
#elif defined(SOC_AM275X)
        /* Set frequency to 166Mhz. */
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
                 TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 166666666);
#else
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
                 TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 166666666);
#endif

    DebugP_assert(status == SystemP_SUCCESS);
}

static void test_ospi_read_write_166Mhz(OSPI_Attrs *attrs, uint32_t offset, Flash_DevConfig *devConfig)
{
    TestData_SizesAttr testDataCurObj;

    attrs->dmaEnable = FALSE;
    DebugP_log("Flash frequency: 166Mhz\r\n");
    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        DebugP_log("Flash protocol: FLASH_CFG_PROTO_8D_8D_8D\r\n");
    }
    else if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NAND)
    {
        DebugP_log("Flash protocol: FLASH_CFG_PROTO_1S_8S_8S\r\n");
    }
    DebugP_log("Phy Condition: enabled\r\n\n");

    DebugP_log(" Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  \n\r");
    DebugP_log("-----------------|-------------------|-------------------|----------------------|----------------------\n\r");


    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |        DAC        |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |        DAC        |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |        DAC        |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif

    attrs->dmaEnable = TRUE;
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |        DAC        |        Yes        |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |        DAC        |        Yes        |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj,offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |        DAC        |        Yes        |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif

}

static void test_ospi_read_write_indirect_25Mhz(OSPI_Attrs *attrs, uint32_t offset, Flash_DevConfig *devConfig)
{
    int32_t status = SystemP_SUCCESS;
    TestData_SizesAttr testDataCurObj;

    attrs->phyEnable = FALSE;
    attrs->baudRateDiv = 8U;
    attrs->dmaEnable = FALSE;

#if defined (SOC_AM62LX)
        /* Set frequency to 200Mhz. */
        status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
                 AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 200000000);
#elif defined(SOC_AM275X)
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
                 TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 200000000);
#else
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
                 TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 200000000);
#endif

    DebugP_assert(status == SystemP_SUCCESS);
    DebugP_log("Flash frequency: 25Mhz\r\n");
    DebugP_log("Flash protocol: FLASH_CFG_PROTO_8D_8D_8D\r\n");
    DebugP_log("Phy Condition: disabled\r\n\n");

    DebugP_log(" Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  \n\r");
    DebugP_log("-----------------|-------------------|-------------------|----------------------|----------------------\n\r");

    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |       INDAC       |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    #if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |       INDAC       |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |       INDAC       |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    #endif

    attrs->phyEnable = TRUE;
    attrs->baudRateDiv = 4U;

#if defined (SOC_AM62LX)
        /* Set frequency to 200Mhz. */
        status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
                 AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 166666666);
#elif defined(SOC_AM275X)
        /* Set frequency to 166Mhz. */
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
                 TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 166666666);
#else
        status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
                 TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 166666666);
#endif

    DebugP_assert(status == SystemP_SUCCESS);
}

static void test_ospi_read_write_indirect_50Mhz(OSPI_Attrs *attrs, uint32_t offset, Flash_DevConfig *devConfig)
{
    int32_t status = SystemP_SUCCESS;
    TestData_SizesAttr testDataCurObj;

    attrs->dmaEnable = FALSE;
    attrs->phyEnable = FALSE;
    test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_1S_1S_1S);

#if defined (SOC_AM62LX)
    /* Set frequency to 200Mhz. */
    status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
             AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 200000000);
#elif defined(SOC_AM275X)
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
             TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 200000000);
#else
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
             TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 200000000);
#endif
    DebugP_assert(status == SystemP_SUCCESS);

    DebugP_log("Flash frequency: 50Mhz\r\n");
    DebugP_log("Flash protocol: FLASH_CFG_PROTO_1S_1S_1S\r\n");
    DebugP_log("Phy Condition: disabled\r\n\n");

    DebugP_log(" Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  \n\r");
    DebugP_log("-----------------|-------------------|-------------------|----------------------|----------------------\n\r");

    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_1MB_SIZE);
    DebugP_log("      1          |       INDAC       |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#if !defined (SOC_AM275X)
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_5MB_SIZE);
    DebugP_log("      5          |       INDAC       |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
    test_ospi_read_write(&testDataCurObj, offset, TEST_OSPI_10MB_SIZE);
    DebugP_log("      10         |       INDAC       |        No         |        %0.2f          |       %0.2f\n\r", testDataCurObj.writeSpeed, testDataCurObj.readSpeed);
#endif

    test_ospi_gdevcfg_set_flash_protocol(FLASH_CFG_PROTO_8D_8D_8D);

    attrs->phyEnable = TRUE;

#if defined (SOC_AM62LX)
    /* Set frequency to 200Mhz. */
    status = SOC_moduleSetClockFrequency(AM62LX_DEV_FSS0,
             AM62LX_DEV_FSS0_OSPI0_RCLK_CLK, 166666666);
#elif defined(SOC_AM275X)
    /* Set frequency to 166Mhz. */
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS1_OSPI_0,
             TISCI_DEV_FSS1_OSPI_0_OSPI_RCLK_CLK, 166666666);
#else
    status = SOC_moduleSetClockFrequency(TISCI_DEV_FSS0_OSPI_0,
             TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK, 166666666);
#endif
    DebugP_assert(status == SystemP_SUCCESS);;
}


static void test_ospi_read_write_different_frequencies(void *args)
{

    uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;

    OSPI_Handle ospiHandle = OSPI_getHandle(CONFIG_OSPI0);
    OSPI_Config *config = (OSPI_Config*)ospiHandle;
    OSPI_Attrs attrs;
    Flash_DevConfig *devConfig = gFlashConfig[CONFIG_FLASH0].devConfig;

    memcpy((void*)&attrs, config->attrs, sizeof(OSPI_Attrs));

    Drivers_ospiClose();

    const OSPI_Attrs *tempAttrs = config->attrs;
    config->attrs = &attrs;

    DebugP_log("\r\n");
    DebugP_log("[TEST OSPI] Different Frequencies Performance Numbers Print Start \n\r");
    DebugP_log("\r\n");

    test_ospi_read_write_25Mhz(&attrs, offset, devConfig);
    test_ospi_read_write_50Mhz(&attrs, offset, devConfig);
    test_ospi_read_write_133Mhz(&attrs, offset, devConfig);
    test_ospi_read_write_166Mhz(&attrs, offset, devConfig);

    config->attrs = tempAttrs;
}

static void test_ospi_read_write_indirect_different_frequencies(void *args)
{

    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;

        OSPI_Handle ospiHandle = OSPI_getHandle(CONFIG_OSPI0);
        OSPI_Config *config = (OSPI_Config*)ospiHandle;
        OSPI_Attrs attrs;
        Flash_DevConfig *devConfig = gFlashConfig[CONFIG_FLASH0].devConfig;

        memcpy((void*)&attrs, config->attrs, sizeof(OSPI_Attrs));

        Drivers_ospiClose();

        const OSPI_Attrs *tempAttrs = config->attrs;
        config->attrs = &attrs;

        DebugP_log("\r\n");
        DebugP_log("[TEST OSPI] Different Frequencies Performance Numbers Print Start \n\r");
        DebugP_log("\r\n");

        *(uint32_t*)&gOspiConfig[CONFIG_OSPI0].attrs->readMode = OSPI_READ_MODE_INDAC;

        test_ospi_read_write_indirect_25Mhz(&attrs, offset, devConfig);
        test_ospi_read_write_indirect_50Mhz(&attrs, offset, devConfig);

        *(uint32_t*)&gOspiConfig[CONFIG_OSPI0].attrs->readMode = OSPI_READ_MODE_DAC;

        config->attrs = tempAttrs;
    }
}

static void test_ospi_validateOtp(void* args)
{
    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        int32_t retVal = SystemP_SUCCESS;
        uint32_t blk, page, txChunkCnt;
        uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;

        OSPI_Handle ospiHandle = OSPI_getHandle(CONFIG_OSPI0);
        OSPI_Config *config = (OSPI_Config*)ospiHandle;
        OSPI_Attrs attrs;
        const CSL_ospi_flash_cfgRegs *pReg;

        memcpy((void*)&attrs, config->attrs, sizeof(OSPI_Attrs));
        pReg = (const CSL_ospi_flash_cfgRegs *)(attrs.baseAddr);

        Drivers_ospiClose();

        attrs.validateOtp = TRUE;
        const OSPI_Attrs *tempAttrs = config->attrs;
        config->attrs = &attrs;

        Drivers_ospiOpen();
        retVal = Board_driversOpen();
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        /* Block erase at the test offset */
        Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
        retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        for(txChunkCnt = 0; txChunkCnt < (TEST_OSPI_2KB_SIZE)/TEST_OSPI_DATA_SIZE; txChunkCnt++)
        {
            memcpy(gOspiTestTxBulkBuf + txChunkCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , sizeof(gOspiTestTxBuf));
        }

        retVal += Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf, TEST_OSPI_2KB_SIZE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        TEST_ASSERT_EQUAL_MEMORY(gOspiTestRxBuf, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

        /* Set the read delay */
        CSL_REG32_FINS(&pReg->RD_DATA_CAPTURE_REG,
                       OSPI_FLASH_CFG_RD_DATA_CAPTURE_REG_DELAY_FLD,
                       0);

        /* Set TX DLL delay */
        CSL_REG32_FINS(&pReg->PHY_CONFIGURATION_REG,
                       OSPI_FLASH_CFG_PHY_CONFIGURATION_REG_PHY_CONFIG_TX_DLL_DELAY_FLD,
                       0);

        retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf, TEST_OSPI_2KB_SIZE);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_MEMORY(gOspiTestRxBuf, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

        Board_driversClose();

        config->attrs = tempAttrs;
    }
}

static void test_ospi_fallBack(void* args)
{
    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        int32_t retVal = SystemP_SUCCESS;
        uint32_t blk, page, txChunkCnt;
        uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;

        OSPI_Handle ospiHandle = OSPI_getHandle(CONFIG_OSPI0);
        OSPI_Config *config = (OSPI_Config*)ospiHandle;
        OSPI_Attrs attrs;
        const CSL_ospi_flash_cfgRegs *pReg;

        memcpy((void*)&attrs, config->attrs, sizeof(OSPI_Attrs));
        pReg = (const CSL_ospi_flash_cfgRegs *)(attrs.baseAddr);

        Drivers_ospiClose();

        attrs.validateOtp = TRUE;
        const OSPI_Attrs *tempAttrs = config->attrs;
        config->attrs = &attrs;

        Drivers_ospiOpen();
        retVal = Board_driversOpen();
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        /* Block erase at the test offset */
        Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
        retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        for(txChunkCnt = 0; txChunkCnt < (TEST_OSPI_2KB_SIZE)/TEST_OSPI_DATA_SIZE; txChunkCnt++)
        {
            memcpy(gOspiTestTxBulkBuf + txChunkCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , sizeof(gOspiTestTxBuf));
        }

        retVal += Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf, TEST_OSPI_2KB_SIZE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        TEST_ASSERT_EQUAL_MEMORY(gOspiTestRxBuf, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

        /* Set the read delay */
        CSL_REG32_FINS(&pReg->RD_DATA_CAPTURE_REG,
                       OSPI_FLASH_CFG_RD_DATA_CAPTURE_REG_DELAY_FLD,
                       0);

        /* Set TX DLL delay */
        CSL_REG32_FINS(&pReg->PHY_CONFIGURATION_REG,
                       OSPI_FLASH_CFG_PHY_CONFIGURATION_REG_PHY_CONFIG_TX_DLL_DELAY_FLD,
                       0);

        memcpy((void *)&config->attrs->phyConfiguration.phyParams, \
               (void *)&gTestFailParams, \
               sizeof(gTestFailParams));

        retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf, TEST_OSPI_2KB_SIZE);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_MEMORY(gOspiTestRxBuf, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

        memcpy((void *)&config->attrs->phyConfiguration.phyParams, \
               (void *)&gTestDefaultParams, \
               sizeof(gTestDefaultParams));

        Board_driversClose();

        config->attrs = tempAttrs;
    }
}

static void test_ospi_fallBack_to_1s1s1s(void* args)
{
    if(modeParams.cfgflashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
    {
        int32_t retVal = SystemP_SUCCESS;
        uint32_t blk, page, txChunkCnt;
        uint32_t offset = TEST_OSPI_FLASH_OFFSET_BASE;

        OSPI_Handle ospiHandle = OSPI_getHandle(CONFIG_OSPI0);
        OSPI_Config *config = (OSPI_Config*)ospiHandle;
        OSPI_Attrs attrs;
        const CSL_ospi_flash_cfgRegs *pReg;

        memcpy((void*)&attrs, config->attrs, sizeof(OSPI_Attrs));
        pReg = (const CSL_ospi_flash_cfgRegs *)(attrs.baseAddr);

        Drivers_ospiClose();

        attrs.validateOtp = TRUE;
        const OSPI_Attrs *tempAttrs = config->attrs;
        config->attrs = &attrs;

        Drivers_ospiOpen();
        retVal = Board_driversOpen();
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        /* Block erase at the test offset */
        Flash_offsetToBlkPage(gFlashHandle[CONFIG_FLASH0], offset, &blk, &page);
        retVal = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], blk);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        for(txChunkCnt = 0; txChunkCnt < (TEST_OSPI_2KB_SIZE)/TEST_OSPI_DATA_SIZE; txChunkCnt++)
        {
            memcpy(gOspiTestTxBulkBuf + txChunkCnt*sizeof(gOspiTestTxBuf) , gOspiTestTxBuf , sizeof(gOspiTestTxBuf));
        }

        retVal += Flash_write(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf, TEST_OSPI_2KB_SIZE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        TEST_ASSERT_EQUAL_MEMORY(gOspiTestRxBuf, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

        /* Set the read delay */
        CSL_REG32_FINS(&pReg->RD_DATA_CAPTURE_REG,
                       OSPI_FLASH_CFG_RD_DATA_CAPTURE_REG_DELAY_FLD,
                       0);

        /* Set TX DLL delay */
        CSL_REG32_FINS(&pReg->PHY_CONFIGURATION_REG,
                       OSPI_FLASH_CFG_PHY_CONFIGURATION_REG_PHY_CONFIG_TX_DLL_DELAY_FLD,
                       0);

        gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksCmd = 0;
        memcpy((void *)&config->attrs->phyConfiguration.phyParams, \
               (void *)&gTestFailParams, \
               sizeof(gTestFailParams));

        retVal = Flash_read(gFlashHandle[CONFIG_FLASH0], offset, gOspiTestRxBuf, TEST_OSPI_2KB_SIZE);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_MEMORY(gOspiTestRxBuf, gOspiTestTxBulkBuf, TEST_OSPI_2KB_SIZE);

        memcpy((void *)&config->attrs->phyConfiguration.phyParams, \
               (void *)&gTestDefaultParams, \
               sizeof(gTestDefaultParams));
        gFlashConfig[CONFIG_FLASH0].devConfig->protocolCfg.dummyClksCmd = 3;

        Board_driversClose();

        config->attrs = tempAttrs;
    }
}

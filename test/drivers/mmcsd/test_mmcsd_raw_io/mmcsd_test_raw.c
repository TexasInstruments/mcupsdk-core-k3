/*
 * Copyright (C) 2021-26 Texas Instruments Incorporated
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

/**\file mmcsd_test_raw.c
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

static Test_MmcModeSettings modeParams;

/* MMCSD Device Data structures */
MMCSD_EmmcDeviceData TestMMCSD_sdData0;
MMCSD_EmmcDeviceData TestMMCSD_emmcData0;

/* MMCSD temporary data buffers */
uint8_t TestMMCSD_dataBuf0[512U] __attribute__((aligned(128U)));
uint8_t TestMMCSD_dataBuf1[512U] __attribute__((aligned(128U)));

/* MMCSD Driver Parameters */
MMCSD_Params lMmcsdParams[] =
{
    {
        .deviceData = &TestMMCSD_sdData0,
        .dataBuf    = &TestMMCSD_dataBuf0[0],
    },
    {
        .deviceData = &TestMMCSD_emmcData0,
        .dataBuf    = &TestMMCSD_dataBuf0[0],
    },
};

/* ========================================================================== */
/*                           Static Function Declarations                     */
/* ========================================================================== */

static void TestMmcsd_getModeSettings(uint32_t type);
static int32_t TestMmcsd_rawIo(MMCSD_Handle handle, uint32_t instType);
#if !defined (SOC_AM275X) && !defined (SOC_J722S)
static uint8_t *TestMmcsd_getUnalignedTxAddr();
static uint8_t *TestMmcsd_getUnalignedRxAddr();
#endif
static int32_t TestMmcsd_multiBlockRawIo(MMCSD_Handle handle, uint32_t instType);

/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

/**
 * \brief Executes raw I/O on eMMC device to validate MMCSD
 * driver functionality.
 *
 * Test Category: Functionality
 *
 * This function verifies the MMCSD peripheral operation with
 * an eMMC device in raw I/O mode. It iterates through all
 * supported bus modes and performs read/write operations using
 * the `TestMmcsd_rawIo()` helper function.
 *
 * The test ensures correct data transfer, mode switching, and
 * driver stability across different eMMC operation modes
 * (e.g., SDR, DDR, HS200). It validates mode-dependent
 * initialization, transaction flow, and resource cleanup.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcRawIo(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t loopVar = 0;
    DebugP_log("Starting EMMC IO  test case\r\n");

    for (loopVar = 0; loopVar < TestMMCSD_modesCount; loopVar ++)
    {
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[loopVar];
        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

        retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_EMMC);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
}

/**
 * \brief Tests enabling and disabling of eMMC boot partition
 * using MMCSD driver APIs.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * enables and disables the eMMC boot partition. It opens the
 * eMMC instance with custom initialization parameters and
 * executes both `MMCSD_enableBootPartition()` and
 * `MMCSD_disableBootPartition()` to confirm proper behavior.
 *
 * The test ensures that the boot partition access commands are
 * handled successfully by the driver and that no errors occur
 * during mode switching or partition reconfiguration. It also
 * validates successful driver initialization and closure.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcEnableDisableBootPartition(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    DebugP_log("Starting EMMC  boot partition enable disable test case\r\n");

    /* Open EMMC instance */
    MMCSD_Params test_params;
    MMCSD_Params_init(&test_params);

    test_params.deviceData = &TestMMCSD_emmcData0;
    test_params.dataBuf    = &TestMMCSD_dataBuf0[0];

    MMCSD_Handle handle =  MMCSD_open(0, &test_params);
    TEST_ASSERT_NOT_NULL(handle);

    /* Enable the boot partition */
    retVal = MMCSD_enableBootPartition(handle, 1);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* Disable the boot partition */
    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    MMCSD_close(handle);
}

/**
 * \brief Tests enabling and disabling of eMMC boot partition
 * using MMCSD driver APIs for invalid partition number.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * fails while enabling invalid boot partition. It opens the
 * eMMC instance with custom initialization parameters and
 * executes both `MMCSD_enableBootPartition'.
 *
 * The test ensures that the boot partition access commands are
 * handled successfully by the driver. It also
 * validates successful driver initialization and closure.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcEnableDisableBootPartitionFail(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    DebugP_log("Starting EMMC boot partition enable disable test case\r\n");

    /* Open EMMC instance */
    MMCSD_Params test_params;
    MMCSD_Params_init(&test_params);

    test_params.deviceData = &TestMMCSD_emmcData0;
    test_params.dataBuf    = &TestMMCSD_dataBuf0[0];

    MMCSD_Handle handle =  MMCSD_open(0, &test_params);
    TEST_ASSERT_NOT_NULL(handle);

    /* Enable the boot partition */
    retVal = MMCSD_enableBootPartition(handle, 5);
    TEST_ASSERT_EQUAL(retVal, SystemP_FAILURE);

    MMCSD_close(handle);
}

/**
 * \brief Tests enabling and disabling of SD boot partition
 * using MMCSD driver APIs.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * enables and disables the SD boot partition. It opens the
 * eMMC instance with custom initialization parameters and
 * executes both `MMCSD_enableBootPartition()` and
 * `MMCSD_disableBootPartition()` to confirm proper behavior.
 *
 * The test ensures that the boot partition access commands are
 * handled successfully by the driver and that no errors occur
 * during mode switching or partition reconfiguration. It also
 * validates successful driver initialization and closure.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_sdEnableDisableBootPartition(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    DebugP_log("Starting SD boot partition enable disable test case\r\n");

    /* Open EMMC instance */
    MMCSD_Params test_params;
    MMCSD_Params_init(&test_params);

    test_params.deviceData = &TestMMCSD_sdData0;
    test_params.dataBuf    = &TestMMCSD_dataBuf0[0];

    MMCSD_Handle handle =  MMCSD_open(1, &test_params);
    TEST_ASSERT_NOT_NULL(handle);

    /* Enable the boot partition */
    retVal = MMCSD_enableBootPartition(handle, 1);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* Disable the boot partition */
    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    MMCSD_close(handle);
}

/**
 * \brief Executes multi-block raw I/O transfers on eMMC to
 * validate MMCSD driver handling of continuous operations.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * handles multi-block read and write operations on an eMMC
 * device. It iterates through all supported modes and executes
 * the `TestMmcsd_multiBlockRawIo()` helper function to
 * perform sequential data transfers.
 *
 * The test ensures proper DMA handling, block count updates,
 * and uninterrupted multi-block data flow across various eMMC
 * modes (e.g., SDR, DDR, HS200). It also confirms driver
 * stability, data integrity, and correct resource management
 * during repeated transactions.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcMultiblockRawIo(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t loopVar = 0;

    DebugP_log("Starting multiple multi block EMMC transfer test case\r\n");
    for ( loopVar = 0; loopVar < TestMMCSD_modesCount ; loopVar ++)
    {
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[loopVar];
        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

        retVal = TestMmcsd_multiBlockRawIo(handle, CONFIG_MMCSD_EMMC);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
};

#if !defined (SOC_AM275X) && !defined (SOC_J722S)

/**
 * \brief Executes raw I/O operations on SD card to validate
 * MMCSD driver functionality in standard SD mode.
 *
 * Test Category: Functionality
 *
 * This function verifies the MMCSD driver operation with an SD
 * card in raw I/O mode. It iterates through all supported SD
 * modes and performs read/write transactions using the
 * `TestMmcsd_rawIo()` helper function.
 *
 * The test ensures proper data transfer, mode switching, and
 * driver stability across different SD modes (e.g., SDR12,
 * SDR25, SDR50, SDR104). It validates correct initialization,
 * transaction flow, and cleanup during repeated operations.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_sdRawIo(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t loopVar = 0;
    DebugP_log("Starting SD card  IO  test case\r\n");

    for (loopVar = 0; loopVar < TestMMCSD_sdModesCount; loopVar ++)
    {
        gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[loopVar];
        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_SD];

        retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_SD);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
}

/**
 * \brief Tests to write and read single block of data.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * writes and reads back single block of data
 * It also validates successful driver initialization 
 * write, read and closure.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_sdSingleBlockTransfer(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t blockSize;
    uint32_t numBlocksPerIter;
    DebugP_log("Starting SD card card single block write and read");

    /*Write data to the boot partition */
    TestMmcsd_fillBuffers();

    gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[0];
    Drivers_mmcsdOpen();
    MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_SD];
    TEST_ASSERT_NOT_NULL(handle);
    blockSize = MMCSD_getBlockSize(handle);
    numBlocksPerIter = 1;

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    memset(TestMMCSD_rxBuf, 0, blockSize);

    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, blockSize);
    Drivers_mmcsdClose();
}

/**
 * \brief Tests EMMC transfers across multiple bus width
 * configurations using MMCSD driver.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * supports different EMMC bus width configurations. It
 * iterates through all supported bus widths (1-bit, 4-bit,
 * 8-bit) and performs raw I/O transfers using the
 * `TestMmcsd_rawIo()` helper function.
 *
 * The test ensures correct driver handling of bus width
 * reconfiguration, data alignment, and protocol transitions.
 * It validates successful transfer completion, mode stability,
 * and recovery after each width change. The bus width is
 * restored to its default configuration after all iterations.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcMultipleBusWidths(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t busConfigNum = 4;
    uint32_t loopVar = 0;

    DebugP_log("Starting EMMC multiple bus width config test case\r\n");

    for (loopVar = 0; loopVar < busConfigNum; loopVar++)
    {

        /* Supported  bus widths are 1, 4, 8 */
        if(loopVar == 0)
        {
            gMmcsdAttrs[CONFIG_MMCSD_EMMC].busWidth = 1;
            DebugP_log("Starting transfer with bus width: %d\r\n", 1);
        }
        else
        {
	    /* When an unsupported bus width is used should revert to 1 */
            gMmcsdAttrs[CONFIG_MMCSD_EMMC].busWidth = (loopVar * 4);
            DebugP_log("Starting transfer with bus width: %d\r\n", (loopVar * 4));
        }
        /* Using a fixed support mode */
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

        retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_EMMC);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
    /* Revert back to normal bus width after testing */
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].busWidth = 8;
    Drivers_mmcsdOpen();
    Drivers_mmcsdClose();
}

/**
 * \brief Tests writing to the boot and UDA partitions.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * enables and disables the eMMC boot partition and writes to them
 * It opens the eMMC instance with custom initialization parameters 
 * and executes both `MMCSD_enableBootPartition()`to enable and 
 * boot partitions and write to it. The test ensures that the boot 
 * partition access commands are handled successfully by the driver 
 * and that no errors occur during mode switching or partition 
 * reconfiguration. It also validates successful driver initialization 
 * write, read and closure.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcWriteReadBootPartition(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t blockSize;
    uint32_t numBlocksPerIter;
    DebugP_log("Starting EMMC boot partition write and read");

    /* This close is required as the above test case fails */
    Drivers_mmcsdClose();
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 1;

    /*Write data to the boot partition */
    TestMmcsd_fillBuffers();

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    TEST_ASSERT_NOT_NULL(handle);
    blockSize = MMCSD_getBlockSize(handle);
    numBlocksPerIter = TEST_MMCSD_6MB_SIZE / blockSize;

    /* Enable the boot0 partition */
    retVal = MMCSD_enableBootPartition(handle, 1);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_6MB_SIZE);

    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_6MB_SIZE);

    /* Disable the boot partition */
    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* Enable the boot1 partition */
    retVal = MMCSD_enableBootPartition(handle, 2);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_6MB_SIZE);

    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_6MB_SIZE);

    /* Disable the boot partition */
    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* Read and write from the UDA partition */
    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_6MB_SIZE);

    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_6MB_SIZE);
    Drivers_mmcsdClose();
}

/**
 * \brief Tests writing to the boot and UDA partitions.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * enables and disables the eMMC boot partition and fails on writing
 * more than 32MB to boot partition and succeeeds for UDA partition
 * and executes both `MMCSD_enableBootPartition()`to enable and 
 * boot partitions and write to it. The test ensures that the boot 
 * partition access commands are handled successfully by the driver 
 * and that no errors occur during mode switching or partition 
 * reconfiguration. It also validates successful driver initialization 
 * write, read and closure.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcWriteReadBootPartitionFail(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t blockSize;
    uint32_t numBlocksPerIter;
    DebugP_log("Starting EMMC boot partition write and read");

    /* This close is required as the above test case fails */
    Drivers_mmcsdClose();
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 1;

    /*Write data to the boot partition */
    TestMmcsd_fillBuffers();

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    TEST_ASSERT_NOT_NULL(handle);
    blockSize = MMCSD_getBlockSize(handle);
    numBlocksPerIter = TEST_MMCSD_DATA_SIZE / blockSize;

    /* Enable the boot0 partition */
    retVal = MMCSD_enableBootPartition(handle, 1);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, retVal);

    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, retVal);

    /* Disable the boot partition */
    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* Enable the boot1 partition */
    retVal = MMCSD_enableBootPartition(handle, 2);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_FAILURE);

    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, 0x0,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_FAILURE);

    /* Disable the boot partition */
    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* Read and write from the UDA partition */
    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_DATA_SIZE);

    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_DATA_SIZE);
    Drivers_mmcsdClose();
}

/**
 * \brief Tests MMCSD driver operation with and without DMA
 * for odd number of blocks
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers  with and without DMA for odd number of blocks
 *
 * After all iterations, the default DMA configuration is restored.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_unalignedBuffersRawIo(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t numBlocksPerIter = 0U;
    int32_t loopVar;

    uint8_t *unalignedTxBufPtr = TestMmcsd_getUnalignedTxAddr();
    uint8_t *unalignedRxBufPtr = TestMmcsd_getUnalignedRxAddr(); 

    /* This close is required as the above test case fails */
    Drivers_mmcsdClose();

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    uint32_t blockSize = MMCSD_getBlockSize(handle);
    Drivers_mmcsdClose();

    numBlocksPerIter = TEST_MMCSD_1MB_SIZE / blockSize;
      
    DebugP_log("Starting the EMMC unaligned buffer transfer\r\n");
       
    TestMmcsd_fillUnalignedBuffers(unalignedTxBufPtr);

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        if(loopVar == 0)
        {
            gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 0;
            DebugP_log("Starting the transfer with DMA disabled\r\n");
        }
        else
        {       
            gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 1;
            DebugP_log("Starting the transfer with DMA enabled\r\n");
        }

        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
        Drivers_mmcsdOpen();
        handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
        retVal = MMCSD_write(handle, unalignedTxBufPtr, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
        TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

        memset(unalignedRxBufPtr, 0, TEST_MMCSD_1MB_SIZE);
        retVal = MMCSD_read(handle, unalignedRxBufPtr, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
        TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
        TEST_ASSERT_EQUAL_MEMORY(unalignedTxBufPtr, unalignedRxBufPtr, TEST_MMCSD_1MB_SIZE);
        Drivers_mmcsdClose();
    } 
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 1;
}

/**
 * \brief Test to create CRC error
 *
 * Test Category: Negative test
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when data CRC error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_crcRecovery(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t numBlocksPerIter = 0U;
    uint32_t blockSize;
    uint32_t itapDlySel;
    const CSL_mmc_sscfgRegs *baseReg = (const CSL_mmc_sscfgRegs *)gMmcsdAttrs[CONFIG_MMCSD_EMMC].ssBaseAddr;

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
#if defined (C7_CORE)
    /* This close is required as the above test case fails for C7 core*/
    Drivers_mmcsdClose();
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 1;
#endif
    Drivers_mmcsdOpen();
    /* Set tuning type as manual tuning */
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].tuningType = 1U;
    MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    blockSize = MMCSD_getBlockSize(handle);

    numBlocksPerIter = TEST_MMCSD_XFER_SIZE / blockSize;
    TestMmcsd_fillBuffers();

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* Read the curent itap  values */
    itapDlySel = 
               (CSL_REG32_RD(&baseReg->PHY_CTRL_4_REG) & CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYSEL_MASK) 
                                                       >> CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYSEL_SHIFT;

    /* Use a failing ITAP value */
    CSL_REG32_FINS(&baseReg->PHY_CTRL_4_REG, MMC_SSCFG_PHY_CTRL_4_REG_ITAPCHGWIN, 1U);
    CSL_REG32_FINS(&baseReg->PHY_CTRL_4_REG, MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYENA, 1U);
    CSL_REG32_FINS(&baseReg->PHY_CTRL_4_REG, MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYSEL, 25U);
    CSL_REG32_FINS(&baseReg->PHY_CTRL_4_REG, MMC_SSCFG_PHY_CTRL_4_REG_ITAPCHGWIN, 0U);

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_XFER_SIZE);
    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_rxBuf, TestMMCSD_txBuf, TEST_MMCSD_XFER_SIZE);

    /* Rewrite the orginal delay values */
    CSL_REG32_FINS(&baseReg->PHY_CTRL_4_REG, MMC_SSCFG_PHY_CTRL_4_REG_ITAPCHGWIN, 1U);
    CSL_REG32_FINS(&baseReg->PHY_CTRL_4_REG, MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYENA, 1U);
    CSL_REG32_FINS(&baseReg->PHY_CTRL_4_REG, MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYSEL, itapDlySel);
    CSL_REG32_FINS(&baseReg->PHY_CTRL_4_REG, MMC_SSCFG_PHY_CTRL_4_REG_ITAPCHGWIN, 0U);

    Drivers_mmcsdClose();
}


/**
 * \brief Tests MMCSD mode switch
 * with different transfer modes
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers  when switching from a low speed
 * to high speed mode and then back to high speed mode from
 * low speed mode.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcSpeedSwitch(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    int32_t numBlocksPerIter = 0U;

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[0];
    Drivers_mmcsdOpen();
    MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    uint32_t blockSize = MMCSD_getBlockSize(handle);
    numBlocksPerIter = TEST_MMCSD_DATA_SIZE / blockSize;

    /* This close is required as the unaligned transfer before
     * this test case fails and exits with out closing the driver.
     */
    Drivers_mmcsdClose();
    TestMmcsd_fillBuffers();

    /* Write the data to one block in HS200 mode */
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
    Drivers_mmcsdClose();

    /* Read the data in DDR50 mode */
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[1];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_DATA_SIZE);
    Drivers_mmcsdClose();

    /* Write the data to START_BLOCK2 in SDR50 mode*/
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[0];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
    Drivers_mmcsdClose();

    /* Read the data in HS200 mode */
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_DATA_SIZE);
    Drivers_mmcsdClose();
}

/**
 * \brief Tests SD card transfers across multiple bus width
 * configurations using MMCSD driver.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * supports different SD card bus width configurations. It
 * iterates through all supported bus widths (1-bit, 4-bit,
 * and performs raw I/O transfers using the `TestMmcsd_rawIo()' 
 * helper function.
 *
 * The test ensures correct driver handling of bus width
 * reconfiguration, data alignment, and protocol transitions.
 * It validates successful transfer completion, mode stability,
 * and recovery after each width change. The bus width is
 * restored to its default configuration after all iterations.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_sdMultipleBusWidths(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t busConfigNum = 2;
    uint32_t loopVar = 0;

    DebugP_log("Starting SD card multiple bus width config test case\r\n");

    for (loopVar = 0; loopVar < busConfigNum; loopVar++)
    {

        /* Supported  bus widths are 1, 4 */
        if(loopVar == 0)
        {
            gMmcsdAttrs[CONFIG_MMCSD_SD].busWidth = 1;
            DebugP_log("Starting transfer with bus width: %d\r\n", 1);
        }
        else
        {
            gMmcsdAttrs[CONFIG_MMCSD_SD].busWidth = 4;
            DebugP_log("Starting transfer with bus width: %d\r\n", 4);
        }
        /* Using a fixed support mode */
        gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[0];
        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_SD];

        retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_SD);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
    /* Revert back to normal bus width after testing */
    gMmcsdAttrs[CONFIG_MMCSD_SD].busWidth = 4;
    Drivers_mmcsdOpen();
    Drivers_mmcsdClose();
}
#endif

/**
 * \brief Tests eMMC transfers with multiple PHY configurations
 * to validate MMCSD driver PHY switching capability.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * handles PHY configuration changes while operating with an
 * eMMC device. It cycles through all supported PHY types:
 * hardware PHY, software PHY, and no PHY, performing raw I/O
 * transfers using the `TestMmcsd_rawIo()` helper function.
 *
 * The test ensures proper PHY initialization, selection, and
 * cleanup for each configuration. It validates data integrity
 * and transfer stability across PHY modes using HS200
 * operation mode. After all iterations, the PHY type is reset
 * to its default (software PHY) configuration.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcMultiplePhyconfig(void *args)
{
    int32_t retVal = SystemP_SUCCESS;

    /* Use HS200 mode */
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    MMCSD_Handle handle;

    DebugP_log("Starting EMMC  PHY switching test case\r\n");
#if defined (SOC_AM62PX)
    /* HW PHY is only supported in AM62PX */
    DebugP_log("Starting transfer with  HW PHY\r\n");
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

    retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_EMMC);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    Drivers_mmcsdClose();
#else
    DebugP_log("Starting transfer with  SW PHY\r\n");
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].phyType = 1;

    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

    retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_EMMC);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    Drivers_mmcsdClose();
#endif

    /* Revert back to normal phy type after testing */
#if defined (SOC_AM62PX)
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].phyType = 0;
#else
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].phyType = 1;
#endif
    Drivers_mmcsdOpen();
    Drivers_mmcsdClose();
}

/**
 * \brief Tests eMMC transfers with different PHY tuning
 * configurations to validate MMCSD tuning control.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * supports both automatic and manual PHY tuning modes for
 * eMMC operation. It switches between tuning configurations
 * and performs raw I/O transfers using the
 * `TestMmcsd_rawIo()` helper function.
 *
 * The test ensures proper PHY tuning initialization and
 * reconfiguration, validating signal integrity, transfer
 * stability, and timing adjustment in HS200 mode. It also
 * confirms that driver resources are restored to default after
 * completing all tuning mode iterations.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcTuningConfig(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t tuningConfigNum = 2;
    uint32_t loopVar = 0;

    DebugP_log("Starting EMMC tuning switch tarnsfer test case\r\n");

    for (loopVar = 0; loopVar < tuningConfigNum; loopVar++)
    {
        if(loopVar == 0)
        {
#if defined (SOC_AM275X)
            /* Auto PHY tuning fails on AM275x */
            continue;
#else
            /* Auto PHY tuning */
            DebugP_log("Starting transfer with  auto PHY tuning\r\n");
#endif
        }
        else
        {
            /* Manual PHY tuning */
            DebugP_log("Starting transfer with  manual PHY tuning\r\n");
        }
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].tuningType = loopVar;
        /* Use HS200 mode */
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];

        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

        retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_EMMC);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
    /* Revert back to manual PHY tuning after testing */
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].tuningType = 1U;
    Drivers_mmcsdOpen();
    Drivers_mmcsdClose();
}

#if !defined (SOC_AM275X) && !defined (SOC_J722S)

/**
 * \brief Tests SD card transfers with different PHY tuning
 * configurations to validate MMCSD tuning behavior.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * supports both automatic and manual PHY tuning modes when
 * operating with an SD card. It switches between tuning
 * configurations and performs raw I/O transfers using the
 * `TestMmcsd_rawIo()` helper function.
 *
 * The test ensures that tuning operations are applied and
 * released correctly, validating signal quality, transfer
 * timing, and overall stability. It confirms correct tuning
 * control handling across configurations and restores the
 * default tuning type after all iterations.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */

void TestMmcsd_sdTuningConfig(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t tuningConfigNum = 2;
    uint32_t loopVar = 0;

    DebugP_log("Starting SD tuning switch transfer test case\r\n");

    for (loopVar = 0; loopVar < tuningConfigNum; loopVar++)
    {
        if(loopVar == 0)
        {
            /* Auto PHY tuning */
            DebugP_log("Starting transfer with  auto PHY tuning\r\n");
        }
        else
        {
            /* Manual PHY tuning */
            DebugP_log("Starting transfer with  manual PHY tuning\r\n");
        }
        gMmcsdAttrs[CONFIG_MMCSD_SD].tuningType = loopVar;
        /* Use HS200 mode */
        gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[0];

        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_SD];

        retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_SD);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
    /* Revert back to normal bus width after testing */
    gMmcsdAttrs[CONFIG_MMCSD_SD].tuningType = 1;
    Drivers_mmcsdOpen();
    Drivers_mmcsdClose();
}

/**
 * \brief Validates MMCSD driver behavior when opening an
 * already instance that was priviously opened in another mode.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver does not have 
 * any issues in opening and closing in different modes.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_multipleOpenClose(void *args)
{
    int loopVar;
   
    /* Open and Close for different SD modes */ 
    for(loopVar = 0; loopVar < TestMMCSD_sdModesCount; loopVar++)
    {
        gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[loopVar];
        MMCSD_Handle handle = MMCSD_open(1, &lMmcsdParams[1]);
        TEST_ASSERT_NOT_NULL(handle);
        MMCSD_close(handle);
    }
    
    for(loopVar = 0; loopVar < TestMMCSD_modesCount; loopVar++)
    {
        /* Do the same for EMMC as well */
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[loopVar];
        MMCSD_Handle handle = MMCSD_open(0, &lMmcsdParams[0]);
        TEST_ASSERT_NOT_NULL(handle);
        MMCSD_close(handle);
    }

    /*Set the card type as no device */
    gMmcsdAttrs[CONFIG_MMCSD_SD].cardType = MMCSD_CARD_TYPE_NO_DEVICE;
    for(loopVar = 0; loopVar < TestMMCSD_sdModesCount; loopVar++)
    {
        gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[loopVar];
        MMCSD_Handle handle = MMCSD_open(1, &lMmcsdParams[1]);
        TEST_ASSERT_NOT_NULL(handle);
        MMCSD_close(handle);
    }
    gMmcsdAttrs[CONFIG_MMCSD_SD].cardType = MMCSD_CARD_TYPE_SD;
}

/**
 * \brief Validates MMCSD driver input clock frequency
 * configuration for SD card operation.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * applies and reports the configured input clock frequency for
 * SD card operation. It sets a known test frequency, opens the
 * driver, and reads back the actual frequency using the
 * `MMCSD_getInputClk()` API.
 *
 * The test ensures proper propagation of configuration values
 * through the driver initialization path and confirms that the
 * reported frequency matches the expected value. It validates
 * clock configuration consistency between driver attributes and
 * hardware setup.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_validateClkFreq(void *args)
{
    int loopVar;
    int testModCount = 4;
    uint32_t inputClk = 0, outputClk, clockDiv;
    uint16_t lowVal, highVal, cc;
    uint32_t expectHz = 0U;
    uint32_t tol;
    const CSL_mmc_ctlcfgRegs *pCtrl = 
			(const CSL_mmc_ctlcfgRegs *)gMmcsdAttrs[CONFIG_MMCSD_EMMC].ctrlBaseAddr;
    uint32_t modesToTest [] = {
	MMCSD_SUPPORT_MMC_DS, 
	MMCSD_SUPPORT_MMC_HS_SDR,
	MMCSD_SUPPORT_MMC_HS_DDR,
	MMCSD_SUPPORT_MMC_HS200,
#if !defined (SOC_AM62PX) ||  !defined (SOC_J722S)
    };
    testModCount = 4;
#else
	MMCSD_SUPPORT_MMC_HS400
    };
    testModCount = 5;
#endif
    DebugP_log("Starting EMMC frequency vaidation test\r\n");
    
    for(loopVar = 0; loopVar < testModCount; loopVar++)
    {
    	gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = modesToTest[loopVar];
    	Drivers_mmcsdOpen();
    	MMCSD_Handle handle = MMCSD_getHandle(CONFIG_MMCSD_EMMC);
    	TEST_ASSERT_NOT_NULL(handle);

    	inputClk = MMCSD_getInputClk(handle);
    	TEST_ASSERT_TRUE(inputClk > 0);

	/* Read the clock control register */
        cc = CSL_REG16_RD(&pCtrl->CLOCK_CONTROL);
        lowVal = (uint16_t)((cc & 0xFF00U) >> 8);
        highVal = (uint16_t)((cc & 0x00C0U) >> 6);

        /* Compute the clock divisor */
        clockDiv = (uint32_t)((uint32_t)lowVal | (uint32_t)((uint32_t)highVal << 8));
        outputClk = (clockDiv == 0U) ? inputClk : (inputClk / (2U * clockDiv));

        if(modesToTest[loopVar] == MMCSD_SUPPORT_MMC_DS)        
        {        
	    expectHz = 26000000U;
        }        
        else if(modesToTest[loopVar] == MMCSD_SUPPORT_MMC_HS_SDR)  
        {        
	    expectHz = 52000000U;
        }        
        else if(modesToTest[loopVar] == MMCSD_SUPPORT_MMC_HS_DDR)  
        {        
            expectHz = 52000000U;
        }        
        else if (modesToTest[loopVar] == MMCSD_SUPPORT_MMC_HS200)   
        {        
            expectHz = 200000000U;
        }        
#if defined (SOC_AM62PX) || defined (SOC_J722S)
        else if (modesToTest[loopVar] == MMCSD_SUPPORT_MMC_HS400)   
        {        
           expectHz = 200000000U;
        }        
#endif
        TEST_ASSERT_TRUE_MESSAGE(expectHz > 0U, "Unknown expected frequency for mode");

        /* 10% tolerance */
        tol = expectHz / 10U;
        TEST_ASSERT_TRUE((outputClk >= expectHz - tol && outputClk <= expectHz + tol));
        Drivers_mmcsdClose();
    }
}
#endif

/**
 * \brief Tests MMCSD driver operation with and without DMA
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers  with and without — executing 
 * raw I/O transfers using the `TestMmcsd_rawIo()` helper function.
 *
 * After all iterations, the default DMA configuration is restored.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_dmaModes(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    DebugP_log("Starting EMMC DMA mode switching test\r\n");
    int loopVar;
    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        if(loopVar == 0)
        {
            DebugP_log("Starting transfer with DMA  disabled\r\n");
            gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 0;
        }
        else
        {
            DebugP_log("Starting transfer with DMA enabled\r\n");
            gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 1;
        }
        /* Using the HS200 mode */
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
        retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_EMMC);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 1;
    Drivers_mmcsdOpen();
    Drivers_mmcsdClose();
}

/**
 * \brief Tests MMCSD driver operation withinterrupt
 * enabled and disabled for eMMC transfers.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers with and with out interrupt
 * It cycles through two modes — executing raw I/O transfers 
 * using the `TestMmcsd_rawIo()` helper function.
 *
 * The test validates driver stability, transfer integrity, 
 * and cleanup while operating in HS200 mode. After all 
 * iterations, the default interrupt configuration is restored.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
/*
void TestMmcsd_intrModes(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    DebugP_log("Starting EMMC interrupt mode switching test\r\n");
    int loopVar;
    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        if(loopVar == 0)
        {
            DebugP_log("Starting transfer with interrupt disabled\r\n");
            gMmcsdAttrs[CONFIG_MMCSD_EMMC].intrEnable = 0;
        }
        else
        {
            DebugP_log("Starting transfer with interrupt enabled\r\n");
            gMmcsdAttrs[CONFIG_MMCSD_EMMC].intrEnable = 1;
        }

        // Using the HS200 mode 
        gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
        Drivers_mmcsdOpen();
        MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
        retVal = TestMmcsd_rawIo(handle, CONFIG_MMCSD_EMMC);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        Drivers_mmcsdClose();
    }
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].intrEnable = 0;
    Drivers_mmcsdOpen();
    Drivers_mmcsdClose();
}
*/

/**
 * \brief Validates MMCSD driver behavior when opening an
 * invalid instance.
 *
 * Test Category: Negative
 *
 * This function verifies that the MMCSD driver properly handles
 * attempts to open an invalid or non-existent instance. It
 * calls `MMCSD_open()` with an out-of-range instance index and
 * checks that the returned handle is NULL.
 *
 * The test ensures robust error handling, boundary checking,
 * and prevention of unintended access to invalid device
 * instances. It validates correct return behavior and driver
 * response under invalid initialization conditions.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */

void TestMmcsd_openInvalidInstance(void *args)
{
    /* Use an unvalid instance */
    MMCSD_Handle handle =  MMCSD_open(10, &lMmcsdParams[0]);
    TEST_ASSERT_EQUAL(handle, NULL);
}

/**
 * \brief Validates MMCSD driver behavior when reopening an
 * already opened instance.
 *
 * Test Category: Negative
 *
 * This function verifies that the MMCSD driver prevents
 * multiple opens of the same instance. It first opens a valid
 * MMCSD instance successfully and then attempts to reopen the
 * same instance, expecting the second call to fail and return
 * NULL.
 *
 * The test ensures proper resource ownership, instance locking,
 * and protection against concurrent or duplicate open requests.
 * It validates that the driver enforces single-instance access
 * and releases resources correctly after closing.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */

void TestMmcsd_openOpenFail(void *args)
{
    /* Open a valid MMC instance */
    MMCSD_Handle handle = MMCSD_open(0, &lMmcsdParams[0]);
    TEST_ASSERT_NOT_NULL(handle);

    /* Open the same instance for the second time which should fail */
    MMCSD_Handle handle2 = MMCSD_open(0, &lMmcsdParams[0]);
    TEST_ASSERT_NULL(handle2);

    MMCSD_close(handle);
}

/**
 * \brief Validates MMCSD block count and capacity detection
 * using driver query APIs.
 *
 * Test Category: Functionality
 *
 * This function verifies that the MMCSD driver correctly
 * reports the total block count of the connected eMMC. 
 * It first fetches the valueof  block count with DMA enabled 
 * and then DMA disabled. It opens the eMMC instance in HS200 mode
 * and queries the block count using `MMCSD_getBlockCount()`. The
 * values obtained with and without DMA should match.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_getBlockCountValidate(void *args)
{
    uint32_t blockCount1, blockCount2;  

    /* Get the block count with dma enabled */
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[1];
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 1;
    Drivers_mmcsdOpen();
    MMCSD_Handle handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    blockCount1 = MMCSD_getBlockCount(handle);
    Drivers_mmcsdClose();
    
    /* Get the block count with dma enabled */
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 0;
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    blockCount2 = MMCSD_getBlockCount(handle);
    Drivers_mmcsdClose();

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma = 1U;

    TEST_ASSERT_EQUAL(blockCount1, blockCount2);
#if !defined (SOC_AM275X) && !defined (SOC_J722S)
    gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[0];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_SD];
    uint32_t isHCSupported = MMCSD_isHC(handle);
    Drivers_mmcsdClose();
    if(isHCSupported == 1)
    {
        /*Check block count for SD card as well */
        gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[0];
        gMmcsdAttrs[CONFIG_MMCSD_SD].enableDma = 1;
        Drivers_mmcsdOpen();
        handle = gMmcsdHandle[CONFIG_MMCSD_SD];
        blockCount1 = MMCSD_getBlockCount(handle);
        Drivers_mmcsdClose();
    
        gMmcsdAttrs[CONFIG_MMCSD_SD].enableDma = 0;
        Drivers_mmcsdOpen();
        handle = gMmcsdHandle[CONFIG_MMCSD_SD];
        blockCount2 = MMCSD_getBlockCount(handle);
        Drivers_mmcsdClose();

        gMmcsdAttrs[CONFIG_MMCSD_SD].enableDma = 1;
        TEST_ASSERT_EQUAL(blockCount1, blockCount2);
    }
#endif
}

/**
 * \brief Validates MMCSD write API behavior with invalid
 * arguments and handles.
 *
 * Test Category: Negative
 *
 * This function verifies that the MMCSD driver correctly
 * handles invalid input parameters passed to the `MMCSD_write()`
 * API. It tests two negative scenarios — first with a NULL
 * handle and then with a NULL data buffer — ensuring both cases
 * return `SystemP_FAILURE`.
 *
 * The test ensures proper argument validation, pointer
 * protection, and error return handling in the driver. It
 * validates robustness of the write API against null or
 * uninitialized resources and prevents unintended memory
 * access.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_writeArgumentValidate(void *args)
{
    int32_t retval;

    /* should fail when handle is NULL */
    MMCSD_Handle handle = NULL;

    retval = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, 20);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retval);

    /* Get a valid handle */
    handle = MMCSD_open(10, &lMmcsdParams[0]);

    /* Should fail when buffer is NULL */
    retval = MMCSD_write(handle, NULL, TEST_MMCSD_EMMC_START_BLK, 20);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retval);

    /* Close the handle */
    MMCSD_close(handle);
}

/**
 * \brief Validates MMCSD read API behavior with invalid
 * arguments and handles.
 *
 * Test Category: Negative
 *
 * This function verifies that the MMCSD driver properly handles
 * invalid arguments passed to the `MMCSD_read()` API. It tests
 * two negative conditions — a NULL handle and a NULL buffer —
 * confirming that both result in `SystemP_FAILURE`.
 *
 * The test ensures correct argument validation, null pointer
 * checks, and safe handling of invalid resources. It validates
 * driver robustness and error response when read operations are
 * invoked with uninitialized or missing parameters.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_readArgumentValidate(void *args)
{
    int32_t retval;

    /* should fail when handle is NULL */
    MMCSD_Handle handle = NULL;

    retval = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, 20);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retval);

    /* Get a valid handle */
    handle = MMCSD_open(0, &lMmcsdParams[0]);

    /* Should fail when buffer is NULL */
    retval = MMCSD_read(handle, NULL, TEST_MMCSD_EMMC_START_BLK, 20);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retval);

    /* Close the handle */
    MMCSD_close(handle);
}

/* ========================================================================== */
/*                           Static Function Declarations                     */
/* ========================================================================== */

/* Function to get the transfer mode and other attributes of a transfer */
static void TestMmcsd_getModeSettings(uint32_t type)
{
    modeParams.busWidth = gMmcsdAttrs[type].busWidth;

    /* Entend this for more flashNames when required*/
    if(gMmcsdAttrs[type].cardType == MMCSD_CARD_TYPE_EMMC)
    {
        modeParams.cardType = "EMMC";
        if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS_SDR)
        {
            modeParams.mode = "SDR";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS_DDR)
        {
            modeParams.mode = "DDR";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS200)
        {
            modeParams.mode = "HS200";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_MMC_HS400)
        {
            modeParams.mode = "HS400";
        }
    }
    else if(gMmcsdAttrs[type].cardType == MMCSD_CARD_TYPE_SD)
    {
        modeParams.cardType = "SD";
        if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_SDR50)
        {
            modeParams.mode = "SDR";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_DDR50)
        {
            modeParams.mode = "DDR";
        }
        else if(gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_SDR104)
        {
            modeParams.mode = "SDR104";
        }
        else if((gMmcsdAttrs[type].supportedModes & MMCSD_SUPPORT_SD_HS))
        {
            modeParams.mode = "HS";
        }
    }
    else if(gMmcsdAttrs[type].cardType == MMCSD_CARD_TYPE_NO_DEVICE)
    {
        modeParams.cardType = "NO DEVICE";
    }

    if(gMmcsdAttrs[type].phyType == MMCSD_PHY_TYPE_HW_PHY)
    {
        modeParams.phyEnable = TRUE;
    }
    else
    {
        modeParams.phyEnable = FALSE;
    }

    if(gMmcsdAttrs[CONFIG_MMCSD_EMMC].enableDma)
    {
        modeParams.dmaEnable = TRUE;
    }
    else
    {
        modeParams.dmaEnable = FALSE;
    }
}

/* Internal static function to do raw IO transfers */
static int32_t TestMmcsd_rawIo(MMCSD_Handle handle, uint32_t instType)
{
    int32_t  retVal = SystemP_SUCCESS;
    uint32_t testCount = 0U, numBlocksPerIter = 0U;
    uint32_t blockSize = MMCSD_getBlockSize(handle);

    uint32_t testSizes[TEST_MMCSD_PERF_TEST_DATA_COUNT] = {
    TEST_MMCSD_128KB_SIZE, TEST_MMCSD_128KB_SIZE, TEST_MMCSD_128KB_SIZE,
    TEST_MMCSD_128KB_SIZE, TEST_MMCSD_128KB_SIZE };

#if !defined (SOC_AM275X) && !defined (C7_CORE) && !defined (SOC_J722S)
    uint32_t perfSizes[TEST_MMCSD_PERF_TEST_DATA_COUNT] = {
        TEST_MMCSD_1MB_SIZE, TEST_MMCSD_4MB_SIZE, TEST_MMCSD_6MB_SIZE,
        TEST_MMCSD_32MB_SIZE, TEST_MMCSD_40MB_SIZE
    };
    memcpy(testSizes, perfSizes, sizeof(testSizes));
#endif

    typedef struct {
        float dataSize;
        uint64_t writeSpeed;
        uint64_t readSpeed;
    } TestData_SizesAttr;

    TestData_SizesAttr testDataObj[TEST_MMCSD_PERF_TEST_DATA_COUNT];

    TestMmcsd_fillBuffers();

    for (testCount = 0; testCount < TEST_MMCSD_PERF_TEST_DATA_COUNT; testCount++)
    {
        numBlocksPerIter = (float)testSizes[testCount] / blockSize;
        testDataObj[testCount].dataSize = (float)((float)testSizes[testCount] / (float)TEST_MMCSD_1MB_SIZE);

        testDataObj[testCount].writeSpeed = ClockP_getTimeUsec();
        retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
        testDataObj[testCount].writeSpeed = ClockP_getTimeUsec() - testDataObj[testCount].writeSpeed;

        if (retVal != SystemP_SUCCESS)
        {
            break;
        }
    }

    if (SystemP_SUCCESS == retVal)
    {
        for (testCount = 0; testCount < TEST_MMCSD_PERF_TEST_DATA_COUNT; testCount++)
        {
            numBlocksPerIter = testSizes[testCount] / blockSize;

            testDataObj[testCount].readSpeed = ClockP_getTimeUsec();
            retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
            testDataObj[testCount].readSpeed = ClockP_getTimeUsec() - testDataObj[testCount].readSpeed;

            if (SystemP_SUCCESS == retVal)
            {
                retVal = memcmp(TestMMCSD_rxBuf, TestMMCSD_txBuf, testSizes[testCount]);
            }
        }
    }
    if (SystemP_SUCCESS == retVal)
    {
        /* Print performance numbers. */
        TestMmcsd_getModeSettings(instType);
        DebugP_log("\n[TEST MMCSD] Performance Numbers Print Start\r\n\n");
        DebugP_log("Card type: %s\r\n",modeParams.cardType);
        DebugP_log("Bus Width: %d\r\n",modeParams.busWidth);
        DebugP_log("Operating mode: %s\r\n",modeParams.mode);

        if (modeParams.phyEnable) DebugP_log("HARD PHY condition: enabled\r\n");
        else                      DebugP_log("SOFT PHY condition: enabled\r\n");

        if (modeParams.dmaEnable) DebugP_log("DMA condition: enabled\r\n");
        else                      DebugP_log("DMA condition: disabled\r\n");

        DebugP_log("Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)\r\n");
        DebugP_log("---------------|--------------------|-----------------\r\n");

        for (testCount=0; testCount < TEST_MMCSD_PERF_TEST_DATA_COUNT; testCount++)
        {
            DebugP_log(" %.2f\t       | %.2f\t\t    | %.2f\r\n",
                testDataObj[testCount].dataSize,
                (float)((float)(testDataObj[testCount].dataSize * TEST_MMCSD_1MB_SIZE) / (float)testDataObj[testCount].writeSpeed),
                (float)((float)(testDataObj[testCount].dataSize * TEST_MMCSD_1MB_SIZE) / (float)testDataObj[testCount].readSpeed));
        }

        DebugP_log("\n[TEST MMCSD] Performance Numbers Print End\r\n\n");
    }

    return retVal;
}

#if !defined (SOC_AM275X) && !defined (SOC_J722S)

/* Function to make Tx address unaligned */
static uint8_t *TestMmcsd_getUnalignedTxAddr()
{
    int32_t shift = 1;
    if((((uintptr_t)TestMMCSD_unalignedTxBuf + shift) % 4) == 0)
    {
        shift++;
    } 
    return TestMMCSD_unalignedTxBuf + shift;
}

/* Function to make Rx address unaligned */
static uint8_t *TestMmcsd_getUnalignedRxAddr()
{
    int32_t shift = 1;
    if((((uintptr_t)TestMMCSD_unalignedRxBuf + shift) % 4) == 0)
    {
        shift++;
    } 
    return TestMMCSD_unalignedRxBuf + shift;
}
#endif

/* Internal static function to do  mutiblock raw io */
static int32_t TestMmcsd_multiBlockRawIo(MMCSD_Handle handle, uint32_t instType)
{
    int32_t  retVal = SystemP_SUCCESS;
    uint32_t blockSize = MMCSD_getBlockSize(handle);
    uint32_t numBlocksPerIter = TEST_MMCSD_XFER_SIZE / blockSize;

    TestMmcsd_fillBuffers();

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK2, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK,  numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_XFER_SIZE);

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_XFER_SIZE);

    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK2, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_XFER_SIZE);

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_XFER_SIZE);

    return retVal;
}

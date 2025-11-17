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

/**\file test_mmcsd_fault_injection.c
 *
 * \brief Test application for MMCSD fault injection.
 *
 * This file contains test routines to validate file input/output functionality
 * using the MMCSD driver in the MCU+ SDK.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdarg.h>
#include "mmcsd_test_common.h"

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

typedef enum
{
    TEST_MMCSD_DATA_NONE_ERROR = 0,
    TEST_MMCSD_DATA_CRC_ERROR,
    TEST_MMCSD_DATA_ENDBIT_ERROR,
    TEST_MMCSD_DATA_TIMEOUT_ERROR,
    TEST_MMCSD_DATA_ADMA_ERROR,
    TEST_MMCSD_CMD_CRC_ERROR,
    TEST_MMCSD_CMD_ENDBIT_ERROR,
    TEST_MMCSD_CMD_INDEX_ERROR,
    TEST_MMCSD_CMD_TIMEOUT_ERROR,
    TEST_MMCSD_EMMC_CID_MONTH_ERROR,
    TEST_MMCSD_EMMC_CID_YEAR_ERROR,
    TEST_MMCSD_EMMC_ECSD_SDREV_ERROR,
    TEST_MMCSD_SD_CSD_CSDVER0_ERROR,
    TEST_MMCSD_SD_CSD_CSDVER2_ERROR,
    TEST_MMCSD_SD_CSD_CSDVER3_ERROR,
    TEST_MMCSD_EMMC_WARM_RST_ERROR,
    TEST_MMCSD_EMMC_DSR_ERROR,
    TEST_MMCSD_EMMC_TUNING_ERROR,
    TEST_MMCSD_ERROR_MAX
} TestMmcsd_errorType;

typedef enum
{
    TEST_MMCSD_NO_XFER_IN_PROGRESS = 0,
    TEST_MMCSD_DATA_XFER_IN_PROGRESS,
    TEST_MMCSD_CMD_XFER_IN_PROGRESS,
    TEST_MMCSD_WARM_RST_XFER_IN_PROGRESS,
    TEST_MMCSD_DSR_XFER_IN_PROGRESS,
    TEST_MMCSD_TUNING_IN_PROGRESS
}TestMmcsd_xferStatus;

/* Global Variable to indicate error type */
volatile TestMmcsd_errorType TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;

/* Global Variable to indicate data transfer in progress */
volatile TestMmcsd_xferStatus TestMMCSD_dataXferStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;

/* Global Variable to indicate command transfer in progress */
volatile TestMmcsd_xferStatus TestMMCSD_cmdXferStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;

/* Global Variable to indicate warm reset transfer in progress */
volatile TestMmcsd_xferStatus TestMMCSD_warmRstXferStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;

/* Global Variable to indicate dsr transfer in progress */
volatile TestMmcsd_xferStatus TestMMCSD_dsrXferStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;

/* Global Variable to indicate tuning in progress */
volatile TestMmcsd_xferStatus TestMMCSD_tuningStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

void TestMmcsd_dataCrcFaultInjection(void *args);
#if defined (SOC_AM62PX)
void TestMmcsd_dataCrcFaultInjectionHS400(void *args);
#endif
void TestMmcsd_dataEBFaultInjection(void *args);
void TestMmcsd_dataTimeOutFaultInjection(void *args);
void TestMmcsd_dataADMAFaultInjection(void *args);
void TestMmcsd_cmdCrcFaultInjection(void *args);
void TestMmcsd_cmdEBFaultInjection(void *args);
void TestMmcsd_cmdIndxFaultInjection(void *args);
void TestMmcsd_cmdTimeOutFaultInjection(void *args);
void TestMmcsd_emmcCIDMonthFaultInjection(void *args);
void TestMmcsd_emmcCIDYearFaultInjection(void *args);
void TestMmcsd_emmcECSDSdRevFaultInjection(void *args);
void TestMmcsd_sdCSDVer0FaultInjection(void *args);
void TestMmcsd_sdCSDVer2FaultInjection(void *args);
void TestMmcsd_sdCSDVer3FaultInjection(void *args);
void TestMmcsd_emmcWarmRstFailFaultInjection(void *args);
void TestMmcsd_emmcDsrFaultInjection(void *args);
void TestMmcsd_emmcTuningFaultInjection(void *args);

/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

/**
* \brief Setup fuction for unity framework
*
* \param None.
*
* \return None.
*/
void setUp(void)
{
    /* Setup function nothing to perform */
}

/**
* \brief Tear down fuction for unity framework
*
* \param None.
*
* \return None.
*/
void tearDown(void)
{
    /* Tear down function nothing to perform */
}

/**
* \brief Main fuction for unity framework
*
* \param None.
*
* \return None.
*/


void test_main(void *args)
{
    Drivers_mmcsdClose();
    UNITY_BEGIN();

    RUN_TEST(TestMmcsd_dataCrcFaultInjection, 8693, NULL);
#if defined (SOC_AM62PX)
    RUN_TEST(TestMmcsd_dataCrcFaultInjectionHS400, 8868, NULL);
#endif
    RUN_TEST(TestMmcsd_dataEBFaultInjection, 8694, NULL);
    RUN_TEST(TestMmcsd_dataTimeOutFaultInjection, 8695, NULL);
    RUN_TEST(TestMmcsd_dataADMAFaultInjection, 8869, NULL);
    RUN_TEST(TestMmcsd_cmdCrcFaultInjection, 8696, NULL);
    RUN_TEST(TestMmcsd_cmdEBFaultInjection, 8697, NULL);
    RUN_TEST(TestMmcsd_cmdIndxFaultInjection, 8698, NULL);
    RUN_TEST(TestMmcsd_cmdTimeOutFaultInjection, 8699, NULL);
    RUN_TEST(TestMmcsd_emmcWarmRstFailFaultInjection, 8327, NULL);
    RUN_TEST(TestMmcsd_emmcDsrFaultInjection, 8321, NULL);
    RUN_TEST(TestMmcsd_emmcTuningFaultInjection, 8000, NULL);
    RUN_TEST(TestMmcsd_emmcCIDMonthFaultInjection, 8320, NULL);
    RUN_TEST(TestMmcsd_emmcCIDYearFaultInjection, 8307, NULL);
    RUN_TEST(TestMmcsd_emmcECSDSdRevFaultInjection, 9246, NULL);
    RUN_TEST(TestMmcsd_sdCSDVer0FaultInjection, 9247, NULL);
    RUN_TEST(TestMmcsd_sdCSDVer2FaultInjection, 9248, NULL);
    RUN_TEST(TestMmcsd_sdCSDVer3FaultInjection, 9249, NULL);

    UNITY_END();

}

/* This is function is used to set data transfer status */
void TestMmcsd_dataFaultInjectInProgress(uint32_t xferStatus)
{
    if(xferStatus == 1)
    {
        TestMMCSD_dataXferStatus = TEST_MMCSD_DATA_XFER_IN_PROGRESS;
    }
    else
    {
        TestMMCSD_dataXferStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;
    }
}

/* This is function is used to set command transfer status */
void TestMmcsd_cmdFaultInjectInProgress(uint32_t xferStatus)
{
    if(xferStatus == 1)
    {
        TestMMCSD_cmdXferStatus = TEST_MMCSD_CMD_XFER_IN_PROGRESS;
    }
    else
    {
        TestMMCSD_cmdXferStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;
    }
}

/* This is function is used to set command transfer status */
void TestMmcsd_warmRstFaultInjectInProgress(uint32_t xferStatus)
{
    if(xferStatus == 1)
    {
        TestMMCSD_warmRstXferStatus = TEST_MMCSD_WARM_RST_XFER_IN_PROGRESS;
    }
    else
    {
        TestMMCSD_warmRstXferStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;
    }
}

/* This is function is used to set command transfer status */
void TestMmcsd_dsrFaultInjectInProgress(uint32_t xferStatus)
{
    if(xferStatus == 1)
    {
        TestMMCSD_dsrXferStatus = TEST_MMCSD_DSR_XFER_IN_PROGRESS;
    }
    else
    {
        TestMMCSD_dsrXferStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;
    }
}

/* This is function is used to set command transfer status */
void TestMmcsd_tuningFaultInjectInProgress(uint32_t xferStatus)
{
    if(xferStatus == 1)
    {
        TestMMCSD_tuningStatus = TEST_MMCSD_TUNING_IN_PROGRESS;
    }
    else
    {
        TestMMCSD_tuningStatus = TEST_MMCSD_NO_XFER_IN_PROGRESS;
    }
}

/* This is function is used to get data transfer status */
int32_t TestMmcsd_isdataFaultInjectInProgress()
{
    int32_t status = 0;
    if(TestMMCSD_dataXferStatus == TEST_MMCSD_DATA_XFER_IN_PROGRESS)
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    return status;
}

/* This is function is used to get command transfer status */
int32_t TestMmcsd_iscmdFaultInjectInProgress()
{
    int32_t status = 0;
    if(TestMMCSD_cmdXferStatus == TEST_MMCSD_CMD_XFER_IN_PROGRESS)
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    return status;
}

/* This is function is used to get command transfer status */
int32_t TestMmcsd_isWarmRstFaultInjectInProgress()
{
    int32_t status = 0;
    if(TestMMCSD_warmRstXferStatus == TEST_MMCSD_WARM_RST_XFER_IN_PROGRESS)
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    return status;
}

/* This is function is used to get command transfer status */
int32_t TestMmcsd_isDsrFaultInjectInProgress()
{
    int32_t status = 0;
    if(TestMMCSD_dsrXferStatus == TEST_MMCSD_DSR_XFER_IN_PROGRESS)
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    return status;
}

/* This is function is used to get tuning  status */
int32_t TestMmcsd_isTuningFaultInjectInProgress()
{
    int32_t status = 0;
    if(TestMMCSD_tuningStatus == TEST_MMCSD_TUNING_IN_PROGRESS)
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    return status;
}

/* This is the handler for injecting faults. Called from the driver */
void TestMmcsd_faultInjectStubHandler(uint32_t numArgs, ...)
{
    va_list args;
    uint16_t *normalVal;
    uint16_t *errVal;
    uint16_t dummyVal = 0;
    
    if(TestMMCSD_currFaultType == TEST_MMCSD_DATA_NONE_ERROR)
    {
        return;
    }

    va_start(args, numArgs);
    
    if(numArgs == 2)
    {
        normalVal = va_arg(args, uint16_t*);
        errVal = va_arg(args, uint16_t*);
    }
    else
    {
        /* Fill the errval with dummy pointer for tests
         * which does not use it.
         */
        normalVal = va_arg(args, uint16_t*);
        errVal = &dummyVal;
    }

    va_end(args);

    switch (TestMMCSD_currFaultType)
    {
        case TEST_MMCSD_DATA_CRC_ERROR:
            if(TestMmcsd_isdataFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting DATA CRC error\n");
                *errVal = (uint16_t)((*errVal) | (uint16_t)CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_CRC_MASK);
                *normalVal &= (uint16_t)~CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_MASK;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_DATA_ENDBIT_ERROR:
            if(TestMmcsd_isdataFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting DATA ENDBIT error\n");
                *errVal = (uint16_t)((*errVal) | (uint16_t)CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_ENDBIT_MASK);
                *normalVal &= (uint16_t)~CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_MASK;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_DATA_TIMEOUT_ERROR:
            if(TestMmcsd_isdataFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting DATA TIMEOUT error\n");
                *errVal = (uint16_t)((*errVal) | (uint16_t)CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_TIMEOUT_MASK);
                *normalVal &= (uint16_t)~CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_MASK;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_DATA_ADMA_ERROR:
            if(TestMmcsd_isdataFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting DATA ADMA error\n");
                *errVal = (uint16_t)((*errVal) | (uint16_t)CSL_MMC_CTLCFG_ERROR_INTR_STS_ADMA_MASK);
                *normalVal &= (uint16_t)~CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_MASK;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_CMD_CRC_ERROR:
            if(TestMmcsd_iscmdFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting CMD CRC error\n");
                *errVal = (uint16_t)((*errVal) | (uint16_t)CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_CRC_MASK);
                *normalVal &= (uint16_t)~CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_MASK;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_CMD_ENDBIT_ERROR:
            if(TestMmcsd_iscmdFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting CMD ENDBIT error\n");
                *errVal = (uint16_t)((*errVal) | (uint16_t)CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_ENDBIT_MASK);
                *normalVal &= (uint16_t)~CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_MASK;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_CMD_INDEX_ERROR:
            if(TestMmcsd_iscmdFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting CMD INDEX error\n");
                *errVal = (uint16_t)((*errVal) | (uint16_t)CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_INDEX_MASK);
                *normalVal &= (uint16_t)~CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_MASK;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_CMD_TIMEOUT_ERROR:
            if(TestMmcsd_iscmdFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting CMD TIMEOUT error\n");
                *errVal = (uint16_t)((*errVal) | (uint16_t)CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_TIMEOUT_MASK);
                *normalVal &= (uint16_t)~CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_MASK;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_EMMC_CID_MONTH_ERROR:
            DebugP_log("Injecting MMCSD EMMC CID month error\n");
            *normalVal = 13;
            TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            break;

        case TEST_MMCSD_EMMC_CID_YEAR_ERROR:
            DebugP_log("Injecting MMCSD EMMC CID year error\n");
            *normalVal = 18;
            TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            break;

        case TEST_MMCSD_EMMC_ECSD_SDREV_ERROR:
            DebugP_log("Injecting MMCSD EMMC sdrev error\n");
            *normalVal = 2;
            TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            break;

        case TEST_MMCSD_SD_CSD_CSDVER0_ERROR:
            DebugP_log("Injecting MMCSD SD CSD csd version 0 error\n");
            *normalVal = 0;
            TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            break;

        case TEST_MMCSD_SD_CSD_CSDVER2_ERROR:
            DebugP_log("Injecting MMCSD SD CSD csd version 2 error\n");
            *normalVal = 2;
            TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            break;

        case TEST_MMCSD_SD_CSD_CSDVER3_ERROR:
            DebugP_log("Injecting MMCSD SD CSD csd version 3 error\n");
            *normalVal = 3;
            TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            break;

        case TEST_MMCSD_EMMC_WARM_RST_ERROR:
            if(TestMmcsd_isWarmRstFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting MMCSD EMMC warm reset error\n");
                *normalVal = 1;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_EMMC_DSR_ERROR:
            if(TestMmcsd_isDsrFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting MMCSD EMMC dsr error\n");
                *normalVal = 1;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        case TEST_MMCSD_EMMC_TUNING_ERROR:
            if(TestMmcsd_isTuningFaultInjectInProgress() == 1)
            {
                DebugP_log("Injecting MMCSD EMMC tuning error\n");
                *normalVal = 0;
                TestMMCSD_currFaultType = TEST_MMCSD_DATA_NONE_ERROR;
            }
            break;

        default:
            DebugP_log("Unknown fault type: %d\n", TestMMCSD_currFaultType);
            break;
    }
}

/**
 * \brief Test to create data CRC error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when data CRC error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */

void TestMmcsd_dataCrcFaultInjection(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    MMCSD_Handle handle;
    uint32_t blockSize;
    uint32_t numBlocksPerIter;

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    blockSize = MMCSD_getBlockSize(handle);
    numBlocksPerIter = TEST_MMCSD_DATA_SIZE / blockSize;

    TestMmcsd_fillBuffers();

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, retVal);

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_DATA_CRC_ERROR;
    
    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_DATA_SIZE);
    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_DATA_SIZE);

    /* cleanup */
    Drivers_mmcsdClose();
}

#if defined (SOC_AM62PX)
/**
 * \brief Test to create data CRC error for HS400 mode
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when data CRC error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */

void TestMmcsd_dataCrcFaultInjectionHS400(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    MMCSD_Handle handle;
    uint32_t blockSize;
    uint32_t numBlocksPerIter;

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[3];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    blockSize = MMCSD_getBlockSize(handle);
    numBlocksPerIter = TEST_MMCSD_DATA_SIZE / blockSize;

    TestMmcsd_fillBuffers();

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, retVal);

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_DATA_CRC_ERROR;
    
    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_DATA_SIZE);
    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_DATA_SIZE);

    /* cleanup */
    Drivers_mmcsdClose();
}
#endif
/**
 * \brief Test to create data endbit  error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when data end bit error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_dataEBFaultInjection(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    MMCSD_Handle handle;
    uint32_t blockSize;
    uint32_t numBlocksPerIter;

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    blockSize = MMCSD_getBlockSize(handle);
    numBlocksPerIter = TEST_MMCSD_DATA_SIZE / blockSize;

    TestMmcsd_fillBuffers();

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, retVal);

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_DATA_ENDBIT_ERROR;

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_DATA_SIZE);
    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_DATA_SIZE);

    /* cleanup */
    Drivers_mmcsdClose();
}

/**
 * \brief Test to create data time out  error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when data time out error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_dataTimeOutFaultInjection(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    MMCSD_Handle handle;
    uint32_t blockSize;
    uint32_t numBlocksPerIter;

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    blockSize = MMCSD_getBlockSize(handle);
    numBlocksPerIter = TEST_MMCSD_DATA_SIZE / blockSize;

    TestMmcsd_fillBuffers();

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, retVal);

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_DATA_TIMEOUT_ERROR;

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_DATA_SIZE);
    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_DATA_SIZE);

    /* cleanup */
    Drivers_mmcsdClose();
}

/**
 * \brief Test to create data ADMA  error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when data ADMA error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_dataADMAFaultInjection(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    MMCSD_Handle handle;
    uint32_t blockSize;
    uint32_t numBlocksPerIter;

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];
    blockSize = MMCSD_getBlockSize(handle);
    numBlocksPerIter = TEST_MMCSD_DATA_SIZE / blockSize;

    TestMmcsd_fillBuffers();

    retVal = MMCSD_write(handle, TestMMCSD_txBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, retVal);

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_DATA_ADMA_ERROR;

    memset(TestMMCSD_rxBuf, 0, TEST_MMCSD_DATA_SIZE);
    retVal = MMCSD_read(handle, TestMMCSD_rxBuf, TEST_MMCSD_EMMC_START_BLK, numBlocksPerIter);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    TEST_ASSERT_EQUAL_MEMORY(TestMMCSD_txBuf, TestMMCSD_rxBuf, TEST_MMCSD_DATA_SIZE);

    /* cleanup */
    Drivers_mmcsdClose();
}

/**
 * \brief Test to create command CRC error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when command CRC error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_cmdCrcFaultInjection(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    MMCSD_Handle handle;

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_CMD_CRC_ERROR;

    retVal = MMCSD_enableBootPartition(handle, 1);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* cleanup */
    Drivers_mmcsdClose();
}

/**
 * \brief Test to create command end bit error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when command end bit error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_cmdEBFaultInjection(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    MMCSD_Handle handle;

    /* cleanup as previous test case fails */
    Drivers_mmcsdClose();

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_CMD_ENDBIT_ERROR;

    retVal = MMCSD_enableBootPartition(handle, 1);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* cleanup */
    Drivers_mmcsdClose();
}

/**
 * \brief Test to create command index error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when command index error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_cmdIndxFaultInjection(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    MMCSD_Handle handle;

    /* cleanup as previous test case fails */
    Drivers_mmcsdClose();

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_CMD_INDEX_ERROR;

    retVal = MMCSD_enableBootPartition(handle, 1);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* cleanup */
    Drivers_mmcsdClose();
}

/**
 * \brief Test to create command time out error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when command time out error happens
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_cmdTimeOutFaultInjection(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    MMCSD_Handle handle;

    /* cleanup as previous test case fails */
    Drivers_mmcsdClose();

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    Drivers_mmcsdOpen();
    handle = gMmcsdHandle[CONFIG_MMCSD_EMMC];

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_CMD_TIMEOUT_ERROR;

    retVal = MMCSD_enableBootPartition(handle, 1);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
    retVal = MMCSD_disableBootPartition(handle);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* cleanup */
    Drivers_mmcsdClose();
}

/**
 * \brief Test to create CID month error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when month code is wrong in the emmc.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcCIDMonthFaultInjection(void *args)
{
    MMCSD_Handle handle;

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_EMMC_CID_MONTH_ERROR;
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    handle = MMCSD_open(0, &gMmcsdParams[0]);
    TEST_ASSERT_NOT_NULL(handle);

    /* cleanup */
    MMCSD_close(handle);
}

/**
 * \brief Test to create CID year error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when year code is wrong in the emmc.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcCIDYearFaultInjection(void *args)
{
    MMCSD_Handle handle;

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_EMMC_CID_YEAR_ERROR;
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    handle = MMCSD_open(0, &gMmcsdParams[0]);
    TEST_ASSERT_NOT_NULL(handle);

    /* cleanup */
    MMCSD_close(handle);
}

/**
 * \brief Test to create CID year error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when ECSD sd revision is wrong in the emmc.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcECSDSdRevFaultInjection(void *args)
{
    MMCSD_Handle handle;

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_EMMC_ECSD_SDREV_ERROR;
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    handle = MMCSD_open(0, &gMmcsdParams[0]);
    TEST_ASSERT_NOT_NULL(handle);

    /* cleanup */
    MMCSD_close(handle);
}

/**
 * \brief Test to create EMMC warm reset error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when warm reset fails for emmc.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcWarmRstFailFaultInjection(void *args)
{
    MMCSD_Handle handle;

    /* cleanup as previous test case fails */
    Drivers_mmcsdClose();

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_EMMC_WARM_RST_ERROR;
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    handle = MMCSD_open(0, &gMmcsdParams[0]);
    TEST_ASSERT_NOT_NULL(handle);

    /* cleanup */
    MMCSD_close(handle);
}

/**
 * \brief Test to create EMMC DSR 
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when emmc supports DSR.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcDsrFaultInjection(void *args)
{
    MMCSD_Handle handle;

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_EMMC_DSR_ERROR;
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    handle = MMCSD_open(0, &gMmcsdParams[0]);
    TEST_ASSERT_NOT_NULL(handle);

    /* cleanup */
    MMCSD_close(handle);
}

/**
 * \brief Test to create EMMC tuning error 
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver returns
 * SystemP_FAILURE on.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_emmcTuningFaultInjection(void *args)
{
    MMCSD_Handle handle;

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_EMMC_TUNING_ERROR;
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[2];
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].tuningType = MMCSD_PHY_TUNING_TYPE_AUTO;
    handle = MMCSD_open(0, &gMmcsdParams[0]);
    TEST_ASSERT_NULL(handle);

    /* cleanup */
    MMCSD_close(handle);
    gMmcsdAttrs[CONFIG_MMCSD_EMMC].tuningType = MMCSD_PHY_TUNING_TYPE_MANUAL;
}

/**
 * \brief Test to create CSD version error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers CSD versionn is wrong in the SD.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_sdCSDVer0FaultInjection(void *args)
{
    MMCSD_Handle handle;

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_SD_CSD_CSDVER0_ERROR;
    gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[0];
    handle = MMCSD_open(1, &gMmcsdParams[1]);
    TEST_ASSERT_NOT_NULL(handle);

    /* cleanup */
    MMCSD_close(handle);
}

/**
 * \brief Test to create CSD version error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when CSD versio is wrong in SD.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_sdCSDVer2FaultInjection(void *args)
{
    MMCSD_Handle handle;

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_SD_CSD_CSDVER2_ERROR;
    gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[0];
    handle = MMCSD_open(1, &gMmcsdParams[1]);
    TEST_ASSERT_NOT_NULL(handle);

    /* cleanup */
    MMCSD_close(handle);
}

/**
 * \brief Test to create CSD version error
 *
 * Test Category: Fault injection test.
 *
 * This function verifies that the MMCSD driver correctly
 * handles data transfers when CSD versio is wrong in SD.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */
void TestMmcsd_sdCSDVer3FaultInjection(void *args)
{
    MMCSD_Handle handle;

    /* Set the fault flag */
    TestMMCSD_currFaultType = TEST_MMCSD_SD_CSD_CSDVER3_ERROR;
    gMmcsdAttrs[CONFIG_MMCSD_SD].supportedModes = TestMMCSD_sdModes[0];
    handle = MMCSD_open(1, &gMmcsdParams[1]);
    TEST_ASSERT_NOT_NULL(handle);

    /* cleanup */
    MMCSD_close(handle);

}

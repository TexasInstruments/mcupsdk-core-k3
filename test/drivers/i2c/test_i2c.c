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

/*  \file   test_i2c.c
 *
 *
 *   \brief  I2C Driver Unit Test File
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/i2c.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include <kernel/dpl/ClockP.h>
#include <drivers/pinmux.h>
#include <drivers/i2c/v0/lld/i2c_lld.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <drivers/hw_include/hw_types.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define NON_EXISTENT_DEVICE_ADDRESS (0x01U)
#define APP_I2C_BUFSIZE (300U)
#define I2C_DELAY_SMALL ((uint32_t) 5000U)
#define INVALID_FREQ (100)
#define DEFAULT   (0U)
#define NULL_HANDLE (1U)
#define BUS_BUSY (2U)
#define TESTCASE_RD_WR_BUSFREQ  (0U)
#define TESTCASE_RD_WR_TIMEOUT  (1U)
#define TESTCASE_RD_WR_INVALIDADDR  (2U)
#define DEFAULT_MEM_TRANSACTION    (0U)
#define INVALID_MEM_ADDR_SIZE    (1U)
#define INVALID_MEM_PARAMS    (2U)
#define TX   (1U)
#define RX   (0U)
#define TEST_I2C_FUZZ_ITERATIONS       5
#define TEST_I2C_CB_QUEUE_TEST_DEPTH   (5U)
#if defined ENABLE_MT_TESTS
#define TEST_I2C_WRITE_THREADS      2
#define TEST_I2C_CB_MT_BYTES        8
#define TEST_I2C_WRITE_ITER         1
#if defined C7X_CORE
#define TEST_I2C_MT_TASK_STACK_SIZE   (1024 * 40)
#else
#define TEST_I2C_MT_TASK_STACK_SIZE   (6 * 1024)
#endif
#endif
#define TEST_I2C_TMP100_TEMP_SHIFT        (4)
#define TEST_I2C_TMP100_SIGN_EXTEND_MASK  (0xF000)
#define TEST_I2C_TMP100_TEMP_DIV          (16)
#define TEST_I2C_TMP100_TEMP_FRAC_SCALE   (625)
#define TEST_I2C_TMP100_SIGN_BIT          (0x80)
#define TEST_I2C_TMP100_SIGN_BIT_POS      (8)
#define TEST_I2C_PERF_TEST_DATA_COUNT   (1U)
/* Payload sizes (data bytes excluding EEPROM address bytes) */
#define TEST_I2C_64B_SIZE    (64U)
#define TEST_I2C_128B_SIZE   (128U)
#define TEST_I2C_256B_SIZE   (256U)
#define TEST_I2C_PERF_NUM_SIZES 3
#define TEST_I2C_SMALL_SZ 1U
#define TEST_I2C_LARGE_SZ 64U
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Structure for I2C probe test settings.
 *
 * Holds parameters for configuring and tracking I2C bus probe operations,
 * including the I2C instance to probe and the number of actual device addresses found.
 */

typedef struct I2C_ProbeSettings_s {

    uint8_t instance;
    uint8_t numActualAddresses;

} I2C_ProbeSettings;

/**
 * \brief  Structure containing parameters for I2C test cases.
 *
 * This structure holds configuration and runtime parameters used for
 * executing various I2C driver test scenarios, including memory address,
 * device address, number of bytes to transfer, frequency settings, and
 * interrupt enable flags.
 */

typedef struct I2C_TestParams_s {

    I2C_Params  i2cParams;
    uint16_t memAddress;
    uint8_t deviceAddress;
    uint8_t numBytes;
    uint8_t numWritesReads;
    bool testSetFrequency;
    bool intrEnable;

} I2C_TestParams;

typedef struct
{
    int32_t threadId;
    I2C_Handle handle;
} TestI2cThreadArgs;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern I2C_Config gI2cConfig[];
SemaphoreP_Object gTestI2cCallbackDoneSemObj;
uint8_t gI2cTxBuffer[APP_I2C_BUFSIZE];
uint8_t gI2cRxBuffer[APP_I2C_BUFSIZE];
#if defined ENABLE_MT_TESTS
uint8_t TestI2c_task1Stack[TEST_I2C_WRITE_THREADS][TEST_I2C_MT_TASK_STACK_SIZE];
uint8_t TestI2c_task2Stack[TEST_I2C_WRITE_THREADS][TEST_I2C_MT_TASK_STACK_SIZE];
TaskP_Object TestI2c_TaskObjs[TEST_I2C_WRITE_THREADS];
static SemaphoreP_Object TestI2c_testSem;
TaskP_Object TestI2c_taskObjsEepromTemp[2];
static I2C_Handle TestI2c_SharedHandle = NULL;
#endif
static volatile uint32_t TestI2c_CbQueuePos;
static uint8_t TestI2c_CbQueueOrder[TEST_I2C_CB_QUEUE_TEST_DEPTH];
#if (defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62X)) && defined(ENABLE_TARGET_EXTERNAL_LOOPBACK)
static SemaphoreP_Object TestI2c_TargetSem;
static uint8_t TestI2c_controllerTxBuf[8];
static uint8_t TestI2c_controllerRxBuf[8];
static uint8_t TestI2c_targetRxBuf[8];
static uint8_t TestI2c_targetTxBuf[8];
#endif
int32_t Test_I2cErrorStat;
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Testcases */
static void test_i2c_write_read(void* args);
static int32_t test_i2c_write_read_mem(void* args);
static void test_i2c_probe(void* args);
static void test_i2c_callback_mode(void* args);
static void test_i2c_timeout(void* args);
static void test_i2c_open_close(void* args);
static void test_i2c_error_nack(void* args);

/* Helpers */
#if (!defined(C7X_CORE))
void test_i2c_dynamic_coverage(void* args);
#endif
static int32_t test_i2c_timeout_negative(void);
static int32_t test_i2c_error_checks(void);
static int32_t test_i2c_open_error(void);
static int32_t test_i2c_recover_bus(void);
static int32_t test_i2c_baseaddress(uint32_t baseAddr);
static int32_t test_i2c_lld(void);
static int32_t test_i2c_differentSpeeds(uint8_t freq, uint8_t testCase);
static int32_t test_i2c_handle_errors(void);
static int32_t test_i2c_memparams(void *args, uint32_t testcase, bool mode);
static int32_t test_i2c_write_read_mem_error_checks(void* args, uint8_t testCase);
static void test_i2c_set_test_params(I2C_TestParams *testParams, int8_t setting_id);
static void test_i2c_callback(I2C_Handle i2cHnd, I2C_Transaction * msg, int32_t transferStatus);
static int32_t test_i2c_nack_error_check(void* args);
static void TestI2c_eepromReadWithoutAddressWrite(void* args);
void TestI2c_sclStuckRecoverBusWithSystestFault(void* args);
void TestI2c_sdaStuckRecoverBusWithSystestFault(void* args);
static void TestI2c_eepromPageOverflow(void *args);
static void TestI2c_perfWriteReadDiffFreq(void* args);
static void TestI2c_openCloseFuzzRand(void *args);
#if defined ENABLE_MT_TESTS
#if defined(SOC_AM62DX)
static void TestI2c_multithreadSharedEepromTemp(void *args);
#endif
#if defined(SOC_AM62AX) || defined (SOC_AM62PX) || defined(SOC_AM62X)
static void TestI2c_multithreadWriteTestSharedOpenCb(void* args);
static void TestI2c_multithreadReadTestSharedOpen(void* args);
static void TestI2c_multithreadWriteRead(void* args);
static void TestI2c_callbackMultithreadWriteTest(void* args);
static void TestI2c_multithreadEepromAndTemp(void *args);
static void TestI2c_tempTask(void *arg);
#endif
#endif
#if (defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62X)) && defined(ENABLE_TARGET_EXTERNAL_LOOPBACK)
static void TestI2c_targetModeWriteSeq(void* args);
static void TestI2c_targetModeCombinedWriteRead(void *args);
static void TestI2c_targetModehostControllerRead(void *args);
static void TestI2c_targetXrdyOverrun(void *args);
static void TestI2c_target_RrdyUnderrun(void *args);
static void TestI2c_targetMultiplehostControllerReads(void *args);
static void TestI2c_targetModehostControllerRead10bit(void *args);
static void TestI2c_targetModehostControllerReadHs(void *args);
static void TestI2c_MemPrimeTransferTargetModeViaTransfer(void *args);
void TestI2c_targetMode10bit7bit(void *args);
void TestI2c_targetModeMultiOwnAddr(void* args);
#endif
static void TestI2c_targetModePollingNegative(void *args);
static void TestI2c_openWithoutDriverLock(void *args);
static void TestI2c_openNullObject(void *args);
static void TestI2c_transferTimeoutBlockingMode(void *args);
static void TestI2c_recoverbusNullObject(void *args);
static void TestI2c_memPrimeTransferInvalidDir(void *args);
void TestI2c_callbackQueueDepth(void* args);
void TestI2c_fifoMgmtTxRxModes(void *args);
static void TestI2c_controllerTxUnderflow(void* args);
static void TestI2c_pollingNackWrite(void *args);
static void TestI2c_pollingNackRead(void *args);
void TestI2c_controllerRxOverrun(void *args);
void TestI2c_controllerAccessError(void *args);

/* ========================================================================== */
/*                            Global Functions                                */
/* ========================================================================== */

uint8_t Board_i2cGetEepromDeviceAddr();
uint16_t Board_i2cGetEepromMemAddr();
uint8_t Board_i2cGetEepromAddrSize();
uint8_t Board_getSocTemperatureSensorAddr(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    I2C_TestParams      testParams;
    I2C_ProbeSettings   probeSettings;
    uint8_t             i;

    UNITY_BEGIN();

    test_i2c_set_test_params(&testParams, 0);
    RUN_TEST(test_i2c_write_read, 1311, (void*)&testParams);
    test_i2c_set_test_params(&testParams, 1);
    RUN_TEST(test_i2c_write_read, 1312, (void*)&testParams);

    test_i2c_set_test_params(&testParams, 2);
    RUN_TEST(test_i2c_write_read, 1313, (void*)&testParams);

    test_i2c_set_test_params(&testParams, 3);
    RUN_TEST(test_i2c_write_read, 1314, (void*)&testParams);

    test_i2c_set_test_params(&testParams, 4);
    RUN_TEST(test_i2c_write_read, 1315, (void*)&testParams);
    for (i=0; i<CONFIG_I2C_NUM_INSTANCES; i++)
    {
        probeSettings.instance = i;
        RUN_TEST(test_i2c_probe, 1316 + i, (void*)&probeSettings);
    }
    RUN_TEST(test_i2c_callback_mode, 1317, NULL);
    RUN_TEST(test_i2c_open_close, 1318, NULL);
    RUN_TEST(test_i2c_timeout, 1319, NULL);
    /* Polling mode test */
    test_i2c_set_test_params(&testParams, 5);
    RUN_TEST(test_i2c_write_read, 1320, (void*)&testParams);
    /* Error Nack test */
    RUN_TEST(test_i2c_error_nack, 6849, (void*)&testParams);
    /* Hw Intr mode I2C_lld_mem_writeIntr*/
    test_i2c_set_test_params(&testParams, 0);

    RUN_TEST(test_i2c_write_read, 6248, (void*)&testParams);
    test_i2c_set_test_params(&testParams, 0);
    RUN_TEST(TestI2c_eepromReadWithoutAddressWrite, 8883, NULL);
    test_i2c_set_test_params(&testParams, 0);
    RUN_TEST(TestI2c_eepromPageOverflow, 8318,(void*)&testParams);
    test_i2c_set_test_params(&testParams, 0);
    RUN_TEST(TestI2c_perfWriteReadDiffFreq, 8319, (void*)&testParams);
    RUN_TEST(TestI2c_openCloseFuzzRand, 8322, (void*)&testParams);

    #if defined ENABLE_MT_TESTS
    #if defined(SOC_AM62DX)
    RUN_TEST(TestI2c_multithreadSharedEepromTemp, 8338, (void*)&testParams);
    #endif
    #if defined(SOC_AM62AX) || defined (SOC_AM62PX) || defined(SOC_AM62X)
    RUN_TEST(TestI2c_multithreadWriteTestSharedOpenCb, 8586, (void*)&testParams);
    RUN_TEST(TestI2c_multithreadReadTestSharedOpen, 8587, (void*)&testParams);
    RUN_TEST(TestI2c_multithreadWriteRead, 8324,(void*)&testParams);
    RUN_TEST(TestI2c_callbackMultithreadWriteTest, 8325,(void*)&testParams);
    RUN_TEST(TestI2c_multithreadEepromAndTemp,8326,(void*)&testParams);
    #endif
    #endif
    #if (defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62X)) && defined(ENABLE_TARGET_EXTERNAL_LOOPBACK)
    test_i2c_set_test_params(&testParams, 0);
    RUN_TEST(TestI2c_targetModeWriteSeq, 8328, (void*)&testParams);
    RUN_TEST(TestI2c_targetModeCombinedWriteRead,8330,(void*)&testParams);
    RUN_TEST(TestI2c_targetModehostControllerRead,8331,(void*)&testParams);
    RUN_TEST(TestI2c_target_RrdyUnderrun, 8332, (void*)&testParams);
    RUN_TEST(TestI2c_targetMultiplehostControllerReads, 8333, (void*)&testParams);
    RUN_TEST(TestI2c_targetModehostControllerRead10bit, 8335, (void*)&testParams);
    RUN_TEST(TestI2c_targetModehostControllerReadHs, 8336, (void*)&testParams);
    RUN_TEST(TestI2c_MemPrimeTransferTargetModeViaTransfer, 8621, (void*)&testParams);
    RUN_TEST(TestI2c_targetMode10bit7bit, 8700, NULL);
    RUN_TEST(TestI2c_targetModeMultiOwnAddr, 8701, NULL);
    RUN_TEST(TestI2c_targetXrdyOverrun, 8622, (void*)&testParams);
    #endif
    RUN_TEST(TestI2c_transferTimeoutBlockingMode, 8623, (void*)&testParams);
    RUN_TEST(TestI2c_sclStuckRecoverBusWithSystestFault, 8334, NULL);
    RUN_TEST(TestI2c_openNullObject, 8624, NULL);
    RUN_TEST(TestI2c_recoverbusNullObject, 8625, NULL);
    #if (!defined(C7X_CORE))
    RUN_TEST(test_i2c_dynamic_coverage, 6605, NULL);
    #endif
    RUN_TEST(TestI2c_targetModePollingNegative, 8627, NULL);
    RUN_TEST(TestI2c_openWithoutDriverLock, 8628, NULL);
    RUN_TEST(TestI2c_fifoMgmtTxRxModes, 8702,NULL);
    RUN_TEST(TestI2c_controllerTxUnderflow, 8703, (void*)&testParams);
    RUN_TEST(TestI2c_pollingNackRead, 8705, NULL);
    RUN_TEST(TestI2c_pollingNackWrite, 8704, NULL);
    RUN_TEST(TestI2c_controllerAccessError, 8720, NULL);
    RUN_TEST(TestI2c_controllerRxOverrun, 8721, NULL);
    /* Below test cases are get stcuk in driver  */
    /* RUN_TEST(TestI2c_callbackQueueDepth, 8631, NULL); */
    RUN_TEST(TestI2c_sdaStuckRecoverBusWithSystestFault, 8630 ,NULL);
    RUN_TEST(TestI2c_memPrimeTransferInvalidDir, 8626, NULL);

#if defined(SOC_J722S)
    RUN_TEST(test_i2c_write_read, 18763, (void*)&testParams);

    RUN_TEST(test_i2c_dynamic_coverage, 18762, NULL);
#endif

    I2C_deinit();

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
 * Testcases
 */

/**
 * \brief  Writes bytes to the EEPROM and reads them back.
 *
 * This test case writes a sequence of bytes to the EEPROM and then reads them back
 * to verify correct I2C operation. It supports polling and interrupt modes, and
 * can set the bus frequency as part of the test.
 */
static void test_i2c_write_read(void* args)
{
    I2C_TestParams *testParams = (I2C_TestParams*)args;
    I2C_Params     *i2cParams = &(testParams->i2cParams);
    uint32_t        i;
    uint32_t        loopCount;
    int32_t         status;
    I2C_Handle      i2cHandle;
    I2C_Transaction i2cTransaction;
    I2C_HwAttrs  *hwAttrs = NULL;

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    /* Disable interrupt registration in case of polling */
    if (testParams->intrEnable == false)
    {
        hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
        hwAttrs->enableIntr = FALSE;
    }


    i2cHandle = I2C_open(CONFIG_I2C0, i2cParams);
    TEST_ASSERT_NOT_NULL(i2cHandle);

    if (testParams->testSetFrequency)
    {
        status = I2C_setBusFrequency(i2cHandle, I2C_400KHZ);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }


    for (loopCount=0; loopCount<testParams->numWritesReads; loopCount++)
    {
        for (i=0; i<testParams->numBytes; i++)    /* Data Bytes */
        {
            gI2cTxBuffer[i+Board_i2cGetEepromAddrSize()] = i;
            gI2cRxBuffer[i] = 0;
        }

        /* Writing to EEPROM */
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.writeBuf   = gI2cTxBuffer;
        i2cTransaction.writeCount = Board_i2cGetEepromAddrSize() + testParams->numBytes;
        i2cTransaction.targetAddress = testParams->deviceAddress;

        if(Board_i2cGetEepromAddrSize()==0x01U)
        {
			gI2cTxBuffer[0] = (uint8_t)(testParams->memAddress);	/* Address Byte */
        }
        else
        {
			gI2cTxBuffer[0] = (uint8_t)(testParams->memAddress >> 8);     /* Address Byte 1 */
            gI2cTxBuffer[1] = (uint8_t)(testParams->memAddress & 0x00FF); /* Address Byte 2 */
        }

		/* To ensure that eeprom is ready, added delay of 4ms */
		ClockP_usleep(4000);
        status = I2C_transfer(i2cHandle, &i2cTransaction);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* After write operation flash will not respond for write cycle time.
         * This is approximately 4ms (min). */
        ClockP_usleep(5000);

        /* wait for write to finish */
        /* Dummy write to set the address to be read from */
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.writeBuf   = gI2cTxBuffer;
        i2cTransaction.writeCount = Board_i2cGetEepromAddrSize();
        i2cTransaction.readBuf    = gI2cRxBuffer;
        i2cTransaction.readCount  = 1;
        i2cTransaction.targetAddress = testParams->deviceAddress;

        /* wait for previous write to complete */
        do
        {
            status = I2C_transfer(i2cHandle, &i2cTransaction);
            if(status==I2C_STS_ERR_NO_ACK)
            {
                /* previous write is not yet complete, try again */
            }
        } while(status == I2C_STS_ERR_NO_ACK);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        ClockP_usleep(4000);

        /* Read from EEPROM */
        /* Actual read from the address */
        I2C_Transaction_init(&i2cTransaction);
        i2cTransaction.writeBuf   = gI2cTxBuffer;
        i2cTransaction.writeCount = Board_i2cGetEepromAddrSize();
        i2cTransaction.readBuf   = gI2cRxBuffer;
        i2cTransaction.readCount = testParams->numBytes;
        i2cTransaction.targetAddress = testParams->deviceAddress;

        status = I2C_transfer(i2cHandle, &i2cTransaction);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        TEST_ASSERT_EQUAL_UINT8_ARRAY(gI2cTxBuffer+Board_i2cGetEepromAddrSize(),
            gI2cRxBuffer, testParams->numBytes);
    }

    I2C_close(i2cHandle);

    return;
}

/**
 * \brief  Test I2C probe against schematic addresses.
 *
 * This test verifies that the I2C probe function returns device addresses
 * that match those specified in the hardware schematic. It ensures correct
 * detection and communication with expected I2C devices on the bus.
 */
static void test_i2c_probe(void* args)
{
    I2C_ProbeSettings   *probeSettings = (I2C_ProbeSettings*)args;
    I2C_Params          i2cParams;
    I2C_Handle          i2cHandle;
    uint8_t             probeDeviceAddr;
    int32_t             status;

    I2C_close(gI2cHandle[probeSettings->instance]);

    I2C_Params_init(&i2cParams);
    i2cHandle = I2C_open(probeSettings->instance, &i2cParams);
    TEST_ASSERT_NOT_NULL(i2cHandle);

    for(probeDeviceAddr = 0; probeDeviceAddr <= 0x7F; probeDeviceAddr++)
    {
        ClockP_usleep(5);
        status = I2C_probe(i2cHandle, probeDeviceAddr);
        if(status == SystemP_SUCCESS)
        {
            DebugP_log("Found device at address 0x%08x\r\n", probeDeviceAddr);
        }
    }
    I2C_close(i2cHandle);
    return;
}

/**
 * \brief  Test function for I2C callback mode.
 *
 * This test demonstrates the usage of I2C in callback mode.
 * It initializes the I2C parameters and performs operations as required
 * for testing the callback mechanism.
 */
static void test_i2c_callback_mode(void* args)
{
    I2C_Params      i2cParams;
    uint8_t         txBuffer1[3];
    uint8_t         txBuffer2[3];
    int32_t         status;
    I2C_Handle      i2cHandle;
    I2C_Transaction i2cTransaction;

    I2C_close(gI2cHandle[CONFIG_I2C0]);
    SemaphoreP_constructBinary(&gTestI2cCallbackDoneSemObj, 0);

    I2C_Params_init(&i2cParams);
    i2cParams.transferMode = I2C_MODE_CALLBACK;
    i2cParams.transferCallbackFxn = &test_i2c_callback;
    i2cHandle = I2C_open(CONFIG_I2C0, &i2cParams);
    TEST_ASSERT_NOT_NULL(i2cHandle);

    /* Writing to EEPROM */
    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = txBuffer1;
    i2cTransaction.writeCount = 3;
    i2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
    i2cTransaction.arg = NULL;

    if (Board_i2cGetEepromAddrSize()==0x01U)
    {
		txBuffer1[0] = (uint8_t)(Board_i2cGetEepromMemAddr());    /* Address Byte */
		txBuffer1[1] = 0x12;
    }
    else
    {
		txBuffer1[0] = (uint8_t)(Board_i2cGetEepromMemAddr() >> 8);     /* Address Byte 1 */
        txBuffer1[1] = (uint8_t)(Board_i2cGetEepromMemAddr() & 0x00FF); /* Address Byte 2 */
        txBuffer1[2] = 0x12;
    }

	status = I2C_transfer(i2cHandle, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Read from EEPROM */
    /* Dummy write to set the address to be read from */
    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = txBuffer2;
    i2cTransaction.writeCount = 2;
    i2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
    i2cTransaction.arg = &gTestI2cCallbackDoneSemObj;

    if(Board_i2cGetEepromAddrSize()==0x01)
    {
		txBuffer2[0] = (uint8_t)((Board_i2cGetEepromMemAddr()+1));     /* Address Byte */
        txBuffer2[1] = 0x34;
    }
    else
    {
		txBuffer2[0] = (uint8_t)((Board_i2cGetEepromMemAddr()+1) >> 8);     /* Address Byte 1 */
        txBuffer2[1] = (uint8_t)((Board_i2cGetEepromMemAddr()+2) & 0x00FF); /* Address Byte 2 */
		txBuffer2[2] = 0x34;
    }

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_pend(&gTestI2cCallbackDoneSemObj, SystemP_WAIT_FOREVER);

    I2C_close(i2cHandle);

    SemaphoreP_destruct(&gTestI2cCallbackDoneSemObj);
    return;
}

/**
 * \brief  Test I2C callback mode operation.
 *
 * This test verifies the I2C driver's callback mode by performing a write and read
 * operation to the EEPROM using callback-based transfers. It checks that the callback
 * is invoked and the data is correctly transferred.
 */
static void test_i2c_timeout(void* args)
{
    I2C_Handle          i2cHandle;
    I2C_Params          params;
    I2C_Transaction     transaction;
    uint8_t             txBuffer;
    int32_t             status;

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    I2C_Params_init(&params);
    params.bitRate = I2C_400KHZ;
    i2cHandle = I2C_open(CONFIG_I2C0, &params);

    I2C_Transaction_init(&transaction);
    transaction.timeout = 50;
    transaction.writeBuf   = &txBuffer;
    transaction.writeCount = 1;
    transaction.targetAddress = NON_EXISTENT_DEVICE_ADDRESS;
    txBuffer = 0xFE;

    status = I2C_transfer(i2cHandle, &transaction);
    status = transaction.status;
    TEST_ASSERT_EQUAL_INT32(I2C_STS_ERR_NO_ACK, status);

    I2C_close(i2cHandle);
}

/**
 * \brief  Test repeated open and close of I2C driver.
 *
 * This test repeatedly opens and closes the I2C driver to verify that resources
 * are properly allocated and released, and that no errors occur during repeated operations.
 */
static void test_i2c_open_close(void* args)
{
    I2C_Handle          i2cHandle;
    I2C_Params          params;
    I2C_Transaction     transaction;
    uint8_t             rxBuffer;
    int32_t             status;
    uint8_t             i;

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    I2C_Params_init(&params);
    params.bitRate = I2C_400KHZ;

    I2C_Transaction_init(&transaction);
    transaction.readBuf   = &rxBuffer;
    transaction.readCount = 1;
    transaction.targetAddress = Board_i2cGetEepromDeviceAddr();

    for (i=0; i<100; i++)
    {
        i2cHandle = I2C_open(CONFIG_I2C0, &params);
        status = I2C_transfer(i2cHandle, &transaction);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        I2C_close(i2cHandle);
    }
}

/**
 * \brief  Test error handling for NACK responses.
 *
 * This test sends transactions to a non-existent device address to verify that
 * the driver correctly detects and reports NACK errors.
 */
static void test_i2c_error_nack(void* args)
{
    I2C_Handle          i2cHandle;
    I2C_Params          params;
    I2C_Transaction     transaction1;
    I2C_Transaction     transaction2;
    uint8_t             txBuffer;
    uint8_t             rxBuffer;
    int                 i;

    I2C_HwAttrs         *hwAttrs = NULL;

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
    hwAttrs->enableIntr = TRUE;

    I2C_Params_init(&params);
    params.bitRate = I2C_100KHZ;
    i2cHandle = I2C_open(CONFIG_I2C0, &params);

    I2C_Transaction_init(&transaction1);

    transaction1.writeBuf   = &txBuffer;
    transaction1.writeCount = 1;
    transaction1.targetAddress = NON_EXISTENT_DEVICE_ADDRESS;
    txBuffer = 0xFE;

    I2C_Transaction_init(&transaction2);

    transaction2.readBuf   = &rxBuffer;
    transaction2.readCount = 1;
    transaction2.targetAddress = Board_i2cGetEepromDeviceAddr();

    for(i = 0; i < 10; i++)
    {
        (void)I2C_transfer(i2cHandle, &transaction1);
        TEST_ASSERT_EQUAL_INT32(I2C_STS_ERR_NO_ACK,  transaction1.status);
        (void)I2C_transfer(i2cHandle, &transaction2);
        TEST_ASSERT_EQUAL_INT32(I2C_STS_SUCCESS,  transaction2.status);
    }

    I2C_close(i2cHandle);
}

/*
 * Helper Functions
 */
static void test_i2c_set_test_params(I2C_TestParams *testParams, int8_t setting_id)
{
    I2C_Params *params = &(testParams->i2cParams);
    I2C_Params_init(params);
    testParams->deviceAddress = Board_i2cGetEepromDeviceAddr();
    testParams->memAddress = Board_i2cGetEepromMemAddr();
    testParams->numBytes = 3;
    testParams->numWritesReads = 2;
    testParams->testSetFrequency = false;
    testParams->intrEnable = true;

    switch (setting_id)
    {
        /* Blocking, 400KHZ */
        case 0:
            params->bitRate = I2C_400KHZ;
            break;

        /* Blocking, 100KHZ */
        case 1:
            break;

        /* Blocking, 400KHZ, 20 Bytes */
        case 2:
            params->bitRate = I2C_400KHZ;

            if (Board_i2cGetEepromAddrSize()==0x01U)
            {
				testParams->numBytes = 16;
            }
            else
            {
				testParams->numBytes = 20;
            }
            break;

        case 3:
            params->bitRate = I2C_400KHZ;
            testParams->numWritesReads = 10;
            break;

        case 4:
            testParams->testSetFrequency = true;
            break;
        /* Polling mode test */
        case 5:
            params->bitRate = I2C_400KHZ;
            testParams->intrEnable = false;
            break;
    }

    return;
}

static void test_i2c_callback(I2C_Handle i2cHnd, I2C_Transaction * msg, int32_t transferStatus)
{
    if(msg && msg->arg!=NULL)
    {
        SemaphoreP_post((SemaphoreP_Object*)msg->arg);
    }
}

static int32_t test_i2c_open_error(void)
{
    I2C_Handle          i2cHandle;
    I2C_Params          params;

    I2C_close(gI2cHandle[CONFIG_I2C0]);
    /* Negative test case for invalid channel open*/
    I2C_Params_init(&params);
    params.bitRate = I2C_100KHZ;
    i2cHandle = I2C_open(CONFIG_I2C_NUM_INSTANCES+1, &params);
    if (i2cHandle != NULL)
    {
        return SystemP_FAILURE;
    }

    /* Negative test case for opening already opened channel*/
    I2C_close(gI2cHandle[CONFIG_I2C0]);
    i2cHandle = I2C_open(CONFIG_I2C0, &params);
    if (i2cHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    i2cHandle = I2C_open(CONFIG_I2C0, &params);
    if (i2cHandle != NULL)
    {
        return SystemP_FAILURE;
    }

    /* test case to assign default params*/
    I2C_close(gI2cHandle[CONFIG_I2C0]);
    i2cHandle = I2C_open(CONFIG_I2C0,NULL);
    if (i2cHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    return SystemP_SUCCESS;
}

/*
 * Test function of I2C read and write transaction for interrupt mode and polling mode with different frequencies.
 */
static int32_t test_i2c_write_read_mem(void* args)
{
    I2C_TestParams      *testParams = (I2C_TestParams*)args;
    I2C_Params          *i2cParams = &(testParams->i2cParams);
    uint32_t             i;
    uint32_t             loopCount;
    int32_t              status;
    I2C_Handle           i2cHandle;
    I2C_Transaction      i2cTransaction;
    I2C_Mem_Transaction  memTransaction;
    I2C_HwAttrs         *hwAttrs = NULL;
#if !defined (SOC_AM275X)
    I2C_Object          *i2cObject = NULL;
    I2CLLD_Handle        i2cLldHandle;
    I2CLLD_Object       *i2cLldObject = NULL;
#endif

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    /* Disable interrupt registration in case of polling */
    if (testParams->intrEnable == false)
    {
        hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
        hwAttrs->enableIntr = FALSE;
    }
    else
    {
       gI2cConfig[CONFIG_I2C0].hwAttrs->enableIntr = true;
    }

    i2cHandle = I2C_open(CONFIG_I2C0, i2cParams);
    if(i2cHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    if (testParams->testSetFrequency)
    {
        status = I2C_setBusFrequency(i2cHandle, I2C_400KHZ);
        if (SystemP_SUCCESS != status)
        {
            return SystemP_FAILURE;
        }
    }

    for (loopCount=0; loopCount<testParams->numWritesReads; loopCount++)
    {
        /* Set default transaction parameters */
        I2C_Transaction_init(&i2cTransaction);

        /* Override with required transaction parameters */
        i2cTransaction.memTxnEnable = true;
        i2cTransaction.memTransaction = &memTransaction;
        i2cTransaction.targetAddress = testParams->deviceAddress;

        memTransaction.memAddr = (uint32_t)testParams->memAddress;
        memTransaction.memAddrSize = (uint32_t)Board_i2cGetEepromAddrSize();
        memTransaction.buffer = gI2cTxBuffer;
        memTransaction.size = (uint32_t)testParams->numBytes;
        memTransaction.memDataDir = I2C_MEM_TXN_DIR_TX;

        for(i = 0; i < testParams->numBytes; i++)
        {
            gI2cTxBuffer[i] = (uint8_t)i;
        }

        /* To ensure that eeprom is ready, added delay of 4ms */
        ClockP_usleep(4000);
        status = I2C_transfer(i2cHandle, &i2cTransaction);
        if(SystemP_SUCCESS != status)
        {
            return SystemP_FAILURE;
        }

        /* After write operation flash will not respond for write cycle time.
        * This is approximately 4ms (min). */
        /* wait for write to finish */
        ClockP_usleep(5000);

        memTransaction.memAddr = (uint32_t)testParams->memAddress;
        memTransaction.memAddrSize = (uint32_t)Board_i2cGetEepromAddrSize();
        memTransaction.buffer = gI2cRxBuffer;
        memTransaction.size = (uint32_t)testParams->numBytes;
        memTransaction.memDataDir = I2C_MEM_TXN_DIR_RX;

        /* Initiate memory read transfer operation */
        status = I2C_transfer(i2cHandle, &i2cTransaction);
        if (SystemP_SUCCESS != status)
        {
            return SystemP_FAILURE;
        }

        if (memcmp(gI2cTxBuffer, gI2cRxBuffer, testParams->numBytes))
        {
            return SystemP_FAILURE;
        }
    }

    /* Read with high speed for I2C_lld_primeTransferPoll */
    ClockP_usleep(5000);

    /* HS mode not supported for am275x, main domain doesn't support HS mode */
#if !defined (SOC_AM275X)
    i2cObject = (I2C_Object*)i2cHandle->object;
    i2cLldHandle = i2cObject->i2cLldHandle;
    i2cLldObject = (I2CLLD_Object*)i2cLldHandle;
    i2cLldObject->bitRate = I2C_1P0MHZ;
    status = I2C_setBusFrequency(i2cHandle, I2C_1P0MHZ);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = I2C_transfer(i2cHandle, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    i2cLldObject->bitRate = I2C_400KHZ;
    status = I2C_setBusFrequency(i2cHandle, I2C_400KHZ);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
#endif

    I2C_close(i2cHandle);
    return SystemP_SUCCESS;
}

static int32_t test_i2c_handle_errors(void)
{
    I2C_Handle i2cHandle;
    I2C_Params i2cParams;
    I2C_Transaction i2cTransaction;
    I2CLLD_Handle i2cLldHandle;
    I2C_Object *object = NULL;
    int32_t status = SystemP_SUCCESS;
    I2C_Transaction_init(&i2cTransaction);
    I2C_close(gI2cHandle[CONFIG_I2C0]);

    I2C_Params_init(&i2cParams);
    i2cHandle = I2C_open(CONFIG_I2C0, &i2cParams);
    if (i2cHandle != NULL)
    {
        return SystemP_FAILURE;
    }
    i2cHandle = gI2cHandle[CONFIG_I2C0];
    object = (I2C_Object*)i2cHandle->object;

    I2C_close(gI2cHandle[CONFIG_I2C0]);
    I2C_Params_init(&i2cParams);
    i2cHandle = I2C_open(CONFIG_I2C0, &i2cParams);
    if (i2cHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    /* Null parameter passed to the I2C_Params_init
       to increase the dynamic coverage as negative testcase*/
    I2C_Params_init(NULL);
    i2cHandle->object->headPtr = (I2C_Transaction *)(&i2cTransaction);
    I2C_close(i2cHandle);
    i2cHandle->object->headPtr = NULL;

    status=I2C_transfer(NULL, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    i2cTransaction.writeCount = 0;
    i2cTransaction.readCount = 0;
    i2cTransaction.memTxnEnable = 0;
    status=I2C_transfer(i2cHandle, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    I2C_probe(NULL, 0);
    I2C_setBusFrequency(NULL, I2C_100KHZ);

    i2cHandle->object->i2cLldHandle->state = I2C_STS_ERR_BUS_BUSY;
    I2C_setBusFrequency(i2cHandle, I2C_100KHZ);
    i2cHandle->object->i2cLldHandle->state = I2C_STATE_IDLE;

    i2cHandle = I2C_getHandle(CONFIG_I2C_NUM_INSTANCES+1);
    TEST_ASSERT_NULL(i2cHandle);

    gI2cConfig[0].object->isOpen = false;
    i2cHandle = I2C_getHandle(0);
    TEST_ASSERT_NULL(i2cHandle);

    gI2cConfig[0].object->isOpen = true;
    /* Saving the I2C config object */
    object = gI2cConfig[0].object;
    gI2cConfig[0].object = NULL;
    i2cHandle = I2C_getHandle(0);
    TEST_ASSERT_NULL(i2cHandle);

    /* Storing back the object contents back to the I2C global config object */
    gI2cConfig[0].object = object;

    gI2cConfig[0].object->isOpen = false;

    I2C_Params_init(&i2cParams);
    i2cHandle = I2C_open(CONFIG_I2C0, &i2cParams);
    if (i2cHandle == NULL)
    {
        return SystemP_FAILURE;
    }
    i2cLldHandle = i2cHandle->object->i2cLldHandle;
    i2cHandle->object->i2cLldHandle = NULL;
    i2cTransaction.memTxnEnable = true;
    status=I2C_transfer(i2cHandle, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    i2cHandle->object->i2cLldHandle = i2cLldHandle;

    I2C_close(i2cHandle);
    return SystemP_SUCCESS;
}

static int32_t test_i2c_memparams(void *args, uint32_t testcase, bool mode)
{
    I2C_TestParams     *testParams = (I2C_TestParams*)args;
    I2C_Handle          i2cHandle;
    I2C_Params          params;
    I2C_Transaction     transaction;
    I2C_Mem_Transaction memTransaction;
    uint8_t             rxBuffer;
    int32_t             status = SystemP_SUCCESS;

    I2C_close(gI2cHandle[CONFIG_I2C0]);
    if (testParams->intrEnable == true)
    {
       gI2cConfig[CONFIG_I2C0].hwAttrs->enableIntr = true;
    }
    else
    {
       gI2cConfig[CONFIG_I2C0].hwAttrs->enableIntr = false;
    }

    I2C_Params_init(&params);
    params.bitRate = I2C_400KHZ;

    /* default memory transaction */
    I2C_Memory_Transaction_init(&memTransaction);
    memTransaction.memAddr = Board_i2cGetEepromMemAddr();
    memTransaction.buffer = gI2cTxBuffer;
    if (mode == TX)
    {
        memTransaction.memDataDir = I2C_MEM_TXN_DIR_TX;
    }
    else
    {
        memTransaction.memDataDir = I2C_MEM_TXN_DIR_RX;
    }
    I2C_Transaction_init(&transaction);
    transaction.readBuf   = &rxBuffer;
    transaction.readCount = 1;
    transaction.targetAddress = Board_i2cGetEepromDeviceAddr();
    transaction.memTxnEnable = (bool) true;
    transaction.memTransaction = &memTransaction;
    switch (testcase)
    {
        /* default memory transaction */
        case DEFAULT_MEM_TRANSACTION:
        i2cHandle = I2C_open(CONFIG_I2C0, &params);
        if (i2cHandle == NULL)
        {
            status = SystemP_FAILURE;
        }
        else
        {
            status = I2C_transfer(i2cHandle, &transaction);
            I2C_close(i2cHandle);
        }
        break;
        /* Test with invalid memory address size */
        case INVALID_MEM_ADDR_SIZE:
            memTransaction.memAddrSize = 0;
            transaction.readBuf   = &rxBuffer;
            transaction.readCount = 1;
            transaction.targetAddress = Board_i2cGetEepromDeviceAddr();
            transaction.memTransaction = &memTransaction;
            i2cHandle = I2C_open(CONFIG_I2C0, &params);
            if (i2cHandle == NULL)
            {
                status = SystemP_FAILURE;
            }
            else
            {
                /* Transfer is called twice to generate negative testcase.
                   so that second transfer happens during the time when first transfer is in progress */
                I2C_transfer(i2cHandle, &transaction);
                I2C_transfer(i2cHandle, &transaction);
                I2C_close(i2cHandle);
            }
            break;
        /* Test with invalid memory params */
        case INVALID_MEM_PARAMS:
            transaction.memTransaction = NULL;
            i2cHandle = I2C_open(CONFIG_I2C0, &params);
            if (i2cHandle == NULL)
            {
                status = SystemP_FAILURE;
            }
            else
            {
                if (mode == TX)
                {
                    if (testParams->intrEnable)
                    {
                        status = I2C_lld_mem_writeIntr((void *)i2cHandle, NULL);
                    }
                    else
                    {
                        status = I2C_lld_mem_write((void *)i2cHandle, NULL, 0);
                    }
                }
                else
                {
                    if (testParams->intrEnable)
                    {
                        status = I2C_lld_mem_readIntr((void *)i2cHandle, NULL);
                    }
                    else
                    {
                        status = I2C_lld_mem_read((void *)i2cHandle, NULL, 0);
                    }
                }
                if (status == I2C_STS_ERR_INVALID_PARAM)
                {
                    I2C_transfer(i2cHandle, &transaction);
                    I2C_close(i2cHandle);
                }
            }
            break;
        default:
            status = SystemP_FAILURE;
            break;
    }

    return status;
}

static int32_t test_i2c_error_checks(void)
{
    I2C_Handle          i2cHandle;
    I2C_Handle            i2cHandle_faulty;
    I2C_Params          params;
    uint32_t             initialAddress;
    uint32_t            status = SystemP_SUCCESS;
    I2C_Object             *temp;
    I2C_HwAttrs         *hwAttrs = NULL;

    I2C_close(gI2cHandle[CONFIG_I2C0]);
    /* i2c open with faulty base address  */
    hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
    initialAddress = hwAttrs->baseAddr;

    hwAttrs->baseAddr = 0;

    i2cHandle = I2C_open(CONFIG_I2C0, &params);
    if (i2cHandle != NULL)
    {
        return SystemP_FAILURE;
    }

    hwAttrs->baseAddr = initialAddress;

    i2cHandle = I2C_open(CONFIG_I2C0, &params);
    if (i2cHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    I2C_close(i2cHandle);

    status = I2C_transfer(i2cHandle, NULL);
    if (SystemP_FAILURE != status)
    {
        return SystemP_FAILURE;
    }

    I2C_Params_init(&params);
    params.bitRate = I2C_100KHZ;
    i2cHandle_faulty = I2C_open(CONFIG_I2C0, &params);

    temp = i2cHandle_faulty->object;
    i2cHandle_faulty->object = NULL;
    /* i2c close with faulty parameters  */
    I2C_close(i2cHandle_faulty);
    i2cHandle_faulty->object = temp;

    I2C_close(i2cHandle_faulty);
    return SystemP_SUCCESS;
}

static int32_t test_i2c_timeout_negative(void)
{
    I2C_Handle          i2cHandle;
    I2C_Params          params;
    I2C_Transaction     transaction;
    uint8_t             txBuffer;
    int32_t             status;

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    I2C_Params_init(&params);
    params.bitRate = I2C_400KHZ;
    i2cHandle = I2C_open(CONFIG_I2C0, &params);

    I2C_Transaction_init(&transaction);
    transaction.timeout = 0;
    transaction.writeBuf   = &txBuffer;
    transaction.writeCount = 1;
    transaction.targetAddress = NON_EXISTENT_DEVICE_ADDRESS;
    txBuffer = 0xFE;

    status = I2C_transfer(i2cHandle, &transaction);
    status = transaction.status;
    I2C_close(i2cHandle);
    return status;
}


/* testcase for i2c recover */
static int32_t test_i2c_recover_bus(void)
{
    I2C_Handle i2cHandle;
    uint32_t   i2cDelay = I2C_DELAY_SMALL;
    int32_t    status;

    /* Retrieve the I2C handle for a specific instance */
    i2cHandle = I2C_getHandle(CONFIG_I2C0);
    if (i2cHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    /* Attempt to recover the I2C bus */
    status = I2C_recoverBus(i2cHandle, i2cDelay);
    if (SystemP_SUCCESS != status)
    {
        return status;
    }

    /* Null handle for i2c recover */
    I2C_close(i2cHandle);
    status = I2C_recoverBus(NULL,i2cDelay);

    return status;
}

/* test case for validating base address */
static int32_t test_i2c_baseaddress(uint32_t baseAddr)
{
    int32_t status;

    status = I2C_lld_isBaseAddrValid(baseAddr);
    if (status < 0)
    {
        return SystemP_FAILURE;
    }

    return SystemP_SUCCESS;
}

static int32_t test_i2c_lld(void)
{
    int32_t status;
    I2C_Handle handle;
    I2C_Object *object = NULL;
    I2C_Params          params;
    I2CLLD_Handle i2cLldHandle;
    I2CLLD_Message msg;
    I2CLLD_Transaction txn;
    I2CLLD_Object* i2cLldObject = NULL;

    I2C_close(gI2cHandle[CONFIG_I2C0]);
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);
    object = (I2C_Object*)handle->object;

    i2cLldHandle = object->i2cLldHandle;

    /* negative test case for i2c_lld_init */
    status = I2C_lld_init(NULL);
    if (I2C_STS_ERR_INVALID_PARAM != status)
    {
        return SystemP_FAILURE;
    }

    /* negative test case for lld_deinit */
    status = I2C_lld_deInit(NULL);
    if (I2C_STS_ERR_INVALID_PARAM != status)
    {
        return SystemP_FAILURE;
    }

    /* negative test case for lld_transaction_init*/
    status = I2C_lld_Transaction_init(NULL);
    if (I2C_STS_ERR_INVALID_PARAM != status)
    {
        return SystemP_FAILURE;
    }

    /* negative test case for lld_message_init*/
    status = I2C_lld_Message_init(NULL);
    if (I2C_STS_ERR_INVALID_PARAM != status)
    {
        return SystemP_FAILURE;
    }

    /* test case for bit rate */
    I2C_lld_deInit(i2cLldHandle);
    i2cLldHandle->bitRate = I2C_1P0MHZ;
    status = I2C_lld_init(i2cLldHandle);
    if (I2C_STS_SUCCESS != status)
    {
        return SystemP_FAILURE;
    }

    /* test case for bit rate */
    I2C_lld_deInit(i2cLldHandle);
    i2cLldHandle->bitRate = I2C_3P4MHZ;
    status = I2C_lld_init(i2cLldHandle);
    if (I2C_STS_SUCCESS != status)
    {
        return SystemP_FAILURE;
    }

    /* test case for bit rate */
    I2C_lld_deInit(i2cLldHandle);
    i2cLldHandle->bitRate = 4;
    status = I2C_lld_init(i2cLldHandle);
    if (I2C_STS_SUCCESS != status)
    {
        return SystemP_FAILURE;
    }

    /* negative test case for lld_transferpoll */
    I2C_lld_deInit(i2cLldHandle);
    status = I2C_lld_transferPoll(i2cLldHandle,NULL);
    if (I2C_STS_ERR_INVALID_PARAM != status)
    {
        return SystemP_FAILURE;
    }
    msg.txn = NULL;
    status = I2C_lld_transferPoll(i2cLldHandle,&msg);

    /*negative test case for I2C_lld_transferIntr */
    I2C_lld_deInit(i2cLldHandle);
    status = I2C_lld_transferIntr(i2cLldHandle,NULL);
    if (I2C_STS_ERR_INVALID_PARAM != status)
    {
        return SystemP_FAILURE;
    }

    msg.txn = NULL;
    msg.timeout = 0;
    status = I2C_lld_transferIntr(i2cLldHandle,&msg);

    /*negative test case for I2C_lld_transferInit*/
    msg.timeout = 50;
    msg.txn = &txn;
    txn.writeCount = 1;
    i2cLldObject = (I2CLLD_Object*)i2cLldHandle;
    i2cLldObject->state = I2C_STATE_BUSY;

    I2C_lld_deInit(i2cLldHandle);
    status = I2C_lld_transferIntr(i2cLldHandle,&msg);
    if (SystemP_FAILURE != status)
    {
        return SystemP_FAILURE;
    }

    i2cLldObject->state = I2C_STATE_IDLE;

    /*negative test case for I2C_lld_primeTransferPoll*/
    I2C_lld_deInit(i2cLldHandle);
    status = I2C_lld_init(i2cLldHandle);
    if (SystemP_SUCCESS != status)
    {
        return SystemP_FAILURE;
    }

    I2C_lld_deInit(i2cLldHandle);
    i2cLldHandle-> state = I2C_STATE_ERROR;
    status = I2C_lld_init(i2cLldHandle);
    if (I2C_STS_ERR != status)
    {
        return SystemP_FAILURE;
    }

    i2cLldHandle->currentMsg = malloc(sizeof(I2CLLD_Message));
    status = I2C_lld_deInit(i2cLldHandle);
    if (I2C_STS_ERR != status)
    {
        return SystemP_FAILURE;
    }
    return SystemP_SUCCESS;
}

/*
 * Test function to verify error conditions for i2c read and write.
 */
static int32_t test_i2c_write_read_mem_error_checks(void* args, uint8_t testCase)
{
    I2C_TestParams      *testParams = (I2C_TestParams*)args;
    I2C_Params          *i2cParams = &(testParams->i2cParams);
    uint32_t             i;
    int32_t              status = SystemP_SUCCESS;
    I2C_Handle           i2cHandle;
    I2C_Transaction      i2cTransaction;
    I2C_Mem_Transaction  memTransaction;
    I2C_HwAttrs         *hwAttrs = NULL;
    I2C_Object          *i2cObject = NULL;
    I2CLLD_Handle        i2cLldHandle;
    I2CLLD_Object       *i2cLldObject = NULL;

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    /* Set default transaction parameters */
    I2C_Transaction_init(&i2cTransaction);

    /* Override with required transaction parameters */
    i2cTransaction.memTxnEnable = true;
    i2cTransaction.memTransaction = &memTransaction;
    i2cTransaction.targetAddress = testParams->deviceAddress;

    memTransaction.buffer = gI2cTxBuffer;
    memTransaction.memDataDir = I2C_MEM_TXN_DIR_TX;

    for(i = 0; i < sizeof(gI2cTxBuffer); i++)
    {
        gI2cTxBuffer[i] = (uint8_t)i;
    }

    /* Disable interrupt registration in case of polling */
    if (testParams->intrEnable == false)
    {
        hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
        hwAttrs->enableIntr = FALSE;
    }

    i2cHandle = I2C_open(CONFIG_I2C0, i2cParams);

    if ( testCase == TESTCASE_RD_WR_BUSFREQ)
    {
        if (testParams->testSetFrequency)
        {
            status = I2C_setBusFrequency(i2cHandle, I2C_400KHZ);
            if(SystemP_SUCCESS != status)
            {
                return status;
            }
        }
    }
    else if ( testCase == TESTCASE_RD_WR_TIMEOUT)
    {
        /* TIMEOUT ERROR CHECK*/
        /* Override with required transaction parameters */
        i2cTransaction.timeout = 1;

        memTransaction.memAddr = (uint32_t)testParams->memAddress;
        memTransaction.memAddrSize = (uint32_t)Board_i2cGetEepromAddrSize();
        memTransaction.size = (uint32_t) 200;

        /* To ensure that eeprom is ready, added delay of 4ms */
        ClockP_usleep(4000);

        status = I2C_transfer(i2cHandle, &i2cTransaction);

        if(SystemP_TIMEOUT != status)
        {
            return status;
        }

        /* After write operation flash will not respond for write cycle time.
         * This is approximately 4ms (min). */
        /* wait for write to finish */
        ClockP_usleep(5000);

        memTransaction.memAddr = (uint32_t)testParams->memAddress;
        memTransaction.memAddrSize = (uint32_t)Board_i2cGetEepromAddrSize();
        memTransaction.buffer = gI2cRxBuffer;
        memTransaction.size = (uint32_t)200;
        memTransaction.memDataDir = I2C_MEM_TXN_DIR_RX;

        /* Initiate memory read transfer operation */
        status = I2C_transfer(i2cHandle, &i2cTransaction);

        if (SystemP_TIMEOUT != status)
        {
            return status;
        }

        /*Test case for 10 bit address in prime Transfer Poll*/
        memTransaction.memDataDir = I2C_MEM_TXN_DIR_TX;

        i2cTransaction.expandSA = true;

        ClockP_usleep(4000);

        status = I2C_transfer(i2cHandle, &i2cTransaction);

        if (SystemP_TIMEOUT != status)
        {
            return status;
        }

        i2cTransaction.expandSA = false;/*Test case for high speed in prime Transfer Poll*/
        ClockP_usleep(4000);

        i2cObject = (I2C_Object*)i2cHandle->object;
        i2cLldHandle = i2cObject->i2cLldHandle;
        i2cLldObject = (I2CLLD_Object*)i2cLldHandle;
        i2cLldObject->bitRate = I2C_1P0MHZ;

        status = I2C_transfer(i2cHandle, &i2cTransaction);

        if (SystemP_TIMEOUT != status)
        {
            return status;
        }
    }
    else if(testCase == TESTCASE_RD_WR_INVALIDADDR)
    {
        memTransaction.memAddr = (uint32_t)testParams->memAddress;

        /* Invalid mem address size */
        memTransaction.memAddrSize = 32;
        memTransaction.size = (uint32_t)testParams->numBytes;

        /* To ensure that eeprom is ready, added delay of 4ms */
        ClockP_usleep(4000);

        status = I2C_transfer(i2cHandle, &i2cTransaction);

        if (SystemP_FAILURE != status)
        {
            return status;
        }

        /* Incorrect mem address size for write*/
        I2C_Transaction_init(&i2cTransaction);
        /* Override with required transaction parameters */
        i2cTransaction.memTxnEnable = true;
        i2cTransaction.memTransaction = &memTransaction;
        i2cTransaction.targetAddress = testParams->deviceAddress;

        memTransaction.memAddr = (uint32_t)testParams->memAddress;
        memTransaction.memAddrSize = 8; /*Incorrect mem address size*/
        memTransaction.buffer = gI2cTxBuffer;
        memTransaction.size = (uint32_t)testParams->numBytes;
        memTransaction.memDataDir = I2C_MEM_TXN_DIR_TX;

        /* To ensure that eeprom is ready, added delay of 4ms */
        ClockP_usleep(4000);

        status = I2C_transfer(i2cHandle, &i2cTransaction);

        if (SystemP_FAILURE != status)
        {
            return status;
        }

        /* wait for write to finish */
        ClockP_usleep(5000);

        /* Invalid mem address size for read*/
        memTransaction.memAddr = (uint32_t)testParams->memAddress;
        memTransaction.memAddrSize = 32;
        memTransaction.buffer = gI2cRxBuffer;
        memTransaction.size = (uint32_t)testParams->numBytes;
        memTransaction.memDataDir = I2C_MEM_TXN_DIR_RX;

        /* Initiate memory read transfer operation */
        status = I2C_transfer(i2cHandle, &i2cTransaction);

        if (SystemP_FAILURE != status)
        {
            return status;
        }

        /* wait for write to finish */
        ClockP_usleep(5000);

        memTransaction.memAddr = (uint32_t)testParams->memAddress;
        memTransaction.memAddrSize = 8;
        memTransaction.buffer = gI2cRxBuffer;
        memTransaction.size = (uint32_t)testParams->numBytes;
        memTransaction.memDataDir = I2C_MEM_TXN_DIR_RX;

        /* Initiate memory read transfer operation */
        status = I2C_transfer(i2cHandle, &i2cTransaction);

        if (SystemP_FAILURE != status)
        {
            return status;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    I2C_close(i2cHandle);
    return status;
}

static int32_t test_i2c_differentSpeeds(uint8_t freq, uint8_t testCase)
{
    int32_t         status;
    int32_t         expectedStatus;
    I2C_Handle      i2cHandle;
    I2C_Params      params;
    I2C_Object     *object = NULL;
    I2CLLD_Handle   i2cLldHandle = NULL;
    I2CLLD_Object  *lldObject = NULL;

    I2C_close(gI2cHandle[CONFIG_I2C0]);
    I2C_Params_init(&params);

    i2cHandle = I2C_open(CONFIG_I2C0, &params);
    if (i2cHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    switch (testCase)
    {
        case BUS_BUSY:
            object = (I2C_Object*)i2cHandle->object;
            i2cLldHandle = object->i2cLldHandle;
            lldObject = (I2CLLD_Object*)i2cLldHandle;
            lldObject->state = I2C_STATE_BUSY;
            expectedStatus = SystemP_FAILURE;
            break;

        case NULL_HANDLE:
            object = (I2C_Object*)i2cHandle->object;
            i2cLldHandle = object->i2cLldHandle;
            object->i2cLldHandle = NULL;
            expectedStatus = SystemP_FAILURE;
            break;

        default:
            expectedStatus = SystemP_SUCCESS;
            break;
    }
    status = I2C_setBusFrequency(i2cHandle, freq);
    if (status != expectedStatus)
    {
        return status;
    }

    if (testCase == NULL_HANDLE)
    {
        object->i2cLldHandle = i2cLldHandle;
    }
    I2C_close(i2cHandle);

    return SystemP_SUCCESS;
}

static int32_t test_i2c_nack_error_check(void* args)
{
    I2C_TestParams     *testParams = (I2C_TestParams*)args;
    I2C_Handle          i2cHandle;
    I2C_Params          params;
    I2C_Transaction     transaction1;
    uint8_t             txBuffer;
    I2C_HwAttrs         *hwAttrs = NULL;

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;

    hwAttrs->enableIntr = TRUE;

    if(testParams->intrEnable == false)
    {
        hwAttrs->enableIntr = FALSE;
    }

    I2C_Params_init(&params);
    params.bitRate = I2C_100KHZ;
    i2cHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(i2cHandle);

    I2C_Transaction_init(&transaction1);

    transaction1.writeBuf   = &txBuffer;
    transaction1.writeCount = 1;
    transaction1.targetAddress = NON_EXISTENT_DEVICE_ADDRESS;
    txBuffer = 0xFE;

    (void)I2C_transfer(i2cHandle, &transaction1);

    I2C_close(i2cHandle);
    return transaction1.status;
}

/**
 * \brief Test SCL stuck low recovery using SYSTEST fault injection.
 *
 * Test Category: Fault Injection
 *
 * This test simulates the SCL line being stuck low using the SYSTEST register and verifies
 * that the I2C_recoverBus API can recover the bus for various bit rates and restores normal operation.
 *
 * \param args Unused.
 */
void TestI2c_sclStuckRecoverBusWithSystestFault(void* args)
{
    I2C_Params i2cParams;
    I2C_Handle handle;
    uint32_t regVal, f, i;
    int32_t status;
    uint32_t i2cDelay = I2C_DELAY_SMALL;;
    I2C_Transaction testI2cTransaction;

    for (i = 0; i < 10; i++)
    {
        gI2cTxBuffer[i + Board_i2cGetEepromAddrSize()] = (uint8_t)i;
    }

    /* Setup: open I2C instance */
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.writeBuf = gI2cTxBuffer;
    testI2cTransaction.writeCount = 2;
    testI2cTransaction.readBuf = NULL;
    testI2cTransaction.readCount = 0;
    testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
    testI2cTransaction.timeout = SystemP_WAIT_FOREVER;

    /* Supported frequencies to test */
    const uint32_t freqList[] = { I2C_100KHZ, I2C_400KHZ};
    const char* Test_I2c_FreqNames[] = { "100kHz", "400kHz"};
    const int32_t Test_I2c_FreqCount = sizeof(freqList)/sizeof(freqList[0]);

    for (f = 0; f < Test_I2c_FreqCount; ++f)
    {
        handle = I2C_getHandle(CONFIG_I2C0);
        if(handle)
        {
            I2C_close(handle);
        }
        gI2cHandle[CONFIG_I2C0] = NULL;
        I2C_Params_init(&i2cParams);
        handle = I2C_open(CONFIG_I2C0, &i2cParams);
        TEST_ASSERT_NOT_NULL(handle);

        handle = I2C_getHandle(CONFIG_I2C0);
        TEST_ASSERT_NOT_NULL(handle);
        uint32_t baseAddr = handle->hwAttrs->baseAddr;

        handle->object->i2cLldHandle->bitRate = freqList[f];
        DebugP_log("Testing SCL stuck recovery at %s...\n", Test_I2c_FreqNames[f]);

        /* Enable test mode and simulate SCL stuck low */
        regVal = HW_RD_REG32(baseAddr + CSL_I2C_SYSTEST);
        regVal |= (1 << CSL_I2C_SYSTEST_ST_EN_SHIFT);       /* ST_EN = 1 */
        regVal |= (0x3 << CSL_I2C_SYSTEST_TMODE_SHIFT);     /* TMODE = 0b11 */
        regVal &= ~(1 << CSL_I2C_SYSTEST_SCL_O_SHIFT);       /* SCL_O = 0 (drive low) */
        HW_WR_REG32(baseAddr + CSL_I2C_SYSTEST, regVal);
        ClockP_usleep(10);         /* Let the line settle */

        /* Confirm SCL is stuck low */
        regVal = HW_RD_REG32(baseAddr + CSL_I2C_SYSTEST);
        bool sclStuck = ((regVal >> 3) & 0x1) == 0;  /* SCL_I == 0 */
        TEST_ASSERT_TRUE_MESSAGE(sclStuck, "SCL line is not stuck as expected");

        /*  Try recovery */
        status = I2C_recoverBus(handle, i2cDelay);
        TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS, status, "I2C_recoverBus() failed");

        status = I2C_transfer(handle, &testI2cTransaction);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Close */
        I2C_close(handle);
    }
}

/**
 * \brief Test SDA stuck low recovery using SYSTEST fault injection.
 *
 * Test Category: Fault Injection
 *
 * This test simulates the SDA line being stuck low using the SYSTEST register and verifies
 * that the I2C_recoverBus API can recover the bus.
 *
 * \param args Unused.
 */
void TestI2c_sdaStuckRecoverBusWithSystestFault(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    int32_t status, i;
    uint32_t orig, val;
    I2C_Transaction testI2cTransaction;

    for (i = 0; i < 10; i++)
    {
        gI2cTxBuffer[i + Board_i2cGetEepromAddrSize()] = (uint8_t)i;
    }

    /* Setup: open I2C instance */
    I2C_Params_init(&params);
    params.bitRate = I2C_400KHZ;
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.writeBuf = gI2cTxBuffer;
    testI2cTransaction.writeCount = 2;
    testI2cTransaction.readBuf = NULL;
    testI2cTransaction.readCount = 0;
    testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
    testI2cTransaction.timeout = SystemP_WAIT_FOREVER;

    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    handle = I2C_getHandle(CONFIG_I2C0);
    TEST_ASSERT_NOT_NULL(handle);
    uint32_t baseAddr = handle->hwAttrs->baseAddr;

    /* Save original SYSTEST */
    orig = HW_RD_REG32(baseAddr + CSL_I2C_SYSTEST);

    /* Enable SYSTEST mode, TMODE = 3 (loopback), force SDA low */
    val = orig;
    val |= CSL_I2C_SYSTEST_ST_EN_MASK;                   /* enable systest */
    val &= ~CSL_I2C_SYSTEST_TMODE_MASK;
    val |= (3U << CSL_I2C_SYSTEST_TMODE_SHIFT);          /* TMODE=3 */
    val |= CSL_I2C_SYSTEST_SCL_O_MASK;                   /* drive SCL high */
    val &= ~CSL_I2C_SYSTEST_SDA_O_MASK;                  /* drive SDA low */
    HW_WR_REG32(baseAddr + CSL_I2C_SYSTEST, val);

    ClockP_usleep(50);

    /* Confirm SDA_I really stuck low */
    uint32_t sysReg = HW_RD_REG32(baseAddr + CSL_I2C_SYSTEST);
    TEST_ASSERT_EQUAL_UINT32(0, sysReg & CSL_I2C_SYSTEST_SDA_I_MASK);

    /* Call recoverBus (should detect SDA stuck and try recovery) */
    status = I2C_recoverBus(handle, I2C_DELAY_SMALL);
    DebugP_log("recoverBus status=%d, SYSTEST=0x%08X\n", status, sysReg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = I2C_transfer(handle, &testI2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    I2C_close(handle);
}

/**
 * \brief Test EEPROM read without prior address write (negative test).
 *
 * Test Category: Negative Test Case
 *
 * This test attempts to read from EEPROM without first writing the address, expecting failure.
 *
 * \param args Unused.
 */
static void TestI2c_eepromReadWithoutAddressWrite(void* args)
{
   I2C_Handle handle;
   I2C_Params params;
   I2C_Transaction transaction;
   uint8_t rxBuf[2];
   int32_t status;
   I2C_Transaction_init(&transaction);
   handle = I2C_getHandle(CONFIG_I2C0);
   if(handle)
   {
       I2C_close(handle);
   }
   I2C_Params_init(&params);
   handle = I2C_open(CONFIG_I2C0, &params);
   TEST_ASSERT_NOT_NULL(handle);

   transaction.writeCount = 0;
   transaction.readCount  = 2;
   transaction.targetAddress = Board_i2cGetEepromMemAddr();
   transaction.readBuf = rxBuf;

   status = I2C_transfer(handle, &transaction);
   TEST_ASSERT_EQUAL(status, SystemP_FAILURE);
   I2C_close(handle);
}

static void TestI2c_eepromPageOverflow(void* args)
{
    int32_t status, i;
    I2C_Handle handle;
    I2C_Params params;
    I2C_Transaction i2cTransaction;

    uint32_t overflowSize = 160; /* pageSize to test wrap */
     I2C_TestParams *testParams = (I2C_TestParams*)args;
    /* Fill write buffer: Addr bytes + overflow data */
    for (i = 0; i < overflowSize; i++)
    {
        gI2cTxBuffer[i + Board_i2cGetEepromAddrSize()] = 0xA5;
    }

    if(Board_i2cGetEepromAddrSize() == 1U)
    {
        gI2cTxBuffer[0] = (uint8_t)(testParams->memAddress);
    }
    else
    {
        gI2cTxBuffer[0] = (uint8_t)(testParams->memAddress >> 8);
        gI2cTxBuffer[1] = (uint8_t)(testParams->memAddress & 0xFF);
    }
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    I2C_Params_init(&params);
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    /* EEPROM Write (160 bytes) */
    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = gI2cTxBuffer;
    i2cTransaction.writeCount = Board_i2cGetEepromAddrSize() + overflowSize;
    i2cTransaction.targetAddress = testParams->deviceAddress;

    ClockP_usleep(5000);  /* wait before write */
    status = I2C_transfer(handle, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for EEPROM write */
    ClockP_usleep(10000);

    /* Read back first page (128 bytes) */
    uint8_t addrBuf[2];
    if (Board_i2cGetEepromAddrSize() == 1)
    {
        addrBuf[0] = (uint8_t)testParams->memAddress;
    }
    else
    {
        addrBuf[0] = (uint8_t)(testParams->memAddress >> 8);
        addrBuf[1] = (uint8_t)(testParams->memAddress & 0xFF);
    }

    memset(gI2cRxBuffer, 0, 128);
    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = addrBuf;
    i2cTransaction.writeCount = Board_i2cGetEepromAddrSize();
    i2cTransaction.readBuf    = gI2cRxBuffer;
    i2cTransaction.readCount  = 128;
    i2cTransaction.targetAddress = testParams->deviceAddress;

    status = I2C_transfer(handle, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("EEPROM Overflow Test: Expected = 0x%02X, Actual = 0x%02X\n", gI2cTxBuffer[Board_i2cGetEepromAddrSize() + 128], gI2cRxBuffer[0]);
    /* Now validate wrap: data[0] = txBuffer[AddrSize + 128] */
    TEST_ASSERT_EQUAL_HEX8(gI2cTxBuffer[Board_i2cGetEepromAddrSize() + 128], gI2cRxBuffer[0]);
}

/**
 * \brief Performance test for I2C write and read at 100 kHz and 400 kHz in polling and interrupt modes.
 *
 * Test Category: Performance / Functionality
 *
 * This test measures the write and read throughput of the I2C driver at 100 kHz and 400 kHz
 * by timing multiple transfers in both polling (blocking) and interrupt (callback) modes.
 * It reports average transfer times and throughput (MiB/s) for each mode and frequency.
 *
 * \param args Pointer to I2C_TestParams structure.
 */
static void TestI2c_perfWriteReadDiffFreq(void* args)
{
    I2C_TestParams *testParams = (I2C_TestParams *)args;
    const uint32_t addrBytes   = Board_i2cGetEepromAddrSize();
    const int32_t Test_I2c_FreqCount = 2;
    int32_t mode, f, i, status, sz;
    const int32_t Test_I2c_FreqEnums[]  = { I2C_100KHZ, I2C_400KHZ };
    const char *Test_I2c_FreqNames[] = { "100 kHz", "400 kHz" };
    const uint32_t dataSizes[TEST_I2C_PERF_NUM_SIZES] = { TEST_I2C_64B_SIZE, TEST_I2C_128B_SIZE, TEST_I2C_256B_SIZE };
    SemaphoreP_Object sem;

    DebugP_log("\nI2C Performance Numbers Print Start\r\n\n");
    DebugP_log("Mode        | Freq        | Data Size (B) | Write MiB/s | Write Time (us) | Read MiB/s | Read Time (us)\r\n");
    DebugP_log("------------|-------------|---------------|-------------|-----------------|------------|---------------\r\n");

    for (mode = 0; mode < 2; mode++)
    {
        bool useCallback = (mode == 1);
        const char *modeName = useCallback ? "INTERRUPT" : "POLLING";
        for (f = 0; f < Test_I2c_FreqCount; f++)
        {
            if (gI2cHandle[CONFIG_I2C0] != NULL)
            {
                I2C_close(gI2cHandle[CONFIG_I2C0]);
                gI2cHandle[CONFIG_I2C0] = NULL;
            }
            I2C_HwAttrs *hw = (I2C_HwAttrs*)gI2cConfig[CONFIG_I2C0].hwAttrs;
            hw->enableIntr = useCallback ? TRUE : FALSE;
            I2C_Params params;
            I2C_Params_init(&params);
            params.transferMode = useCallback ? I2C_MODE_CALLBACK : I2C_MODE_BLOCKING;
            if(useCallback)
            {
                params.transferCallbackFxn = test_i2c_callback;
            }
            gI2cHandle[CONFIG_I2C0] = I2C_open(CONFIG_I2C0, &params);
            TEST_ASSERT_NOT_NULL(gI2cHandle[CONFIG_I2C0]);
            I2C_setBusFrequency(gI2cHandle[CONFIG_I2C0], Test_I2c_FreqEnums[f]);
            for (sz = 0; sz < TEST_I2C_PERF_NUM_SIZES; sz++)
            {
                uint32_t payload = dataSizes[sz];
                for (i=0;i<payload;i++)
                {
                    gI2cTxBuffer[addrBytes + i] = (uint8_t)i;
                    gI2cRxBuffer[i] = 0;
                }
                if (addrBytes == 1U)
                    gI2cTxBuffer[0] = (uint8_t)testParams->memAddress;
                else
                {
                    gI2cTxBuffer[0] = (uint8_t)(testParams->memAddress >> 8);
                    gI2cTxBuffer[1] = (uint8_t)(testParams->memAddress & 0xFF);
                }
                /* Warm-up write */
                I2C_Transaction testI2cTransaction;
                I2C_Transaction_init(&testI2cTransaction);
                testI2cTransaction.targetAddress = testParams->deviceAddress;
                testI2cTransaction.writeBuf      = gI2cTxBuffer;
                testI2cTransaction.writeCount    = addrBytes + payload;
                testI2cTransaction.readCount     = 0;
                if(useCallback)
                {
                    SemaphoreP_constructBinary(&sem, 0);
                    testI2cTransaction.arg=&sem;
                }
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, I2C_transfer(gI2cHandle[CONFIG_I2C0], &testI2cTransaction));
                if(useCallback)
                {
                    SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
                    SemaphoreP_destruct(&sem);
                }
                ClockP_usleep(10000);
                /* Timed write */
                I2C_Transaction_init(&testI2cTransaction);
                testI2cTransaction.targetAddress = testParams->deviceAddress;
                testI2cTransaction.writeBuf      = gI2cTxBuffer;
                testI2cTransaction.writeCount    = addrBytes + payload;
                testI2cTransaction.readCount     = 0;
                if(useCallback)
                {
                    SemaphoreP_constructBinary(&sem, 0);
                    testI2cTransaction.arg=&sem;
                }
                uint64_t t0 = ClockP_getTimeUsec();
                status = I2C_transfer(gI2cHandle[CONFIG_I2C0], &testI2cTransaction);
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
                if(useCallback)
                {
                    SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
                    SemaphoreP_destruct(&sem);
                }
                uint64_t t1 = ClockP_getTimeUsec();
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
                uint64_t writeTime = t1 - t0;
                ClockP_usleep(10000);
                /* Ready poll before read */
                I2C_Transaction_init(&testI2cTransaction);
                testI2cTransaction.targetAddress = testParams->deviceAddress;
                testI2cTransaction.writeBuf      = gI2cTxBuffer;
                testI2cTransaction.writeCount    = addrBytes;
                testI2cTransaction.readBuf       = gI2cRxBuffer;
                testI2cTransaction.readCount     = 1;
                if(useCallback)
                {
                    SemaphoreP_constructBinary(&sem, 0);
                    testI2cTransaction.arg=&sem;
                }
                do {
                    status = I2C_transfer(gI2cHandle[CONFIG_I2C0], &testI2cTransaction);
                    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
                    if(useCallback && status==SystemP_SUCCESS)
                    {
                        SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
                        SemaphoreP_destruct(&sem);
                    }
                    if(status == SystemP_SUCCESS)
                    {
                        break;
                    }
                } while (1);
                ClockP_usleep(4000);
                /* Timed read */
                I2C_Transaction_init(&testI2cTransaction);
                testI2cTransaction.targetAddress = testParams->deviceAddress;
                testI2cTransaction.writeBuf      = gI2cTxBuffer;
                testI2cTransaction.writeCount    = addrBytes;
                testI2cTransaction.readBuf       = gI2cRxBuffer;
                testI2cTransaction.readCount     = payload;
                if(useCallback)
                {
                    SemaphoreP_constructBinary(&sem, 0);
                    testI2cTransaction.arg=&sem;
                }
                t0 = ClockP_getTimeUsec();
                status = I2C_transfer(gI2cHandle[CONFIG_I2C0], &testI2cTransaction);
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
                if(useCallback)
                {
                    SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
                    SemaphoreP_destruct(&sem);
                }
                t1 = ClockP_getTimeUsec();
                uint64_t readTime = t1 - t0;
                double writeMiBps = (writeTime == 0) ? 0.0 : ((double)payload / (1024.0 * 1024.0)) / ((double)writeTime / 1e6);
                double readMiBps  = (readTime == 0) ? 0.0 : ((double)payload / (1024.0 * 1024.0)) / ((double)readTime / 1e6);
                DebugP_log("%-12s| %-11s| %-13u| %10.3f      | %10llu        | %10.3f   | %10llu\r\n",
                    modeName, Test_I2c_FreqNames[f], payload, writeMiBps, (unsigned long long)writeTime, readMiBps, (unsigned long long)readTime);
            }
            I2C_close(gI2cHandle[CONFIG_I2C0]);
            gI2cHandle[CONFIG_I2C0] = NULL;
        }
    }
    DebugP_log("\nI2C Performance Numbers Print End \r\n\n");
}

#if defined ENABLE_MT_TESTS
#if defined(SOC_AM62AX) || defined (SOC_AM62PX) || defined(SOC_AM62X)
/**
 * \brief Worker thread for multi-threaded I2C write test (callback mode).
 *
 * Test Category: Multi-thread / Robustness
 *
 * This function is executed by a worker thread in the multi-threaded I2C write/read test.
 * It opens an I2C handle in callback mode, writes a sequence of bytes to EEPROM, and reads them back
 * to verify data integrity. The function uses a semaphore to wait for transfer completion via callback.
 * After all iterations, it closes the I2C handle and signals completion to the main test thread.
 *
 * \param arg Thread ID (as void pointer, cast to int32_t).
 *
 * \return None. The thread exits via TaskP_exit().
 */
static void TestI2c_writeWorkerCb(void *arg)
{
    int32_t threadId = (int32_t)(int32_t)arg, i, iter;
    uint32_t baseAddr = (uint32_t)threadId * (TEST_I2C_WRITE_ITER + 8);
    const uint32_t addrSize = Board_i2cGetEepromAddrSize();
    uint8_t txBuf[2 + TEST_I2C_WRITE_ITER];
    uint8_t rxBuf[TEST_I2C_WRITE_ITER];
    I2C_Transaction txn;
    int32_t status;
    SemaphoreP_Object sem;

    I2C_Params params;
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_callback;
    I2C_Handle handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    for (iter = 0; iter < TEST_I2C_WRITE_ITER; iter++)
    {
        uint32_t memAddr = baseAddr + iter * TEST_I2C_WRITE_ITER;
        for (i = 0; i < TEST_I2C_WRITE_ITER; i++)
        {
            txBuf[addrSize + i] = (uint8_t)(0xD0 + threadId + i);
            rxBuf[i] = 0;
        }
        if (addrSize == 1U)
            txBuf[0] = (uint8_t)(memAddr & 0xFFU);
        else
        {
            txBuf[0] = (uint8_t)((memAddr >> 8) & 0xFFU);
            txBuf[1] = (uint8_t)(memAddr & 0xFFU);
        }
        /* Write */
        SemaphoreP_constructBinary(&sem, 0);
        I2C_Transaction_init(&txn);
        txn.targetAddress = Board_i2cGetEepromDeviceAddr();
        txn.writeBuf = txBuf;
        txn.writeCount = addrSize + TEST_I2C_WRITE_ITER;
        txn.readBuf = NULL;
        txn.readCount = 0;
        txn.arg = &sem;
        status = I2C_transfer(handle, &txn);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
        SemaphoreP_destruct(&sem);

        ClockP_usleep(5000);

        /* Read-back */
        SemaphoreP_constructBinary(&sem, 0);
        I2C_Transaction_init(&txn);
        txn.targetAddress = Board_i2cGetEepromDeviceAddr();
        txn.writeBuf = txBuf;
        txn.writeCount = addrSize;
        txn.readBuf = rxBuf;
        txn.readCount = TEST_I2C_WRITE_ITER;
        txn.arg = &sem;
        status = I2C_transfer(handle, &txn);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
        SemaphoreP_destruct(&sem);

        TEST_ASSERT_EQUAL_UINT8_ARRAY(&txBuf[addrSize], rxBuf, TEST_I2C_WRITE_ITER);
    }
    I2C_close(handle);
    SemaphoreP_post(&TestI2c_testSem);
    TaskP_exit();
}

/**
 * \brief Multi-threaded I2C write/Read test: one thread uses callback mode, one uses blocking mode.
 *
 * Test Category: Multi-thread / Robustness
 *
 * Spawns two threads: one using callback mode, one using blocking mode. Each thread opens and closes its own I2C handle.
 *
 * \param args Unused.
 */
static void TestI2c_multithreadWriteRead(void *args)
{
    TaskP_Params taskParams;
    int32_t status, i;
    /* Counting semaphore for signaling all threads completed */
    SemaphoreP_constructCounting(&TestI2c_testSem, 0, 2);

    /* Thread 0: callback mode */
    TaskP_Params_init(&taskParams);
    taskParams.priority = 3U;
    taskParams.stackSize = TEST_I2C_MT_TASK_STACK_SIZE;
    taskParams.stack = TestI2c_task1Stack[0];
    taskParams.taskMain = &TestI2c_writeWorkerCb;
    taskParams.args = (void *)(int32_t)0;
    taskParams.name = "I2CWriteCB";
    status = TaskP_construct(&TestI2c_TaskObjs[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Thread 1: blocking mode */
    TaskP_Params_init(&taskParams);
    taskParams.priority = 3U;
    taskParams.stackSize = TEST_I2C_MT_TASK_STACK_SIZE;
    taskParams.stack = TestI2c_task2Stack[0];
    taskParams.taskMain = &TestI2c_tempTask;
    taskParams.args = (void *)(int32_t)1;
    taskParams.name = "I2CTempReadBlocking";
    status = TaskP_construct(&TestI2c_TaskObjs[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for both threads to complete */
    for (i = 0; i < 2; i++)
    {
        int32_t semStatus = SemaphoreP_pend(&TestI2c_testSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, semStatus);
    }

    /* Cleanup tasks */
    TaskP_destruct(&TestI2c_TaskObjs[0]);
    TaskP_destruct(&TestI2c_TaskObjs[1]);
    SemaphoreP_destruct(&TestI2c_testSem);
}

/**
 * \brief Worker thread for multi-threaded I2C write test (callback mode) using a single I2C instance.
 *
 * Test Category: Multi-thread / Robustness
 *
 * Each thread performs non-blocking I2C writes to EEPROM and waits for completion via callback.
 * Validates driver thread safety and callback operation under concurrency.
 *
 * \param arg Thread ID (as void pointer).
 */
static void TestI2c_callbackSingleInstance(void *arg)
{
    int32_t threadId = (int32_t)(int32_t)arg;
    uint32_t i, iter;
    const uint32_t addrSize = Board_i2cGetEepromAddrSize();
    uint8_t txBuf[2 + TEST_I2C_CB_MT_BYTES];      /* address + write payload */
    uint8_t rxBuf[TEST_I2C_CB_MT_BYTES];          /* read-back buffer */
    I2C_Transaction testI2cTransaction;
    int32_t status;
    uint32_t baseAddr = (uint32_t)threadId * (TEST_I2C_CB_MT_BYTES + 8);
    SemaphoreP_Object sem;

    for (iter = 0; iter < TEST_I2C_WRITE_ITER; ++iter)
    {
        uint32_t memAddr = baseAddr + iter * TEST_I2C_CB_MT_BYTES;

        /* Prepare write payload and clear read-back buffer */
        for (i = 0; i < TEST_I2C_CB_MT_BYTES; ++i)
        {
            txBuf[addrSize + i] = (uint8_t)(0xD0 + threadId + i);
            rxBuf[i] = 0;
        }

        /* Memory address bytes */
        if (addrSize == 1U)
        {
            txBuf[0] = (uint8_t)(memAddr & 0xFFU);
        }
        else
        {
            txBuf[0] = (uint8_t)((memAddr >> 8) & 0xFFU);
            txBuf[1] = (uint8_t)(memAddr & 0xFFU);
        }

        /* WRITE (callback) */
        SemaphoreP_constructBinary(&sem, 0);
        I2C_Transaction_init(&testI2cTransaction);
        testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
        testI2cTransaction.writeBuf      = txBuf;
        testI2cTransaction.writeCount    = addrSize + TEST_I2C_CB_MT_BYTES;
        testI2cTransaction.readBuf       = NULL;
        testI2cTransaction.readCount     = 0;
        testI2cTransaction.arg           = &sem;

        DebugP_log("CB_MT[%d] iter %d: WRITE memAddr=0x%04X len=%u\r\n",
                   threadId, (int32_t)iter, (unsigned)memAddr, testI2cTransaction.writeCount);

        status = I2C_transfer(gI2cHandle[CONFIG_I2C0], &testI2cTransaction);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
        SemaphoreP_destruct(&sem);

        /* EEPROM write cycle delay */
        ClockP_usleep(5000);

        /* READ-BACK (callback) */
        SemaphoreP_constructBinary(&sem, 0);
        I2C_Transaction_init(&testI2cTransaction);
        testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
        testI2cTransaction.writeBuf      = txBuf;          /* only address bytes sent */
        testI2cTransaction.writeCount    = addrSize;
        testI2cTransaction.readBuf       = rxBuf;
        testI2cTransaction.readCount     = TEST_I2C_CB_MT_BYTES;
        testI2cTransaction.arg           = &sem;

        DebugP_log("CB_MT[%d] iter %d: READBACK memAddr=0x%04X len=%u\r\n",
                   threadId, (int32_t)iter, (unsigned)memAddr, testI2cTransaction.readCount);

        status = I2C_transfer(gI2cHandle[CONFIG_I2C0], &testI2cTransaction);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
        SemaphoreP_destruct(&sem);

        /* Verify payload */
        TEST_ASSERT_EQUAL_UINT8_ARRAY(&txBuf[addrSize], rxBuf, TEST_I2C_CB_MT_BYTES);
    }

    SemaphoreP_post(&TestI2c_testSem);
    TaskP_exit();
}

/**
 * \brief Multi-threaded I2C write test (callback mode).
 *
 * Test Category: Multi-thread / Robustness
 *
 * Spawns multiple threads, each performing non-blocking I2C writes to EEPROM with callback.
 * Verifies thread safety and correct callback operation under concurrent access.
 *
 * \param args Unused.
 */
static void TestI2c_callbackMultithreadWriteTest(void *args)
{
    TaskP_Params taskParams;
    int32_t threadLoop, i;
    /* Counting semaphore to wait for all threads */
    SemaphoreP_constructCounting(&TestI2c_testSem, 0, TEST_I2C_WRITE_THREADS);

    I2C_Params params;
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_callback;
    gI2cHandle[CONFIG_I2C0] = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(gI2cHandle[CONFIG_I2C0]);

    for (threadLoop = 0; threadLoop < TEST_I2C_WRITE_THREADS; threadLoop++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.priority = 3U;
        taskParams.stackSize = TEST_I2C_MT_TASK_STACK_SIZE;
        taskParams.stack = TestI2c_task1Stack[threadLoop];
        taskParams.taskMain = TestI2c_callbackSingleInstance;
        taskParams.name = "CBThread";

        TaskP_construct(&TestI2c_TaskObjs[threadLoop], &taskParams);
    }

    /* Wait for all threads to complete */
    for (i = 0; i < TEST_I2C_WRITE_THREADS; i++)
    {
        int32_t status = SemaphoreP_pend(&TestI2c_testSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    for (threadLoop = 0; threadLoop < TEST_I2C_WRITE_THREADS; threadLoop++)
    {
        TaskP_destruct(&TestI2c_TaskObjs[threadLoop]);
    }

    I2C_close(gI2cHandle[CONFIG_I2C0]);
    SemaphoreP_destruct(&TestI2c_testSem);
}

/**
 * \brief EEPROM write/read worker task for multi-threaded test.
 *
 * This task writes a byte to EEPROM and reads it back, verifying data integrity.
 * Used in multi-threaded tests to validate concurrent access.
 *
 * \param arg Unused.
 */
static void TestI2c_eepromTask(void *arg)
{
    I2C_Handle i2cHandle;
    I2C_Params params;
    I2C_Transaction testI2cTransaction;
    uint8_t txBuf[3];
    uint8_t rxBuf[1];
    int32_t status;

    I2C_Params_init(&params);
    i2cHandle = I2C_getHandle(CONFIG_I2C0);
    if(i2cHandle)
    {
        I2C_close(i2cHandle);
    }
    i2cHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(i2cHandle);

    txBuf[0] = 0x00; txBuf[1] = 0x10; txBuf[2] = 0xAB;
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.writeBuf = txBuf;
    testI2cTransaction.writeCount = 3;
    testI2cTransaction.readBuf = NULL;
    testI2cTransaction.readCount = 0;
    testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();

    status = I2C_transfer(i2cHandle, &testI2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

     ClockP_usleep(5000);

    /* Read back the byte from EEPROM */
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.writeBuf = txBuf;
    testI2cTransaction.writeCount = 2;
    testI2cTransaction.readBuf = rxBuf;
    testI2cTransaction.readCount = 1;
    testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();

    status = I2C_transfer(i2cHandle, &testI2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT8(txBuf[2], rxBuf[0]);
    I2C_close(i2cHandle);
    SemaphoreP_post(&TestI2c_testSem);
    TaskP_exit();
}

/**
 * \brief Worker thread for multi-threaded I2C temperature sensor read.
 *
 * Reads temperature from a sensor via I2C and logs the value.
 * Used in multi-threaded tests to validate concurrent access.
 *
 * \param arg Unused.
 */
static void TestI2c_tempTask(void *arg)
{
    I2C_Handle i2cHandle;
    I2C_Params i2cParams;
    I2C_Transaction testI2cTransaction;
    uint8_t txBuffer[1];
    uint8_t rxBuffer[2];
    int16_t temperature;
    int32_t status;

    I2C_Params_init(&i2cParams);
    if (gI2cHandle[CONFIG_I2C2] != NULL)
    {
        I2C_close(gI2cHandle[CONFIG_I2C2]);
        gI2cHandle[CONFIG_I2C2] = NULL;
    }
    i2cHandle = I2C_open(CONFIG_I2C2, &i2cParams);
    TEST_ASSERT_NOT_NULL(i2cHandle);
    /* Probe TMP100 */
    status = I2C_probe(i2cHandle, Board_getSocTemperatureSensorAddr());
    DebugP_log("TMP100 Probe = %d\r\n", status);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Read temperature register */
    txBuffer[0] = 0x00;
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.writeBuf     = txBuffer;
    testI2cTransaction.writeCount   = 1;
    testI2cTransaction.readBuf      = rxBuffer;
    testI2cTransaction.readCount    = 2;
    testI2cTransaction.targetAddress = Board_getSocTemperatureSensorAddr();

    status = I2C_transfer(i2cHandle, &testI2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    if (status == SystemP_SUCCESS)
    {
        /* Create 16 bit temperature */
        temperature = ((uint16_t)rxBuffer[0] << TEST_I2C_TMP100_SIGN_BIT_POS) | rxBuffer[1];
        /*
        * 4 LSBs of temperature are 0 according to datasheet
        * since temperature is stored in 12 bits. Therefore,
        * right shift by 4 places
        */
        temperature >>= TEST_I2C_TMP100_TEMP_SHIFT;
        /*
        * If the 12th bit of temperature is set '1' (equivalent to 8th bit of the first byte read),
        * then we have a 2's complement negative value which needs to be sign extended
        */
        if (rxBuffer[0] & TEST_I2C_TMP100_SIGN_BIT)
        {
            temperature |= TEST_I2C_TMP100_SIGN_EXTEND_MASK;
        }
        /* Of the 12 bits of temperature, 4 LSBs are for decimal point according to datasheet so divide by 16 */
        DebugP_log("[I2C2][TMP100] Temperature = %d.%d °C\r\n",
                   temperature / TEST_I2C_TMP100_TEMP_DIV,
                   (temperature % TEST_I2C_TMP100_TEMP_DIV) * TEST_I2C_TMP100_TEMP_FRAC_SCALE);
    }

    I2C_close(i2cHandle);
    SemaphoreP_post(&TestI2c_testSem);
    TaskP_exit();
}

/**
 * \brief Multi-threaded test: concurrent EEPROM write and temperature sensor read.
 *
 * Test Category: Multi-thread / Robustness
 *
 * Spawns two threads: one writes to EEPROM (I2C0), the other reads from a temperature sensor (I2C2).
 * Verifies correct operation and thread safety when different I2C peripherals are accessed concurrently.
 *
 * \param args Unused.
 */
static void TestI2c_multithreadEepromAndTemp(void *args)
{
    TaskP_Params taskEeprom, taskTemp ;
    int32_t i, status;

    /* Construct counting semaphore for 2 threads */
    status = SemaphoreP_constructCounting(&TestI2c_testSem, 0, 2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* EEPROM task */
    TaskP_Params_init(&taskEeprom);
    taskEeprom.priority       = 3U;
    taskEeprom.stack          = TestI2c_task1Stack[0];
    taskEeprom.stackSize      = TEST_I2C_MT_TASK_STACK_SIZE;
    taskEeprom.name           = "mtEeprom";
    taskEeprom.taskMain       = &TestI2c_eepromTask;
    status = TaskP_construct(&TestI2c_taskObjsEepromTemp[0], &taskEeprom);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskTemp);
    taskTemp.priority       = 3U;
    taskTemp.stack          = TestI2c_task2Stack[0];
    taskTemp.stackSize      = TEST_I2C_MT_TASK_STACK_SIZE;
    taskTemp.name           = "TestI2c_tempTask";
    taskTemp.taskMain       = &TestI2c_tempTask;
    status = TaskP_construct(&TestI2c_taskObjsEepromTemp[1], &taskTemp);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    /* Wait for both threads to complete */
    for (i = 0; i < 2; i++)
    {
        int32_t status = SemaphoreP_pend(&TestI2c_testSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Cleanup */
    TaskP_destruct(&TestI2c_taskObjsEepromTemp[0]);
    TaskP_destruct(&TestI2c_taskObjsEepromTemp[1]);
    SemaphoreP_destruct(&TestI2c_testSem);
}

/**
 * \brief Worker thread for multi-threaded I2C temperature sensor read with shared handle.
 *
 * Reads temperature from a sensor using a shared I2C handle.
 *
 * \param arg Pointer to TestI2cThreadArgs structure.
 */
static void TestI2c_tempTaskSharedHandle(void *arg)
{
    TestI2cThreadArgs *threadArgs = (TestI2cThreadArgs *)arg;
    I2C_Handle i2cHandle = threadArgs->handle;
    I2C_Transaction testI2cTransaction;
    uint8_t txBuffer[1];
    uint8_t rxBuffer[2];
    int16_t temperature;
    int32_t status;

    /* Probe TMP100 */
    status = I2C_probe(i2cHandle, Board_getSocTemperatureSensorAddr());
    DebugP_log("TMP100 Probe = %d\r\n", status);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Read temperature register */
    txBuffer[0] = 0x00;
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.writeBuf     = txBuffer;
    testI2cTransaction.writeCount   = 1;
    testI2cTransaction.readBuf      = rxBuffer;
    testI2cTransaction.readCount    = 2;
    testI2cTransaction.targetAddress = Board_getSocTemperatureSensorAddr();

    status = I2C_transfer(i2cHandle, &testI2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    if (status == SystemP_SUCCESS)
    {
        /* Create 16 bit temperature */
        temperature = ((uint16_t)rxBuffer[0] << TEST_I2C_TMP100_SIGN_BIT_POS) | rxBuffer[1];
        temperature >>= TEST_I2C_TMP100_TEMP_SHIFT;
        if (rxBuffer[0] & TEST_I2C_TMP100_SIGN_BIT)
        {
            temperature |= TEST_I2C_TMP100_SIGN_EXTEND_MASK;
        }
        DebugP_log("[I2C2][TMP100] Temperature = %d.%d °C\r\n",
                   temperature / TEST_I2C_TMP100_TEMP_DIV,
                   (temperature % TEST_I2C_TMP100_TEMP_DIV) * TEST_I2C_TMP100_TEMP_FRAC_SCALE);
    }

    SemaphoreP_post(&TestI2c_testSem);
    TaskP_exit();
}
/**
 * \brief Multi-threaded I2C write test thread (blocking mode).
 *
 * Test Category: Multi-thread / Robustness
 *
 * Spawns multiple threads, each opening and closing its own I2C handle and writing to EEPROM.
 * Verifies thread safety and correct operation under concurrent access with per-thread handles.
 *
 * \param args Unused.
 */
static void TestI2c_multithreadReadTestSharedOpen(void* args)
{
    TaskP_Params taskParams;
    int i, status;
    I2C_Params params;
    I2C_Handle handle;
    TestI2cThreadArgs threadArgs[TEST_I2C_WRITE_THREADS];
    /* Construct counting semaphore for thread completion */
    status = SemaphoreP_constructCounting(&TestI2c_testSem, 0, TEST_I2C_WRITE_THREADS);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

    /* Open I2C handle once and share */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_BLOCKING;
    handle = I2C_open(CONFIG_I2C2, &params);
    TEST_ASSERT_NOT_NULL(handle);

    /* Spawn worker threads */
    for (i = 0; i < TEST_I2C_WRITE_THREADS; i++)
    {
        threadArgs[i].threadId = i;
        threadArgs[i].handle = handle;

        TaskP_Params_init(&taskParams);
        taskParams.priority = 3;
        taskParams.stackSize = TEST_I2C_MT_TASK_STACK_SIZE;
        taskParams.stack     = TestI2c_task1Stack[i];
        taskParams.args = &threadArgs[i];
        taskParams.name = "TestI2c_tempTaskSharedHandle";
        taskParams.taskMain = TestI2c_tempTaskSharedHandle;

        int32_t status = TaskP_construct(&TestI2c_TaskObjs[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(status,SystemP_SUCCESS);
    }

    /* Wait for all threads to complete */
    for (i = 0; i < TEST_I2C_WRITE_THREADS; i++)
    {
        int32_t status = SemaphoreP_pend(&TestI2c_testSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Cleanup */
    for (i = 0; i < TEST_I2C_WRITE_THREADS; i++)
    {
        TaskP_destruct(&TestI2c_TaskObjs[i]);
    }
    I2C_close(handle);
    SemaphoreP_destruct(&TestI2c_testSem);
}

/**
 * \brief Worker thread for multi-threaded I2C write test with shared I2C handle (callback mode).
 *
 * Performs a write then reads back and verifies the data for every iteration.
 *
 * \param arg Thread ID (as void pointer).
 */
static void TestI2c_writeReadSharedCallBack(void *arg)
{
    int32_t threadId = (int32_t)(int32_t)arg;
    const uint32_t addrSize = Board_i2cGetEepromAddrSize();
    uint8_t txBuf[2 + TEST_I2C_WRITE_ITER];              /* address + payload */
    uint8_t rxBuf[TEST_I2C_WRITE_ITER];               /* read-back payload */
    I2C_Transaction testI2cTransaction;
    int32_t status;
    uint32_t iter, i;
    uint32_t baseAddr = (uint32_t)threadId * (TEST_I2C_WRITE_ITER + 8);
    SemaphoreP_Object sem;

    for (iter = 0; iter < TEST_I2C_WRITE_ITER; iter++)
    {
        uint32_t memAddr = baseAddr + iter * TEST_I2C_WRITE_ITER;

        /* Prepare payload */
        for (i = 0; i < TEST_I2C_WRITE_ITER; i++)
        {
            txBuf[addrSize + i] = (uint8_t)(0xE0 + threadId + i);
            rxBuf[i] = 0;
        }

        /* Prepare address */
        if (addrSize == 1U)
        {
            txBuf[0] = (uint8_t)(memAddr & 0xFFU);
        }
        else
        {
            txBuf[0] = (uint8_t)((memAddr >> 8) & 0xFFU);
            txBuf[1] = (uint8_t)(memAddr & 0xFFU);
        }

        /* Write transaction (callback mode) */
        SemaphoreP_constructBinary(&sem, 0);
        I2C_Transaction_init(&testI2cTransaction);
        testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
        testI2cTransaction.writeBuf      = txBuf;
        testI2cTransaction.writeCount    = addrSize + TEST_I2C_WRITE_ITER;
        testI2cTransaction.readBuf       = NULL;
        testI2cTransaction.readCount     = 0;
        testI2cTransaction.arg           = &sem;

        DebugP_log("CB_SHARED_WRITE[%d] iter %d: WRITE memAddr=0x%04X len=%u\r\n",
                   threadId, (int32_t)iter, (unsigned)memAddr, testI2cTransaction.writeCount);

        status = I2C_transfer(TestI2c_SharedHandle, &testI2cTransaction);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
        SemaphoreP_destruct(&sem);

        /* EEPROM write cycle delay */
        ClockP_usleep(5000);

        /* Read-back transaction (re-use address bytes in txBuf) */
        SemaphoreP_constructBinary(&sem, 0);
        I2C_Transaction_init(&testI2cTransaction);
        testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
        testI2cTransaction.writeBuf      = txBuf;          /* only address bytes sent */
        testI2cTransaction.writeCount    = addrSize;
        testI2cTransaction.readBuf       = rxBuf;
        testI2cTransaction.readCount     = TEST_I2C_WRITE_ITER;
        testI2cTransaction.arg           = &sem;

        DebugP_log("CB_SHARED_WRITE[%d] iter %d: READBACK memAddr=0x%04X len=%u\r\n",
                   threadId, (int32_t)iter, (unsigned)memAddr, testI2cTransaction.readCount);

        status = I2C_transfer(TestI2c_SharedHandle, &testI2cTransaction);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
        SemaphoreP_destruct(&sem);

        /* Verify payload */
        TEST_ASSERT_EQUAL_UINT8_ARRAY(&txBuf[addrSize], rxBuf, TEST_I2C_WRITE_ITER);
    }

    /* Signal main test thread */
    SemaphoreP_post(&TestI2c_testSem);
    TaskP_exit();
}

/**
 * \brief Multi-threaded I2C write test with shared I2C handle (callback mode).
 *
 * Test Category: Multi-thread / Robustness
 *
 * Spawns multiple threads, each performing non-blocking I2C writes to EEPROM using a single shared I2C handle.
 * Verifies thread safety and correct callback operation under concurrent access with shared instance.
 *
 * \param args Unused.
 */
static void TestI2c_multithreadWriteTestSharedOpenCb(void *args)
{
    I2C_Params params;
    TaskP_Params taskParams;
    int32_t status;
    uint32_t i;

    /* Construct counting semaphore */
    status = SemaphoreP_constructCounting(&TestI2c_testSem, 0, TEST_I2C_WRITE_THREADS);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

    /* Open shared I2C handle (callback mode) */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_callback;

    if (TestI2c_SharedHandle != NULL)
    {
        I2C_close(TestI2c_SharedHandle);
    }
    TestI2c_SharedHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(TestI2c_SharedHandle);

    DebugP_log("Starting I2C multithread shared write (callback mode)\r\n");

    /* Create worker tasks */
    for (i = 0; i < TEST_I2C_WRITE_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.priority  = 3U;
        taskParams.stack     = TestI2c_task1Stack[i];
        taskParams.stackSize = TEST_I2C_MT_TASK_STACK_SIZE;
        taskParams.args      = (void *)(int32_t)i;
        taskParams.taskMain  = &TestI2c_writeReadSharedCallBack;
        taskParams.name      = "TestI2c_writeReadSharedCallBack";

        status = TaskP_construct(&TestI2c_TaskObjs[i], &taskParams);
        TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    }

    /* Wait for all threads to finish */
    for (i = 0; i < TEST_I2C_WRITE_THREADS; i++)
    {
        SemaphoreP_pend(&TestI2c_testSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    DebugP_log("All I2C callback threads completed.\r\n");

    /* Cleanup */
    for (i = 0; i < TEST_I2C_WRITE_THREADS; i++)
    {
        TaskP_destruct(&TestI2c_TaskObjs[i]);
    }

    I2C_close(TestI2c_SharedHandle);
    TestI2c_SharedHandle = NULL;
    SemaphoreP_destruct(&TestI2c_testSem);
}
#endif
#if defined(SOC_AM62DX)
/**
 * \brief Worker thread for multi-threaded EEPROM access using a shared I2C handle.
 *
 * Test Category: Multi-thread / Robustness
 *
 * This function is executed by a worker thread in a multi-threaded test scenario.
 * It performs a write to the EEPROM and then reads back the data using a shared I2C handle.
 * After verifying the data, it signals completion to the test harness and exits the thread.
 *
 * \param arg Unused.
 *
 * \return None. The thread exits via TaskP_exit().
 */
static void TestI2c_multiThreadEepromsharedHnadle(void *arg)
{
    uint8_t txBuf[8], rxBuf[8];
    I2C_Transaction testI2cTransaction;
    int32_t status;

    /* Prepare data */
    txBuf[0] = 0x00;
    txBuf[1] = 0x10;
    txBuf[2] = 0xAB;
    memset(rxBuf, 0, sizeof(rxBuf));

    /* Write */
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.writeBuf = txBuf;
    testI2cTransaction.writeCount = 3;
    testI2cTransaction.readBuf = NULL;
    testI2cTransaction.readCount = 0;
    testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();

    status = I2C_transfer(TestI2c_SharedHandle, &testI2cTransaction);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("mtEeprom: I2C_write failed: %d\n", status);
    }
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

    /* Allow EEPROM write cycle to finish */
    ClockP_usleep(5000);

    /* Read-back: set address, then read 1 byte */
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.writeBuf = txBuf;      // address bytes only
    testI2cTransaction.writeCount = 2;
    testI2cTransaction.readBuf = rxBuf;
    testI2cTransaction.readCount = 1;
    testI2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();

    status = I2C_transfer(TestI2c_SharedHandle, &testI2cTransaction);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("mtEeprom: I2C_read failed: %d\n", status);
    }
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

    /* Signal completion to test harness */
    SemaphoreP_post(&TestI2c_testSem);
    TaskP_exit();
}

/**
 * \brief Worker thread for multi-threaded temperature sensor access using a shared I2C handle.
 *
 * Test Category: Multi-thread / Robustness
 *
 * This function is executed by a worker thread in a multi-threaded test scenario.
 * It reads temperature data from a sensor using a shared I2C handle, logs the result,
 * and signals completion to the test harness before exiting the thread.
 *
 * \param arg Unused.
 *
 * \return None. The thread exits via TaskP_exit().
 */
static void TestI2c_multiThreadTempSharedHandle(void *arg)
{
    I2C_Transaction testI2cTransaction;
    uint8_t txBuffer[1];
    uint8_t rxBuffer[2];
    int16_t temperature;
    int32_t status;

    /* Probe TMP100 */
    status = I2C_probe(TestI2c_SharedHandle, Board_getSocTemperatureSensorAddr());
    DebugP_log("TMP100 Probe = %d\r\n", status);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Read temperature register */
    txBuffer[0] = 0x00;
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.writeBuf     = txBuffer;
    testI2cTransaction.writeCount   = 1;
    testI2cTransaction.readBuf      = rxBuffer;
    testI2cTransaction.readCount    = 2;
    testI2cTransaction.targetAddress = Board_getSocTemperatureSensorAddr();

    status = I2C_transfer(TestI2c_SharedHandle, &testI2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    if (status == SystemP_SUCCESS)
    {
        /* Create 16 bit temperature */
        temperature = ((uint16_t)rxBuffer[0] << TEST_I2C_TMP100_SIGN_BIT_POS) | rxBuffer[1];
        /*
        * 4 LSBs of temperature are 0 according to datasheet
        * since temperature is stored in 12 bits. Therefore,
        * right shift by 4 places
        */
        temperature >>= TEST_I2C_TMP100_TEMP_SHIFT;
        /*
        * If the 12th bit of temperature is set '1' (equivalent to 8th bit of the first byte read),
        * then we have a 2's complement negative value which needs to be sign extended
        */
        if (rxBuffer[0] & TEST_I2C_TMP100_SIGN_BIT)
        {
            temperature |= TEST_I2C_TMP100_SIGN_EXTEND_MASK;
        }
        /* Of the 12 bits of temperature, 4 LSBs are for decimal point according to datasheet so divide by 16 */
        DebugP_log("[I2C2][TMP100] Temperature = %d.%d °C\r\n",
                   temperature / TEST_I2C_TMP100_TEMP_DIV,
                   (temperature % TEST_I2C_TMP100_TEMP_DIV) * TEST_I2C_TMP100_TEMP_FRAC_SCALE);
    }
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    SemaphoreP_post(&TestI2c_testSem);
    TaskP_exit();
}

/**
 * \brief Multi-threaded test: shared I2C handle with EEPROM and temperature sensor access.
 *
 * Test Category: Multi-thread / Robustness
 *
 * Spawns two threads: one accesses EEPROM, the other accesses a temperature sensor, both using
 * the same shared I2C handle. Verifies correct operation and thread safety when multiple
 * peripherals are accessed concurrently via a single I2C instance.
 *
 * \param args Unused.
 */
static void TestI2c_multithreadSharedEepromTemp(void *args)
{

    int32_t loopVar, status;
    TaskP_Params taskEeprom, taskTemp;
    status =  SemaphoreP_constructCounting(&TestI2c_testSem, 0, 2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    I2C_Params params;
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_BLOCKING;
    if (TestI2c_SharedHandle != NULL)
    {
        I2C_close(TestI2c_SharedHandle);
        TestI2c_SharedHandle = NULL;
    }
    TestI2c_SharedHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(TestI2c_SharedHandle);

    TaskP_Params_init(&taskEeprom);
    taskEeprom.priority       = 3U;
    taskEeprom.stack          = TestI2c_task1Stack[0];
    taskEeprom.stackSize      = TEST_I2C_MT_TASK_STACK_SIZE;
    taskEeprom.name           = "mtEeprom";
    taskEeprom.taskMain       = &TestI2c_multiThreadEepromsharedHnadle;

    status = TaskP_construct(&TestI2c_taskObjsEepromTemp[0], &taskEeprom);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskTemp);
    taskTemp.priority       = 3U;
    taskTemp.stack          = TestI2c_task2Stack[0];
    taskTemp.stackSize      = TEST_I2C_MT_TASK_STACK_SIZE;
    taskTemp.name           = "taskTemp";
    taskTemp.taskMain       = &TestI2c_multiThreadTempSharedHandle;

    status = TaskP_construct(&TestI2c_taskObjsEepromTemp[1], &taskTemp);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        status = SemaphoreP_pend(&TestI2c_testSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(status, SystemP_SUCCESS);
    }

    TaskP_destruct(&TestI2c_taskObjsEepromTemp[0]);
    TaskP_destruct(&TestI2c_taskObjsEepromTemp[1]);
    SemaphoreP_destruct(&TestI2c_testSem);
    I2C_close(TestI2c_SharedHandle);
}
#endif
#endif

void test_i2c_dynamic_coverage(void* args)
{
#if !defined (SOC_AM275X)
    uint32_t baseAddr;
#endif
    int32_t retVal;
    I2C_TestParams      testParams;

    test_i2c_set_test_params(&testParams, 4);
    retVal = test_i2c_nack_error_check(&testParams);
    TEST_ASSERT_EQUAL(retVal, I2C_STS_ERR_NO_ACK);

    test_i2c_set_test_params(&testParams, 0);
    retVal = test_i2c_write_read_mem(&testParams);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    test_i2c_set_test_params(&testParams, 1);
    testParams.i2cParams.bitRate = I2C_100KHZ;
    retVal = test_i2c_write_read_mem(&testParams);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    test_i2c_set_test_params(&testParams, 5);
    retVal = test_i2c_write_read_mem_error_checks(&testParams,0);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_write_read_mem_error_checks(&testParams,1);
    TEST_ASSERT_EQUAL(retVal, SystemP_TIMEOUT);

    retVal = test_i2c_write_read_mem_error_checks(&testParams,2);
    TEST_ASSERT_EQUAL(retVal, SystemP_FAILURE);

    test_i2c_set_test_params(&testParams, 2);
    retVal = test_i2c_write_read_mem(&testParams);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    test_i2c_set_test_params(&testParams, 3);
    retVal = test_i2c_write_read_mem(&testParams);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    test_i2c_set_test_params(&testParams, 4);
    retVal = test_i2c_write_read_mem(&testParams);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    test_i2c_set_test_params(&testParams, 5);
    retVal = test_i2c_write_read_mem(&testParams);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_write_read_mem_error_checks(&testParams,0);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_write_read_mem_error_checks(&testParams,1);
    TEST_ASSERT_EQUAL(retVal, SystemP_TIMEOUT);

    retVal = test_i2c_write_read_mem_error_checks(&testParams,2);
    TEST_ASSERT_EQUAL(retVal, SystemP_FAILURE);

    test_i2c_set_test_params(&testParams, 0);
    retVal = test_i2c_write_read_mem(&testParams);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    test_i2c_set_test_params(&testParams, 5);
    gI2cConfig[CONFIG_I2C0].hwAttrs->enableIntr = false;
    retVal = test_i2c_memparams(&testParams,DEFAULT_MEM_TRANSACTION,TX);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_memparams(&testParams,INVALID_MEM_ADDR_SIZE,TX);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_memparams(&testParams,INVALID_MEM_PARAMS,TX);
    TEST_ASSERT_EQUAL(retVal, I2C_STS_ERR_INVALID_PARAM);

    retVal = test_i2c_memparams(&testParams,DEFAULT_MEM_TRANSACTION,RX);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_memparams(&testParams,INVALID_MEM_ADDR_SIZE,RX);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_memparams(&testParams,INVALID_MEM_PARAMS,RX);
    TEST_ASSERT_EQUAL(retVal, I2C_STS_ERR_INVALID_PARAM);

    test_i2c_set_test_params(&testParams, 0);
    retVal = test_i2c_memparams(&testParams,DEFAULT_MEM_TRANSACTION,TX);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_memparams(&testParams,INVALID_MEM_ADDR_SIZE,TX);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_memparams(&testParams,INVALID_MEM_PARAMS,TX);
    TEST_ASSERT_EQUAL(retVal, I2C_STS_ERR_INVALID_PARAM);

    retVal = test_i2c_memparams(&testParams,DEFAULT_MEM_TRANSACTION,RX);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_memparams(&testParams,INVALID_MEM_ADDR_SIZE,RX);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_memparams(&testParams,INVALID_MEM_PARAMS,RX);
    TEST_ASSERT_EQUAL(retVal, I2C_STS_ERR_INVALID_PARAM);

    retVal = test_i2c_error_checks();
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_differentSpeeds(I2C_100KHZ,DEFAULT);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_differentSpeeds(I2C_1P0MHZ,DEFAULT);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_differentSpeeds(I2C_3P4MHZ,DEFAULT);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_differentSpeeds(INVALID_FREQ,DEFAULT);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_differentSpeeds(INVALID_FREQ,BUS_BUSY);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_differentSpeeds(INVALID_FREQ,NULL_HANDLE);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* Open negative test */
    retVal = test_i2c_open_error();
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* i2c recover test */
    retVal = test_i2c_recover_bus();
    TEST_ASSERT_EQUAL(retVal, I2C_STS_ERR);

#if !defined (SOC_AM275X)
    /* address validation test */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_I2C1_CFG_BASE);
    retVal = test_i2c_baseaddress(baseAddr);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* address validation test */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_I2C2_CFG_BASE);
    retVal = test_i2c_baseaddress(baseAddr);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    /* address validation test */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_I2C3_CFG_BASE);
    retVal = test_i2c_baseaddress(baseAddr);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

#if !defined (SOC_AM62LX)
    /* address validation test */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_I2C0_CFG_BASE);
    retVal = test_i2c_baseaddress(baseAddr);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
#endif

    /* address validation test */
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_I2C0_CFG_BASE);
    retVal = test_i2c_baseaddress(baseAddr);
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);
#endif

    retVal = test_i2c_timeout_negative();
    TEST_ASSERT_EQUAL(retVal, I2C_STS_ERR_NO_ACK);

    /* lld_init test case */
    retVal = test_i2c_lld();
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

    retVal = test_i2c_handle_errors();
    TEST_ASSERT_EQUAL(retVal, SystemP_SUCCESS);

}

/**
 * \brief Fuzz test for opening and closing I2C driver with random parameters.
 *
 * Test Category: Negative test case
 *
 * This function performs a fuzz test on the I2C driver by randomly opening and closing
 * I2C instances. It is intended to validate the robustness of the driver against
 * unexpected or invalid input scenarios.
 *
 * \param args Pointer to arguments for the fuzz test, typically containing random seed or configuration.
 */
void TestI2c_openCloseFuzzRand(void *args)
{
    I2C_Params i2cParams;
    I2C_Handle handle;
    int32_t i;
    DebugP_log("Starting I2C fuzz test (open/close + NULL cases)\r\n");

    for (i = 0; i < TEST_I2C_FUZZ_ITERATIONS; i++)
    {
        I2C_Params_init(&i2cParams);

        i2cParams.transferMode = (rand() % 2 == 0) ? I2C_MODE_BLOCKING : I2C_MODE_CALLBACK;
        i2cParams.bitRate = (rand() % 2 == 0) ? I2C_100KHZ : I2C_400KHZ;

        handle = I2C_open(CONFIG_I2C0, &i2cParams);
        TEST_ASSERT_NOT_NULL(handle);
        DebugP_log(" Open succeeded. Closing handle...\r\n");
        I2C_close(handle);
        DebugP_log(" Close succeeded.\r\n");
    }
}

 #if (defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62X)) && defined(ENABLE_TARGET_EXTERNAL_LOOPBACK)
 static void test_i2c_targetCallback(I2C_Handle handle,I2C_Transaction *msg,int32_t transferStatus)
{

    if (msg && msg->arg != NULL)
    {
        SemaphoreP_post((SemaphoreP_Object*)msg->arg);
    }
}

/**
 * \brief Executes a sequence of write operations in I2C target mode for testing purposes.
 *
 * Test Category: Functionality
 *
 * This function is designed to test the I2C peripheral operating in target mode.
 * It performs a series of write transactions, simulating data reception from an I2C controller.
 * The function may validate received data, handle protocol events, and ensure correct target mode behavior.
 *
 * \param args Pointer to arguments or configuration data required for the test sequence.
 */
static void TestI2c_targetModeWriteSeq(void* args)
{
    I2C_Params params;
    I2C_Handle targetHandle, hostControllerHandle;
    I2C_Transaction txnTarget, txnhostController;
    int32_t status, i;

    SemaphoreP_constructBinary(&TestI2c_TargetSem, 0);
    /* Setup Target mode */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_targetCallback;
    targetHandle = I2C_getHandle(CONFIG_I2C1);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    targetHandle = I2C_open(CONFIG_I2C1, &params);
    DebugP_assert(targetHandle != NULL);

    I2C_Transaction_init(&txnTarget);
    txnTarget.controllerMode = false;
    txnTarget.readBuf    = TestI2c_targetRxBuf;       /* receive buffer */
    txnTarget.readCount  = sizeof(TestI2c_targetRxBuf);
    txnTarget.writeBuf   = NULL;              /* not writing to controller */
    txnTarget.writeCount = 0;
    txnTarget.arg        = &TestI2c_TargetSem;

    status = I2C_transfer(targetHandle, &txnTarget);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Setup controller */
    I2C_Params_init(&params);
    hostControllerHandle = I2C_getHandle(CONFIG_I2C0);
    if(hostControllerHandle)
    {
        I2C_close(hostControllerHandle);
    }
    hostControllerHandle = I2C_open(CONFIG_I2C0, &params);
    DebugP_assert(hostControllerHandle != NULL);

    for (i = 0; i < sizeof(TestI2c_controllerTxBuf); i++)
    {
        TestI2c_controllerTxBuf[i] = (uint8_t)(i + 0x10);  /* Example pattern */
    }

    /* controller write */
    I2C_Transaction_init(&txnhostController);
    txnhostController.writeBuf   = TestI2c_controllerTxBuf;
    txnhostController.writeCount = sizeof(TestI2c_controllerTxBuf);
    txnhostController.readBuf    = NULL;
    txnhostController.readCount  = 0;
    txnhostController.targetAddress = 0x10;

    status = I2C_transfer(hostControllerHandle, &txnhostController);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_pend(&TestI2c_TargetSem, 1000);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    SemaphoreP_destruct(&TestI2c_TargetSem);
    DebugP_log("Target received first byte = 0x%02X\r\n", TestI2c_targetRxBuf[0]);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(TestI2c_controllerTxBuf, TestI2c_targetRxBuf, sizeof(TestI2c_controllerTxBuf));
    I2C_close(hostControllerHandle);
    I2C_close(targetHandle);
}

/**
 * \brief Executes a combined write-read operation in I2C target mode for testing purposes.
 *
 * Test Category: Functionality
 *
 * This function performs a sequence where data is first written to the I2C target,
 * followed by a read operation. It is used to validate the correct behavior of the
 * I2C driver in target mode when handling combined transactions.
 *
 * \param args Pointer to arguments required for the test, typically including configuration
 *             and data buffers for the write and read operations.
 */
static void TestI2c_targetModeCombinedWriteRead(void *args)
{
    I2C_Params params;
    I2C_Handle targetHandle, hostControllerHandle;
    I2C_Transaction txnTarget, txnhostController;
    SemaphoreP_Object sem;
    int32_t status;

    /* Binary semaphore for callback sync */
    SemaphoreP_constructBinary(&sem, 0);

    /* -------- Target setup -------- */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_targetCallback;

    targetHandle = I2C_getHandle(CONFIG_I2C1);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    targetHandle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(targetHandle);

    /* Prepare target transaction */
    I2C_Transaction_init(&txnTarget);
    txnTarget.controllerMode = false;
    txnTarget.readBuf = TestI2c_targetRxBuf;      /* Receive buffer */
    txnTarget.readCount = sizeof(TestI2c_targetRxBuf);
    txnTarget.writeBuf = TestI2c_targetTxBuf;     /* Data to send back on repeated start */
    txnTarget.writeCount = 2;             /* controller will read back 2 bytes */
    txnTarget.arg = &sem;

    TestI2c_targetTxBuf[0] = 0xDE;
    TestI2c_targetTxBuf[1] = 0xAD;

    status = I2C_transfer(targetHandle, &txnTarget);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* -------- controller (controller) setup -------- */
    I2C_Params_init(&params);
    hostControllerHandle = I2C_getHandle(CONFIG_I2C0);
    if(hostControllerHandle)
    {
        I2C_close(hostControllerHandle);
    }
    hostControllerHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(hostControllerHandle);

    /* Combined transaction: write + repeated start + read */
    TestI2c_controllerTxBuf[0] = 0xBB;
    I2C_Transaction_init(&txnhostController);
    txnhostController.writeBuf   = TestI2c_controllerTxBuf;   /* First write 1 byte */
    txnhostController.writeCount = 1;
    txnhostController.readBuf    = TestI2c_controllerRxBuf;   /* Then read 2 bytes */
    txnhostController.readCount  = 2;
    txnhostController.targetAddress = 0x10;

    status = I2C_transfer(hostControllerHandle, &txnhostController);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_pend(&sem, 1000);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Target received first byte = 0x%02X\r\n", TestI2c_targetRxBuf[0]);
    DebugP_log("controller received bytes: 0x%02X 0x%02X\r\n",
               TestI2c_controllerRxBuf[0], TestI2c_controllerRxBuf[1]);

    TEST_ASSERT_EQUAL_HEX8(TestI2c_controllerTxBuf[0], TestI2c_targetRxBuf[0]);   /* Target saw BB */
    TEST_ASSERT_EQUAL_UINT8_ARRAY(TestI2c_targetTxBuf, TestI2c_controllerRxBuf, 2); /* controller saw DE AD */
    I2C_close(hostControllerHandle);
    I2C_close(targetHandle);
    SemaphoreP_destruct(&sem);
}

/**
 * \brief Executes an I2C target mode test where the controller reads data from the target.
 *
 * Test Category: Functionality
 *
 * This function performs a test scenario in which the I2C peripheral operates in target mode,
 * and a controller device initiates a read operation to receive data from the target. The function
 * is intended to validate the correct behavior of the I2C driver in target mode during controller read transactions.
 *
 * \param args Pointer to arguments required for the test execution.
 */
static void TestI2c_targetModehostControllerRead(void *args)
{
    I2C_Params params;
    I2C_Handle targetHandle, hostControllerHandle;
    I2C_Transaction txnTarget, txnhostController;
    SemaphoreP_Object sem;
    int32_t status;

    SemaphoreP_constructBinary(&sem, 0);
    targetHandle = I2C_getHandle(CONFIG_I2C1);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    /* Target setup with TX buffer */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_targetCallback;
    targetHandle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(targetHandle);

    TestI2c_targetTxBuf[0] = 0xDE;
    TestI2c_targetTxBuf[1] = 0xAD;

    I2C_Transaction_init(&txnTarget);
    txnTarget.controllerMode = false;
    txnTarget.writeBuf   = TestI2c_targetTxBuf;   /* data to send to controller */
    txnTarget.writeCount = 2;
    txnTarget.readBuf    = NULL;
    txnTarget.readCount  = 0;
    txnTarget.arg        = &sem;

    status = I2C_transfer(targetHandle, &txnTarget);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* controller setup to read */
    I2C_Params_init(&params);
    hostControllerHandle = I2C_getHandle(CONFIG_I2C0);
    if(hostControllerHandle)
    {
        I2C_close(hostControllerHandle);
    }
    hostControllerHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(hostControllerHandle);

    I2C_Transaction_init(&txnhostController);
    txnhostController.writeBuf   = NULL;
    txnhostController.writeCount = 0;
    txnhostController.readBuf    = TestI2c_controllerRxBuf;
    txnhostController.readCount  = 2;
    txnhostController.targetAddress = 0x10;

    status = I2C_transfer(hostControllerHandle, &txnhostController);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Validate controller received */
    TEST_ASSERT_EQUAL_UINT8_ARRAY(TestI2c_targetTxBuf, TestI2c_controllerRxBuf, 2);
    I2C_close(hostControllerHandle);
    I2C_close(targetHandle);
    SemaphoreP_destruct(&sem);
}

/**
 * \brief Test I2C target XRDY overrun condition.
 *
 * Test Category: Negative Test Case
 *
 * This function tests the behavior when the controller requests more bytes than the target can provide.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_targetXrdyOverrun(void *args)
{
    I2C_Params params;
    I2C_Handle targetHandle, hostControllerHandle;
    I2C_Transaction txnTarget, txnhostController;
    SemaphoreP_Object sem;
    int32_t status;

    SemaphoreP_constructBinary(&sem, 0);

    /* Setup Target */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_targetCallback;
    targetHandle = I2C_getHandle(CONFIG_I2C1);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    targetHandle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(targetHandle);

    /* Prepare Target transaction: only 1 byte available */
    I2C_Transaction_init(&txnTarget);
    txnTarget.controllerMode = false;
    txnTarget.readBuf = NULL;
    txnTarget.readCount = 0;
    txnTarget.writeBuf = TestI2c_targetTxBuf;
    txnTarget.writeCount = 1;   /* only 1 byte available */
    txnTarget.arg = &sem;
    TestI2c_targetTxBuf[0] = 0xDE;

    status = I2C_transfer(targetHandle, &txnTarget);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Setup controller (controller) */
    I2C_Params_init(&params);

    hostControllerHandle = I2C_getHandle(CONFIG_I2C0);
    if(hostControllerHandle)
    {
        I2C_close(hostControllerHandle);
    }
    hostControllerHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(hostControllerHandle);

    /* controller requests MORE bytes than target has */
    I2C_Transaction_init(&txnhostController);
    txnhostController.writeBuf = NULL;
    txnhostController.writeCount = 0;
    txnhostController.readBuf = TestI2c_controllerRxBuf;
    txnhostController.readCount = 4;          /* request 2 bytes */
    txnhostController.targetAddress = 0x10;

    status = I2C_transfer(hostControllerHandle, &txnhostController);

    /* Wait for callback */
    status = SemaphoreP_pend(&sem, 100); /* 100 ms timeout */
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("XRDY overrun: No callback (expected for underrun)\n");
        /* Do not fail the test */
    }
    else
    {
        TEST_ASSERT_EQUAL_UINT8(0xDE, TestI2c_controllerRxBuf[0]);
	}

    I2C_close(hostControllerHandle);
    I2C_close(targetHandle);
    SemaphoreP_destruct(&sem);
}

/**
 * \brief Test I2C target RRDY underrun condition.
 *
 * Test Category: Negative Test Case
 *
 * This function tests the behavior when the controller writes more bytes than the target can receive.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_target_RrdyUnderrun(void *args)
{
    I2C_Params params;
    I2C_Handle targetHandle, hostControllerHandle;
    I2C_Transaction txnTarget, txnhostController;
    SemaphoreP_Object sem;
    int32_t status, i;

    SemaphoreP_constructBinary(&sem, 0);

    /* Setup Target  */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_targetCallback;
    targetHandle = I2C_getHandle(CONFIG_I2C1);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    targetHandle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(targetHandle);

    /* Prepare Target transaction: only 1 byte buffer for RX */
    I2C_Transaction_init(&txnTarget);
    txnTarget.controllerMode = false;
    txnTarget.readBuf = TestI2c_targetRxBuf;
    txnTarget.readCount = 1;   /* Only 1 byte can be received */
    txnTarget.writeBuf = NULL;
    txnTarget.writeCount = 0;
    txnTarget.arg = &sem;

    status = I2C_transfer(targetHandle, &txnTarget);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Setup controller (controller) */
    I2C_Params_init(&params);
    hostControllerHandle = I2C_getHandle(CONFIG_I2C0);
    if(hostControllerHandle)
    {
        I2C_close(hostControllerHandle);
    }
    hostControllerHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(hostControllerHandle);

    /* controller writes MORE bytes than target can receive */
    I2C_Transaction_init(&txnhostController);
    txnhostController.writeBuf = TestI2c_controllerTxBuf;
    txnhostController.writeCount = 4;  /* Send 4 bytes, but target only has space for 1 */
    txnhostController.readBuf = NULL;
    txnhostController.readCount = 0;
    txnhostController.targetAddress = 0x10;
    for (i = 0; i < 4; i++) TestI2c_controllerTxBuf[i] = 0xA0 + i;

    status = I2C_transfer(hostControllerHandle, &txnhostController);
    /* Wait for callback */
    status = SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Only the first byte should be received by the target */
    TEST_ASSERT_EQUAL_UINT8(TestI2c_controllerTxBuf[0], TestI2c_targetRxBuf[0]);

    I2C_close(hostControllerHandle);
    I2C_close(targetHandle);

    SemaphoreP_destruct(&sem);
}

/**
 * \brief Test I2C target with multiple controller reads in sequence.
 *
 * Test Category: Functionality
 *
 * This function validates that the target can handle multiple sequential controller read operations.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_targetMultiplehostControllerReads(void *args)
{
    I2C_Params params;
    I2C_Handle targetHandle, hostControllerHandle;
    I2C_Transaction txnTarget, txnhostController;
    SemaphoreP_Object sem;
    int32_t status, cycle,i;
    const int32_t num_cycles = 5;
    const int32_t bytesPerCycle = 4;

    SemaphoreP_constructBinary(&sem, 0);

    /* Target setup */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_targetCallback;
    targetHandle = I2C_getHandle(CONFIG_I2C1);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    targetHandle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(targetHandle);

    /* controller setup */
    I2C_Params_init(&params);
    hostControllerHandle = I2C_getHandle(CONFIG_I2C0);
    if(hostControllerHandle)
    {
        I2C_close(hostControllerHandle);
    }
    hostControllerHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(hostControllerHandle);

    for (cycle = 0; cycle < num_cycles; cycle++)
    {
        /* Prepare target data for this cycle */
        for (i = 0; i < bytesPerCycle; i++)
        {
            TestI2c_targetTxBuf[i] = 0x30 + cycle * 10 + i;
        }
        I2C_Transaction_init(&txnTarget);
        txnTarget.controllerMode = false;
        txnTarget.readBuf = NULL;
        txnTarget.readCount = 0;
        txnTarget.writeBuf = TestI2c_targetTxBuf;
        txnTarget.writeCount = bytesPerCycle;
        txnTarget.arg = &sem;

        status = I2C_transfer(targetHandle, &txnTarget);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* controller reads bytesPerCycle bytes */
        I2C_Transaction_init(&txnhostController);
        txnhostController.writeBuf = NULL;
        txnhostController.writeCount = 0;
        txnhostController.readBuf = TestI2c_controllerRxBuf;
        txnhostController.readCount = bytesPerCycle;
        txnhostController.targetAddress = 0x10;

        status = I2C_transfer(hostControllerHandle, &txnhostController);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Wait for target callback */
        status = SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Validate controller received correct data */
        TEST_ASSERT_EQUAL_UINT8_ARRAY(TestI2c_targetTxBuf, TestI2c_controllerRxBuf, bytesPerCycle);

        DebugP_log("Cycle %d: controller received:", cycle);
        for (i = 0; i < bytesPerCycle; i++)
            DebugP_log(" 0x%02X", TestI2c_controllerRxBuf[i]);
                DebugP_log("\n");
    }
    I2C_close(hostControllerHandle);
    I2C_close(targetHandle);
    SemaphoreP_destruct(&sem);
}

/**
 * \brief Target mode with 10-bit addressing.
 *
 * Test Category: Functionality
 *
 * This test validates target mode operation with 10-bit addressing.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_targetModehostControllerRead10bit(void *args)
{
    I2C_Params params;
    I2C_Handle targetHandle, hostControllerHandle;
    I2C_Transaction txnTarget, txnhostController;
    SemaphoreP_Object sem;
    int32_t status;
    uint8_t TestI2c_targetTxBuf[2] = {0xDE, 0xAD};
    uint8_t TestI2c_controllerRxBuf[2] = {0};

    SemaphoreP_constructBinary(&sem, 0);
    targetHandle = I2C_getHandle(CONFIG_I2C1);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    /* Target setup (10-bit address) */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_targetCallback;
    targetHandle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(targetHandle);

    I2C_Transaction_init(&txnTarget);
    txnTarget.controllerMode = false;
    txnTarget.writeBuf = TestI2c_targetTxBuf;
    txnTarget.writeCount = 2;
    txnTarget.readBuf = NULL;
    txnTarget.readCount = 0;
    txnTarget.expandSA = true; /* 10-bit addressing */
    txnTarget.arg = &sem;

    status = I2C_transfer(targetHandle, &txnTarget);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* controller setup (10-bit address) */
    hostControllerHandle = I2C_getHandle(CONFIG_I2C0);
    if(hostControllerHandle)
    {
        I2C_close(hostControllerHandle);
    }
    I2C_Params_init(&params);
    hostControllerHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(hostControllerHandle);

    I2C_Transaction_init(&txnhostController);
    txnhostController.writeBuf = NULL;
    txnhostController.writeCount = 0;
    txnhostController.readBuf = TestI2c_controllerRxBuf;
    txnhostController.readCount = 2;
    txnhostController.targetAddress = 0x10;
    txnhostController.expandSA = true; /* 10-bit addressing */

    status = I2C_transfer(hostControllerHandle, &txnhostController);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(TestI2c_targetTxBuf, TestI2c_controllerRxBuf, 2);

    I2C_close(hostControllerHandle);
    I2C_close(targetHandle);

    SemaphoreP_destruct(&sem);
}

/**
 * \brief Target mode with High-Speed (HS) mode.
 *
 * Test Category: Functionality
 *
 * This test validates target mode operation in High-Speed (HS) mode.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_targetModehostControllerReadHs(void *args)
{
    I2C_Params params;
    I2C_Handle targetHandle, hostControllerHandle;
    I2C_Transaction txnTarget, txnhostController;
    SemaphoreP_Object sem;
    int32_t status;
    uint8_t TestI2c_targetTxBuf[4] = {0xB1, 0xB2, 0xB3, 0xB4};
    uint8_t TestI2c_controllerRxBuf[4] = {0};

    SemaphoreP_constructBinary(&sem, 0);
    hostControllerHandle = I2C_getHandle(CONFIG_I2C0);
    if(hostControllerHandle)
    {
        I2C_close(hostControllerHandle);
    }
    targetHandle = I2C_getHandle(CONFIG_I2C1);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    /* Target setup */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_targetCallback;
    params.bitRate = I2C_1P0MHZ;
    targetHandle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(targetHandle);

    I2C_Transaction_init(&txnTarget);
    txnTarget.controllerMode = false;
    txnTarget.writeBuf = TestI2c_targetTxBuf;
    txnTarget.writeCount = sizeof(TestI2c_targetTxBuf);
    txnTarget.readBuf = NULL;
    txnTarget.readCount = 0;
    txnTarget.arg = &sem;

    status = I2C_transfer(targetHandle, &txnTarget);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* controller setup (HS mode) */
    I2C_Params_init(&params);
    params.bitRate = I2C_1P0MHZ;
    hostControllerHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(hostControllerHandle);

    I2C_Transaction_init(&txnhostController);
    txnhostController.writeBuf = NULL;
    txnhostController.writeCount = 0;
    txnhostController.readBuf = TestI2c_controllerRxBuf;
    txnhostController.readCount = sizeof(TestI2c_controllerRxBuf);
    txnhostController.targetAddress = 0x10;

    status = I2C_transfer(hostControllerHandle, &txnhostController);
    I2C_close(hostControllerHandle);
    I2C_close(targetHandle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SemaphoreP_pend(&sem, 1000);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(TestI2c_targetTxBuf, TestI2c_controllerRxBuf, sizeof(TestI2c_targetTxBuf));


    SemaphoreP_destruct(&sem);
}


/**
 * \brief Test I2C mem_primeTransfer in target mode via transfer API.
 *
 * Test Category: Negative Test Case
 *
 * This function tests that mem_primeTransfer returns failure when called in target mode.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_MemPrimeTransferTargetModeViaTransfer(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction testI2cTransaction;
    int32_t status;

    /* Open I2C normally */
    I2C_Params_init(&params);
    handle = I2C_getHandle(CONFIG_I2C1);
    if(handle)
    {
        I2C_close(handle);
    }
    gI2cHandle[CONFIG_I2C1] = NULL;
    handle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(handle);

    /* Prepare a transaction in target mode (controllerMode = false) with memTxnEnable = true */
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.controllerMode = false;
    testI2cTransaction.memTxnEnable = true;
    testI2cTransaction.memTransaction = NULL;

    /* Call I2C_transfer, which will call I2C_mem_primeTransfer internally */
    status = I2C_transfer(handle, &testI2cTransaction);
    /* Should return SystemP_FAILURE for target mode + memTxnEnable */
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    I2C_close(handle);
}

/**
 * \brief  Runtime reconfiguration of target own address for 10-bit and 7-bit addressing.
 *
 *  Test Category: Functionality
 *
 *  This test configures the I2C target peripheral at runtime for 10-bit and 7-bit own addresses,
 *  then validates that the controller can successfully write to the target in both modes.
 *  The test closes and reopens the target instance, sets the own address, and performs a write
 *  from the controller. Data integrity is checked after each transfer.
 *
 *  \param args Pointer to test parameters (not used).
 *
 * \return None.
 */
void TestI2c_targetMode10bit7bit(void *args)
{
    uint32_t i2c_addrList[2] = { 0x2AA, 0x10U }; /* 10-bit, 7-bit */
    bool tenBitMode[2] = { true, false };
    I2C_Params i2cParams;
    I2C_Handle handle = NULL;
    I2C_Handle testI2cContrllerHndl = NULL;
    I2C_Transaction testI2ctxnTarget;
    I2C_Transaction testI2ctxnCntrlr;
    SemaphoreP_Object i2cSem;
    int32_t status;
    uint32_t i;
    uint32_t i2cPhase;
    const uint32_t i2cPayloadLen = 6U;

    for(i2cPhase = 0; i2cPhase < 2U; i2cPhase++)
    {
        uint32_t i2cOwnAddr = i2c_addrList[i2cPhase];
        bool I2cis10bit = tenBitMode[i2cPhase];

        /* Close any previously open target/controller handles */
        handle = I2C_getHandle(CONFIG_I2C1);
        if(handle)
        {
            I2C_close(handle);
        }

        testI2cContrllerHndl = I2C_getHandle(CONFIG_I2C0);
        if(testI2cContrllerHndl)
        {
            I2C_close(testI2cContrllerHndl);
        }

        /* Runtime reconfigure own target address */
        I2C_HwAttrs *TestI2c_hw = (I2C_HwAttrs*)gI2cConfig[CONFIG_I2C1].hwAttrs;
        TestI2c_hw->ownTargetAddr[0] = i2cOwnAddr;

        /* Construct semaphore for target completion */
        SemaphoreP_constructBinary(&i2cSem, 0);

        /* Open target in callback mode */
        I2C_Params_init(&i2cParams);
        i2cParams.transferMode = I2C_MODE_CALLBACK;
        i2cParams.transferCallbackFxn = &test_i2c_targetCallback;
        handle = I2C_open(CONFIG_I2C1, &i2cParams);
        TEST_ASSERT_NOT_NULL(handle);

        /* Post a target receive (controller write) */
        I2C_Transaction_init(&testI2ctxnTarget);
        testI2ctxnTarget.controllerMode = false;
        testI2ctxnTarget.readBuf = TestI2c_targetRxBuf;
        testI2ctxnTarget.readCount = i2cPayloadLen;
        testI2ctxnTarget.writeBuf = NULL;
        testI2ctxnTarget.writeCount = 0;
        testI2ctxnTarget.arg = &i2cSem;
        testI2ctxnTarget.expandSA = I2cis10bit;
        testI2ctxnTarget.targetAddress = i2cOwnAddr;
        status = I2C_transfer(handle, &testI2ctxnTarget);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Open controller */
        I2C_Params_init(&i2cParams);
        testI2cContrllerHndl = I2C_open(CONFIG_I2C0, &i2cParams);
        TEST_ASSERT_NOT_NULL(testI2cContrllerHndl);

        /* Prepare payload */
        for(i = 0; i < i2cPayloadLen; i++)
        {
            TestI2c_controllerTxBuf[i] = (uint8_t)(0x90U + i + (I2cis10bit ? 0x20U : 0U));
            TestI2c_targetRxBuf[i] = 0U;
        }

        /* Controller write */
        I2C_Transaction_init(&testI2ctxnCntrlr);
        testI2ctxnCntrlr.writeBuf      = TestI2c_controllerTxBuf;
        testI2ctxnCntrlr.writeCount    = i2cPayloadLen;
        testI2ctxnCntrlr.readBuf       = NULL;
        testI2ctxnCntrlr.readCount     = 0;
        testI2ctxnCntrlr.targetAddress = i2cOwnAddr;
        testI2ctxnCntrlr.expandSA      = I2cis10bit;  /* enable 10-bit address on controller side */
        status = I2C_transfer(testI2cContrllerHndl, &testI2ctxnCntrlr);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Wait for target completion */
        status = SemaphoreP_pend(&i2cSem, 1000);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        SemaphoreP_destruct(&i2cSem);

        /* Validate data */
        TEST_ASSERT_EQUAL_UINT8_ARRAY(TestI2c_controllerTxBuf, TestI2c_targetRxBuf, i2cPayloadLen);

        DebugP_log("Test_I2C_TargetMode_RuntimeOwnAddr: Phase %u %s-bit addr=0x%X passed\r\n",
            (unsigned)i2cPhase,
            I2cis10bit ? "10" : "7",
            (unsigned)i2cOwnAddr);
        I2C_close(testI2cContrllerHndl);
        I2C_close(handle);
    }
}

/**
 * \brief Test I2C target mode with multiple own addresses (multi-target channel feature).
 *
 * This test configures the I2C peripheral in target mode with multiple own addresses.
 * It validates that the target responds correctly to transactions addressed to each of its own addresses.
 */
void TestI2c_targetModeMultiOwnAddr(void* args)
{
    I2C_Params params;
    I2C_Handle targetHandle, controllerHandle;
    I2C_Transaction txnTarget, txnController;
    int32_t status, i, addrIdx;
    SemaphoreP_Object sem;
    uint8_t ownAddrs[4] = { 0x10, 0x20, 0x30, 0x40 };
    uint8_t controllerTx[8], targetRx[8];

    SemaphoreP_constructBinary(&sem, 0);

    I2C_HwAttrs *hwAttrs = (I2C_HwAttrs *)gI2cConfig[CONFIG_I2C1].hwAttrs;
    for (i = 0; i < 4; i++)
    {
        hwAttrs->ownTargetAddr[i] = ownAddrs[i];
    }

    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_targetCallback;

    targetHandle = I2C_getHandle(CONFIG_I2C1);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    targetHandle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(targetHandle);

    for (addrIdx = 0; addrIdx < 1; addrIdx++)
    {
        I2C_Transaction_init(&txnTarget);
        txnTarget.controllerMode = false;
        txnTarget.readBuf = targetRx;
        txnTarget.readCount = sizeof(targetRx);
        txnTarget.writeBuf = NULL;
        txnTarget.writeCount = 0;
        txnTarget.arg = &sem;

        status = I2C_transfer(targetHandle, &txnTarget);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        I2C_Params_init(&params);
        controllerHandle = I2C_getHandle(CONFIG_I2C0);
        if(controllerHandle)
        {
            I2C_close(controllerHandle);
        }
        controllerHandle = I2C_open(CONFIG_I2C0, &params);
        TEST_ASSERT_NOT_NULL(controllerHandle);

        for (i = 0; i < sizeof(controllerTx); i++)
        {
            controllerTx[i] = (uint8_t)(addrIdx * 0x10 + i);
        }

        I2C_Transaction_init(&txnController);
        txnController.writeBuf = controllerTx;
        txnController.writeCount = sizeof(controllerTx);
        txnController.readBuf = NULL;
        txnController.readCount = 0;
        txnController.targetAddress = ownAddrs[addrIdx];

        status = I2C_transfer(controllerHandle, &txnController);
        I2C_close(controllerHandle);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        status = SemaphoreP_pend(&sem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        TEST_ASSERT_EQUAL_UINT8_ARRAY(controllerTx, targetRx, sizeof(controllerTx));
        DebugP_log("Target (ownAddr=0x%02X) received first byte = 0x%02X\r\n", ownAddrs[addrIdx], targetRx[0]);
    }

    SemaphoreP_destruct(&sem);
}
#endif

/**
 * \brief Test I2C target mode in polling (negative test).
 *
 * Test Category: Negative Test Case
 *
 * This function tests that target mode is not supported in polling mode and expects failure.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_targetModePollingNegative(void *args)
{
    I2C_Params params;
    I2C_Handle targetHandle;
    I2C_Transaction testI2cTransaction;
    I2C_HwAttrs         *hwAttrs = NULL;
    int32_t status;

    /* Open target in polling mode */
    I2C_Params_init(&params);
    targetHandle = I2C_getHandle(CONFIG_I2C0);
    if(targetHandle)
    {
        I2C_close(targetHandle);
    }
    gI2cHandle[CONFIG_I2C0] = NULL;

    hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
    hwAttrs->enableIntr = FALSE;

    params.transferMode = I2C_MODE_BLOCKING; /* Polling mode */
    targetHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(targetHandle);

    /* Prepare a target-mode transaction (controllerMode = false) */
    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.controllerMode = false;
    testI2cTransaction.writeBuf = NULL;
    testI2cTransaction.writeCount = 1;
    testI2cTransaction.readBuf = NULL;
    testI2cTransaction.readCount = 1;
    testI2cTransaction.timeout = 1000;

    /* Try to start a target-mode transfer in polling mode */
     status = I2C_transfer(targetHandle, &testI2cTransaction);
    /* Expect failure: polling mode not supported for target mode */
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    I2C_close(targetHandle);
}

/**
 * \brief Test I2C open without driver lock.
 *
 * Test Category: Negative Test Case
 *
 * This function tests opening the I2C driver when the internal lock is NULL.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_openWithoutDriverLock(void *args)
{
    (void)args;
    I2C_Handle handle;

    /* If already open (from Drivers_open), close first */
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle != NULL)
    {
        I2C_close(handle);
    }

    /* De-initialize driver: sets gI2cDrvObj.lock = NULL internally */
    I2C_deinit();

    I2C_Params params;
    I2C_Params_init(&params); /* Safe even when lock is NULL */

    /* Attempt open without lock -> expect NULL */
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NULL(handle);

    /* Restore driver for subsequent tests */
    I2C_init();

    /* Now open should succeed */
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    if(handle != NULL)
    {
        I2C_close(handle);
    }
}

/**
 * \brief Test I2C open with null object pointer.
 *
 * Test Category: Negative Test Case
 *
 * This function tests opening the I2C driver when the object pointer is NULL.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_openNullObject(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Object *savedObject = NULL;
    uint32_t idx = CONFIG_I2C0;

    /* Save original pointers */
    savedObject = gI2cConfig[idx].object;

    /* Case 1: object is NULL */
    gI2cConfig[idx].object = NULL;
    I2C_Params_init(&params);
    handle = I2C_open(idx, &params);
    TEST_ASSERT_NULL(handle);

    /* Restore */
    gI2cConfig[idx].object = savedObject;
    handle = I2C_open(idx, &params);
    TEST_ASSERT_NOT_NULL(handle);
    I2C_close(handle);
}

/**
 * \brief Negative test: Blocking-mode I2C transfer with SCL forced low
 *        to simulate bus stuck condition and validate timeout handling.
 *
 * This test simulates the SCL line being stuck low using the SYSTEST register
 * creating a bus-stuck condition. Since the clock line remains
 * low, the I2C transfer cannot progress and remains blocked until the
 * configured timeout expires and exits with I2C_STS_ERR_TIMEOUT.
 *
 * Test intent:
 *  - Open I2C instance in blocking mode.
 *  - Drive SCL low to simulate a stuck bus.
 *  - Initiate a write transaction.
 *  - Verify that the transaction status is I2C_STS_ERR_TIMEOUT.
 *
 * \param args Unused.
 */
static void TestI2c_transferTimeoutBlockingMode(void *args)
{

    I2C_Params i2cParams;
    I2C_Handle handle;
    uint32_t regVal,i;
    int32_t status;
    uint32_t   i2cDelay = I2C_DELAY_SMALL;
    I2C_Transaction Test_i2cTransaction;

    for (i = 0; i < 10; i++)
    {
        gI2cTxBuffer[i + Board_i2cGetEepromAddrSize()] = (uint8_t)i;
    }

    /* Setup: open I2C instance */
    I2C_Transaction_init(&Test_i2cTransaction);
    Test_i2cTransaction.writeBuf = gI2cTxBuffer;
    Test_i2cTransaction.writeCount = 2;
    Test_i2cTransaction.readBuf = NULL;
    Test_i2cTransaction.readCount = 0;
    Test_i2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
    Test_i2cTransaction.timeout = 1;

    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    gI2cHandle[CONFIG_I2C0] = NULL;
    I2C_Params_init(&i2cParams);
    handle = I2C_open(CONFIG_I2C0, &i2cParams);
    TEST_ASSERT_NOT_NULL(handle);

    handle = I2C_getHandle(CONFIG_I2C0);
    TEST_ASSERT_NOT_NULL(handle);
    uint32_t baseAddr = handle->hwAttrs->baseAddr;

    handle->object->i2cLldHandle->bitRate = I2C_400KHZ;

    /* Enable test mode and simulate SCL stuck low */
    regVal = HW_RD_REG32(baseAddr + CSL_I2C_SYSTEST);
    regVal |= (1 << CSL_I2C_SYSTEST_ST_EN_SHIFT);       /* ST_EN = 1 */
    regVal |= (0x3 << CSL_I2C_SYSTEST_TMODE_SHIFT);     /* TMODE = 0b11 */
    regVal &= ~(1 << CSL_I2C_SYSTEST_SCL_O_SHIFT);       /* SCL_O = 0 (drive low) */
    HW_WR_REG32(baseAddr + CSL_I2C_SYSTEST, regVal);
    ClockP_usleep(10);         /* Let the line settle */

    /* Confirm SCL is stuck low */
    regVal = HW_RD_REG32(baseAddr + CSL_I2C_SYSTEST);
    bool sclStuck = ((regVal >> CSL_I2C_SYSTEST_SCL_I_SHIFT) & 0x1) == 0;  /* SCL_I == 0 */
    TEST_ASSERT_TRUE_MESSAGE(sclStuck, "SCL line is not stuck as expected");

    status = I2C_transfer(handle, &Test_i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /*  Recover bus */
    status = I2C_recoverBus(handle, i2cDelay);
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS, status, "I2C_recoverBus() failed");

    /* Close */
    I2C_close(handle);
}

/**
 * \brief Test I2C recoverBus with null object pointer.
 *
 * Test Category: Negative Test Case
 *
 * This function tests the recoverBus API when the object pointer is NULL.
 *
 * \param args Pointer to arguments for the test.
 */
static void TestI2c_recoverbusNullObject(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Object *savedObject = NULL;
    int32_t status;
   /* Open I2C in blocking mode, interrupts enabled (default) */
    I2C_Params_init(&params);
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    gI2cHandle[CONFIG_I2C0] = NULL;

    /* Open I2C normally */
    I2C_Params_init(&params);
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    /* Save and set object pointer to NULL */
    savedObject = handle->object;
    handle->object = NULL;

    /* Call I2C_recoverBus and expect SystemP_FAILURE */
    status = I2C_recoverBus(handle, I2C_DELAY_SMALL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Restore object pointer */
    handle->object = savedObject;
    I2C_close(handle);
}

/**
 * \brief Executes I2C driver test cases.
 *
 * Test Category: Coverage
 *
 * This function runs a series of tests to validate the functionality and reliability
 * of the I2C driver within the MCU Plus SDK. It should be called with the necessary
 * arguments to configure and execute the tests.
 *
 * \param args Pointer to the arguments structure containing test configuration parameters.
 */
static void TestI2c_memPrimeTransferInvalidDir(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction testI2cTransaction;
    I2C_Mem_Transaction memTxn;
    int32_t status;
    I2C_HwAttrs *hwAttrs;
    hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
    hwAttrs->enableIntr = FALSE;

    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_BLOCKING;
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    I2C_Memory_Transaction_init(&memTxn);
    memTxn.memAddr = 0x10;
    memTxn.memAddrSize = 1;
    memTxn.buffer = NULL;
    memTxn.size = 0;
    memTxn.memDataDir = 0xFF;

    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.controllerMode = true;
    testI2cTransaction.memTxnEnable = true;
    testI2cTransaction.memTransaction = &memTxn;
    testI2cTransaction.targetAddress = 0x50;
    testI2cTransaction.timeout = 1000;

    status = I2C_transfer(handle, &testI2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    I2C_close(handle);
    hwAttrs->enableIntr = TRUE;

    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    params.transferCallbackFxn = NULL;
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    I2C_Memory_Transaction_init(&memTxn);
    memTxn.memAddr = 0x10;
    memTxn.memAddrSize = 1;
    memTxn.buffer = NULL;
    memTxn.size = 0;
    memTxn.memDataDir = 0xFF;

    I2C_Transaction_init(&testI2cTransaction);
    testI2cTransaction.controllerMode = true;
    testI2cTransaction.memTxnEnable = true;
    testI2cTransaction.memTransaction = &memTxn;
    testI2cTransaction.targetAddress = 0x50;
    testI2cTransaction.timeout = 1000;

    status = I2C_transfer(handle, &testI2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    I2C_close(handle);
}

/**
 * \brief Callback function for I2C queue depth test.
 *
 * This function is invoked upon completion of an I2C transaction during queue depth testing.
 * It provides the I2C handle, the transaction message, and the transfer status.
 *
 * \param i2cHnd         Handle to the I2C instance.
 * \param msg            Pointer to the I2C transaction structure.
 * \param transferStatus Status of the completed transfer.
 */
 void test_i2c_queue_callback(I2C_Handle i2cHnd, I2C_Transaction * msg, int32_t transferStatus)
{
    if(msg != NULL)
    {
        uint32_t idx = (uint32_t)(int32_t)msg->arg;
        if(TestI2c_CbQueuePos < TEST_I2C_CB_QUEUE_TEST_DEPTH)
        {
            TestI2c_CbQueueOrder[TestI2c_CbQueuePos++] = (uint8_t)idx;
        }
    }
    SemaphoreP_post(&gTestI2cCallbackDoneSemObj);
}

/**
 * \brief Test case to verify the callback queue depth functionality of the I2C driver.
 *
 * This test checks whether the I2C driver's callback mechanism can handle multiple queued
 * transactions without losing callbacks or causing unexpected behavior. It is intended to
 * ensure that the driver's internal queue for callbacks operates correctly under stress.
 *
 * \param args  Pointer to optional test parameters (unused in this test).
 */
void TestI2c_callbackQueueDepth(void* args)
{
    I2C_Params params;
    I2C_Handle handle;
    uint8_t addrSize;
    uint8_t i;
    I2C_Transaction transactions[TEST_I2C_CB_QUEUE_TEST_DEPTH];
    uint8_t writeBuf[TEST_I2C_CB_QUEUE_TEST_DEPTH][2];
    uint8_t readBuf[TEST_I2C_CB_QUEUE_TEST_DEPTH];

    TestI2c_CbQueuePos = 0;
    for(i=0;i<TEST_I2C_CB_QUEUE_TEST_DEPTH;i++)
    {
        TestI2c_CbQueueOrder[i] = 0xFFU;
    }

    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    SemaphoreP_constructBinary(&gTestI2cCallbackDoneSemObj, 0);

    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_queue_callback;
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    addrSize = Board_i2cGetEepromAddrSize();
    TEST_ASSERT_TRUE((addrSize==1U) || (addrSize==2U));

    for(i=0;i<TEST_I2C_CB_QUEUE_TEST_DEPTH;i++)
    {
        I2C_Transaction_init(&transactions[i]);
        uint16_t baseAddr = (uint16_t)(Board_i2cGetEepromMemAddr() + i);
        if(addrSize==1U)
        {
            writeBuf[i][0] = (uint8_t)(baseAddr & 0xFFU);
        }
        else
        {
            writeBuf[i][0] = (uint8_t)(baseAddr >> 8);
            writeBuf[i][1] = (uint8_t)(baseAddr & 0xFFU);
        }
        transactions[i].writeBuf   = writeBuf[i];
        transactions[i].writeCount = addrSize;
        transactions[i].readBuf    = &readBuf[i];
        transactions[i].readCount  = 1U;
        transactions[i].targetAddress = Board_i2cGetEepromDeviceAddr();
        transactions[i].arg = (void*)(int32_t)i;
        int32_t status = I2C_transfer(handle, &transactions[i]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

     DebugP_log("Before semaphore\r\n");
    for(i = 0; i < TEST_I2C_CB_QUEUE_TEST_DEPTH; i++)
    {
        SemaphoreP_pend(&gTestI2cCallbackDoneSemObj, 1000);
        DebugP_log("semaphore complete\r\n");
    }

    TEST_ASSERT_EQUAL_UINT32(TEST_I2C_CB_QUEUE_TEST_DEPTH, TestI2c_CbQueuePos);
    for(i = 0; i < TEST_I2C_CB_QUEUE_TEST_DEPTH; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(i, TestI2c_CbQueueOrder[i]);
    }

    I2C_close(handle);
    SemaphoreP_destruct(&gTestI2cCallbackDoneSemObj);
}

/**
 * \brief Test I2C FIFO management in various TX/RX modes.
 *
 * This test case validates the I2C driver's FIFO handling for transmit (TX) and receive (RX) operations
 * under different configuration modes. It exercises the FIFO logic by performing data transfers
 * and checks for correct operation, data integrity, and error handling.
 *
 * Test Category: Functionality / FIFO Management
 *
 * \param args Pointer to test parameters or configuration structure (if required).
 *
 * \return None.
 */
void TestI2c_fifoMgmtTxRxModes(void *args)
{
    const uint8_t devAddr = Board_i2cGetEepromDeviceAddr();
    const uint16_t baseMem = Board_i2cGetEepromMemAddr();
    const uint8_t memAddrSize = Board_i2cGetEepromAddrSize();
    I2C_Handle handle;
    uint32_t mode, i;

    for(mode = 0; mode < 2; mode++)
    {
        /* Close existing if open */
        handle = I2C_getHandle(CONFIG_I2C0);
        if(handle)
        {
            I2C_close(handle);
        }

        if(mode == 1)
        {
            gI2cConfig[CONFIG_I2C0].hwAttrs->enableIntr = false;
        }
        else
        {
            gI2cConfig[CONFIG_I2C0].hwAttrs->enableIntr = true;
        }
        DebugP_log("[FIFO] Mode=%s\n", (mode==0)?"IRQ":"Polling");

        I2C_Params params; I2C_Params_init(&params);
        params.transferMode = I2C_MODE_BLOCKING;
        handle = I2C_open(CONFIG_I2C0, &params);
        TEST_ASSERT_NOT_NULL(handle);

        /* SMALL WRITE */
        int32_t txSmallLen = memAddrSize + TEST_I2C_SMALL_SZ;
        uint16_t memAddrSmall = baseMem;
        if(memAddrSize==2U)
        {
            gI2cTxBuffer[0] = (uint8_t)(memAddrSmall >> 8);
            gI2cTxBuffer[1] = (uint8_t)(memAddrSmall & 0xFF);
        }
        else
        {
            gI2cTxBuffer[0] = (uint8_t)memAddrSmall;
        }
        for(i=0;i<TEST_I2C_SMALL_SZ;i++)
        {
            gI2cTxBuffer[memAddrSize+i]=(uint8_t)(0x11U+i);
            gI2cRxBuffer[i]=0U;
        }

        I2C_Transaction wSmall; I2C_Transaction_init(&wSmall);
        wSmall.writeBuf = gI2cTxBuffer;
        wSmall.writeCount = txSmallLen;
        wSmall.readBuf = NULL;
        wSmall.readCount = 0;
        wSmall.targetAddress = devAddr;
        wSmall.timeout = SystemP_WAIT_FOREVER;
        int32_t status = I2C_transfer(handle, &wSmall);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        ClockP_usleep(5000);

        /* SMALL READ */
        I2C_Transaction rSmall; I2C_Transaction_init(&rSmall);
        if(memAddrSize==2U)
        {
            gI2cTxBuffer[0] = (uint8_t)(memAddrSmall >> 8);
            gI2cTxBuffer[1] = (uint8_t)(memAddrSmall & 0xFF);
        }
        else
        {
            gI2cTxBuffer[0] = (uint8_t)memAddrSmall;
        }
        rSmall.writeBuf = gI2cTxBuffer;
        rSmall.writeCount = memAddrSize;
        rSmall.readBuf = gI2cRxBuffer;
        rSmall.readCount = TEST_I2C_SMALL_SZ;
        rSmall.targetAddress = devAddr;
        rSmall.timeout = SystemP_WAIT_FOREVER;
        status = I2C_transfer(handle, &rSmall);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        for(i=0;i<TEST_I2C_SMALL_SZ;i++)
        {
            TEST_ASSERT_EQUAL_UINT8((uint8_t)(0x11U+i), gI2cRxBuffer[i]);
        }

        /* LARGE WRITE */
        int32_t txLargeLen = memAddrSize + TEST_I2C_LARGE_SZ;
        uint16_t memAddrLarge = (uint16_t)(baseMem + 0x40U);
        if(memAddrSize==2U)
        {
            gI2cTxBuffer[0] = (uint8_t)(memAddrLarge >> 8);
            gI2cTxBuffer[1] = (uint8_t)(memAddrLarge & 0xFF);
        }
        else
        {
            gI2cTxBuffer[0] = (uint8_t)memAddrLarge;
        }
        for(i=0;i<TEST_I2C_LARGE_SZ;i++)
        {
            gI2cTxBuffer[memAddrSize+i]=(uint8_t)(0xA5U+i);
            gI2cRxBuffer[i]=0U;
        }

        I2C_Transaction wLarge; I2C_Transaction_init(&wLarge);
        wLarge.writeBuf = gI2cTxBuffer;
        wLarge.writeCount = txLargeLen;
        wLarge.readBuf = NULL;
        wLarge.readCount = 0;
        wLarge.targetAddress = devAddr;
        wLarge.timeout = SystemP_WAIT_FOREVER;
        status = I2C_transfer(handle, &wLarge);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        ClockP_usleep(5000);

        /* LARGE READ */
        I2C_Transaction rLarge; I2C_Transaction_init(&rLarge);
        if(memAddrSize==2U)
        {
            gI2cTxBuffer[0] = (uint8_t)(memAddrLarge >> 8);
            gI2cTxBuffer[1] = (uint8_t)(memAddrLarge & 0xFF);
        }
        else
        {
            gI2cTxBuffer[0] = (uint8_t)memAddrLarge;
        }
        rLarge.writeBuf = gI2cTxBuffer;
        rLarge.writeCount = memAddrSize;
        rLarge.readBuf = gI2cRxBuffer;
        rLarge.readCount = TEST_I2C_LARGE_SZ;
        rLarge.targetAddress = devAddr;
        rLarge.timeout = SystemP_WAIT_FOREVER;
        status = I2C_transfer(handle, &rLarge);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        for(i=0;i<TEST_I2C_LARGE_SZ;i++)
        {
            TEST_ASSERT_EQUAL_UINT8((uint8_t)(0xA5U+i),gI2cRxBuffer[i]);
        }

        I2C_close(handle);
    }
}

/**
 * \brief Test I2C controller transmit underflow condition.
 *
 * This test case simulates a TX underflow by enabling the XUDF interrupt and
 * injecting the XUDF status bit. It verifies that the I2C driver detects and
 * reports the underflow error.
 */
static void TestI2c_controllerTxUnderflow(void* args)
{
    I2C_Params      i2cParams;
    uint8_t         txBuffer1[8];
    int32_t         status;
    I2C_Handle      i2cHandle;
    I2C_Transaction i2cTransaction;
    uint32_t        baseAddr = gI2cConfig[CONFIG_I2C0].hwAttrs->baseAddr;

    i2cHandle = I2C_getHandle(CONFIG_I2C0);
    if(i2cHandle)
    {
        I2C_close(i2cHandle);
    }
    SemaphoreP_constructBinary(&gTestI2cCallbackDoneSemObj, 0);
    gI2cConfig[CONFIG_I2C0].hwAttrs->enableIntr = true;

    I2C_Params_init(&i2cParams);
    i2cParams.transferMode = I2C_MODE_CALLBACK;
    i2cParams.transferCallbackFxn = &test_i2c_callback;
    i2cHandle = I2C_open(CONFIG_I2C0, &i2cParams);
    TEST_ASSERT_NOT_NULL(i2cHandle);

    memset(txBuffer1, 0x5A, sizeof(txBuffer1));

    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = txBuffer1;
    i2cTransaction.writeCount = sizeof(txBuffer1);
    i2cTransaction.targetAddress = Board_i2cGetEepromDeviceAddr();
    i2cTransaction.arg = &gTestI2cCallbackDoneSemObj;

    status = I2C_transfer(i2cHandle, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /*  Enable XUDF interrupt and force raw underflow */
    HW_WR_REG32(baseAddr + CSL_I2C_IRQENABLE_SET, CSL_I2C_IRQSTATUS_XUDF_MASK | CSL_I2C_IRQSTATUS_XRDY_MASK);
    HW_WR_REG32(baseAddr + CSL_I2C_IRQSTATUS_RAW, CSL_I2C_IRQSTATUS_RAW_XUDF_MASK);

    status = SemaphoreP_pend(&gTestI2cCallbackDoneSemObj, SystemP_WAIT_FOREVER);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    I2C_close(i2cHandle);
    SemaphoreP_destruct(&gTestI2cCallbackDoneSemObj);
}

/**
 * \brief Test I2C polling mode NACK condition for write transaction.
 *
 * Attempts to write to a non-existent device address in polling mode in write mode and expects a NACK error.
 */
static void TestI2c_pollingNackWrite(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction transaction;
    int32_t status;
    uint8_t txBuf[2] = {0xAA, 0x55};

    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_BLOCKING;

    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);
    I2C_HwAttrs *hwAttrs = (I2C_HwAttrs *)((I2C_Config *)handle)->hwAttrs;
    hwAttrs->enableIntr = FALSE;
    I2C_Transaction_init(&transaction);
    transaction.writeBuf = txBuf;
    transaction.writeCount = sizeof(txBuf);
    transaction.readBuf = NULL;
    transaction.readCount = 0;
    transaction.targetAddress = NON_EXISTENT_DEVICE_ADDRESS;

    status = I2C_transfer(handle, &transaction);
    status = transaction.status;
    TEST_ASSERT_EQUAL_INT32(I2C_STS_ERR_NO_ACK, status);

    I2C_close(handle);
}

/**
 * \brief Test I2C polling mode NACK condition for read transaction.
 *
 * Attempts to read from a non-existent device address in polling mode in reade mode and expects a NACK error.
 */
static void TestI2c_pollingNackRead(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction transaction;
    int32_t status;
    uint8_t rxBuf[2];

    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_BLOCKING;

    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);
    I2C_HwAttrs *hwAttrs = (I2C_HwAttrs *)((I2C_Config *)handle)->hwAttrs;
    hwAttrs->enableIntr = FALSE;
    I2C_Transaction_init(&transaction);
    transaction.writeBuf = NULL;
    transaction.writeCount = 0;
    transaction.readBuf = rxBuf;
    transaction.readCount = sizeof(rxBuf);
    transaction.targetAddress = NON_EXISTENT_DEVICE_ADDRESS;

    status = I2C_transfer(handle, &transaction);
    status = transaction.status;
    TEST_ASSERT_EQUAL_INT32(I2C_STS_ERR_NO_ACK, status);

    I2C_close(handle);
}

/**
 * \brief Test I2C controller RX FIFO overrun condition.
 *
 * This test simulates an RX FIFO overrun by disabling the RX ready interrupt,
 * allowing the FIFO to fill, and then re-enabling the interrupt. It verifies
 * that the I2C driver correctly handles the overrun condition.
 *
 * Test Category: Negative / Robustness / Error Handling
 *
 * \param args Unused.
 *
 * \return None.
 */
void TestI2c_controllerRxOverrun(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction txn;
    uint8_t rxBuf[256];
    uint32_t baseAddr = gI2cConfig[CONFIG_I2C0].hwAttrs->baseAddr;

    gI2cConfig[CONFIG_I2C0].hwAttrs->enableIntr = true;
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    SemaphoreP_constructBinary(&gTestI2cCallbackDoneSemObj, 0);

    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &test_i2c_callback;

    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    /* Start dummy RX transfer */
    I2C_Transaction_init(&txn);
    txn.readBuf = rxBuf;
    txn.readCount = sizeof(rxBuf);
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    txn.arg = &gTestI2cCallbackDoneSemObj;

    I2C_transfer(handle, &txn);

    /* Disable RX ready interrupt to simulate overrun */
    HW_WR_REG32(baseAddr + CSL_I2C_IRQENABLE_CLR, CSL_I2C_IRQSTATUS_RRDY_MASK);
    ClockP_usleep(5000);  /* Wait for FIFO to fill */

    /* Re-enable RX ready interrupt */
    HW_WR_REG32(baseAddr + CSL_I2C_IRQENABLE_SET, CSL_I2C_IRQSTATUS_RRDY_MASK);

    SemaphoreP_pend(&gTestI2cCallbackDoneSemObj, SystemP_WAIT_FOREVER);


    I2C_close(handle);
    SemaphoreP_destruct(&gTestI2cCallbackDoneSemObj);
}

/**
 * \brief I2C error callback for access error and other interrupt tests.
 *
 * This callback is invoked by the I2C driver when a transfer completes or an error occurs.
 * It records the transfer status in a global variable and posts the semaphore provided in the transaction,
 * allowing the test case to continue.
 *
 * Used by error injection tests such as access error interrupt validation.
 *
 * \param i2cHnd         Handle to the I2C instance.
 * \param msg            Pointer to the I2C transaction structure.
 * \param transferStatus Status of the completed transfer or error.
 */
static void Test_I2cErrorCallback(I2C_Handle i2cHnd, I2C_Transaction * msg, int32_t transferStatus)
{

    Test_I2cErrorStat = transferStatus;
    if(msg && msg->arg!=NULL)
    {
        SemaphoreP_post((SemaphoreP_Object*)msg->arg);
    }
}

/**
 * \brief Test I2C controller access error interrupt handling.
 *
 * This test simulates an I2C access error by enabling the ACCESS_ERROR interrupt
 * and injecting a raw access error condition. It verifies that the I2C driver
 * correctly detects and reports the access error via callback.
 *
 * Test Category: Negative / Robustness / Error Handling
 *
 * \param args Unused.
 *
 * \return None.
 */
void TestI2c_controllerAccessError(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction txn;
    uint8_t rxBuf[64];
    uint32_t baseAddr = gI2cConfig[CONFIG_I2C0].hwAttrs->baseAddr;

    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    SemaphoreP_constructBinary(&gTestI2cCallbackDoneSemObj, 0);
    gI2cConfig[CONFIG_I2C0].hwAttrs->enableIntr = true;

    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = &Test_I2cErrorCallback;
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    I2C_Transaction_init(&txn);
    txn.writeBuf = NULL;
    txn.writeCount = 0;
    txn.readBuf = rxBuf;
    txn.readCount = sizeof(rxBuf);
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    txn.arg = &gTestI2cCallbackDoneSemObj;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, I2C_transfer(handle, &txn));

    ClockP_usleep(5000);

    /* Enable ACCESS_ERROR interrupt and inject raw access error */
    HW_WR_REG32(baseAddr + CSL_I2C_IRQENABLE_SET, CSL_I2C_IRQSTATUS_AERR_MASK);
    HW_WR_REG32(baseAddr + CSL_I2C_IRQSTATUS_RAW, CSL_I2C_IRQSTATUS_RAW_AERR_MASK);

    SemaphoreP_pend(&gTestI2cCallbackDoneSemObj, SystemP_WAIT_FOREVER);
    DebugP_log("I2C Access Error %d \r\n", Test_I2cErrorStat);
    TEST_ASSERT_EQUAL_INT32(I2C_STS_ERR_ACCESS_ERROR, Test_I2cErrorStat);
    I2C_close(handle);
    SemaphoreP_destruct(&gTestI2cCallbackDoneSemObj);
}

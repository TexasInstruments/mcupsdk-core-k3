/*
 * Copyright (C) 2021 Texas Instruments Incorporated
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


extern I2C_Config gI2cConfig[];

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct I2C_ProbeSettings_s {

    uint8_t instance;
    uint8_t numActualAddresses;

} I2C_ProbeSettings;

typedef struct I2C_TestParams_s {

    I2C_Params  i2cParams;
    uint16_t memAddress;
    uint8_t deviceAddress;
    uint8_t numBytes;
    uint8_t numWritesReads;
    bool testSetFrequency;
    bool intrEnable;

} I2C_TestParams;

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
static void test_i2c_dynamic_coverage(void* args);
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

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

SemaphoreP_Object gTestI2cCallbackDoneSemObj;

uint8_t gI2cTxBuffer[APP_I2C_BUFSIZE];
uint8_t gI2cRxBuffer[APP_I2C_BUFSIZE];

/* ========================================================================== */
/*                            Global Functions                                */
/* ========================================================================== */

uint8_t Board_i2cGetEepromDeviceAddr();
uint16_t Board_i2cGetEepromMemAddr();
uint8_t Board_i2cGetEepromAddrSize();


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
    RUN_TEST(test_i2c_error_nack, 12793, (void*)&testParams);

    /* Hw Intr mode I2C_lld_mem_writeIntr*/
    test_i2c_set_test_params(&testParams, 0);
    RUN_TEST(test_i2c_write_read, 6248, (void*)&testParams);

    RUN_TEST(test_i2c_dynamic_coverage, 6605, NULL);

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

/*
 * Test to write bytes to the EEPROM and read it back
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

/*
 * Test to see if probe returns same addresses as known from schematic
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
    I2C_Object *object = NULL;
    int32_t status = SystemP_SUCCESS;

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    I2C_Params_init(&i2cParams);
    i2cHandle = I2C_open(CONFIG_I2C0, &i2cParams);
    if (i2cHandle != NULL)
    {
        return SystemP_FAILURE;
    }

    i2cHandle = gI2cHandle[CONFIG_I2C0];
    object = (I2C_Object*)i2cHandle->object;
    object->i2cLldHandle->currentMsg = NULL;

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

    I2C_getHandle(CONFIG_I2C_NUM_INSTANCES+1);

    gI2cConfig[0].object->isOpen = false;
    I2C_getHandle(0);
    gI2cConfig[0].object->isOpen = true;

    /* Saving the I2C config object */
    object = gI2cConfig[0].object;
    gI2cConfig[0].object = NULL;
    I2C_getHandle(0);
    /* Storing back the object contents back to the I2C global config object */
    gI2cConfig[0].object = object;

    I2C_close(gI2cHandle[CONFIG_I2C0]);

    I2C_Params_init(&i2cParams);
    i2cHandle = I2C_open(CONFIG_I2C0, &i2cParams);

    if (i2cHandle == NULL)
    {
        return SystemP_FAILURE;
    }

    i2cHandle->object->i2cLldHandle = NULL;

    i2cTransaction.memTxnEnable = true;
    status=I2C_transfer(i2cHandle, &i2cTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    I2C_close(CONFIG_I2C0);
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
        memTransaction.memAddrSize = 8; //Incorrect mem address size
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

static void test_i2c_dynamic_coverage(void* args)
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

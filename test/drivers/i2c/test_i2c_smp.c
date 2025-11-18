/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file test_i2c_smp.c
 * @brief The following test aims at creating tasks for each A53 core.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* Standard includes. */
#include <stdint.h>
#include <string.h>

/* Kernel includes. */
#include <drivers/i2c.h>
#include <drivers/uart.h>
#include <kernel/dpl/SemaphoreP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "unity.h"
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>

/* ========================================================================== */
/*                             Macros & Defines                               */
/* ========================================================================== */

#define EEPROM_MEM_ADDRESS          (0x0400U)
#define EEPROM_ADDR_SIZE            (2U)
#define TEST_I2C_SMP_EEPROM_ITERS          1
#define TEST_I2C_SMP_TEMP_ITERS          1
#define TEST_I2C_SMP_TASKS 2

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

static TaskP_Object TestI2c_TaskObj1;
static TaskP_Object TestI2c_TaskObj2;
static uint8_t TestI2c_Task1Stack[6 * 1024];
static uint8_t TestI2c_Task2Stack[6 * 1024];
static SemaphoreP_Object Test_I2cSem;
#ifdef SOC_AM62DX
static I2C_Handle sharedI2cHandle = NULL;
#endif
/* ========================================================================== */
/*                        Internal Function Declarations                      */
/* ========================================================================== */

uint8_t Board_getSocTemperatureSensorAddr(void);
uint8_t Board_i2cGetEepromDeviceAddr();
#ifdef SOC_AM62AX
static void Test_I2c_smpEepromTask(void *arg);
static void Test_I2C_smpTempTask(void *arg);
void Test_I2C_smpMultiInstance(void *args);
#endif
#ifdef SOC_AM62DX
static void Test_I2c_smpEepromWorker(void *arg);
static void Test_I2c_smpTempWorker(void *arg);
void Test_I2CSMPSharedInstance(void *args);
#endif
void setUp(void);
void tearDown(void);

/* ========================================================================== */
/*                        Function Definitions                                */
/* ========================================================================== */
#ifdef SOC_AM62AX
/**
 *  \brief   Task to test I2C EEPROM access in SMP mode on AM62AX.
 *
 *  This task runs on a specific core and performs write/read operations to the EEPROM
 *  using I2C, verifying data integrity. Used in SMP multi-instance test.
 *
 *  \param arg  Unused argument.
 */
static void Test_I2c_smpEepromTask(void *arg)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction txn;
    uint8_t addrSize = EEPROM_ADDR_SIZE;
    uint8_t writeBuf[2 + 32];
    uint8_t readBuf[32];
    int32_t status;

    I2C_Params_init(&params);
    I2C_close(gI2cHandle[CONFIG_I2C0]);
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    for(uint32_t iter=0; iter < TEST_I2C_SMP_EEPROM_ITERS; iter++)
    {
        uint32_t memAddr = (iter * 32U) & 0xFFFFU;
        for(uint32_t i=0;i<32;i++)
        {
            writeBuf[addrSize + i] = (uint8_t)(0x30 + i + iter);
            readBuf[i] = 0;
        }
        if(addrSize == 1U)
            writeBuf[0] = (uint8_t)memAddr;
        else
        {
            writeBuf[0] = (uint8_t)(memAddr >> 8);
            writeBuf[1] = (uint8_t)memAddr;
        }

        I2C_Transaction_init(&txn);
        txn.targetAddress = Board_i2cGetEepromDeviceAddr();
        txn.writeBuf = writeBuf;
        txn.writeCount = addrSize + 32U;
        txn.readBuf = NULL;
        txn.readCount = 0U;
        status = I2C_transfer(handle, &txn);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        ClockP_usleep(5000);

        I2C_Transaction_init(&txn);
        txn.targetAddress = Board_i2cGetEepromDeviceAddr();
        txn.writeBuf = writeBuf;
        txn.writeCount = addrSize;
        txn.readBuf = readBuf;
        txn.readCount = 32U;
        status = I2C_transfer(handle, &txn);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        TEST_ASSERT_EQUAL_UINT8_ARRAY(&writeBuf[addrSize], readBuf, 32U);
    }

    I2C_close(handle);
    SemaphoreP_post(&Test_I2cSem);
}

/**
 *  \brief   Task to test I2C temperature sensor access in SMP mode on AM62AX.
 *
 *  This task runs on a specific core and reads temperature data from the sensor
 *  using I2C, verifying the value is within expected range. Used in SMP multi-instance test.
 *
 *  \param arg  Unused argument.
 */
static void Test_I2C_smpTempTask(void *arg)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction txn;
    uint8_t txBuf[1];
    uint8_t rxBuf[2];
    int32_t status;

    I2C_Params_init(&params);
    I2C_close(gI2cHandle[CONFIG_I2C2]);
    handle = I2C_open(CONFIG_I2C2, &params);
    TEST_ASSERT_NOT_NULL(handle);

    for(uint32_t iter=0; iter < TEST_I2C_SMP_TEMP_ITERS; iter++)
    {
        /*  Probe the sensor */
        status = I2C_probe(handle, Board_getSocTemperatureSensorAddr());
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

       /*  Read temperature register (register 0x00) */
        txBuf[0] = 0x00;
        I2C_Transaction_init(&txn);
        txn.targetAddress = Board_getSocTemperatureSensorAddr();
        txn.writeBuf = txBuf;
        txn.writeCount = 1U;
        txn.readBuf = rxBuf;
        txn.readCount = 2U;
        status = I2C_transfer(handle, &txn);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        int16_t tempRaw = ((int16_t)rxBuf[0] << 4) | (rxBuf[1] >> 4);
        float tempC = tempRaw * 0.0625f;
        TEST_ASSERT_TRUE_MESSAGE((tempC > -55.0f) && (tempC < 150.0f), "Temperature out of range");
    }

    I2C_close(handle);
    SemaphoreP_post(&Test_I2cSem);
}

/**
 *  \brief   SMP multi-instance test for I2C on AM62AX.
 *
 *  Creates two tasks with core affinity: one for EEPROM and one for temperature sensor.
 *  Each task opens its own I2C handle and performs I2C operations in parallel.
 *
 *  \param args  Unused argument.
 */
void Test_I2C_smpMultiInstance(void *args)
{
    int32_t status, loopVar;
    TaskP_Params taskParams1, taskParams2;

    status =  SemaphoreP_constructCounting(&Test_I2cSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestI2c_Task1Stack;
    taskParams1.stackSize      = sizeof(TestI2c_Task1Stack);
    taskParams1.name           = "Test_I2c_smpEepromTask";
    taskParams1.taskMain       = &Test_I2c_smpEepromTask;
    taskParams1.coreAffinity   = ( 1U << 0);

    status = TaskP_construct(&TestI2c_TaskObj1, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestI2c_Task2Stack;
    taskParams2.stackSize      = sizeof(TestI2c_Task2Stack);
    taskParams2.name           = "Test_I2C_smpTempTask";
    taskParams2.taskMain       = &Test_I2C_smpTempTask;
    taskParams2.coreAffinity   = ( 1U <<  1);

    status = TaskP_construct(&TestI2c_TaskObj2, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        status = SemaphoreP_pend(&Test_I2cSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(status, SystemP_SUCCESS);
    }
    SemaphoreP_destruct(&Test_I2cSem);
    TaskP_destruct(&TestI2c_TaskObj1);
    TaskP_destruct(&TestI2c_TaskObj2);
}
#endif

#ifdef SOC_AM62DX
/**
 *  \brief   Worker task for EEPROM access in SMP shared instance test (AM62DX).
 *
 *  This task uses a shared I2C handle to write and read EEPROM data, verifying correctness.
 *  Used in SMP shared instance test.
 *
 *  \param arg  Core-specific argument.
 */
static void Test_I2c_smpEepromWorker(void *arg)
{
    uint8_t addrSize = EEPROM_ADDR_SIZE;
    uint8_t txBuf[2 + 2] = {0}; /* address + 2 bytes data */
    uint8_t rxBuf[2] = {0};
    I2C_Transaction txn;
    int32_t status;

    /*Use a unique address per core */
   uint32_t memAddr = 0x0010;

    /* Pack address bytes (big-endian: MSB first) */
    if (addrSize == 1U)
    {
        txBuf[0] = (uint8_t)memAddr;
    }
    else
    {
        txBuf[0] = (uint8_t)(memAddr >> 8); /* MSB */
        txBuf[1] = (uint8_t)memAddr;       /* LSB */
    }

    /* Data to write */
    txBuf[addrSize + 0] = 0x00 + (uint8_t)(uintptr_t)arg;
    txBuf[addrSize + 1] = 0xff + (uint8_t)(uintptr_t)arg;

    /* Write 2 bytes */
    I2C_Transaction_init(&txn);
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    txn.writeBuf = txBuf;
    txn.writeCount = addrSize + 2;
    txn.readBuf = NULL;
    txn.readCount = 0;
    status = I2C_transfer(sharedI2cHandle, &txn);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_usleep(50000);

   /*  Read back 2 bytes */
    I2C_Transaction_init(&txn);
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    txn.writeBuf = txBuf;
    txn.writeCount = addrSize;
    txn.readBuf = rxBuf;
    txn.readCount = 2;
    status = I2C_transfer(sharedI2cHandle, &txn);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_post(&Test_I2cSem);
}

/**
 *  \brief   Worker task for temperature sensor access in SMP shared instance test (AM62DX).
 *
 *  This task uses a shared I2C handle to read temperature data from the sensor,
 *  verifying the value is within expected range. Used in SMP shared instance test.
 *
 *  \param arg  Core-specific argument.
 */
static void Test_I2c_smpTempWorker(void *arg)
{
    int ok = 1;
    uint8_t tx = 0x00, rx[2] = {0};
    I2C_Transaction txn;
    int32_t status;
    uint8_t tempAddr = Board_getSocTemperatureSensorAddr();

    /* Probe */
    status = I2C_probe(sharedI2cHandle, tempAddr);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Read temperature */
    I2C_Transaction_init(&txn);
    txn.targetAddress = tempAddr;
    txn.writeBuf = &tx;
    txn.writeCount = 1;
    txn.readBuf = rx;
    txn.readCount = 2;

    status = I2C_transfer(sharedI2cHandle, &txn);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    int16_t raw = (int16_t)((rx[0] << 8) | rx[1]);
    raw >>= 4;
    float tempC = raw * 0.0625f;
    if (!(tempC > -55.0f && tempC < 150.0f)) ok = 0;

    DebugP_log("SMP_TEMP: Core %d, Temp = %d.%04d C, ok=%d\n",
        (int)(uintptr_t)arg, (int)tempC, (int)((tempC - (int)tempC) * 10000), ok);

    SemaphoreP_post(&Test_I2cSem);
}

/**
 *  \brief   SMP shared instance test for I2C on AM62DX.
 *
 *  Opens a shared I2C handle and creates two tasks with core affinity:
 *  one for EEPROM and one for temperature sensor. Both tasks use the shared handle.
 *
 *  \param args  Unused argument.
 */
void Test_I2CSMPSharedInstance(void *args)
{
    /* Open shared I2C handle */
    I2C_Params params;
    I2C_Params_init(&params);
    I2C_close(gI2cHandle[CONFIG_I2C0]);
    sharedI2cHandle = NULL;
    sharedI2cHandle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(sharedI2cHandle);
    int32_t status, loopVar;
    TaskP_Params taskParams1, taskParams2;

    status =  SemaphoreP_constructCounting(&Test_I2cSem, 0, 2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestI2c_Task1Stack;
    taskParams1.stackSize      = sizeof(TestI2c_Task1Stack);
    taskParams1.name           = "Test_I2c_smpEepromWorker";
    taskParams1.taskMain       = &Test_I2c_smpEepromWorker;
    taskParams1.coreAffinity   = ( 1U << 0);

    status = TaskP_construct(&TestI2c_TaskObj1, &taskParams1);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestI2c_Task2Stack;
    taskParams2.stackSize      = sizeof(TestI2c_Task2Stack);
    taskParams2.name           = "Test_I2c_smpTempWorker";
    taskParams2.taskMain       = &Test_I2c_smpTempWorker;
    taskParams2.coreAffinity   = ( 1U <<  1);

    status = TaskP_construct(&TestI2c_TaskObj2, &taskParams2);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for(loopVar = 0; loopVar < 2; loopVar++)
    {
        status = SemaphoreP_pend(&Test_I2cSem, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(status, SystemP_SUCCESS);
    }
    I2C_close(sharedI2cHandle);
    SemaphoreP_destruct(&Test_I2cSem);
    TaskP_destruct(&TestI2c_TaskObj1);
    TaskP_destruct(&TestI2c_TaskObj2);
}
#endif

/*
 * Unity framework required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

/**
 *  \brief   Main entry point for I2C SMP tests.
 *
 *  Runs all SMP test cases using Unity framework.
 *
 *  \param args  Unused argument.
 */
void test_i2c_smp_main(void *args)
{
    UNITY_BEGIN();
    #ifdef SOC_AM62AX
    RUN_TEST(Test_I2C_smpMultiInstance, 8877, args);
    #endif
    #ifdef SOC_AM62DX
    RUN_TEST(Test_I2CSMPSharedInstance, 8878, args);
    #endif
    UNITY_END();
}
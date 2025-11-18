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

/**
 * \file test_i2c_fault_injection.c
 * Faults are injected using a stub before starting a transfer.
 */

 /* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <drivers/i2c.h>
#include <drivers/i2c/v0/lld/i2c_lld.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros                              */
/* ========================================================================== */

/** \brief Access Error interrupt */
#define I2C_INT_ACCESS_ERROR        ((uint32_t) I2C_IRQSTATUS_AERR_MASK)
/** \brief Arbitration Lost interrupt */
#define I2C_INT_ARBITRATION_LOST    ((uint32_t) I2C_IRQSTATUS_AL_MASK)

/* ========================================================================== */
/*                           Fault Type Enum                                  */
/* ========================================================================== */

typedef enum {
    TEST_I2C_FAULT_NONE = 0,
    TEST_I2C_INT_ACCESS_ERROR = 1,
    TEST_I2C_INT_ARBITRATION_LOST = 2,
} TestI2c_FaultType;

/* ========================================================================== */
/*                           Global Buffers                                   */
/* ========================================================================== */

static uint8_t gTxBuf[8];
static uint8_t gRxBuf[8];
extern I2C_Config gI2cConfig[];
static volatile TestI2c_FaultType TestI2c_CurrFault = TEST_I2C_FAULT_NONE;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void TestI2c_busFaultError(void *args);
static void TestI2c_arbitrationFaultError(void *args);
static void TestI2c_faultBusErrorPollingWrite(TestI2c_FaultType fault);
static void TestI2c_faultBusErrorPollingRead(TestI2c_FaultType fault);
static void TestI2c_faultArbitrationLostPollingWrite(TestI2c_FaultType fault);
static void TestI2c_faultArbitrationLostPollingRead(TestI2c_FaultType fault);
uint8_t Board_i2cGetEepromDeviceAddr();
uint16_t Board_i2cGetEepromMemAddr();
uint8_t Board_i2cGetEepromAddrSize();
uint8_t Board_getSocTemperatureSensorAddr(void);

/* ========================================================================== */
/*                           Unity Hooks                                      */
/* ========================================================================== */

void setUp(void) { }
void tearDown(void) { }

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * @brief Stub handler to inject I2C fault conditions during transfer.
 *
 * This function is called during I2C transfers to simulate specific fault conditions
 * (such as access error or arbitration lost) by setting the appropriate bits in the
 * transfer status variable. The type of fault to inject is controlled by the global
 * variable TestI2c_CurrFault.
 *
 * @param xsferStatus Pointer to the transfer status variable to modify.
 */
void TestI2c_faultInjectStubHandler(uint32_t *xsferStatus)
{
    if(TestI2c_CurrFault == TEST_I2C_FAULT_NONE)
        return;

    switch(TestI2c_CurrFault)
    {
        case TEST_I2C_INT_ACCESS_ERROR:
            DebugP_log("Injecting the Error I2C_INT_ACCESS_ERROR...\r\n");
            *xsferStatus |= I2C_INT_ACCESS_ERROR;
            break;
        case TEST_I2C_INT_ARBITRATION_LOST:
            DebugP_log("Injecting the Error I2C_INT_ARBITRATION_LOST...\r\n");
            *xsferStatus |= I2C_INT_ARBITRATION_LOST;
            break;
        default:
            break;
    }
}

/**
 * \brief Main entry point for Unity test execution.
 *
 * Registers and runs all I2C fault injection test cases.
 *
 * \param args Unused.
 */
void test_main(void *args)
{
    UNITY_BEGIN();
    RUN_TEST(TestI2c_busFaultError, 8337, NULL);
    RUN_TEST(TestI2c_arbitrationFaultError, 8316, NULL);
    UNITY_END();
}

/**
 * \brief Executes an I2C transfer with a specified fault injected.
 *
 * This function sets up an I2C transfer in polling mode, disables interrupts,
 * and injects the specified fault before performing the transfer.
 * It asserts that the expected error status is returned by the driver.
 *
 * \param fault  The fault type to inject (see TestI2c_FaultType).
 */
static void TestI2c_faultBusErrorPollingWrite(TestI2c_FaultType fault)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction txn;
    int32_t ret;
    I2C_HwAttrs *hwAttrs = NULL;

    I2C_Params_init(&params);
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    gI2cHandle[CONFIG_I2C0] = NULL;

    hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
    hwAttrs->enableIntr = FALSE;
    params.transferMode = I2C_MODE_BLOCKING;
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    memset(gTxBuf, 0xA5, sizeof(gTxBuf));
    memset(gRxBuf, 0x00, sizeof(gRxBuf));

    I2C_Transaction_init(&txn);
    txn.writeBuf      = gTxBuf;
    txn.writeCount    = 2;
    txn.readBuf       = gRxBuf;
    txn.readCount     = 0;
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    txn.timeout       = 1000;
    txn.arg           = NULL;

    TestI2c_CurrFault = fault;

    ret = I2C_transfer(handle, &txn);
    /* Some drivers place final result in txn.status */
    ret = txn.status;
    DebugP_log("Fault %d result status=%d\n", fault, ret);
    TEST_ASSERT_EQUAL(I2C_STS_ERR_ACCESS_ERROR, ret);

    I2C_close(handle);
}

static void TestI2c_faultBusErrorPollingRead(TestI2c_FaultType fault)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction txn;
    int32_t ret;
    I2C_HwAttrs *hwAttrs = NULL;

    I2C_Params_init(&params);
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    gI2cHandle[CONFIG_I2C0] = NULL;

    hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
    hwAttrs->enableIntr = FALSE;
    params.transferMode = I2C_MODE_BLOCKING;
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    memset(gTxBuf, 0xA5, sizeof(gTxBuf));
    memset(gRxBuf, 0x00, sizeof(gRxBuf));

    I2C_Transaction_init(&txn);
    txn.writeBuf      = gTxBuf;
    txn.writeCount    = 0; // No write, only read
    txn.readBuf       = gRxBuf;
    txn.readCount     = 2; // Read 2 bytes to trigger read path
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    txn.timeout       = 1000;
    txn.arg           = NULL;

    TestI2c_CurrFault = fault;

    ret = I2C_transfer(handle, &txn);
    /* Some drivers place final result in txn.status */
    ret = txn.status;
    DebugP_log("Fault %d (read) result status=%d\n", fault, ret);
    TEST_ASSERT_EQUAL(I2C_STS_ERR_ACCESS_ERROR, ret);

    I2C_close(handle);
}

/**
 * \brief Injects an arbitration lost fault during a polling-mode I2C write transfer.
 *
 * This function sets up an I2C transfer in polling mode with interrupts disabled,
 * injects the arbitration lost fault before performing the transfer, and asserts
 * that the expected error status is returned by the driver.
 *
 * \param fault  The fault type to inject (should be TEST_I2C_INT_ARBITRATION_LOST).
 */
static void TestI2c_faultArbitrationLostPollingWrite(TestI2c_FaultType fault)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction txn;
    int32_t ret;
    I2C_HwAttrs *hwAttrs = NULL;

    I2C_Params_init(&params);
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    gI2cHandle[CONFIG_I2C0] = NULL;

    hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
    hwAttrs->enableIntr = FALSE;
    params.transferMode = I2C_MODE_BLOCKING;
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    memset(gTxBuf, 0xA5, sizeof(gTxBuf));
    memset(gRxBuf, 0x00, sizeof(gRxBuf));

    I2C_Transaction_init(&txn);
    txn.writeBuf      = gTxBuf;
    txn.writeCount    = 2;
    txn.readBuf       = gRxBuf;
    txn.readCount     = 0;
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    txn.timeout       = 1000;
    txn.arg           = NULL;

    TestI2c_CurrFault = fault;

    ret = I2C_transfer(handle, &txn);
    ret = txn.status;
    DebugP_log("Arbitration Lost Fault (polling write) result status=%d\n", ret);
    TEST_ASSERT_EQUAL(I2C_STS_ERR_ARBITRATION_LOST, ret);

    I2C_close(handle);
}

/**
 * \brief Injects an arbitration lost fault during a polling-mode I2C read transfer.
 *
 * This function sets up an I2C transfer in polling mode with interrupts disabled,
 * injects the arbitration lost fault before performing the transfer, and asserts
 * that the expected error status is returned by the driver.
 *
 * \param fault  The fault type to inject (should be TEST_I2C_INT_ARBITRATION_LOST).
 */
static void TestI2c_faultArbitrationLostPollingRead(TestI2c_FaultType fault)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction txn;
    int32_t ret;
    I2C_HwAttrs *hwAttrs = NULL;

    I2C_Params_init(&params);
    handle = I2C_getHandle(CONFIG_I2C0);
    if(handle)
    {
        I2C_close(handle);
    }
    gI2cHandle[CONFIG_I2C0] = NULL;

    hwAttrs = (I2C_HwAttrs *) (gI2cConfig[CONFIG_I2C0]).hwAttrs;
    hwAttrs->enableIntr = FALSE;
    params.transferMode = I2C_MODE_BLOCKING;
    handle = I2C_open(CONFIG_I2C0, &params);
    TEST_ASSERT_NOT_NULL(handle);

    memset(gTxBuf, 0xA5, sizeof(gTxBuf));
    memset(gRxBuf, 0x00, sizeof(gRxBuf));

    I2C_Transaction_init(&txn);
    txn.writeBuf      = gTxBuf;
    txn.writeCount    = 0; // No write, only read
    txn.readBuf       = gRxBuf;
    txn.readCount     = 2; // Read 2 bytes
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    txn.timeout       = 1000;
    txn.arg           = NULL;

    TestI2c_CurrFault = fault;

    ret = I2C_transfer(handle, &txn);
    ret = txn.status;
    DebugP_log("Arbitration Lost Fault (polling read) result status=%d\n", ret);
    TEST_ASSERT_EQUAL(I2C_STS_ERR_ARBITRATION_LOST, ret);

    I2C_close(handle);
}

static void TestI2c_busFaultError(void *args)
{
    TestI2c_faultBusErrorPollingWrite(TEST_I2C_INT_ACCESS_ERROR);
    TestI2c_faultBusErrorPollingRead(TEST_I2C_INT_ACCESS_ERROR);
}

static void TestI2c_arbitrationFaultError(void *args)
{
    TestI2c_faultArbitrationLostPollingWrite(TEST_I2C_INT_ARBITRATION_LOST);
    TestI2c_faultArbitrationLostPollingRead(TEST_I2C_INT_ARBITRATION_LOST);
}
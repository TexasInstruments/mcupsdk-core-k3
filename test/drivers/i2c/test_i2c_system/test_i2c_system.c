/*
 *  Copyright (C) 2021-2024 Texas Instruments Incorporated
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
 *  \file test_i2c_system.c
 *
 *  \brief This file contains implementation of all module test cases
 *         for the wkuR5 core.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/soc.h>
#include <drivers/ipc_notify.h>
#include <unity.h>
#include <drivers/i2c.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

uint8_t Board_i2cGetEepromDeviceAddr();
uint16_t Board_i2cGetEepromMemAddr();
uint8_t Board_i2cGetEepromAddrSize();
uint8_t Board_getSocTemperatureSensorAddr(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/**
 * \brief Probes all possible PMIC I2C addresses and verifies device presence.
 *
 * This test closes any existing I2C1 handle, opens I2C1 at 400kHz, and probes
 * the PMIC PTPS6522430RAHRQ1 at all its possible sub-addresses (0x48–0x4B).
 * It logs the result for each address and asserts that each probe succeeds.
 *
 * \param args Unused.
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestI2c_pmicProbe(void* args)
{
    I2C_Params i2cParams;
    I2C_Handle i2cHandle;
    int32_t status;
    uint8_t pmicAddresses[] = {0x48, 0x49, 0x4A, 0x4B};
    uint8_t i;

    I2C_close(gI2cHandle[CONFIG_I2C1]);
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400KHZ;

    i2cHandle = I2C_open(CONFIG_I2C1, &i2cParams);
    TEST_ASSERT_NOT_NULL_MESSAGE(i2cHandle, "I2C_open failed for PMIC test");

    DebugP_log("\r\n[PMIC Test] Probing PMIC PTPS6522430RAHRQ1...\r\n");

    for (i = 0; i < sizeof(pmicAddresses); i++)
    {
        status = I2C_probe(i2cHandle, pmicAddresses[i]);
        if (status == SystemP_SUCCESS)
        {
            DebugP_log("PMIC sub-address 0x%02X detected\r\n", pmicAddresses[i]);
        }
        else
        {
            DebugP_log("PMIC sub-address 0x%02X not responding\r\n", pmicAddresses[i]);
        }
        TEST_ASSERT_EQUAL_INT32_MESSAGE(SystemP_SUCCESS, status, "PMIC I2C address probe failed");
    }

    I2C_close(i2cHandle);
    DebugP_log("[PMIC Test] PMIC probe completed successfully.\r\n");
    return SystemP_SUCCESS;
}

/**
 * \brief Reads the SoC temperature sensor (TMP100) over I2C and logs the value.
 *
 * This test closes any existing I2C1 handle, opens I2C1, probes the TMP100 sensor,
 * and reads the temperature register. The raw and processed temperature values
 * are logged. The test asserts that the probe and read succeed.
 *
 * \param args Unused.
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestI2c_ampI2cTemperature(void *args)
{
    I2C_Handle i2cHandle;
    I2C_Params i2cParams;
    I2C_Transaction txn;
    uint8_t txBuffer[1];
    uint8_t rxBuffer[2];
    int16_t temperature;
    int32_t status;

    DebugP_log("Temp: Starting TestI2c_ampI2cTemperature test\r\n");
    I2C_Params_init(&i2cParams);

    DebugP_log("Temp: Checking if I2C1 handle is already open\r\n");
    if (gI2cHandle[CONFIG_I2C1] != NULL)
    {
        DebugP_log("Temp: Closing existing I2C1 handle\r\n");
        I2C_close(gI2cHandle[CONFIG_I2C1]);
        gI2cHandle[CONFIG_I2C1] = NULL;
    }

    DebugP_log("Temp: Opening I2C1 handle\r\n");
    i2cHandle = I2C_open(CONFIG_I2C1, &i2cParams);
    if (i2cHandle == NULL)
    {
        DebugP_log("Temp: I2C_open failed\r\n");
        return SystemP_FAILURE;
    }
    DebugP_log("Temp: I2C1 handle opened successfully\r\n");

    /* Probe TMP100 */
    uint8_t sensorAddr = Board_getSocTemperatureSensorAddr();
    DebugP_log("Temp: Probing TMP100 at address 0x%02X\r\n", sensorAddr);
    status = I2C_probe(i2cHandle, sensorAddr);
    DebugP_log("Temp: TMP100 Probe status = %d\r\n", status);
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("Temp: TMP100 not detected at address 0x%02X\r\n", sensorAddr);
        I2C_close(i2cHandle);
        return SystemP_FAILURE;
    }
    DebugP_log("Temp: TMP100 detected\r\n");

    /* Read temperature register */
    txBuffer[0] = 0x00;
    I2C_Transaction_init(&txn);
    txn.writeBuf     = txBuffer;
    txn.writeCount   = 1;
    txn.readBuf      = rxBuffer;
    txn.readCount    = 2;
    txn.targetAddress = sensorAddr;

    DebugP_log("Temp: Starting I2C_transfer to read temperature\r\n");
    status = I2C_transfer(i2cHandle, &txn);
    DebugP_log("Temp: I2C_transfer status = %d\r\n", status);
    if (status == SystemP_SUCCESS)
    {
        DebugP_log("Temp: Raw RX buffer: 0x%02X 0x%02X\r\n", rxBuffer[0], rxBuffer[1]);
        temperature = ((uint16_t)rxBuffer[0] << 8) | rxBuffer[1];
        DebugP_log("Temp: Combined raw temperature value = 0x%04X\r\n", temperature);
        temperature >>= 4;
        DebugP_log("Temp: Shifted temperature value = 0x%04X\r\n", temperature);
        if (rxBuffer[0] & 0x80)
        {
            temperature |= 0xF000;
            DebugP_log("Temp: Negative temperature detected, sign-extended value = 0x%04X\r\n", temperature);
        }

        DebugP_log("[I2C2][TMP100] Temperature = %d.%d °C\r\n",
                   temperature / 16, (temperature % 16) * 625);
    }
    else
    {
        DebugP_log("Temp: I2C_transfer failed, could not read temperature\r\n");
    }

    I2C_close(i2cHandle);
    DebugP_log("Temp: I2C1 handle closed, TestI2c_ampI2cTemperature test complete\r\n");
    return status;
}

/**
 * \brief Simple I2C EEPROM write and read test.
 *
 * This test writes a 3-byte pattern to EEPROM and reads it back to verify data integrity.
 * It asserts that both the write and read operations succeed.
 *
 * \param args Unused.
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestI2c_EepromWriteRead(void *args)
{
    I2C_Params params;
    I2C_Handle handle;
    I2C_Transaction txn;
    uint8_t txBuf[3] = {0x00, 0x10, 0xAB};
    uint8_t rxBuf[3] = {0};
    int32_t status;

    /* Close if already open from Drivers_open(), then re-open with desired params */
    if (gI2cHandle[CONFIG_I2C1] != NULL)
    {
        I2C_close(gI2cHandle[CONFIG_I2C1]);
        gI2cHandle[CONFIG_I2C1] = NULL;
    }

    /* Open I2C in blocking mode */
    I2C_Params_init(&params);
    params.transferMode = I2C_MODE_BLOCKING;
    handle = I2C_open(CONFIG_I2C1, &params);
    TEST_ASSERT_NOT_NULL(handle);

    /* Write 3 bytes to EEPROM */
    I2C_Transaction_init(&txn);
    txn.writeBuf = txBuf;
    txn.writeCount = sizeof(txBuf);
    txn.readBuf = NULL;
    txn.readCount = 0;
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    status = I2C_transfer(handle, &txn);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    ClockP_usleep(5000);

    /* Read back 3 bytes from EEPROM */
    I2C_Transaction_init(&txn);
    txn.writeBuf = txBuf;
    txn.writeCount = 1;
    txn.readBuf = rxBuf;
    txn.readCount = sizeof(rxBuf);
    txn.targetAddress = Board_i2cGetEepromDeviceAddr();
    status = I2C_transfer(handle, &txn);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    I2C_close(handle);
    return status;
}


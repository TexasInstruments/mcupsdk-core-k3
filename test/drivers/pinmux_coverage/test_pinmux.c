/*
 * Copyright (C) 2021-2026 Texas Instruments Incorporated
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
#include <kernel/dpl/AddrTranslateP.h>
#include <drivers/pinmux.h>
#include <drivers/hw_include/cslr.h>
#include <drivers/hw_include/cslr_soc.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62X) || defined(SOC_AM62DX)
#define TEST_PINMUX_SOC_SPI_CS0         PIN_MCU_SPI0_CS0
#define TEST_PINMUX_SOC_OSPI0_CLK       PIN_OSPI0_CLK
#define TEST_PINMUX_SOC_OSPI0_D0        PIN_OSPI0_D0
#define TEST_PINMUX_SOC_OSPI0_CSN0      PIN_OSPI0_CSN0
#define TEST_PINMUX_SOC_GPIO_PIN        PIN_GPIO0_45
#define TEST_PINMUX_SOC_MAIN_LAST_PIN   PIN_USB1_DRVVBUS
#define TEST_PINMUX_MAIN_BASE           CSL_PADCFG_CTRL0_CFG0_BASE
#define TEST_PINMUX_MCU_BASE            CSL_WKUP_PADCFG_CTRL0_CFG0_BASE
#elif defined(SOC_AM275X) || defined(SOC_AM62DX)
#define TEST_PINMUX_SOC_SPI_CS0         PIN_SPI0_CS0
#define TEST_PINMUX_SOC_OSPI0_CLK       PIN_OSPI0_CLK
#define TEST_PINMUX_SOC_OSPI0_D0        PIN_OSPI0_D0
#define TEST_PINMUX_SOC_OSPI0_CSN0      PIN_OSPI0_CSN0
#define TEST_PINMUX_SOC_GPIO_PIN        PIN_GPIO1_47
#define TEST_PINMUX_SOC_MAIN_LAST_PIN   PIN_USB0_DRVVBUS
#define TEST_PINMUX_MAIN_BASE           CSL_PADCFG_CTRL0_CFG0_BASE
#define TEST_PINMUX_MCU_BASE            CSL_MCU_PADCFG_CTRL0_CFG0_BASE
#endif

/**
 * @brief Offset value for the PADCFG register in the pinmux module.
 */
#define TEST_PINMUX_PADCFG_OFFSET       (0x4000U)

/* Stress test iteration counts */
#define TEST_PINMUX_STRESS_CONFIG_COUNT     (1000U)
#define TEST_PINMUX_STRESS_LOCK_COUNT       (500U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Testcases */
static void test_pinmux_coverage(void *args);
#if defined(SOC_AM275X) || defined(SOC_AM62DX)
static void TestPinmux_configMultiplePins(void *args);
static void TestPinmux_configVerifyModeChange(void *args);
static void TestPinmux_configAllSettingsBits(void *args);
static void TestPinmux_configEmptyArray(void *args);
static void TestPinmux_configMaxPinMode(void *args);
static void TestPinmux_configSettingsAllBitsSet(void *args);
static void TestPinmux_configSettingsZero(void *args);
static void TestPinmux_configNullPointer(void *args);
static void TestPinmux_configInvalidDomainId(void *args);
static void TestPinmux_unlockMMRInvalidDomain(void *args);
static void TestPinmux_configRepeatedCalls(void *args);
static void TestPinmux_unlockLockRepeated(void *args);
#endif 

/**
 * @file test_pinmux.c
 * @brief Contains declarations for multi-threaded pinmux tests.
 *
 * When ENABLE_MT_TESTS is defined, declares the entry point for running
 * multi-threaded pinmux tests.
 *
 * - run_pinmux_multi_threaded_tests: Executes pinmux tests in a multi-threaded context.
 */
#ifdef ENABLE_MT_TESTS
extern void run_pinmux_multi_threaded_tests(void *args);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_pinmux_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(test_pinmux_coverage, 8070, NULL);

    #if defined(SOC_AM275X) || defined(SOC_AM62DX)
    /* Functional Tests */
    RUN_TEST(TestPinmux_configMultiplePins, 11232, NULL);
    RUN_TEST(TestPinmux_configVerifyModeChange, 11233, NULL);
    RUN_TEST(TestPinmux_configAllSettingsBits, 11234, NULL);

    /* Boundary Tests */
    RUN_TEST(TestPinmux_configEmptyArray, 11235, NULL);
    RUN_TEST(TestPinmux_configMaxPinMode, 11236, NULL);
    RUN_TEST(TestPinmux_configSettingsAllBitsSet, 11237, NULL);
    RUN_TEST(TestPinmux_configSettingsZero, 11238, NULL);

    /* Error Injection Tests */
    RUN_TEST(TestPinmux_configNullPointer, 11239, NULL);
    RUN_TEST(TestPinmux_configInvalidDomainId, 11240, NULL);
    RUN_TEST(TestPinmux_unlockMMRInvalidDomain, 11241, NULL);

    /* Stress Tests */
    RUN_TEST(TestPinmux_configRepeatedCalls, 11242, NULL);
    RUN_TEST(TestPinmux_unlockLockRepeated, 11243, NULL);

    /* Multi-Thread Tests (FreeRTOS only) */
    #ifdef ENABLE_MT_TESTS
    run_pinmux_multi_threaded_tests(NULL);
    #endif

    #endif
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

static void test_pinmux_coverage(void *args)
{
    /* Pinmux config array for MCU domain */
    Pinmux_PerCfg_t pinCfgMCU[] = {
    { TEST_PINMUX_SOC_SPI_CS0, PIN_MODE(0) | PIN_INPUT_ENABLE },
    { PINMUX_END, 0 }
    };

    /* Pinmux config array for MAIN domain */
    Pinmux_PerCfg_t pinCfgMain[] = {
    { TEST_PINMUX_SOC_OSPI0_CLK, PIN_MODE(0) | PIN_INPUT_ENABLE },
    { PINMUX_END, 0 }
    };

    DebugP_log("\r\n pinumux dynamic coverage test...\r\n");

    /* Configuring the pinmux for MAIN domain */
    Pinmux_config(pinCfgMain,PINMUX_DOMAIN_ID_MAIN);

    /* Passing invalid parameter for Configuring the pinmux for MAIN domain  */
    Pinmux_config(NULL, PINMUX_DOMAIN_ID_MAIN);

    /* Unlocks the PAD config control MMRs for the MAIN domain */
    Pinmux_unlockMMR(PINMUX_DOMAIN_ID_MAIN);

    /* Locks the PAD config control MMRs for the MAIN domain */
    Pinmux_lockMMR(PINMUX_DOMAIN_ID_MAIN);

    /* Configuring the pinmux for MCU domain */
    Pinmux_config(pinCfgMCU,PINMUX_DOMAIN_ID_MCU);

    /* Unlocks the PAD config control MMRs for the MCU domain */
    Pinmux_unlockMMR(PINMUX_DOMAIN_ID_MCU);

    /* Locks the PAD config control MMRs for the MCU domain */
    Pinmux_lockMMR(PINMUX_DOMAIN_ID_MCU);

    DebugP_log("\r\n pinumux dynamic coverage test: PASS \r\n");
}

#if defined(SOC_AM275X) || defined(SOC_AM62DX)
/*
 * Test case: TestPinmux_configMultiplePins
 * This test verifies that the Pinmux_config function can correctly configure
 * multiple pins in a single call for the MAIN domain. It sets up three pins
 * with different settings, applies the configuration, and then reads back
 * the register values to ensure each pin was set as expected. This ensures
 * that the driver correctly iterates through the configuration array and
 * applies settings to all specified pins.
 */
static void TestPinmux_configMultiplePins(void *args)
{
    uint32_t baseAddr, readValue;

    DebugP_log("\r\n TestPinmux_configMultiplePins started...\r\n");

    /* Config array with 3 MAIN domain pins */
    Pinmux_PerCfg_t pinCfgMain[] = {
        { TEST_PINMUX_SOC_OSPI0_CLK,  PIN_MODE(0) | PIN_INPUT_ENABLE },
        { TEST_PINMUX_SOC_OSPI0_D0,   PIN_MODE(0) | PIN_INPUT_ENABLE },
        { TEST_PINMUX_SOC_OSPI0_CSN0, PIN_MODE(0) | PIN_PULL_DISABLE },
        { PINMUX_END, 0 }
    };

    Pinmux_config(pinCfgMain, PINMUX_DOMAIN_ID_MAIN);

    /* Read back and verify each pin */
    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_OSPI0_CLK);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_OSPI0_D0);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_OSPI0_CSN0);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_PULL_DISABLE, readValue);

    DebugP_log("TestPinmux_configMultiplePins: PASS\r\n");
}

/*
 * Test case: TestPinmux_configVerifyModeChange
 * This test verifies that the Pinmux_config function can correctly change
 * the mode of a pin that has already been configured. It first sets the pin
 * to Mode 0, reads back and checks the value, then reconfigures the same pin
 * to Mode 7 and verifies the change. This ensures that mode changes are
 * applied correctly and previous settings are properly overwritten.
 */
static void TestPinmux_configVerifyModeChange(void *args)
{
    uint32_t baseAddr, readValue;

    DebugP_log("\r\n TestPinmux_configVerifyModeChange started...\r\n");

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);

    /* Configure pin to Mode 0 */
    Pinmux_PerCfg_t pinCfg1[] = {
        { TEST_PINMUX_SOC_GPIO_PIN, PIN_MODE(0) },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg1, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_GPIO_PIN);
    TEST_ASSERT_EQUAL_UINT32(0x0U, readValue & 0xFU);

    /* Reconfigure same pin to Mode 7 */
    Pinmux_PerCfg_t pinCfg2[] = {
        { TEST_PINMUX_SOC_GPIO_PIN, PIN_MODE(7) },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg2, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_GPIO_PIN);
    TEST_ASSERT_EQUAL_UINT32(0x7U, readValue & 0xFU);

    DebugP_log("TestPinmux_configVerifyModeChange: PASS\r\n");
}

/*
 * Test case: TestPinmux_configAllSettingsBits
 * This test verifies that the Pinmux_config function correctly applies all
 * configurable settings bits for a pin in the MAIN domain. It sets a pin
 * with a combination of mode, pull disable, pull direction, input enable,
 * and output disable, then reads back the register value to ensure each
 * field is set as expected. This ensures that all bit fields are handled
 * properly by the driver.
 */
static void TestPinmux_configAllSettingsBits(void *args)
{
    uint32_t baseAddr, readValue;
    uint32_t settings;

    DebugP_log("\r\n TestPinmux_configAllSettingsBits started...\r\n");

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);

    /* Test 1: All settings with fast drive strength */
    settings = PIN_MODE(5) | PIN_PULL_DISABLE | PIN_PULL_DIRECTION |
               PIN_INPUT_ENABLE | PIN_DRV_STR_FAST | PIN_OUTPUT_DISABLE;

    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_SOC_GPIO_PIN, settings },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_GPIO_PIN);

    /* Verify each bit field */
    TEST_ASSERT_EQUAL_UINT32(5U, readValue & 0xFU);                /* Mode 5 */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 16U) & 0x1U);       /* Pull disable */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 17U) & 0x1U);       /* Pull direction */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 18U) & 0x1U);       /* Input enable */
    TEST_ASSERT_EQUAL_UINT32(2U, (readValue >> 19U) & 0x3U);       /* Drive strength = FAST (2) */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 21U) & 0x1U);       /* Output disable */

    /* Test 2: Nominal drive strength */
    settings = PIN_MODE(7) | PIN_INPUT_ENABLE | PIN_DRV_STR_NOMINAL;

    Pinmux_PerCfg_t pinCfg2[] = {
        { TEST_PINMUX_SOC_GPIO_PIN, settings },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg2, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_GPIO_PIN);

    TEST_ASSERT_EQUAL_UINT32(7U, readValue & 0xFU);                /* Mode 7 */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 18U) & 0x1U);       /* Input enable */
    TEST_ASSERT_EQUAL_UINT32(0U, (readValue >> 19U) & 0x3U);       /* Drive strength = NOMINAL (0) */

    /* Test 3: Explicit drive strength value (1) */
    settings = PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_DRIVE_STRENGTH(1U);

    Pinmux_PerCfg_t pinCfg3[] = {
        { TEST_PINMUX_SOC_GPIO_PIN, settings },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg3, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_GPIO_PIN);

    TEST_ASSERT_EQUAL_UINT32(0U, readValue & 0xFU);                /* Mode 0 */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 19U) & 0x3U);       /* Drive strength = 1 */

    DebugP_log("TestPinmux_configAllSettingsBits: PASS\r\n");
}

/*
 * Test case: TestPinmux_configEmptyArray
 * This test verifies that the Pinmux_config function handles an empty configuration array
 * gracefully. It passes an array containing only the PINMUX_END marker to both MAIN and MCU
 * domains. The function should not crash or perform any register writes, effectively resulting
 * in a zero-iteration loop. The test reads MAIN and MCU domain register values before and after
 * the empty array calls and verifies they remain unchanged.
 */
static void TestPinmux_configEmptyArray(void *args)
{
    uint32_t mainBaseAddr, mcuBaseAddr;
    uint32_t mainBefore, mcuBefore;
    uint32_t mainAfter, mcuAfter;

    DebugP_log("\r\n TestPinmux_configEmptyArray started...\r\n");

    mainBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);
    mcuBaseAddr  = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MCU_BASE + TEST_PINMUX_PADCFG_OFFSET);

    /* Read register values before empty array calls */
    mainBefore = CSL_REG32_RD(mainBaseAddr + TEST_PINMUX_SOC_OSPI0_CLK);
    mcuBefore  = CSL_REG32_RD(mcuBaseAddr + TEST_PINMUX_SOC_SPI_CS0);

    Pinmux_PerCfg_t pinCfgEmpty[] = {
        { PINMUX_END, 0 }
    };

    /* Should not crash and should not modify any registers */
    Pinmux_config(pinCfgEmpty, PINMUX_DOMAIN_ID_MAIN);
    Pinmux_config(pinCfgEmpty, PINMUX_DOMAIN_ID_MCU);

    /* Read register values after empty array calls */
    mainAfter = CSL_REG32_RD(mainBaseAddr + TEST_PINMUX_SOC_OSPI0_CLK);
    mcuAfter  = CSL_REG32_RD(mcuBaseAddr + TEST_PINMUX_SOC_SPI_CS0);

    /* Both domains should remain unchanged */
    TEST_ASSERT_EQUAL_UINT32(mainBefore, mainAfter);
    TEST_ASSERT_EQUAL_UINT32(mcuBefore, mcuAfter);

}

/*
 * Test case: TestPinmux_configMaxPinMode
 * This test verifies that the Pinmux_config function can correctly set the maximum
 * supported pin mode value (Mode 15) for a pin in the MAIN domain. It configures
 * the pin with the highest mode, reads back the register value, and checks that
 * only the lower 4 bits (mode field) are set to 0xF. This ensures the driver
 * properly handles the upper boundary for pin mode configuration.
 */
static void TestPinmux_configMaxPinMode(void *args)
{
    uint32_t baseAddr, readValue;

    DebugP_log("\r\n TestPinmux_configMaxPinMode started...\r\n");

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);

    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_SOC_GPIO_PIN, PIN_MODE(15) },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_GPIO_PIN);
    TEST_ASSERT_EQUAL_UINT32(0xFU, readValue & 0xFU);

    DebugP_log("TestPinmux_configMaxPinMode: PASS\r\n");
}

/*
 * Test case: TestPinmux_configSettingsAllBitsSet
 * This test verifies that the Pinmux_config function correctly applies all possible
 * configuration bits for a pin in the MAIN domain. It sets the mode to the maximum value
 * (Mode 15) and enables all configurable features: pull disable, pull direction, input enable,
 * drive strength (fast), output disable, and wakeup enable. The test then reads back the
 * register value and checks that each relevant bit field is set as expected. This ensures
 * the driver can handle simultaneous configuration of all supported settings without error.
 */
static void TestPinmux_configSettingsAllBitsSet(void *args)
{
    uint32_t baseAddr, readValue;
    uint32_t settings;

    DebugP_log("\r\n TestPinmux_configSettingsAllBitsSet started...\r\n");

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);

    /* Set all bits including fast drive strength */
    settings = PIN_MODE(15) | PIN_PULL_DISABLE | PIN_PULL_DIRECTION |
               PIN_INPUT_ENABLE | PIN_DRV_STR_FAST | PIN_OUTPUT_DISABLE |
               PIN_WAKEUP_ENABLE;

    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_SOC_GPIO_PIN, settings },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_GPIO_PIN);

    /* Mode 15 */
    TEST_ASSERT_EQUAL_UINT32(0xFU, readValue & 0xFU);
    /* Pull disable */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 16U) & 0x1U);
    /* Pull direction */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 17U) & 0x1U);
    /* Input enable */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 18U) & 0x1U);
    /* Drive strength = FAST (2) - bits [20:19] */
    TEST_ASSERT_EQUAL_UINT32(2U, (readValue >> 19U) & 0x3U);
    /* Output disable */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 21U) & 0x1U);
    /* Wakeup enable */
    TEST_ASSERT_EQUAL_UINT32(1U, (readValue >> 29U) & 0x1U);

    DebugP_log("TestPinmux_configSettingsAllBitsSet: PASS\r\n");
}

/*
 * Test case: TestPinmux_configSettingsZero
 * This test verifies that the Pinmux_config function can correctly clear all configuration bits
 * for a pin in the MAIN domain by writing a settings value of zero. It first configures the pin
 * with a non-zero value to ensure a real change occurs, then writes zero to clear all settings.
 * The test reads back the register value and checks that it is zero, confirming that all fields
 * have been reset. This ensures the driver can handle clearing pinmux settings as expected.
 */
static void TestPinmux_configSettingsZero(void *args)
{
    uint32_t baseAddr, readValue;

    DebugP_log("\r\n TestPinmux_configSettingsZero started...\r\n");

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);

    /* First write non-zero to ensure we're testing a real change */
    Pinmux_PerCfg_t pinCfgNonZero[] = {
        { TEST_PINMUX_SOC_GPIO_PIN, PIN_MODE(7) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfgNonZero, PINMUX_DOMAIN_ID_MAIN);

    /* Now write zero to clear all settings */
    Pinmux_PerCfg_t pinCfgZero[] = {
        { TEST_PINMUX_SOC_GPIO_PIN, 0x0U },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfgZero, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_GPIO_PIN);
    TEST_ASSERT_EQUAL_UINT32(0x0U, readValue);

    DebugP_log("TestPinmux_configSettingsZero: PASS\r\n");
}

/*
 * Test case: TestPinmux_configNullPointer
 * This test verifies that the Pinmux_config function gracefully handles NULL pointer inputs
 * for both MAIN and MCU domains. It calls Pinmux_config with a NULL configuration array,
 * ensuring that the driver does not crash or perform any invalid memory accesses.
 * After the NULL pointer calls, the test configures a valid pin and reads back the register
 * value to confirm that the driver remains functional. The test passes if no errors occur
 * and the register value matches the expected configuration.
 */
static void TestPinmux_configNullPointer(void *args)
{
    uint32_t baseAddr, readValue;

    DebugP_log("\r\n TestPinmux_configNullPointer started...\r\n");

    /* NULL pointer should be handled gracefully — no crash */
    Pinmux_config(NULL, PINMUX_DOMAIN_ID_MAIN);
    Pinmux_config(NULL, PINMUX_DOMAIN_ID_MCU);

    /* Verify driver is still functional after NULL calls */
    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_SOC_OSPI0_CLK, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_OSPI0_CLK);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    DebugP_log("TestPinmux_configNullPointer: PASS\r\n");
}

/*
 * Test case: TestPinmux_configInvalidDomainId
 * This test exposes a bug in the Pinmux_config driver: when an invalid domain ID
 * is passed, the else branch incorrectly falls through to the MCU domain base address,
 * causing an unintended write to MCU domain registers.
 *
 * The correct behavior for an invalid domain ID is that NO registers in either domain
 * should be modified. This test asserts that expected correct behavior, so it will FAIL
 * against the current buggy driver — proving that the invalid domain ID is not handled
 * properly.
 *
 * Steps:
 *   1. Save MAIN and MCU register values before the call.
 *   2. Call Pinmux_config with invalid domain ID (0xFFU).
 *   3. Assert MAIN domain register is unchanged (this will pass).
 *   4. Assert MCU domain register is unchanged (this will FAIL because
 *      the driver's else branch writes to MCU base for invalid IDs).
 */
static void TestPinmux_configInvalidDomainId(void *args)
{
    uint32_t mainBaseAddr, mcuBaseAddr;
    uint32_t mainBefore, mcuBefore;
    uint32_t mainAfter, mcuAfter;

    DebugP_log("\r\n TestPinmux_configInvalidDomainId started...\r\n");

    mainBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);
    mcuBaseAddr  = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MCU_BASE + TEST_PINMUX_PADCFG_OFFSET);

    /* Save register values before the invalid domain call */
    mainBefore = CSL_REG32_RD(mainBaseAddr + TEST_PINMUX_SOC_SPI_CS0);
    mcuBefore  = CSL_REG32_RD(mcuBaseAddr + TEST_PINMUX_SOC_SPI_CS0);

    /* Use a distinctly different setting so any unintended write is detectable */
    uint32_t newSettings = PIN_MODE(5) | PIN_PULL_DISABLE | PIN_INPUT_ENABLE;

    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_SOC_SPI_CS0, newSettings },
        { PINMUX_END, 0 }
    };

    /* Pass invalid domain ID — ideally should do nothing */
    Pinmux_config(pinCfg, 0xFFU);

    /* Read register values after the invalid domain call */
    mainAfter = CSL_REG32_RD(mainBaseAddr + TEST_PINMUX_SOC_SPI_CS0);
    mcuAfter  = CSL_REG32_RD(mcuBaseAddr + TEST_PINMUX_SOC_SPI_CS0);

    /* MAIN domain register should remain unchanged */
    TEST_ASSERT_EQUAL_UINT32(mainBefore, mainAfter);

    /*
     * MCU domain register should also remain unchanged for an invalid domain ID.
     * BUG: The driver's else branch treats invalid IDs as MCU domain, so this
     * assertion will FAIL — proving the bug exists.
     */
    TEST_ASSERT_EQUAL_UINT32(mcuBefore, mcuAfter);


    /*
     * Restore the MCU register to its original value BEFORE asserting, so that
     * even if the assertion below fails (longjmp), subsequent tests see a clean
     * MCU register state and are not poisoned by the driver bug.
     */
    Pinmux_PerCfg_t pinCfgRestore[] = {
        { TEST_PINMUX_SOC_SPI_CS0, mcuBefore },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfgRestore, PINMUX_DOMAIN_ID_MCU);
}

/*
 * Test case: TestPinmux_unlockMMRInvalidDomain
 * This test verifies that Pinmux_unlockMMR and Pinmux_lockMMR do not modify any
 * registers when called with an invalid domain ID. Unlike Pinmux_config (which uses
 * if-else and falls into MCU for invalid IDs), the unlock/lock functions use separate
 * if-checks for MAIN and MCU, so an invalid domain should skip both blocks.
 * The test reads MAIN and MCU register values before and after the invalid calls
 * and verifies they remain unchanged.
 */
static void TestPinmux_unlockMMRInvalidDomain(void *args)
{
    uint32_t mainBaseAddr, mcuBaseAddr;
    uint32_t mainBefore, mcuBefore;
    uint32_t mainAfter, mcuAfter;

    DebugP_log("\r\n TestPinmux_unlockMMRInvalidDomain started...\r\n");

    mainBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);
    mcuBaseAddr  = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MCU_BASE + TEST_PINMUX_PADCFG_OFFSET);

    /* Read register values before invalid domain calls */
    mainBefore = CSL_REG32_RD(mainBaseAddr + TEST_PINMUX_SOC_OSPI0_CLK);
    mcuBefore  = CSL_REG32_RD(mcuBaseAddr + TEST_PINMUX_SOC_SPI_CS0);

    /* Invalid domain — both if-checks should be skipped, no registers modified */
    Pinmux_unlockMMR(0xFFU);
    Pinmux_lockMMR(0xFFU);

    /* Read register values after invalid domain calls */
    mainAfter = CSL_REG32_RD(mainBaseAddr + TEST_PINMUX_SOC_OSPI0_CLK);
    mcuAfter  = CSL_REG32_RD(mcuBaseAddr + TEST_PINMUX_SOC_SPI_CS0);

    /* Both domains should remain unchanged */
    TEST_ASSERT_EQUAL_UINT32(mainBefore, mainAfter);
    TEST_ASSERT_EQUAL_UINT32(mcuBefore, mcuAfter);

    /* Verify driver still works after invalid domain calls */
    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_SOC_OSPI0_CLK, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);

    mainAfter = CSL_REG32_RD(mainBaseAddr + TEST_PINMUX_SOC_OSPI0_CLK);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, mainAfter);
}

/*
 * Test case: TestPinmux_configRepeatedCalls
 * This test verifies the robustness of the Pinmux_config function when called repeatedly
 * in rapid succession for both MAIN and MCU domains. It configures a pin in each domain
 * in a tight loop for a large number of iterations, then reads back the register value
 * to ensure the configuration remains correct. This helps ensure that repeated calls
 * do not cause resource leaks, race conditions, or register corruption.
 */
static void TestPinmux_configRepeatedCalls(void *args)
{
    uint32_t baseAddr, readValue, i;

    DebugP_log("\r\n TestPinmux_configRepeatedCalls started...\r\n");

    Pinmux_PerCfg_t pinCfgMain[] = {
        { TEST_PINMUX_SOC_OSPI0_CLK, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };

    Pinmux_PerCfg_t pinCfgMCU[] = {
        { TEST_PINMUX_SOC_SPI_CS0, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };

    /* Stress MAIN domain */
    for (i = 0U; i < TEST_PINMUX_STRESS_CONFIG_COUNT; i++)
    {
        Pinmux_config(pinCfgMain, PINMUX_DOMAIN_ID_MAIN);
    }

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_OSPI0_CLK);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    /* Stress MCU domain */
    for (i = 0U; i < TEST_PINMUX_STRESS_CONFIG_COUNT; i++)
    {
        Pinmux_config(pinCfgMCU, PINMUX_DOMAIN_ID_MCU);
    }

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MCU_BASE + TEST_PINMUX_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_SPI_CS0);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    DebugP_log("TestPinmux_configRepeatedCalls: PASS\r\n");
}

/*
 * Test case: TestPinmux_unlockLockRepeated
 * This test stresses the Pinmux_unlockMMR and Pinmux_lockMMR functions by repeatedly
 * unlocking and locking the MMRs for both MAIN and MCU domains in a tight loop.
 * After the stress cycles, it verifies that pinmux configuration still works correctly
 * by configuring a pin and reading back the register value for both domains.
 * This ensures that repeated lock/unlock operations do not cause resource leaks,
 * deadlocks, or register corruption, and that the driver remains functional.
 */
static void TestPinmux_unlockLockRepeated(void *args)
{
    uint32_t baseAddr, readValue, i;

    DebugP_log("\r\n TestPinmux_unlockLockRepeated started...\r\n");

    /* Stress MAIN domain lock/unlock */
    for (i = 0U; i < TEST_PINMUX_STRESS_LOCK_COUNT; i++)
    {
        Pinmux_unlockMMR(PINMUX_DOMAIN_ID_MAIN);
        Pinmux_lockMMR(PINMUX_DOMAIN_ID_MAIN);
    }

    /* Verify config still works after stress cycling */
    Pinmux_PerCfg_t pinCfgMain[] = {
        { TEST_PINMUX_SOC_OSPI0_CLK, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfgMain, PINMUX_DOMAIN_ID_MAIN);

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MAIN_BASE + TEST_PINMUX_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_OSPI0_CLK);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    /* Stress MCU domain lock/unlock */
    for (i = 0U; i < TEST_PINMUX_STRESS_LOCK_COUNT; i++)
    {
        Pinmux_unlockMMR(PINMUX_DOMAIN_ID_MCU);
        Pinmux_lockMMR(PINMUX_DOMAIN_ID_MCU);
    }

    /* Verify config still works */
    Pinmux_PerCfg_t pinCfgMCU[] = {
        { TEST_PINMUX_SOC_SPI_CS0, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfgMCU, PINMUX_DOMAIN_ID_MCU);

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MCU_BASE + TEST_PINMUX_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SOC_SPI_CS0);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    DebugP_log("TestPinmux_unlockLockRepeated: PASS\r\n");
}
#endif


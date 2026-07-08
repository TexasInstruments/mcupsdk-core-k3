/*
 *  Copyright (C) 2021-2026 Texas Instruments Incorporated
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
 *  \file test_pinmux_system.c
 *
 *  \brief This file contains implementation of system test cases for
 *         the pinmux module. These tests are designed to run in a multi-core
 *         system test framework, following the test_ecap_system.c pattern.
 *
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
#include "test_pinmux_system.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* SOC-specific pin and base address definitions */
#if defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62X) || defined(SOC_AM62DX)
#define TEST_PINMUX_SYS_SPI_CS0        PIN_MCU_SPI0_CS0
#define TEST_PINMUX_SYS_OSPI0_CLK      PIN_OSPI0_CLK
#define TEST_PINMUX_SYS_OSPI0_D0       PIN_OSPI0_D0
#define TEST_PINMUX_SYS_OSPI0_CSN0     PIN_OSPI0_CSN0
#define TEST_PINMUX_SYS_GPIO_PIN       PIN_GPIO0_45
#define TEST_PINMUX_SYS_MAIN_BASE      CSL_PADCFG_CTRL0_CFG0_BASE
#define TEST_PINMUX_SYS_MCU_BASE       CSL_WKUP_PADCFG_CTRL0_CFG0_BASE
#elif defined(SOC_AM275X)
#define TEST_PINMUX_SYS_SPI_CS0        PIN_SPI0_CS0
#define TEST_PINMUX_SYS_OSPI0_CLK      PIN_OSPI0_CLK
#define TEST_PINMUX_SYS_OSPI0_D0       PIN_OSPI0_D0
#define TEST_PINMUX_SYS_OSPI0_CSN0     PIN_OSPI0_CSN0
#define TEST_PINMUX_SYS_GPIO_PIN       PIN_GPIO1_47
#define TEST_PINMUX_SYS_MAIN_BASE      CSL_PADCFG_CTRL0_CFG0_BASE
#define TEST_PINMUX_SYS_MCU_BASE       CSL_MCU_PADCFG_CTRL0_CFG0_BASE
#endif

#define TEST_PINMUX_SYS_PADCFG_OFFSET  (0x4000U)

/* Number of stress iterations for system-level repeated config */
#define TEST_PINMUX_SYS_STRESS_COUNT   (500U)

/* ========================================================================== */
/*                               Typedefs                                     */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

int32_t TestPinmux_configMultiplePins(void *args);
int32_t TestPinmux_configVerifyModeChange(void *args);
int32_t TestPinmux_configAllSettingsBits(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * TC_01: Functional Test - Configure multiple pins in MAIN domain
 * This test configures three MAIN domain pins (OSPI0_CLK, OSPI0_D0, OSPI0_CSN0)
 * with different settings using a single Pinmux_config call. It then reads back
 * the register values for each pin and verifies that the configuration matches
 * the expected settings. This ensures that multiple pin configurations are
 * applied correctly in a batch operation.
 */
int32_t TestPinmux_configMultiplePins(void *args)
{
    uint32_t    baseAddr, readValue;
    int32_t     status = SystemP_SUCCESS;

    DebugP_log("\r\nTestPinmux_configMultiplePins started...\r\n");

    /* Config array with 3 MAIN domain pins */
    Pinmux_PerCfg_t pinCfgMain[] = {
        { TEST_PINMUX_SYS_OSPI0_CLK,  PIN_MODE(0) | PIN_INPUT_ENABLE },
        { TEST_PINMUX_SYS_OSPI0_D0,   PIN_MODE(0) | PIN_INPUT_ENABLE },
        { TEST_PINMUX_SYS_OSPI0_CSN0, PIN_MODE(0) | PIN_PULL_DISABLE },
        { PINMUX_END, 0 }
    };

    Pinmux_config(pinCfgMain, PINMUX_DOMAIN_ID_MAIN);

    /* Read back and verify each pin */
    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_SYS_MAIN_BASE + TEST_PINMUX_SYS_PADCFG_OFFSET);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SYS_OSPI0_CLK);
    if(readValue != (PIN_MODE(0) | PIN_INPUT_ENABLE))
    {
        status = SystemP_FAILURE;
    }

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SYS_OSPI0_D0);
    if(readValue != (PIN_MODE(0) | PIN_INPUT_ENABLE))
    {
        status = SystemP_FAILURE;
    }

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SYS_OSPI0_CSN0);
    if(readValue != (PIN_MODE(0) | PIN_PULL_DISABLE))
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("TestPinmux_configMultiplePins: PASS\r\n");
    }
    else
    {
        DebugP_log("TestPinmux_configMultiplePins: FAIL\r\n");
    }

    return status;
}

/*
 * TC_02: Functional Test - Verify pin mode change
 * This test configures a MAIN domain pin (GPIO) to Mode 0 and verifies the register value.
 * It then reconfigures the same pin to Mode 7 and checks that the mode change is reflected in hardware.
 * This ensures that the Pinmux_config API can correctly update the mode of a pin that has already been configured.
 * The test validates both initial configuration and subsequent mode change for correctness.
 * It follows the ECAP system test pattern for register-level verification.
 */
int32_t TestPinmux_configVerifyModeChange(void *args)
{
    uint32_t    baseAddr, readValue;
    int32_t     status = SystemP_SUCCESS;

    DebugP_log("\r\nTestPinmux_configVerifyModeChange started...\r\n");

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_SYS_MAIN_BASE + TEST_PINMUX_SYS_PADCFG_OFFSET);

    /* Configure pin to Mode 0 */
    Pinmux_PerCfg_t pinCfg1[] = {
        { TEST_PINMUX_SYS_GPIO_PIN, PIN_MODE(0) },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg1, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SYS_GPIO_PIN);
    /* Check if pin is set to Mode 0 */
    if((readValue & 0xFU) != 0x0U)
    {
        status = SystemP_FAILURE;
    }

    /* Reconfigure same pin to Mode 7 */
    Pinmux_PerCfg_t pinCfg2[] = {
        { TEST_PINMUX_SYS_GPIO_PIN, PIN_MODE(7) },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg2, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SYS_GPIO_PIN);
    /* Check if pin is set to Mode 7 */
    if((readValue & 0xFU) != 0x7U)
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("TestPinmux_configVerifyModeChange: PASS\r\n");
    }
    else
    {
        DebugP_log("TestPinmux_configVerifyModeChange: FAIL\r\n");
    }

    return status;
}

/*
 * TC_03: Functional Test - Configure all pin settings bits
 * This test configures a MAIN domain pin (GPIO) with all possible settings bits:
 * mode, pull disable, pull direction, input enable, and output disable.
 * It then reads back the register value and verifies that each bit field is set
 * as expected. This ensures that the Pinmux_config API correctly applies all
 * configuration bits and that the hardware reflects the requested settings.
 */
int32_t TestPinmux_configAllSettingsBits(void *args)
{
    uint32_t    baseAddr, readValue;
    uint32_t    settings;
    int32_t     status = SystemP_SUCCESS;

    DebugP_log("\r\nTestPinmux_configAllSettingsBits started...\r\n");

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_SYS_MAIN_BASE + TEST_PINMUX_SYS_PADCFG_OFFSET);

    settings = PIN_MODE(5) | PIN_PULL_DISABLE | PIN_PULL_DIRECTION | PIN_INPUT_ENABLE | PIN_OUTPUT_DISABLE;

    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_SYS_GPIO_PIN, settings },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_SYS_GPIO_PIN);

    /* Verify each bit field */
    if ((readValue & 0xFU) != 5U) {                /* Mode 5 */
        status = SystemP_FAILURE;
    }
    if (((readValue >> 16U) & 0x1U) != 1U) {       /* Pull disable */
        status = SystemP_FAILURE;
    }
    if (((readValue >> 17U) & 0x1U) != 1U) {       /* Pull direction */
        status = SystemP_FAILURE;
    }
    if (((readValue >> 18U) & 0x1U) != 1U) {       /* Input enable */
        status = SystemP_FAILURE;
    }
    if (((readValue >> 21U) & 0x1U) != 1U) {       /* Output disable */
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("TestPinmux_configAllSettingsBits: PASS\r\n");
    }
    else
    {
        DebugP_log("TestPinmux_configAllSettingsBits: FAIL\r\n");
    }

    return status;
}

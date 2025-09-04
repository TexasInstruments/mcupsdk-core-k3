/*
 * Copyright (C) 2025 Texas Instruments Incorporated
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
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62X)
#define TEST_PINMUX_SOC_SPI_CS0    PIN_MCU_SPI0_CS0
#define TEST_PINMUX_SOC_OSPI0_CLK  PIN_OSPI0_CLK
#endif

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Testcases */
static void test_pinmux_coverage(void *args);

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

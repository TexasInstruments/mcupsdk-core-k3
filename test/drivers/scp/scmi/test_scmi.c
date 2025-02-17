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
#include <kernel/dpl/SystemP.h>
#include <drivers/scmi.h>
#include "ti_drivers_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_SCMI_NUMAGENTS_EXPECTED                0U
#define TEST_SCMI_NUMPROTOCOLS_EXPECTED             2U
#define TEST_SCMI_BASE_MSG_ATTR_EXPECTED            0U
#define TEST_SCMI_VENDOR_NAME_EXPECTED              "Texas"
#define TEST_SCMI_SUBVENDOR_NAME_EXPECTED           "Instruments"
#define TEST_SCMI_IMPLVERSION_EXPECTED              0U

#define TEST_SCMI_PD_EXPECTEDNUM_PD                 98
#define TEST_SCMI_PD_AM62LX_DEV_MMCSD0              28U
#define TEST_SCMI_PD_AM62LX_DEV_MMCSD0_NAME         "MMCSD0"
#define TEST_SCMI_PD_AM62LX_DEV_DSS0                39U
#define TEST_SCMI_PD_AM62LX_DEV_DSS0_NAME           "DSS0"

#define TEST_SCMI_CLOCK_EXPECTEDNUM_CLOCK           66025
#define TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK     134
#define TEST_CLK_EXPECTED_DEV_FSS0_OSPI0_RCLK_PRNT  135
#define TEST_CLK_SET_DEV_FSS0_OSPI0_RCLK_PRNT       136
#define TEST_CLK_NUMPARENTS_OSPI0_RCLK              2
#define TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_NAME    "5_FSS0"
#define TEST_CLK_AM62LX_CLOCK_FREQ                  166666666

/* ========================================================================== */
/*                       Structure Declarations                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Test cases */
static void test_scmi_base_protocol(void *args);
static void test_scmi_power_domain_protocol(void *args);
static void test_scmi_clock_protocol(void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8_t gProtoTableExpected[TEST_SCMI_NUMPROTOCOLS_EXPECTED] = {
	SCMI_PROTOCOL_POWER,
	SCMI_PROTOCOL_CLOCK,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    UNITY_BEGIN();

    RUN_TEST(test_scmi_base_protocol, 3825, NULL);
    RUN_TEST(test_scmi_power_domain_protocol, 3825, NULL);
    RUN_TEST(test_scmi_clock_protocol, 3825, NULL);

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
 * Test cases
 */

static void test_scmi_base_protocol(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t version;
    uint32_t numAgents;
    uint32_t numProtocols;
    uint32_t attributes;
    uint32_t implVersion;
    uint32_t protoCount;
    uint8_t protocols[SCMI_BASE_MAX_NUM_PROTOCOLS];
	uint8_t vendor[SCMI_BASE_NAME_LENGTH_MAX];
	uint8_t subVendor[SCMI_BASE_NAME_LENGTH_MAX];

    DebugP_log("Test: SCMI: Base protocol\r\n");

    SCMI_Handle handle = SCMI_getHandle(CONFIG_SCMI_INSTANCE);

    TEST_ASSERT_NOT_NULL(handle);

    status = SCMI_baseGenericProtocolVersion(handle, SCMI_PROTOCOL_POWER, &version);
    DebugP_log("Test: SCMI_PROTOCOL_POWER: version : %x\r\n", version);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SCMI_baseGenericProtocolVersion(handle, SCMI_PROTOCOL_CLOCK, &version);
    DebugP_log("Test: SCMI_PROTOCOL_CLOCK: version : %x\r\n", version);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SCMI_baseGenericProtocolVersion(handle, SCMI_PROTOCOL_POWERCAP, &version);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = SCMI_baseGetProtocolAttributes(handle, &numAgents, &numProtocols);
    TEST_ASSERT_EQUAL_UINT32(TEST_SCMI_NUMAGENTS_EXPECTED, numAgents);
    TEST_ASSERT_EQUAL_UINT32(TEST_SCMI_NUMPROTOCOLS_EXPECTED, numProtocols);
    DebugP_log("Test: SCMI_PROTOCOL_BASE: Number of agents : %d\r\n", numAgents);
    DebugP_log("Test: SCMI_PROTOCOL_BASE: Number of protocols : %d\r\n", numProtocols);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SCMI_baseGetMessageAttributes(handle, SCMI_BASE_DISCOVER_VENDOR, &attributes);
    TEST_ASSERT_EQUAL_UINT32(TEST_SCMI_BASE_MSG_ATTR_EXPECTED, attributes);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SCMI_baseDiscoverVendor(handle, vendor);
    TEST_ASSERT_EQUAL_STRING(TEST_SCMI_VENDOR_NAME_EXPECTED, vendor);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_BASE: Vendor : %s\r\n", vendor);

    status = SCMI_baseDiscoverSubVendor(handle, subVendor);
    TEST_ASSERT_EQUAL_STRING(TEST_SCMI_SUBVENDOR_NAME_EXPECTED, subVendor);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_BASE: SubVendor : %s\r\n", subVendor);

    status = SCMI_baseDiscoverImplementationVersion(handle, &implVersion);
    TEST_ASSERT_EQUAL_UINT32(TEST_SCMI_IMPLVERSION_EXPECTED, implVersion);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SCMI_baseDiscoverListProtocols(handle, &protoCount, protocols);
    TEST_ASSERT_EQUAL_UINT32(TEST_SCMI_NUMPROTOCOLS_EXPECTED, protoCount);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(gProtoTableExpected, protocols, protoCount);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("Test: SCMI_PROTOCOL_BASE: Identified Protocols :\r\n");
    for(uint8_t i=0; i<TEST_SCMI_NUMPROTOCOLS_EXPECTED; i++)
    {
        switch(protocols[i])
        {
            case SCMI_PROTOCOL_POWER:
                DebugP_log("SCMI_PROTOCOL_POWER\r\n");
                break;
            case SCMI_PROTOCOL_CLOCK:
                DebugP_log("SCMI_PROTOCOL_CLOCK\r\n");
                break;
            default:
                DebugP_log("Unidentified protocol\r\n");
                break;
        }
    }
}


static void test_scmi_power_domain_protocol(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t numPowerDomains;
    uint32_t attributes;
    uint64_t statsAddr;
    uint32_t statsLen;
    uint8_t pdName[SCMI_PWD_SHORT_NAME_SIZE];
    uint8_t extendedName[SCMI_PWD_EXTENDED_NAME_MAX];
    uint32_t flags = 0U;
    uint32_t pstate;

    DebugP_log("Test: SCMI: Power Domain protocol\r\n");

    SCMI_Handle handle = SCMI_getHandle(CONFIG_SCMI_INSTANCE);

    TEST_ASSERT_NOT_NULL(handle);

    status = SCMI_powerDomainGetProtocolAttrs(handle,
                                            &numPowerDomains,
                                            &statsAddr,
                                            &statsLen);
    TEST_ASSERT_EQUAL_UINT32(TEST_SCMI_PD_EXPECTEDNUM_PD, numPowerDomains);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_POWER: Number of power domains : %d\r\n", numPowerDomains);
    DebugP_log("Test: SCMI_PROTOCOL_POWER: Stats address : %d\r\n", statsAddr);
    DebugP_log("Test: SCMI_PROTOCOL_POWER: Stats length : %d\r\n", statsLen);

    status = SCMI_powerDomainGetAttrs(handle, TEST_SCMI_PD_AM62LX_DEV_MMCSD0,
                                     &attributes, pdName);
    TEST_ASSERT_EQUAL_STRING(TEST_SCMI_PD_AM62LX_DEV_MMCSD0_NAME, pdName);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_POWER: Attributes: Name : %s\r\n", pdName);

    DebugP_log("Test: SCMI: Power Domain protocol: Switch on: TEST_SCMI_PD_AM62LX_DEV_MMCSD0\r\n");
    status = SCMI_powerDomainStateSet(handle, TEST_SCMI_PD_AM62LX_DEV_MMCSD0,
                                      flags, SCMI_PWD_POWER_STATE_ON);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = SCMI_powerDomainStateGet(handle, TEST_SCMI_PD_AM62LX_DEV_MMCSD0,
                                      &pstate);
    TEST_ASSERT_EQUAL_UINT32(SCMI_PWD_POWER_STATE_ON, pstate);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_POWER: TEST_SCMI_PD_AM62LX_DEV_MMCSD0: State : %x\r\n", pstate);

    DebugP_log("Test: SCMI: Power Domain protocol: Switch off: TEST_SCMI_PD_AM62LX_DEV_MMCSD0\r\n");
    status = SCMI_powerDomainStateSet(handle, TEST_SCMI_PD_AM62LX_DEV_MMCSD0,
                                      flags, SCMI_PWD_POWER_STATE_OFF);
    status = SCMI_powerDomainStateGet(handle, TEST_SCMI_PD_AM62LX_DEV_MMCSD0,
                                      &pstate);
    TEST_ASSERT_EQUAL_UINT32(SCMI_PWD_POWER_STATE_OFF, pstate);
    DebugP_log("Test: SCMI_PROTOCOL_POWER: TEST_SCMI_PD_AM62LX_DEV_MMCSD0: State : %x\r\n", pstate);

    status = SCMI_powerDomainNameGet(handle, TEST_SCMI_PD_AM62LX_DEV_DSS0,
                                    extendedName);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

}


static void test_scmi_clock_protocol(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t numClocks;
    uint32_t attributes;
    uint8_t clkName[SCMI_CLK_SHORT_NAME_SIZE];
    uint8_t extendedName[SCMI_CLK_NAME_LENGTH_MAX];
    uint32_t clockState;
    uint64_t clockRate;

    DebugP_log("Test: SCMI: CLock protocol\r\n");

    SCMI_Handle handle = SCMI_getHandle(CONFIG_SCMI_INSTANCE);

    TEST_ASSERT_NOT_NULL(handle);

    status = SCMI_clockGetProtocolAttrs(handle, &numClocks);
    TEST_ASSERT_EQUAL_UINT32(TEST_SCMI_CLOCK_EXPECTEDNUM_CLOCK, numClocks);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_CLOCK: Number of clocks: %d\r\n", numClocks);


    status = SCMI_clockGetAttrs(handle, TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK,
                                &attributes, clkName);
    TEST_ASSERT_EQUAL_UINT32(SCMI_CLK_CONFIG_SET_ENABLE, \
                            SCMI_CLK_CONFIG_SET_ENABLE & attributes);
    TEST_ASSERT_EQUAL_UINT32(SCMI_CLK_ATTR_PARENT_CLOCK, \
                            SCMI_CLK_ATTR_PARENT_CLOCK & attributes);
    TEST_ASSERT_EQUAL_STRING(TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_NAME, clkName);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_CLOCK: Attributes: Name : %s\r\n", clkName);

    status = SCMI_clockConfigSet(handle, TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK,
                                SCMI_CLK_CONFIG_SET_ENABLE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SCMI_clockConfigGet(handle, TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK,
                                &clockState);
    TEST_ASSERT_EQUAL_UINT32(SCMI_CLK_CONFIG_SET_ENABLE, clockState);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_CLOCK: TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK: State : %x\r\n", clockState);

    status = SCMI_clockNameGet(handle, TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK,
                            extendedName);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = SCMI_clockRateGet(handle, TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK,
                            &clockRate);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_CLOCK: TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK: Get Rate : %d\r\n", clockRate);


    clockRate = TEST_CLK_AM62LX_CLOCK_FREQ;
    DebugP_log("Test: SCMI: Power Domain protocol: Set Rate %d: TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK\r\n", clockRate);
    status = SCMI_clockRateSet(handle, TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK,
                            clockRate);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    status = SCMI_clockRateGet(handle, TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK,
                            &clockRate);
    TEST_ASSERT_EQUAL_UINT64(TEST_CLK_AM62LX_CLOCK_FREQ, clockRate);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Test: SCMI_PROTOCOL_CLOCK: TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK: Get Rate : %d\r\n", clockRate);

}

#include <stdio.h>
//! [include]
#include <drivers/scmi.h>
//! [include]

void base_protocol(void)
{
//! [base_protocol]
    int32_t status;
    uint32_t version;
    SCMI_Handle handle = SCMI_getHandle(CONFIG_SCMI_INSTANCE);

    /* Get Power Domain Protocol Version */
    status = SCMI_baseGenericProtocolVersion(handle, SCMI_PROTOCOL_POWER, &version);
    DebugP_log("SCMI_PROTOCOL_POWER: version : %x\r\n", version);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Get Clock Domain Protocol Version */
    status = SCMI_baseGenericProtocolVersion(handle, SCMI_PROTOCOL_CLOCK, &version);
    DebugP_log("SCMI_PROTOCOL_CLOCK: version : %x\r\n", version);
    DebugP_assert(status == SystemP_SUCCESS);
//! [base_protocol]
}

void power_domain_protocol(void)
{
//! [power_domain_protocol]
    int32_t status;
    uint32_t flags = 0U;
    /* Power on */
    status = SCMI_powerDomainStateSet(handle, TEST_SCMI_PD_AM62LX_DEV_MMCSD0,
                                      flags, SCMI_PWD_POWER_STATE_ON);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Check the power state */
    status = SCMI_powerDomainStateGet(handle, TEST_SCMI_PD_AM62LX_DEV_MMCSD0,
                                      &pstate);
    DebugP_asssert(pstate == SCMI_PWD_POWER_STATE_ON);
//! [power_domain_protocol]
}

void clock_protocol(void)
{
//! [clock_protocol]
    int32_t status;
    uint64_t clockRate;
    SCMI_Handle handle = SCMI_getHandle(CONFIG_SCMI_INSTANCE);

    /* Get clock rate */
    status = SCMI_clockRateGet(handle, TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK,
                            &clockRate);
    DebugP_assert(status == SystemP_SUCCESS);
    DebugP_log("SCMI_PROTOCOL_CLOCK: TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK: Get Rate : %d\r\n", clockRate);

    /* Set clock rate */
    clockRate = TEST_CLK_AM62LX_CLOCK_FREQ;
    status = SCMI_clockRateSet(handle, TEST_CLK_AM62LX_DEV_FSS0_OSPI0_RCLK_CLK,
                            clockRate);
    DebugP_assert(status == SystemP_SUCCESS);
//! [clock_protocol]
}
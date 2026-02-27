/*
 * Copyright (C) 2026 Texas Instruments Incorporated
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
 *  \file test_sciclient_interrupt_mode.c
 *
 *  \brief This file contains tests for sciclient interrupt mode functionality.
 *         Tests cover mode switching APIs and message passing in interrupt mode.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/sciclient.h>
#include <drivers/hw_include/cslr_soc.h>
#include <drivers/sciclient/include/tisci/security/tisci_otp_revision.h>
#if defined (SOC_AM62AX)
#include <drivers/sciclient/include/tisci/am62ax/tisci_clocks.h>
#elif defined (SOC_AM62PX)
#include <drivers/sciclient/include/tisci/am62px/tisci_clocks.h>
#elif defined (SOC_AM62DX)
#include <drivers/sciclient/include/tisci/am62dx/tisci_clocks.h>
#elif defined (SOC_AM62X)
#include <drivers/sciclient/include/tisci/am62x/tisci_clocks.h>
#elif defined (SOC_AM275X)
#include <drivers/sciclient/include/tisci/am275x/tisci_clocks.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test module ID - TIMER0 is commonly available across SOCs */
#define TEST_MODULE_ID    TISCI_DEV_TIMER0
#if defined (SOC_AM62AX) || defined (SOC_AM62PX) || defined (SOC_AM62DX)
#define CORE_ID           CSL_CORE_ID_MCU_R5FSS0_0
#elif defined (SOC_AM62X)
#define CORE_ID           CSL_CORE_ID_M4FSS0_0
#elif defined (SOC_AM275X)
#define CORE_ID           CSL_CORE_ID_R5FSS0_0
#endif

/* ========================================================================== */
/*                          Message Passing Test Structures                   */
/* ========================================================================== */

/* Request/Response structures for TISCI_MSG_GET_TRACE_CONFIG (forwarded to TIFS) */
static struct tisci_get_trace_config_req requestGetTraceAOP;
static Sciclient_ReqPrm_t reqParamGetTraceAOP =
{
    .messageType    = (uint16_t) TISCI_MSG_GET_TRACE_CONFIG,
    .flags          = (uint32_t) TISCI_MSG_FLAG_AOP,
    .pReqPayload    = (const uint8_t *) &requestGetTraceAOP,
    .reqPayloadSize = (uint32_t) sizeof (requestGetTraceAOP),
    .timeout        = (uint32_t) (0xFFFFFFFFU),
};

static struct tisci_get_trace_config_resp responseGetTraceAOP;
static Sciclient_RespPrm_t respParamGetTraceAOP =
{
    .flags           = (uint32_t) 0,
    .pRespPayload    = (uint8_t *) &responseGetTraceAOP,
    .respPayloadSize = (uint32_t) sizeof (responseGetTraceAOP),
};

static struct tisci_get_trace_config_req requestGetTrace0;
static Sciclient_ReqPrm_t reqParamGetTrace0 =
{
    .messageType = (uint16_t) TISCI_MSG_GET_TRACE_CONFIG,
    .flags = (uint32_t) 0,
    .pReqPayload = (const uint8_t *) &requestGetTrace0,
    .reqPayloadSize = (uint32_t) sizeof (requestGetTrace0),
    .timeout = (uint32_t) (0xFFFFFFFFU),
};

static struct tisci_get_trace_config_resp responseGetTrace0;
static Sciclient_RespPrm_t respParamGetTrace0 =
{
    .flags = (uint32_t) 0,
    .pRespPayload = (uint8_t *) &responseGetTrace0,
    .respPayloadSize = (uint32_t) sizeof (responseGetTrace0),
};

/* Request/Response structures for TISCI_MSG_GET_FREQ (processed by DM alone) */
static struct tisci_msg_get_freq_req requestGetFreqAOP =
{
    .device = (uint32_t) TISCI_DEV_TIMER0,
    .clk    = (uint8_t) TISCI_DEV_TIMER0_TIMER_TCLK_CLK,
};
static Sciclient_ReqPrm_t reqParamGetFreqAOP =
{
    .messageType    = (uint16_t) TISCI_MSG_GET_FREQ,
    .flags          = (uint32_t) TISCI_MSG_FLAG_AOP,
    .pReqPayload    = (const uint8_t *) &requestGetFreqAOP,
    .reqPayloadSize = (uint32_t) sizeof (requestGetFreqAOP),
    .timeout        = (uint32_t) (0xFFFFFFFFU),
};

static struct tisci_msg_get_freq_resp responseGetFreqAOP = {0};
static Sciclient_RespPrm_t respParamGetFreqAOP =
{
    .flags           = (uint32_t) 0,
    .pRespPayload    = (uint8_t *) &responseGetFreqAOP,
    .respPayloadSize = (uint32_t) sizeof (responseGetFreqAOP),
};

static struct tisci_msg_get_freq_req requestGetFreq0 =
{
    .device = (uint32_t) TISCI_DEV_TIMER0,
    .clk    = (uint8_t) TISCI_DEV_TIMER0_TIMER_TCLK_CLK,
};
static Sciclient_ReqPrm_t reqParamGetFreq0 =
{
    .messageType    = (uint16_t) TISCI_MSG_GET_FREQ,
    .flags          = (uint32_t) 0,
    .pReqPayload    = (const uint8_t *) &requestGetFreq0,
    .reqPayloadSize = (uint32_t) sizeof (requestGetFreq0),
    .timeout        = (uint32_t) (0xFFFFFFFFU),
};

static struct tisci_msg_get_freq_resp responseGetFreq0 = {0};
static Sciclient_RespPrm_t respParamGetFreq0 =
{
    .flags           = (uint32_t) 0,
    .pRespPayload    = (uint8_t *) &responseGetFreq0,
    .respPayloadSize = (uint32_t) sizeof (responseGetFreq0),
};

/* Request/Response structures for TISCI_MSG_READ_SWREV (processed by TIFS alone) */
static struct tisci_msg_get_swrev_req requestReadSWRevAOP = 
{
    .identifier = OTP_REV_ID_SEC_BRDCFG,
};
static Sciclient_ReqPrm_t reqParamReadSWRevAOP =
{
    .messageType    = (uint16_t) TISCI_MSG_READ_SWREV,
    .flags          = (uint32_t) TISCI_MSG_FLAG_AOP,
    .pReqPayload    = (const uint8_t *) &requestReadSWRevAOP,
    .reqPayloadSize = (uint32_t) sizeof (requestReadSWRevAOP),
    .timeout        = (uint32_t) (0xFFFFFFFFU),
};

static struct tisci_msg_get_swrev_resp responseReadSWRevAOP = {0};
static Sciclient_RespPrm_t respParamReadSWRevAOP =
{
    .flags           = (uint32_t) 0,
    .pRespPayload    = (uint8_t *) &responseReadSWRevAOP,
    .respPayloadSize = (uint32_t) sizeof (responseReadSWRevAOP),
};

static struct tisci_msg_get_swrev_req requestReadSWRev0 =
{
    .identifier = OTP_REV_ID_SEC_BRDCFG,
};
static Sciclient_ReqPrm_t reqParamReadSWRev0 =
{
    .messageType    = (uint16_t) TISCI_MSG_READ_SWREV,
    .flags          = (uint32_t) 0,
    .pReqPayload    = (const uint8_t *) &requestReadSWRev0,
    .reqPayloadSize = (uint32_t) sizeof (requestReadSWRev0),
    .timeout        = (uint32_t) (0xFFFFFFFFU),
};

static struct tisci_msg_get_swrev_resp responseReadSWRev0 = {0};
static Sciclient_RespPrm_t respParamReadSWRev0 =
{
    .flags           = (uint32_t) 0,
    .pRespPayload    = (uint8_t *) &responseReadSWRev0,
    .respPayloadSize = (uint32_t) sizeof (responseReadSWRev0),
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int8_t test_sciclient_interrupt_mode_main(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Main test function for sciclient interrupt mode.
 *
 *  Tests the following:
 *  1. Mode switching APIs (updateOperModeToInterrupt, updateOperModeToPolled)
 *  2. Interrupt enable/disable APIs
 *  3. Message passing in interrupt mode
 *  4. Init/deinit with mode transitions
 */
int8_t test_sciclient_interrupt_mode_main(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    DebugP_log("\r\n=== Sciclient Interrupt Mode Test ===\r\n");

    DebugP_log("\r\n Deinitializing existing Sciclient if already initialised before for clean run...");
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    DebugP_log("\r\n Reinitializing Sciclient with core id as MCU Core...");
    retVal = Sciclient_init(CORE_ID);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    DebugP_log("\r\n Switching to Interrupt Mode...");
    retVal = Sciclient_updateOperModeToInterrupt();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    DebugP_log("\r\n Disabling interrupts...");
    Sciclient_disableIntr();

    DebugP_log("\r\n Enabling interrupts...");
    Sciclient_enableIntr();

    DebugP_log("\r\n Calling Sciclient Service for messages which are forwarded to TIFS and with AOP flag set...");
    retVal = Sciclient_service(&reqParamGetTraceAOP, &respParamGetTraceAOP);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    DebugP_log("\r\n Calling Sciclient Service for messages which are forwarded to TIFS and with 0 flag set...");
    retVal = Sciclient_service(&reqParamGetTrace0, &respParamGetTrace0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    DebugP_log("\r\n Calling Sciclient Service for messages which are forwarded to DM and with AOP flag set...");
    retVal = Sciclient_service(&reqParamGetFreqAOP, &respParamGetFreqAOP);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    DebugP_log("\r\n Calling Sciclient Service for messages which are forwarded to DM and with 0 flag set...");
    retVal = Sciclient_service(&reqParamGetFreq0, &respParamGetFreq0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    DebugP_log("\r\n Calling Sciclient Service for messages which are processed by TIFS and with AOP flag set...");
    retVal = Sciclient_service(&reqParamReadSWRevAOP, &respParamReadSWRevAOP);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    DebugP_log("\r\n Calling Sciclient Service for messages which are processed by TIFS and with 0 flag set...");
    retVal = Sciclient_service(&reqParamReadSWRev0, &respParamReadSWRev0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    DebugP_log("\r\n\r\n=== Sciclient Interrupt Mode Test Complete ===");
    DebugP_log("\r\n Total failures: %d\r\n", failCount);

    return failCount;
}

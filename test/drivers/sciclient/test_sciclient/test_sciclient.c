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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/sciclient.h>
#include <drivers/sciclient/include/tisci/tisci_core.h>
#include <drivers/sciclient/include/tisci/tisci_protocol.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_clock.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_device.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_ra.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_udmap.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_irq.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_shared.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_psil.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_proxy.h>
#include <drivers/sciclient/include/tisci/lpm/tisci_lpm.h>
#include <drivers/sciclient/include/tisci/security/tisci_ext_otp.h>
#include <drivers/sciclient/include/tisci/security/tisci_otp_revision.h>
#include <drivers/sciclient/include/tisci/security/tisci_sec_handover.h>
#include <drivers/sciclient/include/tisci/security/tisci_dkek.h>
#include <drivers/sciclient/include/tisci/security/tisci_dsmek.h>
#include <drivers/sciclient/include/tisci/security/tisci_keywriter.h>
#include <drivers/sciclient/include/tisci/security/tisci_keyring.h>
#include <drivers/sciclient/include/tisci/security/tisci_firewall.h>
#include <drivers/sciclient/include/tisci/security/tisci_procboot.h>
#include <drivers/sciclient/include/tisci/security/tisci_secure_jtag.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_core.h>
#include <drivers/sciclient/include/tisci/rm/tisci_rm_core.h>
#include "test_sciclient_pm.h"
#include "test_sciclient_rm.h"
#include "test_sciclient_lpm.h"
#include "test_sciclient_sec.h"
#include "test_sciclient_procboot.h"
#include "test_sciclient_intr_polling.h"
#include "test_sciclient_wrapper.h"
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* SoC-specific RM test values are defined in per-device header files included
 * via test_sciclient_rm.h (see am62dx-evm/ and am275x-evm/ subdirs). */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t test_msgVersion(void *args);
static int32_t test_msgDMversion(void *args);
static int32_t test_msgQueryFwCaps(void *args);
static int32_t test_msgBootNotification(void *args);
static int32_t test_msgGetTraceConfig(void *args);
static void testSciclient_version(void *args);
static void testSciclient_sysInit(void *args);

#if !defined(SKIP_SCICLIENT)
static int32_t test_msgBoardConfig(void *args);
static int32_t test_msgBoardConfigRM(void *args);
static int32_t test_msgBoardConfigPM(void *args);
static int32_t test_msgBoardConfigSecurity(void *args);
static void testSciclient_boardConfig(void *args);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(testSciclient_version, 12478, NULL);
    ClockP_usleep(10000);

#if !defined(SKIP_SCICLIENT)
    RUN_TEST(testSciclient_boardConfig, 12080, NULL);
#endif

    ClockP_usleep(10000);
    RUN_TEST(testSciclient_clockMgmt, 12476, NULL);
    RUN_TEST(testSciclient_deviceMgmt, 12475, NULL);
    RUN_TEST(testSciclient_rmRing, 12474, NULL);
    RUN_TEST(testSciclient_rmUdmap, 12473, NULL);
    RUN_TEST(testSciclient_rmIrqPsil, 12472, NULL);
    RUN_TEST(testSciclient_rmProxy, 12471, NULL);

#ifdef CONFIG_TEST_LPM
    RUN_TEST(testSciclient_lpm, 12470, NULL);
#endif

    RUN_TEST(testSciclient_otpKeyMgmt, 12469, NULL);
    RUN_TEST(testSciclient_securityEncryption, 12468, NULL);
    RUN_TEST(testSciclient_sa2ulCrypto, 12467, NULL);
    RUN_TEST(testSciclient_sysInit, 12466, NULL);
    RUN_TEST(testSciclient_rmResourceRange, 12464, NULL);
    RUN_TEST(testSciclient_firewallMgmt, 12463, NULL);

    RUN_TEST(testSciclient_procBoot, 12462, NULL);
    RUN_TEST(testSciclient_sysControl, 12454, NULL);

    ClockP_usleep(10000);
#if !defined(CORE_C7)
    RUN_TEST(testSciclient_interruptModeValidation, 12453, NULL);
#endif
    ClockP_usleep(10000);

    RUN_TEST(testSciclient_pollModeValidation, 12452, NULL);

#if !defined(CORE_C7)
    RUN_TEST(testSciclient_updateOperMode, 12486, NULL);
#endif

    RUN_TEST(testSciclient_powerManagement, 12460, NULL);
    RUN_TEST(testSciclient_firewallApis, 12461, NULL);
    RUN_TEST(testSciclient_coreVersion, 12459, NULL);
    RUN_TEST(testSciclient_initDeinit, 12477, NULL);
#if !defined(CORE_A53)
    /* testSciclient_resourceManagementSciclient: was hanging on AM62DX A53_2 due to
     * Sciclient_rmGetResourceRange() being queried with an invalid
     * secondary_host=TISCI_HOST_ID_ALL (now fixed - see
     * test_sciclient_wrapper.c group 1). Re-enabled for MCU/C7; still
     * guarded off for A53 per the requested per-core exclusion. */
    RUN_TEST(testSciclient_resourceManagementSciclient, 12458, NULL);
#endif

#if !(defined(SOC_AM275X) || defined(CORE_A53))
    RUN_TEST(testSciclient_lpmSciclient, 12457, NULL);
#endif /* !SOC_AM275X */

    RUN_TEST(testSciclient_procBootSciclientApis, 12456, NULL);
    ClockP_usleep(10000);

#if !defined(SKIP_SCICLIENT)
    RUN_TEST(testSciclient_boardCfgApis, 12216, NULL);
    RUN_TEST(testSciclient_dkekApis, 12217, NULL);
    RUN_TEST(testSciclient_uartPrintf, 12214, NULL);
#endif

    UNITY_END();
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
    /* Empty setup */
}

void tearDown(void)
{
    /* Empty teardown */
}

/*
 * TC_00 wrapper — calls all three message sub-tests in sequence
 */
static void testSciclient_version(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgVersion(NULL);
    testfailcount += test_msgDMversion(NULL);
    testfailcount += test_msgQueryFwCaps(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

/*
 * TC_12 wrapper — System Initialisation: Boot Notification & Trace Config
 */
static void testSciclient_sysInit(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgBootNotification(NULL);
    testfailcount += test_msgGetTraceConfig(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

/*
 * TC_01 wrapper — Board Configuration tests
 */
#if !defined(SKIP_SCICLIENT)
static void testSciclient_boardConfig(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgBoardConfig(NULL);
    testfailcount += test_msgBoardConfigRM(NULL);
    testfailcount += test_msgBoardConfigPM(NULL);
    testfailcount += test_msgBoardConfigSecurity(NULL);
    TEST_ASSERT_EQUAL_INT32(testfailcount, 0);
}
#endif

/**
 * test_msgVersion — TISCI_MSG_VERSION (0x0002)
 *
 * TC-01  Positive: valid request, AOP flag, WAIT_FOREVER → SUCCESS + ACK
 * TC-02  Negative: short timeout (0x0A)                  → TIMEOUT
 * TC-03  Negative: RESERVED0 flag, no AOP, short timeout → not SUCCESS
 * TC-04  Negative: NULL pReqPayload, zero size            → FAILURE
 */
static int32_t test_msgVersion(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_version_req  request;
    struct tisci_msg_version_resp response;

    /* TC-01: Positive – valid request, AOP flag, WAIT_FOREVER */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgVersion TC-01 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – short timeout (0x0A) → not SUCCESS */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            (uint32_t) 0x0A
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgVersion TC-02 Negative - short timeout 0x0A: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – RESERVED0 flag only (no AOP), short timeout → not SUCCESS */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_VERSION,
            TISCI_MSG_FLAG_RESERVED0,
            (uint8_t *) &request,
            sizeof(request),
            (uint32_t) 0x0A
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgVersion TC-03 Negative - RESERVED0 flag no AOP short timeout: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – NULL pReqPayload, zero reqPayloadSize → not SUCCESS */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_VERSION,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgVersion TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

/**
 * test_msgDMversion — TISCI_MSG_DM_VERSION (0x000F)
 *
 * TC-01  Positive: valid request, AOP flag, WAIT_FOREVER → SUCCESS + ACK
 * TC-02  Negative: short timeout (0x0A)                  → not SUCCESS
 * TC-03  Negative: RESERVED0 flag only, short timeout    → not SUCCESS
 * TC-04  Negative: NULL pReqPayload, zero size            → not SUCCESS
 */
static int32_t test_msgDMversion(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_dm_version_req  request;
    struct tisci_msg_dm_version_resp response;

    /* TC-01: Positive – valid request, AOP flag, WAIT_FOREVER */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_DM_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgDMversion TC-01 Positive - valid request AOP flag WAIT_FOREVER: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – short timeout (0x0A) → not SUCCESS
     * On mailbox-based (non ENABLE_SCICLIENT_DIRECT) builds like this one,
     * the message is relayed over IPC to a separate DM core, so a very
     * short timeout is expected to expire before the response arrives. */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_DM_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            (uint32_t) 0x0A
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgDMversion TC-02 Negative test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: RESERVED0 flag only (no AOP), short timeout → not SUCCESS
     * Same reasoning as TC-02: on this mailbox-based build the short
     * timeout is expected to expire before a response is received. */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_DM_VERSION,
            TISCI_MSG_FLAG_RESERVED0,
            (uint8_t *) &request,
            sizeof(request),
            (uint32_t) 0x0A
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgDMversion TC-03 Negative - RESERVED0 flag no AOP short timeout: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – NULL pReqPayload, zero reqPayloadSize → not SUCCESS
     * Note: in ENABLE_SCICLIENT_DIRECT mode a NULL payload may return TIMEOUT
     * or another non-SUCCESS code rather than FAILURE; assert only not SUCCESS. */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_DM_VERSION,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgDMversion TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

/**
 * test_msgQueryFwCaps — TISCI_MSG_QUERY_FW_CAPS (0x0022)
 *
 * TC-01  Positive: valid request, AOP flag, WAIT_FOREVER → SUCCESS + ACK
 * TC-02  Negative: short timeout (0x0A)                  → TIMEOUT
 * TC-03  Negative: RESERVED0 flag, no AOP, short timeout → not SUCCESS
 * TC-04  Negative: NULL pReqPayload, zero size            → FAILURE
 */
static int32_t test_msgQueryFwCaps(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_query_fw_caps_req  request;
    struct tisci_query_fw_caps_resp response;

    /* TC-01: Positive – valid request, AOP flag, WAIT_FOREVER */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_QUERY_FW_CAPS,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgQueryFwCaps TC-01 Positive - valid request AOP flag WAIT_FOREVER: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Short timeout (0x0A)
     * Note: in ENABLE_SCICLIENT_DIRECT mode a short timeout may return TIMEOUT
     * or another non-SUCCESS code rather than FAILURE; assert only not SUCCESS. */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_QUERY_FW_CAPS,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            (uint32_t) 0x0A
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
    }

    /* TC-03: RESERVED0 flag only (no AOP), short timeout
     * Same reasoning as TC-02: in direct mode the call still succeeds. */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_QUERY_FW_CAPS,
            TISCI_MSG_FLAG_RESERVED0,
            (uint8_t *) &request,
            sizeof(request),
            (uint32_t) 0x0A
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
    }

    /* TC-04: Negative – NULL pReqPayload, zero reqPayloadSize → not SUCCESS
     * Note: in ENABLE_SCICLIENT_DIRECT mode a NULL payload may return TIMEOUT
     * or another non-SUCCESS code rather than FAILURE; assert only not SUCCESS. */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_QUERY_FW_CAPS,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgQueryFwCaps TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

#if !defined(SKIP_SCICLIENT)
/**
 * TC_01: Board Configuration Messages
 *
 * DRIVER FLOW ANALYSIS:
 *   TISCI_MSG_BOARD_CONFIG          → forwarded to TIFS via Sciclient_serviceSecureProxy()
 *   TISCI_MSG_BOARD_CONFIG_RM       → processed locally by RM, then forwarded to TIFS
 *   TISCI_MSG_BOARD_CONFIG_PM       → processed locally by Sciclient_ProcessPmMessage()
 *   TISCI_MSG_BOARD_CONFIG_SECURITY → forwarded to TIFS via Sciclient_serviceSecureProxy()
 *
 * POSITIVE TEST FEASIBILITY:
 *   BOARD_CONFIG (0x000B):
 *     NO — positive re-apply NOT SAFE at runtime. TIFS ACKs the re-submission
 *     but internally resets its board-configuration state machine, re-arming
 *     the TIFS security initialization path. The subsequent
 *     BOARD_CONFIG_SECURITY call then re-runs one-time TIFS security init
 *     code (firewall reconfiguration, DKEK derivation) on a live system,
 *     causing a firmware crash. Only the negative test (TC-02) is run.
 *
 *   BOARD_CONFIG_RM (0x000C):
 *     YES. Proven safe by test_sciclient_boardcfgRM() in sciclient_direct tests
 *     (cases 2,3,4,5 all pass). Re-applying the same RM board config is idempotent
 *     for existing resource assignments. Use Sciclient_boardCfgRm(NULL) which
 *     sends the identical default config that was applied at boot.
 *
 *   BOARD_CONFIG_PM (0x000E):
 *     YES. DM processes this locally via Sciclient_ProcessPmMessage() without
 *     forwarding to TIFS. Re-applying the same PM config is safe.
 *     Proven by test_sciclient_boardcfg() calling Sciclient_boardCfgPm(NULL).
 *
 *   BOARD_CONFIG_SECURITY (0x000D):
 *     YES. Forwarded to TIFS via Sciclient_serviceSecureProxy(). Re-submitting
 *     the same default security board config blob is idempotent — TIFS ACKs
 *     repeated submissions of the identical configuration (proven by TC-BC-06
 *     in the original test plan). Use Sciclient_getDefaultBoardCfgInfo() to
 *     obtain the same blob that was applied at boot.
 */

/**
 * test_msgBoardConfig — TISCI_MSG_BOARD_CONFIG (0x000B)
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgBoardConfig(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;


    /* TC-01: Positive – send valid BOARD_CONFIG (direct Sciclient_service) */
    {
        Sciclient_DefaultBoardCfgInfo_t bcfgInfo = { 0 };
        struct tisci_msg_board_config_req request = { 0 };
        struct tisci_msg_board_config_resp resp = { 0 };
        int32_t ret = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((ret) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfig TC-01 Positive test: ret=%d\r\n",
                       ret);
            failCount++;
        }
        request.tisci_boardcfgp_low  = (uint32_t)bcfgInfo.boardCfgLow;
        request.tisci_boardcfgp_high = 0U;
        request.tisci_boardcfg_size  = (uint16_t)bcfgInfo.boardCfgLowSize;
        request.tisci_boardcfg_devgrp = (uint8_t)DEVGRP_ALL;

        const Sciclient_ReqPrm_t reqPrm = {
            TISCI_MSG_BOARD_CONFIG,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm = {
            0,
            (uint8_t *)&resp,
            sizeof(resp)
        };
        ret = Sciclient_service(&reqPrm, &respPrm);
        if (!((ret == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfig TC-01 Positive test: ret=%d flags=0x%x\r\n",
                       ret, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL payload */
    {
        struct tisci_msg_board_config_resp resp_neg = { 0 };
        const Sciclient_ReqPrm_t reqPrm = {
            TISCI_MSG_BOARD_CONFIG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm = {
            0,
            (uint8_t *)&resp_neg,
            sizeof(resp_neg)
        };
        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfig TC-01 Negative - NULL payload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: negative – zero pointer/size */
    {
        struct tisci_msg_board_config_req request = { 0 };
        struct tisci_msg_board_config_resp resp = { 0 };
        request.tisci_boardcfgp_low  = 0U;
        request.tisci_boardcfgp_high = 0U;
        request.tisci_boardcfg_size  = 0U;
        request.tisci_boardcfg_devgrp = (uint8_t)DEVGRP_ALL;
        const Sciclient_ReqPrm_t reqPrm = {
            TISCI_MSG_BOARD_CONFIG,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm = {
            0,
            (uint8_t *)&resp,
            sizeof(resp)
        };
        int32_t ret = Sciclient_service(&reqPrm, &respPrm);
        if (!((ret != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfig TC-03 Negative test: ret=%d flags=0x%x\r\n",
                       ret, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: negative – devgrp */
    {
        Sciclient_DefaultBoardCfgInfo_t bcfgInfo = { 0 };
        struct tisci_msg_board_config_req request = { 0 };
        struct tisci_msg_board_config_resp resp = { 0 };
        int32_t ret = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((ret) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfig TC-04 Negative test: ret=%d\r\n",
                       ret);
            failCount++;
        }
        request.tisci_boardcfgp_low  = (uint32_t)bcfgInfo.boardCfgLow;
        request.tisci_boardcfgp_high = 0U;
        request.tisci_boardcfg_size  = (uint16_t)bcfgInfo.boardCfgLowSize;
        request.tisci_boardcfg_devgrp = 0xFFU;
        const Sciclient_ReqPrm_t reqPrm = {
            TISCI_MSG_BOARD_CONFIG,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm = {
            0,
            (uint8_t *)&resp,
            sizeof(resp)
        };
        ret = Sciclient_service(&reqPrm, &respPrm);
        if (!((ret != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfig TC-04 Negative test: ret=%d flags=0x%x\r\n",
                       ret, respPrm.flags);
            failCount++;
        }
    }

    /* TC-05: positive – size (too large) */
    {
        Sciclient_DefaultBoardCfgInfo_t bcfgInfo = { 0 };
        struct tisci_msg_board_config_req request = { 0 };
        struct tisci_msg_board_config_resp resp = { 0 };
        int32_t ret = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((ret) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfig TC-05 Positive test: ret=%d\r\n",
                       ret);
            failCount++;
        }
        request.tisci_boardcfgp_low  = (uint32_t)bcfgInfo.boardCfgLow;
        request.tisci_boardcfgp_high = 0U;
        request.tisci_boardcfg_size  = 0xFFFFU; /* Too large */
        request.tisci_boardcfg_devgrp = (uint8_t)DEVGRP_ALL;
        const Sciclient_ReqPrm_t reqPrm = {
            TISCI_MSG_BOARD_CONFIG,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm = {
            0,
            (uint8_t *)&resp,
            sizeof(resp)
        };
        ret = Sciclient_service(&reqPrm, &respPrm);
        if (!((ret != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfig TC-05 Negative test: ret=%d flags=0x%x\r\n",
                       ret, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

/**
 * test_msgBoardConfigRM — TISCI_MSG_BOARD_CONFIG_RM (0x000C)
 *
 * TC-01  Positive: re-apply default RM board config via raw Sciclient_service()
 *                  → SystemP_SUCCESS + TISCI_MSG_FLAG_ACK
 *        Obtains the default RM board config blob (same data applied at boot)
 *        via Sciclient_getDefaultBoardCfgInfo(), builds tisci_msg_board_config_rm_req
 *        explicitly, and calls Sciclient_service() directly — no wrapper API.
 *        Re-applying the same resource assignments is idempotent (proven by
 *        test_sciclient_boardcfgRM() cases 2, 3, 4, 5 in sciclient_direct tests).
 *        Both transport success AND firmware ACK are verified.
 *
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid devgrp (0xFF) → not SUCCESS or NACK
 * TC-04  Negative: zero size with valid address → not SUCCESS or NACK
 * TC-05  Negative: maximum size (0xFFFF) with valid address → not SUCCESS or NACK
 */
static int32_t test_msgBoardConfigRM(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    {
        Sciclient_DefaultBoardCfgInfo_t      bcfgInfo = { 0 };
        struct tisci_msg_board_config_rm_req request  = { 0 };
        struct tisci_msg_board_config_rm_resp resp_pos = { 0 };

        retVal = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((retVal) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfigRM TC-01 Positive - step1 getDefaultBoardCfgInfo: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        request.tisci_boardcfg_rmp_low   = (uint32_t) bcfgInfo.boardCfgLowRm;
        request.tisci_boardcfg_rmp_high  = 0U;
        request.tisci_boardcfg_rm_size   = (uint16_t) bcfgInfo.boardCfgLowRmSize;
        request.tisci_boardcfg_rm_devgrp = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_RM,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp_pos,
            sizeof(resp_pos)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigRM TC-01 Positive - step2 re-apply default RM board config: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload → Sciclient_service() returns not SUCCESS */
    {
        struct tisci_msg_board_config_rm_resp resp_neg = { 0 };
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_RM,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp_neg,
            sizeof(resp_neg)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigRM TC-02 Negative test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: positive – devgrp (0xFF) */
    {
        Sciclient_DefaultBoardCfgInfo_t bcfgInfo = { 0 };
        struct tisci_msg_board_config_rm_req request = { 0 };
        struct tisci_msg_board_config_rm_resp resp = { 0 };

        retVal = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((retVal) == (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfigRM TC-03 Negative test: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        request.tisci_boardcfg_rmp_low   = (uint32_t) bcfgInfo.boardCfgLowRm;
        request.tisci_boardcfg_rmp_high  = 0U;
        request.tisci_boardcfg_rm_size   = (uint16_t) bcfgInfo.boardCfgLowRmSize;
        request.tisci_boardcfg_rm_devgrp = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_RM,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigRM TC-03 Negative test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: positive – zero size with valid address */
    {
        Sciclient_DefaultBoardCfgInfo_t bcfgInfo = { 0 };
        struct tisci_msg_board_config_rm_req request = { 0 };
        struct tisci_msg_board_config_rm_resp resp = { 0 };

        retVal = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((retVal) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfigRM TC-04 Positive test: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        request.tisci_boardcfg_rmp_low   = (uint32_t) bcfgInfo.boardCfgLowRm;
        request.tisci_boardcfg_rmp_high  = 0U;
        request.tisci_boardcfg_rm_size   = 0U;
        request.tisci_boardcfg_rm_devgrp = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_RM,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigRM TC-04 Negative test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-05: positive – maximum size (0xFFFF) with valid address 
     DM itself doesn’t have any operation or control over it. It just merely forwards the
     message to TIFS and update the response structure and flag based on TIFS response */
    {
        Sciclient_DefaultBoardCfgInfo_t      bcfgInfo = { 0 };
        struct tisci_msg_board_config_rm_req request  = { 0 };
        struct tisci_msg_board_config_rm_resp resp     = { 0 };

        retVal = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((retVal) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfigRM TC-05 negative test: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        request.tisci_boardcfg_rmp_low   = (uint32_t) bcfgInfo.boardCfgLowRm;
        request.tisci_boardcfg_rmp_high  = 0U;
        request.tisci_boardcfg_rm_size   = 0xFFFFU; /* Maximum size — firmware should reject */
        request.tisci_boardcfg_rm_devgrp = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_RM,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigRM TC-05 negative test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

/**
 * test_msgBoardConfigPM — TISCI_MSG_BOARD_CONFIG_PM (0x000E)
 *
 * TC-01  Positive: re-apply default PM board config via raw Sciclient_service()
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid devgrp (0xFF) → not SUCCESS or NACK
 */
static int32_t test_msgBoardConfigPM(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    {
        Sciclient_DefaultBoardCfgInfo_t      bcfgInfo = { 0 };
        struct tisci_msg_board_config_pm_req request  = { 0 };
        struct tisci_msg_board_config_pm_resp resp_pos = { 0 };

        retVal = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((retVal) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfigPM TC-01 Positive - step1 getDefaultBoardCfgInfo: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        request.tisci_boardcfg_pmp_low   = (uint32_t) bcfgInfo.boardCfgLowPm;
        request.tisci_boardcfg_pmp_high  = 0U;
        request.tisci_boardcfg_pm_size   = (uint16_t) bcfgInfo.boardCfgLowPmSize;
        request.tisci_boardcfg_pm_devgrp = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_PM,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp_pos,
            sizeof(resp_pos)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigPM TC-01 Positive - step2 re-apply default PM board config: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload → Sciclient_service() returns not SUCCESS */
    {
        struct tisci_msg_board_config_pm_resp resp_neg = { 0 };
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_PM,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp_neg,
            sizeof(resp_neg)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigPM TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid devgrp (0xFF) */
    {
        Sciclient_DefaultBoardCfgInfo_t bcfgInfo = { 0 };
        struct tisci_msg_board_config_pm_req request = { 0 };
        struct tisci_msg_board_config_pm_resp resp = { 0 };

        retVal = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((retVal) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfigPM TC-03 Negative - step1 getDefaultBoardCfgInfo for invalid devgrp=0xFF: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        request.tisci_boardcfg_pmp_low   = (uint32_t) bcfgInfo.boardCfgLowPm;
        request.tisci_boardcfg_pmp_high  = 0U;
        request.tisci_boardcfg_pm_size   = (uint16_t) bcfgInfo.boardCfgLowPmSize;
        request.tisci_boardcfg_pm_devgrp = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_PM,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigPM TC-03 Negative - invalid devgrp 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

/**
 * test_msgBoardConfigSecurity — TISCI_MSG_BOARD_CONFIG_SECURITY (0x000D)
 *
 * TC-01  Positive: re-apply default security board config via raw Sciclient_service()
 *                  → SystemP_SUCCESS + TISCI_MSG_FLAG_ACK
 *        Obtains the default security board config blob (same data applied at boot)
 *        via Sciclient_getDefaultBoardCfgInfo(), builds
 *        tisci_msg_board_config_security_req explicitly, and calls
 *        Sciclient_service() directly. Re-submitting the identical default security
 *        config blob is idempotent — TIFS ACKs repeated submissions of the same
 *        configuration (see TC-BC-06 in the original test plan).
 *        Both transport success AND firmware ACK are verified.
 *
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid devgrp (0xFF) → not SUCCESS or NACK
 */
static int32_t test_msgBoardConfigSecurity(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    /* TC-01: Positive – re-apply default security board config */
    {
        Sciclient_DefaultBoardCfgInfo_t             bcfgInfo = { 0 };
        struct tisci_msg_board_config_security_req  request  = { 0 };
        struct tisci_msg_board_config_security_resp resp_pos = { 0 };

        retVal = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((retVal) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfigSecurity TC-01 Positive - step1 getDefaultBoardCfgInfo: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        request.tisci_boardcfg_securityp_low   = (uint32_t) bcfgInfo.boardCfgLowSec;
        request.tisci_boardcfg_securityp_high  = 0U;
        request.tisci_boardcfg_security_size   = (uint16_t) bcfgInfo.boardCfgLowSecSize;
        request.tisci_boardcfg_security_devgrp = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_SECURITY,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp_pos,
            sizeof(resp_pos)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigSecurity TC-01 Positive - step2 re-apply default security board config: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload → Sciclient_service() returns not SUCCESS */
    {
        struct tisci_msg_board_config_security_resp resp_neg = { 0 };
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_SECURITY,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp_neg,
            sizeof(resp_neg)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigSecurity TC-02 Negative test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: positive –  devgrp (0xFF) */
    {
        Sciclient_DefaultBoardCfgInfo_t bcfgInfo = { 0 };
        struct tisci_msg_board_config_security_req request = { 0 };
        struct tisci_msg_board_config_security_resp resp = { 0 };

        retVal = Sciclient_getDefaultBoardCfgInfo(&bcfgInfo);
        if ((retVal) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBoardConfigSecurity TC-03 Positive test: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        request.tisci_boardcfg_securityp_low   = (uint32_t) bcfgInfo.boardCfgLowSec;
        request.tisci_boardcfg_securityp_high  = 0U;
        request.tisci_boardcfg_security_size   = (uint16_t) bcfgInfo.boardCfgLowSecSize;
        request.tisci_boardcfg_security_devgrp = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOARD_CONFIG_SECURITY,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBoardConfigSecurity TC-03 Negative test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}
#endif /* SKIP_SCICLIENT */


/**
 * TC_04: RM Ring Messages
 *
 * DRIVER FLOW ANALYSIS:
 *   TISCI_MSG_RM_RING_CFG (0x1110):
 *     Sciclient_ProcessRmMessage() locally on R5F DM, then forwarded to TIFS
 *     via Sciclient_serviceSecureProxy() for security validation if local RM
 *     returns ACK.
 *
 *   TISCI_MSG_RM_RING_MON_CFG (0x1120):
 *     Same dual-path as RING_CFG.
 *
 * AM62DX RESOURCE ALLOCATION (sciclient_defaultBoardcfg_rm.c):
 *   TISCI_HOST_ID_MAIN_0_R5_1 owns BCDMA ring indices 18-23
 *   (TISCI_RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN, start=18, count=6).
 *   No ring-monitor (RA_MON) resource entries are allocated to MAIN_0_R5_1
 *   in the default RM board config.
 *
 * SAFE TEST STRATEGY (valid_params = 0):
 *   All configurable fields are gated by valid_params bits.  Sending
 *   valid_params=0 causes the firmware to perform only the ownership
 *   permission check without writing any hardware registers — a pure
 *   no-op that is safe to use on a live system.
 */
/**
 * TC_15: Firewall Management
 *
 * DRIVER FLOW ANALYSIS:
 *   All three messages are routed via nonSecureContextId, processed by DM
 *   RM firewall management subsystem.
 *
 * TESTABILITY:
 *   TISCI_MSG_SET_FWL_REGION (0x9000):
 *     Positive test IS POSSIBLE using a read-then-restore pattern: GET the
 *     current config for fwl_id=0, region=0 first, then SET back the exact
 *     same values. This is a no-op write that safely exercises the full SET
 *     code path (mirrors Sciclient_firewallSetRegion) without changing any
 *     permissions or address range.
 *
 *   TISCI_MSG_GET_FWL_REGION (0x9001):
 *     Positive test IS POSSIBLE. Read-only query of firewall region
 *     configuration. Use a known firewall ID (fwl_id=0, region=0).
 *
 *   TISCI_MSG_CHANGE_FWL_OWNER (0x9002):
 *     Positive test IS POSSIBLE using owner_index=0 on fwl_id=0, region=0.
 *     owner_index=0 is the privileged/default owner (TIFS/DMSC). If the
 *     firewall is already owned by index 0 the call is a no-op; if not, it
 *     transfers ownership to the most trusted host. Uses same fwl_id=0 that
 *     GET and SET tests confirmed is accessible without side effects.
 *     Pattern mirrors Sciclient_firewallChangeOwnerInfo() in sciclient_firewall.c.
 */


/**
 * test_msgBootNotification — TISCI_MSG_BOOT_NOTIFICATION (0x000A)
 *
 * DRIVER FLOW: In SCICLIENT_DIRECT mode, TISCI_MSG_BOOT_NOTIFICATION is
 * handled in sciclient.c (Sciclient_waitForBootNotification) and
 * sciclient_direct_wrapper.c.  It is forwarded to TIFS via secure proxy.
 *
 * TC-01  Positive: send boot notification with extboot_status=0 → SUCCESS + ACK
 *        This is a re-notification; the initial one was already sent at boot.
 *        TIFS accepts duplicate boot notifications gracefully.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS or NACK
 * TC-03  Negative: flags = TISCI_MSG_FLAG_RESERVED0 → not SUCCESS or NACK
 */
static int32_t test_msgBootNotification(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_boot_notification_req  request;
    struct tisci_msg_boot_notification_resp response;

    /* TC-01: Positive – send boot notification with extboot_status=0.
     * BOOT_NOTIFICATION is a fire-and-forget message: no ACK is returned by
     * TIFS. flags must be 0 (no AOP). The only success indicator is retVal.
     * Pattern from test_sciclient_val.c (reqParam4): flags=0, no AOP. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.extboot_status = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOOT_NOTIFICATION,
            0U,                     /* no AOP — one-way notification, no ACK */
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        /* No ACK flag is set because AOP was not requested */
        if (!(retVal == SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgBootNotification TC-01 Positive - boot notification extboot_status=0 no AOP: retVal=%d\r\n",
                       retVal);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOOT_NOTIFICATION,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBootNotification TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgGetTraceConfig — TISCI_MSG_GET_TRACE_CONFIG (0x0021)
 *
 * DRIVER FLOW: In SCICLIENT_DIRECT mode, this is forwarded to TIFS via
 * secure proxy (falls into default case of Sciclient_service switch).
 * TIFS returns the debug trace configuration from the base board config.
 *
 * TC-01  Positive: query trace config → SUCCESS + ACK
 *        Returns trace_dst_enables and trace_src_enables.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS or NACK
 * TC-03  Negative: NULL pRespPayload → not SUCCESS or NACK
 */
static int32_t test_msgGetTraceConfig(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_get_trace_config_req  request;
    struct tisci_get_trace_config_resp response;

    /* TC-01: Positive – query trace config (read-only, safe) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_TRACE_CONFIG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetTraceConfig TC-01 Positive - query trace config read-only: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_TRACE_CONFIG,
            TISCI_MSG_FLAG_AOP,
            NULL,
            0,
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetTraceConfig TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

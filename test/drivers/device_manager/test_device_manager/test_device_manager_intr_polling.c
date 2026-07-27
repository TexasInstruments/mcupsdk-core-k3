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

#include <unity.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include "test_device_manager_intr_polling.h"

/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

/**
 * Helper: wraps a single Sciclient_service call, checks ACK, and logs on
 * failure.  Returns 1 if the call failed (can be added to failCount directly).
 */
static int32_t testDM_sendAndCheck(const char *testName,
                                    const char *msgLabel,
                                    uint32_t    msgType,
                                    void       *reqBuf,
                                    uint32_t    reqSize,
                                    void       *respBuf,
                                    uint32_t    respSize)
{
    const Sciclient_ReqPrm_t reqPrm =
    {
        msgType,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) reqBuf,
        reqSize,
        SystemP_WAIT_FOREVER
    };
    Sciclient_RespPrm_t respPrm =
    {
        0,
        (uint8_t *) respBuf,
        respSize
    };
    int32_t retVal = Sciclient_service(&reqPrm, &respPrm);
    if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
    {
        DebugP_log("FAIL: %s (positive) %s: retVal=%d expected=%d flags=0x%x expected=0x%x\r\n",
                   testName, msgLabel, retVal, SystemP_SUCCESS, respPrm.flags, TISCI_MSG_FLAG_ACK);
        return 1;
    }
    return 0;
}

static int32_t testDM_validateMessagesSequence(const char *testName)
{
    int32_t failCount = 0;

    /* 1. TISCI_MSG_VERSION (0x0001) */
    {
        struct tisci_msg_version_req  request;
        struct tisci_msg_version_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        failCount += testDM_sendAndCheck(testName, "msg 1 TISCI_MSG_VERSION(0x0001)",
                                         TISCI_MSG_VERSION,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

    /* 2. TISCI_MSG_GET_CLOCK (0x0101) */
    {
        struct tisci_msg_get_clock_req  request;
        struct tisci_msg_get_clock_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.device = TEST_DEVICE_ID;
        request.clk    = (uint8_t) TEST_DEVICE_CLK_ID;
        failCount += testDM_sendAndCheck(testName, "msg 2 TISCI_MSG_GET_CLOCK(0x0101)",
                                         TISCI_MSG_GET_CLOCK,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

    /* 3. TISCI_MSG_GET_FREQ (0x010C) */
    {
        struct tisci_msg_get_freq_req  request;
        struct tisci_msg_get_freq_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.device = TEST_DEVICE_ID;
        request.clk    = (uint8_t) TEST_DEVICE_CLK_ID;
        failCount += testDM_sendAndCheck(testName, "msg 3 TISCI_MSG_GET_FREQ(0x010C)",
                                         TISCI_MSG_GET_FREQ,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

    /* 4. TISCI_MSG_GET_DEVICE (0x0201) */
    {
        struct tisci_msg_get_device_req  request;
        struct tisci_msg_get_device_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.id = TEST_DEVICE_ID;
        failCount += testDM_sendAndCheck(testName, "msg 4 TISCI_MSG_GET_DEVICE(0x0201)",
                                         TISCI_MSG_GET_DEVICE,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

    /* 5. TISCI_MSG_RM_PSIL_READ (0x1282) */
    {
        struct tisci_msg_rm_psil_read_req  request;
        struct tisci_msg_rm_psil_read_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.valid_params = 0U;
        request.nav_id       = (uint16_t) TEST_RM_PSIL_NAV_ID;
        request.thread       = (uint16_t) TEST_RM_PSIL_SRC_THREAD;
        request.taddr        = (uint16_t) TEST_RM_PSIL_TADDR;
        failCount += testDM_sendAndCheck(testName, "msg 5 TISCI_MSG_RM_PSIL_READ(0x1282)",
                                         TISCI_MSG_RM_PSIL_READ,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

    /* 6. TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT (0x030B) */
#ifdef CONFIG_LPM_DM    /* Low power mode handling */
    {
        struct tisci_msg_lpm_get_device_constraint_req  request;
        struct tisci_msg_lpm_get_device_constraint_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.id = TEST_DEVICE_ID;
        failCount += testDM_sendAndCheck(testName, "msg 6 TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT(0x030B)",
                                         TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }
#endif

        /* On SoCs where TEST_DM_OTP_WKUP_HOST_RESTRICTED is defined (see the
         * SoC-specific test_device_manager_val.h), the OTP write_host_id in
         * the security boardcfg does not include the WKUP R5F host that the
         * DM runs on, so TIFS NACKs OTP reads.  Verify transport success only. */
#if defined(TEST_DM_OTP_WKUP_HOST)
    /* 7. TISCI_MSG_GET_OTP_ROW_LOCK_STATUS (0x9026) */
    {
        struct tisci_msg_get_otp_row_lock_status_req  request;
        struct tisci_msg_get_otp_row_lock_status_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.row_idx = 0U;
        failCount += testDM_sendAndCheck(testName, "msg 7 TISCI_MSG_GET_OTP_ROW_LOCK_STATUS(0x9026)",
                                         TISCI_MSG_GET_OTP_ROW_LOCK_STATUS,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

#endif

    /* 8. TISCI_MSG_SA2UL_SET_DKEK + TISCI_MSG_SA2UL_GET_DKEK (0x9028/0x9029) */
    {
        struct tisci_msg_sa2ul_set_dkek_req  setReq;
        struct tisci_msg_sa2ul_set_dkek_resp setResp;
        memset(&setReq,  0, sizeof(setReq));
        memset(&setResp, 0, sizeof(setResp));
        setReq.sa2ul_instance  = 0U;
        setReq.kdf_label_len   = 4U;
        setReq.kdf_context_len = 3U;
        memcpy(&setReq.kdf_label_and_context[0], "TEST", 4);
        memcpy(&setReq.kdf_label_and_context[4], "CTX", 3);
        failCount += testDM_sendAndCheck(testName, "msg 8a TISCI_MSG_SA2UL_SET_DKEK(0x9028)",
                                         TISCI_MSG_SA2UL_SET_DKEK,
                                         &setReq, sizeof(setReq),
                                         &setResp, sizeof(setResp));

        struct tisci_msg_sa2ul_get_dkek_req  request;
        struct tisci_msg_sa2ul_get_dkek_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance  = 0U;
        request.kdf_label_len   = 4U;
        request.kdf_context_len = 3U;
        memcpy(&request.kdf_label_and_context[0], "TEST", 4);
        memcpy(&request.kdf_label_and_context[4], "CTX", 3);
        failCount += testDM_sendAndCheck(testName, "msg 8b TISCI_MSG_SA2UL_GET_DKEK(0x9029)",
                                         TISCI_MSG_SA2UL_GET_DKEK,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

    /* 10. TISCI_MSG_RM_GET_RESOURCE_RANGE (0x1500) */
    {
        struct tisci_msg_rm_get_resource_range_req  request;
        struct tisci_msg_rm_get_resource_range_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.type           = TEST_RM_NAV_INTAGGR_DEV_ID;
        request.subtype        = TISCI_RESASG_SUBTYPE_IA_VINT;
        request.secondary_host = TISCI_HOST_ID_ALL;
        failCount += testDM_sendAndCheck(testName, "msg 10 TISCI_MSG_RM_GET_RESOURCE_RANGE(0x1500)",
                                         TISCI_MSG_RM_GET_RESOURCE_RANGE,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

    /* 11. TISCI_MSG_GET_FWL_REGION (0x9001) */
#ifndef DM_TEST_FWL_INTR_POLL_DISABLE
    {
        struct tisci_msg_fwl_get_firewall_region_req  request;
        struct tisci_msg_fwl_get_firewall_region_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.fwl_id            = 7U;
        request.region            = 0U;
        request.n_permission_regs = FWL_MAX_PRIVID_SLOTS;
        failCount += testDM_sendAndCheck(testName, "msg 11 TISCI_MSG_GET_FWL_REGION(0x9001)",
                                         TISCI_MSG_GET_FWL_REGION,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }
#endif /* DM_TEST_FWL_INTR_POLL_DISABLE */

    /* 12. TISCI_MSG_PROC_GET_STATUS (0xC400) */
    {
        struct tisci_msg_proc_get_status_req  request;
        struct tisci_msg_proc_get_status_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = SCICLIENT_PROC_ID_R5FSS0_CORE0;
        failCount += testDM_sendAndCheck(testName, "msg 12 TISCI_MSG_PROC_GET_STATUS(0xC400)",
                                         TISCI_MSG_PROC_GET_STATUS,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

    return failCount;
}

/* --------------------------------------------------------------------------
 * Switches Sciclient from POLLED to INTERRUPT mode, validates 12 TISCI
 * message types in interrupt mode, then restores POLLED mode.
 * -------------------------------------------------------------------------- */
void testDM_interruptModeValidation(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    Sciclient_updateOperModeToPolled();
    retVal = Sciclient_updateOperModeToInterrupt();
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testDM_interruptModeValidation (positive) mode switch to INTERRUPT: retVal=%d expected=0x%x\r\n",
                   retVal, SystemP_SUCCESS);
        failCount++;
    }

    failCount += testDM_validateMessagesSequence("testDM_interruptModeValidation");

    Sciclient_updateOperModeToPolled();

    TEST_ASSERT_EQUAL_INT32(0, failCount);
}

/* --------------------------------------------------------------------------
 * Switches Sciclient to POLLED mode and validates the same 12 TISCI
 * message types in polled mode.
 * -------------------------------------------------------------------------- */
void testDM_pollModeValidation(void *args)
{
    int32_t failCount = 0;

    Sciclient_updateOperModeToPolled();
    failCount = testDM_validateMessagesSequence("testDM_pollModeValidation");
    TEST_ASSERT_EQUAL_INT32(0, failCount);
}

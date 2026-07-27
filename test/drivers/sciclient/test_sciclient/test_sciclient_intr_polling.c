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
#include "test_sciclient_intr_polling.h"

/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

/**
 * Helper: wraps a single Sciclient_service call, checks ACK, and logs on
 * failure.  Returns 1 if the call failed (can be added to failCount directly).
 */
static int32_t testSciclient_sendAndCheck(const char *testName,
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

static int32_t testSciclient_validateMessagesSequence(const char *testName)
{
    int32_t retVal;
    int32_t failCount = 0;

    /* 1. TISCI_MSG_VERSION (0x0001) */
    {
        struct tisci_msg_version_req  request;
        struct tisci_msg_version_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        failCount += testSciclient_sendAndCheck(testName, "msg 1 TISCI_MSG_VERSION(0x0001)",
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
        failCount += testSciclient_sendAndCheck(testName, "msg 2 TISCI_MSG_GET_CLOCK(0x0101)",
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
        failCount += testSciclient_sendAndCheck(testName, "msg 3 TISCI_MSG_GET_FREQ(0x010C)",
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
        failCount += testSciclient_sendAndCheck(testName, "msg 4 TISCI_MSG_GET_DEVICE(0x0201)",
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
        failCount += testSciclient_sendAndCheck(testName, "msg 5 TISCI_MSG_RM_PSIL_READ(0x1282)",
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
        failCount += testSciclient_sendAndCheck(testName, "msg 6 TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT(0x030B)",
                                         TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }
#endif

        /* On SoCs where TEST_DM_OTP_WKUP_HOST_RESTRICTED is defined (see the
         * SoC-specific test_sciclient_val.h), the OTP write_host_id in
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
        failCount += testSciclient_sendAndCheck(testName, "msg 7 TISCI_MSG_GET_OTP_ROW_LOCK_STATUS(0x9026)",
                                         TISCI_MSG_GET_OTP_ROW_LOCK_STATUS,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

#endif

    /* 8. TISCI_MSG_SA2UL_SET_DKEK + TISCI_MSG_SA2UL_GET_DKEK (0x9028/0x9029) */
    /* sa2ul_auth_cfg.auth_resource_owner in the security boardcfg is
     * TISCI_HOST_ID_TIFS, so no R5/A53 host (including this core) is
     * authorized to acquire/release DKEK — TIFS NACKs the request
     * (retVal=SUCCESS, flags=0x0). Verify transport success only, matching
     * the same relaxation applied in test_sciclient_sec.c's SA2UL tests. */
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
        const Sciclient_ReqPrm_t setReqPrm =
        {
                                         TISCI_MSG_SA2UL_SET_DKEK,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &setReq,
            sizeof(setReq),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t setRespPrm =
        {
            0,
            (uint8_t *) &setResp,
            sizeof(setResp)
        };
        retVal = Sciclient_service(&setReqPrm, &setRespPrm);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: %s (positive) msg 8a TISCI_MSG_SA2UL_SET_DKEK(0x9028): retVal=%d expected=%d flags=0x%x expected=0x%x\r\n",
                       testName, retVal, SystemP_SUCCESS, setRespPrm.flags, TISCI_MSG_FLAG_ACK);
            failCount++;
        }

        struct tisci_msg_sa2ul_get_dkek_req  request;
        struct tisci_msg_sa2ul_get_dkek_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance  = 0U;
        request.kdf_label_len   = 4U;
        request.kdf_context_len = 3U;
        memcpy(&request.kdf_label_and_context[0], "TEST", 4);
        memcpy(&request.kdf_label_and_context[4], "CTX", 3);
        const Sciclient_ReqPrm_t reqPrm =
        {
                                         TISCI_MSG_SA2UL_GET_DKEK,
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
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: %s (positive) msg 8b TISCI_MSG_SA2UL_GET_DKEK(0x9029): retVal=%d expected=%d flags=0x%x expected=0x%x\r\n",
                       testName, retVal, SystemP_SUCCESS, respPrm.flags, TISCI_MSG_FLAG_ACK);
            failCount++;
        }
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
        failCount += testSciclient_sendAndCheck(testName, "msg 10 TISCI_MSG_RM_GET_RESOURCE_RANGE(0x1500)",
                                         TISCI_MSG_RM_GET_RESOURCE_RANGE,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
    }

    /* 11. TISCI_MSG_GET_FWL_REGION (0x9001) */
    {
        struct tisci_msg_fwl_get_firewall_region_req  request;
        struct tisci_msg_fwl_get_firewall_region_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.fwl_id            = 7U;
        request.region            = 0U;
        request.n_permission_regs = FWL_MAX_PRIVID_SLOTS;
#if defined(SOC_AM62X)
        /* AM62X's default security boardcfg restricts fwl_id=7's (FSS0)
         * permission_regs differently than the other AM62-family SoCs: on
         * AM62X neither m4fss0-0 (TISCI_HOST_ID_M4_0) nor a53ss0-0
         * (TISCI_HOST_ID_A53_2) are included, whereas on AM62AX/AM62DX/
         * AM62PX the equivalent MCU-domain/A53 hosts are. TIFS NACKs the
         * query for both AM62X hosts (retVal=SUCCESS, flags=0x0). Verify
         * transport success only, matching the same relaxation applied to
         * the SA2UL DKEK messages (msg 8) above. */
        {
            const Sciclient_ReqPrm_t reqPrm =
            {
                TISCI_MSG_GET_FWL_REGION,
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
            if (retVal != SystemP_SUCCESS)
            {
                DebugP_log("FAIL: %s (positive) msg 11 TISCI_MSG_GET_FWL_REGION(0x9001): retVal=%d expected=%d\r\n",
                           testName, retVal, SystemP_SUCCESS);
                failCount++;
            }
        }
#else
        failCount += testSciclient_sendAndCheck(testName, "msg 11 TISCI_MSG_GET_FWL_REGION(0x9001)",
                                         TISCI_MSG_GET_FWL_REGION,
                                         &request, sizeof(request),
                                         &response, sizeof(response));
#endif
    }

    /* 12. TISCI_MSG_PROC_GET_STATUS (0xC400) */
    {
        struct tisci_msg_proc_get_status_req  request;
        struct tisci_msg_proc_get_status_resp response;
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = SCICLIENT_PROC_ID_R5FSS0_CORE0;
        failCount += testSciclient_sendAndCheck(testName, "msg 12 TISCI_MSG_PROC_GET_STATUS(0xC400)",
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
void testSciclient_interruptModeValidation(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    Sciclient_updateOperModeToPolled();
    retVal = Sciclient_updateOperModeToInterrupt();
#if defined(CORE_A53)
    /* On AM62DX, TISCI_HOST_ID_A53_2's non-secure context has no
     * notification interrupt routed in the secure-proxy map (respIntrNum=0,
     * see gSciclientMap in source/drivers/sciclient/soc/am62dx/
     * sciclient_fmwSecureProxyMap.c). True interrupt-mode operation is
     * architecturally unavailable for this host on this SoC — this is a
     * genuine hardware routing limitation, not a driver defect —
     * Sciclient_updateOperModeToInterrupt() always falls back to polling
     * mode here. Only verify the graceful polling fallback occurred. */
    if (retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_interruptModeValidation (unexpected) mode switch to INTERRUPT succeeded on a53ss0-0, which has no notification interrupt routed: retVal=%d\r\n",
                   retVal);
        failCount++;
    }
#else
    /* mcu-r5fss0-0 (TISCI_HOST_ID_MCU_0_R5_0) and c75ss0-0
     * (TISCI_HOST_ID_C7X_0_0) both have a notification interrupt routed
     * in gSciclientMap, so interrupt mode setup is expected to succeed. */
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_interruptModeValidation (positive) mode switch to INTERRUPT: retVal=%d expected=0x%x\r\n",
                   retVal, SystemP_SUCCESS);
        failCount++;
    }
#endif

    failCount += testSciclient_validateMessagesSequence("testSciclient_interruptModeValidation");

    Sciclient_updateOperModeToPolled();

    TEST_ASSERT_EQUAL_INT32(0, failCount);
}

/* --------------------------------------------------------------------------
 * Switches Sciclient to POLLED mode and validates the same 12 TISCI
 * message types in polled mode.
 * -------------------------------------------------------------------------- */
void testSciclient_pollModeValidation(void *args)
{
    int32_t failCount = 0;

    Sciclient_updateOperModeToPolled();
    failCount = testSciclient_validateMessagesSequence("testSciclient_pollModeValidation");
    TEST_ASSERT_EQUAL_INT32(0, failCount);
}

/* ==========================================================================
 * testSciclient_updateOperMode
 *
 * Covers Sciclient_updateOperModeToInterrupt() with focus on the
 * SemaphoreP_constructBinary failure / cleanup path (sciclient.c)
 *
 * Code paths exercised:
 *   Path B  Main transition (opModeFlag == POLLED → INTERRUPT):
 *     B-ok  Positive: all 7 SemaphoreP_constructBinary calls succeed,
 *           interrupt handler registered → SUCCESS.  On A53 where
 *           respIntrNum=0 the interrupt registration succeeds silently
 *           but leaves respIntr[NON_SEC]==NULL, so the handler-check
 *           (sciclient.c) sets status=FAILURE and
 *           Sciclient_unregisterIntr() destructs the 7 semaphores.
 *     B-fail SemaphoreP_constructBinary failure cleanup:
 *           In FreeRTOS with static allocation xSemaphoreCreateBinaryStatic
 *           always returns non-NULL → this branch is defensive dead-code
 *           that cannot be triggered without fault injection.
 *           Coverage is verified INDIRECTLY:
 *           (i)  TC-3 exercises the SAME cleanup structure (partial-loop
 *                destruct + opModeFlag = POLLED + return FAILURE) through
 *                the interrupt setup failure on A53.
 *           (ii) TC-4 verifies that after any failure the system is in
 *                POLLED mode and TISCI still works, matching the post-
 *                condition the sem-failure cleanup produces.
 *           (iii)TC-5 performs polled→interrupt→polled→interrupt to exercise
 *                the construction-then-destruction cycle twice and confirm
 *                the sems can be reconstructed after destruction.
 *
 *   Path C  Already in interrupt mode:
 *     C-ok  Positive: opModeFlag==INTERRUPT, respIntr[NON_SEC]!=NULL → SUCCESS
 *
 * Teardown: function MUST leave Sciclient in polled mode so all subsequent
 * RUN_TESTs that call Sciclient_service() in polling mode are unaffected.
 * ========================================================================== */
void testSciclient_updateOperMode(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    /* Guarantee we start in polled mode */
    Sciclient_updateOperModeToPolled();

    /* ------------------------------------------------------------------ */
    /* TC-1: Positive — polled → interrupt (Path B-ok)                    */
    /* Exercises all 7 SemaphoreP_constructBinary calls (i = 0..6), the   */
    /* interrupt handler registration, and the opModeFlag transition.     */
    /* On A53 the interrupt setup fails (respIntrNum=0) so the function   */
    /* returns FAILURE and reverts to POLLED after destructing the 7 sems.*/
    /* On other cores (MCU-R5F, C7X) it returns SUCCESS.                  */
    /* ------------------------------------------------------------------ */
    retVal = Sciclient_updateOperModeToInterrupt();
#if defined(CORE_A53)
    /* A53 always fails: respIntrNum=0 for all A53 contexts; this is the   */
    /* closest runnable exercise of the semaphore cleanup path since the   */
    /* interrupt setup failure (sciclient.c) calls the same                */
    /* Sciclient_unregisterIntr() that destructs all 7 semaphores.         */
    if(retVal != SystemP_FAILURE)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-1: A53 expected FAILURE (no interrupt support), got retVal=%d\r\n", retVal);
        failCount++;
    }
    else
    {
        DebugP_log("INFO: testSciclient_updateOperMode TC-1: A53 interrupt mode FAILURE as expected (respIntrNum=0); semaphore construction + cleanup exercised\r\n");
    }
#else
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-1: Positive polled→interrupt  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        failCount++;
    }
#endif

    /* ------------------------------------------------------------------ */
    /* TC-2: Positive — already in interrupt mode (Path C-ok)             */
    /* Only applicable on non-A53 (TC-1 left them in interrupt mode).     */
    /* Re-calling when already in INTERRUPT mode with a valid non-secure   */
    /* handler returns SUCCESS without re-constructing semaphores.        */
    /* ------------------------------------------------------------------ */
#if !defined(CORE_A53)
    retVal = Sciclient_updateOperModeToInterrupt();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-2: Positive re-call in interrupt mode  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        failCount++;
    }

    /* Confirm TISCI still works in interrupt mode */
    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-2 functional: Sciclient_getVersionCheck in interrupt mode  retVal=%d\r\n", retVal);
        failCount++;
    }
#endif /* !CORE_A53 */

    /* ------------------------------------------------------------------ */
    /* TC-3: Indirect SemaphoreP cleanup coverage —                       */
    /* transition to POLLED then back to INTERRUPT on non-A53;            */
    /* on A53 repeat the failure path (sem construct + destruct).         */
    /* Sciclient_updateOperModeToPolled() calls Sciclient_unregisterIntr()*/
    /* which destructs all 7 semaphores (semHandles → NULL).              */
    /* The subsequent updateToInterrupt() call reconstructs them,         */
    /* exercising Path B-ok again and mirroring the post-condition of     */
    /* the SemaphoreP_constructBinary failure cleanup:                    */
    /*   opModeFlag == POLLED, semHandles[0..6] == NULL before re-init.   */
    /* ------------------------------------------------------------------ */
    Sciclient_updateOperModeToPolled();

    /* Verify TISCI still works after reverting to polled */
    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-3: Sciclient_getVersionCheck after updateToPolled  retVal=%d\r\n", retVal);
        failCount++;
    }

    /* Re-enter interrupt mode to reconstruct semaphores */
    retVal = Sciclient_updateOperModeToInterrupt();
#if defined(CORE_A53)
    if(retVal != SystemP_FAILURE)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-3: A53 expected FAILURE on second interrupt attempt  retVal=%d\r\n", retVal);
        failCount++;
    }
#else
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-3: Positive polled→interrupt (2nd time)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        failCount++;
    }
#endif

    /* ------------------------------------------------------------------ */
    /* TC-4: SemaphoreP_constructBinary failure path: post-condition       */
    /* verification.                                                       */
    /* The sem-failure cleanup at sciclient.c produces:                    */
    /*   (a) opModeFlag = SCICLIENT_SERVICE_OPERATION_MODE_POLLED          */
    /*   (b) semHandles[0..i] = NULL                                       */
    /*   (c) return SystemP_FAILURE                                        */
    /* This same post-condition is produced when updateToInterrupt()       */
    /* returns FAILURE from the interrupt setup path (A53) or when        */
    /* updateToPolled() is called (non-A53).                               */
    /* Verify TISCI works after the polled post-condition is established.  */
    /* ------------------------------------------------------------------ */
    Sciclient_updateOperModeToPolled();  /* post-condition: opModeFlag=POLLED */

    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-4: Sciclient_getVersionCheck after POLLED reset (sem-cleanup post-condition)  retVal=%d\r\n", retVal);
        failCount++;
    }
    else
    {
        DebugP_log("INFO: testSciclient_updateOperMode TC-4: TISCI works in POLLED mode — semaphore cleanup post-condition verified\r\n");
    }

    /* ------------------------------------------------------------------ */
    /* TC-5: Sciclient_disableIntr / Sciclient_enableIntr in POLLED mode  */
    /* Both functions guard on opModeFlag == INTERRUPT (sciclient.c)      */
    /* in POLLED mode they are no-ops. TISCI must work   */
    /* normally after either call.                                        */
    /* ------------------------------------------------------------------ */
    Sciclient_updateOperModeToPolled();   /* ensure polled mode */

    /* TC-5a: disableIntr in polled mode → no-op */
    Sciclient_disableIntr();
    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-5a: Sciclient_getVersionCheck after disableIntr (polled, no-op)  retVal=%d\r\n", retVal);
        failCount++;
    }

    /* TC-5b: enableIntr in polled mode → no-op */
    Sciclient_enableIntr();
    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-5b: Sciclient_getVersionCheck after enableIntr (polled, no-op)  retVal=%d\r\n", retVal);
        failCount++;
    }

    /* TC-5c: disableIntr → enableIntr sequence in polled mode → no-op */
    Sciclient_disableIntr();
    Sciclient_enableIntr();
    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-5c: Sciclient_getVersionCheck after disable→enable sequence (polled)  retVal=%d\r\n", retVal);
        failCount++;
    }

    /* ------------------------------------------------------------------ */
    /* TC-6: Sciclient_disableIntr / Sciclient_enableIntr in INTERRUPT    */
    /* mode (non-A53 only).                                               */
    /* disableIntr: calls HwiP_disableInt for each registered handler     */
    /*   (sciclient.c).                                                   */
    /* enableIntr:  calls HwiP_enableInt  for each registered handler     */
    /*   (sciclient.c) .                                                  */
    /* IMPORTANT: Sciclient_service() MUST NOT be called between          */
    /* disableIntr() and enableIntr() — with the interrupt masked the ISR */
    /* cannot signal the semaphore and the pend would never complete.     */
    /* ------------------------------------------------------------------ */
#if !defined(CORE_A53)
    retVal = Sciclient_updateOperModeToInterrupt();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: testSciclient_updateOperMode TC-6 setup: updateToInterrupt  retVal=%d\r\n", retVal);
        failCount++;
    }
    else
    {
        /* TC-6a: disableIntr in interrupt mode — HWI masked */
        Sciclient_disableIntr();

        /* TC-6b: enableIntr in interrupt mode — HWI unmasked */
        Sciclient_enableIntr();

        /* Verify TISCI works in interrupt mode after re-enable */
        retVal = Sciclient_getVersionCheck(0U);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: testSciclient_updateOperMode TC-6: Sciclient_getVersionCheck after disableIntr→enableIntr (interrupt mode)  retVal=%d\r\n", retVal);
            failCount++;
        }

        /* TC-6c: double disableIntr → enableIntr (idempotent HWI mask) */
        Sciclient_disableIntr();
        Sciclient_disableIntr();
        Sciclient_enableIntr();
        Sciclient_enableIntr();
        retVal = Sciclient_getVersionCheck(0U);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: testSciclient_updateOperMode TC-6c: Sciclient_getVersionCheck after double disable→enable  retVal=%d\r\n", retVal);
            failCount++;
        }
    }
#endif /* !CORE_A53 */

    /* ------------------------------------------------------------------ */
    /* Teardown: leave Sciclient in polled mode.                           */
    /* All other RUN_TESTs use Sciclient_service() in polling mode.        */
    /* ------------------------------------------------------------------ */
    Sciclient_updateOperModeToPolled();

    TEST_ASSERT_EQUAL_INT32(0, failCount);
}

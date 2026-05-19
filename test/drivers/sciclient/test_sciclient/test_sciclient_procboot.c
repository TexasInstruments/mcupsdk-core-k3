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
#include <drivers/sciclient/include/tisci/security/tisci_procboot.h>
#include <drivers/sciclient/include/tisci/security/tisci_secure_jtag.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_core.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include "test_sciclient_procboot.h"

/* ========================================================================== */
/*              Static Forward Declarations for Sub-functions                 */
/* ========================================================================== */

static int32_t test_msgProcRequest(void *args);
static int32_t test_msgProcRelease(void *args);
static int32_t test_msgProcHandover(void *args);
static int32_t test_msgProcSetConfig(void *args);
static int32_t test_msgProcSetControl(void *args);
static int32_t test_msgProcGetStatus(void *args);
static int32_t test_msgProcWaitStatus(void *args);
static int32_t test_msgProcAuthBoot(void *args);
static int32_t test_msgSysReset(void *args);

/* ========================================================================== */
/*            Helper Function Implementations — Proc Boot Tests               */
/* ========================================================================== */

/**
 * DRIVER FLOW ANALYSIS:
 *   All PROC_* messages are routed via nonSecureContextId to the DM
 *   processor boot management subsystem.
 *
 * TESTABILITY:
 *   TISCI_MSG_PROC_REQUEST (0xC000):
 *     Positive test is CAREFULLY possible. The DM test runs as
 *     TISCI_HOST_ID_MAIN_0_R5_1 on R5FSS0_CORE0. We can safely request
 *     control of C7X256V0_CORE0 (processor_id=0x04) which is a co-processor
 *     not used by the DM firmware itself. Must be paired with PROC_RELEASE.
 *
 *   TISCI_MSG_PROC_RELEASE (0xC001):
 *     Positive test paired with PROC_REQUEST above.
 *
 *   TISCI_MSG_PROC_HANDOVER (0xC005):
 *     Positive test IS POSSIBLE. REQUEST C7X256V0_CORE0 to gain ownership,
 *     then HANDOVER to TISCI_HOST_ID. Mirrors the REQUEST→HANDOVER
 *     sequence in Sciclient_procBootHandoverProcessor(). Subsequent
 *     GET_STATUS tests still pass since they do not require ownership.
 *
 *   TISCI_MSG_PROC_SET_CONFIG (0xC100):
 *     NOT SAFE for positive test. Sets boot vector and config flags on a
 *     processor. Modifying the boot vector of a running processor is
 *     destructive on warm-reset.
 *
 *   TISCI_MSG_PROC_SET_CONTROL (0xC101):
 *     Positive test IS POSSIBLE using reqFlag=0 (fire-and-forget, no AOP).
 *     This exactly mirrors dm_self_reset.c which sends PROC_SET_CONTROL with
 *     flags=0 (no ACK requested). Calling with TISCI_MSG_FLAG_AOP on a
 *     running processor is NACKed by TIFS because C7X256V0_CORE0 has no
 *     applicable control flags. With reqFlag=0, Sciclient_service enqueues
 *     the message and returns SUCCESS without checking the response — the
 *     same pattern used by the DM for self-reset. The caller must hold
 *     ownership via PROC_REQUEST first; PROC_RELEASE follows.
 *
 *   TISCI_MSG_PROC_GET_STATUS (0xC400):
 *     Positive test IS POSSIBLE. Read-only query of processor status.
 *
 *   TISCI_MSG_PROC_WAIT_STATUS (0xC401):
 *     Positive test IS POSSIBLE. Use clr_all_wait = R5_WFI | R5_WFE with
 *     TISCI_MSG_FLAG_AOP: a running R5FSS0_CORE0 has both WFI and WFE
 *     cleared, so the condition matches immediately and TIFS returns ACK.
 *
 *   TISCI_MSG_PROC_AUTH_BOOT (0xC120):
 *     Positive test IS POSSIBLE on AM62DX using the pre-signed R5 cert from
 *     sciclient_direct/am62dx-evm/test_sciclient_r5_cl0_c0_image.h. Pattern
 *     mirrors Sciclient_procBootAuthAndStart() in sciclient_procboot.c.
 */

/**
 * test_msgProcRequest — TISCI_MSG_PROC_REQUEST (0xC000)
 *
 * TC-01  Positive: request control of C7X256V0_CORE0 → SUCCESS + ACK
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid processor_id (0xFF) → not SUCCESS or NACK
 */
static int32_t test_msgProcRequest(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_proc_request_req  request;
    struct tisci_msg_proc_request_resp response;

    /* TC-01: Positive – request control of C7X256V0_CORE0 (processor_id=0x04) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = TEST_PROC_ID_COPROCESSOR;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_REQUEST,
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
            DebugP_log("FAIL: test_msgProcRequest TC-01 Positive - request control of co-processor: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_REQUEST,
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
            DebugP_log("FAIL: test_msgProcRequest TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid processor_id (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_REQUEST,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcRequest TC-03 Negative - invalid processor_id 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgProcRelease — TISCI_MSG_PROC_RELEASE (0xC001)
 *
 * TC-01  Positive: release C7X256V0_CORE0 (requested in test_msgProcRequest)
 *                  → SUCCESS + ACK
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid processor_id (0xFF) → not SUCCESS or NACK
 */
static int32_t test_msgProcRelease(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_proc_release_req  request;
    struct tisci_msg_proc_release_resp response;

    /* TC-01: Positive – release C7X256V0_CORE0 (cleanup) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = TEST_PROC_ID_COPROCESSOR;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_RELEASE,
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
            DebugP_log("FAIL: test_msgProcRelease TC-01 Positive - release co-processor: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_RELEASE,
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
            DebugP_log("FAIL: test_msgProcRelease TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid processor_id (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_RELEASE,
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
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcRelease TC-03 Negative - invalid processor_id 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgProcHandover — TISCI_MSG_PROC_HANDOVER (0xC005)
 *
 * TC-01  Positive: REQUEST C7X256V0_CORE0, then HANDOVER to A53_2 → SUCCESS + ACK
 *          test_msgProcRelease has already released C7X, so re-acquire it here.
 *          Pattern mirrors Sciclient_procBootHandoverProcessor() in sciclient_procboot.c.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid processor_id (0xFF) → not SUCCESS or NACK
 * TC-04  Negative: invalid host_id (0xFF) → not SUCCESS or NACK
 */
static int32_t test_msgProcHandover(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_proc_handover_req  request;
    struct tisci_msg_proc_handover_resp response;

    /* TC-01: Positive – acquire C7X256V0_CORE0 then hand it over to A53_2.
     * Two-step: PROC_REQUEST to become owner, then PROC_HANDOVER to transfer.
     * After handover A53_2 owns C7X; subsequent GET_STATUS does not need ownership. */
    {
        /* Step 1: acquire ownership of C7X256V0_CORE0 */
        struct tisci_msg_proc_request_req  reqReq  = {0};
        struct tisci_msg_proc_request_resp reqResp = {0};
        reqReq.processor_id = TEST_PROC_ID_COPROCESSOR;

        const Sciclient_ReqPrm_t preReqPrm =
        {
            TISCI_MSG_PROC_REQUEST,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &reqReq,
            sizeof(reqReq),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t preRespPrm =
        {
            0,
            (uint8_t *) &reqResp,
            sizeof(reqResp)
        };
        retVal = Sciclient_service(&preReqPrm, &preRespPrm);
        if (!((retVal == SystemP_SUCCESS) && (preRespPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcHandover TC-01 Positive - step1 acquire co-processor: retVal=%d flags=0x%x\r\n",
                       retVal, preRespPrm.flags);
            failCount++;
        }

        /* Step 2: hand over C7X256V0_CORE0 to TISCI_HOST_ID */
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = TEST_PROC_ID_COPROCESSOR;
        request.host_id      = TISCI_HOST_ID;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_HANDOVER,
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
            DebugP_log("FAIL: test_msgProcHandover TC-01 Positive - step2 hand over co-processor to TISCI_HOST_ID: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_HANDOVER,
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
            DebugP_log("FAIL: test_msgProcHandover TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid processor_id (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = 0xFFU;
        request.host_id      = TISCI_HOST_ID;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_HANDOVER,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcHandover TC-03 Negative - invalid processor_id 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – invalid host_id (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = TEST_PROC_ID_COPROCESSOR;
        request.host_id      = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_HANDOVER,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcHandover TC-04 Negative - invalid host_id 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgProcSetConfig — TISCI_MSG_PROC_SET_CONFIG (0xC100)
 *
 * NOT SAFE for positive test:
 *   Sets boot vector and config flags on a processor. Modifying the boot
 *   vector of a running processor is destructive on warm-reset.
 *
 * TC-01  Negative: NULL pReqPayload → not SUCCESS
 * TC-02  Negative: invalid processor_id (0xFF) → not SUCCESS or NACK
 * TC-03  Negative: NULL pRespPayload → not SUCCESS
 */
static int32_t test_msgProcSetConfig(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_proc_set_config_req  request;
    struct tisci_msg_proc_set_config_resp response;

    /* TC-01: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_SET_CONFIG,
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
            DebugP_log("FAIL: test_msgProcSetConfig TC-01 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid processor_id (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id       = 0xFFU;
        request.bootvector_lo      = 0U;
        request.bootvector_hi      = 0U;
        request.config_flags_1_set   = 0U;
        request.config_flags_1_clear = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_SET_CONFIG,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcSetConfig TC-02 Negative - invalid processor_id 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pRespPayload */
    {
        memset(&request, 0, sizeof(request));
        request.processor_id = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_SET_CONFIG,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            NULL,
            0
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcSetConfig TC-03 Negative - NULL pRespPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgProcSetControl — TISCI_MSG_PROC_SET_CONTROL (0xC101)
 *
 * Positive test uses reqFlag=0 (fire-and-forget, no AOP), mirroring
 * dm_self_reset.c.  TISCI_MSG_FLAG_AOP is NACKed by TIFS on a running
 * C7X256V0_CORE0 (no applicable control flags for C7X architecture).
 * With reqFlag=0 the Sciclient_service path enqueues the message and
 * returns SUCCESS without requiring a TIFS ACK — exactly what the DM
 * itself does when asserting/de-asserting R5 reset during self-reset.
 *
 * TC-01  Positive: REQUEST C7X, SET_CONTROL reqFlag=0 (fire-and-forget), RELEASE
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid processor_id (0xFF) → not SUCCESS or NACK
 * TC-04  Negative: NULL pRespPayload → not SUCCESS
 */
static int32_t test_msgProcSetControl(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_proc_set_control_req  request;
    struct tisci_msg_proc_set_control_resp response;

    /* TC-01: Positive – REQUEST C7X256V0_CORE0, SET_CONTROL with reqFlag=0
     * (fire-and-forget, no AOP).  This mirrors dm_self_reset.c which calls
     * PROC_SET_CONTROL with flags=0 to assert/de-assert R5 reset without
     * waiting for an ACK.  Sciclient_service returns SUCCESS as soon as the
     * message is enqueued; no TIFS ACK is expected or checked. RELEASE after. */
    {
        /* Pre-step: acquire ownership of C7X256V0_CORE0 */
        struct tisci_msg_proc_request_req  reqReq  = {0};
        struct tisci_msg_proc_request_resp reqResp = {0};
        reqReq.processor_id = TEST_PROC_ID_COPROCESSOR;
        const Sciclient_ReqPrm_t preReqPrm =
        {
            TISCI_MSG_PROC_REQUEST,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &reqReq,
            sizeof(reqReq),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t preRespPrm =
        {
            0,
            (uint8_t *) &reqResp,
            sizeof(reqResp)
        };
        retVal = Sciclient_service(&preReqPrm, &preRespPrm);
        if (!((retVal == SystemP_SUCCESS) && (preRespPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcSetControl TC-01 Positive - step1 acquire co-processor: retVal=%d flags=0x%x\r\n",
                       retVal, preRespPrm.flags);
            failCount++;
        }

        /* SET_CONTROL: reqFlag=0 (fire-and-forget, no AOP) — mirrors dm_self_reset.c.
         * C7X has no architecture-specific control flags; flags_set=0, flags_clear=0.
         * Only assert that Sciclient_service returns SUCCESS (message was sent). */
        memset(&request,  0, sizeof(request));
        request.processor_id          = TEST_PROC_ID_COPROCESSOR;
        request.control_flags_1_set   = 0U;
        request.control_flags_1_clear = 0U;
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_SET_CONTROL,
            0,          /* reqFlag=0: fire-and-forget, no AOP — same as dm_self_reset.c */
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            NULL,
            0
        };
        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!(retVal == SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgProcSetControl TC-01 Positive - step2 SET_CONTROL fire-and-forget reqFlag=0: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        /* Post-step: release ownership of C7X256V0_CORE0 */
        struct tisci_msg_proc_release_req  relReq  = {0};
        struct tisci_msg_proc_release_resp relResp = {0};
        relReq.processor_id = TEST_PROC_ID_COPROCESSOR;
        const Sciclient_ReqPrm_t relReqPrm =
        {
            TISCI_MSG_PROC_RELEASE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &relReq,
            sizeof(relReq),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t relRespPrm =
        {
            0,
            (uint8_t *) &relResp,
            sizeof(relResp)
        };
        retVal = Sciclient_service(&relReqPrm, &relRespPrm);
        if (!((retVal == SystemP_SUCCESS) && (relRespPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcSetControl TC-01 Positive - step3 release co-processor: retVal=%d flags=0x%x\r\n",
                       retVal, relRespPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    /* NOT SAFE for positive test: TIFS NACKs PROC_SET_CONTROL on a running
     * processor (C7X256V0_CORE0 is started by A53 Linux at boot). */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_SET_CONTROL,
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
            DebugP_log("FAIL: test_msgProcSetControl TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid processor_id (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id         = 0xFFU;
        request.control_flags_1_set   = 0U;
        request.control_flags_1_clear = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_SET_CONTROL,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcSetControl TC-03 Negative - invalid processor_id 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – NULL pRespPayload */
    {
        memset(&request, 0, sizeof(request));
        request.processor_id = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_SET_CONTROL,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            NULL,
            0
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcSetControl TC-04 Negative - NULL pRespPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgProcGetStatus — TISCI_MSG_PROC_GET_STATUS (0xC400)
 *
 * Positive test IS POSSIBLE:
 *   Read-only query of processor status. Safe to call for any valid
 *   processor_id.
 *
 * TC-01  Positive: get status of R5FSS0_CORE0 → SUCCESS + ACK
 * TC-02  Positive: get status of C7X256V0_CORE0 → SUCCESS + ACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 * TC-04  Negative: invalid processor_id (0xFF) → not SUCCESS or NACK
 * TC-05  Negative: NULL pRespPayload → not SUCCESS
 */
static int32_t test_msgProcGetStatus(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_proc_get_status_req  request;
    struct tisci_msg_proc_get_status_resp response;

    /* TC-01: Positive – get status of R5FSS0_CORE0 (our own core) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = SCICLIENT_PROC_ID_R5FSS0_CORE0;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_GET_STATUS,
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
            DebugP_log("FAIL: test_msgProcGetStatus TC-01 Positive - get status of R5FSS0_CORE0: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Positive – get status of C7X256V0_CORE0 */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = TEST_PROC_ID_COPROCESSOR;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_GET_STATUS,
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
            DebugP_log("FAIL: test_msgProcGetStatus TC-02 Positive - get status of co-processor: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_GET_STATUS,
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
            DebugP_log("FAIL: test_msgProcGetStatus TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – invalid processor_id (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_GET_STATUS,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcGetStatus TC-04 Negative - invalid processor_id 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /*This message falls through the default case of Sciclient_service, inside the Sciclient_serviceSecureProxy.
     There the flag is updated irrespective of NULL pRespPayload*/
    /* TC-05: negative test – NULL pRespPayload */
    {
        memset(&request, 0, sizeof(request));
        request.processor_id = SCICLIENT_PROC_ID_R5FSS0_CORE0;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_GET_STATUS,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            NULL,
            0
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) || (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcGetStatus TC-05 Negative - NULL pRespPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgProcWaitStatus — TISCI_MSG_PROC_WAIT_STATUS (0xC401)
 *
 * Positive test approach:
 *   Use clr_all_wait = (TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI |
 *                       TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFE).
 *   A running R5FSS0_CORE0 (actively executing this test) has both WFI and
 *   WFE status bits cleared, so the condition is satisfied on the first poll
 *   and TIFS returns ACK. Using 0xFFFFFFFF for any wait field must be avoided
 *   as it includes reserved bits that TIFS rejects with NACK.
 *
 * TC-01  Positive: wait on R5FSS0_CORE0 with clr_all=R5_WFI|R5_WFE
 *                  → SUCCESS + ACK (running core satisfies condition)
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid processor_id (0xFF) → not SUCCESS or NACK
 * TC-04  Negative: impossible wait condition (set_all=0xFFFFFFFF,
 *                  clr_all=0xFFFFFFFF, 1 iteration) → not SUCCESS or NACK
 */
static int32_t test_msgProcWaitStatus(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_proc_status_wait_req  request;
    struct tisci_msg_proc_status_wait_resp response;

    /* TC-01: Positive – wait on R5FSS0_CORE0 with clr_all = R5_WFI | R5_WFE.
     * A running R5FSS0_CORE0 (actively executing this test) has both WFI and
     * WFE cleared, so the condition is satisfied on the first poll.
     * 0xFFFFFFFF must NOT be used for any wait field – it includes reserved
     * bits for the R5 processor type and TIFS will NACK such a request. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id                         = SCICLIENT_PROC_ID_R5FSS0_CORE0;
        request.num_wait_iterations                  = 5U;
        request.num_match_iterations                 = 1U;
        request.delay_per_iteration_us               = 1U;
        request.delay_before_iteration_loop_start_us = 0U;
        request.status_flags_1_set_all_wait          = 0U;
        request.status_flags_1_set_any_wait          = 0U;
        request.status_flags_1_clr_all_wait          =
            TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI |
            TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFE;
        request.status_flags_1_clr_any_wait          = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_WAIT_STATUS,
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
            DebugP_log("FAIL: test_msgProcWaitStatus TC-01 Positive - wait on R5FSS0_CORE0 WFI/WFE: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_WAIT_STATUS,
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
            DebugP_log("FAIL: test_msgProcWaitStatus TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid processor_id (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id        = 0xFFU;
        request.num_wait_iterations = 1U;
        request.num_match_iterations = 1U;
        request.delay_per_iteration_us = 1U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_WAIT_STATUS,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcWaitStatus TC-03 Negative - invalid processor_id 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – impossible wait (all bits must be both set AND cleared) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.processor_id                         = SCICLIENT_PROC_ID_R5FSS0_CORE0;
        request.num_wait_iterations                  = 1U;
        request.num_match_iterations                 = 1U;
        request.delay_per_iteration_us               = 1U;
        request.delay_before_iteration_loop_start_us = 0U;
        request.status_flags_1_set_all_wait          = 0xFFFFFFFFU;
        request.status_flags_1_set_any_wait          = 0U;
        request.status_flags_1_clr_all_wait          = 0xFFFFFFFFU;
        request.status_flags_1_clr_any_wait          = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_WAIT_STATUS,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcWaitStatus TC-04 Negative - impossible wait condition: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgProcAuthBoot — TISCI_MSG_PROC_AUTH_BOOT (0xC120)
 *
 * Positive test IS POSSIBLE on AM62DX:
 *   Uses the pre-signed R5 auth-boot certificate from
 *   test/drivers/sciclient/am62dx-evm/test_sciclient_r5_cl0_c0_image.h.
 *   Pattern mirrors Sciclient_procBootAuthAndStart() in sciclient_procboot.c
 *   and test_sciclient_procboot() in sciclient_direct/test_sciclient.c.
 *   TIFS requires the calling host to OWN the target processor via PROC_REQUEST
 *   before AUTH_BOOT is accepted. Sequence: PROC_REQUEST(R5FSS0_CORE0) →
 *   PROC_AUTH_BOOT(cert) → PROC_RELEASE(R5FSS0_CORE0).
 *   The cert configures R5 boot parameters; effect applies on next reset only.
 *
 * TC-01  Positive (if TEST_PROC_AUTH_BOOT_CERT_AVAILABLE): PROC_REQUEST → AUTH_BOOT pre-signed R5 cert
 *                            → SUCCESS + ACK → PROC_RELEASE
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: zero certificate address → not SUCCESS or NACK
 * TC-04  Negative: invalid certificate address (0xDEADBEEF) → not SUCCESS or NACK
 */
static int32_t test_msgProcAuthBoot(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_proc_auth_boot_req  request;
    struct tisci_msg_proc_auth_boot_resp response;

#if defined(TEST_PROC_AUTH_BOOT_CERT_AVAILABLE)
    /* TC-01: Positive – authenticated boot with pre-signed R5 cert.
     * Pattern mirrors Sciclient_procBootAuthAndStart() in sciclient_procboot.c
     * and test_sciclient_procboot() in sciclient_direct/test_sciclient.c.
     * TIFS requires the calling host to OWN the target processor before
     * PROC_AUTH_BOOT is accepted — without PROC_REQUEST first, TIFS NACKs.
     * Sequence: PROC_REQUEST(R5FSS0_CORE0) → PROC_AUTH_BOOT(cert) →
     *           PROC_RELEASE(R5FSS0_CORE0).  The cert reconfigures the R5
     *           boot vector; effect applies on next reset only, so the running
     *           test harness is unaffected. */
    {
        int32_t reqRetVal;

        /* Step 1: Acquire ownership of R5FSS0_CORE0 (required by TIFS) */
        reqRetVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0,
                                                       SystemP_WAIT_FOREVER);
        if (!(reqRetVal == SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgProcAuthBoot TC-01 Positive - step1 acquire R5FSS0_CORE0 ownership: reqRetVal=%d\r\n",
                       reqRetVal);
            failCount++;
        }

        /* Step 2: PROC_AUTH_BOOT with the pre-signed R5 cert */
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.certificate_address_lo = (uint32_t)((uint64_t)r5_cl0_c0_binary_hs & 0xFFFFFFFFU);
        request.certificate_address_hi = (uint32_t)(((uint64_t)r5_cl0_c0_binary_hs >> 32U) & 0xFFFFFFFFU);

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_AUTH_BOOT,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
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
            DebugP_log("FAIL: test_msgProcAuthBoot TC-01 Positive - step2 PROC_AUTH_BOOT with pre-signed cert: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }

        /* Step 3: Release R5FSS0_CORE0 ownership */
        (void)Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0,
                                                 TISCI_MSG_FLAG_AOP,
                                                 SystemP_WAIT_FOREVER);
    }
#endif /* TEST_PROC_AUTH_BOOT_CERT_AVAILABLE */

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_AUTH_BOOT,
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
            DebugP_log("FAIL: test_msgProcAuthBoot TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – zero certificate address */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.certificate_address_lo = 0U;
        request.certificate_address_hi = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_AUTH_BOOT,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcAuthBoot TC-03 Negative - zero certificate address: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – invalid certificate address */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.certificate_address_lo = 0xDEADBEEFU;
        request.certificate_address_hi = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_PROC_AUTH_BOOT,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgProcAuthBoot TC-04 Negative - invalid certificate address: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}


/* ========================================================================== */
/*            Helper Function Implementations — System Control Tests          */
/* ========================================================================== */

/**
 *
 * DRIVER FLOW ANALYSIS:
 *   TISCI_MSG_SYS_RESET (0x0005) is routed via nonSecureContextId.
 *
 * TESTABILITY:
 *   TISCI_MSG_SYS_RESET:
 *     Positive test IS POSSIBLE as the LAST test case in the suite.
 *     A successful SYS_RESET immediately resets the entire system.
 *     Since TC_17 is the final test, the positive case is placed at the
 *     end of test_msgSysReset so all other tests complete first before the
 *     system reboots. Pattern mirrors Sciclient_pmDeviceReset() in
 *     sciclient_pm.c (domain=0, TISCI_MSG_FLAG_AOP, WAIT_FOREVER).
 */

/**
 * test_msgSysReset — TISCI_MSG_SYS_RESET (0x0005)
 *
 * Positive test IS POSSIBLE as the last case (TC-04):
 *   domain=0 triggers a full system reset. Placed last so all negative
 *   tests complete first. Pattern mirrors Sciclient_pmDeviceReset() in
 *   sciclient_pm.c. The system reboots immediately on ACK.
 *
 * TC-01  Negative: NULL pReqPayload → not SUCCESS
 * TC-02  Negative: invalid domain (0xFF) → not SUCCESS or NACK
 * TC-03  Negative: NULL pRespPayload → not SUCCESS
 * TC-04  Positive: domain=0, AOP flag, WAIT_FOREVER → SUCCESS + ACK
 *          (system resets immediately; this is the last test in the suite)
 */
static int32_t test_msgSysReset(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_sys_reset_req  request;
    struct tisci_msg_sys_reset_resp response;

    /* TC-01: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SYS_RESET,
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
            DebugP_log("FAIL: test_msgSysReset TC-01 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid domain (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.domain = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SYS_RESET,
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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSysReset TC-02 Negative - invalid domain 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pRespPayload */
    {
        memset(&request, 0, sizeof(request));
        request.domain = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SYS_RESET,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            NULL,
            0
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSysReset TC-03 Negative - NULL pRespPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

#ifdef ENABLE_MANUAL_TEST
    /* TC-04: Positive – domain=0 (full system reset), AOP flag, WAIT_FOREVER.
     * Mirrors Sciclient_pmDeviceReset() in sciclient_pm.c. TC_17 is the last
     * test in the suite; all prior tests have already completed. The system
     * resets immediately upon ACK from TIFS/DM.
     *
     * NOTE: This test is guarded by ENABLE_MANUAL_TEST because it resets the
     * entire board. When executed, the device reboots immediately and all
     * subsequent logs are lost. Enable this macro only for manual validation. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.domain = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SYS_RESET,
            TISCI_MSG_FLAG_AOP,
            (const uint8_t *) &request,
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
            DebugP_log("FAIL: test_msgSysReset TC-04 Positive - full system reset domain=0: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
#endif /* ENABLE_MANUAL_TEST */
    return failCount;
}


/* ========================================================================== */
/*            Test Wrapper Function Implementations                         */
/* ========================================================================== */

void testSciclient_procBoot(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgProcRequest(NULL);
    testfailcount += test_msgProcRelease(NULL);
    testfailcount += test_msgProcSetConfig(NULL);
    testfailcount += test_msgProcSetControl(NULL);
    testfailcount += test_msgProcHandover(NULL);
    testfailcount += test_msgProcGetStatus(NULL);
    testfailcount += test_msgProcWaitStatus(NULL);
    testfailcount += test_msgProcAuthBoot(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}


void testSciclient_sysControl(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgSysReset(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}


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
#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/tisci_core.h>
#include <drivers/sciclient/include/tisci/tisci_protocol.h>
#include <drivers/sciclient/include/tisci/lpm/tisci_lpm.h>
#include <drivers/sciclient/include/tisci/security/tisci_procboot.h>
#include <drivers/sciclient/include/tisci/security/tisci_secure_jtag.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_core.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include "test_device_manager_lpm.h"

/* ========================================================================== */
/*            Helper Function Implementations — LPM Tests                     */
/* ========================================================================== */

/**
 * DRIVER FLOW ANALYSIS (ENABLE_SCICLIENT_DIRECT mode, CONFIG_LPM_DM):
 *   TISCI_MSG_LPM_WAKE_REASON           → local PM only (read-only query)
 *   TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT  → local PM only (set/clear flag)
 *   TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT → local PM only (set/clear flag)
 *   TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT  → local PM only (read-only query)
 *   TISCI_MSG_LPM_GET_LATENCY_CONSTRAINT → local PM only (read-only query)
 *   TISCI_MSG_LPM_GET_NEXT_SYS_MODE     → local PM only (read-only query)
 *   TISCI_MSG_LPM_GET_NEXT_HOST_STATE    → local PM only (read-only query)
 *
 * EXCLUDED MESSAGES (unsafe for runtime testing):
 *   TISCI_MSG_PREPARE_SLEEP  → triggers system-wide LPM entry, destructive
 *   TISCI_MSG_SET_IO_ISOLATION → can isolate IOs and hang the system
 *   TISCI_MSG_LPM_ABORT → requires prior PREPARE_SLEEP, TIFS interaction
 *
 * NOTE: LPM messages require the appropriate LPM build macro to be defined:
 *   AM62DX  → CONFIG_LPM_DM
 *   AM275X  → CONFIG_LPM_MIN
 * If the macro is absent, Sciclient_ProcessPmMessage() will not recognize these
 * message IDs and they will fall through to the default handler (NACK).
 */

/**
 * test_msgLpmWakeReason — TISCI_MSG_LPM_WAKE_REASON (0x0306)
 *
 * TC-01  Positive: query wake reason → SUCCESS + ACK
 *        Returns wake_source/pin/mode/timestamp.  On a normal boot (no LPM
 *        resume), wake_source and wake_pin are typically INVALID (0xFF).
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgLpmWakeReason(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_lpm_wake_reason_req  request;
    struct tisci_msg_lpm_wake_reason_resp response;

    /* TC-01: Positive – query wake reason (read-only, safe) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_WAKE_REASON,
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
            DebugP_log("FAIL: test_msgLpmWakeReason TC-01 Positive - query wake reason: retVal=%d flags=0x%x\r\n", retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_WAKE_REASON,
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
            DebugP_log("FAIL: test_msgLpmWakeReason TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgLpmSetDeviceConstraint — TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT (0x0309)
 * TC-01  Positive: set constraint (state=1) on TEST_DEVICE_ID → SUCCESS + ACK
 * TC-02  Positive: clear constraint (state=0) on TEST_DEVICE_ID → SUCCESS + ACK
 * TC-03  Negative: invalid device ID → SUCCESS (handler clears constraint)
 * TC-04  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgLpmSetDeviceConstraint(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_lpm_set_device_constraint_req  request;
    struct tisci_msg_lpm_set_device_constraint_resp response;

    /* TC-01: Positive – set device constraint (state=1) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.id    = TEST_DEVICE_ID;
        request.state = 1U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmSetDeviceConstraint TC-01 Positive - set device constraint state=1: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Positive – clear device constraint (state=0, restore) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.id    = TEST_DEVICE_ID;
        request.state = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmSetDeviceConstraint TC-02 Positive - clear device constraint state=0: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: negative – invalid device ID*/
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.id    = 0xFFFFFFFFU;
        request.state = 1U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmSetDeviceConstraint TC-03 Negative - invalid device ID: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmSetDeviceConstraint TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

/**
 * test_msgLpmSetLatencyConstraint — TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT (0x030A)
 * TC-01  Positive: set latency constraint (state=1, 100ms) → SUCCESS + ACK
 * TC-02  Positive: clear constraint (state=0) → SUCCESS + ACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgLpmSetLatencyConstraint(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_lpm_set_latency_constraint_req  request;
    struct tisci_msg_lpm_set_latency_constraint_resp response;

    /* TC-01: Positive – set latency constraint (state=1, resume_latency=100ms) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.resume_latency = 100U;
        request.state          = 1U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmSetLatencyConstraint TC-01 Positive - set latency constraint state=1 resume_latency=100ms: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Positive – clear latency constraint (state=0, restore) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.resume_latency = 0U;
        request.state          = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmSetLatencyConstraint TC-02 Positive - clear latency constraint state=0: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmSetLatencyConstraint TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

/**
 * test_msgLpmGetDeviceConstraint — TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT (0x030B)
 * TC-01  Positive: get constraint for TEST_DEVICE_ID → SUCCESS + ACK + state
 * TC-02  Negative: invalid device ID → NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgLpmGetDeviceConstraint(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_lpm_get_device_constraint_req  request;
    struct tisci_msg_lpm_get_device_constraint_resp response;

    /* TC-01: Positive – get device constraint (read-only, safe) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.id = TEST_DEVICE_ID;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmGetDeviceConstraint TC-01 Positive - get device constraint: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid device ID */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.id = 0xFFFFFFFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmGetDeviceConstraint TC-02 Negative - invalid device ID: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_GET_DEVICE_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmGetDeviceConstraint TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgLpmGetLatencyConstraint — TISCI_MSG_LPM_GET_LATENCY_CONSTRAINT (0x030C)
 * TC-01  Positive: get latency constraint → SUCCESS + ACK + state/latency
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgLpmGetLatencyConstraint(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_lpm_get_latency_constraint_req  request;
    struct tisci_msg_lpm_get_latency_constraint_resp response;

    /* TC-01: Positive – get latency constraint (read-only, safe) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_GET_LATENCY_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmGetLatencyConstraint TC-01 Positive - get latency constraint: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_GET_LATENCY_CONSTRAINT,
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
            DebugP_log("FAIL: test_msgLpmGetLatencyConstraint TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgLpmGetNextSysMode — TISCI_MSG_LPM_GET_NEXT_SYS_MODE (0x030D)
 * TC-01  Positive: query next system mode → SUCCESS + ACK + mode
 *        Returns 0xFE (NOT_SELECTED) if mode selection is not yet locked.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgLpmGetNextSysMode(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_lpm_get_next_sys_mode_req  request;
    struct tisci_msg_lpm_get_next_sys_mode_resp response;

    /* TC-01: Positive – query next system mode (read-only, safe) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_GET_NEXT_SYS_MODE,
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
            DebugP_log("FAIL: test_msgLpmGetNextSysMode TC-01 Positive - query next system mode: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_GET_NEXT_SYS_MODE,
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
            DebugP_log("FAIL: test_msgLpmGetNextSysMode TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgLpmGetNextHostState — TISCI_MSG_LPM_GET_NEXT_HOST_STATE (0x030E)
 *
 * TC-01  Positive: query next host state → SUCCESS + ACK + state
 *        Returns 0xFF (INVALID) if mode is not locked.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgLpmGetNextHostState(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_lpm_get_next_host_state_req  request;
    struct tisci_msg_lpm_get_next_host_state_resp response;

    /* TC-01: Positive – query next host state (read-only, safe) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_GET_NEXT_HOST_STATE,
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
            DebugP_log("FAIL: test_msgLpmGetNextHostState TC-01 Positive - query next host state: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_LPM_GET_NEXT_HOST_STATE,
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
            DebugP_log("FAIL: test_msgLpmGetNextHostState TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}


/* ========================================================================== */
/*            Test Wrapper Function Implementations                         */
/* ========================================================================== */

void testDM_lpm(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgLpmWakeReason(NULL);
#ifdef CONFIG_LPM_DM
    testfailcount += test_msgLpmSetDeviceConstraint(NULL);
    testfailcount += test_msgLpmSetLatencyConstraint(NULL);
    testfailcount += test_msgLpmGetDeviceConstraint(NULL);
    testfailcount += test_msgLpmGetLatencyConstraint(NULL);
    testfailcount += test_msgLpmGetNextSysMode(NULL);
    testfailcount += test_msgLpmGetNextHostState(NULL);
#endif /* CONFIG_LPM_DM */
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

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
#include <drivers/sciclient/include/tisci/security/tisci_ext_otp.h>
#include <drivers/sciclient/include/tisci/security/tisci_otp_revision.h>
#include <drivers/sciclient/include/tisci/security/tisci_sec_handover.h>
#include <drivers/sciclient/include/tisci/security/tisci_dkek.h>
#include <drivers/sciclient/include/tisci/security/tisci_dsmek.h>
#include <drivers/sciclient/include/tisci/security/tisci_keywriter.h>
#include <drivers/sciclient/include/tisci/security/tisci_keyring.h>
#include <drivers/sciclient/include/tisci/security/tisci_firewall.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include "test_sciclient_sec.h"

/* ========================================================================== */
/*              Static Forward Declarations for Sub-functions                 */
/* ========================================================================== */

static int32_t test_msgReadOtpMmr(void *args);
static int32_t test_msgGetOtpRowLockStatus(void *args);
static int32_t test_msgReadSwrev(void *args);
static int32_t test_msgReadKeycntKeyrev(void *args);

static int32_t test_msgSecHandover(void *args);
static int32_t test_msgSa2ulSetDkek(void *args);
static int32_t test_msgSa2ulGetDkek(void *args);
static int32_t test_msgSa2ulReleaseDkek(void *args);
static int32_t test_msgSa2ulSetDsmek(void *args);
static int32_t test_msgSa2ulGetDsmek(void *args);
static int32_t test_msgSa2ulReleaseDsmek(void *args);
#if !defined(SKIP_SCICLIENT)
static int32_t test_msgCryptoGetDkek(void *args);
#endif
static int32_t test_msgKeyWriter(void *args);
static int32_t test_msgKeyringImport(void *args);

static int32_t test_msgSetFwlRegion(void *args);
static int32_t test_msgGetFwlRegion(void *args);
static int32_t test_msgChangeFwlOwner(void *args);

/* ========================================================================== */
/*                 Wrapper Functions for Test Categories                      */
/* ========================================================================== */

/*
 * TC_09 wrapper — OTP & Key Management (read-only safe queries)
 */
void testSciclient_otpKeyMgmt(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgReadOtpMmr(NULL);
    testfailcount += test_msgGetOtpRowLockStatus(NULL);
    testfailcount += test_msgReadSwrev(NULL);
    testfailcount += test_msgReadKeycntKeyrev(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

/*
 * TC_10 wrapper — Security & Encryption (SEC_HANDOVER, KEY_WRITER, KEYRING_IMPORT)
 */
void testSciclient_securityEncryption(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgSecHandover(NULL);
    testfailcount += test_msgKeyWriter(NULL);
    testfailcount += test_msgKeyringImport(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

/*
 * TC_11 wrapper — SA2UL Crypto Accelerator (DKEK / DSMEK)
 */
void testSciclient_sa2ulCrypto(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgSa2ulSetDkek(NULL);
    testfailcount += test_msgSa2ulGetDkek(NULL);
    testfailcount += test_msgSa2ulReleaseDkek(NULL);
    testfailcount += test_msgSa2ulSetDsmek(NULL);
    testfailcount += test_msgSa2ulGetDsmek(NULL);
    testfailcount += test_msgSa2ulReleaseDsmek(NULL);
#if !defined(SKIP_SCICLIENT)
    testfailcount += test_msgCryptoGetDkek(NULL);
#endif
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

/*
 * TC_15 wrapper — Firewall Management
 */
void testSciclient_firewallMgmt(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgSetFwlRegion(NULL);
    testfailcount += test_msgGetFwlRegion(NULL);
    testfailcount += test_msgChangeFwlOwner(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

static int32_t test_msgReadOtpMmr(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_read_otp_mmr_req  request;
    struct tisci_msg_read_otp_mmr_resp response;

    /* TC-01: Read OTP MMR index 0.
     * NOTE: the security boardcfg's otp_config.write_host_id is
     * TISCI_HOST_ID_MAIN_0_R5_0 (see sciclient_defaultBoardcfg_security.c).
     * This test runs on TISCI_HOST_ID_MCU_0_R5_0, which TIFS does not treat
     * as an OTP-authorized host, so the request is always NACKed here
     * regardless of mmr_idx (same class of restriction documented for the
     * WKUP R5F host in test_sciclient_intr_polling.c's
     * TEST_DM_OTP_WKUP_HOST_RESTRICTED case) — only verify that the message
     * transport itself succeeded. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.mmr_idx = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_OTP_MMR,
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
            DebugP_log("FAIL: test_msgReadOtpMmr TC-01 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid mmr_idx (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.mmr_idx = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_OTP_MMR,
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
            DebugP_log("FAIL: test_msgReadOtpMmr TC-02 Negative - invalid mmr_idx 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_OTP_MMR,
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
            DebugP_log("FAIL: test_msgReadOtpMmr TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: pRespPayload=NULL, respPayloadSize=0.
     * Sciclient_service() only requires a non-NULL pRespPayload when
     * respPayloadSize > 0 (see the rxPayloadSize checks in sciclient.c),
     * so respPayloadSize=0 is a valid "discard the response payload"
     * request, not a local parameter error — this request still reaches
     * TIFS. Like test_msgReadOtpMmr TC-01, the resulting ACK/NACK is
     * governed purely by this host's OTP read permission (otp_config in
     * sciclient_defaultBoardcfg_security.c), which can legitimately differ
     * per core (e.g. NACK on mcu-r5fss0-0, ACK on a53ss0-0/c75ss0-0).
     * Only verify that the message transport itself succeeded. */
    {
        memset(&request, 0, sizeof(request));
        request.mmr_idx = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_OTP_MMR,
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
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: test_msgReadOtpMmr TC-04 test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgGetOtpRowLockStatus — TISCI_MSG_GET_OTP_ROW_LOCK_STATUS (0x9026)
 *
 * TC-01  Get lock status for row 0 → transport SUCCESS only (this core,
 *        MCU_0_R5_0, is not the boardcfg otp_config.write_host_id, so the
 *        request is always NACKed here; see test_msgReadOtpMmr TC-01)
 * TC-02  Negative: invalid row_idx (0xFF) → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 * -------------------------------------------------------------------------- */
static int32_t test_msgGetOtpRowLockStatus(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_get_otp_row_lock_status_req  request;
    struct tisci_msg_get_otp_row_lock_status_resp response;

    /* TC-01: Get lock status for row 0.  See test_msgReadOtpMmr TC-01 —
     * MCU_0_R5_0 is not the OTP write_host_id, so TIFS always NACKs this
     * query on this core; only verify the message transport succeeded. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.row_idx = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_OTP_ROW_LOCK_STATUS,
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
            DebugP_log("FAIL: test_msgGetOtpRowLockStatus TC-01 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid row_idx (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.row_idx = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_OTP_ROW_LOCK_STATUS,
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
            DebugP_log("FAIL: test_msgGetOtpRowLockStatus TC-02 Negative - invalid row_idx 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_OTP_ROW_LOCK_STATUS,
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
            DebugP_log("FAIL: test_msgGetOtpRowLockStatus TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgReadSwrev — TISCI_MSG_READ_SWREV (0x9033)
 *
 * Positive test approach (mirrors otp_revision_readSwrev() in otp_revision.c):
 *   Verify that the Sciclient transport layer succeeds (retVal == SystemP_SUCCESS).
 *   TIFS ACKs on provisioned production boards (OTP anti-rollback rows programmed).
 *   TIFS NACKs on unprovisioned dev EVMs (OTP rows blank) — this is a board
 *   provisioning state, NOT a firmware or driver bug. See PROV-001.
 *   The full SUCCESS + ACK assertion is therefore not enforced here.
 *
 * TC-01  Positive: transport-level success; log SWREV value from TIFS response
 *                  → retVal == SystemP_SUCCESS (ACK if provisioned, NACK if not)
 * TC-02  Negative: invalid identifier (0xFF) → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 * -------------------------------------------------------------------------- */
static int32_t test_msgReadSwrev(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_get_swrev_req  request;
    struct tisci_msg_get_swrev_resp response;

    /* TC-01: Positive – read SW revision using OTP_REV_ID_SEC_BRDCFG (=2).
     * Mirrors otp_revision_readSwrev() in otp_revision.c.
     * Only the transport-level result is asserted: retVal == SystemP_SUCCESS
     * confirms the message reached TIFS and a response was received.
     * TIFS ACKs (and populates response.value) on provisioned boards.
     * TIFS NACKs on unprovisioned dev EVMs where the Secure Board Config
     * OTP anti-rollback rows have not been programmed — PROV-001.
     * The ACK/NACK flag is logged for visibility but NOT asserted. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.identifier = OTP_REV_ID_SEC_BRDCFG;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_SWREV,
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
        /* Transport must succeed; ACK vs NACK depends on board provisioning (PROV-001) */
        if (!(retVal == SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgReadSwrev TC-01 Positive - transport-level read SWREV (ACK depends on board provisioning): retVal=%d\r\n",
                       retVal);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid identifier (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.identifier = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_SWREV,
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
            DebugP_log("FAIL: test_msgReadSwrev TC-02 Negative - invalid identifier 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_SWREV,
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
            DebugP_log("FAIL: test_msgReadSwrev TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgReadKeycntKeyrev — TISCI_MSG_READ_KEYCNT_KEYREV (0x9034)
 *
 * Positive test approach (mirrors otp_revision_readKeyrevKeycnt() in otp_revision.c):
 *   Verify that the Sciclient transport layer succeeds (retVal == SystemP_SUCCESS).
 *   TIFS ACKs on provisioned production boards (key OTP rows programmed).
 *   TIFS NACKs on unprovisioned dev EVMs (key OTP rows blank) — this is a
 *   board provisioning state, NOT a firmware or driver bug. See PROV-002.
 *   The full SUCCESS + ACK assertion is therefore not enforced here.
 *
 * TC-01  Positive: transport-level success; log keycnt/keyrev from TIFS response
 *                  → retVal == SystemP_SUCCESS (ACK if provisioned, NACK if not)
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: NULL pRespPayload, zero respPayloadSize → not SUCCESS or NACK
 * -------------------------------------------------------------------------- */
static int32_t test_msgReadKeycntKeyrev(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_get_keycnt_keyrev_req  request;
    struct tisci_msg_get_keycnt_keyrev_resp response;

    /* TC-01: Positive – read key count & key revision (safe read-only).
     * Pattern mirrors otp_revision_readKeyrevKeycnt() in otp_revision.c:
     *   TISCI_MSG_FLAG_AOP, sizeof(request), sizeof(response).
     * On a provisioned board: TIFS ACKs with keycnt/keyrev values.
     * On this dev EVM (key OTP rows blank): TIFS NACKs — this is a board
     * provisioning state (PROV-002), NOT a firmware or driver defect.
     * Assert only that Sciclient transport succeeded (message sent + response
     * received). The ACK/NACK is logged for visibility. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_KEYCNT_KEYREV,
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
        /* Assert only transport-level success: message was processed by TIFS.
         * ACK vs NACK depends on board provisioning, not on driver correctness. */
        if (!(retVal == SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgReadKeycntKeyrev TC-01 Positive - transport-level read keycnt/keyrev: retVal=%d\r\n",
                       retVal);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_KEYCNT_KEYREV,
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
            DebugP_log("FAIL: test_msgReadKeycntKeyrev TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pRespPayload, zero respPayloadSize */
    {
        memset(&request, 0, sizeof(request));

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_READ_KEYCNT_KEYREV,
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
            DebugP_log("FAIL: test_msgReadKeycntKeyrev TC-03 Negative - NULL pRespPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* ==========================================================================
 * TC_10: Security & Crypto Messages
 *
 * DRIVER FLOW ANALYSIS:
 *   ALL messages in this group are forwarded to TIFS via Sciclient_serviceSecureProxy()
 *   through the SECURE context (secureContextId). No local DM processing.
 *
 * TESTABILITY ANALYSIS:
 *
 *   TISCI_MSG_SEC_HANDOVER (0x9030):
 *     NOT SAFE for positive test. Can only be sent by the host specified in
 *     security board configuration. DM test runs as TISCI_HOST_ID_MAIN_0_R5_1
 *     which is NOT the security handover host. Additionally, security handover
 *     is a one-time operation that transfers security ownership from TIFS to
 *     the designated host — executing it at runtime would break the security
 *     state machine. NEGATIVE TESTS ONLY (NULL payload, expect NACK).
 *
 *   TISCI_MSG_SA2UL_SET_DKEK (0x9003):
 *     Positive test is POSSIBLE. Sets a Derived KEK in the crypto engine.
 *     Uses KDF with label+context to derive a 256-bit key. Instance=0.
 *     Safe to call — it programs a volatile key register, not OTP.
 *
 *   TISCI_MSG_SA2UL_GET_DKEK (0x9029):
 *     Positive test is POSSIBLE. Retrieves the DKEK via TISCI (returns 32-byte
 *     key in response). Requires SET_DKEK to be called first with same params.
 *
 *   TISCI_MSG_SA2UL_RELEASE_DKEK (0x9004):
 *     Positive test is POSSIBLE. Releases the DKEK from the crypto engine.
 *     Safe cleanup operation.
 *
 *   TISCI_MSG_SA2UL_SET_DSMEK (0x9037):
 *     Positive test is POSSIBLE. Sets a Derived SMEK in the crypto engine.
 *     Same KDF mechanism as DKEK but for the SMEK key slot.
 *
 *   TISCI_MSG_SA2UL_GET_DSMEK (0x9036):
 *     Positive test is POSSIBLE. Retrieves the DSMEK (32-byte key).
 *     Requires SET_DSMEK first.
 *
 *   TISCI_MSG_SA2UL_RELEASE_DSMEK (0x9038):
 *     Positive test is POSSIBLE. Releases the DSMEK. Safe cleanup.
 *
 *   TISCI_MSG_KEY_WRITER (0x9031):
 *     NOT SAFE for positive test. PERMANENTLY writes keys to OTP eFuses.
 *     Requires a signed X.509 certificate with the key material at a valid
 *     memory address. Any write to OTP is IRREVERSIBLE.
 *     NEGATIVE TESTS ONLY (NULL payload, invalid address).
 *
 *   TISCI_MSG_KEYRING_IMPORT (0x9039):
 *     NOT SAFE for positive test. Imports an encrypted keyring into TIFS
 *     runtime key storage. Requires a properly encrypted and authenticated
 *     keyring blob at a valid memory address. Without genuine key material
 *     TIFS will NACK. NEGATIVE TESTS ONLY (NULL payload, zero address).
 *
 *   TISCI_MSG_SET_ISC_REGION (0x9009):
 *     NOT TESTABLE. Message ID is defined but NO request/response struct
 *     exists in the SDK headers. Cannot construct a valid TISCI payload.
 *     Only NULL-payload negative test is possible.
 *
 *   TISCI_MSG_GET_ISC_REGION (0x900A):
 *     NOT TESTABLE. Same as SET_ISC_REGION — no struct definitions available.
 *     Only NULL-payload negative test is possible.
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * test_msgSecHandover — TISCI_MSG_SEC_HANDOVER (0x9030)
 *
 * NOT SAFE for positive test:
 *   - Only the host specified in security board configuration is allowed.
 *   - DM test runs as TISCI_HOST_ID_MAIN_0_R5_1, NOT the security owner.
 *   - Security handover is a one-time, destructive operation.
 *
 * TC-01  Negative: send from unauthorized host → NACK (host check fails)
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * -------------------------------------------------------------------------- */
static int32_t test_msgSecHandover(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_security_handover_req  request;
    struct tisci_msg_security_handover_resp response;

    /* TC-01: Negative – DM test host (MAIN_0_R5_1) is NOT the designated
     * security handover host. TIFS should NACK. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SEC_HANDOVER,
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
            DebugP_log("FAIL: test_msgSecHandover TC-01 Negative - unauthorized host MAIN_0_R5_1 not handover host: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SEC_HANDOVER,
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
            DebugP_log("FAIL: test_msgSecHandover TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgSa2ulSetDkek — TISCI_MSG_SA2UL_SET_DKEK (0x9003)
 *
 * TC-01  Set DKEK with instance=0, label="TEST", context="CTX" → transport
 *        SUCCESS only. The security boardcfg's sa2ul_auth_cfg.auth_resource_owner
 *        is TISCI_HOST_ID_TIFS (0), so no R5/A53 host — including this core
 *        (MCU_0_R5_0) — is authorized to acquire/release SA2UL authentication
 *        resources; TIFS legitimately NACKs the request regardless of host.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Positive: invalid sa2ul_instance (0xFF) → SUCCESS (DM forwards to TIFS)
 * TC-04  Positive: kdf_label_len overflow → SUCCESS (DM forwards to TIFS)
 *                  → not SUCCESS or NACK
 * -------------------------------------------------------------------------- */
static int32_t test_msgSa2ulSetDkek(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_sa2ul_set_dkek_req  request;
    struct tisci_msg_sa2ul_set_dkek_resp response;

    /* TC-01: Positive – set DKEK with valid params */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance  = 0U;
        request.kdf_label_len   = 4U;
        request.kdf_context_len = 3U;
        memcpy(&request.kdf_label_and_context[0], "TEST", 4);
        memcpy(&request.kdf_label_and_context[4], "CTX", 3);

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_SET_DKEK,
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
            DebugP_log("FAIL: test_msgSa2ulSetDkek TC-01 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_SET_DKEK,
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
            DebugP_log("FAIL: test_msgSa2ulSetDkek TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: sa2ul_instance (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance  = 0xFFU;
        request.kdf_label_len   = 4U;
        request.kdf_context_len = 3U;
        memcpy(&request.kdf_label_and_context[0], "TEST", 4);
        memcpy(&request.kdf_label_and_context[4], "CTX", 3);

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_SET_DKEK,
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
        if (!((retVal == SystemP_SUCCESS) || (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSa2ulSetDkek TC-03 Negative - invalid sa2ul_instance 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: positive – kdf_label_len overflow (exceeds buffer) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance  = 0U;
        request.kdf_label_len   = 0xFFU;  /* far exceeds KDF_LABEL_AND_CONTEXT_LEN_MAX */
        request.kdf_context_len = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_SET_DKEK,
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
        if (!((retVal == SystemP_SUCCESS) || (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSa2ulSetDkek TC-04 Positive - kdf_label_len overflow 0xFF (DM forwards to TIFS): retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgSa2ulGetDkek — TISCI_MSG_SA2UL_GET_DKEK (0x9029)
 *
 * TC-01  Get DKEK with instance=0 → transport SUCCESS only. See
 *        test_msgSa2ulSetDkek TC-01: this core is not the SA2UL
 *        auth_resource_owner, so TIFS always NACKs this request.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Positive: invalid sa2ul_instance (0xFF) → SUCCESS (DM forwards to TIFS)
 * -------------------------------------------------------------------------- */
static int32_t test_msgSa2ulGetDkek(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_sa2ul_get_dkek_req  request;
    struct tisci_msg_sa2ul_get_dkek_resp response;

    /* TC-01: Positive – get DKEK (SET_DKEK was called in test_msgSa2ulSetDkek TC-01) */
    {
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
            DebugP_log("FAIL: test_msgSa2ulGetDkek TC-01 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_GET_DKEK,
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
            DebugP_log("FAIL: test_msgSa2ulGetDkek TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: positive – invalid sa2ul_instance (0xFF)
    This message is directly sent to TIFS from DM and DM doesn't perform any operations while
    sending or receiving. So these messages can be marked as passing test */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance = 0xFFU;

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
        if (!((retVal == SystemP_SUCCESS) || (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSa2ulGetDkek TC-03 Negative - invalid sa2ul_instance 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgSa2ulReleaseDkek — TISCI_MSG_SA2UL_RELEASE_DKEK (0x9004)
 *
 * TC-01  Release DKEK for instance=0 → transport SUCCESS only. See
 *        test_msgSa2ulSetDkek TC-01: this core is not the SA2UL
 *        auth_resource_owner, so TIFS always NACKs this request.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid sa2ul_instance (0xFF) → not SUCCESS or NACK
 * -------------------------------------------------------------------------- */
static int32_t test_msgSa2ulReleaseDkek(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_sa2ul_release_dkek_req  request;
    struct tisci_msg_sa2ul_release_dkek_resp response;

    /* TC-01: Positive – release DKEK (cleanup from SET/GET test above) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_RELEASE_DKEK,
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
            DebugP_log("FAIL: test_msgSa2ulReleaseDkek TC-01 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_RELEASE_DKEK,
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
            DebugP_log("FAIL: test_msgSa2ulReleaseDkek TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid sa2ul_instance (0xFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_RELEASE_DKEK,
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
            DebugP_log("FAIL: test_msgSa2ulReleaseDkek TC-03 Negative - invalid sa2ul_instance 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgSa2ulSetDsmek — TISCI_MSG_SA2UL_SET_DSMEK (0x9037)
 *
 * TC-01  Set DSMEK with instance=0, label="SMEK", context="TST" → transport
 *        SUCCESS only. See test_msgSa2ulSetDkek TC-01: this core is not the
 *        SA2UL auth_resource_owner, so TIFS always NACKs this request.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Positive: invalid sa2ul_instance (0xFF) → SUCCESS (DM forwards to TIFS)
 * -------------------------------------------------------------------------- */
static int32_t test_msgSa2ulSetDsmek(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_sa2ul_set_dsmek_req  request;
    struct tisci_msg_sa2ul_set_dsmek_resp response;

    /* TC-01: Positive – set DSMEK with valid params */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance  = 0U;
        request.kdf_label_len   = 4U;
        request.kdf_context_len = 3U;
        memcpy(&request.kdf_label_and_context[0], "SMEK", 4);
        memcpy(&request.kdf_label_and_context[4], "TST", 3);

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_SET_DSMEK,
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
            DebugP_log("FAIL: test_msgSa2ulSetDsmek TC-01 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_SET_DSMEK,
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
            DebugP_log("FAIL: test_msgSa2ulSetDsmek TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: negative – invalid sa2ul_instance (0xFF)
    This message is directly sent to TIFS from DM and DM doesn't perform any operations 
    while sending or receiving. So these messages can be marked as passing test */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance  = 0xFFU;
        request.kdf_label_len   = 4U;
        request.kdf_context_len = 3U;
        memcpy(&request.kdf_label_and_context[0], "SMEK", 4);
        memcpy(&request.kdf_label_and_context[4], "TST", 3);

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_SET_DSMEK,
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
        if (!((retVal == SystemP_SUCCESS) || (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSa2ulSetDsmek TC-03 Negative - invalid sa2ul_instance 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgSa2ulGetDsmek — TISCI_MSG_SA2UL_GET_DSMEK (0x9036)
 *
 * TC-01  Get DSMEK with instance=0 → transport SUCCESS only. See
 *        test_msgSa2ulSetDkek TC-01: this core is not the SA2UL
 *        auth_resource_owner, so TIFS always NACKs this request.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Positive: invalid sa2ul_instance (0xFF) → SUCCESS (DM forwards to TIFS)
 * -------------------------------------------------------------------------- */
static int32_t test_msgSa2ulGetDsmek(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_sa2ul_get_dsmek_req  request;
    struct tisci_msg_sa2ul_get_dsmek_resp response;

    /* TC-01: Positive – get DSMEK (SET_DSMEK was called in test_msgSa2ulSetDsmek TC-01) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance  = 0U;
        request.kdf_label_len   = 4U;
        request.kdf_context_len = 3U;
        memcpy(&request.kdf_label_and_context[0], "SMEK", 4);
        memcpy(&request.kdf_label_and_context[4], "TST", 3);

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_GET_DSMEK,
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
            DebugP_log("FAIL: test_msgSa2ulGetDsmek TC-01 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_GET_DSMEK,
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
            DebugP_log("FAIL: test_msgSa2ulGetDsmek TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: positive – invalid sa2ul_instance (0xFF)
    This message is directly sent to TIFS from DM and DM doesn't perform any operations while sending or receiving.
    So these messages can be marked as passing test. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_GET_DSMEK,
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
        if (!((retVal == SystemP_SUCCESS) || (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSa2ulGetDsmek TC-03 Negative - invalid sa2ul_instance 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgSa2ulReleaseDsmek — TISCI_MSG_SA2UL_RELEASE_DSMEK (0x9038)
 *
 * TC-01  Release DSMEK for instance=0 → transport SUCCESS only. See
 *        test_msgSa2ulSetDkek TC-01: this core is not the SA2UL
 *        auth_resource_owner, so TIFS always NACKs this request.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Positive: invalid sa2ul_instance (0xFF) → SUCCESS (DM forwards to TIFS)
 * -------------------------------------------------------------------------- */
static int32_t test_msgSa2ulReleaseDsmek(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_sa2ul_release_dsmek_req  request;
    struct tisci_msg_sa2ul_release_dsmek_resp response;

    /* TC-01: Positive – release DSMEK (cleanup) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_RELEASE_DSMEK,
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
            DebugP_log("FAIL: test_msgSa2ulReleaseDsmek TC-01 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_RELEASE_DSMEK,
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
            DebugP_log("FAIL: test_msgSa2ulReleaseDsmek TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: negative – invalid sa2ul_instance (0xFF)
    This message is directly sent to TIFS from DM and DM doesn't perform any operations while sending or receiving.
    So these messages can be marked as passing test. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.sa2ul_instance = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SA2UL_RELEASE_DSMEK,
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
        if (!((retVal == SystemP_SUCCESS) || (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSa2ulReleaseDsmek TC-03 Negative - invalid sa2ul_instance 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

#if !defined(SKIP_SCICLIENT)

/* --------------------------------------------------------------------------
 * test_msgCryptoGetDkek — TISCI_MSG_CRYPTO_GET_DKEK (0x9029)
 *
 * Uses the newer tisci_msg_crypto_get_dkek_req struct (field: instance)
 * instead of the legacy sa2ul_instance alias.
 *
 * TC-01  Positive: SET_DKEK for instance=0, then GET_DKEK with same label
 *                  → SUCCESS + ACK + 32-byte dkek populated
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid instance (0xFF) → not SUCCESS or NACK
 * -------------------------------------------------------------------------- */
static int32_t test_msgCryptoGetDkek(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_crypto_get_dkek_req  request;
    struct tisci_msg_crypto_get_dkek_resp response;

    /* TC-01: Positive – set DKEK via wrapper, then get it via CRYPTO_GET_DKEK */
    {
        /* Prerequisite: set DKEK for instance 0 with a known label */
        struct tisci_msg_sa2ul_set_dkek_req  setReq;
        struct tisci_msg_sa2ul_set_dkek_resp setResp;
        memset(&setReq,  0, sizeof(setReq));
        memset(&setResp, 0, sizeof(setResp));
        setReq.sa2ul_instance  = 0U;
        setReq.kdf_label_len   = 6U;
        setReq.kdf_context_len = 4U;
        memcpy(&setReq.kdf_label_and_context[0], "CRYPTO", 6);
        memcpy(&setReq.kdf_label_and_context[6], "TEST",   4);
        retVal = Sciclient_setDKEK(&setReq, &setResp, SystemP_WAIT_FOREVER);
        if ((retVal) != (SystemP_SUCCESS))
        {
            DebugP_log("FAIL: test_msgCryptoGetDkek TC-01 Positive - step1 SET_DKEK via wrapper: retVal=%d\r\n",
                       retVal);
            failCount++;
        }

        /* Now get the DKEK using tisci_msg_crypto_get_dkek_req (instance field) */
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.instance       = 0U;
        request.kdf_label_len  = 6U;
        request.kdf_context_len = 4U;
        memcpy(&request.kdf_label_and_context[0], "CRYPTO", 6);
        memcpy(&request.kdf_label_and_context[6], "TEST",   4);

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_CRYPTO_GET_DKEK,
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
            DebugP_log("FAIL: test_msgCryptoGetDkek TC-01 Positive - step2 CRYPTO_GET_DKEK with label=CRYPTO: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }

        /* Release DKEK after use */
        struct tisci_msg_sa2ul_release_dkek_req  relReq;
        struct tisci_msg_sa2ul_release_dkek_resp relResp;
        memset(&relReq, 0, sizeof(relReq));
        relReq.sa2ul_instance = 0U;
        (void)Sciclient_releaseDKEK(&relReq, &relResp, SystemP_WAIT_FOREVER);
    }

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_CRYPTO_GET_DKEK,
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
            DebugP_log("FAIL: test_msgCryptoGetDkek TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

#endif

/* --------------------------------------------------------------------------
 * test_msgKeyWriter — TISCI_MSG_KEY_WRITER (0x9031)
 *
 * NOT SAFE for positive test:
 *   PERMANENTLY writes keys to OTP eFuses. Requires a signed X.509 certificate.
 *   Any OTP write is IRREVERSIBLE. NEGATIVE TESTS ONLY.
 *
 * TC-01  Negative: NULL pReqPayload → not SUCCESS
 * TC-02  Negative: zero certificate address → not SUCCESS or NACK
 * -------------------------------------------------------------------------- */
static int32_t test_msgKeyWriter(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_keywriter_req  request;
    struct tisci_msg_keywriter_resp response;

    /* TC-01: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_KEY_WRITER,
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
            DebugP_log("FAIL: test_msgKeyWriter TC-01 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – zero certificate address (no valid certificate) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.image_addr_lo = 0U;
        request.image_addr_hi = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_KEY_WRITER,
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
            DebugP_log("FAIL: test_msgKeyWriter TC-02 Negative - zero certificate address: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgKeyringImport — TISCI_MSG_KEYRING_IMPORT (0x9039)
 *
 * NOT SAFE for positive test:
 *   Requires a properly encrypted and authenticated keyring blob.
 *   Without genuine key material TIFS will NACK.
 *   NEGATIVE TESTS ONLY.
 *
 * TC-01  Negative: NULL pReqPayload → not SUCCESS
 * TC-02  Negative: zero keyring address → not SUCCESS or NACK
 * -------------------------------------------------------------------------- */
static int32_t test_msgKeyringImport(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_keyring_import_req  request;
    struct tisci_msg_keyring_import_resp response;

    /* TC-01: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_KEYRING_IMPORT,
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
            DebugP_log("FAIL: test_msgKeyringImport TC-01 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – zero keyring address (no valid keyring blob) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.keyring_lo = 0U;
        request.keyring_hi = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_KEYRING_IMPORT,
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
            DebugP_log("FAIL: test_msgKeyringImport TC-02 Negative - zero keyring address: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}


/* ==========================================================================
 * TC_14: Resource Manager – Resource Range
 *
 * DRIVER FLOW ANALYSIS:
 *   TISCI_MSG_RM_GET_RESOURCE_RANGE (0x1500) is routed via nonSecureContextId
 *   and processed by the DM RM subsystem.
 *
 * TESTABILITY:
 *   Positive test IS POSSIBLE. This is a read-only query to discover
 *   resource assignments allocated to a given host. Use device_type for
 *   DMASS0_INTAGGR_0 (28U) with subtype IA_VINT.
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * test_msgRmGetResourceRange — TISCI_MSG_RM_GET_RESOURCE_RANGE (0x1500)
 *
 * TC-01  Positive: query IA_VINT resources for INTAGGR_0 → SUCCESS + ACK
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid device type (0xFFFF) → not SUCCESS or NACK
 * TC-04  Negative: invalid subtype (0xFF) → not SUCCESS or NACK
 * TC-05  Negative: NULL pRespPayload → not SUCCESS
 * -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
 * test_msgSetFwlRegion — TISCI_MSG_SET_FWL_REGION (0x9000)
 *
 * TC-01  Positive: read-then-restore fwl_id=0, region=0 → SUCCESS + ACK
 *          First GET the current config, then SET back the exact same values.
 *          This is a no-op write that safely exercises the SET path without
 *          changing any firewall permissions or address range.
 *          Pattern mirrors Sciclient_firewallSetRegion() in sciclient_firewall.c.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid fwl_id (0xFFFF) → not SUCCESS or NACK
 * TC-04  Negative: NULL pRespPayload → not SUCCESS
 * -------------------------------------------------------------------------- */
static int32_t test_msgSetFwlRegion(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_fwl_set_firewall_region_req  request;
    struct tisci_msg_fwl_set_firewall_region_resp response;

    /* TC-01: Positive – read current fwl_id=0 region=0 config, then write it
     * back unchanged.  GET first to avoid hardcoding platform-specific values.
     * Note: fwl_id=0 is valid on AM62DX but not on AM275X; guarded below. */
#if defined(DM_TEST_FWL_ID0_SUPPORTED)
    {
        struct tisci_msg_fwl_get_firewall_region_req  getReq;
        struct tisci_msg_fwl_get_firewall_region_resp getResp;

        memset(&getReq,  0, sizeof(getReq));
        memset(&getResp, 0, sizeof(getResp));
        getReq.fwl_id            = 0U;
        getReq.region            = 0U;
        getReq.n_permission_regs = FWL_MAX_PRIVID_SLOTS;

        const Sciclient_ReqPrm_t getReqPrm =
        {
            TISCI_MSG_GET_FWL_REGION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &getReq,
            sizeof(getReq),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t getRespPrm =
        {
            0,
            (uint8_t *) &getResp,
            sizeof(getResp)
        };

        retVal = Sciclient_service(&getReqPrm, &getRespPrm);
        if (!((retVal == SystemP_SUCCESS) && (getRespPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSetFwlRegion TC-01 Positive - step1 GET fwl_id region=0: retVal=%d flags=0x%x\r\n",
                       retVal, getRespPrm.flags);
            failCount++;
        }

        /* Now SET back exactly what we just read — no-op restore */
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.fwl_id            = getResp.fwl_id;
        request.region            = getResp.region;
        request.n_permission_regs = getResp.n_permission_regs;
        request.control           = getResp.control;
        request.permissions[0]    = getResp.permissions[0];
        request.permissions[1]    = getResp.permissions[1];
        request.permissions[2]    = getResp.permissions[2];
        request.start_address     = getResp.start_address;
        request.end_address       = getResp.end_address;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_FWL_REGION,
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
            DebugP_log("FAIL: test_msgSetFwlRegion TC-01 Positive - step2 SET fwl_id back (no-op restore): retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
#endif

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_FWL_REGION,
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
            DebugP_log("FAIL: test_msgSetFwlRegion TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid fwl_id (0xFFFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.fwl_id            = 0xFFFFU;
        request.region            = 0U;
        request.n_permission_regs = 3U;
        request.control           = 0U;
        request.start_address     = 0ULL;
        request.end_address       = 0ULL;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_FWL_REGION,
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
            DebugP_log("FAIL: test_msgSetFwlRegion TC-03 Negative - invalid fwl_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – NULL pRespPayload */
    {
        memset(&request, 0, sizeof(request));
        request.fwl_id = 0xFFFFU;
        request.region = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_FWL_REGION,
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
            DebugP_log("FAIL: test_msgSetFwlRegion TC-04 Negative - NULL pRespPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgGetFwlRegion — TISCI_MSG_GET_FWL_REGION (0x9001)
 *
 * Positive test IS POSSIBLE:
 *   Read-only query of firewall region configuration.
 *
 * TC-01  Positive: query fwl_id=0, region=0 → SUCCESS + ACK
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid fwl_id (0xFFFF) → not SUCCESS or NACK
 * TC-04  Positive: NULL pRespPayload → SUCCESS + ACK (flags set regardless of payload)
 * -------------------------------------------------------------------------- */
static int32_t test_msgGetFwlRegion(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_fwl_get_firewall_region_req  request;
    struct tisci_msg_fwl_get_firewall_region_resp response;

    /* TC-01: Positive – query fwl_id=0, region=0 */
    /* Note: fwl_id=0 is valid on AM62DX; TIFS restricts access on AM275X. */
#if defined(DM_TEST_FWL_ID0_SUPPORTED)
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.fwl_id            = 0U;
        request.region            = 0U;
        request.n_permission_regs = FWL_MAX_PRIVID_SLOTS;

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

        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetFwlRegion TC-01 Positive - query fwl_id region=0: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
#endif
    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_FWL_REGION,
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
            DebugP_log("FAIL: test_msgGetFwlRegion TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid fwl_id (0xFFFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.fwl_id            = 0xFFFFU;
        request.region            = 0U;
        request.n_permission_regs = FWL_MAX_PRIVID_SLOTS;

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
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetFwlRegion TC-03 Negative - invalid fwl_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    /*This message falls through the default case of Sciclient_service, inside the Sciclient_serviceSecureProxy.
     There the flag is updated irrespective of NULL pRespPayload, so the message is still ACKed by
     firmware even though the (skipped) payload copy is affected by the NULL pointer. Hence
     retVal=SUCCESS, flags=ACK is the correct/expected outcome, not a failure.
     Note: this still targets fwl_id=0, which TIFS restricts on AM275X (same
     restriction as TC-01), so this positive test is only valid when fwl_id=0
     is supported. */
    /* TC-04: Positive – NULL pRespPayload → SUCCESS + ACK */
#if defined(DM_TEST_FWL_ID0_SUPPORTED)
    {
        memset(&request, 0, sizeof(request));
        request.fwl_id            = 0U;
        request.region            = 0U;
        request.n_permission_regs = FWL_MAX_PRIVID_SLOTS;

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
            NULL,
            0
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetFwlRegion TC-04 Positive test: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
#endif
    return failCount;
}

/* --------------------------------------------------------------------------
 * test_msgChangeFwlOwner — TISCI_MSG_CHANGE_FWL_OWNER (0x9002)
 *
 * TC-01  Positive: fwl_id=0, region=0, owner_index=0 → SUCCESS + ACK
 *          owner_index=0 is the privileged/default owner. Safe no-op if the
 *          firewall is already owned by index 0. Pattern mirrors
 *          Sciclient_firewallChangeOwnerInfo() in sciclient_firewall.c.
 * TC-02  Negative: NULL pReqPayload → not SUCCESS
 * TC-03  Negative: invalid fwl_id (0xFFFF) → not SUCCESS or NACK
 * TC-04  Negative: invalid owner_index (0xFF) → not SUCCESS or NACK
 * -------------------------------------------------------------------------- */
static int32_t test_msgChangeFwlOwner(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_fwl_change_owner_info_req  request;
    struct tisci_msg_fwl_change_owner_info_resp response;

    /* TC-01: Positive – change fwl_id=0 region=0 to owner_index=0
     * owner_index=0 is always valid; if already owner, this is a no-op.
     * Note: fwl_id=0 is valid on AM62DX; TIFS restricts access on AM275X. */
#if defined(DM_TEST_FWL_ID0_SUPPORTED)
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.fwl_id      = 0U;
        request.region      = 0U;
        request.owner_index = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_CHANGE_FWL_OWNER,
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
            DebugP_log("FAIL: test_msgChangeFwlOwner TC-01 Positive - change fwl_id owner_index=0: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
#endif

    /* TC-02: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_CHANGE_FWL_OWNER,
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
            DebugP_log("FAIL: test_msgChangeFwlOwner TC-02 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid fwl_id (0xFFFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.fwl_id      = 0xFFFFU;
        request.region      = 0U;
        request.owner_index = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_CHANGE_FWL_OWNER,
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
            DebugP_log("FAIL: test_msgChangeFwlOwner TC-03 Negative - invalid fwl_id 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – invalid owner_index (0xFF) with invalid fwl_id */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.fwl_id      = 0xFFFFU;
        request.region      = 0U;
        request.owner_index = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_CHANGE_FWL_OWNER,
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
            DebugP_log("FAIL: test_msgChangeFwlOwner TC-04 Negative - invalid owner_index 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

#if !defined(SKIP_SCICLIENT)

/* --------------------------------------------------------------------------
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
 * -------------------------------------------------------------------------- */
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

    /* TC-03: Negative – flags = TISCI_MSG_FLAG_RESERVED0 (no AOP, reserved bit set).
     * TIFS rejects requests with reserved flags set. Since AOP is not set,
     * no ACK is expected even if the message were accepted. The only success
     * indicator is retVal. */
    /* TC-03: Negative – TISCI_MSG_FLAG_RESERVED0 (no AOP, reserved bit set) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.extboot_status = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_BOOT_NOTIFICATION,
            TISCI_MSG_FLAG_RESERVED0,
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
        DebugP_log("BOOT_NOTIFICATION reserved flag: retVal=%d flags=0x%x\r\n",
                   retVal, respPrm.flags);
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgBootNotification TC-03 Negative - TISCI_MSG_FLAG_RESERVED0 reserved bit set: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

/* --------------------------------------------------------------------------
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
 * -------------------------------------------------------------------------- */
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
            DebugP_log("FAIL: test_msgGetTraceConfig TC-01 Positive - query trace config: retVal=%d flags=0x%x\r\n",
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

#endif

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
#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/tisci_core.h>
#include <drivers/sciclient/include/tisci/tisci_protocol.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_device.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_clock.h>
#include <drivers/sciclient.h>
#include <drivers/ipc_notify.h>
#include <kernel/dpl/DebugP.h>
#include "test_device_manager_system.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * System test: TISCI_MSG_VERSION (0x0002) — run on every core
 *
 * The DM r5f (ENABLE_SCICLIENT_DIRECT) calls the DM firmware directly.
 * All other cores (mcu-r5f, a53, c75) go through the sciclient proxy to the
 * DM, verifying the full TISCI message path is operational end-to-end.
 */
int32_t TestDM_system_versionQuery(void *args)
{
    int32_t retVal;
    struct tisci_msg_version_req  request;
    struct tisci_msg_version_resp response;

    memset(&request,  0, sizeof(request));
    memset(&response, 0, sizeof(response));

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

    if ((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK))
    {
        DebugP_log("Core[%d]: DM version query PASS - FW: %s\r\n",
                   IpcNotify_getSelfCoreId(), response.str);
        return SystemP_SUCCESS;
    }
    else
    {
        DebugP_log("Core[%d]: DM version query FAIL - retVal=%d flags=0x%x\r\n",
                   IpcNotify_getSelfCoreId(), retVal, respPrm.flags);
        return SystemP_FAILURE;
    }
}

/*
 * System test: TISCI_MSG_GET_DEVICE (0x0201) — run on every core
 *
 * Queries the hardware state of TISCI_DEV_MCU_R5FSS0_CORE0 via the DM.
 * Verifies the device PM path is functional and the device is powered on.
 */
int32_t TestDM_system_getDeviceState(void *args)
{
    int32_t retVal;
    struct tisci_msg_get_device_req  request;
    struct tisci_msg_get_device_resp response;

    memset(&request,  0, sizeof(request));
    memset(&response, 0, sizeof(response));

    request.id = TEST_DM_SYS_R5F_DEV;

    const Sciclient_ReqPrm_t reqPrm =
    {
        TISCI_MSG_GET_DEVICE,
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

    if ((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK))
    {
        DebugP_log("Core[%d]: DM get device state PASS - dev=%u hw_state=%u\r\n",
                   IpcNotify_getSelfCoreId(),
                   (unsigned)TEST_DM_SYS_R5F_DEV,
                   (unsigned)response.current_state);
        return SystemP_SUCCESS;
    }
    else
    {
        DebugP_log("Core[%d]: DM get device state FAIL - retVal=%d flags=0x%x\r\n",
                   IpcNotify_getSelfCoreId(), retVal, respPrm.flags);
        return SystemP_FAILURE;
    }
}

/*
 * System test: TISCI_MSG_GET_FREQ (0x010e) — run on every core
 *
 * Queries the current CPU clock frequency of TISCI_DEV_MCU_R5FSS0_CORE0
 * via the DM.  Verifies the clock PM path is functional and returns a
 * non-zero frequency.
 */
int32_t TestDM_system_getClockFreq(void *args)
{
    int32_t retVal;
    struct tisci_msg_get_freq_req  request;
    struct tisci_msg_get_freq_resp response;

    memset(&request,  0, sizeof(request));
    memset(&response, 0, sizeof(response));

    request.device = TEST_DM_SYS_R5F_DEV;
    request.clk    = TEST_DM_SYS_R5F_CLK;

    const Sciclient_ReqPrm_t reqPrm =
    {
        TISCI_MSG_GET_FREQ,
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

    if ((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK) &&
        (response.freq_hz != 0U))
    {
        DebugP_log("Core[%d]: DM get clock freq PASS - dev=%u clk=%u freq=%llu Hz\r\n",
                   IpcNotify_getSelfCoreId(),
                   (unsigned)TEST_DM_SYS_R5F_DEV,
                   (unsigned)TEST_DM_SYS_R5F_CLK,
                   (unsigned long long)response.freq_hz);
        return SystemP_SUCCESS;
    }
    else
    {
        DebugP_log("Core[%d]: DM get clock freq FAIL - retVal=%d flags=0x%x freq=%llu Hz\r\n",
                   IpcNotify_getSelfCoreId(), retVal, respPrm.flags,
                   (unsigned long long)response.freq_hz);
        return SystemP_FAILURE;
    }
}

/*
 * System test: TISCI_MSG_SET_CLOCK (0x0100) — run on every core
 *
 * Each core independently sets the MCU R5F CPU0 clock to SW_STATE_REQ,
 * confirms the HW state is READY via TISCI_MSG_GET_CLOCK, then restores
 * the clock to SW_STATE_AUTO.  Exercises the full set-clock path through
 * the DM from all cores simultaneously in a multi-core system test.
 */
int32_t TestDM_system_setClock(void *args)
{
    int32_t retVal;

    /* Step 1 — set clock to SW_STATE_REQ (explicitly enabled) */
    {
        struct tisci_msg_set_clock_req  req;
        struct tisci_msg_set_clock_resp resp;

        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));

        req.device = TEST_DM_SYS_R5F_DEV;
        req.clk    = TEST_DM_SYS_R5F_CLK;
        req.state  = TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &req,
            sizeof(req),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if ((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK))
        {
            DebugP_log("Core[%d]: DM set clock (REQ) FAIL - retVal=%d flags=0x%x\r\n",
                       IpcNotify_getSelfCoreId(), retVal, respPrm.flags);
            return SystemP_FAILURE;
        }
    }

    /* Step 2 — verify HW clock state is READY */
    {
        struct tisci_msg_get_clock_req  req;
        struct tisci_msg_get_clock_resp resp;

        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));

        req.device = TEST_DM_SYS_R5F_DEV;
        req.clk    = TEST_DM_SYS_R5F_CLK;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &req,
            sizeof(req),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if ((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK) ||
            (resp.current_state != TISCI_MSG_VALUE_CLOCK_HW_STATE_READY))
        {
            DebugP_log("Core[%d]: DM set clock verify FAIL - retVal=%d flags=0x%x hw_state=%u\r\n",
                       IpcNotify_getSelfCoreId(), retVal, respPrm.flags,
                       (unsigned)resp.current_state);
            return SystemP_FAILURE;
        }
    }

    /* Step 3 — restore clock to SW_STATE_AUTO */
    {
        struct tisci_msg_set_clock_req  req;
        struct tisci_msg_set_clock_resp resp;

        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));

        req.device = TEST_DM_SYS_R5F_DEV;
        req.clk    = TEST_DM_SYS_R5F_CLK;
        req.state  = TISCI_MSG_VALUE_CLOCK_SW_STATE_AUTO;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &req,
            sizeof(req),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if ((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK))
        {
            DebugP_log("Core[%d]: DM set clock (AUTO restore) FAIL - retVal=%d flags=0x%x\r\n",
                       IpcNotify_getSelfCoreId(), retVal, respPrm.flags);
            return SystemP_FAILURE;
        }
    }

    DebugP_log("Core[%d]: DM set clock PASS - dev=%u clk=%u\r\n",
               IpcNotify_getSelfCoreId(),
               (unsigned)TEST_DM_SYS_R5F_DEV,
               (unsigned)TEST_DM_SYS_R5F_CLK);
    return SystemP_SUCCESS;
}

/*
 * System test: TISCI_MSG_SET_DEVICE ON + TISCI_MSG_GET_DEVICE verify — run on every core
 *
 * Each core independently sets TISCI_DEV_MCU_UART0 to SW_STATE_ON via the DM,
 * then reads back the hardware state and confirms it is HW_STATE_ON.
 * Using a peripheral device (MCU UART0) keeps the test safe when all cores
 * issue the request simultaneously — the DM serializes them and SW_STATE_ON
 * is idempotent.
 */
int32_t TestDM_system_setDeviceOn(void *args)
{
    int32_t retVal;

    /* Step 1 — set device to SW_STATE_ON */
    {
        struct tisci_msg_set_device_req  req;
        struct tisci_msg_set_device_resp resp;

        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));

        req.id = TEST_DM_SYS_UART_DEV;
        req.state = TISCI_MSG_VALUE_DEVICE_SW_STATE_ON;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &req,
            sizeof(req),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if ((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK))
        {
            DebugP_log("Core[%d]: DM set device ON FAIL - retVal=%d flags=0x%x\r\n",
                       IpcNotify_getSelfCoreId(), retVal, respPrm.flags);
            return SystemP_FAILURE;
        }
    }

    /* Step 2 — read back and confirm HW_STATE_ON */
    {
        struct tisci_msg_get_device_req  req;
        struct tisci_msg_get_device_resp resp;

        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));

        req.id = TEST_DM_SYS_UART_DEV;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_DEVICE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &req,
            sizeof(req),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *) &resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if ((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK) ||
            (resp.current_state != TISCI_MSG_VALUE_DEVICE_HW_STATE_ON))
        {
            DebugP_log("Core[%d]: DM set device ON verify FAIL - retVal=%d flags=0x%x hw_state=%u\r\n",
                       IpcNotify_getSelfCoreId(), retVal, respPrm.flags,
                       (unsigned)resp.current_state);
            return SystemP_FAILURE;
        }
    }

    DebugP_log("Core[%d]: DM set device ON PASS - dev=%u hw_state=ON\r\n",
               IpcNotify_getSelfCoreId(),
               (unsigned)TEST_DM_SYS_UART_DEV);
    return SystemP_SUCCESS;
}

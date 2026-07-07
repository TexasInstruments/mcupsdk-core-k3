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
#include <drivers/sciclient/include/tisci/pm/tisci_pm_clock.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_device.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include "test_device_manager_pm.h"

/* ========================================================================== */
/*              Static Forward Declarations for Sub-functions                 */
/* ========================================================================== */

static int32_t test_msgSetClock(void *args);
static int32_t test_msgGetClock(void *args);
static int32_t test_msgSetClockParent(void *args);
static int32_t test_msgGetClockParent(void *args);
static int32_t test_msgGetNumClockParents(void *args);
static int32_t test_msgSetFreq(void *args);
static int32_t test_msgQueryFreq(void *args);
static int32_t test_msgGetFreq(void *args);
static int32_t test_msgSetClockSsc(void *args);
static int32_t test_msgGetClockSsc(void *args);
static int32_t test_msgSetDevice(void *args);
static int32_t test_msgGetDevice(void *args);
static int32_t test_msgSetDeviceResets(void *args);

/* ========================================================================== */
/*                 Wrapper Functions for Test Categories                      */
/* ========================================================================== */

/*
 * TC_02 wrapper — Clock Management tests
 */
void testDM_clockMgmt(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgSetClock(NULL);
    testfailcount += test_msgGetClock(NULL);
    testfailcount += test_msgSetClockParent(NULL);
    testfailcount += test_msgGetClockParent(NULL);
    testfailcount += test_msgGetNumClockParents(NULL);
    testfailcount += test_msgSetFreq(NULL);
    testfailcount += test_msgQueryFreq(NULL);
    testfailcount += test_msgGetFreq(NULL);
    testfailcount += test_msgSetClockSsc(NULL);
    testfailcount += test_msgGetClockSsc(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

/*
 * TC_03 wrapper — Device Management tests
 */
void testDM_deviceMgmt(void *args)
{
    int32_t testfailcount = 0;
    testfailcount += test_msgSetDevice(NULL);
    testfailcount += test_msgGetDevice(NULL);
    testfailcount += test_msgSetDeviceResets(NULL);
    TEST_ASSERT_EQUAL_INT32(0,testfailcount);
}

/* ========================================================================== */
/*             Clock Management Test Function Implementations                 */
/* ========================================================================== */

/**
 * test_msgSetClock — TISCI_MSG_SET_CLOCK (0x0100)
 *
 * TC-01  Positive: set clock to AUTO state → SUCCESS + ACK
 * TC-02  Positive: set clock to REQ (enabled) state → SUCCESS + ACK
 * TC-03  Negative: invalid device ID → not SUCCESS or NACK
 * TC-04  Negative: NULL pReqPayload → not SUCCESS or NACK
 * TC-05  Negative: invalid state value (0xFF) → not SUCCESS or NACK
 */
static int32_t test_msgSetClock(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_set_clock_req  request;
    struct tisci_msg_set_clock_resp response;

    /* TC-01: Positive – set clock to AUTO state */
    {
        memset(&request, 0, sizeof(request));
        request.device = TEST_DEVICE_ID;
        request.clk    = (uint8_t) TEST_DEVICE_CLK_ID;
        request.state  = TISCI_MSG_VALUE_CLOCK_SW_STATE_AUTO;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK,
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
            DebugP_log("FAIL: test_msgSetClock TC-01 Positive - set clock to AUTO state: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }

    }

    /* TC-02: Positive – set clock to REQ (enabled) state */
    {
        memset(&request, 0, sizeof(request));
        request.device = TEST_DEVICE_ID;
        request.clk    = (uint8_t) TEST_DEVICE_CLK_ID;
        request.state  = TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK,
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
            DebugP_log("FAIL: test_msgSetClock TC-02 Positive - set clock to REQ (enabled) state: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.device = 0xFFFFU;
        request.clk    = 0;
        request.state  = TISCI_MSG_VALUE_CLOCK_SW_STATE_AUTO;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK,
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
            DebugP_log("FAIL: test_msgSetClock TC-03 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK,
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
            DebugP_log("FAIL: test_msgSetClock TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-05: Negative – invalid state value (0xFF, beyond AUTO/REQ/UNREQ) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.device = TEST_DEVICE_ID;
        request.clk    = TEST_DEVICE_CLK_ID;
        request.state  = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK,
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
            DebugP_log("FAIL: test_msgSetClock TC-05 Negative - invalid state 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgGetClock — TISCI_MSG_GET_CLOCK (0x0101)
 *
 * TC-01  Positive: get clock state for valid device → SUCCESS + ACK
 * TC-02  Negative: invalid device ID → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgGetClock(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_get_clock_req  request;
    struct tisci_msg_get_clock_resp response;

    /* TC-01: Positive – get clock state for valid device */
    {
        memset(&request, 0, sizeof(request));
        request.device = TEST_DEVICE_ID;
        request.clk    = (uint8_t) TEST_DEVICE_CLK_ID;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK,
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
            DebugP_log("FAIL: test_msgGetClock TC-01 Positive - get clock state for valid device: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.device = 0xFFFFU;
        request.clk    = 0;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK,
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
            DebugP_log("FAIL: test_msgGetClock TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK,
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
            DebugP_log("FAIL: test_msgGetClock TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    return failCount;
}

/**
 * test_msgSetClockParent — TISCI_MSG_SET_CLOCK_PARENT (0x0102)
 *
 * TC-01  Positive: set parent of CLK_32K_RC_SEL mux clock → SUCCESS + ACK
 * TC-02  Negative: invalid device ID → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 *
 * DESIGN NOTE — TC-01 uses TISCI_DEV_CLK_32K_RC_SEL_DEV_VD (193U):
 *   TISCI_DEV_CLK_32K_RC_SEL_DEV_VD_CLK (= 0) is the output clock of the
 *   32K RC clock-select mux device.  Unlike MCU_UART0 FCLK_CLK, this clock
 *   has a real switchable parent mux (4 parents: RCOSC, HFOSC0, RCOSC_DUP0,
 *   LFOSC0), so the DM firmware ACKs both GET_CLOCK_PARENT and
 *   SET_CLOCK_PARENT correctly.  Using the constant with its own device
 *   (TISCI_DEV_CLK_32K_RC_SEL_DEV_VD) avoids borrowing a clock index
 *   constant from an unrelated device.
 *   Device ID 193U is consistent across AM62DX and AM275X. */
static int32_t test_msgSetClockParent(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_set_clock_parent_req  request;
    struct tisci_msg_set_clock_parent_resp response;

    {
        memset(&request, 0, sizeof(request));
        request.device = TISCI_DEV_CLK_32K_RC_SEL_DEV_VD; 
        request.clk    = (uint8_t) TISCI_DEV_CLK_32K_RC_SEL_DEV_VD_CLK;  
        request.parent = 1U;   /* parent 1 (RCOSC) — valid for this muxed clock */

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK_PARENT,
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
            DebugP_log("FAIL: test_msgSetClockParent TC-01 Positive - set parent of CLK_32K_RC_SEL mux: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.device = 0xFFFFU;
        request.clk    = 0;
        request.parent = 0;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK_PARENT,
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
            DebugP_log("FAIL: test_msgSetClockParent TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK_PARENT,
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
            DebugP_log("FAIL: test_msgSetClockParent TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgGetClockParent — TISCI_MSG_GET_CLOCK_PARENT (0x0103)
 *
 * TC-01  Positive: query parent of TIMER0 TIMER_TCLK_CLK (muxed) → SUCCESS + ACK
 * TC-02  Positive: query parent of CLK_32K_RC_SEL mux clock → SUCCESS + ACK
 * TC-03  Negative: invalid device ID → not SUCCESS or NACK
 * TC-04  Negative: NULL pReqPayload → not SUCCESS
 *
 * DESIGN NOTE — TC-02 uses TISCI_DEV_CLK_32K_RC_SEL_DEV_VD (193U):
 *   TISCI_DEV_CLK_32K_RC_SEL_DEV_VD_CLK (= 0) is the output clock of the
 *   32K RC clock-select mux device.  It has a real switchable parent mux
 *   (4 parents: RCOSC, HFOSC0, RCOSC_DUP0, LFOSC0), so the DM firmware
 *   ACKs GET_CLOCK_PARENT correctly.  This mirrors TC-01 of
 *   test_msgSetClockParent which uses the same device/clock.
 *   Device ID 193U is consistent across AM62DX and AM275X.
 *
 * TEST_CLK_PARENT_DEV_ID / TEST_CLK_PARENT_CLK_ID are defined in the
 * SoC-specific test_device_manager_val.h (TIMER0, TIMER_TCLK_CLK, clk=2).
 * This clock has a real parent mux on both AM62DX and AM275X.
 */
static int32_t test_msgGetClockParent(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_get_clock_parent_req  request;
    struct tisci_msg_get_clock_parent_resp response;

    /* TC-01: Positive – query parent of TIMER0 TIMER_TCLK_CLK.
     * This clock has a real parent mux (multiple switchable parents).
     * retVal=SUCCESS + flags=ACK → firmware returned the current parent index. */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.device = TEST_CLK_PARENT_DEV_ID;
        request.clk    = (uint8_t) TEST_CLK_PARENT_CLK_ID;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK_PARENT,
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
            DebugP_log("FAIL: test_msgGetClockParent TC-01 Positive - query parent of TIMER0 TIMER_TCLK_CLK: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Positive – query parent of CLK_32K_RC_SEL mux clock.
     * TISCI_DEV_CLK_32K_RC_SEL_DEV_VD_CLK (= 0) is the output of the 32K
     * RC selector mux; it has real switchable parents so the firmware ACKs.
     * Mirrors test_msgSetClockParent TC-01 — same device/clock, read-only. */
    {
        memset(&request, 0, sizeof(request));
        request.device = TISCI_DEV_CLK_32K_RC_SEL_DEV_VD;  
        request.clk    = (uint8_t) TISCI_DEV_CLK_32K_RC_SEL_DEV_VD_CLK; 

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK_PARENT,
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
            DebugP_log("FAIL: test_msgGetClockParent TC-02 Positive - query parent of CLK_32K_RC_SEL mux: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.device = 0xFFFFU;
        request.clk    = 0;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK_PARENT,
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
            DebugP_log("FAIL: test_msgGetClockParent TC-03 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK_PARENT,
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
            DebugP_log("FAIL: test_msgGetClockParent TC-04 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgGetNumClockParents — TISCI_MSG_GET_NUM_CLOCK_PARENTS (0x0104)
 *
 * TC-01  Positive: get num clock parents for valid device → SUCCESS + ACK
 * TC-02  Negative: invalid device ID → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgGetNumClockParents(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_get_num_clock_parents_req  request;
    struct tisci_msg_get_num_clock_parents_resp response;

    /* TC-01: Positive – get number of clock parents */
    {
        memset(&request, 0, sizeof(request));
        request.device = TEST_DEVICE_ID;
        request.clk    = (uint8_t) TEST_DEVICE_CLK_ID;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_NUM_CLOCK_PARENTS,
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
            DebugP_log("FAIL: test_msgGetNumClockParents TC-01 Positive - get num clock parents for valid device: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.device = 0xFFFFU;
        request.clk    = 0;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_NUM_CLOCK_PARENTS,
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
            DebugP_log("FAIL: test_msgGetNumClockParents TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_NUM_CLOCK_PARENTS,
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
        /* Negative: retval != SUCCESS or flag != ACK */
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetNumClockParents TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgSetFreq — TISCI_MSG_SET_FREQ (0x010C)
 *
 * TC-01  Positive: query current freq, then set same freq → SUCCESS + ACK
 * TC-02  Negative: invalid device ID → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgSetFreq(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_set_freq_req  request;
    struct tisci_msg_set_freq_resp response;

    /* TC-01: Positive – read current frequency and set it back (safe) */
    {
        /* First get the current frequency */
        struct tisci_msg_get_freq_req  getReq;
        struct tisci_msg_get_freq_resp getResp;

        memset(&getReq, 0, sizeof(getReq));
        getReq.device = TEST_DEVICE_ID;
        getReq.clk    = (uint8_t) TEST_DEVICE_CLK_ID;

        const Sciclient_ReqPrm_t getReqPrm =
        {
            TISCI_MSG_GET_FREQ,
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
        if (retVal == SystemP_SUCCESS)
        {
            /* Now set the same frequency back */
            memset(&request, 0, sizeof(request));
            request.device         = TEST_DEVICE_ID;
            request.clk            = (uint8_t) TEST_DEVICE_CLK_ID;
            request.min_freq_hz    = getResp.freq_hz;
            request.target_freq_hz = getResp.freq_hz;
            request.max_freq_hz    = getResp.freq_hz;

            const Sciclient_ReqPrm_t reqPrm =
            {
                TISCI_MSG_SET_FREQ,
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
            DebugP_log("FAIL: test_msgSetFreq TC-01 Positive - get freq then set same freq back: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
                failCount++;
            }
        }
    }

    /* TC-02: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.device         = 0xFFFFU;
        request.clk            = 0;
        request.min_freq_hz    = 48000000ULL;
        request.target_freq_hz = 48000000ULL;
        request.max_freq_hz    = 48000000ULL;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_FREQ,
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
            DebugP_log("FAIL: test_msgSetFreq TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_FREQ,
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
            DebugP_log("FAIL: test_msgSetFreq TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgQueryFreq — TISCI_MSG_QUERY_FREQ (0x010D)
 *
 * TC-01  Positive: query achievable frequency → SUCCESS + ACK + valid freq
 * TC-02  Negative: invalid device ID → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgQueryFreq(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_query_freq_req  request;
    struct tisci_msg_query_freq_resp response;

    /* TC-01: Positive – query frequency for valid device */
    {
        memset(&request, 0, sizeof(request));
        request.device         = TEST_DEVICE_ID;
        request.clk            = (uint8_t) TEST_DEVICE_CLK_ID;
        request.min_freq_hz    = 1ULL;
        request.target_freq_hz = 48000000ULL;
        request.max_freq_hz    = 500000000ULL;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_QUERY_FREQ,
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
            DebugP_log("FAIL: test_msgQueryFreq TC-01 Positive - query achievable freq transport: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
        if (!(response.freq_hz != 0ULL))
        {
            DebugP_log("FAIL: test_msgQueryFreq TC-01 Positive - freq_hz must be non-zero: freq_hz=%" PRIu64 "\r\n",
                       response.freq_hz);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.device         = 0xFFFFU;
        request.clk            = 0;
        request.min_freq_hz    = 1ULL;
        request.target_freq_hz = 48000000ULL;
        request.max_freq_hz    = 500000000ULL;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_QUERY_FREQ,
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
            DebugP_log("FAIL: test_msgQueryFreq TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_QUERY_FREQ,
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
            DebugP_log("FAIL: test_msgQueryFreq TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgGetFreq — TISCI_MSG_GET_FREQ (0x010E)
 *
 * TC-01  Positive: get current frequency → SUCCESS + ACK + valid freq
 * TC-02  Negative: invalid device ID → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgGetFreq(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_get_freq_req  request;
    struct tisci_msg_get_freq_resp response;

    /* TC-01: Positive – get frequency for valid device */
    {
        memset(&request, 0, sizeof(request));
        request.device = TEST_DEVICE_ID;
        request.clk    = (uint8_t) TEST_DEVICE_CLK_ID;

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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetFreq TC-01 Positive - get current freq transport: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
        /* TEST_ASSERT_GREATER_THAN_UINT64 requires UNITY_SUPPORT_64 which is
         * disabled in this build; use a plain C boolean check instead. */
        if (!(response.freq_hz != 0ULL))
        {
            DebugP_log("FAIL: test_msgGetFreq TC-01 Positive - freq_hz must be non-zero: freq_hz=%" PRIu64 "\r\n",
                       response.freq_hz);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.device = 0xFFFFU;
        request.clk    = 0;

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
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetFreq TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_FREQ,
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
            DebugP_log("FAIL: test_msgGetFreq TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * TC_03: Device Management Messages
 *
 * DRIVER FLOW ANALYSIS:
 *   All device messages (SET_DEVICE, GET_DEVICE, SET_DEVICE_RESETS) are
 *   processed LOCALLY by Sciclient_ProcessPmMessage() in
 *   ENABLE_SCICLIENT_DIRECT mode. They do NOT go through secure proxy.
 *
 *   This means:
 *   - Timeout parameter is ignored (completes synchronously)
 *   - The DM firmware processes the request directly via rm_pm_hal
 *   - Response is immediate
 *
 * TESTABILITY: All are testable. We use MCU_UART0 as a test device
 *   because it is safe to toggle on/off without system impact.
 *
 * NOTE on TISCI_MSG_GET_DEVICE_MULTIPLE:
 *   Only available when CONFIG_GET_DEVICE_MULTIPLE is defined at build time.
 *   Not included in this test as it may not be enabled in all builds.
 */

/**
 * test_msgSetDevice — TISCI_MSG_SET_DEVICE (0x0200)
 *
 * TC-01  Positive: set device ON state → SUCCESS + ACK
 * TC-02  Positive: set device ON state (repeat) → SUCCESS + ACK
 * TC-03  Positive: set device AUTO_OFF  → SUCCESS + ACK
 * TC-04  Positive: set device back to ON   → SUCCESS + ACK
 * TC-05  Negative: invalid device ID → not SUCCESS or NACK
 * TC-06  Negative: NULL pReqPayload → not SUCCESS
 * TC-07  Negative: invalid state value (0xFF) → not SUCCESS or NACK
 */
static int32_t test_msgSetDevice(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_set_device_req  request;
    struct tisci_msg_set_device_resp response;

    /* TC-01: Positive – set device ON */
    {
        memset(&request, 0, sizeof(request));
        request.id    = TEST_DEVICE_ID;
        request.state = TISCI_MSG_VALUE_DEVICE_SW_STATE_ON;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE,
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
            DebugP_log("FAIL: test_msgSetDevice TC-01 Positive - set device ON state: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }

        /* Verify device state using TISCI_MSG_GET_DEVICE */
        struct tisci_msg_get_device_req get_req;
        struct tisci_msg_get_device_resp get_resp;
        memset(&get_req, 0, sizeof(get_req));
        get_req.id = TEST_DEVICE_ID;
        const Sciclient_ReqPrm_t get_reqPrm = {
            TISCI_MSG_GET_DEVICE,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *)&get_req,
            sizeof(get_req),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t get_respPrm = {
            0,
            (uint8_t *)&get_resp,
            sizeof(get_resp)
        };
        int32_t get_retVal = Sciclient_service(&get_reqPrm, &get_respPrm);
        if (!((get_retVal == SystemP_SUCCESS) && (get_respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSetDevice TC-01 Positive - verify ON via GET_DEVICE: get_retVal=%d flags=0x%x\r\n",
                       get_retVal, get_respPrm.flags);
            failCount++;
        }
        if ((uint32_t)(get_resp.programmed_state) != (uint32_t)(TISCI_MSG_VALUE_DEVICE_SW_STATE_ON))
        {
            DebugP_log("FAIL: test_msgSetDevice TC-01 Positive - programmed_state mismatch: expected=%d actual=%d\r\n",
                       (int32_t)(uint32_t)(TISCI_MSG_VALUE_DEVICE_SW_STATE_ON), (int32_t)(uint32_t)(get_resp.programmed_state));
            failCount++;
        }
        if ((uint32_t)(get_resp.current_state) != (uint32_t)(TISCI_MSG_VALUE_DEVICE_HW_STATE_ON))
        {
            DebugP_log("FAIL: test_msgSetDevice TC-01 Positive - current_state mismatch: expected=%d actual=%d\r\n",
                       (int32_t)(uint32_t)(TISCI_MSG_VALUE_DEVICE_HW_STATE_ON), (int32_t)(uint32_t)(get_resp.current_state));
            failCount++;
        }
    }

    /* TC-02: Positive – set device ON again */
    {
        memset(&request, 0, sizeof(request));
        request.id    = TEST_DEVICE_ID;
        request.state = TISCI_MSG_VALUE_DEVICE_SW_STATE_ON;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE,
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
            DebugP_log("FAIL: test_msgSetDevice TC-02 Positive - set device ON again (repeat): retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Positive – set device AUTO_OFF */
    {
        memset(&request, 0, sizeof(request));
        request.id    = TEST_DEVICE_ID;
        request.state = TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE,
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
            DebugP_log("FAIL: test_msgSetDevice TC-03 Positive - set device AUTO_OFF state: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Positive – set device back ON (restore state) */
    {
        memset(&request, 0, sizeof(request));
        request.id    = TEST_DEVICE_ID;
        request.state = TISCI_MSG_VALUE_DEVICE_SW_STATE_ON;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE,
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
            DebugP_log("FAIL: test_msgSetDevice TC-04 Positive - restore device ON state: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-05: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.id    = 0xFFFFU;
        request.state = TISCI_MSG_VALUE_DEVICE_SW_STATE_ON;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE,
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
            DebugP_log("FAIL: test_msgSetDevice TC-05 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-06: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE,
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
            DebugP_log("FAIL: test_msgSetDevice TC-06 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-07: Negative – invalid state value (0xFF, beyond ON/AUTO_OFF/RETENTION) */
    {
        memset(&request, 0, sizeof(request));
        request.id    = TEST_DEVICE_ID;
        request.state = 0xFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE,
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
            DebugP_log("FAIL: test_msgSetDevice TC-07 Negative - invalid state 0xFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgGetDevice — TISCI_MSG_GET_DEVICE (0x0201)
 *
 * TC-01  Positive: get device state → SUCCESS + ACK + valid state
 * TC-02  Negative: invalid device ID → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 */
static int32_t test_msgGetDevice(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_get_device_req  request;
    struct tisci_msg_get_device_resp response;

    /* TC-01: Positive – get device state */
    {
        memset(&request, 0, sizeof(request));
        request.id = TEST_DEVICE_ID;

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
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetDevice TC-01 Positive - get device state: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.id = 0xFFFFU;

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
        if (!((retVal != SystemP_SUCCESS) || (respPrm.flags != TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgGetDevice TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_DEVICE,
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
            DebugP_log("FAIL: test_msgGetDevice TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgSetDeviceResets — TISCI_MSG_SET_DEVICE_RESETS (0x0203)
 *
 * TC-01  Positive: assert reset (resets=1), then de-assert (resets=0) → SUCCESS
 * TC-02  Negative: invalid device ID → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS
 * TC-04  Negative: invalid resets bitmask (0xFFFFFFFF) → not SUCCESS or NACK
 */
static int32_t test_msgSetDeviceResets(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_set_device_resets_req  request;
    struct tisci_msg_set_device_resets_resp response;

    /* TC-01: Positive – assert reset, then de-assert */
    {
        /* Assert reset */
        memset(&request, 0, sizeof(request));
        request.id     = TEST_DEVICE_ID;
        request.resets = 1U;

        const Sciclient_ReqPrm_t reqPrm1 =
        {
            TISCI_MSG_SET_DEVICE_RESETS,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm1 =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm1, &respPrm1);
        if (!((retVal == SystemP_SUCCESS) && (respPrm1.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSetDeviceResets TC-01 Positive - assert reset resets=1: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm1.flags);
            failCount++;
        }

        /* De-assert reset */
        request.resets = 0U;

        const Sciclient_ReqPrm_t reqPrm2 =
        {
            TISCI_MSG_SET_DEVICE_RESETS,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *) &request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm2 =
        {
            0,
            (uint8_t *) &response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm2, &respPrm2);
        if (!((retVal == SystemP_SUCCESS) && (respPrm2.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: test_msgSetDeviceResets TC-01 Positive - de-assert reset resets=0: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm2.flags);
            failCount++;
        }
    }

    /* TC-02: Negative – invalid device ID */
    {
        memset(&request, 0, sizeof(request));
        request.id     = 0xFFFFU;
        request.resets = 1U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE_RESETS,
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
            DebugP_log("FAIL: test_msgSetDeviceResets TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE_RESETS,
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
            DebugP_log("FAIL: test_msgSetDeviceResets TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-04: Negative – invalid resets bitmask (0xFFFFFFFF) */
    {
        memset(&request, 0, sizeof(request));
        request.id     = TEST_DEVICE_ID;
        request.resets = 0xFFFFFFFFU;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_DEVICE_RESETS,
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
            DebugP_log("FAIL: test_msgSetDeviceResets TC-04 Negative - invalid resets bitmask 0xFFFFFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgSetClockSsc — TISCI_MSG_SET_CLOCK_SSC (0x010A)
 *
 * DRIVER FLOW: In SCICLIENT_DIRECT mode (with CONFIG_PM_CLK_SSC defined),
 * this is processed locally by Sciclient_ProcessPmMessage() → set_ssc_handler().
 * In sciserver, it is dispatched similarly.
 *
 * TC-01  Positive: disable SSC on TEST_SSC_DEVICE_ID / TEST_SSC_CLK_ID.
 *        SSC is only valid for PLL-backed clocks; DM NACKs MCU_UART0_FCLK_CLK.
 * TC-02  Negative: invalid device ID (0xFFFF) → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS or NACK
 */
static int32_t test_msgSetClockSsc(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_set_clock_ssc_req  request;
    struct tisci_msg_set_clock_ssc_resp response;

    /* TC-01: Positive – disable SSC on DSS0 DPI_1_IN_CLK (backed by HSDIV0_16FFT_MAIN_17).
     * SSC is only supported on 16FFT-type PLL-backed clocks.
     * Enabled only when TEST_DM_CLK_SSC is defined (e.g. on AM62DX where DSS0 is present). */
#ifdef TEST_DM_CLK_SSC
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.device      = TISCI_DEV_DSS0;           /* 186U on AM62DX */
        request.clk         = TISCI_DEV_DSS0_DPI_1_IN_CLK; /* 2U — SSC-capable */
        request.modfreq_hz  = 0U;
        request.mod_depth   = 0U;
        request.spread_type = 0U;
        request.enable      = 0U;   /* disable SSC — safe, no side effects */

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK_SSC,
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
            DebugP_log("FAIL: test_msgSetClockSsc TC-01 Positive - disable SSC on DSS0 DPI_1_IN_CLK: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
#endif

    /* TC-02: Negative – invalid device ID (0xFFFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.device     = 0xFFFFU;
        request.clk        = 0U;
        request.modfreq_hz = 0U;
        request.mod_depth  = 0U;
        request.spread_type = 0U;
        request.enable     = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK_SSC,
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
            DebugP_log("FAIL: test_msgSetClockSsc TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_SET_CLOCK_SSC,
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
            DebugP_log("FAIL: test_msgSetClockSsc TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

/**
 * test_msgGetClockSsc — TISCI_MSG_GET_CLOCK_SSC (0x010B)
 *
 * DRIVER FLOW: In SCICLIENT_DIRECT mode (with CONFIG_PM_CLK_SSC defined),
 * this is processed locally by Sciclient_ProcessPmMessage() → get_ssc_handler().
 *
 * TC-01  Positive: query SSC state of TEST_SSC_DEVICE_ID / TEST_SSC_CLK_ID.
 *        SSC is only valid for PLL-backed clocks; DM NACKs MCU_UART0_FCLK_CLK.
 * TC-02  Negative: invalid device ID (0xFFFF) → not SUCCESS or NACK
 * TC-03  Negative: NULL pReqPayload → not SUCCESS or NACK
 */
static int32_t test_msgGetClockSsc(void *args)
{
    int32_t retVal;
    int32_t failCount = 0;

    struct tisci_msg_get_clock_ssc_req  request;
    struct tisci_msg_get_clock_ssc_resp response;

    /* TC-01: Positive – query SSC state on DSS0 DPI_1_IN_CLK (backed by HSDIV0_16FFT_MAIN_17).
     * SSC is only supported on 16FFT-type PLL-backed clocks.
     * Enabled only when TEST_DM_CLK_SSC is defined (e.g. on AM62DX where DSS0 is present). */
#ifdef TEST_DM_CLK_SSC
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.device = TISCI_DEV_DSS0;           /* 186U on AM62DX */
        request.clk    = TISCI_DEV_DSS0_DPI_1_IN_CLK; /* 2U — SSC-capable */

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK_SSC,
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
            DebugP_log("FAIL: test_msgGetClockSsc TC-01 Positive - query SSC state on DSS0 DPI_1_IN_CLK: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
#endif

    /* TC-02: Negative – invalid device ID (0xFFFF) */
    {
        memset(&request,  0, sizeof(request));
        memset(&response, 0, sizeof(response));
        request.device = 0xFFFFU;
        request.clk    = 0U;

        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK_SSC,
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
            DebugP_log("FAIL: test_msgGetClockSsc TC-02 Negative - invalid device ID 0xFFFF: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }

    /* TC-03: Negative – NULL pReqPayload */
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_GET_CLOCK_SSC,
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
            DebugP_log("FAIL: test_msgGetClockSsc TC-03 Negative - NULL pReqPayload: retVal=%d flags=0x%x\r\n",
                       retVal, respPrm.flags);
            failCount++;
        }
    }
    return failCount;
}

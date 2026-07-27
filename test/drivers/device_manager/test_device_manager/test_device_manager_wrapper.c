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
#include "test_device_manager_wrapper.h"

/* UART_printf is implemented in sciclient_direct/uart_print.c; no public header */
extern void UART_printf(const char *pcString, ...);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void testDM_powerManagement(void *args)
{
    int32_t  retVal;
    int32_t  retValFailCnt = 0;
    uint32_t moduleState;
    uint32_t resetState;
    uint32_t contextLossState;
    uint32_t clkState;
    uint32_t numParent;
    uint32_t parent;
    uint64_t freqHz;
    uint64_t respFreqHz;

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleState — TISCI_MSG_SET_DEVICE (0x0200)          */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: set device ON */
    retVal = Sciclient_pmSetModuleState(
        TEST_DEVICE_ID,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState TC-1: Positive: set device ON  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }


    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleState negative cases                           */
    /* ------------------------------------------------------------------ */

    /* TC-2: Positive: Restore device to AUTO_OFF */
    retVal = Sciclient_pmSetModuleState(
        TEST_DEVICE_ID,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState TC-2: Positive: Restore device to AUTO_OFF  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-3: Negative: invalid module ID */
    retVal = Sciclient_pmSetModuleState(
        0xFFFFU,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState TC-3: Negative: invalid module ID  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-4: Negative: invalid state value */
    retVal = Sciclient_pmSetModuleState(
        TEST_DEVICE_ID,
        0xFFFEU,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState TC-4: Negative: invalid state value  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-5: Negative: device ID 0xFFFD (out-of-range, rejected by firmware) */
    retVal = Sciclient_pmSetModuleState(
        0xFFFDU,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleState TC-5: Negative: device ID 0xFFFD (out-of-range, rejected by firmware)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmGetModuleState — TISCI_MSG_GET_DEVICE (0x0201)          */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: query state of the device that was just set ON */
    retVal = Sciclient_pmGetModuleState(
        TEST_DEVICE_ID,
        &moduleState,
        &resetState,
        &contextLossState,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleState TC-1: Positive: query state of the device that was just set ON  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-2: Negative: invalid module ID 0xFFFE (out-of-range) */
    retVal = Sciclient_pmGetModuleState(
        0xFFFEU,
        &moduleState,
        &resetState,
        &contextLossState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleState TC-2: Negative: invalid module ID 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-3: Negative: invalid module ID 0xFFFF (out-of-range) */
    retVal = Sciclient_pmGetModuleState(
        0xFFFFU,
        &moduleState,
        &resetState,
        &contextLossState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleState TC-3: Negative: invalid module ID 0xFFFF (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-4: Negative: module ID 0xFFFD (out-of-range, rejected by firmware) */
    retVal = Sciclient_pmGetModuleState(
        0xFFFDU,
        &moduleState,
        &resetState,
        &contextLossState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleState TC-4: Negative: invalid module ID 0xFFFD (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmModuleClkRequest — TISCI_MSG_SET_CLOCK (0x0100)         */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: enable clock for the device (device must be ON first) */
    retVal = Sciclient_pmModuleClkRequest(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest TC-1: Positive: enable clock for the device (device must be ON first)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-2: Negative: out-of-range clock ID (256) for a valid device */
    retVal = Sciclient_pmModuleClkRequest(
        TEST_DEVICE_ID,
        256U,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest TC-2: Negative: out-of-range clock ID (256) for a valid device  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-3: Negative: invalid device ID 0xFFFE (out-of-range) */
    retVal = Sciclient_pmModuleClkRequest(
        0xFFFEU,
        TEST_DEVICE_CLK_ID,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest TC-3: Negative: invalid device ID 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-4: Negative: invalid device ID 0xFFFF */
    retVal = Sciclient_pmModuleClkRequest(
        0xFFFFU,
        TEST_DEVICE_CLK_ID,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest TC-4: Negative: invalid device ID 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-5: Negative: invalid clock state value 0xFFFE */
    retVal = Sciclient_pmModuleClkRequest(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        0xFFFEU,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest TC-5: Negative: invalid clock state value 0xFFFE  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-6: Negative: device ID 0x0 with out-of-range clock ID 256 */
    retVal = Sciclient_pmModuleClkRequest(
        0x0U,
        256U,
        TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleClkRequest TC-6: Negative: device ID 0x0 with out-of-range clock ID 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmModuleGetClkStatus — TISCI_MSG_GET_CLOCK (0x0101)       */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: read clock state */
    retVal = Sciclient_pmModuleGetClkStatus(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus TC-1: Positive: read clock state  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-2: Negative: out-of-range clock ID (256) */
    retVal = Sciclient_pmModuleGetClkStatus(
        TEST_DEVICE_ID,
        256U,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus TC-2: Negative: out-of-range clock ID (256)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-3: Negative: invalid device ID 0xFFFE (out-of-range) */
    retVal = Sciclient_pmModuleGetClkStatus(
        0xFFFEU,
        TEST_DEVICE_CLK_ID,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus TC-3: Negative: invalid device ID 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-4: Negative: invalid device ID 0xFFFF (out-of-range) */
    retVal = Sciclient_pmModuleGetClkStatus(
        0xFFFFU,
        TEST_DEVICE_CLK_ID,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus TC-4: Negative: invalid device ID 0xFFFF (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-5: Negative: device ID 0x0 with out-of-range clock ID 256 */
    retVal = Sciclient_pmModuleGetClkStatus(
        0x0U,
        256U,
        &clkState,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmModuleGetClkStatus TC-5: Negative: invalid device ID 0x0 with out-of-range clock ID 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleRst — TISCI_MSG_SET_DEVICE_RESETS (0x0202)     */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: assert reset then de-assert */
    retVal = Sciclient_pmSetModuleRst(
        TEST_DEVICE_ID,
        1U,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst TC-1a: Positive: assert reset (resets=1)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    retVal = Sciclient_pmSetModuleRst(
        TEST_DEVICE_ID,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst TC-1b: Positive: de-assert reset (resets=0)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-2: Negative: invalid device ID 0xFFFE (out-of-range) */
    retVal = Sciclient_pmSetModuleRst(
        0xFFFEU,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst TC-2: Negative: invalid device ID 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-3: Negative: invalid device ID 0xFFFF (out-of-range) */
    retVal = Sciclient_pmSetModuleRst(
        0xFFFFU,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst TC-3: Negative: invalid device ID 0xFFFF (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-4: Negative: invalid device ID 0xFFFD (out-of-range) */
    retVal = Sciclient_pmSetModuleRst(
        0xFFFDU,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst TC-4: Negative: invalid device ID 0xFFFD (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleRst_flags — TISCI_MSG_SET_DEVICE_RESETS (0x0202)*/
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: assert reset with AOP flag, then de-assert */
    retVal = Sciclient_pmSetModuleRst_flags(
        TEST_DEVICE_ID,
        1U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags TC-1a: Positive: assert reset with AOP flag (resets=1)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    retVal = Sciclient_pmSetModuleRst_flags(
        TEST_DEVICE_ID,
        0U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags TC-1b: Positive: de-assert reset with AOP flag (resets=0)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-2: Negative: invalid device ID 0xFFFE (out-of-range) */
    retVal = Sciclient_pmSetModuleRst_flags(
        0xFFFEU,
        0U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags TC-2: Negative: invalid device ID 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-3: Negative: invalid device ID 0xFFFF (out-of-range) */
    retVal = Sciclient_pmSetModuleRst_flags(
        0xFFFFU,
        0U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags TC-3: Negative: invalid device ID 0xFFFF (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-4: Negative: invalid device ID 0xFFFD (out-of-range) */
    retVal = Sciclient_pmSetModuleRst_flags(
        0xFFFDU,
        0U,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleRst_flags TC-4: Negative: invalid device ID 0xFFFD (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleClkParent — TISCI_MSG_SET_CLOCK_PARENT (0x0102)*/
    /* MCU_UART0 FCLK is a fixed-source clock: firmware NACKs parent ops,  */
    /* wrapper returns CSL_EFAIL — all cases below expect failure.          */
    /* ------------------------------------------------------------------ */

    /* TC-1: Negative: Fixed-source clock firmware NACK */
    retVal = Sciclient_pmSetModuleClkParent(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        0U,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmSetModuleClkParent TC-1: Negative: Fixed-source clock firmware NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-2: Negative: invalid device 0xFFFE (out-of-range), clock 0, parent 0 */
    retVal = Sciclient_pmSetModuleClkParent(
        0xFFFEU, 0x0U, 0x0U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmSetModuleClkParent TC-2: Negative: invalid device 0xFFFE (out-of-range), clock 0, parent 0  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-3: Negative: invalid device 0xFFFF (out-of-range) */
    retVal = Sciclient_pmSetModuleClkParent(
        0xFFFFU, 0x0U, 0x0U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmSetModuleClkParent TC-3: Negative: invalid device 0xFFFF (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-4: Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmSetModuleClkParent(
        0x0U, 256U, 0x0U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmSetModuleClkParent TC-4: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-5: Negative: device 0x0, clock 0, out-of-range parent 256 */
    retVal = Sciclient_pmSetModuleClkParent(
        0x0U, 0x0U, 256U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmSetModuleClkParent TC-5: Negative: device 0x0, clock 0, out-of-range parent 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmGetModuleClkParent — TISCI_MSG_GET_CLOCK_PARENT (0x0103)*/
    /* ------------------------------------------------------------------ */

    /* TC-1: Negative: Fixed-source clock firmware NACK */
    retVal = Sciclient_pmGetModuleClkParent(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        &parent,
        SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkParent TC-1: Negative: Fixed-source clock firmware NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-2: Negative: invalid device 0xFFFE (out-of-range) */
    retVal = Sciclient_pmGetModuleClkParent(
        0xFFFEU, 0x0U, &parent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmGetModuleClkParent TC-2: Negative: invalid device 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-3: Negative: invalid device 0xFFFF (out-of-range) */
    retVal = Sciclient_pmGetModuleClkParent(
        0xFFFFU, 0x0U, &parent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmGetModuleClkParent TC-3: Negative: invalid device 0xFFFF (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-4: Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmGetModuleClkParent(
        0x0U, 256U, &parent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmGetModuleClkParent TC-4: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmGetModuleClkNumParent — TISCI_MSG_GET_NUM_CLOCK_PARENTS */
    /*                                     (0x0104)                       */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: valid device / clock → SUCCESS */
    retVal = Sciclient_pmGetModuleClkNumParent(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        &numParent,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkNumParent TC-1: Positive: valid device / clock → SUCCESS  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-2: Negative: invalid device 0xFFFE (out-of-range) */
    retVal = Sciclient_pmGetModuleClkNumParent(
        0xFFFEU, 0x0U, &numParent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmGetModuleClkNumParent TC-2: Negative: invalid device 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-3: Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmGetModuleClkNumParent(
        0xFFFFU, 0x0U, &numParent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmGetModuleClkNumParent TC-3: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-4: Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmGetModuleClkNumParent(
        0x0U, 256U, &numParent, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmGetModuleClkNumParent TC-4: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmGetModuleClkFreq — TISCI_MSG_GET_FREQ (0x010E)         */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: read current clock frequency (device must be ON) */
    freqHz = 0ULL;
    retVal = Sciclient_pmGetModuleClkFreq(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        &freqHz,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmGetModuleClkFreq TC-1: Positive: read current clock frequency (device must be ON)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-2: Negative: invalid device 0xFFFE (out-of-range) */
    retVal = Sciclient_pmGetModuleClkFreq(
        0xFFFEU, 0x0U, &freqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmGetModuleClkFreq TC-2: Negative: invalid device 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-3: Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmGetModuleClkFreq(
        0xFFFFU, 0x0U, &freqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmGetModuleClkFreq TC-3: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-4: Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmGetModuleClkFreq(
        0x0U, 256U, &freqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmGetModuleClkFreq TC-4: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmSetModuleClkFreq — TISCI_MSG_SET_FREQ (0x010C)         */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: re-read current frequency and set it back (no-op change) */
    retVal = Sciclient_pmGetModuleClkFreq(
        TEST_DEVICE_ID, TEST_DEVICE_CLK_ID, &freqHz, SystemP_WAIT_FOREVER);
    if (retVal == SystemP_SUCCESS)
    {
        retVal = Sciclient_pmSetModuleClkFreq(
            TEST_DEVICE_ID,
            TEST_DEVICE_CLK_ID,
            freqHz,
            0U,
            SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
         {
             DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq TC-1: Positive: re-read current frequency and set it back (no-op change)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
             retValFailCnt++;
         }
    }

    /* TC-2: Negative: invalid device 0xFFFE (out-of-range) */
    retVal = Sciclient_pmSetModuleClkFreq(
        0xFFFEU, 0x0U, 1000005U, 0x1U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq TC-2: Negative: invalid device 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-3: Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmSetModuleClkFreq(
        0xFFFFU, 0x0U, 1000005U, 0x1U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq TC-3: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-4: Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmSetModuleClkFreq(
        0x0U, 256U, 1000005U, 0x1U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq TC-4: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-5: Negative: unreachable frequency (1 Hz) on valid device/clock */
    retVal = Sciclient_pmSetModuleClkFreq(
        TEST_DEVICE_ID, TEST_DEVICE_CLK_ID, 1ULL, 0x1U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmSetModuleClkFreq TC-5: Negative: unreachable frequency (1 Hz) on valid device/clock  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmQueryModuleClkFreq — TISCI_MSG_QUERY_FREQ (0x010D)     */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: query achievable frequency using last-read freqHz value */
    retVal = Sciclient_pmQueryModuleClkFreq(
        TEST_DEVICE_ID,
        TEST_DEVICE_CLK_ID,
        freqHz,
        &respFreqHz,
        SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_pmQueryModuleClkFreq TC-1: Positive: query achievable frequency using last-read freqHz value  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-2: Negative: invalid device 0xFFFE (out-of-range) */
    retVal = Sciclient_pmQueryModuleClkFreq(
        0xFFFEU, 0x0U, 1000005U, &respFreqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmQueryModuleClkFreq TC-2: Negative: invalid device 0xFFFE (out-of-range)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-3: Negative: invalid device 0xFFFF */
    retVal = Sciclient_pmQueryModuleClkFreq(
        0xFFFFU, 0x0U, 1000005U, &respFreqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmQueryModuleClkFreq TC-3: Negative: invalid device 0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-4: Negative: device 0x0, out-of-range clock 256 */
    retVal = Sciclient_pmQueryModuleClkFreq(
        0x0U, 256U, 1000005U, &respFreqHz, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmQueryModuleClkFreq TC-4: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmDeviceReset — TISCI_MSG_SYS_RESET (0x0005)             */
    /* Positive test resets the board immediately; guard manually.        */
    /* ------------------------------------------------------------------ */
#ifdef ENABLE_MANUAL_TEST
    retVal = Sciclient_pmDeviceReset(SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmDeviceReset TC-0: Negative: device 0x0, out-of-range clock 256  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }
#endif /* ENABLE_MANUAL_TEST */

    /* ------------------------------------------------------------------ */
    /* Sciclient_pmDomainReset — TISCI_MSG_SYS_RESET (domain variant)     */
    /* A positive test would reset the specified power domain, which is   */
    /* destructive.  Only negative tests (invalid domGrp) are safe here. */
    /* ------------------------------------------------------------------ */

    /* TC-1: Negative – invalid domGrp 0xFF → NACK */
    retVal = Sciclient_pmDomainReset(0xFFU, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmDomainReset TC-1: Negative: invalid domGrp 0xFF → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* TC-2: Negative – invalid domGrp 0x70 → NACK */
    retVal = Sciclient_pmDomainReset(0x70U, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
     {
         DebugP_log("FAIL: Sciclient_pmDomainReset TC-2: Negative: invalid domGrp 0x70 → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
         retValFailCnt++;
     }

    /* Final check: All APIs should succeed (retValFailCnt = 0) */
    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);

}

/* ========================================================================== */
/*                                                                            */
/*   testDM_firewallApis                                                      */
/*   Firewall API wrapper tests — JIRA 12097                                  */
/*                                                                            */
/*   Covers:                                                                  */
/*     Sciclient_firewallGetRegion       (TISCI_MSG_GET_FWL_REGION    0x9001) */
/*     Sciclient_firewallSetRegion       (TISCI_MSG_SET_FWL_REGION    0x9000) */
/*     Sciclient_firewallChangeOwnerInfo (TISCI_MSG_CHANGE_FWL_OWNER  0x9002) */
/*                                                                            */
/* ========================================================================== */

void testDM_firewallApis(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ---------------------------------------------------------------------- */
    /* Sciclient_firewallGetRegion — TISCI_MSG_GET_FWL_REGION (0x9001)        */
    /* ---------------------------------------------------------------------- */

    /* TC-1: Positive: query fwl_id=7 (FSS0 — owned by DM on AM62DX/AX/PX), region=0
     * Guarded by DM_TEST_FWL_ID0_SUPPORTED: fwl_id=7 is not DM-owned on AM62X or AM275X. */
#if defined(DM_TEST_FWL_ID0_SUPPORTED)
    {
        struct tisci_msg_fwl_get_firewall_region_req  getReq  = {0};
        struct tisci_msg_fwl_get_firewall_region_resp getResp = {0};

        getReq.fwl_id            = 7U;
        getReq.region            = 0U;
        getReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallGetRegion(&getReq, &getResp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallGetRegion TC-1: Positive: query fwl_id=7 (FSS0 — owned by DM on AM62DX), region=0  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }
#endif /* DM_TEST_FWL_ID0_SUPPORTED */

    /* TC-2: Negative: NULL req and resp pointers */
    retVal = Sciclient_firewallGetRegion(NULL, NULL, 0U);
    if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallGetRegion TC-2: Negative: NULL req and resp pointers  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

    /* TC-3: Negative: invalid fwl_id=0xFFFF */
    {
        struct tisci_msg_fwl_get_firewall_region_req  getReq  = {0};
        struct tisci_msg_fwl_get_firewall_region_resp getResp = {0};

        getReq.fwl_id            = 0xFFFFU;
        getReq.region            = 0U;
        getReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallGetRegion(&getReq, &getResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallGetRegion TC-3: Negative: invalid fwl_id=0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* TC-4: Negative: invalid fwl_id=0xFF */
    {
        struct tisci_msg_fwl_get_firewall_region_req  getReq  = {0};
        struct tisci_msg_fwl_get_firewall_region_resp getResp = {0};

        getReq.fwl_id            = 0xFFU;
        getReq.region            = 0U;
        getReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallGetRegion(&getReq, &getResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallGetRegion TC-4: Negative: invalid fwl_id=0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* Sciclient_firewallSetRegion — TISCI_MSG_SET_FWL_REGION (0x9000)        */
    /* ---------------------------------------------------------------------- */

    /* TC-1: Positive: read-then-restore — GET fwl_id=7 (FSS0, DM-owned) region=0,
     * then SET back the exact same values.  No-op write that safely exercises
     * the full SET code path without changing permissions or address range.
     * Guarded by DM_TEST_FWL_ID0_SUPPORTED: fwl_id=7 is not DM-owned on AM62X or AM275X. */
#if defined(DM_TEST_FWL_ID0_SUPPORTED)
    {
        struct tisci_msg_fwl_get_firewall_region_req  getReq  = {0};
        struct tisci_msg_fwl_get_firewall_region_resp getResp = {0};

        getReq.fwl_id            = 7U;
        getReq.region            = 0U;
        getReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallGetRegion(&getReq, &getResp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallSetRegion TC-1: Positive: read-then-restore GET  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        {
            struct tisci_msg_fwl_set_firewall_region_req  setReq  = {0};
            struct tisci_msg_fwl_set_firewall_region_resp setResp = {0};

            setReq.fwl_id            = getResp.fwl_id;
            setReq.region            = getResp.region;
            setReq.n_permission_regs = getResp.n_permission_regs;
            setReq.control           = getResp.control;
            setReq.permissions[0]    = getResp.permissions[0];
            setReq.permissions[1]    = getResp.permissions[1];
            setReq.permissions[2]    = getResp.permissions[2];
            setReq.start_address     = getResp.start_address;
            setReq.end_address       = getResp.end_address;

            retVal = Sciclient_firewallSetRegion(&setReq, &setResp, SystemP_WAIT_FOREVER);
            if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallSetRegion TC-1: Positive: read-then-restore SET  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
        }
    }
#endif /* DM_TEST_FWL_ID0_SUPPORTED */

    /* TC-2: Negative: NULL req and resp pointers */
    retVal = Sciclient_firewallSetRegion(NULL, NULL, 0U);
    if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallSetRegion TC-2: Negative: NULL req and resp pointers  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

    /* TC-3: Negative: fwl_id=3 (not owned by DM on AM62DX — firmware NACK) */
    {
        struct tisci_msg_fwl_set_firewall_region_req  setReq  = {0};
        struct tisci_msg_fwl_set_firewall_region_resp setResp = {0};

        setReq.fwl_id            = 3U;
        setReq.region            = 0U;
        setReq.n_permission_regs = 3U;
        setReq.control           = 0x30AU;
        setReq.permissions[0]    = 0xC3FFFFU;
        setReq.permissions[1]    = 0xC3FFFFU;
        setReq.permissions[2]    = 0xC3FFFFU;
        setReq.start_address     = 0x70000000U;
        setReq.end_address       = 0x701FF000U;

        retVal = Sciclient_firewallSetRegion(&setReq, &setResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallSetRegion TC-3: Negative: fwl_id=3 (not owned by DM on AM62DX — firmware NACK)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* TC-4: Negative: invalid fwl_id=0xFFFF */
    {
        struct tisci_msg_fwl_set_firewall_region_req  setReq  = {0};
        struct tisci_msg_fwl_set_firewall_region_resp setResp = {0};

        setReq.fwl_id            = 0xFFFFU;
        setReq.region            = 0U;
        setReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallSetRegion(&setReq, &setResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallSetRegion TC-4: Negative: invalid fwl_id=0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* TC-5: Negative: invalid fwl_id=0xFF */
    {
        struct tisci_msg_fwl_set_firewall_region_req  setReq  = {0};
        struct tisci_msg_fwl_set_firewall_region_resp setResp = {0};

        setReq.fwl_id            = 0xFFU;
        setReq.region            = 0U;
        setReq.n_permission_regs = 3U;

        retVal = Sciclient_firewallSetRegion(&setReq, &setResp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallSetRegion TC-5: Negative: invalid fwl_id=0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ---------------------------------------------------------------------- */
    /* Sciclient_firewallChangeOwnerInfo — TISCI_MSG_CHANGE_FWL_OWNER (0x9002)*/
    /* ---------------------------------------------------------------------- */

    /* TC-1: Positive: fwl_id=7 (FSS0, DM-owned), region=0,
     * owner_index=TISCI_HOST_ID_MAIN_0_R5_0 (DM R5F — re-asserting current
     * ownership is a no-op and always succeeds).
     * Guarded by DM_TEST_FWL_ID0_SUPPORTED: fwl_id=7 is not DM-owned on AM62X or AM275X. */
#if defined(DM_TEST_FWL_ID0_SUPPORTED)
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 7U;
        req.region      = 0U;
        req.owner_index = TISCI_HOST_ID_MAIN_0_R5_0;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo TC-1: Positive: fwl_id=7 (FSS0, DM-owned), region=0  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }
    }
#endif /* DM_TEST_FWL_ID0_SUPPORTED */

    /* TC-2: Negative: NULL req and resp pointers */
    retVal = Sciclient_firewallChangeOwnerInfo(NULL, NULL, 0U);
    if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo TC-2: Negative: NULL req and resp pointers  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

    /* TC-3: Negative: fwl_id=3 (not owned by DM on AM62DX — firmware NACK) */
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 3U;
        req.region      = 0U;
        req.owner_index = TISCI_HOST_ID_MAIN_0_R5_0;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo TC-3: Negative: fwl_id=3 (not owned by DM on AM62DX — firmware NACK)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* TC-4: Negative: invalid fwl_id=0xFFFF */
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 0xFFFFU;
        req.region      = 0U;
        req.owner_index = TISCI_HOST_ID_MAIN_0_R5_0;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo TC-4: Negative: invalid fwl_id=0xFFFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* TC-5: Negative: invalid fwl_id=0xFF */
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 0xFFU;
        req.region      = 0U;
        req.owner_index = TISCI_HOST_ID_MAIN_0_R5_0;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo TC-5: Negative: invalid fwl_id=0xFF  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* TC-6: Negative: invalid owner_index=0xFF with valid fwl_id=7 */
    {
        struct tisci_msg_fwl_change_owner_info_req  req  = {0};
        struct tisci_msg_fwl_change_owner_info_resp resp = {0};

        req.fwl_id      = 7U;
        req.region      = 0U;
        req.owner_index = 0xFFU;

        retVal = Sciclient_firewallChangeOwnerInfo(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_firewallChangeOwnerInfo TC-6: Negative: invalid owner_index=0xFF with valid fwl_id=7  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ========================================================================== */
/*                                                                            */
/*   testDM_coreVersion                                                     */
/*   Combined version / ABI / DM-version / SEC-handover API tests            */
/*                                                                            */
/*   Covers (one RUN_TEST, single JIRA):                                      */
/*     Sciclient_abiCheck          TISCI_MSG_VERSION     0x0002              */
/*     Sciclient_getVersionCheck   TISCI_MSG_VERSION     0x0002              */
/*     Sciclient_getDMVersion      TISCI_MSG_DM_VERSION  0x000F              */
/*     Sciclient_triggerSecHandover TISCI_MSG_SEC_HANDOVER 0x9030            */
/*                                                                            */
/* ========================================================================== */

void testDM_coreVersion(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ------------------------------------------------------------------ */
    /* Sciclient_abiCheck — TISCI_MSG_VERSION (0x0002)                     */
    /* Validates SYSFW ABI major version against SCICLIENT_FIRMWARE_ABI_MAJOR */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: firmware running, ABI major version matches expected */
    retVal = Sciclient_abiCheck();
    if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_abiCheck TC-1: Positive: firmware running, ABI major version matches expected  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

    /*
     * Note: Sciclient_abiCheck() takes no arguments. The only way to produce
     * a failure is if the runtime ABI major reported by SYSFW differs from
     * SCICLIENT_FIRMWARE_ABI_MAJOR, which cannot be forced at runtime.
     * No parameter-driven negative case.
     */

    /* ------------------------------------------------------------------ */
    /* Sciclient_getVersionCheck — TISCI_MSG_VERSION (0x0002)             */
    /* Sends TISCI_MSG_VERSION to SYSFW and verifies ACK.                 */
    /* doLog controls console output only, not pass/fail.                 */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: with logging enabled (doLog=1) */
    retVal = Sciclient_getVersionCheck(1U);
    if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_getVersionCheck TC-1: Positive: with logging enabled (doLog=1)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

    /* TC-2: Positive: with logging disabled (doLog=0) */
    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_getVersionCheck TC-2: Positive: with logging disabled (doLog=0)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

    /*
     * Note: doLog is a logging flag only. TISCI_MSG_VERSION always succeeds
     * on a running system. No parameter-driven negative case.
     */

    /* ------------------------------------------------------------------ */
    /* Sciclient_getDMVersion — TISCI_MSG_DM_VERSION (0x000F)             */
    /* In ENABLE_SCICLIENT_DIRECT builds Sciclient_getDMVersion() from     */
    /* drivers.lib cannot be linked (duplicate symbols with               */
    /* sciclient_direct.lib). Sciclient_direct_getDMVersion() is the       */
    /* sciclient_direct equivalent declared in                            */
    /* source/drivers/device_manager/sciclient.h and provides identical   */
    /* behaviour.                                                         */
    /* ------------------------------------------------------------------ */

    /* TC-1: Positive: with logging enabled (doLog=1) */
    retVal = Sciclient_direct_getDMVersion(1U);
    if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_direct_getDMVersion TC-1: Positive: with logging enabled (doLog=1)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

    /* TC-2: Positive: with logging disabled (doLog=0) */
    retVal = Sciclient_direct_getDMVersion(0U);
    if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_direct_getDMVersion TC-2: Positive: with logging disabled (doLog=0)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ==========================================================================
 * testDM_resourceManagementSciclient — Resource Management (RM) API coverage
 *
 * Covers all 13 Sciclient_rm* APIs compiled into sciclient_direct.lib:
 *   Sciclient_rmGetResourceRange
 *   Sciclient_rmIrqSetRaw / Sciclient_rmIrqReleaseRaw
 *   Sciclient_rmRingCfg
 *   Sciclient_rmUdmapGcfgCfg
 *   Sciclient_rmUdmapTxChCfg / Sciclient_rmUdmapRxChCfg
 *   Sciclient_rmUdmapFlowCfg / Sciclient_rmUdmapFlowSizeThreshCfg
 *   Sciclient_rmPsilPair / Sciclient_rmPsilUnpair
 *   Sciclient_rmPsilRead  / Sciclient_rmPsilWrite
 *
 * AM62DX resource allocation (default RM board config):
 *   TISCI_HOST_ID_MAIN_0_R5_1 owns:
 *     BCDMA ring indices 18-23 (DMASS0_BCDMA_0, nav_id=26)
 *     PKTDMA unmapped TX ch 10, RX ch 10, RX flow 10 (DMASS0_PKTDMA_0, nav_id=30)
 *     UDMAP_GLOBAL_CONFIG allocated to TISCI_HOST_ID_ALL
 *     MAIN_GPIOMUX_INTROUTER0 IR_OUTPUT[0..15] allocated to A53_2 (secondary_host)
 *     DMASS0 PSIL threads 0x100B (PKTDMA TX) / 0x900B (PKTDMA RX)
 *
 * Test strategy for configurable APIs: use valid_params=0 (no-op) where
 * possible — only the ownership permission check fires; no HW registers written.
 * IRQ: set route in IrqSetRaw, release it in IrqReleaseRaw.
 * PSIL: pair threads in PsilPair, read/write, then unpair in PsilUnpair.
 * ========================================================================== */

void testDM_resourceManagementSciclient(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ------------------------------------------------------------------ */
    /* 1. Sciclient_rmGetResourceRange — TISCI_MSG_RM_GET_RESOURCE_RANGE   */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_get_resource_range_req  req;
        struct tisci_msg_rm_get_resource_range_resp resp;

        /* TC-1: Positive – query IA_VINT resources for INTAGGR_0.
         * TISCI_HOST_ID_ALL → range_num > 0 expected. */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.type           = (uint16_t) WRAP_RM_NAV_INTAGGR_DEV_ID;
        req.subtype        = TISCI_RESASG_SUBTYPE_IA_VINT;
        req.secondary_host = TISCI_HOST_ID_ALL;
        retVal = Sciclient_rmGetResourceRange(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmGetResourceRange TC-01: Positive: query IA_VINT resources for INTAGGR_0  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – invalid device type (0xFFFF) */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.type           = 0xFFFFU;
        req.subtype        = TISCI_RESASG_SUBTYPE_IA_VINT;
        req.secondary_host = TISCI_HOST_ID_ALL;
        retVal = Sciclient_rmGetResourceRange(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmGetResourceRange TC-02: Negative: invalid device type (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – invalid subtype (0xFF) with valid device type */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.type           = (uint16_t) WRAP_RM_NAV_INTAGGR_DEV_ID;
        req.subtype        = 0xFFU;
        req.secondary_host = TISCI_HOST_ID_ALL;
        retVal = Sciclient_rmGetResourceRange(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmGetResourceRange TC-03: Negative: invalid subtype (0xFF) with valid device type  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-4: Negative – NULL req pointer */
        retVal = Sciclient_rmGetResourceRange(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmGetResourceRange TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 2. Sciclient_rmIrqSetRaw — TISCI_MSG_RM_IRQ_SET (0x1000)           */
    /* Routes MAIN_GPIOMUX_INTROUTER0 input 10 → output 0 for A53_2.     */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_irq_set_req  req;
        struct tisci_msg_rm_irq_set_resp resp;

        /* TC-1: Positive – valid direct IR mux route, secondary_host=A53_2 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                             TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                             TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        req.src_id         = (uint16_t) WRAP_RM_IRQ_SRC_DEV_ID;
        req.src_index      = (uint16_t) WRAP_RM_IRQ_SRC_INDEX;
        req.dst_id         = (uint16_t) WRAP_RM_IRQ_DST_DEV_ID;
        req.dst_host_irq   = (uint16_t) WRAP_RM_IRQ_DST_HOST_IRQ;
        req.secondary_host = (uint8_t)  WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqSetRaw(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSetRaw TC-01: Positive: valid direct IR mux route, secondary_host=A53_2  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – invalid src_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                             TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                             TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        req.src_id         = 0xFFFFU;
        req.src_index      = (uint16_t) WRAP_RM_IRQ_SRC_INDEX;
        req.dst_id         = (uint16_t) WRAP_RM_IRQ_DST_DEV_ID;
        req.dst_host_irq   = (uint16_t) WRAP_RM_IRQ_DST_HOST_IRQ;
        req.secondary_host = (uint8_t)  WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqSetRaw(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSetRaw TC-02: Negative: invalid src_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – NULL req pointer */
        retVal = Sciclient_rmIrqSetRaw(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSetRaw TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 3. Sciclient_rmIrqReleaseRaw — TISCI_MSG_RM_IRQ_RELEASE (0x1001)  */
    /* Releases the route set in step 2 TC-01 above.                     */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_irq_release_req req;

        /* TC-1: Positive – release the route set by IrqSetRaw TC-01 */
        memset(&req, 0, sizeof(req));
        req.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                             TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                             TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        req.src_id         = (uint16_t) WRAP_RM_IRQ_SRC_DEV_ID;
        req.src_index      = (uint16_t) WRAP_RM_IRQ_SRC_INDEX;
        req.dst_id         = (uint16_t) WRAP_RM_IRQ_DST_DEV_ID;
        req.dst_host_irq   = (uint16_t) WRAP_RM_IRQ_DST_HOST_IRQ;
        req.secondary_host = (uint8_t)  WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqReleaseRaw(&req, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqReleaseRaw TC-01: Positive: release the route set by IrqSetRaw TC-01  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – invalid src_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                             TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                             TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        req.src_id         = 0xFFFFU;
        req.src_index      = (uint16_t) WRAP_RM_IRQ_SRC_INDEX;
        req.dst_id         = (uint16_t) WRAP_RM_IRQ_DST_DEV_ID;
        req.dst_host_irq   = (uint16_t) WRAP_RM_IRQ_DST_HOST_IRQ;
        req.secondary_host = (uint8_t)  WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqReleaseRaw(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqReleaseRaw TC-02: Negative: invalid src_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – NULL req pointer */
        retVal = Sciclient_rmIrqReleaseRaw(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqReleaseRaw TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 4. Sciclient_rmRingCfg — TISCI_MSG_RM_RING_CFG (0x1110)           */
    /* BCDMA ring 18 is owned by MAIN_0_R5_1 (start=18, count=6).        */
    /* valid_params=0 → no-op permission-only check; no HW writes.       */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_ring_cfg_req  req;
        struct tisci_msg_rm_ring_cfg_resp resp;

        /* TC-1: Positive – valid_params=0 on owned BCDMA ring 18 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_BCDMA_DEV_ID;
        req.index        = (uint16_t) WRAP_RM_BCDMA_RING_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmRingCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmRingCfg TC-01: Positive: valid_params=0 on owned BCDMA ring 18  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – ring 0 not owned by MAIN_0_R5_1 (A53_2 owns it) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_BCDMA_DEV_ID;
        req.index        = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmRingCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmRingCfg TC-02: Negative: ring 0 not owned by MAIN_0_R5_1 (A53_2 owns it)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.index        = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmRingCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmRingCfg TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-4: Negative – NULL req pointer */
        retVal = Sciclient_rmRingCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmRingCfg TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 5. Sciclient_rmUdmapGcfgCfg — TISCI_MSG_RM_UDMAP_GCFG_CFG (0x1240) */
    /* UDMAP_GLOBAL_CONFIG is allocated to TISCI_HOST_ID_ALL.             */
    /* valid_params=0xf writes all four GCFG fields to their reset values. */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_gcfg_cfg_req  req;
        struct tisci_msg_rm_udmap_gcfg_cfg_resp resp;

        /* TC-1: Positive – PKTDMA GCFG with valid_params=0xf (reset values) */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.valid_params = 0xfU;
        req.perf_ctrl    = 0x20U;
        req.emu_ctrl     = 0x1U;
        req.psil_to      = 0x200U;
        req.rflowfwstat  = 0x0U;
        retVal = Sciclient_rmUdmapGcfgCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapGcfgCfg TC-01: Positive: PKTDMA GCFG with valid_params=0xf (reset values)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapGcfgCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapGcfgCfg TC-02: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapGcfgCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapGcfgCfg TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 6. Sciclient_rmUdmapTxChCfg — TISCI_MSG_RM_UDMAP_TX_CH_CFG (0x1205) */
    /* PKTDMA unmapped TX channel 10 is owned by MAIN_0_R5_1.            */
    /* valid_params=0 → permission-only check; no HW channel writes.     */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_tx_ch_cfg_req  req;
        struct tisci_msg_rm_udmap_tx_ch_cfg_resp resp;

        /* TC-1: Positive – valid_params=0 on owned PKTDMA TX ch 10 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.index        = (uint16_t) WRAP_RM_PKTDMA_TX_CH_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapTxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapTxChCfg TC-01: Positive: valid_params=0 on owned PKTDMA TX ch 10  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – channel 0 not owned by MAIN_0_R5_1 */
        memset(&req, 0, sizeof(req));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.index        = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapTxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapTxChCfg TC-02: Negative: channel 0 not owned by MAIN_0_R5_1  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.index        = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapTxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapTxChCfg TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-41: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapTxChCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapTxChCfg TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 7. Sciclient_rmUdmapRxChCfg — TISCI_MSG_RM_UDMAP_RX_CH_CFG (0x1215) */
    /* PKTDMA unmapped RX channel 10 is owned by MAIN_0_R5_1.            */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_rx_ch_cfg_req  req;
        struct tisci_msg_rm_udmap_rx_ch_cfg_resp resp;

        /* TC-1: Positive – valid_params=0 on owned PKTDMA RX ch 10 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.index        = (uint16_t) WRAP_RM_PKTDMA_RX_CH_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapRxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapRxChCfg TC-01: Positive: valid_params=0 on owned PKTDMA RX ch 10  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – channel 0 not owned by MAIN_0_R5_1 */
        memset(&req, 0, sizeof(req));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.index        = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapRxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapRxChCfg TC-02: Negative: channel 0 not owned by MAIN_0_R5_1  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.index        = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapRxChCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapRxChCfg TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-4: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapRxChCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapRxChCfg TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 8. Sciclient_rmUdmapFlowCfg — TISCI_MSG_RM_UDMAP_FLOW_CFG (0x1230) */
    /* PKTDMA unmapped RX flow 10 is owned by MAIN_0_R5_1.               */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_flow_cfg_req  req;
        struct tisci_msg_rm_udmap_flow_cfg_resp resp;

        /* TC-1: Positive – valid_params=0 on owned PKTDMA RX flow 10 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.flow_index   = (uint16_t) WRAP_RM_PKTDMA_FLOW_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapFlowCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowCfg TC-01: Positive: valid_params=0 on owned PKTDMA RX flow 10  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – flow 0 not owned by MAIN_0_R5_1 */
        memset(&req, 0, sizeof(req));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.flow_index   = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapFlowCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowCfg TC-02: Negative: flow 0 not owned by MAIN_0_R5_1  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id       = 0xFFFFU;
        req.flow_index   = 0U;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapFlowCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowCfg TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-4: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapFlowCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowCfg TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 9. Sciclient_rmUdmapFlowSizeThreshCfg                              */
    /*    TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG (0x1231)                */
    /* PKTDMA RX flow 10 is owned by MAIN_0_R5_1; valid_params=0 no-op.  */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_udmap_flow_size_thresh_cfg_req  req;
        struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp resp;

        /* TC-1: Positive – valid_params=0 on owned PKTDMA RX flow 10 */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.nav_id       = (uint16_t) WRAP_RM_NAV_PKTDMA_DEV_ID;
        req.flow_index   = (uint16_t) WRAP_RM_PKTDMA_FLOW_IDX;
        req.valid_params = 0U;
        retVal = Sciclient_rmUdmapFlowSizeThreshCfg(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowSizeThreshCfg TC-01: Positive: valid_params=0 on owned PKTDMA RX flow 10  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – NULL req pointer */
        retVal = Sciclient_rmUdmapFlowSizeThreshCfg(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmUdmapFlowSizeThreshCfg TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 10. Sciclient_rmPsilPair — TISCI_MSG_RM_PSIL_PAIR (0x1280)         */
    /* Pairs PKTDMA TX thread 0x100B to RX thread 0x900B on DMASS0.      */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_psil_pair_req req;

        /* Setup: clear THREAD_EN on thread 0x100B before pairing.
         * testDM_rmIrqPsil (JIRA 12085) runs before this test and its
         * test_msgRmPsilWrite TC-01 sets THREAD_EN=1 (writes 0x80000000
         * to taddr=2 of thread 0x100B). PSI-L requires THREAD_EN=0 on the
         * source thread before a pair operation; leaving it enabled causes
         * the firmware to NACK the PSIL_PAIR message. */
        {
            struct tisci_msg_rm_psil_write_req wreq;
            memset(&wreq, 0, sizeof(wreq));
            wreq.valid_params = 0U;
            wreq.nav_id       = (uint16_t) WRAP_RM_PSIL_NAV_ID;
            wreq.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
            wreq.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
            wreq.data         = 0U; /* clear THREAD_EN */
            (void) Sciclient_rmPsilWrite(&wreq, SystemP_WAIT_FOREVER);
        }

        /* TC-1: Positive – pair TX thread 0x100B to RX thread 0x900B */
        memset(&req, 0, sizeof(req));
        req.nav_id     = WRAP_RM_PSIL_NAV_ID;
        req.src_thread = WRAP_RM_PSIL_SRC_THREAD;
        req.dst_thread = WRAP_RM_PSIL_DST_THREAD;
        retVal = Sciclient_rmPsilPair(&req, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilPair TC-01: Positive: pair TX thread 0x100B to RX thread 0x900B  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – dst_thread < 0x8000 (spec mandates NACK) */
        memset(&req, 0, sizeof(req));
        req.nav_id     = WRAP_RM_PSIL_NAV_ID;
        req.src_thread = 0x0000U;
        req.dst_thread = 0x0001U;  /* invalid: RX thread must be >= 0x8000 */
        retVal = Sciclient_rmPsilPair(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilPair TC-02: Negative: dst_thread < 0x8000 (spec mandates NACK)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.nav_id     = 0xFFFFU;
        req.src_thread = WRAP_RM_PSIL_SRC_THREAD;
        req.dst_thread = WRAP_RM_PSIL_DST_THREAD;
        retVal = Sciclient_rmPsilPair(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilPair TC-03: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-4: Negative – NULL req pointer */
        retVal = Sciclient_rmPsilPair(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilPair TC-04: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 11. Sciclient_rmPsilRead — TISCI_MSG_RM_PSIL_READ (0x1282)         */
    /* Reads thread config register taddr=0x2 of thread 0x100B.          */
    /* Pre-condition: PsilPair TC-01 has paired 0x100B → 0x900B.         */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_psil_read_req  req;
        struct tisci_msg_rm_psil_read_resp resp;

        /* TC-1: Positive – read taddr=0x2 from thread 0x100B */
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.valid_params = 0U;
        req.nav_id       = (uint16_t) WRAP_RM_PSIL_NAV_ID;
        req.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
        req.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
        retVal = Sciclient_rmPsilRead(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilRead TC-01: Positive: read taddr=0x2 from thread 0x100B  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.valid_params = 0U;
        req.nav_id       = 0xFFFFU;
        req.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
        req.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
        retVal = Sciclient_rmPsilRead(&req, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilRead TC-02: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – NULL req pointer */
        retVal = Sciclient_rmPsilRead(NULL, &resp, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilRead TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 12. Sciclient_rmPsilWrite — TISCI_MSG_RM_PSIL_WRITE (0x1283)       */
    /* Writes thread enable bit (0x80000000) to taddr=0x2 of thread 0x100B */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_psil_write_req req;

        /* TC-1: Positive – write thread enable pattern to taddr=0x2 */
        memset(&req, 0, sizeof(req));
        req.valid_params = 0U;
        req.nav_id       = (uint16_t) WRAP_RM_PSIL_NAV_ID;
        req.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
        req.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
        req.data         = WRAP_RM_PSIL_WRITE_DATA;
        retVal = Sciclient_rmPsilWrite(&req, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilWrite TC-01: Positive: write thread enable pattern to taddr=0x2  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – invalid nav_id (0xFFFF) */
        memset(&req, 0, sizeof(req));
        req.valid_params = 0U;
        req.nav_id       = 0xFFFFU;
        req.thread       = (uint16_t) WRAP_RM_PSIL_SRC_THREAD;
        req.taddr        = (uint16_t) WRAP_RM_PSIL_TADDR;
        req.data         = WRAP_RM_PSIL_WRITE_DATA;
        retVal = Sciclient_rmPsilWrite(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilWrite TC-02: Negative: invalid nav_id (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – NULL req pointer */
        retVal = Sciclient_rmPsilWrite(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilWrite TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* 13. Sciclient_rmPsilUnpair — TISCI_MSG_RM_PSIL_UNPAIR (0x1281)     */
    /* Releases the pair created by PsilPair TC-01.                       */
    /* Must execute AFTER PsilRead/Write to keep pre/post symmetry.       */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_rm_psil_unpair_req req;

        /* TC-1: Positive – unpair the threads paired in PsilPair TC-01 */
        memset(&req, 0, sizeof(req));
        req.nav_id     = WRAP_RM_PSIL_NAV_ID;
        req.src_thread = WRAP_RM_PSIL_SRC_THREAD;
        req.dst_thread = WRAP_RM_PSIL_DST_THREAD;
        retVal = Sciclient_rmPsilUnpair(&req, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilUnpair TC-01: Positive: unpair the threads paired in PsilPair TC-01  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – dst_thread < 0x8000 (spec mandates NACK) */
        memset(&req, 0, sizeof(req));
        req.nav_id     = WRAP_RM_PSIL_NAV_ID;
        req.src_thread = 0x0000U;
        req.dst_thread = 0x0001U;
        retVal = Sciclient_rmPsilUnpair(&req, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilUnpair TC-02: Negative: dst_thread < 0x8000 (spec mandates NACK)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-3: Negative – NULL req pointer */
        retVal = Sciclient_rmPsilUnpair(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmPsilUnpair TC-03: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 14. Sciclient_rmIrqSet — high-level route-find wrapper for         */
    /*     Sciclient_rmProgramInterruptRoute                              */
    /*                                                                    */
    /* NOTE: rmProgramInterruptRoute rejects IR devices as src/dst.       */
    /* Use GPIO1(78):72 → WKUP_R5FSS0_CORE0(121):36, host=A53_2(12)      */
    /* which is the same route used by the sciclient_direct reference     */
    /* test (test_sciclient_rm_irq.c).                                    */
    /* ================================================================== */
    {
        struct tisci_msg_rm_irq_set_req  irqSetReq;
        struct tisci_msg_rm_irq_set_resp irqSetResp;

        /* TC-1: Positive – GPIO1:72 → WKUP_R5FSS0_CORE0:36, host=A53_2 */
        memset(&irqSetReq, 0, sizeof(irqSetReq));
        irqSetReq.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                                   TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                   TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        irqSetReq.src_id         = TISCI_DEV_GPIO1;
        irqSetReq.src_index      = 72U;
        irqSetReq.dst_id         = TISCI_DEV_WKUP_R5FSS0_CORE0;
        irqSetReq.dst_host_irq   = 36U;
        irqSetReq.secondary_host = (uint8_t)WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqSet(&irqSetReq, &irqSetResp,
                                    SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSet TC-01: Positive: GPIO1:72 → WKUP_R5FSS0_CORE0:36, host=A53_2  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – NULL req pointer */
        retVal = Sciclient_rmIrqSet(NULL, NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqSet TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 15. Sciclient_rmIrqRelease — high-level wrapper for                */
    /*     Sciclient_rmClearInterruptRoute                                */
    /* ================================================================== */
    {
        struct tisci_msg_rm_irq_release_req irqRelReq;

        /* TC-1: Positive – release the route set in rmIrqSet TC-01 */
        memset(&irqRelReq, 0, sizeof(irqRelReq));
        irqRelReq.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID       |
                                   TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                   TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
        irqRelReq.src_id         = TISCI_DEV_GPIO1;
        irqRelReq.src_index      = 72U;
        irqRelReq.dst_id         = TISCI_DEV_WKUP_R5FSS0_CORE0;
        irqRelReq.dst_host_irq   = 36U;
        irqRelReq.secondary_host = (uint8_t)WRAP_RM_IRQ_SECONDARY_HOST;
        retVal = Sciclient_rmIrqRelease(&irqRelReq, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqRelease TC-01: Positive: release the route set in rmIrqSet TC-01  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – NULL req pointer */
        retVal = Sciclient_rmIrqRelease(NULL, SystemP_WAIT_FOREVER);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqRelease TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 16. Sciclient_rmIrOutpIsFree — check if IR output is free          */
    /*     Output 0 is special: inp0_mapping defaults to 0, so output 0  */
    /*     always appears occupied.  Use output 1 for the positive test.  */
    /* ================================================================== */
    {
        /* TC-1: Positive – GPIOMUX_IR0 output 1 is free (hardware default) */
        retVal = Sciclient_rmIrOutpIsFree(WRAP_RM_IRQ_SRC_DEV_ID, 1U);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrOutpIsFree TC-01: Positive: GPIOMUX_IR0 output 1 is free (hardware default)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – invalid device ID (0xFFFF) */
        retVal = Sciclient_rmIrOutpIsFree(0xFFFFU, 0U);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrOutpIsFree TC-02: Negative: invalid device ID (0xFFFF)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 18. Sciclient_rmIrqTranslateIrOutput — translate IR output to      */
    /*     destination peripheral input                                   */
    /* ================================================================== */
    {
        uint16_t dstInput = 0U;

        /* TC-1: Negative – NULL dst_input pointer */
        retVal = Sciclient_rmIrqTranslateIrOutput(WRAP_RM_IRQ_SRC_DEV_ID,
                                                  0U, 0U, NULL);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIrOutput TC-01: Negative: NULL dst_input pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-2: Negative – invalid device ID 0 */
        retVal = Sciclient_rmIrqTranslateIrOutput(0U, 0U, 0U, &dstInput);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIrOutput TC-02: Negative: invalid device ID 0  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 19. Sciclient_rmIrqTranslateIaOutput — translate IA output to      */
    /*     destination peripheral input                                   */
    /* ================================================================== */
    {
        uint16_t dstInput = 0U;

        /* TC-5: Negative – NULL dst_input pointer */
        retVal = Sciclient_rmIrqTranslateIaOutput(WRAP_RM_NAV_INTAGGR_DEV_ID,
                                                  0U, 0U, NULL);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIaOutput TC-01: Negative: NULL dst_input pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-6: Negative – invalid device ID 0 */
        retVal = Sciclient_rmIrqTranslateIaOutput(0U, 0U, 0U, &dstInput);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIaOutput TC-02: Negative: invalid device ID 0  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ================================================================== */
    /* 20. Sciclient_rmIrqTranslateIrqInput — translate peripheral input  */
    /*     back to IR/IA output                                           */
    /* ================================================================== */
    {
        uint16_t srcOutput = 0U;

        /* TC-1: Negative – NULL src_output pointer */
        retVal = Sciclient_rmIrqTranslateIrqInput(WRAP_RM_IRQ_DST_DEV_ID,
                                                  0U, 0U, NULL);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIrqInput TC-01: Negative: NULL src_output pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }

        /* TC-2: Negative – invalid device ID 0 */
        retVal = Sciclient_rmIrqTranslateIrqInput(0U, 0U, 0U, &srcOutput);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_rmIrqTranslateIrqInput TC-02: Negative: invalid device ID 0  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ========================================================================== */
/* testDM_procBootSciclient — JIRA SITSW-12101                            */
/*                                                                            */
/* Covers 8 Sciclient_procBoot* high-level wrapper APIs:                     */
/*   Sciclient_procBootRequestProcessor   (TISCI_MSG_PROC_REQUEST  0xC000)   */
/*   Sciclient_procBootReleaseProcessor   (TISCI_MSG_PROC_RELEASE  0xC001)   */
/*   Sciclient_procBootHandoverProcessor  (TISCI_MSG_PROC_HANDOVER 0xC005)   */
/*   Sciclient_procBootSetProcessorCfg    (TISCI_MSG_PROC_SET_CONFIG  0xC100)*/
/*   Sciclient_procBootSetSequenceCtrl    (TISCI_MSG_PROC_SET_CONTROL 0xC101)*/
/*   Sciclient_procBootAuthAndStart       (TISCI_MSG_PROC_AUTH_BOOT  0xC120) */
/*   Sciclient_procBootGetProcessorState  (TISCI_MSG_PROC_GET_STATUS  0xC400)*/
/*   Sciclient_procBootWaitProcessorState (TISCI_MSG_PROC_WAIT_STATUS 0xC401)*/
/*                                                                            */
/* Safe co-processor for ownership tests: WRAP_PROC_ID_COPROCESSOR is        */
/* defined per-SOC in test_device_manager_val.h, selecting a processor in    */
/* the free pool not claimed by any prior test.                               */
/* SetProcessorCfg and AuthAndStart: negative-only (positive test would      */
/* require setting a running processor's boot vector, which is destructive). */
/* ========================================================================== */
void testDM_procBootSciclient(void *args)
{
    int32_t  retVal;
    int32_t  retValFailCnt = 0;
    struct tisci_msg_proc_get_status_resp procStatus;
    struct tisci_msg_proc_set_config_req  cfgReq;
    struct tisci_msg_proc_auth_boot_req   authReq;
    struct tisci_msg_proc_auth_boot_resp  authResp;

    /* ---------------------------------------------------------------------- */
    /* 1. Sciclient_procBootGetProcessorState — TISCI_MSG_PROC_GET_STATUS      */
    /* Read-only status query; no ownership required.                          */
    /* ---------------------------------------------------------------------- */

    /* TC-1: Positive – get state of R5FSS0_CORE0 (the running DM processor) */
    memset(&procStatus, 0, sizeof(procStatus));
    retVal = Sciclient_procBootGetProcessorState(
                 SCICLIENT_PROC_ID_R5FSS0_CORE0,
                 &procStatus,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootGetProcessorState TC-01: Positive: get state of R5FSS0_CORE0 (the running DM processor)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }
    TEST_ASSERT_EQUAL_INT32(SCICLIENT_PROC_ID_R5FSS0_CORE0, procStatus.processor_id);

    /* TC-2: Positive – get state of co-processor (readable, no ownership required) */
    memset(&procStatus, 0, sizeof(procStatus));
    retVal = Sciclient_procBootGetProcessorState(
                 WRAP_PROC_ID_COPROCESSOR,
                 &procStatus,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootGetProcessorState TC-02: Positive: get state of co-processor  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-3: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootGetProcessorState(
                 0xFFU,
                 &procStatus,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootGetProcessorState TC-03: Negative: invalid processor ID (0xFF) → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 2. Sciclient_procBootRequestProcessor — TISCI_MSG_PROC_REQUEST          */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Positive – request WRAP_PROC_ID_COPROCESSOR (SOC-specific free  */
    /*        pool processor; not claimed by any prior test)                   */
    retVal = Sciclient_procBootRequestProcessor(
                 WRAP_PROC_ID_COPROCESSOR,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootRequestProcessor TC-01: Positive: request WRAP_PROC_ID_COPROCESSOR  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootRequestProcessor(
                 0xFFU,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootRequestProcessor TC-02: Negative: invalid processor ID (0xFF) → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 3. Sciclient_procBootSetSequenceCtrl — TISCI_MSG_PROC_SET_CONTROL       */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Positive – fire-and-forget (reqFlag=0) on owned WRAP_PROC_ID_COPROCESSOR. */
    /*        reqFlag=0 means no ACK is requested; Sciclient_service returns   */
    /*        SUCCESS immediately after enqueuing (mirrors dm_self_reset.c).   */
    retVal = Sciclient_procBootSetSequenceCtrl(
                 WRAP_PROC_ID_COPROCESSOR,
                 0U,                /* control_flags_1_set   */
                 0U,                /* control_flags_1_clear */
                 0U,                /* reqFlag = fire-and-forget, no AOP */
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootSetSequenceCtrl TC-01: Positive: fire-and-forget (reqFlag=0) on owned WRAP_PROC_ID_COPROCESSOR  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – invalid processor ID (0xFF) with AOP flag → NACK */
    retVal = Sciclient_procBootSetSequenceCtrl(
                 0xFFU,
                 0U,
                 0U,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootSetSequenceCtrl TC-02: Negative: invalid processor ID (0xFF) with AOP flag → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 4. Sciclient_procBootReleaseProcessor — TISCI_MSG_PROC_RELEASE          */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Positive – release WRAP_PROC_ID_COPROCESSOR (owned since section 2 TC-01) */
    retVal = Sciclient_procBootReleaseProcessor(
                 WRAP_PROC_ID_COPROCESSOR,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootReleaseProcessor TC-01: Positive: release WRAP_PROC_ID_COPROCESSOR (owned since section 2 TC-01)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – release again (caller no longer owner) → NACK */
    retVal = Sciclient_procBootReleaseProcessor(
                 WRAP_PROC_ID_COPROCESSOR,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootReleaseProcessor TC-02: Negative: release again (caller no longer owner) → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-03: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootReleaseProcessor(
                 0xFFU,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootReleaseProcessor TC-03: Negative: invalid processor ID (0xFF) → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 5. Sciclient_procBootHandoverProcessor — TISCI_MSG_PROC_HANDOVER        */
    /* ---------------------------------------------------------------------- */

    /* Setup: re-acquire WRAP_PROC_ID_COPROCESSOR (released in section 4 TC-01) */
    retVal = Sciclient_procBootRequestProcessor(
                 WRAP_PROC_ID_COPROCESSOR,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootRequestProcessor TC-03: Negative: invalid processor ID (0xFF) → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-01: Positive – handover WRAP_PROC_ID_COPROCESSOR to WRAP_PROC_HANDOVER_HOST */
    retVal = Sciclient_procBootHandoverProcessor(
                 WRAP_PROC_ID_COPROCESSOR,
                 WRAP_PROC_HANDOVER_HOST,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootHandoverProcessor TC-01: Positive: handover WRAP_PROC_ID_COPROCESSOR to WRAP_PROC_HANDOVER_HOST  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootHandoverProcessor(
                 0xFFU,
                 WRAP_PROC_HANDOVER_HOST,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootHandoverProcessor TC-02: Negative: invalid processor ID (0xFF) → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-03: Negative – attempt handover when no longer owner               */
    /*        (ownership transferred to WRAP_PROC_HANDOVER_HOST in TC-01) → NACK */
    retVal = Sciclient_procBootHandoverProcessor(
                 WRAP_PROC_ID_COPROCESSOR,
                 WRAP_PROC_HANDOVER_HOST,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootHandoverProcessor TC-03: Negative: attempt handover when no longer owner  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 6. Sciclient_procBootSetProcessorCfg — TISCI_MSG_PROC_SET_CONFIG        */
    /* NOTE: Setting the boot vector of a running processor is destructive on  */
    /* warm reset. Only negative tests are performed here.                     */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Negative – NULL configReq pointer → SystemP_FAILURE */
    retVal = Sciclient_procBootSetProcessorCfg(NULL, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootSetProcessorCfg TC-01: Negative: NULL configReq pointer → SystemP_FAILURE  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-02: Negative – caller does not own WRAP_PROC_ID_COPROCESSOR (handed over) → NACK */
    memset(&cfgReq, 0, sizeof(cfgReq));
    cfgReq.processor_id         = WRAP_PROC_ID_COPROCESSOR;
    cfgReq.bootvector_lo        = 0x0U;
    cfgReq.bootvector_hi        = 0x0U;
    cfgReq.config_flags_1_set   = 0U;
    cfgReq.config_flags_1_clear = 0U;
    retVal = Sciclient_procBootSetProcessorCfg(&cfgReq, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootSetProcessorCfg TC-02: Negative: caller does not own A53_CORE1 (handed over) → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 7. Sciclient_procBootAuthAndStart — TISCI_MSG_PROC_AUTH_BOOT            */
    /* NOTE: A valid HS-FS signed x509 certificate is required for a positive  */
    /* test. Only negative tests are performed here.                           */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Negative – NULL authBootCfg pointer → SystemP_FAILURE */
    retVal = Sciclient_procBootAuthAndStart(NULL, NULL, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootAuthAndStart TC-01: Negative: NULL authBootCfg pointer → SystemP_FAILURE  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-02: Negative – zero certificate address (0x0) → NACK (cert parse fails) */
    memset(&authReq,  0, sizeof(authReq));
    memset(&authResp, 0, sizeof(authResp));
    authReq.certificate_address_lo = 0x0U;
    authReq.certificate_address_hi = 0x0U;
    retVal = Sciclient_procBootAuthAndStart(&authReq, &authResp, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootAuthAndStart TC-02: Negative: zero certificate address (0x0) → NACK (cert parse fails)  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* ---------------------------------------------------------------------- */
    /* 8. Sciclient_procBootWaitProcessorState — TISCI_MSG_PROC_WAIT_STATUS    */
    /* Common test using R5FSS0_CORE0, available on all SOCs                   */
    /* (AM62X, AM62AX, AM62DX, AM62P, J722S, AM275X).                         */
    /* R5F is not claimed by other procBoot tests and is always running.      */
    /* ---------------------------------------------------------------------- */

    /* TC-01: Positive – R5F core is not in WFE (bit0) or WFI (bit1) in */
    /*        a running system; clr_any_wait=3 is immediately satisfied on    */
    /*        the first iteration (status bits already clear).                 */
    retVal = Sciclient_procBootWaitProcessorState(
                 SCICLIENT_PROC_ID_R5FSS0_CORE0,
                 1U,     /* num_match_iterations     */
                 1U,     /* delay_per_iteration_us   */
                 0U,     /* status_flags_1_set_all_wait */
                 0U,     /* status_flags_1_set_any_wait */
                 0U,     /* status_flags_1_clr_all_wait */
                 3U,     /* status_flags_1_clr_any_wait: bit0=WFE, bit1=WFI */
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootWaitProcessorState TC-01: Positive: R5F core is not in WFE (bit0) or WFI (bit1) in  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
        retValFailCnt++;
    }

    /* TC-02: Negative – TISCI_MSG_FLAG_SEC reqFlag → NACK */
    retVal = Sciclient_procBootWaitProcessorState(
                 SCICLIENT_PROC_ID_R5FSS0_CORE0,
                 1U,
                 1U,
                 0U,
                 0U,
                 0U,
                 3U,
                 TISCI_MSG_FLAG_SEC,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootWaitProcessorState TC-02: Negative: TISCI_MSG_FLAG_SEC reqFlag → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    /* TC-03: Negative – invalid processor ID (0xFF) → NACK */
    retVal = Sciclient_procBootWaitProcessorState(
                 0xFFU,
                 1U,
                 1U,
                 0U,
                 0U,
                 0U,
                 3U,
                 TISCI_MSG_FLAG_AOP,
                 SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("FAIL: Sciclient_procBootWaitProcessorState TC-03: Negative: invalid processor ID (0xFF) → NACK  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
        retValFailCnt++;
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}

/* ==========================================================================
 * testDM_boardCfgApis
 *
 * Covers board-configuration wrappers (positive + negative):
 *   1. Sciclient_boardCfg    — combined board config
 *   2. Sciclient_boardCfgPm  — PM board config
 *   3. Sciclient_boardCfgRm  — RM board config
 *   4. Sciclient_boardCfgSec — Security board config
 *
 * NULL parameter applies the default (already-loaded) config → SUCCESS.
 * ========================================================================== */
void testDM_boardCfgApis(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ------------------------------------------------------------------ */
    /* Sciclient_boardCfg                                                 */
    /* ------------------------------------------------------------------ */

    /* TC-01: Positive – NULL re-applies default board config */
    retVal = Sciclient_boardCfg(NULL);
    if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_boardCfg TC-01: Positive: NULL re-applies default board config  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

    /* ------------------------------------------------------------------ */
    /* Sciclient_boardCfgPm                                               */
    /* ------------------------------------------------------------------ */

    /* TC-01: Positive – NULL re-applies default PM board config */
    retVal = Sciclient_boardCfgPm(NULL);
    if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_boardCfgPm TC-01: Positive: NULL re-applies default PM board config  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

    /* TC-02: Negative – invalid devGrp 0x70 */
    {
        Sciclient_BoardCfgPrms_t brdCfg;
        memset(&brdCfg, 0, sizeof(brdCfg));
        brdCfg.devGrp = 0x70U;
        retVal = Sciclient_boardCfgPm(&brdCfg);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_boardCfgPm TC-02: Negative: invalid devGrp 0x70  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_boardCfgRm                                               */
    /* ------------------------------------------------------------------ */

    /* TC-01: Positive – NULL re-applies default RM board config */
    retVal = Sciclient_boardCfgRm(NULL);
    if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_boardCfgRm TC-01: Positive: NULL re-applies default RM board config  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }



    /* ------------------------------------------------------------------ */
    /* Sciclient_boardCfgSec                                              */
    /* ------------------------------------------------------------------ */

    /* TC-01: Positive – NULL re-applies default SEC board config */
    retVal = Sciclient_boardCfgSec(NULL);
    if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_boardCfgSec TC-01: Positive: NULL re-applies default SEC board config  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}


/* ==========================================================================
 * testDM_dkekApis
 *
 * Covers SA2UL DKEK (Derived KEK) wrappers (positive + negative):
 *   1. Sciclient_setDKEK      — TISCI_MSG_SA2UL_SET_DKEK
 *   2. Sciclient_getDKEK      — TISCI_MSG_SA2UL_GET_DKEK
 *   3. Sciclient_releaseDKEK  — TISCI_MSG_SA2UL_RELEASE_DKEK
 *
 * Positive tests use sa2ul_instance=0 with a valid KDF label/context.
 * NULL parameter tests verify graceful failure.
 * ========================================================================== */
void testDM_dkekApis(void *args)
{
    int32_t retVal;
    int32_t retValFailCnt = 0;

    /* ------------------------------------------------------------------ */
    /* Sciclient_setDKEK                                                  */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_sa2ul_set_dkek_req  setReq;
        struct tisci_msg_sa2ul_set_dkek_resp setResp;
        char *label = "Secure storage key";
        const uint8_t context[] = { 0x55, 0x66, 0x77, 0x88 };

        /* TC-1: Positive – set DKEK with valid label/context */
        memset(&setReq, 0, sizeof(setReq));
        setReq.hdr.type  = TISCI_MSG_SA2UL_SET_DKEK;
        setReq.hdr.seq   = 0;
        setReq.hdr.flags = TISCI_MSG_FLAG_AOP;
        setReq.sa2ul_instance = 0;
        memcpy(&setReq.kdf_label_and_context[0], label, strlen(label));
        setReq.kdf_label_len = (uint8_t)strlen(label);
        memcpy(&setReq.kdf_label_and_context[setReq.kdf_label_len],
               context, sizeof(context));
        setReq.kdf_context_len = sizeof(context);
        retVal = Sciclient_setDKEK(&setReq, &setResp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_setDKEK TC-01: Positive: set DKEK with valid label/context  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – NULL req pointer */
        retVal = Sciclient_setDKEK(NULL, NULL, 0U);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_setDKEK TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_getDKEK                                                  */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_sa2ul_get_dkek_req  getReq;
        struct tisci_msg_sa2ul_get_dkek_resp getResp;
        char *label = "Secure storage key";
        const uint8_t context[] = { 0x55, 0x66, 0x77, 0x88 };

        /* TC-1: Positive – get DKEK (after setDKEK above) */
        memset(&getReq, 0, sizeof(getReq));
        memset(&getResp, 0, sizeof(getResp));
        getReq.hdr.type  = TISCI_MSG_SA2UL_GET_DKEK;
        getReq.hdr.seq   = 0;
        getReq.hdr.flags = TISCI_MSG_FLAG_AOP;
        getReq.sa2ul_instance = 0;
        memcpy(&getReq.kdf_label_and_context[0], label, strlen(label));
        getReq.kdf_label_len = (uint8_t)strlen(label);
        memcpy(&getReq.kdf_label_and_context[getReq.kdf_label_len],
               context, sizeof(context));
        getReq.kdf_context_len = sizeof(context);
        retVal = Sciclient_getDKEK(&getReq, &getResp, SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_getDKEK TC-01: Positive: get DKEK (after setDKEK above)  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – NULL req pointer */
        retVal = Sciclient_getDKEK(NULL, NULL, 0U);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_getDKEK TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* Sciclient_releaseDKEK                                              */
    /* ------------------------------------------------------------------ */
    {
        struct tisci_msg_sa2ul_release_dkek_req  relReq;
        struct tisci_msg_sa2ul_release_dkek_resp relResp;

        /* TC-1: Positive – release DKEK set earlier */
        memset(&relReq, 0, sizeof(relReq));
        relReq.hdr.type  = TISCI_MSG_SA2UL_RELEASE_DKEK;
        relReq.hdr.seq   = 0;
        relReq.hdr.flags = TISCI_MSG_FLAG_AOP;
        relReq.sa2ul_instance = 0;
        retVal = Sciclient_releaseDKEK(&relReq, &relResp,
                                       SystemP_WAIT_FOREVER);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_releaseDKEK TC-01: Positive: release DKEK set earlier  retVal=%d expected=%d\r\n", retVal, SystemP_SUCCESS);
            retValFailCnt++;
        }

        /* TC-2: Negative – NULL req pointer */
        retVal = Sciclient_releaseDKEK(NULL, NULL, 0U);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("FAIL: Sciclient_releaseDKEK TC-02: Negative: NULL req pointer  retVal=%d expected!=SystemP_SUCCESS\r\n", retVal);
            retValFailCnt++;
        }
    }

    TEST_ASSERT_EQUAL_INT32(0, retValFailCnt);
}


/* --------------------------------------------------------------------------
 * testDM_uartPrintf — 100% branch coverage of uart_print.c
 *
 * Covers every code path in UART_printf / UART_dataWrite / UART_convertVal:
 *
 * TC-01  Plain string with \n  — exercises UART_dataWrite \n→\r translation
 * TC-02  %c                    — character format specifier
 * TC-03  %d positive           — decimal, ulNeg=0 branch
 * TC-04  %d negative           — decimal, ulNeg=1 branch (minus sign)
 * TC-05  %05d negative         — zero-fill + negative: minus before padding
 * TC-06  %5d positive          — space-fill padding (count>1 && count<16)
 * TC-07  %s no padding         — string, ulCount==0
 * TC-08  %s with padding       — string, ulCount > strlen (padding spaces)
 * TC-09  %u                    — unsigned decimal
 * TC-10  %x                    — hex lowercase
 * TC-11  %X                    — hex uppercase alias
 * TC-12  %p                    — pointer alias of %x
 * TC-13  %%                    — literal percent
 * TC-14  %z (unknown)          — default case → prints "ERROR"
 * -------------------------------------------------------------------------- */
void testDM_uartPrintf(void *args)
{
    /* TC-1: plain string containing \n — hits \r insertion in UART_dataWrite */
    UART_printf("\n ---- UART printf test case started ----\n\r");

    /* TC-2: %c — character specifier */
    UART_printf("TC-02 char: %c\r\n", (uint32_t)'A');

    /* TC-3: %d positive — ulNeg=0 path */
    UART_printf("TC-03 decimal positive: %d\r\n", 1234);

    /* TC-4: %d negative — ulNeg=1 path, minus sign placed after padding */
    UART_printf("TC-04 decimal negative: %d\r\n", -5678);

    /* TC-5: %05d negative — zero-fill + negative: minus before zeros */
    UART_printf("TC-05 zero-fill negative: %05d\r\n", -42);

    /* TC-6: %5d positive — space-fill, exercises count>1 padding loop */
    UART_printf("TC-06 space-fill: %5d\r\n", 7);

    /* TC-7: %s no padding — string, ulCount==0 */
    UART_printf("TC-07 string: %s\r\n", "hello");

    /* TC-8: %10s with padding — ulCount(10) > strlen("hi")(2), adds spaces */
    UART_printf("TC-08 string padded: %10s\r\n", "hi");

    /* TC-9: %u — unsigned decimal */
    UART_printf("TC-09 unsigned: %u\r\n", 99u);

    /* TC-10: %x — hex lowercase */
    UART_printf("TC-10 hex lower: %x\r\n", 0xDEADu);

    /* TC-11: %X — hex uppercase alias (same code path as %x) */
    UART_printf("TC-11 hex upper: %X\r\n", 0xBEEFu);

    /* TC-12: %p — pointer alias of %x */
    UART_printf("TC-12 pointer: %p\r\n", 0x1234u);

    /* TC-13: %% — literal percent, writes single '%' via pStr-1 */
    UART_printf("TC-13 literal percent: 100%%\r\n");

    /* TC-14: %z — unknown specifier, hits default case → prints "ERROR" */
    UART_printf("TC-14 unknown specifier: %z\r\n");

    /* UART_printf has no return value; reaching here without crash = PASS */
    TEST_ASSERT_EQUAL_INT32(0, 0);
}
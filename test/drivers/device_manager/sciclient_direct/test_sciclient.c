/*
 * Copyright (C) 2024 Texas Instruments Incorporated
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

#include <string.h>
#include "test_device_manager.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_sciclient_version(void *args)
{
    int32_t retVal = SystemP_SUCCESS;

    retVal = Sciclient_getVersionCheck(1U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase Sciclient_getVersionCheck_1 failed");
    }
    else{
        DebugP_log("\r\n Testcase Sciclient_getVersionCheck_1 passed");
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Sciclient_getVersionCheck(0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase Sciclient_getVersionCheck_0 failed\r\n");
    }
    else{
        DebugP_log("\r\n Testcase Sciclient_getVersionCheck_0 passed\r\n");
    }

}

void test_sciclient_rm_ir_output(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint16_t irId, outp;
    uint32_t i;
#if defined (SOC_AM62X) || defined(SOC_AM62AX)
    uint16_t validIrDevIds[4] = {
        TISCI_DEV_CMP_EVENT_INTROUTER0,
        TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
        TISCI_DEV_WKUP_MCU_GPIOMUX_INTROUTER0,
        TISCI_DEV_TIMESYNC_EVENT_ROUTER0,
    };
#else
    uint16_t validIrDevIds[4] = {
        TISCI_DEV_CMP_EVENT_INTROUTER0,
        TISCI_DEV_MAIN_GPIOMUX_INTROUTER0,
        TISCI_DEV_MCU_MCU_GPIOMUX_INTROUTER0,
        TISCI_DEV_TIMESYNC_EVENT_INTROUTER0,
    };
#endif
    uint16_t freeOutp[4] = { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };
    uint16_t maxCheckOutp = 50;

    /* First check with invalid IR instance, valid output number */
    irId = 0xFFFF;
    outp = 0; /* All IRs will have atlease one output :) */

    retVal = Sciclient_rmIrOutpIsFree(irId, outp);
    TEST_ASSERT_NOT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    /* Now check for invalid output numbers in all valid IRs */
    outp = 0xFFFF; /* No IR will have 65535 outputs !! */
    for(i = 0; i < (sizeof(validIrDevIds)/sizeof(validIrDevIds[0])); i++)
    {
        retVal = Sciclient_rmIrOutpIsFree(validIrDevIds[i], outp);
        TEST_ASSERT_NOT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    }

    /* Now check for valid values. */
    /* Assume around 50 outputs for each router, exit the loop after finding first free outp */
    for(i = 0; i < 4; i++)
    {
        for(outp = 0; outp < maxCheckOutp; outp++)
        {
            retVal = Sciclient_rmIrOutpIsFree(validIrDevIds[i], outp);
            if(retVal == SystemP_SUCCESS)
            {
                freeOutp[i] = outp;
                DebugP_log("Found free output for IR %d at %d !\r\n", validIrDevIds[i], outp);
                break;
            }
        }
    }

    for(i = 0; i < 4; i++)
    {
        TEST_ASSERT_LESS_THAN_UINT16(maxCheckOutp, freeOutp[i]);
    }

	DebugP_log("\r\n\r\n Wait for 10 seconds... \r\n");
}

int8_t test_sciclient_procboot(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_FLAG_SEC, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetProcessorCfg(&configReq, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 0,
                                               TISCI_MSG_FLAG_SEC, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_proc_auth_boot_req authReq;
    /* Request TIFS (SYSFW) to authenticate (and decrypt if mentioned in the x509 cert) the image */
    authReq.certificate_address_hi = (uint32_t)(((uint64_t)&r5_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq.certificate_address_lo = (uint32_t)((uint64_t)&r5_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);

    retVal = Sciclient_procBootAuthAndStart(&authReq, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	authReq.certificate_address_hi = (uint32_t)(((uint64_t)&a53_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq.certificate_address_lo = (uint32_t)((uint64_t)&a53_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);

    retVal = Sciclient_procBootAuthAndStart(&authReq, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootAuthAndStart(&authReq, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0, 1, 1, 0, 0, 0, 3, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 1, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 1,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 2, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 2,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0x100, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 0x100,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_proc_get_status_resp proc_get_status;
    proc_get_status.processor_id = 0;
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0, \
                                               &proc_get_status, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootHandoverProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, 10, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetProcessorCfg(&configReq2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_R5FSS0_CORE0, 2, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_R5FSS0_CORE0, 0, 2,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release R5_0_0 in case it was already configured */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Get the status of R5_0_0 */
	struct tisci_msg_proc_get_status_resp proc_status = {0};
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_R5FSS0_CORE0, &proc_status, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	else if(proc_status.processor_id != SCICLIENT_PROC_ID_R5FSS0_CORE0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Request R5_0_0 */
	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Authorize and start R5_0_0 */
	authReq.certificate_address_hi = (uint32_t)(((uint64_t)&r5_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq.certificate_address_lo = (uint32_t)((uint64_t)&r5_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);
    retVal = Sciclient_procBootAuthAndStart(&authReq, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release R5_0_0 */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
	if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release A53_0 in case it was already configured */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Get the status of A53_0 */
	struct tisci_msg_proc_get_status_resp proc_status_a53 = {0};
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0, &proc_status_a53, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	else if(proc_status_a53.processor_id != SCICLIENT_PROC_ID_A53SS0_CORE_0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Request A53_0 */
	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Authorize and start A53_0 */
	authReq.certificate_address_hi = (uint32_t)(((uint64_t)&a53_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq.certificate_address_lo = (uint32_t)((uint64_t)&a53_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);
    retVal = Sciclient_procBootAuthAndStart(&authReq, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release A53_0 */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
	if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootReleaseProcessor(0x1, 0x100, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootReleaseProcessor(0x1, 0x2, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetSequenceCtrl(0x1, 0, 0, 0x100, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootAuthAndStart(NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetProcessorCfg(NULL, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                                  1, 1, 0, 3, 0, 0, 0x100, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                                  1, 1, 0, 3, 0, 0, TISCI_MSG_FLAG_SEC, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_FLAG_AOP, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootHandoverProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, 10, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_proc_get_status_resp proc_get_status2;
    proc_get_status2.processor_id = 0;
	retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                               &proc_get_status2, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                                  1, 1, 0, 3, 0, 0, TISCI_MSG_FLAG_SEC, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                                  1, 1, 0, 3, 0, 0, 1, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                                  1, 1, 0, 3, 0, 0, 0, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                                  1, 1, 0, 3, 0, 0, TISCI_MSG_FLAG_AOP, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                                  1, 1, 0, 3, 0, 0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                                  1, 1, 0, 3, 0, 0, 0, 10);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 0,
                                               0, 10);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 10);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    gSciclientHandle.isSecureMode = 1U;
    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_FLAG_SEC, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetProcessorCfg(&configReq3, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 0,
                                               TISCI_MSG_FLAG_SEC, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_proc_auth_boot_req authReq2;
    /* Request TIFS (SYSFW) to authenticate (and decrypt if mentioned in the x509 cert) the image */
    authReq2.certificate_address_hi = (uint32_t)(((uint64_t)&r5_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq2.certificate_address_lo = (uint32_t)((uint64_t)&r5_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);

    retVal = Sciclient_procBootAuthAndStart(&authReq2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	authReq2.certificate_address_hi = (uint32_t)(((uint64_t)&a53_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq2.certificate_address_lo = (uint32_t)((uint64_t)&a53_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);

    retVal = Sciclient_procBootAuthAndStart(&authReq2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootAuthAndStart(&authReq2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0, 1, 1, 0, 0, 0, 3, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 1, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 1,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 2, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 2,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0x100, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 0x100,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_proc_get_status_resp proc_get_status_2;
    proc_get_status_2.processor_id = 0;
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0, \
                                               &proc_get_status_2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootHandoverProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, 10, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootSetProcessorCfg(&configReq2_1, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_R5FSS0_CORE0, 2, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_R5FSS0_CORE0, 0, 2,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release R5_0_0 in case it was already configured */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Get the status of R5_0_0 */
	struct tisci_msg_proc_get_status_resp proc_status2 = {0};
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_R5FSS0_CORE0, &proc_status2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	else if(proc_status2.processor_id != SCICLIENT_PROC_ID_R5FSS0_CORE0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Request R5_0_0 */
	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Authorize and start R5_0_0 */
	authReq2.certificate_address_hi = (uint32_t)(((uint64_t)&r5_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq2.certificate_address_lo = (uint32_t)((uint64_t)&r5_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);
    retVal = Sciclient_procBootAuthAndStart(&authReq2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release R5_0_0 */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
	if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release A53_0 in case it was already configured */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Get the status of A53_0 */
	struct tisci_msg_proc_get_status_resp proc_status_a53_2 = {0};
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0, &proc_status_a53_2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	else if(proc_status_a53_2.processor_id != SCICLIENT_PROC_ID_A53SS0_CORE_0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Request A53_0 */
	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Authorize and start A53_0 */
	authReq2.certificate_address_hi = (uint32_t)(((uint64_t)&a53_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq2.certificate_address_lo = (uint32_t)((uint64_t)&a53_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);
    retVal = Sciclient_procBootAuthAndStart(&authReq2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release A53_0 */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
	if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientHandle.isSecureMode = 0;

    return failCount;
}

int8_t test_sciclient_secproxyRoutingDescription(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;
    uint16_t txConfigId;

    retVal = Sciserver_SproxyGetResponseConfId(0, &txConfigId);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyGetNotifyConfId(0, &txConfigId);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyGetNotifyConfId(0xFFF, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciserver_SproxyGetResponseConfId(0xFFF, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

return failCount;
}

int8_t test_sciclient(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_contextIdFromIntrNum(3U);
    if(retVal != CSL_EFAIL)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_contextIdFromIntrNum(0U);
    if(retVal == CSL_EFAIL)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    gSciclientHandle.isSecureMode = 1U;
    retVal = Sciclient_getCurrentContext(0x1000U);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x000AU);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_getCurrentContext(0x000BU);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_getCurrentContext(0x000DU);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_getCurrentContext(0x0301U);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_getCurrentContext(0x9031U);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_getCurrentContext(0x9023U);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientHandle.initCount = 1U;
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

   gSciclientHandle.isSecureMode = 1U;
   Sciclient_ConfigPrms_t cfgPrms;
    gSciclientHandle.initCount = 0U;
    cfgPrms.opModeFlag = SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT;
    retVal = Sciclient_init(&cfgPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&reqParam1, &respParam1);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    HwiP_Object tempRespIntrVar = {0};
    HwiP_Object *tempRespIntr[2];

    gSciclientHandle.initCount = 1U;
    tempRespIntr[0] = gSciclientHandle.respIntr[0];
    tempRespIntr[1] = gSciclientHandle.respIntr[1];
    gSciclientHandle.respIntr[0] = NULL;
    gSciclientHandle.respIntr[1] = NULL;
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientHandle.respIntr[0] = tempRespIntr[0];
    gSciclientHandle.respIntr[1] = tempRespIntr[1];

    gSciclientHandle.initCount = 1U;
    tempRespIntr[1] = gSciclientHandle.respIntr[1];
    gSciclientHandle.respIntr[1] = (HwiP_Object*)(&tempRespIntrVar);
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientHandle.respIntr[1] = tempRespIntr[1];

    cfgPrms.opModeFlag = SCICLIENT_SERVICE_OPERATION_MODE_POLLED;
    retVal = Sciclient_init(&cfgPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

   gSciclientHandle.initCount = 2U;
   retVal = Sciclient_deinit();
   if(retVal != SystemP_SUCCESS)
   {
       DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
       failCount++;
   }

    gSciclientHandle.initCount = 0U;
    cfgPrms.isSecureMode = 2U;
    cfgPrms.skipLocalBoardCfgProcess = FALSE;
    retVal = Sciclient_init(&cfgPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    cfgPrms.skipLocalBoardCfgProcess = TRUE;
    retVal = Sciclient_init(&cfgPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    gSciclientHandle.initCount = 0U;
    cfgPrms.opModeFlag = 2U;
    retVal = Sciclient_init(&cfgPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    gSciclientHandle.initCount = 0U;
    retVal = Sciclient_init(NULL);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    cfgPrms.opModeFlag = SCICLIENT_SERVICE_OPERATION_MODE_POLLED;
    retVal = Sciclient_init(&cfgPrms);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientHandle.initCount = 2U;

    gSciclientHandle.isSecureMode = 1U;
    retVal = Sciclient_setDebugConfig();
    gSciclientHandle.isSecureMode = 0U;
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    gSciclientHandle.isSecureMode = 1U;
    retVal = Sciclient_abiCheck();
    gSciclientHandle.isSecureMode = 0U;
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    uint32_t contxtId = SCICLIENT_CONTEXT_MAX_NUM;

    retVal = Sciclient_configPrmsInit(NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_serviceGetThreadIds(NULL, &contxtId, NULL, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_servicePrepareHeader(NULL, NULL, 0, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    Sciclient_ReqPrm_t reqPrm;
    retVal = Sciclient_servicePrepareHeader(&reqPrm, NULL, SCICLIENT_CONTEXT_MAX_NUM, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientHandle.initCount = 1U;
    Sciclient_ConfigPrms_t cfgPrms1;
    cfgPrms1.opModeFlag = 0xFF;
    retVal = Sciclient_init(&cfgPrms1);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }    gSciclientHandle.initCount = 1U;
    retVal = Sciclient_init(NULL);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

return failCount;
}

int8_t test_sciclient_dkek(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    struct tisci_msg_sa2ul_set_dkek_req set_req;
    struct tisci_msg_sa2ul_set_dkek_resp set_resp;
    char *label = "Secure storage key";
    const uint8_t context[] = { 0x55, 0x66, 0x77, 0x88 };
    set_req.hdr.type = TISCI_MSG_SA2UL_SET_DKEK;
    set_req.hdr.seq = 0;
    set_req.hdr.flags = TISCI_MSG_FLAG_AOP;
    set_req.sa2ul_instance = 0;
    memcpy(&set_req.kdf_label_and_context[0], label, sizeof(*label));
    set_req.kdf_label_len = sizeof(*label);
    memcpy(&set_req.kdf_label_and_context[set_req.kdf_label_len], context, sizeof(context));
    set_req.kdf_context_len = sizeof(context);

    retVal = Sciclient_setDKEK(&set_req, &set_resp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_sa2ul_release_dkek_req rel_req;
    struct tisci_msg_sa2ul_release_dkek_resp rel_resp;
    rel_req.hdr.type = TISCI_MSG_SA2UL_RELEASE_DKEK;
    rel_req.hdr.seq = 0;
    rel_req.hdr.flags = TISCI_MSG_FLAG_AOP;
    rel_req.sa2ul_instance = 0;
    retVal = Sciclient_releaseDKEK(&rel_req, &rel_resp, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_sa2ul_get_dkek_req get_req;
    struct tisci_msg_sa2ul_get_dkek_resp get_resp;

    uint8_t context2[] = { 0, 0x55, 0x66, 0x77, 0x88 };
    uint8_t dkek[1][SA2UL_DKEK_KEY_LEN];
    memset(&dkek[0][0],0x00, SA2UL_DKEK_KEY_LEN);
    memset(&get_resp,0x00,sizeof(get_resp));
    /* Set DKEK */
    get_req.hdr.type = TISCI_MSG_SA2UL_GET_DKEK;
    get_req.hdr.seq = 0;
    get_req.hdr.flags = TISCI_MSG_FLAG_AOP;
    get_req.sa2ul_instance = 0;
    context2[0] = 0;
    memcpy(&get_req.kdf_label_and_context[0], label, sizeof(&label));
    get_req.kdf_label_len = sizeof(label);
    memcpy(&get_req.kdf_label_and_context[get_req.kdf_label_len], context2, sizeof(context));
    get_req.kdf_context_len = sizeof(context2);
    retVal = Sciclient_getDKEK(&get_req, &get_resp, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_sa2ul_set_dkek_req set_req3;
    struct tisci_msg_sa2ul_set_dkek_resp set_resp3;
    char *label3 = "Secure storage key";
    const uint8_t context3[] = { 0x55, 0x66, 0x77, 0x88 };
    set_req3.sa2ul_instance = 0;
    memcpy(&set_req3.kdf_label_and_context[0], label3, sizeof(*label3));
    set_req3.kdf_label_len = sizeof(*label3);
    memcpy(&set_req3.kdf_label_and_context[set_req3.kdf_label_len], context3, sizeof(context3));
    set_req3.kdf_context_len = sizeof(context3);

    retVal = Sciclient_setDKEK(&set_req3, &set_resp3, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	struct tisci_msg_sa2ul_get_dkek_req get_req4;
    struct tisci_msg_sa2ul_get_dkek_resp get_resp4;

    uint8_t context4[] = { 0, 0x55, 0x66, 0x77, 0x88 };
    char *label4 = "Secure storage key";
    uint8_t dkek4[1][SA2UL_DKEK_KEY_LEN];
    memset(&dkek4[0][0],0x00, SA2UL_DKEK_KEY_LEN);
    memset(&get_resp4,0x00,sizeof(get_resp4));
    get_req4.sa2ul_instance = 0;
    context4[0] = 0;
    memcpy(&get_req4.kdf_label_and_context[0], label4, sizeof(&label4));
    get_req4.kdf_label_len = sizeof(label4);
    memcpy(&get_req4.kdf_label_and_context[get_req4.kdf_label_len], context4, sizeof(context4));
    get_req4.kdf_context_len = sizeof(context4);
    retVal = Sciclient_getDKEK(&get_req4, &get_resp4, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_sa2ul_release_dkek_req rel_req5;
    struct tisci_msg_sa2ul_release_dkek_resp rel_resp5;
    rel_req5.sa2ul_instance = 0;
    retVal = Sciclient_releaseDKEK(&rel_req5, &rel_resp5, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_sa2ul_set_dkek_req set_req2;
    struct tisci_msg_sa2ul_set_dkek_resp set_resp2;
    char *label2 = "Secure storage key";
    const uint8_t context5[] = { 0x55, 0x66, 0x77, 0x88 };
    set_req2.hdr.type = TISCI_MSG_SA2UL_SET_DKEK;
    set_req2.hdr.seq = 0;
    set_req2.hdr.flags = TISCI_MSG_FLAG_AOP;
    set_req2.sa2ul_instance = 0;
    memcpy(&set_req2.kdf_label_and_context[0], label2, sizeof(&label2));
    set_req2.kdf_label_len = sizeof(label2);
    memcpy(&set_req2.kdf_label_and_context[set_req2.kdf_label_len], context5, sizeof(context5));
    set_req2.kdf_context_len = sizeof(context5);

    struct tisci_msg_sa2ul_release_dkek_req rel_req2;
    struct tisci_msg_sa2ul_release_dkek_resp rel_resp2;
    rel_req2.hdr.type = TISCI_MSG_SA2UL_RELEASE_DKEK;
    rel_req2.hdr.seq = 5;
    rel_req2.hdr.flags = TISCI_MSG_FLAG_AOP;
    rel_req2.sa2ul_instance = 5;

    retVal = Sciclient_setDKEK(&set_req2, &set_resp2, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_releaseDKEK(&rel_req2, &rel_resp2, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_setDKEK(NULL, NULL, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_setDKEK(NULL, NULL, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_releaseDKEK(NULL, NULL, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDKEK(NULL, NULL, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_sa2ul_get_dkek_req getDkekReq;
    struct tisci_msg_sa2ul_get_dkek_resp getDkekResp;
    retVal = Sciclient_getDKEK(&getDkekReq, &getDkekResp, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_firewall(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_firewallSetRegion( &setFwReq, &setFwResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_firewallGetRegion(&fwGetReq, &fwGetResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_msg_fwl_change_owner_info_resp fwCngOwnerInfoResp;

    retVal = Sciclient_firewallChangeOwnerInfo( &fwCngOwnerInfoReq, &fwCngOwnerInfoResp, (-1));
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_firewallChangeOwnerInfo( &fwCngOwnerInfoReq2, &fwCngOwnerInfoResp, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_firewallSetRegion( &setFwReq2, &setFwResp2, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_firewallChangeOwnerInfo(NULL, NULL, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_firewallSetRegion(NULL, NULL, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_firewallGetRegion(NULL, NULL, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    struct tisci_msg_fwl_get_firewall_region_req fwGetReq2;
    struct tisci_msg_fwl_get_firewall_region_resp fwGetResp2;
    retVal = Sciclient_firewallGetRegion(&fwGetReq2, &fwGetResp2, (-1));

    return failCount;
}

int8_t test_sciclient_pm(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    uint32_t moduleState;
    uint32_t resetState;
    uint32_t contextLossState;
    uint32_t parent;
    uint32_t state;
    uint32_t numParent;
    uint64_t respFreqHz;
    uint64_t freqHz;
    uint32_t deviceState = TISCI_MSG_FLAG_DEVICE_WAKE_ENABLED;
    uint32_t  moduleId = 186;
    uint32_t reqFlag = TISCI_MSG_FLAG_AOP;

    retVal = Sciclient_pmSetModuleState(moduleId, deviceState, reqFlag, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleState(moduleId, &moduleState, &resetState, &contextLossState, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleRst(moduleId, 1U, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleRst_flags(moduleId, 1U, reqFlag, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmModuleClkRequest(moduleId, TISCI_DEV_DSS0_DPI_0_IN_CLK, 0, 0, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmModuleGetClkStatus(moduleId, TISCI_DEV_DSS0_DPI_1_OUT_CLK, &state, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkParent(moduleId, TISCI_DEV_DSS0_DPI_1_IN_CLK, TISCI_DEV_DSS0_DPI_1_IN_CLK_PARENT_HSDIV0_16FFT_MAIN_17_HSDIVOUT0_CLK, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkParent(moduleId, TISCI_DEV_DSS0_DPI_1_IN_CLK, &parent, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkNumParent(moduleId, TISCI_DEV_DSS0_DPI_1_IN_CLK, &numParent, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkFreq(moduleId, TISCI_DEV_DSS0_DPI_0_IN_CLK, 10000000U, 0, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmQueryModuleClkFreq(moduleId, TISCI_DEV_DSS0_DPI_0_IN_CLK, 10000000U, &respFreqHz, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkFreq(moduleId, TISCI_DEV_DSS0_DPI_0_IN_CLK, &freqHz, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleState(moduleId, deviceState, 0, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleState(moduleId, deviceState, 3, 0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleState(0xFF, deviceState, 2, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleState(0, &moduleState, &resetState, &contextLossState, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleState(0, &moduleState, &resetState, &contextLossState, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleState(0xFF, &moduleState, &resetState, &contextLossState, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleRst(0x0, 0x0, 0x0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleRst(0xFF, 0x0, 0x0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleRst_flags(0x0, 0x0, 0x0, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleRst_flags(0xFF, 0x0, 0x0, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmModuleClkRequest(0x0, 256U, 0x0, 0x0, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmModuleClkRequest(0xFF, 0x0, 0x0, 0x0, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmModuleGetClkStatus(0x0, 256U, &state, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmModuleGetClkStatus(0xFF, 0x0, &state, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkParent(0x0, 256U, 0x0, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkParent(0x0, 0x0, 256U, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkParent(0xFF, 0x0, 0x0, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkParent(0x0, 256U, &parent, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkParent(0xFF, 0x0U, &parent, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkNumParent(0x0, 256U, &numParent, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkNumParent(0xFF0, 0x0, &numParent, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkFreq(0x0, 256U, 1000005U, 0x1, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkFreq(0xFF, 0x0, 1000005U, 0x1, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmQueryModuleClkFreq(0x0, 256U, 1000005U, &respFreqHz, 10U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmQueryModuleClkFreq(0xFF, 0x0, 1000005U, &respFreqHz, 10U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkFreq(0x0, 256U, &respFreqHz, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkFreq(0xFF, 0x0, &respFreqHz, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_boardcfg(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    /* NULL parameter has default configuration */
    retVal = Sciclient_boardCfgPm(NULL);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* NULL parameter has default configuration */
    retVal = Sciclient_boardCfgRm(NULL);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    Sciclient_BoardCfgPrms_t brdCfg;

    brdCfg.devGrp = 0x70;
    retVal = Sciclient_boardCfgPm(&brdCfg);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDefaultBoardCfgInfo(NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_directWrapper(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    gSciclientHandle.isSecureMode = 1;
    retVal = Sciclient_direct_init();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getVersionCheck(0xFFFFFFF);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_getVersionCheck(0);
    if(retVal == 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientHandle.isSecureMode = 0;

    retVal = Sciclient_getSelfDevIdCore();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getVersionCheck(1U);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_getVersionCheck(0);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientHandle.isSecureMode = 0;
    retVal = Sciclient_getVersionCheck(1U);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_getVersionCheck(0);
    if(retVal != 0)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_direct(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    uint8_t commonHeader = 0;
    uint8_t boardCfgHeader = 0;
    Sciclient_BoardCfgPrms_t inPmPrms = {0};
    Sciclient_BoardCfgPrms_t inRmPrms = {0};

    retVal = Sciclient_service(NULL, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    struct tisci_header tx_msg;
    tx_msg.type = 0x0102U;
    retVal = Sciclient_ProcessPmMessage(0, &tx_msg);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    tx_msg.type = 0x0103U;
    retVal = Sciclient_ProcessPmMessage(0, &tx_msg);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    tx_msg.type = 0x1231U;
    retVal = Sciclient_ProcessRmMessage(&tx_msg);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    tx_msg.type = 0x1234U;
    retVal = Sciclient_ProcessRmMessage(&tx_msg);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    tx_msg.type = 0x0;
    retVal = Sciclient_ProcessRmMessage(&tx_msg);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_boardCfgPrepHeader(NULL, NULL, NULL, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_boardCfgPrepHeader(&commonHeader, NULL, NULL, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_boardCfgPrepHeader(NULL, &boardCfgHeader, NULL, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_boardCfgPrepHeader(NULL, NULL, &inPmPrms, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_boardCfgPrepHeader(NULL, NULL, NULL, &inRmPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_boardCfgPrepHeader(NULL, &boardCfgHeader, NULL, &inRmPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_boardCfgParseHeader(NULL, NULL, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_boardCfgParseHeader(&commonHeader, NULL, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_boardCfgParseHeader(NULL, &inPmPrms, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_boardCfgParseHeader(NULL, NULL, &inRmPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_boardCfgParseHeader(&commonHeader, &inPmPrms, &inRmPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    struct tisci_msg_sys_reset_req requestRst;
    requestRst.domain = 1;
    const Sciclient_ReqPrm_t      reqPrmRst =
    {
        TISCI_MSG_SYS_RESET,
        TISCI_MSG_FLAG_AOP,
        (uint8_t *) &requestRst,
        sizeof(requestRst),
        SystemP_WAIT_FOREVER
    };
    struct tisci_msg_version_resp responseRst;
    Sciclient_RespPrm_t           respPrmRst =
    {
        0,
        (uint8_t *) &responseRst,
        sizeof (responseRst)
    };
    retVal = Sciclient_service(&reqPrmRst, &respPrmRst);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_secureproxy(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_verifyThread(0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_verifyThread(23);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_verifyThread(28);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_verifyThread(100);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_verifyThread(120);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_waitThread(0, 100);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    /* no return type */
    (void)Sciclient_sendMessage(0, NULL, 0, NULL, NULL, 0, 0);

    (void)Sciclient_sendMessage(0, NULL, 0, NULL, NULL, 0, 4);

    HW_WR_REG32(0x4D04303C, 0x55);
    (void)Sciclient_flush(6, 60U);

    (void)Sciclient_flush(22, 60U);
    (void)Sciclient_flush(30, 60U);

    return failCount;
}

int8_t test_sciclient_keyWriting(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_service(&kwProgReqParam, &kwProgRespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&readOtpReqParam1, &readOtpRespParam1);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&writeOTPRowReqParam, &writeOTPRowRespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_lowPowerReq(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_service(&prepSleepReqParam, &prepSleepRespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    prepSleepReqParam.timeout = 0;
    retVal = Sciclient_service(&prepSleepReqParam, &prepSleepRespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&prepSleepPassReqParam, &prepSleepPassRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&setIOIsolationReqParam, &setIOIsolationRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_setdevice(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_service(&setDevReqParam, &setDevRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&setDevRstReqParam, &setDevRstRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&setDevReqParam1, &setDevRespParam1);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&setDevReqParam2, &setDevRespParam2);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_boardcfgRM(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    uint8_t rmBcfgCase1Struct[] = {0x30, 0x82, 0, 0};

    struct tisci_msg_board_config_rm_resp rmBcfgCase1Resp;
    struct tisci_msg_board_config_rm_req rmBcfgCase1Cfg =
    {
        .tisci_boardcfg_rmp_low = (uint32_t)(&rmBcfgCase1Struct),
        .tisci_boardcfg_rm_size = 4U,
        .tisci_boardcfg_rmp_high = 0,
        .tisci_boardcfg_rm_devgrp = 0,
    };

    Sciclient_RespPrm_t rmBcfgCase1RespParam =
    {
        .flags = 0,
        .pRespPayload = (uint8_t *) &rmBcfgCase1Resp,
        .respPayloadSize = (uint32_t) sizeof (rmBcfgCase1Resp),
    };
    Sciclient_ReqPrm_t rmBcfgCase1ReqParam =
    {
        .messageType = 0xC,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmBcfgCase1Cfg,
        .reqPayloadSize = (uint32_t) sizeof (rmBcfgCase1Cfg),
        .timeout = 0,
    };

    uint8_t rmBcfgCase2Struct[] = {0x30, 0x81, 0, 0};

    struct tisci_msg_board_config_rm_resp rmBcfgCase2Resp;
    struct tisci_msg_board_config_rm_req rmBcfgCase2Cfg =
    {
        .tisci_boardcfg_rmp_low = (uint32_t)(&rmBcfgCase2Struct),
        .tisci_boardcfg_rm_size = 4U,
        .tisci_boardcfg_rmp_high = 0,
        .tisci_boardcfg_rm_devgrp = 0,
    };

    Sciclient_RespPrm_t rmBcfgCase2RespParam =
    {
        .flags = 0,
        .pRespPayload = (uint8_t *) &rmBcfgCase2Resp,
        .respPayloadSize = (uint32_t) sizeof (rmBcfgCase2Resp),
    };
    Sciclient_ReqPrm_t rmBcfgCase2ReqParam =
    {
        .messageType = 0xC,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmBcfgCase2Cfg,
        .reqPayloadSize = (uint32_t) sizeof (rmBcfgCase2Cfg),
        .timeout = -1,
    };

    uint8_t rmBcfgCase3Struct[] = {0x30, 0x79, 0, 0};

    struct tisci_msg_board_config_rm_resp rmBcfgCase3Resp;
    struct tisci_msg_board_config_rm_req rmBcfgCase3Cfg =
    {
        .tisci_boardcfg_rmp_low = (uint32_t)(&rmBcfgCase3Struct),
        .tisci_boardcfg_rm_size = 4U,
        .tisci_boardcfg_rmp_high = 0,
        .tisci_boardcfg_rm_devgrp = 0,
    };

    Sciclient_RespPrm_t rmBcfgCase3RespParam =
    {
        .flags = 0,
        .pRespPayload = (uint8_t *) &rmBcfgCase3Resp,
        .respPayloadSize = (uint32_t) sizeof (rmBcfgCase3Resp),
    };
    Sciclient_ReqPrm_t rmBcfgCase3ReqParam =
    {
        .messageType = 0xC,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmBcfgCase3Cfg,
        .reqPayloadSize = (uint32_t) sizeof (rmBcfgCase3Cfg),
        .timeout = -1,
    };

    struct tisci_msg_board_config_rm_resp rmBcfgCase4Resp;
    struct tisci_msg_board_config_rm_req rmBcfgCase4Cfg =
    {
        .tisci_boardcfg_rmp_low = (uint32_t)&bcfg_rm_consumed_by_tifs,
        .tisci_boardcfg_rmp_high = 0x00000000,
        .tisci_boardcfg_rm_size = sizeof(bcfg_rm_consumed_by_tifs),
        .tisci_boardcfg_rm_devgrp = 0,
    };

    Sciclient_RespPrm_t rmBcfgCase4RespParam =
    {
        .flags = 0,
        .pRespPayload = (uint8_t *) &rmBcfgCase4Resp,
        .respPayloadSize = (uint32_t) sizeof (rmBcfgCase4Resp),
    };
    Sciclient_ReqPrm_t rmBcfgCase4ReqParam =
    {
        .messageType = 0xC,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmBcfgCase4Cfg,
        .reqPayloadSize = (uint32_t) sizeof (rmBcfgCase4Cfg),
        .timeout = -1,
    };

    struct tisci_msg_board_config_rm_resp rmBcfgCase5Resp;
    struct tisci_msg_board_config_rm_req rmBcfgCase5Cfg =
    {
        .tisci_boardcfg_rmp_low = (uint32_t)&bcfg_rm_consumed_by_tifs_and_dm,
        .tisci_boardcfg_rmp_high = 0x00000000,
        .tisci_boardcfg_rm_size = sizeof(bcfg_rm_consumed_by_tifs_and_dm),
        .tisci_boardcfg_rm_devgrp = 0,
    };

    Sciclient_RespPrm_t rmBcfgCase5RespParam =
    {
        .flags = 0,
        .pRespPayload = (uint8_t *) &rmBcfgCase5Resp,
        .respPayloadSize = (uint32_t) sizeof (rmBcfgCase5Resp),
    };

    Sciclient_ReqPrm_t rmBcfgCase5ReqParam =
    {
        .messageType = 0xC,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmBcfgCase5Cfg,
        .reqPayloadSize = (uint32_t) sizeof (rmBcfgCase5Cfg),
        .timeout = -1,
    };
    Sciclient_RespPrm_t rmBcfgCase6RespParam =
    {
        .flags = 0,
        .pRespPayload = (uint8_t *) &rmBcfgCase4Resp,
        .respPayloadSize = (uint32_t) sizeof (rmBcfgCase4Resp),
    };
    Sciclient_ReqPrm_t rmBcfgCase6ReqParam =
    {
        .messageType = 0xC,
        .flags = 2,
        .pReqPayload = (const uint8_t *) &rmBcfgCase4Cfg,
        .reqPayloadSize = (uint32_t) sizeof (rmBcfgCase4Cfg),
        .timeout = 0,
    };

    retVal = Sciclient_service(&rmBcfgCase2ReqParam, &rmBcfgCase2RespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&rmBcfgCase1ReqParam, &rmBcfgCase1RespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&rmBcfgCase3ReqParam, &rmBcfgCase3RespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&rmBcfgCase4ReqParam, &rmBcfgCase4RespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&rmBcfgCase5ReqParam, &rmBcfgCase5RespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&rmBcfgCase6ReqParam, &rmBcfgCase6RespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_boardCfgParseHdr(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    Sciclient_BoardCfgPrms_t mockPmPrms;
    Sciclient_BoardCfgPrms_t mockRmPrms;

    Sciclient_DirectExtBootBoardCfgDesc mockDescs =
    {
        .type = 0xD,
    };

    Sciclient_DirectBoardCfgDescTable mockBcfgDescTbl =
    {
        .descs[0] = mockDescs,
        .num_elems = 1,
    };

    Sciclient_DirectExtBootX509Comp mockBootComp =
    {
        .comp_type = 0x11,
        .dest_addr = (uint64_t)(&mockBcfgDescTbl),
    };

    Sciclient_DirectExtBootX509Table mockX509Tbl =
    {
        .comps[0] = mockBootComp,
        .magic_word = { 'E', 'X', 'T', 'B', 'O', 'O', 'T', 0 },
        .num_comps = 1,
    };

    Sciclient_DirectExtBootX509Table mockX509TblMagicWord =
    {
        .comps[0] = mockBootComp,
        .magic_word = { 'E', 'X', 'T', 'B', 'O', 'O', 'T', 1 },
        .num_comps = 1,
    };

    retVal = Sciclient_boardCfgParseHeader((uint8_t *)(&mockX509Tbl), &mockPmPrms, &mockRmPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_boardCfgParseHeader((uint8_t *)(&mockX509TblMagicWord), &mockPmPrms, &mockRmPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_boardCfgPrepHdr(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    Sciclient_BoardCfgPrms_t mockPmPrms;
    Sciclient_BoardCfgPrms_t mockRmPrms;

    Sciclient_DirectExtBootBoardCfgDesc mockDescs =
    {
        .type = 0xD,
    };

    Sciclient_DirectBoardCfgDescTable mockBcfgDescTbl =
    {
        .descs[0] = mockDescs,
        .num_elems = 1,
    };

    Sciclient_DirectExtBootX509Comp mockBootComp =
    {
        .comp_type = 0x11,
        .dest_addr = (uint64_t)(&mockBcfgDescTbl),
    };

    Sciclient_DirectExtBootX509Table mockX509Tbl =
    {
        .comps[0] = mockBootComp,
        .magic_word = { 'E', 'X', 'T', 'B', 'O', 'O', 'T', 0 },
        .num_comps = 1,
    };

    retVal = Sciclient_boardCfgPrepHeader(NULL, NULL, NULL, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_boardCfgPrepHeader((uint8_t *)(&mockX509Tbl), (uint8_t *)(&mockBcfgDescTbl), &mockPmPrms, &mockRmPrms);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_boardCfgPrepHeader(NULL, NULL, &mockPmPrms, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_boardCfgPrepHeader((uint8_t *)(&mockX509Tbl), (uint8_t *)(&mockBcfgDescTbl), NULL, &mockRmPrms);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_boardCfgPrepHeader((uint8_t *)(&mockX509Tbl), NULL, &mockPmPrms, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_boardCfgPrepHeader((uint8_t *)(&mockX509Tbl), NULL, &mockPmPrms, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_processPmMessage(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_ProcessPmMessage(0, &mockTxMsg);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_queryFwCaps(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_service(&queryFwCapsReqParam, &queryFwCapsRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    queryFwCapsRespParam.pRespPayload = NULL;
    queryFwCapsReqParam.flags = 0;
    retVal = Sciclient_service(&queryFwCapsReqParam, &queryFwCapsRespParam);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_serviceSecProxy(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;
    uint32_t temp_seq_id;

    retVal = Sciclient_serviceSecureProxy(&ReqParam, &RespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    ReqParam.timeout = 2;
    retVal = Sciclient_serviceSecureProxy(&ReqParam, &RespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    ReqParam.timeout = 0;
    retVal = Sciclient_serviceSecureProxy(&ReqParam, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    ReqParam.reqPayloadSize = 0;
    retVal = Sciclient_serviceSecureProxy(&ReqParam, &RespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    ReqParam.reqPayloadSize = 0xFFFFFFFF;
    ReqParam.pReqPayload = NULL;
    retVal = Sciclient_serviceSecureProxy(&ReqParam, &RespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    ReqParam.reqPayloadSize = (uint32_t) sizeof (mock_req);
    ReqParam.pReqPayload = (const uint8_t *) &mock_req;
    RespParam.respPayloadSize = 0xFFFFFFFF;
    RespParam.pRespPayload = NULL;
    retVal = Sciclient_serviceSecureProxy(&ReqParam, &RespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_serviceSecureProxy(NULL, &RespParam);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    temp_seq_id = gSciclientHandle.currSeqId;
    gSciclientHandle.currSeqId++;
    retVal = Sciclient_service(&reqParam2, &respParam2);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientHandle.currSeqId = temp_seq_id;

    retVal = Sciclient_service(&readOtpReqParam2, &readOtpRespParam2);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    readOtpReqParam2.timeout = 0;
    retVal = Sciclient_service(&readOtpReqParam2, &readOtpRespParam2);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

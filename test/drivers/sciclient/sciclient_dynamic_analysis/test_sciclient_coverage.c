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
#include "test_sciclient.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

extern CSL_SecProxyCfg gSciclientSecProxyCfg;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static CSL_SecProxyThreadStatus threadStatus;

int8_t test_csl_sec_proxy(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;
    uint32_t threadNumMax=0;
    uint8_t dataBytes[5];
    uint8_t *pData = dataBytes;
    uint32_t numBytes=1;
    uint32_t errNumBytes = 0xFFFF;
    uint32_t checkThreadRead=0;

    retVal = CSL_secProxyGetRevision(&secProxyCfg);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = CSL_secProxyGetNumThreads(&secProxyCfg);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    threadNumMax = CSL_secProxyGetNumThreads(&secProxyCfg);
    for(checkThreadRead=0;checkThreadRead<threadNumMax;checkThreadRead++)
    {
        CSL_secProxyGetThreadStatus(&secProxyCfg,checkThreadRead,&threadStatus);
        if(threadStatus.dir==1U)
        {
            break;
        }
    }

    /* No return type */
    (void)CSL_secProxyAccessTarget(&secProxyCfg, checkThreadRead, pData, numBytes, localFpMemAccess);

    /* No return type */
    (void)CSL_secProxyAccessTarget(&secProxyCfg, checkThreadRead, pData, errNumBytes, localFpMemAccess);

    retVal = CSL_secProxyCfgGlobalErrEvtNum(&secProxyCfg, CSL_SEC_PROXY_GLOBAL_ERR_EVT_DISABLE);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* No return type */
    (void)CSL_secProxySetBufferAccessOrderId(&secProxyCfg, 2U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* No return type */
    (void)CSL_secProxyCfg(&secProxyCfg, 0x0ULL, 0x40ULL);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* No return type */
    (void)CSL_secProxyCfg(&secProxyCfg, CSL_DEBUGSS_WRAP0_EXT_APB1_BASE, 0x40ULL);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    CSL_SecProxyThreadCfg threadCfg;
    retVal = CSL_secProxyCfgThread(&secProxyCfg, 1U, &threadCfg);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = CSL_secProxyCfgThread(&secProxyCfg, 0, &threadCfg);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = CSL_secProxyCfgThread(&secProxyCfg, 0xFFFFFFFFU, &threadCfg);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = CSL_secProxyGetDataAddr(&secProxyCfg, 1U, 10U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = CSL_secProxyGetThreadStatus(&secProxyCfg, 1U, &threadStatus);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = CSL_secProxyGetThreadStatus(&secProxyCfg, 31U, &threadStatus);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    for(int threadNum=0; threadNum<100;threadNum++)
    {
        retVal = CSL_secProxyGetThreadStatus(&secProxyCfg, threadNum, &threadStatus);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
            failCount++;
        }

    }
    retVal = CSL_secProxyGetThreadStatus(&test_error_secProxyCfg, 1U, &threadStatus);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = CSL_secProxyGetThreadStatus(&secProxyCfg, 0xFFFFFFFFU, &threadStatus);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_soc_priv(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    retVal = Sciclient_getContext(SCICLIENT_SECURE_CONTEXT, CSL_CORE_ID_1);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getContext(SCICLIENT_NON_SECURE_CONTEXT, CSL_CORE_ID_1);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getContext(SCICLIENT_NON_SECURE_CONTEXT, CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getContext(SCICLIENT_SECURE_CONTEXT, CSL_CORE_ID_A53SS0_0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getContext(SCICLIENT_NON_SECURE_CONTEXT, CSL_CORE_ID_A53SS0_0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getContext(SCICLIENT_NON_SECURE_CONTEXT, CSL_CORE_ID_2);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getContext(SCICLIENT_NON_SECURE_CONTEXT, CSL_CORE_ID_INVALID);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDevId(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDevId(CSL_CORE_ID_1);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDevId(CSL_CORE_ID_A53SS0_0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDevId(CSL_CORE_ID_2);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDevId(CSL_CORE_ID_INVALID);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_procboot(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;
    struct tisci_msg_proc_get_status_resp proc_get_status;

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_1, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_1, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_1, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_1, TISCI_MSG_FLAG_SEC, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_1, SystemP_WAIT_FOREVER);
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
    struct tisci_msg_proc_auth_boot_resp authResp = {0};
    /* Request TIFS (SYSFW) to authenticate (and decrypt if mentioned in the x509 cert) the image */
    authReq.certificate_address_hi = (uint32_t)(((uint64_t)&r5_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq.certificate_address_lo = (uint32_t)((uint64_t)&r5_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);

    retVal = Sciclient_procBootAuthAndStart(&authReq, &authResp, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	authReq.certificate_address_hi = (uint32_t)(((uint64_t)&a53_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq.certificate_address_lo = (uint32_t)((uint64_t)&a53_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);
    retVal = Sciclient_procBootAuthAndStart(&authReq, &authResp, SystemP_WAIT_FOREVER);
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

	retVal = Sciclient_procBootAuthAndStart(&authReq, &authResp, SystemP_WAIT_FOREVER);
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

    proc_get_status.processor_id = 0;
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0, \
                                               &proc_get_status, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootHandoverProcessor(SCICLIENT_PROC_ID_1, 10, SystemP_WAIT_FOREVER);
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

	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_1, 2, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_1, 0, 2,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release R5_0_0 in case it was already configured */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_1, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Get the status of R5_0_0 */
	struct tisci_msg_proc_get_status_resp proc_status = {0};
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_1, &proc_status, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	else if(proc_status.processor_id != SCICLIENT_PROC_ID_1)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Request R5_0_0 */
	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_1, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Authorize and start R5_0_0 */
	authReq.certificate_address_hi = (uint32_t)(((uint64_t)&r5_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq.certificate_address_lo = (uint32_t)((uint64_t)&r5_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);
    retVal = Sciclient_procBootAuthAndStart(&authReq, &authResp, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release R5_0_0 */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_1, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
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
    retVal = Sciclient_procBootAuthAndStart(&authReq, &authResp, SystemP_WAIT_FOREVER);
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

    retVal = Sciclient_procBootAuthAndStart(NULL, NULL, (-1));
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

	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_1, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_1, TISCI_MSG_FLAG_AOP, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootHandoverProcessor(SCICLIENT_PROC_ID_1, 10, 0);
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
                                                  1, 1, 0, 0xFF, 0, 0, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0,
                                                  1, 1, 0, 3, 0, 0, 0, 10);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 0,
                                               0, 10);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_A53SS0_CORE_0, 0, 10);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_1, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_1, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_1, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_1, TISCI_MSG_FLAG_SEC, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_1, SystemP_WAIT_FOREVER);
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
    struct tisci_msg_proc_auth_boot_resp authResp2 = {0};
    /* Request TIFS (SYSFW) to authenticate (and decrypt if mentioned in the x509 cert) the image */
    authReq2.certificate_address_hi = (uint32_t)(((uint64_t)&r5_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq2.certificate_address_lo = (uint32_t)((uint64_t)&r5_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);

    retVal = Sciclient_procBootAuthAndStart(&authReq2, &authResp2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	authReq2.certificate_address_hi = (uint32_t)(((uint64_t)&a53_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq2.certificate_address_lo = (uint32_t)((uint64_t)&a53_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);

    retVal = Sciclient_procBootAuthAndStart(&authReq2, &authResp2, SystemP_WAIT_FOREVER);
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

	retVal = Sciclient_procBootAuthAndStart(&authReq2, &authResp2, SystemP_WAIT_FOREVER);
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

    struct tisci_msg_proc_get_status_resp proc_get_status_2;
    proc_get_status_2.processor_id = 0;
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_A53SS0_CORE_0, \
                                               &proc_get_status_2, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootHandoverProcessor(SCICLIENT_PROC_ID_1, 10, SystemP_WAIT_FOREVER);
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

	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_1, 2, 0,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	retVal = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_1, 0, 2,
                                               TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release R5_0_0 in case it was already configured */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_1, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Get the status of R5_0_0 */
	struct tisci_msg_proc_get_status_resp proc_status2 = {0};
    retVal = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_1, &proc_status2, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
	else if(proc_status2.processor_id != SCICLIENT_PROC_ID_1)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Request R5_0_0 */
	retVal = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_1, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Authorize and start R5_0_0 */
	authReq2.certificate_address_hi = (uint32_t)(((uint64_t)&r5_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq2.certificate_address_lo = (uint32_t)((uint64_t)&r5_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);
    retVal = Sciclient_procBootAuthAndStart(&authReq2, &authResp2, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Release R5_0_0 */
	retVal = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_1, TISCI_MSG_FLAG_AOP, SystemP_WAIT_FOREVER);
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
    if(retVal != SystemP_SUCCESS)
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
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

	/* Authorize and start A53_0 */
	authReq2.certificate_address_hi = (uint32_t)(((uint64_t)&a53_cl0_c0_binary_hs[0] >> 32U) & 0xFFFFFFFFU);
    authReq2.certificate_address_lo = (uint32_t)((uint64_t)&a53_cl0_c0_binary_hs[0] & 0xFFFFFFFFU);
    retVal = Sciclient_procBootAuthAndStart(&authReq2, &authResp2, SystemP_WAIT_FOREVER);
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

    return failCount;
}

int8_t test_sciclient(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;
    uint32_t testCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    uint32_t tempMaxSize = gSciclientSecProxyCfg.pSecProxyRegs->CONFIG;

    retVal = Sciclient_getCurrentContext(0x1000U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x000AU);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x000BU);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x000DU);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x0301U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x9031U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x9023U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x902CU);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getCurrentContext(0x902DU);
    if(retVal == SystemP_SUCCESS)
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

    testCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    retVal = Sciclient_init(testCoreId);
    if(retVal != SystemP_SUCCESS)
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

    reqParam1.timeout = 1;
    retVal = Sciclient_service(&reqParam1, &respParam1);
    if(retVal == SystemP_SUCCESS)
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
    testCoreId = CSL_CORE_ID_A53SS0_0;
    retVal = Sciclient_init(testCoreId);
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
    testCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    retVal = Sciclient_init(testCoreId);
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
    testCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    retVal = Sciclient_init(testCoreId);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_abiCheck();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getVersionCheck(1U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getVersionCheck(0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDMVersion(1U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDMVersion(0);
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

    retVal = Sciclient_abiCheck();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_deinit();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    testCoreId = CSL_CORE_ID_MCU_R5FSS0_0;
    retVal = Sciclient_init(testCoreId);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(NULL, NULL);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&reqParam1, NULL);
    if(retVal == SystemP_SUCCESS)
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

    retVal = Sciclient_init(CSL_CORE_ID_1);
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

    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    struct tisci_get_trace_config_req request3;
    Sciclient_ReqPrm_t reqParam3 = {
        .messageType    = (uint16_t) TISCI_MSG_BOOT_NOTIFICATION,
        .flags          = (uint32_t) TISCI_MSG_FLAG_AOP,
        .pReqPayload    = (const uint8_t *) &request3,
        .reqPayloadSize = (uint32_t) sizeof (request3),
        .timeout        = (uint32_t) (0xFFFFFFFFU),
    };

    struct tisci_get_trace_config_resp response3;
    Sciclient_RespPrm_t respParam3 = {
        .flags           = (uint32_t) 0,
        .pRespPayload    = (uint8_t *) &response3,
        .respPayloadSize = (uint32_t) sizeof (response3),
    };

    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    request3.hdr.flags = 0;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    respParam3.pRespPayload = NULL;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
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

    retVal = Sciclient_init(CSL_CORE_ID_1);
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

    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&reqParam4, &respParam4);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    request4.hdr.flags = 0;
    retVal = Sciclient_service(&reqParam4, &respParam4);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    gSciclientSecProxyCfg.proxyTargetAddr = (uint64_t)0x0UL;
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_init(CSL_CORE_ID_1);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&reqParam4, &respParam4);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    gSciclientSecProxyCfg.proxyTargetAddr = (uint64_t)(CSL_DMASS0_SEC_PROXY_SRC_TARGET_DATA_BASE);
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    reqParam4.pReqPayload = NULL;
    retVal = Sciclient_service(&reqParam4, &respParam4);
    if(retVal == SystemP_SUCCESS)
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

    retVal = Sciclient_init(0xFFFF);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_init(0x15);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_init(CSL_CORE_ID_INVALID);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_abiCheck();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getVersionCheck(0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getVersionCheck(1);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDMVersion(1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_getDMVersion(0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Deinit when not initialized - should fail */
    retVal = Sciclient_deinit();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    reqParam3.timeout = 1;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    reqParam3.timeout = (uint32_t) (0xFFFFFFFFU);

    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    reqParam3.reqPayloadSize = 0;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    reqParam3.reqPayloadSize = (uint32_t) sizeof (request3);

    for(int repeat = 0; repeat<50; repeat++)
    {
        retVal = Sciclient_service(&reqParam3, &respParam3);
        if(retVal == SystemP_SUCCESS)
        {
            DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
            failCount++;
        }
        retVal = Sciclient_abiCheck();
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
            failCount++;
        }
    }

    gSciclientSecProxyCfg.maxMsgSize = 1;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientSecProxyCfg.maxMsgSize = 0;

    gSciclientSecProxyCfg.proxyTargetAddr = (uint64_t)0x100000UL;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientSecProxyCfg.proxyTargetAddr = (uint64_t)(CSL_DMASS0_SEC_PROXY_SRC_TARGET_DATA_BASE);

    reqParam3.pReqPayload = 0;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    reqParam3.pReqPayload = (const uint8_t *) &request3;

    tempMaxSize = gSciclientSecProxyCfg.pSecProxyRegs->CONFIG;
    CSL_REG32_FINS(gSciclientSecProxyCfg.pSecProxyRegs->CONFIG, SEC_PROXY_CONFIG_MSG_SIZE, 9);
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_init(CSL_CORE_ID_1);
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

    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    reqParam3.reqPayloadSize = 4;
    CSL_REG32_FINS(gSciclientSecProxyCfg.pSecProxyRegs->CONFIG, SEC_PROXY_CONFIG_MSG_SIZE, 69);
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    CSL_REG32_FINS(gSciclientSecProxyCfg.pSecProxyRegs->CONFIG, SEC_PROXY_CONFIG_MSG_SIZE, tempMaxSize);
    respParam3.respPayloadSize = 4;
    CSL_REG32_FINS(gSciclientSecProxyCfg.pSecProxyRegs->CONFIG, SEC_PROXY_CONFIG_MSG_SIZE, 69);
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    CSL_REG32_FINS(gSciclientSecProxyCfg.pSecProxyRegs->CONFIG, SEC_PROXY_CONFIG_MSG_SIZE, tempMaxSize);

    /* Simulating case where reqPayloadSize is very large
     * to trigger payload size exceeding max message size check.
     */
    uint32_t savedReqPayloadSize = reqParam3.reqPayloadSize;
    reqParam3.reqPayloadSize = 0xFFFFU;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    reqParam3.reqPayloadSize = savedReqPayloadSize;

    /* Simulating case where reqPayloadSize equals sizeof(struct tisci_header)
     * to test boundary condition where txPayloadSize becomes 0.
     */
    reqParam3.reqPayloadSize = sizeof(struct tisci_header);
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    reqParam3.reqPayloadSize = savedReqPayloadSize;

    /* Simulating case where pReqPayload is NULL but reqPayloadSize > 0
     * to trigger NULL payload with non-zero size check.
     */
    const uint8_t *savedReqPayload = reqParam3.pReqPayload;
    reqParam3.pReqPayload = NULL;
    reqParam3.reqPayloadSize = 100U;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    reqParam3.pReqPayload = savedReqPayload;
    reqParam3.reqPayloadSize = savedReqPayloadSize;

    /* Simulating case where timeout is 0
     * to trigger immediate timeout path in secProxyWaitThread.
     */
    uint32_t savedTimeout = reqParam3.timeout;
    reqParam3.timeout = 0U;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    reqParam3.timeout = savedTimeout;

    /* Simulating case where pSecProxyRtRegs is corrupted (NULL)
     * to trigger thread error verification path.
     */
    CSL_sec_proxy_rtRegs *savedRtRegs = gSciclientSecProxyCfg.pSecProxyRtRegs;
    gSciclientSecProxyCfg.pSecProxyRtRegs = (CSL_sec_proxy_rtRegs *)0x0U;
    retVal = Sciclient_service(&reqParam3, &respParam3);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }
    gSciclientSecProxyCfg.pSecProxyRtRegs = savedRtRegs;

    return failCount;
}

int8_t test_sciclient_message_passing(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    // Deinit in case sciclient is already initialized from a previous test
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Initializing Sciclient with MCU R5 Core ID
    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are forwarded to TIFS and with AOP flag set.
    retVal = Sciclient_service(&reqParamGetTraceAOP, &respParamGetTraceAOP);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are forwarded to TIFS and with 0 flag set.
    retVal = Sciclient_service(&reqParamGetTrace0, &respParamGetTrace0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are processed by DM alone and with AOP flag set.
    retVal = Sciclient_service(&reqParamGetFreqAOP, &respParamGetFreqAOP);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are processed by DM alone and with 0 flag set.
    retVal = Sciclient_service(&reqParamGetFreq0, &respParamGetFreq0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are processed by TIFS alone and with AOP flag set.
    retVal = Sciclient_service(&reqParamReadSWRevAOP, &respParamReadSWRevAOP);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are processed by TIFS alone and with 0 flag set.
    retVal = Sciclient_service(&reqParamReadSWRev0, &respParamReadSWRev0);
    if(retVal != SystemP_SUCCESS)
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
    struct tisci_msg_fwl_change_owner_info_resp fwCngOwnerInfoResp;

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

    retVal = Sciclient_firewallGetRegion(&fwGetReq2, &fwGetResp2, (-1));
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

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
    uint32_t reqFlag     = TISCI_MSG_FLAG_AOP;
    uint32_t moduleId    = TISCI_DEV_TIMER0;
    uint32_t deviceState = TISCI_MSG_FLAG_DEVICE_WAKE_ENABLED;
    uint32_t moduleId1   = TISCI_DEV_DSS0;
    uint32_t modfreq_hz = 100000;
    uint32_t mod_depth = 10;
    uint8_t spread_type = 3;
    uint8_t enable = 1;
    uint32_t respModfreq_hz;
    uint32_t respMod_depth;
    uint8_t respSpread_type;
    uint8_t respEnable;

    retVal = Sciclient_pmSetModuleState(moduleId, deviceState, reqFlag, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleState(moduleId, &moduleState, &resetState, &contextLossState, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleRst(moduleId, 1U, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleRst_flags(moduleId, 1U, reqFlag, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmModuleClkRequest(moduleId, TISCI_DEV_DSS0_DPI_0_IN_CLK, 0, 0, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmModuleGetClkStatus(moduleId, TISCI_DEV_DSS0_DPI_1_OUT_CLK, &state, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkParent(moduleId, TISCI_DEV_DSS0_DPI_1_IN_CLK, TISCI_DEV_DSS0_DPI_1_IN_CLK_PARENT_HSDIV0_16FFT_MAIN_17_HSDIVOUT0_CLK, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkParent(moduleId, TISCI_DEV_DSS0_DPI_1_IN_CLK, &parent, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkNumParent(moduleId, TISCI_DEV_DSS0_DPI_1_IN_CLK, &numParent, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkFreq(moduleId, TISCI_DEV_DSS0_DPI_0_IN_CLK, 10000000U, 0, 0xFFFFFFFFU);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmQueryModuleClkFreq(moduleId, TISCI_DEV_DSS0_DPI_0_IN_CLK, 10000000U, &respFreqHz, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkFreq(moduleId, TISCI_DEV_DSS0_DPI_0_IN_CLK, &freqHz, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleState(moduleId, deviceState, 0, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleState(moduleId, deviceState, 3, 0xFFFFFFFFU);
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

    retVal = Sciclient_pmSetModuleRst_flags(0x0, 0x0, reqFlag, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleRst_flags(0xFF, 0x0, reqFlag, 0x0);
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

    retVal = Sciclient_pmSetModuleRst_flags(moduleId, 1U, 0, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkSSC(moduleId1, TISCI_DEV_DSS0_DPI_1_IN_CLK, modfreq_hz, mod_depth, spread_type, enable, reqFlag, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkSSC(moduleId1, TISCI_DEV_DSS0_DPI_1_IN_CLK, &respModfreq_hz, &respMod_depth, &respSpread_type, &respEnable, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmSetModuleClkSSC(moduleId1, TISCI_DEV_DSS0_DPI_1_IN_CLK, 0, 0, 0, 0, reqFlag, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkSSC(moduleId1, TISCI_DEV_DSS0_DPI_1_IN_CLK, &respModfreq_hz, &respMod_depth, &respSpread_type, &respEnable, SystemP_WAIT_FOREVER);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Negative tests for SSC - invalid moduleId */
    retVal = Sciclient_pmSetModuleClkSSC(0xFF, TISCI_DEV_DSS0_DPI_1_IN_CLK, modfreq_hz, mod_depth, spread_type, enable, reqFlag, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkSSC(0xFF, TISCI_DEV_DSS0_DPI_1_IN_CLK, &respModfreq_hz, &respMod_depth, &respSpread_type, &respEnable, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Negative tests for SSC - invalid clockId */
    retVal = Sciclient_pmSetModuleClkSSC(moduleId1, 256U, modfreq_hz, mod_depth, spread_type, enable, reqFlag, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkSSC(moduleId1, 256U, &respModfreq_hz, &respMod_depth, &respSpread_type, &respEnable, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Negative tests for SSC - invalid spread_type (valid values are 1 or 3) */
    retVal = Sciclient_pmSetModuleClkSSC(moduleId1, TISCI_DEV_DSS0_DPI_1_IN_CLK, modfreq_hz, mod_depth, 0x5, enable, reqFlag, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Negative tests for SSC - invalid timeout (0 timeout) */
    retVal = Sciclient_pmSetModuleClkSSC(moduleId1, TISCI_DEV_DSS0_DPI_1_IN_CLK, modfreq_hz, mod_depth, spread_type, enable, reqFlag, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkSSC(moduleId1, TISCI_DEV_DSS0_DPI_1_IN_CLK, &respModfreq_hz, &respMod_depth, &respSpread_type, &respEnable, 0x0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Negative test for SSC - valid device/clock that doesn't support SSC (UART peripheral clock) */
    retVal = Sciclient_pmSetModuleClkSSC(TISCI_DEV_UART0, TISCI_DEV_UART0_FCLK_CLK, modfreq_hz, mod_depth, spread_type, enable, reqFlag, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_pmGetModuleClkSSC(TISCI_DEV_UART0, TISCI_DEV_UART0_FCLK_CLK, &respModfreq_hz, &respMod_depth, &respSpread_type, &respEnable, SystemP_WAIT_FOREVER);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_lpm(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    uint8_t moduleState;
    uint8_t hostState;
    uint8_t sysMode;
    uint32_t constraintState = 1U;
    uint32_t  moduleId = 186;
    uint16_t resumeLatency = 0;
    uint16_t sysLatency;
    uint32_t wake_source;
    uint64_t wake_timestamp;
    uint8_t wake_pin;
    uint8_t mode;

    retVal = Sciclient_lpmSetModuleConstraint(moduleId, constraintState, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmSetModuleConstraint(0xFF, constraintState, 0xFFFFFFFFU);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmSetModuleConstraint(moduleId, constraintState, 0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetModuleConstraint(moduleId, &moduleState, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetModuleConstraint(0xFF, &moduleState, 0xFFFFFFFFU);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetModuleConstraint(moduleId, &moduleState, 0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmSetLatencyConstraint(resumeLatency, constraintState, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmSetLatencyConstraint(resumeLatency, constraintState, 0x0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetLatencyConstraint(&sysLatency, &moduleState, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetLatencyConstraint(&sysLatency, &moduleState, 0);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetNextSysMode(0xFFFFFFFFU, &sysMode);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetNextSysMode(0, &sysMode);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetNextHostState(0xFFFFFFFFU, &hostState);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetNextHostState(0, &hostState);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetWakeReason(&wake_source, &wake_timestamp, &wake_pin, &mode, 0xFFFFFFFFU);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmGetWakeReason(&wake_source, &wake_timestamp, &wake_pin, &mode, 0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmSendPrepareSleepMessage(mode, 0U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    retVal = Sciclient_lpmSendPrepareSleepMessage(0, 0xFFFFFFFFU);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    return failCount;
}

int8_t test_sciclient_modes(void)
{
    int32_t retVal = SystemP_SUCCESS;
    int8_t failCount = 0;

    /* Deinitialize existing Sciclient if already initialised before for clean run. */
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test updateOperModeToInterrupt when sciclient is not initialized.
     * This should fail since sciclient is not initialized.
     */
    retVal = Sciclient_updateOperModeToInterrupt();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test updateOperModeToPolled when sciclient is not initialized. */
    Sciclient_updateOperModeToPolled();

    /* Test getVersionCheck when sciclient is not initialized - should fail. */
    retVal = Sciclient_getVersionCheck(1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test getDMVersion when sciclient is not initialized - should fail. */
    retVal = Sciclient_getDMVersion(1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test abiCheck when sciclient is not initialized - should fail. */
    retVal = Sciclient_abiCheck();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test getCurrentContext when sciclient is not initialized. */
    retVal = Sciclient_getCurrentContext(TISCI_MSG_VERSION);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Initialize Sciclient */
    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test triggerSecHandover - exercises security handover code path.
     * May succeed or fail depending on device type/state, don't fail on result.
     */
    retVal = Sciclient_triggerSecHandover();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test getVersionCheck when initialized - should succeed. */
    retVal = Sciclient_getVersionCheck(1U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test getVersionCheck with doLog=0 */
    retVal = Sciclient_getVersionCheck(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test getDMVersion when initialized - should succeed. */
    retVal = Sciclient_getDMVersion(1U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test getDMVersion with doLog=0 */
    retVal = Sciclient_getDMVersion(0U);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test abiCheck when initialized - should succeed. */
    retVal = Sciclient_abiCheck();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test updating operation mode to Interrupt. */
    retVal = Sciclient_updateOperModeToInterrupt();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test updateOperModeToInterrupt when already in interrupt mode. */
    retVal = Sciclient_updateOperModeToInterrupt();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test disableIntr when in interrupt mode with valid handlers. */
    Sciclient_disableIntr();

    /* Test enableIntr to re-enable interrupts. */
    Sciclient_enableIntr();

    /* Test Sciclient_updateOperModeToPolled when in interrupt mode. */
    Sciclient_updateOperModeToPolled();

    /* Switch back to interrupt mode for subsequent interrupt mode tests. */
    retVal = Sciclient_updateOperModeToInterrupt();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test sciclient message types in interrupt mode. */
    // Calling Sciclient Service for messages which are forwarded to TIFS and with AOP flag set.
    retVal = Sciclient_service(&reqParamGetTraceAOP, &respParamGetTraceAOP);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are forwarded to TIFS and with 0 flag set.
    retVal = Sciclient_service(&reqParamGetTrace0, &respParamGetTrace0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are processed by DM alone and with AOP flag set.
    retVal = Sciclient_service(&reqParamGetFreqAOP, &respParamGetFreqAOP);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are processed by DM alone and with 0 flag set.
    retVal = Sciclient_service(&reqParamGetFreq0, &respParamGetFreq0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are processed by TIFS alone and with AOP flag set.
    retVal = Sciclient_service(&reqParamReadSWRevAOP, &respParamReadSWRevAOP);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    // Calling Sciclient Service for messages which are processed by TIFS alone and with 0 flag set.
    retVal = Sciclient_service(&reqParamReadSWRev0, &respParamReadSWRev0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test updateOperModeToInterrupt when already in interrupt mode.
     * All interrupts should already be setup.
     */
    retVal = Sciclient_updateOperModeToInterrupt();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test deinit while in interrupt mode to trigger interrupt unregister path. */
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test deinit when already deinitialized. */
    retVal = Sciclient_deinit();
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Re-initialize sciclient. */
    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test Sciclient_updateOperModeToPolled when already in polled mode. */
    Sciclient_updateOperModeToPolled();

    /* Test Sciclient_disableIntr when in polled mode. */
    Sciclient_disableIntr();

    /* Test Sciclient_enableIntr when in polled mode. */
    Sciclient_enableIntr();

    /* Test deinit again. */
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Re-initialize sciclient. */
    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test init when already initialized */
    retVal = Sciclient_init(CSL_CORE_ID_MCU_R5FSS0_0);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test init with invalid coreId (>= CSL_CORE_ID_MAX) when already initialized. */
    retVal = Sciclient_init(CSL_CORE_ID_MAX);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test deinit again. */
    retVal = Sciclient_deinit();
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test Sciclient_init with invalid coreId when sciclient is NOT initialized. */
    retVal = Sciclient_init(CSL_CORE_ID_MAX);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test with another invalid coreId value (CSL_CORE_ID_MAX + 1) */
    retVal = Sciclient_init(CSL_CORE_ID_MAX + 1U);
    if(retVal == SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test Sciclient_updateOperModeToPolled when not initialized. */
    Sciclient_updateOperModeToPolled();

    /* Test Sciclient_disableIntr when not initialized. */
    Sciclient_disableIntr();

    /* Test Sciclient_enableIntr when not initialized. */
    Sciclient_enableIntr();

    /* Re-initialize sciclient with CSL_CORE_ID_1 for RM tests in polled mode.
     * Polling mode can run with any core ID, so we use CSL_CORE_ID_1 here
     * to test the RM code paths that require this core ID configuration.
     */
    retVal = Sciclient_init(CSL_CORE_ID_1);
    if(retVal != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Testcase failed in %d and retVal is %d", __LINE__, retVal);
        failCount++;
    }

    /* Test Sciclient_updateOperModeToPolled when already in polled mode.
     * This covers line 477 FALSE branch.
     */
    Sciclient_updateOperModeToPolled();

    /* Test Sciclient_disableIntr when in polled mode.
     * This covers line 488 FALSE branch.
     */
    Sciclient_disableIntr();

    /* Test Sciclient_enableIntr when in polled mode.
     * This covers line 513 FALSE branch.
     */
    Sciclient_enableIntr();

    return failCount;
}

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

#include "test_sciclient.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Function Declarations                               */
/* ========================================================================== */

void sciclient_testMessageType(void *args);
void test_sciclient_coverage(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    sciclient_testMessageType(NULL);
    test_sciclient_coverage(NULL);

    #if defined LDRA_DYN_COVERAGE_EXIT
        DebugP_log("\n LDRA ENTRY... \n");
        upload_execution_history();
        DebugP_log("\n LDRA EXIT... \n");
    #endif

    return;
}

/* Callback function definition */
void localFpMemAccess( uintptr_t addr, uint8_t *pData, uint32_t elemSizeBytes, uint32_t elemCnt )
{
    DebugP_log("\r\n Callback function of CSL_secProxyAccessTarget is called \r\n");
}

/* Testcases */

void test_sciclient_coverage(void *args)
{
    int8_t failCount = 0;
    uint32_t sumFailure = 0;

    failCount = test_sciclient();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient: All testcase passed successfully \r\n");
    }

	failCount = test_sciclient_procboot();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_procboot: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_procboot: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_rm();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_rm: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_rm: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_firewall();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_firewall: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_firewall: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_pm();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_pm: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_pm: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_rm_irq();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_rm_irq: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_rm_irq: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_soc_priv();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_soc_priv: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_soc_priv: All testcase passed successfully \r\n");
    }

    failCount = test_csl_sec_proxy();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_csl_sec_proxy: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_csl_sec_proxy: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_lpm();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_lpm: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_lpm: All testcase passed successfully \r\n");
    }

   if(sumFailure > 0)
    {
        DebugP_log("\r\n\r\n Overall test status: %d testcase failed \r\n", sumFailure);
    }
    else
    {
        DebugP_log("\r\n\r\n Overall test status: All testcases are passed successfully \r\n");
    }
}

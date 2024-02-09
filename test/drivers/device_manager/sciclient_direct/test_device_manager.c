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
/*                        Function Declarations                               */
/* ========================================================================== */

static void test_dm_full_test(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    test_sciclient_version(NULL);
    test_sciclient_rm_ir_output(NULL);
    ClockP_sleep(3);
    test_dm_full_test(NULL);

#if defined LDRA_DYN_COVERAGE_EXIT
    DebugP_log ( "\n LDRA Output IN display... \n" ) ;
    DebugP_log("\n LDRA ENTRY... \n");
    upload_execution_history();
    DebugP_log("\n LDRA EXIT... \n");
#endif

    return;
}

/* Testcases */

static void test_dm_full_test(void *args)
{
    int8_t failCount = 0;
    uint32_t sumFailure = 0;

    failCount = test_sciserver();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciserver: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciserver: All testcase passed successfully \r\n");
    }

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

    failCount = test_sciclient_secproxyRoutingDescription();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_secproxyRoutingDescription: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_secproxyRoutingDescription: All testcase passed successfully \r\n");
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

    failCount = test_sciclient_dkek();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_dkek: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_dkek: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_boardcfg();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_boardcfg: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_boardcfg: All testcase passed successfully \r\n");
    }


    failCount = test_sciclient_directWrapper();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_directWrapper: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_directWrapper: All testcase passed successfully \r\n");
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

    failCount = test_sciclient_serviceSecProxy();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_serviceSecProxy: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_serviceSecProxy: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_direct();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_direct: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_direct: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_secureproxy();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_secureproxy: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_secureproxy: All testcase passed successfully \r\n");
    }

    failCount = test_sciserver_secproxyTransfer();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciserver_secproxyTransfer: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciserver_secproxyTransfer: All testcase passed successfully \r\n");
    }

    failCount = test_sciserver_init();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciserver_init: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciserver_init: All testcase passed successfully \r\n");
    }

    failCount = test_sciserver_tirtos();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciserver_tirtos: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciserver_tirtos: All testcase passed successfully \r\n");
    }

    failCount =  test_sciclient_lowPowerReq();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_lowPowerReq: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_lowPowerReq: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_boardcfgRM();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_boardcfgRM: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_boardcfgRM: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_boardCfgParseHdr();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_boardCfgParseHdr: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_boardCfgParseHdr: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_boardCfgPrepHdr();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_boardCfgPrepHdr: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_boardCfgPrepHdr: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_processPmMessage();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_processPmMessage: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_processPmMessage: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_queryFwCaps();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_queryFwCaps: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_queryFwCaps: All testcase passed successfully \r\n");
    }

    failCount = test_sciclient_setdevice();
    if(failCount > 0)
    {
        DebugP_log("\r\n test_sciclient_setdevice: %d testcase failed \r\n", failCount);
        sumFailure += (uint32_t)failCount;
    }
    else
    {
        DebugP_log("\r\n test_sciclient_setdevice: All testcase passed successfully \r\n");
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

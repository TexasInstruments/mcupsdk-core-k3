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

#include <stdio.h>
#include <kernel/dpl/DebugP.h>
#if defined ENABLE_SCICLIENT_DIRECT
/* DM R5 will use the SCI Client direct */
#include <drivers/device_manager/sciclient.h>
#else
#include <drivers/sciclient.h>
#endif
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "debug_unlock_cert_hex.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Structure Declarations                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* X509 Certificate to do run time JTAG debug port unlock */
const unsigned char gDebugUnlockCert[] = DEBUG_UNLOCK_X509_CERT;

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void runtime_debug_unlock_main(void *args)
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("Runtime debug unlock example!\r\n");

    Sciclient_ReqPrm_t reqParam;
    Sciclient_RespPrm_t respParam;
    struct tisci_msg_open_debug_fwls_req request =
    {
        .debug_cert_addr = (uint64_t) &gDebugUnlockCert[0],
    };
    struct tisci_msg_open_debug_fwls_resp response;

    /* Request to unlock JTAG during runtime */
    reqParam.messageType      = (uint16_t) TISCI_MSG_OPEN_DEBUG_FWLS;
    reqParam.flags            = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload      = (const uint8_t *) &request;
    reqParam.reqPayloadSize   = (uint32_t) sizeof(request);
    reqParam.timeout          = (uint32_t) SystemP_WAIT_FOREVER;

    respParam.flags           = (uint32_t) 0;   /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t) sizeof(response);

    status = Sciclient_service(&reqParam, &respParam);

	if ( (status == SystemP_SUCCESS) && ((respParam.flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK) )
	{
		DebugP_log("Run time JTAG debug unlock... DONE !!! \r\n");
	}
	else
	{
		DebugP_logError("Run time JTAG debug unlock.. Failed !!!\r\n");
		status = SystemP_FAILURE;
	}

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_logError ("Some tests have failed\r\n");
    }

    return;
}

/*
 * Copyright (c) 2018-2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 *  \file sciclient_genericMsgs.c
 *
 *  \brief File containing the SCICLIENT API interfaces to generic DMSC Services
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/device_manager/sciclient.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t Sciclient_msmcQuery(const struct tisci_query_msmc_req *req,
                            struct tisci_query_msmc_resp *resp,
                            uint32_t timeout)
{
    int32_t r;
    Sciclient_ReqPrm_t sciReq = {0};
    sciReq.messageType    = TISCI_MSG_QUERY_MSMC;
    sciReq.flags          = TISCI_MSG_FLAG_AOP;
    sciReq.pReqPayload    = (const uint8_t *) req;
    sciReq.reqPayloadSize = (uint32_t) sizeof (struct tisci_query_msmc_req);
    sciReq.timeout        = timeout;

    Sciclient_RespPrm_t sciResp = {0};
    sciResp.flags           = 0;
    sciResp.pRespPayload    = (uint8_t *)resp;
    sciResp.respPayloadSize = (uint32_t) sizeof(*resp);

    r = Sciclient_service(&sciReq, &sciResp);
    if ((r != CSL_PASS) ||
        ((sciResp.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK)) {
        r = CSL_EFAIL;
    }

    return r;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

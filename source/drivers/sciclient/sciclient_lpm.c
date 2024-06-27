/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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
 *  \file sciclient_lpm.c
 *
 *  \brief File containing the SCICLIENT API interfaces to the Low Power Mode
 *         SYSFW services.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <drivers/sciclient.h>
#include <kernel/dpl/SystemP.h>

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

int32_t Sciclient_lpmGetNextSysMode(uint32_t timeout,
                                    uint8_t *sysMode)
{
    int32_t retVal = SystemP_SUCCESS;
    Sciclient_ReqPrm_t reqParam = {0};
    Sciclient_RespPrm_t respParam = {0};
    struct tisci_msg_lpm_get_next_sys_mode_req request;
    struct tisci_msg_lpm_get_next_sys_mode_resp response;

    reqParam.messageType      = TISCI_MSG_LPM_GET_NEXT_SYS_MODE;
    reqParam.flags            = TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload      = (const uint8_t *) &request;
    reqParam.reqPayloadSize   = (uint32_t) sizeof(request);
    reqParam.timeout          = timeout;

    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t) sizeof(response);

    retVal = Sciclient_service(&reqParam, &respParam);
    if (retVal == SystemP_SUCCESS)
    {
        if ((respParam.flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK)
        {
            *sysMode = response.mode;
        }
        else
        {
            retVal = SystemP_FAILURE;
        }
    }

    return retVal;
}

int32_t Sciclient_lpmGetNextHostState(uint32_t timeout,
                                      uint8_t *hostState)
{
    int32_t retVal = SystemP_SUCCESS;
    Sciclient_ReqPrm_t reqParam = {0};
    Sciclient_RespPrm_t respParam = {0};
    struct tisci_msg_lpm_get_next_host_state_req request;
    struct tisci_msg_lpm_get_next_host_state_resp response;

    reqParam.messageType      = TISCI_MSG_LPM_GET_NEXT_HOST_STATE;
    reqParam.flags            = TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload      = (const uint8_t *) &request;
    reqParam.reqPayloadSize   = (uint32_t) sizeof(request);
    reqParam.timeout          = timeout;

    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t) sizeof(response);

    retVal = Sciclient_service(&reqParam, &respParam);
    if (retVal == SystemP_SUCCESS)
    {
        if ((respParam.flags & TISCI_MSG_FLAG_ACK) == TISCI_MSG_FLAG_ACK)
        {
            *hostState = response.state;
        }
        else
        {
            retVal = SystemP_FAILURE;
        }
    }

    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */



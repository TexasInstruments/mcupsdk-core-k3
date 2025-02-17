/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS int32_tERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file scmi_power_domain.c
 *
 *  \brief File containing SCMI power domain protocol APIs implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ==================================================== ====================== */

#include <stdlib.h>
#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/scp/scmi/v0/scmi_protocol.h>
#include <drivers/scp/scmi/v0/scmi.h>
#include <drivers/scp/scmi/v0/scmi_base.h>
#include <drivers/scp/scmi/v0/scmi_power_domain.h>
#include <drivers/scp/scmi/v0/transport/scmi_transport.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t SCMI_powerDomainGetProtocolAttrs(SCMI_Handle handle,
                                         uint32_t *numPowerDomains,
                                         uint64_t *statsAddr,
                                         uint32_t *statsLen)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_PdProtocolAttrs outData;
    SCMI_MessageData message;

    if((handle != NULL) && (numPowerDomains != NULL) && (statsAddr != NULL) &&
       (statsLen != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_POWER;
        message.header.id = SCMI_PROTOCOL_ATTRIBUTES;
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {

            *numPowerDomains = SCMI_PWD_PROTO_ATTRS_NUM_PWD(outData.attributes);
            *statsAddr = ((uint64_t)outData.statsAddrHigh << 32) | \
                         (uint64_t)outData.statsAddrLow;
            *statsLen = outData.statsLen;
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_powerDomainGetAttrs(SCMI_Handle handle, uint32_t domainId,
                                 uint32_t *attributes, uint8_t *name)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_PowerDomainAttrsOutData outData;
    SCMI_MessageData message;
    uint32_t pdId = domainId;

    if((handle != NULL) && (attributes != NULL) && (name != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_POWER;
        message.header.id = SCMI_PWD_ATTRIBUTES;
        message.inputMessage = (uint8_t *)&pdId;
        message.inputMessageSize = sizeof(pdId);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {

            *attributes = outData.attributes;
            memcpy((void*)name, outData.name, SCMI_PWD_SHORT_NAME_SIZE);
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_powerDomainStateSet(SCMI_Handle handle, uint32_t domainId,
                                uint32_t flags, uint32_t pstate)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_PowerDomainStateSetInput inData;
    int32_t outStatus;
    SCMI_MessageData message;

    if(handle != NULL)
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_POWER;
        message.header.id = SCMI_PWD_STATE_SET;
        message.inputMessage = (uint8_t *)&inData;
        message.inputMessageSize = sizeof(inData);
        message.outputMessage = (uint8_t *)&outStatus;
        message.outputMessageSize = sizeof(outStatus);

        inData.domainId = domainId;
        inData.flags = flags;
        inData.pstate = pstate;

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outStatus);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_powerDomainStateGet(SCMI_Handle handle, uint32_t domainId,
                                uint32_t *pstate)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_PowerDomainStateGetOut outData;
    SCMI_MessageData message;
    uint32_t pdId = domainId;

    if((handle != NULL) && (pstate != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_POWER;
        message.header.id = SCMI_PWD_STATE_GET;
        message.inputMessage = (uint8_t *)&pdId;
        message.inputMessageSize = sizeof(pdId);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            *pstate = outData.pstate;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_powerDomainNameGet(SCMI_Handle handle, uint32_t domainId,
                                uint8_t *name)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_PowerDomainNameGetOut outData;
    SCMI_MessageData message;
    uint32_t pdId = domainId;

    if((handle != NULL) && (name != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_POWER;
        message.header.id = SCMI_PWD_NAME_GET;
        message.inputMessage = (uint8_t *)&pdId;
        message.inputMessageSize = sizeof(pdId);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            memcpy((void*)name, &outData.extendedName, SCMI_PWD_NAME_LENGTH_MAX);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_powerDomainProtocolInit(SCMI_Handle handle)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_Config *config = (SCMI_Config *)handle;
    SCMI_PowerDomainProtocol *protocol = &config->powerDomainProto;

    if(handle != NULL)
    {
        status = SCMI_baseGenericProtocolVersion(handle, SCMI_PROTOCOL_POWER,
                                                 &protocol->version);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("SCMI: Power Domain: Get protocol version failed.\r\n");
        }

        status += SCMI_powerDomainGetProtocolAttrs(handle,
                                                   &protocol->numPowerDomains,
                                                   &protocol->statsAddr,
                                                   &protocol->statsLen);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}
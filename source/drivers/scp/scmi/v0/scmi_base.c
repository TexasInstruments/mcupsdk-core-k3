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
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file scmi_base.c
 *
 *  \brief File containing scmi base protocol APIs implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ==================================================== ====================== */

#include <stdlib.h>
#include <string.h>
#include <drivers/scp/scmi/v0/scmi_protocol.h>
#include <drivers/scp/scmi/v0/scmi.h>
#include <drivers/scp/scmi/v0/transport/scmi_transport.h>
#include <drivers/scp/scmi/v0/scmi_base.h>

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

int32_t SCMI_baseGenericProtocolVersion(SCMI_Handle handle,
                                        SCMI_StandardProtocol protocolId,
                                        uint32_t *version)
{
	int32_t status = SystemP_SUCCESS;
    SCMI_ProtocolVersionData outData;
    SCMI_MessageData message;

    if((handle != NULL) && (version != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = (uint8_t)protocolId;
        message.header.id = SCMI_PROTOCOL_VERSION;
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            *version = outData.version;
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

	return status;
}

int32_t SCMI_getBaseProtocolVersion(SCMI_Handle handle, uint32_t *version)
{
	return SCMI_baseGenericProtocolVersion(handle, SCMI_PROTOCOL_BASE,
					     version);
}

int32_t SCMI_baseGetProtocolAttributes(SCMI_Handle handle, uint32_t *numAgents,
                                       uint32_t *numProtocols)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_ProtocolAttributesData outData;
    SCMI_MessageData message;

    if ((handle != NULL) && (numAgents != NULL) && (numProtocols != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_BASE;
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
            *numAgents = SCMI_PROTOCOL_ATTRS_NUM_AGENTS(outData.attributes);
            *numProtocols = SCMI_PROTOCOL_ATTRS_NUM_PROTOCOLS(outData.attributes);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

	return status;
}

int32_t SCMI_baseGetMessageAttributes(SCMI_Handle handle, uint32_t messageId,
                                      uint32_t *attributes)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_ProtocolMessageAttributesData outData;
    SCMI_MessageData message;
    uint32_t msgId = messageId;

    if((handle != NULL) && (attributes != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_BASE;
        message.header.id = SCMI_PROTOCOL_MESSAGE_ATTRIBUTES;
        message.inputMessage = (uint8_t *)&msgId;
        message.inputMessageSize = sizeof(msgId);
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
        }
	}
    else
    {
        status = SystemP_FAILURE;
    }

	return status;
}

int32_t SCMI_baseDiscoverVendor(SCMI_Handle handle, uint8_t *vendor)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_MessageData message;
	SCMI_BaseDiscoverVendorOut outData;

    if((handle != NULL) && (vendor != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_BASE;
        message.header.id = SCMI_BASE_DISCOVER_VENDOR;
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            memcpy((void *)vendor, &outData.vendorIdentifier, SCMI_BASE_NAME_LENGTH_MAX);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

	return status;
}

int32_t SCMI_baseDiscoverSubVendor(SCMI_Handle handle,  uint8_t *subVendor)
{
	int32_t status = SystemP_SUCCESS;
    SCMI_BaseDiscoverVendorOut outData;
    SCMI_MessageData message;

    if((handle != NULL) && (subVendor != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_BASE;
        message.header.id = SCMI_BASE_DISCOVER_SUB_VENDOR;
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            memcpy((void *)subVendor, &outData.vendorIdentifier, SCMI_BASE_NAME_LENGTH_MAX);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_baseDiscoverImplementationVersion(SCMI_Handle handle,
                                               uint32_t *implVersion)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_BaseDiscoverImplementationVersionData outData;
    SCMI_MessageData message;

    if((handle != NULL) && (implVersion != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_BASE;
        message.header.id = SCMI_BASE_DISCOVER_IMPL_VERSION;
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            *implVersion = outData.implVersion;
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

	return status;
}

int32_t SCMI_baseDiscoverListProtocols(SCMI_Handle handle,
                                       uint32_t *protocolCount,
                                       uint8_t *protocols)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_BaseDiscoverListProtocolsData outData;
    SCMI_MessageData message;
    uint32_t numAgents = 0U;
    uint32_t totalProtocols = 0U;
    uint32_t skipProtocols = 0U;
    uint8_t count = 0U;

    if((handle != NULL) && (protocolCount != NULL) && (protocols != NULL))
    {
        status = SCMI_baseGetProtocolAttributes(handle, &numAgents, \
                                                &totalProtocols);

        if((status != SystemP_SUCCESS) || (totalProtocols == 0U))
        {
            status = SystemP_FAILURE;
        }
        else
        {
            SCMI_initSCMIMessageData(&message);

            message.header.protocol_id = SCMI_PROTOCOL_BASE;
            message.header.id = SCMI_BASE_DISCOVER_LIST_PROTOCOLS;
            message.inputMessage = (uint8_t *)&skipProtocols;
            message.inputMessageSize = sizeof(skipProtocols);
            message.outputMessage = (uint8_t *)&outData;
            message.outputMessageSize = sizeof(outData);

            do
            {
                status = SCMITransport_processMessage(handle, &message);
                status += SCMI_getSCMIProtocolErrorMapped(outData.status);

                if (status == SystemP_SUCCESS)
                {
                    for(count = 0U; count < outData.numProtocols; count++)
                    {
                        protocols[skipProtocols] = \
                            (uint8_t)(outData.protocols[count / 4U] >> \
                                    ((count % 4U) * 8U));
                        skipProtocols++;
                    }
                }
                else
                {
                    status = SystemP_FAILURE;
                    break;
                }

            } while (skipProtocols < totalProtocols);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if(protocolCount != NULL)
    {
        *protocolCount = totalProtocols;
    }

	return status;
}





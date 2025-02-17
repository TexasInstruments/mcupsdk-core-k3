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
 *  \file scmi_clock.c
 *
 *  \brief File containing scmi clock protocol APIs implementation.
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
#include <drivers/scp/scmi/v0/transport/scmi_transport.h>
#include <drivers/scp/scmi/v0/scmi_clock.h>

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

int32_t SCMI_clockGetProtocolAttrs(SCMI_Handle handle,
                                   uint32_t *numClocks)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_ClockProtocolAttrsOut outData;
    SCMI_MessageData message;

    if(((handle != NULL)) && (numClocks != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
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

            *numClocks = outData.attributes & SCMI_CLK_PROTO_ATTR_COUNT_MASK;
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_clockGetAttrs(SCMI_Handle handle, uint32_t clockId,
                           uint32_t *attributes, uint8_t *name)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_ClockAttributeOut outData;
    SCMI_MessageData message;
    uint32_t clkId = clockId;

    if((handle != NULL) && (attributes != NULL) && (name != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
        message.header.id = SCMI_CLOCK_ATTRIBUTES;
        message.inputMessage = (uint8_t *)&clkId;
        message.inputMessageSize = sizeof(clkId);
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
            memcpy((void*)name, &outData.clockName, SCMI_CLK_SHORT_NAME_SIZE);
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_clockConfigSet(SCMI_Handle handle, uint32_t clockId,
                            uint32_t clockState)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_ClockStateIn inData;
    int32_t outStatus;
    SCMI_MessageData message;

    if(handle != NULL)
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
        message.header.id = SCMI_CLOCK_CONFIG_SET;
        message.inputMessage = (uint8_t *)&inData;
        message.inputMessageSize = sizeof(inData);
        message.outputMessage = (uint8_t *)&outStatus;
        message.outputMessageSize = sizeof(outStatus);

        inData.clockId = clockId;
        inData.attributes = clockState;

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

int32_t SCMI_clockConfigGet(SCMI_Handle handle, uint32_t clockId,
                            uint32_t *clockState)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_ClockStateGetIn inData;
	SCMI_ClockStateGetOut outData;
    SCMI_MessageData message;

    if((handle != NULL) && (clockState != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
        message.header.id = SCMI_CLOCK_CONFIG_GET;
        message.inputMessage = (uint8_t *)&inData;
        message.inputMessageSize = sizeof(inData);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        inData.clockId = clockId;

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            *clockState = outData.config & SCMI_CLK_CONFIG_SET_ENABLE;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_clockNameGet(SCMI_Handle handle, uint32_t clockId,
                          uint8_t *name)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_ClockNameGetOut outData;
    SCMI_MessageData message;
    uint32_t clkId = clockId;

    if((handle != NULL) && (name != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
        message.header.id = SCMI_CLOCK_NAME_GET;
        message.inputMessage = (uint8_t *)&clkId;
        message.inputMessageSize = sizeof(clkId);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            memcpy((void*)name, &outData.clockName, SCMI_CLK_NAME_LENGTH_MAX);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_clockRateGet(SCMI_Handle handle, uint32_t clockId,
                          uint64_t *clockRate)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_ClockRateGetOut outData;
    SCMI_MessageData message;
    uint32_t clkId = clockId;

    if((handle != NULL) && (clockRate != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
        message.header.id = SCMI_CLOCK_RATE_GET;
        message.inputMessage = (uint8_t *)&clkId;
        message.inputMessageSize = sizeof(clkId);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            *clockRate = (uint64_t)outData.clockRateLSB | \
                         (((uint64_t)outData.clockRateMSB) << 32);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_clockRateSet(SCMI_Handle handle, uint32_t clockId,
                          uint64_t clockRate)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_ClockRateSetIn inData;
	int32_t outData;
    SCMI_MessageData message;

    if(handle != NULL)
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
        message.header.id = SCMI_CLOCK_RATE_SET;
        message.inputMessage = (uint8_t *)&inData;
        message.inputMessageSize = sizeof(inData);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);


        inData.clockId = clockId;
        inData.flags = SCMI_CLK_RATE_ROUND_CLOSEST;
        inData.clockRateLSB = (uint32_t)(clockRate & 0xFFFFFFFF);
        inData.clockRateMSB = (uint32_t)(clockRate >> 32);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_clockParentSet(SCMI_Handle handle, uint32_t clockId,
                            uint32_t parentId)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_ClockParentSetIn inData;
	int32_t outData;
    SCMI_MessageData message;

    if(handle != NULL)
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
        message.header.id = SCMI_CLOCK_PARENT_SET;
        message.inputMessage = (uint8_t *)&inData;
        message.inputMessageSize = sizeof(inData);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        inData.clockId = clockId;
        inData.parentId = parentId;

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_clockParentGet(SCMI_Handle handle, uint32_t clockId,
                            uint32_t *parentId)
{
    int32_t status = SystemP_SUCCESS;
	SCMI_ClockParentGetOut outData;
    SCMI_MessageData message;
    uint32_t clkId = clockId;

    if((handle != NULL) && (parentId != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
        message.header.id = SCMI_CLOCK_PARENT_GET;
        message.inputMessage = (uint8_t *)&clkId;
        message.inputMessageSize = sizeof(clkId);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            *parentId = outData.parentId;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_clockGetPossibleParents(SCMI_Handle handle, uint32_t clockId,
                                     uint32_t *numPosParents,
                                     uint32_t *possibleParents)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_ClockGetPossibleParentsIn inData;
    SCMI_ClockGetPossibleParentsOut outData;
    SCMI_MessageData message;
    uint32_t numParentsRecv;
    uint32_t numParentsPend;
    uint32_t *iterator = possibleParents;

    if((handle != NULL) && (numPosParents != NULL) && (possibleParents != NULL))
    {
        SCMI_initSCMIMessageData(&message);

        message.header.protocol_id = SCMI_PROTOCOL_CLOCK;
        message.header.id = SCMI_CLOCK_POSSIBLE_PARENTS_GET;
        message.inputMessage = (uint8_t *)&inData;
        message.inputMessageSize = sizeof(inData);
        message.outputMessage = (uint8_t *)&outData;
        message.outputMessageSize = sizeof(outData);

        inData.clockId = clockId;
        inData.skipParents = 0U;

        status = SCMITransport_processMessage(handle, &message);
        if (status == SystemP_SUCCESS)
        {
            status = SCMI_getSCMIProtocolErrorMapped(outData.status);
        }

        if(status == SystemP_SUCCESS)
        {
            *numPosParents = 0U;

            do
            {
                numParentsRecv = SCMI_CLK_POSSIBLE_PARENTS_NUM_PARENTS_RECV
                                (outData.numParentsFlags);
                numParentsPend = SCMI_CLK_POSSIBLE_PARENTS_NUM_PARENTS_REM
                                (outData.numParentsFlags);

                if(numParentsRecv != 0U)
                {
                    for(uint8_t iter = 0U; iter < numParentsRecv; iter++)
                    {
                        *(iterator + iter) = \
                                *((uint32_t *)outData.possibleParents + iter);
                    }
                    iterator += numParentsRecv;
                    *numPosParents += numParentsRecv;
                }

                if(numParentsPend != 0U)
                {
                    inData.skipParents = numParentsRecv;

                    status = SCMITransport_processMessage(handle, &message);
                    status += SCMI_getSCMIProtocolErrorMapped(outData.status);
                }

            } while ((numParentsPend != 0U) && (numParentsRecv != 0U) && \
                     (status == SystemP_SUCCESS));
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t SCMI_clockProtocolInit(SCMI_Handle handle)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_Config *config = (SCMI_Config *)handle;
    SCMI_ClockProtocol *protocol = &config->clockProto;

    if(handle != NULL)
    {
        status = SCMI_baseGenericProtocolVersion(handle, SCMI_PROTOCOL_CLOCK,
                                                 &protocol->version);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("SCMI: Clock: Get protocol version failed.\r\n");
        }

        status += SCMI_clockGetProtocolAttrs(handle, &protocol->numClocks);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}
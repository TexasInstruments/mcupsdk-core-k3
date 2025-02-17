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
 *  \file scmi.c
 *
 *  \brief File containing SCMI Driver APIs implementation for version V0.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ==================================================== ====================== */

#include <stdint.h>
#include <string.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/scp/scmi/v0/scmi_base.h>
#include <drivers/scp/scmi/v0/scmi_power_domain.h>
#include <drivers/scp/scmi/v0/scmi_clock.h>
#include <drivers/scp/scmi/v0/scmi.h>
#include <drivers/scp/scmi/v0/scmi_protocol.h>
#include <drivers/scp/scmi/v0/transport/scmi_transport.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    void                   *openLock;
    /* *< Driver lock - to protect across open/close */
    SemaphoreP_Object       lockObj;
    /* *< Driver lock object */
} SCMI_DrvObj;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Externs */
extern SCMI_Config gSCMIConfig[];
extern uint32_t gSCMIConfigNum;

/* * \brief Driver object */
static SCMI_DrvObj gSCMIDrvObj =
{
    .openLock = NULL,
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t SCMI_validateRequiredProtocols(SCMI_Config *config);
static int32_t SCMI_fetchBaseProtocolInfo(SCMI_Config *config);
static int32_t SCMI_initRequiredProtocols(SCMI_Config *config);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SCMI_init(void)
{
    int32_t status;
    uint32_t count;
    SCMI_Object *obj;

    /* Init each driver instance object */
    for(count = 0U; count < gSCMIConfigNum; count++)
    {
        /* Init object variables */
        obj = gSCMIConfig[count].object;
        DebugP_assert(NULL != obj);
    }

    /* Create the driver lock */
    status = SemaphoreP_constructMutex(&gSCMIDrvObj.lockObj);
    if(SystemP_SUCCESS == status)
    {
        gSCMIDrvObj.openLock = &gSCMIDrvObj.lockObj;
    }

    return;
}

void SCMI_deinit(void)
{
    /* Delete driver lock */
    if(NULL != gSCMIDrvObj.openLock)
    {
        SemaphoreP_destruct(&gSCMIDrvObj.lockObj);
        gSCMIDrvObj.openLock = NULL;
    }

    return;
}

SCMI_Handle SCMI_open(uint32_t instanceIndex)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_Handle handle = NULL;
    SCMI_Config *config = NULL;
    SCMI_Object *obj = NULL;

    /* Check for valid index */
    if(instanceIndex >= gSCMIConfigNum)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        config = &gSCMIConfig[instanceIndex];
    }

    /* Protect this region from a concurrent SCMI_Open */
    DebugP_assert(NULL != gSCMIDrvObj.openLock);
    SemaphoreP_pend(&gSCMIDrvObj.lockObj, SystemP_WAIT_FOREVER);

    if(SystemP_SUCCESS == status)
    {
        obj = config->object;
        DebugP_assert(NULL != obj);
        if(1U == config->isOpen)
        {
            /* Handle already opened */
            status = SystemP_FAILURE;
        }
    }

    if(SystemP_SUCCESS == status)
    {
        /* Create instance lock */
        status += SemaphoreP_constructMutex(&obj->lockSem);

        SCMI_TransportObject *transport = (SCMI_TransportObject *)obj->transferObject;
        /* Create transfer sync semaphore */
        status += SemaphoreP_constructBinary(&transport->transportLock, 1U);

        if(status == SystemP_SUCCESS)
        {
            status = SCMI_fetchBaseProtocolInfo(config);
            status += SCMI_validateRequiredProtocols(config);

            if(status == SystemP_SUCCESS)
            {
                status = SCMI_initRequiredProtocols(config);
            }

        }
    }

    if(SystemP_SUCCESS == status)
    {
        config->isOpen = 1U;
        handle = (SCMI_Handle) config;
    }

    SemaphoreP_post(&gSCMIDrvObj.lockObj);

    /* Free up resources in case of error */
    if(SystemP_SUCCESS != status)
    {
        if(NULL != config)
        {
            SCMI_close((SCMI_Handle) config);
        }
    }
    return handle;
}

void SCMI_close(SCMI_Handle handle)
{
    if(handle != NULL)
    {
        SCMI_Object *obj = ((SCMI_Config *)handle)->object;
        SCMI_TransportObject *transport = (SCMI_TransportObject *)obj->transferObject;

        /* Destruct all locks and Hwi objects */
        SemaphoreP_destruct(&obj->lockSem);
        SemaphoreP_destruct(&transport->transportLock);
        ((SCMI_Config *)handle)->isOpen = 0U;
        SemaphoreP_post(&gSCMIDrvObj.lockObj);

    }

    return;
}

SCMI_Handle SCMI_getHandle(uint32_t driverInstanceIndex)
{
    SCMI_Handle         handle = NULL;
    /* Check instanceIndex */
    if(driverInstanceIndex < gSCMIConfigNum)
    {
        SCMI_Object *obj;
        obj = gSCMIConfig[driverInstanceIndex].object;

        if(obj && (1U == gSCMIConfig[driverInstanceIndex].isOpen))
        {
            /* valid handle */
            handle = (SCMI_Handle)&gSCMIConfig[driverInstanceIndex];
        }
    }

    return handle;
}

uint32_t SCMI_getInitDriverIndex(void)
{
    uint32_t instanceIndex = 0xFF;

    for(uint8_t count = 0U; count < gSCMIConfigNum; count++)
    {
        SCMI_Object *obj;
        obj = gSCMIConfig[count].object;
        if(obj && (1U == gSCMIConfig[count].isOpen))
        {
            instanceIndex = count;
            break;
        }
    }
    return instanceIndex;
}

int32_t SCMI_getSCMIProtocolErrorMapped(int32_t errorCode)
{
    int32_t status = SystemP_FAILURE;

    switch (errorCode)
    {
	    case SCMI_SUCCESS:
        {
            status  = SystemP_SUCCESS;
            break;
        }
	    case SCMI_NOT_SUPPORTED:
	    case SCMI_INVALID_PARAMETERS:
	    case SCMI_DENIED:
	    case SCMI_NOT_FOUND:
	    case SCMI_OUT_OF_RANGE:
	    case SCMI_BUSY:
	    case SCMI_COMMS_ERROR:
	    case SCMI_GENERIC_ERROR:
	    case SCMI_HARDWARE_ERROR:
	    case SCMI_PROTOCOL_ERROR:
        {
            status = SystemP_FAILURE;
            break;
        }
        default:
            break;
    };

    return status;
}

void SCMI_getProtocolVersionLog(uint32_t instanceIndex)
{
    SCMI_Handle handle = SCMI_getHandle(instanceIndex);

    if(handle != NULL)
    {
        SCMI_Config *config = (SCMI_Config *)handle;
        SCMI_AgentDataInfo *agent  = &config->agentInfo;
        SCMI_PowerDomainProtocol *pdProtocol = &config->powerDomainProto;
        SCMI_ClockProtocol *clkProtocol = &config->clockProto;

        DebugP_log("SCMI: Base protocol version %x\r\n", agent->version);
        DebugP_log("SCMI: Power Domain: Protocol version %x\r\n", pdProtocol->version);
        DebugP_log("SCMI: Clock: Protocol version %x\r\n", clkProtocol->version);
    }
    else
    {
        DebugP_logError("SCMI: Protocol initialisation failed!!!\r\n");
    }
}

static int32_t SCMI_fetchBaseProtocolInfo(SCMI_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_AgentDataInfo *agent = NULL;
    SCMI_Handle handle = NULL;
    uint32_t protoCount = 0U;

    if(config != NULL)
    {
        agent = &config->agentInfo;
        handle = (SCMI_Handle) config;

        status = SCMI_getBaseProtocolVersion(handle, &agent->version);
	    if (status != SystemP_SUCCESS)
        {
		    DebugP_logError("SCMI: Get base protocol version failed.\r\n");
	    }

        if(status == SystemP_SUCCESS)
        {
            if(agent->version < SCMI_BASE_PROTOCOL_VERSION)
            {
                status = SystemP_FAILURE;
                DebugP_logError("SCMI: Base protocol version (%x) lower than expected.\r\n",
                                agent->version);
            }
        }

        if(status == SystemP_SUCCESS)
        {
            status = SCMI_baseGetProtocolAttributes(handle, &agent->numAgents,
                                                    &agent->numProtocols);
            if (status != SystemP_SUCCESS)
            {
                DebugP_logError("SCMI: Get base protocol attributes failed.\r\n");
            }
        }

        if(status == SystemP_SUCCESS)
        {
            status = SCMI_baseDiscoverVendor(handle, agent->vendor);
            if (status != SystemP_SUCCESS)
            {
                DebugP_logError("SCMI: Get base discover vendor failed.\r\n");
            }
        }

        if(status == SystemP_SUCCESS)
        {
            status = SCMI_baseDiscoverSubVendor(handle, agent->subVendor);
            if (status != SystemP_SUCCESS)
            {
                DebugP_logError("SCMI: Get base discover sub-vendor failed.\r\n");
            }
        }

        if(status == SystemP_SUCCESS)
        {
            status = SCMI_baseDiscoverImplementationVersion(handle,
                                                    &agent->implementationVersion);
            if(status != SystemP_SUCCESS)
            {
                DebugP_logError("SCMI: Get base discover implementation version failed.\r\n");
            }
        }

        if(status == SystemP_SUCCESS)
        {
            status = SCMI_baseDiscoverListProtocols(handle, &protoCount,
                                                    agent->protocols);
            if((status != SystemP_SUCCESS) || (protoCount != agent->numProtocols))
            {
                DebugP_logError("SCMI: Get base discover list protocols failed.\r\n");
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t SCMI_validateRequiredProtocols(SCMI_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_AgentDataInfo *agent = NULL;
    SCMI_Object *obj = NULL;

    if(config != NULL)
    {
        agent = &config->agentInfo;
        obj = config->object;

        for(uint8_t count = 0U; count < obj->requiredProtoCount; count++)
        {
            bool protoFound = false;

            for(uint8_t iter = 0U; iter < agent->numProtocols; iter++)
            {
                if(agent->protocols[iter] == obj->requiredProtoList[count])
                {
                    protoFound = true;
                    break;
                }
            }

            if(!protoFound)
            {
                status = SystemP_FAILURE;
                break;
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t SCMI_initRequiredProtocols(SCMI_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    SCMI_Object *obj = NULL;

    if(config != NULL)
    {
        obj = config->object;

        for(uint8_t iterator = 0U; (iterator < obj->requiredProtoCount) &&
            (status == SystemP_SUCCESS); iterator++)
        {
            switch (obj->requiredProtoList[iterator])
            {
                case SCMI_PROTOCOL_POWER:
                {
                    status = SCMI_powerDomainProtocolInit((SCMI_Handle)config);
                    break;
                }
                case SCMI_PROTOCOL_CLOCK:
                {
                    status = SCMI_clockProtocolInit((SCMI_Handle)config);
                    break;
                }
                default:
                {
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

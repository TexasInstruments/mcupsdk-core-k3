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
 *  \file scmi.h
 *
 *  \brief SCMI Driver API/interface file.
 *   This is SCMI top level include for applications.
 */

#ifndef SCMI_H
#define SCMI_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/scp/scmi/v0/scmi_protocol.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**< Maximum possible parents */
#define SCMI_MAX_POSSIBLE_PARENTS             (16U)

/** \brief A handle that is returned from a #SCMI_open() call */
typedef void* SCMI_Handle;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief SCMI_SharedMemory - Description of a Shared memory buffer
 */
typedef struct
{
	uint8_t *buf;
    /**< Shared memory base address. */
	uint32_t size;
    /**< Shared memory byte size. */
} SCMI_SharedMemory;

typedef struct
{
	uint8_t id;
    /**< The identifier of the message being sent. */
	uint8_t protocol_id;
    /**< The identifier of the protocol used to send @id message */
	uint8_t type;
    /**< The SCMI type for this message. */
	uint16_t seq;
    /* The token to identify the message. When a message returns, the
     * platform returns the whole message header unmodified including the
     * token.
     */
	uint32_t status;
    /**< Status of the transfer once it's complete. */
} SCMI_messageHeader;

typedef struct
{
	SCMI_messageHeader  header;
    /**< SCMI Message(Tx/Rx) header */
	uint8_t             *inputMessage;
    /**< Pointer to the message payload sent by the driver. */
	uint32_t            inputMessageSize;
    /**< Byte size of the message payload sent. */
	uint8_t             *outputMessage;
    /**< Pointer to buffer to store response message payload. */
	uint32_t            outputMessageSize;
    /**< Byte size of the response buffer and response payload. */
} SCMI_MessageData;

typedef struct
{
    uint32_t version;
    /**< SCMI version */
	uint32_t numAgents;
    /**< Number of agents in the system */
	uint32_t numProtocols;
    /**< Number of protocols supported by SCMI server */
	uint32_t implementationVersion;
    /**< Implementation version */
	uint8_t protocols[SCMI_BASE_MAX_NUM_PROTOCOLS];
    /**< List if protocols supported */
	uint8_t vendor[SCMI_BASE_NAME_LENGTH_MAX];
    /**< Vendor name */
	uint8_t subVendor[SCMI_BASE_NAME_LENGTH_MAX];
    /**< SubVendor name */
} SCMI_AgentDataInfo;

typedef struct
{
    uint32_t version;
    /**< Power domain protocol version */
    uint32_t numPowerDomains;
    /**< Number of power domains */
	uint32_t statsLen;
    /**< Length of statistics shared memory region */
    uint64_t statsAddr;
    /**< Address of statistics shared memory region */
} SCMI_PowerDomainProtocol;

typedef struct
{
    uint32_t version;
    /**< Clock protocol version */
    uint32_t numClocks;
    /**< Number of clocks */
} SCMI_ClockProtocol;

typedef struct
{
    uint32_t                requiredProtoCount;
    /**< Count of required protocol supported by driver. */
    uint8_t                 *requiredProtoList;
    /**< Pointer to required protocol list. */
    void                    *transferObject;
    /**< Pointer to the transfer object */
    SCMI_SharedMemory       *sharedMem;
    /**< Pointer to the shared memory */
    SemaphoreP_Object       lockSem;
    /**< Semaphore to protect the flash layer calls per instance. */
} SCMI_Object;

typedef struct SCMI_Config_s
{
    uint32_t                    isOpen;
    /**< Flag to indicate if the instance is already open */
    SCMI_Object                 *object;
    /**< Pointer to driver specific data object */
    SCMI_AgentDataInfo          agentInfo;
    /**< Data structure to maintain SCMI agent info. */
    SCMI_PowerDomainProtocol    powerDomainProto;
    /**< Data structure to maintain Power Domain Protocol information */
    SCMI_ClockProtocol          clockProto;
    /**< Data structure to maintain clock Protocol information */
} SCMI_Config;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief SCMI initialization function.
 *   This function should be called before calling any driver APIs and
 *   only once.
 *
 *  \return None
 */
void SCMI_init(void);

/**
 *  \brief  This function de-initializes the SCMI module
 *
 *  \return None
 */
void SCMI_deinit(void);

/**
 *  \brief  This function opens a given SCMI instance
 *
 *  \param  instanceIndex Index of config to use in the *SCMI_Config* array
 *
 *  \return A #SCMI_Handle on success or a NULL on an error or if it has been
 *          opened already
 */
SCMI_Handle SCMI_open(uint32_t instanceIndex);

/**
 *  \brief  This function closes a given SCMI instance.
 *
 *  \param  handle SCMI_Handle returned from SCMI_open API.
 *
 *  \return None
 */
void SCMI_close(SCMI_Handle handle);

/**
 *  \brief  This function returns the handle of an open SCMI
 *          Instance from the instance index
 *
 *  \param  driverInstanceIndex Index of config to use in the *SCMI_Config* array
 *
 *  \return An #SCMI_Handle if it has been opened already or NULL otherwise
 */
SCMI_Handle SCMI_getHandle(uint32_t driverInstanceIndex);

/**
 *  \brief  This function translates the SCMI error codes to SystemP error codes
 *
 *  \param errorCode Error code returned from the SCMI message
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_getSCMIProtocolErrorMapped(int32_t errorCode);

/**
 *  \brief  This function logs the SCMI version probed during init time.
 *
 *  \param instanceIndex Instance of SCMI that was opened in SCMI_open
 *
 *  \return None
 */
void SCMI_getProtocolVersionLog(uint32_t instanceIndex);

/**
 *  \brief  This function returns the initialised instance index.
 *
 *  \return instanceIndex First instance which is open for SCMI  driver
 */
uint32_t SCMI_getInitDriverIndex(void);
/* ========================================================================== */
/*                          Internal Declarations                             */
/* ========================================================================== */
/**
 *  \brief  Function to initialize the #SCMI_MessageData structure
 *
 *
 *  \param  trans Pointer to a SCMI_MessageData structure
 *
 */
static inline void SCMI_initSCMIMessageData(SCMI_MessageData *msg);

/* ========================================================================== */
/*                          Internal Definitions                              */
/* ========================================================================== */
static inline void SCMI_initSCMIMessageData(SCMI_MessageData *msg)
{
    msg->header.id = 0xFFU;
    msg->header.protocol_id = 0xFFU;
    msg->header.seq = 0xFFU;
    msg->header.status = 0xFFU;
    msg->header.type = 0xFFU;
    msg->inputMessage = NULL;
    msg->inputMessageSize = 0U;
    msg->outputMessage = NULL;
    msg->outputMessageSize = 0U;
}

#endif
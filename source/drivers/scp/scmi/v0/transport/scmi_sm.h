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
 *  \file scmi_sm.h
 *
 *  \brief Header file containing scmi shared memory APIs.
 *
 */

#ifndef SCMI_SM_H
#define SCMI_SM_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/scp/scmi/v0/scmi.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SCMI_SHMEM_FLAG_INTR_ENABLED_MASK		        (uint32_t)(0x1U)
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR_MASK	        (uint32_t)(0x2U)
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE_MASK          (uint32_t)(0x1U)
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_BUSY_VAL           (uint32_t)(0U)
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE_VAL           (uint32_t)(1U)


#define GENMASK(h, l)               (((~0UL) << (l)) & (~0UL >> (32 - 1 - (h))))

#define SCMI_SHARED_MEM_HEADER_TOKEN(token)		    (((token) << 18) & GENMASK(31, 18))
#define SCMI_SHARED_MEM_HEADER_PROTOCOL_ID(proto)	(((proto) << 10) & GENMASK(17, 10))
#define SCMI_SHARED_MEM_HEADER_MESSAGE_TYPE(type)	(((type) << 18) & GENMASK(9, 8))
#define SCMI_SHARED_MEM_HEADER_MESSAGE_ID(id)	    ((id) & GENMASK(7, 0))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief SCMI_SharedMemoryMessage - Description of the shared memory message
 *        buffer.
 *
 * Shared Memory based Transport uses 28 byte header prior message payload to
 * handle the state of the communication channel realized by the shared memory
 * area and to define SCMI protocol information the payload relates to.
 *
 */
typedef struct
{
	uint32_t reserved;
    /**< Reserved */
	uint32_t channelStatus;
    /**< Bits[31:2] Reserved, must be zero.
     * Bit[1] Channel error : This bit is set to 1 if the previous
     * message was not transmitted due to a communications error. The caller
     * must clear it when it has ownership of the channel.
     * Bit[0] Channel free : This bit is set to 1 if the channel is free.
     * This bit is cleared to 0 if the channel is busy.
     */
	uint32_t reserved1[2];
    /**< Implementation defined field */
	uint32_t flags;
    /* Channel flags. */
	uint32_t length;
    /**< Total Length in bytes of the Message header and the command payload
     * (4+N)
     */
	uint32_t messageHdr;
    /**< Message header field */
	uint8_t messagePayload[0];
    /**< Array of 32-bit values that are used to hold any
     * parameters or return values.
     */
} SCMI_SharedMemoryMessage;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief API to write SCMI message data to shared memory.
 *
 *  \param  handle  SCMI handle.
 *  \param  msg     SCMI message data
 *
 *  \return SystemP_SUCCESS if successful, else SystemP_FAILURE
 */
int32_t SCMI_writeMessageToSharedMemory(SCMI_Handle handle,
                                        SCMI_MessageData *msg);

/**
 *  \brief API to read SCMI message response data from shared memory.
 *
 *  \param  handle  SCMI handle.
 *  \param  msg     SCMI message data
 *
 *  \return SystemP_SUCCESS if successful, else SystemP_FAILURE
 */
int32_t SCMI_readResponseFromSharedMemory(SCMI_Handle handle,
                                          SCMI_MessageData *msg);

/**
 *  \brief API to clear channel in shared memory.
 *
 *  \param  object  Pointer to SCMI_TransportObject structure.
 *
 */
void SCMI_clearSharedMemoryChannel(SCMI_Handle handle);

#endif /* SCMI_SM_H */

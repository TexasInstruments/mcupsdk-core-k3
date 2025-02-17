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
 *  \file flash.c
 *
 *  \brief File containing Flash Driver APIs implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/utils/utils.h>
#include <drivers/scp/scmi/v0/scmi.h>
#include <drivers/scp/scmi/v0/transport/scmi_sm.h>
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

int32_t SCMI_writeMessageToSharedMemory(SCMI_Handle handle,
                                        SCMI_MessageData *msg)
{
    int32_t status = SystemP_SUCCESS;

    if(handle != NULL)
    {
        SCMI_Object *obj = ((SCMI_Config *)handle)->object;
        SCMI_SharedMemoryMessage *hdr = (SCMI_SharedMemoryMessage *)obj->sharedMem->buf;

        if ((hdr->channelStatus & SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE_MASK) == \
            SCMI_SHMEM_CHAN_STAT_CHANNEL_BUSY_VAL)
        {
            status = SystemP_FAILURE;
        }

        if ((obj->sharedMem->size < (sizeof(*hdr) + msg->inputMessageSize)) || \
            (obj->sharedMem->size < (sizeof(*hdr) + msg->outputMessageSize)))
        {
            status = SystemP_FAILURE;
        }

        if(status == SystemP_SUCCESS)
        {
            /* Write SCMI message into shared memory. */
            /* Load message in shared memory */
            hdr->channelStatus &= ~SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE_MASK;
            hdr->length = msg->inputMessageSize + sizeof(hdr->messageHdr);
            hdr->messageHdr = SCMI_SHARED_MEM_HEADER_TOKEN(msg->header.seq) |
                    SCMI_SHARED_MEM_HEADER_MESSAGE_TYPE(msg->header.type) |
                    SCMI_SHARED_MEM_HEADER_PROTOCOL_ID(msg->header.protocol_id) |
                    SCMI_SHARED_MEM_HEADER_MESSAGE_ID(msg->header.id);

            Utils_memcopyDestinationUnalingned(hdr->messagePayload,
                                            msg->inputMessage,
                                            msg->inputMessageSize);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

	return status;
}

int32_t SCMI_readResponseFromSharedMemory(SCMI_Handle handle,
                                          SCMI_MessageData *msg)
{
    int32_t status = SystemP_SUCCESS;

    if(handle != NULL)
    {
        SCMI_Object *obj = ((SCMI_Config *)handle)->object;
        SCMI_SharedMemoryMessage *hdr = (SCMI_SharedMemoryMessage *)obj->sharedMem->buf;

        if ((hdr->channelStatus & SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE_MASK) == \
            SCMI_SHMEM_CHAN_STAT_CHANNEL_BUSY_VAL)
        {
            status = SystemP_FAILURE;
        }

        if ((hdr->channelStatus & SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR_MASK) == \
            SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR_MASK)
        {
            status = SystemP_FAILURE;
        }

        if (hdr->length > (msg->outputMessageSize + sizeof(hdr->messageHdr)))
        {
            status =  SystemP_FAILURE;
        }

        if(status == SystemP_SUCCESS)
        {
            /* Read SCMI message from a shared buffer and copy it into message data. */
            msg->outputMessageSize = hdr->length - sizeof(hdr->messageHdr);

            Utils_memcopySourceUnalingned(msg->outputMessage, hdr->messagePayload,
                                        msg->outputMessageSize);
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

	return status;
}

void SCMI_clearSharedMemoryChannel(SCMI_Handle handle)
{
    if(handle != NULL)
    {
        SCMI_Object *obj = ((SCMI_Config *)handle)->object;

        SCMI_SharedMemoryMessage *hdr = (void *)obj->sharedMem->buf;
        /* Clear SMT flags in shared buffer to allow further message exchange. */
        hdr->channelStatus &= ~SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR_MASK;
    }

}



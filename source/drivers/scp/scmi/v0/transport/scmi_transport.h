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
 *  \file scmi_transport.h
 *
 *  \brief Header file containing scmi transport APIs.
 *
 */

#ifndef SCMI_TRANSPORT_H
#define SCMI_TRANSPORT_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/scp/scmi/v0/scmi.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief Driver implementation to send a SCMI message.
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new type of transport needs to be implemented.
 *
 * \param handle [in] SCMI driver handle
 * \param message [in] SCMI message structure
 *
 * \return SystemP_SUCCESS on success, else SystemP_FAILURE
 */
typedef int32_t (*SCMI_TransportProcessMessage)(SCMI_Handle handle,
                                                SCMI_MessageData *message);

/**
 * \brief Driver implementation to receive a response for SCMI message.
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new type of transport needs to be implemented.
 *
 * \param handle [in] SCMI driver handle
 * \param message [in] SCMI message structure
 *
 * \return SystemP_SUCCESS on success, else SystemP_FAILURE
 */
typedef int32_t (*SCMI_TransportFetchResponse)(SCMI_Handle handle,
                                               SCMI_MessageData *message);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    SCMI_TransportProcessMessage        processMessageFxn;
    /**< Transport driver implementation specific callback */
    SCMI_TransportFetchResponse         fetchResponseFxn;
    /**< Transport driver implementation specific callback */
} SCMI_TransportFxns;

typedef struct
{
    uint32_t            smccFuntionID;
    /**< SMCC function ID when used SMCC for transport channel. */
    SCMI_TransportFxns  *trptFxns;
    /**< Pointer to to the transport layer functions. */
    SemaphoreP_Object   transportLock;
    /**< Mutex lock for the transport layer. */
} SCMI_TransportObject;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Driver implementation to send a SCMI message.
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new type of transport needs to be implemented.
 *
 * \param handle [in] SCMI driver handle
 * \param message [in] SCMI message structure
 *
 * \return SystemP_SUCCESS on success, else SystemP_FAILURE
 */
int32_t SCMITransport_processMessage(SCMI_Handle handle,
                                     SCMI_MessageData *message);

/**
 * \brief Driver implementation to receive a response for SCMI message.
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new type of transport needs to be implemented.
 *
 * \param handle [in] SCMI driver handle
 * \param message [in] SCMI message structure
 *
 * \return SystemP_SUCCESS on success, else SystemP_FAILURE
 */
int32_t SCMITransport_fetchResponse(SCMI_Handle handle,
                                    SCMI_MessageData *message);


#endif /* SCMI_TRANSPORT_H */
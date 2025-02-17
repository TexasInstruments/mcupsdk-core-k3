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
 *  \file scmi_base.h
 *
 *  \brief Header file containing scmi base protocol APIs.
 *
 */

#ifndef SCMI_BASE_H
#define SCMI_BASE_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/scp/scmi/v0/scmi.h>

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

/**
 *  \brief API to get generic protocol version
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param protocolId  SCMI standard protocol
 *  \param statsAddr  Pointer to version
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_baseGenericProtocolVersion(SCMI_Handle handle,
                                        SCMI_StandardProtocol protocolId,
                                        uint32_t *version);

/**
 *  \brief API to get base protocol version
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param statsAddr  Pointer to version
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_getBaseProtocolVersion(SCMI_Handle handle, uint32_t *version);

/**
 *  \brief API to get protocol attributes for base protocol. This gives number
 *         of agents and number of protocols supported in the platform.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param numAgents  Number of agents
 *  \param numProtocols  Number of protocols
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_baseGetProtocolAttributes(SCMI_Handle handle, uint32_t *numAgents,
                                       uint32_t *numProtocols);

/**
 *  \brief API to get message attributes for base protocol.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param messageId  Base protocol message identifier
 *  \param attributes  Attributes for the message
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_baseGetMessageAttributes(SCMI_Handle handle, uint32_t messageId,
                                      uint32_t *attributes);

/**
 *  \brief API to get vendor name string.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param vendor  Array to get vendor name
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_baseDiscoverVendor(SCMI_Handle handle, uint8_t *vendor);

/**
 *  \brief API to get Sub-vendor name string.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param vendor  Array to get Sub-vendor name
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_baseDiscoverSubVendor(SCMI_Handle handle,  uint8_t *subVendor);

/**
 *  \brief API to get vendor implementation version.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param implVersion Pointer to implementation version.
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_baseDiscoverImplementationVersion(SCMI_Handle handle,
                                               uint32_t *implVersion);

/**
 *  \brief API to get supported protocols count and list by platform.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param protocolCount Protocols count.
 *  \param protocols Array for protocols list.
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_baseDiscoverListProtocols(SCMI_Handle handle,
                                       uint32_t *protocolCount,
                                       uint8_t *protocols);


#endif /* SCMI_BASE_H */

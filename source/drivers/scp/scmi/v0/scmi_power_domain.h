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
 *  \file scmi_power_domain.h
 *
 *  \brief Header file containing scmi power domain protocol APIs.
 *
 */

#ifndef SCMI_POWER_DOMAIN_H
#define SCMI_POWER_DOMAIN_H

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
 *  \brief API to get power domain protocol attributes
 *         using power domain SCMI protocol.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param numPowerDomains  Pointer to get number of power domains
 *  \param statsAddr  Pointer to get address for statistics shared memory
 *  \param statsLen  Pointer to get length for statistics shared memory
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_powerDomainGetProtocolAttrs(SCMI_Handle handle,
                                         uint32_t *numPowerDomains,
                                         uint64_t *statsAddr,
                                         uint32_t *statsLen);
/**
 *  \brief API to get power domain attributes for a power domain Id.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param domainId  Power domain Identifier
 *  \param attributes  Pointer to power domain attributes
 *  \param name  Pointer to name of power domain
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_powerDomainGetAttrs(SCMI_Handle handle, uint32_t domainId,
                                 uint32_t *attributes, uint8_t *name);

/**
 *  \brief API to set power domain to on or off state.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param domainId  Power domain Identifier
 *  \param flags  Parameter flags for the power domain
 *  \param pstate  Power state
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_powerDomainStateSet(SCMI_Handle handle, uint32_t domainId,
                                 uint32_t flags, uint32_t pstate);

/**
 *  \brief API to get power domain state.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param domainId  Power domain Identifier
 *  \param pstate  Power state pointer
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_powerDomainStateGet(SCMI_Handle handle, uint32_t domainId,
                                 uint32_t *pstate);

/**
 *  \brief API to get power domain extended name.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param domainId  Power domain Identifier
 *  \param name  Pointer to extended name
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_powerDomainNameGet(SCMI_Handle handle, uint32_t domainId,
                                uint8_t *name);

/**
 *  \brief API to initialise power domain protocol.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_powerDomainProtocolInit(SCMI_Handle handle);

#endif /* SCMI_POWER_DOMAIN_H */

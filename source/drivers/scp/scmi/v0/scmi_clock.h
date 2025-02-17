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
 *  \file scmi_clock.h
 *
 *  \brief Header file containing scmi clock protocol APIs.
 *
 */

#ifndef SCMI_CLOCK_H
#define SCMI_CLOCK_H

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
 *  \brief API to get clock protocol attributes
 *         using clockSCMI protocol.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param numClocks  Pointer to get number of clocks
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockGetProtocolAttrs(SCMI_Handle handle,
                                   uint32_t *numClocks);

/**
 *  \brief API to get clock attributes for a clock Id.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param clockId  Clock Identifier
 *  \param attributes  Pointer to clock attributes
 *  \param name  Pointer to name of clock
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockGetAttrs(SCMI_Handle handle, uint32_t clockId,
                           uint32_t *attributes, uint8_t *name);

/**
 *  \brief API to set clock state for a clock to enable or disable state.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param clockId  Clock Identifier
 *  \param clockState  Clock state
 *  \param pstate  Power state
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockConfigSet(SCMI_Handle handle, uint32_t clockId,
                            uint32_t clockState);

/**
 *  \brief API to get clock state for a clock.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param clockId  Clock Identifier
 *  \param clockState  Pointer to Clock state
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockConfigGet(SCMI_Handle handle, uint32_t clockId,
                            uint32_t *clockState);

/**
 *  \brief API to get clock's extended name.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param clockId  Clock Identifier
 *  \param name  Pointer to extended name
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockNameGet(SCMI_Handle handle, uint32_t clockId,
                          uint8_t *name);

/**
 *  \brief API to get clock rate for a clock.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param clockId  Clock Identifier
 *  \param clockRate  Pointer to clock rate
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockRateGet(SCMI_Handle handle, uint32_t clockId,
                          uint64_t *clockRate);

/**
 *  \brief API to set clock rate for a clock.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param clockId  Clock Identifier
 *  \param clockRate Clock rate
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockRateSet(SCMI_Handle handle, uint32_t clockId,
                          uint64_t clockRate);

/**
 *  \brief API to set parent for a clock.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param clockId  Clock Identifier
 *  \param parentId Parent Identifier for the clock
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockParentSet(SCMI_Handle handle, uint32_t clockId,
                            uint32_t parentId);

/**
 *  \brief API to get parent for a clock.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param clockId  Clock Identifier
 *  \param parentId Pointer to Parent Identifier for the clock
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockParentGet(SCMI_Handle handle, uint32_t clockId,
                            uint32_t *parentId);

/**
 *  \brief API to get possible parents for a clock.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *  \param clockId  Clock Identifier
 *  \param numPosParents Pointer to number for possible parents.
 *  \param possibleParents Pointer to array of possible parents.
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockGetPossibleParents(SCMI_Handle handle, uint32_t clockId,
                                     uint32_t *numPosParents,
                                     uint32_t *possibleParents);

/**
 *  \brief API to initialise clock protocol.
 *
 *  \param handle  SCMI_Handle handle returned from SCMI_open
 *
 *  \return SystemP_SUCCESS or SystemP_FAILURE
 */
int32_t SCMI_clockProtocolInit(SCMI_Handle handle);

#endif /* SCMI_CLOCK_H */

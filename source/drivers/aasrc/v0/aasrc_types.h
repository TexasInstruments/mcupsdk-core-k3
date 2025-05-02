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
 *  \ingroup DRV_AASRC_MODULE
 *  \defgroup DRV_AASRC_TYPES_MODULE AASRC Channel Types
 *            This is AASRC Channel Types
 *
 *  @{
 */

/**
 *  \file v0/aasrc_types.h
 *
 *  \brief AASRC Driver API/interface data types file.
 */

#ifndef AASRC_TYPES_H_
#define AASRC_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief A handle that is returned from a #AASRC_open() call */
typedef void *AASRC_Handle;

/** \brief AASRC clock zone handle whic points to clk_zone structure*/
typedef void *AASRC_ClkZoneHandle;

/** \brief AASRC channel handle which points to AASRC channnel status and configs*/
typedef void *AASRC_ChHandle;

/** \brief AASRC udma handle which points to udma instance */
typedef void *AASRC_DmaHandle;

/**
 *  \anchor AASRC_ErrorCodes
 *  \name AASRC Error Codes
 *
 *  Error codes returned by AASRC APIs
 *
 *  @{
 */
/** \brief API call successful */
#define AASRC_SOK                        ( (int32_t) (0))
/** \brief API call returned with error as failed. Used for generic error.
 *  It may be some hardware failure and/or software failure. */
#define AASRC_EFAIL                      (-(int32_t) (1))
/** \brief API call returned with error as bad arguments.
 *  Typically, NULL pointer passed to the API where its not expected. */
#define AASRC_EBADARGS                   (-(int32_t) (2))
/** \brief API call returned with error as invalid parameters.
 *  Typically when parameters passed are not valid or out of range. */
#define AASRC_EINVALID_PARAMS            (-(int32_t) (3))
/** \brief API call returned with error as timed out. Typically API is
 *  waiting for some condition and returned as condition not happened
 *  in the timeout period. */
#define AASRC_ETIMEOUT                   (-(int32_t) (4))
/** \brief API call returned with error as allocation failed. */
#define AASRC_EALLOC                     (-(int32_t) (5))
/** @} */

/**
 *  \anchor AASRC_ChTypes
 *  \name AASRC Channel Types
 *
 *  This represents the different types of channels that can be requested
 *  from AASRC IP.
 *      MONO    - single audio channel
 *      STEREO  - two synchronous audio channels
 *      GROUP   - three or more synchronous audio channels
 *
 *  @{
 */
#define AASRC_MONO                      (0U)
#define AASRC_STEREO                    (1U)
#define AASRC_GROUP                     (2U)
/** @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef AASRC_TYPES_H_ */

/** @} */

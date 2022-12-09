/*
 *  Copyright (C) 2018-2019 Texas Instruments Incorporated
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
 *
 */
/**
 * \ingroup DRV_SCICLIENT_MODULE
 * \defgroup SCICLIENT_FMW_GEN_MSG_IF Sciclient Generic Messages API Interface
 *
 *
 * @{
 */
/**
 *  \file   sciclient_genericMsgs.h
 *
 *  \brief  This file contains the definition of all the shim layer functions
 *          which request DMSC for generic services.
 */

#ifndef SCICLIENT_GENERIC_MSGS_H_
#define SCICLIENT_GENERIC_MSGS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 *  \brief Queries SYSFW about MSMC configuration
 *
 *  Queries the sysfw for details on msmc. Response will contain the start and
 *  end address of the msmc region available
 *
 *  \n<b>Message</b>:    @ref TISCI_MSG_QUERY_MSMC
 *  \n<b>Request</b>:    @ref tisci_query_msmc_req
 *  \n<b>Response</b>:   @ref tisci_query_msmc_resp
 *
 *  \param  req             Pointer to msmc query request payload
 *
 *  \param  resp            Pointer to msmc query response payload
 *
 *  \param  timeout         Gives a sense of how long to wait for the operation.
 *                          Refer \ref Sciclient_ServiceOperationTimeout.
 *
 *  \return CSL_PASS on success, else failure
 */
int32_t Sciclient_msmcQuery(const struct tisci_query_msmc_req *req,
                            struct tisci_query_msmc_resp *resp,
                            uint32_t timeout);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef SCICLIENT_GENERIC_MSGS_H_ */

/* @} */

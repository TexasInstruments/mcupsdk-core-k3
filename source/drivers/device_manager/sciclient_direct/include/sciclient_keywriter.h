/*
 *  Copyright (C) 2020 Texas Instruments Incorporated
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
 * \defgroup SCICLIENT_FMW_OTP_IF Sciclient OTP API Interface
 *
 * OTP programming is done using the DMSC. This is needed to convert a
 * field securable device into a HS device.
 *
 * @{
 */
/**
 *  \file   sciclient_keywriter.h
 *
 *  \brief  This file contains the definition of all the message IDs, message
 *          formats to be able to interact with the System Controller firmware
 *          for OTP Key programming.
 *
 */

#ifndef SCICLIENT_KEYWRITER_H_
#define SCICLIENT_KEYWRITER_H_

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
 *  \brief    Message to request a processor
 *  Provides a means for either the “recovery master” host or another host in
 *  the permitted access list to request for a physical processor control.
 *
 *  \n<b>Message</b>:    #TISCI_MSG_KEY_WRITER
 *  \n<b>Request</b>:    #tisci_msg_keywriter_req
 *  \n<b>Response</b>:   #tisci_msg_keywriter_resp
 *
 *  \param  otpKeyCfgAddr   Address of otp writer key config structure
 *                          Refer \ref Sciclient_ProcessorIds.
 *  \param  timeout         Gives a sense of how long to wait for the operation.
 *                          Refer \ref Sciclient_ServiceOperationTimeout.
 *  \param  debug_response  Address of debug_response variable to store the 
 *  						debug response from API call 
 *  \return CSL_PASS on success, else failure
 */
int32_t Sciclient_otpProcessKeyCfg(uint32_t *otpKeyCfgAddr,
                                           uint32_t timeout, uint32_t *debug_response);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SCICLIENT_KEYWRITER_H_ */

/* @} */

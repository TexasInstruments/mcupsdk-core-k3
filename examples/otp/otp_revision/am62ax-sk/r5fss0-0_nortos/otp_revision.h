/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

/** \file otp_revsion.h
 *
 *   \brief This file contains runtime software revision update APIs.
 */

#ifndef OTP_REVISION_H_
#define OTP_REVISION_H_

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
 *  \brief Function to read OTP software revision from the efuses
 *
 *  \param identifier   [IN] OTP revision identifier from enum tisci_otp_revision_identifier
 *  \param val          [OUT] SWREV value read back
 *
 *  \return status [out] SystemP_SUCCESS on success
 */
int32_t otp_revsion_readSwrev(uint8_t identifier, uint32_t *val);

/**
 *  \brief Function to write/burn OTP software revision to the efuses
 *
 *  \param identifier   [IN] OTP revision identifier from enum tisci_otp_revision_identifier
 *  \param val          [IN] SWREV value to be written
 *
 *  \return status [out] SystemP_SUCCESS on success
 */
int32_t otp_revsion_writeSwrev(uint8_t identifier, uint32_t val);

/**
 *  \brief Function to read OTP key revision and key count from the efuses
 *
 *  \param keyCountVal    [OUT] Key count value read back
 *  \param keyRevVal      [OUT] KEYREV value read back
 *
 *  \return status [out] SystemP_SUCCESS on success
 */
int32_t otp_revsion_readKeyrevKeycnt(uint32_t *keyCountVal, uint32_t *keyRevVal);

/**
 *  \brief Function to set VPP, needed to write to eFUSEs
 */
void otp_revsion_setVpp(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef OTP_REVISION_H_ */

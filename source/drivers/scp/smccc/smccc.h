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
 *  \file smccc.h
 *
 *  \brief SMCCC stack interface.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifndef SMCCC_DEFS_H_
#define SMCCC_DEFS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define smccc_smc(...) __smccc_smc(__VA_ARGS__)

/* ========================================================================== */
/*                          Structure Declarations                            */
/* ========================================================================== */

/**
 * \brief Result from SMC call
 *
 * This structure contains the result values from registers 0 to 3 after an SMC
 * call is made.
 *
 */
typedef struct SMCCC_Res_s
{
	uint64_t a0;
	uint64_t a1;
	uint64_t a2;
	uint64_t a3;
} SMCCC_Res;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief make SMC calls
 *
 * \param a0-a7 [IN] arguments passed in registers 0 to 7
 * \param res [OUT] result values from registers 0 to 3
 *
 * This function follows SMC Calling Convention to make SMC calls.
 * The content of the values a0 to a7 are copied to registers 0 to 7
 * before the SMC instruction is called. The return values are taken
 * from register 0 to 3 after the SMC instruction is called. The param
 * res is updated with values from registers 0 to 3.
 */
void __smccc_smc(uint64_t a0, uint64_t a1,
			uint64_t a2, uint64_t a3, uint64_t a4,
			uint64_t a5, uint64_t a6, uint64_t a7,
			SMCCC_Res *res);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef SMCCC_DEFS_H_ */

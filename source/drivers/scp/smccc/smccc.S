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

 /* *
 *  \file   smccc.S
 *
 *  \brief  File containing SMCCC function for communication with the trusted firmware.
 */

/* ========================================================================== */
/*                            Global Symbols                                  */
/* ========================================================================== */

        .global __smccc_smc

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SMCCC_RES_X0_OFFS   (0)
#define SMCCC_RES_X2_OFFS   (16)

.macro SMCCC instr
	stp     x29, x30, [sp, #-16]!
	mov	x29, sp
	\instr	#0
	ldr	x4, [sp, #16]
	stp	x0, x1, [x4, #SMCCC_RES_X0_OFFS]
	stp	x2, x3, [x4, #SMCCC_RES_X2_OFFS]
	ldr	x4, [sp, #24]
	ldp     x29, x30, [sp], #16
	ret
.endm

/* ========================================================================== */
/*                       Function Definitions                                 */
/* ========================================================================== */

/*
 * void smccc_smc(unsigned uint64_t a0, unsigned uint64_t a1, unsigned uint64_t a2,
 *		  unsigned uint64_t a3, unsigned uint64_t a4, unsigned uint64_t a5,
 *		  unsigned uint64_t a6, unsigned uint64_t a7, struct arm_smccc_res *res)
 */
    .section .text.__smccc_smc
    .func __smccc_smc
__smccc_smc:
	SMCCC	smc
    .endfunc

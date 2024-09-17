
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

.text

.macro VECTOR_ENTRY name
        .align  7
\name:
.endm

    .global HwiP_gicv3Vectors
    .section .vecs, "ax"
    .align  11
HwiP_gicv3Vectors:

/*
 *************************************************************************
 * Exception from currentEL, using SP0
 *************************************************************************
 */
VECTOR_ENTRY el1SyncSP0
    B HwiP_SVC_Handler

VECTOR_ENTRY el1IrqSP0
    B HwiP_IRQ_Handler

VECTOR_ENTRY el1FiqSP0
    b       el1FiqSP0

VECTOR_ENTRY el1SErrorSP0
    B el1SErrorSP0

/*
 *************************************************************************
 * Exception from currentEL, using SPx
 *************************************************************************
 */
VECTOR_ENTRY el1SyncSPx
    B HwiP_SVC_Handler

VECTOR_ENTRY el1IrqSPx
    B HwiP_IRQ_Handler

VECTOR_ENTRY el1FiqSPx
    b    el1FiqSPx

VECTOR_ENTRY el1SErrorSPx
    B el1SErrorSPx

/*
 *************************************************************************
 * Exception from lowerEL, all lowerEL using Aarch64
 *************************************************************************
 */
VECTOR_ENTRY el0SyncAarch64
    b    el0SyncAarch64

VECTOR_ENTRY el0IrqAarch64
    b    el0IrqAarch64

VECTOR_ENTRY el0FiqAarch64
    b    el0FiqAarch64

VECTOR_ENTRY el0SErrorAarch64
    b    el0SErrorAarch64

/*
 *************************************************************************
 * Exception from lowerEL, all lowerEL using Aarch32
 *************************************************************************
 */
VECTOR_ENTRY el0SyncAarch32
    b    el0SyncAarch32

VECTOR_ENTRY el0IrqAarch32
    b    el0IrqAarch32

VECTOR_ENTRY el0FiqAarch32
    b    el0FiqAarch32

VECTOR_ENTRY el0SErrorAarch32
    b    el0SErrorAarch32

.end

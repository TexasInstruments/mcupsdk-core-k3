/***************************************************************************
 * Copyright (c) 2024 Microsoft Corporation 
 * 
 * This program and the accompanying materials are made available under the
 * terms of the MIT License which is available at
 * https://opensource.org/licenses/MIT.
 * 
 * SPDX-License-Identifier: MIT
 **************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** ThreadX Component                                                     */
/**                                                                       */
/**   Thread                                                              */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/
#ifdef TX_INCLUDE_USER_DEFINE_FILE
#include "tx_user.h"
#endif

    .text
    .align 3
/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _tx_thread_stack_build                               ARMv8-A        */
/*                                                           6.3.0        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function builds a stack frame on the supplied thread's stack.  */
/*    The stack frame results in a fake interrupt return to the supplied  */
/*    function pointer.                                                   */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    thread_ptr                            Pointer to thread             */
/*    function_ptr                          Pointer to entry function     */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _tx_thread_create                     Create thread service         */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
/*  01-31-2022     Andres Mlinar            Updated comments,             */
/*                                            resulting in version 6.1.10 */
/*  10-31-2023     Tiejun Zhou              Modified comment(s), added    */
/*                                            #include tx_user.h,         */
/*                                            resulting in version 6.3.0  */
/*                                                                        */
/**************************************************************************/

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

// VOID   _tx_thread_stack_build(TX_THREAD *thread_ptr, VOID (*function_ptr)(VOID))
// {
    .global _tx_thread_stack_build
    .type   _tx_thread_stack_build, @function
_tx_thread_stack_build:


    /* Build an interrupt frame.  On Cortex-A35 it should look like this:

       Stack Top:      SSPR        Initial SSPR
                       ELR         Point of interrupt
                       x28         Initial value for x28
                       not used    Not used
                       x26         Initial value for x26
                       x27         Initial value for x27
                       x24         Initial value for x24
                       x25         Initial value for x25
                       x22         Initial value for x22
                       x23         Initial value for x23
                       x20         Initial value for x20
                       x21         Initial value for x21
                       x18         Initial value for x18
                       x19         Initial value for x19
                       x16         Initial value for x16
                       x17         Initial value for x17
                       x14         Initial value for x14
                       x15         Initial value for x15
                       x12         Initial value for x12
                       x13         Initial value for x13
                       x10         Initial value for x10
                       x11         Initial value for x11
                       x8          Initial value for x8
                       x9          Initial value for x9
                       x6          Initial value for x6
                       x7          Initial value for x7
                       x4          Initial value for x4
                       x5          Initial value for x5
                       x2          Initial value for x2
                       x3          Initial value for x3
                       x0          Initial value for x0
                       x1          Initial value for x1
                       x29         Initial value for x29 (frame pointer)
                       x30         Initial value for x30 (link register)
                       0           For stack backtracing

    Stack Bottom: (higher memory address)  */

    LDR     x4, [x0, #24]                       // Pickup end of stack area
    BIC     x4, x4, #0xF                        // Ensure 16-byte alignment

    /* Actually build the stack frame.  */

    MOV     x2, #0                              // Build clear value
    MOV     x3, #0                              //

    STP     x2, x3, [x4, #-16]!                 // Set backtrace to 0
    STP     x2, x3, [x4, #-16]!                 // Set initial x29, x30
    STP     x2, x3, [x4, #-16]!                 // Set initial x0, x1
    STP     x2, x3, [x4, #-16]!                 // Set initial x2, x3
    STP     x2, x3, [x4, #-16]!                 // Set initial x4, x5
    STP     x2, x3, [x4, #-16]!                 // Set initial x6, x7
    STP     x2, x3, [x4, #-16]!                 // Set initial x8, x9
    STP     x2, x3, [x4, #-16]!                 // Set initial x10, x11
    STP     x2, x3, [x4, #-16]!                 // Set initial x12, x13
    STP     x2, x3, [x4, #-16]!                 // Set initial x14, x15
    STP     x2, x3, [x4, #-16]!                 // Set initial x16, x17
    STP     x2, x3, [x4, #-16]!                 // Set initial x18, x19
    STP     x2, x3, [x4, #-16]!                 // Set initial x20, x21
    STP     x2, x3, [x4, #-16]!                 // Set initial x22, x23
    STP     x2, x3, [x4, #-16]!                 // Set initial x24, x25
    STP     x2, x3, [x4, #-16]!                 // Set initial x26, x27
    STP     x2, x3, [x4, #-16]!                 // Set initial x28

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
    STP     q0,  q1,  [x4, #-32]!               // Save q0, q1
    STP     q2,  q3,  [x4, #-32]!               // Save q2, q3
    STP     q4,  q5,  [x4, #-32]!               // Save q4, q5
    STP     q6,  q7,  [x4, #-32]!               // Save q6, q7
    STP     q8,  q9,  [x4, #-32]!               // Save q8, q9
    STP     q10, q11, [x4, #-32]!               // Save q10, q11
    STP     q12, q13, [x4, #-32]!               // Save q12, q13
    STP     q14, q15, [x4, #-32]!               // Save q14, q15
    STP     q16, q17, [x4, #-32]!               // Save q16, q17
    STP     q18, q19, [x4, #-32]!               // Save q18, q19
    STP     q20, q21, [x4, #-32]!               // Save q20, q21
    STP     q22, q23, [x4, #-32]!               // Save q22, q23
    STP     q24, q25, [x4, #-32]!               // Save q24, q25
    STP     q26, q27, [x4, #-32]!               // Save q26, q27
    STP     q28, q29, [x4, #-32]!               // Save q28, q29
    STP     q30, q31, [x4, #-32]!               // Save q30, q31
    MRS     x2, FPSR                            // Pickup FPSR
    MRS     x3, FPCR                            // Pickup FPCR
    STP     x2, x3, [x4, #-16]!                 // Save FPSR, FPCR
#endif // #if !defined(__SOFT_FP__) && defined(__ARM_FP)

    MOV     x2, #0x5                            // Build initial SPSR  (EL1)

    MOV     x3, x1                              // Build initial ELR
    STP     x2, x3, [x4, #-16]!                 // Set initial SPSR & ELR

    /* Setup stack pointer.  */
    // thread_ptr -> tx_thread_stack_ptr =  x2;

    STR     x4, [x0, #8]                        // Save stack pointer in thread's
    RET                                         // Return to caller

// }

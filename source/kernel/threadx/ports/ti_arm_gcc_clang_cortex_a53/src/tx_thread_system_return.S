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
/*    _tx_thread_system_return                             ARMv8-A        */
/*                                                           6.3.0        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is target processor specific.  It is used to transfer */
/*    control from a thread back to the ThreadX system.  Only a           */
/*    minimal context is saved since the compiler assumes temp registers  */
/*    are going to get slicked by a function call anyway.                 */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _tx_thread_schedule                   Thread scheduling loop        */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    ThreadX components                                                  */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
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

// VOID   _tx_thread_system_return(VOID)
// {
    .global _tx_thread_system_return
    .type   _tx_thread_system_return, @function
_tx_thread_system_return:

    /* Save minimal context on the stack.  */

    MRS     x0, DAIF                            // Pickup DAIF
    MSR     DAIFSet, 0x3                        // Lockout interrupts
    STP     x29, x30, [sp, #-16]!               // Save x29 (frame pointer), x30 (link register)
    STP     x19, x20, [sp, #-16]!               // Save x19, x20
    STP     x21, x22, [sp, #-16]!               // Save x21, x22
    STP     x23, x24, [sp, #-16]!               // Save x23, x24
    STP     x25, x26, [sp, #-16]!               // Save x25, x26
    STP     x27, x28, [sp, #-16]!               // Save x27, x28
    LDR     x5, =_tx_thread_current_ptr         // Pickup address of current ptr
    LDR     x6, [x5, #0]                        // Pickup current thread pointer

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
    STP     q8,  q9,  [sp, #-32]!               // Save q8, q9
    STP     q10, q11, [sp, #-32]!               // Save q10, q11
    STP     q12, q13, [sp, #-32]!               // Save q12, q13
    STP     q14, q15, [sp, #-32]!               // Save q14, q15
    MRS     x2, FPSR                            // Pickup FPSR
    MRS     x3, FPCR                            // Pickup FPCR
    STP     x2, x3, [sp, #-16]!                 // Save FPSR, FPCR
#endif // #if !defined(__SOFT_FP__) && defined(__ARM_FP)

    MOV     x1, #0                              // Clear x1
    STP     x0, x1, [sp, #-16]!                 // Save DAIF and clear value for ELR_EK1

#if (defined(TX_ENABLE_EXECUTION_CHANGE_NOTIFY) || defined(TX_EXECUTION_PROFILE_ENABLE))

    /* Call the thread exit function to indicate the thread is no longer executing.  */

    MOV     x19, x5                             // Save x5
    MOV     x20, x6                             // Save x6
    BL      _tx_execution_thread_exit           // Call the thread exit function
    MOV     x5, x19                             // Restore x5
    MOV     x6, x20                             // Restore x6
#endif

    LDR     x2, =_tx_timer_time_slice           // Pickup address of time slice
    LDR     w1, [x2, #0]                        // Pickup current time slice

    /* Save current stack and switch to system stack.  */
    // _tx_thread_current_ptr -> tx_thread_stack_ptr =  sp;
    // sp = _tx_thread_system_stack_ptr;

    MOV     x4, sp                              //
    STR     x4, [x6, #8]                        // Save thread stack pointer
    LDR     x3, =_tx_thread_system_stack_ptr    // Pickup address of system stack
    LDR     x4, [x3, #0]                        // Pickup system stack pointer
    MOV     sp, x4                              // Setup system stack pointer

    /* Determine if the time-slice is active.  */
    // if (_tx_timer_time_slice)
    // {

    MOV     x4, #0                              // Build clear value
    CMP     w1, #0                              // Is a time-slice active?
    BEQ     __tx_thread_dont_save_ts            // No, don't save the time-slice

       /* Save the current remaining time-slice.  */
       // _tx_thread_current_ptr -> tx_thread_time_slice =  _tx_timer_time_slice;
       // _tx_timer_time_slice =  0;

    STR     w4, [x2, #0]                        // Clear time-slice
    STR     w1, [x6, #36]                       // Store current time-slice

    // }
__tx_thread_dont_save_ts:

    /* Clear the current thread pointer.  */
    // _tx_thread_current_ptr =  TX_NULL;

    STR     x4, [x5, #0]                        // Clear current thread pointer

    B       _tx_thread_schedule                 // Jump to scheduler!

// }

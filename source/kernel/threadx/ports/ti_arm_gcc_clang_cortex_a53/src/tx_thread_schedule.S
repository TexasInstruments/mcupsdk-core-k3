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
/*    _tx_thread_schedule                                  ARMv8-A        */
/*                                                           6.3.0        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function waits for a thread control block pointer to appear in */
/*    the _tx_thread_execute_ptr variable.  Once a thread pointer appears */
/*    in the variable, the corresponding thread is resumed.               */
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
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _tx_initialize_kernel_enter          ThreadX entry function         */
/*    _tx_thread_system_return             Return to system from thread   */
/*    _tx_thread_context_restore           Restore thread's context       */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
/*  01-31-2022     Andres Mlinar            Updated comments,             */
/*                                             added ARMv8.2-A support,   */
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

// VOID   _tx_thread_schedule(VOID)
// {
    .global _tx_thread_schedule
    .type   _tx_thread_schedule, @function
_tx_thread_schedule:

    /* Enable interrupts.  */

    MSR     DAIFClr, 0x3                        // Enable interrupts

    /* Wait for a thread to execute.  */
    // do
    // {

    LDR     x1, =_tx_thread_execute_ptr         // Address of thread execute ptr

#ifdef TX_ENABLE_WFI
__tx_thread_schedule_loop:
    LDR     x0, [x1, #0]                        // Pickup next thread to execute
    CMP     x0, #0                              // Is it NULL?
    BNE     _tx_thread_schedule_thread          //
    WFI                                         //
    B       __tx_thread_schedule_loop           // Keep looking for a thread
_tx_thread_schedule_thread:
#else
__tx_thread_schedule_loop:
    LDR     x0, [x1, #0]                        // Pickup next thread to execute
    CMP     x0, #0                              // Is it NULL?
    BEQ     __tx_thread_schedule_loop           // If so, keep looking for a thread
#endif

    // }
    // while(_tx_thread_execute_ptr == TX_NULL);

    /* Yes! We have a thread to execute.  Lockout interrupts and
       transfer control to it.  */

    MSR     DAIFSet, 0x3                        // Lockout interrupts

    /* Setup the current thread pointer.  */
    // _tx_thread_current_ptr =  _tx_thread_execute_ptr;

    LDR     x1, =_tx_thread_current_ptr         // Pickup address of current thread
    STR     x0, [x1, #0]                        // Setup current thread pointer

    /* Increment the run count for this thread.  */
    // _tx_thread_current_ptr -> tx_thread_run_count++;

    LDR     w2, [x0, #4]                        // Pickup run counter
    LDR     w3, [x0, #36]                       // Pickup time-slice for this thread
    ADD     w2, w2, #1                          // Increment thread run-counter
    STR     w2, [x0, #4]                        // Store the new run counter

    /* Setup time-slice, if present.  */
    // _tx_timer_time_slice =  _tx_thread_current_ptr -> tx_thread_time_slice;

    LDR     x2, =_tx_timer_time_slice           // Pickup address of time slice
                                                //   variable
    LDR     x4, [x0, #8]                        // Switch stack pointers
    MOV     sp, x4                              //
    STR     w3, [x2, #0]                        // Setup time-slice

#if (defined(TX_ENABLE_EXECUTION_CHANGE_NOTIFY) || defined(TX_EXECUTION_PROFILE_ENABLE))

    /* Call the thread entry function to indicate the thread is executing.  */

    MOV     x19, x0                             // Save x0
    BL      _tx_execution_thread_enter          // Call the thread execution enter function
    MOV     x0, x19                             // Restore x0
#endif

    /* Switch to the thread's stack.  */
    // sp =  _tx_thread_execute_ptr -> tx_thread_stack_ptr;

    /* Determine if an interrupt frame or a synchronous task suspension frame
       is present.  */

    LDP     x4, x5, [sp], #16                   // Pickup saved SPSR/DAIF and ELR_EL1
    CMP     x5, #0                              // Check for synchronous context switch (ELR_EL1 = NULL)
    BEQ     _tx_solicited_return

    MSR     SPSR_EL1, x4                        // Setup SPSR for return
    MSR     ELR_EL1, x5                         // Setup point of interrupt

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
    LDP     x0, x1,   [sp], #16                 // Pickup FPSR, FPCR
    MSR     FPSR, x0                            // Recover FPSR
    MSR     FPCR, x1                            // Recover FPCR
    LDP     q30, q31, [sp], #32                 // Recover q30, q31
    LDP     q28, q29, [sp], #32                 // Recover q28, q29
    LDP     q26, q27, [sp], #32                 // Recover q26, q27
    LDP     q24, q25, [sp], #32                 // Recover q24, q25
    LDP     q22, q23, [sp], #32                 // Recover q22, q23
    LDP     q20, q21, [sp], #32                 // Recover q20, q21
    LDP     q18, q19, [sp], #32                 // Recover q18, q19
    LDP     q16, q17, [sp], #32                 // Recover q16, q17
    LDP     q14, q15, [sp], #32                 // Recover q14, q15
    LDP     q12, q13, [sp], #32                 // Recover q12, q13
    LDP     q10, q11, [sp], #32                 // Recover q10, q11
    LDP     q8,  q9,  [sp], #32                 // Recover q8, q9
    LDP     q6,  q7,  [sp], #32                 // Recover q6, q7
    LDP     q4,  q5,  [sp], #32                 // Recover q4, q5
    LDP     q2,  q3,  [sp], #32                 // Recover q2, q3
    LDP     q0,  q1,  [sp], #32                 // Recover q0, q1
#endif // #if !defined(__SOFT_FP__) && defined(__ARM_FP)

    LDP     x28, x29, [sp], #16                 // Recover x28
    LDP     x26, x27, [sp], #16                 // Recover x26, x27
    LDP     x24, x25, [sp], #16                 // Recover x24, x25
    LDP     x22, x23, [sp], #16                 // Recover x22, x23
    LDP     x20, x21, [sp], #16                 // Recover x20, x21
    LDP     x18, x19, [sp], #16                 // Recover x18, x19
    LDP     x16, x17, [sp], #16                 // Recover x16, x17
    LDP     x14, x15, [sp], #16                 // Recover x14, x15
    LDP     x12, x13, [sp], #16                 // Recover x12, x13
    LDP     x10, x11, [sp], #16                 // Recover x10, x11
    LDP     x8,  x9,  [sp], #16                 // Recover x8, x9
    LDP     x6,  x7,  [sp], #16                 // Recover x6, x7
    LDP     x4,  x5,  [sp], #16                 // Recover x4, x5
    LDP     x2,  x3,  [sp], #16                 // Recover x2, x3
    LDP     x0,  x1,  [sp], #16                 // Recover x0, x1
    LDP     x29, x30, [sp], #16                 // Recover x29, x30
    ERET                                        // Return to point of interrupt

_tx_solicited_return:

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
    LDP     x0, x1,   [sp], #16                 // Pickup FPSR, FPCR
    MSR     FPSR, x0                            // Recover FPSR
    MSR     FPCR, x1                            // Recover FPCR
    LDP     q14, q15, [sp], #32                 // Recover q14, q15
    LDP     q12, q13, [sp], #32                 // Recover q12, q13
    LDP     q10, q11, [sp], #32                 // Recover q10, q11
    LDP     q8,  q9,  [sp], #32                 // Recover q8, q9
#endif // #if !defined(__SOFT_FP__) && defined(__ARM_FP)

    LDP     x27, x28, [sp], #16                 // Recover x27, x28
    LDP     x25, x26, [sp], #16                 // Recover x25, x26
    LDP     x23, x24, [sp], #16                 // Recover x23, x24
    LDP     x21, x22, [sp], #16                 // Recover x21, x22
    LDP     x19, x20, [sp], #16                 // Recover x19, x20
    LDP     x29, x30, [sp], #16                 // Recover x29, x30
    MSR     DAIF, x4                            // Recover DAIF
    RET                                         // Return to caller
// }

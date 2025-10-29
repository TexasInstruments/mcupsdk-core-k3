/*
 * Copyright (c) 2015-2025, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <tx_api.h>

#include <HwiP_c75.h>
#include <TaskSupport_threadx_c75.h>

#include <tx_timer.h>
#include <tx_thread.h>


VOID _tx_initialize_low_level(VOID)
{
    Hwi_switchFromBootStack();
}

void Task_enter(void)
{
    Hwi_enable();
}

VOID _tx_thread_stack_build(TX_THREAD *thread_ptr, VOID (*function_ptr)(VOID))
{
    void *sp_ptr;

    sp_ptr = TaskSupport_setupTaskStack(thread_ptr->tx_thread_stack_end,
                                        thread_ptr->tx_thread_stack_start,
                                        function_ptr,
                                        NULL,
                                        Task_enter,
                                        1u);

    thread_ptr->tx_thread_stack_ptr = sp_ptr;

    return;
}

extern TX_THREAD *_tx_thread_execute_ptr;
extern TX_THREAD *_tx_thread_current_ptr;


VOID _tx_thread_schedule(VOID)
{
    volatile TX_THREAD *thread_ptr_v;
    TX_THREAD *thread_ptr;
    void **next_thread_stk_ptr;
    void *dummy_thread_stk_ptr;
    void **old_stk_ptr;

    Hwi_enable();

    do {
        thread_ptr_v = (volatile TX_THREAD *)_tx_thread_execute_ptr;
        thread_ptr = (TX_THREAD *)thread_ptr_v;
    } while((volatile TX_THREAD *)_tx_thread_execute_ptr == NULL);

    Hwi_disable();

    thread_ptr_v = (volatile TX_THREAD *)_tx_thread_execute_ptr;
    thread_ptr = (TX_THREAD *)thread_ptr_v;

    next_thread_stk_ptr = &thread_ptr->tx_thread_stack_ptr;
    if(_tx_thread_current_ptr != NULL) {
        old_stk_ptr = &_tx_thread_current_ptr->tx_thread_stack_ptr;
    } else {
        old_stk_ptr = &dummy_thread_stk_ptr;
    }

    _tx_thread_current_ptr = thread_ptr;

    if(old_stk_ptr != next_thread_stk_ptr) {
        TaskSupport_swap(old_stk_ptr, next_thread_stk_ptr);
    }

    Hwi_enable();
}

VOID _tx_thread_switch_from_isr(VOID)
{
    volatile TX_THREAD *thread_ptr_v;
    TX_THREAD *thread_ptr;
    void **next_thread_stk_ptr;
    void *dummy_thread_stk_ptr;
    void **old_stk_ptr;

    thread_ptr_v = (volatile TX_THREAD *)_tx_thread_execute_ptr;
    thread_ptr = (TX_THREAD *)thread_ptr_v;

    next_thread_stk_ptr = &thread_ptr->tx_thread_stack_ptr;
    if(_tx_thread_current_ptr != NULL) {
        old_stk_ptr = &_tx_thread_current_ptr->tx_thread_stack_ptr;
    } else {
        old_stk_ptr = &dummy_thread_stk_ptr;
    }

    _tx_thread_current_ptr = thread_ptr;

    if(old_stk_ptr != next_thread_stk_ptr) {
        TaskSupport_swap(old_stk_ptr, next_thread_stk_ptr);
    } else {
        for(;;) {}
    }

}

VOID _tx_thread_system_return(VOID)
{
    Hwi_disable();

    _tx_thread_schedule();
}


VOID   _tx_timer_interrupt(VOID)
{

    /* Increment system clock. */
    _tx_timer_system_clock++;

    /* Test for time-slice expiration. */
    if (_tx_timer_time_slice)
    {
        /* Decrement the time_slice.  */
        _tx_timer_time_slice--;

        /* Check for expiration.  */
        if (_tx_timer_time_slice == 0)
        {

           /* Set the time-slice expired flag.  */
           _tx_timer_expired_time_slice =  TX_TRUE;
        }
    }

    /* Test for timer expiration.  */
    if (*_tx_timer_current_ptr)
    {

        /* Set expiration flag.  */
        _tx_timer_expired =  TX_TRUE;
    }
    else
    {

        /* No timer expired, increment the timer pointer.  */
        _tx_timer_current_ptr++;

        /* Check for wrap-around.  */
        if (_tx_timer_current_ptr == _tx_timer_list_end)
        {

            /* Wrap to beginning of list.  */
            _tx_timer_current_ptr =  _tx_timer_list_start;
        }
    }

    /* See if anything has expired.  */
    if ((_tx_timer_expired_time_slice) || (_tx_timer_expired))
    {

        /* Did a timer expire?  */
        if (_tx_timer_expired)
        {

            /* Process timer expiration.  */
            _tx_timer_expiration_process();
        }

        /* Did time slice expire?  */
        if (_tx_timer_expired_time_slice)
        {

            /* Time slice interrupted thread.  */
            _tx_thread_time_slice();
        }
    }
}



/* below are set in linker command file */
extern uint32_t __BSS_START;
extern uint32_t __BSS_END;

/*****************************************************************************/
/* _SYSTEM_PRE_INIT() - _system_pre_init() is called in the C/C++ startup    */
/* routine (_c_int00()) and provides a mechanism for the user to             */
/* insert application specific low level initialization instructions prior   */
/* to calling main().  The return value of _system_pre_init() is used to     */
/* determine whether or not C/C++ global data initialization will be         */
/* performed (return value of 0 to bypass C/C++ auto-initialization).        */
/*                                                                           */
/* PLEASE NOTE THAT BYPASSING THE C/C++ AUTO-INITIALIZATION ROUTINE MAY      */
/* RESULT IN PROGRAM FAILURE.                                                */
/*                                                                           */
/* The version of _system_pre_init() below is skeletal and is provided to    */
/* illustrate the interface and provide default behavior.  To replace this   */
/* version rewrite the routine and include it as part of the current project.*/
/* The linker will include the updated version if it is linked in prior to   */
/* linking with the C/C++ runtime library.                                   */
/*****************************************************************************/

int _system_pre_init(void)
{
    /* initialize .bss to zero */
    uint32_t bss_size = ((uintptr_t)&__BSS_END - (uintptr_t)&__BSS_START);
    memset((void*)&__BSS_START, 0x00, bss_size);

    return 1;
}

/*****************************************************************************/
/* _SYSTEM_POST_CINIT() - _system_post_cinit() is a hook function called in  */
/* the C/C++ auto-initialization function after cinit() and before pinit().  */
/*                                                                           */
/* The version of _system_post_cinit() below is skeletal and is provided to  */
/* illustrate the interface and provide default behavior.  To replace this   */
/* version rewrite the routine and include it as part of the current project.*/
/* The linker will include the updated version if it is linked in prior to   */
/* linking with the C/C++ runtime library.                                   */
/*****************************************************************************/


void _system_post_cinit(void)
{
    extern void c7x_startup_init(void);
    c7x_startup_init();
}

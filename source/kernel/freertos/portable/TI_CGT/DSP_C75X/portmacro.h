/*
 * FreeRTOS Kernel V11.1.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 * 1 tab == 4 spaces!
 */
/*
 *  Copyright (C) 2018-2023 Texas Instruments Incorporated
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
#ifndef PORTMACRO_H
    #define PORTMACRO_H

    #ifdef __cplusplus
        extern "C" {
    #endif

#include <stdint.h>
#include <c7x.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/nortos/dpl/c75/IntrinsicsSupport_c75.h>
#include <kernel/nortos/dpl/c75/HwiP_c75.h>

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
    #define portCHAR         char
    #define portFLOAT        float
    #define portDOUBLE       double
    #define portLONG         long
    #define portSHORT        short
    #define portSTACK_TYPE   uint64_t
    #define portBASE_TYPE    long
    #define portPOINTER_SIZE_TYPE uintptr_t

    typedef portSTACK_TYPE   StackType_t;
    typedef long             BaseType_t;
    typedef unsigned long    UBaseType_t;

    typedef uint32_t         TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL

/* Hardware specifics. */
    #define portARCH_NAME         "TI-C7X"
    #define portSTACK_GROWTH      ( -1 )
    #define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
    #define portBYTE_ALIGNMENT    16
    #define portHAS_STACK_OVERFLOW_CHECKING    1
    #define portCRITICAL_NESTING_IN_TCB        1

/* Task switch utilities. */
    extern void vPortYeildFromISR( uint32_t x );
    extern void vPortYield(void);
    extern void vPortYieldAsyncFromISR( void );
    extern void Hwi_refreshNLC( void );
    #define portYIELD_FROM_ISR( x )    vPortYeildFromISR( x )
    #define portEND_SWITCHING_ISR( x ) vPortYeildFromISR( x )
    #define portYIELD()                vPortYield();
    void vPortAssertIfInISR();
    #define portASSERT_IF_IN_ISR()    vPortAssertIfInISR()
    #define vPortRefreshNLC()         Hwi_refreshNLC()


/* Critical section control */
    extern void vTaskEnterCritical( void );
    extern void vTaskExitCritical( void );

    extern unsigned int Hwi_disable(void);
    extern unsigned int Hwi_enable(void);

    #define portENTER_CRITICAL()                      vTaskEnterCritical()
    #define portEXIT_CRITICAL()                       vTaskExitCritical()
    #define portDISABLE_INTERRUPTS()                  Hwi_disable()
    #define portENABLE_INTERRUPTS()                   Hwi_enable()
    #define portSET_INTERRUPT_MASK_FROM_ISR()         HwiP_disable()
    #define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    HwiP_restore( x )

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
    #define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    void vFunction( void * pvParameters )
    #define portTASK_FUNCTION( vFunction, pvParameters )          void vFunction( void * pvParameters )

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
    extern void vPortTaskUsesFPU( void );
    #define portTASK_USES_FLOATING_POINT()    vPortTaskUsesFPU()

    #if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
        /* Store/clear the ready priorities in a bit map. */
        #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
        #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

        #define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities )    uxTopPriority = IntrinsicsSupport_maxbit(uxReadyPriorities)

    #endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Architecture specific optimisations. */
    #ifdef configASSERT
        void vPortValidateInterruptPriority( void );
        #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
    #endif /* configASSERT */

    extern BaseType_t xPortInIsrContext(void);

    #define portMEMORY_BARRIER()    IntrinsicsSupport_mfence()

/* Required by the kernel aware debugger. */
    /* #define portREMOVE_STATIC_QUALIFIER */

    void vPortConfigTimerForRunTimeStats();
    #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vPortConfigTimerForRunTimeStats()

    uint32_t uiPortGetRunTimeCounterValue();
    #define portGET_RUN_TIME_COUNTER_VALUE()        uiPortGetRunTimeCounterValue()

    #ifndef portINLINE
        #define portINLINE   __inline
    #endif

    #ifdef __cplusplus
        } /* extern C */
    #endif


#endif /* PORTMACRO_H */

/*
 * FreeRTOS Kernel V10.4.1
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
 *  Copyright (C) 2018-2021 Texas Instruments Incorporated
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
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <c7x.h>    /* for C7x intrinsics */
#include <FreeRTOS.h>
#include <task.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/TimerP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/nortos/dpl/c75/HwiP_c75.h>
#include <kernel/nortos/dpl/c75/CycleCounterP_c75.h>
#include <kernel/nortos/dpl/c75/TaskSupport_c75.h>
#include <kernel/nortos/dpl/c75/CacheP_c75.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/freertos/dpl/common/ClockP_freertos_priv.h>
#include <kernel/nortos/dpl/c75/csl_clec.h>

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case is messes up unwinding of the stack in the
 * debugger. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#else
    #define portTASK_RETURN_ADDRESS    prvTaskExitError
#endif


/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#define portNO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#define portNO_FLOATING_POINT_CONTEXT    ( ( StackType_t ) 0 )

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
volatile uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
uint32_t ulPortTaskHasFPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ulPortYieldRequired = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ulPortInterruptNesting = 0UL;

/* set to true when schedular gets enabled in xPortStartScheduler */
uint32_t ulPortSchedularRunning = pdFALSE;


/* set to true when scheduler gets enabled in xPortStartScheduler */
uint32_t uxPortIncorrectYieldCount = 0UL;

/* below are set in linker command file */
extern uint32_t __BSS_START;
extern uint32_t __BSS_END;

/*
 * Task control block.  A task control block (TCB) is allocated for each task,
 * and stores task state information, including a pointer to the task's context
 * (the task's run time environment, including register values)
 */
/*
 * Task control block.  A task control block (TCB) is allocated for each task,
 * and stores task state information, including a pointer to the task's context
 * (the task's run time environment, including register values)
 */
typedef struct tskTaskControlBlock       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
{
    volatile StackType_t * pxTopOfStack; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

    #if ( portUSING_MPU_WRAPPERS == 1 )
        xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
    #endif

    ListItem_t xStateListItem;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
    ListItem_t xEventListItem;                  /*< Used to reference a task from an event list. */
    UBaseType_t uxPriority;                     /*< The priority of the task.  0 is the lowest priority. */
    StackType_t * pxStack;                      /*< Points to the start of the stack. */
    char pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

    #if ( ( portSTACK_GROWTH > 0 ) || ( configRECORD_STACK_HIGH_ADDRESS == 1 ) )
        StackType_t * pxEndOfStack; /*< Points to the highest valid address for the stack. */
    #endif

    #if ( portCRITICAL_NESTING_IN_TCB == 1 )
        UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
    #endif

    #if ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
        UBaseType_t uxTaskNumber; /*< Stores a number specifically for use by third party trace code. */
    #endif

    #if ( configUSE_MUTEXES == 1 )
        UBaseType_t uxBasePriority; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
        UBaseType_t uxMutexesHeld;
    #endif

    #if ( configUSE_APPLICATION_TASK_TAG == 1 )
        TaskHookFunction_t pxTaskTag;
    #endif

    #if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS > 0 )
        void * pvThreadLocalStoragePointers[ configNUM_THREAD_LOCAL_STORAGE_POINTERS ];
    #endif

    #if ( configGENERATE_RUN_TIME_STATS == 1 )
        uint32_t ulRunTimeCounter; /*< Stores the amount of time the task has spent in the Running state. */
    #endif

    #if ( configUSE_NEWLIB_REENTRANT == 1 )

        /* Allocate a Newlib reent structure that is specific to this task.
         * Note Newlib support has been included by popular demand, but is not
         * used by the FreeRTOS maintainers themselves.  FreeRTOS is not
         * responsible for resulting newlib operation.  User must be familiar with
         * newlib and must provide system-wide implementations of the necessary
         * stubs. Be warned that (at the time of writing) the current newlib design
         * implements a system-wide malloc() that must be provided with locks.
         *
         * See the third party link http://www.nadler.com/embedded/newlibAndFreeRTOS.html
         * for additional information. */
        struct  _reent xNewLib_reent;
    #endif

    #if ( configUSE_TASK_NOTIFICATIONS == 1 )
        volatile uint32_t ulNotifiedValue[ configTASK_NOTIFICATION_ARRAY_ENTRIES ];
        volatile uint8_t ucNotifyState[ configTASK_NOTIFICATION_ARRAY_ENTRIES ];
    #endif

    /* See the comments in FreeRTOS.h with the definition of
     * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
    #if ( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
        uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
    #endif

    #if ( INCLUDE_xTaskAbortDelay == 1 )
        uint8_t ucDelayAborted;
    #endif

    #if ( configUSE_POSIX_ERRNO == 1 )
        int iTaskErrno;
    #endif
} tskTCB;

extern  tskTCB * volatile pxCurrentTCB;
/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
extern void vPortRestoreTaskContext( void );

static void prvTaskExitError( void )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    DebugP_assert(0);
}



/*
 *  ======== Task_exit ========
 */
void Task_exit(void)
{
    prvTaskExitError();
}

void Task_enter(void)
{
    portENABLE_INTERRUPTS();
}

void ti_sysbios_knl_Task_Func(uint32_t arg1, uint32_t arg2)
{
    TaskFunction_t pxCode = (TaskFunction_t)arg2;
    pxCode((void *)arg1);
}

#if ( portHAS_STACK_OVERFLOW_CHECKING != 1 )
#error "portHAS_STACK_OVERFLOW_CHECKING should be enabled for c7x"
#endif

#if ( portUSING_MPU_WRAPPERS == 1 )
StackType_t *pxPortInitialiseStack(StackType_t * pxTopOfStack, StackType_t * pxEndOfStack, TaskFunction_t pxCode, void * pvParameters , bool privileged)
#else
StackType_t *pxPortInitialiseStack(StackType_t * pxTopOfStack, StackType_t * pxEndOfStack, TaskFunction_t pxCode, void * pvParameters )
#endif
{
#if ( portUSING_MPU_WRAPPERS != 1 )
    /* TODO this should be a parameter */
    bool privileged = true;
#endif
    pxTopOfStack = (StackType_t *)TaskSupport_setupTaskStack(pxTopOfStack, pxEndOfStack, ti_sysbios_knl_Task_Func, Task_exit, Task_enter, pxCode, pvParameters, privileged);

    return pxTopOfStack;
}



#define configTIMER_ID                                                    (2)
#define configTIMER_INT_NUM                                               (10)
#define CLEC_OFFSET                                                       (256u)
#define portCOMPUTE_CLUSTER_CLEC_RTMAP                                    (CSL_CLEC_RTMAP_CPU_ALL)

static uint32_t gTimerBaseAddress = CSL_TIMER2_CFG_BASE;

#define C7X_LOG_TIMER_INT_DELTA (1)

#if (C7X_LOG_TIMER_INT_DELTA == 1)
uint64_t gTscISRLog[1024];
uint64_t gTscISRLogIdx = 0;
#endif

HwiP_Object timerHwiPObj;

static void prvPortInitTickTimer(void)
{
    TimerP_Params timerParams;
    /* These MUST not be 0 */
    DebugP_assert( gClockConfig.timerInputPreScaler != 0);
    DebugP_assert( gClockConfig.timerInputClkHz != 0);
    DebugP_assert( gClockConfig.usecPerTick != 0);
    DebugP_assert( gClockConfig.timerBaseAddr != 0);

    /* init internal data structure */
    gClockCtrl.ticks = 0;
    gClockCtrl.usecPerTick = gClockConfig.usecPerTick;
    gClockCtrl.timerBaseAddr = gClockConfig.timerBaseAddr;

    /* Check if tick period set in FreeRTOS config matches the value that is passed to this function
     * A mistmatch will affect when pdMS_TO_TICKS to calculate delays
     */
    if( pdMS_TO_TICKS( 1000 ) != ClockP_usecToTicks( 1000000 ) )
    {
        DebugP_logWarn("FreeRTOS configTICK_RATE_HZ (%d), does not match ClockP tick rate Hz (%d)\r\n",
            configTICK_RATE_HZ,
            1000000U / gClockConfig.usecPerTick
            );
    }

    HwiP_Params timerHwiParams;

    TimerP_Params_init(&timerParams);
    timerParams.inputPreScaler    = 1;
    timerParams.inputClkHz        = 25000000;
    timerParams.periodInUsec      = portTICK_PERIOD_MS * 1000;
    timerParams.oneshotMode       = 0;
    timerParams.enableOverflowInt = 1;
    TimerP_setup(gTimerBaseAddress, &timerParams);

    /* setup ISR and enable it */
    HwiP_Params_init(&timerHwiParams);
    timerHwiParams.intNum = configTIMER_INT_NUM;
    timerHwiParams.eventId = CLEC_OFFSET + CSLR_C7X256V0_CLEC_GIC_SPI_TIMER2_INTR_PEND_0;
    timerHwiParams.callback = ClockP_timerTickIsr;
    timerHwiParams.isPulse = 1;
    HwiP_construct(&timerHwiPObj, &timerHwiParams);


}

static void prvPortStartTickTimer(void)
{
#if 0
    TimerP_Status status = TimerP_OK;
    status = TimerP_start(pTickTimerHandle);

    /* don't expect the handle to be null */
    DebugP_assert (status == TimerP_OK);
#else
    TimerP_start(gTimerBaseAddress);
#endif

}

BaseType_t xPortStartScheduler(void)
{
    /* Interrupts are turned off in the CPU itself to ensure tick does
     * not execute	while the scheduler is being started.  Interrupts are
     * automatically turned back on in the CPU when the first task starts
     * executing.
     */
    portDISABLE_INTERRUPTS();

    prvPortInitTickTimer();
    Hwi_switchFromBootStack();

    /* Start the ISR handling of the timer that generates the tick ISR. */
    prvPortStartTickTimer();
    ulPortSchedularRunning = pdTRUE;

    /* Start the first task executing. */
    vPortRestoreTaskContext();

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( void ) prvTaskExitError;

    return pdTRUE;
}

void vPortYeildFromISR( uint32_t xSwitchRequired )
{
    if( xSwitchRequired != pdFALSE )
    {
        ulPortYieldRequired = pdTRUE;
    }
}

void vPortTimerTickHandler()
{
    if( ulPortSchedularRunning == pdTRUE )
    {
        /* Increment the RTOS tick. */
        if( xTaskIncrementTick() != pdFALSE )
        {
            ulPortYieldRequired = pdTRUE;
        }
    }
}

void vPortTaskUsesFPU( void )
{
    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ulPortTaskHasFPUContext = pdTRUE;

}


/* initialize high resolution timer for CPU and task load calculation */
void vPortConfigTimerForRunTimeStats()
{

    /* we assume clock is initialized before the schedular is started */
    CycleCounterP_Module_startup();
}

/* return current counter value of high speed counter in units of 10's of usecs */
uint32_t uiPortGetRunTimeCounterValue()
{
// #if 1
    uint64_t ts = __TSC;
    uint64_t timeInUsecs;

    timeInUsecs = (ts * 1000000) / (850 * 1000 * 1000);
    /* note, there is no overflow protection for this 32b value in FreeRTOS
     *
     * Dividing by 10 to reduce the resolution and avoid overflow for longer duration
     * This will overflow after
     * ((0x100000000/1000000)/(60*60))*10 hours ~ 12 hrs
     */
// #else
//     uint64_t timeInUsecs = ClockP_getTimeUsec();
// #endif
    return (uint32_t)timeInUsecs;
}

/* This is used to make sure we are using the FreeRTOS API from within a valid interrupt priority level
 * In our R%F port this means IRQ.
 * i.e FreeRTOS API should not be called from FIQ, however right now we dont enforce it by checking
 * if we are in FIQ when this API is called.
 */
void vPortValidateInterruptPriority()
{
}

/* This is called as part of vTaskEndScheduler(), in our port, there is nothing to do here.
 * interrupt are disabled by FreeRTOS before calling this.
 */
void vPortEndScheduler()
{
    /* nothing to do */
}

/* configCHECK_FOR_STACK_OVERFLOW is set to 1, so the application must provide an
 * implementation of vApplicationStackOverflowHook()
 */
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char * pcTaskName )
{
    DebugP_log("[FreeRTOS] Stack overflow detected for task [%s]", (uintptr_t)pcTaskName);
    DebugP_assert(0);
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task.
 */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
 * function then they must be declared static – otherwise they will be allocated on
 * the stack and so not exists after this function exits.
 */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ (32 * 1024) ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task’s
     * state will be stored.
     */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task’s stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes.
     */
    *pulIdleTaskStackSize = sizeof(uxIdleTaskStack)/sizeof(uxIdleTaskStack[0]);
}

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
 * application must provide an implementation of vApplicationGetTimerTaskMemory()
 * to provide the memory that is used by the Timer service task.
 */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
 * function then they must be declared static – otherwise they will be allocated on
 * the stack and so not exists after this function exits.
 */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ (32 * 1024) ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
     * task's state will be stored.
     */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task’s stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configTIMER_TASK_STACK_DEPTH is specified in words, not bytes.
     */
    *pulTimerTaskStackSize = sizeof(uxTimerTaskStack)/sizeof(uxTimerTaskStack[0]);
}




void vPortRestoreTaskContext()
{
    void * dummyTaskSp;

    TaskSupport_swap( &dummyTaskSp,  (void **)(&pxCurrentTCB->pxTopOfStack));
}

void vPortYield( void )
{
    void **oldSP;
    void **newSP;

    portDISABLE_INTERRUPTS();
    oldSP = ( void ** )( &pxCurrentTCB->pxTopOfStack );
    vTaskSwitchContext();
    newSP = ( void ** )( &pxCurrentTCB->pxTopOfStack );
    /* We should not be swapping from one task back to same task. Indicates bug in invocation of vPortYield */
    if(oldSP != newSP)
    {
        TaskSupport_swap( oldSP, newSP );
    }
    else
    {
        //DebugP_log("Doing switch to same task:%p",(uintptr_t)oldSP);
        uxPortIncorrectYieldCount++;
    }
    if (pxCurrentTCB->uxCriticalNesting == 0)
    {
        /* Enable interrupts if task was preempted outside critical section */
        portENABLE_INTERRUPTS();
    }
}

void vPortYieldAsyncFromISR( void )
{
    void **oldSP;
    void **newSP;

    oldSP = ( void ** )( &pxCurrentTCB->pxTopOfStack );
    vTaskSwitchContext();
    newSP = ( void ** )( &pxCurrentTCB->pxTopOfStack );
    /* We should not be swapping from one task back to same task. Indicates bug in invocation of vPortYieldAsyncFromISR */
    //DebugP_assert(oldSP != newSP);
    if(oldSP != newSP)
    {
        TaskSupport_swap( oldSP, newSP );
    }
    else
    {
        //DebugP_log("Doing switch to same task:%p",(uintptr_t)oldSP);
        uxPortIncorrectYieldCount++;
    }
    /* Interrupts should be disabled in case of async yield from ISR */
    /* Enable interrupts if task was preempted outside critical section */
    portDISABLE_INTERRUPTS();

}

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
BaseType_t xPortInIsrContext()
{
    BaseType_t inISR = false;
    if (ulPortInterruptNesting != 0)
    {
        inISR =  true;
    }
    return inISR;
}

void vPortAssertIfInISR()
{
    if( xPortInIsrContext() )
    {
        DebugP_log( "port_interruptNesting\n\n");
    }

    configASSERT( !xPortInIsrContext() );
}


/* This function is called when configUSE_IDLE_HOOK is 1 in FreeRTOSConfig.h */
void vApplicationIdleHook( void )
{
    void vApplicationLoadHook();

    vApplicationLoadHook();
}

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

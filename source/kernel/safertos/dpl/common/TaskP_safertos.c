/*
 *  Copyright (C) 2018-2026 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/ClockP.h>
#include <SafeRTOS_API.h>
#include <taskAPI.h>
#include <SafeRTOSConfigs.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TaskP_LOAD_CPU_LOAD_SCALE   (10000U)
#define TaskP_REGISTRY_MAX_ENTRIES  (16U)
#define TaskP_STACK_SIZE_MIN        (128U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

#if ( configINCLUDE_RUNTIMESTATS == 1 )
#include "runtimestatsAPI.h"

/* RTS structs for all the tasks. */
static xRTS xIdleTaskRTS = { 0 };
#endif /* ( configINCLUDE_RUNTIMESTATS == 1 ) */

typedef struct TaskP_Struct_ {
    xTCB taskObj;
    portTaskHandleType taskHndl;
    uint32_t     lastRunTime;
    uint64_t     accRunTime;
} TaskP_Struct;

typedef struct {
    TaskP_Struct *taskRegistry[TaskP_REGISTRY_MAX_ENTRIES];
    uint32_t lastTotalTime;
    uint64_t accTotalTime;
    uint32_t idleTskLastRunTime;
    uint64_t idleTskAccRunTime;
} TaskP_Ctrl;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

TaskP_Ctrl gTaskP_ctrl;

/* Declare the stack for the Idle task. */
portInt8Type acIdleTaskStack[ configIDLE_TASK_STACK_SIZE ] __attribute__( ( aligned( configIDLE_TASK_STACK_SIZE ) ) ) = { 0 };

/* Declare the stack for the timer task. */
portInt8Type acTimerTaskStack[ configTIMER_TASK_STACK_SIZE ] __attribute__( ( aligned( configTIMER_TASK_STACK_SIZE ) ) ) = { 0 };

/* The buffer for the timer command queue. */
portInt8Type acTimerCommandQueueBuffer[ configTIMER_CMD_QUEUE_BUFFER_SIZE ] __attribute__( ( aligned( safertosapiWORD_ALIGNMENT ) ) ) = { 0 };

/* The structure passed to xTaskInitializeScheduler() to configure the kernel
 * with the application defined constants and call back functions.
 * This is defined as weak so that application can override this definition.
 */
__attribute__((weak)) const xPORT_INIT_PARAMETERS xPortInit =
{
    configSYSTICK_CLOCK_HZ,                 /* ulTimerClockHz */
    configTICK_RATE_HZ,                     /* ulTickRateHz */
#if defined (BUILD_C7X)
    0,            /* uxYieldInterruptNumber */
#endif

    /* Hook Functions */
    NULL,                                   /* pvSvcHookFunction */

    /* System Stack parameters */
    configSTACK_CHECK_MARGIN,               /* uxAdditionalStackCheckMarginBytes */

    /* Idle Task parameters */
    acIdleTaskStack,                        /* pcIdleTaskStackBuffer */
    configIDLE_TASK_STACK_SIZE,             /* uxIdleTaskStackSizeBytes */

#if defined (BUILD_MCU)
    pdTRUE,                                 /* xIdleTaskUsingFPU */
    /* xIdleTaskMPUParameters */
    {
        mpuUNPRIVILEGED_TASK,               /* The idle hook will be executed in unprivileged mode. */
        {
            { NULL, 0U, 0U, 0U },
            { NULL, 0U, 0U, 0U }
        }
    },
#endif

#if ( configINCLUDE_RUNTIMESTATS == 1 )
    &xIdleTaskRTS,                          /* RTS struct passed in as pvIdleTaskTLSObject */
#else /* ( configINCLUDE_RUNTIMESTATS == 1 ) */
    NULL,                                   /* pvIdleTaskTLSObject */
#endif /* ( configINCLUDE_RUNTIMESTATS == 1 ) */
    "IdleTask",                             /* pcIdleTaskName */
    /* Timer feature initialisation parameters */
    configTIMER_TASK_PRIORITY,              /* uxTimerTaskPriority */
    configTIMER_TASK_STACK_SIZE,            /* uxTimerTaskStackSize */
    acTimerTaskStack,                       /* pcTimerTaskStackBuffer */
    "KernelTimerTask",                      /* pcTimerTaskName */
    configTIMER_QUEUE_LENGTH,               /* uxTimerCommandQueueLength */
    configTIMER_CMD_QUEUE_BUFFER_SIZE,      /* uxTimerCommandQueueBufferSize */
    acTimerCommandQueueBuffer,              /* pcTimerCommandQueueBuffer */
#if defined (BUILD_MCU)
    pdFALSE                                 /* xEnableCache */
#endif
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void TaskP_addToRegistry(TaskP_Struct *task)
{
    uint32_t i;
    portBaseType isStarted;

    isStarted = xTaskIsSchedulerStarted();
    if(isStarted == pdTRUE)
    {
        vTaskSuspendScheduler();
    }

    for(i=0; i<TaskP_REGISTRY_MAX_ENTRIES; i++)
    {
        if(gTaskP_ctrl.taskRegistry[i]==NULL)
        {
            gTaskP_ctrl.taskRegistry[i] = task;
            break;
        }
    }

    if(isStarted == pdTRUE)
    {
        xTaskResumeScheduler();
    }
}

static void TaskP_removeFromRegistry(TaskP_Struct *task)
{
    uint32_t i;
    portBaseType isStarted;

    isStarted = xTaskIsSchedulerStarted();
    if(isStarted == pdTRUE)
    {
        vTaskSuspendScheduler();
    }

    for(i=0; i<TaskP_REGISTRY_MAX_ENTRIES; i++)
    {
        if(gTaskP_ctrl.taskRegistry[i]==task)
        {
            gTaskP_ctrl.taskRegistry[i] = NULL;
            break;
        }
    }

    if(isStarted == pdTRUE)
    {
        xTaskResumeScheduler();
    }
}

void TaskP_Params_init(TaskP_Params *params)
{
    params->name = "Task (DPL)";
    params->stackSize = 0;
    params->stack = NULL;
    params->priority = (TaskP_PRIORITY_HIGHEST - TaskP_PRIORITY_LOWEST) / 2;
    params->args = NULL;
    params->taskMain = NULL;
#if defined(BUILD_MCU)
    params->taskPrivilege = mpuPRIVILEGED_TASK;
#else
    params->taskPrivilege = 0;
#endif
}

int32_t TaskP_construct(TaskP_Object *obj, TaskP_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    TaskP_Struct *taskObj = (TaskP_Struct *)obj;
    portBaseType xCreateResult;

    DebugP_assert(sizeof(TaskP_Struct) <= sizeof(TaskP_Object));
    DebugP_assert(params != NULL);
    DebugP_assert(taskObj != NULL);
    DebugP_assert(params->stackSize >= TaskP_STACK_SIZE_MIN);
    DebugP_assert( (params->stackSize & (sizeof(portStackType) - 1)) == 0);
    DebugP_assert(params->stack != NULL );
    DebugP_assert( ((uintptr_t)params->stack & (sizeof(portStackType) - 1)) == 0);
    DebugP_assert(params->taskMain != NULL );

    /* if prority is out of range, adjust to bring it in range */
    if(params->priority > TaskP_PRIORITY_HIGHEST)
    {
        params->priority = TaskP_PRIORITY_HIGHEST;
    }
    if(params->priority <= TaskP_PRIORITY_LOWEST)
    {
        params->priority = TaskP_PRIORITY_LOWEST;
    }

    taskObj->lastRunTime = 0;
    taskObj->accRunTime = 0;

    TaskP_addToRegistry(taskObj);

    xTaskParameters xTaskPParams =
    {
        params->taskMain,
        params->name,
        &taskObj->taskObj,
        (portInt8Type *) params->stack,
        params->stackSize,
        params->args,
        params->priority,
        NULL,
#if defined(BUILD_MCU)
        pdFALSE,                            /* Task does not use the FPU by default. */
        {                                   /* MPU task parameters. */
            params->taskPrivilege,          /* Check task is privileged. */
            {
                { NULL, 0U, 0U, 0U },       /* No additional region definitions are required. */
                { NULL, 0U, 0U, 0U },
            }
        }
#endif
    };

    xTaskPParams.pvTaskCode         = params->taskMain;
    xTaskPParams.pcTaskName         = params->name;
    xTaskPParams.pxTCB              = &taskObj->taskObj;
    xTaskPParams.pcStackBuffer      = (portInt8Type *) params->stack;
    xTaskPParams.uxStackDepthBytes  = params->stackSize;
    xTaskPParams.pvParameters       = params->args;
    xTaskPParams.uxPriority         = params->priority;
    xTaskPParams.pvObject           = NULL;  /* Thread Local Storage not used. */

    xCreateResult = xTaskCreate(&xTaskPParams, &taskObj->taskHndl);
    if((xCreateResult != pdPASS) || (taskObj->taskHndl == NULL))
    {
        status = SystemP_FAILURE;
    }
    return status;
}

void TaskP_destruct(TaskP_Object *obj)
{
    TaskP_Struct *taskObj = (TaskP_Struct *)obj;

    if(taskObj && taskObj->taskHndl)
    {
        xTaskDelete(taskObj->taskHndl);
        taskObj->taskHndl = NULL;
    }
    if(taskObj)
    {
        TaskP_removeFromRegistry(taskObj);
    }
}

void* TaskP_getHndl(TaskP_Object *obj)
{
    TaskP_Struct *taskObj = (TaskP_Struct *)obj;

    return (void*)taskObj->taskHndl;
}

void TaskP_yield(void)
{
    safertosapiYIELD();
}

void TaskP_exit(void)
{
    xTaskDelete(NULL);
}

/* This is required for runtime load calculation, which SafeRTOS does not support. */
void TaskP_loadGet(TaskP_Object *obj, TaskP_Load *taskLoad)
{
    /* Not implemented in SafeRTOS */
}

/* This is required for runtime load calculation, which SafeRTOS does not support. */
uint32_t TaskP_loadGetTotalCpuLoad(void)
{
    uint32_t cpuLoad = 0;

    return cpuLoad;
}

/* This is required for runtime load calculation, which SafeRTOS does not support. */
void TaskP_loadResetAll(void)
{
    /* Not implemented in SafeRTOS */
}

/* This is required for runtime load calculation, which SafeRTOS does not support. */
void TaskP_loadUpdateAll(void)
{
    /* Not implemented in SafeRTOS */
}

/* This is required for runtime load calculation, which SafeRTOS does not support. */
void vApplicationLoadHook(void)
{
    /* Not implemented in SafeRTOS */
}

void vApplicationErrorHook( portTaskHandleType xHandleOfTaskWithError,
                            portBaseType xErrorCode )
{
    /* The parameters are not used, these lines prevent compiler warnings. */
    ( void ) xHandleOfTaskWithError;
    ( void ) xErrorCode;

    /* Will only get here if an internal kernel error occurs. */
    DebugP_assert(pdFALSE);
}

void TaskP_endScheduler(void)
{
    extern void vTaskSuspendScheduler(void);
    vTaskSuspendScheduler();
}
uint32_t TaskP_disable(void)
{
    vTaskSuspendScheduler();
    return (uint32_t)0;
}
void TaskP_restore(uint32_t key)
{
    xTaskResumeScheduler();
    return;
}

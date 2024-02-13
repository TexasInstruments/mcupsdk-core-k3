/*
 *  Copyright (C) 2020-2021 Texas Instruments Incorporated
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
 *
 */

/**
 *  \file sciserver_tirtos.c
 *
 *  \brief Example Library functions for an application including Sciserver
 *         This file is only for TIRTOS based applications.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* BIOS Header files
// #include <ti/osal/osal.h>
// #include <ti/osal/SemaphoreP.h>
// #include <ti/osal/TaskP.h>
// #include <ti/osal/RegisterIntr.h>
*/

#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>

#include <stdint.h>
#include <string.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/device_manager/sciserver.h>
#include <drivers/device_manager/sciserver_tirtos.h>

#include <lib/strncpy.h>

#include <sciserver_hwiData.h>
#include "sciserver_secproxyTransfer.h"
//#include <ti/drv/sciclient/examples/common/sciclient_appCommon.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Macro to determine the size of an array */
#define SCISERVER_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#if !defined(MCU_PLUS_SDK)
void Sciserver_tirtosUserMsgHwiFxn(uintptr_t arg);
#else
void Sciserver_tirtosUserMsgHwiFxn(void* arg);
#endif
void Sciserver_tirtosUnRegisterIntr(void);
void Sciserver_tirtosDeinit(void);
#if !defined(MCU_PLUS_SDK)
void Sciserver_tirtosUserMsgTask(void* arg0, void* arg1);
#else
void Sciserver_tirtosUserMsgTask(void* arg0);
#endif

static int32_t Sciserver_tirtosInitHwis(void);
static int32_t Sciserver_tirtosInitSemaphores(void);
static int32_t Sciserver_tirtosInitUserTasks(Sciserver_TirtosCfgPrms_t *pPrms);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if !defined(MCU_PLUS_SDK)
HwiP_Handle gSciserverHwiHandles[SCISERVER_HWI_NUM];

SemaphoreP_Params gSciserverUserSemParams[SCISERVER_SEMAPHORE_MAX_CNT];
SemaphoreP_Handle gSciserverUserSemHandles[SCISERVER_SEMAPHORE_MAX_CNT];
SemaphoreP_Params gSciserverSyncParam;
SemaphoreP_Handle gSciserverSyncHandle;

TaskP_Handle gSciserverUserTaskHandles[SCISERVER_TASK_MAX_CNT];
TaskP_Params gSciserverUserTaskParams[SCISERVER_TASK_MAX_CNT];
#else
HwiP_Object gSciserverHwiObjects[SCISERVER_HWI_NUM];
HwiP_Object* gSciserverHwiHandles[SCISERVER_HWI_NUM];

SemaphoreP_Object gSciserverUserSemObjects[SCISERVER_SEMAPHORE_MAX_CNT];
SemaphoreP_Object* gSciserverUserSemHandles[SCISERVER_SEMAPHORE_MAX_CNT];

SemaphoreP_Object gSciserverSyncObject;
SemaphoreP_Object* gSciserverSyncHandle;

TaskP_Object gSciserverUserTaskObjects[SCISERVER_TASK_MAX_CNT];
TaskP_Object* gSciserverUserTaskHandles[SCISERVER_TASK_MAX_CNT];
TaskP_Params gSciserverUserTaskParams[SCISERVER_TASK_MAX_CNT];
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Sciserver_tirtosInit(Sciserver_TirtosCfgPrms_t *pAppPrms)
{
    Sciserver_CfgPrms_t prms;
    int32_t ret = CSL_PASS;

    if (pAppPrms == NULL)
    {
        ret = CSL_EBADARGS;
    }

    /* Initialize the Init Parameters for the Sciserver */
    if (ret == CSL_PASS)
    {
        ret = Sciserver_initPrms_Init(&prms);
    }
    /* Initialize the Sciserver */
    if (ret == CSL_PASS)
    {
        ret = Sciserver_init(&prms);
    }

    /* Create a semaphore for the Sciserver Task */
    if (ret == CSL_PASS)
    {
        ret = Sciserver_tirtosInitSemaphores();
    }

    /* user task initialization */
    if (ret == CSL_PASS) {
        ret = Sciserver_tirtosInitUserTasks(pAppPrms);
    }

    /* hwi initialization */
    if (ret == CSL_PASS) {
        ret = Sciserver_tirtosInitHwis();
    }

    /* Set the process State */
    if (ret == CSL_PASS)
    {
        Sciserver_setCtrlState(SCISERVER_PROCESS_STATE_RUN);
        if (Sciserver_getCtrlState() != SCISERVER_PROCESS_STATE_RUN)
        {
            ret = CSL_EFAIL;
        }
    }

    return ret;
}

#if !defined(MCU_PLUS_SDK)
void Sciserver_tirtosUserMsgHwiFxn(uintptr_t arg)
#else
void Sciserver_tirtosUserMsgHwiFxn(void* arg)
#endif
{
    Sciserver_hwiData *uhd = (Sciserver_hwiData *)   arg;
    int32_t ret = CSL_PASS;
    bool soft_error = false;
#if !defined(MCU_PLUS_SDK)
    Osal_DisableInterrupt(0, (int32_t) uhd->irq_num);
#else
    HwiP_disableInt( (uint32_t) uhd->irq_num);
#endif
    ret = Sciserver_interruptHandler(uhd, &soft_error);

    if ((ret != CSL_PASS) && (soft_error == true))
    {
#if !defined(MCU_PLUS_SDK)
        Osal_EnableInterrupt(0, (int32_t) uhd->irq_num);
#else
        HwiP_enableInt( (uint32_t) uhd->irq_num);
#endif        
    }
    else
    {
        (void) SemaphoreP_post(gSciserverUserSemHandles[uhd->semaphore_id]);
    }

#if !defined(MCU_PLUS_SDK)
        Osal_ClearInterrupt(0, (int32_t) uhd->irq_num);
#else
        HwiP_clearInt( (uint32_t) uhd->irq_num);
#endif 

    if ((ret != CSL_PASS) && (soft_error != true)) {
        /* At this point secure proxy is broken so halt */
#if !defined(MCU_PLUS_SDK)        
        OS_stop();
#else
        extern void vTaskEndScheduler( void );
        vTaskEndScheduler();
#endif        
    }
}

void Sciserver_tirtosDisableIntr(void)
{
    uint32_t i = 0U;

    for (i = 0U; i < SCISERVER_ARRAY_SIZE(sciserver_hwi_list); i++) {
        if (gSciserverHwiHandles[i] != NULL)
        {
#if !defined(MCU_PLUS_SDK)
            Osal_DisableInterrupt(0, sciserver_hwi_list[i].irq_num);
#else
            HwiP_disableInt(sciserver_hwi_list[i].irq_num);
#endif            
        }
    }
}

void Sciserver_tirtosEnableIntr(void)
{
    uint32_t i = 0U;

    for (i = 0U; i < SCISERVER_ARRAY_SIZE(sciserver_hwi_list); i++) {
        if (gSciserverHwiHandles[i] != NULL)
        {
#if !defined(MCU_PLUS_SDK)
            Osal_EnableInterrupt(0, sciserver_hwi_list[i].irq_num);
#else
            HwiP_enableInt(sciserver_hwi_list[i].irq_num);
#endif
        }
    }
}


void Sciserver_tirtosUnRegisterIntr(void)
{
    uint32_t i = 0U;

    for (i = 0U; i < SCISERVER_ARRAY_SIZE(sciserver_hwi_list); i++) {
        if (gSciserverHwiHandles[i] != NULL)
        {
#if !defined(MCU_PLUS_SDK)
            Osal_DeleteInterrupt(gSciserverHwiHandles[i],
                                 sciserver_hwi_list[i].irq_num);
#else
            (void) HwiP_destruct(gSciserverHwiHandles[i]);
#endif                        
            gSciserverHwiHandles[i] = NULL_PTR;
        }
    }
}

void Sciserver_tirtosDeinit(void)
{
    uint32_t i = 0U;

    for (i = 0U; i < (uint32_t) SCISERVER_SEMAPHORE_MAX_CNT; i++) {
#if !defined(MCU_PLUS_SDK)
        SemaphoreP_delete(gSciserverUserSemHandles[i]);
#else
        SemaphoreP_destruct(gSciserverUserSemHandles[i]);
#endif
    }
    Sciserver_deinit();
    Sciserver_tirtosUnRegisterIntr();
}

#if !defined (MCU_PLUS_SDK)
void Sciserver_tirtosUserMsgTask(void *arg0, void* arg1)
#else
void Sciserver_tirtosUserMsgTask(void* arg0)
#endif
{
    int32_t ret;
    volatile bool loopForever = true;
    Sciserver_taskData *utd = (Sciserver_taskData *) arg0;

#if !defined (MCU_PLUS_SDK)
    /* To suppress unused variable warning */
    (void)arg1;
#endif

    /* Set the pending State first */
    utd->state->state = SCISERVER_TASK_PENDING;

    while(loopForever)
    {
#if !defined (MCU_PLUS_SDK)        
        SemaphoreP_pend(gSciserverUserSemHandles[utd->semaphore_id],
                        SemaphoreP_WAIT_FOREVER);
#else
        SemaphoreP_pend(gSciserverUserSemHandles[utd->semaphore_id],
                        SystemP_WAIT_FOREVER);
#endif
        SemaphoreP_pend(gSciserverSyncHandle, SCICLIENT_SERVICE_WAIT_FOREVER);

        ret = Sciserver_processtask (utd);

        SemaphoreP_post(gSciserverSyncHandle);

        if (ret != CSL_PASS)
        {
            /* Failed to process message and failed to send nak response */
#if !defined(MCU_PLUS_SDK)        
            OS_stop();
#else
            extern void vTaskEndScheduler( void );
            vTaskEndScheduler();
#endif 
        }
        else
        {
            /*
             * This is a bit of a hack... using the task ID to pick the offset
             * for the gloabl interrupt data array. This is functional but can
             * be cleaned up.
             */
#if !defined(MCU_PLUS_SDK)
        Osal_EnableInterrupt(0, sciserver_hwi_list[2U * utd->task_id +
                utd->state->current_buffer_idx].irq_num);
#else
        HwiP_enableInt(sciserver_hwi_list[(2U * (uint32_t) utd->task_id) +
                utd->state->current_buffer_idx].irq_num);
#endif              
        }
    }
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static int32_t Sciserver_tirtosInitSemaphores(void)
{
    int32_t ret = CSL_PASS;
    uint32_t i = 0U;

    for (i = 0U; i < (uint32_t) SCISERVER_SEMAPHORE_MAX_CNT; i++) {
#if !defined(MCU_PLUS_SDK)        
        SemaphoreP_Params_init(&gSciserverUserSemParams[i]);
        gSciserverUserSemHandles[i] = SemaphoreP_create(0U, &gSciserverUserSemParams[i]);

        if (gSciserverUserSemHandles[i] == NULL) {
            ret = CSL_EFAIL;
            break;
        }
#else
        gSciserverUserSemHandles[i] = &gSciserverUserSemObjects[i];
        if (SemaphoreP_constructCounting(gSciserverUserSemHandles[i], 0u, 0xFF) != SystemP_SUCCESS)
        {
            gSciserverUserSemHandles[i] = NULL;
            ret = CSL_EFAIL;
            break;
        }
#endif
    }

    if (ret == CSL_PASS) {
#if !defined(MCU_PLUS_SDK)         
        SemaphoreP_Params_init(&gSciserverSyncParam);
        gSciserverSyncHandle = SemaphoreP_create(1U, &gSciserverSyncParam);

        if (gSciserverSyncHandle == NULL) {
            ret = CSL_EFAIL;
        }
#else
        gSciserverSyncHandle = &gSciserverSyncObject;
        if (SemaphoreP_constructCounting(gSciserverSyncHandle, 1u, 0xFF) != SystemP_SUCCESS)
        {
            gSciserverSyncHandle = NULL;
            ret = CSL_EFAIL;
        }
#endif        
    }

    return ret;
}

static int32_t Sciserver_tirtosInitHwis(void)
{
    uint32_t i = 0U;
    int32_t ret = CSL_PASS;

    for (i = 0U; i < SCISERVER_ARRAY_SIZE(sciserver_hwi_list); i++) {
#if !defined(MCU_PLUS_SDK)        
        OsalRegisterIntrParams_t    intrPrms;
        Osal_RegisterInterrupt_initParams(&intrPrms);
        intrPrms.corepacConfig.arg  = (uintptr_t) &sciserver_hwi_list[i];
        intrPrms.corepacConfig.isrRoutine = &Sciserver_tirtosUserMsgHwiFxn;
        intrPrms.corepacConfig.enableIntr = FALSE;
        intrPrms.corepacConfig.corepacEventNum  = 0;
        intrPrms.corepacConfig.intVecNum = (int32_t)
            sciserver_hwi_list[i].irq_num;
        /* Register interrupts */
        ret = Osal_RegisterInterrupt(&intrPrms,
                                     &gSciserverHwiHandles[i]);
        if(OSAL_INT_SUCCESS != ret) {
            gSciserverHwiHandles[i] = NULL_PTR;
            break;
        }
#else
        HwiP_Params                hwiInputParams;
        HwiP_Params_init(&hwiInputParams);

        /* Populate the interrupt parameters */
        hwiInputParams.args     = (void*) &sciserver_hwi_list[i];
        hwiInputParams.callback = &Sciserver_tirtosUserMsgHwiFxn;
        hwiInputParams.eventId  = 0;
        hwiInputParams.intNum   = (int32_t) sciserver_hwi_list[i].irq_num;

        /* Register interrupts */
        gSciserverHwiHandles[i]= &gSciserverHwiObjects[i];
        ret =  HwiP_construct(gSciserverHwiHandles[i], &hwiInputParams);
        if(SystemP_SUCCESS != ret) {
            gSciserverHwiHandles[i] = NULL_PTR;
            break;
        }        
#endif        
    }

    return ret;
}

static int32_t Sciserver_tirtosInitUserTasks(Sciserver_TirtosCfgPrms_t *pPrms)
{
    uint32_t i = 0U;
    int32_t ret = CSL_PASS;

    for (i = 0U; i < SCISERVER_ARRAY_SIZE(gSciserverTaskList); i++)
    {
        TaskP_Params_init (&gSciserverUserTaskParams[i]);
#if !defined(MCU_PLUS_SDK)        
        gSciserverUserTaskParams[i].priority = pPrms->taskPriority[i];
        gSciserverUserTaskParams[i].stack = gSciserverTaskList[i].stack;
        gSciserverUserTaskParams[i].stacksize = SCISERVER_TASK_STACK_SIZE;
        gSciserverUserTaskParams[i].arg0 = (void *) &gSciserverTaskList[i];
        gSciserverUserTaskHandles[i] =
            TaskP_create((void *)Sciserver_tirtosUserMsgTask, &gSciserverUserTaskParams[i]);
        if(NULL == gSciserverUserTaskHandles[i])
        {
            ret = CSL_EFAIL;
            break;
        }
#else
        gSciserverUserTaskParams[i].priority = pPrms->taskPriority[i];
        gSciserverUserTaskParams[i].stack = gSciserverTaskList[i].stack;
        gSciserverUserTaskParams[i].stackSize = SCISERVER_TASK_STACK_SIZE;
        gSciserverUserTaskParams[i].taskMain = Sciserver_tirtosUserMsgTask; /* Pointer to the function that implements the task. */
        gSciserverUserTaskParams[i].args = (void *) &gSciserverTaskList[i];
        gSciserverUserTaskHandles[i] = &gSciserverUserTaskObjects[i];
        
        if (TaskP_construct(gSciserverUserTaskHandles[i], &gSciserverUserTaskParams[i]) != SystemP_SUCCESS)
        {
            gSciserverUserTaskHandles[i] = NULL;
            ret = CSL_EFAIL;
            break;
        }
#endif        
    }

    return ret;
}


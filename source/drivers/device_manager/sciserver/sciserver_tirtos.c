/*
 *  Copyright (C) 2020-2025 Texas Instruments Incorporated
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

void Sciserver_tirtosUserMsgHwiFxn(void* arg);
void Sciserver_tirtosUnRegisterIntr(void);
void Sciserver_tirtosDeinit(void);
void Sciserver_tirtosUserMsgTask(void* arg0);

static int32_t Sciserver_tirtosInitHwis(void);
static int32_t Sciserver_tirtosInitSemaphores(void);
static int32_t Sciserver_tirtosInitUserTasks(Sciserver_TirtosCfgPrms_t *pPrms);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
HwiP_Object gSciserverHwiObjects[SCISERVER_HWI_NUM];
HwiP_Object* gSciserverHwiHandles[SCISERVER_HWI_NUM];

SemaphoreP_Object gSciserverUserSemObjects[SCISERVER_SEMAPHORE_MAX_CNT];
SemaphoreP_Object* gSciserverUserSemHandles[SCISERVER_SEMAPHORE_MAX_CNT];

SemaphoreP_Object gSciserverSyncObject;
SemaphoreP_Object* gSciserverSyncHandle;

TaskP_Object gSciserverUserTaskObjects[SCISERVER_TASK_MAX_CNT];
TaskP_Object* gSciserverUserTaskHandles[SCISERVER_TASK_MAX_CNT];
TaskP_Params gSciserverUserTaskParams[SCISERVER_TASK_MAX_CNT];

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

#if defined(CONFIG_DM2TIFS_INTERRUPT_MODE)
    /* Update the sciclient to interrupt mode */
    if (ret == CSL_PASS) {
        ret = Sciclient_updateOperModeToInterrupt();
    }
#endif

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

void Sciserver_tirtosUserMsgHwiFxn(void* arg)
{
    Sciserver_hwiData *uhd = (Sciserver_hwiData *)   arg;
    int32_t ret = CSL_PASS;
    bool soft_error = false;
    HwiP_disableInt( (uint32_t) uhd->irq_num);
    ret = Sciserver_interruptHandler(uhd, &soft_error);

    if ((ret != CSL_PASS) && (soft_error == true))
    {
        HwiP_enableInt( (uint32_t) uhd->irq_num);
    }
    else
    {
        (void) SemaphoreP_post(gSciserverUserSemHandles[uhd->semaphore_id]);
    }

        HwiP_clearInt( (uint32_t) uhd->irq_num);

    if ((ret != CSL_PASS) && (soft_error != true)) {
        /* At this point secure proxy is broken so halt */
        extern void TaskP_endScheduler( void );
        TaskP_endScheduler();
    }
}

void Sciserver_tirtosDisableIntr(void)
{
    uint32_t i = 0U;

    for (i = 0U; i < SCISERVER_ARRAY_SIZE(sciserver_hwi_list); i++) {
        if (gSciserverHwiHandles[i] != NULL)
        {
            HwiP_disableInt(sciserver_hwi_list[i].irq_num);
        }
    }
}

void Sciserver_tirtosEnableIntr(void)
{
    uint32_t i = 0U;

    for (i = 0U; i < SCISERVER_ARRAY_SIZE(sciserver_hwi_list); i++) {
        if (gSciserverHwiHandles[i] != NULL)
        {
            HwiP_enableInt(sciserver_hwi_list[i].irq_num);
        }
    }
}


void Sciserver_tirtosUnRegisterIntr(void)
{
    uint32_t i = 0U;

    for (i = 0U; i < SCISERVER_ARRAY_SIZE(sciserver_hwi_list); i++) {
        if (gSciserverHwiHandles[i] != NULL)
        {
            (void) HwiP_destruct(gSciserverHwiHandles[i]);
            gSciserverHwiHandles[i] = NULL_PTR;
        }
    }
}

void Sciserver_tirtosDeinit(void)
{
    uint32_t i = 0U;

    for (i = 0U; i < (uint32_t) SCISERVER_SEMAPHORE_MAX_CNT; i++) {
        SemaphoreP_destruct(gSciserverUserSemHandles[i]);
    }
    Sciserver_deinit();
    Sciserver_tirtosUnRegisterIntr();
}

void Sciserver_tirtosUserMsgTask(void* arg0)
{
    int32_t ret;
    volatile bool loopForever = true;
    Sciserver_taskData *utd = (Sciserver_taskData *) arg0;

    /* Set the pending State first */
    utd->state->state = SCISERVER_TASK_PENDING;

    while(loopForever)
    {
        SemaphoreP_pend(gSciserverUserSemHandles[utd->semaphore_id],
                        SystemP_WAIT_FOREVER);
        SemaphoreP_pend(gSciserverSyncHandle, SCICLIENT_SERVICE_WAIT_FOREVER);

        ret = Sciserver_processtask (utd);

        SemaphoreP_post(gSciserverSyncHandle);

        if (ret != CSL_PASS)
        {
            /* Failed to process message and failed to send nak response */
            extern void TaskP_endScheduler( void );
            TaskP_endScheduler();
        }
        else
        {
            /*
             * Using the task ID to pick the offset
             * for the global interrupt data array
             */
        HwiP_enableInt(sciserver_hwi_list[(2U * (uint32_t) utd->task_id) +
                utd->state->current_buffer_idx].irq_num);
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
        gSciserverUserSemHandles[i] = &gSciserverUserSemObjects[i];
        if (SemaphoreP_constructCounting(gSciserverUserSemHandles[i], 0u, 0xFF) != SystemP_SUCCESS)
        {
            gSciserverUserSemHandles[i] = NULL;
            ret = CSL_EFAIL;
            break;
        }
    }

    if (ret == CSL_PASS) {
        gSciserverSyncHandle = &gSciserverSyncObject;
        if (SemaphoreP_constructCounting(gSciserverSyncHandle, 1u, 0xFF) != SystemP_SUCCESS)
        {
            gSciserverSyncHandle = NULL;
            ret = CSL_EFAIL;
        }
    }

    return ret;
}

static int32_t Sciserver_tirtosInitHwis(void)
{
    uint32_t i = 0U;
    int32_t ret = CSL_PASS;

    for (i = 0U; i < SCISERVER_ARRAY_SIZE(sciserver_hwi_list); i++) {
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
    }

    return ret;
}


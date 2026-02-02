/*
 * Copyright (C) 2025-2026 Texas Instruments Incorporated
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
/*
 *  ======== HwiP_safertos_c7x.c ========
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include <SafeRTOS_API.h>
#include <portmacro.h>
#include <kernel/dpl/HwiP.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/nortos/dpl/c75/csl_clec.h>
#include <kernel/nortos/dpl/c75/HwiP_c75.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DPL_SAFERTOS_C7X_CONFIGNUM_HWI      (64U)

#ifndef NULL_PTR
#define NULL_PTR ((void *)0x0)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct HwiP_safertos_s {
    bool              used;
    HwiC7x_Struct     hwi;
} HwiP_safertos;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * Global pool of statically allocated semaphore pools
 */
static HwiP_safertos gOsalHwiPSafeRtosPool[DPL_SAFERTOS_C7X_CONFIGNUM_HWI];

portBaseType xPortInIsrContext(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t gOsalHwiAllocCnt = 0U, gOsalHwiPeak = 0U;
/* --> axEventVectorTable */
extern void* axEventVectorTable;

/* vectorTableBase__C */
#pragma DATA_SECTION(Hwi_vectorTableBase, ".const:Hwi_vectorTableBase");
extern const void *Hwi_vectorTableBase;
extern void (*soft_reset)(void);
const void * Hwi_vectorTableBase = ((const void *)((void*)&axEventVectorTable));

/* vectorTableBase_SS__C */
#pragma DATA_SECTION(Hwi_vectorTableBase_SS, ".const:Hwi_vectorTableBase_SS");
extern const void * Hwi_vectorTableBase_SS;
const void * Hwi_vectorTableBase_SS = NULL;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t HwiP_construct(HwiP_Object *object, HwiP_Params *params)
{
    HwiP_Struct *obj = (HwiP_Struct *)object;
    HwiP_safertos *handle = (HwiP_safertos *) NULL_PTR;
    Hwi_Params  hwiParams;
    uint32_t          i;
    uintptr_t         key;
    HwiP_safertos      *hwiPool;
    uint32_t          maxHwi;
    int32_t status;
    int iStat;

    DebugP_assertNoLog( sizeof(HwiP_Struct) <= sizeof(HwiP_Object) );
    DebugP_assertNoLog( params->callback != NULL );
    DebugP_assertNoLog( params->intNum < DPL_SAFERTOS_C7X_CONFIGNUM_HWI );

    hwiPool        = (HwiP_safertos *) &gOsalHwiPSafeRtosPool[0];
    maxHwi         = DPL_SAFERTOS_C7X_CONFIGNUM_HWI;

    if(gOsalHwiAllocCnt==0U)
    {
        (void)memset((void *)gOsalHwiPSafeRtosPool,0,sizeof(gOsalHwiPSafeRtosPool));
    }

    /* Grab the memory */
    key = HwiP_disable();

    for (i = 0U; i < maxHwi; i++)
    {
        if (hwiPool[i].used == (bool)false)
        {
            hwiPool[i].used = true;
            /* Update statistics */
            gOsalHwiAllocCnt++;
            if (gOsalHwiAllocCnt > gOsalHwiPeak)
            {
                gOsalHwiPeak = gOsalHwiAllocCnt;
            }
            break;
        }
    }
    HwiP_restore(key);

    if (i < maxHwi)
    {
        /* Grab the memory */
        handle = (HwiP_safertos *) &hwiPool[i];
    }

    if (handle != NULL_PTR)
    {
        status =  HwiP_configClec(params->eventId, params->intNum, params->isPulse);

        if(status == SystemP_SUCCESS)
        {
            Hwi_Params_init(&hwiParams);
            hwiParams.arg = (uintptr_t)(params->args);

            if (params->priority==0U)
            {
               /* A priority of 0 is invalid for many targets. -1 forces
                  sysbios to assign a default priority */
               hwiParams.priority       = -1;
            }
            else
            {
               hwiParams.priority       = (int32_t)params->priority;
            }

            hwiParams.eventId        = (int32_t)params->eventId;
            hwiParams.enableInt      = true;
            hwiParams.maskSetting    = Hwi_MaskingOption_SELF;
            iStat = Hwi_construct(&handle->hwi, params->intNum, (Hwi_FuncPtr)(params->callback), &hwiParams);

            if (iStat != 0)
            {
                /* Free the allocated memory and return null */
                handle->used = false;
                handle = (HwiP_safertos *) NULL_PTR;
            }
        }
    }

    obj->intNum = params->intNum;

    return SystemP_SUCCESS;
}

void HwiP_destruct(HwiP_Object *handle)
{
    HwiP_Struct *obj = (HwiP_Struct *)handle;
    DebugP_assertNoLog( obj->intNum < DPL_SAFERTOS_C7X_CONFIGNUM_HWI );

    uintptr_t   key;

    Hwi_destruct(obj->intNum);
    key = HwiP_disable();
    /* Found the osal hwi object to delete */
    if (gOsalHwiAllocCnt > 0U)
    {
        gOsalHwiAllocCnt--;
    }

    HwiP_restore(key);

    return;
}

uintptr_t HwiP_disable(void)
{
    uintptr_t key = (uintptr_t)NULL_PTR;

    if(( 1 == xPortInIsrContext() ) ||
       ( pdFALSE    == xTaskIsSchedulerStarted() ))
    {
        key = Hwi_disable();
    }
    else
    {
        portENTER_CRITICAL_WITHIN_API();
    }

    return (key);
}

void HwiP_restore(uintptr_t key)
{
    if(( xPortInIsrContext() ) ||
       ( pdFALSE == xTaskIsSchedulerStarted() ))
    {
        (void)Hwi_restore((uint32_t)key);
    }
    else
    {
        portEXIT_CRITICAL_WITHIN_API();
    }

    return;
}

uint32_t HwiP_inISR(void)
{
    uint32_t stat = 0U;

    if (xPortInIsrContext() != 0)
    {
        stat =  1U;
    }
    return stat;
}

/* Dispatch handler for TI MCU+ style interrupts. */
void vApplicationInterruptHandlerHook( portUInt32Type intNum )
{
    /* Call the ISR callback function */
    Hwi_dispatchCore(intNum);
}

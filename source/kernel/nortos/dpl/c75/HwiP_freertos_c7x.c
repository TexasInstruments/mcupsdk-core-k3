/*
 * Copyright (c) 2015-2021, Texas Instruments Incorporated
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
 *  ======== HwiP_freeRtos_c7x.c ========
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>


#include <kernel/dpl/HwiP.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/nortos/dpl/c75/csl_clec.h>
#include "HwiP_c75.h"

#include <FreeRTOS.h>
#include <task.h>

#define OSAL_FREERTOS_C7X_CONFIGNUM_HWI                 (64U)

#ifndef OSAL_TARGET_PROC_MASK_DEFAULT
#define OSAL_TARGET_PROC_MASK_DEFAULT (0xFFFFU)
#endif

#ifndef NULL_PTR
#define NULL_PTR ((void *)0x0)
#endif

#define  HWIP_USE_DEFAULT_PRIORITY   (~((uint8_t)0))

uint32_t  gOsalHwiAllocCnt   = 0U, gOsalHwiPeak = 0U;

typedef struct HwiP_freeRtos_s {
    bool              used;
    HwiC7x_Struct        hwi;
} HwiP_freeRtos;

typedef struct HwiP_Struct_s {

    uint32_t intNum;

} HwiP_Struct;

/* global pool of statically allocated semaphore pools */
static HwiP_freeRtos gOsalHwiPFreeRtosPool[OSAL_FREERTOS_C7X_CONFIGNUM_HWI];

int32_t HwiP_construct(HwiP_Object *object, HwiP_Params *params)
{
    HwiP_Struct *obj = (HwiP_Struct *)object;
    HwiP_freeRtos *handle = (HwiP_freeRtos *) NULL_PTR;
    Hwi_Params  hwiParams;
    uint32_t          i;
    uintptr_t         key;
    HwiP_freeRtos      *hwiPool;
    uint32_t          maxHwi;
    int32_t status;
    int iStat;

    DebugP_assertNoLog( sizeof(HwiP_Struct) <= sizeof(HwiP_Object) );
    DebugP_assertNoLog( params->callback != NULL );
    DebugP_assertNoLog( params->intNum < OSAL_FREERTOS_C7X_CONFIGNUM_HWI );

    hwiPool        = (HwiP_freeRtos *) &gOsalHwiPFreeRtosPool[0];
    maxHwi         = OSAL_FREERTOS_C7X_CONFIGNUM_HWI;

    if(gOsalHwiAllocCnt==0U)
    {
        (void)memset((void *)gOsalHwiPFreeRtosPool,0,sizeof(gOsalHwiPFreeRtosPool));
    }


    /* Grab the memory */
    key = HwiP_disable();

    for (i = 0U; i < maxHwi; i++)
    {
        if (hwiPool[i].used == false)
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
        handle = (HwiP_freeRtos *) &hwiPool[i];
    }

    if (handle != NULL_PTR)
    {
        status =  HwiP_configClec(params->eventId, params->intNum, params->isPulse);

        if(status == SystemP_SUCCESS)
        {
            Hwi_Params_init(&hwiParams);
            hwiParams.arg            = (uintptr_t)(params->args);

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
                handle = (HwiP_freeRtos *) NULL_PTR;
            }
        }
    }

    obj->intNum = params->intNum;

    return SystemP_SUCCESS;
}


void HwiP_destruct(HwiP_Object *handle)
{
    HwiP_Struct *obj = (HwiP_Struct *)handle;
    DebugP_assertNoLog( obj->intNum < OSAL_FREERTOS_C7X_CONFIGNUM_HWI );

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

void HwiP_Params_init(HwiP_Params *params)
{
    params->intNum = 0;
    params->callback = NULL;
    params->args = NULL;
    params->eventId = 0;
    params->priority = HWIP_USE_DEFAULT_PRIORITY;
    params->isFIQ = 0;
    params->isPulse = 1;
}

int32_t HwiP_configClec(uint16_t eventId, uint32_t intNum, uint8_t isPulse)
{
    int32_t status = SystemP_SUCCESS;

    if(eventId == HWIP_INVALID_EVENT_ID)
    {
        return status;
    }
    else
    {
        CSL_ClecEventConfig   cfgClec;
        CSL_CLEC_EVTRegs     *clecBaseAddr = (CSL_CLEC_EVTRegs*)CSL_C7X256V0_CLEC_BASE;

        /* Configure CLEC */
        cfgClec.secureClaimEnable = FALSE;
        cfgClec.evtSendEnable     = TRUE;
        cfgClec.rtMap             = CSL_CLEC_RTMAP_CPU_ALL;
        cfgClec.extEvtNum         = 0;
        cfgClec.c7xEvtNum         = intNum;
        CSL_clecClearEvent(clecBaseAddr, eventId);
        CSL_clecConfigEventLevel(clecBaseAddr, eventId, !(isPulse)); /* configure interrupt as level */
        status = CSL_clecConfigEvent(clecBaseAddr, eventId, &cfgClec);
    }

    return status;

}

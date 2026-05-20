/*
 *  Copyright (C) 2018-2025 Texas Instruments Incorporated
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

#ifndef CLOCKP_SAFERTOS_H
#define CLOCKP_SAFERTOS_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TimerP.h>
#include <SafeRTOS_API.h>
#include <queueAPI.h>
#include <timersAPI.h>
#include <taskAPI.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#ifndef pdMS_TO_TICKS
    #define pdMS_TO_TICKS( xTimeInMs )    ( ( portTickType ) ( ( ( portTickType ) ( xTimeInMs ) * ( portTickType ) configTICK_RATE_HZ ) / ( portTickType ) 1000U ) )
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct ClockP_Control_
{
    volatile uint64_t ticks;
    uint32_t usecPerTick;
    HwiP_Object timerHwiObj;
    uint32_t timerBaseAddr;
    uint32_t timerReloadCount;
    volatile uint32_t schedulerStarted; /* Set to 1U once the SafeRTOS scheduler starts */
} ClockP_Control;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void ClockP_timerClearOverflowInt(uint32_t timerBaseAddr);
uint32_t ClockP_getTimerCount(uint32_t timerBaseAddr);
void ClockP_timerTickIsr(void *args);

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

extern ClockP_Control gClockCtrl;
extern ClockP_Config gClockConfig;

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* CLOCKP_SAFERTOS_H */

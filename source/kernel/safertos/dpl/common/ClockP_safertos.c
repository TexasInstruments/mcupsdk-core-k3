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

/**
 *  \file ClockP_safertos.c
 *
 *  \brief File for ClockP API definition for SafeRTOS.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include "ClockP_safertos_priv.h"
#include "SafeRTOS_API.h"
#include "SafeRTOSConfigs.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct ClockP_Struct_
{
    timerInitParametersType timerParameters;
    timerControlBlockType timerControlBlock;
    timerHandleType timerHndl;
    ClockP_FxnCallback callback;
    void *args;
} ClockP_Struct;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void ClockP_sleepTicks(uint32_t ticks);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

ClockP_Control gClockCtrl;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void ClockP_timerTickIsr(void *args)
{
    void vTaskProcessSystemTickFromISR( void );

    /* increment the systick counter */
    gClockCtrl.ticks++;

    /**
     * Timer starts in System_init() before xTaskStartScheduler(). 
     * guard vTaskProcessSystemTickFromISR() until 
     * vApplicationSetupTickInterruptHook() signals the scheduler is ready.
     * vTaskProcessSystemTickFromISR() requires RTOS internal state
     * initialized by xTaskStartScheduler() - calling it pre-scheduler 
     * corrupts state and causes hangs or faults. 
     */
    if (gClockCtrl.schedulerStarted != 0U)
    {
        vTaskProcessSystemTickFromISR();
    }

    ClockP_timerClearOverflowInt(gClockConfig.timerBaseAddr);
}

void ClockP_timerCallbackFunction( timerHandleType xTimer )
{
    ClockP_Struct *pTimer;

    xTimerGetTimerID(xTimer, (portBaseType *) &pTimer);
    if(pTimer != NULL && pTimer->callback )
    {
        pTimer->callback((ClockP_Object*)pTimer, pTimer->args);
    }
}

int32_t ClockP_construct(ClockP_Object *handle, ClockP_Params *params)
{
    ClockP_Struct *pTimer = (ClockP_Struct*)handle;
    portBaseType uxAutoReload = pdFALSE;
    int32_t status;
    portBaseType xReturn;

    DebugP_assert(sizeof(ClockP_Struct) <= sizeof(ClockP_Object));

    memset(pTimer, 0U, sizeof(ClockP_Struct));
    if(params->period == 0)
    {
        uxAutoReload = pdFALSE;
    }
    else
    {
        /* timeout and period MUST match for auto-reloading to take effect */
        DebugP_assert(params->timeout == params->period);

        uxAutoReload = pdTRUE;
    }

    pTimer->callback = params->callback;
    pTimer->args = params->args;

    pTimer->timerParameters.pcTimerName = params->name;
    pTimer->timerParameters.xTimerPeriodInTicks = params->timeout;
    pTimer->timerParameters.xIsPeriodic = uxAutoReload;
    pTimer->timerParameters.xTimerID = (portBaseType) pTimer;
    pTimer->timerParameters.pxNewTimer = &pTimer->timerControlBlock;
    pTimer->timerParameters.pxCallbackFunction = ClockP_timerCallbackFunction;
    pTimer->timerParameters.pxTimerInstance = NULL;
    xReturn = xTimerCreate(&pTimer->timerParameters, &pTimer->timerHndl);
    if((pTimer->timerHndl==NULL) || (xReturn!=pdPASS))
    {
        status = SystemP_FAILURE;
    }
    else
    {
        if(params->start)
        {
            xTimerStart(pTimer->timerHndl, safertosapiMAX_DELAY);
        }
        status = SystemP_SUCCESS;
    }
    return status;
}

void ClockP_destruct(ClockP_Object *handle)
{
    ClockP_Struct *pTimer = (ClockP_Struct*)handle;

    xTimerDelete(pTimer->timerHndl, safertosapiMAX_DELAY);
}

uint64_t ClockP_usecToTicks(uint64_t usecs)
{
    return usecs / gClockCtrl.usecPerTick;
}

uint64_t ClockP_ticksToUsec(uint32_t ticks)
{
    return ((uint64_t)ticks * gClockCtrl.usecPerTick);
}

uint32_t ClockP_getTicks()
{
    return ((uint32_t)xTaskGetTickCount());
}

uint32_t ClockP_getTimeout(ClockP_Object *handle)
{
    ClockP_Struct *pTimer = (ClockP_Struct*)handle;
    uint32_t value = 0;

    if(xTimerIsTimerActive(pTimer->timerHndl))
    {
        /* Function API xTimerGetExpiryTime missing in SafeRTOS */
    }
    return value;
}

uint32_t ClockP_isActive(ClockP_Object *handle)
{
    ClockP_Struct *pTimer = (ClockP_Struct*)handle;

    return xTimerIsTimerActive(pTimer->timerHndl);
}

void ClockP_Params_init(ClockP_Params *params)
{
    params->start = 0;
    params->timeout = 0;
    params->period = 0;
    params->callback = NULL;
    params->args = NULL;
    params->name = "Clock (DPL)";
}

void ClockP_setTimeout(ClockP_Object *handle, uint32_t timeout)
{
    ClockP_Struct *pTimer = (ClockP_Struct*)handle;

    if(HwiP_inISR())
    {
        xTimerChangePeriodFromISR(pTimer->timerHndl, timeout);
        safertosapiYIELD_FROM_ISR();
    }
    else
    {
        xTimerChangePeriod(pTimer->timerHndl, timeout, safertosapiMAX_DELAY);
    }
}

void ClockP_start(ClockP_Object *handle)
{
    portBaseType xReturn;
    ClockP_Struct *pTimer = (ClockP_Struct*)handle;

    if(HwiP_inISR())
    {
        xReturn = xTimerStartFromISR(pTimer->timerHndl);
        DebugP_assertNoLog(xReturn == pdPASS);
        safertosapiYIELD_FROM_ISR();
    }
    else
    {
        xReturn = xTimerStart(pTimer->timerHndl, safertosapiMAX_DELAY);
        DebugP_assert(xReturn == pdPASS);
    }
}

void ClockP_stop(ClockP_Object *handle)
{
    ClockP_Struct *pTimer = (ClockP_Struct*)handle;

    if(HwiP_inISR())
    {
        xTimerStopFromISR(pTimer->timerHndl);
        safertosapiYIELD_FROM_ISR();
    }
    else
    {
        xTimerStop(pTimer->timerHndl, safertosapiMAX_DELAY);
    }
}

void ClockP_sleep(uint32_t sec)
{
    uint64_t ticks = (uint64_t)sec * 1000000 / (uint64_t)gClockCtrl.usecPerTick;

    ClockP_sleepTicks((uint32_t)ticks);
}

void ClockP_usleep(uint64_t usec)
{
    uint64_t curTime, endTime;
    uint32_t ticksToSleep;

    curTime = ClockP_getTimeUsec();
    endTime = curTime + usec;

    if (usec >= gClockCtrl.usecPerTick) {
        ticksToSleep = usec / gClockCtrl.usecPerTick;
        ClockP_sleepTicks(ticksToSleep);
    }
    else
    {
        curTime = ClockP_getTimeUsec();
        while (curTime < endTime) {
            curTime = ClockP_getTimeUsec();
        }
    }
}

/*
 *  Get the current time in microseconds.
 */
uint64_t ClockP_getTimeUsec()
{
    uint64_t ts;
    uint32_t timerCount;
    uint64_t ticks1;
    uint64_t ticks2;

    do {
        ticks1 = gClockCtrl.ticks;
        timerCount = ClockP_getTimerCount(gClockCtrl.timerBaseAddr);
        ticks2 = gClockCtrl.ticks;
    } while (ticks1 != ticks2);

    /* Get the current time in microseconds */
    ts = ticks2 * (uint64_t)gClockCtrl.usecPerTick
             + (uint64_t) ( /* convert timer count to usecs */
                (uint64_t)(timerCount - gClockCtrl.timerReloadCount)*gClockCtrl.usecPerTick/(0xFFFFFFFFu - gClockCtrl.timerReloadCount)
                );

    return (ts);
}

/*
 *  Sleep for a given number of ClockP ticks.
 */
static void ClockP_sleepTicks(uint32_t ticks)
{
    xTaskDelay(ticks);
}

/*
 *  De-initialize the clock module.
 */
void ClockP_deinit()
{
    /* Stop the tick timer and clear any pending interrupts */
    TimerP_stop(gClockCtrl.timerBaseAddr);
    TimerP_clearOverflowInt(gClockCtrl.timerBaseAddr);

    /* Disable and destroy the HWI of the timer used by clock module */
    HwiP_destruct(&gClockCtrl.timerHwiObj);
}


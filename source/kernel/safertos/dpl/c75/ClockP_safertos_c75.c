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

#include <kernel/safertos/dpl/common/ClockP_safertos_priv.h>
#include <kernel/dpl/TimerP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void ClockP_timerClearOverflowInt(uint32_t timerBaseAddr)
{
    TimerP_clearOverflowInt(timerBaseAddr);
}

uint32_t ClockP_getTimerCount(uint32_t timerBaseAddr)
{
    return TimerP_getCount(timerBaseAddr);
}

void ClockP_init(void)
{
    TimerP_Params timerParams;
    HwiP_Params timerHwiParams;

    /* These MUST not be 0 */
    DebugP_assert( gClockConfig.timerInputPreScaler != 0U);
    DebugP_assert( gClockConfig.timerInputClkHz != 0U);
    DebugP_assert( gClockConfig.usecPerTick != 0U);
    DebugP_assert( gClockConfig.timerBaseAddr != 0U);

    /* init internal data structure */
    gClockCtrl.ticks = 0U;
    gClockCtrl.schedulerStarted = 0U;
    gClockCtrl.usecPerTick = gClockConfig.usecPerTick;
    gClockCtrl.timerBaseAddr = gClockConfig.timerBaseAddr;

    /* setup timer - timer will be started below after ISR is registered */
    TimerP_Params_init(&timerParams);
    timerParams.inputPreScaler    = gClockConfig.timerInputPreScaler;
    timerParams.inputClkHz        = gClockConfig.timerInputClkHz;
    timerParams.periodInUsec      = gClockConfig.usecPerTick;
    timerParams.oneshotMode       = 0U;
    timerParams.enableOverflowInt = 1U;
    TimerP_setup(gClockCtrl.timerBaseAddr, &timerParams);

    /* Get timer reload count, we will use this later to compute current time in usecs */
    gClockCtrl.timerReloadCount = TimerP_getReloadCount(gClockCtrl.timerBaseAddr);

    /* setup ISR and enable it */
    HwiP_Params_init(&timerHwiParams);
    timerHwiParams.intNum = gClockConfig.timerHwiIntNum;
    timerHwiParams.eventId = gClockConfig.eventId;
    timerHwiParams.callback = ClockP_timerTickIsr;
    timerHwiParams.isPulse = 1U;
    HwiP_construct(&gClockCtrl.timerHwiObj, &timerHwiParams);

    /* Start the timer here so that ClockP_getTimeUsec works correctly
     * before the scheduler starts. The ISR uses schedulerStarted to
     * guard vTaskProcessSystemTickFromISR until the scheduler is ready. 
     */
    TimerP_start(gClockCtrl.timerBaseAddr);
}

/* SafeRTOS hook invoked at scheduler startup. The timer is already
 * running from ClockP_init; set schedulerStarted to allow the ISR
 * to begin tick processing.
 */
void vApplicationSetupTickInterruptHook( portUInt32Type ulTimerClockHz,
                                         portUInt32Type ulTickRateHz )
{
    /* Signal the ISR that the scheduler is ready for tick processing */
    gClockCtrl.schedulerStarted = 1U;

#if ( configINCLUDE_RUNTIMESTATS == 1 )
    #include "runtimestats.h"
    vInitialiseRunTimeStatistics();
#endif /* ( configINCLUDE_RUNTIMESTATS == 1 ) */
}

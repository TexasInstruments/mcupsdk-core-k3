/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

/* *
 *  \file   rtc.c
 *
 *  \brief  File containing  RTC Driver APIs implementation for V0.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/rtc.h>
#include <stdint.h>
#include <math.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/soc.h>
#include <kernel/dpl/ClockP.h>
#include <drivers/utils/utils.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define RTC_SECONDS_IN_LEAP_YEAR              (31622400ULL)
#define RTC_SECONDS_IN_YEAR                   (31536000ULL)
#define RTC_SECONDS_IN_DAY                    (86400ULL)
#define RTC_SECONDS_IN_AN_HOUR                (3600ULL)
#define RTC_SECONDS_IN_A_MINUTE               (60ULL)
#define RTC_MONTHS_IN_YEAR                    (12U)
#define RTC_HOURS_IN_A_DAY                    (24U)
#define RTC_MINUTES_IN_HOUR                   (60U)
#define RTC_EPOCH_YEAR                        (1970U)
#define RTC_EPOCH_MONTH                       (1U)
#define RTC_TIMEOUT                           (1000U * 120U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    void                   *lock;
    /* *< Driver lock - to protect across open/close */
    SemaphoreP_Object       lockObj;
    /* *< Driver lock object */
} RTC_DrvObj;

/* Default RTC parameters structure */
const RTC_Params RTC_defaultParams =
{
    1U,                     /* Enable Freeze Mode */
    false,                  /* onOffCallback */
    false,                  /* offOnCallback */
};

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

static uint32_t RTC_getIRQStat(uint32_t baseAddr);
static void RTC_setIRQStatusEnable(uint32_t baseAddr, uint32_t mask);
static void RTC_clearIRQStatusEnable(uint32_t baseAddr, uint32_t mask);
static void RTC_clrIRQStatus(uint32_t baseAddr, uint32_t mask);
static void RTC_enableWriteAccess(uint32_t baseAddr, uint32_t key1, uint32_t key2);
static void RTC_disableWriteAccess(uint32_t baseAddr, uint32_t lock1, uint32_t lock2);
static uint32_t RTC_getPendingStatus(uint32_t baseAddr);
static void RTC_setO32kOsc(uint32_t baseAddr, uint32_t mask);
static void RTC_enableFreezeMode(uint32_t baseAddr, uint32_t mask);
static void RTC_updateSecondCount(uint32_t baseAddr, uint64_t seconds);
static uint64_t RTC_getSecondCount(uint32_t baseAddr);
static void RTC_updateOff_OnCount(uint32_t baseAddr, uint64_t seconds);
static void RTC_updateOn_OffCount(uint32_t baseAddr, uint64_t seconds);
static void RTC_configureStop(uint32_t baseAddr);
static void RTC_configureStart(uint32_t baseAddr);
static void RTC_clearWriteErr(uint32_t baseAddr);
static uint32_t RTC_getScratchRegVal(uint32_t baseAddr, uint32_t index);
static void RTC_setScratchRegVal(uint32_t baseAddr, uint32_t index, uint32_t val);
static void RTC_setCompensation(uint32_t baseAddr, int32_t compVal);
static void RTC_reloadFromBbd(uint32_t baseAddr, uint32_t mask);
static uint32_t RTC_getRtcStopStatus(uint32_t baseAddr);
static uint32_t RTC_isUnlocked(uint32_t baseAddr);
static uint32_t RTC_obsStatus(uint32_t baseAddr);
static void RTC_SyncClock(uint32_t baseAddr);
static int32_t RTC_startRtcTimer(uint32_t baseAddr);
static int32_t RTC_checkPendingStatus(uint32_t baseAddr, uint32_t flag);
static int32_t RTC_checkObsStatus(uint32_t baseAddr, uint32_t flag);
static bool RTC_isLeapYear(uint32_t year);
static uint32_t RTC_getDaysInMonth(uint32_t year, uint32_t month);
static uint64_t RTC_convertTimeToSeconds(const RTC_Time *rtc_time);
static void RTC_convertSecondsToTime(uint64_t seconds, RTC_Time *rtc_time);

/* HWI Function */
static void RTC_hwiFxn(void *arg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Externs */
extern RTC_Config gRTCConfig[];
extern uint32_t gRTCConfigNum;

/* * \brief Driver object */
static RTC_DrvObj gRTCDrvObj =
{
    .lock = NULL,
};

/* ========================================================================== */
/*                       API Function Definitions                             */
/* ========================================================================== */

void RTC_init(void)
{
    RTC_Handle handle;
    uint32_t i;

    /* Call init function for each config */
    for(i = 0; i < gRTCConfigNum; i++)
    {
        handle = &gRTCConfig[i];
        /* Input parameter validation */
        if (handle->object != NULL)
        {
            /* Mark the object as available */
            handle->object->isOpen = (bool)false;
        }
    }
    /* Create driver lock */
    (void)SemaphoreP_constructMutex(&gRTCDrvObj.lockObj);
    gRTCDrvObj.lock = &gRTCDrvObj.lockObj;
}

void RTC_deinit(void)
{
    /* Delete driver lock */
    if(NULL != gRTCDrvObj.lock)
    {
        SemaphoreP_destruct(&gRTCDrvObj.lockObj);
        gRTCDrvObj.lock = NULL;
    }
}

void RTC_paramsInit( RTC_Params *params)
{
    /* Input parameter validation */
    if (params != NULL)
    {
        *params =  RTC_defaultParams;
    }
}

RTC_Handle RTC_open(uint32_t idx, const  RTC_Params *params)
{
    RTC_Handle          handle = NULL;
    RTC_Object          *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;
    int32_t                 status = SystemP_SUCCESS;

    /* Check index */
    if(idx >= gRTCConfigNum)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        handle = ( RTC_Handle)&(gRTCConfig[idx]);
    }

    DebugP_assert(NULL != gRTCDrvObj.lock);
    (void)SemaphoreP_pend(&gRTCDrvObj.lockObj, SystemP_WAIT_FOREVER);

    if(status == SystemP_SUCCESS)
    {
        object = ( RTC_Object*)handle->object;
        DebugP_assert(NULL != object);
        DebugP_assert(NULL != handle->hwAttrs);
        hwAttrs = ( RTC_HwAttrs const *)handle->hwAttrs;
        if(object->isOpen)
        {
            /* Handle already opended */
            status = SystemP_FAILURE;
            handle = NULL;
        }
    }

    if (status == SystemP_SUCCESS)
    {
        /* Mark the handle as being used */
        object->isOpen = (bool)true;
        /* Store the  RTC parameters */
        if (params == NULL)
        {
            /* No params passed in, so use the defaults */
            RTC_paramsInit(&(object->RTC_params));
        }
        else
        {
            /* Copy the params contents */
            object->RTC_params = *params;
        }
    }

    if (status == SystemP_SUCCESS)
    {
        if((RTC_isUnlocked(hwAttrs->baseAddr) & RTC_UNLOCK_MASK) == 0U)
        {
            if(RTC_socErratumi2327Applicable())
            {
                DebugP_logInfo("Erratum i2327: Enabling RTC write access failed within 1 second of boot!\n\r");

                status = SystemP_FAILURE;
            }
            else
            {
                RTC_enableWriteAccess(RTC_BASEADDR, KICK0_UNLOCK_VALUE, KICK1_UNLOCK_VALUE);
            }
        }
        if(status == SystemP_SUCCESS)
        {
            /* Disable Interrupt */
            RTC_clearIRQStatusEnable(hwAttrs->baseAddr, (RTC_TMR_INT_INT0_CLEAR_FLAG | RTC_TMR_INT_INT1_CLEAR_FLAG));

            /* Wait for write pend */
            status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);
        }
        if(status == SystemP_SUCCESS)
        {
            /* Clear Interrupt */
            RTC_clrIRQStatus(hwAttrs->baseAddr, (RTC_TMR_INT_INT0_STATUS_FLAG | RTC_TMR_INT_INT1_STATUS_FLAG ));

            /* Wait for write pend */
            status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);

        }

        if(status == SystemP_SUCCESS)
        {
            /* Wait for clock sync time */
            RTC_SyncClock(hwAttrs->baseAddr);

            if (hwAttrs->enableIntr)
            {
                HwiP_Params hwiPrms;
                /* Initialize with defaults */
                HwiP_Params_init(&hwiPrms);
                /* Populate the interrupt parameters */
                hwiPrms.args = (void *)handle;
                hwiPrms.callback = &RTC_hwiFxn;
                hwiPrms.eventId = hwAttrs->eventId;
                hwiPrms.intNum = hwAttrs->intNum;
                hwiPrms.isPulse = (uint8_t)0U;
                hwiPrms.priority = hwAttrs->intrPriority;
                hwiPrms.isFIQ = (uint8_t)0U;
                /* Register interrupts */
                status = HwiP_construct(&object->hwiObj,&hwiPrms);

            }
        }

        if(status == SystemP_SUCCESS)
        {
            status = SemaphoreP_constructMutex(&object->mutex);
        }

        if(status == SystemP_SUCCESS)
        {
            if((RTC_getRtcStopStatus(hwAttrs->baseAddr) & RTC_SW_OFF_MASK) != 0U)
            {
                status = RTC_startRtcTimer(hwAttrs->baseAddr);
            }
            /* Execute memory barrier instruction */
            Utils_dataAndInstructionBarrier();
        }
        if(status == SystemP_SUCCESS)
        {
            status = RTC_checkPendingStatus(hwAttrs->baseAddr, RD_PEND_MASK);

            /* Reload registers from battery backed domain */
            RTC_reloadFromBbd(hwAttrs->baseAddr, CSL_RTC_SYNCPEND_RELOAD_FROM_BBD_MASK);
        }

        if(status == SystemP_SUCCESS)
        {
            /* Wait for write pend */
            status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);
        }

        if(status == SystemP_SUCCESS)
        {
            /* Wait for falling edge */
            status = RTC_checkObsStatus(hwAttrs->baseAddr, O32K_CLK_OBS_BIT_MASK);

            /* Enable Shadow register sync on 32k clock boundary */
            RTC_setO32kOsc(hwAttrs->baseAddr, O32K_OSC_DEP_EN_MASK);
        }

        if(status == SystemP_SUCCESS)
        {
            status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);

            /* Wait for clock to Sync */
            ClockP_sleep(OSC_LOCK_WAIT);

            /* Enable Freeze mode */
            if(object->RTC_params.isfreezemode == 1U)
            {
                RTC_enableFreezeMode(hwAttrs->baseAddr, RTC_FREEZE_MODE);
            }

        }

        if(status == SystemP_SUCCESS)
        {
            status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);
        }

    }

    /* Close the driver if initialization does not go through */
    if(status != SystemP_SUCCESS)
    {
        RTC_close(handle);
    }

    SemaphoreP_post(&gRTCDrvObj.lockObj);
    return (handle);
}

void RTC_close( RTC_Handle handle)
{
    RTC_Object          *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;

    if(handle != NULL)
    {
        object = ( RTC_Object *)handle->object;
        DebugP_assert(NULL != object);
        hwAttrs = ( RTC_HwAttrs const *)handle->hwAttrs;
        DebugP_assert(NULL != hwAttrs);

        DebugP_assert(NULL != gRTCDrvObj.lock);
        (void)SemaphoreP_pend(&gRTCDrvObj.lockObj, SystemP_WAIT_FOREVER);

        if(!hwAttrs->enableIntr)
        {
            /* Clear all interrupt enable */
            RTC_clearIRQStatusEnable(hwAttrs->baseAddr,
                                        RTC_TMR_INT_INT0_STATUS_FLAG |
                                        RTC_TMR_INT_INT1_STATUS_FLAG);

            /* Clear all pending interrupts */
            RTC_clrIRQStatus(hwAttrs->baseAddr,
                                RTC_TMR_INT_INT0_CLEAR_FLAG  |
                                RTC_TMR_INT_INT1_CLEAR_FLAG);

            RTC_disableWriteAccess(hwAttrs->baseAddr, KICK0_LOCK_VALUE, KICK1_LOCK_VALUE);
        }

        /* Destruct the instance lock */
        (void)SemaphoreP_destruct(&object->mutex);

        SemaphoreP_post(&gRTCDrvObj.lockObj);
    }
}

int32_t RTC_setTime(RTC_Handle handle, const RTC_Time *rtc_time)
{
    RTC_Object *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL) && (rtc_time != NULL))
    {
        object = (RTC_Object*)handle->object;
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        /* Acquire the lock for this particular RTC handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        uint64_t time_in_seconds = RTC_convertTimeToSeconds(rtc_time);

        RTC_updateSecondCount(hwAttrs->baseAddr, time_in_seconds);

        status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);

        /* Release the lock for this particular RTC handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }
    return status;
}

int32_t RTC_getTime(RTC_Handle handle, RTC_Time *rtc_time)
{
    RTC_HwAttrs const   *hwAttrs = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL) && (rtc_time != NULL))
    {
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        uint64_t time_in_seconds = RTC_getSecondCount(hwAttrs->baseAddr);

        RTC_convertSecondsToTime(time_in_seconds, rtc_time);
    }
    else
    {
        status = SystemP_FAILURE;
    }
    return status;
}

int32_t RTC_setOff_OnTimerEvent(RTC_Handle handle, const RTC_Time *rtc_time)
{
    RTC_Object *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL) && (rtc_time != NULL))
    {
        object = (RTC_Object*)handle->object;
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        /* Acquire the lock for this particular RTC handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        uint64_t time_in_seconds = RTC_convertTimeToSeconds(rtc_time);

        RTC_updateOff_OnCount(hwAttrs->baseAddr, time_in_seconds);

        status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);

        if(status == SystemP_SUCCESS)
        {
            /* Enable Interrupt */
            RTC_setIRQStatusEnable(hwAttrs->baseAddr, (RTC_TMR_INT_INT1_SET_FLAG));

            status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);
        }

        /* Release the lock for this particular RTC handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }
    return status;
}

int32_t RTC_setOn_OffTimerEvent(RTC_Handle handle, const RTC_Time *rtc_time)
{
    RTC_Object *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL) && (rtc_time != NULL))
    {
        object = (RTC_Object*)handle->object;
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        /* Acquire the lock for this particular RTC handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        uint64_t time_in_seconds = RTC_convertTimeToSeconds(rtc_time);

        RTC_updateOn_OffCount(hwAttrs->baseAddr, time_in_seconds);

        status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);

        if(status == SystemP_SUCCESS)
        {
            /* Enable interrupt */
            RTC_setIRQStatusEnable(hwAttrs->baseAddr, (RTC_TMR_INT_INT0_SET_FLAG));

            status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);
        }

        /* Release the lock for this particular RTC handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }
    return status;
}

uint32_t RTC_readScratchRegister(RTC_Handle handle, uint32_t scratchIndex)
{
    RTC_HwAttrs const   *hwAttrs = NULL;

    uint32_t scratchRegVal = 0U;

    if(handle != NULL)
    {
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        scratchRegVal = RTC_getScratchRegVal(hwAttrs->baseAddr, scratchIndex);
    }

    return scratchRegVal;
}

int32_t RTC_writeScratchRegister(RTC_Handle handle, uint32_t scratchIndex, uint32_t value)
{
    RTC_Object *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL))
    {
        object = (RTC_Object*)handle->object;
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        /* Acquire the lock for this particular RTC handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        RTC_setScratchRegVal(hwAttrs->baseAddr, scratchIndex, value);

        /* Release the lock for this particular RTC handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }
    return status;
}

RTC_Time RTC_calculateElapsedTime(const RTC_Time *startTime, const RTC_Time *endTime)
{
    RTC_Time elapsedTime;

    elapsedTime.year = endTime->year - startTime->year;
    elapsedTime.month = endTime->month;
    elapsedTime.day = endTime->day;
    elapsedTime.hour = endTime->hour;
    elapsedTime.minute = endTime->minute;
    elapsedTime.second = endTime->second;

    /* Handle seconds underflow */
    if(elapsedTime.second < startTime->second)
    {
        elapsedTime.second += (uint32_t)RTC_SECONDS_IN_A_MINUTE;
        elapsedTime.minute--;
    }
    elapsedTime.second -= startTime->second;

    /* Handle minutes underflow */
    if(elapsedTime.minute < startTime->minute)
    {
        elapsedTime.minute += RTC_MINUTES_IN_HOUR;
        elapsedTime.hour--;
    }
    elapsedTime.minute -= startTime->minute;

    /* Handle hours underflow */
    if(elapsedTime.hour < startTime->hour)
    {
        elapsedTime.hour += RTC_HOURS_IN_A_DAY;
        elapsedTime.day--;
    }
    elapsedTime.hour -= startTime->hour;

    /* Handle day underflow */
    if(elapsedTime.day < startTime->day)
    {
        if(startTime->month == 1U)
        {
            elapsedTime.day += 31U;
        }
        else
        {
            elapsedTime.day += (uint32_t)RTC_getDaysInMonth(startTime->year, startTime->month - 1U);
        }
        elapsedTime.month--;
    }
    elapsedTime.day -= startTime->day;

    /* Handle month underflow */
    if(elapsedTime.month < startTime->month)
    {
        elapsedTime.month += RTC_MONTHS_IN_YEAR;
        elapsedTime.year--;
    }
    elapsedTime.month -= startTime->month;

    return elapsedTime;
}

int32_t RTC_adjustForDrift(RTC_Handle handle, Float32 measuredDriftInSeconds)
{
    RTC_Object *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL))
    {
        object = (RTC_Object*)handle->object;
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        /* Acquire the lock for this particular RTC handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        Float32 comp = ((measuredDriftInSeconds) * (Float32)(OSCILLATOR_FREQ_HZ));

        int32_t compensationValue = (int32_t)lroundf(comp);

        RTC_setCompensation(hwAttrs->baseAddr, compensationValue);

        status = RTC_checkPendingStatus(hwAttrs->baseAddr, WR_PEND_MASK);

        /* Release the lock for this particular RTC handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }
    return status;
}

int32_t RTC_stop(RTC_Handle handle)
{
    RTC_Object *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL))
    {
        object = (RTC_Object*)handle->object;
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        /* Acquire the lock for this particular RTC handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        RTC_configureStop(hwAttrs->baseAddr);

        /* Release the lock for this particular RTC handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }
    return status;
}

int32_t RTC_start(RTC_Handle handle)
{
    RTC_Object *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;
    int32_t status = SystemP_SUCCESS;

    if((handle != NULL))
    {
        object = (RTC_Object*)handle->object;
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        /* Acquire the lock for this particular RTC handle */
        (void)SemaphoreP_pend(&object->mutex, SystemP_WAIT_FOREVER);

        status = RTC_startRtcTimer(hwAttrs->baseAddr);

        /* Release the lock for this particular RTC handle */
        (void)SemaphoreP_post(&object->mutex);
    }
    else
    {
        status = SystemP_FAILURE;
    }
    return status;
}

void RTC_erratumi2327Init(void)
{
    /*
	 * If counter has gone past 1, nothing we can do, leave
	 * system locked! This is the only way we know if RTC
	 * can be used for all practical purposes.
	 */
    uint64_t counter = RTC_getSecondCount(RTC_BASEADDR);

    /* Enable write access to RTC */
    if((RTC_isUnlocked(RTC_BASEADDR) & RTC_UNLOCK_MASK) == 0U)
    {
       /*
        * Need to set this up at the very start
        * MUST BE DONE under 1 second of boot.
        */
        if(counter < 1ULL)
        {
            RTC_enableWriteAccess(RTC_BASEADDR, KICK0_UNLOCK_VALUE, KICK1_UNLOCK_VALUE);
        }
        else
        {
            DebugP_logInfo("Erratum i2327: Enabling RTC write access failed within 1 second of boot!\n\r");
        }
    }
    return;
}

/* ========================================================================== */
/*                     API ISR Function Definitions                           */
/* ========================================================================== */
/* HWI Function */
static void RTC_hwiFxn(void *arg)
{
    RTC_Handle          handle = (RTC_Handle)arg;
    RTC_Object          *object = NULL;
    RTC_HwAttrs const   *hwAttrs = NULL;
    uint32_t                isrRegVal = 0U;

    /* Input parameter validation */
    if (handle != NULL)
    {
        /* Get the pointer to the object */
        object = (RTC_Object *)handle->object;
        hwAttrs = (RTC_HwAttrs const *)handle->hwAttrs;

        RTC_SyncClock(hwAttrs->baseAddr);

        while((RTC_getPendingStatus(hwAttrs->baseAddr) & RD_PEND_MASK) != 0U){}

        isrRegVal = RTC_getIRQStat(hwAttrs->baseAddr);
        while((RTC_getPendingStatus(hwAttrs->baseAddr) & RD_PEND_MASK) != 0U){}

        if((isrRegVal & RTC_TMR_INT_INT0_STATUS_FLAG) != 0U)
        {
            object->On_OffCallbackFunction(handle);

            RTC_clrIRQStatus(hwAttrs->baseAddr,
                                   RTC_TMR_INT_INT0_STATUS_FLAG);
            while((RTC_getPendingStatus(hwAttrs->baseAddr) & WR_PEND_MASK) != 0U){}
        }

        if((isrRegVal & RTC_TMR_INT_INT1_STATUS_FLAG) != 0U)
        {
            object->Off_OnCallbackFunction(handle);

            RTC_clrIRQStatus(hwAttrs->baseAddr,
                                   RTC_TMR_INT_INT1_STATUS_FLAG);
            while((RTC_getPendingStatus(hwAttrs->baseAddr) & WR_PEND_MASK) != 0U){}
        }

        RTC_reloadFromBbd(hwAttrs->baseAddr, CSL_RTC_SYNCPEND_RELOAD_FROM_BBD_MASK);

        while((RTC_getPendingStatus(hwAttrs->baseAddr) & RD_PEND_MASK) != 0U){}

        RTC_SyncClock(hwAttrs->baseAddr);

        /* Disable Interrupt */
        RTC_clearIRQStatusEnable(hwAttrs->baseAddr, (RTC_TMR_INT_INT0_STATUS_FLAG | RTC_TMR_INT_INT1_STATUS_FLAG));

        /* Wait for write sync */
        while((RTC_getPendingStatus(hwAttrs->baseAddr) & WR_PEND_MASK) != 0U){}
    }

    return;
}

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

static uint32_t RTC_getIRQStat(uint32_t baseAddr)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_IRQSTATUS_SYS));
    return *addr;
}

static void RTC_setIRQStatusEnable(uint32_t baseAddr, uint32_t mask)
{
    volatile uint32_t *addr =
                    (volatile uint32_t *)(baseAddr + (CSL_RTC_IRQENABLE_SET_SYS));
    *addr |= mask;
}

static void RTC_clearIRQStatusEnable(uint32_t baseAddr, uint32_t mask)
{
    volatile uint32_t *addr =
                    (volatile uint32_t *)(baseAddr + (CSL_RTC_IRQENABLE_CLR_SYS));
    *addr |= mask;
}

static void RTC_clrIRQStatus(uint32_t baseAddr, uint32_t mask)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_IRQSTATUS_SYS));
    *addr |= mask;
}

static void RTC_enableWriteAccess(uint32_t baseAddr, uint32_t key1, uint32_t key2)
{
    /* set unlock value in kick0 */
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_KICK0));
    *addr = key1;

    /* set unlock value in kick1 */
    addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_KICK1));
    *addr = key2;
}

static void RTC_disableWriteAccess(uint32_t baseAddr, uint32_t lock1, uint32_t lock2)
{
    /* set lock value in kick0 */
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_KICK0));
    *addr = lock1;

    /* set lock value in kick1 */
    addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_KICK1));
    *addr = lock2;
}

static uint32_t RTC_getPendingStatus(uint32_t baseAddr)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_SYNCPEND));
    return *addr;
}

static void RTC_setO32kOsc(uint32_t baseAddr, uint32_t mask)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_GENRAL_CTL));
    *addr |= mask;
}

static void RTC_enableFreezeMode(uint32_t baseAddr, uint32_t mask)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_GENRAL_CTL));
    *addr |= mask;
}

static void RTC_updateSecondCount(uint32_t baseAddr, uint64_t seconds)
{
    /* set LSW */
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_S_CNT_LSW));
    *addr = (uint32_t)(seconds & (CSL_RTC_S_CNT_LSW_VAL_MASK));

    /* set MSW */
    addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_S_CNT_MSW));
    *addr = (uint32_t)((seconds >> 32U) & (CSL_RTC_S_CNT_MSW_VAL_MASK));
}

static uint64_t RTC_getSecondCount(uint32_t baseAddr)
{
    /* get LSW */
    volatile uint32_t *addr1 = (volatile uint32_t *)(baseAddr + (CSL_RTC_S_CNT_LSW));
    /* get MSW */
    volatile uint32_t *addr2 = (volatile uint32_t *)(baseAddr + (CSL_RTC_S_CNT_MSW));

    uint32_t lsw = *addr1;
    uint32_t msw = *addr2;

    return (((uint64_t)msw << 32U) | (uint64_t)lsw);
}

static void RTC_updateOff_OnCount(uint32_t baseAddr, uint64_t seconds)
{
    /* set LSW */
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_OFF_ON_S_CNT_LSW));
    *addr = (uint32_t)(seconds & (CSL_RTC_OFF_ON_S_CNT_LSW_VAL_MASK));

    /* set MSW */
    addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_OFF_ON_S_CNT_MSW));
    *addr = (uint32_t)((seconds >> 32U) & (CSL_RTC_OFF_ON_S_CNT_MSW_VAL_MASK));
}

static void RTC_updateOn_OffCount(uint32_t baseAddr, uint64_t seconds)
{
    /* set LSW */
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_ON_OFF_S_CNT_LSW));
    *addr = (uint32_t)(seconds & (CSL_RTC_ON_OFF_S_CNT_LSW_VAL_MASK));

    /* set MSW */
    addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_ON_OFF_S_CNT_MSW));
    *addr = (uint32_t)((seconds >> 32U) & (CSL_RTC_ON_OFF_S_CNT_MSW_VAL_MASK));
}

static void RTC_configureStop(uint32_t baseAddr)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_GENRAL_CTL));
    *addr |= (CSL_RTC_GENRAL_CTL_SW_OFF_MASK);
}

static void RTC_configureStart(uint32_t baseAddr)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_GENRAL_CTL));
    *addr &= ~(CSL_RTC_GENRAL_CTL_SW_OFF_MASK);
}

static void RTC_clearWriteErr(uint32_t baseAddr)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_SYNCPEND));
    *addr |= (CSL_RTC_SYNCPEND_WRT_ERR_MASK);
}

static uint32_t RTC_getScratchRegVal(uint32_t baseAddr, uint32_t index)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_SCRATCH0) + (index * 4U));
    return *addr;
}

static void RTC_setScratchRegVal(uint32_t baseAddr, uint32_t index, uint32_t val)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_SCRATCH0) + (index * 4U));
    *addr = val;
}

static void RTC_setCompensation(uint32_t baseAddr, int32_t compVal)
{
    uint32_t lsb_comp = (uint32_t)((uint32_t)compVal & 0xFFU);
    uint32_t msb_comp = (uint32_t)(((uint32_t)compVal >> 8U) & 0xFFU);

    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_COMP));
    *addr = (msb_comp << 8) | lsb_comp;
}
static void RTC_reloadFromBbd(uint32_t baseAddr, uint32_t mask)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_SYNCPEND));
    *addr |= mask;
}

static uint32_t RTC_getRtcStopStatus(uint32_t baseAddr)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_GENRAL_CTL));
    return *addr;
}

static uint32_t RTC_isUnlocked(uint32_t baseAddr)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_GENRAL_CTL));
    return *addr;
}

static uint32_t RTC_obsStatus(uint32_t baseAddr)
{
    volatile uint32_t *addr = (volatile uint32_t *)(baseAddr + (CSL_RTC_SYNCPEND));
    return *addr;
}

static void RTC_SyncClock(uint32_t baseAddr)
{
    uint32_t i = 0U;

    while((RTC_obsStatus(baseAddr) & O32K_CLK_OBS_BIT_MASK) != 0x0U){}

    while(i <= 2U)
    {
        if((RTC_obsStatus(baseAddr) & O32K_CLK_OBS_BIT_MASK) == 0x4U)
        {
            i++;

            while((RTC_obsStatus(baseAddr) & O32K_CLK_OBS_BIT_MASK) != 0x0U){}
        }
    }
}

static int32_t RTC_startRtcTimer(uint32_t baseAddr)
{
    int32_t status = SystemP_SUCCESS;

    RTC_configureStart(baseAddr);

    status = RTC_checkPendingStatus(baseAddr, WR_PEND_MASK);

    RTC_disableWriteAccess(baseAddr, KICK0_LOCK_VALUE, KICK1_LOCK_VALUE);

    if(status == SystemP_SUCCESS)
    {
        status = RTC_checkPendingStatus(baseAddr, WR_PEND_MASK);

        RTC_clearWriteErr(baseAddr);
    }
    
    /* Enable write access to RTC */
    RTC_enableWriteAccess(baseAddr, KICK0_UNLOCK_VALUE, KICK1_UNLOCK_VALUE);

    return status;
}

static int32_t RTC_checkPendingStatus(uint32_t baseAddr, uint32_t flag)
{
    uint32_t timeout = RTC_TIMEOUT;
    int32_t status = SystemP_SUCCESS;
    uint64_t curTime = ClockP_getTimeUsec();

    while(((ClockP_getTimeUsec() - curTime) < timeout) && ((RTC_getPendingStatus(baseAddr) & flag) != 0U))
    {
        /* Do nothing. */
    }

    if(((RTC_getPendingStatus(baseAddr) & flag) != 0U))
    {
        status = SystemP_FAILURE;
    }
    return status;
}

static int32_t RTC_checkObsStatus(uint32_t baseAddr, uint32_t flag)
{
    uint32_t timeout = RTC_TIMEOUT;
    int32_t status = SystemP_SUCCESS;
    uint64_t curTime = ClockP_getTimeUsec();

    while(((ClockP_getTimeUsec() - curTime) < timeout) && ((RTC_obsStatus(baseAddr) & flag) != 0U))
    {
        /* Do nothing. */
    }

    if(((RTC_obsStatus(baseAddr) & flag) != 0U))
    {
        status = SystemP_FAILURE;
    }
    return status;
}

static bool RTC_isLeapYear(uint32_t year)
{
    return (((year % 4U) == 0U) && (((year % 100U) != 0U) || ((year % 400U) == 0U)));
}

static uint32_t RTC_getDaysInMonth(uint32_t year, uint32_t month)
{
    static const uint32_t Days_In_Months[] = { 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U };

    return (Days_In_Months[month - 1U] + (uint32_t)(((month == 2U) && RTC_isLeapYear(year))? 1U : 0U));
}

static uint64_t RTC_convertTimeToSeconds(const RTC_Time *rtc_time)
{
    uint64_t seconds = 0ULL;
    uint32_t year = rtc_time->year;
    uint32_t month = rtc_time->month;

    /* Add seconds for each year */
    for (uint32_t y = RTC_EPOCH_YEAR; y < year; y++) {
        /* Add 366 or 365 days */
        seconds += (uint64_t)(RTC_isLeapYear(y) ? RTC_SECONDS_IN_LEAP_YEAR : RTC_SECONDS_IN_YEAR);
    }

    /* Add seconds for each month in the current year */
    for (uint32_t m = 1U; m < month; m++) {
        seconds += (uint64_t)(RTC_getDaysInMonth(year, m) * RTC_SECONDS_IN_DAY);
    }

    /* Add seconds for days, hours, minutes, and seconds */
    seconds += (uint64_t)(((uint64_t)rtc_time->day - 1ULL) * RTC_SECONDS_IN_DAY);
    seconds += (uint64_t)(rtc_time->hour) * RTC_SECONDS_IN_AN_HOUR;
    seconds += (uint64_t)(rtc_time->minute) * RTC_SECONDS_IN_A_MINUTE;
    seconds += (uint64_t)(rtc_time->second);

    return seconds;
}

static void RTC_convertSecondsToTime(uint64_t seconds, RTC_Time *rtc_time)
{
    uint32_t year = RTC_EPOCH_YEAR;
    uint32_t month = RTC_EPOCH_MONTH;

    uint64_t currSeconds = seconds;

    /* Calculate the Year */
    while (currSeconds >= (uint64_t)(RTC_isLeapYear(year) ? RTC_SECONDS_IN_LEAP_YEAR : RTC_SECONDS_IN_YEAR))
    {
        currSeconds -= (uint64_t)(RTC_isLeapYear(year) ? RTC_SECONDS_IN_LEAP_YEAR : RTC_SECONDS_IN_YEAR);
        year++;
    }
    rtc_time->year = year;

    /* Calculate the Month */
    while (currSeconds >= (uint64_t)(RTC_getDaysInMonth(year, month) * RTC_SECONDS_IN_DAY))
    {
        currSeconds -= (uint64_t)(RTC_getDaysInMonth(year, month) * RTC_SECONDS_IN_DAY);
        month++;
    }
    rtc_time->month = month;

    /* Calculate the Day */
    rtc_time->day = (uint32_t)(currSeconds / RTC_SECONDS_IN_DAY) + 1U;
    currSeconds %= RTC_SECONDS_IN_DAY;

    /* Calculate the Hour, Minute, and Second */
    rtc_time->hour = (uint32_t)(currSeconds / RTC_SECONDS_IN_AN_HOUR);
    currSeconds %= RTC_SECONDS_IN_AN_HOUR;
    rtc_time->minute = (uint32_t)(currSeconds / RTC_SECONDS_IN_A_MINUTE);
    rtc_time->second = (uint32_t)(currSeconds % RTC_SECONDS_IN_A_MINUTE);
}

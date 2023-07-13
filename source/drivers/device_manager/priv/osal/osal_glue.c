/*
 * rm_pm_hal OSAL callout APIs
 *
 * OSAL Glue layer between PDK and rm_pm_hal
 *
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */


#include <kernel/dpl/TimerP.h>
#include <stdio.h>
#include <kernel/dpl/ClockP.h>
#include <osal/osal_clock_user.h>

/**
 * \brief Block inside the current task for the specified amount of time.
 *
 * \param usecs Amount of time to block before continuing execution. Max delay
 *		 is ((2^64 - 1)/1000) microseconds.
 */
void osal_delay(uint64_t usecs)
{
    uint64_t timestamp;
    uint64_t timestampNow;
    #ifdef MCU_PLUS_SDK
        timestamp = ClockP_getTimeUsec();
        timestampNow = timestamp;
        while ((timestampNow - timestamp) < usecs) {
            timestampNow = ClockP_getTimeUsec();
        }
    #else
        timestamp = TimerP_getTimeInUsecs();
        timestampNow = timestamp;
        while ((timestampNow - timestamp) < usecs) {
            timestampNow = TimerP_getTimeInUsecs();
        }
    #endif
}

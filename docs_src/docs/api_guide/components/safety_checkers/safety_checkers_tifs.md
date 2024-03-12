# SAFETY_CHECKERS_TIFS {#SAFETY_CHECKERS_TIFS_PAGE}

[TOC]

TIFS Safety Checkers library APIs are integrated into the safety application to verify the firewall configuration and validate the FWL configuration against golden reference.

## Features Supported

The module supports below API's for the application

* API to dump Firewall registers for modules.
* API to read Firewall registers at run time and validate they are matching with golden state for modules in the safety loop.

## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

- None

## Example Usage

The following shows an example of TIFS Safety Checkers API usage

Include the below file to access the APIs

\code{.c}
#include "../../src/safety_checkers_tifs.h"
\endcode

Request the TIFS to open firewall

\code{.c}
SafetyCheckers_tifsReqFwlOpen();
\endcode

Uses the pointer to firewall configuration pFwlConfig as input and updates pFwlConfig with the register dump of the firewall registers specified.

\code{.c}
SafetyCheckers_tifsGetFwlCfg(pFwlConfig, gSize);
\endcode

Verify and save firewall configuration as Golden Reference

\code{.c}
TimerP_Params_init(&timerParams);
timerParams.runMode    = TimerP_RunMode_CONTINUOUS;
timerParams.startMode  = TimerP_StartMode_USER;
timerParams.periodType = TimerP_PeriodType_MICROSECS;
timerParams.period     = SAFETY_CHECKERS_TIMER_PERIOD;

handle = TimerP_create(SAFETY_CHECKERS_TIMER_ID, (TimerP_Fxn)&timerIsr, &timerParams);
\endcode

Compares the golden reference with runtime firewall register values and return success or failure.

\code{.c}
while(i > 0)
{
    if(gSafetyCheckers_TifsFlag == 1)
    {
        gSafetyCheckers_TifsFlag = 0;
        status = SafetyCheckers_tifsVerifyFwlCfg(pFwlConfig, gSafetyCheckers_TifsCfgSize);

        if(status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
        {
            SAFETY_CHECKERS_log("Register Mismatch with Golden Reference \n");
        }
        i--;
    }
}
if(status == SAFETY_CHECKERS_SOK)
{
    SAFETY_CHECKERS_log("No Register Mismatch with Golden Reference \n");
}
\endcode

Request the TIFS to close firewall

\code{.c}
SafetyCheckers_tifsReqFwlClose();
\endcode

## API

\ref SAFETY_CHECKERS_TIFS_MODULE

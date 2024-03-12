# SAFETY_CHECKERS_PM {#SAFETY_CHECKERS_PM_PAGE}

[TOC]

PM safety checkers library APIs are integrated into the safety application to verify the PSC/PLL configurations and validate the current PSC/PLL configurations against golden reference.
Also provides the PLL lock API which is responsible for locking a PLL control module registers by preventing the stray writes.

## Features Supported

The module supports below API's for the application

* API to get the configurations registers for PSC , PLL and RM modules.
* API to read PLL and PSC registers at run time and validate they are matching with golden state for modules in the safety loop.
* API to lock the PLL configuration registers.

## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

- None

## Example Usage

The following shows an example of PM safety checkers API usage

Include the below file to access the APIs

\code{.c}
#include "../../src/safety_checkers_pm.h"
\endcode

return the pscRegCfg with register configuration for PSC module.

\code{.c}
SafetyCheckers_pmGetPscRegCfg(pscRegCfg, size);
\endcode

compares the pscRegCfg (golden reference) with runtime PSC configuration values and return success or failure.

\code{.c}
if(gflag == 1)
{
    gflag = 0;
    retVal = SafetyCheckers_pmVerifyPscRegCfg(pscRegCfg, size);

    if(retVal != 0)
    {
        DebugP_log("Register Mismatch\r\n");
    } else{
        DebugP_log("No Register Mismatch\r\n");
    }
}
\endcode

return the pllRegCfg with register configuration for PLL module.

\code{.c}
SafetyCheckers_pmGetPllRegCfg(pllRegCfg, size);
\endcode

compares the pllRegCfg (golden reference) with runtime PLL configuration values and return success or failure.

\code{.c}
if(gflag == 1)
{
    gflag = 0;
    retVal = SafetyCheckers_pmVerifyPllRegCfg(pllRegCfg, size);

    if(retVal != 0)
    {
        DebugP_log("Register Mismatch\r\n");
    } else{
        DebugP_log("No Register Mismatch\r\n");
    }
}
\endcode

lock the PLL control module registers.

\code{.c}
if(gflag == 1)
{
    gflag = 0;
    retVal = SafetyCheckers_pmRegisterLock();

    if(retVal != 0)
    {
        DebugP_log("PLL register lock failed\r\n");
    } else{
        DebugP_log("PLL register lock passes\r\n");
    }
}
\endcode

## API

\ref SAFETY_CHECKERS_PM

# SAFETY_CHECKERS_RM {#SAFETY_CHECKERS_RM_PAGE}

[TOC]

RM safety checkers library APIs are integrated into the safety application to verify the RM modules configurations and validate the current RM modules configurations against golden reference.

## Features Supported

The module supports below API's for the application

* API to get the configurations registers for RM modules such as IR, IA IMAP, Ring Accelerator and DMA config registers.
* API to read RM module registers at run time and validate they are matching with golden state for modules in the safety loop.

## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

- None

## Example Usage

The following shows an example of RM safety checkers API usage

Include the below file to access the APIs

\code{.c}
#include "../../src/safety_checkers_rm.h"
\endcode

return the rmRegCfg with register configuration for RM module.

\code{.c}
SafetyCheckers_rmGetRegCfg(rmRegCfg, size);
\endcode

compares the rmRegCfg (golden reference) with runtime RM configuration values and return success or failure.

\code{.c}
if(gflag == 1)
{
    gflag = 0;
    retVal = SafetyCheckers_rmVerifyRegCfg(rmRegCfg, size);

    if(retVal != 0)
    {
        DebugP_log("Register Mismatch\r\n");
    } else{
        DebugP_log("No Register Mismatch\r\n");
    }
}
\endcode

## API

\ref SAFETY_CHECKERS_RM

# SAFETY_APP {#SAFETY_APP_PAGE}

[TOC]

The Safety Checkers (SC) Library provides productized APIs for ensuring the safety of TIFS, RM and PM modules.

## Features Supported

The example demonstrates the usage of RM, PM and TIFS safety checker APIs.

* PM Safety Checker can be used to validate PSC/PLL configurations
* RM Safety Checkers can be used to validate RM module configurations
* TIFS Safety Checker can be used to verify the firewall configuration

Each of these configurations can be validated using the Golden Reference.

## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

- None

## Example Usage

The following shows an example of Safety Checkers API usage

Include the below file to access the APIs

\code{.c}
#include <safety_checkers_common.h>
#include <safety_checkers_pm.h>
#include <safety_checkers_tifs.h>
#include "tifs_checkers_fwl_config.h"
\endcode

Get PM Checkers Register Configuration

\code{.c}
SafetyCheckers_pmGetPscRegCfg(pscRegisterData, SAFETY_CHECKERS_PM_PSC_REGDUMP_SIZE);
SafetyCheckers_pmGetPllRegCfg(pllRegisterData, SAFETY_CHECKERS_PM_PLL_REGDUMP_SIZE);
\endcode

Get RM Checkers Register Configuration

\code{.c}
SafetyCheckers_rmGetRegCfg(rmRegisterData, SAFETY_CHECKERS_RM_REG_BLOB_SIZE);
\endcode

Request TIFS firewall open

\code{.c}
SafetyCheckers_tifsReqFwlOpen();
\endcode

Get TIFS Checkers Register Configuration

\code{.c}
SafetyCheckers_tifsGetFwlCfg(pFwlConfig, gSafetyCheckersTifsCfgSize);
\endcode

Place holder to verify and save configurations as Golden Reference

Verify the run time register configuration against the golden reference for
each of the checkers.

\code{.c}
numIter = 10;
while(numIter > 0)
{
    status = SemaphoreP_pend(&gBinarySem, SystemP_WAIT_FOREVER);

    if(status == SAFETY_CHECKERS_SOK)
    {
        status = SafetyCheckers_pmVerifyPscRegCfg(pscRegisterData, SAFETY_CHECKERS_PM_PSC_REGDUMP_SIZE);
        if (status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
        {
            SAFETY_CHECKERS_log("\n PSC Register Mismatch with Golden Reference\r\n");
        }

        status = SafetyCheckers_pmGetPllRegCfg(pllRegisterData, SAFETY_CHECKERS_PM_PLL_REGDUMP_SIZE);
        if (status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
        {
            SAFETY_CHECKERS_log("\n PLL Register Mismatch with Golden Reference\r\n");
        }

        status = SafetyCheckers_pmRegisterLock();
        if (status == SAFETY_CHECKERS_FAIL)
        {
            SAFETY_CHECKERS_log("\n PM register lock failed\r\n");
        }

        status = SafetyCheckers_rmVerifyRegCfg(rmRegisterData, SAFETY_CHECKERS_RM_REG_BLOB_SIZE);
        if (status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
        {
            SAFETY_CHECKERS_log("\n RM Register Mismatch with Golden Reference\r\n");
        }

        status = SafetyCheckers_tifsVerifyFwlCfg(pFwlConfig, gSafetyCheckersTifsCfgSize);
        if (status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
        {
            SAFETY_CHECKERS_log("\n Firewall Register Mismatch with Golden Reference\r\n");
        }

        numIter--;
    }
}
\endcode

Request the TIFS to close firewall

\code{.c}
SafetyCheckers_tifsReqFwlClose();
\endcode

## API

* \ref SAFETY_CHECKERS_TIFS_MODULE
* \ref SAFETY_CHECKERS_PM
* \ref SAFETY_CHECKERS_RM

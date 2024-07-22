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

Steps to update board configuration for TIFS Safety Checkers:
* Add below lines to the file " ${mcu_plus_sdk}/source/drivers/sciclient/sciclient_default_boardcfg/{board}/sciclient_defaultBoardcfg_security.c"

\code{.c}
/* SA2UL RM config */
    .sa2ul_auth_cfg = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_SA2UL_CFG_MAGIC_NUM_RSVD,
            .size = 0,
        },
        .auth_resource_owner = 0,
        .enable_saul_psil_global_config_writes = 0x5A,
        .safety_host_present = 0x5A,
        .safety_host = host_id
    },
\endcode

\cond SOC_AM62AX || SOC_AM62PX || SOC_AM62DX
\note host_id = 0x1E for mcu-r5f
\endcond

\cond SOC_AM62X
\note host_id = 0x24 for r5f
\endcond

* Use the following commands to build the Boardcfg changes
For GP and HS-FS
\code
cd ${mcu_plus_sdk}/tools/sysfw/boardcfg/
make SOC={board}

cd ${mcu_plus_sdk}
make scrub SOC={board}
make all SOC={board}
\endcode
For HS-SE
\code
cd ${mcu_plus_sdk}/tools/sysfw/boardcfg/
make SOC={board} DEVICE_TYPE=HS

cd ${mcu_plus_sdk}
make scrub SOC={board} DEVICE_TYPE=HS
make all SOC={board} DEVICE_TYPE=HS
\endcode

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

* \ref TIFS_SAFETY_CHECKERS
* \ref PM_SAFETY_CHECKERS
* \ref RM_SAFETY_CHECKERS

# TIFS_SAFETY_CHECKERS

TIFS Safety Checkers library APIs are integrated into the safety application to verify the firewall configuration and validate the FWL configuration against golden reference.

## Features Supported

The module supports below API's for the application

* API to request TIFS to open firewall.
* API to generate Golden Reference using the list of firewall registers specified.
* API compares the Golden Reference with runtime firewall register values and return success or failure.
* API to request TIFS to close firewall.

## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

Steps to update board configuration for TIFS Safety Checkers:
* Add below lines to the file " ${mcu_plus_sdk}/source/drivers/sciclient/sciclient_default_boardcfg/{board}/sciclient_defaultBoardcfg_security.c"

```
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
```
:::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX
   :::{admonition} Note
   host_id = 0x1E for mcu-r5f :::
   :::


:::{only} SOC_AM62X
   :::{admonition} Note
   host_id = 0x24 for r5f :::
   :::


* Use the following commands to build the Boardcfg changes
For GP and HS-FS
```
cd ${mcu_plus_sdk}/tools/sysfw/boardcfg/
make SOC={board}

cd ${mcu_plus_sdk}
make scrub SOC={board}
make all SOC={board}
```
For HS-SE
```
cd ${mcu_plus_sdk}/tools/sysfw/boardcfg/
make SOC={board} DEVICE_TYPE=HS

cd ${mcu_plus_sdk}
make scrub SOC={board} DEVICE_TYPE=HS
make all SOC={board} DEVICE_TYPE=HS
```
## Example Usage

The following shows an example of TIFS Safety Checkers API usage

Include the below file to access the APIs

```
#include "../../src/safety_checkers_tifs.h"
```
Request the TIFS to open firewall

```
SafetyCheckers_tifsReqFwlOpen();
```
Uses the pointer to firewall configuration pFwlConfig as input and updates pFwlConfig with the register dump of the firewall registers specified.

```
SafetyCheckers_tifsGetFwlCfg(pFwlConfig, gSize);
```
Verify and save firewall configuration as Golden Reference

Compare the golden reference with runtime firewall register values and return success or failure.

```
while (i > 0)
{
    status = SafetyCheckers_tifsVerifyFwlCfg(pFwlConfig, gSafetyCheckersTifsCfgSize);

    if (status == SAFETY_CHECKERS_REG_DATA_MISMATCH)
    {
        SAFETY_CHECKERS_log("\n Firewall register mismatch with Golden Reference !!\r\n");
    }

    SafetyCheckersApp_softwareDelay();
    i--;
}
if (status == SAFETY_CHECKERS_SOK)
{
    SAFETY_CHECKERS_log("\n No firewall register mismatch with Golden Reference \r\n");
}
```
Request the TIFS to close firewall

```
SafetyCheckers_tifsReqFwlClose();
```

## API Reference

```{doxygenfile} safety_checkers_tifs.h
```

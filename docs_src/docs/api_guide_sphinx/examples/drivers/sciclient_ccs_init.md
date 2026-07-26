# Sciclient CCS Init 


## Introduction

This is a special soc initialization example which loads the System Firmware on Cortex M4, sends the sciclient boardcfg to the SYSFW running on M4 and initializes the other cores users to connect and debug. This example is used with CCS based initialization for HS-FS devices. You should run this soc initialization binary in the WKUP-R5F core only after powering on the board in [BOOTMODE_DEVBOOT](#bootmode_devboot).

The SYSFW will be part of the application as a hex array and will be loaded to M4 using `Sciclient_loadFirmware` API. The boardcfg is a SOC specific configuration data regarding the various system attributes controlled by the SYSFW. These include resources, power and clock, security etc. If the SYSFW loads and accepts the boardcfg sent, the test result is passed otherwise failed.

## Supported Combinations 

::::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/drivers/sciclient/sciclient_ccs_init

::::



## Steps to Run the Example

```{note}
When powering the board unplug the UART(J22)
```

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [CCS_PROJECTS_PAGE](#ccs_projects_page)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [MAKEFILE_BUILD_PAGE](#makefile_build_page))
- Launch a CCS debug session and run the executable, see [CCS_LAUNCH_PAGE](#ccs_launch_page)

## See Also

[DRIVERS_SCICLIENT_PAGE](#drivers_sciclient_page)

::::{only} not SOC_J722S
## Sample Output
    \imageStyle{sciclient_ccs_int.png,width:50%}
    \image html sciclient_ccs_int.png "CCS view after loading the binary"
\code

\endcode
::::

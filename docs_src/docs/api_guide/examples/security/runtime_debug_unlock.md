# Runtime debug unlock Example {#EXAMPLES_RUNTIME_DEBUG_UNLOCK}

[TOC]

# Introduction

In HS-SE device, the JTAG debug port is closed by default. The user can do runtime debug unlock by sending a TISCI message with a signed debug certificate.
This example demonstrates how to do runtime JTAG port unlock. If the JTAG is unlocked, the example passes. The example is supported only on HS-SE device.

Refer \htmllink{https://downloads.ti.com/tisci/esd/latest/2_tisci_msgs/security/runtime_debug.html,TISCI documentation} for more details about the API.

\note Only hosts allowed in security board configuration can send jtag unlock message via TISCI. Before running the example change the "jtag_unlock_hosts" parameter
in the "source/drivers/sciclient/sciclient_default_boardcfg/@VAR_SOC_NAME_LOWER/sciclient_defaultBoardcfg_security.c" as follows,
\cond SOC_AM62AX
\code
        .jtag_unlock_hosts = {TISCI_HOST_ID_A53_0, 0, 0, 0},
\endcode
\endcond
\cond SOC_AM62PX
\code
        .jtag_unlock_hosts = {TISCI_HOST_ID_WKUP_0_R5_0, 0, 0, 0},
\endcode
\endcond

# Supported Combinations {#EXAMPLES_RUNTIME_DEBUG_UNLOCK_COMBOS}

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/security/runtime_debug_unlock

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/security/runtime_debug_unlock

\endcond

# Steps to Run the Example

## Generate debug certificate
- Generate the debug certificate for your HSSE device using \ref SECURE_DEBUG_CERT tool.

## Build the example
- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

- As the JTAG is closed, the example can not be loaded through CCS. It can be flashed and booted through any \ref EXAMPLES_DRIVERS_SBL.

- For example, refer \ref GETTING_STARTED_FLASH to boot through SBL OSPI.


# Sample Output

Shown below is a sample output when the application is run,

\code
Runtime debug unlock example!
Run time JTAG debug unlock... DONE !!!
All tests have passed!!
\endcode

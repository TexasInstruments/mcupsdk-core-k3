# MCASP Loopback External HCLK {#EXAMPLES_DRIVERS_MCASP_LOOPBACK_EXT_HCLK}

[TOC]

# Introduction

This example demonstrates the McASP in loopback mode operation with an external
HCLK source

- Mcasp is configured in TDM mode
- Transfers data on single channel

# Supported Combinations {#EXAMPLES_DRIVERS_MCASP_LOOPBACK_EXT_HCLK_COMBOS}

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcasp/mcasp_loopback_ext_hclk

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos             |
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcasp/mcasp_loopback_ext_hclk

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\cond SOC_AM62AX || SOC_AM62X
- External HCLK source needs to be supplied to the pin 15 of J3 header. The frequency of
the supplied source is specified in syscfg
\endcond
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_MCASP_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
[MCASP] Loopback example started. Testing 2560 bytes ...
All bytes match!!
All tests have passed!!
\endcode


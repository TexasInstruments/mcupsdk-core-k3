# CSIRX CAPTURE TEST {#EXAMPLES_DRIVERS_CSIRX_IMX219_TEST}

[TOC]
# Introduction

\cond SOC_AM62AX
In this example, CSIRX is configured to receive RAW8 packets from 1 virtual channel
\endcond

# Supported Combinations {#EXAMPLES_DRIVERS_CSIRX_IMX219_TEST_COMBOS}

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/csirx/csirx_capture_test/

\endcond

# Steps to Run the Example

<!-- - **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). -->
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Flash SBL NULL bootloader by following steps mentioned in \ref EVM_FLASH_SOC_INIT
- Switch to \ref BOOTMODE_OSPI and power on the EVM.
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output


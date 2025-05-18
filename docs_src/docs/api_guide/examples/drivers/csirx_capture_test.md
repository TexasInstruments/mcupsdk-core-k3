# CSIRX CAPTURE TEST {#EXAMPLES_DRIVERS_CSIRX_CAPTURE_TEST}

[TOC]
# Introduction

In this example, each CSIRX instance in the SOC is configured to receive RAW12 packets from 4 virtual channels

# Supported Combinations {#EXAMPLES_DRIVERS_CSIRX_CAPTURE_TEST_COMBOS}


\cond SOC_J722S

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | main-r5fss0-0 freertos
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


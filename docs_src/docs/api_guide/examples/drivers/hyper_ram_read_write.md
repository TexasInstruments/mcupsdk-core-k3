# HYPER RAM READ WRITE {#EXAMPLES_DRIVERS_HYPER_RAM_READ_WRITE}

[TOC]

# Introduction

This example demonstrates basic read write to the HyperRam configured in polled mode of operation.

The example writes known data to a particular offset in the HyperRam and then reads it back. The read back data is then compared with the written known data, And this is done in both cases using CPU and BCDMA.

# Supported Combinations {#EXAMPLES_DRIVERS_HYPER_RAM_READ_WRITE_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/board/hyper_ram/hyper_ram_read_write

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_HYPERBUS_PAGE

# Sample Output

\code
All tests have passed!!
\endcode

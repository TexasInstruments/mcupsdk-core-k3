# FLC Example {#EXAMPLES_DRIVERS_FLC}

[TOC]

# Introduction

To understnd how to configure FLC and integrate it in your project, please go though \ref OPTIFLASH_CONFIGURE

FLC example provides how to use FLC in applications and also shows how FLC brings in benefits.

The example writes known data to a particular offset in the flash using flash drivers and then reads it back using FLC. The read back data is then compared with the written known data.

When both the comparisons match, test result is passed otherwise failed.


# Supported Combinations {#EXAMPLES_DRIVERS_FLC_COMBOS}


\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/flc

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output

\note DMA is not used

\code

Throughput without flc :9.28798 MiBps
Throughput with flc :62.06061 MiBps
All tests have passed!!

\endcode

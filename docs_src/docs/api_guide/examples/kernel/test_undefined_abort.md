# Undefined Abort Test {#EXAMPLES_KERNEL_UNDEFINED_ABORT}

[TOC]

# Introduction
This example shows the how custom data abort handler be implemented in the user application.

Provides information about the undef exception
1. `lr`: Link Register when the exception occurred
2. `spsr`: Saved Program Status Register

\note Please refer to R5F TRM for more information

# Supported Combinations

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/dpl/test_undef/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output

\note this application do not gives any output. This goes inside the `HwiP_user_undefined_handler_c` function and loops forever there. User needs to pause the applcaition and see the values.

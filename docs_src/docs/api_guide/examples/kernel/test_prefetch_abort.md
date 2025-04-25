# Prefetch Abort Test {#EXAMPLES_KERNEL_PREFETCH_ABORT}

[TOC]

# Introduction

This example shows the how custom data abort handler be implemented in the user application.
Provides information about the prefetch abort exception
1. Contents of `IFSR`(Instructiton Fault Status Register) register
   1. `status`: indicates the type of fault generated
   2. `sd`: distinguishes between an AXI Decode or Slave error on an external abort. This bit is  only valid for external aborts. For all other aborts types of abort, this bit is set to zero

2. Contents of `AIFSR`(Auxillary Instruction Fault Status Register) register
   1. `index`: returns the index value for the access giving the error
   2. `side_ext`: value returned in this field indicates the source of the error
   3. `recoverable_error`:  value returned in this field indicates if the error is recoverable (0=Unrecoverable error, 1=Recoverable Error)
   4. `cacheway`: value returned in this field indicates the cache way or ways in which the error occurred

3. `lr`: Link Register when the exception occurred.
4. `spsr`: Saved Program status registers to get the program status when the exception occurred.

\note Please refer to R5F TRM for more information

# Supported Combinations

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/dpl/test_prefetch_abort/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output

\note this application do not gives any output. This goes inside the `HwiP_user_prefetch_abort_handler_c` function and loops forever there. User needs to pause the applcaition and see the values.

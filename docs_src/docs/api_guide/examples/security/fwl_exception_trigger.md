# Firewall Exception Trigger Example {#EXAMPLES_FWL_EXCPT_TRIGGER}

[TOC]

# Introduction

This example can be used to trigger firewall exceptions.
The core running this example waits for the user to enter one of the following two characters:
* 'D' to trigger a DMSC firewall exception
* 'C' to trigger a Combined firewall exception

Consequently, a firewall exception takes place.
This example is used with the \ref EXAMPLES_FWL_EXCPT_LOG example to trigger firewall
exceptions, the latter one responds to exception events as and when they take place.

# Supported Combinations {#EXAMPLES_FWL_EXCPT_TRIGGER_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/security/fwl_exception_trigger

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 ^              | mcu-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/security/fwl_exception_trigger

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Enter 'D' to trigger DMSC firewall exception..
Enter 'C' to trigger CMBN firewall exception..
C
\endcode
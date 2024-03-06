# Firewall Exception Log Example {#EXAMPLES_FWL_EXCPT_LOG}

[TOC]

# Introduction

Firewall exceptions occur when an initiator tries to access memory locations which are firewalled against access from it.
Whenever firewall exceptions take place, corrsponding interrupt for various cores are asserted.
This example demonstrates how to handle firewall exceptions.

# Supported Combinations {#EXAMPLES_FWL_EXCPT_LOG_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/security/fwl_exception_log

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/security/fwl_exception_trigger

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
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
FWL Exception logging example!
Registered handler for DMSC firewall exception interrupt!
Registered handler for CMBN firewall exception!
Waiting for DMSC firewall exceptions...
Waiting for CMBN firewall exceptions...
Combined Firewall Exception Occured!! Check TIFS logs for more details
Combined Firewall Exception Occured!! Check TIFS logs for more details
All tests have passed!!
\endcode

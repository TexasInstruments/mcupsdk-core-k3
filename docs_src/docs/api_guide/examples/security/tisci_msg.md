# TISCI message example {#EXAMPLES_TISCI_MSG}

[TOC]

# Introduction

The TIFS core services TISCI messages from the other cores for various operations. This example demonstrates how to send some of those TISCI messages and get the
response. If all the APIs return success, the example passes.

Refer \htmllink{https://downloads.ti.com/tisci/esd/latest/2_tisci_msgs/index.html#secure-management,TISCI documentation} for more details about the APIs.

# Supported Combinations {#EXAMPLES_TISCI_MSG_COMBOS}

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/security/tisci_msg

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/security/tisci_msg

\endcond

# Steps to Run the Example

## Build the example
- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
TISCI message example!
Handover physical processor core to requested host... DONE !!!
Get unique SOC ID... DONE !!!
SOC UID: 0x4dcb8677f73ca649ce11e477c478756210bb47f28fd33804d078bb36212f253d
Set DKEK to SA2UL instance... DONE !!!
Release DKEK from SA2UL DKEK register... DONE !!!
Get DKEK for the given label and context... DONE !!!
DKEK: 0xeec26d202c3cc8eb11425713c71786f74c3c95a40af8fb9df64d03a20aa4f87d
All tests have passed!!
\endcode

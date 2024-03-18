# SAFETY APP {#EXAMPLES_SAFETY_APP}

[TOC]

# Introduction

The example demonstrates the usage of RM, PM and TIFS safety checker APIs.

* PM Safety Checker can be used to validate PSC/PLL configurations
* RM Safety Checkers can be used to validate RM module configurations
* TIFS Safety Checker can be used to verify the firewall configuration

Each of these configurations can be validated using the Golden Reference.

# Supported Combinations {#EXAMPLES_SAFETY_APP_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/safety/safety_app/

\endcond

\cond SOC_AM62AX || SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/safety/safety_app/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref SAFETY_APP_PAGE

# Sample Output

Shown below is a sample output when the application is run

\code
Get PSC configuration successful.
Get PLL configuration successful.
Get RM configuration successful.
Firewall open successful.
Get firewall configuration successful.
Verifying registers against golden reference...
No register mismatch with golden reference.
Firewall close successful.
\endcode

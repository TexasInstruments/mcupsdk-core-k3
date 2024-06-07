# RM SAFETY CHECKERS APP {#EXAMPLES_RM_CHECKERS_APP}

[TOC]

# Introduction

RM Safety Checker (SAFETY_CHECKERS-RM) provided APIs which are integrated into the safety application to verify the RM modules configuration and validate the runtime RM moudules configuration against golden reference.

SAFETY_CHECKERS-RM library includes the following implementation:
1. Reading the RM modules configuration registers, below are the modules included:
      * IR
      * IA IMAP
      * Ring Accelerator
      * DMA
2. Validation of current RM modules configuration registers against golden reference.

This example demonstrates how to use SAFETY_CHECKERS-RM library APIs.

In generation of RM modules config, Safety application shall call the RM read APIs to access the configuration registers from the Safety Checkers library running in the Safety Core. Safety checkers returns RM modules config to the safety application. Safety application validates the RM modules configuration and save it as a golden reference in a non-volatile memory. This initializes the Safety Application and gathers the initial configuration data.

In validate RM module config stage, Safety application provides golden reference to the RM safety checker and Safety checker will validates at defined intervals. RM safety checker reads the RM modules registers at runtime and validate they are matching with the golden state for modules in safety loop. Safety checker will return success or failure after validates against the golden reference.

The user should implement firewall based protection for golden reference and also create a checksum for the golden reference to ensure validity of the golden reference data.

# Supported Combinations {#EXAMPLES_RM_CHECKERS_APP_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER , @VAR_SK_LP_BOARD_NAME_LOWER,
 Example folder | source/safety_checkers/examples/

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang**
 ^              | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | source/safety_checkers/examples/

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/safety_checkers/examples/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref RM_SAFETY_CHECKERS_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
RM register blob test match !!!
\endcode

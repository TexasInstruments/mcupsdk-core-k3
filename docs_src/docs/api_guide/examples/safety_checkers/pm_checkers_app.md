# PM SAFETY CHECKERS APP {#EXAMPLES_PM_CHECKERS_APP}

[TOC]

# Introduction

PM Safety Checker (SAFETY_CHECKERS-PM) provided APIs which are integrated into the safety application to verify the PSC/PLL configuration and validate the runtime PSC/PLL configuration against golden reference. Also includes the API to lock the PLL control module registers of PM for the prevention of stray writes.

SAFETY_CHECKERS-PM library includes the following implementation:
1. Reading the configuration registers of PSC/PLL modules.
2. Validation of current PLL/PSC configuration registers against golden reference.
3. Locking the PLL control module registers of PM.

This example demonstrates the validation of PM messages by passing the valid and invalid parameters and how to use SAFETY_CHECKERS-PM library APIs.

Validation of PM messages by using the valid and invalid Device ID. PM messages are listed below:
  **TISCI_MSG_SET_DEVICE**,
  **TISCI_MSG_GET_DEVICE**,
  **TISCI_MSG_SET_DEVICE_RESETS**,
  **TISCI_MSG_SET_CLOCK**,
  **TISCI_MSG_SET_CLOCK_PARENT**,
  **TISCI_MSG_SET_FREQ**,
  **TISCI_MSG_GET_CLOCK**,
  **TISCI_MSG_GET_CLOCK_PARENT**,
  **TISCI_MSG_GET_NUM_CLOCK_PARENTS**,
  **TISCI_MSG_QUERY_FREQ**,
  **TISCI_MSG_GET_FREQ**,

Validation of PM messages by using the valid and invalid Clock ID. PM messages are listed below:
  **TISCI_MSG_SET_CLOCK**,
  **TISCI_MSG_SET_CLOCK_PARENT**,
  **TISCI_MSG_SET_FREQ**,
  **TISCI_MSG_GET_CLOCK**,
  **TISCI_MSG_GET_CLOCK_PARENT**,
  **TISCI_MSG_GET_NUM_CLOCK_PARENTS**,
  **TISCI_MSG_QUERY_FREQ**,
  **TISCI_MSG_GET_FREQ**,

Validation of PM messages by using the valid and invalid Device state. PM messages are listed below:
  **TISCI_MSG_SET_DEVICE**,

Validation of PM messages by using the valid and invalid Device resets. PM messages are listed below:
  **TISCI_MSG_SET_DEVICE_RESETS**,

Validation of PM messages by using the valid and invalid Clock State. PM messages are listed below:
  **TISCI_MSG_SET_CLOCK**,

Validation of PM messages by using the valid and invalid Parent Clock. PM messages are listed below:
  **TISCI_MSG_SET_CLOCK_PARENT**,

Validation of PM messages by using the valid and invalid Device group. PM messages are listed below:
  **TISCI_MSG_SYS_RESET**,

In generation of PSC/PLL config, Safety application shall call the PSC/PLL read APIs to access the configuration registers from the Safety Checkers library running in the Safety Core. Safety checkers returns PSC/PLL config to the safety application. Safety application validates the PSC/PLL configuration and save it as a golden reference in a non-volatile memory. This initializes the Safety Application and gathers the initial configuration data.

In validate PSC/PLL config stage, Safety application provides golden reference to the PM safety checker and Safety checker will validates at defined intervals. PM safety checker reads the PSC/PLL registers at runtime and validate they are matching with the golden state for modules in safety loop. Safety checker will return success or failure after validates against the golden reference.

Addition to the above stages, PLL lock will be called to make sure the PLL configuration registers are not modified.

# Supported Combinations {#EXAMPLES_PM_CHECKERS_APP_COMBOS}

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

\ref SAFETY_CHECKERS_PM_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Clock ID boundary validation passed
Clock State boundary validation passed
Device ID boundary validation passed
Device Reset boundary validation passed
Device State boundary validation passed
Parent Clock boundary validation passed
PSC register dump and readback test passed
PLL register dump and readback test passed
PSC and PLL register dump test passed
PLL register Lock test Passed
Device Group boundary validation passed
PM error condition check test passed
Error: Clock ID boundary validation failed !!!
Error: Clock State boundary validation failed !!!
Error: Device ID boundary validation failed !!!
Error: Device Reset boundary validation failed !!!
Error: Device State boundary validation failed !!!
Error: Parent Clock boundary validation failed !!!
Error: PSC and PLL register dump test failed !!!
Error: PLL register Lock test failed !!!
All the PM safety checkers test passed
\endcode
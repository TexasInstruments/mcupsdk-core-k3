# DDR ECC Test MAIN ESM {#EXAMPLES_DRIVERS_DDR_ECC_TEST_MAIN_ESM}

[TOC]
\cond SOC_AM62X
\note This example demostrates handling the ESM error in the Main domain R5.
The error can also be routed to MCU ESM and handled in the safety domain (M4 core)
\endcond

# Introduction

This example simulates a 1b and 2b ECC error for DDR and waits for interrupt via the MAIN ESM instance.
On receiving the interrupt, the handler clears the ECC error bit and restore the original value.
If the interrupt is not received the test fails.

# Supported Combinations {#EXAMPLES_DRIVERS_DDR_ECC_TEST_MAIN_ESM_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/ddr/ddr_ecc_test_main_esm/

\endcond

\cond SOC_AM62AX || SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/ddr/ddr_ecc_test_main_esm/

\endcond

# Steps to Run the Example

\cond SOC_AM62X
\note This example corrupts the data present in DDR for ECC error testing, so it cannot be placed in DDR.
It has to be side loaded from CCS. SBL cannot load this example as it runs from HSM RAM memory.
\endcond

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- By default DDR inline ECC is configured in the sysconfig of SBL NULL bootloader.
- Flash SBL NULL bootloader by following steps mentioned in \ref EVM_FLASH_SOC_INIT
- Switch to \ref BOOTMODE_OSPI and power on the EVM.
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

\note DDR inline ECC can be configured in the sysconfig of other SBLs as well. If you are configuring ECC for different
address region, change the DDR_ECC_REGION0_START macro in the example file for testing.


# See Also

\ref DRIVERS_DDR_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Waiting on Single bit Error Correction Interrupt...
1b ECC error detected
Waiting on Dual bit error detection Interrupt...
2b ECC error detected
All tests have passed!!
\endcode

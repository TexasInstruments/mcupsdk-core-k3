# DDR ECC Test MCU ESM {#EXAMPLES_DRIVERS_DDR_ECC_TEST_MCU_ESM}

# Introduction

This example generates 1b and 2b ECC error for DDR. The M4 enables the
ESM instances (MAIN ESM0 and MCU ESM0).
On generating an ECC error, the M4 receives the interrupt from MCU ESM
(through the MAIN ESM error signal output routed to the MCU ESM).
On receiving the interrupt, the handler clears the corresponding ECC error bit and restore the original value.
If the interrupt is not received the test fails.

# Supported Combinations {#EXAMPLES_DRIVERS_DDR_ECC_TEST_MCU_ESM_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | m4fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/ddr/ddr_ecc_test_mcu_esm/

\endcond

# Steps to Run the Example

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

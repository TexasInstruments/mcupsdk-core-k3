# HYPER RAM READ WRITE {#EXAMPLES_DRIVERS_HYPER_RAM_ECC_TEST}

[TOC]

# Introduction

This example simulates a 1b and 2b ECC error for HYPERRAM and waits for FSS_FSAS_ECC interrupt. On receiving the interrupt, the handler clears the ECC error bit and restore the original value. If the interrupt is not received the test fails.

# Supported Combinations {#EXAMPLES_DRIVERS_HYPER_RAM_ECC_TEST_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/board/hyperRam/hyperRam_ecc_test

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_HYPERBUS_PAGE

# Sample Output

\code
Waiting on Single bit Error Correction Interrupt...
1b ECC error detected and corrected
Waiting on Dual bit error detection Interrupt...
2b ECC error detected
All tests have passed
\endcode

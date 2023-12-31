# SA3UL AES CMAC-256 Test {#EXAMPLES_DRIVERS_SA3UL_AES_CMAC_256}

[TOC]

# Introduction

This example demonstrates the AES CMAC-256 using SA3UL module.

# Supported Combinations {#EXAMPLES_DRIVERS_SA3UL_AES_CMAC_256_COMBOS}

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/security/crypto/sa3ul_aes/crypto_aes_cmac_256/crypto_aes_cmac_256.c

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref SECURITY_SA3UL_MODULE_PAGE

# Sample Output

Shown below is a sample output when the application is run.


CCS Console:
\code
[CRYPTO] AES CMAC-256 example started ...
[CRYPTO] AES CMAC-256 example completed!!
All tests have passed!!

\endcode



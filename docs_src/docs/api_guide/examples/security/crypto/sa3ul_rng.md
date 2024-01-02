# SA3UL Random Number Generator Test {#EXAMPLES_DRIVERS_SA3UL_RNG}

[TOC]

# Introduction

This example demonstrates the Random number generation using SA3UL module.

# Supported Combinations {#EXAMPLES_DRIVERS_SA3UL_RNG_COMBOS}

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/security/crypto/sa3ul_rng/sa3ul_rng.c

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
All tests have passed!!
[SA3UL] Sa3ul Rng example started ...
[SA3UL] Sa3ul Rng output word 1 -- 0x3704DD0A
[SA3UL] Sa3ul Rng output word 2 -- 0x68719DEA
[SA3UL] Sa3ul Rng output word 3 -- 0x3A2733EE
[SA3UL] Sa3ul Rng output word 4 -- 0x943F007E
[SA3UL] Sa3ul Rng output word 1 -- 0xCE83C20D
[SA3UL] Sa3ul Rng output word 2 -- 0xAEB445B0
[SA3UL] Sa3ul Rng output word 3 -- 0xE052FEC9
[SA3UL] Sa3ul Rng output word 4 -- 0x713231C3
[SA3UL] Sa3ul Rng output word 1 -- 0xD5CF553B
[SA3UL] Sa3ul Rng output word 2 -- 0x1AB11E5F
[SA3UL] Sa3ul Rng output word 3 -- 0x25163494
[SA3UL] Sa3ul Rng output word 4 -- 0x5CD0432F
[SA3UL] Sa3ul Rng output word 1 -- 0x8372B743
[SA3UL] Sa3ul Rng output word 2 -- 0x75AA97AC
[SA3UL] Sa3ul Rng output word 3 -- 0x59F277C7
[SA3UL] Sa3ul Rng output word 4 -- 0x8DFC768C
[SA3UL] Sa3ul Rng output word 1 -- 0xAF3B154C
[SA3UL] Sa3ul Rng output word 2 -- 0x3A93F540
[SA3UL] Sa3ul Rng output word 3 -- 0xC3174A84
[SA3UL] Sa3ul Rng output word 4 -- 0xA361D316
[SA3UL] Sa3ul Rng example completed!!
All tests have passed!!

\endcode



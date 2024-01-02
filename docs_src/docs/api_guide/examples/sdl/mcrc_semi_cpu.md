# SDL MCRC Semi CPU {#EXAMPLES_SDL_MCRC_SEMI_CPU}

[TOC]

# Introduction

This example demonstrates the usage of the MCRC module. The example shows how to setup and use the MCRC controller in the semi mode of operation.
Shows the generation of matching CRC as well as non-matching signature due to insertion of error in the block of information on which the CRC
is being performed or in the signature provided to the PSA Signature Register (or both, depending on the mode).

Use Cases
---------

 Use Case | Description
 ---------|------------
 UC-1     | Semi CPU-mode signature compute for Channel 1 and comparison against known value.
 UC-2     | Semi CPU-mode signature compute for Channel 2 and comparison against known value.

# Supported Combinations {#EXAMPLES_SDL_MCRC_SEMI_CPU_COMBOS}

\cond SOC_AM62X || SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/mcrc/mcrc_semi_cpu/

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/mcrc/mcrc_semi_cpu/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref SDL_MCRC_PAGE

# Sample Output

Shown below is a sample output when the application is run,


\cond (SOC_AM62X) || (SOC_AM62AX) || (SOC_AM62PX)
\code
[MAIN_Cortex_R5_0_0]
 MCRC Test Application


MCRC Semi_CPU mode : starting


MCRC SEMI CPU mode on Channel 1: Transfer Test Started...

Calculating Reference MCRC signature Value.
 MCRC signature value : 0x474b7cf03d4145dU
MCRC Full Mode Computation Time: 1995us
MCRC Semi CPU intrrupt status : 1

Sector signature matches - Passed
Calculated MCRC signature value : 0x474b7cf003d4145dU

UDMA Data transfer completed !!
MCRC Semi Mode Computation Time: 0us

MCRC SEMI CPU mode on Channel 2: Transfer Test Started...

Using Pre-Defined Reference MCRC signature Value.

Pre-defined MCRC signature value : 0x474b7cf03d4145dU
MCRC Semi CPU intrrupt status : 100

Sector signature matches - Passed
Calculated MCRC signature value : 0x474b7cf003d4145dU

UDMA Data transfer completed !!
MCRC Semi Mode Computation Time: 0us

Test Name: MCRC_semiCPU_mode  PASSED

 All tests have passed.
\endcode
\endcond

# SDL MCRC Full CPU {#EXAMPLES_SDL_MCRC_FULL_CPU}

[TOC]

# Introduction

This example demonstrates the usage of the MCRC module. The example shows how to setup and use the MCRC controller in the full mode of operation.
Shows the generation of matching CRC as well as non-matching signature due to insertion of error in the block of information on which the CRC
is being performed or in the signature provided to the PSA Signature Register (or both, depending on the mode).

Use Cases
---------

 Use Case | Description
 ---------|------------
 UC-1     | Full CPU-mode signature compute for Channel 1 and comparison against known value.
 UC-2     | Full CPU-mode signature compute for Channel 2 and comparison against known value.

# Supported Combinations {#EXAMPLES_SDL_MCRC_FULL_CPU_COMBOS}

\cond SOC_AM64X || SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | m4fss0-0 nortos
 ^				| r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/mcrc/mcrc_full_cpu/

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/mcrc/mcrc_full_cpu/
\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/mcrc/mcrc_full_cpu/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref SDL_MCRC_PAGE
\cond SOC_AM64X
# Sample Output SOC_AM64X

Shown below is a sample output when the application is run,

\code
 MCRC Application

 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCRC_MCU_NAVSS


 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCRC_MCU_NAVSS

 Applications Name: MCRC_fullCPU_mode  PASSED

 All applications have passed.

 MCRC Application

 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCRC_MCU_NAVSS


 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCRC_MCU_NAVSS

 Applications Name: MCRC_fullCPU_mode  PASSED

 All tests have passed
\endcode
\endcond

\cond SOC_AM62X
# Sample Output SOC_AM62X
\endcond


\cond SOC_AM62AX
# Sample Output SOC_AM62AX

\code
 MCRC Application

 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0


 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

 Applications Name: MCRC_fullCPU_mode  PASSED

 All applications have passed.

 MCRC Application

 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0


 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

 Applications Name: MCRC_fullCPU_mode  PASSED

 All tests have passed
\endcode

\endcond


\cond SOC_AM62PX
# Sample Output SOC_AM62PX

\code
 MCRC Application

 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0


 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

 Applications Name: MCRC_fullCPU_mode  PASSED

 All applications have passed.

 MCRC Application

 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0


 MCRC FULL CPU mode : starting
 Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

 Applications Name: MCRC_fullCPU_mode  PASSED

 All tests have passed
\endcode

\endcond
# Sciclient Get Version {#EXAMPLES_DRIVERS_SCICLIENT_GET_VERSION}

[TOC]

# Introduction

\cond !SOC_AM62X && !SOC_AM62AX && !SOC_AM62PX
This example demonstrates how to check the version of SYSFW running on the Cortex M3 at run time. Since this is frequently done by bootloaders as a sanity check, there is an API included in the Sciclient driver for checking the SYSFW version.
\endcond

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX
This example demonstrates how to check the version of SYSFW running on the Cortex R5 (DM R5) at run time. Since this is frequently done by bootloaders as a sanity check, there is an API included in the Sciclient driver for checking the SYSFW version.
\endcond

However, in this example this API is not used, instead the basic Sciclient_service API is used to send a "GET VERSION" request to the SYSFW and get a response back and print it out.

We also fetch the clock frequency of the current CPU using Sciclient and print that out as well, as additional sanity check.

# Supported Combinations {#EXAMPLES_DRIVERS_SCICLIENT_GET_VERSION_COMBOS}

\cond SOC_AM64X
\attention A53 NORTOS and A53 FREERTOS SMP support is experimental and is NOT supported by TI. \n
\endcond

\cond SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-1 nortos
 ^              | r5fss1-0 nortos
 ^              | r5fss1-1 nortos
 ^              | m4fss0-0 nortos
 ^              | a53ss0-0 nortos
 ^              | a53ss0-0 freertos-smp
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/sciclient/sciclient_get_version

\endcond

\cond SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-1 nortos
 ^              | r5fss1-0 nortos
 ^              | r5fss1-1 nortos
 ^              | m4fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/sciclient/sciclient_get_version

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | m4fss0-0 nortos
 ^              | r5fss0-0 freertos
 ^              | a53ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/sciclient/sciclient_get_version

\endcond
\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 ^              | c75ss0-0 freertos
 ^              | a53ss0-0 nortos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/sciclient/sciclient_get_version

\endcond
\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 ^              | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/sciclient/sciclient_get_version

\endcond
# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\cond SOC_AM62X
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.
\endcond

# See Also

\ref DRIVERS_SCICLIENT_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\cond !SOC_AM62X && !SOC_AM62AX
\code
DMSC Firmware Version 21.1.1--v2021.01a (Terrific Lla
Firmware revision 0x15
ABI revision 3.1
[SCICLIENT] CPU clock frequency = 800000000 Hz
All tests have passed!!
\endcode
\endcond

\cond SOC_AM62X
\code
SYSFW Version 8.6.0--v08.06.00 (Chill Capybar
Firmware revision 0x15
ABI revision 3.1
[SCICLIENT] CPU clock frequency = 400000000 Hz
All tests have passed!!
\endcode
\endcond
\cond SOC_AM62AX
\code
SYSFW Version 9.0.4--v09.00.04 (Kool Koala)
Firmware revision 0x9
ABI revision 3.1
[SCICLIENT] CPU clock frequency = 1250000000 Hz
All tests have passed!!
\endcode
\endcond

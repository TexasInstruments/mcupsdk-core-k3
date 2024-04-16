# MMCSD RAW IO {#EXAMPLES_DRIVERS_MMCSD_RAW_IO}

[TOC]

# Introduction

This example demonstrates basic read write to the eMMC/SD Card. The MMC instance and the media connected to it are selectable via Sysconfig.

The example writes known data to a particular offset in the media and then reads it back. The read back data is then compared with the written known data.

When both the comparisons match, test result is passed otherwise failed.

# Supported Combinations {#EXAMPLES_DRIVERS_MMCSD_RAW_IO_COMBOS}

\cond SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/mmcsd/mmcsd_raw_io

\endcond

\cond SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mmcsd/mmcsd_raw_io

\endcond



\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | a53ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/mmcsd/mmcsd_raw_io

\endcond


\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | a53ss0-0 freertos
 ^              | a53ss0-0 nortos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mmcsd/mmcsd_raw_io

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mmcsd/mmcsd_raw_io

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\cond !SOC_AM62X
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\endcond
\cond SOC_AM62X
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.
\endcond
# See Also

\ref DRIVERS_MMCSD_PAGE

# Sample Output

\code
[MMCSD RAW IO] Starting...
All tests have passed!!
\endcode

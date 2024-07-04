# GPMC Flash IO {#EXAMPLES_DRIVERS_GPMC_FLASH_IO}

[TOC]

# Introduction

This example demonstrate's basic read, write and erase to the Parallel NAND flash using GPMC configured in polled mode of operation. APIs from flash driver are used to read, write and erase to the flash. The flash APIs call the underlying GPMC APIs for read, write and erase function.

The example writes known data to a particular offset in the flash and then reads it back. The read back data is then compared with the written known data.
When both the comparisons match, test result is passed otherwise failed.


# Supported Combinations {#EXAMPLES_DRIVERS_GPMC_FLASH_IO_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | a53ss0-0 freertos
 ^              | a53ss0-0 nortos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/gpmc/gpmc_flash_io/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

\cond SOC_AM62X
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.
\endcond

# See Also

\ref DRIVERS_GPMC_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Starting GPMC application
All tests have passed
\endcode
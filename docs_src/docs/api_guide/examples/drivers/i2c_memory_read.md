# I2C Memory Read {#EXAMPLES_DRIVERS_I2C_MEMORY_READ}

[TOC]

# Introduction

This example demonstrates writing a data to I2C based EEPROM devices present in the board and
then reading back the same data from the EEPROM.

# Supported Combinations {#EXAMPLES_DRIVERS_I2C_MEMORY_READ_COMBOS}

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | c75ss0-0 freertos
 ^              | mcu-r5fss0-0 nortos
 ^              | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/i2c/i2c_memory_read

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_I2C_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\cond SOC_AM62DX

\code
[I2C] Writing data to EEPROM ... !!!
[I2C] Reading data from EEPROM ... !!!
[I2C] Data at address 0x400 : 0x10
All tests have passed!!
\endcode

\endcond

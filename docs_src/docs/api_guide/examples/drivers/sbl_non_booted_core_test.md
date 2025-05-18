# SBL Non Booted Core Test {#EXAMPLES_DRIVERS_SBL_NON_BOOTED_CORE_TEST}

[TOC]

# Introduction

This SBL example checks if non-booted cores are properly switched off.

It checks and displays the status of all cores other than the core running the application (WKUP R5F).

# Supported Combinations {#EXAMPLES_DRIVERS_SBL_NON_BOOTED_CORE_TEST_COMBOS}

\cond SOC_J722S

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_non_booted_core_test

\endcond

# Steps to Run the Example

It is run from an SD card unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

<!-- - **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). -->
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Partition the SD card to have boot and root parititon
- Copy sbl_sd.release.hs_fs.tiimage as tiboot3.bin to the boot partition of SD card
- Copy application image as app to the boot partition of SD card

# Sample Output

\cond SOC_J722S
\code

DMSC Firmware Version 10.0.8--v10.00.08 (Fiery Fox)
DMSC Firmware revision 0xa
DMSC ABI revision 4.0

[BOOTLOADER_PROFILE] Boot Media      : SD Card
[BOOTLOADER_PROFILE] Boot Image Size : 105 KB
[BOOTLOADER_PROFILE] Cores present   :
wkup-r5f0-0
[BOOTLOADER PROFILE] System_init                     :     35388us
[BOOTLOADER PROFILE] Drivers_open                    :    162986us
[BOOTLOADER PROFILE] Board_driversOpen               :         0us
[BOOTLOADER PROFILE] Sciclient Get Version           :      9766us
[BOOTLOADER_PROFILE] SBL Total Time Taken            :    208141us

Image loading done, switching to application ...
Starting RTOS/Baremetal applications
a530-0 is powered OFF !!
a530-1 is powered OFF !!
a531-0 is powered OFF !!
a531-1 is powered OFF !!
mcu-r5f is powered OFF !!
main-r5f is powered OFF !!
c75ss0-0 is powered OFF !!
c75ss1-0 is powered OFF !!
All tests have passed

\endcode
\endcond
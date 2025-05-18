# SBL OSPI NAND {#EXAMPLES_DRIVERS_SBL_OSPI_NAND}

[TOC]

# Introduction

This bootloader does SOC initializations and attempts to boot a multicore appimage present at 0x80000 location in the OSPI Flash. To flash a multicore appimage at this location, follow the steps mentioned in \ref BASIC_STEPS_TO_FLASH_FILES.

If a multicore appimage is found at the location, the SBL parses it, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset. For more on bootflow/bootloaders, please refer \ref BOOTFLOW_GUIDE

# Supported Combinations {#EXAMPLES_DRIVERS_SBL_OSPI_NAND_COMBOS}

\cond SOC_J722S

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi

\endcond

# Steps to Run the Example

Since this is a bootloader, the example will be run every time you boot an application using this example. It is run from a OSPI boot media  unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

<!-- - **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). -->
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Flash SBL, Appimage to OSPI Flash, follow below steps to flash the binaries
\note Before running the following command, user needs to build sbl_uart_uniflash_stage1, sbl_uart_uniflash_stage2_nand, sbl_ospi_nand, appimage and edit the cfg file according to appimage that we are booting
- If Linux PC is used, assuming SDK is installed at ~/ti/mcu_plus_sdk

      cd ~/ti/mcu_plus_sdk/tools/boot
       python uart_uniflash.py -p <main UART COM port> --cfg=~/ti/mcu_plus_sdk/tools/sbl_prebuilt/j722s-evm/default_sbl_ospi_nand_hs_fs.cfg
# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

\code
[BOOTLOADER_PROFILE] Boot Media       : FLASH
[BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
[BOOTLOADER_PROFILE] Boot Image Size  : 435 KB
[BOOTLOADER_PROFILE] Cores present    :
mcu-r5f0-0
wkup-r5f0-0
main-r5f0-0
c75ss0
c75ss1
[BOOTLOADER PROFILE] System_init                      :      36445us
[BOOTLOADER PROFILE] Drivers_open                     :         52us
[BOOTLOADER PROFILE] Board_driversOpen                :         74us
[BOOTLOADER PROFILE] App_loadImages                   :      91264us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :     127836us

Image loading done, switching to application ...
Starting RTOS/Baremetal applications
Sciserver Testapp Built On: Mar  4 2024 16:34:41
Sciserver Version: v2023.12.0.0-WAKEUP.MCUSDK.J722S.DM.w2023.02
RM_PM_HAL Version: w2023.02-j722s
Starting Sciserver..... PASSED
wkup R5 core booted
mcu R5 core booted
main R5 core booted
c75x_1 core booted
c75x_2 core booted
wkup R5 core reports : All tests have passed
\endcode
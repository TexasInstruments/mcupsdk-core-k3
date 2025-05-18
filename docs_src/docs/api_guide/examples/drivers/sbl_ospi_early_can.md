# SBL OSPI EARLY CAN {#EXAMPLES_DRIVERS_SBL_OSPI_EARLY_CAN}

[TOC]

# Introduction

This bootloader does SOC initializations and attempts to boot a multicore appimage present at 0x80000 location in the OSPI Flash. To flash a multicore appimage at this location, follow the steps mentioned in \ref BASIC_STEPS_TO_FLASH_FILES.

If a multicore appimage is found at the location, the SBL parses it, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset. For more on bootflow/bootloaders, please refer \ref BOOTFLOW_GUIDE

This SBL image is different comapred to SBL OSPI in terms of optimizations done to obtain the expected Early CAN Response. Optimizations required include disabling UART prints and not initializing DDR in the SBL. Both of these are expected to be taken care of by the application being run post SBL.

# Supported Combinations {#EXAMPLES_DRIVERS_SBL_OSPI__EARLY_CAN_COMBOS}

\cond SOC_J722S

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_early_can

\endcond

# Steps to Run the Example

Since this is a bootloader, the example will be run every time you boot an application using this example. It is run from a OSPI boot media  unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

<!-- - **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). -->
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Flash SBL, Appimage to OSPI Flash, follow below steps to flash the binaries
\note Before running the following command, user needs to build sbl_uart_uniflash, sbl_ospi_early_can, appimage and edit the cfg file according to appimage that we are booting
- If Linux PC is used, assuming SDK is installed at ~/ti/mcu_plus_sdk

      cd ~/ti/mcu_plus_sdk/tools/boot
       python uart_uniflash.py -p <main UART COM port> --cfg=~/ti/mcu_plus_sdk/tools/sbl_prebuilt/j722s-evm/default_sbl_ospi_hs_fs.cfg

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

No UART logs are expected as UART is disabled for this SBL.
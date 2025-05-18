# SBL OSPI HLOS {#EXAMPLES_DRIVERS_SBL_OSPI_HLOS}

[TOC]

# Introduction

This is a bootloader example, which shows an example of booting Linux/U-Boot/QNX on A53 core and RTOS/NORTOS applications on DM R5 and M4 cores. This SBL target supports booting the following test cases

- SBL Booting Linux Kernel
- SBL Booting U-Boot
- SBL Booting QNX

# Supported Combinations

\cond SOC_J722S
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_hlos
\endcond



# Steps to Run the Example

## Prepare the SD Card

- Create SD card using balena etcher tool, refer Processor-SDK-Linux for more details
- This is needed to have file system in root partition of SD card

## Build the Example

\cond !SOC_J722S
- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
\endcond
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Create Linux Appimage

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)** or (ATF, OPTEE, Kernel, DTB) in case of fastboot mode.
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details

## Create QNX Appimage

- Create a QNX Appimage containing (TAF, OPTEE, QNX-IFS)
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/qnxAppimageGen after setting the PSDK path in file `config.mak`
- Refer \ref QNX_APPIMAGE_GEN_TOOL for more details

## Run the Example

- Flash SBL, Appimage to OSPI Flash, follow below steps to flash the binaries
\note Before running the following command, user needs to build sbl_uart_uniflash_stage1, sbl_uart_uniflash_stage2, sbl_ospi_hlos, HLOS appimage and edit the cfg file according to HLOS appimage that we are booting
- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        - cd ~/ti/mcu_plus_sdk/tools/boot
        - python uart_uniflash.py -p <main UART COM port> --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_hlos_hs_fs.cfg

- Boot the EVM in OSPI NOR boot mode.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

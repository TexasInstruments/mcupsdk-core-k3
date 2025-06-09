# CAN Response App {#EXAMPLES_DRIVERS_MCAN_RESPONSE_APP}

[TOC]

# Introduction

This application is responsible for transmitting an Early CAN Message using MCU_MCAN0 instance.

It enables CAN transceiver by exiting the StandBy mode. Following which it transmits a 64B CAN FD message which can be received from the MCU_MCAN0 (J5 header).

To measure CAN Response, it should use sbl_ospi_early_can and measure time from MCU_PORz Reset (TP43) to CAN-H line on MCU_MCAN0 (J5 header).

# Supported Combinations {#EXAMPLES_DRIVERS_MCAN_RESPONSE_APP_COMBOS}

\cond SOC_J722S

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcan/can_response_app

\endcond

# Steps to Run the Example

<!-- - **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). -->
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Flash SBL, Appimage to OSPI Flash, follow below steps to flash the binaries
\note Before running the following command, user needs to build sbl_uart_uniflash, sbl_ospi_early_can, can_response_app and edit the cfg file according to appimage that we are booting
- If Linux PC is used, assuming SDK is installed at ~/ti/mcu_plus_sdk

      cd ~/ti/mcu_plus_sdk/tools/boot
       python uart_uniflash.py -p <main UART COM port> --cfg=~/ti/mcu_plus_sdk/tools/sbl_prebuilt/j722s-evm/default_sbl_ospi_hs_fs.cfg

# See Also

\ref DRIVERS_BOOTLOADER_PAGE
\ref DRIVERS_MCAN_PAGE

# Sample Output

\code

Sciserver Testapp Built On: Oct 24 2024 09:34:09
Sciserver Version: v2024.07.0.0REL.MCUSDK.10.00.00.13+
RM_PM_HAL Version: v10.00.07
Starting Sciserver..... PASSED
Message successfully transferred with payload Bytes: 64B
CAN message successfully transmitted...

\endcode
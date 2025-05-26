# UART Echo DMA {#EXAMPLES_DRIVERS_UART_ECHO_BCDMA}

[TOC]

# Introduction

This example demonstrates the UART RX and TX operation in blocking,
DMA-BCDMA mode of operation.
This example receives 8 characters and echos back the same.
The application ends when the user types 8 characters.

# Supported Combinations {#EXAMPLES_DRIVERS_UART_ECHO_BCDMA_COMBOS}

\cond SOC_AM62LX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 ^              | a53ss0-0 nortos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/uart/uart_echo_bcdma

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\cond SOC_AM62LX
- To Load and Run an example (see \ref DFU_LOAD_CCS_DEBUG)
\endcond
- Please select the UART port used for console as mentioned in \ref CCS_UART_TERMINAL

# See Also

\ref DRIVERS_UART_PAGE

# Sample Output

Shown below is a sample output when the application is run,
Please note that application prints in both CCS and UART console.
In UART console you need to enter 8 characters.

UART Console:
\code
This is uart echo test DMA blocking mode
Receives 8 characters then echo's back. Please input..
12345678
All tests have passed!!
\endcode

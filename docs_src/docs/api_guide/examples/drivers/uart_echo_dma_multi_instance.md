# UART Echo DMA Multi-Instance {#EXAMPLES_DRIVERS_UART_ECHO_DMA_MULTI_INSTANCES}

[TOC]

# Introduction

This example demonstrates the UART RX and TX operation in blocking,
DMA-PKTDMA mode of operation for two UART instances.
Two uart instances runs parallely asking the user to input 8 characters
and once both the transfer is completed successfully, the application ends.

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62LX || SOC_AM62PX
The user should input 8 characters in UART0 and UART1.
\endcond

\cond SOC_AM275X
The user should input 8 characters in UART0 and UART2.
\endcond

\cond SOC_AM62DX
The user should input 8 characters in UART0 and UART4.
\endcond

# Supported Combinations {#EXAMPLES_DRIVERS_UART_ECHO_DMA_MULTI_INSTANCES_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/uart/uart_echo_dma_multi_instance

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/uart/uart_echo_dma_multi_instance

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/uart/uart_echo_dma_multi_instance

\endcond

\cond SOC_AM62LX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/uart/uart_echo_dma_multi_instance

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/uart/uart_echo_dma_multi_instance

\endcond

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/uart/uart_echo_dma_multi_instance

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\cond SOC_AM62LX
- To Load and Run an example (see \ref DFU_LOAD_CCS_DEBUG)
\endcond
\cond !SOC_AM62LX
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\endcond
- Please select the UART port used for console as mentioned in \ref CCS_UART_TERMINAL

# See Also

\ref DRIVERS_UART_PAGE

# Sample Output

Shown below is a sample output when the application is run,
Please note that application prints in two UART consoles one
after the other as two UART instances are configured.
In UART console you need to enter 8 characters.

UART Console:
\code
This is uart echo test DMA blocking mode
Receives 8 characters then echo's back. Please input..
12345678
All tests have passed!!
\endcode

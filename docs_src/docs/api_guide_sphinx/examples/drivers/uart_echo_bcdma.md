# UART Echo BCDMA

## Introduction

This example demonstrates the UART RX and TX operation in blocking,
DMA-BCDMA mode of operation.
This example receives 8 characters and echos back the same.
The application ends when the user types 8 characters.

## Supported Combinations
:::{only} SOC_AM62LX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 ^              | a53ss0-0 nortos
 Toolchain      | arm.gnu.aarch64-none
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/drivers/uart/uart_echo_bcdma

:::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
:::{only} SOC_AM62LX
- To Load and Run an example (see [Application Run and debugging using CCS](../../getting_started/application_launch.md))
:::
- Please select the UART port used for console as mentioned in [EVM Setup](../../device/am62lx/am62lx_evm_setup.md)

## See Also

[UART](../../components/drivers/uart.md)

## Sample Output

Shown below is a sample output when the application is run,
Please note that application prints in both CCS and UART console.
In UART console you need to enter 8 characters.

UART Console:
```
This is uart echo test DMA blocking mode
Receives 8 characters then echo's back. Please input..
12345678
All tests have passed!!
```

# UART Echo DMA Multi-Instance
## Introduction

This example demonstrates the UART RX and TX operation in blocking,
DMA-PKTDMA mode of operation for two UART instances.
Two uart instances runs parallely asking the user to input 8 characters
and once both the transfer is completed successfully, the application ends.


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62LX or SOC_AM62PX
   The user should input 8 characters in UART0 and UART1.
::::


::::{only} SOC_AM275X
   The user should input 8 characters in UART0 and UART2.
::::


::::{only} SOC_AM62DX
   The user should input 8 characters in UART0 and UART4.
::::


## Supported Combinations
::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/uart/uart_echo_dma_multi_instance |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/uart/uart_echo_dma_multi_instance |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/uart/uart_echo_dma_multi_instance |

::::


::::{only} SOC_AM62LX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/uart/uart_echo_dma_multi_instance |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/uart/uart_echo_dma_multi_instance |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/uart/uart_echo_dma_multi_instance |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM62LX
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::

- Please select the UART port used for console as mentioned in [Setup UART Terminal](../../getting_started/am62px_evm_setup.md)

## See Also

[UART](../../components/drivers/uart.md)

## Sample Output

Shown below is a sample output when the application is run,
Please note that application prints in two UART consoles one
after the other as two UART instances are configured.
In UART console you need to enter 8 characters.

UART Console:
```
This is uart echo test DMA blocking mode
Receives 8 characters then echo's back. Please input..
12345678
All tests have passed!!
```
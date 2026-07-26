# MCAN External Read Write

## Introduction

This example demonstrates CAN message communication to an external CAN controller using a PCAN-USB (from PEAK Systems : IPEH-004022) with the following configuration.

- CAN FD Message Format
- Message ID Type is Standard with Msg Id 0xC0
- MCAN is configured in Interrupt Mode
- MCAN Interrupt Line Number 0
- Arbitration Bit Rate 1Mbps
- Data Bit Rate 5Mbps
- Buffer mode is used for Tx and RX to store message in message RAM.

The MCAN module is programmed to transmit a CAN message and wait for the same message to be received back from the external CAN controller connected via a PCAN-USB. Once 10 messages are sent and received without any error the example is completed.

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcan/mcan_external_read_write |

::::

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcan/mcan_external_read_write |

::::

## Steps to Run the Example

- **Hardware Connectivity**, connect the PCAN-USB module to PC from USB and Serial Port.
- **Software Setup**, Download and Install the PCAN-View from https://www.peak-system.com/PCAN-View.242.0.html?&L=1
- Click on CAN in the menu bar and connect to PCAN-Usb. Set Mode as ISO CAN FD, Sampling point under Nominal Bit Rate as 85 percent and Sampling Point under Data Bit Rate as 87.5 percent. Leave the rest as default.
- After successful reception of data, transmit data ten times from PCAN-View in a ping pong fashion for the test to complete.
- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[MCAN](../../components/drivers/mcan.md)

## Sample Output

Shown below is a sample output when the application is run,

```
[MCAN] External read - write test, application started ...
After transmitting messages it will wait to receive ten messages for test to pass ...
All tests have passed!!
```

# MCAN External Read Write {#EXAMPLES_DRIVERS_MCAN_EXTERNAL_READ_WRITE}

[TOC]

# Introduction

This example demonstrates CAN message communication to an external CAN controller using a PCAN-USB (from PEAK Systems : IPEH-004022) with the following configuration.

- CAN FD Message Format
- Message ID Type is Standard with Msg Id 0xC0
- MCAN is configured in Interrupt Mode
- MCAN Interrupt Line Number 0
- Arbitration Bit Rate 1Mbps
- Data Bit Rate 5Mbps
- Buffer mode is used for Tx and RX to store message in message RAM.

The MCAN module is programmed to transmit a CAN message and wait for the same message to be received back from the external CAN controller connected via a PCAN-USB. Once 10 messages are sent and recieved without any error the example is completed.

# Supported Combinations {#EXAMPLES_DRIVERS_MCAN_EXTERNAL_READ_WRITE_COMBOS}

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 ^              | mcu-r5fss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | a53ss0-0 nortos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcan/mcan_external_read_write

\endcond

# Steps to Run the Example

- **Hardware Conectivity**, connect the PCAN-USB module to PC from USB and Serial Port to be connected as mentioned in the image below.


\imageStyle{mcan_external_hw_connect.png,width:40%}
\image html mcan_external_hw_connect.png MCAN Hardware Connectivity with PCAN USB.

- **Software Setup**, Download and Install the PCAN-View from https://www.peak-system.com/PCAN-View.242.0.html?&L=1

- Click on CAN in the menu bar and connect to PCAN-Usb. Set Mode as ISO CAN FD, Sampling point under Nominal Bit Rate as 85 percent and Sampling Point under Data Bit Rate as 87.5 percent. Leave the rest as default.

- When data is received from MCAN instance, it will be visible as shown in the image below in PCAN-View.

\imageStyle{pcan_message_received.PNG,width:50%}
\image html pcan_message_received.PNG Data received as shown in PCAN-View

- After successful reception of data, the data has to be transmitted ten times from PCAN-View in a ping pong fashion for test to be completed successfully.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_MCAN_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
[MCAN] External read - write test, application started ...
After transmitting messages it will wait to recieve ten messages for test to pass ...
All tests have passed!!
\endcode

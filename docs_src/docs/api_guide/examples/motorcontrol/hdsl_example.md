#  HDSL Diagnostic {#EXAMPLE_MOTORCONTROL_HDSL}

# Introduction

The HDSL firmware running on ICSS-PRU provides a defined well interface to execute the HDSL protocol.
The HDSL diagnostic application described here interacts with the firmware interface.

HDSL diagnostic application does below,
- Configures pinmux, GPIO, ICSS clock to 225MHz,
- Initializes ICSS0-PRU1, ICSS0-IEP0 and IEP1(for SYNC mode support.Timesync router is used to latch the loopback.),
- Loads lookup table for encoding/decoding of Hiperface data
- Loads the initialization section of PRU firmware & executes it.

Firmware is split to three sections, initialization, datalink and transport.
At startup, the application displays details about encoder and status. It
then presents the user with menu options, based on the option selected,
application communicates with HDSL interface and the result is presented
to the user.

## Features Supported

-  PRU firmware source
-  External pulse synchronization
-  Safe position
-  Supports upto 100m cable
-  Communication status
-  Register interface to be compatible with SICK HDSL FPGA IP Core.
   (except registers that have different functionality for read and
    write)
-  Parameter channel communication (short message write)

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

SysConfig can be used to configure things mentioned below:
- Selecting the ICSSG0PRUx instance.(Tested on ICSSG0-PRU1)
- Configuring PINMUX.

## Features Not Supported

In general, peripherals or features not mentioned as part of "Features Supported" section are not supported, including the below
 -  Fast position, speed
 -  Pipeline channel
 -  Short message read
 -  Safety

## Important files and directory structure

<table>
<tr>
    <th>Folder/Files
    <th>Description
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/examples/motor_control/hdsl_diagnostic</td></tr>
<tr>
    <td>hdsl_diagnostic.c</td>
    <td>Hdsl diagnostic application</td>
</tr>
<tr>
    <td>hdsl_lut.c</td>
    <td>Look up tables for HDSL.</td>
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/source/motor_control/position_sense/hdsl</td></tr>
<tr>
    <td>firmware/</td>
    <td>Folder containing HDSL PRU firmware sources.</td>
</tr>
</table>

# Supported Combinations {#EXAMPLES_MOTORCONTROL_HDSL_COMBOS}

\cond SOC_AM64X || SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ICSSG          | ICSSG0
 PRU            | PRU1
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/motorcontrol/hdsl_example

\endcond

# Steps to Run the Example

## Hardware Prerequisites

Other than the basic EVM setup mentioned in \ref EVM_SETUP_PAGE, below additional HW is required to run this demo
- HDSL encoder
- Below are two options to connect encoder to AM64x EVM.
    - **Option 1** 
        - TIDA-00179 Universal Digital Interface to Absolute Position Encoders, http://www.ti.com/tool/TIDA-00179
        - TIDEP-01015 3 Axis board
        - Interface card connecting EVM and TIDEP-01015 3 Axis board
        - Connect the Hiperface DSL encoder to HDSL+/-(Pin number 6 and 7) signals available on header J7 or Sub-D15 connector of the "Universal Digital Interface to Absolute Position Encoders" board.
    - **Option 2** 
        - HDSL AM64xE1 Transceiver. If application is using this card, define the macro HDSL_AM64xE1_TRANSCEIVER in the CCS project/make file.
        - Connect the Hiperface DSL encoder to J10.
		- HDSL AM64xE1 Transceiver supports two channels that can be used to support HDSL safety, multi axis servo drives.
		- Schematics are shared in the MCU+SDK package. For more design details of the transceiver card, please contact TI via E2E/FAE.
		- \htmllink{../am64x_am243x/HDSL_AM64xE1_Schematics.pdf, HDSL Transceiver Card Schematics} document.

## Hardware Setup(Using TIDA-00179, TIDEP-01015 and Interface board)

\imageStyle{HDSL_Connections.png,width:40%}
\image html HDSL_Connections.png "Hardware Setup"

## Hardware Setup(Using HDSL AM64xE1 Transceiver)

\imageStyle{HDSL_AM64xE1_2.png,width:80%} 
\image html HDSL_AM64xE1_2.png "Hardware Setup"

## Build, load and run

- **When using CCS projects to build**, import the CCS project and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
- Refer to UART terminal for user interface menu options.

# Sample Output

Shown below is a sample output when the application is run:

- Freerun mode,
\imageStyle{HDSL_Normal.png,width:60%}
\image html HDSL_Normal.png "HDSL Diagnostic in freerun mode"

- Sync Mode,
\imageStyle{HDSL_SYNC.png,width:60%}
\image html HDSL_SYNC.png "HDSL Diagnostic in SYNC mode"

#  EnDAT Diagnostic {#EXAMPLE_MOTORCONTROL_ENDAT}

[TOC]

# Introduction

EnDat is a bidirectional interface for position encoders. During EnDat
operation the EnDat master receives position information from the EnDat
position encoder. The EnDat diagnostic application, described here,
demonstrates the EnDat master operation.

The EnDat driver provides a well defined set of API's to expose EnDat
master interface.

The diagnostic invokes these API's to
- initialize EnDat,
- configure the host trigger mode,
- select between concurrent multi channel or single channel configuration,
- select the channel (channels in the case of concurrent multi channel configuration)
- and run the firmware.

Once these steps are executed,
- the driver waits for the EnDat to be initialized.
- It then sets clock frequency to 200KHz (as propagation delay is not yet compensated)
- and obtains the encoder details including serial number, position resolution etc, and displays
on the console.
- Based on the whether encoder is 2.2 or 2.1 type, it sets clock to either 8MHz or 1MHz respectively.
- While configuring clock, propagation delay is taken care using the automatically estimated
propagation delay (user can override it too).
- In the case of concurrent multi channel configuration, if propagation delay between various
channels are different, that too is automatically taken care.

Once initial setup is over,
- the diagnostic provides the user with a
self explanatory menu.
- Two types of menu options are presented. One type
(1-14) will send an EnDat command as per EnDat 2.2 specification.
- The other type (100-108) allows the user to configure clock frequency,
various timing parameters, simulate motor control loop using 2.1 command
as well as 2.2 command with safety (redundant position information),
switch to continuous clock mode and monitor raw data.
- Concurrent multi
channel configuration can work simultaneously for up-to three encoders
with identical part number, all variants of 2.2 position commands as
well as the 2.1 position command is supported and an additional option
(109) to configure wire delay (useful when propagation delay in each
channel is different) is available.
- Application by default, handles wire
delay as required, the menu option provides a way to override it.

After the user selects an EnDat command,
- the diagnostic asks for more
details to frame the command and performs a basic sanity check on the
user entered values.
- Then the EnDat API is invoked to process the
command.
- The received EnDat is processed & validated using the defined
API's. The result is then presented to the user.

## Features Supported

   -  PRU Firmware source
   -  EnDat 2.2 command set
   -  EnDat 2.1 command set
   -  Interrupted and continuous clock mode
   -  Clock configuration up to 16MHz
   -  Cable length up to 100m @8MHz
   -  Propagation delay compensation (capable of handling different
      propagation delay of different channels in concurrent multi
      channel configuration)
   -  Automatic estimation of propagation delay
   -  Receive on-the-fly CRC verification of position, parameters and
      additional information
   -  Two modes of operation - host trigger and periodic trigger
   -  Channel select
   -  Concurrent multi channel support (up-to 3 encoders with identical
      part number @ 8MHz maximum)

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

SysConfig can be used to configure things mentioned below:
- Selecting the ICSSG0PRUx instance.(Tested on ICSSG0-PRU1)
- Configuring PINMUX.

## Features Not Supported

In general, peripherals or features not mentioned as part of "Features Supported" section are not supported in this release, including the below
- Safety

## Important files and directory structure

<table>
<tr>
    <th>Folder/Files
    <th>Description
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/examples/motor_control/endat_diagnostic</td></tr>
<tr>
    <td>endat_diagnostic.c</td>
    <td>EnDAT diagnostic application</td>
</tr>
<tr><td colspan="2" bgcolor=#F0F0F0> ${SDK_INSTALL_PATH}/source/motor_control/position_sense/endat</td></tr>
<tr>
    <td>firmware/</td>
    <td>Folder containing EnDAT firmware sources.</td>
</tr>
<tr>
    <td>driver/</td>
    <td>EnDAT diagnostic driver.</td>
</tr>
</table>

# Supported Combinations {#EXAMPLES_MOTORCONTROL_ENDAT_COMBOS}

\cond SOC_AM64X || SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ICSSG          | ICSSG0
 PRU            | PRU1
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/motorcontrol/endat_example

\endcond


# Steps to Run the Example

## Hardware Prerequisites

Other than the basic EVM setup mentioned in \ref EVM_SETUP_PAGE, below additional HW is required to run this demo
- EnDAT encoder
- TIDA-00179 Universal Digital Interface to Absolute Position Encoders, http://www.ti.com/tool/TIDA-00179
- TIDEP-01015 3 Axis board
- Interface card connecting EVM and TIDEP-01015 3 Axis board

## Hardware Setup

\imageStyle{EnDAT_Connections.png,width:40%}
\image html EnDAT_Connections.png "Hardware Setup"

## Build, load and run

- **When using CCS projects to build**, import the CCS project and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
- Refer to UART terminal for user interface menu options.

# Sample Output

Shown below is a sample output when the application is run:

\imageStyle{EnDAT_1.png,width:60%}
\image html EnDAT_1.png "EnDAT Usage"


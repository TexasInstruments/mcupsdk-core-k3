# AASRC Sinewave Conversion {#EXAMPLES_DRIVERS_AASRC_SINEWAVE_CONVERSION}

[TOC]

# Introduction

This example demonstrates the AASRC configured for three channel config with operating
mode set to MONO, STEREO & GROUP mode. The samples of sine wave signal of signal freqeuncy
1.92 kHz sampled at 192 kHz provided as input for each of the channel config and aasrc converts
it to output sampling frequency of 96.01 kHZ for MONO Channel config, 208.51 kHZ for STEREO channel config,
and 96.01 kHZ for group channel config with a MONO channel count of five

- AASRC is configured in 24 bit data format

The example converts the data provided and send it out using UART. A python script is provided in
${SDK_INSTALL_PATH}/tools/aasrc_validation/aasrc_validation.py
which can receive and read these data and plot graphs showcasing the conversion of sampling
frequency from one clock zone to another. Change the serial port mentioned in script as per the example and run the script first which will make the script to wait for receiving data and then run the example

\note Sysconfig don't support AASRC configuration now.
 ' aasrc_config.c ' and ' aasrc_config.h ' files are provided at ${SDK_INSTALL_PATH}/examples/drivers/aasrc/aasrc_sinewave_conversion for manual AASRC configuration


# Supported Combinations {#EXAMPLES_DRIVERS_AASRC_SINEWAVE_CONVERSION_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 ^              | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/aasrc/aasrc_sinewave_conversion

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_AASRC_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
[AASRC] Sinewave sampling frequency conversion example started
AASRC 0 input clock zone 0 freq = 192.10176086 KHz
AASRC 0 output clock zone 0 freq = 96.01265717 KHz
AASRC 0 input clock zone 1 freq = 192.10232544 KHz
AASRC 0 output clock zone 1 freq = 208.51408386 KHz
AASRC 0 input clock zone 2 freq = 192.10232544 KHz
AASRC 0 output clock zone 2 freq = 96.01278687 KHz
Data Start
MONO CHANNEL : 0, Signal Frequency: 1.92101765 KHz, Data Format: 24 Bits
Input Buffer Sending
Output Buffer Sending
Data End
Data Start
STEREO CHANNEL : 0, Signal Frequency: 1.92101765 KHz, Data Format: 24 Bits
Input Buffer Sending
Output Buffer Sending
Data End
Data Start
STEREO CHANNEL : 1, Signal Frequency: 1.92101765 KHz, Data Format: 24 Bits
Input Buffer Sending
Output Buffer Sending
Data End
Data Start
GROUP CHANNEL : 0, Signal Frequency: 1.92101765 KHz, Data Format: 24 Bits
Input Buffer Sending
Output Buffer Sending
Data End
Data Start
GROUP CHANNEL : 1, Signal Frequency: 1.92101765 KHz, Data Format: 24 Bits
Input Buffer Sending
Output Buffer Sending
Data End
Data Start
GROUP CHANNEL : 2, Signal Frequency: 1.92101765 KHz, Data Format: 24 Bits
Input Buffer Sending
Output Buffer Sending
Data End
Data Start
GROUP CHANNEL : 3, Signal Frequency: 1.92101765 KHz, Data Format: 24 Bits
Input Buffer Sending
Output Buffer Sending
Data End
Data Start
GROUP CHANNEL : 4, Signal Frequency: 1.92101765 KHz, Data Format: 24 Bits
Input Buffer Sending
Output Buffer Sending
Data End
All Over
\endcode

# SWASRC Multichannel Playback {#EXAMPLES_DRIVERS_SWASRC_MULTICHANNEL_PLAYBACK}

[TOC]

# Introduction

This example demonstrates the SW ASRC takes the multichannel digital audio data streams
received using McASP configured with TDM 8 at 32 kHz and converts the same to 48 kHz and
send out the converted data as audio out using McASP.

Audio can be inputed from the 3.5mm audio line in jacks (J1A, J1B, J2A, J2B)
and audio out can be heard from audio line out jacks (J3A, J3B, J4A, J4B).

- McASP is configured in 32 bit data format
- Mcasp RX is configured in TDM8 mode to receive from the 2xPCM6240
- Mcasp TX is configured in 4xI2S mode to transmit to 4xTAD5212
- McASP Rx clock is internally generated with FSYNC rate of 32 kHz
- McASP Tx clock is externally generated with FSYNC rate of 48 kHz

# Supported Combinations {#EXAMPLES_SWASRC_MULTICHANNEL_PLAYBACK_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/signal_processing/swasrc_multichannel_playback

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/signal_processing/swasrc_multichannel_playback

\endcond

# System Flow Overview
\image html swasrc_multichannel_playback.png "SWASRC with CALCRATIO Flow Overview"


# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also
\ref SW_CALCRATIO_PAGE

# Sample Output

Shown below is a sample output from the script when the application is run,

\cond SOC_AM275X

\code
..
...
\endcode

\endcond

\cond SOC_AM62DX

\code
...
\endcode

\endcond

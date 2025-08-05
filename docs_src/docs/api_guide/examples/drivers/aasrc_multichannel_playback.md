# AASRC Multichannel Playback {#EXAMPLES_DRIVERS_AASRC_MULTICHANNEL_PLAYBACK}

[TOC]

# Introduction

This example demonstrates the AASRC configured for GROUP operating mode. AASRC takes the
multichannel digital audio data streams received using McASP configured with TDM 8 at 48 kHz
and converts the same to 96 kHz and send out the converted data as audio out using McASP.

Audio can be inputed from the 3.5mm audio line in jacks (J1A, J1B, J2A, J2B)
and audio out can be heard from audio line out jacks (J3A, J3B, J4A, J4B).

- AASRC & McASP is configured in 24 bit data format
- McASP RX/Tx is configured in TDM8 mode to receive and transmit
- McASP Rx clock is internally generated with FSYNC rate of 48 kHz
- McASP Tx clock is externally generated with FSYNC rate of 96 kHz
- McASP FSYNC clocks is being used as the reference clock for AASRC receive and transmit.

# Supported Combinations {#EXAMPLES_DRIVERS_AASRC_MULTICHANNEL_PLAYBACK_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/aasrc/aasrc_multichannel_playback

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
[AASRC] Audio playback example started.
Enter your response on UART terminal
Stop the demo? (y/n) : y
Exiting demo
\endcode

# MCASP Multichannel Playback {#EXAMPLES_DRIVERS_MCASP_MULTICHANNEL_PLAYBACK}

[TOC]

# Introduction

This example demostrates the McASP configured for an 8 channel audio playback mode
of operation. Audio can be inputed from the 3.5mm audio line in jacks (J1A, J1B, J2A, J2B)
and audio out can be heard from audio line out jacks (J3A, J3B, J4A, J4B).

- Mcasp RX is configured in TDM8 mode to receive from the 2xPCM6240
- Mcasp TX is configured in 4xI2S mode to transmit to 4xTAD5212
- Mcasp is configured as the clock master with external clock sourced from CDCE6214


# Supported Combinations {#EXAMPLES_DRIVERS_MCASP_MULTICHANNEL_PLAYBACK_COMBOS}

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | c75ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 ^              | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcasp/mcasp_multichannel_playback

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_MCASP_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
[MCASP] Audio playback example started.
Enter your response on UART terminal
Stop the demo? (y/n) : y
\endcode

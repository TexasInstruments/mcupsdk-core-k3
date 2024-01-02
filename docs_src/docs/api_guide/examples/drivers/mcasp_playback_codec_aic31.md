# MCASP Playback {#EXAMPLES_DRIVERS_MCASP_PLAYBACK}

[TOC]

# Introduction

This example demostrates the McASP configured for an audio playback mode of operation.
A headset with mic needs to be connected to the auido jack on @VAR_BOARD_NAME_LOWER.
The audio from the microphone will be played back to both the headset (Left & Right).

- Mcasp is configured in I2S mode
- Data transfer is on both channels (Left and Right)

# Supported Combinations {#EXAMPLES_DRIVERS_MCASP_PLAYBACK_COMBOS}

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 ^              | r5fss0-0 nortos
 ^              | a53ss0-0 freertos
 Toolchain      | ti-c7000
 ^              | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcasp/mcasp_playback_codec_aic32

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

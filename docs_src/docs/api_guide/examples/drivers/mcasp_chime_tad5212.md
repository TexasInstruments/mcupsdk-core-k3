# MCASP Chime {#EXAMPLES_DRIVERS_MCASP_CHIME_TAD5212}

[TOC]

# Introduction

This example demonstrates audio chime.

A headset needs to be connected to the audio jack J3 Top @VAR_BOARD_NAME_LOWER for hearing the audio.

- Mcasp is configured in I2S mode
- Audio chime is played on both channels (Left and Right)

# Supported Combinations {#EXAMPLES_DRIVERS_MCASP_CHIME_TAD5212_COMBOS}

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0_freertos
 Toolchain      | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcasp/mcasp_chime_tad5212

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
Starting Chime
Chime completed
\endcode

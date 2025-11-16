# CALCRATIO {#EXAMPLES_DRIVERS_CALCRATIO_MEASUREMENT}

[TOC]

# Introduction

This example demonstrates real-time clock-ratio estimation between two asynchronous audio clocks (e.g., a 32 kHz receiver and a 48 kHz transmitter).
The estimated ratio is periodically updated and fed to the SW ASRC (Software Asynchronous Sample-Rate Converter) so that the receiver can resample the incoming stream without clicks or drift.

Every 0.5 s a timer tick triggers the capture of:
- Rx Sample Counter – number of samples consumed by the MCASP-Rx (32 kHz domain)
- Tx Sample Counter – number of samples produced by the MCASP-Tx (48 kHz domain)
- MCASP is configured in 32 bit data format

\note
- This demo does not perform actual audio streaming or sample-rate conversion.
- Ensure that the McASP RX and TX DMA configurations use the same DMA transfer size, including the loop-job buffer.

# System Flow Overview
\image html calcratio.png "CalcRatio DMA Counter Flow Overview"


# Supported Combinations {#EXAMPLES_DRIVERS_CALCRATIO_MEASUREMENT_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/signal_processing/calcratio

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/signal_processing/calcratio

\endcond


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
Calcratio + DMA Couter playback example started.
ActualRatio for 32000Hz to 48000Hz = 1.500000
ActualRatio for 32000Hz to 48000Hz = 1.500492
ActualRatio for 32000Hz to 48000Hz = 1.500246
ActualRatio for 32000Hz to 48000Hz = 1.500328
ActualRatio for 32000Hz to 48000Hz = 1.500246
ActualRatio for 32000Hz to 48000Hz = 1.500295
ActualRatio for 32000Hz to 48000Hz = 1.500246
ActualRatio for 32000Hz to 48000Hz = 1.500281
ActualRatio for 32000Hz to 48000Hz = 1.500246
...
\endcode

\endcond

\cond SOC_AM62DX

\code
Calcratio + DMA Couter playback example started.
ActualRatio for 32000Hz to 48000Hz = 1.500000
ActualRatio for 32000Hz to 48000Hz = 1.500492
ActualRatio for 32000Hz to 48000Hz = 1.500246
ActualRatio for 32000Hz to 48000Hz = 1.500328
ActualRatio for 32000Hz to 48000Hz = 1.500246
ActualRatio for 32000Hz to 48000Hz = 1.500295
ActualRatio for 32000Hz to 48000Hz = 1.500246
ActualRatio for 32000Hz to 48000Hz = 1.500281
ActualRatio for 32000Hz to 48000Hz = 1.500246
...
\endcode

\endcond
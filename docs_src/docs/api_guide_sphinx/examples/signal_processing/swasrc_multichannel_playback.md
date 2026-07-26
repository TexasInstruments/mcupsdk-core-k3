# SWASRC Multichannel Playback

## Introduction

This example demonstrates the SW ASRC takes the multichannel digital audio data streams
received using McASP configured with TDM 8 at 32 kHz and converts the same to 48 kHz and
sends out the converted data as audio out using McASP.

Audio can be input from the 3.5mm audio line in jacks (J1A, J1B, J2A, J2B)
and audio out can be heard from audio line out jacks (J3A, J3B, J4A, J4B).

- McASP is configured in 32 bit data format
- McASP RX is configured in TDM8 mode to receive from the 2xPCM6240
- McASP TX is configured in 4xI2S mode to transmit to 4xTAD5212
- McASP Rx clock is internally generated with FSYNC rate of 32 kHz
- McASP Tx clock is externally generated with FSYNC rate of 48 kHz

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/signal_processing/swasrc_multichannel_playback |

::::

::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/signal_processing/swasrc_multichannel_playback |

::::

## System Flow Overview

```{figure} ../../images/examples/swasrc_multichannel_playback.png
:align: center

SWASRC with CALCRATIO Flow Overview
```

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[Signal Processing](../examples_signal_processing.rst)

## Sample Output

Shown below is a sample output from the script when the application is run,

::::{only} SOC_AM62DX or SOC_AM275X

```
...
```

::::

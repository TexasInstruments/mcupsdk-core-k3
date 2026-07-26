# AASRC Stereo Playback

## Introduction

This example demonstrates the AASRC configured for STEREO operating mode. AASRC takes the
digital audio data streams received using McASP at 48 kHz FSYNC rate and converts the same
to 96 kHz and send out the converted data as audio out using McASP. McASP FSYNC clocks is being used as
the reference clock for AASRC receive and transmit. Audio can be inputed from the 3.5mm audio
line in jack (J2 Top) and audio out can be heard from audio line out jack (J3 Top).

- AASRC & McASP is configured in 24 bit data format

## Supported Combinations

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/aasrc/aasrc_stereo_playback |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[AASRC](../../components/drivers/aasrc.md)

## Sample Output

Shown below is a sample output when the application is run,

```
[AASRC] Audio playback example started.
Enter your response on UART terminal
Stop the demo? (y/n) : y
Exiting demo
```

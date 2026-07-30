# MCASP Multichannel in Stereo out

## Introduction

This example demonstrates the McASP configured for an 8 channel audio playback mode
of operation. Audio can be input from the 3.5mm audio line in jacks (J1A, J1B, J2A, J2B)
and audio out can be heard from audio line out jack (J3A).

- MCASP RX is configured in TDM8 mode to receive from the 2xPCM6240
- MCASP TX is configured in I2S mode to transmit to TAD5212
- MCASP is configured as the clock master with external clock sourced from CDCE6214

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcasp/mcasp_multichannel_playback |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[MCASP](../../components/drivers/mcasp_v1.md)

## Sample Output

Shown below is a sample output when the application is run,

```
[MCASP] Audio playback example started.
Enter your response on UART terminal
Stop the demo? (y/n) : y
```

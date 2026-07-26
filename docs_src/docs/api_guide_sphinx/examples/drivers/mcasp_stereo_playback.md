# MCASP Stereo Playback

## Introduction

This example demonstrates the McASP configured for stereo audio playback mode
of operation. Audio can be input from the 3.5mm audio line in jack (J2 Top)
and audio out can be heard from audio line out jack (J3 Top).

- MCASP RX is configured in TDM2 mode to receive from the PCM6240
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

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcasp/mcasp_stereo_playback |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[MCASP](../../components/drivers/mcasp.md)

## Sample Output

Shown below is a sample output when the application is run,

```
[MCASP] Audio playback example started.
Enter your response on UART terminal
Stop the demo? (y/n) : y
```

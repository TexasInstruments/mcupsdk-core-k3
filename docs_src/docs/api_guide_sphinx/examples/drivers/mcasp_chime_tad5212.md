# MCASP Chime

## Introduction

This example demonstrates audio chime.

A headset needs to be connected to the audio jack J3 Top {{ VAR_BOARD_NAME_LOWER }} for hearing the audio.

- MCASP is configured in I2S mode
- Audio chime is played on both channels (Left and Right)

## Supported Combinations

::::{only} SOC_AM62DX or SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcasp/mcasp_chime_tad5212 |

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
Starting Chime
Chime completed
```

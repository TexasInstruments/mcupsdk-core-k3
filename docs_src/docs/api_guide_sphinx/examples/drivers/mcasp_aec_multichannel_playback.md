# MCASP AEC Multichannel Playback

## Introduction

This example demonstrates the multichannel playback using Audio Expansion Card.

- The AEC board needs to be powered with a DC Supply voltage of typical 14.4V across PVDD & GND

::::{only} SOC_AM62DX
- Make the PORZ_SELECT Switch 'S1' on AEC in 'PORZ' position
::::

::::{only} SOC_AM275X
- Make the PORZ_SELECT Switch 'S1' on AEC in 'RESET STATZ' position
::::

- Power ON the Power Supply first and then the {{ VAR_BOARD_NAME_LOWER }}

Speakers need to be connected to the 8 channel audio out on each card connected to AEC1 & AEC2 slots on {{ VAR_BOARD_NAME_LOWER }} for hearing the audio.

- MCASP is configured in TDM mode with 8 slots for each instance
- Audio out is played on 8 channels of each, thus 16 channels in total

## Supported Combinations

::::{only} SOC_AM62DX or SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcasp/mcasp_aec_multichannel_playback |

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
[MCASP] AEC Audio playback example started.
Enter your response on UART terminal
Stop the demo? (y/n) : y
```

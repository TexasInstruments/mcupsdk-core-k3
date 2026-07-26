# CALCRATIO

## Introduction

This example demonstrates real-time clock-ratio estimation between two asynchronous audio clocks (e.g., a 32 kHz receiver and a 48 kHz transmitter). The estimated ratio is periodically updated and fed to the SW ASRC (Software Asynchronous Sample-Rate Converter) so that the receiver can resample the incoming stream without clicks or drift.

Every 0.5 s a timer tick triggers the capture of:
- Rx Sample Counter — number of samples consumed by the MCASP-Rx (32 kHz domain)
- Tx Sample Counter — number of samples produced by the MCASP-Tx (48 kHz domain)
- MCASP is configured in 32 bit data format

:::{admonition} Note
- This demo does not perform actual audio streaming or sample-rate conversion.
- Ensure that the McASP RX and TX DMA configurations use the same DMA transfer size, including the loop-job buffer.
:::

## System Flow Overview

```{figure} ../../images/examples/calcratio.png
:align: center

CalcRatio DMA Counter Flow Overview
```

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/signal_processing/calcratio |

::::

::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/signal_processing/calcratio |

::::

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
```

::::

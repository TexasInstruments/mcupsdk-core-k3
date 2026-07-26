# TISP Real-Time Audio Signal Chain: 8 Channels to 12 Channels Example

:::{admonition} Warning
**EXPERIMENTAL FEATURE DISCLAIMER:** TISP library and associated examples are experimental. Provided for evaluation purposes only. Texas Instruments does not offer official support for TISP at this time.
:::

## Introduction

This example demonstrates a real-time audio signal processing chain converting 8 input audio channels to 12 output channels through gain control, filtering, equalization, delay, balance/fader, limiting, and muting stages.

:::{admonition} Known Issues
Non-zero delay leads to incorrect values. Set delay to 0 for proper operation.
:::

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/tisp/sigchain_dsp_rt/sigchain_8ch_to_12ch_audio_chain |

::::

::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/tisp/sigchain_dsp_rt/sigchain_8ch_to_12ch_audio_chain |

::::

## Steps to Run the Example

- **Using CCS Projects:** Import the system CCS project and build it (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **Using Makefiles:** Build using the `make` command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)).
- Load and run the compiled binary on the DSP Core (C75) and the R5F0 Core.

## See Also

[Signal Processing](../examples_signal_processing.rst)

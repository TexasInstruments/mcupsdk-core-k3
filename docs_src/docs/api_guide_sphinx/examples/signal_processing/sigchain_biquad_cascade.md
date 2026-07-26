# TISP Real-Time Signal Chain: Cascade Biquad Parametric EQ Example

:::{admonition} Warning
**EXPERIMENTAL FEATURE DISCLAIMER:** TISP library and associated examples are experimental. Provided for evaluation purposes only. Texas Instruments does not offer official support for TISP at this time.
:::

## Introduction

This example demonstrates a simple real-time parametric equalization signal processing chain using TISP running on the DSP Core (C75). The example showcases a 3-stage cascade biquad filter implementation for parametric EQ processing.

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/tisp/sigchain_dsp_rt/sigchain_biquad_cascade |

::::

::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/tisp/sigchain_dsp_rt/sigchain_biquad_cascade |

::::

## Steps to Run the Example

- **Using CCS Projects:** Import the system CCS project and build it (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all dependent CPU projects as well.
- **Using Makefiles:** Build the system makefile using the `make` command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)).
- Load and run the compiled binary on the DSP Core (C75) and the R5F0 Core.

## See Also

[Signal Processing](../examples_signal_processing.rst)

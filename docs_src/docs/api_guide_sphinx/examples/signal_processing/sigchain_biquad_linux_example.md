# TISP Linux Real-Time Signal Chain: Cascade Biquad Parametric EQ Example

:::{admonition} Warning
**EXPERIMENTAL FEATURE DISCLAIMER:** TISP library and associated examples are experimental. Provided for evaluation purposes only. Texas Instruments does not offer official support for TISP at this time.
:::

## Introduction

This example demonstrates real-time parametric equalizer processing using a 3-stage biquad cascade signal chain on the C7x DSP with dynamic EQ on/off control from Linux.

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/tisp/sigchain_dsp_rt/sigchain_biquad_cascade/am62dx-evm/c75ss0-0_freertos_linux |

::::

## Steps to Run the Example

- **Build DSP Firmware:** Import and build the CCS project from `examples/tisp/sigchain_dsp_rt/sigchain_biquad_cascade/am62dx-evm/c75ss0-0_freertos_linux/ti-c7000/`
- **Build Linux Application:** Clone and build from `https://github.com/TexasInstruments/rpmsg-dma`
- Run `./rpmsg_sigchain_biquad_example` on the AM62DX board running Linux

## See Also

[Signal Processing](../examples_signal_processing.rst)

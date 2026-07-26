# TISP Real-Time Signal Chain Examples

:::{admonition} Warning
**EXPERIMENTAL FEATURE DISCLAIMER:** TISP (Texas Instruments Signal Processing) library and associated examples are currently in experimental versions. These are provided for evaluation and development purposes only. Texas Instruments does not offer official support for TISP at this time. Use at your own discretion.
:::

## Introduction

The TISP Real-Time Signal Chain examples demonstrate audio processing on the C75x DSP core using the TISP middleware library. These examples showcase how to build audio-processing pipelines with various DSP operations and signal routing capabilities.

## Common Architecture

All examples use a dual-core architecture:
- **C75x DSP Core:** Performs intensive signal-processing computations and configures the McASP
- **R5F Core:** Handles codec configuration and IPC communication
- **Audio I/O:** McASP with UDMA places and reads data to/from L2SRAM of the C75x DSP
- **Triple buffering:** Input and output are triple buffered for streaming data
- **Sampling rate:** 48kHz
- **Block Size:** 64

All signal chains follow a common pattern:

**Audio Input → Type Conversion (int32→float) → [Processing Nodes] → Type Conversion (float→int32) → Audio Output**

## Signal Chain Examples Overview

::::{only} SOC_AM62DX or SOC_AM275X

```{toctree}
:maxdepth: 1
:hidden:
:titlesonly:

sigchain_biquad_cascade
sigchain_eq_gain_mute
sigchain_router_8ch_12ch
sigchain_8ch_to_12ch_audio_chain
```

- [Cascade Biquad Parametric EQ](sigchain_biquad_cascade.md)
- [EQ, Gain, and Mute](sigchain_eq_gain_mute.md)
- [Router with Advanced DSP Processing (8ch to 12ch)](sigchain_router_8ch_12ch.md)
- [8 Channels to 12 Channels Audio Chain](sigchain_8ch_to_12ch_audio_chain.md)

::::

::::{only} SOC_AM62DX

```{toctree}
:maxdepth: 1
:hidden:
:titlesonly:

sigchain_biquad_linux_example
```

- [Cascade Biquad Parametric EQ (Linux)](sigchain_biquad_linux_example.md)

::::

## Getting Started

- **Using CCS Projects:** Import the system CCS project and build it (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **Using Makefiles:** Build using the `make` command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)).

## See Also

[Signal Processing](../examples_signal_processing.rst)

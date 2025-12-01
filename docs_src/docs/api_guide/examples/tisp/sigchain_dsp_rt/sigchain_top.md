# TISP Real-Time Signal Chain Examples {#EXAMPLES_TISP_SIGCHAIN_TOP}

[TOC]

\warning **EXPERIMENTAL FEATURE DISCLAIMER:** TISP (Texas Instruments Signal Processing) library and associated examples are currently in experimental versions. These are provided for evaluation and development purposes only. Texas Instruments does not offer official support for TISP at this time. Use at your own discretion.

# Introduction

The TISP (Texas Instruments Signal Processing) Real-Time Signal Chain examples demonstrate audio processing on the C75x DSP core using the TISP middleware library. These examples showcase how to build audio-processing pipelines with various DSP operations and signal routing capabilities.

# TISP Signal Chain Architecture

The TISP middleware provides a framework for constructing signal-processing pipelines on the C75x DSP, where multiple DSP operations are connected sequentially. Each operation (or "node") processes signal data and passes it to the next node in the chain, enabling complex signal transformations in real-time.

Key characteristics of TISP signal chains:
- **Sequential Processing:** Operations execute in a defined order through the chain
- **Optimized for C75x DSP:** Leverages DSP-specific optimizations for real-time signal streaming via AUDIOLIB, DSPLIB, and FFTLIB
- **Modular Node Design:** Individual processing nodes can be configured and combined flexibly
- **Floating-Point Processing:** High-precision 32-bit floating-point operations for signal quality

# Common Architecture

All examples use a dual-core architecture:
- **C75x DSP Core:** Performs intensive signal-processing computations and configuring the McASP
- **R5F Core:** Handles codec configuration and IPC communication
- **Audio I/O:** McASP with UDMA places and reads data to and from L2SRAM of the C75x DSP  for real-time, low-latency, high-throughput audio processing
- **Triple buffering:** Input and output are triple buffered for streaming data and processing the same in parallel
- **Sampling rate:** 48kHz
- **Block Size:** 64


All signal chains follow a common pattern:

**Audio Input → Type Conversion (int32→float) → [Processing Nodes] → Type Conversion (float→int32) → Audio Output**

Type conversions enable high-precision floating-point processing while maintaining compatibility with hardware audio interfaces.

# Signal Chain Examples Overview

The following examples demonstrate progressively complex signal chains, from simple filtering to comprehensive audio processing pipelines.

## 1. Cascade Biquad Parametric EQ 
\subpage EXAMPLES_TISP_SIGCHAIN_BIQUAD_CASCADE

**Complexity:** Simple (3 processing nodes)

A straightforward parametric equalization example demonstrating 3-stage cascade biquad filtering.

**Signal Chain:**
```
Input (8-ch, int32) → TypeConv → CascadeBiquad (3-stage EQ) → TypeConv → Output (8-ch, int32)
```

**Key Features:**
- 3-stage parametric EQ using cascade biquad filters
- Multi-channel processing
- Configurable filter coefficients

## 2. EQ, Gain, and Mute
\subpage EXAMPLES_TISP_SIGCHAIN_EQ_GAIN_MUTE

**Complexity:** Simple (5 processing nodes)

Combines parametric EQ with per-channel gain control and smooth muting capabilities.

**Signal Chain:**
```
Input (8ch, int32) → TypeConv → EQ → Gain → Mute → TypeConv → Output (8ch, int32)
```

**Key Features:**
- 3-stage parametric equalization
- Independent per-channel gain control
- Smooth fade-in/fade-out muting
- 8-channel audio processing at 48 kHz

## 3. Router with FFT/IFFT DSP Processing (8ch to 12ch)
\subpage EXAMPLES_TISP_SIGCHAIN_ROUTER_8CH_12CH

**Complexity:** Moderate (10 processing nodes)

Demonstrates comprehensive DSP techniques including IIR/FIR filtering, FFT processing, and channel routing.

**Signal Chain:**
```
Input (8ch, int32) → TypeConv → Biquad0 → Biquad1 → MatTrans → FIR →
RFFT → IFFTR → MatTrans → Router → TypeConv → Output (12ch, int32)
```

**Key Features:**
- Dual cascade biquad filters (6 total biquad stages)
- 64-tap FIR filter for linear phase filtering
- FFT/IFFT for frequency domain processing
- Matrix transpose operations for data optimization
- Channel expansion from 8 to 12 channels
- Configurable channel routing matrix

---

## 4. Comprehensive Audio Chain (8ch to 12ch)
\subpage EXAMPLES_TISP_SIGCHAIN_8CH_TO_12CH_AUDIO_CHAIN

**Complexity:** Moderate (11 processing nodes)

Signal chain combining multiple audio-processing operations.

**Signal Chain:**
```
Input (8ch, int32) → TypeConv → Gain → HPF → Router → EQ → Delay →
Balance/Fader → Trim → Limiter → Mute → TypeConv → Output (12ch, int32)
```

**Key Features:**
- Fragment of typical automotive audio-processing pipeline
- High-pass filtering to remove DC and low-frequency noise
- Channel routing and expansion (8 → 12 channels)
- Parametric EQ for speaker tuning
- Per-channel delay for time alignment (known issues, delay=0 for now)
- Balance/Fader for spatial audio control
- Trim gains and master volume control
- Soft-knee limiter for clipping prevention
- Smooth per-channel muting

**Known Issues:**
- Conducted minimal validation
  - Qualitative validation of output audio stream via frequency analysis with Audacity
- Non-zero delay does not work

# Getting Started

## Building and Running

All examples use CCS projects or Makefiles and run on dual-core architecture (C75x DSP + R5F). Refer to individual example documentation for detailed build instructions, hardware requirements, and configuration parameters.

## Input Audio and Monitor the output
In the examples, the input is a chirp played from Audacity whose spectrum is as shown below.

\image html TISP_input_chirp_spectrum.png "Input spectrum of chirp signal from Audacity" width=1000px

The Audio I/O configuration is as shown below:
   - Input audio stream into stereo jacks J2 and/or J1
     - J2 top:  channels 0 and 4
	 - J2 bottom: channels 1 and 5
	 - J1 top: channels 2 and 6
	 - J1 bottom: channels 3 and 7
   - Output audio stream monitored via stereo jacks J3 and/or J4
     - J3 top:  channels 0 and 4
	 - J3 bottom: channels 1 and 5
	 - J4 top: channels 2 and 6
	 - J4 bottom: channels 3 and 7

# See Also

- \ref EXAMPLES_TISP_SIGCHAIN_BIQUAD_CASCADE
- \ref EXAMPLES_TISP_SIGCHAIN_EQ_GAIN_MUTE
- \ref EXAMPLES_TISP_SIGCHAIN_ROUTER_8CH_12CH
- \ref EXAMPLES_TISP_SIGCHAIN_8CH_TO_12CH_AUDIO_CHAIN

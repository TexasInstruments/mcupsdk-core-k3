# TISP Real-Time Audio Signal Chain: 8 Channels to 12 Channels Example {#EXAMPLES_TISP_SIGCHAIN_8CH_TO_12CH_AUDIO_CHAIN}

[TOC]

\warning **EXPERIMENTAL FEATURE DISCLAIMER:** TISP (Texas Instruments Signal Processing) library and associated examples are currently in experimental versions. These are provided for evaluation and development purposes only. Texas Instruments does not offer official support for TISP at this time. Use at your own discretion.

# Introduction

This example demonstrates a real-time audio signal processing chain using TISP (Texas Instruments Signal Processing) library running on the DSP Core (C75). The example showcases an 8-channel to 12-channel audio-processing pipeline that includes various audio effects such as gain control, filtering, equalization, delay, balance/fader, limiting, and muting capabilities.

The signal chain processes audio data in real-time, converting 8 input audio channels to 12 output channels through a series of processing stages optimized for DSP execution. 

## Known Issues
1. Non-zero delay leads to incorrect values (delay should be set to 0 for proper operation).

## Example Workflow

1. **Signal Chain Initialization:**
   - The `create_graph()` function initializes all processing nodes in the signal chain.
   - Memory buffers are allocated for intermediate data storage.
   - Filter coefficients, gain values, and other parameters are configured.

2. **Real-Time Processing:**
   - Input audio data (8 channels, int32_t format) is received.
   - The `execute_graph()` function processes data through the entire signal chain.
   - Each processing node operates on the data sequentially.
   - Output audio data (12 channels, int32_t format) is generated.

3. **Processing Pipeline:**
   - **Type Conversion:** Converts input from int32_t to float for DSP processing.
   - **Gain Control:** Applies target gain to each input channel.
   - **High-Pass Filter:** Removes low-frequency content using cascade biquad filter.
   - **Channel Router:** Expands 8 input channels to 12 output channels.
   - **Parametric EQ:** Applies speaker equalization using cascade biquad filter.
   - **Delay:** Applies configurable per-channel delay.
   - **Balance/Fader:** Implements balance and fader controls for spatial audio.
   - **Trim Gain:** Applies per-channel trim gains and master volume.
   - **Limiter:** Prevents clipping through dynamic range compression.
   - **Mute Control:** Enables smooth fade-in/fade-out muting.
   - **Type Conversion:** Converts output from float back to int32_t.
   
The frequency response of the parametric equalizer is as shown below.
\image html TISP_pe_frequency.png "Frequency response of parametric filter (cascade biquad)" width=1000px
   

## Signal Chain Details

The audio processing signal chain consists of 11 processing nodes executed sequentially:

\image html TISP_8ch_to_12ch_audio_signal_chain.svg "Signal chain" width=90%

### Processing Stages

1. **TypeConversion (int32 → float):** Converts 8-channel input data from int32_t to float format for processing.

2. **GainNCh:** Applies target gain (0.5) to all 8 input channels for level control.

3. **CascadeBiquad (HPF):** 3-stage cascade biquad high-pass filter removes unwanted low-frequency content from all 8 channels.

4. **Router (8ch → 12ch):** Routes and duplicates the 8 input channels to 12 output channels based on configuration mapping.

5. **CascadeBiquad (Parametric EQ):** 3-stage cascade biquad filter applies parametric equalization for speaker tuning across all 12 channels.

6. **DelayNCh:** Applies per-channel delay compensation (configurable up to maximum delay) for time alignment of speakers.

7. **BalanceFader:** Implements balance (left-right) and fader (front-rear) controls for spatial audio positioning across the 12 channels.

8. **GainNChTrim:** Applies individual channel gains (0.9) and master gain (0.95) for final volume adjustment.

9. **Limiter:** Soft-knee limiter with configurable threshold (-3 dB), knee width (6 dB), attack, and release coefficients prevents clipping.

10. **MuteNCh:** Per-channel mute control with smooth fade-in/fade-out transitions to avoid audible artifacts.

11. **TypeConversion (float → int32):** Converts processed 12-channel output from float back to int32_t format.

### Key Features

- **Real-time processing:** Optimized for low-latency audio processing on C75 DSP core
- **Channel expansion:** Routing from 8 input channels to 12 output channels
- **Comprehensive audio processing:** Includes filtering, EQ, dynamics, spatial control, and level management
- **Configurable parameters:** All processing parameters can be adjusted dynamically
- **Professional audio quality:** Uses floating-point processing for high-precision audio

# Supported Combinations

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 ^              | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang and ti-C7000-CGT
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/tisp/sigchain_dsp_rt/sigchain_8ch_to_12ch_audio_chain

\endcond

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 ^              | r5fss0-0 freertos 
 Toolchain      | ti-arm-clang and ti-C7000-CGT
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/tisp/sigchain_dsp_rt/sigchain_8ch_to_12ch_audio_chain

\endcond

# Steps to Run the Example

## Build the Example

- **Using CCS Projects:** Import the system CCS project and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). This will build all dependent CPU projects as well.
- **Using Makefiles:** Build the system makefile using the `make` command (see \ref MAKEFILE_BUILD_PAGE). This will build all dependent CPU makefiles as well.

## Run the Example

1. **Load and run the application:**
   - Load and run the compiled binary on the DSP Core (C75).
   - Load and run the compiled binary on the R5F0.
   - The application will initialize the signal chain and begin processing audio frames.

2. **Monitor the output:**
   - The example processes audio data in real-time through the 11-stage processing pipeline.
   - Performance metrics including cycle count and DSP load are measured and reported.

3. **Audio Flow:**
   - Input: 8 channels of audio data (int32_t format)
   - Processing: Real-time execution through all 11 processing stages
   - Output: 12 channels of processed audio data (int32_t format)

## Configuration Parameters

The example includes configurable parameters for each processing stage:

- **Gain:** Target gain values for input channels (default: 0.5)
- **HPF Coefficients:** High-pass filter biquad coefficients for 3 stages
- **Router Configuration:** Channel mapping from 8 inputs to 12 outputs
- **EQ Coefficients:** Parametric EQ biquad coefficients for 3 stages
- **Delay Sizes:** Per-channel delay values (default: 0)
- **Balance/Fader:** Balance, fader, and channel configuration parameters
- **Trim Gains:** Per-channel gains (default: 0.9) and master gain (default: 0.95)
- **Limiter:** Threshold (-3 dB), knee width (6 dB), attack/release coefficients (0.9)
- **Mute:** Per-channel mute state (default: all unmuted)

# Sample Output
Input is a chirp waveform from Audacity with the following parameters:
- 200Hz to 10kHz with linear interpolation of frequency
- Amplitude of 0.6

The output spectrum of the audio stream is as shown below, which was captured using Audacity.

\image html TISP_8ch_to_12ch_audio_chain.png "Output spectrum" width=1000px

The output waveform captured via Audacity is as shown below for reference.
\image html TISP_8ch_to_12ch_audio_chain_wave.png "Output waverform" width=1000px

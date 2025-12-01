# TISP Real-Time Signal Chain: EQ, Gain, and Mute Example {#EXAMPLES_TISP_SIGCHAIN_EQ_GAIN_MUTE}

[TOC]

\warning **EXPERIMENTAL FEATURE DISCLAIMER:** TISP (Texas Instruments Signal Processing) library and associated examples are currently in experimental versions. These are provided for evaluation and development purposes only. Texas Instruments does not offer official support for TISP at this time. Use at your own discretion.


# Introduction

This example demonstrates a real-time audio signal processing chain using TISP (Texas Instruments Signal Processing) middleware library running on the DSP Core (C75). The example showcases a typical audio processing pipeline that combines parametric equalization, per-channel gain control, and smooth muting capabilities.

The signal chain processes multi-channel audio data in real-time, applying equalization, gain adjustment, and mute control optimized for DSP execution.



## Example Workflow

1. **Signal Chain Initialization:**
   - The `create_graph()` function initializes all processing nodes in the signal chain.
   - Memory buffers are statically allocated for intermediate data storage.
   - Filter coefficients, gain values, and mute parameters are configured.

2. **Real-Time Processing:**
   - Input audio data (8 channels, int32_t format) is received via McASP+UDMA and placed in L2SRAM of the C7x.
   - The `execute_graph()` function processes data through the entire signal chain.
   - Each processing node operates on the data sequentially.
   - Output audio data (8 channels, int32_t format) is generated and placed in L2SRAM of the C7x for UDMA+McASP transmission.
   - Input and output are triple buffered for streaming data and processing the same in parallel.

3. **Processing Pipeline:**
   - **Type Conversion:** Converts input from int32_t to float for DSP processing.
   - **Parametric EQ:** Applies 3-stage parametric equalization using cascade biquad filter.
   - **Gain Control:** Applies per-channel gain adjustment.
   - **Mute Control:** Enables smooth fade-in/fade-out muting per channel.
   - **Type Conversion:** Converts output from float back to int32_t.

## Signal Chain Details

The audio processing signal chain consists of 5 processing nodes executed sequentially:

\image html TISP_pe_gain_mute.svg "Signal chain" width=75%

### Processing Stages

1. **TypeConversion (int32 → float):** Converts 8-channel input data from int32_t to float format for processing.

2. **CascadeBiquad (Parametric EQ):** 3-stage cascade biquad filter implementing parametric equalization:
   - Uses Direct Form I (DF1) biquad implementation
   - Applies frequency-dependent gain adjustment
   - Processes all 8 channels independently with the same filter coefficients
   - Sample rate: 48 kHz
   - Figure below shows the frequency response of the parametric equalizer employed via casacade biquad.
   \image html TISP_pe_frequency.png "Frequency response of cascade biquad filter" width=750px


3. **GainNCh:** Applies per-channel gain control:
   - Independent gain for each of the 8 channels
   - Default gains: [0.8, 1.0, 0.2, 0.5, 1.0, 1.3, 1.4, 1.5]
   - Enables level balancing across channels

4. **MuteNCh:** Per-channel mute control with smooth transitions:
   - Supports independent mute state for each channel
   - Smooth fade-in/fade-out to avoid audible clicks
   - Configurable fade time and transition type
   - Sample rate: 48 kHz
   - All channels unmuted by default

5. **TypeConversion (float → int32):** Converts processed 8-channel output from float back to int32_t format.

### Key Features

- **Real-time processing:** Optimized for low-latency audio processing on C75 DSP core
- **Comprehensive signal chain:** Combines EQ, gain, and mute in a single pipeline
- **Per-channel control:** Independent processing parameters for each audio channel


# Supported Combinations

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 ^              | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang and ti-C7000-CGT
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/tisp/sigchain_dsp_rt/sigchain_eq_gain_mute

\endcond

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 ^              | r5fss0-0 freertos 
 Toolchain      | ti-arm-clang and ti-C7000-CGT
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/tisp/sigchain_dsp_rt/sigchain_eq_gain_mute

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
   - The example processes audio data in real-time through the 5-stage processing pipeline.
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

3. **Audio Flow:**
   - Input: 8 channels of audio data (int32_t format)
   - Processing: Real-time execution through EQ → Gain → Mute stages
   - Output: 8 channels of processed audio data (int32_t format)

## Configuration Parameters

The example includes configurable parameters for each processing stage:

- **Parametric EQ Coefficients:** 3-stage cascade biquad coefficients
  - Each stage has 5 coefficients (b0, b1, b2, a1, a2)
  - Total of 15 coefficients for the 3-stage filter

- **Per-Channel Gains:** Individual gain values for each of 8 channels
  - Channel 0: 0.8
  - Channel 1: 1.0
  - Channel 2: 0.2
  - Channel 3: 0.5
  - Channel 4: 1.0
  - Channel 5: 1.3
  - Channel 6: 1.4
  - Channel 7: 1.5

- **Mute Parameters:**
  - Initial gain: 1.0 (all channels)
  - Target gain: 1.0 (all channels)
  - Mute state: 0 (unmuted) for all channels
  - Fade time: 0.0 seconds
  - Sample rate: 48 kHz

# Sample Output

Input is a chirp waveform from Audacity with the following parameters:
- 200Hz to 10kHz with linear interpolation of frequency
- Amplitude of 0.6

The output spectrum of the audio stream is as shown below, which was captured using Audacity.

\image html TISP_pe_gain_mute.png "Output spectrum" width=50%


Also, it can be noted that the output waveform's amplitude is diminished based on the gain value.

\image html TISP_pe_gain_mute_wave.png "Output waverform" width=50%


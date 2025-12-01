# TISP Real-Time Signal Chain: Router with Advanced DSP Processing (8ch to 12ch) Example {#EXAMPLES_TISP_SIGCHAIN_ROUTER_8CH_12CH}

[TOC]

\warning **EXPERIMENTAL FEATURE DISCLAIMER:** TISP (Texas Instruments Signal Processing) library and associated examples are currently in experimental versions. These are provided for evaluation and development purposes only. Texas Instruments does not offer official support for TISP at this time. Use at your own discretion.

# Introduction

This example demonstrates a real-time audio signal processing chain using TISP (Texas Instruments Signal Processing) library running on the DSP Core (C75). The example showcases a comprehensive processing pipeline that combines multiple filtering stages, frequency domain processing using FFT/IFFT, and channel routing from 8 input channels to 12 output channels. Input and output sampling rate are set to 48kHz.

The signal chain processes audio data in real-time through cascade biquad filters, FIR filtering, FFT-based processing, and intelligent channel routing optimized for DSP execution.

## Example Workflow

1. **Signal Chain Initialization:**
   - The `create_graph()` function initializes all processing nodes in the signal chain.
   - Memory buffers are allocated for intermediate data storage.
   - Filter coefficients (biquad and FIR) and router configuration are set up.

2. **Real-Time Processing:**
   - Input audio data (8 channels, int32_t format) is received.
   - The `execute_graph()` function processes data through the entire signal chain.
   - Each processing node operates on the data sequentially.
   - Output audio data (12 channels, int32_t format) is generated.

3. **Processing Pipeline:**
   - **Type Conversion:** Converts input from int32_t to float for DSP processing.
   - **Cascade Biquad Filters:** Two stages of 3-stage cascade biquad filters.
   - **Matrix Transpose:** Prepares data for FIR processing.
   - **FIR Filter:** Applies 64-tap FIR filter for frequency shaping.
   - **FFT Processing:** Real FFT for frequency domain analysis.
   - **IFFT Processing:** Inverse FFT to convert back to time domain.
   - **Matrix Transpose:** Restores data organization.
   - **Channel Router:** Expands 8 channels to 12 channels.
   - **Type Conversion:** Converts output from float back to int32_t.

## Signal Chain Details

The audio processing signal chain consists of 10 processing nodes executed sequentially:

\image html TISP_router_8ch_to_12ch.svg "Signal Chain" width=100%

### Processing Stages

1. **TypeConversion (int32 → float):** Converts 8-channel input data from int32_t to float format for processing.

2. **CascadeBiquad0 (First Filter):** 3-stage cascade biquad filter implementing the first filtering stage:
   - Uses Direct Form I (DF1) biquad implementation
   - Configured for 5kHz low-pass filtering
   - Processes all 8 channels independently

3. **CascadeBiquad1 (Second Filter):** 3-stage cascade biquad filter implementing the second filtering stage:
   - Provides additional frequency shaping
   - Configured for 500Hz high-pass filtering
   - Cascaded after the first filter for more complex frequency response

4. **MatrixTranspose:** Transposes the data matrix to prepare for FIR filtering:
   - Converts from channel-interleaved to time-interleaved format
   - Optimizes data access patterns for subsequent FIR processing

5. **FIR Filter:** 64-tap finite impulse response filter:
   - Implements linear phase filtering
   - Provides precise frequency response control
   - Processes all channels with the same filter coefficients
   - Low-pass filter with cutoff frequency of 3kHz

6. **RFFT (Real FFT):** 1D batched real FFT:
   - Transforms time-domain signals to frequency domain
   - Processes all channels in batched mode for efficiency

7. **IFFTR (Inverse Real FFT):** 1D batched inverse real FFT:
   - Converts frequency-domain signals back to time domain
   - Completes the FFT round-trip processing
   - Restores temporal information

8. **MatrixTranspose:** Transposes back to original data organization:
   - Converts from time-interleaved back to channel-interleaved format
   - Prepares data for channel routing

9. **Router (8ch → 12ch):** Channel routing and expansion:
   - Routes 8 input channels to 12 output channels
   - Default mapping: channels 0-7 → outputs 0-7, channels 0-3 duplicated → outputs 8-11
   - Configurable routing matrix for flexible channel assignment

10. **TypeConversion (float → int32):** Converts processed 12-channel output from float back to int32_t format.

### Key Features

- **Real-time processing:** Optimized for low-latency audio processing on C75 DSP core
- **Comprehensive filtering:** Multiple cascade biquad stages plus FIR filtering
- **FFT processing:** Enables frequency-domain manipulation capabilities
- **Channel expansion:** Routing from 8 to 12 channels

### Filter Configurations

The example includes:
- **2x Cascade Biquad Filters:** Each with 3 stages (6 biquad stages total)
- **64-tap FIR Filter:** Linear phase filtering with precise frequency control
- **FFT/IFFT Processing:** For frequency domain operations

# Supported Combinations

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 ^              | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang and ti-C7000-CGT
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/tisp/sigchain_dsp_rt/sigchain_router_8ch_12ch

\endcond

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 ^              | r5fss0-0 freertos 
 Toolchain      | ti-arm-clang and ti-C7000-CGT
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/tisp/sigchain_dsp_rt/sigchain_router_8ch_12ch

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
   - The example processes audio data in real-time through the 10-stage processing pipeline and monitored via Audacity.


3. **Audio Flow:**
   - Input: 8 channels of audio data (int32_t format)
   - Processing: Real-time execution through the DSP pipeline
   - Output: 12 channels of processed audio data (int32_t format)

## Configuration Parameters

The example includes configurable parameters for each processing stage:

- **Cascade Biquad 0 Coefficients:** 3-stage filter (15 coefficients)
- **Cascade Biquad 1 Coefficients:** 3-stage filter (15 coefficients)
- **FIR Filter Coefficients:** 64 taps for linear phase filtering
- **FFT Size:** Configurable based on block size
- **Router Configuration:** Channel mapping from 8 inputs to 12 outputs
  - Default: [0,1,2,3,4,5,6,7,0,1,2,3]
  - Channels 0-7 pass through, channels 0-3 duplicated to outputs 8-11

# Sample Output

Input is a chirp waveform from Audacity with the following parameters:
- 200Hz to 10kHz with linear interpolation of frequency
- Amplitude of 0.6

The output spectrum of the audio stream is as shown below, which was captured using Audacity.

\image html TISP_router_8ch_12ch.png "Output Spectrum" width=1000px


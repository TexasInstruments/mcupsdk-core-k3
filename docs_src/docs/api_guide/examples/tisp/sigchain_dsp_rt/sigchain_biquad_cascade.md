# TISP Real-Time Signal Chain: Cascade Biquad Parametric EQ Example {#EXAMPLES_TISP_SIGCHAIN_BIQUAD_CASCADE}

[TOC]

# Introduction

This example demonstrates a simple real-time parametric equalization signal processing chain using TISP (Texas Instruments Signal Processing) libraries running on the DSP Core (C75). The example showcases a 3-stage cascade biquad filter implementation for parametric EQ processing.

The signal chain applies parametric equalization to multi-channel audio data in real-time, using cascade biquad filters optimized for DSP execution.

## Example Workflow

1. **Signal Chain Initialization:**
   - The `create_graph()` function initializes all processing nodes in the signal chain.
   - Memory buffers are allocated for intermediate data storage.
   - Filter coefficients for the 3-stage parametric EQ are configured.

2. **Real-Time Processing:**
   - Input audio data (multi-channel, int32_t format) is received.
   - The `execute_graph()` function processes data through the entire signal chain.
   - Each processing node operates on the data sequentially.
   - Output audio data (multi-channel, int32_t format) is generated.

3. **Processing Pipeline:**
   - **Type Conversion:** Converts input from int32_t to float for DSP processing.
   - **Cascade Biquad Parametric EQ:** Applies 3-stage parametric equalization filter.
   - **Type Conversion:** Converts output from float back to int32_t.

## Signal Chain Details

The parametric EQ signal chain consists of 3 processing nodes executed sequentially:

**Input (N-ch, int32) → TypeConv → Cascade Biquad (3-stage Parametric EQ) → TypeConv → Output (N-ch, int32)**

### Processing Stages

1. **TypeConversion (int32 → float):** Converts multi-channel input data from int32_t to float format for processing.

2. **CascadeBiquad (Parametric EQ):** 3-stage cascade biquad filter implementing parametric equalization:
   - Uses Direct Form I (DF1) biquad implementation
   - Each stage can implement different EQ characteristics (peak, notch, shelving, etc.)
   - Coefficients define the frequency response, Q factor, and gain for each stage
   - Processes all channels independently

3. **TypeConversion (float → int32):** Converts processed multi-channel output from float back to int32_t format.

### Key Features

- **Real-time processing:** Optimized for low-latency audio processing on C75 DSP core
- **Parametric EQ:** Professional-grade 3-stage parametric equalization
- **Multi-channel support:** Processes multiple audio channels simultaneously
- **Configurable filters:** All filter coefficients can be adjusted dynamically
- **Floating-point precision:** Uses floating-point processing for high-quality audio

### Filter Characteristics

The example includes pre-configured 3-stage parametric EQ with:
- **Stage 1:** Peak/notch filter for frequency shaping
- **Stage 2:** Mid-frequency parametric control
- **Stage 3:** Additional parametric band for fine tuning

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
   - The application will initialize the signal chain and begin processing audio frames.

2. **Monitor the output:**
   - The example processes audio data in real-time through the 3-stage parametric EQ pipeline.
   - Performance metrics including cycle count and DSP load are measured and reported.

3. **Audio Flow:**
   - Input: N channels of audio data (int32_t format)
   - Processing: Real-time execution through 3-stage parametric EQ
   - Output: N channels of equalized audio data (int32_t format)

## Configuration Parameters

The example includes configurable parameters:

- **Filter Coefficients:** 3-stage cascade biquad coefficients for parametric EQ
  - Each stage has 5 coefficients (b0, b1, b2, a1, a2)
  - Total of 15 coefficients for the 3-stage filter
- **Number of Channels:** Configurable based on application requirements
- **Block Size:** Number of samples per frame to process

# Sample Output

```

```



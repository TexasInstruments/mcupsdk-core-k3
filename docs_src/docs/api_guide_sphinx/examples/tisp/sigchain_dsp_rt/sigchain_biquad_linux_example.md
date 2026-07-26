# TISP Linux Real-Time Signal Chain: Cascade Biquad Parametric EQ Example

:::::{only} SOC_AM62DX

::::{warning}
**EXPERIMENTAL FEATURE DISCLAIMER:** TISP (Texas Instruments Signal Processing) library and associated examples are currently in experimental versions. These are provided for evaluation and development purposes only. Texas Instruments does not offer official support for TISP at this time. Use at your own discretion.
::::

## Introduction

This example demonstrates real-time parametric equalizer processing using a 3-stage biquad cascade signal chain on the C7x DSP. The demo processes 8-channel audio at 48kHz with dynamic EQ on/off control from Linux and provides performance monitoring capabilities.

The signal chain applies parametric equalization to multi-channel audio data in real-time, using a cascade biquad filter, optimized for DSP execution.

### Example Workflow

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

### Signal Chain Details

The parametric EQ signal chain consists of 3 processing nodes executed sequentially:

```{figure} ../../../images/am62dx/TISP_cascadeBiquad.svg
:align: center
:width: 50%

**Signal chain**
```

#### Processing Stages

1. **TypeConversion (int32 → float):** Converts multi-channel input data from int32_t to float format for processing.

2. **CascadeBiquad (Parametric EQ):** 3-stage cascade biquad filter implementing parametric equalization:
   - Uses Direct Form I (DF1) biquad implementation
   - Each stage can implement different EQ characteristics (peak, notch, shelving, etc.)
   - Coefficients define the frequency response, Q factor, and gain for each stage
   - Processes all channels independently
   - Frequency response is as shown below

```{figure} ../../../images/am62dx/TISP_pe_frequency.png
:align: center
:width: 1000px

**Frequency response of cascade biquad filter**
```

3. **TypeConversion (float → int32):** Converts processed multi-channel output from float back to int32_t format.

### Key Features

- **Real-time processing:** Optimized for low-latency audio processing on C75 DSP core
- **Parametric EQ:** A 3-stage parametric equalization
- **Multi-channel support:** Processes multiple audio channels simultaneously
- **Floating-point precision:** Uses floating-point processing for high-quality audio

### Filter Characteristics

The example includes pre-configured 3-stage parametric EQ with:
- **Stage 1:** Low-shelf filter
- **Stage 2:** 1kHz notch filter
- **Stage 3:** High-shelf filter

The demo uses shared memory for Linux-DSP communication, enabling dynamic EQ on/off control and real-time performance monitoring.

## Supported Combinations

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos_linux |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/tisp/sigchain_dsp_rt/sigchain_biquad_cascade/am62dx-evm/c75ss0-0_freertos_linux |

## Steps to Run the Example

### Build the DSP Firmware

- **When using CCS projects to build**, import the CCS project from:
  `examples/tisp/sigchain_dsp_rt/sigchain_biquad_cascade/am62dx-evm/c75ss0-0_freertos_linux/ti-c7000/`
- **When using makefiles to build**, build using make command:
  ```bash
  cd examples/tisp/sigchain_dsp_rt/sigchain_biquad_cascade/am62dx-evm/c75ss0-0_freertos_linux/ti-c7000/
  make clean && make
  ```
- This generates `sigchain_biquad_cascade.c75ss0-0.release.strip.out` firmware file

### Build the Linux Application

The Linux application is part of the rpmsg-dma framework.

**Repository:** https://github.com/TexasInstruments/rpmsg-dma

```bash
# Clone and build from rpmsg-dma repository:
git clone https://github.com/TexasInstruments/rpmsg-dma.git
cd rpmsg-dma
mkdir build && cd build
cmake ..
make
```

### Run the Example

1. **Deploy DSP firmware to the Linux target:**
   ```bash
   # The DSP firmware is already packaged and available in the Linux image.
   # If using custom firmware, copy the DSP firmware to /lib/firmware/ directory on AM62DX board running Linux
   scp sigchain_biquad_cascade.c75ss0-0.release.strip.out root@<board_ip>:/lib/firmware/
   ```

2. **Run the Linux application on AM62DX board:**
   ```bash
   ./rpmsg_sigchain_biquad_example
   ```
3. **Monitor the output:**
   ```bash
   python3 rpmsg_sigchain_biquad_example.py <board_ip>
   ```
   - The python GUI shows DSP load, cycle count, and throughput metrics in real-time.

4. **Audio Flow:**
   - Input: Eight channels of audio data (int32_t format)
   - Processing: Real-time execution through 3-stage parametric EQ
   - Output: Eight channels of equalized audio data (int32_t format)

## Hardware Setup

1. **Audio Connections:**
   - Connect audio input source to EVM's MCASP input (PCM6240-Q1 codec)
   - Connect audio output to speakers/headphones via EVM's MCASP output
   - Ensure codec configuration for 48kHz, 8-channel operation

2. **DSP Firmware Loading:**
   - Firmware loading, soflink generation, codec configuration are handled by the Linux application.

## Sample Output

### DSP Firmware Console Output

```
sigchain_dsp_main ...
[LINUX_IPC] Initializing Linux-specific IPC...
[LINUX_IPC] Creating Linux-specific IPC receive task...
[LINUX_IPC] Linux IPC receive task created successfully
[LINUX_MCASP] Setting up Linux-specific audio I/O...
[LINUX_MCASP] Linux MCASP processing task created successfully
[IPC] Ready to receive FIRST message...
[TISP_GRAPH] Signal processing graph initialized: SUCCESS
[IPC] CMA setup request
[CMA_SETUP] CMA buffer setup completed
[IPC] Setup complete
```

:::::

# TISP Linux 2D FFT Offload Example {#EXAMPLES_TISP_FFT2D_LINUX_DSP_OFFLOAD}


[TOC]

# Introduction

This example demonstrates the usage of RP Message APIs to offload 2D FFT processing from the Cortex-A CPU (running Linux) to the DSP Core (C75). The Cortex-A CPU reads input data from an SD card and sends it to the DSP Core. The C75 core performs the 2D FFT on the input data and overwrites the output in the same input buffer. The processed output will be verified by Cortex-A CPU and respective error metric logs are printed over the UART.

In this example,
- The DSP core (C75) creates an RPMessage endpoint for message exchange with the Linux userspace application.
- On startup, after driver initialization, DSP core waits for Linux to be ready.
- Then the DSP core (C75) announces to Linux the endpoints on which it is waiting for messages.
- This is needed to be done else Linux cannot initiate message exchange with RTOS/NORTOS CPUs.
- Once both cores (Linux CPU and DSP) come to synchronization, the DSP will wait for an RPMessage that contains the data buffer pointer and the parameter buffer pointer with their metadata.
- The sender can be Linux CPU or other RTOS/NORTOS CPUs.
- On receiving the message, the application triggers the signal chain and performs the 2D FFT. Once the 2D FFT is done, the DSP core sends an acknowledgement to Linux with the CPU task load, total cycles taken to perform 2D FFT and memory throughput.
- This example provides support for graceful shutdown of the core (C7). Refer \ref GRACEFUL_REMOTECORE_SHUTDOWN

## Signal Chain Details

Figure below shows the signal chain, where, the input is 128x128 floating point numbers in complex (a+ib) form. The output is the processed 128x128 floating point numbers in complex form.

\imageStyle{fft_2d_signal_chain.png,width:100%}
\image html fft_2d_signal_chain.png "TISP 2D FFT signal chain"

1. **1D Batched FFT:** The first 1D FFT is performed on the rows.
2. **Matrix Transpose:** The data matrix is transposed to convert coloumns to rows and vice versa. Because FFTLIB libraries are designed perform FFT on 1D data in rows format.
3. **1D Batched FFT:** The second 1D FFT is performed on the coloumns data.

 During processing, data is moved between L2SRAM (lower latency, lower capacity) and DDR (higher capacity, higher latency) to use memory efficiently.

# Supported Combinations

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/tisp/fft2d_dsp_offload/fft2d_linux_dsp_offload
\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). This will build all the dependant CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see \ref MAKEFILE_BUILD_PAGE). This will build all the dependant CPU makefiles as well.
- To run this demo, Linux needs to run on the Cortex A-core. Refer to **Processor SDK Linux** user guide to load and run this example.
- The application elf file have to be copied to the SD card to the path mentioned in `/etc/dsp_offload.cfg` by the name `C7_NEW_FW_PATH`
- The dsp offload application can be triggered from Linux with the command `fft2d_linux_dsp_offload_example` from Linux userspace
- Refer Linux user space application \htmllink{https://github.com/TexasInstruments/rpmsg-dma/blob/main/README.md, **README**} for more details on running the application

# See Also

\ref DRIVERS_IPC_RPMESSAGE_PAGE

# Sample Output

There is no direct output from the RTOS/NORTOS CPUs on the UART or CCS console.
The output is seen on the Linux console on Cortex-A CPU.

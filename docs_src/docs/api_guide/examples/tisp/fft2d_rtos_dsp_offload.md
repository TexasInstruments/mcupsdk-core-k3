# TISP 2D FFT DSP Offload Example {#EXAMPLES_TISP_FFT2D_DSP_OFFLOAD}

[TOC]

# Introduction

This example demonstrates the usage of RP Message APIs to offload 2D FFT processing from the Primary Core to the DSP Core (C75). The Primary Core reads input data from an SD card and sends it to the DSP Core. The C75 core performs the 2D FFT on the input data and overwrites the output in the same input buffer. The processed output is written back to the SD card by the Primary Core for validation.

The signal chain for performing the 2D FFT on the C7x core is as follows:

**DDR → L2 → 1D Batched FFT → Matrix Transpose → L2 → DDR → L2 → 1D Batched FFT → L2 → DDR**

## Example Workflow

1. **Input Generation:**
   - The input data is generated using a Python script by specifying the number of rows and columns for the 2D FFT.
   - A reference output is also generated using NumPy libraries for validation.
   - Both the input (`fft2d_input.bin`) and reference output (`fft2d_output.bin`) are placed on the SD card.

2. **Primary Core :**
   - Reads the input data (`fft2d_input.bin`) from the SD card.
   - Sends the input data to the DSP Core (C75) via RP Message.
   - Waits for the DSP Core to complete the 2D FFT processing.

3. **DSP Core (C75):**
   - Receives the input data and parameters from the Primary Core.
   - Executes the 2D FFT signal chain:
     - Performs the first 1D FFT on the input data.
     - Transposes the intermediate data.
     - Performs the second 1D FFT on the transposed data.
   - Overwrites the processed output in the same input buffer.
   - Sends an acknowledgment to the Primary Core with performance metrics.

4. **Validation:**
   - Primary Core Writes the processed output (`c7x.bin`) back to the SD card.
   - Compares the processed output with the reference output (`fft2d_output.bin`).
   - Logs the error metrics and performance parameters such as execution time, memory throughput and DSP load .


## Signal Chain Details

The signal chain for the 2D FFT processing is as follows:
\imageStyle{fft_2d_signal_chain.png,width:100%}
\image html fft_2d_signal_chain.png "TISP 2D FFT signal chain"
1. **1D Batched FFT:** The first 1D FFT is performed on the rows.
2. **Matrix Transpose:** The data matrix is transposed to convert coloumns to rows and vice versa. Because FFTLIB libraries are designed perform FFT on 1D data in rows format.
3. **1D Batched FFT:** The second 1D FFT is performed on the coloumns data.

 In between while processing, the data is interchanged between L2SRAM(lower latency, lower capacity) and DDR(higher capacity, higher latency) to use the memory efficiently.

# Supported Combinations
\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 ^              | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/tisp/fft2d_dsp_offload/fft2d_rtos_dsp_offload |

\endcond

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/tisp/fft2d_dsp_offload/fft2d_rtos_dsp_offload |

\endcond

# Steps to Run the Example

## Build the Example

- **Using CCS Projects:** Import the system CCS project and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). This will build all dependent CPU projects as well.
- **Using Makefiles:** Build the system makefile using the `make` command (see \ref MAKEFILE_BUILD_PAGE). This will build all dependent CPU makefiles as well.

## Prepare the Input Data

1. Use the provided Python script to generate the input data and reference output:
   - Given command below will run the script.
   ```bash
   python3 ${SDK_INSTALL_PATH}/examples/tisp/fft2d_dsp_offload/fft2d_rtos_dsp_offload/host/gen_data.py
   ```
   - This will create `fft2d_input.bin` and `fft2d_output.bin` files.
   - Data size used for the EVM is 128x128 by default. Application user need to use either Hyper RAM or external memory to increase the size beyond 128x128.
2. Copy both files to the SD card.

## Run the Example

1. **Set up the hardware:**
   - Load the SD card with input and reference output data and insert the SD card into the board.
   - Keep the MMC0_SELECT button ON to read the data from SD card.
   - Connect the board to the host PC via USB for communication.

2. **Run the application:**
   - Load and run the application on both the Primary Core and the DSP Core (C75).
   - The Primary Core will read the input data from the SD card and send it to the DSP Core for processing.

3. **Monitor the output:**
   - The processed data will be stored in the same input buffer.
   - The Primary Core will write the processed output to the SD card as `c7x.bin`.

4. **Validate the output:**
   - Once after writting back to SD the Primary core compares the reference output with actual output for each element and calculates error metrics.
   - The module will log the error metrics and performance parameters.

## Input/Output Format

   - The data (input/output) is complex by default and will be in the format a1+jb1, a2+jb2, a3+jb3...
   - In the Python file (`gen_data.py`), the data is written as a1 b1 a2 b2 a3 b3... in fft2d_input.bin and fft2d_output.bin files.
   - Once the 2D FFT is performed, the output is stored in the same input buffer using the same format.

# Sample Output

```

Starting FFT2D DSP Offload example

Loading test data...
Input data samples (a+ib):
0.89 + 0.89j
0.21 + 0.13j

Offloading FFT to DSP...

Receiving FFT output from DSP...

=========FFT Performance Results=========
  DSP Load           : 99
  Cycle Count        : 83615
  Mem Throughput     : 3.14 GB/s

Output data samples (a+ib):
8120.53 + 8206.41j
50.93 + 13.73j

Comparing FFT output with expected output...
======FFT Output Comparison With Python Results===========
  Max Absolute Error   : 4.882812e-04
  Mean Absolute Error  : 5.047727e-06
  RMSE                 : 8.646451e-06
  Relative Max Error   : 5.949997e-08

All tests have completed!!


```

# See Also
- \ref DRIVERS_IPC_RPMESSAGE_PAGE
# TISP 2D FFT DSP Offload Example

## Introduction

This example demonstrates the usage of RP Message APIs to offload 2D FFT processing from the Primary Core to the DSP Core (C75). The Primary Core reads input data from an SD card and sends it to the DSP Core. The C75 core performs the 2D FFT on the input data and overwrites the output in the same input buffer. The processed output is written back to the SD card by the Primary Core for validation.

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/tisp/fft2d_dsp_offload/fft2d_rtos_dsp_offload |

::::

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/tisp/fft2d_dsp_offload/fft2d_rtos_dsp_offload |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependent CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependent CPU makefiles as well.
- Use the provided Python script to generate input data:
  ```
  python3 ${SDK_INSTALL_PATH}/examples/tisp/fft2d_dsp_offload/fft2d_rtos_dsp_offload/host/gen_data.py
  ```
- Copy `fft2d_input.bin` and `fft2d_output.bin` to the SD card
- Load the SD card and run the application on both the Primary Core and the DSP Core (C75)

## See Also

[IPC RPMessage](../../components/drivers/ipc_rpmsg.md)

## Sample Output

Shown below is a sample output when the application is run,

```
Starting FFT2D DSP Offload example

Loading test data...
Offloading FFT to DSP...
Receiving FFT output from DSP...

=========FFT Performance Results=========
  DSP Load           : 99
  Cycle Count        : 83615
  Mem Throughput     : 3.14 GB/s

Comparing FFT output with expected output...
======FFT Output Comparison With Python Results===========
  Max Absolute Error   : 4.882812e-04
  Mean Absolute Error  : 5.047727e-06
  RMSE                 : 8.646451e-06
  Relative Max Error   : 5.949997e-08

All tests have completed!!
```

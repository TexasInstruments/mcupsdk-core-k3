# TISP Linux 2D FFT Offload Example

## Introduction

This example demonstrates the usage of RP Message APIs to offload 2D FFT processing from the Cortex-A CPU (running Linux) to the DSP Core (C75). The Cortex-A CPU reads input data from an SD card and sends it to the DSP Core. The C75 core performs the 2D FFT on the input data and overwrites the output in the same input buffer.

This example provides support for graceful shutdown of the core (C7).

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/tisp/fft2d_dsp_offload/fft2d_linux_dsp_offload |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependent CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependent CPU makefiles as well.
- To run this demo, Linux needs to run on the Cortex A-core. Refer to **Processor SDK Linux** user guide to load and run this example.
- Copy the application elf file to the SD card path mentioned in `/etc/dsp_offload.cfg` as `C7_NEW_FW_PATH`
- Trigger the dsp offload application from Linux with the command `fft2d_linux_dsp_offload_example`

## See Also

[IPC RPMessage](../../components/drivers/ipc_rpmsg.md)

## Sample Output

There is no direct output from the RTOS/NORTOS CPUs on the UART or CCS console.
The output is seen on the Linux console on Cortex-A CPU.

# IPC RP Message Linux Audio Filter Offload

## Introduction

This example shows usage of RP Message APIs to exchange messages between RTOS/NORTOS CPUs as
well as exchange messages with Linux on Cortex-A CPU.

In this example,
- We create an RP Message end point for message exchange with the Linux userspace application
- All cores on startup after driver initialization first wait for Linux to be ready
- Then they `announce` the end points on which they are waiting for messages to Linux.
- Two tasks are then created which listen for incoming messages and echo it back to the sender.
- A task is created to service the linux user space application messages which contains the buffer
  containing audio data and parameters of the signal chain.
- The application on receiving the message from Linux application would trigger the audio filter
  signal chain on the buffer with the parameters and sends an acknowledgement to Linux with the CPU task load.
- This example provides support for graceful shutdown of the core (C7).

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_linux_audio_filter_offload |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependent CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependent CPU makefiles as well.
- To run this demo, Linux needs to run on the Cortex A-core. Refer to **Processor SDK Linux** user guide to load and run this example.
- The application elf file have to be copied to the SD card to the path mentioned in `/etc/dsp_offload.cfg` by the name `C7_NEW_FW_PATH`
- The dsp offload application can be triggered from Linux with the command `rpmsg_audio_offload_example` from Linux userspace
  and the audio output can be heard at audio out ports `J3 and J4`

## See Also

[IPC RPMessage](../../components/drivers/ipc_rpmsg.md)

## Sample Output

There is no direct output from the RTOS/NORTOS CPUs on the UART or CCS console.
The output is seen on the Linux console on Cortex-A CPU.

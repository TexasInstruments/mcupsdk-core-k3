# IPC RP Message RTOS Audio Filter Offload

## Introduction

This example shows usage of RP Message APIs to offload the audio processing from Master Core to DSP Core by exchanging messages between RTOS/NORTOS CPUs.

In this example,
- All cores on startup after driver initialization wait for getting in sync
- DSP Core services the Master Core messages which points to the buffer containing audio data and parameters of the signal chain.
- The DSP application on receiving the message from Master Core triggers the audio filter signal chain on the buffer and sends an acknowledgement to Master Core.
- The master core sends the input data, output filtered data and the metrics to the host utility using Socket Communication.

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_linux_audio_filter_offload |

::::

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_linux_audio_filter_offload |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependent CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependent CPU makefiles as well.
- Run the host utility script provided in `${SDK_INSTALL_PATH}/examples/drivers/ipc/ipc_rpmsg_rtos_audio_filter_offload/master/host_interface/audmon.py`
- Run the application on both master and dsp core

## See Also

[IPC RPMessage](../../components/drivers/ipc_rpmsg.md)

## Sample Output

Shown below is a sample output when the application is run,

```
Starting IPC RPMSG DSP OFFLOAD example on main core 0
Network is UP ...
[LOG] Accepted new connection
All Connections are Up ...
All tests have passed!!
```

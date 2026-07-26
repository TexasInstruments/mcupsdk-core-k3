# IPC Notify Echo Example With OptiShare

## Introduction

This example shows usage of IPC Notify APIs for exchanging 28b messages between multiple CPUs with Optishare enabled.

In this example,
- One "main" CPU, sends 28b messages to other "remote" CPUs using the IPC notify API
- The "remote" CPUs, then echo back the message to the main CPU
- Once all messages are echoed all the CPUs exit
- With the application of OptiShare, there is shared code and data across all cores

## Supported Combinations

:::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-1 freertos
 ^              | r5fss1-0 freertos
 ^              | r5fss1-1 freertos
 Toolchain      | ti-arm-clang
 Boards         | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/drivers/ipc/ipc_notify_echo_optishare

:::

## Steps to Run the Example

:::{note}
This is a `system` or multi-core project, so refer to system project build instructions for CCS project or makefiles when building the example.
:::

### Building with Makefile

- Build the system makefile using the make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependent CPU makefiles as well.
- To build with OptiShare enabled, use the command:
```
  make sso
```
This builds the `sso` rule which does the normal build and also performs the further OptiShare processing.

### Loading And Running the example using uart_uniflash tool

- Flash the application using uart_uniflash.py. Flash the binaries with extension `*.optishare.mcelf` and `*.optishare.mcelf_xip` from the `system_freertos` folder.
- Additionally, flash `sso.mcelf` which contains the shared code and data.
- More on how to flash can be read at [Flashing Tools](../../components/tools/tools_flash.md)
- Change the boot mode to OSPI boot mode and do a board reset to see the output as shown in the sample output.

### Loading And Running the example using CCS

Once this example has been built using Makefile, the optishare binaries can be loaded with CCS.

1. Load the debugging session as described in [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
2. Load `sso.out` (from the `system_freertos` folder) **first**, as it contains the shared code and data.
3. For each core, load the corresponding `*.optishare.out` binary (not the regular `.out`).
4. Run all cores.

### Building using CCS

:::{note}
Building this example using CCS is not supported yet.
:::

## See Also

[IPC Notify](../../components/drivers/ipc_notify.md)
[Optishare](../../developer_guides/optishare/optishare.md)

## Sample Output

Shown below is a sample output when the application is run.

```
[IPC NOTIFY ECHO] Message exchange started by main core !!!
[IPC NOTIFY ECHO] All echoed messages received by main core from 3 remote cores !!!
[IPC NOTIFY ECHO] Messages sent to each core = 1000000
[IPC NOTIFY ECHO] Number of remote cores = 3
All tests have passed!!
```

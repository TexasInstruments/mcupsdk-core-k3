# IPC Notify Echo
## Introduction

This example shows usage of IPC Notify APIs for exchanging 28b messages between multiple CPUs.

In this example,
- One "main" CPU, sends 28b messages to other "remote" CPUs using the IPC notify API
- The "remote" CPUs, then echo back the message to the main CPUs
- Once all messages are echoed all the CPUs exit

## Supported Combinations
::::{only} SOC_AM64X
   :::{admonition} Attention
   A53 NORTOS support is experimental and is NOT supported by TI. \n
   :::
   :::


::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss1-0 nortos |
| CPU + OS | r5fss1-1 nortos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | a53ss0-0 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_notify_echo |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss1-0 nortos |
| CPU + OS | r5fss1-1 nortos |
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_notify_echo |

::::


::::{only} SOC_AM263X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss1-0 nortos |
| CPU + OS | r5fss1-1 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_notify_echo |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-1 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_notify_echo |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_notify_echo |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos-smp |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_notify_echo |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 freertos |
| CPU + OS | r5fss1-0 freertos |
| CPU + OS | r5fss1-1 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | c75ss1-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_notify_echo |

::::


::::{only} SOC_AM62AX or SOC_AM62DX
   **Note**
   There are two examples for A53 cores, a53ss0-0_freertos-smp and a53ss0-0_nortos.
   For single core application use a53ss0-0_nortos and for smp application use a53ss0-0_freertos-smp
::::


## Steps to Run the Example

:::{admonition} Note
This is a `system` or multi-core project, so refer to system project build instructions for CCS project or makefiles when building the example.
:::


- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependant CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependant CPU makefiles as well.

::::{only} SOC_AM263X
   - Launch a CCS debug session, follow the steps for running multi core applications in [Prerequisites](../../getting_started/ccs_launch.md) and run the executables, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::

- Launch a CCS debug session and run the executables, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X
   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


   - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
::::

- This is a multi-core example. Hence the executables should be loaded and run for all the above mentioned cores
- The application has a sync mechanism at the start which waits for all cores to start before doing the test. Hence the cores can be loaded and run in any sequence.

## See Also

[IPC Notify](../../components/drivers/ipc_notify.md)

## Sample Output

Shown below is a sample output when the application is run,

::::{only} SOC_AM64X

   ```
   [IPC NOTIFY ECHO] Message exchange started by main core !!!
   [m4f0-0]     0.283025s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f0-1]     0.001023s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f0-1]     2.152508s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   [r5f1-0]     0.435019s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f1-0]     2.585876s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   [r5f1-1]     0.360022s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f1-1]     2.511288s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   [a530-0]     0.209031s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [m4f0-0]     4.045393s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   [IPC NOTIFY ECHO] All echoed messages received by main core from 5 remote cores !!!
   [IPC NOTIFY ECHO] Messages sent to each core = 1000000
   [IPC NOTIFY ECHO] Number of remote cores = 5
   All tests have passed!!
   [a530-0]     4.569557s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   ```

::::

::::{only} SOC_AM243X

   ```
   [IPC NOTIFY ECHO] Message exchange started by main core !!!
   [m4f0-0]     0.249022s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f0-1]     0.473040s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f0-1]     2.645696s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   [r5f0-1]     2.645712s : All tests have passed!!
   [r5f1-0]     0.366043s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f1-0]     2.538699s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   [r5f1-0]     2.538715s : All tests have passed!!
   [r5f1-1]     0.296028s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f1-1]     2.468686s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   [r5f1-1]     2.468702s : All tests have passed!!
   [IPC NOTIFY ECHO] All echoed messages received by main core from 4 remote cores !!!
   [IPC NOTIFY ECHO] Messages sent to each core = 1000000
   [IPC NOTIFY ECHO] Number of remote cores = 4
   [m4f0-0]     4.246567s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   [m4f0-0]     4.246586s : All tests have passed!!
   ```

::::

::::{only} SOC_AM62AX or SOC_AM62DX

   ```
   [IPC NOTIFY ECHO] Message exchange started by main core !!!
   [mcu-r5f0-0]     0.049185s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [a530-0]         0.000250s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
   [a530-0]         27.053760s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
   [IPC NOTIFY ECHO] All echoed messages received by main core from 2 remote cores !!!
   [IPC NOTIFY ECHO] Messages sent to each core = 1000000
   [IPC NOTIFY ECHO] Number of remote cores = 2
   All tests have passed!!
   [mcu-r5f0-0]     39.345675s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!

   ```

::::

::::{only} SOC_AM62X

   After this the following message will appear on the WAKEUP UART.

   ```
   [IPC NOTIFY ECHO] Message exchange started by main core !!!
   [IPC NOTIFY ECHO] All echoed messages received by main core from 2 remote cores !!!
   [IPC NOTIFY ECHO] Messages sent to each core = 1000000
   [IPC NOTIFY ECHO] Number of remote cores = 2
   All tests have passed!!

   ```

::::

```
[IPC NOTIFY ECHO] Message exchange started by main core !!!
[IPC NOTIFY ECHO] All echoed messages received by main core from 3 remote cores !!!
[IPC NOTIFY ECHO] Messages sent to each core = 1000000
[IPC NOTIFY ECHO] Number of remote cores = 3
All tests have passed!!
[r5f0-1]     2.965606s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
[r5f0-1]     8.203494s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
[r5f1-0]     6.069463s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
[r5f1-0]    11.306840s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
[r5f1-1]     8.245586s : [IPC NOTIFY ECHO] Remote Core waiting for messages from main core ... !!!
[r5f1-1]    13.483076s : [IPC NOTIFY ECHO] Remote core has echoed all messages !!!
```

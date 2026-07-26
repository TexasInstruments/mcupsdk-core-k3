# IPC RP Message Echo
## Introduction

This example shows usage of RP Message APIs to each multi-byte messages between different CPUs

In this example,
- One "main" CPU, sends multi-byte messages to other "remote" CPUs using the RP Message APIs
- The "remote" CPUs, then echo back the same message to the main CPUs
- Once all messages are echoed the main CPU exits. The remote CPUs remain waiting to receive new messages.

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
| CPU + OS | a53ss0-0 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 nortos |
| CPU + OS | r5fss1-0 nortos |
| CPU + OS | r5fss1-1 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo |

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
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo |

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
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo |

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
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo |

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

[IPC RPMessage](../../components/drivers/ipc_rpmsg.md)

## Sample Output

Shown below is a sample output when the application is run,

::::{only} SOC_AM64X

   ```
   [m4f0-0]     0.019049s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f0-1]     0.018063s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f1-0]     0.019063s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f1-1]     0.019063s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [a530-0]     0.000043s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [IPC RPMSG ECHO] Message exchange started by main core !!!
   [IPC RPMSG ECHO] All echoed messages received by main core from 5 remote cores !!!
   [IPC RPMSG ECHO] Messages sent to each core = 100000
   [IPC RPMSG ECHO] Number of remote cores = 5
   [IPC RPMSG ECHO] Total execution time = 3479561 usecs
   [IPC RPMSG ECHO] One way message latency = 3479 nsec
   All tests have passed!!
   ```

::::

::::{only} SOC_AM243X

   ```
   [m4f0-0]     0.002039s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f0-1]     0.001056s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f1-0]     0.002056s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [r5f1-1]     0.002056s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [IPC RPMSG ECHO] Message exchange started by main core !!!
   [IPC RPMSG ECHO] All echoed messages received by main core from 4 remote cores !!!
   [IPC RPMSG ECHO] Messages sent to each core = 100000
   [IPC RPMSG ECHO] Number of remote cores = 4
   [IPC RPMSG ECHO] Total execution time = 2918245 usecs
   [IPC RPMSG ECHO] One way message latency = 3647 nsec
   All tests have passed!!
   ```

::::

::::{only} SOC_AM62AX or SOC_AM62DX

   ```
   [mcu-r5f0-0]    32.119999s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [a530-0]        66.509049s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [c75ss0]        0.000999s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
   [IPC RPMSG ECHO] Message exchange started by main core !!!
   [IPC RPMSG ECHO] All echoed messages received by main core from 3 remote cores !!!
   [IPC RPMSG ECHO] Messages sent to each core = 10
   [IPC RPMSG ECHO] Number of remote cores = 3
   [IPC RPMSG ECHO] Total execution time = 1779 usecs
   [IPC RPMSG ECHO] One way message latency = 29650 nsec
   All tests have passed!!
   [mcu-r5f0-0]    32.622999s : [IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
   [mcu-r5f0-0]    32.622999s : All tests have passed!!
   [a530-0]        67.013217s : [IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
   [a530-0]        67.013221s : All tests have passed!!
   [c75ss0]        0.504999s : [IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
   [c75ss0]        0.505999s : All tests have passed!!
   ```

::::

::::{only} SOC_AM62X

   After this the following message will appear on the WAKEUP UART.

   ```
   [IPC RPMSG ECHO] Message exchange started by main core !!!
   [IPC RPMSG ECHO] All echoed messages received by main core from 2 remote cores !!!
   [IPC RPMSG ECHO] Messages sent to each core = 10
   [IPC RPMSG ECHO] Number of remote cores = 2
   [IPC RPMSG ECHO] Total execution time = 438 usecs
   [IPC RPMSG ECHO] One way message latency = 10950 nsec
   All tests have passed!!
   ```

::::

::::{only} SOC_AM62PX

   ```
   Sciserver Testapp Built On: Oct 14 2023 10:06:22
   Sciserver Version: v2023.10.0.0
   RM_PM_HAL Version: v09.01.01
   Starting Sciserver..... PASSED
   [IPC RPMSG ECHO] Message exchange started by main core !!!
   [IPC RPMSG ECHO] All echoed messages received by main core from 1 remote cores !!!
   [IPC RPMSG ECHO] Messages sent to each core = 10
   [IPC RPMSG ECHO] Number of remote cores = 1
   [IPC RPMSG ECHO] Total execution time = 230 usecs
   [IPC RPMSG ECHO] One way message latency = 11500 nsec
   All tests have passed!!
   ```

::::

```
[r5f0-1]     1.019992s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
[r5f1-0]     0.512016s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
[r5f1-1]     0.000055s : [IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
[IPC RPMSG ECHO] Message exchange started by main core !!!
[IPC RPMSG ECHO] All echoed messages received by main core from 3 remote cores !!!
[IPC RPMSG ECHO] Messages sent to each core = 100000
[IPC RPMSG ECHO] Number of remote cores = 3
[IPC RPMSG ECHO] Total execution time = 4203377 usecs
[IPC RPMSG ECHO] One way message latency = 7005 nsec
All tests have passed!!
```

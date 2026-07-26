# Spinlock Example

## Introduction

The Spinlock module provides hardware assistance for synchronizing the processes running on multiple processors in the device. The following example shows the working of spinlock in synchronizing multiple cores.

In this example 2 cores work simultaneously. Synchronization is achieved with the help of spinlock, where the core is only active when it has acquired the spinlock, while the other core waits till the lock is free.

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/spinlock/spinlock_example/ |

::::

::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/spinlock/spinlock_example/ |

::::

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/spinlock/spinlock_example/ |

::::

## Steps to Run the Example

:::{admonition} Note
This is a `system` or multi-core project, so refer to system project build instructions for CCS project or makefiles when building the example.
:::

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependent CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependent CPU makefiles as well.
- Launch a CCS debug session and run the executables, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
- This is a multi-core example. Hence the executables should be loaded and run for all the above mentioned cores

::::{only} SOC_AM62X or SOC_AM62DX
:::{admonition} Attention
As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
:::

- Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
::::

## Sample Output

Shown below is a sample output when the application is run,

```
[Cortex_R5_0] hello core 0
[Cortex_R5_1] hello core 1
[Cortex_R5_0] hello core 0
[Cortex_R5_1] hello core 1
[Cortex_R5_0] All Test Cases passed!
```

# SafeRTOS Task Switch Example

## Introduction

This example shows usage of direct SafeRTOS APIs, i.e not via the DPL APIs.
It shows usage of task APIs, task notification APIs, semaphore and delay APIs.
It also shows how to signal to SafeRTOS task from ISRs.
This example needs the SafeRTOS kernel to build and use.
Please contact WITTENSTEIN for SafeRTOS kernel package.

The example does the below
- Creates two semaphores
- Creates two tasks, ping and pong
- Ping and pong tasks signal each other using semaphores and task notifications
- A HW ISR is also created and ping task is signaled from the ISR
- Task delay API usage is shown

## Supported Combinations


::::{only} SOC_AM62AX

    Parameter      | Value
    ---------------|-----------
    CPU + OS       | c75ss0-0 safertos
    ^              | r5fss0-0 safertos
    Toolchain      | ti-c7000
    ^              | ti-arm-clang
    Boards         | {{ VAR_BOARD_NAME_LOWER }}
    Example folder | examples/kernel/safertos/task_switch

::::


## Steps to Run C75 Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM62AX
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::


## Steps to Run R5F Example

- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Load the example in SBL NULL config at appropriate flash offset
- Flash SBL NULL bootloader by following steps mentioned in [Flash SOC Initialization Binary](../../getting_started/am62px_evm_setup.md)
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62px_evm_setup.md) and power on the EVM.
- Collect the logs from UART

## See Also

[SafeRTOS](../../components/kernel/os/safertos.md)

## Sample Output

Shown below is a sample output when the C7X application is run,

```
[SafeRTOS] ping task ... start !!!

execution time for task switches = 5582856 us
number of task switches = 2000000
time per task switch (semaphore give/take) = 2791 ns

execution time for task - ISR - task - task switches = 6553420 us
number of ISRs = 2000000
time per task - ISR - task switch (semaphore give/take) = 3276 ns

[SafeRTOS] ping task ... done !!!

All tests have passed!!
```
Shown below is a sample output when the R5F application is run,

```
[SafeRTOS] ping task ... start !!!

execution time for task switches = 4353885 us
number of task switches = 2000000
time per task switch (semaphore give/take) = 2176 ns

execution time for task - ISR - task - task switches = 4493120 us
number of ISRs = 2000000
time per task - ISR - task switch (semaphore give/take) = 2246 ns

[SafeRTOS] ping task ... done !!!

All tests have passed!!
```
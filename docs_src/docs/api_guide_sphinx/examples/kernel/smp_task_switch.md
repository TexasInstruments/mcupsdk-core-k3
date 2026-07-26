# FreeRTOS SMP Task Switch Example

## Introduction

This example shows usage of direct FreeRTOS APIs, i.e not via the DPL APIs.
It shows usage of task APIs, task notification APIs, semaphore and delay APIs.
It also shows how to signal to FreeRTOS task from ISRs.

The example does the below
- Creates two semaphores
- Creates two tasks, ping and pong
- Run tasks with core affinity
- Ping and pong tasks signal each other using semaphores and task notifications
- A HW ISR is also created and ping task is signaled from the ISR
- Task delay API usage is shown

## Supported Combinations


::::{only} SOC_AM64X
   :::{admonition} Attention
   A53 FREERTOS SMP support is experimental and is NOT supported by TI. \n :::
::::


::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos-smp |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/freertos/smp_task_switch |

::::


::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos-smp |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/freertos/smp_task_switch |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos-smp |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/kernel/freertos/smp_task_switch |

::::


## Steps to Run the Example
:::{admonition} Note
Create a sync group for cores when running an SMP example in CCS
::::


- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[FreeRTOS](../../components/kernel/os/freertos.md)

## Sample Output
````{only} SOC_AM64X
```
Shown below is a sample output when the application is run,

[FreeRTOS] ping task ... start !!!

execution time for task switches = 32937660 us
number of task switches = 2000000
time per task switch (semaphore give/take) = 16468 ns

execution time for task switches = 17862161 us
number of task switches = 2000000
time per task switch (direct-to-task notification give/take) = 8931 ns

execution time for task - ISR - task - task switches = 19287679 us
number of ISRs = 2000000
time per task - ISR - task switch (semaphore give/take) = 9643 ns

[FreeRTOS] ping task ... done !!!

All tests have passed!!
```
````
```
Shown below is a sample output when the application is run,The CoreID may change when you set different core affinity,

Pong CoreID = 1
Ping CoreID = 0

[FreeRTOS] ping task ... start !!!

execution time for task switches = 16669227 us
number of task switches = 2000000
time per task switch (semaphore give/take) = 8334 ns
Pong ISR CoreID = 1

execution time for task switches = 10991883 us
number of task switches = 2000000
time per task switch (direct-to-task notification give/take) = 5495 ns
Ping ISR CoreID = 0
Pong End CoreID = 1

execution time for task - ISR - task - task switches = 11043170 us
number of ISRs = 2000000
time per task - ISR - task switch (semaphore give/take) = 5521 ns

[FreeRTOS] ping task ... done !!!

Ping End CoreID = 0
All tests have passed!!

```

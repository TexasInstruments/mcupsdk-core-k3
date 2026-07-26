# HYPERRAM XIP Benchmark

## Introduction

This example shows a application running in XIP (eXecute In Place) mode. This example can be used to check and evaluate the performance
of the SOC when running in XIP mode.

The example does the below
- SOC is booted to run applications for multiple CPUs
- The bootloader configures the hyperRam at highest possible speed and highest throughput mode.

::::{only} SOC_AM275X
- On {{ VAR_SOC_NAME }}, this means, the hyperRam is in
  - Direct access (DAC) mode for read
  - Dual data rate (DDR) mode
  - HyperRam at 166Mhz clock speed
::::

- All the CPUs are configured to run FreeRTOS with below functions being executed.
  - FIR function, here, code, input data and coeff data is kept in HyperRam
  - memcpy function, here, code, input data is kept in HyperRam
- The linker command file of the CPUs is setup so that code and rodata is execute and referenced from HyperRam.
- An MPU entry is setup at each CPU, to enable execute from flahs region with cache enabled.
- Each function is run multiple times and the worst case, best case and average case performance is printed on the
  UART terminal in units of cycles.
- There is a compile time flag `ENABLE_CPU_SYNC` to "sync" all the CPUs such that all execute and access the code and data from HyperRam
  at the approximately the same time. This allows to simulate the worst case simultaneous access to the HyperRam device in multi CPU environment.
  **NOTE**, by default, `ENABLE_CPU_SYNC` is `0`, i.e the CPUs are not synced.

## Supported Combinations

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/benchmarks/xip_benchmark/ |

::::

## Steps to Run the Example

:::{admonition} Note
This is a `system` or multi-core project, so refer to system project build instructions for CCS project or makefiles when building the example.
:::

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependant CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependant CPU makefiles as well.
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## Sample Output


Shown below is a sample output when the application is run on am275x,

```
Starting OSPI Bootloader ...

SYSFW Firmware Version 11.0.6--v11.00.06 (Fancy Rat)
SYSFW Firmware revision 0xb
SYSFW ABI revision 4.0

[KPI] Boot Media       : FLASH
[KPI] Boot Media Clock : 166.667 MHz
[KPI] Boot Image Size  : 417 KB
[KPI] Cores present    :
[KPI] TIFS init                        :        691us
[KPI] System_init                      :       1879us
[KPI] Board_init                       :          2us
[KPI] FreeRtosTask Create              :        297us
[KPI] Drivers_open                     :        103us
[KPI] Board_driversOpen                :          0us
[KPI] sciServer_init                   :      15073us
[KPI] SBL Drivers_open                 :       3174us
[KPI] SBL Board_driversOpen            :       2907us
[KPI] Sciclient Get Version            :      10023us
[KPI] R5FSS0_0 Image Load              :       1454us
[KPI] R5FSS0_1 Image Load              :       1563us
[KPI] R5FSS1_0 Image Load              :       1568us
[KPI] R5FSS1_1 Image Load              :       1554us
[KPI] DSP 0 Image Load                 :       6967us
[KPI] DSP 1 Image Load                 :       6791us
[KPI] SBL Total Time Taken             :      54054us

Image loading done...
Starting RTOS/Baremetal applications


### HYPERRAM XIP benchmark ###
FIR:
  23905 cycles (code/data fully cached) ,
  47648 cycles (code/data not cached) ,
  26282 cycles (code/data not-cached 1 of 10 iterations)
MEMCPY:
   1564 cycles (code/data fully cached) ,
   4297 cycles (code/data not cached) ,
   1840 cycles (code/data not-cached 1 of 10 iterations)
All tests have passed!!
```

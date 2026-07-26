# RL2 Example

## Introduction

Rl2 example provides how to use RL2 in applications and also shows how RL2 brings in benefits.

## Supported Combinations

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/rl2 |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## Sample Output

```
Starting OSPI Bootloader ...

SYSFW Firmware Version 11.0.7--v11.00.07 (Fancy Rat)
SYSFW Firmware revision 0xb
SYSFW ABI revision 4.0

[KPI] Boot Media       : FLASH
[KPI] Boot Media Clock : 166.667 MHz
[KPI] Boot Image Size  : 441 KB
[KPI] Cores present    :
[KPI] TIFS init                        :        750us
[KPI] System_init                      :       1895us
[KPI] Board_init                       :          2us
[KPI] FreeRtosTask Create              :        255us
[KPI] Drivers_open                     :         98us
[KPI] Board_driversOpen                :          0us
[KPI] sciServer_init                   :      15068us
[KPI] SBL Drivers_open                 :       3168us
[KPI] SBL Board_driversOpen            :       2917us
[KPI] Sciclient Get Version            :      10023us
[KPI] R5FSS0_0 Image Load              :       1674us
[KPI] R5FSS0_1 Image Load              :       1564us
[KPI] R5FSS1_0 Image Load              :       1568us
[KPI] R5FSS1_1 Image Load              :       1552us
[KPI] DSP 0 Image Load                 :       6963us
[KPI] DSP 1 Image Load                 :       6821us
[KPI] SBL Total Time Taken             :      54325us

Image loading done...
Starting RTOS/Baremetal applications

L2 Cache:       i = 0   Miss = 129      Hits = 0
L2 Cache:       i = 1   Miss = 0        Hits = 129
L2 Cache:       i = 2   Miss = 0        Hits = 129
L2 Cache:       i = 3   Miss = 0        Hits = 129
L2 Cache:       i = 4   Miss = 0        Hits = 129
L2 Cache:       i = 5   Miss = 0        Hits = 129
L2 Cache:       i = 6   Miss = 0        Hits = 129
L2 Cache:       i = 7   Miss = 0        Hits = 129
L2 Cache:       i = 8   Miss = 0        Hits = 129
L2 Cache:       i = 9   Miss = 0        Hits = 129
Profile Point: With RL2
Cycle Count: 97006
No. Of CPU instructions executed Count: 21184
ICache Miss Count: 8
ICache Access Count: 450

Profile Point: Without RL2
Cycle Count: 340983
No. Of CPU instructions executed Count: 20699
ICache Miss Count: 0
ICache Access Count: 165

All tests have passed!!
```

## Description

On how to configure RL2, please go through [Configuring OptiFlash various IP](../../developer_guides/optiflash_configuration.md).

This example shows how RL2 is used and how its different functions are used. With RL2 enabled, the function that was being executed is getting cached in the RL2 cache bank. First time, it caused 129 L2 cache misses, and because each L2 cache line (at a size of 128KB) is 32 bytes, it implies that a total of ~4KB of code is being cached. This is in alignment with the size of the function that is being executed from the flash. Later on, every time there were L2 cache hits,

Another point to highlight is performance improvement. This is clear from the cycle count with RL2 and without RL2.

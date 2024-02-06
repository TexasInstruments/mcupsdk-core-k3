# Datasheet {#DATASHEET_AM62PX_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Generic Setup details

SOC Details             | Values
------------------------|------------------------------
Core                    | R5F
Core Operating Speed    | 400 MHz
Cache Status            | Enabled

Optimization Details    | Values
------------------------|------------------------------
Build Profile           | Release
R5F Compiler flags      | -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -Wall -Werror -g -mthumb -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function
R5F Linker flags        | -Wl,--diag_suppress=10063 -Wl,--ram_model -Wl,--reread_libs
Code Placement          | HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)
Data Placement          | HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)

## Performance Numbers

### SBL OSPI NOR performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 205 KB
- Size of images loaded by stage2  : 851 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.545
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.088
SBL Stage1: SBL Drivers_open            |    0.130
SBL Stage1: Board_driversOpen           |    0.010
SBL Stage1: SBL Board_driversOpen       |   22.478
SBL Stage1: App_loadSelfcoreImage       |    4.562
SBL Stage2: System_init                 |    2.700
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.259
SBL Stage2: SBL Drivers_open            |   10.255
SBL Stage2: SBL Board_driversOpen       |   34.353
SBL Stage2: App_loadImages              |    2.755
SBL Stage2: App_loadMCUcoreImage        |    3.295
SBL Stage2: App_loadLinuxImages         |    9.973
----------------------------------------|--------------
SBL : Total time taken                  |  129.406

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 159 KB
- Size of images loaded by stage2  : 851 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.268
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   19.425
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |   35.546
SBL Stage2: System_init                 |    2.518
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.257
SBL Stage2: SBL Drivers_open            |   21.692
SBL Stage2: App_loadImages              |    4.528
SBL Stage2: App_loadMCUcoreImage        |    4.856
SBL Stage2: App_loadLinuxImages         |   15.997
----------------------------------------|--------------
SBL : Total time taken                  |  143.087

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
wkup-r5f0-0 | mcu-r5f0-0  |  1.14

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us)
------------|-------------|--------------|------------------------------|------------------
 wkup-r5f0-0|   mcu-r5f0-0|            32|                        14.413|                25
 wkup-r5f0-0|   mcu-r5f0-0|            64|                        21.110|                23
 wkup-r5f0-0|   mcu-r5f0-0|           112|                        31.066|                42


### EMMC Performance

Mode   | Read Speed (MiBps) | Size (MiB)
-------|--------------------|--------------
 HS400 | 261                | 4
 HS200 | 167                | 4

### OSPI NOR Flash Performance

Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
PHY : enabled
DMA : enabled
DAC : disabled

Data size(MiB) | Read speed(MiBps)
---------------|-------------------
1              | 283.58
5              | 284.71
10             | 284.88
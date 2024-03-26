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
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 895 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.629
SBL Stage1: Board_init                  |    0.002
SBL Stage1: Drivers_open                |    0.088
SBL Stage1: SBL Drivers_open            |    0.134
SBL Stage1: Board_driversOpen           |    0.010
SBL Stage1: SBL Board_driversOpen       |    7.228
SBL Stage1: App_loadSelfcoreImage       |    4.162
----------------------------------------|--------------
SBL Stage1: Total time taken            |   50.256


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.645
SBL Stage2: Board_init                  |    0.002
SBL Stage2: FreeRtosTask Create         |    0.259
SBL Stage2: SBL Drivers_open            |    0.491
SBL Stage2: SBL Board_driversOpen       |    0.102
SBL Stage2: App_loadImages              |    3.720
SBL Stage2: App_loadMCUImages           |    6.542
SBL Stage2: App_loadLinuxImages         |   19.179
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.943

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 165 KB
- Size of images loaded by stage2  : 895 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.593
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   19.695
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    8.645
----------------------------------------|--------------
SBL Stage1: Total time taken            |   66.935


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.568
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.258
SBL Stage2: SBL Drivers_open            |   21.711
SBL Stage2: App_loadImages              |    5.220
SBL Stage2: App_loadMCUImages           |    7.239
SBL Stage2: App_loadLinuxImages         |   20.068
----------------------------------------|--------------
SBL Stage2: Total time taken            |   57.068

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
wkup-r5f0-0 | mcu-r5f0-0  |  1.12

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us)
------------|-------------|--------------|------------------------------|------------------
 wkup-r5f0-0|   mcu-r5f0-0|            32|                        14.343|                15
 wkup-r5f0-0|   mcu-r5f0-0|            64|                        21.065|                22
 wkup-r5f0-0|   mcu-r5f0-0|           112|                        31.077|                31


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	       | 40.54		    | 45.06
 SDR50 | 4	       | 41.50		    | 45.56
 SDR50 | 6	       | 36.28		    | 45.59
 DDR50 | 1	       | 67.59		    | 81.92
 DDR50 | 4	       | 70.87		    | 83.64
 DDR50 | 6	       | 71.18		    | 83.74
 HS200 | 1	       | 100.52		    | 158.66
 HS200 | 4	       | 74.83		    | 169.46
 HS200 | 6	       | 90.15		    | 169.87
 HS400 | 1	       | 100.67		    | 242.17
 HS400 | 4	       | 108.80		    | 267.32
 HS400 | 6	       | 83.54		    | 263.86

### OSPI NOR Flash Performance
Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
PHY : enabled
DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 0.42		        | 283.57
 5	           | 0.42		        | 284.78
 10	           | 0.43		        | 284.93
# Datasheet {#DATASHEET_AM62PX_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Generic Setup details

SOC Details             | Values
------------------------|------------------------------
Core                    | R5F
Core Operating Speed    | 800 MHz
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
- Size of images loaded by stage1  : 195 KB
- Size of images loaded by stage2  : 908 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.266
SBL Stage1: App_waitForMcuPbist         |    0.002
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.090
SBL Stage1: SBL Drivers_open            |    0.133
SBL Stage1: Board_driversOpen           |    0.009
SBL Stage1: SBL Board_driversOpen       |    1.281
SBL Stage1: App_loadSelfcoreImage       |    4.212
----------------------------------------|--------------
SBL Stage1: Total time taken            |   43.997

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.157
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.257
SBL Stage2: SBL Drivers_open            |    1.002
SBL Stage2: SBL Board_driversOpen       |    0.132
SBL Stage2: App_loadImages              |    3.691
SBL Stage2: App_loadMCUImages           |    6.550
SBL Stage2: App_loadLinuxImages         |   19.0098
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.894

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 168 KB
- Size of images loaded by stage2  : 908 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.098
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   20.432
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    8.567
----------------------------------------|--------------
SBL Stage1: Total time taken            |   67.098


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.066
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.258
SBL Stage2: SBL Drivers_open            |   22.945
SBL Stage2: App_loadImages              |    5.256
SBL Stage2: App_loadMCUImages           |    8.062
SBL Stage2: App_loadLinuxImages         |   19.548
----------------------------------------|--------------
SBL Stage2: Total time taken            |   58.138

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

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
 wkup-r5f0-0|   mcu-r5f0-0|            32|                        14.233|                15|         1000
 wkup-r5f0-0|   mcu-r5f0-0|            64|                        20.666|                21|         1000
 wkup-r5f0-0|   mcu-r5f0-0|           112|                        30.199|                31|         1000


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	       | 9.13		    | 44.98
 SDR50 | 4	       | 25.90		    | 45.55
 SDR50 | 6	       | 41.53		    | 45.58
 DDR50 | 1	       | 69.22		    | 82.07
 DDR50 | 4	       | 70.97		    | 83.69
 DDR50 | 6	       | 52.52		    | 83.77
 HS200 | 1	       | 104.45		    | 157.70
 HS200 | 4	       | 107.78		    | 169.40
 HS200 | 6	       | 110.31		    | 169.82
 HS400 | 1	       | 100.81		    | 238.15
 HS400 | 4	       | 74.93		    | 265.60
 HS400 | 6	       | 89.85		    | 264.73

### OSPI NOR Flash Performance
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 0.42		        | 283.57
 5	           | 0.42		        | 284.78
 10	           | 0.43		        | 284.93

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          3.39 ms
Fast Tuning Window          |          1.15 ms

 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2
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
- Size of images loaded by stage1  : 256 KB
- Size of images loaded by stage2  : 886 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   27.921
SBL Stage1: App_waitForMcuPbist         |    0.002
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.001
SBL Stage1: SBL Drivers_open            |    0.151
SBL Stage1: Board_driversOpen           |    0.009
SBL Stage1: SBL Board_driversOpen       |    1.342
SBL Stage1: App_loadSelfcoreImage       |    4.452
----------------------------------------|--------------
SBL Stage1: Total time taken            |   33.882

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.992
SBL Stage2: Board_init                  |    0.002
SBL Stage2: FreeRtosTask Create         |    0.260
SBL Stage2: SBL Drivers_open            |    1.177
SBL Stage2: SBL Board_driversOpen       |    0.222
SBL Stage2: App_loadImages              |    3.828
SBL Stage2: App_loadMCUImages           |    4.212
SBL Stage2: App_loadLinuxImages         |   13.788
----------------------------------------|--------------
SBL Stage2: Total time taken            |   25.484

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 231 KB
- Size of images loaded by stage2  : 914 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   27.640
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   20.413
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    8.989
----------------------------------------|--------------
SBL Stage1: Total time taken            |   57.044


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.991
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.260
SBL Stage2: SBL Drivers_open            |   22.870
SBL Stage2: App_loadImages              |    5.514
SBL Stage2: App_loadMCUImages           |    6.089
SBL Stage2: App_loadLinuxImages         |   18.346
----------------------------------------|--------------
SBL Stage2: Total time taken            |   55.073

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### CPSW Performance

For CPSW performance refer \ref enetlld_performance

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
wkup-r5f0-0 | mcu-r5f0-0  |  1.24

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
 wkup-r5f0-0|   mcu-r5f0-0|            32|                        14.758|                16|         1000
 wkup-r5f0-0|   mcu-r5f0-0|            64|                        21.329|                22|         1000
 wkup-r5f0-0|   mcu-r5f0-0|           112|                        30.709|                32|         1000


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 HS200 | 1	            | 71.69	     	     | 158.83
 HS200 | 4	            | 108.75		     | 169.52
 HS200 | 6	            | 86.61		         | 152.17
 HS200 | 32	            | 100.89 		     | 166.79
 HS200 | 40	            | 97.13 		     | 167.42
 HS400 | 1	            | 41.95	     	     | 246.32
 HS400 | 4	            | 101.31		     | 268.21
 HS400 | 6	            | 102.44		     | 225.61
 HS400 | 32	            | 90.79 		     | 258.12
 HS400 | 40	            | 93.12 		     | 258.64

### OSPI NOR Flash Performance

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          3.47 ms
Fast Tuning Window          |          1.17 ms


 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.41          |       2.87
      5          |        DAC        |        No         |        0.42          |       2.87
      10         |        DAC        |        No         |        0.42          |       2.87
      1          |        DAC        |        Yes        |        0.42          |       48.72
      5          |        DAC        |        Yes        |        0.42          |       48.76
      10         |        DAC        |        Yes        |        0.42          |       48.76

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.39           |       5.87
      5          |        DAC        |        No         |        0.40           |       5.87
      10         |        DAC        |        No         |        0.40           |       5.87
      1          |        DAC        |        Yes        |        0.40           |       6.23
      5          |        DAC        |        Yes        |        0.40           |       6.23
      10         |        DAC        |        Yes        |        0.40           |       6.23

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       6.39
      5          |        DAC        |        No         |        0.42           |       6.38
      10         |        DAC        |        No         |        0.42           |       6.38
      1          |        DAC        |        Yes        |        0.42           |       233.67
      5          |        DAC        |        Yes        |        0.42           |       234.62
      10         |        DAC        |        Yes        |        0.42           |       234.74

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       7.04
      5          |        DAC        |        No         |        0.42          |       7.04
      10         |        DAC        |        No         |        0.42          |       7.04
      1          |        DAC        |        Yes        |        0.42          |       283.36
      5          |        DAC        |        Yes        |        0.42          |       284.72
      10         |        DAC        |        Yes        |        0.42          |       284.89

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.42          |       13.91
      5          |       INDAC       |        No         |        0.42          |       13.91
      10         |       INDAC       |        No         |        0.42          |       13.91

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.40          |       6.25
      5          |       INDAC       |        No         |        0.40          |       6.25
      10         |       INDAC       |        No         |        0.40          |       6.25

 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2
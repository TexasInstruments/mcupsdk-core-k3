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
SBL Stage1: System_init                 |   37.864
SBL Stage1: App_waitForMcuPbist         |    0.002
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |    0.153
SBL Stage1: Board_driversOpen           |    0.009
SBL Stage1: SBL Board_driversOpen       |    1.267
SBL Stage1: App_loadSelfcoreImage       |    4.531
----------------------------------------|--------------
SBL Stage1: Total time taken            |   43.829

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.167
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.301
SBL Stage2: SBL Drivers_open            |    0.967
SBL Stage2: SBL Board_driversOpen       |    0.133
SBL Stage2: App_loadImages              |    3.751
SBL Stage2: App_loadMCUImages           |    4.141
SBL Stage2: App_loadLinuxImages         |   12.013
----------------------------------------|--------------
SBL Stage2: Total time taken            |   23.481

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
SBL Stage1: System_init                 |   37.843
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   20.376
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    9.024
----------------------------------------|--------------
SBL Stage1: Total time taken            |   67.245


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.995
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.259
SBL Stage2: SBL Drivers_open            |   24.204
SBL Stage2: App_loadImages              |    6.087
SBL Stage2: App_loadMCUImages           |    6.728
SBL Stage2: App_loadLinuxImages         |   15.853
----------------------------------------|--------------
SBL Stage2: Total time taken            |   55.129

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
wkup-r5f0-0 | mcu-r5f0-0  |  1.25

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
 wkup-r5f0-0|   mcu-r5f0-0|            32|                        15.205|                16|         1000
 wkup-r5f0-0|   mcu-r5f0-0|            64|                        21.343|                22|         1000
 wkup-r5f0-0|   mcu-r5f0-0|           112|                        31.146|                32|         1000


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            |  9.30	             | 45.05
 SDR50 | 4	            | 27.06		         | 45.56
 SDR50 | 6	            | 41.62		         | 45.58
 SDR50 | 32	            | 39.29		         | 44.62
 SDR50 | 40	            | 39.91		         | 44.62
 DDR50 | 1	            | 54.11		         | 82.03
 DDR50 | 4	            | 70.94		         | 83.67
 DDR50 | 6	            | 70.96		         | 79.35
 DDR50 | 32	            | 65.77		         | 83.02
 DDR50 | 40	            | 65.04		         | 83.17
 HS200 | 1	            | 43.70	     	     | 160.41
 HS200 | 4	            | 108.59		     | 169.54
 HS200 | 6	            | 109.68		     | 152.11
 HS200 | 32	            | 95.38 		     | 166.77
 HS200 | 40	            | 99.45 		     | 167.39

### OSPI NOR Flash Performance

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          3.47 ms
Fast Tuning Window          |          1.17 ms


 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.46          |       2.87
      5          |        No         |        0.47          |       2.87
      10         |        No         |        0.47          |       2.87
      1          |        Yes        |        0.46          |       48.72
      5          |        Yes        |        0.47          |       48.76
      10         |        Yes        |        0.47          |       48.76

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled


 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.43          |       5.87
      5          |        No         |        0.44          |       5.87
      10         |        No         |        0.44          |       5.87
      1          |        Yes        |        0.43          |       6.23
      5          |        Yes        |        0.44          |       6.23
      10         |        Yes        |        0.44          |       6.23

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled


 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.46          |       6.39
      5          |        No         |        0.46          |       6.39
      10         |        No         |        0.46          |       6.38
      1          |        Yes        |        0.46          |       233.79
      5          |        Yes        |        0.47          |       234.65
      10         |        Yes        |        0.46          |       234.76

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled


 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.46          |       7.04
      5          |        No         |        0.47          |       7.04
      10         |        No         |        0.46          |       7.04
      1          |        Yes        |        0.46          |       283.55
      5          |        Yes        |        0.47          |       284.78
      10         |        Yes        |        0.47          |       284.92

 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2
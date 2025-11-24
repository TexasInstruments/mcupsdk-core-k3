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

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 257 KB
- Size of images loaded by stage2  : 1061 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   28.049
SBL Stage1: App_waitForMcuPbist         |    0.002
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |    0.153
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: SBL Board_driversOpen       |    7.028
SBL Stage1: App_loadSelfcoreImage       |    5.203
----------------------------------------|--------------
SBL Stage1: Total time taken            |   40.439

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.179
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.260
SBL Stage2: SBL Drivers_open            |    0.993
SBL Stage2: SBL Board_driversOpen       |    0.522
SBL Stage2: App_loadImages              |    5.444
SBL Stage2: App_loadMCUImages           |    5.963
SBL Stage2: App_loadLinuxImages         |   14.506
----------------------------------------|--------------
SBL Stage2: Total time taken            |   29.873

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL OSPI NOR performance (HS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 257 KB
- Size of images loaded by stage2  : 1061 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   28.190
SBL Stage1: App_waitForMcuPbist         |    0.002
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |    0.153
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: SBL Board_driversOpen       |    6.930
SBL Stage1: App_loadSelfcoreImage       |    5.210
----------------------------------------|--------------
SBL Stage1: Total time taken            |   40.489

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.178
SBL Stage2: Board_init                  |    0.004
SBL Stage2: FreeRtosTask Create         |    0.259
SBL Stage2: SBL Drivers_open            |    0.997
SBL Stage2: SBL Board_driversOpen       |    0.519
SBL Stage2: App_loadImages              |    5.457
SBL Stage2: App_loadMCUImages           |    5.948
SBL Stage2: App_loadLinuxImages         |   14.531
----------------------------------------|--------------
SBL Stage2: Total time taken            |   29.896

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 230 KB
- Size of images loaded by stage2  : 1116 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   27.932
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   21.534
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    8.870
----------------------------------------|--------------
SBL Stage1: Total time taken            |   58.338


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.010
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.302
SBL Stage2: SBL Drivers_open            |   24.225
SBL Stage2: App_loadImages              |    5.757
SBL Stage2: App_loadMCUImages           |    7.218
SBL Stage2: App_loadLinuxImages         |   16.560
----------------------------------------|--------------
SBL Stage2: Total time taken            |   56.076

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 230 KB
- Size of images loaded by stage2  : 1116 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   27.828
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   21.508
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    8.904
----------------------------------------|--------------
SBL Stage1: Total time taken            |   58.242


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.998
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.302
SBL Stage2: SBL Drivers_open            |   24.042
SBL Stage2: App_loadImages              |    5.769
SBL Stage2: App_loadMCUImages           |    7.244
SBL Stage2: App_loadLinuxImages         |   16.576
----------------------------------------|--------------
SBL Stage2: Total time taken            |   55.934

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
 wkup-r5f0-0|   mcu-r5f0-0|            32|                        14.864|                16|         1000
 wkup-r5f0-0|   mcu-r5f0-0|            64|                        21.329|                22|         1000
 wkup-r5f0-0|   mcu-r5f0-0|           112|                        30.945|                32|         1000


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 9.41	     	     | 45.00
 SDR50 | 4	            | 28.41  		     | 45.55
 SDR50 | 6	            | 41.63  		     | 45.58
 SDR50 | 32	            | 39.39 		     | 45.08
 SDR50 | 40	            | 38.74 		     | 44.32
 DDR50 | 1	            | 10.58     	     | 82.26
 DDR50 | 4	            | 41.90 		     | 83.64
 DDR50 | 6	            | 70.90 		     | 79.32
 DDR50 | 32	            | 63.52 		     | 82.96
 DDR50 | 40	            | 65.58 		     | 83.17
 HS200 | 1	            | 71.49	     	     | 162.24
 HS200 | 4	            | 106.83		     | 169.39
 HS200 | 6	            | 73.28		         | 151.96
 HS200 | 32	            | 96.16 		     | 166.56
 HS200 | 40	            | 93.07 		     | 167.41
 HS400 | 1	            | 70.77	     	     | 243.80
 HS400 | 4	            | 107.60		     | 266.76
 HS400 | 6	            | 107.88		     | 222.71
 HS400 | 32	            | 91.83 		     | 255.36
 HS400 | 40	            | 95.79 		     | 258.51

### OSPI NOR Flash Performance  {#OSPI_DATA_SHEET}

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 51.40

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.51  ms
Fast Tuning Window          |          0.55  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          9.65 ms
Fast Tuning Window          |          6.43 ms


 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.41          |       2.87
      5          |        DAC        |        No         |        0.42          |       2.87
      10         |        DAC        |        No         |        0.42          |       2.87
      1          |        DAC        |        Yes        |        0.41          |       48.72
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
      1          |        DAC        |        Yes        |        0.39           |       6.23
      5          |        DAC        |        Yes        |        0.40           |       6.23
      10         |        DAC        |        Yes        |        0.40           |       6.23

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       4.09
      5          |        DAC        |        No         |        0.42           |       4.09
      10         |        DAC        |        No         |        0.42           |       4.09
      1          |        DAC        |        Yes        |        0.42           |       48.73
      5          |        DAC        |        Yes        |        0.42           |       48.76
      10         |        DAC        |        Yes        |        0.42           |       48.76

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       5.97
      5          |        DAC        |        No         |        0.42           |       5.97
      10         |        DAC        |        No         |        0.41           |       5.97
      1          |        DAC        |        Yes        |        0.41           |       124.57
      5          |        DAC        |        Yes        |        0.42           |       124.82
      10         |        DAC        |        Yes        |        0.41           |       124.85

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       6.38
      5          |        DAC        |        No         |        0.42           |       6.38
      10         |        DAC        |        No         |        0.42           |       6.38
      1          |        DAC        |        Yes        |        0.41           |       233.80
      5          |        DAC        |        Yes        |        0.42           |       234.65
      10         |        DAC        |        Yes        |        0.42           |       234.76

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       6.72
      5          |        DAC        |        No         |        0.42           |       6.72
      10         |        DAC        |        No         |        0.42           |       6.72
      1          |        DAC        |        Yes        |        0.42           |       153.20
      5          |        DAC        |        Yes        |        0.42           |       153.58
      10         |        DAC        |        Yes        |        0.42           |       153.62

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       7.04
      5          |        DAC        |        No         |        0.42          |       7.04
      10         |        DAC        |        No         |        0.42          |       7.04
      1          |        DAC        |        Yes        |        0.41          |       283.56
      5          |        DAC        |        Yes        |        0.42          |       284.77
      10         |        DAC        |        Yes        |        0.42          |       284.92

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.41          |       13.91
      5          |       INDAC       |        No         |        0.42          |       13.91
      10         |       INDAC       |        No         |        0.42          |       13.91

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.39          |       6.25
      5          |       INDAC       |        No         |        0.40          |       6.25
      10         |       INDAC       |        No         |        0.40          |       6.25

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.45           |       13.93
      5          |       INDAC       |        No         |        0.46           |       13.93
      10         |       INDAC       |        No         |        0.46           |       13.93

 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2
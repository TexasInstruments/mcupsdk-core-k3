# Datasheet


## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for {{ VAR_SOC_NAME }}


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
- Size of images loaded by stage1  : 242 KB
- Size of images loaded by stage2  : 1080 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   27.961
SBL Stage1: App_waitForMcuPbist         |    0.091
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.001
SBL Stage1: SBL Drivers_open            |    0.157
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: SBL Board_driversOpen       |    7.124
SBL Stage1: App_loadSelfcoreImage       |    5.110
----------------------------------------|--------------
SBL Stage1: Total time taken            |   40.447

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.011
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.261
SBL Stage2: SBL Drivers_open            |    1.167
SBL Stage2: SBL Board_driversOpen       |    0.525
SBL Stage2: App_loadImages              |    5.439
SBL Stage2: App_loadMCUImages           |    5.946
SBL Stage2: App_loadLinuxImages         |   14.043
----------------------------------------|--------------
SBL Stage2: Total time taken            |   29.397

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL OSPI NOR performance (HS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 242 KB
- Size of images loaded by stage2  : 1080 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   27.839
SBL Stage1: App_waitForMcuPbist         |    0.092
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.001
SBL Stage1: SBL Drivers_open            |    0.158
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: SBL Board_driversOpen       |    7.067
SBL Stage1: App_loadSelfcoreImage       |    5.110
----------------------------------------|--------------
SBL Stage1: Total time taken            |   40.268

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.001
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.260
SBL Stage2: SBL Drivers_open            |    1.166
SBL Stage2: SBL Board_driversOpen       |    0.524
SBL Stage2: App_loadImages              |    5.454
SBL Stage2: App_loadMCUImages           |    5.943
SBL Stage2: App_loadLinuxImages         |   14.046
----------------------------------------|--------------
SBL Stage2: Total time taken            |   29.401

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 231 KB
- Size of images loaded by stage2  : 1080 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   28.607
SBL Stage1: Board_init                  |    0.092
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   21.722
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    6.346
SBL Stage1: PBIST Positive Tests        |    0.268
SBL Stage1: PBIST Negative Tests        |    0.675
----------------------------------------|--------------
SBL Stage1: Total time taken            |   57.713


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.144
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.304
SBL Stage2: SBL Drivers_open            |   24.465
SBL Stage2: App_loadImages              |    3.902
SBL Stage2: App_loadMCUImages           |    4.628
SBL Stage2: App_loadLinuxImages         |   14.359
----------------------------------------|--------------
SBL Stage2: Total time taken            |   49.804

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 231 KB
- Size of images loaded by stage2  : 1080 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   28.432
SBL Stage1: Board_init                  |    0.093
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   21.734
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    6.299
SBL Stage1: PBIST Positive Tests        |    0.270
SBL Stage1: PBIST Negative Tests        |    0.673
----------------------------------------|--------------
SBL Stage1: Total time taken            |   57.503


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.143
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.302
SBL Stage2: SBL Drivers_open            |   24.286
SBL Stage2: App_loadImages              |    3.985
SBL Stage2: App_loadMCUImages           |    4.643
SBL Stage2: App_loadLinuxImages         |   14.303
----------------------------------------|--------------
SBL Stage2: Total time taken            |   49.664

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### CPSW Performance

For CPSW performance refer [Ethernet Performance](../components/networking/enet_lld/enet_cpsw_performance_am62px.md)

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
wkup-r5f0-0 | mcu-r5f0-0  |  1.250

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
 wkup-r5f0-0|   mcu-r5f0-0|            32|                        15.016|                16|         1000
 wkup-r5f0-0|   mcu-r5f0-0|            64|                        21.332|                22|         1000
 wkup-r5f0-0|   mcu-r5f0-0|           112|                        31.167|                32|         1000


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 40.59            | 45.14
 SDR50 | 4	            | 41.57         | 45.54
 SDR50 | 6	            | 41.63         | 45.57
 SDR50 | 32	            | 38.94        | 44.06
 SDR50 | 40	            | 39.43        | 45.22
 DDR50 | 1	            | 54.01           | 81.81
 DDR50 | 4	            | 70.67        | 83.62
 DDR50 | 6	            | 60.09        | 79.33
 DDR50 | 32	            | 64.18        | 82.97
 DDR50 | 40	            | 65.84        | 83.17
 HS200 | 1	            | 72.98            | 159.82
 HS200 | 4	            | 108.41       | 169.33
 HS200 | 6	            | 109.66           | 152.03
 HS200 | 32	            | 93.84        | 166.55
 HS200 | 40	            | 97.89        | 167.40
 HS400 | 1	            | 38.38            | 244.88
 HS400 | 4	            | 81.15       | 267.77
 HS400 | 6	            | 109.23       | 225.52
 HS400 | 32	            | 93.74        | 256.09
 HS400 | 40	            | 97.82        | 260.24

### OSPI NOR Flash Performance 

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 56.03

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.52  ms
Fast Tuning Window          |          0.56  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          9.61 ms
Fast Tuning Window          |          6.44 ms


 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.44          |       2.87
      5          |        DAC        |        No         |        0.45          |       2.87
      10         |        DAC        |        No         |        0.45          |       2.87
      1          |        DAC        |        Yes        |        0.44          |       48.72
      5          |        DAC        |        Yes        |        0.44          |       48.76
      10         |        DAC        |        Yes        |        0.45          |       48.76

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       5.87
      5          |        DAC        |        No         |        0.42           |       5.87
      10         |        DAC        |        No         |        0.42           |       5.87
      1          |        DAC        |        Yes        |        0.41           |       6.23
      5          |        DAC        |        Yes        |        0.42           |       6.23
      10         |        DAC        |        Yes        |        0.42           |       6.23

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       4.08
      5          |        DAC        |        No         |        0.44           |       4.08
      10         |        DAC        |        No         |        0.45           |       4.08
      1          |        DAC        |        Yes        |        0.44           |       48.73
      5          |        DAC        |        Yes        |        0.44           |       48.76
      10         |        DAC        |        Yes        |        0.45           |       48.76

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       5.97
      5          |        DAC        |        No         |        0.43           |       5.97
      10         |        DAC        |        No         |        0.44           |       5.97
      1          |        DAC        |        Yes        |        0.43           |       124.59
      5          |        DAC        |        Yes        |        0.44           |       124.82
      10         |        DAC        |        Yes        |        0.44           |       124.85

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       6.38
      5          |        DAC        |        No         |        0.44           |       6.38
      10         |        DAC        |        No         |        0.44           |       6.38
      1          |        DAC        |        Yes        |        0.44           |       233.82
      5          |        DAC        |        Yes        |        0.44           |       234.65
      10         |        DAC        |        Yes        |        0.44           |       234.76

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       6.72
      5          |        DAC        |        No         |        0.44           |       6.72
      10         |        DAC        |        No         |        0.44           |       6.72
      1          |        DAC        |        Yes        |        0.43           |       153.22
      5          |        DAC        |        Yes        |        0.44           |       153.58
      10         |        DAC        |        Yes        |        0.44           |       153.62

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.44          |       7.04
      5          |        DAC        |        No         |        0.44          |       7.04
      10         |        DAC        |        No         |        0.44          |       7.04
      1          |        DAC        |        Yes        |        0.44          |       283.52
      5          |        DAC        |        Yes        |        0.44          |       284.77
      10         |        DAC        |        Yes        |        0.44          |       284.92

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.44          |       13.91
      5          |       INDAC       |        No         |        0.44          |       13.91
      10         |       INDAC       |        No         |        0.45          |       13.91

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.42          |       6.25
      5          |       INDAC       |        No         |        0.42          |       6.25
      10         |       INDAC       |        No         |        0.42          |       6.25

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.44           |       13.93
      5          |       INDAC       |        No         |        0.44           |       13.93
      10         |       INDAC       |        No         |        0.45           |       13.93

 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2
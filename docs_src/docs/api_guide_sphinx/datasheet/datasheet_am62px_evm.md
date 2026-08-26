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

### CPSW

For CPSW performance refer [Ethernet Performance](../components/networking/enet_lld/enet_cpsw_performance_am62px.md)

### DDR

- Software/Application used        : ddr_perf
- Measured on wkup-r5f0-0

DDR Bandwidth | Value (MiB/s)
--------------|--------------
Read          | 279
Write         | 309
Total         | 588

### EMMC

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 33.56            | 42.88
 SDR50 | 4	            | 39.62         | 43.43
 SDR50 | 6	            | 39.68         | 42.19
 SDR50 | 32	            | 37.48        | 43.25
 SDR50 | 40	            | 37.42        | 43.30
 DDR50 | 1	            | 51.54           | 78.33
 DDR50 | 4	            | 54.05        | 79.74
 DDR50 | 6	            | 67.91        | 75.65
 DDR50 | 32	            | 60.75        | 79.12
 DDR50 | 40	            | 62.63        | 79.31
 HS200 | 1	            | 67.43            | 150.78
 HS200 | 4	            | 104.73       | 161.45
 HS200 | 6	            | 72.31           | 145.02
 HS200 | 32	            | 93.49        | 158.87
 HS200 | 40	            | 90.80        | 159.67
 HS400 | 1	            | 68.43            | 232.72
 HS400 | 4	            | 104.61       | 254.92
 HS400 | 6	            | 104.81       | 213.42
 HS400 | 32	            | 89.85        | 244.33
 HS400 | 40	            | 93.59        | 248.05

### I2C

- Data write/read throughput measured at 100 kHz and 400 kHz, in polling and interrupt transfer modes
- MiB/s computed from Data Size / Transfer Time (firmware's floating-point throughput print does not render on this build; transfer time is measured directly)

**mcu-r5f0-0:**

Mode      | Freq    | Data Size (B) | Write MiB/s | Write Time (us) | Read MiB/s | Read Time (us)
----------|---------|---------------|-------------|------------------|------------|---------------
POLLING   | 100 kHz | 64            | 0.01        | 6066             | 0.01       | 6175
POLLING   | 100 kHz | 128           | 0.01        | 11825            | 0.01       | 11934
POLLING   | 100 kHz | 256           | 0.01        | 23343            | 0.01       | 23452
POLLING   | 400 kHz | 64            | 0.04        | 1622             | 0.04       | 1653
POLLING   | 400 kHz | 128           | 0.04        | 3159             | 0.04       | 3189
POLLING   | 400 kHz | 256           | 0.04        | 6230             | 0.04       | 6261
INTERRUPT | 100 kHz | 64            | 0.01        | 6064             | 0.01       | 6178
INTERRUPT | 100 kHz | 128           | 0.01        | 11824            | 0.01       | 11938
INTERRUPT | 100 kHz | 256           | 0.01        | 23343            | 0.01       | 23456
INTERRUPT | 400 kHz | 64            | 0.04        | 1622             | 0.04       | 1656
INTERRUPT | 400 kHz | 128           | 0.04        | 3158             | 0.04       | 3192
INTERRUPT | 400 kHz | 256           | 0.04        | 6230             | 0.04       | 6264

**wkup-r5f0-0:**

Mode      | Freq    | Data Size (B) | Write MiB/s | Write Time (us) | Read MiB/s | Read Time (us)
----------|---------|---------------|-------------|------------------|------------|---------------
POLLING   | 100 kHz | 64            | 0.01        | 6064             | 0.01       | 6173
POLLING   | 100 kHz | 128           | 0.01        | 11824            | 0.01       | 11932
POLLING   | 100 kHz | 256           | 0.01        | 23342            | 0.01       | 23450
POLLING   | 400 kHz | 64            | 0.04        | 1570             | 0.04       | 1599
POLLING   | 400 kHz | 128           | 0.04        | 3058             | 0.04       | 3086
POLLING   | 400 kHz | 256           | 0.04        | 6034             | 0.04       | 6063
INTERRUPT | 100 kHz | 64            | 0.01        | 6061             | 0.01       | 6173
INTERRUPT | 100 kHz | 128           | 0.01        | 11821            | 0.01       | 11933
INTERRUPT | 100 kHz | 256           | 0.01        | 23340            | 0.01       | 23452
INTERRUPT | 400 kHz | 64            | 0.04        | 1569             | 0.04       | 1600
INTERRUPT | 400 kHz | 128           | 0.04        | 3057             | 0.04       | 3088
INTERRUPT | 400 kHz | 256           | 0.04        | 6033             | 0.04       | 6064

### IPC

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
wkup-r5f0-0 | mcu-r5f0-0  |  1.260

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
 wkup-r5f0-0|   mcu-r5f0-0|            32|                        14.855|                17|         1000
 wkup-r5f0-0|   mcu-r5f0-0|            64|                        21.329|                22|         1000
 wkup-r5f0-0|   mcu-r5f0-0|           112|                        31.073|                32|         1000


(ospi-nor-flash-performance)=
### OSPI NOR Flash

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 56.03

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.49  ms
Fast Tuning Window          |          0.54  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          9.86 ms
Fast Tuning Window          |          6.57 ms


 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 2.87 |
| 5 | DAC | No | 0.43 | 2.87 |
| 10 | DAC | No | 0.43 | 2.87 |
| 1 | DAC | Yes | 0.43 | 48.72 |
| 5 | DAC | Yes | 0.43 | 48.76 |
| 10 | DAC | Yes | 0.43 | 48.76 |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.41 | 5.87 |
| 5 | DAC | No | 0.41 | 5.87 |
| 10 | DAC | No | 0.41 | 5.87 |
| 1 | DAC | Yes | 0.41 | 6.23 |
| 5 | DAC | Yes | 0.41 | 6.23 |
| 10 | DAC | Yes | 0.41 | 6.23 |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 4.08 |
| 5 | DAC | No | 0.43 | 4.08 |
| 10 | DAC | No | 0.43 | 4.08 |
| 1 | DAC | Yes | 0.43 | 48.73 |
| 5 | DAC | Yes | 0.43 | 48.76 |
| 10 | DAC | Yes | 0.43 | 48.76 |

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.42 | 5.97 |
| 5 | DAC | No | 0.42 | 5.97 |
| 10 | DAC | No | 0.42 | 5.97 |
| 1 | DAC | Yes | 0.42 | 124.59 |
| 5 | DAC | Yes | 0.42 | 124.83 |
| 10 | DAC | Yes | 0.42 | 124.85 |

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 6.39 |
| 5 | DAC | No | 0.43 | 6.38 |
| 10 | DAC | No | 0.43 | 6.38 |
| 1 | DAC | Yes | 0.43 | 233.80 |
| 5 | DAC | Yes | 0.43 | 234.65 |
| 10 | DAC | Yes | 0.43 | 234.76 |

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 6.72 |
| 5 | DAC | No | 0.42 | 6.72 |
| 10 | DAC | No | 0.43 | 6.72 |
| 1 | DAC | Yes | 0.42 | 153.23 |
| 5 | DAC | Yes | 0.42 | 153.58 |
| 10 | DAC | Yes | 0.43 | 153.62 |
 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 7.04 |
| 5 | DAC | No | 0.43 | 7.04 |
| 10 | DAC | No | 0.43 | 7.04 |
| 1 | DAC | Yes | 0.43 | 283.58 |
| 5 | DAC | Yes | 0.43 | 284.77 |
| 10 | DAC | Yes | 0.43 | 284.92 |

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.43 | 13.91 |
| 5 | INDAC | No | 0.43 | 13.91 |
| 10 | INDAC | No | 0.43 | 13.91 |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.41 | 6.25 |
| 5 | INDAC | No | 0.41 | 6.25 |
| 10 | INDAC | No | 0.41 | 6.25 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.43 | 13.93 |
| 5 | INDAC | No | 0.43 | 13.93 |
| 10 | INDAC | No | 0.43 | 13.93 |

## Latency

### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2

## SBL Performance

### SBL OSPI NOR (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 243 KB
- Size of images loaded by stage2  : 1087 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   27.899
SBL Stage1: App_waitForMcuPbist         |    0.092
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.001
SBL Stage1: SBL Drivers_open            |    0.160
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: SBL Board_driversOpen       |    6.975
SBL Stage1: App_loadSelfcoreImage       |    5.111
----------------------------------------|--------------
SBL Stage1: Total time taken            |   40.242

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.010
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.383
SBL Stage2: SBL Drivers_open            |    1.040
SBL Stage2: SBL Board_driversOpen       |    0.524
SBL Stage2: App_loadImages              |    5.442
SBL Stage2: App_loadMCUImages           |    5.953
SBL Stage2: App_loadLinuxImages         |   14.559
----------------------------------------|--------------
SBL Stage2: Total time taken            |   29.917

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL OSPI NOR (HS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 243 KB
- Size of images loaded by stage2  : 1085 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   28.211
SBL Stage1: App_waitForMcuPbist         |    0.092
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.001
SBL Stage1: SBL Drivers_open            |    0.159
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: SBL Board_driversOpen       |    7.011
SBL Stage1: App_loadSelfcoreImage       |    5.114
----------------------------------------|--------------
SBL Stage1: Total time taken            |   40.592

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.023
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.383
SBL Stage2: SBL Drivers_open            |    1.031
SBL Stage2: SBL Board_driversOpen       |    0.525
SBL Stage2: App_loadImages              |    5.456
SBL Stage2: App_loadMCUImages           |    5.936
SBL Stage2: App_loadLinuxImages         |   14.552
----------------------------------------|--------------
SBL Stage2: Total time taken            |   29.912

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 232 KB
- Size of images loaded by stage2  : 1087 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   28.468
SBL Stage1: Board_init                  |    0.093
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   21.733
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    6.744
SBL Stage1: PBIST Positive Tests        |    0.270
SBL Stage1: PBIST Negative Tests        |    0.672
----------------------------------------|--------------
SBL Stage1: Total time taken            |   57.982


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.144
SBL Stage2: Board_init                  |    0.001
SBL Stage2: FreeRtosTask Create         |    0.386
SBL Stage2: SBL Drivers_open            |   26.186
SBL Stage2: App_loadImages              |    5.093
SBL Stage2: App_loadMCUImages           |    4.534
SBL Stage2: App_loadLinuxImages         |   14.455
----------------------------------------|--------------
SBL Stage2: Total time taken            |   52.802

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC (HS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 232 KB
- Size of images loaded by stage2  : 1087 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   28.811
SBL Stage1: Board_init                  |    0.093
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   21.723
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    8.461
SBL Stage1: PBIST Positive Tests        |    0.270
SBL Stage1: PBIST Negative Tests        |    0.682
----------------------------------------|--------------
SBL Stage1: Total time taken            |   60.043


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.140
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.448
SBL Stage2: SBL Drivers_open            |   26.126
SBL Stage2: App_loadImages              |    6.253
SBL Stage2: App_loadMCUImages           |    6.659
SBL Stage2: App_loadLinuxImages         |   16.732
----------------------------------------|--------------
SBL Stage2: Total time taken            |   58.360

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.


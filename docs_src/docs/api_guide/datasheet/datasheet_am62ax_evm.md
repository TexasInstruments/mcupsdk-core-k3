# Datasheet {#DATASHEET_AM62AX_EVM}

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

### SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 192 KB
- Size of images loaded by stage2  : 1203 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   25.924
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.194
SBL Stage1: Board_driversOpen           |   26.783
SBL Stage1: Sciclient Get Version       |   10.170
SBL Stage1: App_waitForMcuPbist         |    0.082
SBL Stage1: MCU R5 Image Load           |    3.273
SBL Stage1: DM R5 Image Load            |    5.888
----------------------------------------|--------------
SBL Stage2: Total time taken            |   72.318

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.713
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.221
SBL Stage2: Board_driversOpen           |   31.003
SBL Stage2: Sciclient Get Version       |   10.217
SBL Stage2: HSM Image Load              |    2.181
SBL Stage2: DM R5 Image Load            |    7.323
SBL Stage2: A53 Image Load              |   12.456
SBL Stage2: DSP Image Load              |   12.375
----------------------------------------|--------------
SBL Stage2: Total time taken            |   94.207

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL OSPI NAND performance (HS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 193 KB
- Size of images loaded by stage2  : 1202 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   26.005
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.194
SBL Stage1: Board_driversOpen           |   26.751
SBL Stage1: Sciclient Get Version       |   10.170
SBL Stage1: App_waitForMcuPbist         |    0.082
SBL Stage1: MCU R5 Image Load           |    3.382
SBL Stage1: DM R5 Image Load            |    5.892
----------------------------------------|--------------
SBL Stage2: Total time taken            |   72.380

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.713
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.222
SBL Stage2: Board_driversOpen           |   31.044
SBL Stage2: Sciclient Get Version       |   10.215
SBL Stage2: HSM Image Load              |    2.187
SBL Stage2: DM R5 Image Load            |    7.327
SBL Stage2: A53 Image Load              |   29.087
SBL Stage2: DSP Image Load              |   12.459
----------------------------------------|--------------
SBL Stage2: Total time taken            |   94.258

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 190 KB
- Size of images loaded by stage2  : 1203 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   26.397
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   20.608
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.168
SBL Stage1: MCU R5 Image Load           |    7.672
SBL Stage1: DM R5 Image Load            |    7.201
----------------------------------------|--------------
SBL Stage1: Total time taken            |   72.047

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.712
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.532
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.263
SBL Stage2: HSM Image Load              |    5.540
SBL Stage2: DM R5 Image Load            |    7.877
SBL Stage2: A53 Image Load              |   19.151
SBL Stage2: DSP Image Load              |   13.695
----------------------------------------|--------------
SBL Stage2: Total time taken            |   78.773

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 199 KB
- Size of images loaded by stage2  : 1203 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   25.910
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   20.628
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.167
SBL Stage1: MCU R5 Image Load           |    6.867
SBL Stage1: DM R5 Image Load            |    7.210
----------------------------------------|--------------
SBL Stage1: Total time taken            |   70.785

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.720
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.532
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.211
SBL Stage2: HSM Image Load              |    6.262
SBL Stage2: DM R5 Image Load            |    7.912
SBL Stage2: A53 Image Load              |   18.452
SBL Stage2: DSP Image Load              |   13.699
----------------------------------------|--------------
SBL Stage2: Total time taken            |   78.792

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | mcu-r5f0-0  |  1.25
 r5f0-0     | a530-0      |  6.67
 r5f0-0     | c75ss0      |  17.36

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
      r5f0-0|       a530-0|             4|                         6.981|                 9|         1000
      r5f0-0|   mcu-r5f0-0|             4|                         8.836|                11|         1000
      r5f0-0|       c75ss0|             4|                        75.545|                88|         1000
      r5f0-0|       a530-0|            32|                         9.442|                12|         1000
      r5f0-0|       a530-0|            64|                        12.405|                16|         1000
      r5f0-0|       a530-0|           112|                        16.918|                21|         1000
      r5f0-0|   mcu-r5f0-0|            32|                        14.442|                18|         1000
      r5f0-0|   mcu-r5f0-0|            64|                        20.714|                24|         1000
      r5f0-0|   mcu-r5f0-0|           112|                        30.186|                36|         1000
      r5f0-0|       c75ss0|            32|                        83.408|                96|         1000
      r5f0-0|       c75ss0|            64|                        96.060|               118|         1000
      r5f0-0|       c75ss0|           112|                       105.467|               134|         1000


### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 8.40		         | 45.05
 SDR50 | 4	            | 41.54	             | 45.56
 SDR50 | 6	            | 37.40		         | 45.58
 SDR50 | 32	            | 40.52	             | 45.62
 SDR50 | 40	            | 39.13		         | 44.26
 DDR50 | 1	            | 53.09		         | 82.43
 DDR50 | 4	            | 70.45	             | 83.66
 DDR50 | 6	            | 71.21		         | 79.34
 DDR50 | 32	            | 64.46	             | 83.02
 DDR50 | 40	            | 66.34		         | 83.16
 HS200 | 1	            | 70.98		         | 158.59
 HS200 | 4	            | 80.88	             | 169.47
 HS200 | 6	            | 80.74	             | 152.06
 HS200 | 32	            | 86.06	             | 166.77
 HS200 | 40	            | 87.05	             | 167.37

**a53ss0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 32.79		         | 46.15
 SDR50 | 4	            | 42.36	             | 46.53
 SDR50 | 6	            | 42.42		         | 46.54
 SDR50 | 32	            | 39.34	             | 46.58
 SDR50 | 40	            | 40.14		         | 46.57
 DDR50 | 1	            | 55.60		         | 85.23
 DDR50 | 4	            | 59.57	             | 86.97
 DDR50 | 6	            | 61.64		         | 87.07
 DDR50 | 32	            | 63.69	             | 87.19
 DDR50 | 40	            | 66.92		         | 87.16
 HS200 | 1	            | 75.93		         | 171.28
 HS200 | 4	            | 112.80	         | 183.63
 HS200 | 6	            | 90.38	             | 184.08
 HS200 | 32	            | 101.92	         | 184.68
 HS200 | 40	            | 98.33	             | 184.57

### OSPI NAND Performance
**r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.14  ms
Fast Tuning Window          |          0.65  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.25          |       4.35
      5          |        DAC        |        No         |        2.25          |       4.33
      10         |        DAC        |        No         |        2.25          |       4.32
      1          |        DAC        |        Yes        |        8.79          |       30.94
      5          |        DAC        |        Yes        |        8.85          |       30.95
      10         |        DAC        |        Yes        |        8.84          |       30.95

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.53           |       5.56
      5          |        DAC        |        No         |        1.53           |       5.56
      10         |        DAC        |        No         |        1.53           |       5.56
      1          |        DAC        |        Yes        |        3.88           |       5.76
      5          |        DAC        |        Yes        |        3.88           |       5.76
      10         |        DAC        |        Yes        |        3.88           |       5.76

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.25           |       3.56
      5          |        DAC        |        No         |        2.25           |       3.56
      10         |        DAC        |        No         |        2.25           |       3.56
      1          |        DAC        |        Yes        |        8.75           |       30.05
      5          |        DAC        |        Yes        |        8.75           |       30.05
      10         |        DAC        |        Yes        |        8.85           |       30.05

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.26           |       5.27
      5          |        DAC        |        No         |        2.25           |       5.28
      10         |        DAC        |        No         |        2.25           |       5.27
      1          |        DAC        |        Yes        |        9.77           |       45.10
      5          |        DAC        |        Yes        |        9.76           |       45.09
      10         |        DAC        |        Yes        |        9.90           |       45.10

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.26          |       5.77
      5          |        DAC        |        No         |        2.25          |       5.77
      10         |        DAC        |        No         |        2.25          |       5.77
      1          |        DAC        |        Yes        |        9.98          |       49.65
      5          |        DAC        |        Yes        |        9.97          |       49.66
      10         |        DAC        |        Yes        |        10.11         |       49.65

**mcu-r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.31  ms
Fast Tuning Window          |          0.75  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        1.96          |       4.08
      5          |        DAC        |        No         |        1.96          |       4.08
      10         |        DAC        |        No         |        1.96          |       4.08
      1          |        DAC        |        Yes        |        8.54          |       29.92
      5          |        DAC        |        Yes        |        8.62          |       29.93
      10         |        DAC        |        Yes        |        8.68          |       29.93

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.43           |       5.36
      5          |        DAC        |        No         |        1.43           |       5.35
      10         |        DAC        |        No         |        1.43           |       5.36
      1          |        DAC        |        Yes        |        3.84           |       5.76
      5          |        DAC        |        Yes        |        3.85           |       5.76
      10         |        DAC        |        Yes        |        3.86           |       5.76

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.95           |       3.39
      5          |        DAC        |        No         |        1.95           |       3.39
      10         |        DAC        |        No         |        1.95           |       3.39
      1          |        DAC        |        Yes        |        8.53           |       30.25
      5          |        DAC        |        Yes        |        8.57           |       30.25
      10         |        DAC        |        Yes        |        8.67           |       30.25

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------
      1          |        DAC        |        No         |        1.96           |       4.93
      5          |        DAC        |        No         |        1.95           |       4.93
      10         |        DAC        |        No         |        1.95           |       4.93
      1          |        DAC        |        Yes        |        9.48           |       45.59
      5          |        DAC        |        Yes        |        9.51           |       45.59
      10         |        DAC        |        Yes        |        9.65           |       45.60

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        1.96          |       5.39
      5          |        DAC        |        No         |        1.95          |       5.39
      10         |        DAC        |        No         |        1.95          |       5.39
      1          |        DAC        |        Yes        |        9.48          |       49.08
      5          |        DAC        |        Yes        |        9.51          |       49.08
      10         |        DAC        |        Yes        |        9.65          |       49.08

 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2
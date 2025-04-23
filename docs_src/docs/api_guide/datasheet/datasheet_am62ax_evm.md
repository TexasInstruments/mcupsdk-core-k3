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
SBL Stage1: System_init                 |   37.327
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.194
SBL Stage1: Board_driversOpen           |   26.591
SBL Stage1: Sciclient Get Version       |   10.171
SBL Stage1: App_waitForMcuPbist         |    0.083
SBL Stage1: MCU R5 Image Load           |    3.258
SBL Stage1: DM R5 Image Load            |    5.800
----------------------------------------|--------------
SBL Stage2: Total time taken            |   83.427

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.741
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.225
SBL Stage2: Board_driversOpen           |   26.452
SBL Stage2: Sciclient Get Version       |   10.217
SBL Stage2: HSM Image Load              |    2.105
SBL Stage2: DM R5 Image Load            |    7.316
SBL Stage2: A53 Image Load              |   25.213
SBL Stage2: DSP Image Load              |   12.375
----------------------------------------|--------------
SBL Stage2: Total time taken            |   85.648

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
SBL Stage1: System_init                 |   36.736
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.194
SBL Stage1: Board_driversOpen           |   26.691
SBL Stage1: Sciclient Get Version       |   10.172
SBL Stage1: App_waitForMcuPbist         |    0.083
SBL Stage1: MCU R5 Image Load           |    3.345
SBL Stage1: DM R5 Image Load            |    5.887
----------------------------------------|--------------
SBL Stage2: Total time taken            |   83.110

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.726
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.222
SBL Stage2: Board_driversOpen           |   26.566
SBL Stage2: Sciclient Get Version       |   10.226
SBL Stage2: HSM Image Load              |    2.193
SBL Stage2: DM R5 Image Load            |    7.407
SBL Stage2: A53 Image Load              |   25.341
SBL Stage2: DSP Image Load              |   12.471
----------------------------------------|--------------
SBL Stage2: Total time taken            |   86.157

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
SBL Stage1: System_init                 |   37.304
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   20.614
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.170
SBL Stage1: MCU R5 Image Load           |    7.329
SBL Stage1: DM R5 Image Load            |    7.193
----------------------------------------|--------------
SBL Stage1: Total time taken            |   82.613

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.739
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.567
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.215
SBL Stage2: HSM Image Load              |    5.471
SBL Stage2: DM R5 Image Load            |    7.877
SBL Stage2: A53 Image Load              |   17.301
SBL Stage2: DSP Image Load              |   13.623
----------------------------------------|--------------
SBL Stage2: Total time taken            |   76.796

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
SBL Stage1: System_init                 |   36.699
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   20.607
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.181
SBL Stage1: MCU R5 Image Load           |    7.651
SBL Stage1: DM R5 Image Load            |    7.243
----------------------------------------|--------------
SBL Stage1: Total time taken            |   82.384

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.761
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.539
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.251
SBL Stage2: HSM Image Load              |    5.542
SBL Stage2: DM R5 Image Load            |    7.943
SBL Stage2: A53 Image Load              |   17.458
SBL Stage2: DSP Image Load              |   13.692
----------------------------------------|--------------
SBL Stage2: Total time taken            |   77.189

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | mcu-r5f0-0  |  1.25
 r5f0-0     | a530-0      |  6.95
 r5f0-0     | c75ss0      |  18.52

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
      r5f0-0|       a530-0|             4|                         7.126|                10|         1000
      r5f0-0|       a530-0|            32|                         9.709|                12|         1000
      r5f0-0|       a530-0|            64|                        12.825|                17|         1000
      r5f0-0|       a530-0|           112|                        17.535|                21|         1000
      r5f0-0|   mcu-r5f0-0|             4|                         9.023|                12|         1000
      r5f0-0|   mcu-r5f0-0|            32|                        14.811|                18|         1000
      r5f0-0|   mcu-r5f0-0|            64|                        21.377|                26|         1000
      r5f0-0|   mcu-r5f0-0|           112|                        31.222|                36|         1000
      r5f0-0|       c75ss0|             4|                        80.614|                94|         1000
      r5f0-0|       c75ss0|            32|                        89.298|               103|         1000
      r5f0-0|       c75ss0|            64|                       100.854|               126|         1000
      r5f0-0|       c75ss0|           112|                       112.348|               129|         1000


### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 37.63		         | 45.16
 SDR50 | 4	            | 42.40	             | 44.50
 SDR50 | 6	            | 41.57		         | 44.94
 SDR50 | 32	            | 42.54	             | 45.41
 SDR50 | 40	            | 42.43		         | 45.53
 DDR50 | 1	            | 48.21		         | 82.39
 DDR50 | 4	            | 53.53	             | 80.17
 DDR50 | 6	            | 61.12		         | 81.60
 DDR50 | 32	            | 59.81	             | 83.17
 DDR50 | 40	            | 60.95		         | 83.57
 HS200 | 1	            | 44.93		         | 164.48
 HS200 | 4	            | 63.79	             | 155.82
 HS200 | 6	            | 63.22	             | 160.95
 HS200 | 32	            | 60.65	             | 167.48
 HS200 | 40	            | 59.19	             | 169.11

**a53ss0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 37.63		         | 45.16
 SDR50 | 4	            | 42.40	             | 44.50
 SDR50 | 6	            | 41.57		         | 44.94
 SDR50 | 32	            | 42.54	             | 45.41
 SDR50 | 40	            | 42.43		         | 45.53
 DDR50 | 1	            | 48.21		         | 82.39
 DDR50 | 4	            | 53.53	             | 80.17
 DDR50 | 6	            | 61.12		         | 81.60
 DDR50 | 32	            | 59.81	             | 83.17
 DDR50 | 40	            | 60.95		         | 83.57
 HS200 | 1	            | 44.93		         | 164.48
 HS200 | 4	            | 63.79	             | 155.82
 HS200 | 6	            | 63.22	             | 160.95
 HS200 | 32	            | 60.65	             | 167.48
 HS200 | 40	            | 59.19	             | 169.11

### OSPI NAND Performance
**r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.14  ms
Fast Tuning Window          |          0.65  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.33          |       4.34
      5          |        No         |        2.33          |       4.34
      10         |        No         |        2.33          |       4.34
      1          |        Yes        |        2.33          |       30.92
      5          |        Yes        |        2.33          |       30.92
      10         |        Yes        |        2.33          |       30.92


 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        1.56          |       5.52
      5          |        No         |        1.56          |       5.52
      10         |        No         |        1.56          |       5.52
      1          |        Yes        |        1.56          |       5.75
      5          |        Yes        |        1.56          |       5.75
      10         |        Yes        |        1.56          |       5.75


 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.33          |       3.56
      5          |        No         |        2.33          |       3.56
      10         |        No         |        2.33          |       3.56
      1          |        Yes        |        2.33          |       30.04
      5          |        Yes        |        2.33          |       30.04
      10         |        Yes        |        2.33          |       30.04


 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.00          |       5.27
      5          |        No         |        1.99          |       5.27
      10         |        No         |        1.99          |       5.27
      1          |        Yes        |        1.99          |       44.93
      5          |        Yes        |        1.99          |       45.03
      10         |        Yes        |        1.99          |       45.05


 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.33          |       5.76
      5          |        No         |        2.33          |       5.77
      10         |        No         |        2.33          |       5.77
      1          |        Yes        |        2.32          |       49.40
      5          |        Yes        |        2.33          |       49.40
      10         |        Yes        |        2.33          |       49.40


**mcu-r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.31  ms
Fast Tuning Window          |          0.75  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        1.72          |       2.14
      5          |        No         |        1.72          |       2.14
      10         |        No         |        1.72          |       2.14
      1          |        Yes        |        1.71          |       18.44
      5          |        Yes        |        1.72          |       18.45
      10         |        Yes        |        1.72          |       18.45

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        1.50          |       5.20
      5          |        No         |        1.50          |       5.20
      10         |        No         |        1.50          |       5.20
      1          |        Yes        |        1.50          |       5.76
      5          |        Yes        |        1.50          |       5.76
      10         |        Yes        |        1.50          |       5.76

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        1.81          |       4.89
      5          |        No         |        1.80          |       4.89
      10         |        No         |        1.80          |       4.89
      1          |        Yes        |        1.81          |       45.50
      5          |        Yes        |        1.81          |       45.51
      10         |        Yes        |        1.80          |       45.51


 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.01          |       5.35
      5          |        No         |        2.00          |       5.36
      10         |        No         |        2.00          |       5.36
      1          |        Yes        |        2.00          |       48.79
      5          |        Yes        |        2.00          |       48.79
      10         |        Yes        |        2.00          |       48.79


 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2
# Datasheet {#DATASHEET_AM62DX_EVM}

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

### SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_multistage, ipc_rpmsg_echo, and HSM App Images
- Cores booted by stage1 SBL       : r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 259 KB
- Size of images loaded by stage2  : 267 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |      17.538
SBL Stage1: Board_init                  |       0.000
SBL Stage1: Drivers_open                |       0.001
SBL Stage1: SBL Drivers_open            |       0.192
SBL Stage1: Board_driversOpen           |       0.007
SBL Stage1: SBL Board_driversOpen       |       1.414
SBL Stage1: Sciclient Get Version       |      10.170
SBL Stage1: App_loadSelfcoreImage       |       4.998
SBL Stage1: App_waitForMcuPbist         |       0.003
----------------------------------------|--------------
SBL Stage2: Total time taken            |      34.327

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |       1.921
SBL Stage2: Board_init                  |       0.003
SBL Stage2: FreeRtosTask Create         |       0.299
SBL Stage2: SBL Drivers_open            |       0.748
SBL Stage2: SBL Board_driversOpen       |       0.200
SBL Stage2: App_loadHSMImage            |       3.230
SBL Stage2: App_loadMCUImage            |       4.513
SBL Stage2: App_loadA53Images           |       6.095
SBL Stage2: App_loadDSPImage            |      15.422
----------------------------------------|--------------
SBL Stage2: SBL Total Time Taken        |      32.435

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~17 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_multistage, ipc_rpmsg_echo and HSM App Images
- Cores booted by stage1 SBL       : r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 259 KB
- Size of images loaded by stage2  : 267 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |      17.521
SBL Stage1: Board_init                  |       0.000
SBL Stage1: Drivers_open                |       0.000
SBL Stage1: SBL Drivers_open            |      20.630
SBL Stage1: Board_driversOpen           |       0.000
SBL Stage1: Sciclient Get Version       |      10.181
SBL Stage1: App_loadSelfcoreImage       |       9.809
----------------------------------------|--------------
SBL Stage1: SBL Total Time Taken        |      58.143

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |       1.916
SBL Stage2: Board_init                  |        .  3
SBL Stage2: FreeRtosTask Create         |        .255
SBL Stage2: SBL Drivers_open            |      16.666
SBL Stage2: App_loadHSMImage            |       6.313
SBL Stage2: App_loadMCUImage            |       6.037
SBL Stage2: App_loadA53Images           |       6.579
SBL Stage2: App_loadDSPImage            |      13.922
----------------------------------------|--------------
SBL Stage2: SBL Total Time Taken        |      51.694

- The emmc driver initialization is done as part of Drivers_open.

- Out of the ~17 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured.
- All cores are running from DDR with the exception of MCU-R5 from MSRAM

Local Core  | Remote Core | Average Message Latency (ns)
------------|-------------|------------------------------
 mcu-r5f0-0	| c75ss0	  | 1956ns
 mcu-r5f0-0	| a530-0	  | 1221ns
 mcu-r5f0-0	| r5f0-0	  | 1840ns
 a530-0	    | c75ss0	  | 1956ns
 c75ss0	    | r5f0-0	  | 1956ns
 a530-0	    | r5f0-0	  | 1060ns

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) |
------------|-------------|--------------|------------------------------|------------------|
      r5f0-0|       a530-0|             4|                         7.219|                10|
      r5f0-0|   mcu-r5f0-0|             4|                         9.130|                12|
      r5f0-0|       c75ss0|             4|                        76.210|                89|
      r5f0-0|       a530-0|            32|                         9.809|                12|
      r5f0-0|       a530-0|            64|                        12.874|                16|
      r5f0-0|       a530-0|           112|                        17.838|                21|
      r5f0-0|   mcu-r5f0-0|            32|                        15.146|                18|
      r5f0-0|   mcu-r5f0-0|            64|                        21.922|                26|
      r5f0-0|   mcu-r5f0-0|           112|                        32.056|                37|
      r5f0-0|       c75ss0|            32|                        85.545|                99|
      r5f0-0|       c75ss0|            64|                        95.048|               121|
      r5f0-0|       c75ss0|           112|                       106.842|               136|

### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 26.72		         | 45.17
 SDR50 | 4	            | 38.03		         | 45.56
 SDR50 | 6	            | 41.64		         | 45.58
 SDR50 | 32	            | 39.27		         | 45.62
 SDR50 | 40	            | 39.95		         | 44.25
 DDR50 | 1	            | 54.18		         | 82.00
 DDR50 | 4	            | 70.68		         | 83.66
 DDR50 | 6	            | 59.78		         | 79.37
 DDR50 | 32	            | 68.17		         | 83.02
 DDR50 | 40	            | 63.71		         | 83.17
 HS200 | 1	            | 71.61		         | 160.23
 HS200 | 4	            | 109.75		     | 169.47
 HS200 | 6	            | 109.49		     | 152.14
 HS200 | 32	            | 95.56		         | 166.77
 HS200 | 40	            | 99.37		         | 167.39

### OSPI Performance

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.44          |       2.74
      5          |        No         |        0.43          |       2.74
      10         |        No         |        0.43          |       2.74
      1          |        Yes        |        0.44          |       48.74
      5          |        Yes        |        0.43          |       48.76
      10         |        Yes        |        0.43          |       48.76


 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.41          |       5.87
      5          |        No         |        0.41          |       5.87
      10         |        No         |        0.41          |       5.87
      1          |        Yes        |        0.41          |       6.23
      5          |        Yes        |        0.41          |       6.23
      10         |        Yes        |        0.41          |       6.23


 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.43          |       6.14
      5          |        No         |        0.43          |       6.13
      10         |        No         |        0.43          |       6.13
      1          |        Yes        |        0.43          |       233.99
      5          |        Yes        |        0.43          |       234.69
      10         |        Yes        |        0.43          |       234.78


 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.43          |       6.83
      5          |        No         |        0.43          |       6.83
      10         |        No         |        0.43          |       6.83
      1          |        Yes        |        0.43          |       283.82
      5          |        Yes        |        0.43          |       284.83
      10         |        Yes        |        0.43          |       284.95

### McASP (audio) Latency
 - McASP operating at 48KHz, I2C mode
 - RX to TX pin to pin latency is measured
 - Rx To Tx pin to pin latency ~468us

### Boot latency
 - Measured from MCU_PORz to the first response of MCU-R5 and C7x cores
 - OSPI boot mode with SBL running OSPI in 8D-8D-8D mode (Phy enabled, DMA enabled)
 - HSM image size ~7KB
 - MCU R5 image size ~1MB
 - Boot time as observed in HS-FS device

#### MCU R5 boot time
 - GPIO toggle time from MCUR5 main (Measured from MCU_PORz)
  - 112 ms

#### C7x audio chime time
 - C7x audio out time (Measured from MCU_PORz)
 - Includes DAC configuration time
  - 185 ms


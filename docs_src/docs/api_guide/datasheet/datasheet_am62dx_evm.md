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
- Size of images loaded by stage1  : 261 KB
- Size of images loaded by stage2  : 267 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |      17.605
SBL Stage1: Board_init                  |       0.000
SBL Stage1: Drivers_open                |       0.001
SBL Stage1: SBL Drivers_open            |       0.193
SBL Stage1: Board_driversOpen           |       0.000
SBL Stage1: SBL Board_driversOpen       |       7.344
SBL Stage1: Sciclient Get Version       |       6.612
SBL Stage1: App_loadSelfcoreImage       |       5.620
SBL Stage1: App_waitForMcuPbist         |       0.002
----------------------------------------|--------------
SBL Stage1: Total time taken            |      37.382

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |       1.911
SBL Stage2: Board_init                  |       0.002
SBL Stage2: FreeRtosTask Create         |       0.256
SBL Stage2: SBL Drivers_open            |       0.738
SBL Stage2: SBL Board_driversOpen       |       0.488
SBL Stage2: App_loadHSMImage            |       3.709
SBL Stage2: App_loadMCUImage            |       4.606
SBL Stage2: App_loadA53Images           |       5.734
SBL Stage2: App_loadDSPImage            |      14.153
----------------------------------------|--------------
SBL Stage2: SBL Total Time Taken        |      31.602

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~17 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_multistage, ipc_rpmsg_echo and HSM App Images
- Cores booted by stage1 SBL       : r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 261 KB
- Size of images loaded by stage2  : 267 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |      24.189
SBL Stage1: Board_init                  |       0.000
SBL Stage1: Drivers_open                |       0.000
SBL Stage1: SBL Drivers_open            |      21.568
SBL Stage1: Board_driversOpen           |       0.000
SBL Stage1: Sciclient Get Version       |       6.608
SBL Stage1: PBIST Positive Tests        |       0.054
SBL Stage1: PBIST Negative Tests        |       0.127
SBL Stage1: App_loadSelfcoreImage       |      10.778
----------------------------------------|--------------
SBL Stage1: SBL Total Time Taken        |      63.328

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |       1.961
SBL Stage2: Board_init                  |       0.002
SBL Stage2: FreeRtosTask Create         |       0.258
SBL Stage2: SBL Drivers_open            |      17.534
SBL Stage2: App_loadHSMImage            |       5.758
SBL Stage2: App_loadMCUImage            |       6.217
SBL Stage2: App_loadA53Images           |       6.748
SBL Stage2: App_loadDSPImage            |       8.248
----------------------------------------|--------------
SBL Stage2: SBL Total Time Taken        |      46.730

- The emmc driver initialization is done as part of Drivers_open.

- Out of the ~17 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured.
- All cores are running from DDR with the exception of MCU-R5 from MSRAM

Local Core  | Remote Core | Average Message Latency (ns)
------------|-------------|------------------------------
 mcu-r5f0-0	| c75ss0	  | 1897ns
 mcu-r5f0-0	| a530-0	  | 1226ns
 mcu-r5f0-0	| r5f0-0	  | 1762ns
 a530-0	    | c75ss0	  | 1954ns
 c75ss0	    | r5f0-0	  | 1956ns
 a530-0	    | r5f0-0	  | 1060ns

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) |
------------|-------------|--------------|------------------------------|------------------|
      r5f0-0|       a530-0|             4|                         7.391|                10|
      r5f0-0|   mcu-r5f0-0|             4|                         9.275|                12|
      r5f0-0|       c75ss0|             4|                        79.866|               104|
      r5f0-0|       a530-0|            32|                         9.945|                13|
      r5f0-0|       a530-0|            64|                        13.082|                17|
      r5f0-0|       a530-0|           112|                        17.995|                24|
      r5f0-0|   mcu-r5f0-0|            32|                        15.483|                20|
      r5f0-0|   mcu-r5f0-0|            64|                        22.185|                28|
      r5f0-0|   mcu-r5f0-0|           112|                        32.554|                42|
      r5f0-0|       c75ss0|            32|                        89.549|               103|
      r5f0-0|       c75ss0|            64|                        95.198|               126|
      r5f0-0|       c75ss0|           112|                       112.850|               142|

### EMMC Performance

**a53 :**

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 35.78      	     | 45.98
 SDR50 | 4	            | 42.22      	     | 46.51
 SDR50 | 6	            | 37.59      	     | 46.54
 SDR50 | 32	            | 40.51      	     | 46.58
 SDR50 | 40	            | 39.66      	     | 46.58
 DDR50 | 1	            | 54.45		         | 85.58
 DDR50 | 4	            | 73.23		         | 86.94
 DDR50 | 6	            | 73.62		         | 87.04
 DDR50 | 32	            | 66.04		         | 87.13
 DDR50 | 40	            | 68.30		         | 87.17
 HS200 | 1	            | 73.67		         | 170.81
 HS200 | 4	            | 67.75		         | 183.53
 HS200 | 6	            | 116.05		     | 184.00
 HS200 | 32	            | 97.99		         | 184.42
 HS200 | 40	            | 103.15		     | 184.57

**r5 :**

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1.00	        | 26.32		         |  45.14
 SDR50 | 4.00	        | 41.57		         |  45.54
 SDR50 | 6.00	        | 41.62		         |  45.57
 SDR50 | 32.00	        | 39.04		         |  43.59
 SDR50 | 40.00	        | 39.74		         |  45.13
 DDR50 | 1.00	        | 32.96		         |  81.75
 DDR50 | 4.00	        | 71.02		         |  83.62
 DDR50 | 6.00	        | 56.49		         |  83.73
 DDR50 | 32.00	        | 66.31		         |  78.06
 DDR50 | 40.00	        | 64.62		         |  83.85
 HS200 | 1.00	        | 73.38		         |  159.80
 HS200 | 4.00	        | 109.16	    	 |  169.34
 HS200 | 6.00	        | 108.74	    	 |  152.02
 HS200 | 32.00	        | 97.27		         |  166.56
 HS200 | 40.00	        | 99.43		         |  167.40

### OSPI Performance {#OSPI_DATA_SHEET}

**a53 :**

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          10.10 ms
Fast Tuning Window          |          6.71 ms

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       2.74
      5          |        DAC        |        No         |        0.43          |       2.74
      10         |        DAC        |        No         |        0.43          |       2.74
      1          |        DAC        |        Yes        |        0.42          |       48.72
      5          |        DAC        |        Yes        |        0.43          |       48.76
      10         |        DAC        |        Yes        |        0.43          |       48.76

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.40           |       5.87
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
      1          |        DAC        |        No         |        0.42           |       6.14
      5          |        DAC        |        No         |        0.43           |       6.14
      10         |        DAC        |        No         |        0.43           |       6.14
      1          |        DAC        |        Yes        |        0.42           |       233.76
      5          |        DAC        |        Yes        |        0.43           |       234.64
      10         |        DAC        |        Yes        |        0.43           |       234.75

- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       6.83
      5          |        DAC        |        No         |        0.43          |       6.83
      10         |        DAC        |        No         |        0.43          |       6.83
      1          |        DAC        |        Yes        |        0.42          |       283.48
      5          |        DAC        |        Yes        |        0.43          |       284.76
      10         |        DAC        |        Yes        |        0.43          |       284.92


- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.42          |       12.82
      5          |       INDAC       |        No         |        0.43          |       12.82
      10         |       INDAC       |        No         |        0.43          |       12.81

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.40          |       6.25
      5          |       INDAC       |        No         |        0.40          |       6.25
      10         |       INDAC       |        No         |        0.40          |       6.25

**r5f0-0:**


DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          10.10 ms
Fast Tuning Window          |          6.71 ms

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       2.74
      5          |        DAC        |        No         |        0.43          |       2.74
      10         |        DAC        |        No         |        0.43          |       2.74
      1          |        DAC        |        Yes        |        0.42          |       48.72
      5          |        DAC        |        Yes        |        0.43          |       48.76
      10         |        DAC        |        Yes        |        0.43          |       48.76


- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.40           |       5.87
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
      1          |        DAC        |        No         |        0.42           |       6.14
      5          |        DAC        |        No         |        0.43           |       6.14
      10         |        DAC        |        No         |        0.43           |       6.14
      1          |        DAC        |        Yes        |        0.42           |       233.76
      5          |        DAC        |        Yes        |        0.43           |       234.64
      10         |        DAC        |        Yes        |        0.43           |       234.75


- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       6.83
      5          |        DAC        |        No         |        0.43          |       6.83
      10         |        DAC        |        No         |        0.43          |       6.83
      1          |        DAC        |        Yes        |        0.42          |       283.48
      5          |        DAC        |        Yes        |        0.43          |       284.76
      10         |        DAC        |        Yes        |        0.43          |       284.92

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.42          |       12.82
      5          |       INDAC       |        No         |        0.43          |       12.82
      10         |       INDAC       |        No         |        0.43          |       12.81

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.40          |       6.25
      5          |       INDAC       |        No         |        0.40          |       6.25
      10         |       INDAC       |        No         |        0.40          |       6.25

**mcu-r5f0-0:**

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          11.82 ms
Fast Tuning Window          |          7.97 ms

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       2.72
      5          |        DAC        |        No         |        0.42          |       2.72
      10         |        DAC        |        No         |        0.42          |       2.72
      1          |        DAC        |        Yes        |        0.42          |       48.73
      5          |        DAC        |        Yes        |        0.42          |       48.76
      10         |        DAC        |        Yes        |        0.42          |       48.76


- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.40           |       5.88
      5          |        DAC        |        No         |        0.40           |       5.88
      10         |        DAC        |        No         |        0.40           |       5.88
      1          |        DAC        |        Yes        |        0.40           |       6.23
      5          |        DAC        |        Yes        |        0.40           |       6.23
      10         |        DAC        |        Yes        |        0.40           |       6.23


- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       5.64
      5          |        DAC        |        No         |        0.42           |       5.64
      10         |        DAC        |        No         |        0.43           |       5.64
      1          |        DAC        |        Yes        |        0.42           |       233.80
      5          |        DAC        |        Yes        |        0.42           |       234.65
      10         |        DAC        |        Yes        |        0.42           |       234.76


- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       6.16
      5          |        DAC        |        No         |        0.42          |       6.16
      10         |        DAC        |        No         |        0.42          |       6.16
      1          |        DAC        |        Yes        |        0.42          |       283.54
      5          |        DAC        |        Yes        |        0.42          |       284.76
      10         |        DAC        |        Yes        |        0.43          |       284.92

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.42          |       10.95
      5          |       INDAC       |        No         |        0.42          |       10.95
      10         |       INDAC       |        No         |        0.42          |       10.95

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.40          |       6.25
      5          |       INDAC       |        No         |        0.40          |       6.25
      10         |       INDAC       |        No         |        0.40          |       6.25


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
  - 128 ms

#### C7x audio chime time
 - C7x audio out time (Measured from MCU_PORz)
 - Includes DAC configuration time
 - 151 ms


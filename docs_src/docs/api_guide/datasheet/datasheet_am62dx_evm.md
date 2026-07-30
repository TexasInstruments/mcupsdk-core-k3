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
- Size of images loaded by stage1  : 270 KB
- Size of images loaded by stage2  : 272 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |      17.620
SBL Stage1: Board_init                  |       0.090
SBL Stage1: Drivers_open                |       0.002
SBL Stage1: SBL Drivers_open            |       0.201
SBL Stage1: Board_driversOpen           |       0.000
SBL Stage1: SBL Board_driversOpen       |       7.317
SBL Stage1: Sciclient Get Version       |       6.702
SBL Stage1: App_loadSelfcoreImage       |       5.698
SBL Stage1: App_waitForMcuPbist         |       0.003
----------------------------------------|--------------
SBL Stage1: Total time taken            |      37.637

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |       1.918
SBL Stage2: Board_init                  |       0.003
SBL Stage2: FreeRtosTask Create         |       0.256
SBL Stage2: SBL Drivers_open            |       0.752
SBL Stage2: SBL Board_driversOpen       |       0.490
SBL Stage2: App_loadHSMImage            |       3.718
SBL Stage2: App_loadMCUImage            |       4.616
SBL Stage2: App_loadA53Images           |       5.785
SBL Stage2: App_loadDSPImage            |      14.316
----------------------------------------|--------------
SBL Stage2: SBL Total Time Taken        |      31.858

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~17 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_multistage, ipc_rpmsg_echo and HSM App Images
- Cores booted by stage1 SBL       : r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 260 KB
- Size of images loaded by stage2  : 477 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |      24.274
SBL Stage1: Board_init                  |       0.094
SBL Stage1: Drivers_open                |       0.000
SBL Stage1: SBL Drivers_open            |      21.637
SBL Stage1: Board_driversOpen           |       0.000
SBL Stage1: Sciclient Get Version       |       6.797
SBL Stage1: PBIST Positive Tests        |       0.166
SBL Stage1: PBIST Negative Tests        |       0.445
SBL Stage1: App_loadSelfcoreImage       |       7.477
----------------------------------------|--------------
SBL Stage1: SBL Total Time Taken        |      60.894

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |       1.812
SBL Stage2: Board_init                  |       0.003
SBL Stage2: FreeRtosTask Create         |       0.263
SBL Stage2: SBL Drivers_open            |      33.970
SBL Stage2: App_loadHSMImage            |       4.132
SBL Stage2: App_loadMCUImage            |       4.698
SBL Stage2: App_loadA53Images           |       6.236
SBL Stage2: App_loadDSPImage            |       5.950
----------------------------------------|--------------
SBL Stage2: SBL Total Time Taken        |      57.066

- The emmc driver initialization is done as part of Drivers_open.

- Out of the ~17 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured.
- All cores are running from DDR with the exception of MCU-R5 from MSRAM

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0	    | mcu-r5f0-0  |  1.25
 r5f0-0	    | a530-0	  |  1.08
 r5f0-0	    | c75ss0	  | 14.54
 mcu-r5f0-0	| r5f0-0	  |  1.25
 mcu-r5f0-0	| a530-0	  |  1.25
 mcu-r5f0-0	| c75ss0	  | 14.54
 a530-0	    | mcu-r5f0-0  |  1.23
 a530-0	    | r5f0-0	  |  1.07
 a530-0	    | c75ss0	  | 14.48
 c75ss0	    | mcu-r5f0-0  | 17.28
 c75ss0	    | r5f0-0	  | 17.29
 c75ss0	    | a530-0	  | 17.28

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
      r5f0-0|       a530-0|             4|                         7.709|                10|         1000
      r5f0-0|       a530-0|            32|                        11.166|                12|            3
      r5f0-0|       a530-0|            64|                        14.333|                15|            3
      r5f0-0|       a530-0|           112|                        18.500|                18|            3
      r5f0-0|   mcu-r5f0-0|            32|                        15.666|                17|            3
      r5f0-0|   mcu-r5f0-0|            64|                        22.500|                23|            3
      r5f0-0|   mcu-r5f0-0|           112|                        32.333|                34|            3
  mcu-r5f0-0|       a530-0|             4|                         8.400|                11|         1000
  mcu-r5f0-0|       a530-0|            32|                        11.500|                12|            3
  mcu-r5f0-0|       a530-0|            64|                        15.500|                15|            3
  mcu-r5f0-0|       a530-0|           112|                        23.000|                26|            3
  mcu-r5f0-0|       r5f0-0|            32|                        16.500|                17|            3
  mcu-r5f0-0|       r5f0-0|            64|                        22.333|                23|            3
  mcu-r5f0-0|       r5f0-0|           112|                        32.166|                33|            3
  mcu-r5f0-0|       c75ss0|            32|                        87.666|               100|            3
  mcu-r5f0-0|       c75ss0|            64|                       103.333|               121|            3
  mcu-r5f0-0|       c75ss0|           112|                       109.166|               127|            3
  mcu-r5f0-0|       a530-0|            32|                        13.500|                13|            3
  mcu-r5f0-0|       a530-0|            64|                        19.333|                19|            3
  mcu-r5f0-0|       a530-0|           112|                        23.333|                27|            3
      c75ss0|       a530-0|             4|                        79.276|                92|         1000
      c75ss0|       a530-0|            32|                        79.166|                80|            3
      c75ss0|       a530-0|            64|                        84.000|                95|            3
      c75ss0|       a530-0|           112|                        79.166|                81|            3
      c75ss0|       r5f0-0|            32|                        98.166|               104|            3
      c75ss0|       r5f0-0|            64|                       109.000|               118|            3
      c75ss0|       r5f0-0|           112|                       111.000|               116|            3
      c75ss0|   mcu-r5f0-0|            32|                        87.833|                89|            3
      c75ss0|   mcu-r5f0-0|            64|                       109.000|               118|            3
      c75ss0|   mcu-r5f0-0|           112|                       114.833|               123|            3
      c75ss0|       a530-0|            32|                        79.333|                80|            3
      c75ss0|       a530-0|            64|                        83.833|                93|            3
      c75ss0|       a530-0|           112|                        77.833|                79|            3
      a530-0|       r5f0-0|            32|                        10.833|                11|            3
      a530-0|       r5f0-0|            64|                        13.166|                13|            3
      a530-0|       r5f0-0|           112|                        17.833|                19|            3
      a530-0|   mcu-r5f0-0|            32|                        12.000|                12|            3
      a530-0|   mcu-r5f0-0|            64|                        15.666|                16|            3
      a530-0|   mcu-r5f0-0|           112|                        21.500|                22|            3
      a530-0|       c75ss0|            32|                        76.000|                78|            3
      a530-0|       c75ss0|            64|                        75.666|                78|            3
      a530-0|       c75ss0|           112|                        76.333|                78|            3 


### EMMC Performance

**a53 :**

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1.00	        | 34.07		         | 43.97
 SDR50 | 4.00	        | 40.39		         | 44.35
 SDR50 | 6.00	        | 40.45		         | 44.38
 SDR50 | 32.00	        | 37.77		         | 44.42
 SDR50 | 40.00	        | 38.52		         | 44.42
 DDR50 | 1.00	        | 52.50		         | 81.12
 DDR50 | 4.00	        | 56.10		         | 82.90
 DDR50 | 6.00	        | 60.92		         | 83.00
 DDR50 | 32.00	        | 62.80		         | 83.10
 DDR50 | 40.00	        | 63.67		         | 83.13
 HS200 | 1.00	        | 70.20		         | 164.55
 HS200 | 4.00	        | 108.71		     | 174.96
 HS200 | 6.00	        | 109.31		     | 175.44
 HS200 | 32.00	        | 92.96		         | 175.85
 HS200 | 40.00	        | 96.90		         | 176.01

**r5 :**

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1.00	        | 33.63		         | 42.89
 SDR50 | 4.00	        | 39.62		         | 43.43
 SDR50 | 6.00	        | 35.33		         | 42.18
 SDR50 | 32.00	        | 37.80		         | 43.25
 SDR50 | 40.00	        | 37.34		         | 43.30
 DDR50 | 1.00	        | 51.35		         | 78.38
 DDR50 | 4.00	        | 67.65		         | 79.73
 DDR50 | 6.00	        | 67.90		         | 75.64
 DDR50 | 32.00	        | 60.91		         | 79.12
 DDR50 | 40.00	        | 62.58		         | 79.31
 HS200 | 1.00	        | 69.52		         | 150.56
 HS200 | 4.00	        | 61.53		         | 161.42
 HS200 | 6.00	        | 104.18             | 144.91
 HS200 | 32.00	        | 86.95		         | 158.84
 HS200 | 40.00	        | 92.81		         | 159.61

### OSPI Performance {#OSPI_DATA_SHEET}

**a53 :**
 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 57.25

Non-DQS Tuning Algorithm    |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          1.50  ms
Fast Tuning Window          |          0.54  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          9.66 ms
Fast Tuning Window          |          6.54 ms

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       0.73
      5          |        DAC        |        No         |        0.45           |       0.73
      10         |        DAC        |        No         |        0.45           |       0.73
      1          |        DAC        |        Yes        |        0.44           |       49.83
      5          |        DAC        |        Yes        |        0.45           |       49.86
      10         |        DAC        |        Yes        |        0.45           |       49.86

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       0.54
      5          |        DAC        |        No         |        0.42           |       0.54
      10         |        DAC        |        No         |        0.42           |       0.54
      1          |        DAC        |        Yes        |        0.41           |       6.25
      5          |        DAC        |        Yes        |        0.42           |       6.25
      10         |        DAC        |        Yes        |        0.42           |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       1.06
      5          |        DAC        |        No         |        0.44           |       1.06
      10         |        DAC        |        No         |        0.45           |       1.06
      1          |        DAC        |        Yes        |        0.44           |       49.83
      5          |        DAC        |        Yes        |        0.44           |       49.86
      10         |        DAC        |        Yes        |        0.45           |       49.86

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       1.58
      5          |        DAC        |        No         |        0.44           |       1.58
      10         |        DAC        |        No         |        0.44           |       1.58
      1          |        DAC        |        Yes        |        0.43           |       132.09
      5          |        DAC        |        Yes        |        0.44           |       132.30
      10         |        DAC        |        Yes        |        0.44           |       132.33

- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       1.67
      5          |        DAC        |        No         |        0.44           |       1.67
      10         |        DAC        |        No         |        0.44           |       1.67
      1          |        DAC        |        Yes        |        0.43           |       261.75
      5          |        DAC        |        Yes        |        0.44           |       262.55
      10         |        DAC        |        Yes        |        0.44           |       262.65

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       1.77
      5          |        DAC        |        No         |        0.44           |       1.77
      10         |        DAC        |        No         |        0.44           |       1.77
      1          |        DAC        |        Yes        |        0.43           |       164.74
      5          |        DAC        |        Yes        |        0.44           |       165.06
      10         |        DAC        |        Yes        |        0.44           |       165.09

- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       1.89
      5          |        DAC        |        No         |        0.44           |       1.89
      10         |        DAC        |        No         |        0.44           |       1.89
      1          |        DAC        |        Yes        |        0.44           |       325.66
      5          |        DAC        |        Yes        |        0.44           |       326.93
      10         |        DAC        |        Yes        |        0.44           |       327.07


- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.43           |       15.60
      5          |       INDAC       |        No         |        0.44           |       15.60
      10         |       INDAC       |        No         |        0.44           |       15.60

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.41           |       6.25
      5          |       INDAC       |        No         |        0.42           |       6.25
      10         |       INDAC       |        No         |        0.42           |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.44           |       15.60
      5          |       INDAC       |        No         |        0.44           |       15.60
      10         |       INDAC       |        No         |        0.44           |       15.60


**r5f0-0:**

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 56.33

Non-DQS Tuning Algorithm    |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          1.62  ms
Fast Tuning Window          |          0.58  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          10.41 ms
Fast Tuning Window          |          7.01 ms

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       2.74
      5          |        DAC        |        No         |        0.43           |       2.74
      10         |        DAC        |        No         |        0.43           |       2.74
      1          |        DAC        |        Yes        |        0.43           |       48.72
      5          |        DAC        |        Yes        |        0.43           |       48.76
      10         |        DAC        |        Yes        |        0.43           |       48.76


- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.40           |       5.87
      5          |        DAC        |        No         |        0.41           |       5.87
      10         |        DAC        |        No         |        0.41           |       5.87
      1          |        DAC        |        Yes        |        0.40           |       6.23
      5          |        DAC        |        Yes        |        0.41           |       6.23
      10         |        DAC        |        Yes        |        0.41           |       6.23

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       3.98
      5          |        DAC        |        No         |        0.43           |       3.98
      10         |        DAC        |        No         |        0.43           |       3.98
      1          |        DAC        |        Yes        |        0.43           |       48.73
      5          |        DAC        |        Yes        |        0.43           |       48.76
      10         |        DAC        |        Yes        |        0.43           |       48.76

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled


 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       5.79
      5          |        DAC        |        No         |        0.42           |       5.79
      10         |        DAC        |        No         |        0.42           |       5.79
      1          |        DAC        |        Yes        |        0.42           |       124.58
      5          |        DAC        |        Yes        |        0.42           |       124.82
      10         |        DAC        |        Yes        |        0.42           |       124.85


- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       6.14
      5          |        DAC        |        No         |        0.43           |       6.13
      10         |        DAC        |        No         |        0.43           |       6.13
      1          |        DAC        |        Yes        |        0.42           |       233.78
      5          |        DAC        |        Yes        |        0.43           |       234.65
      10         |        DAC        |        Yes        |        0.43           |       234.75


 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       6.48
      5          |        DAC        |        No         |        0.42           |       6.48
      10         |        DAC        |        No         |        0.43           |       6.48
      1          |        DAC        |        Yes        |        0.42           |       153.20
      5          |        DAC        |        Yes        |        0.42           |       153.57
      10         |        DAC        |        Yes        |        0.43           |       153.62


- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       6.83
      5          |        DAC        |        No         |        0.43           |       6.83
      10         |        DAC        |        No         |        0.43           |       6.83
      1          |        DAC        |        Yes        |        0.43           |       283.48
      5          |        DAC        |        Yes        |        0.43           |       284.76
      10         |        DAC        |        Yes        |        0.43           |       284.92


- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.43           |       12.81
      5          |       INDAC       |        No         |        0.43           |       12.81
      10         |       INDAC       |        No         |        0.43           |       12.81


- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.41           |       6.25
      5          |       INDAC       |        No         |        0.41           |       6.25
      10         |       INDAC       |        No         |        0.41           |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.42           |       12.82
      5          |       INDAC       |        No         |        0.43           |       12.81
      10         |       INDAC       |        No         |        0.43           |       12.82

**mcu-r5f0-0:**

- PHY condition: enabled
- Flash type: SERIAL NOR
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Temperature: 57.70

Non-DQS Tuning Algorithm    |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          1.90  ms
Fast Tuning Window          |          0.67  ms

- Flash type: SERIAL NOR
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          11.82 ms
Fast Tuning Window          |          7.97 ms

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       2.72
      5          |        DAC        |        No         |        0.42           |       2.72
      10         |        DAC        |        No         |        0.42           |       2.72
      1          |        DAC        |        Yes        |        0.42           |       48.73
      5          |        DAC        |        Yes        |        0.42           |       48.76
      10         |        DAC        |        Yes        |        0.42           |       48.76


- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.40           |       5.88
      5          |        DAC        |        No         |        0.40           |       5.88
      10         |        DAC        |        No         |        0.40           |       5.87
      1          |        DAC        |        Yes        |        0.40           |       6.23
      5          |        DAC        |        Yes        |        0.40           |       6.23
      10         |        DAC        |        Yes        |        0.40           |       6.23


- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       3.79
      5          |        DAC        |        No         |        0.42           |       3.79
      10         |        DAC        |        No         |        0.42           |       3.79
      1          |        DAC        |        Yes        |        0.42           |       48.73
      5          |        DAC        |        Yes        |        0.42           |       48.76
      10         |        DAC        |        Yes        |        0.42           |       48.76


- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       5.37
      5          |        DAC        |        No         |        0.41           |       5.37
      10         |        DAC        |        No         |        0.42           |       5.37
      1          |        DAC        |        Yes        |        0.41           |       124.58
      5          |        DAC        |        Yes        |        0.41           |       124.82
      10         |        DAC        |        Yes        |        0.42           |       124.85


- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       5.65
      5          |        DAC        |        No         |        0.42           |       5.65
      10         |        DAC        |        No         |        0.42           |       5.65
      1          |        DAC        |        Yes        |        0.41           |       233.82
      5          |        DAC        |        Yes        |        0.42           |       234.65
      10         |        DAC        |        Yes        |        0.42           |       234.75


- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       5.93
      5          |        DAC        |        No         |        0.42           |       5.93
      10         |        DAC        |        No         |        0.42           |       5.93
      1          |        DAC        |        Yes        |        0.41           |       153.22
      5          |        DAC        |        Yes        |        0.42           |       153.57
      10         |        DAC        |        Yes        |        0.42           |       153.62


- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       6.16
      5          |        DAC        |        No         |        0.42           |       6.16
      10         |        DAC        |        No         |        0.42           |       6.16
      1          |        DAC        |        Yes        |        0.42           |       283.54
      5          |        DAC        |        Yes        |        0.42           |       284.76
      10         |        DAC        |        Yes        |        0.42           |       284.92


- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.42           |       10.94
      5          |       INDAC       |        No         |        0.42           |       10.95
      10         |       INDAC       |        No         |        0.42           |       10.95

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.40           |       6.25
      5          |       INDAC       |        No         |        0.40           |       6.25
      10         |       INDAC       |        No         |        0.40           |       6.25

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.42           |       10.94
      5          |       INDAC       |        No         |        0.42           |       10.95
      10         |       INDAC       |        No         |        0.42           |       10.95      

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

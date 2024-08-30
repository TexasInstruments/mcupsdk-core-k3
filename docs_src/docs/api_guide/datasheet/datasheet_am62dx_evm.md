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
- Size of images loaded by stage1  : 199 KB
- Size of images loaded by stage2  : 265 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.745
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.001
SBL Stage1: SBL Drivers_open            |    0.194
SBL Stage1: Board_driversOpen           |    0.008
SBL Stage1: SBL Board_driversOpen       |    1.312
SBL Stage1: Sciclient Get Version       |   10.170
SBL Stage1: App_loadSelfcoreImage       |    5.428
----------------------------------------|--------------
SBL Stage2: Total time taken            |   40.861

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.762
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.255
SBL Stage2: SBL Drivers_open            |    0.720
SBL Stage2: SBL Board Drivers_open      |    0.117
SBL Stage2: App_loadImages              |    3.042
SBL Stage2: App_loadMCUImages           |    5.401
SBL Stage2: App_loadA53Images           |    6.454
SBL Stage2: App_loadDSPImage            |   16.154
----------------------------------------|--------------
SBL Stage2: Total time taken            |   33.912

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~23 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_multistage, ipc_rpmsg_echo and HSM App Images
- Cores booted by stage1 SBL       : r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 199 KB
- Size of images loaded by stage2  : 265 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.434
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.573
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.168
SBL Stage1: App_loadImages              |    9.867
----------------------------------------|--------------
SBL Stage1: Total time taken            |   63.044

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.760
SBL Stage2: Board_init                  |    0.002
SBL Stage2: FreeRtosTask Create         |    0.256
SBL Stage2: Drivers_open                |   15.578
SBL Stage2: App_loadImages              |    6.153
SBL Stage2: App_loadMCUImage            |    6.934
SBL Stage2: App_loadA53Images           |    6.963
SBL Stage2: App_loadDSPImage            |   14.723
----------------------------------------|--------------
SBL Stage2: Total time taken            |   52.372

- The emmc driver initialization is done as part of Drivers_open.

- Out of the ~23 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured.
- All cores are running from DDR with the exception of MCU-R5 from MSRAM

Local Core  | Remote Core | Average Message Latency (ns)
------------|-------------|------------------------------
 mcu-r5f0-0	| c75ss0	  | 2094ns
 mcu-r5f0-0	| a530-0	  | 1169ns
 mcu-r5f0-0	| r5f0-0	  | 1689ns
 a530-0	    | c75ss0	  | 2082ns
 c75ss0	    | r5f0-0	  | 2065ns
 a530-0	    | r5f0-0	  | 1000ns

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) |
------------|-------------|--------------|------------------------------|------------------|
      r5f0-0|       a530-0|             4|                         6.842|                10|
      r5f0-0|   mcu-r5f0-0|             4|                         8.933|                12|
      r5f0-0|       c75ss0|             4|                        79.916|                94|
      r5f0-0|       a530-0|            32|                         9.659|                12|
      r5f0-0|       a530-0|            64|                        12.655|                15|
      r5f0-0|       a530-0|           112|                        17.544|                21|
      r5f0-0|   mcu-r5f0-0|            32|                        15.526|                18|
      r5f0-0|   mcu-r5f0-0|            64|                        22.628|                25|
      r5f0-0|   mcu-r5f0-0|           112|                        33.379|                36|
      r5f0-0|       c75ss0|            32|                        89.926|               104|
      r5f0-0|       c75ss0|            64|                        92.618|               127|
      r5f0-0|       c75ss0|           112|                       113.281|               128|


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 40.57		         | 45.01
 SDR50 | 4	            | 32.34		         | 45.54
 SDR50 | 6	            | 41.63		         | 45.57
 DDR50 | 1	            | 69.14		         | 82.03
 DDR50 | 4	            | 71.01		         | 83.67
 DDR50 | 6	            | 59.46		         | 83.76
 HS200 | 1	            | 53.48 		     | 157.51
 HS200 | 4	            | 109.84		     | 169.34
 HS200 | 6	            | 108.03	         | 169.78


### OSPI Performance
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 0.43		        | 283.77
 5	           | 0.43		        | 284.83
 10	           | 0.43		        | 284.96

### McASP (audio) Latency
 - Measured in am62a-sk
 - McASP operating at 48KHz, I2C mode
 - RX to TX pin to pin latency is measured
 - Rx To Tx pin to pin latency ~792us

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


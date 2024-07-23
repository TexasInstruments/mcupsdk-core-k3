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
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 180 KB
- Size of images loaded by stage2  : 381 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   34.932
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.195
SBL Stage1: Board_driversOpen           |    1.315
SBL Stage1: Sciclient Get Version       |   10.169
SBL Stage1: App_loadImages              |    3.191
SBL Stage1: App_loadSelfcoreImage       |    5.025
----------------------------------------|--------------
SBL Stage2: Total time taken            |   54.830

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.918
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.243
SBL Stage2: App_loadImages              |    2.864
SBL Stage2: App_loadSelfcoreImage       |    5.059
SBL Stage2: App_loadA53Images           |    4.075
SBL Stage2: App_loadDSPImage            |   11.352
----------------------------------------|--------------
SBL Stage2: Total time taken            |   25.516

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_multistage, ipc_rpmsg_echo and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 151 KB
- Size of images loaded by stage2  : 381 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   34.859
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.556
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.169
SBL Stage1: App_loadImages              |    6.735
SBL Stage1: App_loadSelfcoreImage       |    7.652
----------------------------------------|--------------
SBL Stage1: Total time taken            |   78.975

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.769
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   19.516
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.274
SBL Stage2: App_loadImages              |    6.015
SBL Stage2: App_loadSelfcoreImage       |    8.341
SBL Stage2: App_loadA53Images           |    6.960
SBL Stage2: App_loadDSPImage            |   14.899
----------------------------------------|--------------
SBL Stage2: Total time taken            |   67.780

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | mcu-r5f0-0  |  1.12
 r5f0-0     | a530-0      |  8.90
 r5f0-0     | c75ss0      |  29.86

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us)
------------|-------------|--------------|------------------------------|------------------
      r5f0-0|       a530-0|            32|                        10.940|                17
      r5f0-0|       a530-0|            64|                        14.735|                20
      r5f0-0|       a530-0|           112|                        20.705|                26
      r5f0-0|   mcu-r5f0-0|            32|                        18.197|                24
      r5f0-0|   mcu-r5f0-0|            64|                        27.343|                33
      r5f0-0|   mcu-r5f0-0|           112|                        40.974|                46
      r5f0-0|       c75ss0|            32|                       109.337|               128
      r5f0-0|       c75ss0|            64|                       110.234|               148
      r5f0-0|       c75ss0|           112|                       132.391|               152


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 41.36		         | 46.04
 SDR50 | 4	            | 42.36		         | 46.51
 SDR50 | 6	            | 42.44		         | 46.54
 DDR50 | 1	            | 69.36		         | 85.15
 DDR50 | 4	            | 56.89		         | 86.96
 DDR50 | 6	            | 66.57		         | 87.06
 HS200 | 1	            | 105.10		     | 169.81
 HS200 | 4	            | 112.91		     | 183.47
 HS200 | 6	            | 97.30		         | 183.96


### OSPI Performance
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 0.45		        | 326.04
 5	           | 0.45		        | 327.00
 10	           | 0.45		        | 327.11

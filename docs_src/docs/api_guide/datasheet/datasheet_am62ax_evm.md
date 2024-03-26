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
- Size of images loaded by stage1  : 185 KB
- Size of images loaded by stage2  : 1110 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.429
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.189
SBL Stage1: Board_driversOpen           |   11.368
SBL Stage1: Sciclient Get Version       |   10.170
SBL Stage1: App_waitForMcuPbist         |    0.004
SBL Stage1: App_loadImages              |    3.384
SBL Stage1: App_loadSelfcoreImage       |    6.482
----------------------------------------|--------------
SBL Stage2: Total time taken            |   70.030

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.794
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.222
SBL Stage2: Board_driversOpen           |   50.031
SBL Stage2: Sciclient Get Version       |   10.219
SBL Stage2: App_loadImages              |    2.070
SBL Stage2: App_loadSelfcoreImage       |    7.063
SBL Stage2: App_loadLinuxImages         |   29.450
SBL Stage2: App_loadDSPImage            |   13.163
----------------------------------------|--------------
SBL Stage2: Total time taken            |  114.015

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL OSPI NAND performance (HS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 185 KB
- Size of images loaded by stage2  : 1110 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   37.747
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.190
SBL Stage1: Board_driversOpen           |   11.042
SBL Stage1: Sciclient Get Version       |   10.169
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_loadImages              |    3.467
SBL Stage1: App_loadSelfcoreImage       |    6.548
----------------------------------------|--------------
SBL Stage2: Total time taken            |   69.171

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.784
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.218
SBL Stage2: Board_driversOpen           |   49.851
SBL Stage2: Sciclient Get Version       |   10.219
SBL Stage2: App_loadImages              |    2.119
SBL Stage2: App_loadSelfcoreImage       |    6.898
SBL Stage2: App_loadLinuxImages         |   27.990
SBL Stage2: App_loadDSPImage            |   13.096
----------------------------------------|--------------
SBL Stage2: Total time taken            |  112.179

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 161 KB
- Size of images loaded by stage2  : 1110 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.593
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.575
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.183
SBL Stage1: App_loadImages              |    6.909
SBL Stage1: App_loadSelfcoreImage       |    7.428
----------------------------------------|--------------
SBL Stage1: Total time taken            |   82.691

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.711
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.505
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.241
SBL Stage2: App_loadImages              |    5.988
SBL Stage2: App_loadSelfcoreImage       |    7.819
SBL Stage2: App_loadLinuxImages         |   20.100
SBL Stage2: App_loadDSPImage            |   14.289
----------------------------------------|--------------
SBL Stage2: Total time taken            |   79.658

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 161 KB
- Size of images loaded by stage2  : 1110 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   37.629
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.573
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.169
SBL Stage1: App_loadImages              |    6.965
SBL Stage1: App_loadSelfcoreImage       |    8.228
----------------------------------------|--------------
SBL Stage1: Total time taken            |   82.566

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.696
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.505
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.220
SBL Stage2: App_loadImages              |    5.360
SBL Stage2: App_loadSelfcoreImage       |    7.911
SBL Stage2: App_loadLinuxImages         |   20.097
SBL Stage2: App_loadDSPImage            |   14.992
----------------------------------------|--------------
SBL Stage2: Total time taken            |   79.787

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | mcu-r5f0-0  |  1.12
 r5f0-0     | a530-0      |  6.79
 r5f0-0     | c75ss0      |  18.01

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) 
------------|-------------|--------------|------------------------------|------------------
      r5f0-0|       a530-0|            32|                         9.619|                12
      r5f0-0|       a530-0|            64|                        12.584|                17
      r5f0-0|       a530-0|           112|                        17.308|                22
      r5f0-0|   mcu-r5f0-0|            32|                        14.215|                17
      r5f0-0|   mcu-r5f0-0|            64|                        20.734|                27
      r5f0-0|   mcu-r5f0-0|           112|                        30.550|                38
      r5f0-0|       c75ss0|            32|                        76.941|               103
      r5f0-0|       c75ss0|            64|                        86.202|               104
      r5f0-0|       c75ss0|           112|                        93.336|               112


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 35.20		   | 45.00
 SDR50 | 4	            | 41.55		   | 45.54
 SDR50 | 6	            | 41.63		   | 44.24
 DDR50 | 1	            | 54.16		   | 81.77
 DDR50 | 4	            | 54.87		   | 83.65
 DDR50 | 6	            | 61.99		   | 79.33
 HS200 | 1	            | 73.72		   | 157.99
 HS200 | 4	            | 109.78		   | 169.31
 HS200 | 6	            | 109.95		   | 152.03


### OSPI NAND Performance
Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
PHY : enabled
DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 2.35		    | 50.39
 5	       | 2.36		    | 50.38
 10	       | 2.36		    | 50.38

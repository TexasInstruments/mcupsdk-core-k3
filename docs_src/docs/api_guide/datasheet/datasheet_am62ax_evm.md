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
- Size of images loaded by stage1  : 183 KB
- Size of images loaded by stage2  : 1102 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   37.923
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.194
SBL Stage1: Board_driversOpen           |    5.231
SBL Stage1: Sciclient Get Version       |    9.913
SBL Stage1: APP_waitForMcuPbist         |    0.005
SBL Stage1: App_loadImages              |    3.406
SBL Stage1: App_loadSelfcoreImage       |    6.478
SBL Stage2: System_init                 |    1.778
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.217
SBL Stage2: Board_driversOpen           |    5.175
SBL Stage2: Sciclient Get Version       |   10.004
SBL Stage2: App_loadImages              |    2.043
SBL Stage2: App_loadSelfcoreImage       |    6.670
SBL Stage2: App_loadLinuxImages         |   26.632
SBL Stage2: App_loadDSPImages           |    6.454
----------------------------------------|--------------
SBL : Total time taken                  |  122.124

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL OSPI NAND performance (HS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 183 KB
- Size of images loaded by stage2  : 1102 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   37.576
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.195
SBL Stage1: Board_driversOpen           |    5.548
SBL Stage1: Sciclient Get Version       |    9.909
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_loadImages              |    3.491
SBL Stage1: App_loadSelfcoreImage       |    6.563
SBL Stage2: System_init                 |    1.779
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.219
SBL Stage2: Board_driversOpen           |    5.443
SBL Stage2: Sciclient Get Version       |    9.965
SBL Stage2: App_loadImages              |    2.128
SBL Stage2: App_loadSelfcoreImage       |    6.771
SBL Stage2: App_loadLinuxImages         |   28.007
SBL Stage2: App_loadDSPImage            |    6.560
----------------------------------------|--------------
SBL : Total time taken                  |  124.159

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 160 KB
- Size of images loaded by stage2  : 1102 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   37.251
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   26.179
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.908
SBL Stage1: App_loadImages              |   21.947
SBL Stage1: App_loadSelfcoreImage       |   23.300
SBL Stage2: System_init                 |    1.683
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.522
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.007
SBL Stage2: App_loadImages              |   21.168
SBL Stage2: App_loadSelfcoreImage       |   23.721
SBL Stage2: App_loadLinuxImages         |   35.924
SBL Stage2: App_loadDSPImages           |   23.644
----------------------------------------|--------------
SBL : Total time taken                  |  254.255

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 160 KB
- Size of images loaded by stage2  : 1102 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   37.102
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   48.870
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.897
SBL Stage1: App_loadImages              |   22.013
SBL Stage1: App_loadSelfcoreImage       |   23.369
SBL Stage2: System_init                 |    1.676
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.522
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    9.946
SBL Stage2: App_loadImages              |   21.223
SBL Stage2: App_loadSelfcoreImage       |   23.779
SBL Stage2: App_loadLinuxImages         |   35.985
SBL Stage2: App_loadDSPImages           |   23.691
----------------------------------------|--------------
SBL : Total time taken                  |  277.073

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | mcu-r5f0-0  |  4.269
 r5f0-0     | a530-0      |  3.559
 r5f0-0     | c75ss0      |  6.513

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us)
------------|-------------|--------------|------------------------------|------------------
      r5f0-0|       a530-0|            32|                         9.989|                13
      r5f0-0|       a530-0|            64|                        13.249|                17
      r5f0-0|       a530-0|           112|                        18.011|                22
      r5f0-0|   mcu-r5f0-0|            32|                        14.990|                19
      r5f0-0|   mcu-r5f0-0|            64|                        21.623|                27
      r5f0-0|   mcu-r5f0-0|           112|                        31.636|                40
      r5f0-0|       c75ss0|            32|                        82.528|               105
      r5f0-0|       c75ss0|            64|                        88.367|               106
      r5f0-0|       c75ss0|           112|                        95.303|               121


### EMMC Performance

Mode   | Read Speed (MiBps) | Size (MiB)
-------|--------------------|--------------
 HS200 | 167                | 4
 DDR50 | 83                 | 4
 SDR50 | 45                 | 4

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
- Size of images loaded by stage1  : 184 KB
- Size of images loaded by stage2  : 1045 KB
- Boot Media Clock                 : 166.667 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   39.073
SBL Stage1: Drivers_open                |    0.191
SBL Stage1: Board_driversOpen           |    5.541
SBL Stage1: Sciclient Get Version       |    9.894
SBL Stage1: App_waitForMcuPbist         |    0.004
SBL Stage1: App_waitForMcuLbist         |    7.792
SBL Stage1: App_loadImages              |    3.689
SBL Stage1: App_loadSelfcoreImage       |    7.092
SBL Stage2: System_init                 |    1.792
SBL Stage2: Drivers_open                |    0.224
SBL Stage2: Board_driversOpen           |    5.543
SBL Stage2: Sciclient Get Version       |    9.913
SBL Stage2: App_loadImages              |    2.093
SBL Stage2: App_loadSelfcoreImage       |    6.912
SBL Stage2: App_loadLinuxImages         |   31.427
SBL Stage2: App_loadDSPImage            |    7.284
----------------------------------------|--------------
SBL : Total time taken                  |  138.471

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL OSPI NAND performance (HS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 184 KB
- Size of images loaded by stage2  : 1045 KB
- Boot Media Clock                 : 166.667 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.753
SBL Stage1: Drivers_open                |    0.193
SBL Stage1: Board_driversOpen           |    5.547
SBL Stage1: Sciclient Get Version       |    9.907
SBL Stage1: App_waitForMcuPbist         |    0.004
SBL Stage1: App_waitForMcuLbist         |    7.792
SBL Stage1: App_loadImages              |    3.779
SBL Stage1: App_loadSelfcoreImage       |    7.186
SBL Stage2: System_init                 |    1.808
SBL Stage2: Drivers_open                |    0.224
SBL Stage2: Board_driversOpen           |    5.636
SBL Stage2: Sciclient Get Version       |    9.908
SBL Stage2: App_loadImages              |    2.179
SBL Stage2: App_loadSelfcoreImage       |    7.021
SBL Stage2: App_loadLinuxImages         |   31.579
SBL Stage2: App_loadDSPImage            |    7.389
----------------------------------------|--------------
SBL : Total time taken                  |  138.912

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 160 KB
- Size of images loaded by stage2  : 1045 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   39.504
SBL Stage1: Drivers_open                |   61.574
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.895
SBL Stage1: App_loadImages              |   22.280
SBL Stage1: App_loadSelfcoreImage       |   23.785
SBL Stage2: System_init                 |    1.703
SBL Stage2: Drivers_open                |   19.520
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    9.909
SBL Stage2: App_loadImages              |   21.214
SBL Stage2: App_loadSelfcoreImage       |   24.195
SBL Stage2: App_loadLinuxImages         |   39.742
SBL Stage2: App_loadDSPImages           |   24.483
----------------------------------------|--------------
SBL : Total time taken                  |  297.809

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 160 KB
- Size of images loaded by stage2  : 1045 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.283
SBL Stage1: Drivers_open                |   29.208
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.917
SBL Stage1: App_loadImages              |   22.333
SBL Stage1: App_loadSelfcoreImage       |   23.871
SBL Stage2: System_init                 |    1.703
SBL Stage2: Drivers_open                |   19.520
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    9.910
SBL Stage2: App_loadImages              |   21.302
SBL Stage2: App_loadSelfcoreImage       |   24.272
SBL Stage2: App_loadLinuxImages         |   39.855
SBL Stage2: App_loadDSPImages           |   24.589
----------------------------------------|--------------
SBL : Total time taken                  |  264.726

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

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us)
------------|-------------|--------------|------------------------------
 r5f0-0     | mcu-r5f0-0  | 32           |  1.425
 r5f0-0     | mcu-r5f0-0  | 64           |  2.088
 r5f0-0     | mcu-r5f0-0  | 112          |  3.069
 r5f0-0     | a530-0      | 32           |  0.952
 r5f0-0     | a530-0      | 64           |  1.256
 r5f0-0     | a530-0      | 112          |  1.730
 r5f0-0     | c75ss0      | 32           |  7.664
 r5f0-0     | c75ss0      | 64           |  8.368
 r5f0-0     | c75ss0      | 112          |  9.326

# Datasheet {#DATASHEET_AM62X_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Generic Setup details

SOC Details             | Values
------------------------|------------------------------
Core                    | R5F
Core Operating Speed    | 400 MHz
Cache Status            | Enabled

Optimization Details    | Values
------------------------|------------------------------
Build Profile           | Release
R5F Compiler flags      | -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -Wall -Werror -g -mthumb -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function
R5F Linker flags        | -Wl,--diag_suppress=10063 -Wl,--ram_model -Wl,--reread_libs
Code Placement          | HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)
Data Placement          | HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)

## Performance Numbers

### AM62X-SK SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 184 KB
- Size of images loaded by stage2  : 1049 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   5.565
SBL Stage1: Board_init                  |   0.000
SBL Stage1: Drivers_open                |   0.299
SBL Stage1: Board_driversOpen           |   27.556
SBL Stage1: Sciclient Get Version       |   9.929
SBL Stage1: App_waitForMcuPbist         |   0.005
SBL Stage1: App_waitForMcuLbist         |   7.689
SBL Stage1: App_loadImages              |   3.676
SBL Stage1: App_loadSelfcoreImage       |   4.187
SBL Stage2: System_init                 |   2.793
SBL Stage2: Board_init                  |   0.001
SBL Stage2: Drivers_open                |   0.371
SBL Stage2: Board_driversOpen           |   27.183
SBL Stage2: Sciclient Get Version       |   9.957
SBL Stage2: App_loadImages              |   2.782
SBL Stage2: App_loadSelfcoreImage       |   4.322
SBL Stage2: App_loadLinuxImages         |   13.227
----------------------------------------|--------------
SBL : Total time taken                  |   119.542

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK SBL OSPI performance (HS-SE)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 184 KB
- Size of images loaded by stage2  : 1049 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.311
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.301
SBL Stage1: Board_driversOpen           |   27.779
SBL Stage1: Sciclient Get Version       |    9.927
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.747
SBL Stage1: App_loadSelfcoreImage       |    4.273
SBL Stage2: System_init                 |    2.790
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.364
SBL Stage2: Board_driversOpen           |   27.108
SBL Stage2: Sciclient Get Version       |    9.965
SBL Stage2: App_loadImages              |    2.868
SBL Stage2: App_loadSelfcoreImage       |    4.418
SBL Stage2: App_loadLinuxImages         |   13.257
----------------------------------------|--------------
SBL : Total time taken                  |  119.802

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK LP SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 180 KB
- Size of images loaded by stage2  : 993 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.478
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.207
SBL Stage1: Board_driversOpen           |   14.899
SBL Stage1: Sciclient Get Version       |    9.929
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.988
SBL Stage1: App_loadSelfcoreImage       |    7.342
SBL Stage2: System_init                 |    2.821
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.268
SBL Stage2: Board_driversOpen           |   14.465
SBL Stage2: Sciclient Get Version       |    9.979
SBL Stage2: App_loadImages              |    2.177
SBL Stage2: App_loadSelfcoreImage       |    7.369
SBL Stage2: App_loadLinuxImages         |   36.944
----------------------------------------|--------------
SBL : Total time taken                  |  151.561

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL OSPI NAND performance (HS-SE)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 180 KB
- Size of images loaded by stage2  : 993 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.312
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.208
SBL Stage1: Board_driversOpen           |   14.848
SBL Stage1: Sciclient Get Version       |    9.929
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.077
SBL Stage1: App_loadSelfcoreImage       |    7.426
SBL Stage2: System_init                 |    2.835
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.264
SBL Stage2: Board_driversOpen           |   14.585
SBL Stage2: Sciclient Get Version       |    9.958
SBL Stage2: App_loadImages              |    2.263
SBL Stage2: App_loadSelfcoreImage       |    7.469
SBL Stage2: App_loadLinuxImages         |   37.029
----------------------------------------|--------------
SBL : Total time taken                  |  151.881

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 157 KB
- Size of images loaded by stage2  : 1049 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   5.256
SBL Stage1: Board_init                  |   0.000
SBL Stage1: Drivers_open                |   50.067
SBL Stage1: Board_driversOpen           |   0
SBL Stage1: Sciclient Get Version       |   9.926
SBL Stage1: App_loadImages              |   22.452
SBL Stage1: App_loadSelfcoreImage       |   23.740
SBL Stage2: System_init                 |   2.624
SBL Stage2: Board_init                  |   0.000
SBL Stage2: Drivers_open                |   19.543
SBL Stage2: Board_driversOpen           |   0.001
SBL Stage2: Sciclient Get Version       |   9.936
SBL Stage2: App_loadImages              |   21.306
SBL Stage2: App_loadSelfcoreImage       |   24.489
SBL Stage2: App_loadLinuxImages         |   42.774
----------------------------------------|--------------
SBL : Total time taken                  |   232.114

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 157 KB
- Size of images loaded by stage2  : 1049 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.434
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   53.786
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.927
SBL Stage1: App_loadImages              |   22.509
SBL Stage1: App_loadSelfcoreImage       |   23.815
SBL Stage2: System_init                 |    2.630
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.541
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |    9.986
SBL Stage2: App_loadImages              |   21.378
SBL Stage2: App_loadSelfcoreImage       |   24.530
SBL Stage2: App_loadLinuxImages         |   43.017
----------------------------------------|--------------
SBL : Total time taken                  |  235.554

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 157 KB
- Size of images loaded by stage2  : 993 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.209
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   54.907
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.927
SBL Stage1: App_loadImages              |   22.445
SBL Stage1: App_loadSelfcoreImage       |   23.853
SBL Stage2: System_init                 |    2.649
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.542
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |    9.970
SBL Stage2: App_loadImages              |   21.305
SBL Stage2: App_loadSelfcoreImage       |   24.367
SBL Stage2: App_loadLinuxImages         |   42.633
----------------------------------------|--------------
SBL : Total time taken                  |  264.808

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 157 KB
- Size of images loaded by stage2  : 993 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.288
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   26.479
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.927
SBL Stage1: App_loadImages              |   22.531
SBL Stage1: App_loadSelfcoreImage       |   23.955
SBL Stage2: System_init                 |    2.660
SBL Stage2: Drivers_open                |   19.542
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |    9.970
SBL Stage2: App_loadImages              |   21.409
SBL Stage2: App_loadSelfcoreImage       |   24.481
SBL Stage2: App_loadLinuxImages         |   42.690
----------------------------------------|--------------
SBL : Total time taken                  |  236.960

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.


### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | m4f0-0      |  1.605

#### IPC RPMSG

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) |Max Tx Latency (us) | Max Rx Latency (us)
------------|-------------|--------------|------------------------------|--------------------|---------------------
 r5f0-0     | m4f0-0      | 32           |  2.273                       |  5                 |  46
 r5f0-0     | m4f0-0      | 64           |  3.296                       |  6                 |  68
 r5f0-0     | m4f0-0      | 112          |  4.823                       |  7                 |  103

### EMMC Performance

Mode   | Read Speed (MiBps) | Size (MiB)
-------|--------------------|--------------
 HS200 | 155                | 4
 DDR50 | 80                 | 4
 SDR50 | 44                 | 4

### OSPI NOR Flash Performance

Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
PHY : enabled
DMA : enabled
DAC : disabled

Data size(MiB) |  Read speed(MiBps)
---------------|-----------------
1              | 283.58
5              | 284.71
10             | 284.88
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
- Size of images loaded by stage2  : 940 KB
- Boot Media Clock                 : 166.667 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   6.441
SBL Stage1: Drivers_open                |   0.208
SBL Stage1: Board_driversOpen           |   27.571
SBL Stage1: Sciclient Get Version       |   9.927
SBL Stage1: App_waitForMcuPbist         |   0.005
SBL Stage1: App_waitForMcuLbist         |   7.689
SBL Stage1: App_loadImages              |   3.535
SBL Stage1: App_loadSelfcoreImage       |   6.279
SBL Stage2: System_init                 |   2.825
SBL Stage2: Drivers_open                |   0.266
SBL Stage2: Board_driversOpen           |   27.055
SBL Stage2: Sciclient Get Version       |   9.967
SBL Stage2: App_loadImages              |   1.967
SBL Stage2: App_loadSelfcoreImage       |   6.557
SBL Stage2: App_loadLinuxImages         |   29.163
----------------------------------------|--------------
SBL : Total time taken                  |   139.425

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK SBL OSPI performance (HS-SE)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 184 KB
- Size of images loaded by stage2  : 940 KB
- Boot Media Clock                 : 166.667 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    6.606
SBL Stage1: Drivers_open                |    0.207
SBL Stage1: Board_driversOpen           |   27.693
SBL Stage1: Sciclient Get Version       |    9.927
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.619
SBL Stage1: App_loadSelfcoreImage       |    6.367
SBL Stage2: System_init                 |    2.818
SBL Stage2: Drivers_open                |    0.266
SBL Stage2: Board_driversOpen           |   27.103
SBL Stage2: Sciclient Get Version       |    9.957
SBL Stage2: App_loadImages              |    2.045
SBL Stage2: App_loadSelfcoreImage       |    6.642
SBL Stage2: App_loadLinuxImages         |   29.258
----------------------------------------|--------------
SBL : Total time taken                  |  140.206

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK LP SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 182 KB
- Size of images loaded by stage2  : 895 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   37.270
SBL Stage1: Drivers_open                |    0.207
SBL Stage1: Board_driversOpen           |    0.088
SBL Stage1: Sciclient Get Version       |    9.925
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    5.520
SBL Stage1: App_loadSelfcoreImage       |   10.788
SBL Stage2: System_init                 |    2.845
SBL Stage2: Drivers_open                |    0.269
SBL Stage2: Board_driversOpen           |    0.089
SBL Stage2: Sciclient Get Version       |    9.976
SBL Stage2: App_loadImages              |    2.427
SBL Stage2: App_loadSelfcoreImage       |   11.338
SBL Stage2: App_loadLinuxImages         |   52.860
----------------------------------------|--------------
SBL : Total time taken                  |  151.302

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL OSPI NAND performance (HS-SE)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 182 KB
- Size of images loaded by stage2  : 895 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   45.202
SBL Stage1: Drivers_open                |    0.209
SBL Stage1: Board_driversOpen           |    0.088
SBL Stage1: Sciclient Get Version       |    9.925
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    5.602
SBL Stage1: App_loadSelfcoreImage       |   10.865
SBL Stage2: System_init                 |    2.835
SBL Stage2: Drivers_open                |    0.269
SBL Stage2: Board_driversOpen           |    0.088
SBL Stage2: Sciclient Get Version       |    9.961
SBL Stage2: App_loadImages              |    2.514
SBL Stage2: App_loadSelfcoreImage       |   11.431
SBL Stage2: App_loadLinuxImages         |   52.995
----------------------------------------|--------------
SBL : Total time taken                  |  159.683

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 157 KB
- Size of images loaded by stage2  : 940 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   6.668
SBL Stage1: Drivers_open                |   50.067
SBL Stage1: Board_driversOpen           |   0
SBL Stage1: Sciclient Get Version       |   9.928
SBL Stage1: App_loadImages              |   23.087
SBL Stage1: App_loadSelfcoreImage       |   24.984
SBL Stage2: System_init                 |   2.669
SBL Stage2: Drivers_open                |   19.541
SBL Stage2: Board_driversOpen           |   0.001
SBL Stage2: Sciclient Get Version       |   9.975
SBL Stage2: App_loadImages              |   21.374
SBL Stage2: App_loadSelfcoreImage       |   26.255
SBL Stage2: App_loadLinuxImages         |   50.493
----------------------------------------|--------------
SBL : Total time taken                  |   245.066

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 157 KB
- Size of images loaded by stage2  : 940 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    6.861
SBL Stage1: Drivers_open                |   60.652
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.928
SBL Stage1: App_loadImages              |   23.162
SBL Stage1: App_loadSelfcoreImage       |   25.043
SBL Stage2: System_init                 |    2.666
SBL Stage2: Drivers_open                |   19.542
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.001
SBL Stage2: App_loadImages              |   21.468
SBL Stage2: App_loadSelfcoreImage       |   26.326
SBL Stage2: App_loadLinuxImages         |   50.596
----------------------------------------|--------------
SBL : Total time taken                  |   256.246

- The emmc driver initialization is done as part of Drivers_open. It takes more than 750ms. This needs more investigation.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 157 KB
- Size of images loaded by stage2  : 895 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   36.179
SBL Stage1: Drivers_open                |   25.260
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.929
SBL Stage1: App_loadImages              |   23.180
SBL Stage1: App_loadSelfcoreImage       |   25.072
SBL Stage2: System_init                 |    2.676
SBL Stage2: Drivers_open                |   19.546
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |    9.972
SBL Stage2: App_loadImages              |   21.393
SBL Stage2: App_loadSelfcoreImage       |   26.299
SBL Stage2: App_loadLinuxImages         |   49.668
----------------------------------------|--------------
SBL : Total time taken                  |  249.180

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 157 KB
- Size of images loaded by stage2  : 895 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   36.164
SBL Stage1: Drivers_open                |   26.775
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    9.927
SBL Stage1: App_loadImages              |   23.284
SBL Stage1: App_loadSelfcoreImage       |   25.177
SBL Stage2: System_init                 |    2.676
SBL Stage2: Drivers_open                |   19.542
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |    9.970
SBL Stage2: App_loadImages              |   21.511
SBL Stage2: App_loadSelfcoreImage       |   26.418
SBL Stage2: App_loadLinuxImages         |   50.718
----------------------------------------|--------------
SBL : Total time taken                  |  252.168

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

Local Core  | Remote Core | Message Size | Average Message Latency (us)
------------|-------------|--------------|------------------------------
 r5f0-0     | m4f0-0      | 32           |  2.273
 r5f0-0     | m4f0-0      | 64           |  3.296
 r5f0-0     | m4f0-0      | 112          |  4.823

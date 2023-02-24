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

### AM62X-SK SBL OSPI performance (HS_FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 181 KB
- Size of images loaded by stage2  : 927 KB
- Boot Media Clock                 : 166.667 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   6.631
SBL Stage1: Drivers_open                |   0.216
SBL Stage1: Board_driversOpen           |   102.127
SBL Stage1: Sciclient Get Version       |   10.109
SBL Stage1: App_loadImages              |   34.924
SBL Stage1: App_loadSelfcoreImage       |   23.380
SBL Stage2: System_init                 |   2.820
SBL Stage2: Drivers_open                |   0.268
SBL Stage2: Board_driversOpen           |   43.889
SBL Stage2: Sciclient Get Version       |   10.135
SBL Stage2: App_loadImages              |   3.080
SBL Stage2: App_loadSelfcoreImage       |   30.158
SBL Stage2: App_loadLinuxImages         |   131.160
----------------------------------------|--------------
SBL : Total time taken                  |   398.902

- The time taken for Board_driversOpen (around 100 ms) is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- Most of the time taken for the CPU load is in loading the M4F. This needs more investigation. Possible reason is the M4F IRAM and DRAM initialization time.

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK SBL OSPI performance (HS_SE)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 181 KB
- Size of images loaded by stage2  : 927 KB
- Boot Media Clock                 : 166.667 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   6.733
SBL Stage1: Drivers_open                |   0.208
SBL Stage1: Board_driversOpen           |   41.962
SBL Stage1: Sciclient Get Version       |   10.110
SBL Stage1: App_loadImages              |   35.132
SBL Stage1: App_loadSelfcoreImage       |   23.807
SBL Stage2: System_init                 |   2.827
SBL Stage2: Drivers_open                |   0.266
SBL Stage2: Board_driversOpen           |   98.048
SBL Stage2: Sciclient Get Version       |   10.162
SBL Stage2: App_loadImages              |   3.183
SBL Stage2: App_loadSelfcoreImage       |   30.592
SBL Stage2: App_loadLinuxImages         |   133.246
----------------------------------------|--------------
SBL : Total time taken                  |   396.280

- The time taken for Board_driversOpen (around 100 ms) is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- Most of the time taken for the CPU load is in loading the M4F. This needs more investigation. Possible reason is the M4F IRAM and DRAM initialization time.

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK LP SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 175 KB
- Size of images loaded by stage2  : 1005 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   35.926
SBL Stage1: Drivers_open                |   0.207
SBL Stage1: Board_driversOpen           |   0.086
SBL Stage1: Sciclient Get Version       |   10.111
SBL Stage1: App_loadImages              |   52.718
SBL Stage1: App_loadSelfcoreImage       |   36.703
SBL Stage2: System_init                 |   2.823
SBL Stage2: Drivers_open                |   0.276
SBL Stage2: Board_driversOpen           |   0.087
SBL Stage2: Sciclient Get Version       |   10.162
SBL Stage2: App_loadImages              |   4.399
SBL Stage2: App_loadSelfcoreImage       |   49.680
SBL Stage2: App_loadLinuxImages         |   232.701
----------------------------------------|--------------
SBL : Total time taken                  |   435.884

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL OSPI NAND performance (HS-SE)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 175 KB
- Size of images loaded by stage2  : 1005 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   36.488
SBL Stage1: Drivers_open                |   0.207
SBL Stage1: Board_driversOpen           |   0.087
SBL Stage1: Sciclient Get Version       |   10.110
SBL Stage1: App_loadImages              |   52.925
SBL Stage1: App_loadSelfcoreImage       |   37.109
SBL Stage2: System_init                 |   2.831
SBL Stage2: Drivers_open                |   0.274
SBL Stage2: Board_driversOpen           |   0.087
SBL Stage2: Sciclient Get Version       |   10.185
SBL Stage2: App_loadImages              |   4.496
SBL Stage2: App_loadSelfcoreImage       |   50.126
SBL Stage2: App_loadLinuxImages         |   234.955
----------------------------------------|--------------
SBL : Total time taken                  |   439.884

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

\cond AM62X_TBD
### AM62X-SK SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 155 KB
- Size of images loaded by stage2  : 927 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   6.294
SBL Stage1: Drivers_open                |   764.664
SBL Stage1: Board_driversOpen           |   0
SBL Stage1: Sciclient Get Version       |   10.113
SBL Stage1: App_loadImages              |   188.937
SBL Stage1: App_loadSelfcoreImage       |   264.425
SBL Stage2: System_init                 |   2.643
SBL Stage2: Drivers_open                |   764.698
SBL Stage2: Board_driversOpen           |   0
SBL Stage2: Sciclient Get Version       |   10.158
SBL Stage2: App_loadImages              |   91.115
SBL Stage2: App_loadSelfcoreImage       |   313.199
SBL Stage2: App_loadLinuxImages         |   815.840
----------------------------------------|--------------
SBL : Total time taken                  |   3232.092

- The emmc driver initialization is done as part of Drivers_open. It takes more than 750ms. This needs more investigation.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 154 KB
- Size of images loaded by stage2  : 926 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   6.647
SBL Stage1: Drivers_open                |   764.665
SBL Stage1: Board_driversOpen           |   0
SBL Stage1: Sciclient Get Version       |   10.112
SBL Stage1: App_loadImages              |   186.334
SBL Stage1: App_loadSelfcoreImage       |   263.199
SBL Stage2: System_init                 |   2.642
SBL Stage2: Drivers_open                |   765.607
SBL Stage2: Board_driversOpen           |   0
SBL Stage2: Sciclient Get Version       |   10.161
SBL Stage2: App_loadImages              |   91.233
SBL Stage2: App_loadSelfcoreImage       |   311.608
SBL Stage2: App_loadLinuxImages         |   815.437
----------------------------------------|--------------
SBL : Total time taken                  |   3227.652

- The emmc driver initialization is done as part of Drivers_open. It takes more than 750ms. This needs more investigation.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 155 KB
- Size of images loaded by stage2  : 1005 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   35.648
SBL Stage1: Drivers_open                |   764.661
SBL Stage1: Board_driversOpen           |   0
SBL Stage1: Sciclient Get Version       |   10.112
SBL Stage1: App_loadImages              |   187.195
SBL Stage1: App_loadSelfcoreImage       |   263.916
SBL Stage2: System_init                 |   2.675
SBL Stage2: Drivers_open                |   764.703
SBL Stage2: Board_driversOpen           |   0
SBL Stage2: Sciclient Get Version       |   10.150
SBL Stage2: App_loadImages              |   91.221
SBL Stage2: App_loadSelfcoreImage       |   313.282
SBL Stage2: App_loadLinuxImages         |   883.338
----------------------------------------|--------------
SBL : Total time taken                  |   3326.909

- The emmc driver initialization is done as part of Drivers_open. It takes more than 750ms. This needs more investigation.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 155 KB
- Size of images loaded by stage2  : 1005 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   35.980
SBL Stage1: Drivers_open                |   764.674
SBL Stage1: Board_driversOpen           |   0
SBL Stage1: Sciclient Get Version       |   10.112
SBL Stage1: App_loadImages              |   188.348
SBL Stage1: App_loadSelfcoreImage       |   265.976
SBL Stage2: System_init                 |   2.663
SBL Stage2: Drivers_open                |   764.703
SBL Stage2: Board_driversOpen           |   0.001
SBL Stage2: Sciclient Get Version       |   10.149
SBL Stage2: App_loadImages              |   91.385
SBL Stage2: App_loadSelfcoreImage       |   314.835
SBL Stage2: App_loadLinuxImages         |   894.793
----------------------------------------|--------------
SBL : Total time taken                  |   3343.625

- The emmc driver initialization is done as part of Drivers_open. It takes more than 750ms. This needs more investigation.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

\endcond

### IPC performance

#### IPC NOTIFY

- 1000000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0 | m4f0-0        |  1.605

#### IPC RPMSG

- 100000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us)
------------|-------------|--------------|------------------------------
 r5f0-0 | m4f0-0        | 32    |  26
 r5f0-0 | m4f0-0        | 64    |  36
 r5f0-0 | m4f0-0        | 112   |  52

# Datasheet {#DATASHEET_AM62X_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Generic Setup details

<table>
    <tr>
        <th>SOC Details</th>
        <th>Core</th>
        <th>Value</th>
    </tr>
    <tr>
        <td rowspan=2>Core Operating Speed</td>
        <td>R5F</td>
        <td>400 MHz</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>1.4 GHz</td>
    </tr>
    <tr>
        <td rowspan=2>Cache Status</td>
        <td>R5F</td>
        <td>Enabled</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>Enabled</td>
    </tr>
</table>

<table>
    <tr>
        <th>Optimization Details</th>
        <th>Core</th>
        <th>Value</th>
    </tr>
    <tr>
        <td>Build Profile</td>
        <td>R5F, A53</td>
        <td>Release</td>
    </tr>
    <tr>
        <td rowspan=2>Compiler flags</td>
        <td>R5F</td>
        <td>-mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -Wall -Werror -g -mthumb -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>-mcpu=cortex-a53+fp+simd -mabi=lp64 -mcmodel=large -mstrict-align -mfix-cortex-a53-835769 -mfix-cortex-a53-843419 -Wall -Werror -g        -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wno-unused-but-set-variable -fdata-sections -ffunction-sections</td>
    </tr>
    <tr>
        <td rowspan=2>Linker flags</td>
        <td>R5F</td>
        <td>-Wl,--diag_suppress=10063 -Wl,--ram_model -Wl,--reread_libs</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>-Wl,-static -Wl,--gc-sections -Wl,--build-id=none -lstdc++ -lgcc -lm -lc -lrdimon</td>
    </tr>
    <tr>
        <td rowspan=2>Code Placement</td>
        <td>R5F</td>
        <td>HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>DDR</td>
    </tr>
    <tr>
        <td rowspan=2>Data Placement</td>
        <td>R5F</td>
        <td>HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>DDR</td>
    </tr>
</table>


## Performance Numbers

### AM62X-SK SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 184 KB
- Size of images loaded by stage2  : 1058 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.381
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.297
SBL Stage1: Board_driversOpen           |    6.786
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_waitForMcuPbist         |    4.989
SBL Stage1: App_waitForMcuLbist         |    7.688
SBL Stage1: App_loadImages              |    3.566
SBL Stage1: App_loadSelfcoreImage       |    3.950
----------------------------------------|--------------
SBL Stage1: Total time taken            |   42.859

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.798
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.370
SBL Stage2: Board_driversOpen           |    0.107
SBL Stage2: Sciclient Get Version       |   10.240
SBL Stage2: App_loadImages              |    2.683
SBL Stage2: App_loadSelfcoreImage       |    4.163
SBL Stage2: App_loadLinuxImages         |   12.273
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.635

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK SBL OSPI performance (HS-SE)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 184 KB
- Size of images loaded by stage2  : 1058 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.439
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.297
SBL Stage1: Board_driversOpen           |    6.786
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_waitForMcuPbist         |    4.990
SBL Stage1: App_waitForMcuLbist         |    7.688
SBL Stage1: App_loadImages              |    3.659
SBL Stage1: App_loadSelfcoreImage       |    4.036
----------------------------------------|--------------
SBL Stage1: Total time taken            |   43.098

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.802
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.369
SBL Stage2: Board_driversOpen           |    0.107
SBL Stage2: Sciclient Get Version       |   10.242
SBL Stage2: App_loadImages              |    2.763
SBL Stage2: App_loadSelfcoreImage       |    4.262
SBL Stage2: App_loadLinuxImages         |   12.234
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.780

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK-SIP SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 184 KB
- Size of images loaded by stage2  : 1058 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.472
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.293
SBL Stage1: Board_driversOpen           |    6.785
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    5.002
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.574
SBL Stage1: App_loadSelfcoreImage       |    3.977
----------------------------------------|--------------
SBL Stage1: Total time taken            |   60.996

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.792
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.366
SBL Stage2: Board_driversOpen           |   28.039
SBL Stage2: Sciclient Get Version       |   10.252
SBL Stage2: App_loadImages              |    2.681
SBL Stage2: App_loadSelfcoreImage       |    4.206
SBL Stage2: App_loadLinuxImages         |   12.638
----------------------------------------|--------------
SBL Stage2: Total time taken            |   60.975

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK LP SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 182 KB
- Size of images loaded by stage2  : 1043 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.403
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.205
SBL Stage1: Board_driversOpen           |    6.590
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    5.283
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.965
SBL Stage1: App_loadSelfcoreImage       |    7.347
----------------------------------------|--------------
SBL Stage1: Total time taken            |   74.686

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.846
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.267
SBL Stage2: Board_driversOpen           |   47.049
SBL Stage2: Sciclient Get Version       |   10.240
SBL Stage2: App_loadImages              |    2.179
SBL Stage2: App_loadSelfcoreImage       |    7.645
SBL Stage2: App_loadLinuxImages         |   39.963
----------------------------------------|--------------
SBL Stage2: Total time taken            |  110.190

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL OSPI NAND performance (HS-SE)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 182 KB
- Size of images loaded by stage2  : 1043 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.519
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.204
SBL Stage1: Board_driversOpen           |    6.702
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    5.173
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.059
SBL Stage1: App_loadSelfcoreImage       |    7.444
----------------------------------------|--------------
SBL Stage1: Total time taken            |   74.994

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.841
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.269
SBL Stage2: Board_driversOpen           |   47.512
SBL Stage2: Sciclient Get Version       |   10.225
SBL Stage2: App_loadImages              |    2.268
SBL Stage2: App_loadSelfcoreImage       |    7.724
SBL Stage2: App_loadLinuxImages         |   40.077
----------------------------------------|--------------
SBL Stage2: Total time taken            |  110.917

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 158 KB
- Size of images loaded by stage2  : 1058 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.280
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.556
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_loadImages              |    7.382
SBL Stage1: App_loadSelfcoreImage       |    7.822
----------------------------------------|--------------
SBL Stage1: Total time taken            |   50.246

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.623
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.524
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.234
SBL Stage2: App_loadImages              |    6.173
SBL Stage2: App_loadSelfcoreImage       |    8.678
SBL Stage2: App_loadLinuxImages         |   28.859
----------------------------------------|--------------
SBL Stage2: Total time taken            |   76.091

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 158 KB
- Size of images loaded by stage2  : 1058 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.373
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.512
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_loadImages              |    6.344
SBL Stage1: App_loadSelfcoreImage       |    7.639
----------------------------------------|--------------
SBL Stage1: Total time taken            |   49.072

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.628
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.539
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.265
SBL Stage2: App_loadImages              |    5.175
SBL Stage2: App_loadSelfcoreImage       |    8.503
SBL Stage2: App_loadLinuxImages         |   28.549
----------------------------------------|--------------
SBL Stage2: Total time taken            |   74.659

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK-SIP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 158 KB
- Size of images loaded by stage2  : 1058 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.401
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.558
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.201
SBL Stage1: App_loadImages              |    7.429
SBL Stage1: App_loadSelfcoreImage       |    7.912
----------------------------------------|--------------
SBL Stage1: Total time taken            |   68.501

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.637
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.527
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.248
SBL Stage2: App_loadImages              |    6.161
SBL Stage2: App_loadSelfcoreImage       |    8.695
SBL Stage2: App_loadLinuxImages         |   29.126
----------------------------------------|--------------
SBL Stage2: Total time taken            |   76.394

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 158 KB
- Size of images loaded by stage2  : 1043 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.659
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   30.414
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_loadImages              |    6.437
SBL Stage1: App_loadSelfcoreImage       |    7.799
----------------------------------------|--------------
SBL Stage1: Total time taken            |

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.652
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.543
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.258
SBL Stage2: App_loadImages              |    5.227
SBL Stage2: App_loadSelfcoreImage       |    8.609
SBL Stage2: App_loadLinuxImages         |   29.035
----------------------------------------|--------------
SBL Stage2: Total time taken            |   75.325

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 158 KB
- Size of images loaded by stage2  : 1043 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.267
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   64.300
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_loadImages              |    6.763
SBL Stage1: App_loadSelfcoreImage       |    7.954
----------------------------------------|--------------
SBL Stage1: Total time taken            |  122.488

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.661
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.546
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.236
SBL Stage2: App_loadImages              |    5.402
SBL Stage2: App_loadSelfcoreImage       |    8.742
SBL Stage2: App_loadLinuxImages         |   29.230
----------------------------------------|--------------
SBL Stage2: Total time taken            |   75.818

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.


### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | m4f0-0      |  1.58
 r5f0-0     | a530-0      |  10.00

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) |Max Latency (us)
------------|-------------|--------------|------------------------------|--------------------
      r5f0-0|       m4f0-0|             4|                        14.140|                15
      r5f0-0|       m4f0-0|            32|                        23.762|                24
      r5f0-0|       m4f0-0|            64|                        34.884|                36
      r5f0-0|       m4f0-0|           112|                        51.509|                53
      r5f0-0|       a530-0|             4|                        10.835|                12
      r5f0-0|       a530-0|            32|                        14.647|                16
      r5f0-0|       a530-0|            64|                        19.345|                20
      r5f0-0|       a530-0|           112|                        26.236|                27

### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 36.80		         | 44.14
 SDR50 | 4	            | 41.50		         | 43.48
 SDR50 | 6	            | 41.74		         | 43.93
 DDR50 | 1	            | 49.63		         | 79.05
 DDR50 | 4	            | 47.22		         | 77.00
 DDR50 | 6	            | 52.24		         | 78.28
 HS200 | 1	            | 48.79		         | 151.55
 HS200 | 4	            | 57.12		         | 144.02
 HS200 | 6	            | 55.92		         | 149.03
**a53 :**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1              | 41.05              | 46.15
 SDR50 | 4              | 43.22              | 45.40
 SDR50 | 6              | 41.85              | 46.04
 DDR50 | 1              | 56.55              | 85.67
 DDR50 | 4              | 60.29              | 83.08
 DDR50 | 6              | 60.40              | 84.47
 HS200 | 1              | 59.85              | 177.94
 HS200 | 4              | 58.30              | 167.16
 HS200 | 6              | 61.80              | 172.92

### OSPI NOR Flash Performance
**r5f0-0:**
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 0.43		    | 247.45
 5	       | 0.44		    | 248.67
 10	       | 0.43		    | 248.83

**a53 :**
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1             | 0.47               | 325.76
 5             | 0.47               | 326.95
 10            | 0.47               | 327.09

### OSPI NAND Flash Performance
**r5f0-0:**
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 2.40		    | 44.86
 5	       | 2.40		    | 47.69
 10	       | 2.40		    | 47.69

**a53 :**
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - PHY : disabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1             | 2.23               | 18.67
 5             | 2.24               | 18.67
 10            | 2.24               | 18.67
 ### GPMC NAND Flash Performance

 - Flash type: PARALLEL NAND
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 6.69		    | 19.93
 5	       | 6.70		    | 19.93
 10	       | 6.70		    | 19.93
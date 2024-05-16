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
SBL Stage1: System_init                 |    5.508
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.299
SBL Stage1: Board_driversOpen           |    6.786
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    4.996
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.574
SBL Stage1: App_loadSelfcoreImage       |    3.948
----------------------------------------|--------------
SBL Stage1: Total time taken            |   43.008

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.836
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.365
SBL Stage2: Board_driversOpen           |   27.967
SBL Stage2: Sciclient Get Version       |   10.261
SBL Stage2: App_loadImages              |    2.680
SBL Stage2: App_loadSelfcoreImage       |    4.152
SBL Stage2: App_loadLinuxImages         |   11.765
----------------------------------------|--------------
SBL Stage2: Total time taken            |   60.030

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
SBL Stage1: System_init                 |    5.465
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.297
SBL Stage1: Board_driversOpen           |    6.786
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    4.998
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.643
SBL Stage1: App_loadSelfcoreImage       |    4.025
----------------------------------------|--------------
SBL Stage1: Total time taken            |   43.111

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.832
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.371
SBL Stage2: Board_driversOpen           |   27.747
SBL Stage2: Sciclient Get Version       |   10.231
SBL Stage2: App_loadImages              |    2.763
SBL Stage2: App_loadSelfcoreImage       |    4.238
SBL Stage2: App_loadLinuxImages         |   11.847
----------------------------------------|--------------
SBL Stage2: Total time taken            |   60.033

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
SBL Stage1: System_init                 |   23.402
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.295
SBL Stage1: Board_driversOpen           |    6.784
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_waitForMcuPbist         |    5.002
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.571
SBL Stage1: App_loadSelfcoreImage       |    3.968
----------------------------------------|--------------
SBL Stage1: Total time taken            |   60.920

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.857
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.367
SBL Stage2: Board_driversOpen           |   28.008
SBL Stage2: Sciclient Get Version       |   10.240
SBL Stage2: App_loadImages              |    2.677
SBL Stage2: App_loadSelfcoreImage       |    4.181
SBL Stage2: App_loadLinuxImages         |   12.109
----------------------------------------|--------------
SBL Stage2: Total time taken            |   60.030

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
SBL Stage1: System_init                 |   33.300
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.204
SBL Stage1: Board_driversOpen           |    6.587
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    5.298
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.017
SBL Stage1: App_loadSelfcoreImage       |    7.347
----------------------------------------|--------------
SBL Stage1: Total time taken            |   74.651

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.884
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.267
SBL Stage2: Board_driversOpen           |   47.058
SBL Stage2: Sciclient Get Version       |   10.289
SBL Stage2: App_loadImages              |    2.182
SBL Stage2: App_loadSelfcoreImage       |    7.648
SBL Stage2: App_loadLinuxImages         |   39.437
----------------------------------------|--------------
SBL Stage2: Total time taken            |  109.768

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
SBL Stage1: System_init                 |   33.559
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.203
SBL Stage1: Board_driversOpen           |    6.701
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_waitForMcuPbist         |    5.176
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.095
SBL Stage1: App_loadSelfcoreImage       |    7.446
----------------------------------------|--------------
SBL Stage1: Total time taken            |   75.076

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.887
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.266
SBL Stage2: Board_driversOpen           |   47.533
SBL Stage2: Sciclient Get Version       |   10.249
SBL Stage2: App_loadImages              |    2.261
SBL Stage2: App_loadSelfcoreImage       |    7.732
SBL Stage2: App_loadLinuxImages         |   39.516
----------------------------------------|--------------
SBL Stage2: Total time taken            |  110.448

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
SBL Stage1: System_init                 |    5.621
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   50.974
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_loadImages              |    6.682
SBL Stage1: App_loadSelfcoreImage       |    7.989
----------------------------------------|--------------
SBL Stage1: Total time taken            |   81.472

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    3.658
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   19.541
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.250
SBL Stage2: App_loadImages              |    5.530
SBL Stage2: App_loadSelfcoreImage       |    8.827
SBL Stage2: App_loadLinuxImages         |   28.470
----------------------------------------|--------------
SBL Stage2: Total time taken            |   76.282

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
SBL Stage1: System_init                 |    5.397
SBL Stage1: Board_init                  |    0.001
SBL Stage1: Drivers_open                |   19.515
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.201
SBL Stage1: App_loadImages              |    6.357
SBL Stage1: App_loadSelfcoreImage       |    7.632
----------------------------------------|--------------
SBL Stage1: Total time taken            |   49.106

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.663
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   19.537
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.260
SBL Stage2: App_loadImages              |    5.202
SBL Stage2: App_loadSelfcoreImage       |    8.470
SBL Stage2: App_loadLinuxImages         |   28.090
----------------------------------------|--------------
SBL Stage2: Total time taken            |   74.226

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
SBL Stage1: System_init                 |   23.459
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.575
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_loadImages              |    7.371
SBL Stage1: App_loadSelfcoreImage       |    7.887
----------------------------------------|--------------
SBL Stage1: Total time taken            |   68.497

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.652
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   19.524
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.258
SBL Stage2: App_loadImages              |    6.163
SBL Stage2: App_loadSelfcoreImage       |    8.675
SBL Stage2: App_loadLinuxImages         |   28.567
----------------------------------------|--------------
SBL Stage2: Total time taken            |   75.844

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
SBL Stage1: System_init                 |   33.272
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   58.245
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.201
SBL Stage1: App_loadImages              |    6.422
SBL Stage1: App_loadSelfcoreImage       |    7.742
----------------------------------------|--------------
SBL Stage1: Total time taken            |  115.885

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.693
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   19.545
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.263
SBL Stage2: App_loadImages              |    5.161
SBL Stage2: App_loadSelfcoreImage       |    8.560
SBL Stage2: App_loadLinuxImages         |   28.521
----------------------------------------|--------------
SBL Stage2: Total time taken            |   74.749

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
SBL Stage1: System_init                 |   33.454
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   45.241
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_loadImages              |    6.650
SBL Stage1: App_loadSelfcoreImage       |    7.950
----------------------------------------|--------------
SBL Stage1: Total time taken            |  103.498

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.688
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   19.546
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.241
SBL Stage2: App_loadImages              |    5.562
SBL Stage2: App_loadSelfcoreImage       |    9.011
SBL Stage2: App_loadLinuxImages         |   28.992
----------------------------------------|--------------
SBL Stage2: Total time taken            |   76.044

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.


### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | m4f0-0      |  1.58
 r5f0-0     | a530-0      |  9.77

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) |Max Latency (us)
------------|-------------|--------------|------------------------------|--------------------
      r5f0-0|       m4f0-0|             4|                        13.824|                15
      r5f0-0|       m4f0-0|            32|                        22.792|                23
      r5f0-0|       m4f0-0|            64|                        32.998|                34
      r5f0-0|       m4f0-0|           112|                        48.224|                49
      r5f0-0|       a530-0|             4|                        10.582|                11
      r5f0-0|       a530-0|            32|                        14.215|                15
      r5f0-0|       a530-0|            64|                        18.562|                21
      r5f0-0|       a530-0|           112|                        25.626|                26
### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 36.75		         | 44.14
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
 1	           | 0.42		        | 247.42
 5	           | 0.43		        | 248.67
 10	           | 0.43		        | 248.83

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
 1	           | 2.39		        | 44.75
 5	           | 2.40		        | 47.24
 10	           | 2.40		        | 47.46

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
 1	           | 6.70		        | 19.93
 5	           | 6.70		        | 19.93
 10	           | 6.70		        | 19.93
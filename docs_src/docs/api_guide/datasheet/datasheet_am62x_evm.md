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
- Size of images loaded by stage1  : 190 KB
- Size of images loaded by stage2  : 988 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.460
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.298
SBL Stage1: Board_driversOpen           |    1.272
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_waitForMcuPbist         |    8.663
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.611
SBL Stage1: App_loadSelfcoreImage       |    4.021
----------------------------------------|--------------
SBL Stage1: Total time taken            |   41.219

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.819
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.382
SBL Stage2: Board_driversOpen           |    0.152
SBL Stage2: Sciclient Get Version       |   10.247
SBL Stage2: App_loadImages              |    2.688
SBL Stage2: App_loadSelfcoreImage       |    4.201
SBL Stage2: App_loadLinuxImages         |   10.995
----------------------------------------|--------------
SBL Stage2: Total time taken            |   31.487

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK SBL OSPI performance (HS-SE)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 190 KB
- Size of images loaded by stage2  : 988 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.646
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.300
SBL Stage1: Board_driversOpen           |    1.267
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    8.652
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.692
SBL Stage1: App_loadSelfcoreImage       |    4.097
----------------------------------------|--------------
SBL Stage1: Total time taken            |   41.551

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.805
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.385
SBL Stage2: Board_driversOpen           |    0.154
SBL Stage2: Sciclient Get Version       |   10.212
SBL Stage2: App_loadImages              |    2.771
SBL Stage2: App_loadSelfcoreImage       |    4.291
SBL Stage2: App_loadLinuxImages         |   11.060
----------------------------------------|--------------
SBL Stage2: Total time taken            |   31.682

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK-SIP SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 190 KB
- Size of images loaded by stage2  : 988 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.623
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.300
SBL Stage1: Board_driversOpen           |    1.264
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    6.000
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.596
SBL Stage1: App_loadSelfcoreImage       |    4.042
----------------------------------------|--------------
SBL Stage1: Total time taken            |   50.727

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.797
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.382
SBL Stage2: Board_driversOpen           |    0.153
SBL Stage2: Sciclient Get Version       |   10.241
SBL Stage2: App_loadImages              |    2.690
SBL Stage2: App_loadSelfcoreImage       |    4.238
SBL Stage2: App_loadLinuxImages         |   11.277
----------------------------------------|--------------
SBL Stage2: Total time taken            |   31.783

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK LP SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 188 KB
- Size of images loaded by stage2  : 1081 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.655
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.208
SBL Stage1: Board_driversOpen           |   26.467
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_waitForMcuPbist         |    6.000
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.956
SBL Stage1: App_loadSelfcoreImage       |    7.530
----------------------------------------|--------------
SBL Stage1: Total time taken            |   89.717

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.856
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.273
SBL Stage2: Board_driversOpen           |   30.276
SBL Stage2: Sciclient Get Version       |   10.256
SBL Stage2: App_loadImages              |    2.169
SBL Stage2: App_loadSelfcoreImage       |    7.768
SBL Stage2: App_loadLinuxImages         |   40.535
----------------------------------------|--------------
SBL Stage2: Total time taken            |   94.137

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL OSPI NAND performance (HS-SE)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 188 KB
- Size of images loaded by stage2  : 1081 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.458
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.209
SBL Stage1: Board_driversOpen           |   26.467
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_waitForMcuPbist         |    5.000
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.047
SBL Stage1: App_loadSelfcoreImage       |    7.642
----------------------------------------|--------------
SBL Stage1: Total time taken            |   89.725

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.854
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.276
SBL Stage2: Board_driversOpen           |   26.067
SBL Stage2: Sciclient Get Version       |   10.227
SBL Stage2: App_loadImages              |    2.245
SBL Stage2: App_loadSelfcoreImage       |    7.854
SBL Stage2: App_loadLinuxImages         |   40.600
----------------------------------------|--------------
SBL Stage2: Total time taken            |   90.118

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 159 KB
- Size of images loaded by stage2  : 988 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.378
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |  109.659
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_loadImages              |    6.439
SBL Stage1: App_loadSelfcoreImage       |    7.706
----------------------------------------|--------------
SBL Stage1: Total time taken            |  139.387

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.626
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.555
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.256
SBL Stage2: App_loadImages              |    5.213
SBL Stage2: App_loadSelfcoreImage       |    8.660
SBL Stage2: App_loadLinuxImages         |   26.900
----------------------------------------|--------------
SBL Stage2: Total time taken            |   73.215

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 159 KB
- Size of images loaded by stage2  : 988 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.523
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   44.318
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.201
SBL Stage1: App_loadImages              |    6.427
SBL Stage1: App_loadSelfcoreImage       |    7.670
----------------------------------------|--------------
SBL Stage1: Total time taken            |   74.143

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.631
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.556
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.268
SBL Stage2: App_loadImages              |    5.182
SBL Stage2: App_loadSelfcoreImage       |    8.561
SBL Stage2: App_loadLinuxImages         |   26.798
----------------------------------------|--------------
SBL Stage2: Total time taken            |   73.001

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK-SIP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 159 KB
- Size of images loaded by stage2  : 988 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.558
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.556
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_loadImages              |    7.348
SBL Stage1: App_loadSelfcoreImage       |    8.600
----------------------------------------|--------------
SBL Stage1: Total time taken            |   69.269

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.633
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   19.524
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.239
SBL Stage2: App_loadImages              |    5.404
SBL Stage2: App_loadSelfcoreImage       |    8.737
SBL Stage2: App_loadLinuxImages         |   26.505
----------------------------------------|--------------
SBL Stage2: Total time taken            |   73.047

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 159 KB
- Size of images loaded by stage2  : 1081 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   33.281
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   39.524
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.201
SBL Stage1: App_loadImages              |    6.442
SBL Stage1: App_loadSelfcoreImage       |    7.838
----------------------------------------|--------------
SBL Stage1: Total time taken            |   77.289

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.653
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   19.558
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.239
SBL Stage2: App_loadImages              |    5.228
SBL Stage2: App_loadSelfcoreImage       |    8.600
SBL Stage2: App_loadLinuxImages         |   29.639
----------------------------------------|--------------
SBL Stage2: Total time taken            |   75.922

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
SBL Stage1: System_init                 |   33.460
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   83.355
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.201
SBL Stage1: App_loadImages              |    6.704
SBL Stage1: App_loadSelfcoreImage       |    8.220
----------------------------------------|--------------
SBL Stage1: Total time taken            |  141.943

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.644
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   19.558
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.260
SBL Stage2: App_loadImages              |    5.557
SBL Stage2: App_loadSelfcoreImage       |    9.089
SBL Stage2: App_loadLinuxImages         |   30.052
----------------------------------------|--------------
SBL Stage2: Total time taken            |   77.165

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.


### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | m4f0-0      |  1.58
 r5f0-0     | a530-0      |  9.74

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
      r5f0-0|       m4f0-0|             4|                        13.815|                14|         1000
      r5f0-0|       m4f0-0|            32|                        22.780|                23|         1000
      r5f0-0|       m4f0-0|            64|                        32.917|                34|         1000
      r5f0-0|       m4f0-0|           112|                        48.203|                49|         1000
      r5f0-0|       a530-0|             4|                        10.536|                11|         1000
      r5f0-0|       a530-0|            32|                        14.166|                15|         1000
      r5f0-0|       a530-0|            64|                        18.459|                19|         1000
      r5f0-0|       a530-0|           112|                        25.020|                26|         1000

### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 36.79		         | 44.14
 SDR50 | 4	            | 39.71		         | 43.49
 SDR50 | 6	            | 41.74		         | 43.93
 DDR50 | 1	            | 49.29		         | 79.12
 DDR50 | 4	            | 57.11	             | 77.45
 DDR50 | 6	            | 51.95		         | 78.29
 HS200 | 1	            | 49.27		         | 151.68
 HS200 | 4	            | 55.42		         | 144.10
 HS200 | 6	            | 57.18		         | 149.07
**a53 :**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1              | 40.66              | 46.14
 SDR50 | 4              | 43.23              | 45.41
 SDR50 | 6              | 41.51              | 45.92
 DDR50 | 1              | 56.94              | 86.60
 DDR50 | 4              | 59.54              | 83.08
 DDR50 | 6              | 58.57              | 83.12
 HS200 | 1              | 59.85              | 177.97
 HS200 | 4              | 58.30              | 167.30
 HS200 | 6              | 61.80              | 172.99

### OSPI NOR Flash Performance
**r5f0-0:**
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 0.43		    | 247.44
 5	       | 0.44		    | 248.67
 10	       | 0.44		    | 248.83

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          3.53 ms
Fast Tuning Window          |          1.15 ms

**a53 :**
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 0.44		    | 325.76
 5	       | 0.45		    | 326.94
 10	       | 0.45		    | 327.08

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          2.96 ms
Fast Tuning Window          |          1.01 ms

### OSPI NAND Flash Performance
**r5f0-0:**
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 2.07		    | 46.88
 5	       | 2.07		    | 46.90
 10	       | 2.07		    | 46.90

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.12  ms
Fast Tuning Window          |          0.63  ms

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
**r5f0-0:**
 - Flash type: PARALLEL NAND
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 6.66		    | 20.06
 5	       | 6.66		    | 20.06
 10	       | 6.67		    | 20.06

**a53 :**
Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 9.65		    | 22.15
 5	       | 9.66		    | 22.15
 10	       | 9.66		    | 22.15
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

### AM62X Dhrystone Benchmark performance

Core : **a530-0**

Benchmarks                      | am62x-sk      | am62x-sk-lp    | am62x-sip-sk |
--------------------------------|---------------|----------------|--------------|
cpu_clock (MHz)                 |   1400        |  1400          |  1400        |
dhrystone_per_mhz (DMIPS/MHz)   |   2.8577      |  2.8577        |  2.8577      |
dhrystone_per_second            |   7029351.2   |  7029351.2     |  7029351.2   |

### AM62X Interrupt Latency Benchmark performance

The latency measurements include IRQ entry handling latency + ISR + IRQ exit handling latency.

Core : **a530-0**

Benchmarks                      | am62x-sk      | am62x-sk-lp   | am62x-sip-sk   |
--------------------------------|---------------|---------------|----------------|
cpu_clock (MHz)                 |   1400        |  1400         |  1400          |
interrupt latency (ns)          |   620         |  622          |  620           |

### AM62X Coremark Pro Benchmark performance

Workload computed for **Single core**

Core : **a530-0**

Benchmark (worloads)             |  am62xx_lp_sk-fs  |    am62xx_sk-fs    |   am62xxsip_sk-fs    |
---------------------------------|-------------------|--------------------|----------------------|
cjpeg-rose7-preset               | 40.42             | 40.42              | 40.42                |
core                             | 0.29              | 0.29               | 0.29                 |
linear_alg-mid-100x100-sp        | 16.30             | 16.30              | 16.30                |
loops-all-mid-10k-sp             | 0.72              | 0.72               | 0.73                 |
nnet_test                        | 1.88              | 1.88               | 1.88                 |
parser-125k                      | 5.75              | 5.76               | 5.76                 |
radix2-big-64k                   | 76.80             | 78.32              | 77.87                |
sha-test                         | 81.73             | 81.74              | 81.74                |
zip-test                         | 27.16             | 27.31              | 27.31                |
Coremark-pro()(overall score)    | 987.78            | 992.26             | 991.40               |

### AM62X-SK SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 191 KB
- Size of images loaded by stage2  : 1030 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.551
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.207
SBL Stage1: Board_driversOpen           |    1.367
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    8.653
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.663
SBL Stage1: App_loadSelfcoreImage       |    4.125
----------------------------------------|--------------
SBL Stage1: Total time taken            |   41.462

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.774
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.262
SBL Stage2: Board_driversOpen           |    0.251
SBL Stage2: Sciclient Get Version       |   10.278
SBL Stage2: App_loadImages              |    2.887
SBL Stage2: App_loadSelfcoreImage       |    4.701
SBL Stage2: App_loadLinuxImages         |   13.317
----------------------------------------|--------------
SBL Stage2: Total time taken            |   34.474

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK SBL OSPI performance (HS-SE)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 191 KB
- Size of images loaded by stage2  : 1030 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.654
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.207
SBL Stage1: Board_driversOpen           |    1.353
SBL Stage1: Sciclient Get Version       |   10.206
SBL Stage1: App_waitForMcuPbist         |    8.653
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.680
SBL Stage1: App_loadSelfcoreImage       |    4.133
----------------------------------------|--------------
SBL Stage1: Total time taken            |   41.579

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.769
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.264
SBL Stage2: Board_driversOpen           |    0.249
SBL Stage2: Sciclient Get Version       |   10.234
SBL Stage2: App_loadImages              |    2.897
SBL Stage2: App_loadSelfcoreImage       |    4.697
SBL Stage2: App_loadLinuxImages         |   13.334
----------------------------------------|--------------
SBL Stage2: Total time taken            |   34.447

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK-SIP SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 191 KB
- Size of images loaded by stage2  : 1030 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.833
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.207
SBL Stage1: Board_driversOpen           |    1.357
SBL Stage1: Sciclient Get Version       |   10.205
SBL Stage1: App_waitForMcuPbist         |    0.104
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.672
SBL Stage1: App_loadSelfcoreImage       |    4.152
----------------------------------------|--------------
SBL Stage1: Total time taken            |   51.223

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.765
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.261
SBL Stage2: Board_driversOpen           |    0.249
SBL Stage2: Sciclient Get Version       |   10.244
SBL Stage2: App_loadImages              |    2.888
SBL Stage2: App_loadSelfcoreImage       |    4.691
SBL Stage2: App_loadLinuxImages         |   13.538
----------------------------------------|--------------
SBL Stage2: Total time taken            |   34.640

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK LP SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 189 KB
- Size of images loaded by stage2  : 1122 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   20.891
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.208
SBL Stage1: Board_driversOpen           |   26.488
SBL Stage1: Sciclient Get Version       |   10.205
SBL Stage1: App_waitForMcuPbist         |    0.103
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.976
SBL Stage1: App_loadSelfcoreImage       |    6.274
----------------------------------------|--------------
SBL Stage1: Total time taken            |   75.838

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.842
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.274
SBL Stage2: Board_driversOpen           |   30.319
SBL Stage2: Sciclient Get Version       |   10.253
SBL Stage2: App_loadImages              |    2.304
SBL Stage2: App_loadSelfcoreImage       |    7.770
SBL Stage2: App_loadLinuxImages         |   35.067
----------------------------------------|--------------
SBL Stage2: Total time taken            |   88.834

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL OSPI NAND performance (HS-SE)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 189 KB
- Size of images loaded by stage2  : 1121 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   20.928
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.207
SBL Stage1: Board_driversOpen           |   26.471
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_waitForMcuPbist         |    0.103
SBL Stage1: App_waitForMcuLbist         |    7.688
SBL Stage1: App_loadImages              |    3.986
SBL Stage1: App_loadSelfcoreImage       |    6.298
----------------------------------------|--------------
SBL Stage1: Total time taken            |   75.889

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.816
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.273
SBL Stage2: Board_driversOpen           |   30.284
SBL Stage2: Sciclient Get Version       |   10.234
SBL Stage2: App_loadImages              |    2.316
SBL Stage2: App_loadSelfcoreImage       |    7.784
SBL Stage2: App_loadLinuxImages         |   35.036
----------------------------------------|--------------
SBL Stage2: Total time taken            |   88.747

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 1030 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.652
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   94.021
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_loadImages              |    6.703
SBL Stage1: App_loadSelfcoreImage       |    7.273
----------------------------------------|--------------
SBL Stage1: Total time taken            |   123.853

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.823
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.815
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.250
SBL Stage2: App_loadImages              |    5.494
SBL Stage2: App_loadSelfcoreImage       |    8.252
SBL Stage2: App_loadLinuxImages         |   22.222
----------------------------------------|--------------
SBL Stage2: Total time taken            |   68.859

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 1030 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.863
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   132.436
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_loadImages              |    6.596
SBL Stage1: App_loadSelfcoreImage       |    7.208
----------------------------------------|--------------
SBL Stage1: Total time taken            |   162.129

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.828
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.808
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.246
SBL Stage2: App_loadImages              |    5.401
SBL Stage2: App_loadSelfcoreImage       |   8.158
SBL Stage2: App_loadLinuxImages         |   22.123
----------------------------------------|--------------
SBL Stage2: Total time taken            |   69.568

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK-SIP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 1030 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.917
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   20.712
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_loadImages              |    8.306
SBL Stage1: App_loadSelfcoreImage       |    7.416
----------------------------------------|--------------
SBL Stage1: Total time taken            |   70.557

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.801
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.656
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.246
SBL Stage2: App_loadImages              |    5.688
SBL Stage2: App_loadSelfcoreImage       |    8.359
SBL Stage2: App_loadLinuxImages         |   22.852
----------------------------------------|--------------
SBL Stage2: Total time taken            |   70.605

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 1122 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   20.827
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   98.556
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_loadImages              |    6.653
SBL Stage1: App_loadSelfcoreImage       |    7.276
----------------------------------------|--------------
SBL Stage1: Total time taken            |   143.518

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.832
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   20.845
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.231
SBL Stage2: App_loadImages              |    5.459
SBL Stage2: App_loadSelfcoreImage       |    8.230
SBL Stage2: App_loadLinuxImages         |   22.740
----------------------------------------|--------------
SBL Stage2: Total time taken            |   70.341

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 1122 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   21.072
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   42.572
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_loadImages              |    6.745
SBL Stage1: App_loadSelfcoreImage       |    7.388
----------------------------------------|--------------
SBL Stage1: Total time taken            |  87.981

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.816
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.798
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.233
SBL Stage2: App_loadImages              |    5.414
SBL Stage2: App_loadSelfcoreImage       |    8.195
SBL Stage2: App_loadLinuxImages         |   22.757
----------------------------------------|--------------
SBL Stage2: Total time taken            |   70.217

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.


### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0	    | m4f0-0	  |  1.47
 r5f0-0	    | a530-0	  |  1.53
 r5f0-0	    | a530-1	  |  2.31

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
      r5f0-0|       m4f0-0|             4|                        24.219|                25|         1000
      r5f0-0|       a530-0|             4|                        11.912|                15|         1000
      r5f0-0|       a530-1|             4|                        13.326|                14|         1000
      r5f0-0|       m4f0-0|            32|                        32.601|                33|         1000
      r5f0-0|       m4f0-0|            64|                        42.766|                44|         1000
      r5f0-0|       m4f0-0|           112|                        57.590|                59|         1000
      r5f0-0|       a530-0|            32|                        15.809|                17|         1000
      r5f0-0|       a530-0|            64|                        19.883|                21|         1000
      r5f0-0|       a530-0|           112|                        26.743|                28|         1000
      r5f0-0|       a530-1|            32|                        16.950|                19|         1000
      r5f0-0|       a530-1|            64|                        21.143|                22|         1000
      r5f0-0|       a530-1|           112|                        27.423|                29|         1000

### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 36.82  	         | 44.16
 SDR50 | 4	            | 41.56		         | 43.57
 SDR50 | 6	            | 41.16		         | 43.90
 SDR50 | 32	            | 41.83		         | 44.38
 SDR50 | 40	            | 41.40		         | 44.49
 DDR50 | 1	            | 49.20		         | 79.07
 DDR50 | 4	            | 56.97	             | 76.98
 DDR50 | 6	            | 55.87		         | 78.26
 DDR50 | 32	            | 57.32	             | 79.78
 DDR50 | 40	            | 57.44		         | 80.15
 HS200 | 1	            | 53.80		         | 151.68
 HS200 | 4	            | 57.97		         | 144.22
 HS200 | 6	            | 54.75		         | 148.73
 HS200 | 32	            | 57.35		         | 154.42
 HS200 | 40	            | 57.46		         | 155.71
**a53 :**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 38.16		         | 46.14
 SDR50 | 4	            | 43.22		         | 45.84
 SDR50 | 6	            | 41.75		         | 45.81
 SDR50 | 32	            | 43.23		         | 46.39
 SDR50 | 40	            | 42.72		         | 46.48
 DDR50 | 1	            | 54.28		         | 85.65
 DDR50 | 4	            | 64.17	             | 83.15
 DDR50 | 6	            | 61.27		         | 84.52
 DDR50 | 32	            | 63.45	             | 86.52
 DDR50 | 40	            | 63.47		         | 86.83
 HS200 | 1	            | 56.95		         | 178.03
 HS200 | 4	            | 64.83		         | 167.48
 HS200 | 6	            | 58.50 	         | 173.12
 HS200 | 32	            | 63.34		         | 183.68
 HS200 | 40	            | 64.07 	         | 183.15

### OSPI NOR Flash Performance
**r5f0-0:**

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          3.57 ms
Fast Tuning Window          |          1.14 ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       2.86
      5          |        DAC        |        No         |        0.42          |       2.86
      10         |        DAC        |        No         |        0.42          |       2.86
      1          |        DAC        |        Yes        |        0.42          |       47.53
      5          |        DAC        |        Yes        |        0.42          |       47.57
      10         |        DAC        |        Yes        |        0.42          |       47.58

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.40           |       6.14
      5          |        DAC        |        No         |        0.40           |       6.14
      10         |        DAC        |        No         |        0.40           |       6.14
      1          |        DAC        |        Yes        |        0.40           |       6.21
      5          |        DAC        |        Yes        |        0.40           |       6.21
      10         |        DAC        |        Yes        |        0.40           |       6.21

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       6.33
      5          |        DAC        |        No         |        0.43           |       6.33
      10         |        DAC        |        No         |        0.42           |       6.33
      1          |        DAC        |        Yes        |        0.42           |       208.62
      5          |        DAC        |        Yes        |        0.43           |       209.58
      10         |        DAC        |        Yes        |        0.42           |       209.69

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.42          |       7.02
      5          |        DAC        |        No         |        0.43          |       7.02
      10         |        DAC        |        No         |        0.42          |       7.02
      1          |        DAC        |        Yes        |        0.42          |       247.35
      5          |        DAC        |        Yes        |        0.43          |       248.65
      10         |        DAC        |        Yes        |        0.42          |       248.82

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.42          |       13.74
      5          |       INDAC       |        No         |        0.42          |       13.75
      10         |       INDAC       |        No         |        0.42          |       13.75

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.40          |       6.25
      5          |       INDAC       |        No         |        0.40          |       6.25
      10         |       INDAC       |        No         |        0.40          |       6.25

**a53 :**

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          2.98 ms
Fast Tuning Window          |          0.98 ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.43          |       0.76
      5          |        DAC        |        No         |        0.44          |       0.76
      10         |        DAC        |        No         |        0.44          |       0.76
      1          |        DAC        |        Yes        |        0.43          |       49.83
      5          |        DAC        |        Yes        |        0.44          |       49.86
      10         |        DAC        |        Yes        |        0.44          |       49.86

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       0.54
      5          |        DAC        |        No         |        0.41           |       0.54
      10         |        DAC        |        No         |        0.42           |       0.54
      1          |        DAC        |        Yes        |        0.41           |       6.25
      5          |        DAC        |        Yes        |        0.41           |       6.25
      10         |        DAC        |        Yes        |        0.42           |       6.25

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       1.85
      5          |        DAC        |        No         |        0.44           |       1.85
      10         |        DAC        |        No         |        0.44           |       1.85
      1          |        DAC        |        Yes        |        0.43           |       261.75
      5          |        DAC        |        Yes        |        0.44           |       262.56
      10         |        DAC        |        Yes        |        0.44           |       262.65

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.43          |       2.08
      5          |        DAC        |        No         |        0.44          |       2.08
      10         |        DAC        |        No         |        0.44          |       2.08
      1          |        DAC        |        Yes        |        0.43          |       325.74
      5          |        DAC        |        Yes        |        0.44          |       326.93
      10         |        DAC        |        Yes        |        0.44          |       327.08

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.43          |       19.63
      5          |       INDAC       |        No         |        0.44          |       19.63
      10         |       INDAC       |        No         |        0.44          |       19.63

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.41          |       6.25
      5          |       INDAC       |        No         |        0.41          |       6.25
      10         |       INDAC       |        No         |        0.42          |       6.25

### OSPI NAND Flash Performance
**r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.12  ms
Fast Tuning Window          |          0.63  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.36          |       4.41
      5          |        DAC        |        No         |        2.36          |       4.41
      10         |        DAC        |        No         |        2.35          |       4.41
      1          |        DAC        |        Yes        |        8.51          |       28.67
      5          |        DAC        |        Yes        |        8.53          |       28.67
      10         |        DAC        |        Yes        |        8.63          |       28.67

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.55           |       5.53
      5          |        DAC        |        No         |        1.55           |       5.53
      10         |        DAC        |        No         |        1.55           |       5.53
      1          |        DAC        |        Yes        |        3.88           |       5.73
      5          |        DAC        |        Yes        |        3.88           |       5.73
      10         |        DAC        |        Yes        |        3.88           |       5.73

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.36           |       3.63
      5          |        DAC        |        No         |        2.36           |       3.62
      10         |        DAC        |        No         |        2.36           |       3.63
      1          |        DAC        |        Yes        |        8.48           |       29.22
      5          |        DAC        |        Yes        |        8.57           |       29.22
      10         |        DAC        |        Yes        |        8.57           |       29.22

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.36           |       5.37
      5          |        DAC        |        No         |        2.36           |       5.37
      10         |        DAC        |        No         |        2.36           |       5.37
      1          |        DAC        |        Yes        |        8.48           |       43.29
      5          |        DAC        |        Yes        |        8.57           |       43.27
      10         |        DAC        |        Yes        |        8.57           |       43.28

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.35          |       5.98
      5          |        DAC        |        No         |        2.35          |       5.99
      10         |        DAC        |        No         |        2.35          |       5.99
      1          |        DAC        |        Yes        |        9.60          |       46.75
      5          |        DAC        |        Yes        |        9.60          |       46.76
      10         |        DAC        |        Yes        |        9.74          |       46.75

**a53 :**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          0.96  ms
Fast Tuning Window          |          0.54  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.92          |       1.27
      5          |        DAC        |        No         |        2.91          |       1.27
      10         |        DAC        |        No         |        2.91          |       1.27
      1          |        DAC        |        Yes        |        9.10          |       32.13
      5          |        DAC        |        Yes        |        9.21          |       32.13
      10         |        DAC        |        Yes        |        9.23          |       32.14

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.63           |       0.57
      5          |        DAC        |        No         |        1.63           |       0.57
      10         |        DAC        |        No         |        1.63           |       0.57
      1          |        DAC        |        Yes        |        3.90           |       5.76
      5          |        DAC        |        Yes        |        3.93           |       5.76
      10         |        DAC        |        Yes        |        3.93           |       5.76

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.54           |       1.01
      5          |        DAC        |        No         |        2.53           |       1.01
      10         |        DAC        |        No         |        2.53           |       1.01
      1          |        DAC        |        Yes        |        9.05           |       31.23
      5          |        DAC        |        Yes        |        9.18           |       31.19
      10         |        DAC        |        Yes        |        9.17           |       31.19

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.91           |       1.64
      5          |        DAC        |        No         |        2.89           |       1.64
      10         |        DAC        |        No         |        2.89           |       1.64
      1          |        DAC        |        Yes        |        10.18          |       51.33
      5          |        DAC        |        Yes        |        10.21          |       51.33
      10         |        DAC        |        Yes        |        10.26          |       51.33

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.91          |       1.81
      5          |        DAC        |        No         |        2.91          |       1.81
      10         |        DAC        |        No         |        2.91          |       1.81
      1          |        DAC        |        Yes        |        10.42          |       53.57
      5          |        DAC        |        Yes        |        10.55          |       53.59
      10         |        DAC        |        Yes        |        10.53          |       53.59

### GPMC NAND Flash Performance
**r5f0-0:**
 - Flash type: PARALLEL NAND
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 6.55		        | 19.96
 5	           | 6.53		        | 19.96
 10	           | 6.52		        | 19.96

**a53 :**
Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 9.79		        | 22.16
 5	           | 9.71		        | 22.16
 10	           | 9.68		        | 22.16


 ### CPSW Performance

For CPSW performance refer \ref enetlld_performance

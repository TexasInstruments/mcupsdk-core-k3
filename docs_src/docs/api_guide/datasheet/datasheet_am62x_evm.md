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
dhrystone_per_mhz (DMIPS/MHz)   |   2.8721      |  2.8577        |  2.8577      |
dhrystone_per_second            |   7064885.2   |  7029351.2     |  7029351.2   |

### AM62X Interrupt Latency Benchmark performance

The latency measurements include IRQ entry handling latency + ISR + IRQ exit handling latency.

Core : **a530-0**

Benchmarks                      | am62x-sk      | am62x-sk-lp   | am62x-sip-sk   |
--------------------------------|---------------|---------------|----------------|
cpu_clock (MHz)                 |   1400        |  1400         |  1400          |
interrupt latency (ns)          |   628         |  620          |  620           |

### AM62X Coremark Pro Benchmark performance

Workload computed for **Single core**

Core : **a530-0**

Benchmark (worloads)             |  am62xx_lp_sk-fs  |    am62xx_sk-fs    |   am62xxsip_sk-fs    |
---------------------------------|-------------------|--------------------|----------------------|
cjpeg-rose7-preset               | 40.40             | 40.40              | 40.40                |
core                             | 0.29              | 0.28               | 0.29                 |
linear_alg-mid-100x100-sp        | 16.30             | 16.30              | 16.30                |
loops-all-mid-10k-sp             | 0.72              | 0.72               | 0.73                 |
nnet_test                        | 1.88              | 1.88               | 1.88                 |
parser-125k                      | 5.75              | 5.76               | 5.76                 |
radix2-big-64k                   | 76.72             | 78.25              | 77.84                |
sha-test                         | 81.73             | 81.74              | 81.75                |
zip-test                         | 27.17             | 27.32              | 27.26                |
Coremark-pro()(overall score)    | 987.65            | 986.78             | 991.34               |

### AM62X-SK SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 192 KB
- Size of images loaded by stage2  : 1206 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.520
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.211
SBL Stage1: Board_driversOpen           |    7.262
SBL Stage1: Sciclient Get Version       |    6.636
SBL Stage1: App_waitForMcuPbist         |    6.325
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.304
SBL Stage1: App_loadSelfcoreImage       |    4.701
----------------------------------------|--------------
SBL Stage1: Total time taken            |   42.652

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.707
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.259
SBL Stage2: Board_driversOpen           |    0.535
SBL Stage2: Sciclient Get Version       |    6.678
SBL Stage2: App_loadImages              |    3.485
SBL Stage2: App_loadSelfcoreImage       |    5.321
SBL Stage2: App_loadLinuxImages         |   13.309
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.299

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK SBL OSPI performance (HS-SE)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 192 KB
- Size of images loaded by stage2  : 1206 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.660
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.211
SBL Stage1: Board_driversOpen           |    7.297
SBL Stage1: Sciclient Get Version       |    6.636
SBL Stage1: App_waitForMcuPbist         |    6.279
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.307
SBL Stage1: App_loadSelfcoreImage       |    4.699
----------------------------------------|--------------
SBL Stage1: Total time taken            |   42.782

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.708
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.258
SBL Stage2: Board_driversOpen           |    0.537
SBL Stage2: Sciclient Get Version       |    6.677
SBL Stage2: App_loadImages              |    3.484
SBL Stage2: App_loadSelfcoreImage       |    5.320
SBL Stage2: App_loadLinuxImages         |   13.304
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.292

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
SBL Stage1: System_init                 |   23.818
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.209
SBL Stage1: Board_driversOpen           |    7.354
SBL Stage1: Sciclient Get Version       |    6.635
SBL Stage1: App_waitForMcuPbist         |    0.105
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.274
SBL Stage1: App_loadSelfcoreImage       |    4.717
----------------------------------------|--------------
SBL Stage1: Total time taken            |   54.806

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.721
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.263
SBL Stage2: Board_driversOpen           |    0.534
SBL Stage2: Sciclient Get Version       |    6.681
SBL Stage2: App_loadImages              |    3.487
SBL Stage2: App_loadSelfcoreImage       |    5.325
SBL Stage2: App_loadLinuxImages         |   13.648
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.663

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK LP SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 191 KB
- Size of images loaded by stage2  : 1245 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   20.916
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.216
SBL Stage1: Board_driversOpen           |   32.568
SBL Stage1: Sciclient Get Version       |    6.637
SBL Stage1: App_waitForMcuPbist         |    0.109
SBL Stage1: App_waitForMcuLbist         |    7.688
SBL Stage1: App_loadImages              |    4.123
SBL Stage1: App_loadSelfcoreImage       |    6.562
----------------------------------------|--------------
SBL Stage1: Total time taken            |   78.823

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.747
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.264
SBL Stage2: Board_driversOpen           |   31.047
SBL Stage2: Sciclient Get Version       |    6.667
SBL Stage2: App_loadImages              |    2.344
SBL Stage2: App_loadSelfcoreImage       |    8.184
SBL Stage2: App_loadLinuxImages         |   36.645
----------------------------------------|--------------
SBL Stage2: Total time taken            |   87.902

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~21 ms taken for System Init is mostly attributed to DDR initialization.

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
SBL Stage1: System_init                 |   21.048
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.214
SBL Stage1: Board_driversOpen           |   32.561
SBL Stage1: Sciclient Get Version       |    6.637
SBL Stage1: App_waitForMcuPbist         |    0.108
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.127
SBL Stage1: App_loadSelfcoreImage       |    6.567
----------------------------------------|--------------
SBL Stage1: Total time taken            |   78.955

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.745
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.261
SBL Stage2: Board_driversOpen           |   31.034
SBL Stage2: Sciclient Get Version       |    6.674
SBL Stage2: App_loadImages              |    2.355
SBL Stage2: App_loadSelfcoreImage       |    8.213
SBL Stage2: App_loadLinuxImages         |   36.964
----------------------------------------|--------------
SBL Stage2: Total time taken            |   88.251

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~21 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 186 KB
- Size of images loaded by stage2  : 1206 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.498
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   93.093
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.635
SBL Stage1: App_loadImages              |    8.762
SBL Stage1: App_loadSelfcoreImage       |   10.002
----------------------------------------|--------------
SBL Stage1: Total time taken            |   123.993

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.714
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.630
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    6.657
SBL Stage2: App_loadImages              |    6.744
SBL Stage2: App_loadSelfcoreImage       |    9.998
SBL Stage2: App_loadLinuxImages         |   22.582
----------------------------------------|--------------
SBL Stage2: Total time taken            |   70.330

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
SBL Stage1: System_init                 |    5.678
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   51.014
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.635
SBL Stage1: App_loadImages              |    8.630
SBL Stage1: App_loadSelfcoreImage       |   10.089
----------------------------------------|--------------
SBL Stage1: Total time taken            |   82.039

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.713
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.594
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    6.672
SBL Stage2: App_loadImages              |    6.436
SBL Stage2: App_loadSelfcoreImage       |    9.590
SBL Stage2: App_loadLinuxImages         |   22.208
----------------------------------------|--------------
SBL Stage2: Total time taken            |   69.217

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
SBL Stage1: System_init                 |   23.866
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   21.694
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.634
SBL Stage1: App_loadImages              |    7.788
SBL Stage1: App_loadSelfcoreImage       |    8.308
----------------------------------------|--------------
SBL Stage1: Total time taken            |   68.292

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.736
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.685
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    6.650
SBL Stage2: App_loadImages              |    6.113
SBL Stage2: App_loadSelfcoreImage       |    8.633
SBL Stage2: App_loadLinuxImages         |   21.934
----------------------------------------|--------------
SBL Stage2: Total time taken            |   67.755

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
SBL Stage1: System_init                 |   20.761
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   36.496
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.635
SBL Stage1: App_loadImages              |    7.143
SBL Stage1: App_loadSelfcoreImage       |    7.922
----------------------------------------|--------------
SBL Stage1: Total time taken            |   78.959

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.769
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   21.652
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |    6.649
SBL Stage2: App_loadImages              |    6.574
SBL Stage2: App_loadSelfcoreImage       |    9.012
SBL Stage2: App_loadLinuxImages         |   23.230
----------------------------------------|--------------
SBL Stage2: Total time taken            |   69.890

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
SBL Stage1: System_init                 |   21.059
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   51.604
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.636
SBL Stage1: App_loadImages              |    7.055
SBL Stage1: App_loadSelfcoreImage       |    7.878
----------------------------------------|--------------
SBL Stage1: Total time taken            |   94.235

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.757
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.600
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    6.649
SBL Stage2: App_loadImages              |    5.622
SBL Stage2: App_loadSelfcoreImage       |    8.922
SBL Stage2: App_loadLinuxImages         |   23.129
----------------------------------------|--------------
SBL Stage2: Total time taken            |   68.683

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.


### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0	    | m4f0-0	  |  1.89
 r5f0-0	    | a530-0	  |  1.76
 r5f0-0	    | a530-1	  |  2.07

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
      r5f0-0|       m4f0-0|             4|                        23.849|                25|         1000
      r5f0-0|       a530-0|             4|                        11.649|                13|         1000
      r5f0-0|       a530-1|             4|                        13.077|                14|         1000
      r5f0-0|       m4f0-0|            32|                        32.607|                33|         1000
      r5f0-0|       m4f0-0|            64|                        42.638|                43|         1000
      r5f0-0|       m4f0-0|           112|                        57.508|                58|         1000
      r5f0-0|       a530-0|            32|                        15.464|                16|         1000
      r5f0-0|       a530-0|            64|                        19.786|                21|         1000
      r5f0-0|       a530-0|           112|                        26.410|                28|         1000
      r5f0-0|       a530-1|            32|                        16.803|                18|         1000
      r5f0-0|       a530-1|            64|                        20.880|                22|         1000
      r5f0-0|       a530-1|           112|                        27.294|                28|         1000

### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 36.05		         | 44.15
 SDR50 | 4	            | 41.26		         | 43.82
 SDR50 | 6	            | 41.59		         | 43.90
 SDR50 | 32	            | 41.39		         | 44.38
 SDR50 | 40	            | 41.17		         | 44.42
 DDR50 | 1	            | 49.45		         | 79.01
 DDR50 | 4	            | 59.25		         | 77.97
 DDR50 | 6	            | 52.10		         | 78.26
 DDR50 | 32	            | 56.15		         | 79.80
 DDR50 | 40	            | 56.50		         | 79.92
 HS200 | 1	            | 50.04		         | 151.62
 HS200 | 4	            | 57.00		         | 147.74
 HS200 | 6	            | 54.85		         | 148.73
 HS200 | 32	            | 56.29		         | 154.33
 HS200 | 40	            | 56.85		         | 154.81
**a53 :**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 37.34              | 46.14
 SDR50 | 4	            | 42.85              | 45.75
 SDR50 | 6	            | 42.32              | 45.62
 SDR50 | 32	            | 43.29              | 46.34
 SDR50 | 40	            | 43.18              | 46.48
 DDR50 | 1	            | 48.85              | 85.66
 DDR50 | 4	            | 57.88              | 84.32
 DDR50 | 6	            | 55.12              | 83.89
 DDR50 | 32	            | 57.84              | 86.36
 DDR50 | 40	            | 57.96              | 86.56
 HS200 | 1	            | 52.15              | 178.18
 HS200 | 4	            | 55.17              | 172.29
 HS200 | 6	            | 59.22              | 170.52
 HS200 | 32	            | 57.74              | 181.18
 HS200 | 40	            | 57.62              | 181.85

### OSPI NOR Flash Performance  {#OSPI_DATA_SHEET}
**r5f0-0:**

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 54.99

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.53  ms
Fast Tuning Window          |          0.55  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          9.95 ms
Fast Tuning Window          |          6.67 ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.44          |       2.86
      5          |        DAC        |        No         |        0.44          |       2.86
      10         |        DAC        |        No         |        0.44          |       2.86
      1          |        DAC        |        Yes        |        0.44          |       47.53
      5          |        DAC        |        Yes        |        0.44          |       47.57
      10         |        DAC        |        Yes        |        0.44          |       47.58

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       6.14
      5          |        DAC        |        No         |        0.42           |       6.14
      10         |        DAC        |        No         |        0.42           |       6.14
      1          |        DAC        |        Yes        |        0.42           |       6.21
      5          |        DAC        |        Yes        |        0.42           |       6.21
      10         |        DAC        |        Yes        |        0.42           |       6.21

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       4.07
      5          |        DAC        |        No         |        0.43           |       4.07
      10         |        DAC        |        No         |        0.43           |       4.07
      1          |        DAC        |        Yes        |        0.42           |       47.53
      5          |        DAC        |        Yes        |        0.43           |       47.57
      10         |        DAC        |        Yes        |        0.43           |       47.58

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       5.99
      5          |        DAC        |        No         |        0.43           |       5.99
      10         |        DAC        |        No         |        0.43           |       5.99
      1          |        DAC        |        Yes        |        0.42           |       117.05
      5          |        DAC        |        Yes        |        0.43           |       117.35
      10         |        DAC        |        Yes        |        0.43           |       117.39

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       6.33
      5          |        DAC        |        No         |        0.44           |       6.33
      10         |        DAC        |        No         |        0.44           |       6.33
      1          |        DAC        |        Yes        |        0.44           |       208.68
      5          |        DAC        |        Yes        |        0.44           |       209.58
      10         |        DAC        |        Yes        |        0.44           |       209.70

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       6.71
      5          |        DAC        |        No         |        0.43           |       6.71
      10         |        DAC        |        No         |        0.43           |       6.71
      1          |        DAC        |        Yes        |        0.42           |       141.98
      5          |        DAC        |        Yes        |        0.43           |       142.42
      10         |        DAC        |        Yes        |        0.43           |       142.47

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.43          |       7.08
      5          |        DAC        |        No         |        0.43          |       7.08
      10         |        DAC        |        No         |        0.43          |       7.08
      1          |        DAC        |        Yes        |        0.43          |       247.39
      5          |        DAC        |        Yes        |        0.43          |       248.67
      10         |        DAC        |        Yes        |        0.43          |       248.83

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.43          |       13.75
      5          |       INDAC       |        No         |        0.43          |       13.75
      10         |       INDAC       |        No         |        0.43          |       13.75

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.41          |       6.25
      5          |       INDAC       |        No         |        0.40          |       6.25
      10         |       INDAC       |        No         |        0.41          |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.43           |       13.76
      5          |       INDAC       |        No         |        0.44           |       13.75
      10         |       INDAC       |        No         |        0.43           |       13.75

**a53 :**

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 56.14

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.08  ms
Fast Tuning Window          |          0.45  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          8.57 ms
Fast Tuning Window          |          5.73 ms

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
      5          |        DAC        |        No         |        0.42           |       0.54
      10         |        DAC        |        No         |        0.42           |       0.54
      1          |        DAC        |        Yes        |        0.41           |       6.25
      5          |        DAC        |        Yes        |        0.42           |       6.25
      10         |        DAC        |        Yes        |        0.42           |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       1.11
      5          |        DAC        |        No         |        0.43           |       1.11
      10         |        DAC        |        No         |        0.44           |       1.11
      1          |        DAC        |        Yes        |        0.42           |       49.83
      5          |        DAC        |        Yes        |        0.43           |       49.86
      10         |        DAC        |        Yes        |        0.43           |       49.86

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       1.72
      5          |        DAC        |        No         |        0.42           |       1.72
      10         |        DAC        |        No         |        0.43           |       1.72
      1          |        DAC        |        Yes        |        0.42           |       132.09
      5          |        DAC        |        Yes        |        0.42           |       132.30
      10         |        DAC        |        Yes        |        0.43           |       132.33

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       1.85
      5          |        DAC        |        No         |        0.44           |       1.85
      10         |        DAC        |        No         |        0.44           |       1.85
      1          |        DAC        |        Yes        |        0.43           |       261.74
      5          |        DAC        |        Yes        |        0.44           |       262.55
      10         |        DAC        |        Yes        |        0.44           |       262.65

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       1.96
      5          |        DAC        |        No         |        0.43           |       1.96
      10         |        DAC        |        No         |        0.43           |       1.96
      1          |        DAC        |        Yes        |        0.42           |       164.74
      5          |        DAC        |        Yes        |        0.43           |       165.05
      10         |        DAC        |        Yes        |        0.43           |       165.09

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.43          |       2.08
      5          |        DAC        |        No         |        0.44          |       2.08
      10         |        DAC        |        No         |        0.44          |       2.08
      1          |        DAC        |        Yes        |        0.43          |       325.69
      5          |        DAC        |        Yes        |        0.44          |       326.91
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
      5          |       INDAC       |        No         |        0.42          |       6.25
      10         |       INDAC       |        No         |        0.42          |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.42           |       19.63
      5          |       INDAC       |        No         |        0.43           |       19.63
      10         |       INDAC       |        No         |        0.43           |       19.63

### OSPI NAND Flash Performance
**r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          1.10  ms
Fast Tuning Window          |          0.61  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.43          |       4.42
      5          |        DAC        |        No         |        2.41          |       4.39
      10         |        DAC        |        No         |        2.41          |       4.39
      1          |        DAC        |        Yes        |        9.49          |       29.47
      5          |        DAC        |        Yes        |        9.40          |       29.51
      10         |        DAC        |        Yes        |        9.39          |       29.51

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.57           |       5.51
      5          |        DAC        |        No         |        1.57           |       5.51
      10         |        DAC        |        No         |        1.57           |       5.51
      1          |        DAC        |        Yes        |        4.04           |       5.70
      5          |        DAC        |        Yes        |        4.02           |       5.70
      10         |        DAC        |        Yes        |        4.00           |       5.70

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.42           |       3.59
      5          |        DAC        |        No         |        2.42           |       3.59
      10         |        DAC        |        No         |        2.41           |       3.59
      1          |        DAC        |        Yes        |        9.51           |       28.36
      5          |        DAC        |        Yes        |        9.40           |       28.26
      10         |        DAC        |        Yes        |        9.30           |       28.36

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.42           |       5.37
      5          |        DAC        |        No         |        2.41           |       5.37
      10         |        DAC        |        No         |        2.40           |       5.37
      1          |        DAC        |        Yes        |        10.59          |       41.14
      5          |        DAC        |        Yes        |        10.49          |       41.19
      10         |        DAC        |        Yes        |        10.48          |       41.20

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.42          |       5.93
      5          |        DAC        |        No         |        2.41          |       5.93
      10         |        DAC        |        No         |        2.40          |       5.93
      1          |        DAC        |        Yes        |        10.85         |       43.88
      5          |        DAC        |        Yes        |        10.73         |       43.99
      10         |        DAC        |        Yes        |        10.71         |       44.00

**a53 :**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)    
----------------------------|------------------------
Default Tuning Window       |          0.94  ms
Fast Tuning Window          |          0.52  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        3.01          |       1.27
      5          |        DAC        |        No         |        3.00          |       1.27
      10         |        DAC        |        No         |        2.99          |       1.27
      1          |        DAC        |        Yes        |        10.09         |       31.50
      5          |        DAC        |        Yes        |        10.09         |       31.50
      10         |        DAC        |        Yes        |        10.00         |       31.50

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.65           |       0.57
      5          |        DAC        |        No         |        1.65           |       0.57
      10         |        DAC        |        No         |        1.65           |       0.57
      1          |        DAC        |        Yes        |        4.10           |       5.74
      5          |        DAC        |        Yes        |        4.07           |       5.74
      10         |        DAC        |        Yes        |        4.06           |       5.74

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.59           |       1.01
      5          |        DAC        |        No         |        2.58           |       1.01
      10         |        DAC        |        No         |        2.58           |       1.01
      1          |        DAC        |        Yes        |        10.13          |       30.46
      5          |        DAC        |        Yes        |        10.01          |       30.46
      10         |        DAC        |        Yes        |        10.00          |       30.46

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)  
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        3.00           |       1.64
      5          |        DAC        |        No         |        2.98           |       1.64
      10         |        DAC        |        No         |        2.97           |       1.64
      1          |        DAC        |        Yes        |        11.47          |       50.07
      5          |        DAC        |        Yes        |        11.33          |       50.08
      10         |        DAC        |        Yes        |        11.30          |       50.08

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)  
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        3.02          |       1.81
      5          |        DAC        |        No         |        2.99          |       1.81
      10         |        DAC        |        No         |        2.98          |       1.81
      1          |        DAC        |        Yes        |        11.82         |       51.69
      5          |        DAC        |        Yes        |        11.65         |       51.68
      10         |        DAC        |        Yes        |        11.67         |       51.68

### GPMC NAND Flash Performance
**r5f0-0:**
 - Flash type: PARALLEL NAND
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 6.61		        | 19.87
 5	           | 6.56		        | 19.92
 10	           | 6.52		        | 19.92

**a53 :**
Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 9.94		        | 22.10
 5	           | 9.83		        | 22.11
 10	           | 9.74		        | 22.11


 ### CPSW Performance

For CPSW performance refer \ref enetlld_performance

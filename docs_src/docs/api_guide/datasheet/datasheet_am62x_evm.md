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
cjpeg-rose7-preset               | 40.40             | 40.40              | 40.40                |
core                             | 0.28              | 0.28               | 0.28                 |
linear_alg-mid-100x100-sp        | 16.30             | 16.30              | 16.30                |
loops-all-mid-10k-sp             | 0.71              | 0.72               | 0.73                 |
nnet_test                        | 1.87              | 1.88               | 1.88                 |
parser-125k                      | 5.75              | 5.76               | 5.76                 |
radix2-big-64k                   | 77.54             | 78.46              | 78.02                |
sha-test                         | 81.72             | 81.73              | 81.75                |
zip-test                         | 27.13             | 27.32              | 27.28                |
Coremark-pro()(overall score)    | 982.68            | 984.90             | 984.74               |

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
SBL Stage1: System_init                 |    5.516
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.211
SBL Stage1: Board_driversOpen           |    1.267
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_waitForMcuPbist         |    8.753
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.617
SBL Stage1: App_loadSelfcoreImage       |    4.041
----------------------------------------|--------------
SBL Stage1: Total time taken            |   41.300

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.789
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.271
SBL Stage2: Board_driversOpen           |    0.154
SBL Stage2: Sciclient Get Version       |   10.226
SBL Stage2: App_loadImages              |    2.814
SBL Stage2: App_loadSelfcoreImage       |    4.605
SBL Stage2: App_loadLinuxImages         |   11.177
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.039

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
SBL Stage1: System_init                 |    5.605
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.210
SBL Stage1: Board_driversOpen           |    1.265
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_waitForMcuPbist         |    8.748
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.699
SBL Stage1: App_loadSelfcoreImage       |    4.130
----------------------------------------|--------------
SBL Stage1: Total time taken            |   41.554

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.789
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.269
SBL Stage2: Board_driversOpen           |    0.152
SBL Stage2: Sciclient Get Version       |   10.254
SBL Stage2: App_loadImages              |    2.899
SBL Stage2: App_loadSelfcoreImage       |    4.695
SBL Stage2: App_loadLinuxImages         |   11.285
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.347

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
SBL Stage1: System_init                 |   23.941
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.209
SBL Stage1: Board_driversOpen           |    1.259
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_waitForMcuPbist         |    0.105
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.598
SBL Stage1: App_loadSelfcoreImage       |    4.062
----------------------------------------|--------------
SBL Stage1: Total time taken            |   51.067

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.791
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.269
SBL Stage2: Board_driversOpen           |    0.153
SBL Stage2: Sciclient Get Version       |   10.251
SBL Stage2: App_loadImages              |    2.813
SBL Stage2: App_loadSelfcoreImage       |    4.587
SBL Stage2: App_loadLinuxImages         |   11.433
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.301

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
SBL Stage1: System_init                 |   23.273
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.209
SBL Stage1: Board_driversOpen           |   26.422
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_waitForMcuPbist         |    0.103
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.896
SBL Stage1: App_loadSelfcoreImage       |    6.196
----------------------------------------|--------------
SBL Stage1: Total time taken            |   77.991

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.810
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.270
SBL Stage2: Board_driversOpen           |   30.187
SBL Stage2: Sciclient Get Version       |   10.259
SBL Stage2: App_loadImages              |    2.337
SBL Stage2: App_loadSelfcoreImage       |    7.610
SBL Stage2: App_loadLinuxImages         |   31.081
----------------------------------------|--------------
SBL Stage2: Total time taken            |   84.450

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
SBL Stage1: System_init                 |   23.398
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.210
SBL Stage1: Board_driversOpen           |   26.415
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_waitForMcuPbist         |    0.107
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.981
SBL Stage1: App_loadSelfcoreImage       |    6.287
----------------------------------------|--------------
SBL Stage1: Total time taken            |   78.294

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.811
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.270
SBL Stage2: Board_driversOpen           |   30.157
SBL Stage2: Sciclient Get Version       |   10.240
SBL Stage2: App_loadImages              |    2.303
SBL Stage2: App_loadSelfcoreImage       |    7.692
SBL Stage2: App_loadLinuxImages         |   31.127
----------------------------------------|--------------
SBL Stage2: Total time taken            |   84.604

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
SBL Stage1: System_init                 |    5.700
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   49.570
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.206
SBL Stage1: App_loadImages              |    6.659
SBL Stage1: App_loadSelfcoreImage       |    7.328
----------------------------------------|--------------
SBL Stage1: Total time taken            |   79.466

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.755
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.829
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.242
SBL Stage2: App_loadImages              |    5.401
SBL Stage2: App_loadSelfcoreImage       |    8.141
SBL Stage2: App_loadLinuxImages         |   19.291
----------------------------------------|--------------
SBL Stage2: Total time taken            |   66.663

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
SBL Stage1: System_init                 |    5.862
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   52.278
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.206
SBL Stage1: App_loadImages              |    6.939
SBL Stage1: App_loadSelfcoreImage       |    7.604
----------------------------------------|--------------
SBL Stage1: Total time taken            |   82.893

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.770
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.843
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.251
SBL Stage2: App_loadImages              |    5.728
SBL Stage2: App_loadSelfcoreImage       |   13.388
SBL Stage2: App_loadLinuxImages         |   19.254
----------------------------------------|--------------
SBL Stage2: Total time taken            |   72.238

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
SBL Stage1: System_init                 |   23.678
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   20.719
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.204
SBL Stage1: App_loadImages              |    7.501
SBL Stage1: App_loadSelfcoreImage       |    8.125
----------------------------------------|--------------
SBL Stage1: Total time taken            |   70.329

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.753
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.681
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.229
SBL Stage2: App_loadImages              |    5.599
SBL Stage2: App_loadSelfcoreImage       |    8.268
SBL Stage2: App_loadLinuxImages         |   19.045
----------------------------------------|--------------
SBL Stage2: Total time taken            |   66.580

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
SBL Stage1: System_init                 |   23.209
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   37.764
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.205
SBL Stage1: App_loadImages              |    6.589
SBL Stage1: App_loadSelfcoreImage       |    7.328
----------------------------------------|--------------
SBL Stage1: Total time taken            |   85.099

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.793
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   20.833
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.226
SBL Stage2: App_loadImages              |    5.451
SBL Stage2: App_loadSelfcoreImage       |    8.229
SBL Stage2: App_loadLinuxImages         |   20.556
----------------------------------------|--------------
SBL Stage2: Total time taken            |   68.093

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
SBL Stage1: System_init                 |   23.266
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   53.477
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_loadImages              |    6.970
SBL Stage1: App_loadSelfcoreImage       |    7.686
----------------------------------------|--------------
SBL Stage1: Total time taken            |  101.604

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.796
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.836
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.259
SBL Stage2: App_loadImages              |    5.765
SBL Stage2: App_loadSelfcoreImage       |    8.521
SBL Stage2: App_loadLinuxImages         |   20.874
----------------------------------------|--------------
SBL Stage2: Total time taken            |   69.055

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
      r5f0-0|       m4f0-0|             4|                        23.990|                25|         1000
      r5f0-0|       m4f0-0|            32|                        32.659|                33|         1000
      r5f0-0|       m4f0-0|            64|                        42.544|                43|         1000
      r5f0-0|       m4f0-0|           112|                        57.508|                58|         1000
      r5f0-0|       a530-0|             4|                        11.955|                14|         1000
      r5f0-0|       a530-0|            32|                        15.515|                16|         1000
      r5f0-0|       a530-0|            64|                        20.197|                21|         1000
      r5f0-0|       a530-0|           112|                        26.807|                28|         1000
      r5f0-0|       a530-1|             4|                        13.303|                14|         1000
      r5f0-0|       a530-1|            32|                        16.900|                19|         1000
      r5f0-0|       a530-1|            64|                        21.096|                22|         1000
      r5f0-0|       a530-1|           112|                        27.337|                28|         1000

### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 30.68		         | 44.12
 SDR50 | 4	            | 41.53		         | 43.50
 SDR50 | 6	            | 41.74		         | 43.89
 SDR50 | 32	            | 41.60		         | 44.37
 SDR50 | 40	            | 41.29		         | 44.49
 DDR50 | 1	            | 48.98		         | 79.03
 DDR50 | 4	            | 58.45	             | 76.98
 DDR50 | 6	            | 54.01		         | 78.21
 DDR50 | 32	            | 58.04	             | 79.77
 DDR50 | 40	            | 57.13		         | 80.14
 HS200 | 1	            | 53.36		         | 151.63
 HS200 | 4	            | 60.69		         | 144.16
 HS200 | 6	            | 55.85		         | 148.86
 HS200 | 32	            | 58.25		         | 154.30
 HS200 | 40	            | 58.05		         | 155.73
**a53 :**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 38.14		         | 46.15
 SDR50 | 4	            | 38.77		         | 45.40
 SDR50 | 6	            | 43.52		         | 45.81
 SDR50 | 32	            | 43.34		         | 46.38
 SDR50 | 40	            | 43.14		         | 46.48
 DDR50 | 1	            | 39.09		         | 85.65
 DDR50 | 4	            | 62.81	             | 83.16
 DDR50 | 6	            | 61.26		         | 84.85
 DDR50 | 32	            | 61.29	             | 86.60
 DDR50 | 40	            | 60.30		         | 86.83
 HS200 | 1	            | 57.01		         | 178.30
 HS200 | 4	            | 64.38		         | 167.48
 HS200 | 6	            | 64.71 	         | 173.12
 HS200 | 32	            | 61.78		         | 183.68
 HS200 | 40	            | 61.03		         | 183.08

### OSPI NOR Flash Performance
**r5f0-0:**

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          3.59 ms
Fast Tuning Window          |          1.15 ms


 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.42          |       2.87
      5          |        No         |        0.42          |       2.87
      10         |        No         |        0.42          |       2.87
      1          |        Yes        |        0.42          |       47.53
      5          |        Yes        |        0.42          |       47.57
      10         |        Yes        |        0.42          |       47.58


 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.40          |       6.14
      5          |        No         |        0.40          |       6.14
      10         |        No         |        0.40          |       6.14
      1          |        Yes        |        0.40          |       6.21
      5          |        Yes        |        0.40          |       6.21
      10         |        Yes        |        0.40          |       6.21


 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.42          |       6.33
      5          |        No         |        0.42          |       6.33
      10         |        No         |        0.42          |       6.33
      1          |        Yes        |        0.42          |       208.66
      5          |        Yes        |        0.42          |       209.57
      10         |        Yes        |        0.42          |       209.69


 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.42          |       7.08
      5          |        No         |        0.42          |       7.08
      10         |        No         |        0.42          |       7.08
      1          |        Yes        |        0.42          |       247.39
      5          |        Yes        |        0.42          |       248.65
      10         |        Yes        |        0.42          |       248.82

**a53 :**

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          2.98 ms
Fast Tuning Window          |          0.97 ms

Flash frequency: 25Mhz
Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.44          |       0.76
      5          |        No         |        0.44          |       0.76
      10         |        No         |        0.44          |       0.76
      1          |        Yes        |        0.44          |       49.83
      5          |        Yes        |        0.44          |       49.86
      10         |        Yes        |        0.43          |       49.86

Flash frequency: 50Mhz
Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.41          |       0.54
      5          |        No         |        0.41          |       0.54
      10         |        No         |        0.41          |       0.54
      1          |        Yes        |        0.41          |       6.25
      5          |        Yes        |        0.41          |       6.25
      10         |        Yes        |        0.41          |       6.25

Flash frequency: 133Mhz
Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.44          |       1.85
      5          |        No         |        0.44          |       1.85
      10         |        No         |        0.44          |       1.85
      1          |        Yes        |        0.44          |       261.77
      5          |        Yes        |        0.44          |       262.55
      10         |        Yes        |        0.44          |       262.65


Flash frequency: 166Mhz
Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.44          |       2.08
      5          |        No         |        0.44          |       2.08
      10         |        No         |        0.44          |       2.08
      1          |        Yes        |        0.44          |       325.73
      5          |        Yes        |        0.44          |       326.92
      10         |        Yes        |        0.44          |       327.08


### OSPI NAND Flash Performance
**r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.12  ms
Fast Tuning Window          |          0.62  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.42          |       4.41
      5          |        No         |        2.42          |       4.41
      10         |        No         |        2.42          |       4.41
      1          |        Yes        |        2.42          |       28.67
      5          |        Yes        |        2.42          |       28.67
      10         |        Yes        |        2.42          |       28.67


 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        1.58          |       5.53
      5          |        No         |        1.58          |       5.53
      10         |        No         |        1.57          |       5.53
      1          |        Yes        |        1.57          |       5.73
      5          |        Yes        |        1.58          |       5.73
      10         |        Yes        |        1.58          |       5.73


 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.43          |       3.60
      5          |        No         |        2.42          |       3.60
      10         |        No         |        2.42          |       3.60
      1          |        Yes        |        2.42          |       29.22
      5          |        Yes        |        2.42          |       29.22
      10         |        Yes        |        2.43          |       29.22


 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.08          |       5.40
      5          |        No         |        2.08          |       5.41
      10         |        No         |        2.08          |       5.41
      1          |        Yes        |        2.08          |       43.26
      5          |        Yes        |        2.08          |       43.26
      10         |        Yes        |        2.08          |       43.27


 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.09          |       5.97
      5          |        No         |        2.09          |       5.97
      10         |        No         |        2.09          |       5.97
      1          |        Yes        |        2.09          |       46.70
      5          |        Yes        |        2.09          |       46.71
      10         |        Yes        |        2.09          |       46.70

**a53 :**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          0.96  ms
Fast Tuning Window          |          0.53  ms

Flash frequency: 25Mhz
Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        3.05          |       1.27
      5          |        No         |        3.04          |       1.27
      10         |        No         |        3.04          |       1.27
      1          |        Yes        |        3.04          |       32.19
      5          |        Yes        |        3.04          |       32.19
      10         |        Yes        |        3.05          |       32.19


 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        1.67          |       0.58
      5          |        No         |        1.67          |       0.58
      10         |        No         |        1.67          |       0.58
      1          |        Yes        |        1.66          |       5.80
      5          |        Yes        |        1.67          |       5.80
      10         |        Yes        |        1.67          |       5.80


 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.63          |       1.01
      5          |        No         |        2.63          |       1.01
      10         |        No         |        2.63          |       1.01
      1          |        Yes        |        2.62          |       32.32
      5          |        Yes        |        2.63          |       32.33
      10         |        Yes        |        2.63          |       32.32


 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.28          |       1.64
      5          |        No         |        2.27          |       1.64
      10         |        No         |        2.27          |       1.64
      1          |        Yes        |        2.27          |       51.33
      5          |        Yes        |        2.27          |       51.33
      10         |        Yes        |        2.28          |       51.34


 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        2.63          |       1.82
      5          |        No         |        2.62          |       1.82
      10         |        No         |        2.62          |       1.82
      1          |        Yes        |        2.62          |       57.13
      5          |        Yes        |        2.62          |       57.14
      10         |        Yes        |        2.62          |       57.15

### GPMC NAND Flash Performance
**r5f0-0:**
 - Flash type: PARALLEL NAND
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 6.50		        | 19.93
 5	           | 6.51		        | 19.93
 10	           | 6.51		        | 19.93

**a53 :**
Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 9.67		        | 22.11
 5	           | 9.64		        | 22.11
 10	           | 9.64		        | 22.11


 ### CPSW Performance

For CPSW performance refer \ref enetlld_performance

# Datasheet

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for {{ VAR_SOC_NAME }}


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
dhrystone_per_second            |   7029371.0   |  7029327.6     |  7029351.2   |

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
cjpeg-rose7-preset               | 40.39             | 40.39              | 40.39                |
core                             | 0.28              | 0.28               | 0.28                 |
linear_alg-mid-100x100-sp        | 16.30             | 16.30              | 16.29                |
loops-all-mid-10k-sp             | 0.72              | 0.72               | 0.72                 |
nnet_test                        | 1.88              | 1.88               | 1.88                 |
parser-125k                      | 5.75              | 5.74               | 5.75                 |
radix2-big-64k                   | 78.29             | 76.78              | 77.86                |
sha-test                         | 81.76             | 81.75              | 81.77                |
zip-test                         | 27.30             | 27.15              | 27.24                |
Coremark-pro()(overall score)    | 986.56            | 986.62             | 985.66               |

### AM62X-SK SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 198 KB
- Size of images loaded by stage2  : 1195 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.922
SBL Stage1: Board_init                  |    0.095
SBL Stage1: Drivers_open                |    0.217
SBL Stage1: Board_driversOpen           |    7.231
SBL Stage1: Sciclient Get Version       |    6.728
SBL Stage1: App_waitForMcuPbist         |    5.792
SBL Stage1: App_waitForMcuLbist         |    7.697
SBL Stage1: App_loadImages              |    7.205
SBL Stage1: App_loadSelfcoreImage       |    4.728
----------------------------------------|--------------
SBL Stage1: Total time taken            |   45.615

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.752
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.272
SBL Stage2: Board_driversOpen           |    0.539
SBL Stage2: Sciclient Get Version       |    6.771
SBL Stage2: App_loadImages              |    3.501
SBL Stage2: App_loadSelfcoreImage       |    5.297
SBL Stage2: App_loadLinuxImages         |   13.862
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.995

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK SBL OSPI performance (HS-SE)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 198 KB
- Size of images loaded by stage2  : 1195 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    6.075
SBL Stage1: Board_init                  |    0.095
SBL Stage1: Drivers_open                |    0.218
SBL Stage1: Board_driversOpen           |    7.384
SBL Stage1: Sciclient Get Version       |    6.729
SBL Stage1: App_waitForMcuPbist         |    5.364
SBL Stage1: App_waitForMcuLbist         |    7.697
SBL Stage1: App_loadImages              |    7.218
SBL Stage1: App_loadSelfcoreImage       |    4.746
----------------------------------------|--------------
SBL Stage1: Total time taken            |   45.796

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.754
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.274
SBL Stage2: Board_driversOpen           |    0.538
SBL Stage2: Sciclient Get Version       |    6.761
SBL Stage2: App_loadImages              |    3.513
SBL Stage2: App_loadSelfcoreImage       |    5.310
SBL Stage2: App_loadLinuxImages         |   13.893
----------------------------------------|--------------
SBL Stage2: Total time taken            |   33.042

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK-SIP SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 198 KB
- Size of images loaded by stage2  : 1194 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   18.731
SBL Stage1: Board_init                  |    0.095
SBL Stage1: Drivers_open                |    0.216
SBL Stage1: Board_driversOpen           |    7.153
SBL Stage1: Sciclient Get Version       |    6.728
SBL Stage1: App_waitForMcuPbist         |    0.113
SBL Stage1: App_waitForMcuLbist         |    7.697
SBL Stage1: App_loadImages              |    7.169
SBL Stage1: App_loadSelfcoreImage       |    4.782
----------------------------------------|--------------
SBL Stage1: Total time taken            |   52.676

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.748
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.271
SBL Stage2: Board_driversOpen           |    0.538
SBL Stage2: Sciclient Get Version       |    6.757
SBL Stage2: App_loadImages              |    3.500
SBL Stage2: App_loadSelfcoreImage       |    5.316
SBL Stage2: App_loadLinuxImages         |   14.105
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.236

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK LP SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 193 KB
- Size of images loaded by stage2  : 1233 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   15.849
SBL Stage1: Board_init                  |    0.095
SBL Stage1: Drivers_open                |    0.216
SBL Stage1: Board_driversOpen           |   32.823
SBL Stage1: Sciclient Get Version       |    6.728
SBL Stage1: App_waitForMcuPbist         |    0.114
SBL Stage1: App_waitForMcuLbist         |    7.697
SBL Stage1: App_loadImages              |    7.046
SBL Stage1: App_loadSelfcoreImage       |    6.603
----------------------------------------|--------------
SBL Stage1: Total time taken            |   77.171

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.820
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.275
SBL Stage2: Board_driversOpen           |   31.269
SBL Stage2: Sciclient Get Version       |    6.760
SBL Stage2: App_loadImages              |    2.364
SBL Stage2: App_loadSelfcoreImage       |    8.340
SBL Stage2: App_loadLinuxImages         |   37.082
----------------------------------------|--------------
SBL Stage2: Total time taken            |   88.874

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
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 1195 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    6.437
SBL Stage1: Board_init                  |    0.099
SBL Stage1: Drivers_open                |   21.860
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.775
SBL Stage1: PBIST Positive Tests        |    7.801
SBL Stage1: PBIST Negative Tests        |    0.443
SBL Stage1: App_loadImages              |    9.020
SBL Stage1: App_loadSelfcoreImage       |    6.043
----------------------------------------|--------------
SBL Stage1: Total time taken            |   58.482

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.874
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.853
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    6.795
SBL Stage2: App_loadImages              |    4.228
SBL Stage2: App_loadSelfcoreImage       |    6.828
SBL Stage2: App_loadLinuxImages         |   20.295
----------------------------------------|--------------
SBL Stage2: Total time taken            |   62.878

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 1195 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    6.576
SBL Stage1: Board_init                  |    0.099
SBL Stage1: Drivers_open                |   58.049
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.780
SBL Stage1: PBIST Positive Tests        |    0.175
SBL Stage1: PBIST Negative Tests        |    0.441
SBL Stage1: App_loadImages              |   10.904
SBL Stage1: App_loadSelfcoreImage       |    8.090
----------------------------------------|--------------
SBL Stage1: Total time taken            |   91.129

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.879
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.887
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    6.811
SBL Stage2: App_loadImages              |    5.469
SBL Stage2: App_loadSelfcoreImage       |    8.515
SBL Stage2: App_loadLinuxImages         |   21.617
----------------------------------------|--------------
SBL Stage2: Total time taken            |   67.182

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK-SIP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 1194 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   19.024
SBL Stage1: Board_init                  |    0.100
SBL Stage1: Drivers_open                |   21.873
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.779
SBL Stage1: PBIST Positive Tests        |    0.171
SBL Stage1: PBIST Negative Tests        |    0.441
SBL Stage1: App_loadImages              |    8.965
SBL Stage1: App_loadSelfcoreImage       |    5.927
----------------------------------------|--------------
SBL Stage1: Total time taken            |   63.279

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.891
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.884
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |    6.813
SBL Stage2: App_loadImages              |    4.343
SBL Stage2: App_loadSelfcoreImage       |    6.860
SBL Stage2: App_loadLinuxImages         |   20.581
----------------------------------------|--------------
SBL Stage2: Total time taken            |   63.372

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 187 KB
- Size of images loaded by stage2  : 1233 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   15.803
SBL Stage1: Board_init                  |    0.094
SBL Stage1: Drivers_open                |  124.452
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.724
SBL Stage1: App_loadImages              |   10.218
SBL Stage1: App_loadSelfcoreImage       |    8.097
----------------------------------------|--------------
SBL Stage1: Total time taken            |  165.388

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.819
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.828
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    6.755
SBL Stage2: App_loadImages              |    5.369
SBL Stage2: App_loadSelfcoreImage       |    8.349
SBL Stage2: App_loadLinuxImages         |   22.579
----------------------------------------|--------------
SBL Stage2: Total time taken            |   67.702

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
      r5f0-0|       m4f0-0|             4|                        23.979|                25|         1000
      r5f0-0|       a530-0|             4|                        11.670|                13|         1000
      r5f0-0|       a530-1|             4|                        13.182|                14|         1000
      r5f0-0|       m4f0-0|            32|                        32.740|                33|         1000
      r5f0-0|       m4f0-0|            64|                        42.761|                44|         1000
      r5f0-0|       m4f0-0|           112|                        57.728|                59|         1000
      r5f0-0|       a530-0|            32|                        15.454|                16|         1000
      r5f0-0|       a530-0|            64|                        19.745|                21|         1000
      r5f0-0|       a530-0|           112|                        26.330|                27|         1000
      r5f0-0|       a530-1|            32|                        16.867|                18|         1000
      r5f0-0|       a530-1|            64|                        20.846|                22|         1000
      r5f0-0|       a530-1|           112|                        27.225|                28|         1000

### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 36.09 	         | 44.09
 SDR50 | 4	            | 39.22		         | 43.80
 SDR50 | 6	            | 41.66		         | 43.89
 SDR50 | 32	            | 41.42		         | 44.38
 SDR50 | 40	            | 41.42		         | 44.42
 DDR50 | 1	            | 51.50		         | 78.87
 DDR50 | 4	            | 51.94		         | 77.93
 DDR50 | 6	            | 60.87		         | 78.23
 DDR50 | 32	            | 60.27		         | 79.77
 DDR50 | 40	            | 59.54		         | 79.89
 HS200 | 1	            | 52,80		         | 151.11
 HS200 | 4	            | 60.57		         | 147.59
 HS200 | 6	            | 62.55		         | 148.64
 HS200 | 32	            | 60.16		         | 154.33
 HS200 | 40	            | 59.28		         | 154.81
**a53 :**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 37.68              | 46.14
 SDR50 | 4	            | 42.96              | 45.75
 SDR50 | 6	            | 42.02              | 45.63
 SDR50 | 32	            | 43.29              | 46.34
 SDR50 | 40	            | 42.80              | 46.48
 DDR50 | 1	            | 52.02              | 85.67
 DDR50 | 4	            | 61.41              | 84.32
 DDR50 | 6	            | 57.17              | 83.90
 DDR50 | 32	            | 62.70              | 86.37
 DDR50 | 40	            | 63.22              | 86.57
 HS200 | 1	            | 54.55              | 178.21
 HS200 | 4	            | 59.06              | 172.30
 HS200 | 6	            | 64.44              | 170.58
 HS200 | 32	            | 62.42              | 181.16
 HS200 | 40	            | 63.32              | 181.91

### OSPI NOR Flash Performance
**r5f0-0:**

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 54.99

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.54  ms
Fast Tuning Window          |          0.53  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |         10.07 ms
Fast Tuning Window          |          6.82 ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.40           |       2.87
      5          |        DAC        |        No         |        0.40           |       2.87
      10         |        DAC        |        No         |        0.40           |       2.87
      1          |        DAC        |        Yes        |        0.39           |       47.53
      5          |        DAC        |        Yes        |        0.40           |       47.57
      10         |        DAC        |        Yes        |        0.40           |       47.58

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.37           |       6.14
      5          |        DAC        |        No         |        0.38           |       6.14
      10         |        DAC        |        No         |        0.38           |       6.14
      1          |        DAC        |        Yes        |        0.37           |       6.21
      5          |        DAC        |        Yes        |        0.38           |       6.21
      10         |        DAC        |        Yes        |        0.38           |       6.21

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.39           |       4.08
      5          |        DAC        |        No         |        0.40           |       4.08
      10         |        DAC        |        No         |        0.40           |       4.08
      1          |        DAC        |        Yes        |        0.39           |       47.53
      5          |        DAC        |        Yes        |        0.40           |       47.57
      10         |        DAC        |        Yes        |        0.40           |       47.58

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.38           |       5.98
      5          |        DAC        |        No         |        0.39           |       5.98
      10         |        DAC        |        No         |        0.39           |       5.98
      1          |        DAC        |        Yes        |        0.38           |       117.07
      5          |        DAC        |        Yes        |        0.39           |       117.35
      10         |        DAC        |        Yes        |        0.39           |       117.39


 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.39           |       6.33
      5          |        DAC        |        No         |        0.40           |       6.33
      10         |        DAC        |        No         |        0.40           |       6.33
      1          |        DAC        |        Yes        |        0.39           |       208.62
      5          |        DAC        |        Yes        |        0.40           |       209.58
      10         |        DAC        |        Yes        |        0.40           |       209.69

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.39           |       6.71
      5          |        DAC        |        No         |        0.40           |       6.71
      10         |        DAC        |        No         |        0.40           |       6.71
      1          |        DAC        |        Yes        |        0.39           |       142.00
      5          |        DAC        |        Yes        |        0.40           |       142.42
      10         |        DAC        |        Yes        |        0.40           |       142.48

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.39           |       7.08
      5          |        DAC        |        No         |        0.40           |       7.08
      10         |        DAC        |        No         |        0.40           |       7.08
      1          |        DAC        |        Yes        |        0.39           |       247.40
      5          |        DAC        |        Yes        |        0.40           |       248.66
      10         |        DAC        |        Yes        |        0.40           |       248.82

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.39           |       13.70
      5          |       INDAC       |        No         |        0.40           |       13.70
      10         |       INDAC       |        No         |        0.40           |       13.70

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.37           |       6.25
      5          |       INDAC       |        No         |        0.38           |       6.25
      10         |       INDAC       |        No         |        0.38           |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.39           |       13.76
      5          |       INDAC       |        No         |        0.40           |       13.75
      10         |       INDAC       |        No         |        0.40           |       13.75

**a53 :**

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 56.14

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.31  ms
Fast Tuning Window          |          0.47  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          8.42 ms
Fast Tuning Window          |          5.65 ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       0.76
      5          |        DAC        |        No         |        0.43           |       0.76
      10         |        DAC        |        No         |        0.43           |       0.76
      1          |        DAC        |        Yes        |        0.42           |       49.83
      5          |        DAC        |        Yes        |        0.43           |       49.86
      10         |        DAC        |        Yes        |        0.43           |       49.86

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.39           |       0.54
      5          |        DAC        |        No         |        0.40           |       0.54
      10         |        DAC        |        No         |        0.40           |       0.54
      1          |        DAC        |        Yes        |        0.40           |       6.25
      5          |        DAC        |        Yes        |        0.40           |       6.25
      10         |        DAC        |        Yes        |        0.40           |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       1.11
      5          |        DAC        |        No         |        0.42           |       1.11
      10         |        DAC        |        No         |        0.42           |       1.11
      1          |        DAC        |        Yes        |        0.42           |       49.83
      5          |        DAC        |        Yes        |        0.42           |       49.86
      10         |        DAC        |        Yes        |        0.42           |       49.86

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       1.72
      5          |        DAC        |        No         |        0.41           |       1.72
      10         |        DAC        |        No         |        0.41           |       1.72
      1          |        DAC        |        Yes        |        0.40           |       132.09
      5          |        DAC        |        Yes        |        0.41           |       132.30
      10         |        DAC        |        Yes        |        0.41           |       132.33

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       1.85
      5          |        DAC        |        No         |        0.42           |       1.85
      10         |        DAC        |        No         |        0.42           |       1.85
      1          |        DAC        |        Yes        |        0.41           |       261.74
      5          |        DAC        |        Yes        |        0.42           |       262.55
      10         |        DAC        |        Yes        |        0.42           |       262.65

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       1.96
      5          |        DAC        |        No         |        0.41           |       1.96
      10         |        DAC        |        No         |        0.42           |       1.96
      1          |        DAC        |        Yes        |        0.40           |       164.74
      5          |        DAC        |        Yes        |        0.41           |       165.05
      10         |        DAC        |        Yes        |        0.42           |       165.09

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       2.08
      5          |        DAC        |        No         |        0.42           |       2.08
      10         |        DAC        |        No         |        0.42           |       2.08
      1          |        DAC        |        Yes        |        0.41           |       325.66
      5          |        DAC        |        Yes        |        0.42           |       326.92
      10         |        DAC        |        Yes        |        0.42           |       327.07

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.41           |       19.61
      5          |       INDAC       |        No         |        0.42           |       19.61
      10         |       INDAC       |        No         |        0.42           |       19.61

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.39           |       6.25
      5          |       INDAC       |        No         |        0.40           |       6.25
      10         |       INDAC       |        No         |        0.40           |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.41           |       19.60
      5          |       INDAC       |        No         |        0.42           |       19.61
      10         |       INDAC       |        No         |        0.42           |       19.61

### OSPI NAND Flash Performance
**r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.10  ms
Fast Tuning Window          |          0.61  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.43           |       4.40
      5          |        DAC        |        No         |        2.42           |       4.39
      10         |        DAC        |        No         |        2.41           |       4.39
      1          |        DAC        |        Yes        |        9.56           |       27.99
      5          |        DAC        |        Yes        |        9.51           |       29.33
      10         |        DAC        |        Yes        |        9.44           |       29.54

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.58           |       5.49
      5          |        DAC        |        No         |        1.58           |       5.50
      10         |        DAC        |        No         |        1.57           |       5.50
      1          |        DAC        |        Yes        |        4.05           |       5.70
      5          |        DAC        |        Yes        |        4.04           |       5.70
      10         |        DAC        |        Yes        |        4.02           |       5.70

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.43           |       3.59
      5          |        DAC        |        No         |        2.43           |       3.59
      10         |        DAC        |        No         |        2.42           |       3.59
      1          |        DAC        |        Yes        |        9.58           |       28.41
      5          |        DAC        |        Yes        |        9.54           |       28.42
      10         |        DAC        |        Yes        |        9.43           |       28.42

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.42           |       5.40
      5          |        DAC        |        No         |        2.41           |       5.40
      10         |        DAC        |        No         |        2.41           |       5.40
      1          |        DAC        |        Yes        |        10.66          |       43.62
      5          |        DAC        |        Yes        |        10.58          |       43.63
      10         |        DAC        |        Yes        |        10.46          |       43.63

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.42           |       5.97
      5          |        DAC        |        No         |        2.41           |       5.92
      10         |        DAC        |        No         |        2.41           |       5.91
      1          |        DAC        |        Yes        |        10.88          |       43.64
      5          |        DAC        |        Yes        |        10.82          |       46.98
      10         |        DAC        |        Yes        |        10.69          |       46.98

**a53 :**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          0.94  ms
Fast Tuning Window          |          0.52  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        3.02           |       1.27
      5          |        DAC        |        No         |        3.01           |       1.27
      10         |        DAC        |        No         |        3.00           |       1.27
      1          |        DAC        |        Yes        |        10.11          |       31.49
      5          |        DAC        |        Yes        |        10.18          |       31.49
      10         |        DAC        |        Yes        |        10.09          |       31.49

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.66           |       0.57
      5          |        DAC        |        No         |        1.65           |       0.57
      10         |        DAC        |        No         |        1.65           |       0.57
      1          |        DAC        |        Yes        |        4.10           |       5.74
      5          |        DAC        |        Yes        |        4.09           |       5.74
      10         |        DAC        |        Yes        |        4.08           |       5.74

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.61           |       1.01
      5          |        DAC        |        No         |        2.60           |       1.01
      10         |        DAC        |        No         |        2.59           |       1.01
      1          |        DAC        |        Yes        |        10.19          |       30.46
      5          |        DAC        |        Yes        |        10.12          |       30.46
      10         |        DAC        |        Yes        |        10.12          |       30.45

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        3.00           |       1.63
      5          |        DAC        |        No         |        2.99           |       1.63
      10         |        DAC        |        No         |        2.98           |       1.63
      1          |        DAC        |        Yes        |        11.34          |       48.13
      5          |        DAC        |        Yes        |        11.50          |       48.12
      10         |        DAC        |        Yes        |        11.31          |       48.12

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        3.01           |       1.81
      5          |        DAC        |        No         |        3.00           |       1.81
      10         |        DAC        |        No         |        2.99           |       1.81
      1          |        DAC        |        Yes        |        11.62          |       52.51
      5          |        DAC        |        Yes        |        11.76          |       52.51
      10         |        DAC        |        Yes        |        11.59          |       52.51

### GPMC NAND Flash Performance
**r5f0-0:**
 - Flash type: PARALLEL NAND
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 6.67		        | 19.99
 5	           | 6.61		        | 19.99
 10	           | 6.55		        | 19.99

**a53 :**
Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 10.03		            | 22.11
 5	           | 9.87		            | 22.11
 10	           | 9.76		            | 22.11


 ### CPSW Performance

For CPSW performance refer [Ethernet Performance](../components/networking/enet_lld/enet_cpsw_performance_am62x.md)

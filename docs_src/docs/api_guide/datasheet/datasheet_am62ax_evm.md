# Datasheet {#DATASHEET_AM62AX_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Generic Setup details

SOC Details             | Values
------------------------|------------------------------
Core                    | R5F
Core Operating Speed    | 800 MHz
Cache Status            | Enabled

Optimization Details    | Values
------------------------|------------------------------
Build Profile           | Release
R5F Compiler flags      | -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -Wall -Werror -g -mthumb -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function
R5F Linker flags        | -Wl,--diag_suppress=10063 -Wl,--ram_model -Wl,--reread_libs
Code Placement          | HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)
Data Placement          | HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)

## Performance Numbers

### SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 194 KB
- Size of images loaded by stage2  : 1360 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   26.080
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.196
SBL Stage1: Board_driversOpen           |   31.939
SBL Stage1: Sciclient Get Version       |    6.610
SBL Stage1: App_waitForMcuPbist         |    0.083
SBL Stage1: MCU R5 Image Load           |    3.462
SBL Stage1: DM R5 Image Load            |    6.062
----------------------------------------|--------------
SBL Stage2: Total time taken            |   74.436

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.670
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.217
SBL Stage2: Board_driversOpen           |   37.663
SBL Stage2: Sciclient Get Version       |    6.642
SBL Stage2: HSM Image Load              |    2.210
SBL Stage2: DM R5 Image Load            |    7.760
SBL Stage2: A53 Image Load              |   30.779
SBL Stage2: DSP Image Load              |   12.718
----------------------------------------|--------------
SBL Stage2: Total time taken            |   99.633

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL OSPI NAND performance (HS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 194 KB
- Size of images loaded by stage2  : 1360 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   26.003
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.196
SBL Stage1: Board_driversOpen           |   31.903
SBL Stage1: Sciclient Get Version       |    6.610
SBL Stage1: App_waitForMcuPbist         |    0.082
SBL Stage1: MCU R5 Image Load           |    3.470
SBL Stage1: DM R5 Image Load            |    6.607
----------------------------------------|--------------
SBL Stage2: Total time taken            |   74.334

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.670
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.216
SBL Stage2: Board_driversOpen           |   37.514
SBL Stage2: Sciclient Get Version       |    6.648
SBL Stage2: HSM Image Load              |    2.217
SBL Stage2: DM R5 Image Load            |    7.750
SBL Stage2: A53 Image Load              |   30.711
SBL Stage2: DSP Image Load              |   12.712
----------------------------------------|--------------
SBL Stage2: Total time taken            |   99.444

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 188 KB
- Size of images loaded by stage2  : 1360 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   26.382
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   21.473
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.609
SBL Stage1: MCU R5 Image Load           |    8.166
SBL Stage1: DM R5 Image Load            |    7.362
----------------------------------------|--------------
SBL Stage1: Total time taken            |   69.994

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.669
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.426
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    6.634
SBL Stage2: HSM Image Load              |    5.847
SBL Stage2: DM R5 Image Load            |    8.134
SBL Stage2: A53 Image Load              |   19.442
SBL Stage2: DSP Image Load              |   13.895
----------------------------------------|--------------
SBL Stage2: Total time taken            |   77.051

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 188 KB
- Size of images loaded by stage2  : 1360 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   25.993
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   21.466
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.608
SBL Stage1: MCU R5 Image Load           |    7.265
SBL Stage1: DM R5 Image Load            |    7.371
----------------------------------------|--------------
SBL Stage1: Total time taken            |   68.706

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.669
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   21.322
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |    6.637
SBL Stage2: HSM Image Load              |    5.848
SBL Stage2: DM R5 Image Load            |    8.150
SBL Stage2: A53 Image Load              |   19.239
SBL Stage2: DSP Image Load              |   13.880
----------------------------------------|--------------
SBL Stage2: Total time taken            |   76.749

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | mcu-r5f0-0  |  1.24
 r5f0-0     | a530-0      |  6.64
 r5f0-0     | c75ss0      |  14.66

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
      r5f0-0|       a530-0|             4|                         7.288|                 9|         1000
      r5f0-0|   mcu-r5f0-0|             4|                         9.102|                11|         1000
      r5f0-0|       c75ss0|             4|                        77.705|               103|         1000
      r5f0-0|       a530-0|            32|                         9.757|                12|         1000
      r5f0-0|       a530-0|            64|                        12.763|                16|         1000
      r5f0-0|       a530-0|           112|                        17.399|                23|         1000
      r5f0-0|   mcu-r5f0-0|            32|                        14.887|                18|         1000
      r5f0-0|   mcu-r5f0-0|            64|                        21.410|                27|         1000
      r5f0-0|   mcu-r5f0-0|           112|                        31.237|                38|         1000
      r5f0-0|       c75ss0|            32|                        85.867|               113|         1000
      r5f0-0|       c75ss0|            64|                        91.992|               121|         1000
      r5f0-0|       c75ss0|           112|                       104.768|               139|         1000


### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 40.49		         | 45.05
 SDR50 | 4	            | 41.54	             | 45.54
 SDR50 | 6	            | 41.60		         | 45.57
 SDR50 | 32	            | 38.97	             | 43.88
 SDR50 | 40	            | 38.96		         | 44.94
 DDR50 | 1	            | 21.79		         | 82.31
 DDR50 | 4	            | 71.01	             | 83.63
 DDR50 | 6	            | 70.99		         | 83.73
 DDR50 | 32	            | 62.85	             | 83.79
 DDR50 | 40	            | 64.91		         | 83.19
 HS200 | 1	            | 73.38		         | 158.25
 HS200 | 4	            | 109.53             | 169.36
 HS200 | 6	            | 80.30	             | 152.06
 HS200 | 32	            | 92.07	             | 166.58
 HS200 | 40	            | 96.10	             | 167.41

**a53ss0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 35.78		         | 46.11
 SDR50 | 4	            | 42.36	             | 46.50
 SDR50 | 6	            | 42.36		         | 46.54
 SDR50 | 32	            | 40.02	             | 46.58
 SDR50 | 40	            | 40.43		         | 46.57
 DDR50 | 1	            | 33.64		         | 85.55
 DDR50 | 4	            | 61.71	             | 86.93
 DDR50 | 6	            | 61.64		         | 87.03
 DDR50 | 32	            | 73.54	             | 87.13
 DDR50 | 40	            | 65.75		         | 87.17
 HS200 | 1	            | 72.39		         | 170.67
 HS200 | 4	            | 113.56	         | 183.49
 HS200 | 6	            | 77.01              | 183.95
 HS200 | 32	            | 105.89	         | 184.43
 HS200 | 40	            | 96.59              | 184.59

### OSPI NAND Performance {#OSPI_DATA_SHEET}
**r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.13  ms
Fast Tuning Window          |          0.65  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.32          |       4.31
      5          |        DAC        |        No         |        2.31          |       4.31
      10         |        DAC        |        No         |        2.31          |       4.31
      1          |        DAC        |        Yes        |        9.79          |       29.21
      5          |        DAC        |        Yes        |        9.79          |       29.22
      10         |        DAC        |        Yes        |        9.87          |       29.23

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.56           |       5.53
      5          |        DAC        |        No         |        1.55           |       5.53
      10         |        DAC        |        No         |        1.55           |       5.53
      1          |        DAC        |        Yes        |        4.07           |       5.72
      5          |        DAC        |        Yes        |        4.06           |       5.72
      10         |        DAC        |        Yes        |        4.05           |       5.72

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.32           |       3.55
      5          |        DAC        |        No         |        2.31           |       3.55
      10         |        DAC        |        No         |        2.31           |       3.55
      1          |        DAC        |        Yes        |        9.78           |       29.21
      5          |        DAC        |        Yes        |        9.74           |       29.22
      10         |        DAC        |        Yes        |        9.68           |       29.22

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.31           |       5.26
      5          |        DAC        |        No         |        2.31           |       5.26
      10         |        DAC        |        No         |        2.31           |       5.26
      1          |        DAC        |        Yes        |        11.07          |       44.12
      5          |        DAC        |        Yes        |        11.01          |       44.12
      10         |        DAC        |        Yes        |        10.95          |       44.12

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.32          |       5.73
      5          |        DAC        |        No         |        2.32          |       5.74
      10         |        DAC        |        No         |        2.31          |       5.74
      1          |        DAC        |        Yes        |        11.33         |       47.30
      5          |        DAC        |        Yes        |        11.26         |       47.31
      10         |        DAC        |        Yes        |        11.19         |       47.30


**mcu-r5f0-0:**

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.27  ms
Fast Tuning Window          |          0.72  ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.03          |       4.05
      5          |        DAC        |        No         |        2.02          |       4.05
      10         |        DAC        |        No         |        2.01          |       4.05
      1          |        DAC        |        Yes        |        10.01         |       28.62
      5          |        DAC        |        Yes        |        9.80          |       28.63
      10         |        DAC        |        Yes        |        9.72          |       28.63

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        1.47           |       5.26
      5          |        DAC        |        No         |        1.46           |       5.26
      10         |        DAC        |        No         |        1.45           |       5.26
      1          |        DAC        |        Yes        |        4.10           |       5.72
      5          |        DAC        |        Yes        |        4.08           |       5.72
      10         |        DAC        |        Yes        |        4.07           |       5.72

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.02           |       3.38
      5          |        DAC        |        No         |        2.01           |       3.38
      10         |        DAC        |        No         |        2.01           |       3.38
      1          |        DAC        |        Yes        |        10.02          |       29.06
      5          |        DAC        |        Yes        |        9.85           |       29.06
      10         |        DAC        |        Yes        |        9.84           |       29.06

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        2.03           |       4.90
      5          |        DAC        |        No         |        2.01           |       4.90
      10         |        DAC        |        No         |        2.01           |       4.90
      1          |        DAC        |        Yes        |        11.31          |       43.52
      5          |        DAC        |        Yes        |        11.13          |       43.52
      10         |        DAC        |        Yes        |        11.12          |       43.52

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        2.46          |       5.36
      5          |        DAC        |        No         |        2.43          |       5.36
      10         |        DAC        |        No         |        2.43          |       5.36
      1          |        DAC        |        Yes        |        11.58          |       46.53
      5          |        DAC        |        Yes        |        11.40          |       46.53
      10         |        DAC        |        Yes        |        11.37          |       46.53


 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2


 ### UART callback latency
UART callback latency is measured by measuring how long it takes to physically transmit a known-length string at the configured baud rate. This timing measurement is done when a 28bytes of data is send over different baud.

Core          | Baud         | Transmssion          | Transmission         |Callback
              |              | Expected Latency (us)| Measured Latency (us)|Latency (us)
--------------|--------------|----------------------|----------------------|-------------- 
 mcu-r5f      | 1200         | 233438               | 233333               | 19
 mcu-r5f      | 2400         | 116715               | 116666               | 19
 mcu-r5f      | 4800         | 58367                | 58333                | 19
 mcu-r5f      | 9600         | 29227                | 29166                | 19
 mcu-r5f      | 19200        | 14570                | 14583                | 19
 mcu-r5f      | 38400        | 7285                 | 7291                 | 19
 mcu-r5f      | 57600        | 4857                 | 4861                 | 19
 mcu-r5f      | 115200       | 2429                 | 2430                 | 19
 a53ss0-0     | 1200         | 233438               | 233333               | 53
 a53ss0-0     | 2400         | 116715               | 116666               | 53
 a53ss0-0     | 4800         | 58367                | 58333                | 53
 a53ss0-0     | 9600         | 29227                | 29166                | 53
 a53ss0-0     | 19200        | 14570                | 14583                | 53
 a53ss0-0     | 38400        | 7285                 | 7291                 | 53
 a53ss0-0     | 57600        | 4857                 | 4861                 | 53
 a53ss0-0     | 115200       | 2429                 | 2430                 | 53
 c75ss0       | 1200         | 233438               | 233333               | 43
 c75ss0       | 2400         | 116715               | 116666               | 43
 c75ss0       | 4800         | 58367                | 58333                | 43
 c75ss0       | 9600         | 29227                | 29166                | 43
 c75ss0       | 19200        | 14570                | 14583                | 43
 c75ss0       | 38400        | 7285                 | 7291                 | 43
 c75ss0       | 57600        | 4857                 | 4861                 | 43
 c75ss0       | 115200       | 2429                 | 2430                 | 43
 r5f0-0       | 1200         | 233438               | 233333               | 32
 r5f0-0       | 2400         | 116715               | 116666               | 32
 r5f0-0       | 4800         | 58367                | 58333                | 32
 r5f0-0       | 9600         | 29227                | 29166                | 32
 r5f0-0       | 19200        | 14570                | 14583                | 32
 r5f0-0       | 38400        | 7285                 | 7291                 | 32
 r5f0-0       | 57600        | 4857                 | 4861                 | 32
 r5f0-0       | 115200       | 2429                 | 2430                 | 32
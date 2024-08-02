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
- Size of images loaded by stage1  : 192 KB
- Size of images loaded by stage2  : 1125 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.335
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.196
SBL Stage1: Board_driversOpen           |   26.747
SBL Stage1: Sciclient Get Version       |   10.169
SBL Stage1: App_waitForMcuPbist         |    0.002
SBL Stage1: App_loadImages              |    3.400
SBL Stage1: App_loadSelfcoreImage       |    6.740
----------------------------------------|--------------
SBL Stage2: Total time taken            |   85.594

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.770
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |    0.223
SBL Stage2: Board_driversOpen           |   26.670
SBL Stage2: Sciclient Get Version       |   10.216
SBL Stage2: App_loadImages              |    2.041
SBL Stage2: App_loadSelfcoreImage       |    6.911
SBL Stage2: App_loadLinuxImages         |   28.738
SBL Stage2: App_loadDSPImage            |   12.968
----------------------------------------|--------------
SBL Stage2: Total time taken            |   89.180

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL OSPI NAND performance (HS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 192 KB
- Size of images loaded by stage2  : 1125 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   37.332
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.197
SBL Stage1: Board_driversOpen           |   26.713
SBL Stage1: Sciclient Get Version       |   10.170
SBL Stage1: App_waitForMcuPbist         |    0.002
SBL Stage1: App_loadImages              |    3.482
SBL Stage1: App_loadSelfcoreImage       |    6.815
----------------------------------------|--------------
SBL Stage2: Total time taken            |   84.714

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.764
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.221
SBL Stage2: Board_driversOpen           |   26.662
SBL Stage2: Sciclient Get Version       |   10.221
SBL Stage2: App_loadImages              |    2.127
SBL Stage2: App_loadSelfcoreImage       |    6.994
SBL Stage2: App_loadLinuxImages         |   28.438
SBL Stage2: App_loadDSPImage            |   13.054
----------------------------------------|--------------
SBL Stage2: Total time taken            |   89.486

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 162 KB
- Size of images loaded by stage2  : 1125 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.230
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.570
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.169
SBL Stage1: App_loadImages              |    6.900
SBL Stage1: App_loadSelfcoreImage       |    7.438
----------------------------------------|--------------
SBL Stage1: Total time taken            |   82.309

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.660
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.502
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.266
SBL Stage2: App_loadImages              |    5.982
SBL Stage2: App_loadSelfcoreImage       |    7.918
SBL Stage2: App_loadLinuxImages         |   20.341
SBL Stage2: App_loadDSPImage            |   14.211
----------------------------------------|--------------
SBL Stage2: Total time taken            |   79.884

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 162 KB
- Size of images loaded by stage2  : 1125 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   37.442
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   19.573
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.169
SBL Stage1: App_loadImages              |    6.967
SBL Stage1: App_loadSelfcoreImage       |    7.528
----------------------------------------|--------------
SBL Stage1: Total time taken            |   81.681

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.660
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   19.506
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.224
SBL Stage2: App_loadImages              |    6.070
SBL Stage2: App_loadSelfcoreImage       |    8.013
SBL Stage2: App_loadLinuxImages         |   20.363
SBL Stage2: App_loadDSPImage            |   14.279
----------------------------------------|--------------
SBL Stage2: Total time taken            |   80.120

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~39 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | mcu-r5f0-0  |  1.12
 r5f0-0     | a530-0      |  6.79
 r5f0-0     | c75ss0      |  18.01

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us)
------------|-------------|--------------|------------------------------|------------------
      r5f0-0|       a530-0|            32|                         9.619|                12
      r5f0-0|       a530-0|            64|                        12.584|                17
      r5f0-0|       a530-0|           112|                        17.308|                22
      r5f0-0|   mcu-r5f0-0|            32|                        14.215|                17
      r5f0-0|   mcu-r5f0-0|            64|                        20.734|                27
      r5f0-0|   mcu-r5f0-0|           112|                        30.550|                38
      r5f0-0|       c75ss0|            32|                        76.941|               103
      r5f0-0|       c75ss0|            64|                        86.202|               104
      r5f0-0|       c75ss0|           112|                        93.336|               112


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 35.20		   | 45.00
 SDR50 | 4	            | 41.55		   | 45.54
 SDR50 | 6	            | 41.63		   | 44.24
 DDR50 | 1	            | 54.16		   | 81.77
 DDR50 | 4	            | 54.87		   | 83.65
 DDR50 | 6	            | 61.99		   | 79.33
 HS200 | 1	            | 73.72		   | 157.99
 HS200 | 4	            | 109.78		   | 169.31
 HS200 | 6	            | 109.95		   | 152.03


### OSPI NAND Performance
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	       | 2.35		    | 50.39
 5	       | 2.36		    | 50.38
 10	       | 2.36		    | 50.38


 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2
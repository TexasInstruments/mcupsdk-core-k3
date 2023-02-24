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
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 178 KB
- Size of images loaded by stage2  : 825 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   44.846
SBL Stage1: Drivers_open                |   0.216
SBL Stage1: Board_driversOpen           |   0.086
SBL Stage1: Sciclient Get Version       |   10.091
SBL Stage1: App_loadImages              |   16.346
SBL Stage1: App_loadSelfcoreImage       |   37.587
SBL Stage2: System_init                 |   2.385
SBL Stage2: Drivers_open                |   0.246
SBL Stage2: Board_driversOpen           |   0.084
SBL Stage2: Sciclient Get Version       |   10.093
SBL Stage2: App_loadImages              |   4.341
SBL Stage2: App_loadSelfcoreImage       |   42.883
SBL Stage2: App_loadLinuxImages         |   183.609
----------------------------------------|--------------
SBL : Total time taken                  |   352.819

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~45 ms taken for System Init is mostly attributed to DDR initialization.

\cond AM62AX_TBD
### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : mcu-r5f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 158 KB
- Size of images loaded by stage2  : 853 KB
- Boot Media Clock                 : 200.000 MHz

Boot time breakdown                     |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   44.458
SBL Stage1: Drivers_open                |   784.024
SBL Stage1: Board_driversOpen           |   0
SBL Stage1: Sciclient Get Version       |   10.092
SBL Stage1: App_loadImages              |   163.992
SBL Stage1: App_loadSelfcoreImage       |   220.837
SBL Stage2: System_init                 |   2.282
SBL Stage2: Drivers_open                |   766.184
SBL Stage2: Board_driversOpen           |   0
SBL Stage2: Sciclient Get Version       |   10.162
SBL Stage2: App_loadImages              |   90.634
SBL Stage2: App_loadSelfcoreImage       |   299.848
SBL Stage2: App_loadLinuxImages         |   723.241
----------------------------------------|--------------
SBL : Total time taken                  |   3115.760

- The emmc driver initialization is done as part of Drivers_open. It takes more than 750ms. This needs more investigation.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~45 ms taken for System Init is mostly attributed to DDR initialization.
\endcond

### IPC performance

#### IPC NOTIFY

- 1000000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0 | m4f0-0        |  7.909

#### IPC RPMSG

- 100000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us)
------------|-------------|--------------|------------------------------
 r5f0-0 | m4f0-0        | 32    |  76
 r5f0-0 | m4f0-0        | 64    |  114
 r5f0-0 | m4f0-0        | 112   |  135

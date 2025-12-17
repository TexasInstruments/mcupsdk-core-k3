# Datasheet {#DATASHEET_AM275X_EVM}

[TOC]

This datasheet provides the performance numbers of various device drivers in FreeRTOS SDK for @VAR_SOC_NAME

## Generic Setup details

SOC Details             | Values
------------------------|------------------------------
Core                    | R5F
Core Operating Speed    | 1000 MHz
Cache Status            | Enabled

SOC Details             | Values
------------------------|------------------------------
Core                    | C75
Core Operating Speed    | 1000 MHz
Cache Status            | Enabled

Optimization Details    | Values
------------------------|------------------------------
Build Profile           | Release
R5F Compiler flags      | -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -Wall -Werror -g -mthumb -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function
R5F Linker flags        | -Wl,--diag_suppress=10063 -Wl,--ram_model -Wl,--reread_libs
Code Placement          | MSRAM
Data Placement          | MSRAM
C7 Compiler flags       | -mv7524  --abi=eabi -q -mo -pden -pds=238 -pds=880 -pds1110 --endian=little  --disable_inlining -ea.se71 --emit_warnings_as_errors --diag_suppress=770 --diag_suppress=69 --diag_suppress=70 -Dxdc_target_name__=C71 --opt_level=3 --symdebug:none
C7 Linker flags         | --silicon_version=7524 -z --emit_warnings_as_errors --diag_suppress=10063 --ram_model --warn_sections -q -x --mapfile_contents=sym_defs
Code Placement          | MSRAM / L2RAM
Data Placement          | MSRAM / L2RAM

## Performance Numbers
### SBL OSPI NOR performance (HS-FS)

- Software/Application used        : sbl_ospi, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 463 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        779
System_init                      |       1903
Board_init                       |          7
FreeRtosTask Create              |        296
Drivers_open                     |       5793
Board_driversOpen                |        159
sciServer_init                   |      15160
SBL Drivers_open                 |       3233
SBL Board_driversOpen            |       5886
Sciclient Get Version            |       6546
R5FSS0_0 Image Load              |       2187
R5FSS0_1 Image Load              |       1644
R5FSS1_0 Image Load              |       1638
R5FSS1_1 Image Load              |       1625
DSP 0 Image Load                 |       7007
DSP 1 Image Load                 |       6893
---------------------------------|--------------
SBL Total Time Taken             |      60762

### SBL Fast-xSPI NOR performance (HS-FS)

- Software/Application used        : sbl_ospi, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 463 KB
- Boot Media Clock                 : 133.333 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        801
System_init                      |       1901
Board_init                       |          8
FreeRtosTask Create              |        296
Drivers_open                     |       5794
Board_driversOpen                |        160
sciServer_init                   |      15164
SBL Drivers_open                 |       3230
SBL Board_driversOpen            |        472
Sciclient Get Version            |       6551
R5FSS0_0 Image Load              |       2226
R5FSS0_1 Image Load              |       1683
R5FSS1_0 Image Load              |       1677
R5FSS1_1 Image Load              |       1660
DSP 0 Image Load                 |       7117
DSP 1 Image Load                 |       7010
---------------------------------|--------------
SBL Total Time Taken             |      55757

#### R5FSS0_0 boot time using Fast-xSPI Bootmode

For how to enable Fast XSPI boot refer \ref FAST_XSPI_BOOTMODE_GUIDE
 - GPIO toggle time from R5FSS0_0 (Measured from PORz)
   - 53 ms

 - Cores booted by SBL : r5fss0-0, r5fss0-1, r5fss1-0, r5fss1-1, c75ss0-0, c75ss1-0
 - R5FSS0-0 image size = ~ 1 MB and remaining cores by default ipc rpmsg images

#### C7x audio chime time using Fast-xSPI Bootmode

For how to enable Fast XSPI boot refer \ref FAST_XSPI_BOOTMODE_GUIDE
 - C7x audio out time (Measured from PORz)
   - 80 ms

 - Cores booted by SBL : r5fss0-0, r5fss0-1, r5fss1-0, r5fss1-1, c75ss0-0, c75ss1-0
 - C75SS0-0 image size = ~ 1 MB and remaining cores by default ipc rpmsg images
 - Includes DAC configuration time


### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 463 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS200

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |       1079
System_init                      |        793
Board_init                       |          4
FreeRtosTask Create              |        255
Drivers_open                     |       6808
Board_driversOpen                |        159
sciServer_init                   |        114
SBL Drivers_open                 |      16431
Sciclient Get Version            |       6528
R5FSS0_0 Image Load              |      13763
R5FSS0_1 Image Load              |      11341
R5FSS1_0 Image Load              |      12086
R5FSS1_1 Image Load              |      12040
DSP 0 Image Load                 |      18117
DSP 1 Image Load                 |      18763
---------------------------------|--------------
SBL Total Time Taken             |     118287

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
c75ss0-0	| c75ss1-0	  | 1.425
 r5f0-0	    | r5f0-1	  | 1.131
 r5f0-0	    | r5f1-0	  | 1.261
 r5f0-0	    | r5f1-1	  | 1.140
 r5f0-0	    | c75ss0-0	  | 1.163
 r5f0-0	    | c75ss1-0	  | 1.163
#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured
Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) |
------------|-------------|--------------|------------------------------|------------------|
      r5f0-0|       r5f0-1|            32|                         6.959|                 7|
      r5f0-0|       r5f0-1|            64|                         8.331|                 8|
      r5f0-0|       r5f0-1|           112|                        10.515|                11|
      r5f0-0|       r5f1-0|            32|                         6.811|                 7|
      r5f0-0|       r5f1-0|            64|                         8.290|                 9|
      r5f0-0|       r5f1-0|           112|                        10.466|                11|
      r5f0-0|       r5f1-1|            32|                         6.965|                 7|
      r5f0-0|       r5f1-1|            64|                         8.352|                 9|
      r5f0-0|       r5f1-1|           112|                        10.518|                11|
      r5f0-0|     c75ss0-0|            32|                         8.673|                10|
      r5f0-0|     c75ss0-0|            64|                         9.296|                10|
      r5f0-0|     c75ss0-0|           112|                        10.368|                11|
      r5f0-0|     c75ss1-0|            32|                         8.906|                10|
      r5f0-0|     c75ss1-0|            64|                         9.543|                10|
      r5f0-0|     c75ss1-0|           112|                        10.564|                11|


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
SDR50  | 	   1        |       26.20		 |      45.23
DDR50  | 	   1        |       50.49		 |      82.64
HS200  | 	   1        |       79.73		 |     157.23

### OSPI NOR Flash Performance {#OSPI_DATA_SHEET}

**wkup-r5f0-0:**

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          5.29 ms
Fast Tuning Window          |          5.36 ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.45          |        3.09
      1          |        DAC        |        Yes        |        0.45          |       48.73

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       6.24
      1          |        DAC        |        Yes        |        0.42           |       6.23

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.45           |        7.66
      1          |        DAC        |        Yes        |        0.45           |      233.99

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.45          |         8.75
      1          |        DAC        |        Yes        |        0.45          |       283.86

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.44          |        21.14

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.42          |         6.25

**c75ss0:**

 Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.43          |        5.87
      1          |        DAC        |        Yes        |        0.43          |       49.85

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       6.23
      1          |        DAC        |        Yes        |        0.41           |       6.25

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       13.34
      1          |        DAC        |        Yes        |        0.43           |      262.44

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.43          |        16.64
      1          |        DAC        |        Yes        |        0.43          |       326.73

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.43          |       21.79

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.41          |        6.25

 ### XIP Benchmark
- Core :	R5F
- Core Operating Speed : 800 MHz

- Software/Application used : xip_benchmark

- 1) FIR operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    23905
Code/Data not cached                    |    52400
Code/Data not cached 1 of 10 iterations |    26757

- 2) MEMCPY operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    1564
Code/Data not cached                    |    3771
Code/Data not cached 1 of 10 iterations |    1789

### HYPERRAM Performance with cache enabled

For R5 core:-

ECC         | Transfer Mode  | Write speed(MiBps) | Read speed(MiBps)
------------|----------------|--------------------|-------------------
Disabled    |     CPU        |      80.57         |        68.63
Disabled    |     BCDMA      |      144.04        |        143.82
enabled     |     CPU        |      75.29         |        68.92
enabled     |     BCDMA      |      108.63        |        136.20

For c7x core:-

ECC         | Transfer Mode  | Write speed(MiBps) | Read speed(MiBps)
------------|----------------|--------------------|-------------------
Disabled    |     CPU        |      145.11        |        72.39
Disabled    |     BCDMA      |      143.82        |        143.82
enabled     |     CPU        |      109.36        |        70.31
enabled     |     BCDMA      |      108.63        |        136.01

### HYPERRAM XIP benchmark
- Core :	R5F
- Core Operating Speed : 800 MHz

- Software/Application used : hyperRam_xip_benchmark

- 1) FIR operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    23905
Code/Data not cached                    |    54895
Code/Data not cached 1 of 10 iterations |    27006

- 2) MEMCPY operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    1564
Code/Data not cached                    |    5386
Code/Data not cached 1 of 10 iterations |    1950

### Ethernet Performance
For Ethernet performance Refer to the page \ref enetlld_performance

### Ethernet AVB Performance
For Ethernet AVB performance, refer to the page \ref EAVB_PERFORMANCE

### McASP (audio) Latency
 - McASP operating at 48KHz, I2C mode
 - RX to TX pin to pin latency is measured
 - Rx To Tx pin to pin latency ~126us

### ARM R5F - Memory Access latency
- [32-BIT READ] Self TCM Access Average Latency Per Byte: 0.796875 ns
- [32-BIT READ] MSRAM Access Average Latency Per Byte: 9.234375 ns
- [32-BIT READ] Non-Self TCM Access Average Latency Per Byte: 35.320312 ns

- [64-BIT READ] Self TCM Access Average Latency Per Byte: 0.300781 ns
- [64-BIT READ] MSRAM Access Read Average Latency Per Byte: 4.617188 ns
- [64-BIT READ] Non-Self TCM Access Read Average Latency Per Byte: 17.660156 ns

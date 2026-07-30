# Datasheet

This datasheet provides the performance numbers of various device drivers in FreeRTOS SDK for {{ VAR_SOC_NAME }}

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
- Size of images loaded            : 479 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        296
System_init                      |       2720
Board_init                       |          7
FreeRtosTask Create              |        300
Drivers_open                     |       5794
Board_driversOpen                |        159
sciServer_init                   |      15090
SBL Drivers_open                 |       3217
SBL Board_driversOpen            |       5815
Sciclient Get Version            |       6607
R5FSS0_0 Image Load              |       17496
R5FSS0_1 Image Load              |       2430
R5FSS1_0 Image Load              |       2429
R5FSS1_1 Image Load              |       2414
DSP 0 Image Load                 |       7767
DSP 1 Image Load                 |       7656
---------------------------------|--------------
SBL Total Time Taken             |      82489

### SBL Fast-xSPI NOR performance (HS-FS)

- Software/Application used        : sbl_ospi, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 463 KB
- Boot Media Clock                 : 133.333 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        296
System_init                      |       2743
Board_init                       |          7
FreeRtosTask Create              |        255
Drivers_open                     |       5789
Board_driversOpen                |        159
sciServer_init                   |      15090
SBL Drivers_open                 |       3212
SBL Board_driversOpen            |       5810
Sciclient Get Version            |       6608
R5FSS0_0 Image Load              |       2188
R5FSS0_1 Image Load              |       1652
R5FSS1_0 Image Load              |       1651
R5FSS1_1 Image Load              |       1633
DSP 0 Image Load                 |       7020
DSP 1 Image Load                 |       6908
---------------------------------|--------------
SBL Total Time Taken             |      61021

#### R5FSS0_0 boot time using Fast-xSPI Bootmode

For how to enable Fast XSPI boot refer FAST_XSPI_BOOTMODE_GUIDE
 - GPIO toggle time from R5FSS0_0 (Measured from PORz)
   - 53 ms

 - Cores booted by SBL : r5fss0-0, r5fss0-1, r5fss1-0, r5fss1-1, c75ss0-0, c75ss1-0
 - R5FSS0-0 image size = ~ 1 MB and remaining cores by default ipc rpmsg images

#### C7x audio chime time using Fast-xSPI Bootmode

For how to enable Fast XSPI boot refer FAST_XSPI_BOOTMODE_GUIDE
 - C7x audio out time (Measured from PORz)
   - 80 ms

 - Cores booted by SBL : r5fss0-0, r5fss0-1, r5fss1-0, r5fss1-1, c75ss0-0, c75ss1-0
 - C75SS0-0 image size = ~ 1 MB and remaining cores by default ipc rpmsg images
 - Includes DAC configuration time


### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 467 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS200

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        335
System_init                      |      13534
Board_init                       |          5
FreeRtosTask Create              |        260
Drivers_open                     |       5807
Board_driversOpen                |        160
sciServer_init                   |        131
SBL Drivers_open                 |      53122
Sciclient Get Version            |       6652
R5FSS0_0 Image Load              |      18523
R5FSS0_1 Image Load              |      16666
R5FSS1_0 Image Load              |      16663
R5FSS1_1 Image Load              |      16646
DSP 0 Image Load                 |      18884
DSP 1 Image Load                 |      18783
---------------------------------|--------------
SBL Total Time Taken             |     196453

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core      | Remote Core   | Average Message Latency (us)
----------------|---------------|------------------------------
c75ss0-0	    | c75ss1-0	  | 1.600
 r5f0-0	    | r5f0-1	  | 1.150
 r5f0-0	    | r5f1-0	  | 1.265
 r5f0-0	    | r5f1-1	  | 1.150
 r5f0-0	    | c75ss0-0	  | 1.169
 r5f0-0	    | c75ss1-0	  | 1.166
#### IPC RPMSG

1000 messages are sent and average one way message latency is measured:

| Local Core | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) |
|------------|-------------|--------------|------------------------------|------------------|
| r5f0-0     | r5f0-1      | 32           | 7.333                        | 7                |
| r5f0-0     | r5f0-1      | 64           | 8.333                        | 8                |
| r5f0-0     | r5f0-1      | 112          | 10.666                       | 11               |
| r5f0-0     | r5f1-0      | 32           | 7.000                        | 7                |
| r5f0-0     | r5f1-0      | 64           | 8.166                        | 8                |
| r5f0-0     | r5f1-0      | 112          | 10.833                       | 11               |
| r5f0-0     | r5f1-1      | 32           | 7.000                        | 7                |
| r5f0-0     | r5f1-1      | 64           | 8.500                        | 8                |
| r5f0-0     | r5f1-1      | 112          | 10.833                       | 11               |
| r5f0-0     | c75ss0-0    | 32           | 8.833                        | 9                |
| r5f0-0     | c75ss0-0    | 64           | 9.500                        | 9                |
| r5f0-0     | c75ss0-0    | 112          | 10.166                       | 10               |
| r5f0-0     | c75ss1-0    | 32           | 8.833                        | 9                |
| r5f0-0     | c75ss1-0    | 64           | 9.166                        | 9                |
| r5f0-0     | c75ss1-0    | 112          | 10.333                       | 10               |


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
SDR50  |     0.12	      |       11.67        | 38.65
DDR50  | 	 0.12       |       38.05        | 65.00
HS200  | 	 0.12       |       49.96        | 107.57

### OSPI NOR Flash Performance
**wkup-r5f0-0:**

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 41.98

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.01  ms
Fast Tuning Window          |          0.40  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          5.25 ms
Fast Tuning Window          |          5.29 ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.42              | 3.09             |
| 1               | DAC       | Yes         | 0.42              | 48.73            |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.40              | 6.24             |
| 1               | DAC       | Yes         | 0.40              | 6.23             |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.42              | 4.57             |
| 1               | DAC       | Yes         | 0.42              | 48.73            |

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.41              | 7.20             |
| 1               | DAC       | Yes         | 0.41              | 124.64           |

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.41              | 7.67             |
| 1               | DAC       | Yes         | 0.41              | 233.99           |

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.41              | 8.27             |
| 1               | DAC       | Yes         | 0.41              | 153.29           |

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.42              | 8.74             |
| 1               | DAC       | Yes         | 0.41              | 283.84           |

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | INDAC     | No          | 0.42              | 21.04            |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | INDAC     | No          | 0.39              | 6.25             |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | INDAC     | No          | 0.42              | 21.05            |

**c75ss0:**

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 45.24

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          0.93  ms
Fast Tuning Window          |          0.38  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          5.03 ms
Fast Tuning Window          |          5.01 ms

 Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.42              | 5.87             |
| 1               | DAC       | Yes         | 0.42              | 49.85            |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.40              | 6.23             |
| 1               | DAC       | Yes         | 0.40              | 6.25             |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.42              | 8.49             |
| 1               | DAC       | Yes         | 0.42              | 49.86            |

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.42              | 11.96            |
| 1               | DAC       | Yes         | 0.42              | 132.26           |

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.42              | 13.34            |
| 1               | DAC       | Yes         | 0.42              | 262.37           |

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.42              | 14.65            |
| 1               | DAC       | Yes         | 0.42              | 165.01           |

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | DAC       | No          | 0.42              | 16.64            |
| 1               | DAC       | Yes         | 0.42              | 326.72           |

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | INDAC     | No          | 0.42              | 21.77            |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | INDAC     | No          | 0.40              | 6.25             |

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|-----------------|-----------|-------------|-------------------|------------------|
| 1               | INDAC     | No          | 0.42              | 21.76            |

 ### XIP Benchmark
- Core :	R5F
- Core Operating Speed : 800 MHz

- Software/Application used : xip_benchmark

- 1) FIR operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    23915
Code/Data not cached                    |    108393
Code/Data not cached 1 of 10 iterations |    32576

- 2) MEMCPY operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    1564
Code/Data not cached                    |    7661
Code/Data not cached 1 of 10 iterations |    2177

### HYPERRAM Performance with cache enabled

For R5 core:-

ECC         | Transfer Mode  | Write speed(MiBps) | Read speed(MiBps)
------------|----------------|--------------------|-------------------
Disabled    |     CPU        |      95.65         |        70.66
Disabled    |     BCDMA      |      144.68         |        144.46
enabled     |     CPU        |      79.52         |        68.53
enabled     |     BCDMA      |      109.11         |        136.58

For c7x core:-

ECC         | Transfer Mode  | Write speed(MiBps) | Read speed(MiBps)
------------|----------------|--------------------|-------------------
Disabled    |     CPU        |      145.32        |        72.39
Disabled    |     BCDMA      |      144.04        |        143.82
enabled     |     CPU        |      109.48        |        70.36
enabled     |     BCDMA      |      108.63        |        136.01

### HYPERRAM XIP benchmark
- Core :	R5F
- Core Operating Speed : 800 MHz

- Software/Application used : hyperRam_xip_benchmark

- 1) FIR operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    23913
Code/Data not cached                    |    46640
Code/Data not cached 1 of 10 iterations |    26187

- 2) MEMCPY operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    1563
Code/Data not cached                    |    5274
Code/Data not cached 1 of 10 iterations |    1935

### Ethernet Performance
For Ethernet performance refer [Ethernet Performance](../components/networking/enet_lld/enet_cpsw_performance_am275x.md)

### Ethernet AVB Performance
For Ethernet AVB performance, refer to the page EAVB_PERFORMANCE

### McASP (audio) Latency
 - McASP operating at 48KHz, I2C mode
 - RX to TX pin to pin latency is measured
 - Rx To Tx pin to pin latency ~126us

### ARM R5F - Memory Access latency
- [32-BIT READ] Self TCM Access Average Latency Per Byte: 1.078125 ns
- [32-BIT READ] MSRAM Access Average Latency Per Byte: 9.132812 ns
- [32-BIT READ] Non-Self TCM Access Average Latency Per Byte: 35.320312 ns

- [64-BIT READ] Self TCM Access Average Latency Per Byte: 0.300781 ns
- [64-BIT READ] MSRAM Access Average Latency Per Byte: 4.617188 ns
- [64-BIT READ] Non-Self TCM Access Average Latency Per Byte: 17.660156 ns

### C7x - Memory Access latency

- [32-BIT READ] L2RAM Access Average Latency Per Byte: 2.117188 ns
- [32-BIT READ] MSRAM Access Average Latency Per Byte: 2.320312 ns

- [64-BIT READ] L2RAM Access Average Latency Per Byte: 1.187500 ns
- [64-BIT READ] MSRAM Access Average Latency Per Byte: 1.375000 ns

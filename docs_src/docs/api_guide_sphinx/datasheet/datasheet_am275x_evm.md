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
- Size of images loaded            : 467 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        294
System_init                      |       2743
Board_init                       |          7
FreeRtosTask Create              |        255
Drivers_open                     |       5789
Board_driversOpen                |        158
sciServer_init                   |      15084
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
SBL Total Time Taken             |      61020

### SBL Fast-xSPI NOR performance (HS-FS)

- Software/Application used        : sbl_ospi, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 463 KB
- Boot Media Clock                 : 133.333 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        294
System_init                      |       2743
Board_init                       |          7
FreeRtosTask Create              |        255
Drivers_open                     |       5789
Board_driversOpen                |        158
sciServer_init                   |      15084
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
SBL Total Time Taken             |      61020

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
TIFS init                        |        333
System_init                      |      13387
Board_init                       |          5
FreeRtosTask Create              |        258
Drivers_open                     |       5809
Board_driversOpen                |        162
sciServer_init                   |        129
SBL Drivers_open                 |      61609
Sciclient Get Version            |       6648
R5FSS0_0 Image Load              |      18949
R5FSS0_1 Image Load              |      16830
R5FSS1_0 Image Load              |      16830
R5FSS1_1 Image Load              |      16812
DSP 0 Image Load                 |      19136
DSP 1 Image Load                 |      19059
---------------------------------|--------------
SBL Total Time Taken             |     196946

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
c75ss0-0	| c75ss1-0	  | 1.700
 r5f0-0	    | r5f0-1	  | 1.133
 r5f0-0	    | r5f1-0	  | 1.261
 r5f0-0	    | r5f1-1	  | 1.121
 r5f0-0	    | c75ss0-0	  | 1.164
 r5f0-0	    | c75ss1-0	  | 1.166
#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured
Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) |
------------|-------------|--------------|------------------------------|------------------|
      r5f0-0|       r5f0-1|            32|                         6.975|                 7|
      r5f0-0|       r5f0-1|            64|                         8.338|                 9|
      r5f0-0|       r5f0-1|           112|                        10.535|                11|
      r5f0-0|       r5f1-0|            32|                         6.820|                 7|
      r5f0-0|       r5f1-0|            64|                         8.311|                 9|
      r5f0-0|       r5f1-0|           112|                        10.457|                11|
      r5f0-0|       r5f1-1|            32|                         6.971|                 7|
      r5f0-0|       r5f1-1|            64|                         8.329|                 9|
      r5f0-0|       r5f1-1|           112|                        10.519|                11|
      r5f0-0|     c75ss0-0|            32|                         8.511|                10|
      r5f0-0|     c75ss0-0|            64|                         9.185|                10|
      r5f0-0|     c75ss0-0|           112|                        10.235|                11|
      r5f0-0|     c75ss1-0|            32|                         8.778|                10|
      r5f0-0|     c75ss1-0|            64|                         9.407|                10|
      r5f0-0|     c75ss1-0|           112|                        10.490|                11|


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
SDR50  | 	   1        |       29.34   |      43.81
DDR50  | 	   1        |       41.35   |      77.93
HS200  | 	   1        |       59.52   |     138.55

### OSPI NOR Flash Performance
**wkup-r5f0-0:**

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 47.86

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.02  ms
Fast Tuning Window          |          0.42  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          5.39 ms
Fast Tuning Window          |          5.40 ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.44          |        3.09
      1          |        DAC        |        Yes        |        0.44          |       48.73

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       6.24
      1          |        DAC        |        Yes        |        0.41           |       6.23

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       4.57
      1          |        DAC        |        Yes        |        0.44           |       48.74

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       7.20
      1          |        DAC        |        Yes        |        0.43           |       124.64

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |        7.67
      1          |        DAC        |        Yes        |        0.43           |      234.02

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.43           |       8.20
      1          |        DAC        |        Yes        |        0.43           |       153.31

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.44          |         8.75
      1          |        DAC        |        Yes        |        0.44          |       283.88

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.44          |        21.07

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.42          |         6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.44           |       21.06

**c75ss0:**

 - PHY condition: enabled
 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Temperature: 49.99

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          0.96  ms
Fast Tuning Window          |          0.40  ms

 - Flash type: SERIAL NOR
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          5.02 ms
Fast Tuning Window          |          5.04 ms

 Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.45          |        5.87
      1          |        DAC        |        Yes        |        0.45          |       49.86

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.42           |       6.23
      1          |        DAC        |        Yes        |        0.42           |       6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.45           |       8.49
      1          |        DAC        |        Yes        |        0.45           |       49.86

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       11.96
      1          |        DAC        |        Yes        |        0.44           |       132.26

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       13.34
      1          |        DAC        |        Yes        |        0.44           |      262.44

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.44           |       14.62
      1          |        DAC        |        Yes        |        0.44           |       165.02

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.45          |        16.64
      1          |        DAC        |        Yes        |        0.44          |       326.78

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.45          |       21.77

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.42          |        6.25

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |       INDAC       |        No         |        0.45           |       21.77

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
Disabled    |     CPU        |      80.18         |        70.00
Disabled    |     BCDMA      |      143.82         |        143.82
enabled     |     CPU        |      75.64         |        64.63
enabled     |     BCDMA      |      108.51         |        136.20

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
Code/Data fully cached                  |    23913
Code/Data not cached                    |    48303
Code/Data not cached 1 of 10 iterations |    26354

- 2) MEMCPY operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    1564
Code/Data not cached                    |    4358
Code/Data not cached 1 of 10 iterations |    1844

### Ethernet Performance
For Ethernet performance Refer to the page enetlld_performance

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

### UART callback latency
UART callback latency is measured by measuring how long it takes to physically transmit a known-length string at the configured baud rate. This timing measurement is done when a 28bytes of data is send over different baud.

Core          | Baud         | Transmssion          | Transmission         |Callback
              |              | Expected Latency (us)| Measured Latency (us)|Latency (us)
--------------|--------------|----------------------|----------------------|--------------
 r5fss*       | 1200         | 233434               | 233333               | 45
 r5fss*       | 2400         | 116717               | 116666               | 45
 r5fss*       | 4800         | 58367                | 58333                | 45
 r5fss*       | 9600         | 29229                | 29166                | 45
 r5fss*       | 19200        | 14575                | 14583                | 45
 r5fss*       | 38400        | 7290                 | 7291                 | 45
 r5fss*       | 57600        | 4857                 | 4861                 | 45
 r5fss*       | 115200       | 2429                 | 2430                 | 45
 c75ss*       | 1200         | 233434               | 233333               | 41
 c75ss*       | 2400         | 116717               | 116666               | 41
 c75ss*       | 4800         | 58367                | 58333                | 41
 c75ss*       | 9600         | 29229                | 29166                | 41
 c75ss*       | 19200        | 14575                | 14583                | 41
 c75ss*       | 38400        | 7290                 | 7291                 | 41
 c75ss*       | 57600        | 4857                 | 4861                 | 41
 c75ss*       | 115200       | 2429                 | 2430                 | 41
 wkup-r5fss   | 1200         | 233434               | 233333               | 27
 wkup-r5fss   | 2400         | 116717               | 116666               | 27
 wkup-r5fss   | 4800         | 58367                | 58333                | 27
 wkup-r5fss   | 9600         | 29229                | 29166                | 27
 wkup-r5fss   | 19200        | 14575                | 14583                | 27
 wkup-r5fss   | 38400        | 7290                 | 7291                 | 27
 wkup-r5fss   | 57600        | 4857                 | 4861                 | 27
 wkup-r5fss   | 115200       | 2429                 | 2430                 | 27

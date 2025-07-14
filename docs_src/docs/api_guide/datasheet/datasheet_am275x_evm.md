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
C7 Linker flags         | --silicon_version=7524 -z --emit_warnings_as_errors --diag_suppress=10063 --ram_model --warn_sections -q -x
Code Placement          | MSRAM / L2RAM
Data Placement          | MSRAM / L2RAM

## Performance Numbers
### SBL OSPI NOR performance (HS-FS)

- Software/Application used        : sbl_ospi, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 462 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        609
System_init                      |       1904
Board_init                       |          7
FreeRtosTask Create              |        297
Drivers_open                     |       5792
Board_driversOpen                |        159
sciServer_init                   |      15075
SBL Drivers_open                 |       3213
SBL Board_driversOpen            |       2977
Sciclient Get Version            |      10023
R5FSS0_0 Image Load              |       2169
R5FSS0_1 Image Load              |       1638
R5FSS1_0 Image Load              |       1634
R5FSS1_1 Image Load              |       1618
DSP 0 Image Load                 |       6991
DSP 1 Image Load                 |       6887
---------------------------------|--------------
SBL Total Time Taken             |      60999

### SBL Fast-xSPI NOR performance (HS-FS)

- Software/Application used        : sbl_ospi, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 462 KB
- Boot Media Clock                 : 133.333 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        838
System_init                      |       1902
Board_init                       |          6
FreeRtosTask Create              |        297
Drivers_open                     |       5792
Board_driversOpen                |        159
sciServer_init                   |      15082
SBL Drivers_open                 |       3215
SBL Board_driversOpen            |        192
Sciclient Get Version            |      10019
R5FSS0_0 Image Load              |       2129
R5FSS0_1 Image Load              |       1609
R5FSS1_0 Image Load              |       1605
R5FSS1_1 Image Load              |       1590
DSP 0 Image Load                 |       7027
DSP 1 Image Load                 |       6932
---------------------------------|--------------
SBL Total Time Taken             |      58402

#### R5FSS0_0 boot time using Fast-xSPI Bootmode

For how to enable Fast XSPI boot refer \ref FAST_XSPI_BOOTMODE_GUIDE
 - GPIO toggle time from R5FSS0_0 (Measured from PORz)
   - 47 ms

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
- Size of images loaded            : 462 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS200

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        741
System_init                      |        787
Board_init                       |          3
FreeRtosTask Create              |        255
Drivers_open                     |       6836
Board_driversOpen                |        158
sciServer_init                   |        109
SBL Drivers_open                 |      60898
Sciclient Get Version            |      10038
R5FSS0_0 Image Load              |       8813
R5FSS0_1 Image Load              |       6862
R5FSS1_0 Image Load              |       6860
R5FSS1_1 Image Load              |       6837
DSP 0 Image Load                 |      12846
DSP 1 Image Load                 |      12868
---------------------------------|--------------
SBL Total Time Taken             |     134918

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
c75ss0-0	| c75ss1-0	  | 1.500
 r5f0-0	    | r5f0-1	  | 1.135
 r5f0-0	    | r5f1-0	  | 1.266
 r5f0-0	    | r5f1-1	  | 1.121
 r5f0-0	    | c75ss0-0	  | 1.161
 r5f0-0	    | c75ss1-0	  | 1.163
#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured
Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) |
------------|-------------|--------------|------------------------------|------------------|
      r5f0-0|       r5f0-1|            32|                         6.980|                 7|
      r5f0-0|       r5f0-1|            64|                         8.337|                 9|
      r5f0-0|       r5f0-1|           112|                        10.524|                11|
      r5f0-0|       r5f1-0|            32|                         6.815|                 7|
      r5f0-0|       r5f1-0|            64|                         8.265|                 9|
      r5f0-0|       r5f1-0|           112|                        10.469|                11|
      r5f0-0|       r5f1-1|            32|                         6.969|                 7|
      r5f0-0|       r5f1-1|            64|                         8.366|                 9|
      r5f0-0|       r5f1-1|           112|                        10.524|                11|
      r5f0-0|     c75ss0-0|            32|                         8.564|                10|
      r5f0-0|     c75ss0-0|            64|                         9.239|                10|
      r5f0-0|     c75ss0-0|           112|                        10.262|                11|
      r5f0-0|     c75ss1-0|            32|                         8.776|                10|
      r5f0-0|     c75ss1-0|            64|                         9.425|                10|
      r5f0-0|     c75ss1-0|           112|                        10.495|                11|


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
SDR50  | 1	       | 26.20		    | 45.23
DDR50  | 1	       | 50.49		    | 82.64
HS200  | 1	       | 79.73		    | 157.23

### OSPI NOR Flash Performance

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.43          |       3.09
      1          |        Yes        |        0.43          |       48.74


 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.41          |       6.24
      1          |        Yes        |        0.41          |       6.23


 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.43          |       7.63
      1          |        Yes        |        0.43          |       234.20


 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|----------------------|----------------------
      1          |        No         |        0.43          |       8.77
      1          |        Yes        |        0.43          |       284.07


 ### XIP Benchmark
- Core :	R5F
- Core Operating Speed : 800 MHz

- Software/Application used : xip_benchmark

- 1) FIR operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    23906
Code/Data not cached                    |    52861
Code/Data not cached 1 of 10 iterations |    26850

- 2) MEMCPY operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    1564
Code/Data not cached                    |    3892
Code/Data not cached 1 of 10 iterations |    1800

### HYPERRAM Performance

Transfer Mode  | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-------------------
    CPU        |      92.92         |        70.77
    BCDMA      |      144.68        |        144.46


### HYPERRAM XIP benchmark
- Core :	R5F
- Core Operating Speed : 800 MHz

- Software/Application used : hyperRam_xip_benchmark

- 1) FIR operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    23913
Code/Data not cached                    |    47805
Code/Data not cached 1 of 10 iterations |    26303

- 2) MEMCPY operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    1564
Code/Data not cached                    |    4295
Code/Data not cached 1 of 10 iterations |    1838

### McASP (audio) Latency
 - McASP operating at 48KHz, I2C mode
 - RX to TX pin to pin latency is measured
 - Rx To Tx pin to pin latency ~126us

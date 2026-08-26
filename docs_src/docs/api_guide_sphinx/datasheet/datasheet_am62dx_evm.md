# Datasheet


## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for {{ VAR_SOC_NAME }}


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

### CPSW

For CPSW performance refer [Ethernet Performance](../components/networking/enet_lld/enet_cpsw_performance_am62dx.md)

### DDR

- Software/Application used        : ddr_perf (10MB DDR-to-DDR memcpy, measured via DDR controller load/bandwidth counters)
- Measured on r5f0-0

DDR Bandwidth | Value (MiB/s)
--------------|--------------
Read          | 280
Write         | 318
Total         | 598

### EMMC

**a53:**

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
SDR50  | 1              | 35.74              | 45.97
SDR50  | 4              | 42.35              | 46.51
SDR50  | 6              | 37.81              | 46.54
SDR50  | 32             | 40.38              | 46.58
SDR50  | 40             | 39.88              | 46.58
DDR50  | 1              | 55.36              | 85.54
DDR50  | 4              | 73.32              | 86.93
DDR50  | 6              | 73.27              | 87.04
DDR50  | 32             | 65.72              | 87.13
DDR50  | 40             | 67.66              | 87.17
HS200  | 1              | 75.50              | 170.61
HS200  | 4              | 66.32              | 183.44
HS200  | 6              | 115.67             | 183.96
HS200  | 32             | 97.14              | 184.41
HS200  | 40             | 101.87             | 184.55

**r5:**

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
SDR50  | 1.00           | 40.46              | 45.10
SDR50  | 4.00           | 36.40              | 45.54
SDR50  | 6.00           | 41.61              | 45.57
SDR50  | 32.00          | 38.90              | 43.89
SDR50  | 40.00          | 39.66              | 45.57
DDR50  | 1.00           | 68.89              | 81.77
DDR50  | 4.00           | 70.94              | 83.60
DDR50  | 6.00           | 54.08              | 83.71
DDR50  | 32.00          | 65.89              | 78.21
DDR50  | 40.00          | 64.28              | 83.85
HS200  | 1.00           | 22.80              | 159.55
HS200  | 4.00           | 108.88             | 169.25
HS200  | 6.00           | 108.39             | 169.72
HS200  | 32.00          | 93.29              | 148.38
HS200  | 40.00          | 97.40              | 170.27

### I2C

- Data write/read throughput measured at 100 kHz and 400 kHz, in polling and interrupt transfer modes
- MiB/s computed from Data Size / Transfer Time (firmware's floating-point throughput print does not render on this build; transfer time is measured directly)

**a53:**

Mode      | Freq    | Data Size (B) | Write MiB/s | Write Time (us) | Read MiB/s | Read Time (us)
----------|---------|---------------|-------------|------------------|------------|---------------
POLLING   | 100 kHz | 64            | 0.01        | 6065             | 0.01       | 6174
POLLING   | 100 kHz | 128           | 0.01        | 11825            | 0.01       | 11933
POLLING   | 100 kHz | 256           | 0.01        | 23343            | 0.01       | 23452
POLLING   | 400 kHz | 64            | 0.04        | 1572             | 0.04       | 1601
POLLING   | 400 kHz | 128           | 0.04        | 3060             | 0.04       | 3089
POLLING   | 400 kHz | 256           | 0.04        | 6035             | 0.04       | 6065
INTERRUPT | 100 kHz | 64            | 0.01        | 6064             | 0.01       | 6178
INTERRUPT | 100 kHz | 128           | 0.01        | 11824            | 0.01       | 11937
INTERRUPT | 100 kHz | 256           | 0.01        | 23343            | 0.01       | 23456
INTERRUPT | 400 kHz | 64            | 0.04        | 1572             | 0.04       | 1604
INTERRUPT | 400 kHz | 128           | 0.04        | 3060             | 0.04       | 3092
INTERRUPT | 400 kHz | 256           | 0.04        | 6035             | 0.04       | 6068

**r5f0-0:**

Mode      | Freq    | Data Size (B) | Write MiB/s | Write Time (us) | Read MiB/s | Read Time (us)
----------|---------|---------------|-------------|------------------|------------|---------------
POLLING   | 100 kHz | 64            | 0.01        | 6066             | 0.01       | 6176
POLLING   | 100 kHz | 128           | 0.01        | 11827            | 0.01       | 11935
POLLING   | 100 kHz | 256           | 0.01        | 23344            | 0.01       | 23455
POLLING   | 400 kHz | 64            | 0.04        | 1573             | 0.04       | 1603
POLLING   | 400 kHz | 128           | 0.04        | 3061             | 0.04       | 3091
POLLING   | 400 kHz | 256           | 0.04        | 6036             | 0.04       | 6066
INTERRUPT | 100 kHz | 64            | 0.01        | 6065             | 0.01       | 6178
INTERRUPT | 100 kHz | 128           | 0.01        | 11824            | 0.01       | 11938
INTERRUPT | 100 kHz | 256           | 0.01        | 23343            | 0.01       | 23457
INTERRUPT | 400 kHz | 64            | 0.04        | 1572             | 0.04       | 1605
INTERRUPT | 400 kHz | 128           | 0.04        | 3060             | 0.04       | 3093
INTERRUPT | 400 kHz | 256           | 0.04        | 6036             | 0.04       | 6069

### IPC

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured.
- All cores are running from DDR with the exception of MCU-R5 from MSRAM

Local Core  | Remote Core | Average Message Latency (ns)
------------|-------------|------------------------------
mcu-r5f0-0  | c75ss0      |  1956ns
mcu-r5f0-0  | a530-0      |  1226ns
mcu-r5f0-0  | r5f0-0      |  1762ns
a530-0      | c75ss0      |  1955ns
c75ss0      | r5f0-0      |  1956ns
a530-0      | r5f0-0      |  1060ns

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us)
------------|-------------|--------------|------------------------------|------------------
r5f0-0      | a530-0      | 4            | 7.789                        | 10
r5f0-0      | mcu-r5f0-0  | 4            | 9.691                        | 12
r5f0-0      | c75ss0      | 4            | 77.424                       | 96
r5f0-0      | a530-0      | 32           | 10.543                       | 14
r5f0-0      | a530-0      | 64           | 13.677                       | 18
r5f0-0      | a530-0      | 112          | 18.430                       | 25
r5f0-0      | mcu-r5f0-0  | 32           | 15.757                       | 20
r5f0-0      | mcu-r5f0-0  | 64           | 22.373                       | 30
r5f0-0      | mcu-r5f0-0  | 112          | 32.800                       | 43
r5f0-0      | c75ss0      | 32           | 86.281                       | 112
r5f0-0      | c75ss0      | 64           | 93.988                       | 122
r5f0-0      | c75ss0      | 112          | 110.168                      | 138


(OSPI_DATA_SHEET)=
### OSPI

**a53:**

- PHY condition: enabled
- Flash type: SERIAL NOR
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Temperature: 57.63

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.50 ms
Fast Tuning Window          |          0.54 ms

- Flash type: SERIAL NOR
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          9.39 ms
Fast Tuning Window          |          6.33 ms

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 0.73 |
| 5 | DAC | No | 0.44 | 0.73 |
| 10 | DAC | No | 0.44 | 0.73 |
| 1 | DAC | Yes | 0.44 | 49.83 |
| 5 | DAC | Yes | 0.44 | 49.86 |
| 10 | DAC | Yes | 0.44 | 49.86 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.41 | 0.54 |
| 5 | DAC | No | 0.42 | 0.54 |
| 10 | DAC | No | 0.42 | 0.54 |
| 1 | DAC | Yes | 0.41 | 6.25 |
| 5 | DAC | Yes | 0.42 | 6.25 |
| 10 | DAC | Yes | 0.42 | 6.25 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 1.06 |
| 5 | DAC | No | 0.44 | 1.06 |
| 10 | DAC | No | 0.44 | 1.06 |
| 1 | DAC | Yes | 0.44 | 49.84 |
| 5 | DAC | Yes | 0.44 | 49.86 |
| 10 | DAC | Yes | 0.44 | 49.86 |

- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 1.58 |
| 5 | DAC | No | 0.43 | 1.58 |
| 10 | DAC | No | 0.43 | 1.58 |
| 1 | DAC | Yes | 0.43 | 132.10 |
| 5 | DAC | Yes | 0.43 | 132.30 |
| 10 | DAC | Yes | 0.43 | 132.33 |

- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 1.67 |
| 5 | DAC | No | 0.44 | 1.67 |
| 10 | DAC | No | 0.44 | 1.67 |
| 1 | DAC | Yes | 0.43 | 261.78 |
| 5 | DAC | Yes | 0.44 | 262.55 |
| 10 | DAC | Yes | 0.44 | 262.65 |

- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 1.77 |
| 5 | DAC | No | 0.43 | 1.77 |
| 10 | DAC | No | 0.43 | 1.77 |
| 1 | DAC | Yes | 0.43 | 164.74 |
| 5 | DAC | Yes | 0.43 | 165.06 |
| 10 | DAC | Yes | 0.43 | 165.09 |

- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.43 | 1.89 |
| 5 | DAC | No | 0.44 | 1.89 |
| 10 | DAC | No | 0.44 | 1.89 |
| 1 | DAC | Yes | 0.43 | 325.65 |
| 5 | DAC | Yes | 0.44 | 326.93 |
| 10 | DAC | Yes | 0.44 | 327.07 |

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.44 | 15.60 |
| 5 | INDAC | No | 0.44 | 15.60 |
| 10 | INDAC | No | 0.44 | 15.60 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.41 | 6.25 |
| 5 | INDAC | No | 0.42 | 6.25 |
| 10 | INDAC | No | 0.42 | 6.25 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.43 | 15.60 |
| 5 | INDAC | No | 0.44 | 15.60 |
| 10 | INDAC | No | 0.44 | 15.60 |

**r5f0-0:**

- PHY condition: enabled
- Flash type: SERIAL NOR
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Temperature: 56.41

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.61 ms
Fast Tuning Window          |          0.58 ms

- Flash type: SERIAL NOR
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          10.13 ms
Fast Tuning Window          |          6.76 ms

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.42 | 2.74 |
| 5 | DAC | No | 0.43 | 2.74 |
| 10 | DAC | No | 0.43 | 2.74 |
| 1 | DAC | Yes | 0.42 | 48.72 |
| 5 | DAC | Yes | 0.43 | 48.76 |
| 10 | DAC | Yes | 0.43 | 48.76 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.40 | 5.87 |
| 5 | DAC | No | 0.40 | 5.87 |
| 10 | DAC | No | 0.40 | 5.87 |
| 1 | DAC | Yes | 0.40 | 6.23 |
| 5 | DAC | Yes | 0.40 | 6.23 |
| 10 | DAC | Yes | 0.40 | 6.23 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.42 | 3.99 |
| 5 | DAC | No | 0.43 | 3.99 |
| 10 | DAC | No | 0.43 | 3.99 |
| 1 | DAC | Yes | 0.42 | 48.73 |
| 5 | DAC | Yes | 0.43 | 48.76 |
| 10 | DAC | Yes | 0.43 | 48.76 |

- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.41 | 5.80 |
| 5 | DAC | No | 0.42 | 5.80 |
| 10 | DAC | No | 0.42 | 5.80 |
| 1 | DAC | Yes | 0.41 | 124.57 |
| 5 | DAC | Yes | 0.42 | 124.82 |
| 10 | DAC | Yes | 0.42 | 124.85 |

- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.42 | 6.14 |
| 5 | DAC | No | 0.42 | 6.14 |
| 10 | DAC | No | 0.42 | 6.14 |
| 1 | DAC | Yes | 0.42 | 233.76 |
| 5 | DAC | Yes | 0.42 | 234.65 |
| 10 | DAC | Yes | 0.42 | 234.76 |

- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.42 | 6.48 |
| 5 | DAC | No | 0.42 | 6.48 |
| 10 | DAC | No | 0.42 | 6.48 |
| 1 | DAC | Yes | 0.42 | 153.20 |
| 5 | DAC | Yes | 0.42 | 153.57 |
| 10 | DAC | Yes | 0.42 | 153.62 |

- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.42 | 6.83 |
| 5 | DAC | No | 0.43 | 6.83 |
| 10 | DAC | No | 0.43 | 6.83 |
| 1 | DAC | Yes | 0.42 | 283.48 |
| 5 | DAC | Yes | 0.42 | 284.76 |
| 10 | DAC | Yes | 0.43 | 284.92 |

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.42 | 12.82 |
| 5 | INDAC | No | 0.43 | 12.82 |
| 10 | INDAC | No | 0.43 | 12.82 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.40 | 6.25 |
| 5 | INDAC | No | 0.40 | 6.25 |
| 10 | INDAC | No | 0.40 | 6.25 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.42 | 12.82 |
| 5 | INDAC | No | 0.43 | 12.81 |
| 10 | INDAC | No | 0.43 | 12.81 |

**mcu-r5f0-0:**

- PHY condition: enabled
- Flash type: SERIAL NOR
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Temperature: 57.47

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.91 ms
Fast Tuning Window          |          0.67 ms

- Flash type: SERIAL NOR
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          11.54 ms
Fast Tuning Window          |          7.75 ms

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.41 | 2.71 |
| 5 | DAC | No | 0.42 | 2.71 |
| 10 | DAC | No | 0.42 | 2.71 |
| 1 | DAC | Yes | 0.42 | 48.73 |
| 5 | DAC | Yes | 0.42 | 48.76 |
| 10 | DAC | Yes | 0.42 | 48.76 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.40 | 5.88 |
| 5 | DAC | No | 0.40 | 5.88 |
| 10 | DAC | No | 0.40 | 5.88 |
| 1 | DAC | Yes | 0.39 | 6.23 |
| 5 | DAC | Yes | 0.40 | 6.23 |
| 10 | DAC | Yes | 0.40 | 6.23 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.41 | 3.77 |
| 5 | DAC | No | 0.42 | 3.77 |
| 10 | DAC | No | 0.42 | 3.77 |
| 1 | DAC | Yes | 0.41 | 48.73 |
| 5 | DAC | Yes | 0.42 | 48.76 |
| 10 | DAC | Yes | 0.42 | 48.76 |

- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.41 | 5.34 |
| 5 | DAC | No | 0.41 | 5.34 |
| 10 | DAC | No | 0.41 | 5.34 |
| 1 | DAC | Yes | 0.41 | 124.58 |
| 5 | DAC | Yes | 0.41 | 124.82 |
| 10 | DAC | Yes | 0.41 | 124.85 |

- Flash frequency: 133Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.41 | 5.48 |
| 5 | DAC | No | 0.42 | 5.48 |
| 10 | DAC | No | 0.42 | 5.48 |
| 1 | DAC | Yes | 0.41 | 233.80 |
| 5 | DAC | Yes | 0.42 | 234.65 |
| 10 | DAC | Yes | 0.42 | 234.75 |

- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.41 | 5.87 |
| 5 | DAC | No | 0.41 | 5.87 |
| 10 | DAC | No | 0.41 | 5.87 |
| 1 | DAC | Yes | 0.41 | 153.22 |
| 5 | DAC | Yes | 0.41 | 153.57 |
| 10 | DAC | Yes | 0.41 | 153.62 |

- Flash frequency: 166Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: enabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | DAC | No | 0.41 | 6.16 |
| 5 | DAC | No | 0.42 | 6.16 |
| 10 | DAC | No | 0.42 | 6.16 |
| 1 | DAC | Yes | 0.41 | 283.54 |
| 5 | DAC | Yes | 0.42 | 284.76 |
| 10 | DAC | Yes | 0.42 | 284.92 |

- Flash frequency: 25Mhz
- Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.41 | 10.80 |
| 5 | INDAC | No | 0.42 | 10.80 |
| 10 | INDAC | No | 0.42 | 10.80 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.39 | 6.25 |
| 5 | INDAC | No | 0.40 | 6.25 |
| 10 | INDAC | No | 0.40 | 6.25 |

- Flash frequency: 50Mhz
- Flash protocol: FLASH_CFG_PROTO_8S_8S_8S
- Phy Condition: disabled

| Data Size(MiB) | READ MODE | DMA Enabled | Write Speed(mbps) | Read Speed(mbps) |
|---|---|---|---|---|
| 1 | INDAC | No | 0.41 | 10.81 |
| 5 | INDAC | No | 0.42 | 10.81 |
| 10 | INDAC | No | 0.42 | 10.81 |

### UDMA

- BCDMA block-copy throughput for various source/destination combinations (DDR, internal OCRAM)

**a53:**

Test                                                          | Throughput (MB/s)
--------------------------------------------------------------|-------------------
BCDMA Blockcpy DDR 1MB to DDR 1MB                              | 1004
BCDMA 2D Blockcpy INTERNAL(OCRAM) circular 1KB to DDR 1MB      | 2582
BCDMA 2D Blockcpy DDR 1MB to INTERNAL(OCRAM) circular 1KB      | 1616
BCDMA 2D Blockcpy DDR 4MB to INTERNAL(OCRAM) circular 4KB (20ms pacing) | 419
BCDMA 2D Blockcpy INTERNAL(OCRAM) circular 1KB to INTERNAL(OCRAM) circular 1KB | 2653

**r5f0-0:**

Test                                                          | Throughput (MB/s)
--------------------------------------------------------------|-------------------
BCDMA Blockcpy DDR 1MB to DDR 1MB                              | 1003
BCDMA 2D Blockcpy INTERNAL(OCRAM) circular 1KB to DDR 1MB      | 2569
BCDMA 2D Blockcpy DDR 1MB to INTERNAL(OCRAM) circular 1KB      | 1614
BCDMA 2D Blockcpy DDR 4MB to INTERNAL(OCRAM) circular 4KB (20ms pacing) | 419
BCDMA 2D Blockcpy INTERNAL(OCRAM) circular 1KB to INTERNAL(OCRAM) circular 1KB | 2640

## Latency

### GPIO latency

GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2

### MCASP (audio) Latency

- MCASP operating at 48KHz, I2C mode
- RX to TX pin to pin latency is measured
- Rx To Tx pin to pin latency ~468us

### UART callback latency

UART callback latency is measured by measuring how long it takes to physically transmit a known-length string at the configured baud rate. This timing measurement is done when a 28bytes of data is send over different baud.

Core          | Baud         | Transmssion          | Transmission         |Callback
              |              | Expected Latency (us)| Measured Latency (us)|Latency (us)
--------------|--------------|----------------------|----------------------|-------------- 
 mcu-r5f      | 1200         | 233434               | 233333               | 19
 mcu-r5f      | 2400         | 116717               | 116666               | 19
 mcu-r5f      | 4800         | 58367                | 58333                | 19
 mcu-r5f      | 9600         | 29229                | 29166                | 19
 mcu-r5f      | 19200        | 14575                | 14583                | 19
 mcu-r5f      | 38400        | 7290                 | 7291                 | 19
 mcu-r5f      | 57600        | 4857                 | 4861                 | 19
 mcu-r5f      | 115200       | 2429                 | 2430                 | 19
 a53ss0-0     | 1200         | 233434               | 233333               | 53
 a53ss0-0     | 2400         | 116717               | 116666               | 53
 a53ss0-0     | 4800         | 58367                | 58333                | 53
 a53ss0-0     | 9600         | 29229                | 29166                | 53
 a53ss0-0     | 19200        | 14575                | 14583                | 53
 a53ss0-0     | 38400        | 7290                 | 7291                 | 53
 a53ss0-0     | 57600        | 4857                 | 4861                 | 53
 a53ss0-0     | 115200       | 2429                 | 2430                 | 53
 c75ss0       | 1200         | 233434               | 233333               | 50
 c75ss0       | 2400         | 116717               | 116666               | 50
 c75ss0       | 4800         | 58367                | 58333                | 50
 c75ss0       | 9600         | 29229                | 29166                | 50
 c75ss0       | 19200        | 14575                | 14583                | 50
 c75ss0       | 38400        | 7290                 | 7291                 | 50
 c75ss0       | 57600        | 4857                 | 4861                 | 50
 c75ss0       | 115200       | 2429                 | 2430                 | 50
 r5f0-0       | 1200         | 233434               | 233333               | 34
 r5f0-0       | 2400         | 116717               | 116666               | 34
 r5f0-0       | 4800         | 58367                | 58333                | 34
 r5f0-0       | 9600         | 29229                | 29166                | 34
 r5f0-0       | 19200        | 14575                | 14583                | 34
 r5f0-0       | 38400        | 7290                 | 7291                 | 34
 r5f0-0       | 57600        | 4857                 | 4861                 | 34
 r5f0-0       | 115200       | 2429                 | 2430                 | 34

### Boot latency

- Measured from MCU_PORz to the first response of MCU-R5 and C7x cores
- OSPI boot mode with SBL running OSPI in 8D-8D-8D mode (Phy enabled, DMA enabled)
- HSM image size ~7KB
- MCU R5 image size ~1MB
- Boot time as observed in HS-FS device

#### MCU R5 boot time

- GPIO toggle time from MCUR5 main (Measured from MCU_PORz)
- 128 ms

#### C7x audio chime time

- C7x audio out time (Measured from MCU_PORz)
- Includes DAC configuration time
- 151 ms

## SBL Performance

### SBL OSPI (HS-FS)

- Software/Application used        : sbl_ospi_multistage, ipc_rpmsg_echo, and HSM App Images
- Cores booted by stage1 SBL       : r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 269 KB
- Size of images loaded by stage2  : 270 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   17.625
SBL Stage1: Board_init                  |    0.089
SBL Stage1: Drivers_open                |    0.001
SBL Stage1: SBL Drivers_open            |    0.200
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: SBL Board_driversOpen       |    7.279
SBL Stage1: Sciclient Get Version       |    6.703
SBL Stage1: App_loadSelfcoreImage       |    5.690
SBL Stage1: App_waitForMcuPbist         |    0.003
----------------------------------------|--------------
SBL Stage1: Total time taken            |   37.594

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.943
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.299
SBL Stage2: SBL Drivers_open            |    0.751
SBL Stage2: SBL Board_driversOpen       |    0.488
SBL Stage2: App_loadHSMImage            |    3.716
SBL Stage2: App_loadMCUImage            |    4.611
SBL Stage2: App_loadA53Images           |    5.774
SBL Stage2: App_loadDSPImage            |   14.286
----------------------------------------|--------------
SBL Stage2: Total time taken            |   31.876

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~17 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC (HS-FS)

- Software/Application used        : sbl_emmc_multistage, ipc_rpmsg_echo and HSM App Images
- Cores booted by stage1 SBL       : r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 269 KB
- Size of images loaded by stage2  : 270 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   24.254
SBL Stage1: Board_init                  |    0.094
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   21.651
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |    6.715
SBL Stage1: PBIST Positive Tests        |    0.169
SBL Stage1: PBIST Negative Tests        |    0.441
SBL Stage1: App_loadSelfcoreImage       |    7.479
----------------------------------------|--------------
SBL Stage1: Total time taken            |   60.806

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.053
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.301
SBL Stage2: SBL Drivers_open            |   17.877
SBL Stage2: App_loadHSMImage            |    4.151
SBL Stage2: App_loadMCUImage            |    4.766
SBL Stage2: App_loadA53Images           |    5.222
SBL Stage2: App_loadDSPImage            |    5.820
----------------------------------------|--------------
SBL Stage2: Total time taken            |   40.195

- The emmc driver initialization is done as part of Drivers_open.

- Out of the ~17 ms taken for System Init is mostly attributed to DDR initialization.


# Datasheet {#DATASHEET_AM62LX_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Performance Numbers

### AM62LX Dhrystone Benchmark performance

Core : **a530-0**

Benchmarks                      | am62lx-evm    |
--------------------------------|---------------|
cpu_clock (MHz)                 |   1250        |
dhrystone_per_mhz (DMIPS/MHz)   |   2.8583      |
dhrystone_per_second            |   6277461.0   |

### AM62LX Interrupt Latency Benchmark performance

The latency measurements include IRQ entry handling latency + ISR + IRQ exit handling latency.

Core : **a530-0**

Benchmarks                      | am62lx-evm     |
--------------------------------|---------------|
cpu_clock (MHz)                 |   1250        |
interrupt latency (ns)          |   470         |

### AM62LX Coremark Pro Benchmark performance

Workload computed for **Single core**
Core : **a530-0**

Benchmark (worloads)             |  am62lx-evm       |
---------------------------------|-------------------|
cjpeg-rose7-preset               | 36.08             |
core                             | 0.25              |
linear_alg-mid-100x100-sp        | 14.55             |
loops-all-mid-10k-sp             | 0.62              |
nnet_test                        | 1.68              |
parser-125k                      | 5.12              |
radix2-big-64k                   | 16.23             |
sha-test                         | 73.04             |
zip-test                         | 25.04             |
Coremark-pro()(overall score)    | 748.07            |

### EMMC Performance
**a53 :**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 32.66		         | 46.04
 SDR50 | 4	            | 43.16		         | 47.35
 SDR50 | 6	            | 39.25		         | 46.27
 SDR50 | 32	            | 42.84		         | 47.40
 SDR50 | 40	            | 42.26		         | 47.41
 DDR50 | 1	            | 54.04		         | 85.31
 DDR50 | 4	            | 71.32		         | 89.91
 DDR50 | 6	            | 62.44		         | 89.65
 DDR50 | 32	            | 66.75		         | 90.11
 DDR50 | 40	            | 68.47		         | 90.14
 HS200 | 1	            | 88.03 		     | 167.96
 HS200 | 4	            | 131.61	         | 186.60
 HS200 | 6	            | 135.19		     | 185.43
 HS200 | 32	            | 130.06	         | 187.39
 HS200 | 40	            | 129.77		     | 187.55

### OSPI NOR Flash Performance
**a53 :**

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          6.49 ms
Fast Tuning Window          |          4.23 ms

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.41          |       0.78
      5          |        DAC        |        No         |        0.42          |       0.78
      10         |        DAC        |        No         |        0.42          |       0.78
      1          |        DAC        |        Yes        |        0.41          |       49.82
      5          |        DAC        |        Yes        |        0.42          |       49.84
      10         |        DAC        |        Yes        |        0.42          |       49.84

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.38           |       0.54
      5          |        DAC        |        No         |        0.39           |       0.54
      10         |        DAC        |        No         |        0.39           |       0.54
      1          |        DAC        |        Yes        |        0.38           |       6.25
      5          |        DAC        |        Yes        |        0.39           |       6.25
      10         |        DAC        |        Yes        |        0.39           |       6.25

 - Flash frequency: 133Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)   |    Read Speed(mbps)
-----------------|-------------------|-------------------|-----------------------|----------------------
      1          |        DAC        |        No         |        0.41           |       2.08
      5          |        DAC        |        No         |        0.42           |       2.08
      10         |        DAC        |        No         |        0.42           |       2.08
      1          |        DAC        |        Yes        |        0.41           |       245.40
      5          |        DAC        |        Yes        |        0.42           |       246.00
      10         |        DAC        |        Yes        |        0.42           |       246.07

 - Flash frequency: 166Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: enabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |        DAC        |        No         |        0.41          |       2.50
      5          |        DAC        |        No         |        0.42          |       2.50
      10         |        DAC        |        No         |        0.42          |       2.50
      1          |        DAC        |        Yes        |        0.41          |       325.22
      5          |        DAC        |        Yes        |        0.42          |       326.25
      10         |        DAC        |        Yes        |        0.42          |       326.38

 - Flash frequency: 25Mhz
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.41          |       31.30
      5          |       INDAC       |        No         |        0.42          |       31.31
      10         |       INDAC       |        No         |        0.42          |       31.31

 - Flash frequency: 50Mhz
 - Flash protocol: FLASH_CFG_PROTO_1S_1S_1S
 - Phy Condition: disabled

 Data Size(MiB)  |     READ MODE     |    DMA Enabled    |   Write Speed(mbps)  |    Read Speed(mbps)
-----------------|-------------------|-------------------|----------------------|----------------------
      1          |       INDAC       |        No         |        0.39          |       6.25
      5          |       INDAC       |        No         |        0.39          |       6.25
      10         |       INDAC       |        No         |        0.39          |       6.25

### CPSW Performance

For CPSW performance refer \ref enetlld_performance
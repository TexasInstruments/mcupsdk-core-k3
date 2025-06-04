# Datasheet {#DATASHEET_AM62LX_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Performance Numbers

### AM62LX Dhrystone Benchmark performance

Core : **a530-0**

Benchmarks                      | am62lx-evm     |
--------------------------------|---------------|
cpu_clock (MHz)                 |   1250        |
dhrystone_per_mhz (DMIPS/MHz)   |   2.8600      |
dhrystone_per_second            |   6281246.0   |

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

Benchmark (worloads)             |  am62lx-evm        |
---------------------------------|-------------------|
cjpeg-rose7-preset               | 36.08             |
core                             | 0.25              |
linear_alg-mid-100x100-sp        | 14.55             |
loops-all-mid-10k-sp             | 0.63              |
nnet_test                        | 1.68              |
parser-125k                      | 5.13              |
radix2-big-64k                   | 16.24             |
sha-test                         | 73.04             |
zip-test                         | 25.05             |
Coremark-pro()(overall score)    | 751.3             |

### EMMC Performance
**a53 :**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 41.35		         | 46.02
 SDR50 | 4	            | 42.17		         | 46.51
 SDR50 | 6	            | 38.31		         | 46.53
 SDR50 | 32	            | 40.57		         | 46.57
 SDR50 | 40	            | 40.28		         | 46.56
 DDR50 | 1	            | 69.78		         | 85.63
 DDR50 | 4	            | 73.23		         | 86.94
 DDR50 | 6	            | 73.54		         | 87.02
 DDR50 | 32	            | 66.75		         | 87.14
 DDR50 | 40	            | 68.47		         | 87.11
 HS200 | 1	            | 106.03		     | 171.36
 HS200 | 4	            | 70.93		         | 183.47
 HS200 | 6	            | 115.72		     | 183.87
 HS200 | 32	            | 99.89		         | 184.47
 HS200 | 40	            | 103.43		     | 184.32

### OSPI NOR Flash Performance
**a53 :**
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 0.44		        | 325.56
 5	           | 0.44		        | 326.33
 10	           | 0.44		        | 327.42

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          3.17 ms
Fast Tuning Window          |          0.96 ms

### CPSW Performance

For CPSW performance refer \ref enetlld_performance
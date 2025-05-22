# Datasheet {#DATASHEET_AM62LX_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Performance Numbers

### AM62LX Dhrystone Benchmark performance

Core : **a530-0**

Benchmarks                      | am62lx-sk     |
--------------------------------|---------------|
cpu_clock (MHz)                 |   1250        |
dhrystone_per_mhz (DMIPS/MHz)   |   2.8600      |
dhrystone_per_second            |   6281246.0   |

### AM62LX Interrupt Latency Benchmark performance

The latency measurements include IRQ entry handling latency + ISR + IRQ exit handling latency.

Core : **a530-0**

Benchmarks                      | am62lx-sk     |
--------------------------------|---------------|
cpu_clock (MHz)                 |   1250        |
interrupt latency (ns)          |   470         |

### AM62LX Coremark Pro Benchmark performance

Workload computed for **Single core**
Core : **a530-0**

Benchmark (worloads)             |  am62lx-sk        |
---------------------------------|-------------------|
cjpeg-rose7-preset               | 36.09             |
core                             | 0.25              |
linear_alg-mid-100x100-sp        | 14.55             |
loops-all-mid-10k-sp             | 0.62              |
nnet_test                        | 1.68              |
parser-125k                      | 5.12              |
radix2-big-64k                   | 16.67             |
sha-test                         | 73.05             |
zip-test                         | 25.09             |
Coremark-pro()(overall score)    | 750.97            |

### CPSW Performance

For CPSW performance refer \ref enetlld_performance
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

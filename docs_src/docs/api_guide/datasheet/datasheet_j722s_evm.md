# Datasheet {#DATASHEET_J722S_EVM}

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
R5F Compiler flags      | -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -mthumb -Wall -Werror -g -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function
R5F Linker flags        | -Wl,--diag_suppress=10063 -Wl,--priority -Wl,--ram_model -Wl,--reread_libs
Code Placement          | HSM RAM (For SBL), DDR (others)
Data Placement          | HSM RAM (For SBL), DDR (others)

## Performance Numbers

### Early CAN Response

CAN response is measured from MCU_PORz Reset to pulling the CAN-H line out of standby.

Device           | Measured Time (ms)
-----------------|----------------------------------------
J722S HS-FS      | 50.8

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
wkup-r5f0-0 | mcu-r5f0-0  |  1.26
wkup-r5f0-0 | main-r5f0-0 |  0.97
wkup-r5f0-0 | c75ss0      |  1.17
wkup-r5f0-0 | c75ss1      |  1.38

#### IPC RPMSG

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us)
------------|-------------|--------------|------------------------------
wkup-r5f0-0 | mcu-r5f0-0  | 4            | 0.924
wkup-r5f0-0 | mcu-r5f0-0  | 32           | 1.556
wkup-r5f0-0 | mcu-r5f0-0  | 64           | 2.240
wkup-r5f0-0 | mcu-r5f0-0  | 112          | 3.308
wkup-r5f0-0 | main-r5f0-0 | 4            | 0.781
wkup-r5f0-0 | main-r5f0-0 | 32           | 1.365
wkup-r5f0-0 | main-r5f0-0 | 64           | 2.012
wkup-r5f0-0 | main-r5f0-0 | 112          | 2.948
wkup-r5f0-0 | c75ss0      | 4            | 1.354
wkup-r5f0-0 | c75ss0      | 32           | 1.680
wkup-r5f0-0 | c75ss0      | 64           | 1.972
wkup-r5f0-0 | c75ss0      | 112          | 2.417
wkup-r5f0-0 | c75ss1      | 4            | 1.380
wkup-r5f0-0 | c75ss1      | 32           | 1.693
wkup-r5f0-0 | c75ss1      | 64           | 2.002
wkup-r5f0-0 | c75ss1      | 112          | 2.440

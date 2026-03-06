# Release Notes 12.00.00 {#RELEASE_NOTES_12_00_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

\attention FreeRTOS SDK on A53 is provided as is for customers as a reference to implement/validate on their own SW Stack & OS. TI will not support these features on the E2E forum as these are not part of the FreeRTOS SDK product. If these features need to be productized, TI can recommend third parties who can help.

## Device and Validation Information

SOC    | Supported CPUs | EVM                                                    | Host PC
-------|----------------|--------------------------------------------------------|-----------------------------------
AM62L  | A53            | @VAR_BOARD_NAME EVM (referred to as am62lx-evm in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release
\note Update of OSPI tuning algorithm on this SDK causes increase in tuning time. Refer \ref OSPI_DATA_SHEET

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
 -                                                                                             | -

## Dependent Tools and Compiler Information

Tools/Components        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | A53                      | 20.3.1
SysConfig               | A53                      | 1.24.2, build 4234
GCC AARCH64             | A53                      | 9.2-2019.12
FreeRTOS Kernel         | A53                      | 11.1.0
TF-A                    | A53                      | 11.00.13

## SDK Components

### TIFS

<table>
    <tr>
        <td>Version</td>
        <td>11.00.12</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_00_12/release_notes/release_notes.html)</td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_00_12/1_intro/TISCI.html)</td>
    </tr>
</table>

## Key Features

### OS Kernel

OS              | Supported CPUs | SysConfig Support
----------------|----------------|-------------------
FreeRTOS Kernel | A53            | NA
FreeRTOS POSIX  | A53            | NA
No RTOS         | A53            | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs  | SysConfig Support | OS support
------------------|-----------------|-------------------|------------------
Address Translate | A53             | Yes               | FreeRTOS, NORTOS
Cache             | A53             | Yes               | FreeRTOS, NORTOS
Clock             | A53             | Yes               | FreeRTOS, NORTOS
CycleCounter      | A53             | NA                | FreeRTOS, NORTOS
Debug             | A53             | Yes               | FreeRTOS, NORTOS
Heap              | A53             | NA                | FreeRTOS, NORTOS
Hwi               | A53             | Yes               | FreeRTOS, NORTOS
MMU               | A53             | Yes               | FreeRTOS, NORTOS
Semaphore         | A53             | NA                | FreeRTOS, NORTOS
Task              | A53             | NA                | FreeRTOS
Timer             | A53             | Yes               | FreeRTOS, NORTOS

### SOC Device Drivers

Peripheral        | Supported CPUs  | SysConfig Support
------------------|-----------------|-------------------
ADC               | A53             | Yes
DSS               | A53             | Yes
ECAP              | A53             | Yes
EPWM              | A53             | Yes
EQEP              | A53             | Yes
GPIO              | A53             | Yes
GTC               | A53             | Yes
I2C               | A53             | Yes
MCAN              | A53             | Yes
MCASP             | A53             | Yes
MCSPI             | A53             | Yes
MMCSD             | A53             | Yes
OSPI              | A53             | Yes
UDMA              | A53             | Yes
UART              | A53             | Yes
WDT               | A53             | Yes

### Networking

Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested                                                                                                                                                                    | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------
LwIP                        | A53            | YES               | FreeRTOS    |  TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping | Other LwIP features
Ethernet driver (ENET)      | A53            | YES               | FreeRTOS    |  Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW  | RMII mode

## Fixed Issues

<table>
<tr>
   <th> ID
   <th> Head Line
   <th> Module
</tr>
<tr>
    <td> -
    <td> -
    <td> -
</tr>
</table>

## Known Issues


<table>
<tr>
   <th> ID
   <th> Head Line
   <th> Module
</tr>
<tr>
    <td> -
    <td> -
    <td> -
</tr>
</table>

## Upgrade and Compatibility Information
This section lists changes which could affect user applications developed using older SDK versions.
Read this carefully to see if you need to do any changes in your existing application when migrating to this SDK version relative to
previous SDK version. Also refer to older SDK version release notes to see changes in
earlier SDKs.


The below table captures the list of migration document sections when migrating from one version to another.
The migration for a partcluar module will be applicable, if you are migrating from older version listed to
newer version listed on the table below.


Module       | Migration guide                              | Older version  | Newer version
-------------|----------------------------------------------|----------------| -----------------
OSPI         |  \ref OSPI_MIGRATION_GUIDE     &zwj;         |   <= 11.01.00  | >= 11.02.00
Watchdog     |  \ref WATCHDOG_12_0_MIGRATION  &zwj;         |   <= 11.02.00  | >= 12.00.00

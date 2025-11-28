# Release Notes 11.02.00 {#RELEASE_NOTES_11_02_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

SOC    | Supported CPUs              | EVM                                                    | Host PC
-------|-----------------------------|--------------------------------------------------------|-----------------------------------
AM62P  | MCU R5F, WKUP R5F           | @VAR_BOARD_NAME EVM (referred to as am62px-sk in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
TBD                                                                                            | TBD

### Experimental Features {#EXPERIMENTAL_FEATURES}

\attention Features listed below are early versions and should be considered as "experimental".
\attention Users can evaluate the feature, however the feature is not fully tested at TI side.
\attention TI would not support these feature on public e2e.
\attention Experimental features will be enabled with limited examples and SW modules.

Feature                                                                             | Module
------------------------------------------------------------------------------------|--------------------------
Ethernet traffic sharing accross multiple cores, called Ethernet Firmware           | Networking

## Dependent Tools and Compiler Information
\attention It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recommended and may cause TIFS/ DM functionality to break.

Tools/Components        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, WKUP-R5F        | 20.3.1
SysConfig               | MCU-R5F, WKUP-R5F        | 1.24.2, build 4234
TI ARM CLANG            | MCU-R5F, WKUP-R5F        | 4.0.1.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F        | 11.1.0

## SDK Components

### SYSFW / TIFS

<table>
    <tr>
        <td>Version</td>
        <td>11.01.05d</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_01_05/release_notes/release_notes.html)</td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_01_05/1_intro/TISCI.html)</td>
    </tr>
</table>

## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, WKUP-R5F         | NA
FreeRTOS POSIX  | MCU-R5F                   | NA
No RTOS         | MCU-R5F, WKUP-R5F         | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs            | SysConfig Support | OS support
------------------|---------------------------|-------------------|------------------
Address Translate | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
Cache             | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
Clock             | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS, NORTOS
Debug             | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
Heap              | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS, NORTOS
Hwi               | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
MPU               | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
Semaphore         | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS, NORTOS
Task              | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS
Timer             | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | WKUP-R5F       | Yes               | Yes         |   Yes       | NORTOS
EMMC      | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS
UART      | WKUP-R5F       | Yes               | NA          |   No        | NORTOS

### SDL

SDL Module       | Supported CPUs | SysConfig Support
-----------------|----------------|-------------------
MCRC             |MCU-R5F         | No
ESM              |MCU-R5F         | No
VTM              |MCU-R5F         | No
DCC              |MCU-R5F         | No
ECC              |MCU-R5F         | No
RTI              |MCU-R5F         | No
POK              |MCU-R5F         | No
STOG             |MCU-R5F         | No
MTOG             |MCU-R5F         | No
PBIST            |MCU-R5F         | No
LBIST            |MCU-R5F         | No
ROM_CHECKSUM     |MCU-R5F         | No

### Networking

Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested                                                                                                                                                                    | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------
TSN                         | WKUP-R5F       | NO                | FreeRTOS    | gPTP IEEE 802.1 AS-2020 compliant gPTP stack, End Nodes and Bridge mode support, YANG data model configuration  | Multi-Clock Domain
LwIP                        | WKUP-R5F       | YES               | FreeRTOS    | TCP/UDP IP networking stack with and without checksum offload enabled, TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs and raw APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping, LwIP bridge, shared memory driver  | Other LwIP features
Ethernet driver (ENET)      | WKUP-R5F       | YES               | FreeRTOS    | Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW, Strapped PHY (Early Ethernet), cut through switch on CPSW  | RMII mode

### SOC Device Drivers

\note See the updated MCASP usage guidelines in \ref DRIVERS_MCASP_PAGE for changes in
MCASP driver

<table>
    <tr>
        <th>Peripheral</th>
        <th>Domain</th>
        <th>Supported CPUs</th>
        <th>SysConfig Support</th>
    </tr>
    <tr>
        <td>DDR</td>
        <td>Main</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>ECAP</td>
        <td>Main</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>EPWM</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>DSS</td>
        <td>Main</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>GPIO</td>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCAN</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCASP</td>
        <td>Main</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
</table>



## Fixed Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/TBD, TBD}
    <td> TBD
    <td> TBD
    <td> 11.01.00
</tr>
</table>

## Known Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Reported in release
    <th> Workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/TBD, TBD}
    <td> TBD
    <td> TBD
    <td> 11.00.00
    <td> TBD
</tr>
</table>

## Limitations

<table>
<tr>
    <th> S.No
    <th> Head Line
    <th> Module
</tr>
<tr>
    <td> 1
    <td> The **ROM** startup model for runtime initializations in TI ARM CLANG is not supported/tested in the SDK
    <td> NA
</tr>
<tr>
    <td> 2
    <td> LPM is not supported with SBL boot flow. It is supported only with SPL boot flow.
    <td> Bootloader
</tr>
<tr>
    <td> 3
    <td> The EVM is limited to only one MAC address in the EEPROM, applications requiring multiple MAC addresses should enable and configure manual MAC address entry in Sysconfig.
    <td> Networking
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


Module       | Migration guide                        | Older version  | Newer version
-------------|----------------------------------------|----------------| -----------------
Bootloader   |  \ref BOOTLOADER_MIGRATION_GUIDELINE  &zwj; |   <= 10.01.00  | >= 11.00.00
NETWORKING   |  \ref enet_mcupsdk_update       &zwj;       |   <= 11.01.00  | >= 11.02.00

### Networking

<table>
<tr>
    <th> Module
    <th> Affected API
    <th> Change
</tr>
<tr>
    <td> TSN
    <td> `notify_linkchange`
    <td> `notify_linkchange` function is renamed to `cb_lld_notify_linkchange`,
          include path `<tsn_combase/tilld/cb_lld_ethernet.h>` in the file that uses `cb_lld_notify_linkchange`.
</tr>
</table>
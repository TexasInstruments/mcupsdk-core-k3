# Release Notes 12.00.00 {#RELEASE_NOTES_12_00_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

\cond SOC_AM62DX
SOC    | Supported CPUs              | EVM                                                    | Host PC
-------|-----------------------------|--------------------------------------------------------|-----------------------------------
AM62Dx | MCU R5F, WKUP R5F, A53, C75 | @VAR_BOARD_NAME EVM (referred to as am62dx-evm in code)| Windows 10 64b or Ubuntu 22.04 64b
\endcond

## Features Added in This Release
\note Update of OSPI tuning algorithm on this SDK causes increase in tuning time. Refer \ref OSPI_DATA_SHEET

Feature                                                                                      | Module
---------------------------------------------------------------------------------------------|-----------------------------------
 PADCFG drive strength adjustment through SYSCFG                                             | Pinmux
 Support de-interleave of data on MCASP                                                      | MCASP
 LBIST/PBIST initiated in SBL EMMC                                                           | SBL
 Enable WKUP-R5F ATCM                                                                        | SBL
 Support PMIC driver for TPS6522X                                                            | PMIC
 Watchdog support for DM R5/WKUP-R5F                                                         | WDT
 Save/Restore of FPU registers on context switch enabled by default on A53                   | FreeRTOS
 MMCSD drive strength as a configurable option                                               | MMCSD
 Add 8S-8S-8S protocol support                                                               | OSPI
 Route SecProxy event for MCU cores                                                          | DM
 Interrupt mode in SCIClient                                                                 | SCI Client
 Move task stack allocation to application layer                                             | SCI Server
 Add Linux sigchain biquad cascade example                                                   | TISP

### Experimental Features {#EXPERIMENTAL_FEATURES_12_00_00}

\attention Features listed below are early versions and should be considered as "experimental".
\attention Users can evaluate the feature, however the feature is not fully tested at TI side.
\attention TI would not support these feature on public e2e.
\attention Experimental features will be enabled with limited examples and SW modules.

Feature                                                                    | Module
---------------------------------------------------------------------------|--------------------------
Ethernet traffic sharing across multiple cores, called Ethernet Firmware   | Networking
C++ Support                                                                | NA

## Dependent Tools and Compiler Information
\attention It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.

Tools                   | Supported CPUs             | Version
------------------------|----------------------------|-----------------------
Code Composer Studio    | MCU-R5F, C75               | 20.3.1
SysConfig               | MCU-R5F, DM-R5F, C75       | 1.24.2, build 4234
TI ARM CLANG            | MCU-R5F, WKUP-R5F          | 4.0.1.LTS
GCC AARCH64             | A53                        | 9.2-2019.12
C7000-CGT               | C75                        | 5.0.0.LTS
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F, C75, A53| 11.1.0

## SDK Components

### SYSFW / TIFS

<table>
    <tr>
        <td>Version</td>
        <td>12.00.02</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/12_00_02/release_notes/release_notes.html)</td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/12_00_02/1_intro/TISCI.html)</td>
    </tr>
</table>

## Key Features

### OS Kernel

OS              | Supported CPUs              | SysConfig Support
----------------|-----------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, WKUP-R5F, A53, C75 | NA
FreeRTOS POSIX  | MCU-R5F, A53                | NA
FreeRTOS SMP    | A53                         | NA
No RTOS         | MCU-R5F, WKUP-R5F, A53      | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs              | SysConfig Support | OS support
------------------|-----------------------------|-------------------|------------------
Address Translate | MCU-R5F, WKUP-R5F           | Yes               | FreeRTOS, NORTOS
Cache             | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
Clock             | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, WKUP-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Debug             | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
Heap              | MCU-R5F, WKUP-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Hwi               | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
MPU               | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
Semaphore         | MCU-R5F, WKUP-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Task              | MCU-R5F, WKUP-R5F, A53, C75 | NA                | FreeRTOS
Timer             | MCU-R5F, WKUP-R5F, A53      | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | WKUP-R5F       | Yes               | No          |   Yes       | NORTOS
EMMC      | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS
UART      | WKUP-R5F       | Yes               | NA          |   No        | NORTOS

### Networking
Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested  | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------|-------------------------
TSN                         | R5F       | NO                | FreeRTOS    | gPTP IEEE 802.1 AS-2020 compliant gPTP stack, End Nodes and Bridge mode support, YANG data model configuration, IEEE 1722 compliant AVTP Stack | Multi-Clock Domain
LwIP                        | R5F       | YES               | FreeRTOS    | TCP/UDP IP networking stack with and without checksum offload enabled, TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs and raw APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping, LwIP bridge, shared memory driver  | Other LwIP features
Ethernet driver (ENET)      | R5F       | YES               | FreeRTOS    | Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW, cut through switch on CPSW  | RMII mode

### SOC Device Drivers

For SOC device driver support information per CPU, refer to \ref BUILDSHEET.

### Board Device Drivers

Peripheral    | Supported CPUs                    | SysConfig Support
--------------|-----------------------------------|-------------------
EEPROM        | MCU-R5F, WKUP-R5F, A53, C75      | Yes
Ethernet PHY  | MCU-R5F, WKUP-R5F, A53, C75      | Yes
Flash         | MCU-R5F, WKUP-R5F, A53            | Yes
LED           | MCU-R5F, A53, C75                 | Yes
PMIC          | MCU-R5F                           | Yes
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

## Fixed Issues

<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-245, EXT_SITMPUSW-245}
    <td> MCU+ SDK LPDDR4 Driver starts DDR Training/Leveling Sequence twice
    <td> DDR
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-309, EXT_SITMPUSW-309}
    <td> LPM: Spurious wake up on MCU only mode
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-312, EXT_SITMPUSW-312}
    <td> Incorrect context description of SCICLIENT_CONTEXT_DM2TIFS
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-251, EXT_SITMPUSW-251}
    <td> MCU+ SDK Example Projects using incorrect ARMv7 MPU Attributes for Peripheral Register Region
    <td> Examples
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-301, EXT_SITMPUSW-301}
    <td> OSPI_norFlashInit1s1s1s has an implementation of wait for 500 milliseconds instead of microseconds
    <td> Flash
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-304, EXT_SITMPUSW-304}
    <td> AM62x: Critical section protection not added in vPortTimerTickHandler for A53
    <td> FreeRTOS
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-282, EXT_SITMPUSW-282}
    <td> Sysconfig not generating code for GPIO Trigger
    <td> GPIO
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-279, EXT_SITMPUSW-279}
    <td> I2C close is not working properly during error conditions
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-299, EXT_SITMPUSW-299}
    <td> IPC notify: Null check is not handled properly
    <td> IPC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-277, EXT_SITMPUSW-277}
    <td> MCASP: tx.evtCtl Used Instead of rx.evtCtl for REVTCTL Configuration
    <td> MCASP
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-276, EXT_SITMPUSW-276}
    <td> MCASP: intCfgTx.intrNum Used Instead of intCfgRx.intrNum in Interrupt Check
    <td> MCASP
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-114, EXT_SITMPUSW-114}
    <td> MMCSD_enableBootPartition implements two mutually exclusive concepts as one function
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-295, EXT_SITMPUSW-295}
    <td> Flash Close Logic Requires OSPI Handle to be reset to 1S-1S-1S
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-280, EXT_SITMPUSW-280}
    <td> OSPI Indac Mode Should Check for odd bytes
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-292, EXT_SITMPUSW-292}
    <td> Bootloader_socOpenFirewalls is called before System_init in the SBLs
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-281, EXT_SITMPUSW-281}
    <td> UART: UART_open fails when NULL argument is passed as UART_Params argument
    <td> UART
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-214, EXT_SITMPUSW-214}
    <td> WDT: Hang due to no valid argument check in APIs
    <td> Watchdog
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-13267, EXT_EP-13267}
    <td> SDL ESM: Wrong instance argument in SDL_ESM_loInterruptHandler causing misidentification of ESM0 interrupts
    <td> SDL-ESM
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-153, EXT_SITMPUSW-153}
    <td> MCU+ SDK CCS Project Build Generates Invalid/Redundant Boot Image Files
    <td> Build
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-221, EXT_SITMPUSW-221}
    <td> DebugP_log does not work when tried from multiple cores in SMP mode.
    <td> DPL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-219, EXT_SITMPUSW-219}
    <td> AM62D/A/275: C7x `portGET_RUN_TIME_COUNTER_VALUE` API uses hard coded CPU Freq
    <td> FreeRTOS
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-224, EXT_SITMPUSW-224}
    <td> Mcasp :  Not working on interrupt mode
    <td> MCASP
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-222, EXT_SITMPUSW-222}
    <td> MMCSD field Card Type is not ordered logically in the Sysconfig
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-220, EXT_SITMPUSW-220}
    <td> SBL_SD bootloaders report incorrect boot image size
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-214, EXT_SITMPUSW-214}
    <td> Spinlock: Hang in multithread test cases due to HW interrupt config
    <td> Spinlock
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-214, EXT_SITMPUSW-214}
    <td> Spinlock: Missing NULL Pointer Validation for Base Address Parameter in Spinlock APIs
    <td> Spinlock
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-324, EXT_SITMPUSW-324}
    <td> UART_udmaIsrTx does not handles continuous Callbacks properly
    <td> UART
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12276, EXT_EP-12276}
    <td> ECC: Firewall related aggregators failures
    <td> SDL-ECC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12283, EXT_EP-12283}
    <td> ECC aggregators CPSW0, CSI RX are failing on AM62A and CPSW0 on AM62D.
    <td> SDL-ECC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-13265, EXT_EP-13265}
    <td> MCU R5 ECC Aggr init fails when MCU LBIST is enabled in bootloader
    <td> SDL-LBIST
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12280, EXT_EP-12280}
    <td> Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F
    <td> SDL-LBIST
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
Bootloader   |  \ref BOOTLOADER_MIGRATION_GUIDELINE  &zwj;  |   <= 10.01.00  | >= 11.00.00
NETWORKING   |  \ref enet_mcupsdk_update       &zwj;        |   <= 11.01.00  | >= 11.02.00
MCASP        |  \ref MCASP_11_2_MIGRATION     &zwj;         |   <= 11.01.00  | >= 11.02.00
OSPI         |  \ref OSPI_MIGRATION_GUIDE     &zwj;         |   <= 11.01.00  | >= 11.02.00
Watchdog     |  \ref WATCHDOG_12_0_MIGRATION  &zwj;         |   <= 11.02.00  | >= 12.00.00
SCI Server   |  \ref SCISERVER_12_0_MIGRATION  &zwj;        |   <= 11.02.00  | >= 12.00.00
SBL Linker   |  \ref SBL_LINKER_12_0_MIGRATION  &zwj;      |   <= 11.02.00  | >= 12.00.00

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


# Release Notes 12.00.00 {#RELEASE_NOTES_12_00_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

SOC    | Supported CPUs              | EVM                                                     | Host PC
-------|-----------------------------|---------------------------------------------------------|-----------------------------------
AM275x | R5F, C75                    | @VAR_BOARD_NAME (referred to as am275x-evm in code) | Windows 10 64b or Ubuntu 22.04 64b

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
 Example for Memory latency benchmarking on R5F and C7x                                      | Becnhmarks
 MMCSD drive strength as a configurable option                                               | MMCSD
 Add 8S-8S-8S protocol support                                                               | OSPI
 Route SecProxy event for MCU cores                                                          | DM
 Interrupt mode in SCIClient                                                                 | SCI Client
 Move task stack allocation to application layer                                             | SCI Server
 Ethernet based uniflash support                                                             | Uniflash, Ethernet
 C7x example for HyperRAM                                                                    | Hyper RAM

## Dependent Tools and Compiler Information

Tools/ Component        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | R5F, C75                 | 20.3.1
SysConfig               | R5F, C75                 | 1.24.2, build 4234
TI ARM CLANG            | R5F                      | 4.0.1.LTS
C7000-CGT               | C75                      | 5.0.0.LTS
FreeRTOS Kernel         | R5F, C75                 | 11.1.0

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

### Experimental Features {#EXPERIMENTAL_FEATURES}
\attention Features listed below are early versions and should be considered as "experimental".
\attention Users can evaluate the feature, however the feature is not fully tested at TI side.
\attention TI would not support these feature on public e2e.
\attention Experimental features will be enabled with limited examples and SW modules.

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
C++ support                                                         | NA

### Eval Features

\attention Features listed below are early versions and gone through limited testing.

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
AUDIOLIB TISP                                                       | All modules in AUDIOLIB, TISP

## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | R5F, C75                  | NA
FreeRTOS POSIX  | R5F, C75                  | NA
No RTOS         | R5F                       | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs | SysConfig Support | OS support
------------------|----------------|-------------------|------------------
Address Translate | R5F            | Yes               | FreeRTOS, NORTOS
Cache             | R5F, C75       | Yes               | FreeRTOS, NORTOS
Clock             | R5F, C75       | Yes               | FreeRTOS, NORTOS
CycleCounter      | R5F, C75       | NA                | FreeRTOS, NORTOS
Debug             | R5F, C75       | Yes               | FreeRTOS, NORTOS
Heap              | R5F, C75       | NA                | FreeRTOS, NORTOS
Hwi               | R5F, C75       | Yes               | FreeRTOS, NORTOS
MPU               | R5F, C75       | Yes               | FreeRTOS, NORTOS
Semaphore         | R5F, C75       | NA                | FreeRTOS, NORTOS
Task              | R5F, C75       | NA                | FreeRTOS
Timer             | R5F            | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | WKUP-R5F       | Yes               | Yes         |   Yes       | NORTOS
EMMC      | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS
UART      | WKUP-R5F       | Yes               | NA          |   No        | NORTOS
SD        | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS


### Networking
Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested  | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------|-------------------------
TSN                         | R5F       | NO                | FreeRTOS    | gPTP IEEE 802.1 AS-2020 compliant gPTP stack, End Nodes and Bridge mode support, YANG data model configuration, IEEE 1722 compliant AVTP Stack | Multi-Clock Domain
LwIP                        | R5F       | YES               | FreeRTOS    | TCP/UDP IP networking stack with and without checksum offload enabled, TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs and raw APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping, LwIP bridge, shared memory driver  | Other LwIP features
Ethernet driver (ENET)      | R5F       | YES               | FreeRTOS    | Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW, cut through switch on CPSW  | RMII mode

### SOC Device Drivers

\note See the updated MCASP usage guidelines in \ref DRIVERS_MCASP_PAGE for changes in
MCASP driver

Peripheral | Supported CPUs          | SysConfig Support
-----------|-------------------------|-------------------
ADC        | R5F                     | YES
AASRC      | R5F, C7X                | YES
ECAP       | R5F, C7X                | YES
EPWM       | R5F, C7X                | YES
FLC        | R5F                     | YES
GPIO       | R5F, C7X                | YES
I2C        | R5F, C7X                | YES
IPC        | R5F, C7X                | YES
MCAN       | R5F                     | YES
MCASP      | R5F, C7X                | YES
MCSPI      | R5F, C7X                | YES
MMCSD      | R5F, WKUP-R5F, C7X      | YES
OSPI       | R5F, WKUP-R5F, C7X      | YES
Pinmux     | R5F, C7X                | YES
PMU        | R5F, WKUP-R5F           | YES
RL2        | R5F                     | YES
RTC        | R5F, C7X                | YES
SOC        | R5F, C7X                | YES
SCI Client | R5F, C7X                | YES
Spinlock   | R5F, C7X                | YES
UART       | R5F, C7X                | YES
UDMA       | R5F, C7X                | YES
WDT        | R5F, WKUP-R5F, C7X      | YES


### Board Device Drivers

Peripheral    | Supported CPUs | SysConfig Support
--------------|----------------|-------------------
EEPROM        | R5F            | Yes
Ethernet PHY  | R5F            | Yes
Flash         | R5F, WKUP-R5F, C75  | Yes
HyperRAM      | R5F, WKUP-R5F, C75  | Yes
LED           | R5F, C75       | Yes
PMIC          | R5F            | Yes

### SDL

SDL Module       | Supported CPUs | SysConfig Support
-----------------|----------------|-------------------
MCRC             |  R5F           | No
ESM              |  R5F           | No
VTM              |  R5F           | No
DCC              |  R5F           | No
ECC              |  R5F           | No
RTI              |  R5F           | No
POK              |  R5F           | No
PBIST            |  R5F           | No
LBIST            |  R5F           | No
ROM_CHECKSUM     |  R5F           | No


\note This is BQ release for SDL. FSQ release will be provided in next release. \n

## Fixed Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-308, EXT_SITMPUSW-308}
    <td> AASRC sysconfig bug: Example code build fails when Tx/Rx loopjob buffer is disabled
    <td> ASRC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-285, EXT_SITMPUSW-285}
    <td> AASRC driver bug: AASRC_MAX_OUT_FIFO_THRESHOLD set to 16U
    <td> ASRC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-290, EXT_SITMPUSW-290}
    <td> TX macro (AASRC_TX_DMA_TR_COUNT) used inside AASRC_udmaIsrRx (RX function)
    <td> ASRC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-286, EXT_SITMPUSW-286}
    <td> AM275: RM boardcfg changes are not taking effect
    <td> Build
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-282, EXT_SITMPUSW-282}
    <td> Sysconfig not generating code for GPIO Trigger
    <td> GPIO
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-311, EXT_SITMPUSW-311}
    <td> AM275x: Not able to add instance for wkup-r5 core
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-279, EXT_SITMPUSW-279}
    <td> I2C close is not working properly during error conditions
    <td> I2C
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-249, EXT_SITMPUSW-249}
    <td> 2 C7x cores ( c7x_0 and c7x_1 ) in AM275 are not able to run 2 different McASP instances
    <td> MCASP
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-296, EXT_SITMPUSW-296}
    <td> Fix issues with log in sbl_jtag_uniflash
    <td> SBL
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-289, EXT_SITMPUSW-289}
    <td> Uniflash script fails when trying to erase sector or size 4MB
    <td> Uniflash
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-326, EXT_SITMPUSW-326}
    <td> AASRC - AASRC channel data gets shifted when c7x workload is high and multiple mcasp instances are used
    <td> AASRC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-153, EXT_SITMPUSW-153}
    <td> MCU+ SDK CCS Project Build Generates Invalid/Redundant Boot Image Files
    <td> Build
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-120, EXT_SITMPUSW-120}
    <td> AM62A/AM275x: C7x task size/alignment should be 8KB (not 16KB)
    <td> C7X
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-261, EXT_SITMPUSW-261}
    <td> AM275x FreeRTOS SDK: The CycleCounterP_getCount32 for R5F_0_0 is not accurate
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12282, EXT_EP-12282}
    <td> AM275x: ECC: Some of the aggregators are failing on AM275x
    <td> SDL-ECC
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
</table>

## Upgrade and Compatibility Information
This section lists changes which could affect user applications developed using older SDK versions.
Read this carefully to see if you need to do any changes in your existing application when migrating to this SDK version relative to
previous SDK version. Also refer to older SDK version release notes to see changes in
earlier SDKs.


The below table captures the list of migration document sections when migrating from one version to another.
The migration for a partcluar module will be applicable, if you are migrating from older version listed to
newer version listed on the table below.

<table>
<tr>
    <th> Module
    <th> Migration guide
    <th> Older version
    <th> Newer version
</tr>
<tr>
    <td> Bootloader
    <td> \ref BOOTLOADER_MIGRATION_GUIDELINE
    <td> <= 10.01.00
    <td> >= 11.00.00
</tr>
<tr>
    <td> NETWORKING
    <td> \ref enet_mcupsdk_update
    <td> <= 11.01.00
    <td> >= 11.02.00
</tr>
<tr>
    <td> OSPI
    <td> \ref OSPI_MIGRATION_GUIDE
    <td> <= 11.01.00
    <td> >= 11.02.00
</tr>
<tr>
    <td> Watchdog
    <td> \ref WATCHDOG_12_0_MIGRATION
    <td> <= 11.02.00
    <td> >= 12.00.00
</tr>
<tr>
    <td> SCI Server
    <td> \ref SCISERVER_12_0_MIGRATION
    <td> <= 11.02.00
    <td> >= 12.00.00
</tr>
</table>

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


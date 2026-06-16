# Release Notes 12.00.00 {#RELEASE_NOTES_12_00_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.

\attention MCU+SDK on A53 is provided as is for customers as a reference to implement/validate on their own SW Stack & OS. TI will not support these features on the E2E forum as these are not part of the MCU+SDK product. If these features need to be productized, TI can recommend third parties who can help.

## Device and Validation Information


SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62x  | M4F, R5F, A53   | SK-AM62 (referred as am62x-sk in code), SK-AM62-LP (referred as am62x-sk-lp in code), SK-AM62-SIP (referred as am62x-sip-sk in code) | Windows 10 64b or Ubuntu 22.04 64b


## Features Added in This Release

\note Update of OSPI tuning algorithm on this SDK causes increase in tuning time. Refer \ref OSPI_DATA_SHEET

\attention DeepSleep low power mode (LPM) is not supported if the DM R5 is used for a general purpose application. This is because when the SoC goes to any LPM, the context of peripherals used by DM R5 will be lost. To use DM R5 for a general purpose application, disable LPM support. Refer \ref DISABLE_LPM to know how to disable LPM.

Feature                                                                                      | Module
---------------------------------------------------------------------------------------------|-----------------------------------
 PADCFG drive strength adjustment through SYSCFG                                             | Pinmux
 LBIST/PBIST initiated in SBL EMMC                                                           | SBL
 Enable WKUP-R5F ATCM                                                                        | SBL
 Watchdog support for DM R5/WKUP-R5F                                                         | WDT
 Save/Restore of FPU registers on context switch enabled by default on A53                   | FreeRTOS
 MMCSD drive strength as a configurable option                                               | MMCSD
 Add 8S-8S-8S protocol support                                                               | OSPI
 Route SecProxy event for MCU cores                                                          | DM
 Interrupt mode in SCIClient                                                                 | SCI Client
 Move task stack allocation to application layer                                             | SCI Server
 Add WFI in MCU only mode to save power                                                      | LPM

## Dependent Tools and Compiler Information

\attention It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.

Tools/Components        | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | M4F, R5F, A53  | 20.3.1
SysConfig               | M4F, R5F, A53  | 1.24.2, build 4234
TI ARM CLANG            | M4F, R5F       | 4.0.1.LTS
GCC AARCH64             | A53            | 9.2-2019.12
FreeRTOS Kernel         | M4F, R5F, A53  | 11.1.0

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

OS              | Supported CPUs  | SysConfig Support
----------------|-----------------|-------------------
FreeRTOS Kernel | M4F, R5F, A53   | NA
FreeRTOS POSIX  | M4F, A53        | NA
No RTOS         | M4F, R5F, A53   | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs  | SysConfig Support | OS support
------------------|-----------------|-------------------|------------------
Address Translate | M4F, R5F        | Yes               | FreeRTOS, NORTOS
Cache             | R5F, A53        | Yes               | FreeRTOS, NORTOS
Clock             | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
CycleCounter      | M4F, R5F, A53   | NA                | FreeRTOS, NORTOS
Debug             | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
Heap              | M4F, R5F, A53   | NA                | FreeRTOS, NORTOS
Hwi               | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
MPU               | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
Semaphore         | M4F, R5F, A53   | NA                | FreeRTOS, NORTOS
Task              | M4F, R5F, A53   | NA                | FreeRTOS
Timer             | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | R5F            | Yes               | Yes         |   Yes       | NORTOS
OSPI NAND | R5F            | Yes               | Yes         |   Yes       | NORTOS
EMMC      | R5F            | Yes               | NA          |   NA        | NORTOS
UART      | R5F            | Yes               | NA          |   No        | NORTOS

### Networking

Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested                                                                                                                                                                    | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------
TSN                         | A53            | NO                | FreeRTOS    | gPTP IEEE 802.1 AS-2020 compliant gPTP stack, End Nodes and Bridge mode support, YANG data model configuration  | Multi-Clock Domain
LwIP                        | A53            | YES               | FreeRTOS    | TCP/UDP IP networking stack with and without checksum offload enabled, TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs and raw APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping, LwIP bridge, shared memory driver  | Other LwIP features
Ethernet driver (ENET)      | A53            | YES               | FreeRTOS    | Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW, Strapped PHY (Early Ethernet), cut through switch on CPSW  | RMII mode

### SOC Device Drivers

For SOC device driver support information per CPU, refer to \ref BUILDSHEET.

### Board Device Drivers

Peripheral    | Supported CPUs | SysConfig Support
--------------|----------------|-------------------
EEPROM        | A53            | Yes
Ethernet PHY  | A53            | Yes
Flash         | R5F, A53       | Yes
LED           | M4F, R5F, A53  | Yes

### Software Diagnostic Library (SDL)

SDL Module   | Supported CPUs | SysConfig Support
-------------|----------------|-------------------
ESM          | M4F, R5F       | No
MCRC         | M4F, R5F       | No
RTI          | M4F, R5F       | No
DCC          | M4F, R5F       | No
VTM          | M4F, R5F       | No
STOG         | M4F, R5F       | No
PBIST        | M4F, R5F       | No
MTOG         | M4F            | No
POK          | M4F, R5F       | No
ECC          | M4F, R5F       | No
LBIST        | M4F            | No
ROM Checksum | R5F            | No

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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-293, EXT_SITMPUSW-293}
    <td> Sciclient driver uses incorrect context for the TISCI_MSG_KEYRING_IMPORT
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-309, EXT_SITMPUSW-309}
    <td> LPM: Spurious wake up on MCU only mode
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-303, EXT_SITMPUSW-303}
    <td> DM does not handle NACK properly for LPM msgs and RM board config msg
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-291, EXT_SITMPUSW-291}
    <td> Wait for Status mechanism via Sciclient API call fails during self reset
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-312, EXT_SITMPUSW-312}
    <td> Incorrect context description of SCICLIENT_CONTEXT_DM2TIFS
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-288, EXT_SITMPUSW-288}
    <td> LPM: Unable to enter LPM in Interrupt Mode
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-251, EXT_SITMPUSW-251}
    <td> MCU+ SDK Example Projects using incorrect ARMv7 MPU Attributes for Peripheral Register Region
    <td> Examples
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-297, EXT_SITMPUSW-297}
    <td> Flash Params Not Reflected In Syscfg
    <td> FLASH
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-306, EXT_SITMPUSW-306}
    <td> Missing call to I2C_lld_recoverBus on polling mode
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-256, EXT_SITMPUSW-256}
    <td> Incorrect calculation of rowColEnd in the ext_otp_writeMmr
    <td> OTP
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-292, EXT_SITMPUSW-292}
    <td> Bootloader_socOpenFirewalls is called before System_init in the SBLs
    <td> SBL
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-87, EXT_SITMPUSW-87}
    <td> Sysconfig crashing when adding large number of GPIO pins
    <td> GPIO
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-28, EXT_SITMPUSW-28}
    <td> Outstanding mailbox messages prevent suspend
    <td> IPC
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
    <td> Spinlock: Missing NULL Pointer Validation for Base Address Parameter in Spinlock APIs
    <td> Spinlock
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-324, EXT_SITMPUSW-324}
    <td> UART_udmaIsrTx does not handles continuous Callbacks properly
    <td> UART
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12275, EXT_EP-12275}
    <td> AM62x: ECC: SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR and  SDL_DMASS0_DMSS_AM62_ECCAGGR aggregators are failing
    <td> SDL-ECC
</tr>
<tr>
    <td> PROC_SDL-8868
    <td> AM62x: ECC: ecc_test_app is failing
    <td> SDL-ECC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12276, EXT_EP-12276}
    <td> ECC: Firewall related aggregators failures
    <td> SDL-ECC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12278, EXT_EP-12278}
    <td> ECC Aggregator SMS0_SMS_HSM_ECC Aggr fails on AM62x
    <td> SDL-ECC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12279, EXT_EP-12279}
    <td> CSI RX ECC aggregators are failing on AM62P/AM62X
    <td> SDL-ECC
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
    <td> PHY mode not supported for OSPI NAND SBL on DDR mode. It is supported for SDR mode only
    <td> Bootloader
</tr>
<tr>
    <td> 3
    <td> LPM is not supported with SBL boot flow. It is supported only with SPL boot flow.
    <td> Bootloader
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
OSPI         |  \ref OSPI_MIGRATION_GUIDE       &zwj;      |   <= 11.01.00  | >= 11.02.00
Watchdog     |  \ref WATCHDOG_12_0_MIGRATION    &zwj;      |   <= 11.02.00  | >= 12.00.00
SCI Server   |  \ref SCISERVER_12_0_MIGRATION   &zwj;      |   <= 11.02.00  | >= 12.00.00
SBL Linker   |  \ref SBL_LINKER_12_0_MIGRATION   &zwj;     |   <= 11.02.00  | >= 12.00.00


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


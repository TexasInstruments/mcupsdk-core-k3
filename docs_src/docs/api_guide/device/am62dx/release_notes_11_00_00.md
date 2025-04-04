# Release Notes 11.00.00 {#RELEASE_NOTES_11_00_00_PAGE}

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

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
ECC example for R5F cache                                                                      | SDL
FreeRTOS AMP support on A53                                                                    | DPL
OSPI support on MCU-R5F                                                                        | OSPI
RTC driver on R5F                                                                              | RTC
Example to show usage of firewalls isolation of MCU domain                                     | Examples
Optimized boottime for eMMC, SD boot by enabling DMA for DDR to DDR copy                       | Bootloader
Ethernet AVB: CRF Talker functionality added along with example                                | Networking

### Experimental Features {#EXPERIMENTAL_FEATURES}

\attention Features listed below are early versions and should be considered as "experimental".
\attention Users can evaluate the feature, however the feature is not fully tested at TI side.
\attention TI would not support these feature on public e2e.
\attention Experimental features will be enabled with limited examples and SW modules.

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
FreeRTOS AMP support on A53.                                        | DPL, FreeRTOS
A53 FreeRTOS AMP examples demonstrating usage of ethernet           | Networking

## Dependent Tools and Compiler Information
\attention It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.

Tools                   | Supported CPUs             | Version
------------------------|----------------------------|-----------------------
Code Composer Studio    | MCU-R5F, C75, A53          | 20.1.0
SysConfig               | MCU-R5F, WKUP-R5F, C75, A53| 1.23.0, build 4000
TI ARM CLANG            | MCU-R5F, WKUP-R5F          | 4.0.1.LTS
GCC AARCH64             | A53                        | 9.2-2019.12
C7000-CGT               | C75                        | 4.1.0.LTS
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F, C75, A53| 11.1.0

## SDK Components

### SYSFW / TIFS

<table>
    <tr>
        <td>Version</td>
        <td>11.00.07</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_00_07/release_notes/release_notes.html)</td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_00_07/1_intro/TISCI.html)</td>
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
        <td rowspan=3>GPIO</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>I2C</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>IPC</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCAN</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Maim</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan>MCASP</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MMCSD</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>OSPI</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SA3UL</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UDMA</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>WDT</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
</table>

\note Refer \ref MAIN_DOMAIN_PERIPHERAL_FROM_MCU for accessing main/wakeup peripherals from MCU Domain.

### Board Device Drivers

Peripheral | Supported CPUs      | SysConfig Support
-----------|---------------------|-------------------
EEPROM     | MCU-R5F, A53, C75   | Yes
Flash      | WKUP-R5F, A53       | Yes
LED        | MCU-R5F, A53, C75   | Yes
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
    <th> Applicable Releases
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-52, EXT_SITMPUSW-52}
    <td> UART baud rate and operational mode condition misalignment
    <td> UART
    <td> 10.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-57, EXT_SITMPUSW-57}
    <td> Data Abort at MCSPI_udmaIsrTx when using MCSPI DMA
    <td> MCSPI
    <td> 10.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-59, EXT_SITMPUSW-59}
    <td> VTM giving same value for every call
    <td> VTM
    <td> 10.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-88, EXT_SITMPUSW-88}
    <td> MCASP_close() function is not having a graceful exit and is stuck in a for loop for very long time.
    <td> MCASP
    <td> 10.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-89, EXT_SITMPUSW-89}
    <td> I2C Error Handler transition from status to i2cTransaction.status
    <td> I2C
    <td> 10.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-90, EXT_SITMPUSW-90}
    <td> MMCSD_write & MMCSD_read function fails for the numBlocks greater than 0xFFFF
    <td> MCSPI
    <td> 10.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-91, EXT_SITMPUSW-91}
    <td> The DMA channels are not able to close without DMA Tx for MCSPI and UART
    <td> DMA
    <td> 10.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12316, EXT_EP-12316}
    <td> AM62dx: PBIST: VPAC controller test is to be removed
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12318, EXT_EP-12318}
    <td> SDL_ECC_aggrTransBaseAddressTable declared without extern keyword
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12324, EXT_EP-12324}
    <td> gSDL_pvt_poly_golden has to be used in SDL_vtmPrepLookupTable API instead of gSDL_pvt_poly
    <td> SDL
    <td> 11.00.00
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-73, EXT_SITMPUSW-73}
    <td> OSPI_readDirect and OSPI_isPhyEnable do not correctly check if the PHY is enabled
    <td> OSPI
    <td> 10.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-77, EXT_SITMPUSW-77}
    <td> Modify Read capture delay logic for Tap Mode
    <td> OSPI
    <td> 10.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-78, EXT_SITMPUSW-78}
    <td> MMCSD Sysconfig provides options to configure PHY type
    <td> MMCSD
    <td> 10.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-85, EXT_SITMPUSW-85}
    <td> Flash_eraseSector and Flash_norOspiEraseSector does not erases the mentioned sector.
    <td> Flash
    <td> 10.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12267, EXT_EP-12267}
    <td> AM62D: MCRC Udma Init failure in semi cpu and auto mode configuration - MCRC semi cpu and auto mode examples fail at udma init step
    <td> SDL
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12276, EXT_EP-12276}
    <td> ECC: Firewall related aggregators failures - ECC Aggregators SDL_SMS0_SMS_TIFS_ECC, SDL_SMS0_SMS_HSM_ECC, SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR and SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR fail because of firewall access issues faced by SDL
    <td> SDL
    <td> 10.01.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12283, EXT_EP-12283}
    <td> ECC aggregators CPSW0, CSI RX are failing on AM62A and CPSW0 on AM62D.
    <td> SDL
    <td> 09.00.00
    <td> No known workaround
</tr>
<tr>
    <td> TBD
    <td> TBD
    <td> TBD
    <td> TBD
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
</table>
</table>

## Upgrade and Compatibility Information

\attention When migrating from oldder version to 11.00.00, see \ref BOOTLOADER_MIGRATION_GUIDELINE for more details

This section lists changes which could affect user applications developed using older SDK versions.
Read this carefully to see if you need to do any changes in your existing application when migrating to this SDK version relative to
previous SDK version. Also refer to older SDK version release notes to see changes in
earlier SDKs.

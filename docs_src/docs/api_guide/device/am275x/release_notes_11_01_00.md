# Release Notes 11.01.00 {#RELEASE_NOTES_11_01_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

SOC    | Supported CPUs              | EVM                                                     | Host PC
-------|-----------------------------|---------------------------------------------------------|-----------------------------------
AM275x | R5F, C75                    | @VAR_BOARD_NAME (referred to as am275x-evm in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release

Feature                                                                                  | Module
-----------------------------------------------------------------------------------------|-----------------------------------
HW ASRC support                                                                          | ASRC
Optiflash support                                                                        | OSPI
HyperRAM  support                                                                        | OSPI
Hello World CPP example added for C7x and R5x                                            | examples
ECC Functional Test example for single bit errors is added                               | SDL

## Dependent Tools and Compiler Information

Tools/ Component        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | R5F, C75                 | 20.2.0
SysConfig               | R5F, C75                 | 1.24.0, build 4150
TI ARM CLANG            | R5F                      | 4.0.1.LTS
C7000-CGT               | C75                      | 5.0.0.LTS
FreeRTOS Kernel         | R5F, C75                 | 11.1.0

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

### Eval Features

\attention Features listed below are early versions and gone through limited testing.

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
HW ASRC support                                                     | ASRC
HyperRAM support                                                    | OSPI
Optiflash support                                                   | OSPI
AUDIOLIB                                                            | All modules in AUDIOLIB

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

Peripheral | Supported CPUs  | SysConfig Support
-----------|-----------------|-------------------
ADC        | R5F             | YES
ASRC       | C7X             | YES
ECAP       | R5F, C7X        | YES
EPWM       | R5F, C7X        | YES
EQEP       | R5F, C7X        | YES
GPIO       | R5F, C7X        | YES
I2C        | R5F, C7X        | YES
IPC        | R5F, C7X        | YES
MCAN       | R5F             | YES
MCASP      | R5F, C7X        | YES
MCSPI      | R5F             | YES
MMCSD      | R5F             | YES
Pinmux     | R5F, C7X        | YES
RTC        | C7X             | YES
SOC        | R5F, C7X        | YES
SCI Client | R5F, C7X        | YES
UART       | R5F, C7X        | YES
UDMA       | R5F, C7X        | YES


### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
EEPROM     | R5F            | Yes
Flash      | WKUP-R5F       | Yes
LED        | R5F            | Yes

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
    <th> Applicable Releases
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12721, EXT_EP-12721}
    <td> ECC TCM example cannot be built for AM275
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-93, EXT_SITMPUSW-93}
    <td> AM275: System project build failure in windows OS
    <td> Build
    <td> 11.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-94, EXT_SITMPUSW-94}
    <td> Change of eCAP Functional clock frequency to 250Mhz from 125Mhz
    <td> ECAP
    <td> 11.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-95, EXT_SITMPUSW-95}
    <td> AM62D/AM275: MCASP stereo playback has unbalanced amplitude in L/R
    <td> McASP
    <td> 11.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-99, EXT_SITMPUSW-99}
    <td> AM275x FreeRTOS SDK: The Flash option is not available for Main R5F_0_0
    <td> Flash
    <td> 11.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-105, EXT_SITMPUSW-105}
    <td> MMCSD driver uses snprintf function from libc
    <td> MMCSD
    <td> 11.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-77, EXT_SITMPUSW-77}
    <td> Modify Read capture delay logic for Tap Mode
    <td> OSPI
    <td> 11.00.00
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-106, EXT_SITMPUSW-106}
    <td> OSPI Phy Tuning Data is not written correctly in Flash_norOspiOpen()
    <td> OSPI
    <td> 10.01.00
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-85, EXT_SITMPUSW-1085}
    <td> Flash_eraseSector and Flash_norOspiEraseSector does not erases the mentioned sector.
    <td> Flash
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-109, EXT_SITMPUSW-109}
    <td> Wrong comments on HwiP_inISR() API
    <td> DPL
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-78, EXT_SITMPUSW-78}
    <td> MMCSD Sysconfig provides options to configure PHY type
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-84, EXT_SITMPUSW-84}
    <td> MMCSD error recovery sequence isn't implemented correctly
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-110, EXT_SITMPUSW-110}
    <td> eMMC Init Code Missing DLL Register Settings needed for Initial Legacy SDR Mode Phase
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-113, EXT_SITMPUSW-113}
    <td> eMMC PHY I/O Calibration not getting executed during eMMC boot
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-114, EXT_SITMPUSW-114}
    <td> MMCSD_enableBootPartition implements two mutually exclusive concepts as one function
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-115, EXT_SITMPUSW-115}
    <td> SDR/DDR mode are not enabled in the Sysconfig for MMCSD
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-123, EXT_SITMPUSW-123}
    <td> MMCSD driver does not follow the SWITCH command sequence correctly
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-124, EXT_SITMPUSW-124}
    <td> EXTCSD HS_TIMING register is set incorrectly at certain places in the driver
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-125, EXT_SITMPUSW-125}
    <td> MMCSD driver uses infinite loop instead of timeout for checking fields of PRESENTSTATE register
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-126, EXT_SITMPUSW-126}
    <td> Timing issues with MMCSD host controller driver
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-128, EXT_SITMPUSW-128}
    <td> EMMC timiing parameters to be changed based on SOC and MMC instance
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-120, EXT_SITMPUSW-120}
    <td> C7x task size/alignment should be 8KB (not 16KB)
    <td> FreeRTOS
    <td> 11.00.00
    <td> Change the stack alignment
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-121, EXT_SITMPUSW-121}
    <td> FORCE bit not book keeped properly for MCSPI DMA mode of operation
    <td> MCSPI
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-112, EXT_SITMPUSW-112}
    <td> SysConfig does not generate correct FLASH section parameters
    <td> Flash
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12282, EXT_EP-12282}
    <td> AM275x: ECC: Some of the aggregators are failing on AM275x - FSS1_OSPI, MCAN0_MSGMEM_WRAP, ADC12FCC0, R5FSS0_PULSAR, WKUP_AGGR0_DM, DMASS0 and WKUP_PSRAM are failing
    <td> SDL
    <td> 10.01.00
    <td> No known workaround
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
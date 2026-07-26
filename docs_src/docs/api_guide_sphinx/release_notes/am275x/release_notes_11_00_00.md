# Release Notes 11.00.00

:::{attention}
Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.
:::

:::{note}
The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination.
Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.
:::

## Device and Validation Information

SOC    | Supported CPUs              | EVM                                                     | Host PC
-------|-----------------------------|---------------------------------------------------------|-----------------------------------
AM275x | R5F, C75                    | {{ VAR_BOARD_NAME }} (referred to as am275x-evm in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release

Feature                                                                                  | Module
-----------------------------------------------------------------------------------------|-----------------------------------
ECC example for R5F cache                                                                | SDL
DRU support is enabled with DMAUtils examples                                            | UDMA
OSPI XIP boot support is added with XIP benchmark example                                | Bootloader
ADC support on R5F                                                                       | ADC
ECAP, EPWM, EQEP on R5F and C7X                                                          | Drivers
MCAN external read write example is added                                                | MCAN
Early chime example is added                                                             | McASP
RTC support on R5F                                                                       | RTC
Image version check on SBL                                                               | Bootloader
Ethernet AVB: CRF Talker functionality added along with example                          | Networking

## Dependent Tools and Compiler Information

Tools/ Component        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | R5F, C75                 | 20.1.0
SysConfig               | R5F, C75                 | 1.23.0, build 4000
TI ARM CLANG            | R5F                      | 4.0.1.LTS
C7000-CGT               | C75                      | 4.1.0.LTS
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

:::{note}
See the updated MCASP usage guidelines in DRIVERS_MCASP_PAGE for changes in
MCASP driver
:::

Peripheral | Supported CPUs  | SysConfig Support
-----------|-----------------|-------------------
ADC        | R5F             | YES
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


:::{note}
This is BQ release for SDL. FSQ release will be provided in next release.
:::

## Fixed Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
</tr>
<tr>
    <td> [ EXT_SITMPUSW-52](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-52)
    <td> UART baud rate and operational mode condition misalignment
    <td> UART
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-57](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-57)
    <td> Data Abort at MCSPI_udmaIsrTx when using MCSPI DMA
    <td> MCSPI
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-59](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-59)
    <td> VTM giving same value for every call
    <td> VTM
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-88](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-88)
    <td> MCASP_close() function is not having a graceful exit and is stuck in a for loop for very long time.
    <td> MCASP
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-89](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-89)
    <td> I2C Error Handler transition from status to i2cTransaction.status
    <td> I2C
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-90](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-90)
    <td> MMCSD_write & MMCSD_read function fails for the numBlocks greater than 0xFFFF
    <td> MCSPI
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-91](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-91)
    <td> The DMA channels are not able to close without DMA Tx for MCSPI and UART
    <td> DMA
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_EP-12321](https://sir.ext.ti.com/jira/browse/EXT_EP-12321)
    <td> MCRC: System_deinit failure in MCRC Semi CPU mode and MCRC auto mode in AM275x and AM62a
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> [ EXT_EP-12322](https://sir.ext.ti.com/jira/browse/EXT_EP-12322)
    <td> AM275x: PBIST: MAIN_PULSAR_0 (PBIST1) and MAIN_PULSAR_1 (PBIST2) secondary core reset failure
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> [ EXT_EP-12323](https://sir.ext.ti.com/jira/browse/EXT_EP-12323)
    <td> AM275x: PBIST: MAIN_IP (PBIST0) controller testing failure
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> [ EXT_EP-12324](https://sir.ext.ti.com/jira/browse/EXT_EP-12324)
    <td> gSDL_pvt_poly_golden has to be used in SDL_vtmPrepLookupTable API instead of gSDL_pvt_poly
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> [ EXT_EP-12318](https://sir.ext.ti.com/jira/browse/EXT_EP-12318)
    <td> SDL_ECC_aggrTransBaseAddressTable declared without extern keyword
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
    <td> [ EXT_SITMPUSW-73](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-73)
    <td> OSPI_readDirect and OSPI_isPhyEnable do not correctly check if the PHY is enabled
    <td> OSPI
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-77](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-77)
    <td> Modify Read capture delay logic for Tap Mode
    <td> OSPI
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-78](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-78)
    <td> MMCSD Sysconfig provides options to configure PHY type
    <td> MMCSD
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-85](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-85)
    <td> Flash_eraseSector and Flash_norOspiEraseSector does not erases the mentioned sector.
    <td> Flash
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12276](https://sir.ext.ti.com/jira/browse/EXT_EP-12276)
    <td> ECC: Firewall related aggregators failures - ECC Aggregators SDL_SMS0_SMS_TIFS_ECC, SDL_SMS0_SMS_HSM_ECC, SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR and SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR fail because of firewall access issues faced by SDL
    <td> SDL
    <td> 10.01.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12282](https://sir.ext.ti.com/jira/browse/EXT_EP-12282)
    <td> AM275x: ECC: Some of the aggregators are failing on AM275x - ECC aggregators IDOM0_PULSAR_8 and 10, IDOM0_MAIN_4 and 6, IDOM1_PULSAR_9 and 11, IDOM1_MAIN_5 and 7, FSS1_OSPI, WKUP_AGGR0_DM, WKUP_PSRAM and ADC12FCC0 are failing
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

:::{attention}
When migrating from oldder version to 11.00.00, see BOOTLOADER_MIGRATION_GUIDELINE for more details
:::

This section lists changes which could affect user applications developed using older SDK versions.
Read this carefully to see if you need to do any changes in your existing application when migrating to this SDK version relative to
previous SDK version. Also refer to older SDK version release notes to see changes in
earlier SDKs.

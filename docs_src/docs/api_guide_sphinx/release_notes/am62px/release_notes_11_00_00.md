# Release Notes 11.00.00
:::{admonition} Attention
Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.
:::


:::{admonition} Note
The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.
:::


## Device and Validation Information

SOC    | Supported CPUs              | EVM                                                    | Host PC
-------|-----------------------------|--------------------------------------------------------|-----------------------------------
AM62P  | MCU R5F, WKUP R5F           | {{ VAR_BOARD_NAME }} EVM (referred to as am62px-sk in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
ECC example for R5F cache                                                                      | SDL
Example for Key Revision update                                                                | OTP
RTC driver on MCU R5F                                                                          | RTC
LPM example for MCU only with Timer and MCAN as wakeup sources                                 | LPM
Optimized boottime for eMMC, SD boot by enabling DMA for DDR to DDR copy                       | Bootloader
Optimized boottime for OSPI by enabling HCDMA in bootloader                                    | Bootloader


### Experimental Features
:::{admonition} Attention
- Features listed below are early versions and should be considered as "experimental".
- Users can evaluate the feature, however the feature is not fully tested at TI side.
- TI would not support these feature on public e2e.
- Experimental features will be enabled with limited examples and SW modules.
:::


Feature                                                                             | Module
------------------------------------------------------------------------------------|--------------------------
Ethernet traffic sharing accross multiple cores, called Ethernet Firmware           | Networking

## Dependent Tools and Compiler Information
:::{admonition} Attention
It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.
:::


Tools/Components        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, WKUP-R5F        | 20.1.0
SysConfig               | MCU-R5F, WKUP-R5F        | 1.23.0, build 4000
TI ARM CLANG            | MCU-R5F, WKUP-R5F        | 4.0.1.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F        | 11.1.0

## SDK Components

### SYSFW / TIFS

<table>
    <tr>
        <td>Version</td>
        <td>11.00.07</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td><a href="https://software-dl.ti.com/tisci/esd/11_00_07/release_notes/release_notes.html">LINK</a></td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td><a href="https://software-dl.ti.com/tisci/esd/11_00_07/1_intro/TISCI.html">LINK</a></td>
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

:::{admonition} Note
See the updated MCASP usage guidelines in [MCASP](../../components/drivers/mcasp_v1.md) for changes in MCASP driver
:::


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
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-52">EXT_SITMPUSW-52</a>
    <td> UART baud rate and operational mode condition misalignment
    <td> UART
    <td> 09.02.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-57">EXT_SITMPUSW-57</a>
    <td> Data Abort at MCSPI_udmaIsrTx when using MCSPI DMA
    <td> MCSPI
    <td> 09.02.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-58">EXT_SITMPUSW-58</a>
    <td> MCU PLUS SDK: ipc_rpmsg_echo [DM Firmware] Timeout not working as expected, crashes FW
    <td> DM, IPC
    <td> 09.02.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-59">EXT_SITMPUSW-59</a>
    <td> VTM giving same value for every call
    <td> VTM
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-60">EXT_SITMPUSW-60</a>
    <td> No synchronization wrt DMA between main & boot thread of the Stage2/DM application
    <td> Bootloader
    <td> 09.02.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-89">EXT_SITMPUSW-89</a>
    <td> I2C Error Handler transition from status to i2cTransaction.status
    <td> I2C
    <td> 09.02.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-90">EXT_SITMPUSW-90</a>
    <td> MMCSD_write & MMCSD_read function fails for the numBlocks greater than 0xFFFF
    <td> MCSPI
    <td> 09.02.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12317">EXT_EP-12317</a>
    <td> AM62Px: PBIST: Unnecessary code in pbist_test_cfg.c files
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12318">EXT_EP-12318</a>
    <td> SDL_ECC_aggrTransBaseAddressTable declared without extern keyword
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12324">EXT_EP-12324</a>
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
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-28">EXT_SITMPUSW-28</a>
    <td> Outstanding mailbox messages prevent suspend
    <td> IPC
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-73">EXT_SITMPUSW-73</a>
    <td> OSPI_readDirect and OSPI_isPhyEnable do not correctly check if the PHY is enabled
    <td> OSPI
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-77">EXT_SITMPUSW-77</a>
    <td> Modify Read capture delay logic for Tap Mode
    <td> OSPI
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-78">EXT_SITMPUSW-78</a>
    <td> MMCSD Sysconfig provides options to configure PHY type
    <td> MMCSD
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-85">EXT_SITMPUSW-85</a>
    <td> Flash_eraseSector and Flash_norOspiEraseSector does not erases the mentioned sector.
    <td> Flash
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12277">EXT_EP-12277</a>
    <td> AM62Px: ECC: SDL_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR aggregator is failing
    <td> SDL
    <td> 10.01.00
    <td> No known workaround
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12279">EXT_EP-12279</a>
    <td> CSI RX ECC aggregators are failing on AM62P/AM62X
    <td> SDL
    <td> 09.01.00
    <td> No known workaround
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12280">EXT_EP-12280</a>
    <td> Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F - After running MCU LBIST, not able to connect to any core through JTAG on AM62px
    <td> SDL
    <td> 09.00.00
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
    <td> The <b>ROM</b> startup model for runtime initializations in TI ARM CLANG is not supported/tested in the SDK
    <td> NA
</tr>
<tr>
    <td> 2
    <td> LPM is not supported with SBL boot flow. It is supported only with SPL boot flow.
    <td> Bootloader
</tr>
</table>
</table>

## Upgrade and Compatibility Information

:::{admonition} Attention
When migrating from oldder version to 11.00.00, see [Bootloader Migration Guidelines](../../components/drivers/bootloader.md) for more details
:::


This section lists changes which could affect user applications developed using older SDK versions.
Read this carefully to see if you need to do any changes in your existing application when migrating to this SDK version relative to
previous SDK version. Also refer to older SDK version release notes to see changes in
earlier SDKs.

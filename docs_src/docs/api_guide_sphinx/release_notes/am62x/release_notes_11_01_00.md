---
orphan: true
---

# Release Notes 11.01.00

:::{attention}
Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.
:::

:::{note}
The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination.
Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.
:::

## Device and Validation Information


SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62x  | M4F, R5F, A53   | SK-AM62 (referred as am62x-sk in code), SK-AM62-LP (referred as am62x-sk-lp in code), SK-AM62-SIP (referred as am62x-sip-sk in code) | Windows 10 64b or Ubuntu 22.04 64b


## Features Added in This Release


:::{attention}
DeepSleep low power mode (LPM) is not supported if the DM R5 is used for a general purpose application. This is because when the SoC goes to any LPM, the context of peripherals used by DM R5 will be lost. To use DM R5 for a general purpose application, disable LPM support. Refer DISABLE_LPM to know how to disable LPM.
:::

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
ECC Functional Test example for single bit errors is added                                     | SDL
Updated DDR configuration from DDR configuration tool v10.30                                   | DDR


### Experimental Features
:::{attention}
Features listed below are early versions and should be considered as "experimental".
:::
:::{attention}
Users can evaluate the feature, however the feature is not fully tested at TI side.
:::
:::{attention}
TI would not support these feature on public e2e.
:::
:::{attention}
Experimental features will be enabled with limited examples and SW modules.
:::

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
FreeRTOS AMP support on A53.                                        | DPL, FreeRTOS
A53 FreeRTOS AMP examples demonstrating usage of ethernet           | Networking

### FreeRTOS Support on A53
Is                                                      | Is Not
--------------------------------------------------------|--------------------------
FreeRTOS AMP support on A53                             | GPU Support
Drivers listed for A53 in "SOC Device Drivers" section  | Low power mode support
Ethernet Networking                                     | CSI RX Driver
-                                                       | WiFi, USB, BLE Drivers
-                                                       | Safety on A53

## Dependent Tools and Compiler Information

:::{attention}
It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.
:::

Tools/Components        | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | M4F, R5F, A53  | 20.2.0
SysConfig               | M4F, R5F, A53  | 1.24.0, build 4150
TI ARM CLANG            | M4F, R5F       | 4.0.1.LTS
GCC AARCH64             | A53            | 9.2-2019.12
FreeRTOS Kernel         | M4F, R5F, A53  | 11.1.0

## SDK Components

### SYSFW / TIFS

<table>
    <tr>
        <td>Version</td>
        <td>11.01.02</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_01_02/release_notes/release_notes.html)</td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_01_02/1_intro/TISCI.html)</td>
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

:::{note}
See the updated MCASP usage guidelines in {ref}`MCASP <DRIVERS_MCASP_PAGE>` for changes in
MCASP driver
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
        <td>R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>DSS</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>ECAP</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>EPWM</td>
        <td>Main</td>
        <td>M4F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>EQEP</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>GPIO</td>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>GPMC</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCAN</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MMCSD</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>OSPI</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>RTC</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>UDMA</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>WDT</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
</table>

:::{note}
Refer {ref}`Accessing main and wakeup domain peripherals from MCU domain <MAIN_DOMAIN_PERIPHERAL_FROM_MCU>` for accessing main/wakeup peripherals from MCU Domain.
:::

### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
Flash      | R5F            | Yes

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
    <th> Applicable Releases
</tr>
<tr>
    <td> [ EXT_SITMPUSW-96](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-96)
    <td> Coremark pro core test only has 1 iteration test for am62x
    <td> Benchmark Examples
    <td> 11.00.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-105](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-105)
    <td> MMCSD driver uses snprintf function from libc
    <td> MMCSD
    <td> 11.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-77](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-77)
    <td> Modify Read capture delay logic for Tap Mode
    <td> OSPI
    <td> 11.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-106](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-106)
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
    <td> [ EXT_SITMPUSW-1085](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-85)
    <td> Flash_eraseSector and Flash_norOspiEraseSector does not erases the mentioned sector.
    <td> Flash
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-28](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-28)
    <td> Outstanding mailbox messages prevent suspend
    <td> IPC
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-87](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-87)
    <td> Sysconfig crashing when adding large number of GPIO pins
    <td> GPIO
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-109](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-109)
    <td> Wrong comments on HwiP_inISR() API
    <td> DPL
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-78](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-78)
    <td> MMCSD Sysconfig provides options to configure PHY type
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-84](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-84)
    <td> MMCSD error recovery sequence isn't implemented correctly
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-110](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-110)
    <td> eMMC Init Code Missing DLL Register Settings needed for Initial Legacy SDR Mode Phase
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-113](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-113)
    <td> eMMC PHY I/O Calibration not getting executed during eMMC boot
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-114](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-114)
    <td> MMCSD_enableBootPartition implements two mutually exclusive concepts as one function
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-123](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-123)
    <td> MMCSD driver does not follow the SWITCH command sequence correctly
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-124](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-124)
    <td> EXTCSD HS_TIMING register is set incorrectly at certain places in the driver
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-125](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-125)
    <td> MMCSD driver uses infinite loop instead of timeout for checking fields of PRESENTSTATE register
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-126](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-126)
    <td> Timing issues with MMCSD host controller driver
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-128](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-128)
    <td> EMMC timiing parameters to be changed based on SOC and MMC instance
    <td> MMCSD
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-117](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-117)
    <td> Linux Kernel IPC Examples are broken
    <td> IPC
    <td> 11.00.00
    <td> Change ti.ipc4.ping-pong to rpmsg-client-sample in the example
</tr>
<tr>
    <td> [ EXT_SITMPUSW-121](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-121)
    <td> FORCE bit not book keeped properly for MCSPI DMA mode of operation
    <td> MCSPI
    <td> 11.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-133](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-133)
    <td> Falcon Boot through SBL is not supported
    <td> SBL
    <td> 09.02.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-134](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-134)
    <td> GPIO input interrupt example not working on A53 AMP
    <td> GPIO
    <td> 10.01.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12275](https://sir.ext.ti.com/jira/browse/EXT_EP-12275)
    <td> AM62x: ECC: SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR and SDL_DMASS0_DMSS_AM62_ECCAGGR aggregators are failing.
    <td> SDL
    <td> 10.01.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12276](https://sir.ext.ti.com/jira/browse/EXT_EP-12276)
    <td> ECC: Firewall related aggregator failures - ECC Aggregators SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR and SDL_SMS0_SMS_TIFS_ECC fail because of firewall access issues faced by SDL
    <td> SDL
    <td> 10.01.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12278](https://sir.ext.ti.com/jira/browse/EXT_EP-12278)
    <td> ECC Aggregator SMS0_SMS_HSM_ECC Aggr fails on AM62x.
    <td> SDL
    <td> 10.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12279](https://sir.ext.ti.com/jira/browse/EXT_EP-12279)
    <td> CSI RX ECC aggregators are failing on AM62P/AM62X
    <td> SDL
    <td> 09.01.00
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
Bootloader   |  {ref}`Bootloader Migration Guidelines <BOOTLOADER_MIGRATION_GUIDELINE>` |   <= 10.01.00  | >= 11.00.00
NETWORKING   |  {ref}`Version Updates from earlier SDKs to Latest <enet_mcupsdk_update>` |    11.00.00  | >= 11.01.00

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

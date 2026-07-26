---
orphan: true
---

# Release Notes 10.01.00

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
OSPI flash diag application for custom flashes                                                 | OSPI
Support for authentication from DDR when in-place authentication fails from OSPI NOR           | Bootloader
Support for SW version check of binaries through RPRC header                                   | Bootloader
FreeRTOS AMP support on A53                                                                    | Kernel
RTC driver                                                                                     | Drivers
Display driver support on A53                                                                  | Drivers
A53 applications booted with ATF now                                                           | ATF


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
Networking                                              | CSI RX Driver
-                                                       | WiFi, USB, BLE Drivers
-                                                       | Safety on A53

## Dependent Tools and Compiler Information

:::{attention}
It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.
:::

Tools/Components        | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | M4F, R5F, A53  | 12.8.1
SysConfig               | M4F, R5F, A53  | 1.20.0, build 3587
TI ARM CLANG            | M4F, R5F       | 3.2.2.LTS
GCC AARCH64             | A53            | 9.2-2019.12
FreeRTOS Kernel         | M4F, R5F, A53  | 11.1.0
TIFS                    | NA             | v10.01.08

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
TSN                         | A53            | NO                | FreeRTOS    | [Experimental] gPTP IEEE 802.1 AS-2020 compliant gPTP stack, End Nodes and Bridge mode support, YANG data model configuration  | Multi-Clock Domain
LwIP                        | A53            | YES               | FreeRTOS    | [Experimental] TCP/UDP IP networking stack with and without checksum offload enabled, TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs and raw APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping, LwIP bridge, shared memory driver  | Other LwIP features
Ethernet driver (ENET)      | A53            | YES               | FreeRTOS    | [Experimental] Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW, Strapped PHY (Early Ethernet), cut through switch on CPSW  | RMII mode

### SOC Device Drivers

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
    <td> [ EXT_SITMPUSW-34](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-34)
    <td> SBL_UART_UNIFLASH_STAGE2 build fails on removing OSPI and FLASH module in Sysconfig
    <td> Uniflasher
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-5](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-5)
    <td> Potential Infinite loop in OSPI_utilLog2 defined in ospi_v0.c
    <td> OSPI
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-35](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-35)
    <td> MMCSD_initSD always returns SUCCESS
    <td> SD
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-36](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-36)
    <td> MMCSD_initSD does not check the retry variable for failure for OCR command
    <td> SD
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-37](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-37)
    <td> Misleading "File read from SD card" bootloader profile point in the SBL_SD bootloader
    <td> Bootloader
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-38](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-38)
    <td> Remote core getting hangs when doing IPC with HLOS
    <td> IPC
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-39](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-39)
    <td> Error in the CCS build of the SBL examples
    <td> SBL
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-40](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-40)
    <td> The SYSFW_IMAGE_INTEGRITY OID is incorrectly mentioned in the comment
    <td> Bootloader
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-41](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-41)
    <td> ClockP_getTicks to use xTaskGetTickCountFromISR() freeRTOS function if it is from ISR
    <td> DPL
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-3](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-3)
    <td> EMMC:The tuning algorithm to re-execute up to 10 times if there is no failing or passing itapdly.
    <td> EMMC
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-42](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-42)
    <td> Enable floating point task save restore for all tasks by default
    <td> DPL
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-43](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-43)
    <td> MMCSD driver doesn't implement the recovery steps for CRC errors
    <td> EMMC
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-44](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-44)
    <td> DebugP_log API returning wrong value
    <td> DPL
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-45](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-45)
    <td> Memcpy: Utils_memcpyWord function doesn't work on 64 bit systems
    <td> Utils
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-46](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-46)
    <td> SK-AM62-LP: LPM: MCU only mode unable to resolve with uart
    <td> IPC
    <td> 10.01.00
</tr>
<tr>
    <td> PROC_SDL-8139
    <td> SDL ECC example application exits with failure on UC-2
    <td> SDL
    <td> 10.01.00
</tr>
<tr>
    <td> PROC_SDL-8137
    <td> PBIST example app fails when built for freertos
    <td> SDL
    <td> 10.01.00
</tr>
<tr>
    <td> PROC_SDL-8134
    <td> POK example app fails when built for freertos
    <td> SDL
    <td> 10.01.00
</tr>
<tr>
    <td> SITSW-3685
    <td> DM Sciclient ignores flags field for TIFS bound messages
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SITSW-4773
    <td> DM is ignoring the exact flags sent in TISCI message
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SITSW-5794
    <td> TISCI Messages from A53_4 are not receiving a response
    <td> DM
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SYSFW-5992
    <td> Unable to set exact pixel clock for OLDI LCD display / HDMI Pixel clock
    <td> DM
    <td> 08.05.00 onwards
</tr>
<tr>
    <td> SYSFW-6432
    <td> Set device API doesn't return Error when PD is in transition state
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-7559
    <td> In MCU-Only mode resume path the MCU_M4 LPSC is ON
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7571
    <td> Device IDs higher than 255 does not work with set device constraint API
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7602
    <td> RTC count value not getting updated after DeepSleep exit
    <td> DM (LPM)
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-7614
    <td> Unable to configure DSS clock below 15.625MHz
    <td> DM
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7617
    <td> LPM mode selection logic does not check for constraints on all the hosts/devices
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7740
    <td> Only the last latency constraint value passed from a host considered in LPM selection
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7760
    <td> LPM: MCU subsystem (GPIO) clock should not be changed in MCU Only mode
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-6426
    <td> Ownership of a firewall region can be transferred to an invalid host
    <td> TIFS
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-7739
    <td> LPM constraint messages received by TIFS not forwarded to DM
    <td> TIFS
    <td> 10.00.00
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
    <td> MCUSDK-208
    <td> gmake with -j can sometimes lock up Windows command prompt
    <td> Build
    <td> 07.03.00
    <td> Use bash for windows as part of git for windows or don't use -j option
</tr>
<tr>
    <td> SYSFW-7781
    <td> Get device API does not return error when the LPSC is in transition state
    <td> DM
    <td> 10.01.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7884
    <td> There is an additional divide by 4 on all clocks of WKUP/MCU GPIO clock mux
    <td> DM
    <td> 10.01.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7898
    <td> Switching between MCU-Only and DeepSleep mode fails after some iterations
    <td> DM (LPM)
    <td> 10.01.00
    <td> None.
</tr>
<tr>
    <td> PROC_SDL-8582
    <td> VTM Example is failing in no-bootmode for M4F core
    <td> SDL
    <td> 10.01.00
    <td> Use UART Bootmode
</tr>
<tr>
    <td> PROC_SDL-8404 (CSI), PROC_SDL-8872 (WKUP_R5F), PROC_SDL-8865 (ICSS)
    <td> ECC is not supported for some instances. These are
    SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR
    SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR
    SDL_ICSSM0_ICSS_M_CORE_BORG_ECC_AGGR
    <td> SDL
    <td> 10.01.00 (WKUP_R5F,ICSS), 09.01.00 (CSI)
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8861
    <td> ECC is not supported for some instances due to firewall. These are
    SDL_SA3_SS0_SA3SS_AM62_DMSS_ECCAGGR
    SDL_SMS0_SMS_HSM_ECC
    SDL_SMS0_SMS_TIFS_ECC
    <td> SDL
    <td> 10.01.0
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8792
    <td> System_deinit error in MCRC Semi CPU and Auto CPU examples
    <td> SDL
    <td> 10.01.00
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8870
    <td> VTM Example is failing on R5F core
    <td> SDL
    <td> 10.01.00
    <td> Generate binary for M4F core
</tr>
<tr>
    <td> PROC_SDL-8890
    <td> ECC TCM Example is failing
    <td> SDL
    <td> 10.01.00
    <td> None
</tr>

<tr>
    <td> [ EXT_SITMPUSW-55](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-55)
    <td> AM62x: ENET : A53 : TCP Throughput drop in iperf application running on FreeRTOS A53 core
    <td> Ethernet
    <td> 10.01.00
    <td> Issue is seen only with 1Gbps Full Duplex link speed. Any other link speed such as 100 Mbps link speed shall work seemlessly
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

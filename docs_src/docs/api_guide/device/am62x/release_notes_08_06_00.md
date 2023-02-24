# Release Notes 08.06.00 {#RELEASE_NOTES_08_06_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.

## Device and Validation Information


SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62x  | M4F, R5F        | AM62x SK EVM (referred to as am62x-sk in code), AM62x SK LP EVM (referred to as am62x-sk-lp in code)  | Windows 10 64b or Ubuntu 18.04 64b


## Features Added in This Release

Feature                                                                                         | Module
------------------------------------------------------------------------------------------------|-----------------------------------
DMA Support on OSPI NOR and OSPI NAND SBLs                                                      | Bootloader
MCU Domain reset isolation example                                                              | Safety Examples
OTP Writer example                                                                              | OTP
HS-FS and HS-SE support                                                                         | Bootloader
Device Manager is available as source in MCU+SDK                                                | Device Manager
I2C, SPI, GPIO, MCAN, IPC, UART drivers and examples for DM R5  (WKUP_R5)                       | I2C, SPI, GPIO, MCAN, IPC, UART
Support for ESM, MCRC, RTI, DCC, VTM, STOG, PBIST, MTOG, POK, ECC modules are added as part of SDL  | SDL

## Dependent Tools and Compiler Information

Tools                   | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | M4F, R5F       | @VAR_CCS_VERSION
SysConfig               | M4F, R5F       | @VAR_SYSCFG_VERSION, build @VAR_SYSCFG_BUILD
TI ARM CLANG            | M4F, R5F       | @VAR_TI_ARM_CLANG_VERSION
FreeRTOS Kernel         | M4F, R5F       | @VAR_FREERTOS_KERNEL_VERSION

## Key Features

### OS Kernel

OS              | Supported CPUs  | SysConfig Support
----------------|-----------------|-------------------
FreeRTOS Kernel | M4F, R5F        | NA
FreeRTOS POSIX  | M4F             | NA
NO RTOS         | M4F, R5F        | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs  | SysConfig Support | OS support
------------------|-----------------|-------------------|------------------
Address Translate | M4F, R5F        | YES               | FreeRTOS, NORTOS
Cache             | R5F             | YES               | FreeRTOS, NORTOS
Clock             | M4F, R5F        | YES               | FreeRTOS, NORTOS
CycleCounter      | M4F, R5F        | NA                | FreeRTOS, NORTOS
Debug             | M4F, R5F        | YES               | FreeRTOS, NORTOS
Heap              | M4F, R5F        | NA                | FreeRTOS, NORTOS
Hwi               | M4F, R5F        | YES               | FreeRTOS, NORTOS
MPU               | M4F, R5F        | YES               | FreeRTOS, NORTOS
Semaphore         | M4F, R5F        | NA                | FreeRTOS, NORTOS
Task              | M4F, R5F        | NA                | FreeRTOS
Timer             | M4F, R5F        | YES               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | R5F            | YES               | Yes         |   Yes       | NORTOS
OSPI NAND | R5F            | YES               | No          |   Yes       | NORTOS
EMMC      | R5F            | YES               | NA          |   NA        | NORTOS
UART      | R5F            | YES               | NA          |   No        | NORTOS


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
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=2>GPIO</td>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=2>MCAN</td>
        <td>Main</td>
        <td>R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>R5F</td>
        <td>YES</td>
    </tr>
</table>

\note Refer \ref MAIN_DOMAIN_PERIPHERAL_FROM_MCU for accessing main/wakeup peripherals from M4F.
### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
Flash      | R5F            | YES

### Software Diagnostic Library (SDL)

SDL Module| Supported CPUs | SysConfig Support
----------|----------------|-------------------
ESM       | M4F, R5F       | NO
MCRC      | M4F, R5F       | NO
RTI       | M4F, R5F       | NO
DCC       | M4F, R5F       | NO
VTM       | M4F, R5F       | NO
STOG      | M4F            | NO
PBIST     | M4F, R5F       | NO
MTOG      | M4F            | NO
POK       | R5F            | NO
ECC       | M4F, R5F       | NO

\note STOG and MTOG on R5F will be supported in future release.

## Fixed Issues

<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
    <th> Resolution/Comments
</tr>
<tr>
    <td> SITSW-1736
    <td> Issue with LPDRR initialization after warm reset is resolved.
    <td> DDR
    <td> 8.4.0
    <td> Fixed
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
    <td> 7.3.0
    <td> Use bash for windows as part of git for windows or don't use -j option
</tr>
<tr>
    <td> SITSW-1382
    <td> MCU UART prints a single character of junk data on the first print after the power cycle of the EVM
    <td> MCU UART
    <td> 8.3.0
    <td> None
</tr>
<tr>
    <td> PROC_SDL-5670
    <td> ECC is not supported for 12 instances. These are CSI_RX_IF_EDC_CTRL_0, ICB_RAMECC, ITE_RAMECC, LPI_RAMECC, comput cluster core0-3 and corepac, USB2SS_16FFC_USB2SS_CORE_AXI2VBUSM_MST_KSBUS_AXI2VBUSM_RDATA_BUFFER, USB2SS_16FFC_USB2SS_CORE_RAMS_MEM_CTRL_RA M0, AM62_MCU_CBASS_SCRP_32B_CLK4_SCR_AM62_MCU_CBASS_SCRP_32B_CLK4_SCR_EDC_CTRL_BUSECC_1, PSRAM16KX32E_PSRAM0_ECC, PSRAM256X32E_PSRAM0_ECC, USB2SS_16FFC_USB2SS_CORE_AXI2VBUSM_MST_KSB US_AXI2VBUSM_RDATA_BUFFER, USB2SS_16FFC_USB2SS_CORE_RAMS_MEM_CTRL_RA M0
    <td> SDL
    <td> 8.6.0
    <td> None. Support will be added in future release.
</tr>
<tr>
    <td> PROC_SDL-5671
    <td> PBIST is not supported for some of the instances. From R5F, PBIST is not supported for MPU instance. From M4F, PBIST is not supported for MPU and MAIN instances. 
    <td> SDL
    <td> 8.6.0
    <td> None. Support will be added in future release.
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
    <td> PHY mode not supported for OSPI NAND SBL
    <td> Bootloader
</tr>
</table>

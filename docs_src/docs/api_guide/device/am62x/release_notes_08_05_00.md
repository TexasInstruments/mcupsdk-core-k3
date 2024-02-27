# Release Notes 08.05.00 {#RELEASE_NOTES_08_05_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.

## Device and Validation Information


SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62x  | M4F, R5F        | AM62x SK EVM (referred to as am62x-sk in code), AM62x SK LP EVM (referred to as am62x-sk-lp in code)  | Windows 10 64b or Ubuntu 18.04 64b



## Dependent Tools and Compiler Information

Tools                   | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | M4F, R5F       | 12.1.0
SysConfig               | M4F, R5F       | 1.14.0, build 2667
TI ARM CLANG            | M4F, R5F       | 2.1.2.LTS
FreeRTOS Kernel         | M4F            | 10.4.3

## Key Features

### OS Kernel

OS              | Supported CPUs  | SysConfig Support
----------------|-----------------|-------------------
FreeRTOS Kernel | M4F         | NA
FreeRTOS POSIX  | M4F         | NA
NO RTOS         | M4F         | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs  | SysConfig Support | OS support
------------------|-----------------|-------------------|------------------
Address Translate | M4F         | YES               | FreeRTOS, NORTOS
Clock             | M4F         | YES               | FreeRTOS, NORTOS
CycleCounter      | M4F         | NA                | FreeRTOS, NORTOS
Debug             | M4F         | YES               | FreeRTOS, NORTOS
Heap              | M4F         | NA                | FreeRTOS, NORTOS
Hwi               | M4F         | YES               | FreeRTOS, NORTOS
MPU               | M4F         | YES               | FreeRTOS, NORTOS
Semaphore         | M4F         | NA                | FreeRTOS, NORTOS
Task              | M4F         | NA                | FreeRTOS
Timer             | M4F         | YES               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | R5F            | YES               | Yes         |   No        | NORTOS
OSPI NAND | R5F            | YES               | No          |   No        | NORTOS
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
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCAN</td>
        <td>MCU</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>M4F,R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F,R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>M4F,R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>M4F,R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=2>UART</td>
        <td>Main</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F</td>
        <td>YES</td>
    </tr>
</table>

\note Refer \ref MAIN_DOMAIN_PERIPHERAL_FROM_MCU for accessing main/wakeup peripherals from M4F.
### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
Flash      | R5F            | YES

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
    <td> DMA not supported for OSPI NOR, UART SBLs
    <td> Bootloader
</tr>
<tr>
    <td> 3
    <td> DMA, PHY mode not supported for OSPI NAND SBL
    <td> Bootloader
</tr>
</table>

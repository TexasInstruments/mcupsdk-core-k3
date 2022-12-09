# Release Notes 08.04.00 {#RELEASE_NOTES_08_04_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.

## Features Added in This Release

Feature                                                                                         | Module
------------------------------------------------------------------------------------------------|-----------------------------------
SPI driver support is added for M4F                                                             | SPI
OSPI NOR, OSPI NAND, EMMC, UART and NULL SBL support                                            | Bootloader
SBL UART uniflash support                                                                       | Bootloader
FreeRTOS task switch and posix demo examples added                                              | FreeRTOS
Access to main domain GPIO, I2C, SPI and UART from MCU M4 added through sysconfig               | GPIO, I2C, SPI, UART


## Device and Validation Information


SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62x  | M4F, R5F        | AM62x SK EVM (referred to as am62x-sk in code), AM62x SK LP EVM (referred to as am62x-sk-lp in code)  | Windows 10 64b or Ubuntu 18.04 64b



## Dependent Tools and Compiler Information

Tools                   | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | M4F, R5F       | @VAR_CCS_VERSION
SysConfig               | M4F, R5F       | @VAR_SYSCFG_VERSION, build @VAR_SYSCFG_BUILD
TI ARM CLANG            | M4F, R5F       | @VAR_TI_ARM_CLANG_VERSION
FreeRTOS Kernel         | M4F            | @VAR_FREERTOS_KERNEL_VERSION

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

Peripheral | Supported CPUs  | SysConfig Support
-----------|-----------------|-------------------
DDR        | R5F             | YES
I2C        | M4F             | YES
IPC Rpmsg  | M4F             | YES
MCAN       | M4F             | YES
MCSPI      | M4F             | YES
Pinmux     | R5F, M4F        | YES
SOC        | R5F, M4F        | YES
Sciclient  | M4F             | YES
UART       | M4F             | YES

### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
Flash      | R5F            | YES


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

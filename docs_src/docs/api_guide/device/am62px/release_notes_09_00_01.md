# Release Notes 09.00.01 {#RELEASE_NOTES_09_00_01_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

SOC    | Supported CPUs              | EVM                                                    | Host PC
-------|-----------------------------|--------------------------------------------------------|-----------------------------------
AM62P  | MCU R5F, WKUP R5F           | @VAR_BOARD_NAME EVM (referred to as am62px-sk in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release

Feature                                                                                  | Module
-----------------------------------------------------------------------------------------|-----------------------------------
FreeRTOS support on MCU R5F and WKUP R5F                                                 | OS
UART, SCI Client, IPC, GPIO, I2C, MCAN and MCSPI drivers on MCU R5F                      | Drviers
UART, SCI Client, DDR, OSPI, EMMC, IPC and DM on WKUP R5F                                | Drviers
DSS suport on WKUP R5F                                                                   | Drviers
McASP suport on WKUP R5F                                                                 | Drviers

## Dependent Tools and Compiler Information

Tools                   | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, WKUP-R5F        | @VAR_CCS_VERSION
SysConfig               | MCU-R5F, WKUP-R5F        | @VAR_SYSCFG_VERSION, build @VAR_SYSCFG_BUILD
TI ARM CLANG            | MCU-R5F, WKUP-R5F        | @VAR_TI_ARM_CLANG_VERSION
GCC AARCH64             | A53                      | @VAR_GCC_AARCH64_VERSION
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F        | @VAR_FREERTOS_KERNEL_VERSION

## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, WKUP-R5F         | NA
FreeRTOS POSIX  | MCU-R5F                   | NA
NO RTOS         | MCU-R5F, WKUP-R5F         | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs            | SysConfig Support | OS support
------------------|---------------------------|-------------------|------------------
Address Translate | MCU-R5F, WKUP-R5F         | YES               | FreeRTOS, NORTOS
Cache             | MCU-R5F, WKUP-R5F         | YES               | FreeRTOS, NORTOS
Clock             | MCU-R5F, WKUP-R5F         | YES               | FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS, NORTOS
Debug             | MCU-R5F, WKUP-R5F         | YES               | FreeRTOS, NORTOS
Heap              | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS, NORTOS
Hwi               | MCU-R5F, WKUP-R5F         | YES               | FreeRTOS, NORTOS
MPU               | MCU-R5F, WKUP-R5F         | YES               | FreeRTOS, NORTOS
Semaphore         | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS, NORTOS
Task              | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS
Timer             | MCU-R5F, WKUP-R5F         | YES               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | WKUP-R5F       | YES               | YES         |   YES       | NORTOS
EMMC      | WKUP-R5F       | YES               | NA          |   NA        | NORTOS
UART      | WKUP-R5F       | YES               | NA          |   No        | NORTOS


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
        <td>WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>DSS</td>
        <td>Main</td>
        <td>WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=2>GPIO</td>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCAN</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCASP</td>
        <td>Main</td>
        <td>WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>YES</td>
    </tr>
</table>



## Fixed Issues
NA

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
    <td> 9.0.1
    <td> Use bash for windows as part of git for windows or don't use -j option
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
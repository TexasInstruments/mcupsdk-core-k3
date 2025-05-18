# Release Notes 10.01.00 {#RELEASE_NOTES_10_01_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.
\parblock
\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in FreeRTOS in R5F and C75 cores and no-RTOS in C75 cores.\n
\endparblock
\parblock
\endparblock

## Device and Validation Information

SOC    | Supported CPUs                              | EVM                                                    | Host PC
-------|---------------------------------------------|--------------------------------------------------------|-----------------------------------
J722S  | MCU R5F, WKUP R5F, MAIN R5F, C75SS0, C75SS1 | @VAR_BOARD_NAME (referred to as j722s-evm in code)     | Ubuntu 22.04 64b


## Features Added in This Release

Feature                                                                                                     | Module
------------------------------------------------------------------------------------------------------------|-----------------------------------
SafeRTOS support on MAIN R5F, MCU R5F, WKUP R5F, C75SS0 and C75SS1                                          | OS
CPU Load measurement with FreeRTOS, Default exception Handling on R5F                                       | OS
DDR Load measurement on WKUP R5F                                                                            | Drivers
UART PDMA supported on MAIN R5F, MCU R5F, WKUP R5F, C75SS0 and C75SS1                                       | Drivers
PDMA support on MAIN R5F, MCU R5F, WKUP R5F, C75SS0 and C75SS1                                              | Drivers
Serial NAND with DMA and PHY support on MAIN R5F, MCU R5F and WKUP R5F                                      | Drivers
CSI-Rx support for YUV420, YUV422, RGB, Raw formats                                                         | Examples
CSI support for re-transmit stream                                                                          | Examples

## Dependent Tools and Compiler Information

Tools                   | Supported CPUs                               | Version
------------------------|----------------------------------------------|----------------------------------------------
Code Composer Studio    | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1  | @VAR_CCS_VERSION
SysConfig               | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1  | @VAR_SYSCFG_VERSION, build @VAR_SYSCFG_BUILD
TI ARM CLANG            | MCU-R5F, WKUP-R5F, MAIN-R5F                  | @VAR_TI_ARM_CLANG_VERSION
TI CGT                  | C75SS0, C75SS1                               | @VAR_TI_C7000_CGT_VERSION
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1  | @VAR_FREERTOS_KERNEL_VERSION

## Key Features

### OS Kernel

OS              | Supported CPUs                              | SysConfig Support
----------------|---------------------------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | NA
SafeRTOS Kernel | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | NA
NO RTOS         | MCU-R5F, WKUP-R5F, MAIN-R5F                 | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs                              | SysConfig Support | OS support(NoRTOS only on R5F)
------------------|---------------------------------------------|-------------------|-------------------------------
Address Translate | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | YES               | SafeRTOS,FreeRTOS, NORTOS
Cache             | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | YES               | SafeRTOS,FreeRTOS, NORTOS
Clock             | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | YES               | SafeRTOS,FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | NA                | SafeRTOS,FreeRTOS, NORTOS
Debug             | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | YES               | SafeRTOS,FreeRTOS, NORTOS
Heap              | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | NA                | FreeRTOS,NORTOS
Hwi               | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | YES               | SafeRTOS,FreeRTOS, NORTOS
MPU               | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | YES               | SafeRTOS,FreeRTOS, NORTOS
Semaphore         | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | NA                | SafeRTOS,FreeRTOS, NORTOS
Task              | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | NA                | SafeRTOS,FreeRTOS
Timer             | MCU-R5F, WKUP-R5F, MAIN-R5F, C75SS0, C75SS1 | YES               | SafeRTOS,FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support | HLOS Boot(Linux/QNX/U-BOOT)
----------|----------------|-------------------|-------------|-------------|------------|------------------------------
OSPI NOR  | WKUP-R5F       | YES               | YES         |   YES       | NORTOS     | Yes
OSPI NAND | WKUP-R5F       | YES               | YES         |   YES       | NORTOS     | Yes
EMMC      | WKUP-R5F       | YES               | NA          |   NA        | NORTOS     | Yes
UART      | WKUP-R5F       | YES               | NA          |   No        | NORTOS     | No
MMCSD     | WKUP-R5F       | YES               | NA          |   Yes       | NORTOS     | Yes


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
        <td>Wakeup</td>
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
        <td rowspan=3>GPIO</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>MAIN-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
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
        <td rowspan=3>IPC </td>
        <td>Main</td>
        <td>MAIN-R5F, C75SS0, C75SS1</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>UDMA </td>
        <td>Main</td>
        <td>MAIN-R5F, C75SS0, C75SS1</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=1>CSI-Rx </td>
        <td>Main</td>
        <td>MAIN-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=1>CSI-Tx </td>
        <td>Main</td>
        <td>MAIN-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>MCSPI </td>
        <td>Main</td>
        <td>MAIN-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCAN</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>MAIN-R5F, C75SS0, C75SS1</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>YES</td>
    </tr>
     <tr>
        <td rowspan=3>SCIClient</td>
        <td>Main</td>
        <td>MAIN-R5F, C75SS0, C75SS1</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
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

<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
    <th> Applicable Devices
    <th> Resolution/Comments
</tr>
<tr>
    <td> PDK-15021
    <td> [Hwi]: type mismatch for priv (arg) parameter limits C7x usage in high memory 
    <td> DPL
    <td> J722S
    <td> 10.01.00
    <td>  The parameters are fixed to be of same type
</tr>
<tr>
    <td> PDK-15173
    <td> [CSIRX]: incorrect instObj in CsirxDrv_eventDisable API
    <td> CSI2RX
    <td> 10.01.00
    <td> J722S
    <td> Updated the event disable API to reference drvHandle as virtualcontext object 
</tr>
</table>

## Known Issues

NA


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
    <td> CCS can not be used in No Boot mode.
    <td> Use SBL NULL to side load binaries and debug using CCS.
</tr>
</table>
</table>

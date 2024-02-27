# Release Notes 08.06.00 {#RELEASE_NOTES_08_06_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

\cond SOC_AM62AX
SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62Ax | MCU R5F, R5F    | @VAR_BOARD_NAME EVM (referred to as am62ax-sk in code) | Windows 10 64b or Ubuntu 18.04 64b
\endcond

## Features Added in This Release

Feature                                                                                         | Module
------------------------------------------------------------------------------------------------|-----------------------------------
Support for RTI, DCC, STOG, MTOG, POK, ECC modules are added as part of SDL                     | SDL

## Dependent Tools and Compiler Information

Tools                   | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | MCU-R5F        | 12.2.0
SysConfig               | MCU-R5F, R5F   | 1.15.0, build 2826
TI ARM CLANG            | MCU-R5F, R5F   | 2.1.2.LTS
FreeRTOS Kernel         | MCU-R5F, R5F   | 10.4.3

## Key Features

### OS Kernel

OS              | Supported CPUs  | SysConfig Support
----------------|-----------------|-------------------
FreeRTOS Kernel | MCU-R5F, R5F    | NA
FreeRTOS POSIX  | MCU-R5F         | NA
NO RTOS         | MCU-R5F, R5F    | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs  | SysConfig Support | OS support
------------------|-----------------|-------------------|------------------
Address Translate | MCU-R5F, R5F    | YES               | FreeRTOS, NORTOS
Cache             | MCU-R5F, R5F    | YES               | FreeRTOS, NORTOS
Clock             | MCU-R5F, R5F    | YES               | FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, R5F    | NA                | FreeRTOS, NORTOS
Debug             | MCU-R5F, R5F    | YES               | FreeRTOS, NORTOS
Heap              | MCU-R5F, R5F    | NA                | FreeRTOS, NORTOS
Hwi               | MCU-R5F, R5F    | YES               | FreeRTOS, NORTOS
MPU               | MCU-R5F, R5F    | YES               | FreeRTOS, NORTOS
Semaphore         | MCU-R5F, R5F    | NA                | FreeRTOS, NORTOS
Task              | MCU-R5F, R5F    | NA                | FreeRTOS
Timer             | MCU-R5F, R5F    | YES               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
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
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCAN</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>R5F</td>
        <td>YES</td>
    </tr>
</table>

\note Refer \ref MAIN_DOMAIN_PERIPHERAL_FROM_MCU for accessing main/wakeup peripherals from MCU Domain.

### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
Flash      | R5F            | YES
LED        | MCU-R5F        | YES

### SDL

SDL Module| Supported CPUs | SysConfig Support
----------|----------------|-------------------
MCRC      |MCU-R5F         | NO
ESM       |MCU-R5F         | NO
VTM       |MCU-R5F         | NO
DCC       |MCU-R5F         | NO
RTI       |MCU-R5F         | NO
POK       |MCU-R5F         | NO
STOG      |MCU-R5F         | NO
MTOG      |MCU-R5F         | NO
POK       |MCU-R5F         | NO
ECC       |MCU-R5F         | NO

\note PBIST will be supported in future release.

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
    <td> SITSW-2186
    <td> SBL OSPI DMA is not working on the HS-SE devices
    <td> Bootloader
    <td> 8.6.0
    <td> Disable DMA on the OSPI NAND SBL example when HS-SE device is used
</tr>
<tr>
    <td> PROC_SDL-5745
    <td> ECC is not supported for 4 instances. These are SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR, SDL_MCU_MSRAM_256K1_MSRAM32KX64E_ECC_AGGR, SDL_MCU_MSRAM_256K0_MSRAM32KX64E_ECC_AGGR,SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR
    <td> SDL
    <td> 8.6.0
    <td> None. Support will be added in future release.
</tr>
<tr>
    <td> PROC_SDL-5747
    <td> STOG example fails when run continuously. Single step execution works.
    <td> SDL
    <td> 8.6.0
    <td> None. Support will be added in future release.
</tr>

## Limitations

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
</table>
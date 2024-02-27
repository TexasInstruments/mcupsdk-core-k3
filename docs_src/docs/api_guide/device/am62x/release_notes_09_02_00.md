# Release Notes 09.01.00 {#RELEASE_NOTES_09_02_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.

## Device and Validation Information


SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62x  | M4F, R5F        | SK-AM62 (referred as am62x-sk in code), SK-AM62-LP (referred as am62x-sk-lp in code), SK-AM62-SIP (referred as am62x-sip-sk in code) | Windows 10 64b or Ubuntu 18.04 64b


## Features Added in This Release


\attention DeepSleep low power mode (LPM) is not supported if the DM R5 is used for a general purpose application. This is because when the SoC goes to any LPM, the context of peripherals used by DM R5 will be lost. To use DM R5 for a general purpose application, disable LPM support. Refer \ref DISABLE_LPM to know how to disable LPM.

Feature                                                                                  | Module
-----------------------------------------------------------------------------------------|-----------------------------------
TBD                                                                                      | TBD

## Dependent Tools and Compiler Information

Tools                   | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | M4F, R5F       | @VAR_CCS_VERSION
SysConfig               | M4F, R5F       | @VAR_SYSCFG_VERSION, build @VAR_SYSCFG_BUILD
TI ARM CLANG            | M4F, R5F       | @VAR_TI_ARM_CLANG_VERSION
GCC AARCH64             | A53            | @VAR_GCC_AARCH64_VERSION
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
    <tr>
        <td>UDMA</td>
        <td>Main</td>
        <td>R5F</td>
        <td>YES</td>
    </tr>
</table>

\note Refer \ref MAIN_DOMAIN_PERIPHERAL_FROM_MCU for accessing main/wakeup peripherals from MCU Domain.
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
STOG      | M4F, R5F       | NO
PBIST     | M4F, R5F       | NO
MTOG      | M4F            | NO
POK       | M4F, R5F       | NO
ECC       | M4F, R5F       | NO
LBIST     | M4F            | NO

## Fixed Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
</tr>
<tr>
    <td> TBD
    <td> TBD
    <td> TBD
    <td> TBD
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
    <td> SITSW-2269
    <td> DeepSleep Low power mode (LPM) is not supported if the DM R5 is used for a general purpose application.
    <td> DM
    <td> 8.6.0
    <td> None.
</tr>
<tr>
    <td> PROC_SDL-6300
    <td> ECC is not supported for some instances when SDL is executed from M4F. These are SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR, SDL_ICSSM0_ICSS_M_CORE_BORG_ECC_AGGR, SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR, SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR, SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR.
    <td> SDL
    <td> 9.0.0
    <td> None.
</tr>
<tr>
    <td> PROC_SDL-6431
    <td> VIM diagnostics for register read back are not supported.
    <td> SDL
    <td> 9.0.0
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
<tr>
    <td> 3
    <td> LPM is not supported when SBL boot flow. It is supported only with SPL boot flow.
    <td> Bootloader
</tr>
</table>

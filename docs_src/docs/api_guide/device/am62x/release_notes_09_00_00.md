# Release Notes 09.00.00 {#RELEASE_NOTES_09_00_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.

## Device and Validation Information


SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62x  | M4F, R5F        | AM62x SK EVM (referred to as am62x-sk in code), AM62x SK LP EVM (referred to as am62x-sk-lp in code)  | Windows 10 64b or Ubuntu 18.04 64b


## Features Added in This Release


\attention DeepSleep low power mode (LPM) is not supported if the DM R5 is used for a general purpose application. This is because when the SoC goes to any LPM, the context of peripherals used by DM R5 will be lost. To use DM R5 for a general purpose application, disable LPM support. Refer \ref DISABLE_LPM to know how to disable LPM.

Feature                                                                                  | Module
-----------------------------------------------------------------------------------------|-----------------------------------
SBL OSPI runs MCU LBIST and PBIST before loading MCU M4F                                 | SBL
Boottime optimization: Use Authentication type 2                                         | SBL
DDR inline ECC                                                                           | DDR
EMMC init time optimized                                                                 | EMMC
EMMC HS200 support                                                                       | EMMC
Example for monitoring firewall exceptions                                               | Security

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

## Fixed Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
</tr>
<tr>
    <td> SITSW-2569
    <td> SBL was not unlocking the main domain control MMRs, before starting Linux on A53.
    <td> SBL
    <td> 8.4.0 onwards
</tr>
<tr>
    <td> SITSW-2547
    <td> JTAG Unlock of cores not working with bootloader certificate DBG_FULL_ENABLE.
    <td> Makefiles
    <td> 8.4.0 onwards
</tr>
<tr>
    <td> SITSW-2343
    <td> Board configuration missing changes required for CSI-RX
    <td> Board Configuration
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2306
    <td> IPC RP message length on linux example is 96 bytes instead of 512 bytes
    <td> IPC
    <td> 8.3.0 onwards
</tr>
<tr>
    <td> SITSW-2512
    <td> R5F IPC example appimage generated using CCS is not working
    <td> DM
    <td> 8.6.0 onwards
</tr>
<tr>
    <td> SITSW-2397
    <td> SBL not able to write OSPI PHY pattern when expected PHY pattern missing from PHY offset
    <td> SBL
    <td> 8.4.0 onwards
</tr>
<tr>
    <td> SITSW-2057
    <td> SBL not closing the Timer/disabling the interrupts before switching to application on DM R5
    <td> SBL
    <td> 8.4.0 onwards
</tr>
<tr>
    <td> SITSW-1962
    <td> R5 MPU configuration is not reset for all regions before configuring
    <td> MPU
    <td> 8.6.0 onwards
</tr>
<tr>
    <td> SITSW-1766
    <td> Utility elf2rprc not generating correct appimage if data sections have different load and run addresses
    <td> Tools
    <td> 8.4.0 onwards
</tr>
<tr>
    <td> SITSW-2513
    <td> Inconsistency in Sysconfig version used by SDK makefiles & CCS
    <td> Makefiles
    <td> 8.6.0
</tr>
<tr>
    <td> PROC_SDL-5753
    <td> ECC example is not supported on R5F.
    <td> SDL
    <td> 8.6.0
</tr>
<tr>
    <td> PROC_SDL-5742
    <td> PBIST is not supported on Main instance from M4F.
    <td> SDL
    <td> 8.6.0
</tr>
<tr>
    <td> PROC_SDL-5743
    <td> ECC is not supported for 2 instances. These are SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR and SDL_MCU_ECC_AGGR0_SAM62_MCU_ECC_AGGR
    <td> SDL
    <td> 8.6.0
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

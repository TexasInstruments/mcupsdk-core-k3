# Release Notes 10.00.00 {#RELEASE_NOTES_10_00_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

\cond SOC_AM62AX
SOC    | Supported CPUs              | EVM                                                    | Host PC
-------|-----------------------------|--------------------------------------------------------|-----------------------------------
AM62Ax | MCU R5F, DM R5F, A53, C75   | @VAR_BOARD_NAME EVM (referred to as am62ax-sk in code) | Windows 10 64b or Ubuntu 22.04 64b
\endcond

## Features Added in This Release

Feature                                                                                  | Module
-----------------------------------------------------------------------------------------|-----------------------------------
TBD                                                                                      | TBD

### Experimental Features {#EXPERIMENTAL_FEATURES}

\attention Features listed below are early versions and should be considered as "experimental".
\attention Users can evaluate the feature, however the feature is not fully tested at TI side.
\attention TI would not support these feature on public e2e.
\attention Experimental features will be enabled with limited examples and SW modules.

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
A53 FreeRTOS SMP support and A53 FreeRTOS SMP examples              | DPL, FreeRTOS

## Dependent Tools and Compiler Information

Tools                   | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, C75, A53        | @VAR_CCS_VERSION
SysConfig               | MCU-R5F, DM-R5F, C75, A53| @VAR_SYSCFG_VERSION, build @VAR_SYSCFG_BUILD
TI ARM CLANG            | MCU-R5F, DM-R5F          | @VAR_TI_ARM_CLANG_VERSION
GCC AARCH64             | A53                      | @VAR_GCC_AARCH64_VERSION
C7000-CGT               | C75                      | @VAR_TI_C7000_CGT_VERSION
FreeRTOS Kernel         | MCU-R5F, DM-R5F, C75, A53| @VAR_FREERTOS_KERNEL_VERSION
FreeRTOS SMP Kernel     | A53                      | @VAR_FREERTOS_SMP_KERNEL_VERSION

## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, DM-R5F, A53, C75 | NA
FreeRTOS POSIX  | MCU-R5F, A53              | NA
FreeRTOS SMP    | A53                       | NA
No RTOS         | MCU-R5F, DM-R5F, A53      | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs            | SysConfig Support | OS support
------------------|---------------------------|-------------------|------------------
Address Translate | MCU-R5F, DM-R5F           | Yes               | FreeRTOS, NORTOS
Cache             | MCU-R5F, DM-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
Clock             | MCU-R5F, DM-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, DM-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Debug             | MCU-R5F, DM-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
Heap              | MCU-R5F, DM-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Hwi               | MCU-R5F, DM-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
MPU               | MCU-R5F, DM-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
Semaphore         | MCU-R5F, DM-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Task              | MCU-R5F, DM-R5F, A53, C75 | NA                | FreeRTOS
Timer             | MCU-R5F, DM-R5F, A53      | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NAND | DM-R5F         | Yes               | No          |   Yes       | NORTOS
EMMC      | DM-R5F         | Yes               | NA          |   NA        | NORTOS
UART      | DM-R5F         | Yes               | NA          |   No        | NORTOS


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
        <td>DM-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>ECAP</td>
        <td>Main</td>
        <td>DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>EPWM</td>
        <td>Main</td>
        <td>DM-R5F, A53, C75</td>
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
        <td>MCU-R5F, DM-R5F, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCAN</td>
        <td>MCU</td>
        <td>MCU-DM-R5F</td>
        <td>Yes</td>
    <tr>
        <td rowspan>MCASP</td>
        <td>Main</td>
        <td>DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MMCSD</td>
        <td>Main</td>
        <td>DM-R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>OSPI</td>
        <td>Main</td>
        <td>DM-R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SA3UL</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>DM-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>UDMA</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>WDT</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
</table>

\note Refer \ref MAIN_DOMAIN_PERIPHERAL_FROM_MCU for accessing main/wakeup peripherals from MCU Domain.

### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
EEPROM     | MCU-R5F, A53   | Yes
Flash      | DM-R5F, A53    | Yes
LED        | MCU-R5F, A53   | Yes

### SDL

SDL Module| Supported CPUs | SysConfig Support
----------|----------------|-------------------
MCRC      |MCU-R5F         | No
ESM       |MCU-R5F         | No
VTM       |MCU-R5F         | No
DCC       |MCU-R5F         | No
RTI       |MCU-R5F         | No
POK       |MCU-R5F         | No
STOG      |MCU-R5F         | No
MTOG      |MCU-R5F         | No
POK       |MCU-R5F         | No
ECC       |MCU-R5F         | No
PBIST     |MCU-R5F         | No
LBIST     |MCU-R5F         | No


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
    <td> TBD
    <td> TBD
    <td> TBD
    <td> TBD
    <td> TBD
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
    <td> DDR PHY mode not supported for OSPI NAND SBL
    <td> Bootloader
</tr>
</table>
</table>
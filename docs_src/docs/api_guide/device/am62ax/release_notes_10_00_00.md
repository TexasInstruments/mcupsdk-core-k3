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

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
Bad block management support for OSPI NAND                                                     | OSPI
GPIO default value can be configured in sysconfig                                              | GPIO
GPIO direction is set part of sysconfig generated code                                         | GPIO
QoS support                                                                                    | QoS
Early PLL driver in TIFS init updated to follow recommended sequence to avoid PLL instability  | TIFS
PM PLL and HSDIV programing in PLL init updated to remove steps violating the recommendation   | DM

### Experimental Features {#EXPERIMENTAL_FEATURES}

\attention Features listed below are early versions and should be considered as "experimental".
\attention Users can evaluate the feature, however the feature is not fully tested at TI side.
\attention TI would not support these feature on public e2e.
\attention Experimental features will be enabled with limited examples and SW modules.

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
A53 FreeRTOS SMP support and A53 FreeRTOS SMP examples              | DPL, FreeRTOS

## Other Updates on This Release

Update                                                                                   | Module
-----------------------------------------------------------------------------------------|-----------------------------------
ATF Load Address is updated to 0X80000000 from 0x9e780000                                | LinuxAppImageGen, QnxAppImagegen
Linux FDT is added in qnx app image and loaded at DDR 0x88000000                         | QnxAppImagegen
make commands are added in boardcfg makefile to open k3-resource-part tool               | BoardCfg
SBL emmc uart-uniflash config files are added for QNX                                    | Uart Uniflash
OSPI tuning optimizations to redue tuning time                                           | OSPI
I2C driver updated for inclusinve API names                                              | I2C
Bootloader powers off cores if image not present                                         | SBL
DRU UTC support is added in UDMA                                                         | UDMA
Option to skip driver open is added in sysconfig                                         | McASP
FreeRTOS FAT will now work with FreeRTOS application as well                             | FAT FS

## Dependent Tools and Compiler Information
\attention It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.

Tools                   | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, C75, A53        | 12.7.0
SysConfig               | MCU-R5F, DM-R5F, C75, A53| 1.20.0, build 3587
TI ARM CLANG            | MCU-R5F, DM-R5F          | 3.2.2.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
C7000-CGT               | C75                      | 4.1.0.LTS
FreeRTOS Kernel         | MCU-R5F, DM-R5F, C75, A53| 10.6.1
FreeRTOS SMP Kernel     | A53                      | MCUSDK_REL.09.01.00_SMP
TIFS                    | NA                       | 10.00.08



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
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>EQEP</td>
        <td>Main</td>
        <td>DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>GPIO</td>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
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
        <td>MCU-R5F, A53</td>
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
        <td>MCU-R5F, DM-R5F, A53, C75</td>
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

SDL Module   | Supported CPUs | SysConfig Support
-------------|----------------|-------------------
MCRC         |MCU-R5F         | No
ESM          |MCU-R5F         | No
VTM          |MCU-R5F         | No
DCC          |MCU-R5F         | No
RTI          |MCU-R5F         | No
POK          |MCU-R5F         | No
STOG         |MCU-R5F         | No
MTOG         |MCU-R5F         | No
ECC          |MCU-R5F         | No
PBIST        |MCU-R5F         | No
LBIST        |MCU-R5F         | No
ROM Checksum |MCU-R5F         | No


## Fixed Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
</tr>
<tr>
    <td> SITSW-3945
    <td> Issues with the OSPI NAND PHY tuning
    <td> OSPI
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SITSW-4229
    <td> OSPI NAND performance reduction when phy tuning is skipped
    <td> OSPI
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> SITSW-4243
    <td> Enabling DM firmware log causing the DM to go to abort
    <td> DM
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> SITSW-4271
    <td> Update the FSS_CTRL register to support 128MB flash size by default.
    <td> OSPI
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-4282
    <td> Skip tuning is not happenning for sbl stage2 as stage1 closes the drivers.
    <td> OSPI
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> SITSW-4337
    <td> Bootloader_socInitR5FAtcmBtcm function uses global ATCM address resulting in CBASS error
    <td> SBL
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-4345
    <td> A53 core freq is limited to 1250MHz in bootloader
    <td> SBL
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-4417
    <td> No checks on number blocks in a single MMCSD R/W transaction
    <td> MMCSD
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> SITSW-4439
    <td> Match VRING addresses to MCAL driver
    <td> IPC
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-4549
    <td> OSPI Read delay using an older value
    <td> OSPI
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> SITSW-4599
    <td> SysConfig Updates to UART Clock Frequency fails to reflect in ti_drivers_config.c
    <td> UART
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-4611
    <td> Generated tiboot3.bin in SBL examples are copy of GP images instead of HSFS
    <td> SBL
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-4612
    <td> UART driver is initialized late in the sysconfig generated code
    <td> UART
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-4613
    <td> Generation of Board Configuration Binary fails for HS-SE device type
    <td> SBL
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> PROC_SDL-7823
    <td> Setting trim value for non-Ping pong mode POKs accesses invalid offset
    <td> SDL
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> SYSFW-7536
    <td> Sending JTAG unlock certificate to TIFS using T32 JTAG fails
    <td> TIFS
    <td> 09.02.01 onwards
</tr>
<tr>
    <td> SYSFW-7474
    <td> Write access from DMA initiators to RA GCFG region results in firewall exception
    <td> TIFS
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SYSFW-7485
    <td> Update the PLL driver in TIFS boot flow to follow correct sequence
    <td> TIFS
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SYSFW-7463
    <td> TISCI_MSG_GET_CLOCK always return Enabled for input clock
    <td> DM
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SYSFW-7486
    <td> PM: Cleanup additional steps in pll init startup routine
    <td> DM
    <td> 08.06.00 onwards
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
    <td> SYSFW-5992
    <td> Unable to set exact pixel clock for OLDI LCD display / HDMI Pixel clock
    <td> DM
    <td> 08.05.00
    <td> Avoid gving range for SET_CLOCK, use exact values for min, max and target
</tr>
<tr>
    <td> SYSFW-6369
    <td> DM unable to enter deep sleep mode when booting in SBL flow
    <td> DM
    <td> 08.03.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-6432
    <td> Set device API doesn't return Error when PD is in transition state
    <td> DM
    <td> 08.03.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-6426
    <td> Ownership of a firewall region can be transferred to an invalid host
    <td> TIFS
    <td> 08.03.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7096
    <td> TIFS halts when proc auth boot TISCI message is sent for an AES-256 encrypted appimage
    <td> TIFS
    <td> 09.01.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7559
    <td> LPM: In MCU Only mode resume path the MCU_M4 LPSC is ON
    <td> DM
    <td> 10.00.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7571
    <td> LPM: Device IDs higher than 255 will not work with set device constraint
    <td> DM
    <td> 10.00.00
    <td> None.
</tr>
<tr>
    <td> PROC_SDL-6326
    <td> Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F
    <td> LBIST
    <td> 09.00.00
    <td> None
</tr>
<tr>
    <td> PROC_SDL-6299
    <td> ECC is not supported for some instances. These are SDL_CPSW0_CPSW_3GUSS_CORE_ECC_CPSW_ECC_AGGR and SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR.
    <td> SDL
    <td> 09.00.00
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
    <td> DDR PHY mode not supported for OSPI NAND SBL
    <td> Bootloader
</tr>
</table>
</table>

## Upgrade and Compatibility Information

This section lists changes which could affect user applications developed using older SDK versions.
Read this carefully to see if you need to do any changes in your existing application when migrating to this SDK version relative to
previous SDK version. Also refer to older SDK version release notes to see changes in
earlier SDKs.

### Compiler Options

<table>
<tr>
    <th> Module
    <th> Affected API
    <th> Change
    <th> Additional Remarks
</tr>
</table>

### Examples

<table>
<tr>
    <th> Module
    <th> Affected API
    <th> Change
    <th> Additional Remarks
</tr>
</table>

### OS Kernel

<table>
<tr>
    <th> Module
    <th> Affected API
    <th> Change
    <th> Additional Remarks
</tr>
</table>

### SOC Device Drivers

<table>
<tr>
    <th> Module
    <th> Affected API
    <th> Change
    <th> Additional Remarks
</tr>
<tr>
    <td> Bootloader
    <td> Bootloader_parseAndLoadLinuxAppImage
    <td> Bootloader_parseAndLoadLinuxAppImage is removed, Bootloader_parseMultiCoreAppImage is updated to parse and load Linux AppImage
    <td> NA
</table>

### Networking

<table>
<tr>
    <th> Module
    <th> Affected API
    <th> Change
    <th> Additional Remarks
</tr>
</table>

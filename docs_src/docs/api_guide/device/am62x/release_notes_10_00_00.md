# Release Notes 10.00.00 {#RELEASE_NOTES_10_00_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.

## Device and Validation Information


SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62x  | M4F, R5F, A53   | SK-AM62 (referred as am62x-sk in code), SK-AM62-LP (referred as am62x-sk-lp in code), SK-AM62-SIP (referred as am62x-sip-sk in code) | Windows 10 64b or Ubuntu 22.04 64b


## Features Added in This Release


\attention DeepSleep low power mode (LPM) is not supported if the DM R5 is used for a general purpose application. This is because when the SoC goes to any LPM, the context of peripherals used by DM R5 will be lost. To use DM R5 for a general purpose application, disable LPM support. Refer \ref DISABLE_LPM to know how to disable LPM.

Feature                                                                                  | Module
-----------------------------------------------------------------------------------------|-----------------------------------
Bad block management support for OSPI NAND                                               | OSPI
A53 Drivers: ECAP, EPWM, EQEP, GPMC, Spinlock                                            | Drivers
GPIO default value can be configured in sysconfig                                        | GPIO
GPIO direction is set part of sysconfig generated code                                   | GPIO
FreeRTOS FAT is now supported with FreeRTOS                                              | File System
QoS support                                                                              | QoS

### Experimental Features {#EXPERIMENTAL_FEATURES}

\attention Features listed below are early versions and should be considered as "experimental".
\attention Users can evaluate the feature, however the feature is not fully tested at TI side.
\attention TI would not support these feature on public e2e.
\attention Experimental features will be enabled with limited examples and SW modules.

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
A53 FreeRTOS support and A53 FreeRTOS examples                      | DPL, FreeRTOS

## Other Updates on This Release

Update                                                                                   | Module
-----------------------------------------------------------------------------------------|-----------------------------------
ATF Load Address is updated to 0X80000000 from 0x9e780000                                | LinuxAppImageGen, QnxAppImagegen
Linux FDT is added in qnx app image and loaded at DDR 0x88000000                         | QnxAppImagegen
make commands are added in boardcfg makefile to open k3-resource-part tool               | BoardCfg
OSPI tuning optimizations to redue tuning time                                           | OSPI
I2C driver updated for inclusinve API names                                              | I2C
Bootloader powers off cores if image not present                                         | SBL
FreeRTOS FAT will now work with FreeRTOS application as well                             | FAT FS

### FreeRTOS Support on A53
Is                                                      | Is Not
--------------------------------------------------------|--------------------------
FreeRTOS single core support on A53                     | GPU Support 
Drivers listed for A53 in "SOC Device Drivers" section  | Low power mode support
-                                                       | CSI RX Driver
-                                                       | WiFi, USB, BLE Drivers
-                                                       | Safety on A53

## Dependent Tools and Compiler Information

\attention It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.

Tools/Components        | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | M4F, R5F, A53  | 12.7.0
SysConfig               | M4F, R5F, A53  | 1.20.0, build 3587
TI ARM CLANG            | M4F, R5F       | 3.2.2.LTS
GCC AARCH64             | A53            | 9.2-2019.12
FreeRTOS Kernel         | M4F, R5F, A53  | 10.6.1
TIFS                    | NA             | 10.00.08

## Key Features

### OS Kernel

OS              | Supported CPUs  | SysConfig Support
----------------|-----------------|-------------------
FreeRTOS Kernel | M4F, R5F, A53   | NA
FreeRTOS POSIX  | M4F, A53        | NA
No RTOS         | M4F, R5F, A53   | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs  | SysConfig Support | OS support
------------------|-----------------|-------------------|------------------
Address Translate | M4F, R5F        | Yes               | FreeRTOS, NORTOS
Cache             | R5F, A53        | Yes               | FreeRTOS, NORTOS
Clock             | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
CycleCounter      | M4F, R5F, A53   | NA                | FreeRTOS, NORTOS
Debug             | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
Heap              | M4F, R5F, A53   | NA                | FreeRTOS, NORTOS
Hwi               | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
MPU               | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
Semaphore         | M4F, R5F, A53   | NA                | FreeRTOS, NORTOS
Task              | M4F, R5F, A53   | NA                | FreeRTOS
Timer             | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | R5F            | Yes               | Yes         |   Yes       | NORTOS
OSPI NAND | R5F            | Yes               | Yes         |   Yes       | NORTOS
EMMC      | R5F            | Yes               | NA          |   NA        | NORTOS
UART      | R5F            | Yes               | NA          |   No        | NORTOS


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
        <td>Yes</td>
    </tr>
    <tr>
        <td>ECAP</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>EPWM</td>
        <td>Main</td>
        <td>M4F, A53</td>
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
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>GPMC</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCAN</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MMCSD</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>OSPI</td>
        <td>Main</td>
        <td>R5F, A53</td>
        <td>Yes</td>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>M4F, R5F, A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>M4F, R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>UDMA</td>
        <td>Main</td>
        <td>R5F, A53</td>
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
Flash      | R5F            | Yes

### Software Diagnostic Library (SDL)

SDL Module   | Supported CPUs | SysConfig Support
-------------|----------------|-------------------
ESM          | M4F, R5F       | No
MCRC         | M4F, R5F       | No
RTI          | M4F, R5F       | No
DCC          | M4F, R5F       | No
VTM          | M4F, R5F       | No
STOG         | M4F, R5F       | No
PBIST        | M4F, R5F       | No
MTOG         | M4F            | No
POK          | M4F, R5F       | No
ECC          | M4F, R5F       | No
LBIST        | M4F            | No
ROM Checksum | R5F            | No

## Fixed Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
</tr>
<tr>
    <td> SITSW-3920
    <td> DDR Inline ECC example does not work in debug mode on AM62x
    <td> DDR
    <td> 09.01.00 onwards
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
    <td> SITSW-4271
    <td> Update the FSS_CTRL register to support 128MB flash size by default.
    <td> OSPI
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-4282
    <td> Skip tuning is not happenning for sbl stage2 as stage1 closes the drivers.
    <td> OSPI
    <td> 09.01.00 onwards
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
    <td> SITSW-4549
    <td> OSPI Read delay using an older value
    <td> OSPI
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> SITSW-4599
    <td> SysConfig Updates to UART Clock Frequency fails to reflect in ti_drivers_config.c
    <td> UART
    <td> 08.04.00 onwards
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
    <td> SITSW-4630
    <td> Hwip_disable API not working properly on M4F
    <td> DPL
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-4647
    <td> AM62X : PADCFG offset value is missing for B16 pin
    <td> Pinmux
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
    <td> MCUSDK-208
    <td> gmake with -j can sometimes lock up Windows command prompt
    <td> Build
    <td> 07.03.00
    <td> Use bash for windows as part of git for windows or don't use -j option
</tr>
<tr>
    <td> SITSW-2269
    <td> DeepSleep Low power mode (LPM) is not supported if the DM R5 is used for a general purpose application.
    <td> DM
    <td> 08.06.00
    <td> None.
</tr>
<tr>
    <td> SITSW-4001
    <td> On SK-AM62-SIP, SBL with ECC enabled does not boot linux, when the SDRAM index is set to 13
    <td> DDR
    <td> 09.01.00
    <td> None.
</tr>
<tr>
    <td> PROC_SDL-6300
    <td> ECC is not supported for some instances when SDL is executed from M4F. These are SDL_ECC_AGGR0_SAM62_SEC_ECC_AGGR, SDL_ICSSM0_ICSS_M_CORE_BORG_ECC_AGGR, SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR, SDL_PSRAMECC_16K0_PSRAM16KX32E_ECC_AGGR, SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR.
    <td> SDL
    <td> 09.00.00
    <td> None.
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
    <td> PHY mode not supported for OSPI NAND SBL on DDR mode. It is supported for SDR mode only
    <td> Bootloader
</tr>
<tr>
    <td> 3
    <td> LPM is not supported with SBL boot flow. It is supported only with SPL boot flow.
    <td> Bootloader
</tr>
</table>

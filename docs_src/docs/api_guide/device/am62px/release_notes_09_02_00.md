# Release Notes 09.02.00 {#RELEASE_NOTES_09_02_00_PAGE}

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
OSPI NOR tuning algorithm is updated for robustness                                      | OSPI
DDR inline ECC support added                                                             | DDR
APIs to measure DDR usage is added                                                       | DDR
UDMA Examples are added for MCU R5F                                                      | UDMA
Dhryston benchmark examples added for MCU R5F                                            | Examples
Memcpy benchmark examples added for MCU R5F and DM R5F                                   | Examples
TIFS, RM and PM safety checker library and examples are added                            | Safety Checker 
ECAP and EPWM support is added for MCU-R5F                                               | ECAP, EPWM
MCU reset isolation support is added                                                     | Safety
MCU only LPM support added                                                               | IPC
LBIST and PBIST of MCU R5F is done on SBL before booting MCU R5F                         | SBL

## Dependent Tools and Compiler Information

Tools                   | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, WKUP-R5F        | 12.6.0
SysConfig               | MCU-R5F, WKUP-R5F        | 1.19.0, build 3426
TI ARM CLANG            | MCU-R5F, WKUP-R5F        | 3.2.2.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F        | 10.6.1

## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, WKUP-R5F         | NA
FreeRTOS POSIX  | MCU-R5F                   | NA
No RTOS         | MCU-R5F, WKUP-R5F         | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs            | SysConfig Support | OS support
------------------|---------------------------|-------------------|------------------
Address Translate | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
Cache             | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
Clock             | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS, NORTOS
Debug             | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
Heap              | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS, NORTOS
Hwi               | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
MPU               | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS
Semaphore         | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS, NORTOS
Task              | MCU-R5F, WKUP-R5F         | NA                | FreeRTOS
Timer             | MCU-R5F, WKUP-R5F         | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | WKUP-R5F       | Yes               | Yes         |   Yes       | NORTOS
EMMC      | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS
UART      | WKUP-R5F       | Yes               | NA          |   No        | NORTOS

### SDL

SDL Module       | Supported CPUs | SysConfig Support
-----------------|----------------|-------------------
MCRC             |MCU-R5F         | No
ESM              |MCU-R5F         | No
VTM              |MCU-R5F         | No
DCC              |MCU-R5F         | No
ECC              |MCU-R5F         | No
RTI              |MCU-R5F         | No
POK              |MCU-R5F         | No
STOG             |MCU-R5F         | No
MTOG             |MCU-R5F         | No
POK              |MCU-R5F         | No
PBIST            |MCU-R5F         | No
LBIST            |MCU-R5F         | No
ROM_CHECKSUM     |MCU-R5F         | No


\note This is EA(early adopter) version for SDL. GA(General Availability) release will be provided in next release. \n

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
        <td>Yes</td>
    </tr>
    <tr>
        <td>ECAP</td>
        <td>Main</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>EPWM</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>DSS</td>
        <td>Main</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>GPIO</td>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCAN</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCASP</td>
        <td>Main</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
</table>



## Fixed Issues

<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
</tr>
<tr>
    <td> SITSW-2776
    <td> OSPI is broken on SBL Falcon mode
    <td> OSPI
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3100
    <td> MCASP Driver Stop, then MCASP Start does not work
    <td> MCASP
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3353
    <td> UART traces from TIFS M4 are not available
    <td> UART
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3443
    <td> Sysconfig error in MMCSD module on setting Card Type to NO_DEVICE
    <td> MMCSD
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3448
    <td> Issue in the clean target of Linux Appimage makefile on windows
    <td> Build
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3489
    <td> HSM & Linux Appimage build fails with gmake from CCS in Windows
    <td> Build
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3600
    <td> FwdStatus is set as SCISERVER_FORWARD_MSG for secure messages from DM R5 core
    <td> DM
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3606
    <td> OSPI Phase Delay Value is wrong
    <td> OSPI
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3610
    <td> clock mux changes are lost after deepsleep entry/exit
    <td> DM
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3612
    <td> EMMC boot is failing after warm reset
    <td> EMMC
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3645
    <td> Default DMA configs are using invalid ring ranges
    <td> UDMA
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3678
    <td> Failure in importing any example in CCS from AM62P MCU+ SDK
    <td> Build
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3795
    <td> Early splash screen not coming under 200 ms with fast boot
    <td> DSS
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3823
    <td> EMMC CSL header has issue withrespect to STRBSEL
    <td> EMMC
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3845
    <td> Errata i2310 causes erroneous set of UART timeout interrupt
    <td> UART
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> SITSW-3901
    <td> fwl isolation example configures ownership for background region instead of foreground region
    <td> Security Examples
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3902
    <td> Bootloader DMA has redundent cache management policies
    <td> SBL
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3950
    <td> DDR: sdram index field is not cleared before writing
    <td> DDR
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3965
    <td> DDR DFI timeout interrupts are happening in idle state
    <td> DDR
    <td> 09.01.00 onwards
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
    <td> 09.01.0
    <td> Use bash for windows as part of git for windows or don't use -j option
</tr>
<tr>
    <td> SITSW-2269
    <td> DeepSleep Low power mode (LPM) is not supported if the DM R5 is used for a general purpose application.
    <td> DM
    <td> 09.01.00
    <td> None.
</tr>
<tr>
    <td> PROC_SDL-6326
    <td> Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F
    <td> LBIST
    <td> 09.02.00
    <td> None
</tr>
<tr>
    <td> PROC_SDL-7044
    <td> ECC is not supported for some instances. These are
    SDL_DSS_DSI0_K3_DSS_DSI_DSI_TOP_ECC_AGGR_SYS
    SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR
    <td> SDL
    <td> 09.01.00
    <td> None. Support will be added in future release.
</tr>
<tr>
    <td> PROC_SDL-7045
    <td> ESM example is failing.
    <td> SDL
    <td> 09.01.00
    <td> None. Support will be added in future release.
    ESM itself is working when it's integrated in to other SDL components.
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
    <td> 3
    <td> LPM is not supported when SBL boot flow. It is supported only with SPL boot flow.
    <td> Bootloader
</tr>
</table>

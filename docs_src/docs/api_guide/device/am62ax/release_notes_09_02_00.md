# Release Notes 09.02.00 {#RELEASE_NOTES_09_02_00_PAGE}

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
APIs to measure DDR usage is added                                                       | DDR
C7x: ECAP, EPWM driver support is added                                                  | Drivers
A53: EQEP driver support is added                                                        | Drivers
A53: IPC SMP example is added                                                            | IPC
UDMA Examples are added for MCU R5F                                                      | UDMA
Dhryston benchmark examples added for MCU R5F                                            | Examples
Memcpy benchmark examples added for MCU R5F and DM R5F                                   | Examples
TIFS, RM and PM safety checker library and examples are added                            | Safety Checker 
SBL SD now boots C7x core as well                                                        | SBL
PLL Configuration sequence updated to latest recommendation                              | DM

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
Code Composer Studio    | MCU-R5F, C75, A53        | 12.6.0
SysConfig               | MCU-R5F, DM-R5F, C75, A53| 1.19.0, build 3426
TI ARM CLANG            | MCU-R5F, DM-R5F          | 3.2.2.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
C7000-CGT               | C75                      | 4.1.0.LTS
FreeRTOS Kernel         | MCU-R5F, DM-R5F, C75, A53| 10.6.1
FreeRTOS SMP Kernel     | A53                      | MCUSDK_REL.09.01.00_SMP

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
    <td> SITSW-2776
    <td> OSPI is broken on SBL Falcon mode
    <td> OSPI
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SITSW-3100
    <td> MCASP Driver Stop, then MCASP Start does not work
    <td> MCASP
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SITSW-3181
    <td> CycleCounterP_getCount 64b is missing for C7X
    <td> DPL
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SITSW-3353
    <td> UART traces from TIFS M4 are not available
    <td> UART
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-3443
    <td> Sysconfig error in MMCSD module on setting Card Type to NO_DEVICE
    <td> MMCSD
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-3448
    <td> Issue in the clean target of Linux Appimage makefile on windows
    <td> Build
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3488
    <td> CCS log does not work for C75 core
    <td> Linker cmd
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SITSW-3489
    <td> HSM & Linux Appimage build fails with gmake from CCS in Windows
    <td> Build
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3525
    <td> C7x exception logs are not readable
    <td> NA
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SITSW-3559
    <td> SBL SD and SBL SD Linux are broken
    <td> NA
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3600
    <td> FwdStatus is set as SCISERVER_FORWARD_MSG for secure messages from DM R5 core
    <td> DM
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-3610
    <td> clock mux changes are lost after deepsleep entry/exit
    <td> DM
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-3614
    <td> C7x SBl boot fails when L2 memory is used in the application
    <td> SBL
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SITSW-3645
    <td> Default DMA configs are using invalid ring ranges
    <td> UDMA
    <td> 08.06.00 onwards
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
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SITSW-3902
    <td> Bootloader DMA has redundent cache management policies
    <td> SBL
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3921
    <td> DDR Bist Priming does not prime the entire region given in the syscfg
    <td> DDR
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SITSW-3950
    <td> DDR: sdram index field is not cleared before writing
    <td> DDR
    <td> 08.06.00 onwards
</tr>
<tr>
    <td> SITSW-3990
    <td> CSL EMIF header file uses uintptr_t for ECC region start and end address
    <td> DDR
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SITSW-4234
    <td> SBL Uart Linux does not acknowledge 'end of file' message
    <td> SBL
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> PROC_SDL-7267
    <td> SDL_POK_Inst and SDL_PRG_Inst macros defined twice in POK driver
    <td> SDL
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> PROC_SDL-7128
    <td> Remove ESM Error Pin Counter Value Register from static register read API
    <td> SDL
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> PROC_SDL-7048
    <td> DCC: SDL_DCC_getStatus() does not return correct status of DONE and ERR pending interrupts
    <td> SDL
    <td> 09.02.00 onwards
</tr>
<tr>
    <td> SYSFW-6763
    <td> TISCI_MSG_SET_DEVICE_RESETS message returns success for invalid device reset range
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-7056
    <td> Implement New PLL sequence Proposed by HW team
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-6941
    <td> TISCI_MSG_SYS_RESET fails for negative testcase
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-6892
    <td> TISCI Clock api returns success for invalid Clock ID
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-5266
    <td> LPM: USB must not remove reset isolation until LPSC has been reenabled
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-6805
    <td> TISCI_MSG_QUERY_FW_CAPS is giving NACK when send over secure queue
    <td> TIFS
    <td> 09.00.00 onwards
</tr>
<tr>
    <td> SYSFW-6879
    <td> clock_stop API in baremetal disables all configurable interrupts
    <td> TIFS
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SYSFW-6811
    <td> HSM core not allowed to access SA2UL context memory
    <td> TIFS
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
    <td> 08.06.00
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
    <td> DDR PHY mode not supported for OSPI NAND SBL
    <td> Bootloader
</tr>
<tr>
    <td> 3
    <td> LPM is not supported with SBL boot flow. It is supported only with SPL boot flow.
    <td> Bootloader
</tr>
</table>

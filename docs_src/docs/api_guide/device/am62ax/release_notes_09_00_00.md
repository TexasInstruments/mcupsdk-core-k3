# Release Notes 09.00.00 {#RELEASE_NOTES_09_00_00_PAGE}

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
FreeRTOS and FreeRTOS-SMP dual core support on A53                                       | OS
FreeRTOS support on C75                                                                  | OS
SBL support for booting C75 Core                                                         | SBL
SBL OSPI NAND, SBL EMMC, SBL UART and SBL SD support booting RTOS/baremetal on A53 Core  | SBL
SBL OSPI NAND runs MCU LBIST and PBIST before loading MCU R5F                            | SBL
Boottime optimization: Use Authentication type 2                                         | SBL
DDR inline ECC                                                                           | DDR
GPIO, I2C, IPC, Sciclient, UDMA and UART driver support on A53                           | Drivers
I2C, IPC, Sciclient and UART driver support on C75                                       | Drivers
EMMC init time optimized                                                                 | EMMC
EMMC HS200 support                                                                       | EMMC
McASP support on C75 and DM-R5F                                                          | MCASP
MCU reset isolation                                                                      | Safety
Example for monitoring firewall exceptions                                               | Security

### Experimental Features {#EXPERIMENTAL_FEATURES_09_00_00}

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
Code Composer Studio    | MCU-R5F, C75, A53        | 12.3.0
SysConfig               | MCU-R5F, DM-R5F, C75, A53| 1.16.1, build 2960
TI ARM CLANG            | MCU-R5F, DM-R5F          | 2.1.3.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
C7000-CGT               | C75                      | 3.1.0LTS
FreeRTOS Kernel         | MCU-R5F, DM-R5F, C75, A53| 10.4.3


## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, DM-R5F, A53, C75 | NA
FreeRTOS POSIX  | MCU-R5F, A53              | NA
FreeRTOS SMP    | A53(Dual Core)            | NA
NO RTOS         | MCU-R5F, DM-R5F, A53      | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs            | SysConfig Support | OS support
------------------|---------------------------|-------------------|------------------
Address Translate | MCU-R5F, DM-R5F           | YES               | FreeRTOS, NORTOS
Cache             | MCU-R5F, DM-R5F, A53, C75 | YES               | FreeRTOS, NORTOS
Clock             | MCU-R5F, DM-R5F, A53, C75 | YES               | FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, DM-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Debug             | MCU-R5F, DM-R5F, A53, C75 | YES               | FreeRTOS, NORTOS
Heap              | MCU-R5F, DM-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Hwi               | MCU-R5F, DM-R5F, A53, C75 | YES               | FreeRTOS, NORTOS
MPU               | MCU-R5F, DM-R5F, A53, C75 | YES               | FreeRTOS, NORTOS
Semaphore         | MCU-R5F, DM-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Task              | MCU-R5F, DM-R5F, A53, C75 | NA                | FreeRTOS
Timer             | MCU-R5F, DM-R5F, A53      | YES               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NAND | DM-R5F         | YES               | No          |   Yes       | NORTOS
EMMC      | DM-R5F         | YES               | NA          |   NA        | NORTOS
UART      | DM-R5F         | YES               | NA          |   No        | NORTOS


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
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=2>GPIO</td>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>IPC</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCAN</td>
        <td>MCU</td>
        <td>MCU-DM-R5F</td>
        <td>YES</td>
    <tr>
        <td rowspan>MCASP</td>
        <td>Main</td>
        <td>DM-R5F, C75</td>
        <td>YES</td>
    </tr>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>YES</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F, A53, C75</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>DM-R5F</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>UDMA</td>
        <td>Main</td>
        <td>DM-R5F, A53</td>
        <td>YES</td>
    </tr>
</table>

\note Refer \ref MAIN_DOMAIN_PERIPHERAL_FROM_MCU for accessing main/wakeup peripherals from MCU Domain.

### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
Flash      | DM-R5F         | YES
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
PBIST     |MCU-R5F         | NO
LBIST     |MCU-R5F         | NO


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
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2547
    <td> JTAG Unlock of cores not working with bootloader certificate DBG_FULL_ENABLE.
    <td> SBL
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2343
    <td> Board configuration missing changes required for CSI-RX
    <td> Board Configuration
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2336
    <td> SBL is not able to boot DM firmware generated using the Firmware Builder
    <td> SBL
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2306
    <td> IPC RP message length on linux example is 96 bytes instead of 512 bytes
    <td> IPC
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2186
    <td> OSPI DMA is not working on the HS-SE devices
    <td> OSPI, SBL
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2512
    <td> R5F IPC example appimage generated using CCS is not working
    <td> DM
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2397
    <td> SBL not able to write OSPI PHY pattern when expected PHY pattern missing from PHY offset
    <td> SBL
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2057
    <td> SBL not closing the Timer/disabling the interrupts before switching to application on DM R5
    <td> SBL
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-1962
    <td> R5 MPU configuration is not reset for all regions before configuring
    <td> MPU
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-1766
    <td> Utility elf2rprc not generating correct appimage if data sections have different load and run addresses
    <td> MPU
    <td> 8.6.0
</tr>
<tr>
    <td> SITSW-2513
    <td> Inconsistency in Sysconfig version used by SDK makefiles & CCS
    <td> Makefiles
    <td> 8.6.0
</tr>
<tr>
    <td> PROC_SDL-5747
    <td> STOG example fails when run continuously. Single step execution works.
    <td> SDL
    <td> 8.6.0
</tr>
<tr>
    <td> PROC_SDL-6229
    <td> PBIST MAIN INSTANCE is not working for positive test vector.
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
    <td> 8.6.0
    <td> Use bash for windows as part of git for windows or don't use -j option
</tr>
<tr>
    <td> SITSW-2701
    <td> Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F
    <td> LBIST
    <td> 9.0.0
    <td> None
</tr>
<tr>
    <td> SITSW-2737
    <td> DM trace log is not generated on the WKUP UART after the DM is booted.
    <td> DM
    <td> 9.0.0
    <td> None
</tr>
<tr>
    <td> PROC_SDL-6299
    <td> ECC is not supported for some instances. These are SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR, SDL_WKUP_ECC_AGGR1_SAM62A_DM_MCU_ECC_AGGR , SDL_MCU_MSRAM_256K1_MSRAM32KX64E_ECC_AGGR,SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR, SDL_CPSW0_CPSW_3GUSS_CORE_ECC_CPSW_ECC_AGGR, SDL_MCU_MSRAM_256K0_MSRAM32KX64E_ECC_AGGR, SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR, SDL_MCU_ECC_AGGR0_SAM62A_MCU_MCU_ECC_AGGR , SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR , SDL_VPAC0_SAM62A_VPAC_WRAP_IVPAC_TOP_0_PAC_BASE_KSDW_ECC_AGGR, SDL_VPAC0_SAM62A_VPAC_WRAP_IVPAC_TOP_0_VPAC_LDC0_KSDW_ECC_AGGR, SDL_VPAC0_SAM62A_VPAC_WRAP_IVPAC_TOP_0_VPAC_VISS0_KSDW_ECC_AGGR, SDL_MCU_ECC_AGGR1_SAM62A_MCU_PULSAR_UL_ECC_AGGR,
    SDL_C7X256V0_SAM62A_C7XV_WRAP_ECC_AGGR, SDL_USB1_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR, SDL_USB0_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR, SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE0, SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE1, SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE2,
    SDL_COMPUTE_CLUSTER0_SAM62A_A53_512KB_WRAP_A53_DUAL_WRAP_CBA_WRAP_A53_DUAL_WRAP_CBA_COREPAC_ECC_AGGR_CORE3,
    <td> SDL
    <td> 9.0.0
    <td> None. Support will be added in future release.
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
    <td> DDR PHY mode not supported for OSPI NAND SBL
    <td> Bootloader
</tr>
</table>
</table>
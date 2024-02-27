# Release Notes 09.01.00 {#RELEASE_NOTES_09_01_00_PAGE}

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
FreeRTOS kernel upgrated to 10.6.1                                                       | OS
FreeRTOS-SMP quad core support on A53                                       | OS
Priming DDR for inline ECC done through BIST                                             | DDR
SBL SD Linux support                                                                     | SBL
ECAP, EEPROM, EPWM, MCASP, MCSPI, MMCSD, OSPI, WDT, SA3UL support on A53                 | Drivers
GPIO driver support on C7X                                                               | GPIO
Example for isolation of MCU through firewall                                            | Safety
Boottime optimization: Use Authentication type 0                                         | SBL
Boottime optimization: Use BCDMA for DDR to DDR copy during SBL                          | SBL

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
Code Composer Studio    | MCU-R5F, C75, A53        | 12.5.0
SysConfig               | MCU-R5F, DM-R5F, C75, A53| 1.18.0, build 3266
TI ARM CLANG            | MCU-R5F, DM-R5F          | 3.2.0.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
C7000-CGT               | C75                      | 3.1.0LTS
FreeRTOS Kernel         | MCU-R5F, DM-R5F, C75, A53| 10.6.1
FreeRTOS SMP Kernel     | A53                      | MCU_PLUS_SDK_09_01_00-SMP

## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, DM-R5F, A53, C75 | NA
FreeRTOS POSIX  | MCU-R5F, A53              | NA
FreeRTOS SMP    | A53                       | NA
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
        <td>ECAP</td>
        <td>Main</td>
        <td>DM-R5F, A53</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>EPWM</td>
        <td>Main</td>
        <td>DM-R5F, A53</td>
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
        <td>DM-R5F, A53, C75</td>
        <td>YES</td>
    </tr>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
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
        <td>MMCSD</td>
        <td>Main</td>
        <td>DM-R5F, A53</td>
        <td>YES</td>
    </tr>
    <tr>
        <td>OSPI</td>
        <td>Main</td>
        <td>DM-R5F, A53</td>
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
        <td>SA3UL</td>
        <td>Main</td>
        <td>A53</td>
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
    <tr>
        <td>WDT</td>
        <td>Main</td>
        <td>A53</td>
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
    <td> SITSW-2775
    <td> uart_boot_socid.py syntax errors are fixed
    <td> Tools
    <td> 8.6.0 onwards
</tr>
<tr>
    <td> SITSW-2781
    <td> Linux Kernel crashes with SBL EMMC LINUX boot flow
    <td> SBL
    <td> 8.6.0 onwards
</tr>
<tr>
    <td> SITSW-2841
    <td> McASP BCLK and FCLK not generated with external HCLK
    <td> McASP
    <td> 9.0.0 onwards
</tr>
<tr>
    <td> SITSW-2967
    <td> McASP Event deregistering fails if RX not started
    <td> McASP
    <td> 9.0.0 onwards
</tr>
<tr>
    <td> SITSW-3001
    <td> Wrong number conversion from decimal to hex is fixed on MCAN sysconfig
    <td> MCAN
    <td> 8.6.0 onwards
</tr>
<tr>
    <td> SITSW-3037
    <td> Not able to generate ti_dpl_config.c & ti_dpl_config.h file
    <td> A53
    <td> 9.0.0 onwards
</tr>
<tr>
    <td> SITSW-3087
    <td> Conflict of address between APPIMAGE and FDT for FALCON BOOT
    <td> Boot
    <td> 9.0.0 onwards
</tr>
<tr>
    <td> SITSW-3099
    <td> MCASP Example does not work for buffer size 1024 or 512
    <td> McASP
    <td> 9.0.0 onwards
</tr>
<tr>
    <td> SITSW-3162
    <td> MpuP_isEnable check is wrongly verified in 09.00.00 versions
    <td> DPL
    <td> 9.0.0 onwards
</tr>
<tr>
    <td> SITSW-3228
    <td> Use of Incorrect ROM degenerate key
    <td> SBL
    <td> 8.6.0 onwards
</tr>
<tr>
    <td> SITSW-3357
    <td> IPC shutdown acknowledge sent 2 times when shutdown request received from Linux
    <td> IPC
    <td> 9.0.0 onwards
</tr>
<tr>
    <td> SITSW-3384
    <td> UART DMA example not working on A53 FreeRTOS
    <td> IPC
    <td> 9.0.0 onwards
</tr>
<tr>
    <td> SITSW-3388
    <td> CCS makefiles issue with auth_type
    <td> IPC
    <td> 9.0.0 onwards
</tr>

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
# Release Notes 10.01.00

:::{attention}
Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.
:::

:::{note}
The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination.
Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.
:::

## Device and Validation Information

:::{only} SOC_AM62AX
SOC    | Supported CPUs              | EVM                                                    | Host PC
-------|-----------------------------|--------------------------------------------------------|-----------------------------------
AM62Ax | MCU R5F, DM R5F, A53, C75   | {{ VAR_BOARD_NAME }} EVM (referred to as am62ax-sk in code) | Windows 10 64b or Ubuntu 22.04 64b
:::

## Features Added in This Release

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
Support for authentication from DDR when in-place authentication fails from OSPI NOR           | Bootloader
Support for SW version check of binaries through RPRC header                                   | Bootloader
SBL now ensures the cores are switched off if no application image is present                  | Bootloader

### Experimental Features
:::{attention}
Features listed below are early versions and should be considered as "experimental".
:::
:::{attention}
Users can evaluate the feature, however the feature is not fully tested at TI side.
:::
:::{attention}
TI would not support these feature on public e2e.
:::
:::{attention}
Experimental features will be enabled with limited examples and SW modules.
:::

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
A53 FreeRTOS SMP support and A53 FreeRTOS SMP examples              | DPL, FreeRTOS


## Dependent Tools and Compiler Information
:::{attention}
It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.
:::

Tools                   | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, C75, A53        | 12.8.1
SysConfig               | MCU-R5F, DM-R5F, C75, A53| 1.20.0, build 3587
TI ARM CLANG            | MCU-R5F, DM-R5F          | 3.2.2.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
C7000-CGT               | C75                      | 4.1.0.LTS
FreeRTOS Kernel         | MCU-R5F, DM-R5F, C75, A53| 11.1.0
TIFS                    | NA                       | v10.01.08

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

:::{note}
Refer [Accessing main and wakeup domain peripherals from MCU domain](../../developer_guides/main_domain_peripheral_access.md) for accessing main/wakeup peripherals from MCU Domain.
:::

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
    <td> [ EXT_SITMPUSW-34](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-34)
    <td> SBL_UART_UNIFLASH_STAGE2 build fails on removing OSPI and FLASH module in Sysconfig
    <td> Uniflasher
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-5](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-5)
    <td> Potential Infinite loop in OSPI_utilLog2 defined in ospi_v0.c
    <td> OSPI
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-35](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-35)
    <td> MMCSD_initSD always returns SUCCESS
    <td> SD
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-36](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-36)
    <td> MMCSD_initSD does not check the retry variable for failure for OCR command
    <td> SD
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-37](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-37)
    <td> Misleading "File read from SD card" bootloader profile point in the SBL_SD bootloader
    <td> Bootloader
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-38](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-38)
    <td> Remote core getting hangs when doing IPC with HLOS
    <td> IPC
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-39](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-39)
    <td> Error in the CCS build of the SBL examples
    <td> SBL
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-47](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-47)
    <td> Update the DDR configuration with DDR syscfg 9.09+
    <td> SBL
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-41](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-41)
    <td> ClockP_getTicks to use xTaskGetTickCountFromISR() freeRTOS function if it is from ISR
    <td> DPL
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-3](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-3)
    <td> EMMC:The tuning algorithm to re-execute up to 10 times if there is no failing or passing itapdly.
    <td> EMMC
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-42](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-42)
    <td> Enable floating point task save restore for all tasks by default
    <td> DPL
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-43](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-43)
    <td> MMCSD driver doesn't implement the recovery steps for CRC errors
    <td> EMMC
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-44](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-44)
    <td> DebugP_log API returning wrong value
    <td> DPL
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-45](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-45)
    <td> Memcpy: Utils_memcpyWord function doesn't work on 64 bit systems
    <td> Utils
    <td> 10.01.00
</tr>
<tr>
    <td> SITSW-3685
    <td> DM Sciclient ignores flags field for TIFS bound messages
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SITSW-4773
    <td> DM is ignoring the exact flags sent in TISCI message
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-5992
    <td> Unable to set exact pixel clock for OLDI LCD display / HDMI Pixel clock
    <td> DM
    <td> 08.05.00 onwards
</tr>
<tr>
    <td> SYSFW-6432
    <td> Set device API doesn't return Error when PD is in transition state
    <td> DM
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-7559
    <td> In MCU-Only mode resume path the MCU_M4 LPSC is ON
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7571
    <td> Device IDs higher than 255 does not work with set device constraint API
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7602
    <td> RTC count value not getting updated after DeepSleep exit
    <td> DM (LPM)
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-7614
    <td> Unable to configure DSS clock below 15.625MHz
    <td> DM
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7617
    <td> LPM mode selection logic does not check for constraints on all the hosts/devices
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7740
    <td> Only the last latency constraint value passed from a host considered in LPM selection
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7758
    <td> MAIN PLL15 HSDIVs (DM) if updated in SBL flow results in boot failure in later stages
    <td> DM
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7760
    <td> LPM: MCU subsystem (GPIO) clock should not be changed in MCU Only mode
    <td> DM (LPM)
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-6426
    <td> Ownership of a firewall region can be transferred to an invalid host
    <td> TIFS
    <td> 08.03.00 onwards
</tr>
<tr>
    <td> SYSFW-7096
    <td> TIFS halts when proc auth boot message is sent for an AES-256 encrypted image
    <td> TIFS
    <td> 09.01.00 onwards
</tr>
<tr>
    <td> SYSFW-7739
    <td> LPM constraint messages received by TIFS not forwarded to DM
    <td> TIFS
    <td> 10.00.00
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
    <td> SYSFW-7781
    <td> Get device API does not return error when the LPSC is in transition state
    <td> DM
    <td> 10.01.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7811
    <td> Resume from IO Only + DDR mode fails sometimes
    <td> DM (LPM)
    <td> 10.01.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7831
    <td> DMA Resources used by ROM are not cleaned up when resuming from IO Only + DDR mode
    <td> DM (LPM)
    <td> 10.01.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7884
    <td> There is an additional divide by 4 on all clocks of WKUP/MCU GPIO clock mux
    <td> DM
    <td> 10.01.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7897
    <td> Partial I/O mode fails after few hundred iterations
    <td> DM (LPM)
    <td> 10.01.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7034
    <td> Read lock on extended OTP area does not work after doing write lock
    <td> TIFS
    <td> 09.01.00
    <td> None.
</tr>
<tr>
    <td> PROC_SDL-6326
    <td> Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F
    <td> LBIST
    <td> 09.00.00
    <td> None.
</tr>
<tr>
    <td> PROC_SDL-8863
    <td> ECC is failing for 2 Bit VTM selftest
    <td> SDL
    <td> 10.01.00
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8861
    <td> SDL cannot test the following aggregators due to firewall : SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR
    SDL_SMS0_SMS_HSM_ECC
    SDL_SMS0_SMS_TIFS_ECC
    <td> SDL
    <td> 10.01.00
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8792
    <td> System_deinit error in MCRC Semi cpu and Auto CPU examples.
    <td> SDL
    <td> 10.01.00
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
    <td> PHY mode not supported for OSPI NAND SBL on DDR mode. It is supported for SDR mode only
    <td> Bootloader
</tr>
</table>
</table>

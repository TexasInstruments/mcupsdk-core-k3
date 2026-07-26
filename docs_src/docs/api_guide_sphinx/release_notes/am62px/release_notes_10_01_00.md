# Release Notes 10.01.00
:::{admonition} Attention
Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.
:::


:::{admonition} Note
The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.
:::


## Device and Validation Information

SOC    | Supported CPUs              | EVM                                                    | Host PC
-------|-----------------------------|--------------------------------------------------------|-----------------------------------
AM62P  | MCU R5F, WKUP R5F           | {{ VAR_BOARD_NAME }} EVM (referred to as am62px-sk in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
OSPI flash diag application for custom flashes                                                 | OSPI
Support for authentication from DDR when in-place authentication fails from OSPI NOR           | Bootloader
Support for SW version check of binaries through RPRC header                                   | Bootloader
SBL now ensures the cores are switched off if no application image is present                  | Bootloader
SBL NULL: Close flash drivers before jumping to DM application                                 | Bootloader
A53 priv-id is now set to 1 to match other SOCs (instead of previous value 4)                  | TIFS
WKUP-R5 FreeRTOS examples demonstrating usage of ethernet Networking with LwIP and TSN         | Networking

## Additional updates on this release

Update                                                                                                  | Module
--------------------------------------------------------------------------------------------------------|-----------------------------------
Networking Examples have been moved from examples to source/networking/enet/core/                       | Networking
PHY drivers used by networking examples have been moved, and added support through sysconfig-GUI        | Networking

## Dependent Tools and Compiler Information
:::{admonition} Attention
It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.
:::


Tools/Components        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, WKUP-R5F        | 12.8.1
SysConfig               | MCU-R5F, WKUP-R5F        | 1.20.0, build 3587
TI ARM CLANG            | MCU-R5F, WKUP-R5F        | 3.2.2.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F        | 11.1.0
TIFS                    | NA                       | v10.01.08

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
PBIST            |MCU-R5F         | No
LBIST            |MCU-R5F         | No
ROM_CHECKSUM     |MCU-R5F         | No

### Networking

Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested                                                                                                                                                                    | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------
TSN                         | WKUP-R5F       | NO                | FreeRTOS    | gPTP IEEE 802.1 AS-2020 compliant gPTP stack, End Nodes and Bridge mode support, YANG data model configuration  | Multi-Clock Domain
LwIP                        | WKUP-R5F       | YES               | FreeRTOS    | TCP/UDP IP networking stack with and without checksum offload enabled, TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs and raw APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping, LwIP bridge, shared memory driver  | Other LwIP features
Ethernet driver (ENET)      | WKUP-R5F       | YES               | FreeRTOS    | Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW, Strapped PHY (Early Ethernet), cut through switch on CPSW  | RMII mode

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
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-34">EXT_SITMPUSW-34</a>
    <td> <a href="../../examples/examples_drivers_sbl.html">SBL_UART_UNIFLASH_STAGE2</a> build fails on removing OSPI and FLASH module in Sysconfig
    <td> Uniflasher
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-5">EXT_SITMPUSW-5</a>
    <td> Potential Infinite loop in OSPI_utilLog2 defined in ospi_v0.c
    <td> OSPI
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-35">EXT_SITMPUSW-35</a>
    <td> MMCSD_initSD always returns SUCCESS
    <td> SD
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-36">EXT_SITMPUSW-36</a>
    <td> MMCSD_initSD does not check the retry variable for failure for OCR command
    <td> SD
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-37">EXT_SITMPUSW-37</a>
    <td> Misleading "File read from SD card" bootloader profile point in the <a href="../../examples/examples_drivers_sbl.html">SBL_SD</a> bootloader
    <td> Bootloader
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-38">EXT_SITMPUSW-38</a>
    <td> Remote core getting hangs when doing IPC with HLOS
    <td> IPC
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-39">EXT_SITMPUSW-39</a>
    <td> Error in the CCS build of the SBL examples
    <td> SBL
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-47">EXT_SITMPUSW-47</a>
    <td> Update the DDR configuration with DDR syscfg 9.09+
    <td> SBL
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-48">EXT_SITMPUSW-48</a>
    <td> AM62P VTM Temperature output value 0
    <td> SBL
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-41">EXT_SITMPUSW-41</a>
    <td> ClockP_getTicks to use xTaskGetTickCountFromISR() freeRTOS function if it is from ISR
    <td> DPL
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-3">EXT_SITMPUSW-3</a>
    <td> EMMC:The tuning algorithm to re-execute up to 10 times if there is no failing or passing itapdly.
    <td> EMMC
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-42">EXT_SITMPUSW-42</a>
    <td> Enable floating point task save restore for all tasks by default
    <td> DPL
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-43">EXT_SITMPUSW-43</a>
    <td> MMCSD driver doesn't implement the recovery steps for CRC errors
    <td> EMMC
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-49">EXT_SITMPUSW-49</a>
    <td> SBL NULL: Close flash drivers before jumping to DM application
    <td> EMMC
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-44">EXT_SITMPUSW-44</a>
    <td> DebugP_log API returning wrong value
    <td> DPL
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
    <td> SYSFW-7753
    <td> A53 privid is set to 4 and does not match other SOCs value of 1
    <td> TIFS
    <td> 09.02.00 onwards
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
    <td> PMICDRV-194
    <td> CRC value received from the PMIC doesn't match with the calculated value
    <td> PMIC
    <td> 10.00.00
    <td> None.
</tr>
<tr>
    <td> PMICDRV-195
    <td> Getting ADC result code as zero
    <td> PMIC
    <td> 10.00.00
    <td> None.
</tr>
<tr>
    <td> SYSFW-7781
    <td> Get device API does not return error when the LPSC is in transition state
    <td> DM
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
    <td> SYSFW-7899
    <td> LPM configuration is not enabled in HS-SE firmware
    <td> TIFS (LPM)
    <td> 10.01.00
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
    <td> PROC_SDL-8582
    <td> VTM Example is failing in no-bootmode
    <td> SDL
    <td> 10.01.00
    <td> Use UART Bootmode
</tr>
<tr>
    <td> PROC_SDL-8860 (MCAN1), PROC_SDL-7044 (CSI)
    <td> ECC is not supported for some instances. These are
    SDL_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR
    SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR
    <td> SDL
    <td> 10.01.00 (MCAN1), 09.01.00 (CSI)
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8861
    <td> ECC is not supported for some instances due to firewall. These are
    SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR
    SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR
    <td> SDL
    <td> 10.01.00
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8792
    <td> System_deinit error in MCRC Semi CPU and Auto CPU examples
    <td> SDL
    <td> 10.01.00
    <td> None
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
    <td> The <b>ROM</b> startup model for runtime initializations in TI ARM CLANG is not supported/tested in the SDK
    <td> NA
</tr>
<tr>
    <td> 2
    <td> LPM is not supported with SBL boot flow. It is supported only with SPL boot flow.
    <td> Bootloader
</tr>
</table>
</table>

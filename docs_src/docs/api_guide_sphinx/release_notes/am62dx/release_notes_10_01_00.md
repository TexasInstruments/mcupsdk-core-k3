# Release Notes 10.01.00 

```{attention}
Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.
```

```{note}
The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination.
Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.
```

## Device and Validation Information

:::{only} SOC_AM62DX
SOC    | Supported CPUs              | EVM                                                    | Host PC
-------|-----------------------------|--------------------------------------------------------|-----------------------------------
AM62Dx | MCU R5F, WKUP R5F, A53, C75 | {{ VAR_BOARD_NAME }} EVM (referred to as am62dx-evm in code)| Windows 10 64b or Ubuntu 22.04 64b

::::

## Features Added in This Release

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
OSPI flash diag application for custom flashes                                                 | OSPI
Support for authentication from DDR when in-place authentication fails from OSPI NOR           | Bootloader
Support for SW version check of binaries through RPRC header                                   | Bootloader
Support for ECAP and EPWN on C7x and A53                                                       | Drivers
Support for EQEP  on A53                                                                       | Drivers

## Other Updates on This Release

Update                                                                                   | Module
-----------------------------------------------------------------------------------------|-----------------------------------
-                                                                                        |-

## Dependent Tools and Compiler Information
```{attention}
It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.
```

Tools                   | Supported CPUs             | Version
------------------------|----------------------------|-----------------------
Code Composer Studio    | MCU-R5F, C75, A53          | 12.8.1 with AM62D CCS CSP
SysConfig               | MCU-R5F, WKUP-R5F, C75, A53| 1.22.0, build 3893
TI ARM CLANG            | MCU-R5F, WKUP-R5F          | 3.2.2.LTS
GCC AARCH64             | A53                        | 9.2-2019.12
C7000-CGT               | C75                        | 4.1.0.LTS
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F, C75, A53| 11.1.0
TIFS                    | NA                         | v10.01.08

## Key Features

### OS Kernel

OS              | Supported CPUs              | SysConfig Support
----------------|-----------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, WKUP-R5F, A53, C75 | NA
FreeRTOS POSIX  | MCU-R5F, A53                | NA
FreeRTOS SMP    | A53                         | NA
No RTOS         | MCU-R5F, WKUP-R5F, A53      | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs              | SysConfig Support | OS support
------------------|-----------------------------|-------------------|------------------
Address Translate | MCU-R5F, WKUP-R5F           | Yes               | FreeRTOS, NORTOS
Cache             | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
Clock             | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, WKUP-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Debug             | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
Heap              | MCU-R5F, WKUP-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Hwi               | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
MPU               | MCU-R5F, WKUP-R5F, A53, C75 | Yes               | FreeRTOS, NORTOS
Semaphore         | MCU-R5F, WKUP-R5F, A53, C75 | NA                | FreeRTOS, NORTOS
Task              | MCU-R5F, WKUP-R5F, A53, C75 | NA                | FreeRTOS
Timer             | MCU-R5F, WKUP-R5F, A53      | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | WKUP-R5F       | Yes               | No          |   Yes       | NORTOS
EMMC      | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS
UART      | WKUP-R5F       | Yes               | NA          |   No        | NORTOS

### Networking
Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested  | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------|-------------------------
TSN                         | R5F       | NO                | FreeRTOS    | gPTP IEEE 802.1 AS-2020 compliant gPTP stack, End Nodes and Bridge mode support, YANG data model configuration, IEEE 1722 compliant AVTP Stack | Multi-Clock Domain
LwIP                        | R5F       | YES               | FreeRTOS    | TCP/UDP IP networking stack with and without checksum offload enabled, TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs and raw APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping, LwIP bridge, shared memory driver  | Other LwIP features
Ethernet driver (ENET)      | R5F       | YES               | FreeRTOS    | Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW, cut through switch on CPSW  | RMII mode

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
        <td rowspan=3>GPIO</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>I2C</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>IPC</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCAN</td>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Maim</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan>MCASP</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>MMCSD</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>OSPI</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
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
        <td>MCU-R5F, WKUP-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>MCU-R5F, WKUP-R5F, A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UDMA</td>
        <td>Main</td>
        <td>A53, C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>WKUP-R5F</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>WDT</td>
        <td>Main</td>
        <td>A53</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F</td>
        <td>Yes</td>
    </tr>
</table>

```{note}
Refer {ref}`Accessing main and wakeup domain peripherals from MCU domain <MAIN_DOMAIN_PERIPHERAL_FROM_MCU>` for accessing main/wakeup peripherals from MCU Domain.
```

### Board Device Drivers

Peripheral | Supported CPUs      | SysConfig Support
-----------|---------------------|-------------------
EEPROM     | MCU-R5F, A53, C75   | Yes
Flash      | WKUP-R5F, A53       | Yes
LED        | MCU-R5F, A53, C75   | Yes
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
    <td> SBL_UART_UNIFLASH_STAGE2 build fails on removing OSPI and FLASH module in Sysconfig
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
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-38">EXT_SITMPUSW-38</a>
    <td> Remote core getting hangs when doing IPC with HLOS
    <td> IPC
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-40">EXT_SITMPUSW-40</a>
    <td> The SYSFW_IMAGE_INTEGRITY OID is incorrectly mentioned in the comment
    <td> Bootloader
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
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-44">EXT_SITMPUSW-44</a>
    <td> DebugP_log API returning wrong value
    <td> DPL
    <td> 10.01.00
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-45">EXT_SITMPUSW-45</a>
    <td> Memcpy: Utils_memcpyWord function doesn't work on 64 bit systems
    <td> Utils
    <td> 10.01.00
</tr>
<tr>
    <td> SITSW-3685
    <td> DM Sciclient ignores flags field for TIFS bound messages
    <td> DM
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SITSW-4773
    <td> DM is ignoring the exact flags sent in TISCI message
    <td> DM
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-5992
    <td> Unable to set exact pixel clock for OLDI LCD display / HDMI Pixel clock
    <td> DM
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-6432
    <td> Set device API doesn't return Error when PD is in transition state
    <td> DM
    <td> 10.00.00 onwards
</tr>
<tr>
    <td> SYSFW-7614
    <td> Unable to configure DSS clock below 15.625MHz
    <td> DM
    <td> 10.00.00 onwards
</tr>

<tr>
    <td> SYSFW-7758
    <td> MAIN PLL15 HSDIVs (DM) if updated in SBL flow results in boot failure in later stages
    <td> DM
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
    <td> SYSFW-7884
    <td> There is an additional divide by 4 on all clocks of WKUP/MCU GPIO clock mux
    <td> DM
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
    <td> PROC_SDL-8582
    <td> am62dx: VTM is failing in no-bootmode
    <td> SDL
    <td> 10.01.00
    <td> None. This issue will fix in next release.
</tr>
<tr>
    <td> PROC_SDL-6299
    <td> ECC is not supported for some instances. These are SDL_CPSW0_CPSW_3GUSS_CORE_ECC_CPSW_ECC_AGGR and SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR.
    <td> SDL
    <td> 10.01.00
    <td> None. Support will be added in future release.
</tr>
<tr>
    <td> SITSW-6317
    <td> I2C0 SDA line does not get pulled up after random resets of EVM on E2 EVM
    <td> MCU+SDK
    <td> 10.01.00
    <td> None. This issue will be fixed in future release.
</tr>
<tr>
    <td> SITSW-6304
    <td> MCSPI application runs into data abort when operating in DMA mode.
    <td> MCU+SDK
    <td> 10.01.00
    <td> None. This issue will be fixed in future release.
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
</table>
</table>

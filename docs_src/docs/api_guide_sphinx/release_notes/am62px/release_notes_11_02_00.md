# Release Notes 11.02.00
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

:::{admonition} Note
Update of OSPI tuning algorithm on this SDK causes increase in tuning time. Refer {ref}`OSPI NOR Flash Performance <ospi-nor-flash-performance>`
:::


Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
SBL EMMC Falcon boot support                                                                   | SBL
MMCSD Driver on MCU R5F                                                                        | MMCSD
New OSPI tuning algorithm is added                                                             | OSPI
Example to demonstrate VTM triggered SoC reset is added                                        | SDL
ATCM/BTCM reset base toggle support for multistage bootloader                                  | DM
Spread spectrum clocking (SSC) support for Display PLLs                                        | DM
Support to print DM application logs based on board config is added                            | DM

### Experimental Features
:::{admonition} Attention
- Features listed below are early versions and should be considered as "experimental".
- Users can evaluate the feature, however the feature is not fully tested at TI side.
- TI would not support these feature on public e2e.
- Experimental features will be enabled with limited examples and SW modules.
:::


Feature                                                                             | Module
------------------------------------------------------------------------------------|--------------------------
Ethernet traffic sharing accross multiple cores, called Ethernet Firmware           | Networking
C++ SUpport                                                                         | NA

## Dependent Tools and Compiler Information
:::{admonition} Attention
It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recommended and may cause TIFS/ DM functionality to break.
:::


Tools/Components        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, WKUP-R5F        | 20.3.1
SysConfig               | MCU-R5F, WKUP-R5F        | 1.24.2, build 4234
TI ARM CLANG            | MCU-R5F, WKUP-R5F        | 4.0.1.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F        | 11.1.0

## SDK Components

### SYSFW / TIFS

<table>
    <tr>
        <td>Version</td>
        <td>11.02.05</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td><a href="https://software-dl.ti.com/tisci/esd/11_02_05/release_notes/release_notes.html">LINK</a></td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td><a href="https://software-dl.ti.com/tisci/esd/11_02_05/1_intro/TISCI.html">LINK</a></td>
    </tr>
</table>

### Keywriter Package

There is __NO__ Keywriter package available specifically based on this version of
the MCU+ SDK release.

The most recent Keywriter package available (otp_keywriter_am62px_11_01_00) is
based on the MCU+ SDK version 11.01.00 and it is available on the 'Secure resources'
portal of ti.com.

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

:::{admonition} Note
See the updated MCASP usage guidelines in [MCASP](../../components/drivers/mcasp_v1.md) for changes in MCASP driver
:::


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
        <td>MMCSD</td>
        <td>Main</td>
        <td>WKUP-R5F, MCU-R5F</td>
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
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-177">EXT_SITMPUSW-177</a>
    <td> Invalid comment in the linker command files
    <td> Build
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-243">EXT_SITMPUSW-243</a>
    <td> Debug unlock certificate generation script does not generate DER certificate blob
    <td> Build
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-269">EXT_SITMPUSW-269</a>
    <td> LPDDR: DDR PLL reset code issue
    <td> DDR
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-172">EXT_SITMPUSW-172</a>
    <td> DebugP_assert: change so that it does not lock up the entire core
    <td> DPL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-217">EXT_SITMPUSW-217</a>
    <td> ClockP_usleep() getting into infinite loop due to timer wraparound
    <td> DPL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-234">EXT_SITMPUSW-234</a>
    <td> OLDI Single Link Common Mode VOCM Voltage Drop with MCU+SDK
    <td> Display
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-109">EXT_SITMPUSW-109</a>
    <td> Wrong comments on HwiP_inISR() API
    <td> Documentation
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-112">EXT_SITMPUSW-112</a>
    <td> SysConfig does not generate correct FLASH section parameters.
    <td> Flash
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-179">EXT_SITMPUSW-179</a>
    <td> I2C Target Overrun Test Hangs Waiting for Callback
    <td> I2C
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-183">EXT_SITMPUSW-183</a>
    <td> I2c_transfer not returning correct status when transfer mode is set to polling
    <td> I2C
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-191">EXT_SITMPUSW-191</a>
    <td> I2C_transfer() return not handled properly while i2cLldHandle is NULL
    <td> I2C
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-192">EXT_SITMPUSW-192</a>
    <td> SysConfig does not support configuring both 10-bit own addresses for I2C target mode
    <td> I2C
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-194">EXT_SITMPUSW-194</a>
    <td> NACK is not returned to application when performing i2c write in polling mode
    <td> I2C
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-232">EXT_SITMPUSW-232</a>
    <td> I2C target mode with multiple own addresses transaction fails
    <td> I2C
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-117">EXT_SITMPUSW-117</a>
    <td> Linux Kernel IPC Examples are broken
    <td> IPC
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-211">EXT_SITMPUSW-211</a>
    <td> DMA channel teardown sequence is not proper in MCASP_disableDmaTx
    <td> MCASP
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-188">EXT_SITMPUSW-188</a>
    <td> [MCSPI]End of Channel Transfer status check is missing for DMA mode
    <td> MCSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-200">EXT_SITMPUSW-200</a>
    <td> [MCSPI] Timeout mechanism missing to prevent Infinite loops in MCSPI driver
    <td> MCSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-208">EXT_SITMPUSW-208</a>
    <td>  PDMA channels are not aligned properly with the different MCSPI instants
    <td> MCSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-110">EXT_SITMPUSW-110</a>
    <td> eMMC Init Code Missing DLL Register Settings needed for Initial Legacy SDR Mode Phase
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-113">EXT_SITMPUSW-113</a>
    <td> eMMC PHY I/O Calibration not getting executed during eMMC boot
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-115">EXT_SITMPUSW-115</a>
    <td> SDR/DDR mode are not enabled in the Sysconfig for MMCSD
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-123">EXT_SITMPUSW-123</a>
    <td> MMCSD driver does not follow the SWITCH command sequence correctly
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-124">EXT_SITMPUSW-124</a>
    <td> EXTCSD HS_TIMING register is set incorrectly at certain places in the driver
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-125">EXT_SITMPUSW-125</a>
    <td> MMCSD driver uses infinite loop instead of timeout for checking fields of PRESENTSTATE register
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-126">EXT_SITMPUSW-126</a>
    <td> Timing issues with MMCSD host controller driver
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-127">EXT_SITMPUSW-127</a>
    <td> Incorrect handling of the CAPABILITIES register in the eMMC initialization
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-137">EXT_SITMPUSW-137</a>
    <td> Random CRC errors observed for eMMC HS400 mode on random reset test
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-139">EXT_SITMPUSW-139</a>
    <td> Comment and Implementation does not match in the MMCSD_retune
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-153">EXT_SITMPUSW-153</a>
    <td> eMMC Driver Error Interrupt Flags accessed in Wrong Register
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-153">EXT_SITMPUSW-153</a>
    <td> eMMC Init Code ignores early failures and continues Execution
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-155">EXT_SITMPUSW-155</a>
    <td> eMMC Driver Error Recovery Recursion can lead to System Crashes
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-171">EXT_SITMPUSW-171</a>
    <td> MMCSD : Read fails when injecting Command time out  fault
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-176">EXT_SITMPUSW-176</a>
    <td> MMCSD : Read fails when injecting Command Index  fault
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-185">EXT_SITMPUSW-185</a>
    <td> MMCSD : Read times out in HS200 mode after writing in SDR50 mode
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-186">EXT_SITMPUSW-186</a>
    <td> MMCSD : Read fails when injecting Command CRC fault
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-195">EXT_SITMPUSW-195</a>
    <td> MMCSD : Read fails when passing invalid argument.
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-203">EXT_SITMPUSW-203</a>
    <td> eMMC PHY Tuning Status Result Ignored when switching to HS400 Mode
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-204">EXT_SITMPUSW-204</a>
    <td> MMCSD close() is not proper
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-209">EXT_SITMPUSW-209</a>
    <td> Simultaneous FAT transfer fails for the same instance while being accessed from two different tasks.
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-212">EXT_SITMPUSW-212</a>
    <td> MMCSD : Write fails when passing invalid argument.
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-215">EXT_SITMPUSW-215</a>
    <td> MMCSD : Read fails when injecting Command End Bit  fault
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-225">EXT_SITMPUSW-225</a>
    <td> HSDDR50 mode lead to data CRC errors with correct timing values.
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-230">EXT_SITMPUSW-230</a>
    <td> MMCSD close fails after opening the same instance twice.
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-78">EXT_SITMPUSW-78</a>
    <td> MMCSD Sysconfig provides options to configure PHY type
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-84">EXT_SITMPUSW-84</a>
    <td> MMCSD error recovery sequence isn't implemented correctly
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-207">EXT_SITMPUSW-207</a>
    <td> Missing -p flag with strip command to reduce the size of *.out
    <td> Makefiles
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-118">EXT_SITMPUSW-118</a>
    <td> OSPI tuning algorithm finds points in noisy region on rare scenarios
    <td> OSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-158">EXT_SITMPUSW-158</a>
    <td> OSPI_flashExecCmd has a couple of checks where the code may get stuck
    <td> OSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-181">EXT_SITMPUSW-181</a>
    <td> Configured dummy cycles in flash driver contradicts flash data sheet
    <td> OSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-187">EXT_SITMPUSW-187</a>
    <td> OSPI DAC Mode Configuration hardcoded and not based on flashsize
    <td> OSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-190">EXT_SITMPUSW-190</a>
    <td> OSPI_PhyTuneGrapher missing read delay value 4
    <td> OSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-213">EXT_SITMPUSW-213</a>
    <td> OSPI Phy Status Check Missing
    <td> OSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-227">EXT_SITMPUSW-227</a>
    <td> AM62P: fss flash boot size is locking the MMRs
    <td> OSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-240">EXT_SITMPUSW-240</a>
    <td> NOR Flash Fixup missing in SBL NULL
    <td> OSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-85">EXT_SITMPUSW-85</a>
    <td> Flash_eraseSector and Flash_norOspiEraseSector does not erases the mentioned sector.
    <td> OSPI
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-157">EXT_SITMPUSW-157</a>
    <td> gMemBootloaderConfig in the bootloader driver is not thread safe
    <td> SBL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-159">EXT_SITMPUSW-159</a>
    <td> SBL SD is broken on AM62P
    <td> SBL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-189">EXT_SITMPUSW-189</a>
    <td> Secure board configurations by default allows JTAG unlocking
    <td> SBL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-193">EXT_SITMPUSW-193</a>
    <td> DMA is not enabled for SOC Memory boot media in the SysConfig
    <td> SBL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-202">EXT_SITMPUSW-202</a>
    <td> gAppimage is not allocated to the intended section defined in the linker command files
    <td> SBL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-205">EXT_SITMPUSW-205</a>
    <td> """sbl_uart_uniflash_stage2"" is not prebuilt"
    <td> SBL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-121">EXT_SITMPUSW-121</a>
    <td> FORCE bit not book keeped properly for MCSPI DMA mode of operation
    <td> Software
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-226">EXT_SITMPUSW-226</a>
    <td> Improve Sysconfig tool tips for all drivers
    <td> SysConfig
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-174">EXT_SITMPUSW-174</a>
    <td> UDMA: HC/UHC channel allocation fails due to RM config mismatch with CSL defines
    <td> UDMA
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-214">EXT_SITMPUSW-214</a>
    <td> UDMA multiple channel open for the same channel and invalid instance not handling properly
    <td> UDMA
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-13056">EXT_EP-13056</a>
    <td> VTM module sensor reset sequence modification for reliable functionality
    <td> SDL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-13057">EXT_EP-13057</a>
    <td> SDL DCC Seed Value Calculation Deviates from TRM Guidelines
    <td> SDL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-13058">EXT_EP-13058</a>
    <td> PBIST example and tests fail in UART Bootmode
    <td> SDL
</tr>
</table>


## Known Issues


<table>
<tr>
   <th> ID
   <th> Head Line
   <th> Module
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-245">EXT_SITMPUSW-245</a>
    <td> MCU+ SDK LPDDR4 Driver starts DDR Training/Leveling Sequence twice
    <td> DDR
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-251">EXT_SITMPUSW-251</a>
    <td> MCU+ SDK Example Projects using incorrect ARMv7 MPU Attributes for Peripheral Register Region
    <td> Examples
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-28">EXT_SITMPUSW-28</a>
    <td> Outstanding mailbox messages prevent suspend
    <td> IPC
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-114">EXT_SITMPUSW-114</a>
    <td> MMCSD_enableBootPartition implements two mutually exclusive concepts as one function
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-138">EXT_SITMPUSW-138</a>
    <td> MMCSD_read & MMCSD_write function are not designed simple & readable
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-222">EXT_SITMPUSW-222</a>
    <td> MMCSD field Card Type is not ordered logically in the Sysconfig
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-256">EXT_SITMPUSW-256</a>
    <td> Incorrect calculation of rowColEnd in the ext_otp_writeMmr
    <td> OTP
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-135">EXT_SITMPUSW-135</a>
    <td> RTC Test application failing intermittently.
    <td> RTC
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-220">EXT_SITMPUSW-220</a>
    <td> <a href="../../examples/examples_drivers_sbl.html">SBL_SD</a> bootloaders report incorrect boot image size
    <td> SBL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-153">EXT_SITMPUSW-153</a>
    <td> MCU+ SDK CCS Project Build Generates Invalid/Redundant Boot Image Files
    <td> Build
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-258">EXT_SITMPUSW-258</a>
    <td> WKUP UART0 is not working in CallBack mode
    <td> UART
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-259">EXT_SITMPUSW-259</a>
    <td> eMMC retuning may be attempted during the initialization sequence
    <td> MMCSD
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12276">EXT_EP-12276</a>
    <td> ECC: Firewall related aggregators failures - ECC Aggregators SDL_SMS0_SMS_TIFS_ECC, SDL_SMS0_SMS_HSM_ECC, SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR and SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR fail because of firewall access issues faced by SDL
    <td> SDL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12277">EXT_EP-12277</a>
    <td> AM62Px: ECC: SDL_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR aggregator is failing
    <td> SDL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12279">EXT_EP-12279</a>
    <td> CSI RX ECC aggregators are failing on AM62P/AM62X
    <td> SDL
</tr>
<tr>
    <td> <a href="https://sir.ext.ti.com/jira/browse/EXT_EP-12280">EXT_EP-12280</a>
    <td> Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F
    <td> SDL
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
<tr>
    <td> 3
    <td> The EVM is limited to only one MAC address in the EEPROM, applications requiring multiple MAC addresses should enable and configure manual MAC address entry in Sysconfig.
    <td> Networking
</tr>
</table>

## Upgrade and Compatibility Information
This section lists changes which could affect user applications developed using older SDK versions.
Read this carefully to see if you need to do any changes in your existing application when migrating to this SDK version relative to
previous SDK version. Also refer to older SDK version release notes to see changes in
earlier SDKs.


The below table captures the list of migration document sections when migrating from one version to another.
The migration for a partcluar module will be applicable, if you are migrating from older version listed to
newer version listed on the table below.


Module       | Migration guide                        | Older version  | Newer version
-------------|----------------------------------------|----------------| -----------------
Bootloader   |  [Bootloader Migration Guidelines](../../components/drivers/bootloader.md)  &zwj; |   <= 10.01.00  | >= 11.00.00
NETWORKING   |  [Enet MCU+ SDK Update](../../components/networking/enet_lld/enet_mcupsdk_update.md) &zwj;       |   <= 11.01.00  | >= 11.02.00
OSPI         |  [OSPI Migration Guide](../../components/drivers/ospi.md)       &zwj;      |   <= 11.01.00  | >= 11.02.00

### Networking

<table>
<tr>
    <th> Module
    <th> Affected API
    <th> Change
</tr>
<tr>
    <td> TSN
    <td> <code>notify_linkchange</code>
    <td> <code>notify_linkchange</code> function is renamed to <code>cb_lld_notify_linkchange</code>,
          include path `<tsn_combase/tilld/cb_lld_ethernet.h>` in the file that uses `cb_lld_notify_linkchange`.
</tr>
</table>

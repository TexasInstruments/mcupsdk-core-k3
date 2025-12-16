# Release Notes 11.02.00 {#RELEASE_NOTES_11_02_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

\attention FreeRTOS SDK on A53 is provided as is for customers as a reference to implement/validate on their own SW Stack & OS. TI will not support these features on the E2E forum as these are not part of the FreeRTOS SDK product. If these features need to be productized, TI can recommend third parties who can help.

## Device and Validation Information

SOC    | Supported CPUs | EVM                                                    | Host PC
-------|----------------|--------------------------------------------------------|-----------------------------------
AM62L  | A53            | @VAR_BOARD_NAME EVM (referred to as am62lx-evm in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release
\note Update of OSPI tuning algorithm on this SDK causes increase in tuning time. Refer \ref OSPI_DATA_SHEET

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
 New OSPI tuning algorithm is added                                                            | OSPI

## Dependent Tools and Compiler Information

Tools/Components        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | A53                      | 20.3.1
SysConfig               | A53                      | 1.24.2, build 4234
GCC AARCH64             | A53                      | 9.2-2019.12
FreeRTOS Kernel         | A53                      | 11.1.0
TF-A                    | A53                      | 11.00.13

## SDK Components

### TIFS

<table>
    <tr>
        <td>Version</td>
        <td>11.00.12</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_00_12/release_notes/release_notes.html)</td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_00_12/1_intro/TISCI.html)</td>
    </tr>
</table>

## Key Features

### OS Kernel

OS              | Supported CPUs | SysConfig Support
----------------|----------------|-------------------
FreeRTOS Kernel | A53            | NA
FreeRTOS POSIX  | A53            | NA
No RTOS         | A53            | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs  | SysConfig Support | OS support
------------------|-----------------|-------------------|------------------
Address Translate | A53             | Yes               | FreeRTOS, NORTOS
Cache             | A53             | Yes               | FreeRTOS, NORTOS
Clock             | A53             | Yes               | FreeRTOS, NORTOS
CycleCounter      | A53             | NA                | FreeRTOS, NORTOS
Debug             | A53             | Yes               | FreeRTOS, NORTOS
Heap              | A53             | NA                | FreeRTOS, NORTOS
Hwi               | A53             | Yes               | FreeRTOS, NORTOS
MMU               | A53             | Yes               | FreeRTOS, NORTOS
Semaphore         | A53             | NA                | FreeRTOS, NORTOS
Task              | A53             | NA                | FreeRTOS
Timer             | A53             | Yes               | FreeRTOS, NORTOS

### SOC Device Drivers

Peripheral        | Supported CPUs  | SysConfig Support
------------------|-----------------|-------------------
ADC               | A53             | Yes
DSS               | A53             | Yes
ECAP              | A53             | Yes
EPWM              | A53             | Yes
EQEP              | A53             | Yes
GPIO              | A53             | Yes
GTC               | A53             | Yes
I2C               | A53             | Yes
MCAN              | A53             | Yes
MCASP             | A53             | Yes
MCSPI             | A53             | Yes
MMCSD             | A53             | Yes
OSPI              | A53             | Yes
UDMA              | A53             | Yes
UART              | A53             | Yes
WDT               | A53             | Yes

### Networking

Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested                                                                                                                                                                    | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------
LwIP                        | A53            | YES               | FreeRTOS    |  TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping | Other LwIP features
Ethernet driver (ENET)      | A53            | YES               | FreeRTOS    |  Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW  | RMII mode

## Fixed Issues

<table>
<tr>
   <th> ID
   <th> Head Line
   <th> Module
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-242, EXT_SITMPUSW-242}
    <td> AM62L: UDMA : Event notify callback not called with multiple Flows on a single DMA channel
    <td> DMA
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-172, EXT_SITMPUSW-172}
    <td> DebugP_assert: change so that it does not lock up the entire core
    <td> DPL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-217, EXT_SITMPUSW-217}
    <td> ClockP_usleep() getting into infinite loop due to timer wraparound
    <td> DPL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-109, EXT_SITMPUSW-109}
    <td> Wrong comments on HwiP_inISR() API
    <td> Documentation
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-112, EXT_SITMPUSW-112}
    <td> SysConfig does not generate correct FLASH section parameters.
    <td> Flash
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-179, EXT_SITMPUSW-179}
    <td> I2C Target Overrun Test Hangs Waiting for Callback
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-183, EXT_SITMPUSW-183}
    <td> I2c_transfer not returning correct status when transfer mode is set to polling
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-191, EXT_SITMPUSW-191}
    <td> I2C_transfer() return not handled properly while i2cLldHandle is NULL
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-192, EXT_SITMPUSW-192}
    <td> SysConfig does not support configuring both 10-bit own addresses for I2C target mode
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-194, EXT_SITMPUSW-194}
    <td> NACK is not returned to application when performing i2c write in polling mode
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-232, EXT_SITMPUSW-232}
    <td> I2C target mode with multiple own addresses transaction fails
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-211, EXT_SITMPUSW-211}
    <td> DMA channel teardown sequence is not proper in MCASP_disableDmaTx
    <td> MCASP
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-188, EXT_SITMPUSW-188}
    <td> [MCSPI]End of Channel Transfer status check is missing for DMA mode
    <td> MCSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-200, EXT_SITMPUSW-200}
    <td> [MCSPI] Timeout mechanism missing to prevent Infinite loops in MCSPI driver
    <td> MCSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-208, EXT_SITMPUSW-208}
    <td>  PDMA channels are not aligned properly with the different MCSPI instants 
    <td> MCSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-123, EXT_SITMPUSW-123}
    <td> MMCSD driver does not follow the SWITCH command sequence correctly
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-124, EXT_SITMPUSW-124}
    <td> EXTCSD HS_TIMING register is set incorrectly at certain places in the driver
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-125, EXT_SITMPUSW-125}
    <td> MMCSD driver uses infinite loop instead of timeout for checking fields of PRESENTSTATE register
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-126, EXT_SITMPUSW-126}
    <td> Timing issues with MMCSD host controller driver
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-127, EXT_SITMPUSW-127}
    <td> Incorrect handling of the CAPABILITIES register in the eMMC initialization
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-153, EXT_SITMPUSW-153}
    <td> eMMC Driver Error Interrupt Flags accessed in Wrong Register
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-153, EXT_SITMPUSW-153}
    <td> eMMC Init Code ignores early failures and continues Execution
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-155, EXT_SITMPUSW-155}
    <td> eMMC Driver Error Recovery Recursion can lead to System Crashes
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-171, EXT_SITMPUSW-171}
    <td> MMCSD : Read fails when injecting Command time out  fault
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-176, EXT_SITMPUSW-176}
    <td> MMCSD : Read fails when injecting Command Index  fault
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-185, EXT_SITMPUSW-185}
    <td> MMCSD : Read times out in HS200 mode after writing in SDR50 mode 
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-186, EXT_SITMPUSW-186}
    <td> MMCSD : Read fails when injecting Command CRC fault
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-195, EXT_SITMPUSW-195}
    <td> MMCSD : Read fails when passing invalid argument.
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-204, EXT_SITMPUSW-204}
    <td> MMCSD close() is not proper
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-209, EXT_SITMPUSW-209}
    <td> Simultaneous FAT transfer fails for the same instance while being accessed from two different tasks.
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-212, EXT_SITMPUSW-212}
    <td> MMCSD : Write fails when passing invalid argument.
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-215, EXT_SITMPUSW-215}
    <td> MMCSD : Read fails when injecting Command End Bit  fault
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-230, EXT_SITMPUSW-230}
    <td> MMCSD close fails after opening the same instance twice. 
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-78, EXT_SITMPUSW-78}
    <td> MMCSD Sysconfig provides options to configure PHY type
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-84, EXT_SITMPUSW-84}
    <td> MMCSD error recovery sequence isn't implemented correctly
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-207, EXT_SITMPUSW-207}
    <td> Missing -p flag with strip command to reduce the size of *.out
    <td> Makefiles
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-158, EXT_SITMPUSW-158}
    <td> OSPI_flashExecCmd has a couple of checks where the code may get stuck
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-181, EXT_SITMPUSW-181}
    <td> Configured dummy cycles in flash driver contradicts flash data sheet
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-190, EXT_SITMPUSW-190}
    <td> OSPI_PhyTuneGrapher missing read delay value 4
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-213, EXT_SITMPUSW-213}
    <td> OSPI Phy Status Check Missing
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-235, EXT_SITMPUSW-235}
    <td> AM62L : wrong register is reading for the Reset status 
    <td> SOC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-121, EXT_SITMPUSW-121}
    <td> FORCE bit not book keeped properly for MCSPI DMA mode of operation
    <td> Software
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-226, EXT_SITMPUSW-226}
    <td> Improve Sysconfig tool tips for all drivers
    <td> SysConfig
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-174, EXT_SITMPUSW-174}
    <td> UDMA: HC/UHC channel allocation fails due to RM config mismatch with CSL defines
    <td> UDMA
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-214, EXT_SITMPUSW-214}
    <td> UDMA multiple channel open for the same channel and invalid instance not handling properly
    <td> UDMA
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-251, EXT_SITMPUSW-251}
    <td> MCU+ SDK Example Projects using incorrect ARMv7 MPU Attributes for Peripheral Register Region
    <td> Examples
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-251, EXT_SITMPUSW-251}
    <td> AM62L: time: Application crashes due to time() function
    <td> Timer
</tr>
</table>

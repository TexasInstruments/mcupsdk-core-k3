# Release Notes 11.02.00 {#RELEASE_NOTES_11_02_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

\cond SOC_AM62AX
SOC    | Supported CPUs              | EVM                                                    | Host PC
-------|-----------------------------|--------------------------------------------------------|-----------------------------------
AM62Ax | MCU R5F, DM R5F, C75   | @VAR_BOARD_NAME EVM (referred to as am62ax-sk in code) | Windows 10 64b or Ubuntu 22.04 64b
\endcond

## Features Added in This Release

Feature                                                                                      | Module
---------------------------------------------------------------------------------------------|-----------------------------------
 CSI RX camera capture on DM R5                                                              | CSI-RX
 Drive strength adjustment capability in SW                                                  | Pinmux
 SBL EMMC Falcon boot support                                                                | SBL
 Example to demonstrate VTM triggered SoC reset is added                                     | SDL
 ATCM/BTCM reset base toggle support for multistage bootloader                               | DM
 Support to print DM application logs based on board config is added                         | DM
 SafeRTOS DPL support                                                                        | DPL
 Watchdog support for DM R5/WKUP-R5F                                                         | Watchdog
 SBL EMMC FALCON boot support                                                                | SBL
 Enable integrated PBIST self-test on SBL EMMC                                               | SBL 
 Ethernet Firmwars support                                                                   | Ethernet
 WFI in MCU only mode to save power                                                          | LPM
 8S-8S-8S protocol support                                                                   | OSPI
 ROV support in CCS v20                                                                      | ROV
 Interrupt mode in Sciclient                                                                 | SCI Client
 
### Unsupported Features

\attention TI would not support these feature on public e2e.

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
A53 FreeRTOS SMP support and A53 FreeRTOS SMP examples              | DPL, FreeRTOS


## Dependent Tools and Compiler Information
\attention It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.

Tools                   | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | MCU-R5F, C75               | 20.3.1
SysConfig               | MCU-R5F, DM-R5F, C75       | 1.26.2, build 4234
TI ARM CLANG            | MCU-R5F, WKUP-R5F          | 4.0.1.LTS
GCC AARCH64             | A53                        | 9.2-2019.12
C7000-CGT               | C75                        | 5.0.0.LTS
FreeRTOS Kernel         | MCU-R5F, WKUP-R5F, C75, A53| 11.1.0

## SDK Components

### SYSFW / TIFS

<table>
    <tr>
        <td>Version</td>
        <td>11.02.05</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_02_05/release_notes/release_notes.html)</td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_02_05/1_intro/TISCI.html)</td>
    </tr>
</table>

## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | MCU-R5F, DM-R5F, C75      | NA
FreeRTOS POSIX  | MCU-R5F                   | NA
No RTOS         | MCU-R5F, DM-R5F           | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs            | SysConfig Support | OS support
------------------|---------------------------|-------------------|------------------
Address Translate | MCU-R5F, DM-R5F           | Yes               | FreeRTOS, NORTOS
Cache             | MCU-R5F, DM-R5F, C75      | Yes               | FreeRTOS, NORTOS
Clock             | MCU-R5F, DM-R5F, C75      | Yes               | FreeRTOS, NORTOS
CycleCounter      | MCU-R5F, DM-R5F, C75      | NA                | FreeRTOS, NORTOS
Debug             | MCU-R5F, DM-R5F, C75      | Yes               | FreeRTOS, NORTOS
Heap              | MCU-R5F, DM-R5F, C75      | NA                | FreeRTOS, NORTOS
Hwi               | MCU-R5F, DM-R5F, C75      | Yes               | FreeRTOS, NORTOS
MPU               | MCU-R5F, DM-R5F, C75      | Yes               | FreeRTOS, NORTOS
Semaphore         | MCU-R5F, DM-R5F, C75      | NA                | FreeRTOS, NORTOS
Task              | MCU-R5F, DM-R5F, C75      | NA                | FreeRTOS
Timer             | MCU-R5F, DM-R5F           | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NAND | DM-R5F         | Yes               | No          |   Yes       | NORTOS
EMMC      | DM-R5F         | Yes               | NA          |   NA        | NORTOS
UART      | DM-R5F         | Yes               | NA          |   No        | NORTOS


### SOC Device Drivers

\note See the updated MCASP usage guidelines in \ref DRIVERS_MCASP_PAGE for changes in
MCASP driver

<table>
    <tr>
        <th>Peripheral</th>
        <th>Domain</th>
        <th>Supported CPUs</th>
        <th>SysConfig Support</th>
    </tr>
    <tr>
        <td>CSI-RX</td>
        <td>Main</td>
        <td>DM-R5F</td>
        <td>No</td>
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
        <td>DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>EPWM</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>EQEP</td>
        <td>Main</td>
        <td>DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=2>GPIO</td>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>I2C </td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F , C75</td>
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
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCAN</td>
        <td>MCU</td>
        <td>MCU-R5F     </td>
        <td>Yes</td>
    <tr>
        <td rowspan>MCASP</td>
        <td>Main</td>
        <td>DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    </tr>
    <tr>
        <td rowspan=2>MCSPI</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F     </td>
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
        <td>DM-R5F     </td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>OSPI</td>
        <td>Main</td>
        <td>DM-R5F     </td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>Pinmux</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>MCU</td>
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>Wakeup</td>
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>RTC</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F </td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SOC</td>
        <td>NA</td>
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td>SCIClient</td>
        <td>NA</td>
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
    <tr>
        <td rowspan=3>UART</td>
        <td>Main</td>
        <td>MCU-R5F, DM-R5F , C75</td>
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
        <td>MCU-R5F, DM-R5F , C75</td>
        <td>Yes</td>
    </tr>
</table>

\note Refer \ref MAIN_DOMAIN_PERIPHERAL_FROM_MCU for accessing main/wakeup peripherals from MCU Domain.

### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
EEPROM     | MCU-R5F        | Yes
Flash      | DM-R5F         | Yes
LED        | MCU-R5F        | Yes

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
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-177, EXT_SITMPUSW-177}
    <td> Invalid comment in the linker command files
    <td> Build
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-243, EXT_SITMPUSW-243}
    <td> Debug unlock certificate generation script does not generate DER certificate blob
    <td> Build
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-169, EXT_SITMPUSW-169}
    <td> C7x Minimum stack size is increased from 10.1 to 11.0 for AM62A, AM62D
    <td> C7X
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-178, EXT_SITMPUSW-178}
    <td> Incorrect handling of the donedataLen in the SA2UL_contextProcess
    <td> Crypto
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-173, EXT_SITMPUSW-173}
    <td> Incorrect calculation of ptrInput and ptrOutput in the SA2UL_contextProcess
    <td> Crypto
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-269, EXT_SITMPUSW-269}
    <td> LPDDR:  DDR PLL reset code issue
    <td> DDR
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-245, EXT_SITMPUSW-245}
    <td> MCU+ SDK LPDDR4 Driver starts DDR Training/Leveling Sequence twice
    <td> DDR
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-293, EXT_SITMPUSW-293}
    <td> Sciclient driver uses incorrect context for the TISCI_MSG_KEYRING_IMPORT
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-309, EXT_SITMPUSW-309}
    <td> LPM: Spurious wake up on MCU only mode
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-303, EXT_SITMPUSW-303}
    <td> DM does not handle NACK properly for LPM msgs and RM board config msg
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-291, EXT_SITMPUSW-291}
    <td> Wait for Status mechanism via Sciclient API call fails during self reset
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-312, EXT_SITMPUSW-312}
    <td> Incorrect context description of SCICLIENT_CONTEXT_DM2TIFS
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-288, EXT_SITMPUSW-288}
    <td> LPM: Unable to enter LPM in Interrupt Mode
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-162, EXT_SITMPUSW-162}
    <td> Sciclient, update the context ID check in sciclient ISR
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-161, EXT_SITMPUSW-161}
    <td> Possibility of different sequence id initialization in a multi thread environment
    <td> DM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-109, EXT_SITMPUSW-109}
    <td> Wrong comments on HwiP_inISR() API
    <td> Documentation
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-217, EXT_SITMPUSW-217}
    <td> ClockP_usleep() getting into infinite loop due to timer wraparound
    <td> DPL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-196, EXT_SITMPUSW-196}
    <td> ClockP_getTimeUsec() returns 1000 us less than the actual time when it's multiple of 1000 us on C7x core.
    <td> DPL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-172, EXT_SITMPUSW-172}
    <td> DebugP_assert: change so that it does not lock up the entire core
    <td> DPL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-251, EXT_SITMPUSW-251}
    <td> MCU+ SDK Example Projects using incorrect ARMv7 MPU Attributes for Peripheral Register Region
    <td> Examples
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-112, EXT_SITMPUSW-112}
    <td> SysConfig does not generate correct FLASH section parameters.
    <td> Flash
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-297, EXT_SITMPUSW-297}
    <td> Flash Params Not Reflected In Syscfg
    <td> FLASH
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-301, EXT_SITMPUSW-301}
    <td> OSPI_norFlashInit1s1s1s has an implementation of wait for 500 milliseconds instead of microseconds
    <td> Flash
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-282, EXT_SITMPUSW-282}
    <td> Sysconfig not generating code for GPIO Trigger
    <td> GPIO
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-194, EXT_SITMPUSW-194}
    <td> NACK is not returned to application when performing i2c write in polling mode
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-192, EXT_SITMPUSW-192}
    <td> SysConfig does not support configuring both 10-bit own addresses for I2C target mode
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-232, EXT_SITMPUSW-232}
    <td> I2C target mode with multiple own addresses transaction fails
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-183, EXT_SITMPUSW-183}
    <td> I2c_transfer not returning correct status when transfer mode is set to polling
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-179, EXT_SITMPUSW-179}
    <td> I2C Target Overrun Test Hangs Waiting for Callback
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-279, EXT_SITMPUSW-279}
    <td> I2C close is not working properly during error conditions
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-191, EXT_SITMPUSW-191}
    <td> I2C_transfer() return not handled properly while i2cLldHandle is NULL
    <td> I2C
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-117, EXT_SITMPUSW-117}
    <td> Linux Kernel IPC Examples are broken
    <td> IPC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-207, EXT_SITMPUSW-207}
    <td> Missing -p flag with strip command to reduce the size of *.out
    <td> Makefiles
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-211, EXT_SITMPUSW-211}
    <td> DMA channel teardown sequence is not proper in MCASP_disableDmaTx
    <td> MCASP
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-200, EXT_SITMPUSW-200}
    <td> [MCSPI] Timeout mechanism missing to prevent Infinite loops in MCSPI driver
    <td> MCSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-188, EXT_SITMPUSW-188}
    <td> [MCSPI]End of Channel Transfer status check is missing for DMA mode
    <td> MCSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-208, EXT_SITMPUSW-208}
    <td> PDMA channels are not aligned properly with the different MCSPI instants
    <td> MCSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-121, EXT_SITMPUSW-121}
    <td> FORCE bit not book keeped properly for MCSPI DMA mode of operation
    <td> MCSPI
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-215, EXT_SITMPUSW-215}
    <td> MMCSD : Read fails when injecting Command End Bit  fault
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-212, EXT_SITMPUSW-212}
    <td> MMCSD : Write fails when passing invalid argument.
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-185, EXT_SITMPUSW-185}
    <td> MMCSD : Read times out in HS200 mode after writing in SDR50 mode
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-198, EXT_SITMPUSW-198}
    <td> MMCSD : EMMC clock validation fails in C7 core
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-230, EXT_SITMPUSW-230}
    <td> MMCSD close fails after opening the same instance twice.
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-209, EXT_SITMPUSW-209}
    <td> Simultaneous FAT transfer fails for the same instance while being accessed from two different tasks.
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-153, EXT_SITMPUSW-153}
    <td> eMMC Driver Error Interrupt Flags accessed in Wrong Register
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-204, EXT_SITMPUSW-204}
    <td> MMCSD close() is not proper
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-110, EXT_SITMPUSW-110}
    <td> eMMC Init Code Missing DLL Register Settings needed for Initial Legacy SDR Mode Phase
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-113, EXT_SITMPUSW-113}
    <td> eMMC PHY I/O Calibration not getting executed during eMMC boot
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-125, EXT_SITMPUSW-125}
    <td> MMCSD driver uses infinite loop instead of timeout for checking fields of PRESENTSTATE register
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-124, EXT_SITMPUSW-124}
    <td> EXTCSD HS_TIMING register is set incorrectly at certain places in the driver
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-123, EXT_SITMPUSW-123}
    <td> MMCSD driver does not follow the SWITCH command sequence correctly
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-126, EXT_SITMPUSW-126}
    <td> Timing issues with MMCSD host controller driver
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-84, EXT_SITMPUSW-84}
    <td> MMCSD error recovery sequence isn't implemented correctly
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-78, EXT_SITMPUSW-78}
    <td> MMCSD Sysconfig provides options to configure PHY type
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-127, EXT_SITMPUSW-127}
    <td> Incorrect handling of the CAPABILITIES register in the eMMC initialization
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-114, EXT_SITMPUSW-114}
    <td> MMCSD_enableBootPartition implements two mutually exclusive concepts as one function
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-213, EXT_SITMPUSW-213}
    <td> OSPI Phy Status Check Missing
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-190, EXT_SITMPUSW-190}
    <td> OSPI_PhyTuneGrapher missing read delay value 4
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-187, EXT_SITMPUSW-187}
    <td> OSPI DAC Mode Configuration hardcoded and not based on flashsize
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-158, EXT_SITMPUSW-158}
    <td> OSPI_flashExecCmd has a couple of checks where the code may get stuck
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-231, EXT_SITMPUSW-231}
    <td> OSPI NAND Writes DAC enable
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-295, EXT_SITMPUSW-295}
    <td> Flash Close Logic Requires OSPI Handle to be reset to 1S-1S-1S
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-280, EXT_SITMPUSW-280}
    <td> OSPI Indac Mode Should Check for odd bytes
    <td> OSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-256, EXT_SITMPUSW-256}
    <td> Incorrect calculation of rowColEnd in the ext_otp_writeMmr
    <td> OTP
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-107, EXT_SITMPUSW-107}
    <td> AM62A : Reset Isolation sequence is wrong
    <td> RESET
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-202, EXT_SITMPUSW-202}
    <td> gAppimage is not allocated to the intended section defined in the linker command files
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-193, EXT_SITMPUSW-193}
    <td> DMA is not enabled for SOC Memory boot media in the SysConfig
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-189, EXT_SITMPUSW-189}
    <td> Secure board configurations by default allows JTAG unlocking
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-133, EXT_SITMPUSW-133}
    <td> Falcon Boot through SBL is not supported
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-122, EXT_SITMPUSW-122}
    <td> HSM core does not boot
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-205, EXT_SITMPUSW-205}
    <td> "sbl_uart_uniflash_stage2" is not prebuilt
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-292, EXT_SITMPUSW-292}
    <td> Bootloader_socOpenFirewalls is called before System_init in the SBLs
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-226, EXT_SITMPUSW-226}
    <td> Improve Sysconfig tool tips for all drivers
    <td> SysConfig
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-281, EXT_SITMPUSW-281}
    <td> UART: UART_open fails when NULL argument is passed as UART_Params argument
    <td> UART
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
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-13057, EXT_EP-13057}
    <td> SDL DCC Seed Value Calculation Deviates from TRM Guidelines
    <td> SDL-DCC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-13058, EXT_EP-13058}
    <td> PBIST Example/FT/UT fail in UART Bootmode
    <td> SDL-PBIST
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-13056, EXT_EP-13056}
    <td> VTM module sensor reset sequence modification for reliable functionality
    <td> SDL-VTM
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-214, EXT_SITMPUSW-214}
    <td> WDT: Hang due to no valid argument check in APIs
    <td> Watchdog
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-13267, EXT_EP-13267}
    <td> SDL ESM: Wrong instance argument in SDL_ESM_loInterruptHandler causing misidentification of ESM0 interrupts
    <td> SDL-ESM
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
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-219, EXT_SITMPUSW-219}
    <td> AM62D/A/275: C7x `portGET_RUN_TIME_COUNTER_VALUE` API uses hard coded CPU Freq
    <td> FreeRTOS
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-28, EXT_SITMPUSW-28}
    <td> Outstanding mailbox messages prevent suspend
    <td> IPC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-224, EXT_SITMPUSW-224}
    <td> Mcasp :  Not working on interrupt mode
    <td> MCASP
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-246, EXT_SITMPUSW-246}
    <td> AM62A : MCSPI DMA channels Teardown Failures When DMA transaction is Incomplete
    <td> MCSPI
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-222, EXT_SITMPUSW-222}
    <td> MMCSD field Card Type is not ordered logically in the Sysconfig
    <td> MMCSD
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-220, EXT_SITMPUSW-220}
    <td> SBL_SD bootloaders report incorrect boot image size
    <td> SBL
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-329, EXT_SITMPUSW-329}
    <td> Incorrect Value of UART_EFR2_TIMEOUT_BEHAVE_MASK
    <td> UART
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-324, EXT_SITMPUSW-324}
    <td> UART_udmaIsrTx does not handles continuous Callbacks properly
    <td> UART
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12281, EXT_EP-12281}
    <td> AM62A: ECC: ECC is failing for 2 Bit VTM selftest
    <td> SDL-ECC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12276, EXT_EP-12276}
    <td> ECC: Firewall related aggregators failures
    <td> SDL-ECC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12283, EXT_EP-12283}
    <td> ECC aggregators CPSW0, CSI RX are failing on AM62A and CPSW0 on AM62D.
    <td> SDL-ECC
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-13265, EXT_EP-13265}
    <td> MCU R5 ECC Aggr init fails when MCU LBIST is enabled in bootloader
    <td> SDL-LBIST
</tr>
<tr>
    <td> \htmllink{https://sir.ext.ti.com/jira/browse/EXT_EP-12280, EXT_EP-12280}
    <td> Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F
    <td> SDL-LBIST
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
Bootloader   |  \ref BOOTLOADER_MIGRATION_GUIDELINE  &zwj; |   <= 10.01.00  | >= 11.00.00
OSPI         |  \ref OSPI_MIGRATION_GUIDE     &zwj;         |   <= 11.01.00  | >= 11.02.00
Watchdog     |  \ref WATCHDOG_11_2_MIGRATION  &zwj;         |   <= 11.01.00  | >= 11.02.00
SCI Server   |  \ref SCISERVER_11_2_MIGRATION  &zwj;        |   <= 11.01.00  | >= 11.02.00

### Networking

<table>
<tr>
    <th> Module
    <th> Affected API
    <th> Change
</tr>
<tr>
    <td> TSN
    <td> `notify_linkchange`
    <td> `notify_linkchange` function is renamed to `cb_lld_notify_linkchange`,
          include path `<tsn_combase/tilld/cb_lld_ethernet.h>` in the file that uses `cb_lld_notify_linkchange`.
</tr>
</table>

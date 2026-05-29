# Release Notes 11.03.00 {#RELEASE_NOTES_11_03_00_PAGE}

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

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
-                                                                                              | -

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
SysConfig               | MCU-R5F, DM-R5F, C75       | 1.24.2, build 4234
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

For SOC device driver support information per CPU, refer to \ref BUILDSHEET.

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
    <td> -
    <td> -
    <td> -
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
    <td> -
    <td> -
    <td> -
</tr>
</table>

## Errata
<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> SDK Status
    <th> Remarks
</tr>
<tr>
    <td> i2310
    <td> USART: Erroneous clear/trigger of timeout interrupt
    <td> UART
    <td> Implemented
    <td> Workaround implemented in UART_i2310WA() in the UART driver
</tr>
<tr>
    <td> i2311
    <td> USART: Spurious DMA Interrupts
    <td> UART
    <td> Implemented
    <td> FIFO trigger levels are always set to power-of-2 values via SysConfig
</tr>
<tr>
    <td> i2189
    <td> OSPI: Controller PHY Tuning Algorithm
    <td> OSPI
    <td> Implemented
    <td> PHY tuning algorithm implemented in OSPI driver per SPRACT2
</tr>
<tr>
    <td> i2249
    <td> OSPI: Internal PHY Loopback and Internal Pad Loopback clocking modes with DDR timing inoperable
    <td> OSPI
    <td> Implemented
    <td> SDK uses only unaffected clocking modes (DQS with PHY or No PHY mode)
</tr>
<tr>
    <td> i2383
    <td> OSPI: 2-byte address is not supported in PHY DDR mode
    <td> OSPI
    <td> Application Related
    <td> Application must configure 3-byte or 4-byte addressing mode for OSPI flash
</tr>
<tr>
    <td> i2431
    <td> BCDMA: RX Channel can lockup in certain scenarios
    <td> BCDMA
    <td> Implemented
    <td> SDK drivers set TR EOP flag (TR_FLAGS_EOP=1) and PDMA Z parameter (fifoCnt) to non-zero per workaround
</tr>
<tr>
    <td> i2436
    <td> BCDMA: BCDMA RX_IGNORE_LONG setting in RX CHAN CFG register doesn't work
    <td> BCDMA
    <td> N/A
    <td> RX_IGNORE_LONG is not used in SDK (ignoreLongPkts defaults to FALSE); errata condition cannot be triggered
</tr>
<tr>
    <td> i2134
    <td> USB: 2.0 Compliance Receive Sensitivity Test Limitation
    <td> USB
    <td> N/A
    <td> USB is not supported in AM62Ax MCU+SDK
</tr>
<tr>
    <td> i2409
    <td> USB: USB2 PHY locks up due to short suspend
    <td> USB
    <td> N/A
    <td> USB is not supported in AM62Ax MCU+SDK
</tr>
<tr>
    <td> i2410
    <td> Boot: ROM may fail to boot due to i2409
    <td> Boot
    <td> N/A
    <td> USB is not supported in AM62Ax MCU+SDK
</tr>
<tr>
    <td> i2049
    <td> ECC_AGGR: Potential IP Clockstop/Reset Sequence Hang due to Pending ECC Aggregator Interrupts
    <td> ECC_AGGR
    <td> N/A
    <td> Not applicable for FreeRTOS SDK; relevant only for functional safety (FuSA) use cases
</tr>
<tr>
    <td> i2062
    <td> RAT: Error Interrupt Triggered Even When Error Logging Disable Is Set
    <td> RAT
    <td> N/A
    <td> SDK RAT driver does not use error interrupts or error logging
</tr>
<tr>
    <td> i2087
    <td> C71x: MMA HWA_STATUS Reports Errors Before Application Starts
    <td> C71x
    <td> Open
    <td> Fix tracked in SITSW-7847 for 12.01.00; initialization sequence not yet merged
</tr>
<tr>
    <td> i2097
    <td> DSS: Disabling a Layer Connected to Overlay May Result in Synclost During the Next Frame
    <td> DSS
    <td> N/A
    <td> DSS is not supported in AM62Ax MCU+SDK
</tr>
<tr>
    <td> i2120
    <td> C71x: SE Hangs on Non-Parity Error Detection in Transposed Streams with LEZR
    <td> C71x
    <td> N/A
    <td> SDK does not use stream templates with both LEZR and transposed mode enabled
</tr>
<tr>
    <td> i2137
    <td> PSIL: Clock stop operation can result in undefined behavior
    <td> PSIL
    <td> Implemented
    <td> SDK UDMA driver provides ChDisable/ChEnable APIs for proper channel teardown before clock stop
</tr>
<tr>
    <td> i2160
    <td> DDR: Valid VRef Range Must be Defined During LPDDR4 Command Bus Training
    <td> DDR
    <td> Implemented
    <td> SDK ships pre-generated DDR register init file with correct CALVL_VREF values from TI DDR Configuration Tool
</tr>
<tr>
    <td> i2190
    <td> CSI: CSI_RX_IF may enter unknown state following an incomplete frame
    <td> CSI_RX
    <td> Open
    <td> CSI_RX driver does not reset CSI_RX_IF module on CRC/incomplete frame error as required by the workaround
</tr>
<tr>
    <td> i2196
    <td> IA: Potential deadlock scenarios in IA
    <td> Interrupt Aggregator
    <td> N/A
    <td> SDK does not use IA multicast block functionality; not applicable
</tr>
<tr>
    <td> i2199
    <td> C71x: SE returning incorrect data when non-aligned transposed stream crosses AM1 circular buffer boundary
    <td> C71x
    <td> N/A
    <td> SDK does not use non-aligned transposed streams that cross AM1 circular buffer boundary
</tr>
<tr>
    <td> i2208
    <td> CPSW: ALE IET Express Packet Drops
    <td> CPSW
    <td> Implemented
    <td> TSN stack sets minimum IET fragment size to 128 bytes via ENET_MACPORT_IOCTL_SET_PREEMPT_MIN_FRAG_SIZE
</tr>
<tr>
    <td> i2253
    <td> PRG: CTRL_MMR STAT registers are unreliable indicators of POK threshold failure
    <td> PRG
    <td> Implemented
    <td> POK driver clears ESM flags on initialization as per workaround
</tr>
<tr>
    <td> i2278
    <td> MCAN: Message Transmit order not guaranteed from dedicated Tx Buffers configured with same Message ID
    <td> MCAN
    <td> Application Related
    <td> Customer must use Tx FIFO instead of dedicated Tx Buffers with same Message ID
</tr>
<tr>
    <td> i2279
    <td> MCAN: Specification Update for dedicated Tx Buffers and Tx Queues configured with same Message ID
    <td> MCAN
    <td> N/A
    <td> Documentation erratum only; no code change required
</tr>
<tr>
    <td> i2312
    <td> MMCSD: HS200 and SDR104 Command Timeout Window Too Small
    <td> MMCSD
    <td> N/A
    <td> No SDK command requires a timeout longer than 700ms; not applicable
</tr>
<tr>
    <td> i2373
    <td> VPU: VPU's interrupt is not routed to A53
    <td> VPU
    <td> N/A
    <td> VPU is not supported in AM62Ax MCU+SDK
</tr>
<tr>
    <td> i2376
    <td> C71x: SE/SA/HWAOPEN receives corrupted template following two back to back VPUT/MVC instructions
    <td> C71x
    <td> Implemented
    <td> Workaround is automatically included by the TI C7504 compiler
</tr>
<tr>
    <td> i2366
    <td> Boot: ROM does not comprehend specific JEDEC SFDP features for 8D-8D-8D operation
    <td> Boot
    <td> N/A
    <td> Flash selection constraint; review SFDP table to avoid incompatible 8D-8D-8D flash devices
</tr>
<tr>
    <td> i2371
    <td> Boot: ROM code may hang in UART boot mode during data transfer
    <td> Boot
    <td> N/A
    <td> No SDK workaround; ROM issue. Use an alternate boot interface
</tr>
<tr>
    <td> i2399
    <td> C71x: CPU NLC Module Not Clearing State on Interrupt
    <td> C71x
    <td> Implemented
    <td> NLCINIT issued in ISRs as part of context saving; fix implemented in SDK 11.2.1 and later
</tr>
<tr>
    <td> i2401
    <td> CPSW: Host Timestamps Cause CPSW Port to Lock up
    <td> CPSW
    <td> Open
    <td> SDK enables CPTS host Rx timestamps by default (hostRxTsEn=true); workaround requires disabling host timestamps
</tr>
<tr>
    <td> i2407
    <td> RESET: MCU_RESETSTATz unreliable when MCU_RESETz is asserted low
    <td> RESET
    <td> N/A
    <td> Board design constraint; use Main Domain RESETSTATz instead of MCU_RESETSTATz
</tr>
<tr>
    <td> i2413
    <td> Boot: HS-FS ROM boots corrupted ROM boot image
    <td> Boot
    <td> Implemented
    <td> Workaround supported via app image signing with RSA degenerate key
</tr>
<tr>
    <td> i2414
    <td> Boot: Ethernet PHY Scan and Bring-Up Flow doesn't work with PHYs that don't support Auto Negotiation
    <td> Boot
    <td> N/A
    <td> No workaround; PHY must support auto-negotiation for Ethernet ROM boot
</tr>
<tr>
    <td> i2419
    <td> Boot: When disabling deskew calibration, ROM does not check if deskew calibration was enabled
    <td> Boot
    <td> N/A
    <td> No workaround needed; no functional issue as ROM clears config bit regardless
</tr>
<tr>
    <td> i2420
    <td> Boot: XSPI Boot time is not consistent in SFDP mode
    <td> Boot
    <td> N/A
    <td> No workaround; ROM race condition during SFDP DDR boot, no functional fix
</tr>
<tr>
    <td> i2421
    <td> Boot: fatTiny GPT handling causes data abort
    <td> Boot
    <td> N/A
    <td> User must use MBR partition table with FAT filesystem; GPT is not supported by ROM
</tr>
<tr>
    <td> i2422
    <td> Boot: ROM timeout for MMCSD filesystem boot too long
    <td> Boot
    <td> N/A
    <td> User must boot from alternate mode if eMMC filesystem boot timeout is unacceptable
</tr>
<tr>
    <td> i2423
    <td> Boot: HS-FS ROM applies debug access restrictions to all address space covered by the efuse controller firewall
    <td> Boot
    <td> Application Related
    <td> Application must request TIFS SW to open the firewall region before accessing address space on HS-FS devices
</tr>
<tr>
    <td> i2435
    <td> Boot: ROM timeout for eMMC boot too long
    <td> Boot
    <td> Application Related
    <td> Application must use an alternate boot mode to initially program eMMC
</tr>
<tr>
    <td> i2482
    <td> Boot: ROM does not provide enough clocks during SD card initialization
    <td> Boot
    <td> N/A
    <td> No workaround available; ROM issue with no functional impact observed in practice
</tr>
<tr>
    <td> i2464
    <td> Boot: ROM is unable to boot from SD cards with incorrect formatting
    <td> Boot
    <td> N/A
    <td> User must add -a argument to mkfs.vfat when creating SD card on Ubuntu 22.04
</tr>
<tr>
    <td> i2487
    <td> LPM: Low power modes may inadvertently corrupt DDR contents
    <td> LPM
    <td> Implemented
    <td> Workaround implemented in SDK 11.1 and later; ensures DDR retention latch is in correct state
</tr>
<tr>
    <td> i2493
    <td> MMCSD: HS200 Write Failures
    <td> MMCSD
    <td> Open
    <td> SDK has retry logic for MMCSD failures but does not implement the specific 5us inter-block delay workaround
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
SBL Linker   |  \ref SBL_LINKER_11_3_MIGRATION  &zwj;      |   <= 11.02.00  | >= 11.03.00
VTM (SDL)    |  SDL_VTM_getTemp API now takes int32_t pointer instead of uint32_t   |   <= 11.02.00  | >= 11.03.00

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

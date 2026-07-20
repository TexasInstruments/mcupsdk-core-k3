# Release Notes 12.01.00 {#RELEASE_NOTES_12_01_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.

\attention MCU+SDK on A53 is provided as is for customers as a reference to implement/validate on their own SW Stack & OS. TI will not support these features on the E2E forum as these are not part of the MCU+SDK product. If these features need to be productized, TI can recommend third parties who can help.

## Device and Validation Information


SOC    | Supported CPUs  | EVM                                              | Host PC
-------|-----------------|--------------------------------------------------|-----------------------------------
AM62x  | M4F, R5F, A53   | SK-AM62 (referred as am62x-sk in code), SK-AM62-LP (referred as am62x-sk-lp in code), SK-AM62-SIP (referred as am62x-sip-sk in code) | Windows 10 64b or Ubuntu 22.04 64b


## Features Added in This Release



Feature                                                                                      | Module
---------------------------------------------------------------------------------------------|-----------------------------------
         |      


## Dependent Tools and Compiler Information

\attention It is recommended to use the TIFS version provided with the release for ensuring compatibility between TIFS and device manager. Using the TIFS from different MCU+SDK release is not recomended and may cause TIFS/ DM functionality to break.

Tools/Components        | Supported CPUs | Version
------------------------|----------------|-----------------------
Code Composer Studio    | M4F, R5F, A53  | 20.3.1
SysConfig               | M4F, R5F, A53  | 1.24.2, build 4234
TI ARM CLANG            | M4F, R5F       | 4.0.5.LTS
GCC AARCH64             | A53            | 9.2-2019.12
FreeRTOS Kernel         | M4F, R5F, A53  | 11.1.0

## SDK Components

### SYSFW / TIFS

<table>
    <tr>
        <td>Version</td>
        <td>12.01.02</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/12_01_02/release_notes/release_notes.html)</td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/12_01_02/1_intro/TISCI.html)</td>
    </tr>
</table>

## Key Features

### OS Kernel

OS              | Supported CPUs  | SysConfig Support
----------------|-----------------|-------------------
FreeRTOS Kernel | M4F, R5F, A53   | NA
FreeRTOS POSIX  | M4F, A53        | NA
No RTOS         | M4F, R5F, A53   | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs  | SysConfig Support | OS support
------------------|-----------------|-------------------|------------------
Address Translate | M4F, R5F        | Yes               | FreeRTOS, NORTOS
Cache             | R5F, A53        | Yes               | FreeRTOS, NORTOS
Clock             | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
CycleCounter      | M4F, R5F, A53   | NA                | FreeRTOS, NORTOS
Debug             | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
Heap              | M4F, R5F, A53   | NA                | FreeRTOS, NORTOS
Hwi               | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
MPU               | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS
Semaphore         | M4F, R5F, A53   | NA                | FreeRTOS, NORTOS
Task              | M4F, R5F, A53   | NA                | FreeRTOS
Timer             | M4F, R5F, A53   | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | R5F            | Yes               | Yes         |   Yes       | NORTOS
OSPI NAND | R5F            | Yes               | Yes         |   Yes       | NORTOS
EMMC      | R5F            | Yes               | NA          |   NA        | NORTOS
UART      | R5F            | Yes               | NA          |   No        | NORTOS

### Networking

Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested                                                                                                                                                                    | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------
TSN                         | A53            | NO                | FreeRTOS    | gPTP IEEE 802.1 AS-2020 compliant gPTP stack, End Nodes and Bridge mode support, YANG data model configuration  | Multi-Clock Domain
LwIP                        | A53            | YES               | FreeRTOS    | TCP/UDP IP networking stack with and without checksum offload enabled, TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs and raw APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping, LwIP bridge, shared memory driver  | Other LwIP features
Ethernet driver (ENET)      | A53            | YES               | FreeRTOS    | Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW, Strapped PHY (Early Ethernet), cut through switch on CPSW  | RMII mode

### SOC Device Drivers

For SOC device driver support information per CPU, refer to \ref BUILDSHEET.

### Board Device Drivers

Peripheral    | Supported CPUs | SysConfig Support
--------------|----------------|-------------------
EEPROM        | A53            | Yes
Ethernet PHY  | A53            | Yes
Flash         | R5F, A53       | Yes
LED           | M4F, R5F, A53  | Yes

### Software Diagnostic Library (SDL)

SDL Module   | Supported CPUs | SysConfig Support
-------------|----------------|-------------------
ESM          | M4F, R5F       | No
MCRC         | M4F, R5F       | No
RTI          | M4F, R5F       | No
DCC          | M4F, R5F       | No
VTM          | M4F, R5F       | No
STOG         | M4F, R5F       | No
PBIST        | M4F, R5F       | No
MTOG         | M4F            | No
POK          | M4F, R5F       | No
ECC          | M4F, R5F       | No
LBIST        | M4F            | No
ROM Checksum | R5F            | No

## Fixed Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
</tr>
<tr>
    <td>
    <td>
    <td>
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
    <td>
    <td>
    <td>
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
    <td> i2320
    <td> BCDMA and PKTDMA: Descriptors and TRs required to be returned unfragmented
    <td> DMA
    <td> N/A
    <td> Hardware constraint; no software workaround. Descriptors must not be placed in R5 TCM
</tr>
<tr>
    <td> i2134
    <td> USB: 2.0 Compliance Receive Sensitivity Test Limitation
    <td> USB
    <td> N/A
    <td> USB is not supported in AM62X MCU+SDK
</tr>
<tr>
    <td> i2409
    <td> USB: USB2 PHY locks up due to short suspend
    <td> USB
    <td> N/A
    <td> USB is not supported in AM62X MCU+SDK
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
    <td> i2097
    <td> DSS: Disabling a Layer Connected to Overlay May Result in Synclost During the Next Frame
    <td> DSS
    <td> Open
    <td> DSS driver does not implement the layer position workaround before disabling a layer
</tr>
<tr>
    <td> i2103
    <td> Internal Diagnostics Modules: Incorrect Reporting of ECC_GRP, ECC_BIT and ECC_TYPE Information for Functional Safety Errors
    <td> Internal Diagnostic Modules
    <td> N/A
    <td> No software workaround available; detection and interrupt signaling are unaffected
</tr>
<tr>
    <td> i2160
    <td> DDR: Valid VRef Range Must be Defined During LPDDR4 Command Bus Training
    <td> DDR
    <td> Implemented
    <td> SDK ships pre-generated DDR register init file with correct CALVL_VREF values from TI DDR Configuration Tool
</tr>
<tr>
    <td> i2196
    <td> IA: Potential deadlock scenarios in IA
    <td> Interrupt Aggregator
    <td> N/A
    <td> SDK does not use IA multicast block functionality; not applicable
</tr>
<tr>
    <td> i2208
    <td> CPSW: ALE IET Express Packet Drops
    <td> CPSW
    <td> Implemented
    <td> TSN stack sets minimum IET fragment size to 128 bytes via ENET_MACPORT_IOCTL_SET_PREEMPT_MIN_FRAG_SIZE
</tr>
<tr>
    <td> i2232
    <td> DDR: Controller postpones more than allowed refreshes after frequency change
    <td> DDR
    <td> N/A
    <td> SDK does not perform dynamic DDR frequency switching; errata condition cannot be triggered
</tr>
<tr>
    <td> i2244
    <td> DDR: Valid stop value must be defined for write DQ VREF training
    <td> DDR
    <td> Implemented
    <td> SDK DDR init file sets valid WDQLVL_VREF_INITIAL values (STOP=50, START=0, STEPSIZE=1) satisfying the stop value formula
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
    <td> i2283
    <td> Restrictions on how CP Tracer Debug Probes can be used
    <td> DEBUG
    <td> N/A
    <td> No software workaround available; limitation applies to CP Tracer probes only
</tr>
<tr>
    <td> i2307
    <td> Boot: ROM does not properly select OSPI clocking modes based on BOOTMODE
    <td> Boot
    <td> N/A
    <td> ROM always selects internal loopback; avoid external board loopback OSPI topology
</tr>
<tr>
    <td> i2312
    <td> MMCSD: HS200 and SDR104 Command Timeout Window Too Small
    <td> MMCSD
    <td> N/A
    <td> No SDK command requires a timeout longer than 700ms; not applicable
</tr>
<tr>
    <td> i2327
    <td> RTC: Hardware wakeup event limitation
    <td> RTC
    <td> N/A
    <td> No software workaround available; only RTC hardware wakeup event is affected
</tr>
<tr>
    <td> i2328
    <td> Boot: USB MSC boots intermittently
    <td> Boot
    <td> N/A
    <td> No workaround available; ROM USB MSC protocol timing violation
</tr>
<tr>
    <td> i2329
    <td> MDIO: MDIO interface corruption (CPSW and PRU-ICSS)
    <td> MDIO
    <td> Open
    <td> MDIO manual mode is supported in SDK but not enabled by default; user must explicitly configure via SysConfig
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
    <td> i2410
    <td> Boot: ROM may fail to boot due to i2409
    <td> Boot
    <td> N/A
    <td> USB is not supported in AM62X MCU+SDK; ROM boot issue only
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
    <td> i2415
    <td> Boot: UART Backup Boot Authentication Failure w/ xSPI Primary Boot Mode
    <td> Boot
    <td> N/A
    <td> HS-SE only; ensure redundant offset contains a complete boot certificate, not just a TIFS/SYSFW certificate
</tr>
<tr>
    <td> i2416
    <td> Boot: FAT boot partition with ESP flag doesn't boot
    <td> Boot
    <td> N/A
    <td> User must ensure boot partition type is FAT and not ESP (0xEF) when creating SD card
</tr>
<tr>
    <td> i2417
    <td> Boot: GPMC NAND configured to slower clock speed
    <td> Boot
    <td> N/A
    <td> No workaround; ROM uses conservative timing values, no functional impact observed
</tr>
<tr>
    <td> i2418
    <td> Boot: Secure ROM Panic due to Certificate Info not present
    <td> Boot
    <td> N/A
    <td> User must ensure Extended or Legacy Certificate info is always present in the boot image
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
    <td> User must boot from alternate mode to program eMMC; occurs only when eMMC is empty or erased
</tr>
<tr>
    <td> i2423
    <td> Boot: HS-FS ROM applies debug access restrictions to all address space covered by the efuse controller firewall
    <td> Boot
    <td> Application Related
    <td> Application must request TIFS SW to open the firewall region before accessing address space on HS-FS devices
</tr>
<tr>
    <td> i2431
    <td> BCDMA: RX Channel can lockup in certain scenarios
    <td> BCDMA
    <td> Implemented
    <td> SDK drivers set TR EOP flag (TR_FLAGS_EOP=1) and PDMA Z parameter (fifoCnt) to non-zero per workaround
</tr>
<tr>
    <td> i2435
    <td> Boot: ROM timeout for eMMC boot too long
    <td> Boot
    <td> Application Related
    <td> Application must use an alternate boot mode to initially program eMMC
</tr>
<tr>
    <td> i2436
    <td> BCDMA: BCDMA RX_IGNORE_LONG setting in RX CHAN CFG register doesn't work
    <td> BCDMA
    <td> N/A
    <td> RX_IGNORE_LONG is not used in SDK (ignoreLongPkts defaults to FALSE); errata condition cannot be triggered
</tr>
<tr>
    <td> i2457
    <td> Boot: Missing data in UART transfer causes boot failures
    <td> Boot
    <td> Open
    <td> Requires building special xmodem tool (sx) with 50ms inter-character delay
</tr>
<tr>
    <td> i2464
    <td> Boot: ROM is unable to boot from SD cards with incorrect formatting
    <td> Boot
    <td> N/A
    <td> User must add -a argument to mkfs.vfat when creating SD card on Ubuntu 22.04
</tr>
<tr>
    <td> i2482
    <td> Boot: ROM does not provide enough clocks during SD card initialization
    <td> Boot
    <td> N/A
    <td> No workaround; ROM issue with no functional impact observed in practice
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
<tr>
    <td> 3
    <td> LPM is not supported with SBL boot flow. It is supported only with SPL boot flow.
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
NETWORKING   |  \ref enet_mcupsdk_update       &zwj;       |   <= 11.01.00  | >= 11.02.00
OSPI         |  \ref OSPI_MIGRATION_GUIDE       &zwj;      |   <= 11.01.00  | >= 11.02.00
Watchdog     |  \ref WATCHDOG_12_0_MIGRATION    &zwj;      |   <= 11.02.00  | >= 12.00.00
SCI Server   |  \ref SCISERVER_12_0_MIGRATION   &zwj;      |   <= 11.02.00  | >= 12.00.00
SBL Linker   |  \ref SBL_LINKER_12_0_MIGRATION   &zwj;     |   <= 11.02.00  | >= 12.00.00
VTM (SDL)    |  SDL_VTM_getTemp API now takes int32_t pointer instead of uint32_t   |   <= 12.00.00  | >= 12.01.00
DPL          |  TimerP_start, TimerP_stop, TimerP_clearOverflowInt return type changed from void to int32_t   |   <= 12.00.00  | >= 12.01.00
DPL          |  AddrTranslateP_setRegion promoted to public API; AddrTranslateP_readbackVerify added as new API   |   <= 12.00.00  | >= 12.01.00
UART         |  `UART_enableLoopbackMode` and `UART_disableLoopbackMode` return type changed from `void` to `int32_t`. Check the return value; `SystemP_FAILURE` is returned if the base address is invalid.  |   <= 12.00.00  | >= 12.01.00


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

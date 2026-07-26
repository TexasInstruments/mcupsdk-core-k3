# Release Notes 12.01.00

:::{attention}
Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.
:::

:::{note}
The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination.
Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment.
:::

## Device and Validation Information

SOC    | Supported CPUs              | EVM                                                     | Host PC
-------|-----------------------------|---------------------------------------------------------|-----------------------------------
AM275x | R5F, C75                    | {{ VAR_BOARD_NAME }} (referred to as am275x-evm in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release


Feature                                                                                      | Module
---------------------------------------------------------------------------------------------|-----------------------------------
         |


## Dependent Tools and Compiler Information

Tools/ Component        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | R5F, C75                 | 20.3.1
SysConfig               | R5F, C75                 | 1.24.2, build 4234
TI ARM CLANG            | R5F                      | 4.0.5.LTS
C7000-CGT               | C75                      | 5.0.0.LTS
FreeRTOS Kernel         | R5F, C75                 | 11.1.0

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
C++ support                                                         | NA

### Eval Features

:::{attention}
Features listed below are early versions and gone through limited testing.
:::

Feature                                                             | Module
--------------------------------------------------------------------|--------------------------
AUDIOLIB TISP                                                       | All modules in AUDIOLIB, TISP

## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | R5F, C75                  | NA
FreeRTOS POSIX  | R5F, C75                  | NA
No RTOS         | R5F                       | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs | SysConfig Support | OS support
------------------|----------------|-------------------|------------------
Address Translate | R5F            | Yes               | FreeRTOS, NORTOS
Cache             | R5F, C75       | Yes               | FreeRTOS, NORTOS
Clock             | R5F, C75       | Yes               | FreeRTOS, NORTOS
CycleCounter      | R5F, C75       | NA                | FreeRTOS, NORTOS
Debug             | R5F, C75       | Yes               | FreeRTOS, NORTOS
Heap              | R5F, C75       | NA                | FreeRTOS, NORTOS
Hwi               | R5F, C75       | Yes               | FreeRTOS, NORTOS
MPU               | R5F, C75       | Yes               | FreeRTOS, NORTOS
Semaphore         | R5F, C75       | NA                | FreeRTOS, NORTOS
Task              | R5F, C75       | NA                | FreeRTOS
Timer             | R5F            | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | WKUP-R5F       | Yes               | Yes         |   Yes       | NORTOS
EMMC      | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS
UART      | WKUP-R5F       | Yes               | NA          |   No        | NORTOS
SD        | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS


### Networking
Module                      | Supported CPUs | SysConfig Support | OS Support  | Key features tested  | Key features not tested
----------------------------|----------------|-------------------|-------------|----------------------|-------------------------
TSN                         | R5F       | NO                | FreeRTOS    | gPTP IEEE 802.1 AS-2020 compliant gPTP stack, End Nodes and Bridge mode support, YANG data model configuration, IEEE 1722 compliant AVTP Stack | Multi-Clock Domain
LwIP                        | R5F       | YES               | FreeRTOS    | TCP/UDP IP networking stack with and without checksum offload enabled, TCP/UDP IP networking stack with server and client functionality, basic Socket APIs, netconn APIs and raw APIs, DHCP, ping, TCP iperf, scatter-gather, DSCP priority mapping, LwIP bridge, shared memory driver  | Other LwIP features
Ethernet driver (ENET)      | R5F       | YES               | FreeRTOS    | Ethernet as port using CPSW,  MAC loopback and PHY loopback, Layer 2 MAC, Packet Timestamping, CPSW Switch, Policer and Classifier, MDIO Manual Mode, CBS (IEEE 802.1Qav) on CPSW, IET (IEEE 802.1Qbu) on CPSW, cut through switch on CPSW  | RMII mode

### SOC Device Drivers

For SOC device driver support information per CPU, refer to BUILDSHEET.

### Board Device Drivers

Peripheral    | Supported CPUs | SysConfig Support
--------------|----------------|-------------------
EEPROM        | R5F            | Yes
Ethernet PHY  | R5F            | Yes
Flash         | R5F, WKUP-R5F, C75  | Yes
HyperRAM      | R5F, WKUP-R5F, C75  | Yes
LED           | R5F, C75       | Yes
PMIC          | R5F            | Yes

### SDL

SDL Module       | Supported CPUs | SysConfig Support
-----------------|----------------|-------------------
MCRC             |  R5F           | No
ESM              |  R5F           | No
VTM              |  R5F           | No
DCC              |  R5F           | No
ECC              |  R5F           | No
RTI              |  R5F           | No
POK              |  R5F           | No
PBIST            |  R5F           | No
LBIST            |  R5F           | No
ROM_CHECKSUM     |  R5F           | No


:::{note}
This is BQ release for SDL. FSQ release will be provided in next release.
:::

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
    <td> i2377
    <td> RAT input signals rbytecnt and wbytecnt calculation is wrong
    <td> RAT
    <td> Implemented
    <td> SysConfig enforces minimum RAT region size of 32 bytes; region boundaries smaller than 32 bytes are not configurable
</tr>
<tr>
    <td> i2401
    <td> CPSW: Host Timestamps Cause CPSW Port to Lock up
    <td> CPSW
    <td> Open
    <td> SDK enables CPTS host Rx timestamps by default (hostRxTsEn=true); workaround requires disabling host timestamps
</tr>
<tr>
    <td> i2427
    <td> Safety: RAM SEC can cause Spurious RAM writes resulting in L2 and MBOX memory corruption
    <td> C71x
    <td> N/A
    <td> C75 L2SRAM is configured as write-back cacheable (MAIR7) in example SysConfig files; CPU performs only full line writes making the partial write condition not applicable
</tr>
<tr>
    <td> i2435
    <td> Boot: ROM timeout for eMMC boot too long
    <td> Boot
    <td> Application Related
    <td> Application must use an alternate boot mode to initially program eMMC
</tr>
<tr>
    <td> i2438
    <td> CPSW: Host to Ethernet Checksum Generation with VLAN ADD/Remove
    <td> CPSW
    <td> Open
    <td> SDK enables TX checksum offload by default; VLAN tag add/remove on egress must not be used simultaneously with checksum generation
</tr>
<tr>
    <td> i2449
    <td> Pulsars do not have RAT MMR Parity - Mismatch with Diagnostic RAT5
    <td> Pulsar
    <td> Implemented
    <td> Software readback of RAT MMR values implemented in SDK 12.01.00 (SITSW-11362)
</tr>
<tr>
    <td> i2455
    <td> PWM: The eint interrupt from all three PWM are not routed to main Pulsar
    <td> PWM
    <td> Open
    <td> Workaround requires routing PWM eint via DM R5 to Main Pulsar; not feasible directly from Main Pulsar Core
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
</table>
</table>

## Upgrade and Compatibility Information
This section lists changes which could affect user applications developed using older SDK versions.
Read this carefully to see if you need to do any changes in your existing application when migrating to this SDK version relative to
previous SDK version. Also refer to older SDK version release notes to see changes in
earlier SDKs.


The below table captures the list of migration document sections when migrating from one version to another.
The migration for a partcluar module will be applicable, if you are migrating from older version listed to
newer version listed on the table below.

<table>
<tr>
    <th> Module
    <th> Migration guide
    <th> Older version
    <th> Newer version
</tr>
<tr>
    <td> Bootloader
    <td> BOOTLOADER_MIGRATION_GUIDELINE
    <td> <= 10.01.00
    <td> >= 11.00.00
</tr>
<tr>
    <td> NETWORKING
    <td> enet_mcupsdk_update
    <td> <= 11.01.00
    <td> >= 11.02.00
</tr>
<tr>
    <td> OSPI
    <td> OSPI_MIGRATION_GUIDE
    <td> <= 11.01.00
    <td> >= 11.02.00
</tr>
<tr>
    <td> Watchdog
    <td> WATCHDOG_12_0_MIGRATION
    <td> <= 11.02.00
    <td> >= 12.00.00
</tr>
<tr>
    <td> SCI Server
    <td> SCISERVER_12_0_MIGRATION
    <td> <= 11.02.00
    <td> >= 12.00.00
</tr>
<tr>
    <td> SBL Linker
    <td> SBL_LINKER_12_0_MIGRATION
    <td> <= 11.02.00
    <td> >= 12.00.00
</tr>
<tr>
    <td> VTM (SDL)
    <td> SDL_VTM_getTemp API now takes int32_t pointer instead of uint32_t
    <td> <= 12.00.00
    <td> >= 12.01.00
</tr>
<tr>
    <td> DPL
    <td> TimerP_start, TimerP_stop, TimerP_clearOverflowInt return type changed from void to int32_t
    <td> <= 12.00.00
    <td> >= 12.01.00
</tr>
<tr>
    <td> DPL
    <td> AddrTranslateP_setRegion promoted to public API; AddrTranslateP_readbackVerify added as new API
    <td> <= 12.00.00
    <td> >= 12.01.00
</tr>
<tr>
    <td> UART
    <td> `UART_enableLoopbackMode` and `UART_disableLoopbackMode` return type changed from `void` to `int32_t`. Check the return value; `SystemP_FAILURE` is returned if the base address is invalid.
    <td> <= 12.00.00
    <td> >= 12.01.00
</tr>
</table>

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

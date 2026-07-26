# Release Notes 10.01.00

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

Feature                                                                                  | Module
-----------------------------------------------------------------------------------------|-----------------------------------
R5F: I2C, UDMA, MCASP, UART, OSPI, McSPI, GPIO, SCI Client, DM Timer, IPC                | Drivers
C7X: I2C, UDMA, MCASP, UART, GPIO, SCI Client, DM Timer, IPC                             | Drivers
SBL: OSPI NOR, SD, UART, EMMC                                                            | Bootloader

## Dependent Tools and Compiler Information

Tools/ Component        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | R5F, C75                 | 12.8.1
SysConfig               | R5F, C75                 | 1.22.0, build 3893
TI ARM CLANG            | R5F                      | 3.2.0.LTS
C7000-CGT               | C75                      | 4.1.0.LTS
FreeRTOS Kernel         | R5F, C75                 | 11.1.0
TIFS                    | NA                       | v10.01.09

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

Peripheral | Supported CPUs  | SysConfig Support
-----------|-----------------|-------------------
GPIO       | R5F, C7X        | YES
I2C        | R5F, C7X        | YES
IPC        | R5F, C7X        | YES
MCAN       | R5F             | YES
MCASP      | R5F, C7X        | YES
MCSPI      | R5F             | YES
MMCSD      | R5F             | YES
Pinmux     | R5F, C7X        | YES
SOC        | R5F, C7X        | YES
SCI Client | R5F, C7X        | YES
UART       | R5F, C7X        | YES
UDMA       | R5F, C7X        | YES


### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
EEPROM     | R5F            | Yes
Flash      | WKUP-R5F       | Yes
LED        | R5F            | Yes

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
    <th> Applicable Releases
</tr>
<tr>
    <td> NA
    <td> NA
    <td> NA
    <td> NA
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
    <td> PROC_SDL-8786
    <td> PBIST MAIN IP Controller (PBIST0) fails if tested and hence has been disabled
    <td> SDL
    <td> 10.01.00
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8788
    <td> Secondary core testing of MAIN_PULSAR_0 and MAIN_PULSAR_1 Controllers (PBIST1, PBIST2) fails if tested and hence is disabled
    <td> SDL
    <td> 10.01.00
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8790
    <td> ECC is not supported for some instances. These are
    SDL_IDOM0_PULSAR_PLL_ECC_AGGR10
    SDL_IDOM0_PULSAR_PLL_ECC_AGGR8
    SDL_IDOM0_MAIN_PLL_ECC_AGGR6_IDOM0_MAIN_PLL_ECC_AGGR
    SDL_IDOM0_MAIN_PLL_ECC_AGGR4_IDOM0_MAIN_PLL_ECC_AGGR
    SDL_IDOM1_MAIN_PLL_ECC_AGGR5_IDOM1_MAIN_PLL_ECC_AGGR
    SDL_IDOM1_MAIN_PLL_ECC_AGGR7_IDOM1_MAIN_PLL_ECC_AGGR
    SDL_IDOM1_PULSAR_PLL_ECC_AGGR9
    SDL_IDOM1_PULSAR_PLL_ECC_AGGR11
    SDL_FSS1_FSS_OSPI1_OSPI_WRAP_ECC_AGGR
    SDL_WKUP_ECC_AGGR0_AM275_DM_DM_ECC_AGGR
    SDL_WKUP_PSRAM2KX32E0_PSRAM2KX32E_ECC_AGGR
    <td> SDL
    <td> 10.01.00
    <td> None
</tr>
<tr>
    <td> PROC_SDL-8861
    <td> ECC is not supported for some instances due to firewall. These are
    SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR
    SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR
    SDL_SMS0_SMS_HSM_ECC
    SDL_SMS0_SMS_TIFS_ECC
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
    <td> The **ROM** startup model for runtime initializations in TI ARM CLANG is not supported/tested in the SDK
    <td> NA
</tr>
</table>
</table>

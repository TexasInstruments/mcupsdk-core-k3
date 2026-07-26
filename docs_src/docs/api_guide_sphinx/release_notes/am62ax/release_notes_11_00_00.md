# Release Notes 11.00.00

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
AM62Ax | MCU R5F, DM R5F, C75   | {{ VAR_BOARD_NAME }} EVM (referred to as am62ax-sk in code) | Windows 10 64b or Ubuntu 22.04 64b
:::

## Features Added in This Release

Feature                                                                                        | Module
-----------------------------------------------------------------------------------------------|-----------------------------------
Safety qualification for IPC driver                                                            | IPC
Exmaple for Key Revision update                                                                | OTP
RTC driver on R5F                                                                              | RTC
LPM example for MCU only with Timer and MCAN as wakeup sources                                 | LPM
ECC example for R5F cache                                                                      | SDL
Optimized boottime for eMMC, SD boot by enabling DMA for DDR to DDR copy                       | Bootloader

### Unsupported Features

:::{attention}
TI would not support these feature on public e2e.
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
Code Composer Studio    | MCU-R5F, C75             | 20.1.0
SysConfig               | MCU-R5F, DM-R5F, C75     | 1.23.0, build 4000
TI ARM CLANG            | MCU-R5F, DM-R5F          | 4.0.1.LTS
GCC AARCH64             | A53                      | 9.2-2019.12
C7000-CGT               | C75                      | 4.1.0.LTS
FreeRTOS Kernel         | MCU-R5F, DM-R5F, C75     | 11.1.0

## SDK Components

### SYSFW / TIFS

<table>
    <tr>
        <td>Version</td>
        <td>11.00.07</td>
    </tr>
    <tr>
        <td>Release Notes</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_00_07/release_notes/release_notes.html)</td>
    </tr>
    <tr>
        <td>User Guide</td>
        <td>[LINK](https://software-dl.ti.com/tisci/esd/11_00_07/1_intro/TISCI.html)</td>
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

:::{note}
See the updated MCASP usage guidelines in [MCASP](../../components/drivers/mcasp_v1.md) for changes in
MCASP driver
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

:::{note}
Refer [Accessing main and wakeup domain peripherals from MCU domain](../../developer_guides/main_domain_peripheral_access.md) for accessing main/wakeup peripherals from MCU Domain.
:::

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
    <th> Applicable Releases
</tr>
<tr>
    <td> [ EXT_SITMPUSW-52](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-52)
    <td> UART baud rate and operational mode condition misalignment
    <td> UART
    <td> 08.06.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-57](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-57)
    <td> Data Abort at MCSPI_udmaIsrTx when using MCSPI DMA
    <td> MCSPI
    <td> 08.06.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-58](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-58)
    <td> MCU PLUS SDK: ipc_rpmsg_echo [DM Firmware] Timeout not working as expected, crashes FW
    <td> DM, IPC
    <td> 08.06.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-59](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-59)
    <td> VTM giving same value for every call
    <td> VTM
    <td> 10.01.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-89](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-89)
    <td> I2C Error Handler transition from status to i2cTransaction.status
    <td> I2C
    <td> 08.03.00
</tr>
<tr>
    <td> [ EXT_SITMPUSW-90](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-90)
    <td> MMCSD_write & MMCSD_read function fails for the numBlocks greater than 0xFFFF
    <td> MCSPI
    <td> 08.04.00
</tr>
<tr>
    <td> [ EXT_EP-12318](https://sir.ext.ti.com/jira/browse/EXT_EP-12318)
    <td> SDL_ECC_aggrTransBaseAddressTable declared without extern keyword
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> [ EXT_EP-12321](https://sir.ext.ti.com/jira/browse/EXT_EP-12321)
    <td> MCRC: System_deinit failure in MCRC Semi CPU mode and MCRC auto mode in AM275x and AM62a
    <td> SDL
    <td> 11.00.00
</tr>
<tr>
    <td> [ EXT_EP-12324](https://sir.ext.ti.com/jira/browse/EXT_EP-12324)
    <td> gSDL_pvt_poly_golden has to be used in SDL_vtmPrepLookupTable API instead of gSDL_pvt_poly
    <td> SDL
    <td> 11.00.00
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
    <td> [ EXT_SITMPUSW-28](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-28)
    <td> Outstanding mailbox messages prevent suspend
    <td> IPC
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-73](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-73)
    <td> OSPI_readDirect and OSPI_isPhyEnable do not correctly check if the PHY is enabled
    <td> OSPI
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-77](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-77)
    <td> Modify Read capture delay logic for Tap Mode
    <td> OSPI
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-78](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-78)
    <td> MMCSD Sysconfig provides options to configure PHY type
    <td> MMCSD
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_SITMPUSW-85](https://sir.ext.ti.com/jira/browse/EXT_SITMPUSW-85)
    <td> Flash_eraseSector and Flash_norOspiEraseSector does not erases the mentioned sector.
    <td> Flash
    <td> 08.03.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12281](https://sir.ext.ti.com/jira/browse/EXT_EP-12281)
    <td> AM62A: ECC: ECC is failing for 2 Bit VTM selftest - ECC Unit test fails at the API call ECC_Test_runECC2BitVTM0selfTest()
    <td> SDL
    <td> 10.01.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12276](https://sir.ext.ti.com/jira/browse/EXT_EP-12276)
    <td> ECC: Firewall related aggregators failures - ECC Aggregators SDL_SMS0_SMS_TIFS_ECC, SDL_SMS0_SMS_HSM_ECC and SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR fail because of firewall access issues faced by SDL
    <td> SDL
    <td> 10.01.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12280](https://sir.ext.ti.com/jira/browse/EXT_EP-12280)
    <td> Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F - Running MCU LBIST on SBL causes JTAG connection issues to MCU R5F on AM62ax
    <td> SDL
    <td> 09.00.00
    <td> No known workaround
</tr>
<tr>
    <td> [ EXT_EP-12283](https://sir.ext.ti.com/jira/browse/EXT_EP-12283)
    <td> ECC aggregators CPSW0, CSI RX are failing on AM62A and CPSW0 on AM62D.
    <td> SDL
    <td> 09.00.00
    <td> No known workaround
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

## Upgrade and Compatibility Information

:::{attention}
When migrating from oldder version to 11.00.00, see [BOOTLOADER](../../components/drivers/bootloader.md) for more details
:::

This section lists changes which could affect user applications developed using older SDK versions.
Read this carefully to see if you need to do any changes in your existing application when migrating to this SDK version relative to
previous SDK version. Also refer to older SDK version release notes to see changes in
earlier SDKs.

# SBL OSPI Linux {#EXAMPLES_DRIVERS_SBL_OSPI_LINUX_MULTISTAGE}

\note The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.

[TOC]

# Introduction

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on DM R5 and M4 cores.

\cond SOC_AM62X

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and stats running it.

 - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.

The SBL uses 6 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, SPL)**.
- Appimage for **SBL stage1**
- Appimage for **SBL stage2**
- Appimage for **MCU M4**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
\endcond

\cond SOC_AM6A2X

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU R5 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and stats running it.

 - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.

The SBL uses 6 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, SPL)**.
- Appimage for **SBL stage1**
- Appimage for **SBL stage2**
- Appimage for **MCU R5**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
\endcond


# Supported Combinations

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_linux_multistage

# Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Flash the OSPI NOR with the default linux image

\note This needs to be the first step as later the tiboot3.bin at the starting of the bootpartition will be overwritten by `sbl_ospi_nand_linux.tiimage` .

- For booting A53 with linux, OSPI NOR needs to be flashed with the Linux image. Refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/Foundational_Components/U-Boot/UG-QSPI.html, **Processor SDK Linux**} user guide on how to flash OSPI NOR to boot Linux.

## Create Linux Appimage

\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.

\note Change PSDK_LINUX_HS_IMAGE_PATH to the path where A53 spl images (ATF, OPTEE, A53 uboot) is.

\note Instructions to build A53 uboot can be found in the SDK Linux documentation at
        **Foundational Components » U-Boot » User’s Guide » General Information » Build U-Boot**

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, SPL)**
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details

## Create Device Manager (DM) Appimage

- Create a DM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/deviceManagerAppimageGen
- Refer \ref DM_APPIMAGE_GEN_TOOL for more details

## Create HSM Appimage

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details

## Run the example

\cond SOC_AM62X
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for R5, M4 CPUs and Linux Appimage.
\endcond

\cond SOC_AM6A2X
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for DM R5, MCU R5 CPUs and Linux Appimage.
\endcond

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/@VAR_BOARD_NAME_LOWER/{cpu}_{os}/default_sbl_ospi_linux.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/@VAR_BOARD_NAME_LOWER/r5fss0-0_nortos/default_sbl_ospi_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/@VAR_BOARD_NAME_LOWER/r5fss0-0_nortos/default_sbl_ospi_linux.cfg

- Boot the EVM in OSPI NAND boot mode.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

    DMSC Firmware Version 8.4.7--v08.04.07 (Jolly Jellyfi
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 148 KB
    [BOOTLOADER_PROFILE] Cores present    :
    m4f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      28173us
    [BOOTLOADER PROFILE] Drivers_open                     :         93us
    [BOOTLOADER PROFILE] Board_driversOpen                :      23716us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10113us
    [BOOTLOADER PROFILE] App_loadImages                   :      25181us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     137785us

    Image loading done, switching to application ...
    Starting MCU-m4f and 2nd stage bootloader

    DMSC Firmware Version 8.4.7--v08.04.07 (Jolly Jellyfi
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 853 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2698us
    [BOOTLOADER PROFILE] Drivers_open                     :        100us
    [BOOTLOADER PROFILE] Board_driversOpen                :      23604us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10165us
    [BOOTLOADER PROFILE] App_loadImages                   :        215us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      67330us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     461619us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.7(release):v2.7.0-dirty
    NOTICE:  BL31: Built : 16:38:50, Sep  8 2022
    I/TC:
    I/TC: OP-TEE version: 3.17.0-125-g15a746d28 (gcc version 9.2.1 20191025 (GNU Toolchain for the A-profile Architecture 9.2-2019.12 (arm-9.10))) #1 Thu Sep  8 16:42:29 UTC 2022 aarch64
    I/TC: Primary CPU initializing
    I/TC: SYSFW ABI: 3.1 (firmware rev 0x0008 '8.4.7--v08.04.07 (Jolly Jellyfi')
    I/TC: HUK Initialized
    I/TC: Primary CPU switching to normal world boot

    U-Boot SPL 2021.01-gb8840490a1 (Sep 08 2022 - 16:42:45 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0008 '8.4.7--v08.04.07 (Jolly Jellyfi')
    Trying to boot from SPI


    .
    .
    .
    .
    .
    .


    _____                    _____           _         _
    |  _  |___ ___ ___ ___   |  _  |___ ___  |_|___ ___| |_
    |     |  _| .'| . | . |  |   __|  _| . | | | -_|  _|  _|
    |__|__|_| |__,|_  |___|  |__|  |_| |___|_| |___|___|_|
                |___|                    |___|

    Arago Project http://arago-project.org am64xx-evm ttyS2

    Arago 2020.09 am62xx-evm ttyS2

    am62xx-evm login:

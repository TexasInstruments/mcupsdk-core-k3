# SBL OSPI Linux Multistage {#EXAMPLES_DRIVERS_SBL_OSPI_LINUX_MULTISTAGE}

\note The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.

[TOC]

# Introduction

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on DM R5 and M4 cores.

\cond SOC_AM62AX
\note By default, AM62AX-SK ships with OSPI NAND flash. This example is applicable only after modifying it to OSPI NOR flash
\endcond

\cond SOC_AM62X

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and stats running it.

 - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.

The SBL uses 6 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU M4**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
\endcond

\cond SOC_AM62AX

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU R5 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and stats running it.

 - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.

The SBL uses 6 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU R5**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
\endcond

Refer \ref SBL_BOOTING_LINUX_OSPI for more details on the OSPI boot loader.

\cond SOC_AM62AX
In order to boot faster,
- Linux appimage can be packaged with the Linux kernel and DTB in fastboot mode (\ref LINUX_APPIMAGE_GEN_TOOL). Refer to Processor SDK Linux for more information on how to create a buildable Kernel and DTB
- This example reuses the OSPI initialization already performed at SBL stage 1 instead of reprogramming it. This is done by enabling the **Skip OSPI Programming** option in SBL stage 2 sysconfig
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

## Flash the OSPI NOR with u-boot and linux kernel

\note This needs to be the first step as later the tiboot3.bin at the starting of the bootpartition will be overwritten by `sbl_ospi_nand_linux.tiimage` .

- For booting A53 with linux, OSPI NOR needs to be flashed with the Linux image. Refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/Foundational_Components/U-Boot/UG-QSPI.html, **Processor SDK Linux**} user guide on how to flash OSPI NOR to boot Linux.

## Create Linux Appimage

\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.

\note Change PSDK_LINUX_PATH to the path where A53 spl images (ATF, OPTEE, A53 uboot) is.

\note Instructions to build A53 uboot can be found in the SDK Linux documentation at
        **Foundational Components » U-Boot » User’s Guide » General Information » Build U-Boot**

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)** or (ATF, OPTEE, Kernel, DTB) in case of fastboot mode.
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details

## Create HSM Appimage

\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.

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

\note For HS-SE device, use **default_sbl_ospi_linux_hs.cfg** as the cfg file.
\note For HS-FS device, use **default_sbl_ospi_linux_hs_fs.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux.cfg

- Boot the EVM in OSPI NAND boot mode.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

    DMSC Firmware Version 9.0.5--v09.00.05 (Kool Koala)
    DMSC Firmware revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 184 KB
    [BOOTLOADER_PROFILE] Cores present    :
    m4f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :       6411us
    [BOOTLOADER PROFILE] Drivers_open                     :        208us
    [BOOTLOADER PROFILE] Board_driversOpen                :      27571us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9927us
    [BOOTLOADER PROFILE] App_waitForMcuPbist              :          5us
    [BOOTLOADER PROFILE] App_waitForMcuLbist              :       7689us
    [BOOTLOADER PROFILE] App_loadImages                   :       3535us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       6279us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      61628us

    Image loading done, switching to application ...
    Starting MCU-m4f and 2nd stage bootloader

    DMSC Firmware Version 9.0.5--v09.00.05 (Kool Koala)
    DMSC Firmware revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 940 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2825us
    [BOOTLOADER PROFILE] Drivers_open                     :        266us
    [BOOTLOADER PROFILE] Board_driversOpen                :      27055us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9967us
    [BOOTLOADER PROFILE] App_loadImages                   :       1961us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       6557us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :      29163us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      77797us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
    NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

    U-Boot SPL 2023.04-ga3595f1e3e (Jun 15 2023 - 08:14:46 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
    SPL initial stack usage: 1856 bytes
    Trying to boot from SPI
    Authentication passed
    Authentication passed


    U-Boot 2023.04-gd6bccb1b9e (Jun 09 2023 - 06:25:21 +0000)

    SoC:   AM62X SR1.0 HS-FS
    Model: Texas Instruments AM625 SK
    EEPROM not available at 80, trying to read at 81
    Board: AM62-SKEVM rev E3
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

    Arago Project am62xx-evm -

    Arago 2023.04 am62xx-evm -

    am62xx-evm login:

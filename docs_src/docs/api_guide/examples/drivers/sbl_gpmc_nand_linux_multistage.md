# SBL GPMC NAND Linux Multistage {#EXAMPLES_DRIVERS_SBL_GPMC_NAND_LINUX_MULTISTAGE}

\note The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.

[TOC]

# Introduction

\attention Board modification are required for supporting GPMC NAND flash device daughter card. Refer the board user guide of SK-AM62-LP for details on the modifications.

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on DM R5 and M4 cores.
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


# Supported Combinations

\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_gmpc_nand_linux_multistage
\endcond


# Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Create Linux Appimage
\cond SOC_AM62X
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.
\endcond

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details

## Create HSM Appimage

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details

## Run the example

\cond SOC_AM62X
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for R5, M4 CPUs and Linux Appimage.
\note For HS-SE device, use **default_sbl_gpmc_linux_hs.cfg** as the cfg file.
\note For HS-FS device, use **default_sbl_gpmc_linux_hs_fs.cfg** as the cfg file.

\attention The UART uniflash does not have the GPMC flash enabled by default. Enable GPMC by adding another flash instance with 'Flash Topology' as 'Parallel Flash'. It will add GPMC module as well.


- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_gpmc_linux_hs_fs.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_gpmc_linux_hs_fs.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_gpmc_nand_linux_hs_fs.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_gpmc_nand_linux_hs_fs.cfg

\endcond


- Boot the EVM in GMPC NAND boot mode.

\cond SOC_AM62X
\note The above config file will flash till u-boot on the GPMC NAND. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/devices/AM62X/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output
After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

\cond SOC_AM62X

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 133.333 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 181 KB
    [BOOTLOADER_PROFILE] Cores present    :
    m4f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      36631us
    [BOOTLOADER PROFILE] Drivers_open                     :        202us
    [BOOTLOADER PROFILE] Board_driversOpen                :         34us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9926us
    [BOOTLOADER PROFILE] App_loadImages                   :       7737us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      15078us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      69611us

    Image loading done, switching to application ...
    Starting MCU-m4f and 2nd stage bootloader

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 133.333 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 959 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2821us
    [BOOTLOADER PROFILE] Drivers_open                     :        267us
    [BOOTLOADER PROFILE] Board_driversOpen                :         44us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9971us
    [BOOTLOADER PROFILE] App_loadImages                   :       3381us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      16135us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :      81618us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     114240us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
    NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

    U-Boot SPL 2023.04-g794614311a (Jul 05 2023 - 17:29:58 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
    Trying to boot from NAND
    Authentication passed
    Authentication passed



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

    Arago Project http://arago-project.org am62xx-evm ttyS2

    Arago 2020.09 am62xxx-evm ttyS2

    am62xx-evm login:

\endcond

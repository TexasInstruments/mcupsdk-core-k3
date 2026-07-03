# SBL OSPI NAND Linux {#EXAMPLES_DRIVERS_SBL_OSPI_NAND_LINUX}

\note The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.

[TOC]

# Introduction

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on R5 cores.


The SBL uses 4 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
- tiboot3.bin with **SBL, TIFS, BoardConfig**
- Appimage for **MCU M4**
- DM firmware appimage for **DM R5**

The bootloader does SOC initializations and parses the multicore appimage, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset.

For booting Linux, SBL parses the Linux appimage, splits it into individual linux binaries (ATF, OPTEE, A53 SPL). SBL loads the Linux binaries, entry point is set to the start address of ATF and A53 core is released from reset.


# Supported Combinations

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_nand_linux

# Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
## Flash the OSPI NAND with the default linux image

\note This needs to be the first step as later the tiboot3.bin at the starting of the bootpartition will be overwritten by `sbl_ospi_nand_linux.tiimage` .

- For booting A53 with linux, OSPI NAND needs to be flashed with the uboot and Linux image. Refer to **Processor SDK Linux** user guide on how to flash uboot and Linux kernel to OSPI NAND.

## Create Linux Appimage

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK_LINUX_PATH in file `config.mak`
- Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details

## Run the example

- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for R5, M4 CPUs and Linux Appimage.
- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/examples/drivers/boot/sbl_ospi_nand_linux/@VAR_BOARD_NAME_LOWER/{cpu}_{os}/default_sbl_ospi_nand_linux.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_linux.cfg` shown above.

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/examples/drivers/boot/sbl_ospi_nand_linux/@VAR_SK_LP_BOARD_NAME_LOWER/r5fss0-0_nortos/default_sbl_ospi_nand_linux.cfg
# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

    SYSFW Version 8.4.3--w2022.02-am62a (Jolly Je
    SYSFW revision 0x8
    DMSC ABI revision 3.1

    [KPI] Boot Media       : SPI FLASH
    [KPI] Boot Media Clock : 200.000 MHz
    [KPI] Boot Image Size  : 957 KB
    [KPI] Cores present    :
    mcu-r5f0-0
    r5f0-0
    a530-0
    [KPI] System_init                      :      38236us
    [KPI] Drivers_open                     :         94us
    [KPI] Board_driversOpen                :         75us
    [KPI] Sciclient Get Version            :      10112us
    [KPI] App_loadImages                   :      26335us
    [KPI] App_loadSelfcoreImage            :      84645us
    [KPI] App_loadLinuxImages              :     522175us
    [KPI] SBL Total Time Taken             :     681675us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.6(release):08.03.00.003-dirty
    NOTICE:  BL31: Built : 19:07:38, Aug 10 2022

    U-Boot SPL 2021.01-gacf0fe0dc6 (Aug 10 2022 - 19:11:27 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0008 '8.4.3--w2022.02-am62a (Jolly Je')
    am62a_init: board_init_f done
    am62a_init: spl_boot_device: devstat = 0x3 bootmedia = 0x7 bootindex = 0
    Trying to boot from SPINAND
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

    Arago Project http://arago-project.org am62axx-evm ttyS2

    Arago 2020.09 am62axx-evm ttyS2

    am62axx-evm login:

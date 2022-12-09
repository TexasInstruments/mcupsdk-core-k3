# SBL OSPI NAND Linux Multistage {#EXAMPLES_DRIVERS_SBL_OSPI_NAND_LINUX_MULTISTAGE}

\note The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.

[TOC]

# Introduction
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

\cond SOC_AM6A2X

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


# Supported Combinations

\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_nand_linux_multistage
\endcond

\cond SOC_AM62AX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_nand_linux_multistage
\endcond

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
\cond SOC_AM62X
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.

\note Change PSDK_LINUX_HS_IMAGE_PATH to the path where A53 spl images (ATF, OPTEE, A53 uboot) is.
\endcond

\note Instructions to build A53 uboot can be found in the SDK Linux documentation at
        **Foundational Components » U-Boot » User’s Guide » General Information » Build U-Boot**

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**
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

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage1/@VAR_SK_LP_BOARD_NAME_LOWER/{cpu}_{os}/default_sbl_ospi_linux.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage1/@VAR_SK_LP_BOARD_NAME_LOWER/r5fss0-0_nortos/default_sbl_ospi_nand_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage1/@VAR_SK_LP_BOARD_NAME_LOWER/r5fss0-0_nortos/default_sbl_ospi_nand_linux.cfg

\endcond

\cond SOC_AM62AX
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for DM R5, MCU R5 CPUs and Linux Appimage.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage1/@VAR_BOARD_NAME_LOWER/{cpu}_{os}/default_sbl_ospi_linux.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage1/@VAR_BOARD_NAME_LOWER/r5fss0-0_nortos/default_sbl_ospi_nand_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/examples/drivers/boot/sbl_ospi_nand_linux_multistage/sbl_ospi_nand_linux_stage1/@VAR_BOARD_NAME_LOWER/r5fss0-0_nortos/default_sbl_ospi_nand_linux.cfg
\endcond

- Boot the EVM in OSPI NAND boot mode.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output
After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

\cond SOC_AM62X

    DMSC Firmware Version 8.4.3--w2022.02-am62a (Jolly Je
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 133 KB
    [BOOTLOADER_PROFILE] Cores present    :
    mcu-r5f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      38459us
    [BOOTLOADER PROFILE] Drivers_open                     :         94us
    [BOOTLOADER PROFILE] Board_driversOpen                :         75us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10112us
    [BOOTLOADER PROFILE] App_loadImages                   :      26331us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      63094us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     138168us

    Image loading done, switching to application ...
    Starting MCU-r5f and 2nd stage bootloader

    DMSC Firmware Version 8.4.3--w2022.02-am62a (Jolly Je
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 917 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       1557us
    [BOOTLOADER PROFILE] Drivers_open                     :         97us
    [BOOTLOADER PROFILE] Board_driversOpen                :         72us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10177us
    [BOOTLOADER PROFILE] App_loadImages                   :        409us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      81710us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :     504160us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     598184us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.6(release):08.03.00.003-dirty
    NOTICE:  BL31: Built : 19:07:38, Aug 10 2022

    U-Boot SPL 2021.01-gacf0fe0dc6 (Aug 10 2022 - 19:11:27 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0008 '8.4.3--w2022.02-am62a (Jolly Je')
    am62a_init: board_init_f done
    am62a_init: spl_boot_device: devstat = 0x3 bootmedia = 0x7 bootindex = 0
    Trying to boot from SPINAND

    U-Boot 2021.01-g060f008b9f (Aug 26 2022 - 16:48:08 +0000)

    SoC:   AM62AX SR1.0 GP
    Model: Texas Instruments AM62A7 SK
    EEPROM not available at 0x50, trying to read at 0x51
    Board: AM62A-SKEVM rev E1
    DRAM:  2 GiB
    MMC:   mmc@fa10000: 0, mmc@fa00000: 1, mmc@fa20000: 2


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

\cond SOC_AM62AX

    DMSC Firmware Version 8.4.3--w2022.02-am62a (Jolly Je
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 133 KB
    [BOOTLOADER_PROFILE] Cores present    :
    mcu-r5f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      57521us
    [BOOTLOADER PROFILE] Drivers_open                     :         95us
    [BOOTLOADER PROFILE] Board_driversOpen                :         74us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10128us
    [BOOTLOADER PROFILE] App_loadImages                   :      26341us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     157215us

    Image loading done, switching to application ...
    Starting MCU-r5f and 2nd stage bootloader

    DMSC Firmware Version 8.4.3--w2022.02-am62a (Jolly Je
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 917 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       1547us
    [BOOTLOADER PROFILE] Drivers_open                     :         98us
    [BOOTLOADER PROFILE] Board_driversOpen                :         74us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10150us
    [BOOTLOADER PROFILE] App_loadImages                   :        412us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      81651us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     597283us

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
\endcond

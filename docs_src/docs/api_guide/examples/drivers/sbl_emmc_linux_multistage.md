# SBL EMMC Linux {#EXAMPLES_DRIVERS_SBL_EMMC_LINUX_MULTISTAGE}

\note SBL EMMC Linux boots from the boot partition 1 of eMMC and does not use a filesystem boot. The appimage is flashed to the offsets in eMMC as configured using syscfg.
\attention Care should be taken to ensure that the R5, M4 appimage and the Linux appimage flashed does NOT overwrite the Linux binaries in eMMC.
\note The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.

[TOC]

# Introduction

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on R5 and M4 cores from eMMC.

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

The bootloader does SOC initializations and parses the multicore appimage present at 0x800000 in eMMC boot partition 1, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset.

For booting Linux, SBL parses the Linux appimage present at 0xA00000 in eMMC boot partition, splits it into individual linux binaries (ATF, OPTEE, SPL). SBL loads the Linux binaries, entry point is set to the start address of ATF and A53 core is released from reset.


# Supported Combinations

\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_emmc_linux_multistage
\endcond

\cond SOC_AM62AX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_emmc_linux_multistage
\endcond

# Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Flash the eMMC with the default linux image

\note This needs to be the first step as later the tiboot3.bin at the starting of the bootpartition will be overwritten by `sbl_emmc_linux.tiimage` .

- For booting A53 with linux, eMMC needs to be flashed with the Linux image. Refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/Foundational_Components/U-Boot/UG-Memory.html, **Processor SDK Linux**} user guide on how to flash eMMC to boot Linux.

## Create Linux Appimage

\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.

\note For HS, Instructions to build A53 uboot can be found in the SDK Linux documentation at
        **Foundational Components » U-Boot » User’s Guide » General Information » Build U-Boot**

\note Copy ATF, OPTEE from ${SDK_INSTALL_PATH}/board-support/prebuilt-images and ${OUTPUT_PATH_OF_U-BOOT_A53}/a53/spl/u-boot-spl.bin (unsigned image) to a new folder.

\note Change PSDK_LINUX_HS_IMAGE_PATH to the path where A53 spl images (ATF, OPTEE, A53 uboot) are copied.

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

- This example is the SBL which needs to be flashed on the eMMC, along with sample application images for R5, M4 CPUs and Linux Appimage.
\note Use **default_sbl_emmc_linux_hs.cfg** when flashing to HS devices
- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage1/@VAR_BOARD_NAME_LOWER/{cpu}_{os}/default_sbl_emmc_linux.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_emmc_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage1/@VAR_BOARD_NAME_LOWER/r5fss0-0_nortos/default_sbl_emmc_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/examples/drivers/boot/sbl_emmc_linux_multistage/sbl_emmc_linux_stage1/@VAR_BOARD_NAME_LOWER/r5fss0-0_nortos/default_sbl_emmc_linux.cfg

- Boot the EVM in eMMC boot mode to boot Linux on A53 and RTOS/Baremetal application on R5 and M4 cores.

\note User might be required to set environmet variables from uBooot prompt to boot linux kernel from eMMC. Refer to **Processor SDK Linux** user guide for details.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

    DMSC Firmware Version 8.4.7--v08.04.07 (Jolly Jellyfi
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 152 KB
    [BOOTLOADER_PROFILE] Cores present    :
    m4f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      27757us
    [BOOTLOADER PROFILE] Drivers_open                     :     764670us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10115us
    [BOOTLOADER PROFILE] App_loadImages                   :     129890us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :    1090861us

    Image loading done, switching to application ...
    Starting MCU-m4f and 2nd stage bootloader

    DMSC Firmware Version 8.4.7--v08.04.07 (Jolly Jellyfi
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 853 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2714us
    [BOOTLOADER PROFILE] Drivers_open                     :     764715us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10181us
    [BOOTLOADER PROFILE] App_loadImages                   :      51580us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :     334055us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :    1544969us

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
    Trying to boot from MMC1


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

    Arago 2020.09 am64xx-evm ttyS2

    am62xx-evm login:

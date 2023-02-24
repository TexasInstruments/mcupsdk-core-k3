# SBL GPMC NAND Linux Multistage {#EXAMPLES_DRIVERS_SBL_GPMC_NAND_LINUX_MULTISTAGE}

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

## Flash the GPMC NAND with the default linux image

\note This needs to be the first step as later the tiboot3.bin at the starting of the bootpartition will be overwritten by `sbl_gpmc_nand_linux_stage1.tiimage` .

- For booting A53 with linux, GMPC NAND needs to be flashed with the uboot and Linux image. Refer to **Processor SDK Linux** user guide on how to flash uboot and Linux kernel to GMPC NAND.

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

## Create HSM Appimage

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details

## Run the example

\cond SOC_AM62X
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for R5, M4 CPUs and Linux Appimage.
\note For HS-SE device, use **default_sbl_gpmc_linux_hs.cfg** as the cfg file.
\note For HS-FS device, use **default_sbl_gpmc_linux_hs_fs.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_gpmc_linux.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_gpmc_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_gpmc_nand_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_gpmc_nand_linux.cfg

\endcond


- Boot the EVM in GMPC NAND boot mode.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output
After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

\cond SOC_AM62X

    DMSC Firmware Version 8.5.3--v08.05.03 (Chill Capybar
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 133.333 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 151 KB
    [BOOTLOADER_PROFILE] Cores present    :
    m4f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      35664us
    [BOOTLOADER PROFILE] Drivers_open                     :         95us
    [BOOTLOADER PROFILE] Board_driversOpen                :         23us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10111us
    [BOOTLOADER PROFILE] App_loadImages                   :      70241us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :     101763us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     217899us

    Image loading done, switching to application ...
    Starting MCU-m4f and 2nd stage bootloader

    DMSC Firmware Version 8.5.3--v08.05.03 (Chill Capybar
    DMSC Firmware revision 0x8
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SPI FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 133.333 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 969 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2671us
    [BOOTLOADER PROFILE] Drivers_open                     :        107us
    [BOOTLOADER PROFILE] Board_driversOpen                :         34us
    [BOOTLOADER PROFILE] Sciclient Get Version            :      10151us
    [BOOTLOADER PROFILE] App_loadImages                   :      11101us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :     144019us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :     595945us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     764031us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.7(release):v2.7.0-359-g1309c6c805-dirty
    NOTICE:  BL31: Built : 06:15:22, Dec 23 2022
    I/TC:
    I/TC: OP-TEE version: 3.19.0-15-gd6c5d0037 (gcc version 9.2.1 20191025 (GNU Toolchain for the A-profile Architecture 9.2-2019.12 (arm-9.10))) #1 Fri Dec 23 06:19:37 UTC 2022 aarch64
    I/TC: WARNING: This OP-TEE configuration might be insecure!
    I/TC: WARNING: Please check https://optee.readthedocs.io/en/latest/architecture/porting_guidelines.html
    I/TC: Primary CPU initializing
    I/TC: SYSFW ABI: 3.1 (firmware rev 0x0008 '8.5.3--v08.05.03 (Chill Capybar')
    I/TC: HUK Initialized
    I/TC: Activated SA2UL device
    I/TC: Fixing SA2UL firewall owner for GP device
    I/TC: Enabled firewalls for SA2UL TRNG device
    I/TC: SA2UL TRNG initialized
    I/TC: SA2UL Drivers initialized
    I/TC: Primary CPU switching to normal world boot

    U-Boot SPL 2021.01-00001-g1b6a0a56ac-dirty (Dec 26 2022 - 10:50:42 +0530)
    SYSFW ABI: 3.1 (firmware rev 0x0008 '8.5.3--v08.05.03 (Chill Capybar')
    Trying to boot from NAND
    Warning: Did not detect image signing certificate. Skipping authentication to prevent boot failure. This will fail on Security Enforcing(HS-SE) devices
    Warning: Did not detect image signing certificate. Skipping authentication to prevent boot failure. This will fail on Security Enforcing(HS-SE) devices


    U-Boot 2021.01-00001-g1b6a0a56ac-dirty (Dec 26 2022 - 10:50:42 +0530)

    SoC:   AM62X SR1.0 TEST
    Model: Texas Instruments AM62x LP SK
    EEPROM not available at 0x50, trying to read at 0x51
    Board: AM62-LP-SKEVM rev E1
    DRAM:  2 GiB
    NAND:  1024 MiB
    MMC:   mmc@fa10000: 0, mmc@fa00000: 1, mmc@fa20000: 2
    Loading Environment from MMC... OK
    In:    serial@2800000
    Out:   serial@2800000
    Err:   serial@2800000
    Net:
    Warning: ethernet@8000000port@1 (eth0) using random MAC address - e6:6d:1c:d6:d8:95
    eth0: ethernet@8000000port@1


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

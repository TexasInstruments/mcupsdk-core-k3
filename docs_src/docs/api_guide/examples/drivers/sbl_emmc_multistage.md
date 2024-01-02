# SBL EMMC Multistage{#EXAMPLES_DRIVERS_SBL_EMMC_MULTISTAGE}

\note SBL EMMC RTOS/NORTOS boots from the boot partition 1 of eMMC. The appimage is flashed to the offsets in eMMC as configured using syscfg.
\attention Care should be taken to ensure that the R5, M4 and A53 appinage flashed does NOT overwrite the binaries in eMMC.
\note The load address of resource table for R5,M4 and A53 cores must be consistant with the address.

[TOC]

# Introduction

\cond SOC_AM62AX

This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on R5,M4 and A53 cores from eMMC.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and stats running it.

 - The stage2 of the bootloader boots RTOS/NORTOS on A53 and then self loads DM firmware on the DM R5.

The SBL uses 6 appimages
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU R5**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
- Appimage for **A53**
\endcond

# Supported Combinations

\cond SOC_AM62AX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_emmc_multistage
\endcond

# Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Create HSM Appimage

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details

## Run the example

- This example is the SBL which needs to be flashed on the eMMC, along with sample application images for R5, M4 CPUs and A53 Appimage.
\note Use **default_sbl_emmc_hs.cfg** when flashing to HS-SE devices
\note Use **default_sbl_emmc_hs_fs.cfg** when flashing to HS-FS devices
- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_emmc_hs.cfg

- Make sure IPC rpmsg echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_ECHO)

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_emmc_hs.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_emmc_hs.cfg

- If Linux PC is used, assuming SDK is installed at `~PSDK_LINUX_HS_IMAGE_PATH~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER//default_sbl_emmc_hs.cfg

- Boot the EVM in eMMC boot mode to boot RTOS/Baremetal application on R5, M4 and A53 cores.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

\cond SOC_AM62AX

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 151 KB
    [BOOTLOADER_PROFILE] Cores present    :
    mcu-r5f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      40220us
    [BOOTLOADER PROFILE] Drivers_open                     :      30403us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9907us
    [BOOTLOADER PROFILE] App_loadImages                   :      22082us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      23788us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     126403us

    Image loading done, switching to application ...
    Starting MCU-r5f and 2nd stage bootloader

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 302 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    c75ss0
    [BOOTLOADER PROFILE] System_init                      :       2315us
    [BOOTLOADER PROFILE] Drivers_open                     :      19523us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9917us
    [BOOTLOADER PROFILE] App_loadImages                   :      21223us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      24059us
    [BOOTLOADER PROFILE] App_loadA53Images                :      22086us
    [BOOTLOADER PROFILE] App_loadDSPImages                :      24176us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     123304us

    Image loading done, switching to application ...
    Starting RTOS/Baremetal applications
    Hello World!

\endcond
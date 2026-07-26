# SBL EMMC HLOS 


## Introduction

SBL EMMC Linux boots from the boot partition 0 of eMMC and does not use a filesystem boot. The appimage is flashed to the offsets in eMMC as configured using syscfg.

This is a bootloader example, which shows an example of booting Linux/U-Boot/QNX on A53 core and RTOS/NORTOS applications on R5/DSP cores. This SBL target supports booting the following test cases

- SBL Booting Linux Kernel
- SBL Booting U-Boot
- SBL Booting QNX

## Supported Combinations 

::::{only} SOC_J722S

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/drivers/boot/sbl_emmc

::::

## Steps to Run the Example

### Prepare the SD Card

- Create SD card using balena etcher tool, refer Processor-SDK-Linux for more details
- This is needed to have file system in root partition of SD card

### Build the Example

::::{only} not SOC_J722S
- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [CCS_PROJECTS_PAGE](#ccs_projects_page)).
::::
- **When using makefiles to build**, note the required combination and build using
  make command (see [MAKEFILE_BUILD_PAGE](#makefile_build_page))

### Create Linux Appimage

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)** or (ATF, OPTEE, Kernel, DTB) in case of fastboot mode.
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer [LINUX_APPIMAGE_GEN_TOOL](#linux_appimage_gen_tool) for more details

### Create QNX Appimage

- Create a QNX Appimage containing (TAF, OPTEE, QNX-IFS)
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/qnxAppimageGen after setting the PSDK path in file `config.mak`
- Refer [QNX_APPIMAGE_GEN_TOOL](#qnx_appimage_gen_tool) for more details

### Run the Example

- Flash SBL, Appimage to eMMC, follow below steps to flash the binaries
- Create a folder named sbl in the boot partition of wic image flashed SD card and copy SBL image (may be as tiboot3.bin) and application image (may be as app)
- Insert the SD card into the EVM and boot the board in SD boot mode
- Halt at U-Boot and execute the following commands
    - mmc dev 0 1
    - fatload mmc 1 ${loadaddr} sbl/tiboot3.bin
    - mmc write ${loadaddr} 0x0 0x300 (size of app in blocks)
    - fatload mmc 1 ${loadaddr} sbl/app
    - mmc write ${loadaddr} 0x400 0x800 (size of app in blocks)
    - mmc partconf 0 1 1 1
    - mmc bootbus 0 2 0 0
- Note: one block is of size 512 bytes
- Now change the boot switch settings to eMMC boot mode and reset the evm

## See Also

[DRIVERS_BOOTLOADER_PAGE](#drivers_bootloader_page)

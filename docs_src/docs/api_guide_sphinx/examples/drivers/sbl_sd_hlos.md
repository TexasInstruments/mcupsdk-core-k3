# SBL SD HLOS 


## Introduction

This is a bootloader example, which shows an example of booting Linux/U-Boot/QNX on A53 core and RTOS/NORTOS applications on DM R5 and M4 cores. This SBL target supports booting the following test cases

- SBL Booting Linux Kernel
- SBL Booting U-Boot
- SBL Booting QNX

## Supported Combinations

::::{only} SOC_J722S
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/drivers/boot/sbl_ospi_hlos
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

### Run the example

- Copy SBL image as tiboot3.bin to the boot partition of SD card
- Copy HLOS appimage as app to the boot partition of SD card
- Copy u-boot.img to the boot partition of SD card in case booting U-Boot

- Boot the EVM in SD boot mode.

## See Also

[DRIVERS_BOOTLOADER_PAGE](#drivers_bootloader_page)

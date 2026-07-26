# SBL OSPI NAND HLOS 


## Introduction

This is a bootloader example, which shows an example of booting Linux/U-Boot/QNX on A53 core and RTOS/NORTOS applications on DM R5/DSP cores. This SBL target supports booting the following test cases

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
 Example folder | examples/drivers/boot/sbl_ospi_nand_hlos
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

- Flash SBL, Appimage to OSPI NAND Flash, follow below steps to flash the binaries
```{note}
Before running the following command, user needs to build sbl_uart_uniflash_stage1, sbl_uart_uniflash_stage2_nand, sbl_ospi_nand_hlos, HLOS appimage and edit the cfg file according to HLOS appimage that we are booting
- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`
```

        - cd ~/ti/mcu_plus_sdk/tools/boot
        - python uart_uniflash.py -p <main UART COM port> --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_nand_hlos_hs_fs.cfg

- Boot the EVM in OSPI NAND boot mode.
- Another way to flash on to OSPI NAND
    - Create an SD card which boots U-boot
    - Create a folder named boot_imgs in the boot partition of SD card and copy sbl image (may be as tiboot3.bin)
      and application image (may be as app)
    - Boot till U-Boot in SD boot mode and execute the following commands
        - mtd list
        - mtd erase spi-nand0 0x0 0x4000000
        - fatload mmc 1 $loadaddr boot_imgs/tiboot3.bin
        - mtd write spi-nand0 $loadaddr 0x0 $filesize
        - fatload mmc 1 $loadaddr boot_imgs/app
        - mtd write spi-nand0 $loadaddr 0x80000 $filesize

## See Also

[DRIVERS_BOOTLOADER_PAGE](#drivers_bootloader_page)

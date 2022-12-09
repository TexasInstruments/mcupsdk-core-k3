# SBL UART Linux {#EXAMPLES_DRIVERS_SBL_UART_LINUX}

[TOC]

# Introduction

This bootloader does SOC initializations and attempts to boot a multicore appimage received over UART via XMODEM. The image file is sent using a python script (See \ref UART_BOOTLOADER_PYTHON_SCRIPT). Once image is received, the SBL then parses it, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset. For more on bootflow/bootloaders, please refer \ref BOOTFLOW_GUIDE

# Supported Combinations

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_uart_linux

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_uart_linux

\endcond
# Steps to Run the Example
## Build the example
Since this is a bootloader and is used as a SOC initialization binary, the example will be run every time you boot an application using this example. It is generally run from a boot media (OSPI Flash, SD Card or over UART) unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE).

\cond SOC_AM62X || SOC_AM62AX
## Create an SD-Card with Linux image

- For booting A53 with linux SD-Card with linux image needs to be created. Refer to **Processor SDK Linux** user guide on how to create SD-Card to boot Linux.

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

\endcond
# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

Since this SBL receives the appimage over UART using XMODEM protocol, it doesn't print anything to the console so as not to corrupt the XMODEM transport.
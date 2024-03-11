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
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
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

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_uart_linux

\endcond

Refer \ref ENABLE_DDR_INLINE_ECC enablig inline ECC

# Steps to Run the Example
## Build the example
Since this is a bootloader and is used as a SOC initialization binary, the example will be run every time you boot an application using this example. It is generally run from a boot media (OSPI Flash, SD Card or over UART) unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE).

\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX
## Create Linux Appimage

\cond !SOC_AM62PX
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.
\endcond

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details

## Run the example
\cond !SOC_AM62PX
\note For HS-SE device, use default_sbl_uart_hs.cfg as the cfg file.
\endcond
\note For HS-FS device, use default_sbl_uart_hs_fs.cfg as the cfg file.

\cond SOC_AM62X
- Run the following command from the {MCU_PLUS_SDK_INSTALLATION_PATH}/tools/boot
   - For am62x-sk

            python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/am62x-sk/default_sbl_uart_linux.cfg

   - For am62x-sk-lp

            python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/am62x-sk-lp/default_sbl_uart_linux.cfg

   - For am62x-sip-sk

            python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/am62x-sip-sk/default_sbl_uart_linux.cfg

\endcond

\cond SOC_AM62AX || SOC_AM62PX
- Run the following command from the {MCU_PLUS_SDK_INSTALLATION_PATH}/tools/boot
   - For @VAR_BOARD_NAME_LOWER

            python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_uart_linux.cfg

\endcond
Here /dev/ttyUSB0  can be changed to COM port like'COM4' incase of Windows.
\endcond

\cond SOC_AM62X
\note The above config file will flash till u-boot. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/devices/AM62X/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

\cond SOC_AM62AX
\note The above config file will flash till u-boot. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/devices/AM62AX/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

\cond SOC_AM62PX
\note The above config file will flash till u-boot. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/devices/AM62PX/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

Since this SBL receives the appimage over UART using XMODEM protocol, it doesn't print anything to the console so as not to corrupt the XMODEM transport.

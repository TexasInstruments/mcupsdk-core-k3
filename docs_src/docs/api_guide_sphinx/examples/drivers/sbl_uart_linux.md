# SBL UART Linux
## Introduction

This bootloader does SOC initializations and attempts to boot a multicore appimage received over UART via XMODEM. The image file is sent using a python script (See [UART Bootloader Python Script](../../components/tools/tools_boot.md)). Once image is received, the SBL then parses it, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset. For more on bootflow/bootloaders, please refer [Understanding the bootflow and bootloaders](../../developer_guides/bootflow.md)

:::{admonition} Note
This example is loaded with UART bootmode. A53 SPL loaded by this example will pick this up and boot up in UART bootmode. This can be changed by calling SOC_setDevStat() in main.c
:::


:::{admonition} Note
Once the A53 SPL begins execution in UART bootmode(C is printed), the U-Boot image can be sent over UART0(/dev/ttyUSBx for Linux and COMx for Windows). The U-boot image is located at tools/boot/linuxAppimageGen/board. Send the U-boot image using xmodem over UART0. If SD Card is present, U-boot will load the linux filesystem from SD Card.
:::


## Supported Combinations


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart_linux |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart_linux |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart_linux |

::::


Refer [Enabling DDR inline ECC](../../components/drivers/ddr.md) enablig inline ECC

## Steps to Run the Example
## Build the example
Since this is a bootloader and is used as a SOC initialization binary, the example will be run every time you boot an application using this example. It is generally run from a boot media (OSPI Flash, SD Card or over UART) unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)).


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX
   **Create Linux Appimage**

   :::{admonition} Note
   Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.
   :::


   - Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**
   - This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
   - Refer [Linux Appimage Generator Tool](../../components/tools/tools_boot.md) for more details

   **Run the example**
   :::{admonition} Note
   For HS-SE device, use default_sbl_uart_hs.cfg as the cfg file.
   :::

   :::{admonition} Note
   For HS-FS device, use default_sbl_uart_hs_fs.cfg as the cfg file.
   :::


   :::{only} SOC_AM62X
      - Run the following command from the {MCU_PLUS_SDK_INSTALLATION_PATH}/tools/boot
         - For am62x-sk

                  python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/am62x-sk/default_sbl_uart_linux.cfg

         - For am62x-sk-lp

                  python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/am62x-sk-lp/default_sbl_uart_linux.cfg

         - For am62x-sip-sk

                  python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/am62x-sip-sk/default_sbl_uart_linux.cfg

   :::


   ::::{only} SOC_AM62AX or SOC_AM62PX
      - Run the following command from the {MCU_PLUS_SDK_INSTALLATION_PATH}/tools/boot
         - For {{ VAR_BOARD_NAME_LOWER }}

                  python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_uart_linux.cfg

   ::::

   Here /dev/ttyUSB0  can be changed to COM port like'COM4' incase of Windows.
::::


::::{only} SOC_AM62X
   :::{admonition} Note
   The above config file will flash till u-boot. U-Boot can load kernel from any bootmedia, refer to [**Processor SDK Linux**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/devices/AM62X/linux/Overview.html) user guide for more details.
   :::
::::


::::{only} SOC_AM62AX
   :::{admonition} Note
   The above config file will flash till u-boot. U-Boot can load kernel from any bootmedia, refer to [**Processor SDK Linux**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/devices/AM62AX/linux/Overview.html) user guide for more details.
   :::
::::


::::{only} SOC_AM62PX
   :::{admonition} Note
   The above config file will flash till u-boot. U-Boot can load kernel from any bootmedia, refer to [**Processor SDK Linux**](https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/devices/AM62PX/linux/Overview.html) user guide for more details.
   :::
::::


## See Also

[BOOTLOADER](../../components/drivers/bootloader.md)

## Device-Specific Overlay

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX
   - For AM62A, AM62P, AM62X2-SK-LP, and AM62X-SK devices:
      - The overlay is applied to load the ATF at 0x80000000.
      - The overlay code is:

         ```
         /dts-v1/;
         /plugin/;
         / {
             #address-cells = <0x02>;
             #size-cells = <0x02>;
             fragment@0 {
                 #address-cells = <0x02>;
                 #size-cells = <0x02>;
                 ranges;
                 target-path = "/reserved-memory/tfa09e780000";
                 __overlay {
                     #address-cells = <0x02>;
                     #size-cells = <0x02>;
                     ranges;
                     reg = <0x00 0x80000000 0x00 0x80000>;
                 };
             };
         };
         ```
::::

## Sample Output

Since this SBL receives the appimage over UART using XMODEM protocol, it doesn't print anything to the console so as not to corrupt the XMODEM transport.

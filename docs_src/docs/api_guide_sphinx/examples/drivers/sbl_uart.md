# SBL UART
## Introduction


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX

   This bootloader does SOC initializations and attempts to boot a multicore appimage received over UART via XMODEM. The image file is sent using a python script (See [UART Bootloader Python Script](../../components/tools/tools_boot.md)). Once image is received, the SBL then parses it, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset. For more on bootflow/bootloaders, please refer [Understanding the bootflow and bootloaders](../../developer_guides/bootflow.md)

::::


::::{only} SOC_AM275X

   This bootloader does SOC initializations and attempts to boot a multicore elf image (mcelf) received over UART via XMODEM. The image file is sent using a python script (See [UART Bootloader Python Script](../../components/tools/tools_boot.md)). The SBL first recieves the elf image meta data from host, once meta is received, the SBL parses it and requests the program segments applicable for each core by specifying the required segment offset and length to host. It then receives the segments and loads to respective load addresses. Each core is then initialized, entry points are set and the core is released from reset.

   Since the image is received segment wise with proper handshaking between target and host and also loaded directly to load addresses it eliminates the usage of large intermediate scratch buffer to hold the complete image.
   For more on bootflow/bootloaders, please refer [Understanding the bootflow and bootloaders](../../developer_guides/bootflow.md)

::::


## Supported Combinations
::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart |

::::


::::{only} SOC_AM273X or SOC_AWR294X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart |

::::


::::{only} SOC_AM263X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart |

::::


::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0_freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/boot/sbl_uart |

::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX

   Refer [Enabling DDR inline ECC](../../components/drivers/ddr.md) enablig inline ECC

::::


## Steps to Run the Example
## Build the example
Since this is a bootloader and is used as a SOC initialization binary, the example will be run every time you boot an application using this example. It is generally run from a boot media (OSPI Flash, SD Card or over UART) unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)).


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX

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

                  python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/am62x-sk/default_sbl_uart.cfg

         - For am62x-sk-lp

                  python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/am62x-sk-lp/default_sbl_uart.cfg

         - For am62x-sip-sk

                  python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/am62x-sip-sk/default_sbl_uart.cfg

   :::


   :::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
      - Run the following command from the {MCU_PLUS_SDK_INSTALLATION_PATH}/tools/boot
         - For {{ VAR_BOARD_NAME_LOWER }}

                  python uart_bootloader.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_uart.cfg

   ::::

   Here /dev/ttyUSB0  can be changed to COM port like'COM4' incase of Windows.
::::

## See Also

[BOOTLOADER](../../components/drivers/bootloader.md)

## Sample Output

Since this SBL receives the appimage over UART using XMODEM protocol, it doesn't print anything to the console so as not to corrupt the XMODEM transport.

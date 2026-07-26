# SBL UART Uniflash

## Introduction

This is a flash-writer application which works in conjunction with the uart_uniflash.py python script mentioned in [Flashing Tools](../../components/tools/tools_flash.md). Although it is not strictly not a bootloader, it uses bootloader APIs to do basic SOC initialization required to be able to flash binaries to the OSPI flash. Like other SBLs, this is also booted by the ROM bootloader.

Once the example starts running it attempts to receive files via UART+XMODEM and process them in a loop. Once it receives a file (this is sent by the uart_uniflash.py script), it finds out what to do with the received file from the file header. It can be three things:

- Flash the received file at the given offset
- Verify if the data in the received file is present at the given offset
- Erase the flash at the given offset for the given size

The meta-data required for doing these operations (offset, file size, erase size etc.) will be extracted from the same header.

After the file is processed, an acknowledgment is sent back to the host side python script and the loop continues.

This example is more or less like a flashing server, and will never terminate until EVM is powered down or the core is reset.

## Supported Combinations

:::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/drivers/boot/sbl_uart_uniflash

:::

## Steps to Run the Example

Since this is mainly a flash-writer application, this is sent via the UART unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

## See Also

[BOOTLOADER](../../components/drivers/bootloader.md)

## Sample Output

Since this SBL receives the appimage and other files over UART using XMODEM protocol, it doesn't print anything to the console so as not to corrupt the XMODEM transport.

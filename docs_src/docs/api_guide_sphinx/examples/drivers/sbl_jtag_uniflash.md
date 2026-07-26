# SBL JTAG Uniflash

## Introduction

This is a flash-writer example which uses JTAG to write files or erase flash and thereby removes UART dependency.
Although it is not strictly a bootloader, it uses flash APIs to be able to flash binaries to the OSPI flash.
You should run this example in the WKUP-R5F core only after powering on the board in [EVM Setup](../../device/am275x/am275x_evm_setup.md)
This example performs the following operations.

- Flash the received file at the given offset
- Verify if the data in the received file is present at the given offset
- Erase the entire flash.

Once the example starts running it displays a following menu.

```
 1: Erase Complete Flash
 2: Write File to Flash and Verify
 3: Verify file in Flash

 x: Exit

 Enter Choice:
```

After the file is written, verified or flash is erased, an acknowledgment is sent back to the console and the loop continues.
This example is more or less like a flashing server, and will terminate until user does not enter 'x'.

## Supported Combinations
:::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/drivers/boot/sbl_jtag_uniflash

:::

## Steps to Run the Example
:::{note}
When powering the board unplug the UART(J22)
:::

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[BOOTLOADER](../../components/drivers/bootloader.md)

## Sample Output

```

==================
 JTAG Uniflash Menu
 ==================

 1: Erase Complete Flash
 2: Write File to Flash and Verify
 3: Verify file in Flash

 x: Exit

 Enter Choice: 1
 [FLASH WRITER] Erasing complete flash ...
 [FLASH WRITER] This can take few minutes, so please wait ...
 [FLASH WRITER] Erasing complete flash ... SUCCESS !!!


 ==================
 JTAG Uniflash Menu
 ==================

 1: Erase Complete Flash
 2: Write File to Flash and Verify
 3: Verify file in Flash

 x: Exit

 Enter Choice: 2

 Enter file name along with path to write or verify :  ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am275x-evm/sbl_null.release.hs_fs.tiimage
 Enter flash offset (in hex format) : 0x0
 Enter below commands in CCS scripting console to load the file data to memory.
 AFTER the file load is done, enter '1' to continue ...

 var session = ds.openSession("WKUP_R5F_0");
 session.memory.loadBinary(0x72100020n, "${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am275x-evm/sbl_null.release.hs_fs.tiimage");
1
 [FLASH WRITER] Flashing success!!...


 ==================
 JTAG Uniflash Menu
 ==================

 1: Erase Complete Flash
 2: Write File to Flash and Verify
 3: Verify file in Flash

 x: Exit

 Enter Choice: 3

 Enter file name along with path to write or verify : ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am275x-evm/sbl_null.release.hs_fs.tiimage
 Enter flash offset (in hex format) : 0x0
 Enter below commands in CCS scripting console to load the file data to memory.
 AFTER the file load is done, enter '1' to continue ...

 var session = ds.openSession("WKUP_R5F_0");
 session.memory.loadBinary(0x72100020n, "${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am275x-evm/sbl_null.release.hs_fs.tiimage");
1
 [FLASH WRITER] Verifying success!!...


 ==================
 JTAG Uniflash Menu
 ==================

 1: Erase Complete Flash
 2: Write File to Flash and Verify
 3: Verify file in Flash

 x: Exit

 Enter Choice: x

 [FLASH WRITER] Application exited !!!
All tests have passed!!

```

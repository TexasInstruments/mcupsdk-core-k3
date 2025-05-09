# SBL JTAG Uniflash {#EXAMPLES_DRIVERS_SBL_JTAG_UNIFLASH}

[TOC]

# Introduction

This is a flash-writer example which uses JTAG to write files or erase flash and thereby removes UART dependency.
Although it is not strictly a bootloader, it uses flash APIs to be able to flash binaries to the OSPI flash.
You should run this example in the WKUP-R5F core only after powering on the board in \ref BOOTMODE_DEVBOOT
This example performs the following operations.

- Flash the received file at the given offset
- Verify if the data in the received file is present at the given offset
- Erase the entire flash.

Once the example starts running it displays a following menu.

\code
 1: Erase Complete Flash
 2: Write File to Flash and Verify
 3: Verify file in Flash

 x: Exit

 Enter Choice:
\endcode

After the file is written, verified or flash is erased, an acknowledgment is sent back to the console and the loop continues.
This example is more or less like a flashing server, and will terminate until user does not enter 'x'.

# Supported Combinations {#EXAMPLES_DRIVERS_SBL_JTAG_UNIFLASH_COMBOS}

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_jtag_uniflash

\endcond

# Steps to Run the Example
\note  When powering the board unplug the UART(J22)

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

\code

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
 Enter below command in CCS scripting console to load the file data to memory.
 AFTER the file load is done, enter '1' to continue ...

 loadRaw(0x72100020, 0, "${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am275x-evm/sbl_null.release.hs_fs.", 32, false);
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

 Enter file name along with path to write or verify : ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am275x-evm/sbl_null.release.hs_fs.
 Enter flash offset (in hex format) : 0x0
 Enter below command in CCS scripting console to load the file data to memory.
 AFTER the file load is done, enter '1' to continue ...

 loadRaw(0x72100020, 0, "${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/am275x-evm/sbl_null.release.hs_fs.", 32, false);
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

\endcode

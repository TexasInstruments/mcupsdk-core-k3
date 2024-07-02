# SBL SD {#EXAMPLES_DRIVERS_SBL_SD}

[TOC]

# Introduction

\if SOC_AM62AX || SOC_AM62DX

This bootloader does SOC initializations and attempts to boot MCU R5 image by the name "app", DM R5 image by the name "dm", A53 image by the name "app_a53" and C7x image by the name "app_dsp" present in the first FAT partition found in the connected SD card. The file can be copied to the SD card by connecting it to the host PC using a card reader. Make sure that the images are named without any file extension. If the card is new, make sure that it is formatted with FAT32/16.

If the appimage files are found at the location, the SBL reads the files into a buffer, parses it. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset. For more on bootflow/bootloaders, please refer \ref BOOTFLOW_GUIDE

\elseif SOC_AM62X

This bootloader does SOC initializations and attempts to boot MCU M4 image by the name "app", DM R5 image by the name "dm", A53 image by the name "app_a53" present in the first FAT partition found in the connected SD card. The file can be copied to the SD card by connecting it to the host PC using a card reader. Make sure that the images are named without any file extension. If the card is new, make sure that it is formatted with FAT32/16.

If the appimage files are found at the location, the SBL reads the files into a buffer, parses it. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset. For more on bootflow/bootloaders, please refer \ref BOOTFLOW_GUIDE

\else

This bootloader does SOC initializations and attempts to boot a multicore appimage file named "app" present in the first FAT partition found in the connected SD card. The file can be copied to the SD card by connecting it to the host PC using a card reader. Make sure that it is named "app" without any file extension. If the card is new, make sure that it is formatted with FAT32/16.

If a multicore appimage file is found at the location, the SBL reads the file into a buffer, parses it, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset. For more on bootflow/bootloaders, please refer \ref BOOTFLOW_GUIDE

\endif
# Supported Combinations {#EXAMPLES_DRIVERS_SBL_SD_COMBOS}

\cond SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_sd

\endcond

\cond SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_sd

\endcond

\cond SOC_AM62AX || SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_sd

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_sd

\endcond

# Steps to Run the Example

Since this is a bootloader, the example will be run every time you boot an application using this example. It is run from an SD card unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Refer to the page \ref BASIC_STEPS_TO_FLASH_FILES to flash this bootloader along with the application to boot.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output
\if SOC_AM62AX || SOC_AM62DX
\code
[BOOTLOADER_PROFILE] Boot Media       : SD Card
[BOOTLOADER_PROFILE] Boot Image Size  : 198 KB
[BOOTLOADER_PROFILE] Cores present    :
mcu-r5f0-0
r5f0-0
a530-0
[BOOTLOADER PROFILE] System_init                                :      38668us
[BOOTLOADER PROFILE] Drivers_open                               :      97508us
[BOOTLOADER PROFILE] Board_driversOpen                          :          0us
[BOOTLOADER PROFILE] File read from SD card                     :       9813us
[BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_MCU_R5FSS0_0)   :      69261us
[BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_R5FSS0_0)       :      75471us
[BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_A53SS0_0)       :      70009us
[BOOTLOADER PROFILE] SBL End                                    :        156us
[BOOTLOADER_PROFILE] SBL Total Time Taken                       :     360890us

Image loading done, switching to application ...
\endcode

\elseif SOC_AM62X
\code
SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
SYSFW Firmware revision 0x9
SYSFW ABI revision 3.1

[BOOTLOADER_PROFILE] Boot Media       : SD Card
[BOOTLOADER_PROFILE] Boot Image Size  : 198 KB
[BOOTLOADER_PROFILE] Cores present    :
m4f0-0
r5f0-0
a530-0
[BOOTLOADER PROFILE] System_init                      :      33665us
[BOOTLOADER PROFILE] Board_init                       :          0us
[BOOTLOADER PROFILE] Drivers_open                     :     108146us
[BOOTLOADER PROFILE] Board_driversOpen                :          0us
[BOOTLOADER PROFILE] File read from SD card           :      10341us
[BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_M4FSS0_0) :     152950us
[BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_R5FSS0_0) :     141854us
[BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_A53SS0_0) :     138552us
[BOOTLOADER PROFILE] SBL End                          :        150us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :     585663us

Image loading done, switching to application ...
[IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
[IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
All tests have passed!!

SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
SYSFW Firmware revision 0x9
SYSFW ABI revision 3.1

[BOOTLOADER_PROFILE] Boot Media       : SD Card
[BOOTLOADER_PROFILE] Boot Image Size  : 198 KB
[BOOTLOADER_PROFILE] Cores present    :
m4f0-0
r5f0-0
a530-0
[BOOTLOADER PROFILE] System_init                      :      33597us
[BOOTLOADER PROFILE] Board_init                       :          0us
[BOOTLOADER PROFILE] Drivers_open                     :     108073us
[BOOTLOADER PROFILE] Board_driversOpen                :          0us
[BOOTLOADER PROFILE] File read from SD card           :      10335us
[BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_M4FSS0_0) :     152960us
[BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_R5FSS0_0) :     162888us
[BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_A53SS0_0) :     159556us
[BOOTLOADER PROFILE] SBL End                          :        150us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :     627564us

Image loading done, switching to application ...
[IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
[IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
All tests have passed!!
\endcode

\else
\code
[BOOTLOADER PROFILE] SYSFW Load                       :      17632us
[BOOTLOADER PROFILE] System_init                      :      12246us
[BOOTLOADER PROFILE] Drivers_open                     :      82499us
[BOOTLOADER PROFILE] Board_driversOpen                :          0us
[BOOTLOADER PROFILE] File read from SD card           :       6843us
[BOOTLOADER PROFILE] CPU load                         :       9501us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :     129399us

Image loading done, switching to application ...
\endcode
\endif
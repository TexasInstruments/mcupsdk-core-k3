# SBL SD LINUX {#EXAMPLES_DRIVERS_SBL_SD_LINUX}

\note SBL SD Linux boots from the boot partition 1 of SD and uses a filesystem boot.

\cond SOC_AM62AX
\attention Care should be taken to ensure that the MCU_R5, DM_R5, C7x appimages and the Linux appimage flashed with correct names.
\endcond

\cond SOC_AM62PX
\attention Care should be taken to ensure that the MCU_R5, WKUP_R5 and the Linux appimage flashed with correct names.
\endcond

[TOC]

# Introduction

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on R5 cores.

The SBL uses two appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.

\cond SOC_AM62AX
- A muticore appimage containing the **RTOS/NORTOS applications for MCU_R5, DM_R5 and C7x cores**.
\endcond

\cond SOC_AM62PX
- A muticore appimage containing the **RTOS/NORTOS applications for MCU_R5, WKUP_R5 cores**.
\endcond

The bootloader does SOC initializations and parses the multicore appimage present in boot partition of sd card, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset.

For booting Linux, SBL parses the Linux appimage present as linux_a53_image in boot partition of sd card, splits it into individual linux binaries (ATF, OPTEE, SPL). SBL loads the Linux binaries, entry point is set to the start address of ATF and A53 core is released from reset.

# Supported Combinations {#EXAMPLES_DRIVERS_SBL_SD_LINUX_COMBOS}

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_sd

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_uart_linux

\endcond

# Steps to Run the Example

Since this is a bootloader, the example will be run every time you boot an application using this example. It is run from an SD card unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Refer to the page \ref BASIC_STEPS_TO_FLASH_FILES to flash this bootloader along with the application to boot.

# Flash SD card

Copy sbl_sd_linux.tiimage to boot partition of the SD card as tiboot3.bin.
For booting A53 with Linux and running applications on other cores (MCU R5F, DM R5F, C7x) the appimages should be copied to SD card with correct file names.

File names for respective applications
\cond SOC_AM62AX

- Linux APP image **linux_a53_image**
- R5 APP image **dm_r5_image**
- MCU R5 APP image **mcu_r5_image**
- C7X image **c7x_image**

\endcond

\cond SOC_AM62PX

- Linux APP image **linux_a53_image**
- R5 APP image **wkup_r5_image**
- MCU R5 APP image **mcu_r5_image**

\endcond

\note All the images should be present in boot partition of SD card.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output
\if SOC_AM62AX
\code
    DMSC Firmware Version 9.0.5--v09.00.05 (Kool Koala)
    DMSC Firmware revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SD Card
    [BOOTLOADER_PROFILE] Boot Image Size  : 198 KB
    [BOOTLOADER_PROFILE] Cores present    :
    mcu-r5f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :      38563us
    [BOOTLOADER PROFILE] Drivers_open                     :     125747us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9814us
    [BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_R5FSS0_0) :     150395us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :     145879us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     470400us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
    NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

    U-Boot SPL 2023.04-g24098ea90d (Jul 06 2023 - 12:59:40 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
    am62a_init: board_init_f done
    am62a_init: spl_boot_device: devstat = 0x243 bootmedia = 0x8 bootindex = 0
    Trying to boot from MMC2
    am62a_init: spl_boot_device: devstat = 0x243 bootmedia = 0x8 bootindex = 0
    Authentication passed
    am62a_init: spl_boot_device: devstat = 0x243 bootmedia = 0x8 bootindex = 0
    Authentication passed


    U-Boot 2023.04-g756ba776d4 (Jul 13 2023 - 05:36:12 +0000)

    SoC:   AM62AX SR1.0 HS-FS
    Model: Texas Instruments AM62A7 SK
    DRAM:  2 GiB (effective 4 GiB)
    Core:  57 devices, 27 uclasses, devicetree: separate
    MMC:   mmc@fa10000: 0, mmc@fa00000: 1
    Loading Environment from nowhere... OK
    In:    serial@2800000
    Out:   serial@2800000
    Err:   serial@2800000
    Net:   eth0: ethernet@8000000port@1
    Hit any key to stop autoboot:  0
    =>


    .
    .
    .
    .
    .
    .


    _____                    _____           _         _
    |  _  |___ ___ ___ ___   |  _  |___ ___  |_|___ ___| |_
    |     |  _| .'| . | . |  |   __|  _| . | | | -_|  _|  _|
    |__|__|_| |__,|_  |___|  |__|  |_| |___|_| |___|___|_|
                |___|                    |___|

    Arago Project am62axx-evm -

    Arago 2023.04 am62axx-evm -

    am62axx-evm login:

\endcode
\endif

\if SOC_AM62PX
\code
    DMSC Firmware Version 9.1.5--v09.01.05 (Kool Koala)
    DMSC Firmware revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : SD Card
    [BOOTLOADER_PROFILE] Boot Image Size  : 190 KB
    [BOOTLOADER_PROFILE] Cores present    :
    mcu-r5f0-0
    wkup-r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :      38931us
    [BOOTLOADER PROFILE] Drivers_open                     :     107950us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9776us
    [BOOTLOADER PROFILE] App_loadImages(CSL_CORE_ID_WKUP_R5FSS0_0) :     151451us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :     147606us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     455716us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.9(release):v2.9.0-dirty
    NOTICE:  BL31: Built : 14:12:59, May 22 2023

    U-Boot SPL 2023.04-g48c1296285 (Sep 14 2023 - 21:24:43 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.1.5--v09.01.05 (Kool Koala)')
    Trying to boot from MMC2
    Authentication passed
    Authentication passed


    U-Boot 2023.04-g2e0e4ab05e (Nov 03 2023 - 22:40:06 +0000)

    SoC:   AM62PX SR1.0 HS-FS
    Model: Texas Instruments AM62P5 SK
    DRAM:  2 GiB (effective 8 GiB)
    Core:  79 devices, 29 uclasses, devicetree: separate
    MMC:   mmc@fa10000: 0, mmc@fa00000: 1
    Loading Environment from nowhere... OK
    In:    serial@2800000
    Out:   serial@2800000
    Err:   serial@2800000
    Net:
    Warning: ethernet@8000000port@1 (eth0) using random MAC address - 6e:fa:4d:03:fd:23
    eth0: ethernet@8000000port@1
    Warning: ethernet@8000000port@2 (eth1) using random MAC address - d6:2c:d6:ca:5f:1b
    , eth1: ethernet@8000000port@2
    Hit any key to stop autoboot:  0
    =>


    .
    .
    .
    .
    .
    .


     _____                    _____           _         _
    |  _  |___ ___ ___ ___   |  _  |___ ___  |_|___ ___| |_
    |     |  _| .'| . | . |  |   __|  _| . | | | -_|  _|  _|
    |__|__|_| |__,|_  |___|  |__|  |_| |___|_| |___|___|_|
                  |___|                    |___|

    Arago Project am62pxx-evm -

    Arago 2023.04 am62pxx-evm -

    am62pxx-evm login:

\endcode
\endif
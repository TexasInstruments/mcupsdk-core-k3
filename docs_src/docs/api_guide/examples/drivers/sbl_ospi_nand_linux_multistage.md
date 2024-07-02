# SBL OSPI NAND Linux Multistage {#EXAMPLES_DRIVERS_SBL_OSPI_NAND_LINUX_MULTISTAGE}

\note The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.

[TOC]

# Introduction

\cond SOC_AM62X

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on DM R5 and M4 cores.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and stats running it.

 - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.

The SBL uses 6 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU M4**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
\endcond

\cond SOC_AM62AX || SOC_AM62DX

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on DM R5, MCU R5 and C75 cores.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU R5 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and stats running it.

 - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.

The SBL uses 7 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU R5**
- Appimage for **HSM M4**
- Appimage for **C75**
- DM firmware appimage for **DM R5**
\endcond

Refer \ref SBL_BOOTING_LINUX_OSPI for more details on the OSPI boot loader.

Refer \ref ENABLE_DDR_INLINE_ECC enablig inline ECC

# Supported Combinations

\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_nand_linux_multistage
\endcond

\cond SOC_AM62AX || SOC_AM62DX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_nand_linux_multistage
\endcond

# Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.

## Create Linux Appimage
\cond SOC_AM62X
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.
\endcond

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details

## Create HSM Appimage
\cond SOC_AM62X
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate HSM Appimage for HS-SE device.
\endcond

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details

## Run the example

\cond SOC_AM62X
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for R5, M4 CPUs and Linux Appimage.

\note For HS-SE device, use **default_sbl_ospi_nand_linux_hs.cfg** as the cfg file.
\note For HS-FS device, use **default_sbl_ospi_nand_linux_hs_fs.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_ospi_nand_linux.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_nand_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_ospi_nand_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_ospi_nand_linux.cfg

\endcond

\cond SOC_AM62AX || SOC_AM62DX
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for DM R5, MCU R5, C75, HSM M4 CPUs and Linux Appimage.
\note For HS-SE device, use **default_sbl_ospi_nand_linux_hs.cfg** as the cfg file.
\note For HS-FS device, use **default_sbl_ospi_nand_linux_hs_fs.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_nand_linux_hs_fs.cfg

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentioned in Linux dts file.


- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_nand_linux_hs_fs.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_nand_linux_hs_fs.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_nand_linux_hs_fs.cfg
\endcond

- Boot the EVM in OSPI NAND boot mode.

\cond SOC_AM62X
\note The above config file will flash till u-boot on the OSPI NAND bootmedia. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/devices/AM62X/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

\cond SOC_AM62AX || SOC_AM62DX
\note The above config file will flash till u-boot on the OSPI NAND bootmedia. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/devices/AM62AX/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

\cond SOC_AM62PX
\note The above config file will flash till u-boot on the OSPI NAND bootmedia. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/devices/AM62PX/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

# See Also

- \ref DRIVERS_BOOTLOADER_PAGE

\cond SOC_AM62X
- Refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html, **Processor SDK Linux - Boot time Optimizations**} guide to optimize the time taken by bootloader in the boot sequence.
\endcond

\cond SOC_AM62AX || SOC_AM62DX
- Refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html, **Processor SDK Linux - Boot time Optimizations**}  guide to optimize the time taken by bootloader in the boot sequence.
\endcond

\cond SOC_AM62PX
- Refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html, **Processor SDK Linux - Boot time Optimizations**}  guide to optimize the time taken by bootloader in the boot sequence.
\endcond

# Sample Output
After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

\cond SOC_AM62X
    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 182 KB
    [BOOTLOADER_PROFILE] Cores present    :
    m4f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      37270us
    [BOOTLOADER PROFILE] Drivers_open                     :        207us
    [BOOTLOADER PROFILE] Board_driversOpen                :         88us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9925us
    [BOOTLOADER PROFILE] App_waitForMcuPbist              :          5us
    [BOOTLOADER PROFILE] App_waitForMcuLbist              :       7689us
    [BOOTLOADER PROFILE] App_loadImages                   :       5520us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      10788us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      71496us

    Image loading done, switching to application ...
    Starting MCU-m4f and 2nd stage bootloader

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 895 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2845us
    [BOOTLOADER PROFILE] Drivers_open                     :        269us
    [BOOTLOADER PROFILE] Board_driversOpen                :         89us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9976us
    [BOOTLOADER PROFILE] App_loadImages                   :       2427us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      11338us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :      52860us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      79806us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
    NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

    U-Boot SPL 2023.04-ga3595f1e3e (Jun 15 2023 - 08:14:46 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
    Trying to boot from SPINAND


    U-Boot 2023.04-ga3595f1e3e (Jun 15 2023 - 08:14:46 +0000)

    SoC:   AM62X SR1.0 HS-FS
    Model: Texas Instruments AM62x LP SK
    EEPROM not available at 80, trying to read at 81
    Board: AM62-LP-SKEVM rev E1
    DRAM:  2 GiB



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

    Arago Project am62xx-lp-evm -

    Arago 2023.04 am62xx-lp-evm -

    am62xx-lp-evm login:


\endcond

\cond SOC_AM62AX || SOC_AM62DX

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 184 KB
    [BOOTLOADER_PROFILE] Cores present    :
    mcu-r5f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      39073us
    [BOOTLOADER PROFILE] Drivers_open                     :        191us
    [BOOTLOADER PROFILE] Board_driversOpen                :       5541us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9894us
    [BOOTLOADER PROFILE] App_waitForMcuPbist              :          4us
    [BOOTLOADER PROFILE] App_waitForMcuLbist              :       7792us
    [BOOTLOADER PROFILE] App_loadImages                   :       3689us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       7092us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      73280us

    Image loading done, switching to application ...
    Starting MCU-r5f and 2nd stage bootloader

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 1045 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    c75ss0
    [BOOTLOADER PROFILE] System_init                      :       1792us
    [BOOTLOADER PROFILE] Drivers_open                     :        224us
    [BOOTLOADER PROFILE] Board_driversOpen                :       5543us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9913us
    [BOOTLOADER PROFILE] App_loadImages                   :       2093us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       6912us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :      31427us
    [BOOTLOADER PROFILE] App_loadDSPImages                :       7284us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      65191us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
    NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

    U-Boot SPL 2023.04-g794614311a (Jul 05 2023 - 17:29:58 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
    am62a_init: board_init_f done
    am62a_init: spl_boot_device: devstat = 0x3 bootmedia = 0x10 bootindex = 0
    Trying to boot from SPINAND
    am62a_init: spl_boot_device: devstat = 0x3 bootmedia = 0x10 bootindex = 0
    Authentication passed
    am62a_init: spl_boot_device: devstat = 0x3 bootmedia = 0x10 bootindex = 0
    Authentication passed


    U-Boot 2023.04-g794614311a (Jul 05 2023 - 17:29:58 +0000)

    SoC:   AM62AX SR1.0 HS-FS
    Model: Texas Instruments AM62A7 SK

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

    Arago Project http://arago-project.org am62axx-evm ttyS2

    Arago 2020.09 am62axx-evm ttyS2

    am62axx-evm login:
\endcond

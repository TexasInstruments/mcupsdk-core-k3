# SBL OSPI Linux Multistage {#EXAMPLES_DRIVERS_SBL_OSPI_LINUX_MULTISTAGE}

\note The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.

[TOC]

# Introduction

\cond SOC_AM62AX
\note By default, AM62AX-SK ships with OSPI NAND flash. This example is applicable only after modifying it to OSPI NOR flash
\endcond

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

\cond SOC_AM62AX

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on DM R5, MCU R5 and C75 cores.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU R5 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and stats running it.

 - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.

The SBL uses 6 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU R5**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
\endcond

\cond SOC_AM62PX

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on WKUP R5, MCU R5 cores.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It initializes the DDR. Then it loads the stage2 of the bootloader with Device Manager to DDR and stats running it.
 - Stage2 is a multithreaded application which boots HSM-M4, RTOS on MCU-R5F, Linux on A53 in bootloader therad and sciserver will be running in another thread.

The SBL uses 5 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **WKUP R5 with SBL stage2**
- Appimage for **MCU R5**
- Appimage for **HSM M4**

\endcond

Refer \ref SBL_BOOTING_LINUX_OSPI for more details on the OSPI boot loader.

\cond SOC_AM62AX || SOC_AM62X || SOC_AM62PX
In order to boot faster,
- Linux appimage can be packaged with the Linux kernel and DTB in falcon mode (\ref LINUX_APPIMAGE_GEN_TOOL). Refer to Processor SDK Linux for more information on how to create a buildable Kernel and DTB
- This example reuses the OSPI initialization already performed at SBL stage 1 instead of reprogramming it. This is done by enabling the **Skip OSPI Programming** option in SBL stage 2 sysconfig
\endcond

Refer \ref ENABLE_DDR_INLINE_ECC enablig inline ECC

# Supported Combinations

\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_linux_multistage
\endcond

\cond SOC_AM62AX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_linux_multistage
\endcond

\cond SOC_AM62PX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_linux_multistage
\endcond



# Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Create Linux Appimage

\cond !SOC_AM62PX
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.
\endcond

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)** or (ATF, OPTEE, Kernel, DTB) in case of falcon mode.
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details

## Create HSM Appimage

\cond !SOC_AM62PX
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate Linux Appimage for HS-SE device.
\endcond

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details

## Run the example

\cond SOC_AM62X
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for R5, M4 CPUs and Linux Appimage.
\endcond

\cond SOC_AM62AX
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for DM R5, C7x, MCU R5 CPUs and Linux Appimage.
\endcond

\cond SOC_AM62PX
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for WKUP R5, MCU R5 CPUs and Linux Appimage.
\endcond

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux.cfg

\cond !SOC_AM62PX
- For HS-SE device, use **default_sbl_ospi_linux_hs.cfg** as the cfg file.
\endcond
- For HS-FS device, use **default_sbl_ospi_linux_hs_fs.cfg** as the cfg file.

- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

\cond SOC_AM62PX
- If only stage 2 bootloader with Device Manager is required on wkup-r5 core, update the wkup-r5 image in the flash config with sbl_ospi_linux_stage2 image

        # 2nd stage bootloader with DM is flashed at 0x80000 or to whatever offset your bootloader is configured for
        --file=../../examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/sbl_ospi_linux_stage2.release.appimage --operation=flash --flash-offset=0x80000

\note For early splash and display sharing on HLOS with SBL on HS-FS device, use **default_sbl_ospi_linux_hs_fs_splash_screen.cfg** as the cfg file.
\endcond

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux.cfg

- Boot the EVM in OSPI NOR boot mode.

\cond SOC_AM62X
\note The above config file will flash till u-boot on the OSPI NOR bootmedia. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/devices/AM62X/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

\cond SOC_AM62AX
\note The above config file will flash till u-boot on the OSPI NOR bootmedia. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/devices/AM62AX/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

\cond SOC_AM62PX
\note The above config file will flash till u-boot on the OSPI NOR bootmedia. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/devices/AM62PX/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

# See Also

- \ref DRIVERS_BOOTLOADER_PAGE

\cond SOC_AM62X
- Refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/linux/How_to_Guides/Target/How_to_boot_quickly.html, **Processor SDK Linux - Boot time Optimizations**} guide to optimize the time taken by bootloader in the boot sequence.
\endcond

\cond SOC_AM62AX
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
    [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 184 KB
    [BOOTLOADER_PROFILE] Cores present    :
    m4f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :       6411us
    [BOOTLOADER PROFILE] Drivers_open                     :        208us
    [BOOTLOADER PROFILE] Board_driversOpen                :      27571us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9927us
    [BOOTLOADER PROFILE] App_waitForMcuPbist              :          5us
    [BOOTLOADER PROFILE] App_waitForMcuLbist              :       7689us
    [BOOTLOADER PROFILE] App_loadImages                   :       3535us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       6279us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      61628us

    Image loading done, switching to application ...
    Starting MCU-m4f and 2nd stage bootloader

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 940 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2825us
    [BOOTLOADER PROFILE] Drivers_open                     :        266us
    [BOOTLOADER PROFILE] Board_driversOpen                :      27055us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9967us
    [BOOTLOADER PROFILE] App_loadImages                   :       1961us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       6557us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :      29163us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      77797us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
    NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

    U-Boot SPL 2023.04-ga3595f1e3e (Jun 15 2023 - 08:14:46 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
    SPL initial stack usage: 1856 bytes
    Trying to boot from SPI
    Authentication passed
    Authentication passed


    U-Boot 2023.04-gd6bccb1b9e (Jun 09 2023 - 06:25:21 +0000)

    SoC:   AM62X SR1.0 HS-FS
    Model: Texas Instruments AM625 SK
    EEPROM not available at 80, trying to read at 81
    Board: AM62-SKEVM rev E3
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

    Arago Project am62xx-evm -

    Arago 2023.04 am62xx-evm -

    am62xx-evm login:

\endcond


\cond SOC_AM62PX


    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 180 KB
    [BOOTLOADER_PROFILE] Cores present    :
    wkup-r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      38923us
    [BOOTLOADER PROFILE] Drivers_open                     :          0us
    [BOOTLOADER PROFILE] SBL Drivers_open                 :        150us
    [BOOTLOADER PROFILE] Board_driversOpen                :         10us
    [BOOTLOADER PROFILE] SBL Board_driversOpen            :      21978us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       5611us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      66674us

    Image loading done, switching to application ...
    Starting 2nd stage bootloader
    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 853 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    mcu-r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2305us
    [BOOTLOADER PROFILE] Board_init                       :          0us
    [BOOTLOADER PROFILE] SciserverInit                    :      16144us
    [BOOTLOADER PROFILE] SBL Drivers_open                 :        359us
    [BOOTLOADER PROFILE] SBL Board_driversOpen            :      22009us
    [BOOTLOADER PROFILE] App_loadImages                   :       1829us
    [BOOTLOADER PROFILE] App_loadMCUImages                :       3521us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :      19311us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      65479us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.9(release):v2.9.0-dirty
    NOTICE:  BL31: Built : 14:12:59, May 22 2023

    U-Boot SPL 2023.04-g48c1296285 (Sep 14 2023 - 21:24:43 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.6--w09.00.04-am62p (Kool Ko')
    Trying to boot from SPI
    Authentication passed
    Authentication passed


    U-Boot 2023.04-g48c1296285 (Sep 14 2023 - 21:24:43 +0000)

    SoC:   AM62PX SR1.0 HS-FS
    Model: Texas Instruments AM62P5 SK
    DRAM:  2 GiB (effective 8 GiB)
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

\endcond
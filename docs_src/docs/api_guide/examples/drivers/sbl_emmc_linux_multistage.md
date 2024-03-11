# SBL EMMC Linux Multistage{#EXAMPLES_DRIVERS_SBL_EMMC_LINUX_MULTISTAGE}

\note SBL EMMC Linux boots from the boot partition 1 of eMMC and does not use a filesystem boot. The appimage is flashed to the offsets in eMMC as configured using syscfg.
\attention Care should be taken to ensure that the R5, M4 appimage and the Linux appimage flashed does NOT overwrite the Linux binaries in eMMC.
\note The load address of resource table for R5 and M4 cores must be consistant with the address in the Linux dts file.

[TOC]

# Introduction

\cond SOC_AM62X

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on R5 and M4 cores from eMMC.

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

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on DM R5, MCU R5 and C75 cores from eMMC.


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

\cond SOC_AM62PX

This is a bootloader example, which shows an example of booting Linux on A53 core and RTOS/NORTOS applications on WKUP R5, MCU R5 cores from eMMC.


The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It initializes the DDR. Then it loads the stage2 of the bootloader with Device Manager to DDR and starts running it.
 - Stage2 is a multithreaded application which boots HSM-M4, RTOS on MCU-R5F, Linux on A53 in bootloader therad and sciserver will be running in another thread.

The SBL uses 5 appimages
- A Linux appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**.
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **WKUP R5 with SBL stage2**
- Appimage for **MCU R5**
- Appimage for **HSM M4**
\endcond

The bootloader does SOC initializations and parses the multicore appimage present in eMMC boot partition 1, splits it into RPRCs for each core applicable. Each core is then initialized, RPRC image is loaded, entry points are set and the core is released from reset.

For booting Linux, SBL parses the Linux appimage present in eMMC boot partition, splits it into individual linux binaries (ATF, OPTEE, SPL). SBL loads the Linux binaries, entry point is set to the start address of ATF and A53 core is released from reset.

Refer \ref SBL_BOOTING_LINUX_EMMC for more details on the EMMC bootflow.

Refer \ref ENABLE_DDR_INLINE_ECC enablig inline ECC

# Supported Combinations

\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_emmc_linux_multistage
\endcond

\cond SOC_AM62AX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_emmc_linux_multistage
\endcond

\cond SOC_AM62PX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_emmc_linux_multistage
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

- Create a Linux Appimage containing the **Linux binaries (ATF, OPTEE, A53 SPL)**
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/linuxAppimageGen after setting the PSDK path in file `config.mak`
- Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details

## Create HSM Appimage

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details

## Run the example

- This example is the SBL which needs to be flashed on the eMMC, along with sample application images for R5, M4 CPUs and Linux Appimage.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_emmc_linux.cfg

\cond !SOC_AM62PX
\note Use **default_sbl_emmc_linux_hs.cfg** when flashing to HS-SE devices
\endcond
\note Use **default_sbl_emmc_linux_hs_fs.cfg** when flashing to HS-FS devices
- Make sure IPC rpmsg linux echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO)

\note For IPC rpmsg linux echo, the resource table entity must be placed at the beginning of remoteproc memory section as mentoined in Linux dts file.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_emmc_linux.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Linux Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_emmc_linux.cfg

- If Linux PC is used, assuming SDK is installed at `~PSDK_LINUX_HS_IMAGE_PATH~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER//default_sbl_emmc_linux.cfg

- Boot the EVM in eMMC boot mode to boot Linux on A53 and RTOS/Baremetal application on R5 and M4 cores.

\cond SOC_AM62X
\note The above config file will flash till u-boot on the EMMC bootmedia. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62X/latest/exports/docs/devices/AM62X/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

\cond SOC_AM62AX
\note The above config file will flash till u-boot on the EMMC bootmedia. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62AX/latest/exports/docs/devices/AM62AX/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

\cond SOC_AM62PX
\note The above config file will flash till u-boot on the EMMC bootmedia. U-Boot can load kernel from any bootmedia, refer to \htmllink{https://software-dl.ti.com/processor-sdk-linux/esd/AM62PX/latest/exports/docs/devices/AM62PX/linux/Overview.html, **Processor SDK Linux**} user guide for more details.
\endcond

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)
\cond SOC_AM62X

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 157 KB
    [BOOTLOADER_PROFILE] Cores present    :
    m4f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :       6688us
    [BOOTLOADER PROFILE] Drivers_open                     :      50067us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9928us
    [BOOTLOADER PROFILE] App_loadImages                   :      23087us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      24984us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     114756us

    Image loading done, switching to application ...
    Starting MCU-m4f and 2nd stage bootloader

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 940 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2669us
    [BOOTLOADER PROFILE] Drivers_open                     :      19541us
    [BOOTLOADER PROFILE] Board_driversOpen                :          1us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9975us
    [BOOTLOADER PROFILE] App_loadImages                   :      21374us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      26255us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :      50493us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     130310us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
    NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

    U-Boot SPL 2023.04-ga3595f1e3e (Jun 15 2023 - 08:14:46 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
    SPL initial stack usage: 1856 bytes
    Trying to boot from MMC1
    Authentication passed
    Authentication passed


    U-Boot 2023.04-ga3595f1e3e (Jun 15 2023 - 08:14:46 +0000)

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

\cond SOC_AM62AX
    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 160 KB
    [BOOTLOADER_PROFILE] Cores present    :
    mcu-r5f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      39504us
    [BOOTLOADER PROFILE] Drivers_open                     :      61574us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9895us
    [BOOTLOADER PROFILE] App_loadImages                   :      22280us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      23785us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     157040us

    Image loading done, switching to application ...
    Starting MCU-r5f and 2nd stage bootloader

    SYSFW Version 9.0.5--v09.00.05 (Kool Koala)
    SYSFW revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 1045 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    c75ss0
    [BOOTLOADER PROFILE] System_init                      :       1703us
    [BOOTLOADER PROFILE] Drivers_open                     :      19520us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9909us
    [BOOTLOADER PROFILE] App_loadImages                   :      21214us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      24195us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :      39742us
    [BOOTLOADER PROFILE] App_loadDSPImages                :      24483us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     140769us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.8(release):v2.8-226-g2fcd408bb3-dirty
    NOTICE:  BL31: Built : 00:42:57, Jan 13 2023

    U-Boot SPL 2023.04-g794614311a (Jul 05 2023 - 17:29:58 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.5--v09.00.05 (Kool Koala)')
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

\endcond

\cond SOC_AM62PX

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 139 KB
    [BOOTLOADER_PROFILE] Cores present    :
    wkup-r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      38955us
    [BOOTLOADER PROFILE] Drivers_open                     :          0us
    [BOOTLOADER PROFILE] SBL Drivers_open                 :      19425us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :      35864us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      94246us

    Image loading done, switching to application ...
    Starting 2nd stage bootloader
    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 853 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    mcu-r5f0-0
    a530-0
    [BOOTLOADER PROFILE] System_init                      :       2104us
    [BOOTLOADER PROFILE] Board_init                       :          0us
    [BOOTLOADER PROFILE] FreeRtosTask Create              :        192us
    [BOOTLOADER PROFILE] SciserverInit                    :      15884us
    [BOOTLOADER PROFILE] SBL Drivers_open                 :      14602us
    [BOOTLOADER PROFILE] App_loadImages                   :       3035us
    [BOOTLOADER PROFILE] App_loadMCUImages                :       4730us
    [BOOTLOADER PROFILE] App_loadLinuxImages              :      21217us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      61768us

    Image loading done, switching to application ...
    Starting linux and RTOS/Baremetal applications
    NOTICE:  BL31: v2.9(release):v2.9.0-dirty
    NOTICE:  BL31: Built : 14:12:59, May 22 2023

    U-Boot SPL 2023.04-g48c1296285 (Sep 14 2023 - 21:24:43 +0000)
    SYSFW ABI: 3.1 (firmware rev 0x0009 '9.0.6--w09.00.04-am62p (Kool Ko')
    Trying to boot from MMC1
    Authentication passed
    Authentication passed


    U-Boot 2023.04-g48c1296285 (Sep 14 2023 - 21:24:43 +0000)

    SoC:   AM62PX SR1.0 HS-FS
    Model: Texas Instruments AM62P5 SK
    DRAM:  2 GiB (effective 8 GiB)
    Core:  81 devices, 29 uclasses, devicetree: separate
    MMC:   mmc@fa10000: 0, mmc@fa00000: 1, mmc@fa20000: 2
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

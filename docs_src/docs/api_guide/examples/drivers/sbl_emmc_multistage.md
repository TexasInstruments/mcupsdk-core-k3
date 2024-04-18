# SBL EMMC Multistage{#EXAMPLES_DRIVERS_SBL_EMMC_MULTISTAGE}

\note SBL EMMC RTOS/NORTOS boots from the boot partition 1 of eMMC. The appimage is flashed to the offsets in eMMC as configured using syscfg.
\attention Care should be taken to ensure that the R5, M4 and A53 appimage flashed does NOT overwrite the binaries in eMMC.
\note The load address of resource table for R5,M4 and A53 cores must be consistant with the address.

[TOC]

# Introduction

\cond SOC_AM62AX

This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on R5,M4 and A53 cores from eMMC.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU R5 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and starts running it.

 - The stage2 of the bootloader boots RTOS/NORTOS on A53, C75 and then self loads DM firmware on the DM R5.

The SBL uses 6 appimages
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU R5**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
- Appimage for **A53**
- Appimage for **C75**
\endcond

\cond SOC_AM62X

This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on R5,M4 and A53 cores from eMMC.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and starts running it.

 - The stage2 of the bootloader boots RTOS/NORTOS application on A53 and then self loads DM firmware on the DM R5.

The SBL uses following appimages
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU M4**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
- Appimage for **A53**
\endcond

# Supported Combinations

\cond SOC_AM62AX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_emmc_multistage
\endcond

\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER. @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_emmc_multistage
\endcond

# Steps to Run the Example

## Build the example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Create HSM Appimage

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details

## Run the example

- This example is the SBL which needs to be flashed on the eMMC, along with sample application images for R5, M4 CPUs and A53 Appimage.
\note Use **default_sbl_emmc_hs.cfg** when flashing to HS-SE devices
\note Use **default_sbl_emmc_hs_fs.cfg** when flashing to HS-FS devices
- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_emmc_hs_fs.cfg

- Make sure IPC rpmsg echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_ECHO)

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_emmc_hs.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_emmc_hs_fs.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk/`

        cd ~/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_emmc_hs_fs.cfg

- Boot the EVM in eMMC boot mode to boot RTOS/Baremetal application on R5, M4 and A53 cores.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

\cond SOC_AM62AX

    DMSC Firmware Version 9.1.8--v09.01.08 (Kool Koala)
    DMSC Firmware revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 148 KB
    [BOOTLOADER_PROFILE] Cores present    :
    mcu-r5f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      37940us
    [BOOTLOADER PROFILE] Board_init                       :          0us
    [BOOTLOADER PROFILE] Drivers_open                     :      60669us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9898us
    [BOOTLOADER PROFILE] App_loadImages                   :       5806us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       7259us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :     121574us

    Image loading done, switching to application ...
    Starting MCU-r5f and 2nd stage bootloader

    DMSC Firmware Version 9.1.8--v09.01.08 (Kool Koala)
    DMSC Firmware revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : eMMC
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 311 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    c75ss0
    [BOOTLOADER PROFILE] System_init                      :       1673us
    [BOOTLOADER PROFILE] Board_init                       :          0us
    [BOOTLOADER PROFILE] Drivers_open                     :      19520us
    [BOOTLOADER PROFILE] Board_driversOpen                :          0us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9990us
    [BOOTLOADER PROFILE] App_loadImages                   :       5127us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       7501us
    [BOOTLOADER PROFILE] App_loadA53Images                :       6393us
    [BOOTLOADER PROFILE] App_loadDSPImages                :       6850us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      57060us

    Image loading done, switching to application ...
    Starting RTOS/Baremetal applications
    Hello World!

\endcond

\cond SOC_AM62X
\code
SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
SYSFW Firmware revision 0x9
SYSFW ABI revision 3.1

[BOOTLOADER_PROFILE] Boot Media       : eMMC
[BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
[BOOTLOADER_PROFILE] Boot Image Size  : 139 KB
[BOOTLOADER_PROFILE] Cores present    :
m4f0-0
r5f0-0
[BOOTLOADER PROFILE] System_init                      :       5419us
[BOOTLOADER PROFILE] Board_init                       :          0us
[BOOTLOADER PROFILE] Drivers_open                     :      88487us
[BOOTLOADER PROFILE] Board_driversOpen                :          0us
[BOOTLOADER PROFILE] Sciclient Get Version            :      10203us
[BOOTLOADER PROFILE] App_loadImages                   :       6281us
[BOOTLOADER PROFILE] App_loadSelfcoreImage            :       7955us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :     118348us

Image loading done, switching to application ...
Starting MCU-m4f and 2nd stage bootloader

SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
SYSFW Firmware revision 0x9
SYSFW ABI revision 3.1

[BOOTLOADER_PROFILE] Boot Media       : eMMC
[BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
[BOOTLOADER_PROFILE] Boot Image Size  : 242 KB
[BOOTLOADER_PROFILE] Cores present    :
hsm-m4f0-0
r5f0-0
a530-0
[BOOTLOADER PROFILE] System_init                      :       2700us
[BOOTLOADER PROFILE] Board_init                       :          1us
[BOOTLOADER PROFILE] Drivers_open                     :      19541us
[BOOTLOADER PROFILE] Board_driversOpen                :          1us
[BOOTLOADER PROFILE] Sciclient Get Version            :      10248us
[BOOTLOADER PROFILE] App_loadImages                   :       5522us
[BOOTLOADER PROFILE] App_loadSelfcoreImage            :       8504us
[BOOTLOADER PROFILE] App_loadA53Images                :       7905us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :      54426us

Image loading done, switching to application ...
Starting  RTOS/Baremetal applications
[IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
[IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
All tests have passed!!
\endcode
\endcond
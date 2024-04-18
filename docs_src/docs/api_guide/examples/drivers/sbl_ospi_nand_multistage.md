# SBL OSPI NAND Multistage {#EXAMPLES_DRIVERS_SBL_OSPI_NAND_MULTISTAGE}

\note The load address of resource table for R5, M4 and A53 cores must be consistant with the address.

[TOC]

# Introduction

\cond SOC_AM62AX

This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on DM R5, MCU R5 C75 and A53 cores.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU R5 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and stats running it.

 - The stage2 of the bootloader boots RTOS/NORTOS on A53 and then self loads DM firmware on the DM R5.

The SBL uses 7 appimages
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU R5**
- Appimage for **HSM M4**
- Appimage for **C75**
- DM firmware appimage for **DM R5**
- Appimage for **A53**
\endcond

\cond SOC_AM62X

This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on DM R5, MCU M4 and A53 cores.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR. Then it loads the stage2 of the bootloader to DDR and starts running it.

 - The stage2 of the bootloader boots RTOS/NORTOS on A53 and then self loads DM firmware on the DM R5.

The SBL uses 6 appimages
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
 Example folder | examples/drivers/boot/sbl_ospi_nand_multistage
\endcond

\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_nand_multistage
\endcond

# Steps to Run the Example

## Build the example

Since this is a bootloader, the example will be run every time you boot an application using this example. It is run from a OSPI boot media  unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Refer to the page \ref BASIC_STEPS_TO_FLASH_FILES to flash this bootloader along with the application to boot.

## Create HSM Appimage
\cond SOC_AM62X
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate HSM Appimage for HS-SE device.
\endcond

- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details

## Run the example

\cond SOC_AM62X
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for R5, M4 CPUs and A53 Appimage.

\note For HS-SE device, use **default_sbl_ospi_nand_hs.cfg** as the cfg file.
\note For HS-FS device, use **default_sbl_ospi_nand_hs_fs.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_ospi_nand.cfg

- Make sure IPC rpms echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_ECHO)

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_nand.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and RTOS Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_ospi_nand.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/@VAR_SK_LP_BOARD_NAME_LOWER/default_sbl_ospi_nand.cfg

\endcond

\cond SOC_AM62AX
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for DM R5, MCU R5, C75, HSM M4 CPUs and A53 Appimage.
\note For HS-SE device, use **default_sbl_ospi_nand_hs.cfg** as the cfg file.
\note For HS-FS device, use **default_sbl_ospi_nand_hs_fs.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_nand_hs_fs.cfg

- Make sure IPC rpmsg echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_ECHO)

\note For IPC rpmsg echo, the resource table entity must be placed at the beginning of remoteproc memory section.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_nand_hs_fs.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and RTOS Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_nand_hs_fs.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_nand_hs_fs.cfg
\endcond

- Boot the EVM in OSPI NAND boot mode.

# See Also

\ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

\cond SOC_AM62AX

    DMSC Firmware Version 9.1.8--v09.01.08 (Kool Koala)
    DMSC Firmware revision 0x9
    DMSC ABI revision 3.1

    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 171 KB
    [BOOTLOADER_PROFILE] Cores present    :
    mcu-r5f0-0
    r5f0-0
    [BOOTLOADER PROFILE] System_init                      :      38003us
    [BOOTLOADER PROFILE] Board_init                       :          0us
    [BOOTLOADER PROFILE] Drivers_open                     :        193us
    [BOOTLOADER PROFILE] Board_driversOpen                :         89us
    [BOOTLOADER PROFILE] Sciclient Get Version            :       9909us
    [BOOTLOADER PROFILE] App_loadImages                   :       3680us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       8538us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      60416us

    Image loading done, switching to application ...
    Starting MCU-r5f and 2nd stage bootloader
    [BOOTLOADER_PROFILE] Boot Media       : FLASH
    [BOOTLOADER_PROFILE] Boot Media Clock : 200.000 MHz
    [BOOTLOADER_PROFILE] Boot Image Size  : 311 KB
    [BOOTLOADER_PROFILE] Cores present    :
    hsm-m4f0-0
    r5f0-0
    a530-0
    c75ss0
    [BOOTLOADER PROFILE] System_init                      :       1779us
    [BOOTLOADER PROFILE] Board_init                       :          0us
    [BOOTLOADER PROFILE] Drivers_open                     :        220us
    [BOOTLOADER PROFILE] App_loadImages                   :       2326us
    [BOOTLOADER PROFILE] App_loadSelfcoreImage            :       8543us
    [BOOTLOADER PROFILE] App_loadA53Images                :       5045us
    [BOOTLOADER PROFILE] App_loadDSPImages                :       6790us
    [BOOTLOADER_PROFILE] SBL Total Time Taken             :      24705us

    Image loading done, switching to application ...
    Starting RTOS/Baremetal applications
    Hello World!

\endcond
\cond SOC_AM62X
\code

SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
SYSFW Firmware revision 0x9
SYSFW ABI revision 3.1

[BOOTLOADER_PROFILE] Boot Media       : FLASH
[BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
[BOOTLOADER_PROFILE] Boot Image Size  : 163 KB
[BOOTLOADER_PROFILE] Cores present    :
m4f0-0
r5f0-0
[BOOTLOADER PROFILE] System_init                      :      32999us
[BOOTLOADER PROFILE] Board_init                       :          0us
[BOOTLOADER PROFILE] Drivers_open                     :        204us
[BOOTLOADER PROFILE] Board_driversOpen                :      10588us
[BOOTLOADER PROFILE] Sciclient Get Version            :      10204us
[BOOTLOADER PROFILE] App_waitForMcuPbist              :       1288us
[BOOTLOADER PROFILE] App_waitForMcuLbist              :       7689us
[BOOTLOADER PROFILE] App_loadImages                   :       5749us
[BOOTLOADER PROFILE] App_loadSelfcoreImage            :       3655us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :      72379us

Image loading done, switching to application ...
Starting MCU-m4f and 2nd stage bootloader

SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
SYSFW Firmware revision 0x9
SYSFW ABI revision 3.1

[BOOTLOADER_PROFILE] Boot Media       : FLASH
[BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
[BOOTLOADER_PROFILE] Boot Image Size  : 242 KB
[BOOTLOADER_PROFILE] Cores present    :
hsm-m4f0-0
r5f0-0
a530-0
[BOOTLOADER PROFILE] System_init                      :       2871us
[BOOTLOADER PROFILE] Board_init                       :          1us
[BOOTLOADER PROFILE] Drivers_open                     :        264us
[BOOTLOADER PROFILE] Board_driversOpen                :      47234us
[BOOTLOADER PROFILE] Sciclient Get Version            :      10240us
[BOOTLOADER PROFILE] App_loadImages                   :        580us
[BOOTLOADER PROFILE] App_loadSelfcoreImage            :       5570us
[BOOTLOADER PROFILE] App_loadA53Images                :       2750us
[BOOTLOADER_PROFILE] SBL Total Time Taken             :      69513us

Image loading done, switching to application ...
Starting  RTOS/Baremetal applications
[IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
[IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
All tests have passed!!
\endcode
\endcond
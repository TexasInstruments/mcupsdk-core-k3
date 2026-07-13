# SBL EMMC {#EXAMPLES_DRIVERS_SBL_EMMC}

[TOC]

# Introduction

\cond SOC_AM275X

This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on R5, C7x and HSM cores.

The booting is done in single stage
 - The stage is multithreaded with one thread runs the sciServer and the other thread runs the SBL which boots the RTOS/NORTOS applications to R5/C7x/HSM cores

SBL reads the CANUART_WAKE_STAT1 MMR in wakeup control MMR to detect partial IO (or IO retention) mode exit. If exit is detected, then SBL will save the wake reason, that is the pad number that triggered the wakeup in BACKUP MMR0 of wakeup control MMR and clear isolation from the pins. Then, it continues the boot.

The SBL uses 5 appimages
- tiboot3.bin with **SBL, TIFS, BoardConfig**
- mcelf for **R5**
- mcelf for **C7x**
- mcelf for **HSM**
\endcond

# Supported Combinations

\cond SOC_AM275X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup_r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          |  @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_emmc

\attention While using device variants, please remove the cores that are not present on the device from the **BOOTLOADER** section of the example Syscfg
\imageStyle{sbl_emmc_syscfg_subparts.png,width:45%}
\image html sbl_emmc_syscfg_subparts.png

\endcond

# Steps to Run the Example

## Build the example

Since this is a bootloader, the example will be run every time you boot an application using this example. It is run from a eMMC boot media  unlike other examples which are usually loaded with CCS. Nevertheless, you can build this example like you do for the others using makefile or build it via CCS by importing as a project.

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Refer to the page \ref BASIC_STEPS_TO_FLASH_FILES to flash this bootloader along with the application to boot.

## Create HSM Appimage
\cond SOC_AM275X
\note Change DEVICE_TYPE to HS in ${SDK_INSTALL_PATH}/devconfig/devconfig.mak and then generate HSM Appimage for HS-SE device.
\endcond

\cond SOC_AM275X
- Create a HSM MCELF Image
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMMCELFImageGen
- Refer \ref HSM_MCELF_IMAGE_GEN_TOOL for more details
\endcond

\cond !SOC_AM275X
- Create a HSM Appimage
- This can be done by running the makefile at {SDK_INSTALL_PATH}/tools/boot/HSMAppimageGen
- Refer \ref HSM_APPIMAGE_GEN_TOOL for more details
\endcond

## Run the example

\cond SOC_AM275X
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for R5, C7x and HSM.

\note For HS-SE device, use **sbl_emmc_hs.cfg** as the cfg file.
\note For HS-FS device, use **sbl_emmc_hs_fs.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/sbl_emmc_hs_fs.cfg

- Make sure IPC rpms echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_ECHO)

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `sbl_emmc_hs_fs.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example and IPC application is built using makefiles, and RTOS Appimage is already created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/sbl_emmc_hs_fs.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/@VAR_BOARD_NAME_LOWER/sbl_emmc_hs_fs.cfg

\endcond

- Boot the EVM in eMMC boot mode.

# See Also

- \ref DRIVERS_BOOTLOADER_PAGE

# Sample Output

After flashing and booting the EVM, you will see below output on the UART console (Complete log is not shown)

\cond SOC_AM275X
\code

Sciserver Testapp Built On: Nov 29 2024 18:43:49
Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
RM_PM_HAL Version: vMM.NN.PP
Starting Sciserver..... PASSED

Starting EMMC Bootloader ...

SYSFW Firmware Version 10.0.8--w2024.02-am275x (Fiery
SYSFW Firmware revision 0xa
SYSFW ABI revision 4.0

[KPI] Boot Media       : EMMC
[KPI] Boot Media Clock : 166.667 MHz
[KPI] Boot Image Size  : 457 KB
[KPI] Cores present    :
[KPI] TIFS init                        :        722us
[KPI] System_init                      :       1801us
[KPI] Board_init                       :          2us
[KPI] FreeRtosTask Create              :        255us
[KPI] Drivers_open                     :         97us
[KPI] Board_driversOpen                :          0us
[KPI] sciServer_init                   :      15043us
[KPI] SBL Drivers_open                 :       3052us
[KPI] SBL Board_driversOpen            :         94us
[KPI] Sciclient Get Version            :      10187us
[KPI] DSP 0 Image Load                 :      11551us
[KPI] DSP 1 Image Load                 :      11521us
[KPI] R5FSS0_0 Image Load              :       5941us
[KPI] R5FSS0_1 Image Load              :       5807us
[KPI] R5FSS1_0 Image Load              :       5819us
[KPI] R5FSS1_1 Image Load              :       5805us
[KPI] SBL Total Time Taken             :      77703us

Image loading done...
Starting RTOS/Baremetal applications

[IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
[IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
All tests have passed!!

\endcode
\endcond

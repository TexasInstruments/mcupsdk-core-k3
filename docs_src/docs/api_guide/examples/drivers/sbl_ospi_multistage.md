# SBL OSPI  Multistage {#EXAMPLES_DRIVERS_SBL_OSPI_MULTISTAGE}

\note The load address of resource table for R5, M4 and A53 cores must be consistant with the address.

[TOC]

# Introduction

\cond SOC_AM62X

This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on DM R5, MCU M4 and A53 cores.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It boots MCU M4 with RTOS/NORTOS application and initializes the DDR.
 - The stage2 of the bootloader is then loaded to the BTCM and DDR. The boot vectors are loaded at BTCM.
 - The core is then reset to boot from BTCM.
 - ATCM is enabled to load images in the next stage.

 - The stage2 of the bootloader boots Linux on A53 and then self loads DM firmware on the DM R5.
 - DM R5 image is loaded with some sections in the ATCM and the rest in DDR by stage 2 of the bootloader.

The SBL uses 6 appimages
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU M4**
- Appimage for **HSM M4**
- DM firmware appimage for **DM R5**
- Appimage for **A53**
\endcond

\cond SOC_AM62DX

This is a bootloader example, which shows an example of booting  RTOS/NORTOS applications on WKUP R5F, MCU R5F, C7X and A53 cores.

The booting is done in 2 stages(2 bootloader applications).
 - The stage1 of the bootloader runs from the HSM RAM. It initialized DDR, and runs LBIST for MCU R5F core in parallele to DDR intialitation.  Then it loads the stage2 of the bootloader to DDR and starts running it.
 In this stage, SBL reads the CANUART_WAKE_STAT1 MMR in wakeup control MMR to detect partial IO (or IO retention) mode exit. If exit is detected, then SBL will save the wake reason, that is the pad number that triggered the wakeup in BACKUP MMR0 of wakeup control MMR and clear isolation from the pins. Then, it continues the boot.

 - The stage2 of the bootloader integrated along with DM. DM runs on a seperate thread. In parallel, bootloader operation executed in a different thread. Stage2 boots RTOS/NORTOS on A53, MCU R5F, C7x and HSM M4F. Stage2 also perfoms PBIST on MCU R5F before booting the

\note After enabling MCU LBIST on SBL, we will not be able to connect to MCU R5F core through JTAG. This is a known issue will be fixed in the futre release. Disable LBIST on SBL Stage2 to avoid this.

The SBL uses 6 appimages
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **MCU R5F**
- Appimage for **HSM M4**
- Appimage for **C7x**
- Appimage for **A53**
\endcond

\cond SOC_J722S

This is a bootloader example, which shows an example of booting RTOS/NORTOS applications on WKUP R5F, MAIN R5F, C7x DSP, A53 and HSM cores.

The booting is done in 2 stages (2 bootloader applications).

- The stage1 of the bootloader runs on WKUP R5F from internal SRAM. It loads TIFS and BoardConfig, initializes clocks and DDR, and can boot application images on WKUP R5F, MAIN R5F, C7x DSP and A53 cores.

- The stage2 of the bootloader is then loaded to the WKUP R5F ATCM/BTCM and DDR. The boot vectors are configured in ATCM/BTCM.

- The core continues execution from ATCM/BTCM with DDR enabled.

- The stage2 of the bootloader boots Linux on A53 (if used) and loads application images on MAIN R5F, C7x DSP and HSM cores.

- Stage2 supports booting all non-self cores. Booting WKUP R5F from stage2 is not supported since stage2 executes on the WKUP R5F core.

- Core images may have sections placed in ATCM/BTCM and remaining sections placed in DDR by stage2.

The SBL uses multiple appimages
- tiboot3.bin with **SBL stage1, TIFS, BoardConfig**
- Appimage for **SBL stage2**
- Appimage for **WKUP R5F**
- Appimage for **MAIN R5F**
- Appimage for **MCU R5F**
- Appimage for **C7x DSP**
- Appimage for **A53**

\endcond

\cond !SOC_J722S
\note
The default appimages in the SDK are built with authentication type 0  and load address 0x84000000. The gAppimage section in the bootloader application also has to be linked to the same address (0x84000000). If gAppimage section address is changed or multiple gAppimage buffers are used in the bootloader application, please ensure application's makefile is also updated with the corresponding load address.
\endcond

\cond SOC_J722S
\note
The default appimages in the SDK are built with authentication type 0  and load address 0xC2000000. The gAppimage section in the bootloader application also has to be linked to the same address (0xC2000000). If gAppimage section address is changed or multiple gAppimage buffers are used in the bootloader application, please ensure application's makefile is also updated with the corresponding load address.
\endcond

# Supported Combinations

\cond SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          |  @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_multistage
\endcond

\cond SOC_J722S
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/boot/sbl_ospi_multistage
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

\note For HS-SE device, use **default_sbl_ospi_hs.cfg** as the cfg file.
\note For HS-FS device, use **default_sbl_ospi_hs_fs.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_hs_fs.cfg

- Make sure IPC rpms echo application is built before running the flash script. (see \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_ECHO)

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving the flash config file, point to the `default_sbl_ospi_hs_fs.cfg` shown above.

- Example, assuming SDK is installed at `${SDK_INSTALL_PATH}` and this example and IPC application is built using makefiles, and RTOS Appimage is already created, in Windows,

        cd ${SDK_INSTALL_PATH}
        python uart_uniflash.py -p COM13 --cfg=${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_hs_fs.cfg

- If Linux PC is used, assuming SDK is installed at `${SDK_INSTALL_PATH}`

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_hs_fs.cfg

\endcond

\cond SOC_J722S
- This example is the SBL which needs to be flashed on the EVM flash, along with sample application images for MAIN R5F, C7x, A53 cores using the hello_world example.

\note IPC RPMessage example is not used in this case since it requires WKUP R5F participation, which is not supported when booting from Stage2.

\note For HS-SE device, use **default_sbl_ospi_hs.cfg** as the cfg file.
\note For HS-FS device, use **default_sbl_ospi_hs_fs.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the hello_world application images:

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_hs_fs.cfg

- Make sure the hello_world application for the required cores is built before running the flash script.

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH. When providing the flash config file, point to the `default_sbl_ospi_hs_fs.cfg` shown above.

- Example, assuming SDK is installed at `${SDK_INSTALL_PATH}` and this example and hello_world application are built using makefiles, and the RTOS Appimage is already created, in Windows:

        cd ${SDK_INSTALL_PATH}
        python uart_uniflash.py -p COM13 --cfg=${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_hs_fs.cfg

- If Linux PC is used, assuming SDK is installed at `${SDK_INSTALL_PATH}`:

        cd ${SDK_INSTALL_PATH}/tools/boot
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_hs_fs.cfg

\endcond

- Boot the EVM in OSPI NOR boot mode.

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
\code

SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
SYSFW Firmware revision 0x9
SYSFW ABI revision 3.1

[KPI] Boot Media       : FLASH
[KPI] Boot Media Clock : 166.667 MHz
[KPI] Boot Image Size  : 165 KB
[KPI] Cores present    :
m4f0-0
r5f0-0
[KPI] System_init                      :      23124us
[KPI] Board_init                       :          0us
[KPI] Drivers_open                     :        295us
[KPI] Board_driversOpen                :       6786us
[KPI] Sciclient Get Version            :      10204us
[KPI] App_waitForMcuPbist              :       4990us
[KPI] App_waitForMcuLbist              :       7689us
[KPI] App_loadImages                   :       3262us
[KPI] App_loadSelfcoreImage            :       3972us
[KPI] SBL Total Time Taken             :      60326us

Image loading done, switching to application ...
Starting MCU-m4f and 2nd stage bootloader

SYSFW Firmware Version 9.2.7--v09.02.07 (Kool Koala)
SYSFW Firmware revision 0x9
SYSFW ABI revision 3.1

[KPI] Boot Media       : FLASH
[KPI] Boot Media Clock : 166.667 MHz
[KPI] Boot Image Size  : 242 KB
[KPI] Cores present    :
hsm-m4f0-0
r5f0-0
a530-0
[KPI] System_init                      :       2812us
[KPI] Board_init                       :          0us
[KPI] Drivers_open                     :        361us
[KPI] Board_driversOpen                :      28043us
[KPI] Sciclient Get Version            :      10265us
[KPI] App_loadImages                   :       2680us
[KPI] App_loadSelfcoreImage            :       4064us
[KPI] App_loadA53Images                :       3675us
[KPI] SBL Total Time Taken             :      51904us

Image loading done, switching to application ...
Starting RTOS/Baremetal applications
[IPC RPMSG ECHO] Remote Core waiting for messages from main core ... !!!
[IPC RPMSG ECHO] Received and echoed 10 messages ... !!!
All tests have passed!!

\endcode
\endcond

\cond SOC_J722S
\code

INFO: Bootloader_loadSelfCpu:127: CPU wkup-r5f is initialized to 800000000 Hz !!!
[KPI] Boot Media       : FLASH
[KPI] Boot Media Clock : 166.667 MHz
[KPI] Boot Image Size  : 170 KB
[KPI] Cores present    :
wkup-r5f0-0
[KPI] System_init                      :      35452us
[KPI] Board_init                       :          0us
[KPI] Drivers_open                     :        146us
[KPI] Board_driversOpen                :       9736us
[KPI] App_loadSelfcoreImage            :      13054us
[KPI] SBL Total Time Taken             :      58391us

Image loading done, switching to application ...
Starting 2nd stage bootloader
Sciserver Testapp Built On: Feb 18 2026 12:26:58
Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
RM_PM_HAL Version: vMM.NN.PP
Starting Sciserver..... PASSED
[KPI] Boot Media       : FLASH
[KPI] Boot Media Clock : 166.667 MHz
[KPI] Boot Image Size  : 39 KB
[KPI] Cores present    :
main-r5f0-0
[KPI] System_init                      :       2657us
[KPI] Board_init                       :          3us
[KPI] FreeRTOS Task Created            :        258us
[KPI] SBL Drivers_open                 :      25862us
[KPI] SBL Board_driversOpen            :       9854us
[KPI] App_loadImages                   :       4553us
[KPI] SBL Total Time Taken             :      43188us

Image loading done, switching to application ...
Starting RTOS/Baremetal applications
Hello World!
\endcode
\endcond
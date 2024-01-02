# DSS Display Share {#EXAMPLES_DRIVERS_DSS_DISPLAY_SHARE}

[TOC]
# Introduction

Display subsystem supports sharing of display between multiple hosts as it
provides separate register space (common* region) for each host to programming
display controller and also an unique interrupt line for each host. HLOS like
Linux owns one or more of the video planes with video port (along with
corresponding overlay manager) associated with these planes being owned and
controlled by a remote core.

This example shares the DSS with high level OS like linux. The example uses one
DSS pipeline (VIDL) and keeps the other pipeline for HLOS (VID).

The example uses DSS0 instance with VIDL pipeline, OVR1 overlay and VP1
videoport. The overlay manager is configured with Zorder 1 for VID pipeline and
Zorder 2 for VIDL pipeline. The example acts as master for controlling DSS and
expects linux to use VID pipeline. The VID and VIDL pipeline are overlayed
together as per mentioned zorder above.

The Display sharing feature can be enabled by using below shown sysconfig
option.

\image html docs_src/docs/api_guide/images/examples/dss_display_share.png

The example integrates early splash of image along with SBL on OSPI bootmedia,
Device Manager and Interprocessor communication functionality. The bootloader
IPC and Display run on separate tasks. The Display task displays a splash image
with alpha blending and finally switches to display sharing task, where it ping
pongs tell tale frames. The SBL stage 2 thread boots all the cores along with
HLOS like Linux. Refer \ref SBL_BOOTING_LINUX_OSPI for boot flow sequence.

The example configures OLDI LVDS panel for Video Port 1. Please refer
<a href="https://www.ti.com/tool/SK-LCD1">**SK-LCD1**</a> for panel details. The
Video port timinng parameters are configured with respect to
<a href="https://www.ti.com/tool/SK-LCD1">**SK-LCD1**</a>. Timing parameters can
be configured using sysconfig option.

\note To support display sharing on Linux, there exists a device tree overlay which
should be applied to kernel device tree to enable DSS sharing on Linux.
The overlays are **k3-am62p5-sk-microtips-mf101hie-panel.dtbo** and
**k3-am62p5-sk-dss-shared-mode.dtbo**. Use
**tisdk-display-cluster-image-am62pxx-evm.wic.xz** image to flash linux root
file system. This default wic image launches Cluster demo as shown in display
output below. Please refer Processor SDK Linux documentation for more details.

# Supported Combinations {#EXAMPLES_DRIVERS_DSS_DISPLAY_SHARE_COMBOS}

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/dss/dss_display_share

\endcond

# Steps to Run the Example

- This example integrates SBL on OSPI bootmedia which needs to be flashed on the
EVM flash, along with sample application images for MCU R5 CPUs, HSM M4F and
Linux Appimage.

- For HS-FS device, use **default_sbl_ospi_linux_hs_fs_splash_screen.cfg** as the cfg file.

- There is a default flash config file as shown below which flashes this SBL and the display share application

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux_hs_fs_splash_screen.cfg

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving
the flash config file, point to the `default_sbl_ospi_linux_hs_fs_splash_screen.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example
and IPC application is built using makefiles, and Linux Appimage is already
created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux_hs_fs_splash_screen.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux_hs_fs_splash_screen.cfg

- Switch to \ref BOOTMODE_OSPI and power on the EVM.

\attention As the wake-up R5 is the device manager, it needs to be started by
the SBL. So it can not be loaded through CCS. It should be flashed and booted
through SBL.

# See Also

\ref DRIVERS_DSS_PAGE

# Sample Output
\code
Sciserver Testapp Built On: Dec  7 2023 14:12:00
Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
RM_PM_HAL Version: vMM.NN.PP
Starting Sciserver..... PASSED
[IPC RPMSG ECHO] Version: REL.MCUSDK.MM.NN.PP.bb (Dec  7 2023 14:12:16):
DispApp_init() - DONE !!!
DSS display share application started...
Display create complete!!
Starting display ... !!!
Display in progress ... DO NOT HALT !!!
DSS display share Passed!!
Number of elapsed frames = 300, elapsed msec = 4999, fps = 60.01
[IPC RPMSG ECHO] Message exchange started with RTOS cores !!!
[IPC RPMSG ECHO] Remote Core waiting for messages at end point 13 ... !!!
[IPC RPMSG ECHO] Remote Core waiting for messages at end point 14 ... !!!
Number of elapsed frames = 300, elapsed msec = 5010, fps = 59.88
[IPC RPMSG ECHO] All echoed messages received by main core from 1 remote cores !!!
[IPC RPMSG ECHO] Messages sent to each core = 100000
[IPC RPMSG ECHO] Number of remote cores = 1
[IPC RPMSG ECHO] Total execution time = 3591085 usecs
[IPC RPMSG ECHO] One way message latency = 17955 nsec
Number of elapsed frames = 300, elapsed msec = 5011, fps = 59.87
Number of elapsed frames = 300, elapsed msec = 5011, fps = 59.87
\endcode

**Display Output**
\image html docs_src/docs/api_guide/images/examples/dss_display_share_output.png width=50%

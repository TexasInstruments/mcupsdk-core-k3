# DSS Safety Test {#EXAMPLES_DRIVERS_DSS_SAFETY_TEST}

[TOC]
# Introduction

This example tests the Freeze frame detection and Data integrity check safety
features for video pipeline and video port. DSS supports the following safety
check regions to implement the safety features:\

- Video pipelines: One safety check region at the output of each video
pipeline.
- Video port outputs: Up to four sub-regions within the active video output
area of the final display output of each video port.


The safety region in the video pipeline captures data only if the embedded alpha
data is not equal to 0 (that is, non-transparent pixels). The safety regions in
the display video port output captures all active video pixels within the region
boundary. The (up to four) regions in the display output should be typically
non-overlapping areas of the screen, but the hardware does not restrict them to
be non-overlapping.

The example configures freeze frame detection for two regions and data integrity
check for rest of the two regions on Video port. The example also configures
freeze frame detect for VID pipeline and data integrity check for VIDL piepline.
The data integrity check failure is created by corruting frame buffer so that
previous frame buffer is different from current frame buffer.

Safety region configurations are available as part of driver sysconfig feature
shown below.

**Video Port Safety Region**
\image html docs_src/docs/api_guide/images/drivers/VpSafety.png
**Video Pipeline Safety Region**
\image html docs_src/docs/api_guide/images/drivers/VIDandVIDLsafety.png


The example configures OLDI LVDS panel for Video Port 1. Please refer
<a href="https://www.ti.com/tool/SK-LCD1">**SK-LCD1**</a> for panel details. The
Video port timinng parameters are configured with respect to
<a href="https://www.ti.com/tool/SK-LCD1">**SK-LCD1**</a>. Timing parameters can
be configured using sysconfig option.

The example integrates bootloading funtionality with SBL on OSPI bootmedia. It
also integrates Device manager functionality. The SBL stage 2 thread boots all
the cores along with HLOS like Linux. Refer \ref SBL_BOOTING_LINUX_OSPI for boot
flow sequence.

# Supported Combinations {#EXAMPLES_DRIVERS_DSS_SAFETY_TEST_COMBOS}

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/dss/dss_safety_test

\endcond

# Steps to Run the Example

- This example integrates SBL on OSPI bootmedia which needs to be flashed on the
EVM flash, along with sample application images for MCU R5 CPUs, HSM M4F and
Linux Appimage.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux_hs_fs.cfg

- Update the wkup-r5 image in the flash config with dss_safety_test image.

        # 2nd stage bootloader with DM is flashed at 0x80000 or to whatever offset your bootloader is configured for
        --file=../../examples/drivers/dss/dss_safety_test/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/dss_safety_test.release.appimage.hs_fs --operation=flash --flash-offset=0x80000

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH . Only when giving
the flash config file, point to the `default_sbl_ospi_linux_hs_fs.cfg` shown above.

- Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example
and IPC application is built using makefiles, and Linux Appimage is already
created, in Windows,

        cd C:/ti/mcu_plus_sdk/tools/boot
        python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux_hs_fs.cfg

- If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

        cd ~/ti/mcu_plus_sdk
        python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux_hs_fs.cfg

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
DispApp_init() - DONE !!!
DSS display application started...
Display create complete!!
Starting display ... !!!
Display in progress ... DO NOT HALT !!!
Underflow did not occur
Underflow did not occur
Sync Lost did not occur
Display delete complete!!
DispApp_deInit() - DONE !!!
****************************************************
Safety Data Log Region : 0
Safety Data VP ID: VP1
Safety Check Interupt Trigger: TRUE
Safety Check Mode: FRAME_FREEZE_DETECT
Safety Data Frame count: 13
Safety Data Captured Signature: 0xCCFA10E0
****************************************************
Safety Data Log Region : 1
Safety Data VP ID: VP1
Safety Check Interupt Trigger: TRUE
Safety Check Mode: FRAME_FREEZE_DETECT
Safety Data Frame count: 33
Safety Data Captured Signature: 0x7FE99F52
****************************************************
Safety Data Log Region : 2
Safety Data VP ID: VP1
Safety Check Interupt Trigger: TRUE
Safety Check Mode: DATA_INTEGRITY
Safety Data Frame count: 73
Safety Data Captured Signature: 0x5576A020
****************************************************
Safety Data Log Region : 3
Safety Data VP ID: VP1
Safety Check Interupt Trigger: TRUE
Safety Check Mode: DATA_INTEGRITY
Safety Data Frame count: 73
Safety Data Captured Signature: 0xCD822043
****************************************************
Safety Data Pipeline ID: VID1
Safety Check Interupt Trigger: TRUE
Safety Check Mode: FRAME_FREEZE_DETECT
Safety Data Frame count: 53
Safety Data Captured Signature: 0xF6BA4989
****************************************************
Safety Data Pipeline ID: VIDL1
Safety Check Interupt Trigger: TRUE
Safety Check Mode: DATA_INTEGRITY
Safety Data Frame count: 73
Safety Data Captured Signature: 0xC948AD61
DSS Safety Test Passed!!
\endcode

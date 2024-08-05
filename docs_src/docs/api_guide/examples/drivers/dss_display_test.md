# DSS Display Test {#EXAMPLES_DRIVERS_DSS_DISPLAY_TEST}

[TOC]
# Introduction

This example tests the complete video pipeline configuration of DSS and displays
it on a video port. DSS includes two video pipelines:
    - Video pipeline (VID)
    - Video lite pipeline (VIDL1)

The example allocates frame buffers and prepares test pattern for frame buffers
for both pipelines in DDR. The example configures both the pipelines VID and
VIDL for different attributes like input frame format, scaling, global alpha,
and more. The mentioned VID and VIDL configurations are done as part of DSS
driver sysconfig options shown below.

\image html docs_src/docs/api_guide/images/drivers/VIDandVIDLconfig.png


The example generates test pattern for both pipelines based on the frame format
selected. The supported frame formats are RGB 16-bit, RGB 32-bit, RGB 64-bit,
RGB 24-bit and YUV formats.

The example configures Zorder for overlay manager where VID and VIDL pipelines
have Zorder 1 and 2 respectively. The Zorder can be changed using sysconfig
option. The example configures scaling by default for VID pipeline. The VIDL
pipeline does not support scaling for input frames.

The example configures DPI Panel for Video Port 2. It sets the video timing
parameters for DPI output interface. The example also adds a Panel driver that
configures a Sii9022a bridge driver for DPI to HDMI output on AM62P-SK
board.

The example integrates bootloading funtionality with SBL on OSPI bootmedia. It
also integrates Device manager functionality. The SBL stage 2 thread boots all
the cores along with HLOS like Linux. Refer \ref SBL_BOOTING_LINUX_OSPI for boot
flow sequence.

# Supported Combinations {#EXAMPLES_DRIVERS_DSS_DISPLAY_TEST_COMBOS}

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/dss/dss_display_test

\endcond

# Steps to Run the Example

- This example integrates SBL on OSPI bootmedia which needs to be flashed on the
EVM flash, along with sample application images for MCU R5 CPUs, HSM M4F and
Linux Appimage.

- There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

        ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/@VAR_BOARD_NAME_LOWER/default_sbl_ospi_linux_hs_fs.cfg

- Update the wkup-r5 image in the flash config with dss_display_test image.

        # 2nd stage bootloader with DM is flashed at 0x80000 or to whatever offset your bootloader is configured for
        --file=../../examples/drivers/dss/dss_display_test/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/dss_display_test.release.appimage.hs_fs --operation=flash --flash-offset=0x80000

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
Number of frames = 300, elapsed msec = 5032, fps = 59.62
DispApp_deInit() - DONE !!!
DSS display test Passed!!
\endcode

**Display Output**
\image html docs_src/docs/api_guide/images/examples/dss_display_test_output.png width=50%

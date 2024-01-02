# MCASP Early Chime {#EXAMPLES_DRIVERS_MCASP_EARLY_CHIME}

[TOC]

# Introduction

This example demonstrates early audio chime from stage 2 sbl with DM.
A headset needs to be connected to the audio jack on @VAR_BOARD_NAME_LOWER for hearing the audio.

- Mcasp is configured in I2S mode
- Audio chime is played on both channels (Left and Right)

The example integrates bootloading funtionality with SBL on OSPI bootmedia. It
also integrates Device manager functionality. The SBL stage 2 thread boots all
the cores along with HLOS like Linux. Refer \ref SBL_BOOTING_LINUX_OSPI for boot
flow sequence.

# Supported Combinations {#EXAMPLES_DRIVERS_MCASP_EARLY_CHIME_COMBOS}

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcasp/mcasp_early_chime

\endcond
# Steps to Run the Example

\cond !SOC_AM62PX
- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\endcond

\cond SOC_AM62PX

- This example integrates SBL on OSPI bootmedia which needs to be flashed on the
EVM flash, along with sample application images for MCU R5 CPUs, HSM M4F and
Linux Appimage.

- For HS-FS device, use **default_sbl_ospi_linux_hs_fs.cfg** as the cfg file.

- Update the wkup-r5 image in the flash config with mcasp_early_chime image.


        # 2nd stage bootloader with DM is flashed at 0x80000 or to whatever offset your bootloader is configured for
        --file=../../examples/drivers/mcasp/mcasp_early_chime/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/mcasp_early_chime.release.appimage.hs_fs --operation=flash --flash-offset=0x80000

- To flash to the EVM, refer to \ref GETTING_STARTED_FLASH .

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
\endcond

# See Also

\ref DRIVERS_MCASP_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Starting Chime
Chime completed
\endcode

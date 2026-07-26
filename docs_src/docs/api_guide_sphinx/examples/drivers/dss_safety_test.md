# DSS Safety Test
## Introduction

This example tests the Freeze frame detection and Data integrity check safety
features for video pipeline and video port. DSS supports the following safety
check regions to implement the safety features:

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
check for rest of the two regions on Video port. The example also configures data integrity check for VIDL piepline. The data integrity check failure is created by corruting frame buffer so that previous frame buffer is different from current frame buffer.

Safety region configurations are available as part of driver sysconfig feature
shown below.

```{figure} ../../images/drivers/VpSafety.png
:align: center

**Video Port Safety Region**
```

```{figure} ../../images/drivers/VIDandVIDLsafety.png
:align: center

**Video Pipeline Safety Region**
```


::::{only} SOC_AM62X or SOC_AM62PX
   The example configures OLDI LVDS panel for Video Port 1. Please refer
   <a href="https://www.ti.com/tool/SK-LCD1">**SK-LCD1**</a> for panel details. The
   Video port timinng parameters are configured with respect to
   <a href="https://www.ti.com/tool/SK-LCD1">**SK-LCD1**</a>. Timing parameters can
   be configured using sysconfig option.
::::


::::{only} SOC_AM62PX
   The example integrates bootloading funtionality with SBL on OSPI bootmedia. It
   also integrates Device manager functionality. The SBL stage 2 thread boots all
   the cores along with HLOS like Linux. Refer [SBL Booting Linux From OSPI](../../developer_guides/sbl_booting_linux_ospi.md) for boot
   flow sequence.
::::


## Supported Combinations
::::{only} SOC_AM62PX

   | Parameter      | Value                              |
|---|---|
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/dss/dss_safety_test |

::::


::::{only} SOC_AM62X

   | Parameter      | Value                                                                         |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/dss/dss_safety_test |

::::


::::{only} SOC_AM62LX

   | Parameter      | Value                              |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/dss/dss_safety_test |

::::


## Steps to Run the Example


::::{only} SOC_AM62LX
   - **When using CCS projects to build**, import the CCS project for the required combination
     and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
   - **When using makefiles to build**, note the required combination and build using
     make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM62X
   - **When using CCS projects to build**, import the CCS project for the required combination
     and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
   - **When using makefiles to build**, note the required combination and build using
     make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

   :::{only} SOC_AM62X
      :::{admonition} Attention
      As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
      :::


      - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
   :::

::::


::::{only} SOC_AM62PX
   - This example integrates SBL on OSPI bootmedia which needs to be flashed on the
   EVM flash, along with sample application images for MCU R5 CPUs, HSM M4F and
   Linux Appimage.

   - There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

           ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_linux_hs_fs.cfg

   - Update the wkup-r5 image in the flash config with dss_safety_test image.

           # 2nd stage bootloader with DM is flashed at 0x80000 or to whatever offset your bootloader is configured for
           --file=../../examples/drivers/dss/dss_safety_test/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/dss_safety_test.release.appimage.hs_fs --operation=flash --flash-offset=0x80000

   - To flash to the EVM, refer to [Flash a Hello World example](../../getting_started/getting_started_flash.md) . Only when giving
   the flash config file, point to the `default_sbl_ospi_linux_hs_fs.cfg` shown above.

   - Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example
   and IPC application is built using makefiles, and Linux Appimage is already
   created, in Windows,

           cd C:/ti/mcu_plus_sdk/tools/boot
           python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_linux_hs_fs.cfg

   - If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

           cd ~/ti/mcu_plus_sdk
           python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_linux_hs_fs.cfg

   - Switch to [OSPI NOR BOOT MODE](../../getting_started/am62px_evm_setup.md) and power on the EVM.

   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


## See Also

[DSS](../../components/drivers/dss.md)

## Sample Output


::::{only} SOC_AM62LX

```
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
```

::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S

```
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
```

::::


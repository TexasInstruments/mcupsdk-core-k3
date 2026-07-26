# DSS Display Test
## Introduction


::::{only} SOC_AM62LX
   This example tests the complete video pipeline configuration of DSS and displays
   it on a video port. DSS includes one video pipelines:
       - Video lite pipeline (VIDL1)

   The example allocates frame buffers and prepares test pattern for frame buffers
   for VIDL pipeline in DDR. The example configures VIDL pipeline for different attributes like input frame format, frame size and more. The mentioned VIDL configurations are done as part of DSS driver sysconfig options shown below.

::::


::::{only} SOC_AM62X or SOC_AM62PX
   This example tests the complete video pipeline configuration of DSS and displays
   it on a video port. DSS includes two video pipelines:
       - Video pipeline (VID)
       - Video lite pipeline (VIDL1)

   The example allocates frame buffers and prepares test pattern for frame buffers
   for both pipelines in DDR. The example configures both the pipelines VID and
   VIDL for different attributes like input frame format, scaling, global alpha,
   and more. The mentioned VID and VIDL configurations are done as part of DSS
   driver sysconfig options shown below.

::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S

```{figure} ../../images/drivers/VIDandVIDLconfig.png
:align: center

**VID and VIDL Configuration**
```

::::


::::{only} SOC_AM62LX

```{figure} ../../images/drivers/VIDLConfig.png
:align: center

**VIDL Configuration**
```

::::


The example generates test pattern for both pipelines based on the frame format
selected. The supported frame formats are RGB 16-bit, RGB 32-bit, RGB 64-bit,
RGB 24-bit and YUV formats.


::::{only} SOC_AM62X or SOC_AM62PX
   The example configures Zorder for overlay manager where VID and VIDL pipelines
   have Zorder 1 and 2 respectively. The Zorder can be changed using sysconfig
   option. The example configures scaling by default for VID pipeline. The VIDL
   pipeline does not support scaling for input frames.

   The example configures DPI Panel for Video Port 2. It sets the video timing
   parameters for DPI output interface. The example also adds a Panel driver that
   configures a Sii9022a bridge driver for DPI to HDMI output on board.

::::


::::{only} SOC_AM62LX
   The example configures DPI Panel for Video Port 1. It sets the video timing
   parameters for DPI output interface. The example also adds a Panel driver that
   configures a Sii9022a bridge driver for DPI to HDMI output on board.

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
| Example folder | examples/drivers/dss/dss_display_test |

::::


::::{only} SOC_AM62X

   | Parameter      | Value                                                                         |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/dss/dss_display_test |

::::


::::{only} SOC_AM62LX

   | Parameter      | Value                              |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/dss/dss_display_test |

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

   ::::{only} SOC_AM62X
      :::{admonition} Attention
      As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
      :::


      - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
   ::::

::::


::::{only} SOC_AM62PX
   - This example integrates SBL on OSPI bootmedia which needs to be flashed on the
   EVM flash, along with sample application images for MCU R5 CPUs, HSM M4F and
   Linux Appimage.

   - There is a default flash config file as shown below which flashes this SBL and the IPC RPMsg Linux echo applications

           ${SDK_INSTALL_PATH}/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_linux_hs_fs.cfg

   - Update the wkup-r5 image in the flash config with dss_display_test image.

           # 2nd stage bootloader with DM is flashed at 0x80000 or to whatever offset your bootloader is configured for
           --file=../../examples/drivers/dss/dss_display_test/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/dss_display_test.release.appimage.hs_fs --operation=flash --flash-offset=0x80000

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

::::

## See Also

[DSS](../../components/drivers/dss.md)

## Sample Output

::::{only} SOC_AM62X

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
Number of frames = 300, elapsed msec = 5032, fps = 59.62
DispApp_deInit() - DONE !!!
DSS display test Passed!!
```
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX

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
Number of frames = 300, elapsed msec = 5032, fps = 59.62
DispApp_deInit() - DONE !!!
DSS display test Passed!!
```

::::

**Display Output**

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S

```{figure} ../../images/examples/dss_display_test_output.png
:align: center
:width: 50%

**Display Output**
```

::::


::::{only} SOC_AM62LX

```{figure} ../../images/examples/dss_display_test_am62l.png
:align: center
:width: 50%

**Display Output**
```

::::

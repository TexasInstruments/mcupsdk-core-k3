# DSS Colorbar Test
## Introduction


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   This example tests the inbuilt colorbar generation of overlay manager of DSS.
   DSS has two overlay managers OVR1 and OVR2. Each overlay manager supports a
   simple internal color bar insertion in each display output path to enable
   testing of display output interface without using the frame buffer data from the memory.
::::


::::{only} SOC_AM62LX
   This example tests the inbuilt colorbar generation of overlay manager of DSS.
   DSS has one overlay managers OVR1. Each overlay manager supports a
   simple internal color bar insertion in each display output path to enable
   testing of display output interface without using the frame buffer data from the memory.
::::


The colors are: White, Yellow, Cyan, Green, Magenta, Red, Blue, Black.
When internal colorbar is enabled, the overlay output data is replaced
by the predefined ARGB48 color bar data .The example configures Video Port and
Overlay managers using DSS driver IOCTLS. Since the colorbar is internal to DSS,
there is no Video pipeline configuration required. The example configures
Overlay Manager OVR1 to enable internal colorbar enable feature.


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   The example configures OLDI LVDS panel for Video Port 1.
   Please refer <a href="https://www.ti.com/tool/SK-LCD1">**SK-LCD1**</a> for panel
   details. The Video port timinng parameters are configured with respect to
   <a href="https://www.ti.com/tool/SK-LCD1">**SK-LCD1**</a>. Timing parameters can
   be configured using sysconfig option.

::::

```{figure} ../../images/examples/dss_colorbar_enable.png
:align: center

**DSS Colorbar Enable**
```

::::{only} SOC_AM62PX
   The example integrates bootloading funtionality with SBL on OSPI bootmedia. It
   also integrates Device manager functionality. The SBL stage 2 thread boots all
   the cores along with HLOS like Linux. Refer [SBL Booting Linux From OSPI](../../developer_guides/sbl_booting_linux_ospi.md) for boot
   flow sequence.
::::


## Supported Combinations
::::{only} SOC_AM62PX

   | Parameter      | Value                                  |
|---|---|
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/dss/dss_colorbar_test |

::::


::::{only} SOC_AM62X

   | Parameter      | Value                                                                         |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/dss/dss_colorbar_test |

::::


::::{only} SOC_AM62LX

   | Parameter      | Value                              |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/dss/dss_colorbar_test |

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

   - Update the wkup-r5 image in the flash config with dss_colorbar_test image.

           # 2nd stage bootloader with DM is flashed at 0x80000 or to whatever offset your bootloader is configured for
           --file=../../examples/drivers/dss/dss_colorbar_test/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/dss_colorbar_test.release.appimage.hs_fs --operation=flash --flash-offset=0x80000

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


::::{only} SOC_AM62LX

```
DispApp_init() - DONE !!!
DSS colorbar application started...
Display create complete!!
Starting display ... !!!
Display in progress ... DO NOT HALT !!!
Display delete complete!!
DispApp_deInit() - DONE !!!
DSS colorbar test Passed!!
```

::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S

```
Sciserver Testapp Built On: Dec  7 2023 14:12:00
Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
RM_PM_HAL Version: vMM.NN.PP
Starting Sciserver..... PASSED
DispApp_init() - DONE !!!
DSS colorbar application started...
Display create complete!!
Starting display ... !!!
Display in progress ... DO NOT HALT !!!
Display delete complete!!
DispApp_deInit() - DONE !!!
DSS colorbar test Passed!!
```

::::


## Display Output

```{figure} ../../images/examples/dss_colorbar_test_output.png
:align: center
:width: 50%

**Display Output**
```

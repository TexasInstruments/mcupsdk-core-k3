# DDR {#DRIVERS_DDR_PAGE}

[TOC]
\cond SOC_AM62X || SOC_AM62AX || SOC_AM62PX
\attention Please note that this driver is supported only on DM R5(WKUP R5) as part SBL examples. It is not supported on @VAR_SOC_MCU_CORE.
\endcond

The DDR driver provides API to configure the DDR module.

## Features Supported

- Ability to enable/disable DDR support in your application
- Ability to specify the DDR config generated using the "DDR SUBSYSTEM REGISTER CONFIGURATION" tool
\cond !SOC_AM62PX
- Ability to enable/disable inline ECC (1b and 2b) in the application
- Add regions for enabling inline ECC
\endcond

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

- Ability to specify the DDR config generated using the "DDR SUBSYSTEM REGISTER CONFIGURATION" tool
- Enables DDR, EMIF module clock when DDR module is selected
\cond !SOC_AM62PX
- Toggle inline ECC functionality
- Add regions for which inline ECC needs to be enabled
\endcond

## Features not Supported

NA

## Creating your own DDR config file

### Step 1: Generate a DDR config file for your EVM

- Goto https://dev.ti.com/sysconfig
- Select "Software Product" as "DDR SUBSYSTEM REGISTER CONFIGURATION"
- Select "Device" of interest, @VAR_SOC_NAME in this case.

\imageStyle{ddr_config_tool.png,width:60%}
\image html ddr_config_tool.png "DDR SUBSYSTEM REGISTER CONFIGURATION Tool"

- Configure the DDR parameters using the tool
- Save the generated `board_ddrReginit.h` in your project workspace or work area

\imageStyle{ddr_config_tool_save.png,width:90%}
\image html ddr_config_tool_save.png "Configure and save the generated file"

### Step 2: Add the generated DDR config file to your project

- Open SysConfig (\ref SYSCONFIG_INTRO_PAGE) for your project
- Add "DDR" as shown below

\imageStyle{ddr_sysconfig.png,width:60%}
\image html ddr_sysconfig.png "Add DDR via SysConfig"

- Specify the path to the generated `board_ddrReginit.h` file including the filename in the sysconfig text box
  as shown above

  - Make sure to use forward slash "/" in the file path so that this will work with linux as well as windows build
  - Make sure that path to this is file set in your application include path, as needed.

- Save the sysconfig project and build your application

## Creating your own LPDDR config file

### Step 1: Generate a LPDDR config file for your EVM

- Goto https://dev.ti.com/sysconfig
- Select "Software Product" as "DDR SUBSYSTEM REGISTER CONFIGURATION"
- Select "Device" of interest, @VAR_SOC_NAME in this case.

\imageStyle{ddr_config_tool.png,width:60%}
\image html ddr_config_tool.png "DDR SUBSYSTEM REGISTER CONFIGURATION Tool"

- Configure the LPDDR parameters using the tool
- Save the generated `board_ddrReginit.h` in your project workspace or work area. Rename the file as "board_lpddrReginit.h".

\imageStyle{lpddr_config_tool_save.png,width:90%}
\image html lpddr_config_tool_save.png "Configure and save the generated file"

### Step 2: Add the generated LPDDR config file to your project

- Open SysConfig (\ref SYSCONFIG_INTRO_PAGE) for your project
- Add "DDR" as shown below

\imageStyle{lpddr_sysconfig.png,width:60%}
\image html lpddr_sysconfig.png "Add DDR via SysConfig"

- Specify the path to the generated `board_lpddrReginit.h` file including the filename in the sysconfig text box
  as shown above

  - Make sure to use forward slash "/" in the file path so that this will work with linux as well as windows build
  - Make sure that path to this is file set in your application include path, as needed.

- Save the sysconfig project and build your application

\cond SOC_AM62X || SOC_AM62AX
## Enabling DDR inline ECC {#ENABLE_DDR_INLINE_ECC}

### Step 1: Enable inline ECC in the SBL sysconfig

- Open SysConfig file (\ref SYSCONFIG_INTRO_PAGE) of your SBL
- Enable inline ECC as shown below

\imageStyle{inline_ecc_sysconfig.png,width:60%}
\image html inline_ecc_sysconfig.png "Enable inline ECC via SysConfig"

- Add regions for which inline ECC needs to be enabled
- Save the sysconfig project and build your application

### Step 2: Generate linux appimage and u-boot.img

- If SBL is booting linux, 1/9th of DDR has to be reserved in the device tree for storing ECC values
- For u-boot flow,

\cond SOC_AM62X
  - Reduce the "DDR memory" to 8/9th of whole DDR size in u-boot device tree by modifying the device tree board file (arch/arm/dts/k3-am625-sk.dts and arch/arm/dts/k3-am62x-sk-common.dtsi)
\endcond
\cond SOC_AM62AX
  - Reduce the "DDR memory" to 8/9th of whole DDR size in u-boot device tree by modifying the device tree board file (arch/arm/dts/k3-am62a7-sk.dts)
\endcond
\cond SOC_AM62PX
  - Reduce the "DDR memory" to 8/9th of whole DDR size in u-boot device tree by modifying the device tree board file (arch/arm/dts/k3-am62p5-sk.dts)
\endcond
  - Rebuild a53 spl and u-boot.img with this change. Instructions to build A53 uboot can be found in the SDK Linux documentation at Foundational Components » U-Boot » User’s Guide » General Information » Build U-Boot
  - Generate the linux.appimage using the updated A53 SPL
  - Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details
  - Flash the linux.appimage and u-boot.img


- For Falcon mode (fast bootmode),

\cond SOC_AM62X
  - Reduce the "DDR memory" to 8/9th of whole DDR size in linux device tree by modifying the device tree board file (arch/arm64/boot/dts/ti/k3-am625-sk.dts and arch/arm64/boot/dts/ti/k3-am62x-sk-common.dtsi)
\endcond
\cond SOC_AM62AX
  - Reduce the "DDR memory" to 8/9th of whole DDR size in linux device tree by modifying the device tree board file (arch/arm64/boot/dts/ti/k3-am62a7-sk.dts)
\endcond
\cond SOC_AM62PX
  - Reduce the "DDR memory" to 8/9th of whole DDR size in linux device tree by modifying the device tree board file (aarch/arm64/boot/dts/ti/k3-am62p5-sk.dts)
\endcond
  - Rebuild the linux devicetree blob (dtb). For more information, refer the Linux SDK docs, section Foundational Components > Kernel > Users Guide
  - Generate the linux.appimage using the updated dtb file
  - Refer \ref LINUX_APPIMAGE_GEN_TOOL for more details
  - Flash the linux.appimage
\endcond

## Important Usage Guidelines

\cond SOC_AM64X || SOC_AM243X
- Please read the application note https://www.ti.com/lit/pdf/spracu1
  for projects having own board design with DDR.
\endcond
- Ideally DDR should be enabled in the bootloader application and the SDK bootloader by default
  enables DDR by default.

## Usage Overview

Include the below file to access the APIs
\snippet Ddr_sample.c include

Initialize DDR
\snippet Ddr_sample.c init_ddr

## Example Usage

NA

## API

\ref DRV_DDR_MODULE
# DDR

```{contents}
:depth: 2
:local:
```

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX

   :::{admonition} Attention
   Please note that this driver is supported only on DM R5(WKUP R5) as part SBL examples. It is not supported on {{ VAR_SOC_MCU_CORE }}.
   :::

::::


The DDR driver provides API to configure the DDR module.

## Features Supported

- Ability to enable/disable DDR support in your application
- Ability to specify the DDR config generated using the "DDR SUBSYSTEM REGISTER CONFIGURATION" tool
- Ability to enable/disable inline ECC (1b and 2b) in the application
- Add regions for enabling inline ECC

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


- Ability to specify the DDR config generated using the "DDR SUBSYSTEM REGISTER CONFIGURATION" tool
- Enables DDR, EMIF module clock when DDR module is selected
- Toggle inline ECC functionality
- Add regions for which inline ECC needs to be enabled
- Ability to set the SDRAM index based on the connected DDR size

## Features not Supported

NA

## Creating your own DDR config file

### Step 1: Generate a DDR config file for your EVM

(step-1-generate-a-ddr-config-file-for-your-evm)=

- Goto https://dev.ti.com/sysconfig
- Select "Software Product" as "DDR SUBSYSTEM REGISTER CONFIGURATION"
- Select "Device" of interest, {{ VAR_SOC_NAME }} in this case.
```{figure} ../../images/drivers/ddr_config_tool.png
:align: center
:alt: DDR SUBSYSTEM REGISTER CONFIGURATION Tool

DDR SUBSYSTEM REGISTER CONFIGURATION Tool
```


- Configure the DDR parameters using the tool
- Save the generated `board_ddrReginit.h` in your project workspace or work area
```{figure} ../../images/drivers/ddr_config_tool_save.png
:align: center
:alt: Configure and save the generated file

Configure and save the generated file
```


### Step 2: Add the generated DDR config file to your project

- Open SysConfig ([Using SDK with SysConfig](../../developer_guides/syscfg_intro.md)) for your project
- Add "DDR" as shown below

```{figure} ../../images/drivers/ddr_sysconfig.png
:align: center
:alt: Add DDR via SysConfig

Add DDR via SysConfig
```


- Specify the path to the generated `board_ddrReginit.h` file including the filename in the sysconfig text box
  as shown above

  - Make sure to use forward slash "/" in the file path so that this will work with linux as well as windows build
  - Make sure that path to this is file set in your application include path, as needed.

- Save the sysconfig project and build your application

## Creating your own LPDDR config file

### Step 1: Generate a LPDDR config file for your EVM

- Goto https://dev.ti.com/sysconfig
- Select "Software Product" as "DDR SUBSYSTEM REGISTER CONFIGURATION"
- Select "Device" of interest, {{ VAR_SOC_NAME }} in this case. The tool UI is the same as shown in [Step 1: Generate a DDR config file for your EVM](#step-1-generate-a-ddr-config-file-for-your-evm).
- Configure the LPDDR parameters using the tool
- Save the generated `board_ddrReginit.h` in your project workspace or work area. Rename the file as "board_lpddrReginit.h".
```{figure} ../../images/drivers/lpddr_config_tool_save.png
:align: center
:alt: Configure and save the generated file

Configure and save the generated file
```


### Step 2: Add the generated LPDDR config file to your project

- Open SysConfig ([Using SDK with SysConfig](../../developer_guides/syscfg_intro.md)) for your project
- Add "DDR" as shown below

```{figure} ../../images/drivers/lpddr_sysconfig.png
:align: center
:alt: Add LPDDR via SysConfig

Add LPDDR via SysConfig
```

- Specify the path to the generated `board_lpddrReginit.h` file including the filename in the sysconfig text box
  as shown above

  - Make sure to use forward slash "/" in the file path so that this will work with linux as well as windows build
  - Make sure that path to this is file set in your application include path, as needed.

- Save the sysconfig project and build your application


## Enabling DDR inline ECC

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_J722S

- For SDRAM data integrity, the DDRSS bridge supports inline ECC on the data written to or read from the SDRAM. ECC is stored
  together with the data so that a dedicated SDRAM device for ECC is not required. The 8-bit single error correction double error
  detection (SECDED) ECC data is calculated over 64-bit data quanta.
- For every 256-byte (AM62X) or 512-byte (AM62AX/AM62DX/AM62PX) data block, 32 or 64 bytes of ECC is stored inline respectively.
- Thus 1/9th of the total SDRAM space is used for ECC storage and the rest 8/9th is available for system use. From system point
  of view that 8/9th of the SDRAM data space are seen as consecutive byte addresses. DDRSS supports up to 3 ECC protected
  non-overlapping memory ranges.

:::{admonition} Attention
When inline ECC is enabled, the last 1/9th part of the DDR memory should not used. This rule applies irrespective of the size of the ECC regions.
:::

::::

### Step 1: Enable inline ECC in the SBL sysconfig

Open the SBL SysConfig file and configure the inline ECC settings as described below.

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_J722S

- Open SysConfig file ([Using SDK with SysConfig](../../developer_guides/syscfg_intro.md)) of your SBL
- Calculate the SDRAM index based on your connected DDR size and update the field
    - Formula: SDRAM index = log2(connected DDR size) - 16
- Enable inline ECC and add regions for which inline ECC needs to be enabled as shown.

```{figure} ../../images/drivers/inline_ecc_sysconfig.png
:align: center
:alt: Enable inline ECC via SysConfig

Enable inline ECC via SysConfig
```

- Things to take care when adding ECC regions,
    - The address (ECC start and end) has to be specified as an offset from the DDR region start
    - The ECC region is inclusive of the start and end address.
    - The ECC region start address and the size should be aligned to 0x10000 bytes
    - The ECC region size has to be in the powers of two and greater than 0x10000 bytes
    - ECC region size = ECC region end address - ECC region start address + 1
    - When ECC is enabled, BIST engine primes only the 8/9th portion of the given size. So the actual ECC end address will be
      lesser than the given ECC address.
    - For the given ECC region, the actual end address will be calculated and displayed in the sysconfig
    - When ECC is enabled, last 1/9th of the total SDRAM space is used for ECC storage and
      the rest 8/9th is available for system use.
    - So 8/9th of the given ECC region should not fall under the last 1/9th part of the DDR memory.

- Sysconfig files will get generated only if all the above conditions are met, otherwise it will throw an error.

:::{admonition} Note
If you are using older release and migrating to 09_02 SDK, please make sure the above conditions are met in the added ECC regions.
:::

- Save the sysconfig project.
- In the SBL, before using the DDR memory check if DDR init is done using the DDR_isInitDone function.
  ```
  while(!DDR_isInitDone())
  {
      ClockP_usleep(100);
  }
  ```
- Build the SBL

::::

### Step 2: Generate linux appimage and u-boot.img

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX

- If SBL is booting linux, last 1/9th of the DDR memory should not used anywhere in the linux and it has to be reserved in the device tree for storing ECC values.
- For u-boot flow:

:::::{only} SOC_AM62X

   - Reduce the "DDR memory" to 8/9th of whole DDR size in u-boot device tree by modifying the device tree board file for the following devices respectively
   - am62x-sk: ti-u-boot-2025.01+git/dts/upstream/src/arm64/ti/k3-am625-sk.dts
   - am62x-sip-sk: ti-u-boot-2025.01+git/dts/upstream/src/arm64/ti/k3-am6254xxl.dtsi
   - am62-sk-lp: ti-u-boot-2025.01+git/dts/upstream/src/arm64/ti/k3-am62-lp-sk.dts

:::::

:::::{only} SOC_AM62AX

   - Reduce the "DDR memory" to 8/9th of whole DDR size in u-boot device tree by modifying the device tree board file (arch/arm/dts/k3-am62a7-sk.dts)

:::::

:::::{only} SOC_AM62PX

   - Reduce the "DDR memory" to 8/9th of whole DDR size in u-boot device tree by modifying the device tree board file (arch/arm/dts/k3-am62p5-sk.dts)

:::::

- Rebuild a53 spl and u-boot.img with this change. Instructions to build A53 uboot can be found in the SDK Linux documentation at Foundational Components » U-Boot » User’s Guide » General Information » Build U-Boot
- Generate the linux.appimage using the updated A53 SPL
- Refer [Linux Appimage Generator Tool](../tools/tools_boot.md) for more details
- Flash the linux.appimage and u-boot.img

- For Falcon mode (fast bootmode):

:::::{only} SOC_AM62X

   - Reduce the "DDR memory" to 8/9th of whole DDR size in linux device tree by modifying the device tree board file (arch/arm64/boot/dts/ti/k3-am625-sk.dts and arch/arm64/boot/dts/ti/k3-am62x-sk-common.dtsi)

:::::

:::::{only} SOC_AM62AX or SOC_AM62DX

   - Reduce the "DDR memory" to 8/9th of whole DDR size in linux device tree by modifying the device tree board file (arch/arm64/boot/dts/ti/k3-am62a7-sk.dts)

:::::

:::::{only} SOC_AM62PX

   - Reduce the "DDR memory" to 8/9th of whole DDR size in linux device tree by modifying the device tree board file (arch/arm64/boot/dts/ti/k3-am62p5-sk.dts)

:::::

- Rebuild the linux devicetree blob (dtb). For more information, refer the Linux SDK docs, section Foundational Components > Kernel > Users Guide
- Generate the linux.appimage using the updated dtb file
- Refer [Linux Appimage Generator Tool](../tools/tools_boot.md) for more details
- Flash the linux.appimage

::::


## Important Usage Guidelines

Follow these guidelines when configuring and using the DDR driver.

::::{only} SOC_AM64X or SOC_AM243X

   - Please read the application note https://www.ti.com/lit/pdf/spracu1 for projects having own board design with DDR.

::::

- Ideally DDR should be enabled in the bootloader application and the SDK bootloader by default
  enables DDR by default.

## Usage Overview

Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Ddr_sample.c
:language: c
:lines: 2-27
```

### Initialize DDR

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Ddr_sample.c
:language: c
:lines: 34-34
```


## Example Usage

NA


## API Reference

```{doxygenfile} ddr/v0/ddr.h
```

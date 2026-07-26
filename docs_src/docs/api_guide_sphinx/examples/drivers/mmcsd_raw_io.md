# MMCSD RAW IO
## Introduction

This example demonstrates basic read write to the eMMC/SD Card. The MMC instance and the media connected to it are selectable via Sysconfig.

The example writes known data to a particular offset in the media and then reads it back. The read back data is then compared with the written known data.

When both the comparisons match, test result is passed otherwise failed.

## Supported Combinations
::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mmcsd/mmcsd_raw_io |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mmcsd/mmcsd_raw_io |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mmcsd/mmcsd_raw_io |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mmcsd/mmcsd_raw_io |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mmcsd/mmcsd_raw_io |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0_freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mmcsd/mmcsd_raw_io |

::::


::::{only} SOC_AM62LX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mmcsd/mmcsd_raw_io |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0_freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mmcsd/mmcsd_raw_io |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX and not SOC_AM62LX
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::


::::{only} SOC_AM62LX
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM62X
   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


   - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
::::


::::{only} SOC_AM275X
   **AM275X-EVM**
   - Ensure SW9 "MMC0_SEL" is in OFF postion to select eMMC

::::

## See Also

[MMCSD](../../components/drivers/mmcsd.md)

## Sample Output

```
[MMCSD RAW IO] Starting...
All tests have passed!!
```
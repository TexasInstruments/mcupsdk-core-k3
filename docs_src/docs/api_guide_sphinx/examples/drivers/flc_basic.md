# FLC Example

## Introduction

To understnd how to configure FLC and integrate it in your project, please go though [Configuring OptiFlash various IP](../../developer_guides/optiflash_configuration.md)

FLC example provides how to use FLC in applications and also shows how FLC brings in benefits.

The example writes known data to a particular offset in the flash using flash drivers and then reads it back using FLC. The read back data is then compared with the written known data.

When both the comparisons match, test result is passed otherwise failed.


## Supported Combinations

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/flc |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## Sample Output

:::{admonition} Note
DMA is not used
:::

```
Throughput without flc :9.28798 MiBps
Throughput with flc :62.06061 MiBps
All tests have passed!!
```

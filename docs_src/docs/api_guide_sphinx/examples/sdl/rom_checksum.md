# SDL ROM_CHECKSUM Example
## Introduction

This example demonstrates usage of the SDL ROM Checksum. This example is used to check the integrity of the data. Its work is to take a set of data associated with the memory regions of ROM and perform checksum on that data and then compare that resultant data value against a pre-determined golden vector value (golden vector has the expected value which should come as a result of 512-bit of hash message, golden vector is already defined and it has fixed address in ROM region).


::::{only} SOC_AM243X or SOC_AM62X or SOC_AM275X

   **Use Cases**

| Use Case | Description |
|---|---|
| UC-1 | Calculate ROM CHECKSUM from R5F Core. |


::::


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX

   **Use Cases**

| Use Case | Description |
|---|---|
| UC-1 | Calculate ROM CHECKSUM from MCU-R5F Core. |


::::


## Supported Combinations
::::{only} SOC_AM243X or SOC_AM62X or SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/rom_checksum/ |


::::


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/rom_checksum/ |


::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[ROM_CHECKSUM](../../components/sdl/rom_checksum.md)

## Sample Output

```
ROM Checksum Example Application
Compute ROM-Checksum Data integrity passed
```
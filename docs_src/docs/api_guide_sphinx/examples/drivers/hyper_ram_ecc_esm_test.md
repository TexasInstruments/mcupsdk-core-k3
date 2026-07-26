# HYPER RAM READ WRITE

## Introduction

This example simulates a 1b and 2b ECC error for HYPERRAM and waits for interrupt via the MAIN ESM instance. On receiving the interrupt, the handler clears the ECC error bit and restore the original value. If the interrupt is not received the test fails.

## Supported Combinations
:::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/board/hyperRam/hyperRam_ecc_esm_test

:::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[HYPERBUS](../../components/drivers/hyperbus.md)

## Sample Output

```
Waiting on Single bit Error Correction Interrupt...
1b ECC error detected and corrected
Waiting on Dual bit error detection Interrupt...
2b ECC error detected
All tests have passed
```

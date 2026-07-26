# Undefined Abort Test

## Introduction
This example shows the how custom data abort handler be implemented in the user application.

Provides information about the undef exception
1. `lr`: Link Register when the exception occurred
2. `spsr`: Saved Program Status Register

:::{note}
Please refer to R5F TRM for more information
:::

## Supported Combinations

:::{only} SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/kernel/dpl/test_undef/

:::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## Sample Output

:::{note}
this application do not gives any output. This goes inside the `HwiP_user_undefined_handler_c` function and loops forever there. User needs to pause the applcaition and see the values.
:::

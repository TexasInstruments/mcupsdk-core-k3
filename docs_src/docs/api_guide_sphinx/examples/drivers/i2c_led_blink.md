# I2C Led Blink
## Introduction

This example demonstrates setting of multiple LED at the same time connected to the same I2C controller.
The application will blink all the I2C controlled LED in the EVM.

Application exits after 10 iterations..

## Supported Combinations
::::{only} SOC_AM64X
   :::{admonition} Attention
   A53 NORTOS, A53 FREERTOS and A53 FREERTOS SMP support is experimental and is NOT supported by TI. \n
   :::
   :::


::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/i2c/i2c_led_blink |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/i2c/i2c_led_blink |

::::


::::{only} SOC_AM263X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/i2c/i2c_led_blink |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | m4fss0-0 freertos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/i2c/i2c_led_blink |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/i2c/i2c_led_blink |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/i2c/i2c_led_blink |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/i2c/i2c_led_blink |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/i2c/i2c_led_blink |
::::


::::{only} SOC_AM62LX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/i2c/i2c_led_blink |

::::


::::{only} SOC_AM263X
   **AM263X-CC**
   - Watch out for LEDs LD2, LD3, LD4, LD5, LD6, LD7, LD8, LD9, LD10, LD11 on the CC to blink which is controlled by I2C2.

   **AM263X-LP**
   - Watch out for LED D7, D8, D9, D10, D11, D12, D13, D14 on the LP to blink which is controlled by I2C1.
::::


::::{only} SOC_AM62X
   **AM62X-SK**
   - Watch out for LED LD11 to blink which is controlled by I2C1.
   **AM62X-SK-LP**
   - Watch out for LED LD7 to blink which is controlled by I2C1.

::::


::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM275X
   **AM62X-SK**
   - Watch out for LED LD5 to blink which is controlled by I2C1.

::::


::::{only} SOC_AM62PX or SOC_AM62LX
   **AM62X-SK**
   - Watch out for LED LD2 to blink which is controlled by I2C1.

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM62LX
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::


::::{only} SOC_AM62X or SOC_AM62PX
   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


   - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
::::

## See Also

[I2C](../../components/drivers/i2c.md)

## Sample Output

Shown below is a sample output when the application is run,

```
I2C LED Blink Test Started ...
LED will Blink for 10 loop ...
I2C LED Blink Test Passed!!
All tests have passed!!
```
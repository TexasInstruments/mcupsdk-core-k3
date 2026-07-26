# GPIO LED Blink
## Introduction

This example configures a GPIO pin connected to an LED on the EVM in output mode.
The application toggles the LED on/off for 10 seconds and exits.

::::{only} SOC_AM62X
   We do not have any LED connected direct from MCU connection for testing gpio pins on the board, So we are using MCU_HEADER pins for gpio pins for glowing LED.
   Make the following connections for this example to work on the SK-AM62.
    - Connect LED(high) to Pin 18 of J9.
    - Connect LED(ground) to Pin 27 of J9.

   For A53 example the User LED on the board will blink for 10 seconds and exits.
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
   To modify the example to use main domain GPIO, refer [Accessing main and wakeup domain peripherals from MCU domain](../../developer_guides/main_domain_peripheral_access.md)
::::

## Supported Combinations
::::{only} SOC_AM64X
   :::{admonition} Attention
   A53 NORTOS, A53 FREERTOS and A53 FREERTOS SMP support is experimental and is NOT supported by TI. \n
   :::
   :::


::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 freertos-smp |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | m4fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AM62LX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AM243X

   **AM243X-EVM**
| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

   **AM243X-LP**
| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AM273X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | c66ss0 nortos |
| Toolchain | ti-arm-clang, ti-c6000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AM263X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

::::


::::{only} SOC_AWR294X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/gpio/gpio_led_blink/ |

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


::::{only} SOC_AM64X
   - Watch out for LED LD26 on the EVM to blink which is controlled by MCU_GPIO0_5.
::::


::::{only} SOC_AM263X
   **AM263X-CC**
   - Watch out for LED LD13 on the CC to blink which is controlled by GPIO0_1.

   **AM263X-LP**
   - Watch out for LED DS2 on the LP to blink which is controlled by GPIO0_26.
::::


::::{only} SOC_AM243X

   **AM243X-EVM**
   - Watch out for LED LD26 on the EVM to blink which is controlled by MCU_GPIO0_5.

   **AM243X-LP**
   - Watch out for LED LD1 on the LP to blink which is controlled by GPIO0_22.

::::


::::{only} SOC_AM273X

   **AM273X-EVM**
   - Watch out for LED TPR_MSS_GPIO2 on the EVM to blink which is controlled by MSS_GPIO26.

::::


::::{only} SOC_AWR294X

   **AWR294X-EVM**
   - Watch out for LED MSS_GPIO2 on the EVM to blink which is controlled by GPIO26.

::::


::::{only} SOC_AM62LX

   **AM62LX-EVM**
   - Watch out for LED LD9 on the EVM to blink which is controlled by GPIO123.

::::

## See Also

[GPIO](../../components/drivers/gpio.md)

## Sample Output

Shown below is a sample output when the application is run,

```
GPIO LED Blink Test Started ...
LED will Blink for 10 seconds ...
GPIO LED Blink Test Passed!!
All tests have passed!!
```
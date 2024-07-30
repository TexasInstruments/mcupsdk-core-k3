# PMIC {#BOARD_PMIC_PAGE}

[TOC]

The PMIC driver provides API to control I2C based PMIC present in the board. It supports configuration
of various features/modules in the PMIC. I2C controller is used to read/write to the PMIC registers.
Refer to the corresponding PMIC datasheet for more details.

## Features Supported

- Support enable/disable watchdog
- Watchdog in trigger and Q&A mode with interrupt/reset support upon failure
- GPIO configuration
- Thermal monitoring
- Voltage monitoring

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

- Option to specify I2C address for the register pages
- Toggle watchdog functionality
- Watchdog mode selection
- Single/dual I2C communication mode selection
- Watchdog parameters configuration
- Warm reset option upon watchdog failure

## Features NOT Supported

- ADC
- CRC check for read and write

## Important Usage Guidelines

- Power cycle the board to restore the PMIC register configurations.

## Example Usage

Include the below file to access the APIs
\snippet Pmic_sample.c include

Instance Open Example
\snippet Pmic_sample.c open

Instance Close Example
\snippet Pmic_sample.c close

GPIO pin configuration example
\snippet Pmic_sample.c pmic_gpio_config

## API

\ref BOARD_PMIC_MODULE

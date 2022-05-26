# GPIO {#DRIVERS_GPIO_PAGE}

[TOC]

The General-Purpose Input/Output (GPIO) driver provides API to configure general-purpose pins as either inputs or outputs.
It also provided API to configure GPIO to produce host CPU interrupts and DMA synchronization events in different
interrupt/event generation modes.

## Features Supported

- Supports up to 16 GPIO signals per bank
- Supports up to 9 banks of interrupt and DMA trigger capable GPIOs
- Set/clear functionality

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

- Set pin direction: input or output
- Set interrupt trigger type
- Configuring pinmux based on selected pin

## Features NOT Supported

NA

## Important Usage Guidelines

- Note: Not all GPIO pins, banks are present in a particular device.
Refer device TRM for actual GPIO instances and pins supported

## Example Usage

Include the below file to access the APIs
\snippet Gpio_sample.c include

GPIO configuration as output
\snippet Gpio_sample.c output

GPIO configuration as input
\snippet Gpio_sample.c input

GPIO configuration for bank interrupt
\snippet Gpio_sample.c bank_interrupt

GPIO configuration for per pin interrupt
\snippet Gpio_sample.c pin_interrupt

## API

\ref DRV_GPIO_MODULE

# GPIO

```{contents}
:depth: 2
:local:
```

The General-Purpose Input/Output (GPIO) driver provides API to configure general-purpose pins as either inputs or outputs.
It also provided API to configure GPIO to produce host CPU interrupts and DMA synchronization events in different
interrupt/event generation modes.

## Features Supported

- Supports up to 16 GPIO signals per bank
- Supports up to 9 banks of interrupt and DMA trigger capable GPIOs
- Set/clear functionality

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


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

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Gpio_sample.c
:language: c
:lines: 4-4
```

### GPIO configuration as output

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Gpio_sample.c
:language: c
:lines: 20-33
```

### GPIO configuration as input

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Gpio_sample.c
:language: c
:lines: 40-52
```

### GPIO configuration for bank interrupt

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Gpio_sample.c
:language: c
:lines: 57-113
```

### GPIO configuration for per pin interrupt

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Gpio_sample.c
:language: c
:lines: 117-162
```



## API Reference

```{doxygenfile} gpio/v0/gpio.h
```

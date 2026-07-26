# PMIC

```{contents}
:depth: 2
:local:
```

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

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


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

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Pmic_sample.c
:language: c
:lines: 3-58
```

### Instance Open Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Pmic_sample.c
:language: c
:lines: 62-70
```

### Instance Close Example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Pmic_sample.c
:language: c
:lines: 75-77
```

### GPIO pin configuration example

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Pmic_sample.c
:language: c
:lines: 82-98
```


## API Reference

```{doxygenfile} pmic.h
```

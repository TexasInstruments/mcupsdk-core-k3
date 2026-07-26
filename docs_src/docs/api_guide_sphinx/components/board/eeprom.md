# EEPROM

```{contents}
:depth: 2
:local:
```

The EEPROM driver provides API to read and write to I2C based EEPROM devices present in the board.
The driver takes care of all sequencing necessary to perform writes across pages and
the application need not take care of the programming intricacies.

## Features Supported

- Read and write API from any offset
- Provide API to return EEPROM attributes like size, page size etc

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


- Option to select EEPROM type based on board
- Supported EEPROMs

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM62DX or SOC_AM275X or SOC_AM62LX or SOC_J722S

- AT24C

::::

::::{only} SOC_AM263X

- CAT24M

::::

::::{only} SOC_AM273X or SOC_AWR294X

- CAV24C

::::

- Option to set the I2C address of the EEPROM

## Features NOT Supported

NA

## Important Usage Guidelines

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62X or SOC_AM62AX or SOC_AM62PX or SOC_AM275X or SOC_J722S or SOC_AM263X or SOC_AM273X or SOC_AWR294X

None

::::

::::{only} SOC_AM62DX

J20 header pins needs to be shorted for having the write protect disabled for the EEPROM

::::

::::{only} SOC_AM62LX

J22 header pins needs to be shorted for having the write protect disabled for the EEPROM

::::

## Example Usage

Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Eeprom_sample.c
:language: c
:lines: 3-5
```

### EEPROM Read API

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Eeprom_sample.c
:language: c
:lines: 15-18
```

### EEPROM Write API

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Eeprom_sample.c
:language: c
:lines: 24-27
```


## API Reference

```{doxygenfile} eeprom.h
```

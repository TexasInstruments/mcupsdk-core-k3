# LED

```{contents}
:depth: 2
:local:
```

The LED driver provides API to control I2C/GPIO based LED present in the board.
The driver supports multiple LED control for the LEDs connected to the same
I2C controller using a single API which can be used to set LED ON/OFF for multiple LED at the same time.

## Features Supported

- API to turn ON/OFF LED
- Set LED mask using single API to set the LED state of multiple LEDs connected
to same controller at one go

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


- Option to select LED type based on board
- Supported LED
    - GPIO

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM62AX or SOC_AM62PX or SOC_AM62X or SOC_AM62DX or SOC_AM275X or SOC_AM62LX

   - TPIC2810 (I2C based)
   - IO Expander: TCA6424 (I2C based)
   - Based on the type of LED controller selected, the GPIO or I2C driver can be configured
   - In case of IO Expander based LED control, provides option to select the pin to which the LED is connected
   - In case of I2C based LED controller, ability to provide the I2C slave address of the controller

::::


## Features NOT Supported

- Set mask API is not supported for GPIO based LED as typically only one LED
is connected to a single instance of GPIO pin

## Important Usage Guidelines

None

## Example Usage

Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Led_sample.c
:language: c
:lines: 3-5
```

### LED ON API

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Led_sample.c
:language: c
:lines: 14-17
```

### LED OFF API

```{literalinclude} ../../../../docs/api_guide/doxy_samples/board/Led_sample.c
:language: c
:lines: 23-26
```


## API Reference

```{doxygenfile} led.h
```

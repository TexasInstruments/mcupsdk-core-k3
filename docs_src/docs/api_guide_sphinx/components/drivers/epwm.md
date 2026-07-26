# EPWM

```{contents}
:depth: 2
:local:
```

The ePWM driver provides API to configure various sub-modules within the ePWM module.
Below are the high level features supported by the driver.

## Features Supported

- Configuration of Time Base submodule to set time-base clock, counter mode,
- Configuration of Counter Compare submodule to specify duty cycle
- Configuration of Action Qualifier submodule to specify the type of action to take when time-base or counter-compare event occurs
- Configuration of Dead Band submodule to set rising-edge and falling-edge delay or bypass the module
- Configuration of Chopper submodule to generate a chopper frequency, set pulse width of the first pulse in the chopped pulse train or bypass the module
- Configuration of Trip Zone submodule to specify the tripping action to take when a fault occurs
- Configuration of event-trigger submodule to trigger an interrupt and rate at which these events occur

## SysConfig Features

:::{admonition} Note
It is strongly recommend to use SysConfig where it is available instead of using direct SW API calls. This will help simplify the SW application and also catch common mistakes early in the development cycle.
:::


- Selection of output channels.
- Configuring pinmux based on selected pin.
- Enabling TimeBase Clock based on selected ePWM instance.

## Features NOT Supported

- ePWM digital comparator modules
- ePWM high-resolution modules

## Important Usage Guidelines

NA

## Example Usage

Include the below file to access the APIs

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Epwm_sample.c
:language: c
:lines: 7-7
```

### Check external Synchronization signal

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Epwm_sample.c
:language: c
:lines: 15-25
```

### Get Timebase Counter direction

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Epwm_sample.c
:language: c
:lines: 32-42
```

### Configure Counter compare

```{literalinclude} ../../../../docs/api_guide/doxy_samples/drivers/Epwm_sample.c
:language: c
:lines: 49-62
```



## API Reference

```{doxygenfile} epwm/v0/epwm.h
```
